"""Generate UTF-8 assembly, raw bytes, hashes and verified address metadata."""
from pathlib import Path
import hashlib
import json
import sys
root=Path(__file__).resolve().parent
sys.path.insert(0,str(root/'deps'))
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
source=root.parent/'DFO'/'DFO_fixed_v3.exe'
data=source.read_bytes()
pe=pefile.PE(data=data)
base=pe.OPTIONAL_HEADER.ImageBase
dest=root/'evidence'
dest.mkdir(exist_ok=True)
spans=[
 ('pvf_decrypt_verify',0xa54e70,0xa54f39),
 ('path_hash_including_nul',0xa54f80,0xa54fa1),
 ('tree_entry',0xa55fa0,0xa55fef),
 ('archive_open',0xa570d0,0xa57431),
 ('lookup_hash_and_name',0xa56000,0xa56180),
 ('archive_read_bridge',0xa56180,0xa56213),
 ('read_entry_and_crc',0xa55320,0xa55500),
 ('script_init',0x82fde0,0x82ff2e),
 ('script_open',0x82f790,0x82f7c8),
 ('read_integer_and_float',0x82f7d0,0x82f8f4),
 ('reader_dispatch',0x8b2950,0x8b29ec),
 ('reader_open_text',0xb8ba50,0xb8ba8c),
 ('reader_push_text',0xb8b5c0,0xb8b77c),
 ('read_script_from_archive',0x8316f0,0x831ab0),
 ('startup_register_skills',0x44ae47,0x44ae60),
 ('skill_class_lists',0x8a0ae0,0x8a0da0),
 ('skill_load_class',0x8a2940,0x8a2a7f),
 ('skill_parse_properties',0x8a0da0,0x8a2340),
 ('consume_mp_branch',0x8a167f,0x8a1700),
 ('skill_runtime_materialization',0x551ad0,0x5535e0),
 ('linear_interpolation',0xb099b0,0xb099da),
 ('runtime_mp_getter',0x550e10,0x550f5b),
 ('mp_qualification_check',0x4d6417,0x4d6444),
 ('mp_debit',0x4d954f,0x4d9575),
]
md=Cs(CS_ARCH_X86,CS_MODE_32)
items=[]
for name,start,end in spans:
    off=pe.get_offset_from_rva(start-base)
    raw=data[off:off+end-start]
    (dest/(name+'.bin')).write_bytes(raw)
    listing=[f'; Source SHA256: {hashlib.sha256(data).hexdigest()}',
             f'; VA {start:08x}..{end:08x} (end exclusive); file offset {off:08x}',
             '; This is an instruction excerpt, not a recovered original source file.']
    for ins in md.disasm(raw,start):
        listing.append(f'{ins.address:08x}  {ins.bytes.hex():24} {ins.mnemonic:10} {ins.op_str}')
    (dest/(name+'.asm')).write_text('\n'.join(listing)+'\n',encoding='utf-8')
    items.append(dict(name=name,va=hex(start),rva=hex(start-base),end_va_exclusive=hex(end),
                      file_offset=hex(off),size=len(raw),sha256=hashlib.sha256(raw).hexdigest()))
(dest/'index.json').write_text(json.dumps(dict(source=str(source),
    source_sha256=hashlib.sha256(data).hexdigest(),image_base=hex(base),excerpts=items),indent=2),encoding='utf-8')
outputs=[]
for file in sorted((root/'decompiled').glob('*.c')):
    outputs.append(dict(file=file.name,size=file.stat().st_size,sha256=hashlib.sha256(file.read_bytes()).hexdigest()))
(root/'decompiled'/'all_outputs.json').write_text(json.dumps(dict(
    warning='Unreviewed angr pseudocode. Guessed prototypes/register arguments/SEH/protected fields can be wrong. Not original source; not directly compilable.',
    outputs=outputs),indent=2),encoding='utf-8')
print('evidence excerpts',len(items),'pseudocode files',len(outputs))
