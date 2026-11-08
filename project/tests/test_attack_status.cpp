#include "dnf/attack_status.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
struct StatusChecks {
    Json checks=Json::array();
    void operator()(bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Attack status: ")+message);
        checks.push_back(message);
    }
    template<class Action> bool rejects(Action action) const {
        try {action();} catch(const std::exception &) {return true;}return false;
    }
};
// Synthetic decoded documents exercise malformed/ordered parser inputs. The
// bytes have valid five-byte spans and an explicit fixture identity; they are
// never represented as a native PVF serializer or used by normal gameplay.
void statusSeal(Script &source,const std::string &package="status-fixture") {
    size_t end=2;Json fields=Json::array();
    for(auto &field:source.fields) {field.offset=end;end+=5*(1+field.values.size());fields.push_back({field.tag,field.values});}
    const auto text=fields.dump();source.rawBytes.assign(end,0);
    for(size_t i=2;i<end;++i) source.rawBytes[i]=uint8_t(text[(i-2)%text.size()]);
    source.source={{"package_identity",package},{"literal_path",source.path},{"member_sha256",sha256(source.rawBytes)}};
    source.tokens=Json::array({{{"fixture_decoded_fields",fields},{"unknown_repeat",Json::array({7,7})}}});
}
Script statusAttack(const std::string &path,double chance=100,int duration=1000,int level=0) {
    Script out;out.path=path;out.fields={{"[active status]",Json::array(),0},
        {"[stun]",Json::array({chance,level,duration}),0}};statusSeal(out);return out;
}
StatusResistanceSnapshot statusZero(const std::string &package="status-fixture",int level=1) {
    StatusResistanceSnapshot out;out.packageIdentity=package;out.level=level;
    out.sources={{"fixture","explicit zero source resistance"}};return out;
}
StatusRequest statusRequest(const Script &source,EntityHandle owner,EntityHandle target,uint64_t attack=1) {
    StatusRequest out;out.attacker=owner;out.attackerLevel=1;out.target.handle=target;
    out.target.resistance=statusZero(source.source.at("package_identity").get<std::string>());
    out.attackInstance=attack;out.attack=readAttackStatuses(source);return out;
}
EquippedAttributeSource statusCoat(const std::string &package) {
    EquippedAttributeSource out;out.instanceUid=7;out.equippedSlot="[coat]";out.currentDurability=35;
    out.source.path="equipment/status-fixture-coat.equ";
    out.source.fields={{"[usable job]",Json::array({"[swordman]"}),0},{"[equipment type]",Json::array({"[coat]",17}),0},
        {"[minimum level]",Json::array({1}),0},{"[durability]",Json::array({35}),0},
        {"[stun resistance]",Json::array({25}),0},{"[all activestatus resistance]",Json::array({5}),0}};
    statusSeal(out.source,package);return out;
}
} // namespace

Json runAttackStatusTests(Pvf &pvf,Assets &assets) {
    (void)assets;StatusChecks check;Json samples=Json::object();
    const auto policy=StunStatusPolicy::inferredFlatChanceStunV1();
    const auto heading=pvf.script("monster/tau/attackinfo/heading.atk");const auto native=readAttackStatuses(heading);
    check(native.usable() && native.entries.size()==1 && native.entries[0].kind==AttackStatusKind::Stun &&
        native.entries[0].chancePercent==30 && native.entries[0].level==0 && native.entries[0].durationMs==1000 &&
        native.entries[0].rawPayload==Json::array({30,0,1000}) && native.entries[0].sources.size()==2 &&
        native.entries[0].sources[0].byteOffset==107 && native.entries[0].sources[1].byteOffset==112,
        "Actual Tau heading preserves separate type-five stun, source chance30 level0 duration1000 and both exact field spans");
    check(native.source.rawBytes==pvf.read(heading.path) && native.snapshot(true).at("document").at("tokens")==heading.tokens &&
        native.entries[0].sources[0].memberSha256=="42e83c719f986b648a118385fd3212ced08a59c9555d7ee7fce017bfc9bc9b01",
        "Native attack bytes, ordered tokens, content identity and exact member hash remain lossless");
    samples["native_heading"]=native.snapshot(true);
    auto none=statusAttack("fixture/none.atk");none.fields={{"[active status]",Json::array({"[none]",17,"ignored"}),0}};statusSeal(none);
    auto inlineStun=statusAttack("fixture/inline.atk");inlineStun.fields={{"[active status]",Json::array({"[stun]",100,20,3000}),0}};statusSeal(inlineStun);
    check(readAttackStatuses(none).usable() && readAttackStatuses(none).entries[0].rawPayload==Json::array({17,"ignored"}) &&
        readAttackStatuses(inlineStun).usable() && readAttackStatuses(inlineStun).entries[0].level==20,
        "None retains ignored source operands and inline enum stun uses its own authored payload");
    Script empty;empty.path="fixture/empty.atk";statusSeal(empty);
    check(readAttackStatuses(empty).usable() && readAttackStatuses(empty).entries.empty(),"An ATK without active status remains an empty source document");
    auto poison=statusAttack("fixture/poison.atk");poison.fields[1]={"[poison]",Json::array({50,7,2000,13,0.5,29}),0};statusSeal(poison);
    check(!readAttackStatuses(poison).usable() && readAttackStatuses(poison).entries[0].rawPayload==poison.fields[1].values &&
        readAttackStatuses(poison).entries[0].kind==AttackStatusKind::RequiredUnsupported,
        "Required unsupported poison retains its complete variable payload instead of being silently converted or discarded");
    auto pvp=poison;pvp.fields.insert(pvp.fields.begin(),{"[pvp]",Json::array(),0});pvp.fields.push_back({"[/pvp]",Json::array(),0});statusSeal(pvp);
    check(readAttackStatuses(pvp).usable() && !readAttackStatuses(pvp).entries[0].runtime &&
        readAttackStatuses(pvp).entries[0].rawPayload==poison.fields[1].values,
        "Unsupported PvP-only status remains preserved and explicitly excluded from the dungeon consumer");
    for(const auto &bad:std::vector<Json>{Json::array({30,0}),Json::array({30,0,0}),Json::array({101,0,1000}),
        Json::array({30,-1,1000}),Json::array({30,0,"1000"}),Json{{"a",30},{"b",0},{"c",1000}}}) {
        auto malformed=statusAttack("fixture/malformed.atk");malformed.fields[1].values=bad;statusSeal(malformed);
        check(!readAttackStatuses(malformed).usable(),"Malformed stun shape, chance, level or milliseconds returns required diagnostics");
    }
    auto ordered=statusAttack("fixture/ordered.atk");ordered.fields.push_back(ordered.fields[0]);ordered.fields.push_back(ordered.fields[1]);statusSeal(ordered);
    check(readAttackStatuses(ordered).entries.size()==2 && readAttackStatuses(ordered).entries[1].ordinal==1 &&
        readAttackStatuses(ordered).entries[0].sources[0].ordinal!=readAttackStatuses(ordered).entries[1].sources[0].ordinal,
        "Repeated source statuses retain their authored order and independent source ordinals");

    CharacterCatalog characters(pvf);const auto &swordman=characters.at(0);
    const auto base=buildCharacterBaseAttributes(swordman,{},5,CharacterGrowthPolicy::inferredChrGrowthV1());
    const auto resistance=evaluateCharacterStatusResistances(base,swordman,{},5);
    check(resistance.usable() && resistance.stunResistance()==0 && resistance.values[13]==0,
        "Current Swordman source produces explicit zero stun resistance without relabelling evasion or elemental resistance");
    auto coat=statusCoat(resistance.packageIdentity);
    const auto dressed=evaluateCharacterStatusResistances(base,swordman,{coat},5);
    check(dressed.usable() && dressed.values[3]==25 && dressed.allActiveStatusResistance==5 && dressed.stunResistance()==30,
        "Qualified owned EQU stun25 and all-active5 feed the actual stun resistance consumer as separate source groups");
    coat.currentDurability=0;
    check(evaluateCharacterStatusResistances(base,swordman,{coat},5).stunResistance()==0,
        "A broken durable item stops contributing both individual and global status resistance");
    coat.currentDurability=35;
    check(!evaluateCharacterStatusResistances(base,swordman,{coat,coat},5).usable(),"Repeated inventory UID and occupied slot cannot double-count status resistance");
    auto wrong=coat;wrong.equippedSlot="[weapon]";
    check(!evaluateCharacterStatusResistances(base,swordman,{wrong},5).usable(),"Status equipment uses the shared exact equipped-slot qualification");
    wrong=coat;wrong.source.fields[0].values=Json::array({"[fighter]"});statusSeal(wrong.source,resistance.packageIdentity);
    check(!evaluateCharacterStatusResistances(base,swordman,{wrong},5).usable(),"Wrong-job status equipment rejects rather than contributing its resistances");
    wrong=coat;wrong.source.fields[2].values=Json::array({6});statusSeal(wrong.source,resistance.packageIdentity);
    check(!evaluateCharacterStatusResistances(base,swordman,{wrong},5).usable(),"Status equipment qualification consumes the normal progression level");
    wrong=coat;wrong.source.fields.push_back({"[stun resistance]",Json::array({2}),0});statusSeal(wrong.source,resistance.packageIdentity);
    check(!evaluateCharacterStatusResistances(base,swordman,{wrong},5).usable(),"Ambiguous repeated resistance scalars block the complete attribute result");
    wrong=coat;wrong.source.fields.insert(wrong.source.fields.begin()+4,{"[if]",Json::array(),0});statusSeal(wrong.source,resistance.packageIdentity);
    check(!evaluateCharacterStatusResistances(base,swordman,{wrong},5).usable(),"Conditional resistance modifiers require their own consumer instead of becoming permanent flats");
    const auto mob=evaluateMonsterCombatAttributes(readMonsterAttributeSource(pvf,"monster/tau/tauarmy.mob",false),1,false,
        MonsterCombatAttributePolicy::inferredMobCombatTableV1());const auto mobResistance=makeMonsterStatusResistances(mob);
    check(mob.usable() && mobResistance.usable() && mobResistance.values[3]==mob.attributes->statusResistance[3] &&
        statusResistanceOrder()[3]==std::string("stun") && statusResistanceOrder()[13]==std::string("stuck"),
        "Frozen monster resistance uses the named adapter stun slot3 while keeping stuck evasion at slot13");
    samples["character_resistance"]=dressed.snapshot();samples["monster_resistance"]=mobResistance.snapshot();

    EntityRegistry registry;const auto owner=registry.create(),target=registry.create(),other=registry.create(),renewed=registry.create();
    const auto sure=statusAttack("fixture/sure.atk"),zero=statusAttack("fixture/zero.atk",0),shorter=statusAttack("fixture/short.atk",100,100);
    const auto chance=statusAttack("fixture/chance.atk",30);std::map<std::string,Script> documents;
    for(const auto &script:{sure,zero,shorter,chance}) documents.emplace(script.path,script);
    const auto resolve=[&](const std::string &path){return documents.at(path);};
    auto request=statusRequest(sure,owner,target);StatusHost host("status-fixture",policy);Pcg32 random(7,13);
    check(!StatusHost("status-fixture").prepare(request,100,random).ready(),"The default host policy cannot silently enable inferred status behavior");
    const auto initial=host.snapshot(100,1),initialRandom=random.snapshot();auto prepared=host.prepare(request,100,random);
    check(prepared.ready() && host.snapshot(100,1)==initial && random.snapshot()==initialRandom && !host.stunned(target,100),
        "Successful preparation stages HP-independent status, IDs and random state without publishing any live mutation");
    const auto receipt=prepared.receipt;host.publish(std::move(prepared),random);
    check(host.stunned(target,100) && host.instance(target,100)->id==1 && host.instance(target,100)->expiresMs==1100 &&
        random.snapshot()==initialRandom && !prepared.ready(),"A 100-percent status publishes one unique instance and exact fixed milliseconds without a random draw");
    check(check.rejects([&]{host.publish(std::move(prepared),random);}),"A consumed status candidate cannot publish a second time");
    const auto beforeDuplicate=host.instance(target,100)->id;auto duplicate=host.prepare(request,100,random);
    check(duplicate.ready() && duplicate.receipt.at("deduplicated")==true,"The same accepted attack and hit index use the persisted contact ledger");
    host.publish(std::move(duplicate),random);
    check(host.instance(target,100)->id==beforeDuplicate && random.snapshot()==initialRandom,"Duplicate contact cannot reroll, allocate another instance or extend the timer");
    auto refresh=statusRequest(shorter,owner,target,2);auto refreshed=host.prepare(refresh,200,random);host.publish(std::move(refreshed),random);
    check(host.instance(target,200)->id==2 && host.instance(target,200)->expiresMs==1100 && host.instance(target,200)->maximumDurationMs==1000,
        "A successful shorter reapplication gets a new identity while retaining the longer expiration and duration watermark");
    check(host.stunned(target,1099) && !host.stunned(target,1100),"Stun expires at the exact authored millisecond boundary");
    registry.retire(owner);
    check(host.stunned(target,200),"Retiring the owner does not remove a status already belonging to the target");
    host.clearTarget(target,200,"fixture cleanse");auto cleansed=host.prepare(refresh,200,random);host.publish(std::move(cleansed),random);
    check(!host.stunned(target,200),"Cleansing removes active stun while preserving same-contact deduplication");
    const auto watermark=host.snapshot(200,1).at("instance_ids");host.clearAll(200,"fixture scene change");
    check(host.snapshot(200,1).at("contacts").empty() && host.snapshot(200,1).at("sources").empty() &&
        host.snapshot(200,1).at("instance_ids")==watermark,"Scene cleanup releases contacts and bound sources without resetting the monotonic instance IDs");
    auto failed=statusRequest(zero,owner,target,3);auto failure=host.prepare(failed,200,random);host.publish(std::move(failure),random);
    auto failedDuplicate=host.prepare(failed,200,random);
    check(failedDuplicate.ready() && failedDuplicate.receipt.at("deduplicated")==true && !host.stunned(target,200) && random.snapshot()==initialRandom,
        "A zero-percent failure consumes no RNG but still persists its accepted contact so it cannot reroll");
    host.publish(std::move(failedDuplicate),random);
    auto resisted=request;resisted.attackInstance=4;resisted.target.resistance.values[3]=25;resisted.target.resistance.allActiveStatusResistance=5;
    const auto beforeReject=host.snapshot(200,1);
    check(!host.prepare(resisted,200,random).ready() && host.snapshot(200,1)==beforeReject,
        "Nonzero resistance blocks publication unless the explicitly comparable percentage inference is enabled");
    StatusHost inferred("status-fixture",StunStatusPolicy::inferredFlatChanceStunV1(true));auto inferredPrepared=inferred.prepare(resisted,200,random);
    check(inferredPrepared.ready() && inferredPrepared.receipt.at("outcomes")[0].at("effective_chance_percent")==70 &&
        inferredPrepared.receipt.at("outcomes")[0].at("target_level")==1,
        "Explicit resistance inference consumes stun25 plus global5 as a 70-percent chance without an invented level ratio");
    auto highLevel=resisted;highLevel.attackerLevel=99;highLevel.target.resistance.level=99;auto highPrepared=inferred.prepare(highLevel,200,random);
    check(highPrepared.ready() && highPrepared.receipt.at("outcomes")[0].at("effective_chance_percent")==70,
        "Authored and participant levels remain trace data and do not silently scale status probability");
    auto immune=request;immune.attackInstance=5;immune.target.immuneToStun=true;
    check(!host.prepare(immune,200,random).ready(),"Immunity requires explicit source evidence");
    immune.target.immunitySource={{"fixture","documented immunity"}};auto immunePrepared=host.prepare(immune,200,random);
    check(immunePrepared.ready() && immunePrepared.receipt.at("outcomes")[0].at("procced")==false &&
        immunePrepared.receipt.at("draws_before")==immunePrepared.receipt.at("draws_after"),"Sourced immunity consumes neither RNG nor an active instance");

    StatusHost rolled("status-fixture",policy);Pcg32 rollRandom(41,3),expectedRandom=rollRandom;
    const auto expectedRoll=expectedRandom.bounded(1000000);auto chanceRequest=statusRequest(chance,owner,target,6);
    auto rollPrepared=rolled.prepare(chanceRequest,100,rollRandom);
    check(rollPrepared.ready() && rollPrepared.receipt.at("outcomes")[0].at("roll_0_999999")==expectedRoll &&
        rollPrepared.receipt.at("outcomes")[0].at("procced")==bool(expectedRoll<300000) && rollRandom.draws()==0,
        "An intermediate source chance stages exactly the documented PCG bounded draw and threshold comparison");
    rolled.publish(std::move(rollPrepared),rollRandom);
    check(rollRandom.snapshot()==expectedRandom.snapshot(),"Accepted publication commits the candidate random stream exactly once");
    auto stale=rolled.prepare(request,100,rollRandom);rollRandom.next();const auto staleBefore=rolled.snapshot(100,1),staleRng=rollRandom.snapshot();
    check(check.rejects([&]{rolled.publish(std::move(stale),rollRandom);}) && rolled.snapshot(100,1)==staleBefore && rollRandom.snapshot()==staleRng,
        "An independently changed RNG rejects the staged status before any host or RNG publication");
    stale=rolled.prepare(request,100,rollRandom);rolled.expire(101);
    check(!rolled.canPublish(stale,rollRandom),"A changed host revision invalidates an earlier candidate");
    auto exhaustedRandom=rollRandom;auto exhaustedState=exhaustedRandom.snapshot();exhaustedState["draws"]=UINT64_MAX;exhaustedRandom.restore(exhaustedState);
    const auto exhaustedBefore=rolled.snapshot(101,1);auto exhaustedRequest=chanceRequest;exhaustedRequest.attackInstance=99;
    check(!rolled.prepare(exhaustedRequest,101,exhaustedRandom).ready() && rolled.snapshot(101,1)==exhaustedBefore && exhaustedRandom.snapshot()==exhaustedState,
        "Random counter exhaustion rejects without consuming live state or publishing a partial status");
    check(!StatusHost("status-fixture",policy).prepare(request,UINT64_MAX-100,random).ready(),"Status time overflow rejects before publication");
    StatusHost exhaustedHost("status-fixture",policy);auto exhaustedIds=exhaustedHost.snapshot(100,1);exhaustedIds["instance_ids"]["next"]=0;
    exhaustedHost.restore(exhaustedIds,100,1,resolve,[](EntityHandle){return true;});
    check(!exhaustedHost.prepare(request,100,random).ready(),"An exhausted persisted ID watermark cannot wrap to a reused instance");

    StatusHost savedHost("status-fixture",policy);Pcg32 savedRandom;auto a=savedHost.prepare(request,100,savedRandom);savedHost.publish(std::move(a),savedRandom);
    auto second=statusRequest(sure,owner,other,7);a=savedHost.prepare(second,100,savedRandom);savedHost.publish(std::move(a),savedRandom);
    auto saved=savedHost.snapshot(350,42,true);saved["future_metadata"]={{"preserve",17}};saved["active"][0]["future_instance"]=19;
    StatusHost restored("status-fixture",policy);const auto live=[&](EntityHandle h){return h==target || h==other || h==renewed;};
    restored.restore(saved,5000,42,resolve,live);
    check(restored.stunned(target,5749) && !restored.stunned(target,5750) && restored.instance(target,5000)->attacker==owner &&
        restored.snapshot(5000,42).at("future_metadata")==saved.at("future_metadata") &&
        restored.snapshot(5000,42).at("active")[0].at("future_instance")==19,
        "Same-generation restore preserves remaining milliseconds, historical owner, and unknown root/instance metadata without rerolling");
    auto repeat=restored.prepare(request,5000,savedRandom);
    check(repeat.ready() && repeat.receipt.at("deduplicated")==true,"Restored accepted contacts prevent duplicate status and RNG work after reload");
    const auto restoreBefore=restored.snapshot(5000,42);
    check(check.rejects([&]{restored.restore(saved,5000,43,resolve,live);}) && restored.snapshot(5000,42)==restoreBefore,
        "Wrong commit generation rejects the entire status restore atomically");
    auto bad=saved;bad["sources"][sure.path]["source"]["member_sha256"]="modified";
    check(check.rejects([&]{restored.restore(bad,5000,42,resolve,live);}) && restored.snapshot(5000,42)==restoreBefore,
        "A source hash mismatch rejects without overwriting current statuses");
    bad=saved;bad["active"][1]["id"]=bad["active"][0]["id"];
    check(check.rejects([&]{restored.restore(bad,5000,42,resolve,live);}),"Duplicate active instance identities cannot pass restore");
    bad=saved;bad["contacts"]=Json::array();
    check(check.rejects([&]{restored.restore(bad,5000,42,resolve,live);}),"An active status without its successful accepted-contact record cannot pass restore");
    check(check.rejects([&]{restored.restore(saved,5000,42,resolve,[](EntityHandle){return false;});}),"Stale target handles require an explicit reconstruction mapping before restore");
    auto aba=restored.prepare(request,5000,savedRandom);const auto abaSaved=restored.snapshot(5000,42);restored.restore(abaSaved,5000,42,resolve,live);
    check(!restored.canPublish(aba,savedRandom),"Restoring an equal saved revision cannot revive an earlier candidate through revision ABA");

    auto bundle=savedHost.snapshotTarget(other,350,42,true);
    check(bundle.at("active").size()==1 && bundle.at("contacts").size()==1 && bundle.at("sources").size()==1 &&
        bundle.at("target_bundle").at("target")==other.json() && bundle.at("instance_ids")==saved.at("instance_ids"),
        "Single-target export contains only its own active/contact/source dependency closure and the full global ID watermark");
    StatusHost merged("status-fixture",policy);Pcg32 mergeRandom;
    a=merged.prepare(request,4500,mergeRandom);merged.publish(std::move(a),mergeRandom);
    const auto mergeLive=[&](EntityHandle h){return h==target || h==renewed;};
    merged.mergeTarget(bundle,other,renewed,5000,42,resolve,mergeLive);
    check(merged.stunned(target,5000) && merged.stunned(renewed,5000) && merged.instance(renewed,5000)->id==2 &&
        merged.instance(renewed,5000)->attacker==owner && merged.snapshot(5000,42).at("contacts").size()==2 &&
        merged.snapshot(5000,42).at("instance_ids").at("next")==3,
        "Target merge remaps the explicit target, preserves historical owner and unrelated contacts, and merges the unique-ID watermark");
    auto remapped=second;remapped.target.handle=renewed;auto remappedPrepared=merged.prepare(remapped,5000,mergeRandom);
    check(remappedPrepared.ready() && remappedPrepared.receipt.at("deduplicated")==true,
        "Imported contact identities are rehashed for the new target so a restored attack cannot reroll");
    const auto mergedBefore=merged.snapshot(5000,42);
    check(check.rejects([&]{merged.mergeTarget(bundle,target,renewed,5000,42,resolve,mergeLive);}) && merged.snapshot(5000,42)==mergedBefore,
        "A target bundle cannot be applied using a different claimed historical target");
    bad=bundle;bad["contacts"][0]["identity"]["target"]=target.json();
    check(check.rejects([&]{merged.mergeTarget(bad,other,renewed,5000,42,resolve,mergeLive);}) && merged.snapshot(5000,42)==mergedBefore,
        "Foreign-target contact injection rejects the complete target merge before publication");
    check(check.rejects([&]{merged.mergeTarget(bundle,other,renewed,5000,41,resolve,mergeLive);}),"Target merge checks its exact actor/character commit generation");
    check(check.rejects([&]{merged.mergeTarget(bundle,other,renewed,5000,42,resolve,live);}),
        "An explicitly mapped old target that is still live cannot be duplicated onto another live entity");
    auto conflicting=savedHost.snapshotTarget(target,350,42);
    StatusHost collision("status-fixture",policy);auto c=statusRequest(sure,owner,other,8);a=collision.prepare(c,100,mergeRandom);collision.publish(std::move(a),mergeRandom);
    const auto collisionBefore=collision.snapshot(5000,42);
    check(check.rejects([&]{collision.mergeTarget(conflicting,target,renewed,5000,42,resolve,
        [&](EntityHandle h){return h==other || h==renewed;});}) && collision.snapshot(5000,42)==collisionBefore,
        "Two different targets cannot import the same historical successful instance ID");
    auto retiredMerge=savedHost;retiredMerge.mergeTarget(bundle,other,renewed,500,42,resolve,mergeLive);
    check(retiredMerge.stunned(target,500) && !retiredMerge.stunned(other,500) && retiredMerge.stunned(renewed,500) &&
        retiredMerge.snapshot(500,42).at("contacts").size()==2,
        "Retired old-target active and contact data are replaced explicitly while another live target remains intact");
    retiredMerge.mergeTarget(bundle,other,renewed,500,42,resolve,mergeLive);
    check(retiredMerge.instance(renewed,500)->id==2 && retiredMerge.snapshot(500,42).at("contacts").size()==2 &&
        retiredMerge.snapshot(500,42).at("instance_ids").at("next")==3,
        "Repeating an explicit retired-target restoration replaces its bundle without duplicate contacts or IDs");
    retiredMerge.retireTarget(target,500,"fixture complete removal");
    check(!retiredMerge.stunned(target,500) && retiredMerge.stunned(renewed,500) &&
        retiredMerge.snapshot(500,42).at("contacts").size()==1 && retiredMerge.snapshot(500,42).at("sources").size()==1,
        "Complete entity retirement removes its ledger while preserving another target and their still-required shared source");
    retiredMerge.retireTarget(renewed,500,"fixture roster replacement");
    check(retiredMerge.snapshot(500,42).at("contacts").empty() && retiredMerge.snapshot(500,42).at("sources").empty() &&
        retiredMerge.snapshot(500,42).at("instance_ids").at("next")==3,
        "Retiring the final target releases source dependencies without resetting the global ID watermark");
    retiredMerge.mergeTarget(bundle,other,renewed,500,42,resolve,mergeLive);
    retiredMerge.retireTarget(renewed,500,"fixture second roster replacement");
    const auto nextIncarnation=registry.create();
    retiredMerge.mergeTarget(bundle,other,nextIncarnation,500,42,resolve,[&](EntityHandle h){return h==nextIncarnation;});
    check(retiredMerge.instance(nextIncarnation,500)->id==2 && retiredMerge.snapshot(500,42).at("contacts").size()==1,
        "Repeated room roster replacement retires the previous remapped ledger before importing the original bundle into a newer handle");
    StatusHost rooms("status-fixture",policy);Pcg32 roomRandom;
    a=rooms.prepare(request,100,roomRandom);rooms.publish(std::move(a),roomRandom);
    const auto roomA=rooms.snapshotTarget(target,350,42);rooms.clearAll(350,"fixture leave room A");
    a=rooms.prepare(second,500,roomRandom);rooms.publish(std::move(a),roomRandom);
    rooms.mergeTarget(roomA,target,renewed,600,42,resolve,[&](EntityHandle h){return h==other || h==renewed;});
    auto roomNext=statusRequest(sure,owner,renewed,9);a=rooms.prepare(roomNext,700,roomRandom);rooms.publish(std::move(a),roomRandom);
    check(rooms.instance(other,700)->id==2 && rooms.instance(renewed,700)->id==3 &&
        rooms.snapshot(700,42).at("instance_ids").at("next")==4,
        "Room A instance1, room B instance2 and the restored-room next instance3 share a never-decreasing global watermark");
    auto emptyBundle=savedHost.snapshotTarget(renewed,350,42);
    merged.mergeTarget(emptyBundle,renewed,renewed,5000,42,resolve,mergeLive);
    check(!merged.stunned(renewed,5000) && merged.snapshot(5000,42).at("contacts").size()==1 &&
        merged.snapshot(5000,42).at("instance_ids").at("next")==3,
        "An explicit empty target bundle clears only that target while preserving other contacts and monotonic IDs");
    samples["application"]=receipt;samples["target_bundle"]=bundle;
    std::vector<uint64_t> expectedTicks;
    for(const int fps:{30,60,120,144,240}) {
        FixedStepClock clock;StatusHost timed("status-fixture",policy);Pcg32 timedRandom;
        auto staged=timed.prepare(request,0,timedRandom);timed.publish(std::move(staged),timedRandom);
        std::vector<uint64_t> activeTicks;int64_t previous=0;
        for(int frame=1;frame<=fps*2;++frame) {
            const auto boundary=int64_t(frame)*2000000000/(fps*2);clock.addNanoseconds(boundary-previous);previous=boundary;
            while(const auto step=clock.popTick()) {timed.expire(step->milliseconds);if(timed.stunned(target,step->milliseconds)) activeTicks.push_back(step->tick);}
        }
        if(expectedTicks.empty()) expectedTicks=activeTicks;
        check(activeTicks==expectedTicks && activeTicks.size()==59 && !timed.stunned(target,clock.milliseconds()),
            "Fixed 60-Hz status duration is identical across render frame batches and exact boundary expiry");
    }
    return {{"status","pass"},{"checks",check.checks},{"count",check.checks.size()},{"samples",samples},
        {"classification","stun host inferred beta; World consumers, other statuses and frontend comparison are separate gates"}};
}
} // namespace dnf
