#include "dnf/skill_learning.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
CharacterSkillDefinition replaceLearningField(CharacterSkillDefinition definition, const std::string &tag,
    const Json &values, bool append = false) {
    if (!append) for (auto &entry:definition.fields) if (entry.scope=="common" && normalize(entry.field.tag)==normalize(tag)) {
        entry.field.values=values; return definition;
    }
    definition.fields.push_back({Field{tag,values,9000+definition.fields.size()},"common",definition.fields.size()});
    return definition;
}
CharacterSkillDefinition removeLearningField(CharacterSkillDefinition definition, const std::string &tag) {
    definition.fields.erase(std::remove_if(definition.fields.begin(),definition.fields.end(),[&](const auto &field) {
        return field.scope=="common" && normalize(field.field.tag)==normalize(tag);
    }),definition.fields.end()); return definition;
}
} // namespace

Json runSkillLearningTests(Pvf &pvf) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *name) {
        if (!okay) throw std::runtime_error(std::string("Skill learning: ")+name);
        checks.push_back(name);
    };
    CharacterCatalog catalog(pvf); SkillLearningService service(pvf,catalog);
    const auto sourceTable=pvf.read("etc/sptable.etc");
    const auto sourceChr=catalog.at(0).source.bytes;
    const auto sourceUpper=catalog.skillDefinition({0,46}).source.bytes;
    const auto runtime=[&](int id) {
        const auto &definition=catalog.skillDefinition({0,id});
        // A test host explicitly binds a consumer; this fixture never registers
        // an otherwise unimplemented source skill as playable in the game.
        return RuntimeSkillPolicy{{0,id},definition.kind,true,true,100};
    };
    CharacterSkillState empty({0,0,0}); const auto emptyBefore=empty.snapshot(1000);
    check(service.quote(empty,4,runtime(46),1,1000).gate==SkillLearningGate::Uninitialized,
        "Normal purchase rejects an uninitialized ledger");
    const auto initialized=service.prepareInitialization(empty,1,SkillInitializationMode::NewCharacter,1000);
    check(initialized.ok && empty.snapshot(1000)==emptyBefore && initialized.state.learnedLevel({0,5})==1 &&
        initialized.state.learnedLevel({0,46})==1 && initialized.state.learnedLevel({0,174})==1 &&
        initialized.state.learnedLevel({0,181})==2 && initialized.state.learnedLevel({0,179})==7 &&
        initialized.state.learnedLevel({0,8})==0 && initialized.state.learnedLevel({0,12})==0,
        "New initialization privately grants the exact CHR initial pairs and leaves other skills unlearned");
    auto normal=initialized.state;
    check(service.budget(normal,1,1000).earnedSp==0 && service.budget(normal,2,1000).earnedSp==30 &&
        service.budget(normal,3,1000).earnedSp==60 && service.budget(normal,5,1000).earnedSp==120 &&
        service.budget(normal,10,1000).earnedSp==270 && service.budget(normal,15,1000).earnedSp==570,
        "Earned normal SP sums the actual source level rows instead of fixed points per level");
    check(service.budget(normal,49,1000).earnedTp==0 && service.budget(normal,50,1000).earnedTp==1 &&
        service.budget(normal,99,1000).earnedTp==50 &&
        service.budget(normal,50,1000).trace[1]["classification"]=="inferred",
        "TP uses the explicitly classified server candidate with a separate normal balance");
    const auto initializedSnapshot=normal.snapshot(1000);
    const auto idempotent=service.prepareInitialization(normal,15,SkillInitializationMode::NewCharacter,1000);
    check(idempotent.ok && idempotent.replayed && idempotent.state.snapshot(1000)==initializedSnapshot,
        "Initialization with existing learning metadata validates and returns an identical ledger");
    check(service.quote(normal,3,runtime(46),2,1000).gate==SkillLearningGate::CharacterLevel &&
        service.quote(normal,4,runtime(46),2,1000).accepted() &&
        service.quote(normal,4,runtime(46),2,1000).requiredCharacterLevel==4,
        "Real UpperSlash level two requires character level four from source 1 plus range three");
    check(service.quote(normal,14,runtime(8),1,1000).gate==SkillLearningGate::CharacterLevel &&
        service.quote(normal,15,runtime(8),1,1000).accepted(),
        "Real TripleSlash learning opens exactly at the source character level");
    auto missing=runtime(46); missing.implemented=false;
    auto passive=runtime(12); passive.passiveConsumerBound=false;
    auto wrong=runtime(46); wrong.key.jobId=1;
    check(service.quote(normal,15,missing,2,1000).gate==SkillLearningGate::MissingImplementation &&
        service.quote(normal,15,passive,1,1000).gate==SkillLearningGate::PassiveHasNoConsumer &&
        !service.quote(normal,15,wrong,1,1000).accepted(),
        "Runtime implementation, passive consumer and actual job remain independent purchase gates");
    const SkillLearningRequest upper2{"purchase-upper-2",{0,46},0,2};
    const auto bought=service.prepare(normal,4,runtime(46),upper2,1000);
    check(bought.ok && !bought.replayed && bought.state.learnedLevel({0,46})==2 &&
        service.budget(bought.state,4,1000).spentSp==20 && service.budget(bought.state,4,1000).remainingSp==70 &&
        normal.snapshot(1000)==initializedSnapshot && bought.receipt["quote"]["cost"]==20,
        "A purchase privately publishes one learned level and actual source SP cost in one candidate");
    const auto boughtSnapshot=bought.state.snapshot(1000);
    const auto retried=service.prepare(bought.state,4,runtime(46),upper2,1000);
    check(retried.ok && retried.replayed && retried.receipt==bought.receipt &&
        retried.state.snapshot(1000)==boughtSnapshot && service.budget(retried.state,4,1000).spentSp==20,
        "Stable request replay returns the original receipt without spending or granting twice");
    auto conflicting=upper2; conflicting.targetLevel=3;
    const auto conflict=service.prepare(bought.state,7,runtime(46),conflicting,1000);
    check(!conflict.ok && conflict.quote.gate==SkillLearningGate::RequestConflict && conflict.state.snapshot(1000)==boughtSnapshot,
        "Reusing a request ID with different payload fails without changing the candidate");
    const auto stale=service.prepare(bought.state,7,runtime(46),{"upper-stale",{0,46},0,3},1000);
    check(!stale.ok && stale.quote.gate==SkillLearningGate::StaleRevision && stale.state.snapshot(1000)==boughtSnapshot,
        "A stale quote revision fails atomically");
    const auto skipped=service.prepare(bought.state,10,runtime(46),{"upper-skip",{0,46},1,4},1000);
    const auto noTarget=service.prepare(bought.state,7,runtime(46),{"upper-no-target",{0,46},1,0},1000);
    check(!skipped.ok && skipped.quote.gate==SkillLearningGate::InvalidLevel && !noTarget.ok &&
        noTarget.quote.gate==SkillLearningGate::InvalidRequest && noTarget.state.snapshot(1000)==boughtSnapshot,
        "Transactions require an explicit single-level target and never cycle or skip levels");
    check(service.useEligibility(bought.state,{0,46},3).gate==SkillLearningGate::TemporaryLevelIneligible &&
        service.useEligibility(bought.state,{0,46},4).allowed() && bought.state.snapshot(1000)==boughtSnapshot,
        "Lower effective character level blocks use while retaining normal purchases and levels");
    check(service.useEligibility(normal,{0,8},99).gate==SkillLearningGate::NotLearned,
        "A high effective character level does not grant unlearned skills");
    const auto boughtAgain=service.prepare(bought.state,7,runtime(46),{"purchase-upper-3",{0,46},1,3},1000);
    check(boughtAgain.ok && service.budget(boughtAgain.state,7,1000).spentSp==40 &&
        boughtAgain.state.snapshot(1000)["learning"]["purchases"][1]["cost"]==20,
        "Short source purchase vectors repeat their final cost and retain per-level history");
    auto learnedZero=CharacterSkillState({0,0,0}); learnedZero.setLearnedLevel({0,46},0);
    learnedZero.setLearnedLevel({0,1},1); learnedZero.setLearnedLevel({0,99999},7);
    auto legacyRoot=learnedZero.snapshot(1000); legacyRoot["future_root"]="preserved";
    legacyRoot["skills"][0]["future_skill"]=Json::array({1,2}); learnedZero.restore(legacyRoot,1000);
    const auto legacy=service.prepareInitialization(learnedZero,10,SkillInitializationMode::LegacyImport,1000);
    check(legacy.ok && legacy.state.learnedLevel({0,46})==0 && legacy.state.learnedLevel({0,99999})==7 &&
        legacy.state.snapshot(1000)["future_root"]=="preserved" &&
        legacy.state.snapshot(1000)["skills"][0]["future_skill"]==Json::array({1,2}) &&
        service.budget(legacy.state,10,1000).spentSp==0 && legacy.state.snapshot(1000)["learning"]["purchases"].empty(),
        "Legacy import preserves explicit zero, unknown keys and fields without inventing historical spending");
    check(service.quote(legacy.state,9,runtime(1),2,1000).gate==SkillLearningGate::CharacterLevel &&
        service.quote(legacy.state,10,runtime(1),2,1000).accepted(),
        "Real Guard level two requires level ten from source range five");
    const auto legacyReset=service.prepareReset(legacy.state,10,"legacy-reset",0,1000);
    check(legacyReset.ok && legacyReset.receipt["refunded_sp"]==0 && legacyReset.state.learnedLevel({0,1})==1 &&
        legacyReset.state.learnedLevel({0,99999})==7 && legacyReset.state.learnedLevel({0,46})==0,
        "Reset cannot turn legacy grants into refundable points or reapply initial gifts over explicit zero");
    const auto reset=service.prepareReset(boughtAgain.state,7,"reset-real-purchases",2,1000);
    check(reset.ok && reset.receipt["refunded_sp"]==40 && reset.receipt["refunded_tp"]==0 &&
        reset.state.learnedLevel({0,46})==1 && service.budget(reset.state,7,1000).spentSp==0 &&
        reset.state.snapshot(1000)["learning"]["purchases"].size()==2,
        "Reset refunds actual recorded purchase costs, preserves grants and keeps refund history");
    const auto resetRetry=service.prepareReset(reset.state,7,"reset-real-purchases",2,1000);
    check(resetRetry.ok && resetRetry.replayed && resetRetry.state.snapshot(1000)==reset.state.snapshot(1000),
        "Reset request replay cannot refund twice");
    const auto afterReset=service.prepare(reset.state,4,runtime(46),{"upper-after-reset",{0,46},3,2},1000);
    check(afterReset.ok && service.budget(afterReset.state,4,1000).spentSp==20 && afterReset.state.learnedLevel({0,46})==2,
        "Buying again after reset starts from the preserved grant and excludes refunded purchases");
    const Json rewardSource={{"kind","quest_reward"},{"quest_id",123},{"source_path","fixture/quest.etc"}};
    const auto reward=service.preparePointReward(normal,1,"quest-123-reward",0,25,2,rewardSource,1000);
    const auto rewardRetry=service.preparePointReward(reward.state,1,"quest-123-reward",0,25,2,rewardSource,1000);
    check(reward.ok && rewardRetry.ok && rewardRetry.replayed && service.budget(rewardRetry.state,1,1000).earnedSp==25 &&
        service.budget(rewardRetry.state,1,1000).earnedTp==2 && service.budget(normal,1,1000).earnedSp==0,
        "Stable external quest point events grant once without overwriting source level totals");
    const auto badReward=service.preparePointReward(reward.state,1,"quest-123-reward",0,26,2,rewardSource,1000);
    check(!badReward.ok && badReward.quote.gate==SkillLearningGate::RequestConflict &&
        badReward.state.snapshot(1000)==reward.state.snapshot(1000),
        "Point reward ID conflicts preserve the live ledger");
    check(service.quote(normal,50,runtime(140),1,1000).gate==SkillLearningGate::Prerequisite,
        "Real TP skill requires its authored prerequisite before spending any TP");
    CharacterSkillState tpImported({0,0,0}); tpImported.setLearnedLevel({0,20},10);
    const auto tpInitialized=service.prepareInitialization(tpImported,50,SkillInitializationMode::LegacyImport,1000);
    const auto tpQuote=service.quote(tpInitialized.state,50,runtime(140),1,1000);
    const auto tpBought=service.prepare(tpInitialized.state,50,runtime(140),{"tp-real-140",{0,140},0,1},1000);
    check(tpInitialized.ok && tpQuote.accepted() && tpQuote.currency=="TP" && tpQuote.cost==1 && tpBought.ok &&
        service.budget(tpBought.state,50,1000).spentTp==1 && service.budget(tpBought.state,50,1000).spentSp==0,
        "Real source TP purchase consumes its independent point pool after prerequisite checks");
    const auto guard=catalog.skillDefinition({0,1});
    const auto exact=replaceLearningField(guard,"[purchase cost]",Json::array({120}));
    const auto tooMuch=replaceLearningField(guard,"[purchase cost]",Json::array({121}));
    check(service.quoteDefinition(normal,5,runtime(1),exact,1,1000).accepted() &&
        service.quoteDefinition(normal,5,runtime(1),tooMuch,1,1000).gate==SkillLearningGate::InsufficientPoints,
        "Exact point balance succeeds and a one-point deficit fails without borrowing TP");
    auto discounted=replaceLearningField(exact,"[growtype fitness]",Json::array({30,0,0,0,0,0}));
    check(service.quoteDefinition(normal,5,runtime(1),discounted,1,1000).cost==84,
        "Explicit inferred SP fitness discount uses positive integer truncation on source cost");
    const auto oddPrereq=replaceLearningField(guard,"[pre required skill]",Json::array({46,1,5}));
    const auto repeated=replaceLearningField(guard,"[purchase cost]",Json::array({20}),true);
    const auto malformed=replaceLearningField(guard,"[purchase cost]",Json::array({20.0}));
    const auto explicitEmpty=replaceLearningField(guard,"[purchase cost]",Json::array());
    check(service.quoteDefinition(normal,15,runtime(1),oddPrereq,1,1000).gate==SkillLearningGate::SourceInvalid &&
        service.quoteDefinition(normal,15,runtime(1),repeated,1,1000).gate==SkillLearningGate::SourceInvalid &&
        service.quoteDefinition(normal,15,runtime(1),malformed,1,1000).gate==SkillLearningGate::SourceInvalid &&
        service.quoteDefinition(normal,15,runtime(1),explicitEmpty,1,1000).gate==SkillLearningGate::SourceInvalid &&
        normal.snapshot(1000)==initializedSnapshot,
        "Odd prerequisites, repeated, floating and explicitly empty costs are rejected without state mutation");
    const auto noCost=removeLearningField(guard,"[purchase cost]");
    const auto twoCosts=replaceLearningField(guard,"[special purchase cost]",Json::array({1}));
    const auto gsp=replaceLearningField(guard,"[purchase gsp]",Json::array({5}));
    check(service.quoteDefinition(normal,15,runtime(1),noCost,1,1000).gate==SkillLearningGate::SourceInvalid &&
        service.quoteDefinition(normal,15,runtime(1),twoCosts,1,1000).gate==SkillLearningGate::SourceInvalid &&
        service.quoteDefinition(normal,15,runtime(1),gsp,1,1000).gate==SkillLearningGate::SpecialQualification,
        "Missing or dual currency is not free learning; special GSP source requirements cannot use SP fallback");
    auto ceilingImported=CharacterSkillState({0,0,0}); ceilingImported.setLearnedLevel({0,46},10);
    const auto ceiling=service.prepareInitialization(ceilingImported,99,SkillInitializationMode::LegacyImport,1000);
    check(service.quote(ceiling.state,99,runtime(46),11,1000).gate==SkillLearningGate::InvalidLevel,
        "Purchase ceiling ten is enforced independently from UpperSlash all-means maximum fifty");
    auto tampered=bought.state.snapshot(1000); tampered["skills"][1]["level"]=999;
    CharacterSkillState damaged({0,0,0}); damaged.restore(tampered,1000);
    const auto invalid=service.prepareInitialization(damaged,4,SkillInitializationMode::LegacyImport,1000);
    check(!invalid.ok && invalid.quote.gate==SkillLearningGate::InvalidLedger && invalid.state.snapshot(1000)==tampered,
        "Existing learning metadata cannot silently migrate a contradictory learned-level array");
    auto mismatched=bought.state.snapshot(1000); mismatched["learning"]["package_identity"]="different-source";
    damaged.restore(mismatched,1000);
    check(service.quote(damaged,4,runtime(46),3,1000).gate==SkillLearningGate::SourceMismatch,
        "A different PVF source identity blocks purchases instead of reusing the old budget");
    bool tableRejected=false;
    auto badTable=pvf.script("etc/sptable.etc");
    for (auto &entry:badTable.fields) if (normalize(entry.tag)=="[sp table]") entry.values[2]=1;
    try { SkillLearningService invalidTable(catalog,badTable,pvf.identity()); } catch (const std::exception &) { tableRejected=true; }
    check(tableRejected,"A duplicate or shifted SP-table level is rejected instead of assigning points to wrong levels");
    tableRejected=false; badTable=pvf.script("etc/sptable.etc");
    badTable.fields.push_back(badTable.fields.front());
    try { SkillLearningService invalidTable(catalog,badTable,pvf.identity()); } catch (const std::exception &) { tableRejected=true; }
    check(tableRejected,"Ambiguous repeated SP tables are rejected");
    SkillLearningTestOverlay overlay;
    const auto testBuy=service.prepareTest(normal,overlay,4,runtime(46),{"test-upper-2",{0,46},0,2},1000);
    check(testBuy.ok && testBuy.overlay.spentSp==20 && testBuy.overlay.spentTp==0 &&
        testBuy.overlay.effectiveState(normal,1000).learnedLevel({0,46})==2 &&
        normal.snapshot(1000)==initializedSnapshot && service.budget(normal,1,1000).earnedSp==0 &&
        service.budget(normal,1,1000).spentSp==0,
        "Test purchase uses an isolated effective-level pool and overlay without granting normal points or levels");
    check(!testBuy.overlay.effectiveState(normal,1000).snapshot(1000).contains("learning") &&
        service.quote(testBuy.overlay.effectiveState(normal,1000),4,runtime(46),3,1000).gate==SkillLearningGate::Uninitialized,
        "An effective test view cannot accidentally spend against the normal learning ledger");
    const auto testRetry=service.prepareTest(normal,testBuy.overlay,4,runtime(46),{"test-upper-2",{0,46},0,2},1000);
    check(testRetry.ok && testRetry.replayed && testRetry.overlay.snapshot()==testBuy.overlay.snapshot(),
        "Independent test request replay cannot spend its test pool twice");
    check(service.quoteTest(normal,testBuy.overlay,1,runtime(5),2,1000).gate==SkillLearningGate::CharacterLevel &&
        service.quoteTest(normal,testBuy.overlay,1,runtime(1),1,1000).budget.remainingSp==-20,
        "Lowered test level retains the point conflict and does not refund or alter normal history");
    SkillLearningTestOverlay restoredOverlay; restoredOverlay.restore(testBuy.overlay.snapshot());
    check(restoredOverlay.snapshot()==testBuy.overlay.snapshot() &&
        restoredOverlay.effectiveState(normal,1000).learnedLevel({0,46})==2 &&
        SkillLearningTestOverlay{}.effectiveState(normal,1000).learnedLevel({0,46})==1,
        "Test overlay round-trip is isolated and clearing it recovers the normal learned level");
    check(service.quoteTest(bought.state,testBuy.overlay,7,runtime(46),3,1000).gate==SkillLearningGate::StaleRevision,
        "Normal skill changes invalidate a bound test overlay until explicitly reset");
    auto cooldownNormal=normal; cooldownNormal.startCooldown({0,46},1000,500);
    check(service.quoteTest(cooldownNormal,testBuy.overlay,7,runtime(46),3,1000).accepted(),
        "Normal cooldown passage or updates do not change the test overlay learning fingerprint");
    cooldownNormal.startCooldown({0,8},1000,500);
    check(service.quoteTest(cooldownNormal,testBuy.overlay,7,runtime(46),3,1000).accepted() &&
        restoredOverlay.effectiveState(cooldownNormal,2000).learnedLevel({0,46})==2,
        "First cooldown of a test-only skill may add an unlearned normal row without invalidating learning");
    auto legacyOverlay=testBuy.overlay;
    auto legacySnapshot=cooldownNormal.snapshot(1000);
    for (auto &record:legacySnapshot["skills"]) record.erase("remaining_cooldown_ms");
    const auto legacyBytes=legacySnapshot.dump();
    legacyOverlay.normalFingerprint=sha256(Bytes(legacyBytes.begin(),legacyBytes.end()));
    legacyOverlay.upgradeNormalBinding(cooldownNormal,1000);
    cooldownNormal.startCooldown({0,20},1000,500);
    check(legacyOverlay.normalFingerprint.rfind("learning-v2:",0)==0 &&
        legacyOverlay.effectiveState(cooldownNormal,1000).learnedLevel({0,46})==2,
        "Precisely matched legacy binding migrates before another cooldown-only row is added");
    const auto rejectsChanged=[&](Json changed,const char *name) {
        CharacterSkillState altered(normal.identity()); altered.restore(changed,1000);
        bool rejected=false;
        try { legacyOverlay.effectiveState(altered,1000); } catch(const std::exception &) { rejected=true; }
        check(rejected,name);
    };
    auto changed=cooldownNormal.snapshot(1000);
    for(auto &record:changed["skills"]) if(record["key"]["skill_id"]==8) record["future_runtime_field"]=1;
    rejectsChanged(changed,"Unknown fields on zero-level rows remain protected by the learning binding");
    changed=cooldownNormal.snapshot(1000);
    for(auto &record:changed["skills"]) if(record["key"]["skill_id"]==8) record["key"]["future_key_field"]=1;
    rejectsChanged(changed,"Unknown zero-level key fields are not silently normalized away");
    changed=cooldownNormal.snapshot(1000); changed["learning"]["future_learning_field"]=1;
    rejectsChanged(changed,"Learning metadata changes still invalidate the isolated test overlay");
    changed=cooldownNormal.snapshot(1000); changed["identity"]["future_identity_field"]=1;
    rejectsChanged(changed,"Unknown identity fields remain part of the binding");
    changed=cooldownNormal.snapshot(1000); changed["future_root_field"]=1;
    rejectsChanged(changed,"Unknown root fields remain part of the binding");
    auto invalidOverlay=testBuy.overlay.snapshot(); invalidOverlay["spent_sp"]=0;
    const auto overlayBefore=restoredOverlay.snapshot(); bool overlayRejected=false;
    try { restoredOverlay.restore(invalidOverlay); } catch (const std::exception &) { overlayRejected=true; }
    check(overlayRejected && restoredOverlay.snapshot()==overlayBefore,
        "Test overlay restore rejects point/history conflicts atomically");
    check(pvf.read("etc/sptable.etc")==sourceTable && pvf.read(catalog.at(0).source.script.path)==sourceChr &&
        pvf.read(catalog.skillDefinition({0,46}).source.script.path)==sourceUpper,
        "Learning, migration, reset and test transactions never modify source PVF bytes");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},
        {"classification","inferred executable learning policy, source-derived costs and level gates"},
        {"sp_table_sha256",sha256(sourceTable)},{"character_sha256",sha256(sourceChr)},
        {"scope","Pure service tests do not register new combat controllers or constitute normal UI acceptance"}};
}
} // namespace dnf
