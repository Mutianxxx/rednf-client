"""Source-bound read-only x86 excerpts for the skill32 spawned-object chain."""
from pathlib import Path
import sys, json, hashlib, struct, re
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent
SOURCE = ROOT.parents[1] / 'DFO' / 'DFO_fixed_v3.exe'
RAW = SOURCE.read_bytes()
SHA256 = hashlib.sha256(RAW).hexdigest()
if SHA256 != 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b':
    raise ValueError('Unexpected executable; do not reuse 60US VAs')
PE = pefile.PE(data=RAW)
BASE = PE.OPTIONAL_HEADER.ImageBase
MD = Cs(CS_ARCH_X86, CS_MODE_32)
MD.skipdata = True

def chunk(start, length):
    offset = PE.get_offset_from_rva(start - BASE)
    return RAW[offset:offset + length], offset

def save(start, length):
    raw, offset = chunk(start, length)
    name = f'{start:08X}-{start+length:08X}'
    (ROOT / (name + '.bin')).write_bytes(raw)
    (ROOT / (name + '.asm')).write_text('\n'.join(
        f'{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}'
        for i in MD.disasm(raw, start)), encoding='utf-8')
    record = dict(source=str(SOURCE), source_sha256=SHA256, start_va=start,
                  length=length, file_offset=offset, chunk_sha256=hashlib.sha256(raw).hexdigest(),
                  observed_execution=False)
    (ROOT / (name + '.json')).write_text(json.dumps(record, indent=2), encoding='utf-8')
    return record

if __name__ == '__main__':
    mode = sys.argv[1]
    if mode == 'save':
        for i in range(2, len(sys.argv), 2):
            row = save(int(sys.argv[i], 0), int(sys.argv[i+1], 0))
            print(f"{row['start_va']:08X}+{row['length']:X}")
    elif mode == 'dis':
        start, length = map(lambda v: int(v,0), sys.argv[2:4])
        data, _ = chunk(start,length)
        print('\n'.join(f'{i.address:08x}  {i.mnemonic:10} {i.op_str}' for i in MD.disasm(data,start)))

