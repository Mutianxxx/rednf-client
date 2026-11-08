"""Export owner-collision evidence; writes only in combat_motion/owner."""
from pathlib import Path
import hashlib
import json
import struct
import sys

DEST = Path(__file__).resolve().parent
ROOT = DEST.parents[2]
sys.path.insert(0, str(ROOT / "analysis/deps"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE = ROOT / "DFO/DFO_fixed_v3.exe"
raw = SOURCE.read_bytes()
SOURCE_HASH = hashlib.sha256(raw).hexdigest()
assert SOURCE_HASH == "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
pe = pefile.PE(data=raw)
BASE = pe.OPTIONAL_HEADER.ImageBase
md = Cs(CS_ARCH_X86, CS_MODE_32)
md.skipdata = True
RANGES = [
    ("owner_z_nonnegative", 0x4ac100, 0x11),
    ("owner_xy_wrapper", 0x4b00f0, 0x117),
    ("owner_response_wrapper", 0x4b97b0, 0x51),
    ("position_probe", 0x4e7dd0, 0x135),
    ("response_attachment_forward", 0x4e8a30, 0x43),
    ("manager_first_blocker", 0x50b240, 0x9a),
    ("layer_terrain_probe", 0x485950, 0x2f0),
    ("terrain_cell_read", 0x485580, 0xe7),
    ("pair_blocker", 0x4eb600, 0x180),
    ("pair_bounds_intersection", 0x4e81d0, 0x84),
    ("ignore_list_contains", 0x4eb1d0, 0x49),
    ("type1_scalar_positive", 0x484670, 0x12),
    ("class_mask_test", 0x498ff0, 0x17),
    ("status_slot_active", 0x4ac020, 0x2b),
    ("appendage_list_get", 0x744870, 7),
    ("native_state_get", 0x744c30, 0xb),
    ("actor_scan_flag_get", 0x407bb0, 7),
    ("position_set_xyz", 0x499050, 0x3e),
    ("position_set_axis", 0x510f50, 0x3e),
    ("layer_get", 0x438690, 7),
    ("scalar_21c_get", 0x4386d0, 7),
    ("footprint_width_height", 0x4387f0, 0x20),
    ("footprint_bounds", 0x438810, 0xa0),
    ("detour_on_collision", 0x4b9560, 0x1ec),
    ("detour_reset_check", 0x4b9750, 0x5e),
    ("half_open_rectangle", 0x8adab0, 0x34),
    ("extension_row_blocks", 0x4869d0, 0x95),
    ("tile_column_count", 0x486a70, 0x2b),
    ("total_tile_rows", 0x486c30, 0x64),
    ("base_height", 0x486ca0, 0x57),
]


def at(va, size):
    offset = pe.get_offset_from_rva(va - BASE)
    data = raw[offset:offset + size]
    assert len(data) == size
    return offset, data


def main():
    records = []
    for name, va, size in RANGES:
        offset, data = at(va, size)
        stem = f"{va:08x}-{name}"
        (DEST / (stem + ".bin")).write_bytes(data)
        (DEST / (stem + ".asm")).write_text("\n".join(
            f"{i.address:08x}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}"
            for i in md.disasm(data, va)) + "\n", encoding="utf-8")
        records.append(dict(name=name, va=f"0x{va:08x}", file_offset=offset,
                            size=size, sha256=hashlib.sha256(data).hexdigest(),
                            binary=stem + ".bin", assembly=stem + ".asm"))
    slots = []
    for slot in [0x2c, 0x64, 0x88, 0xa8, 0xac, 0xdc, 0xe0, 0x1c4, 0x1fc, 0x200,
                 0x204, 0x208, 0x20c, 0x210, 0x214, 0x218, 0x230, 0x244, 0x248,
                 0x274, 0x33c, 0x3c4, 0x410, 0x57c]:
        offset, data = at(0xd80f94 + slot, 4)
        slots.append(dict(slot=f"0x{slot:x}", vtable="0x00d80f94", file_offset=offset,
                          bytes=data.hex(), target=f"0x{struct.unpack('<I', data)[0]:08x}"))
    tables = []
    for va in [0x485c30, 0x4eb760, 0x4eb770]:
        offset, data = at(va, 16)
        tables.append(dict(va=f"0x{va:08x}", file_offset=offset, bytes=data.hex(),
                           targets=[f"0x{v:08x}" for v in struct.unpack("<4I", data)]))
    rtti = []
    for va in [0xf551f4, 0xf5963c, 0xf4287c, 0xf428a0]:
        offset, data = at(va, 128)
        name = data[8:].split(b"\0", 1)[0]
        rtti.append(dict(va=f"0x{va:08x}", file_offset=offset,
                         type_descriptor_bytes=data[:9 + len(name)].hex(), name=name.decode("ascii")))
    support = []
    for path in sorted((ROOT / "analysis/rea/results").glob("*.json")):
        if path.name[:3] not in ["081", "082", "083", "084", "085", "086", "087"] and "entity-blocking-predicate" not in path.name:
            continue
        document = json.loads(path.read_text(encoding="utf-8"))
        found = []

        def walk(value):
            if isinstance(value, dict):
                if isinstance(value.get("pseudocode"), str):
                    found.append(value["pseudocode"])
                for child in value.values():
                    walk(child)
            elif isinstance(value, list):
                for child in value:
                    walk(child)

        walk(document)
        if found:
            target = path.stem + ".c"
            (DEST / target).write_text(found[0].replace("\r\r\n", "\n"), encoding="utf-8")
            support.append(dict(source="../../rea/results/" + path.name,
                                sha256=hashlib.sha256(path.read_bytes()).hexdigest(), pseudocode=target))
    manifest = dict(source=str(SOURCE), sha256=SOURCE_HASH, image_base=f"0x{BASE:08x}",
                    excerpts=records, swordman_slots=slots, jump_tables=tables, rtti=rtti, rea_support=support,
                    coverage="current Swordman owner collision functions; static evidence, no original-client runtime observation",
                    cautions=["Some helper ranges are deliberate excerpts, not asserted complete function boundaries.",
                              "Class masks, state16 status-slot name and scalar21c semantic name are not guessed.",
                              "Manager objects and callback classes remain runtime inputs; read contracts before integrating."])
    (DEST / "evidence.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    for record in records:
        assert (DEST / record["binary"]).read_bytes() == at(int(record["va"], 16), record["size"])[1]
    print(json.dumps(dict(excerpts=len(records), verified=len(records), rea_support=len(support))))


if __name__ == "__main__":
    main()
