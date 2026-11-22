#include "dnf/region_ui.hpp"
#include <cmath>
namespace dnf {
namespace {
constexpr const char *inventoryArt = "interface/newstyle/windows/inventory/inventory.img";
constexpr const char *commonArt = "interface/windowcommon.img";
bool inside(int mx,int my,int x,int y,int w,int h) {return mx>=x&&mx<x+w&&my>=y&&my<y+h;}
void art(Renderer &r,const char *path,int frame,int x,int y) {r.sprite(path,frame,x,y,1,1,0,255,0,true);}
bool tab(Renderer &r,const std::string &label,int x,int y,int width,bool selected,int mx,int my,bool click,bool enabled=true) {
    int base=width==70?86:width==39?82:110;
    bool hover=enabled&&inside(mx,my,x,y,width,21);
    art(r,commonArt,base+(!enabled?3:selected?2:hover?1:0),x,y);
    r.text(label,float(x+(width-r.textWidth(label,12))/2),float(y+5),12,
           !enabled?SDL_Color{110,107,98,255}:SDL_Color{233,219,162,255});
    return hover&&click;
}
bool smallButton(Renderer &r,const std::string &label,int x,int y,int mx,int my,bool click,bool enabled=true) {
    bool hover=enabled&&inside(mx,my,x,y,56,23);
    art(r,commonArt,enabled?(hover?13:12):15,x,y);
    r.text(label,float(x+(56-r.textWidth(label,12))/2),float(y+4),12,enabled?SDL_Color{240,221,165,255}:SDL_Color{117,113,104,255});
    return hover&&click;
}
SDL_Color itemColor(const ItemDefinition &d) {
    if(d.rarity==1)return {146,205,255,255};
    if(d.rarity==2)return {197,143,255,255};
    if(d.rarity==3)return {255,119,213,255};
    if(d.rarity>=4)return {255,193,76,255};
    return {238,238,238,255};
}
std::string kind(const ItemDefinition &d) {
    if(d.avatar)return "装扮";
    if(d.slot=="[weapon]")return "武器";
    if(d.slot=="[coat]")return "上衣";if(d.slot=="[pants]")return "下装";
    if(d.slot=="[shoulder]")return "护肩";if(d.slot=="[waist]")return "腰带";
    if(d.slot=="[shoes]")return "鞋";return d.equipment?"装备":d.hp||d.mp?"消耗品":"材料";
}
void tooltip(Renderer &r,const ItemDefinition &d,const Json *entry,int x,int y,bool worn,bool fitting=false,bool selling=false) {
    struct Line {std::string text;SDL_Color color;};
    const SDL_Color white{230,230,230,255},blue{92,213,238,255},gray{157,153,144,255};
    std::vector<Line> lines;
    auto line=[&](std::string s,SDL_Color c){lines.push_back({std::move(s),c});};
    if(worn)line("穿戴中的物品",{230,212,158,255});
    if(fitting)line("试穿预览",{94,217,242,255});
    line(d.name.empty()?kind(d)+" #"+std::to_string(d.id):d.name,itemColor(d));line("",white);
    line(kind(d)+"                 Lv."+std::to_string(d.minimumLevel),white);
    if(d.equipment&&!d.avatar&&entry)
        line("耐久度 "+std::to_string(entry->value("durability",0))+" / "+std::to_string(d.durability),white);
    if(d.physicalAttack)line("物理攻击力 +"+std::to_string(d.physicalAttack),white);
    if(d.physicalDefense)line("物理防御力 +"+std::to_string(d.physicalDefense),white);
    if(d.hp)line("恢复HP"+std::to_string(d.hp)+"点。",blue);
    if(d.mp)line("恢复MP"+std::to_string(d.mp)+"点。",blue);
    if(d.cooldown&&!d.equipment)line("冷却时间:"+std::to_string(d.cooldown/1000)+"秒",white);
    if(d.avatar)line("装扮外观随对应部位替换",gray);
    line("",white);
    line(fitting?"[点击图标试穿；不改变已装备物品]":worn?"[鼠标右键解除装备]":selling?"[鼠标右键出售一件]":d.equipment?"[鼠标右键或双击穿戴]":"[鼠标右键或双击使用]",blue);
    const int width=216,height=int(lines.size())*15+14;
    y=std::clamp(y,24,548-height);
    r.rect(float(x),float(y),width,float(height),{0,0,0,222});
    r.rect(float(x),float(y),width,float(height),{116,109,90,230},false);
    for(size_t i=0;i<lines.size();++i) {
        // Names may contain a source colour suffix; wrap with actual font widths.
        auto text=lines[i].text;
        while(!text.empty()&&r.textWidth(text,12)>width-12) {
            auto end=text.size()-1;while(end>0&&(uint8_t(text[end])&0xc0)==0x80)--end;
            text.erase(end);
        }
        r.text(text,float(x+6),float(y+7+int(i)*15),12,lines[i].color);
        if(i==1||(!worn&&!fitting&&i==0))r.rect(float(x+5),float(y+24+int(i)*15),width-10,1,{100,94,80,120});
    }
}
}
void RegionUi::inventory(Renderer &r,World &w,Progression &p,const CharacterAppearance &appearance,int mx,int my,bool click,bool activate) {
    if(!uiSources_.bound()) {r.text("装备界面源尚未绑定",470,110,16);return;}
    const auto &root=uiSources_.layout("ui/inventory/iteminventorywindow.ui");
    const auto &items=uiSources_.layout("ui/inventory/inventory_item.ui");
    const auto &avatars=uiSources_.layout("ui/inventory/inventory_avatar.ui");
    const auto &bottom=uiSources_.layout("ui/inventory/inventory_bottom.ui");
    const int x=int(root.source.number("[horizontal distance]")),y=int(root.source.number("[vertical distance]"));
    // Tile metrics and window furniture are the reconstructed common-window adapter.
    // Child origins, tab labels, images, grids and slot bounds come from the selected PVF.
    sourceWindow(r,x-10,y-14,258,452);r.rect(float(x-4),float(y+15),246,416,{2,14,22,245});
    art(r,commonArt,9,x-11,y-19);r.sprite(commonArt,10,x+92,y-19,1,88.0/12,0,255,0,true,1);
    art(r,commonArt,11,x+180,y-19);art(r,"interface2/window_title_accessory/window_title_accessory.img",int(root.source.number("[title accesorry type]")),x-18,y-23);
    const std::string title=inventoryTab_==1?"装扮栏(I)":"物品栏(I)";r.text(title,float(x+119-r.textWidth(title,12)/2),float(y-8),12);
    bool closeHover=inside(mx,my,x+229,y-9,13,15);art(r,commonArt,closeHover?43:42,x+231,y-6);
    if(closeHover&&click){close();return;}
    const auto &tabs=root.require("0","[tab group]");const int tabWidth=tabs.integers.at(0);
    for(int i=0;i<int(tabs.strings.size());++i)if(tab(r,tabs.strings[i],x+int(tabs.x)+i*tabWidth,y+int(tabs.y)+2,tabWidth,inventoryTab_==i,mx,my,click,i<2)){
        inventoryTab_=i;bagTab_=bagPage_=0;inventorySelection_=-1;
    }
    const bool avatar=inventoryTab_==1;const auto &layout=avatar?avatars:items;
    const auto childOrigin=root.position(avatar?"2":"1");const int ox=x+childOrigin[0],oy=y+childOrigin[1];
    // State-dependent glows and later equipment overlays are retained in source,
    // and are not drawn as unconditional images.
    auto imageControl=[&](const BusinessUiControl &c){if(c.strings.empty()||c.integers.empty())return;auto pos=layout.position(c);
        r.sprite(c.strings[0],c.integers[0],ox+pos[0],oy+pos[1],1,1,0,255,0,true);};
    for(const auto &c:layout.controls)if(c.type=="[image]" && (c.name=="-1"||c.name=="2400") && c.strings.size()==1)imageControl(c);
    if(avatar)for(const auto &c:layout.controls)if(c.type=="[image]"&&c.strings.size()==2&&c.strings[1]=="LINEARDODGE"){
        auto pos=layout.position(c);r.sprite(c.strings[0],c.integers.at(0),ox+pos[0],oy+pos[1],1,1,1);
    }
    CharacterAppearance preview=appearance;
    if(avatar&&fitting_)for(const auto &part:fittingItems_)if(auto d=p.item(part.second))applyEquipmentAppearance(preview,d->source);
    Actor doll;const auto &previewControl=layout.require(avatar?"2199":"1199","[control]");
    auto pp=layout.position(previewControl);doll.x=doll.px=ox+pp[0]+(avatar?0:previewControl.integers.at(0)/2);
    doll.y=doll.py=oy+pp[1]+(avatar?0:previewControl.integers.at(1)-4);doll.animation=previewMoving_?"move":"stay";
    r.player(doll,int64_t(SDL_GetTicks64()),1,preview);
    if(!avatar){const auto &toggle=items.require("1200");art(r,toggle.strings.at(0).c_str(),toggle.integers.at(previewMoving_?3:0),ox+int(toggle.x),oy+int(toggle.y));
        if(click&&inside(mx,my,ox+int(toggle.x),oy+int(toggle.y),56,20))previewMoving_=!previewMoving_;}
    int hovered=-1;bool hoverWorn=false;const ItemDefinition *trialHover=nullptr;const auto &inv=p.state.at("inventory");
    auto icon=[&](const ItemDefinition &d,int xx,int yy){if(!d.icon.empty())r.sprite(d.icon,d.iconFrame,xx+1,yy+1,1,1,0,255,0,true);};
    const auto &slots=uiSources_.layout(avatar?"ui/inventory/inventory_avatar_control_group.ui":"ui/inventory/inventory_item_control_group.ui");
    const char *itemKeys[]={"[shoulder]","[coat]","[pants]","[waist]","[shoes]","[weapon]","[title name]","[wrist]","[amulet]","[ring]"};
    const char *avatarKeys[]={"[hair avatar]","[hat avatar]","[face avatar]","[breast avatar]","[coat avatar]","[skin avatar]","[waist avatar]","[pants avatar]","[shoes avatar]","[aurora avatar]"};
    auto group=layout.position(avatar?"2101":"1101");
    for(size_t i=0;i<slots.controls.size();++i){const auto &c=slots.controls[i];auto pos=slots.position(c);int xx=ox+group[0]+pos[0],yy=oy+group[1]+pos[1];
        if(c.type!="[control]"||c.integers.size()!=2)continue;
        // The two additional ordinary source slots lack a verified equipment-type binding.
        // Keep their source bounds, without inventing equip semantics.
        if(!avatar&&i>=std::size(itemKeys)){if(inside(mx,my,xx,yy,c.integers[0],c.integers[1]))r.text("此槽位映射待核实",x-220,y+200,12);continue;}
        if(avatar&&i>=std::size(avatarKeys))continue;
        int index=p.equippedIndex(avatar?avatarKeys[i]:itemKeys[i]);if(index<0||index>=int(inv.size()))continue;
        auto d=p.item(inv[index].at("id"));if(!d)continue;icon(*d,xx,yy);
        if(inside(mx,my,xx,yy,c.integers[0],c.integers[1])){hovered=index;hoverWorn=true;if(click)inventorySelection_=index;}
    }
    auto grid=BusinessUiGrid::from(layout,avatar?"2110":"1114");grid.x+=ox;grid.y+=oy;
    const auto &bagTabs=layout.require(avatar?"2000":"1000","[tab group]");auto bt=layout.position(bagTabs);const int bw=bagTabs.integers.at(0);
    for(int i=0;i<int(bagTabs.strings.size());++i)if(tab(r,bagTabs.strings[i],ox+bt[0]+i*bw,oy+bt[1],bw,(avatar?0:bagTab_)==i,mx,my,click,!avatar||i==0)){bagTab_=i;bagPage_=0;inventorySelection_=-1;}
    if(avatar&&smallButton(r,fitting_?"返回":"试穿",x+180,oy+bt[1],mx,my,click)){fitting_=!fitting_;fittingSelection_=-1;bagPage_=0;}
    std::vector<int> visible;
    for(size_t i=0;i<inv.size();++i){auto d=p.item(inv[i].at("id"));if(!d||p.equipped(int(i)))continue;
        bool questItem=d->source.number("[quest]",0)!=0 || d->path.find("/quest/")!=std::string::npos;
        bool profession=d->path.find("/expertjob/")!=std::string::npos;
        bool show=avatar?d->avatar:bagTab_==0?d->equipment&&!d->avatar:bagTab_==1?!d->equipment&&(d->hp||d->mp):bagTab_==2?!d->equipment&&!d->hp&&!d->mp&&!questItem&&!profession:bagTab_==3?profession:questItem;
        if(show)visible.push_back(int(i));
    }
    const int trialIds[]={39147,39530,40728,41190,41830,40307,41488};bool trial=avatar&&fitting_;
    if(bagSorted_)std::stable_sort(visible.begin(),visible.end(),[&](int l,int rr){return int(inv[l].at("id"))<int(inv[rr].at("id"));});
    const int count=trial?int(std::size(trialIds)):int(visible.size()),perPage=grid.perPage();const int pages=BusinessUiPage::pages(count,perPage);bagPage_=BusinessUiPage::clamp(bagPage_,count,perPage);
    for(int cell=0;cell<perPage;++cell){auto pos=grid.cell(cell);int xx=pos[0],yy=pos[1];art(r,commonArt,57,xx,yy);int n=bagPage_*perPage+cell;if(n>=count)continue;
        int index=trial?-1:visible[n];auto d=p.item(trial?trialIds[n]:int(inv[index].at("id")));if(!d)continue;icon(*d,xx,yy);
        if(!trial&&inv[index].value("count",1)>1){auto label=std::to_string(int(inv[index].at("count")));r.text(label,float(xx+28-r.textWidth(label,10)),float(yy+19),10);}
        if((trial&&fittingItems_.count(d->slot)&&fittingItems_[d->slot]==d->id)||(!trial&&inventorySelection_==index))r.rect(float(xx),float(yy),30,30,{247,213,93,255},false);
        if(grid.hit(mx,my)==cell){r.rect(float(xx),float(yy),30,30,{103,212,255,255},false);if(trial){trialHover=d;if(click||activate){fittingItems_[d->slot]=d->id;fittingSelection_=d->id;}}else{hovered=index;hoverWorn=false;if(click)inventorySelection_=index;}}
    }
    // The source inventory_bottom child is a sibling of the tab contents.
    for(const auto &c:bottom.controls)if(c.type=="[image]"&&!c.strings.empty()&&!c.integers.empty())r.sprite(c.strings[0],c.integers[0],x+int(c.x),y+int(c.y),1,1,0,255,0,true);
    const auto &sort=bottom.require("9200");if(smallButton(r,sort.strings.at(1),x+int(sort.x),y+int(sort.y),mx,my,click)){bagSorted_=true;message="仅整理显示顺序，物品身份保留";}
    const auto &weight=bottom.require("9300"),&gauge=bottom.require("9100");r.text(weight.strings.at(0),float(x+weight.x),float(y+weight.y),12);
    art(r,gauge.strings.at(0).c_str(),gauge.integers.at(0),x+int(gauge.x),y+int(gauge.y));
    // Currency text bindings use the matching source text/container coordinates.
    auto currency=[&](const char *id,const std::string &value,bool supported){const auto &c=bottom.require(id);r.text(value,float(x+c.x),float(y+c.y),12,supported?SDL_Color{230,200,155,255}:SDL_Color{139,135,124,255});};
    currency("9398","0 装扮币",false);currency("9301","0 个",false);currency("9302","0 胜点",false);currency("9399","0 代币券",false);currency("9303","0 点券",false);currency("9304",std::to_string(p.gold())+" 金币",true);
    if(pages>1){const int xx=x+229,yy=grid.y;art(r,commonArt,16,xx,yy);art(r,commonArt,22,xx,yy+108);
        if(click&&inside(mx,my,xx-2,yy,16,16))bagPage_=std::max(0,bagPage_-1);if(click&&inside(mx,my,xx-2,yy+104,16,18))bagPage_=std::min(pages-1,bagPage_+1);
        r.text(std::to_string(bagPage_+1)+"/"+std::to_string(pages),float(x+203),float(grid.y+124),10);}
    if(avatar&&fitting_){r.text("试穿预览",float(x+3),float(y+185),12,{105,221,248,255});if(smallButton(r,"还原",x+95,y+180,mx,my,click)){fittingItems_.clear();fittingSelection_=-1;}}
    if(hovered>=0&&hovered<int(inv.size())){if(auto d=p.item(inv[hovered].at("id"))){
        tooltip(r,*d,&inv[hovered],x-230,my+18,hoverWorn,false,inventorySelling_);
        if(!hoverWorn&&d->equipment){int worn=p.equippedIndex(d->slot);if(worn>=0&&worn!=hovered)if(auto other=p.item(inv[worn].at("id")))tooltip(r,*other,&inv[worn],x-450,my+18,true);}
        if(activate){Operation result;
            if(hoverWorn){result=w.changeEquipment(p,hovered,true);equipmentPublished=result.ok;}
            else if(inventorySelling_&&!w.combat)result=p.sell(hovered);
            else if(d->equipment){result=w.changeEquipment(p,hovered);equipmentPublished=result.ok;}
            else{result=p.usePotion(hovered,w.nowMs(),w.player.hp,w.player.maxHp,w.player.mp,w.player.maxMp);if(result){w.player.hp=std::min(w.player.maxHp,w.player.hp+result.hp);w.player.mp=std::min(w.player.maxMp,w.player.mp+result.mp);}}
            message=result.message;changed=result.ok;inventoryMessageUntil_=SDL_GetTicks64()+3000;
        }
    }}else if(trialHover)tooltip(r,*trialHover,nullptr,x-230,my+18,false,true);
    if(inventorySelling_){r.text("右键出售物品",float(x-125),541,12);if(smallButton(r,"商店",x-71,455,mx,my,click)){panel=RegionPanel::Shop;inventorySelling_=false;}}
    if(!message.empty()&&SDL_GetTicks64()<inventoryMessageUntil_)r.text(message,float(x-230),541,12,{236,213,151,255});
}
} // namespace dnf
