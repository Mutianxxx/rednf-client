#include "dnf/effect_plan.hpp"
#include <functional>
#include <limits>
#include <map>
#include <set>
namespace dnf {
std::string effectResource(Pvf &pvf, const std::string &source, const std::string &child) {
    const auto name = normalize(child);
    const auto local = normalize((std::filesystem::u8path(source).parent_path() /
                                  std::filesystem::u8path(name)).lexically_normal().generic_u8string());
    std::set<std::string> candidates;
    for (const auto &p : {local, name}) if (pvf.has(p)) candidates.insert(p);
    return candidates.size() == 1 ? *candidates.begin() : "";
}
EffectEventPlan animationEffectEvents(Pvf &pvf, Assets &assets, const std::string &animation, const std::string &sourceTreePolicy) {
    EffectEventPlan out;
    out.animation = normalize(animation);
    const auto als = out.animation + ".als";
    // This reviewed source-tree policy admits one native layout. It
    // does not make follow-parent a generic supported ALS command.
    const bool followPolicy=sourceTreePolicy=="inferred-current1031-watercannon-tree-v1"&&
        pvf.identity()=="d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d"&&
        out.animation.rfind("passiveobject/character/mage/animation/atwatercannon/",0)==0;
    const auto diagnostic = [&](const std::string &code, size_t order, const Field *field,
                                const std::string &reason) {
        Json issue = {{"code", code}, {"path", als}, {"animation", out.animation},
            {"source_order", order}, {"reason", reason}};
        if (field) {
            issue["offset"] = field->offset;
            issue["tag"] = field->tag;
            issue["values"] = field->values;
        }
        if (!out.alsSource.source.empty()) issue["source"] = out.alsSource.source;
        out.diagnostics.push_back(std::move(issue));
    };
    if (!pvf.has(out.animation)) {
        diagnostic("missing_parent_animation", 0, nullptr, "parent animation is absent");
        return out;
    }
    try {
        out.frameCount = assets.animation(out.animation)->frames.size();
    } catch (const std::exception &error) {
        diagnostic("invalid_parent_animation", 0, nullptr, error.what());
        return out;
    }
    if (!pvf.has(als)) return out; // No ALS sidecar is a normal leaf animation.
    try {
        out.alsSource = pvf.script(als);
    } catch (const std::exception &error) {
        // Preserve the unparsed document as well when ScriptFile framing fails.
        out.alsSource.path = als;
        out.alsSource.rawBytes = pvf.read(als);
        if (pvf.reads().contains(als)) out.alsSource.source = pvf.reads().at(als);
        diagnostic("invalid_als_script", 0, nullptr, error.what());
        return out;
    }
    if (out.frameCount == 0) {
        diagnostic("empty_parent_animation", 0, nullptr, "no source frames can receive ALS events");
        return out;
    }
    // Resolved JSON values alone cannot distinguish native string token 7 from
    // other string-table token kinds. Preserve and validate the ALS grammar.
    std::map<size_t, std::vector<int>> payloadTypes;
    size_t fieldOffset = 0;
    bool hasTag = false, leadingTokens = false;
    for (const auto &token : out.alsSource.tokens) {
        const int type = token.at("type").get<int>();
        if (type == 5) {
            fieldOffset = token.at("offset").get<size_t>();
            hasTag = true;
            payloadTypes[fieldOffset];
        } else if (hasTag) payloadTypes[fieldOffset].push_back(type);
        else leadingTokens = true;
    }
    if (leadingTokens)
        diagnostic("invalid_als_leading_tokens", 0, nullptr, "tokens before the first ALS tag are not executable");
    // Declaration identity is exact and case-sensitive in the 1031 parser.
    // Resolve the whole table first, retaining duplicate/ambiguous bindings.
    struct Declaration { size_t order; const Field *field; std::string animation; };
    std::map<std::string, std::vector<Declaration>> declarations;
    for (size_t order = 0; order < out.alsSource.fields.size(); ++order) {
        const auto &field = out.alsSource.fields[order];
        if (field.tag != "[use animation]") continue;
        const auto &v = field.values;
        if (payloadTypes[field.offset] != std::vector<int>{7, 7} ||
            v.size() != 2 || !v[0].is_string() || !v[1].is_string() ||
            v[0].get<std::string>().empty() || v[1].get<std::string>().empty() ||
            v[0].get<std::string>().find('\0') != std::string::npos ||
            v[1].get<std::string>().find('\0') != std::string::npos) {
            diagnostic("invalid_als_declaration", order, &field, "expected path and nonempty uniqueName");
            continue;
        }
        const auto instance = v[1].get<std::string>();
        auto &bindings = declarations[instance];
        bindings.push_back({order, &field, effectResource(pvf, als, v[0].get<std::string>())});
        if (bindings.size() > 1)
            diagnostic("duplicate_als_name", order, &field, "uniqueName has multiple declarations; no binding is selected");
    }
    const auto integer = [](const Json &value, int64_t minimum, int64_t maximum, int &result) {
        if (!value.is_number_integer()) return false;
        if (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(maximum)) return false;
        const auto number = value.get<int64_t>();
        if (number < minimum || number > maximum) return false;
        result = int(number);
        return true;
    };
    for (size_t order = 0; order < out.alsSource.fields.size(); ++order) {
        const auto &field = out.alsSource.fields[order];
        const auto &v = field.values;
        if (field.tag == "[use animation]") continue;
        const bool followParent=field.tag=="[create draw only object follow parent]"&&followPolicy;
        const bool drawOnly = field.tag == "[create draw only object]"||followParent;
        if (field.tag != "[add]" && field.tag != "[remove]" && !drawOnly) {
            diagnostic("unsupported_als_command", order, &field,
                "command has no recovered live consumer in this adapter");
            continue;
        }
        int frame = 0, layer = 0, x = 0, y = 0, z = 0;
        const auto i16 = [&](const Json &value, int &result) {
            return integer(value, std::numeric_limits<int16_t>::min(),
                std::numeric_limits<int16_t>::max(), result);
        };
        const bool payloadValid = drawOnly ?
            payloadTypes[field.offset] == std::vector<int>{2, 7, 2, 2, 2} &&
                v.size() == 5 && i16(v[0], frame) && i16(v[2], x) && i16(v[3], y) && i16(v[4], z) :
            payloadTypes[field.offset] == std::vector<int>{2, 2, 7} &&
                v.size() == 3 && integer(v[0], std::numeric_limits<int16_t>::min(),
                    std::numeric_limits<int16_t>::max(), frame);
        // Keep the two native layouts separate: draw-only has no layer field.
        const bool layerValid = drawOnly || (v.size() == 3 && integer(v[1],
            std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max(), layer));
        const size_t nameIndex = drawOnly ? 1 : 2;
        if (!payloadValid || !layerValid || !v[nameIndex].is_string() ||
            v[nameIndex].get<std::string>().empty() || v[nameIndex].get<std::string>().find('\0') != std::string::npos) {
            diagnostic("invalid_als_event", order, &field,
                drawOnly ? "expected signed i16 frame, uniqueName, and signed i16 XYZ" :
                    "expected signed frame, layer and nonempty uniqueName");
            continue;
        }
        if (drawOnly && z <= -1000) {
            diagnostic("unsupported_als_ground_layer", order, &field,
                "native Z sentinel selects ground height and layer enum 2; layer rendering contract is not recovered");
            continue;
        }
        if (frame < 0 || size_t(frame) >= out.frameCount) {
            diagnostic("unsupported_als_frame", order, &field, "frame is outside the parent source frame set");
            continue;
        }
        const auto instance = v[nameIndex].get<std::string>();
        const auto found = declarations.find(instance);
        if (found == declarations.end() || found->second.size() != 1) {
            diagnostic("unresolved_als_name", order, &field,
                found == declarations.end() ? "uniqueName is undeclared" : "uniqueName declaration is ambiguous");
            continue;
        }
        const auto &declaration = found->second.front();
        if (declaration.animation.empty()) {
            diagnostic("unresolved_als_animation", order, &field,
                "declared ANI is absent or its relative/root reference is ambiguous");
            continue;
        }
        if (field.tag != "[remove]") {
            try {
                // Image-less ANI frames are valid logical instances. Only an
                // absent/invalid clip or a clip without frames blocks add.
                if (assets.animation(declaration.animation)->frames.empty()) {
                    diagnostic("empty_als_animation", order, &field, "declared ANI has no source frames");
                    continue;
                }
            } catch (const std::exception &error) {
                diagnostic("invalid_als_animation", order, &field, error.what());
                continue;
            }
        }
        out.events.push_back({followParent?EffectEventKind::DrawOnlyFollowParent:drawOnly ? EffectEventKind::DrawOnly :
            field.tag == "[add]" ? EffectEventKind::Add : EffectEventKind::Remove,
            frame, layer, order, field.offset, declaration.field->offset, declaration.animation,
            instance, als, out.alsSource.source.value("member_sha256", ""), x, y, z});
    }
    return out;
}
EffectPlan animationEffectPlan(Pvf &pvf, Assets &assets, const std::string &animation, const std::string &sourceTreePolicy) {
    (void)sourceTreePolicy; // live follow-parent cannot be flattened safely
    EffectPlan out;
    std::vector<std::string> ancestry;
    std::function<void(std::string, int, int, int, std::string, size_t)> visit;
    visit = [&](std::string path, int begin, int limit, int layer, std::string source, size_t offset) {
        if (!pvf.has(path) || ancestry.size() >= 12 || out.tracks.size() >= 256 ||
            std::find(ancestry.begin(), ancestry.end(), path) != ancestry.end()) {
            out.diagnostics.push_back({{"path", path}, {"source", source}, {"offset", offset},
                                       {"reason", "missing/ambiguous resource, recursion or instance limit"}});
            return;
        }
        const auto ani = assets.animation(path);
        if (ani->frames.empty()) {
            out.diagnostics.push_back({{"path", path}, {"reason", "empty animation"}}); return;
        }
        const int end = std::min(limit, begin + ani->duration);
        if (begin >= end) return;
        const auto parentIndex = out.tracks.size();
        out.tracks.push_back({path, source, "", offset, begin, end, layer, parentIndex == 0});
        const auto als = path + ".als";
        if (!pvf.has(als)) return;
        ancestry.push_back(path);
        struct Active { size_t first, last; int begin; };
        std::map<std::string, std::string> declarations;
        std::map<std::string, Active> active;
        const auto script = pvf.script(als);
        auto frameTime = [&](int frame) {
            int time = 0;
            for (int f = 0; f < frame && f < int(ani->frames.size()); ++f) time += ani->frames[f].duration;
            return time;
        };
        // Native ALS parsing resolves the complete use-animation table before
        // executing frame commands (1099C00 -> 10A2420, then 109B550). Keep
        // declaration order in Script, but allow an event before its binding.
        for (const auto &f : script.fields) {
            const auto &v = f.values;
            if (f.tag == "[use animation]" && v.size() >= 2 && v[0].is_string() && v[1].is_string()) {
                declarations[normalize(v[1].get<std::string>())] = effectResource(pvf, als, v[0].get<std::string>());
            }
        }
        for (const auto &f : script.fields) {
            const auto &v = f.values;
            if (f.tag == "[use animation]" || f.tag.rfind("[/", 0) == 0) continue;
            if (f.tag != "[add]" && f.tag != "[remove]") {
                out.diagnostics.push_back({{"path", als}, {"offset", f.offset}, {"tag", f.tag}, {"values", v},
                    {"reason", "ALS command requires live instance semantics; not compiled by bounded effect plan"}});
                continue;
            }
            if (v.size() < 3 || !v[0].is_number_integer() || !v[1].is_number_integer() || !v[2].is_string()) {
                out.diagnostics.push_back({{"path", als}, {"offset", f.offset}, {"reason", "unknown ALS event"}}); continue;
            }
            const int frame = v[0].get<int>();
            if (frame < 0 || frame >= int(ani->frames.size())) {
                out.diagnostics.push_back({{"path", als}, {"offset", f.offset}, {"frame", frame},
                                           {"reason", "unsupported ALS frame"}}); continue;
            }
            const int time = begin + frameTime(frame);
            const auto instance = normalize(v[2].get<std::string>());
            if (f.tag == "[remove]") {
                const auto old = active.find(instance);
                if (old != active.end()) {
                    for (size_t i = old->second.first; i < old->second.last; ++i)
                        out.tracks[i].end = std::min(out.tracks[i].end, time);
                    active.erase(old);
                }
                continue;
            }
            const auto declaration = declarations.find(instance);
            if (declaration == declarations.end() || declaration->second.empty()) {
                out.diagnostics.push_back({{"path", als}, {"offset", f.offset}, {"instance", instance},
                                           {"reason", "undeclared/missing/ambiguous ALS resource"}}); continue;
            }
            const size_t first = out.tracks.size();
            visit(declaration->second, time, end, layer + v[1].get<int>(), als, f.offset);
            for (size_t i = first; i < out.tracks.size(); ++i) out.tracks[i].instance = instance;
            active[instance] = {first, out.tracks.size(), time};
        }
        ancestry.pop_back();
    };
    visit(normalize(animation), 0, 0x3fffffff, 0, normalize(animation), 0);
    return out;
}
EffectPlan objectEffectPlan(Pvf &pvf, Assets &assets, const std::string &object) {
    EffectPlan out;
    const auto script = pvf.script(object);
    for (const auto &f : script.fields) {
        if (f.tag != "[basic motion]" && f.tag != "[add object effect]") continue;
        const auto &v = f.values;
        if (v.empty() || !v[0].is_string()) continue;
        const auto path = effectResource(pvf, object, v[0].get<std::string>());
        if (path.empty()) {
            out.diagnostics.push_back({{"path", object}, {"offset", f.offset}, {"reference", v[0]},
                                       {"reason", "missing/ambiguous object motion"}}); continue;
        }
        auto child = animationEffectPlan(pvf, assets, path);
        const int layer = f.tag == "[add object effect]" && v.size() > 1 && v[1].is_number_integer() ? v[1].get<int>() : 0;
        for (auto track : child.tracks) {
            track.layer += layer;
            track.primary = f.tag == "[basic motion]" && track.primary;
            if (track.source == path) { track.source = object; track.sourceOffset = f.offset; }
            out.tracks.push_back(std::move(track));
        }
        for (const auto &diagnostic : child.diagnostics) out.diagnostics.push_back(diagnostic);
    }
    return out;
}
} // namespace dnf
