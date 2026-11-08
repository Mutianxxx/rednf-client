"""Retain bounded 60US HardAttack effect/controller evidence from the fixed PE."""
from pathlib import Path
import hashlib
import json
import struct
import sys

HERE=Path(__file__).resolve().parent
ROOT=HERE.parent.parent
sys.path.insert(0,str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

EXPECTED='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
raw=(ROOT/'DFO/DFO_fixed_v3.exe').read_bytes()
assert hashlib.sha256(raw).hexdigest()==EXPECTED
pe=pefile.PE(data=raw)
md=Cs(CS_ARCH_X86,CS_MODE_32)
targets={
    'state20_body_atk':(0x731f0c,0xc4),
    'normal_effects':(0x7326f0,0xfb),
    'layer_wrapper':(0x4acf80,0x78),
    'layer_record_reset':(0x49b7b0,0x130),
    'negative_layers_before_body':(0x49a359,0x82),
    'nonnegative_layers_after_body':(0x49a5b7,0x78),
    'effect_image_rate_override':(0xa25900,0xd8),
}
index=[]
for name,(va,size) in targets.items():
    offset=pe.get_offset_from_rva(va-pe.OPTIONAL_HEADER.ImageBase)
    data=raw[offset:offset+size]
    (HERE/f'{name}.bin').write_bytes(data)
    (HERE/f'{name}.asm').write_text('\n'.join(
        f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}'
        for i in md.disasm(data,va)),encoding='utf-8')
    index.append(dict(name=name,va=hex(va),file_offset=offset,size=size,
                      sha256=hashlib.sha256(data).hexdigest()))
strings=[]
for va in (0xd7f6c0,0xd7f678):
    offset=pe.get_offset_from_rva(va-pe.OPTIONAL_HEADER.ImageBase)
    end=offset
    while raw[end:end+2]!=b'\0\0':end+=2
    strings.append(dict(va=hex(va),offset=offset,encoding='utf-16le',
                        text=raw[offset:end].decode('utf-16le'),raw_hex=raw[offset:end+2].hex()))
offset=pe.get_offset_from_rva(0xcc10ac-pe.OPTIONAL_HEADER.ImageBase)
result=dict(source='DFO/DFO_fixed_v3.exe',source_sha256=EXPECTED,
            evidence_kind='read-only raw PE and Capstone; not REA provider Evidence or runtime observation',
            slices=index,strings=strings,
            scale_constant=dict(va='0xcc10ac',raw_hex=raw[offset:offset+4].hex(),
                                float32=struct.unpack_from('<f',raw,offset)[0]))
(HERE/'evidence-index.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print('HardAttack bounded evidence verified and retained:',len(index),'slices')
