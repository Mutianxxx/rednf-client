#pragma once
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>

namespace dnf {
// Source-qualified test ownership only. This uses the real EQU/equip request,
// so the production CannonBall weapon gate is exercised, never bypassed.
class FemaleGunnerHandcannonTestFixture {
    World &world_;
    Progression &progression_;
    int previousIndex_=-1,handcannonIndex_=-1;
    bool restored_=false;
    Json source_,beforeState_;
  public:
    FemaleGunnerHandcannonTestFixture(World &world,Progression &progression,const CharacterDefinition &character)
        :world_(world),progression_(progression) {
        int handcannon=-1;const Field *table=nullptr;
        for(const auto &field:character.settings.script.fields)if(field.tag=="[key value index]"&&!field.values.empty()&&
            (field.values[0]=="weaponSubTypeIndex"||field.values[0]=="defaultWeaponBySubType")) {
            if(table)throw std::invalid_argument("Ambiguous source handcannon fixture table");table=&field;
        }
        if(!table)throw std::invalid_argument("No source handcannon fixture table");
        for(size_t at=2;at+1<table->values.size();at+=2)if(table->values[at]==3)handcannon=table->values[at+1].get<int>();
        const auto *item=progression.item(handcannon);
        if(!item||item->source.number("[sub type]",-1)!=3||item->slot!="[weapon]")
            throw std::invalid_argument("Source handcannon fixture EQU is unavailable");
        const auto itemPath=item->path;const auto durability=item->durability,minimumLevel=item->minimumLevel;
        beforeState_=progression.state;
        while(progression.level()<minimumLevel) {
            const auto level=progression.level(),xp=progression.experienceToNextLevel();
            if(xp<=0)throw std::invalid_argument("Source handcannon fixture cannot reach its equipment level");
            progression.addExperience(xp);
            if(progression.level()<=level)throw std::invalid_argument("Source handcannon fixture progression did not advance");
        }
        previousIndex_=progression.equippedIndex("[weapon]");handcannonIndex_=int(progression.state.at("inventory").size());
        const int uid=progression.state.at("next_uid").get<int>();
        progression.state["inventory"].push_back({{"uid",uid},{"id",handcannon},{"count",1},{"durability",durability}});
        progression.state["next_uid"]=uid+1;
        const auto operation=world.changeEquipment(progression,handcannonIndex_);
        if(!operation.ok){progression.state=beforeState_;throw std::invalid_argument("Source handcannon fixture equip rejected: "+operation.message);}
        source_={{"equipment_id",handcannon},{"equipment_path",itemPath},{"owned_instance_uid",uid},
            {"source_subtype",3},{"character_settings",character.settings.script.path},{"settings_field_offset",table->offset},
            {"source_minimum_level",minimumLevel},{"fixture_level",progression.level()},
            {"policy","real-source-equipment-fixture-not-qualification-bypass"}};
    }
    const Json &source() const {return source_;}
    bool restore() {
        if(restored_)return true;
        const auto operation=previousIndex_>=0?world_.changeEquipment(progression_,previousIndex_):
            world_.changeEquipment(progression_,handcannonIndex_,true);
        if(!operation.ok)return false;
        progression_.state=beforeState_;world_.applyEquipment(progression_);
        restored_=true;return true;
    }
    ~FemaleGunnerHandcannonTestFixture(){if(!restored_)try{restore();}catch(...) {}}
};
}
