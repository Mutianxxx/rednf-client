#include "explicit_skill_preview_fixture.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
struct Checks {
    Json rows=Json::array();
    void operator()(bool okay,const std::string &message) {
        if(!okay)throw std::runtime_error("Experimental character: "+message);rows.push_back(message);
    }
    template<class Function> bool rejects(Function function){try{function();}catch(const std::exception &){return true;}return false;}
};
CharacterActionRequest keyRequest(int key,int64_t ms=0,bool down=true) {
    CharacterActionRequest request;request.inputKey=key;request.inputDown=down;request.simulationMs=ms;
    request.action=key==4?CharacterAction::BasicAttack:key==5?CharacterAction::Jump:key<4?CharacterAction::Move:CharacterAction::Skill;
    return request;
}
const ExperimentalSkillRow *usableCostSkill(const ExperimentalCharacterPlan &plan) {
    for(const auto &row:plan.skills)if(row.second.kind==SkillSourceKind::Active&&row.second.data) {
        const auto cost=evaluateCharacterSkillCosts(*row.second.data,1,plan.characterDefinition,-1,false,{}, {},inferred1031SkillCostAbsencePolicy());
        if(cost.consumeMp()&&*cost.consumeMp()>0&&cost.cooldownMs()&&*cost.cooldownMs()>0)return &row.second;
    }return nullptr;
}
void naked(World &world,Progression &progression) {
    progression.state["inventory"]=Json::array();progression.state["equipped"]=Json::object();
    world.applyEquipment(progression);world.combat=true;world.freezeAi=true;world.mapWidth=1200;world.walkRects={{0,185,1200,240}};
    world.player.x=world.player.px=560;world.player.y=world.player.py=300;world.player.dir=1;
}
void deadlineRuntimeChecks(Checks &check,const std::shared_ptr<ExperimentalCharacterPlan> &source) {
    // Synthetic timing/box/sound rows exercise the production runtime. They
    // replace one ANI only in this private fixture plan; no source/cache write.
    auto fixture=std::make_shared<ExperimentalCharacterPlan>(*source);
    fixture->characterDefinition.basicAttackCancelFrames.clear();
    const auto motion=*fixture->motion("[attack motion]");
    auto animation=std::make_shared<Animation>();animation->path=motion.source.memberPath;
    for(const int duration:{0,5,5,70}) {
        AniFrame frame;frame.duration=duration;frame.properties["16"]="clock-fixture-"+std::to_string(animation->frames.size());
        frame.boxes.push_back({15,int(animation->frames.size()),0,0,10,10,10});
        animation->frames.push_back(std::move(frame));animation->duration+=duration;
    }
    fixture->animations[motion.source.memberPath]=animation;
    ExperimentalActorState actor;actor.mp=1000;actor.attackPerMille=1000;
    const auto walk=[](double,double){return true;};
    ExperimentalCharacterRuntime runtime(fixture);
    runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);runtime.request(keyRequest(4));
    auto first=runtime.advance(1,actor,walk);
    std::vector<size_t> frames;for(const auto &frame:first.attacks)frames.push_back(frame.sourceFrame);
    check(first.animationClock&&first.poseFrame==-1&&first.animationClock->frame==3&&first.animationClock->elapsedMs==16&&
        first.animationClock->spanMs==70&&frames==std::vector<size_t>({0,1,2,3})&&first.sounds.size()==5&&
        first.sounds.front()=="R_FT_ATK"&&std::equal(first.sounds.begin()+1,first.sounds.end(),
            std::vector<std::string>({"clock-fixture-0","clock-fixture-1","clock-fixture-2","clock-fixture-3"}).begin()),
        "Deadline runtime publishes zero-prefix and all crossed ANI frame boxes/sounds before one current pose; actual="+
        Json({{"clock",first.animationClock?Json({{"frame",first.animationClock->frame},{"elapsed_ms",first.animationClock->elapsedMs},
                 {"span_ms",first.animationClock->spanMs},{"last_tick",first.animationClock->lastTick},
                 {"rate_percent",first.animationClock->ratePercent},{"ended",first.animationClock->ended}}):Json()},
              {"pose",first.poseFrame},
              {"frames",frames},{"sound_count",first.sounds.size()},{"sounds",first.sounds}}).dump());
    check(std::all_of(first.attacks.begin(),first.attacks.end(),[](const auto &frame){return frame.animationClock&&
        frame.animationClock->frame==frame.sourceFrame&&frame.animationClock->lastTick==1;}),
        "Each crossed source attack carries its matching body-root snapshot for real equipment projection");
    auto candidate=runtime;auto pausedActor=actor;pausedActor.hitStopped=true;
    const auto paused=candidate.advance(2,pausedActor,walk);
    check(paused.animationClock&&paused.animationClock->elapsedMs==16&&paused.animationClock->lastTick==2&&
        paused.animationClock->paused&&paused.attacks.empty()&&paused.sounds.empty()&&
        runtime.snapshotDiagnostics().at("animation_clock").at("last_tick")==1,
        "A paused private candidate changes neither source runtime clock nor sounds/contacts");
    const auto independent=runtime.advance(2,actor,walk);
    check(independent.animationClock->elapsedMs==33&&candidate.snapshotDiagnostics().at("animation_clock").at("elapsed_ms")==16,
        "Copied runtime cursors advance independently while sharing immutable delay ownership");
    runtime.cancel(ControllerCancelReason::RoomChange);
    auto moved=std::move(candidate);
    const auto resumed=moved.advance(3,actor,walk);
    check(resumed.animationClock&&resumed.animationClock->elapsedMs==33&&!resumed.animationClock->paused&&
        resumed.sounds.empty()&&resumed.attacks.size()==1&&resumed.attacks.front().sourceFrame==3,
        "Moved candidate survives original cancellation and resumes once with held-frame contact and no sound replay");
    const auto stable=moved.snapshotDiagnostics();
    check(check.rejects([&]{moved.advance(3,actor,walk);})&&moved.snapshotDiagnostics()==stable,
        "Duplicate owner tick rejects before changing the production runtime clock");
    moved.setAnimationClockPolicy(ani_clock::ClockPolicy::Inferred60UsPercentDeadlines);
    const auto pending=moved.advance(4,actor,walk);
    check(pending.animationClock&&pending.animationClock->policy==ani_clock::ClockPolicy::SourceDelay100,
        "Requested animation policy waits for the next source action boundary");
    moved.advance(5,actor,walk);const auto ended=moved.advance(6,actor,walk);
    check(ended.animationClock&&ended.animationClock->ended&&ended.animationClock->frame==3&&!moved.attacking(),
        "Source action completes at cursor ended while retaining its final published frame");
    moved.request(keyRequest(4));const auto installed=moved.advance(7,actor,walk);
    check(installed.animationClock&&installed.animationClock->ratePercent>100&&installed.animationClock->spanMs==69&&
        installed.animationClock->rateRevision==1&&installed.sounds.size()==5&&installed.sounds.front()=="R_FT_ATK",
        "New inferred action preserves installation rate100.0000076/deadline69 and emits one base cue plus crossed frame sounds");
    auto faster=actor;faster.attackPerMille=1500.75;
    const auto refreshed=moved.advance(8,faster,walk);
    check(refreshed.animationClock&&refreshed.animationClock->ratePercent==150&&refreshed.animationClock->rateRevision==2&&
        refreshed.animationClock->elapsedMs==27&&refreshed.sounds.empty(),
        "Changed effective integer attack stat refreshes/reprojects once without historical sound replay");
    const auto unchanged=moved.advance(9,faster,walk);
    check(unchanged.animationClock&&unchanged.animationClock->rateRevision==2,
        "Unchanged effective attack stat preserves the installed refreshed rate and revision");
    auto blocked=actor;blocked.blocked=true;const auto cancelled=moved.advance(10,blocked,walk);
    check(!moved.attacking()&&!cancelled.animationClock&&cancelled.attacks.empty()&&cancelled.sounds.empty(),
        "Recovery cancels root clock and frame events before publishing a replacement lifecycle pose");
    // A source combo installs at the completed tick boundary; its zero-prefix
    // events belong to the new action and it receives no second tick delta.
    auto comboMotion=motion;comboMotion.slot=1;
    fixture->motions.erase(std::remove_if(fixture->motions.begin(),fixture->motions.end(),[&](const auto &entry){
        return normalize(entry.tag)==normalize(comboMotion.tag)&&entry.slot==1&&entry.occurrence==comboMotion.occurrence;
    }),fixture->motions.end());fixture->motions.push_back(comboMotion);
    ExperimentalCharacterRuntime combo(fixture);combo.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
    combo.request(keyRequest(4));combo.advance(1,actor,walk);combo.request(keyRequest(4));
    ExperimentalTickResult boundary;
    for(uint64_t tick=2;tick<=6;++tick) {
        boundary=combo.advance(tick,actor,walk);
        if(combo.activeActionSequence()==std::optional<uint64_t>(2))break;
    }
    Json comboBoundary={{"active_sequence",combo.activeActionSequence().value_or(0)},
        {"clock",boundary.animationClock?Json{{"elapsed_ms",boundary.animationClock->elapsedMs},
            {"frame",boundary.animationClock->frame},{"last_tick",boundary.animationClock->lastTick},
            {"ended",boundary.animationClock->ended}}:Json(nullptr)},
        {"sounds",boundary.sounds},{"attacks",Json::array()}};
    for(const auto &attack:boundary.attacks)comboBoundary["attacks"].push_back({{"action_sequence",attack.actionSequence},
        {"source_frame",attack.sourceFrame},{"box_count",attack.boxes.size()}});
    const std::vector<std::string> comboPrefixSounds={"R_FT_ATK","clock-fixture-0","clock-fixture-1"};
    const bool comboPrefixAttacks=boundary.attacks.size()==3&&boundary.attacks[0].actionSequence==1&&
        boundary.attacks[0].sourceFrame==3&&boundary.attacks[1].actionSequence==2&&boundary.attacks[1].sourceFrame==0&&
        boundary.attacks[2].actionSequence==2&&boundary.attacks[2].sourceFrame==1;
    check(combo.activeActionSequence()==std::optional<uint64_t>(2)&&boundary.animationClock&&boundary.animationClock->elapsedMs==0&&
        boundary.animationClock->frame==1&&boundary.sounds==comboPrefixSounds&&comboPrefixAttacks,
        "Combo publishes the next action's zero-prefix at the same ended boundary with elapsed zero: "+comboBoundary.dump());
    const auto comboNext=combo.advance(boundary.animationClock->lastTick+1,actor,walk);
    check(comboNext.sounds.size()==2&&comboNext.animationClock->elapsedMs==17,
        "Next combo tick advances once and does not repeat installation-prefix sounds");
    ExperimentalCharacterRuntime legacy(fixture);legacy.request(keyRequest(4));
    auto legacyActor=actor;legacyActor.attackPerMille=2000;const auto old=legacy.advance(1,legacyActor,walk);
    check(!old.animationClock&&old.poseFrame>=0&&old.animationAgeMs==32,
        "Nullopt clock preserves the existing scaled local age and explicit legacy frame path");
    auto invalid=std::make_shared<ExperimentalCharacterPlan>(*fixture);
    auto tiny=std::make_shared<Animation>(*animation);for(auto &frame:tiny->frames)frame.duration=1;tiny->duration=4;
    invalid->animations[motion.source.memberPath]=tiny;
    ExperimentalCharacterRuntime refusal(invalid);refusal.setAnimationClockPolicy(ani_clock::ClockPolicy::Inferred60UsPercentDeadlines);
    refusal.request(keyRequest(4));auto excessive=actor;excessive.attackPerMille=10000;
    const auto denied=refusal.advance(1,excessive,walk);
    check(!refusal.attacking()&&!denied.animationClock&&denied.attacks.empty()&&denied.sounds.empty()&&denied.actor.mp==actor.mp&&
        std::any_of(denied.diagnostics.begin(),denied.diagnostics.end(),[](const auto &row){return row.value("code",std::string())=="experimental_attack_clock_blocked";}),
        "All quantized-zero deadline spans reject the source action explicitly without cost or frame events");
    check(animation->frames.front().duration==0&&animation->frames.back().duration==70&&
        !runtime.snapshotDiagnostics().at("runtime_complete").get<bool>(),
        "Clock operation leaves source fixture delays and incomplete experimental classification intact");
}
}
Json runExperimentalCharacterTests(Pvf &pvf,Assets &assets) {
    Checks check;CharacterCatalog catalog(pvf);
    auto registry=CharacterControllerRegistry::currentCandidate(catalog);const auto before=registry.snapshot();
    size_t baseCount=0,experimentalCount=0;std::shared_ptr<ExperimentalCharacterPlan> sample,clockSample;
    Json sourceRows=Json::array();
    for(const auto &definition:catalog.definitions) {
        const CharacterIdentity identity{definition.registration.id,0,0};if(definition.runtimeDeferredByUser)continue;++baseCount;
        auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,catalog,identity));
        bool ownSkills=true;for(const auto &row:plan->skills)ownSkills&=row.first.jobId==identity.jobId&&
            (row.second.kind==SkillSourceKind::Unknown||row.second.source.packageIdentity==pvf.identity());
        bool ownMotions=true;for(const auto &motion:plan->motions) {
            const auto *source=definition.resource(motion.tag,motion.slot,motion.occurrence);
            ownMotions&=source&&source->path==motion.source.memberPath&&motion.source.packageIdentity==pvf.identity();
        }
        check(ownSkills&&ownMotions,"Every plan preserves exact selected-job CHR slots and typed SKL source identity: "+definition.job);
        check(!plan->snapshot().at("runtime_complete").get<bool>(),"Source plan never advertises complete runtime: "+definition.job);
        if(identity.jobId!=0) {
            check(!registry.supports(identity),"Default candidate does not silently open unfinished job: "+definition.job);++experimentalCount;
            if(!clockSample&&identity.jobId==1&&plan->motion("[attack motion]")&&plan->motion("[move motion]")&&usableCostSkill(*plan))clockSample=plan;
            if(!sample&&identity.jobId==3&&plan->motion("[attack motion]")&&plan->motion("[move motion]")&&usableCostSkill(*plan))sample=std::move(plan);
        }
        sourceRows.push_back({{"identity",identity.json()},{"skills",definition.skills.entries.size()},{"job",definition.job}});
    }
    check(baseCount==10&&experimentalCount==9,"Current PVF supplies all ten non-Creator base sources, with nine opt-in experiments");
    check(registry.snapshot()==before,"Read-only source planning leaves default controller registry unchanged");
    registerExperimentalControllers(registry,catalog,pvf.identity());
    for(const auto &definition:catalog.definitions) {
        const CharacterIdentity identity{definition.registration.id,0,0};const auto *info=registry.find(identity);
        if(definition.runtimeDeferredByUser){check(!registry.supports(identity),"Creator deferral survives experimental opt-in");continue;}
        if(!identity.jobId)continue;
        check(info&&info->executable()&&!info->runtimeComplete()&&!info->nativeConfirmed()&&info->readiness==ControllerReadiness::ExperimentalUserTest,
            "Opt-in admission is executable and explicitly incomplete: "+definition.job);
        check(!registry.supports({identity.jobId,1,0})&&!registry.supports({identity.jobId,0,1}),"Experimental opt-in does not claim advancement or awakening");
    }
    check(bool(clockSample),"Fighter source supports the clock fixture's source attack cue and ordinary ANI");
    check(bool(sample),"Mage source supports the shared template fixture's ordinary ANI and evaluable skill cost");
    deadlineRuntimeChecks(check,clockSample);
    const auto *row=usableCostSkill(*sample);const auto motion=*sample->motion("[attack motion]");
    ExperimentalSkillConfiguration configuration(*sample);
    {
        auto temporary=configuration;
        temporary.configureBasicAttackTemplate(row->key,1,*sample);
        const auto receipt=temporary.snapshot();
        temporary.restore(receipt,*sample);
        check(temporary.snapshot()==receipt&&temporary.binding(row->key)->unknown.contains("user_requested_temporary_template"),
            "Temporary release source choices and their classification survive a configuration round trip");
        temporary.configureSkill(row->key,motion,std::nullopt,1,*sample);
        check(!temporary.binding(row->key)->unknown.contains("user_requested_temporary_template"),
            "A later manual source configuration removes the obsolete temporary-template label");
    }
    const std::array<std::string,13> expectedLabels{{"A","S","D","F","G","H","Q","W","E","R","T","Y","Space"}};
    bool labelsMatch=true;for(size_t i=0;i<13;++i)labelsMatch&=expectedLabels[i]==ExperimentalSkillConfiguration::slotLabels()[i];
    check(labelsMatch,
        "Source experiment exposes the requested 13 independent key slots");
    configuration.configureSkill(row->key,motion,std::nullopt,1,*sample);configuration.assignSlot(12,row->key,*sample);
    auto saved=configuration.snapshot();saved["future_root"]={{"kept",true}};saved["skill_bindings"][0]["future_binding"]=17;
    configuration.restore(saved,*sample);
    check(configuration.snapshot()==saved,"Configuration round-trip preserves unknown root and binding fields");
    const auto stable=configuration.snapshot();auto wrong=saved;wrong["skill_bindings"][0]["skill_source"]["member_sha256"]=std::string(64,'0');
    check(check.rejects([&]{configuration.restore(wrong,*sample);})&&configuration.snapshot()==stable,"Changed SKL source receipt rejects atomically");
    wrong=saved;wrong["pvf_identity"]=std::string(64,'0');
    check(check.rejects([&]{configuration.restore(wrong,*sample);})&&configuration.snapshot()==stable,"Foreign PVF configuration rejects atomically");
    auto foreign=motion;foreign.source.packageIdentity=std::string(64,'0');
    check(check.rejects([&]{configuration.configureSkill(row->key,foreign,std::nullopt,1,*sample);}),"Cross-profile motion binding is rejected");
    check(check.rejects([&]{configuration.assignSlot(13,row->key,*sample);}),"Slot index must fit the exact 13-key configuration");
    bool passiveRejected=false;
    for(const auto &skill:sample->skills)if(skill.second.kind==SkillSourceKind::Passive){passiveRejected=check.rejects([&]{configuration.assignSlot(0,skill.first,*sample);});break;}
    check(passiveRejected,"Visible source passives cannot masquerade as active manual controllers");
    configuration.setWeaponTypePolicy("magical");check(configuration.weaponTypePolicy()=="magical","Experimental weapon-type inference can be switched explicitly");
    configuration.setWeaponTypePolicy("physical");
    check(check.rejects([&]{configuration.setWeaponTypePolicy("invented");}),"Unknown experimental weapon policy rejects");
    ExperimentalCharacterRuntime runtime(sample);runtime.configuration()=configuration;
    ExperimentalActorState actor;actor.x=300;actor.y=260;actor.mp=INT32_MAX;
    runtime.request(keyRequest(1));const auto moved=runtime.advance(1,actor,[](double,double){return true;});
    check(moved.actor.x>actor.x&&moved.animationPath==sample->motion("[move motion]")->source.memberPath,"Held movement consumes the selected job's CHR move ANI");
    runtime.releaseInputs();runtime.cancel(ControllerCancelReason::ExplicitReset);runtime.request(keyRequest(5));
    const auto jumped=runtime.advance(2,actor,[](double,double){return true;});
    check(jumped.actor.z>0&&jumped.actor.vz>0,"Jump consumes fixed-tick arithmetic and real actor vertical state");
    runtime.cancel(ControllerCancelReason::ExplicitReset);runtime.request(keyRequest(7));
    const auto cast=runtime.advance(3,actor,[](double,double){return true;});
    const auto expectedCost=evaluateCharacterSkillCosts(*row->data,1,sample->characterDefinition,-1,false,{}, {},inferred1031SkillCostAbsencePolicy());
    check(cast.actor.mp==actor.mp-*expectedCost.consumeMp()&&cast.animationPath==motion.source.memberPath,
        "Space executes its configured same-job motion and unified evaluated MP cost");
    const auto deadline=int64_t(std::ceil(*expectedCost.cooldownMs()));
    check(runtime.remainingCooldown(row->key,int64_t(FixedStepClock::millisecondsAtTick(3)))==deadline,"Configured source cooldown starts once with evaluated duration");
    const auto cooldownState=runtime.cooldownSnapshot(int64_t(FixedStepClock::millisecondsAtTick(3)));
    const auto capturedMs=int64_t(FixedStepClock::millisecondsAtTick(3));
    const auto restoredDeadlines=ExperimentalCharacterRuntime::prepareCooldownRestore(cooldownState,*sample,capturedMs);
    check(restoredDeadlines.at(row->key)==capturedMs+deadline,"Experimental cooldown save/load preserves remaining time on the restored simulation clock");
    auto wrongCooldown=cooldownState;wrongCooldown["skills"][0]["skill_source"]["member_sha256"]=std::string(64,'0');
    check(check.rejects([&]{ExperimentalCharacterRuntime::prepareCooldownRestore(wrongCooldown,*sample,capturedMs);}),"Cooldown restore rejects altered SKL source identity");
    check(check.rejects([&]{ExperimentalCharacterRuntime::prepareCooldownRestore(cooldownState,*sample,capturedMs+1);}),"Cooldown restore rejects a different checkpoint simulation boundary");
    runtime.cancel(ControllerCancelReason::RoomChange);runtime.configuration().assignSlot(12,std::nullopt,*sample);
    check(!runtime.request(keyRequest(7)),"Clearing Space prevents activation instead of falling back to a Swordman slot");
    auto held=actor;held.hitStopped=true;runtime.request(keyRequest(1));const auto stopped=runtime.advance(4,held,[](double,double){return true;});
    check(stopped.actor.x==actor.x&&stopped.attacks.empty(),"Actor hit pause freezes experimental movement and attack emission");
    check(check.rejects([&]{runtime.advance(6,actor,[](double,double){return true;});}),"Skipped simulation ticks cannot silently enter runtime");
    runtime.cancel(ControllerCancelReason::Reload);runtime.request(keyRequest(4));
    size_t boxes=0;std::set<size_t> sourceFrames;auto next=actor;
    for(uint64_t tick=7;tick<247;++tick){const auto out=runtime.advance(tick,next,[](double,double){return true;});next=out.actor;for(const auto &frame:out.attacks){if(sourceFrames.insert(frame.sourceFrame).second)boxes+=frame.boxes.size();check(frame.motion.source.memberPath==motion.source.memberPath,"Ordinary attack frame retains exact same-job ANI receipt");}if(!runtime.attacking())break;}
    const auto ani=sample->animations.at(motion.source.memberPath);size_t expectedBoxes=0;for(const auto &frame:ani->frames)for(const auto &box:frame.boxes)if(box.type==15)++expectedBoxes;
    check(boxes==expectedBoxes,"Shared attack intervals retain every authored type15 box without losing source frame identity");
    // Actual World dispatch: this is not an animation-only or callback-capture test.
    RegionCatalog regions(pvf,assets);Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);
    const auto swordSkills=world.skills.size();world.enableExperimentalCharacters();world.selectCharacter(sample->identity);dnf::enterExplicitSkillPreviewFixture(world);naked(world,progression);
    check(world.isExperimentalCharacter()&&world.skills.empty()&&world.passives.empty()&&std::all_of(world.bindings.begin(),world.bindings.end(),[](int x){return x==-1;}),
        "World selection removes Swordman runtime skills, passives and legacy slot indexes");
    const double x=world.player.x;world.enqueue({world.simulationNanoseconds(),1,true});world.advance(16666667);
    check(world.player.x>x&&world.actorAni()==sample->motion("[move motion]")->source.memberPath,"World fixed-tick callback dispatches actual source experimental movement");
    world.releaseInputs();world.experimentalRuntime()->configuration()=configuration;world.player.mp=INT32_MAX;
    const auto normalLedger=world.skillState().snapshot(world.nowMs());const int mpBefore=world.player.mp;
    world.enqueue({world.simulationNanoseconds(),7,true});world.advance(16666667);
    check(world.actorAni()==motion.source.memberPath&&world.player.mp==mpBefore-*expectedCost.consumeMp()&&world.skillState().snapshot(world.nowMs())==normalLedger,
        "World Space dispatch consumes independent experimental configuration without changing normal learned levels");
    world.selectCharacter({});check(!world.isExperimentalCharacter()&&world.skills.size()==swordSkills&&!world.passives.empty(),"Switching back to Swordman restores its original compatibility skill views");
    // Swap Space with the first source skill and verify the normal input
    // request and applyInput both consume bindings[12]. Storage covers reload.
    world.bindings[12]=0;world.player.mp=world.player.maxMp;world.freeCd=true;
    world.enqueue({world.simulationNanoseconds(),7,true});world.advance(16666667);
    check(world.activeSkill()==0,"Normal Swordman Space uses its reconfigured slot instead of fixed skill index 12");
    world.idle();world.bindings[12]=-1;world.enqueue({world.simulationNanoseconds(),7,true});world.advance(16666667);
    check(world.activeSkill()==-1,"Empty normal Swordman Space cannot activate the former default skill");
    Json attackCoverage=Json::array();size_t actualDamageJobs=0;
    auto testRoot=std::filesystem::absolute(std::filesystem::path("cache")/"experimental-character-tests"/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    check(testRoot.root_name()==std::filesystem::path("D:/").root_name(),"Experimental persistence fixtures stay on the D drive");
    for(const auto &definition:catalog.definitions) {
        if(!definition.registration.id||definition.runtimeDeferredByUser)continue;
        const CharacterIdentity identity{definition.registration.id,0,0};
        CharacterStore store(testRoot/std::to_string(identity.jobId));
        store.data["characters"][0]={{"name","ExperimentalSourceTest"},{"class",std::filesystem::u8path(definition.registration.path).stem().u8string()},{"identity",identity.json()},
            {"level",1},{"skill_initialization","source-v1"}};
        World actorWorld(pvf,assets,WorldRules::BetaFoundationV1);actorWorld.enableExperimentalCharacters();Progression actorProgression(regions);
        const auto clockPolicy=identity.jobId%2?ani_clock::ClockPolicy::SourceDelay100:ani_clock::ClockPolicy::Inferred60UsPercentDeadlines;
        actorWorld.configureAnimationClock(clockPolicy);
        store.apply(0,actorWorld,actorProgression);dnf::enterExplicitSkillPreviewFixture(actorWorld);
        actorWorld.combat=true;actorWorld.freezeAi=true;actorWorld.mapWidth=1200;actorWorld.walkRects={{0,185,1200,240}};
        actorWorld.player.x=actorWorld.player.px=560;actorWorld.player.y=actorWorld.player.py=300;
        for(int id=1;id<=3;++id) {
            Actor target;target.id=id;target.monsterPath="monster/goblin/goblin.mob";
            target.x=target.px=actorWorld.player.x+id*35;target.y=target.py=actorWorld.player.y;target.dir=-1;
            actorWorld.initializeMonsterAttributes(target,1);actorWorld.monsters.push_back(std::move(target));
        }
        int hpBefore=0;for(const auto &target:actorWorld.monsters)hpBefore+=target.hp;
        actorWorld.normalAttack();bool observedMotion=false,observedClock=false;size_t emittedBoxes=0;
        for(int tick=0;tick<240;++tick) {
            actorWorld.advance(16666667);observedMotion|=actorWorld.player.animation=="experimental_attack";
            // Host-controlled stage delays are already scaled and consume
            // SourceDelay100 exclusively; the requested native-rate strategy
            // remains applicable to unmodified source-delay clips.
            const bool controlled=!actorWorld.experimentalRuntime()->snapshotDiagnostics().at("action_timing").is_null();
            const auto expectedClock=controlled?ani_clock::ClockPolicy::SourceDelay100:clockPolicy;
            observedClock|=actorWorld.player.animationClock&&actorWorld.player.animationClock->policy==expectedClock&&
                actorWorld.player.animationClockSource==actorWorld.player.animationPath&&actorWorld.player.poseFrame==-1;
            emittedBoxes=std::max(emittedBoxes,actorWorld.attackVolumes.size());
            if(observedMotion&&!actorWorld.experimentalRuntime()->attacking()&&!actorWorld.player.hitStopped)break;
        }
        int hpAfter=0;for(const auto &target:actorWorld.monsters)hpAfter+=target.hp;
        if(hpAfter<hpBefore)++actualDamageJobs;
        check(observedMotion,"Actual CharacterStore-created job consumes its own ordinary attack motion: "+definition.job);
        check(observedClock,"Actual experimental adapter publishes a matched source clock and unfrozen pose for body/weapon rendering: "+definition.job);
        check(emittedBoxes>0&&hpAfter<hpBefore,"Every actual created experimental job applies its own body/EQU source ordinary contact to HP: "+definition.job);
        std::map<int,int> hits;for(const auto &event:actorWorld.events)if(event.kind=="hit")++hits[event.target];
        check(std::all_of(hits.begin(),hits.end(),[](const auto &entry){return entry.second<=1;}),"Repeated ordinary source boxes hit each live target at most once: "+definition.job);
        attackCoverage.push_back({{"identity",identity.json()},{"job",definition.job},{"source_weapon",actorProgression.state.value("experimental_starter",Json())},
            {"animation_observed",observedMotion},{"emitted_attack_boxes",emittedBoxes},{"hp_before",hpBefore},{"hp_after",hpAfter},
            {"clock_policy",ani_clock::policyName(clockPolicy)},{"clock_observed",observedClock},
            {"actual_hp_loss",hpBefore-hpAfter},{"damage_receipt",actorWorld.statReport().at("last_damage")},
            {"diagnostics",actorWorld.experimentalDiagnostics()},
            {"status",hpAfter<hpBefore?"source_contact_hp_applied":"motion_only_or_contact_blocked"}});
        actorWorld.idle();actorWorld.releaseInputs();
        actorWorld.changeScene();
        // A prior source ATK may have pushed, lifted or killed these targets.
        // Use fresh source-initialized incarnations for the independent skill
        // release so its real contact is measured at the same authored range.
        actorWorld.monsters.clear();
        for(int id=1;id<=3;++id) {
            Actor target;target.id=id;target.monsterPath="monster/goblin/goblin.mob";
            target.x=target.px=actorWorld.player.x+id*35;target.y=target.py=actorWorld.player.y;target.dir=-1;
            actorWorld.initializeMonsterAttributes(target,1);actorWorld.monsters.push_back(std::move(target));
        }
        actorWorld.synchronizeEntityHandles();
        auto &runtime=*actorWorld.experimentalRuntime();const auto &plan=runtime.plan();
        if(identity.jobId==1) {
            const auto unresolved=std::find_if(plan.skills.begin(),plan.skills.end(),[&](const auto &entry){
                return entry.second.kind==SkillSourceKind::Active&&!plan.sourceSkillActions.count(entry.first);
            });
            ExperimentalSkillConfiguration guarded(plan);
            check(unresolved!=plan.skills.end()&&check.rejects([&]{
                guarded.configureBasicAttackTemplate(unresolved->first,1,plan);
            }),"Unresolved Fighter skills reject the generic template instead of borrowing Upper/basic combat");
        }
        const int equipmentId=actorProgression.state.at("experimental_starter").at("equipment_id").get<int>();
        const auto *equipment=actorProgression.item(equipmentId);
        check(equipment!=nullptr,"Created experimental job retains its qualified source weapon definition: "+definition.job);
        const int subtype=int(equipment->source.number("[sub type]",-1));
        const ExperimentalSkillRow *selectedSkill=nullptr;
        for(const auto &entry:plan.skills) if(entry.second.kind==SkillSourceKind::Active&&entry.second.data) {
            if(identity.jobId==5&&entry.first.skillId!=5)continue;
            if(identity.jobId==2&&entry.first.skillId!=4)continue; // This integration must exercise own Knee, not another temporary gunner skill.
            if(identity.jobId==1) {
                const auto action=plan.sourceSkillActions.find(entry.first);
                if(action==plan.sourceSkillActions.end()||!action->second.native40Jp||
                   action->second.kind!=SourceSkillActionKind::BodyAttack||!action->second.attackDefinition.usable())continue;
            }
            const auto cost=evaluateCharacterSkillCosts(*entry.second.data,1,plan.characterDefinition,subtype,false,{}, {},inferred1031SkillCostAbsencePolicy());
            if(cost.consumeMp()&&*cost.consumeMp()>0&&*cost.consumeMp()<=actorWorld.player.maxMp&&cost.cooldownMs()&&*cost.cooldownMs()>0) {selectedSkill=&entry.second;break;}
        }
        check(selectedSkill!=nullptr,identity.jobId==1?
            "Fighter release fixture selects an affordable 40JP-family body attack with its own source attack definition":
            "Each experimental job has an affordable positive-cost source SKL for temporary release testing: "+definition.job);
        const auto oldSlots=runtime.configuration().slots();
        runtime.configuration().configureBasicAttackTemplate(selectedSkill->key,1,plan);
        check(runtime.configuration().slots()==oldSlots,"Selecting a temporary release template never assigns or overwrites any user key slot: "+definition.job);
        runtime.configuration().assignSlot(0,selectedSkill->key,plan);
        const auto cost=evaluateCharacterSkillCosts(*selectedSkill->data,1,plan.characterDefinition,subtype,false,{}, {},inferred1031SkillCostAbsencePolicy());
        actorWorld.player.mp=actorWorld.player.maxMp;const int startMp=actorWorld.player.mp;
        const auto ledger=actorWorld.skillState().snapshot(actorWorld.nowMs());const auto eventsBefore=actorWorld.events.size();
        actorWorld.enqueue({actorWorld.simulationNanoseconds(),20,true});actorWorld.advanceSingleTick();
        const auto cd=runtime.remainingCooldown(selectedSkill->key,actorWorld.nowMs());const auto started=actorWorld.nowMs();
        check(actorWorld.player.mp==startMp-*cost.consumeMp()&&cd==int64_t(std::ceil(*cost.cooldownMs())),
            "A real World temporary release charges its selected job SKL MP and starts its source cooldown once: "+definition.job);
        for(int i=0;i<3;++i) {actorWorld.enqueue({actorWorld.simulationNanoseconds(),20,true});actorWorld.advanceSingleTick();}
        check(actorWorld.player.mp==startMp-*cost.consumeMp()&&runtime.remainingCooldown(selectedSkill->key,actorWorld.nowMs())==std::max<int64_t>(0,cd-(actorWorld.nowMs()-started)),
            "Repeated skill input during the source action neither repeats MP charges nor restarts cooldown: "+definition.job);
        for(int tick=0;tick<240&&runtime.attacking();++tick)actorWorld.advanceSingleTick();
        std::map<int,int> templateHits;
        for(size_t index=eventsBefore;index<actorWorld.events.size();++index)if(actorWorld.events[index].kind=="hit")++templateHits[actorWorld.events[index].target];
        check(!templateHits.empty()&&std::all_of(templateHits.begin(),templateHits.end(),[](const auto &entry){return entry.second==1;}),
            "Each temporary release reaches actual source contact and deduplicates all weapon/body frames per target: "+definition.job);
        const auto lastDamage=actorWorld.statReport().at("last_damage");const auto lastTrace=lastDamage.dump();
        const auto reviewed=plan.sourceSkillActions.find(selectedSkill->key);
        if(identity.jobId==2)check(selectedSkill->key==SkillKey{2,4}&&reviewed!=plan.sourceSkillActions.end()&&reviewed->second.inferredNativeBody,
            "Shared Gunner release actually exercises the own inferred Knee descriptor instead of falling back to a temporary attack");
        bool classified=false;Json classificationEvidence=Json::object();
        if(reviewed!=plan.sourceSkillActions.end()) {
            const auto &descriptor=reviewed->second;const auto expected=descriptor.snapshot();
            const auto &skillSources=lastDamage.at("sources").at("skill").at("sources");
            const bool exactAdapter=std::any_of(skillSources.begin(),skillSources.end(),[&](const Json &source){
                return source.is_object()&&source.contains("adapter")&&source.at("adapter")==expected;});
            const auto currentSource=[&](const SourceRef &source){return !source.memberPath.empty()&&!source.memberSha256.empty()&&
                source.packageIdentity==pvf.identity()&&source.memberSha256==sha256(pvf.read(source.memberPath));};
            const auto &actualAttack=lastDamage.at("sources").at("attack").at("source");
            const bool exactAttack=actualAttack.at("path")==descriptor.attack.memberPath&&actualAttack.at("member_sha256")==descriptor.attack.memberSha256;
            const bool ownSources=currentSource(descriptor.skill)&&currentSource(descriptor.motion)&&currentSource(descriptor.attack)&&
                descriptor.skill.memberPath==selectedSkill->source.memberPath&&descriptor.skill.memberSha256==selectedSkill->source.memberSha256;
            classified=exactAdapter&&exactAttack&&ownSources&&lastTrace.find("user_requested_temporary")==std::string::npos;
            if(descriptor.inferredNativeBody) {
                const auto &actualMotion=lastDamage.at("sources").at("contact_range").at("evidence").at("motion");
                classified=classified&&actualMotion==descriptor.motion.json();
                check(descriptor.kind==SourceSkillActionKind::BodyAttack&&descriptor.callback.memberPath.empty()&&descriptor.callback.memberSha256.empty()&&
                    expected.at("execution_model")== (descriptor.native40Jp?"40jp-native-family-current1031-source-stages-v1":"inferred_native_body"),
                    "Own native-body reconstruction explicitly has no NUT callback; an empty hash is never used as a successful callback match: "+definition.job);
                classificationEvidence={{"model",expected.at("execution_model")},{"callback_absent",true},{"actual_body_contact_motion",actualMotion}};
            } else {
                check(currentSource(descriptor.callback),"Reviewed NUT classification requires its nonempty current source callback: "+definition.job);
                classified=classified&&lastTrace.find(descriptor.callback.memberSha256)!=std::string::npos;
                classificationEvidence={{"model","reviewed_nut"},{"callback",descriptor.callback.json()}};
            }
            classificationEvidence["skill"]=descriptor.skill.json();classificationEvidence["motion"]=descriptor.motion.json();
            classificationEvidence["attack"]=descriptor.attack.json();classificationEvidence["exact_adapter_receipt"]=exactAdapter;
            classificationEvidence["actual_attack_source"]=actualAttack;
        } else {
            classified=identity.jobId==5?lastTrace.find("skill/atgunner/headshot.skl")!=std::string::npos:
                lastTrace.find("user_requested_temporary")!=std::string::npos;
            classificationEvidence={{"model",identity.jobId==5?"dedicated_female_gunner":"user_requested_temporary"}};
        }
        check(actorWorld.skillState().snapshot(actorWorld.nowMs())==ledger&&classified,
            "Source release retains its exact inferred-body, reviewed-NUT, dedicated female-Gunner or temporary-job classification without modifying normal learning: "+definition.job);
        attackCoverage.back()["temporary_release"]={{"key",selectedSkill->key.json()},{"cost",cost.json()},
            {"mp_before",startMp},{"mp_after",actorWorld.player.mp},{"cooldown_started",cd},{"target_hit_counts",Json::object()},
            {"binding",runtime.configuration().binding(selectedSkill->key)->unknown},{"classification",classificationEvidence}};
        for(const auto &[id,count]:templateHits)attackCoverage.back()["temporary_release"]["target_hit_counts"][std::to_string(id)]=count;
    }
    check(actualDamageJobs==9,"All nine actual non-Swordman source ordinary contacts write shared damage into monster HP");
    return {{"status","pass"},{"checks",check.rows},{"source_jobs",sourceRows},{"ordinary_attack_coverage",attackCoverage},
        {"ordinary_attack_hp_damage_jobs",actualDamageJobs},{"fixture_directory",testRoot.u8string()},
        {"cooldown_policy","source identity + remaining simulation milliseconds, restored at one world checkpoint"},
        {"runtime_complete",false},{"frontend_started",false},{"original_client_comparison","pending_user"}};
}
} // namespace dnf
