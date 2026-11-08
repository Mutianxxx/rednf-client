#include "dnf/combat.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/storage.hpp"
#include "dnf/effect_plan.hpp"
#include <numeric>
#include <stdexcept>

namespace dnf {
Json runAnimationClockTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    Json experimentalRoundTrips=Json::array();
    const auto require=[&](bool ok,const char *name) {
        if(!ok)throw std::runtime_error(std::string("Animation clock consumer: ")+name);
        checks.push_back(name);
    };
    const auto source=ani_clock::ClockPolicy::SourceDelay100;
    const auto inferred=ani_clock::ClockPolicy::Inferred60UsPercentDeadlines;
    for(const auto policy:{source,inferred}) {
        World world(pvf,assets);world.freezeAi=true;world.configureAnimationClock(policy);
        const auto before=world.player.mp;
        world.normalAttack();
        require(world.player.animationClock&&world.player.poseFrame==-1,"ordinary attack publishes initial clock without freezing tween");
        const auto animation=assets.animation(world.actorAni());
        const auto original=animation->frames.front().duration;
        uint64_t elapsed=0;
        for(int tick=0;tick<9;++tick)world.advanceSingleTick();
        elapsed=world.player.animationClock->elapsedMs;
        const auto frame=world.player.animationClock->frame;
        const auto eventCount=world.events.size();
        world.player.hitStopTicks=3;
        for(int tick=0;tick<3;++tick) {
            world.advanceSingleTick();
            require(world.player.animationClock&&world.player.animationClock->elapsedMs==elapsed&&
                world.player.animationClock->frame==frame&&world.player.animationClock->paused,
                "hit pause advances tick identity with zero animation delta");
        }
        require(world.events.size()==eventCount,"paused ordinary clock does not replay sound or attack events");
        world.advanceSingleTick();
        require(world.player.animationClock->elapsedMs>elapsed,"first resumed tick advances the root once");
        const auto motion=readCharacterAttackMotion(assets,world.characterAppearance(),world.actorAni());
        const auto boxes=motion.boxesAt(*world.player.animationClock);
        require(!motion.body->frames.empty()&&animation->frames.front().duration==original,
            "actual body and weapon consumer keeps cached decoded delays immutable");
        (void)boxes;
        require(world.player.mp==before,"clock publication and pause do not charge an ordinary action");
        world.changeScene();
        require(!world.player.animationClock&&world.effects.empty(),"room change cancels root and transient visual instances");
        world.normalAttack();const auto checkpoint=world.simulationCheckpoint();
        world.restoreSimulationCheckpoint(checkpoint);
        require(!world.player.animationClock&&world.player.animation=="stay","ordinary checkpoint restore cancels transient animation clocks");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.freezeAi=true;world.configureAnimationClock(inferred);
        const auto base=world.prepareBaseAttributes(world.identity(),1);
        auto speeds=evaluateCharacterSpeeds(base,world.characterSource(),std::vector<EquippedSpeedSource>{},CharacterSpeedPolicy::inferredFlatEquipmentV1());
        speeds.attackPerMille=1000;world.applyCharacterSpeeds(speeds);world.normalAttack();
        for(int tick=0;tick<7;++tick)world.advanceSingleTick();
        const auto before=*world.player.animationClock;
        speeds.attackPerMille=1500;world.applyCharacterSpeeds(speeds);world.player.hitStopTicks=3;
        for(int tick=0;tick<3;++tick)world.advanceSingleTick();
        const auto paused=*world.player.animationClock;
        require(paused.elapsedMs==before.elapsedMs&&paused.frame==before.frame&&paused.ratePercent==before.ratePercent,
            "speed change during hit pause defers rate refresh and preserves frozen root pose");
        world.advanceSingleTick();
        require(world.player.animationClock->ratePercent==150,
            "deferred speed change refreshes once on first unfrozen simulation tick");
    }
    {
        World world(pvf,assets);world.freezeAi=true;world.configureAnimationClock(inferred);
        world.normalAttack();world.normalAttack();bool chained=false;
        for(int tick=0;tick<50;++tick) {
            world.advanceSingleTick();
            if(world.player.animation=="attack2") {
                require(world.snapshot().at("last_attack_frame").get<int>()==int(world.player.animationClock->frame),
                    "queued combo consumes new first-frame events and boxes in its installation tick");
                chained=true;break;
            }
        }
        require(chained,"real ordinary source cancel threshold reaches the next swing");
        world.idle();world.advanceSingleTick();world.advanceSingleTick();
        require(world.player.animationClock&&world.player.animationClockSource==world.actorAni()&&world.player.animationClock->loop,
            "waiting body publishes a root clock for same-motion equipment layers");
        const auto elapsed=world.player.animationClock->elapsedMs;world.player.hitStopTicks=2;
        world.advanceSingleTick();world.advanceSingleTick();
        require(world.player.animationClock->elapsedMs==elapsed,"waiting root does not restart when legacy hitstop shifts animStart");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        RegionCatalog regions(pvf,assets);
        const auto fixtureRoot=std::filesystem::absolute("cache/clock-created-character-fixtures");
        size_t roundTrips=0;
        for(const auto &definition:world.characterCatalog().definitions) {
            if(!definition.registration.id||definition.runtimeDeferredByUser)continue;
            const CharacterIdentity identity{definition.registration.id,0,0};
            const auto policy=identity.jobId%2?source:inferred;
            world.configureAnimationClock(policy);
            Progression progression(regions);
            CharacterStore store(fixtureRoot/std::to_string(identity.jobId));
            store.data["characters"][0]={{"name","ClockSourceTest"},
                {"class",std::filesystem::u8path(definition.registration.path).stem().u8string()},{"identity",identity.json()},
                {"level",1},{"skill_initialization","source-v1"}};
            store.apply(0,world,progression);
            require(!world.statReport().at("combat_attributes").is_null(),
                "clock round trip starts from a real created character with source starter equipment");
            world.monsters.clear();world.freezeAi=true;
            for(int tick=0;tick<3;++tick)world.advanceSingleTick();
            const auto waitingSource=world.actorAni();
            require(world.player.animation=="stay"&&world.player.animStart==0&&world.player.animationClock&&
                world.player.animationClock->loop&&world.player.animationClock->elapsedMs>0,
                "real experimental waiting motion installs and advances before an attack");
            world.normalAttack();world.advanceSingleTick();
            bool attacked=world.player.animation=="experimental_attack",returned=false;
            const auto initialRuntime=world.experimentalRuntime()->snapshotDiagnostics();
            const auto attackPolicy=initialRuntime.at("action_timing").is_null()?policy:source;
            if(!attacked||!world.player.animationClock||world.player.animationClock->policy!=attackPolicy)
                writeJson("reports/clock-fixture-policy-failure.json",{{"identity",identity.json()},
                    {"runtime",initialRuntime},{"world",world.snapshot()},
                    {"expected_policy",ani_clock::policyName(attackPolicy)}});
            require(attacked&&world.player.animationClock&&world.player.animationClock->policy==attackPolicy,
                "real experimental normal attack uses requested source clock or exclusive pre-scaled controller delays");
            const auto attackAnimation=assets.animation(world.actorAni());
            std::vector<int32_t> delays;
            for(const auto &frame:attackAnimation->frames)delays.push_back(frame.duration);
            const auto deadlineMs=ani_clock::deadlineCycle({delays.data(),delays.size()},world.player.animationClock->ratePercent,attackPolicy);
            // Gunner's controller exits the raise on entering the terminal
            // held pose. Test actual input recovery, not a ten-second wait
            // that accidentally blesses a missing state transition.
            const bool gunner=identity.jobId==2||identity.jobId==5;
            uint64_t controllerDeadline=gunner?deadlineMs-ani_clock::frameSpan(
                {delays.data(),delays.size()},delays.size()-1,world.player.animationClock->ratePercent,attackPolicy):deadlineMs;
            uint64_t phaseTickSlack=3;
            if(identity.jobId==2) {
                const auto &plan=world.experimentalRuntime()->plan();
                const auto subtype=initialRuntime.at("gunner_ground").at("subtype").get<int>();
                const auto &gun=plan.gunnerBasicSources.at(subtype);
                // These deadlines already include the actual installed actor
                // speed. Numeric formula parity is checked by gunner-basic;
                // this regression checks clock ownership and full recovery.
                const auto &receipt=initialRuntime.at("gunner_ground").at("deadlines");
                GunnerBasicDeadlines deadlines;
                deadlines.shot=receipt.at("shot_ms").get<int32_t>();
                deadlines.continuation=receipt.at("continuation_ms").get<int32_t>();
                deadlines.recovery=receipt.at("recovery_ms").get<int32_t>();
                deadlines.drawRate=receipt.at("draw_rate_permille").get<int32_t>();
                deadlines.shootRate=receipt.at("shoot_rate_permille").get<int32_t>();
                require(gun.values[0]>=1&&deadlines.drawRate>0&&deadlines.shootRate>0,
                    "installed male gun deadlines retain valid source subtype and actor rates");
                const auto raise=gunnerBasicStageTiming(*attackAnimation,0,deadlines);
                require(!raise.runtimeDelays.empty(),"male raise has finite pre-hold source spans");
                const auto *reloadBinding=plan.motion("[etc motion]",4);
                require(reloadBinding!=nullptr,"male complete round trip resolves its own Reload source");
                const auto reload=gunnerBasicStageTiming(*plan.animations.at(reloadBinding->source.memberPath),4,deadlines);
                controllerDeadline=uint64_t(raise.runtimeDurationMs-raise.runtimeDelays.back())+
                    uint64_t(std::max(deadlines.recovery,deadlines.shot))+uint64_t(reload.runtimeDurationMs);
                phaseTickSlack=6; // Each authored phase may install at a separate fixed-tick endpoint.
            }
            const auto attackTickBudget=ani_clock::addChecked(ani_clock::multiplyChecked(controllerDeadline,60),999)/1000+phaseTickSlack;
            const auto attackStarted=world.tick;
            for(uint64_t tick=0;tick<attackTickBudget;++tick) {
                world.advanceSingleTick();
                if(world.player.animation=="experimental_attack") {
                    attacked=true;
                    const bool controlled=!world.experimentalRuntime()->snapshotDiagnostics().at("action_timing").is_null();
                    const auto expectedPolicy=controlled?source:policy;
                    require(world.player.animationClock&&world.player.animationClock->policy==expectedPolicy&&
                        world.player.animationClockSource==world.player.animationPath&&!world.player.animationClock->loop,
                        "locomotion owner release preserves the actual experimental combat snapshot");
                } else if(attacked&&!world.experimentalRuntime()->attacking()&&world.player.animation=="stay") {
                    returned=true;break;
                }
            }
            if(!attacked||!returned) {
                writeJson("reports/animation-clock-roundtrip-failure.json",{{"job",definition.job},{"identity",identity.json()},
                    {"attack_observed",attacked},{"waiting_return_observed",returned},{"player_animation",world.player.animation},
                    {"animation_source",world.actorAni()},{"tick",world.tick},{"world",world.snapshot()},
                    {"source_duration_ms",attackAnimation->duration},{"policy_deadline_ms",deadlineMs},{"tick_budget",attackTickBudget},
                    {"experimental",world.experimentalDiagnostics()}});
                throw std::runtime_error("Animation clock consumer: experimental attack round trip failed for "+definition.job+
                    "; animation="+world.player.animation+"; attack_observed="+std::to_string(attacked));
            }
            require(attacked&&returned,"real experimental attack naturally returns to waiting without an explicit idle reset");
            require(identity.jobId!=2||uint64_t(world.tick-attackStarted)<=attackTickBudget,
                "male complete Raise Shoot Reload chain recovers within its exact source-derived phase budget");
            require(identity.jobId!=5||world.tick-attackStarted<60,
                "female ordinary Raise still recovers within one second while source long hold stays intact");
            require(attackAnimation->duration==std::accumulate(delays.begin(),delays.end(),int64_t(0)),
                "controller recovery does not truncate or rewrite source ANI delays");
            require(world.actorAni()==waitingSource&&world.player.animStart==0&&world.player.animationClock&&
                world.player.animationClockSource==waitingSource&&world.player.animationClock->loop&&
                world.player.animationClock->elapsedMs==0&&world.player.animationClock->lastTick==uint64_t(world.tick),
                "return to the identical experimental waiting source installs a fresh root at the current tick");
            const auto returnedAt=world.tick;
            for(int tick=0;tick<3;++tick) {
                world.advanceSingleTick();
                require(world.player.animation=="stay"&&world.player.animationClock&&
                    world.player.animationClock->lastTick==uint64_t(world.tick)&&world.player.animationClock->elapsedMs>0,
                    "experimental waiting root advances consecutively after the complete attack round trip");
            }
            experimentalRoundTrips.push_back({{"identity",identity.json()},{"job",definition.job},{"clock_policy",ani_clock::policyName(policy)},
                {"attack_source",attackAnimation->path},{"source_duration_ms",attackAnimation->duration},{"policy_deadline_ms",deadlineMs},
                {"controller_deadline_ms",controllerDeadline},{"attack_clock_policy",ani_clock::policyName(attackPolicy)},
                {"tick_budget",attackTickBudget},{"attack_started_tick",attackStarted},{"waiting_return_tick",returnedAt},
                {"resumed_waiting_tick",world.tick},{"same_waiting_source",world.actorAni()==waitingSource},{"status","pass"}});
            ++roundTrips;
        }
        require(roundTrips==9,"all nine opt-in experimental jobs complete waiting attack and resumed waiting clock ownership");
    }
    {
        const auto catalog=std::make_shared<CharacterCatalog>(pvf);
        for(const auto &definition:catalog->definitions) {
            if(!definition.registration.id||definition.runtimeDeferredByUser)continue;
            const auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,*catalog,
                {definition.registration.id,0,0}));
            for(const auto policy:{std::optional<ani_clock::ClockPolicy>{},std::optional<ani_clock::ClockPolicy>{source},
                                  std::optional<ani_clock::ClockPolicy>{inferred}}) {
                ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(policy);
                ExperimentalActorState actor;actor.mp=10000;actor.attackPerMille=1000;actor.movePerMille=1000;
                if(definition.registration.id==2)actor.weaponSubtype=plan->gunnerBasicSources.begin()->first;
                const auto key=[&](int input,uint64_t tick) {
                    CharacterActionRequest r;r.action=input==4?CharacterAction::BasicAttack:CharacterAction::Move;
                    r.inputKey=input;r.inputDown=true;r.simulationMs=FixedStepClock::millisecondsAtTick(tick);
                    require(runtime.request(r),"actual ordinary attack and movement input accepted");
                };
                key(4,0);const auto initial=runtime.advance(1,actor,[](double,double){return true;});
                actor=initial.actor;
                require(runtime.attacking(),"ordinary clock fixture starts an actual qualified source attack");
                key(4,1);uint64_t boundary=0;
                for(uint64_t tick=2;tick<=120;++tick) {
                    auto paused=actor;paused.hitStopped=tick<=4;
                    const auto result=runtime.advance(tick,paused,[](double,double){return true;});actor=result.actor;actor.hitStopped=false;
                    if(tick<=4)require(result.animationAgeMs==initial.animationAgeMs,
                        "hitstop exactly freezes the installed ordinary action age and its cancel/held-tail boundaries");
                    if(runtime.activeActionSequence()==std::optional<uint64_t>(2)||!runtime.attacking()){boundary=tick;break;}
                }
                require(boundary>0,"all experimental jobs accept queued attack or recover without long held-tail lock");
                if(!definition.basicAttackCancelFrames.empty()) {
                    const auto ani=plan->animations.at(plan->motion("[attack motion]")->source.memberPath);
                    require(boundary*1000/60<uint64_t(ani->duration)+100,
                        "native source cancel tables are consumed before or at ordinary recovery");
                }
                // Let the queued action finish, then a real held movement
                // must move the actor without idle()/cancel() escape hatches.
                key(1,boundary);
                bool moved=false;
                for(uint64_t tick=boundary+1;tick<=boundary+180;++tick) {
                    const auto before=actor.x;const auto result=runtime.advance(tick,actor,[](double,double){return true;});actor=result.actor;
                    if(actor.x>before&&!runtime.attacking()){moved=true;break;}
                }
                require(moved,"normal movement resumes after queued ordinary attacks under every clock policy");
            }
        }
    }
    {
        Animation body,child;body.path="body";child.path="child";
        AniFrame a,b,c;a.duration=40;b.duration=80;c.duration=50;
        a.x=0;b.x=80;a.properties["10"]=true;
        body.frames={a,b};body.duration=120;
        AniFrame x=a,y=b,z=c;x.duration=100;y.duration=200;
        x.boxes={{15,1,2,3,4,5,6}};y.boxes={{15,7,8,9,10,11,12}};
        child.frames={x,y,z};child.duration=350;
        AnimationPlayback clock;clock.install(body,false,200,inferred,0);
        const auto advanced=clock.advance(1,false);
        const auto pose=body.samplePose(advanced.snapshot,ani_render::RenderProfile::Inferred60Us1031);
        require(pose.progress>.7&&pose.progress<.9&&pose.x>55&&pose.x<75,
            "render tween divides runtime local time by accelerated deadline span");
        const auto projected=child.followClock(body,advanced.snapshot,false);
        require(projected.frame==advanced.snapshot.frame&&projected.spanMs==advanced.snapshot.spanMs&&
            child.frames[0].duration==100&&child.frames[1].duration==200&&child.frames[2].duration==50,
            "child min-delay view follows root and preserves own trailing delay and bytes");
        CharacterAttackMotion motion;motion.body=std::make_shared<Animation>(body);motion.weapons={std::make_shared<Animation>(child)};
        const auto boxes=motion.boxesAt(advanced.snapshot);
        require(boxes.size()==1&&boxes[0].x==1,"weapon-only hitbox uses same root-derived frame as rendered layer");
        auto copy=clock;copy.advance(2,false);
        require(clock.snapshot().lastTick==1&&copy.snapshot().lastTick==2,"copied runtime cursor keeps immutable delays alive with independent state");
    }
    Json reference;
    const auto trajectory=[&](int hz,bool catchup) {
        World world(pvf,assets);world.freezeAi=true;world.configureAnimationClock(inferred);
        Json rows=Json::array();world.normalAttack();world.normalAttack();
        world.setBeforeTick([](World &w){if(w.tick==6)w.player.hitStopTicks=4;});
        world.setObjectTick([&](World &w){
            const auto &s=w.player.animationClock;
            rows.push_back({w.tick,w.player.animation,s?Json(s->frame):Json(),s?Json(s->localMs):Json(),w.events.size()});
        });
        int64_t previous=0;
        if(catchup) {world.advance(1000000000,8);while(world.pendingTicks())world.advance(0,8);}
        else for(int frame=1;frame<=hz;++frame) {
            const auto now=int64_t(frame)*1000000000/hz;world.advance(now-previous,8);previous=now;
            while(world.pendingTicks())world.advance(0,8);
        }
        return rows;
    };
    reference=trajectory(60,false);
    for(int hz:{30,120,144,240})require(trajectory(hz,false)==reference,"actual ordinary frames events and pause are invariant across rendering rates");
    require(trajectory(60,true)==reference,"eight-tick catchup debt preserves the same actual ordinary action timeline");
    {
        World world(pvf,assets);world.freezeAi=true;world.configureAnimationClock(inferred);
        const std::string path="character/swordman/effect/animation/ashenfork_ds/ashenfork_back_normal.ani";
        const auto plan=animationEffectEvents(pvf,assets,path);
        Effect effect;effect.id=7000;effect.animation=path;effect.born=0;effect.expires=2000;
        effect.damageEnabled=false;effect.attached=true;effect.parentId=0;
        world.effects.push_back(effect);world.advanceSingleTick();
        require(world.effects.front().animationClock&&world.effects.front().pauseWithPlayer,
            "effect independently binds source-rate100 clock and separate actor pause policy");
        const auto elapsed=world.effects.front().animationClock->elapsedMs;
        world.player.hitStopTicks=2;world.advanceSingleTick();world.advanceSingleTick();
        require(world.effects.front().animationClock->elapsedMs==elapsed,"attached visual clock pauses without consuming shifted legacy age twice");
        for(int tick=0;tick<35;++tick)world.advanceSingleTick();
        size_t adds=0;
        for(const auto &event:world.events)if(event.kind=="als_event"&&event.source==7000)++adds;
        require(adds==plan.events.size()&&adds==3,"real ALS commands are dispatched once from parent frame visits");
        require(world.effects.size()>1,"real ALS frame events instantiate live child effects");
        world.effects.front().expires=world.nowMs();world.advanceSingleTick();
        require(world.effects.empty(),"removing independent parent cancels its live ALS descendants");
    }
    {
        World world(pvf,assets);world.freezeAi=true;world.configureAnimationClock(inferred);
        Effect root;root.id=8000;root.animation="character/swordman/effect/animation/ashenfork_ds/ashenfork_back_normal.ani";
        root.born=-200;root.expires=2000;root.damageEnabled=false;root.x=root.px=root.trajectoryStartX=100;
        root.speed=400;root.trajectoryMs=280;world.effects.push_back(root);
        int childId=-1;double atBirth=0;
        for(int tick=0;tick<35&&childId<0;++tick) {
            world.advanceSingleTick();
            for(const auto &child:world.effects)if(child.alsParentId==8000) {
                childId=child.id;atBirth=child.x;
                require(child.trajectoryStartX==child.x,"moving ALS child starts its own trajectory at parent current position");break;
            }
        }
        require(childId>=0,"moving real source parent creates an ALS child");
        world.advanceSingleTick();bool found=false;
        for(const auto &child:world.effects)if(child.id==childId) {
            require(child.x>=atBirth&&child.x<=212.001,"new ALS child never jumps back to parent old trajectory origin");found=true;
        }
        require(found,"moving ALS child remains live after its first motion tick");
        for(int tick=0;tick<10;++tick)world.advanceSingleTick();
        for(const auto &child:world.effects)if(child.id==childId)
            require(child.x<=212.001,"ALS child remaining trajectory cannot become unlimited motion at zero remainder");
    }
    return {{"status","pass"},{"checks",checks},{"check_count",checks.size()},{"experimental_waiting_roundtrips",experimentalRoundTrips},
        {"classification","1031 cross-version inference; fixed-tick host scheduling"},
        {"original_game_dynamic_comparison","pending"}};
}
}
