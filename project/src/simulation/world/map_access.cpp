#include "dnf/map_access.hpp"
#include <cmath>
#include <chrono>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void issue(Json &diagnostics,const std::string &code,const std::string &severity,Json details=Json::object()) {
    details["code"]=code;details["severity"]=severity;diagnostics.push_back(std::move(details));
}
bool integer(const Json &value,int &result) {
    if(!value.is_number_integer() || value<std::numeric_limits<int>::min() || value>std::numeric_limits<int>::max())return false;
    result=value.get<int>();return true;
}
SourceRef sourceOf(const Pvf &pvf,const Script &script,uint64_t offset=0,uint64_t length=0,size_t ordinal=0) {
    if(offset>script.rawBytes.size() || length>script.rawBytes.size()-offset)throw std::runtime_error("MAP directory source span is invalid");
    SourceRef ref;ref.packageIdentity=pvf.identity();ref.memberPath=script.path;ref.memberSha256=sha256(script.rawBytes);
    ref.literalPath=script.source.value("literal_path",script.path);ref.byteOffset=offset;
    ref.byteLength=length?length:uint64_t(script.rawBytes.size()-offset);ref.ordinal=ordinal;ref.scope="map-access-source";return ref;
}
std::string memberPath(const std::string &registry,const std::string &literal) {
    auto value=literal;std::replace(value.begin(),value.end(),'\\','/');
    auto path=std::filesystem::u8path(value);
    if(path.is_absolute() || path.has_root_name() || value.empty())return {};
    const auto directory=std::filesystem::u8path(registry).parent_path();
    const auto prefix=directory.generic_u8string()+"/";
    if(normalize(value).rfind(normalize(prefix),0)!=0)path=directory/path;
    const auto result=normalize(path.lexically_normal().generic_u8string());
    if(result.rfind(normalize(prefix),0)!=0 || result.find("../")!=std::string::npos)return {};
    return result;
}
Json fields(const Script &script) {
    Json result=Json::array();for(size_t i=0;i<script.fields.size();++i) {
        const auto &field=script.fields[i];result.push_back({{"tag",field.tag},{"values",field.values},{"offset",field.offset},{"ordinal",i}});
    }return result;
}
std::optional<int> positiveField(const Script &script,const std::string &tag,Json &diagnostics) {
    std::vector<int> candidates;size_t count=0;
    for(const auto &field:script.fields)if(normalize(field.tag)==tag) {
        ++count;int value=0;
        if(field.values.size()!=1 || !integer(field.values[0],value) || value<1) {
            issue(diagnostics,"invalid_source_level_field","error",{{"path",script.path},{"tag",tag},{"offset",field.offset},{"values",field.values}});
            continue;
        }
        candidates.push_back(value);
    }
    if(count>1)issue(diagnostics,"repeated_source_level_field","warning",{{"path",script.path},{"tag",tag},{"count",count},
        {"selection_policy","maximum valid authored constraint; all fields retained"}});
    if(candidates.empty())return {};
    return *std::max_element(candidates.begin(),candidates.end());
}
std::optional<double> backgroundField(const Script &script,Json &diagnostics) {
    std::vector<double> candidates;
    for(const auto &field:script.fields)if(normalize(field.tag)=="[background pos]") {
        if(field.values.size()!=1 || !field.values[0].is_number() || !std::isfinite(field.values[0].get<double>())) {
            issue(diagnostics,"invalid_background_origin","error",{{"path",script.path},{"offset",field.offset},{"values",field.values}});continue;
        }
        candidates.push_back(field.values[0].get<double>());
    }
    if(candidates.empty())return {};
    if(std::any_of(candidates.begin(),candidates.end(),[&](double value){return value!=candidates[0];})) {
        issue(diagnostics,"ambiguous_background_origin","error",{{"path",script.path},{"values",candidates}});return {};
    }
    return candidates[0];
}
std::string firstText(const Script &script,const std::string &tag) {
    for(const auto &field:script.fields)if(normalize(field.tag)==tag)
        for(const auto &value:field.values)if(value.is_string())return value.get<std::string>();
    return {};
}
bool levelSourceError(const Json &diagnostics) {
    return std::any_of(diagnostics.begin(),diagnostics.end(),[](const Json &entry) {
        const auto code=entry.value("code",std::string());
        return code=="dungeon_source_unreadable" || code=="unregistered_source_dungeon" ||
            code=="ambiguous_source_dungeon_registration" || code=="invalid_source_dungeon" || code=="invalid_source_level_field";
    });
}
} // namespace

Json MapAccessEntry::json() const {
    return {{"index",index},{"id",id?Json(*id):Json()},{"key",key},{"path",path},{"name",name},{"type",type},
        {"dungeon_id",dungeonId},{"minimum_level",minimumLevel},{"basis_level",basisLevel},{"background_origin",backgroundOrigin},
        {"registered",registered},{"readable",readable},{"special",special},{"minimum_level_known",minimumLevelKnown},
        {"basis_level_known",basisLevelKnown},{"background_origin_known",backgroundOriginKnown},{"source",source.json()},
        {"registration_source",registrationSource.json()},{"registration",registration},{"source_fields",sourceFields},
        {"dungeon_sources",dungeonSources},{"diagnostics",diagnostics},{"complete",false}};
}
Json MapAccessPage::json() const {
    Json rows=Json::array();for(const auto &entry:entries)rows.push_back(entry.json());
    return {{"total",total},{"offset",offset},{"entries",rows},{"diagnostics",diagnostics},{"complete",false},
        {"matches_complete",matchesComplete},{"name_index",nameIndex?nameIndex->json():Json()},
        {"pending_metadata",pendingMetadata}};
}
Json MapNameIndexProgress::json() const {
    return {{"indexed",indexed},{"total",total},{"next",next},{"last_step_entries",lastStepEntries},
        {"last_step_microseconds",lastStepMicroseconds},{"budget_microseconds",budgetMicroseconds},
        {"complete",complete},{"budget_exceeded",budgetExceeded},
        {"scheduling","single-writer; source decode is atomic; deadline checked between entries"}};
}
Json MapAdmissionResult::json() const {
    return {{"allowed",allowed},{"test_mode",testMode},{"diagnostics",diagnostics},{"complete",false}};
}
MapAccessCatalog::MapAccessCatalog(Pvf &pvf):pvf_(pvf) {
    std::set<std::string> registeredPaths;
    try {
        const auto registry=pvf_.script("map/map.lst");
        const auto registrySource=sourceOf(pvf_,registry);
        for(size_t i=0;i<registry.tokens.size();) {
            MapAccessEntry entry;entry.index=entries_.size();entry.registered=true;
            const auto &token=registry.tokens[i];entry.key="map.lst:"+std::to_string(i);
            int id=0;const bool hasId=integer(token.at("value"),id);
            if(hasId)entry.id=id;
            const bool pair=hasId && i+1<registry.tokens.size() && registry.tokens[i+1].at("value").is_string();
            entry.registration.push_back(token);
            const size_t length=pair?10:5;
            entry.registrationSource=registrySource;entry.registrationSource.byteOffset=token.at("offset").get<uint64_t>();
            entry.registrationSource.byteLength=length;entry.registrationSource.ordinal=i;
            if(pair) {
                entry.registration.push_back(registry.tokens[i+1]);
                const auto literal=registry.tokens[i+1].at("value").get<std::string>();entry.path=memberPath(registry.path,literal);
                if(entry.path.empty())issue(entry.diagnostics,"invalid_registered_map_path","error",{{"literal",literal}});
                else registeredPaths.insert(entry.path);
            } else issue(entry.diagnostics,"malformed_map_registration","error",{{"token_index",i},{"token",token}});
            entries_.push_back(std::move(entry));loaded_.push_back(false);i+=pair?2:1;
        }
    } catch(const std::exception &error) {
        issue(diagnostics_,"map_registry_unreadable","error",{{"path","map/map.lst"},{"reason",error.what()}});
    }
    // Pvf::paths returns every actual matching member sorted by normalized path.
    // This keeps town/special/test/unregistered MAPs without creating source IDs.
    for(const auto &path:pvf_.paths("",".map"))if(!registeredPaths.count(path)) {
        MapAccessEntry entry;entry.index=entries_.size();entry.key="pvf:"+path;entry.path=path;
        issue(entry.diagnostics,"map_not_registered","info",{{"path",path},{"selection_identity","PVF member path"}});
        entries_.push_back(std::move(entry));loaded_.push_back(false);
    }
    std::map<int,std::vector<size_t>> ids;std::map<std::string,std::vector<size_t>> paths;
    for(const auto &entry:entries_) {
        if(entry.id)ids[*entry.id].push_back(entry.index);
        if(entry.registered && !entry.path.empty())paths[entry.path].push_back(entry.index);
        if(entry.id)byId_[*entry.id].push_back(entry.index);
        if(!entry.path.empty())byPath_[entry.path].push_back(entry.index);
    }
    for(const auto &[id,indices]:ids)if(indices.size()>1) {
        std::set<std::string> choices;for(auto index:indices)choices.insert(entries_[index].path);
        for(auto index:indices)issue(entries_[index].diagnostics,choices.size()>1?"ambiguous_map_id":"duplicate_map_registration","warning",
            {{"id",id},{"indices",indices},{"paths",choices}});
    }
    for(const auto &[path,indices]:paths)if(indices.size()>1)
        for(auto index:indices)issue(entries_[index].diagnostics,"map_path_has_multiple_registrations","info",{{"path",path},{"indices",indices}});
    try {
        const auto registry=pvf_.script("dungeon/dungeon.lst");
        for(size_t i=0;i<registry.tokens.size();) {
            int id=0;
            if(integer(registry.tokens[i].at("value"),id) && i+1<registry.tokens.size() && registry.tokens[i+1].at("value").is_string()) {
                const auto path=memberPath(registry.path,registry.tokens[i+1].at("value").get<std::string>());
                if(!path.empty())dungeonPaths_[id].push_back(path);
                else issue(diagnostics_,"invalid_dungeon_registration_path","error",{{"id",id},{"token_index",i}});
                i+=2;
            } else {issue(diagnostics_,"malformed_dungeon_registration","error",{{"token_index",i},{"token",registry.tokens[i]}});++i;}
        }
    } catch(const std::exception &error) {
        issue(diagnostics_,"dungeon_registry_unreadable","error",{{"path","dungeon/dungeon.lst"},{"reason",error.what()}});
    }
}
void MapAccessCatalog::load(size_t index) const {
    auto &entry=entries_.at(index);if(loaded_.at(index))return;
    // Build all lazy metadata privately; rejected/failed sources remain visible
    // entries with their exact diagnostics instead of disappearing from a page.
    auto prepared=entry;
    prepared.source.packageIdentity=pvf_.identity();prepared.source.memberPath=prepared.path;
    try {
        if(prepared.path.empty())throw std::runtime_error("Registration has no loadable MAP member path");
        const auto map=pvf_.script(prepared.path);prepared.source=sourceOf(pvf_,map);prepared.sourceFields=fields(map);
        prepared.name=firstText(map,"[name]");prepared.type=firstText(map,"[type]");
        prepared.special=!prepared.type.empty() && normalize(prepared.type)!="[normal]";
        const auto ownMinimum=positiveField(map,"[minimum required level]",prepared.diagnostics);
        if(ownMinimum){prepared.minimumLevel=*ownMinimum;prepared.minimumLevelKnown=true;}
        auto ownBackground=backgroundField(map,prepared.diagnostics);
        if(ownBackground){prepared.backgroundOrigin=*ownBackground;prepared.backgroundOriginKnown=true;}
        std::vector<int> sourceDungeons;
        for(const auto &field:map.fields)if(normalize(field.tag)=="[dungeon]")for(const auto &value:field.values) {
            int id=0;
            if(!integer(value,id))issue(prepared.diagnostics,"invalid_source_dungeon","error",{{"offset",field.offset},{"value",value}});
            else if(id>=0 && std::find(sourceDungeons.begin(),sourceDungeons.end(),id)==sourceDungeons.end())sourceDungeons.push_back(id);
        }
        if(sourceDungeons.size()==1)prepared.dungeonId=sourceDungeons[0];
        else if(sourceDungeons.size()>1)issue(prepared.diagnostics,"multiple_source_dungeons","warning",{{"ids",sourceDungeons},
            {"primary_dungeon_id","unset; every source minimum level is checked"}});
        std::vector<int> bases;std::vector<double> backgrounds;std::vector<std::string> names;
        for(int id:sourceDungeons) {
            const auto found=dungeonPaths_.find(id);
            if(found==dungeonPaths_.end()) {
                issue(prepared.diagnostics,"unregistered_source_dungeon","error",{{"id",id}});
                prepared.dungeonSources.push_back({{"id",id},{"readable",false},{"reason","unregistered dungeon ID"}});continue;
            }
            const std::set<std::string> choices(found->second.begin(),found->second.end());
            if(choices.size()>1)issue(prepared.diagnostics,"ambiguous_source_dungeon_registration","error",{{"id",id},{"paths",found->second}});
            for(const auto &path:choices) {
                Json record={{"id",id},{"path",path},{"registered_paths",found->second},{"readable",false}};
                SourceRef dungeonSource;dungeonSource.packageIdentity=pvf_.identity();dungeonSource.memberPath=path;
                record["source"]=dungeonSource.json();
                try {
                    const auto dungeon=pvf_.script(path);Json diagnostics=Json::array();
                    record["source"]=sourceOf(pvf_,dungeon).json();record["fields"]=fields(dungeon);record["readable"]=true;
                    const auto minimum=positiveField(dungeon,"[minimum required level]",diagnostics);
                    const auto basis=positiveField(dungeon,"[basis level]",diagnostics);const auto background=backgroundField(dungeon,diagnostics);
                    record["minimum_level"]=minimum?Json(*minimum):Json();record["basis_level"]=basis?Json(*basis):Json();
                    record["background_origin"]=background?Json(*background):Json();record["name"]=firstText(dungeon,"[name]");record["diagnostics"]=diagnostics;
                    for(const auto &diagnostic:diagnostics)prepared.diagnostics.push_back(diagnostic);
                    if(minimum){prepared.minimumLevel=std::max(prepared.minimumLevel,*minimum);prepared.minimumLevelKnown=true;}
                    if(basis)bases.push_back(*basis);if(background)backgrounds.push_back(*background);
                    const auto name=firstText(dungeon,"[name]");if(!name.empty())names.push_back(name);
                }catch(const std::exception &error) {
                    try {record["source"]=makeSourceRef(pvf_,path).json();}catch(const std::exception &) {}
                    record["reason"]=error.what();issue(prepared.diagnostics,"dungeon_source_unreadable","error",{{"id",id},{"path",path},{"reason",error.what()}});
                }
                prepared.dungeonSources.push_back(std::move(record));
            }
        }
        if(!bases.empty() && std::all_of(bases.begin(),bases.end(),[&](int value){return value==bases[0];})) {
            prepared.basisLevel=bases[0];prepared.basisLevelKnown=true;
        } else if(!bases.empty())issue(prepared.diagnostics,"ambiguous_dungeon_basis_level","warning",{{"values",bases},{"fallback",1}});
        if(!ownBackground && !backgrounds.empty() && std::all_of(backgrounds.begin(),backgrounds.end(),[&](double value){return value==backgrounds[0];})) {
            prepared.backgroundOrigin=backgrounds[0];prepared.backgroundOriginKnown=true;
        } else if(!ownBackground && !backgrounds.empty())issue(prepared.diagnostics,"ambiguous_dungeon_background","warning",{{"values",backgrounds},{"fallback",0}});
        if(prepared.name.empty() && !names.empty() && std::all_of(names.begin(),names.end(),[&](const std::string &value){return value==names[0];}))prepared.name=names[0];
        if(prepared.name.empty())prepared.name=std::filesystem::u8path(prepared.path).stem().u8string();
        if(!prepared.minimumLevelKnown)issue(prepared.diagnostics,"no_authored_minimum_level","info",{{"policy","No source level constraint is invented"}});
        if(!prepared.basisLevelKnown)issue(prepared.diagnostics,"basis_level_default","info",{{"value",1},{"classification","explicit direct-MAP fallback; not source balance"}});
        if(!prepared.backgroundOriginKnown)issue(prepared.diagnostics,"background_origin_default","info",{{"value",0},{"classification","explicit direct-MAP fallback; not native projection proof"}});
        prepared.readable=true;
    }catch(const std::exception &error) {
        issue(prepared.diagnostics,"map_source_unreadable","error",{{"path",prepared.path},{"reason",error.what()}});
        try {if(!prepared.path.empty())prepared.source=makeSourceRef(pvf_,prepared.path);}catch(const std::exception &) {}
    }
    entry=std::move(prepared);loaded_[index]=true;++loadedCount_;
}
const MapAccessEntry &MapAccessCatalog::at(size_t index) const {load(index);return entries_.at(index);}
std::vector<size_t> MapAccessCatalog::findById(int id) const {
    const auto found=byId_.find(id);return found==byId_.end()?std::vector<size_t>{}:found->second;
}
std::vector<size_t> MapAccessCatalog::findByPath(const std::string &path) const {
    const auto found=byPath_.find(normalize(path));return found==byPath_.end()?std::vector<size_t>{}:found->second;
}
MapAccessPage MapAccessCatalog::page(const std::string &search,size_t offset,size_t limit) const {
    auto query=normalize(search);const bool pathOnly=query.rfind("path:",0)==0,idOnly=query.rfind("id:",0)==0,nameOnly=query.rfind("name:",0)==0;
    if(pathOnly)query.erase(0,5);if(idOnly)query.erase(0,3);if(nameOnly)query.erase(0,5);
    std::vector<size_t> matches;
    for(const auto &entry:entries_) {
        bool match=query.empty() || (!idOnly && !nameOnly && entry.path.find(query)!=std::string::npos) ||
            (!pathOnly && !nameOnly && entry.id && (idOnly?std::to_string(*entry.id)==query:std::to_string(*entry.id).find(query)!=std::string::npos));
        if(!match && !pathOnly && !idOnly)match=normalize(at(entry.index).name).find(query)!=std::string::npos;
        if(match)matches.push_back(entry.index);
    }
    MapAccessPage result;result.total=matches.size();result.offset=std::min(offset,matches.size());result.diagnostics=diagnostics_;
    const auto count=std::min(limit,matches.size()-result.offset);
    for(size_t i=0;i<count;++i)result.entries.push_back(at(matches[result.offset+i]));return result;
}
MapNameIndexProgress MapAccessCatalog::nameIndexProgress() const {
    auto progress=lastNameStep_;
    progress.indexed=loadedCount_;progress.total=entries_.size();progress.next=nameIndexNext_;
    while(progress.next<loaded_.size()&&loaded_[progress.next])++progress.next;
    progress.complete=loadedCount_==entries_.size();
    return progress;
}
MapNameIndexProgress MapAccessCatalog::stepNameIndex(size_t maxEntries,uint64_t budgetMicroseconds) const {
    using Clock=std::chrono::steady_clock;
    const auto started=Clock::now();
    lastNameStep_={};lastNameStep_.budgetMicroseconds=std::min<uint64_t>(budgetMicroseconds,4000);
    const auto elapsed=[&] {
        return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now()-started).count());
    };
    // A work request never creates a thread or touches the same Pvf from a
    // worker. Callers retain ownership and may stop between UI frames.
    if(maxEntries&&lastNameStep_.budgetMicroseconds) {
        while(nameIndexNext_<loaded_.size()) {
            if(loaded_[nameIndexNext_]){++nameIndexNext_;continue;}
            if(lastNameStep_.lastStepEntries>=maxEntries || elapsed()>=lastNameStep_.budgetMicroseconds)break;
            load(nameIndexNext_);++nameIndexNext_;++lastNameStep_.lastStepEntries;
        }
    }
    lastNameStep_.lastStepMicroseconds=elapsed();
    lastNameStep_.budgetExceeded=lastNameStep_.budgetMicroseconds&&
        lastNameStep_.lastStepMicroseconds>lastNameStep_.budgetMicroseconds;
    return nameIndexProgress();
}
MapAccessPage MapAccessCatalog::partialPage(const std::string &search,size_t offset,size_t limit) const {
    auto query=normalize(search);
    const bool pathOnly=query.rfind("path:",0)==0,idOnly=query.rfind("id:",0)==0,nameOnly=query.rfind("name:",0)==0;
    if(pathOnly)query.erase(0,5);if(idOnly)query.erase(0,3);if(nameOnly)query.erase(0,5);
    std::vector<size_t> matches;
    for(const auto &entry:entries_) {
        bool match=query.empty() || (!idOnly&&!nameOnly&&entry.path.find(query)!=std::string::npos) ||
            (!pathOnly&&!nameOnly&&entry.id&&(idOnly?std::to_string(*entry.id)==query:std::to_string(*entry.id).find(query)!=std::string::npos));
        if(!match&&!pathOnly&&!idOnly&&loaded_[entry.index])match=normalize(entry.name).find(query)!=std::string::npos;
        if(match)matches.push_back(entry.index);
    }
    MapAccessPage result;result.total=matches.size();result.offset=std::min(offset,matches.size());result.diagnostics=diagnostics_;
    result.nameIndex=nameIndexProgress();
    result.matchesComplete=query.empty()||pathOnly||idOnly||result.nameIndex->complete;
    const auto count=std::min(limit,matches.size()-result.offset);
    for(size_t i=0;i<count;++i) {
        const auto index=matches[result.offset+i];
        result.entries.push_back(entries_[index]);
        if(!loaded_[index])result.pendingMetadata.push_back(index);
    }
    return result;
}
Json MapAccessCatalog::indexSnapshot() const {
    Json entries=Json::array();for(const auto &entry:entries_)entries.push_back({{"index",entry.index},{"key",entry.key},
        {"id",entry.id?Json(*entry.id):Json()},{"path",entry.path},{"registered",entry.registered},
        {"registration",entry.registration},{"registration_source",entry.registrationSource.json()}});
    return {{"entries",entries},{"diagnostics",diagnostics_},{"complete",false},{"metadata_loaded_on_demand",true}};
}
MapAdmissionResult MapAccessCatalog::admission(size_t index,int characterLevel,bool testMode,bool taskConditionsMet) const {
    const auto &entry=at(index);MapAdmissionResult result;result.testMode=testMode;result.diagnostics=entry.diagnostics;
    if(!entry.readable) {
        issue(result.diagnostics,"map_cannot_load","error",{{"path",entry.path},{"test_mode_cannot_supply_missing_source",true}});return result;
    }
    if(testMode) {
        result.allowed=true;issue(result.diagnostics,"test_mode_admission_override","info",{{"bypassed",Json::array({"level","task","historical_region_whitelist"})}});return result;
    }
    if(characterLevel<1 || (entry.minimumLevelKnown && characterLevel<entry.minimumLevel))
        issue(result.diagnostics,"source_minimum_level_not_met","error",{{"required",entry.minimumLevel},{"character_level",characterLevel}});
    else if(!taskConditionsMet)issue(result.diagnostics,"task_condition_not_met","error");
    else if(levelSourceError(entry.diagnostics))issue(result.diagnostics,"source_level_admission_unresolved","error");
    else result.allowed=true;
    return result;
}
} // namespace dnf
