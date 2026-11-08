#include "dnf/audio_catalog.hpp"
#include <cctype>
#include <limits>
#include <set>

namespace dnf {
namespace {
std::string hex(const std::string &s) {
    static const char digits[] = "0123456789abcdef";
    std::string out; out.reserve(s.size() * 2);
    for (unsigned char c : s) { out += digits[c >> 4]; out += digits[c & 15]; }
    return out;
}
std::string xmlText(std::string s) {
    if (std::any_of(s.begin(), s.end(), [](unsigned char c) { return c >= 128; })) s = gbk(s);
    for (auto pair : {std::pair<const char *, const char *>{"&quot;", "\""}, {"&apos;", "'"},
                      {"&lt;", "<"}, {"&gt;", ">"}, {"&amp;", "&"}}) {
        size_t at = 0;
        while ((at = s.find(pair.first, at)) != s.npos) {
            s.replace(at, std::strlen(pair.first), pair.second); at += std::strlen(pair.second);
        }
    }
    return s;
}
Json attributes(const std::string &xml, size_t begin, size_t end, Json &issues) {
    Json result = Json::array();
    size_t at = begin;
    while (at < end) {
        while (at < end && std::isspace(static_cast<unsigned char>(xml[at]))) ++at;
        if (at == end || xml[at] == '/') break;
        size_t start = at;
        while (at < end && !std::isspace(static_cast<unsigned char>(xml[at])) && xml[at] != '=') ++at;
        std::string name = xml.substr(start, at - start);
        while (at < end && std::isspace(static_cast<unsigned char>(xml[at]))) ++at;
        if (at == end || xml[at++] != '=') { issues.push_back({{"kind", "invalid XML attribute"}, {"offset", start}}); break; }
        while (at < end && std::isspace(static_cast<unsigned char>(xml[at]))) ++at;
        if (at == end || (xml[at] != '\'' && xml[at] != '"')) { issues.push_back({{"kind", "unquoted XML attribute"}, {"offset", start}}); break; }
        char quote = xml[at++]; size_t valueBegin = at;
        while (at < end && xml[at] != quote) ++at;
        if (at == end) { issues.push_back({{"kind", "unterminated XML attribute"}, {"offset", start}}); break; }
        auto raw = xml.substr(valueBegin, at - valueBegin); ++at;
        result.push_back({{"name", name}, {"value", xmlText(raw)}, {"offset", start},
                          {"value_offset", valueBegin}, {"quote", std::string(1, quote)}, {"raw_hex", hex(raw)}});
    }
    return result;
}
std::string attribute(const Json &attrs, const char *name) {
    for (const auto &a : attrs) if (a["name"] == name) return a["value"].get<std::string>();
    return {};
}
}
const char *audioKindName(AudioKind kind) {
    switch (kind) {
    case AudioKind::Music: return "MUSIC";
    case AudioKind::Ambient: return "AMBIENT";
    case AudioKind::Effect: return "EFFECT";
    case AudioKind::Random: return "RANDOM";
    default: return "UNKNOWN";
    }
}
Json AudioScenePlan::snapshot() const {
    return {{"source_ids", sourceIds}, {"music", music}, {"ambient", ambient}, {"effects", effects}, {"issues", issues}};
}
AudioCatalog::AudioCatalog(Bytes source, std::string sourcePath)
    : source_(std::move(source)), sourcePath_(std::move(sourcePath)) {
    std::string xml(source_.begin(), source_.end());
    size_t at = 0, random = size_t(-1);
    while ((at = xml.find('<', at)) != xml.npos) {
        size_t begin = at;
        if (xml.compare(at, 4, "<!--") == 0) {
            auto end = xml.find("-->", at + 4);
            if (end == xml.npos) { issues_.push_back({{"kind", "unterminated XML comment"}, {"offset", at}}); break; }
            at = end + 3; continue;
        }
        bool quoted = false; char quote = 0; size_t end = at + 1;
        for (; end < xml.size(); ++end) {
            char c = xml[end];
            if (quoted) { if (c == quote) quoted = false; }
            else if (c == '\'' || c == '"') { quoted = true; quote = c; }
            else if (c == '>') break;
        }
        if (end == xml.size()) { issues_.push_back({{"kind", "unterminated XML tag"}, {"offset", at}}); break; }
        at = begin + 1; bool closing = at < end && xml[at] == '/'; if (closing) ++at;
        size_t nameBegin = at;
        while (at < end && (std::isalnum(static_cast<unsigned char>(xml[at])) || xml[at] == '_')) ++at;
        auto tag = xml.substr(nameBegin, at - nameBegin);
        if (closing) {
            if (tag == "RANDOM" && random != size_t(-1)) { declarations_[random].endOffset = end + 1; random = size_t(-1); }
            at = end + 1; continue;
        }
        AudioKind kind = tag == "MUSIC" ? AudioKind::Music : tag == "AMBIENT" ? AudioKind::Ambient :
                         tag == "EFFECT" ? AudioKind::Effect : tag == "RANDOM" ? AudioKind::Random : AudioKind::Unknown;
        if (kind != AudioKind::Unknown || (tag == "ITEM" && random != size_t(-1))) {
            auto attrs = attributes(xml, at, end, issues_);
            auto raw = hex(xml.substr(begin, end + 1 - begin));
            if (tag == "ITEM") {
                AudioRandomItem item; item.id = attribute(attrs, "TAG"); item.offset = begin; item.rawHex = raw; item.attributes = attrs;
                auto weight = attribute(attrs, "PROB");
                try {
                    size_t consumed = 0; long long n = std::stoll(weight, &consumed);
                    if (consumed != weight.size() || n < 0 || n > std::numeric_limits<int>::max()) throw std::runtime_error("weight");
                    item.weight = int(n);
                } catch (...) { issues_.push_back({{"kind", "invalid RANDOM weight"}, {"offset", begin}, {"literal", weight}}); }
                declarations_[random].items.push_back(std::move(item));
            } else {
                AudioDeclaration d; d.kind = kind; d.id = attribute(attrs, "ID"); d.fileLiteral = attribute(attrs, "FILE");
                d.file = d.fileLiteral.empty() ? "" : normalize(d.fileLiteral); d.offset = begin; d.endOffset = end + 1;
                d.attributes = std::move(attrs); d.rawHex = std::move(raw);
                if (d.id.empty()) issues_.push_back({{"kind", "audio declaration without ID"}, {"offset", begin}});
                else byId_[d.id].push_back(declarations_.size());
                declarations_.push_back(std::move(d));
                if (kind == AudioKind::Random) random = declarations_.size() - 1;
            }
        }
        at = end + 1;
    }
}
std::vector<const AudioDeclaration *> AudioCatalog::find(const std::string &id) const {
    std::vector<const AudioDeclaration *> found;
    auto it = byId_.find(id);
    if (it != byId_.end()) for (auto index : it->second) found.push_back(&declarations_[index]);
    return found;
}
AudioKind AudioCatalog::kind(const std::string &id, std::vector<std::string> &stack) const {
    if (stack.size() >= 16 || std::find(stack.begin(), stack.end(), id) != stack.end()) return AudioKind::Unknown;
    auto entries = find(id); if (entries.empty()) return AudioKind::Unknown;
    stack.push_back(id); AudioKind found = AudioKind::Unknown;
    for (auto entry : entries) {
        auto k = entry->kind;
        if (k == AudioKind::Random) {
            k = AudioKind::Unknown;
            for (const auto &item : entry->items) if (item.weight > 0) {
                auto child = kind(item.id, stack);
                if (child == AudioKind::Unknown || (k != AudioKind::Unknown && child != k)) { stack.pop_back(); return AudioKind::Unknown; }
                k = child;
            }
        }
        if (k == AudioKind::Unknown || (found != AudioKind::Unknown && k != found)) { stack.pop_back(); return AudioKind::Unknown; }
        found = k;
    }
    stack.pop_back(); return found;
}
AudioKind AudioCatalog::kind(const std::string &id) const { std::vector<std::string> stack; return kind(id, stack); }
AudioScenePlan AudioCatalog::scene(const Json &ids) const {
    AudioScenePlan plan;
    if (!ids.is_array()) { plan.issues.push_back({{"kind", "scene sound list is not an array"}}); return plan; }
    plan.sourceIds = ids;
    std::set<std::string> seen;
    for (const auto &value : ids) {
        if (!value.is_string()) { plan.issues.push_back({{"kind", "non-string scene sound ID"}, {"value", value}}); continue; }
        auto id = value.get<std::string>(); if (!seen.insert(id).second) continue;
        switch (kind(id)) {
        case AudioKind::Music:
            if (plan.music.empty()) plan.music = id;
            else plan.issues.push_back({{"kind", "multiple scene music IDs; first retained"}, {"retained", plan.music}, {"unused", id}});
            break;
        case AudioKind::Ambient: plan.ambient.push_back(id); break;
        case AudioKind::Effect: plan.effects.push_back(id); break;
        default: plan.issues.push_back({{"kind", "unresolved or mixed-kind scene sound ID"}, {"id", id}}); break;
        }
    }
    return plan;
}
Json AudioCatalog::snapshot(bool includeSource) const {
    Json rows = Json::array();
    for (const auto &d : declarations_) {
        Json items = Json::array();
        for (const auto &i : d.items) items.push_back({{"id", i.id}, {"weight", i.weight}, {"offset", i.offset}, {"attributes", i.attributes}, {"raw_hex", i.rawHex}});
        rows.push_back({{"kind", audioKindName(d.kind)}, {"id", d.id}, {"file", d.file}, {"file_literal", d.fileLiteral},
                        {"offset", d.offset}, {"end_offset", d.endOffset}, {"attributes", d.attributes}, {"raw_tag_hex", d.rawHex}, {"items", items}});
    }
    Json result = {{"source", sourcePath_}, {"source_bytes", source_.size()}, {"declarations", rows}, {"issues", issues_},
                   {"unconsumed_source_attributes", {"VOLUME_ADJUST", "PRIORITY", "LOOP_DELAY"}},
                   {"policy", "source category routes voices; no native volume/priority/delay formula claimed"}};
    if (includeSource) result["source_bytes_hex"] = hex(std::string(source_.begin(), source_.end()));
    return result;
}
} // namespace dnf
