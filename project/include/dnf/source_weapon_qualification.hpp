#pragma once
#include "dnf/character_controller.hpp"
#include <cmath>
#include <limits>

namespace dnf {
// Legacy ItemDefinition::weapon is a four-slot Swordman compatibility value.
// Other jobs retain raw EQU subtype identities. One complete current CHR
// weapon-skill row is required; World still preflights actual EQU/LAY pixels,
// attributes and movement before committing equipment or restoration.
inline bool characterWeaponSourceSupported(const CharacterDefinition &character,
                                           const Script &equipment,int legacyCategory) {
    if(character.registration.id==0)return legacyCategory>=0;
    const Field *subtype=nullptr,*table=nullptr;
    for(const auto &field:equipment.fields)if(normalize(field.tag)=="[sub type]") {
        if(subtype)return false;subtype=&field;
    }
    for(const auto &field:character.source.script.fields)if(normalize(field.tag)=="[weapon skill info]") {
        if(table)return false;table=&field;
    }
    if(!subtype||subtype->values.size()!=1||!subtype->values[0].is_number_integer()||
       !table||table->values.empty()||table->values.size()%4)return false;
    if(subtype->values[0].is_number_unsigned()&&subtype->values[0].get<uint64_t>()>uint64_t(INT32_MAX))return false;
    const auto raw=subtype->values[0].get<int64_t>();
    if(raw<0||uint64_t(raw)>=table->values.size()/4)return false;
    for(size_t column=0;column<4;++column) {
        const auto &value=table->values[size_t(raw)*4+column];
        if(!value.is_number()||!std::isfinite(value.get<double>())||value.get<double>()<0)return false;
    }
    return true;
}
}
