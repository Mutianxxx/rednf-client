#include "dnf/selection_ui.hpp"
#include "dnf/target_hud.hpp"
#include "dnf/session.hpp"
#include "dnf/monster_action_ai.hpp"
#include "dnf/monster_event_ai.hpp"
#include "dnf/act_world_host.hpp"
#include <climits>
#include <stdexcept>
namespace dnf {
Json runWorldPresentationSourceTests(Pvf &pvf,Assets &assets) {
  Json checks=Json::array(),routes=Json::array();
  auto check=[&](bool okay,const char *what){if(!okay)throw std::runtime_error(what);checks.push_back(what);};
  auto rejects=[&](auto fn){try{fn();return false;}catch(const std::exception &){return true;}};
  RegionCatalog catalog(pvf,assets);SelectionUi ui;ui.bind(pvf,assets);
  auto model=captureDungeonSelectionModel(pvf,catalog);int cards=0;
  for(const auto &path:pvf.paths("worldmap/",".wdm")) {
   catalog.prepareWorldmap(path);const auto source=captureDungeonSelectionModel(pvf,catalog,path);
   for(const auto &choice:source.choices){++cards;
    auto state=enterDungeonSelection(source);state.selectedDungeon=choice.id;state.difficulty=2;
    ui.startDungeonPresentation(state,5000);const auto layout=ui.dungeonLayout(source,choice.id);
    auto card=std::find_if(layout.cards.begin(),layout.cards.end(),[&](const auto &c){return c.dungeonId==choice.id;});
    check(card!=layout.cards.end(),"source card retained");
    const auto &q=card->imageRect;const auto &left=layout.difficultyLeft,&right=layout.difficultyRight;
    check(left.x>=q.x&&right.x+right.width<=q.x+q.width&&left.y>=q.y+q.height*.45&&left.y+left.height<=q.y+q.height,
        "difficulty controls stay in selected source card middle/lower area");
    auto event=updateDungeonSelection(source,layout,state,{DungeonSelectionAction::PointerActivate,{right.x+1,right.y+1},6299,2},{1,true,4,true});
    check(event.kind==DungeonSelectionEventKind::None&&state.open&&state.difficulty==2,"intro blocks double-click and difficulty input");
    event=updateDungeonSelection(source,layout,state,{DungeonSelectionAction::PointerActivate,{right.x+1,right.y+1},6600,2},{1,true,4,true});
    check(event.kind==DungeonSelectionEventKind::DifficultyChanged&&state.difficulty==3&&state.open&&!state.entryConsumed,
        "double-click difficulty arrow changes tier without entering card");
    event=updateDungeonSelection(source,layout,state,{DungeonSelectionAction::PointerActivate,{q.x+q.width/2,q.y+7},6600,2},{1,true,4,true});
    check(event.kind==DungeonSelectionEventKind::EnterDungeon&&event.dungeonId==choice.id&&event.difficulty==3&&!state.open,
        "admitted card double-click enters with selected tier");
    event=updateDungeonSelection(source,layout,state,{DungeonSelectionAction::Enter,{},6601},{1,true,4,true});
    check(event.kind==DungeonSelectionEventKind::None,"entry is consumed only once");
   }
  }
  check(cards>=100,"all source card variants covered");
  auto state=enterDungeonSelection(model);const auto layout=ui.dungeonLayout(model,state.selectedDungeon);
  const auto card=layout.cards.back();auto blocked=model;for(auto &c:blocked.choices)c.sourceEnabled=false;
  auto event=updateDungeonSelection(blocked,layout,state,{DungeonSelectionAction::PointerActivate,{card.imageRect.x+20,card.imageRect.y+7},0,2},{1,true,4,false});
  check(event.kind==DungeonSelectionEventKind::Selected&&state.open&&!state.entryConsumed,"double-click cannot bypass admission");
  state.difficulty=3;
  event=updateDungeonSelection(model,layout,state,{DungeonSelectionAction::DifficultyRight,{},0},{1,false,1,true});
  check(state.difficulty==0&&event.kind==DungeonSelectionEventKind::None,"unsupported tiers remain normal and inactive");
  for(int i=0;i<dungeonDifficultyCount;++i){check(!std::string(dungeonDifficultyName(i)).empty(),"difficulty tier has name");}
  check(rejects([&]{dungeonDifficultyRequest(4);}),"unproven fifth tier is rejected");
  for(const char *path:{"monster/act8/blackscalemoussambani/blackscalemoussambani.mob",
       "monster/act8/blackscalemoussambani/blackscalemoussambani_global_bosstower.mob",
       "monster/newmonsters/event/2018_hellparty/boss/boss1.mob"}) {
   const auto mob=pvf.script(path);
   for(int tier=0;tier<4;++tier){
    const auto request=dungeonDifficultyRequest(tier);const auto resolved=resolveDungeonDifficulty(mob,request);
    const auto action=selectMonsterActionAiRoutes(pvf,mob,request),exactAction=selectMonsterActionAiRoutes(pvf,mob,resolved.selected);
    const auto eventRoute=selectMonsterEventAi(pvf,mob,request),exactEvent=selectMonsterEventAi(pvf,mob,resolved.selected);
    check(action.ok&&eventRoute.ok,"source-family request reaches actual Action/Event AI route decoders");
    check(action.paths==exactAction.paths&&eventRoute.resolvedPath==exactEvent.resolvedPath,
        "source-family selection exactly matches explicit authored row paths");
    check(action.difficulty==request&&eventRoute.difficulty==request,
        "persisted request retains tier policy across rooms and pending Event AI restore");
    check(action.source.at("difficulty_selection").at("selected")==resolved.selected,
        "route receipt retains exact source tag and inferred family policy");
    routes.push_back({{"path",path},{"tier",tier},{"resolution",resolved.json()},{"action",action.json()},{"event",eventRoute.json()}});
   }
  }
  const auto old=pvf.script("monster/act8/blackscalemoussambani/blackscalemoussambani.mob");
  check(!selectMonsterActionAiRoutes(pvf,old,"normal").ok&&!selectMonsterEventAi(pvf,old,"normal").ok,
      "historic exact test-policy names never gain implicit alias fallback");
  auto malformed=old;for(auto &f:malformed.fields)if(normalize(f.tag)=="[medium]"&&f.values.size()==4)f.tag="[missing_medium]";
  check(rejects([&]{resolveDungeonDifficulty(malformed,dungeonDifficultyRequest(1));}),"absent selected source tier rejects without easy fallback");
  malformed=old;malformed.fields.insert(malformed.fields.begin()+1,Field{"[ai pattern]",Json::array(),0});
  check(rejects([&]{resolveDungeonDifficulty(malformed,dungeonDifficultyRequest(0));}),"ambiguous source family block rejected");
  check(rejects([&]{resolveDungeonDifficulty(old,"dungeon_hero");}),"unimplemented dungeon policy name rejected");
  World world(pvf,assets);RegionSession session;
  for(int tier=0;tier<4;++tier){
   session.begin(catalog,1,654321,{},"legacy-demo-v1","legacy-snapshot-damage-v1",{},tier);
   check(session.monsterAiDifficulty()==dungeonDifficultyRequest(tier),"begin freezes executable AI tier policy for run");
   auto saved=session.save(world,"dungeon");saved["future_root"]={{"raw",{1,2,3}}};saved["dungeon_difficulty"]["future_tag"]="retained";
   RegionSession loaded;check(loaded.load(saved,catalog),"selected difficulty session loads");
   check(loaded.dungeonDifficulty==tier&&loaded.monsterAiDifficulty()==session.monsterAiDifficulty(),"reload restores same selected run tier");
   auto after=loaded.save(world,"dungeon");check(after["run"]==saved["run"]&&after["future_root"]==saved["future_root"]&&after["dungeon_difficulty"]["future_tag"]=="retained",
       "difficulty restore retains topology, source fields and unknown root/nested metadata");
   const auto before=loaded.save(world,"dungeon");auto invalid=saved;invalid["dungeon_difficulty"]["tier"]=4;
   check(rejects([&]{loaded.load(invalid,catalog);})&&loaded.save(world,"dungeon")==before,"invalid saved difficulty fails transactionally");
   invalid=saved;invalid["dungeon_difficulty"]["tier"]=true;check(rejects([&]{loaded.load(invalid,catalog);}),"boolean tier rejected");
   invalid=saved;invalid["dungeon_difficulty"]["policy"]="unknown";check(rejects([&]{loaded.load(invalid,catalog);}),"unknown saved difficulty policy rejected");
   saved.erase("dungeon_difficulty");check(loaded.load(saved,catalog)&&loaded.monsterAiDifficulty()=="easy"&&loaded.dungeonDifficulty==0,
       "legacy save remains exact easy with no new tier policy reinterpretation");
   check(!loaded.save(world,"town").contains("dungeon_difficulty"),"town save removes dungeon difficulty with run");
   loaded.clear();check(loaded.monsterAiDifficulty()=="easy"&&loaded.dungeonDifficulty==0,"run exit clears tier selection");
  }
  const auto registry=pvf.script("monster/monster.lst");
  int kaizenId=-1;constexpr const char *kaizenPath="monster/newmonsters/shonan/kaizen/kaizen.mob";
  for(size_t i=0;i+1<registry.tokens.size();++i)if(registry.tokens[i].at("value").is_number_integer()&&registry.tokens[i+1].at("value").is_string()&&
      normalize("monster/"+registry.tokens[i+1].at("value").get<std::string>())==kaizenPath)kaizenId=registry.tokens[i].at("value").get<int>();
  check(kaizenId>=0,"runtime fixture uses real source Kaizen registration");
  for(int tier=0;tier<4;++tier) {
   World live(pvf,assets);live.configureSourceActions("presentation-AI-static:"+sha256(assets.staticBytes("audio.xml")),true);
   live.mapWidth=20000;live.walkRects={{12,185,19976,1200}};live.combat=true;live.freezeAi=false;
   live.player.x=live.player.px=6000;live.player.y=live.player.py=500;
   Actor actor;actor.id=31;actor.sourceId=kaizenId;actor.monsterPath=kaizenPath;actor.hp=actor.maxHp=10000;
   actor.x=actor.px=1000;actor.y=actor.py=500;actor.dir=1;
   actor.sourceStats["spawn"]={{"diagnostic_fixture","real Kaizen MOB/AI/ACT; wide plane and legacy balance"}};
   live.monsters.push_back(actor);live.synchronizeEntityHandles();
   session.begin(catalog,1,654321,{},"legacy-demo-v1","legacy-snapshot-damage-v1",{},tier);
   live.configureMonsterActionAi(session.monsterAiDifficulty());live.advanceSingleTick();
   check(std::count_if(live.events.begin(),live.events.end(),[](const Event &e){return e.kind=="source_action"&&e.name=="monster/newmonsters/shonan/kaizen/action/teleport.act";})==1&&
       live.actHost()->ownsActor(live.monsters[0].handle),"selected run tier reaches real World Action.ai tick and binds authored teleport ACT");
   check(live.monsterActionAiState().at("difficulty")==session.monsterAiDifficulty(),"actual World scheduler retains selected session request");
   auto saved=live.simulationCheckpoint();World resumed(pvf,assets);
   resumed.configureSourceActions("presentation-AI-static:"+sha256(assets.staticBytes("audio.xml")),true);
   resumed.restoreSimulationCheckpoint(saved);
   check(resumed.monsterActionAiState().at("difficulty")==session.monsterAiDifficulty(),"actual simulation resume restores selected source-family request");
   World eventWorld(pvf,assets);eventWorld.combat=true;eventWorld.mapWidth=20000;eventWorld.walkRects={{12,185,19976,1200}};
   eventWorld.player.x=eventWorld.player.px=560;eventWorld.player.y=eventWorld.player.py=344;
   Actor jena;jena.id=17;jena.sourceId=56503;jena.monsterPath="monster/newmonsters/heaven/jena/jena.mob";
   jena.x=jena.px=640;jena.y=jena.py=344;jena.dir=-1;jena.hp=jena.maxHp=10000;
   eventWorld.monsters.push_back(jena);eventWorld.synchronizeEntityHandles();
   eventWorld.configureSourceActions("presentation-Event-static:"+sha256(assets.staticBytes("audio.xml")));
   const auto owner=eventWorld.monsters[0].handle;
   check(eventWorld.configureMonsterEventAi(owner,session.monsterAiDifficulty(),MonsterEventAiPolicy::inferredIntegralChanceV1()),
       "selected run tier installs real Event.ai service and source damage window");
   const auto eventSaved=eventWorld.monsterEventActorCheckpoint(owner,1);
   eventWorld.validateMonsterEventActorCheckpoint(eventWorld.monsters[0],eventSaved,eventWorld.nowMs(),1);
   check(eventSaved.at("difficulty")==session.monsterAiDifficulty(),"actual Event.ai actor checkpoint retains validated family selection for restoration");
  }
  for(int hp:{1,999,1000})check(BossHealthLayerView::split(hp,5000).frame==2,"last live Boss layer always uses source red frame2");
  std::set<int> colors;for(int hp:{1000,2000,3000,4000,5000,6000})colors.insert(BossHealthLayerView::split(hp,6000).frame);
  check(colors.size()==6,"six consecutive layers use six distinct source colors");
  check(BossHealthLayerView::split(INT_MAX,INT_MAX).remaining==2147484,"large HP layer arithmetic remains bounded");
  check(BossHealthGeometry::height==26&&BossHealthGeometry::outerHeight==30,"Boss bar rectangle matches requested portrait-height region");
  return {{"status","passed"},{"count",checks.size()},{"checks",checks},{"cards",cards},{"routes",routes},
      {"difficulty_boundary","four-tier AI row selection; difficulty aggression/CD/stat scaling not reconstructed"}};
}
} // namespace dnf
