#include "dnf/attack_status.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include <stdexcept>

namespace dnf {
namespace {
Script effectFixture(const std::string &tag,Json payload,const std::string &package) {
    Script out;out.path="fixture/extended-status.atk";out.fields={{"[active status]",Json::array(),0},{tag,payload,0}};
    size_t end=2;Json fields=Json::array();for(auto &f:out.fields){f.offset=end;end+=5*(f.values.size()+1);fields.push_back({f.tag,f.values});}
    const auto encoded=fields.dump();out.rawBytes.assign(end,0);for(size_t i=2;i<end;++i)out.rawBytes[i]=uint8_t(encoded[(i-2)%encoded.size()]);
    out.source={{"package_identity",package},{"member_sha256",sha256(out.rawBytes)},{"literal_path",out.path}};
    out.tokens=Json::array({{{"decoded_fixture",fields}}});return out;
}
StatusRequest effectRequest(const Script &source,uint64_t instance=1) {
    StatusRequest q;q.attacker={1,1};q.target.handle={2,1};q.attackerLevel=20;q.target.resistance.level=20;
    q.target.resistance.packageIdentity=source.source.at("package_identity");q.attackInstance=instance;q.attack=readAttackStatuses(source);
    q.independentAttack=100;q.independentRate=1;return q;
}
} // namespace
Json runStatusEffectsTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool condition,const char *message){if(!condition)throw std::runtime_error(std::string("Extended status: ")+message);checks.push_back(message);};
    const auto policy=StunStatusPolicy::inferredFlatChanceStunV1();CharacterCatalog catalog(pvf);
    const auto nativeAttack=pvf.script("character/gunner/atattackinfo/fastknee.atk");const auto package=pvf.identity();
    for(const auto id:{2,7,9,53,57,58,76,78,98,101,103,107,108}) {
        const auto source=readSkillSourceData(catalog.skillDefinition({5,id}));const auto parsed=readSkillAttackStatuses(source,1);
        check(parsed.usable() && !parsed.entries.empty(),"Actual female Gunner status SKL produces source-bound selected setter entries");
        check(parsed.source.snapshot(true)==source.snapshot(true) && !parsed.entries.front().sources.empty(),
              "SKL setter retains raw source, selected scopes, level-property schema, column operands and exact source references");
        auto q=effectRequest(nativeAttack,uint64_t(id));q.skill=parsed;
        StatusHost host(package,policy);Pcg32 random(29,7);const auto before=random.snapshot();
        auto applied=host.prepare(q,1000,random);
        check(applied.ready() && host.canPublish(applied,random),"Source-bound SKL status prepares against the original dormant ATK without editing it");
        host.publish(std::move(applied),random);const auto snapshot=host.snapshot(1000,9,true);
        check(snapshot.at("sources").at(nativeAttack.path).at("document").at("raw_bytes")==nativeAttack.rawBytes,
              "Accepted source setter keeps original ATK bytes separate from SKL source provenance");
        StatusHost restored(package,policy);restored.restore(snapshot,1500,9,[&](const std::string &path){return pvf.script(path);},
            [&](EntityHandle target){return target==q.target.handle;});
        auto duplicate=restored.prepare(q,1500,random);
        check(duplicate.ready() && duplicate.receipt.at("deduplicated")==true,
              "Skill status contact restores same-generation source evidence and cannot reroll or reapply the same hit");
        samples[std::to_string(id)]=snapshot;
    }
    for(const auto *tag:{"[freeze]","[burn]","[lightning]","[bleeding]","[blind]"}) {
        const bool freeze=std::string(tag)=="[freeze]";
        const bool blind=std::string(tag)=="[blind]";
        const auto atk=effectFixture(tag,freeze?Json::array({100,20,3000}):blind?Json::array({100,20,3000,45,21}):Json::array({100,20,3000,37}),package);
        const auto parsed=readAttackStatuses(atk);
        check(parsed.usable() && parsed.entries[0].tag==tag && parsed.entries[0].durationMs==3000,
              "Annotated sample extended status width preserves complete probability, authored level, milliseconds and damage");
        auto q=effectRequest(atk);StatusHost host(package,policy);Pcg32 random;const auto randomBefore=random.snapshot();
        auto prepared=host.prepare(q,1000,random);check(prepared.ready(),"Positive supported extended ATK status prepares a real effect instance");
        host.publish(std::move(prepared),random);auto start=host.snapshot(1000,11,true);
        start["effects"][0]["future_effect_metadata"]={{"preserve",true},{"opaque",Json::array({7,"versioned"})}};
        check(start.at("effects").size()==1 && random.snapshot()==randomBefore,
              "Guaranteed extended status publishes one monotonic instance without a probability draw");
        if(freeze) check(host.frozen(q.target.handle,1000) && host.controlled(q.target.handle,3999) && !host.controlled(q.target.handle,4000),
                         "Freeze has independent source duration and blocks control only inside its exact active interval");
        if(blind) check(host.blindMissPercent(q.target.handle,1000)==21 && host.blindMissPercent(q.target.handle,4000)==0 &&
                       !host.controlled(q.target.handle,1000),"Blind consumes exact authored stuck increase as accuracy loss and does not block target movement");
        const auto resolver=[&](const std::string &path){return path==atk.path?atk:pvf.script(path);};
        StatusHost loaded(package,policy);loaded.restore(start,1500,11,resolver,[&](EntityHandle t){return t==q.target.handle;});
        check(loaded.snapshot(1500,11,true).at("effects")[0].at("future_effect_metadata")==
              start.at("effects")[0].at("future_effect_metadata"),
              "Extended status roundtrip preserves unknown future effect metadata alongside validated source, identity and schedule");
        if(std::string(tag)=="[burn]" || std::string(tag)=="[bleeding]") {
            bool snapshotRejected=false;try{host.snapshot(2000,11);}catch(const std::exception &){snapshotRejected=true;}
            check(snapshotRejected,"Snapshot rejects an uncommitted due periodic HP receipt instead of silently losing pending damage");
            auto advance=loaded.prepareAdvance(2000);
            check(advance.ready() && advance.receipt.at("damages").empty(),"Restored periodic status retains remaining delay instead of drawing or firing early");
            loaded.publish(std::move(advance));advance=loaded.prepareAdvance(2500);
            check(advance.ready() && advance.receipt.at("damages").size()==1 && advance.receipt.at("damages")[0].at("amount")==37,
                  "Burn and bleeding emit exact frozen source damage on their named beta interval after restore");
            loaded.publish(std::move(advance));const auto checkpoint=loaded.snapshot(2500,12,true);
            StatusHost replay(package,policy);replay.restore(checkpoint,2500,12,resolver,[&](EntityHandle t){return t==q.target.handle;});
            const auto repeat=replay.prepareAdvance(2500);
            check(repeat.ready() && repeat.receipt.at("damages").empty(),"Committed periodic receipt and next deadline restore without duplicating a due tick");
            auto end=replay.prepareAdvance(4500);
            check(end.ready() && end.receipt.at("damages").size()==2,"Catch-up emits all remaining source-duration periodic ticks in deterministic order");
            replay.publish(std::move(end));check(replay.snapshot(4500,13).at("effects").empty(),"Expired periodic instances clean up after the final due damage receipt");
        } else if(std::string(tag)=="[lightning]") {
            q.attackInstance=2;auto contact=loaded.prepare(q,1500,random);
            check(contact.ready() && contact.receipt.at("bonus_hp_damage")==37,
                  "Lightning contributes its frozen extra damage to a subsequent accepted contact in the same status/RNG candidate");
            loaded.publish(std::move(contact),random);auto same=loaded.prepare(q,1500,random);
            check(same.ready() && same.receipt.at("deduplicated")==true && !same.receipt.contains("bonus_hp_damage"),
                  "Repeated accepted-hit identity cannot trigger lightning damage twice");
        }
        auto tampered=start;tampered["effects"][0]["hp_damage"]=123456;
        bool rejected=false;try{StatusHost invalid(package,policy);invalid.restore(tampered,1500,11,resolver,[&](EntityHandle){return true;});}
        catch(const std::exception &){rejected=true;}
        check(rejected,"Forged frozen extended-status damage rejects before restored state publication");
        host.clearTarget(q.target.handle,1000,"test_cleanse");check(host.snapshot(1000,14).at("effects").empty(),
            "Target cleansing removes freeze, lightning and periodic effects without clearing source contact deduplication");
    }
    auto malformed=effectFixture("[burn]",Json::array({100,20,3000,37,10,1,1000}),package);
    check(!readAttackStatuses(malformed).usable(),"Burn aura operands remain required unsupported until their geometry and nearby-target consumer exists");
    auto skill=readSkillAttackStatuses(readSkillSourceData(catalog.skillDefinition({5,58})),1);
    skill.entries.front().chancePercent=100;auto q=effectRequest(nativeAttack);q.skill=skill;StatusHost host(package,policy);Pcg32 random;
    const auto randomBefore=random.snapshot();const auto rejected=host.prepare(q,1000,random);
    check(!rejected.ready() && random.snapshot()==randomBefore && host.snapshot(1000,1).at("effects").empty(),
          "Forged SKL setter values fail source recomputation and leave host, instance IDs and RNG unchanged");
    {
        const auto source=pvf.script("passiveobject/character/gunner/attackinfo/emp_bomb_sub2.atk");
        auto legacyRequest=effectRequest(source);StatusHost legacy(package,policy);Pcg32 legacyRandom;
        auto candidate=legacy.prepare(legacyRequest,1000,legacyRandom);legacy.publish(std::move(candidate),legacyRandom);
        auto old=legacy.snapshot(1000,15,true);old.erase("effects");old["future_top_level"]={{"keep",77}};
        old["active"][0]["future_stun_field"]="preserved old bundle";
        StatusHost reloaded(package,policy);reloaded.restore(old,1500,15,[&](const std::string &path){return pvf.script(path);},
            [&](EntityHandle t){return t==legacyRequest.target.handle;});
        const auto migrated=reloaded.snapshot(1500,15,true);
        check(migrated.at("future_top_level")==old.at("future_top_level") &&
              migrated.at("active")[0].at("future_stun_field")=="preserved old bundle" &&
              migrated.at("active")[0].at("source_entry")==old.at("active")[0].at("source_entry") && migrated.at("effects").empty(),
              "Historical stun-only snapshots restore without an effects field and preserve unknown top-level and stun data");
    }
    {
        const auto plan=loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0});size_t upgraded=0,addedBleed=0,changedStatus=0;
        Json features=Json::array();
        for(const auto &[key,row]:plan.skills) {
            auto tuples=row.data->definition.fieldsInScope("[special level up]","dungeon");
            if(tuples.empty())tuples=row.data->definition.fieldsInScope("[special level up]","common");
            if(tuples.empty()||tuples.front()->field.values.empty())continue;
            const auto prerequisites=row.data->definition.fieldsInScope("[pre required skill]","common");
            const auto prerequisite=prerequisites.empty()?Json::array():prerequisites.front()->field.values;int target=-1,level=1;
            if(prerequisite.size()>=2&&prerequisite[0].is_number_integer()&&prerequisite[1].is_number_integer()) {
                target=prerequisite[0];level=prerequisite[1];
            }
            if(target<0)for(const auto &[candidate,skill]:plan.skills)
                for(const auto *field:skill.data->definition.fieldsInScope("[feature skill index]","common"))for(const auto &id:field->field.values)
                    if(id.is_number_integer()&&id.get<int>()==key.skillId)target=candidate.skillId;
            if(target<0)continue;
            const auto &base=*plan.skills.at({5,target}).data;const auto original=base.snapshot(true);
            auto command=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,target}),base,level,0);
            applyFemaleGunnerTpOperands(command,{{key,1}},plan,0);
            const auto setter=readFemaleGunnerSkillAttackStatuses(command,plan),plain=readSkillAttackStatuses(base,level);
            check(setter.usable()&&setter.features.size()==1,"Every registered TP command status overlay is recomputed from immutable base and TP sources");
            check(setter.source.snapshot(true)==original,"TP status overlay leaves original selected source bytes and scope view unchanged");
            if(base.definition.kind==SkillSourceKind::Passive)check(setter.entries.empty(),
                "A source-qualified passive TP retains its feature evidence without generating unrelated global status procs");
            if(setter.entries.size()!=plain.entries.size())++changedStatus;
            else for(size_t n=0;n<setter.entries.size();++n)if(setter.entries[n].chancePercent!=plain.entries[n].chancePercent ||
                setter.entries[n].durationMs!=plain.entries[n].durationMs || setter.entries[n].damage!=plain.entries[n].damage) {++changedStatus;break;}
            if(target==40)for(const auto &entry:setter.entries)if(entry.kind==AttackStatusKind::Bleeding)++addedBleed;
            auto q=effectRequest(nativeAttack,10000+uint64_t(key.skillId));q.skill=setter;StatusHost upgradedHost(package,policy);Pcg32 featureRandom(31,17);
            auto prepared=upgradedHost.prepare(q,1000,featureRandom);check(prepared.ready(),"TP status passes the same atomic source validation as original skill setters");
            upgradedHost.publish(std::move(prepared),featureRandom);const auto saved=upgradedHost.snapshot(1000,20,true);
            StatusHost restored(package,policy);restored.restore(saved,1500,20,[&](const std::string &path){return pvf.script(path);},
                [&](EntityHandle handle){return handle==q.target.handle;});
            const auto repeat=restored.prepare(q,1500,featureRandom);
            check(repeat.ready()&&repeat.receipt.at("deduplicated")==true,"TP status restores original base and feature source hashes without rerolling accepted contact");
            auto forged=command;forged.rawTables["level_info"][1]=123456;
            check(!readFemaleGunnerSkillAttackStatuses(forged,plan).usable(),"A command with forged TP numeric table is rejected before status publication");
            auto tampered=setter;tampered.features[0].source.selected.begin()->second.field.values.push_back("forged");q.skill=tampered;
            const auto before=featureRandom.snapshot();const auto rejected=restored.prepare(q,1500,featureRandom);
            check(!rejected.ready()&&featureRandom.snapshot()==before,"Modified TP selected source view fails canonical validation and preserves RNG");
            features.push_back({{"tp",key.json()},{"base",target},{"setter",setter.snapshot(true)}});++upgraded;
        }
        check(upgraded>20&&addedBleed>0&&changedStatus>0,"TP schema changes add actual Steyr bleeding and change real status operands across the registered feature set");
        for(const int requested:{3,6,7}) {
            auto alternate=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,100}),*plan.skills.at({5,100}).data,1,0);
            alternate.key={5,requested};alternate.skillSource=plan.skills.at(alternate.key).source;
            alternate.family=requested==3?"twingunblade_somersault":requested==6?"twingunblade_chain_cut":"twingunblade_spinning_blade";
            const auto setter=readFemaleGunnerSkillAttackStatuses(alternate,plan);
            check(setter.usable()&&setter.source.definition.key==SkillKey{5,100}&&setter.entries.empty(),
                "Source100 alternate actions use mode status authority without inheriting ordinary Sting stun or Punisher grab semantics");
            alternate.rawTables["source"]["member_sha256"]="forged";
            check(!readFemaleGunnerSkillAttackStatuses(alternate,plan).usable(),"Foreign alternate-mode status source identity fails before publication");
        }
        samples["feature_status"]={{"upgraded",upgraded},{"added_steyr_bleeding",addedBleed},{"changed_status_skills",changedStatus},{"rows",features}};
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","source-bound SKL setters and ATK freeze/lightning/burn/bleeding; beta cadence/scaling explicitly inferred; native parity pending"}};
}
} // namespace dnf
