#include "dnf/portal_visuals.hpp"
#include <stdexcept>

namespace dnf {
namespace {
std::string relative(const std::string &parent,const std::string &literal) {
    return normalize((std::filesystem::u8path(parent).parent_path()/std::filesystem::u8path(literal)).lexically_normal().generic_u8string());
}
int sourceInt(const Json &v) {
    if(!v.is_number_integer())throw std::runtime_error("Pathgate requires integer pair");
    const auto n=v.get<int64_t>();
    if(n<INT32_MIN||n>INT32_MAX)throw std::runtime_error("Pathgate integer out of range");
    return int(n);
}
}
PortalObjectSource resolveDungeonPortalSource(Pvf &pvf,const std::vector<int> &ids,Direction direction,bool boss) {
    PortalObjectSource result;result.direction=int(direction);result.boss=boss;result.inputIds=ids;
    auto fail=[&](const std::string &message){result.diagnostic=message;return result;};
    if(ids.size()!=10)return fail("Unsupported [pathgate object] length "+std::to_string(ids.size())+"; expected current 1031 ten-slot layout");
    if(result.direction<0||result.direction>3)return fail("Unsupported pathgate direction");
    constexpr size_t normalSlots[]={0,3,6,8};
    result.slot=normalSlots[result.direction]+(boss?1:0);result.objectId=ids[result.slot];
    if(result.objectId==-1)return fail("DGN declares no pathgate object for selected direction/state");
    if(result.objectId<0)return fail("Unsupported negative pathgate object ID "+std::to_string(result.objectId));
    const std::string registryPath="passiveobject/passiveobject.lst";
    if(!pvf.has(registryPath))return fail("Missing passiveobject registry");
    const auto registry=pvf.script(registryPath);
    // Do not use map<int,string>: duplicate IDs must retain their provenance
    // and must not silently choose the last registration.
    for(size_t i=0;i+1<registry.tokens.size();++i) {
        const auto &id=registry.tokens[i].at("value"),&literal=registry.tokens[i+1].at("value");
        if(!id.is_number_integer()||!literal.is_string())continue;
        if(id.get<int64_t>()!=result.objectId){++i;continue;}
        const auto object=relative(registryPath,literal.get<std::string>());
        const uint64_t offset=registry.tokens[i].at("offset").get<uint64_t>();
        const auto ref=makeSourceRef(pvf,registryPath,offset,10,i,"registry ID/resource token pair");
        result.registryMatches.push_back({{"object",object},{"literal",literal},{"source",ref.json()}});
        if(result.registryMatches.size()==1){result.object=object;result.registrySource=ref;}
        ++i;
    }
    if(result.registryMatches.empty())return fail("Unregistered pathgate object ID "+std::to_string(result.objectId));
    if(result.registryMatches.size()!=1){result.object.clear();return fail("Ambiguous pathgate object ID "+std::to_string(result.objectId));}
    if(!pvf.has(result.object))return fail("Registered pathgate object is missing: "+result.object);
    if(std::filesystem::u8path(result.object).extension().u8string()!=".obj")return fail("Registered pathgate resource is not an OBJ: "+result.object);
    result.objectSource=makeSourceRef(pvf,result.object,0,0,0,"DGN-selected pathgate OBJ");
    result.available=true;return result;
}
PortalObjectSource resolveDungeonPortalSource(Pvf &pvf,const DungeonDefinition &dungeon,Direction direction,bool boss) {
    auto result=resolveDungeonPortalSource(pvf,dungeon.pathgateObjects,direction,boss);
    if(dungeon.path.empty()||!pvf.has(dungeon.path)) {
        result.available=false;result.diagnostic="DGN pathgate owner source is missing: "+dungeon.path;return result;
    }
    const auto source=pvf.script(dungeon.path);
    size_t fields=0;const Field *pathgates=nullptr;
    for(const auto &field:source.fields)if(normalize(field.tag)=="[pathgate object]"){++fields;pathgates=&field;}
    if(fields!=1||!pathgates||pathgates->values!=Json(dungeon.pathgateObjects)) {
        result.available=false;result.diagnostic="DGN pathgate model differs from its unique source field: "+dungeon.path;return result;
    }
    result.dungeonSource=makeSourceRef(pvf,dungeon.path,pathgates->offset,
        uint64_t(5*(1+pathgates->values.size())),result.slot,"[pathgate object] ten-slot adapter");
    return result;
}
const PortalObjectSource &DungeonPortalSourceCache::resolve(Pvf &pvf,const DungeonDefinition &dungeon,
                                                           Direction direction,bool boss) {
    const Key key{pvf.identity(),dungeon.id,normalize(dungeon.path),int(direction),boss};
    const auto found=sources_.find(key);
    if(found!=sources_.end()){++hits_;return found->second;}
    PortalObjectSource result;
    try {result=resolveDungeonPortalSource(pvf,dungeon,direction,boss);}
    catch(const std::exception &error) {
        result.direction=int(direction);result.boss=boss;result.inputIds=dungeon.pathgateObjects;
        result.diagnostic="Pathgate source resolution failed: "+std::string(error.what());
    }
    return sources_.emplace(key,std::move(result)).first->second;
}
Json DungeonPortalSourceCache::snapshot() const {
    Json rows=Json::array();
    for(const auto &[key,source]:sources_)rows.push_back({{"pvf_identity",std::get<0>(key)},
        {"dungeon_id",std::get<1>(key)},{"dungeon",std::get<2>(key)},{"result",source.snapshot()}});
    return {{"entries",rows},{"resolutions",sources_.size()},{"cache_hits",hits_},
        {"scope","DGN/registry/OBJ source selection cache; no runtime filename fallback"}};
}
Json PortalObjectSource::snapshot() const {
    auto ref=[](const SourceRef &source)->Json{return source.memberPath.empty()?Json():source.json();};
    return {{"available",available},{"classification",classification},{"direction",direction},{"boss",boss},
        {"slot",slot},{"object_id",objectId},{"object",object},{"diagnostic",diagnostic},{"input_ids",inputIds},
        {"dungeon_source",ref(dungeonSource)},{"registry_source",ref(registrySource)},{"object_source",ref(objectSource)},
        {"registry_matches",registryMatches}};
}
PortalVisualPlan portalVisuals(Pvf &pvf,const std::string &object,bool open) {
    PortalVisualPlan plan;plan.source=pvf.script(object);plan.open=open;
    const auto strings=plan.source.values("[string data]"),ints=plan.source.values("[int data]");
    if(strings.empty()&&ints.empty())throw std::runtime_error("Pathgate OBJ has no source visual plan: "+object);
    if(strings.empty()||ints.size()!=strings.size()*2)throw std::runtime_error("Unsupported pathgate source string/int pair count: "+object);
    for(size_t i=0;i<strings.size();++i) {
        if(!strings[i].is_string())throw std::runtime_error("Nonstring pathgate resource");
        const auto path=relative(plan.source.path,strings[i].get<std::string>());
        const auto ext=normalize(std::filesystem::u8path(path).extension().u8string());
        const int a=sourceInt(ints[i*2]),b=sourceInt(ints[i*2+1]);
        if(ext==".til") {plan.tiles.push_back({i,path,{a,b}});continue;}
        if(ext!=".ani"||a<0||a>2||b<0||b>99)throw std::runtime_error("Unsupported pathgate ANI state/variant: "+object);
        if(a==0||a==(open?2:1))plan.tracks.push_back({i,a,b,path});
    }
    if(plan.tracks.empty())throw std::runtime_error("Pathgate selected state has no animations: "+object);
    return plan;
}
std::string portalImageVariant(std::string image,int variant) {
    if(variant<0||variant>99)throw std::runtime_error("Unsupported pathgate IMG variant");
    const auto digits=std::string(1,char('0'+variant/10))+char('0'+variant%10);
    size_t at=0;
    while((at=image.find("%d%d",at))!=std::string::npos){image.replace(at,4,digits);at+=2;}
    return image;
}
bool portalAnimationLoops(const Animation &animation) {
    const auto found=animation.globals.find("0");
    if(found==animation.globals.end())return false;
    if(!found->is_boolean())throw std::invalid_argument("Pathgate ANI LOOP source operand is not boolean: "+animation.path);
    return found->get<bool>();
}
PortalPlaybackTime PortalPlaybackClock::sample(const std::string &scene,const std::string &key,
        const std::string &object,int64_t now,bool open) {
    if(now<0||scene.empty()||key.empty()||object.empty()||scene.size()>8192||key.size()>256||object.size()>8192)
        throw std::invalid_argument("Invalid pathgate simulation identity/clock");
    const bool newScene=scene_!=scene;
    if(newScene){scene_=scene;instances_.clear();}
    const auto existing=instances_.find(key);
    const bool reset=existing==instances_.end()||existing->second.object!=object||now<existing->second.last;
    if(reset) {
        if(existing==instances_.end()&&instances_.size()>=32)throw std::invalid_argument("Pathgate room instance budget exceeded");
        instances_[key]={object,open,now,now,now};return {0,0,true,false};
    }
    auto &state=existing->second;const bool changed=state.open!=open;
    if(changed){state.open=open;state.stateStart=now;}
    state.last=now;return {now-state.commonStart,now-state.stateStart,false,changed};
}
Json PortalPlaybackClock::snapshot() const {
    Json out=Json::array();for(const auto &[key,state]:instances_)out.push_back({{"instance",key},{"object",state.object},
        {"open",state.open},{"common_start_ms",state.commonStart},{"state_start_ms",state.stateStart},{"last_ms",state.last}});
    return {{"policy","inferred-source-pathgate-state-clock-v2"},{"classification","inferred_beta"},{"scene",scene_},
        {"instances",out},{"clock","simulation milliseconds; no render/wall-clock advancement"},{"persistent",false}};
}
Json PortalVisualPlan::snapshot() const {
    Json trackRows=Json::array(),tileRows=Json::array(),fields=Json::array();
    for(const auto &t:tracks)trackRows.push_back({{"ordinal",t.ordinal},{"state",t.state},{"variant",t.imageVariant},{"animation",t.animation}});
    for(const auto &t:tiles)tileRows.push_back({{"ordinal",t.ordinal},{"path",t.path},{"source_pair",t.sourcePair},{"collision_consumer",false}});
    for(const auto &f:source.fields)fields.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    return {{"object",source.path},{"source",source.source},{"raw_bytes",source.rawBytes},{"tokens",source.tokens},{"fields",fields},
        {"classification",classification},{"open",open},{"tracks",trackRows},{"tiles",tileRows},
        {"lifecycle","source LOOP with per-portal simulation state transitions; native controller comparison remains user verification"}};
}
} // namespace dnf
