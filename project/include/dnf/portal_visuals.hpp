#pragma once
#include "resources.hpp"
#include "content_profile.hpp"
#include "region.hpp"
#include <tuple>

namespace dnf {
struct PortalObjectSource {
    bool available = false, boss = false;
    int objectId = -1, direction = -1;
    size_t slot = 0;
    std::string object, diagnostic;
    std::string classification = "inferred-1031-dgn-pathgate-ten-slot-v1";
    SourceRef dungeonSource, registrySource, objectSource;
    Json inputIds = Json::array(), registryMatches = Json::array();
    Json snapshot() const;
};
// Current 1031 ten-slot adapter: L normal/boss/wall, R normal/boss/wall,
// U normal/boss, D normal/boss. Unknown shapes and unresolved registrations
// return a diagnostic; callers must not replace them with a Lorien filename.
PortalObjectSource resolveDungeonPortalSource(Pvf &, const std::vector<int> &,
                                              Direction, bool boss);
PortalObjectSource resolveDungeonPortalSource(Pvf &, const DungeonDefinition &,
                                              Direction, bool boss);
// The source owner/model is immutable for a content identity and DGN id/path.
// Both unavailable and available results are cached; no per-frame registry scan.
class DungeonPortalSourceCache {
    using Key = std::tuple<std::string,int,std::string,int,bool>;
    std::map<Key,PortalObjectSource> sources_;
    uint64_t hits_ = 0;
  public:
    const PortalObjectSource &resolve(Pvf &,const DungeonDefinition &,Direction,bool boss);
    size_t size() const { return sources_.size(); }
    Json snapshot() const;
};
struct PortalVisualTrack {
    size_t ordinal = 0;
    int state = 0, imageVariant = 0;
    std::string animation;
};
struct PortalTileBinding {
    size_t ordinal = 0;
    std::string path;
    std::array<int,2> sourcePair{};
};
struct PortalVisualPlan {
    Script source;
    bool open = false;
    std::vector<PortalVisualTrack> tracks;
    std::vector<PortalTileBinding> tiles;
    std::string classification = "inferred-1031-pathgate-state-pairs-v1";
    Json snapshot() const;
};
// In the supported 1031 pathgate source, ANI string i has (state,variant)
// at int[2*i]. State 0 is common, 1 closed, 2 open. This interpretation is
// inferred from actual source lists/names; native controller parity is pending.
// TIL pairs remain opaque: they do not share the ANI state semantics.
PortalVisualPlan portalVisuals(Pvf &,const std::string &object,bool open);
std::string portalImageVariant(std::string image,int variant);
// Current binary global node 0 is the source LOOP flag. Absence uses the
// explicit nonloop beta default; never infer looping from filenames/state.
bool portalAnimationLoops(const Animation &);
struct PortalPlaybackTime {int64_t commonMs=0,stateMs=0;bool reset=false,changed=false;};
class PortalPlaybackClock {
    struct State {std::string object;bool open=false;int64_t commonStart=0,stateStart=0,last=0;};
    std::string scene_;
    std::map<std::string,State> instances_;
  public:
    PortalPlaybackTime sample(const std::string &scene,const std::string &instance,
        const std::string &object,int64_t simulationMs,bool open);
    void clear() noexcept {scene_.clear();instances_.clear();}
    Json snapshot() const;
};
Json runPortalStateTests(Pvf &,Assets &);
Json runPortalVisualTests(Pvf &,Assets &);
} // namespace dnf
