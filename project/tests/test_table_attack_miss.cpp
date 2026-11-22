#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include <stdexcept>
#include <cmath>
namespace dnf {
Json runTableAttackMissTests(Pvf &pvf,Assets &assets) {
    int checks=0;Json samples=Json::array();
    const auto check=[&](bool okay,const char *message){++checks;if(!okay)throw std::runtime_error(std::string("Table attack miss: ")+message);};
    const auto rejects=[](auto action){try{action();}catch(const std::exception&){return true;}return false;};
    const auto policy=MonsterCombatAttributePolicy::inferredMobCombatTableV1();
    const auto source=readMonsterAttributeSource(pvf,"monster/goblin/goblin.mob",false);
    const auto expectedRaw=[&](const MonsterAttributeSource &s,int level) {
        for(size_t row=0;row<s.table.tokens.size();row+=24)if(s.table.tokens[row].at("value")==level)return s.table.tokens[row+11].at("value").get<int>();
        throw std::runtime_error("Missing source level");
    };
    const auto delta=[](int raw){volatile float value=float(raw),scale=.01f;volatile float result=value*scale;return result;};
    auto damagePolicy=DamageResolutionPolicy::inferredPveDamageV1(pvf.script("etc/etcparameter.etc"));
    for(const auto &[path,boss]:std::vector<std::pair<std::string,bool>>{{"monster/goblin/goblin.mob",false},{"monster/tau/taubeast.mob",true}}) {
        const auto current=readMonsterAttributeSource(pvf,path,boss);
        for(const int level:{1,9,25,50,60,99}) {
            const int raw=expectedRaw(current,level);const auto evaluated=evaluateMonsterCombatAttributes(current,level,boss,policy);
            check(evaluated.usable(),"Real common/boss high-level source remains usable with every raw11 term consumed");
            const auto &v=*evaluated.attributes;
            check(v.tableAttackMissDeltaPercent==delta(raw)&&v.tableAttackMissSource.at("raw_value")==raw&&
                v.tableAttackMissSource.at("raw_column")==11&&v.tableAttackMissSource.at("level")==level&&
                v.tableAttackMissSource.at("classification")=="inferred_beta",
                "Exact source integer-to-float32 times float32 .01 is frozen with source level and inferred classification");
            const auto attack=makeDamageCombatant(evaluated,damagePolicy);
            check(attack.usable()&&attack.attackMissDeltaPercent==delta(raw)&&attack.evasionPercent==0&&v.hitRateBonus==0&&v.evasionRateBonus==0,
                "Actual damage adapter uses attacker miss delta without aliasing hit/evasion");
            const auto frozen=evaluated.snapshot(true);const auto restored=restoreMonsterCombatAttributes(frozen,current);
            check(restored.snapshot(true)==frozen&&makeDamageCombatant(restored,damagePolicy).attackMissDeltaPercent==delta(raw),
                "Frozen receipt and real damage input roundtrip exactly without recomputing HP or full attributes");
            samples.push_back({{"monster",path},{"level",level},{"raw",raw},{"frozen",frozen}});
        }
    }
    const auto high=evaluateMonsterCombatAttributes(source,50,false,policy);const auto saved=high.snapshot();
    for(int alteration=0;alteration<12;++alteration) {
        auto bad=saved;auto &a=bad["attributes"];
        if(alteration==0)a["table_attack_miss_delta_percent"]=0;
        if(alteration==1)a["table_attack_miss_delta_percent"]=0.02; // binary64 decimal != exact source float32
        if(alteration==2)a.erase("table_attack_miss_source");
        if(alteration==3){a.erase("table_attack_miss_source");a.erase("table_attack_miss_delta_percent");}
        if(alteration==4)a["table_attack_miss_source"]["raw_value"]=0;
        if(alteration==5)a["table_attack_miss_source"]["level"]=25;
        if(alteration==6)a["table_attack_miss_source"]["source"]["byte_offset"]=2;
        if(alteration==7)a["table_attack_miss_source"]["source"]["member_sha256"]="wrong";
        if(alteration==8)a["table_attack_miss_source"]["classification"]="native_confirmed";
        if(alteration==9)a["table_attack_miss_source"]["policy"]="unknown";
        if(alteration==10)a["table_attack_miss_delta_percent"]="0.02";
        if(alteration==11){a["table_attack_miss_source"]=Json::object();a["table_attack_miss_delta_percent"]=0;}
        check(rejects([&]{restoreMonsterCombatAttributes(bad,source);}),"Altered/source-erasing high-level receipt rejects before publication");
    }
    auto legacy=evaluateMonsterCombatAttributes(source,1,false,policy).snapshot();
    legacy["attributes"].erase("table_attack_miss_delta_percent");legacy["attributes"].erase("table_attack_miss_source");
    const auto legacyRestored=restoreMonsterCombatAttributes(legacy,source);
    check(legacyRestored.usable()&&legacyRestored.attributes->tableAttackMissDeltaPercent==0,
        "Old neutral level1 receipts migrate explicitly while nonzero historical omission stays rejected");
    RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);Progression progression(catalog);
    World character(pvf,assets,WorldRules::BetaFoundationV1);character.applyEquipment(progression);
    DamageRequest request;request.attacker={1,1};request.target={2,1};request.attackInstance=1;
    request.attackerStats=makeDamageCombatant(high,damagePolicy);request.targetStats=makeDamageCombatant(*character.combatAttributes());
    request.targetStats.evasionPercent=0;request.targetStats.damageMissBonusPercent={};
    request.attack=readAttackDamage(pvf.script("monster/goblin/attackinfo/attack1.atk"),AttackStatusConsumer::StunHostV1);request.attack.missDeltaPercent=0;
    damagePolicy.rollHit=true;damagePolicy.rollCritical=false;damagePolicy.randomVariation=false;
    Pcg32 search(11,17),zero;bool found=false;
    for(int i=0;i<1000000;++i){auto candidate=search;if(candidate.bounded(10000)==0){zero=search;found=true;break;}search.bounded(10000);}
    check(found,"A deterministic retained PCG boundary vector has next roll exactly0");
    auto raisedRng=zero,neutralRng=zero;const auto raised=resolveDamage(request,damagePolicy,&raisedRng);
    request.attackerStats.attackMissDeltaPercent=0;const auto neutral=resolveDamage(request,damagePolicy,&neutralRng);
    check(raised.usable()&&raised.missed&&raised.hpDamage==0&&neutral.usable()&&!neutral.missed&&*neutral.hpDamage>0,
        "Only real source attacker raw11 delta changes same roll0 into accepted MISS/zero damage");
    check(raisedRng.snapshot()==neutralRng.snapshot(),"Changing source miss outcome retains the same one-draw RNG progression under disabled variation/critical");
    samples.push_back({{"boundary_with_source",raised.snapshot()},{"boundary_neutral",neutral.snapshot()}});
    for(const int level:{25,50}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);
        world.combat=true;world.freezeAi=false;world.mapWidth=1200;world.walkRects={{0,240,1200,240}};
        world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
        Actor actor;actor.id=1;actor.monsterPath=source.monster.path;actor.x=actor.px=605;actor.y=actor.py=344;actor.dir=-1;
        world.initializeMonsterAttributes(actor,level,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
        actor.hp-=1;const int damagedHp=actor.hp;
        const auto encoded=saveActor(actor,world.nowMs());auto decoded=loadActor(encoded,world.nowMs());world.restoreMonsterAttributes(decoded);
        check(decoded.hp==damagedHp&&decoded.combatAttributes&&decoded.combatAttributes->snapshot()==actor.combatAttributes->snapshot(),
            "Actual saveActor/loadActor/World restore preserves damaged HP and exact high-level frozen combat inputs");
        world.monsters.push_back(std::move(decoded));const int before=world.player.hp;bool contacted=false;
        for(int i=0;i<240&&!contacted;++i){world.advance(16666667);const auto report=world.statReport();
            contacted=report.contains("last_damage")&&report["last_damage"].contains("sources")&&
                report["last_damage"]["sources"].contains("attacker")&&
                report["last_damage"]["sources"]["attacker"].value("adapter",std::string())=="inferred-monster-damage-input-v1";}
        check(contacted,"Actual high-level source monster AI/ANI attack makes real incoming World contact");
        const auto live=world.statReport().at("last_damage");const float expected=delta(expectedRaw(source,level));
        check(live.at("usable")==true&&live.at("sources").at("attacker").at("attack_miss_delta_percent").get<float>()==expected&&
            live.at("sources").at("attacker").at("sources").at("attributes").at("table_attack_miss_source").at("level")==level,
            "Actual World incoming request binds high-level raw11 source receipt to attacker miss input");
        check(world.player.hp==std::max(0,before-live.at("hp_damage").get<int>()),"Incoming World HP equals accepted source damage/MISS result");
        samples.push_back({{"world_level",level},{"damage",live}});
    }
    return {{"status","pass"},{"checks",checks},{"samples",samples},
        {"classification","inferred_beta; source producer and additive reader statically evidenced; protected continuation/full native miss formula pending"}};
}
}
