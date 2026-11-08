#include "dnf/business_ui_source.hpp"
#include <cmath>
#include <climits>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
int integer(const Json &v) {
    if(!v.is_number_integer() || (v.is_number_unsigned() && v.get<uint64_t>()>uint64_t(INT_MAX)))
        throw std::runtime_error("UI requires an integer");
    const auto n=v.get<int64_t>();
    if(n<INT_MIN || n>INT_MAX)throw std::runtime_error("UI integer out of range");
    return int(n);
}
size_t count(const Json &values,size_t &at) {
    if(at>=values.size())throw std::runtime_error("UI missing parameter count");
    const int n=integer(values[at++]);
    if(n<0 || size_t(n)>values.size()-at)throw std::runtime_error("UI parameter count exceeds record");
    return size_t(n);
}
}
Json BusinessUiControl::option(const std::string &name) const {
    Json result=Json::array();bool found=false;
    for(const auto &f:options)if(normalize(f.tag)=="[int option]" && !f.values.empty() && f.values[0]==name) {
        if(found)throw std::runtime_error("UI duplicate typed option: "+name);
        found=true;for(size_t i=1;i<f.values.size();++i)if(f.values[i]!="[/int option]")result.push_back(f.values[i]);
    }
    return result;
}
Json BusinessUiControl::snapshot() const {
    Json nested=Json::array();for(const auto &f:options)nested.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    return {{"type",type},{"name",name},{"x",x},{"y",y},{"ordinal",ordinal},{"offset",offset},
        {"strings",strings},{"integers",integers},{"parent",parent},{"parent_kind",parentKind},{"parent_state",parentState},{"options",nested}};
}
BusinessUiLayout readBusinessUiLayout(Script source) {
    BusinessUiLayout result;result.source=std::move(source);BusinessUiControl *current=nullptr;
    for(size_t ordinal=0;ordinal<result.source.fields.size();++ordinal) {
        const auto &f=result.source.fields[ordinal];const auto tag=normalize(f.tag);
        if(tag=="[ui controls]") {
            if(current)throw std::runtime_error("UI nested control: "+result.source.path);
            const auto &v=f.values;
            if(v.size()<6 || !v[0].is_string() || !v[1].is_string() || !v[2].is_number() || !v[3].is_number())
                throw std::runtime_error("UI malformed control: "+result.source.path);
            BusinessUiControl c;c.type=normalize(v[0]);c.name=v[1];c.x=v[2];c.y=v[3];c.ordinal=ordinal;c.offset=f.offset;
            if(!std::isfinite(c.x)||!std::isfinite(c.y)||std::abs(c.x)>1000000||std::abs(c.y)>1000000)
                throw std::runtime_error("UI invalid coordinate");
            size_t at=4,n=count(v,at);for(size_t i=0;i<n;++i){if(!v[at].is_string())throw std::runtime_error("UI nonstring parameter");c.strings.push_back(v[at++]);}
            n=count(v,at);for(size_t i=0;i<n;++i)c.integers.push_back(integer(v[at++]));
            if(at!=v.size())throw std::runtime_error("UI uncounted parameter");
            result.controls.push_back(std::move(c));current=&result.controls.back();
        } else if(tag=="[/ui controls]") {
            if(!current || !f.values.empty())throw std::runtime_error("UI unmatched control end");current=nullptr;
        } else if(current) {
            current->options.push_back(f);
            if(tag=="[parent]" || tag=="[parent tab]" || tag=="[parent radio]") {
                if(!current->parent.empty()||f.values.empty()||!f.values[0].is_string())throw std::runtime_error("UI malformed parent");
                current->parent=f.values[0];current->parentKind=tag;
                if(tag!="[parent]") {if(f.values.size()!=2)throw std::runtime_error("UI parent state missing");current->parentState=integer(f.values[1]);}
            }
        } else if(tag=="[ui path]") {
            if(f.values.size()!=2||!f.values[0].is_string()||!f.values[1].is_string())throw std::runtime_error("UI malformed child path");
            result.children.emplace_back(normalize(f.values[0]),f.values[1]);
        }
    }
    if(current)throw std::runtime_error("UI unterminated control");
    for(const auto &c:result.controls)if(!c.parent.empty())result.position(c); // cycles/missing parent fail early
    for(const auto &c:result.children)result.require(c.second);
    return result;
}
const BusinessUiControl &BusinessUiLayout::require(const std::string &name,const std::string &type) const {
    if(name=="-1")throw std::runtime_error("Anonymous UI IDs require ordinal lookup");
    const BusinessUiControl *found=nullptr;
    for(const auto &c:controls)if(c.name==name){if(found)throw std::runtime_error("UI ambiguous named control: "+source.path+":"+name);found=&c;}
    if(!found||(!type.empty()&&found->type!=type))throw std::runtime_error("UI missing/unsupported control: "+source.path+":"+name);
    return *found;
}
std::array<int,2> BusinessUiLayout::position(const BusinessUiControl &control) const {
    double x=control.x,y=control.y;std::set<const BusinessUiControl *> seen{&control};const auto *c=&control;
    while(!c->parent.empty()) {
        const auto *child=c;c=&require(c->parent);if(!seen.insert(c).second)throw std::runtime_error("UI cyclic parent");x+=c->x;y+=c->y;
        // In this 1031 schema each radio state carries four frames plus x/y.
        // Child origins include that state's offset (SP -15; TP -145+130).
        if(child->parentKind=="[parent radio]"&&c->type=="[radiobutton]") {
            if(c->integers.empty()||child->parentState<0||child->parentState>=c->integers[0]||c->integers.size()!=size_t(2+6*c->integers[0]))
                throw std::runtime_error("UI unsupported radio-parent schema");
            const auto at=1+6*child->parentState;x+=c->integers.at(at+4);y+=c->integers.at(at+5);
        }
    }
    if(!std::isfinite(x)||!std::isfinite(y)||std::abs(x)>1000000||std::abs(y)>1000000)throw std::runtime_error("UI parent coordinate overflow");
    return {int(std::lround(x)),int(std::lround(y))};
}
Json BusinessUiLayout::snapshot() const {
    Json controlsJson=Json::array(),fields=Json::array();for(const auto &c:controls)controlsJson.push_back(c.snapshot());
    for(const auto &f:source.fields)fields.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    return {{"path",source.path},{"source",source.source},{"raw_bytes",source.rawBytes},{"tokens",source.tokens},
        {"fields",fields},{"controls",controlsJson},{"children",children}};
}
BusinessUiGrid BusinessUiGrid::from(const BusinessUiLayout &layout,const std::string &name) {
    const auto &c=layout.require(name,"[grid]");const auto p=layout.position(c);const auto grid=c.option("[grid data]"),cell=c.option("[cell basic data]"),margin=c.option("[cell margin]");
    if(grid.size()!=2||cell.size()!=4||margin.size()!=1)throw std::runtime_error("UI unsupported grid schema");
    BusinessUiGrid result{p[0]+integer(cell[0]),p[1]+integer(cell[1]),integer(grid[0]),integer(grid[1]),integer(cell[2]),integer(cell[3]),integer(margin[0])};
    if(result.columns<=0||result.rows<=0||result.columns>100||result.rows>100||result.cellWidth<=0||result.cellHeight<=0||result.margin<0)
        throw std::runtime_error("UI invalid grid dimensions");
    return result;
}
std::array<int,2> BusinessUiGrid::cell(int ordinal) const {
    if(ordinal<0||ordinal>=perPage())throw std::runtime_error("UI grid cell out of range");
    return {x+(ordinal%columns)*(cellWidth+margin),y+(ordinal/columns)*(cellHeight+margin)};
}
int BusinessUiGrid::hit(int mx,int my) const {
    for(int i=0;i<perPage();++i){auto p=cell(i);if(mx>=p[0]&&my>=p[1]&&mx<p[0]+cellWidth&&my<p[1]+cellHeight)return i;}return -1;
}
int BusinessUiPage::pages(int count,int pageSize) {if(count<0||pageSize<=0)throw std::runtime_error("Invalid UI page dimensions");return std::max(1,count/pageSize+(count%pageSize!=0));}
int BusinessUiPage::clamp(int page,int count,int pageSize) {return std::clamp(page,0,pages(count,pageSize)-1);}
std::vector<int> BusinessUiPage::indices(int page,int count,int pageSize) {
    std::vector<int> out;page=clamp(page,count,pageSize);for(int i=page*pageSize;i<std::min(count,page*pageSize+pageSize);++i)out.push_back(i);return out;
}
void BusinessUiSources::bind(Pvf &pvf) {
    std::map<std::string,BusinessUiLayout> layouts;
    for(const auto *path:{"ui/inventory/iteminventorywindow.ui","ui/inventory/inventory_item.ui","ui/inventory/inventory_avatar.ui",
            "ui/inventory/inventory_bottom.ui","ui/inventory/inventory_item_control_group.ui","ui/inventory/inventory_avatar_control_group.ui",
            "ui/skill/skillshopwindow.ui","ui/skill/skillshopsppage.ui","ui/skill/skillshoptppage.ui","ui/skill/skillshopexplain.ui"})
        layouts.emplace(path,readBusinessUiLayout(pvf.script(path)));
    auto portraits=pvf.script("etc/dialogwindowimageindex.etc");
    const auto pairs=portraits.values("[npc image index pair]");
    if(pairs.empty()||!pairs[0].is_string()||pairs.size()%2!=1)throw std::runtime_error("UI invalid NPC portrait map");
    std::set<int> ids;for(size_t i=1;i<pairs.size();i+=2){if(!ids.insert(integer(pairs[i])).second)throw std::runtime_error("UI duplicate NPC portrait ID");integer(pairs[i+1]);}
    layouts_=std::move(layouts);portraits_=std::move(portraits);pvf_=&pvf;
}
const BusinessUiLayout &BusinessUiSources::layout(const std::string &path) const {
    const auto it=layouts_.find(normalize(path));if(it==layouts_.end())throw std::runtime_error("UI source not bound: "+path);return it->second;
}
std::pair<std::string,int> BusinessUiSources::portrait(int npc) const {
    const auto v=portraits_.values("[npc image index pair]");for(size_t i=1;i+1<v.size();i+=2)if(v[i]==npc)return {v[0],integer(v[i+1])};return {"",-1};
}
Json BusinessUiSources::snapshot() const {
    Json layouts=Json::array();for(const auto &[path,l]:layouts_)layouts.push_back(l.snapshot());
    return {{"classification","1031 source envelopes, hierarchy and sprite bindings; event/layout adapters reconstructed"},{"layouts",layouts},
        {"portrait_source",portraits_.source},{"portrait_path",portraits_.path},{"portrait_bytes",portraits_.rawBytes},{"portrait_tokens",portraits_.tokens}};
}
Json runBusinessUiSourceTests(Pvf &pvf) {
    int checks=0;auto check=[&](bool good,const std::string &message){++checks;if(!good)throw std::runtime_error("Business UI test: "+message);};
    BusinessUiSources sources;sources.bind(pvf);
    const auto &root=sources.layout("ui/inventory/iteminventorywindow.ui"),&item=sources.layout("ui/inventory/inventory_item.ui"),&avatar=sources.layout("ui/inventory/inventory_avatar.ui");
    check(root.position("1")==std::array<int,2>{0,-3},"inventory parent tab coordinates");
    auto grid=BusinessUiGrid::from(item,"1114");check(grid.columns==8&&grid.rows==4&&grid.cellWidth==30&&grid.cellHeight==30,"source item grid");
    check(BusinessUiGrid::from(avatar,"2110").perPage()==28,"source avatar grid");
    for(int i=0;i<grid.perPage();++i){auto p=grid.cell(i);check(grid.hit(p[0]+1,p[1]+1)==i,"grid hit cell");check(grid.hit(p[0]+29,p[1]+29)==i,"grid bottom edge");}
    check(grid.hit(grid.x-1,grid.y)==-1,"grid outside");
    check(sources.layout("ui/inventory/inventory_item_control_group.ui").controls.size()==12,"all 12 source equipment slots retained");
    check(sources.portrait(1)==std::make_pair(std::string("Interface/NPC_Dialog_Face.img"),0),"Linus portrait");
    check(sources.portrait(2).second==1,"Seria portrait");check(sources.portrait(100).second==-2,"negative portrait sentinel retained");check(sources.portrait(-99).second==-1,"unmapped portrait");
    for(int total:{0,1,5,6,7,31,100})for(int size:{5,6,9,32}){
        std::vector<int> covered;for(int page=0;page<BusinessUiPage::pages(total,size);++page){auto ids=BusinessUiPage::indices(page,total,size);covered.insert(covered.end(),ids.begin(),ids.end());}
        check(int(covered.size())==total,"no inaccessible row");for(int i=0;i<total;++i)check(covered[i]==i,"page ordering no duplicates");
    }
    auto malformed=item.source;malformed.fields.front().values=Json::array({"[grid]","broken",0,0,99});bool rejected=false;try{readBusinessUiLayout(malformed);}catch(...){rejected=true;}check(rejected,"malformed source rejected");
    auto cycle=root.source;for(auto &f:cycle.fields)if(f.tag=="[parent tab]"&&f.values[1]==0)f.values[0]="1";
    rejected=false;try{readBusinessUiLayout(cycle);}catch(...){rejected=true;}check(rejected,"parent cycle rejected");
    return {{"status","passed"},{"checks",checks},{"sources",sources.snapshot()},{"scope","source parsing, hierarchy, grids, complete row reachability, portrait sentinels; user visual checks pending"}};
}
} // namespace dnf
