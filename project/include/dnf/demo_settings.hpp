#pragma once
#include "resources.hpp"
#include <cmath>
namespace dnf {
// Explicit user-requested demo balance. Never interpreted as MOB/PVF values.
struct DemoBalance {
    int normalHpMultiplier = 2, bossHpMultiplier = 3;
    static DemoBalance fromJson(const Json &value, int normalDefault = 2, int bossDefault = 3) {
        DemoBalance result{normalDefault, bossDefault};
        if (!value.is_object()) return result;
        auto read = [&](const char *key, int fallback) {
            auto found = value.find(key);
            if (found == value.end() || !found->is_number_integer()) return fallback;
            // Validate before narrowing potentially large external JSON integers.
            if (*found < 1 || *found > 10) return fallback;
            return found->get<int>();
        };
        result.normalHpMultiplier = read("normal_hp_multiplier", normalDefault);
        result.bossHpMultiplier = read("boss_hp_multiplier", bossDefault);
        return result;
    }
    int monsterHp(bool boss) const {
        return (boss ? 240 : 65) * std::clamp(boss ? bossHpMultiplier : normalHpMultiplier, 1, 10);
    }
    Json describe() const {
        return {{"normal_hp_multiplier", normalHpMultiplier}, {"boss_hp_multiplier", bossHpMultiplier},
                {"basis", "previous-demo-normal65-boss240"}, {"evidence", "user-requested-demo-tuning"}};
    }
};
struct AudioVolumes {
    double master = 1, music = 1, effects = 1, ambient = 1;
    static AudioVolumes fromJson(const Json &value) {
        AudioVolumes result;
        if (!value.is_object()) return result;
        auto read = [&](const char *key) {
            const auto found = value.find(key);
            if (found == value.end() || !found->is_number()) return 1.0;
            const auto number = found->get<double>();
            return std::isfinite(number) ? std::clamp(number, 0.0, 1.0) : 1.0;
        };
        result.master = read("master"); result.music = read("music");
        result.effects = read("effects"); result.ambient = read("ambient");
        return result;
    }
    Json describe() const {
        return {{"master", master}, {"music", music}, {"effects", effects}, {"ambient", ambient}};
    }
};
} // namespace dnf
