"""Source-bound original byte excerpts for reaction motion; writes this folder."""
from pathlib import Path
import hashlib, json, struct, sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT/'analysis/deps'))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE_HASH = 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
raw = (ROOT/'DFO/DFO_fixed_v3.exe').read_bytes()
assert hashlib.sha256(raw).hexdigest() == SOURCE_HASH
pe = pefile.PE(data=raw)
md = Cs(CS_ARCH_X86, CS_MODE_32)
rows = []
for name, va, size in [
    ('horizontal_motion', 0x4ba620, 0x149),
    ('horizontal_stat', 0x4bdd40, 0x33),
    ('vertical_impulse', 0x4b98f0, 0x37),
    ('gravity', 0x4b9fa0, 0x113),
    ('gravity_install', 0x4ba0c0, 0x51),
    ('state3_apply', 0x4bb091, 0x171),
    ('state3_tick_duration_gate', 0x4bd06a, 0x4d),
    ('state0_request_shared', 0x4bd9f2, 0xe),
]:
    off = pe.get_offset_from_rva(va-0x400000)
    data = raw[off:off+size]
    (HERE/(name+'.bin')).write_bytes(data)
    (HERE/(name+'.asm')).write_text('\n'.join(f'{i.address:08x} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}' for i in md.disasm(data, va))+'\n', encoding='utf8')
    rows.append(dict(name=name, va=hex(va), file_offset=off, size=size,
                     sha256=hashlib.sha256(data).hexdigest()))
slots = []
for table in (0xd80f94, 0xd8385c):
    for slot in (0x344, 0x488, 0x494, 0x49c, 0x518):
        off = pe.get_offset_from_rva(table+slot-0x400000)
        slots.append(dict(vtable=hex(table), slot=hex(slot), file_offset=off,
                          bytes=raw[off:off+4].hex(), target=hex(struct.unpack_from('<I', raw, off)[0])))
constants = []
for va in (0xcc10ac, 0xcd1434, 0xcd1438, 0xcd1440, 0xcd145c):
    off = pe.get_offset_from_rva(va-0x400000)
    constants.append(dict(va=hex(va), file_offset=off, bytes=raw[off:off+4].hex(),
                          float32=struct.unpack_from('<f', raw, off)[0]))
index = json.loads((ROOT/'analysis/rea/evidence-index.json').read_text(encoding='utf8'))
rea = [dict(evidence_id=e['evidence_id'], file=e.get('result_file'), parameters=e['parameters'])
       for e in index if e['parameters'].get('procedure','').lower() in
       ['0x4ba620', '0x4b98f0', '0x4b9fa0', '0x4bad60']]
report = dict(source='DFO/DFO_fixed_v3.exe', sha256=SOURCE_HASH, original_client_runtime=False,
              slices=rows, slots=slots, constants=constants, rea_evidence=rea)
(HERE/'evidence-index.json').write_text(json.dumps(report, indent=2)+'\n', encoding='utf8')
print(f'{len(rows)} reaction byte excerpts, {len(slots)} slots, {len(constants)} constants, {len(rea)} REA records')
