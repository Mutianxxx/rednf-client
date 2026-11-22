#include "dnf/diagnostics/frame_statistics.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {

void require(bool condition, const char *message) {
    if (!condition) throw std::runtime_error(message);
}

template <typename Error, typename Action>
void rejects(Action action, const char *message) {
    try {
        action();
    } catch (const Error &) {
        return;
    }
    throw std::runtime_error(message);
}

void runChecks() {
    using dnf::diagnostics::FrameStatistics;

    rejects<std::invalid_argument>([] { FrameStatistics invalid(0); }, "Zero capacity must be rejected");

    FrameStatistics empty;
    const auto noSamples = empty.snapshot();
    require(noSamples.totalSamples == 0 && noSamples.windowSamples == 0,
            "A new accumulator must have no samples");
    require(noSamples.capacity == FrameStatistics::defaultCapacity,
            "Default capacity must be explicit in the snapshot");
    require(noSamples.lifetimeMaxNanoseconds == 0 && noSamples.windowMedianNanoseconds == 0 &&
                noSamples.windowP95Nanoseconds == 0,
            "Empty statistics must report zero duration");

    FrameStatistics one(1);
    one.record(0);
    const auto zero = one.snapshot();
    require(zero.totalSamples == 1 && zero.windowSamples == 1 && zero.windowMedianNanoseconds == 0 &&
                zero.windowP95Nanoseconds == 0,
            "A zero duration is a real accepted sample");
    one.record(std::numeric_limits<std::int64_t>::max());
    one.record(7);
    const auto wrappedOne = one.snapshot();
    require(wrappedOne.totalSamples == 3 && wrappedOne.windowSamples == 1 &&
                wrappedOne.windowMedianNanoseconds == 7 && wrappedOne.windowP95Nanoseconds == 7,
            "Capacity one must retain exactly the most recent duration");
    require(wrappedOne.lifetimeMaxNanoseconds == std::numeric_limits<std::int64_t>::max(),
            "An evicted peak must remain in the lifetime maximum without arithmetic overflow");

    FrameStatistics ranks(100);
    for (std::int64_t value = 99; value >= 0; --value) ranks.record(value);
    const auto ranked = ranks.snapshot();
    require(ranked.windowMedianNanoseconds == 50 && ranked.windowP95Nanoseconds == 95,
            "Median and P95 must preserve the existing upper-rank policy");
    require(ranks.snapshot().windowP95Nanoseconds == ranked.windowP95Nanoseconds,
            "Taking a snapshot must not modify running statistics");

    FrameStatistics even(4);
    for (const auto value : {40, 10, 30, 20}) even.record(value);
    require(even.snapshot().windowMedianNanoseconds == 30,
            "Even-sized median must select the upper middle sample");

    FrameStatistics wrapped(4);
    for (const auto value : {1000, 1, 2, 3, 4, 5}) wrapped.record(value);
    const auto recent = wrapped.snapshot();
    require(recent.totalSamples == 6 && recent.windowSamples == 4 && recent.capacity == 4,
            "Ring wrap must retain bounded storage and lifetime count");
    require(recent.windowMedianNanoseconds == 4 && recent.windowP95Nanoseconds == 5 &&
                recent.lifetimeMaxNanoseconds == 1000,
            "Window quantiles and lifetime maximum must have separate scopes");
    rejects<std::invalid_argument>([&] { wrapped.record(-1); }, "Negative frame duration must be rejected");
    const auto afterRejected = wrapped.snapshot();
    require(afterRejected.totalSamples == recent.totalSamples &&
                afterRejected.windowMedianNanoseconds == recent.windowMedianNanoseconds &&
                afterRejected.windowP95Nanoseconds == recent.windowP95Nanoseconds &&
                afterRejected.lifetimeMaxNanoseconds == recent.lifetimeMaxNanoseconds,
            "Rejected samples must not mutate any statistics");

    FrameStatistics longRun(31);
    longRun.record(9000000);
    for (std::int64_t value = 0; value < 100000; ++value) longRun.record(value);
    const auto finalWindow = longRun.snapshot();
    require(finalWindow.totalSamples == 100001 && finalWindow.windowSamples == 31 &&
                finalWindow.capacity == 31,
            "Long streams must not increase sample storage beyond configured capacity");
    require(finalWindow.windowMedianNanoseconds == 99984 && finalWindow.windowP95Nanoseconds == 99998 &&
                finalWindow.lifetimeMaxNanoseconds == 9000000,
            "Long streams must preserve the exact newest window and full-run maximum");

    longRun.reset();
    const auto cleared = longRun.snapshot();
    require(cleared.totalSamples == 0 && cleared.windowSamples == 0 && cleared.capacity == 31 &&
                cleared.lifetimeMaxNanoseconds == 0 && cleared.windowP95Nanoseconds == 0,
            "Reset must retain capacity and clear both lifetime and window statistics");
    longRun.record(12);
    require(longRun.snapshot().windowMedianNanoseconds == 12,
            "Recording after reset must not include stale ring contents");
}

} // namespace

int main() {
    try {
        runChecks();
        std::cout << "FrameStatistics checks passed\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
