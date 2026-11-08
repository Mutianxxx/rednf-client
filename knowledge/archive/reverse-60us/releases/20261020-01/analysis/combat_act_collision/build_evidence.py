"""Read current client and PVF; export evidence only into this directory."""
from pathlib import Path
import hashlib
import json
import re
import struct
import sys

DEST = Path(__file__).resolve().parent
ROOT = DEST.parents[1]
sys.path.insert(0, str(ROOT / "analysis/deps"))
sys.path.insert(0, str(ROOT / "analysis"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from pvf60 import Pvf60

HASH = "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
PVF_HASH = "23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98"
RANGES = [
    ("owner_forward", 0x4e8a30, 0x43),
    ("current_act_install", 0x499f10, 0x8b),
    ("current_act_wrapper", 0x4e9480, 0x57),
    ("secondary_monster_construct", 0x501cd3, 0xa6),
    ("parse_proc_action", 0x88c8ad, 0x33),
    ("action_constructor", 0x4a3900, 0x166),
    ("action_owner_set", 0xa2d020, 0xd),
    ("scalar_parameter_decode", 0xa2d1c0, 0x13e),
    ("scalar_literal_encode", 0xa3f0a4, 0x19),
    ("action_install_helper", 0xa2d790, 0x1a0),
    ("collision_consumer_and_tables", 0xa30d20, 0x51e),
    ("int_parameter_get", 0x533100, 0x2b),
    ("vector_index", 0xa3e780, 0x49),
    ("trigger_reset", 0xa48250, 0x4b),
    ("parse_move_collision", 0xa45c72, 0x27),
    ("parse_axis_index", 0xa46a31, 0x3f),
    ("parse_do_behavior_match", 0xa4541a, 0x1c),
    ("parse_do_behavior_target", 0xa46bb7, 0x15f),
    ("parse_condition_append", 0xa46d28, 0x3d),
    ("behavior_target_selector", 0xa49220, 0x44f),
    ("behavior_request", 0xa48c80, 0x189),
    ("actor_behavior_route", 0x4ac850, 0x284),
    ("base_behavior_route", 0x49a0a0, 0x30),
    ("behavior_interpreter_entry", 0xa36050, 0x85),
    ("condition_filter", 0xa4a380, 0x183d),
]


def main():
    DEST.mkdir(exist_ok=True)
    raw = (ROOT / "DFO/DFO_fixed_v3.exe").read_bytes()
    assert hashlib.sha256(raw).hexdigest() == HASH
    pe = pefile.PE(data=raw)
    base = pe.OPTIONAL_HEADER.ImageBase
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.skipdata = True
    def at(va, size):
        off = pe.get_offset_from_rva(va-base)
        return off, raw[off:off+size]
    def u32(va):
        return struct.unpack("<I", at(va,4)[1])[0]
    excerpts=[]
    for name, va, size in RANGES:
        off, body=at(va,size)
        stem=f"{va:08x}-{name}"
        (DEST/(stem+".bin")).write_bytes(body)
        (DEST/(stem+".asm")).write_text("\n".join(f"{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}" for i in md.disasm(body,va))+"\n",encoding="utf8")
        excerpts.append(dict(name=name,va=hex(va),file_offset=off,size=size,sha256=hashlib.sha256(body).hexdigest(),binary=stem+".bin",assembly=stem+".asm"))
    vt=0xccefd0
    col=u32(vt-4)
    descriptor=u32(col+12)
    rtti=at(descriptor+8,100)[1].split(b"\0",1)[0].decode("ascii")
    literals=[]
    for va in [0xe4712c,0xe47484,0xe4745c,0xe22f5c,0xe46c40,0xe22a84]:
        off,body=at(va,128)
        end=next(i for i in range(0,len(body),2) if body[i:i+2]==b"\0\0")
        literals.append(dict(va=hex(va),file_offset=off,text=body[:end].decode("utf-16-le"),bytes=body[:end+2].hex()))
    mappings=[]
    for kind in range(50):
        index=at(0xa3120c+kind,1)[1][0]
        mappings.append(dict(kind=kind,index=index,target=hex(u32(0xa311e4+index*4))))
    rea=[]
    for name in ["097-act-collision","098-act-install-helper","105-act-behavior-dispatch","106-act-target-selector"]:
        paths=list((ROOT/"analysis/rea/results").glob(name+".json"))
        for p in paths:
            doc=json.loads(p.read_text(encoding="utf8"));found=[]
            def walk(v):
                if isinstance(v,dict):
                    if isinstance(v.get("pseudocode"),str):found.append(v["pseudocode"])
                    for c in v.values():walk(c)
                elif isinstance(v,list):
                    for c in v:walk(c)
            walk(doc)
            if found:
                (DEST/(name+".c")).write_text(found[0],encoding="utf8")
                rea.append(dict(source="../rea/results/"+p.name,sha256=hashlib.sha256(p.read_bytes()).hexdigest(),pseudocode=name+".c"))
    pvf=Pvf60(ROOT/"DFO/Script.pvf")
    assert hashlib.sha256(pvf.data).hexdigest()==PVF_HASH
    resources=[];scanned=0
    out=DEST/"pvf";out.mkdir(exist_ok=True)
    for entry in pvf.entries:
        if not entry["path"].endswith(".act"):continue
        scanned+=1
        content=pvf.read(entry["path"])
        if b"[on move collision]" not in content.lower():continue
        name=entry["path"].replace("/","__")
        (out/name).write_bytes(content)
        # Preserve original bytes. The parser-facing ASCII tags are unaffected
        # by the legacy comment encoding; report exact selected line numbers.
        text=content.decode("cp949",errors="replace")
        lines=text.splitlines()
        tags=[dict(line=i+1,text=line) for i,line in enumerate(lines) if "[ON MOVE COLLISION]" in line.upper()]
        resources.append(dict(entry,raw="pvf/"+name,sha256=hashlib.sha256(content).hexdigest(),display_encoding="cp949 with replacement for comments; raw authoritative",collision_tags=tags,text=text))
    owners=[]
    for name in ["monster/newmonsters/lizardman/avengers/megaira/body.mob","monster/newmonsters/goblinkingdom/golgo/golgo.mob"]:
        content=pvf.read(name);filename=name.replace("/","__");(out/filename).write_bytes(content)
        owners.append(dict(pvf.by_path[name],raw="pvf/"+filename,sha256=hashlib.sha256(content).hexdigest(),
                           notes="Raw owner resource only; commented alternatives are not marked active by this exporter."))
    result=dict(schema="60US-act-collision-evidence/1",source_sha256=HASH,pvf_sha256=PVF_HASH,image_base=hex(base),
                excerpts=excerpts,dynamic_class=dict(vtable=hex(vt),col=hex(col),descriptor=hex(descriptor),rtti=rtti,
                slots={hex(s):hex(u32(vt+s)) for s in range(0,0x20,4)}),literals=literals,
                condition_dispatch=mappings,rea_support=rea,pvf_act_scanned=scanned,pvf_resources=resources,pvf_owner_resources=owners,
                runtime_observed=False,cautions=["Enclosing static excerpts are not all asserted function body sizes.","Only selected collision trigger branches have executable model coverage."])
    (DEST/"evidence.json").write_text(json.dumps(result,ensure_ascii=False,indent=2)+"\n",encoding="utf8")
    print(json.dumps(dict(excerpts=len(excerpts),rea_support=len(rea),act_scanned=scanned,collision_resources=len(resources),rtti=rtti)))


if __name__=="__main__":main()
