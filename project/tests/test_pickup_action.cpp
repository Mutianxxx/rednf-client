#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <stdexcept>
namespace dnf {
Json runPickupActionTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){checks.push_back({{"passed",pass},{"message",message}});
        if(!pass)throw std::runtime_error(message);};
    try {
    RegionCatalog regions(pvf,assets);
    const std::array<std::pair<int,const char *>,7> jobs={{{0,"swordman"},{1,"fighter"},{2,"gunner"},{3,"mage"},{4,"priest"},{5,"atgunner"},{8,"atmage"}}};
    for(const auto &entry:jobs)for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        const int job=entry.first;const std::string name=entry.second;
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute(std::string("pick-")+name+ani_clock::policyName(clock)));
        store.data["characters"][0]={{"name","PickupSource"},{"class",name},{"identity",CharacterIdentity{job,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);world.configureAnimationClock(clock);
        const auto floor=[&](){world.changeScene();world.monsters.clear();world.events.clear();world.combat=true;world.freezeAi=true;
            world.releaseInputs();world.idle();world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.hp=p.maxHp;p.mp=p.maxMp;p.dead=false;
            p.life=ActorLife::Alive;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const auto path=world.characterSource().motion("[getitem motion]");const auto clip=assets.animation(path);
        check(!clip->frames.empty()&&clip->duration>0,"Own job "+std::to_string(job)+" source CHR GetItem has a finite ANI");
        floor();const auto mp=world.player.mp;const auto normal=world.skillState().snapshot(world.nowMs());
        const auto rng=world.randomStreams().snapshot();auto ids=world.idSources().snapshot();
        check(world.tryPickupAction(),"Actual source pickup accepted for job "+std::to_string(job));
        check(world.pickupActionActive()&&world.actorAni()==path&&world.player.animation=="getitem"&&world.player.animationClock&&
            world.player.animationClock->ratePercent==100,"Pickup owns exact own source body and rate100 independently from combat clock");
        check(world.player.mp==mp&&world.idSources().snapshot()==ids&&world.randomStreams().snapshot()==rng,
            "Acceptance publishes no MP cost, combat ID or RNG");
        check(world.pickupActionTrace().at("duration_ms")==clip->duration&&!world.pickupActionTrace().at("resources").empty(),
            "Source receipt retains exact duration and actual body/equipment source closure");
        const auto start=world.nowMs();int ticks=0,objectTicks=0;
        world.setObjectTick([&](World &){++objectTicks;});
        while(world.pickupActionActive()&&ticks<240) {
            world.attackVolumes.clear();world.normalAttack();world.activate(0);
            world.enqueue({world.simulationNanoseconds(),4,true});world.enqueue({world.simulationNanoseconds(),20,true});
            world.enqueue({world.simulationNanoseconds(),4,false});world.enqueue({world.simulationNanoseconds(),20,false});
            if(auto *r=world.experimentalRuntime()) {
                CharacterActionRequest direct;direct.action=CharacterAction::BasicAttack;direct.inputKey=4;direct.inputDown=true;r->request(direct);
            }
            world.advanceSingleTick();++ticks;
            check(world.attackVolumes.empty()&&world.player.mp==mp&&world.activeSkill()<0&&world.player.animation.find("attack")==std::string::npos&&
                (!world.experimentalRuntime()||!world.experimentalRuntime()->attacking()),"Pickup cannot enter any direct/queued attack consumer");
            if(world.pickupActionActive())check(world.actorAni()==path&&world.player.animationClock&&world.player.animationClockSource==path,
                "Every pickup tick projects own body clock through actual renderer source binding");
        }
        world.setObjectTick({});
        check(!world.pickupActionActive()&&ticks<240&&world.nowMs()-start>=clip->duration&&world.nowMs()-start-clip->duration<=17,
            "Pickup ends on source finite delay boundary without speed scaling");
        check(objectTicks==ticks,"Shared object/world fixed-tick consumer keeps advancing during pickup");
        for(int t=0;t<8;++t)world.advanceSingleTick();
        check(world.activeSkill()<0&&world.player.animation.find("attack")==std::string::npos&&(!world.experimentalRuntime()||!world.experimentalRuntime()->attacking())&&world.attackVolumes.empty(),
            "Suppressed pickup X and direct requests leave no deferred attack");
        check(world.skillState().snapshot(world.nowMs())==normal,"Pickup keeps normal skill/advancement ledger unchanged");
        evidence.push_back({{"job",job},{"clock",ani_clock::policyName(clock)},{"source",world.pickupActionTrace()},{"ticks",ticks}});
        for(const auto *reason:{"air","dead","stun","recovery","hitstop","attack"}) {
            floor();const std::string r=reason;
            if(r=="air")world.player.z=20;else if(r=="dead"){world.player.dead=true;world.player.life=ActorLife::Dying;}
            else if(r=="stun")world.player.stunUntil=world.nowMs()+1000;else if(r=="recovery")world.player.recovery=1;
            else if(r=="hitstop")world.player.hitStopped=true;else {world.normalAttack();world.advanceSingleTick();}
            const auto before=world.player.animation,position=world.actorAni();const auto oldMp=world.player.mp;
            const auto beforeIds=world.idSources().snapshot(),beforeRng=world.randomStreams().snapshot();
            check(!world.tryPickupAction()&&!world.pickupActionActive()&&world.player.animation==before&&world.actorAni()==position&&world.player.mp==oldMp&&
                world.idSources().snapshot()==beforeIds&&world.randomStreams().snapshot()==beforeRng,"Pickup rejects "+r+" without replacing live actor state");
        }
        floor();auto &appearance=const_cast<CharacterAppearance &>(world.characterAppearance());
        const auto original=appearance.bodyMotions;
        appearance.bodyMotions.erase(std::remove_if(appearance.bodyMotions.begin(),appearance.bodyMotions.end(),[&](const auto &v){return v.resource.path==path;}),appearance.bodyMotions.end());
        const auto before=world.player.animation;const auto beforeIds=world.idSources().snapshot(),beforeRng=world.randomStreams().snapshot();
        check(!world.tryPickupAction()&&!world.pickupActionActive()&&world.player.animation==before&&world.idSources().snapshot()==beforeIds&&
            world.randomStreams().snapshot()==beforeRng&&world.pickupActionTrace().at("code").get<std::string>().find("preflight_rejected")!=std::string::npos,
            "Missing own appearance binding fails actual source preparation before pose/ID/RNG publication");
        appearance.bodyMotions=original;
        for(const auto *reason:{"claim_cancel","scene","idle","hurt","death","recovery"}) {
            floor();check(world.tryPickupAction(),"Exit fixture accepts source pickup");world.advanceSingleTick();
            const std::string r=reason;
            if(r=="claim_cancel")world.cancelPickupAction();else if(r=="scene")world.changeScene();else if(r=="idle")world.idle();
            else if(r=="hurt"){world.player.animation="damage1";world.player.animationPath.clear();world.player.stunUntil=world.nowMs()+250;}
            else if(r=="recovery")world.player.recovery=1;else {world.player.dead=true;world.player.life=ActorLife::Dying;}
            world.advanceSingleTick();check(!world.pickupActionActive()&&world.player.animationPath!=path&&world.player.animationClockSource!=path&&world.attackVolumes.empty(),
                "No pickup pose/clock/attack survives "+r);
        }
        if((job==0||job==3)&&clock==ani_clock::ClockPolicy::SourceDelay100) {
            const auto schedule=[&](int fps,bool catchup) {
                Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
                CharacterStore c(std::filesystem::absolute(std::string("pick-replay-")+name+std::to_string(fps)));
                c.data["characters"][0]={{"name","ReplayPickup"},{"class",name},{"identity",CharacterIdentity{job,0,0}.json()},
                    {"level",1},{"skill_initialization","source-v1"}};c.apply(0,w,p);w.configureAnimationClock(clock);
                w.monsters.clear();w.combat=true;w.freezeAi=true;w.events.clear();w.player.x=w.player.px=600;w.player.y=w.player.py=300;
                check(w.tryPickupAction(),"Replay accepts actual source pickup");Json frames=Json::array();
                w.setObjectTick([&](World &v){frames.push_back({{"tick",v.tick},{"active",v.pickupActionActive()},{"pose",v.player.animation},
                    {"path",v.actorAni()},{"mp",v.player.mp},{"clock",v.player.animationClock?Json{{"frame",v.player.animationClock->frame},
                    {"elapsed",v.player.animationClock->elapsedMs},{"ended",v.player.animationClock->ended}}:Json()}});});
                constexpr int64_t total=2000000000;int64_t prev=0;
                if(catchup){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
                else for(int f=1;f<=fps*2;++f){auto now=total*f/(fps*2);w.advance(now-prev);prev=now;}
                check(w.tick==120&&w.pendingTicks()==0,"Every source pickup simulation tick completes under render pump");return frames;
            };
            const auto reference=schedule(60,false);
            for(int fps:{30,144})check(schedule(fps,false)==reference,"Own pickup pose/clock agrees at FPS "+std::to_string(fps));
            check(schedule(1,true)==reference,"Budget8 catchup preserves source pickup timeline");
        }
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},{"native_admission_parity",false}};
    }catch(const std::exception &error){writeJson("pickup-action-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
