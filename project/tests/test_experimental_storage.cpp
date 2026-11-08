#include "explicit_skill_preview_fixture.hpp"
#include "dnf/storage.hpp"
#include "dnf/experimental_character.hpp"
#include <chrono>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
Json experimentalStorageRoot() {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)},{"future_root",{{"keep",true}}}};
    root["characters"][0]={{"name","Normal Swordman"},{"class","swordman"},{"identity",CharacterIdentity{0,0,0}.json()},
        {"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
    root["characters"][1]={{"name","Experimental Fighter"},{"class","fighter"},{"identity",CharacterIdentity{1,0,0}.json()},
        {"level",1},{"weapon",0},{"skill_initialization","source-v1"},{"future_character",{{"keep",true}}}};
    return root;
}
Json experimentalStorageWorld(const World &world) {
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},{"events",world.eventLog()},
        {"inputs",world.inputs()},{"normal_skills",world.skillState().snapshot(world.nowMs())},
        {"overlay",world.skillTestOverlay().snapshot()},{"experimental",world.experimentalDiagnostics()},
        {"experimental_configuration",world.experimentalRuntime()?world.experimentalRuntime()->configuration().snapshot():Json()},
        {"experimental_cooldowns",world.experimentalRuntime()?world.experimentalRuntime()->cooldownSnapshot(world.nowMs()):Json()}};
}
void rejectionSentinel(World &world) {
    // Diagnostic mutation sentinels for failed-restore atomicity. These do not
    // claim normal experimental combat or a native skill execution chain.
    world.player.hp=std::max(1,world.player.maxHp-7);
    world.enqueue({world.simulationNanoseconds()+1000000000,1,true});
    world.randomStreams().stream(RandomDomain::Loot).next();
    Effect effect;effect.id=991;effect.phase="experimental-storage-rejection-sentinel";world.effects.push_back(effect);
}
} // namespace

Json runExperimentalStorageTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const std::string &name) {
        if(!okay)throw std::runtime_error("Experimental storage: "+name);checks.push_back(name);
    };
    const auto rejects=[&](auto callback) {try{callback();}catch(const std::exception &){return true;}return false;};
    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/experimental-storage-tests")/std::to_string(stamp));
    CharacterStore store(directory,"experimental-storage-source-test");store.data=experimentalStorageRoot();
    RegionCatalog region(pvf,assets);Progression progression(region);
    World normal(pvf,assets,WorldRules::BetaFoundationV1);
    const auto normalBefore=experimentalStorageWorld(normal),progressionBefore=progression.state;
    check(!normal.supportsCharacter({1,0,0}) && rejects([&]{store.apply(1,normal,progression);}) &&
          experimentalStorageWorld(normal)==normalBefore && progression.state==progressionBefore,
          "Normal candidate does not admit experimental saves or mutate World and Progression before explicit enable");

    {
        CharacterStore legacyStore(directory/"legacy-absent","experimental-storage-source-test");
        legacyStore.data=experimentalStorageRoot();legacyStore.data["characters"][1].erase("skill_initialization");
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression legacyProgression(region);
        legacyStore.apply(1,world,legacyProgression);dnf::enterExplicitSkillPreviewFixture(world);
    const auto emptyConfiguration=world.experimentalRuntime()->configuration().snapshot();
    check(emptyConfiguration.at("skill_bindings").empty() &&
          std::all_of(emptyConfiguration.at("slots").begin(),emptyConfiguration.at("slots").end(),[](const Json &slot){return slot.is_null();}),
          "Absent experimental configuration creates an explicit empty same-job configuration without guessed skill bindings");
        legacyStore.close();
    }

    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    store.apply(1,world,progression);dnf::enterExplicitSkillPreviewFixture(world);
    check(world.identity()==CharacterIdentity{1,0,0} && world.isExperimentalCharacter() && world.experimentalRuntime() &&
          world.skills.empty() && world.passives.empty() &&
          std::all_of(world.bindings.begin(),world.bindings.end(),[](int value){return value==-1;}),
          "Real CharacterStore selection installs the Fighter runtime with empty Swordman skill views and unbound normal hotbar");
    check(progression.state.at("inventory").size()==1 && progression.state.at("inventory")[0].at("id")==29000 &&
          progression.state.at("equipped").at("[weapon]")==progression.state.at("inventory")[0].at("uid") &&
          progression.attackBonus()>0 && world.combatAttributes() && world.combatAttributes()->physicalAttack>0 &&
          world.combatAttributes()->magicalAttack>0 && progression.state.at("experimental_starter").at("policy")=="user-experimental-sd-default-weapon-v1",
          "A new Fighter receives its own SD-qualified source glove through the named user experiment and unified equipment attributes, without the Swordman starter");
    const auto initialConfiguration=world.experimentalRuntime()->configuration().snapshot();
    const SkillKey freeUpper{1,5};const auto *initialUpper=world.experimentalRuntime()->configuration().binding(freeUpper);
    check(world.skillState().learnedLevel(freeUpper)==1 && initialUpper && initialUpper->key==freeUpper && initialUpper->level==1 &&
          initialUpper->unknown.at("source_body_action_controller")==world.experimentalRuntime()->plan().sourceSkillActions.at(freeUpper).snapshot() &&
          initialConfiguration.at("skill_bindings").size()==1 &&
          initialConfiguration.at("skill_bindings")==world.normalSkillConfigurationSnapshot().at("skill_bindings") &&
          initialConfiguration.at("slots").size()==13 &&
          std::all_of(initialConfiguration.at("slots").begin(),initialConfiguration.at("slots").end(),[](const Json &slot){return slot.is_null();}),
          "Source-v1 absent explicit configuration projects only actual free own Upper1 and never guesses user slots");

    const auto &plan=world.experimentalRuntime()->plan();const ExperimentalSkillRow *selectedSkill=nullptr;
    for(const auto &[key,row]:plan.skills)if(row.kind==SkillSourceKind::Active && row.data && world.skillState().learnedLevel(key)==0) {
        const auto cost=evaluateCharacterSkillCosts(*row.data,1,plan.characterDefinition,-1,false,{}, {},inferred1031SkillCostAbsencePolicy());
        if(cost.consumeMp() && *cost.consumeMp()>0 && *cost.consumeMp()<world.player.mp &&
           cost.cooldownMs() && *cost.cooldownMs()>100 && *cost.cooldownMs()<=INT32_MAX) {
            selectedSkill=&row;break;
        }
    }
    const ExperimentalSourceBinding *motion=nullptr;
    for(const auto &binding:plan.motions)if(plan.animations.count(binding.source.memberPath)) {
        if(!motion)motion=&binding;if(normalize(binding.tag)=="[attack motion]"){motion=&binding;break;}
    }
    std::optional<ExperimentalSourceBinding> attack;
    for(const auto &binding:plan.attacks) {
        const auto definition=plan.attackDefinitions.find(binding.source.memberPath);
        if(definition!=plan.attackDefinitions.end() && definition->second.usable()){attack=binding;break;}
    }
    check(selectedSkill && motion,"Real Fighter PVF supplies an unlearned active SKL and a decoded same-job CHR motion for the storage fixture");
    const auto normalLedger=world.skillState().snapshot(world.nowMs()),normalOverlay=world.skillTestOverlay().snapshot();
    auto &configuration=world.experimentalRuntime()->configuration();
    configuration.configureBasicAttackTemplate(selectedSkill->key,1,plan);configuration.assignSlot(0,selectedSkill->key,plan);
    check(configuration.binding(selectedSkill->key)->unknown.at("user_requested_temporary_template").at("source_job")==world.identity().jobId &&
          configuration.binding(selectedSkill->key)->motion.json()==plan.motion("[attack motion]")->json() &&
          configuration.binding(selectedSkill->key)->attack->json()==plan.attack("[attack info]")->json(),
          "Temporary Swordman release template binds this job's exact basic CHR/ATK and preserves its user-requested classification");
    configuration.assignSlot(12,selectedSkill->key,plan);
    const auto selectedBinding=[&](Json &value)->Json & {
        Json *selected=nullptr;size_t matches=0;
        for(auto &binding:value.at("skill_bindings"))if(SkillKey::fromJson(binding.at("key"))==selectedSkill->key) {selected=&binding;++matches;}
        if(matches!=1)throw std::runtime_error("Storage fixture requires one exact selected SkillKey binding");return *selected;
    };
    auto configured=configuration.snapshot();configured["future_configuration"]={{"keep","portable source choices"}};
    selectedBinding(configured)["future_binding"]=Json::array({3,"keep"});configuration.restore(configured,plan);
    check(world.skillState().snapshot(world.nowMs())==normalLedger && world.skillTestOverlay().snapshot()==normalOverlay &&
          world.skillState().learnedLevel(selectedSkill->key)==0,
          "Configuring experimental slots, source motion, attack and level does not grant a normal skill or modify learning purchases and test overlay");
    const auto mpBeforeCast=world.player.mp;
    world.enqueue({world.simulationNanoseconds()+1,20,true});world.advanceSingleTick();
    const auto savedCooldown=world.experimentalRuntime()->cooldownSnapshot(world.nowMs());
    check(world.player.mp<mpBeforeCast && world.experimentalRuntime()->remainingCooldown(selectedSkill->key,world.nowMs())>0 &&
          savedCooldown.at("captured_ms")==world.nowMs() && savedCooldown.at("skills").size()==1 &&
          world.skillState().snapshot(world.nowMs())==normalLedger,
          "Actual configured key starts source-evaluated experimental MP and cooldown consumers without writing cooldown into the normal skill ledger");
    store.capture(1,world,progression);const auto saved=store.data.at("characters").at(1);
    check(saved.at("experimental_manual_preview_configuration")==configured && saved.at("experimental_skill_execution_mode")=="manual_preview" && saved.at("experimental_cooldowns")==savedCooldown &&
          saved.at("skill_state")==normalLedger &&
          saved.at("skills").empty() && saved.at("passives").empty() &&
          std::all_of(saved.at("bindings").begin(),saved.at("bindings").end(),[](const Json &slot){return slot==-1;}) &&
          saved.at("future_character").at("keep").get<bool>(),
          "Capture persists experimental choices separately while normal ledger and empty compatibility views retain their own identities");
    store.commit("experimental-source-configuration-roundtrip");const auto generation=store.generation();store.close();
    const auto diskBytes=readFile(directory/"characters.json");
    CharacterStore recovered(directory,"experimental-storage-source-test");
    World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression loadedProgression(region);
    recovered.apply(1,loaded,loadedProgression);
    check(loaded.experimentalRuntime() && loaded.experimentalRuntime()->configuration().snapshot()==configured &&
          loaded.experimentalRuntime()->cooldownSnapshot(loaded.nowMs())==savedCooldown &&
          loaded.skillState().snapshot(loaded.nowMs())==normalLedger && loaded.skillState().learnedLevel(selectedSkill->key)==0 &&
          loadedProgression.state.at("inventory").size()==1 && loadedProgression.state.at("inventory")[0].at("id")==29000 &&
          loadedProgression.state.at("experimental_starter")==progression.state.at("experimental_starter"),
          "Actual disk reload restores same-job source configuration and unknown fields without creating purchases or a replacement starter");
    check(recovered.generation()==generation && readFile(directory/"characters.json")==diskBytes,
          "Applying an experimental save reads the durable generation without rewriting user data or allocating a business receipt");
    const auto restoredMp=loaded.player.mp;
    const auto restoredNow=loaded.nowMs();
    const auto actionBefore=loaded.experimentalRuntime()->snapshotDiagnostics().at("action_sequence");
    const auto remainingBefore=loaded.experimentalRuntime()->remainingCooldown(selectedSkill->key,restoredNow);
    loaded.enqueue({loaded.simulationNanoseconds()+1,7,true});loaded.advanceSingleTick();
    check(loaded.player.mp==restoredMp && !loaded.experimentalRuntime()->attacking() &&
          loaded.experimentalRuntime()->snapshotDiagnostics().at("action_sequence")==actionBefore &&
          loaded.experimentalRuntime()->remainingCooldown(selectedSkill->key,loaded.nowMs())==remainingBefore-(loaded.nowMs()-restoredNow) &&
          loaded.skillState().snapshot(loaded.nowMs())==normalLedger,
          "Actual restored Space binding cannot bypass the persisted cooldown, spend MP or start a new action; only fixed simulation elapsed time reduces it");

    rejectionSentinel(loaded);const auto liveBefore=experimentalStorageWorld(loaded),loadedProgressionBefore=loadedProgression.state;
    const auto validSaved=recovered.data.at("characters").at(1);std::vector<std::pair<std::string,Json>> invalid;
    auto invalidConfiguration=[&](const std::string &label,const Json &value) {
        auto character=validSaved;character["experimental_skill_configuration"]=value;invalid.emplace_back(label,std::move(character));
    };
    auto bad=configured;bad["schema"]=999;invalidConfiguration("schema",bad);
    bad=configured;bad["policy"]="unrecognized-policy";invalidConfiguration("policy",bad);
    bad=configured;bad["pvf_identity"]="foreign-pvf";invalidConfiguration("PVF identity",bad);
    bad=configured;bad["identity"]["job_id"]=0;invalidConfiguration("character identity",bad);
    bad=configured;bad["slots"][0]["job_id"]=0;invalidConfiguration("foreign-job slot",bad);
    bad=configured;bad["slots"].push_back(Json());invalidConfiguration("slot count",bad);
    bad=configured;selectedBinding(bad)["level"]=0;invalidConfiguration("binding level",bad);
    bad=configured;selectedBinding(bad)["skill_source"]["member_sha256"]="bad-skl";invalidConfiguration("SKL digest",bad);
    bad=configured;selectedBinding(bad)["motion"]["source"]["member_sha256"]="bad-ani";invalidConfiguration("ANI digest",bad);
    bad=configured;selectedBinding(bad)["motion"]["slot"]=2147483647;invalidConfiguration("CHR motion slot",bad);
    bad=configured;selectedBinding(bad)["motion"]["occurrence"]=2147483647;invalidConfiguration("CHR field occurrence",bad);
    bad=configured;const auto duplicate=selectedBinding(bad);bad["skill_bindings"].push_back(duplicate);invalidConfiguration("duplicate skill binding",bad);
    bad=configured;bad["weapon_type_policy"]="invented-weapon-type";invalidConfiguration("weapon type policy",bad);
    if(attack) {
        bad=configured;selectedBinding(bad)["attack"]["source"]["member_sha256"]="bad-atk";invalidConfiguration("ATK digest",bad);
    }
    const size_t configurationInvalidCount=invalid.size();
    auto invalidCooldown=[&](const std::string &label,const Json &value) {
        auto character=validSaved;character["experimental_cooldowns"]=value;invalid.emplace_back("cooldown "+label,std::move(character));
    };
    bad=savedCooldown;bad["schema"]=999;invalidCooldown("schema",bad);
    bad=savedCooldown;bad["identity"]["job_id"]=0;invalidCooldown("identity",bad);
    bad=savedCooldown;bad["pvf_identity"]="foreign-pvf";invalidCooldown("PVF",bad);
    bad=savedCooldown;bad["policy"]="foreign-policy";invalidCooldown("policy",bad);
    bad=savedCooldown;bad["captured_ms"]=world.nowMs()+1;invalidCooldown("simulation boundary",bad);
    bad=savedCooldown;bad["skills"][0]["key"]["job_id"]=0;invalidCooldown("foreign key",bad);
    bad=savedCooldown;bad["skills"][0]["key"]["skill_id"]=2147483647;invalidCooldown("unknown key",bad);
    bad=savedCooldown;bad["skills"][0]["skill_source"]["member_sha256"]="bad-skl";invalidCooldown("SKL digest",bad);
    for(const Json &remaining:Json::array({0,-1,int64_t(INT32_MAX)+1,1.5})) {
        bad=savedCooldown;bad["skills"][0]["remaining_ms"]=remaining;invalidCooldown("invalid remaining "+remaining.dump(),bad);
    }
    bad=savedCooldown;const auto duplicateCooldown=bad["skills"][0];bad["skills"].push_back(duplicateCooldown);invalidCooldown("duplicate key",bad);
    invalidCooldown("present null",Json());
    auto missingSimulation=validSaved;missingSimulation.erase("simulation");invalid.emplace_back("cooldown missing simulation",std::move(missingSimulation));
    for(const auto &[label,character]:invalid) {
        recovered.data["characters"][1]=character;
        check(rejects([&]{recovered.apply(1,loaded,loadedProgression);}) && experimentalStorageWorld(loaded)==liveBefore &&
              loadedProgression.state==loadedProgressionBefore && readFile(directory/"characters.json")==diskBytes,
              "Malformed "+label+" is rejected before cancelling the live controller or changing World, RNG, inputs, ledger, Progression and durable bytes");
    }
    for(size_t i=configurationInvalidCount;i<invalid.size();++i) {
        recovered.data["characters"][1]=invalid[i].second;
        check(rejects([&]{recovered.apply(1,loaded);}) && experimentalStorageWorld(loaded)==liveBefore &&
              loadedProgression.state==loadedProgressionBefore && readFile(directory/"characters.json")==diskBytes,
              "Standalone apply privately rejects malformed "+invalid[i].first+" and preserves live state and durable bytes");
    }
    recovered.data["characters"][1]=invalid.front().second;
    check(rejects([&]{recovered.apply(1,loaded);}) && experimentalStorageWorld(loaded)==liveBefore,
          "Standalone CharacterStore apply validates experimental configuration privately before selecting a new incarnation");
    recovered.data["characters"][1]=validSaved;

    auto lostInventory=validSaved;lostInventory["progression"].erase("inventory");
    lostInventory["progression"]["equipped"]=Json::object();recovered.data["characters"][1]=lostInventory;
    check(rejects([&]{recovered.apply(1,loaded,loadedProgression);}) && experimentalStorageWorld(loaded)==liveBefore &&
          loadedProgression.state==loadedProgressionBefore,
          "An existing starter receipt with a missing inventory rejects restoration instead of issuing a replacement weapon");
    recovered.data["characters"][1]=validSaved;

    // Preserved explicit inventories are validated, never silently filtered or
    // replaced to make an otherwise incompatible equipped item appear usable.
    Progression swordInventory(region);auto badEquipment=validSaved;
    badEquipment["progression"]=swordInventory.state;recovered.data["characters"][1]=badEquipment;
    check(rejects([&]{recovered.apply(1,loaded,loadedProgression);}) && experimentalStorageWorld(loaded)==liveBefore &&
          loadedProgression.state==loadedProgressionBefore,
          "An explicit saved Swordman weapon remains visible and fails Fighter equipment qualification before live mutation");
    auto partialProgression=validSaved;partialProgression["progression"]={{"level",1},{"gold",37},{"future_progression",true}};
    recovered.data["characters"][1]=partialProgression;recovered.apply(1,loaded,loadedProgression);
    check(loadedProgression.gold()==37 && loadedProgression.state.at("future_progression").get<bool>() &&
          loadedProgression.state.at("inventory").size()==1 && loadedProgression.state.at("inventory")[0].at("id")==29000,
          "Partial non-Sword progression preserves its counters and unknown fields while absent inventory receives only its own qualified source starter");
    auto emptyInventory=validSaved;emptyInventory["progression"]["inventory"]=Json::array();
    emptyInventory["progression"]["equipped"]=Json::object();recovered.data["characters"][1]=emptyInventory;
    recovered.apply(1,loaded,loadedProgression);
    check(loadedProgression.state.at("inventory").empty() && loadedProgression.state.at("equipped").empty() &&
          loadedProgression.state.at("experimental_starter")==validSaved.at("progression").at("experimental_starter"),
          "Explicit saved empty inventory remains empty and retains the source starter receipt without a second grant or reroll");

    auto staleViews=experimentalStorageRoot().at("characters").at(1);staleViews.erase("skill_initialization");
    staleViews["skills"]={{"46",99},{"8",77}};staleViews["passives"]={{"basicmastery",99}};
    staleViews["bindings"]=std::vector<int>(13,46);recovered.data["characters"][1]=staleViews;
    recovered.apply(0,loaded,loadedProgression);recovered.apply(1,loaded,loadedProgression);
    const auto migrated=loaded.skillState().snapshot(loaded.nowMs());
    check(migrated.at("skills").empty() && migrated.at("learning").at("grants").empty() &&
          migrated.at("learning").at("purchases").empty() && loaded.skills.empty() && loaded.passives.empty() &&
          std::all_of(loaded.bindings.begin(),loaded.bindings.end(),[](int slot){return slot==-1;}),
          "Switching from Swordman to an experimental legacy save cannot migrate stale Swordman compatibility levels or hotbar slots into the normal ledger");
    recovered.apply(0,loaded,loadedProgression);
    check(!loaded.isExperimentalCharacter() && loaded.identity()==CharacterIdentity{0,0,0} && !loaded.skills.empty() &&
          !loaded.passives.empty() && loadedProgression.state.at("inventory").size()==1 &&
          loadedProgression.state.at("inventory")[0].at("id")==27118 && loaded.skillState().learnedLevel({0,46})==1,
          "Selecting the normal Swordman after an experiment restores its original runtime skill arrays and existing source gift/starter behavior");
    auto normalWithExperiment=recovered.data.at("characters").at(0);normalWithExperiment["experimental_skill_configuration"]=configured;
    normalWithExperiment["experimental_cooldowns"]=savedCooldown;
    recovered.data["characters"][0]=normalWithExperiment;const auto swordBefore=experimentalStorageWorld(loaded),swordProgression=loadedProgression.state;
    check(rejects([&]{recovered.apply(0,loaded,loadedProgression);}) && experimentalStorageWorld(loaded)==swordBefore && loadedProgression.state==swordProgression,
          "A normal controller cannot silently accept a foreign experimental configuration");
    recovered.data["characters"][0].erase("experimental_skill_configuration");
    check(rejects([&]{recovered.apply(0,loaded,loadedProgression);}) && experimentalStorageWorld(loaded)==swordBefore && loadedProgression.state==swordProgression,
          "A normal controller rejects a foreign experimental cooldown field independently of source configuration");
    recovered.capture(0,loaded,loadedProgression);
    check(!recovered.data.at("characters").at(0).contains("experimental_skill_configuration") &&
          !recovered.data.at("characters").at(0).contains("experimental_cooldowns"),
          "Capturing a normal controller clears recognized stale experimental configuration and cooldown fields from that slot");

    // A real legacy Swordman restore occurs while current arrays are empty.
    // Target-specific compatibility views must be used before selectCharacter.
    recovered.data["characters"][1]=validSaved;recovered.apply(1,loaded,loadedProgression);
    auto legacySword=experimentalStorageRoot().at("characters").at(0);legacySword.erase("skill_initialization");
    legacySword["skills"]={{"46",0},{"8",0}};recovered.data["characters"][0]=legacySword;
    recovered.apply(0,loaded,loadedProgression);
    check(loaded.skillState().learnedLevel({0,46})==0 && loaded.skillState().learnedLevel({0,8})==0 &&
          std::any_of(loaded.skills.begin(),loaded.skills.end(),[](const Skill &skill){return skill.id==46 && skill.level==0;}),
          "Legacy normal restore uses target Swordman compatibility views and preserves explicit unlearned levels after leaving empty experimental views");

    Json jobStarters=Json::array();
    const std::array<const char *,10> classes{{"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage","demonicswordman"}};
    const std::array<int,10> expectedWeapons{{27118,29000,31000,33679,35000,31000,37000,29000,33679,27118}};
    for(int job=1;job<=9;++job) {
        recovered.data["characters"][2]={{"name","Own source starter"},{"class",classes[size_t(job)]},
            {"identity",CharacterIdentity{job,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
        recovered.apply(2,loaded,loadedProgression);const auto &receipt=loadedProgression.state.at("experimental_starter");
        const auto &instance=loadedProgression.state.at("inventory").at(0);const auto *item=loadedProgression.item(instance.at("id").get<int>());
        bool ownDefault=false;const auto authored=loaded.characterCatalog().defaultAppearanceSources(job);
        for(const auto &entry:authored.equipment)if(entry.equipmentId==instance.at("id").get<int>() && entry.exists)
            ownDefault=entry.source.script.path==receipt.at("source").at("member_path") &&
                sha256(entry.source.script.rawBytes)==receipt.at("source").at("member_sha256") &&
                receipt.at("default_equipment_field_offset")==entry.fieldOffset && receipt.at("default_equipment_value_index")==entry.valueIndex;
        check(item && ownDefault && instance.at("id")==expectedWeapons[size_t(job)] &&
              equipmentAllowsJob(loaded.characterCatalog().at(job),item->source) &&
              loadedProgression.state.at("equipped").at("[weapon]")==instance.at("uid") &&
              !receipt.at("native_creation_gift_confirmed").get<bool>() && loaded.combatAttributes() &&
              loaded.combatAttributes()->physicalAttack>0 && loaded.combatAttributes()->magicalAttack>0,
              "Experimental job "+std::to_string(job)+" equips its own uniquely qualified SD/EQU source weapon and feeds positive physical/magical attack into the real World");
        jobStarters.push_back(receipt);
    }

    recovered.data["characters"][0]=experimentalStorageRoot().at("characters").at(0);
    recovered.apply(0,loaded,loadedProgression);int upper=-1;
    for(size_t i=0;i<loaded.skills.size();++i)if(loaded.skills[i].id==46)upper=int(i);
    check(upper>=0 && loaded.skillState().learnedLevel({0,46})==1,"Normal Space storage fixture has the real source initial upper-slash skill");
    loaded.bindings.fill(-1);loaded.bindings[12]=upper;
    recovered.capture(0,loaded,loadedProgression);recovered.checkpoint();
    recovered.close();
    CharacterStore spaceStore(directory,"experimental-storage-source-test");
    World spaceWorld(pvf,assets,WorldRules::BetaFoundationV1);Progression spaceProgression(region);
    spaceStore.apply(0,spaceWorld,spaceProgression);
    check(spaceWorld.bindings[12]>=0 && spaceWorld.skills.at(size_t(spaceWorld.bindings[12])).id==46 &&
          spaceStore.data.at("characters").at(0).at("bindings")[12]==46,
          "Normal thirteenth Space slot stores a source skill ID and restores its current runtime index after actual disk reload");
    spaceWorld.enqueue({spaceWorld.simulationNanoseconds()+1,7,true});spaceWorld.advanceSingleTick();
    check(spaceWorld.activeSkill()>=0 && spaceWorld.skills.at(size_t(spaceWorld.activeSkill())).id==46 &&
          spaceWorld.remainingCd(spaceWorld.activeSkill())>0,
          "Actual logical Space key 7 executes the rebound saved slot through the normal controller and source cooldown consumer");
    spaceWorld.idle();spaceWorld.releaseInputs();spaceWorld.skillState().clearCooldowns();spaceWorld.bindings[12]=-1;
    spaceStore.capture(0,spaceWorld,spaceProgression);spaceStore.checkpoint();spaceStore.close();
    CharacterStore clearedStore(directory,"experimental-storage-source-test");
    World clearedWorld(pvf,assets,WorldRules::BetaFoundationV1);Progression clearedProgression(region);
    clearedStore.apply(0,clearedWorld,clearedProgression);const auto mp=clearedWorld.player.mp;
    clearedWorld.enqueue({clearedWorld.simulationNanoseconds()+1,7,true});clearedWorld.advanceSingleTick();
    check(clearedWorld.bindings[12]==-1 && clearedWorld.activeSkill()==-1 && clearedWorld.player.mp==mp &&
          std::none_of(clearedWorld.events.begin(),clearedWorld.events.end(),[](const Event &event){return event.kind=="skill_cost";}),
          "Clearing and saving Space survives disk reload and actual key 7 consumes no skill, MP or cooldown");
    clearedStore.close();
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"save_directory",directory.u8string()},
        {"source_fixture",{{"identity",plan.identity.json()},{"skill",selectedSkill->key.json()},{"motion",motion->json()},
                           {"attack",attack?attack->json():Json()},{"pvf_identity",pvf.identity()}}},
        {"scope","Actual opt-in World and CharacterStore capture/apply/disk reload and failure atomicity; experimental bindings remain incomplete user experiments, not native or complete beta skills"},
        {"job_starter_sources",jobStarters},{"runtime_complete",false},{"frontend_started",false},{"native_dynamic_comparison","pending user"}};
}
} // namespace dnf
