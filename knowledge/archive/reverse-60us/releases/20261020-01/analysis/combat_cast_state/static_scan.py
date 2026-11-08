"""Read-only x86 evidence excerpts, bound to the supplied 60US client hash."""
from pathlib import Path
import sys, struct, re, json, hashlib
sys.path.insert(0, r'D:\dnf\60US\analysis\deps')
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent
SOURCE = Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe')
RAW = SOURCE.read_bytes()
PE = pefile.PE(data=RAW)
BASE = PE.OPTIONAL_HEADER.ImageBase
MD = Cs(CS_ARCH_X86, CS_MODE_32)
MD.skipdata = True

def chunk(start, length):
    offset = PE.get_offset_from_rva(start - BASE)
    return RAW[offset:offset + length], offset

def save(start, length):
    data, offset = chunk(start, length)
    name = f'{start:08X}-{start + length:08X}'
    (ROOT / (name + '.bin')).write_bytes(data)
    (ROOT / (name + '.asm')).write_text('\n'.join(f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data, start)), encoding='utf-8')
    record = {'source': str(SOURCE), 'source_sha256': hashlib.sha256(RAW).hexdigest(), 'start_va': start, 'length': length, 'rva': start - BASE, 'file_offset': offset, 'chunk_sha256': hashlib.sha256(data).hexdigest(), 'observed_execution': False}
    (ROOT / (name + '.json')).write_text(json.dumps(record, indent=2), encoding='utf-8')
    return record

def refs(target):
    rows = []
    for match in re.finditer(re.escape(struct.pack('<I', target)), RAW):
        off = match.start()
        rows.append({'kind': 'absolute', 'va': BASE + PE.get_rva_from_offset(off), 'file_offset': off, 'context': RAW[max(0, off-6):off+8].hex()})
    for section in PE.sections:
        if not section.Characteristics & 0x20000000:
            continue
        for match in re.finditer(b'[\xe8\xe9]', section.get_data()):
            off = section.PointerToRawData + match.start()
            va = BASE + section.VirtualAddress + match.start()
            if off + 5 <= len(RAW) and (va + 5 + struct.unpack_from('<i', RAW, off+1)[0]) & 0xffffffff == target:
                rows.append({'kind': 'rel32', 'va': va, 'file_offset': off, 'bytes': RAW[off:off+5].hex()})
    return rows

if __name__ == '__main__':
    mode = sys.argv[1]
    if mode == 'save':
        for i in range(2, len(sys.argv), 2):
            row = save(int(sys.argv[i], 0), int(sys.argv[i+1], 0)); print(f"{row['start_va']:08X}+{row['length']:X}")
    elif mode == 'dis':
        start, length = [int(x, 0) for x in sys.argv[2:4]]
        data, _ = chunk(start, length)
        print('\n'.join(f'{i.address:08x}  {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data, start)))
    elif mode == 'refs':
        print(json.dumps(refs(int(sys.argv[2], 0)), indent=2))
