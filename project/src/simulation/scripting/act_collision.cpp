#include "dnf/act_collision.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
ActCollisionAttack readActCollisionAttack(const Script &source) {
    ActCollisionAttack out;out.original=source;out.damage=readAttackDamage(source,AttackStatusConsumer::StunHostV1);
    const auto statuses=readAttackStatuses(source);out.sourceReady=out.damage.usable()&&statuses.usable();
    bool pvp=false;std::set<size_t> enums,delegatedOffsets;std::set<std::string> seen;bool supported=true;
    // Status parsing owns exact source spans, including separate type-5 enums.
    for(const auto &entry:statuses.entries)if(entry.runtime)for(const auto &ref:entry.sources)delegatedOffsets.insert(ref.byteOffset);
    for(size_t i=0;i<source.tokens.size();++i) {
        const auto &token=source.tokens[i];
        if(token.at("value")=="[hit info]")for(size_t j=0;j<=4&&i+j<source.tokens.size();++j)
            delegatedOffsets.insert(source.tokens[i+j].at("offset").get<size_t>());
    }
    const auto missing=[&](const std::string &kind,size_t i) {
        supported=false;out.diagnostics.push_back({{"kind",kind},{"tag",source.fields.at(i).tag},
            {"offset",source.fields.at(i).offset},{"values",source.fields.at(i).values},{"path",source.path}});
    };
    for(size_t i=0;i<source.fields.size();++i) {
        const auto &f=source.fields[i];const auto tag=normalize(f.tag);
        if(tag=="[pvp]"){pvp=true;continue;}if(tag=="[/pvp]"){pvp=false;continue;}if(pvp||enums.count(i))continue;
        const auto scalar=[&](double &result) {
            if(!seen.insert(tag).second||f.values.size()!=1||!f.values[0].is_number()||!std::isfinite(f.values[0].get<double>())) {
                missing("act_attack_reaction_operand",i);return false;
            }
            result=f.values[0].get<double>();return true;
        };
        if(tag=="[damage reaction]") {
            if(!seen.insert(tag).second){missing("act_attack_reaction_repeated",i);continue;}
            if(f.values.size()==1&&f.values[0].is_string())out.reaction=normalize(f.values[0].get<std::string>());
            else if(f.values.empty()&&i+1<source.fields.size()&&source.fields[i+1].values.empty()) {
                out.reaction=normalize(source.fields[i+1].tag);enums.insert(i+1);
            }else missing("act_attack_reaction_enum",i);
            if(out.reaction!="[damage]"&&out.reaction!="[none]")missing("act_player_down_or_custom_reaction_consumer_missing",i);
        } else if(tag=="[push aside]") {
            if(scalar(out.push)&&out.push!=0)missing("act_player_source_push_consumer_missing",i);
        } else if(tag=="[lift up]") {
            if(scalar(out.lift)&&out.lift!=0)missing("act_player_source_lift_consumer_missing",i);
        } else if(tag=="[knuck back]"||tag=="[bounce]") {
            double value=0;if(scalar(value)&&value!=0)missing("act_player_knockback_or_bounce_consumer_missing",i);
        } else if(tag=="[attack enemy]") {
            double value=0;if(scalar(value)&&(value==0||value==1))out.enemy=value==1;
            else missing("act_attack_enemy_filter_operand",i);
        } else if(tag=="[attack our team]"||tag=="[attack friendly]"||tag=="[ignore super armor]"||tag=="[ignore weight]") {
            double value=0;if(scalar(value)&&value!=0)missing("act_attack_target_or_protection_consumer_missing",i);
        } else if(tag=="[hit wav]") {
            if(!seen.insert(tag).second||f.values.size()!=1||!f.values[0].is_string())missing("act_attack_hit_sound_operand",i);
            else out.sound=f.values[0].get<std::string>();
        } else if(tag=="[max target hit number]") {
            double value=0;if(scalar(value)&&(value<=0||std::floor(value)!=value))missing("act_attack_target_limit_operand_or_zero_semantics",i);
            // This first host attacks one hostile Character only. A positive
            // target limit cannot exclude its first and sole hostile target.
        } else if(tag=="[attack type]"||tag=="[elemental property]"||tag=="[attack direction]") {
            std::string value;
            if(f.values.size()==1&&f.values[0].is_string())value=normalize(f.values[0].get<std::string>());
            else if(f.values.empty()&&i+1<source.fields.size()&&source.fields[i+1].values.empty()) {
                value=normalize(source.fields[i+1].tag);enums.insert(i+1);
            }
            if(tag=="[attack direction]"&&value!="[hit horizon]"&&value!="[horizontal]")
                missing("act_player_attack_direction_consumer_missing",i);
        } else if(tag=="[hit effect]"||tag=="[hit effect animation]"||tag=="[damage except human]") {
            missing("act_attack_visual_or_target_binding_missing",i);
        } else {
            static const std::set<std::string> damageOwned={"[damage]","[absolute damage]","[damage bonus]","[critical hit]","[stuck]",
                "[weapon damage apply]","[ignore defense]","[human damage rate]","[fort damage rate]","[monster damage rate]",
                "[hp drain]","[mp drain]","[weakness]","[stuck prob increase]"};
            if(!damageOwned.count(tag)&&!delegatedOffsets.count(f.offset))missing("act_attack_unregistered_behavior_field",i);
        }
    }
    // Fixed ordered tuple: type5 cut/blow and blood are operands, not fields.
    pvp=false;bool found=false;
    for(size_t i=0;i<source.tokens.size();++i) {
        const auto &v=source.tokens[i].at("value");if(!v.is_string())continue;const auto tag=normalize(v.get<std::string>());
        if(tag=="[pvp]"){pvp=true;continue;}if(tag=="[/pvp]"){pvp=false;continue;}
        if(pvp||tag!="[hit info]")continue;
        if(found||i+4>=source.tokens.size()){supported=false;out.diagnostics.push_back({{"kind","act_attack_hit_info_shape"}});continue;}
        found=true;
        for(size_t j=1;j<=4;++j)out.hitInfo.push_back(source.tokens[i+j].at("value"));
        if(!out.hitInfo[0].is_string()||!out.hitInfo[1].is_string()||!out.hitInfo[2].is_number()||!out.hitInfo[3].is_number()) {
            supported=false;out.diagnostics.push_back({{"kind","act_attack_hit_info_types"}});continue;
        }
        out.pauseMs=out.hitInfo[2].get<double>();out.delayRate=out.hitInfo[3].get<double>();
        if(!std::isfinite(out.pauseMs)||out.pauseMs<0||out.pauseMs>500||!std::isfinite(out.delayRate)||out.delayRate<0||out.delayRate>240) {
            supported=false;out.diagnostics.push_back({{"kind","act_attack_hit_pause_or_inheritance_consumer_missing"}});
        }
        out.diagnostics.push_back({{"kind","act_hit_visual_binding_incomplete"},{"blocking",false},
            {"policy","existing-hit-flash-and-source-sound; type/blood animation caller remains unverified"},{"hit_info",out.hitInfo}});
    }
    out.reactionReady=out.sourceReady&&supported;
    return out;
}
std::vector<size_t> actCollisionFrames(const Animation &animation,uint64_t beforeUs,uint64_t afterUs,bool first,size_t maximum) {
    if(afterUs<beforeUs||animation.frames.empty()||!maximum)throw std::invalid_argument("Invalid ACT collision animation interval");
    std::vector<size_t> out;uint64_t start=0;
    for(size_t i=0;i<animation.frames.size();++i) {
        if(animation.frames[i].duration<0)throw std::invalid_argument("Negative ACT collision ANI duration");
        if((first&&start==0)||(start>beforeUs&&start<=afterUs))out.push_back(i);
        const auto duration=uint64_t(animation.frames[i].duration)*1000;
        if(start>UINT64_MAX-duration)throw std::overflow_error("ACT collision ANI duration overflow");
        start+=duration;
    }
    if(afterUs<start) {
        const auto frame=animation.frameAt(int64_t(afterUs/1000),false);
        if(std::find(out.begin(),out.end(),frame)==out.end())out.push_back(frame);
    }
    if(out.size()>maximum)throw std::invalid_argument("ACT collision frame boundary budget exceeded");
    return out;
}
} // namespace dnf
