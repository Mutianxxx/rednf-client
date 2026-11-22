#include "dnf/scene_tiles.hpp"
#include "dnf/scene.hpp"
#include "dnf/content_profile.hpp"
#include <cmath>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
std::string tilePath(const std::string &parent,const std::string &literal) {
    if(literal.empty()||literal.front()=='/'||literal.front()=='\\'||literal.find(':')!=std::string::npos)
        throw std::runtime_error("Invalid source TIL literal");
    const auto resolved=normalize((std::filesystem::u8path(parent).parent_path()/std::filesystem::u8path(literal)).lexically_normal().generic_u8string());
    if(resolved==".."||resolved.rfind("../",0)==0)throw std::runtime_error("Source TIL escapes content root");
    return resolved;
}
Json fields(const Script &source) {
    Json result=Json::array();
    for(const auto &field:source.fields)result.push_back({{"tag",field.tag},{"offset",field.offset},{"values",field.values}});
    return result;
}
struct Tile {
    Script script;
    std::string image,type,dimensionPolicy;
    int frame=0,columns=14,rows=0,width=0;
    double height=0,dx=0,dy=0;
    Pixels pixels;
    Json passes=Json::array(),images=Json::array(),evidence=Json::array(),evidenceErrors=Json::array();
    bool drawable=false,forest=false;
};
class Reader {
    Pvf &pvf_;Assets &assets_;
    std::map<std::string,Tile> cache_;
    std::map<std::string,std::vector<std::string>> neighbors_;
  public:
    Reader(Pvf &p,Assets &a):pvf_(p),assets_(a){}
    Tile raw(const std::string &path) {
        if(const auto found=cache_.find(path);found!=cache_.end())return found->second;
        Tile tile;tile.script=pvf_.script(path);tile.passes=tile.script.values("[pass type]");
        if(tile.passes.empty()||tile.passes.size()%14||tile.passes.size()>140000)
            throw std::runtime_error("Unsupported source TIL pass-grid shape: "+path);
        tile.rows=int(tile.passes.size()/14);
        for(const auto &value:tile.passes)if(!value.is_number_integer()||value<0||value>2)
            throw std::runtime_error("Unsupported source TIL pass code: "+path);
        tile.type=normalize(tile.script.text("[tile type]","[basic]"));
        if(tile.type!="[basic]"&&tile.type!="[extended]")throw std::runtime_error("Unsupported source TIL type: "+path);
        for(const auto &field:tile.script.fields)if(normalize(field.tag)=="[image]") {
            if(field.values.size()!=2||!field.values[0].is_string()||!field.values[1].is_number_integer()||
                field.values[1]<0||field.values[1]>std::numeric_limits<int>::max())
                throw std::runtime_error("Malformed source TIL IMAGE: "+path);
            tile.images.push_back({{"offset",field.offset},{"values",field.values}});
        }
        if(tile.images.empty())throw std::runtime_error("Source TIL has no IMAGE: "+path);
        tile.image=tile.images.front().at("values").at(0);tile.frame=tile.images.front().at("values").at(1);
        if(!tile.image.empty()) {
            const auto pixels=assets_.pixels(tile.image,tile.frame);
            tile.pixels={pixels.width,pixels.height,pixels.x,pixels.y,pixels.logicalWidth,pixels.logicalHeight,{}};
            tile.width=pixels.logicalWidth>0?pixels.logicalWidth:pixels.width;
            tile.height=pixels.logicalHeight>0?pixels.logicalHeight:pixels.height;
            if(tile.width<=0||tile.height<=0||tile.width>100000||tile.height>100000)
                throw std::runtime_error("Invalid source TIL logical canvas: "+path);
            tile.drawable=true;
            const auto image=normalize(tile.image);
            tile.forest=image=="map/01tile00.img"||image=="map/01tile01.img"||
                image=="map/01tile02.img"||image=="map/01tile03.img";
            tile.dimensionPolicy="source-IMG-logical-canvas";
        }
        cache_[path]=tile;return tile;
    }
    Tile resolved(const std::string &path) {
        auto tile=raw(path);
        if(!tile.drawable) {
            if(path=="map/elvengard/tile/dummy.til"&&tile.rows==30) {
                // Preserve the previously validated, narrowly scoped forest dummy.
                tile.width=224;tile.height=480;tile.forest=true;
                tile.dimensionPolicy="existing-elvengard-dummy-14x30-forest-geometry-v1";
                tile.evidence.push_back({{"basis","existing forest source/MAP gate calibration"},{"classification","inferred"}});
            } else {
                const auto directory=std::filesystem::u8path(path).parent_path().generic_u8string();
                if(!neighbors_.count(directory)) {
                    auto &neighbors=neighbors_[directory];
                    for(const auto &candidate:pvf_.paths(directory+"/",".til"))
                        if(std::filesystem::u8path(candidate).parent_path().generic_u8string()==directory)neighbors.push_back(candidate);
                }
                struct Candidate {Tile tile;bool direct=false;};
                std::vector<Candidate> direct,extended;
                for(const auto &candidate:neighbors_.at(directory)) {
                    try {
                        auto peer=raw(candidate);if(!peer.drawable)continue;
                        if(peer.type==tile.type&&peer.rows==tile.rows)direct.push_back({std::move(peer),true});
                        else if(tile.type=="[basic]"&&tile.rows!=30&&peer.type=="[extended]"&&peer.rows==10)
                            extended.push_back({std::move(peer),false});
                    } catch(const std::exception &error) {
                        tile.evidenceErrors.push_back({{"tile",candidate},{"error",error.what()},
                            {"scope","unrequired neighboring evidence; not a substituted current-map dependency"}});
                    }
                }
                const auto &candidates=direct.empty()?extended:direct;
                std::set<std::pair<int,double>> dimensions;
                for(const auto &candidate:candidates)dimensions.emplace(candidate.tile.width,
                    candidate.direct?candidate.tile.height:candidate.tile.height/candidate.tile.rows*tile.rows);
                if(dimensions.size()!=1)throw std::runtime_error("Empty source TIL dimensions missing or ambiguous: "+path+
                    " local dimension candidates="+std::to_string(dimensions.size()));
                tile.width=dimensions.begin()->first;tile.height=dimensions.begin()->second;
                tile.dimensionPolicy=direct.empty()?"inferred-empty-basic-row-height-from-local-extended-grid-v1":
                    "inferred-empty-TIL-canvas-from-same-directory-same-type-and-grid-v1";
                for(const auto &candidate:candidates)tile.evidence.push_back({
                    {"source",makeSourceRef(pvf_,candidate.tile.script.path).json()},
                    {"image",candidate.tile.image},{"frame",candidate.tile.frame},
                    {"grid",{candidate.tile.columns,candidate.tile.rows}},
                    {"image_logical_size",{candidate.tile.width,candidate.tile.height}},
                    {"classification","current-source-dimension-support; blank-TIL-binding-inferred"}});
            }
        }
        tile.dx=double(tile.width)/tile.columns;
        tile.dy=tile.forest?12:tile.height/tile.rows;
        return tile;
    }
};
} // namespace

SceneTileLoadResult loadSceneSourceTiles(Pvf &pvf,Assets &assets,Scene &scene) {
    SceneTileLoadResult result;Reader reader(pvf,assets);
    scene.tiles.clear();scene.sourceTileVisuals.clear();scene.tileGrids=Json::array();scene.walkRects.clear();scene.width=0;
    struct Slot {std::optional<double>x,width,height,nextY;};
    std::vector<Slot> columns;double cursor=0;size_t extendedIndex=0;
    auto diagnose=[&](const char *kind,const Json &record){
        // The exact fields/tokens and complete evidence live once in records.
        // Diagnostics identify that retained record; copying its complete grid
        // repeatedly makes normal map loading and error display unnecessarily
        // expensive for maps with many transparent/extended source slots.
        Json diagnostic={{"kind",kind},{"severity","diagnostic"},{"record_index",result.records.size()}};
        for(const auto *key:{"map_source","source_field_ordinal","source_field_offset","value_index","raw",
            "resolved","tile_source","dimension_policy","error"})
            if(record.contains(key))diagnostic[key]=record.at(key);
        result.diagnostics.push_back(std::move(diagnostic));
    };
    auto consume=[&](const Field &field,size_t ordinal,size_t index,bool extension) {
        const auto &value=field.values.at(index);
        Json record={{"kind",extension?"extended_tile":"tile"},{"map_source",makeSourceRef(pvf,scene.path).json()},
            {"source_field_ordinal",ordinal},{"source_field_offset",field.offset},{"value_index",index},{"raw",value}};
        std::optional<size_t> column;
        if(extension) {if(!columns.empty())column=extendedIndex%columns.size();++extendedIndex;}
        else {columns.push_back({result.columnsResolved?std::optional<double>(cursor):std::nullopt,{},{},{}});column=columns.size()-1;}
        try {
            if(!value.is_string())throw std::runtime_error("Non-string source MAP TIL literal");
            const auto path=tilePath(scene.path,value.get<std::string>());record["resolved"]=path;
            const auto tile=reader.resolved(path);
            record["tile_source"]=makeSourceRef(pvf,path).json();record["tile_fields"]=fields(tile.script);
            record["tile_tokens"]=tile.script.tokens;record["image_variants"]=tile.images;
            record["dimension_policy"]=tile.dimensionPolicy;record["dimension_evidence"]=tile.evidence;
            record["dimension_evidence_errors"]=tile.evidenceErrors;
            record["image_logical_size"]={tile.width,tile.height};record["transparent"]=!tile.drawable;
            if(!column)throw std::runtime_error("Extended source tile has no authored basic columns");
            auto &slot=columns.at(*column);
            if(!extension){slot.width=tile.width;slot.height=tile.height;slot.nextY=scene.bg+tile.height;}
            if(!slot.x||(extension&&!slot.nextY))throw std::runtime_error("Source tile position unresolved after preceding dependency");
            const double x=*slot.x,y=extension?*slot.nextY:scene.bg;
            if(extension&&slot.width&&std::abs(*slot.width-tile.width)>1e-9)
                throw std::runtime_error("Extended source tile width differs from its basic column");
            const auto policy=tile.forest?"existing-four-forest-and-dummy-grid-16x12-v1":
                "inferred-source-logical-dimensions-divided-by-authored-grid-v1";
            Json grid={{"tile",path},{"source",makeSourceRef(pvf,path).json()},{"map_field_ordinal",ordinal},
                {"source_field_offset",field.offset},{"value_index",index},{"extended",extension},
                {"column",*column},{"extended_row",extension?(extendedIndex-1)/columns.size():0},
                {"grid",{tile.columns,tile.rows}},{"cell_size",{tile.dx,tile.dy}},{"origin",{x,y}},
                {"image",tile.image},{"frame",tile.frame},{"image_logical_size",{tile.width,tile.height}},
                {"transparent",!tile.drawable},{"dimension_policy",tile.dimensionPolicy},
                {"dimension_evidence",tile.evidence},{"policy",policy},{"pass_values",tile.passes},
                {"ground_consumer","only pass0; pass1 floating-only and pass2 blocked remain excluded"},
                {"native_pc_parity","pending"}};
            std::array<int,3> counts{};
            for(size_t i=0;i<tile.passes.size();++i) {
                const int pass=tile.passes[i];++counts[pass];
                if(pass==0)scene.walkRects.push_back({x+double(i%tile.columns)*tile.dx,
                    y+double(i/tile.columns)*tile.dy,tile.dx,tile.dy});
            }
            grid["pass_counts"]=counts;scene.tileGrids.push_back(grid);record["grid"]=grid;
            if(tile.drawable) {
                scene.tiles.emplace_back(tile.image,tile.frame,x,y);
                scene.sourceTileVisuals.push_back(sourceTileVisual(path,tile.image,tile.frame,x,y,tile.pixels));
            }
            if(tile.images.size()>1)diagnose("tile_image_variants_first_authored_beta_policy",record);
            if(!tile.drawable)diagnose("transparent_tile_dimensions_inferred",record);
            if(!tile.forest)diagnose("tile_grid_world_footprint_inferred",record);
            if(counts[1])diagnose("source_pass1_preserved_floating_movement_consumer_pending",record);
            if(extension)*slot.nextY+=tile.height;
            else cursor+=tile.width;
        }catch(const std::exception &error){
            result.complete=false;record["error"]=error.what();diagnose("tile_dependency_or_placement_unavailable",record);
            if(extension&&column)columns[*column].nextY.reset();
            else if(!extension&&column&&!columns[*column].width)result.columnsResolved=false;
        }
        result.records.push_back(std::move(record));
    };
    for(size_t f=0;f<scene.script.fields.size();++f)if(normalize(scene.script.fields[f].tag)=="[tile]")
        for(size_t i=0;i<scene.script.fields[f].values.size();++i)consume(scene.script.fields[f],f,i,false);
    if(cursor>std::numeric_limits<int>::max())throw std::runtime_error("Source tile width exceeds Scene API");
    scene.width=int(std::ceil(cursor));
    for(size_t f=0;f<scene.script.fields.size();++f)if(normalize(scene.script.fields[f].tag)=="[extended tile]")
        for(size_t i=0;i<scene.script.fields[f].values.size();++i)consume(scene.script.fields[f],f,i,true);
    return result;
}
} // namespace dnf
