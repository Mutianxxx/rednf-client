#include "dnf/source_skill_action.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/character_controller.hpp"
#include <algorithm>
#include <regex>
#include <stdexcept>

namespace dnf {
namespace {
int upperConstant(const Bytes &raw,const std::string &name) {
    const std::string original(raw.begin(),raw.end());
    const auto block=std::regex_replace(original,std::regex(R"(/\*[\s\S]*?\*/)"),"");
    const auto text=std::regex_replace(block,std::regex(R"(//[^\r\n]*)"),"");
    const std::regex re("\\b"+name+R"(\s*<-\s*(-?[0-9]+)\b)");
    std::sregex_iterator at(text.begin(),text.end(),re),end;
    if(at==end)throw std::invalid_argument("Upper common state constant missing: "+name);
    const auto found=std::stoi((*at)[1].str());
    if(++at!=end)throw std::invalid_argument("Upper common state constant repeated: "+name);
    return found;
}
}

void appendSourceMageUpperAction(Pvf &pvf,Assets &assets,const CharacterCatalog &catalog,CharacterIdentity identity,
    std::map<SkillKey,SourceSkillAction> &out,Json &diagnostics) {
    try {
        SourceSkillAction action;action.kind=SourceSkillActionKind::BodyAttack;action.inferredNativeBody=true;
        action.header=makeSourceRef(pvf,"sqr/dnf_enum_header.nut");const auto enums=pvf.read(action.header.memberPath);
        if(identity.jobId!=upperConstant(enums,"ENUM_CHARACTERJOB_MAGE"))return;
        const auto chr=makeSourceRef(pvf,catalog.at(identity.jobId).source.script.path);
        if(chr.memberPath!="character/mage/mage.chr"||chr.memberSha256!="46488abd08d458bb26749c0d46be4dab96c2d43c3f4bf3223cddeda6b6227483")
            throw std::invalid_argument("Unreviewed current1031 Mage CHR initial/default Upper relationship");
        size_t skills=0;
        for(const auto &entry:catalog.at(identity.jobId).skills.entries)
            if(entry.exists&&entry.path=="skill/mage/upperswing.skl") {action.key={identity.jobId,entry.id};++skills;}
        if(skills!=1)throw std::invalid_argument("Mage Upper source skill registration missing/ambiguous");
        const auto &skill=catalog.skillDefinition(action.key);action.skill=makeSourceRef(pvf,skill.source.script.path);
        if(action.skill.memberSha256!="9e3c527a1979ed30f2a4f898e3bf13ef76ff101ad7a5dc0716ca5f80856b654b"||
           !skill.fieldsInScope("[executable states]","common").empty())
            throw std::invalid_argument("Unreviewed current1031 Mage Upper SKL/admission");
        action.standState=upperConstant(enums,"STATE_STAND");action.dashState=upperConstant(enums,"STATE_DASH");
        action.attackState=upperConstant(enums,"STATE_ATTACK");action.jumpState=upperConstant(enums,"STATE_JUMP");
        action.executableStates={action.standState,action.dashState};
        size_t motions=0,attacks=0;
        for(const auto &binding:orderedCharacterBindings(catalog.at(identity.jobId))) {
            if(binding.occurrence!=0)continue;
            if(normalize(binding.resource.tag)=="[etc motion]"&&binding.resource.path=="character/mage/animation/upperswing.ani") {
                action.motion=makeSourceRef(pvf,binding.resource.path);action.motionSlot=int(binding.resource.valueIndex);++motions;
            }
            if(normalize(binding.resource.tag)=="[etc attack info]"&&binding.resource.path=="character/mage/attackinfo/upperswing.atk") {
                action.attack=makeSourceRef(pvf,binding.resource.path);action.attackSlot=int(binding.resource.valueIndex);++attacks;
            }
        }
        if(motions!=1||attacks!=1||action.motion.memberSha256!="1349ee90f25019124d9278496426e67744cfa5199869b36b978238f652bde9a2"||
           action.attack.memberSha256!="0c9f28c39ef0bf211961cdc1e1e83709a9e32fa4a60874986b7e7f536efe878a")
            throw std::invalid_argument("Unreviewed Mage Upper own CHR/body/ATK relationship");
        action.animation=action.motion;action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));
        if(!action.attackDefinition.usable()||action.attackDefinition.type!=DamageAttackType::Physical||!action.attackDefinition.weaponDamageApply)
            throw std::invalid_argument("Mage Upper own physical equipped-weapon ATK unavailable");
        const auto body=assets.animation(action.motion.memberPath);
        if(body->frames.empty()||body->duration<=0||pvf.has(action.motion.memberPath+".als"))
            throw std::invalid_argument("Mage Upper reviewed finite/no-ALS body changed");
        for(const auto &frame:body->frames) {
            if(frame.properties.contains("13"))throw std::invalid_argument("Mage Upper now authors protection; review source frame policy");
            for(const auto &box:frame.boxes)if(box.type==15)throw std::invalid_argument("Mage Upper now authors body attack; review equipped-only policy");
        }
        const auto appearance=defaultCharacterAppearance(pvf,catalog,identity);
        const auto composed=readCharacterAttackMotion(assets,appearance,action.motion.memberPath);
        int first=-1;
        for(size_t frame=0;frame<body->frames.size();++frame)
            for(const auto &box:composed.boxesAt(frame))if(box.w>0&&box.h>0&&box.d>0&&first<0)first=int(frame);
        if(first<=0)throw std::invalid_argument("Mage Upper default EQU/LAY first real attack boundary unavailable");
        SourceBodySidestepPolicy step;step.returnFrame=first;
        for(int frame=0;frame<first;++frame)step.returnSourceMs+=body->frames.at(size_t(frame)).duration;
        step.turnSourceMs=step.returnSourceMs/2;
        // Explicit beta tuning: raw 1031 explains out/back but has no distance.
        // Keep this version-limited amplitude in the descriptor, not ANI data.
        step.distance=24;action.bodySidestep=step;
        action.percentColumn=0;action.speedColumn=1;action.speedToPermille=1;
        action.liftColumn=2;action.independentColumn=4;action.requiresEquippedAttackVolume=true;
        const auto visual=makeSourceRef(pvf,"character/mage/effect/animation/upperswing.ani");
        const auto effect=assets.animation(visual.memberPath);
        if(visual.memberSha256!="4c8591f414444badc313f35b7356dfbd038b450a61756bea1a0e4d24c168a3ac"||
           effect->frames.empty()||effect->duration<=0||pvf.has(visual.memberPath+".als"))
            throw std::invalid_argument("Unreviewed Mage Upper exact inferred visual");
        const auto preload=skill.values("[skill preloading image]","common");bool visible=false;
        for(const auto &frame:effect->frames)if(!frame.image.empty()) {
            bool match=false;for(const auto &image:preload)match|=image.is_string()&&normalize(image.get<std::string>())==normalize(frame.image);
            if(!match)throw std::invalid_argument("Mage Upper effect IMG differs from exact own SKL preload");visible=true;
        }
        if(!visible)throw std::invalid_argument("Mage Upper source effect has no visible preloaded frames");
        FemaleGunnerSkillLayer layer;layer.source=visual;layer.bodyPath=action.motion.memberPath;layer.layer=1;
        layer.loop=false;layer.synchronizedToBody=false;layer.inheritBodyRate=true;
        layer.evidence.push_back({{"policy","inferred-current1031-mage-upper-visual-v1"},{"classification","inferred_beta"},
            {"source_skill",action.skill.json()},{"source_ani",visual.json()},{"birth","accepted action start; preserve source blank320"},
            {"basis","Exact own preload IMG matches all visible ANI frames; no native spawn caller is claimed"},
            {"local_xyz",{0,0,0}},{"source_xy_scale_blend_immutable",true},
            {"lifetime","owned by action; source visible ends640 before body680; only terminal blank truncated"},
            {"native_birth_layer_verified",false}});
        action.bodyLayers.push_back(std::move(layer));
        action.evidence={{"policy","inferred-current1031-mage-upper-body-v1"},{"classification","inferred_beta"},
            {"source_character",chr.json()},
            {"source_chain","own SKL/list -> CHR motion2/ATK1 -> actual EQU/LAY type15 -> MP/CD/operands -> unified damage and own MOB reactions"},
            {"state_identity","not present in current enum; -1 means unknown, not a native state claim"},
            {"operand_mapping",{{"percent",0},{"speed_tenth_percent",1},{"lift",2},{"unknown_preserved",3},{"independent_percent",4}}},
            {"knowledge_conflict","Course11024 prose speed1.0/independent0.47 conflicts with current SKL speed0.1 and row36; current bytes win"},
            {"lift_policy","inferred direct source level-info force350; current ATK lacks lift. UI350->100% is display, native mass formula unknown"},
            {"movement_policy",step.snapshot()},{"movement_basis","Own SKL explain: hold up/down to slide aside then return to attack; amplitude24 and midpoint turn are beta inference"},
            {"protection_policy","No own explicit frame protection; no armor or invulnerability granted"},
            {"qualification","inferred ground stand/dash; normal source initial1 and purchased levels use canonical effective ledger"},
            {"normal_learning_consumer_bound",true},{"tp210_normal_admitted",false},
            {"unverified",{"native caller/state/cancel","native sidestep distance/velocity/turn","lift mass and independent damage formula","native visual spawn/layer","TP210 and other Mage passive chains","cast and hit sounds"}},
            {"full_skill_complete",false}};
        out.emplace(action.key,std::move(action));
    }catch(const std::exception &error) {
        diagnostics.push_back({{"code","source_mage_upper_adapter_blocked"},{"message",error.what()},{"full_skill_complete",false}});
    }
}
} // namespace dnf
