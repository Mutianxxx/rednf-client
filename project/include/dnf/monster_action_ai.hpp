#pragma once
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"
#include <functional>
#include <map>
#include <memory>
#include <optional>

namespace dnf {
struct MonsterActionAiNode {
    enum class Kind { Return, Area, Cooldown, Chance };
    Kind kind = Kind::Return;
    int value = -1;
    std::array<double,4> area{};
    uint32_t numerator = 0, denominator = 1;
    SourceRef source;
    std::vector<size_t> yes, no;
};
struct MonsterActionAiProgram {
    Script original;
    SourceRef source;
    std::vector<MonsterActionAiNode> nodes;
    std::vector<size_t> sequence;
    Json retainedFields = Json::array();
};
struct MonsterActionAiCompilation {
    std::shared_ptr<const MonsterActionAiProgram> program;
    Json diagnostics = Json::array();
    bool ok() const { return bool(program); }
    Json json() const;
};
struct MonsterActionAiContext {
    EntityHandle owner, target;
    std::array<double,3> ownerPosition{}, targetPosition{};
    int direction = 1;
    std::function<std::optional<bool>(int)> cooldown;
};
struct MonsterActionAiEvaluation {
    bool ok = false;
    std::optional<int> returned;
    std::optional<Pcg32> candidateRandom;
    Json trace = Json::array(), diagnostics = Json::array();
    Json json() const;
};
MonsterActionAiCompilation compileMonsterActionAi(const Pvf &,const Script &);
MonsterActionAiEvaluation evaluateMonsterActionAi(const MonsterActionAiProgram &,
    const MonsterActionAiContext &,const Pcg32 &);
// A difficulty selects the complete explicit MOB row, with fixed Event,
// DestinationSelect, Action and MoveMethod source slots. No filename fallback.
struct MonsterActionAiRoutes {
    bool configured = false, ok = false;
    std::string difficulty;
    std::array<std::string,4> paths{};
    Json source = Json::object(), diagnostics = Json::array();
    Json json() const;
};
MonsterActionAiRoutes selectMonsterActionAiRoutes(const Pvf &,const Script &,const std::string &);
Json monsterActionAiPolicy();
// Cross-version movement adapter. Source values and the conversion policy are
// retained separately; an unsupported destination/method never grants motion.
struct MonsterSourceMovement {
    int destination = -1, method = -1;
    double speed = 0, keepDistance = 0;
    double keepY = 0, radiusX = 0, radiusY = 0, offsetX = 0, offsetY = 0;
    int sideX = -1, sideY = -1;
    int fixedDirection = 0;
    Json evidence = Json::object();
    bool ready = false;
};
struct MonsterMovementStep {
    double dx = 0, dy = 0;
    int direction = 1;
    bool moving = false;
};
MonsterSourceMovement readMonsterSourceMovement(const Pvf &,const Script &,int level,
    int destination,int method);
// 40JP 0x4DF2D0: independent destination axes, stop each axis at the
// destination instead of crossing it. The map remains the movement authority.
MonsterMovementStep planMonsterMovement(const MonsterSourceMovement &,
    const std::array<double,2> &owner,const std::array<double,2> &target,
    int facing,int64_t deltaMs,int targetFacing = 1);
struct MonsterActionAiBinding {
    int sourceId = 0, actorId = 0;
    std::string monster;
    MonsterActionAiRoutes routes;
    std::array<std::shared_ptr<const MonsterActionAiProgram>,3> programs;
    std::string stayAction, moveAction;
    int64_t thinkMs = 500;
    bool ready = false;
};
struct MonsterActionAiRestore {
    bool enabled = false;
    std::string difficulty;
    MonotonicIds instances;
};
} // namespace dnf
