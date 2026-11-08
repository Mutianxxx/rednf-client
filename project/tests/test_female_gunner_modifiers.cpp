#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/experimental_character.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace dnf {
Json runFemaleGunnerModifierTests(Pvf &pvf,Assets &assets) {
    CharacterCatalog catalog(pvf);
    auto plan=loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0});
    Json checks=Json::array(),failures=Json::array(),tpRows=Json::array();
    const auto check=[&](bool ok,const std::string &message){checks.push_back({{"passed",ok},{"message",message}});if(!ok)failures.push_back(message);};
    const auto near=[](double a,double b){return std::abs(a-b)<0.0001*std::max(1.0,std::abs(b));};
    const auto command=[&](int id,int level=1) {return evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,id}),*plan.skills.at({5,id}).data,level,0);};
    const auto raw=[](const FemaleGunnerSkillCommand &c,int column,bool stat=false){const auto t=c.rawTables.at(stat?"static_data":"level_info");return stat?t.at(size_t(column)).get<double>():*skillLevelValue(t,c.level,column);};
    // Exercise every authored TP tuple against its real base source, not a
    // synthetic uniform multiplier. Missing source cells remain diagnostics.
    size_t tpCount=0;
    for(const auto &entry:plan.skills) {
        const auto &definition=entry.second.data->definition;
        auto special=definition.fieldsInScope("[special level up]","dungeon");
        if(special.empty())special=definition.fieldsInScope("[special level up]","common");
        if(special.empty())continue;
        const auto prerequisite=definition.fieldsInScope("[pre required skill]","common");
        int target=-1,baseLevel=1;
        if(!prerequisite.empty()&&prerequisite.front()->field.values.size()>=2) {
            target=prerequisite.front()->field.values[0].get<int>();baseLevel=prerequisite.front()->field.values[1].get<int>();
        }
        if(target<0)for(const auto &candidate:plan.skills)for(const auto *f:candidate.second.data->definition.fieldsInScope("[feature skill index]","common"))
            for(const auto &id:f->field.values)if(id.is_number_integer()&&id.get<int>()==entry.first.skillId)target=candidate.first.skillId;
        if(target<0) {check(special.front()->field.values.empty(),"Unbound TP has no invented behavior: "+entry.second.name);continue;}
        try {
            auto c=command(target,baseLevel);const auto original=plan.skills.at({5,target}).data->snapshot(true);
            const std::map<SkillKey,int> configured{{entry.first,1},{{5,target},baseLevel}};
            applyFemaleGunnerTpOperands(c,configured,plan,0);++tpCount;
            const auto cells=c.rawTables.value("tp_applied_cells",Json::array());
            if(entry.first.skillId==167) {
                // Both source47 and feature167 have exactly static[250], but
                // the source special tuple explicitly targets static column1.
                // Keep the missing cell; no fabricated second operand.
                check(cells.size()+1==special.front()->field.values.size()/4,
                    "LiftShotEx executes available damage cells and retains its authored missing static1 boundary");
                check(c.diagnostics.size()==1&&c.diagnostics[0].value("code",std::string())=="tp_target_cell_unavailable"&&
                    c.diagnostics[0].at("selector")==1&&c.diagnostics[0].at("column")==1,
                    "LiftShotEx malformed/unresolved source static1 remains a specific diagnostic, never invented");
            }else {
                check(cells.size()==special.front()->field.values.size()/4,"TP executes every authored cell: "+entry.second.name);
                check(c.diagnostics.empty(),"TP selected cells are available in current1031 base: "+entry.second.name);
            }
            for(const auto &cell:cells) {
                const auto before=cell.at("before").get<double>(),delta=cell.at("per_level").get<double>();const auto op=cell.at("operation").get<std::string>();
                const double expected=op=="%"?before*(1+delta/100):op=="+"?before+delta:before-delta;
                check(near(cell.at("after").get<double>(),expected),"TP operator changes its exact source operand: "+entry.second.name);
            }
            const auto damage=c.damage.snapshot(),parameters=c.parameters;applyFemaleGunnerTpOperands(c,configured,plan,0);
            check(damage==c.damage.snapshot()&&parameters==c.parameters,"TP reevaluation does not compound on an already evaluated command: "+entry.second.name);
            check(original==plan.skills.at({5,target}).data->snapshot(true),"TP leaves immutable source definition unchanged: "+entry.second.name);
            tpRows.push_back({{"tp",entry.first.json()},{"base",target},{"cells",cells},{"diagnostics",c.diagnostics}});
        }catch(const std::exception &e){check(false,entry.second.name+": "+e.what());}
    }
    auto head=command(5,10);const auto headBase=head.damage.percent;
    applyFemaleGunnerTpOperands(head,{{{5,140},2}},plan,0);
    check(near(head.damage.percent,headBase*1.2),"HeadShot TP level two changes source damage column by exactly +20 percent");
    check(near(raw(head,3),*skillLevelValue(plan.skills.at({5,5}).data->values("[level info]"),10,3)+6),"HeadShot TP separately adds source piercing, never damage");
    auto punish=command(6,10);const auto punishCount=punish.count;const auto punishPercent=punish.damage.percent;
    applyFemaleGunnerTpOperands(punish,{{{5,145},1}},plan,0);
    check(punish.count==punishCount+2&&near(punish.damage.percent,punishPercent*.85),"Punisher TP reduces per-bullet damage while adding two real shots");
    auto charge=command(109,10);const auto chargeConsumption=raw(charge,1,true);
    applyFemaleGunnerTpOperands(charge,{{{5,226},1}},plan,0);
    check(near(raw(charge,1,true),chargeConsumption-1),"ChargeBuster TP subtraction changes the selected source consumption cell");
    auto unlearned=command(5,10);const auto unlearnedSnapshot=unlearned.snapshot();
    applyFemaleGunnerTpOperands(unlearned,{{{5,140},0}},plan,0);
    check(unlearned.snapshot()==unlearnedSnapshot,"Unlearned TP leaves the actual skill command unchanged");
    auto pvpPlan=plan;
    for(const int id:{5,140})pvpPlan.skills.at({5,id}).data=std::make_shared<SkillSourceData>(readSkillSourceData(plan.skills.at({5,id}).data->definition,"pvp"));
    auto pvp=evaluateFemaleGunnerSkill(pvpPlan.femaleGunnerSkills.at({5,5}),*pvpPlan.skills.at({5,5}).data,10,0);
    const auto pvpPercent=pvp.damage.percent;applyFemaleGunnerTpOperands(pvp,{{{5,140},2}},pvpPlan,0);
    check(near(pvp.damage.percent,pvpPercent)&&pvp.rawTables.at("tp_applied_cells")[0].at("tp_scope")=="pvp","PvP TP uses its zero source override rather than dungeon increase");
    const auto stats=evaluateFemaleGunnerActorModifiers({},{{{5,186},1},{{5,188},1},{{5,200},1}},plan,0);
    check(stats.physicalCriticalPercent>0&&stats.magicalCriticalPercent>0&&stats.strength>0&&stats.intelligence>0,"Combat passives affect distinct actual primary/critical operands");
    const auto musket=evaluateFemaleGunnerActorModifiers({},{{{5,110},1}},plan,2);
    const auto revolver=evaluateFemaleGunnerActorModifiers({},{{{5,110},1}},plan,0);
    check(musket.attackMultiplier>1&&revolver.attackMultiplier==1,"Musket mastery requires source EQU subtype two");
    const auto shots=femaleGunnerAdditionalBasicShots({{{5,110},1}},plan,2);
    check(shots.extraShots==3&&!shots.trace.empty()&&femaleGunnerAdditionalBasicShots({{{5,110},1}},plan,0).extraShots==0,
        "Source110 actual dungeon additional3 shots are restricted to source musket subtype2");
    for(const int id:{1,2,30,52}) {
        auto ammo=command(id,10);const auto before=ammo.count;
        const std::map<SkillKey,int> levels{{{5,49},5},{{5,151},2}};
        applyFemaleGunnerAmmoCapacity(ammo,levels,plan);
        const auto sourceAmount=skillLevelValue(plan.skills.at({5,49}).data->values("[level info]"),5,id==52?1:0).value();
        const auto expected=before+uint32_t(sourceAmount)+(id==52?4:10);
        check(ammo.count==expected&&ammo.rawTables.contains("ammo_capacity_modifier"),
            "Source49 and TP151 change actual reload charges with ammo-specific columns: "+std::to_string(id));
        applyFemaleGunnerAmmoCapacity(ammo,levels,plan);
        check(ammo.count==expected,"Reevaluating source magazine capacity never compounds extra charges: "+std::to_string(id));
    }
    const auto caster=command(176);const auto timedStats=evaluateFemaleGunnerActorModifiers({caster},{},plan,0);
    check(timedStats.intelligence>0&&evaluateFemaleGunnerActorModifiers({}, {},plan,0).intelligence==0,"Expired intelligence buff leaves no permanent stat overlay");
    const auto heavy=femaleGunnerCostModifiers({5,12},{},{{{5,21},1}},plan,0);
    const auto nonHeavy=femaleGunnerCostModifiers({5,5},{},{{{5,21},1}},plan,0);
    check(heavy.mp.size()==1&&heavy.mp.front().multiply<1&&nonHeavy.mp.empty(),"Heavy-weapon mastery MP applies only to source enumerated heavy skills");
    const auto spit=femaleGunnerCostModifiers({5,52},{},{{{5,110},1}},plan,2);
    const auto common=femaleGunnerCostModifiers({5,56},{},{{{5,110},1}},plan,2);
    check(spit.cooldown.size()==1&&common.cooldown.empty(),"Musket cooldown source qualification keeps class skills distinct from shared base skills");
    check(femaleGunnerEffectiveSkillLevel({5,12},10,{{{5,44},1}},plan)==11&&femaleGunnerEffectiveSkillLevel({5,5},10,{{{5,44},1}},plan)==10,
        "Heavy weapon awakening passive adds one source level to its enumerated skills only");
    DamageRequest basic;basic.attack.type=DamageAttackType::Physical;
    FemaleGunnerAttackContext context;context.weaponSubtype=0;context.characterLevel=20;context.basicMotion="[attack motion]";
    applyFemaleGunnerAttackOperands(basic,{},{{{5,174},1}},plan,context);
    check(basic.skill.totalMultiplier>1,"Basic mastery consumes actual basic contact coefficients");
    auto skill=DamageRequest{};skill.attack.type=DamageAttackType::Physical;context.attackSkill=SkillKey{5,5};
    applyFemaleGunnerAttackOperands(skill,{},{{{5,174},1}},plan,context);
    check(skill.skill.totalMultiplier==1,"Basic mastery cannot become a universal active-skill multiplier");
    DamageRequest clutch;clutch.attack.type=DamageAttackType::Physical;context.attackSkill=SkillKey{5,7};
    applyFemaleGunnerAttackOperands(clutch,{},{{{5,32},1}},plan,context);
    check(clutch.skill.totalMultiplier>1,"Triple clutch modifies its source named follow-up skill");
    DamageRequest death;death.attack.type=DamageAttackType::Physical;
    applyFemaleGunnerAttackOperands(death,{command(60)},{},plan,context);
    check(death.skill.criticalMultiplier>1&&death.skill.totalMultiplier==1,"Death by revolver writes only the real-critical consumer operand");
    DamageRequest wrongWeapon;wrongWeapon.attack.type=DamageAttackType::Physical;context.weaponSubtype=2;
    applyFemaleGunnerAttackOperands(wrongWeapon,{command(60)},{},plan,context);context.weaponSubtype=0;
    check(wrongWeapon.skill.criticalMultiplier==1,"DeathByRevolver source explain requires equipped revolver subtype0");
    DamageRequest robotics;robotics.attack.type=DamageAttackType::Magical;context.family="robot_summon";
    applyFemaleGunnerAttackOperands(robotics,{command(46)},{},plan,context);
    check(robotics.attackerStats.intelligence>0&&robotics.attackerStats.strength>0,"Robotics increases robot source primary stats");
    DamageRequest ordinary;ordinary.attack.type=DamageAttackType::Physical;context.family="bullet_headshot";
    applyFemaleGunnerAttackOperands(ordinary,{command(46)},{},plan,context);
    check(ordinary.attackerStats.intelligence==0&&ordinary.attackerStats.strength==0,"Robotics does not increase the caster's ordinary attack stats");
    auto turning=command(20);applyFemaleGunnerTpOperands(turning,{{{5,5},10},{{5,140},2}},plan,0);
    check(near(turning.damage.percent,head.damage.percent*1.2),"TurningShoot inherits configured HeadShot level and TP before its source 120 percent strengthening");
    const auto cannon=command(73);check(near(cannon.damage.percent,raw(cannon,0)),"A charged damage min/max range is not summed as two attacks");
    const auto air=command(101);check(near(air.damage.independentPercent,raw(air,2)),"Source damage X count keeps hit count out of damage coefficient");
    Json result={{"schema",1},{"passed",failures.empty()},{"check_count",checks.size()},{"checks",checks},{"failures",failures},
        {"tp_count",tpCount},{"tp_rows",tpRows},{"pvf_identity",pvf.identity()},
        {"scope","Pure source modifier consumers; World contacts/normal learning/original dynamic comparison require separate verification"}};
    if(!failures.empty()){writeJson("reports/knowledge-base-audit/female-gunner-modifier-tests-failed.json",result);throw std::runtime_error("Female Gunner modifier checks failed");}
    return result;
}
} // namespace dnf
