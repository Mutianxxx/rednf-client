"""Run copied 50FDE0 axis instructions in a minimal PE32 numeric harness.

This does not launch DFO. It supplies synthetic plain-provider virtual methods,
null owner/controller, and original constant bytes. Only combat_motion is written.
Windows x86 support is required to execute the generated PE32. Two explicit x87
control words are checked; neither is asserted to be the client's runtime word.
"""
from dataclasses import asdict
from pathlib import Path
import hashlib
import json
import struct
import subprocess
import sys

from motion_model import Axis, axis_config, f32, step_axis

DEST = Path(__file__).resolve().parent
ROOT = DEST.parents[1]
sys.path.insert(0, str(ROOT / "analysis/deps"))
import pefile

SOURCE = ROOT / "DFO/DFO_fixed_v3.exe"
SOURCE_HASH = "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
raw = SOURCE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == SOURCE_HASH
original = pefile.PE(data=raw)
BASE = 0x400000


def original_bytes(va, size):
    off = original.get_offset_from_rva(va - BASE)
    return raw[off:off + size]


def u32(n):
    return struct.pack("<I", n & 0xffffffff)


def align(n, boundary):
    return (n + boundary - 1) // boundary * boundary


def cases():
    values = [
        ("idle", Axis(), 16),
        ("constant_positive", Axis(0, 600, 0, -1), 16),
        ("constant_negative", Axis(0, -600, 0, -1), 16),
        ("deceleration_before_expiry", Axis(0, 600, -1000, 600), 100),
        ("deceleration_at_expiry", Axis(0, 600, -1000, 600), 600),
        ("deceleration_after_expiry", Axis(0, 600, -1000, 600), 700),
        ("deceleration_negative", Axis(0, -600, 1000, 600), 700),
        ("indefinite_acceleration", Axis(2.5, 100, 20, -1), 40),
        ("zero_dt", Axis(2.5, 100, -20, 10), 0),
        ("zero_remaining_acceleration", Axis(2.5, 100, -20, 0), 40),
        ("displacement_positive_clamp", Axis(5, 300000, 0, -1), 10000),
        ("displacement_negative_clamp", Axis(-5, -300000, 0, -1), 10000),
        ("int32_acceleration_product_wrap", Axis(0, 1, 0x7fffffff, -1), 2),
    ]
    for scale in (1, 850, 999, 1000, 1001, 1500):
        a = axis_config(600, 600, -1000, 1, scale, stop_when_decelerating=True)
        values.append((f"setup_scale_{scale}_at_expiry", a, a.remaining))
        values.append((f"setup_scale_{scale}_cross_expiry", a, a.remaining + 100))
    return values


def build_harness(values, ani_values=()):
    harness = bytearray(0x10000)
    entry_va = 0x401000
    state_va, output_va = 0x408000, 0x409000
    methods_va, vtable_va = 0x404000, 0x405000
    imports_rva, cw53_va, written_va = 0xe000, 0x405020, 0x405024
    # IMAGE_IMPORT_DESCRIPTOR + null descriptor, then DLL/name/thunk tables.
    blob = bytearray(0x200)
    dll_rva, names_rva, ilt_rva, iat_rva = imports_rva + 0x40, imports_rva + 0x60, imports_rva + 0xc0, imports_rva + 0xe0
    blob[0:20] = struct.pack("<5I", ilt_rva, 0, 0, dll_rva, iat_rva)
    blob[0x40:0x40 + 13] = b"kernel32.dll\0"
    cursor = names_rva
    names = ["GetStdHandle", "WriteFile", "ExitProcess"]
    for i, name in enumerate(names):
        encoded = b"\0\0" + name.encode() + b"\0"
        offset = cursor - imports_rva
        blob[offset:offset + len(encoded)] = encoded
        blob[ilt_rva - imports_rva + i * 4:ilt_rva - imports_rva + i * 4 + 4] = u32(cursor)
        blob[iat_rva - imports_rva + i * 4:iat_rva - imports_rva + i * 4 + 4] = u32(cursor)
        cursor = align(cursor + len(encoded), 2)
    harness[imports_rva - 0x1000:imports_rva - 0x1000 + len(blob)] = blob
    iat = BASE + iat_rva
    methods = [
        bytes.fromhex("8b442404d9448104c20400"),  # position get
        bytes.fromhex("8b4424048b54240889548104c20800"),  # position set
        bytes.fromhex("8b442404d9448110c20400"),  # velocity get
        bytes.fromhex("8b4424048b54240889548110c20800"),  # velocity set
    ]
    for i, method in enumerate(methods):
        off = methods_va - entry_va + i * 0x20
        harness[off:off + len(method)] = method
        off = vtable_va - entry_va + i * 4
        harness[off:off + 4] = u32(methods_va + i * 0x20)
    harness[cw53_va - entry_va:cw53_va - entry_va + 2] = struct.pack("<H", 0x027f)
    code = bytearray()

    def emit(b):
        code.extend(b)

    def push(value):
        emit(b"\x68" + u32(value))

    def set_mem(address, value):
        emit(b"\xc7\x05" + u32(address) + u32(value))

    def call(va):
        start = entry_va + len(code)
        emit(b"\xe8" + u32(va - start - 5))

    def capture(source, destination):
        emit(b"\xa1" + u32(source) + b"\xa3" + u32(destination))

    record = 0
    for precision in (64, 53):
        emit(bytes.fromhex("dbe3"))  # FNINIT: 0x037F, precision 64
        if precision == 53:
            emit(b"\xd9\x2d" + u32(cw53_va))
        for _, axis, dt in values:
            emit(b"\xbf" + u32(state_va) + b"\x31\xc0\xb9" + u32(0x80) + b"\xf3\xab")
            set_mem(state_va + 8, vtable_va)
            set_mem(state_va + 0xc, struct.unpack("<I", struct.pack("<f", axis.position))[0])
            set_mem(state_va + 0x18, struct.unpack("<I", struct.pack("<f", axis.velocity))[0])
            set_mem(state_va + 0x24, axis.acceleration)
            set_mem(state_va + 0x30, axis.remaining)
            push(dt)
            push(0)
            emit(b"\xb9" + u32(state_va))
            call(0x50fde0)
            dest = output_va + record * 20
            emit(b"\xa3" + u32(dest + 16))
            for src_off, dst_off in [(0xc, 0), (0x18, 4), (0x24, 8), (0x30, 12)]:
                capture(state_va + src_off, dest + dst_off)
            record += 1
    for precision in (64, 53):
        emit(bytes.fromhex("dbe3"))
        if precision == 53:
            emit(b"\xd9\x2d" + u32(cw53_va))
        for _, delay, rate in ani_values:
            set_mem(state_va + 0x134, struct.unpack("<I", struct.pack("<f", rate))[0])
            set_mem(state_va + 0x1fc, delay)
            emit(b"\xbd" + u32(state_va + 0x200))
            emit(b"\xbe" + u32(state_va))
            emit(bytes.fromhex("31ff"))  # EDI = initial deadline 0
            call(0xa2792f)
            dest = output_va + record * 20
            emit(b"\xa3" + u32(dest))  # negative delta from C01544
            for src_off, dst_off in [(0x12c, 4), (0x134, 8), (0x1fc, 12)]:
                capture(state_va + src_off, dest + dst_off)
            set_mem(dest + 16, 0)
            record += 1
    push(-11)  # STD_OUTPUT_HANDLE
    emit(b"\xff\x15" + u32(iat))
    push(0)
    push(written_va)
    push(record * 20)
    push(output_va)
    emit(b"\x50\xff\x15" + u32(iat + 4))
    push(0)
    emit(b"\xff\x15" + u32(iat + 8))
    assert len(code) < methods_va - entry_va
    assert record * 20 < 0x4000
    harness[:len(code)] = code

    native = bytearray(0x2000)
    native[0xde0:0xde0 + 0x40b] = original_bytes(0x50fde0, 0x40b)
    ani = bytearray(0x1000)
    ani[0x92f:0x94b] = original_bytes(0xa2792f, 0x1c)
    ani[0x94b] = 0xc3  # return after the untouched arithmetic slice
    truncate = bytearray(0x1000)
    truncate[0x544:0x5b9] = original_bytes(0xc01544, 0x75)
    constants = bytearray(0x40000)
    for va, size in [(0xcab8e8, 8), (0xcc11f8, 4), (0xcd4bd0, 4), (0xcd6828, 4), (0xcd682c, 4)]:
        constants[va - 0xca0000:va - 0xca0000 + size] = original_bytes(va, size)
    zero = bytearray(0x1000)
    zero[0x7a4:0x7a8] = original_bytes(0xe9d7a4, 4)
    deadline_constant = bytearray(0x1000)
    deadline_constant[0x53c:0x540] = original_bytes(0xdf053c, 4)
    # The Windows image loader requires successive virtual section extents;
    # reserve the address gaps as zero-filled tails without writing huge files.
    sections = [(b".harness", 0x1000, 0x10e000, harness, 0xe0000020),
                (b".native", 0x10f000, 0x518000, native, 0x60000020),
                (b".ani", 0x627000, 0x1da000, ani, 0x60000020),
                (b".trunc", 0x801000, 0x9f000, truncate, 0x60000020),
                (b".const", 0x8a0000, 0x150000, constants, 0x40000040),
                (b".anicst", 0x9f0000, 0xad000, deadline_constant, 0x40000040),
                (b".zero", 0xa9d000, 0x1000, zero, 0x40000040)]
    headers = bytearray(0x400)
    headers[0:2] = b"MZ"
    struct.pack_into("<I", headers, 0x3c, 0x80)
    headers[0x80:0x84] = b"PE\0\0"
    headers[0x84:0x98] = struct.pack("<HHIIIHH", 0x14c, len(sections), 0, 0, 0, 224, 0x0103)
    opt = 0x98
    struct.pack_into("<HBBIIIIII", headers, opt, 0x10b, 0, 0,
                     len(harness) + len(native) + len(ani) + len(truncate),
                     len(constants) + len(zero) + len(deadline_constant), 0, 0x1000, 0x1000, 0x8a0000)
    struct.pack_into("<III", headers, opt + 28, BASE, 0x1000, 0x200)
    struct.pack_into("<HHHHHH", headers, opt + 40, 4, 0, 0, 0, 4, 0)
    struct.pack_into("<IIIIHH", headers, opt + 52, 0, 0xa9e000, 0x400, 0, 3, 0)
    struct.pack_into("<IIIIII", headers, opt + 72, 0x100000, 0x1000, 0x100000, 0x1000, 0, 16)
    struct.pack_into("<II", headers, opt + 96 + 8, imports_rva, 40)
    out = bytearray(headers)
    for i, (name, rva, virtual_size, data, flags) in enumerate(sections):
        raw_offset = len(out)
        raw_size = align(len(data), 0x200)
        section_header = struct.pack("<8sIIIIIIHHI", name, virtual_size, rva, raw_size, raw_offset, 0, 0, 0, 0, flags)
        start = 0x178 + i * 40
        out[start:start + 40] = section_header
        out.extend(data)
        out.extend(b"\0" * (raw_size - len(data)))
    checked = pefile.PE(data=out)
    assert checked.OPTIONAL_HEADER.ImageBase == BASE
    assert [i.name.decode() for i in checked.DIRECTORY_ENTRY_IMPORT[0].imports] == names
    return bytes(out)


def main():
    values = cases()
    image = build_harness(values)
    executable = DEST / "native-axis-harness.exe"
    executable.write_bytes(image)
    result = subprocess.run([str(executable)], cwd=DEST, capture_output=True, check=False, timeout=20)
    (DEST / "native-vector-output.bin").write_bytes(result.stdout)
    if result.returncode != 0 or len(result.stdout) != len(values) * 2 * 20:
        raise RuntimeError(f"PE32 numeric harness failed: exit={result.returncode:#x}, bytes={len(result.stdout)}, stderr={result.stderr!r}")
    rows, mismatches = [], []
    for mode_index, precision in enumerate((64, 53)):
        for index, (name, initial, dt) in enumerate(values):
            offset = (mode_index * len(values) + index) * 20
            native_bytes = result.stdout[offset:offset + 20]
            pos, vel, acc, remaining, code = struct.unpack("<ffi i i".replace(" ", ""), native_bytes)
            state = Axis(**asdict(initial))
            axes = [state, Axis(), Axis()]
            model_code = step_axis(axes, 0, dt)
            model_bytes = struct.pack("<ffiii", state.position, state.velocity, state.acceleration, state.remaining, model_code)
            match = native_bytes == model_bytes
            row = dict(name=name, x87_precision=precision,
                       x87_control_word="0x037f" if precision == 64 else "0x027f",
                       initial=asdict(initial), dt=dt,
                       native=dict(position=pos, velocity=vel, acceleration=acc, remaining=remaining, result_code=code),
                       native_bytes=native_bytes.hex(), model_bytes=model_bytes.hex(), matches=match)
            rows.append(row)
            if not match:
                mismatches.append(row)
    report = dict(kind="extracted native 50FDE0 instructions executed in a synthetic PE32 process; not DFO runtime capture",
                  source_sha256=SOURCE_HASH, native_va="0x0050fde0", native_size=0x40b,
                  native_code_sha256=hashlib.sha256(original_bytes(0x50fde0, 0x40b)).hexdigest(),
                  harness_sha256=hashlib.sha256(image).hexdigest(),
                  output_sha256=hashlib.sha256(result.stdout).hexdigest(),
                  provider="synthetic plain position/velocity getter/setter; owner/controller null",
                  cases_per_precision=len(values), precisions=[64, 53],
                  matches=len(rows) - len(mismatches), mismatches=len(mismatches), vectors=rows)
    (DEST / "native-vectors.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in ["kind", "cases_per_precision", "precisions", "matches", "mismatches"]}))
    if mismatches:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
