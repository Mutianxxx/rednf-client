#include "dnf/monster_event_ai.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *jenaMob="monster/newmonsters/heaven/jena/jena.mob";
const Json *eventAiTrace(const MonsterEventAiEvaluation &result,const std::string &kind) {
    for(const auto &entry:result.trace) if(entry.value("kind",std::string())==kind) return &entry;
    return nullptr;
}
} // namespace
Json runMonsterEventAiTests(Pvf &pvf) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Monster Event.ai: ")+message);checks.push_back(message);
    };
    const auto monster=pvf.script(jenaMob);
    const auto route=selectMonsterEventAi(pvf,monster,"easy");
    check(route.configured && route.ok && route.resolvedPath=="monster/newmonsters/heaven/jena/ai/event.ai",
        "Current Jena MOB selects its real first Event.ai path from the explicit easy difficulty row");
    const auto source=pvf.script(route.resolvedPath);
    check(route.operandSource.byteOffset==867 && route.operandSource.byteLength==5 &&
        route.operandSource.memberSha256==sha256(monster.rawBytes) && route.resolvedSource.memberSha256==sha256(source.rawBytes) &&
        route.fieldTokens.size()==5 && route.orderedAiFields.size()==12,
        "MOB route retains exact authored operand/tag refs, complete ordered difficulty paths and target member identity");
    for(const auto *difficulty:{"hard","medium","ultimate","hero"})
        check(selectMonsterEventAi(pvf,monster,difficulty).resolvedPath==route.resolvedPath,
            "All other authored Jena difficulty rows independently select the same exact source member");
    check(!selectMonsterEventAi(pvf,monster,"normal").ok && !selectMonsterEventAi(pvf,monster,"").ok,
        "Missing or absent difficulty never falls back to a different source AI row");
    const auto legacy=selectMonsterEventAi(pvf,pvf.script("monster/goblin/goblin.mob"),"easy");
    check(!legacy.configured && !legacy.ok,"A legacy MOB without an AI block does not invent an Event.ai program");
    auto foreign=monster;foreign.source["package_identity"]="foreign";
    check(!selectMonsterEventAi(pvf,foreign,"easy").ok,"Foreign MOB identity rejects Event.ai routing");
    const auto policy=MonsterEventAiPolicy::inferredIntegralChanceV1();
    const auto compiled=compileMonsterEventAi(pvf,source,policy);
    check(compiled.ok && compiled.program && compiled.program->sourceScript().rawBytes==source.rawBytes &&
        compiled.program->sourceScript().tokens==source.tokens && compiled.program->retainedFields().size()==source.fields.size(),
        "The bounded compiler preserves the entire actual source document, ordered fields and original tokens");
    check(!compileMonsterEventAi(pvf,source).ok,"Event.ai execution requires an explicit named inference policy");
    MonsterEventAiContext context;context.owner={71,2};context.tick=17;
    Pcg32 random(19,3);const auto before=random.snapshot();int queried=0;
    const auto noHit=evaluateMonsterEventAi(*compiled.program,context,random,[&](EntityHandle,int)->std::optional<bool> {
        ++queried;return false;
    });
    check(noHit.ok && noHit.returnedActionIndex==-1 && noHit.candidateRandom->snapshot()==before && random.snapshot()==before &&
        !eventAiTrace(noHit,"chance") && queried==0,
        "Without a typed accepted hit, authored hitfalse returns no action without chance draws or cooldown queries");
    context.acceptedHit=MonsterAcceptedHit{91,{5,1}};
    std::optional<Pcg32> passing,failing;MonsterEventAiEvaluation selected,notSelected;
    for(uint64_t seed=0;seed<256 && (!passing || !failing);++seed) {
        Pcg32 candidate(seed,3);
        const auto result=evaluateMonsterEventAi(*compiled.program,context,candidate,[&](EntityHandle owner,int index)->std::optional<bool> {
            if(owner!=context.owner || index!=4) throw std::runtime_error("Unexpected source cooldown query");return false;
        });
        check(result.ok && candidate.snapshot()==result.randomBefore,"Pure Event.ai evaluation never changes its supplied RNG");
        if(result.returnedActionIndex==4 && !passing) {passing=candidate;selected=result;}
        if(result.returnedActionIndex==-1 && !failing) {failing=candidate;notSelected=result;}
    }
    check(passing.has_value() && failing.has_value(),"Bounded diagnostic seeds reach both real authored30/100 chance outcomes");
    const auto *chance=eventAiTrace(selected,"chance"),*hit=eventAiTrace(selected,"hit");
    check(chance && chance->at("numerator")==30 && chance->at("denominator")==100 && chance->at("sample")<30 &&
        hit && hit->at("accepted_event")==91 && hit->at("attacker")==context.acceptedHit->attacker.json() &&
        selected.returnSource->byteOffset==97 && selected.returnSource->memberSha256==sha256(source.rawBytes),
        "A selected real source return retains accepted-event identity, exact source ratio, sample and authored return offset");
    check(!eventAiTrace(notSelected,"cooldown") && notSelected.candidateRandom->snapshot()!=notSelected.randomBefore,
        "A failed chance still prepares its single consumed sample while skipping the unreachable cooldown query");
    const auto inCd=evaluateMonsterEventAi(*compiled.program,context,*passing,[](EntityHandle,int)->std::optional<bool>{return true;});
    check(inCd.ok && inCd.returnedActionIndex==-1 && eventAiTrace(inCd,"cooldown") &&
        eventAiTrace(inCd,"cooldown")->at("result")==true && inCd.candidateRandom->snapshot()==selected.candidateRandom->snapshot(),
        "An authored in-cooldown result returns no action after exactly the same source chance draw");
    for(int failure=0;failure<3;++failure) {
        MonsterEventCooldownQuery query;
        if(failure==1) query=[](EntityHandle,int)->std::optional<bool>{return std::nullopt;};
        if(failure==2) query=[](EntityHandle,int)->std::optional<bool>{throw std::runtime_error("diagnostic cooldown fault");};
        const auto rejected=evaluateMonsterEventAi(*compiled.program,context,*passing,query);
        check(!rejected.ok && !rejected.candidateRandom && !rejected.returnedActionIndex && passing->snapshot()==selected.randomBefore,
            "Missing, invalid-index and faulting cooldown consumers expose no RNG/result candidate after a reached chance draw");
    }
    auto invalid=context;invalid.owner={};
    check(!evaluateMonsterEventAi(*compiled.program,invalid,*passing,{}).ok,"A missing current actor identity rejects AI evaluation");
    invalid=context;invalid.acceptedHit->attacker={};
    check(!evaluateMonsterEventAi(*compiled.program,invalid,*passing,{}).ok,"A typed hit with a missing attacker rejects before any random draw");
    auto limits=MonsterEventAiLimits{};limits.maxEvaluationSteps=1;
    const auto bounded=compileMonsterEventAi(pvf,source,policy,limits);
    check(bounded.ok && bool(bounded.program),"A valid source compiles before the evaluation-step budget is exercised");
    const auto stepFault=evaluateMonsterEventAi(*bounded.program,context,*passing,[](EntityHandle,int)->std::optional<bool>{return false;});
    check(bounded.ok && !stepFault.ok && !stepFault.candidateRandom,"The evaluation-step budget rejects without publishing a partial result");
    limits=MonsterEventAiLimits{};limits.maxRandomDraws=1;
    const auto drawBounded=compileMonsterEventAi(pvf,source,policy,limits);
    check(drawBounded.ok && bool(drawBounded.program),"A valid source compiles before the random-draw budget is exercised");
    Pcg32 zero;auto zeroState=zero.snapshot();zeroState["state"]=uint64_t(0);zeroState["increment"]=uint64_t(1);zeroState["draws"]=uint64_t(0);zero.restore(zeroState);
    const auto drawFault=evaluateMonsterEventAi(*drawBounded.program,context,zero,[](EntityHandle,int)->std::optional<bool>{return false;});
    check(!drawFault.ok && !drawFault.candidateRandom && zero.snapshot()==zeroState,
        "A deterministic rejected PCG sample exhausts the bounded rejection budget without altering live random state");
    auto exhaustedState=passing->snapshot();exhaustedState["draws"]=UINT64_MAX;Pcg32 exhausted;exhausted.restore(exhaustedState);
    const auto exhaustedFault=evaluateMonsterEventAi(*compiled.program,context,exhausted,[](EntityHandle,int)->std::optional<bool>{return false;});
    check(!exhaustedFault.ok && !exhaustedFault.candidateRandom && exhausted.snapshot()==exhaustedState,
        "An exhausted PCG draw counter fails closed without wrapping or preparing a candidate");
    auto noHitContext=context;noHitContext.acceptedHit.reset();
    check(evaluateMonsterEventAi(*compiled.program,noHitContext,exhausted,{}).ok,
        "An exhausted random stream does not reject an authored branch that reaches no random instruction");
    limits=MonsterEventAiLimits{};limits.maxNodes=1;
    const auto tooSmall=compileMonsterEventAi(pvf,source,policy,limits);
    check(!tooSmall.ok && tooSmall.diagnostics[0].at("ordered_fields").size()==source.fields.size(),
        "A node-budget compile failure retains all unconsumed and unreachable source fields in its diagnostic");
    check(!compileMonsterEventAi(pvf,pvf.script("monster/newmonsters/heaven/jena/ai/action.ai"),policy).ok,
        "Unsupported real Action.ai grammar cannot be silently reduced to the accepted Event.ai subset");
    auto tampered=source;tampered.fields[2].values[0]=0;
    check(!compileMonsterEventAi(pvf,tampered,policy).ok,"Decoded operands cannot diverge from their current source bytes and token identities");
    tampered=source;tampered.rawBytes[17]^=1;tampered.source["member_sha256"]=sha256(tampered.rawBytes);
    check(!compileMonsterEventAi(pvf,tampered,policy).ok,"Changing bytes and rehashing metadata cannot impersonate the current PVF member");
    RandomStreams streams(43),reference(43);
    streams.stream(RandomDomain::MonsterEventAi,context.owner.id).next();
    const auto savedStreams=streams.snapshot();RandomStreams restored;restored.restore(savedStreams);
    check(restored.snapshot()==savedStreams &&
        restored.stream(RandomDomain::MonsterEventAi,context.owner.id).next()==streams.stream(RandomDomain::MonsterEventAi,context.owner.id).next() &&
        streams.stream(RandomDomain::Ai,context.owner.id).next()==reference.stream(RandomDomain::Ai,context.owner.id).next() &&
        streams.stream(RandomDomain::Combat,context.owner.id).next()==reference.stream(RandomDomain::Combat,context.owner.id).next(),
        "The new Event.ai domain roundtrips exact PCG state and cannot collide with existing action-AI or combat streams using the same instance number");
    samples["route"]=route.json();samples["selected"]=selected.json();samples["chance_false"]=notSelected.json();samples["in_cd"]=inCd.json();
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Strict current-source Event.ai parser/evaluator and deterministic candidate RNG only; World accepted damage, scheduling, action binding, saves and complete AI are separate"}};
}
} // namespace dnf
