#include "dnf/animation_events.hpp"
#include <stdexcept>
namespace dnf {
void AnimationEventCursor::update(const Animation &animation, int frame, bool suppressed) {
    if (suppressed || frame == lastFrame_) return;
    if (frame < 0 || size_t(frame) >= animation.frames.size())
        throw std::runtime_error("ANI event frame outside source: " + animation.path);
    auto assign = [&](int index) {
        const auto &properties = animation.frames[size_t(index)].properties;
        if (!properties.contains("23")) return;
        const auto &value = properties.at("23");
        if (!value.is_number_integer()) throw std::runtime_error("Noninteger ANI event: " + animation.path);
        const auto event = uint16_t(value.get<int32_t>());
        if (event != 0xffff) pending_ = event;
    };
    // 108F370 walks skipped forward frames in source order, then assigns the
    // current frame. Empty/sentinel frames leave the single pending flag intact.
    for (int index = lastFrame_ + 1; index < frame; ++index) assign(index);
    lastFrame_ = frame;
    assign(frame);
}
} // namespace dnf
