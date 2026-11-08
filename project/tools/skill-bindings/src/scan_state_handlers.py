"""Scan swordman setState handlers (CE1998[state-3]) for etc-motion index
and related immediates.

Patterns (MSVC thiscall, ecx = character):
  mov edx,[eax+slot32]; push imm8; mov ecx,esi; call edx   -> (slot, imm) vtable call
  push imm8; mov ecx,esi; call rel32                        -> direct call w/ imm arg
  push imm8; push imm8; mov ecx,esi; call rel32             -> direct call w/ 2 imm args
"""
import json
import os
import re
import struct

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.environ.get("DNF1031_EXE", r"D:\dnf-rebuild\DNF1031客户端\DNF.exe")
IB = 0x400000
TABLE = 0xCE1998
STATES = list(range(3, 80))
WINDOW = 0x600

def va2off(va):
    rva = va - IB
    if 0x1000 <= rva < 0x115A000:
        return rva - 0x1000 + 0x400
    if 0x115A000 <= rva < 0x15D9000:
        return rva - 0x115A000 + 0x1158E00
    raise ValueError(hex(va))

f = open(EXE, "rb")
def read_va(va, n):
    f.seek(va2off(va))
    return f.read(n)

# --- pattern regexes over raw bytes ---
# vtable call: 8b <modrm mod=10 reg=dest rm=base> <disp32> then optional small gap then 6a imm8, 8b ce/cb, ff d0-d7
# we allow the disp32 load and the push/call to be separated by < 6 bytes of fixed junk
vt = re.compile(
    rb"\x8b([\x80-\xbf])"          # mov r32, [r32+disp32]  (mod=10)
    rb"(....)"                      # disp32
    rb"{0,8}?\x6a(.)"               # push imm8 (with up to 8 junk bytes)
    rb"\x8b[\xce\xcb\xcf]"          # mov ecx, esi/ebx/edi
    rb"\xff[\xd0-\xd7]",            # call reg
    re.S,
)
dcall1 = re.compile(
    rb"\x6a(.)\x6a(.)\x8b[\xce\xcb\xcf]\xe8(....)", re.S)
dcall2 = re.compile(
    rb"\x6a(.)\x8b[\xce\xcb\xcf]\xe8(....)", re.S)

def rel(base, b):
    v = struct.unpack("<i", b)[0]
    return base + v

raw = read_va(TABLE, 4 * len(STATES))
entries = struct.unpack(f"<{len(STATES)}I", raw)

result = {}
for idx, handler in enumerate(entries):
    state = idx + 3
    code = read_va(handler, WINDOW)
    rec = {"handler": f"0x{handler:08x}", "vt_calls": [], "direct_calls": []}
    for m in vt.finditer(code):
        modrm = m.group(1)[0]
        disp = struct.unpack("<I", m.group(2))[0]
        imm = m.group(3)[0]
        # reg (dest) = bits 5:3, rm (base) = bits 2:0
        reg = (modrm >> 3) & 7
        rm = modrm & 7
        rec["vt_calls"].append({
            "slot": disp, "imm": imm, "dest_reg": reg, "base_reg": rm,
            "at": f"0x{handler + m.start():08x}",
        })
    for m in dcall1.finditer(code):
        at = handler + m.start() + 6  # after two pushes + mov ecx
        target = rel(at + 1 + 4 - 5 + 5, m.group(3)) if False else None
        # call addr: pattern is 6a A 6a B 8b ce e8 rel ; e8 starts at m.start()+6-?:
        # bytes: [0]=6a A [2]=6a B [4]=8b ce [6]=e8 rel32 ; next instr at m.start()+11
        e8_off = m.start() + 6
        nxt = handler + e8_off + 5
        target = nxt + struct.unpack("<i", m.group(3))[0]
        rec["direct_calls"].append({"imm_a": m.group(1)[0], "imm_b": m.group(2)[0],
                                     "target": f"0x{target:08x}",
                                     "at": f"0x{handler + e8_off:08x}"})
    for m in dcall2.finditer(code):
        e8_off = m.start() + 4
        nxt = handler + e8_off + 5
        target = nxt + struct.unpack("<i", m.group(2))[0]
        rec["direct_calls"].append({"imm": m.group(1)[0],
                                     "target": f"0x{target:08x}",
                                     "at": f"0x{handler + e8_off:08x}"})
    result[state] = rec

out = os.path.join(BASE, "evidence", "state-handler-scan.json")
json.dump(result, open(out, "w"), indent=1)
print(f"scanned {len(result)} states -> {out}")

# quick report: motion candidates = slot 0x804 imms
print("\nstate -> slot0x804 imms (motion candidates):")
for state in sorted(result, key=int):
    r = result[state]
    motions = [c["imm"] for c in r["vt_calls"] if c["slot"] == 0x804]
    all_slots = sorted({c["slot"] for c in r["vt_calls"]})
    if motions or all_slots:
        print(f"  state {state:>2}: motions={motions} slots={[hex(s) for s in all_slots]}")
