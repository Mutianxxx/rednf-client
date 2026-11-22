#include "dnf/hud_source.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
int integer(const Json &value, const std::string &context) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max())))
        throw std::runtime_error("HUD source requires an integer: " + context);
    const auto number = value.get<int64_t>();
    if (number < std::numeric_limits<int>::min() || number > std::numeric_limits<int>::max())
        throw std::runtime_error("HUD source integer out of range: " + context);
    return int(number);
}
size_t count(const Json &values, size_t &cursor, const std::string &context) {
    if (cursor >= values.size()) throw std::runtime_error("HUD source missing parameter count: " + context);
    const int result = integer(values[cursor++], context);
    if (result < 0 || size_t(result) > values.size() - cursor)
        throw std::runtime_error("HUD source parameter count exceeds its record: " + context);
    return size_t(result);
}
} // namespace

HudSourceLayout readHudSourceLayout(Script source) {
    HudSourceLayout result;
    result.source = std::move(source);
    bool open = false;
    for (size_t ordinal = 0; ordinal < result.source.fields.size(); ++ordinal) {
        const auto &field = result.source.fields[ordinal];
        const auto tag = normalize(field.tag);
        if (tag == "[/ui controls]") {
            if (!open || !field.values.empty()) throw std::runtime_error("HUD source unmatched control end");
            open = false;
            continue;
        }
        if (tag != "[ui controls]") continue; // Unknown nested fields stay lossless in source.
        if (open) throw std::runtime_error("HUD source nested or unclosed control");
        open = true;
        const auto &values = field.values;
        const auto context = result.source.path + ":" + std::to_string(field.offset);
        if (values.size() < 6 || !values[0].is_string() || !values[1].is_string() ||
            !values[2].is_number() || !values[3].is_number())
            throw std::runtime_error("HUD source malformed control header: " + context);
        HudSourceControl control;
        control.type = values[0].get<std::string>(); control.name = values[1].get<std::string>();
        control.x = values[2].get<double>(); control.y = values[3].get<double>();
        control.offset = field.offset; control.ordinal = ordinal;
        if (!std::isfinite(control.x) || !std::isfinite(control.y))
            throw std::runtime_error("HUD source nonfinite control position: " + context);
        size_t cursor = 4;
        const auto strings = count(values, cursor, context);
        for (size_t i = 0; i < strings; ++i) {
            if (!values[cursor].is_string()) throw std::runtime_error("HUD source nonstring parameter: " + context);
            control.strings.push_back(values[cursor++].get<std::string>());
        }
        const auto integers = count(values, cursor, context);
        for (size_t i = 0; i < integers; ++i) control.integers.push_back(integer(values[cursor++], context));
        if (cursor != values.size()) throw std::runtime_error("HUD source uncounted parameters: " + context);
        result.controls.push_back(std::move(control));
    }
    if (open) throw std::runtime_error("HUD source unterminated control");
    return result;
}

const HudSourceControl &HudSourceLayout::require(const std::string &name, const std::string &type,
                                               size_t strings, size_t integers) const {
    const HudSourceControl *result = nullptr;
    for (const auto &control : controls) if (control.name == name) {
        if (result) throw std::runtime_error("HUD source ambiguous named binding: " + name);
        result = &control;
    }
    if (!result || result->type != type || result->strings.size() != strings || result->integers.size() != integers)
        throw std::runtime_error("HUD source unsupported named binding: " + source.path + ":" + name);
    return *result;
}
Json HudSourceControl::snapshot() const {
    return {{"type", type}, {"name", name}, {"x", x}, {"y", y}, {"ordinal", ordinal}, {"offset", offset},
        {"strings", strings}, {"integers", integers}};
}
Json HudSourceLayout::snapshot() const {
    Json decoded = Json::array(), fields = Json::array();
    for (const auto &control : controls) decoded.push_back(control.snapshot());
    for (const auto &field : source.fields)
        fields.push_back({{"tag", field.tag}, {"values", field.values}, {"offset", field.offset}});
    return {{"path", source.path}, {"provenance", source.source}, {"raw_bytes", source.rawBytes},
        {"tokens", source.tokens}, {"fields", fields}, {"controls", decoded},
        {"scope", "count-prefixed source envelope; native UI event and animation semantics not recovered"}};
}
} // namespace dnf
