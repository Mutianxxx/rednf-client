"""Byte-bound motion / animation-rate evidence. Writes only beside this file."""
from pathlib import Path
import hashlib
import json
import struct
import sys

DEST = Path(__file__).resolve().parent
ROOT = DEST.parents[1]
sys.path.insert(0, str(ROOT / "analysis/deps"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE = ROOT / "DFO/DFO_fixed_v3.exe"
EXPECTED = "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
raw = SOURCE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == EXPECTED
pe = pefile.PE(data=raw)
base = pe.OPTIONAL_HEADER.ImageBase
md = Cs(CS_ARCH_X86, CS_MODE_32)
md.skipdata = True

RANGES = [
    ("state22_motion_setup", 0x732c63, 0x78),
    ("actor_axis_config", 0x4b9d80, 0x183),
    ("actor_axis_apply", 0x4b99c0, 0x151),
    ("actor_direction_apply", 0x4b9b20, 0xf9),
    ("swordman_direction_apply", 0x745c30, 0x41),
    ("actor_mode_set", 0x4b9c60, 0x10b),
    ("mode_scale_get", 0x4b9bf0, 0x70),
    ("mode2_effective_stat", 0x4b55a0, 0x66),
    ("move_scale_set", 0x4b9e40, 0x66),
    ("ani_scale_set", 0x4b9eb0, 0xe9),
    ("periodic_scale_refresh_excerpt", 0x4bcb77, 0xb7),
    ("live_direction_input_gate", 0x4cbd90, 0x113),
    ("local_owner_gate", 0x49c090, 0x20),
    ("provider_position_velocity_methods", 0x49c0b0, 0x50),
    ("movement_constructor", 0x49c440, 0xb4),
    ("movement_reset", 0x511160, 0x129),
    ("velocity_set", 0x511040, 0x7d),
    ("countdown_set", 0x5110c0, 0x4a),
    ("acceleration_set", 0x511dd0, 0xc0),
    ("deceleration_countdown", 0x510d70, 0x71),
    ("axis_integrator", 0x50fde0, 0x40b),
    ("movement_tick", 0x511400, 0x7b0),
    ("movement_timer_reset", 0x512390, 0x70),
    ("movement_owner_set", 0x512400, 0x20),
    ("actor_tick_motion_call_excerpt", 0x49be80, 0x4a),
    ("position_round", 0x447ff0, 0xb0),
    ("msvc_float_truncate", 0xc01544, 0x75),
    ("timer_elapsed", 0xb06f00, 0x55),
    ("clock_channel_get", 0xb12a80, 0x28),
    ("clock_channels_advance", 0xb12ab0, 0x1d3),
    ("movement_clock_channel_set", 0x510f20, 0x2b),
    ("body_ani_install_rate", 0x4b4da0, 0x60),
    ("effect_ani_install_rate", 0x4acf80, 0xa1),
    ("ani_rate_set", 0xa29c70, 0xf7),
    ("ani_total_duration", 0xa24bb0, 0x107),
    ("ani_frame_deadline_set", 0xa27870, 0x142),
    ("ani_tree_clock_advance", 0xa27dc0, 0x1a0),
    ("global_ani_install_factor_init", 0xca1c00, 0x2a),
]


def at(va, size):
    offset = pe.get_offset_from_rva(va - base)
    data = raw[offset:offset + size]
    assert len(data) == size
    return offset, data


records = []
for name, va, size in RANGES:
    offset, data = at(va, size)
    stem = f"{va:08x}-{name}"
    (DEST / f"{stem}.bin").write_bytes(data)
    (DEST / f"{stem}.asm").write_text("\n".join(
        f"{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}"
        for i in md.disasm(data, va)) + "\n", encoding="utf-8")
    records.append(dict(name=name, va=f"0x{va:08x}", file_offset=offset,
                        size=size, sha256=hashlib.sha256(data).hexdigest(),
                        binary=f"{stem}.bin", assembly=f"{stem}.asm"))

constants = []
for va, fmt, use in [
    (0xcc11f8, "f", "movement 0.001 and ANI install multiplier"),
    (0xcc8830, "f", "ANI refresh multiplier 0.1"),
    (0xcd6928, "f", "deceleration countdown numerator -1000"),
    (0xccb260, "d", "zero used by countdown product comparison"),
    (0xcd4bd0, "f", "mean velocity multiplier 0.5"),
    (0xcd6828, "f", "negative displacement clamp"),
    (0xcd682c, "f", "positive displacement clamp"),
    (0xcab8e8, "d", "relative float comparison epsilon"),
    (0xe9d7a4, "f", "zero"),
    (0xcc1f58, "f", "one for duration reciprocal"),
    (0xccb9d8, "f", "duration scale +100"),
    (0xdf053c, "f", "deadline scale -100"),
    (0xcc10ac, "f", "clock-channel percentage multiplier 0.01"),
]:
    offset, data = at(va, struct.calcsize(fmt))
    constants.append(dict(va=f"0x{va:08x}", file_offset=offset, bytes=data.hex(),
                          format=fmt, value=struct.unpack("<" + fmt, data)[0], use=use))

vtables = []
for vt, slots in [(0xd80f94, [0xa8, 0xac, 0x274, 0x344, 0x488, 0x494, 0x498,
                               0x49c, 0x584, 0x588, 0x58c, 0x770]),
                  (0xcce978, [0, 4, 8, 0xc, 0x10])]:
    for slot in slots:
        offset, data = at(vt + slot, 4)
        vtables.append(dict(vtable=f"0x{vt:08x}", slot=f"0x{slot:x}",
                           va=f"0x{vt+slot:08x}", file_offset=offset, bytes=data.hex(),
                           target=f"0x{struct.unpack('<I', data)[0]:08x}"))
imports = [dict(dll=dll.dll.decode(), name=i.name.decode() if i.name else i.ordinal,
                iat_va=f"0x{i.address:08x}")
           for dll in pe.DIRECTORY_ENTRY_IMPORT for i in dll.imports
           if i.address == 0x140f0d8]
assert imports == [dict(dll="winmm.dll", name="timeGetTime", iat_va="0x0140f0d8")]
support = []
for name in ["054-motion-axis-set.c", "055-motion-control-set.c",
             "067-motion-integrate-axis.c", "068-motion-tick.c"]:
    path = ROOT / "analysis/rea" / name
    if path.exists():
        support.append(dict(path="../rea/" + name,
                            sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
manifest = dict(source=str(SOURCE), sha256=EXPECTED, image_base=f"0x{base:08x}",
                evidence_kind="static native bytes; extracted arithmetic execution is separately labeled",
                excerpts=records, constants=constants, vtables=vtables,
                imports=imports, rea_support=support,
                limitations=["Some ranges are excerpts and do not assert recovered function boundaries.",
                             "Ghidra types for 50FDE0 parameters are wrong: axis and dt are int32.",
                             "Original-client runtime states and owner/controller collision behavior are not observed."])
(DEST / "evidence.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
for rec in records:
    _, data = at(int(rec["va"], 16), rec["size"])
    assert (DEST / rec["binary"]).read_bytes() == data
print(json.dumps(dict(excerpts=len(records), verified=len(records), constants=len(constants), imports=imports)))
