#include "dnf/appearance.hpp"
#include "dnf/equipment_motion.hpp"
#include <iomanip>
#include <set>
#include <sstream>
#include <stdexcept>
namespace dnf {
namespace {
std::string padded(int value, int width) {
    std::ostringstream out;
    out << std::setfill('0') << std::setw(width) << value;
    return out.str();
}
}
AppearancePart parseEquipmentAppearance(const Script &source, const std::string &job) {
    AppearancePart result;
    result.slot = source.text("[equipment type]");
    result.job = job;
    result.source = source;
    std::string animationJob;
    std::array<int, 2> variation{0, 0};
    AppearanceLayer *pending = nullptr;
    for (const auto &field : source.fields) {
        const auto &v = field.values;
        if (field.tag == "[animation job]") {
            animationJob = v.empty() || !v[0].is_string() ? "" : v[0].get<std::string>();
            variation = {0, 0};
            pending = nullptr;
        } else if (field.tag == "[variation]" && v.size() >= 2 && v[0].is_number_integer() && v[1].is_number_integer()) {
            variation = {v[0].get<int>(), v[1].get<int>()};
            pending = nullptr;
            if (animationJob.empty() || animationJob == job) result.variation = variation;
        } else if (field.tag == "[layer variation]") {
            pending = nullptr;
            if ((animationJob.empty() || animationJob == job) && v.size() >= 2 && v[0].is_number_integer() && v[1].is_string()) {
                AppearanceLayer layer;
                layer.order = v[0]; layer.name = normalize(v[1]); layer.variation = variation;
                layer.slot = result.slot; layer.sourcePath = source.path; layer.sourceOffset = field.offset;
                layer.animationDirectory = normalize((std::filesystem::path(source.path).parent_path() / layer.name).generic_string());
                result.layers.push_back(std::move(layer));
                pending = &result.layers.back();
            }
        } else if (field.tag == "[equipment ani script]" && pending && !v.empty() && v[0].is_string()) {
            pending->animationScript = normalize(v[0]);
        } else if (field.tag == "[hide equipment]") {
            for (const auto &value : v) if (value.is_string()) result.hideEquipment.push_back(value.get<std::string>());
        } else if (field.tag == "[hide layer]") {
            for (const auto &value : v) if (value.is_number_integer()) result.hideLayers.push_back(value.get<int>());
        }
    }
    return result;
}
bool applyEquipmentAppearance(CharacterAppearance &appearance, const Script &source, const std::string &job) {
    auto part = parseEquipmentAppearance(source, job);
    if (part.slot.empty() || (part.layers.empty() && part.slot != "[skin avatar]")) return false;
    appearance.parts[part.slot] = std::move(part);
    return true;
}
CharacterAppearance defaultCharacterAppearance(Pvf &pvf, const CharacterCatalog &catalog,
                                               CharacterIdentity identity) {
    CharacterAppearance result;
    result.identity = identity;
    const auto &character = catalog.at(identity.jobId);
    const auto sources = catalog.defaultAppearanceSources(identity.jobId);
    result.job = character.job;
    result.issues = sources.issues;
    std::map<std::string, std::map<size_t, size_t>> occurrences;
    for (const auto &resource : character.resources) {
        const auto &tag = resource.tag;
        if (!(tag.size() >= 8 && tag.compare(tag.size() - 8, 8, " motion]") == 0) &&
            tag.rfind("[throw motion ", 0) != 0 && tag.rfind("[damage motion ", 0) != 0) continue;
        auto &fields = occurrences[normalize(tag)];
        const auto occurrence = fields.emplace(resource.fieldOffset, fields.size()).first->second;
        result.bodyMotions.push_back({resource, occurrence});
    }
    for (const auto &entry : sources.equipment) {
        if (entry.equipmentId < 0) continue;
        if (!entry.registered || !entry.exists || !entry.hasAnimationJob) continue; // source issues retained above
        if (!applyEquipmentAppearance(result, entry.source.script, character.job))
            result.issues.push_back({{"kind", "default_equipment_has_no_supported_appearance"},
                {"equipment_id", entry.equipmentId}, {"path", entry.path}});
    }
    bindEquipmentMotions(pvf, result);
    return result;
}
void bindEquipmentMotions(Pvf &pvf, CharacterAppearance &appearance) {
    std::map<std::string, std::shared_ptr<const EquipmentMotionDefinition>> loaded;
    for (auto &part : appearance.parts) for (auto &layer : part.second.layers) {
        layer.motionDefinition.reset();
        const auto key = layer.animationScript + "|" + layer.animationDirectory;
        const auto previous = loaded.find(key);
        if (previous != loaded.end()) { layer.motionDefinition = previous->second; continue; }
        if (layer.animationScript.empty() || !pvf.has(layer.animationScript)) {
            appearance.issues.push_back({{"kind", "missing_equipment_motion_script"},
                {"equipment", layer.sourcePath}, {"offset", layer.sourceOffset}, {"path", layer.animationScript}});
            continue;
        }
        auto motions = std::make_shared<EquipmentMotionDefinition>(
            loadEquipmentMotion(pvf, layer.animationScript, layer.animationDirectory));
        layer.motionDefinition = motions;
        loaded.emplace(key, std::move(motions));
    }
}
const AppearanceBodyMotion *appearanceBodyMotion(const CharacterAppearance &appearance,
                                                 const std::string &pathOrStem) {
    const auto wanted = normalize(pathOrStem);
    const bool fullPath = wanted.find('/') != std::string::npos;
    const AppearanceBodyMotion *result = nullptr;
    for (const auto &motion : appearance.bodyMotions) {
        const auto &source = motion.resource;
        const auto candidate = fullPath ? normalize(source.path) :
            normalize(std::filesystem::u8path(source.path).stem().u8string());
        if (source.literal.empty() || !source.exists || candidate != wanted) continue;
        // Identical source path can occupy multiple slots, which are allowed
        // only when every visible LAY resolves them identically.
        if (result) for (const auto &layer : appearance.orderedLayers())
            if (appearanceLayerMotion(layer, *result) != appearanceLayerMotion(layer, motion))
                throw std::runtime_error("Ambiguous body-to-equipment motion: " + wanted);
        if (!result) result = &motion;
    }
    return result;
}
std::string appearanceLayerMotion(const AppearanceLayer &layer, const AppearanceBodyMotion &body) {
    if (!layer.motionDefinition) return {};
    const auto *motion = resolveEquipmentMotion(*layer.motionDefinition, body.resource, body.occurrence);
    return motion ? motion->path : std::string{};
}
int legacyWeaponSubtype(int category) {
    // Compatibility with existing save/controller category numbers only.
    static constexpr std::array<int, 4> subtypes{0, 1, 3, 2};
    if (category < 0 || size_t(category) >= subtypes.size()) throw std::invalid_argument("Unsupported legacy weapon category");
    return subtypes[size_t(category)];
}
CharacterAppearance diagnosticWeaponAppearance(Pvf &pvf, const CharacterCatalog &catalog,
                                               CharacterIdentity identity, int category) {
    auto result = defaultCharacterAppearance(pvf, catalog, identity);
    const auto &character = catalog.at(identity.jobId);
    const Field *table = nullptr;
    for (const auto &field : character.settings.script.fields) {
        if (field.tag != "[key value index]" || field.values.empty() || !field.values[0].is_string()) continue;
        if (field.values[0] != "weaponSubTypeIndex" && field.values[0] != "defaultWeaponBySubType") continue;
        if (table) throw std::runtime_error("Ambiguous default weapon source table");
        table = &field;
    }
    if (!table || table->values.size() < 2 || (table->values.size() - 2) % 2)
        throw std::runtime_error("Missing or malformed default weapon source table");
    const auto &values = table->values;
    if (!values[1].is_number_integer()) throw std::runtime_error("Malformed default weapon fallback");
    int equipmentId = -1; // The first integer's missing-key fallback is not proven.
    std::set<int> subtypes;
    for (size_t index = 2; index + 1 < values.size(); index += 2) {
        if (!values[index].is_number_integer() || !values[index + 1].is_number_integer())
            throw std::runtime_error("Malformed default weapon source pair");
        const int subtype = values[index].get<int>();
        if (!subtypes.insert(subtype).second) throw std::runtime_error("Repeated default weapon subtype");
        if (subtype == legacyWeaponSubtype(category)) equipmentId = values[index + 1].get<int>();
    }
    if (equipmentId < 0) throw std::runtime_error("Unmapped default weapon subtype");
    const auto equipment = catalog.equipment(equipmentId);
    if (equipment.script.text("[equipment type]") != "[weapon]")
        throw std::runtime_error("Default weapon table refers to a non-weapon");
    if (!applyEquipmentAppearance(result, equipment.script, character.job))
        throw std::runtime_error("Default weapon has no current-job appearance");
    bindEquipmentMotions(pvf, result);
    return result;
}
std::vector<AppearanceLayer> CharacterAppearance::orderedLayers() const {
    std::set<int> hiddenLayers;
    std::map<std::string, std::set<int>> hiddenEquipment;
    for (const auto &entry : parts) {
        const auto &part = entry.second;
        // The sample explicitly requires both the hidden equipment type and
        // layer numbers. Do not erase all hair when only one split is hidden.
        if (part.hideEquipment.empty()) hiddenLayers.insert(part.hideLayers.begin(), part.hideLayers.end());
        for (const auto &slot : part.hideEquipment)
            hiddenEquipment[slot].insert(part.hideLayers.begin(), part.hideLayers.end());
    }
    std::vector<AppearanceLayer> result;
    for (const auto &entry : parts) for (const auto &layer : entry.second.layers) {
        auto hidden = hiddenEquipment.find(layer.slot);
        if (hiddenLayers.count(layer.order) ||
            (hidden != hiddenEquipment.end() && hidden->second.count(layer.order))) continue;
        result.push_back(layer);
    }
    std::stable_sort(result.begin(), result.end(), [](const auto &a, const auto &b) { return a.order < b.order; });
    return result;
}
int CharacterAppearance::bodyVariation() const {
    auto skin = parts.find("[skin avatar]");
    return skin == parts.end() ? 0 : skin->second.variation[1];
}
std::string appearanceImage(std::string pattern, const std::array<int, 2> &variation, bool body) {
    // Most costume/weapon IMG names have %02d%02d. Width is a minimum, so
    // source model 123 correctly becomes 12300 rather than being truncated.
    size_t from = 0;
    int parameter = 0;
    while ((from = pattern.find('%', from)) != std::string::npos) {
        size_t end = from + 1;
        int width = 0;
        if (end < pattern.size() && pattern[end] == '0') {
            ++end;
            while (end < pattern.size() && pattern[end] >= '0' && pattern[end] <= '9')
                width = std::min(8, width * 10 + pattern[end++] - '0');
        }
        if (end >= pattern.size() || pattern[end] != 'd' || parameter >= 2) { ++from; continue; }
        const int value = body ? variation[1] : variation[parameter];
        auto replacement = padded(value, width);
        pattern.replace(from, end - from + 1, replacement);
        from += replacement.size(); ++parameter;
    }
    return normalize(pattern);
}
} // namespace dnf
