#include "explicit_skill_preview_fixture.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
CharacterActionRequest attackRequest(int key=4) {
    CharacterActionRequest request;request.inputKey=key;request.inputDown=true;
    request.action=key==4?CharacterAction::BasicAttack:CharacterAction::Skill;return request;
}
struct ReaderWorld {
    World world;
    Progression progression;
    ReaderWorld(Pvf &pvf,Assets &assets,const RegionCatalog &regions,const CharacterCatalog &characters,
                int job,const std::filesystem::path &root)
        :world(pvf,assets,WorldRules::BetaFoundationV1),progression(regions) {
        world.enableExperimentalCharacters();const CharacterIdentity identity{job,0,0};
        CharacterStore store(root/std::to_string(job));
        const auto className=std::filesystem::u8path(characters.at(job).registration.path).stem().u8string();
        store.data["characters"][0]={{"name","SharedAttackSourceTest"},{"class",className},{"identity",identity.json()},
            {"level",1},{"skill_initialization","source-v1"}};
        store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);
        world.combat=true;world.freezeAi=true;world.mapWidth=1600;world.walkRects={{0,185,1600,240}};
        world.player.x=world.player.px=560;world.player.y=world.player.py=300;world.player.dir=1;
        world.synchronizeEntityHandles();
    }
};
Json noInputRequestIds(const World &world) {
    const auto checkpoint=world.simulationCheckpoint();auto ids=checkpoint.at("ids");ids.erase("requests");return ids;
}
} // namespace

Json runCharacterAttackTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool value,const char *message) {
        if(!value)throw std::runtime_error(std::string("Shared character attack: ")+message);checks.push_back(message);
    };
    CharacterCatalog characters(pvf);RegionCatalog regions(pvf,assets);
    const auto root=std::filesystem::absolute(std::filesystem::path("cache")/"shared-character-attack-tests"/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    {
        // Female Fighter's actual basic ANI has no body type15. Her source
        // default glove c-layer supplies frame1; do not synthesize a box.
        ReaderWorld fixture(pvf,assets,regions,characters,1,root/"late-entry");auto &world=fixture.world;
        const auto *binding=world.experimentalRuntime()->plan().motion("[attack motion]");
        check(binding!=nullptr,"Actual female Fighter has an exact source basic CHR motion");
        const auto motion=readCharacterAttackMotion(assets,world.characterAppearance(),binding->source.memberPath);
        size_t bodyBoxes=0,sharedBoxes=0;
        for(size_t frame=0;frame<motion.body->frames.size();++frame) {
            for(const auto &box:motion.body->frames[frame].boxes)if(box.type==15)++bodyBoxes;
            sharedBoxes+=motion.boxesAt(frame).size();
        }
        check(bodyBoxes==0&&sharedBoxes>0&&!motion.weapons.empty(),"Shared reader obtains Fighter's real weapon-only attack volume while her body remains empty");
        Actor target;target.id=1;target.sourceId=1;target.monsterPath="monster/goblin/goblin.mob";
        target.x=target.px=world.player.x+400;target.y=target.py=world.player.y;target.dir=-1;
        world.initializeMonsterAttributes(target,1);world.monsters.push_back(std::move(target));world.synchronizeEntityHandles();
        const auto targetHandle=world.monsters[0].handle;const int hp=world.monsters[0].hp;
        world.normalAttack();bool active=false;
        for(size_t tick=0;tick<120;++tick) {
            world.advanceSingleTick();if(!world.attackVolumes.empty()){active=true;break;}
        }
        check(active&&world.resolveActor(targetHandle)->hp==hp,"Weapon-only source interval opens with the target still outside its real volume");
        auto *entered=world.resolveActor(targetHandle);entered->x=entered->px=world.player.x+35;entered->y=entered->py=world.player.y;
        world.advanceSingleTick();
        size_t contacts=0;
        for(const auto &event:world.events)if(event.target==1&&(event.kind=="hit"||event.kind=="miss"))++contacts;
        check(contacts==1,"A target entering after the source weapon frame's first sample still reaches one actual contact on the sustained interval");
        for(size_t tick=0;tick<120&&world.experimentalRuntime()->attacking();++tick)world.advanceSingleTick();
        size_t total=0;for(const auto &event:world.events)if(event.target==1&&(event.kind=="hit"||event.kind=="miss"))++total;
        check(total==1,"Sustained weapon samples and response/hit-pause cannot register a second accepted contact on that swing");
        samples["weapon_only_late_entry"]={{"motion",motion.json()},{"hp_before",hp},{"hp_after",world.resolveActor(targetHandle)->hp},
            {"contacts",total},{"events",world.eventLog()}};
    }
    {
        auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,characters,{7,0,0}));
        const auto *binding=plan->motion("[attack motion]");check(binding!=nullptr,"Male Fighter source motion is available for real ANI sound boundaries");
        const auto animation=plan->animations.at(binding->source.memberPath);
        std::map<std::string,size_t> expected,actual;std::map<size_t,size_t> samplesByFrame;
        for(const auto &frame:animation->frames)if(frame.properties.contains("16")) {
            const auto &sound=frame.properties.at("16");if(sound.is_string()&&!sound.get<std::string>().empty())++expected[sound.get<std::string>()];
        }
        check(!expected.empty(),"The sound regression uses authored source frame16 events rather than an injected sound");
        ExperimentalCharacterRuntime runtime(plan);ExperimentalActorState actor;actor.mp=INT32_MAX;
        check(runtime.request(attackRequest()),"Source sound regression accepts one ordinary attack request");
        bool paused=false;
        for(uint64_t tick=1;tick<180;++tick) {
            actor.hitStopped=tick==2||tick==3;
            const auto out=runtime.advance(tick,actor,[](double,double){return true;});actor=out.actor;
            if(actor.hitStopped) {paused=true;check(out.sounds.empty()&&out.attacks.empty(),"Hit pause repeats neither source sound nor contact samples");}
            for(const auto &sound:out.sounds)++actual[sound];
            for(const auto &frame:out.attacks)++samplesByFrame[frame.sourceFrame];
            if(!runtime.attacking())break;
        }
        check(paused&&actual==expected,"Every authored ANI sound emits exactly once while persistent frame intervals repeat and resume from hit pause");
        check(std::any_of(samplesByFrame.begin(),samplesByFrame.end(),[](const auto &row){return row.second>1;}),
            "The sound check actually traverses repeated samples of a persistent source frame");
        samples["persistent_sound"]={{"expected",expected},{"actual",actual}};
    }
    {
        ReaderWorld fixture(pvf,assets,regions,characters,1,root/"source-fault");auto &world=fixture.world;
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto *equipment=fixture.progression.item(fixture.progression.state.at("experimental_starter").at("equipment_id").get<int>());
        check(equipment!=nullptr,"Source fault fixture retains its actual starter weapon definition");
        const int subtype=int(equipment->source.number("[sub type]",-1));
        const ExperimentalSkillRow *skill=nullptr;
        for(const auto &row:plan.skills)if(row.second.kind==SkillSourceKind::Active&&row.second.data) {
            const auto cost=evaluateCharacterSkillCosts(*row.second.data,1,plan.characterDefinition,subtype,false,{}, {},inferred1031SkillCostAbsencePolicy());
            if(cost.consumeMp()&&*cost.consumeMp()>0&&*cost.consumeMp()<=world.player.maxMp&&cost.cooldownMs()&&*cost.cooldownMs()>0) {skill=&row.second;break;}
        }
        check(skill!=nullptr,"Source fault fixture has a real positive-cost SKL");
        runtime.configuration().configureBasicAttackTemplate(skill->key,1,plan);runtime.configuration().assignSlot(0,skill->key,plan);
        const auto goodAppearance=world.characterAppearance();auto broken=goodAppearance;
        // Public caller can provide a same-identity appearance with no CHR
        // binding. This is a controlled source fault, never a source rewrite.
        broken.bodyMotions.clear();world.setCharacterAppearance(std::move(broken));
        world.player.mp=world.player.maxMp;const int mp=world.player.mp;const auto events=world.events.size();
        const auto rng=world.randomStreams().snapshot(),ids=noInputRequestIds(world),configuration=runtime.configuration().snapshot();
        const auto actionSequence=runtime.snapshotDiagnostics().at("action_sequence");
        world.enqueue({world.simulationNanoseconds(),1,true});world.enqueue({world.simulationNanoseconds(),20,true});
        world.advanceSingleTick();
        check(world.player.mp==mp&&runtime.remainingCooldown(skill->key,world.nowMs())==0&&!runtime.attacking()&&
            world.attackVolumes.empty()&&world.randomStreams().snapshot()==rng&&noInputRequestIds(world)==ids&&
            runtime.snapshotDiagnostics().at("action_sequence")==actionSequence,
            "Failed CHR/EQU preflight rejects the current action before MP, cooldown, RNG or action/attack/event identity publication");
        const bool onlyRejection=std::all_of(world.events.begin()+events,world.events.end(),[](const Event &event){return event.kind=="skill_rejected";});
        check(onlyRejection&&runtime.configuration().snapshot()==configuration&&world.player.skillFailureFeedback.startedMs==world.nowMs(),
            "A source preflight rejection publishes neither source sound nor a rewritten manual binding");
        const auto diagnostics=world.experimentalDiagnostics().at("world");
        check(!diagnostics.empty()&&diagnostics.back().at("code")=="experimental_attack_source_preflight_rejected"&&
            diagnostics.back().at("current_action_rejected")==true,
            "Failed source preflight has an explicit current-action rejection diagnostic");
        const auto x=world.player.x;world.advanceSingleTick();
        check(world.player.x>x&&world.player.mp==mp&&!runtime.attacking(),
            "The rejection maintains consecutive tick state, preserves unrelated held movement and never auto-retries the rejected cast");
        world.setCharacterAppearance(goodAppearance);world.releaseInputs();
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(runtime.attacking()&&world.player.mp<mp&&runtime.remainingCooldown(skill->key,world.nowMs())>0,
            "After source repair a new explicit request can start through the same runtime and unchanged configuration");
        samples["source_fault_recovery"]={{"diagnostics",diagnostics},{"configuration",configuration},{"mp_before",mp},{"mp_after_repair",world.player.mp}};
    }
    {
        ReaderWorld fixture(pvf,assets,regions,characters,1,root/"identity-exhaustion");auto &world=fixture.world;
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto *equipment=fixture.progression.item(fixture.progression.state.at("experimental_starter").at("equipment_id").get<int>());
        check(equipment!=nullptr,"Identity exhaustion fixture retains its source weapon");
        const int subtype=int(equipment->source.number("[sub type]",-1));const ExperimentalSkillRow *skill=nullptr;
        for(const auto &row:plan.skills)if(row.second.kind==SkillSourceKind::Active&&row.second.data) {
            const auto cost=evaluateCharacterSkillCosts(*row.second.data,1,plan.characterDefinition,subtype,false,{}, {},inferred1031SkillCostAbsencePolicy());
            if(cost.consumeMp()&&*cost.consumeMp()>0&&*cost.consumeMp()<=world.player.maxMp&&cost.cooldownMs()&&*cost.cooldownMs()>0) {skill=&row.second;break;}
        }
        check(skill!=nullptr,"Identity exhaustion uses an affordable positive-cost source SKL");
        runtime.configuration().configureBasicAttackTemplate(skill->key,1,plan);runtime.configuration().assignSlot(0,skill->key,plan);
        world.idSources().attacks=MonotonicIds(0);world.player.mp=world.player.maxMp;const int mp=world.player.mp;
        const auto ids=noInputRequestIds(world),sequence=runtime.snapshotDiagnostics().at("action_sequence");
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.player.mp==mp&&!runtime.attacking()&&runtime.remainingCooldown(skill->key,world.nowMs())==0&&
            noInputRequestIds(world)==ids&&runtime.snapshotDiagnostics().at("action_sequence")==sequence,
            "Exhausted attack IDs reject before MP/CD or action publication and never wrap the terminal watermark");
        const auto diagnostics=world.experimentalDiagnostics().at("world");
        check(!diagnostics.empty()&&diagnostics.back().at("code")=="experimental_attack_source_preflight_rejected",
            "Identity preflight failure remains an explicit rejection at a valid fixed-tick boundary");
        samples["identity_exhaustion"]={{"diagnostics",diagnostics},{"ids",noInputRequestIds(world)}};
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual same-job source weapon contact, persistent frame16 sound and failed source transaction/recovery; no frontend or native parity claim"}};
}
} // namespace dnf
