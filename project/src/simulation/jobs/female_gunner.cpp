#include "dnf/female_gunner.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <regex>
#include <stdexcept>

namespace dnf {
namespace {
bool contains(const std::string &value,const std::string &part){return value.find(part)!=std::string::npos;}
std::string stemOf(const std::string &path){return normalize(std::filesystem::path(path).stem().string());}
Json propertySchema(const SkillSourceData &data) {
    const auto matches=data.definition.fieldsInScope("[level property]","common");
    Json out=Json::array();
    if(matches.empty())return out;
    if(matches.size()!=1)throw std::invalid_argument("Repeated female Gunner level property schema");
    const auto &v=matches.front()->field.values;
    if(v.size()<3||!v[2].is_string()||(v.size()-3)%3)throw std::invalid_argument("Malformed female Gunner level property schema");
    std::string format=v[2].get<std::string>();
    // Retain authored literal newlines. A line may contain multiple operands.
    const std::regex placeholder("<(?:int|float[0-9]*)>");
    size_t operand=0,lineStart=0;
    while(lineStart<=format.size()) {
        const auto end=format.find("\\n",lineStart);const auto line=format.substr(lineStart,end==std::string::npos?end:end-lineStart);
        std::string inheritedLabel;
        const auto colon=line.find(':');if(colon!=std::string::npos)inheritedLabel=line.substr(0,colon);
        else {const auto chinese=line.find("：");if(chinese!=std::string::npos)inheritedLabel=line.substr(0,chinese);}
        for(auto i=std::sregex_iterator(line.begin(),line.end(),placeholder);i!=std::sregex_iterator();++i) {
            const auto n=3+operand*3;if(n+2>=v.size())throw std::invalid_argument("Missing female Gunner display operand");
            if(!v[n].is_number_integer()||!v[n+1].is_number_integer()||!v[n+2].is_number())throw std::invalid_argument("Invalid female Gunner display selector");
            const auto start=size_t(i->position()),length=size_t(i->length());
            const auto suffix=line.substr(start+length);
            std::string unit="number";
            if(suffix.rfind("%%",0)==0||suffix.rfind("%",0)==0)unit="percent";
            else if(suffix.rfind("秒",0)==0)unit="seconds";
            else if(suffix.rfind("px",0)==0)unit="pixels";
            else if(suffix.rfind("发",0)==0||suffix.rfind("次",0)==0||suffix.rfind("个",0)==0||suffix.rfind("台",0)==0)unit="count";
            std::string label=inheritedLabel;
            if(label.empty())label=line.substr(0,start);
            while(!label.empty()&&label.back()==' ')label.pop_back();
            out.push_back({{"ordinal",operand},{"label",label},{"line",line},{"unit",unit},
                {"selector",v[n]},{"column",v[n+1]},{"scale",v[n+2]},
                {"schema_offset",matches.front()->field.offset},{"schema_ordinal",matches.front()->ordinal}});
            ++operand;
        }
        if(end==std::string::npos)break;lineStart=end+2;
    }
    // Current1031 includes authored operands beyond the visible placeholders
    // (FM31, CrisisRX78, RX78Ex and G3Ex). Preserve these as uninterpreted
    // operands; omitting a display placeholder cannot remove a source skill.
    while(3+operand*3<v.size()) {
        const auto n=3+operand*3;
        if(!v[n].is_number_integer()||!v[n+1].is_number_integer()||!v[n+2].is_number())throw std::invalid_argument("Invalid trailing female Gunner display operand");
        out.push_back({{"ordinal",operand},{"label",""},{"line",""},{"unit","unknown"},
            {"selector",v[n]},{"column",v[n+1]},{"scale",v[n+2]},
            {"schema_offset",matches.front()->field.offset},{"schema_ordinal",matches.front()->ordinal},
            {"interpretation","authored_operand_without_visible_placeholder"}});++operand;
    }
    return out;
}
FemaleGunnerStage stage(size_t motion,std::optional<size_t> attack={},bool emit=false,bool hold=false) {
    FemaleGunnerStage out;out.motionSlot=motion;out.hasAttack=bool(attack);out.attackSlot=attack.value_or(0);
    out.emitCommand=emit;out.holdForCommandLifetime=hold;return out;
}
FemaleGunnerStage namedStage(const char *tag,bool emit=true) {
    auto out=stage(0,{},emit);out.motionTag=tag;return out;
}
void addObject(FemaleGunnerSkillDescriptor &out,const std::string &stem) {
    out.inferredObjectMembers.push_back("passiveobject/character/gunner/"+stem+".obj");
}
void addMonster(FemaleGunnerSkillDescriptor &out,const std::string &stem) {
    out.inferredObjectMembers.push_back("monster/gunner/robot/"+stem+".mob");
}
std::string relativeMember(const std::string &parent,const std::string &literal) {
    const auto slash=parent.find_last_of('/');
    const auto value=normalize(literal);
    if(value.rfind("character/",0)==0||value.rfind("passiveobject/",0)==0||value.rfind("monster/",0)==0)return value;
    return normalize((std::filesystem::path(parent.substr(0,slash+1))/value).lexically_normal().generic_string());
}
std::optional<double> parameter(const FemaleGunnerSkillCommand &out,const std::string &label) {
    for(const auto &p:out.parameters)if(contains(p.at("label").get<std::string>(),label))return p.at("value").get<double>();
    return {};
}
void duration(FemaleGunnerSkillCommand &out,const std::string &label) {
    if(const auto v=parameter(out,label))out.lifetimeMs=int64_t(std::llround(*v*1000));
}
void interval(FemaleGunnerSkillCommand &out,const std::string &label) {
    if(const auto v=parameter(out,label))out.intervalMs=int64_t(std::llround(*v*1000));
}
void count(FemaleGunnerSkillCommand &out,const std::string &label) {
    if(const auto v=parameter(out,label)) {
        if(*v<0||*v>100000)throw std::invalid_argument("Female Gunner source count out of range");
        out.count=uint32_t(std::floor(*v));
    }
}
void attackCoefficients(FemaleGunnerSkillCommand &out) {
    // The selected semantic line is an explicitly inferred native setter
    // equivalent. Every operand retains its authored display class/column.
    bool selected=false;std::string selectedLine;
    out.damage.percent=0;out.damage.independentPercent=0;out.damage.replacesAttackCoefficients=true;
    for(const auto &p:out.parameters) {
        const auto label=p.at("label").get<std::string>();
        if(!contains(label,"攻击力")||contains(label,"增加")||contains(label,"减少")||contains(label,"附加")||contains(label,"感电")||contains(label,"灼伤")||contains(label,"出血"))continue;
        if(selected&&selectedLine!=p.at("line"))continue;
        // A source damage range describes charged min/max, not addition.
        // Likewise the operand following X is a hit count, not damage.
        const auto line=p.at("line").get<std::string>();
        if(p.at("unit")=="count")continue;
        if(selected&&(contains(line,"~")||contains(line,"～")))continue;
        selected=true;selectedLine=p.at("line").get<std::string>();
        const auto selector=p.at("selector").get<int>();
        const auto raw=p.at("raw_value").get<float>();
        if(selector==-2||selector==-4||selector==-5||selector==-6)out.damage.independentPercent+=raw;
        else if(p.at("unit")=="percent"||contains(line,"%%"))out.damage.percent+=p.at("value").get<float>();
        else out.damage.independentPercent+=raw;
    }
    if(!selected)out.damage.replacesAttackCoefficients=false;
    out.damage.sources.push_back({{"policy","inferred-1031-female-gunner-skl-setters-v1"},{"classification","inferred"},
        {"basis","Current1031 SKL ordered level-property operand and matching selected level/static row; KB is secondary"},
        {"unverified_conditions","Native setter dispatch, independent display classes and target-specific coefficient variants require original comparison"},
        {"impact","Apply one selected skill coefficient line once; preserve all other lines for per-stage/passive consumers"},
        {"skill_source",out.skillSource.json()},{"selected_line",selectedLine},{"parameters",out.parameters}});
}
}
const char *femaleGunnerCommandKindName(FemaleGunnerCommandKind kind) {
    switch(kind) {
    case FemaleGunnerCommandKind::Launch:return "launch";case FemaleGunnerCommandKind::Strike:return "strike";
    case FemaleGunnerCommandKind::Spawn:return "spawn";case FemaleGunnerCommandKind::Buff:return "buff";
    case FemaleGunnerCommandKind::Clear:return "clear";case FemaleGunnerCommandKind::Stage:return "stage";}
    return "unknown";
}
Json FemaleGunnerSkillDescriptor::snapshot() const {
    Json stageRows=Json::array(),effects=Json::array(),objects=Json::array(),attacks=Json::array();
    for(const auto &s:stages)stageRows.push_back({{"motion_tag",s.motionTag},{"motion_slot",s.motionSlot},
        {"attack_tag",s.attackTag},{"attack_slot",s.hasAttack?Json(s.attackSlot):Json()},
        {"repeat",s.repeat},{"emit_command",s.emitCommand},{"hold_for_command_lifetime",s.holdForCommandLifetime}});
    for(const auto &s:effectSources)effects.push_back(s.json());for(const auto &s:objectSources)objects.push_back(s.json());for(const auto &s:attackSources)attacks.push_back(s.json());
    return {{"key",key.json()},{"source",source.json()},{"stem",stem},{"family",family},{"dedicated_runtime",dedicatedRuntime},
        {"native_confirmed",false},{"classification","inferred_source_controller"},{"stages",stageRows},
        {"effects",effects},{"objects",objects},{"attacks",attacks},{"property_schema",propertySchema},{"diagnostics",diagnostics}};
}
Json FemaleGunnerSkillCommand::snapshot() const {
    return {{"kind",femaleGunnerCommandKindName(kind)},{"key",key.json()},{"skill_source",skillSource.json()},
        {"motion_source",motionSource?motionSource->json():Json()},{"animation_source",animationSource?animationSource->json():Json()},
        {"attack_source",attackSource?attackSource->json():Json()},{"object_source",objectSource?objectSource->json():Json()},
        {"action_sequence",actionSequence},{"pulse_id",pulseId},{"stage",stage},{"level",level},{"family",family},{"effect_role",effectRole},
        {"x",x},{"y",y},{"z",z},{"offset_x",offsetX},{"offset_y",offsetY},{"offset_z",offsetZ},{"direction",direction},
        {"speed",speed},{"range",range},{"lifetime_ms",lifetimeMs},{"interval_ms",intervalMs},{"count",count},{"follow_caster",followCaster},
        {"preflight_only",preflightOnly},{"release_delay_ms",releaseDelayMs},
        {"damage",damage.snapshot()},{"parameters",parameters},{"raw_tables",rawTables},{"evidence",evidence},{"diagnostics",diagnostics}};
}
FemaleGunnerSkillDescriptor describeFemaleGunnerSkill(const SkillSourceData &data,const SourceRef &source) {
    if(data.definition.key.jobId!=5)throw std::invalid_argument("Female Gunner descriptor requires job5");
    FemaleGunnerSkillDescriptor out;out.key=data.definition.key;out.source=source;out.kind=data.definition.kind;
    out.stem=stemOf(source.memberPath);out.propertySchema=propertySchema(data);
    if(out.kind==SkillSourceKind::Passive) {
        if(out.key.skillId>=179&&out.key.skillId<=194&&out.key.skillId!=185&&out.key.skillId!=186&&out.key.skillId!=187&&out.key.skillId!=188&&out.key.skillId!=189&&out.key.skillId!=190)out.family="profession_or_system_passive";
        else if(out.stem.rfind("armormastery",0)==0)out.family="armor_mastery";
        else if(out.stem.rfind("cancel",0)==0||out.key.skillId==8||out.key.skillId==32)out.family="input_qualification";
        else if(out.key.skillId>=140&&out.key.skillId<=168||out.key.skillId>=211)out.family="skill_reinforcement";
        else out.family="combat_passive";
        out.diagnostics.push_back({{"code","passive_requires_actual_consumer"},{"message","Source parameters are exposed; passive state/stat/profession consumers must be audited individually"}});
        return out;
    }
    out.dedicatedRuntime=true;
    switch(out.key.skillId) {
    case 1:case 2:case 30:case 52:
        out.family="ammo_enchantment";out.stages={namedStage("[buff motion]")};
        if(out.key.skillId==1)addObject(out,"flamebulletfireexplosion");break;
    case 3:out.family="melee_multihit";out.stages={stage(9,0),stage(10)};break;
    case 4:out.family="melee_launcher";out.stages={stage(11,1)};break;
    case 7:out.family="melee_stun";out.stages={stage(14,3)};break;
    case 6:out.family="grab_ground_shoot";out.stages={stage(12,2),stage(13,{},true)};addObject(out,"treadshootsub");break;
    case 14:out.family="grab_aerial_gatling";out.stages={stage(11,1),stage(23),stage(24,{},true)};addObject(out,"subweaponbulletgatlingaerial");break;
    case 5:case 20:case 47:
        out.family=out.key.skillId==47?"bullet_launcher":"bullet_headshot";out.stages={namedStage("[attack motion]")};
        for(const auto *w:{"revolver","automatic","musket","handcannon","bowgun"})addObject(out,std::string("upbullet")+w);break;
    case 9:out.family="radial_multishot";out.stages={stage(99),stage(15,9,true,true)};break;
    case 10:out.family="ranged_guard";out.stages={stage(16,{},true,true)};break;
    case 11:case 33:case 37:case 43:case 46:case 60:case 62:case 175:case 176:case 180:
        out.family="timed_buff";out.stages={namedStage("[buff motion]")};break;
    case 12:out.family="channel_projectile";out.stages={stage(19),stage(20,{},true,true)};addObject(out,"subweaponbulletgatlingfront");break;
    case 13:case 36:case 107:
        out.family="channel_flame";out.stages={stage(19),stage(20,{},true,true)};
        addObject(out,out.key.skillId==13?"subweaponbulletflamethrowerat":out.key.skillId==36?"subweaponbulletflamethrowerboostat":"subweaponbulletblizzardthrowerboostat");break;
    case 15:out.family="mobile_shoot";out.stages={stage(25,{},true)};addObject(out,"upbulletrevolver");break;
    case 26:out.family="counter_shoot";out.stages={stage(49),stage(50,7)};break;
    case 27:case 28:case 29:case 63:case 105:case 106:
        out.family="robot_summon";out.stages={stage(34,{},true)};
        addMonster(out,out.key.skillId==27?"rx78":out.key.skillId==28?"ez8":out.key.skillId==29?"exs":out.key.skillId==63?"tempesterat":out.key.skillId==105?"ez8ex":"exsex");
        addObject(out,out.key.skillId==27?"rx78explosion":out.key.skillId==28?"ez8explosion":out.key.skillId==29?"exsviperbullet":out.key.skillId==63?"tempestergunbullet":out.key.skillId==105?"rx78explosionex":"exslaser");break;
    case 35:out.family="moving_melee";out.stages={stage(46,5)};break;
    case 38:case 39:case 40:case 73:
        out.family="heavy_projectile";out.stages={stage(17),stage(18,{},true)};
        addObject(out,out.key.skillId==38?"subweaponbulletfm31":out.key.skillId==39?"subweaponbulletlaser":out.key.skillId==40?"subweaponbulletsteyr":"cannonball");break;
    case 45:out.family="targeted_bomb";out.stages={namedStage("[throw motion 2-1]")};addObject(out,"uraniumbomb");break;
    case 48:out.family="spread_shot";out.stages={stage(35,{},true)};addObject(out,"crossshoot");break;
    case 50:out.family="robot_detonation";out.stages={namedStage("[throw motion 2-1]")};break;
    case 51:out.family="returning_gunhawk";out.stages={stage(51,{},true),stage(52)};addObject(out,"doublegunhawk");break;
    case 53:out.family="projectile_field";out.stages={namedStage("[throw motion 2-1]")};addObject(out,"atnapalmbomb");addObject(out,"atnapalmbombexplosion");break;
    case 56:case 57:case 58:
        out.family="grenade";out.stages={namedStage("[throw motion 1-1]")};
        addObject(out,out.key.skillId==56?"grenadenone":out.key.skillId==57?"grenadelight":"grenadewater");break;
    case 59:out.family="robot_airdrop";out.stages={namedStage("[throw motion 2-1]")};addObject(out,"mechadrop");addMonster(out,"droprx78");break;
    case 71:out.family="charged_pull_projectile";out.stages={stage(37),stage(38),stage(39,{},true)};addObject(out,"extruder");break;
    case 72:out.family="multishot";out.stages={stage(40),stage(41,{},true),stage(42),stage(43),stage(44),stage(45)};addObject(out,"upbulletrevolver");break;
    case 75:case 108:
        out.family="cluster_bomb";out.stages={stage(21),stage(22,{},true)};addObject(out,out.key.skillId==75?"atstinger":"atstingerex");
        addObject(out,out.key.skillId==75?"atstingersub":"atstingersubex");break;
    case 76:case 103:
        out.family="proximity_mine";out.stages={stage(34,{},true)};addObject(out,out.key.skillId==76?"flashmine":"flashmineex");break;
    case 77:case 102:
        out.family="remote_bomb";out.stages={stage(47),stage(out.key.skillId==77?48:96,{},true)};addObject(out,out.key.skillId==77?"c4remote":"c4exdisk");break;
    case 78:out.family="targeted_sniping";out.stages={namedStage("[sit motion]")};addObject(out,"nielsnipingscope");addObject(out,"nielsnipinghit");break;
    case 79:case 80:case 81:
        out.family="g_transform";out.stages={stage(34,{},true)};addObject(out,out.key.skillId==79?"g1":out.key.skillId==80?"g2":"g3");
        if(out.key.skillId==79)addObject(out,"g1bullet");break;
    case 83:out.family="factory_summon";out.stages={stage(34,{},true)};addObject(out,"sparrowfactory");addMonster(out,"sparrow");break;
    case 96:out.family="awakening_g0";out.stages={stage(62),stage(63,{},true,true)};addObject(out,"g0");break;
    case 97:out.family="awakening_particle_cannon";out.stages={stage(64),stage(65,{},true,true)};addObject(out,"ancienttrigger");addObject(out,"ancienttriggersublaser");break;
    case 98:out.family="awakening_emp";out.stages={namedStage("[throw motion 2-1]")};addObject(out,"empstorm");addObject(out,"empstormexp");break;
    case 100:out.family="awakening_twingunblade";out.stages={stage(66,{},true)};
        for(const char *object:{"twingunbladebulletattack","twingunbladebulletdashattack","twingunbladebulletjumpattack","twingunbladegunhawk","twingunbladegunhawktrace"})addObject(out,object);break;
    case 101:out.family="moving_melee_burn";out.stages={stage(94,22)};break;
    case 104:out.family="multishot_finisher";out.stages={stage(40),stage(97,24),stage(41,{},true),stage(98,25)};addObject(out,"upbulletrevolver");break;
    case 109:out.family="charged_ammo_shot";out.stages={stage(100),stage(101,{},true)};addObject(out,"upbulletmusket");break;
    case 169:out.family="backstep";out.stages={namedStage("[jump motion]")};break;
    case 190:out.family="quick_standing";out.stages={namedStage("[sit motion]")};break;
    default:out.family="unmapped_active";out.dedicatedRuntime=false;
        out.diagnostics.push_back({{"code","female_gunner_active_dispatch_missing"},{"skill",out.key.json()}});break;
    }
    return out;
}
void loadFemaleGunnerResources(Pvf &pvf,Assets &assets,FemaleGunnerSkillDescriptor &out) {
    std::set<std::string> effects,attacks;
    for(const auto &path:out.inferredObjectMembers) {
        if(!pvf.has(path)){out.diagnostics.push_back({{"code","female_gunner_object_missing"},{"path",path}});out.dedicatedRuntime=false;continue;}
        out.objectSources.push_back(makeSourceRef(pvf,path));
        FemaleGunnerObjectBinding object;object.source=out.objectSources.back();
        const auto script=pvf.script(path);
        for(const auto &f:script.fields) {
            const auto tag=normalize(f.tag);
            const bool ani=tag=="[basic motion]"||tag=="[etc motion]"||contains(tag," motion]");
            const bool atk=tag=="[attack info]"||tag=="[etc attack info]";
            size_t slot=0;
            for(const auto &v:f.values) {
                const auto currentSlot=slot++;
                if(!v.is_string()||v.get<std::string>().empty())continue;
                const bool particle=normalize(v.get<std::string>()).size()>4&&normalize(v.get<std::string>()).substr(normalize(v.get<std::string>()).size()-4)==".ptl";
                if(!ani&&!atk&&!particle)continue;
                const auto member=relativeMember(path,v.get<std::string>());
                if(!pvf.has(member)){out.diagnostics.push_back({{"code","female_gunner_object_dependency_missing"},{"parent",path},{"path",member}});continue;}
                const auto bindingName=tag+"#"+std::to_string(currentSlot);
                if(ani)try {
                    const auto animation=assets.animation(member);
                    if(animation->frames.empty())throw std::invalid_argument("Empty female Gunner entity ANI");
                    const auto ref=makeSourceRef(pvf,member);object.animations.emplace_back(bindingName,ref);
                    if(effects.insert(member).second)out.effectSources.push_back(ref);
                }catch(const std::exception &e){out.diagnostics.push_back({{"code","female_gunner_object_animation_unusable"},{"path",member},{"message",e.what()}});}
                if(atk){const auto ref=makeSourceRef(pvf,member);object.attacks.emplace_back(bindingName,ref);if(attacks.insert(member).second)out.attackSources.push_back(ref);}
                if(particle)object.particles.emplace_back(bindingName,makeSourceRef(pvf,member));
            }
        }
        out.objectBindings.emplace(path,std::move(object));
    }
}
FemaleGunnerSkillCommand evaluateFemaleGunnerSkill(const FemaleGunnerSkillDescriptor &descriptor,
    const SkillSourceData &data,int level,int weaponSubtype) {
    if(!(descriptor.key==data.definition.key)||level<1)throw std::invalid_argument("Female Gunner source level/key mismatch");
    FemaleGunnerSkillCommand out;out.key=descriptor.key;out.skillSource=descriptor.source;out.level=level;out.family=descriptor.family;
    out.rawTables={{"level_info",data.values("[level info]")},{"static_data",data.values("[static data]")},
        {"property_schema",descriptor.propertySchema},{"source",descriptor.source.json()},{"mode",data.mode}};
    for(const auto &schema:descriptor.propertySchema) {
        auto item=schema;const auto selector=item.at("selector").get<int>(),column=item.at("column").get<int>();
        const auto table=data.values(selector<0?"[level info]":"[static data]");
        std::optional<double> value;
        if(selector<0)value=skillLevelValue(table,level,column);
        else if(column>=0&&size_t(column)<table.size()&&table[size_t(column)].is_number())value=table[size_t(column)].get<double>();
        if(!value||!std::isfinite(*value))throw std::invalid_argument("Female Gunner source operand unavailable: "+descriptor.stem+" column "+std::to_string(column));
        const auto scale=item.at("scale").get<double>();
        if(!std::isfinite(scale)||!std::isfinite(*value*scale))throw std::invalid_argument("Nonfinite female Gunner source display operand");
        item["raw_value"]=*value;item["value"]=*value*scale;item["table"]=selector<0?"[level info]":"[static data]";
        const auto selected=data.selected.find(item.at("table").get<std::string>());
        if(selected!=data.selected.end()){item["table_scope"]=selected->second.scope;item["table_offset"]=selected->second.field.offset;}
        out.parameters.push_back(std::move(item));
    }
    attackCoefficients(out);
    const auto family=out.family;
    if(data.definition.kind==SkillSourceKind::Passive)out.kind=FemaleGunnerCommandKind::Buff;
    else if(family=="ammo_enchantment"||family=="timed_buff"||family=="ranged_guard"||family=="awakening_twingunblade"||family=="quick_standing"||family=="backstep"||family=="mobile_shoot")out.kind=FemaleGunnerCommandKind::Buff;
    else if(family=="robot_detonation")out.kind=FemaleGunnerCommandKind::Clear;
    else if(family=="robot_summon"||family=="robot_airdrop"||family=="factory_summon"||family=="g_transform"||family=="proximity_mine"||family=="remote_bomb"||family=="projectile_field"||family.rfind("awakening_",0)==0)out.kind=FemaleGunnerCommandKind::Spawn;
    else if(!descriptor.objectSources.empty()||family=="radial_multishot")out.kind=FemaleGunnerCommandKind::Launch;
    else out.kind=FemaleGunnerCommandKind::Stage;
    duration(out,"持续时间");
    if(const auto r=parameter(out,"范围"))out.range=*r;
    if(const auto r=parameter(out,"射程"))out.range=*r;
    interval(out,"攻击间隔");
    if(const auto r=parameter(out,"攻击次数"))out.count=uint32_t(std::clamp(*r,1.0,100000.0));
    if(family=="channel_projectile") {duration(out,"发射时间上限");count(out,"每秒发射数");
        if(out.count){out.intervalMs=std::max<int64_t>(1,int64_t(1000/out.count));out.count=uint32_t(std::max<int64_t>(1,out.lifetimeMs/out.intervalMs));}}
    if(family=="channel_flame") {if(out.lifetimeMs==0) {
        const auto durationValue=skillLevelValue(data.values("[level info]"),level,1);
        if(durationValue)out.lifetimeMs=int64_t(*durationValue);}
        interval(out,"攻击间隔");if(out.intervalMs>0&&out.lifetimeMs>0)out.count=uint32_t(std::max<int64_t>(1,out.lifetimeMs/out.intervalMs));out.followCaster=true;}
    if(family=="ammo_enchantment"){count(out,"装弹数");if(out.count==1)count(out,"装弹");}
    if(family=="mobile_shoot"&&weaponSubtype>=0&&weaponSubtype<=4)
        if(const auto n=skillLevelValue(data.values("[level info]"),level,3+weaponSubtype))out.count=uint32_t(std::clamp(*n,1.0,100000.0));
    if(family=="multishot"||family=="multishot_finisher"){count(out,"发射次数上限");}
    if(family=="targeted_sniping"){count(out,"狙击次数上限");interval(out,"狙击冷却时间");duration(out,"狙击限制时间");}
    if(family=="cluster_bomb")count(out,"爆弹数量");
    if(family=="heavy_projectile"&&out.key.skillId==38)count(out,"发射榴弹数");
    if(family=="grab_ground_shoot") {
        if(parameter(out,"追射子弹数"))count(out,"追射子弹数");else count(out,"发射子弹数");
    }
    if(family=="grab_aerial_gatling")count(out,"发射子弹数");
    if(family=="robot_airdrop")count(out,"空投追击者数量");
    if(family=="g_transform"){interval(out,"自动发射冷却时间");if(!out.intervalMs)interval(out,"攻击间隔");out.followCaster=true;}
    if(family=="proximity_mine")duration(out,"存在时间上限");
    if(family=="projectile_field"){duration(out,"电磁地带持续时间");interval(out,"多段攻击间隔");}
    if(family=="ranged_guard"&&out.lifetimeMs==0)out.lifetimeMs=0;
    if(family=="quick_standing")duration(out,"蹲伏姿势无敌时间");
    if(family=="awakening_particle_cannon"){duration(out,"主炮持续时间");count(out,"主炮攻击次数");if(out.count)out.intervalMs=out.lifetimeMs/out.count;}
    if(!descriptor.objectSources.empty())out.objectSource=descriptor.objectSources.front();
    if(!descriptor.effectSources.empty())out.animationSource=descriptor.effectSources.front();
    if(!descriptor.attackSources.empty())out.attackSource=descriptor.attackSources.front();
    if(descriptor.objectSources.size()==5&&(family=="bullet_headshot"||family=="bullet_launcher")) {
        if(weaponSubtype<0||weaponSubtype>4)throw std::invalid_argument("Female Gunner bullet requires actual source weapon subtype");
        out.objectSource=descriptor.objectSources[size_t(weaponSubtype)];
    }
    Json objectRows=Json::array();
    for(const auto &entry:descriptor.objectBindings) {
        Json row={{"source",entry.second.source.json()},{"animations",Json::array()},{"attacks",Json::array()},{"particles",Json::array()}};
        for(const auto &value:entry.second.animations)row["animations"].push_back({{"binding",value.first},{"source",value.second.json()}});
        for(const auto &value:entry.second.attacks)row["attacks"].push_back({{"binding",value.first},{"source",value.second.json()}});
        for(const auto &value:entry.second.particles)row["particles"].push_back({{"binding",value.first},{"source",value.second.json()}});
        objectRows.push_back(std::move(row));
    }
    out.rawTables["object_bindings"]=std::move(objectRows);
    if(out.objectSource) {
        const auto known=descriptor.objectBindings.find(out.objectSource->memberPath);
        if(known!=descriptor.objectBindings.end()) {
            // Select the exact authored object's basic animation and ATK. No
            // stem matching and no parallel-array index assumptions.
            if(!known->second.animations.empty())out.animationSource=known->second.animations.front().second;
            if(!known->second.attacks.empty())out.attackSource=known->second.attacks.front().second;
            for(const auto &ani:known->second.animations)if(ani.first=="[basic motion]#0")out.animationSource=ani.second;
            for(const auto &atk:known->second.attacks)if(atk.first=="[attack info]#0")out.attackSource=atk.second;
        }
    }
    // Source data in this 1031 does not include the compiled launch velocity
    // setters for the common bullet objects. Keep an explicit centralized
    // inferred trajectory, never mark the chosen numbers as source operands.
    if(out.kind==FemaleGunnerCommandKind::Launch&&family!="channel_flame") {
        out.speed=1200;
        if(family=="grenade"||family=="returning_gunhawk"||family=="cluster_bomb")out.speed=450;
        if(out.range<=0)out.range=900;
        if(out.lifetimeMs<=0)out.lifetimeMs=int64_t(std::ceil(out.range/out.speed*1000));
        out.evidence.push_back({{"policy","inferred-1031-gunner-projectile-trajectory-v1"},{"classification","inferred"},
            {"basis","Source projectile OBJ/ANI/ATK define visuals and boxes; compiled native launch setters are absent from current NUT"},
            {"speed_pixels_per_second",out.speed},{"range_pixels",out.range},{"lifetime_ms",out.lifetimeMs},
            {"unverified_conditions","Native velocity, barrel origin, flight curvature and target selection require original dynamic comparison"}});
    }
    out.evidence.push_back({{"policy","inferred-1031-female-gunner-source-families-v1"},{"classification","inferred"},
        {"basis","Selected1031 CHR ordered slots, SKL mode/level/static operands and explicit OBJ/MOB references; source-only chains do not prove native dispatch"},
        {"native_confirmed",false},{"family",family},{"descriptor",descriptor.snapshot()}});
    return out;
}
} // namespace dnf
