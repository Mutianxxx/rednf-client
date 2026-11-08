#include "dnf/damage_resolution.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
void damageSpans(Script &script) {
    size_t offset=2;
    for (auto &field:script.fields) { field.offset=offset; offset+=5*(1+field.values.size()); }
    script.rawBytes.assign(offset,0);
}
Script damageScript(const std::string &path) {
    Script s; s.path=path; s.source={{"package_identity","damage-fixture-package"},{"literal_path",path}}; return s;
}
Script damageConstants() {
    auto s=damageScript("etc/etcparameter.etc");
    s.fields={{"[damage fomula constant]",Json::array({250,10000,200,10000,3,0.28f,250,10000,200,10000,3,0.28f,
        105,0.45f,0.3f,0.3f,250,0,250,0,2,4,5,5,0.004f,0.004f,0.01f}),0}};
    damageSpans(s); return s;
}
Script damageAttack(const std::string &type="[physic]",int base=0,float bonus=0,int absolute=0) {
    auto s=damageScript("attackinfo/fixture.atk");
    s.fields={{"[damage]",Json::array({base}),0},{"[absolute damage]",Json::array({absolute}),0},
        {"[damage bonus]",Json::array({bonus}),0},{"[attack type]",Json::array(),0},{type,Json::array(),0},
        {"[weapon damage apply]",Json::array({1}),0},{"[elemental property]",Json::array(),0},{"[no element]",Json::array(),0},
        {"[damage reaction]",Json::array(),0},{"[damage]",Json::array(),0}};
    s.tokens.push_back({{"raw_fixture",true}}); damageSpans(s); return s;
}
DamageCombatant damageActor(int level=5) {
    DamageCombatant actor; actor.packageIdentity="damage-fixture-package"; actor.adapter="explicit-test-input"; actor.level=level; return actor;
}
DamageRequest damageRequest() {
    DamageRequest q; q.attacker={1,1}; q.target={2,1}; q.attackInstance=19;
    q.attackerStats=damageActor(); q.targetStats=damageActor(); q.attack=readAttackDamage(damageAttack()); return q;
}
bool damageIssue(const Json &issues,const std::string &kind) {
    for (const auto &entry:issues) if (entry.value("kind",std::string())==kind) return true; return false;
}
const Json *damageStage(const DamageResolution &r,const std::string &stage) {
    for (const auto &entry:r.trace) if (entry.value("stage",std::string())==stage) return &entry; return nullptr;
}
} // namespace

Json runDamageResolutionTests(Pvf &pvf,Assets &) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *message) {
        if (!okay) throw std::runtime_error(std::string("Damage resolution: ")+message); checks.push_back(message);
    };
    auto policy=DamageResolutionPolicy::inferredPveDamageV1(damageConstants());
    policy.rollHit=false; policy.rollCritical=false; policy.randomVariation=false;
    auto q=damageRequest();
    const auto atk=readAttackDamage(damageAttack("[physic]",10,20,30));
    check(atk.usable() && atk.type==DamageAttackType::Physical && atk.baseDamage==10 && atk.absoluteDamage==30 && atk.bonusPercent==20 && atk.weaponDamageApply,
        "ATK enum fields preserve physical type, numeric base, additive percentage and absolute damage");
    check(atk.source.fields.back().tag=="[damage]" && atk.source.fields.back().values.empty() && atk.source.fields[0].values==Json::array({10}),
        "Reaction [damage] is consumed as an enum and never shadows numeric base damage");
    check(atk.snapshot(true)["source"]["ordered_tokens"]==atk.source.tokens &&
        atk.snapshot(true)["source"]["raw_bytes_hex"].get<std::string>().size()==atk.source.rawBytes.size()*2,
        "ATK raw bytes, ordered tokens, repeated tags and source spans remain available for export");
    check(!resolveDamage(q).usable(),"Disabled default policy cannot publish inferred damage");
    check(!resolveDamage(q,DamageResolutionPolicy::inferredPveDamageV1(damageConstants())).usable(),
        "Stochastic resolution requires an explicit owned combat random stream");
    q.attack=atk; q.attackerStats.physicalAttack=100; q.attackerStats.strength=250;
    q.targetStats.physicalDefense=1000; q.targetStats.physicalAbsoluteDefensePercent=25;
    const auto physical=resolveDamage(q,policy);
    check(physical.hpDamage==126 && !physical.critical && !physical.missed,
        "Physical damage combines source ATK, equipment attack, STR, target ratio defense and post-defense absolute damage");
    check(damageStage(physical,"target_defense") && (*damageStage(physical,"target_defense"))["attacker_basis_level"]==5 &&
        (*damageStage(physical,"target_defense"))["rate"]==0.5f,
        "Per-target defense uses attacker basis level and retains its denominator and rate trace");
    auto other=q; other.target={3,7}; other.targetStats.physicalDefense=0;
    const auto unarmored=resolveDamage(other,policy);
    check(unarmored.hpDamage==225 && physical.hpDamage!=unarmored.hpDamage && unarmored.target==EntityHandle{3,7},
        "One attack instance resolves each target's own defense without cached attacker-only damage");
    other=q; other.targetStats.level=99;
    check(resolveDamage(other,policy).hpDamage==physical.hpDamage,
        "Defender level does not silently replace the source defense function's attacker basis level");
    auto magic=q; magic.attack=readAttackDamage(damageAttack("[magic]",10,0,0));
    magic.attackerStats.magicalAttack=50; magic.attackerStats.intelligence=750;
    magic.targetStats.magicalDefense=0; magic.targetStats.magicalAbsoluteDefensePercent=0;
    check(resolveDamage(magic,policy).hpDamage==240,"Magical damage consumes magical equipment attack and INT rather than physical attack and STR");
    auto ignore=q; ignore.attack=readAttackDamage(damageAttack("[ignore defense]",10,0,0));
    ignore.targetStats.physicalAbsoluteDefensePercent=0;
    check(resolveDamage(ignore,policy).hpDamage==110,
        "Ignore-defense attack type uses physical weapon attack, bypasses ratio defense and skips physical primary amplification");
    auto noWeapon=q; auto noWeaponSource=damageAttack("[physic]",10,0,0); noWeaponSource.fields[5].values=Json::array({0});
    damageSpans(noWeaponSource); noWeapon.attack=readAttackDamage(noWeaponSource); noWeapon.targetStats.physicalAbsoluteDefensePercent=0;
    check(resolveDamage(noWeapon,policy).hpDamage==10,"Weapon-application zero excludes equipment attack while retaining authored base damage and STR");
    auto missingWeapon=damageAttack("[physic]",10,0,0); missingWeapon.fields.erase(missingWeapon.fields.begin()+5); damageSpans(missingWeapon);
    check(readAttackDamage(missingWeapon).usable() && !readAttackDamage(missingWeapon).weaponDamageApply,
        "Absent weapon application uses the sample's explicit false default");
    auto noPower=damageRequest();
    check(resolveDamage(noPower,policy).hpDamage==1,"An unarmed zero-power contact uses the documented final floor without inventing training weapon power");
    auto skill=damageRequest(); skill.attackerStats.physicalAttack=100; skill.attackerStats.strength=250;
    skill.attack=readAttackDamage(damageAttack("[physic]",900,100,0));
    skill.skill.percent=200; skill.skill.fixedDamage=10; skill.skill.replacesAttackCoefficients=true;
    check(resolveDamage(skill,policy).hpDamage==420 && (*damageStage(resolveDamage(skill,policy),"attack_and_skill"))["effective_bonus_factor"]==1,
        "Controller replacement consumes skill percentage and fixed damage once and records the authored ATK values it superseded");
    skill.skill.replacesAttackCoefficients=false;
    check(resolveDamage(skill,policy).hpDamage==8040,"Explicit composition preserves both the ATK and controller multiplier when selected");
    skill=damageRequest(); skill.attackerStats.physicalAttack=100; skill.attackerStats.independentAttack=20; skill.attackerStats.independentRate=1.5f;
    skill.skill.fixedDamage=10; skill.skill.independentPercent=50;
    check(resolveDamage(skill,policy).hpDamage==130,"Fixed source points and explicit independent attack percentage form their own rate group");
    skill.skill.independentPercent=0;
    check(resolveDamage(skill,policy).hpDamage==115,"Equipment independent attack is not added without a controller-defined independent percentage");
    auto fire=damageRequest(); fire.attackerStats.physicalAttack=100; fire.attackerStats.weaponElement=0;
    fire.attackerStats.elementalAttack[0]=100; fire.targetStats.elementalResistance[0]=0;
    check(resolveDamage(fire,policy).hpDamage==150,"Source elemental base105 and rate0.45 apply once to the inherited effective weapon element");
    fire.targetStats.elementalResistance[0]=100;
    check(resolveDamage(fire,policy).hpDamage==104,
        "Equal element attack and resistance preserve the single binary32 baseline and its explicit truncation boundary");
    const auto elemental=resolveDamage(fire,policy);
    check((*damageStage(elemental,"element"))["factor"]==1.05f,
        "The trace exposes elemental baseline rounding rather than multiplying by another hidden 1.05");
    auto crit=q; auto critPolicy=policy; critPolicy.rollCritical=true; critPolicy.baseCriticalPercent=100;
    Pcg32 critRandom(13,9); const auto critical=resolveDamage(crit,critPolicy,&critRandom);
    check(critical.hpDamage==189 && critical.critical && critRandom.draws()>0,
        "Guaranteed critical uses the explicit 1.5 factor after absolute defense and commits its random roll");
    crit.skill.criticalMultiplier=2;Pcg32 criticalBuffRandom(13,9);
    const auto criticalBuffed=resolveDamage(crit,critPolicy,&criticalBuffRandom);
    check(criticalBuffed.critical&&criticalBuffed.hpDamage==378,
        "A skill critical-damage buff consumes only after a real successful critical roll");
    const auto criticalBuffNormal=resolveDamage(crit,policy);
    check(!criticalBuffNormal.critical&&criticalBuffNormal.hpDamage==126,
        "The same critical-damage buff leaves a normal contact unchanged");
    crit.skill.criticalMultiplier=-1;Pcg32 invalidCriticalRandom(13,9);const auto invalidCriticalBefore=invalidCriticalRandom.snapshot();
    check(!resolveDamage(crit,critPolicy,&invalidCriticalRandom).usable()&&invalidCriticalRandom.snapshot()==invalidCriticalBefore,
        "An invalid critical-damage multiplier fails before RNG publication");
    auto miss=q; miss.attackerStats.attackMissDeltaPercent=100; auto missPolicy=policy; missPolicy.rollHit=true;
    Pcg32 missRandom(8,7); const auto missed=resolveDamage(miss,missPolicy,&missRandom);
    check(missed.hpDamage==0 && missed.missed && !missed.critical && missRandom.draws()>0 && !damageStage(missed,"attack_and_skill"),
        "An accepted miss publishes zero damage, commits only the hit roll and skips downstream damage work");
    auto randomPolicy=policy; randomPolicy.randomVariation=true; randomPolicy.rollHit=true; randomPolicy.rollCritical=true;
    Pcg32 sequence(23,11); const auto checkpoint=sequence.snapshot(); const auto randomA=resolveDamage(q,randomPolicy,&sequence);
    Pcg32 replay; replay.restore(checkpoint); const auto randomB=resolveDamage(q,randomPolicy,&replay);
    check(randomA.snapshot()==randomB.snapshot() && sequence.snapshot()==replay.snapshot(),
        "Combat random checkpoints replay the same target result and stream receipt deterministically");
    Pcg32 exhausted; auto exhaustedState=exhausted.snapshot(); exhaustedState["draws"]=uint64_t(UINT64_MAX); exhausted.restore(exhaustedState);
    const auto exhaustedResult=resolveDamage(q,randomPolicy,&exhausted);
    check(!exhaustedResult.usable() && damageIssue(exhaustedResult.diagnostics,"damage_random_stream_exhausted") && exhausted.snapshot()==exhaustedState,
        "An exhausted random counter produces a diagnostic and preserves its checkpoint instead of escaping into World");
    auto invalid=q; invalid.target.generation=0;
    Pcg32 atomic(31,17); const auto atomicBefore=atomic.snapshot();
    check(!resolveDamage(invalid,randomPolicy,&atomic).usable() && atomic.snapshot()==atomicBefore,
        "Invalid entity generations cannot consume random state or publish damage");
    invalid=q; invalid.targetStats.packageIdentity="other-package";
    check(!resolveDamage(invalid,randomPolicy,&atomic).usable() && atomic.snapshot()==atomicBefore,
        "Mixed source packages fail before random consumption");
    invalid=q; invalid.skill.totalMultiplier=std::numeric_limits<float>::max();
    const auto overflow=resolveDamage(invalid,randomPolicy,&atomic);
    check(!overflow.usable() && damageIssue(overflow.diagnostics,"damage_arithmetic_overflow") && atomic.snapshot()==atomicBefore,
        "Arithmetic failure after staged random draws preserves the caller's stream atomically");
    invalid=q; invalid.skill.percent=-1;
    check(!resolveDamage(invalid,policy).usable(),"Negative skill damage coefficients cannot enter the arithmetic chain");
    invalid=q; invalid.attackerStats.strength=std::numeric_limits<float>::infinity();
    check(!resolveDamage(invalid,policy).usable(),"Non-finite combatant attributes cannot become successful minimum damage");
    auto badConstants=policy; badConstants.damageConstants.fields[0].values[0]=0;
    check(!resolveDamage(q,badConstants).usable(),"Zero stat divisors fail with source-specific constant diagnostics");
    badConstants=policy; badConstants.damageConstants.fields[0].values.push_back(0); damageSpans(badConstants.damageConstants);
    check(!resolveDamage(q,badConstants).usable(),"A changed constant field arity cannot silently select the prior positional layout");
    badConstants=policy; badConstants.damageConstants.source["member_sha256"]="tampered";
    check(!resolveDamage(q,badConstants).usable(),"Source member hash mismatch blocks constant use");
    auto source=damageAttack(); source.fields.push_back({"[pvp]",Json::array(),0});
    source.fields.push_back({"[damage bonus]",Json::array({-99}),0}); source.fields.push_back({"[/pvp]",Json::array(),0}); damageSpans(source);
    check(readAttackDamage(source).usable() && readAttackDamage(source).bonusPercent==0,
        "PvP overrides remain preserved and cannot leak into dungeon damage selection");
    source.fields.pop_back(); damageSpans(source);
    check(!readAttackDamage(source).usable(),"Unclosed PvP scope is diagnosed instead of truncating the source selection");
    source=damageAttack(); source.fields.push_back({"[damage bonus]",Json::array({7}),0}); damageSpans(source);
    check(!readAttackDamage(source).usable(),"Repeated dungeon bonus operands remain ambiguous rather than selecting the first");
    source=damageAttack(); source.fields[0].values=Json::array({1.25f}); damageSpans(source);
    check(!readAttackDamage(source).usable(),"ATK integer base damage retains its source type contract");
    source=damageAttack(); source.fields[3].values=Json::array({"[magic]"}); source.fields.erase(source.fields.begin()+4); damageSpans(source);
    check(readAttackDamage(source).usable() && readAttackDamage(source).type==DamageAttackType::Magical,
        "Inline enum operands and separate enum tokens have equivalent typed meaning");
    source=damageAttack("[weapon]"); auto weapon=q; weapon.attack=readAttackDamage(source);
    check(!resolveDamage(weapon,policy).usable(),"ATK weapon type requires a qualified controller weapon-type input");
    weapon.weaponType=DamageAttackType::Physical;
    check(resolveDamage(weapon,policy).usable(),"A qualified physical weapon type resolves the source weapon enum");
    source=damageAttack(); source.fields.push_back({"[active status]",Json::array(),0}); source.fields.push_back({"[poison]",Json::array({100,10,1000,10}),0}); damageSpans(source);
    check(!readAttackDamage(source).usable() && damageIssue(readAttackDamage(source).diagnostics,"attack_status_consumer_required"),
        "A material status payload requires its real consumer instead of disappearing from a successful attack");
    source=damageAttack(); source.fields.push_back({"[monster damage rate]",Json::array({80}),0}); damageSpans(source);
    check(readAttackDamage(source).usable() && readAttackDamage(source).targetCategoryPercent[2]==80,
        "Source target-category percentages have a typed consumer and retain their nonneutral authored value");
    auto categoryRequest=damageRequest();categoryRequest.attack=readAttackDamage(source);
    categoryRequest.attackerStats.physicalAttack=100;categoryRequest.targetStats.targetCategory=DamageTargetCategory::Monster;
    check(resolveDamage(categoryRequest,policy).hpDamage==80,
        "The source monster percentage changes actual resolved HP damage for an explicitly classified monster");
    source.fields.back().values=Json::array({100});
    check(readAttackDamage(source).usable(),"A source-authored neutral category percentage is explicitly harmless");
    {
        auto classified=damageAttack();
        classified.fields.push_back({"[human damage rate]",Json::array({80.0}),0});
        classified.fields.push_back({"[fort damage rate]",Json::array({125.0}),0});
        classified.fields.push_back({"[monster damage rate]",Json::array({50.0}),0});damageSpans(classified);
        auto request=damageRequest();request.attack=readAttackDamage(classified);request.attackerStats.physicalAttack=100;
        for(const auto category:{DamageTargetCategory::Human,DamageTargetCategory::Fort,DamageTargetCategory::Monster}) {
            request.targetStats.targetCategory=category;
            const auto result=resolveDamage(request,policy);const int expected=category==DamageTargetCategory::Human?80:category==DamageTargetCategory::Fort?125:50;
            check(result.hpDamage==expected && damageStage(result,"target_category_rate") &&
                  damageStage(result,"target_category_rate")->at("target_category")==damageTargetCategoryName(category),
                "Each target category consumes only its own original percentage and reports the selected multiplier");
        }
        request.targetStats.targetCategory=DamageTargetCategory::Unknown;Pcg32 rejectedRandom(19,13);const auto unchanged=rejectedRandom.snapshot();
        check(!resolveDamage(request,randomPolicy,&rejectedRandom).usable() && rejectedRandom.snapshot()==unchanged,
            "Unknown target category blocks nonneutral category multipliers before any random publication");
        for(const auto &traits:std::vector<Json>{Json::array({"[human]","[goblin]"}),Json::array({"[human armor]"}),
            Json::array({"[fort armor]"}),Json::array({"[divine armor]"}),Json::array({"[future armor]"}),
            Json::array({"[fort armor]","[human armor]"})}) {
            auto mobSource=damageScript("monster/category-fixture.mob");
            mobSource.fields={{"[category]",traits,0},{"[/category]",Json::array(),0}};damageSpans(mobSource);
            auto target=damageActor();bindDamageTargetCategory(target,mobSource,DamageTargetCategory::Monster);
            const auto first=traits.front().get<std::string>();const auto expected=traits.size()>1 && first=="[fort armor]"?DamageTargetCategory::Unknown:
                first=="[human armor]"?DamageTargetCategory::Human:first=="[fort armor]"?DamageTargetCategory::Fort:
                first=="[human]"?DamageTargetCategory::Monster:DamageTargetCategory::Unknown;
            check(target.targetCategory==expected && target.trace.back().at("categories")==traits,
                "Source armor classification preserves species separately and refuses divine, unknown or conflicting armor guesses");
        }
        auto splitSource=damageScript("monster/split-category-fixture.mob");
        splitSource.fields={{"[category]",Json::array(),0},{"[fort armor]",Json::array(),0},{"[/category]",Json::array(),0}};damageSpans(splitSource);
        auto splitTarget=damageActor();bindDamageTargetCategory(splitTarget,splitSource,DamageTargetCategory::Monster);
        check(splitTarget.targetCategory==DamageTargetCategory::Fort && splitTarget.trace.back().at("sources").size()==3,
            "Separate category type tokens retain all source spans and select the same fort consumer as inline strings");
        classified.fields[classified.fields.size()-2].values=Json::array({0});damageSpans(classified);
        request.attack=readAttackDamage(classified);request.targetStats.targetCategory=DamageTargetCategory::Fort;
        const auto zero=resolveDamage(request,policy);
        check(zero.usable() && zero.hpDamage==0 && !zero.missed,
            "Authored zero category percentage produces accepted zero HP damage instead of being replaced by minimum one");
        classified.fields.back().values=Json::array({-1});damageSpans(classified);
        check(!readAttackDamage(classified).usable(),"Negative target-category percentages remain invalid source operands");
        classified.fields.back().values=Json::array({100,125});damageSpans(classified);
        check(!readAttackDamage(classified).usable(),"A malformed category percentage cannot be truncated to its first operand");
    }
    source=damageAttack(); source.fields.push_back({"[unknown damage rule]",Json::array({0}),0}); damageSpans(source);
    check(!readAttackDamage(source).usable(),"Unknown material damage semantics cannot bypass the gate by using a zero-looking value");
    auto alternate=policy; alternate.damageConstants.fields[0].values[0]=500;
    check(resolveDamage(q,alternate).hpDamage==101,"The stat divisor comes from the selected source candidate rather than a hidden literal250");
    auto extreme=damageRequest(); extreme.attackerStats.physicalAttack=100; extreme.targetStats.physicalDefense=1.0e20f;
    check(resolveDamage(extreme,policy).hpDamage==1 && (*damageStage(resolveDamage(extreme,policy),"target_defense"))["multiplier"]==0.01f,
        "Extreme finite ratio defense retains the explicit minimum multiplier before final truncation");

    const auto actualPolicy=DamageResolutionPolicy::inferredPveDamageV1(pvf.script("etc/etcparameter.etc"));
    {
        auto deterministic=actualPolicy;deterministic.rollHit=false;deterministic.rollCritical=false;deterministic.randomVariation=false;
        for(const auto *path:{"passiveobject/character/gunner/attackinfo/rx78explosion.atk",
                             "passiveobject/character/gunner/attackinfo/rx78explosionex.atk"}) {
            const auto original=pvf.script(path);const auto attack=readAttackDamage(original);
            check(attack.usable() && attack.targetCategoryPercent[1]==125 && attack.source.rawBytes==pvf.read(path) &&
                  attack.source.tokens==original.tokens,"Actual RX78/EX ATK retains its original fort125 operand, bytes, tokens and typed damage definition");
            DamageRequest request;request.attacker={1,1};request.target={2,1};request.attackInstance=71;request.attack=attack;
            for(auto *actor:{&request.attackerStats,&request.targetStats}) {
                actor->packageIdentity=pvf.identity();actor->adapter="explicit-source-category-test";actor->level=20;
            }
            request.attackerStats.physicalAttack=request.attackerStats.magicalAttack=100;
            request.targetStats.targetCategory=DamageTargetCategory::Monster;const auto ordinary=resolveDamage(request,deterministic);
            bindDamageTargetCategory(request.targetStats,pvf.script("monster/gunner/robot/hphealrx78.mob"),DamageTargetCategory::Monster);
            const auto fort=resolveDamage(request,deterministic);
            check(ordinary.usable() && fort.usable() && fort.hpDamage>ordinary.hpDamage &&
                  damageStage(fort,"target_category_rate")->at("percent")==125 &&
                  request.targetStats.targetCategory==DamageTargetCategory::Fort,
                "Actual fort-armored MOB receives source robot explosion category damage rather than the ordinary monster multiplier");
            request.skill.replacesAttackCoefficients=true;request.skill.fixedDamage=100;request.skill.percent=0;
            const auto replaced=resolveDamage(request,deterministic);
            check(replaced.usable() && damageStage(replaced,"target_category_rate")->at("percent")==125,
                "Controller skill coefficient replacement preserves the original ATK category multiplier");
        }
    }
    CharacterCatalog characters(pvf); const auto &swordman=characters.at(0);
    const auto base=buildCharacterBaseAttributes(swordman,{},5,CharacterGrowthPolicy::inferredChrGrowthV1());
    const auto sourceAttributes=evaluateCombatAttributes(base,swordman,{},5,
        CombatAttributePolicy::inferredEquipmentCombatStatV1(pvf.script("etc/etcparameter.etc")));
    const auto beforeAttributes=sourceAttributes.snapshot(); const auto characterInput=makeDamageCombatant(sourceAttributes);
    check(characterInput.usable() && characterInput.strength==sourceAttributes.strength &&
        characterInput.physicalAttack==0 && characterInput.physicalDefense==sourceAttributes.physicalDefense && sourceAttributes.snapshot()==beforeAttributes,
        "The real character adapter owns its receipt and carries already-derived defense without adding VIT a second time");
    auto evasionAttributes=sourceAttributes; evasionAttributes.evasionPerMille=15;
    check(makeDamageCombatant(evasionAttributes).evasionPercent==1.5f,
        "Character source evasion per-mille converts to percentage points independently of attacker miss increments");
    auto unusableAttributes=sourceAttributes; unusableAttributes.policy="disabled";
    check(!makeDamageCombatant(unusableAttributes).usable(),"An unusable character aggregate cannot publish a valid damage input");
    const auto realSword=readAttackDamage(pvf.script("character/swordman/attackinfo/attack1.atk"));
    check(realSword.usable() && realSword.type==DamageAttackType::Physical && realSword.baseDamage==0 && realSword.bonusPercent==-15 && realSword.weaponDamageApply,
        "Current1031 swordman attack1 selects source minus15 bonus without confusing the reaction damage token");
    const auto realGoblin=readAttackDamage(pvf.script("monster/goblin/attackinfo/attack1.atk"));
    check(realGoblin.usable() && realGoblin.weaponDamageApply && realGoblin.type==DamageAttackType::Physical,
        "Current1031 goblin source ATK is a usable physical equipment-attack consumer without demo5/14/8 values");
    const auto mob=evaluateMonsterCombatAttributes(readMonsterAttributeSource(pvf,"monster/goblin/goblin.mob",false),1,false,
        MonsterCombatAttributePolicy::inferredMobCombatTableV1());
    const auto monster=makeDamageCombatant(mob,actualPolicy);
    check(monster.usable() && monster.strength==5 && monster.physicalAttack==9 && monster.physicalDefense==37,
        "Real goblin primary5, equipment attack9 and equipment defense12 stay separate through source-factor defense conversion");
    auto real=q; real.attack=realGoblin; real.attackerStats=monster; real.targetStats=monster;
    real.targetStats.physicalDefense=0; auto deterministic=actualPolicy;
    deterministic.randomVariation=false; deterministic.rollCritical=false; deterministic.rollHit=false;
    const auto realDamage=resolveDamage(real,deterministic);
    check(realDamage.hpDamage==9,"Real goblin equipment attack is used in typed damage with no fabricated training base");
    auto malformedMob=mob;
    if (malformedMob.attributes) malformedMob.attributes->absoluteDamage=1;
    check(!makeDamageCombatant(malformedMob,actualPolicy).usable(),
        "A future nonzero monster absolute input cannot silently acquire an invented unit mapping");
    check(policy.describe()["neutral_semantics"]["packet_ctor_used"]==false &&
        policy.describe()["neutral_semantics"]["factor"]==1 && policy.describe()["neutral_semantics"]["final_percent"]==100,
        "Non-neutral STComputeDamageVariable constructor fields are excluded from semantic policy defaults");
    return {{"schema",1},{"status","pass"},{"checks",checks},{"count",checks.size()},{"policy",policy.describe()},
        {"physical_fixture",physical.snapshot()},{"real_goblin_damage",realDamage.snapshot()},
        {"scope","source/typed arithmetic checks; runtime HP consumer and user play are separate"}};
}
} // namespace dnf
