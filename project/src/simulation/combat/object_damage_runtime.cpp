#include "dnf/combat.hpp"
#include "dnf/objects.hpp"
#include "dnf/female_gunner_world.hpp"
#include <cmath>
#include <set>

namespace dnf {
namespace {
uint64_t objectDamageIdentity(const ObjectIdentity &identity) {
    uint64_t result=1469598103934665603ull;
    for (const auto c:identity.key()) result=(result^static_cast<unsigned char>(c))*1099511628211ull;
    return result?result:1;
}
DamageCombatant objectDamageTarget(const ObjectInstance &object) {
    DamageCombatant out;
    out.adapter="inferred-explicit-hp-object-target-v1";
    out.level=1;
    const auto &definition=*object.definition;
    const auto &source=definition.script;
    out.packageIdentity=source.source.value("package_identity",std::string());
    out.sources={{"object_identity",object.placement.identity.json()},{"path",source.path},
                 {"member_sha256",sha256(source.rawBytes)},{"provenance",source.source}};
    bindDamageTargetCategory(out,source,DamageTargetCategory::Fort);
    auto issue=[&](const char *kind,Json detail=Json::object()) {
        detail["kind"]=kind;detail["severity"]="error";out.diagnostics.push_back(std::move(detail));
    };
    if (!definition.explicitHpMax || *definition.explicitHpMax<=0 || !object.durability)
        issue("object_explicit_hp_consumer_required");
    if (source.source.value("member_sha256",std::string())!=sha256(source.rawBytes))
        issue("object_damage_source_hash_mismatch");
    size_t hpCount=0,levelCount=0;bool insideCategory=false;
    for (const auto &field:source.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[category]"){insideCategory=true;continue;}
        if(tag=="[/category]"){insideCategory=false;continue;}
        if(insideCategory)continue;
        if (tag=="[hp max]") {
            ++hpCount;
            if (field.values.size()!=1 || !field.values[0].is_number_integer() ||
                !definition.explicitHpMax || field.values[0]!=*definition.explicitHpMax)
                issue("invalid_object_damage_hp_source",{{"offset",field.offset},{"values",field.values}});
        }
        if (tag=="[level]") {
            ++levelCount;
            if (field.values.size()!=1 || !field.values[0].is_number_integer() ||
                field.values[0].get<int64_t>()<1 || field.values[0].get<int64_t>()>99)
                issue("invalid_object_damage_level",{{"offset",field.offset},{"values",field.values}});
            else out.level=field.values[0].get<int>();
        }
        if (tag.find("defen")!=std::string::npos || tag.find("resist")!=std::string::npos ||
            tag.find("armor")!=std::string::npos || tag.find("evasion")!=std::string::npos ||
            tag.find("ability")!=std::string::npos || tag.find("active status")!=std::string::npos)
            issue("object_damage_modifier_consumer_required",{{"tag",tag},{"offset",field.offset},{"values",field.values}});
    }
    if (hpCount!=1 || levelCount>1) issue("ambiguous_object_damage_source",{{"hp_count",hpCount},{"level_count",levelCount}});
    out.trace.push_back({{"policy",out.adapter},{"classification","inferred"},
        {"basis","passiveobjectsample.obj lines 4-16 explicitly define HP but no general defense/primary-stat growth contract"},
        {"unverified_conditions","Original passive-object defense and attacker/target correction chain unrecovered; missing armor class uses explicit fort inference"},
        {"impact","Use shared damage resolution with explicit neutral defense/evasion/resistance; unknown authored modifiers block"},
        {"default_level",1},{"level_from_source",levelCount==1},{"physical_defense",0},{"magical_defense",0}});
    return out;
}
}

DamageResolution World::resolveObjectContact(const AttackVolume &volume,const ObjectInstance &object) {
    DamageResolution unavailable;
    unavailable.policy="inferred-explicit-hp-object-target-v1";
    if (!usesSourceGrowth() || !combatAttributes_ || !object.definition || !volume.serial) {
        unavailable.diagnostics.push_back({{"kind","source_object_damage_inputs_required"},{"severity","error"}});
        return unavailable;
    }
    const auto policy=DamageResolutionPolicy::inferredPveDamageV1(combatAttributes_->damageConstants);
    DamageRequest request;
    request.attacker=player.handle;
    // Objects retain their complete persistent ObjectIdentity in target sources.
    // This numerical identity is never passed to World::resolveActor.
    request.target={objectDamageIdentity(object.placement.identity),1};
    request.attackInstance=volume.serial;
    if (volume.pulse>UINT32_MAX) {
        unavailable.diagnostics.push_back({{"kind","object_damage_pulse_out_of_range"},{"severity","error"}});
        return unavailable;
    }
    request.hitIndex=uint32_t(volume.pulse);
    request.attackerStats=makeDamageCombatant(*combatAttributes_);
    request.targetStats=objectDamageTarget(object);
    if (!volume.sourceAttack || !volume.sourceModifiers) {
        unavailable.diagnostics.push_back({{"kind","source_object_attack_receipt_required"},{"severity","error"}});
        return unavailable;
    }
    request.attack=*volume.sourceAttack;
    request.skill=*volume.sourceModifiers;
    if(request.targetStats.targetCategory==DamageTargetCategory::Fort&&volume.sourceFortModifiers)
        request.skill=*volume.sourceFortModifiers;
    request.weaponType=volume.sourceWeaponType;
    if(femaleGunnerWorld_ && identity_.jobId==5)
        femaleGunnerWorld_->applyAttack(request,volume.skillId?std::optional<SkillKey>(SkillKey{5,volume.skillId}):std::nullopt,
            volume.sourceMotionTag,volume.sourceAttackFamily);
    auto candidateRandom=random_;
    auto result=resolveDamage(request,policy,&candidateRandom.stream(RandomDomain::Combat,request.attackInstance));
    if(result.usable())random_=std::move(candidateRandom);
    lastDamageTrace_=result.snapshot();
    return result;
}
} // namespace dnf
