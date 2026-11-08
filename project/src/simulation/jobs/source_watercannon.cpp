#include "dnf/source_skill_action.hpp"
#include "dnf/character_controller.hpp"
#include "dnf/effect_plan.hpp"
#include <algorithm>
#include <climits>
#include <regex>
#include <stdexcept>

namespace dnf {
namespace {
std::string text(Pvf &pvf,const std::string &path,const char *expected=nullptr) {
    const auto raw=pvf.read(path);
    if(expected&&sha256(raw)!=expected)throw std::invalid_argument("Unreviewed source WaterCannon program: "+path);
    std::string out(raw.begin(),raw.end());
    out=std::regex_replace(out,std::regex(R"(/\*[\s\S]*?\*/)"),"");
    return std::regex_replace(out,std::regex(R"(//[^\r\n]*)"),"");
}
std::smatch one(const std::string &source,const std::string &expression) {
    const std::regex pattern(expression);std::sregex_iterator at(source.begin(),source.end(),pattern),end;
    if(at==end)throw std::invalid_argument("WaterCannon source expression missing: "+expression);
    auto result=*at;if(++at!=end)throw std::invalid_argument("WaterCannon source expression ambiguous: "+expression);return result;
}
int number(const std::string &value) {
    size_t end=0;const auto n=std::stoll(value,&end);
    if(end!=value.size()||n<INT32_MIN||n>INT32_MAX)throw std::invalid_argument("WaterCannon operand outside int32");return int(n);
}
int constant(const std::string &source,const std::string &name) {
    return number(one(source,"\\b"+name+R"(\s*<-\s*(-?[0-9]+)\b)")[1]);
}
SourceRef nut(Pvf &pvf,const std::string &path) {
    auto ref=makeSourceRef(pvf,path);ref.textEncoding="ASCII executable tokens; original CP949 comments retained";return ref;
}
std::string unique(const Script &source,const char *tag) {
    const Field *found=nullptr;
    for(const auto &field:source.fields)if(normalize(field.tag)==tag) {
        if(found||field.values.size()!=1||!field.values[0].is_string())throw std::invalid_argument("WaterCannon ambiguous OBJ field");found=&field;
    }
    if(!found)throw std::invalid_argument("WaterCannon missing OBJ field");return found->values[0].get<std::string>();
}
SourceRef child(Pvf &pvf,const Script &parent,const std::string &value) {
    const auto path=effectResource(pvf,parent.path,value);
    if(path.empty())throw std::invalid_argument("WaterCannon source dependency missing/ambiguous: "+value);
    return makeSourceRef(pvf,path);
}
SourceRef object(Pvf &pvf,const Script &registry,int wanted) {
    const Json *found=nullptr;
    for(size_t i=0;i+1<registry.tokens.size();i+=2)if(registry.tokens[i].at("value")==wanted) {
        if(found)throw std::invalid_argument("WaterCannon repeated passive ID");found=&registry.tokens[i+1].at("value");
    }
    if(!found||!found->is_string())throw std::invalid_argument("WaterCannon passive ID missing");return child(pvf,registry,found->get<std::string>());
}
void registration(const std::string &loader,const std::string &path,int id) {
    size_t count=0;
    const std::regex expression(R"wc(IRDSQRCharacter\s*\.\s*pushPassiveObj\s*\(\s*"([^"]+)"\s*,\s*([0-9]+)\s*\))wc");
    for(std::sregex_iterator i(loader.begin(),loader.end(),expression),end;i!=end;++i)
        if(normalize((*i)[1].str())==path) {if(number((*i)[2])!=id)throw std::invalid_argument("WaterCannon PO callback ID differs");++count;}
    if(count!=1)throw std::invalid_argument("WaterCannon missing/ambiguous PO callback registration");
}
} // namespace

Json SourceMovingImpactAction::snapshot() const {
    return {{"impact_callback",impactCallback.json()},{"impact_object_id",impactObjectId},
        {"impact_object",impactObject.json()},{"impact_animation",impactAnimation.json()},{"impact_attack",impactAttack.json()},
        {"size_column",sizeColumn},{"speed_static",speedStatic},{"distance_static",distanceStatic},{"recoil_statics",recoilStatics},
        {"travel_time_numerator",travelTimeNumerator},{"impact_size_subtract",impactSizeSubtract},
        {"any_source_flag",anySourceFlag},{"impact_offset",impactOffset},{"visual_policy",visualPolicy},
        {"contact_policy","inferred-first-accepted-nonmiss-contact-spawn-impact-v1"},
        {"native_callback_miss_stuck_order_verified",false}};
}

void appendSourceWaterCannonAction(Pvf &pvf,Assets &assets,const CharacterCatalog &catalog,CharacterIdentity identity,
    std::map<SkillKey,SourceSkillAction> &out,Json &diagnostics) {
    try {
        const auto enums=text(pvf,"sqr/dnf_enum_header.nut");
        if(identity.jobId!=constant(enums,"ENUM_CHARACTERJOB_AT_MAGE"))return;
        SourceSkillAction action;action.kind=SourceSkillActionKind::MovingImpactObject;
        action.registration=nut(pvf,"sqr/character/atmage_load_state.nut");action.header=nut(pvf,"sqr/character/atmage/atmage_header.nut");
        action.callback=nut(pvf,"sqr/character/atmage/watercannon/watercannon.nut");
        action.passiveCallback=nut(pvf,"sqr/character/atmage/watercannon/po_atwatercannon.nut");
        SourceMovingImpactAction moving;moving.impactCallback=nut(pvf,"sqr/character/atmage/watercannon/po_atwatercannonexp.nut");
        const auto script=text(pvf,action.callback.memberPath,"6538c9a61c1f52567cac3bd84af028401e471bcf23281b13c9f8a948cd6e491b");
        const auto passive=text(pvf,action.passiveCallback.memberPath,"6c61c0ae07333cfdf05a073f0cb48c07956f3464f22ff1ae5321a637a9b8540c");
        text(pvf,moving.impactCallback.memberPath,"dc5e9331b08f84ae5b67f95b142ab809aed3bc6b500e5cfed80549b9fcabd2a8");
        const auto loader=text(pvf,action.registration.memberPath),header=text(pvf,action.header.memberPath);
        const auto bind=one(loader,R"wc(pushState\s*\(\s*(\w+)\s*,\s*"([^"]+)"\s*,\s*"WaterCannon"\s*,\s*(\w+)\s*,\s*(\w+)\s*\))wc");
        if("sqr/"+normalize(bind[2].str())!=action.callback.memberPath)throw std::invalid_argument("WaterCannon state script differs");
        action.key={constant(enums,bind[1]),constant(header,bind[4])};action.state=constant(header,bind[3]);
        if(action.key.jobId!=identity.jobId)throw std::invalid_argument("WaterCannon source job differs");
        action.standState=constant(enums,"STATE_STAND");action.dashState=constant(enums,"STATE_DASH");
        action.attackState=constant(enums,"STATE_ATTACK");action.jumpState=constant(enums,"STATE_JUMP");
        const auto &definition=catalog.skillDefinition(action.key);action.skill=makeSourceRef(pvf,definition.source.script.path);
        const auto executable=definition.fieldsInScope("[executable states]","common");
        if(executable.size()!=1)throw std::invalid_argument("WaterCannon executable state scope differs");
        for(const auto &value:executable.front()->field.values)if(!value.is_number_integer()||!action.executableStates.insert(value.get<int>()).second)
            throw std::invalid_argument("WaterCannon executable state malformed/repeated");
        if(action.executableStates.empty())throw std::invalid_argument("WaterCannon executable states empty");
        action.motionSlot=constant(header,one(script,R"(sq_SetCurrentAnimation\s*\(\s*(\w+)\s*\))")[1]);
        action.motion=makeSourceRef(pvf,catalog.at(identity.jobId).motion("[etc motion]",size_t(action.motionSlot)));
        action.percentColumn=number(one(script,R"(sq_GetBonusRateWithPassive\s*\(\s*SKILL_WATER_CANNON\s*,\s*STATE_WATER_CANNON\s*,\s*([0-9]+)\s*,\s*1\.0\s*\))")[1]);
        moving.sizeColumn=number(one(script,R"(sq_GetLevelData\s*\(\s*obj\s*,\s*SKILL_WATER_CANNON\s*,\s*([0-9]+)\s*,\s*skillLevel\s*\))")[1]);
        const auto spawn=one(script,R"(sq_SendCreatePassiveObjectPacket\s*\(\s*([0-9]+)\s*,\s*0\s*,\s*(-?[0-9]+)\s*,\s*(-?[0-9]+)\s*,\s*(-?[0-9]+)\s*\))");
        action.objectId=number(spawn[1]);for(size_t i=0;i<3;++i)action.offset[i]=number(spawn[i+2]);
        const auto column=[&](const std::string &variable,bool local=true) {
            return number(one(script,(local?"local\\s+":"[\\r\\n]\\s*")+variable+R"(\s*=\s*sq_GetIntData\s*\(\s*obj\s*,\s*SKILL_WATER_CANNON\s*,\s*([0-9]+)\s*\))")[1]);
        };
        moving.speedStatic=column("xVelocityWaterCannon");moving.distanceStatic=column("distance");
        moving.recoilStatics={column("xVelocity"),column("xAccel"),column("xVelocity",false),column("xAccel",false)};
        moving.travelTimeNumerator=number(one(passive,R"(local\s+arriveTime\s*=\s*\(\s*distance\s*\*\s*([0-9]+)\s*\)\s*/\s*xVelocity)")[1]);
        moving.impactSizeSubtract=number(one(passive,R"wc(local\s+sizeRate\s*=\s*obj\.getVar\("rate"\)\.get_vector\(0\)\s*-\s*([0-9]+))wc")[1]);
        moving.impactObjectId=number(one(passive,R"(sq_SendCreatePassiveObjectPacketPos\s*\(\s*parentObj\s*,\s*([0-9]+)\s*,\s*0\s*,\s*x\s*,\s*y\s*,\s*z\s*\))")[1]);
        moving.impactOffset[1]=number(one(passive,R"(local\s+y\s*=\s*sq_GetYPos\(obj\)\s*\+\s*([0-9]+))")[1]);
        action.castSound=one(script,R"wc(sq_PlaySound\s*\(\s*"([^"]+)"\s*\))wc")[1];
        registration(loader,action.passiveCallback.memberPath.substr(4),action.objectId);
        registration(loader,moving.impactCallback.memberPath.substr(4),moving.impactObjectId);
        action.objectRegistry=makeSourceRef(pvf,"passiveobject/passiveobject.lst");const auto registry=pvf.script(action.objectRegistry.memberPath);
        action.object=object(pvf,registry,action.objectId);moving.impactObject=object(pvf,registry,moving.impactObjectId);
        const auto mainObject=pvf.script(action.object.memberPath),impactObject=pvf.script(moving.impactObject.memberPath);
        action.animation=child(pvf,mainObject,unique(mainObject,"[basic motion]"));action.attack=child(pvf,mainObject,unique(mainObject,"[attack info]"));
        moving.impactAnimation=child(pvf,impactObject,unique(impactObject,"[basic motion]"));moving.impactAttack=child(pvf,impactObject,unique(impactObject,"[attack info]"));
        action.objectAnimation=assets.animation(action.animation.memberPath);moving.impactClip=assets.animation(moving.impactAnimation.memberPath);
        if(!action.objectAnimation->globals.value("0",false)||action.objectAnimation->duration<=0||moving.impactClip->duration<=0)
            throw std::invalid_argument("WaterCannon source loop/lifetime unavailable");
        action.attackDefinition=readAttackDamage(pvf.script(action.attack.memberPath));moving.impactAttackDefinition=readAttackDamage(pvf.script(moving.impactAttack.memberPath));
        if(!action.attackDefinition.usable()||!moving.impactAttackDefinition.usable())throw std::invalid_argument("WaterCannon ATK consumer unavailable");
        const auto body=assets.animation(action.motion.memberPath);size_t flagCount=0;
        for(const auto &frame:body->frames)if(frame.properties.contains("23")) {
            if(!frame.properties.at("23").is_number_integer())throw std::invalid_argument("WaterCannon source flag malformed");
            action.flag=uint16_t(frame.properties.at("23").get<int32_t>());++flagCount;
        }
        if(flagCount!=1)throw std::invalid_argument("WaterCannon revised multiple-flag program requires review");moving.anySourceFlag=true;
        action.layersSource=makeSourceRef(pvf,action.motion.memberPath+".als");const auto als=pvf.script(action.layersSource.memberPath);
        std::map<std::string,SourceRef> declared;
        for(const auto &field:als.fields)if(normalize(field.tag)=="[use animation]") {
            if(field.values.size()!=2||!field.values[0].is_string()||!field.values[1].is_string()||
               !declared.emplace(field.values[1].get<std::string>(),child(pvf,als,field.values[0].get<std::string>())).second)
                throw std::invalid_argument("WaterCannon body ALS declaration ambiguous");
        }
        for(const auto &field:als.fields)if(normalize(field.tag)!="[use animation]") {
            if(normalize(field.tag)!="[none effect add]"||field.values.size()!=3||field.values[0]!=0||
               !field.values[1].is_number_integer()||!field.values[2].is_string())throw std::invalid_argument("WaterCannon body ALS event contract changed");
            FemaleGunnerSkillLayer layer;layer.source=declared.at(field.values[2].get<std::string>());layer.bodyPath=action.motion.memberPath;
            layer.layer=field.values[1].get<int>();layer.synchronizedToBody=false;layer.inheritBodyRate=true;
            const auto clip=assets.animation(layer.source.memberPath);if(clip->frames.empty()||clip->duration<=0)throw std::invalid_argument("WaterCannon body effect unavailable");
            layer.loop=clip->globals.value("0",false);layer.evidence.push_back({{"policy",moving.visualPolicy},{"classification","inferred_beta"},
                {"source",action.layersSource.json()},{"source_offset",field.offset},{"ordered_payload",field.values},
                {"native_kind",5},{"native_child_flag",1},{"sentinel_layer_render_semantics_verified",false}});action.bodyLayers.push_back(std::move(layer));
        }
        if(action.bodyLayers.size()!=declared.size()||declared.empty())throw std::invalid_argument("WaterCannon body effect coverage differs");
        std::stable_sort(action.bodyLayers.begin(),action.bodyLayers.end(),[](const auto &a,const auto &b){return a.layer<b.layer;});
        action.evidence={{"policy","inferred-current1031-watercannon-moving-impact-v1"},{"classification","inferred_beta"},
            {"source_program","own registration -> fixed body/none-effect layers -> source flag -> moving24217 with size/recoil -> accepted nonmiss hit -> impact24256 excluding original handle -> source end cleanup"},
            {"knowledge_conflict","11731 forward-key prose conflicts with current opposite(input)==facing; executable current NUT wins"},
            {"elemental_chain","Source skill51 level0 returns before any change; learned passive separately unsupported, never silently granted"},
            {"tp236","Separate unsupported consumer does not block unmodified base26"},
            {"native_dynamic_parity",false},{"unverified",{"IGNORE_FORCE/cancel","miss/isStuck callback order","uniform-velocity rounding","mass-to-lift formula","follow-parent lifetime policy","elemental-chain and TP consumers"}}};
        action.movingImpact=std::move(moving);out.emplace(action.key,std::move(action));
    } catch(const std::exception &error) {
        diagnostics.push_back({{"code","source_watercannon_adapter_blocked"},{"message",error.what()},{"full_skill_complete",false}});
    }
}
} // namespace dnf
