"""Read-only, source-bound PE evidence for Monster death investigation.

Raw reference matches are candidates only. Capturing a byte range does not
establish reachability, class identity, or a complete function boundary.
"""
from pathlib import Path
import hashlib
import json
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "analysis/deps"))
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

SOURCE = ROOT / "DFO/DFO_fixed_v3.exe"
RAW = SOURCE.read_bytes()
SHA256 = hashlib.sha256(RAW).hexdigest()
EXPECTED = "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"
if SHA256 != EXPECTED:
    raise RuntimeError("The selected binary differs from the recorded 60US target")
PE = pefile.PE(data=RAW)
BASE = PE.OPTIONAL_HEADER.ImageBase
MD = Cs(CS_ARCH_X86, CS_MODE_32)
MD.detail = True


def off(addr):
    return PE.get_offset_from_rva(addr - BASE)


def va(pos):
    return BASE + PE.get_rva_from_offset(pos)


def data(addr, size):
    pos = off(addr)
    return RAW[pos:pos + size]


def u32(addr):
    return struct.unpack("<I", data(addr, 4))[0]


def asm(addr, size):
    return "\n".join(
        f"{i.address:08x} {i.bytes.hex():24} {i.mnemonic:9} {i.op_str}"
        for i in MD.disasm(data(addr, size), addr)
    ) + "\n"


def capture(addr, size, label, *, status="native_bytes", note="", disassemble=True):
    name = f"{addr:08x}-{label}"
    chunk = data(addr, size)
    item = {
        "source": "DFO/DFO_fixed_v3.exe", "source_sha256": SHA256,
        "va": hex(addr), "rva": hex(addr - BASE),
        "file_offset": off(addr), "length": size,
        "bytes_sha256": hashlib.sha256(chunk).hexdigest(),
        "status": status, "note": note,
    }
    (OUT / (name + ".bin")).write_bytes(chunk)
    if disassemble:
        (OUT / (name + ".asm")).write_text(asm(addr, size), encoding="utf-8")
    item["disassembled"] = disassemble
    (OUT / (name + ".json")).write_text(json.dumps(item, indent=2) + "\n", encoding="utf-8")
    return item


def refs(addr):
    result = []
    for hit in re.finditer(re.escape(struct.pack("<I", addr)), RAW):
        result.append({"kind": "raw_absolute_candidate", "va": hex(va(hit.start()))})
    for sec in PE.sections:
        if not sec.Characteristics & 0x20000000:
            continue
        start, size = sec.PointerToRawData, sec.SizeOfRawData
        for hit in re.finditer(b"[\xe8\xe9]", RAW[start:start + size]):
            pos = start + hit.start()
            target = (va(pos) + 5 + struct.unpack_from("<i", RAW, pos + 1)[0]) & 0xffffffff
            if target == addr:
                result.append({"kind": "raw_rel32_candidate", "va": hex(va(pos))})
    return result


if __name__ == "__main__":
    op = sys.argv[1]
    addr = int(sys.argv[2], 0)
    if op == "asm":
        print(asm(addr, int(sys.argv[3], 0)))
    elif op == "capture":
        print(json.dumps(capture(addr, int(sys.argv[3], 0), sys.argv[4]), indent=2))
    elif op == "refs":
        print(json.dumps(refs(addr), indent=2))
    elif op == "table":
        count = int(sys.argv[3], 0)
        print(json.dumps([{"slot": hex(i * 4), "target": hex(u32(addr + i * 4))} for i in range(count)], indent=2))
