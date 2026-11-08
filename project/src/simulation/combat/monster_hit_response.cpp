#include "dnf/combat.hpp"
#include "dnf/collision.hpp"
#include "dnf/axis_motion.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
// The 1031 MOB adapter uses the same endpoint/clamp order as the existing
// monster combat attribute evaluator. 40JP's encrypted attribute ABI is not
// imported into this later PVF version.
double reactionEndpoint(const Script &source,const char *wanted,int level,double fallback) {
    const Json *selected=nullptr;
    bool excluded=false,category=false,traits=false;
    for(const auto &field:source.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[/ability category]"){category=false;continue;}
        if(tag=="[/category]"){traits=false;continue;}
        if(tag=="[/pvp]"||tag=="[/warroom]"||tag=="[/death tower]"){excluded=false;continue;}
        if(!excluded&&!category&&!traits&&tag==wanted) {
            if(selected)return fallback; // Ambiguous source is not silently last-wins.
            selected=&field.values;
        }
        if(tag=="[ability category]")category=true;
        if(tag=="[category]")traits=true;
        if(tag=="[pvp]"||tag=="[warroom]"||tag=="[death tower]")excluded=true;
    }
    if(!selected||selected->empty()||selected->size()>2)return fallback;
    for(const auto &value:*selected)
        if(!value.is_number()||!std::isfinite(value.get<double>()))return fallback;
    const double first=(*selected)[0].get<double>();
    if(selected->size()==1)return std::trunc(first);
    const auto range=source.values("[level]");
    if(range.size()!=2||!range[0].is_number_integer()||!range[1].is_number_integer())return fallback;
    const int low=range[0].get<int>(),high=range[1].get<int>();
    if(low<1||high<low)return fallback;
    const double fraction=low==high?0:double(std::clamp(level,low,high)-low)/(high-low);
    return std::trunc(first+((*selected)[1].get<double>()-first)*fraction);
}
int32_t reactionInteger(double value) {
    if(!std::isfinite(value))throw std::invalid_argument("Nonfinite monster reaction operand");
    return int32_t(std::clamp(std::trunc(value),double(INT32_MIN),double(INT32_MAX)));
}
int reactionRandom(int low,int high,Pcg32 &stream) {
    // 40JP uses rand()%1000 and integer interpolation over 0..999. Use the
    // world's saved, isolated stream instead of reseeding a process-global RNG.
    return low+int((int64_t(high)-low)*stream.bounded(1000)/999);
}
}
void World::applyResponse(Actor &target, const AttackResponse &response, int direction) {
    if(target.capturedBy>=0||target.dead) {
        target.hitReaction={};target.vx=target.vy=target.vz=0;return;
    }
    if(response.noReaction)return;
    MonsterHitReaction next;
    next.direction=direction<0?-1:1;
    double recovery=500;
    if(!target.monsterPath.empty()) {
        Script loadedSource;
        const Script *source=nullptr;
        if(target.combatAttributes&&
           normalize(target.combatAttributes->source.monster.path)==normalize(target.monsterPath))
            source=&target.combatAttributes->source.monster;
        else {loadedSource=pvf_.script(target.monsterPath);source=&loadedSource;}
        int level=target.combatAttributes?target.combatAttributes->level:1;
        if(!target.combatAttributes&&target.sourceStats.is_object()&&target.sourceStats.contains("level")&&
           target.sourceStats.at("level").is_number_integer()) {
            const auto &saved=target.sourceStats.at("level");
            if(saved.is_number_unsigned())level=int(std::min<uint64_t>(saved.get<uint64_t>(),INT32_MAX));
            else level=int(std::clamp<int64_t>(saved.get<int64_t>(),1,INT32_MAX));
        }
        next.weight=std::max(0.0,reactionEndpoint(*source,"[weight]",level,45000));
        recovery=reactionEndpoint(*source,"[hit recovery]",level,500);
    }
    const bool flight=response.knockDown||target.z>0||target.recovery!=0;
    if(!flight) {
        // 40JP 58E920/state3: hit recovery affects the duration, while the
        // standing-hurt slide is 400 units/s with a linear stop within 150 ms.
        double rate=response.hitDelayRate<0?1:response.hitDelayRate;
        if(response.attackType=="[magic]")rate*=.7;
        const int percent=std::max(0,reactionInteger(rate*100));
        next.state=3;
        next.remainingMs=std::clamp<int64_t>(int64_t(std::max(0,reactionInteger((2000-recovery)*.25)))*percent/100,1,INT32_MAX);
        next.accelerationRemainingMs=int32_t(std::min<int64_t>(150,next.remainingMs));
        // The native kind2 path takes the attack-context class at +124, not a
        // trailing hit-info operand. This caller supplies ordinary contacts.
        next.pushSpeed=400;
        next.accelerationX=reactionInteger(-1000*next.pushSpeed/next.accelerationRemainingMs)*next.direction;
        target.vx=next.direction*next.pushSpeed;target.vy=0;
        target.stunUntil=nowMs()+next.remainingMs;
    } else {
        // Exact call operands checked in ARAD.exe 58EE05..58EE22: third
        // sub_495430 parameter is 100, omitted from the delivered pseudocode.
        const double denominator=(next.weight-10000)*double(.0121f)+double(2100.0f);
        const auto convert=[&](double raw){return reactionInteger(4000.0*reactionInteger(raw)/denominator);};
        int push=convert(response.push)/2;
        if(push<0){next.direction=-next.direction;push=push==INT32_MIN?INT32_MAX:-push;}
        const int lift=convert(response.lift);
        int height=reactionInteger(double(lift)*lift/(-2*next.gravity));
        if(lift<0)height=-height;
        // Prior flying/downed state is the native substate>=1 flag. Ordinary
        // first-flight hits are not arbitrarily weakened on every contact.
        next.substate=target.recovery>=2||target.hitReaction.substate>=1?1:0;
        if(next.substate>=1)height/=4;
        auto candidateRandom=random_;
        auto &stream=candidateRandom.stream(RandomDomain::HitReaction,0);
        next.pushSpeed=reactionRandom(reactionInteger(push*.8),reactionInteger(push*1.2),stream);
        height=reactionRandom(reactionInteger(height*.9),reactionInteger(height*1.1),stream);
        next.launchHeight=height;next.peakHeight=0;
        next.state=4;
        target.vx=next.direction*next.pushSpeed;target.vy=0;
        // sub_4A0550 writes only when h*a<=0. Preserve this explicit gate for
        // negative lift; do not invent a negative-root throw absent in 40JP.
        if(height>=0)target.vz=std::sqrt(double(-2*next.gravity)*height);
        target.recovery=1;
        target.stunUntil=nowMs();
        random_=std::move(candidateRandom);
        events.push_back({tick,"relaunch",response.source,0,target.id,int(std::lround(target.vz))});
    }
    target.dir=-next.direction;
    target.hitReaction=next;
}
bool World::advanceMonsterHitReaction(Actor &target,int64_t movementMs) {
    auto &reaction=target.hitReaction;
    if(!reaction.state)return false;
    if(target.dead||target.capturedBy>=0) {
        reaction={};target.vx=target.vy=target.vz=0;return true;
    }
    if(target.hitStopped||movementMs<=0)return true;
    const int32_t elapsed=int32_t(std::min<int64_t>(movementMs,INT32_MAX));
    AxisMotion horizontal{float(target.vx),reaction.accelerationX,reaction.accelerationRemainingMs};
    const double displacement=advanceAxisMotion(horizontal,elapsed);
    target.vx=horizontal.velocity;
    reaction.accelerationX=horizontal.acceleration;
    reaction.accelerationRemainingMs=horizontal.accelerationRemainingMs;
    if(reaction.state==3&&reaction.accelerationRemainingMs==0)target.vx=0;
    // The native motion block validates successive pixels. A large tick cannot
    // tunnel through a source map wall simply because its endpoint is walkable.
    const int steps=std::max(1,int(std::ceil(std::abs(displacement))));
    const double step=displacement/steps;
    for(int i=0;i<steps;++i) {
        const double x=target.x+step;
        if(!canWalk(x,target.y)){target.vx=0;reaction.accelerationX=0;reaction.accelerationRemainingMs=0;break;}
        target.x=x;
    }
    target.vy=0;
    if(reaction.state==3) {
        reaction.remainingMs=std::max<int64_t>(0,reaction.remainingMs-elapsed);
        if(!reaction.remainingMs){reaction={};target.vx=target.vy=0;target.stunUntil=nowMs();}
        return true;
    }
    reaction.peakHeight=std::max(reaction.peakHeight,target.z);
    AxisMotion vertical{float(target.vz),reaction.gravity,-1};
    target.z+=advanceAxisMotion(vertical,elapsed);target.vz=vertical.velocity;
    reaction.peakHeight=std::max(reaction.peakHeight,target.z);
    if(target.z>0)return true;
    target.z=0;
    if(reaction.substate==0&&reaction.peakHeight>=5) {
        // 58FC30/state4 floor landing calls state4/conversion0: halve the
        // stored push in the SAME direction, peak-height/5, then the shared
        // two random interpolations. The separate /-5 branch is a wall hit.
        int bounce=reactionInteger(reaction.peakHeight)/5;
        const int push=reactionInteger(std::abs(target.vx))/2;
        auto candidateRandom=random_;
        auto &stream=candidateRandom.stream(RandomDomain::HitReaction,0);
        reaction.pushSpeed=reactionRandom(reactionInteger(push*.8),reactionInteger(push*1.2),stream);
        bounce=reactionRandom(reactionInteger(bounce*.9),reactionInteger(bounce*1.1),stream);
        target.vx=reaction.direction*reaction.pushSpeed;
        reaction.substate=1;reaction.launchHeight=bounce;reaction.peakHeight=0;
        target.vz=std::sqrt(double(-2*reaction.gravity)*bounce);
        random_=std::move(candidateRandom);
        return true;
    }
    target.vx=target.vy=target.vz=0;reaction={};
    // Keep the current 1031 down/sit ANI presentation. The 40JP state2 ground
    // hold is now owned by recovery2, so the existing get-up consumer can run.
    const auto motion=monsterMotion(target,"down");
    target.recovery=2;target.animation="down";target.animStart=nowMs();
    target.animationPath=motion->valid()?motion->base->path:"";
    if(motion->valid())target.animStart-=motion->base->duration-motion->base->frames.back().duration;
    target.stunUntil=nowMs()+(motion->valid()?std::clamp(motion->base->frames.back().duration,150,500):200);
    if(!motion->valid())events.push_back({tick,"monster_visual_issue","Missing/invalid down motion",target.id});
    return true;
}
void World::publishMonsterHitFeedback(Actor &target,const AttackResponse &response,int direction,
                                     int value,bool allowLegacyWeaponFallback,const CombatBox *contact,bool critical) {
    // Accepted non-miss contact owns ATK sound even on lethal/no-reaction hits.
    // Keeping it out of the movement response avoids route-specific duplicates.
    if(!response.sound.empty())events.push_back({tick,"sound",response.sound,0,target.id});
    const bool bull=target.monsterPath.find("/tau/")!=std::string::npos;
    const auto monsterSound=mapExplorationActive_?explorationMonsterSound(target,target.dead):
        std::string(bull?(target.dead?"TAU_DIE":"R_TAU_DMG"):(target.dead?"R_GOBLIN_DIE":"R_GOBLIN_DMG"));
    if(!monsterSound.empty())events.push_back({tick,"sound",monsterSound,target.id});
    events.push_back({tick,"hit_feedback",response.source,0,target.id,value});

    try {
        // 40JP sub_4E88A0 composes elemental/magic feedback AND a directional
        // spark. A single fallback spark discarded those independent layers.
        // Parser sub_4C99C0 identifies +120 as attack direction, despite the
        // decompiler's misleading nWeaponKind label. Current 1031 tokens win.
        struct Layer { std::string path; double scale=1; };
        std::vector<Layer> layers;
        auto add=[&](const std::string &path,double scale=1.0) {
            if(pvf_.has(path))layers.push_back({path,scale});
            else events.push_back({tick,"monster_visual_issue","Missing hit feedback ANI: "+path,target.id});
        };
        const std::string root="common/hiteffect/animation/";
        if(response.element=="[dark]"){add(root+"darkhit2.ani");add(root+"darkhit1.ani");}
        else if(response.element=="[light]")add(root+"lighthit.ani");
        if(response.attackType=="[magic]")add(root+"magichit3.ani");
        auto candidateRandom=random_;
        bool drewRandom=false;
        if(!response.hitEffect.empty()) {
            auto path=response.hitEffect;
            if(!pvf_.has(path)) {
                const auto slash=response.source.find_last_of('/');
                const auto relative=slash==std::string::npos?path:response.source.substr(0,slash+1)+path;
                if(pvf_.has(relative))path=relative;
            }
            add(path,critical?1.5:1);
        } else {
            std::string category=response.hitInfo.empty()||!response.hitInfo[0].is_string()?"":
                normalize(response.hitInfo[0].get<std::string>());
            // This fallback remains limited to the old Swordman selector.
            if(category.empty()&&allowLegacyWeaponFallback&&identity_.jobId==0)
                category=weapon%4==3?"[blow]":"[cut]";
            if(category=="[cut]"||category=="[blow]") {
                const bool large=candidateRandom.stream(RandomDomain::HitPresentation,0).bounded(2)==0;
                drewRandom=true;
                const std::string size=large?"large":"small";
                if(category=="[blow]")add(root+"knock"+size+".ani",critical?1.5:1);
                else {
                    const auto &angle=response.attackDirection;
                    // Current PVF and 40JP parser spell the horizontal token
                    // [hit horizon]. Native default direction is horizontal.
                    const int variant=angle=="[hit lift up]"?3:angle=="[hit down]"?1:2;
                    add(root+"slash"+size+std::to_string(variant)+".ani",critical?1.5:1);
                }
            }
        }
        if(layers.empty())return;
        if(pendingEffects_.size()+layers.size()>2048)throw std::length_error("Hit feedback visual queue is full");
        auto preparedIds=effectIds_;
        std::vector<Effect> prepared;
        prepared.reserve(layers.size());
        for(const auto &layer:layers) {
            const auto animation=assets_.animation(layer.path);
            if(animation->frames.empty()||animation->duration<=0)
                throw std::invalid_argument("Hit feedback ANI has no positive source duration: "+layer.path);
            const auto id=preparedIds.next();
            if(id>INT32_MAX)throw std::overflow_error("Hit feedback effect identity exhausted");
            Effect flash;flash.id=int(id);flash.skill=-2;flash.animation=layer.path;
            flash.x=flash.px=target.x;flash.y=flash.py=target.y;flash.z=target.z+55;flash.pz=flash.z;
            // Contact X/Z center, victim ground Y: 40JP sub_4E88A0.
            if(contact && std::isfinite(contact->x) && std::isfinite(contact->z) &&
                std::isfinite(contact->w) && std::isfinite(contact->d) && contact->w>=0 && contact->d>=0) {
                flash.x=flash.px=contact->x+contact->w*.5;
                flash.z=contact->z+contact->d*.5;flash.pz=flash.z;
            }
            flash.dir=direction;flash.born=nowMs();flash.imageScale=layer.scale;
            if(animation->duration>INT64_MAX-flash.born)throw std::overflow_error("Hit feedback expiry overflow");
            flash.expires=flash.born+animation->duration;flash.damageEnabled=false;flash.phase="hit-feedback";
            flash.resourceSource=response.source;prepared.push_back(std::move(flash));
        }
        // Reserve before publishing: malformed layers do not consume IDs or
        // random choices, and do not leave half of a compound hit effect.
        pendingEffects_.reserve(pendingEffects_.size()+prepared.size());
        for(auto &flash:prepared)pendingEffects_.push_back(std::move(flash));
        effectIds_=std::move(preparedIds);
        if(drewRandom)random_=std::move(candidateRandom);
    } catch(const std::exception &error) {
        events.push_back({tick,"monster_visual_issue",error.what(),target.id});
    }
}

void World::applyMonsterHurtMotion(Actor &m, const AttackResponse &response, double launch) {
    // A grounded hit must not turn a knocked-down actor into a standing hurt pose.
    if (m.dead || response.noReaction) return;
    {
        const int index = m.z > 0 || launch > 0 ? 1 : response.reactionIndex;
        const bool flying=m.hitReaction.state==4||m.recovery==1;
        std::string state = flying ? "down" : m.recovery == 2 && launch <= 0 ? "down" :
                            m.recovery == 3 && launch <= 0 ? "sit" : index ? "damage2" : "damage1";
        // 40JP combat_core case3: first standing hit selects rand()%2 when
        // both authored hurt poses exist; a further state3 hit alternates.
        // State4 binds the dedicated down/flight animation, not damage1/2.
        if (!flying&&m.z <= 0 && launch <= 0 && m.recovery < 2 && !response.knockDown) {
            std::array<std::string,2> choices;
            size_t count=0;
            std::string firstPath;
            for (const auto *candidate : {"damage1", "damage2"}) {
                const auto available = monsterMotion(m, candidate);
                if (available->valid() && (count==0 || available->base->path!=firstPath)) {
                    if(count==0)firstPath=available->base->path;
                    choices[count++]=candidate;
                }
            }
            if (count) state = choices.front();
            if (count > 1 && m.hitReaction.state==3 &&
                (m.animation=="damage1"||m.animation=="damage2")) {
                state=m.animation=="damage1"?"damage2":"damage1";
                events.push_back({tick,"monster_hurt_variant",state,m.id});
            } else if (count > 1) {
                // A separate saved domain cannot perturb damage, loot, AI or
                // corpse-particle draws. The chosen animationPath is persisted
                // by saveActor; restore never repeats this draw.
                auto candidateRandom = random_;
                // This domain has one world-scoped stream. Runtime handles are
                // renewed on restore and cannot be persistent random keys.
                auto &stream = candidateRandom.stream(RandomDomain::MonsterHurt, 0);
                state = choices.at(stream.bounded(uint32_t(count)));
                random_ = std::move(candidateRandom);
                events.push_back({tick, "monster_hurt_variant", state, m.id});
            }
        }
        const auto motion = monsterMotion(m, state);
        if (motion->valid()) {
            m.animation = state; m.animationPath = motion->base->path; m.animStart = nowMs(); m.poseFrame = -1;
            if (m.recovery == 2 && launch <= 0) {
                // A grounded follow-up holds the source lying pose; the long
                // intermediate down frames belong to controller-held flight.
                m.animStart -= motion->base->duration - motion->base->frames.back().duration;
            }
        } else events.push_back({tick, "monster_visual_issue",
                                 motion->error.empty() ? std::string("Missing ") + state : motion->error, m.id});
    }
}
} // namespace dnf
