"""Export read-only, byte-addressed evidence for the current 60US ATK chain."""
from pathlib import Path
import hashlib
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
DEST = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "analysis" / "deps"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE = ROOT / "DFO" / "DFO_fixed_v3.exe"
raw = SOURCE.read_bytes()
pe = pefile.PE(data=raw)
base = pe.OPTIONAL_HEADER.ImageBase
md = Cs(CS_ARCH_X86, CS_MODE_32)
md.skipdata = True

excerpts = [
    ("atk_parser_entry", 0x836c20, 0x94),
    ("atk_damage_and_bonus_parse", 0x836cb4, 0x117),
    ("atk_type_parse", 0x836dcb, 0x8c),
    ("atk_weapon_apply_parse", 0x836e57, 0x3a),
    ("atk_element_parse", 0x836f3f, 0x45),
    ("atk_reaction_push_lift_parse", 0x8376e5, 0x118),
    ("element_name_enum", 0x82fc70, 0xf0),
    ("atk_element_set", 0x46d830, 0x67),
    ("atk_normalize_install", 0x4cf680, 0x185),
    ("atk_install_copy", 0x4edcd0, 0x3c),
    ("current_atk_get", 0x438650, 0x7),
    ("atk_copy", 0x4a27e0, 0xb48),
    ("atk_reset_core", 0x435430, 0xf7),
    ("hardattack_setup", 0x731fa7, 0x12f),
    ("hardattack_charge_ratio", 0x7320db, 0x9b),
    ("level_query_bridge", 0x4caa20, 0x21),
    ("level_query", 0x550150, 0x215),
    ("level_value", 0x550080, 0xc9),
    ("skill_load_parse", 0x551ad0, 0xcd),
    ("skill_levelinfo_materialize", 0x553265, 0x1da),
    ("skl_parser_entry", 0x8a0da0, 0xae),
    ("skl_levelinfo_parse", 0x8a1e5b, 0xb7),
    ("static_value", 0x54ff60, 0x5b),
    ("damage_pack_entry", 0x4eb780, 0x44),
    ("damage_pack_atk_core", 0x4eb960, 0x117),
    ("damage_pack_stats", 0x4ebc36, 0x8e),
    ("swordman_context_stat", 0x744a50, 0x11),
    ("swordman_weapon_type0", 0x744a90, 0x11),
    ("swordman_weapon_type1", 0x744b10, 0x11),
    ("weapon_type0_value", 0x4b5610, 0x68),
    ("weapon_type1_value", 0x4b56f0, 0x68),
    ("damage_pack_full", 0x4eb780, 0x129a),
    ("damage_base_dispatch", 0x8b85f0, 0x5e),
    ("damage_weapon_percent", 0x8b79c0, 0xef),
    ("damage_common_entry", 0x8b8650, 0x4d0),
    ("protected_int_get", 0x402060, 0xdd),
    ("protected_float_get", 0x4333b0, 0xdd),
    ("protected_value_set", 0x404560, 0x8f),
]

def at(address, size):
    off = pe.get_offset_from_rva(address - base)
    return off, raw[off:off + size]

records = []
for name, address, size in excerpts:
    off, data = at(address, size)
    stem = f"{address:08x}-{name}"
    (DEST / f"{stem}.bin").write_bytes(data)
    assembly = "\n".join(f"{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}"
                          for i in md.disasm(data, address)) + "\n"
    (DEST / f"{stem}.asm").write_text(assembly, encoding="utf-8")
    records.append(dict(name=name, va=f"0x{address:08x}", file_offset=off,
                        size=size, sha256=hashlib.sha256(data).hexdigest(),
                        binary=f"{stem}.bin", assembly=f"{stem}.asm"))

strings = []
for address in [0xe14b28, 0xe14bb4, 0xcda4a4, 0xe14c04, 0xe14c14,
                0xe14be0, 0xe13eb4, 0xe13ea4, 0xe1499c, 0xcc3d74,
                0xe14c48, 0xe14c28, 0xe149c8, 0xe14980, 0xe1496c,
                0xe13800, 0xe137e0, 0xe137c0, 0xe137a0, 0xe29210]:
    off, data = at(address, 300)
    end = next(i for i in range(0, len(data) - 1, 2) if data[i:i+2] == b"\0\0")
    value = data[:end].decode("utf-16-le")
    strings.append(dict(va=f"0x{address:08x}", file_offset=off, value=value,
                        bytes=data[:end+2].hex()))
constants = []
for address in [0xcc10ac, 0xcc1f58]:
    off, data = at(address, 4)
    constants.append(dict(va=f"0x{address:08x}", file_offset=off,
                          bytes=data.hex(), float32=struct.unpack("<f", data)[0]))

vtable = []
for slot in [0x19c, 0x1d0, 0x1d8, 0x1e8, 0x64c, 0x67c]:
    address = 0xd80f94 + slot
    off, data = at(address, 4)
    vtable.append(dict(vtable="0x00d80f94", slot=f"0x{slot:x}",
                       va=f"0x{address:08x}", file_offset=off,
                       bytes=data.hex(), target=f"0x{struct.unpack('<I',data)[0]:08x}"))
manifest = dict(source=str(SOURCE), sha256=hashlib.sha256(raw).hexdigest(),
                image_base=f"0x{base:08x}", excerpts=records,
                strings=strings, constants=constants, swordman_vtable=vtable)
(DEST / "evidence.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
for rec in records:
    address = int(rec["va"], 16)
    _, current = at(address, rec["size"])
    assert (DEST / rec["binary"]).read_bytes() == current
    assert hashlib.sha256(current).hexdigest() == rec["sha256"]
print(json.dumps(dict(excerpts=len(records), verified=len(records),
                      element_names=strings[-5:-1], constants=constants,
                      swordman_vtable=vtable), ensure_ascii=False))
