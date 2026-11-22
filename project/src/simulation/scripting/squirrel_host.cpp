#include "squirrel_host.hpp"
#include <squirrel.h>
#include <cstddef>
#include <cmath>
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
struct HandleToken {uint64_t id;uint32_t generation;};
static int handleTag;
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
            std::set<std::string> declared=functions;
            for(size_t i=0;i+2<tokens.size();i++)if(tokens[i].text=="function"&&tokens[i+2].text=="(")declared.insert(tokens[i+1].text);
            for(size_t i=0;i+1<tokens.size();i++) {
                if(tokens[i+1].text!="("||controls.count(tokens[i].text)||(i&&tokens[i-1].text=="function"))continue;
                if(tokens[i].text=="("||tokens[i].text=="="||tokens[i].text==","||tokens[i].text=="return")continue;
                const bool member=i&&tokens[i-1].text==".";
                const auto &token=tokens[i];
                std::string classification="unknown";
                if(member && token.text=="getBuffSkillIndex" && bridge.hasBuffSkillIndex())classification="implemented_host";
                else if(member && token.text=="sq_PlaySound" && bridge.hasSoundConsumer())classification="implemented_host";
                else if(member && delegates.count(token.text))classification="vm_delegate";
                else if(!member && declared.count(token.text))classification="source_function";
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
    static void compileError(HSQUIRRELVM v,const SQChar *description,const SQChar*,SQInteger row,SQInteger column) {
        auto &host=self(v);const auto message=description?utf8(description,std::char_traits<SQChar>::length(description)):std::string("compiler error");
        uint64_t index=0,line=1;while(index<host.decoded.text.size()&&line<uint64_t(std::max(1,row)))if(host.decoded.text[index++]==u'\n')line++;
        if(column>0)index=std::min<uint64_t>(host.decoded.text.size(),index+uint64_t(column-1));
        host.compilerDiagnostic={"compile_error",message,offsetSource(host.current.source,host.decoded.byteOffsets.at(index)),uint64_t(std::max(0,row)),uint64_t(std::max(0,column))};
    }
    void open() {
        if(vm)return;vm=sq_open(256);if(!vm)throw detail::Abort("sq_open failed");
        sq_setforeignptr(vm,this);sq_setcompilererrorhandler(vm,compileError);
        // No I/O, clock, random, thread, dynamic compiler or error-hook root
        // functions are exposed. The script language/value delegates remain VM.
        sq_newtable(vm);sq_setroottable(vm);sq_settop(vm,0);
    }
    void pushHandle(EntityHandle owner) {
        auto *token=static_cast<HandleToken*>(sq_newuserdata(vm,sizeof(HandleToken)));
        *token={owner.id,owner.generation};sq_settypetag(vm,-1,&handleTag);sq_newtable(vm);
        auto method=[&](const SQChar *name,SQFUNCTION function,SQInteger params){sq_pushstring(vm,name,-1);sq_newclosure(vm,function,0);sq_setparamscheck(vm,params,nullptr);sq_newslot(vm,-3,SQFalse);};
        if(bridge.hasBuffSkillIndex())method(L"getBuffSkillIndex",buff,1);
        if(bridge.hasSoundConsumer())method(L"sq_PlaySound",sound,2);
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
