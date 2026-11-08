from pathlib import Path
import sys,struct,json,re
sys.path.insert(0,r'D:\dnf\60US\analysis\deps');import pefile
raw=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe').read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
vt=0xd80f94;offset=pe.get_offset_from_rva(vt-base)
for k in range(0,0x800,4):
 ptr=struct.unpack_from('<I',raw,offset+k)[0]
 print(f'{k:03x} {ptr:08x}')
print('RTTI')
for m in re.finditer(rb'\.?AVCN[^\0]{0,35}\x00',raw):
 s=m.group().decode('ascii',errors='replace')
 if any(q.lower() in s.lower() for q in ('Swordman','Fighter','Gunner','Mage','Priest')):print(hex(base+pe.get_rva_from_offset(m.start())),s)
