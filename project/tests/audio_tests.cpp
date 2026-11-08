#include "dnf/audio.hpp"
#include "dnf/content_profile.hpp"
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace dnf {
Json runAudioTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool ok, const char *message) {
        if (!ok) throw std::runtime_error(std::string("Audio: ") + message);
        checks.push_back(message);
    };
    const std::string xml = R"xml(<AudioTagDatabase>
<!-- <MUSIC ID="FAKE" FILE="fake.ogg"/> -->
<AMBIENT FILE='Sounds\Wind.ogg' ID='WIND' LOOP_DELAY='42' UNKNOWN='a&gt;b'/>
<MUSIC FILE="Music\Theme.ogg" VOLUME_ADJUST="-3" ID="THEME"/>
<EFFECT ID="HIT" FILE="sounds\hit1.ogg" PRIORITY="7"/>
<EFFECT ID="HIT" FILE="sounds\hit2.ogg"/>
<RANDOM ID="R_HIT"><ITEM PROB="100" TAG="HIT"/></RANDOM>
<RANDOM ID="LOOP"><ITEM TAG="LOOP" PROB="1"/></RANDOM>
<RANDOM ID="MIXED"><ITEM TAG="THEME" PROB="1"/><ITEM TAG="HIT" PROB="1"/></RANDOM>
</AudioTagDatabase>)xml";
    AudioCatalog fixture(Bytes(xml.begin(), xml.end()), "fixture.xml");
    require(fixture.find("FAKE").empty(), "commented XML tags do not become declarations");
    require(fixture.find("HIT").size() == 2, "repeated declarations remain ordered variants");
    auto wind = fixture.find("WIND");
    require(wind.size() == 1 && wind[0]->file == "sounds/wind.ogg", "attribute order and single quotes resolve canonical path");
    require(wind[0]->attributes.size() == 4 && wind[0]->attributes[3]["value"] == "a>b" && !wind[0]->rawHex.empty(),
            "unknown XML fields and original tag/attribute bytes retained");
    require(fixture.kind("R_HIT") == AudioKind::Effect && fixture.kind("LOOP") == AudioKind::Unknown &&
            fixture.kind("MIXED") == AudioKind::Unknown, "random categories reject cycles and mixed audio buses");
    auto route = fixture.scene(Json::array({"WIND", "THEME", "HIT", "WIND", "MISSING"}));
    require(route.music == "THEME" && route.ambient == std::vector<std::string>{"WIND"} &&
            route.effects == std::vector<std::string>{"HIT"} && route.issues.size() == 1,
            "full scene sound list routes all categories independent of order");
    auto reverse = fixture.scene(Json::array({"THEME", "WIND"}));
    require(reverse.music == route.music && reverse.ambient == route.ambient, "music first and ambient first yield the same buses");
    require(!fixture.scene(Json::array({17})).issues.empty() && !fixture.scene("THEME").issues.empty(),
            "invalid scene values produce explicit diagnostics");
    require(fixture.snapshot(true)["source_bytes_hex"].get<std::string>().size() == xml.size() * 2,
            "complete source XML bytes survive independently of normalized identifiers");

    AudioCatalog catalog(assets.staticBytes("audio.xml"), "audio.xml");
    for (const auto &map : {"map/elvengard/(r)gate.map", "map/elvengard/elvengard.map", "map/elvengard/d_elvengard.map",
                            "map/lorien/s0.map", "map/lorien/4.map", "map/lorien/b1.map"}) {
        auto plan = catalog.scene(pvf.script(map).values("[sound]"));
        require(!plan.music.empty() && plan.issues.empty(), "current source map selects actual MUSIC declaration");
        if (std::string(map).find("lorien") != std::string::npos)
            require(plan.ambient == std::vector<std::string>{"AMB_FOREST_01"}, "forest ambience remains independent of dungeon music");
    }
    require(catalog.scene(pvf.script("map/lorien/s0.map").values("[sound]")).music == "M_FOREST_01_NEW" &&
            catalog.scene(pvf.script("map/lorien/b1.map").values("[sound]")).music == "M_FOREST_02",
            "ordinary and boss maps retain distinct source music despite identical first sound ID");

    // Headless dummy device validates decoded PCM/callbacks, never audibility.
    if (SDL_WasInit(SDL_INIT_AUDIO)) throw std::runtime_error("Audio tests require an isolated SDL audio subsystem");
    SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
    if (SDL_InitSubSystem(SDL_INIT_AUDIO)) throw std::runtime_error(SDL_GetError());
    Json observed = Json::object();
    try {
        // Exact IDs emitted by normal own-source Knee and current WaterCannon preview consumers.
        // Audio::play is the same concrete event sink as main's sound loop;
        // require source decoding/resampling, not merely an OggS container.
        for(const auto *id:{"GN_JACKSPIKE_01","GN_JACKSPIKE_02","JACKSPIKE_SWING","MW_WCANNON_READY","WCANNON_CAST","CHASER_WATER_HIT","PR_ANTIAIR","FT_UPPER_READY","FT_UPPER_SWING"}) {
            Audio audio(assets); // One sound/device lifetime per assertion.
            require(audio.snapshot()["device_open"].get<bool>(),"isolated source-skill dummy audio device opens");
            const auto beforeEffect=audio.snapshot()["buses"]["EFFECT"]["nonzero_mixed_samples"].get<uint64_t>();
            audio.play(id);const auto prepared=audio.snapshot();bool decoded=false;
            for(const auto &request:prepared["recent_requests"])if(request.value("id",std::string())==id&&
                request.value("status",std::string())=="prepared"&&request.value("resolved_id",std::string())==id&&
                request.value("source_bytes",0)>4&&request.value("source_rate",0)>0&&request.value("source_channels",0)>0&&
                request.value("output_frames",0)>0)decoded=true;
            require(decoded,"Concrete own-source skill event decodes actual source PCM through Audio::play");
            bool mixed=false;for(int tick=0;tick<125&&!mixed;++tick) {
                mixed=audio.snapshot()["buses"]["EFFECT"]["nonzero_mixed_samples"].get<uint64_t>()>beforeEffect;
                if(!mixed)SDL_Delay(20);
            }
            require(mixed,"Concrete own-source skill sound reaches dummy-device nonzero effect PCM");
        }
        Audio audio(assets);
        require(audio.snapshot()["device_open"].get<bool>(), "isolated dummy audio device opens");
        audio.scene(pvf.script("map/lorien/s0.map").values("[sound]"));
        auto initial = audio.snapshot();
        auto count = [](const Json &snapshot, const char *kind, const char *id = nullptr) {
            int n = 0;
            for (const auto &voice : snapshot["voices"])
                if (voice["kind"] == kind && (!id || voice["id"] == id)) ++n;
            return n;
        };
        require(count(initial, "MUSIC", "M_FOREST_01_NEW") == 1 && count(initial, "AMBIENT", "AMB_FOREST_01") == 1,
                "runtime commits independent music and ambience voices");
        auto waitMixed = [&](const char *bus) {
            for (int i = 0; i < 125; ++i) {
                if (audio.snapshot()["buses"][bus]["nonzero_mixed_samples"].get<uint64_t>() > 0) return true;
                SDL_Delay(20);
            }
            return false;
        };
        require(waitMixed("MUSIC") && waitMixed("AMBIENT"), "both buses actually emit nonzero decoded samples");
        auto before = audio.snapshot();
        audio.scene(pvf.script("map/lorien/4.map").values("[sound]"));
        auto same = audio.snapshot();
        auto mixed = [](const Json &snapshot, const char *kind) {
            for (const auto &v : snapshot["voices"]) if (v["kind"] == kind) return v["mixed_samples"].get<uint64_t>();
            return uint64_t(0);
        };
        require(mixed(same, "MUSIC") >= mixed(before, "MUSIC") && mixed(same, "MUSIC") > 0 &&
                same["request_count"] == before["request_count"], "same source track across rooms preserves phase without decoding or restart");
        for (int i = 0; i < 40; ++i) audio.play("sounds/amb/amb_forest_01.ogg");
        audio.scene(pvf.script("map/lorien/b1.map").values("[sound]"));
        auto boss = audio.snapshot();
        require(count(boss, "MUSIC", "M_FOREST_02") == 1 && count(boss, "AMBIENT") == 1 &&
                boss["dropped_effects"].get<uint64_t>() > 0 && count(boss, "EFFECT") <= 32,
                "effect voice saturation cannot discard boss music or ambience");
        audio.music("NO_SUCH_MUSIC_FOR_RETRY_TEST"); audio.music("NO_SUCH_MUSIC_FOR_RETRY_TEST");
        auto failed = audio.snapshot();
        require(count(failed, "MUSIC") == 0 && failed["unresolved_ids"]["NO_SUCH_MUSIC_FOR_RETRY_TEST"] == 2,
                "failed same-ID music requests retry and never commit a false active voice");
        audio.music("M_CHARACTER_SELECT");
        auto selection = audio.snapshot();
        require(count(selection, "MUSIC", "M_CHARACTER_SELECT") == 1 && count(selection, "AMBIENT") == 0,
                "screen music replaces dungeon music and clears scene ambience");
        audio.setVolumes(0, .5f, .4f, .3f);
        auto muted = audio.snapshot(); SDL_Delay(80); auto afterMute = audio.snapshot();
        require(afterMute["nonzero_output_samples"] == muted["nonzero_output_samples"] &&
                afterMute["output_samples"].get<uint64_t>() > muted["output_samples"].get<uint64_t>(),
                "master mute silences PCM while the independent audio clock keeps running");
        audio.setVolumes(2, -.5f, .75f, .25f);
        require(audio.volumes()["master"] == 1 && audio.volumes()["music"] == 0 && audio.volumes()["effects"] == .75f,
                "per-bus volume controls clamp finite input to local 0..1 policy");
        std::atomic<bool> snapshotsOk{true};
        std::thread reader([&] {
            try { for (int i = 0; i < 100; ++i) if (!audio.snapshot().contains("voices")) snapshotsOk = false; }
            catch (...) { snapshotsOk = false; }
        });
        for (int i = 0; i < 100; ++i) audio.setVolumes(1, i % 2 ? .5f : 1, 1, 1);
        reader.join();
        require(snapshotsOk, "diagnostics snapshots synchronize with callback and volume writers");
        require(audio.snapshot()["errors"].empty(), "real source OGG tracks decode without audio errors");
        observed = {{"initial", initial}, {"same_track", same}, {"boss_under_effect_load", boss},
                    {"failed_retry", failed}, {"screen", selection}, {"final", audio.snapshot()}};
    } catch (...) { SDL_QuitSubSystem(SDL_INIT_AUDIO); throw; }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return {{"status", "pass"}, {"checks", checks}, {"observed", observed},
            {"scope", "source routing and SDL dummy mixed PCM; no GUI, output device routing, listening or native timing parity claim"}};
}
} // namespace dnf

#ifdef DNF_AUDIO_TEST_STANDALONE
#include "dnf/entry.hpp"
int audioTestRun(int argc, char **argv) {
    try {
        auto root = std::filesystem::u8path(argc > 1 ? argv[1] : "../DNF1031客户端");
        dnf::ContentProfile profile;
        profile.pvfPath = root / "Script.pvf"; profile.resourceRoots = {root};
        const auto identity = profile.fingerprint();
        dnf::Pvf pvf(root / "Script.pvf",identity.pvfSha256);
        dnf::Assets assets(std::vector<std::filesystem::path>{root}, pvf, identity.manifest);
        auto result = dnf::runAudioTests(pvf, assets);
        result["content_identity"] = identity.json();
        if (argc > 2) dnf::writeJson(std::filesystem::u8path(argv[2]), result);
        std::cout << "Audio checks " << result["checks"].size() << " pass (SDL dummy; not listening verification)\n";
        return 0;
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
DNF_ENTRY(audioTestRun)
#endif
