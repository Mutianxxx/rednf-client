#include "dnf/combat.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
bool projectileErrors(const Json &diagnostics) {
    for(const auto &entry:diagnostics) if(entry.value("severity",std::string())=="error") return true;
    return false;
}
void projectileIssue(MonsterProjectileDefinition &out,const char *kind,Json details=Json::object(),const char *severity="error") {
    details["kind"]=kind;details["severity"]=severity;out.diagnostics.push_back(std::move(details));
}
Json projectileRef(const Script &source,size_t offset=0,size_t length=0,size_t ordinal=0) {
    SourceRef result;
    result.packageIdentity=source.source.value("package_identity",std::string());
    result.memberPath=source.path;result.memberSha256=sha256(source.rawBytes);
    result.literalPath=source.source.value("literal_path",source.path);
    result.byteOffset=offset;result.byteLength=length?length:source.rawBytes.size()-std::min(offset,source.rawBytes.size());
    result.ordinal=ordinal;result.scope="monster_projectile";
    return result.json();
}
Json projectileFieldRef(const Script &source,size_t ordinal) {
    const auto offset=source.fields.at(ordinal).offset;
    const auto end=ordinal+1<source.fields.size()?source.fields[ordinal+1].offset:source.rawBytes.size();
    return projectileRef(source,offset,end>=offset?end-offset:0,ordinal);
}
Json projectileDocument(const Script &source) {
    Json fields=Json::array();
    for(const auto &field:source.fields) fields.push_back({{"tag",field.tag},{"offset",field.offset},{"values",field.values}});
    return {{"path",source.path},{"source",source.source},{"raw_bytes",source.rawBytes},{"fields",fields},{"tokens",source.tokens}};
}
bool projectileInteger(const Json &value,int &out,bool allowNegative=false) {
    if(!value.is_number_integer() ||
       (value.is_number_unsigned() && value.get<uint64_t>()>uint64_t(std::numeric_limits<int>::max()))) return false;
    const auto n=value.get<int64_t>();
    if(n<(allowNegative?std::numeric_limits<int>::min():0) || n>std::numeric_limits<int>::max()) return false;
    out=int(n);return true;
}
std::optional<size_t> projectileField(MonsterProjectileDefinition &out,const Script &source,const std::string &tag,bool required=true) {
    std::vector<size_t> matches;
    for(size_t i=0;i<source.fields.size();++i) if(normalize(source.fields[i].tag)==tag) matches.push_back(i);
    if(matches.size()==1) return matches.front();
    if(required || matches.size()>1) projectileIssue(out,"missing_or_ambiguous_projectile_field",
        {{"path",source.path},{"tag",tag},{"ordinals",matches}});
    return std::nullopt;
}
std::string projectileBinding(MonsterProjectileDefinition &out,const Pvf &pvf,const Script &source,
                              const std::string &tag,int slot=0,bool required=true) {
    const auto ordinal=projectileField(out,source,tag,required);
    if(!ordinal) return {};
    const auto &values=source.fields[*ordinal].values;
    if(slot<0 || size_t(slot)>=values.size() || !values[size_t(slot)].is_string() ||
       values[size_t(slot)].get<std::string>().empty()) {
        projectileIssue(out,"invalid_projectile_resource_binding",{{"source",projectileFieldRef(source,*ordinal)},
            {"slot",slot},{"values",values}});return {};
    }
    // Only attack motion is an indexed MOB list. OBJ bindings are singular;
    // multiple ATKs/motions need a corresponding controller, not first-item use.
    if(tag!="[attack motion]" && values.size()!=1) {
        projectileIssue(out,"unsupported_projectile_resource_binding_count",{{"source",projectileFieldRef(source,*ordinal)},
            {"tag",tag},{"count",values.size()}});return {};
    }
    const auto path=normalize((std::filesystem::u8path(source.path).parent_path()/
        std::filesystem::u8path(values[size_t(slot)].get<std::string>())).lexically_normal().generic_u8string());
    out.trace.push_back({{"stage","projectile_resource_binding"},{"source",projectileFieldRef(source,*ordinal)},
        {"slot",slot},{"literal",values[size_t(slot)]},{"path",path}});
    if(!pvf.has(path)) projectileIssue(out,"missing_projectile_dependency",{{"path",path},{"source",projectileFieldRef(source,*ordinal)}});
    return path;
}
} // namespace

bool MonsterProjectileDefinition::usable() const {
    return !projectileErrors(diagnostics) && level>0 && projectileCount==1 && objectType==1 && power==0 &&
        attackNumber==1 && throwFrame>=0 && lifetimeMs>0 && std::isfinite(speed) && speed>0 &&
        std::isfinite(offsetX) && std::isfinite(offsetY) && std::isfinite(offsetZ) &&
        projectileMotion && !projectileMotion->frames.empty() && throwMotion && size_t(throwFrame)<throwMotion->frames.size() &&
        attack.usable() && !object.path.empty() && !motionParticle.path.empty();
}
Json MonsterProjectileDefinition::snapshot(bool full) const {
    Json result={{"schema",1},{"policy",policy},{"classification","inferred_beta"},{"usable",usable()},
        {"object_id",objectId},{"level",level},{"attack_variant",attackVariant},{"projectile_count",projectileCount},
        {"object_type",objectType},{"power",power},{"attack_number",attackNumber},{"throw_frame",throwFrame},
        {"offset",Json::array({offsetX,offsetY,offsetZ})},{"speed",speed},{"lifetime_ms",lifetimeMs},
        {"animation",animation},{"throw_animation",throwAnimation},{"throw_sound",throwSound},{"attack_path",attackPath},
        {"loop",loop},{"landing_type",landingType},{"width",width},{"floating_height",floatingHeight},
        {"piercing_power",piercingPower},{"layer",layer},{"pass_type",passType},{"attack",attack.snapshot(full)},
        {"sources",sources},{"trace",trace},{"diagnostics",diagnostics},
        {"capabilities",{{"launch_and_contact",usable()},{"destroy_particle_presentation",destroyParticle.path.empty()},
            {"native_pc_parity","pending"}}}};
    if(full) result["source_documents"]={{"monster",projectileDocument(monster)},{"registry",projectileDocument(registry)},
        {"object",projectileDocument(object)},{"motion_particle",projectileDocument(motionParticle)},
        {"destroy_particle",projectileDocument(destroyParticle)},
        {"projectile_animation_bytes",projectileAnimationBytes},{"throw_animation_bytes",throwAnimationBytes}};
    return result;
}

MonsterProjectileDefinition World::prepareMonsterProjectile(const Actor &actor) const {
    MonsterProjectileDefinition out;out.attackVariant=actor.attackVariant;
    try {
        if(actor.monsterPath.empty() || !pvf_.has(actor.monsterPath)) {
            projectileIssue(out,"missing_projectile_monster_source",{{"path",actor.monsterPath}});return out;
        }
        out.monster=pvf_.script(actor.monsterPath);out.sources["monster"]=projectileRef(out.monster);
        if(!actor.sourceStats.is_object() || !actor.sourceStats.contains("level") ||
           !projectileInteger(actor.sourceStats.at("level"),out.level) || out.level<1)
            projectileIssue(out,"missing_frozen_projectile_level",{{"reason","Projectile level belongs to the spawning monster receipt, never the current player"}});
        if(actor.combatAttributes && (!actor.combatAttributes->usable() || actor.combatAttributes->level!=out.level ||
           normalize(actor.combatAttributes->source.monster.path)!=out.monster.path ||
           actor.combatAttributes->source.monster.source.value("package_identity",std::string())!=pvf_.identity() ||
           sha256(actor.combatAttributes->source.monster.rawBytes)!=sha256(out.monster.rawBytes)))
            projectileIssue(out,"projectile_frozen_monster_source_mismatch");
        std::vector<size_t> matches;
        for(size_t ordinal=0;ordinal<out.monster.fields.size();++ordinal) {
            const auto &field=out.monster.fields[ordinal];
            if(normalize(field.tag)!="[throw attack]") continue;
            int index=-1;size_t count=0;
            for(size_t i=0;i+1<field.values.size();i+=2) if(field.values[i].is_string() &&
                normalize(field.values[i].get<std::string>())=="[attack index]") {
                ++count;if(!projectileInteger(field.values[i+1],index)) index=-1;
            }
            if(count==1 && index==actor.attackVariant) matches.push_back(ordinal);
        }
        if(matches.size()!=1) {
            projectileIssue(out,"missing_or_ambiguous_monster_throw_attack",{{"attack_variant",actor.attackVariant},
                {"matching_ordinals",matches},{"source",out.sources["monster"]}});return out;
        }
        const auto ordinal=matches.front();const auto &field=out.monster.fields[ordinal];
        out.sources["throw_attack"]=projectileFieldRef(out.monster,ordinal);
        if(ordinal+1>=out.monster.fields.size() || normalize(out.monster.fields[ordinal+1].tag)!="[/throw attack]" || field.values.size()%2) {
            projectileIssue(out,"malformed_monster_throw_attack_block",{{"source",out.sources["throw_attack"]}});return out;
        }
        const std::set<std::string> supported={"[attack index]","[passive object number]","[passive object filename]",
            "[object type]","[passive object index]","[power]","[throw frame]","[passive object start x cood]",
            "[passive object start y cood]","[passive object start z cood]","[attack number]","[throw sound]"};
        std::map<std::string,Json> values;
        for(size_t i=0;i<field.values.size();i+=2) {
            if(!field.values[i].is_string()) {
                projectileIssue(out,"malformed_monster_throw_key",{{"source",out.sources["throw_attack"]},{"value_index",i}});continue;
            }
            const auto key=normalize(field.values[i].get<std::string>());
            const auto ref=projectileRef(out.monster,field.offset+5+i*5,10,i/2);
            if(!supported.count(key)) projectileIssue(out,"unsupported_monster_throw_field",{{"tag",key},{"source",ref}});
            if(values.count(key)) projectileIssue(out,"duplicate_monster_throw_field",{{"tag",key},{"source",ref}});
            values[key]=field.values[i+1];
            out.trace.push_back({{"stage","monster_throw_operand"},{"tag",key},{"value",field.values[i+1]},{"source",ref}});
        }
        const auto integer=[&](const char *key,int &target,bool signedValue=false) {
            const auto found=values.find(key);
            if(found==values.end() || !projectileInteger(found->second,target,signedValue))
                projectileIssue(out,"invalid_monster_throw_integer",{{"tag",key},{"source",out.sources["throw_attack"]}});
        };
        integer("[passive object number]",out.projectileCount);integer("[object type]",out.objectType);
        integer("[passive object index]",out.objectId);integer("[power]",out.power);
        integer("[throw frame]",out.throwFrame);integer("[attack number]",out.attackNumber);
        int offsets[3]={};
        const char *offsetKeys[]={"[passive object start x cood]","[passive object start y cood]","[passive object start z cood]"};
        for(size_t i=0;i<3;++i) integer(offsetKeys[i],offsets[i],true);
        out.offsetX=offsets[0];out.offsetY=offsets[1];out.offsetZ=offsets[2];
        if(out.projectileCount!=1 || out.objectType!=1 || out.power!=0 || out.attackNumber!=1)
            projectileIssue(out,"unsupported_monster_throw_semantics",{{"projectile_count",out.projectileCount},
                {"object_type",out.objectType},{"magic_level_power",out.power},{"throws_per_attack",out.attackNumber},
                {"supported","one particle with one registered OBJ template, zero magic-level override and one throw"}});
        const auto sound=values.find("[throw sound]");
        if(sound==values.end() || !sound->second.is_string()) projectileIssue(out,"invalid_monster_throw_sound");
        else out.throwSound=sound->second.get<std::string>();
        const auto particle=values.find("[passive object filename]");
        if(particle==values.end() || !particle->second.is_string() || particle->second.get<std::string>().empty())
            projectileIssue(out,"invalid_monster_throw_particle_binding");
        if(projectileErrors(out.diagnostics)) return out;
        const auto particlePath=normalize((std::filesystem::u8path(out.monster.path).parent_path()/
            std::filesystem::u8path(particle->second.get<std::string>())).lexically_normal().generic_u8string());
        if(!pvf_.has(particlePath)) {projectileIssue(out,"missing_projectile_dependency",{{"path",particlePath}});return out;}
        out.motionParticle=pvf_.script(particlePath);out.sources["motion_particle"]=projectileRef(out.motionParticle);
        // This adapter handles the complete constant-X trajectory in its scope.
        // Extra axes, gravity, nonconstant endpoints or changing policies block.
        const std::set<std::string> motionTags={"[x axis]","[move type]","[move variable 1]","[life time]","[landing type]"};
        for(const auto &entry:out.motionParticle.fields) if(!motionTags.count(normalize(entry.tag)))
            projectileIssue(out,"unsupported_projectile_motion_field",{{"tag",entry.tag},{"path",particlePath},{"offset",entry.offset}});
        const auto axis=projectileField(out,out.motionParticle,"[x axis]");
        if(axis && !out.motionParticle.fields[*axis].values.empty()) projectileIssue(out,"invalid_projectile_motion_axis");
        const auto move=projectileField(out,out.motionParticle,"[move type]");
        if(move && out.motionParticle.fields[*move].values!=Json::array({"[straight line]"})) projectileIssue(out,"unsupported_projectile_move_type");
        const auto variable=projectileField(out,out.motionParticle,"[move variable 1]");
        int start=0,end=0;
        if(variable) {
            const auto &v=out.motionParticle.fields[*variable].values;
            if(v.size()!=2 || !projectileInteger(v[0],start) || !projectileInteger(v[1],end) || start<=0 || start!=end)
                projectileIssue(out,"unsupported_projectile_velocity_endpoints",{{"source",projectileFieldRef(out.motionParticle,*variable)},{"values",v}});
            else out.speed=start;
        }
        const auto life=projectileField(out,out.motionParticle,"[life time]");
        if(life) {
            const auto &v=out.motionParticle.fields[*life].values;
            if(v.size()!=1 || !projectileInteger(v[0],out.lifetimeMs) || out.lifetimeMs<=0) projectileIssue(out,"invalid_projectile_lifetime");
        }
        const auto landing=projectileField(out,out.motionParticle,"[landing type]");
        if(landing) {
            const auto &v=out.motionParticle.fields[*landing].values;
            if(v!=Json::array({"[vanish]"})) projectileIssue(out,"unsupported_projectile_landing_type");
            else out.landingType=v[0].get<std::string>();
        }
        out.registry=pvf_.script("passiveobject/passiveobject.lst");
        const auto &tokens=out.registry.tokens;std::vector<size_t> registrations;
        if(tokens.size()%2) projectileIssue(out,"malformed_projectile_object_registry");
        for(size_t i=0;i+1<tokens.size();i+=2) {
            int id=-1;
            if(tokens[i].at("type")==2 && projectileInteger(tokens[i].at("value"),id) && id==out.objectId) registrations.push_back(i);
        }
        if(registrations.size()!=1) {
            projectileIssue(out,"missing_or_ambiguous_projectile_object_registration",{{"object_id",out.objectId},{"token_indices",registrations}});return out;
        }
        const auto registration=registrations.front();const auto &name=tokens[registration+1];
        if(name.at("type")!=7 || !name.at("value").is_string() || name.at("value").get<std::string>().empty()) {
            projectileIssue(out,"invalid_projectile_object_registration",{{"token_index",registration}});return out;
        }
        const auto objectPath=normalize((std::filesystem::u8path(out.registry.path).parent_path()/
            std::filesystem::u8path(name.at("value").get<std::string>())).lexically_normal().generic_u8string());
        out.sources["object_registration"]=projectileRef(out.registry,tokens[registration].at("offset").get<size_t>(),10,registration/2);
        out.trace.push_back({{"stage","registered_projectile_object"},{"object_id",out.objectId},{"literal",name.at("value")},
            {"path",objectPath},{"source",out.sources["object_registration"]}});
        if(!pvf_.has(objectPath)) {projectileIssue(out,"missing_projectile_dependency",{{"path",objectPath}});return out;}
        out.object=pvf_.script(objectPath);out.sources["object"]=projectileRef(out.object);
        const std::set<std::string> objectTags={"[width]","[floating height]","[layer]","[pass type]","[piercing power]",
            "[basic motion]","[destroy particle]","[attack info]","[name]"};
        for(size_t i=0;i<out.object.fields.size();++i) if(!objectTags.count(normalize(out.object.fields[i].tag)))
            projectileIssue(out,"unsupported_projectile_object_field",{{"tag",out.object.fields[i].tag},{"source",projectileFieldRef(out.object,i)}});
        const auto width=projectileField(out,out.object,"[width]");
        if(width) {
            const auto &v=out.object.fields[*width].values;
            if(v.size()!=2 || !projectileInteger(v[0],out.width[0]) || !projectileInteger(v[1],out.width[1]) || !out.width[0] || !out.width[1])
                projectileIssue(out,"invalid_projectile_object_width");
        }
        const auto objectInteger=[&](const char *tag,int &target) {
            const auto i=projectileField(out,out.object,tag);
            if(i && (out.object.fields[*i].values.size()!=1 || !projectileInteger(out.object.fields[*i].values[0],target)))
                projectileIssue(out,"invalid_projectile_object_integer",{{"tag",tag},{"source",projectileFieldRef(out.object,*i)}});
        };
        objectInteger("[floating height]",out.floatingHeight);objectInteger("[piercing power]",out.piercingPower);
        if(out.piercingPower!=0) projectileIssue(out,"projectile_piercing_consumer_required",{{"piercing_power",out.piercingPower}});
        const auto objectEnum=[&](const char *tag,const char *supportedValue,std::string &target) {
            const auto i=projectileField(out,out.object,tag);
            if(i) {
                const auto &v=out.object.fields[*i].values;
                if(v!=Json::array({supportedValue})) projectileIssue(out,"unsupported_projectile_object_enum",{{"tag",tag},{"values",v}});
                else target=supportedValue;
            }
        };
        objectEnum("[layer]","[normal]",out.layer);objectEnum("[pass type]","[pass all]",out.passType);
        out.animation=projectileBinding(out,pvf_,out.object,"[basic motion]");
        out.attackPath=projectileBinding(out,pvf_,out.object,"[attack info]");
        out.throwAnimation=projectileBinding(out,pvf_,out.monster,"[attack motion]",actor.attackVariant);
        const auto destroy=projectileBinding(out,pvf_,out.object,"[destroy particle]",0,false);
        if(!destroy.empty() && pvf_.has(destroy)) {
            out.destroyParticle=pvf_.script(destroy);out.sources["destroy_particle"]=projectileRef(out.destroyParticle);
            projectileIssue(out,"projectile_destroy_particle_presentation_pending",{{"source",out.sources["destroy_particle"]},
                {"reason","Source retained; multi-particle creation, random rotation, gravity and fade need a presentation consumer"}},"warning");
        }
        if(projectileErrors(out.diagnostics)) return out;
        out.attack=readAttackDamage(pvf_.script(out.attackPath));
        if(!out.attack.usable()) projectileIssue(out,"unusable_projectile_attack",{{"path",out.attackPath},{"diagnostics",out.attack.diagnostics}});
        out.sources["attack"]=projectileRef(out.attack.source);
        out.projectileAnimationBytes=pvf_.read(out.animation);out.throwAnimationBytes=pvf_.read(out.throwAnimation);
        out.sources["animation"]=makeSourceRef(pvf_,out.animation,0,0,0,"monster_projectile_animation").json();
        out.sources["throw_animation"]=makeSourceRef(pvf_,out.throwAnimation,0,0,0,"monster_projectile_throw_animation").json();
        out.projectileMotion=assets_.animation(out.animation);out.throwMotion=assets_.animation(out.throwAnimation);
        out.loop=out.projectileMotion->globals.value("0",false);
        if(out.projectileMotion->frames.empty() || out.throwFrame<0 || size_t(out.throwFrame)>=out.throwMotion->frames.size())
            projectileIssue(out,"invalid_projectile_animation_or_throw_frame",{{"throw_frame",out.throwFrame}});
        bool attackBox=false;
        for(const auto &frame:out.projectileMotion->frames) for(const auto &box:frame.boxes) if(box.type==15) {
            attackBox=true;
            if(box.w<=0 || box.h<=0 || box.d<=0) projectileIssue(out,"invalid_projectile_source_attack_box");
        }
        if(!attackBox) projectileIssue(out,"missing_projectile_source_attack_box");
        out.trace.push_back({{"stage","projectile_beta_policy"},{"policy",out.policy},{"classification","inferred_beta"},
            {"annotated_sample",{{"path","pvf官方文档/sample(官方注释)/monstersample.mob"},{"encoding","CP949"},
                {"sha256","e3af213de4ac47b2bce3e8cc9d722fd8dc01b68006e4afe6a5ced88e7f22be0f"},{"lines",Json::array({221,222,223,224,225,226,227,228,229,230,231,232,233,234,235})}}},
            {"basis",Json::array({"Current MOB carries a PTL plus registered OBJ index; OBJ binds ANI and ATK",
                "Annotated monstersample.mob lines221-235 distinguish particle type1 from passive-object type0",
                "PTL constant X endpoints are interpreted as facing-relative world units per second; life time is milliseconds"})},
            {"source_level",out.level},{"power_semantics","annotated magic level; only explicit zero supported"},
            {"throw_count_semantics","attack number is throws per attack, separate from particle filename count"},
            {"unverified_conditions",Json::array({"Original PC particle/object dispatch and final PTL modifiers",
                "AI distance/selection/attack-clock calibration","Destroy-particle presentation"})},
            {"impact","Source launch timing/offset/speed/lifetime and OBJ ANI/ATK drive beta contact; original-client parity remains pending"}});
    } catch(const std::exception &error) {
        projectileIssue(out,"projectile_source_preparation_failed",{{"message",error.what()},{"monster",actor.monsterPath}});
    }
    return out;
}

std::string World::monsterAttackPath(const Actor &actor) const {
    if(actor.monsterPath.empty()) throw std::runtime_error("Monster attack needs an explicit source MOB");
    const auto source=pvf_.script(actor.monsterPath);
    const Field *binding=nullptr;
    for(const auto &field:source.fields) if(normalize(field.tag)=="[attack info]") {
        if(binding) throw std::runtime_error("Monster attack has ambiguous attack-info bindings: "+actor.monsterPath);
        binding=&field;
    }
    if(!binding) throw std::runtime_error("Monster attack needs an ordered attack-info binding: "+actor.monsterPath);
    const auto &values=binding->values;
    const int slot=actor.attackVariant;
    if(slot<0 || size_t(slot)>=values.size() || !values[slot].is_string() || values[slot].get<std::string>().empty())
        throw std::runtime_error("Monster attack-info slot is absent: "+actor.monsterPath+":"+std::to_string(slot));
    const auto path=normalize((std::filesystem::path(actor.monsterPath).parent_path()/
        values[slot].get<std::string>()).generic_string());
    if(!pvf_.has(path)) throw std::runtime_error("Monster attack-info source is missing: "+path);
    return path;
}
DamageSkillModifiers World::damageSkillModifiers(int id,int phase) const {
    DamageSkillModifiers out;
    const Skill *skill=nullptr;
    for(const auto &entry:skills) if(entry.id==id) skill=&entry;
    if(skill) {
        const auto p=[&](int col){ return float(skill->parameter(col)); };
        out.replacesAttackCoefficients=true;
        switch(id) {
        case 46: out.percent=p(0);out.fixedDamage=p(3);break;
        case 5: out.percent=p(0);out.fixedDamage=p(1);break;
        case 8: out.percent=p(phase==2?1:0);out.fixedDamage=p(phase==2?4:3);break;
        case 11: out.percent=p(0);out.fixedDamage=p(2);break;
        case 16: case 17: case 65: out.percent=p(0);break;
        case 20: out.percent=p(2);out.fixedDamage=p(0);break;
        case 58: out.percent=p(std::min(phase,2));out.fixedDamage=phase==2?p(3):0;break;
        case 64: out.percent=p(phase?1:0);out.fixedDamage=phase?p(7):0;break;
        case 77: out.percent=p(std::min(phase,1));out.fixedDamage=p(phase?4:3);break;
        default: throw std::runtime_error("Skill damage column consumer is unavailable: "+std::to_string(id));
        }
        out.sources.push_back({{"classification","inferred_controller_skl_columns"},{"key",skill->identity().json()},
            {"path",skill->source},{"level",skill->level},{"phase",phase},
            {"source",skill->sourceData?skill->sourceData->definition.source.provenance:Json()},
            {"basis","Existing separately mapped Swordman controller level-info columns and level-property units"},
            {"unverified_conditions","Original PC setters, stage coefficient replacement and independent attack scaling remain unverified"},
            {"impact","Changes outgoing damage; does not establish original-client numerical parity"}});
    }
    const auto attack=readAttackDamage(pvf_.script(attackResponse(id,phase).source));
    const bool magic=attack.type==DamageAttackType::Magical;
    const int magicColumn[]={8,9,10,9};
    const auto mastery=effectivePassive(passives.at(1+weapon%4));
    out.attackMultiplier=1+float(mastery.parameter(magic?magicColumn[weapon%4]:0))/1000;
    out.sources.push_back({{"consumer","weapon_mastery"},{"key",mastery.identity().json()},{"level",mastery.level},
        {"source",mastery.source},{"classification","inferred_controller_column"}});
    for(const auto &effect:effects) if(effect.skill==25 && effect.phase=="khazan:stay" && nowMs()>=effect.born &&
        nowMs()<effect.expires && !effect.attached && std::abs(player.x-effect.x)<125 && std::abs(player.y-effect.y)<80)
        out.primaryStatBonus=std::max(out.primaryStatBonus,float(skills.at(7).parameter(magic?2:0)));
    if(id==0) {
        Skill basic=effectivePassive(passives.at(0));
        if(basic.level>0) {
            basic.level=std::max(1,characterLevel);
            const int col=player.animation=="dashattack"?1:player.animation=="jumpattack"?2:0;
            out.totalMultiplier=1+float(basic.parameter(col))/1000;
        }
        out.sources.push_back({{"consumer","basic_training"},{"key",basic.identity().json()},
            {"effective_level",basic.level},{"classification","inferred_controller_column"}});
    }
    return out;
}
} // namespace dnf
