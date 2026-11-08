#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace dnf {
enum class TextInputField { None, CharacterName, MapQuery };
enum class TextInputKey { Return, Escape, Backspace, Delete, Left, Right, Home, End,
                          Up, Down, PageUp, PageDown, Space, Other, Count };
enum class TextInputIntent { None, Submit, Cancel, Up, Down, PageUp, PageDown };
struct TextInputRoute {
    bool consumed = false, changed = false;
    TextInputIntent intent = TextInputIntent::None;
};
struct TextInputPolicy {
    size_t maximumCodepoints = 16, maximumBytes = 64;
    size_t maximumCompositionCodepoints = 128, maximumCompositionBytes = 512;
    std::function<bool(uint32_t)> allows;
    static TextInputPolicy characterName(std::function<bool(uint32_t)> allows);
    static TextInputPolicy mapQuery();
};
// Pure portable UTF-8 editor. SDL/Win32, drawing, save/name rules and business
// transactions remain in the host. Carets/IME selection lengths are codepoints,
// never UTF-8 byte indices. Existing saved names need not pass this new editor.
class TextInputModel {
    TextInputField field_ = TextInputField::None;
    TextInputPolicy policy_;
    std::string text_, composition_, error_;
    size_t caret_ = 0, compositionCaret_ = 0, compositionSelection_ = 0;
    uint64_t revision_ = 0;
    bool focused_ = true, batchFence_ = false;
    std::array<bool,size_t(TextInputKey::Count)> down_{}, untilKeyUp_{};
    bool allowed(const std::vector<uint32_t> &) const;
    void clearComposition();
  public:
    // Throws only for an invalid policy/initial buffer. activate/deactivate are
    // scope changes; a pending transaction must deactivate the input owner.
    void activate(TextInputField,const std::string &initial,TextInputPolicy);
    void deactivate();
    void setFocused(bool);
    bool active() const { return focused_ && field_ != TextInputField::None; }
    TextInputField field() const { return field_; }
    bool focused() const { return focused_; }
    const std::string &text() const { return text_; }
    const std::string &composition() const { return composition_; }
    const std::string &error() const { return error_; }
    bool composing() const { return !composition_.empty(); }
    size_t caret() const { return caret_; }
    size_t compositionCaret() const { return compositionCaret_; }
    size_t compositionSelection() const { return compositionSelection_; }
    uint64_t revision() const { return revision_; }
    bool canSubmit() const;
    std::string beforeCaret() const;
    std::string afterCaret() const;

    // Host MUST pre-scan the main-window event batch before handling any key.
    // hasTextOrEditingEvents covers TEXTINPUT/TEXTEDITING/EXT even when empty.
    // This blocks both KEYDOWN-before-commit and commit-before-KEYDOWN order.
    // Protected keys involved in IME traffic stay fenced until their KEYUP.
    void beginEventBatch(bool hasTextOrEditingEvents);
    void endEventBatch() { batchFence_ = false; }
    bool commitUtf8(const std::string &);
    bool updateComposition(const std::string &,int start,int length);
    TextInputRoute keyDown(TextInputKey,bool repeat=false);
    void keyUp(TextInputKey);
};
// Rejects malformed sequences, overlong encodings, surrogate and >U+10FFFF.
// Throws invalid_argument, never emits replacement characters or partial UTF8.
std::vector<uint32_t> decodeTextInputUtf8(const std::string &);
} // namespace dnf
