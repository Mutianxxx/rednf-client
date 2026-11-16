#include "dnf/ptl_program.hpp"
#include <algorithm>
#include <filesystem>
#include <map>
#include <set>
#include <utility>

namespace dnf {
namespace {
std::string relativeTo(const std::string &parent, const std::string &child) {
    return normalize(
        (std::filesystem::u8path(parent).parent_path() / std::filesystem::u8path(normalize(child)))
            .lexically_normal()
            .generic_u8string());
}
bool endsWith(const std::string &value, const char *tail) {
    const std::string suffix = tail;
    return value.size() >= suffix.size() && value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
}
int32_t asInt32(double value) {
    return int32_t(std::clamp(value, double(INT32_MIN), double(INT32_MAX)));
}
void noteUnrecovered(PtlProgram &program, const std::string &field, const std::string &reason) {
    program.diagnostics.push_back({{"field", field}, {"reason", reason}});
}

// passiveobject/passiveobject.lst maps numeric object ids to .obj paths; the
// same registry ObjectCatalog uses (src/simulation/entities/objects.cpp:55-60).
std::map<int, std::string> readObjectRegistry(Pvf &pvf) {
    std::map<int, std::string> paths;
    try {
        const auto registry = pvf.script("passiveobject/passiveobject.lst");
        for (size_t i = 0; i + 1 < registry.tokens.size(); ++i) {
            const auto &id = registry.tokens[i]["value"];
            const auto &path = registry.tokens[i + 1]["value"];
            if (id.is_number_integer() && path.is_string())
                paths.emplace(id.get<int>(),
                              relativeTo("passiveobject/passiveobject.lst", path.get<std::string>()));
        }
    } catch (const std::exception &) {
    }
    return paths;
}

// A [passive object] particle draws the object's [basic motion] animation —
// the same chain the object pass walks (objects.cpp [basic motion] handling).
std::string objectAnimation(Pvf &pvf, const std::map<int, std::string> &registry, int id) {
    const auto found = registry.find(id);
    if (found == registry.end() || !pvf.has(found->second)) return {};
    try {
        const auto object = pvf.script(found->second);
        for (const auto &field : object.fields) {
            if (normalize(field.tag) != "[basic motion]") continue;
            for (const auto &value : field.values) {
                if (!value.is_string() || normalize(value.get<std::string>()).empty()) continue;
                const auto path = relativeTo(found->second, value.get<std::string>());
                if (endsWith(path, ".ani") && pvf.has(path)) return path;
            }
        }
    } catch (const std::exception &) {
    }
    return {};
}
} // namespace

bool ptlFieldStructural(const std::string &tag) {
    return tag == "[/object]" || tag == "[end]";
}
bool ptlFieldConsumed(const std::string &tag) {
    static const std::set<std::string> consumed = {
        "[x axis]", "[y axis]", "[z axis]", "[move type]", "[move variable 1]",
        "[changing term]", "[changing type]", "[gravity]", "[life time]",
        "[maximum create number]", "[transparent value]", "[create area size]",
        "[object]", "[object type]"};
    return consumed.find(tag) != consumed.end();
}

PtlProgram readPtl(Pvf &pvf, const std::string &path) {
    PtlProgram program;
    program.path = normalize(path);
    Script source;
    try {
        source = pvf.script(program.path);
    } catch (const std::exception &failure) {
        program.error = failure.what();
        return program;
    }
    int axis = -1;
    std::string objectType;
    std::vector<std::pair<std::string, int>> objectPairs;
    bool objectPairsMalformed = false;
    for (const auto &field : source.fields) {
        const auto tag = normalize(field.tag);
        if (tag == "[x axis]") axis = 0;
        else if (tag == "[y axis]") axis = 1;
        else if (tag == "[z axis]") axis = 2;
        else if (tag == "[move type]") {
            // Only straight-line motion is recovered. The [sin]/[cos] wave and
            // the back-and-forth branch of CNRDParticle__vmt48 stay diagnostic.
            if (!(field.values.size() == 1 && field.values[0].is_string() &&
                  normalize(field.values[0].get<std::string>()) == "[straight line]")) {
                program.error = "不支持的 [move type]（仅 [straight line]）";
                return program;
            }
        } else if (tag == "[move variable 1]" && axis >= 0) {
            if (field.values.size() != 2 || !field.values[0].is_number() || !field.values[1].is_number()) {
                program.error = "畸形的 [move variable 1]";
                return program;
            }
            program.velocity[size_t(axis)] = {field.values[0].get<double>(), field.values[1].get<double>()};
        } else if (tag == "[changing term]") {
            if (axis < 0 || field.values.size() != 1 || !field.values[0].is_number()) {
                program.error = "畸形的 [changing term]（缺少轴或数值）";
                return program;
            }
            program.changingTermMs[size_t(axis)] = asInt32(field.values[0].get<double>());
        } else if (tag == "[changing type]") {
            if (!(field.values.size() == 1 && field.values[0].is_string() &&
                  normalize(field.values[0].get<std::string>()) == "[keep last value]")) {
                program.error = "不支持的 [changing type]（仅 [keep last value]）";
                return program;
            }
        } else if (tag == "[gravity]") {
            program.gravity = source.number(field.tag);
        } else if (tag == "[life time]") {
            program.lifeMs = source.number(field.tag);
        } else if (tag == "[maximum create number]") {
            program.count = int(source.number(field.tag));
        } else if (tag == "[transparent value]") {
            if (field.values.size() != 2 || !field.values[0].is_number() || !field.values[1].is_number()) {
                program.error = "畸形的 [transparent value]";
                return program;
            }
            program.alphaStart = field.values[0].get<double>();
            program.alphaEnd = field.values[1].get<double>();
        } else if (tag == "[create area size]") {
            if (field.values.size() != 3 || !std::all_of(field.values.begin(), field.values.end(),
                                                        [](const Json &v) { return v.is_number(); })) {
                program.error = "畸形的 [create area size]";
                return program;
            }
            for (size_t i = 0; i < 3; ++i) program.area[i] = field.values[i].get<double>();
        } else if (tag == "[object]") {
            if (field.values.size() % 2) {
                objectPairsMalformed = true;
                continue;
            }
            for (size_t i = 0; i + 1 < field.values.size(); i += 2) {
                if (!field.values[i].is_string() || !field.values[i + 1].is_number_integer()) {
                    objectPairsMalformed = true;
                    continue;
                }
                objectPairs.emplace_back(field.values[i].get<std::string>(),
                                         field.values[i + 1].get<int>());
            }
        } else if (tag == "[object type]") {
            if (field.values.size() != 1 || !field.values[0].is_string()) {
                program.error = "畸形的 [object type]";
                return program;
            }
            objectType = normalize(field.values[0].get<std::string>());
        } else if (tag == "[creation frequency]") {
            const double frequency = source.number(field.tag, -1);
            if (frequency != -1)
                noteUnrecovered(program, field.tag, "持续发射未实现（只做一次性 burst）");
        } else if (tag == "[maximum create time]") {
            if (source.number(field.tag, 0) != 0)
                noteUnrecovered(program, field.tag, "持续发射时限未实现（只做一次性 burst）");
        } else if (tag == "[rotation angle]" || tag == "[rotation angle range type]" ||
                   tag == "[rotation angle variable]" || tag == "[random range]" ||
                   tag == "[move variable 2]" || tag == "[move variable 3]" ||
                   tag == "[display effect rate]" || tag == "[landing type]" ||
                   tag == "[destroy condition]" || tag == "[creation pos]" ||
                   tag == "[create pos correct]" || tag == "[create area rotation angle]") {
            noteUnrecovered(program, field.tag, "该字段的消费语义未恢复");
        } else if (ptlFieldStructural(tag)) {
            // Closing tags carry no behavior; their presence is structure, not
            // a field whose semantics could be silently dropped.
        } else {
            noteUnrecovered(program, field.tag, "未知 PTL 字段；无消费者，按缺口记录而非忽略");
        }
    }
    // Resolve [object] after the walk: whether a pair names an animation or a
    // passive object id depends on [object type], which may appear before or
    // after the [object] field itself.
    if (objectPairsMalformed) {
        program.error = "畸形的 [object] 对";
        return program;
    }
    if (objectType.empty() || objectType == "[animation]") {
        for (const auto &pair : objectPairs) {
            if (normalize(pair.first).empty()) {
                program.error = "[animation] 型粒子的 [object] 路径为空";
                return program;
            }
            auto animation = relativeTo(program.path, pair.first);
            if (!endsWith(animation, ".ani")) {
                program.error = "[object] 不是 .ani: " + animation;
                return program;
            }
            if (!pvf.has(animation)) {
                const auto direct = normalize(pair.first);
                if (!pvf.has(direct)) {
                    program.error = "[object] ANI 未解析: " + animation;
                    return program;
                }
                animation = direct;
            }
            program.objects.push_back({animation, pair.second});
        }
    } else if (objectType == "[passive object]") {
        const auto registry = readObjectRegistry(pvf);
        for (const auto &pair : objectPairs) {
            if (!normalize(pair.first).empty()) {
                program.error = "[passive object] 型粒子带有未识别的路径前缀: " + pair.first;
                return program;
            }
            auto animation = objectAnimation(pvf, registry, pair.second);
            if (animation.empty()) {
                program.error = "对象 id=" + std::to_string(pair.second) + " 无 [basic motion] 动画";
                return program;
            }
            program.objects.push_back({std::move(animation), -1});
        }
    } else {
        program.error = "不支持的 [object type]: " + objectType;
        return program;
    }
    // The three area numbers are source bytes, but their random distribution is
    // not closed by current-end native evidence. The World factory applies a
    // deterministic in-range offset; that is reconstruction, not equivalence.
    if (std::any_of(program.area.begin(), program.area.end(), [](double v) { return v != 0; }))
        noteUnrecovered(program, "[create area size]", "区域随机分布未恢复；仅做确定性范围内偏移");
    if (program.count > 512) program.count = 512; // bounded like the object pass
    if (program.objects.empty()) program.error = "没有 [object] 动画";
    else if (program.count <= 0) program.error = "[maximum create number] <= 0";
    else if (program.lifeMs <= 0) program.error = "[life time] <= 0";
    return program;
}
} // namespace dnf
