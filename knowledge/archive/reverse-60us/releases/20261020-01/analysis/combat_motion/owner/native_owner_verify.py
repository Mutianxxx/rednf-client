"""Execute copied owner predicates against explicit synthetic class/map fixtures."""
from dataclasses import asdict, replace
from pathlib import Path
import hashlib
import json
import struct
import subprocess
import sys

DEST = Path(__file__).resolve().parent
sys.path.insert(0, str(DEST.parent))
from native_verify import BASE, build_harness, original_bytes, SOURCE_HASH, u32
from owner_model import Appendage, Owner, Terrain, pair_blocks, response_effects, terrain_allowed, wrapper_branch, z_allowed
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

md = Cs(CS_ARCH_X86, CS_MODE_32)
ENTRY, ACTOR, OTHER, MAP, OUTPUT, VTABLE = 0x401000, 0x408000, 0x409000, 0x40a000, 0x40c000, 0x407400
CALLS, DETOURS = 0x40a100, 0x40a104


def terrain_cases():
    base = Owner(x=64, y=60, width=8, height=8, class_mask_e4=0x11)
    result = []
    for tile in (0, 1, 2, 3, 4, 5):
        for layer in (0, 1, 2):
            for scalar in (0, 1):
                if tile != 1 and scalar == 1:
                    continue
                owner = replace(base, layer498=layer, scalar21c=scalar)
                result.append((f"tile{tile}_layer{layer}_scalar{scalar}", owner, tile, None))
    for name, changes in [
        ("negative_x", dict(x=-1)), ("negative_y", dict(y=-1)),
        ("upper_x_equal", dict(x=224)), ("upper_y_equal", dict(y=120)),
        ("last_center_inside", dict(x=223, y=119)),
        ("no_bounds_class_outside", dict(x=-1, class_mask_e4=0)),
        ("mask21_bounds_off", dict(x=-1, class_mask_e4=0x21, data_bounds1d=False)),
        ("mask21_bounds_on", dict(x=-1, class_mask_e4=0x21, data_bounds1d=True)),
        ("zero_footprint_blocked_tile", dict(width=0, height=0)),
    ]:
        result.append((name, replace(base, **changes), 2 if "footprint" in name else 0, None))
    for name, rect in [("rect_center_inside_overrides_tile2", (60, 50, 10, 20)),
                       ("rect_upper_x_exclusive", (54, 50, 10, 20)),
                       ("rect_center_outside", (0, 0, 10, 10))]:
        result.append((name, base, 2, rect))
    return result


def pair_cases():
    actor = Owner(x=50, y=50, width=10, height=10, class_mask_e4=0x11)
    other = Owner(x=55, y=50, width=10, height=10, class_mask_e4=0x21, data_type8=2)
    result = [("pair_neither_mask21", actor, replace(other, class_mask_e4=0x11)),
              ("pair_no_xy_overlap", actor, replace(other, x=100)),
              ("pair_touching_bounds", actor, replace(other, x=60)),
              ("pair_zero_width", replace(actor, width=0), other),
              ("pair_ignores_z", replace(actor, z=1000), replace(other, z=-1000))]
    for datatype in (0, 1, 2, 3, 4, 5):
        for layer in (0, 1):
            result.append((f"pair_other_type{datatype}_layer{layer}", actor,
                           replace(other, data_type8=datatype, layer498=layer)))
    for scalar in (0, 1):
        result.append((f"pair_other_type1_actor_scalar{scalar}", replace(actor, scalar21c=scalar), replace(other, data_type8=1)))
    ignored = replace(other, ignore4d4=[actor])
    result.append(("pair_other_ignore_contains_actor", actor, ignored))
    self_special = replace(actor, class_mask_e4=0x21, data_type8=2)
    plain = replace(other, class_mask_e4=0x11)
    result.append(("pair_self_type2", self_special, plain))
    result.append(("pair_self_type2_ignore", replace(self_special, ignore4d4=[plain]), plain))
    return result


def wrapper_cases():
    result = []
    for name, state, status, scan, entries in [
        ("status16_state22_empty", 22, True, False, []),
        ("status16_state5_empty", 5, True, False, []),
        ("status16_off_delegates", 22, False, False, []),
        ("webpull_active_delegates", 22, True, True, [(True, True, True)]),
        ("webpull_inactive_final_pointer_delegates", 22, True, True, [(True, True, False)]),
        ("later_failed_cast_clears_pointer", 22, True, True, [(True, True, False), (True, False, False)]),
        ("foreign_owner_does_not_clear_pointer", 22, True, True, [(True, True, False), (False, False, False)]),
        ("active_break_ignores_later_failed_cast", 22, True, True, [(True, True, True), (True, False, False)]),
    ]:
        owner = Owner(native_state=state, status16_active=status, appendage_scan_flag184=scan)
        owner.appendages = [Appendage(owner if same_owner else Owner(), cast, active) for same_owner, cast, active in entries]
        result.append((name, owner, entries))
    return result


def relocate(va, size, new_va, calls=None, tables=()):
    body = bytearray(original_bytes(va, size))
    calls = calls or {}
    for ins in md.disasm(body, va):
        if ins.mnemonic == "call" and len(ins.bytes) == 5 and ins.bytes[0] == 0xe8:
            old_target = ins.address + 5 + struct.unpack("<i", ins.bytes[1:])[0]
            target = calls[old_target]
            off = ins.address - va
            body[off + 1:off + 5] = u32(target - (new_va + off + 5))
    for table_va, count in tables:
        body = bytearray(bytes(body).replace(u32(table_va), u32(new_va + table_va - va)))
        for index in range(count):
            off = table_va - va + index * 4
            old = struct.unpack_from("<I", body, off)[0]
            struct.pack_into("<I", body, off, new_va + old - va)
    return body


def build():
    image = bytearray(build_harness([]))
    pe = pefile.PE(data=image)

    def write(va, data):
        offset = pe.get_offset_from_rva(va - BASE)
        image[offset:offset + len(data)] = data

    write(0x50f000, bytes(0x2000))
    # Helpers are synthetic map shape / tile getters; the complete decision
    # function, rectangle helper, z callback, response wrappers and pair predicate
    # below are copied native bytes, with only relocation fixups.
    stubs = {}
    method_cursor = 0x407000

    def stub(name, data):
        nonlocal method_cursor
        stubs[name] = method_cursor
        write(method_cursor, data)
        method_cursor += 0x20
        return stubs[name]

    def getter(name, offset):
        return stub(name, b"\x8b\x81" + u32(offset) + b"\xc3")

    mask = stub("mask", original_bytes(0x498ff0, 0x17))
    slot_map = {0x2c: mask}
    for slot, offset in [(0x94, 0x20), (0x98, 0x24), (0x1fc, 0x2c), (0x200, 0x30),
                         (0x20c, 0x34), (0x210, 0x38), (0x214, 0x3c), (0x218, 0x40),
                         (0x208, 0x44), (0x204, 0x44), (0x1c4, 0x48)]:
        slot_map[slot] = getter(f"field_{offset:x}", offset)
    slot_map[0x33c] = stub("data_pointer", bytes.fromhex("8d8100030000c3"))
    slot_map[0x248] = 0x50fb00
    slot_map[0x57c] = stub("detour_record", b"\xff\x05" + u32(DETOURS) + b"\xc2\x04\x00")
    slot_map[0x64] = stub("scan_flag", bytes.fromhex("8a8184010000c3"))
    slot_map[0x3c4] = getter("appendage_list", 0x12dc)
    slot_map[0x410] = stub("status_active_fixture", bytes.fromhex("8a8100050000c20400"))
    slot_map[0x230] = getter("state_fixture", 0x155c)
    active_stub = stub("appendage_active", bytes.fromhex("8a410cc3"))
    cast_stub = stub("cast_fixture", bytes.fromhex("8b44240483780800750231c0c3"))
    delegate_stub = stub("delegate_fixture", b"\xff\x05" + u32(CALLS) + b"\xb8\x01\x00\x00\x00\xc2\x0c\x00")
    attachment = stub("attachment_record", b"\xff\x05" + u32(CALLS) + b"\xc2\x0c\x00")
    for slot, target in slot_map.items():
        write(VTABLE + slot, u32(target))
    write(0x407c00 + 0x1c, u32(attachment))
    write(0x407d00 + 0x60, u32(active_stub))
    helper_calls = {0x8adab0: 0x50f400,
                    0x4869d0: getter("extension_blocks", 0x20),
                    0x486ca0: getter("base_height", 0x24),
                    0x486a70: getter("total_columns", 0x28),
                    0x486c30: getter("total_rows", 0x2c),
                    0x485580: stub("tile_lookup", b"\x8b\x41\x30\xc2\x08\x00")}
    write(0x50f000, relocate(0x485950, 0x2f0, 0x50f000, helper_calls, [(0x485c30, 4)]))
    write(0x50f400, original_bytes(0x8adab0, 0x34))
    write(0x50f500, original_bytes(0x4ac100, 0x11))
    write(0x50f600, relocate(0x4b97b0, 0x51, 0x50f600, {0x4e8a30: 0x50f700}))
    write(0x50f700, original_bytes(0x4e8a30, 0x43))
    write(0x50f800, relocate(0x4eb600, 0x180, 0x50f800,
                           {0x484670: 0x50fc00, 0x4eb1d0: 0x50fa00}, [(0x4eb760, 4), (0x4eb770, 4)]))
    write(0x50fa00, original_bytes(0x4eb1d0, 0x49))
    write(0x50fb00, original_bytes(0x4e81d0, 0x84))
    write(0x50fc00, original_bytes(0x484670, 0x12))
    write(0x50fd00, relocate(0x4b00f0, 0x117, 0x50fd00, {0xc00d0b: cast_stub, 0x4e7dd0: delegate_stub}))
    code, records = bytearray(), []

    def emit(data):
        code.extend(data)

    def push(value):
        emit(b"\x68" + u32(value))

    def mem(address, value):
        emit(b"\xc7\x05" + u32(address) + u32(value))

    def call(target):
        start = ENTRY + len(code)
        emit(b"\xe8" + u32(target - start - 5))

    def clear():
        emit(b"\xbf" + u32(ACTOR) + b"\x31\xc0\xb9" + u32(0x1800 // 4) + b"\xf3\xab")
        mem(CALLS, 0)
        mem(DETOURS, 0)

    def owner_fields(address, owner):
        left, top, right, bottom = owner.bounds()
        for off, value in [(0, VTABLE), (0x20, owner.x), (0x24, owner.y), (0x28, owner.z),
                           (0x2c, owner.width), (0x30, owner.height), (0x34, left), (0x38, right),
                           (0x3c, top), (0x40, bottom), (0x44, owner.scalar21c), (0x48, owner.layer498),
                           (0xe4, owner.class_mask_e4), (0x308, owner.data_type8),
                           (0x31c, int(owner.data_bounds1d) << 8)]:
            mem(address + off, value)

    def capture(name, expected, kind, fields):
        emit(b"\x25" + u32(0xff))
        dest = OUTPUT + len(records) * 20
        emit(b"\xa3" + u32(dest))
        for i, source in enumerate([CALLS, DETOURS], 1):
            emit(b"\xa1" + u32(source) + b"\xa3" + u32(dest + i * 4))
        mem(dest + 12, 0)
        mem(dest + 16, 0)
        records.append(dict(name=name, expected=expected, kind=kind, inputs=fields))

    for value in [-0x80000000, -1, 0, 1, 0x7fffffff]:
        clear()
        push(value)
        call(0x50f500)
        capture(f"z_{value}", bool(z_allowed(value)), "z", dict(z=value))
    for name, owner, tile, rect in terrain_cases():
        clear()
        owner_fields(ACTOR, owner)
        terrain = Terrain(1, 10, tile_at=lambda x, y, tile=tile: tile,
                          rectangles174=[rect] if rect else [])
        for off, value in [(0x20, 0), (0x24, 120), (0x28, 14), (0x2c, 10), (0x30, tile),
                           (0x218, MAP + 0x800), (0x21c, MAP + 0x800 + 36)]:
            mem(MAP + off, value)
        if rect:
            mem(MAP + 0x174, MAP + 0x900)
            mem(MAP + 0x178, MAP + 0x910)
            for i, value in enumerate(rect):
                mem(MAP + 0x900 + i * 4, value)
        push(ACTOR)
        emit(b"\xb9" + u32(MAP))
        call(0x50f000)
        capture(name, bool(terrain_allowed(owner, terrain)), "terrain",
                dict(owner=asdict(owner), tile=tile, rectangle=rect))
    for name, a, b in pair_cases():
        clear()
        owner_fields(ACTOR, a)
        owner_fields(OTHER, b)
        # Only identity membership matters to 4EB1D0; map fixture storage to the
        # two native object addresses without copying Python object ids.
        for address, own, target, other in [(ACTOR, a, OTHER, b), (OTHER, b, ACTOR, a)]:
            if any(item is other for item in own.ignore4d4):
                mem(address + 0x4d4, MAP + address - ACTOR + 0x800)
                mem(address + 0x4d8, MAP + address - ACTOR + 0x804)
                mem(MAP + address - ACTOR + 0x800, target)
        push(OTHER)
        emit(b"\xb9" + u32(ACTOR))
        call(0x50f800)
        capture(name, bool(pair_blocks(a, b)), "pair",
                dict(a={k: v for k, v in asdict(a).items() if k not in ["ignore4d4", "appendages"]},
                     b={k: v for k, v in asdict(b).items() if k not in ["ignore4d4", "appendages"]},
                     a_ignores_b=any(item is b for item in a.ignore4d4),
                     b_ignores_a=any(item is a for item in b.ignore4d4)))
    for name, owner, entries in wrapper_cases():
        clear()
        mem(ACTOR, VTABLE)
        mem(ACTOR + 0x184, int(owner.appendage_scan_flag184))
        mem(ACTOR + 0x500, int(owner.status16_active))
        mem(ACTOR + 0x155c, owner.native_state)
        mem(ACTOR + 0x12dc, MAP + 0x600)
        mem(MAP + 0x604, MAP + 0x640)
        mem(MAP + 0x608, MAP + 0x640 + len(entries) * 4)
        for i, (same_owner, cast, active) in enumerate(entries):
            pointer = MAP + 0x800 + i * 0x40
            mem(MAP + 0x640 + i * 4, pointer)
            for off, value in [(0, 0x407d00), (4, ACTOR if same_owner else OTHER), (8, int(cast)), (12, int(active))]:
                mem(pointer + off, value)
        push(0)
        push(60)
        push(64)
        emit(b"\xb9" + u32(ACTOR))
        call(0x50fd00)
        branch = wrapper_branch(owner)
        capture(name, dict(allowed=True if branch is None else branch, delegated=branch is None),
                "wrapper", dict(native_state=owner.native_state, status16_active=owner.status16_active,
                                scan_flag184=owner.appendage_scan_flag184, entries=entries))
    for axis, live, detour, attachments in [(0, False, -1, 2), (0, True, -1, 2), (1, True, -1, 1),
                                             (2, True, -1, 2), (-1, True, -1, 0), (0, True, 1, 2)]:
        clear()
        mem(ACTOR, VTABLE)
        mem(ACTOR + 0x1604, 0x01010000 if live else 0)
        mem(ACTOR + 0x1678, detour)
        for i in range(attachments):
            mem(ACTOR + [0x148, 0x154][i], MAP + 0x200 + i * 0x100)
            mem(MAP + 0x200 + i * 0x100, 0x407c00)
        push(0x1234)
        push(0x43fa0000)  # velocity500 float bits, opaque to response wrappers
        push(axis)
        emit(b"\xb9" + u32(ACTOR))
        call(0x50f600)
        effects = response_effects(axis, 500.0, "fixture", "a" if attachments else None,
                                   "b" if attachments == 2 else None,
                                   live_x=live, live_y=live, detour1678=detour)
        capture(f"response_axis{axis}_live{int(live)}_detour{detour}_attachments{attachments}",
                dict(attachments=attachments, detours=sum(e["kind"] == "owner_v57c" for e in effects)),
                "response", dict(axis=axis, live_x=live, live_y=live, detour=detour, attachments=attachments))
    push(-11)
    emit(b"\xff\x15" + u32(0x40e0e0))
    push(0)
    push(MAP + 0x108)
    push(len(records) * 20)
    push(OUTPUT)
    emit(b"\x50\xff\x15" + u32(0x40e0e4))
    push(0)
    emit(b"\xff\x15" + u32(0x40e0e8))
    assert len(code) < 0x6000, len(code)
    assert len(records) * 20 < 0x2000
    write(ENTRY, code)
    return bytes(image), records


def main():
    image, records = build()
    exe = DEST / "native-owner-harness.exe"
    exe.write_bytes(image)
    result = subprocess.run([str(exe)], cwd=DEST, capture_output=True, timeout=20)
    (DEST / "native-owner-output.bin").write_bytes(result.stdout)
    if result.returncode != 0 or len(result.stdout) != len(records) * 20:
        raise RuntimeError(f"owner fixture exit={result.returncode:#x}; bytes={len(result.stdout)} expected={len(records)*20}")
    mismatches = []
    for i, record in enumerate(records):
        returned, attachments, detours, _, _ = struct.unpack_from("<5I", result.stdout, i * 20)
        if record["kind"] == "response":
            native = dict(attachments=attachments, detours=detours)
        elif record["kind"] == "wrapper":
            native = dict(allowed=bool(returned), delegated=bool(attachments))
        else:
            native = bool(returned)
        record["native"] = native
        record["matches"] = native == record["expected"]
        if not record["matches"]:
            mismatches.append(record)
    report = dict(kind="relocated original owner decision instructions in synthetic PE32; not DFO runtime capture",
                  source_sha256=SOURCE_HASH, harness_sha256=hashlib.sha256(image).hexdigest(),
                  output_sha256=hashlib.sha256(result.stdout).hexdigest(), matches=len(records)-len(mismatches),
                  mismatches=len(mismatches), vectors=records,
                  scope=["4AC100 signed z predicate", "485950 complete bounds/rect/grid decision function + original8ADAB0",
                         "4EB600 original pair predicate,4E81D0 bounds,4EB1D0 list membership,484670 scalar check",
                         "4B00F0 original wrapper decision function with fixture status/cast/delegate callbacks",
                         "4B97B0 and4E8A30 original response wrapper call gates"],
                  fixtures=["virtual getters return supplied synthetic x/y/footprint/layer/scalar/data values",
                            "terrain lookup is a uniform tile fixture, not original485580 storage",
                            "map shape helpers return fixture dimensions; two objects share a synthetic vtable",
                            "attachments record calls; detour+57C records calls without its implementation"])
    (DEST / "native-owner-vectors.json").write_text(json.dumps(report, ensure_ascii=False, indent=2)+"\n", encoding="utf-8")
    print(json.dumps(dict(matches=report["matches"], mismatches=len(mismatches), cases=len(records))))
    if mismatches:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
