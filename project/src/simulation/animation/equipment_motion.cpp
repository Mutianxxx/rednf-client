#include "dnf/equipment_motion.hpp"
#include <map>
#include <utility>

namespace dnf {
namespace {
bool motionTag(const std::string &tag) {
    if (tag.size() < 3 || tag[0] != '[' || tag[1] == '/') return false;
    return (tag.size() >= 8 && tag.compare(tag.size() - 8, 8, " motion]") == 0) ||
        tag.rfind("[throw motion ", 0) == 0 || tag.rfind("[damage motion ", 0) == 0;
}
bool layerZero(const Field &field) {
    return field.values.size() == 1 && field.values[0].is_number_integer() && field.values[0] == 0;
}
void issue(EquipmentMotionDefinition &definition, const EquipmentMotionBinding &binding,
           const char *kind) {
    definition.issues.push_back({{"kind", kind}, {"tag", binding.tag},
        {"field_ordinal", binding.fieldOrdinal}, {"field_offset", binding.fieldOffset},
        {"occurrence", binding.occurrence}, {"slot", binding.slot}, {"value", binding.value}});
}
} // namespace

EquipmentMotionDefinition parseEquipmentMotionSource(CharacterScript source,
    const std::string &animationDirectory) {
    EquipmentMotionDefinition result;
    result.source = std::move(source);
    result.animationDirectory = normalize(animationDirectory);
    const auto &fields = result.source.script.fields;
    for (size_t index = 0; index < fields.size(); ++index) {
        if (normalize(fields[index].tag) != "[layer]") continue;
        if (!result.layers.empty()) {
            result.layers.back().endField = index;
            result.layers.back().endOffset = fields[index].offset;
        }
        EquipmentMotionLayer layer;
        layer.field = fields[index];
        layer.ordinal = result.layers.size();
        layer.beginField = index;
        layer.endField = fields.size();
        layer.endOffset = result.source.bytes.size();
        result.layers.push_back(std::move(layer));
    }
    const bool supportedLayer = result.layers.size() == 1 && layerZero(result.layers[0].field);
    if (supportedLayer) result.layers[0].supported = true;
    else {
        result.issues.push_back({{"kind", "unsupported_layer_layout"},
            {"layer_count", result.layers.size()}, {"supported", "exactly one [LAYER] with integer 0"}});
        for (const auto &layer : result.layers)
            result.issues.push_back({{"kind", "preserved_unsupported_layer"},
                {"ordinal", layer.ordinal}, {"offset", layer.field.offset},
                {"values", layer.field.values}, {"begin_field", layer.beginField},
                {"end_field", layer.endField}, {"end_offset", layer.endOffset}});
    }
    std::map<std::string, size_t> occurrences;
    size_t currentLayer = std::numeric_limits<size_t>::max();
    for (size_t index = 0; index < fields.size(); ++index) {
        const auto &field = fields[index];
        const auto tag = normalize(field.tag);
        if (tag == "[layer]") {
            currentLayer = currentLayer == std::numeric_limits<size_t>::max() ? 0 : currentLayer + 1;
            continue;
        }
        if (!motionTag(tag)) continue;
        const size_t occurrence = occurrences[tag]++;
        for (size_t slot = 0; slot < field.values.size(); ++slot) {
            EquipmentMotionBinding binding;
            binding.tag = field.tag;
            binding.value = field.values[slot];
            binding.fieldOrdinal = index;
            binding.fieldOffset = field.offset;
            binding.slot = slot;
            binding.occurrence = occurrence;
            binding.layerOrdinal = currentLayer;
            if (binding.value.is_string()) binding.literal = binding.value.get<std::string>();
            if (!supportedLayer || currentLayer != 0) {
                issue(result, binding, "motion_outside_supported_layer");
            } else if (!binding.value.is_string()) {
                issue(result, binding, "non_string_motion_slot");
            } else if (binding.literal.empty()) {
                binding.status = EquipmentMotionStatus::Empty;
            } else {
                const auto percent = binding.literal.find('%');
                if (percent == std::string::npos || binding.literal.compare(percent, 2, "%s") != 0 ||
                    binding.literal.find('%', percent + 1) != std::string::npos) {
                    issue(result, binding, "unsupported_motion_template");
                } else if (result.animationDirectory.empty() || result.animationDirectory.find('%') != std::string::npos) {
                    issue(result, binding, "unsupported_animation_directory");
                } else {
                    auto path = binding.literal;
                    path.replace(percent, 2, result.animationDirectory);
                    binding.path = normalize(path);
                    binding.status = EquipmentMotionStatus::Resolved;
                }
            }
            result.bindings.push_back(std::move(binding));
        }
    }
    return result;
}

EquipmentMotionDefinition loadEquipmentMotion(Pvf &pvf, const std::string &layPath,
    const std::string &animationDirectory) {
    CharacterScript source;
    source.bytes = pvf.read(layPath);
    source.script = pvf.script(layPath);
    source.provenance = pvf.reads().at(normalize(layPath));
    auto result = parseEquipmentMotionSource(std::move(source), animationDirectory);
    for (auto &binding : result.bindings) {
        if (binding.status != EquipmentMotionStatus::Resolved) continue;
        binding.existenceChecked = true;
        binding.exists = pvf.has(binding.path);
        if (!binding.exists) {
            result.issues.push_back({{"kind", "missing_equipment_motion"},
                {"tag", binding.tag}, {"field_offset", binding.fieldOffset},
                {"occurrence", binding.occurrence}, {"slot", binding.slot},
                {"literal", binding.literal}, {"candidate_path", binding.path}});
            binding.path.clear();
            binding.status = EquipmentMotionStatus::Unsupported;
        }
    }
    return result;
}

const EquipmentMotionBinding *resolveEquipmentMotion(const EquipmentMotionDefinition &definition,
    const CharacterResource &bodyBinding, size_t occurrence) {
    const auto tag = normalize(bodyBinding.tag);
    const EquipmentMotionBinding *result = nullptr;
    for (const auto &binding : definition.bindings)
        if (normalize(binding.tag) == tag && binding.occurrence == occurrence && binding.slot == bodyBinding.valueIndex) {
            if (result) return nullptr; // A corrupted/ambiguous model cannot choose a winner.
            result = &binding;
        }
    return result;
}
} // namespace dnf
