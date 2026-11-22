#include "dnf/text_input.hpp"
#include <algorithm>
#include <stdexcept>
#include <utility>

namespace dnf {
namespace {
size_t byteAt(const std::string &value,size_t codepoint) {
    size_t at=0;
    while(at<value.size()&&codepoint--) {
        const auto lead=uint8_t(value[at]);at+=lead<0x80?1:lead<0xe0?2:lead<0xf0?3:4;
    }
    return at;
}
bool validKey(TextInputKey key) { return size_t(key)<size_t(TextInputKey::Other); }
}
std::vector<uint32_t> decodeTextInputUtf8(const std::string &text) {
    std::vector<uint32_t> out;
    for(size_t i=0;i<text.size();) {
        const auto lead=uint8_t(text[i]);uint32_t cp=0,minimum=0;size_t bytes=0;
        if(lead<0x80){cp=lead;bytes=1;}
        else if(lead>=0xc2&&lead<=0xdf){cp=lead&0x1f;bytes=2;minimum=0x80;}
        else if(lead>=0xe0&&lead<=0xef){cp=lead&0x0f;bytes=3;minimum=0x800;}
        else if(lead>=0xf0&&lead<=0xf4){cp=lead&0x07;bytes=4;minimum=0x10000;}
        else throw std::invalid_argument("Invalid UTF-8 leading byte");
        if(bytes>text.size()-i)throw std::invalid_argument("Truncated UTF-8 sequence");
        for(size_t n=1;n<bytes;++n) {
            const auto next=uint8_t(text[i+n]);
            if((next&0xc0)!=0x80)throw std::invalid_argument("Invalid UTF-8 continuation byte");
            cp=(cp<<6)|(next&0x3f);
        }
        if(cp<minimum||cp>0x10ffff||(cp>=0xd800&&cp<=0xdfff))
            throw std::invalid_argument("Invalid UTF-8 scalar value");
        out.push_back(cp);i+=bytes;
    }
    return out;
}
TextInputPolicy TextInputPolicy::characterName(std::function<bool(uint32_t)> allows) {
    if(!allows)throw std::invalid_argument("Character name policy requires current source whitelist");
    TextInputPolicy out;out.allows=std::move(allows);return out;
}
TextInputPolicy TextInputPolicy::mapQuery() {
    TextInputPolicy out;out.maximumCodepoints=160;out.maximumBytes=160;return out;
}
bool TextInputModel::allowed(const std::vector<uint32_t> &codepoints) const {
    return std::all_of(codepoints.begin(),codepoints.end(),[&](uint32_t cp) {
        return cp>=0x20&&!(cp>=0x7f&&cp<=0x9f)&&(!policy_.allows||policy_.allows(cp));
    });
}
void TextInputModel::activate(TextInputField field,const std::string &initial,TextInputPolicy policy) {
    if(field==TextInputField::None||!policy.maximumBytes||!policy.maximumCodepoints||
       !policy.maximumCompositionBytes||!policy.maximumCompositionCodepoints)
        throw std::invalid_argument("Invalid text-input scope/limits");
    if(field==TextInputField::CharacterName&&!policy.allows)
        throw std::invalid_argument("Character name scope requires current source whitelist");
    if(initial.size()>policy.maximumBytes)throw std::invalid_argument("Initial text exceeds byte limit");
    const auto decoded=decodeTextInputUtf8(initial);
    if(decoded.size()>policy.maximumCodepoints)throw std::invalid_argument("Initial text exceeds character limit");
    const auto oldPolicy=policy_;policy_=std::move(policy);
    if(!allowed(decoded)){policy_=oldPolicy;throw std::invalid_argument("Initial text violates source whitelist");}
    field_=field;text_=initial;caret_=decoded.size();composition_.clear();error_.clear();
    compositionCaret_=compositionSelection_=0;down_.fill(false);untilKeyUp_.fill(false);batchFence_=false;++revision_;
}
void TextInputModel::clearComposition() {
    if(!composition_.empty()||compositionCaret_||compositionSelection_)++revision_;
    composition_.clear();compositionCaret_=compositionSelection_=0;
}
void TextInputModel::deactivate() {
    field_=TextInputField::None;clearComposition();down_.fill(false);untilKeyUp_.fill(false);batchFence_=false;++revision_;
}
void TextInputModel::setFocused(bool focused) {
    if(focused_==focused)return;
    focused_=focused;clearComposition();down_.fill(false);untilKeyUp_.fill(false);batchFence_=false;++revision_;
}
bool TextInputModel::canSubmit() const {
    return active()&&(!text_.empty()||field_==TextInputField::MapQuery)&&composition_.empty()&&error_.empty()&&!batchFence_;
}
std::string TextInputModel::beforeCaret() const { return text_.substr(0,byteAt(text_,caret_)); }
std::string TextInputModel::afterCaret() const { return text_.substr(byteAt(text_,caret_)); }
void TextInputModel::beginEventBatch(bool hasTextOrEditingEvents) {
    batchFence_=active()&&(hasTextOrEditingEvents||composing());
    if(batchFence_)for(size_t i=0;i<untilKeyUp_.size();++i)untilKeyUp_[i]=untilKeyUp_[i]||down_[i];
}
bool TextInputModel::commitUtf8(const std::string &value) {
    if(!active())return false;
    batchFence_=true;clearComposition();
    if(value.empty())return true;
    if(value.size()>policy_.maximumBytes||value.size()>policy_.maximumBytes-text_.size()) {
        error_="输入内容超过长度限制";return false;
    }
    std::vector<uint32_t> codepoints;
    try{codepoints=decodeTextInputUtf8(value);}catch(const std::invalid_argument &){error_="输入内容不是有效的UTF-8文本";return false;}
    if(codepoints.size()>policy_.maximumCodepoints-decodeTextInputUtf8(text_).size()) {
        error_="输入内容超过字符数限制";return false;
    }
    if(!allowed(codepoints)){error_="输入包含当前规则不允许的字符";return false;}
    text_.insert(byteAt(text_,caret_),value);caret_+=codepoints.size();error_.clear();++revision_;return true;
}
bool TextInputModel::updateComposition(const std::string &value,int start,int length) {
    if(!active())return false;
    batchFence_=true;
    if(value.size()>policy_.maximumCompositionBytes){error_="输入法组字内容过长";return false;}
    std::vector<uint32_t> codepoints;
    try{codepoints=decodeTextInputUtf8(value);}catch(const std::invalid_argument &){error_="输入法组字文本编码无效";return false;}
    if(codepoints.size()>policy_.maximumCompositionCodepoints){error_="输入法组字内容过长";return false;}
    if(std::any_of(codepoints.begin(),codepoints.end(),[](uint32_t cp){return cp<0x20||(cp>=0x7f&&cp<=0x9f);})) {
        error_="输入法组字包含控制字符";return false;
    }
    composition_=value;compositionCaret_=std::min(size_t(std::max(0,start)),codepoints.size());
    compositionSelection_=std::min(size_t(std::max(0,length)),codepoints.size()-compositionCaret_);
    error_.clear();++revision_;return true;
}
TextInputRoute TextInputModel::keyDown(TextInputKey key,bool repeat) {
    if(!active()||!validKey(key))return {};
    const auto index=size_t(key);const bool alreadyDown=down_[index];down_[index]=true;
    if(batchFence_||composing()||untilKeyUp_[index]) {
        untilKeyUp_[index]=true;return {true,false,TextInputIntent::None};
    }
    if(key==TextInputKey::Return||key==TextInputKey::Escape) {
        if(repeat||alreadyDown)return {true,false,TextInputIntent::None};
        if(key==TextInputKey::Escape)return {true,false,TextInputIntent::Cancel};
        return {true,false,canSubmit()?TextInputIntent::Submit:TextInputIntent::None};
    }
    const auto count=decodeTextInputUtf8(text_).size();bool changed=false;
    if(key==TextInputKey::Backspace) {
        if(caret_){const auto from=byteAt(text_,caret_-1),to=byteAt(text_,caret_);text_.erase(from,to-from);--caret_;changed=true;}
    } else if(key==TextInputKey::Delete) {
        if(caret_<count){const auto from=byteAt(text_,caret_),to=byteAt(text_,caret_+1);text_.erase(from,to-from);changed=true;}
    } else if(key==TextInputKey::Left){if(caret_){--caret_;changed=true;}}
    else if(key==TextInputKey::Right){if(caret_<count){++caret_;changed=true;}}
    else if(key==TextInputKey::Home){changed=caret_!=0;caret_=0;}
    else if(key==TextInputKey::End){changed=caret_!=count;caret_=count;}
    else if(key==TextInputKey::Space)return {true,false,TextInputIntent::None}; // actual insertion is TEXTINPUT only
    else if(field_==TextInputField::MapQuery) {
        TextInputIntent intent=TextInputIntent::None;
        if(key==TextInputKey::Up)intent=TextInputIntent::Up;
        else if(key==TextInputKey::Down)intent=TextInputIntent::Down;
        else if(key==TextInputKey::PageUp)intent=TextInputIntent::PageUp;
        else if(key==TextInputKey::PageDown)intent=TextInputIntent::PageDown;
        return {true,false,repeat||alreadyDown?TextInputIntent::None:intent};
    }
    if(changed){error_.clear();++revision_;}
    return {true,changed,TextInputIntent::None};
}
void TextInputModel::keyUp(TextInputKey key) {
    if(!validKey(key))return;
    down_[size_t(key)]=false;untilKeyUp_[size_t(key)]=false;
}
} // namespace dnf
