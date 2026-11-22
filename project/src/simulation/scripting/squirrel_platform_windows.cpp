#include "squirrel_host.hpp"
#define NOMINMAX
#include <windows.h>
#include <bcrypt.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace dnf::squirrel_stage {
namespace {
class WindowsServices final : public SourceServices {
  public:
    DecodedText decodeCp936(const Bytes &raw) const override {
        DecodedText decoded;
        for(size_t at=0;at<raw.size();) {
            decoded.byteOffsets.push_back(at);
            const uint8_t lead=raw[at];
            if(lead==0) throw std::runtime_error("NUL in text source at byte "+std::to_string(at));
            size_t count=1;
            if(lead>=0x81 && lead<=0xfe) {
                count=2;
                if(at+1>=raw.size() || raw[at+1]<0x40 || raw[at+1]>0xfe || raw[at+1]==0x7f)
                    throw std::runtime_error("invalid GBK trail at byte "+std::to_string(at));
            } else if(lead>=0x80) throw std::runtime_error("invalid GBK lead at byte "+std::to_string(at));
            wchar_t value=0;
            if(MultiByteToWideChar(936,MB_ERR_INVALID_CHARS,reinterpret_cast<const char*>(raw.data()+at),int(count),&value,1)!=1)
                throw std::runtime_error("unmapped CP936 source at byte "+std::to_string(at));
            char back[4]{};BOOL substituted=FALSE;
            int roundtrip=WideCharToMultiByte(936,WC_NO_BEST_FIT_CHARS,&value,1,back,4,nullptr,&substituted);
            if(substituted || roundtrip!=int(count) || std::memcmp(back,raw.data()+at,count)!=0)
                throw std::runtime_error("non-lossless CP936 source at byte "+std::to_string(at));
            decoded.text.push_back(static_cast<char16_t>(value));
            at+=count;
        }
        decoded.byteOffsets.push_back(raw.size());
        return decoded;
    }
    std::string digest(const Bytes &raw) const override {
        BCRYPT_ALG_HANDLE algorithm=nullptr;BCRYPT_HASH_HANDLE hash=nullptr;
        if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0)
            throw std::runtime_error("SHA256 provider unavailable");
        DWORD bytes=0,size=0;
        if(BCryptGetProperty(algorithm,BCRYPT_OBJECT_LENGTH,reinterpret_cast<PUCHAR>(&size),sizeof(size),&bytes,0)<0) {
            BCryptCloseAlgorithmProvider(algorithm,0);throw std::runtime_error("SHA256 size unavailable");
        }
        Bytes object(size),result(32);
        NTSTATUS status=BCryptCreateHash(algorithm,&hash,object.data(),DWORD(object.size()),nullptr,0,0);
        if(status>=0)status=BCryptHashData(hash,const_cast<PUCHAR>(raw.data()),ULONG(raw.size()),0);
        if(status>=0)status=BCryptFinishHash(hash,result.data(),ULONG(result.size()),0);
        if(hash)BCryptDestroyHash(hash);BCryptCloseAlgorithmProvider(algorithm,0);
        if(status<0)throw std::runtime_error("SHA256 operation failed");
        std::ostringstream output;output<<std::hex<<std::setfill('0');
        for(auto byte:result)output<<std::setw(2)<<unsigned(byte);
        return output.str();
    }
};
}
std::unique_ptr<SourceServices> windowsSourceServices(){return std::make_unique<WindowsServices>();}
} // namespace dnf::squirrel_stage
