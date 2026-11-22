#pragma once
#include "dnf/resources.hpp"

namespace dnf {
// Inferred visible pixel anchor, never a recovered native socket. Keep the
// renderer's crop, authored IMAGEPOS, flip and transform profile in one order.
inline ani_render::Point inferredGunnerPixelPoint(const AniPose &pose, int cropX, int cropY,
    double pixelX, double pixelY, ani_render::RenderProfile profile, int direction = 1) {
    ani_render::QuadInput input;
    input.pose.position={pose.x,pose.y};
    input.pose.rate={pose.scaleX*((pose.flip&1)?-1:1),pose.scaleY*((pose.flip&2)?-1:1)};
    input.pose.angle=pose.rotationRadians;input.cropX=cropX+pixelX;input.cropY=cropY+pixelY;input.direction=direction;
    return ani_render::makeQuad(input,profile).vertices[0];
}
}
