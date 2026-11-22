#include "dnf/selection_ui.hpp"
#include "dnf/dungeon_difficulty.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runSelectionUiTests(Pvf &pvf,Assets &assets) {
    int checks=0;auto check=[&](bool okay,const std::string &name){++checks;if(!okay)throw std::runtime_error("Selection UI: "+name);};
    SelectionUi ui;ui.bind(pvf,assets);const auto source=ui.snapshot();
    check(source.at("under").at("path")=="ui/selectcharacter/selectcharacterunder.ui","normal under source");
    check(source.at("under").at("controls").size()==80,"all normal under controls retained");
    check(source.at("over").at("controls").size()==82,"all normal over controls retained");
    check(source.at("under").at("controls").at(4).at("integers")==Json::array({62,33,0,1,2,3,4,5,6,7,8}),"loop counts and nine source frames retained");
    check(source.at("name_rules").at("allow_ranges")==Json::array({Json::array({48,57}),Json::array({19968,40908}),Json::array({65,90}),Json::array({97,122})}),"source Unicode ranges are ordered");
    const auto &rules=ui.nameRules();
    for(uint32_t cp:{48u,57u,65u,90u,97u,122u,0x4e00u,0x9fccu})check(rules.allows(cp),"source whitelist endpoints accepted");
    for(uint32_t cp:{0u,32u,47u,58u,64u,91u,96u,123u,0x4dffu,0x9fcdu,0xd800u,0x1f600u,0x110000u})check(!rules.allows(cp),"outside whitelist rejected");
    std::set<int> slots;
    for(int page=0;page<2;++page)for(int visible=0;visible<12;++visible) {
        const auto r=CharacterSelectionGeometry::slot(visible);
        const auto id=CharacterSelectionGeometry::hitSlot(page,{r.x+1,r.y+1});
        if(page*12+visible<20){check(id==page*12+visible,"each page slot is reachable");slots.insert(id);}
        else check(id==-1,"unused page-two cells do not invent characters");
        check(CharacterSelectionGeometry::hitSlot(page,{r.x+r.width,r.y+1})==-1,"slot gap and right boundary excluded");
    }
    check(slots.size()==20,"all twenty character slots covered once");
    check(CharacterSelectionGeometry::hitSlot(0,{-1,-1})==-1,"outside page ignored");
    check(CharacterSelectionGeometry::clampPage(-5)==0&&CharacterSelectionGeometry::clampPage(9)==1,"page bounds");
    std::set<int> portraits,buttons;
    for(int id=0;id<10;++id) {
        const auto *a=characterCreationArt(id);check(a&&a->jobId==id,"all ten current art associations registered");
        portraits.insert(a->portrait);buttons.insert(a->button);
        for(int frame:{a->background,a->portrait,a->button,a->button+1,a->button+2,a->button+3,a->logo,a->description,a->stats}) {
            const auto pixels=assets.pixels("interface2/charactercreate/charactercreate.img",frame);
            check(pixels.logicalWidth>0&&pixels.logicalHeight>0&&!pixels.rgba.empty(),"associated current IMG frame decodes");
        }
        const auto portrait=assets.pixels("interface2/charactercreate/charactercreate.img",a->portrait);
        check(portrait.logicalWidth==800&&portrait.logicalHeight==600,"portrait retains original logical canvas");
        const auto hit=CharacterSelectionGeometry::creationJobButton(id);
        check(hit.x>=0&&hit.x+hit.width<=800&&hit.y+hit.height<512,"ten icon hit areas fit without covering name input");
    }
    check(portraits.size()==10&&buttons.size()==10,"each job uses its own portrait and button");
    const auto *mageArt=characterCreationArt(3),*gunnerArt=characterCreationArt(5);
    check(mageArt&&mageArt->portrait==43&&mageArt->button==26&&mageArt->logo==49&&mageArt->description==63&&mageArt->stats==55&&
          gunnerArt&&gunnerArt->portrait==42&&gunnerArt->button==22&&gunnerArt->logo==48&&gunnerArt->description==62&&gunnerArt->stats==59,
          "Female Mage and Female Gunner use their registered portrait, button, profession, description and difficulty frames");
    check(characterCreationArt(10)!=nullptr,"deferred Creator art preserved without runtime admission");
    check(!characterCreationArt(-1)&&!characterCreationArt(11),"unknown registrations have no invented art");
    const auto name=CharacterSelectionGeometry::nameField();check(name.contains({319,537})&&!name.contains({482,537}),"name field uses the same half-open hit geometry");
    DungeonSelectionModel model;DungeonSelectionChoice choice;choice.id=1;choice.name="Test";choice.minimumLevel=1;choice.sourceEnabled=true;model.choices.push_back(choice);
    auto fresh=[&](){return enterDungeonSelection(model);};auto state=fresh();
    const auto layout=ui.dungeonLayout(model,state.selectedDungeon);
    check(layout.difficultyRight.width>0&&layout.difficultyLeft.width>0,"difficulty hit regions bind the selected card");
    check(layout.scale==1&&layout.offsetX==0&&layout.offsetY==0,"main logical mouse is not scaled twice");
    check(layout.cancelButton.x==699&&layout.cancelButton.y==541&&layout.cancelButton.width>0,"cancel geometry uses common UI binding and IMG metrics");
    const SelectionPoint right{layout.difficultyRight.x+1,layout.difficultyRight.y+1};
    auto event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::PointerActivate,right},{1,true,1});
    check(state.difficulty==0&&event.kind==DungeonSelectionEventKind::None,"pointer cannot enable unsupported difficulty");
    event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyRight,{}},{1,true,1});
    check(state.difficulty==0&&event.kind==DungeonSelectionEventKind::None,"keyboard cannot enable unsupported difficulty");
    for(int i=0;i<8;++i)updateDungeonSelection(model,layout,state,{DungeonSelectionAction::PointerActivate,right},{1,true,3});
    check(state.difficulty==2,"three-tier admission subset remains clamped to index two");
    const SelectionPoint left{layout.difficultyLeft.x+1,layout.difficultyLeft.y+1};
    for(int i=0;i<8;++i)updateDungeonSelection(model,layout,state,{DungeonSelectionAction::PointerActivate,left},{1,true,3});
    check(state.difficulty==0,"pointer difficulty is clamped to zero");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::PointerActivate,right,-1,2},{1,true,dungeonDifficultyCount});
    check(state.difficulty==3&&event.difficulty==3&&state.open&&!state.entryConsumed,"four-tier pointer arrows reach king without double-click entry");
    for(int i=0;i<8;++i)updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyLeft,{}},{1,true,dungeonDifficultyCount});
    check(state.difficulty==0,"four-tier keyboard left clamps to normal");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyRight,{}},{1,true,dungeonDifficultyCount});
    check(state.difficulty==3&&event.difficulty==3,"four-tier keyboard right shares pointer upper bound");
    event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyRight,{}},{1,true,999});
    check(state.difficulty==3&&event.difficulty==3,"excessive advertised count cannot expose a fifth tier");
    event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyRight,{}},{1,true,0});
    check(state.difficulty==0&&event.kind==DungeonSelectionEventKind::None,"invalid zero count clamps an existing tier back to normal");
    state=fresh();event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::PointerActivate,{layout.cancelButton.x+1,layout.cancelButton.y+1}},{1,false,1});
    check(event.kind==DungeonSelectionEventKind::Cancelled&&!state.open&&state.awaitingEntranceExit,"source return button cancels same controller");
    state=enterDungeonSelection(model,state);check(!state.open,"entrance cannot reopen before exit");leaveDungeonEntrance(state);state=enterDungeonSelection(model,state);check(state.open,"exit permits intentional reentry");
    event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::Enter,{}},{1,false,1});
    check(event.kind==DungeonSelectionEventKind::EnterDungeon&&event.dungeonId==1,"entry event preserves source ID");
    event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::Enter,{}},{1,false,1});check(event.kind==DungeonSelectionEventKind::None,"entry consumed exactly once");
    return {{"status","passed"},{"checks",checks},{"sources",source},{"scope","source rules, art bounds, twenty-slot geometry, controller admission/difficulty/entry; rendering and real IME separate"}};
}

Json runSelectionUiRuntimeTests(Pvf &pvf,Assets &assets,const std::filesystem::path &output) {
    int checks=0;auto check=[&](bool okay,const std::string &name){++checks;if(!okay)throw std::runtime_error("Selection render: "+name);};
    std::filesystem::create_directories(output);SelectionUi ui;ui.bind(pvf,assets);
    Renderer r(assets,RendererOptions{"Hidden selection regression",800,600,false,false,false});
    std::vector<CharacterCreationJobView> jobs;
    for(int id=0;id<11;++id)jobs.push_back({id,"职业"+std::to_string(id),id!=0,id==10});
    for(const auto size:{std::array<int,2>{800,600},{1280,720},{1920,1080}}) {
        r.resize(size[0],size[1]);
        for(int id=0;id<10;++id){
            r.begin();r.ui();const auto action=ui.drawCreation(r,jobs,id,true,{},1000);
            check(action.selectedJob==id&&!action.create&&!action.cancel,"drawing preserves creation choice without action");
            if(size[0]==800)r.screenshot(output/("create-"+std::to_string(id)+".png"));r.present();
        }
    }
    std::array<CharacterSelectionSlotView,20> slots{};
    r.resize(800,600);r.begin();r.ui();auto action=ui.drawCharacters(r,slots,0,0,{150,540,true},1000);
    check(action.create&&!action.start,"empty slot permits create only");r.present();
    slots[19].occupied=true;slots[19].name="测试角色19";slots[19].jobName="鬼剑士";slots[19].level=3;
    r.begin();r.ui();action=ui.drawCharacters(r,slots,19,1,{350,540,true},1500);
    check(action.start&&!action.create,"occupied slot starts from page two");r.screenshot(output/"select-page-two.png");r.present();
    r.begin();r.ui();const auto create=ui.drawCreation(r,jobs,0,true,{int(CharacterSelectionGeometry::creationJobButton(5).x)+2,450,true},1000);
    check(create.selectedJob==5,"source female gunner icon selects own job");r.present();
    r.begin();r.ui();const auto pending=ui.drawCreation(r,jobs,5,true,{350,570,true},1000,"写入失败，重试当前提交",true);
    check(!pending.create&&!pending.cancel,"frozen save cannot duplicate create or abandon draft");r.present();
    check(r.errors.empty(),"all hidden source UI renders have no renderer errors");
    return {{"status","passed"},{"checks",checks},{"renderer_errors",r.errors},{"renderer_unsupported",r.unsupported},
        {"scope","hidden SDL source-image/event checks; no original visual equivalence or real Windows IME claim"}};
}
} // namespace dnf
