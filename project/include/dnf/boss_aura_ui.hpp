#pragma once
#include "renderer.hpp"
namespace dnf {
// The ANI/IMG/timing/transform are current-source facts. Applying this general
// resource to all living Boss actors is an explicitly inferred display policy;
// a native general caller has not been recovered from the current PVF.
void drawSourceBossAura(Renderer &,const Actor &,int64_t ms,double interpolation,
                        double cameraX,double cameraY);
}
