#include "dnf/text_input.hpp"
#include "dnf/resources.hpp"
#include <stdexcept>

namespace dnf {
Json runTextInputTests() {
    Json checks=Json::array(),failures=Json::array();
    const auto check=[&](bool okay,const char *message) {
        checks.push_back({{"passed",okay},{"message",message}});if(!okay)failures.push_back(message);
    };
    const auto whitelist=[](uint32_t cp) {
        return cp>='a'&&cp<='z'||cp>='A'&&cp<='Z'||cp>='0'&&cp<='9'||cp>=0x4e00&&cp<=0x9fff;
    };
    TextInputModel input;input.activate(TextInputField::CharacterName,"",TextInputPolicy::characterName(whitelist));
    check(decodeTextInputUtf8("A中😀")==std::vector<uint32_t>({65,0x4e2d,0x1f600}),
        "UTF8 decoder preserves distinct ASCII/CJK/supplementary scalar values");
    for(const auto &bad:{std::string("\xc0\xaf",2),std::string("\xe0\x80\xaf",3),std::string("\xed\xa0\x80",3),
        std::string("\xf4\x90\x80\x80",4),std::string("\xe4\xb8",2),std::string("\x80",1),std::string("\xe4\x41\xad",3)}) {
        bool rejected=false;try{decodeTextInputUtf8(bad);}catch(const std::invalid_argument &){rejected=true;}
        check(rejected,"Malformed/overlong/surrogate/out-of-range/truncated UTF8 is rejected atomically");
    }
    input.beginEventBatch(true);check(input.commitUtf8("鬼剑A"),"Source-callback-approved multibyte name commits");
    input.endEventBatch();check(input.text()=="鬼剑A"&&input.caret()==3&&input.canSubmit(),
        "Name length and caret count codepoints rather than UTF8 bytes");
    input.keyDown(TextInputKey::Left);input.keyUp(TextInputKey::Left);
    input.keyDown(TextInputKey::Backspace);input.keyUp(TextInputKey::Backspace);
    check(input.text()=="鬼A"&&input.beforeCaret()=="鬼"&&input.afterCaret()=="A",
        "Backspace removes one complete Chinese codepoint at an interior caret");
    input.beginEventBatch(true);input.commitUtf8("中");input.endEventBatch();
    check(input.text()=="鬼中A"&&input.caret()==2,"Text commit inserts at the actual caret");
    input.keyDown(TextInputKey::Delete);input.keyUp(TextInputKey::Delete);
    check(input.text()=="鬼中","Forward Delete removes the next complete UTF8 codepoint");
    const auto valid=input.text();input.beginEventBatch(true);
    check(!input.commitUtf8("😀")&&input.text()==valid&&!input.error().empty(),
        "Current-name whitelist rejection is visible and preserves the previously valid buffer");
    check(!input.commitUtf8("\n")&&!input.commitUtf8(std::string("\0",1))&&input.text()==valid,
        "Control/newline/NUL never enter committed text");input.endEventBatch();

    input.activate(TextInputField::CharacterName,"",TextInputPolicy::characterName(whitelist));
    std::string sixteen;for(int i=0;i<16;++i)sixteen+="中";
    input.beginEventBatch(true);check(input.commitUtf8(sixteen),"Sixteen Chinese characters fit the declared16-codepoint64-byte policy");
    check(!input.commitUtf8("A")&&input.text()==sixteen,"Seventeenth codepoint rejects without truncating multibyte text");input.endEventBatch();
    input.activate(TextInputField::MapQuery,std::string(159,'a'),TextInputPolicy::mapQuery());input.beginEventBatch(true);
    check(!input.commitUtf8("中")&&input.text()==std::string(159,'a'),"160-byte query limit never splits the final UTF8 character");input.endEventBatch();

    input.activate(TextInputField::CharacterName,"鬼",TextInputPolicy::characterName(whitelist));
    input.beginEventBatch(true);check(input.updateComposition("zhong中",5,100)&&input.composing()&&
        input.compositionCaret()==5&&input.compositionSelection()==1&&!input.canSubmit(),
        "Preedit is distinct from committed text and clamps caret/selection by codepoint");
    for(const auto key:{TextInputKey::Return,TextInputKey::Escape,TextInputKey::Backspace,TextInputKey::Delete,
        TextInputKey::Left,TextInputKey::Right,TextInputKey::Up,TextInputKey::Down,TextInputKey::PageUp,TextInputKey::PageDown,TextInputKey::Space}) {
        const auto route=input.keyDown(key);check(route.consumed&&route.intent==TextInputIntent::None&&input.text()=="鬼",
            "Composition reserves candidate/editing keys and never generates page/save/game commands");input.keyUp(key);
    }
    input.updateComposition("",0,0);input.commitUtf8("中");
    check(input.keyDown(TextInputKey::Return).intent==TextInputIntent::None&&input.text()=="鬼中",
        "Commit before Return cannot leak IME confirmation into character creation");input.endEventBatch();
    input.beginEventBatch(false);check(input.keyDown(TextInputKey::Return).intent==TextInputIntent::None,
        "IME confirmation remains fenced into the next batch until its corresponding KEYUP");
    input.keyUp(TextInputKey::Return);check(input.keyDown(TextInputKey::Return).intent==TextInputIntent::Submit,
        "A distinct Return after KEYUP can submit exactly once");
    check(input.keyDown(TextInputKey::Return,true).intent==TextInputIntent::None,
        "Held/repeated Return cannot duplicate save/create transactions");input.keyUp(TextInputKey::Return);input.endEventBatch();

    input.activate(TextInputField::MapQuery,"艾尔文",TextInputPolicy::mapQuery());
    input.beginEventBatch(true);
    check(input.keyDown(TextInputKey::Return).intent==TextInputIntent::None,
        "Pre-scanned batch blocks Return-before-TEXTINPUT ordering too");
    input.commitUtf8("防线");input.endEventBatch();input.keyUp(TextInputKey::Return);
    input.beginEventBatch(false);check(input.keyDown(TextInputKey::Return).intent==TextInputIntent::Submit,
        "Independent map query confirmation works after text composition finishes");input.keyUp(TextInputKey::Return);
    check(input.keyDown(TextInputKey::PageDown).intent==TextInputIntent::PageDown,
        "Map navigation works outside IME scope and composition traffic");input.keyUp(TextInputKey::PageDown);input.endEventBatch();
    input.activate(TextInputField::MapQuery,"",TextInputPolicy::mapQuery());input.beginEventBatch(false);
    check(input.canSubmit()&&input.keyDown(TextInputKey::Return).intent==TextInputIntent::Submit,
        "An empty map query can confirm the existing selection/reset list");input.keyUp(TextInputKey::Return);input.endEventBatch();

    input.beginEventBatch(true);input.updateComposition("ce",0,2);input.endEventBatch();const auto committed=input.text();
    input.setFocused(false);check(!input.active()&&!input.composing()&&!input.commitUtf8("错")&&input.text()==committed,
        "Window focus loss clears preedit and rejects text from another/debug window");
    input.setFocused(true);check(input.active()&&!input.composing(),"Focus return reactivates only the existing field owner");
    input.deactivate();check(!input.active()&&input.keyDown(TextInputKey::Return).intent==TextInputIntent::None,
        "Leaving edit scope or freezing a pending transaction removes all editing/submit ownership");
    bool missingRulesRejected=false;try{input.activate(TextInputField::CharacterName,"",TextInputPolicy{});}catch(const std::invalid_argument &){missingRulesRejected=true;}
    check(missingRulesRejected,"Name editor cannot silently substitute a guessed whitelist for source rules");
    return {{"status",failures.empty()?"passed":"failed"},{"checks",checks},{"failures",failures},
        {"scope","Portable UTF8/editor/IME-routing contract; real Windows candidate window, SDL event timing and redraw stall are separate host/user verification"}};
}
} // namespace dnf
