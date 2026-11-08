#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include <stdexcept>

namespace dnf {
Json runMonsterAccuracyTests(Pvf &pvf,Assets &assets) {
    int checks=0;Json samples=Json::array();
    auto check=[&](bool value,const std::string &message){++checks;if(!value)throw std::runtime_error("Monster accuracy: "+message);};
    const auto policy=MonsterCombatAttributePolicy::inferredMobCombatTableV1();
    const std::string mob="monster/act8/crokhan_spearman/crokhan_spearman.mob";
    const auto source=readMonsterAttributeSource(pvf,mob,false);
    const auto evaluated=evaluateMonsterCombatAttributes(source,1,false,policy);
    check(evaluated.usable(),"The real source spearman accepts its nonzero authored stuckbonus at the explicit diagnostic level1");
    check(evaluated.attributes->damageMissBonusPercent==std::array<double,2>{10,10},"Actual four source10 operands become melee/ranged10percent");
    const auto saved=evaluated.snapshot();
    check(restoreMonsterCombatAttributes(saved,source).snapshot()==saved,"Frozen nonzero bonus restores without rerunning attribute/HP evaluation");
    for(int alteration=0;alteration<8;++alteration) {
        auto bad=saved;
        if(alteration==0)bad["attributes"]["damage_miss_bonus_percent"]=Json::array({101,10});
        if(alteration==1)bad["attributes"].erase("damage_miss_bonus_source");
        if(alteration==2){bad["attributes"].erase("damage_miss_bonus_source");bad["attributes"].erase("damage_miss_bonus_percent");}
        if(alteration==3){bad["attributes"]["damage_miss_bonus_source"]=Json::object();bad["attributes"]["damage_miss_bonus_percent"]=Json::array({0,0});}
        if(alteration==4)bad["attributes"]["damage_miss_bonus_source"]["level"]=2;
        if(alteration==5)bad["attributes"]["damage_miss_bonus_source"]["source_level_range"]=Json::array({1,2});
        if(alteration==6)bad["attributes"]["damage_miss_bonus_source"]["classification"]="native_confirmed";
        if(alteration==7)bad["attributes"]["damage_miss_bonus_source"]["endpoints_ranged_then_melee"]=Json::array({0,0,0,0});
        bool rejected=false;try{restoreMonsterCombatAttributes(bad,source);}catch(const std::exception&){rejected=true;}
        check(rejected,"Malformed or source-erasing nonzero frozen bonus is rejected before publication");
    }
    const auto goblinSource=readMonsterAttributeSource(pvf,"monster/goblin/goblin.mob",false);
    const auto goblin=evaluateMonsterCombatAttributes(goblinSource,1,false,policy);auto legacy=goblin.snapshot();
    legacy["attributes"].erase("damage_miss_bonus_source");legacy["attributes"].erase("damage_miss_bonus_percent");
    const auto restoredLegacy=restoreMonsterCombatAttributes(legacy,goblinSource);
    check(restoredLegacy.usable()&&restoredLegacy.attributes->damageMissBonusPercent==std::array<double,2>{},
        "Historical neutral receipts remain readable under the old no-recomputation contract");
    auto diagnostic=source;
    diagnostic.monster.path="diagnostic/source-stuckbonus.mob";
    diagnostic.monster.tokens.clear();diagnostic.monster.rawBytes.resize(52,0);
    diagnostic.monster.fields={{"[level]",Json::array({1,3}),2},{"[stuckbonus on damage]",Json::array({10,30,2,6}),17}};
    const auto mid=evaluateMonsterCombatAttributes(diagnostic,2,false,policy);
    check(mid.usable()&&mid.attributes->damageMissBonusPercent==std::array<double,2>{4,20},
        "Explicit diagnostic four-endpoint source interpolates separate ranged and melee values in source order");
    for(const auto &invalid:std::vector<Json>{Json::array({1,2}),Json::array({1,2,3}),Json::array({-1,0,0,0}),Json::array({0,101,0,0}),Json::array({0,"x",0,0})}) {
        auto bad=diagnostic;bad.monster.fields[1].values=invalid;
        check(!evaluateMonsterCombatAttributes(bad,2,false,policy).usable(),"Malformed/nonpercentage four-endpoint source is not silently neutralized");
    }
    auto damagePolicy=DamageResolutionPolicy::inferredPveDamageV1(pvf.script("etc/etcparameter.etc"));
    // The real World exposes the exact source constants via its prepared stats.
    RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);Progression progress(catalog);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progress);
    // These constants have the same immutable content identity as the actors.
    DamageRequest request;request.attacker=EntityHandle{1,1};request.target=EntityHandle{2,1};request.attackInstance=1;
    request.attackerStats=makeDamageCombatant(*world.combatAttributes());
    request.targetStats=makeDamageCombatant(mid,damagePolicy);
    request.attack=readAttackDamage(pvf.script("character/swordman/attackinfo/attack1.atk"),AttackStatusConsumer::StunHostV1);
    damagePolicy.randomVariation=false;damagePolicy.rollCritical=false;damagePolicy.rollHit=true;
    Pcg32 rng(1,3);const auto before=rng.snapshot();
    check(!resolveDamage(request,damagePolicy,&rng).usable()&&rng.snapshot()==before,
        "Unknown contact range with asymmetric target bonuses rejects without RNG publication");
    for(auto distance:{DamageContactRange::Melee,DamageContactRange::Ranged}) {
        request.contactRange=distance;request.targetStats.damageMissBonusPercent={0,100};
        Pcg32 roll(7,9);const auto result=resolveDamage(request,damagePolicy,&roll);
        check(result.usable()&&result.missed==(distance==DamageContactRange::Ranged),
            "Real hit-roll distinguishes0percent melee from100percent ranged on the same target");
        samples.push_back(result.snapshot());
    }
    request.contactRange=DamageContactRange::Unknown;request.targetStats.damageMissBonusPercent={100,100};
    check(resolveDamage(request,damagePolicy,&rng).missed,"Equal range bonuses need no guessed distance class");
    for(const auto &[categories,expected]:std::vector<std::pair<Json,DamageContactRange>>{
        {Json::array({"[melee]"}),DamageContactRange::Melee},{Json::array({"[bullet]"}),DamageContactRange::Ranged},
        {Json::array({"[magic]"}),DamageContactRange::Unknown},{Json::array({"[range combat]"}),DamageContactRange::Unknown},
        {Json::array({"[melee]","[bullet]"}),DamageContactRange::Unknown}}) {
        Script object;object.path="diagnostic/category.obj";object.fields={{"[category]",categories,2},{"[/category]",Json::array(),17}};
        bindDamageContactRange(request,object);check(request.contactRange==expected,
            "Explicit object type category is distinct from physical/magical or AI range categories");
    }
    world.combat=true;world.freezeAi=true;world.mapWidth=2000;world.walkRects={{0,200,2000,1000}};
    world.player.x=world.player.px=500;world.player.y=world.player.py=344;world.player.dir=1;
    Actor target;target.id=1;target.monsterPath=mob;target.x=target.px=560;target.y=target.py=344;target.dir=-1;
    world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    const int hp=target.hp;world.monsters.push_back(target);world.normalAttack();
    bool contact=false;
    for(int i=0;i<90&&!contact;++i) {
        world.advance(16666667);const auto stats=world.statReport();
        contact=stats.contains("last_damage")&&stats["last_damage"].contains("trace")&&
            std::any_of(stats["last_damage"]["trace"].begin(),stats["last_damage"]["trace"].end(),[](const Json &row){return row.value("stage",std::string())=="target_stuckbonus_on_damage";});
    }
    check(contact,"Actual normalAttack root ANI collision reaches the source stuckbonus damage consumer in World");
    const auto live=world.statReport().at("last_damage");
    check(live.at("usable")==true&&live.at("sources").at("contact_range").at("selection")=="melee"&&
        live.at("sources").at("target").at("damage_miss_bonus_percent")==Json::array({10.0,10.0}),
        "Actual World request carries its explicit body melee classification and frozen source10percent bonus");
    check(world.monsters.front().hp==std::max(0,hp-live.at("hp_damage").get<int>()),"Actual HP exactly follows the accepted hit/miss receipt");
    samples.push_back(live);
    World gunner(pvf,assets,WorldRules::BetaFoundationV1);gunner.enableExperimentalCharacters();
    CharacterStore store(std::filesystem::absolute("tests/gunner-fixture"));
    store.data["characters"][0]={{"name","SourceAccuracyGunner"},{"class","atgunner"},
        {"identity",CharacterIdentity{5,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
    store.apply(0,gunner,progress);gunner.combat=true;gunner.freezeAi=true;gunner.mapWidth=3000;gunner.walkRects={{0,185,3000,600}};
    gunner.player.x=gunner.player.px=1000;gunner.player.y=gunner.player.py=300;gunner.player.dir=1;
    Actor rangedTarget;rangedTarget.id=1;rangedTarget.monsterPath=mob;rangedTarget.x=rangedTarget.px=1120;rangedTarget.y=rangedTarget.py=300;rangedTarget.dir=-1;
    gunner.initializeMonsterAttributes(rangedTarget,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    const int rangedHp=rangedTarget.hp;gunner.monsters.push_back(rangedTarget);gunner.normalAttack();bool rangedContact=false;
    for(int i=0;i<120&&!rangedContact;++i) {
        gunner.advance(16666667);const auto report=gunner.statReport();
        if(report.contains("last_damage")&&report["last_damage"].contains("sources")) {
            const auto &range=report["last_damage"]["sources"]["contact_range"];
            rangedContact=range.at("selection")=="ranged";
        }
    }
    check(rangedContact,"Actual female-gunner ordinary projectile reaches explicit ranged classification in the unified damage consumer");
    const auto rangedLive=gunner.statReport().at("last_damage");
    check(rangedLive.at("usable")==true&&rangedLive.at("sources").at("contact_range").at("evidence").at("policy")=="inferred-ordinary-bullet-contact-range-v1"&&
        rangedLive.at("sources").at("target").at("damage_miss_bonus_percent")==Json::array({10.0,10.0}),
        "Registered source GunnerDefaultGunInfo projectile carries the frozen source ranged10percent bonus");
    check(gunner.monsters.front().hp==std::max(0,rangedHp-rangedLive.at("hp_damage").get<int>()),
        "Actual ranged HP follows the accepted source hit/miss receipt");
    samples.push_back(rangedLive);
    return {{"status","pass"},{"checks",checks},{"samples",samples},
        {"scope","Actual source spearman level1 diagnostic placement, source endpoints/frozen recovery/hit-roll, real World ordinary attack; statBase27 remains unresolved"}};
}
}
