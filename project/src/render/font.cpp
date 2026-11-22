#include "dnf/font.hpp"
#ifdef _WIN32
#include <windows.h>
#include <cstring>
#include <map>

namespace dnf {
namespace {
uint16_t big16(const Bytes &b, size_t at) { return uint16_t((uint16_t(b[at]) << 8) | b[at + 1]); }
uint32_t big32(const Bytes &b, size_t at) { return (uint32_t(big16(b, at)) << 16) | big16(b, at + 2); }
bool tableRange(const Bytes &b, const char *name, size_t &offset, size_t &length) {
    if (b.size() < 12) return false;
    for (size_t i = 0; i < big16(b, 4); ++i) {
        const size_t at = 12 + i * 16;
        if (at + 16 > b.size()) return false;
        if (std::memcmp(b.data() + at, name, 4)) continue;
        offset = big32(b, at + 8); length = big32(b, at + 12);
        return offset <= b.size() && length <= b.size() - offset;
    }
    return false;
}
bool privateName(Bytes &b) {
    // This client's file is named msjh.ttf but calls itself FangSong. A host
    // Windows installation can have another FangSong version. An equal-length
    // alias in an ephemeral memory copy removes that family-name collision.
    // The original bytes and all glyph/hinting/metric tables remain untouched.
    size_t table = 0, length = 0;
    if (!tableRange(b, "name", table, length) || length < 6) return false;
    const size_t strings = table + big16(b, table + 4);
    bool renamed = false;
    for (size_t i = 0; i < big16(b, table + 2); ++i) {
        size_t at = table + 6 + i * 12;
        if (at + 12 > table + length) return false;
        const auto id = big16(b, at + 6), n = big16(b, at + 8);
        size_t start = strings + big16(b, at + 10);
        if (start > table + length || n > table + length - start) return false;
        if (id != 1 && id != 4 && id != 6) continue;
        const char *from = "FangSong", *to = "DNFSrcUI";
        if (n == 8 && !std::memcmp(b.data() + start, from, 8)) {
            std::memcpy(b.data() + start, to, 8); renamed = true;
        } else if (n == 16) {
            bool same = true;
            for (int k = 0; k < 8; ++k)
                if (b[start + 2 * k] || b[start + 2 * k + 1] != uint8_t(from[k])) same = false;
            if (same) {
                for (int k = 0; k < 8; ++k) b[start + 2 * k + 1] = uint8_t(to[k]);
                renamed = true;
            }
        }
    }
    return renamed;
}
std::wstring wideText(const std::string &s) {
    int count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), int(s.size()), nullptr, 0);
    if (!count && !s.empty()) return {};
    std::wstring out(size_t(count), 0);
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), int(s.size()), out.data(), count);
    return out;
}
bool sameTable(HDC dc, const Bytes &source, const char *name) {
    size_t offset = 0, length = 0;
    if (!tableRange(source, name, offset, length)) return false;
    DWORD tag = uint8_t(name[0]) | (DWORD(uint8_t(name[1])) << 8) |
                (DWORD(uint8_t(name[2])) << 16) | (DWORD(uint8_t(name[3])) << 24);
    if (GetFontData(dc, tag, 0, nullptr, 0) != length) return false;
    Bytes actual(length);
    return GetFontData(dc, tag, 0, actual.data(), DWORD(length)) == length &&
           std::equal(actual.begin(), actual.end(), source.begin() + offset);
}
} // namespace
struct HintedFont::State {
    Bytes memory;
    HANDLE resource = nullptr;
    HDC dc = nullptr;
    HGDIOBJ initialFont = nullptr;
    std::map<int, HFONT> fonts;
    bool verified = false;
    HFONT select(int size) {
        if (!dc || !resource || size <= 0) return nullptr;
        auto it = fonts.find(size);
        if (it == fonts.end()) {
            HFONT font = CreateFontW(-size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                GB2312_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY, DEFAULT_PITCH, L"DNFSrcUI");
            if (!font) return nullptr;
            it = fonts.emplace(size, font).first;
        }
        SelectObject(dc, it->second);
        return it->second;
    }
    ~State() {
        if (dc && initialFont) SelectObject(dc, initialFont);
        for (const auto &font : fonts) DeleteObject(font.second);
        if (dc) DeleteDC(dc);
        if (resource) RemoveFontMemResourceEx(resource);
    }
};
HintedFont::HintedFont(const Bytes &source) : state_(std::make_unique<State>()) {
    state_->memory = source;
    if (!privateName(state_->memory)) return;
    DWORD count = 0;
    state_->resource = AddFontMemResourceEx(state_->memory.data(), DWORD(state_->memory.size()), nullptr, &count);
    if (!state_->resource) return;
    state_->dc = CreateCompatibleDC(nullptr);
    if (!state_->dc) return;
    state_->initialFont = GetCurrentObject(state_->dc, OBJ_FONT);
    if (!state_->select(14)) return;
    // Fail back to the exact source's portable rasterizer if Windows selects
    // any substitute. A matching family name alone is not sufficient evidence.
    state_->verified = true;
    for (const auto name : {"glyf", "loca", "cmap", "hmtx", "hhea", "fpgm", "prep", "cvt "})
        if (!sameTable(state_->dc, source, name)) state_->verified = false;
    SetBkMode(state_->dc, TRANSPARENT);
    SetTextColor(state_->dc, RGB(255, 255, 255));
    SetTextAlign(state_->dc, TA_LEFT | TA_TOP | TA_NOUPDATECP);
}
HintedFont::~HintedFont() = default;
bool HintedFont::available() const { return state_->verified; }
int HintedFont::width(const std::string &s, int size) {
    if (!available() || !state_->select(size)) return -1;
    auto text = wideText(s);
    if (text.empty() && !s.empty()) return -1;
    SIZE extent{};
    return GetTextExtentPoint32W(state_->dc, text.data(), int(text.size()), &extent) ? extent.cx : -1;
}
bool HintedFont::mask(const std::string &s, int size, int pad, FontMask &out) {
    int advance = width(s, size);
    if (advance < 0) return false;
    auto text = wideText(s);
    TEXTMETRICW metrics{};
    if (!GetTextMetricsW(state_->dc, &metrics)) return false;
    const int w = advance + pad * 2 + 1, h = metrics.tmHeight + pad * 2 + 2;
    BITMAPINFO bitmap{};
    bitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap.bmiHeader.biWidth = w; bitmap.bmiHeader.biHeight = -h;
    bitmap.bmiHeader.biPlanes = 1; bitmap.bmiHeader.biBitCount = 32;
    bitmap.bmiHeader.biCompression = BI_RGB;
    void *pixels = nullptr;
    HBITMAP dib = CreateDIBSection(state_->dc, &bitmap, DIB_RGB_COLORS, &pixels, nullptr, 0);
    if (!dib || !pixels) { if (dib) DeleteObject(dib); return false; }
    HGDIOBJ old = SelectObject(state_->dc, dib);
    std::memset(pixels, 0, size_t(w) * h * 4);
    const bool ok = TextOutW(state_->dc, pad, pad, text.data(), int(text.size())) != FALSE;
    GdiFlush();
    if (ok) {
        out.width = w; out.height = h; out.advance = advance;
        out.coverage.resize(size_t(w) * h);
        const auto *bgra = static_cast<const uint8_t *>(pixels);
        for (size_t i = 0; i < out.coverage.size(); ++i) out.coverage[i] = bgra[i * 4];
    }
    SelectObject(state_->dc, old); DeleteObject(dib);
    return ok;
}
} // namespace dnf
#else
namespace dnf {
struct HintedFont::State {};
HintedFont::HintedFont(const Bytes &) : state_(std::make_unique<State>()) {}
HintedFont::~HintedFont() = default;
bool HintedFont::available() const { return false; }
bool HintedFont::mask(const std::string &, int, int, FontMask &) { return false; }
int HintedFont::width(const std::string &, int) { return -1; }
} // namespace dnf
#endif
