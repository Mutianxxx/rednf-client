"""Read-only source-bound x86 excerpt capture for the 60US collision audit."""
from pathlib import Path
import sys, struct, hashlib, json, re
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'analysis/deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
RAW = (ROOT / 'DFO/DFO_fixed_v3.exe').read_bytes()
PE = pefile.PE(data=RAW)
BASE = PE.OPTIONAL_HEADER.ImageBase
OUT = Path(__file__).resolve().parent
MD = Cs(CS_ARCH_X86, CS_MODE_32); MD.skipdata = True
def off(va): return PE.get_offset_from_rva(va - BASE)
def va(offset): return BASE + PE.get_rva_from_offset(offset)
def capture(addr, length, label):
    pos=off(addr); data=RAW[pos:pos+length]
    asm='\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:9} {i.op_str}' for i in MD.disasm(data,addr))+'\n'
    name=f'{addr:08x}-{label}'
    (OUT/(name+'.bin')).write_bytes(data)
    (OUT/(name+'.asm')).write_text(asm,encoding='utf8')
    (OUT/(name+'.json')).write_text(json.dumps({'source':'DFO/DFO_fixed_v3.exe','source_sha256':hashlib.sha256(RAW).hexdigest(),'va':hex(addr),'rva':hex(addr-BASE),'file_offset':pos,'length':length,'bytes_sha256':hashlib.sha256(data).hexdigest()},indent=2),encoding='utf8')
    return asm
def refs(addr):
    out=[]
    for m in re.finditer(re.escape(struct.pack('<I',addr)),RAW): out.append({'type':'absolute','va':hex(va(m.start())),'file_offset':m.start()})
    for sec in PE.sections:
        if not sec.Characteristics & 0x20000000: continue
        start=sec.PointerToRawData; end=start+sec.SizeOfRawData
        for m in re.finditer(b'[\xe8\xe9]', RAW[start:end]):
            p=start+m.start()
            if p+5<=len(RAW) and ((va(p)+5+struct.unpack_from('<i',RAW,p+1)[0])&0xffffffff)==addr: out.append({'type':'rel32','va':hex(va(p)),'file_offset':p})
    return out
if __name__=='__main__':
    if sys.argv[1]=='capture': print(capture(int(sys.argv[2],0),int(sys.argv[3],0),sys.argv[4]))
    if sys.argv[1]=='refs': print(json.dumps(refs(int(sys.argv[2],0)),indent=2))
    if sys.argv[1]=='table':
        addr=int(sys.argv[2],0); count=int(sys.argv[3],0)
        print(json.dumps([hex(x) for x in struct.unpack_from('<'+'I'*count,RAW,off(addr))],indent=2))
