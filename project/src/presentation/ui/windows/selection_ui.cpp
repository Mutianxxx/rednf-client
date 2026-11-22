#include "dnf/dungeon_difficulty.hpp"
#include "dnf/selection_ui.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *createImage="interface2/charactercreate/charactercreate.img";
constexpr const char *commonImage="interface/windowcommon.img";
constexpr const char *creationProfile="d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
const std::array<CharacterCreationArt,11> creationArt{{
    {0,0,38,6,46,60,52},{1,0,39,10,47,61,53},
    {2,0,41,18,48,62,54},{3,0,43,26,49,63,55},
    {4,0,44,30,50,64,56},{5,0,42,22,48,62,59},
    {6,0,45,34,51,65,57},{7,0,40,14,47,61,58},
    {8,0,73,69,49,74,75},{9,76,77,81,78,79,80},
    {10,76,85,89,86,87,88}
}};
Json scriptIdentity(const Script &s) {
    Json fields=Json::array();
    for(const auto &f:s.fields)fields.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    return {{"path",s.path},{"source",s.source},{"raw_bytes",s.rawBytes},{"tokens",s.tokens},{"fields",fields}};
}
bool button(Renderer &r,const std::string &image,int normal,int hover,int disabled,
            const SelectionRect &rect,SelectionUiPointer pointer,bool enabled) {
    const bool inside=rect.contains({double(pointer.x),double(pointer.y)});
    r.sprite(image,enabled?(inside?hover:normal):disabled,rect.x,rect.y);
    return enabled&&inside&&pointer.click;
}
const CharacterCreationJobView *creationJob(const std::vector<CharacterCreationJobView> &jobs,int id) {
    const auto found=std::find_if(jobs.begin(),jobs.end(),[id](const auto &j){return j.jobId==id;});
    return found==jobs.end()?nullptr:&*found;
}
const DungeonSelectionChoice *dungeonChoice(const DungeonSelectionModel &model,int id) {
    const auto found=std::find_if(model.choices.begin(),model.choices.end(),[id](const auto &c){return c.id==id;});
    return found==model.choices.end()?nullptr:&*found;
}
}

void CharacterNameSourceRules::bind(Pvf &pvf) {
    auto source=pvf.script("etc/restrictnameunicoderangetable.etc");
    auto invalid=pvf.script("etc/invalidname.etc"),slang=pvf.script("etc/slangname.etc");
    std::vector<std::array<uint32_t,2>> ranges;
    bool active=false,seen=false,closed=false;
    for(const auto &f:source.fields) {
        const auto tag=normalize(f.tag);
        if(tag=="[allow unicode range]") {
            if(active||seen||!f.values.empty())throw std::runtime_error("Unsupported duplicate name whitelist");
            active=true;seen=true;
        } else if(tag=="[/allow unicode range]") {
            if(!active||!f.values.empty())throw std::runtime_error("Unmatched name whitelist end");
            active=false;closed=true;
        } else if(active) {
            if(tag!="[range]"||f.values.size()!=2||!f.values[0].is_number_integer()||!f.values[1].is_number_integer())
                throw std::runtime_error("Unsupported name whitelist field: "+f.tag);
            const auto lo=f.values[0].get<int64_t>(),hi=f.values[1].get<int64_t>();
            if(lo<0||hi<lo||hi>0x10ffff||(lo<=0xdfff&&hi>=0xd800))
                throw std::runtime_error("Invalid Unicode name whitelist range");
            ranges.push_back({uint32_t(lo),uint32_t(hi)});
        } else throw std::runtime_error("Unsupported name whitelist envelope: "+f.tag);
    }
    if(active||!seen||!closed||ranges.empty())throw std::runtime_error("Missing name whitelist");
    // These source lists are empty in this supported profile. A future nonempty
    // list needs its real parser before names can be presented as validated.
    for(const auto *s:{&invalid,&slang})for(const auto &f:s->fields)
        if(!f.values.empty())throw std::runtime_error("Unsupported nonempty name restriction: "+s->path);
    allowed_=std::move(source);invalid_=std::move(invalid);slang_=std::move(slang);ranges_=std::move(ranges);
}
bool CharacterNameSourceRules::allows(uint32_t cp) const {
    return std::any_of(ranges_.begin(),ranges_.end(),[cp](const auto &r){return cp>=r[0]&&cp<=r[1];});
}
Json CharacterNameSourceRules::snapshot() const {
    return {{"allow_ranges",ranges_},{"allowed",scriptIdentity(allowed_)},{"invalid",scriptIdentity(invalid_)},
        {"slang",scriptIdentity(slang_)},{"scope","committed codepoint whitelist; length is separate host policy"}};
}
const CharacterCreationArt *characterCreationArt(int id) {
    const auto found=std::find_if(creationArt.begin(),creationArt.end(),[id](const auto &a){return a.jobId==id;});
    return found==creationArt.end()?nullptr:&*found;
}
SelectionRect CharacterSelectionGeometry::slot(int i) {
    if(i<0||i>=slotsPerPage)throw std::runtime_error("Selection visible slot out of range");
    return {double(27+(i%6)*124),double(74+(i/6)*208),119,207};
}
int CharacterSelectionGeometry::clampPage(int page) {return std::clamp(page,0,1);}
int CharacterSelectionGeometry::hitSlot(int page,SelectionPoint point) {
    page=clampPage(page);
    for(int i=0;i<slotsPerPage&&page*slotsPerPage+i<slotCount;++i)
        if(slot(i).contains(point))return page*slotsPerPage+i;
    return -1;
}
SelectionRect CharacterSelectionGeometry::nameField() {return {318,536,164,20};}
SelectionRect CharacterSelectionGeometry::creationJobButton(int i) {
    if(i<0||i>=10)throw std::runtime_error("Creation job index exceeds supported layout");
    return {double(15+i*77),448,77,54};
}

void SelectionUi::bind(Pvf &pvf,Assets &assets) {
    auto under=readBusinessUiLayout(pvf.script("ui/selectcharacter/selectcharacterunder.ui"));
    auto over=readBusinessUiLayout(pvf.script("ui/selectcharacter/selectcharacterover.ui"));
    auto common=readBusinessUiLayout(pvf.script("worldmap/ui/common/common.ui"));
    CharacterNameSourceRules rules;rules.bind(pvf);
    const auto &board=under.require("105","[board image]");
    if(board.strings.size()!=2||normalize(board.strings[1])!="draw by loop"||board.integers.size()!=11||
        board.integers[0]<1||board.integers[1]<1||board.integers[0]>200||board.integers[1]>200)
        throw std::runtime_error("Unsupported selection loop board schema");
    std::array<std::array<int,2>,9> metrics{};
    for(int i=0;i<9;++i) {
        const auto p=assets.pixels(board.strings[0],board.integers[i+2]);
        if(p.logicalWidth<=0||p.logicalHeight<=0)throw std::runtime_error("Invalid source board metric");
        metrics[i]={p.logicalWidth,p.logicalHeight};
    }
    for(const auto *id:{"101","106","107","110","160"})under.require(id,"[image]");
    for(const auto *id:{"102","103","104"})under.require(id,"[animation]");
    for(int i=0;i<12;++i){under.require(std::to_string(140+i),"[image]");over.require(std::to_string(1000+i),"[text]");}
    common.require("IDC_WORLDMAP_RETURN2TOWN_BUTTON","[text button]");
    // This control explicitly references the source UI action. Consume its alpha
    // sequences, not animation-clock time (simulation is paused in selection).
    const auto &banner=common.require("IDC_WORLDMAP_MAP_SELECT_BANNER","[image]");
    Json action=Json::array();
    for(const auto &option:banner.options)if(normalize(option.tag)=="[common action]")action=option.values;
    if(action.empty()||!action[0].is_string())throw std::runtime_error("Dungeon banner action binding missing");
    dungeonBannerAction_=pvf.script(normalize((std::filesystem::u8path(common.source.path).parent_path()/
        std::filesystem::u8path(action[0].get<std::string>())).lexically_normal().generic_u8string()));
    dungeonBannerAlpha_.clear();dungeonCardsAlpha_.clear();dungeonCardsDelayMs_=0;
    bool interpolation=false,alpha=false;DungeonUiAlphaSegment segment;int64_t revealAt=-1;
    for(const auto &f:dungeonBannerAction_.fields) {
        const auto tag=normalize(f.tag);
        if(tag=="[set action]"&&f.values.size()==2&&f.values[0].is_number_integer()&&f.values[1]==f.values[0]&&f.values[0].get<int64_t>()>0)revealAt=f.values[0];
        if(tag=="[interpolation]"){interpolation=true;alpha=false;segment={};}
        else if(interpolation&&tag=="[alpha]")alpha=true;
        else if(interpolation&&tag=="[duration]"&&!f.values.empty())segment.durationMs=f.values[0];
        else if(interpolation&&tag=="[first arg]"&&!f.values.empty())segment.from=f.values[0];
        else if(interpolation&&tag=="[second arg]"&&!f.values.empty())segment.to=f.values[0];
        else if(tag=="[/interpolation]") {
            if(alpha&&segment.durationMs>0) {
                if(dungeonBannerAlpha_.size()<3)dungeonBannerAlpha_.push_back(segment);
                else dungeonCardsAlpha_.push_back(segment);
            }
            interpolation=false;
        }
    }
    // The narrow adapter supports this source action's banner then balloon phases;
    // keep other UI actions unclaimed. Raw fields/tokens remain in snapshot().
    if(dungeonBannerAlpha_.size()!=3||dungeonCardsAlpha_.size()!=1)
        throw std::runtime_error("Unsupported source dungeon banner alpha sequence");
    for(const auto &segment:dungeonBannerAlpha_)dungeonCardsDelayMs_+=segment.durationMs;
    if(revealAt<dungeonCardsDelayMs_)throw std::runtime_error("Unsupported dungeon banner reveal timing");
    dungeonCardsDelayMs_=revealAt;
    under_=std::move(under);over_=std::move(over);dungeonCommon_=std::move(common);
    nameRules_=std::move(rules);boardMetrics_=metrics;assets_=&assets;
    sourceIdentity_=pvf.identity();creationArtProfile_=sourceIdentity_==creationProfile;
}
void SelectionUi::drawImage(Renderer &r,const BusinessUiLayout &layout,const BusinessUiControl &c,double dx,double dy) const {
    if(c.strings.empty()||c.integers.empty())throw std::runtime_error("Selection image has no source binding");
    const auto p=layout.position(c);
    const int blend=std::any_of(c.strings.begin()+1,c.strings.end(),[](const auto &s){return normalize(s)=="lineardodge";})?2:0;
    const uint8_t alpha=c.integers.size()==4?uint8_t(std::clamp(c.integers[3],0,255)):255;
    r.sprite(c.strings[0],c.integers[0],dx+p[0],dy+p[1],1,1,blend,alpha);
}
void SelectionUi::drawLoopBoard(Renderer &r) const {
    const auto &c=under_.require("105","[board image]");const auto p=under_.position(c);
    const int cols=c.integers[0],rows=c.integers[1];
    const int left=boardMetrics_[0][0],top=boardMetrics_[0][1];
    const int centerW=boardMetrics_[4][0],centerH=boardMetrics_[4][1];
    // Repeat logical cells rather than scaling the source ornament texture.
    for(int yy=0;yy<rows+2;++yy)for(int xx=0;xx<cols+2;++xx) {
        const int row=yy==0?0:yy==rows+1?2:1,col=xx==0?0:xx==cols+1?2:1;
        const int x=p[0]+(xx==0?0:xx==cols+1?left+cols*centerW:left+(xx-1)*centerW);
        const int y=p[1]+(yy==0?0:yy==rows+1?top+rows*centerH:top+(yy-1)*centerH);
        r.sprite(c.strings[0],c.integers[2+row*3+col],x,y);
    }
}
Json SelectionUi::snapshot() const {
    Json art=Json::array();for(const auto &a:creationArt)art.push_back({{"job",a.jobId},{"background",a.background},
        {"portrait",a.portrait},{"button",a.button},{"logo",a.logo},{"description",a.description},{"stats",a.stats},{"classification",a.classification}});
    return {{"under",under_.snapshot()},{"over",over_.snapshot()},{"dungeon_common",dungeonCommon_.snapshot()},
        {"name_rules",nameRules_.snapshot()},{"creation_art",art},{"board_metrics",boardMetrics_},
        {"pvf_sha256",sourceIdentity_},{"creation_art_profile",creationProfile},{"creation_art_profile_supported",creationArtProfile_},
        {"layout_classification","source bindings; dynamic slot/footer/creation geometry reconstructed"},
        {"dungeon_banner_action",scriptIdentity(dungeonBannerAction_)},{"dungeon_cards_delay_ms",dungeonCardsDelayMs_},
        {"unrecovered",{"native dynamic placement","full pattern-table column semantics","remaining UI ACT lifecycle","original IME/native input chain"}}};
}
CharacterSelectionAction SelectionUi::drawCharacters(Renderer &r,const std::array<CharacterSelectionSlotView,20> &slots,
    int selected,int page,SelectionUiPointer pointer,int64_t wallMs,const std::string &message) const {
    if(!bound())throw std::runtime_error("Selection UI is not bound");
    CharacterSelectionAction action;action.selected=std::clamp(selected,0,19);action.page=CharacterSelectionGeometry::clampPage(page);
    // Mouse changes are resolved before deriving selected art and button state.
    if(pointer.click) {const auto hit=CharacterSelectionGeometry::hitSlot(action.page,{double(pointer.x),double(pointer.y)});if(hit>=0)action.selected=hit;}
    drawImage(r,under_,under_.require("101"));
    for(const auto *id:{"102","103","104"}) {
        const auto &c=under_.require(id,"[animation]");const auto p=under_.position(c);
        r.animation(c.strings.at(0),double(wallMs),p[0],p[1]);
    }
    drawLoopBoard(r);drawImage(r,under_,under_.require("106"));drawImage(r,under_,under_.require("107"));
    for(int i=0;i<12;++i) {
        const int slot=action.page*12+i;if(slot>=20)break;
        const auto rect=CharacterSelectionGeometry::slot(i);const auto &view=slots[slot];
        if(slot==action.selected)drawImage(r,under_,under_.require("110"),rect.x,rect.y);
        drawImage(r,under_,under_.require(slot==action.selected?"160":std::to_string(140+i)),rect.x,rect.y+140);
        if(view.occupied) {
            if(view.appearance){Actor actor;actor.x=actor.px=rect.x+60;actor.y=actor.py=rect.y+165;r.player(actor,wallMs,1,*view.appearance);}
            const auto &style=over_.require(std::to_string(1000+i),"[text]");
            const auto &v=style.integers;
            const SDL_Color color=v.size()==9?SDL_Color{uint8_t(std::clamp(v[6],0,255)),uint8_t(std::clamp(v[7],0,255)),uint8_t(std::clamp(v[8],0,255)),255}:SDL_Color{209,185,148,255};
            r.text(businessUiFitted(r,"Lv."+std::to_string(view.level)+" "+view.name,112,12),float(rect.x+4),float(rect.y+179),12,color);
            r.text(businessUiFitted(r,view.jobName+(view.experimental?" · 实验":""),112,12),float(rect.x+4),float(rect.y+194),12,color);
        }
    }
    if(r.button("↑",754,84,22,24,pointer.x,pointer.y,pointer.click,action.page>0)){action.page=0;if(action.selected>=12)action.selected-=12;}
    if(r.button("↓",754,485,22,24,pointer.x,pointer.y,pointer.click,action.page<1)){action.page=1;if(action.selected<12)action.selected=std::min(19,action.selected+12);}
    r.text(std::to_string(action.page+1)+"/2",738,528,11);
    action.create=button(r,commonImage,90,91,93,{137,536,77,23},pointer,!slots[action.selected].occupied);
    r.text("创建角色",150,539,14);
    button(r,commonImage,90,91,93,{216,536,77,23},pointer,false);r.text("删除角色",229,539,14,{130,130,130,255});
    button(r,commonImage,90,91,93,{509,536,77,23},pointer,false);r.text("选择频道",522,539,14,{130,130,130,255});
    action.quit=button(r,commonImage,90,91,93,{589,536,77,23},pointer,true);r.text("结束游戏",602,539,14);
    action.start=button(r,under_.require("101").strings.at(0),7,8,10,{337,526,125,43},pointer,slots[action.selected].occupied);
    if(!message.empty())r.text(businessUiFitted(r,message,740,13),30,574,13,{255,190,140,255});
    return action;
}
CharacterCreationAction SelectionUi::drawCreation(Renderer &r,const std::vector<CharacterCreationJobView> &jobs,
    int selectedJob,bool nameCanSubmit,SelectionUiPointer pointer,int64_t wallMs,const std::string &message,bool pending) const {
    if(!bound())throw std::runtime_error("Selection UI is not bound");
    CharacterCreationAction action;action.selectedJob=selectedJob;
    int visible=0;
    for(const auto &job:jobs)if(!job.deferred){
        if(visible>=10)throw std::runtime_error("More than ten supported creation jobs");
        const auto rect=CharacterSelectionGeometry::creationJobButton(visible++);
        if(!pending&&creationArtProfile_&&pointer.click&&rect.contains({double(pointer.x),double(pointer.y)})&&characterCreationArt(job.jobId))action.selectedJob=job.jobId;
    }
    const auto *job=creationJob(jobs,action.selectedJob);
    const auto *art=creationArtProfile_&&job&&!job->deferred?characterCreationArt(action.selectedJob):nullptr;
    r.sprite(createImage,art?art->background:0,0,0);
    if(art) {
        // Portrait frames have a logical 800x600 canvas and authored crop;
        // retaining origin=true is essential for each job's own position.
        r.sprite(createImage,art->portrait,0,0);
        r.sprite(createImage,art->logo,480,105);
        r.sprite(createImage,art->description,480,229);
        r.sprite(createImage,art->stats,492,354);
    }
    r.sprite(createImage,1,344,33);
    if(job)r.text(job->name+(job->experimental?" · 实验内容":""),495,77,16);
    visible=0;
    for(const auto &choice:jobs)if(!choice.deferred) {
        const auto rect=CharacterSelectionGeometry::creationJobButton(visible++);const auto *icon=creationArtProfile_?characterCreationArt(choice.jobId):nullptr;
        if(icon) {
            const bool hover=rect.contains({double(pointer.x),double(pointer.y)});
            const int state=pending?3:action.selectedJob==choice.jobId?2:hover?1:0;
            r.sprite(createImage,icon->button+state,rect.x,rect.y);
        } else r.button(choice.name,int(rect.x),int(rect.y),77,54,pointer.x,pointer.y,false,false);
    }
    r.sprite(createImage,5,342,512);
    const auto name=CharacterSelectionGeometry::nameField();
    r.rect(float(name.x),float(name.y),float(name.width),float(name.height),{12,13,24,240});
    r.rect(float(name.x),float(name.y),float(name.width),float(name.height),{192,162,101,255},false);
    action.focusName=!pending&&pointer.click&&name.contains({double(pointer.x),double(pointer.y)});
    action.create=button(r,createImage,2,3,4,{337,555,125,43},pointer,nameCanSubmit&&art&&!pending);
    action.cancel=r.button("返回",15,555,90,30,pointer.x,pointer.y,pointer.click,!pending);
    if(!message.empty())r.text(businessUiFitted(r,message,298,12),489,558,12,{255,190,140,255});
    else r.text(!creationArtProfile_?"当前PVF缺少已核实创建图集映射":pending?"保存待重试，请先完成当前提交":"缔造者暂缓；实验技能仍待正规验证",489,558,12);
    (void)wallMs; // UI animation host contract is available; no invented source animation.
    return action;
}
void SelectionUi::startDungeonPresentation(DungeonSelectionState &state,int64_t wallMs) const {
    state.openedWallMs=wallMs;state.cardsVisibleAfterMs=dungeonCardsDelayMs_;
}
DungeonUiTransition SelectionUi::dungeonTransition(const DungeonSelectionState &state,int64_t wallMs) const {
    auto sample=[](const std::vector<DungeonUiAlphaSegment>&segments,int64_t age,double terminal){
        if(age<0)return uint8_t(0);
        for(const auto &key:segments){if(age<key.durationMs)
            return uint8_t(std::lround(std::clamp(key.from+(key.to-key.from)*double(age)/key.durationMs,0.0,255.0)));
            age-=key.durationMs;}
        return uint8_t(std::clamp(terminal,0.0,255.0));
    };
    const int64_t age=std::max<int64_t>(0,wallMs-state.openedWallMs);
    return {sample(dungeonBannerAlpha_,age,0),sample(dungeonCardsAlpha_,age-dungeonCardsDelayMs_,255),age>=dungeonCardsDelayMs_};
}
DungeonSelectionLayout SelectionUi::dungeonLayout(const DungeonSelectionModel &model,int selectedDungeon) const {
    if(!bound())throw std::runtime_error("Selection UI is not bound");
    auto layout=makeDungeonSelectionLayout(model);
    const auto compactBorder=assets_->pixels("worldmap/selectdungeon02.img",22);
    for(auto &card:layout.cards) {
        const auto *choice=dungeonChoice(model,card.dungeonId);if(!choice||choice->slotImage.empty())continue;
        const auto pixels=assets_->pixels(choice->slotImage,choice->slotFrame);
        const bool selected=choice->id==selectedDungeon;
        // Two source balloon sizes: full slot canvas, compact highlight frame+inset.
        // Column association remains a version-bound inference; all values originate
        // in source IMG/table/UI. No shared 84/89 placement for every direction.
        const double width=selected?pixels.logicalWidth:std::min(pixels.logicalWidth,compactBorder.logicalWidth+4);
        const double height=selected?pixels.logicalHeight:std::min(pixels.logicalHeight,compactBorder.logicalHeight+4);
        auto control=std::find_if(model.controls.begin(),model.controls.end(),[&](const auto &c){return c.type=="[balloon]"&&!c.integers.empty()&&c.integers.back()==choice->id;});
        SelectionRect image=card.imageRect;image.width=width;image.height=height;
        if(control!=model.controls.end()) {
            image.x=control->x-width/2;image.y=control->y-height;
            if(control->integers.size()>=2) {
                const auto tag="["+std::to_string(control->integers[1])+"]";
                const auto row=std::find_if(model.secondPatternTable.begin(),model.secondPatternTable.end(),[&](const auto&r){return normalize(r.tag)==tag;});
                if(row!=model.secondPatternTable.end()&&row->values.size()==6) {
                    const size_t pair=selected?2:0;
                    image.x=control->x+row->values[pair];image.y=control->y+row->values[pair+1];
                }
            }
        }
        // Preserve same-anchor source alternatives as distinct selectable cards.
        // Only exact duplicates receive an explicit small fan offset; no new map order.
        int duplicate=0;for(const auto &other:layout.cards) {
            if(&other==&card)break;
            const auto oc=std::find_if(model.controls.begin(),model.controls.end(),[&](const auto&c){return c.type=="[balloon]"&&!c.integers.empty()&&c.integers.back()==other.dungeonId;});
            if(control!=model.controls.end()&&oc!=model.controls.end()&&control->x==oc->x&&control->y==oc->y&&control->integers.size()>=2&&oc->integers.size()>=2&&control->integers[1]==oc->integers[1])++duplicate;
        }
        image.x+=duplicate*14;image.y+=duplicate*14;
        card.imageRect=image;card.hitRect=image;
    }
    // The expanded selected source image is drawn and hit-tested last.
    std::stable_partition(layout.cards.begin(),layout.cards.end(),[&](const auto&c){return c.dungeonId!=selectedDungeon;});
    const auto &c=dungeonCommon_.require("IDC_WORLDMAP_RETURN2TOWN_BUTTON","[text button]");
    const auto point=dungeonCommon_.position(c);const auto pixels=assets_->pixels(c.strings.at(0),c.integers.at(0));
    layout.cancelButton={double(point[0]),double(point[1]),double(pixels.logicalWidth),double(pixels.logicalHeight)};
    positionDungeonDifficultyControls(layout,selectedDungeon);
    return layout;
}
void SelectionUi::drawDungeon(Renderer &r,const DungeonSelectionModel &model,const DungeonSelectionLayout &layout,
    const DungeonSelectionState &state,DungeonSelectionAdmission admission,SelectionUiPointer pointer,int64_t wallMs) const {
    if(!bound())throw std::runtime_error("Selection UI is not bound");
    const auto transition=dungeonTransition(state,wallMs);
    r.rect(0,0,800,600,{8,9,14,255});
    if(transition.cardsAlpha)r.sprite(model.backgroundImage,model.backgroundFrame,0,0,1,1,0,transition.cardsAlpha);
    for(const auto &c:dungeonCommon_.controls)if(c.type=="[image]") {
        if(c.name=="IDC_WORLDMAP_MAP_SELECT_BANNER") {
            const auto p=dungeonCommon_.position(c);
            if(transition.bannerAlpha)r.sprite(c.strings.at(0),c.integers.at(0),p[0],p[1],1,1,0,transition.bannerAlpha);
        }else if(transition.cardsAlpha)drawImage(r,dungeonCommon_,c);
    }
    if(!transition.cardsInteractive) {
        const auto &c=dungeonCommon_.require("IDC_WORLDMAP_RETURN2TOWN_BUTTON");const auto p=dungeonCommon_.position(c);
        r.sprite(c.strings.at(0),c.integers.at(0),p[0],p[1]);r.text("返回城镇",p[0]+7,p[1]+7,12);return;
    }
    for(const auto &card:layout.cards) {
        const auto *choice=dungeonChoice(model,card.dungeonId);if(!choice)continue;
        const auto &q=card.imageRect;const auto alpha=transition.cardsAlpha;
        r.rect(float(q.x-2),float(q.y-2),float(q.width+4),float(q.height+4),{12,13,20,alpha});
        if(!choice->slotImage.empty()) {
            const auto px=assets_->pixels(choice->slotImage,choice->slotFrame);
            r.sprite(choice->slotImage,choice->slotFrame,q.x,q.y,1,q.width/std::max(1,px.logicalWidth),0,alpha,0,true,q.height/std::max(1,px.logicalHeight));
        }
        if(choice->id==state.selectedDungeon||choice->id==state.hoveredDungeon) {
            const int frame=choice->id==state.selectedDungeon?23:22;
            const auto px=assets_->pixels("worldmap/selectdungeon02.img",frame);
            // Match each actual displayed picture extent; no oversized fixed frame.
            r.sprite("worldmap/selectdungeon02.img",frame,q.x,q.y,1,q.width/px.logicalWidth,0,alpha,0,true,q.height/px.logicalHeight);
        }
        const bool admitted=canEnterDungeonSelection(model,choice->id,admission);
        const bool selectedCard=choice->id==state.selectedDungeon;
        const int font=selectedCard?13:11;
        r.text(businessUiFitted(r,choice->name,int(q.width)-8,font),float(q.x+4),float(selectedCard?q.y+5:q.y+q.height-23),font,
            admitted?SDL_Color{245,225,173,alpha}:SDL_Color{180,174,159,alpha});
        r.text("源Lv."+std::to_string(choice->minimumLevel),float(q.x+4),float(selectedCard?q.y+22:q.y+q.height-11),10,{209,221,177,alpha});
    }
    const auto *selected=dungeonChoice(model,state.selectedDungeon);
    const bool canEnter=selected&&canEnterDungeonSelection(model,selected->id,admission);
    // Source Antberr direction0 intentionally extends to y561. Keep metadata
    // in the footer so a fixed 492..564 panel cannot hide that selected card.
    if(selected) {
        r.rect(8,572,462,22,{20,18,24,240});
        const auto info=selected->name+"  源Lv."+std::to_string(selected->minimumLevel)+" / 基础"+
            std::to_string(selected->basisLevel)+"  怪物适配Lv."+std::to_string(admission.characterLevel);
        r.text(businessUiFitted(r,info,450,11),14,576,11);
    }
    for(const auto &c:dungeonCommon_.controls)if(c.type=="[text button]") {
        const auto p=dungeonCommon_.position(c);
        const bool cancel=c.name=="IDC_WORLDMAP_RETURN2TOWN_BUTTON";
        if(c.name=="IDC_WORLDMAP_EXPAND_BUTTON")continue; // same source anchor as Hell button; unavailable variant
        const bool hover=cancel&&layout.cancelButton.contains({double(pointer.x),double(pointer.y)});
        r.sprite(c.strings.at(0),c.integers.at(cancel?(hover?1:0):3),p[0],p[1]);
        r.text(cancel?"返回城镇":c.name=="IDC_WORLDMAP_EXERCISE_BUTTON"?"练习（未支持）":"深渊（未支持）",float(p[0]+7),float(p[1]+7),12,cancel?SDL_Color{240,229,197,255}:SDL_Color{135,135,135,255});
    }
    const auto &enter=layout.enterButton;
    r.button("进入副本",int(enter.x),int(enter.y),int(enter.width),int(enter.height),pointer.x,pointer.y,false,canEnter);
    const int difficultyCount=admission.allowSupportedDifficulty?
        std::clamp(admission.supportedDifficultyCount,1,dungeonDifficultyCount):1;
    const int tier=std::clamp(state.difficulty,0,difficultyCount-1);
    const auto &left=layout.difficultyLeft,&right=layout.difficultyRight,&label=layout.difficultyLabel;
    if(selected&&left.width>0) {
        r.rect(float(left.x-3),float(left.y-2),105,23,{8,9,14,uint8_t(transition.cardsAlpha*0.82)});
        const auto arrow=[&](const SelectionRect &q,int frame,bool enabled){
            const bool hover=q.contains({double(pointer.x),double(pointer.y)});
            r.sprite("worldmap/selectdungeon02.img",enabled?frame+(hover?1:0):frame+3,q.x,q.y,
                1,1,0,transition.cardsAlpha);
        };
        arrow(left,3,tier>0);arrow(right,7,tier+1<difficultyCount);
        // Source 11..14 contain the four Chinese difficulty labels as pixels.
        r.sprite("worldmap/selectdungeon02.img",11+tier,label.x,label.y,1,1,0,transition.cardsAlpha);
    }
    r.text("Enter / Esc",598,519,12,{205,198,176,255});
    if(const auto *hovered=dungeonChoice(model,state.hoveredDungeon);hovered&&
        !layout.difficultyLeft.contains({double(pointer.x),double(pointer.y)})&&
        !layout.difficultyRight.contains({double(pointer.x),double(pointer.y)})) {
        const float x=float(std::clamp(pointer.x+16,6,484)),y=float(std::clamp(pointer.y+18,4,400));
        r.rect(x,y,310,84,{12,14,23,248});r.rect(x,y,310,84,{190,169,117,255},false);
        r.text(businessUiFitted(r,hovered->name,294,14),x+8,y+7,14);
        r.text("源最低Lv."+std::to_string(hovered->minimumLevel)+" / 基础Lv."+std::to_string(hovered->basisLevel),x+8,y+30,12);
        r.text("进入后怪物适配Lv."+std::to_string(admission.characterLevel),x+8,y+48,12,{190,222,181,255});
        r.text(businessUiFitted(r,hovered->dungeonPath,294,10),x+8,y+66,10,{174,179,190,255});
    }
}
} // namespace dnf
