#include "dnf/region.hpp"
#include <functional>
#include <queue>
#include <sstream>
namespace dnf {
namespace {
constexpr const char *version="pcg32-source-topology-v2";
struct Edge {int left,right,bit,otherBit;};
using Domains=std::vector<std::vector<int>>;
bool propagate(Domains &domains,const std::vector<Edge>&edges) {
    bool changed=true;while(changed){changed=false;for(const auto&e:edges)for(int side=0;side<2;++side){
        const int x=side?e.right:e.left,y=side?e.left:e.right,xb=side?e.otherBit:e.bit,yb=side?e.bit:e.otherBit;
        auto &dx=domains[x];const auto &dy=domains[y];const auto before=dx.size();
        dx.erase(std::remove_if(dx.begin(),dx.end(),[&](int mask){return std::none_of(dy.begin(),dy.end(),[&](int other){return bool(mask&xb)==bool(other&yb);});}),dx.end());
        if(dx.empty())return false;changed|=dx.size()!=before;
    }}return true;
}
bool connected(const Domains&domains,const std::vector<Edge>&edges,int start,int boss,bool complete) {
    std::vector<bool> reached(domains.size());std::queue<int> q;reached[start]=true;q.push(start);
    while(!q.empty()){int x=q.front();q.pop();for(const auto&e:edges){
        if(e.left!=x&&e.right!=x)continue;const int y=e.left==x?e.right:e.left,bit=e.left==x?e.bit:e.otherBit,other=e.left==x?e.otherBit:e.bit;
        if(std::none_of(domains[x].begin(),domains[x].end(),[&](int m){return bool(m&bit);})||std::none_of(domains[y].begin(),domains[y].end(),[&](int m){return bool(m&other);}))continue;
        if(!reached[y]){reached[y]=true;q.push(y);}
    }}
    if(!reached[boss])return false;
    for(size_t i=0;i<domains.size();++i){bool mandatory=complete?domains[i][0]!=0:std::find(domains[i].begin(),domains[i].end(),0)==domains[i].end();if(mandatory&&!reached[i])return false;}
    return true;
}
}
DungeonRun generateSourceDungeon(const RegionCatalog&catalog,int id,uint64_t seed) {
    const auto &d=catalog.dungeons.at(id);if(!d.enabled)throw std::runtime_error("Source dungeon capability unavailable: "+d.lockedReason);
    RandomStreams streams(seed);auto &random=streams.stream(RandomDomain::WorldGeneration);
    auto shuffle=[&](auto &v){for(size_t i=v.size();i>1;--i)std::swap(v[i-1],v[size_t(random.bounded64(i))]);};
    struct Scenario{size_t maze;int start,boss;};std::vector<Scenario> scenarios;Json failures=Json::array();
    for(size_t mi=0;mi<d.mazes.size();++mi){const auto&m=d.mazes[mi];
        if(m.width<1||m.height<1||m.width>128||m.height>128||m.doorMasks.size()!=size_t(m.width*m.height)){failures.push_back({{"maze",mi},{"code","greed_dimensions"}});continue;}
        for(const auto&s:m.starts)for(const auto&b:m.bosses){if(s[0]<0||s[1]<0||s[0]>=m.width||s[1]>=m.height||b[0]<0||b[1]<0||b[0]>=m.width||b[1]>=m.height)continue;
            const int start=s[1]*m.width+s[0],boss=b[1]*m.width+b[0];if(start==boss&&m.width*m.height!=1)continue;scenarios.push_back({mi,start,boss});}
    }shuffle(scenarios);
    // Bound the actual constraint work, not the number of theoretical edge
    // subsets. Source DGN/MAP closure is never weakened on budget exhaustion.
    constexpr size_t budget=250000;size_t nodes=0;
    for(const auto scenario:scenarios){const auto &m=d.mazes[scenario.maze];const int n=m.width*m.height;std::vector<Edge> edges;std::vector<int> possible(n);
        for(int y=0;y<m.height;++y)for(int x=0;x<m.width;++x){const int c=y*m.width+x;
            if(x+1<m.width&&(m.doorMasks[c]&1)&&(m.doorMasks[c+1]&4)){edges.push_back({c,c+1,1,4});possible[c]|=1;possible[c+1]|=4;}
            if(y+1<m.height&&(m.doorMasks[c]&8)&&(m.doorMasks[c+m.width]&2)){edges.push_back({c,c+m.width,8,2});possible[c]|=8;possible[c+m.width]|=2;}
        }
        Domains domains(n);Json missing=Json::array();
        for(int cell=0;cell<n;++cell){for(int mask=1;mask<=15;++mask)if(!(mask&~possible[cell])&&!dungeonRoomCandidates(catalog,id,m,cell,mask,cell==scenario.boss,version).empty())domains[cell].push_back(mask);
            shuffle(domains[cell]);if(n==1&&!dungeonRoomCandidates(catalog,id,m,cell,0,true,version).empty())domains[cell].push_back(0);
            if(cell!=scenario.start&&cell!=scenario.boss)domains[cell].push_back(0);
            if(domains[cell].empty())missing.push_back({{"cell",cell},{"source_mask",m.doorMasks[cell]},{"reciprocal_mask",possible[cell]}});
        }
        if(!missing.empty()){failures.push_back({{"maze",scenario.maze},{"start",scenario.start},{"boss",scenario.boss},{"code","endpoint_candidate_empty"},{"cells",missing}});continue;}
        std::function<bool(Domains&)> solve=[&](Domains &current){if(++nodes>budget)return false;if(!propagate(current,edges)||!connected(current,edges,scenario.start,scenario.boss,false))return false;
            int chosen=-1;for(int c=0;c<n;++c)if(current[c].size()>1&&(chosen<0||current[c].size()<current[chosen].size()))chosen=c;
            if(chosen<0)return connected(current,edges,scenario.start,scenario.boss,true);
            const auto options=current[chosen];for(int mask:options){Domains next=current;next[chosen]={mask};if(solve(next)){current=std::move(next);return true;}if(nodes>budget)return false;}return false;
        };
        if(!solve(domains)){failures.push_back({{"maze",scenario.maze},{"start",scenario.start},{"boss",scenario.boss},{"code",nodes>budget?"constraint_budget":"source_constraints_unsatisfied"},{"nodes",nodes}});if(nodes>budget)break;continue;}
        DungeonRun run;run.dungeonId=id;run.seed=seed;run.width=m.width;run.height=m.height;run.generatorVersion=version;run.token=std::to_string(id)+":"+std::to_string(seed);
        for(int cell=0;cell<n;++cell)if(domains[cell][0]||n==1){RunRoom room;room.x=cell%m.width;room.y=cell/m.width;room.doors=domains[cell][0];room.boss=cell==scenario.boss;
            room.candidates=dungeonRoomCandidates(catalog,id,m,cell,room.doors,room.boss,version);room.mapId=room.candidates[size_t(random.bounded64(room.candidates.size()))];room.path=catalog.maps.at(room.mapId).path;
            if(cell==scenario.start)run.start=run.current=int(run.rooms.size());if(cell==scenario.boss)run.boss=int(run.rooms.size());run.rooms.push_back(std::move(room));}
        run.room().visited=true;run.randomState=streams.snapshot();return run;
    }
    throw std::runtime_error("No source-compatible topology: "+Json{{"dungeon",id},{"path",d.path},{"generator",version},{"budget",budget},{"nodes",nodes},{"failures",failures}}.dump());
}
}
