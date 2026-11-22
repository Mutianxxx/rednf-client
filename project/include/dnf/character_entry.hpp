#pragma once
#include "dnf/town_access.hpp"
#include <map>
#include <set>

namespace dnf {
struct CharacterTownEntry {
    PreparedTownArea town;
    std::optional<int> hp,mp,direction;
    bool revive=false;
    Json report=Json::object();
};
// Application login policy is deliberately separate from lossless simulation
// restoration. It never prepares or awards the saved dungeon.
class CharacterEntryService {
    Pvf &pvf_; Assets &assets_; const RegionCatalog &regions_; const TownAccessCatalog &towns_;
    bool indexed_=false;
    std::set<size_t> rooms_;
    std::map<size_t,std::vector<size_t>> edges_;
    Json evidence_=Json::array();
    void index();
  public:
    CharacterEntryService(Pvf &p,Assets &a,const RegionCatalog &r,const TownAccessCatalog &t)
        :pvf_(p),assets_(a),regions_(r),towns_(t) {}
    // Missing source rooms use the previously established home. Only legacy
    // snapshots without one migrate explicitly to the original creation room.
    TownLocation roomFor(const TownLocation &,const std::optional<TownLocation> &previous={},Json *trace=nullptr);
    CharacterTownEntry prepare(World &,const Json &savedSession);
};
// Used by main's actual town publisher and login regression. No save, reward,
// RNG draw, progression edit or source-resource work occurs here.
void publishCharacterEntry(World &,Scene &,CharacterTownEntry &&);
Json runCharacterEntryTests(Pvf &,Assets &);
} // namespace dnf
