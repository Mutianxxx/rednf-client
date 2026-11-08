"""Execute the original A24950 pose updater in an isolated synthetic PE32.

Only the pose updater, its two interpolation helpers and truncation helper are
copied. Inputs, clock, key, frame storage and x87 control words are fixtures.
This does not launch or attach to DFO.
"""
from pathlib import Path
import hashlib
import json
import math
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parent/'interpolation'
sys.path.insert(0, str(ROOT/'analysis/deps'))
import pefile

SOURCE = ROOT/'analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe'
SHA = 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
BASE = 0x400000


def u32(value):
    return struct.pack('<I', value & 0xffffffff)


def fbits(value):
    return struct.unpack('<I', struct.pack('<f', value))[0]


def f32(value):
    return struct.unpack('<f', struct.pack('<f', value))[0]


def align(value, n):
    return (value+n-1)//n*n


def fixtures():
    a = dict(position=[-7, -65], rate=[0.2, 0.05], angle=0, rgba=[255,255,255,0])
    b = dict(position=[16, -6], rate=[0.6, 0.6], angle=6.28, rgba=[60,0,255,255])
    rows = [dict(name=name, a=a, b=b, elapsed=elapsed, span=500)
            for name, elapsed in [('before',-1),('start',0),('quarter',125),
                                  ('middle',250),('late',499),('end',500),('after',501)]]
    rows += [dict(name='disabled',a=a,b=b,elapsed=250,span=500,enabled=False),
             dict(name='ended',a=a,b=b,elapsed=250,span=500,ended=True),
             dict(name='last_nonloop',a=a,b=b,elapsed=250,span=500,last=True),
             dict(name='last_loop',a=a,b=b,elapsed=250,span=500,last=True,loop=True),
             dict(name='negative_coordinate_fraction',
                  a=dict(position=[-3,-2],rate=[-2,1],angle=-6.28,rgba=[1,2,3,255]),
                  b=dict(position=[0,1],rate=[2,-1],angle=6.28,rgba=[254,253,252,0]),
                  elapsed=1,span=4)]
    return rows


def expected(case):
    a,b = case['a'],case['b']
    if not case.get('enabled',True) or case.get('ended') or (case.get('last') and not case.get('loop')):
        return dict(a,rate=[f32(v) for v in a['rate']],angle=f32(a['angle']))
    elapsed,span = case['elapsed'],case['span']
    def lerp(x,y):
        x,y=f32(x),f32(y)
        return y if elapsed>=span else x if elapsed<=0 else x+(y-x)*elapsed/span
    return dict(position=[math.trunc(lerp(x,y)) for x,y in zip(a['position'],b['position'])],
                rate=[f32(lerp(x,y)) for x,y in zip(a['rate'],b['rate'])],
                angle=f32(lerp(a['angle'],b['angle'])),
                rgba=[math.trunc(lerp(x,y))&255 for x,y in zip(a['rgba'],b['rgba'])])


def build(raw, cases):
    source=pefile.PE(data=raw)
    code=bytearray();harness=bytearray(0x20000)
    entry=0x401000;state=0x410000;frames=0x411000;output=0x414000
    written=0x418000;cw=0x418010;key=0x10D3EFC;secret=0x12345678
    imports=0x19000;iat=BASE+imports+0xE0
    def emit(data):code.extend(data)
    def push(value):emit(b'\x68'+u32(value))
    def write(address,value):emit(b'\xc7\x05'+u32(address)+u32(value))
    def copy(address,destination):emit(b'\xa1'+u32(address)+b'\xa3'+u32(destination))
    def call(va):emit(b'\xe8'+u32(va-(entry+len(code)+5)))
    def protected(address,value):write(address,(fbits(value)^secret)+address)
    def color(rgba):return sum(v<<(8*i) for i,v in enumerate(rgba))
    record=0
    write(key,secret)
    write(cw,0x027f)
    for precision in (64,53):
        emit(bytes.fromhex('dbe3'))
        if precision==53:emit(b'\xd9\x2d'+u32(cw))
        for c in cases:
            # Initialize only fields read/written by the retained function.
            write(state+0x98,frames);write(state+0x9C,frames+2*0x7C)
            write(state+0x188,0);write(state+0x13A,int(bool(c.get('ended'))))
            write(state+0x130,int(bool(c.get('loop'))))
            write(state+0x124,1 if c.get('last') else 0)
            write(state+0x128,1000);write(state+0x12C,1000+c['span'])
            write(state+0x8C,1000+c['elapsed'])
            for at,style in [(frames+0x7C if c.get('last') else frames,c['a']),
                             (frames if c.get('last') else frames+0x7C,c['b']),
                             (state+0xA8,c['a'])]:
                write(at+8,style['position'][0]);write(at+0xC,style['position'][1])
                protected(at+0x10,style['rate'][0]);protected(at+0x14,style['rate'][1])
                write(at+0x18,fbits(style['angle']));write(at+0x1C,color(style['rgba']))
                write(at+0x20,int(c.get('enabled',True)))
                write(at,0x13572468);write(at+0x28,2)
            emit(b'\xb9'+u32(state));call(0xA24950)
            dest=output+record*32
            copy(state+0xB0,dest);copy(state+0xB4,dest+4)
            for offset,outoff in [(0xB8,8),(0xBC,12)]:
                emit(b'\xa1'+u32(state+offset)+b'\x2d'+u32(state+offset)+b'\x35'+u32(secret)+b'\xa3'+u32(dest+outoff))
            for src,dst in [(0xC0,16),(0xC4,20),(0xA8,24),(0xD0,28)]:copy(state+src,dest+dst)
            record+=1
    push(-11);emit(b'\xff\x15'+u32(iat))
    push(0);push(written);push(record*32);push(output);emit(b'\x50\xff\x15'+u32(iat+4))
    push(0);emit(b'\xff\x15'+u32(iat+8))
    assert len(code)<state-entry
    harness[:len(code)]=code
    blob=bytearray(0x200);dll=imports+0x40;ilt=imports+0xC0
    blob[:20]=struct.pack('<5I',ilt,0,0,dll,imports+0xE0)
    blob[0x40:0x4D]=b'kernel32.dll\0';cursor=imports+0x60
    for i,name in enumerate(['GetStdHandle','WriteFile','ExitProcess']):
        data=b'\0\0'+name.encode()+b'\0';offset=cursor-imports
        blob[offset:offset+len(data)]=data
        for start in [0xC0,0xE0]:blob[start+i*4:start+i*4+4]=u32(cursor)
        cursor=align(cursor+len(data),2)
    harness[imports-0x1000:imports-0x1000+len(blob)]=blob
    fragments=[(b'.integer',0x473000,0x473F20,0x29),
               (b'.pose',0xA24000,0xA24950,0x260),
               (b'.float',0xB09000,0xB099B0,0x2A),
               (b'.trunc',0xC01000,0xC01544,0x75)]
    sections=[(b'.harness',0x1000,harness,0xE0000020)]
    for name,page,va,size in fragments:
        data=bytearray(0x1000);data[va-page:va-page+size]=source.get_data(va-BASE,size)
        sections.append((name,page-BASE,data,0x60000020))
    sections.append((b'.key',0x10D3000-BASE,bytearray(0x1000),0xC0000040))
    headers=bytearray(0x400);headers[:2]=b'MZ';struct.pack_into('<I',headers,0x3C,0x80)
    headers[0x80:0x84]=b'PE\0\0'
    struct.pack_into('<HHIIIHH',headers,0x84,0x14C,len(sections),0,0,0,224,0x103)
    opt=0x98
    struct.pack_into('<HBBIIIIII',headers,opt,0x10B,0,0,0x24000,0x1000,0,0x1000,0x1000,0xCD3000)
    struct.pack_into('<III',headers,opt+28,BASE,0x1000,0x200)
    struct.pack_into('<HHHHHH',headers,opt+40,4,0,0,0,4,0)
    struct.pack_into('<IIIIHH',headers,opt+52,0,0xCD4000,0x400,0,3,0)
    struct.pack_into('<IIIIII',headers,opt+72,0x100000,0x1000,0x100000,0x1000,0,16)
    struct.pack_into('<II',headers,opt+104,imports,40)
    image=bytearray(headers)
    for i,(name,rva,data,flags) in enumerate(sections):
        extent=sections[i+1][1]-rva if i+1<len(sections) else 0x1000
        raw_size=align(len(data),0x200)
        struct.pack_into('<8sIIIIIIHHI',image,0x178+i*40,name,extent,rva,raw_size,len(image),0,0,0,0,flags)
        image.extend(data);image.extend(bytes(raw_size-len(data)))
    pefile.PE(data=image)
    return bytes(image)


def main():
    raw=SOURCE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
    cases=fixtures();image=build(raw,cases);OUT.mkdir(parents=True,exist_ok=True)
    exe=OUT/'native-pose-harness.exe';exe.write_bytes(image)
    run=subprocess.run([str(exe)],capture_output=True,timeout=20,cwd=OUT)
    (OUT/'native-output.bin').write_bytes(run.stdout)
    if run.returncode or len(run.stdout)!=len(cases)*2*32:
        raise RuntimeError(f'harness exit {run.returncode:#x}, output {len(run.stdout)}, {run.stderr!r}')
    rows=[]
    for mode,precision in enumerate((64,53)):
        for index,c in enumerate(cases):
            x,y,rx,ry,angle,color,image_pointer,effect=struct.unpack_from('<iifffIII',run.stdout,(mode*len(cases)+index)*32)
            actual=dict(position=[x,y],rate=[rx,ry],angle=angle,rgba=[(color>>(i*8))&255 for i in range(4)])
            wanted=expected(c)
            rows.append(dict(name=c['name'],precision=precision,inputs=c,expected=wanted,native=actual,
                             discrete_fields_unchanged=image_pointer==0x13572468 and effect==2,
                             matches=actual==wanted and image_pointer==0x13572468 and effect==2))
    report=dict(source_sha256=SHA,kind='full extracted A24950 and helpers in synthetic PE32; not DFO runtime',
                harness_sha256=hashlib.sha256(image).hexdigest(),vectors=rows,
                matches=sum(r['matches'] for r in rows),mismatches=sum(not r['matches'] for r in rows),
                limitations=['Synthetic clock, frames and protection key; runtime x87 state not captured.',
                             'Does not execute parser, frame advancement, rendering or an actual game draw.'])
    (OUT/'native-vectors.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
    print(json.dumps({k:report[k] for k in ('kind','matches','mismatches')}))
    if report['mismatches']:raise SystemExit(1)


if __name__=='__main__':main()
