"""Read-only native ANI blend evidence; API names are separately sourced headers."""
from pathlib import Path
import hashlib,json,re,sys,struct
HERE=Path(__file__).resolve().parent
ROOT=HERE.parent.parent
sys.path.insert(0,str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
raw=(ROOT/'analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe').read_bytes()
sha=hashlib.sha256(raw).hexdigest()
assert sha=='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
pe=pefile.PE(data=raw);md=Cs(CS_ARCH_X86,CS_MODE_32)
targets={'ani_graphic_effect_parse':(0xa291d0,0x138),'current_frame_draw':(0xa23d60,0x130),
         'blend_dispatch':(0x401020,0x88),'blend_restore':(0x4010b0,0x34),
         'blend_record_setter':(0xb084b0,0x17),'device_blend_apply':(0xb084f0,0x154),
         'draw_batch_mode_copy':(0xb091ff,0x20),'device_setup':(0xb08200,0x2a0)}
rows=[]
for name,(va,size) in targets.items():
    off=pe.get_offset_from_rva(va-0x400000);data=raw[off:off+size]
    (HERE/(name+'.bin')).write_bytes(data)
    (HERE/(name+'.asm')).write_text('\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(data,va)),encoding='utf-8')
    rows.append(dict(name=name,va=hex(va),file_offset=off,size=size,sha256=hashlib.sha256(data).hexdigest()))
headers=[]
for name in ['d3d8.h','d3d8types.h']:
    data=(HERE/name).read_bytes()
    headers.append(dict(file=name,url='https://raw.githubusercontent.com/mingw-w64/mingw-w64/master/mingw-w64-headers/include/'+name,
                        acquired_date='2026-10-19',sha256=hashlib.sha256(data).hexdigest(),authority='external API reference; not DNF behavior evidence'))
header=(HERE/'d3d8.h').read_text()
part=header.split('DECLARE_INTERFACE_IID_(IDirect3DDevice8,IUnknown,')[1].split('#undef INTERFACE')[0]
names=re.findall(r'STDMETHOD(?:_\([^,]+,|\()\s*(\w+)\)',part)
assert names[50]=='SetRenderState' and names[63]=='SetTextureStageState'
off=pe.get_offset_from_rva(0xb08630-0x400000)
table=[hex(struct.unpack_from('<I',raw,off+4*i)[0]) for i in range(5)]
assert table[2]=='0xb0853d'
result=dict(source_sha256=sha,evidence_kind='static PE bytes plus separately identified API headers',slices=rows,
            headers=headers,d3d8_slots={hex(i*4):names[i] for i in [23,24,50,63,76,83,85]},
            blend_jump_table=table,
            graphic_effects={'NONE':{'enum':0,'srcblend':5,'destblend':6},'LINEARDODGE':{'enum':2,'srcblend':5,'destblend':2}},
            limitations=['D3D8 RGB blend operators established statically; GPU precision, gamma, interpolation and original-game visual equality not measured'])
(HERE/'evidence-index.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print('ANI blend: LINEARDODGE -> SRCALPHA / ONE, 8 native slices retained')
