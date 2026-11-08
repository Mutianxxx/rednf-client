"""Export byte-bound native evidence for current 60US Swordman skill 8.

All writes stay in this directory. The original EXE and PVF remain read-only.
"""
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
assert hashlib.sha256(raw).hexdigest() == "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
pe = pefile.PE(data=raw)
base = pe.OPTIONAL_HEADER.ImageBase
md = Cs(CS_ARCH_X86, CS_MODE_32)
md.skipdata = True

EXCERPTS = [
    ("state22_cleanup", 0x730b30, 0x54),
    ("state22_entry_and_variant", 0x7329cf, 0x14a),
    ("state22_motion_and_atk", 0x732b19, 0x4d),
    ("state22_skill_columns", 0x732b66, 0xfd),
    ("state22_movement", 0x732c63, 0x78),
    ("state22_sounds_effect_load_attach", 0x732cdb, 0x1cb),
    ("state22_command_start", 0x72af0c, 0xa8),
    ("state22_command_continue_finish", 0x72afb4, 0x125),
    ("swordman_tick_state_switch", 0x7261d4, 0x22),
    ("state22_visual_tick", 0x726c9e, 0xf6),
    ("state_queue", 0x4ed1d0, 0x107),
    ("state_queue_send", 0x4edaeC, 0x109),
    ("base_transition_timer_reset", 0x4bc640, 0x41),
    ("swordman_transition_base_call", 0x73a168, 0x25),
    ("actor_transition_base_call", 0x4c5780, 0x26),
    ("actor_transition_base2_call", 0x4deed0, 0x30),
    ("direction_set_bridge", 0x4990c0, 0x1d),
    ("direction_set", 0x511110, 0x4b),
    ("direction_get", 0x499100, 0x16),
    ("effect_attach_speed_wrapper", 0x4acf80, 0xa1),
    ("effect_attach_reset", 0x49b7b0, 0x130),
    ("animation_reset_tree", 0xa27360, 0xec),
    ("animation_frame_set", 0xa23c90, 0xac),
    ("animation_update_tree", 0xa27f60, 0x11e),
    ("animation_advance_parent_time", 0xa27dc0, 0x1a0),
    ("motion_axis_set", 0x4b9d80, 0x183),
    ("motion_mode_set", 0x4b9c60, 0x10b),
    ("swordman_motion_direction", 0x745c30, 0x41),
    ("motion_direction", 0x4b9b20, 0xf9),
    ("input_selection", 0x559140, 0xf3),
    ("weapon_type_get", 0x4cd7f0, 0x50),
]


def at(va, size):
    offset = pe.get_offset_from_rva(va - base)
    data = raw[offset:offset + size]
    assert len(data) == size
    return offset, data


records = []
for name, va, size in EXCERPTS:
    offset, data = at(va, size)
    stem = f"{va:08x}-{name}"
    (DEST / f"{stem}.bin").write_bytes(data)
    (DEST / f"{stem}.asm").write_text("\n".join(
        f"{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}"
        for i in md.disasm(data, va)) + "\n", encoding="utf-8")
    records.append(dict(name=name, va=f"0x{va:08x}", file_offset=offset,
                        size=size, sha256=hashlib.sha256(data).hexdigest(),
                        binary=f"{stem}.bin", assembly=f"{stem}.asm"))

strings = []
for va in [0xd7f570, 0xd7f5c0, 0xd7f644, 0xd7f614, 0xd7f62c, 0xd7be38]:
    offset, data = at(va, 256)
    size = next(i for i in range(0, len(data)-1, 2) if data[i:i+2] == b"\0\0")
    strings.append(dict(va=f"0x{va:08x}", file_offset=offset,
                        value=data[:size].decode("utf-16-le"),
                        bytes=data[:size+2].hex()))
vtable = []
for slot in [0xb8, 0xc0, 0xf0, 0xf4, 0xf8, 0xfc, 0x198, 0x19c,
             0x22c, 0x28c, 0x38c, 0x488, 0x494, 0x49c, 0x620,
             0x67c, 0x72c, 0x73c, 0x768]:
    va = 0xd80f94 + slot
    offset, data = at(va, 4)
    vtable.append(dict(vtable="0x00d80f94", slot=f"0x{slot:x}",
                       va=f"0x{va:08x}", file_offset=offset,
                       bytes=data.hex(), target=f"0x{struct.unpack('<I', data)[0]:08x}"))
offset, data = at(0xd79744, 16)
gate = dict(va="0x00d79744", file_offset=offset, bytes=data.hex(),
            signed_int32=list(struct.unpack("<4i", data)),
            coverage="four entries needed before possible fifth segment; following bytes are not part of this table")
assert gate["signed_int32"] == [3, 3, 3, 3]
map_offset, state_map = at(0x730304, 0x35)
jump_index = state_map[22]
jump_va = 0x730280 + jump_index * 4
jump_offset, jump_data = at(jump_va, 4)
assert jump_index == 7 and struct.unpack("<I", jump_data)[0] == 0x726c9e
tick_switch = dict(state_getter="0x402060(actor+0x155c)",
                   dispatch="0x7261d4..0x7261f5", state=22,
                   map_va="0x00730304", map_file_offset=map_offset,
                   map_bytes=state_map.hex(), mapped_index=jump_index,
                   jump_va=f"0x{jump_va:08x}", jump_file_offset=jump_offset,
                   jump_bytes=jump_data.hex(), target="0x00726c9e")
manifest = dict(source=str(SOURCE), sha256=hashlib.sha256(raw).hexdigest(),
                image_base=f"0x{base:08x}", excerpts=records,
                strings=strings, swordman_vtable=vtable, continuation_frame_gate=gate,
                state22_tick_switch=tick_switch,
                evidence_kind="static native bytes; no original-client runtime observation",
                rea_support=["../rea/015-state-function.c", "../rea/results/047-tripleslash-command-containing.json",
                             "../rea/049-swordman-command-pseudocode.c"],
                limitations=["Some excerpts intentionally begin inside a larger function.",
                             "Function-wide Ghidra switch recovery is incomplete; literal bytes take priority."])
(DEST / "evidence.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
for record in records:
    _, current = at(int(record["va"], 16), record["size"])
    assert (DEST / record["binary"]).read_bytes() == current
    assert hashlib.sha256(current).hexdigest() == record["sha256"]
print(json.dumps(dict(native_excerpts=len(records), verified=len(records),
                      continuation_frame_gate=gate, strings=strings), ensure_ascii=False))
