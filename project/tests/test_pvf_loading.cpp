#include "dnf/content_profile.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
void u32(Bytes &bytes,uint32_t value) {
    for(int i=0;i<4;++i)bytes.push_back(uint8_t(value>>(i*8)));
}
void token(Bytes &bytes,uint8_t type,int32_t value) {bytes.push_back(type);u32(bytes,uint32_t(value));}
Bytes encrypted(Bytes bytes,uint32_t crc) {
    while(bytes.size()%4)bytes.push_back(0);
    for(size_t i=0;i<bytes.size();i+=4) {
        uint32_t word;std::memcpy(&word,bytes.data()+i,4);
        word=((word<<6)|(word>>26))^0x81A79011u^crc;
        std::memcpy(bytes.data()+i,&word,4);
    }
    return bytes;
}
Bytes text(const std::string &value) {return Bytes(value.begin(),value.end());}
void archive(const std::filesystem::path &path,const std::vector<std::pair<std::string,Bytes>> &members) {
    Bytes tree,payload;
    for(size_t i=0;i<members.size();++i) {
        const auto &[name,bytes]=members[i];const uint32_t crc=uint32_t(101+i);
        u32(tree,uint32_t(i));u32(tree,uint32_t(name.size()));tree.insert(tree.end(),name.begin(),name.end());
        u32(tree,uint32_t(bytes.size()));u32(tree,crc);u32(tree,uint32_t(payload.size()));
        const auto data=encrypted(bytes,crc);payload.insert(payload.end(),data.begin(),data.end());
    }
    tree=encrypted(tree,91);
    Bytes bytes;u32(bytes,36);bytes.resize(40,0);u32(bytes,1);u32(bytes,uint32_t(tree.size()));u32(bytes,91);u32(bytes,uint32_t(members.size()));
    bytes.insert(bytes.end(),tree.begin(),tree.end());bytes.insert(bytes.end(),payload.begin(),payload.end());
    std::ofstream stream(path,std::ios::binary);
    if(!stream.write(reinterpret_cast<const char*>(bytes.data()),std::streamsize(bytes.size())))throw std::runtime_error("Cannot write PVF fixture");
}
Json fieldsJson(const std::vector<Field> &fields) {
    Json rows=Json::array();for(const auto &f:fields)rows.push_back({{"tag",f.tag},{"values",f.values},{"offset",f.offset}});return rows;
}
}
Json runPvfLoadingTests() {
    Json checks=Json::array();
    const auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    const auto reject=[&](auto function,const char *name){bool failed=false;try{function();}catch(const std::exception&){failed=true;}check(failed,name);};
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/tests/lazy-pvf")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory);
    const std::vector<std::string> strings={"first.str","second.str","unrelated.str","[name]","NAME","[dungeon]","[unused]","unused-value"};
    Bytes table;u32(table,uint32_t(strings.size()));
    uint32_t offset=uint32_t((strings.size()+1)*4);
    for(const auto &s:strings){u32(table,offset);offset+=uint32_t(s.size());}u32(table,offset);
    for(const auto &s:strings)table.insert(table.end(),s.begin(),s.end());
    Bytes list{0xb0,0xd0};token(list,2,4);token(list,7,0);token(list,2,5);token(list,7,2);token(list,2,4);token(list,7,1);
    Bytes script{0xb0,0xd0};token(script,5,3);token(script,9,4);token(script,10,4);
    token(script,5,5);token(script,2,12);token(script,5,6);token(script,7,7);token(script,5,5);token(script,2,13);
    Bytes badIndex{0xb0,0xd0};token(badIndex,5,6);token(badIndex,7,9999);
    const auto file=directory/"fixture.pvf";
    archive(file,{{"stringtable.bin",table},{"n_string.lst",list},{"first.str",text("NAME>first\r\nOTHER>other\r\n")},
        {"second.str",text("NAME>final\r\n")},{"unrelated.str",text("NAME>unrelated\n")},{"map/sample.map",script},
        {"map/bad-index.map",badIndex},{"map/bad-token.map",Bytes{0xb0,0xd0,5}}});
    Pvf pvf(file);
    check(pvf.reads().size()==2,"Index construction reads only stringtable and translation directory");
    check(pvf.loadingStats()["decoded_strings"]==0&&pvf.loadingStats()["translation_groups_loaded"]==0,
          "String and translation contents remain undecoded after indexing");
    const auto projection=pvf.fieldView("map/sample.map",{"[DUNGEON]"});
    check(projection.fields.size()==2&&projection.fields[0].values==Json::array({12})&&projection.fields[1].values==Json::array({13}),
          "Metadata view preserves case-insensitive selection, duplicate tags, order and values");
    check(projection.fields[0].offset==17&&projection.fields[1].offset==37,"Metadata offsets address original token5 bytes");
    check(projection.selectedTokens.size()==4,"Projection retains only selected original tag/value tokens");
    check(projection.rawBytes==script&&projection.source["member_sha256"]==sha256(script),"Projection retains complete raw bytes and member identity");
    check(pvf.loadingStats()["scripts_cached"]==0,"Metadata view never populates full-script cache");
    check(!pvf.reads().contains("first.str")&&!pvf.reads().contains("second.str")&&!pvf.reads().contains("unrelated.str"),
          "Numeric map metadata never reads unrelated translation bodies");
    const auto full=pvf.script("map/sample.map");
    check(full.text("[name]")=="final","Duplicate translation ids merge in source list order, with last key winning");
    check(full.tokens[2]["value"]=="NAME"&&full.tokens[2]["raw"]==4,"Raw linked token keeps untranslated key and string index");
    check(pvf.reads().contains("first.str")&&pvf.reads().contains("second.str")&&!pvf.reads().contains("unrelated.str"),
          "A type10 link loads its exact translation group only");
    check(pvf.loadingStats()["translation_groups_loaded"]==1,"One requested id publishes one complete translation group");
    const auto selectedName=pvf.fieldView("map/sample.map",{"[name]"});
    check(selectedName.values("[NAME]")==Json::array({"final"}),"Linked values are identical in full parser and projected metadata");
    check(selectedName.source==full.source&&selectedName.rawBytes==full.rawBytes,"Full and projected source provenance agrees");
    check(fieldsJson(pvf.script("map/sample.map").fields)==fieldsJson(full.fields),"Repeated full parse is stable after field views");
    check(pvf.fieldView("map/sample.map",{}).fields.empty(),"Empty metadata selection reads no fields");
    reject([&]{pvf.fieldView("map/bad-index.map",{"[dungeon]"});},"Unselected malformed string index is diagnosed");
    reject([&]{pvf.fieldView("map/bad-token.map",{"[dungeon]"});},"Malformed token5 length is diagnosed before projection");
    reject([&]{pvf.script("missing.skl");},"Missing content remains a concrete error");
    reject([&]{Pvf changed(file,std::string(64,'0'));},"Lazy indexing still verifies the supplied PVF fingerprint");
    auto invalidTable=table;std::fill(invalidTable.begin()+4,invalidTable.begin()+8,0xff);
    archive(directory/"bad-table.pvf",{{"stringtable.bin",invalidTable}});
    reject([&]{Pvf malformed(directory/"bad-table.pvf");},"Every stringtable range is validated during index creation");
    return {{"status","passed"},{"checks",checks},{"count",checks.size()},{"scope","Synthetic source-format edge cases; actual1031 differential probe is separate"}};
}
}
