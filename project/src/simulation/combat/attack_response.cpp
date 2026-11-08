#include "dnf/combat.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
Json dungeonValues(const Script &script, const std::string &wanted) {
    // Preserve the ordered fields; a PvP override must never supply PvE data.
    bool dungeon = false, other = false;
    Json common = Json::array();
    for (const auto &field : script.fields) {
        const auto tag = normalize(field.tag);
        if (tag == "[dungeon]") { dungeon = true; other = false; continue; }
        if (tag == "[/dungeon]") { dungeon = false; continue; }
        if (tag == "[pvp]" || tag == "[warroom]" || tag == "[death tower]") { other = true; continue; }
        if (tag == "[/pvp]" || tag == "[/warroom]" || tag == "[/death tower]") { other = false; continue; }
        if (tag != normalize(wanted) || other) continue;
        if (dungeon) return field.values;
        if (common.empty()) common = field.values;
    }
    return common;
}
double dungeonNumber(const Script &script, const std::string &tag, double fallback = 0) {
    auto values = dungeonValues(script, tag);
    if(values.empty())return fallback;
    if(values.size()!=1||!values[0].is_number()||!std::isfinite(values[0].get<double>()))
        throw std::invalid_argument("Invalid AttackInfo response number " + tag + ": " + script.path);
    return values[0].get<double>();
}
Json orderedHitInfo(const Script &script) {
    // In this PVF cut/blow/blood may themselves be type-5 tokens. Field.values
    // truncates there, so the fixed hit-info tuple must use the ordered tokens.
    Json common = Json::array();
    bool dungeon = false, other = false;
    for (size_t i = 0; i < script.tokens.size(); ++i) {
        const auto &value = script.tokens[i]["value"];
        if (!value.is_string()) continue;
        const auto tag = normalize(value.get<std::string>());
        if (tag == "[dungeon]") { dungeon = true; other = false; continue; }
        if (tag == "[/dungeon]") { dungeon = false; continue; }
        if (tag == "[pvp]" || tag == "[warroom]" || tag == "[death tower]") { other = true; continue; }
        if (tag == "[/pvp]" || tag == "[/warroom]" || tag == "[/death tower]") { other = false; continue; }
        if (tag != "[hit info]" || other) continue;
        if(i + 4 >= script.tokens.size())
            throw std::invalid_argument("Truncated AttackInfo hit info: " + script.path);
        Json tuple = Json::array();
        for (size_t n = 1; n <= 4; ++n) tuple.push_back(script.tokens[i+n]["value"]);
        if (!tuple[0].is_string() || !tuple[1].is_string() ||
            !tuple[2].is_number() || !tuple[3].is_number())
            throw std::invalid_argument("Malformed AttackInfo hit info: " + script.path);
        for (size_t n = 5; n <= 6 && i+n < script.tokens.size(); ++n) {
            if (!script.tokens[i+n]["value"].is_number()) break;
            tuple.push_back(script.tokens[i+n]["value"]);
        }
        if (dungeon) return tuple;
        if (common.empty()) common = tuple;
    }
    return common;
}
std::string dungeonOperand(const Script &script, const std::string &wanted) {
    std::string common;
    bool dungeon=false, other=false;
    for(size_t i=0;i<script.tokens.size();++i) {
        const auto &value=script.tokens[i]["value"];
        if(!value.is_string())continue;
        const auto tag=normalize(value.get<std::string>());
        if(tag=="[dungeon]"){dungeon=true;other=false;continue;}
        if(tag=="[/dungeon]"){dungeon=false;continue;}
        if(tag=="[pvp]"||tag=="[warroom]"||tag=="[death tower]"){other=true;continue;}
        if(tag=="[/pvp]"||tag=="[/warroom]"||tag=="[/death tower]"){other=false;continue;}
        if(other||tag!=wanted||i+1>=script.tokens.size())continue;
        const auto &operand=script.tokens[i+1]["value"];
        if(!operand.is_string())throw std::invalid_argument("Invalid AttackInfo operand "+wanted+": "+script.path);
        const auto text=normalize(operand.get<std::string>());
        if(dungeon)return text;
        if(common.empty())common=text;
    }
    return common;
}
} // namespace
AttackResponse readAttackResponse(const Script &script) {
    AttackResponse out;
    out.source=script.path;
    out.attackType=dungeonOperand(script,"[attack type]");
    out.element=dungeonOperand(script,"[elemental property]");
    out.attackDirection=dungeonOperand(script,"[attack direction]");
    out.push=dungeonNumber(script,"[push aside]");
    out.lift=dungeonNumber(script,"[lift up]");
    const auto sound=dungeonValues(script,"[hit wav]");
    if(!sound.empty()) {
        if(sound.size()!=1||!sound[0].is_string())
            throw std::invalid_argument("Invalid AttackInfo hit sound: "+script.path);
        out.sound=sound[0].get<std::string>();
    }
    out.hitInfo=orderedHitInfo(script);
    if(!out.hitInfo.empty()) {
        const double pause=out.hitInfo[2].get<double>(),delay=out.hitInfo[3].get<double>();
        if(!std::isfinite(pause)||!std::isfinite(delay))
            throw std::invalid_argument("Nonfinite AttackInfo hit timing: "+script.path);
        if(pause>=0)out.hitPause=pause;
        if(delay>=0)out.hitDelayRate=delay;
    }
    for(const auto *tag:{"[hit effect]","[hit effect animation]"}) {
        const auto values=dungeonValues(script,tag);
        if(values.empty())continue;
        if(values.size()==1&&values[0].is_string())out.hitEffect=normalize(values[0].get<std::string>());
        break;
    }
    // Reaction operands are themselves tag tokens in current binary PVF.
    // Select the dungeon reaction as one value: [none] must override a common
    // [down] rather than leaving both flags active. Other mode scopes cannot
    // affect this PvE response.
    bool dungeon=false,other=false;
    std::string commonReaction,dungeonReaction;
    for(size_t i=0;i<script.tokens.size();++i) {
        const auto &value=script.tokens[i]["value"];
        if(!value.is_string())continue;
        const auto tag=normalize(value.get<std::string>());
        if(tag=="[dungeon]"){dungeon=true;other=false;continue;}
        if(tag=="[/dungeon]"){dungeon=false;continue;}
        if(tag=="[pvp]"||tag=="[warroom]"||tag=="[death tower]"){other=true;continue;}
        if(tag=="[/pvp]"||tag=="[/warroom]"||tag=="[/death tower]"){other=false;continue;}
        if(other)continue;
        if(tag=="[damage reaction]" && i+1<script.tokens.size() && script.tokens[i+1]["value"].is_string()) {
            auto &selected=dungeon?dungeonReaction:commonReaction;
            if(selected.empty())selected=normalize(script.tokens[i+1]["value"].get<std::string>());
        }
    }
    const auto &reaction=dungeonReaction.empty()?commonReaction:dungeonReaction;
    out.knockDown=reaction=="[down]";
    out.noReaction=reaction=="[none]";
    out.reactionIndex=out.knockDown?1:0;
    return out;
}
AttackResponse World::characterAttackResponse(const Script &attack) const {
    auto out=readAttackResponse(attack);
    // 40JP 4AF8E0: category=4, pause=-1 and rate=-1.0 inherit separately.
    // 4B1870/4B1910/4B2530 return no category and zero timings without an
    // equipped weapon. Never invent a bare-hand row from the CHR table length.
    int subtype=-1;
    if(combatAttributes_) {
        for(const auto &equipped:combatAttributes_->equipmentSources)
            if(normalize(equipped.equippedSlot)=="[weapon]") {
                const auto values=equipped.source.values("[sub type]");
                if(values.size()==1&&values[0].is_number_integer()) {
                    const auto value=values[0].get<int64_t>();
                    if(value>=0&&value<=INT32_MAX)subtype=int(value);
                }
            }
    } else if(identity_.jobId==0) {
        // Preserve the explicitly selected legacy diagnostic sword equipment.
        subtype=legacyWeaponSubtype(weapon);
    }
    Json inherited=Json::array({"[none]","[no blood]",0,0.0});
    const auto table=characterSource().source.script.values("[weapon hit info]");
    const size_t base=subtype<0?table.size():size_t(subtype)*6;
    if(subtype>=0&&table.size()%6==0&&base<table.size()&&table.size()-base>=6) {
        Json row=Json::array();
        for(size_t i=0;i<6;++i)row.push_back(table[base+i]);
        if(row[0].is_string()&&row[1].is_string()&&row[2].is_number()&&row[3].is_number()&&
           std::isfinite(row[2].get<double>())&&std::isfinite(row[3].get<double>()))inherited=std::move(row);
    }
    const auto raw=out.hitInfo;
    out.hitInfo=raw.empty()?inherited:raw;
    if(!raw.empty()) {
        const auto category=normalize(raw[0].get<std::string>());
        if(category!="[blow]"&&category!="[cut]"&&category!="[burn]"&&category!="[etc]") {
            out.hitInfo[0]=inherited[0];out.hitInfo[1]=inherited[1];
        }
        if(raw[2].get<double>()==-1)out.hitInfo[2]=inherited[2];
        if(raw[3].get<double>()==-1)out.hitInfo[3]=inherited[3];
    }
    out.hitPause=std::max(0.0,out.hitInfo[2].get<double>());
    out.hitDelayRate=std::max(0.0,out.hitInfo[3].get<double>());
    return out;
}
} // namespace dnf
