#pragma once
#include "combat.hpp"
#include "scene.hpp"
#include "font.hpp"
#include "appearance.hpp"
#include "portal_visuals.hpp"
#include "dnf/presentation/characters/character_presentation.hpp"
#include <functional>
#include <SDL.h>
#include <unordered_set>
namespace dnf {
struct ActSpeechBubble;
struct TexturePart {
    SDL_Texture *value=nullptr;
    int x=0,y=0,w=0,h=0;
};
struct Texture {
    SDL_Texture *value = nullptr;
    int w = 0, h = 0, x = 0, y = 0;
    std::vector<TexturePart> parts;
};
struct RendererOptions {
    std::string title = "DNF Native Combat Demo";
    int width = 800, height = 600;
    bool vsync = true, shown = true, resizable = true;
};
class Renderer : private ICharacterDrawSink {
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    Assets &assets_;
    CharacterPresentation characterPresentation_;
    std::unordered_map<std::string, Texture> textures_;
    Bytes font_;
    std::unique_ptr<HintedFont> hintedFont_;
    std::filesystem::path fontSource_;
    std::unordered_set<std::string> failures_;
    std::unordered_map<std::string, PortalVisualPlan> portalPlans_;
    PortalPlaybackClock portalPlayback_;
    std::map<std::string, std::shared_ptr<const MonsterMotion>> monsterMotions_;
    ani_render::RenderProfile renderProfile_ = ani_render::RenderProfile::Legacy1031;
    void drawCharacterAnimation(const CharacterAnimationRequest &) override;
    void reportCharacterIssue(const std::string &key, const Json &issue,
                              bool unsupported) override;
    void drawMonsterMotion(const MonsterMotion &motion, double time, double x, double y,
                           int facing, bool loop, bool silhouette = false, double alpha = 1);
    void drawMonsterFragment(const std::string &image, int frame, double x, double y,
                             double size, double angle, uint8_t alpha);
    Texture &texture(const std::string &path, int frame, bool pure = false);
    Texture &textTexture(const std::string &text, int size);
    void drawImage(std::string path, int frame, double x, double y, int dir, double scaleX,
                   double scaleY, int blend, uint8_t alpha, double angle, bool origin,
                   SDL_Color color, double offsetX = 0, double offsetY = 0, bool snapPixels = false,
                   bool pure = false, const SDL_Rect *source = nullptr, bool sourceAni = false);
    // sourceAni selects the explicit profile and interprets angle as radians;
    // generic sprites retain their public degree-based legacy transform.

  public:
    Json errors = Json::array();
    Json unsupported = Json::array();
    bool vsync = true;
    explicit Renderer(Assets &assets);
    Renderer(Assets &assets, const RendererOptions &options);
    ~Renderer();
    SDL_Renderer *raw() { return renderer_; }
    SDL_Window *window() { return window_; }
    int viewWidth = 800, viewHeight = 600;
    double uiScale = 1;
    SceneViewport sceneView;
    void viewport();
    void viewport(const Scene &);
    void sceneFooter();
    void ui(int width = 800, int height = 600);
    void mouse(int &x, int &y, int width = 800, int height = 600) const;
    std::array<int, 2> outputSize() const;
    void resize(int w, int h);
    void fullscreen(bool enabled);
    std::vector<std::array<int, 2>> modes() const;
    void begin();
    void present();
    void setVsync(bool v);
    void setRenderProfile(ani_render::RenderProfile profile) { renderProfile_ = profile; }
    ani_render::RenderProfile renderProfile() const { return renderProfile_; }
    Json renderProfileReport() const;
    void title(const std::string &s);
    void rect(float x, float y, float w, float h, SDL_Color c, bool fill = true);
    void text(const std::string &s, float x, float y, int size = 16, SDL_Color color = {240, 229, 197, 255});
    int textWidth(const std::string &s, int size = 16);
    Json fontReport() const;
    Json textTextureReport() const;
    bool button(const std::string &s, int x, int y, int w, int h, int mx, int my, bool click,
                bool enabled = true);
    void sprite(std::string path, int frame, double x, double y, int dir = 1, double scale = 1, int blend = 0,
                uint8_t alpha = 255, double angle = 0, bool origin = true, double scaleY = 0,
                SDL_Color color = {255, 255, 255, 255});
    void outlinedSprite(std::string path, int frame, double x, double y, SDL_Color outline,
                        int dir = 1, double scale = 1);
    void animation(const std::string &path, double time, double x, double y, int dir = 1, bool loop = true,
                   std::string overrideImage = "", int frameOverride = -1,
                   double alphaMultiplier = 1, bool pure = false, const ani_clock::Snapshot *clock = nullptr,
                   const std::function<std::string(const std::string &)> &imageResolver = {}, double imageScale = 1,
                   double transformScaleX = 1, double transformScaleY = 1);
    void imageRegion(const std::string &path, int frame, const SDL_Rect &source,
                     float x, float y, float width, float height,
                     SDL_Color color = {255, 255, 255, 255});
    void tileSprite(const std::string &path, int frame, double x, double y);
    void player(const Actor &actor, int64_t ms, double alpha, const CharacterAppearance &appearance,
                double cameraX = 0, double cameraY = 0, const std::string &bodyMotion = "");
    void monster(Pvf &pvf, const Actor &actor, int64_t ms, double interpolation,
                 double cameraX = 0, double cameraY = 0, bool sourceActionConsumed = false);
    void effect(const Effect &effect, int64_t ms, double interpolation,
                double cameraX = 0, double cameraY = 0);
    void actionSpeech(const World &,const std::vector<ActSpeechBubble> &,double interpolation,
                      double cameraX = 0,double cameraY = 0);
    void portal(Pvf &p, const std::string &object, int64_t ms, double x, double y, bool open,
                const std::string &sceneIdentity = {}, int portalIndex = 0);
    // Compatibility only: boss selection belongs to DGN -> OBJ, never IMG filename guessing.
    void portal(Pvf &p,const std::string &object,int64_t ms,double x,double y,bool open,bool) {
        portal(p,object,ms,x,y,open);
    }
    // Observe at fixed simulation boundaries as well as rendering so
    // transition starts are independent of render catch-up grouping.
    void observePortal(const std::string &scene,int instance,const std::string &object,int64_t ms,bool open) {
        (void)portalPlayback_.sample(scene,std::to_string(instance),normalize(object),ms,open);
    }
    Json portalSourceReport() const;
    void screenshot(const std::filesystem::path &p);
    size_t cachedTextures() const { return textures_.size(); }
};
} // namespace dnf
