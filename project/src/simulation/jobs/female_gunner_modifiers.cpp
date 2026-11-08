#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/experimental_character.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
using Levels=std::map<SkillKey,int>;
const ScopedSkillField *selectedField(const SkillSourceData &data,const std::string &tag,bool mode) {
    auto fields=data.definition.fieldsInScope(tag,mode?data.mode:"common");
    if(fields.empty()&&mode&&data.mode!="common")fields=data.definition.fieldsInScope(tag,"common");
    if(fields.size()>1)throw std::invalid_argument("Ambiguous female Gunner modifier field: "+tag);
    return fields.empty()?nullptr:fields.front();
}
int learned(const Levels &levels,int id) {
    const auto found=levels.find({5,id});return found==levels.end()?0:std::max(0,found->second);
}
std::optional<double> operand(const FemaleGunnerSkillCommand &command,const std::string &label) {
    for(const auto &p:command.parameters)if(p.at("label").get<std::string>().find(label)!=std::string::npos)
        return p.at("value").get<double>();
    return {};
}
double value(const FemaleGunnerSkillCommand &command,const std::string &label,double absent=0) {
    return operand(command,label).value_or(absent);
}
double raw(const FemaleGunnerSkillCommand &command,int column,bool staticData=false,double absent=0) {
    const auto table=command.rawTables.value(staticData?"static_data":"level_info",Json::array());
    if(!staticData)return skillLevelValue(table,command.level,column).value_or(absent);
    if(column<0||size_t(column)>=table.size()||!table[size_t(column)].is_number())return absent;
    return table[size_t(column)].get<double>();
}
std::optional<FemaleGunnerSkillCommand> passive(int id,const Levels &levels,const ExperimentalCharacterPlan &plan) {
    const auto level=learned(levels,id);if(level<1)return {};
    const auto row=plan.skills.find({5,id});const auto descriptor=plan.femaleGunnerSkills.find({5,id});
    if(row==plan.skills.end()||descriptor==plan.femaleGunnerSkills.end()||!row->second.data)return {};
    auto command=evaluateFemaleGunnerSkill(descriptor->second,*row->second.data,level,0);
    applyFemaleGunnerTpOperands(command,levels,plan,0);return command;
}
const FemaleGunnerSkillCommand *buff(const std::vector<FemaleGunnerSkillCommand> &buffs,int id) {
    // Replacement buffs do not stack by retaining stale copies of the same
    // skill. World owns the actual owner/deadline filter and refresh policy.
    for(auto i=buffs.rbegin();i!=buffs.rend();++i)if(i->key==SkillKey{5,id})return &*i;
    return nullptr;
}
Json receipt(const FemaleGunnerSkillCommand &c,const std::string &consumer,const Json &operands) {
    return {{"consumer",consumer},{"source",c.skillSource.json()},{"level",c.level},{"operands",operands},
        {"classification","inferred-source-semantic-consumer"},{"native_confirmed",false}};
}
bool sourceHeavySkill(SkillKey key,const ExperimentalCharacterPlan &plan) {
    if(key.jobId!=5)return false;
    const auto row=plan.skills.find({5,44});if(row==plan.skills.end()||!row->second.data)return false;
    for(const auto &id:row->second.data->values("[static data]"))if(id.is_number_integer()&&id.get<int>()==key.skillId)return true;
    return false;
}
bool sourceSpitfireSkill(SkillKey key,const ExperimentalCharacterPlan &plan) {
    const auto row=plan.skills.find(key);if(key.jobId!=5||row==plan.skills.end()||!row->second.data)return false;
    const auto fit=row->second.data->values("[skill fitness growtype]");
    // Source marks class-specific Spitfire skills by exactly one growtype=4.
    // Shared base skills listing every job do not gain class-wide reduction.
    return fit.size()==1&&fit[0].is_number_integer()&&fit[0].get<int>()==4;
}
bool robotFamily(const std::string &family) {
    return family=="robot_summon"||family=="robot_airdrop"||family=="factory_summon"||family=="awakening_g0";
}
double positiveFactor(double percent) {
    if(!std::isfinite(percent))throw std::invalid_argument("Nonfinite female Gunner modifier");
    return std::max(0.0,1+percent/100);
}
}

int femaleGunnerEffectiveSkillLevel(SkillKey key,int level,const Levels &configured,const ExperimentalCharacterPlan &plan) {
    if(level<=0||key.jobId!=5||!learned(configured,44)||!sourceHeavySkill(key,plan))return level;
    const auto row=plan.skills.find(key);if(row==plan.skills.end()||!row->second.data)return level;
    const auto table=row->second.data->values("[level info]");
    if(table.empty()||!table[0].is_number_integer()||table[0].get<int>()<=0)return level;
    const auto width=table[0].get<size_t>();if((table.size()-1)%width)return level;
    return std::min(level+1,int((table.size()-1)/width));
}

void applyFemaleGunnerTpOperands(FemaleGunnerSkillCommand &command,const Levels &configured,
    const ExperimentalCharacterPlan &plan,int weaponSubtype) {
    if(command.key.jobId!=5)return;
    const auto row=plan.skills.find(command.key);const auto descriptor=plan.femaleGunnerSkills.find(command.key);
    if(row==plan.skills.end()||!row->second.data||descriptor==plan.femaleGunnerSkills.end())return;
    if(command.key.skillId==20) {
        const auto headshot=plan.skills.find({5,5});const auto headDescriptor=plan.femaleGunnerSkills.find({5,5});
        if(headshot==plan.skills.end()||!headshot->second.data||headDescriptor==plan.femaleGunnerSkills.end())
            throw std::invalid_argument("TurningShoot source HeadShot dependency unavailable");
        const int headLevel=std::max(1,learned(configured,5));
        auto inherited=evaluateFemaleGunnerSkill(headDescriptor->second,*headshot->second.data,headLevel,weaponSubtype);
        applyFemaleGunnerTpOperands(inherited,configured,plan,weaponSubtype);
        command.damage=inherited.damage;
        const double ratio=value(command,"攻击力强化比率")/100;
        command.damage.percent*=float(ratio);command.damage.independentPercent*=float(ratio);command.damage.fixedDamage*=float(ratio);
        command.damage.sources.push_back(receipt(command,"turning_shoot_current_headshot_inheritance",{{"headshot_level",headLevel},
            {"source",headshot->second.source.json()},{"strengthening_ratio",ratio},{"unlearned_headshot_test_policy",learned(configured,5)<1}}));
        command.rawTables["inherited_headshot"]=inherited.snapshot();
    }
    // Reentry cannot compound an already applied TP. Rebuild from the exact
    // immutable base row on each invocation; entity position/lifecycle stay.
    auto source=*row->second.data;auto upgradedDescriptor=descriptor->second;
    Json changes=Json::array(),diagnostics=Json::array(),templates=Json::array();
    const auto feature=selectedField(source,"[feature skill index]",false);
    for(const auto &configuredRow:configured) {
        if(configuredRow.first.jobId!=5||configuredRow.second<1||configuredRow.first==command.key)continue;
        const auto tp=plan.skills.find(configuredRow.first);
        if(tp==plan.skills.end()||!tp->second.data||tp->second.kind!=SkillSourceKind::Passive)continue;
        const auto &tpData=*tp->second.data;
        const auto special=selectedField(tpData,"[special level up]",true);if(!special)continue;
        bool target=false;
        if(feature)for(const auto &id:feature->field.values)if(id.is_number_integer()&&id.get<int>()==configuredRow.first.skillId)target=true;
        if(const auto prerequisite=selectedField(tpData,"[pre required skill]",false)) {
            const auto &v=prerequisite->field.values;
            for(size_t i=0;i+1<v.size();i+=2)if(v[i].is_number_integer()&&v[i].get<int>()==command.key.skillId)target=true;
        }
        if(!target)continue;
        // Some feature SKLs introduce additional columns and a new display
        // schema (CrossShoot count, Steyr bleed, Guard complete absorption).
        // Their selected tables are an alternate skill specification sampled
        // at the BASE skill level, not at the learned TP level. This explicit
        // inference is retained alongside both original specifications.
        for(const auto *tag:{"[level info]","[static data]"}) {
            const auto replacement=tpData.selected.find(normalize(tag));
            if(replacement!=tpData.selected.end())source.selected[normalize(tag)]=replacement->second;
        }
        const auto tpDescriptor=plan.femaleGunnerSkills.find(configuredRow.first);
        if(tpDescriptor!=plan.femaleGunnerSkills.end()&&!tpDescriptor->second.propertySchema.empty())
            upgradedDescriptor.propertySchema=tpDescriptor->second.propertySchema;
        templates.push_back({{"tp_source",tp->second.source.json()},{"base_source",row->second.source.json()},
            {"base_skill_level",command.level},{"tp_level",configuredRow.second},
            {"policy","inferred-1031-feature-template-at-base-level-v1"},{"classification","inferred"},
            {"basis","Current1031 feature SKL adds columns/schema and may change base values; native feature dispatch absent"}});
        const auto &v=special->field.values;if(v.size()%4)throw std::invalid_argument("Malformed source TP [special level up]");
        for(size_t i=0;i<v.size();i+=4) {
            if(!v[i].is_number_integer()||!v[i+1].is_number_integer()||!v[i+2].is_string()||!v[i+3].is_number())
                throw std::invalid_argument("Malformed source TP operand tuple");
            const auto selector=v[i].get<int>(),column=v[i+1].get<int>();const auto op=v[i+2].get<std::string>();
            const double delta=v[i+3].get<double>();
            const std::string tag=selector<0?"[level info]":"[static data]";
            auto field=source.selected.find(normalize(tag));size_t cell=0;
            bool available=field!=source.selected.end()&&column>=0;
            if(available&&selector<0) {
                const auto &table=field->second.field.values;
                available=bool(skillLevelValue(table,command.level,column));
                if(available)cell=1+size_t(command.level-1)*table[0].get<size_t>()+size_t(column);
            }else if(available) {cell=size_t(column);available=cell<field->second.field.values.size();}
            if(!available||!field->second.field.values[cell].is_number()) {
                diagnostics.push_back({{"code","tp_target_cell_unavailable"},{"tp_source",tp->second.source.json()},
                    {"selector",selector},{"column",column},{"mode",source.mode}});continue;
            }
            const double before=field->second.field.values[cell].get<double>();double after=before;
            if(op=="%")after=before*(1+delta*configuredRow.second/100);
            else if(op=="+")after=before+delta*configuredRow.second;
            else if(op=="-")after=before-delta*configuredRow.second;
            else throw std::invalid_argument("Unsupported source TP operator: "+op);
            if(!std::isfinite(after)||after<0)throw std::invalid_argument("Source TP yields invalid target operand");
            field->second.field.values[cell]=after;
            changes.push_back({{"tp_key",configuredRow.first.json()},{"tp_source",tp->second.source.json()},
                {"tp_level",configuredRow.second},{"tp_scope",special->scope},{"tp_offset",special->field.offset},
                {"table",tag},{"table_scope",field->second.scope},{"table_offset",field->second.field.offset},
                {"selector",selector},{"column",column},{"operation",op},{"per_level",delta},{"before",before},{"after",after},
                {"policy","inferred-1031-linear-source-special-level-up-v1"},{"classification","inferred"}});
        }
    }
    if(templates.empty()) {for(const auto &d:diagnostics)command.diagnostics.push_back(d);return;}
    auto refreshed=evaluateFemaleGunnerSkill(upgradedDescriptor,source,command.level,weaponSubtype);
    command.parameters=std::move(refreshed.parameters);command.damage=std::move(refreshed.damage);
    command.rawTables=std::move(refreshed.rawTables);command.rawTables["tp_applied_cells"]=changes;
    command.rawTables["source_level_info"]=row->second.data->values("[level info]");
    command.rawTables["source_static_data"]=row->second.data->values("[static data]");
    command.rawTables["feature_template_selection"]=templates;
    command.count=refreshed.count;command.intervalMs=refreshed.intervalMs;
    // Action-bound fallback durations remain when the source has no duration.
    if(refreshed.lifetimeMs>0)command.lifetimeMs=refreshed.lifetimeMs;
    if(refreshed.range>0)command.range=refreshed.range;
    command.evidence.push_back({{"consumer","source_tp_cell_overlay"},{"changes",changes},
        {"classification","inferred"},{"native_confirmed",false},
        {"unverified_conditions","Native rounding and interaction order require original comparison"}});
    for(const auto &d:diagnostics)command.diagnostics.push_back(d);
}

Json FemaleGunnerActorModifiers::snapshot() const {
    return {{"move_multiplier",moveMultiplier},{"attack_multiplier",attackMultiplier},{"cast_multiplier",castMultiplier},
        {"jump_multiplier",jumpMultiplier},{"strength",strength},{"intelligence",intelligence},{"vitality",vitality},{"spirit",spirit},
        {"physical_defense",physicalDefense},{"magical_defense",magicalDefense},{"evasion_percent",evasionPercent},
        {"physical_critical_percent",physicalCriticalPercent},{"magical_critical_percent",magicalCriticalPercent},
        {"physical_damage_reduction_percent",physicalDamageReductionPercent},{"magical_damage_reduction_percent",magicalDamageReductionPercent},
        {"hp_maximum_multiplier",hpMaximumMultiplier},{"trace",trace},{"diagnostics",diagnostics}};
}
void applyFemaleGunnerAmmoCapacity(FemaleGunnerSkillCommand &command,const Levels &configured,const ExperimentalCharacterPlan &plan) {
    if(command.key.jobId!=5||command.family!="ammo_enchantment"||
        (command.key.skillId!=1&&command.key.skillId!=2&&command.key.skillId!=30&&command.key.skillId!=52))return;
    const auto c=passive(49,configured,plan);if(!c)return;
    const auto extra=raw(*c,command.key.skillId==52?1:0);
    const auto original=command.rawTables.value("ammo_capacity_source_count",command.count);
    if(!std::isfinite(extra)||extra<0||std::floor(extra)!=extra||extra+original>100000)
        throw std::invalid_argument("Source magazine expansion produces invalid charge count");
    command.rawTables["ammo_capacity_source_count"]=original;
    command.count=original+uint32_t(extra);
    auto trace=receipt(*c,"magazine_expansion_actual_reload_capacity",{{"ammo_key",command.key.json()},
        {"source_column",command.key.skillId==52?1:0},{"base_count",original},{"added_count",extra},{"final_count",command.count},
        {"tp_cells",c->rawTables.value("tp_applied_cells",Json::array())},
        {"basis","Source49 explain names Silver/Freeze/Flame/Piercing; TP151 has distinct per-column additions"}});
    command.rawTables["ammo_capacity_modifier"]=trace;command.evidence.push_back(std::move(trace));
}
FemaleGunnerShotCountModifier femaleGunnerAdditionalBasicShots(const Levels &configured,const ExperimentalCharacterPlan &plan,int weaponSubtype) {
    FemaleGunnerShotCountModifier out;if(weaponSubtype!=2)return out;
    if(const auto c=passive(110,configured,plan)) {
        const auto amount=raw(*c,2);
        if(!std::isfinite(amount)||amount<0||std::floor(amount)!=amount||amount>10000)
            throw std::invalid_argument("Source musket additional shot count is invalid");
        out.extraShots=uint32_t(amount);
        out.trace.push_back(receipt(*c,"source_musket_additional_basic_shots",{{"extra_shots",out.extraShots},{"source_column",2},
            {"weapon_subtype",weaponSubtype},{"basis","Source110 explain restricts additional ordinary shooting to musket-series weapons"},
            {"unverified_conditions","Native per-shot spacing and firing poses require original dynamic comparison"}}));
    }
    return out;
}
FemaleGunnerActorModifiers evaluateFemaleGunnerActorModifiers(const std::vector<FemaleGunnerSkillCommand> &buffs,
    const Levels &configured,const ExperimentalCharacterPlan &plan,int weaponSubtype) {
    FemaleGunnerActorModifiers out;
    if(const auto c=passive(200,configured,plan)) {
        out.strength=value(*c,"增加力量");out.vitality=value(*c,"增加体力");
        out.intelligence=value(*c,"增加智力");out.spirit=value(*c,"增加精神");
        out.trace.push_back(receipt(*c,"primary_attributes",{{"strength",out.strength},{"intelligence",out.intelligence},{"vitality",out.vitality},{"spirit",out.spirit}}));
    }
    if(const auto c=passive(186,configured,plan)){out.physicalCriticalPercent=value(*c,"暴击率");out.trace.push_back(receipt(*c,"physical_critical_probability",out.physicalCriticalPercent));}
    if(const auto c=passive(188,configured,plan)){out.magicalCriticalPercent=value(*c,"暴击率");out.trace.push_back(receipt(*c,"magical_critical_probability",out.magicalCriticalPercent));}
    if(weaponSubtype==2)if(const auto c=passive(110,configured,plan)) {
        out.attackMultiplier*=positiveFactor(value(*c,"攻击速度"));out.trace.push_back(receipt(*c,"source_musket_attack_speed",out.attackMultiplier));
    }
    if(const auto c=buff(buffs,176)) {out.intelligence+=value(*c,"智力增加");out.trace.push_back(receipt(*c,"timed_intelligence",value(*c,"智力增加")));}
    if(const auto c=buff(buffs,100)) {
        out.moveMultiplier*=positiveFactor(value(*c,"移动速度增加"));out.attackMultiplier*=positiveFactor(value(*c,"攻击速度增加"));
        out.evasionPercent+=value(*c,"回避率增加");out.trace.push_back(receipt(*c,"twin_gunblade_live_mode_speed_evasion",c->parameters));
    }
    if(const auto c=buff(buffs,15)) {out.moveMultiplier*=positiveFactor(value(*c,"移动速度增加"));out.trace.push_back(receipt(*c,"mobile_shoot_mode_movement",out.moveMultiplier));}
    if(const auto c=buff(buffs,43)) {
        out.evasionPercent+=value(*c,"回避率");out.physicalDefense+=value(*c,"物理防御力");out.magicalDefense+=value(*c,"魔法防御力");
        out.physicalDamageReductionPercent=value(*c,"物理伤害减少率");out.magicalDamageReductionPercent=value(*c,"魔法伤害减少率");
        out.trace.push_back(receipt(*c,"camouflage_defense_evasion_mitigation",c->parameters));
    }
    if(const auto c=passive(195,configured,plan)) {out.hpMaximumMultiplier=positiveFactor(value(*c,"HP最大值变化量"));out.trace.push_back(receipt(*c,"hp_maximum",out.hpMaximumMultiplier));}
    // The source explain says +20%; static200 therefore represents +200/1000.
    // The actual jump request consumes this ratio in the runtime.
    if(const auto c=buff(buffs,175))out.trace.push_back(receipt(*c,"inferred_source_jump_power_per_mille",
        {{"source_static",c->rawTables.value("static_data",Json::array())},{"consumer","ExperimentalCharacterRuntime::advance/sourceJumpPower"},
         {"source_explain_percent",20},{"policy","inferred-1031-jump-power-as-initial-velocity-v1"}}));
    return out;
}

FemaleGunnerCostModifiers femaleGunnerCostModifiers(SkillKey key,const std::vector<FemaleGunnerSkillCommand> &buffs,
    const Levels &configured,const ExperimentalCharacterPlan &plan,int weaponSubtype) {
    FemaleGunnerCostModifiers out;if(key.jobId!=5)return out;
    const auto reduce=[&](std::vector<SkillCostModifier> &to,const FemaleGunnerSkillCommand &c,const std::string &label,const std::string &id) {
        const auto p=operand(c,label);if(!p)return;
        SkillCostModifier m;m.id=id;m.multiply=std::clamp(1-*p/100,0.0,1.0);m.source=c.skillSource;
        m.evidence.push_back(receipt(c,id,{{"source_percent",*p},{"multiply",m.multiply}}));out.trace.push_back(m.evidence.back());to.push_back(std::move(m));
    };
    if(sourceHeavySkill(key,plan))if(const auto c=passive(21,configured,plan))reduce(out.mp,*c,"技能MP消耗减少","heavy_weapon_mastery_mp");
    if(weaponSubtype==2&&sourceSpitfireSkill(key,plan))if(const auto c=passive(110,configured,plan))reduce(out.cooldown,*c,"冷却时间减少","musket_mastery_spitfire_cooldown");
    // G-extension stacks require actual transformation history. A learned
    // passive alone is never treated as five active stacks.
    if(key.skillId>=79&&key.skillId<=81)if(const auto c=buff(buffs,95)) {
        reduce(out.mp,*c,"MP消耗量减少","g_extension_live_stack_mp");
        reduce(out.cooldown,*c,"改装冷却时间减少","g_extension_live_stack_cooldown");
    }
    return out;
}

Json applyFemaleGunnerAttackOperands(DamageRequest &request,const std::vector<FemaleGunnerSkillCommand> &buffs,
    const Levels &configured,const ExperimentalCharacterPlan &plan,const FemaleGunnerAttackContext &context) {
    Json trace=Json::array();if(plan.identity.jobId!=5)return trace;
    const auto actor=evaluateFemaleGunnerActorModifiers(buffs,configured,plan,context.weaponSubtype);
    request.attackerStats.strength+=float(actor.strength);request.attackerStats.intelligence+=float(actor.intelligence);
    request.attackerStats.physicalCriticalBonusPercent+=float(actor.physicalCriticalPercent);
    request.attackerStats.magicalCriticalBonusPercent+=float(actor.magicalCriticalPercent);
    for(const auto &t:actor.trace)trace.push_back(t);
    const auto multiply=[&](const FemaleGunnerSkillCommand &c,const std::string &consumer,double percent) {
        request.skill.totalMultiplier*=float(positiveFactor(percent));trace.push_back(receipt(c,consumer,{{"percent",percent}}));
    };
    if(!context.attackSkill) {
        auto masteryLevels=configured;
        if(learned(configured,174))masteryLevels[{5,174}]=std::max(1,context.characterLevel);
        if(const auto c=passive(174,masteryLevels,plan)) {
            const char *label=context.basicMotion=="[dashattack motion]"?"前冲攻击力":context.basicMotion=="[jumpattack motion]"?"跳跃攻击力":"基本攻击力";
            multiply(*c,"basic_dash_jump_training",value(*c,label));
        }
        if(context.airborne)if(const auto c=buff(buffs,33))multiply(*c,"airborne_basic_shot_buff",value(*c,"攻击力增加"));
    }
    if(context.backAttack) {
        if(const auto c=passive(178,configured,plan)){const auto p=value(*c,"暴击率");request.attackerStats.physicalCriticalBonusPercent+=float(p);trace.push_back(receipt(*c,"actual_back_attack_physical_critical",p));}
        if(const auto c=passive(189,configured,plan)){const auto p=value(*c,"暴击率");request.attackerStats.magicalCriticalBonusPercent+=float(p);trace.push_back(receipt(*c,"actual_back_attack_magical_critical",p));}
    }
    if(context.attackSkill) {
        const auto key=*context.attackSkill;
        if(key==SkillKey{5,7}||key==SkillKey{5,47})if(const auto c=passive(32,configured,plan))
            multiply(*c,"triple_clutch_specific_followup",raw(*c,key.skillId==7?0:1));
        if(sourceHeavySkill(key,plan)) {
            if(const auto c=passive(93,configured,plan))multiply(*c,"overheat_heavy_weapon",value(*c,"重火器攻击力"));
            if(const auto c=buff(buffs,62)) {
                multiply(*c,"heavy_weapon_live_buff_damage",value(*c,"攻击力增加"));
                const auto p=value(*c,"命中率增加");request.attackerStats.attackMissDeltaPercent-=float(p);trace.push_back(receipt(*c,"heavy_weapon_live_buff_hit_probability",p));
            }
        }
        if(key.skillId>=79&&key.skillId<=81)if(const auto c=buff(buffs,95))multiply(*c,"g_extension_live_stack_damage",value(*c,"攻击力增加"));
    }
    if(robotFamily(context.family))if(const auto c=buff(buffs,46)) {
        // Source repeated placeholders on the same line retain ordinals, so
        // use the exact source columns for the individual robot stats.
        request.attackerStats.strength+=float(raw(*c,2));request.attackerStats.intelligence+=float(raw(*c,3));
        trace.push_back(receipt(*c,"robotics_robot_primary_stats",{{"strength",raw(*c,2)},{"intelligence",raw(*c,3)}}));
    }
    const bool magical=request.attack.type==DamageAttackType::Magical||
        (request.attack.type==DamageAttackType::Weapon&&request.weaponType==DamageAttackType::Magical);
    // Source60 explain restricts this effect to revolver-series weapons.
    if(!magical&&context.weaponSubtype==0)if(const auto c=buff(buffs,60)) {
        request.skill.criticalMultiplier*=float(positiveFactor(value(*c,"物理暴击伤害")));
        trace.push_back(receipt(*c,"physical_critical_only_damage_multiplier",{{"multiply",request.skill.criticalMultiplier},{"consumer","resolveDamage_after_actual_critical_roll"}}));
    }
    for(const auto &t:trace)request.skill.sources.push_back(t);
    return trace;
}
} // namespace dnf
