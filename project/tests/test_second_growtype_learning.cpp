// Regression for independent current1031 ordinary/awakening qualification.
// Uses actual current1031 source/service and actual runtime rebase consumers.
// Explicit service policies and imported prerequisite rows are diagnostic
// fixtures, never production controller admission or fabricated paid learning.
#include "dnf/skill_learning.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/character_advancement.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
CharacterSkillDefinition setSecondField(CharacterSkillDefinition definition,const std::string &tag,const Json &values) {
    for(auto &field:definition.fields)if(field.scope=="common"&&normalize(field.field.tag)==normalize(tag)) {
        field.field.values=values;return definition;
    }
    definition.fields.push_back({Field{tag,values,9000+definition.fields.size()},"common",definition.fields.size()});
    return definition;
}
CharacterSkillDefinition eraseSecondField(CharacterSkillDefinition definition,const std::string &tag) {
    definition.fields.erase(std::remove_if(definition.fields.begin(),definition.fields.end(),[&](const auto &field) {
        return field.scope=="common"&&normalize(field.field.tag)==normalize(tag);
    }),definition.fields.end());return definition;
}
CharacterSkillState secondLedger(const SkillLearningService &service,const CharacterSkillDefinition &definition,
                                CharacterIdentity identity) {
    CharacterSkillState state(identity);
    for(const auto *field:definition.fieldsInScope("[pre required skill]","common"))
        for(size_t i=0;i+1<field->field.values.size();i+=2)
            state.setLearnedLevel({identity.jobId,field->field.values.at(i).get<int>()},field->field.values.at(i+1).get<int>());
    auto prepared=service.prepareInitialization(state,99,SkillInitializationMode::LegacyImport);
    if(!prepared.ok)throw std::runtime_error("Explicit imported service fixture: "+prepared.quote.error);
    return prepared.state;
}
}
Json runSecondGrowtypeLearningTests(Pvf &pvf,Assets &assets) {
    CharacterCatalog catalog(pvf);SkillLearningService service(pvf,catalog);
    Json checks=Json::array(),evidence=Json::array();
    const auto require=[&](bool okay,const char *message) {
        if(!okay)throw std::runtime_error(message);checks.push_back(message);
    };
    const std::array<std::pair<int,int>,4> cases{{{96,3},{97,2},{98,4},{100,1}}};
    for(const auto &[id,branch]:cases) {
        const SkillKey key{5,id};const CharacterIdentity identity{5,branch,1};
        const auto &definition=catalog.skillDefinition(key);const auto original=definition.source.bytes;
        const auto fitness=definition.fieldsInScope("[skill fitness growtype]","common");
        require(fitness.size()==1&&fitness.front()->field.values.empty(),
            "Actual current1031 awakening-only source has a present legal empty ordinary fitness field");
        const auto ledger=secondLedger(service,definition,identity);
        const auto before=ledger.snapshot(0);const auto budget=service.budget(ledger,99).json();
        const RuntimeSkillPolicy fixture{key,definition.kind,true,false,100};
        const auto quote=service.quote(ledger,99,fixture,1);
        require(quote.accepted()&&quote.purchaseMaximum==30&&quote.requiredCharacterLevel==50,
            "Actual source service selects second-growtype branch, level50 and purchase maximum30");
        require(service.sourceUseEligibility(identity,key,1,50).allowed()&&
            service.sourceUseEligibility(identity,key,1,49).gate==SkillLearningGate::TemporaryLevelIneligible,
            "Actual use service shares second-table identity semantics and exact character-level floor");
        require(service.useEligibility(ledger,key,99).gate==SkillLearningGate::NotLearned,
            "Source-qualified configured preview does not grant normal learned eligibility");
        for(int other=0;other<=4;++other)if(other!=branch)require(
            service.sourceUseEligibility({5,other,1},key,1,99).gate==SkillLearningGate::SourceExcluded,
            "Every nonmatching actual source branch remains explicitly excluded");
        require(service.sourceUseEligibility({5,branch,0},key,1,99).gate==SkillLearningGate::SourceExcluded&&
            service.sourceUseEligibility({5,branch,2},key,1,99).gate==SkillLearningGate::SourceExcluded&&
            service.sourceUseEligibility({5,branch,3},key,1,99).gate==SkillLearningGate::SourceExcluded,
            "Base and nonauthored awakening stages cannot inherit a different source column");
        auto disabled=fixture;disabled.implemented=false;
        require(service.quote(ledger,99,disabled,1).gate==SkillLearningGate::MissingImplementation&&
            ledger.snapshot(0)==before&&service.budget(ledger,99).json()==budget,
            "Source qualification change never bypasses real runtime implementation or spends a normal budget");
        const auto odd=setSecondField(definition,"[second growtype maximum level]",Json::array({0,0,30}));
        const auto shortRows=setSecondField(definition,"[second growtype maximum level]",Json::array({0,30}));
        const auto missing=eraseSecondField(definition,"[skill fitness second growtype]");
        const auto noOrdinary=eraseSecondField(definition,"[skill fitness growtype]");
        const auto emptyStages=setSecondField(definition,"[skill fitness second growtype]",Json::array());
        const auto malformed=setSecondField(definition,"[skill fitness second growtype]",Json::array({1.5}));
        const auto unknown=setSecondField(definition,"[skill fitness second growtype]",Json::array({3}));
        const auto repeated=setSecondField(definition,"[skill fitness second growtype]",Json::array({1,1}));
        auto duplicatedField=definition;
        for(const auto &field:definition.fields)if(field.scope=="common"&&normalize(field.field.tag)=="[skill fitness second growtype]") {
            duplicatedField.fields.push_back(field);break;
        }
        require(service.quoteDefinition(ledger,99,fixture,odd,1).gate==SkillLearningGate::SourceInvalid&&
            service.quoteDefinition(ledger,99,fixture,shortRows,1).gate==SkillLearningGate::SourceInvalid&&
            service.quoteDefinition(ledger,99,fixture,missing,1).gate==SkillLearningGate::SourceInvalid,
            "Odd, unknown short and incomplete secondary qualification fields diagnose invalid source rather than guessing admission");
        require(service.quoteDefinition(ledger,99,fixture,noOrdinary,1).accepted(),
            "Absent ordinary fitness grants no ordinary dimension but does not block an explicit valid secondary source dimension");
        require(service.quoteDefinition(ledger,99,fixture,emptyStages,1).gate==SkillLearningGate::SourceExcluded&&
            service.quoteDefinition(ledger,99,fixture,malformed,1).gate==SkillLearningGate::SourceInvalid&&
            service.quoteDefinition(ledger,99,fixture,unknown,1).gate==SkillLearningGate::SourceInvalid&&
            service.quoteDefinition(ledger,99,fixture,repeated,1).gate==SkillLearningGate::SourceInvalid&&
            service.quoteDefinition(ledger,99,fixture,duplicatedField,1).gate==SkillLearningGate::SourceInvalid,
            "Empty second fitness explicitly excludes, while noninteger, unknown, duplicate stages and duplicate fields diagnose malformed source");
        const auto outside=secondLedger(service,definition,{5,6,1});
        require(service.quote(outside,99,fixture,1).gate==SkillLearningGate::SourceInvalid,
            "Actual service checks ordinary row bounds before second-table indexing");
        require(ledger.snapshot(0)==before&&pvf.read(definition.source.script.path)==original,
            "Pure source/service inspection keeps the ledger and original PVF member byte-exact");
        evidence.push_back({{"key",key.json()},{"identity",identity.json()},{"quote",quote.json()},
            {"use",service.sourceUseEligibility(identity,key,1,50).json()},{"source_sha256",sha256(original)}});
    }
    // Actual full-registry counterexample to required ordinary fitness:
    // job3 skill111 lacks that field entirely, with secondary branch1 max30.
    const SkillKey iceKey{3,111};
    const auto &ice=catalog.skillDefinition(iceKey);
    require(ice.source.script.path=="skill/mage/walloficeex.skl"&&
        sha256(ice.source.bytes)=="eea10aa5e0656a617e79c84fc062d48a34222c4070a75dd97960c4a3e2e705ec"&&
        ice.fieldsInScope("[skill fitness growtype]","common").empty(),
        "Actual current1031 registered WallOfIceEx bytes have no ordinary fitness field");
    const CharacterIdentity iceIdentity{3,1,1};
    const auto iceLedger=secondLedger(service,ice,iceIdentity);
    const auto iceBefore=iceLedger.snapshot(0);
    const RuntimeSkillPolicy iceFixture{iceKey,ice.kind,true,false,100};
    const auto iceQuote=service.quote(iceLedger,60,iceFixture,1);
    require(iceQuote.accepted()&&iceQuote.requiredCharacterLevel==60&&iceQuote.purchaseMaximum==30&&
        iceQuote.cost==60&&service.sourceUseEligibility(iceIdentity,iceKey,1,60).allowed(),
        "Actual WallOfIceEx quote and use select legal secondary branch1 at source level60 and SP60");
    require(service.quote(iceLedger,59,iceFixture,1).gate==SkillLearningGate::CharacterLevel&&
        service.sourceUseEligibility(iceIdentity,iceKey,1,59).gate==SkillLearningGate::TemporaryLevelIneligible,
        "Actual WallOfIceEx rejects normal quote and configured use one level below its source requirement");
    for(int branch=0;branch<=4;++branch)if(branch!=1) {
        const auto wrong=secondLedger(service,ice,{3,branch,1});
        require(service.quote(wrong,99,iceFixture,1).gate==SkillLearningGate::SourceExcluded&&
            service.sourceUseEligibility({3,branch,1},iceKey,1,99).gate==SkillLearningGate::SourceExcluded,
            "Actual WallOfIceEx excludes each wrong source branch in both quote and use");
    }
    for(int stage:{0,2,3}) {
        const auto wrong=secondLedger(service,ice,{3,1,stage});
        require(service.quote(wrong,99,iceFixture,1).gate==SkillLearningGate::SourceExcluded&&
            service.sourceUseEligibility({3,1,stage},iceKey,1,99).gate==SkillLearningGate::SourceExcluded,
            "Actual WallOfIceEx excludes base, nonauthored second and unknown awakening stages in quote and use");
    }
    require(service.useEligibility(iceLedger,iceKey,99).gate==SkillLearningGate::NotLearned&&
        iceLedger.snapshot(0)==iceBefore,
        "Actual secondary source qualification cannot fabricate WallOfIceEx normal learning or point history");
    const auto noMax=eraseSecondField(ice,"[growtype maximum level]");
    require(service.quoteDefinition(iceLedger,60,iceFixture,noMax,1).gate==SkillLearningGate::SourceInvalid,
        "A valid secondary pair cannot silently supply a missing required ordinary maximum table");
    evidence.push_back({{"key",iceKey.json()},{"identity",iceIdentity.json()},
        {"quote",iceQuote.json()},{"source_sha256",sha256(ice.source.bytes)}});

    // Real registered negative: empty fitness still excludes ordinary even
    // when the source max table happens to contain positive base value30.
    const SkillKey dormantKey{9,85};
    const auto &dormant=catalog.skillDefinition(dormantKey);
    const auto dormantFitness=dormant.fieldsInScope("[skill fitness growtype]","common");
    const auto dormantMaximum=dormant.fieldsInScope("[growtype maximum level]","common");
    require(dormant.source.script.path=="skill/demonicswordman/notapplicable/hellbenter.skl"&&
        dormantFitness.size()==1&&dormantFitness.front()->field.values.empty()&&
        dormantMaximum.size()==1&&dormantMaximum.front()->field.values.at(0)==30,
        "Actual DemonicSwordman HellBenter source contains positive base maximum30 but empty ordinary fitness");
    const RuntimeSkillPolicy dormantFixture{dormantKey,dormant.kind,true,true,100};
    for(int branch=0;branch<=4;++branch) {
        const auto state=secondLedger(service,dormant,{9,branch,0});
        require(service.quote(state,99,dormantFixture,1).gate==SkillLearningGate::SourceExcluded&&
            service.sourceUseEligibility({9,branch,0},dormantKey,1,99).gate==SkillLearningGate::SourceExcluded,
            "Actual HellBenter base and every unawakened branch remain excluded despite positive ordinary maximum");
    }

    // Ordinary source qualification must survive awakening without requiring
    // an otherwise absent secondary field, and mixed zero rows must not make
    // an independently excluded ordinary branch eligible.
    const auto &ordinary=catalog.skillDefinition({5,4});
    const auto normal=secondLedger(service,ordinary,{5,3,1});
    const RuntimeSkillPolicy ordinaryFixture{{5,4},ordinary.kind,true,false,100};
    require(service.quote(normal,99,ordinaryFixture,1).accepted()&&
        service.sourceUseEligibility({5,3,1},{5,4},1,99).allowed(),
        "Actual ordinary source remains available to a legal awakened identity when no secondary restriction is authored");
    const auto missingOrdinary=eraseSecondField(ordinary,"[skill fitness growtype]");
    require(service.quoteDefinition(normal,99,ordinaryFixture,missingOrdinary,1).gate==SkillLearningGate::SourceInvalid,
        "Missing ordinary fitness without any authored secondary pair remains an explicit source error");
    auto mixed=setSecondField(ordinary,"[second growtype maximum level]",Json::array({0,0,0,0,0,0,0,0,0,0,0,0}));
    mixed=setSecondField(mixed,"[skill fitness second growtype]",Json::array({1}));
    require(service.quoteDefinition(normal,99,ordinaryFixture,mixed,1).accepted(),
        "Synthetic zero secondary column falls back only to an independently qualified ordinary source row");
    mixed=setSecondField(mixed,"[skill fitness growtype]",Json::array());
    require(service.quoteDefinition(normal,99,ordinaryFixture,mixed,1).gate==SkillLearningGate::SourceExcluded,
        "Synthetic mixed table cannot turn an empty ordinary fitness into an unrestricted fallback");

    // Real rebase consumer is deliberately exercised with a source-preview
    // configuration, not a normal learned grant. This ensures the GSD reader
    // sees the same eligibility result without admitting a production skill.
    CharacterAdvancementCatalog advancement(pvf,catalog);
    auto base=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0}));
    ExperimentalCharacterRuntime preview(base);
    preview.configuration().configureFemaleGunnerSourceSkill({5,96},1,*base);
    preview.configuration().assignSlot(0,SkillKey{5,96},*base);
    const auto baseSnapshot=preview.configuration().snapshot();
    auto mechanical=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,catalog,{5,3,1},&advancement));
    auto matched=preview.rebasedForIdentity(mechanical,service,50);
    const auto *kept=matched.configuration().binding({5,96});
    require(kept&&kept->level==1&&preview.configuration().snapshot()==baseSnapshot,
        "Actual runtime rebase preserves source-qualified G0 preview privately and leaves the original identity/configuration unchanged");
    auto ranger=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,catalog,{5,1,1},&advancement));
    auto rejected=preview.rebasedForIdentity(ranger,service,50);
    require(!rejected.configuration().binding({5,96})&&rejected.configuration().snapshot().contains("advancement_disabled_bindings"),
        "Actual runtime rebase removes wrong-branch G0 from usable bindings and retains its disabled source record");
    auto tooLow=preview.rebasedForIdentity(mechanical,service,49);
    require(!tooLow.configuration().binding({5,96}),"Actual runtime rebase uses the same source character-level floor as use eligibility");
    return {{"status","pass"},{"checks",checks},{"source_evidence",evidence},
        {"classification","current1031 source regression with inferred table selection; explicit diagnostic runtime policies do not admit game controllers"},
        {"scope","Actual current1031 SKL/service and runtime identity rebase; synthetic malformed sources explicitly labeled; no normal SP grants or native parity claim"}};
}
} // namespace dnf
