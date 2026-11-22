#include "dnf/map_access.hpp"
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
bool hasCode(const Json &diagnostics,const std::string &code) {
    return std::any_of(diagnostics.begin(),diagnostics.end(),[&](const Json &item) {
        return item.value("code",std::string())==code;
    });
}
bool sameFields(const Json &actual,const Script &script) {
    if(actual.size()!=script.fields.size())return false;
    for(size_t i=0;i<script.fields.size();++i) {
        const auto &field=script.fields[i];const auto &row=actual.at(i);
        if(row.at("tag")!=field.tag || row.at("values")!=field.values ||
           row.at("offset")!=field.offset || row.at("ordinal")!=i)return false;
    }
    return true;
}
std::set<std::string> readMapPaths(const Pvf &pvf) {
    std::set<std::string> result;
    for(const auto &row:pvf.reads().items()) {
        const auto &path=row.key();
        if(path.size()>=4 && path.compare(path.size()-4,4,".map")==0)result.insert(path);
    }
    return result;
}
} // namespace

Json runMapAccessTests(Pvf &pvf) {
    Json checks=Json::array(),samples=Json::array(),incrementalEvidence=Json::object();
    auto check=[&](bool value,const std::string &name) {
        if(!value)throw std::runtime_error("Map access: "+name);
        checks.push_back(name);
    };
    auto rejects=[&](auto callback,const std::string &name) {
        bool rejected=false;try {callback();}catch(const std::out_of_range &) {rejected=true;}
        check(rejected,name);
    };
    const auto readsBefore=readMapPaths(pvf);
    MapAccessCatalog catalog(pvf);const auto index=catalog.indexSnapshot();
    check(readMapPaths(pvf)==readsBefore,"Complete directory construction and index snapshot do not decode MAP metadata");
    check(index.at("entries").size()==catalog.size() && !index.at("complete").get<bool>() &&
          index.at("metadata_loaded_on_demand").get<bool>(),
          "Index reports every entry with explicit lazy metadata and incomplete gameplay coverage");

    const auto registry=pvf.script("map/map.lst");const auto registryHash=sha256(registry.rawBytes);
    const auto members=pvf.paths("",".map");const std::set<std::string> memberSet(members.begin(),members.end());
    Json reconstructed=Json::array();std::map<int,std::vector<size_t>> ids;
    std::map<std::string,std::vector<size_t>> paths;std::set<std::string> keys,registeredPaths;
    size_t registeredCount=0,orphans=0,malformed=0,missing=0;
    bool ordered=true,spans=true,identities=true,orphanIdentity=true;
    for(const auto &row:index.at("entries")) {
        const auto ordinal=row.at("index").get<size_t>();const auto path=row.at("path").get<std::string>();
        ordered=ordered && ordinal==keys.size();identities=identities && keys.insert(row.at("key").get<std::string>()).second;
        if(!row.at("id").is_null())ids[row.at("id").get<int>()].push_back(ordinal);
        if(!path.empty())paths[path].push_back(ordinal);
        if(row.at("registered").get<bool>()) {
            ++registeredCount;registeredPaths.insert(path);const auto &tokens=row.at("registration");
            const auto tokenIndex=reconstructed.size();const auto &source=row.at("registration_source");
            identities=identities && row.at("key")=="map.lst:"+std::to_string(tokenIndex);
            spans=spans && !tokens.empty() && source.at("member_path")==registry.path &&
                source.at("member_sha256")==registryHash && source.at("package_identity")==pvf.identity() &&
                source.at("byte_offset")==tokens.at(0).at("offset") && source.at("ordinal")==tokenIndex &&
                source.at("byte_length")==tokens.size()*5;
            for(const auto &token:tokens)reconstructed.push_back(token);
            if(tokens.size()!=2)++malformed;
            if(!path.empty() && !pvf.has(path))++missing;
        } else {
            ++orphans;orphanIdentity=orphanIdentity && row.at("id").is_null() &&
                row.at("key")=="pvf:"+path && memberSet.count(path) && row.at("registration").empty();
        }
    }
    check(ordered && identities,"Authored registrations and sorted member additions have unique stable selection keys and indices");
    check(reconstructed==registry.tokens,"Every original map.lst token survives in authored order, including duplicate and malformed records");
    check(spans,"Registration SourceRefs bind actual registry bytes, token ordinals, offsets and exact five-byte token spans");
    check(orphanIdentity,"Unregistered MAP members use source paths without fabricated numeric IDs or registrations");
    bool allMembers=true,allIdLookups=true,allPathLookups=true;size_t duplicateIds=0,duplicatePaths=0,expectedOrphans=0;
    for(const auto &path:members) {
        allMembers=allMembers && !catalog.findByPath(path).empty();
        if(!registeredPaths.count(path))++expectedOrphans;
    }
    for(const auto &[id,indices]:ids) {
        allIdLookups=allIdLookups && catalog.findById(id)==indices;
        if(indices.size()>1)++duplicateIds;
    }
    for(const auto &[path,indices]:paths) {
        allPathLookups=allPathLookups && catalog.findByPath(path)==indices;
        if(indices.size()>1)++duplicatePaths;
    }
    check(allMembers && orphans==expectedOrphans && registeredCount+expectedOrphans==catalog.size(),
          "Every actual .map member across all PVF namespaces remains selectable exactly once beyond its source registrations");
    check(allIdLookups && allPathLookups,"ID and path lookup return all source registrations without last-one-wins resolution");
    MapAccessCatalog repeated(pvf);
    check(repeated.indexSnapshot()==index,"Rebuilding a directory from the same PVF preserves every selection identity and source row");
    const auto zero=catalog.page("",0,0),past=catalog.page("",std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
    check(zero.total==catalog.size() && zero.entries.empty() && zero.offset==0 &&
          past.total==catalog.size() && past.offset==catalog.size() && past.entries.empty(),
          "Zero-sized and maximum-offset pages retain totals without decoding or arithmetic overflow");
    check(readMapPaths(pvf)==readsBefore,"Empty and out-of-range pages do not eagerly read unrelated MAP members");
    const auto page=catalog.page("",2,5);bool pageOrder=page.entries.size()==std::min(size_t(5),catalog.size()-size_t(2));
    for(size_t i=0;i<page.entries.size();++i)pageOrder=pageOrder && page.entries[i].index==i+2 && !page.entries[i].complete;
    check(pageOrder && !page.complete && !page.json().at("complete").get<bool>(),
          "Visible pages retain source ordering and never imply full gameplay capability");
    rejects([&]{catalog.at(catalog.size());},"Out-of-range metadata selection is rejected before any source read");
    rejects([&]{catalog.admission(catalog.size(),1,true);},"Out-of-range admission is rejected in test mode as well");

    auto sourceCase=[&](const std::string &path,int expectedId,int dungeonId,const std::string &dungeonPath,
                        int minimum,int basis,double background,const std::string &mapHash) {
        const auto selected=catalog.findByPath(path);check(!selected.empty(),"Real source MAP is indexed: "+path);
        const auto &entry=catalog.at(selected.front());const auto map=pvf.script(path),dungeon=pvf.script(dungeonPath);
        check(entry.readable && entry.registered && entry.id==expectedId && entry.dungeonId==dungeonId &&
              entry.minimumLevelKnown && entry.minimumLevel==minimum && entry.basisLevelKnown && entry.basisLevel==basis &&
              entry.backgroundOriginKnown && entry.backgroundOrigin==background,
              "Non-Lorien MAP consumes its actual DGN minimum, basis and background metadata: "+path);
        check(entry.source.packageIdentity==pvf.identity() && entry.source.memberPath==path &&
              entry.source.memberSha256==mapHash && entry.source.memberSha256==sha256(map.rawBytes) &&
              entry.source.byteOffset==0 && entry.source.byteLength==map.rawBytes.size() && sameFields(entry.sourceFields,map),
              "MAP provenance preserves full source identity and all ordered fields: "+path);
        bool dungeonEvidence=false;
        for(const auto &record:entry.dungeonSources)if(record.value("path",std::string())==dungeonPath)
            dungeonEvidence=record.at("id")==dungeonId && record.at("readable").get<bool>() &&
                record.at("source").at("member_sha256")==sha256(dungeon.rawBytes) &&
                record.at("source").at("package_identity")==pvf.identity() && sameFields(record.at("fields"),dungeon);
        check(dungeonEvidence,"DGN provenance and repeated or unknown fields are retained independently of RegionCatalog: "+path);
        const auto low=catalog.admission(entry.index,1,false),test=catalog.admission(entry.index,0,true,false);
        const auto task=catalog.admission(entry.index,minimum,false,false),normal=catalog.admission(entry.index,minimum,false,true);
        check(!low.allowed && hasCode(low.diagnostics,"source_minimum_level_not_met") &&
              !task.allowed && hasCode(task.diagnostics,"task_condition_not_met") && normal.allowed,
              "Normal admission consumes source level and externally supplied task eligibility: "+path);
        check(test.allowed && test.testMode && !test.complete && !test.json().at("complete").get<bool>() &&
              hasCode(test.diagnostics,"test_mode_admission_override"),
              "Test mode bypasses source level, task and historical whitelist without granting completeness: "+path);
        samples.push_back(entry.json());return entry.index;
    };
    const auto nagor=sourceCase("map/bakalcastle/15076nagor.map",15076,65,"dungeon/impossible/bakalcastle.dgn",70,70,80,
        "a9b7e3cce553517e012a8cc07fadfa48a6ee4575d2dec2eb7d31ecc759eec9fd");
    sourceCase("map/gentsouthgate/(4,0)normal.map",10037,82,"dungeon/act7/gentsouthgate.dgn",57,60,80,
        "1f8255d13646c0a89cbfcd5e0eec00ba5fdfdb0a01d30af75a906033586cf53a");
    check(catalog.findByPath("MAP\\BAKALCASTLE\\15076NAGOR.MAP")==catalog.findByPath("map/bakalcastle/15076nagor.map"),
          "Path selection canonicalizes archive case and slash aliases without merging source registrations");
    const auto beforeSearch=readMapPaths(pvf);const auto idPage=catalog.page("id:15076",0,24);
    const auto pathPage=catalog.page("path:bakalcastle/15076nagor.map",0,24);const auto afterSearch=readMapPaths(pvf);
    std::set<std::string> expectedSearchReads;
    for(const auto &row:index.at("entries"))if(row.at("id")==15076 ||
        row.at("path").get<std::string>().find("bakalcastle/15076nagor.map")!=std::string::npos)
        expectedSearchReads.insert(row.at("path").get<std::string>());
    bool onlySelected=true;for(const auto &path:afterSearch)if(!beforeSearch.count(path))
        onlySelected=onlySelected && expectedSearchReads.count(path);
    check(idPage.total==catalog.findById(15076).size() && pathPage.total==catalog.findByPath("map/bakalcastle/15076nagor.map").size() &&
          onlySelected && std::any_of(idPage.entries.begin(),idPage.entries.end(),[&](const auto &entry){return entry.index==nagor;}),
          "Exact ID and path-prefix queries find source entries without decoding unrelated names");
    check(catalog.page("id:not-an-integer",0,24).total==0 && catalog.page("path:__absent_source_member__",0,24).total==0,
          "Unmatched ID and path queries produce empty pages with valid totals");
    // Name search intentionally scans metadata. Use a zero-sized page so the
    // result checks its full match count without serializing every MAP.
    const auto nameQuery="name:"+catalog.at(nagor).name;const auto namePage=catalog.page(nameQuery,0,0);
    check(!catalog.at(nagor).name.empty() && namePage.total>0 && namePage.entries.empty(),
          "Source or derived display names are searchable with explicit full metadata scan semantics");
    size_t readableCount=0,unreadableCount=0,noDungeonCount=0,specialCount=0;
    bool allTestAdmissions=true,normalTasks=true,allIncomplete=true;
    for(size_t i=0;i<catalog.size();++i) {
        const auto &entry=catalog.at(i);const auto test=catalog.admission(i,0,true,false);
        if(entry.readable)++readableCount;else ++unreadableCount;
        if(entry.readable && entry.dungeonSources.empty())++noDungeonCount;
        if(entry.readable && entry.special)++specialCount;
        allTestAdmissions=allTestAdmissions && test.allowed==entry.readable &&
            (entry.readable?hasCode(test.diagnostics,"test_mode_admission_override"):
                hasCode(test.diagnostics,"map_cannot_load") && hasCode(entry.diagnostics,"map_source_unreadable"));
        if(!entry.readable && unreadableCount<=3)samples.push_back(entry.json());
        normalTasks=normalTasks && !catalog.admission(i,std::numeric_limits<int>::max(),false,false).allowed;
        allIncomplete=allIncomplete && !entry.complete && !test.complete;
    }
    check(allTestAdmissions && readableCount+unreadableCount==catalog.size(),
          "Test admission permits every readable directory entry without level, task or historical region filtering and rejects every unreadable entry");
    check(normalTasks && allIncomplete,
          "Every normal admission respects a failed external task condition and no directory entry or test override claims complete gameplay");

    const auto townIndices=catalog.findByPath("map/elvengard/elvengard.map");
    check(!townIndices.empty(),"Town MAP outside DGN topology remains in the complete source directory");
    const auto &town=catalog.at(townIndices.front());
    check(town.readable && !town.registered && !town.id && town.key=="pvf:"+town.path && town.dungeonId==-1 &&
          town.dungeonSources.empty() && catalog.admission(town.index,0,true,false).allowed,
          "An unregistered readable town with no DGN is test-admissible without inventing a source ID or dungeon association");
    samples.push_back(town.json());
    check(!catalog.findByPath("map/elvengard/(r)gate.map").empty(),
          "Actual town gate MAP remains independently selectable by its source member path");
    bool duplicateDiagnostics=true;
    for(const auto &[id,indices]:ids)if(indices.size()>1)for(auto ordinal:indices) {
        const auto &entry=catalog.at(ordinal);
        duplicateDiagnostics=duplicateDiagnostics && (hasCode(entry.diagnostics,"ambiguous_map_id") ||
            hasCode(entry.diagnostics,"duplicate_map_registration"));
    }
    for(const auto &[path,indices]:paths) {
        size_t registrations=0;for(auto ordinal:indices)if(index.at("entries").at(ordinal).at("registered").get<bool>())++registrations;
        if(registrations>1)for(auto ordinal:indices)duplicateDiagnostics=duplicateDiagnostics &&
            hasCode(catalog.at(ordinal).diagnostics,"map_path_has_multiple_registrations");
    }
    check(duplicateDiagnostics,"Every actual duplicate ID retains all source choices and a concrete ambiguity or duplication diagnostic");
    {
        MapAccessCatalog incremental(pvf);
        const auto initial=incremental.nameIndexProgress();
        check(initial.total==incremental.size()&&initial.indexed==0&&initial.next==0&&
              initial.complete==!incremental.size(),
              "Incremental name index starts with zero decoded records and an explicit source directory total");
        const auto reads=readMapPaths(pvf);
        const auto skeletons=incremental.partialPage("",0,9);
        check(skeletons.total==incremental.size()&&skeletons.matchesComplete&&skeletons.nameIndex&&
              skeletons.nameIndex->indexed==0&&skeletons.pendingMetadata.size()==skeletons.entries.size()&&
              !skeletons.complete&&readMapPaths(pvf)==reads,
              "Partial empty query returns source-ordered skeletons and pending metadata without synchronous source work");
        const auto absentName=incremental.partialPage("name:__not_a_source_name__",0,9);
        check(absentName.total==0&&absentName.entries.empty()&&!absentName.matchesComplete&&
              !absentName.json().at("matches_complete").get<bool>()&&readMapPaths(pvf)==reads,
              "Incomplete name query reports a lower-bound empty result without claiming no matching source name exists");
        const auto numeric=incremental.partialPage("id:15076",0,9);
        check(numeric.matchesComplete&&numeric.total==incremental.findById(15076).size()&&
              numeric.pendingMetadata.size()==numeric.entries.size()&&incremental.nameIndexProgress().indexed==0,
              "Partial exact ID query has a complete match set before any name decoding");
        auto progress=incremental.stepNameIndex(0,4000);
        check(progress.indexed==0&&progress.lastStepEntries==0,
              "Zero entry budget performs no metadata work");
        progress=incremental.stepNameIndex(3,0);
        check(progress.indexed==0&&progress.lastStepEntries==0&&readMapPaths(pvf)==reads,
              "Zero time budget performs no metadata work");
        size_t cursor=0,workSteps=0,zeroWork=0,maximumBatch=0;uint64_t maximumStepUs=0;bool timeOverrun=false;
        std::set<size_t> loadedIndices;
        const auto captureLoaded=[&] {
            const auto page=incremental.partialPage("",0,incremental.size());
            std::set<size_t> pending(page.pendingMetadata.begin(),page.pendingMetadata.end());
            for(const auto &row:page.entries)if(!pending.count(row.index))loadedIndices.insert(row.index);
            check(page.entries.size()==incremental.size()&&page.total==incremental.size(),
                  "Progress paging preserves every directory row during indexing");
        };
        // Select out of cursor order, as a visible-row click/admission does.
        if(incremental.size()>3) {
            incremental.at(incremental.size()-1);loadedIndices.insert(incremental.size()-1);
            check(incremental.nameIndexProgress().indexed==1&&incremental.nameIndexProgress().next==0,
                  "On-demand selection contributes to progress without rewinding the name-index cursor");
        }
        while(!incremental.nameIndexProgress().complete) {
            const auto before=incremental.nameIndexProgress();
            progress=incremental.stepNameIndex(3,4000);++workSteps;
            check(progress.indexed>=before.indexed&&progress.indexed-before.indexed==progress.lastStepEntries&&
                  progress.lastStepEntries<=3&&progress.next>=cursor&&progress.next<=incremental.size(),
                  "Each index step has a hard record cap, monotonic cursor and exact decoded-record progress");
            cursor=progress.next;maximumBatch=std::max(maximumBatch,progress.lastStepEntries);
            maximumStepUs=std::max(maximumStepUs,progress.lastStepMicroseconds);timeOverrun|=progress.budgetExceeded;
            if(!progress.lastStepEntries) {
                if(++zeroWork>100)throw std::runtime_error("Map incremental index repeatedly missed its scheduling budget");
            }else zeroWork=0;
            if(workSteps==1) {
                captureLoaded();
                const auto &first=incremental.at(0);
                const auto query="name:"+first.name;
                const auto partial=incremental.partialPage(query,0,incremental.size());
                check(!partial.matchesComplete&&partial.nameIndex&&partial.nameIndex->indexed<partial.nameIndex->total&&
                      partial.pendingMetadata.empty()&&std::any_of(partial.entries.begin(),partial.entries.end(),
                          [](const auto &entry){return entry.index==0;}),
                      "Loaded source names can be searched during an incomplete index without decoding remaining names");
            }
        }
        const auto complete=incremental.nameIndexProgress();
        check(complete.complete&&complete.indexed==incremental.size()&&complete.next==incremental.size()&&workSteps>1,
              "Repeated bounded steps finish all names, including unreadable entries, without a one-frame full scan");
        progress=incremental.stepNameIndex(3,4000);
        check(progress.complete&&progress.lastStepEntries==0&&progress.indexed==complete.indexed,
              "Completed name index accepts later frames without decoding records again");
        const std::vector<std::string> queries{"","id:15076","path:bakalcastle",nameQuery,"name:__not_a_source_name__","map/"};
        for(const auto &query:queries) {
            const auto expected=catalog.page(query,0,0);
            size_t consumed=0;
            do {
                const auto partial=incremental.partialPage(query,consumed,17),synchronous=catalog.page(query,consumed,17);
                bool equivalent=partial.matchesComplete&&partial.pendingMetadata.empty()&&partial.total==synchronous.total&&
                    partial.offset==synchronous.offset&&partial.entries.size()==synchronous.entries.size();
                for(size_t i=0;i<partial.entries.size();++i)
                    equivalent=equivalent&&partial.entries[i].json()==synchronous.entries[i].json();
                check(equivalent,"Completed incremental query pages exactly match the existing synchronous source metadata API");
                consumed+=partial.entries.size();
                if(partial.entries.empty())break;
            }while(consumed<expected.total);
            check(consumed==expected.total,"Incremental pagination has no omitted or repeated matches after index completion");
        }
        const auto overflow=incremental.partialPage("",std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
        check(overflow.offset==incremental.size()&&overflow.entries.empty()&&overflow.matchesComplete,
              "Partial page keeps overflow-safe offset and limit behavior after indexing");
        incrementalEvidence={{"source_entry_count",incremental.size()},{"step_count",workSteps},{"maximum_batch_entries",maximumBatch},
            {"maximum_step_microseconds",maximumStepUs},{"source_atomic_decode_exceeded_soft_deadline",timeOverrun},
            {"deadline_policy","4000us checked between source records; atomic decode cannot be preempted"},
            {"thread_policy","single-writer; no shared Pvf worker or renderer"},{"complete",complete.json()}};
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"complete",false},
        {"incremental_name_index",incrementalEvidence},
        {"scope","Full MAP registration/member directory, source metadata, paging/search and admission only; scene/gameplay consumers are verified separately"},
        {"counts",{{"catalog_entries",catalog.size()},{"source_registration_rows",registeredCount},{"actual_map_members",members.size()},
                   {"unregistered_members",orphans},{"duplicate_ids",duplicateIds},{"duplicate_paths",duplicatePaths},
                   {"malformed_rows",malformed},{"missing_registered_members",missing},{"readable_entries",readableCount},
                   {"unreadable_entries",unreadableCount},{"readable_without_dungeon",noDungeonCount},{"readable_special_entries",specialCount}}},
        {"source_negative_fixture_coverage",{{"malformed_rows_exercised",malformed>0},{"duplicate_ids_exercised",duplicateIds>0},
                                            {"unreadable_members_exercised",unreadableCount>0},
                                            {"note","Counts report actual source cases; absence does not claim a synthetic malformed-source fixture was executed"}}},
        {"samples",samples},{"diagnostics",catalog.diagnostics()},{"frontend_started",false},{"native_dynamic_comparison","pending user"}};
}
} // namespace dnf
