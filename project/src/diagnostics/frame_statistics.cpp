#include "dnf/diagnostics/frame_statistics.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace dnf::diagnostics {

FrameStatistics::FrameStatistics(std::size_t capacity) : ring_(capacity) {
    if (capacity == 0) throw std::invalid_argument("Frame statistics capacity must be positive");
}

void FrameStatistics::record(std::int64_t nanoseconds) {
    if (nanoseconds < 0) throw std::invalid_argument("Frame duration cannot be negative");
    if (count_ == std::numeric_limits<std::uint64_t>::max())
        throw std::overflow_error("Frame statistics sample count exhausted");

    ring_[next_] = nanoseconds;
    if (++next_ == ring_.size()) next_ = 0;
    if (size_ < ring_.size()) ++size_;
    ++count_;
    maximum_ = std::max(maximum_, nanoseconds);
}

FrameStatisticsSnapshot FrameStatistics::snapshot() const {
    FrameStatisticsSnapshot result;
    result.totalSamples = count_;
    result.windowSamples = size_;
    result.capacity = ring_.size();
    result.lifetimeMaxNanoseconds = maximum_;
    if (size_ == 0) return result;

    // Before the ring fills, valid elements are a prefix. Once full, ordering
    // does not matter for quantiles, so no ring rotation or extra copy is needed.
    std::vector<std::int64_t> ordered(ring_.begin(), ring_.begin() + size_);
    std::sort(ordered.begin(), ordered.end());
    result.windowMedianNanoseconds = ordered[size_ / 2];
    // floor(0.95 * size_) == size_ - ceil(size_ / 20). Integer arithmetic
    // preserves the previous rank policy without a floating conversion or an
    // overflowing multiplication for large capacities.
    const auto p95Index = size_ - size_ / 20 - (size_ % 20 != 0 ? 1 : 0);
    result.windowP95Nanoseconds = ordered[p95Index];
    return result;
}

void FrameStatistics::reset() noexcept {
    next_ = 0;
    size_ = 0;
    count_ = 0;
    maximum_ = 0;
}

} // namespace dnf::diagnostics
