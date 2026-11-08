"""Small address-aware static inspection helper (x86 PE)."""
import argparse
import pathlib
import re
import struct
import sys
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent / 'deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

p = argparse.ArgumentParser()
p.add_argument('mode', choices=['find', 'refs', 'disasm', 'imports'])
p.add_argument('value', nargs='?', default='')
p.add_argument('--size', type=lambda n: int(n, 0), default=0x200)
p.add_argument('--exe', default='DFO/DFO_fixed_v3.exe')
args = p.parse_args()
raw = pathlib.Path(args.exe).read_bytes()
pe = pefile.PE(data=raw)
base = pe.OPTIONAL_HEADER.ImageBase

def va(off):
    return base + pe.get_rva_from_offset(off)

if args.mode == 'find':
    for pattern in args.value.split('|'):
        for enc in ['ascii', 'utf-16-le']:
            try:
                needle = pattern.encode(enc)
            except UnicodeEncodeError:
                continue
            for m in re.finditer(re.escape(needle), raw, re.I):
                print(hex(va(m.start())), enc, repr(raw[max(0,m.start()-16):m.end()+64]))
elif args.mode == 'refs':
    target = int(args.value, 0)
    for m in re.finditer(re.escape(struct.pack('<I', target)), raw):
        print('absolute', hex(va(m.start())), 'file', hex(m.start()), raw[max(0,m.start()-6):m.start()+8].hex())
    for m in re.finditer(b'[\xe8\xe9]', raw[:0x8b0000]):
        off = m.start()
        if off+5 <= len(raw) and (va(off) + 5 + struct.unpack_from('<i', raw, off+1)[0]) & 0xffffffff == target:
            print('rel32', hex(va(off)), raw[off:off+5].hex())
elif args.mode == 'disasm':
    addr = int(args.value, 0)
    off = pe.get_offset_from_rva(addr - base)
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.skipdata = True
    for ins in md.disasm(raw[off:off+args.size], addr):
        print(f'{ins.address:08x}  {ins.bytes.hex():24} {ins.mnemonic:10} {ins.op_str}')
elif args.mode == 'imports':
    for dll in pe.DIRECTORY_ENTRY_IMPORT:
        print(dll.dll)
        for i in dll.imports:
            if not args.value or (i.name and re.search(args.value, i.name.decode(), re.I)):
                print(hex(i.address), i.name or i.ordinal)
