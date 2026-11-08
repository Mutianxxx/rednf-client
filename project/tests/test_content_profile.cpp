#include "dnf/content_profile.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runContentProfileTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    auto rejects=[&](auto function,const char *name){bool threw=false;try{function();}catch(const std::exception&){threw=true;}check(threw,name);};
    check(sha256({})=="e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855","SHA-256 empty FIPS vector");
    check(sha256(Bytes{'a','b','c'})=="ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad","SHA-256 abc FIPS vector");
    check(sha256(Bytes(1000000,'a'))=="cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0","SHA-256 multi-block million-a FIPS vector");
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/tests/content-profile")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory/"one/Fonts");
    writeJson(directory/"one/Script.pvf",{{"fixture","bytes used for identity only"}});
    writeJson(directory/"one/Fonts/font.bin",{{"font",1}});
    writeJson(directory/"profile.json",{{"profileId","fixture"},{"pvfPath","one/Script.pvf"},{"resourceRoots",{"one"}}});
    const auto profile=resolveContentProfile(directory/"profile.json","missing",{},directory/"irrelevant-cwd");
    check(profile.pvfPath==directory/"one/Script.pvf"&&profile.resourceRoots.front()==directory/"one","Profile relative paths resolve against config, independently of cwd");
    const auto identity=profile.fingerprint();
    check(identity.manifest.size()==1&&identity.manifest[0]["sha256"]==sha256File(directory/"one/Fonts/font.bin"),"Static manifest records actual bytes and relative member paths");
    std::filesystem::copy(directory/"one",directory/"moved",std::filesystem::copy_options::recursive);
    ContentProfileOverrides moved;moved.pvfPath="moved/Script.pvf";moved.resourceRoots={"moved"};
    const auto relocated=resolveContentProfile(directory/"profile.json","missing",moved,directory);
    check(relocated.fingerprint().contentId==identity.contentId,"Moving PVF and static roots preserves content identity");
    check(relocated.effective(identity)["resolution"].size()==4,"Effective profile records config and both CLI override sources");
    writeJson(directory/"moved/Script.pvf",{{"fixture","changed source bytes"}});
    const auto changedPvf=relocated.fingerprint();
    check(changedPvf.contentId!=identity.contentId&&changedPvf.cacheId!=identity.cacheId,"Actual PVF byte change invalidates content and cache namespaces");
    writeJson(directory/"moved/Fonts/font.bin",{{"font",2}});
    check(relocated.fingerprint().archiveManifestHash!=changedPvf.archiveManifestHash,"Static byte change invalidates manifest independently of PVF");
    auto parserChange=profile;parserChange.parserVersion="next-parser";
    check(parserChange.fingerprint().contentId==identity.contentId&&parserChange.fingerprint().cacheId!=identity.cacheId,"Parser version invalidates derived cache without changing source identity");
    auto rulesChange=profile;rulesChange.ruleProfileId="next-rules";
    check(rulesChange.fingerprint().cacheId!=identity.cacheId,"Rule version invalidates semantic cache");
    rejects([&]{resolveContentProfile(directory/"absent.json",directory/"one");},"Explicit missing profile cannot silently use default client");
    writeJson(directory/"bad.json",{{"pvfPath","one/Script.pvf"},{"resourceRoots",{"one"}},{"textEncoding","guess"}});
    rejects([&]{resolveContentProfile(directory/"bad.json",directory/"one");},"Unknown encoding is rejected explicitly");
    writeJson(directory/"bad.json",{{"pvfPath","one/Script.pvf"},{"resourceRoots",Json::array()}});
    rejects([&]{resolveContentProfile(directory/"bad.json",directory/"one");},"Empty static root list is rejected");
    writeJson(directory/"bad.json",{{"pvfPath","one/Script.pvf"},{"resourceRoots",{"one"}},{"pvfSha256","untrusted"}});
    rejects([&]{resolveContentProfile(directory/"bad.json",directory/"one");},"User-provided digest cannot masquerade as a verified identity");
    const auto script=pvf.script("skill/swordman/guard.skl");
    const auto ref=makeSourceRef(pvf,script.path,script.fields.at(0).offset,5,0,"common");
    check(script.rawBytes==pvf.read(script.path)&&script.source["package_identity"]==pvf.identity(),"Real script retains decrypted bytes and package identity");
    check(ref.memberSha256==sha256(script.rawBytes)&&ref.byteOffset==script.fields[0].offset&&ref.scope=="common","SourceRef binds actual member digest and exact field range");
    rejects([&]{makeSourceRef(pvf,script.path,script.rawBytes.size()+1);},"SourceRef refuses an out-of-range field");
    check(std::filesystem::is_regular_file(assets.staticFile("Fonts/msjh.ttf")),"Loose font consumer resolves through explicit static root");
    rejects([&]{assets.staticFile("../Script.pvf");},"Loose static paths cannot escape root");
    rejects([&]{assets.staticFile("untracked.bin");},"Loose static consumers cannot bypass the fingerprinted content namespaces");
    std::filesystem::create_directories(directory/"two/Fonts");
    writeJson(directory/"two/Fonts/font.bin",{{"font",3}});
    Assets conflicting(std::vector<std::filesystem::path>{directory/"one",directory/"two"},pvf);
    rejects([&]{conflicting.staticFile("Fonts/font.bin");},"Different loose member bytes in multiple roots report ambiguity");
    Assets split(std::vector<std::filesystem::path>{directory/"two",assets.root()},pvf);
    check(std::filesystem::is_regular_file(split.staticFile("audio.xml")),"Loose audio metadata can resolve from a later static root");
    Assets unbound(std::vector<std::filesystem::path>{directory/"one"},pvf);
    check(!unbound.manifestBound(),"Compatibility Assets constructor is explicitly unbound");
    const auto boundRoot=directory/"bound";
    std::filesystem::create_directories(boundRoot/"Fonts");
    std::filesystem::create_directories(boundRoot/"ImagePacks2");
    const auto fontFile=boundRoot/"Fonts/font.bin", archiveFile=boundRoot/"ImagePacks2/fixture.npk";
    auto writeBytes=[&](const std::filesystem::path &path,const Bytes &raw) {
        std::ofstream output(path,std::ios::binary|std::ios::trunc);
        if(!output.write(reinterpret_cast<const char*>(raw.data()),std::streamsize(raw.size())))
            throw std::runtime_error("Cannot write static identity fixture");
    };
    const Bytes originalFont{'f','o','n','t'}, originalPayload{'a','b','c'};
    Bytes archive(284+originalPayload.size(),0);
    const std::string signature="NeoplePack_Bill";
    std::copy(signature.begin(),signature.end(),archive.begin());
    auto u32=[&](size_t at,uint32_t value){for(size_t i=0;i<4;++i)archive[at+i]=uint8_t(value>>(i*8));};
    u32(16,1);u32(20,284);u32(24,uint32_t(originalPayload.size()));
    std::string key="puchikon@neople dungeon and fighter ";
    while(key.size()<255)key+="DNF"[key.size()%3];
    key.resize(256,0);
    const std::string member="sprite/fixture.bin";
    for(size_t i=0;i<256;++i)archive[28+i]=uint8_t((i<member.size()?member[i]:0)^key[i]);
    std::copy(originalPayload.begin(),originalPayload.end(),archive.begin()+284);
    writeBytes(fontFile,originalFont);writeBytes(archiveFile,archive);
    auto boundProfile=profile;boundProfile.resourceRoots={boundRoot};
    const auto boundIdentity=boundProfile.fingerprint();
    Assets bound(std::vector<std::filesystem::path>{boundRoot},pvf,boundIdentity.manifest);
    check(bound.manifestBound()&&bound.staticBytes("Fonts/font.bin")==originalFont&&bound.blob("fixture.bin")==originalPayload,
          "Bound consumers read exact declared loose bytes and a valid indexed NPK member");
    const auto fontTime=std::filesystem::last_write_time(fontFile);
    auto changedFont=originalFont;changedFont[0]='x';writeBytes(fontFile,changedFont);
    std::filesystem::last_write_time(fontFile,fontTime+std::chrono::seconds(2));
    rejects([&]{bound.staticFile("Fonts/font.bin");},"A changed loose file is rehashed after metadata changes and rejected");
    std::filesystem::last_write_time(fontFile,fontTime);
    rejects([&]{bound.staticBytes("Fonts/font.bin");},"Exact-byte API rejects same-size changed content even when its timestamp is restored");
    writeBytes(fontFile,originalFont);std::filesystem::last_write_time(fontFile,fontTime);
    writeBytes(boundRoot/"Fonts/new.bin",originalFont);
    rejects([&]{bound.staticBytes("Fonts/new.bin");},"A loose file introduced after fingerprinting is never consumed under the old identity");
    auto changedArchive=archive;changedArchive.back()='x';
    const auto archiveTime=std::filesystem::last_write_time(archiveFile);
    writeBytes(archiveFile,changedArchive);
    std::filesystem::last_write_time(archiveFile,archiveTime+std::chrono::seconds(2));
    rejects([&]{bound.blob("fixture.bin");},"NPK metadata changes trigger a full archive rehash before later blob reads");
    rejects([&]{Assets changed(std::vector<std::filesystem::path>{boundRoot},pvf,boundIdentity.manifest);},
            "NPK index construction rejects changed archives instead of recording a recoverable parser warning");
    writeBytes(archiveFile,archive);std::filesystem::last_write_time(archiveFile,archiveTime);
    Assets firstRead(std::vector<std::filesystem::path>{boundRoot},pvf,boundIdentity.manifest);
    writeBytes(archiveFile,changedArchive);std::filesystem::last_write_time(archiveFile,archiveTime);
    rejects([&]{firstRead.blob("fixture.bin");},"First NPK blob read rehashes the archive even when index-time metadata is unchanged");
    writeBytes(archiveFile,archive);std::filesystem::last_write_time(archiveFile,archiveTime);
    writeBytes(boundRoot/"ImagePacks2/new.npk",archive);
    rejects([&]{Assets added(std::vector<std::filesystem::path>{boundRoot},pvf,boundIdentity.manifest);},
            "An archive introduced after fingerprinting cannot enter the bound index");
    rejects([&]{Assets invalid(std::vector<std::filesystem::path>{boundRoot},pvf,Json());},
            "Strict manifest constructor rejects a missing manifest rather than becoming unbound");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
            {"scope","Configuration, source identity and static lookup contracts; moved fixtures are not a second real PVF version"},
            {"fixture_directory",directory.u8string()}};
}
} // namespace dnf
