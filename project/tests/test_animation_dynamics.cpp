#include "dnf/resources.hpp"
#include "dnf/geometry.hpp"
#include "dnf/target_hud.hpp"
#include <stdexcept>

namespace dnf {
Json runAnimationDynamicsTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool value, const char *name) {
        if (!value) throw std::runtime_error(std::string("Animation dynamics: ") + name);
        checks.push_back(name);
    };
    auto near = [](double a, double b) { return std::abs(a - b) < 0.002; };
    auto light = assets.animation("passiveobject/mapobject/pathgate/act1/animation/granflorisrightlight.ani");
    require(light->frames.size() == 2 && light->duration == 1000, "source gate two-key period");
    for (auto [time, expected] : {std::pair<double, double>{0, 0}, {125, 63.75},
                                 {250, 127.5}, {500, 255}, {750, 127.5}, {1000, 0}})
        require(near(light->samplePose(time, true).rgba[3], expected), "source gate smooth alpha and loop seam");
    require(near(light->samplePose(750, false).rgba[3], 255), "nonloop final frame holds");
    require(near(light->samplePose(-10, true).rgba[3], 0), "negative time clamps to beginning");
    require(near(light->samplePose(250, true, 1).rgba[3], 255), "explicit frame bypasses tween");
    const auto inferred=ani_render::RenderProfile::Inferred60Us1031;
    require(light->samplePose(250,true,-1,inferred).rgba[3]==127,
            "R60 source gate uses native truncation in explicit inferred profile");
    require(light->samplePose(750,false,-1,inferred).rgba[3]==255 &&
            !light->samplePose(1000,false,-1,inferred).interpolated,
            "R60 nonloop final frame and ended hold without interpolation");
    require(light->samplePose(750,true,-1,inferred).rgba[3]==127,
            "R60 loop last frame interpolates to frame zero");
    require(light->samplePose(250,true,1,inferred).rgba[3]==255 &&
            !light->samplePose(250,true,1,inferred).interpolated,
            "R60 frozen frame bypasses interpolation");
    Animation synthetic;
    synthetic.duration = 200;
    synthetic.globals = {{"7", {2, 3}}, {"9", {200, 180, 160, 240}}};
    AniFrame first, second;
    first.duration = second.duration = 100;
    first.image = "first.img"; first.imageFrame = 7;
    first.properties = {{"10", true}, {"9", {0, 0, 0, 0}}, {"7", {-1, 1}}, {"8", 0.0}};
    second.image = "second.img"; second.imageFrame = 9;
    second.x = 20; second.y = 40;
    second.properties = {{"8", 6.28}, {"11", {{"effect", 2}}}};
    synthetic.frames = {first, second};
    auto half = synthetic.samplePose(50, true), end = synthetic.samplePose(100, true);
    require(near(half.rgba[3], 120) && near(end.rgba[3], 240), "omitted frame RGBA resets to global");
    require(near(half.scaleX, 0.5) && near(half.scaleY, 2), "signed scale interpolation");
    require(near(half.x, 10) && near(half.y, 20), "ANI local offset interpolation");
    require(near(half.rotationRadians, 3.14), "authored radians interpolate without shortest-arc loss");
    require(half.image == "first.img" && half.imageFrame == 7 && half.blend == 0,
            "image frame and blend remain discrete");
    require(!end.interpolated && near(end.rotationRadians, 6.28), "noninterpolation frame stays discrete");
    auto nativeHalf=synthetic.samplePose(50,true,-1,inferred);
    require(nativeHalf.rotationRadians==double(float(double(float(6.28))*.5)) &&
            nativeHalf.image=="first.img" && nativeHalf.imageFrame==7 && nativeHalf.blend==0,
            "R60 authored whole revolution is float32 while image and blend stay discrete");
    synthetic.frames[0].x=-3;synthetic.frames[1].x=0;
    require(synthetic.samplePose(25,false,-1,inferred).x==-2 && synthetic.samplePose(25,false).x==-2.25,
            "R60 negative full-result truncation differs from preserved legacy profile");
    synthetic.frames[0].x=0;synthetic.frames[1].x=20;
    ani_render::QuadInput input;input.pose.position={-10,-20};input.pose.rate={2,1};
    input.pose.angle=3.14159265358979323846/2;input.cropX=2;input.cropY=3;input.width=4;input.height=6;
    const auto nativeQuad=ani_render::makeQuad(input,inferred);
    require(near(nativeQuad.vertices[0].x,-34)&&near(nativeQuad.vertices[0].y,8),
            "R60 negative radians and output-axis scaling include IMAGE POS and crop");
    auto quad = imageQuad(0, 0, 0, 0, 0, 0, 10, 20, 1, 1, 1,
                          radiansToDegrees(3.14159265358979323846 / 2));
    require(near(quad[1].x, 0) && near(quad[1].y, 10), "source radians convert once at degree backend boundary");
    auto flash = assets.animation("monster/common/animation/monsterdieflash.ani")->samplePose(50, false);
    require(near(flash.scaleX, 1.25) && near(flash.rgba[3], 127.5), "source death flash scale and alpha tween");
    auto piece = assets.animation("monster/common/animation/monsterdiepiece.ani");
    require(piece->samplePose(200, false).image.empty() &&
            near(piece->samplePose(200, false).rotationRadians, 2),
            "source image-free piece motion remains sampleable");
    synthetic.frames[0].properties["27"] = {0, 0, 1, 1};
    require(!synthetic.samplePose(0, false).unsupported.empty(), "unconsumed source controls reported");
    TargetHealthState health;
    health.hit(1, 40, 100, 100, 1000);
    require(near(health.ratio(), .4) && near(health.trail(1100), 1), "target immediate HP and dark trail hold");
    require(health.trail(1300) < 1 && health.trail(1300) > .4 && near(health.trail(1600), .4),
            "target dark trail converges on real HP");
    health.hit(1, 0, 100, 40, 1700);
    require(health.opacity(1800) == 1 && health.opacity(2400) == 0,
            "lethal target holds then disappears");
    health.hit(2, 75, 100, 100, 2500);
    require(health.target == 2 && near(health.trail(2500), 1), "target change resets prior trail");
    health.reset();
    require(health.opacity(2500) == 0, "scene change clears target health");
    require(pvf.script("monster/goblin/goblin.mob").values("[die effect]") == Json::array({0, 1, 0}),
            "source goblin death selector preserved");
    return {{"status", "pass"}, {"checks", checks},
            {"scope", "portable sampling and target display state; no SDL/PC visual parity claim"}};
}
} // namespace dnf
