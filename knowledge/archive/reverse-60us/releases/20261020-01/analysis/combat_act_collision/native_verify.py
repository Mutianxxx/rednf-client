"""Execute original A30D20 and type17 filter in explicit synthetic fixtures."""
from pathlib import Path
import copy
import hashlib
import json
import struct
import subprocess
import sys

DEST=Path(__file__).resolve().parent
sys.path.insert(0,str(DEST.parent/"combat_motion"))
from native_verify import build_harness, original_bytes, SOURCE_HASH, u32, BASE
from collision_model import Condition, Trigger, collision_calls
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ACT, OWNER, TRIGGERS, CONDITIONS, PARAMS=0x408000,0x408400,0x408800,0x409000,0x40a000
CONFIG, COUNT, TRACE, TARGETS, OUTPUT=0x407000,0x407020,0x40b000,0x407040,0x40c000
REQUESTS, LAST_BEHAVIOR=0x407024,0x407028
md=Cs(CS_ARCH_X86,CS_MODE_32);md.skipdata=True


def cases():
    basic=lambda:Trigger([Condition(17),Condition(0,(0,3))])
    result=[]
    def add(name,axis,triggers=None,**kw):
        result.append(dict(name=name,axis=axis,triggers=triggers if triggers is not None else [basic()],**kw))
    for axis in [0,1,2,3,-1]:add(f"default_axis{axis}",axis)
    add("null_owner",0,owner_present=False)
    add("nonlocal_owner",0,local_owner=False)
    add("empty_context",0,context_count=0)
    add("trigger_disabled",0,[Trigger(basic().conditions,enabled18=False)])
    add("trigger_blocked19",0,[Trigger(basic().conditions,blocked19=True)])
    add("limit_reached",0,[Trigger(basic().conditions,count10=2,limit14=2)])
    add("limit_negative_unbounded",0,[Trigger(basic().conditions,count10=7,limit14=-1)])
    add("no_collision_marker_xy",0,[Trigger([Condition(0,(0,7))])])
    add("no_collision_marker_other_axis",3,[Trigger([Condition(0,(0,7))])])
    for axis in [0,1,2]:
        add(f"axis2_selection_event{axis}",axis,[Trigger([Condition(47,(2,)),Condition(17),Condition(0,(0,4))])])
    add("axis_selection_carries_between_triggers",1,[Trigger([Condition(47,(0,))]),basic()])
    add("invalid_selection_keeps_xy",1,[Trigger([Condition(47,(7,)),Condition(17),Condition(0,(0,4))])])
    add("multiple_do_exceeds_limit_in_one_scan",0,[Trigger([Condition(17),Condition(0,(0,1)),Condition(0,(0,2))],limit14=1)])
    for event in [6,9,10,11,12,13,14,15,16]:
        add(f"wrong_event_{event}",0,[Trigger([Condition(event),Condition(17),Condition(0,(0,1))])])
    add("proc33_requires_collision_marker",2,[Trigger([Condition(17),Condition(33,(0,5))])])
    add("proc33_no_marker",0,[Trigger([Condition(33,(0,5))])])
    add("proc49_owner_v108_false",0,[Trigger([Condition(17),Condition(49,(0,6))])])
    add("proc49_owner_v108_true",0,[Trigger([Condition(17),Condition(49,(0,6))])],owner_v108=True)
    add("two_triggers_index_order",1,[basic(),Trigger([Condition(17),Condition(0,(0,8))])])
    return result


def build(values):
    image=bytearray(build_harness([]));pe=pefile.PE(data=image)
    def write(va,data):
        off=pe.get_offset_from_rva(va-BASE);image[off:off+len(data)]=data
    def relocate(va,size,new,calls):
        body=bytearray(original_bytes(va,size))
        for i in md.disasm(body,va):
            if len(i.bytes)==5 and i.bytes[0]==0xe8:
                target=i.address+5+struct.unpack("<i",i.bytes[1:])[0]
                replacement=calls.get(target,0x405000)
                pos=i.address-va
                body[pos+1:pos+5]=u32(replacement-(new+pos+5))
        return body
    # Unexpected dependency execution traps instead of silently succeeding.
    write(0x405000,b"\xcc\xc3")
    write(0x405020,b"\xa1"+u32(CONFIG)+b"\xc3")
    # Explicit append fixture: supplied owner context of length0/1, no allocation.
    write(0x405040,b"\xc7\x41\x04"+u32(TARGETS)+b"\xa1"+u32(CONFIG+4)+b"\x89\x41\x08\xc2\x04\x00")
    write(0x405060,b"\xc3") # fixture free; caller owns stack args
    write(0x405080,b"\xa1"+u32(CONFIG+8)+b"\xc3")
    # Record the A49220 entry, then execute the original selector (target0).
    recorder=(b"\x89\x0d"+u32(CONFIG+0x10)
              +b"\xa1"+u32(COUNT)+b"\xc1\xe0\x04\x05"+u32(TRACE)
              +b"\x8b\x54\x24\x04\x89\x10" # trigger index
              +b"\x8b\x54\x24\x08\x8b\x0a\x89\x48\x04" # kind
              +b"\x8b\x52\x28\x8b\x4a\x08\x89\x48\x08" # literal fixture label
              +b"\x8b\x54\x24\x10\x89\x50\x0c"
              +b"\xff\x05"+u32(COUNT)+b"\x8b\x0d"+u32(CONFIG+0x10))
    recorder+=b"\xe9"+u32(0x405a00-(0x405100+len(recorder)+5))
    write(0x405100,recorder)
    write(0x405180,b"\xff\x05"+u32(REQUESTS)+b"\x8b\x44\x24\x08\xa3"+u32(LAST_BEHAVIOR)+b"\xc2\x10\x00")
    write(0x405800,relocate(0x533100,0x2b,0x405800,{0xa3e780:0x405900}))
    write(0x405900,original_bytes(0xa3e780,0x49))
    write(0x405a00,relocate(0xa49220,0x44f,0x405a00,{0xa3e780:0x405900,0xa2d1c0:0x405e60,
          0x48e4f0:0x405040,0xa48c80:0x405180,0xbfffdd:0x405060}))
    write(0x405e60,relocate(0xa2d1c0,0x13e,0x405e60,{0xa3e780:0x405900,0x533100:0x405800}))
    new=0x50f000
    body=relocate(0xa30d20,0x51e,new,{0x49c090:0x405020,0x48e4f0:0x405040,
         0x533100:0x405800,0xa3e780:0x405900,0xa49220:0x405100,
         0xa4a380:0x50f600,0xbfffdd:0x405060})
    for old,count in [(0xa311e4,10),(0xa3120c,0)]:
        body=bytearray(bytes(body).replace(u32(old),u32(new+old-0xa30d20)))
        for i in range(count):
            off=old-0xa30d20+i*4
            target=struct.unpack_from('<I',body,off)[0]
            struct.pack_into('<I',body,off,new+target-0xa30d20)
    write(new,body)
    write(0x50f600,relocate(0xa4a380,0x183d,0x50f600,{}))
    write(0x406000+0x108,u32(0x405080))
    code=bytearray()
    def emit(v):code.extend(v)
    def setmem(address,value):emit(b"\xc7\x05"+u32(address)+u32(value))
    def push(v):emit(b"\x68"+u32(v))
    def capture(src,dst):emit(b"\xa1"+u32(src)+b"\xa3"+u32(dst))
    width=80
    for index,case in enumerate(values):
        # Clear all fixture state; code, vtable and configuration are separate.
        emit(b"\xbf"+u32(ACT)+b"\x31\xc0\xb9"+u32(0x1000)+b"\xf3\xab")
        setmem(COUNT,0)
        setmem(REQUESTS,0);setmem(LAST_BEHAVIOR,-1)
        setmem(CONFIG,int(case.get('local_owner',True)))
        setmem(CONFIG+4,TARGETS+4*case.get('context_count',1))
        setmem(CONFIG+8,int(case.get('owner_v108',False)))
        setmem(TARGETS,OWNER)
        setmem(OWNER,0x406000)
        setmem(ACT+0x7c,OWNER if case.get('owner_present',True) else 0)
        setmem(ACT+0x90,TRIGGERS)
        setmem(ACT+0x94,TRIGGERS+len(case['triggers'])*0x1c)
        ci=0;pi=0
        for ti,trigger in enumerate(case['triggers']):
            tr=TRIGGERS+ti*0x1c
            setmem(tr+4,CONDITIONS+ci*0x34)
            setmem(tr+8,CONDITIONS+(ci+len(trigger.conditions))*0x34)
            setmem(tr+0x10,trigger.count10);setmem(tr+0x14,trigger.limit14)
            setmem(tr+0x18,int(trigger.enabled18)|(int(trigger.blocked19)<<8))
            for cond in trigger.conditions:
                cr=CONDITIONS+ci*0x34;pr=PARAMS+pi*4
                vals=cond.values
                if cond.kind in (0,33,49):
                    vals=(vals[0],0,vals[1]) # selector0 + scalar literal encoding[0,N]
                setmem(cr,cond.kind);setmem(cr+0x28,pr);setmem(cr+0x2c,pr+len(vals)*4)
                for n,value in enumerate(vals):setmem(pr+n*4,value)
                ci+=1;pi+=len(vals)
        push(0x12345678);push(0x447a0000);push(case['axis'])
        emit(b"\xb9"+u32(ACT))
        emit(b"\xe8"+u32(new-(0x401000+len(code)+5)))
        dst=OUTPUT+index*width
        capture(COUNT,dst)
        capture(TRIGGERS+0x10,dst+4);capture(TRIGGERS+0x1c+0x10,dst+8)
        for n in range(12):capture(TRACE+n*4,dst+12+n*4)
        capture(REQUESTS,dst+72);capture(LAST_BEHAVIOR,dst+76)
    push(-11);emit(b"\xff\x15"+u32(0x40e0e0))
    push(0);push(0x407060);push(len(values)*width);push(OUTPUT)
    emit(b"\x50\xff\x15"+u32(0x40e0e4));push(0);emit(b"\xff\x15"+u32(0x40e0e8))
    assert len(code)<0x4000,len(code)
    write(0x401000,code)
    return bytes(image),width


def main():
    values=cases();image,width=build(values)
    exe=DEST/"native-act-collision-harness.exe";exe.write_bytes(image)
    result=subprocess.run([str(exe)],capture_output=True,timeout=30)
    assert result.returncode==0,(result.returncode,result.stderr)
    assert len(result.stdout)==len(values)*width,len(result.stdout)
    (DEST/"native-output.bin").write_bytes(result.stdout)
    rows=[]
    for index,case in enumerate(values):
        triggers=copy.deepcopy(case['triggers'])
        calls=collision_calls(triggers,case['axis'],**{k:v for k,v in case.items() if k not in ['name','axis','triggers']})
        data=struct.unpack_from('<20i',result.stdout,index*width)
        native_calls=[dict(trigger=data[3+i*4],condition_kind=data[4+i*4],behavior=data[5+i*4],proc_flag=data[6+i*4]) for i in range(data[0])]
        expected=[{k:v for k,v in c.items() if k!='selector'} for c in calls]
        counts=[t.count10 for t in triggers]
        matched=(native_calls==expected and list(data[1:1+len(counts)])==counts
                 and data[18]==len(calls) and data[19]==(calls[-1]['behavior'] if calls else -1))
        rows.append(dict(name=case['name'],axis=case['axis'],expected_calls=expected,native_calls=native_calls,
                         expected_counts=counts,native_counts=list(data[1:1+len(counts)]),
                         native_A48C80_request_count=data[18],native_decoded_last_behavior=data[19],match=matched))
    report=dict(kind="original A30D20 + original A4A380 type17 path + original A49220 selector0 + original A2D1C0 literal decode; synthetic context/locality fixtures and A48C80 recorder; no DFO runtime capture",source_sha256=SOURCE_HASH,
                harness_sha256=hashlib.sha256(image).hexdigest(),output_sha256=hashlib.sha256(result.stdout).hexdigest(),
                matches=sum(r['match'] for r in rows),mismatches=sum(not r['match'] for r in rows),vectors=rows,
                boundaries=["A49220 executes selector0 only; other selector branches unsupported by these fixtures","A48C80 is recorded; native behavior interpreter and message0x33 not executed","Original type17 filter executes; other filter conditions unsupported"])
    (DEST/"native-vectors.json").write_text(json.dumps(report,ensure_ascii=False,indent=2)+"\n",encoding="utf8")
    print(json.dumps(dict(matches=report['matches'],mismatches=report['mismatches'])))
    assert report['mismatches']==0,[r for r in rows if not r['match']]


if __name__=="__main__":main()
