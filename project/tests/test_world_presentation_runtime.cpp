#include "dnf/selection_ui.hpp"
#include "dnf/target_hud.hpp"
#include "dnf/session.hpp"
#include "dnf/monster_action_ai.hpp"
#include "dnf/monster_event_ai.hpp"
#include <climits>
#include <stdexcept>
namespace dnf {
Json runWorldPresentationRuntimeTests(Pvf &pvf,Assets &assets,const std::filesystem::path &out) {
  std::filesystem::create_directories(out);Json checks=Json::array();
  auto check=[&](bool okay,const char *what){if(!okay)throw std::runtime_error(what);checks.push_back(what);};
  RegionCatalog catalog(pvf,assets);SelectionUi ui;ui.bind(pvf,assets);auto model=captureDungeonSelectionModel(pvf,catalog);
  Renderer renderer(assets,RendererOptions{"Hidden world presentation",800,600,false,false,false});
  auto state=enterDungeonSelection(model);ui.startDungeonPresentation(state,0);const auto selectedLayout=ui.dungeonLayout(model,state.selectedDungeon);
  for(int tier=0;tier<4;++tier){state.difficulty=tier;renderer.begin();renderer.ui();
   ui.drawDungeon(renderer,model,selectedLayout,state,{50,true,4,true},{},1600);
   renderer.screenshot(out/("dungeon-tier-"+std::to_string(tier)+".png"));renderer.present();}
  Actor boss;boss.id=1;boss.boss=true;boss.maxHp=6000;boss.monsterPath="monster/act8/blackscalemoussambani/blackscalemoussambani.mob";TargetHud target;
  for(int hp:{1000,2500,6000}){boss.hp=hp;target.reset();target.hit(boss,100,hp);renderer.begin();renderer.ui();target.draw(renderer,pvf,200);
   renderer.screenshot(out/("boss-"+std::to_string(hp)+".png"));
   Bytes frame(size_t(800)*600*4);
   check(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,frame.data(),800*4)==0,"read actual Boss render pixels");
   auto pixel=[&](int x,int y){const size_t i=(size_t(y)*800+x)*4;return std::array<int,3>{frame[i],frame[i+1],frame[i+2]};};
   if(hp==1000){int redRows=0;for(int y=55;y<100;++y){const auto c=pixel(200,y);if(c[0]>150&&c[1]<40&&c[2]<40)++redRows;}
    check(redRows>=24&&redRows<=28,"actual final red fill spans portrait-height rectangle");}
   if(hp==2500){const auto foreground=pixel(200,75),behind=pixel(600,75);check(foreground!=behind&&foreground[1]>150&&behind[0]>200,
       "actual current and following source layer colors render distinctly");}
   renderer.present();check(boss.hp==hp,"Boss rendering leaves actual actor HP untouched");}
  check(renderer.errors.empty(),"new difficulty row and tall Boss bar render with current source assets");
  return {{"status","passed"},{"count",checks.size()},{"checks",checks},
      {"renderer_errors",renderer.errors},{"renderer_unsupported",renderer.unsupported},
      {"scope","hidden actual pixels; foreground feel and original-client comparison await user"}};
}
} // namespace dnf
