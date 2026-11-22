#pragma once
#include "content_profile.hpp"
#include <map>
#include <optional>

namespace dnf {
// One entry per original map.lst registration, including duplicates. A MAP
// found only by PVF enumeration receives a path identity and no fabricated ID.
struct MapAccessEntry {
    size_t index = 0;
    std::optional<int> id;
    std::string key, path, name, type;
    int dungeonId = -1, minimumLevel = 1, basisLevel = 1;
    double backgroundOrigin = 0;
    bool registered = false, readable = false, special = false;
    bool minimumLevelKnown = false, basisLevelKnown = false, backgroundOriginKnown = false;
    bool complete = false; // Directory/readability never grants gameplay capability.
    SourceRef source, registrationSource;
    Json registration = Json::array(), sourceFields = Json::array();
    Json dungeonSources = Json::array(), diagnostics = Json::array();
    Json json() const;
};
struct MapNameIndexProgress {
    size_t indexed = 0, total = 0, next = 0, lastStepEntries = 0;
    uint64_t lastStepMicroseconds = 0, budgetMicroseconds = 0;
    bool complete = false, budgetExceeded = false;
    Json json() const;
};
struct MapAccessPage {
    size_t total = 0, offset = 0;
    std::vector<MapAccessEntry> entries;
    Json diagnostics = Json::array();
    bool complete = false;
    // This describes search coverage, independently from gameplay complete.
    bool matchesComplete = true;
    std::optional<MapNameIndexProgress> nameIndex;
    std::vector<size_t> pendingMetadata;
    Json json() const;
};
struct MapAdmissionResult {
    bool allowed = false, testMode = false, complete = false;
    Json diagnostics = Json::array();
    Json json() const;
};
class MapAccessCatalog {
    Pvf &pvf_;
    mutable std::vector<MapAccessEntry> entries_;
    mutable std::vector<bool> loaded_;
    mutable size_t loadedCount_ = 0, nameIndexNext_ = 0;
    mutable MapNameIndexProgress lastNameStep_;
    std::map<int, std::vector<size_t>> byId_;
    std::map<std::string, std::vector<size_t>> byPath_;
    std::map<int, std::vector<std::string>> dungeonPaths_;
    Json diagnostics_ = Json::array();
    void load(size_t index) const;
  public:
    // Cheap complete registration/member enumeration; metadata is loaded on
    // demand. Name search must inspect all MAP metadata; an empty page query
    // reads only its visible page. No RegionCatalog/region whitelist dependency.
    explicit MapAccessCatalog(Pvf &);
    size_t size() const { return entries_.size(); }
    const MapAccessEntry &at(size_t index) const;
    std::vector<size_t> findById(int id) const;
    std::vector<size_t> findByPath(const std::string &path) const;
    // id:123 and path:foo search the index without decoding unrelated MAPs.
    // name:foo (or general text) also searches source/display names.
    MapAccessPage page(const std::string &search = "", size_t offset = 0, size_t limit = 24) const;
    // Single-writer work on the owning/UI thread. At most maxEntries MAP
    // records are decoded; the 1..4000us deadline is checked BETWEEN records.
    // One source decode is atomic and can overrun, which progress reports.
    // maxEntries==0 or budgetMicroseconds==0 performs no source work.
    MapNameIndexProgress stepNameIndex(size_t maxEntries = 2, uint64_t budgetMicroseconds = 2000) const;
    MapNameIndexProgress nameIndexProgress() const;
    // Zero PVF reads. Name matches use loaded metadata only, with a lower-bound
    // total until matchesComplete. ID/path results can contain indexed skeletons;
    // pendingMetadata identifies those rows. Select via at() before admission.
    MapAccessPage partialPage(const std::string &search = "", size_t offset = 0, size_t limit = 24) const;
    MapAdmissionResult admission(size_t index, int characterLevel, bool testMode,
                                 bool taskConditionsMet = true) const;
    const Json &diagnostics() const { return diagnostics_; }
    Json indexSnapshot() const; // Registration/member coverage; no lazy MAP reads.
};
Json runMapAccessTests(Pvf &);
} // namespace dnf
