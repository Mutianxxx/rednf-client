#include "dnf/content_profile.hpp"
#include <iomanip>
#include <limits>
#include <set>
#include <sstream>

namespace dnf {
namespace {
// FIPS 180-4 SHA-256, explicit big-endian loads. No platform structures enter identity.
class Sha256 {
    std::array<uint32_t, 8> h_{0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
                               0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};
    std::array<uint8_t, 64> block_{};
    size_t used_ = 0;
    uint64_t bytes_ = 0;
    static uint32_t rotr(uint32_t x, unsigned n) { return (x >> n) | (x << (32-n)); }
    void compress() {
        static constexpr uint32_t k[64] = {
            0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
            0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
            0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
            0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
            0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
            0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
            0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
            0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
        uint32_t w[64];
        for (unsigned i=0;i<16;++i) w[i]=(uint32_t(block_[i*4])<<24)|(uint32_t(block_[i*4+1])<<16)|
            (uint32_t(block_[i*4+2])<<8)|uint32_t(block_[i*4+3]);
        for (unsigned i=16;i<64;++i) {
            const auto a=w[i-15],b=w[i-2];
            w[i]=w[i-16]+(rotr(a,7)^rotr(a,18)^(a>>3))+w[i-7]+(rotr(b,17)^rotr(b,19)^(b>>10));
        }
        auto a=h_[0],b=h_[1],c=h_[2],d=h_[3],e=h_[4],f=h_[5],g=h_[6],h=h_[7];
        for (unsigned i=0;i<64;++i) {
            const auto t1=h+(rotr(e,6)^rotr(e,11)^rotr(e,25))+((e&f)^(~e&g))+k[i]+w[i];
            const auto t2=(rotr(a,2)^rotr(a,13)^rotr(a,22))+((a&b)^(a&c)^(b&c));
            h=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;
        }
        h_[0]+=a;h_[1]+=b;h_[2]+=c;h_[3]+=d;h_[4]+=e;h_[5]+=f;h_[6]+=g;h_[7]+=h;
    }
  public:
    void add(const uint8_t *data,size_t n) {
        if (n > std::numeric_limits<uint64_t>::max()/8-bytes_) throw std::runtime_error("SHA-256 size limit");
        bytes_+=n;
        while(n) {
            const auto count=std::min(n,block_.size()-used_);
            std::memcpy(block_.data()+used_,data,count); used_+=count; data+=count; n-=count;
            if(used_==block_.size()) {compress();used_=0;}
        }
    }
    std::string finish() {
        const uint64_t bits=bytes_*8;
        block_[used_++]=0x80;
        if(used_>56) {std::fill(block_.begin()+used_,block_.end(),0);compress();used_=0;}
        std::fill(block_.begin()+used_,block_.end(),0);
        for(unsigned i=0;i<8;++i) block_[63-i]=uint8_t(bits>>(i*8));
        compress();
        std::ostringstream out;out<<std::hex<<std::setfill('0');
        for(auto h:h_) out<<std::setw(8)<<h;
        return out.str();
    }
};
std::filesystem::path absoluteFrom(const std::filesystem::path &p,const std::filesystem::path &base) {
    return std::filesystem::absolute(p.is_absolute()?p:base/p).lexically_normal();
}
std::string digestJson(const Json &j) {
    const auto text=j.dump();return sha256(Bytes(text.begin(),text.end()));
}
}
std::string sha256(const Bytes &b) {Sha256 digest;digest.add(b.data(),b.size());return digest.finish();}
std::string sha256File(const std::filesystem::path &path) {
    std::ifstream file(path,std::ios::binary);
    if(!file) throw std::runtime_error("Cannot fingerprint: "+path.u8string());
    Sha256 digest;std::array<uint8_t,1024*64> buffer;
    while(file) {file.read(reinterpret_cast<char*>(buffer.data()),buffer.size());digest.add(buffer.data(),size_t(file.gcount()));}
    if(!file.eof()) throw std::runtime_error("Failed fingerprinting: "+path.u8string());
    return digest.finish();
}
Json SourceRef::json() const {
    return {{"package_identity",packageIdentity},{"member_path",memberPath},{"member_sha256",memberSha256},
            {"encoding",textEncoding},{"byte_offset",byteOffset},{"byte_length",byteLength},
            {"ordinal",ordinal},{"scope",scope},{"literal_path",literalPath}};
}
SourceRef makeSourceRef(const Pvf &pvf,const std::string &path,uint64_t offset,uint64_t length,size_t ordinal,const std::string &scope) {
    const auto raw=pvf.read(path);
    if(offset>raw.size()||length>raw.size()-offset) throw std::runtime_error("SourceRef byte range: "+path);
    const auto literal=pvf.reads().at(normalize(path)).value("literal_path",path);
    return {pvf.identity(),normalize(path),sha256(raw),"CP936",offset,length?length:uint64_t(raw.size()-offset),ordinal,scope,literal};
}
Json ContentIdentity::json() const {
    return {{"content_id",contentId},{"pvf_sha256",pvfSha256},{"archive_manifest_hash",archiveManifestHash},{"cache_id",cacheId}};
}
ContentProfile resolveContentProfile(const std::optional<std::filesystem::path> &config,
    const std::filesystem::path &defaultClient,const ContentProfileOverrides &overrides,const std::filesystem::path &invocationDirectory) {
    ContentProfile result;
    result.pvfPath=absoluteFrom(defaultClient/"Script.pvf",invocationDirectory);
    result.resourceRoots={absoluteFrom(defaultClient,invocationDirectory)};
    result.resolution.push_back({{"source","default_client"},{"path",result.resourceRoots.front().u8string()}});
    if(config) {
        const auto file=absoluteFrom(*config,invocationDirectory);
        const auto document=Json::parse(readFile(file));
        if(!document.is_object()) throw std::runtime_error("Content profile must be an object");
        for(const auto &item:document.items()) {
            static const std::set<std::string> supported={"profileId","pvfPath","resourceRoots","textEncoding","parserVersion","compatibilityProfileId","ruleProfileId"};
            if(!supported.count(item.key())) throw std::runtime_error("Unknown content profile field: "+item.key());
        }
        result.profileId=document.value("profileId",result.profileId);
        result.textEncoding=document.value("textEncoding",result.textEncoding);
        result.parserVersion=document.value("parserVersion",result.parserVersion);
        result.compatibilityProfileId=document.value("compatibilityProfileId",result.compatibilityProfileId);
        result.ruleProfileId=document.value("ruleProfileId",result.ruleProfileId);
        if(document.contains("pvfPath")) result.pvfPath=absoluteFrom(std::filesystem::u8path(document.at("pvfPath").get<std::string>()),file.parent_path());
        if(document.contains("resourceRoots")) {
            if(!document.at("resourceRoots").is_array()) throw std::runtime_error("resourceRoots must be an array");
            result.resourceRoots.clear();
            for(const auto &root:document.at("resourceRoots")) result.resourceRoots.push_back(absoluteFrom(std::filesystem::u8path(root.get<std::string>()),file.parent_path()));
        }
        result.resolution.push_back({{"source","profile"},{"path",file.u8string()}});
    }
    if(overrides.pvfPath) {
        result.pvfPath=absoluteFrom(*overrides.pvfPath,invocationDirectory);
        result.resolution.push_back({{"source","command_line"},{"field","pvfPath"}});
    }
    if(!overrides.resourceRoots.empty()) {
        result.resourceRoots.clear();
        for(const auto &root:overrides.resourceRoots) result.resourceRoots.push_back(absoluteFrom(root,invocationDirectory));
        result.resolution.push_back({{"source","command_line"},{"field","resourceRoots"}});
    }
    if(result.textEncoding!="CP936"&&result.textEncoding!="GBK") throw std::runtime_error("Unsupported content encoding: "+result.textEncoding);
    result.textEncoding="CP936";
    if(result.profileId.empty()||result.parserVersion.empty()||result.compatibilityProfileId.empty()||result.ruleProfileId.empty())
        throw std::runtime_error("Content profile identities must not be empty");
    if(!std::filesystem::is_regular_file(result.pvfPath)) throw std::runtime_error("PVF does not exist: "+result.pvfPath.u8string());
    if(result.resourceRoots.empty()) throw std::runtime_error("At least one static resource root is required");
    std::set<std::filesystem::path> unique;
    for(const auto &root:result.resourceRoots) {
        if(!std::filesystem::is_directory(root)) throw std::runtime_error("Static resource root does not exist: "+root.u8string());
        if(!unique.insert(std::filesystem::weakly_canonical(root)).second) throw std::runtime_error("Duplicate static resource root");
    }
    return result;
}
bool fingerprintedStaticPath(const std::filesystem::path &relative) {
    if (relative.empty() || relative.is_absolute()) return false;
    const auto path = relative.lexically_normal();
    for (const auto &part : path) if (part == "..") return false;
    const auto key = normalize(path.generic_u8string());
    if (key == "audio.xml") return true;
    for (const auto *prefix : {"imagepacks2/", "soundpacks/", "music/", "fonts/", "video/"})
        if (key.rfind(prefix,0) == 0) return true;
    return false;
}
ContentIdentity ContentProfile::fingerprint() const {
    const auto pvfSize=std::filesystem::file_size(pvfPath);
    const auto pvfTime=std::filesystem::last_write_time(pvfPath);
    ContentIdentity result;result.pvfSha256=sha256File(pvfPath);
    if(pvfSize!=std::filesystem::file_size(pvfPath)||pvfTime!=std::filesystem::last_write_time(pvfPath))
        throw std::runtime_error("PVF changed while fingerprinting: "+pvfPath.u8string());
    for(size_t index=0;index<resourceRoots.size();++index) {
        const auto &root=resourceRoots[index];
        std::vector<std::filesystem::path> files;
        if(std::filesystem::is_regular_file(root/"audio.xml")) files.push_back(root/"audio.xml");
        for(const auto *folder:{"ImagePacks2","SoundPacks","Music","Fonts","Video"}) {
            const auto directory=root/folder;
            if(!std::filesystem::exists(directory)) continue;
            for(const auto &entry:std::filesystem::recursive_directory_iterator(directory)) {
                if(entry.is_symlink()) throw std::runtime_error("Static manifest requires resolved roots; symlink: "+entry.path().u8string());
                if(entry.is_regular_file()) files.push_back(entry.path());
            }
        }
        std::sort(files.begin(),files.end(),[&](const auto&a,const auto&b){return a.lexically_relative(root).generic_u8string()<b.lexically_relative(root).generic_u8string();});
        for(const auto &file:files) {
            const auto size=std::filesystem::file_size(file);
            const auto time=std::filesystem::last_write_time(file);
            const auto hash=sha256File(file);
            if(size!=std::filesystem::file_size(file)||time!=std::filesystem::last_write_time(file))
                throw std::runtime_error("Resource changed while fingerprinting: "+file.u8string());
            result.manifest.push_back({{"root",index},{"path",file.lexically_relative(root).generic_u8string()},
                                       {"size",size},{"sha256",hash}});
        }
    }
    result.archiveManifestHash=digestJson(result.manifest);
    result.contentId=digestJson({{"identity_version",1},{"pvf",result.pvfSha256},{"static",result.archiveManifestHash},{"encoding",textEncoding}});
    result.cacheId=digestJson({{"content",result.contentId},{"parser",parserVersion},{"compatibility",compatibilityProfileId},{"rules",ruleProfileId}});
    return result;
}
Json ContentProfile::effective(const ContentIdentity &identity) const {
    Json roots=Json::array();for(const auto &path:resourceRoots) roots.push_back(path.u8string());
    return {{"profileId",profileId},{"pvfPath",pvfPath.u8string()},{"resourceRoots",roots},{"textEncoding",textEncoding},
            {"parserVersion",parserVersion},{"compatibilityProfileId",compatibilityProfileId},{"ruleProfileId",ruleProfileId},
            {"identity",identity.json()},{"resolution",resolution},{"hot_swap_supported",false},
            {"static_manifest_scope",Json::array({"audio.xml","ImagePacks2/**","SoundPacks/**","Music/**","Fonts/**","Video/**"})},
            {"unfingerprinted_loose_file_access","rejected"}};
}
} // namespace dnf
