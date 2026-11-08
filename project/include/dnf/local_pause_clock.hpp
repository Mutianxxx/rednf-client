#pragma once

#include <algorithm>
#include <cmath>

namespace dnf {

// Actor-local pause clock. 40JP shows that hit stop freezes an object's
// clock while the outer world clock continues. This adapter deliberately uses
// the current 1031 fixed-step contract and keeps source milliseconds separate
// from the persisted remaining-tick view.
class LocalPauseClock {
    int remainingTicks_ = 0;
    bool frozen_ = false;

public:
    static int ticksForMilliseconds(double milliseconds, int ticksPerSecond = 60) noexcept {
        if (!std::isfinite(milliseconds) || milliseconds <= 0 || ticksPerSecond <= 0)
            return 0;
        const auto bounded = std::clamp(milliseconds, 0.0, 500.0);
        return std::max(1, static_cast<int>(std::ceil(bounded * ticksPerSecond / 1000.0)));
    }

    void setCountdown(double milliseconds, int ticksPerSecond = 60) noexcept {
        const auto ticks = ticksForMilliseconds(milliseconds, ticksPerSecond);
        if (ticks <= 0) return;
        remainingTicks_ = std::max(remainingTicks_, ticks);
        frozen_ = true;
    }

    // The tick that consumes the last unit remains paused. This preserves the
    // existing simulation and save/load contract.
    bool advance(bool dead = false) noexcept {
        if (dead) {
            remainingTicks_ = 0;
            frozen_ = false;
            return false;
        }
        const bool wasFrozen = remainingTicks_ > 0;
        if (wasFrozen) --remainingTicks_;
        frozen_ = wasFrozen;
        return wasFrozen;
    }

    void restore(int remainingTicks, bool frozen) noexcept {
        remainingTicks_ = std::max(0, remainingTicks);
        frozen_ = remainingTicks_ > 0 && frozen;
    }

    int remainingTicks() const noexcept { return remainingTicks_; }
    bool frozen() const noexcept { return frozen_; }
};

} // namespace dnf
