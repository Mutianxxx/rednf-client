#include "dnf/source_skill_action.hpp"
#include "dnf/character_controller.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/character_attack.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <climits>
#include <stdexcept>

namespace dnf {
namespace {
struct Token {std::string value;bool quoted=false;size_t begin=0,end=0;};
std::vector<Token> lex(const Bytes &bytes) {
    std::vector<Token> out;
    for(size_t i=0;i<bytes.size();) {
        const auto c=bytes[i];
        if(std::isspace(static_cast<unsigned char>(c))){++i;continue;}
        if(c=='/'&&i+1<bytes.size()&&bytes[i+1]=='/') {while(i<bytes.size()&&bytes[i]!='\n')++i;continue;}
        if(c=='/'&&i+1<bytes.size()&&bytes[i+1]=='*') {
            i+=2;while(i+1<bytes.size()&&!(bytes[i]=='*'&&bytes[i+1]=='/'))++i;
            if(i+1>=bytes.size())throw std::invalid_argument("Unclosed source action comment");i+=2;continue;
        }
        Token token;token.begin=i;
        if(c=='"'||c=='\'') {
            token.quoted=true;const auto quote=c;++i;
            while(i<bytes.size()&&bytes[i]!=quote) {
                if(bytes[i]=='\\')throw std::invalid_argument("Unadmitted source action string escape");
                token.value.push_back(char(bytes[i++]));
            }
            if(i==bytes.size())throw std::invalid_argument("Unclosed source action string");++i;
        } else if(std::isalnum(static_cast<unsigned char>(c))||c=='_') {
            while(i<bytes.size()&&(std::isalnum(static_cast<unsigned char>(bytes[i]))||bytes[i]=='_'))token.value.push_back(char(bytes[i++]));
        } else if(i+1<bytes.size()&&((c=='<'&&bytes[i+1]=='-')||(c=='='&&bytes[i+1]=='='))) {
            token.value=std::string(1,char(c))+char(bytes[i+1]);i+=2;
        } else token.value.push_back(char(bytes[i++]));
        token.end=i;out.push_back(std::move(token));
    }
    return out;
}
using Args=std::vector<std::vector<Token>>;
std::vector<Args> calls(const std::vector<Token> &tokens,const std::string &name) {
    std::vector<Args> out;
    for(size_t i=0;i+1<tokens.size();++i)if(!tokens[i].quoted&&tokens[i].value==name&&tokens[i+1].value=="(") {
        Args args(1);int depth=1;size_t end=i+2;
        for(;end<tokens.size();++end) {
            const auto &t=tokens[end];if(!t.quoted&&t.value=="(")++depth;
            if(!t.quoted&&t.value==")"&&!--depth)break;
            if(!t.quoted&&t.value==","&&depth==1)args.emplace_back();else args.back().push_back(t);
        }
        if(end==tokens.size())throw std::invalid_argument("Unclosed source action call");
        if(args.size()==1&&args.front().empty())args.clear();out.push_back(std::move(args));
    }
    return out;
}
Args oneCall(const std::vector<Token> &tokens,const std::string &name,size_t arity) {
    auto found=calls(tokens,name);
    if(found.size()!=1||found.front().size()!=arity)throw std::invalid_argument("Ambiguous/unsupported source action API: "+name);
    return found.front();
}
std::string operand(const std::vector<Token> &tokens) {
    std::string out;for(const auto &token:tokens)out+=token.value;return out;
}
int integer(const std::vector<Token> &tokens) {
    const auto text=operand(tokens);size_t end=0;const auto value=std::stoll(text,&end);
    if(end!=text.size()||value<INT32_MIN||value>INT32_MAX)throw std::invalid_argument("Invalid source action int32 operand");return int(value);
}
int constant(const std::vector<Token> &tokens,const std::string &name) {
    std::optional<int> result;
    for(size_t i=0;i+2<tokens.size();++i)if(!tokens[i].quoted&&tokens[i].value==name&&tokens[i+1].value=="<-") {
        if(result)throw std::invalid_argument("Repeated source action constant: "+name);
        size_t end=i+3;if(tokens[i+2].value=="-")++end;
        if(end>tokens.size())throw std::invalid_argument("Truncated source action constant");
        result=integer({tokens.begin()+i+2,tokens.begin()+end});
    }
    if(!result)throw std::invalid_argument("Missing source action constant: "+name);return *result;
}
std::string pathOperand(const std::vector<Token> &tokens) {
    if(tokens.size()!=1||!tokens.front().quoted)throw std::invalid_argument("Source action needs an exact quoted path");
    return normalize(tokens.front().value);
}
SourceRef nutRef(Pvf &pvf,const std::string &path) {
    auto out=makeSourceRef(pvf,path);out.textEncoding="ASCII executable tokens; original comments retained, CP949 candidate unconfirmed";return out;
}
std::string relative(const std::string &parent,const std::string &child) {
    return normalize((std::filesystem::u8path(parent).parent_path()/std::filesystem::u8path(child)).generic_u8string());
}
std::string uniqueString(const Script &script,const std::string &tag) {
    size_t count=0;std::string result;
    for(const auto &field:script.fields)if(normalize(field.tag)==tag) {
        if(++count>1||field.values.size()!=1||!field.values[0].is_string())throw std::invalid_argument("Source action OBJ field ambiguous: "+tag);
        result=field.values[0].get<std::string>();
    }
    if(count!=1)throw std::invalid_argument("Source action OBJ field missing: "+tag);return result;
}
}
Json SourceNativeStage::snapshot() const {
    Json out={{"motion_tag",motionTag},{"motion_slot",motionSlot},{"motion",motion.json()},
        {"attack_tag",attackTag},{"attack_slot",attackSlot},{"attack",attack.json()},
        {"controller_substate",controllerSubstate},{"controller_style",controllerStyle},
        {"percent_column",percentColumn},{"independent_column",independentColumn},
        {"repeat",repeat},{"repeat_column",repeatColumn},{"repeat_static",repeatStatic},
        {"runtime_delays_ms",runtimeDelays},{"sound",sound},{"suppress_body_damage",suppressBodyDamage},
        {"layers",Json::array()},{"contact_effects",Json::array()},
        {"movement",{{"start_ms",movementStartMs},{"speed_static",speedStatic},{"acceleration_static",accelerationStatic},{"speed",speed},{"acceleration",acceleration}}}};
    for(const auto &layer:layers)out["layers"].push_back(layer.snapshot());
    for(const auto &effect:contactEffects)out["contact_effects"].push_back(effect.snapshot());
    return out;
}
Json SourceSkillAction::snapshot() const {
    Json out={{"key",key.json()},{"state",state},{"source_flag",flag},{"motion_slot",motionSlot},{"object_id",objectId},
        {"spawn_offset",offset},{"executable_states",executableStates},
        {"host_state_mapping",{{"stand",standState},{"dash",dashState},{"attack",attackState},{"jump",jumpState}}},
        {"columns",{{"percent",percentColumn},{"fixed",fixedColumn},{"lift",liftColumn}}},
        {"registration",registration.json()},{"header",header.json()},{"callback",callback.json()},
        {"passive_callback",passiveCallback.json()},{"skill",skill.json()},{"motion",motion.json()},
        {"object_registry",objectRegistry.json()},{"object",object.json()},{"animation",animation.json()},
        {"attack",attack.json()},{"evidence",evidence},{"full_skill_complete",false},{"native_host_parity",false}};
    if(movingImpact) {out["moving_impact"]=movingImpact->snapshot();out["kind"]="moving_impact_object";out["cast_sound"]=castSound;
        out["layers_source"]=layersSource.json();out["body_layers"]=Json::array();
        for(const auto &layer:bodyLayers)out["body_layers"].push_back(layer.snapshot());}
    if(kind==SourceSkillActionKind::BodyAttack) {
        out["kind"]="body_attack";out["attack_slot"]=attackSlot;out["cast_sound"]=castSound;
        if(!attackSound.empty())out["first_body_attack_sound"]=attackSound;
        out["shake"]={{"flag",flag},{"amplitude",shakeAmplitude},{"duration_ms",shakeDurationMs}};
        out["layers_source"]=layersSource.json();out["body_layers"]=Json::array();
        for(const auto &layer:bodyLayers)out["body_layers"].push_back(layer.snapshot());
    }
    if(inferredNativeBody) {
        out["execution_model"]="inferred_native_body";
        out["native_body_columns"]={{"independent_percent",independentColumn},{"speed_percent",speedColumn},{"recovery_static",recoveryColumn}};
        out["recovery_ms"]=recoveryMs;
        if(speedToPermille!=10)out["source_speed_to_permille"]=speedToPermille;
        if(actorAttackSpeedOnly)out["attack_speed_policy"]="inferred-actor-attack-speed-only-v1";
        if(bodyLayerBirthFrame>=0)out["body_layer_birth"]={{"equipped_attack_frame",bodyLayerBirthFrame},
            {"clock","source-delay-rate100"},{"lifetime","own source ANI or action exit"}};
        if(requiresEquippedAttackVolume)out["requires_equipped_attack_volume"]=true;
        if(sourceFrameSuperArmor)out["source_frame_super_armor"]=true;
        if(bodySidestep)out["body_sidestep"]=bodySidestep->snapshot();
    }
    if(native40Jp) {
        out["execution_model"]="40jp-native-family-current1031-source-stages-v1";
        out["native_family"]=nativeFamily;out["native_stages"]=Json::array();
        for(const auto &stage:nativeStages)out["native_stages"].push_back(stage.snapshot());
        if(nativeGrab)out["native_grab"]={{"try_stage",nativeGrab->tryStage},{"release_stage",nativeGrab->releaseStage},
            {"hold_offset",nativeGrab->holdOffset},{"direct_hit_frame",nativeGrab->directHitFrame}};
        if(nativeProjectile)out["native_projectile"]={{"birth_frame",nativeProjectile->birthFrame},{"speed_column",nativeProjectile->speedColumn},
            {"range_static",nativeProjectile->rangeStatic},{"speed",nativeProjectile->speed},{"range",nativeProjectile->range},{"loop",nativeProjectile->loop}};
    }
    return out;
}
namespace {
// Central character registration: no skill owns a copied action executor.
// Names identify current CHR resources, never 40JP addresses or 1031 NUT slots
// (the current NUT enum contains later/different CHR slot layouts).
void appendFighterNative40(Pvf &pvf,Assets &assets,const CharacterCatalog &catalog,CharacterIdentity identity,
    std::map<SkillKey,SourceSkillAction> &out,Json &diagnostics) {
    const auto bindings=orderedCharacterBindings(catalog.at(identity.jobId));
    const auto enums=lex(pvf.read("sqr/dnf_enum_header.nut"));
    const auto binding=[&](const std::string &name,bool attack)->CharacterResource {
        std::optional<CharacterResource> result;
        const auto expected="character/fighter/"+std::string(attack?"attackinfo/":"animation/")+normalize(name)+(attack?".atk":".ani");
        for(const auto &row:bindings)if(row.occurrence==0&&normalize(row.resource.path)==expected) {
            const auto tag=normalize(row.resource.tag);
            if(attack?tag=="[etc attack info]":(tag=="[etc motion]"||tag=="[buff motion]")) {
                if(result)throw std::invalid_argument("Ambiguous Fighter CHR binding: "+expected);result=row.resource;
            }
        }
        if(!result)throw std::invalid_argument("Missing Fighter CHR binding: "+expected);return *result;
    };
    struct Step {const char *motion;const char *attack;int percent=-1,independent=-1;int repeat=1,repeatColumn=-1,repeatStatic=-1;};
    const auto add=[&](const char *skillName,const char *family,std::initializer_list<Step> stages,
        const char *sound,bool jp,int grabRelease=-1,int objectId=-1,int projectileBirth=0,int speedColumn=-1,int rangeStatic=-1) {
        try {
            SourceSkillAction a;a.native40Jp=true;a.inferredNativeBody=true;a.kind=SourceSkillActionKind::BodyAttack;
            a.nativeFamily=family;a.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
            const auto path="skill/fighter/"+std::string(skillName)+".skl";size_t count=0;
            for(const auto &r:catalog.at(identity.jobId).skills.entries)if(normalize(r.path)==path) {a.key={identity.jobId,r.id};++count;}
            if(count!=1)throw std::invalid_argument("Missing/ambiguous Fighter skill registration: "+path);
            const auto &def=catalog.skillDefinition(a.key);
            if(def.kind!=SkillSourceKind::Active)return;
            a.skill=makeSourceRef(pvf,path);a.castSound=sound;
            // Host states are current runtime enums; 40JP state numbers remain
            // evidence only and cannot be transplanted as content identities.
            a.standState=0;a.dashState=2;a.attackState=8;a.jumpState=6;
            a.standState=constant(enums,"STATE_STAND");a.dashState=constant(enums,"STATE_DASH");
            a.attackState=constant(enums,"STATE_ATTACK");a.jumpState=constant(enums,"STATE_JUMP");
            a.executableStates={a.standState,a.dashState};a.actorAttackSpeedOnly=true;
            if(std::string(skillName)=="stomp")a.executableStates={a.jumpState};
            for(const auto &s:stages) {
                SourceNativeStage stage;const auto b=binding(s.motion,false);
                stage.motionTag=b.tag;stage.motionSlot=int(b.valueIndex);stage.motion=makeSourceRef(pvf,b.path);
                stage.percentColumn=s.percent;stage.independentColumn=s.independent;
                stage.repeat=s.repeat;stage.repeatColumn=s.repeatColumn;stage.repeatStatic=s.repeatStatic;
                stage.suppressBodyDamage=!s.attack||!*s.attack;
                if(!stage.suppressBodyDamage) {
                    const auto atk=binding(s.attack,true);stage.attackTag=atk.tag;stage.attackSlot=int(atk.valueIndex);stage.attack=makeSourceRef(pvf,atk.path);
                }
                const auto clip=assets.animation(stage.motion.memberPath);
                if(clip->frames.empty()||clip->duration<=0)throw std::invalid_argument("Empty Fighter stage "+b.path);
                // These are native held-pose controller stages, not seconds
                // conversion. Preserve raw delays and use adjacent source
                // finite timing for the trial controller's release boundary.
                bool held=false;for(const auto &f:clip->frames)held|=f.duration>=8000;
                if(held) {
                    for(size_t i=0;i<clip->frames.size();++i) {
                        int delay=clip->frames[i].duration;
                        if(delay>=8000) {
                            delay=100;
                            for(size_t d=1;d<clip->frames.size();++d) {
                                if(i>=d&&clip->frames[i-d].duration>0&&clip->frames[i-d].duration<1000){delay=clip->frames[i-d].duration;break;}
                                if(i+d<clip->frames.size()&&clip->frames[i+d].duration>0&&clip->frames[i+d].duration<1000){delay=clip->frames[i+d].duration;break;}
                            }
                        }
                        stage.runtimeDelays.push_back(delay);
                    }
                }
                a.nativeStages.push_back(std::move(stage));
            }
            if(a.nativeStages.empty())throw std::invalid_argument("Empty Fighter native stages");
            const auto &first=a.nativeStages.front();a.motion=first.motion;a.motionSlot=first.motionSlot;
            a.attack=first.attack;a.attackSlot=first.attackSlot;a.animation=a.motion;
            a.percentColumn=first.percentColumn;a.independentColumn=first.independentColumn;
            if(a.attackSlot>=0)a.attackDefinition=readAttackDamage(pvf.script(a.attack.memberPath));
            if(grabRelease>=0) {a.nativeGrab=SourceNativeGrab{};a.nativeGrab->releaseStage=size_t(grabRelease);a.nativeGrab->holdOffset={35,0,20};}
            const auto move=[&](size_t index,int start,int speedStatic,int accelStatic,double speed=0,double acceleration=0) {
                auto &stage=a.nativeStages.at(index);stage.movementStartMs=start;stage.speedStatic=speedStatic;
                stage.accelerationStatic=accelStatic;stage.speed=speed;stage.acceleration=acceleration;
            };
            if(std::string(skillName)=="liftupper") {move(0,200,-1,-1,800,-4000);a.attackSound="FT_UPPER_SWING";a.sourceFrameSuperArmor=true;
                a.state=constant(enums,"STATE_LIFT_UPPER");a.liftColumn=2;a.speedColumn=0;a.actorAttackSpeedOnly=false;}
            else if(std::string(skillName)=="singlekick")move(0,0,0,1);
            else if(std::string(skillName)=="shouldercharge")move(0,0,2,3);
            else if(std::string(skillName)=="shouldertackle")move(0,0,2,4);
            else if(std::string(skillName)=="dashpunch"||std::string(skillName)=="dashpunchex")move(0,0,0,1);
            else if(std::string(skillName)=="dashafterdash") {move(0,0,0,1);move(1,0,2,3);move(2,0,4,5);}
            if(std::string(skillName)=="suplex")a.nativeGrab->directHitFrame=4;
            // Native attach calls use screen-local XY. Keep world depth zero,
            // project negative draw Y through positive local Z.
            const auto attach=[&](size_t index,const char *name,std::array<double,3> offset,bool native)->SourceSkillVisualCue * {
                const auto path="character/fighter/effect/animation/"+normalize(name)+".ani";
                if(!pvf.has(path)) {diagnostics.push_back({{"code","fighter40jp_effect_member_absent"},{"skill",skillName},{"path",path}});return nullptr;}
                try {
                    const auto clip=assets.animation(path);if(clip->frames.empty()||clip->duration<=0)return nullptr;
                    SourceSkillVisualCue layer;layer.source=makeSourceRef(pvf,path);layer.bodyPath=a.nativeStages[index].motion.memberPath;
                    layer.offset=offset;layer.layer=1;layer.loop=clip->globals.value("0",false);layer.inheritBodyRate=true;
                    layer.evidence.push_back({{"classification",native?"40jp-native-attachment-current1031-resource":"current1031-own-name-visual-inference"},
                        {"local_xyz",offset},{"native_2d_projection","drawX=actorX+dir*X; drawY=actorY+Y-Z"},
                        {"attachment_lifetime","own ANI clock bounded by source stage exit; native detach parity pending"}});
                    a.nativeStages[index].layers.push_back(std::move(layer));
                    return &a.nativeStages[index].layers.back();
                }catch(const std::exception &e){diagnostics.push_back({{"code","fighter40jp_effect_decode_unavailable"},{"path",path},{"message",e.what()}});return nullptr;}
            };
            if(std::string(skillName)=="closepunch")attach(0,"ClosePunchExecute",{33,0,49},true);
            else if(std::string(skillName)=="sajahu") {attach(0,"RoarStun1",{0,0,65},true);attach(0,"RoarStun2",{0,0,65},true);}
            else if(std::string(skillName)=="energyball") {
                auto &stage=a.nativeStages.at(0);stage.controllerSubstate=12;stage.controllerStyle=1;
                auto *charge=attach(0,"EnergyCharge",{},true);
                if(charge) {
                    charge->controllerSubstates={12,16};
                    charge->evidence.push_back({{"condition_source","40jp-reverse-source/src/combat/bigfunc_5EA970_sub_5EA970.cpp:1229"},
                        {"condition","controller substate 12 or 16"},{"current1031_mapping","test adapter routes EnergyBall to substate 12; 16 remains represented but unresolved"}});
                }
                if(auto *shoot=attach(0,"EnergyBallShoot",{},true)) {
                    shoot->controllerSubstates={12};shoot->controllerStyle=1;
                    shoot->evidence.push_back({{"condition_source","40jp-reverse-source/src/combat/bigfunc_5EA970_sub_5EA970.cpp:1229-1276"},
                        {"condition","substate 12 and style 1"},{"current1031_mapping","test adapter selects the 40JP shot route; current PVF does not expose this native selector"}});
                }
            }
            else if(std::string(skillName)=="liftupper") {
                attach(0,"Upper",{},false);
                diagnostics.push_back({{"code","fighter40jp_effect_binding_inferred"},{"skill",skillName},
                    {"path","character/fighter/effect/animation/upper.ani"},
                    {"basis","reviewed current1031 female Upper visual association; no 40JP Upper ANI caller recovered"}});
            }
            else if(std::string(skillName)=="shouldertackle") {
                attach(0,"ShoulderTackle",{},true);
                const auto hitPath="character/fighter/effect/animation/shouldertacklehit.ani";
                if(pvf.has(hitPath))try {
                    const auto clip=assets.animation(hitPath);
                    if(clip->frames.empty()||clip->duration<=0)throw std::invalid_argument("Empty ShoulderTackleHit ANI");
                    SourceSkillVisualCue cue;cue.source=makeSourceRef(pvf,hitPath);cue.bodyPath=a.nativeStages[0].motion.memberPath;
                    cue.trigger=SourceSkillVisualTrigger::AcceptedHit;cue.layer=1;cue.loop=false;
                    cue.evidence.push_back({{"classification","40jp-native-hit-effect-callsite-current1031-resource"},
                        {"source","40jp-reverse-source/src/combat/fighter_skills.cpp:2920-2947"},
                        {"position","center of accepted overlap volume in world XYZ"},
                        {"lifetime","source ANI duration; scene-owned transient"}});
                    a.nativeStages[0].contactEffects.push_back(std::move(cue));
                } catch(const std::exception &e) {
                    diagnostics.push_back({{"code","fighter40jp_effect_decode_unavailable"},{"skill",skillName},{"path",hitPath},{"message",e.what()}});
                }
                else diagnostics.push_back({{"code","fighter40jp_conditional_effect_member_absent"},
                    {"skill",skillName},{"path",hitPath},{"source","40jp-reverse-source/src/combat/fighter_skills.cpp:2920"}});
            }
            else if(std::string(skillName)=="spire") {
                for(const auto *name:{"JumpSuplexRollUnder","JumpSuplexRollOver"})if(auto *cue=attach(1,name,{},true)) {
                    cue->scalePolicy=SourceSkillVisualScalePolicy::HeldTargetWidth;
                    cue->evidence.push_back({{"scale_source","40jp-reverse-source/src/combat/bigfunc_5EA970_sub_5EA970.cpp:1645-1682"},
                        {"source_curve","linear scale 1..3 over target size 100..250"},
                        {"current1031_size_input","MOB [width] used as an explicitly inferred proxy for held-object size"}});
                }
            }
            else {
                Json motions=Json::array();for(const auto &stage:a.nativeStages)motions.push_back(stage.motion.memberPath);
                diagnostics.push_back({{"code","fighter40jp_effect_binding_unrecovered"},{"skill",skillName},
                    {"stage_motion_members",std::move(motions)},
                    {"reason","No exact 40JP effect ANI callsite is registered for this action family"},
                    {"fallback","same-stem/current-name effects are not attached"}});
            }
            // Retain the first-stage source layer view for older diagnostics;
            // the native executor presents only its active stage's layers.
            a.bodyLayers=a.nativeStages.front().layers;
            if(objectId>=0) {
                a.objectId=objectId;a.objectRegistry=makeSourceRef(pvf,"passiveobject/passiveobject.lst");
                const auto registry=pvf.script(a.objectRegistry.memberPath);size_t found=0;
                for(size_t i=0;i+1<registry.tokens.size();i+=2)if(registry.tokens[i].at("value")==objectId) {
                    a.object=makeSourceRef(pvf,relative(a.objectRegistry.memberPath,registry.tokens[i+1].at("value").get<std::string>()));++found;
                }
                if(found!=1)throw std::invalid_argument("Fighter native PO registry differs");
                const auto obj=pvf.script(a.object.memberPath);
                a.animation=makeSourceRef(pvf,relative(obj.path,uniqueString(obj,"[basic motion]")));
                a.attack=makeSourceRef(pvf,relative(obj.path,uniqueString(obj,"[attack info]")));
                a.objectAnimation=assets.animation(a.animation.memberPath);a.attackDefinition=readAttackDamage(pvf.script(a.attack.memberPath));
                a.nativeProjectile=SourceNativeProjectile{projectileBirth,speedColumn,rangeStatic,0,0,a.objectAnimation->globals.value("0",false)};
                a.nativeProjectile->birthFrame=std::min<int>(projectileBirth,int(assets.animation(a.motion.memberPath)->frames.size()-1));
                // 40JP cast/tick supplies a nonzero muzzle height; never actor feet.
                a.offset={60,0,70};
                if(objectId==21005||objectId==21007||objectId==21010)a.offset={0,0,0};
                if(objectId==21006)a.offset={107,1,62};
            }
            a.evidence={{"policy","40jp-fighter-shared-native-stages-v1"},{"classification",jp?"40jp-native-structure-with-current1031-resources":"current1031-same-family-inference"},
                {"behavior_source","40jp-reverse-source/src/combat/bigfunc_5EA970_sub_5EA970.cpp; fighter_skills.cpp sub_5E6EE0; bigfunc_5E78C0_sub_5E78C0.cpp"},
                {"resource_identity",a.skill.json()},{"source_binding","exact own CHR path/ordered binding; no cross-version numeric slots"},
                {"effect_binding_policy","only exact 40JP ANI callsites are attached; same-stem inference and missing conditional effects remain diagnostics"},
                {"stage_execution","one shared executor, source frame visits, independent stage ledgers, one MP/CD, conditional accepted-hit grabs"},
                {"held_frame_policy","explicit debug preview only: nearest finite source frame delay; normal mode retains raw held frames; raw ANI unchanged"},
                {"unverified",{"1031 native per-skill caller parity","all buff/passive consumers","PO native custom data beyond listed operands","hold duration and follow-up input windows","final original-client visual/feel comparison"}}};
            // A 40JP behavioral result supersedes the old guessed recovery.
            // LowKick's static1000 is not an additional idle wait in the native
            // action-completion branch; keep the original SKL as evidence.
            out[a.key]=std::move(a);
        }catch(const std::exception &error) {diagnostics.push_back({{"code","fighter40jp_source_family_unavailable"},{"skill",skillName},{"message",error.what()}});}
    };
    add("crouch","crouch",{{"crouch",""}},"FT_SIT",true);
    add("crashlowkick","leg_kick",{{"crashlowkick","crashlowkick",1,6}},"G_BONECRUSHER",true);
    add("liftupper","upper",{{"liftupper","liftupper",1,3}},"FT_UPPER_READY",true);
    add("damagelowkick","leg_kick",{{"damagelowkick","damagelowkick",1,2}},"G_LOWKICK",true);
    add("suplex","accepted_hit_grab",{{"trysuplex","trygrab"},{"suplex","suplex",2,0}},"FT_SUPLEX",true,1);
    add("spire","accepted_hit_grab",{{"tryjumpsuplex","trygrab"},{"jumpsuplex","jumpsuplex",-1,0},{"jumpsuplexlariat","jumpsuplexlariat",-1,1}},"FT_SPIRE",true,2);
    add("throwenemy","accepted_hit_grab",{{"trythrowenemy","trygrab"},{"throwenemyhold",""},{"throwenemythrow","suplex",-1,0}},"FT_ROPLING",true,2);
    add("legsuplex","accepted_hit_grab",{{"trylegsuplex","trygrab"},{"legsuplexthrow",""},{"legsuplexkick","legsuplexkick",-1,0}},"",false,2);
    add("closepunch","close_punch",{{"closepunch","closepunch",0}},"FT_ONEINCH",true);
    add("stomp","air_stomp",{{"stomp","stomp",0,3,1,1}},"FT_SKYSTEP",true);
    add("singlekick","hammer_kick",{{"singlekick","singlekick",2,3}},"FT_HAMMER_KICK",true);
    add("shouldercharge","body_dash",{{"shouldercharge","shouldercharge",0}},"",false);
    add("shouldertackle","charged_dash",{{"shouldertackle","shouldertackle",0,2}},"FT_TK",true);
    add("whirlwindkick","source_repeat",{{"whirlwindkick","whirlwindkick",0,-1,1,1}},"",false);
    add("blockbuster","body_impact",{{"blockbuster","blockbuster",0}},"",false);
    add("hiddensting","body_sting",{{"hiddensting","hiddensting",0}},"",false);
    add("dashpunch","body_dash",{{"dashpunch","dashpunch",0}},"",false);
    add("punchafterreturn","counter_punch",{{"punchafterreturn","punchafterreturn",2}},"",false);
    add("randomkick","repeat_finisher",{{"randomkickready",""},{"randomkickstart","randomkickstart",0,-1,1,-1,0},{"randomkickend","randomkickend",1},{"randomkickendpunch","randomkickend",2}},"",false);
    add("risingupper","dash_upper",{{"risingupperdash","risingupperdash",0},{"risingupper","risingupper",1}},"",false);
    add("dashafterdash","four_stage_combo",{{"dashafterdashcombo1","dashafterdashcombo1",0},{"dashafterdashcombo2","dashafterdashcombo2",1},{"dashafterdashcombo3","dashafterdashcombo3",2},{"dashafterdashcombo4","dashafterdashcombo4",3}},"",false);
    add("earthbreak","body_impact",{{"earthbreak",""}},"",false);
    add("holdup","accepted_hit_grab",{{"holduptry","holduptry"},{"holduphold",""},{"holduphit","holduphit",0}},"",false,2);
    add("suplexcyclone","accepted_hit_grab",{{"trysuplexcyclone","trygrab"},{"suplexcycloneturn","suplexcyclonecrash",0,1,1,-1,2},{"suplexcyclonecrash","suplexcyclonecrash",2,3},{"suplexcyclonefinish","suplexcyclonefinish",4,5}},"",false,3);
    add("strongestlowkick","three_stage_finisher",{{"strongestlowkickstamp",""},{"strongestlowkickready",""},{"strongestlowkick","strongestlowkick",0}},"",false);
    add("mount","accepted_hit_grab",{{"mounttry","trygrab"},{"mount",""},{"mountleft","mount",0,-1,1,-1,0},{"mountright","mount",0},{"mountend","mount",1}},"",false,4);
    add("crazymount","accepted_hit_grab",{{"crazymountstart","trygrab"},{"crazymountleft","crazymount",2,-1,1,-1,0},{"crazymountright","crazymount",2},{"crazymountend","crazymount",2}},"",false,3);
    add("typhoon","accepted_hit_grab",{{"trytyphoon","trygrab"},{"typhoonspin","suplexcyclonecrash",0,1,5},{"typhoonfinish","suplexcyclonefinish",2,3}},"",false,2);
    add("venommine","two_stage_impact",{{"venomminethrow",""},{"venomminepound",""}},"",false);
    add("junkspin","source_repeat",{{"junkspin","",-1,-1,1,-1,0}},"",false);
    add("nenflower","summon_cast",{{"nenflower",""}},"",false);
    add("poisonmist","field_cast",{{"poisonmist",""},{"poisonmistexplosion",""}},"",false);
    add("lightningdragon","channel_cast",{{"lightningdragon",""}},"",false);
    add("grabexplosion","source_held_body",{{"grabexplosion","grabexplosion",0}},"",false);
    add("grabexplosionex","source_held_body",{{"grabexplosionex","grabexplosion",1}},"",false);
    add("dashpunchex","body_dash",{{"dashpunchex","dashpunchex",0}},"",false);
    add("risingupperex","three_stage_upper",{{"risingupperexstart","risingupperexstart",0},{"risingupperex","risingupperex",1,4,1,-1,3},{"risingupperexfinish","risingupperfinishex",0}},"",false);
    add("blockbusterex","three_stage_impact",{{"blockbusterextry",""},{"blockbusterexjump",""},{"blockbusterexfinish","blockbusterfinishex",0,1}},"",false);
    add("suplexcycloneex","two_stage_spin",{{"suplexcycloneexjump","suplexcycloneex",0,1},{"suplexcycloneexspin","suplexcycloneexspin",2,3}},"",false);
    add("legsuplexex","multi_stage_grab",{{"trylegsuplex","trygrab"},{"legsuplexexspin","legsuplexexspin",0,1},{"legsuplexexthrow1",""},{"trylegsuplexexsecond",""},{"legsuplexexthrow2","legsuplexkick",4,6}},"",false,4);
    add("groundkick","two_stage_kick",{{"groundkickcharge",""},{"groundkickkick","groundkick",0}},"",false);
    // Cast families use the actual Fighter buff/cast pose until the source
    // native cast group is reconstructed. They never borrow Upper/basic ANI.
    add("energyball","moving_source_projectile",{{"buff","",1,7}},"FT_NENTAN",true,-1,21002,4,0,0);
    add("throwsand","moving_source_projectile",{{"buff","",2,6}},"FT_HELLTER",true,-1,21004,4,0,1);
    add("sajahu","radial_source_object",{{"buff","",3}},"FT_SAJAHU_CAST",true,-1,21005,4);
    add("kikouken","field_source_object",{{"buff","",0,6}},"FT_ENERGY_SHOT",true,-1,21006,4);
    add("spiralnen","orb_source_object",{{"buff","",0}},"",true,-1,21007,4);
    add("nenguard","guard_source_object",{{"buff",""}},"",false,-1,21010,4);
    add("throwweb","moving_source_projectile",{{"throwweb","",-1,2}},"",false,-1,21015,2);
    for(const auto *name:{"superarmor","attackspeedup","lightenchantweapon","lighttoleranceup","slowdownpowerup","enchantpoison","aimvitalpoint","doublethrow","provocation","definitegrab","jumppowerup","magicalattackup","muscleshift"})
        add(name,"buff_cast",{{"buff",""}},"",true);
    // Known source attack/visual gaps remain visible in coverage rather than
    // granting an unrelated action in the runtime registry.
}
}
std::map<SkillKey,SourceSkillAction> loadSourceSkillActions(Pvf &pvf,Assets &assets,const CharacterCatalog &catalog,CharacterIdentity identity,Json &diagnostics) {
    std::map<SkillKey,SourceSkillAction> out;
    // This dedicated adapter registry is version scoped. It does not infer
    // resource relationships or native semantics from filenames or preload.
    try {
        const auto enums=lex(pvf.read("sqr/dnf_enum_header.nut"));
        if(identity.jobId==constant(enums,"ENUM_CHARACTERJOB_FIGHTER")) {
            // Independent failure boundary: a changed/missing Upper source must
            // not disable the already reviewed female LowKick consumer below.
            try {
                SourceSkillAction upper;upper.kind=SourceSkillActionKind::BodyAttack;upper.inferredNativeBody=true;
                upper.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
                upper.key={identity.jobId,constant(enums,"SKILL_LIFT_UPPER")};
                upper.state=constant(enums,"STATE_LIFT_UPPER");
                upper.standState=constant(enums,"STATE_STAND");upper.dashState=constant(enums,"STATE_DASH");
                upper.attackState=constant(enums,"STATE_ATTACK");upper.jumpState=constant(enums,"STATE_JUMP");
                upper.executableStates={upper.standState,upper.dashState};
                upper.motionSlot=constant(enums,"CUSTOM_ANI_LIFT_UPPER");
                upper.attackSlot=constant(enums,"CUSTOM_ATTACKINFO_LIFT_UPPER");
                const auto &skill=catalog.skillDefinition(upper.key);
                upper.skill=makeSourceRef(pvf,skill.source.script.path);
                if(upper.skill.memberPath!="skill/fighter/liftupper.skl"||
                   upper.skill.memberSha256!="a40014b6ebfa77185903856fdfc7d3a08b7d3bed59e823a7a5e17bfe3caa0c83"||
                   !skill.fieldsInScope("[executable states]","common").empty())
                    throw std::invalid_argument("Unreviewed current1031 female Upper SKL/qualification semantics");
                upper.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(upper.motionSlot)));
                size_t attacks=0;
                for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId)))
                    if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.valueIndex==size_t(upper.attackSlot)&&binding.occurrence==0)
                        {upper.attack=makeSourceRef(pvf,binding.resource.path);++attacks;}
                if(attacks!=1||upper.motion.memberPath!="character/fighter/animation/liftupper.ani"||
                   upper.motion.memberSha256!="aa91dc98611f24133e0bcd7715708bef9edf2287dc4c511663631324b054dd13"||
                   upper.attack.memberPath!="character/fighter/attackinfo/liftupper.atk"||
                   upper.attack.memberSha256!="472b1c3deb7b321f49fd0f8da471b4976910c203d9ceb46c4d2d5766fa03b9db")
                    throw std::invalid_argument("Unreviewed current1031 female Upper own CHR/body/ATK relationship");
                upper.animation=upper.motion;upper.attackDefinition=readAttackDamage(pvf.script(upper.attack.memberPath));
                const auto body=assets.animation(upper.motion.memberPath);bool hasAttack=false;
                for(const auto &frame:body->frames)for(const auto &box:frame.boxes)
                    hasAttack|=box.type==15&&box.w>0&&box.h>0&&box.d>0;
                if(!upper.attackDefinition.usable()||upper.attackDefinition.type!=DamageAttackType::Physical||
                   !upper.attackDefinition.weaponDamageApply||!hasAttack||body->frames.empty()||body->duration<=0||
                   pvf.has(upper.motion.memberPath+".als")||!body->frames.front().properties.contains("13")||
                   body->frames.front().properties.at("13")!=1)
                    throw std::invalid_argument("Female Upper direct body/physical ATK/explicit first-frame protection changed");
                upper.percentColumn=1;upper.speedColumn=0;upper.liftColumn=2;upper.independentColumn=3;
                upper.sourceFrameSuperArmor=true;
                const auto visualSource=makeSourceRef(pvf,"character/fighter/effect/animation/upper.ani");
                const auto visual=assets.animation(visualSource.memberPath);
                if(visualSource.memberSha256!="be4dcaa637a3acd52dfa6c35282b74138864df7f778d51ab422dd477de0a9f88"||
                   visual->frames.empty()||visual->duration<=0)
                    throw std::invalid_argument("Unreviewed female Upper inferred visual association");
                FemaleGunnerSkillLayer layer;layer.source=visualSource;layer.bodyPath=upper.motion.memberPath;layer.layer=1;
                layer.loop=false;layer.synchronizedToBody=false;layer.inheritBodyRate=true;
                layer.evidence.push_back({{"policy","inferred-current1031-fighter-upper-visual-v1"},{"classification","inferred_beta"},
                    {"source_animation",visualSource.json()},{"source_duration_ms",visual->duration},
                    {"birth","action start; own source 250+70ms blank retained"},{"local_xyz",{0,0,0}},
                    {"layer","inferred above actor"},{"native_spawn_and_layer",false},
                    {"basis","Own female upper source, not male atliftupper; exact version association, no NUT/ALS caller proven"}});
                upper.bodyLayers.push_back(std::move(layer));
                upper.castSound="FT_UPPER_READY";upper.attackSound="FT_UPPER_SWING";
                upper.evidence={{"policy","inferred-current1031-fighter-upper-body-v1"},{"classification","inferred_beta"},
                    {"source_chain","own skill enum/registration -> own CHR motion/ATK -> body and all equipped type15 -> SKL four columns -> unified damage and actual monster response"},
                    {"operand_mapping",{{"percent_column",1},{"speed_percent_column",0},{"lift_column",2},{"independent_percent_column",3}}},
                    {"knowledge_basis","Course10897 and current SKL level-property locate four columns; level-property is display, not a recovered native formula"},
                    {"qualification_policy","Inferred ground stand/dash; source initial1 is independent of implementation; no cancellation purchase/grant"},
                    {"speed_policy","Inferred additive source speed percent*10 to effective actor attack permille; SourceDelay100 retains raw ANI timing"},
                    {"lift_policy","Inferred direct active-level force overrides ATK lift0; native mass/ratio formula unknown"},
                    {"protection_policy","inferred-current1031-fighter-upper-explicit-frame-armor-v1"},
                    {"protection_boundary","Only current frame explicit property13==1; source absent-field inheritance remains unknown; HP/death/control consumers stay active"},
                    {"equipment_clock_policy","Existing followClock body-frame composition; raw weapon delays retained, never prolong body740ms to weapon1370ms"},
                    {"audio_policy","inferred-current1031-fighter-upper-two-phase-audio-v1"},
                    {"audio_timing","READY once at accepted cast; SWING once at first visited body type15; both preflighted before cost; native caller unknown"},
                    {"normal_learning_consumer_bound",false},{"tp_163_normal_admitted",false},
                    {"unverified",{"native activation/cancel priority","native protection carry/default","damage/independent formula","native lift/weight formula","effect native caller/layer","voice native caller/phase","TP163 and other modifiers"}}};
                out.emplace(upper.key,std::move(upper));
            } catch(const std::exception &error) {
                diagnostics.push_back({{"code","fighter_upper_source_adapter_blocked"},{"message",error.what()},
                    {"existing_lowkick_preserved",true},{"full_skill_complete",false}});
            }
            SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;action.inferredNativeBody=true;
            // The enum is a current PVF identity/slot reference, not a NUT
            // controller. Numeric content is read; the reviewed mapping is
            // intentionally registered here as inferred source semantics.
            action.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
            action.key={identity.jobId,constant(enums,"SKILL_DAMAGE_LOW_KICK")};
            action.state=constant(enums,"STATE_LOW_KICK");
            action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
            action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
            action.executableStates={action.standState,action.dashState};
            action.motionSlot=constant(enums,"CUSTOM_ANI_DAMAGE_LOW_KICK");
            action.attackSlot=constant(enums,"CUSTOM_ATTACKINFO_DAMAGE_LOW_KICK");
            action.skill=makeSourceRef(pvf,catalog.skillDefinition(action.key).source.script.path);
            if(action.skill.memberPath!="skill/fighter/damagelowkick.skl"||
               action.skill.memberSha256!="9e7be4f1e82e894d9542df6e60812baff2bfdd937039e35eb3f2d101f78eb46e")
                throw std::invalid_argument("Unreviewed current1031 LowKick SKL semantics");
            const auto &skill=catalog.skillDefinition(action.key);
            if(!skill.fieldsInScope("[executable states]","common").empty())
                throw std::invalid_argument("LowKick now authors executable states; review source qualification before using inferred policy");
            action.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(action.motionSlot)));
            size_t attacks=0;
            for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId)))
                if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.valueIndex==size_t(action.attackSlot)&&binding.occurrence==0)
                    {action.attack=makeSourceRef(pvf,binding.resource.path);++attacks;}
            if(attacks!=1||action.motion.memberPath!="character/fighter/animation/damagelowkick.ani"||
               action.attack.memberPath!="character/fighter/attackinfo/damagelowkick.atk")
                throw std::invalid_argument("LowKick enum/own-CHR motion or ATK binding differs");
            action.animation=action.motion;action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
            if(!action.attackDefinition.usable()||action.attackDefinition.type!=DamageAttackType::Physical)
                throw std::invalid_argument("LowKick physical ATK consumer unavailable");
            const auto body=assets.animation(action.motion.memberPath);bool hasAttack=false;
            for(const auto &frame:body->frames)for(const auto &box:frame.boxes)
                hasAttack|=box.type==15&&box.w>0&&box.h>0&&box.d>0;
            if(!hasAttack||body->duration<=0||pvf.has(action.motion.memberPath+".als"))
                throw std::invalid_argument("LowKick reviewed direct body ANI contract changed");
            action.percentColumn=1;action.independentColumn=2;action.speedColumn=0;action.recoveryColumn=0;
            const auto recovery=skill.values("[static data]","dungeon");
            if(recovery.size()!=1||!recovery[0].is_number_integer()||recovery[0].get<int64_t>()<0||recovery[0].get<int64_t>()>INT32_MAX)
                throw std::invalid_argument("LowKick dungeon static recovery operand unavailable");
            action.recoveryMs=recovery[0].get<int>();
            action.evidence={{"policy","inferred-current1031-fighter-lowkick-body-v1"},{"classification","inferred_beta"},
                {"execution_model","native-body-reconstruction; no own fighter NUT exists in current PVF"},
                {"source_chain","enum skill/state/motion/ATK constants -> own CHR ordered bindings -> body/equipped type15 -> source ATK and SKL dungeon operands -> unified damage/monster response -> source recovery"},
                {"operand_mapping",{{"percent_column",1},{"independent_percent_column",2},{"speed_percent_column",0},{"recovery_static_column",0}}},
                {"knowledge_basis","Course10898 labels independentAttack*x0.54 and 1000ms post-release stiffness; current SKL level property independently labels columns1/2/0 and contains dungeon static1000"},
                {"qualification_policy","test-overlay-only; inferred ground stand/dash admission because current SKL has no executable states; no native cancel grant"},
                {"speed_policy","Inferred additive skill percent*10 to effective attack permille for selected rate clock; SourceDelay100 comparison retains raw ANI timing"},
                {"recovery_policy","Default after_animation: source static duration after ANI end; since_activation comparison begins duration at accepted cast. Both interpretations inferred, hitstop freezes local duration"},
                {"normal_source_qualification",{{"required_level",5},{"growtypes",{0,1,2,3,4}},{"purchase_maximum",50},{"runtime_normal_learning_bound",false}}},
                {"unverified",{"native activation/cancel priority","static1000 recovery origin","skill speed aggregation formula","all TP/passive modifiers","native independent damage formula","native hit-recovery and down-hit response details"}}};
            out.emplace(action.key,std::move(action));
            appendFighterNative40(pvf,assets,catalog,identity,out,diagnostics);return out;
        }
        if(identity.jobId==constant(enums,"ENUM_CHARACTERJOB_GUNNER")) {
            SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;action.inferredNativeBody=true;
            action.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
            // Current global enum has no own Gunner knee state/slot. Register
            // this exact reviewed relationship, not a later NUT state number.
            size_t skills=0;
            for(const auto &entry:catalog.at(identity.jobId).skills.entries)
                if(entry.path=="skill/gunner/aerialknee.skl"&&entry.exists){action.key={identity.jobId,entry.id};++skills;}
            if(skills!=1)throw std::invalid_argument("Gunner Knee skill registration missing or ambiguous");
            action.skill=makeSourceRef(pvf,catalog.skillDefinition(action.key).source.script.path);
            if(action.skill.memberSha256!="a5dd0ce1416e594fab06aa717dd199f2a118b0fa632f3e20e4580a3ffb0689f2")throw std::invalid_argument("Unreviewed current1031 Gunner Knee SKL semantics");
            const auto &skill=catalog.skillDefinition(action.key);
            if(!skill.fieldsInScope("[executable states]","common").empty())
                throw std::invalid_argument("Gunner Knee now authors executable states; review inferred admission");
            action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
            action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
            action.executableStates={action.standState,action.dashState};
            size_t motions=0,attacks=0;
            for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId))) {
                if(binding.occurrence!=0)continue;
                if(normalize(binding.resource.tag)=="[etc motion]"&&binding.resource.path=="character/gunner/animation/aerialknee.ani")
                    {action.motion=makeSourceRef(pvf,binding.resource.path);action.motionSlot=int(binding.resource.valueIndex);++motions;}
                if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.path=="character/gunner/attackinfo/aerialknee.atk")
                    {action.attack=makeSourceRef(pvf,binding.resource.path);action.attackSlot=int(binding.resource.valueIndex);++attacks;}
            }
            if(motions!=1||attacks!=1||action.motion.memberSha256!="fcece609b6507b35d2411af68ca95da06be30445c7c96d222698c1b8e8f3b22d"||action.attack.memberSha256!="19e4f7321605ebedb39e2e7acde0e40a03594c803d6ff289ec0f73c221492e7b")
                throw std::invalid_argument("Unreviewed current1031 Gunner Knee own CHR/body/ATK relationship");
            action.animation=action.motion;action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
            if(!action.attackDefinition.usable()||action.attackDefinition.type!=DamageAttackType::Physical||!action.attackDefinition.weaponDamageApply)
                throw std::invalid_argument("Gunner Knee physical weapon-applied ATK unavailable");
            const auto body=assets.animation(action.motion.memberPath);bool hasAttack=false;
            for(const auto &frame:body->frames)for(const auto &box:frame.boxes)hasAttack|=box.type==15&&box.w>0&&box.h>0&&box.d>0;
            if(!hasAttack||body->frames.empty()||body->duration<=0||pvf.has(action.motion.memberPath+".als")||
               !body->frames.front().properties.contains("13")||body->frames.front().properties.at("13")!=1)
                throw std::invalid_argument("Gunner Knee reviewed body/first-frame protection contract changed");
            action.percentColumn=0;action.speedColumn=1;action.liftColumn=2;action.independentColumn=3;
            action.sourceFrameSuperArmor=true;
            // Dedicated inferred visual association: no own NUT/ALS spawn is
            // claimed. Source blank250 equals own body windup250; source XYZ,
            // scale/blend and immutable delays remain untouched.
            const auto effectSource=makeSourceRef(pvf,"character/gunner/effect/animation/aerialkneekick.ani");
            const auto effect=assets.animation(effectSource.memberPath);
            if(effectSource.memberSha256!="17d7deb9619492583470cee41f55ddaa1899409fdf0b7a38e396777e7a501bbd"||effect->frames.empty()||effect->duration<=0)
                throw std::invalid_argument("Unreviewed Gunner Knee inferred visual");
            FemaleGunnerSkillLayer layer;layer.source=effectSource;layer.bodyPath=action.motion.memberPath;layer.layer=1;
            layer.loop=false;layer.synchronizedToBody=false;layer.inheritBodyRate=true;
            layer.evidence.push_back({{"policy","inferred-current1031-gunner-knee-visual-v1"},{"classification","inferred_beta"},
                {"basis","Own AerialKneeKick source blank250 matches own AerialKnee body windup250; explicit version-scoped association, not filename auto-dispatch"},
                {"source_animation",effectSource.json()},{"source_duration_ms",effect->duration},
                {"birth","action start; source blank lead retained"},{"local_xyz",{0,0,0}},
                {"layer","inferred above actor"},{"native_spawn_and_layer",false}});
            action.bodyLayers.push_back(std::move(layer));
            action.evidence={{"policy","inferred-current1031-gunner-knee-body-v1"},{"classification","inferred_beta"},
                {"source_chain","job2 own skill registration -> CHR own etc motion/ATK -> body/equipped type15 -> exact MP/CD and SKL operands -> unified damage/real monster response"},
                {"knowledge_basis","Course10618 matches current SKL level-property columns percent0/speed1/lift2/independent3; course10732 is female identity and not a substitute"},
                {"operand_mapping",{{"percent_column",0},{"speed_percent_column",1},{"lift_column",2},{"independent_percent_column",3}}},
                {"lift_policy","Inferred direct active-level SKL force overrides ATK1600 for this action only; UI scales350 to100%, native mass/ratio formula unknown"},
                {"protection_policy","Only explicit own ANI frame type13=1 is inferred super armor from own SKL activation explain; absent property ends armor, HP and death still apply; global enum not claimed"},
                {"qualification_policy","Inferred ground stand/dash; normal source initial level1 is distinct from runtime implementation; no forced/cancel passive grant"},
                {"speed_policy","Inferred additive skill percent*10 to effective attack permille; SourceDelay100 keeps raw source delays"},
                {"normal_learning_consumer_bound",false},
                {"unverified",{"native activation/cancel/force priority","source damage-type enum and carry semantics","TP168/passive growth chains","native lift/weight formula","visual native spawn/layer","independent damage formula","cast voice"}}};
            out.emplace(action.key,std::move(action));return out;
        }
        if(identity.jobId==constant(enums,"ENUM_CHARACTERJOB_MAGE")) {
            // Independent append: changed Upper bytes cannot remove reviewed Thrust.
            appendSourceMageUpperAction(pvf,assets,catalog,identity,out,diagnostics);
            SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;action.inferredNativeBody=true;
            action.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
            // This 1031 enum has no Mage Thrust state/skill/slot constants.
            // Resolve identities from actual skill-list and CHR registrations;
            // state remains unknown, rather than importing a later NUT number.
            size_t skills=0;
            for(const auto &entry:catalog.at(identity.jobId).skills.entries)
                if(entry.path=="skill/mage/thrust.skl"&&entry.exists){action.key={identity.jobId,entry.id};++skills;}
            if(skills!=1)throw std::invalid_argument("Mage Thrust skill source registration missing or ambiguous");
            action.skill=makeSourceRef(pvf,catalog.skillDefinition(action.key).source.script.path);
            if(action.skill.memberSha256!="6bda01f0487266e532565eebfc69514d03a7a77fb98448958b18b72c56dc19bf")
                throw std::invalid_argument("Unreviewed current1031 Mage Thrust SKL semantics");
            const auto &skill=catalog.skillDefinition(action.key);
            if(!skill.fieldsInScope("[executable states]","common").empty())
                throw std::invalid_argument("Mage Thrust now authors executable states; review inferred admission");
            action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
            action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
            action.executableStates={action.standState,action.dashState};
            size_t motions=0,attacks=0;
            for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId))) {
                if(binding.occurrence!=0)continue;
                if(normalize(binding.resource.tag)=="[etc motion]"&&binding.resource.path=="character/mage/animation/thrust.ani")
                    {action.motion=makeSourceRef(pvf,binding.resource.path);action.motionSlot=int(binding.resource.valueIndex);++motions;}
                if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.path=="character/mage/attackinfo/thrust.atk")
                    {action.attack=makeSourceRef(pvf,binding.resource.path);action.attackSlot=int(binding.resource.valueIndex);++attacks;}
            }
            if(motions!=1||attacks!=1)throw std::invalid_argument("Mage Thrust own CHR binding missing or ambiguous");
            if(action.motion.memberSha256!="385cc27e697f7be2eedbd69456dee359bf122d5caad1e7ff33b45b6216627398"||
               action.attack.memberSha256!="ec414fc1b5605cc2ee527b7cf1b36e0b5926fc3e30389353945b2b52cf2f996a")
                throw std::invalid_argument("Unreviewed current1031 Mage Thrust body/ATK semantics");
            action.animation=action.motion;action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
            if(!action.attackDefinition.usable()||action.attackDefinition.type!=DamageAttackType::Physical||!action.attackDefinition.weaponDamageApply)
                throw std::invalid_argument("Mage Thrust physical equipped-weapon ATK unavailable");
            const auto body=assets.animation(action.motion.memberPath);
            if(body->duration<=0||body->frames.empty()||pvf.has(action.motion.memberPath+".als"))
                throw std::invalid_argument("Mage Thrust reviewed body timeline contract changed");
            bool equippedVolume=false;
            const auto defaults=defaultCharacterAppearance(pvf,catalog,identity);
            const auto composed=readCharacterAttackMotion(assets,defaults,action.motion.memberPath);
            for(size_t frame=0;frame<body->frames.size();++frame)
                for(const auto &box:composed.boxesAt(frame))equippedVolume|=box.w>0&&box.h>0&&box.d>0;
            if(!equippedVolume)throw std::invalid_argument("Mage Thrust source default EQU/LAY has no real attack volume");
            action.percentColumn=0;action.independentColumn=2;action.speedColumn=1;action.speedToPermille=1;
            action.requiresEquippedAttackVolume=true;
            // Current SKL preload identifies the exact IMG, but does not prove
            // spawning. This bounded explicit reconstruction associates only
            // these reviewed effect clips; generic ALS remains unchanged.
            for(const auto &[path,order]:std::array<std::pair<const char *,int>,2>{{
                {"character/mage/effect/animation/thrustunder.ani",-1},
                {"character/mage/effect/animation/thrustover.ani",1}}}) {
                const auto clip=assets.animation(path);const auto source=makeSourceRef(pvf,path);
                const std::string expected=order<0?"ab3f9219f90eb8fa18588dbc9580799f534b4cb750f8f4ca2e0b8b91e321dbf3":
                    "3d4937a23de55e03a4694f01cb4e5f2a97766bd54a255eacb0858b3bb2857679";
                if(source.memberSha256!=expected||clip->frames.empty()||clip->duration<=0)
                    throw std::invalid_argument("Unreviewed Mage Thrust reconstructed visual clip");
                bool preloadMatches=false;
                const auto preload=skill.values("[skill preloading image]","common");
                for(const auto &frame:clip->frames)if(!frame.image.empty()) {
                    bool matches=false;for(const auto &image:preload)matches|=image.is_string()&&normalize(image.get<std::string>())==normalize(frame.image);
                    if(!matches)throw std::invalid_argument("Mage Thrust visual IMG differs from exact SKL preload");
                    preloadMatches=true;
                }
                if(!preloadMatches)throw std::invalid_argument("Mage Thrust reconstructed clip has no preloaded source IMG");
                FemaleGunnerSkillLayer layer;layer.source=source;layer.bodyPath=action.motion.memberPath;layer.layer=order;
                layer.loop=false;layer.synchronizedToBody=false;layer.inheritBodyRate=true;
                layer.evidence.push_back({{"policy","inferred-current1031-mage-thrust-visual-v1"},{"classification","inferred_beta"},
                    {"basis","Exact current SKL preload IMG identity matches every visible clip frame; names Over/Under and 160ms source blank lead agree with 160ms body windup"},
                    {"source_skill",action.skill.json()},{"source_ani",source.json()},{"source_duration_ms",clip->duration},
                    {"birth","accepted source action frame0; not a recovered native spawn call"},{"local_xyz",{0,0,0}},
                    {"layer_policy","under=-1 before character, over=1 after; named inference, native absolute layer unknown"},
                    {"clock","own immutable ANI delays, inherit selected body rate/pause; preserve source scale/rotation/blend/XY"},
                    {"lifetime","owned by source body action; final source blank tail may retire when body ends; every visible frame finishes earlier"},
                    {"native_dynamic_parity",false}});
                action.bodyLayers.push_back(std::move(layer));
            }
            action.evidence={{"policy","inferred-current1031-mage-thrust-body-v1"},{"classification","inferred_beta"},
                {"execution_model","native-body-reconstruction; no own mage NUT exists in current PVF"},
                {"source_chain","skilllist job3 registration -> MageSkill Thrust skill4 -> own CHR motion1/ATK0 -> actual EQU/LAY type15 -> source MP/CD and SKL operands -> unified damage/real monster response"},
                {"state_identity","not present in current global enum; state=-1 is unknown, never a runtime native state claim"},
                {"operand_mapping",{{"percent_column",0},{"independent_percent_column",2},{"speed_tenth_percent_column",1},{"speed_to_permille",1}}},
                {"knowledge_basis","Course11022 matches current level-property columns0/2 and speed1 with scale0.1%; independent coefficient55 is not flat damage"},
                {"qualification_policy","test-overlay-only inferred ground stand/dash; no native attack cancel grant or substituted BattleMage identity"},
                {"source_hit_response","Current dungeon ATK physical/weapon apply, push300 lift100 hitDelayRate3 hitWav SLASH_HIT_04; native weapon-inherited hitPause remains unknown"},
                {"normal_source_qualification",{{"required_level",5},{"growtypes",{0,1,2,3,4}},{"purchase_maximum",50},{"runtime_normal_learning_bound",false}}},
                {"unverified",{"native hit-confirm cancellation into UpperSwing/HandStrike/Swing","BattleMage normal-attack forced cancellation","exact native state and visual birth/layer/ownership","TP/chaser/passive chains","native speed combination and independent damage formula"}},
                {"scope","Real single Thrust release consumer; known followup/cancel mechanics remain incomplete; not whole skill or Mage completion"}};
            out.emplace(action.key,std::move(action));return out;
        }
        if(identity.jobId==constant(enums,"ENUM_CHARACTERJOB_PRIEST")) {
            // Independent bounded registration: a changed Upper source cannot
            // silently remove the already reviewed Hedgehog controller.
            try {
            SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;action.inferredNativeBody=true;
            action.header=nutRef(pvf,"sqr/dnf_enum_header.nut");
            action.key={identity.jobId,constant(enums,"SKILL_ANTIAIR_UPPER")};
            action.state=constant(enums,"STATE_ANTIAIR_UPPER");
            action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
            action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
            action.executableStates={action.standState,action.dashState};
            action.motionSlot=constant(enums,"CUSTOM_ANI_ANTIAIR_UPPER");
            action.attackSlot=constant(enums,"CUSTOM_ATTACKINFO_ANTIAIR_UPPER");
            const auto &skill=catalog.skillDefinition(action.key);
            action.skill=makeSourceRef(pvf,skill.source.script.path);
            if(action.skill.memberPath!="skill/priest/antiairupper.skl"||action.skill.memberSha256!="d8a660636603db3ff2e331558df8344cd6729bb319f9ed7ae8231f3cf5c325c3")
                throw std::invalid_argument("Unreviewed current1031 Priest Upper SKL");
            if(!skill.fieldsInScope("[executable states]","common").empty())
                throw std::invalid_argument("Priest Upper now authors executable states; review inferred admission");
            action.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(action.motionSlot)));
            size_t attacks=0;
            for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId)))
                if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.valueIndex==size_t(action.attackSlot)&&binding.occurrence==0)
                    {action.attack=makeSourceRef(pvf,binding.resource.path);++attacks;}
            if(attacks!=1||action.motion.memberPath!="character/priest/animation/antiairupper.ani"||
               action.motion.memberSha256!="1ad42c823e699fd82bdf77f8fbcb9e88e7e5d89650eb002226795e5b19d83422"||action.attack.memberPath!="character/priest/attackinfo/antiairupper.atk"||
               action.attack.memberSha256!="378696dd94288d7b90f44c5a40277e4d96b6578ed09a66d27aaff6dfb0cbb6b4")throw std::invalid_argument("Priest Upper own CHR/enum/ANI/ATK relationship changed");
            action.animation=action.motion;action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
            if(!action.attackDefinition.usable()||action.attackDefinition.type!=DamageAttackType::Physical||!action.attackDefinition.weaponDamageApply)
                throw std::invalid_argument("Priest Upper physical equipped-weapon ATK unavailable");
            const auto body=assets.animation(action.motion.memberPath);
            if(body->frames.empty()||body->duration<=0||pvf.has(action.motion.memberPath+".als"))
                throw std::invalid_argument("Priest Upper source body/no-ALS contract changed");
            for(const auto &frame:body->frames) {
                if(!frame.properties.contains("13")||frame.properties.at("13")!=1)
                    throw std::invalid_argument("Priest Upper reviewed source protection changed");
                for(const auto &box:frame.boxes)if(box.type==15)
                    throw std::invalid_argument("Priest Upper now has body attacks; review equipped-only policy");
            }
            const auto defaults=defaultCharacterAppearance(pvf,catalog,identity);
            const auto composed=readCharacterAttackMotion(assets,defaults,action.motion.memberPath);
            for(size_t frame=0;frame<body->frames.size();++frame)
                for(const auto &box:composed.boxesAt(frame))if(box.w>0&&box.h>0&&box.d>0&&action.bodyLayerBirthFrame<0)
                    action.bodyLayerBirthFrame=int(frame);
            if(action.bodyLayerBirthFrame<0)throw std::invalid_argument("Priest Upper actual default EQU/LAY supplies no attack volume");
            action.percentColumn=0;action.liftColumn=1;action.independentColumn=2;
            action.actorAttackSpeedOnly=true;action.requiresEquippedAttackVolume=true;action.sourceFrameSuperArmor=true;
            const auto shake=skill.values("[shake screen]","common");
            if(shake.size()!=2||!shake[0].is_number_integer()||!shake[1].is_number_integer()||
               shake[0].get<int64_t>()<0||shake[0].get<int64_t>()>INT32_MAX||shake[1].get<int64_t>()<0||shake[1].get<int64_t>()>INT32_MAX)
                throw std::invalid_argument("Priest Upper source shake unavailable");
            action.shakeAmplitude=shake[0].get<int>();action.shakeDurationMs=shake[1].get<int>();
            action.castSound="PR_ANTIAIR";
            for(const auto &[path,order]:std::array<std::pair<const char *,int>,2>{{
                {"character/priest/effect/animation/antiairupper/back.ani",-1},
                {"character/priest/effect/animation/antiairupper/front.ani",1}}}) {
                const auto source=makeSourceRef(pvf,path);const auto clip=assets.animation(path);
                const std::string expected=order<0?"f8f08d782f5dd9b2b7fbbb7115053f1a9f449e3685105fc79b4456d274e78896":"b4b97d590f2220fc3991bc6ed8b8d9fd2cc68187b202057d0ce72d70bb640bf9";
                if(source.memberSha256!=expected||clip->frames.empty()||clip->duration<=0||clip->globals.value("0",false))
                    throw std::invalid_argument("Unreviewed Priest Upper effect source");
                FemaleGunnerSkillLayer layer;layer.source=source;layer.bodyPath=action.motion.memberPath;layer.layer=order;
                layer.evidence.push_back({{"policy","inferred-current1031-priest-upper-visual-v1"},{"classification","inferred_beta"},
                    {"source_animation",source.json()},{"source_duration_ms",clip->duration},{"local_xyz",{0,0,0}},
                    {"birth_frame",action.bodyLayerBirthFrame},{"birth_basis","first actual default EQU/LAY attack; all current starter weapon families checked"},
                    {"clock","own source delays at rate100, pause with owner; independent from live actor rate rescaling"},
                    {"lifetime","retire at own ANI end or owner action exit, control, death, map change"},
                    {"layer_policy","inferred back=-1/front=1; no recovered native or automatic ALS caller"},{"native_dynamic_parity",false}});
                action.bodyLayers.push_back(std::move(layer));
            }
            action.evidence={{"policy","inferred-current1031-priest-upper-body-v1"},{"classification","inferred_beta"},
                {"source_chain","CHR initial1 -> enum state20/motion1/ATK2 -> own body + actual EQU/LAY type15 -> SKL percent0/independent2/lift1 -> unified damage and own monster response"},
                {"speed_policy","actor/equipment real attack speed only; no skill speed operand; native aggregation unresolved"},
                {"effects_policy","explicit exact-version visual association, not a preload, filename or recovered caller"},
                {"audio_policy","inferred PR_ANTIAIR once at accepted cast; exact source catalog and OGG preflight"},
                {"shake_policy","source amplitude/duration once at first equipped attack frame; timing/waveform inferred"},
                {"protection_policy","existing reviewed current type13 body armor policy; distinct from invincibility, death still cancels"},
                {"unverified",{"native speed/weight/protection formulas","native effect/audio caller and ordering","WillDriver13 active mode","TP210 damage boost","Avenger123 gauge and transformed119 state"}},
                {"full_skill_complete",false}};
            out.emplace(action.key,std::move(action));
            } catch(const std::exception &error) {diagnostics.push_back({{"code","source_priest_upper_adapter_blocked"},{"message",error.what()},{"full_skill_complete",false}});}
        }
        if(identity.jobId==constant(enums,"ENUM_CHARACTERJOB_PRIEST")) {
            SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;
            action.registration=nutRef(pvf,"sqr/character/avenger_load_state.nut");
            action.header=nutRef(pvf,"sqr/character/priest/avenger_header.nut");
            action.callback=nutRef(pvf,"sqr/character/priest/hedgehog.nut");
            if(action.callback.memberSha256!="785588ad5884600326f6b469cfceb521e4b7957ca330152b40c62885d7acb630")
                throw std::invalid_argument("Unreviewed source Hedgehog callback program");
            const auto header=lex(pvf.read(action.header.memberPath)),script=lex(pvf.read(action.callback.memberPath));
            size_t registrations=0;
            for(const auto &args:calls(lex(pvf.read(action.registration.memberPath)),"pushState")) {
                if(args.size()!=4||args[1].size()!=1||!args[1][0].quoted||args[1][0].value!="Hedgehog")continue;
                if(pathOperand(args[0])!=action.callback.memberPath.substr(4))throw std::invalid_argument("Hedgehog callback registration differs");
                action.key={identity.jobId,constant(header,operand(args[3]))};action.state=constant(header,operand(args[2]));++registrations;
            }
            if(registrations!=1)throw std::invalid_argument("Missing/ambiguous source Hedgehog state registration");
            action.skill=makeSourceRef(pvf,catalog.skillDefinition(action.key).source.script.path);
            action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
            action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
            const auto executable=catalog.skillDefinition(action.key).fieldsInScope("[executable states]","common");
            if(executable.size()!=1)throw std::invalid_argument("Source Hedgehog executable states ambiguous");
            for(const auto &value:executable.front()->field.values)
                if(!value.is_number_integer()||!action.executableStates.insert(value.get<int>()).second)
                    throw std::invalid_argument("Invalid source Hedgehog executable state");
            if(action.executableStates.empty())throw std::invalid_argument("Source Hedgehog executable states unavailable");
            action.motionSlot=constant(header,operand(oneCall(script,"sq_setCurrentAnimation",1)[0]));
            action.attackSlot=constant(header,operand(oneCall(script,"sq_setCurrentAttackInfo",1)[0]));
            action.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(action.motionSlot)));
            // Both motion and attack slots are current CHR ordered bindings.
            size_t attacks=0;
            for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId)))
                if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.valueIndex==size_t(action.attackSlot)&&binding.occurrence==0)
                    {action.attack=makeSourceRef(pvf,binding.resource.path);++attacks;}
            if(attacks!=1)throw std::invalid_argument("Source Hedgehog CHR attack binding ambiguous");
            action.animation=action.motion;
            action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
            if(!action.attackDefinition.usable())throw std::invalid_argument("Source Hedgehog ATK consumer unavailable");
            const auto power=oneCall(script,"sq_setAttackPowerWithPassive",5);
            if(constant(header,operand(power[0]))!=action.key.skillId||operand(power[1])!="state"||integer(power[2])!=-1||operand(power[4])!="1.0")
                throw std::invalid_argument("Unadmitted source Hedgehog power operands");
            action.percentColumn=integer(power[3]);
            const auto sound=oneCall(script,"sq_PlaySound",1);
            if(sound[0].size()!=1||!sound[0][0].quoted)throw std::invalid_argument("Invalid source Hedgehog cast sound");
            action.castSound=sound[0][0].value;
            const auto shake=oneCall(script,"sq_setShake",3);
            if(operand(shake[0])!="obj")throw std::invalid_argument("Unadmitted source Hedgehog shake owner");
            action.shakeAmplitude=integer(shake[1]);action.shakeDurationMs=integer(shake[2]);
            size_t flags=0;
            for(size_t i=0;i+2<script.size();++i)if(!script[i].quoted&&script[i].value=="flagIndex"&&script[i+1].value=="==") {
                const auto flag=integer({script[i+2]});if(flag<0||flag>=0xffff)throw std::invalid_argument("Source Hedgehog flag outside native low word");
                action.flag=uint16_t(flag);++flags;
            }
            const auto body=assets.animation(action.motion.memberPath);bool hasFlag=false,hasAttack=false;
            for(const auto &frame:body->frames) {
                if(frame.properties.contains("23")&&frame.properties.at("23").is_number_integer())hasFlag|=uint16_t(frame.properties.at("23").get<int32_t>())==action.flag;
                for(const auto &box:frame.boxes)hasAttack|=box.type==15;
            }
            if(flags!=1||!hasFlag||!hasAttack||body->duration<=0||action.percentColumn<0||action.shakeAmplitude<0||action.shakeDurationMs<0)
                throw std::invalid_argument("Source Hedgehog ANI/flag/attack operands unavailable");
            action.layersSource=makeSourceRef(pvf,action.motion.memberPath+".als");
            const auto als=pvf.script(action.layersSource.memberPath);
            std::map<std::string,std::string> declared;
            for(const auto &field:als.fields)if(normalize(field.tag)=="[use animation]") {
                if(field.values.size()!=2||!field.values[0].is_string()||!field.values[1].is_string()||
                    !declared.emplace(field.values[1].get<std::string>(),effectResource(pvf,als.path,field.values[0].get<std::string>())).second)
                    throw std::invalid_argument("Source Hedgehog ALS declaration ambiguous");
            }
            for(const auto &field:als.fields)if(normalize(field.tag)!="[use animation]") {
                if(normalize(field.tag)!="[none effect add]"||field.values.size()!=3||field.values[0]!=0||
                    !field.values[1].is_number_integer()||!field.values[2].is_string())
                    throw std::invalid_argument("Source Hedgehog ALS outside reviewed frame0 attachment contract");
                const auto name=field.values[2].get<std::string>();const auto found=declared.find(name);
                if(found==declared.end()||found->second.empty())throw std::invalid_argument("Source Hedgehog ALS name unresolved");
                const auto clip=assets.animation(found->second);
                if(clip->frames.empty()||clip->duration<=0)throw std::invalid_argument("Source Hedgehog layer ANI unavailable");
                FemaleGunnerSkillLayer layer;layer.source=makeSourceRef(pvf,found->second);layer.bodyPath=action.motion.memberPath;
                layer.layer=field.values[1].get<int>();layer.loop=clip->globals.value("0",false);
                layer.synchronizedToBody=false;layer.inheritBodyRate=true;
                layer.evidence.push_back({{"policy","inferred-reviewed-hedgehog-none-effect-source-ani-v1"},
                    {"classification","inferred_beta"},{"als_source",action.layersSource.json()},{"source_offset",field.offset},
                    {"ordered_payload",field.values},{"native_kind",5},{"native_child_flag",1},{"unique_name",name},
                    {"source_frame",0},{"source_layer",layer.layer},{"local_xyz",{0,0,0}},
                    {"blend_policy","Retain own source ANI blend/RGBA/crop/rotation/scale; unknown native child flag render effect is not guessed"},
                    {"native_flag_render_consumer","unsupported"},{"native_layer_sentinel_interpretation","unresolved; current source numeric stable ordering"},
                    {"clock_policy","own source delays, owner currentTime/rate and pause; frame0 birth; 1031 addLayer rate inheritance confirmed, host clock mapping inferred"},
                    {"native_dynamic_parity",false}});
                action.bodyLayers.push_back(std::move(layer));
            }
            if(action.bodyLayers.size()!=declared.size()||action.bodyLayers.empty())throw std::invalid_argument("Source Hedgehog ALS attachment coverage differs");
            std::stable_sort(action.bodyLayers.begin(),action.bodyLayers.end(),[](const auto &a,const auto &b){return a.layer<b.layer;});
            action.evidence={{"policy","inferred-1031-reviewed-nut-body-action-v1"},{"classification","current1031-source-with-inferred-host-adaptation"},
                {"source_program","checkExecutable -> stopMove -> own CHR etc ANI/ATK -> SKL percent -> cast sound -> body type15 -> ALS effects -> flag shake -> ANI end stand"},
                {"damage_mapping","sq_setAttackPowerWithPassive fixedColumn -1 / percentColumn0; current SKL level-property explicitly labels magical attack percent"},
                {"qualification_policy","explicit-experimental-all-source-branches; source growtype4 required in normal learning; normal ledger untouched"},
                {"unverified",{"native cancel/IGNORE_FORCE priority","passive and TP multipliers","none-effect child flag drawing and layer sentinel meaning","native camera-shake waveform/intensity mapping","native damage formula"}}};
            out.emplace(action.key,std::move(action));return out;
        }
        if(identity.jobId!=constant(enums,"ENUM_CHARACTERJOB_AT_MAGE"))return out;
        SourceSkillAction action;
        action.registration=nutRef(pvf,"sqr/character/atmage_load_state.nut");
        action.header=nutRef(pvf,"sqr/character/atmage/atmage_header.nut");
        action.callback=nutRef(pvf,"sqr/character/atmage/windstrike/wind_strike.nut");
        action.passiveCallback=nutRef(pvf,"sqr/character/atmage/windstrike/po_wind_strike.nut");
        // Unknown edited programs must not silently retain a partial semantic
        // translation. Source numeric values are still read below, not copied.
        if(action.callback.memberSha256!="d4b8e155427ef7522b1236397edfc78f66851635aa9688cc8220d3aa7991a0c6"||
           action.passiveCallback.memberSha256!="8ac9189d9f725058dfee4a54bf0655a39b4d8912085bb7b7d8f92b7a7299758d")
            throw std::invalid_argument("Unreviewed source WindStrike callback program");
        const auto header=lex(pvf.read(action.header.memberPath)),script=lex(pvf.read(action.callback.memberPath));
        size_t registrations=0;
        for(const auto &args:calls(lex(pvf.read(action.registration.memberPath)),"pushState")) {
            if(args.size()!=5||args[2].size()!=1||!args[2][0].quoted||args[2][0].value!="WindStrike")continue;
            if(pathOperand(args[1])!=normalize(action.callback.memberPath.substr(4)))throw std::invalid_argument("WindStrike registration script differs");
            const auto enums=lex(pvf.read("sqr/dnf_enum_header.nut"));
            action.key={constant(enums,operand(args[0])),constant(header,operand(args[4]))};
            action.state=constant(header,operand(args[3]));++registrations;
        }
        if(registrations!=1||action.key.jobId!=identity.jobId)throw std::invalid_argument("Missing/ambiguous source WindStrike state registration");
        action.skill=makeSourceRef(pvf,catalog.skillDefinition(action.key).source.script.path);
        action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
        action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
        const auto executable=catalog.skillDefinition(action.key).fieldsInScope("[executable states]","common");
        if(executable.size()!=1)throw std::invalid_argument("Source NUT executable states missing or ambiguous");
        for(const auto &value:executable.front()->field.values) {
            if(!value.is_number_integer())throw std::invalid_argument("Malformed source NUT skill executable state");
            if(!action.executableStates.insert(value.get<int>()).second)throw std::invalid_argument("Repeated source NUT skill executable state");
        }
        if(action.executableStates.empty())throw std::invalid_argument("Source NUT executable states unavailable");
        action.motionSlot=constant(header,operand(oneCall(script,"sq_SetCurrentAnimation",1)[0]));
        action.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(action.motionSlot)));
        const auto percent=oneCall(script,"sq_GetBonusRateWithPassive",4),power=oneCall(script,"sq_GetPowerWithPassive",5);
        action.percentColumn=constant(header,operand(percent[2]));action.fixedColumn=constant(header,operand(power[2]));
        if(operand(percent[3])!="1.0"||operand(power[4])!="1.0"||constant(header,operand(power[3]))!=action.percentColumn)
            throw std::invalid_argument("Unadmitted source WindStrike coefficient scaling");
        action.liftColumn=integer(oneCall(script,"sq_GetLevelData",1)[0]);
        const auto spawn=oneCall(script,"sq_SendCreatePassiveObjectPacket",5);
        action.objectId=integer(spawn[0]);if(integer(spawn[1])!=0)throw std::invalid_argument("Unadmitted source WindStrike spawn direction mode");
        for(size_t axis=0;axis<3;++axis)action.offset[axis]=integer(spawn[axis+2]);
        size_t flagMatches=0;
        for(size_t i=0;i+2<script.size();++i)if(!script[i].quoted&&script[i].value=="flagIndex"&&script[i+1].value=="==") {
            const auto value=integer({script[i+2]});if(value<0||value>=0xffff)throw std::invalid_argument("Source action flag outside native low word");
            action.flag=uint16_t(value);++flagMatches;
        }
        if(flagMatches!=1)throw std::invalid_argument("Source action keyframe predicate ambiguous");
        size_t passiveRegistrations=0;
        for(const auto &args:calls(lex(pvf.read(action.registration.memberPath)),"pushPassiveObj"))
            if(args.size()==2&&args[0].size()==1&&args[0][0].quoted&&pathOperand(args[0])==action.passiveCallback.memberPath.substr(4)) {
                if(integer(args[1])!=action.objectId)throw std::invalid_argument("Source passive NUT/PO ID differs");++passiveRegistrations;
            }
        if(passiveRegistrations!=1)throw std::invalid_argument("Missing/ambiguous source passive registration");
        action.objectRegistry=makeSourceRef(pvf,"passiveobject/passiveobject.lst");
        const auto list=pvf.script(action.objectRegistry.memberPath);size_t objects=0;
        for(size_t i=0;i+1<list.tokens.size();i+=2)if(list.tokens[i].at("value")==action.objectId) {
            action.object=makeSourceRef(pvf,relative(action.objectRegistry.memberPath,list.tokens[i+1].at("value").get<std::string>()));++objects;
        }
        if(objects!=1)throw std::invalid_argument("Source passive object registration ambiguous");
        const auto object=pvf.script(action.object.memberPath);
        action.animation=makeSourceRef(pvf,relative(object.path,uniqueString(object,"[basic motion]")));
        action.attack=makeSourceRef(pvf,relative(object.path,uniqueString(object,"[attack info]")));
        action.objectAnimation=assets.animation(action.animation.memberPath);
        if(action.objectAnimation->duration<=0||action.objectAnimation->frames.empty())throw std::invalid_argument("Source action PO ANI has no positive duration");
        action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
        if(!action.attackDefinition.usable())throw std::invalid_argument("Source action PO ATK consumer unavailable");
        const auto body=assets.animation(action.motion.memberPath);bool hasFlag=false;
        for(const auto &frame:body->frames)if(frame.properties.contains("23")&&frame.properties.at("23").is_number_integer())
            hasFlag|=uint16_t(frame.properties.at("23").get<int32_t>())==action.flag;
        if(!hasFlag)throw std::invalid_argument("Source action body ANI has no required native flag");
        action.evidence={{"policy","inferred-1031-reviewed-nut-passive-action-v1"},{"classification","current1031-source-with-inferred-host-adaptation"},
            {"source_program","checkExecutable -> onSetState StopMove/CHR custom ANI/attack speed -> flag predicate -> write percent/fixed/upForce -> create PO -> customData ATK setters -> destroy at PO ANI end"},
            {"damage_mapping","Percent column and fixed column from source APIs; existing unified damage/independent scaling remains inferred"},
            {"passive_modifier_chain","No source passive modifier consumer added; tested baseline has none"},
            {"spawn_axes","NUT X/Y/Z offset, X mirrored by source direction; engine direction-mode parity pending user"},
            {"unverified",{"native cancellation/force-priority contract","native independent attack formula","TP/other passive modifiers","native mass-to-lift formula"}}};
        out.emplace(action.key,std::move(action));
    } catch(const std::exception &error) {
        diagnostics.push_back({{"code","source_nut_action_adapter_blocked"},{"message",error.what()},{"full_skill_complete",false}});
    }
    appendSourceWaterCannonAction(pvf,assets,catalog,identity,out,diagnostics);
    return out;
}
SourceSkillOperands evaluateSourceSkillAction(const SourceSkillAction &action,const SkillSourceData &skill,int level) {
    SourceSkillOperands out;
    const auto table=skill.values("[level info]");
    if(action.native40Jp) {
        if(level<1)throw std::invalid_argument("Fighter native action requires a positive selected level");
        const auto value=[&](int col)->double {if(col<0)return 0;const auto v=skillLevelValue(table,level,col);
            if(!v||!std::isfinite(*v)||*v<0||*v>INT32_MAX)throw std::invalid_argument("Fighter stage source coefficient unavailable");return *v;};
        out.damage.percent=float(value(action.percentColumn));out.damage.independentPercent=float(value(action.independentColumn));
        out.damage.replacesAttackCoefficients=true;
        if(action.liftColumn>=0) {
            const auto lift=value(action.liftColumn);if(lift>65535)throw std::invalid_argument("Fighter source lift exceeds native operand range");
            out.bodyLift=lift;
        }
        if(action.key==SkillKey{1,5}||action.key==SkillKey{1,6}||action.key==SkillKey{1,4}) {
            const auto speed=skillLevelValue(table,level,0);if(speed&&*speed>=0)out.attackSpeedBonusPermille=*speed*10;
        }
        out.evidence={{"adapter",action.snapshot()},{"level",level},{"percent",out.damage.percent},
            {"independent_percent",out.damage.independentPercent},{"stage_coefficients","selected per source stage at emission"},
            {"source_recovery_ms",0},{"formula_classification","40jp-source-structure-current1031-SKL-columns; independent scaling inferred"}};
        if(out.bodyLift)out.evidence["source_body_lift"]=*out.bodyLift;
        out.damage.sources.push_back(out.evidence);return out;
    }
    if(action.movingImpact) {
        const auto &spec=*action.movingImpact;const auto tableStatic=skill.values("[static data]");
        const auto integer=[&](const Json &v,const char *what)->int {
            if(!v.is_number_integer()||v<INT32_MIN||v>INT32_MAX)throw std::invalid_argument(what);return v.get<int>();};
        const auto value=[&](int column)->int {if(column<0||size_t(column)>=tableStatic.size())throw std::invalid_argument("Moving source static operand missing");
            return integer(tableStatic[size_t(column)],"Moving source static operand invalid");};
        const auto percent=skillLevelValue(table,level,action.percentColumn),size=skillLevelValue(table,level,spec.sizeColumn);
        if(!percent||!size||*percent<0||*percent>INT32_MAX||*size<=spec.impactSizeSubtract||*size>65535||std::floor(*size)!=*size)
            throw std::invalid_argument("Moving source damage/size payload out of range");
        SourceMovingImpactOperands moving;moving.sizePercent=int(*size);moving.speed=value(spec.speedStatic);moving.distance=value(spec.distanceStatic);
        if(moving.speed<=0||moving.speed>65535||moving.distance<=0||moving.distance>65535||spec.travelTimeNumerator<=0)
            throw std::invalid_argument("Moving source speed/distance payload out of range");
        const auto travel=int64_t(moving.distance)*spec.travelTimeNumerator/moving.speed;
        if(travel<=0||travel>INT32_MAX)throw std::invalid_argument("Moving source travel duration out of range");moving.travelMs=int(travel);
        moving.recoilVelocity=value(spec.recoilStatics[0]);moving.recoilAcceleration=value(spec.recoilStatics[1]);
        moving.alternateRecoilVelocity=value(spec.recoilStatics[2]);moving.alternateRecoilAcceleration=value(spec.recoilStatics[3]);
        if(moving.recoilVelocity>=0||moving.alternateRecoilVelocity>=0||moving.recoilAcceleration<=0||moving.alternateRecoilAcceleration<=0)
            throw std::invalid_argument("Moving source recoil stop contract differs");
        out.movingImpact=moving;out.damage.percent=float(*percent);out.damage.fixedDamage=0;out.damage.replacesAttackCoefficients=true;
        out.evidence={{"adapter",action.snapshot()},{"level",level},{"percent",*percent},{"fixed",0},{"size_percent",moving.sizePercent},
            {"speed",moving.speed},{"distance",moving.distance},{"travel_ms",moving.travelMs},
            {"image_box_scale",*size/100.0},{"impact_image_box_scale",(*size-spec.impactSizeSubtract)/100.0},
            {"formula_classification","inferred-unified-source-percent-damage-v1"},{"passives_applied",false}};
        out.damage.sources.push_back(out.evidence);return out;
    }
    if(action.kind==SourceSkillActionKind::BodyAttack) {
        const auto percent=skillLevelValue(table,level,action.percentColumn);
        if(!percent||*percent<0||*percent>INT32_MAX)throw std::invalid_argument("Source body skill percent operand unavailable");
        out.damage.percent=float(*percent);out.damage.fixedDamage=0;out.damage.replacesAttackCoefficients=true;
        out.evidence={{"adapter",action.snapshot()},{"level",level},{"percent",*percent},{"fixed",0},
            {"passives_applied",false},{"formula_classification","inferred-unified-damage-baseline"}};
        if(action.inferredNativeBody) {
            const auto independent=skillLevelValue(table,level,action.independentColumn);
            if(action.actorAttackSpeedOnly&&action.speedColumn!=-1)
                throw std::invalid_argument("Actor-only body speed requires an absent skill speed column");
            const auto speed=action.actorAttackSpeedOnly?std::optional<double>(0):skillLevelValue(table,level,action.speedColumn);
            if(!independent||!speed||*independent<0||*independent>INT32_MAX||*speed<0||!std::isfinite(action.speedToPermille)||action.speedToPermille<=0||*speed>INT32_MAX/action.speedToPermille||action.recoveryMs<0)
                throw std::invalid_argument("Native-body skill independent/speed/recovery operand unavailable");
            out.damage.independentPercent=float(*independent);
            out.attackSpeedBonusPermille=*speed*action.speedToPermille;out.recoveryMs=action.recoveryMs;
            out.evidence["independent_percent"]=*independent;out.evidence["fixed"]=0;
            if(action.actorAttackSpeedOnly)out.evidence["attack_speed_policy"]="inferred-actor-attack-speed-only-v1; no SKL speed column or bonus";
            else out.evidence[action.speedToPermille==10?"source_speed_percent":"source_speed_tenth_percent"]=*speed;
            out.evidence["attack_speed_bonus_permille"]=out.attackSpeedBonusPermille;
            out.evidence["source_recovery_ms"]=out.recoveryMs;
            out.evidence["independent_mapping"]=action.independentColumn==2?"SKL dungeon column2 is percent of independent attack, not flat fixed damage; unified formula remains inferred":
                "SKL dungeon independentColumn is percent of independent attack, not flat fixed damage; unified formula remains inferred";
            if(action.liftColumn>=0) {
                const auto lift=skillLevelValue(table,level,action.liftColumn);
                if(!lift||!std::isfinite(*lift)||*lift<0||*lift>65535)throw std::invalid_argument("Source body lift operand unavailable");
                out.bodyLift=*lift;out.evidence["source_body_lift"]=*lift;
                out.evidence["body_lift_policy"]="inferred-direct-active-level-force-v1; only this descriptor overrides source ATK lift";
            }
        }
        out.damage.sources.push_back(out.evidence);return out;
    }
    const auto percent=skillLevelValue(table,level,action.percentColumn),fixed=skillLevelValue(table,level,action.fixedColumn),lift=skillLevelValue(table,level,action.liftColumn);
    if(!percent||!fixed||!lift||*percent<0||*fixed<0||*lift<0||*lift>65535||*percent>INT32_MAX||*fixed>INT32_MAX)
        throw std::invalid_argument("Source NUT skill operands invalid or outside payload units");
    out.damage.percent=float(*percent);out.damage.fixedDamage=float(*fixed);out.damage.replacesAttackCoefficients=true;
    out.lift=*lift;
    out.evidence={{"adapter",action.snapshot()},{"level",level},{"percent",*percent},{"fixed",*fixed},{"lift",*lift},
        {"level_data_single_operand","Current NUT sq_GetLevelData(column) reads the active skill level"},
        {"passives_applied",false},{"formula_classification","inferred-unified-damage-baseline"}};
    out.damage.sources.push_back(out.evidence);return out;
}
SourceSkillOperands evaluateSourceSkillActionTp(const SourceSkillAction &action,const SkillSourceData &base,int baseLevel,
    SkillKey passive,const SourceRef &passiveSource,const SkillSourceData &tp,int tpLevel) {
    if(!(action.key==SkillKey{2,4})||action.skill.memberSha256!="a5dd0ce1416e594fab06aa717dd199f2a118b0fa632f3e20e4580a3ffb0689f2"||
       !(passive==SkillKey{2,168})||passiveSource.memberPath!="skill/gunner/aerialkneeex.skl"||
       passiveSource.memberSha256!="35f71f44f3f92bc5319595931ca5ce9b65a5caf9078072862afe51e76908ce11"||
       passiveSource.packageIdentity!=action.skill.packageIdentity||!(base.definition.key==action.key)||!(tp.definition.key==passive)||
       sha256(base.definition.source.bytes)!=action.skill.memberSha256||sha256(tp.definition.source.bytes)!=passiveSource.memberSha256||
       action.kind!=SourceSkillActionKind::BodyAttack||!action.inferredNativeBody||tp.definition.kind!=SkillSourceKind::Passive||
       base.mode!=tp.mode||(base.mode!="dungeon"&&base.mode!="pvp")||tpLevel<0)
        throw std::invalid_argument("Unreviewed source-action TP identity/source/mode");
    const auto one=[&](const SkillSourceData &data,const char *tag,bool mode)->const ScopedSkillField & {
        auto fields=data.definition.fieldsInScope(tag,mode?data.mode:"common");
        if(fields.empty()&&mode)fields=data.definition.fieldsInScope(tag,"common");
        if(fields.size()!=1)throw std::invalid_argument("Missing/ambiguous reviewed source-action TP field: "+std::string(tag));
        return *fields.front();
    };
    const auto &feature=one(base,"[feature skill index]",false),&prerequisite=one(tp,"[pre required skill]",false);
    const auto &kind=one(tp,"[feature skill type]",false),&special=one(tp,"[special level up]",true);
    if(feature.field.values!=Json::array({passive.skillId})||prerequisite.field.values!=Json::array({action.key.skillId,10})||
       kind.field.values!=Json::array({1})||special.field.values!=Json::array({-1,action.percentColumn,"%",8,-1,action.independentColumn,"%",8}))
        throw std::invalid_argument("Reviewed source-action TP relationship or operand contract changed");
    int ceiling=0;for(const auto &value:tp.values("[growtype maximum level]")) {
        if(!value.is_number_integer()||value.get<int>()<0)throw std::invalid_argument("Malformed source TP purchase ceiling");
        ceiling=std::max(ceiling,value.get<int>());
    }
    if(tpLevel>ceiling||(tpLevel>0&&baseLevel<prerequisite.field.values[1].get<int>()))
        throw std::invalid_argument("Source-action TP level/base prerequisite unavailable");
    auto selected=base;auto field=selected.selected.find("[level info]");
    if(field==selected.selected.end())throw std::invalid_argument("Source-action TP base table unavailable");
    Json changes=Json::array();const auto &tuples=special.field.values;
    for(size_t tuple=0;tuple<tuples.size();tuple+=4) {
        const int column=tuples[tuple+1].get<int>();const double delta=tuples[tuple+3].get<double>();
        const auto original=skillLevelValue(base.values("[level info]"),baseLevel,column);
        if(!original)throw std::invalid_argument("Reviewed TP target base cell unavailable");
        const double changed=*original*(1+delta*tpLevel/100);
        if(!std::isfinite(changed)||changed<0||changed>INT32_MAX)throw std::invalid_argument("Source-action TP cell overflow");
        const size_t index=1+size_t(baseLevel-1)*field->second.field.values[0].get<size_t>()+size_t(column);
        field->second.field.values[index]=changed;
        changes.push_back({{"column",column},{"operator",tuples[tuple+2]},{"per_level",delta},
            {"before",*original},{"after",changed},{"base_scope",field->second.scope},{"base_offset",field->second.field.offset},
            {"tp_scope",special.scope},{"tp_offset",special.field.offset},{"tuple_index",tuple/4}});
    }
    // No TP template substitution: the current supported base rows are equal.
    // Original bytes/tokens and immutable selected fields stay untouched.
    auto result=evaluateSourceSkillAction(action,selected,baseLevel);
    Json receipt={{"policy","inferred-current1031-knee-tp-linear-base-overlay-v1"},{"classification","inferred_beta"},
        {"base",action.skill.json()},{"tp",passiveSource.json()},{"tp_key",passive.json()},
        {"base_level",baseLevel},{"tp_level",tpLevel},{"cells",changes},
        {"base_feature_offset",feature.field.offset},{"prerequisite_offset",prerequisite.field.offset},
        {"native_rounding_verified",false},{"template_replaced",false}};
    result.evidence["source_action_tp"]=receipt;result.evidence["passives_applied"]=tpLevel>0;
    result.damage.sources.push_back(std::move(receipt));return result;
}
} // namespace dnf
