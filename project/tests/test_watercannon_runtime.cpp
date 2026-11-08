#include "explicit_skill_preview_fixture.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/combat.hpp"
#include "dnf/damage_contact.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/renderer.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey water{8,26};
constexpr const char *tree="inferred-current1031-watercannon-tree-v1";
struct WaterFixture {
    World world;
    WaterFixture(Pvf &pvf,Assets &assets,const RegionCatalog &regions,ani_clock::ClockPolicy clock):world(pvf,assets,WorldRules::BetaFoundationV1) {
        Progression p(regions);world.enableExperimentalCharacters();CharacterStore store(std::filesystem::absolute("watercannon-isolated-fixture"));
        store.data["characters"][0]={{"name","SourceWater"},{"class","atmage"},{"identity",CharacterIdentity{8,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,p);enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
        world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
        auto &a=world.player;a.x=a.px=700;a.y=a.py=344;a.z=a.pz=0;a.vx=a.vy=a.vz=0;a.dir=1;a.mp=100000;a.hp=a.maxHp;
        a.dead=false;a.life=ActorLife::Alive;a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;
    }
    ExperimentalCharacterRuntime &runtime(){return *world.experimentalRuntime();}
    void configure(int level=1,int direction=1) {
        auto &r=runtime();r.configuration().configureBasicAttackTemplate(water,level,r.plan());r.configuration().assignSlot(0,water,r.plan());world.player.dir=direction;
    }
    void key(int key,bool down){world.enqueue({world.simulationNanoseconds(),key,down});}
    void start(){key(20,true);world.advanceSingleTick();key(20,false);}
    void ticks(int count){while(count-->0)world.advanceSingleTick();}
    Effect *flight(){for(auto &fx:world.effects)if(fx.phase=="source-nut:passive-object"&&fx.skill==26&&world.nowMs()<fx.expires)return &fx;return nullptr;}
    Effect *impact(){for(auto &fx:world.effects)if(fx.phase=="source-nut:watercannon-impact"&&world.nowMs()<fx.expires)return &fx;return nullptr;}
    bool reachFlight(){for(int i=0;i<90;++i){if(flight())return true;world.advanceSingleTick();}return false;}
    void target(int id,double x,double y,double z=0) {
        Actor a;a.id=id;a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";a.x=a.px=x;a.y=a.py=y;a.z=a.pz=z;a.dir=-world.player.dir;
        world.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");a.hp=a.maxHp=100000000;
        world.monsters.push_back(std::move(a));world.synchronizeEntityHandles();
    }
};
size_t hits(const World &w,int target=-1) {
    return size_t(std::count_if(w.events.begin(),w.events.end(),[&](const Event &e){return e.kind=="hit"&&e.name=="source_nut_passive_object"&&(target<0||e.target==target);}));
}
Json treeState(const World &w) {
    Json rows=Json::array();for(const auto &fx:w.effects)if(fx.sourceTreePolicy==tree)
        rows.push_back({{"id",fx.id},{"animation",fx.animation},{"xyz",{fx.x,fx.y,fx.z}},{"born",fx.born},{"expires",fx.expires},
            {"scale",fx.imageScale},{"auto",fx.autoLayerScale},{"parent",fx.alsParentId},{"follow",fx.alsFollowParent},
            {"clock",fx.animationClock?Json{{"elapsed",fx.animationClock->elapsedMs},{"frame",fx.animationClock->frame},{"visit",fx.animationClock->visit}}:Json()}});
    return rows;
}
}
Json runWaterCannonRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool passed,const std::string &message){checks.push_back({{"passed",passed},{"message",message}});
        if(!passed){writeJson("watercannon-runtime-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}};
    RegionCatalog regions(pvf,assets);
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        WaterFixture source(pvf,assets,regions,clock);source.configure();const auto &d=source.runtime().plan().sourceSkillActions.at(water);const auto &program=*d.movingImpact;
        check(d.motionSlot==47&&d.state==43&&d.objectId==24217&&program.impactObjectId==24256&&d.percentColumn==0&&program.sizeColumn==1,
            "Current1031 registration, CHR slot and two actual passive IDs reach moving/impact descriptor");
        check(d.objectAnimation->duration==580&&d.objectAnimation->globals.value("0",false)&&program.impactClip->duration==640,
            "Source flight loop is 580ms and independent impact clip 640ms");
        const auto generic=animationEffectEvents(pvf,assets,d.animation.memberPath),reviewed=animationEffectEvents(pvf,assets,d.animation.memberPath,tree);
        check(generic.events.size()==1&&!generic.diagnostics.empty()&&reviewed.diagnostics.empty()&&reviewed.events.size()==2&&
            reviewed.events[1].kind==EffectEventKind::DrawOnlyFollowParent,"Follow-parent is admitted only through this exact source-tree policy; generic behavior remains diagnostic");
        check(source.world.runtimeSkillPolicy(water).implemented&&!source.world.runtimeSkillPolicy({8,236}).implemented&&!source.world.runtimeSkillPolicy({8,51}).implemented,
            "Independent normal base admission leaves TP/elemental-chain closed; this suite still exercises explicit preview operands");
        for(const int level:{1,10})for(const int direction:{-1,1})for(const bool opposite:{false,true}) {
            WaterFixture f(pvf,assets,regions,clock);f.configure(level,direction);auto &w=f.world;auto &r=f.runtime();
            const auto normal=w.skillState().snapshot(w.nowMs());const auto &descriptor=r.plan().sourceSkillActions.at(water);
            const auto operands=evaluateSourceSkillAction(descriptor,*r.plan().skills.at(water).data,level);const auto &moving=*operands.movingImpact;
            check(moving.travelMs==850&&moving.distance==425&&moving.speed==400&&moving.sizePercent>30,"Actual SKL columns determine flight time, distance, speed and independent image/box scale");
            // Exercise the actual speed snapshot instead of a synthetic delay
            // table: this body has a commented attack-speed call in source.
            check(bool(w.speedAttributes_),"Source fixture has real equipped speed attributes");w.speedAttributes_->attackPerMille=2200;
            const auto mp=w.player.mp;const auto startMs=w.nowMs();f.start();f.key(opposite?(direction>0?0:1):(direction>0?1:0),true);
            const auto paid=w.player.mp;check(paid<mp&&r.remainingCooldown(water,w.nowMs())>0,"Slot cast charges actual MP and source cooldown once");
            check(f.reachFlight(),"Actual frame flag creates a source flying entity");const auto root=*f.flight();
            check(root.born-startMs>=400&&root.born-startMs<=417&&root.expires-root.born==850,
                "Fixed source body flag occurs at 400ms despite 2200 attack-speed snapshot; PO lifetime is 850ms");
            check(std::abs(root.imageScale-moving.sizePercent/100.0)<1e-9&&root.autoLayerScale==root.imageScale&&root.loop&&
                root.z==70&&root.y==345,"Flight visual has independent level scale, source XYZ and looping clip");
            bool box=false;for(const auto &volume:w.attackVolumes)if(volume.skillId==26) {
                check(volume.sourceAttackFamily=="source_watercannon_flight","No borrowed body type15 adds an extra water hit");
                for(const auto &raw:descriptor.objectAnimation->frames[0].boxes)if(raw.type==15)
                    box|=volume.box.w==int(raw.w*root.imageScale)&&volume.box.h==int(raw.h*root.imageScale)&&volume.box.d==int(raw.d*root.imageScale);
            }
            check(box,"Real AttackVolume consumes all three scaled box extents");
            const auto origin=root.x;std::set<int> tails;bool looped=false,bodyEndedWithFlight=false,childScale=false,tailFlip=false;
            double farthest=0;Json sample;
            while(w.nowMs()<root.expires) {
                for(const auto &fx:w.effects)if(fx.sourceTreePolicy==tree&&w.nowMs()<fx.expires) {
                    if(fx.id==root.id) {
                        const auto elapsed=std::min<int64_t>(w.nowMs()-root.born,850);
                        check(std::abs(fx.x-origin-direction*425.0*elapsed/850)<1e-6,"Actual projectile position uses its independent elapsed source clock");
                        farthest=std::max(farthest,std::abs(fx.x-origin));looped|=fx.animationClock&&fx.animationClock->loopCount>0;
                        bodyEndedWithFlight|=!r.attacking();
                    } else {
                        childScale|=std::abs(fx.imageScale-root.imageScale)<1e-9;
                        check(fx.speed==0&&fx.trajectoryMs==0&&!fx.attached,"Source ALS children do not inherit projectile integration or player attachment");
                        if(fx.phase=="source-watercannon:inferred-follow-tail-clip-or-parent-lifetime-v1") {
                            tails.insert(fx.id);check(fx.alsParentId==root.id&&fx.expires==std::min(fx.born+500,root.expires),"Each repeated tail has independent 500ms or parent-lifetime bound");
                            const auto parent=std::find_if(w.effects.begin(),w.effects.end(),[&](const auto &e){return e.id==root.id;});
                            check(parent!=w.effects.end()&&fx.x==parent->x&&fx.y==parent->y-1&&fx.z==parent->z,"Follow-parent tail follows current projectile XYZ plus unscaled source offset");
                            const auto ani=assets.animation(fx.animation);tailFlip|=ani->samplePose(0,false).scaleY<0;
                        }
                    }
                }
                if(sample.is_null()&&w.nowMs()-root.born>=600)sample=treeState(w);
                w.advanceSingleTick();
            }
            check(looped&&bodyEndedWithFlight&&farthest>400&&tails.size()==2&&childScale&&tailFlip,
                "Source loop revisits frame0 once, creates two independent tails, preserves original flip and outlives fixed 960ms body");
            check(!f.flight()&&!f.impact()&&treeState(w).empty()&&r.snapshotDiagnostics().at("source_nut_entities")==0&&hits(w)==0,
                "Empty cast retires the flying PO and complete tail tree without a fake impact or damage");
            check(w.player.mp==paid&&w.skillState().snapshot(w.nowMs())==normal,"MP is not charged per tick and preview never mutates normal learning ledger");
            const auto diagnostics=w.experimentalDiagnostics().at("world");bool expectedRecoil=false;
            for(const auto &row:diagnostics)if(row.value("code",std::string())=="source_watercannon_recoil")expectedRecoil|=row.at("opposite_input")==opposite&&
                row.at("source_velocity")== (opposite?moving.alternateRecoilVelocity:moving.recoilVelocity);
            check(expectedRecoil,"Current NUT opposite-input branch selects weak recoil through restored AxisMotion consumer");
            evidence.push_back({{"phase","empty_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",direction},{"opposite_input",opposite},{"tail_sample",sample}});
        }
        // Spawn privately on a true accepted contact, then preserve the typed
        // original target exclusion while a neighboring actual Goblin takes
        // the independent impact exactly once.
        {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Hit fixture reaches real flight");auto &w=f.world;const auto flight=*f.flight();
            f.target(1,flight.x+15,flight.y,flight.z);f.target(2,flight.x+55,flight.y,flight.z);w.randomStreams()=RandomStreams(67);
            for(int i=0;i<20&&!f.impact();++i)w.advanceSingleTick();check(f.impact()!=nullptr,"Actual nonmiss flight contact creates one impact entity");const auto explosion=*f.impact();
            check(explosion.y==flight.y+1&&explosion.z==flight.z&&explosion.imageScale==.95&&explosion.autoLayerScale==1&&
                explosion.expires-explosion.born==640&&explosion.sourceObject==program.impactObject.memberPath,"Impact uses contact position, source Y+1, own 0.95 size and 640ms clip");
            check(hits(w,1)==1&&!f.flight(),"First accepted target retires flying entity immediately and takes one flight hit");
            const auto firstHandle=w.monsters[0].handle;check(explosion.projectileSource.at("excluded_target")==firstHandle.json(),"Impact exclusion is full EntityHandle incarnation");
            bool impactChild=false,launch=false,ownReaction=false;
            for(int i=0;i<55;++i) {
                for(const auto &fx:w.effects)if(fx.alsParentId==explosion.id&&fx.sourceTreePolicy==tree)impactChild|=fx.imageScale==1&&fx.autoLayerScale==1;
                for(const auto &a:w.monsters){launch|=a.z>flight.z&&a.vz>0;ownReaction|=!a.animationPath.empty()&&a.animationPath.rfind("monster/goblin/",0)==0;}
                w.advanceSingleTick();
            }
            check(hits(w,1)==1&&hits(w,2)==1&&impactChild&&launch&&ownReaction,"Original target excluded; second source target takes one scaled impact with ATK lift/down, own ANI and unscaled child layer");
            check(treeState(w).empty()&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==0,"Accepted impact retires runtime collision, visible root and nested graph");
            evidence.push_back({{"phase","real_goblin_contacts"},{"clock",ani_clock::policyName(clock)},{"flight",flight.projectileSource},{"impact",explosion.projectileSource},{"events",w.eventLog()}});
        }
        {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Outgoing MISS fixture reaches source flight");auto &w=f.world;const auto root=*f.flight();
            f.target(1,root.x+15,root.y,root.z);
            // Explicit diagnostic injection only into the existing resolved
            // miss probability; skill, source geometry and transaction stay
            // production consumers. No native Goblin probability is claimed.
            w.monsters[0].combatAttributes->attributes->damageMissBonusPercent={100,100};
            w.monsters[0].combatAttributes->attributes->damageMissBonusSource={{"policy","diagnostic-water-miss100"}};
            const auto hp=w.monsters[0].hp;w.advanceSingleTick();
            check(f.flight()&&!f.impact()&&w.monsters[0].hp==hp&&hits(w)==0&&std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return e.kind=="miss";})==1,
                "Actual outgoing MISS records contact once and keeps the original flight without spawning an impact");
            const auto current=*f.flight();f.target(2,current.x+15,current.y,current.z);w.randomStreams()=RandomStreams(67);
            for(int i=0;i<4&&!f.impact();++i)w.advanceSingleTick();
            check(f.impact()&&hits(w,2)==1&&f.impact()->projectileSource.at("excluded_target")==w.monsters[1].handle.json(),
                "The same real flight can miss one target then impact the next nonmiss target with its own exclusion handle");
            evidence.push_back({{"phase","outgoing_miss_then_hit"},{"classification","diagnostic-miss-probability; actual source contact consumers"},{"events",w.eventLog()}});
        }
        {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Handle-incarnation fixture reaches source flight");auto &w=f.world;const auto root=*f.flight();
            f.target(1,root.x+15,root.y,root.z);w.randomStreams()=RandomStreams(67);
            for(int i=0;i<4&&!f.impact();++i)w.advanceSingleTick();check(f.impact()&&hits(w,1)==1,"Handle fixture gets original accepted flight hit");
            const auto old=w.monsters[0].handle;auto replacement=w.monsters[0];replacement.handle=w.entities_.renew(old);replacement.hp=replacement.maxHp;
            replacement.x=replacement.px=f.impact()->x;replacement.y=replacement.py=f.impact()->y;replacement.z=replacement.pz=f.impact()->z;
            replacement.vx=replacement.vy=replacement.vz=0;replacement.recovery=0;replacement.stunUntil=0;replacement.hitStopped=false;replacement.hitStopTicks=0;
            replacement.animation="stay";replacement.animationPath.clear();replacement.animationClock.reset();replacement.animStart=w.nowMs();w.monsters[0]=std::move(replacement);
            check(w.monsters[0].handle.id==old.id&&w.monsters[0].handle.generation!=old.generation,"Diagnostic renewal reuses numeric entity ID with a new valid generation");
            f.ticks(3);check(hits(w,1)==2,"Impact excludes the original incarnation, while same-ID new generation receives one independent impact hit");
        }
        {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Late impact-contact fault reaches source flight");auto &w=f.world;const auto root=*f.flight();
            f.target(1,root.x+15,root.y,root.z);f.target(2,root.x+55,root.y,root.z);w.randomStreams()=RandomStreams(67);
            for(int i=0;i<4&&!f.impact();++i)w.advanceSingleTick();check(f.impact()&&hits(w,1)==1&&hits(w,2)==0,"Flight commits original target before later impact contact");
            w.monsterDamageWindows_[w.monsters[1].handle]=initialMonsterDamageWindow(pvf,pvf.script(w.monsters[1].monsterPath),uint64_t(w.nowMs()));w.monsterEventAiPending_.resize(1024);
            const auto hp1=w.monsters[0].hp,hp2=w.monsters[1].hp;const auto random=w.randomStreams().snapshot(),ids=w.idSources().snapshot();
            w.advanceSingleTick();check(w.monsters[0].hp==hp1&&w.monsters[1].hp==hp2&&hits(w,1)==1&&hits(w,2)==0&&w.randomStreams().snapshot()==random&&w.idSources().snapshot()==ids&&f.impact(),
                "A later impact-target accepted-event fault preserves the earlier committed flight hit and publishes no failing HP/RNG/ID change");
            w.monsterEventAiPending_.clear();f.ticks(3);check(hits(w,1)==1&&hits(w,2)==1,"Repairing late impact fault retries uncommitted target once without repeating first hit");
        }
        for(const std::string fault:{"impact_attack_id","impact_visual_id","impact_image","accepted_queue"}) {
            WaterFixture f(pvf,assets,regions,clock);auto plan=std::make_shared<ExperimentalCharacterPlan>(f.runtime().plan());
            f.world.experimentalRuntime_=std::make_unique<ExperimentalCharacterRuntime>(plan);f.runtime().setAnimationClockPolicy(clock);f.configure();f.start();check(f.reachFlight(),"Late-fault fixture reaches real flight before injection");
            auto &w=f.world;const auto flying=*f.flight();f.target(1,flying.x+15,flying.y,flying.z);
            if(fault=="impact_attack_id")w.ids_.attacks=MonotonicIds(0);
            if(fault=="impact_visual_id")w.effectIds_=MonotonicIds(0);
            if(fault=="impact_image")plan->sourceSkillActions.at(water).movingImpact->impactAnimation.memberPath="missing/water-impact.ani";
            if(fault=="accepted_queue") {w.monsterDamageWindows_[w.monsters[0].handle]=initialMonsterDamageWindow(pvf,pvf.script(w.monsters[0].monsterPath),uint64_t(w.nowMs()));w.monsterEventAiPending_.resize(1024);}
            const auto random=w.randomStreams().snapshot(),ids=w.idSources().snapshot();const auto effectIds=w.effectIds_.snapshot();const auto hp=w.monsters[0].hp;
            const auto entitySequence=f.runtime().snapshotDiagnostics().at("source_nut_entity_sequence");w.advanceSingleTick();
            check(w.monsters[0].hp==hp&&w.randomStreams().snapshot()==random&&w.idSources().snapshot()==ids&&w.effectIds_.snapshot()==effectIds&&
                f.runtime().snapshotDiagnostics().at("source_nut_entity_sequence")==entitySequence&&f.flight()&&!f.impact()&&hits(w)==0,
                "Late "+fault+" fault rejects this source contact with no HP/RNG/allocator/impact publication");
            evidence.push_back({{"phase","late_fault"},{"fault",fault},{"clock",ani_clock::policyName(clock)},{"diagnostics",w.experimentalDiagnostics().at("world")}});
        }
        for(const std::string reason:{"scene","death","explicit_cancel"}) {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Cleanup fixture reaches actual flight and children");
            if(reason=="scene")f.world.changeScene();else if(reason=="death"){f.world.player.dead=true;f.world.player.life=ActorLife::Dying;}else f.world.idle();
            f.ticks(2);check(treeState(f.world).empty()&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==0,"Actual "+reason+" retires water collision, root, follow-tail and nested layers");
        }
        {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.world.freeCd=true;f.start();check(f.reachFlight(),"No-CD fixture reaches first independent PO");auto &w=f.world;
            auto reaction=w.prepareNeutralPlayerReaction(w.player);w.publishNeutralPlayerReaction(reaction);f.start();
            for(int i=0;i<35&&f.runtime().snapshotDiagnostics().at("source_nut_entities")!=2;++i)w.advanceSingleTick();
            check(f.runtime().snapshotDiagnostics().at("source_nut_entities")==2,"No-CD plus an ordinary prepared cancellation allows two independent source POs with distinct identities");
            std::set<int> roots;for(const auto &fx:w.effects)if(fx.phase=="source-nut:passive-object"&&w.nowMs()<fx.expires)roots.insert(fx.id);
            check(roots.size()==2,"Both no-CD source entities have separate actual rendered roots");w.changeScene();f.ticks(2);check(treeState(w).empty(),"Scene reset cleans both no-CD roots and every descendant");
        }
        // The production prepared-reaction service consumes the live moving
        // state. Both alternatives allocate before damage; ordinary reaction
        // preserves independent POs, lethal publication retires them together.
        for(const bool afterBody:{false,true})for(const bool lethal:{false,true}) {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Prepared moving reaction reaches source flight");
            if(afterBody)while(f.runtime().attacking())f.world.advanceSingleTick();auto &w=f.world;
            check(f.runtime().sourceMovingReactionReady()&&w.neutralPlayerReactionGate(w.player).empty(),"Prepared ground incoming gate accepts exact source moving state before/after body completion");
            const auto treeBefore=treeState(w),runtimeBefore=f.runtime().snapshotDiagnostics(),ids=w.idSources().snapshot(),random=w.randomStreams().snapshot();
            const auto cooldown=f.runtime().cooldownSnapshot(w.nowMs());const auto mp=w.player.mp;
            auto prepared=w.prepareNeutralPlayerReaction(w.player);
            check(treeState(w)==treeBefore&&f.runtime().snapshotDiagnostics()==runtimeBefore&&w.idSources().snapshot()==ids&&w.randomStreams().snapshot()==random,
                "Preparation alone does not cancel live body/entities or change gameplay allocator/random state");
            if(lethal){w.player.hp=0;w.player.dead=true;w.player.life=ActorLife::Dying;}w.publishNeutralPlayerReaction(prepared);
            check(!f.runtime().attacking()&&f.runtime().cooldownSnapshot(w.nowMs())==cooldown&&w.player.mp==mp,
                "Prepared moving reaction cancels body/recoil while preserving paid MP and source cooldown");
            check(lethal?treeState(w).empty()&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==0&&w.experimentalAdapter_->neutralReactionReady():
                treeState(w)==treeBefore&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==1,
                lethal?"Lethal prepared publication clears runtime PO, root/tails and corresponding ledger in the same commit":"Ordinary prepared publication preserves independent source PO, clocks and typed hit ledger");
        }
        for(const bool afterBody:{false,true})for(const std::string mode:{"ordinary","lethal","miss","reaction_fault"}) {
            WaterFixture f(pvf,assets,regions,clock);f.configure();f.start();check(f.reachFlight(),"Incoming ACT fixture reaches actual source flight");
            if(afterBody)while(f.runtime().attacking())f.world.advanceSingleTick();auto &w=f.world;
            constexpr const char *doll="monster/act8/wooden_doll_nomnal/wooden_doll_nomnal.mob";
            Actor actor;actor.id=1;actor.monsterPath=doll;actor.x=actor.px=200;actor.y=actor.py=344;actor.dir=1;
            w.initializeMonsterAttributes(actor,mode=="miss"?65:1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");w.monsters.push_back(std::move(actor));w.synchronizeEntityHandles();
            ActWorldHost host(w,pvf,assets,"water-incoming:"+sha256(assets.staticBytes("audio.xml")));
            const auto route=selectMonsterAction(pvf,pvf.script(doll),"attack",0);const auto compiled=host.compile(route.resolvedPath);
            check(route.ok&&compiled.ok,"Incoming regression uses actual wooden-doll MOB slot/ACT/ATK");
            ActBindRequest bind;bind.owner=w.monsters[0].handle;bind.instanceId=40;bind.actionId=140;bind.tick=uint64_t(w.tick);bind.simulationMs=uint64_t(w.nowMs());
            bind.randomSeed=7;bind.randomSequence=9;bind.clockMode=ActClockMode::ExternalAnimationDelta;
            check(host.bind(compiled.program,bind,{},false,&route).ok,"Incoming actual source ACT binds while water entity is live");
            bool attempted=false;Json sample;
            w.setObjectTick([&](World &current){
                if(attempted)return;attempted=true;
                auto &collision=host.state_.collisions.at(40);const auto attackAni=assets.animation(collision.baseAnimation);
                const auto bodyAni=assets.animation(current.player.animationPath);const auto bodyFrame=current.player.animationClock?current.player.animationClock->frame:size_t(0);
                bool aligned=false;uint64_t phase=0;
                for(size_t index=0;index<attackAni->frames.size()&&!aligned;++index) {
                    for(const auto &box:attackAni->frames[index].boxes)if(box.type==15)for(const auto &hurt:bodyAni->frames.at(bodyFrame).boxes)
                        if(hurt.type==14&&!aligned&&box.z+box.d>=hurt.z&&hurt.z+hurt.d>=box.z) {
                            const double hx=current.player.x+(current.player.dir>0?hurt.x:-double(hurt.x)-hurt.w)+hurt.w*.5;
                            auto &owner=current.monsters[0];owner.dir=1;owner.x=owner.px=hx-box.x-box.w*.5;
                            owner.y=owner.py=current.player.y+hurt.y+hurt.h*.5-box.y-box.h*.5;
                            auto &instance=host.state_.instances.at(40);instance.animationUs=phase;instance.firstAdvance=false;aligned=true;
                        }
                    if(!aligned)phase+=uint64_t(attackAni->frames[index].duration)*1000;
                }
                check(aligned,"Incoming source phase/placement aligns real XYZ type15 and current own type14 without synthetic boxes");
                const auto attack=readActCollisionAttack(pvf.script(collision.currentAttack));
                const auto policy=DamageResolutionPolicy::inferredPveDamageV1(current.combatAttributes_->damageConstants);
                DamageRequest request;request.attacker=current.monsters[0].handle;request.target=current.player.handle;
                request.attackInstance=collision.attackInstance;request.hitIndex=collision.hitIndex;
                request.attackerStats=makeDamageCombatant(*current.monsters[0].combatAttributes,policy);request.targetStats=makeDamageCombatant(*current.combatAttributes_);
                request.attack=attack.damage;request.contactRange=DamageContactRange::Melee;
                const auto resistance=evaluateCharacterStatusResistances(current.combatAttributes_->pureChr,current.characterSource(),current.combatAttributes_->equipmentSources,current.combatAttributes_->qualificationLevel);
                bool selected=false;
                for(uint64_t seed=0;seed<65536&&!selected;++seed) {RandomStreams random(seed);const auto prepared=prepareDamageContact(request,policy,resistance,current.statuses_,random,uint64_t(current.nowMs()));
                    if(prepared.ready()&&prepared.resolution.missed==(mode=="miss")){current.randomStreams()=RandomStreams(seed);selected=true;}}
                check(selected,"Incoming regression chooses reproducible real source MISS/nonmiss seed");
                current.player.hp=mode=="lethal"?1:1000000;current.player.maxHp=std::max(current.player.maxHp,current.player.hp);
                if(mode=="reaction_fault") {check(bool(current.equippedAppearance_),"Reaction resource fault has real equipped appearance");
                    auto &motions=current.equippedAppearance_->bodyMotions;const auto down=current.characterSource().motion("[down motion]");
                    motions.erase(std::remove_if(motions.begin(),motions.end(),[&](const auto &m){return m.resource.path==down;}),motions.end());}
                const auto runtime=f.runtime().snapshotDiagnostics(),beforeTree=treeState(current),random=current.randomStreams().snapshot(),ids=current.idSources().snapshot();
                const auto hp=current.player.hp,mp=current.player.mp;const auto cooldown=f.runtime().cooldownSnapshot(current.nowMs());
                const SimulationStep step{uint64_t(current.tick),uint64_t(current.nowMs()),uint32_t(current.nowMs()-FixedStepClock::millisecondsAtTick(current.tick-1))};
                const auto result=host.advance(step,{{40,1}});
                const auto count=size_t(std::count_if(current.events.begin(),current.events.end(),[](const Event &event){return event.kind=="player_hit"&&event.name=="act_source";}));
                if(mode=="reaction_fault")check(count==0&&current.player.hp==hp&&treeState(current)==beforeTree&&f.runtime().snapshotDiagnostics()==runtime&&
                    current.randomStreams().snapshot()==random&&current.idSources().snapshot()==ids,"Actual incoming late reaction-resource fault preserves current water runtime/tree, HP, RNG and IDs");
                else if(mode=="miss")check(result.ok&&count==0&&current.player.hp==hp&&treeState(current)==beforeTree&&f.runtime().snapshotDiagnostics()==runtime,
                    "Actual incoming source MISS does not cancel moving body, independent PO or tail clocks");
                else {
                    check(result.ok&&count==1&&current.player.hp<hp&&!f.runtime().attacking()&&current.player.mp==mp&&f.runtime().cooldownSnapshot(current.nowMs())==cooldown,
                        "Actual incoming source nonmiss publishes damage and prepared body/recoil cancellation without refund or cooldown reset");
                    check(mode=="lethal"?current.player.dead&&treeState(current).empty()&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==0&&current.experimentalAdapter_->neutralReactionReady():
                        !current.player.dead&&treeState(current)==beforeTree&&f.runtime().snapshotDiagnostics().at("source_nut_entities")==1,
                        mode=="lethal"?"Actual lethal ACT clears source runtime, flight/tails and ledger in same accepted commit":"Actual ordinary ACT preserves independent moving source tree and ledger while body enters own damage pose");
                }
                sample={{"mode",mode},{"after_body",afterBody},{"clock",ani_clock::policyName(clock)},{"host",{{"ok",result.ok},{"error",result.error},{"diagnostics",result.diagnostics}}},{"last_damage",current.lastDamageTrace_}};
            });
            w.advanceSingleTick();w.setObjectTick({});check(attempted,"Actual incoming consumer was invoked at fixed boundary");evidence.push_back({{"phase","actual_incoming_act"},{"sample",sample}});
        }
        const auto schedule=[&](int fps,bool catchup) {
            WaterFixture f(pvf,assets,regions,clock);f.configure();auto &w=f.world;w.randomStreams()=RandomStreams(67);
            f.target(1,900,345,70);f.target(2,950,345,70);w.enqueue({0,20,true});w.enqueue({16666667,20,false});Json frames=Json::array();
            w.setObjectTick([&](World &current){Json targets=Json::array();for(const auto &a:current.monsters)targets.push_back({{"hp",a.hp},{"xyz",{a.x,a.y,a.z}},
                {"v",{a.vx,a.vy,a.vz}},{"animation",a.animationPath},{"life",int(a.life)}});
                frames.push_back({{"tick",current.tick},{"mp",current.player.mp},{"player",{current.player.x,current.player.y,current.player.z}},
                    {"runtime",f.runtime().snapshotDiagnostics()},{"tree",treeState(current)},{"targets",targets},{"random",current.randomStreams().snapshot()},
                    {"ids",current.idSources().snapshot()},{"events",current.eventLog()}});});
            constexpr int64_t total=2500000000;int64_t previous=0;
            if(catchup){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}else for(int pump=1;pump<=fps*5/2;++pump){const auto now=total*pump/(fps*5/2);w.advance(now-previous);previous=now;}
            check(w.tick==150&&!w.pendingTicks(),"Water fixed simulation preserves all 150 ticks under render pumping/catch-up");return frames;
        };
        const auto reference=schedule(60,false);check(schedule(30,false)==reference&&schedule(144,false)==reference&&schedule(4,true)==reference,
            "Every source tick/contact/scale/position/reaction/MP/CD/RNG/ID/event matches at 30/60/144Hz and budget8 catch-up");
    }
    {
        // No-clock mode must advance only the reviewed tree, retaining the
        // caller-selected legacy behavior of unrelated effects in the scene.
        WaterFixture f(pvf,assets,regions,ani_clock::ClockPolicy::SourceDelay100);f.world.animationClockPolicy_.reset();f.runtime().setAnimationClockPolicy(std::nullopt);f.configure();f.start();
        check(f.reachFlight(),"Legacy-clock coexistence fixture reaches controlled source water clock");auto &w=f.world;
        Effect legacy;legacy.id=1800000000;legacy.animation="character/swordman/effect/animation/hardattack1.ani";legacy.born=w.nowMs();legacy.expires=w.nowMs()+2000;
        legacy.damageEnabled=false;legacy.alsParentId=1800000001;legacy.x=legacy.px=500;legacy.y=legacy.py=300;w.effects.push_back(legacy);
        const auto events=w.events.size();w.advanceSingleTick();const auto old=std::find_if(w.effects.begin(),w.effects.end(),[&](const auto &e){return e.id==legacy.id;});
        check(old!=w.effects.end()&&!old->clockBound&&!old->playback.installed()&&old->expires==legacy.expires&&
            std::none_of(w.events.begin()+std::ptrdiff_t(events),w.events.end(),[&](const Event &e){return e.kind=="als_event"&&e.source==legacy.id;}),
            "Water tree does not install clocks, dispatch ALS or recursively retire unrelated legacy effects");
        w.effects.erase(std::remove_if(w.effects.begin(),w.effects.end(),[&](const auto &e){return e.id==legacy.id;}),w.effects.end());
    }
    // Real pixels distinguish the source 0.85 inner ANI scale from the outer
    // level multiplier. The pivot is kept in place; world offsets are not
    // scaled. No visible window is created by this regression.
    {
        const auto *driver=SDL_getenv("SDL_VIDEODRIVER");if(!driver||std::string(driver)!="dummy")throw std::runtime_error("Water pixel regression requires SDL_VIDEODRIVER=dummy");
        const bool owns=!(SDL_WasInit(SDL_INIT_VIDEO)&SDL_INIT_VIDEO);if(owns&&SDL_InitSubSystem(SDL_INIT_VIDEO))throw std::runtime_error(SDL_GetError());
        {
            RendererOptions options;options.shown=false;options.vsync=false;Renderer renderer(assets,options);renderer.setRenderProfile(ani_render::RenderProfile::Inferred60Us1031);
            Effect fx;fx.animation="passiveobject/character/mage/animation/atwatercannon/water_normal.ani";fx.born=0;fx.expires=850;fx.x=fx.px=400;fx.y=fx.py=300;fx.z=70;fx.pz=70;
            const auto pixels=[&](){Bytes bytes(800*600*4);if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,bytes.data(),800*4))throw std::runtime_error(SDL_GetError());return bytes;};
            renderer.begin();const auto blank=pixels();renderer.effect(fx,0,1,0,0);const auto base=pixels();
            fx.imageScale=1.25;renderer.begin();renderer.effect(fx,0,1,0,0);const auto scaled=pixels();
            const auto bounds=[&](const Bytes &b){std::array<int,4> r{800,600,-1,-1};for(int y=0;y<600;++y)for(int x=0;x<800;++x){const auto off=size_t(y*800+x)*4;
                if(!std::equal(b.begin()+off,b.begin()+off+4,blank.begin()+off)){r[0]=std::min(r[0],x);r[1]=std::min(r[1],y);r[2]=std::max(r[2],x);r[3]=std::max(r[3],y);}}return r;};
            const auto b=bounds(base),s=bounds(scaled);check(base!=blank&&scaled!=base&&renderer.errors.empty()&&s[2]-s[0]>b[2]-b[0]&&
                std::abs((s[2]-s[0]+1)-1.25*(b[2]-b[0]+1))<=3&&std::abs((s[3]-s[1]+1)-1.25*(b[3]-b[1]+1))<=3,
                "Actual hidden Renderer::effect pixels enlarge source ANI by outer1.25 while preserving inner rate/flip/crop consumer");
            evidence.push_back({{"phase","hidden_pixels"},{"base_bounds",b},{"scaled_bounds",s},{"outer_scale",fx.imageScale},
                {"original_ani_scale",assets.animation(fx.animation)->samplePose(0,true).scaleX}});
        }
        if(owns)SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    return {{"passed",true},{"checks",checks},{"check_count",checks.size()},{"evidence",evidence},
        {"scope","Reviewed current1031 WaterCannon moving-impact preview consumers; base normal admission/TP/elemental-chain remain separate"},
        {"native_dynamic_comparison","pending_user"},{"whole_job_complete",false}};
}
} // namespace dnf
