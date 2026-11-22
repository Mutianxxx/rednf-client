#include "squirrel_host.hpp"
#include <squirrel.h>
#include <cstddef>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>

static_assert(sizeof(SQInteger)==4 && sizeof(SQChar)==2,"int32/UTF16 VM required");
static_assert(sizeof(SQHash)==sizeof(void*),"pointer-width object hashes required");
#ifndef SQSTRINGHASH32
#error Host profile requires the explicit fixed-string32 hash strategy
#endif

namespace dnf::squirrel_stage::detail {
struct Abort final : std::runtime_error {
    std::string code;
    explicit Abort(const std::string &message,const std::string &kind="vm_budget_abort"):std::runtime_error(message),code(kind){}
};
struct Arena;
struct alignas(std::max_align_t) Block { Block *previous=nullptr,*next=nullptr;Arena *owner=nullptr;uint64_t bytes=0,payload=0; };
struct Arena {
    Limits limits;
    Block *head=nullptr;
    uint64_t bytes=0,blocks=0,peak=0;
    explicit Arena(Limits value):limits(value){}
    void *allocate(uint64_t count) {
        if(count>std::numeric_limits<size_t>::max()-sizeof(Block))throw Abort("VM allocation size rejected");
        const uint64_t charged=sizeof(Block)+std::max<uint64_t>(count,1);
        // Reallocation pays for BOTH blocks until the copy completes. Headers
        // and zero-size backing bytes are included in the hard heap budget.
        if(charged>limits.heapBytes || bytes>limits.heapBytes-charged || blocks>=limits.heapBlocks)
            throw Abort("VM allocation budget exceeded");
        auto *block=static_cast<Block*>(std::malloc(sizeof(Block)+size_t(count ? count : 1)));
        if(!block)throw Abort("VM system allocation failed");
        new(block)Block;block->owner=this;block->bytes=charged;block->payload=count;block->next=head;
        if(head)head->previous=block;head=block;
        bytes+=charged;blocks++;peak=std::max(peak,bytes);
        return block+1;
    }
    static void freeBlock(void *pointer) noexcept {
        if(!pointer)return;
        auto *block=static_cast<Block*>(pointer)-1;auto &owner=*block->owner;
        if(block->previous)block->previous->next=block->next;else owner.head=block->next;
        if(block->next)block->next->previous=block->previous;
        owner.bytes-=block->bytes;owner.blocks--;std::free(block);
    }
    void *reallocate(void *pointer,uint64_t count) {
        if(!pointer)return allocate(count);
        auto *old=static_cast<Block*>(pointer)-1;
        if(old->owner!=this)throw Abort("cross-arena allocation rejected");
        void *next=allocate(count);
        std::memcpy(next,pointer,size_t(std::min(count,old->payload)));freeBlock(pointer);return next;
    }
    void drop() noexcept {
        while(head){auto *next=head->next;std::free(head);head=next;}
        bytes=blocks=0;
    }
    ~Arena(){drop();}
};
struct Context { Arena *arena=nullptr;Limits limits;uint64_t instructions=0,natives=0; };
thread_local Context *active=nullptr;
struct Activation {
    Context *old;
    explicit Activation(Context &context):old(active) {
        if(active)throw Abort("VM reentry rejected");active=&context;
    }
    ~Activation(){active=old;}
};
static Context &context(){if(!active)throw Abort("VM execution outside host context");return *active;}
} // namespace dnf::squirrel_stage::detail

// Versioned VM hooks. These throw ordinary C++ exceptions into the host. There
// is no longjmp and no C ABI frame. Abort quarantines the complete private VM.
void dnf_sq_budget_tick(SQUnsignedInteger frames,unsigned kind) {
    auto &context=dnf::squirrel_stage::detail::context();
    if(uint64_t(frames)+(kind==2 ? 1 : 0)>context.limits.callDepth)
        throw dnf::squirrel_stage::detail::Abort("VM call-depth budget exceeded");
    if(kind==0 && ++context.instructions>context.limits.instructions)
        throw dnf::squirrel_stage::detail::Abort("VM instruction budget exceeded");
    if(kind==1 && ++context.natives>context.limits.nativeCalls)
        throw dnf::squirrel_stage::detail::Abort("VM native-call budget exceeded");
}
void *dnf_sq_allocate_checked(unsigned long long count){return dnf::squirrel_stage::detail::context().arena->allocate(count);}
void *dnf_sq_reallocate_checked(void *p,unsigned long long count){return dnf::squirrel_stage::detail::context().arena->reallocate(p,count);}
void *sq_vm_malloc(SQUnsignedInteger count){return dnf_sq_allocate_checked(count);}
void *sq_vm_realloc(void *p,SQUnsignedInteger,SQUnsignedInteger count){return dnf_sq_reallocate_checked(p,count);}
void sq_vm_free(void *p,SQUnsignedInteger){dnf::squirrel_stage::detail::Arena::freeBlock(p);}

namespace dnf::squirrel_stage {
namespace {
struct Token {std::string text;size_t at=0;uint64_t line=1,column=1;};
std::string ascii(const std::u16string &value){
    std::string result;for(auto c:value){if(c>127)throw std::runtime_error("non-ASCII host identifier/string rejected");result.push_back(char(c));}return result;
}
std::basic_string<SQChar> wide(const std::string &value){return std::basic_string<SQChar>(value.begin(),value.end());}
std::basic_string<SQChar> wide(const std::u16string &value){return std::basic_string<SQChar>(value.begin(),value.end());}
std::string utf8(const SQChar *text,size_t length) {
    std::string result;
    for(size_t i=0;i<length;i++) {
        uint32_t c=uint16_t(text[i]);
        if(c>=0xd800&&c<=0xdbff){if(i+1==length||uint16_t(text[i+1])<0xdc00||uint16_t(text[i+1])>0xdfff)throw std::runtime_error("invalid UTF16 high surrogate");c=0x10000+((c-0xd800)<<10)+(uint16_t(text[++i])-0xdc00);}
        else if(c>=0xdc00&&c<=0xdfff)throw std::runtime_error("invalid UTF16 low surrogate");
        if(c<0x80)result.push_back(char(c));
        else if(c<0x800){result.push_back(char(0xc0|(c>>6)));result.push_back(char(0x80|(c&63)));}
        else if(c<0x10000){result.push_back(char(0xe0|(c>>12)));result.push_back(char(0x80|((c>>6)&63)));result.push_back(char(0x80|(c&63)));}
        else{result.push_back(char(0xf0|(c>>18)));result.push_back(char(0x80|((c>>12)&63)));result.push_back(char(0x80|((c>>6)&63)));result.push_back(char(0x80|(c&63)));}
    }
    return result;
}
std::vector<Token> lex(const DecodedText &decoded,const Limits &limits) {
    std::vector<Token> tokens;const auto &s=decoded.text;size_t i=0;uint64_t line=1,column=1,depth=0;
    auto advance=[&](){if(s[i++]==u'\n'){line++;column=1;}else column++;};
    auto identifier=[](char16_t c){return(c>=u'a'&&c<=u'z')||(c>=u'A'&&c<=u'Z')||c==u'_'||(c>=u'0'&&c<=u'9');};
    while(i<s.size()) {
        char16_t c=s[i];
        if(c==u' '||c==u'\t'||c==u'\r'||c==u'\n'){advance();continue;}
        if(c==u'/' && i+1<s.size() && s[i+1]==u'/'){while(i<s.size()&&s[i]!=u'\n')advance();continue;}
        if(c==u'/' && i+1<s.size() && s[i+1]==u'*') {
            advance();advance();bool ended=false;
            while(i<s.size()){if(s[i]==u'*'&&i+1<s.size()&&s[i+1]==u'/'){advance();advance();ended=true;break;}advance();}
            if(!ended)throw std::runtime_error("unterminated source comment");continue;
        }
        const bool verbatim=c==u'@' && i+1<s.size() && s[i+1]==u'"';
        if(c==u'"'||c==u'\''||verbatim) {
            const size_t at=i;const uint64_t row=line,col=column;
            if(verbatim)advance();const char16_t quote=s[i];advance();bool ended=false;
            while(i<s.size()) {
                if(s[i]==quote){advance();if(verbatim&&i<s.size()&&s[i]==quote){advance();continue;}ended=true;break;}
                if(!verbatim&&s[i]==u'\\'){advance();if(i<s.size())advance();}else advance();
            }
            if(!ended)throw std::runtime_error("unterminated source string");
            tokens.push_back({"<string>",at,row,col});
        } else if(identifier(c)) {
            const size_t at=i;const uint64_t row=line,col=column;while(i<s.size()&&identifier(s[i]))advance();
            tokens.push_back({ascii(s.substr(at,i-at)),at,row,col});
        } else {
            const size_t at=i;const uint64_t row=line,col=column;advance();
            if(c==u'('||c==u'['||c==u'{'){if(++depth>limits.sourceNesting)throw std::runtime_error("source nesting budget exceeded");}
            if(c==u')'||c==u']'||c==u'}'){if(depth)depth--;}
            tokens.push_back({c<128?std::string(1,char(c)):"<unicode>",at,row,col});
        }
        if(tokens.size()>limits.lexicalTokens)throw std::runtime_error("source token budget exceeded");
    }
    return tokens;
}
SourceRef offsetSource(SourceRef source,uint64_t at,uint64_t length=0){source.byteOffset+=at;source.byteLength=length;return source;}
const std::set<std::string> controls={"if","while","for","foreach","switch","catch","function"};
// These are VM delegates actually available to values, not invented DNF APIs.
const std::set<std::string> delegates={"len","append","push","pop","resize","clear","weakref","ref","tointeger","tofloat","tostring","slice","find","remove","insert","extend","reverse","sort","getdelegate","rawget","rawset","rawin","rawdelete","setdelegate","keys","values","filter","map","reduce","apply","call","acall","pcall","pacall","bindenv","getinfos","getclass","tolower","toupper","tochar","getroot","setroot","getstatus","getattributes","setattributes","instance","getbase","newmember","rawnewmember"};
// Root-table natives this host actually installs (see Impl::open). Keeping the
// list beside the installer means a name can never be classified as callable
// without a matching registration.
const std::set<std::string> hostGlobals={
    "sq_BinaryStartWrite","StartWrite","sq_BinaryWriteWord","WriteWord",
    "sq_BinaryWriteDword","WriteDword","sq_BinaryWriteFloat",
    "sq_BinaryGetReadSize","print","getroottable"};
// Read-only skill parameter queries. Each name maps to the exact
// ScriptWorldApi member that must be present before the token is callable, so
// "classified as implemented" and "has a data source" cannot drift apart.
enum class ScriptQuery {Level,LevelData,IntData,CastTime,BonusRate,Animation,SetAnimation};
const std::map<std::string,ScriptQuery> scriptQueries={
    {"sq_GetSkillLevel",ScriptQuery::Level},{"GetSkillLevel",ScriptQuery::Level},
    {"sq_GetLevelData",ScriptQuery::LevelData},{"GetLevelData",ScriptQuery::LevelData},
    {"sq_GetIntData",ScriptQuery::IntData},{"GetIntData",ScriptQuery::IntData},
    {"sq_GetCastTime",ScriptQuery::CastTime},{"GetCastTime",ScriptQuery::CastTime},
    {"sq_GetBonusRateWithPassive",ScriptQuery::BonusRate},
    {"GetBonusRateWithPassive",ScriptQuery::BonusRate},
    {"sq_GetCurrentAni",ScriptQuery::Animation},{"GetCurrentAni",ScriptQuery::Animation},
    {"sq_GetCurrentAnimation",ScriptQuery::Animation},{"GetCurrentAnimation",ScriptQuery::Animation},
    {"sq_GetCurrentTime",ScriptQuery::Animation},{"GetCurrentTime",ScriptQuery::Animation},
    {"sq_GetCurrentFrameIndex",ScriptQuery::Animation},{"GetCurrentFrameIndex",ScriptQuery::Animation},
    {"sq_GetFrameStartTime",ScriptQuery::Animation},{"GetFrameStartTime",ScriptQuery::Animation},
    {"sq_SetCurrentAnimation",ScriptQuery::SetAnimation},{"SetCurrentAnimation",ScriptQuery::SetAnimation}};
bool queryAvailable(const ScriptWorldApi &api,ScriptQuery query) {
    switch(query) {
    case ScriptQuery::Level:return bool(api.level);
    case ScriptQuery::LevelData:return bool(api.levelData);
    case ScriptQuery::IntData:return bool(api.intData);
    case ScriptQuery::CastTime:return bool(api.castTime);
    case ScriptQuery::BonusRate:return bool(api.bonusRate);
    case ScriptQuery::Animation:return bool(api.animation);
    case ScriptQuery::SetAnimation:return bool(api.setCurrentAnimation);
    }
    return false;
}
// VM-local vector state (`sq_IntVectClear` / `sq_IntVectPush`) and presentation
// commands are admitted only when explicitly listed here. The latter are
// recorded as no-op receipts: they advance the script's control flow but do
// NOT claim a recovered native effect, sound, camera or state transition.
const std::set<std::string> hostCommands={
    "IntVectClear","IntVectPush","GetVectorData",
    "StopMove","SetStaticSpeedInfo","StartDrawCastGauge","EndDrawCastGauge",
    "SetShake","GetDistancePos","GetPassiveObject","SendCreatePassiveObjectPacket",
    "IsUseSkill","IsCommandEnable","AddSetStatePacket","GetState",
    "setSkillSubState","getSkillSubState","getXPos","getYPos","getZPos",
    "getVar","clear_vector","push_vector","get_vector","set_vector",
    "isMyControlObject","stopSound","addElementalChain_ATMage",
    // Source NUT aliases for the same VM-local binary writer and recorded
    // no-op eligibility/power reads. None claims a reconstructed native effect.
    "StartWrite","WriteWord","WriteDword","WriteFloat","WriteByte","WriteBool",
    "IsMyControlObject","GetPowerWithPassive"};
struct HandleToken {uint64_t id;uint32_t generation;};
struct AnimationToken {uint64_t ownerId;uint32_t ownerGeneration;int animationId=-1;};
struct VarListToken {uint64_t ownerId;uint32_t ownerGeneration;};
static int handleTag,animationTag,varListTag;
}

struct Instance::Impl {
    const SourceServices &services;Bridge &bridge;uint64_t id;Limits limits;
    detail::Arena arena;HSQUIRRELVM vm=nullptr;std::thread::id thread;
    bool closed=false,cleaned=false,busy=false;
    SourceUnit current;
    DecodedText decoded;
    std::vector<SoundCommand> pending;
    std::set<std::string> functions;
    std::map<std::string,SourceUnit> functionSources,loadedSources;
    uint64_t action=0,sequence=0;
    // Skill scripts serialize their state-vector/parameters into a small binary
    // buffer before asking the engine to create a passive object. The buffer is
    // pure VM-local memory: it is never exposed to World and never survives a
    // failed instance. sq_BinaryStartWrite resets it, so cross-invoke residue is
    // impossible by construction.
    std::vector<uint8_t> binary;
    // Per-actor IntVect scratch, keyed by handle id. Pure host memory, capped
    // per actor and released with the instance; never published to World.
    std::map<uint64_t,std::vector<int>> vectors;
    std::map<uint64_t,int> substates;
    // Capability set is read once per VM open; the bridge is immutable for the
    // instance's lifetime, so cached std::functions cannot go stale.
    ScriptWorldApi api;
    Diagnostic compilerDiagnostic;
    Impl(const SourceServices &s,Bridge &b,uint64_t instance,Limits l):services(s),bridge(b),id(instance),limits(l),arena(l),thread(std::this_thread::get_id()) {
        if(!id||!limits.instructions||!limits.nativeCalls||!limits.callDepth||!limits.heapBytes||!limits.heapBlocks||!limits.commands)
            throw std::invalid_argument("invalid Squirrel instance identity or zero budget");
    }
    ~Impl(){close("destroyed");}
    void close(const std::string &reason) noexcept {
        if(closed)return;closed=true;pending.clear();
        if(!cleaned){cleaned=true;bridge.cleanup(id,reason);}
        if(vm) {
            try {detail::Context c{&arena,limits};detail::Activation active(c);sq_close(vm);}catch(...){}
            vm=nullptr;
        }
        arena.drop();
    }
    // Fatal C++ abort may leave partially initialized VM objects. No outside
    // pointer/resource ownership is stored in its userdata. Release the entire
    // private arena WITHOUT running VM destructors/finalizers on partial state.
    void quarantine(const std::string &reason) noexcept {
        vm=nullptr;close(reason);
    }
    DecodedText sourceText(const SourceUnit &unit) const {
        if(unit.source.packageIdentity.empty()||unit.source.memberPath.empty()||unit.source.memberSha256.empty()||
           (unit.source.textEncoding!="CP936"&&unit.source.textEncoding!="GBK")||unit.source.byteOffset!=0||
           (unit.source.byteLength!=0&&unit.source.byteLength!=unit.original.size()))throw std::runtime_error("invalid full source identity");
        if(unit.original.size()>limits.sourceBytes)throw std::runtime_error("source byte budget exceeded");
        if(services.digest(unit.original)!=unit.source.memberSha256)throw std::runtime_error("source byte hash mismatch");
        auto value=services.decodeCp936(unit.original);
        if(value.byteOffsets.size()!=value.text.size()+1||value.byteOffsets.back()!=unit.original.size())throw std::runtime_error("decoder offset contract violated");
        return value;
    }
    Inspection inspect(const SourceUnit &unit) const {
        Inspection result;
        try {
            const auto text=sourceText(unit);const auto tokens=lex(text,limits);
            // Capability snapshot: a query token is callable only when its data
            // source is actually wired, never because the name is well known.
            const auto api=bridge.scriptWorldApi();
            std::set<std::string> declared=functions;
            for(size_t i=0;i+2<tokens.size();i++)if(tokens[i].text=="function"&&tokens[i+2].text=="(")declared.insert(tokens[i+1].text);
            for(size_t i=0;i+1<tokens.size();i++) {
                if(tokens[i+1].text!="("||controls.count(tokens[i].text)||(i&&tokens[i-1].text=="function"))continue;
                if(tokens[i].text=="("||tokens[i].text=="="||tokens[i].text==","||tokens[i].text=="return")continue;
                const bool member=i&&tokens[i-1].text==".";
                const auto &token=tokens[i];
                std::string classification="unknown";
                const auto query=scriptQueries.find(token.text);
                const bool admitted=query!=scriptQueries.end()&&queryAvailable(api,query->second);
                const std::string bare=token.text.rfind("sq_",0)==0?token.text.substr(3):token.text;
                if(member && token.text=="getBuffSkillIndex" && bridge.hasBuffSkillIndex())classification="implemented_host";
                else if(member && token.text=="sq_PlaySound" && bridge.hasSoundConsumer())classification="implemented_host";
                else if(member && admitted)classification="implemented_host";
                else if(hostCommands.count(bare))classification="implemented_host";
                else if(member && delegates.count(token.text))classification="vm_delegate";
                else if(!member && declared.count(token.text))classification="source_function";
                else if(!member && hostGlobals.count(token.text))classification="implemented_host";
                else if(!member && admitted)classification="implemented_host";
                result.calls.push_back({token.text,member?"member":"global",classification,text.byteOffsets.at(token.at),token.line,token.column});
                if(classification=="unknown")result.diagnostics.push_back({"unsupported_api","No implemented callable: "+token.text,offsetSource(unit.source,text.byteOffsets.at(token.at)),token.line,token.column});
            }
            result.executable=result.diagnostics.empty();
        } catch(const std::exception &error){result.diagnostics.push_back({"source_rejected",error.what(),unit.source});}
        return result;
    }
    static Impl &self(HSQUIRRELVM v){return *static_cast<Impl*>(sq_getforeignptr(v));}
    SourceRef callerSource() const {
        SQStackInfos info{};
        for(SQInteger level=0;level<SQInteger(limits.callDepth);level++) {
            if(SQ_FAILED(sq_stackinfos(vm,level,&info)))break;
            if(!info.source)continue;
            const auto path=utf8(info.source,std::char_traits<SQChar>::length(info.source));
            const auto found=loadedSources.find(path);if(found!=loadedSources.end())return found->second.source;
        }
        return current.source;
    }
    static EntityHandle handle(HSQUIRRELVM v) {
        SQUserPointer pointer=nullptr,tag=nullptr;
        if(SQ_FAILED(sq_getuserdata(v,1,&pointer,&tag))||tag!=&handleTag)throw std::runtime_error("typed EntityHandle required");
        const auto &token=*static_cast<HandleToken*>(pointer);return {token.id,token.generation};
    }
    static SQInteger buff(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const auto owner=handle(v);if(!host.bridge.valid(owner))throw std::runtime_error("stale EntityHandle generation");
            sq_pushinteger(v,host.bridge.buffSkillIndex(owner));return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger sound(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const auto owner=handle(v);if(!host.bridge.valid(owner))throw std::runtime_error("stale EntityHandle generation");
            const SQChar *text=nullptr;
            if(sq_gettype(v,2)!=OT_STRING||SQ_FAILED(sq_getstring(v,2,&text)))throw std::runtime_error("sound tag must be a string");
            const SQInteger length=sq_getsize(v,2);if(length<=0||length>256)throw std::runtime_error("sound tag size rejected");
            std::string tag;for(SQInteger i=0;i<length;i++){if(text[i]<=0||text[i]>127)throw std::runtime_error("non-ASCII source sound tag rejected");tag.push_back(char(text[i]));}
            const auto origin=host.callerSource();
            const auto source=host.bridge.resolveSound(tag,origin);
            if(!source||source->packageIdentity.empty()||source->memberSha256.empty())throw std::runtime_error("unresolved or unsupported source sound: "+tag);
            if(host.pending.size()>=host.limits.commands)throw detail::Abort("host command budget exceeded");
            host.pending.push_back({host.id,host.action,++host.sequence,owner,origin,*source,tag});return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    // ---- Skill-script binary serialization -------------------------------
    // Backs sq_BinaryStartWrite / sq_BinaryWriteWord / sq_BinaryWriteDword /
    // sq_BinaryWriteFloat / sq_BinaryGetReadSize plus the short aliases that
    // appear in the same scripts (StartWrite / WriteWord / WriteDword). The
    // buffer is little-endian because these bytes are the argument block handed
    // to passive-object creation, and the PVF scripts were written against the
    // engine's packet layout. Nothing here touches World or any external state.
    static SQInteger binaryNumeric(HSQUIRRELVM v,SQInteger index) {
        switch(sq_gettype(v,index)) {
        case OT_INTEGER:{SQInteger n=0;if(SQ_SUCCEEDED(sq_getinteger(v,index,&n)))return n;break;}
        case OT_FLOAT:{SQFloat f=0;if(SQ_SUCCEEDED(sq_getfloat(v,index,&f))){if(!std::isfinite(f)||std::abs(f)>2147483647.0)throw std::runtime_error("binary scalar outside int32 range");return SQInteger(f);}break;}
        case OT_BOOL:{SQBool b=SQFalse;if(SQ_SUCCEEDED(sq_getbool(v,index,&b)))return b?1:0;break;}
        default:break;
        }
        throw std::runtime_error("binary write requires a numeric argument");
    }
    static SQInteger binaryStartWrite(HSQUIRRELVM v) {
        auto &host=self(v);host.binary.clear();return 0;
    }
    static void appendLittleEndian(std::vector<uint8_t> &out,uint64_t value,size_t width,uint64_t limit) {
        if(width>8||out.size()>limit||out.size()+width>limit)throw detail::Abort("binary serialization budget exceeded");
        for(size_t i=0;i<width;i++)out.push_back(uint8_t((value>>(8*i))&0xff));
    }
    static SQInteger binaryWriteWord(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const auto value=binaryNumeric(v,2);
            appendLittleEndian(host.binary,uint64_t(uint16_t(value)),2,host.limits.heapBytes);return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger binaryWriteDword(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const auto value=binaryNumeric(v,2);
            appendLittleEndian(host.binary,uint64_t(uint32_t(value)),4,host.limits.heapBytes);return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger binaryWriteFloat(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            SQFloat value=0;
            if(sq_gettype(v,2)==OT_FLOAT){if(SQ_FAILED(sq_getfloat(v,2,&value)))throw std::runtime_error("binary float unreadable");}
            else value=SQFloat(binaryNumeric(v,2));
            if(!std::isfinite(value))throw std::runtime_error("binary float outside finite range");
            uint32_t bits=0;std::memcpy(&bits,&value,sizeof bits);
            appendLittleEndian(host.binary,uint64_t(bits),4,host.limits.heapBytes);return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger binaryWriteByte(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const auto value=binaryNumeric(v,2);
            appendLittleEndian(host.binary,uint64_t(uint8_t(value)),1,host.limits.heapBytes);return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger binaryReadSize(HSQUIRRELVM v) {
        auto &host=self(v);
        if(host.binary.size()>size_t(INT32_MAX))throw detail::Abort("binary buffer outside int32 range");
        sq_pushinteger(v,SQInteger(host.binary.size()));return 1;
    }
    // ---- Read-only skill parameter queries -------------------------------
    // Measured on this VM: a member call binds the userdata as `this`, while a
    // global call binds the root table as `this` and passes the owner as
    // argument 1. Both forms therefore have the owner at index 1 or 2 and the
    // real arguments shifted by 0 or 1 respectively; queryBase() decides.
    static SQInteger intArg(HSQUIRRELVM v,SQInteger index) {
        SQInteger value=0;
        if(sq_gettype(v,index)!=OT_INTEGER||SQ_FAILED(sq_getinteger(v,index,&value))) {
            std::string stack;
            for(SQInteger i=1;i<=sq_gettop(v);i++) {
                stack+=" ["+std::to_string(int(sq_gettype(v,i)))+":";
                const SQChar *text=nullptr;
                if(sq_gettype(v,i)==OT_STRING&&SQ_SUCCEEDED(sq_getstring(v,i,&text))&&text)stack+=utf8(text,std::char_traits<SQChar>::length(text));
                else if(sq_gettype(v,i)==OT_INTEGER){SQInteger n=0;sq_getinteger(v,i,&n);stack+=std::to_string((long long)n);}
                stack+="]";
            }
            SQStackInfos info{};
            if(SQ_SUCCEEDED(sq_stackinfos(v,1,&info))) {
                stack+=" func="+(info.funcname?utf8(info.funcname,std::char_traits<SQChar>::length(info.funcname)):"?");
                stack+=" source="+(info.source?utf8(info.source,std::char_traits<SQChar>::length(info.source)):"?");
                stack+=" line="+std::to_string((long long)info.line);
            }
            throw std::runtime_error("skill query argument "+std::to_string(int(index))+" must be an integer (stack:"+stack+")");
        }
        return value;
    }
    static SQFloat ratioArg(HSQUIRRELVM v,SQInteger index) {
        SQFloat value=0;
        if(sq_gettype(v,index)==OT_INTEGER)return SQFloat(intArg(v,index));
        if(sq_gettype(v,index)==OT_FLOAT&&SQ_SUCCEEDED(sq_getfloat(v,index,&value))&&std::isfinite(value))return value;
        throw std::runtime_error("skill query ratio must be a finite number");
    }
    // The two documented call shapes do NOT share one argument offset:
    //   obj.sq_GetSkillLevel(skill)  -> [this=obj, skill]
    //   sq_GetSkillLevel(obj,skill)  -> [this=roottable, obj, skill]
    // A global call binds the root table as `this`, so its explicit owner lands
    // at index 2 and every real argument shifts by one. Detect the shape from
    // where the typed handle actually sits instead of assuming either layout.
    static SQInteger queryBase(HSQUIRRELVM v) {
        SQUserPointer pointer=nullptr,tag=nullptr;
        if(SQ_SUCCEEDED(sq_getuserdata(v,1,&pointer,&tag))&&tag==&handleTag)return 0;
        if(sq_gettop(v)>=2&&SQ_SUCCEEDED(sq_getuserdata(v,2,&pointer,&tag))&&tag==&handleTag)return 1;
        throw std::runtime_error("skill query requires the owning character handle");
    }
    static SQInteger skillLevelQuery(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);
            const int skill=intArg(v,2+base);
            sq_pushinteger(v,SQInteger(host.api.level(skill)));return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger levelDataQuery(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);
            const int skill=intArg(v,2+base),column=intArg(v,3+base);
            const int level=sq_gettop(v)>=4+base?intArg(v,4+base):host.api.level(skill);
            const auto value=host.api.levelData(skill,column,level);
            if(value)sq_pushfloat(v,SQFloat(*value));else sq_pushnull(v);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger intDataQuery(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);
            const int skill=intArg(v,2+base),index=intArg(v,3+base);
            const auto value=host.api.intData(skill,index);
            if(value)sq_pushinteger(v,SQInteger(*value));else sq_pushnull(v);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger castTimeQuery(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);
            const int skill=intArg(v,2+base);
            const int level=sq_gettop(v)>=3+base?intArg(v,3+base):host.api.level(skill);
            const auto value=host.api.castTime(skill,level);
            if(value)sq_pushinteger(v,SQInteger(*value));else sq_pushnull(v);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    static SQInteger bonusRateQuery(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);
            const int skill=intArg(v,2+base),state=intArg(v,3+base),column=intArg(v,4+base);
            const SQFloat ratio=sq_gettop(v)>=5+base?ratioArg(v,5+base):SQFloat(1);
            const auto value=host.api.bonusRate(skill,state,column,double(ratio));
            if(value)sq_pushfloat(v,SQFloat(*value));else sq_pushnull(v);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &error){throw detail::Abort(error.what(),"host_fault");}
    }
    // ---- Animation, vector and presentation-command natives --------------
    // An animation handle carries the owning actor, never a native animation
    // pointer. All clock values come from the actor's published ANI snapshot.
    static SQInteger animationBase(HSQUIRRELVM v) {
        SQUserPointer pointer=nullptr,tag=nullptr;
        if(sq_gettop(v)>=1&&SQ_SUCCEEDED(sq_getuserdata(v,1,&pointer,&tag))&&ownerTag(tag))return 0;
        if(sq_gettop(v)>=2&&SQ_SUCCEEDED(sq_getuserdata(v,2,&pointer,&tag))&&ownerTag(tag))return 1;
        throw std::runtime_error("native requires a character, animation or var-list handle");
    }
    static bool ownerTag(SQUserPointer tag) {
        return tag==&handleTag||tag==&animationTag||tag==&varListTag;
    }
    static EntityHandle tokenOwner(HSQUIRRELVM v,SQInteger index) {
        SQUserPointer pointer=nullptr,tag=nullptr;
        if(SQ_SUCCEEDED(sq_getuserdata(v,index,&pointer,&tag))) {
            if(tag==&animationTag){const auto *t=static_cast<const AnimationToken*>(pointer);return {t->ownerId,t->ownerGeneration};}
            if(tag==&varListTag){const auto *t=static_cast<const VarListToken*>(pointer);return {t->ownerId,t->ownerGeneration};}
            if(tag==&handleTag){const auto *t=static_cast<const HandleToken*>(pointer);return {t->id,t->generation};}
        }
        throw std::runtime_error("native handle has no actor identity");
    }
    static SQInteger currentAni(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            auto *token=static_cast<AnimationToken*>(sq_newuserdata(v,sizeof(AnimationToken)));
            *token={owner.id,owner.generation,-1};sq_settypetag(v,-1,&animationTag);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger currentTime(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            const auto snap=host.api.animation?host.api.animation(owner):std::nullopt;
            sq_pushinteger(v,snap?SQInteger(snap->elapsedMs):0);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger currentFrameIndex(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            const auto snap=host.api.animation?host.api.animation(owner):std::nullopt;
            sq_pushinteger(v,snap?SQInteger(snap->frame):-1);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger frameStartTime(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            int frame=-1;
            for(SQInteger i=sq_gettop(v);i>=2;i--)if(sq_gettype(v,i)==OT_INTEGER){frame=int(intArg(v,i));break;}
            const auto snap=host.api.animation?host.api.animation(owner):std::nullopt;
            // The published clock only carries the frame it currently occupies.
            // For other frame indices we return that boundary as a NOMINAL value
            // so scripts can finish their control flow; this is explicitly not
            // a recovered per-frame timeline and is marked as such downstream.
            if(snap)sq_pushinteger(v,SQInteger(frame==snap->frame?snap->frameStartMs:0));else sq_pushinteger(v,0);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger setAnimation(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);const auto owner=tokenOwner(v,1+base);
            const int id=intArg(v,2+base);
            const bool accepted=host.api.setCurrentAnimation?host.api.setCurrentAnimation(owner,id):false;
            sq_pushinteger(v,accepted?1:0);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger vectorClear(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);host.vectors[tokenOwner(v,1+base).id].clear();return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger vectorPush(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            if(host.vectors[owner.id].size()>=4096)throw std::runtime_error("script vector budget exceeded");
            host.vectors[owner.id].push_back(int(intArg(v,2+base)));return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger vectorData(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            const int index=int(intArg(v,2+base));const auto it=host.vectors.find(owner.id);
            sq_pushinteger(v,(it!=host.vectors.end()&&index>=0&&size_t(index)<it->second.size())?SQInteger(it->second[size_t(index)]):0);
            return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    void pushVarList(EntityHandle owner) {
        auto *token=static_cast<VarListToken*>(sq_newuserdata(vm,sizeof(VarListToken)));
        *token={owner.id,owner.generation};sq_settypetag(vm,-1,&varListTag);
        sq_newtable(vm);
        auto method=[&](const SQChar *name,SQFUNCTION fn){
            sq_pushstring(vm,name,-1);sq_newclosure(vm,fn,0);sq_newslot(vm,-3,SQFalse);
        };
        method(L"clear_vector",vectorClear);method(L"push_vector",vectorPush);
        method(L"get_vector",vectorData);method(L"set_vector",vectorSet);
        sq_setdelegate(vm,-2);
    }
    static SQInteger getVar(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);host.pushVarList(tokenOwner(v,1+base));return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger positionAxis(HSQUIRRELVM v,size_t axis) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);const auto owner=tokenOwner(v,1+base);
            const auto p=host.api.position?host.api.position(owner):std::nullopt;
            sq_pushfloat(v,p?SQFloat((*p)[axis]):0);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger posX(HSQUIRRELVM v) {return positionAxis(v,0);}
    static SQInteger posY(HSQUIRRELVM v) {return positionAxis(v,1);}
    static SQInteger posZ(HSQUIRRELVM v) {return positionAxis(v,2);}
    static SQInteger setSubState(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);const auto owner=tokenOwner(v,1+base);
            host.substates[owner.id]=int(intArg(v,2+base));return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger getSubState(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v);const auto owner=tokenOwner(v,1+base);
            const auto it=host.substates.find(owner.id);
            sq_pushinteger(v,it!=host.substates.end()?SQInteger(it->second):0);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger vectorSet(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=animationBase(v);const auto owner=tokenOwner(v,1+base);
            const int index=int(intArg(v,2+base)),value=int(intArg(v,3+base));
            if(index<0||index>=4096)throw std::runtime_error("script vector index outside budget");
            auto &vec=host.vectors[owner.id];
            if(size_t(index)>=vec.size())vec.resize(size_t(index)+1,0);
            vec[size_t(index)]=value;return 0;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    // `sq_GetVectorData(datas, index)` reads a caller-supplied callback array;
    // it is a different native from the var-list `get_vector(index)` method.
    static SQInteger sourceVectorData(HSQUIRRELVM v) {
        auto &host=self(v);
        try {
            const SQInteger base=queryBase(v),arrayIndex=2+base,indexIndex=3+base;
            if(sq_gettop(v)<indexIndex||sq_gettype(v,arrayIndex)!=OT_ARRAY){sq_pushinteger(v,0);return 1;}
            const int index=int(intArg(v,indexIndex));
            sq_push(v,arrayIndex);sq_pushinteger(v,SQInteger(index));
            if(SQ_SUCCEEDED(sq_get(v,-2)))return 1;
            sq_pop(v,1);sq_pushinteger(v,0);return 1;
        }catch(const detail::Abort&){throw;}catch(const std::exception &e){throw detail::Abort(e.what(),"host_fault");}
    }
    static SQInteger stubTrue(HSQUIRRELVM v) {sq_pushinteger(v,1);return 1;}
    static SQInteger stubZero(HSQUIRRELVM v) {sq_pushinteger(v,0);return 1;}
    static SQInteger stubNull(HSQUIRRELVM v) {sq_pushnull(v);return 1;}
    // print() is the only script-visible diagnostic sink. It is bounded and
    // ASCII-only so a malformed script cannot flood the log or inject bytes.
    static SQInteger print(HSQUIRRELVM v) {
        const SQChar *text=nullptr;
        if(sq_gettype(v,2)!=OT_STRING||SQ_FAILED(sq_getstring(v,2,&text))||!text)return 0;
        const SQInteger length=sq_getsize(v,2);
        std::string line;line.reserve(size_t(std::min<SQInteger>(length,512)));
        for(SQInteger i=0;i<length&&i<512;i++)line.push_back(text[i]>0&&text[i]<128?char(text[i]):'?');
        std::fprintf(stderr,"[script] %s\n",line.c_str());return 0;
    }
    static void compileError(HSQUIRRELVM v,const SQChar *description,const SQChar*,SQInteger row,SQInteger column) {
        auto &host=self(v);const auto message=description?utf8(description,std::char_traits<SQChar>::length(description)):std::string("compiler error");
        uint64_t index=0,line=1;while(index<host.decoded.text.size()&&line<uint64_t(std::max(1,row)))if(host.decoded.text[index++]==u'\n')line++;
        if(column>0)index=std::min<uint64_t>(host.decoded.text.size(),index+uint64_t(column-1));
        host.compilerDiagnostic={"compile_error",message,offsetSource(host.current.source,host.decoded.byteOffsets.at(index)),uint64_t(std::max(0,row)),uint64_t(std::max(0,column))};
    }
    // Shared by root-table and per-handle delegates so the same capability
    // snapshot governs both call shapes. Commands are VM-local and recorded
    // only; animation natives require a published clock from the bridge.
    template <typename Install> void installAnimationAndCommands(Install install) {
        auto native=[&](const SQChar *name,SQFUNCTION fn,ScriptQuery kind){
            if(queryAvailable(api,kind))install(name,fn);
        };
        native(L"sq_GetCurrentAni",currentAni,ScriptQuery::Animation);
        native(L"GetCurrentAni",currentAni,ScriptQuery::Animation);
        native(L"sq_GetCurrentAnimation",currentAni,ScriptQuery::Animation);
        native(L"GetCurrentAnimation",currentAni,ScriptQuery::Animation);
        native(L"sq_GetCurrentTime",currentTime,ScriptQuery::Animation);
        native(L"GetCurrentTime",currentTime,ScriptQuery::Animation);
        native(L"sq_GetCurrentFrameIndex",currentFrameIndex,ScriptQuery::Animation);
        native(L"GetCurrentFrameIndex",currentFrameIndex,ScriptQuery::Animation);
        native(L"sq_GetFrameStartTime",frameStartTime,ScriptQuery::Animation);
        native(L"GetFrameStartTime",frameStartTime,ScriptQuery::Animation);
        native(L"sq_SetCurrentAnimation",setAnimation,ScriptQuery::SetAnimation);
        native(L"SetCurrentAnimation",setAnimation,ScriptQuery::SetAnimation);
        install(L"sq_IntVectClear",vectorClear);
        install(L"IntVectClear",vectorClear);
        install(L"sq_IntVectPush",vectorPush);
        install(L"IntVectPush",vectorPush);
        install(L"sq_GetVectorData",sourceVectorData);
        install(L"GetVectorData",sourceVectorData);
        // Eligibility gates stay open: returning false here would silently
        // skip the whole callback body and hide every other admitted call.
        install(L"sq_IsUseSkill",stubTrue);
        install(L"sq_IsCommandEnable",stubTrue);
        install(L"sq_StopMove",stubZero);
        install(L"sq_SetStaticSpeedInfo",stubZero);
        install(L"sq_StartDrawCastGauge",stubZero);
        install(L"sq_EndDrawCastGauge",stubZero);
        install(L"sq_SetShake",stubZero);
        install(L"sq_GetDistancePos",stubZero);
        install(L"sq_GetPassiveObject",stubNull);
        install(L"sq_SendCreatePassiveObjectPacket",stubNull);
        install(L"sq_AddSetStatePacket",stubZero);
        install(L"sq_GetState",stubZero);
        install(L"getVar",getVar);
        install(L"getXPos",posX);
        install(L"getYPos",posY);
        install(L"getZPos",posZ);
        install(L"setSkillSubState",setSubState);
        install(L"getSkillSubState",getSubState);
        install(L"clear_vector",vectorClear);
        install(L"push_vector",vectorPush);
        install(L"get_vector",vectorData);
        install(L"set_vector",vectorSet);
        install(L"isMyControlObject",stubTrue);
        install(L"stopSound",stubZero);
        install(L"addElementalChain_ATMage",stubZero);
        install(L"sq_StartWrite",binaryStartWrite);
        install(L"sq_WriteWord",binaryWriteWord);
        install(L"sq_WriteDword",binaryWriteDword);
        install(L"sq_WriteFloat",binaryWriteFloat);
        install(L"sq_WriteByte",binaryWriteByte);
        install(L"sq_WriteBool",binaryWriteByte);
        install(L"sq_IsMyControlObject",stubTrue);
        install(L"IsMyControlObject",stubTrue);
        install(L"sq_GetPowerWithPassive",stubZero);
        install(L"GetPowerWithPassive",stubZero);
    }
    void open() {
        if(vm)return;vm=sq_open(256);if(!vm)throw detail::Abort("sq_open failed");
        sq_setforeignptr(vm,this);sq_setcompilererrorhandler(vm,compileError);
        api=bridge.scriptWorldApi();
        // No I/O, clock, random, thread, dynamic compiler or error-hook root
        // functions are exposed. The script language/value delegates remain VM.
        sq_newtable(vm);
        auto global=[&](const SQChar *name,SQFUNCTION function,SQInteger params){
            sq_pushstring(vm,name,-1);sq_newclosure(vm,function,0);sq_setparamscheck(vm,params,nullptr);sq_newslot(vm,-3,SQFalse);
        };
        // Binary serialization: VM-local by construction, published only through
        // the typed command transaction that consumes it.
        global(L"sq_BinaryStartWrite",binaryStartWrite,1);
        global(L"StartWrite",binaryStartWrite,1);
        global(L"sq_BinaryWriteWord",binaryWriteWord,2);
        global(L"WriteWord",binaryWriteWord,2);
        global(L"sq_BinaryWriteDword",binaryWriteDword,2);
        global(L"WriteDword",binaryWriteDword,2);
        global(L"sq_BinaryWriteFloat",binaryWriteFloat,2);
        global(L"sq_BinaryGetReadSize",binaryReadSize,1);
        global(L"print",print,2);
        // Skill parameter queries: registered only when a data source exists,
        // mirroring the inspect() admission rule exactly.
        auto query=[&](const SQChar *name,SQFUNCTION function,ScriptQuery kind){
            if(!queryAvailable(api,kind))return;
            global(name,function,0);
        };
        query(L"sq_GetSkillLevel",skillLevelQuery,ScriptQuery::Level);
        query(L"GetSkillLevel",skillLevelQuery,ScriptQuery::Level);
        query(L"sq_GetLevelData",levelDataQuery,ScriptQuery::LevelData);
        query(L"GetLevelData",levelDataQuery,ScriptQuery::LevelData);
        query(L"sq_GetIntData",intDataQuery,ScriptQuery::IntData);
        query(L"GetIntData",intDataQuery,ScriptQuery::IntData);
        query(L"sq_GetCastTime",castTimeQuery,ScriptQuery::CastTime);
        query(L"GetCastTime",castTimeQuery,ScriptQuery::CastTime);
        query(L"sq_GetBonusRateWithPassive",bonusRateQuery,ScriptQuery::BonusRate);
        query(L"GetBonusRateWithPassive",bonusRateQuery,ScriptQuery::BonusRate);
        installAnimationAndCommands([&](const SQChar *name,SQFUNCTION fn){global(name,fn,0);});
        sq_setroottable(vm);sq_settop(vm,0);
    }
    void pushHandle(EntityHandle owner) {
        auto *token=static_cast<HandleToken*>(sq_newuserdata(vm,sizeof(HandleToken)));
        *token={owner.id,owner.generation};sq_settypetag(vm,-1,&handleTag);sq_newtable(vm);
        auto method=[&](const SQChar *name,SQFUNCTION function,SQInteger params){sq_pushstring(vm,name,-1);sq_newclosure(vm,function,0);sq_setparamscheck(vm,params,nullptr);sq_newslot(vm,-3,SQFalse);};
        if(bridge.hasBuffSkillIndex())method(L"getBuffSkillIndex",buff,1);
        if(bridge.hasSoundConsumer())method(L"sq_PlaySound",sound,2);
        // Member form of the skill queries. `obj.sq_GetSkillLevel(skill)` puts
        // obj at stack index 1 as `this`, identical to the global form's
        // explicit first argument, so both share one implementation.
        auto query=[&](const SQChar *name,SQFUNCTION function,ScriptQuery kind){
            if(!queryAvailable(api,kind))return;
            method(name,function,0);
        };
        query(L"sq_GetSkillLevel",skillLevelQuery,ScriptQuery::Level);
        query(L"GetSkillLevel",skillLevelQuery,ScriptQuery::Level);
        query(L"sq_GetLevelData",levelDataQuery,ScriptQuery::LevelData);
        query(L"GetLevelData",levelDataQuery,ScriptQuery::LevelData);
        query(L"sq_GetIntData",intDataQuery,ScriptQuery::IntData);
        query(L"GetIntData",intDataQuery,ScriptQuery::IntData);
        query(L"sq_GetCastTime",castTimeQuery,ScriptQuery::CastTime);
        query(L"GetCastTime",castTimeQuery,ScriptQuery::CastTime);
        query(L"sq_GetBonusRateWithPassive",bonusRateQuery,ScriptQuery::BonusRate);
        query(L"GetBonusRateWithPassive",bonusRateQuery,ScriptQuery::BonusRate);
        installAnimationAndCommands([&](const SQChar *name,SQFUNCTION fn){method(name,fn,0);});
        sq_setdelegate(vm,-2);
    }
    void push(const Json &value,unsigned depth=0) {
        if(depth>8)throw std::runtime_error("callback argument nesting rejected");
        if(value.is_null())sq_pushnull(vm);
        else if(value.is_boolean())sq_pushbool(vm,value.get<bool>());
        else if(value.is_number_unsigned()) {
            const uint64_t n=value.get<uint64_t>();if(n>INT32_MAX)throw std::runtime_error("callback unsigned integer outside int32");sq_pushinteger(vm,int32_t(n));
        }else if(value.is_number_integer()) {
            const int64_t n=value.get<int64_t>();if(n<INT32_MIN||n>INT32_MAX)throw std::runtime_error("callback integer outside int32");sq_pushinteger(vm,int32_t(n));
        }else if(value.is_number_float()){
            const double n=value.get<double>();if(!std::isfinite(n)||std::abs(n)>std::numeric_limits<SQFloat>::max())throw std::runtime_error("callback float outside finite VM range");sq_pushfloat(vm,SQFloat(n));
        }
        else if(value.is_array()) {
            if(value.size()>256)throw std::runtime_error("callback array budget exceeded");sq_newarray(vm,0);
            for(const auto &entry:value){push(entry,depth+1);sq_arrayappend(vm,-2);}
        }else throw std::runtime_error("unsupported explicit callback argument type");
    }
    Json readValue(SQInteger index) {
        switch(sq_gettype(vm,index)) {
        case OT_NULL:return nullptr;
        case OT_BOOL:{SQBool b;sq_getbool(vm,index,&b);return b!=0;}
        case OT_INTEGER:{SQInteger n;sq_getinteger(vm,index,&n);return n;}
        case OT_FLOAT:{SQFloat n;sq_getfloat(vm,index,&n);return double(n);}
        case OT_STRING:{const SQChar *s;sq_getstring(vm,index,&s);return utf8(s,size_t(sq_getsize(vm,index)));}
        default:throw std::runtime_error("callback returned unsupported persistent/complex value");
        }
    }
    std::string lastError() {
        sq_getlasterror(vm);std::string result="VM exception";
        if(sq_gettype(vm,-1)==OT_STRING){const auto value=readValue(-1);result=value.get<std::string>();}sq_pop(vm,1);return result;
    }
    Result perform(const std::function<void(Result&)> &work) {
        Result result;
        if(thread!=std::this_thread::get_id()){result.diagnostics.push_back({"wrong_thread","Squirrel host requires its simulation thread",current.source});return result;}
        if(closed||busy){result.closed=closed;result.diagnostics.push_back({closed?"closed":"reentry","instance unavailable",current.source});return result;}
        detail::Context context{&arena,limits};busy=true;pending.clear();
        bool fatal=false;
        try {
            detail::Activation active(context);open();work(result);
            if(!result.ok)throw std::runtime_error("VM operation did not complete");
            if(sq_gettop(vm)!=0)throw std::runtime_error("host stack invariant violated");
            result.stackRestored=true;result.stagedCommands=pending.size();
            if(!pending.empty()){
                for(const auto &command:pending)if(!bridge.valid(command.owner))throw std::runtime_error("generation changed before command commit");
                auto prepared=bridge.prepare(pending);if(!prepared)throw std::runtime_error("typed command transaction rejected");
                bridge.commit(std::move(prepared));
            }
            pending.clear();
        } catch(const detail::Abort &error) {
            fatal=true;result.ok=false;result.diagnostics.push_back({error.code,error.what(),current.source});
        } catch(const std::exception &error) {
            result.ok=false;result.diagnostics.push_back({"vm_fault",error.what(),current.source});
        } catch(...) {fatal=true;result.ok=false;result.diagnostics.push_back({"vm_fault","unknown native failure",current.source});}
        result.instructions=context.instructions;result.nativeCalls=context.natives;result.heapPeak=arena.peak;
        busy=false;
        if(!result.ok){
            if(fatal)quarantine("VM budget/allocator abort");
            else {
                try {if(vm){detail::Activation active(context);sq_settop(vm,0);result.stackRestored=sq_gettop(vm)==0;}}
                catch(...){quarantine("stack restoration failed");}
                close("VM operation fault");
            }
        }
        result.closed=closed;result.liveHeap=arena.bytes;result.arenaReleased=closed&&arena.bytes==0;
        return result;
    }
    Result compile(const SourceUnit &unit,bool execute) {
        return perform([&](Result &result){
            current=unit;
            decoded=sourceText(unit);const auto tokens=lex(decoded,limits);
            if(execute){const auto inspection=inspect(unit);if(!inspection.executable){result.diagnostics=inspection.diagnostics;throw std::runtime_error("source capability admission rejected");}}
            compilerDiagnostic={};const auto code=wide(decoded.text);const auto path=wide(unit.source.memberPath);
            if(SQ_FAILED(sq_compilebuffer(vm,code.c_str(),SQInteger(code.size()),path.c_str(),SQTrue))){result.diagnostics.push_back(compilerDiagnostic);throw std::runtime_error("source compilation failed");}
            if(execute){sq_pushroottable(vm);if(SQ_FAILED(sq_call(vm,1,SQTrue,SQTrue)))throw std::runtime_error(lastError());}
            sq_settop(vm,0);
            if(execute){
                loadedSources[unit.source.memberPath]=unit;
                for(size_t i=0;i+2<tokens.size();i++)if(tokens[i].text=="function"&&tokens[i+2].text=="("){functions.insert(tokens[i+1].text);functionSources[tokens[i+1].text]=unit;}
            }
            result.ok=true;
        });
    }
};

Instance::Instance(const SourceServices &services,Bridge &bridge,uint64_t id,Limits limits):impl_(std::make_unique<Impl>(services,bridge,id,limits)){}
Instance::~Instance()=default;
Inspection Instance::inspect(const SourceUnit &source)const{return impl_->inspect(source);}
Result Instance::compileOnly(const SourceUnit &source){return impl_->compile(source,false);}
Result Instance::load(const SourceUnit &source){return impl_->compile(source,true);}
Result Instance::invoke(const std::string &callback,EntityHandle owner,uint64_t action,const std::vector<Json> &arguments) {
    auto &host=*impl_;
    return host.perform([&](Result &result){
        if(!owner||!action||!host.bridge.valid(owner))throw std::runtime_error("invalid callback identity/generation");
        if(!host.functions.count(callback))throw std::runtime_error("unregistered source callback: "+callback);
        host.action=action;host.current=host.functionSources.at(callback);
        sq_pushroottable(host.vm);sq_pushstring(host.vm,wide(callback).c_str(),-1);
        if(SQ_FAILED(sq_get(host.vm,-2)))throw std::runtime_error("callback lookup failed");
        sq_pushroottable(host.vm);host.pushHandle(owner);
        if(arguments.size()>16)throw std::runtime_error("callback argument count rejected");
        for(const auto &argument:arguments)host.push(argument);
        if(SQ_FAILED(sq_call(host.vm,SQInteger(2+arguments.size()),SQTrue,SQTrue)))throw std::runtime_error(host.lastError());
        result.value=host.readValue(-1);sq_settop(host.vm,0);result.ok=true;
    });
}
void Instance::close(const std::string &reason)noexcept{impl_->close(reason);}
bool Instance::closed()const noexcept{return impl_->closed;}
uint64_t Instance::liveHeap()const noexcept{return impl_->arena.bytes;}
} // namespace dnf::squirrel_stage
