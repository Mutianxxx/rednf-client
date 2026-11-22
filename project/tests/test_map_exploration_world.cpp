#include "dnf/combat.hpp"
#include "dnf/session.hpp"
#include "dnf/progression.hpp"
#include "dnf/act_world_host.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace dnf {
namespace {
void explorationFloor(World &world) {
    world.combat=true;world.freezeAi=false;world.mapWidth=2000;
    // Deliberate diagnostic plane isolates consumer gates, not MAP geometry.
    world.walkRects={{0,240,2000,240}};
    world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
}
void appendExplorationActor(World &world,int actorId,int sourceId,const std::string &path,double x,int level=1) {
    Actor actor;actor.id=actorId;actor.sourceId=sourceId;actor.monsterPath=path;
    actor.x=actor.px=x;actor.y=actor.py=344;actor.dir=-1;
    world.initializeMonsterAttributes(actor,level);
    world.monsters.push_back(std::move(actor));
}
size_t explorationEvents(const World &world,const std::string &kind,int source=-999) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),[&](const Event &event) {
        return event.kind==kind && (source==-999 || event.source==source);
    }));
}
void explorationTicks(World &world,int count) { for(int i=0;i<count;++i) world.advanceSingleTick(); }
const Json consumer(const World &world,EntityHandle owner) {
    const auto policy=world.mapExplorationPolicy();
    for(const auto &entry:policy.at("actors")) if(entry.at("owner")==owner.json()) return entry;
    throw std::runtime_error("Exploration World: missing consumer receipt");
}
Json explorationState(const World &world) {
    Json actors=Json::array();for(const auto &actor:world.monsters) actors.push_back(saveActor(actor,world.nowMs()));
    return {{"simulation",world.simulationCheckpoint()},{"player",saveActor(world.player,world.nowMs())},
        {"actors",actors},{"events",world.eventLog()},{"policy",world.mapExplorationPolicy()}};
}
template<class F> bool explorationRejected(F &&operation) {
    try {operation();return false;}catch(const std::exception &) {return true;}
}
} // namespace

Json runMapExplorationWorldTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Exploration World: ")+message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf,assets);Progression progression(catalog);
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);explorationFloor(world);
        appendExplorationActor(world,1,1,"monster/goblin/goblin.mob",950);
        appendExplorationActor(world,2,5001,"monster/lugaru/lugaru.mob",1150);
        world.synchronizeEntityHandles();const auto before=explorationState(world);
        const auto known=world.monsters[0].handle,unknown=world.monsters[1].handle;
        world.setMapExplorationPolicy(true);
        auto after=explorationState(world);after["policy"]=before.at("policy");
        check(after==before,"Installing source consumer policy leaves actors, HP, simulation IDs, RNG and pending events unchanged");
        const auto supported=consumer(world,known),unregistered=consumer(world,unknown);
        writeJson("reports/beta-experiment/map-exploration-world-first-policy.json",world.mapExplorationPolicy());
        check(supported.at("incoming_damage")==true && supported.at("legacy_autonomous_controller")==true &&
            unregistered.at("incoming_damage")==true && unregistered.at("legacy_autonomous_controller")==false,
            "Mixed exploration admits source damage independently while only the registered Goblin keeps legacy autonomous AI");
        check(supported.at("source").at("package_identity")==pvf.identity() &&
            unregistered.at("source").at("member_sha256")==sha256(pvf.script("monster/lugaru/lugaru.mob").rawBytes),
            "Every consumer decision retains exact source package and current MOB member hash");
        explorationTicks(world,90);
        check(world.monsters[0].x<950 && world.monsters[1].x==1150 && world.monsters[1].animation=="stay" &&
            !world.freezeAi && world.combat,
            "The real supported Goblin chases while the unregistered Lugaru remains still without a global AI pause");
        samples["mixed_consumers"]=world.mapExplorationPolicy();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);explorationFloor(world);
        appendExplorationActor(world,7,5001,"monster/lugaru/lugaru.mob",640);
        // This obsolete broad marker must not suppress a working consumer.
        world.monsters[0].sourceStats["test_exploration"]={{"combat_capability",false},{"map_complete",false}};
        world.synchronizeEntityHandles();world.setMapExplorationPolicy(true);
        const auto hp=world.monsters[0].hp;world.normalAttack();
        for(int i=0;i<120 && explorationEvents(world,"hit")==0;++i) world.advanceSingleTick();
        check(explorationEvents(world,"hit")>0 && world.monsters[0].hp<hp &&
            world.statReport().at("last_damage").at("policy")=="inferred-pve-damage-v1",
            "An unknown autonomous controller with preflighted hurt/death consumers still accepts real source ordinary-attack damage");
        const bool goblinAudio=std::any_of(world.events.begin(),world.events.end(),[](const Event &event) {
            return event.kind=="sound" && event.source==7 &&
                (event.name=="R_GOBLIN_DMG" || event.name=="R_GOBLIN_DIE");
        });
        check(!goblinAudio,"Unknown source actors never inherit Goblin hurt/death audio during exploration");
        samples["source_incoming"]=world.statReport().at("last_damage");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);explorationFloor(world);
        appendExplorationActor(world,1,2,"monster/goblin/goblinthrower.mob",710,2);
        world.synchronizeEntityHandles();const auto owner=world.monsters[0].handle;world.setMapExplorationPolicy(true);
        check(consumer(world,owner).at("legacy_autonomous_controller")==true,
            "The source-qualified thrower keeps its preflighted projectile controller in exploration");
        bool projectile=false;
        for(int i=0;i<180 && !projectile;++i) {
            world.advanceSingleTick();
            for(const auto &effect:world.effects) if(effect.hostile && effect.hostileStats && effect.hostileOwnerHandle==owner) projectile=true;
        }
        check(projectile && explorationEvents(world,"monster_projectile",1)>0,
            "Exploration thrower AI emits the real source PO/ANI/ATK projectile with frozen combat stats and owner handle");
        for(int i=0;i<120 && explorationEvents(world,"player_hit")==0;++i) world.advanceSingleTick();
        check(explorationEvents(world,"player_hit")>0 && world.statReport().at("last_damage").at("usable")==true,
            "The retained source projectile reaches the player through the existing unified damage consumer");
        samples["thrower"]=world.mapExplorationPolicy();
    }
    {
        std::unique_ptr<World> selected;uint64_t seed=0;
        for(;seed<32 && !selected;++seed) {
            auto world=std::make_unique<World>(pvf,assets,WorldRules::BetaFoundationV1);
            world->applyEquipment(progression);explorationFloor(*world);world->randomStreams()=RandomStreams(seed);
            appendExplorationActor(*world,1,11,"monster/tau/tauarmy.mob",605);
            world->monsters[0].attackSerial=1;world->synchronizeEntityHandles();world->setMapExplorationPolicy(true);
            check(consumer(*world,world->monsters[0].handle).at("legacy_autonomous_controller")==true,
                "The source-qualified Tau keeps its second-attack/status-capable controller in exploration");
            for(int i=0;i<360 && !world->player.dead;++i) {
                world->advanceSingleTick();
                if(world->statusStunned(world->player.handle)) {selected=std::move(world);break;}
            }
        }
        check(bool(selected),"Exploration Tau AI still accepts an authored heading.atk stun and real HP damage through the status host");
        samples["tau_status"]={{"seed",seed-1},{"status",selected->statusCheckpoint(selected->player.handle)},
            {"damage",selected->statReport().at("last_damage")}};
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);explorationFloor(world);
        Actor broken;broken.id=9;broken.sourceId=999999;broken.monsterPath="monster/does-not-exist.mob";
        broken.x=broken.px=640;broken.y=broken.py=344;world.monsters.push_back(broken);
        world.synchronizeEntityHandles();const auto before=explorationState(world);world.setMapExplorationPolicy(true);
        auto after=explorationState(world);after["policy"]=before.at("policy");
        check(after==before && !consumer(world,world.monsters[0].handle).at("incoming_damage").get<bool>(),
            "A missing source member produces actor diagnostics without throwing or mutating the prepared scene");
        const auto random=world.randomStreams().snapshot(),ids=world.idSources().snapshot();
        const auto hp=world.monsters[0].hp;
        world.diagnosticHit(9,999,0,0,1,{});
        check(world.monsters[0].hp==hp && world.randomStreams().snapshot()==random && world.idSources().snapshot()==ids &&
            explorationEvents(world,"damage_blocked")==1 && explorationEvents(world,"hit")==0,
            "Unavailable incoming consumer rejects even a diagnostic contact before attack/status RNG, IDs or HP change");
        world.monsters[0].monsterPath="";explorationTicks(world,5);
        check(world.monsters[0].animation=="stay" && world.monsters[0].x==640,
            "A source-less actor never acquires Goblin motion or generic chase AI in exploration");
        samples["blocked_actor"]=world.mapExplorationPolicy();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);explorationFloor(world);
        appendExplorationActor(world,1,1,"monster/goblin/goblin.mob",640);
        world.synchronizeEntityHandles();world.setMapExplorationPolicy(true);
        // Identity drift invalidates grants even when the old handle survives.
        world.monsters[0].sourceId=5001;
        const auto random=world.randomStreams().snapshot();const auto hp=world.monsters[0].hp;
        world.diagnosticHit(1,999,0,0,1,{});explorationTicks(world,1);
        check(world.monsters[0].hp==hp && world.monsters[0].x==640 && world.randomStreams().snapshot()==random,
            "A current handle cannot lend its old controller/damage grant to a changed source identity");
        const auto stale=world.monsters[0].handle;world.changeScene();
        check(!world.mapExplorationActive() && world.mapExplorationPolicy().at("actors").empty() && !world.resolveActor(stale),
            "Scene exit clears all exploration grants and retires their old entity handles");
    }
    {
        World world(pvf,assets);world.combat=true;world.walkRects.clear();
        world.player.x=world.player.px=500;world.player.y=world.player.py=260;
        check(world.canWalk(500,260),"An inactive policy leaves the historical normal-mode empty-floor contract unchanged");
        world.setMapExplorationPolicy(false);
        check(!world.canWalk(500,260) && world.nearestWalkable(500,500)==std::array<double,2>{500,500} && world.walkRects.empty(),
            "Missing exploration geometry explicitly blocks walking and recovery without manufacturing a source floor");
        world.enqueue({world.simulationNanoseconds(),1,true});explorationTicks(world,60);
        check(world.player.x==500 && world.player.y==260 && explorationEvents(world,"position_recovery")==0,
            "Held movement and recovery cannot enter the historical 185..340 fallback when exploration geometry is absent");
        world.changeScene();
        check(!world.mapExplorationActive() && world.canWalk(500,260),
            "Leaving exploration restores normal geometry behavior and clears held test input");
    }
    {
        World world(pvf,assets);world.configureSourceActions("exploration-test-static:"+sha256(assets.staticBytes("audio.xml")));
        explorationFloor(world);world.player.x=world.player.px=1000;
        Actor actor;actor.id=5;actor.sourceId=56721;
        actor.monsterPath="monster/newmonsters/dimensiongate/bakal/dark_dragon_nagor/dark_dragon_nagor.mob";
        actor.x=actor.px=800;actor.y=actor.py=344;actor.dir=-1;
        // Explicit legacy numerical fixture isolates the real ACT service
        // consumer. It cannot grant source incoming damage or regional scope.
        world.initializeMonsterAttributes(actor,70,"legacy-demo-v1","legacy-snapshot-damage-v1");
        actor.sourceStats["spawn"]={{"diagnostic_source_actor",true}};world.monsters.push_back(std::move(actor));
        world.synchronizeEntityHandles();const auto owner=world.monsters[0].handle;world.setMapExplorationPolicy(true);
        check(consumer(world,owner).at("source_actions")==true &&
            consumer(world,owner).at("legacy_autonomous_controller")==false,
            "A source ACT actor stays owned by the ACT service and never opts into legacy autonomous AI");
        explorationTicks(world,1);
        check(world.resolveActor(owner)->dir==1 && !world.actHost()->instances().empty() && explorationEvents(world,"source_action",5)>0,
            "The actual Nagor source waiting action still executes OnSet direction through the World ACT host in exploration");
        const auto random=world.randomStreams().snapshot(),ids=world.idSources().snapshot();
        world.requestSourceMonsterAction(owner,"attack",999999);explorationTicks(world,1);
        check(world.randomStreams().snapshot()==random && world.idSources().snapshot()==ids &&
            world.resolveActor(owner)->animation!="attack1",
            "A failed ACT action request never falls through to generic chase/attack or consumes candidate RNG/IDs");
        world.changeScene();
        check(!world.mapExplorationActive() && !world.actHost()->ownsActor(owner) && !world.actHost()->controlsMovement(owner),
            "Scene exit cancels source ACT instances together with exploration consumers");
        samples["act_service"]=world.sourceActionDiagnostics();
    }
    {
        World world(pvf,assets);const auto before=explorationState(world);
        world.validateSceneActorCapacity(64);
        check(explorationState(world)==before,"Room roster capacity validation is a pure private allocator dry run");
        auto checkpoint=world.simulationCheckpoint();checkpoint["entities"]["ids"]["next"]=UINT64_MAX-1;
        world.restoreSimulationCheckpoint(checkpoint);const auto oneLeft=explorationState(world);
        check(explorationRejected([&]{world.validateSceneActorCapacity(1);}) && explorationState(world)==oneLeft,
            "Insufficient identities for a new player plus room actors reject before cancelling or modifying the old scene");
        world.validateSceneActorCapacity(0);
        check(explorationState(world)==oneLeft,"The exact final player identity can be preflighted without consuming it");
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual World per-consumer exploration gates, source damage/projectile/status/ACT retention, missing geometry, scene cleanup and entity capacity; diagnostic plane/source actors do not establish full MAP/MOB, normal progression, rewards or native visual parity"}};
}
} // namespace dnf
