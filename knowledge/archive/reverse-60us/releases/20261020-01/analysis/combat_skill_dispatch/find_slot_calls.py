from pathlib import Path
import sys,struct,re
sys.path.insert(0,r'D:\dnf\60US\analysis\deps');import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
raw=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe').read_bytes();pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase;md=Cs(CS_ARCH_X86,CS_MODE_32);md.skipdata=True
start=0x71b000;end=0x744750;off=pe.get_offset_from_rva(start-base);block=raw[off:off+end-start]
for m in re.finditer(b'\xff[\x90-\x97]\x68\x07\0\0',block):
 va=start+m.start();print('CALL',hex(va));data=raw[off+m.start()-40:off+m.start()+15]
 print('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,va-40)))
