#pragma once
#include "character.hpp"
#include "content_profile.hpp"
#include <deque>
#include <map>
#include <set>

namespace dnf {
class RegionCatalog;
// These states describe an actual consumer, never the existence of its inputs.
enum class CapabilityState { Supported = 0, Inferred = 1, Blocked = 2 };
enum class DependencyUse { Required, OptionalPresentation, Preload, Metadata };
const char *capabilityStateName(CapabilityState value);
const char *dependencyUseName(DependencyUse value);

struct CapabilityNode {
    std::string key;
    CapabilityState state = CapabilityState::Blocked;
    std::string reason = "No executable semantic consumer has been registered";
    SourceRef source;
    Json evidence = Json::array();
};
struct DependencyEdge {
    std::string from, to, kind;
    DependencyUse use = DependencyUse::Required;
    SourceRef source;
    // Empty means unconditional. An absent context key remains unresolved,
    // which blocks required behavior instead of dropping an unknown branch.
    std::string condition, compilerCapability;
    Json json() const;
};
struct CapabilityContext {
    std::string mode;
    std::map<std::string, bool> conditions;
};
struct CapabilityReport {
    std::string target, mode;
    CapabilityState state = CapabilityState::Blocked;
    Json causes = Json::array(), warnings = Json::array();
    bool playable() const { return state != CapabilityState::Blocked; }
    Json json() const;
};
// Monotone propagation computes the fixed point, so legal cycles do not fail
// merely because they are cycles. Required edges alone affect eligibility.
// Execution/recursive-spawn budgets belong to the executor, not this graph.
class CapabilityGraph {
    std::map<std::string, CapabilityNode> nodes_;
    std::vector<DependencyEdge> edges_;
  public:
    void define(CapabilityNode node);
    void depend(DependencyEdge edge);
    const auto &nodes() const { return nodes_; }
    const auto &edges() const { return edges_; }
    CapabilityReport evaluate(const std::string &target, const CapabilityContext &context = {}) const;
    Json snapshot() const;
};

struct SemanticAdapter {
    std::string id, version, format, contentIdentity;
    std::string behavior, sourceSelection, invalidation;
    CapabilityState state = CapabilityState::Blocked;
    int priority = 0;
    Json evidence = Json::array(), limitations = Json::array();
    Json json() const;
};
struct AdapterResolution {
    const SemanticAdapter *adapter = nullptr;
    std::string reason;
    std::vector<std::string> candidates;
    Json json() const;
};
class SemanticAdapterRegistry {
    // Registry additions preserve previously resolved adapter addresses.
    std::deque<SemanticAdapter> adapters_;
  public:
    void add(SemanticAdapter adapter);
    // Exact matching only. Empty identity explicitly means format-wide;
    // specificity never silently overrides an equal explicit priority.
    AdapterResolution resolve(const std::string &format, const std::string &identity) const;
    Json snapshot() const;
};

struct CatalogDocument {
    SourceRef source;
    Bytes bytes;
    Script script;
    bool token5 = false;
    Json diagnostics = Json::array();
    Json json(bool includeBytes = false) const;
};
struct CatalogMember {
    std::string path, format;
};
struct CatalogRegistry {
    std::string kind;
    SourceRef source;
    CharacterList list;
    Json json(bool includeSource = false) const;
};
// Full archive membership is cheap to enumerate. Only registration documents
// are decoded here; referenced definitions/ANI/IMG stay lazy. All raw members
// remain readable even when their format/behavior is unknown or deferred.
class ContentCatalog {
    Pvf &pvf_;
    std::vector<CatalogMember> members_;
    std::map<std::string, CatalogRegistry> registries_;
    Json diagnostics_ = Json::array();
    void addRegistry(const std::string &path, const std::string &kind, const std::string &base);
  public:
    explicit ContentCatalog(Pvf &pvf);
    const auto &members() const { return members_; }
    const auto &registries() const { return registries_; }
    const Json &diagnostics() const { return diagnostics_; }
    const CatalogMember *member(const std::string &path) const;
    CatalogDocument loadDocument(const std::string &path) const;
    // A unique registry row is required; duplicates are retained and rejected.
    const CharacterRegistration *registration(const std::string &registry, int id) const;
    Json snapshot(bool includeMembers = false, bool includeSource = false) const;
};
// Audits the actual RegionCatalog's loaded definitions for the full beta gate.
// It does not toggle the historical demo's enabled flag or imply that unloaded
// world regions were inspected. Target keys are "beta.dungeon:<registration>"
// and "beta.world" (which additionally requires complete registered coverage).
CapabilityGraph buildRegionCapabilityGraph(Pvf &pvf, const RegionCatalog &region);
Json runContentCatalogTests(Pvf &pvf, Assets &assets);
} // namespace dnf
