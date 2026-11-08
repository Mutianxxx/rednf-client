#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerSourceCacheTests(Pvf &pvf,Assets &assets) {
    RegionCatalog regions(pvf,assets);Progression progression(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    CharacterStore store(std::filesystem::absolute("source-cache-fixture"));
    store.data["characters"][0]={{"name","SourceCache"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
        {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);
    Json checks=Json::array(),shots=Json::array();
    const auto check=[&](bool pass,const std::string &label) {
        checks.push_back({{"passed",pass},{"message",label}});
        if(!pass){writeJson("source-cache-failed.json",{{"checks",checks},{"shots",shots}});throw std::runtime_error(label);}
    };
    const auto fire=[&](bool bodyOnly) {
        world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
        world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
        auto &p=world.player;p.x=p.px=500;p.y=p.py=300;p.z=p.pz=0;p.vz=0;p.dir=1;p.mp=INT32_MAX;
        p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        const auto diagnosticsBefore=world.femaleGunnerDiagnostics();
        const auto before=diagnosticsBefore.is_null()?Json():diagnosticsBefore.at("source_work_cache");
        const auto start=std::chrono::steady_clock::now();
        world.enqueue({world.simulationNanoseconds(),4,true});Json bullet;
        for(int tick=0;tick<90;++tick){world.advanceSingleTick();for(const auto &fx:world.effects)
            if(fx.phase=="female-gunner:ordinary_bullet"&&bullet.is_null())bullet=fx.projectileSource;}
        const auto elapsed=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();
        const auto after=world.femaleGunnerDiagnostics().at("source_work_cache");
        check(!bullet.is_null(),"Repeated real X input publishes source bullet");
        check(!bodyOnly||(!bullet.at("diagnostics").empty()&&bullet.at("coordinate_trace").at("muzzle_basis")=="diagnosed_source_body_fallback"),
            "Missing weapon fallback diagnostics survive source cache reuse");
        shots.push_back({{"body_only",bodyOnly},{"before",before},{"after",after},{"world_90_ticks_ms",elapsed},{"bullet",bullet}});
    };
    for(int i=0;i<8;++i)fire(false);
    const auto &first=shots[0].at("after"),&eighth=shots[7].at("after");
    const bool enabled=eighth.at("enabled").get<bool>();
    check(eighth.at("descriptor_requests")==8,"Eight actual World activations request eight source descriptors");
    check(eighth.at("descriptor_loads")==unsigned(enabled?1:8),"Source descriptor work is measured for repeated identical weapon use");
    check(!enabled||(first.at("pixel_decodes")==eighth.at("pixel_decodes")&&first.at("pixels_scanned")==eighth.at("pixels_scanned")),
        "Repeated same-owner source frames add no pixel decode or alpha scan after first activation");
    check(!enabled||eighth.at("point_hits").get<uint64_t>()>=14,"Equipped muzzle and bullet sprite reuse immutable derived points");
    auto appearance=world.characterAppearance();appearance.parts.erase("[weapon]");world.setCharacterAppearance(appearance);
    fire(true);const auto fallbackFirst=shots.back().at("after");fire(true);const auto fallbackSecond=shots.back().at("after");
    check(!enabled||fallbackFirst.at("pixel_decodes")==fallbackSecond.at("pixel_decodes"),"Fallback body source point reuses work without losing per-shot diagnostics");
    const auto normal=world.skillState().snapshot(world.nowMs());world.changeScene();
    check(world.femaleGunnerDiagnostics().at("entities").empty()&&world.femaleGunnerDiagnostics().at("buffs").empty(),
        "Scene retirement clears combat transients while retaining only immutable source work");
    check(world.skillState().snapshot(world.nowMs())==normal,"Source cache has no normal skill ledger consumer");
    World secondWorld(pvf,assets,WorldRules::BetaFoundationV1);secondWorld.enableExperimentalCharacters();
    Progression secondProgression(regions);store.apply(0,secondWorld,secondProgression);
    const auto secondDiagnostics=secondWorld.femaleGunnerDiagnostics();
    check(secondDiagnostics.is_null()||secondDiagnostics.at("source_work_cache").at("descriptor_requests")==0,
        "Independent World does not inherit another owner cache or counters");
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"shots",shots},{"enabled",enabled},
        {"timing_scope","Actual X activation plus 90 simulation ticks, warm-disk private diagnostic; not frontend FPS"}};
}
}
