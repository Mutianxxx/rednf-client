#include "dnf_ani_clock.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

namespace {
using namespace dnf::ani_clock;
constexpr auto inferred = ClockPolicy::Inferred60UsPercentDeadlines;
struct Check { std::string name; bool passed; };
struct NativeResult {
    std::string name;
    int precision = 0, expectedDelta = 0, expectedDeadline = 0, actualDelta = 0, actualDeadline = 0;
    float expectedRate = 0, actualRate = 0;
    bool passed = false;
};
struct Report {
    std::vector<Check> checks;
    std::vector<NativeResult> native;
    std::string error;
    void check(bool pass, const std::string &name) { checks.push_back({name, pass}); }
    bool passed() const {
        return error.empty() && native.size() == 46 &&
            std::all_of(checks.begin(), checks.end(), [](const Check &v) { return v.passed; });
    }
};
uint32_t bits(float value) {
    uint32_t result;
    static_assert(sizeof(value) == sizeof(result) && std::numeric_limits<float>::is_iec559, "IEEE binary32 required");
    std::memcpy(&result, &value, sizeof(result));
    return result;
}
template <class Function> bool rejects(Function function) {
    try { function(); } catch (const std::exception &) { return true; }
    return false;
}
bool same(const Snapshot &a, const Snapshot &b) {
    return a.policy == b.policy && a.frame == b.frame && a.nextFrame == b.nextFrame &&
        a.lastTick == b.lastTick && a.elapsedMs == b.elapsedMs && a.frameStartMs == b.frameStartMs &&
        a.nextDeadlineMs == b.nextDeadlineMs && a.localMs == b.localMs && a.spanMs == b.spanMs &&
        a.visit == b.visit && a.loopCount == b.loopCount && a.rateRevision == b.rateRevision &&
        bits(a.ratePercent) == bits(b.ratePercent) && a.ended == b.ended && a.loop == b.loop && a.paused == b.paused;
}
TickInput tick(uint64_t index, bool paused = false) {
    return {index, uint32_t(millisecondsAtTick(index) - millisecondsAtTick(index - 1)), paused};
}
void nativeVectors(const std::string &path, Report &report) {
    std::ifstream in(path);
    std::string magic, extra;
    size_t count = 0;
    if (!(in >> magic >> count) || magic != "DNF_ANI_CLOCK_NATIVE_V1" || count != 46)
        throw std::runtime_error("Invalid captured clock fixture header");
    std::set<std::pair<int, std::string>> seen;
    for (size_t i = 0; i < count; ++i) {
        NativeResult row;
        double rateInput = 0, expectedRate = 0;
        int delay = 0, ratePath = 0;
        if (!(in >> row.name >> row.precision >> rateInput >> ratePath >> delay >> expectedRate >>
                row.expectedDelta >> row.expectedDeadline) || (row.precision != 53 && row.precision != 64) ||
                !seen.emplace(row.precision, row.name).second || ratePath < 0 || ratePath > 2)
            throw std::runtime_error("Invalid/duplicate captured clock fixture row");
        row.expectedRate = float(expectedRate);
        row.actualRate = resolveRate(rateInput, static_cast<RatePath>(ratePath));
        row.actualDeadline = frameDuration(delay, row.actualRate);
        row.actualDelta = -row.actualDeadline;
        row.passed = bits(row.actualRate) == bits(row.expectedRate) && row.actualDeadline == row.expectedDeadline &&
            row.actualDelta == row.expectedDelta;
        const auto id = "native/" + std::to_string(row.precision) + "/" + row.name;
        report.check(row.passed, id);
        report.check(frameDuration(delay, row.actualRate) == row.actualDeadline, id + "/repeat-query");
        report.native.push_back(row);
    }
    if (in >> extra) throw std::runtime_error("Unexpected native clock fixture field");
    report.check(seen.size() == 46, "native/all-23-inputs-at-both-captured-precisions");
}
void arithmetic(Report &r) {
    const auto install = resolveRate(1000, RatePath::Installation);
    const auto refresh = resolveRate(1000, RatePath::Refresh);
    r.check(bits(install) == 0x42c80001u && bits(refresh) == 0x42c80000u,
        "rate/install-and-refresh-preserve-distinct-float32-stores");
    r.check(frameDuration(70, install) == 69 && frameDuration(300, install) == 299 &&
        frameDuration(70, refresh) == 70 && frameDuration(300, refresh) == 300,
        "rate/captured-1000-install-69-299-versus-refresh-70-300");
    r.check(nativeZeroRate(0) == 1 && nativeZeroRate(-0.0) == 1,
        "rate/zero-native-helper-is-separate-from-normal-profile");
    r.check(rescaleElapsed(100, 85, 150) == 56 && rescaleElapsed(100, 150, 85) == 176,
        "rate/change-truncates-the-complete-recovered-expression");
    const int32_t delays[] = {70, 70, 300};
    ClipView clip{delays, 3};
    r.check(deadlineCycle(clip, install, inferred) == 437 && totalDuration(clip, install) == 437,
        "rate/total-duration-helper-has-independent-api");
    r.check(frameDuration(0, 100) == 0 && frameDuration(1, 150) == 0,
        "rate/zero-delay-and-submillisecond-deadlines-are-not-clamped");
    // This is the explicitly selected portable model, not an extra native
    // fixture. The captured native vectors do not include this precision edge.
    const int32_t precisionEdge[] = {29};
    r.check(frameDuration(29, 100) == 28 && deadlineCycle({precisionEdge, 1}, 100,
        ClockPolicy::SourceDelay100) == 29,
        "rate/uncaptured-binary64-edge-is-distinct-from-source-delay-policy");
    for (double value : {0.0, -1.0, std::numeric_limits<double>::infinity(),
                         std::numeric_limits<double>::quiet_NaN(), 1e300, 1e-300})
        r.check(rejects([&] { resolveRate(value, RatePath::ExplicitPercent); }), "rate/reject-unsupported-explicit-input");
    r.check(rejects([] { resolveRate(850.5, RatePath::Refresh); }) &&
        rejects([] { resolveRate(1000, RatePath::Installation, 0); }) &&
        rejects([] { resolveRate(1000, static_cast<RatePath>(99)); }), "rate/reject-fractional-stat-invalid-global-and-path");
    r.check(rejects([] { frameDuration(-1, 100); }) && rejects([] { frameDuration(INT32_MAX, 0.01f); }) &&
        rejects([] { rescaleElapsed(UINT64_MAX, 100, 100); }), "rate/reject-delay-and-truncation-overflow");
}
void boundaries(Report &r) {
    const int32_t delays[] = {0, 0, 16, 17};
    const auto original = std::vector<int32_t>(std::begin(delays), std::end(delays));
    Cursor cursor;
    auto result = cursor.install({delays, 4});
    r.check(result.visits.size() == 3 && result.visits[0].frame == 0 && result.visits[1].frame == 1 &&
        result.visits[2].frame == 2 && result.snapshot.frame == 2 && result.snapshot.spanMs == 16,
        "cursor/install-consumes-ordered-zero-delay-prefix-once");
    result = cursor.advance(tick(1));
    r.check(result.snapshot.elapsedMs == 16 && result.snapshot.frame == 3 && result.snapshot.frameStartMs == 16 &&
        result.snapshot.nextDeadlineMs == 33 && result.snapshot.localMs == 0 && result.snapshot.spanMs == 17 &&
        result.visits.size() == 1 && !result.snapshot.ended, "cursor/deadline-equality-advances-and-publishes-actual-span");
    result = cursor.advance(tick(2));
    r.check(result.snapshot.elapsedMs == 33 && result.snapshot.ended && result.snapshot.frame == 3 &&
        result.snapshot.localMs == 17 && result.visits.empty(), "cursor/nonloop-ended-holds-final-frame-without-new-visit");
    result = cursor.advance(tick(3));
    r.check(result.snapshot.ended && result.snapshot.frame == 3 && result.snapshot.elapsedMs == 50 && result.visits.empty(),
        "cursor/ended-is-not-detach-and-does-not-reemit-events");
    r.check(std::equal(original.begin(), original.end(), std::begin(delays)), "cursor/source-delays-remain-immutable");
    Snapshot query;
    const int32_t ordinary[] = {16, 17};
    for (const auto pair : {std::pair<uint64_t, size_t>{0, 0}, {15, 0}, {16, 1}, {32, 1}, {33, 1}, {100, 1}}) {
        query.elapsedMs = pair.first;
        const auto pose = followRoot({ordinary, 2}, query);
        r.check(pose.frame == pair.second && pose.ended == (pair.first >= 33),
            "cursor/explicit-before-at-and-after-boundary-projection");
    }
    const int32_t single[] = {10};
    Cursor loop;
    loop.install({single, 1, true});
    for (uint64_t i = 1; i <= 10; ++i) {
        const auto step = loop.advance(tick(i));
        r.check(step.snapshot.frame == 0 && !step.snapshot.ended && step.visits.empty() && step.snapshot.visit == 1,
            "cursor/native-single-frame-loop-retains-installed-frame");
    }
    const int32_t shortLoop[] = {5, 5};
    loop.install({shortLoop, 2, true});
    result = loop.advance(tick(1));
    r.check(result.snapshot.frame == 1 && result.snapshot.loopCount == 1 && result.snapshot.localMs == 1 &&
        result.visits.size() == 3 && result.visits[0].frame == 1 && result.visits[1].frame == 0 &&
        result.visits[2].frame == 1, "cursor/short-crossed-frames-retain-all-ordered-visits");
    const auto before = loop.snapshot();
    r.check(rejects([&] { loop.advance(tick(2), 1); }) && same(before, loop.snapshot()),
        "cursor/exhausted-visit-budget-refuses-without-partial-publication");
    query.elapsedMs = 1000000;
    const auto projected = followRoot({shortLoop, 2, true}, query, 2);
    r.check(projected.frame == 0 && projected.loopCount == 100000 && projected.frameStartMs == 1000000,
        "cursor/read-only-child-projection-skips-old-loops-without-event-replay");
    const int32_t zero[] = {0, 0};
    r.check(rejects([&] { loop.install({zero, 2}); }) && same(before, loop.snapshot()),
        "cursor/all-zero-clip-refuses-atomically");
    r.check(rejects([&] { loop.install({single, 1}, 10000, inferred); }) && same(before, loop.snapshot()),
        "cursor/all-quantized-zero-spans-refuse-atomically");
    r.check(rejects([&] { loop.install({delays, 4}, 100, ClockPolicy::SourceDelay100, 0, 2); }) &&
        same(before, loop.snapshot()), "cursor/zero-prefix-budget-refuses-atomically");
}
void tickAndPause(Report &r) {
    const int32_t delays[] = {70, 70, 300};
    Cursor c;
    c.install({delays, 3}, resolveRate(1000, RatePath::Installation), inferred);
    for (uint64_t i = 1; i <= 4; ++i) c.advance(tick(i));
    r.check(c.snapshot().elapsedMs == 66 && c.snapshot().frame == 0 && c.snapshot().spanMs == 69,
        "tick/installation-deadline-precedes-source-delay");
    auto before = c.snapshot();
    const auto paused = c.advance(tick(5, true));
    r.check(paused.snapshot.elapsedMs == 66 && paused.snapshot.frame == 0 && paused.snapshot.lastTick == 5 &&
        paused.snapshot.paused && paused.visits.empty(), "tick/pause-advances-owner-tick-but-not-ANI-time");
    r.check(rejects([&] { c.advance(tick(5)); }) && rejects([&] { c.advance(tick(7)); }) &&
        rejects([&] { c.advance({6, 16, false}); }), "tick/reject-duplicate-skipped-and-wrong-16-17-delta");
    r.check(same(paused.snapshot, c.snapshot()), "tick/invalid-clock-input-preserves-published-state");
    auto resumed = c.advance(tick(6));
    r.check(resumed.snapshot.elapsedMs == 83 && resumed.snapshot.frame == 1 && resumed.snapshot.frameStartMs == 69 &&
        resumed.snapshot.spanMs == 69 && resumed.snapshot.localMs == 14 && resumed.visits.size() == 1,
        "tick/resume-advances-once-without-pause-debt-or-second-rate");
    c.install({delays, 3}, 85, inferred);
    for (uint64_t i = 1; i <= 6; ++i) c.advance(tick(i));
    before = c.snapshot();
    const auto refreshed = c.setRate(150);
    r.check(refreshed.elapsedMs == 56 && refreshed.frame == 1 && refreshed.frameStartMs == 46 &&
        refreshed.nextDeadlineMs == 92 && refreshed.spanMs == 46 && refreshed.localMs == 10 &&
        refreshed.lastTick == before.lastTick && refreshed.visit == before.visit && refreshed.rateRevision == 2,
        "tick/rate-change-reprojects-root-preserves-event-watermark-and-tick");
    r.check(same(refreshed, c.setRate(150)), "tick/identical-rate-is-idempotent");
    r.check(rejects([&] { c.setRate(0); }) && same(refreshed, c.snapshot()), "tick/invalid-refresh-is-atomic");
    Cursor source;
    source.install({delays, 3});
    r.check(rejects([&] { source.setRate(150); }), "tick/source-delay-mode-rejects-second-scaling");
    r.check(rejects([] { Cursor empty; empty.advance(tick(1)); }), "tick/uninstalled-cursor-rejects-advance");
}
void attachments(Report &r) {
    const int32_t body[] = {20, 30, 40};
    const int32_t child[] = {1, 1, 1, 25};
    const int32_t shortChild[] = {1, 1};
    Cursor root;
    root.install({body, 3});
    for (uint64_t i = 1; i <= 3; ++i) root.advance(tick(i));
    const auto state = root.snapshot();
    const auto childPose = followRoot({child, 4, false, body, 3}, state);
    const auto shortPose = followRoot({shortChild, 2, false, body, 3}, state);
    r.check(state.elapsedMs == 50 && state.frame == 2 && childPose.frame == 2 && childPose.frameStartMs == 50 &&
        childPose.spanMs == 40 && childPose.lastTick == state.lastTick && childPose.ratePercent == state.ratePercent,
        "attachment/child-shares-root-time-rate-and-copied-decoded-delay");
    r.check(shortPose.frame == 1 && shortPose.ended && shortPose.nextDeadlineMs == 50,
        "attachment/short-child-retains-own-frame-count-and-ended-state");
    Snapshot after = state; after.elapsedMs = 95;
    const auto extra = followRoot({child, 4, false, body, 3}, after);
    r.check(extra.frame == 3 && extra.frameStartMs == 90 && extra.spanMs == 25 && extra.localMs == 5 && !extra.ended,
        "attachment/min-copy-retains-child-extra-frame-source-delay");
    const auto unchanged = root.snapshot();
    followRoot({child, 4, false, body, 3}, state);
    r.check(same(unchanged, root.snapshot()) && child[0] == 1 && child[3] == 25 && body[0] == 20,
        "attachment/query-does-not-tick-root-or-mutate-shared-content");
    const auto paused = root.advance(tick(4, true));
    const auto following = followRoot({child, 4, false, body, 3}, paused.snapshot);
    r.check(following.elapsedMs == 50 && following.frame == 2 && following.paused && following.lastTick == 4,
        "attachment/following-child-inherits-paused-root-without-new-clock");
    r.check(rejects([&] { followRoot({child, 4, false, nullptr, 3}, state); }),
        "attachment/incomplete-shared-delay-view-rejected");
}
void renderCadences(Report &r) {
    const int32_t delays[] = {0, 5, 20, 45};
    std::vector<Snapshot> reference;
    std::vector<uint64_t> referenceVisits;
    for (int fps : {30, 60, 120, 144, 240}) {
        Cursor cursor;
        cursor.install({delays, 4, true}, resolveRate(850, RatePath::Refresh), inferred);
        uint64_t current = 0;
        std::vector<Snapshot> snapshots;
        std::vector<uint64_t> visits;
        for (int frame = 1; frame <= fps * 2; ++frame) {
            const uint64_t target = uint64_t(frame) * 60 / uint64_t(fps);
            while (current < target) {
                const auto out = cursor.advance(tick(++current));
                snapshots.push_back(out.snapshot);
                for (const auto &visit : out.visits) visits.push_back(visit.visit);
            }
        }
        if (reference.empty()) { reference = snapshots; referenceVisits = visits; }
        r.check(snapshots.size() == 120 && visits == referenceVisits &&
            std::equal(snapshots.begin(), snapshots.end(), reference.begin(), same),
            "cadence/" + std::to_string(fps) + "-Hz-render-preserves-every-fixed-tick-and-visit");
    }
    Cursor budgeted;
    budgeted.install({delays, 4, true}, resolveRate(850, RatePath::Refresh), inferred);
    uint64_t pending = 120, done = 0;
    std::vector<Snapshot> snapshots;
    while (pending) for (size_t i = 0, count = size_t(std::min<uint64_t>(8, pending)); i < count; ++i) {
        snapshots.push_back(budgeted.advance(tick(++done)).snapshot); --pending;
    }
    r.check(snapshots.size() == reference.size() && std::equal(snapshots.begin(), snapshots.end(), reference.begin(), same),
        "cadence/eight-tick-catch-up-budget-keeps-identical-clock-history");
}
std::string quote(const std::string &text) {
    std::string out = "\"";
    for (const char value : text) {
        if (value == '"' || value == '\\') out += '\\';
        if (value == '\n') out += "\\n";
        else if (value == '\r') out += "\\r";
        else out += value;
    }
    return out + '"';
}
void writeReport(const std::string &path, const Report &r) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Cannot write ANI clock report");
    out << std::setprecision(17) << "{\"schema\":\"dnf-ani-clock-contract-v1\",\"passed\":" << (r.passed() ? "true" : "false")
        << ",\"native_vectors_checked\":" << r.native.size() << ",\"native_runtime_clock_recovered\":false,\"error\":"
        << quote(r.error) << ",\"arithmetic_profile\":" << quote(arithmeticProfileName())
        << ",\"uncaptured_precision_edge\":{\"delay\":29,\"rate\":100,\"portable_duration\":"
        << frameDuration(29, 100) << ",\"source_delay_duration\":29,\"native_result\":null},\"checks\":[";
    for (size_t i = 0; i < r.checks.size(); ++i) {
        if (i) out << ',';
        out << "{\"name\":" << quote(r.checks[i].name) << ",\"passed\":" << (r.checks[i].passed ? "true" : "false") << '}';
    }
    out << "],\"native\":[";
    for (size_t i = 0; i < r.native.size(); ++i) {
        if (i) out << ',';
        const auto &v = r.native[i];
        out << "{\"name\":" << quote(v.name) << ",\"precision\":" << v.precision << ",\"passed\":" << (v.passed ? "true" : "false")
            << ",\"actual_rate_bits\":" << bits(v.actualRate) << ",\"captured_rate_bits\":" << bits(v.expectedRate)
            << ",\"actual_deadline\":" << v.actualDeadline << ",\"native_deadline\":" << v.expectedDeadline
            << ",\"actual_negative_delta\":" << v.actualDelta << ",\"native_negative_delta\":" << v.expectedDelta << '}';
    }
    out << "]}\n";
}
} // namespace
int main(int argc, char **argv) {
    if (argc != 3) { std::cerr << "clock-contract-test <captured-fixture> <report.json>\n"; return 2; }
    Report report;
    try {
        nativeVectors(argv[1], report);
        arithmetic(report); boundaries(report); tickAndPause(report); attachments(report); renderCadences(report);
    } catch (const std::exception &error) { report.error = error.what(); }
    try { writeReport(argv[2], report); } catch (const std::exception &error) { std::cerr << error.what() << '\n'; return 2; }
    const auto failures = std::count_if(report.checks.begin(), report.checks.end(), [](const Check &check) { return !check.passed; });
    std::cout << "ANI clock contract: " << report.native.size() << " native vectors, " << report.checks.size()
              << " checks, " << failures << " failures" << (report.error.empty() ? "" : "; " + report.error) << '\n';
    return report.passed() ? 0 : 1;
}
