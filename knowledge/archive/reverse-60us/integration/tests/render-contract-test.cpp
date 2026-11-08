#include "dnf_ani_render.hpp"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Captured native values are supplied by the verifier from the immutable
// package. This executable does not regenerate those expected values.
namespace {
using namespace dnf::ani_render;
constexpr auto inferred = RenderProfile::Inferred60Us1031;

struct Check {
    std::string name;
    bool passed;
};
struct NativeResult {
    std::string name;
    int precision = 0;
    Pose actual, expected;
    bool passed = false;
};
struct Report {
    std::vector<Check> checks;
    std::vector<NativeResult> native;
    std::string error;

    void check(bool passed, const std::string &name) {
        checks.push_back({name, passed});
    }
    bool passed() const {
        return error.empty() && native.size() == 24 &&
            std::all_of(checks.begin(), checks.end(), [](const Check &v) { return v.passed; });
    }
};

uint32_t bits(double value) {
    const float number = static_cast<float>(value);
    uint32_t result = 0;
    static_assert(sizeof(number) == sizeof(result), "IEEE binary32 required");
    std::memcpy(&result, &number, sizeof(result));
    return result;
}
bool floatExact(double actual, double expected) {
    return std::isfinite(actual) && actual == static_cast<double>(static_cast<float>(actual)) &&
        bits(actual) == bits(expected);
}
bool poseExact(const Pose &a, const Pose &b) {
    return a.position == b.position && a.rate == b.rate && a.angle == b.angle && a.rgba == b.rgba;
}
bool nativeExact(const Pose &a, const Pose &b) {
    return a.position == b.position && a.rgba == b.rgba &&
        floatExact(a.rate[0], b.rate[0]) && floatExact(a.rate[1], b.rate[1]) &&
        floatExact(a.angle, b.angle);
}
bool near(double a, double b, double tolerance = 1e-10) {
    return std::isfinite(a) && std::isfinite(b) && std::abs(a - b) <= tolerance;
}
void readPose(std::istream &in, Pose &pose) {
    in >> pose.position[0] >> pose.position[1] >> pose.rate[0] >> pose.rate[1] >> pose.angle;
    for (double &channel : pose.rgba) in >> channel;
    const double values[] = {pose.position[0], pose.position[1], pose.rate[0], pose.rate[1],
        pose.angle, pose.rgba[0], pose.rgba[1], pose.rgba[2], pose.rgba[3]};
    if (!in || std::any_of(std::begin(values), std::end(values),
            [](double value) { return !std::isfinite(value); }))
        throw std::runtime_error("Invalid/truncated pose fixture");
}
void nativeVectors(const std::string &path, Report &report) {
    std::ifstream input(path);
    if (!input) throw std::runtime_error("Cannot open captured native vector fixture");
    std::string line, magic, extra;
    size_t count = 0;
    if (!std::getline(input, line)) throw std::runtime_error("Missing native fixture header");
    std::istringstream header(line);
    if (!(header >> magic >> count) || magic != "DNF_RENDER_NATIVE_VECTORS_V1" ||
            count != 24 || (header >> extra))
        throw std::runtime_error("Invalid native fixture header");
    std::set<std::pair<int, std::string>> seen;
    const std::set<std::string> names = {"before", "start", "quarter", "middle", "late",
        "end", "after", "disabled", "ended", "last_nonloop", "last_loop",
        "negative_coordinate_fraction"};
    for (size_t index = 0; index < count; ++index) {
        if (!std::getline(input, line)) throw std::runtime_error("Missing native fixture row");
        std::istringstream row(line);
        NativeResult result;
        int enabled = 0, ended = 0, last = 0, loop = 0;
        SampleContext context;
        Pose a, b;
        row >> result.name >> result.precision >> enabled >> ended >> last >> loop
            >> context.elapsed >> context.span;
        if (!row || names.count(result.name) == 0 ||
                (result.precision != 64 && result.precision != 53) ||
                (enabled != 0 && enabled != 1) || (ended != 0 && ended != 1) ||
                (last != 0 && last != 1) || (loop != 0 && loop != 1) ||
                !std::isfinite(context.elapsed) || !std::isfinite(context.span) ||
                !seen.emplace(result.precision, result.name).second)
            throw std::runtime_error("Invalid/duplicated native fixture metadata");
        readPose(row, a);
        readPose(row, b);
        readPose(row, result.expected);
        if (row >> extra) throw std::runtime_error("Unconsumed native fixture fields");
        context.enabled = enabled != 0;
        context.ended = ended != 0;
        context.hasNext = !last || loop;
        const auto originalA = a, originalB = b;
        const auto sampled = samplePose(a, b, context, inferred);
        result.actual = sampled.pose;
        result.passed = nativeExact(result.actual, result.expected);
        const auto id = "native/" + std::to_string(result.precision) + "/" + result.name;
        report.check(result.passed, id);
        report.check(poseExact(originalA, a) && poseExact(originalB, b), id + "/input-preserved");
        const auto repeated = samplePose(a, b, context, inferred);
        report.check(poseExact(sampled.pose, repeated.pose) &&
            sampled.active == repeated.active && sampled.ratio == repeated.ratio,
            id + "/repeat-query");
        report.native.push_back(result);
    }
    while (std::getline(input, line)) {
        if (line.find_first_not_of(" \t\r") != std::string::npos)
            throw std::runtime_error("Unexpected trailing native fixture row");
    }
    report.check(seen.size() == 24, "fixture/all-12-cases-at-both-captured-precisions");
}

void controlCases(Report &report) {
    Pose a, b;
    a.position = {-7, -65};
    a.rate = {0.2, 0.05};
    a.rgba = {255, 255, 255, 0};
    b.position = {16, -6};
    b.rate = {0.6, 0.6};
    b.angle = 6.28;
    b.rgba = {60, 0, 255, 255};
    SampleContext context;
    context.elapsed = 250;
    context.span = 500;
    const auto source = samplePose(a, b, SampleContext{}, inferred).pose;
    const auto gate = [&](SampleContext gated, const std::string &name) {
        const auto output = samplePose(a, b, gated, inferred);
        report.check(!output.active && output.ratio == 0 && poseExact(output.pose, source), name);
    };
    auto gated = context;
    gated.enabled = false;
    gate(gated, "controls/source-switch-disabled");
    gated = context;
    gated.requested = false;
    gate(gated, "controls/caller-disabled");
    gated = context;
    gated.frozen = true;
    gate(gated, "controls/frozen-reference-holds-source");
    gated = context;
    gated.ended = true;
    gate(gated, "controls/ended-holds-source");
    gated = context;
    gated.hasNext = false;
    gate(gated, "controls/no-target-holds-source");
    for (const double span : {0.0, -1.0, std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::quiet_NaN()}) {
        gated = context;
        gated.span = span;
        gate(gated, "controls/invalid-span-holds-source");
    }
    for (const double elapsed : {std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::quiet_NaN()}) {
        gated = context;
        gated.elapsed = elapsed;
        gate(gated, "controls/nonfinite-elapsed-holds-source");
    }
    gated = context;
    gated.elapsed = -1;
    auto sample = samplePose(a, b, gated, inferred);
    report.check(sample.active && sample.ratio == 0 && poseExact(sample.pose, source),
        "controls/before-start-retains-native-source");
    gated.elapsed = 501;
    sample = samplePose(a, b, gated, inferred);
    report.check(sample.active && sample.ratio == 1 && sample.pose.position == b.position &&
        sample.pose.rgba == b.rgba && floatExact(sample.pose.angle, b.angle),
        "controls/after-end-uses-native-target");
    gated = context;
    gated.elapsed = 125.9;
    const auto integral = samplePose(a, b, gated, inferred);
    gated.elapsed = 125;
    report.check(poseExact(integral.pose, samplePose(a, b, gated, inferred).pose),
        "adapter/integral-source-clock-policy");

    Pose start, end;
    start.angle = -6.28;
    end.angle = 6.28;
    gated = context;
    gated.elapsed = 125;
    const auto rotation = samplePose(start, end, gated, inferred);
    report.check(floatExact(rotation.pose.angle, -3.140000104904175),
        "native-angle/raw-full-revolution-no-shortest-arc");
    start.rgba = {-1, 256, 257.9, -257.1};
    gated.requested = false;
    report.check(samplePose(start, end, gated, inferred).pose.rgba ==
        std::array<double, 4>{255, 0, 1, 255}, "adapter/color-byte-low-eight-bits");
    const auto legacy = samplePose(a, b, context, RenderProfile::Legacy1031);
    report.check(legacy.active && legacy.pose.position == std::array<double, 2>{4.5, -35.5} &&
        legacy.pose.rgba == std::array<double, 4>{157.5, 127.5, 255, 127.5},
        "legacy/separate-fractional-interpolation-no-native-claim");
    report.check(std::string(profileName(inferred)) == "inferred60us1031" &&
        std::string(profileEvidence(inferred)) == "cross-version-inference-from-60US" &&
        std::string(profileName(RenderProfile::Legacy1031)) == "legacy1031",
        "adapter/explicit-profile-and-evidence-labels");
}

void checkQuad(Report &report, const std::string &name, const QuadInput &input,
        const std::array<Point, 4> &expected, RenderProfile profile = inferred) {
    const auto actual = makeQuad(input, profile);
    for (size_t i = 0; i < expected.size(); ++i)
        report.check(near(actual.vertices[i].x, expected[i].x) &&
            near(actual.vertices[i].y, expected[i].y), name + "/vertex-" + std::to_string(i));
}
void transformCases(Report &report) {
    // Expected vertices are explicit geometry examples, not a second copy of
    // makeQuad. Crop/image positions are both measured from the source origin.
    QuadInput input;
    input.actorX = 100;
    input.actorY = 50;
    input.actorZ = 7;
    input.cropX = -2;
    input.cropY = 5;
    input.width = 4;
    input.height = 2;
    input.pose.position = {3, -4};
    checkQuad(report, "quad/position-crop-and-z", input,
        {{{101, 44}, {105, 44}, {105, 46}, {101, 46}}});
    input.actorX = -10;
    input.actorY = -20;
    input.actorZ = 3;
    input.pose.position = {-7, -6};
    input.cropX = -2;
    input.cropY = -3;
    input.width = 2;
    input.height = 1;
    checkQuad(report, "quad/negative-world-and-local-coordinates", input,
        {{{-19, -32}, {-17, -32}, {-17, -31}, {-19, -31}}});

    input = QuadInput{};
    input.actorX = 20;
    input.actorY = 20;
    input.pose.position = {3, 2};
    input.pose.rate = {2, 1};
    input.pose.angle = std::acos(-1.0) / 2;
    input.width = 2;
    input.height = 1;
    checkQuad(report, "quad/nonuniform-output-scale-negative-radian-sign", input,
        {{{24, 17}, {24, 15}, {26, 15}, {26, 17}}});
    input.direction = -1;
    checkQuad(report, "quad/facing-mirrors-output-x-preserves-uv-order", input,
        {{{16, 17}, {16, 15}, {14, 15}, {14, 17}}});
    input.direction = 1;
    input.pose.rate = {-2, -1};
    checkQuad(report, "quad/negative-rates-with-rotation", input,
        {{{16, 23}, {16, 25}, {14, 25}, {14, 23}}});
    input.pose.rate = {2, 1};
    checkQuad(report, "quad/legacy-positive-angle-and-local-axis-scale", input,
        {{{18, 26}, {18, 30}, {17, 30}, {17, 26}}}, RenderProfile::Legacy1031);
    input.pose.angle = 2 * std::acos(-1.0);
    checkQuad(report, "quad/full-turn-keeps-source-origin", input,
        {{{26, 22}, {30, 22}, {30, 23}, {26, 23}}});
    input.pose.rate = {0, 0};
    checkQuad(report, "quad/zero-rate-collapses-at-actor-origin", input,
        {{{20, 20}, {20, 20}, {20, 20}, {20, 20}}});
}

void colorCases(Report &report) {
    report.check(classifyBlend(0) == BlendMode::Normal &&
        classifyBlend("NONE") == BlendMode::Normal, "blend/NONE-classification");
    report.check(classifyBlend(2) == BlendMode::LinearDodge &&
        classifyBlend("LINEARDODGE") == BlendMode::LinearDodge, "blend/LINEARDODGE-classification");
    for (int effect : {-1, 1, 3, 255})
        report.check(classifyBlend(effect) == BlendMode::Unsupported,
            "blend/unsupported-numeric-effect-" + std::to_string(effect));
    for (const std::string effect : {"", "none", "SCREEN", "LINEARDODGE "})
        report.check(classifyBlend(effect) == BlendMode::Unsupported,
            "blend/unsupported-text-effect-" + effect);
    const auto color = textureModulate({200, 100, 50, 128}, {60, 0, 255, 128});
    report.check(near(color[0], 12000.0 / 255) && color[1] == 0 && color[2] == 50 &&
        near(color[3], 16384.0 / 255), "color/texture-times-frame-independent-RGBA");
    const std::array<double, 3> source{200, 100, 50}, destination{10, 20, 30};
    const auto normal = blendRgb(source, destination, color[3], BlendMode::Normal);
    const auto additive = blendRgb(source, destination, color[3], BlendMode::LinearDodge);
    // Effective alpha is 128*128/(255*255), applied once by blendRgb.
    constexpr double alpha = 16384.0 / 65025.0;
    const std::array<double, 3> normalExpected{
        10 + 190 * alpha, 20 + 80 * alpha, 30 + 20 * alpha};
    const std::array<double, 3> additiveExpected{
        10 + 200 * alpha, 20 + 100 * alpha, 30 + 50 * alpha};
    for (size_t i = 0; i < 3; ++i) {
        report.check(near(normal[i], normalExpected[i]), "blend/NONE-alpha-once-" + std::to_string(i));
        report.check(near(additive[i], additiveExpected[i]),
            "blend/LINEARDODGE-alpha-once-" + std::to_string(i));
    }
    report.check(blendRgb(source, destination, 0, BlendMode::Normal) == destination &&
        blendRgb(source, destination, 0, BlendMode::LinearDodge) == destination,
        "blend/zero-alpha-preserves-destination");
    report.check(blendRgb(source, destination, 255, BlendMode::Normal) == source,
        "blend/opaque-NONE-replaces-destination");
    report.check(blendRgb({250, 240, 100}, {20, 30, 200}, 255, BlendMode::LinearDodge) ==
        std::array<double, 3>{255, 255, 255}, "blend/LINEARDODGE-saturates");
    report.check(blendRgb(source, destination, 255, BlendMode::Unsupported) == destination,
        "blend/unsupported-has-explicit-classification-and-preserves-destination");
    report.check(blendRgb(source, destination, -1, BlendMode::Normal) == destination &&
        blendRgb(source, destination, 256, BlendMode::Normal) == source,
        "adapter/alpha-clamped-to-byte-domain");
}

std::string quoted(const std::string &value) {
    std::ostringstream out;
    out << '"';
    for (const unsigned char c : value) {
        if (c == '"' || c == '\\') out << '\\' << static_cast<char>(c);
        else if (c < 32) out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
            << static_cast<unsigned>(c) << std::dec;
        else out << static_cast<char>(c);
    }
    out << '"';
    return out.str();
}
void jsonPose(std::ostream &out, const Pose &pose) {
    out << std::setprecision(17) << "{\"position\":[" << pose.position[0] << ',' << pose.position[1]
        << "],\"rate\":[" << pose.rate[0] << ',' << pose.rate[1] << "],\"angle\":" << pose.angle
        << ",\"rgba\":[" << pose.rgba[0] << ',' << pose.rgba[1] << ',' << pose.rgba[2] << ','
        << pose.rgba[3] << "],\"float32_bits\":[" << bits(pose.rate[0]) << ','
        << bits(pose.rate[1]) << ',' << bits(pose.angle) << "]}";
}
void writeReport(const std::string &path, const Report &report) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write contract report");
    out << "{\n\"schema\":\"dnf-ani-render-contract-v1\",\n\"passed\":"
        << (report.passed() ? "true" : "false") << ",\n\"native_vectors_checked\":"
        << report.native.size() << ",\n\"checks\":" << report.checks.size()
        << ",\n\"scope\":\"60US captured local pose outputs plus portable adapter geometry and color; 1031 behavior inferred\","
        << "\n\"limitations\":[\"No original-game execution\","
        << "\"No game clock/frame-advance equivalence\","
        << "\"No GPU or original pixel equivalence\","
        << "\"Discrete image/effect/boxes/events remain caller-owned\"],"
        << "\n\"error\":" << quoted(report.error) << ",\n\"native_vectors\":[";
    for (size_t i = 0; i < report.native.size(); ++i) {
        const auto &row = report.native[i];
        if (i) out << ',';
        out << "\n{\"name\":" << quoted(row.name) << ",\"captured_x87_precision\":" << row.precision
            << ",\"passed\":" << (row.passed ? "true" : "false") << ",\"actual\":";
        jsonPose(out, row.actual);
        out << ",\"captured_native\":";
        jsonPose(out, row.expected);
        out << '}';
    }
    out << "\n],\n\"results\":[";
    for (size_t i = 0; i < report.checks.size(); ++i) {
        if (i) out << ',';
        out << "\n{\"name\":" << quoted(report.checks[i].name) << ",\"passed\":"
            << (report.checks[i].passed ? "true" : "false") << '}';
    }
    out << "\n]\n}\n";
    if (!out) throw std::runtime_error("Incomplete contract report write");
}
} // namespace

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: render-contract-test native-vectors.txt contract-report.json\n";
        return 2;
    }
    Report report;
    try {
        nativeVectors(argv[1], report);
        controlCases(report);
        transformCases(report);
        colorCases(report);
    } catch (const std::exception &error) {
        report.error = error.what();
    }
    try {
        writeReport(argv[2], report);
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
    for (const auto &check : report.checks)
        if (!check.passed) std::cerr << "FAIL " << check.name << '\n';
    if (!report.error.empty()) std::cerr << report.error << '\n';
    std::cout << report.native.size() << " captured native vectors; " << report.checks.size()
        << " checks; " << (report.passed() ? "PASS" : "FAIL") << '\n';
    return report.passed() ? 0 : 1;
}
