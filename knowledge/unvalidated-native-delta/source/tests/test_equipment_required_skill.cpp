#include "dnf/storage.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/scene.hpp"
#include "dnf/session.hpp"
#include <chrono>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
CharacterSkillState legacyPermission(const SkillLearningService &learning,CharacterIdentity identity,
    int skill,int ownedLevel,int normalLevel) {
    // Explicit old ownership fixture, never a fabricated source-v1 creation.
    CharacterSkillState old(identity);old.setLearnedLevel({identity.jobId,skill},ownedLevel);
    auto initialized=learning.prepareInitialization(old,normalLevel,SkillInitializationMode::LegacyImport);
    if(!initialized.ok)throw std::runtime_error("Legacy permission fixture: "+initialized.quote.error);
    return initialized.state;
}
Script parserFixture(const std::vector<Field> &fields) {
    Script s;s.path="equipment/fixture/required-skill-shape.equ";s.fields=fields;return s;
}
int addSourceItem(Progression &p,int id) {
    const auto *item=p.item(id);if(!item)throw std::runtime_error("Missing real EQU test source");
    const int index=int(p.state.at("inventory").size()),uid=p.state.at("next_uid").get<int>();
    p.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",item->durability}});
    p.state["next_uid"]=uid+1;return index;
}
Json rootFor(const CharacterSkillState &normal,int level) {
    const std::array<std::string,9> classes={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)},{"future_root","preserve"}};
    root["characters"][0]={{"name","Required skill fixture"},{"class",classes.at(normal.identity().jobId)},
        {"identity",normal.identity().json()},{"level",level},{"skill_state",normal.snapshot(0)},
        {"future_character",Json::array({4,3,4})}};
    return root;
}
Json live(const World &w,const Progression &p) {
    auto snapshot=w.snapshot();snapshot["stats"].erase("last_equipment_change");
    return {{"world",snapshot},{"simulation",w.simulationCheckpoint()},{"normal",w.skillState().snapshot(w.nowMs())},
        {"progression",p.state},{"events",w.eventLog()},{"inputs",w.inputs()}};
}
void rest(World &w) {
    w.combat=false;w.releaseInputs();w.player.animation="stay";w.player.animationPath.clear();
    w.player.z=w.player.vx=w.player.vy=w.player.vz=0;w.player.dead=false;w.player.life=ActorLife::Alive;
}
Scene trainer(const World &w) {
    Scene s;MapNpc n;n.id=w.advancementCatalog().trainerId();n.source=w.advancementCatalog().trainerPath();
    n.visible=true;n.x=w.player.x;n.y=w.player.y;s.npcs.push_back(n);return s;
}
Json town(const World &w) {
    return {{"schema",3},{"location","town"},{"player",saveActor(w.player,w.nowMs())},
        {"reward_ledger",{{"permission-fixture","preserved"}}}};
}
// The real 30200 also has unsupported conditional stun effects. Keep the real
// member and its result below. This isolated in-memory cache fixture removes
// those effects solely to exercise the World success/restore/GSD plumbing.
// No PVF, original EQU or runtime support gate is rewritten by the fixture.
struct PlainPermissionFixture {
    Progression &owner;
    ItemDefinition original;
    explicit PlainPermissionFixture(Progression &p):owner(p),original(*p.item(30200)) {
        auto *item=const_cast<ItemDefinition *>(p.item(30200));
        auto &s=item->source;
        const auto end=std::find_if(s.fields.begin(),s.fields.end(),[](const Field &f){return normalize(f.tag)=="[if]";});
        s.fields.erase(end,s.fields.end());
        s.path="equipment/fixture/plain-required34-world.equ";
        size_t offset=2;
        for(auto &f:s.fields){f.offset=offset;offset+=5*(1+f.values.size());}
        s.rawBytes.assign(offset,0);s.tokens=Json::array();
        s.source={{"package_identity",original.source.source.at("package_identity")},
            {"literal_path",s.path},{"member_sha256",sha256(s.rawBytes)},
            {"test_fixture",true},{"origin_member",original.source.path},
            {"origin_sha256",sha256(original.source.rawBytes)},
            {"scope","synthetic no-effect transaction fixture; not the original EQU or production support"}};
        item->path=s.path;item->requiredSkill=parseEquipmentSkillRequirement(s);
    }
    // commitPrepared swaps whole definition maps. Resolve the current cache
    // member again instead of keeping a pointer invalidated by that swap.
    ~PlainPermissionFixture(){*const_cast<ItemDefinition *>(owner.item(30200))=std::move(original);}
};
}

Json runEquipmentRequiredSkillTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool good,const std::string &message) {
        if(!good)throw std::runtime_error("Required equipment skill: "+message);checks.push_back(message);
    };
    const auto rejects=[&](const std::function<void()> &run,const std::string &needle) {
        try{run();}catch(const std::exception &e){return std::string(e.what()).find(needle)!=std::string::npos;}return false;
    };
    const auto real=pvf.script("equipment/character/fighter/weapon/boxglove/bglove_waprrentice.equ");
    const auto originalBytes=pvf.read(real.path);const auto parsed=parseEquipmentSkillRequirement(real);
    check(parsed.valid&&parsed.present&&parsed.skillId==34&&parsed.fieldOffset==487,
        "Actual30200 parses one ID34 at byte487, not an ID/level pair");
    for(const auto &name:{"equipment/character/fighter/weapon/boxglove/102040039.equ",
        "equipment/character/mage/weapon/broom/106040050.equ","equipment/character/fighter/weapon/boxglove/102040048.equ"}) {
        const auto source=pvf.script(name);const auto requirement=parseEquipmentSkillRequirement(source);
        check(requirement.valid&&requirement.present&&requirement.skillId>=0,
            "Actual top-level requirement after closed conditional blocks remains visible: "+source.path);
    }
    check(parseEquipmentSkillRequirement(parserFixture({})).valid&&
        !parseEquipmentSkillRequirement(parserFixture({})).present,"Absent required-skill field is unconditioned");
    check(parseEquipmentSkillRequirement(parserFixture({{"[required skill]",Json::array({-1}),2}})).valid,
        "Official-sample -1 is an explicit no-additional-requirement sentinel");
    check(parseEquipmentSkillRequirement(parserFixture({{"[required skill]",Json::array({0}),2}})).skillId==0,
        "ID zero remains an own registration lookup, never an implicit no-requirement sentinel");
    for(const auto &bad:{Json::array(),Json::array({34,1}),Json::array({34.0}),Json::array({-2}),
        Json::array({uint64_t(INT32_MAX)+1}),Json::array({"34"})})
        check(!parseEquipmentSkillRequirement(parserFixture({{"[required skill]",bad,2}})).valid,
            "Malformed required-skill shape rejects exact input "+bad.dump());
    check(!parseEquipmentSkillRequirement(parserFixture({{"[required skill]",Json::array({34}),2},
        {"[required skill]",Json::array({34}),12}})).valid,"Repeated requirement tags do not select the first");
    for(const auto &scope:{"[if]","[then]","[pvp]","[dungeon]","[ability]"})
        check(!parseEquipmentSkillRequirement(parserFixture({{scope,Json::array(),2},
            {"[required skill]",Json::array({34}),7}})).valid,"Nested/unclosed requirement rejects: "+std::string(scope));
    check(!parseEquipmentSkillRequirement(parserFixture({{"[unknown mode]",Json::array(),2},
        {"[required skill]",Json::array({34}),7},{"[/unknown mode]",Json::array(),17}})).valid,
        "Unknown explicitly paired source scope cannot turn a nested requirement into common data");

    CharacterCatalog characters(pvf);SkillLearningService learning(pvf,characters);
    auto owned=legacyPermission(learning,{1,2,0},34,1,18);
    auto missing=legacyPermission(learning,{1,2,0},34,0,18);
    EquipmentSkillContext yes{&learning,&owned,0},no{&learning,&missing,0};
    const auto sourcePermission=learning.equipmentPermissionEligibility(owned,{1,34},18);
    check(sourcePermission.allowed()&&sourcePermission.requiredCharacterLevel==0&&sourcePermission.learnedLevel==1,
        "Explicit LegacyImport normal own34 satisfies source fitness without inventing an absent SKL required-level");
    check(requireEquipmentSkillQualification(real,{1,2,0},18,&yes).at("status")=="qualified",
        "Actual30200 required-skill permission passes for normal-own34 g2 independently of other equipment effects");
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},18,&no);},"Normal ledger does not own"),
        "Normal level zero cannot satisfy permission");
    auto selfGrant=real;selfGrant.fields.push_back({"[skill levelup]",Json::array({"[fighter]",34,1}),0});
    check(rejects([&]{requireEquipmentSkillQualification(selfGrant,{1,2,0},99,&no);},"Normal ledger does not own"),
        "Synthetic injected equipment skill bonus cannot make an unowned normal permission authorize itself");
    CharacterSkillState uninitialized({1,2,0});uninitialized.setLearnedLevel({1,34},1);
    EquipmentSkillContext rawContext{&learning,&uninitialized,0};
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},18,&rawContext);},"Missing learning metadata"),
        "Raw learned number without source-bound normal learning history is insufficient");
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},18);},"context is required"),
        "No normal ledger context fails closed for restricted equipment");
    auto base=legacyPermission(learning,{1,0,0},34,1,18);EquipmentSkillContext baseContext{&learning,&base,0};
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,0,0},18,&baseContext);},"Neither source learning dimension"),
        "Preserved legacy ownership cannot bypass source growtype fitness");
    auto male=legacyPermission(learning,{7,2,0},34,1,18);EquipmentSkillContext maleContext{&learning,&male,0};
    check(requireEquipmentSkillQualification(real,{7,2,0},18,&maleContext).at("status")=="qualified",
        "Supplemental male Fighter uses its own registered permission34");
    check(rejects([&]{requireEquipmentSkillQualification(real,{7,2,0},18,&yes);},"another target identity"),
        "A female Fighter normal ledger cannot authorize a male target with the same numeric skill ID");
    auto over=legacyPermission(learning,{1,2,0},34,2,18);
    check(!learning.equipmentPermissionEligibility(over,{1,34},18).allowed(),"Legacy level above source maximum is preserved but unusable as permission");
    auto fake=owned;fake.setLearnedLevel({1,34},0);EquipmentSkillContext tampered{&learning,&fake,0};
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},18,&tampered);},"history"),
        "Changing learned level without normal grant history fails ledger validation");
    SkillLearningTestOverlay overlay;overlay.levels[{1,34}]=1;
    const auto effective=overlay.effectiveState(missing);EquipmentSkillContext testContext{&learning,&effective,0};
    check(rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},99,&testContext);},"Test learning overlay"),
        "Test skill ownership and high effective level cannot authorize normal equipment");
    auto differentSource=real;differentSource.source["package_identity"]="other-package";
    check(rejects([&]{requireEquipmentSkillQualification(differentSource,{1,2,0},18,&yes);},"different or invalid identities"),
        "Equipment/normal-ledger package mismatch rejects without changing either source");
    auto broom=legacyPermission(learning,{3,4,0},91,1,15);
    check(learning.equipmentPermissionEligibility(broom,{3,91},15).allowed()&&
        !learning.equipmentPermissionEligibility(broom,{3,91},14).allowed(),
        "Own Mage broom91 consumes its authored required15 instead of applying glove absence policy globally");

    RegionCatalog regions(pvf,assets);Progression inv(regions);inv.initialize(18);
    inv.state["inventory"]=Json::array();inv.state["equipped"]=Json::object();
    const int index=addSourceItem(inv,30200);const auto beforeInv=inv.state;
    check(!inv.equip(index,characters.at(1)).ok&&inv.state==beforeInv,
        "Bare Progression equip with no normal authority rejects real required34 and preserves inventory");
    check(inv.equip(index,characters.at(1),yes).ok&&inv.equippedIndex("[weapon]")==index,
        "Inventory-level real30200 equip accepts exact normal-own34; full World effect support remains separate");
    inv.state=beforeInv;inv.state["level"]=17;
    check(!inv.equip(index,characters.at(1),yes).ok&&inv.state.at("equipped").empty(),
        "Normal equip minimum18 is independent of source permission and debug levels");

    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto out=std::filesystem::absolute(std::filesystem::path("cache/equipment-required-skill-tests")/std::to_string(stamp));
    CharacterStore store(out/"normal","equipment-required-skill-fixture");store.data=rootFor(owned,18);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression p(regions);
    store.apply(0,world,p);rest(world);const int glove=addSourceItem(p,30200);
    const auto fullBefore=live(world,p);const auto realRejected=world.changeEquipment(p,glove);
    const auto realDiagnostic=world.statReport().at("last_equipment_change");
    check(!realRejected.ok&&live(world,p)==fullBefore&&
        realDiagnostic.value("error",std::string()).find("combat_equipment_effect_consumer_required")!=std::string::npos,
        "Actual30200 permission passes but unsupported conditional stun still rejects the complete World equip atomically");
    store.capture(0,world,p);const auto realUnequipped=store.data;
    store.data["characters"][0]["progression"]["equipped"]["[weapon]"]=p.state.at("inventory").at(glove).at("uid");
    const auto restoreBefore=live(world,p);
    check(rejects([&]{store.apply(0,world,p);},"combat_equipment_effect_consumer_required")&&live(world,p)==restoreBefore,
        "Actual30200 saved outfit with valid permission still rejects its unsupported effects before live restore");
    store.data=realUnequipped;
    {
        PlainPermissionFixture synthetic(p);const auto snapshot=world.skillState().snapshot(world.nowMs());
        check(world.changeEquipment(p,glove).ok&&world.skillState().snapshot(world.nowMs())==snapshot,
            "Explicit SYNTHETIC no-effect EQU exercises World success without granting or charging a permission skill");
        const auto baseAttributes=world.prepareBaseAttributes(world.identity(),18);
        const auto authority=world.normalEquipmentSkillContext();
        check(!evaluateCharacterSpeeds(baseAttributes,p,world.characterSource(),CharacterSpeedPolicy::inferredFlatEquipmentV1()).usable()&&
            evaluateCharacterSpeeds(baseAttributes,p,world.characterSource(),CharacterSpeedPolicy::inferredFlatEquipmentV1(),&authority).usable(),
            "Direct speed evaluator requires the same normal authority for restricted synthetic source");
        check(!evaluateEquipmentResourceAttributes(baseAttributes,p,world.characterSource(),EquipmentResourcePolicy::inferredFlatAndRateV1()).usable()&&
            evaluateEquipmentResourceAttributes(baseAttributes,p,world.characterSource(),EquipmentResourcePolicy::inferredFlatAndRateV1(),&authority).usable(),
            "Direct HPMP evaluator cannot bypass source permission");
        const auto combatPolicy=CombatAttributePolicy::inferredEquipmentCombatStatV1(pvf.script("etc/etcparameter.etc"));
        check(!evaluateCombatAttributes(baseAttributes,p,world.characterSource(),combatPolicy).usable()&&
            evaluateCombatAttributes(baseAttributes,p,world.characterSource(),combatPolicy,&authority).usable(),
            "Direct combat evaluator recognizes the consumed requirement and enforces normal permission");
        DebugOverrides debug;debug.enabled=true;debug.level=1;world.applyDebugOverrides(debug,18);
        check(world.characterLevel==1&&world.skillState().learnedLevel({1,34})==1,
            "Low debug effective level does not remove a normally qualified permission");
        debug.enabled=false;debug.level.reset();world.applyDebugOverrides(debug,18);rest(world);
        store.capture(0,world,p);store.checkpoint();const auto good=store.data;
        World target(pvf,assets,WorldRules::BetaFoundationV1);target.enableExperimentalCharacters();Progression targetP(p);
        store.apply(0,target,targetP);
        check(target.identity()==world.identity()&&target.skillState().learnedLevel({1,34})==1&&targetP.equippedIndex("[weapon]")==glove,
            "SYNTHETIC restore uses target-private normal ownership even though previous live World is an unrelated base Swordman");
        const auto targetBefore=live(target,targetP);store.data["characters"][0]["skill_state"]=missing.snapshot(0);
        check(rejects([&]{store.apply(0,target,targetP);},"Normal ledger does not own")&&live(target,targetP)==targetBefore,
            "Restore cannot borrow live-owned34 for a saved target without34; complete live state rolls back");
        store.data=good;store.data["characters"][0]["identity"]=CharacterIdentity{1,1,0}.json();
        auto wrongBranch=owned.snapshot(0);wrongBranch["identity"]=CharacterIdentity{1,1,0}.json();
        store.data["characters"][0]["skill_state"]=wrongBranch;
        // Only this corrupted-target permission fixture omits optional derived
        // experiment preferences/cooldowns captured from the previous branch.
        // Keep its target ledger, progression and simulation for the actual gate.
        for(const char *field:{"experimental_skill_configuration","experimental_test_skill_configuration",
            "experimental_manual_preview_configuration","experimental_cooldowns"})
            store.data["characters"][0].erase(field);
        check(rejects([&]{store.apply(0,target,targetP);},"Neither source learning dimension")&&live(target,targetP)==targetBefore,
            "Restore checks saved target fitness instead of the previous qualified live branch");
        store.data=good;rest(world);auto scene=trainer(world);CharacterAdvancementTransaction transaction;
        const auto generation=store.generation();const auto old=live(world,p);const auto disk=readFile(store.directory()/"characters.json");
        const CharacterAdvancementRequest request{"required34-wrong-branch",world.identity(),{1,1,0},generation,world.advancementCatalog().trainerId()};
        const auto declined=transaction.submit(store,0,world,p,scene,request,town(world));
        check(!declined.ok&&!transaction.pending()&&store.generation()==generation&&live(world,p)==old&&
            readFile(store.directory()/"characters.json")==disk,
            "GSD rejects incompatible target-private permission before durable write, preserving source branch/ledger/EQU/generation");
        const CharacterAdvancementRequest awaken{"required34-same-branch-awakening",world.identity(),{1,2,1},generation,world.advancementCatalog().trainerId()};
        check(!transaction.submit(store,0,world,p,scene,awaken,town(world)).ok,
            "Permission ownership cannot bypass independent source awakening minimum50");
        check(world.changeEquipment(p,glove,true).ok,"Normally qualified synthetic outfit can be explicitly unequipped");
    }
    // Restore complete real source; the synthetic success never licenses it.
    check(p.item(30200)->source.rawBytes==originalBytes&&pvf.read(real.path)==originalBytes,
        "Synthetic cache guard and all permission tests preserve the complete real30200 bytes");
    store.close();
    {
        // A separate synthetic-success fixture at the actual source awakening
        // level exercises durable failures/retry. It does not grant34 or a1
        // skills and is not a claim that the source glove effects run.
        auto level50=legacyPermission(learning,{1,2,0},34,1,50);
        CharacterStore durable(out/"durable","equipment-required-skill-fixture");durable.data=rootFor(level50,50);
        World current(pvf,assets,WorldRules::BetaFoundationV1);current.enableExperimentalCharacters();Progression dp(regions);
        durable.apply(0,current,dp);rest(current);const int at=addSourceItem(dp,30200);
        PlainPermissionFixture fixture(dp);check(current.changeEquipment(dp,at).ok,"SYNTHETIC source-level50 fixture equips before GSD durability test");
        current.skillState().startCooldown({1,34},current.nowMs(),1700);
        current.randomStreams().stream(RandomDomain::Loot,341).next();
        durable.capture(0,current,dp);durable.checkpoint();const auto generation=durable.generation();
        const auto frozen=live(current,dp);auto scene=trainer(current);
        const CharacterAdvancementRequest awaken{"required34-a1-fault",current.identity(),{1,2,1},generation,current.advancementCatalog().trainerId()};
        CharacterAdvancementTransaction tx;
        durable.setFailureInjector([](SaveFailurePoint point){if(point==SaveFailurePoint::BeforePublish)throw std::runtime_error("permission-save-fault");});
        const auto pending=tx.submit(durable,0,current,dp,scene,awaken,town(current));
        check(pending.state==CharacterAdvancementState::Pending&&tx.pending()&&durable.hasPendingCommit()&&
            durable.generation()==generation&&live(current,dp)==frozen,
            "SYNTHETIC compatible target permission is privately prepared; durable fault keeps identity/EQU/ledger/CD/RNG frozen");
        durable.setFailureInjector({});const auto resumed=tx.retry(durable,current);
        check(resumed.ok&&durable.generation()==generation+1&&current.identity()==CharacterIdentity{1,2,1}&&
            current.skillState().learnedLevel({1,34})==1&&current.skillState().remainingCooldown({1,34},current.nowMs())==1700,
            "SYNTHETIC GSD retry publishes exactly one target generation without regranting34 or resetting its ledger/CD");
        const auto committed=live(current,dp);const auto replay=tx.submit(durable,0,current,dp,scene,awaken,town(current));
        check(replay.ok&&replay.state==CharacterAdvancementState::Replayed&&durable.generation()==generation+1&&live(current,dp)==committed,
            "Repeated compatible request replays its durable receipt without another equipment or skill mutation");
        World reloaded(pvf,assets,WorldRules::BetaFoundationV1);reloaded.enableExperimentalCharacters();Progression rp(dp);
        durable.apply(0,reloaded,rp);
        check(reloaded.identity()==current.identity()&&reloaded.skillState().snapshot(reloaded.nowMs())==current.skillState().snapshot(current.nowMs())&&rp.state==dp.state,
            "SYNTHETIC committed identity/permission/outfit/CD restore from the same durable generation");
        durable.close();
    }
    {
        // Actual SKL costs and service.prepare generate every purchase/receipt.
        // These explicit test hosts bind source rules, not production combat
        // consumers. LegacyImport supplies only stated old ownership34=1.
        auto spDebt=legacyPermission(learning,{1,2,0},34,1,99);
        const auto host=[&](SkillKey key) {
            const auto &definition=characters.skillDefinition(key);
            return RuntimeSkillPolicy{key,definition.kind,true,true,100};
        };
        for(int level=1;level<=48;++level) {
            const auto revision=learning.budget(spDebt,99,1000).revision;
            const auto paid=learning.prepare(spDebt,99,host({1,6}),
                {"required34-sp-lowkick-"+std::to_string(level),{1,6},revision,level},1000);
            check(paid.ok,"Real source LowKick SP purchase "+std::to_string(level)+" prepares its actual receipt");
            spDebt=paid.state;
        }
        const auto crouch=learning.prepare(spDebt,99,host({1,2}),
            {"required34-sp-crouch",{1,2},learning.budget(spDebt,99,1000).revision,1},1000);
        check(crouch.ok,"Real source Crouch50SP completes a history over the normal18 budget");spDebt=crouch.state;
        spDebt.startCooldown({1,34},1000,1700);const auto savedDebt=spDebt.snapshot(1000);
        const auto budget18=learning.budget(spDebt,18,1000);
        const auto permission18=learning.equipmentPermissionEligibility(spDebt,{1,34},18,1000);
        const EquipmentSkillContext debtContext{&learning,&spDebt,1000};
        check(budget18.earnedSp==750 && budget18.spentSp==770 && budget18.remainingSp==-20 &&
            budget18.remainingTp==0 && permission18.gate==SkillLearningGate::BudgetConflict,
            "Actual source48x15+50 purchase history yields normal18 SP debt20 and required34 rejects BudgetConflict");
        check(learning.equipmentPermissionEligibility(spDebt,{1,34},99,1000).allowed() &&
            rejects([&]{requireEquipmentSkillQualification(real,{1,2,0},18,&debtContext);},"Existing purchases exceed current normal point budget") &&
            spDebt.snapshot(1000)==savedDebt && spDebt.remainingCooldown({1,34},1000)==1700,
            "Only current normal budget changes acceptance; required-skill preflight preserves exact ownership, paid receipts and cooldown");
        auto tpSeed=CharacterSkillState({1,2,0});tpSeed.setLearnedLevel({1,34},1);tpSeed.setLearnedLevel({1,4},10);
        const auto imported=learning.prepareInitialization(tpSeed,55,SkillInitializationMode::LegacyImport,1000);
        check(imported.ok,"Explicit legacy TP fixture preserves own34 and actual source prerequisite CrashLowKick4 level10");
        const auto tpPaid=learning.prepare(imported.state,55,host({1,214}),
            {"required34-tp-crashlowkick-1",{1,214},learning.budget(imported.state,55,1000).revision,1},1000);
        check(tpPaid.ok,"Actual TP214 source qualification and 2TP cost prepare one normal purchase receipt");
        const auto tpBefore=tpPaid.state.snapshot(1000);const auto tp18=learning.budget(tpPaid.state,18,1000);
        const auto tpPermission=learning.equipmentPermissionEligibility(tpPaid.state,{1,34},18,1000);
        check(tp18.spentSp==0 && tp18.remainingSp==750 && tp18.earnedTp==0 && tp18.spentTp==2 && tp18.remainingTp==-2 &&
            tpPermission.gate==SkillLearningGate::BudgetConflict &&
            learning.equipmentPermissionEligibility(tpPaid.state,{1,34},55,1000).allowed() && tpPaid.state.snapshot(1000)==tpBefore,
            "Independent negative TP rejects glove permission while positive SP and identical normal ownership remain unchanged");
        for(const auto &debt:std::vector<std::pair<std::string,CharacterSkillState>>{{"sp",spDebt},{"tp",tpPaid.state}}) {
            CharacterStore budgetStore(out/("budget-"+debt.first),"equipment-required-skill-budget-fixture");
            budgetStore.data=rootFor(debt.second,18);budgetStore.data["characters"][0]["skill_state"]=debt.second.snapshot(1000);
            World budgetWorld(pvf,assets,WorldRules::BetaFoundationV1);budgetWorld.enableExperimentalCharacters();Progression budgetP(regions);
            budgetStore.apply(0,budgetWorld,budgetP);rest(budgetWorld);const int gloveAt=addSourceItem(budgetP,30200);
            budgetWorld.randomStreams().stream(RandomDomain::Loot,341).next();
            budgetStore.capture(0,budgetWorld,budgetP);budgetStore.checkpoint();
            const auto liveBefore=live(budgetWorld,budgetP);const auto generation=budgetStore.generation();
            const auto disk=readFile(budgetStore.directory()/"characters.json");
            const auto rejected=budgetWorld.changeEquipment(budgetP,gloveAt);
            check(!rejected.ok && live(budgetWorld,budgetP)==liveBefore && budgetStore.generation()==generation &&
                readFile(budgetStore.directory()/"characters.json")==disk &&
                budgetWorld.statReport().at("last_equipment_change").value("error",std::string()).find("budget_conflict")!=std::string::npos,
                "Negative "+debt.first+" actual World equip rejects specifically at permission budget and preserves ledger/CD/RNG/progression/save generation");
            budgetStore.close();
        }
        auto pointBalanced=spDebt;
        const auto reward=learning.preparePointReward(pointBalanced,18,"required34-cover-sp-debt",budget18.revision,20,0,
            {{"kind","explicit-test-point-reward"},{"note","does not alter source spending or skill ownership"}},1000);
        check(reward.ok && learning.budget(reward.state,18,1000).remainingSp==0 &&
            learning.equipmentPermissionEligibility(reward.state,{1,34},18,1000).allowed(),
            "Exactly zero normal remaining SP is accepted; actual point reward does not alter purchases or source permission ownership");
        const auto tpZero=learning.preparePointReward(tpPaid.state,18,"required34-cover-tp-debt",tp18.revision,0,2,
            {{"kind","explicit-test-point-reward"},{"note","zero-boundary lifecycle fixture only"}},1000);
        check(tpZero.ok&&learning.budget(tpZero.state,18,1000).remainingTp==0,
            "Actual two-point test reward balances only TP debt without rewriting its purchase");
        for(const auto &entry:std::vector<std::pair<std::string,CharacterSkillState>>{
            {"negative-sp",spDebt},{"negative-tp",tpPaid.state},{"zero-sp",reward.state},{"zero-tp",tpZero.state}}) {
            const bool allowed=entry.first.rfind("zero-",0)==0;
            CharacterStore lifecycle(out/("budget-lifecycle-"+entry.first),"equipment-budget-lifecycle-fixture");
            lifecycle.data=rootFor(entry.second,18);lifecycle.data["characters"][0]["skill_state"]=entry.second.snapshot(1000);
            World current(pvf,assets,WorldRules::BetaFoundationV1);current.enableExperimentalCharacters();Progression currentP(regions);
            lifecycle.apply(0,current,currentP);rest(current);const int at=addSourceItem(currentP,30200);
            // The existing explicit synthetic fixture isolates permission from real30200's unsupported stun.
            PlainPermissionFixture fixture(currentP);current.randomStreams().stream(RandomDomain::Loot,341).next();
            lifecycle.capture(0,current,currentP);lifecycle.checkpoint();const auto bare=lifecycle.data;
            auto savedOutfit=bare;savedOutfit["characters"][0]["progression"]["equipped"]["[weapon]"]=
                currentP.state.at("inventory").at(at).at("uid");lifecycle.data=savedOutfit;
            const auto restoreLive=live(current,currentP);const auto restoreGeneration=lifecycle.generation();
            const auto restoreDisk=readFile(lifecycle.directory()/"characters.json");
            if(allowed) {
                lifecycle.apply(0,current,currentP);
                check(currentP.equippedIndex("[weapon]")==at&&current.skillState().snapshot(current.nowMs())==entry.second.snapshot(1000)&&
                    current.skillLearningBudget(false,18).remainingSp>=0&&current.skillLearningBudget(false,18).remainingTp>=0,
                    entry.first+": zero boundary permits actual saved-target restore with exact normal ledger/CD");
            }else check(rejects([&]{lifecycle.apply(0,current,currentP);},"budget_conflict")&&live(current,currentP)==restoreLive,
                entry.first+": actual saved-outfit restore rejects specifically at budget before live publication");
            check(lifecycle.data==savedOutfit&&lifecycle.generation()==restoreGeneration&&!lifecycle.hasPendingCommit()&&
                readFile(lifecycle.directory()/"characters.json")==restoreDisk,
                entry.first+": restore keeps complete target root, durable bytes and generation unchanged");
            // Prepare a bare base identity, then inject ONLY a target-private outfit input.
            // This never claims that an unadvanced actor can normally wear the glove.
            auto base=rootFor(entry.second,18);base["characters"][0]["skill_state"]=entry.second.snapshot(1000);
            base["characters"][0]["progression"]=bare.at("characters")[0].at("progression");
            base["characters"][0]["identity"]=CharacterIdentity{1,0,0}.json();
            base["characters"][0]["skill_state"]["identity"]=CharacterIdentity{1,0,0}.json();
            lifecycle.data=base;lifecycle.apply(0,current,currentP);rest(current);
            lifecycle.capture(0,current,currentP);lifecycle.checkpoint();
            currentP.state["equipped"]["[weapon]"]=currentP.state.at("inventory").at(at).at("uid");
            const auto gsdLive=live(current,currentP),gsdRoot=lifecycle.data;
            const auto gsdGeneration=lifecycle.generation();const auto gsdDisk=readFile(lifecycle.directory()/"characters.json");
            const auto unchanged=[&] {return live(current,currentP)==gsdLive&&lifecycle.data==gsdRoot&&
                lifecycle.generation()==gsdGeneration&&!lifecycle.hasPendingCommit()&&
                readFile(lifecycle.directory()/"characters.json")==gsdDisk;};
            if(allowed) {
                auto prepared=current.prepareCharacterAdvancement({1,2,0},currentP);
                check(bool(prepared)&&unchanged(),entry.first+": source-legal target GSD privately prepares at zero budget without publication");
            }else {
                check(rejects([&]{current.prepareCharacterAdvancement({1,2,0},currentP);},"budget_conflict")&&unchanged(),
                    entry.first+": direct source-legal target GSD preparation rejects budget atomically");
                CharacterAdvancementTransaction tx;const auto scene=trainer(current);
                const CharacterAdvancementRequest request{"required34-"+entry.first,current.identity(),{1,2,0},gsdGeneration,
                    current.advancementCatalog().trainerId()};
                const auto result=tx.submit(lifecycle,0,current,currentP,scene,request,town(current));
                check(!result.ok&&result.state==CharacterAdvancementState::Rejected&&!tx.pending()&&
                    result.error.find("budget_conflict")!=std::string::npos&&unchanged(),
                    entry.first+": actual GSD submit rejects budget before pending/save and preserves full live/root/disk/generation");
            }
            lifecycle.close();
        }
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"real30200_world_rejection",realDiagnostic},
        {"scope","source permission + normal ledger + target-private restore/GSD; synthetic no-effect World success is test preparation only"},
        {"not_claimed",Json::array({"real30200 complete equipment support","branch skill grant or legacy refill migration","235 required34 items wearable","native server parity"})}};
}
} // namespace dnf
