#pragma once
#include "resources.hpp"

namespace dnf {
struct Scene;
struct SceneTileLoadResult {
    bool complete=true, columnsResolved=true;
    Json records=Json::array(), diagnostics=Json::array();
};
// Shared by normal Scene::load and source-map preparation. Source pass values,
// repeated IMAGE fields, dimensions and all inferred placements remain in the
// receipt. Empty imagery is transparent, never a missing-asset replacement.
SceneTileLoadResult loadSceneSourceTiles(Pvf &,Assets &,Scene &);
} // namespace dnf
