#include "dnf/character_advancement.hpp"
#include "dnf/combat.hpp"
#include <chrono>
#include <functional>
#include <stdexcept>
#include <utility>

namespace dnf {
namespace {
// Small synthetic source packages use the same container construction already
// exercised by test_pvf_loading.cpp. Original PVF files are never written.
void cacheU32(Bytes &bytes,uint32_t value) {
    for(int n=0;n<4;++n)bytes.push_back(uint8_t(value>>(n*8)));
}
void cacheToken(Bytes &bytes,uint8_t type,int32_t value) {bytes.push_back(type);cacheU32(bytes,uint32_t(value));}
Bytes cacheEncrypt(Bytes bytes,uint32_t crc) {
    while(bytes.size()%4)bytes.push_back(0);
    for(size_t i=0;i<bytes.size();i+=4) {
        uint32_t word;std::memcpy(&word,bytes.data()+i,4);
        word=((word<<6)|(word>>26))^0x81A79011u^crc;
        std::memcpy(bytes.data()+i,&word,4);
    }
    return bytes;
}
struct CacheSourceFixture {
    std::vector<std::string> strings;
    int index(const std::string &s) {
        auto found=std::find(strings.begin(),strings.end(),s);
        if(found!=strings.end())return int(found-strings.begin());
        strings.push_back(s);return int(strings.size()-1);
    }
    void text(Bytes &bytes,uint8_t type,const std::string &value){cacheToken(bytes,type,index(value));}
    void field(Bytes &bytes,const std::string &tag){text(bytes,5,tag);}
    Bytes registry(const std::vector<std::pair<int,std::string>> &entries) {
        Bytes bytes{0xb0,0xd0};for(const auto &[id,path]:entries){cacheToken(bytes,2,id);text(bytes,7,path);}return bytes;
    }
    Bytes quest(bool awakening) {
        Bytes bytes{0xb0,0xd0};field(bytes,"[reward type]");text(bytes,7,awakening?"[awakening type]":"[grow type]");
        field(bytes,"[reward int data]");cacheToken(bytes,2,1);
        field(bytes,"[job]");text(bytes,7,"[fixture job]");
        field(bytes,"[grow type]");cacheToken(bytes,2,awakening?1:-1);
        field(bytes,"[level]");cacheToken(bytes,2,awakening?50:15);cacheToken(bytes,2,99);return bytes;
    }
    void write(const std::filesystem::path &path,bool ambiguousTrainer) {
        Bytes chr{0xb0,0xd0};field(chr,"[job]");text(chr,7,"[fixture job]");
        field(chr,"[growtype name]");text(chr,7,"Base");text(chr,7,"Branch");
        field(chr,"[initial value]");field(chr,"[growtype 1]");field(chr,"[growtype 2]");
        field(chr,"[awakening name]");text(chr,7,"Awakened");field(chr,"[awakening 1]");
        const std::vector<std::pair<int,std::string>> trainers=ambiguousTrainer?
            std::vector<std::pair<int,std::string>>{{7,"gsd.npc"},{8,"gsd.npc"}}:
            std::vector<std::pair<int,std::string>>{{7,"gsd.npc"}};
        std::vector<std::pair<std::string,Bytes>> members={
            {"character/character.lst",registry({{0,"fixture.chr"}})},
            {"skill/skilllist.lst",registry({})},{"character/characteretc/default.etc",Bytes{0xb0,0xd0}},
            {"character/fixture.chr",chr},{"npc/npc.lst",registry(trainers)},
            {"npc/gsd.npc",Bytes{0xb0,0xd0}},
            {"n_quest/quest.lst",registry({{1,"branch.qst"},{2,"awakening.qst"}})},
            {"n_quest/branch.qst",quest(false)},{"n_quest/awakening.qst",quest(true)}};
        Bytes table;cacheU32(table,uint32_t(strings.size()));uint32_t offset=uint32_t((strings.size()+1)*4);
        for(const auto &s:strings){cacheU32(table,offset);offset+=uint32_t(s.size());}cacheU32(table,offset);
        for(const auto &s:strings)table.insert(table.end(),s.begin(),s.end());
        members.insert(members.begin(),{"stringtable.bin",std::move(table)});
        Bytes tree,payload;
        for(size_t i=0;i<members.size();++i) {
            const auto &[name,bytes]=members[i];const uint32_t crc=uint32_t(101+i);
            cacheU32(tree,uint32_t(i));cacheU32(tree,uint32_t(name.size()));tree.insert(tree.end(),name.begin(),name.end());
            cacheU32(tree,uint32_t(bytes.size()));cacheU32(tree,crc);cacheU32(tree,uint32_t(payload.size()));
            const auto encrypted=cacheEncrypt(bytes,crc);payload.insert(payload.end(),encrypted.begin(),encrypted.end());
        }
        tree=cacheEncrypt(tree,91);Bytes bytes;cacheU32(bytes,36);bytes.resize(40,0);
        cacheU32(bytes,1);cacheU32(bytes,uint32_t(tree.size()));cacheU32(bytes,91);cacheU32(bytes,uint32_t(members.size()));
        bytes.insert(bytes.end(),tree.begin(),tree.end());bytes.insert(bytes.end(),payload.begin(),payload.end());
        std::ofstream stream(path,std::ios::binary);
        if(!stream.write(reinterpret_cast<const char*>(bytes.data()),std::streamsize(bytes.size())))
            throw std::runtime_error("Cannot write advancement cache fixture");
    }
};
}

Json runCharacterAdvancementCacheTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),contexts=Json::array();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Advancement cache: "+name);checks.push_back(name);};
    const auto rejects=[&](auto operation){try{operation();return false;}catch(const std::exception &){return true;}};
    const auto out=std::filesystem::absolute(std::filesystem::path("cache/tests/character-advancement-cache")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(out);
    const auto count=[](const Json &value,const char *key){return value.at(key).get<uint64_t>();};
    const auto cold=[](const Pvf &owner){const auto s=characterAdvancementCacheSnapshot(owner);
        return !s.at("entry_present").get<bool>()&&s.at("requests")==0&&s.at("hits")==0&&s.at("builds")==0;};
    try {
        CacheSourceFixture fixture;fixture.write(out/"source.pvf",false);
        Pvf source(out/"source.pvf");CharacterCatalog characters(source),equivalent(source);
        check(cold(source),"New source owner starts with an empty zero-counter slot");
        auto first=sharedCharacterAdvancementCatalog(source,characters);
        auto second=sharedCharacterAdvancementCatalog(source,equivalent);
        const auto initial=characterAdvancementCacheSnapshot(source);
        check(first==second&&count(initial,"requests")==2&&count(initial,"hits")==1&&count(initial,"builds")==1,
            "Independent equivalent catalogs reuse one complete immutable owner payload");
        check(first->options().size()==2&&first->find({0,1,0})&&first->find({0,1,1})&&
            first->find({0,1,0})->requiredLevel==15&&first->find({0,1,1})->requiredLevel==50,
            "Synthetic parsed QST/CHR fixture admits actual branch and first-awakening source options");
        CharacterAdvancementCatalog direct(source,characters);
        check(first->snapshot()==direct.snapshot(),"Cached fixture retains the uncached source refs, diagnostics, names and rules");
        auto snapshotCopy=first->snapshot();snapshotCopy["options"]=Json::array();
        check(first->snapshot()==direct.snapshot(),"Returned diagnostic JSON does not mutate the shared catalog");
        Pvf foreign(out/"source.pvf");CharacterCatalog foreignCharacters(foreign);
        const auto beforeForeign=characterAdvancementCacheSnapshot(source);
        check(source.identity()==foreign.identity()&&rejects([&]{sharedCharacterAdvancementCatalog(source,foreignCharacters);})&&
            characterAdvancementCacheSnapshot(source)==beforeForeign&&cold(foreign),
            "Equal-hash foreign CharacterCatalog is rejected before counters or entries change");

        const auto mutation=[&](const std::string &name,const std::function<void(CharacterCatalog &)> &change) {
            auto baseline=sharedCharacterAdvancementCatalog(source,characters);
            const auto oldSnapshot=baseline->snapshot(),oldContext=characterAdvancementSourceContext(source,characters);
            CharacterCatalog changed=characters;change(changed);
            const auto newContext=characterAdvancementSourceContext(source,changed),before=characterAdvancementCacheSnapshot(source);
            auto result=sharedCharacterAdvancementCatalog(source,changed);CharacterAdvancementCatalog expected(source,changed);
            const auto after=characterAdvancementCacheSnapshot(source);
            check(oldContext!=newContext&&result!=baseline&&count(after,"builds")==count(before,"builds")+1,
                "Changed "+name+" cannot hit the previous interpreted context");
            check(result->snapshot()==expected.snapshot()&&baseline->snapshot()==oldSnapshot,
                "Changed "+name+" matches uncached behavior and leaves an old reader intact");
            contexts.push_back({{"case",name},{"context_sha256",after.at("context_sha256")},
                {"options",result->options().size()},{"diagnostics",result->snapshot().at("diagnostics")}});
        };
        mutation("branch name",[](auto &c){c.definitions.at(0).growtypeNames[1]="Renamed branch";});
        mutation("user deferral",[](auto &c){c.definitions.at(0).runtimeDeferredByUser=true;});
        mutation("job identity",[](auto &c){c.definitions.at(0).job="[different job]";});
        mutation("registration identity",[](auto &c){c.definitions.at(0).registration.id=11;});
        mutation("source stat identities",[](auto &c){for(auto &b:c.definitions.at(0).stats)if(b.growtype==2)b.growtype=99;});
        mutation("repeated awakening-name field",[](auto &c){
            for(auto &b:c.definitions.at(0).stats)if(b.growtype==2&&b.awakening==0)
                for(const auto &f:b.fields)if(normalize(f.tag)=="[awakening name]"){const auto extra=f;b.fields.push_back(extra);return;}
            throw std::runtime_error("Fixture has no awakening name");
        });
        mutation("member provenance",[](auto &c){c.definitions.at(0).source.provenance["fixture_revision"]=2;});
        auto original=sharedCharacterAdvancementCatalog(source,characters);const auto sourceState=characterAdvancementCacheSnapshot(source);
        Pvf copied(source);check(cold(copied)&&characterAdvancementCacheSnapshot(source)==sourceState,"Pvf copy starts cold without clearing source slot");
        CharacterCatalog copyCharacters(copied);auto copyValue=sharedCharacterAdvancementCatalog(copied,copyCharacters);
        check(copyValue!=original&&copyValue->snapshot()==original->snapshot(),"Copied owner builds independent identical source payload");
        Pvf moved(std::move(copied));check(cold(moved)&&cold(copied),"Pvf move construction clears both cache slots");
        check(copyValue->snapshot()==original->snapshot(),"External immutable payload survives source move");
        CharacterCatalog movedCharacters(moved);auto movedValue=sharedCharacterAdvancementCatalog(moved,movedCharacters);
        check(movedValue!=copyValue,"Moved destination does not inherit old owner payload");
        Pvf assigned(out/"source.pvf");CharacterCatalog assignedBefore(assigned);auto oldAssigned=sharedCharacterAdvancementCatalog(assigned,assignedBefore);
        assigned=source;check(cold(assigned)&&characterAdvancementCacheSnapshot(source)==sourceState,"Copy assignment clears destination and preserves source slot");
        check(oldAssigned->snapshot()==original->snapshot(),"External destination payload survives copy assignment");
        CharacterCatalog assignedCharacters(assigned);auto assignedValue=sharedCharacterAdvancementCatalog(assigned,assignedCharacters);
        assigned=std::move(moved);check(cold(assigned)&&cold(moved),"Move assignment clears both owner slots");
        check(assignedValue->snapshot()==original->snapshot()&&movedValue->snapshot()==original->snapshot(),
            "External payloads survive move assignment independently of both slots");
        const auto assignedState=characterAdvancementCacheSnapshot(assigned);
        check(rejects([&]{sharedCharacterAdvancementCatalog(assigned,copyCharacters);})&&characterAdvancementCacheSnapshot(assigned)==assignedState,
            "A catalog borrowed from a moved-from different owner is rejected before cache publication");
        std::shared_ptr<const CharacterAdvancementCatalog> detached;std::weak_ptr<const CharacterAdvancementCatalog> observer;
        {Pvf temporary(out/"source.pvf");CharacterCatalog local(temporary);detached=sharedCharacterAdvancementCatalog(temporary,local);observer=detached;}
        check(detached->snapshot().at("options").size()==2,"Payload has no borrowed dependency on destroyed Pvf or CharacterCatalog");
        detached.reset();check(observer.expired(),"Destroying owner and last reader releases the payload without a cycle");

        CacheSourceFixture invalidFixture;invalidFixture.write(out/"ambiguous-gsd.pvf",true);
        Pvf invalid(out/"ambiguous-gsd.pvf");CharacterCatalog invalidCharacters(invalid);
        for(uint64_t attempt=1;attempt<=2;++attempt) {
            check(rejects([&]{sharedCharacterAdvancementCatalog(invalid,invalidCharacters);}),"Ambiguous registered GSD throws on attempt "+std::to_string(attempt));
            const auto failed=characterAdvancementCacheSnapshot(invalid);
            check(!failed.at("entry_present").get<bool>()&&count(failed,"requests")==attempt&&count(failed,"builds")==0&&count(failed,"hits")==0,
                "Constructor-wide failure publishes no entry and retries instead of caching success");
        }

        // Use the actual source/profile and the normal engine, not a fixture
        // World or a scan of code text. The direct reference is deliberately
        // independent of the cached construction.
        CharacterCatalog actualCharacters(pvf),actualEquivalent(pvf);
        auto actual=sharedCharacterAdvancementCatalog(pvf,actualCharacters);
        const auto actualBefore=characterAdvancementCacheSnapshot(pvf);
        {auto same=sharedCharacterAdvancementCatalog(pvf,actualEquivalent);
            check(same==actual,"Independent actual1031 CharacterCatalogs reuse the same owner payload");}
        check(count(characterAdvancementCacheSnapshot(pvf),"hits")==count(actualBefore,"hits")+1,
            "Actual1031 equivalent context records a real factory hit");
        CharacterAdvancementCatalog actualDirect(pvf,actualCharacters);
        check(actual->snapshot()==actualDirect.snapshot()&&actual->options().size()==64,
            "Actual1031 cached catalog equals uncached full source scan including all 64 current options");
        const auto *expected=actual.get();std::weak_ptr<const CharacterAdvancementCatalog> worldObserver=actual;
        const auto builds=count(characterAdvancementCacheSnapshot(pvf),"builds");
        {
            World one(pvf,assets,WorldRules::BetaFoundationV1),two(pvf,assets,WorldRules::BetaFoundationV1);
            const auto twoControllers=two.controllerCoverage();one.enableExperimentalCharacters();
            check(two.controllerCoverage()==twoControllers&&!two.supportsCharacter({1,1,0})&&one.supportsCharacter({1,1,0}),
                "Enabling one World registers its own advancement adapters without changing the other registry");
            two.enableExperimentalCharacters();
            check(&one.advancementCatalog()==expected&& &two.advancementCatalog()==expected,
                "Overlapping actual Worlds acquire the same source catalog");
            actual.reset();
            const auto twoLedger=two.skillState().snapshot(two.nowMs()),twoRandom=two.randomStreams().snapshot(),twoSimulation=two.simulationCheckpoint();
            const int twoMp=two.player.mp;const auto twoIdentity=two.identity();
            one.selectCharacter({1,0,0});one.skillState().setLearnedLevel({1,6},2);one.skillState().startCooldown({1,6},one.nowMs(),1000);
            one.randomStreams().stream(RandomDomain::Loot,429).next();if(one.player.mp>0)--one.player.mp;
            one.enqueue({one.simulationNanoseconds(),1,true});one.advanceSingleTick();
            check(one.identity().jobId==1&&one.skillState().learnedLevel({1,6})==2&&one.skillState().remainingCooldown({1,6},one.nowMs())>0&&one.tick>two.tick,
                "First World performs independent identity, learning, cooldown, RNG and queued simulation mutations");
            check(two.identity()==twoIdentity&&two.skillState().snapshot(two.nowMs())==twoLedger&&two.randomStreams().snapshot()==twoRandom&&
                two.simulationCheckpoint()==twoSimulation&&two.player.mp==twoMp,
                "Shared source catalog does not share actual World identity, skills, CD, MP, input, clock, IDs or RNG");
        }
        check(!worldObserver.expired(),"Pvf strong slot retains payload after all Worlds and external strong readers are destroyed");
        {World sequential(pvf,assets,WorldRules::BetaFoundationV1);sequential.enableExperimentalCharacters();
            check(&sequential.advancementCatalog()==expected&&count(characterAdvancementCacheSnapshot(pvf),"builds")==builds,
                "Sequential actual World reuses retained source data without another catalog build");}
        Json result={{"status","pass"},{"checks",checks},{"count",checks.size()},{"context_cases",contexts},
            {"fixture_directory",out.u8string()},{"actual_source",pvf.identity()},{"actual_cache",characterAdvancementCacheSnapshot(pvf)},
            {"scope","Actual Pvf/parser/catalog/cache and World consumers; frontend and native visual parity remain separate"},
            {"limitations",Json::array({"No deterministic allocation failure injection with a previously populated entry",
                "No counter-saturation or same-address placement fixture; no concurrent Pvf safety claim",
                "No elapsed-time/FPS measurement or new skill-completeness claim"})}};
        writeJson("reports/seven-job-world/character-advancement-cache-tests.json",result);return result;
    } catch(const std::exception &error) {
        writeJson("reports/seven-job-world/character-advancement-cache-tests.json",{{"status","failed"},{"error",error.what()},
            {"checks",checks},{"count",checks.size()},{"fixture_directory",out.u8string()}});throw;
    }
}
} // namespace dnf
