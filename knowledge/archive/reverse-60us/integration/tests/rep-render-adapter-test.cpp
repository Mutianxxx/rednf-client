#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "pvf_animation.hpp"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>

namespace {
using dnf::ani_render::Pose;
using dnf::ani_render::RenderProfile;
constexpr auto inferred = RenderProfile::Inferred60Us1031;
constexpr auto legacy = RenderProfile::Legacy1031;
struct Check { std::string name; bool passed; };
struct Source {
    std::wstring path;
    std::string hash, fixture;
    size_t frames = 0, interpolating = 0;
    double duration = 0;
    bool loop = false;
};
struct Report {
    std::vector<Check> checks;
    std::vector<Source> sources;
    std::string error, archiveHash;
    size_t candidates = 0;
    void check(bool passed, const std::string &name) { checks.push_back({name, passed}); }
    bool passed() const {
        return error.empty() && sources.size() >= 8 &&
            std::all_of(checks.begin(), checks.end(), [](const auto &c) { return c.passed; });
    }
};
bool same(const Pose &a, const Pose &b) {
    return a.position == b.position && a.rate == b.rate && a.angle == b.angle && a.rgba == b.rgba;
}
Pose values(const pvf::AniFrame &frame) {
    Pose pose;
    pose.position = {double(frame.x), double(frame.y)};
    pose.rate = {double(frame.scale[0]), double(frame.scale[1])};
    pose.angle = frame.rotationRadians;
    for (size_t i = 0; i < 4; ++i) pose.rgba[i] = frame.rgba[i];
    return pose;
}
pvf::Animation fixture() {
    pvf::Animation animation;
    animation.path = L"synthetic/captured-60US-local-pose-not-1031-native.ani";
    animation.durationMs = 1000;
    animation.frames.resize(2);
    auto &a = animation.frames[0], &b = animation.frames[1];
    a.x = -7; a.y = -65; a.scale = {0.2f, 0.05f}; a.rgba = {255, 255, 255, 0};
    b.x = 16; b.y = -6; b.scale = {0.6f, 0.6f}; b.rotationRadians = 6.28f;
    b.rgba = {60, 0, 255, 255};
    a.delayMs = b.delayMs = 500;
    a.interpolate = b.interpolate = true;
    a.imageId = 0; a.imageFrame = 12; a.effect = 0; a.event = 3;
    b.imageId = 1; b.imageFrame = 51; b.effect = 2; b.event = 7;
    a.boxes.push_back({0, {-9, -10, 0, 20, 30, 40}, 0, {1, 2, 3}});
    b.boxes.push_back({1, {5, 6, 1, 21, 31, 41}, 0, {4, 5, 6}});
    a.raw = {7, 8, 9}; b.raw = {10, 11, 12};
    animation.raw = {1, 2, 3, 4};
    return animation;
}
void syntheticCases(Report &report) {
    auto animation = fixture();
    const auto before = animation;
    // Fixed outputs copied from frozen native-vectors.json middle and negative
    // coordinate cases. This is adapter mapping, not 1031 native evidence.
    Pose middle;
    middle.position = {4, -35};
    middle.rate = {0.4000000059604645, 0.32500001788139343};
    middle.angle = 3.140000104904175;
    middle.rgba = {157, 127, 255, 127};
    auto sample = animation.samplePose(250, false, inferred);
    report.check(sample.frame == 0 && sample.nextFrame == 1 && sample.interpolated &&
        same(sample.values, middle), "synthetic/captured-native-middle-through-rep-adapter");
    sample = animation.samplePose(250, false, legacy);
    report.check(sample.frame == 0 && !sample.interpolated &&
        same(sample.values, values(animation.frames[0])), "synthetic/legacy-remains-discrete");
    sample = animation.samplePose(250, false, inferred, false);
    report.check(!sample.interpolated && same(sample.values, values(animation.frames[0])),
        "synthetic/caller-disables-interpolation");
    animation.frames[0].interpolate = false;
    sample = animation.samplePose(250, false, inferred);
    report.check(!sample.interpolated && same(sample.values, values(animation.frames[0])),
        "synthetic/source-switch-disables-interpolation");
    animation.frames[0].interpolate = true;
    sample = animation.samplePose(250, false, inferred, true, 0);
    report.check(!sample.interpolated && sample.frame == 0 &&
        same(sample.values, values(animation.frames[0])), "synthetic/frozen-frame-reference");
    sample = animation.samplePose(250, false, inferred, true, 999);
    report.check(!sample.interpolated && sample.frame == 1 &&
        same(sample.values, values(animation.frames[1])), "synthetic/frozen-frame-override-clamped");
    for (const double time : {500.0, 750.0, 1000.0, 1500.0}) {
        sample = animation.samplePose(time, false, inferred);
        report.check(sample.frame == 1 && sample.nextFrame == 1 && !sample.interpolated &&
            same(sample.values, values(animation.frames[1])),
            "synthetic/nonloop-tail-or-ended-" + std::to_string(int(time)));
    }
    sample = animation.samplePose(750, true, inferred);
    report.check(sample.frame == 1 && sample.nextFrame == 0 && sample.interpolated &&
        same(sample.values, middle), "synthetic/loop-last-to-first");
    sample = animation.samplePose(1000, true, inferred);
    report.check(sample.frame == 0 && sample.nextFrame == 1 && sample.interpolated &&
        same(sample.values, values(animation.frames[0])), "synthetic/loop-exact-duration-wraps");
    for (double time : {-1.0, std::numeric_limits<double>::quiet_NaN(),
            std::numeric_limits<double>::infinity()}) {
        sample = animation.samplePose(time, false, inferred);
        report.check(sample.frame == 0 && same(sample.values, values(animation.frames[0])),
            "adapter/invalid-playback-time-normalizes-to-zero");
    }
    report.check(animation.raw == before.raw && animation.frames[0].raw == before.frames[0].raw &&
        animation.frames[0].imageFrame == 12 && animation.frames[1].imageFrame == 51 &&
        animation.frames[0].effect == 0 && animation.frames[1].effect == 2 &&
        animation.frames[0].event == 3 && animation.frames[1].event == 7 &&
        animation.frames[0].boxes[0].values == before.frames[0].boxes[0].values &&
        animation.frames[1].boxes[0].raw == before.frames[1].boxes[0].raw,
        "synthetic/discrete-image-effect-event-box-and-raw-preserved");
    auto &a = animation.frames[0], &b = animation.frames[1];
    a.x = -3; a.y = -2; a.scale = {-2, 1}; a.rotationRadians = -6.28f;
    a.rgba = {1, 2, 3, 255};
    b.x = 0; b.y = 1; b.scale = {2, -1}; b.rotationRadians = 6.28f;
    b.rgba = {254, 253, 252, 0};
    a.delayMs = b.delayMs = 4;
    animation.durationMs = 8;
    Pose negative;
    negative.position = {-2, -1}; negative.rate = {-1, 0.5};
    negative.angle = -3.140000104904175; negative.rgba = {64, 64, 65, 191};
    sample = animation.samplePose(1, false, inferred);
    report.check(sample.interpolated && same(sample.values, negative),
        "synthetic/negative-position-whole-result-truncation-and-full-turn");
    sample = animation.samplePose(1.9, false, inferred);
    report.check(same(sample.values, negative), "synthetic/fractional-clock-integral-policy");
    a.delayMs = 0; animation.durationMs = 4;
    sample = animation.samplePose(0, false, inferred);
    report.check(sample.frame == 1 && !sample.interpolated,
        "synthetic/zero-delay-frame-has-no-positive-interval");
    pvf::Animation empty;
    sample = empty.samplePose(1, true, inferred);
    report.check(sample.frame == 0 && sample.nextFrame == 0 && !sample.interpolated &&
        same(sample.values, Pose{}), "synthetic/empty-animation");
}
void realSourceCases(const std::filesystem::path &archivePath,
        const std::filesystem::path &output, Report &report) {
    pvf::Archive archive(archivePath);
    report.archiveHash = archive.sha256();
    if (report.archiveHash != "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d")
        throw pvf::Error("Expected current 1031 archive identity");
    std::vector<size_t> candidates;
    for (size_t index = 0; index < archive.entries().size(); ++index) {
        const auto path = pvf::normalizePath(archive.entries()[index].path);
        if (path.starts_with(L"character/swordman/animation/") && path.ends_with(L".ani"))
            candidates.push_back(index);
    }
    std::sort(candidates.begin(), candidates.end(), [&](size_t a, size_t b) {
        return archive.entries()[a].path < archive.entries()[b].path;
    });
    // A focused source-adapter sample, not a whole-PVF completeness audit.
    // Keep four representative base frames and up to eight source animations
    // with enabled interpolation. Selection is deterministic by source path.
    size_t plain = 0, enabled = 0;
    std::filesystem::create_directory(output / L"rep-source-ani");
    for (const auto index : candidates) {
        ++report.candidates;
        const auto &entry = archive.entries()[index];
        auto animation = pvf::decodeAnimation(archive.read(index), entry.path);
        const size_t enabledCount = std::count_if(animation.frames.begin(), animation.frames.end(),
            [](const auto &frame) { return frame.interpolate && frame.delayMs > 0; });
        if (animation.frames.empty()) continue;
        if (enabledCount && animation.frames.size() > 1) {
            if (enabled == 8) continue;
            ++enabled;
        } else {
            if (plain == 4) continue;
            ++plain;
        }
        Source source{entry.path, animation.hash,
            "rep-source-ani/" + std::to_string(report.sources.size()) + ".ani",
            animation.frames.size(), enabledCount, animation.durationMs, animation.loop};
        const auto sourceRaw = animation.raw;
        std::ofstream saved(output / source.fixture, std::ios::binary);
        saved.write(reinterpret_cast<const char *>(sourceRaw.data()), std::streamsize(sourceRaw.size()));
        if (!saved) throw pvf::Error("Cannot preserve decrypted ANI source fixture");
        const auto id = "1031/" + pvf::toUtf8(entry.path);
        report.check(pvf::sha256(sourceRaw) == animation.hash, id + "/raw-hash-identity");
        double start = 0;
        for (size_t frameIndex = 0; frameIndex < animation.frames.size(); ++frameIndex) {
            const auto &frame = animation.frames[frameIndex];
            if (frame.delayMs <= 0) continue;
            const auto time = start + frame.delayMs / 2.0;
            const auto label = id + "/frame-" + std::to_string(frameIndex);
            const auto discrete = values(frame);
            const auto old = animation.samplePose(time, false, legacy);
            report.check(old.frame == frameIndex && !old.interpolated && same(old.values, discrete),
                label + "/legacy-discrete");
            const auto disabled = animation.samplePose(time, false, inferred, false);
            report.check(disabled.frame == frameIndex && !disabled.interpolated &&
                same(disabled.values, discrete), label + "/feature-off-source-values");
            const auto frozen = animation.samplePose(time, true, inferred, true, int(frameIndex));
            report.check(frozen.frame == frameIndex && !frozen.interpolated &&
                same(frozen.values, discrete), label + "/frozen-source-values");
            const auto sample = animation.samplePose(time, false, inferred);
            const bool shouldInterpolate = frame.interpolate && frameIndex + 1 < animation.frames.size();
            report.check(sample.frame == frameIndex && sample.interpolated == shouldInterpolate &&
                sample.nextFrame == std::min(frameIndex + 1, animation.frames.size() - 1),
                label + "/source-delay-and-interpolation-flag");
            // Check the adapter against the independently verified portable
            // contract, using source clock and frame selection as the inputs.
            dnf::ani_render::SampleContext context;
            context.elapsed = frame.delayMs / 2.0;
            context.span = frame.delayMs;
            context.requested = frame.interpolate;
            context.hasNext = frameIndex + 1 < animation.frames.size();
            const auto expected = dnf::ani_render::samplePose(discrete,
                values(animation.frames[std::min(frameIndex + 1, animation.frames.size() - 1)]),
                context, inferred);
            report.check(same(sample.values, expected.pose), label + "/portable-contract-wiring");
            start += frame.delayMs;
        }
        const auto last = animation.samplePose(animation.durationMs + 1, false, inferred);
        report.check(last.frame == animation.frames.size() - 1 && !last.interpolated &&
            same(last.values, values(animation.frames.back())), id + "/nonloop-ended-tail");
        const auto wrapped = animation.samplePose(animation.durationMs, true, inferred);
        const auto initial = animation.samplePose(0, true, inferred);
        report.check(wrapped.frame == initial.frame && same(wrapped.values, initial.values),
            id + "/exact-duration-wrap");
        report.check(animation.raw == sourceRaw && pvf::sha256(animation.raw) == source.hash,
            id + "/all-queries-preserve-source-bytes");
        report.sources.push_back(std::move(source));
        if (plain == 4 && enabled == 8) break;
    }
    report.check(plain >= 4 && enabled >= 4, "1031/at-least-four-plain-and-four-interpolation-sources");
}
void writeReport(const std::filesystem::path &path, const Report &report) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw pvf::Error("Cannot write REP adapter report");
    out << std::setprecision(17) << "{\n\"schema\":\"dnf-rep-render-adapter-v1\","
        << "\n\"passed\":" << (report.passed() ? "true" : "false")
        << ",\n\"checks\":" << report.checks.size() << ",\n\"archive_sha256\":\""
        << report.archiveHash << "\",\n\"source_animations_checked\":" << report.sources.size()
        << ",\n\"source_candidates_decoded\":" << report.candidates
        << ",\n\"scope\":\"REP source-to-portable pose adapter; 60US local pose reused in 1031 as inference\","
        << "\n\"limitations\":[\"Source samples limited to swordman animation subtree\","
        << "\"Synthetic 60US values are not 1031 native execution evidence\","
        << "\"No original game clock or GPU pixel equivalence\"],"
        << "\n\"error\":\"" << pvf::jsonEscape(report.error) << "\",\n\"sources\":[";
    for (size_t i = 0; i < report.sources.size(); ++i) {
        const auto &s = report.sources[i];
        if (i) out << ',';
        out << "\n{\"path\":\"" << pvf::jsonEscape(s.path) << "\",\"sha256\":\"" << pvf::jsonEscape(s.hash)
            << "\",\"fixture\":\"" << pvf::jsonEscape(s.fixture) << "\",\"frames\":" << s.frames
            << ",\"interpolation_frames\":" << s.interpolating << ",\"duration_ms\":" << s.duration
            << ",\"source_loop\":" << (s.loop ? "true" : "false") << '}';
    }
    out << "\n],\n\"results\":[";
    for (size_t i = 0; i < report.checks.size(); ++i) {
        if (i) out << ',';
        out << "\n{\"name\":\"" << pvf::jsonEscape(report.checks[i].name) << "\",\"passed\":"
            << (report.checks[i].passed ? "true" : "false") << '}';
    }
    out << "\n]\n}\n";
    if (!out) throw pvf::Error("Incomplete REP adapter report write");
}
} // namespace
int wmain(int argc, wchar_t **argv) {
    if (argc != 3) {
        std::cerr << "Usage: rep-render-adapter-test Script.pvf OUTPUT_DIRECTORY\n";
        return 2;
    }
    const auto output = std::filesystem::absolute(argv[2]).lexically_normal();
    if (output.root_name() != L"D:" && output.root_name() != L"d:") {
        std::cerr << "REP adapter artifacts must stay on D:\n";
        return 2;
    }
    Report report;
    try {
        syntheticCases(report);
        realSourceCases(argv[1], output, report);
    } catch (const std::exception &error) {
        report.error = error.what();
    }
    try {
        writeReport(output / L"rep-adapter-report.json", report);
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
    for (const auto &check : report.checks)
        if (!check.passed) std::cerr << "FAIL " << check.name << '\n';
    if (!report.error.empty()) std::cerr << report.error << '\n';
    std::cout << report.sources.size() << " real 1031 source animations; "
        << report.checks.size() << " checks; " << (report.passed() ? "PASS" : "FAIL") << '\n';
    return report.passed() ? 0 : 1;
}
