from audit60 import RAW,PE,BASE,off,va,refs,OUT
import struct,json,sys,re
def u32(a): return struct.unpack_from('<I',RAW,off(a))[0]
def readtype(a):
 p=off(a)+8
 return RAW[p:RAW.index(0,p)].decode('ascii','replace')
def locate(descriptor):
 result=[]
 for hit in refs(descriptor):
  if hit['type']!='absolute':continue
  addr=int(hit['va'],16)-12
  try:
   signature,offset,cd,pType,pCHD=struct.unpack_from('<5I',RAW,off(addr))
   if signature!=0 or offset>0x10000 or pType!=descriptor:continue
   for rh in refs(addr):
    if rh['type']!='absolute': continue
    table=int(rh['va'],16)+4
    if not 0x400000<=u32(table)<0xcc0000:continue
    slots={hex(s):hex(u32(table+s)) for s in [0x94,0x98,0x9c,0xc0,0x19c,0x1a0,0x1a4,0x1a8,0x1c8,0x234,0x238,0x23c,0x240,0x2d4,0x2dc,0x310,0x3d8,0x3dc,0x3e8,0x3ec]}
    result.append({'descriptor':hex(descriptor),'type':readtype(descriptor),'COL':hex(addr),'offset':offset,'cdOffset':cd,'vtable':hex(table),'slots':slots})
  except (ValueError,struct.error):continue
 return result
if __name__=='__main__':
 res=locate(int(sys.argv[1],0)); print(json.dumps(res,indent=2))
 (OUT/f'rtti-{int(sys.argv[1],0):08x}.json').write_text(json.dumps(res,indent=2),encoding='utf8')
