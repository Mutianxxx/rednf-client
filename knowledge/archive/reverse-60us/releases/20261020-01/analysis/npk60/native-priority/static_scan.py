from pathlib import Path
import sys,struct,re,json,hashlib
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
root=Path(r'D:\dnf\60US\analysis\npk60\native-priority');source=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe');raw=source.read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase;md=Cs(CS_ARCH_X86,CS_MODE_32);md.skipdata=True
mode=sys.argv[1]
if mode=='save':
 start=int(sys.argv[2],0);length=int(sys.argv[3],0);offset=pe.get_offset_from_rva(start-base);chunk=raw[offset:offset+length];name=f'{start:08X}-{start+length:08X}'
 (root/(name+'.bin')).write_bytes(chunk)
 (root/(name+'.asm')).write_text('\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(chunk,start)),encoding='utf8')
 record={'source':str(source),'source_sha256':hashlib.sha256(raw).hexdigest(),'start_va':start,'length':length,'rva':start-base,'file_offset':offset,'chunk_sha256':hashlib.sha256(chunk).hexdigest()}
 (root/(name+'.json')).write_text(json.dumps(record,indent=2),encoding='utf8');print(name)
elif mode=='refs':
 target=int(sys.argv[2],0);rows=[]
 for m in re.finditer(re.escape(struct.pack('<I',target)),raw):rows.append({'kind':'absolute','va':base+pe.get_rva_from_offset(m.start()),'file_offset':m.start(),'context':raw[max(0,m.start()-6):m.start()+8].hex()})
 for s in pe.sections:
  if not s.Characteristics&0x20000000:continue
  for m in re.finditer(b'[\xe8\xe9]',s.get_data()):
   off=s.PointerToRawData+m.start();va=base+s.VirtualAddress+m.start()
   if off+5<=len(raw) and (va+5+struct.unpack_from('<i',raw,off+1)[0])&0xffffffff==target:rows.append({'kind':'rel32','va':va,'file_offset':off,'bytes':raw[off:off+5].hex()})
 print(json.dumps(rows,indent=2))
