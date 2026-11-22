#include "dnf/attack_status.hpp"
#include "dnf/damage_resolution.hpp"
#include <stdexcept>

namespace dnf {
namespace {
// Explicit decoded fixtures exercise rejected near misses; they do not encode
// native PVF bytes and are never used by the runtime content loader.
Script dormantFixture(const std::string &tag,const Json &payload,bool inlineEnum=false) {
    Script source;source.path="fixture/dormant-status.atk";
    Json operands=Json::array({tag});for(const auto &v:payload) operands.push_back(v);
    if(inlineEnum) source.fields={{"[active status]",operands,0}};
    else source.fields={{"[active status]",Json::array(),0},{tag,payload,0}};
    size_t end=2;Json fields=Json::array();
    for(auto &field:source.fields) {field.offset=end;end+=5*(1+field.values.size());fields.push_back({field.tag,field.values});}
    const auto encoded=fields.dump();source.rawBytes.assign(end,0);
    for(size_t i=2;i<end;++i) source.rawBytes[i]=uint8_t(encoded[(i-2)%encoded.size()]);
    source.source={{"package_identity","dormant-fixture"},{"literal_path",source.path},{"member_sha256",sha256(source.rawBytes)}};
    source.tokens=Json::array({{{"fixture_decoded_fields",fields}}});return source;
}
bool dormantDiagnostic(const AttackStatusEntry &entry) {
    for(const auto &diagnostic:entry.diagnostics)
        if(diagnostic.value("kind",std::string())=="zero_probability_dormant_source_status" &&
           diagnostic.value("severity",std::string())=="info" && diagnostic.at("tag")==entry.tag &&
           diagnostic.at("complete_payload")==entry.rawPayload) return true;
    return false;
}
} // namespace

Json runAttackStatusDormantTests(Pvf &pvf,Assets &) {
    Json checks=Json::array(),samples=Json::array();
    const auto check=[&](bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Dormant attack status: ")+message);
        checks.push_back(message);
    };
    struct AuthoredDormant {const char *path,*tag,*hash;size_t activeOffset,typeOffset;};
    const AuthoredDormant authored[]={
        {"character/gunner/atattackinfo/fastknee.atk","[stun]",
         "8f6257a087cc32d349087461d03ad33f87a2835c7ebe6dd1821eb0a9ec17bd67",127,132},
        {"character/gunner/attackinfo/fastknee.atk","[stun]",
         "8f6257a087cc32d349087461d03ad33f87a2835c7ebe6dd1821eb0a9ec17bd67",127,132},
        {"character/gunner/atattackinfo/airraidex.atk","[burn]",
         "81f4dc6821176607818bfe069f11b5684ae2da7d61069ef67ebff5c3afe6e9bd",97,102},
        {"passiveobject/character/gunner/attackinfo/flashmineexbomb.atk","[stun]",
         "bbb309406b25211023e5e92ded494fec562d4fc0e7138228ec2291b85e02478d",97,102}};
    auto damagePolicy=DamageResolutionPolicy::inferredPveDamageV1(pvf.script("etc/etcparameter.etc"));
    damagePolicy.rollHit=false;damagePolicy.rollCritical=false;damagePolicy.randomVariation=false;
    uint64_t attackInstance=41;
    for(const auto &expected:authored) {
        const auto source=pvf.script(expected.path);const auto parsed=readAttackStatuses(source);
        check(parsed.usable() && parsed.entries.size()==1,"Actual 1031 dormant attack parses as a usable source without dropping its entry");
        const auto &entry=parsed.entries[0];
        check(entry.kind==AttackStatusKind::None && entry.tag==expected.tag && entry.runtime &&
              entry.rawPayload==Json::array({0,0,0}) && entry.chancePercent==0 && entry.level==0 && entry.durationMs==0 &&
              dormantDiagnostic(entry),"Exact integer zero triple retains authored type and gains an explicit informational no-effect diagnosis");
        check(entry.sources.size()==2 && entry.sources[0].byteOffset==expected.activeOffset &&
              entry.sources[1].byteOffset==expected.typeOffset && entry.sources[0].memberSha256==expected.hash &&
              entry.sources[1].memberSha256==expected.hash && entry.sources[0].byteLength==5 && entry.sources[1].byteLength==20,
              "Dormant compatibility preserves both original ATK spans, field lengths and member hash");
        const auto full=parsed.snapshot(true);
        check(parsed.source.rawBytes==pvf.read(expected.path) && full.at("document").at("tokens")==source.tokens &&
              full.at("document").at("raw_bytes")==source.rawBytes && full.at("entries")[0].at("tag")==expected.tag &&
              full.at("entries")[0].at("raw_payload")==Json::array({0,0,0}),
              "Complete raw bytes, tokens, payload and provenance remain available in the dormant source snapshot");
        check(!readAttackDamage(source).usable(),"Pure damage still requires an explicitly registered status consumer for authored non-none status tags");
        const auto attack=readAttackDamage(source,AttackStatusConsumer::StunHostV1);
        check(attack.usable() && attack.source.rawBytes==source.rawBytes && attack.source.tokens==source.tokens,
              "Registered status host allows the original dormant ATK through the actual damage reader without rewriting source fields");
        bool delegated=false;
        for(const auto &stage:attack.trace) if(stage.value("stage",std::string())=="delegated_attack_status" &&
            stage.at("statuses")==parsed.snapshot()) delegated=true;
        check(delegated,"Damage trace contains the complete delegated no-active-status source result");

        const auto package=source.source.at("package_identity").get<std::string>();
        StatusRequest request;request.attacker={1,1};request.attackerLevel=20;request.target.handle={2,1};
        request.target.resistance.packageIdentity=package;request.target.resistance.level=20;
        request.attackInstance=attackInstance++;request.attack=parsed;
        StatusHost host(package,StunStatusPolicy::inferredFlatChanceStunV1());Pcg32 random(19,13);
        const auto randomBefore=random.snapshot(),idsBefore=host.instanceWatermark();
        auto prepared=host.prepare(request,1000,random);
        check(prepared.ready() && prepared.receipt.at("outcomes").empty() && host.canPublish(prepared,random) &&
              !host.stunned(request.target.handle,1000) && random.snapshot()==randomBefore,
              "No-effect source prepares through StatusHost without creating active effects or consuming random state");
        host.publish(std::move(prepared),random);const auto saved=host.snapshot(1000,7,true);
        check(saved.at("active").empty() && saved.at("contacts").size()==1 && saved.at("sources").size()==1 &&
              saved.at("sources").at(expected.path)==full && random.snapshot()==randomBefore && host.instanceWatermark()==idsBefore,
              "Publication records the accepted source contact while leaving status IDs, RNG and target control unchanged");
        StatusHost restored(package,StunStatusPolicy::inferredFlatChanceStunV1());
        restored.restore(saved,1500,7,[&](const std::string &path){return pvf.script(path);},
            [&](EntityHandle handle){return handle==request.target.handle;});
        const auto loaded=restored.snapshot(1500,7,true);auto repeated=restored.prepare(request,1500,random);
        check(loaded.at("active").empty() && loaded.at("contacts")==saved.at("contacts") &&
              loaded.at("sources")==saved.at("sources") && repeated.ready() && repeated.receipt.at("deduplicated")==true &&
              random.snapshot()==randomBefore,"Same-generation restore preserves dormant source evidence and accepted-contact deduplication without rerolling");
        restored.publish(std::move(repeated),random);
        DamageRequest damage;damage.attacker=request.attacker;damage.target=request.target.handle;
        damage.attackInstance=request.attackInstance;damage.attack=attack;damage.weaponType=DamageAttackType::Physical;
        for(auto *participant:{&damage.attackerStats,&damage.targetStats}) {
            participant->packageIdentity=package;participant->adapter="explicit-dormant-source-regression";participant->level=20;
        }
        damage.attackerStats.physicalAttack=100;damage.attackerStats.magicalAttack=100;
        const auto resolved=resolveDamage(damage,damagePolicy,&random);
        check(resolved.usable() && resolved.hpDamage.value()>0 && !resolved.missed &&
              resolved.attackInstance==request.attackInstance && random.snapshot()==randomBefore,
              "Actual source ATK resolves positive HP damage through the normal damage calculator with an accepted no-active-status host contact");
        samples.push_back({{"source",full},{"damage",resolved.snapshot()},{"status_host",saved}});
    }
    for(const auto *tag:{"[stun]","[burn]"}) {
        const auto inlineSource=dormantFixture(tag,Json::array({0,0,0}),true);
        const auto inlineParsed=readAttackStatuses(inlineSource);
        check(inlineParsed.usable() && inlineParsed.entries[0].kind==AttackStatusKind::None &&
              inlineParsed.entries[0].sources.size()==1 && dormantDiagnostic(inlineParsed.entries[0]),
              "Inline source enum uses the same narrowly validated zero triple while preserving its single original field reference");
        for(const auto &bad:std::vector<Json>{Json::array({1,0,0}),Json::array({0,1,0}),Json::array({0,0}),
            Json::array({0,0,0,0}),Json::array({0.0,0,0}),Json::array({0,0.0,0}),Json::array({0,0,0.0}),
            Json::array({"0",0,0}),Json::array({0,-1,0}),Json::array({0,0,-1}),Json::array({-0.0,0,0})}) {
            const auto rejected=readAttackStatuses(dormantFixture(tag,bad));
            check(!rejected.usable() && rejected.entries[0].rawPayload==bad && !dormantDiagnostic(rejected.entries[0]),
                  "Malformed, noninteger, nonzero or incomplete zero-duration status remains rejected with its original payload");
        }
    }
    for(const auto *tag:{"[freeze]","[poison]","[lightning]","[unknown]"})
        check(!readAttackStatuses(dormantFixture(tag,Json::array({0,0,0}))).usable(),
              "Unsupported status kinds cannot acquire a consumer by copying the zero triple");
    for(const auto &burn:std::vector<Json>{Json::array({0,0,1000}),Json::array({100,10,20000,1000,10,1,3000})})
        check(!readAttackStatuses(dormantFixture("[burn]",burn)).usable(),
              "Burn with meaningful operands still requires its own complete consumer");
    const auto zeroChanceLive=readAttackStatuses(dormantFixture("[stun]",Json::array({0,0,1000})));
    check(zeroChanceLive.usable() && zeroChanceLive.entries[0].kind==AttackStatusKind::Stun &&
          zeroChanceLive.entries[0].durationMs==1000 && !dormantDiagnostic(zeroChanceLive.entries[0]),
          "Existing valid zero-chance positive-duration stun retains its original stun definition");
    const auto heading=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
    const auto emp=readAttackStatuses(pvf.script("passiveobject/character/gunner/attackinfo/emp_bomb_sub2.atk"));
    check(heading.usable() && heading.entries[0].kind==AttackStatusKind::Stun && heading.entries[0].rawPayload==Json::array({30,0,1000}) &&
          emp.usable() && emp.entries[0].kind==AttackStatusKind::Stun && emp.entries[0].rawPayload==Json::array({100,90,5000}),
          "Native Tau and EMP positive stun definitions keep their supported probability, level and duration");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","exact 1031 integer zero triples only; active burn/freeze/lightning and controller-supplied status are separate consumers"}};
}
} // namespace dnf
