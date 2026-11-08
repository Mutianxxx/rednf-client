#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerReleaseOriginTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message) {
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("release-origin-failed.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    RegionCatalog regions(pvf,assets);
    for(const auto policy:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("release-origin-fixture-"+std::string(ani_clock::policyName(policy))));
        store.data["characters"][0]={{"name","SourceReleaseOrigin"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(policy);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto floor=[&]() {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
            auto &p=world.player;p.x=p.px=500;p.y=p.py=300;p.z=p.pz=0;p.dir=1;p.mp=INT32_MAX;p.dead=false;p.life=ActorLife::Alive;
            p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        };
        const auto press=[&](int key,bool down) {world.enqueue({world.simulationNanoseconds(),key,down});};
        const auto contactCount=[&]() {
            const auto diag=world.femaleGunnerDiagnostics();size_t count=0;
            for(const auto &entity:diag.at("entities"))count+=entity.at("command").at("role")=="channel_contact";return count;
        };
        for(const int id:{36,107})for(const int key:{20,7}) {
            floor();runtime.configuration()=ExperimentalSkillConfiguration(plan);
            runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,plan);
            runtime.configuration().assignSlot(key==7?12:0,SkillKey{5,id},plan);
            const auto normal=world.skillState().snapshot(world.nowMs());press(key,true);bool entered=false;
            for(int tick=0;tick<500&&!entered;++tick){world.advanceSingleTick();entered=contactCount()!=0;}
            check(entered,"Real World initiating skill key reaches one focus/ice channel: "+std::to_string(id)+" key "+std::to_string(key));
            check(contactCount()==1,"One skill activation creates one damage consumer");
            const auto x=world.player.x,y=world.player.y;const auto mp=world.player.mp;press(1,true);press(3,true);
            for(int tick=0;tick<6;++tick){press(key,true);world.advanceSingleTick();}
            check(world.player.x>x&&world.player.y>y&&contactCount()==1&&world.player.mp==mp,
                "Source spraying ratio permits actual XY movement and OS repeat creates no second release/cost");
            press(21,false);press(4,true);press(4,false);world.advanceSingleTick();
            check(contactCount()==1,"Unrelated skill-key release and source ATTACK release cannot stop the user initiating-key channel");
            world.player.hitStopTicks=3;world.advanceSingleTick();const auto pausedX=world.player.x;press(key,false);world.advanceSingleTick();
            check(contactCount()==1&&world.player.x==pausedX,"Hitstop pauses movement and defers queued initiating KEYUP without damaging-state mutation");
            for(int tick=0;tick<6&&contactCount();++tick)world.advanceSingleTick();
            evidence.push_back({{"phase","before_keyup_check"},{"skill",id},{"key",key},{"contact_count",contactCount()},
                {"runtime",runtime.snapshotDiagnostics()},{"world",world.experimentalDiagnostics()}});
            check(contactCount()==0&&!runtime.attacking(),"Actual initiating KEYUP retires contact in the controller/World transaction");
            const auto afterStop=world.player.x;world.advanceSingleTick();
            check(world.player.x>afterStop,"Held movement resumes ordinary locomotion after channel KEYUP");
            check(world.skillState().snapshot(world.nowMs())==normal,"Test release/movement leaves normal learning ledger unchanged");
            evidence.push_back({{"clock",ani_clock::policyName(policy)},{"skill",id},{"key",key},{"runtime",runtime.snapshotDiagnostics()},
                {"world",world.experimentalDiagnostics()},{"entities_after_stop",world.femaleGunnerDiagnostics()}});
            floor();runtime.configuration().assignSlot(key==7?12:0,SkillKey{5,id},plan);press(key,true);press(key,false);
            bool emitted=false,started=false;
            for(int tick=0;tick<500;++tick){world.advanceSingleTick();emitted|=contactCount()>0;started|=runtime.attacking();if(started&&!runtime.attacking())break;}
            check(started&&!emitted&&!runtime.attacking(),"DOWN and UP before startup completion never publish a focus/ice damaging spray");
            floor();press(key,true);for(int tick=0;tick<500&&!contactCount();++tick)world.advanceSingleTick();
            check(contactCount()==1,"Cancellation fixture enters real hold channel");world.player.recovery=5;world.advanceSingleTick();
            check(contactCount()==0,"Actual actor interruption retires the exact hold channel");
            world.changeScene();check(world.femaleGunnerDiagnostics().at("entities").empty(),"Scene cleanup discards input and every pending spray entity");
        }
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"classification","actual-world; source movement ratio; hold-key is explicit user strategy; basic-bullet origin is unchanged"},
        {"original_dynamic_comparison","pending_user"}};
}
}
