"""Capture current 60US controller windows without executing the target."""
import hashlib,json,struct,sys
from pathlib import Path
root=Path(__file__).resolve().parent
sys.path.insert(0,str(root/'deps'))
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
data=(root.parent/'DFO/DFO_fixed_v3.exe').read_bytes();pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase
md=Cs(CS_ARCH_X86,CS_MODE_32);md.skipdata=True
dest=root/'combat_native_skills';dest.mkdir(exist_ok=True)
targets={0x71fff0:0x10350,0x7307b0:0xce40,0x730340:0x2b00,0x732d00:0x1800,0x7469a0:0x300,0x4d3ce0:0xc0,0x5270f0:0x100}
manifest=[]
for va,size in targets.items():
 off=pe.get_offset_from_rva(va-base);raw=data[off:off+size]
 (dest/f'{va:08x}.bin').write_bytes(raw)
 instructions=list(md.disasm(raw,va))
 (dest/f'{va:08x}.asm').write_text('\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in instructions),encoding='utf-8')
 manifest.append(dict(va=hex(va),file_offset=off,size=len(raw),sha256=hashlib.sha256(raw).hexdigest()))
(dest/'slices.json').write_text(json.dumps(dict(source_sha256=hashlib.sha256(data).hexdigest(),kind='static raw PE/Capstone; not REA Evidence',slices=manifest),indent=2),encoding='utf-8')
print('saved',dest)
