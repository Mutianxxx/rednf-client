import sys,struct,re,json
from audit60 import RAW, va, refs, off, MD
if sys.argv[1]=='epsilon':
 for fmt,num in [('<d',2**-23),('<f',2**-23),('<d',1e-7),('<f',1e-7)]:
  pat=struct.pack(fmt,num)
  for m in re.finditer(re.escape(pat),RAW):
   address=va(m.start()); hits=refs(address)
   print(fmt,num,hex(address),hits)
if sys.argv[1]=='calls':
 addr=int(sys.argv[2],0); size=int(sys.argv[3],0)
 for i in MD.disasm(RAW[off(addr):off(addr)+size],addr):
  if i.mnemonic in ['call','jmp']: print(hex(i.address),i.mnemonic,i.op_str)
if sys.argv[1]=='pattern':
 pat=bytes.fromhex(sys.argv[2])
 for m in re.finditer(re.escape(pat),RAW): print(hex(va(m.start())))
if sys.argv[1]=='vtable':
 addr=int(sys.argv[2],0); count=int(sys.argv[3],0)
 for index in range(count): print(f'{index*4:03x} {struct.unpack_from("<I",RAW,off(addr)+index*4)[0]:08x}')
if sys.argv[1]=='strings':
 addr=int(sys.argv[2],0); data=RAW[off(addr):off(addr)+int(sys.argv[3],0)]
 print(data.hex()); print(data.decode('ascii','replace'));print(data.decode('utf-16-le','replace'))
if sys.argv[1]=='mem':
 addr=int(sys.argv[2],0)
 pat=struct.pack('<I',addr)
 for m in re.finditer(re.escape(pat),RAW):
  p=m.start(); before=RAW[max(0,p-0x4000):p]
  starts=[v.start() for v in re.finditer(b'\x55\x8b\xec',before)]
  if not starts: continue
  f=max(0,p-0x4000)+starts[-1]
  ins=[i for i in MD.disasm(RAW[f:p+0x30],va(f)) if i.address<=va(p)<i.address+i.size]
  if ins: print(hex(va(f)),hex(va(p)),str([(i.mnemonic,i.op_str) for i in ins]))
