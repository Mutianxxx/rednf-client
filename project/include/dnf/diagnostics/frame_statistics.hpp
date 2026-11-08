#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace dnf::diagnostics {

// Nanosecond samples are descriptive diagnostics, never a simulation clock.
// The count and maximum cover the object's full lifetime. Percentiles cover
// only the most recent windowSamples samples; callers must report that scope.
struct FrameStatisticsSnapshot {
    std::uint64_t totalSamples = 0;
    std::size_t windowSamples = 0;
    std::size_t capacity = 0;
    std::int64_t lifetimeMaxNanoseconds = 0;
    std::int64_t windowMedianNanoseconds = 0;
    std::int64_t windowP95Nanoseconds = 0;
};

// Single-owner diagnostic accumulator. Storage is allocated once at creation;
// record() neither allocates nor sorts. snapshot() sorts a temporary copy when
// a report is requested, leaving the running ring and subsequent samples intact.
class FrameStatistics {
  public:
    static constexpr std::size_t defaultCapacity = 4096;

    explicit FrameStatistics(std::size_t capacity = defaultCapacity);

    // Zero-duration frames are valid. Negative durations throw invalid_argument
    // without changing state. A saturated total count throws overflow_error.
    void record(std::int64_t nanoseconds);
    FrameStatisticsSnapshot snapshot() const;
    void reset() noexcept;

  private:
    std::vector<std::int64_t> ring_;
    std::size_t next_ = 0;
    std::size_t size_ = 0;
    std::uint64_t count_ = 0;
    std::int64_t maximum_ = 0;
};

} // namespace dnf::diagnostics
