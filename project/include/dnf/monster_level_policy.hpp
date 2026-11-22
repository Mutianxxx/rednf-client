#pragma once
#include "resources.hpp"
#include <stdexcept>

namespace dnf {
// Source spawn levels remain immutable. This separate policy is the user's
// beta request, frozen once per dungeon, never a claimed native level rule.
class MonsterLevelPolicy {
    std::string id_ = "source-map-v1";
    int frozen_ = 0;
    Json preserved_ = Json::object();
  public:
    static MonsterLevelPolicy playerLevel(int level) {
        if(level<1 || level>99)throw std::invalid_argument("Player-adapted monster level must be 1..99");
        MonsterLevelPolicy out;out.id_="user-player-level-v1";out.frozen_=level;return out;
    }
    bool adapted() const { return id_=="user-player-level-v1"; }
    int frozenLevel() const { return frozen_; }
    Json json() const {
        Json out=preserved_;out["id"]=id_;
        out["classification"]=adapted()?"user_requested_beta_tuning":"source_map_level";
        out["frozen_player_level"]=adapted()?Json(frozen_):Json();
        return out;
    }
    static MonsterLevelPolicy fromJson(const Json &value) {
        if(value.is_null())return {};
        if(!value.is_object() || !value.contains("id") || !value.at("id").is_string())
            throw std::invalid_argument("Invalid saved monster level policy");
        MonsterLevelPolicy out;const auto id=value.at("id").get<std::string>();
        if(id=="user-player-level-v1") {
            const auto &level=value.at("frozen_player_level");
            if(!level.is_number_integer() || level<1 || level>99)
                throw std::invalid_argument("Invalid frozen player level");
            out=playerLevel(level.get<int>());
        } else if(id!="source-map-v1")throw std::invalid_argument("Unknown saved monster level policy: "+id);
        else if(value.contains("frozen_player_level") && !value.at("frozen_player_level").is_null())
            throw std::invalid_argument("Source MAP policy cannot contain a player level override");
        out.preserved_=value;return out;
    }
};
} // namespace dnf
