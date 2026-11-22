#include "dnf/squirrel_world_bridge.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <stdexcept>
#include <thread>

namespace dnf {
namespace {
Json scriptWorldState(const World &world) {
    Json actors=Json::array(),statuses=Json::array();
    for(const auto &actor:world.monsters){actors.push_back(saveActor(actor,world.nowMs()));statuses.push_back(world.statusCheckpoint(actor.handle));}
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},{"events",world.eventLog()},
        {"inputs",world.inputs()},{"player",saveActor(world.player,world.nowMs())},{"actors",actors},{"statuses",statuses},
        {"normal_ledger",world.skillState().snapshot(world.nowMs())},{"learning_overlay",world.skillTestOverlay().snapshot()},
        {"map_exploration",world.mapExplorationPolicy()},{"source_actions",world.sourceActionDiagnostics()}};
}
SquirrelInvocationContext context(World &world,std::optional<SkillKey> buff=std::nullopt) {
    return {world.idSources().requests.next(),world.idSources().actions.next(),world.player.handle,buff};
}
size_t eventCount(const World &world,const std::string &kind) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),[&](const Event &event){return event.kind==kind;}));
}
void loadBuff(squirrel_stage::Instance &vm,SquirrelWorldBridge &bridge) {
    if(!vm.load(bridge.source("sqr/dnf_enum_header.nut")).ok ||
       !vm.load(bridge.source("sqr/character/atmage/atmage_buff.nut")).ok)
        throw std::runtime_error("Squirrel World fixture: actual enum/Buff sources failed admission/load");
}
bool responseExecutable(const Script &source) {
    bool pvp=false;
    for(size_t i=0;i<source.tokens.size();++i) {
        const auto &value=source.tokens[i]["value"];if(!value.is_string())continue;
        const auto tag=normalize(value.get<std::string>());
        if(tag=="[pvp]"){pvp=true;continue;}if(tag=="[/pvp]"){pvp=false;continue;}if(pvp)continue;
        if(tag=="[hit info]") {
            if(i+4>=source.tokens.size())return false;
            for(size_t n=3;n<=4;++n)if(!source.tokens[i+n]["value"].is_number() || source.tokens[i+n]["value"].get<double>()<0)return false;
        }
    }
    return readAttackDamage(source,AttackStatusConsumer::StunHostV1).usable();
}
} // namespace

// DRAFT: written for the parent to compile/run after dependency integration.
// This tests real World consumers and actual VM callbacks where present. The
// contact fixture is explicitly direct C++, not a restored native script API.
Json runSquirrelWorldBridgeTests(Pvf &pvf,Assets &assets,const std::string &staticIdentity) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Squirrel World: "+name);checks.push_back(name);};
    const auto rejects=[](auto function){try{function();}catch(const std::exception&){return true;}return false;};
    auto services=squirrel_stage::windowsSourceServices();
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();world.selectCharacter({8,0,0});
        const auto invocation=context(world,SkillKey{8,176});SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);
        squirrel_stage::Instance vm(*services,bridge,invocation.instanceId);loadBuff(vm,bridge);
        const auto skills=world.skillState().snapshot(world.nowMs()),overlay=world.skillTestOverlay().snapshot();
        const auto soundsBefore=eventCount(world,"sound");
        const auto result=vm.invoke("onAfterSetState_Buff",world.player.handle,invocation.actionId,{0,Json::array(),true});
        check(result.ok && result.stagedCommands==1 && eventCount(world,"sound")==soundsBefore+1 &&
              world.events.back().kind=="sound" && world.events.back().name=="MW_ANCIENT",
              "Actual atmage Buff callback publishes one real World sound event through the existing typed VM and audio dependency resolver");
        check(world.skillState().snapshot(world.nowMs())==skills && world.skillTestOverlay().snapshot()==overlay,
              "Source Buff query does not create normal learning, purchases, passive attributes or test overrides");
        const auto receipt=bridge.diagnostics().at("sound_receipts").at(0);
        check(receipt.at("owner")==world.player.handle.json() && receipt.at("instance_id")==invocation.instanceId &&
              receipt.at("script_source").at("member_path")=="sqr/character/atmage/atmage_buff.nut" &&
              receipt.at("script_source").at("package_identity")==pvf.identity() && !receipt.at("dependencies").empty(),
              "World sound receipt preserves actual script PVF identity and transitive audio.xml/audio-byte dependencies");
        const auto afterSound=scriptWorldState(world);
        const auto fault=vm.invoke("onAfterSetState_Buff",world.player.handle,invocation.actionId+1,{0,Json::array(),true});
        vm.close();vm.close();
        check(!fault.ok && fault.stagedCommands==1 && fault.closed && fault.arenaReleased && bridge.diagnostics().at("cleanup_count")==1 &&
              scriptWorldState(world)==afterSound && !bridge.valid(world.player.handle),
              "An actual callback stages a sound then fails foreign-action preparation; cleanup closes once and releases its arena without retracting committed World events");
        samples["buff_sound"]=bridge.diagnostics();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);const auto invocation=context(world);
        const auto beforeInvalid=scriptWorldState(world);auto invalid=invocation;
        invalid.actionId=world.idSources().actions.nextValue();
        check(rejects([&]{SquirrelWorldBridge rejected(world,pvf,assets,staticIdentity,invalid);}) && scriptWorldState(world)==beforeInvalid,
              "An unissued action ID cannot bind a Squirrel context or mutate World state");
        SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);const auto unit=bridge.source("sqr/dnf_enum_header.nut");
        const auto sound=bridge.resolveSound("MW_ANCIENT",unit.source);check(bool(sound),"Source audio fixture resolves through the production resource closure");
        squirrel_stage::SoundCommand first{invocation.instanceId,invocation.actionId,1,world.player.handle,unit.source,*sound,"MW_ANCIENT"};
        auto bad=first;bad.sequence=2;bad.soundSource.memberSha256="foreign-audio";
        const auto before=scriptWorldState(world),beforeBridge=bridge.diagnostics();
        check(rejects([&]{bridge.prepare({first,bad});}) && scriptWorldState(world)==before && bridge.diagnostics()==beforeBridge,
              "A later bad sound in one prepared batch leaves all World events and bridge receipts unchanged");
        bool wrongThreadRejected=false;std::thread worker([&]{wrongThreadRejected=rejects([&]{bridge.source("sqr/dnf_enum_header.nut");});});worker.join();
        check(wrongThreadRejected && scriptWorldState(world)==before,"Source admission rejects a foreign simulation thread without mutation");
        auto prepared=bridge.prepare({first});bridge.cleanup(invocation.instanceId,"fixture close");bridge.commit(std::move(prepared));
        check(scriptWorldState(world)==before && bridge.diagnostics().at("cleanup_count")==1,
              "Closing an instance invalidates its prepared sound batch and cannot publish it later");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();world.selectCharacter({8,0,0});
        const auto invocation=context(world,SkillKey{8,176});SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);
        squirrel_stage::Instance vm(*services,bridge,invocation.instanceId);loadBuff(vm,bridge);
        world.changeScene();const auto before=scriptWorldState(world);
        const auto failed=vm.invoke("onAfterSetState_Buff",invocation.owner,invocation.actionId,{0,Json::array(),true});
        check(!failed.ok && failed.closed && bridge.diagnostics().at("cleanup_count")==1 && scriptWorldState(world)==before,
              "Room-change handle generations cannot be retargeted by an old Squirrel callback");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);const auto invocation=context(world);
        SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);squirrel_stage::Instance vm(*services,bridge,invocation.instanceId);
        const auto before=scriptWorldState(world);const auto source=bridge.source("sqr/character/atmage/windstrike/wind_strike.nut");
        const auto inspection=vm.inspect(source);
        const auto result=vm.load(source);
        check(inspection.executable && result.ok && !result.closed && scriptWorldState(world)==before &&
              bridge.diagnostics().at("source_damage_native_api_registered")==false,
              "WindStrike source passes recorded-no-op admission without registering a native damage consumer");
    }
    {
        RegionCatalog catalog(pvf,assets);Progression progression(catalog);World world(pvf,assets,WorldRules::BetaFoundationV1);
        world.applyEquipment(progression);world.combat=true;world.freezeAi=true;
        world.mapWidth=1200;world.walkRects={{0,240,1200,240}};world.player.x=world.player.px=560;world.player.y=world.player.py=344;
        Actor goblin;goblin.id=goblin.sourceId=1;goblin.monsterPath="monster/goblin/goblin.mob";goblin.x=goblin.px=610;goblin.y=goblin.py=344;
        world.initializeMonsterAttributes(goblin,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
        world.monsters.push_back(std::move(goblin));world.synchronizeEntityHandles();
        world.configureSourceActions(staticIdentity);world.setMapExplorationPolicy(true);
        const auto *host=world.actHost();
        const auto hostInstances=host->instances().size();
        const auto hostDiagnostics=host->diagnostics();
        size_t externalCallbacks=0;
        world.setBeforeTick([&](World &){++externalCallbacks;});world.setObjectTick([&](World &){++externalCallbacks;});
        const auto invocation=context(world);SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);
        const auto origin=bridge.source("sqr/dnf_enum_header.nut");std::optional<SourceRef> attack;
        for(const auto &resource:world.characterSource().resources) {
            if(!resource.exists || (resource.tag!="[attack info]"&&resource.tag!="[etc attack info]"&&resource.tag!="[jumpattack info]"&&resource.tag!="[dashattack info]"))continue;
            if(!responseExecutable(pvf.script(resource.path)))continue;
            try{attack=bridge.attackSource(resource.tag,resource.valueIndex);break;}catch(const std::exception&){}
        }
        check(bool(attack),"Own Swordman CHR supplies an ATK whose explicit pause/damage operands have real consumers");
        SquirrelSourceContact command{invocation.instanceId,invocation.actionId,1,0,world.player.handle,world.monsters[0].handle,origin.source,*attack,"physical"};
        auto bad=command;bad.attackOrdinal=2;bad.attackSource.memberSha256="foreign-atk";
        const auto before=scriptWorldState(world),beforeBridge=bridge.diagnostics();
        const auto rejected=bridge.applySourceContacts({command,bad});
        check(!rejected.ok && scriptWorldState(world)==before && bridge.diagnostics()==beforeBridge,
              "Late ATK-source rejection rolls back the entire private candidate, including HP, status, random streams, attack IDs, effects and events");
        SquirrelContactResult hit;const int hpBefore=world.monsters[0].hp;
        const auto feedbackBefore=eventCount(world,"hit_feedback");
        for(uint32_t i=0;i<32 && world.monsters[0].hp==hpBefore;++i){command.hitIndex=i;hit=bridge.applySourceContacts({command});check(hit.ok,"Direct typed source contact uses the real World damage/status transaction");}
        check(world.monsters[0].hp<hpBefore && !hit.receipts.empty() && hit.receipts.at(0).at("outcome").at("usable").get<bool>(),
              "Internal typed C++ contact consumes real CHR/EQU/MOB/ATK inputs and writes the accepted unified source damage to World HP");
        const auto response=readAttackResponse(pvf.script(attack->memberPath));
        check(eventCount(world,"hit_feedback")==feedbackBefore+1 &&
              (response.sound.empty() || std::count_if(world.events.begin(),world.events.end(),[&](const Event &event){
                  return event.kind=="sound" && event.name==response.sound && event.target==world.monsters[0].id;
              })==1),
              "Accepted script contact publishes one shared monster feedback and at most one authored ATK sound; misses publish neither");
        const auto after=scriptWorldState(world),afterBridge=bridge.diagnostics();const auto duplicate=bridge.applySourceContacts({command,command});
        check(duplicate.ok && duplicate.accepted==0 && duplicate.duplicates==2 && scriptWorldState(world)==after && bridge.diagnostics()==afterBridge,
              "Duplicate attack/pulse/target identities consume no additional HP, RNG, status roll, event or ID");
        const auto geometry=world.walkRects;world.walkRects.clear();
        const auto withoutGeometry=scriptWorldState(world);
        check(!bridge.applySourceContacts({command}).ok && scriptWorldState(world)==withoutGeometry && bridge.diagnostics()==afterBridge,
              "Even an accepted duplicate cannot bypass the live map exploration incoming-damage geometry policy");
        world.walkRects=geometry;
        const auto issuedAttacks=world.idSources().attacks;world.idSources().attacks=MonotonicIds(1);
        const auto rewound=scriptWorldState(world);
        check(!bridge.applySourceContacts({command}).ok && scriptWorldState(world)==rewound && bridge.diagnostics()==afterBridge,
              "An externally rewound attack allocator cannot reuse a prior Squirrel attack identity");
        world.idSources().attacks=issuedAttacks;
        if(!world.monsters[0].dead) {
            world.monsters[0].hp=1;command.attackOrdinal=2;const auto killedBefore=eventCount(world,"killed");
            for(uint32_t i=0;i<32 && !world.monsters[0].dead;++i){command.hitIndex=i;check(bridge.applySourceContacts({command}).ok,"Lethal source contact remains executable");}
            check(world.monsters[0].dead && world.monsters[0].life==ActorLife::Dying && eventCount(world,"killed")==killedBefore+1,
                  "Accepted lethal source damage enters the actual World death lifecycle and emits exactly one kill event");
            const auto dead=scriptWorldState(world);const auto again=bridge.applySourceContacts({command});
            check(again.ok && again.duplicates==1 && scriptWorldState(world)==dead,"Repeating a lethal pulse cannot duplicate the reward-facing kill event");
        }
        check(world.actHost()==host && host->instances().size()==hostInstances && host->diagnostics()==hostDiagnostics && externalCallbacks==0,
              "Candidate damage, death and destruction never invoke or replace live ACT services or external World tick callbacks");
        world.monsters[0].life=ActorLife::Removed;world.synchronizeEntityHandles();
        const auto retired=scriptWorldState(world);
        check(!bridge.applySourceContacts({command}).ok && scriptWorldState(world)==retired,
              "A duplicate contact carrying a retired target handle is rejected before deduplication");
        bridge.cleanup(invocation.instanceId,"contact fixture closed");bridge.cleanup(invocation.instanceId,"repeat close");
        const auto closedState=scriptWorldState(world);check(!bridge.applySourceContacts({command}).ok && scriptWorldState(world)==closedState &&
            bridge.diagnostics().at("cleanup_count")==1,"Cleanup is idempotent and permanently rejects further contacts without undoing committed business events");
        samples["source_contacts"]=bridge.diagnostics();
    }
    {
        // Read-only parameter queries must read the same SKL cells the combat
        // pipeline uses, and must do so for both call shapes (global and member).
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        world.enableExperimentalCharacters();world.selectCharacter({8,0,0});
        world.skillState().setLearnedLevel({8,2},1);
        const auto invocation=context(world);SquirrelWorldBridge bridge(world,pvf,assets,staticIdentity,invocation);
        squirrel_stage::Instance vm(*services,bridge,invocation.instanceId);
        // Values are the 1031 source cells for skill/atmage/chainlightning.skl:
        // [static data] = [500,0,650,400,300]; [level info] = width 4 then
        // level 1 row [7,1200,276,4] (link count, attack time, rate, hit count);
        // [casting time] = [600,600]. A PVF change must fail this check.
        const std::string text=
            "function probeQuery(obj) {\n"
            "  local a=obj.sq_GetSkillLevel(2);\n"
            "  local b=obj.sq_GetIntData(2,0);\n"
            "  local c=obj.sq_GetLevelData(2,0,1);\n"
            "  local d=sq_GetSkillLevel(obj,2);\n"
            "  local e=obj.sq_GetBonusRateWithPassive(2,25,2,1.0);\n"
            "  local f=sq_GetCastTime(obj,2,1);\n"
            "  if(a!=1) { print(\"a=\"+a); return 0; }\n"
            "  if(b!=500) { print(\"b=\"+b); return 0; }\n"
            "  if(c!=7) { print(\"c=\"+c); return 0; }\n"
            "  if(d!=a) { print(\"d=\"+d); return 0; }\n"
            "  if(e!=276) { print(\"e=\"+e); return 0; }\n"
            "  if(f!=600) { print(\"f=\"+f); return 0; }\n"
            "  print(\"probe-done\");\n"
            "  return 1;\n"
            "}\n";
        squirrel_stage::SourceUnit probe;
        probe.source.packageIdentity=pvf.identity();
        probe.source.memberPath="sqr/probe/skill-query.nut";
        probe.original.assign(text.begin(),text.end());
        probe.source.memberSha256=services->digest(probe.original);
        const auto loaded=vm.load(probe);
        const auto invoked=loaded.ok?vm.invoke("probeQuery",world.player.handle,invocation.actionId):loaded;
        std::string detail=loaded.ok?"loaded":"load-failed";
        if(!loaded.diagnostics.empty())detail+=":"+loaded.diagnostics.front().code+"/"+loaded.diagnostics.front().message;
        if(loaded.ok) {
            detail+=" invoked="+(invoked.ok?std::string("ok"):std::string("fail"));
            if(!invoked.ok&&!invoked.diagnostics.empty())detail+=":"+invoked.diagnostics.front().code+"/"+invoked.diagnostics.front().message;
            if(invoked.ok)detail+=" value="+invoked.value.dump();
        }
        check(invoked.ok && invoked.value.is_number() && invoked.value.get<int>()==1,
              "Skill query natives read SKILL int-data, level-info and cast cells for both call shapes ["+detail+"]");
        // The actual 1031 chain-lightning script must clear the zero-trust
        // admission gate now that its 30 distinct sq_ calls are implemented.
        const auto chain=vm.inspect(bridge.source("sqr/character/atmage/chainlightning/chainlightning.nut"));
        std::string missing;
        for(const auto &d:chain.diagnostics)if(d.code=="unsupported_api")missing+=d.message+"; ";
        check(chain.executable,"Actual chain-lightning NUT passes capability admission ["+
              (chain.executable?std::string("ok"):missing.empty()?std::string("not executable"):missing)+"]");
        // Execute the source callback to find host faults that static
        // admission cannot see (null handles, unimplemented value shapes).
        const auto enumLoaded=vm.load(bridge.source("sqr/dnf_enum_header.nut"));
        const auto headerLoaded=enumLoaded.ok?vm.load(bridge.source("sqr/character/atmage/atmage_header.nut")):enumLoaded;
        const auto bodyLoaded=headerLoaded.ok?vm.load(bridge.source("sqr/character/atmage/chainlightning/chainlightning.nut")):headerLoaded;
        const auto stateInvoke=(headerLoaded.ok&&bodyLoaded.ok)
            ?vm.invoke("onSetState_ChainLightning",world.player.handle,invocation.actionId,{25,Json::array(),true})
            :bodyLoaded;
        std::string invokeDetail="header="+(headerLoaded.ok?std::string("ok"):"fail")+
            " body="+(bodyLoaded.ok?std::string("ok"):"fail")+
            " callback="+(stateInvoke.ok?std::string("ok"):"fail");
        if(!stateInvoke.ok&&!stateInvoke.diagnostics.empty())
            invokeDetail+=" :"+stateInvoke.diagnostics.front().code+"/"+stateInvoke.diagnostics.front().message;
        check(stateInvoke.ok,"Actual chain-lightning onSetState callback executes in the typed VM ["+invokeDetail+"]");
        samples["script_skill_queries"]=bridge.diagnostics();
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"samples",samples},{"runtime_complete",false},
        {"scope","Actual typed VM Buff/audio callbacks plus internal C++ source-contact bridge; native skill/packet callback routing remains incomplete"},
        {"vm_policy",squirrel_stage::vmPolicyId},{"frontend_started",false},{"native_dynamic_comparison","pending user"}};
}
} // namespace dnf
