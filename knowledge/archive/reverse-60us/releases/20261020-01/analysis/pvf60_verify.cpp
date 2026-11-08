// Semantic reconstruction from the hash-bound 60US client; not original source.
// Native references: A54E70, A54F80, A55FA0, A570D0. Image base 00400000.
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using Bytes = std::vector<std::uint8_t>;

static std::uint32_t u32(const Bytes& data, std::size_t pos) {
    if (pos > data.size() || data.size()-pos < 4) throw std::runtime_error("truncated u32");
    return std::uint32_t(data[pos]) | std::uint32_t(data[pos+1])<<8 |
           std::uint32_t(data[pos+2])<<16 | std::uint32_t(data[pos+3])<<24;
}

static std::uint32_t crc32(const Bytes& data, std::uint32_t seed) {
    std::uint32_t crc=~seed;
    for (std::uint8_t byte : data) {
        crc ^= byte;
        for (int bit=0; bit<8; ++bit) crc=(crc>>1) ^ ((0u-(crc&1)) & 0xedb88320u);
    }
    return ~crc;
}

// A54E70: native inputs are EAX=expected CRC, ECX=seed,
// stack arguments = expected CRC, buffer pointer, aligned byte length.
static Bytes decrypt_verify(const Bytes& archive, std::size_t pos, std::size_t length,
                            std::uint32_t expected, std::uint32_t seed, std::uint32_t key) {
    if ((length&3) || pos>archive.size() || length>archive.size()-pos)
        throw std::runtime_error("invalid encrypted range");
    Bytes clear(length);
    for (std::size_t i=0; i<length; i+=4) {
        const std::uint32_t v=u32(archive,pos+i)^expected^key;
        const std::uint32_t value=(v>>6)|(v<<26);
        for (int byte=0; byte<4; ++byte) clear[i+byte]=std::uint8_t(value>>(byte*8));
    }
    if (crc32(clear,seed)!=expected) throw std::runtime_error("CRC mismatch");
    return clear;
}

// A54F80 adds the terminating NUL for non-empty paths.
static std::uint32_t path_hash(const std::string& path) {
    std::uint32_t result=0x1505;
    if (path.empty()) return result;
    for (unsigned char byte : path) {
        if (byte>=128) throw std::runtime_error("this sample verifier requires ASCII paths");
        result=result*33+byte;
    }
    return result*33;
}

// B099B0. x87 evaluation/rounding in callers remains a separate concern.
static double interpolate(float first, float last, int progress, int steps) {
    if (progress>=steps) return last;
    if (progress<=0) return first;
    return (double(last)-first)*progress/steps+first;
}

int main(int argc, char** argv) {
    try {
        if (argc<2) throw std::runtime_error("usage: pvf60_verify.exe Script.pvf [key, default 0]");
        const std::uint32_t key=argc>2 ? std::stoul(argv[2],nullptr,0) : 0;
        std::ifstream input(argv[1],std::ios::binary);
        if (!input) throw std::runtime_error("cannot open PVF");
        const Bytes archive((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
        if (u32(archive,0)!=36) throw std::runtime_error("unobserved GUID length");
        const auto version=u32(archive,40), tree_length=u32(archive,44);
        const auto tree_crc=u32(archive,48), count=u32(archive,52);
        const std::size_t data_base=56+std::size_t(tree_length);
        const Bytes tree=decrypt_verify(archive,56,tree_length,tree_crc,count,key);
        std::size_t at=0, verified=0, hash_mismatches=0, duplicate_hashes=0;
        std::unordered_map<std::uint32_t,std::string> seen;
        for (std::uint32_t i=0; i<count; ++i) {
            const auto hash=u32(tree,at), name_length=u32(tree,at+4);
            at+=8;
            if (name_length>4096 || at>tree.size() || name_length>tree.size()-at)
                throw std::runtime_error("invalid path range");
            const std::string name(reinterpret_cast<const char*>(tree.data()+at),name_length);
            at+=name_length;
            const auto size=u32(tree,at), crc=u32(tree,at+4), relative=u32(tree,at+8);
            at+=12;
            if (path_hash(name)!=hash) ++hash_mismatches;
            if (!seen.emplace(hash,name).second) ++duplicate_hashes;
            decrypt_verify(archive,data_base+relative,(std::size_t(size)+3)&~std::size_t(3),crc,hash,key);
            ++verified;
        }
        std::cout << "{\"version\":" << version << ",\"files_verified\":" << verified
                  << ",\"path_hash_mismatches\":" << hash_mismatches
                  << ",\"duplicate_hashes\":" << duplicate_hashes
                  << ",\"parsed_tree_bytes\":" << at << ",\"tree_bytes\":" << tree.size()
                  << ",\"tree_crc_verified\":true,\"key\":" << key << "}\n";
        return hash_mismatches ? 2 : 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
