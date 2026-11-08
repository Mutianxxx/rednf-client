"""Current native ANI terminal-frame and attachment ordering evidence."""
from pathlib import Path
import hashlib,json,struct,sys
HERE=Path(__file__).resolve().parent;ROOT=HERE.parent.parent
sys.path.insert(0,str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
raw=(ROOT/'DFO/DFO_fixed_v3.exe').read_bytes();sha=hashlib.sha256(raw).hexdigest()
assert sha=='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
pe=pefile.PE(data=raw);md=Cs(CS_ARCH_X86,CS_MODE_32)
slices=[]
for name,va,size in [('frame_advance',0xa27dc0,0x19b),('set_frame',0xa27870,0x143),
                     ('negative_attach_draw',0x49a359,0x82),('nonnegative_attach_draw',0x49a5b7,0x78),
                     ('attach_record',0x49b7b0,0x12d),('current_draw',0xa26990,0x388),
                     ('releasewave_ended_tick',0x5ce7a0,0x31),('set_rate',0xa29c70,0x20)]:
 off=pe.get_offset_from_rva(va-0x400000);data=raw[off:off+size]
 (HERE/(name+'.bin')).write_bytes(data)
 (HERE/(name+'.asm')).write_text('\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(data,va))+'\n',encoding='utf-8')
 slices.append(dict(name=name,va=hex(va),size=size,file_offset=off,sha256=hashlib.sha256(data).hexdigest()))
off=pe.get_offset_from_rva(0xdf053c-0x400000);constant=raw[off:off+4]
assert struct.unpack('<f',constant)[0]==-100.0
rea=[e for e in json.loads((ROOT/'analysis/rea/evidence-index.json').read_text(encoding='utf-8'))
     if e['parameters'].get('procedure','').lower()=='0xa27dc0']
(HERE/'evidence-index.json').write_text(json.dumps(dict(source_sha256=sha,runtime_observed=False,slices=slices,
 negative_percent_constant=dict(va='0xDF053C',bytes=constant.hex(),value=-100.0),
 rea_evidence=[dict(evidence_id=e['evidence_id'],file=e['result_file']) for e in rea]),indent=2),encoding='utf-8')
print('8 ANI timeline slices and native -100 rate constant retained')
