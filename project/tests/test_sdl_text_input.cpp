#include "dnf/sdl_text_input.hpp"
#include "dnf/selection_ui.hpp"
#include "dnf/storage.hpp"
#include <cstring>
#include <stdexcept>
#include <type_traits>
namespace dnf {
Json runSdlTextInputTests(Pvf &pvf,Assets &,const std::filesystem::path &output) {
    static_assert(!std::is_copy_constructible_v<SdlTextInputBatch>);
    static_assert(!std::is_copy_assignable_v<SdlTextInputBatch>);
    Json checks=Json::array(),failures=Json::array();
    const auto check=[&](bool passed,const char *message) {
        checks.push_back({{"passed",passed},{"message",message}});if(!passed)failures.push_back(message);
    };
    if(!(SDL_WasInit(SDL_INIT_EVENTS)&SDL_INIT_EVENTS)&&SDL_InitSubSystem(SDL_INIT_EVENTS))
        throw std::runtime_error(SDL_GetError());
    SdlTextInputBatch batch;batch.collect();batch.clear();
    constexpr Uint32 windowId=1031,otherWindow=60;
    const auto push=[&](SDL_Event event) {
        if(SDL_PushEvent(&event)!=1){if(event.type==SDL_TEXTEDITING_EXT)SDL_free(event.editExt.text);throw std::runtime_error("SDL event injection failed");}
    };
    const auto key=[&](Uint32 type,SDL_Keycode symbol){SDL_Event e{};e.type=type;e.key.windowID=windowId;e.key.keysym.sym=symbol;push(e);};
    const auto commit=[&](const char *text,Uint32 id=windowId){SDL_Event e{};e.type=SDL_TEXTINPUT;e.text.windowID=id;SDL_strlcpy(e.text.text,text,sizeof e.text.text);push(e);};
    const auto editing=[&](const char *text){SDL_Event e{};e.type=SDL_TEXTEDITING;e.edit.windowID=windowId;SDL_strlcpy(e.edit.text,text,sizeof e.edit.text);e.edit.start=1;push(e);};
    CharacterNameSourceRules names;names.bind(pvf);TextInputModel input;
    input.activate(TextInputField::CharacterName,"",TextInputPolicy::characterName([&](uint32_t cp){return names.allows(cp);}));
    size_t submits=0,cancels=0;
    const auto route=[&] {
        batch.collect();input.beginEventBatch(batch.hasTextTraffic(windowId));
        for(const auto &event:batch.events()) {
            if(sdlInputEventWindow(event)!=windowId)continue;
            if(event.type==SDL_TEXTINPUT)input.commitUtf8(event.text.text);
            else if(event.type==SDL_TEXTEDITING)input.updateComposition(event.edit.text,event.edit.start,event.edit.length);
            else if(event.type==SDL_TEXTEDITING_EXT)input.updateComposition(event.editExt.text?event.editExt.text:"",event.editExt.start,event.editExt.length);
            else if(event.type==SDL_KEYUP)input.keyUp(sdlTextInputKey(event.key.keysym.sym));
            else if(event.type==SDL_KEYDOWN) {
                const auto result=input.keyDown(sdlTextInputKey(event.key.keysym.sym),event.key.repeat!=0);
                submits+=result.intent==TextInputIntent::Submit;cancels+=result.intent==TextInputIntent::Cancel;
            }
        }
        input.endEventBatch();
    };
    // These are actual queued SDL events, rather than calls that assume one
    // particular ordering from a real Windows input method.
    key(SDL_KEYDOWN,SDLK_RETURN);editing("gui");commit("鬼剑士");route();
    check(submits==0&&input.text()=="鬼剑士"&&!input.composing(),
        "Real SDL batch pre-scan prevents Return-before-commit creating a character");
    key(SDL_KEYDOWN,SDLK_RETURN);route();check(submits==0,
        "The queued confirmation key remains fenced until its actual SDL_KEYUP");
    key(SDL_KEYUP,SDLK_RETURN);key(SDL_KEYDOWN,SDLK_RETURN);route();
    check(submits==1&&input.text()=="鬼剑士","A separate queued Return submits the Chinese name exactly once");
    key(SDL_KEYUP,SDLK_RETURN);editing("");commit("测试");key(SDL_KEYDOWN,SDLK_RETURN);route();
    check(submits==1&&input.text()=="鬼剑士测试","Commit-before-Return also stays inside the IME batch");
    key(SDL_KEYUP,SDLK_RETURN);commit("外窗",otherWindow);route();
    check(input.text()=="鬼剑士测试"&&!batch.hasTextTraffic(windowId),
        "Foreign/debug window text never reaches the main field or its pre-scan");
    SDL_Event ext{};ext.type=SDL_TEXTEDITING_EXT;ext.editExt.windowID=windowId;
    ext.editExt.text=SDL_strdup("changzuzichangzuzichangzuzichangzuzi");
    if(!ext.editExt.text)throw std::bad_alloc();ext.editExt.start=5;ext.editExt.length=2;push(ext);
    route();check(input.composing()&&input.compositionCaret()==5&&input.compositionSelection()==2,
        "Real queued extended preedit survives until the owning batch releases it");
    const auto allocatedBefore=SDL_GetNumAllocations();batch.clear();const auto allocatedAfter=SDL_GetNumAllocations();
    check(allocatedBefore<0||allocatedAfter<allocatedBefore,
        "Clearing an owned extended event releases its SDL allocation");
    batch.clear();check(batch.events().empty(),"Repeated clear and subsequent destruction are safe and cannot free an EXT pointer twice");
    editing("zuzi");key(SDL_KEYDOWN,SDLK_ESCAPE);route();
    check(cancels==0&&input.text()=="鬼剑士测试","Actual composing Escape never becomes page cancel");
    input.setFocused(false);commit("错");route();check(input.text()=="鬼剑士测试"&&!input.composing(),
        "Focus-paused field rejects queued text after the main window loses input ownership");
    input.setFocused(true);input.updateComposition("",0,0);input.endEventBatch();

    const auto fixture=std::filesystem::absolute(output)/"chinese-name-save";
    std::filesystem::create_directories(fixture);
    std::string uuid;
    {
        CharacterStore store(fixture,pvf.identity());
        store.data["characters"][19]={{"name",input.text()},{"class","swordman"},
            {"identity",CharacterIdentity{0,0,0}.json()},{"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
        store.save();uuid=store.data["characters"][19].at("uuid").get<std::string>();
    }
    {
        CharacterStore reloaded(fixture,pvf.identity());
        check(reloaded.data["characters"][19].at("name")==input.text()&&
            reloaded.data["characters"][19].at("uuid")==uuid,
            "The actual CharacterStore preserves the queued Chinese name and UUID after save/reload in slot20");
    }
    check(sdlTextInputKey(SDLK_KP_ENTER)==TextInputKey::Return&&sdlTextInputKey(SDLK_HOME)==TextInputKey::Home,
        "Production SDL key mapping includes keypad submit and caret movement");
    const auto result=Json{{"status",failures.empty()?"passed":"failed"},{"checks",checks},{"failures",failures},
        {"extended_allocation_count_before_clear",allocatedBefore},{"extended_allocation_count_after_clear",allocatedAfter},
        {"scope","Actual SDL_PushEvent/PollEvent batch, extended-event ownership and isolated CharacterStore roundtrip; Windows IME candidate UI remains pending user"}};
    writeJson(std::filesystem::absolute(output)/"sdl-text-input-tests.json",result);return result;
}
} // namespace dnf
