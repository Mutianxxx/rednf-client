#pragma once
#include "dnf/map_exploration.hpp"

namespace dnf {
// Identity is the source town/area pair, never a hardcoded city alias. SourceRef
// covers the complete TWN and resolved MAP; paths and IDs are validated together.
struct TownLocation {
    int townId = -1, areaId = -1;
    std::string townPath, mapPath;
    SourceRef townSource, mapSource;
    Json preserved = Json::object();
    Json json() const;
};
struct TownAccessArea {
    size_t index = 0, registrationOrdinal = 0, areaOrdinal = 0;
    int townId = -1, areaId = -1;
    std::string townPath, townName, mapLiteral, mapPath, kind;
    bool readable = false, valid = false;
    std::optional<std::array<double, 2>> authoredSpawn;
    std::optional<int> worldmapId, worldmapArea;
    std::string worldmapPath;
    SourceRef registrationSource, townSource, areaSource, mapSource;
    Json registration = Json::array(), raw = Json::array(), diagnostics = Json::array();
    Json json() const;
};
struct TownRestoreState {
    std::optional<TownLocation> current, returnAnchor;
    Json migrations = Json::array();
};
struct TownNavigation {
    enum class Kind { Area, DungeonGate, Unavailable };
    Kind kind = Kind::Unavailable;
    std::optional<size_t> destination;
    std::optional<int> worldmapId, worldmapArea;
    std::string worldmapPath;
    Json diagnostics = Json::array();
    Json json() const;
};
class TownAccessCatalog {
    Pvf &pvf_;
    std::vector<TownAccessArea> areas_;
    Json documents_ = Json::array(), diagnostics_ = Json::array();
  public:
    explicit TownAccessCatalog(Pvf &);
    size_t size() const { return areas_.size(); }
    const TownAccessArea &at(size_t index) const { return areas_.at(index); }
    std::vector<size_t> find(int townId, int areaId) const;
    size_t require(int townId, int areaId) const;
    TownLocation location(size_t index) const;
    TownLocation validateLocation(const Json &) const;
    TownRestoreState restoreState(const Json &regionSession) const;
    void attachState(Json &regionSession, const std::optional<TownLocation> &current,
        const std::optional<TownLocation> &returnAnchor) const;
    MapAccessPage page(const std::string &search = "", size_t offset = 0, size_t limit = 9) const;
    bool admitted(size_t index) const;
    TownNavigation navigate(const TownLocation &current, const TownExit &) const;
    Json json() const;
};
struct PreparedTownArea {
    bool ok = false;
    TownLocation location;
    Scene scene;
    std::array<double, 2> spawn{0, 0};
    Json diagnostics = Json::array(), records = Json::array();
    Json json() const;
};
// Preparation uses private World geometry and never mutates live scene, actors,
// location, RNG or saves. Missing movement geometry refuses publication.
PreparedTownArea prepareTownArea(Pvf &, Assets &, World &, const RegionCatalog &,
    const TownAccessCatalog &, size_t index, const std::optional<TownLocation> &from = {});
std::string townRuntimeLocation(const TownLocation &);
Json runTownAccessTests(Pvf &, Assets &);
} // namespace dnf
