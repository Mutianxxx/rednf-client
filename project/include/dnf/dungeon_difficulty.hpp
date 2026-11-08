#pragma once
#include "resources.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
// Four-tier beta adapter: tier order across these two authored naming families
// is inferred. Exact names used by historic saves/test commands stay exact.
inline constexpr int dungeonDifficultyCount = 4;
inline constexpr const char *dungeonDifficultyPolicy = "inferred-source-family-tier-v1";
inline const char *dungeonDifficultyName(int tier) {
    static constexpr const char *names[]{"普通级","冒险级","勇士级","王者级"};
    if(tier<0||tier>=dungeonDifficultyCount)throw std::invalid_argument("Unsupported dungeon difficulty tier");
    return names[tier];
}
inline std::string dungeonDifficultyRequest(int tier) {
    static constexpr const char *names[]{"dungeon_normal","dungeon_expert","dungeon_master","dungeon_king"};
    if(tier<0||tier>=dungeonDifficultyCount)throw std::invalid_argument("Unsupported dungeon difficulty tier");
    return names[tier];
}
struct DungeonDifficultyResolution {
    std::string requested, selected, family="exact-source-name";
    Json evidence=Json::array();
    Json json() const {return {{"requested",requested},{"selected",selected},{"family",family},
        {"classification",family=="exact-source-name"?"source-literal":"inferred-beta-tier-adapter"},
        {"policy",family=="exact-source-name"?"exact-source-name":dungeonDifficultyPolicy},{"source_fields",evidence}};}
};
inline DungeonDifficultyResolution resolveDungeonDifficulty(const Script &mob,const std::string &request) {
    DungeonDifficultyResolution out;out.requested=out.selected=normalize(request);
    if(out.requested.rfind("dungeon_",0)!=0)return out;
    int tier=-1;for(int i=0;i<dungeonDifficultyCount;++i)if(out.requested==dungeonDifficultyRequest(i))tier=i;
    if(tier<0)throw std::invalid_argument("Unsupported dungeon difficulty policy request");
    std::set<std::string> tags;bool in=false;int blocks=0;bool closed=false;
    for(const auto &f:mob.fields) {
        const auto tag=normalize(f.tag);
        if(tag=="[ai pattern]"){if(++blocks!=1||!f.values.empty())throw std::invalid_argument("Ambiguous MOB AI difficulty block");in=true;continue;}
        if(tag=="[/ai pattern]"){if(!in||!f.values.empty())throw std::invalid_argument("Malformed MOB AI difficulty closing block");in=false;closed=true;continue;}
        if(in&&tag.rfind("[/",0)!=0){tags.insert(tag);out.evidence.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});}
    }
    if(blocks!=1||in||!closed)throw std::invalid_argument("Missing complete MOB AI difficulty block");
    const bool old=tags.count("[easy]")!=0,modern=tags.count("[normal]")!=0;
    if(old==modern)throw std::invalid_argument("MOB AI difficulty family is absent or ambiguous; no fallback");
    static constexpr const char *oldNames[]{"easy","medium","hard","ultimate"};
    static constexpr const char *newNames[]{"normal","expert","master","king"};
    out.family=old?"easy-medium-hard-ultimate":"normal-expert-master-king";
    out.selected=old?oldNames[tier]:newNames[tier];
    if(!tags.count("["+out.selected+"]"))throw std::invalid_argument("Selected MOB AI tier is absent; no fallback");
    return out;
}
} // namespace dnf
