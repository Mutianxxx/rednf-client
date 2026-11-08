"""Retain read-only current-PE evidence for attack-history epochs."""
from pathlib import Path
import hashlib,json,re,struct,sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parent.parent
sys.path.insert(0,str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
raw=(ROOT/'DFO/DFO_fixed_v3.exe').read_bytes()
sha=hashlib.sha256(raw).hexdigest()
assert sha=='a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
pe=pefile.PE(data=raw);md=Cs(CS_ARCH_X86,CS_MODE_32)
targets={
 'history_clear':(0x438990,0x53),
 'canonical_history_query':(0x4ece50,0x7a),
 'attackinfo_install':(0x4edcd0,0x3a),
 'object_remove_notification':(0x4edd10,0x102),
 'canonical_history_register':(0x4ede20,0x85),
 'mode2_clock_gate':(0x4edeb0,0xb1),
 'entity_reset':(0x4ed140,0x85),
 'active_attackinfo_install':(0x4afa10,0x5a),
 'character_attackinfo_install':(0x4cf680,0x240),
 'swordman_attackinfo_wrapper':(0x746c30,0x1b),
 'hardattack_install_call':(0x731fbc,0x14),
 'tripleslash_install_call':(0x732b19,0x4d),
 'tripleslash_clock_reset':(0x729b56,0x25),
 'qualification_history_and_mode':(0x4edfad,0x23),
 'qualification_register_and_emit':(0x4ee130,0x20),
 'passive_reset_and_install':(0x49f010,0x75),
}
rows=[]
for name,(va,size) in targets.items():
 off=pe.get_offset_from_rva(va-0x400000);data=raw[off:off+size]
 (HERE/(name+'.bin')).write_bytes(data)
 (HERE/(name+'.asm')).write_text('\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(data,va))+'\n',encoding='utf-8')
 rows.append(dict(name=name,va=hex(va),file_offset=off,size=size,sha256=hashlib.sha256(data).hexdigest()))
slots=[]
for table in [0xd80f94,0xd8385c,0xcbb7d4,0xd057d4]:
 for slot in [0x198,0x19c,0x1a0,0x1a4,0x1a8,0x1c8,0x298]:
  va=table+slot;off=pe.get_offset_from_rva(va-0x400000)
  slots.append(dict(vtable=hex(table),slot=hex(slot),va=hex(va),file_offset=off,
                    bytes=raw[off:off+4].hex(),target=hex(struct.unpack_from('<I',raw,off)[0])))
reset_calls=[]
for m in re.finditer(b'\xff[\x90-\x97]\xa0\x01\x00\x00',raw[:0x8b0000]):
 reset_calls.append(hex(pe.get_rva_from_offset(m.start())+0x400000))
index=json.loads((ROOT/'analysis/rea/evidence-index.json').read_text(encoding='utf-8'))
rea=[dict(evidence_id=e['evidence_id'],file=e.get('result_file'),parameters=e['parameters'])
     for e in index if e['parameters'].get('procedure','').lower() in ['0x4edcd0','0x4cf680','0x4ece50','0x4ede20']]
result=dict(source='DFO/DFO_fixed_v3.exe',sha256=sha,runtime_observed=False,
 slices=rows,vtable_slots=slots,raw_pattern_vcall1a0_candidates=reset_calls,
 pattern_scope='Raw opcode-pattern candidates are not all semantically verified calls on these classes.',rea_evidence=rea)
(HERE/'evidence-index.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print(f'{len(rows)} history slices, {len(slots)} slots, {len(rea)} REA observations')
