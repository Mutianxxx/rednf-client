"""Execute extracted arithmetic in a synthetic PE32; never launch DFO.

Uses the PE32 harness technique already validated in combat_reaction_motion.
Original 8B7AB0/8B7C90 and 8B8808..8B8B41 instructions retain their VAs.
Protected getters, RNG, context factors and victim.slot320 are declared stubs.
"""
from pathlib import Path
import sys,struct,json,hashlib,subprocess
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT.parent/'combat_spawned_object'))
from static_evidence import chunk,SHA256
from numeric_model import defense_ratio,critical_stage,bounded,f32,sf
import pefile

def u32(x):return struct.pack('<I',int(x)&0xffffffff)
def bits(x):return struct.unpack('<I',struct.pack('<f',float(x)))[0]
def align(x,a):return (x+a-1)//a*a
def fv(x):return float(sf(x))
FLOATS='6 f 13 17 1b 1f 23 27 37 3b 3f 43 4b 4f 53 57 5b 5f 6b 6f 93 9f a3 a7 ab bf'.split()
BYTES='4 5 e 18a 18b 18e 1b5 1bc 1c1 1a6 c3 c4 c5'.split()
INTS='63 67 8b 8f 97 9b af b3 b7 bb 195 199 1ac 1c2'.split()
GLOBALS={'10bfeb0':100,'10bfed0':100,'10bfea8':10,'10bfeb8':10,'10bfee0':10,'10bfe80':10,'10bfe90':1.5}
NUM,FRAME,ATTACKER,VICTIM,VTABLE=0x10dc000,0x10dd000,0x10de000,0x10df000,0x10e0000
OUTPUT,CTX,MODEOBJ,SCRATCH=0x10e1000,0x10e3000,0x10e5000,0x10e6000

def template(kind=1):
 n={'numeric_'+x:0 for x in FLOATS+BYTES+INTS}
 n.update(numeric_5=kind,numeric_18b=50,numeric_195=0x111,numeric_199=0x11,
          numeric_1b=100,numeric_1ac=100,numeric_5f=1,numeric_6b=1,numeric_6f=1)
 ext={'protected_global_'+x:y for x,y in GLOBALS.items()}
 for i in range(11):
  ext['448c10_attacker_'+str(i)]=1;ext['448c10_victim_'+str(i)]=1
 ext.update(mode6_table_level=60,mode7_table_level=70,
            **{'8ae160_return':9999},victim_slot320_does_not_mutate_numeric_snapshot=True)
 return n,ext

def cases():
 rows=[]
 def add(kind,n,e,b=552,label=''):rows.append(dict(kind=kind,numeric=n,external=e,incoming=b,label=label))
 for kind in (0,1):
  for level in (-128,-1,0,1,9,10,50,127):
   for amount in (-1000,-10,0,1,1000):
    n,e=template(kind);n['numeric_18b']=level;n['numeric_8b' if kind==0 else 'numeric_97']=amount
    add('defense',n,e,label='signed level/defense')
  for mode in (4,6,7):
   n,e=template(kind);n.update(numeric_18a=mode,numeric_18b=1,numeric_1bc=1)
   n['numeric_8b' if kind==0 else 'numeric_97']=1234
   n['numeric_8f' if kind==0 else 'numeric_9b']=17
   n['numeric_93' if kind==0 else 'numeric_9f']=23.5
   e['448c10_victim_1']=fv(.1234567)
   add('defense',n,e,label='mode level table and denominator double')
 for rng in (-2147483648,-1,0,299,300,301,9999,10000,2147483647):
  n,e=template();e['8ae160_return']=rng;add('critical',n,e,label='strict threshold and signed IDIV')
 for kind in (0,1,2):
  for flags,alternate,back in [(0,0,0),(0x11,0,0),(0x81,1,0),(0x111,0,1),(0x81,1,1)]:
   n,e=template(kind);n.update(numeric_195=flags,numeric_18e=alternate,numeric_1b5=back,
    numeric_13=1.25,numeric_17=3.25,numeric_4b=4.75,numeric_4f=5.5,
    numeric_53=6.25,numeric_57=7.5,numeric_5b=9.5,numeric_bf=1.75,numeric_6f=1.25)
   e['8ae160_return']=499;add('critical',n,e,label='rate contributors')
 for rate,rng in [(-10,-1),(-3,0),(97,9999),(150,9999),(0,299)]:
  n,e=template();n['numeric_13']=rate;e['8ae160_return']=rng
  add('critical',n,e,label='no rate clamp')
 for kind in (0,1,2):
  for variant in range(9):
   n,e=template(kind)
   n.update(numeric_8b=1000,numeric_97=2000,numeric_8f=5,numeric_9b=10,numeric_93=2,numeric_9f=3,
    numeric_3f=10,numeric_43=20,numeric_a3=30,numeric_a7=40,numeric_f=50,
    numeric_6=10,numeric_37=20,numeric_3b=30,numeric_4=1,numeric_63=100,numeric_67=150,
    numeric_ab=.5,numeric_af=12,numeric_b3=14,numeric_b7=3,numeric_bb=5,numeric_bf=2)
   b=552
   if variant==1:n['numeric_e']=1
   if variant==2:n['numeric_199']=0
   if variant==3:n['numeric_18a']=4
   if variant==4:n.update(numeric_1c1=1,numeric_1c2=0xB3B2)
   if variant==5:
    n.update(numeric_1a6=1,numeric_c3=1,numeric_c4=1,numeric_c5=1,
     numeric_1f=111,numeric_23=79,numeric_27=50,numeric_6b=.8,numeric_1b=135,numeric_1ac=70)
    e['8ae160_return']=0
   if variant==6:b=-1000
   if variant==7:n.update(numeric_1b=0,numeric_199=0)
   if variant==8:
    e['448c10_victim_1']=fv(.9);e['448c10_victim_6']=fv(1.25)
    e['448c10_attacker_5']=fv(.8);e['448c10_attacker_9']=fv(.75)
    e['448c10_victim_10']=fv(.6)
   add('bounded',n,e,b,label='consumer variant '+str(variant))
 return rows

def build(rows):
 first=bytearray(0x32000);flt=bytearray(0x1000);factor=bytearray(0x1000)
 native=bytearray(0xb000);trunc=bytearray(0x1000)
 copies=[(0x8B7AB0,0x13B),(0x8B7C90,0x194),(0x8B8808,0x339),(0xC01544,0x75)]
 for va,size in copies:
  dest,start=(trunc,0xc01000) if va==0xc01544 else (native,0x8ae000)
  dest[va-start:va-start+size]=chunk(va,size)[0]
 flt[0x3b0:0x3b3]=bytes.fromhex('d901c3')
 factor[0xc10:0xc1d]=bytes.fromhex('8b4424048b542408d9449020c3')
 native[0x160:0x166]=b'\xa1'+u32(SCRATCH+0x80)+b'\xc3' # declared RNG return
 end=b'\xd9\x1d'+u32(SCRATCH+4)+b'\xc3'
 native[0xaB41:0xaB41+len(end)]=end # stop after bounded fragment
 first[0x100:0x103]=bytes.fromhex('c20400') # victim.slot320 callback no-op
 constants=[]
 for base,addresses in [(0xcc1000,[0xcc10ac,0xcc1f58]),(0xccb000,[0xccb578,0xccb9d8]),
                         (0xd5a000,[0xd5a848]),(0xdf5000,[0xdf5190]),(0xe9d000,[0xe9d7a4])]:
  data=bytearray(0x1000)
  for va in addresses:data[va-base:va-base+4]=chunk(va,4)[0]
  constants.append((base,data))
 import_rva,dll,names,ilt,iat=0x3000,0x3040,0x3060,0x30c0,0x30e0
 imp=bytearray(0x200);imp[:20]=struct.pack('<5I',ilt,0,0,dll,iat);imp[0x40:0x4d]=b'kernel32.dll\0'
 imported=['GetStdHandle','WriteFile','ExitProcess'];cursor=names
 for i,name in enumerate(imported):
  data=b'\0\0'+name.encode()+b'\0';imp[cursor-import_rva:cursor-import_rva+len(data)]=data
  for target in (ilt,iat):imp[target-import_rva+i*4:target-import_rva+i*4+4]=u32(cursor)
  cursor=align(cursor+len(data),2)
 first[import_rva-0x1000:import_rva-0x1000+len(imp)]=imp
 first[0x200:0x202]=struct.pack('<H',0x027f)
 entry,code,record=0x404000,bytearray(),0
 def emit(data):code.extend(data)
 def push(x):emit(b'\x68'+u32(x))
 def mem(a,x):emit(b'\xc7\x05'+u32(a)+u32(x))
 def byte(a,x):emit(b'\xc6\x05'+u32(a)+bytes([int(x)&255]))
 def call(a):emit(b'\xe8'+u32(a-(entry+len(code))-5))
 def capture(a,d):emit(b'\xa1'+u32(a)+b'\xa3'+u32(d))
 mem(VICTIM,VTABLE);mem(VTABLE+0x320,0x401100)
 mem(0x1002848,CTX);mem(CTX+0x1060,MODEOBJ);mem(CTX+0x1064,MODEOBJ)
 mem(MODEOBJ+0x74,0);mem(MODEOBJ+0x80,0)
 mem(0x10da440,0x10da800);mem(0x10da128,0x10da900)
 for precision in (64,53):
  for row in rows:
   emit(bytes.fromhex('dbe3'))
   if precision==53:emit(b'\xd9\x2d'+u32(0x401200))
   emit(b'\xbf'+u32(NUM)+b'\x31\xc0\xb9'+u32(0x80)+b'\xf3\xab')
   for key in FLOATS:
    if row['numeric']['numeric_'+key]:mem(NUM+int(key,16),bits(row['numeric']['numeric_'+key]))
   for key in BYTES:
    if row['numeric']['numeric_'+key]:byte(NUM+int(key,16),row['numeric']['numeric_'+key])
   for key in INTS:
    if row['numeric']['numeric_'+key]:mem(NUM+int(key,16),row['numeric']['numeric_'+key])
   ex=row['external']
   for key in GLOBALS:mem(int(key,16),bits(ex['protected_global_'+key]))
   for which,addr in [('attacker',ATTACKER),('victim',VICTIM)]:
    for index in range(1,11):mem(addr+0x20+4*index,bits(ex['448c10_'+which+'_'+str(index)]))
   mem(0x10da802,ex['mode6_table_level']);mem(0x10da902,ex['mode7_table_level'])
   mem(SCRATCH+0x80,ex['8ae160_return'])
   dest=OUTPUT+record*24
   if row['kind']=='defense':
    push(VICTIM);push(NUM);push(SCRATCH+4);push(SCRATCH);call(0x8b7c90);emit(bytes.fromhex('83c410'))
    capture(SCRATCH,dest);capture(SCRATCH+4,dest+4)
   elif row['kind']=='critical':
    mem(SCRATCH,bits(row['incoming']));push(SCRATCH+0x84);push(SCRATCH);push(NUM)
    call(0x8b7ab0);emit(bytes.fromhex('83c40c0fb6c0')+b'\xa3'+u32(dest+8))
    capture(SCRATCH,dest);emit(b'\x0f\xb6\x05'+u32(NUM+0x1a5)+b'\xa3'+u32(dest+12))
   else:
    mem(FRAME+8,bits(row['incoming']))
    emit(bytes.fromhex('55565753')+b'\xbd'+u32(FRAME)+b'\xbe'+u32(NUM)+b'\xbf'+u32(VICTIM)+b'\xbb'+u32(ATTACKER))
    start=0x8b8808 if row['numeric']['numeric_199']&0x11==0x11 else 0x8b88bf
    call(start);emit(bytes.fromhex('5b5f5e5d'))
    capture(FRAME+8,dest);capture(SCRATCH+4,dest+4)
    emit(b'\x0f\xb6\x05'+u32(NUM+0x1a5)+b'\xa3'+u32(dest+8))
    capture(NUM+0x1a7,dest+12)
   record+=1
 push(-11);emit(b'\xff\x15'+u32(0x400000+iat))
 push(0);push(SCRATCH+0x88);push(record*24);push(OUTPUT)
 emit(b'\x50\xff\x15'+u32(0x400000+iat+4));push(0);emit(b'\xff\x15'+u32(0x400000+iat+8))
 assert entry+len(code)<0x433000,hex(len(code))
 first[entry-0x401000:entry-0x401000+len(code)]=code
 starts=[(0x401000,first,0xe0000020),(0x433000,flt,0x60000020),(0x448000,factor,0x60000020),
  (0x8ae000,native,0x60000020),(0xc01000,trunc,0x60000020)]+[(a,b,0xc0000040) for a,b in constants]+[
  (0x1002000,bytearray(0x1000),0xc0000040),(0x10bf000,bytearray(0x1000),0xc0000040),
  (0x10da000,bytearray(0x1000),0xc0000040),(0x10db000,bytearray(0xd000),0xc0000040)]
 headers=bytearray(0x600);headers[:2]=b'MZ';struct.pack_into('<I',headers,0x3c,0x80);headers[0x80:0x84]=b'PE\0\0'
 struct.pack_into('<HHIIIHH',headers,0x84,0x14c,len(starts),0,0,0,224,0x0103)
 opt=0x98;image_end=starts[-1][0]+len(starts[-1][1])
 struct.pack_into('<HBBIIIIII',headers,opt,0x10b,0,0,0x40000,0x10000,0,entry-0x400000,0x1000,0xcc1000-0x400000)
 struct.pack_into('<III',headers,opt+28,0x400000,0x1000,0x200)
 struct.pack_into('<HHHHHH',headers,opt+40,4,0,0,0,4,0)
 struct.pack_into('<IIIIHH',headers,opt+52,0,image_end-0x400000,0x600,0,3,0)
 struct.pack_into('<IIIIII',headers,opt+72,0x100000,0x1000,0x100000,0x1000,0,16)
 struct.pack_into('<II',headers,opt+104,import_rva,40)
 out=bytearray(headers)
 for i,(va,data,flags) in enumerate(starts):
  virtual_end=starts[i+1][0] if i+1<len(starts) else image_end
  assert va+align(len(data),0x1000)<=virtual_end
  size=align(len(data),0x200);offset=len(out)
  struct.pack_into('<8sIIIIIIHHI',out,0x178+i*40,('.s'+str(i)).encode(),virtual_end-va,va-0x400000,size,offset,0,0,0,0,flags)
  out.extend(data);out.extend(b'\0'*(size-len(data)))
 checked=pefile.PE(data=out);assert [x.name.decode() for x in checked.DIRECTORY_ENTRY_IMPORT[0].imports]==imported
 return bytes(out),copies

def main():
 rows=cases();image,copies=build(rows);exe=ROOT/'native-numeric-harness.exe';exe.write_bytes(image)
 run=subprocess.run([str(exe)],cwd=ROOT,capture_output=True,timeout=20)
 (ROOT/'native-output.bin').write_bytes(run.stdout)
 if run.returncode or len(run.stdout)!=len(rows)*2*24:
  raise RuntimeError(f'exit {run.returncode:#x}, output {len(run.stdout)} / {len(rows)*2*24}, stderr {run.stderr!r}')
 vectors=[];record=0
 for precision in (64,53):
  for row in rows:
   raw=run.stdout[record*24:record*24+24];record+=1
   native=struct.unpack('<ffII',raw[:16]);kind=row['kind'];n=row['numeric'];e=row['external'];b=row['incoming']
   if kind=='defense':
    expected=defense_ratio(n,e,precision=precision)
    match=raw[:8]==struct.pack('<ff',expected['ratio_f32'],expected['extra_f32'])
   elif kind=='critical':
    expected=critical_stage(b,n,e,precision=precision)
    match=raw[:4]==struct.pack('<f',expected['value_f32']) and native[2]==native[3]==expected['numeric_1a5']
   else:
    expected=bounded(b,n,e,precision=precision)
    match=raw[:8]==struct.pack('<ff',expected['stored_f32'],expected['value_f32']) and native[2]==expected['numeric_1a5'] and native[3]==(expected['numeric_1a7'] or 0)&0xffffffff
   vectors.append(dict(**row,x87_precision=precision,native=dict(stored_f32=native[0],stack_f32_or_extra=native[1],flag=native[2],integer=native[3]),model=expected,matches=match))
 report=dict(schema='60us-common-numeric-native-fixtures-v1',source_sha256=SHA256,
  original_client_runtime=False,evidence_kind='original instruction arithmetic with explicit fixture providers in independently generated PE32',
  harness_sha256=hashlib.sha256(image).hexdigest(),output_sha256=hashlib.sha256(run.stdout).hexdigest(),
  extracted_bodies=[dict(va=hex(a),size=s,sha256=hashlib.sha256(chunk(a,s)[0]).hexdigest()) for a,s in copies],
  matches=sum(x['matches'] for x in vectors),mismatches=sum(not x['matches'] for x in vectors),vectors=vectors,
  stubs=['4333B0 decoded float fld [ecx]','448C10 explicit actor/target factor array','8AE160 explicit signed return, seed not evolved','victim.slot320 no-op','8B8B41 fixture stop and capture'],
  limitations=['No DFO launch, game runtime observation, final 8B8650 integer, final HP update, element or pre-defense random stage.','53/64 significand settings are fixture choices; client control word remains unknown.'])
 (ROOT/'native-vectors.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
 print(json.dumps({k:report[k] for k in ('matches','mismatches','original_client_runtime')}))
 failures=[v for v in vectors if not v['matches']]
 if failures:
  print(json.dumps(failures[:3],indent=2,ensure_ascii=False));raise SystemExit(1)

if __name__=='__main__':main()
