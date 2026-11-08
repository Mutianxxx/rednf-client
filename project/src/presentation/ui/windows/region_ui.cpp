#include "dnf/region_ui.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/business_ui_render.hpp"
#include "dnf/world_map_ui.hpp"
#include <regex>
namespace dnf {
void sourceWindow(Renderer &r,int x,int y,int w,int h) {
    for(int row=0;row<3;++row)for(int col=0;col<3;++col) {
        int xx=x+(col==0?0:col==1?11:w-11), yy=y+(row==0?0:row==1?11:h-11);
        r.sprite("interface/windowcommon.img",row*3+col,xx,yy,1,col==1?(w-22)/12.0:1,
                 0,255,0,false,row==1?(h-22)/13.0:1);
    }
}
static std::string plain(std::string s) {
    s=std::regex_replace(s,std::regex("<[^>]*>"),"");
    size_t p=0;while((p=s.find("\\n",p))!=std::string::npos)s.replace(p,2,"\n");return s;
}
static void wrapped(Renderer &r,std::string s,int x,int y,int width,int lines=4,int size=15) {
    s=plain(s); std::string line;int n=0;
    auto flush=[&]{r.text(line,float(x),float(y+n*(size+5)),size);line.clear();++n;};
    for(size_t i=0;i<s.size()&&n<lines;) {
        unsigned char ch=s[i];size_t len=ch<128?1:ch<224?2:ch<240?3:4;
        if(ch=='\n'){++i;flush();continue;}
        const auto glyph=s.substr(i,len);
        if(!line.empty()&&r.textWidth(line+glyph,size)>width)flush();
        if(n>=lines)break;line+=glyph;i+=len;
    }
    if(!line.empty()&&n<lines)flush();
}
void RegionUi::openNpc(int id,Progression &p) { npc=id;panel=RegionPanel::NpcMenu;shopPage_=npcMenuPage_=npcQuestPage_=textPage_=dialogueIndex_=0;questSelection_=-1;dialogueAdvanceRequested_=false;message.clear();p.talkNpc(id);changed=true; }
void RegionUi::minimap(Renderer &r,const RegionSession &s,bool expanded) {
    if(!s.active())return;
    drawSourceDungeonMinimap(r,s.run,expanded,int64_t(SDL_GetTicks64()));
}
bool RegionUi::townMinimap(Renderer &r,const std::vector<TownArea> &areas,int areaId,double playerX,
                           double playerY,int sceneWidth,int sceneHeight,const std::string &title,
                           const std::vector<MapNpc> &npcs,int mx,int my,bool click) {
    struct AreaBox { int id; double x0=0,y0=0,x1=0,y1=0; };
    std::vector<AreaBox> boxes;
    double minX=1e9,minY=1e9,maxX=-1e9,maxY=-1e9;
    for (const auto &area : areas) {
        AreaBox box; box.id=area.id; bool found=false;
        for (size_t i=0;i+4<area.raw.size();++i)
            if (area.raw[i]=="[minimap rect]") {
                box.x0=area.raw[i+1];box.y0=area.raw[i+2];box.x1=area.raw[i+3];box.y1=area.raw[i+4];
                found=box.x1>box.x0&&box.y1>box.y0;break;
            }
        if (!found) continue;
        boxes.push_back(box);
        minX=std::min(minX,box.x0);minY=std::min(minY,box.y0);
        maxX=std::max(maxX,box.x1);maxY=std::max(maxY,box.y1);
    }
    if (boxes.empty()) return minimapVisible_;
    // Source town minimap: frame 0 of interface/minimap_minimap_town.img is the
    // full parchment act map (640x424). TWN [minimap rect] entries index that
    // same canvas, so the panel crops around the active area. Frames 7/22 are
    // the source cyan/yellow marker rings used for the player and NPCs.
    const double canvasW=640,canvasH=424;
    const double panelW=128,titleH=15;
    const double panelX=800-panelW-12,panelY=32;
    const double bodyH=minimapVisible_?84.0:0.0;
    r.rect(float(panelX),float(panelY),float(panelW),float(titleH+bodyH),{13,11,9,225});
    r.rect(float(panelX),float(panelY),float(panelW),float(titleH+bodyH),{176,158,110,255},false);
    r.rect(float(panelX+1),float(panelY+1),float(panelW-2),float(titleH-1),{30,27,22,240});
    r.text(title,float(panelX+6),float(panelY+2),11,{238,222,178,255});
    // Panel toggle: the source town map keeps this control on the panel itself.
    // Glyph is drawn (no dedicated source frame for the collapse state exists in
    // this IMG), but it stays inside the title bar like the source button.
    const double bx=panelX+panelW-15,by=panelY+1;
    const bool hover=mx>=int(bx)&&mx<int(bx)+13&&my>=int(by)&&my<int(by)+13;
    r.rect(float(bx),float(by),13,13,hover?SDL_Color{84,72,44,255}:SDL_Color{48,42,30,255});
    r.rect(float(bx),float(by),13,13,{168,150,104,255},false);
    {
        const double cy=by+6.5;
        if (minimapVisible_)
            r.rect(float(bx)+3,float(cy)-1,7,2,{226,208,160,255});
        else {
            r.rect(float(bx)+5,float(cy)-3,2,7,{226,208,160,255});
            r.rect(float(bx)+5,float(cy)-1,6,2,{226,208,160,255});
        }
    }
    if (click&&hover) minimapVisible_=!minimapVisible_;
    if (!minimapVisible_) return false;

    auto current=std::find_if(boxes.begin(),boxes.end(),[&](const AreaBox &b){return b.id==areaId;});
    const double cxc=current!=boxes.end()?(current->x0+current->x1)*0.5:(minX+maxX)*0.5;
    const double cyc=current!=boxes.end()?(current->y0+current->y1)*0.5:(minY+maxY)*0.5;
    const double margin=12;
    double sw=std::min(canvasW,std::max(current!=boxes.end()?current->x1-current->x0+2*margin:200.0,190.0));
    double sh=std::min(canvasH,std::max(current!=boxes.end()?current->y1-current->y0+2*margin:140.0,128.0));
    const double sx=std::clamp(cxc-sw*0.5,0.0,canvasW-sw);
    const double sy=std::clamp(cyc-sh*0.5,0.0,canvasH-sh);
    const double bodyY=panelY+titleH,innerW=panelW-6,innerH=bodyH-4;
    const double sc=std::min(innerW/sw,innerH/sh);
    const double dw=sw*sc,dh=sh*sc;
    const double dx=panelX+(panelW-dw)*0.5,dy=bodyY+(bodyH-dh)*0.5;
    r.imageRegion("interface/minimap_minimap_town.img",0,
                  SDL_Rect{int(sx),int(sy),int(sw),int(sh)},
                  float(dx),float(dy),float(dw),float(dh),{255,255,255,255});
    auto project=[&](double wx,double wy,double &ox,double &oy) {
        const double nx=sceneWidth>0?std::clamp(wx/std::max(1,sceneWidth),0.0,1.0):0.5;
        const double ny=sceneHeight>0?std::clamp(wy/std::max(1,sceneHeight),0.0,1.0):0.5;
        const double ax=current!=boxes.end()?current->x0:(minX+maxX)*0.5-1;
        const double ay=current!=boxes.end()?current->y0:(minY+maxY)*0.5-1;
        const double aw=current!=boxes.end()?current->x1-current->x0:2;
        const double ah=current!=boxes.end()?current->y1-current->y0:2;
        ox=dx+(ax+aw*nx-sx)*sc;oy=dy+(ay+ah*ny-sy)*sc;
    };
    for (const auto &npc : npcs) {
        if (!npc.visible) continue;
        double ox,oy;project(npc.x,npc.y,ox,oy);
        if(ox<dx||ox>dx+dw||oy<dy||oy>dy+dh)continue;
        r.sprite("interface/minimap_minimap_town.img",22,float(ox)-4,float(oy)-4,1,0.18,0,220);
    }
    double px,py;project(playerX,playerY,px,py);
    r.sprite("interface/minimap_minimap_town.img",7,float(px)-7,float(py)-7,1,0.32,0,235);
    r.rect(float(px)-1,float(py)-1,2,2,{130,225,255,255});
    return true;
}
int RegionUi::drawDungeon(Renderer &r,const Progression &p,int mx,int my,bool click) {
    r.sprite("worldmap/lorien.img",0,0,0,1,1,0,255,0,false);
    for(const auto &[id,d]:p.catalog().dungeons) {
        int x=d.worldX-100,y=d.worldY-100;
        r.sprite("worldmap/selectdungeon02.img",1,x,y,1,1,0,255,0,false);
        bool enabled=d.enabled&&(p.level()>=d.minimumLevel);
        if(dungeon==id)r.sprite("worldmap/selectdungeon02.img",23,x+18,y+22,1,1,0,255,0,false);
        wrapped(r,d.name,x+20,y+30,165,1,18);
        r.text("Lv."+std::to_string(d.minimumLevel)+(enabled?"  普通级":"  未开放"),float(x+24),float(y+60),13,
               enabled?SDL_Color{243,218,146,255}:SDL_Color{164,155,146,255});
        if(click&&mx>=x&&mx<x+200&&my>=y&&my<y+107)dungeon=id;
    }
    const auto &d=p.catalog().dungeons.at(dungeon);
    sourceWindow(r,220,492,360,99);
    r.text(d.name,242,507,19);
    bool enabled=d.enabled&&p.level()>=d.minimumLevel;
    if(r.button("进入地下城",325,549,150,28,mx,my,click,enabled))return dungeon;
    if(!enabled)r.text(d.enabled?"角色等级不足":("需要 Lv."+std::to_string(d.minimumLevel)+"；本版本未开放"),240,532,13);
    return 0;
}
namespace {
// Source menu frames were inspected in the current 1031 popup.img. Their
// placement and event dispatch are reconstructed; popups02 is a social menu.
bool npcMenuButton(Renderer &r,int frame,int x,int y,int mx,int my,bool click,bool enabled=true) {
    const bool hover=enabled&&mx>=x&&mx<x+100&&my>=y&&my<y+21;
    r.sprite("interface2/popup/popup.img",frame+(hover?1:0),x,y,1,1,0,enabled?255:110);
    return hover&&click;
}
std::vector<std::pair<int,std::string>> dialogueParts(const NpcDefinition &n,int level) {
    std::vector<std::pair<int,std::string>> result{{n.id,n.source.text("[quest speech]","你好，冒险家。")}};
    for(const auto &f:n.source.fields)if(normalize(f.tag)=="[dialog]"&&f.values.size()>=7&&f.values[1].is_number_integer()&&f.values[2].is_number_integer()) {
        if(level<int(f.values[1])||level>int(f.values[2]))continue;
        // Only ordinary condition-zero records can enter this offline adapter.
        // Favor/dungeon-dependent dialogue retains its source without a guessed gate.
        if(!f.values[4].is_number_integer()||int(f.values[4])!=0)continue;
        if(f.values.size()>7)continue;
        if(!f.values[6].is_string())continue;
        const std::string text=f.values[6];size_t at=0;int speaker=n.id;
        while(at<text.size()) {
            if(text.compare(at,6,"<npc::")==0){auto end=text.find('>',at);if(end!=std::string::npos){try{speaker=std::stoi(text.substr(at+6,end-at-6));}catch(...){speaker=n.id;}at=end+1;}}
            auto end=text.find("<npc::",at);std::string part=text.substr(at,end==std::string::npos?std::string::npos:end-at);
            if(!businessUiPlain(part).empty())result.emplace_back(speaker,part);
            if(end==std::string::npos)break;at=end;
        }
    }
    return result;
}
}
void RegionUi::draw(Renderer &r,World &w,Progression &p,const RegionSession &session,const CharacterAppearance &appearance,int mx,int my,bool click,bool activate) {
    changed=false;returnTown=false;equipmentPublished=false;learnSkillsRequested=false;advancementRequested.reset();if(!open())return;
    if(panel==RegionPanel::Inventory){inventory(r,w,p,appearance,mx,my,click,activate);return;}
    auto operate=[&](const Operation &o){message=o.message;changed=changed||o.ok;};
    if(panel==RegionPanel::Advancement){
        sourceWindow(r,163,95,475,450);r.text("G.S.D · 转职与觉醒",183,117,20);
        if(r.button("×",600,107,23,23,mx,my,click)){close();return;}
        r.text("当前等级 "+std::to_string(p.level())+"    达到等级即可设置",184,154,14);
        int yy=192;bool any=false;
        for(const auto &[identity,option]:w.advancementCatalog().options())if(identity.jobId==w.identity().jobId){
            any=true;const bool current=identity==w.identity();
            const auto label=option.name+"  Lv."+std::to_string(option.requiredLevel)+(current?"  [当前]":"");
            if(r.button(businessUiFitted(r,label,400,14),184,yy,431,31,mx,my,click,
                !current&&p.level()>=option.requiredLevel&&!w.debugOverrides().enabled))advancementRequested=identity;
            yy+=35;
        }
        if(!any)r.text("当前职业没有可核对的转职或觉醒来源。",184,202,14);
        r.text("已学习等级、点数和装备保留；不匹配的技能暂停生效。",184,482,11);
        if(!message.empty())r.text(businessUiFitted(r,message,430,12),184,512,12,{236,213,151,255});
        return;
    }
    if(panel==RegionPanel::NpcMenu||panel==RegionPanel::Npc||panel==RegionPanel::Shop){
        const auto it=p.catalog().npcs.find(npc);if(it==p.catalog().npcs.end()){close();return;}const auto &n=it->second;
        auto quests=p.availableQuests(npc);
        if(panel==RegionPanel::NpcMenu){
            const bool gsd=w.advancementCatalog().isTrainer(npc);
            sourceWindow(r,332,158,144,gsd?244:206);r.text(businessUiFitted(r,n.name,120,14),344,173,14);
            if(r.button("×",451,163,18,20,mx,my,click)){close();return;}
            int yy=204;
            if(npcMenuButton(r,47,354,yy,mx,my,click)){panel=RegionPanel::Npc;questSelection_=-1;textPage_=dialogueIndex_=0;}yy+=26;
            if(npcMenuButton(r,41,354,yy,mx,my,click,!quests.empty())){panel=RegionPanel::Npc;questSelection_=int(quests.front().at("id"));textPage_=0;}yy+=26;
            if(npcMenuButton(r,44,354,yy,mx,my,click,n.shop>=0&&n.unavailableReason.empty())){panel=RegionPanel::Shop;shopPage_=0;}yy+=26;
            if(npcMenuButton(r,128,354,yy,mx,my,click,!n.source.values("[skill]").empty())){learnSkillsRequested=true;close();}yy+=26;
            if(gsd&&r.button("转职 / 觉醒",341,yy,126,25,mx,my,click)){panel=RegionPanel::Advancement;return;}
            if(gsd)yy+=30;
            if(!n.unavailableReason.empty())businessUiTextPages(r,n.unavailableReason,300,379,230,4,0,mx,my,false,12);
            else if(n.shop<0)r.text("此NPC没有物品商店",339,yy+7,11,{155,151,140,255});
            return;
        }
        if(panel==RegionPanel::Npc){
            // Source 718x165 dialogue backing plus mapped 194x248 portrait.
            r.sprite("interface/npc_dialog_ui.img",0,41,378);
            int speaker=npc;std::string speech;
            const auto parts=dialogueParts(n,p.level());dialogueIndex_=std::clamp(dialogueIndex_,0,int(parts.size())-1);
            const Json *selectedQuest=nullptr;
            const auto resolveSpeech=[&] {
                speaker=npc;selectedQuest=nullptr;
                for(const auto &q:quests)if(int(q.at("id"))==questSelection_)selectedQuest=&q;
                if(selectedQuest)speech=selectedQuest->value("description",std::string());
                else{speaker=parts[dialogueIndex_].first;speech=parts[dialogueIndex_].second;}
            };
            resolveSpeech();
            const auto pageCount=BusinessUiPage::pages(int(businessUiLines(r,speech,465,14).size()),4);
            const bool pointerContinue=click&&mx>=41&&mx<759&&my>=378&&my<541&&
                !(pageCount>1&&my>=495&&my<519);
            const bool advance=dialogueAdvanceRequested_||pointerContinue;
            dialogueAdvanceRequested_=false;
            if(advance) {
                if(textPage_+1<pageCount)++textPage_;
                else if(!selectedQuest&&dialogueIndex_+1<int(parts.size())) {++dialogueIndex_;textPage_=0;}
                else if(selectedQuest) {questSelection_=-1;textPage_=0;}
                else {close();return;}
                // Publish the new speaker and text in this same draw. Do not
                // clamp its fresh page against the previous segment's length.
                resolveSpeech();
            }
            auto face=uiSources_.portrait(speaker);
            if(!face.first.empty()&&face.second>=0)r.sprite(face.first,face.second,52,292);
            else {auto fallback=n.source.values("[big face]");if(fallback.size()>=2&&fallback[0].is_string()&&fallback[1].is_number_integer())r.sprite(fallback[0],fallback[1],100,385);}
            auto speakerIt=p.catalog().npcs.find(speaker);const std::string name=speakerIt==p.catalog().npcs.end()?n.name:speakerIt->second.name;
            r.text(name,260,389,17);textPage_=businessUiTextPages(r,speech,260,417,465,4,textPage_,mx,my,click&&!advance,14);
            r.text("按 X 继续 / 点击对话框",526,522,12,{255,255,255,255});
            if(r.button("菜单",54,550,84,26,mx,my,click)){panel=RegionPanel::NpcMenu;textPage_=0;}
            if(r.button("关闭",666,550,84,26,mx,my,click)){close();return;}
            if(!selectedQuest){
                if(r.button("上一段",260,550,90,26,mx,my,click,dialogueIndex_>0)){--dialogueIndex_;textPage_=0;}
                r.text(std::to_string(dialogueIndex_+1)+" / "+std::to_string(parts.size()),365,555,12);
                if(r.button("下一段",446,550,90,26,mx,my,click,dialogueIndex_+1<int(parts.size()))){++dialogueIndex_;textPage_=0;}
            }
            if(!quests.empty()){
                sourceWindow(r,264,80,485,252);r.text("任务",280,96,17);
                npcQuestPage_=BusinessUiPage::clamp(npcQuestPage_,int(quests.size()),5);
                for(int index:BusinessUiPage::indices(npcQuestPage_,int(quests.size()),5)){
                    const auto &q=quests[index];const int id=q.at("id");const bool active=q.value("active",false),ready=q.value("ready",false);
                    const std::string label=(ready?"[可交付] ":active?"[进行中] ":"[可接受] ")+q.value("name",std::string());
                    if(r.button(businessUiFitted(r,label,435,13),281,124+(index-npcQuestPage_*5)*31,448,27,mx,my,click)){questSelection_=id;textPage_=0;}
                }
                if(r.button("<",281,289,32,24,mx,my,click,npcQuestPage_>0))--npcQuestPage_;
                r.text(std::to_string(npcQuestPage_+1)+" / "+std::to_string(BusinessUiPage::pages(int(quests.size()),5)),332,294,12);
                if(r.button(">",697,289,32,24,mx,my,click,npcQuestPage_+1<BusinessUiPage::pages(int(quests.size()),5)))++npcQuestPage_;
            }
            if(selectedQuest){const auto &q=*selectedQuest;const bool active=q.value("active",false),ready=q.value("ready",false),receiver=q.value("complete_npc",-1)==npc;
                auto receiverIt=p.catalog().npcs.find(q.value("complete_npc",-1));const auto receiverName=receiverIt==p.catalog().npcs.end()?"交付人":receiverIt->second.name;
                const std::string label=ready?(receiver?"完成任务":"前往"+receiverName):active?"任务尚未完成":"接受任务";
                if(r.button(businessUiFitted(r,label,185,13),446,550,205,26,mx,my,click,!active||(ready&&receiver))){
                    operate(ready?p.turnInQuest(questSelection_,npc):p.acceptQuest(questSelection_,npc));textPage_=0;
                    if(ready&&message.size())questSelection_=-1;
                }
            }
            if(!message.empty())r.text(businessUiFitted(r,message,620,12),90,583,12,{236,213,151,255});return;
        }
        // The NPC shop has no standalone 1031 layout member in this client.
        // Its item cells nevertheless use the same source inventory grid and
        // common slot artwork.  Consume those source dimensions instead of a
        // hand-written icon grid; the shelf contents below remain exactly the
        // [sell item] IDs loaded from the NPC's .shp member.
        sourceWindow(r,90,65,620,455);
        if(r.button("×",675,75,23,23,mx,my,click)){close();return;}
        if(!n.unavailableReason.empty()){panel=RegionPanel::NpcMenu;return;}
        auto face=n.source.values("[small face]");if(face.size()>=2)r.sprite(face[0],face[1],115,105,1,1,0,255,0,false);
        r.text(n.name,218,90,22);
        if(r.button("返回菜单",553,90,111,27,mx,my,click)){panel=RegionPanel::NpcMenu;questSelection_=-1;}
        auto si=p.catalog().shops.find(n.shop);r.text("金币 "+std::to_string(p.gold()),220,121,16);
        if(si!=p.catalog().shops.end()){
            std::vector<int> list;for(int id:si->second.items){auto d=p.item(id);if(d&&p.itemUsableBy(id,w.characterSource()))list.push_back(id);}
            const auto &itemLayout=uiSources_.layout("ui/inventory/inventory_item.ui");
            const auto sourceGrid=BusinessUiGrid::from(itemLayout,"1114");
            // Keep the source cell size and page capacity. Four columns and
            // two rows fit the wider shop panel while preserving the source
            // 30x30 cell/slot appearance and mouse hit geometry.
            const int columns=4,rows=2,pageSize=columns*rows;
            shopPage_=BusinessUiPage::clamp(shopPage_,int(list.size()),pageSize);const int pages=BusinessUiPage::pages(int(list.size()),pageSize);
            const int gridX=122,gridY=154,stepX=137,stepY=76;
            for(int cell=0;cell<pageSize;++cell){
                const int xx=gridX+(cell%columns)*stepX,yy=gridY+(cell/columns)*stepY;
                r.sprite("interface/windowcommon.img",57,xx,yy);
                const int index=shopPage_*pageSize+cell;if(index>=int(list.size()))continue;
                auto d=p.item(list[index]);if(!d)continue;
                if(!d->icon.empty())r.sprite(d->icon,d->iconFrame,xx+1,yy+1,1,1,0,255,0,true);
                wrapped(r,d->name,xx+35,yy,92,1,13);
                const SDL_Color priceColor=d->rarity>=4?SDL_Color{255,193,76,255}:
                    d->rarity==3?SDL_Color{255,119,213,255}:
                    d->rarity==2?SDL_Color{197,143,255,255}:
                    d->rarity==1?SDL_Color{146,205,255,255}:SDL_Color{238,238,238,255};
                r.text(std::to_string(d->price)+" 金币",float(xx+35),float(yy+20),12,priceColor);
                if(r.button("购买",xx+35,yy+39,62,23,mx,my,click))operate(p.buy(n.shop,d->id));
            }
            if(r.button("上一页",122,332,90,27,mx,my,click,shopPage_>0))--shopPage_;
            r.text(std::to_string(shopPage_+1)+" / "+std::to_string(pages),242,336,15);
            if(r.button("下一页",315,332,90,27,mx,my,click,shopPage_+1<pages))++shopPage_;
            r.text("源格子 "+std::to_string(sourceGrid.columns)+"×"+std::to_string(sourceGrid.rows)+
                   " / 当前货架 "+std::to_string(list.size())+" 件",450,336,11,{167,159,142,255});
        }
        if(r.button("修理全部  "+std::to_string(p.repairCost())+" 金币",122,372,300,30,mx,my,click))operate(p.repair());
        if(r.button("背包 / 出售",440,372,205,30,mx,my,click)){openInventory(true);inventorySelection_=-1;}
    }else if(panel==RegionPanel::Quests){
        // No full quest-window .ui exists in this source. Common-window tiles
        // provide the art, while the split list/detail layout is explicit inference.
        sourceWindow(r,85,65,630,482);r.text("任务",110,85,22);
        if(r.button("×",680,77,23,23,mx,my,click)){close();return;}
        if(r.button(completedQuests_?"查看进行中":"查看已完成",490,90,180,27,mx,my,click)){completedQuests_=!completedQuests_;questPage_=textPage_=0;questSelection_=-1;}
        auto all=p.questSummary();std::vector<Json> qs;for(const auto &q:all)if((q.value("status",std::string())=="complete")==completedQuests_)qs.push_back(q);
        questPage_=BusinessUiPage::clamp(questPage_,int(qs.size()),9);const int pages=BusinessUiPage::pages(int(qs.size()),9);
        if(questSelection_<0&&!qs.empty())questSelection_=qs[questPage_*9].at("id");
        for(int index:BusinessUiPage::indices(questPage_,int(qs.size()),9)){const auto &q=qs[index];const int id=q.at("id");
            const std::string label=(id==questSelection_?"> ":"")+q.value("name",std::string())+(q.value("ready",false)?" [可交付]":"");
            if(r.button(businessUiFitted(r,label,230,13),107,135+(index-questPage_*9)*34,246,29,mx,my,click)){questSelection_=id;textPage_=0;}
        }
        r.rect(366,132,1,350,{110,95,65,255});
        if(r.button("<",107,451,32,26,mx,my,click,questPage_>0))--questPage_;
        r.text(std::to_string(questPage_+1)+" / "+std::to_string(pages),160,456,13);
        if(r.button(">",321,451,32,26,mx,my,click,questPage_+1<pages))++questPage_;
        const Json *selected=nullptr;for(const auto &q:qs)if(int(q.at("id"))==questSelection_)selected=&q;
        if(selected){const auto &q=*selected;std::string detail=q.value("name",std::string())+"\n\n"+q.value("description",std::string());
            const int id=q.at("id");auto source=p.catalog().quests.find(id);
            if(source!=p.catalog().quests.end()){
                const auto giver=int(source->second.number("[npc index]",-1));auto who=p.catalog().npcs.find(giver);if(who!=p.catalog().npcs.end())detail+="\n\n委托人："+who->second.name;
                auto reward=source->second.values("[reward item]");if(!reward.empty()){detail+="\n任务奖励：";for(size_t i=0;i+1<reward.size();i+=2)if(reward[i].is_number_integer()&&reward[i+1].is_number_integer())if(auto item=p.item(reward[i]))detail+="\n"+item->name+" ×"+std::to_string(int(reward[i+1]));}
            }
            textPage_=businessUiTextPages(r,detail,383,141,295,15,textPage_,mx,my,click,13);
        }else r.text(completedQuests_?"暂无已完成任务":"与NPC交谈接受任务。",383,155,14);
        r.text("任务交付请前往对应NPC",383,510,13,{194,180,142,255});
    }else if(panel==RegionPanel::Results){
        sourceWindow(r,90,65,620,455);if(r.button("×",675,75,23,23,mx,my,click)){close();return;}
        r.text("地下城通关",292,100,30);r.text("等级 "+std::to_string(p.level())+"   金币 "+std::to_string(p.gold()),245,158,19);
        r.text("经验 "+std::to_string(p.state.value("xp",int64_t(0))),245,195,17);int count=0;for(const auto &room:session.run.rooms)if(room.cleared)++count;
        r.text("已清理 "+std::to_string(count)+" / "+std::to_string(session.run.rooms.size())+" 个房间",245,230,17);
        r.text("战利品保留在地面，可继续拾取或修理。",180,315,17);
        if(r.button("继续探索",150,440,220,35,mx,my,click))close();
        if(r.button("返回艾尔文防线",425,440,235,35,mx,my,click)){returnTown=true;close();}
    }
    if(!message.empty())wrapped(r,message,120,489,550,1,13);
}
} // namespace dnf
