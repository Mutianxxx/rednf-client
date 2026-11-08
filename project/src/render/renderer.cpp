#include "dnf/renderer.hpp"
#include "dnf/boss_aura_ui.hpp"
#include "dnf/monster_equipment.hpp"
#include "dnf/act_world_host.hpp"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
namespace dnf {
static std::string relativePath(const std::string &, const std::string &);
namespace {
std::vector<uint32_t> textCodepoints(const std::string &s) {
    std::vector<uint32_t> chars;
    for (size_t i = 0; i < s.size();) {
        const uint8_t first = uint8_t(s[i++]);
        if (first < 0x80) { chars.push_back(first); continue; }
        int remaining = first >= 0xf0 && first <= 0xf4 ? 3 :
                        first >= 0xe0 && first <= 0xef ? 2 :
                        first >= 0xc2 && first <= 0xdf ? 1 : -1;
        if (remaining < 0) { chars.push_back(0xfffd); continue; }
        uint32_t cp = first & (remaining == 3 ? 7 : remaining == 2 ? 15 : 31);
        const uint32_t minimum = remaining == 3 ? 0x10000 : remaining == 2 ? 0x800 : 0x80;
        bool valid = true;
        for (int n = 0; n < remaining; ++n) {
            if (i == s.size() || (uint8_t(s[i]) & 0xc0) != 0x80) { valid = false; break; }
            cp = (cp << 6) | (uint8_t(s[i++]) & 63);
        }
        if (!valid || cp < minimum || cp > 0x10ffff || (cp >= 0xd800 && cp <= 0xdfff)) cp = 0xfffd;
        chars.push_back(cp);
    }
    return chars;
}
float textAdvance(const stbtt_fontinfo &font, const std::vector<uint32_t> &chars, float scale) {
    float advance = 0;
    for (size_t i = 0; i < chars.size(); ++i) {
        int adv;
        stbtt_GetCodepointHMetrics(&font, chars[i], &adv, nullptr);
        advance += adv * scale;
        if (i + 1 < chars.size())
            advance += stbtt_GetCodepointKernAdvance(&font, chars[i], chars[i + 1]) * scale;
    }
    return advance;
}
} // namespace
Renderer::Renderer(Assets &a) : Renderer(a,RendererOptions{}) {}
Renderer::Renderer(Assets &a, const RendererOptions &options)
    : assets_(a), characterPresentation_(a, *this) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    const auto flags = SDL_WINDOW_ALLOW_HIGHDPI | (options.shown ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN) |
                       (options.resizable ? SDL_WINDOW_RESIZABLE : 0);
    window_ = SDL_CreateWindow(options.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               options.width, options.height, flags);
    if (!window_)
        throw std::runtime_error(SDL_GetError());
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED |
                                   (options.vsync ? SDL_RENDERER_PRESENTVSYNC : 0));
    if (!renderer_)
        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer_) {
        const std::string error = SDL_GetError();
        SDL_DestroyWindow(window_); window_ = nullptr;
        throw std::runtime_error(error);
    }
    // SDL's software renderer can start with PRESENTVSYNC even when the
    // create flags omit it. Apply the requested policy to the created driver,
    // including the fallback, so a secondary tools window cannot stall a tick.
    if (SDL_RenderSetVSync(renderer_, options.vsync ? 1 : 0) != 0 && !options.vsync) {
        const std::string error = SDL_GetError();
        SDL_DestroyRenderer(renderer_); renderer_ = nullptr;
        SDL_DestroyWindow(window_); window_ = nullptr;
        throw std::runtime_error("Cannot disable renderer vsync: " + error);
    }
    vsync = options.vsync;
    SDL_SetWindowMinimumSize(window_, 640, 480);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    // A host font outside the selected content identity would silently change
    // glyphs and metrics. Missing source fonts are an explicit content error.
    try {
        fontSource_ = a.staticFile("Fonts/msjh.ttf");
        font_ = a.staticBytes("Fonts/msjh.ttf");
        hintedFont_ = std::make_unique<HintedFont>(font_);
    } catch (...) {
        SDL_DestroyRenderer(renderer_); renderer_ = nullptr;
        SDL_DestroyWindow(window_); window_ = nullptr;
        throw;
    }
}
Renderer::~Renderer() {
    for (auto &t : textures_) {
        if(t.second.value)SDL_DestroyTexture(t.second.value);
        for(const auto &part:t.second.parts)if(part.value)SDL_DestroyTexture(part.value);
    }
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}
std::array<int, 2> Renderer::outputSize() const {
    int w, h;
    SDL_GetRendererOutputSize(renderer_, &w, &h);
    return {w, h};
}
void Renderer::viewport() {
    auto [w, h] = outputSize();
    sceneView = sceneViewport(w, h);
    SDL_RenderSetViewport(renderer_, nullptr);
    SDL_RenderSetClipRect(renderer_, nullptr);
    uiScale = sceneView.scale;
    viewWidth = int(std::ceil(sceneView.width));
    viewHeight = int(std::ceil(sceneView.height));
    SDL_RenderSetScale(renderer_, float(uiScale), float(uiScale));
}
void Renderer::viewport(const Scene &scene) {
    auto [w, h] = outputSize();
    sceneView = sceneViewport(w, h, scene);
    SDL_RenderSetViewport(renderer_, nullptr);
    SDL_RenderSetClipRect(renderer_, nullptr);
    uiScale = sceneView.scale;
    viewWidth = int(std::ceil(sceneView.width));
    viewHeight = int(std::ceil(sceneView.height));
    SDL_RenderSetScale(renderer_, float(uiScale), float(uiScale));
}
void Renderer::sceneFooter() {
    auto &t = texture("interface2/hud/hud.img", 84);
    // The existing footer retains its 43/600 output-height fraction. Derive
    // both device edges from one frame's viewport so resize and a narrow-map
    // scene scale cannot detach the source footer from the actual output edge.
    const double top = std::floor(sceneView.gameplayBottom * sceneView.scale) / sceneView.scale;
    imageRegion("interface2/hud/hud.img", 84, {0, 0, t.w, t.h}, 0, float(top),
                float(sceneView.width), float(sceneView.height - top));
}
void Renderer::ui(int width, int height) {
    auto [w, h] = outputSize();
    if (width <= 0 || height <= 0) throw std::invalid_argument("UI canvas dimensions must be positive");
    float scale = std::min(w / float(width), h / float(height));
    SDL_Rect vp{int((w - width * scale) / 2), int((h - height * scale) / 2), int(width * scale), int(height * scale)};
    SDL_RenderSetViewport(renderer_, &vp);
    SDL_RenderSetScale(renderer_, scale, scale);
    SDL_RenderSetClipRect(renderer_, nullptr);
}
void Renderer::mouse(int &x, int &y, int width, int height) const {
    int ww, wh;
    SDL_GetWindowSize(window_, &ww, &wh);
    auto [w, h] = outputSize();
    if (width <= 0 || height <= 0) throw std::invalid_argument("UI canvas dimensions must be positive");
    double scale = std::min(w / double(width), h / double(height));
    x = int((x * double(w) / ww - (w - width * scale) / 2) / scale);
    y = int((y * double(h) / wh - (h - height * scale) / 2) / scale);
}
void Renderer::resize(int w, int h) {
    if (w >= 640 && h >= 480) {
        SDL_SetWindowFullscreen(window_, 0);
        SDL_SetWindowSize(window_, w, h);
        viewport();
    }
}
void Renderer::fullscreen(bool enabled) {
    SDL_SetWindowFullscreen(window_, enabled ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    viewport();
}
std::vector<std::array<int, 2>> Renderer::modes() const {
    std::vector<std::array<int, 2>> out = {
        {{800, 600}}, {{1024, 768}}, {{1280, 720}}, {{1600, 900}}, {{1920, 1080}}};
    int display = SDL_GetWindowDisplayIndex(window_);
    for (int i = 0; i < SDL_GetNumDisplayModes(display); i++) {
        SDL_DisplayMode m;
        if (SDL_GetDisplayMode(display, i, &m) == 0 && m.w >= 640 && m.h >= 480) {
            std::array<int, 2> size{m.w, m.h};
            if (std::find(out.begin(), out.end(), size) == out.end())
                out.push_back(size);
        }
    }
    std::sort(out.begin(), out.end());
    return out;
}
void Renderer::begin() {
    SDL_SetRenderDrawColor(renderer_, 9, 12, 17, 255);
    SDL_RenderClear(renderer_);
}
void Renderer::present() { SDL_RenderPresent(renderer_); }
void Renderer::setVsync(bool v) {
    if (SDL_RenderSetVSync(renderer_, v ? 1 : 0) == 0)
        vsync = v;
    else
        errors.push_back({{"vsync", v}, {"error", SDL_GetError()}});
}
void Renderer::title(const std::string &s) { SDL_SetWindowTitle(window_, s.c_str()); }
Json Renderer::renderProfileReport() const {
    return {{"profile", ani_render::profileName(renderProfile_)},
            {"evidence", ani_render::profileEvidence(renderProfile_)},
            {"contract", renderProfile_ == ani_render::RenderProfile::Inferred60Us1031 ?
                "reverse-60us/releases/20261020-01/analysis/combat_render" : "existing-1031-renderer"},
            {"native_1031_verified", false}, {"original_game_pixel_comparison", false},
            {"pivot", "normal-image-position"}, {"native_game_clock", false}};
}
void Renderer::rect(float x, float y, float w, float h, SDL_Color c, bool fill) {
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
    SDL_FRect r{x, y, w, h};
    if (fill)
        SDL_RenderFillRectF(renderer_, &r);
    else
        SDL_RenderDrawRectF(renderer_, &r);
}
Texture &Renderer::texture(const std::string &p, int frame, bool pure) {
    std::string key = normalize(p) + "#" + std::to_string(frame) + (pure ? ":alpha-mask" : "");
    auto it = textures_.find(key);
    if (it != textures_.end())
        return it->second;
    Texture t;
    try {
        auto pix = assets_.pixels(p, frame);
        t.w = pix.width;
        t.h = pix.height;
        t.x = pix.x;
        t.y = pix.y;
        if (pure)
            for (size_t i = 0; i < pix.rgba.size(); i += 4)
                pix.rgba[i] = pix.rgba[i + 1] = pix.rgba[i + 2] = 255;
        if (t.w && t.h) {
            t.value =
                SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, t.w, t.h);
            if (!t.value)
                throw std::runtime_error(SDL_GetError());
            SDL_UpdateTexture(t.value, nullptr, pix.rgba.data(), t.w * 4);
            SDL_SetTextureBlendMode(t.value, SDL_BLENDMODE_BLEND);
        }
    } catch (const std::exception &e) {
        errors.push_back({{"resource", p}, {"frame", frame}, {"error", e.what()}});
    }
    return textures_.emplace(key, t).first->second;
}
void Renderer::sprite(std::string p, int frame, double x, double y, int dir, double scale, int blend,
                      uint8_t alpha, double angle, bool origin, double scaleY, SDL_Color color) {
    drawImage(std::move(p), frame, x, y, dir, scale, scaleY == 0 ? scale : scaleY,
              blend, alpha, angle, origin, color);
}
void Renderer::outlinedSprite(std::string p, int frame, double x, double y, SDL_Color outline,
                              int dir, double scale) {
    const std::string path = p;
    // Field drops get the thin yellow pickup keyline visible in the source
    // capture. A few offset alpha silhouettes leave the original sprite crisp.
    for (const auto &offset : std::array<std::array<double, 2>, 4>{{{{-1, 0}}, {{1, 0}}, {{0, -1}}, {{0, 1}}}})
        drawImage(path, frame, x + offset[0], y + offset[1], dir, scale, scale, 0,
                  uint8_t(std::min(255, int(outline.a))), 0, true, outline, 0, 0, false, true);
    drawImage(path, frame, x, y, dir, scale, scale, 0, 255, 0, true,
              {255, 255, 255, 255});
}
void Renderer::drawImage(std::string p, int frame, double x, double y, int dir, double scale,
                         double scaleY, int blend, uint8_t alpha, double angle, bool origin,
                         SDL_Color color, double offsetX, double offsetY, bool snapPixels,
                         bool pure, const SDL_Rect *source, bool sourceAni) {
    for (auto spec : {std::pair<const char *, const char *>{"%04d", "0000"}, {"%02d", "00"}}) {
        size_t pos;
        while ((pos = p.find(spec.first)) != p.npos)
            p.replace(pos, 4, spec.second);
    }
    const auto profile = sourceAni ? renderProfile_ : ani_render::RenderProfile::Legacy1031;
    const bool inferred = profile == ani_render::RenderProfile::Inferred60Us1031;
    if (blend == 5 && !inferred) pure = true;
    auto &t = texture(p, frame, pure);
    if (!t.value)
        return;
    SDL_Rect src = source ? *source : SDL_Rect{0, 0, t.w, t.h};
    ani_render::QuadInput input;
    input.pose.position = {offsetX, offsetY};
    input.pose.rate = {scale, scaleY};
    // Public sprite/particle angles remain degrees. ANI retains authored radians
    // all the way to the shared numeric transform.
    input.pose.angle = sourceAni ? angle : angle * 3.14159265358979323846 / 180.0;
    input.actorX = x; input.actorY = y;
    input.cropX = (origin ? t.x : 0) + src.x;
    input.cropY = (origin ? t.y : 0) + src.y;
    input.width = src.w; input.height = src.h; input.direction = dir;
    auto quad = ani_render::makeQuad(input, profile).vertices;
    if (snapPixels) {
        // Adjacent TILs must share the same device-pixel boundary at fractional
        // window scales (e.g. 1.2 at 1280x720), including a fractional camera.
        float sx, sy;
        SDL_RenderGetScale(renderer_, &sx, &sy);
        for (auto &point : quad) {
            point.x = std::round(point.x * sx) / sx;
            point.y = std::round(point.y * sy) / sy;
        }
    }
    const auto mode = ani_render::classifyBlend(blend);
    const bool additive = inferred ? mode == ani_render::BlendMode::LinearDodge : blend == 1 || blend == 2;
    if (SDL_SetTextureBlendMode(t.value, additive ? SDL_BLENDMODE_ADD : SDL_BLENDMODE_BLEND) != 0 &&
        failures_.insert("blend-backend:" + p).second)
        errors.push_back({{"blend_source", p}, {"profile", ani_render::profileName(profile)}, {"error", SDL_GetError()}});
    const bool unknown = inferred ? mode == ani_render::BlendMode::Unsupported : blend != 0 && blend != 5;
    if (unknown && failures_.insert(std::string(ani_render::profileName(profile)) + ":blend:" + std::to_string(blend)).second)
        unsupported.push_back({{"graphic_effect", blend}, {"fallback", additive ? "SDL additive approximation" : "alpha blend"},
                               {"source", p}, {"profile", ani_render::profileName(profile)},
                               {"evidence", ani_render::profileEvidence(profile)}, {"PC_equivalence", false}});
    // Geometry supplies modulation per vertex; clear modulation left by text.
    SDL_SetTextureAlphaMod(t.value, 255);
    SDL_SetTextureColorMod(t.value, 255, 255, 255);
    color.a = alpha;
    float u0 = float(src.x) / t.w, u1 = float(src.x + src.w) / t.w;
    float v0 = float(src.y) / t.h, v1 = float(src.y + src.h) / t.h;
    const SDL_FPoint uv[] = {{u0, v0}, {u1, v0}, {u1, v1}, {u0, v1}};
    SDL_Vertex vertices[4];
    for (int i = 0; i < 4; ++i)
        vertices[i] = {{float(quad[i].x), float(quad[i].y)}, color, uv[i]};
    const int indices[] = {0, 1, 2, 0, 2, 3};
    if (SDL_RenderGeometry(renderer_, t.value, vertices, 4, indices, 6) != 0 &&
        failures_.insert("geometry:" + p).second)
        errors.push_back({{"geometry", p}, {"error", SDL_GetError()}});
}
void Renderer::actionSpeech(const World &world,const std::vector<ActSpeechBubble> &bubbles,double interpolation,
                            double cameraX,double cameraY) {
    for(const auto &bubble:bubbles) {
        const auto *actor=world.resolveActor(bubble.speaker);
        if(!actor || actor->dead || bubble.expiresMs<=uint64_t(world.nowMs())) continue;
        const auto a=std::clamp(interpolation,0.0,1.0);
        const auto x=actor->px+(actor->x-actor->px)*a-cameraX;
        const auto y=actor->py+(actor->y-actor->py)*a-(actor->pz+(actor->z-actor->pz)*a)-cameraY-90;
        const auto width=textWidth(bubble.text,14);
        text(bubble.text,float(x-width/2),float(y),14,{255,245,215,255});
    }
}
void Renderer::tileSprite(const std::string &path, int frame, double x, double y) {
    drawImage(path, frame, x, y, 1, 1, 1, 0, 255, 0, true, {255, 255, 255, 255}, 0, 0, true);
}
void Renderer::animation(const std::string &path, double time, double x, double y, int dir, bool loop,
                         std::string overrideImage, int frameOverride, double alphaMultiplier, bool pure,
                         const ani_clock::Snapshot *clock,
                         const std::function<std::string(const std::string &)> &imageResolver, double imageScale,
                         double transformScaleX, double transformScaleY) {
    try {
        auto a = assets_.animation(path);
        if (a->frames.empty())
            return;
        auto pose = a->samplePose(time, loop, frameOverride, renderProfile_, clock);
        if (pose.image.empty() && overrideImage.empty())
            return;
        auto byte = [&](double v) {
            return renderProfile_ == ani_render::RenderProfile::Inferred60Us1031 ? ani_render::colorByte(v) :
                uint8_t(std::lround(std::clamp(v, 0.0, 255.0)));
        };
        SDL_Color color{byte(pose.rgba[0]), byte(pose.rgba[1]), byte(pose.rgba[2]), 255};
        if (pure) color = {255, 255, 255, 255};
        if (pose.blend == 5 && renderProfile_ == ani_render::RenderProfile::Legacy1031)
            color = {pose.effectRgb[0], pose.effectRgb[1], pose.effectRgb[2], 255};
        if (!pose.unsupported.empty() && failures_.insert("nodes:" + path).second)
            unsupported.push_back({{"animation", path}, {"unconsumed_render_nodes", pose.unsupported}});
        if (pose.flip & 1) pose.scaleX = -pose.scaleX;
        if (pose.flip & 2) pose.scaleY = -pose.scaleY;
        // Resolve the image selected by this pose, including animations that
        // switch IMG paths after frame zero. Never pin a portal to its first IMG.
        auto image=overrideImage.empty()?pose.image:overrideImage;
        if(imageResolver)image=imageResolver(image);
        drawImage(image, pose.imageFrame, x, y, dir,
                  pose.scaleX * imageScale * transformScaleX, pose.scaleY * imageScale * transformScaleY, pure ? 0 : pose.blend,
                  byte(pose.rgba[3] * std::clamp(alphaMultiplier, 0.0, 1.0)),
                  pose.rotationRadians, true, color, pose.x, pose.y, false, pure, nullptr, true);
    } catch (const std::exception &e) {
        if (failures_.insert(path).second)
            errors.push_back({{"animation", path}, {"error", e.what()}});
    }
}
void Renderer::imageRegion(const std::string &path, int frame, const SDL_Rect &source,
                           float x, float y, float width, float height, SDL_Color color) {
    auto &t = texture(path, frame);
    if (!t.value || width <= 0 || height <= 0) return;
    SDL_SetTextureColorMod(t.value, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(t.value, color.a);
    SDL_SetTextureBlendMode(t.value, SDL_BLENDMODE_BLEND);
    SDL_FRect target{x, y, width, height};
    if (SDL_RenderCopyF(renderer_, t.value, &source, &target) != 0 &&
        failures_.insert("region:" + path).second)
        errors.push_back({{"region", path}, {"error", SDL_GetError()}});
}
Texture &Renderer::textTexture(const std::string &s, int size) {
    std::string key = "text:" + std::to_string(size) + ":" + s;
    auto it = textures_.find(key);
    if (it == textures_.end()) {
        // The reference client uses a compact one-pixel keyline with a very
        // faint second pixel. A three-pixel opaque dilation makes small HUD
        // labels look swollen and obscures the glyph's bright centre.
        constexpr int outlineRadius = 2;
        constexpr int pad = outlineRadius + 1;
        FontMask hinted;
        int width, height, advance;
        Bytes mask;
        if (hintedFont_->mask(s, size, pad, hinted)) {
            width = hinted.width; height = hinted.height; advance = hinted.advance;
            mask = std::move(hinted.coverage);
        } else {
            stbtt_fontinfo info;
            if (!stbtt_InitFont(&info, font_.data(), stbtt_GetFontOffsetForIndex(font_.data(), 0)))
                throw std::runtime_error("Cannot initialize UI font");
            float scale = stbtt_ScaleForPixelHeight(&info, float(size));
            int ascent, descent, gap;
            stbtt_GetFontVMetrics(&info, &ascent, &descent, &gap);
            ascent = int(ascent * scale);
            const auto chars = textCodepoints(s);
            const float logicalAdvance = textAdvance(info, chars, scale);
            advance = int(std::lround(logicalAdvance));
            width = 2 * pad + int(std::ceil(logicalAdvance)) + 1;
            height = size + 2 * pad + 2;
            mask.resize(size_t(width) * height, 0);
            float pen = float(pad);
            for (size_t i = 0; i < chars.size(); ++i) {
                auto c = chars[i];
                int w, h, ox, oy, adv;
                auto bitmap = stbtt_GetCodepointBitmap(&info, 0, scale, c, &w, &h, &ox, &oy);
                stbtt_GetCodepointHMetrics(&info, c, &adv, nullptr);
                for (int yy = 0; yy < h; yy++)
                    for (int xx = 0; xx < w; xx++) {
                        int px = int(std::lround(pen)) + ox + xx, py = pad + ascent + oy + yy;
                        if (px >= 0 && py >= 0 && px < width && py < height) {
                            auto &coverage = mask[size_t(py) * width + px];
                            coverage = std::max(coverage, bitmap[yy * w + xx]);
                        }
                    }
                stbtt_FreeBitmap(bitmap, nullptr);
                pen += adv * scale;
                if (i + 1 < chars.size())
                    pen += stbtt_GetCodepointKernAdvance(&info, c, chars[i + 1]) * scale;
            }
        }
        // DNF text uses a dark, feathered outline around a bright glyph. The
        // outline is kept in the cached texture so every caller gets the same
        // readable treatment while the caller's colour still modulates the
        // white glyph centre.
        Bytes rgba(size_t(width) * height * 4, 0);
        for (int py = 0; py < height; ++py) {
            for (int px = 0; px < width; ++px) {
                // Reconstruct a compact distance-graded keyline. Include it
                // underneath antialiased glyph pixels, otherwise those pixels
                // disappear over Seria's bright background. These weights are
                // an approximation from screenshots, not decoded PC settings.
                const double fill = std::pow(mask[size_t(py) * width + px] / 255.0, 0.75);
                double outline = 0;
                for (int dy = -outlineRadius; dy <= outlineRadius; ++dy)
                    for (int dx = -outlineRadius; dx <= outlineRadius; ++dx) {
                        int distance2 = dx * dx + dy * dy;
                        if (distance2 > 4) continue;
                        int sx = px + dx, sy = py + dy;
                        if (sx < 0 || sy < 0 || sx >= width || sy >= height) continue;
                        double weight = distance2 <= 1 ? 0.96 : distance2 == 2 ? 0.68 : 0.18;
                        outline = std::max(outline, mask[size_t(sy) * width + sx] / 255.0 * weight);
                    }
                size_t z = (size_t(py) * width + px) * 4;
                const double alpha = fill + outline * (1 - fill);
                if (alpha > 0) {
                    // Straight alpha, glyph over black. Do not multiply glyph
                    // coverage into both RGB and alpha (the old dark centre).
                    rgba[z] = rgba[z + 1] = rgba[z + 2] = uint8_t(std::lround(255 * fill / alpha));
                    rgba[z + 3] = uint8_t(std::lround(255 * alpha));
                }
            }
        }
        Texture t;
        t.w = width;
        t.h = height;
        t.x = int(std::lround(advance)); // logical advance; excludes outline padding
        SDL_RendererInfo driver{};
        if(SDL_GetRendererInfo(renderer_,&driver)!=0)throw std::runtime_error(SDL_GetError());
        // Upload tiles of the same fully rasterized mask. Glyph shaping,
        // advances and outline pixels stay identical across tile boundaries.
        // Some SDL software drivers report no bound; retain a portable budget.
        const int limitW=driver.max_texture_width>0?std::min(4096,driver.max_texture_width):4096;
        const int limitH=driver.max_texture_height>0?std::min(4096,driver.max_texture_height):4096;
        const auto upload=[&](int left,int top,int w,int h) {
            SDL_Texture *value=SDL_CreateTexture(renderer_,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STATIC,w,h);
            if(!value)throw std::runtime_error("UI text texture upload: "+std::string(SDL_GetError()));
            const auto *pixels=rgba.data()+(size_t(top)*size_t(width)+size_t(left))*4;
            if(SDL_UpdateTexture(value,nullptr,pixels,width*4)!=0||SDL_SetTextureBlendMode(value,SDL_BLENDMODE_BLEND)!=0) {
                const auto error=std::string(SDL_GetError());SDL_DestroyTexture(value);
                throw std::runtime_error("UI text texture update: "+error);
            }
            return value;
        };
        try {
            if(width<=limitW&&height<=limitH)t.value=upload(0,0,width,height);
            else {
                t.parts.reserve(((size_t(width)+limitW-1)/limitW)*((size_t(height)+limitH-1)/limitH));
                for(int top=0;top<height;top+=limitH)for(int left=0;left<width;left+=limitW) {
                    const int w=std::min(limitW,width-left),h=std::min(limitH,height-top);
                    t.parts.push_back({upload(left,top,w,h),left,top,w,h});
                }
            }
            it=textures_.emplace(key,t).first;
        }catch(...) {
            if(t.value)SDL_DestroyTexture(t.value);
            for(const auto &part:t.parts)if(part.value)SDL_DestroyTexture(part.value);
            throw;
        }
    }
    return it->second;
}
int Renderer::textWidth(const std::string &s, int size) {
    if (s.empty() || size <= 0) return 0;
    int hinted = hintedFont_->width(s, size);
    if (hinted >= 0) return hinted;
    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, font_.data(), stbtt_GetFontOffsetForIndex(font_.data(), 0)))
        throw std::runtime_error("Cannot initialize UI font");
    // Measurement does not rasterize or cache unused labels. This is also used
    // for wrapping quest/dialogue paragraphs one glyph at a time.
    return int(std::lround(textAdvance(info, textCodepoints(s), stbtt_ScaleForPixelHeight(&info, float(size)))));
}
Json Renderer::fontReport() const {
    return {{"source", fontSource_.u8string()}, {"bytes", font_.size()},
            {"backend", hintedFont_->available() ? "Windows GDI grayscale, TrueType grid fit" : "stb_truetype, unhinted fallback"},
            {"source_glyph_and_hint_tables_verified", hintedFont_->available()},
            {"font_registration", "process-private memory only, no installed font changes"},
            {"outline", "reconstructed distance-graded black edge, bright glyph centre"},
            {"PC_pixel_parity", false}};
}
Json Renderer::textTextureReport() const {
    size_t entries=0,tiled=0,parts=0;int maxWidth=0,maxHeight=0,largestLogicalWidth=0;
    for(const auto &[key,texture]:textures_)if(key.rfind("text:",0)==0) {
        ++entries;largestLogicalWidth=std::max(largestLogicalWidth,texture.w);
        if(!texture.parts.empty())++tiled;
        if(texture.value){++parts;maxWidth=std::max(maxWidth,texture.w);maxHeight=std::max(maxHeight,texture.h);}
        for(const auto &part:texture.parts){++parts;maxWidth=std::max(maxWidth,part.w);maxHeight=std::max(maxHeight,part.h);}
    }
    return {{"entries",entries},{"tiled_entries",tiled},{"parts",parts},{"largest_logical_width",largestLogicalWidth},
        {"maximum_uploaded_size",{maxWidth,maxHeight}},{"upload_policy","exact-mask-tiles-up-to-driver-limit-or-4096"}};
}
void Renderer::text(const std::string &s, float x, float y, int size, SDL_Color color) {
    if (s.empty() || size <= 0) return;
    auto &t = textTexture(s, size);
    const auto draw=[&](SDL_Texture *value,int left,int top,int width,int height) {
        SDL_SetTextureColorMod(value,color.r,color.g,color.b);SDL_SetTextureAlphaMod(value,color.a);
        SDL_FRect dst{x-3.0f+left,y-3.0f+top,float(width),float(height)};
        SDL_RenderCopyF(renderer_,value,nullptr,&dst);
    };
    if(t.value)draw(t.value,0,0,t.w,t.h);
    for(const auto &part:t.parts)draw(part.value,part.x,part.y,part.w,part.h);
}
bool Renderer::button(const std::string &s, int x, int y, int w, int h, int mx, int my, bool click,
                      bool enabled) {
    bool hover = enabled && mx >= x && mx < x + w && my >= y && my < y + h;
    rect(x, y, w, h,
         enabled ? hover ? SDL_Color{68, 94, 104, 240} : SDL_Color{32, 43, 54, 240}
                 : SDL_Color{28, 28, 32, 220});
    rect(x, y, w, h, hover ? SDL_Color{225, 192, 110, 255} : SDL_Color{123, 106, 72, 255}, false);
    text(s, x + 8, y + (h - 18) / 2, 16,
         enabled ? SDL_Color{242, 230, 193, 255} : SDL_Color{112, 110, 106, 255});
    return hover && click;
}
void Renderer::drawCharacterAnimation(const CharacterAnimationRequest &request) {
    animation(request.path, request.elapsedMs, request.x, request.y, request.direction,
              request.loop, request.imageOverride, request.frameOverride, 1, false,
              request.clock ? &*request.clock : nullptr, {}, 1, request.scaleX, request.scaleY);
}
void Renderer::reportCharacterIssue(const std::string &key, const Json &issue,
                                    bool isUnsupported) {
    if (!failures_.insert(key).second) return;
    if (isUnsupported) unsupported.push_back(issue);
    else errors.push_back(issue);
}
void Renderer::player(const Actor &actor, int64_t ms, double interpolation,
                       const CharacterAppearance &appearance,
                       double cameraX, double cameraY, const std::string &bodyMotion) {
    characterPresentation_.draw(actor, ms, interpolation, appearance, renderProfile_,
                                cameraX, cameraY, bodyMotion);
}
void Renderer::drawMonsterMotion(const MonsterMotion &motion, double elapsed, double x, double y,
                                 int facing, bool loop, bool silhouette, double alpha) {
    if (!motion.valid()) return;
    const double time = monsterMotionTime(motion, elapsed, loop);
    for (const auto &track : motion.tracks) {
        if (time < track.start || (!track.hold && time >= track.end)) continue;
        const auto clock=monsterTrackClock(motion,track,time);
        animation(track.animation->path, time - track.start, x + facing * track.x, y + track.y,
                  facing, track.loop, "", -1, alpha, silhouette,clock?&*clock:nullptr);
    }
}
void Renderer::drawMonsterFragment(const std::string &path, int frame, double x, double y,
                                   double size, double angle, uint8_t alpha) {
    auto &image = texture(path, frame);
    if (!image.value) return;
    // PTL substitutes the palette image into an image-free ANI. The selected
    // crop is centered on the particle; corpse rectangles are never reused.
    drawImage(path, frame, x, y, 1, size, size, 0, alpha, angle, false,
              {255, 255, 255, 255}, -image.w * .5, -image.h * .5);
}
void Renderer::monster(Pvf &pvf, const Actor &p, int64_t ms, double a,
                        double cameraX, double cameraY,bool sourceActionConsumed) {
    if (p.life == ActorLife::Removed) return;
    const bool alive = p.life == ActorLife::Alive;
    std::shared_ptr<const MonsterMotion> motion = p.deathMotion;
    if (alive || !motion) {
        const auto path = p.monsterPath.empty() ? "monster/goblin/goblin.mob" : p.monsterPath;
        const auto key = normalize(path) + "|" + p.animation;
        auto found = monsterMotions_.find(key);
        if (found == monsterMotions_.end())
            found = monsterMotions_.emplace(key, compileMonsterMotion(pvf, assets_, path, p.animation)).first;
        motion = found->second;
        if (!p.animationPath.empty() && (!motion->valid() || motion->base->path != normalize(p.animationPath))) {
            const auto overrideKey = key + "|" + normalize(p.animationPath);
            auto selected = monsterMotions_.find(overrideKey);
            if (selected == monsterMotions_.end())
                selected = monsterMotions_.emplace(overrideKey,
                    compileMonsterAnimationForMob(pvf, assets_, path, p.animationPath, p.animation)).first;
            motion = selected->second;
        }
    }
    if (!motion->valid()) {
        const auto key = "monster-motion:" + p.monsterPath + "|" + p.animation;
        if (failures_.insert(key).second)
            errors.push_back({{"monster", p.monsterPath}, {"state", p.animation},
                              {"error", motion->error.empty() ? "No explicit state resource" : motion->error}});
        return;
    }
    const auto issueKey = "monster-plan:" + motion->entry + (sourceActionConsumed?"|action-consumed":"|visual-only");
    if (!failures_.count(issueKey)) {
        Json issues=Json::array();
        for(const auto &issue:motion->issues)
            if(!sourceActionConsumed || (!issue.contains("unexecuted_act_tag") && !issue.contains("unexecuted_motion_tag")))
                issues.push_back(issue);
        if (!issues.empty())
            unsupported.push_back({{"monster", p.monsterPath}, {"entry", motion->entry}, {"issues", std::move(issues)}});
        failures_.insert(issueKey);
    }
    if (alive) {
        drawSourceBossAura(*this,p,ms,a,cameraX,cameraY);
        const double x = p.px + (p.x - p.px) * a - cameraX;
        const double y = p.py + (p.y - p.py) * a - (p.pz + (p.z - p.pz) * a) - cameraY;
        const bool loop = p.animation == "move" || p.animation == "stay";
        drawMonsterMotion(*motion, ms - p.animStart, x, y, p.dir, loop);
        if (ms < p.hitFlashUntil)
            drawMonsterMotion(*motion, ms - p.animStart, x, y, p.dir, loop, true,
                              std::clamp((p.hitFlashUntil - ms) / 175.0, 0.0, 1.0));
        return;
    }
    const double elapsed = std::max<int64_t>(0, ms - p.deathStart);
    const double x = p.deathAnchorX - cameraX, groundY = p.deathAnchorY - cameraY;
    if (p.independentDeath) {
        drawMonsterMotion(*motion, elapsed, x, groundY - p.deathHeight, p.dir, false);
        return;
    }
    if (p.deathRoute != "shared-source-palette") {
        drawMonsterMotion(*motion, p.deathPoseTime, x, groundY - p.deathHeight, p.dir,
                          p.deathLoop, false, std::clamp(1 - elapsed / p.deathDuration, 0.0, 1.0));
        return;
    }
    const double fade = std::clamp(1 - (elapsed - monsterDeathBurstMs) / monsterDeathFadeMs, 0.0, 1.0);
    if (fade > 0)
        drawMonsterMotion(*motion, p.deathPoseTime, x, groundY - p.deathHeight, p.dir,
                          p.deathLoop, elapsed >= monsterDeathWhiteMs, fade);
    if (elapsed < monsterDeathBurstMs) return;
    const double age = elapsed - monsterDeathBurstMs;
    const auto &profile = p.deathProfile;
    if (profile.pieces && age < monsterFragmentDisplayMs(profile)) {
        const auto pose = assets_.animation(profile.pieceAnimation)->samplePose(age, false, -1, renderProfile_);
        const double alpha = std::clamp(pose.rgba[3], 0.0, 255.0) * monsterFragmentOpacity(profile, age);
        for (const auto &fragment : p.deathFragments) {
            const auto pos = monsterFragmentPose(fragment, age / 1000, profile.gravity);
            drawMonsterFragment(profile.image, fragment.frame, x + pos.x, groundY + pos.y - pos.z,
                                fragment.size, pos.angle, uint8_t(std::lround(alpha)));
        }
    }
    const auto &b = p.deathBounds;
    if (profile.flash && age < assets_.animation(profile.flashAnimation)->duration)
        animation(profile.flashAnimation, age, x + b[0] + b[2] * .5,
                  groundY - p.deathHeight + b[1] + b[3] * .5, 1, false);
    if (profile.smoke && age < assets_.animation(profile.smokeAnimation)->duration)
        animation(profile.smokeAnimation, age, x + b[0] + b[2] * .5,
                  groundY - p.deathHeight + b[1] + b[3], 1, false, "", -1, .35);
}
void Renderer::effect(const Effect &fx, int64_t ms, double a, double cameraX, double cameraY) {
    if (!fx.drawSelf || ms < fx.born || ms >= fx.expires) return;
    // Parent attachment and local motion are owned by the simulation; no second
    // application of offset/facing here. The queue consumes fx.layer/parentId.
    animation(fx.animation, double(ms - fx.born + fx.animationOffset),
              fx.px + (fx.x - fx.px) * a - cameraX,
              fx.py + (fx.y - fx.py) * a - (fx.pz.value_or(fx.z) + (fx.z - fx.pz.value_or(fx.z)) * a) - cameraY,
              fx.dir, fx.loop, "", -1, 1, false, fx.animationClock ? &*fx.animationClock : nullptr, {}, fx.imageScale);
}
void Renderer::portal(Pvf &p,const std::string &object,int64_t ms,double x,double y,bool open,
                      const std::string &sceneIdentity,int portalIndex) {
    const auto key="portal:"+p.identity()+":"+normalize(object)+(open?":open":":closed");
    if(failures_.count(key))return;
    try {
        auto cached=portalPlans_.find(key);
        if(cached==portalPlans_.end())cached=portalPlans_.emplace(key,portalVisuals(p,object,open)).first;
        const auto time=portalPlayback_.sample(sceneIdentity.empty()?"default-portal-scene":sceneIdentity,
            sceneIdentity.empty()?normalize(object)+":"+std::to_string(portalIndex):std::to_string(portalIndex),normalize(object),ms,open);
        for(const auto &track:cached->second.tracks) {
            const auto resolveImage=[variant=track.imageVariant](const std::string &image) {
                return portalImageVariant(image,variant);
            };
            const auto source=assets_.animation(track.animation);
            animation(track.animation,double(track.state==0?time.commonMs:time.stateMs),x,y,1,portalAnimationLoops(*source),"",-1,1,false,nullptr,resolveImage);
        }
    } catch(const std::exception &error) {
        if(failures_.insert(key).second)errors.push_back({{"portal",object},{"open",open},
            {"pvf_identity",p.identity()},{"error",error.what()}});
    }
}
Json Renderer::portalSourceReport() const {
    Json entries=Json::array();
    for(const auto &[key,plan]:portalPlans_)entries.push_back({{"key",key},{"plan",plan.snapshot()}});
    return {{"entries",entries},{"plans",portalPlans_.size()},{"playback",portalPlayback_.snapshot()},
        {"image_binding","source state/variant/LOOP and per-portal simulation state clock applied to actual ANI poses"}};
}
void Renderer::screenshot(const std::filesystem::path &p) {
    SDL_Rect old;
    float sx, sy;
    SDL_RenderGetViewport(renderer_, &old);
    SDL_RenderGetScale(renderer_, &sx, &sy);
    SDL_RenderSetViewport(renderer_, nullptr);
    SDL_RenderSetScale(renderer_, 1, 1);
    int w, h;
    SDL_GetRendererOutputSize(renderer_, &w, &h);
    Bytes b(size_t(w) * h * 4);
    if (SDL_RenderReadPixels(renderer_, nullptr, SDL_PIXELFORMAT_RGBA32, b.data(), w * 4))
        throw std::runtime_error(SDL_GetError());
    std::filesystem::create_directories(p.parent_path());
    if (!stbi_write_png(p.u8string().c_str(), w, h, 4, b.data(), w * 4))
        throw std::runtime_error("PNG write");
    SDL_RenderSetViewport(renderer_, &old);
    SDL_RenderSetScale(renderer_, sx, sy);
}
static std::string relativePath(const std::string &parent, const std::string &child) {
    return normalize((std::filesystem::path(parent).parent_path() / child).generic_string());
}
void Scene::draw(Renderer &r, int64_t ms, double camera, bool front, double cameraY) {
    for (const auto &command : sceneDrawCommands(*this, front)) {
        if (command.kind == MapDrawCommand::Kind::Tile) {
            const auto &t = tiles.at(command.index);
            // Source TIL is already the 480-line background canvas positioned
            // at MAP bg. PC reference grass matches crop245+bg80=325 exactly;
            // entity foreground projection adds 120, but tiles must not.
            r.tileSprite(std::get<0>(t), std::get<1>(t), std::get<2>(t) - camera,
                     std::get<3>(t) - cameraY - 120);
            continue;
        }
        const auto &layer = layers.at(command.index);
        if (layer.background) {
            if (layer.repeatWidth <= 0) continue;
            const auto origin = backgroundOrigin(layer, camera, cameraY);
            const auto xs = backgroundRepeatOrigins(origin[0], layer.repeatWidth, r.sceneView.width, true);
            const auto ys = backgroundRepeatOrigins(origin[1], layer.repeatHeight, r.sceneView.height, layer.loopY, true);
            for (double x : xs) for (double y : ys)
                r.animation(layer.animation, ms, std::round(x), y);
        } else {
            r.animation(layer.animation, ms, std::round(layer.x - camera), layer.y - cameraY);
        }
    }
}
} // namespace dnf
