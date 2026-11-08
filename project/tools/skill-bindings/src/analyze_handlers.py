"""Precise state-handler analyzer using capstone.

Tracks vtable slot loads and immediate pushes to identify, per state:
  - etc-motion selection calls (vtable slot, motion index)
  - direct calls with immediate args (ATK thunk 0x70213F, effect attach, etc.)
"""
import json
import os
import sys

sys.path.insert(0, r"D:\dnf-rebuild\gba-research\third_party\research-python")
import capstone
from capstone import CS_ARCH_X86, CS_MODE_32, CS_OP_REG, CS_OP_IMM, CS_OP_MEM, x86

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.environ.get("DNF1031_EXE", r"D:\dnf-rebuild\DNF1031客户端\DNF.exe")
IB = 0x400000
TABLE = 0xCE1998
STATES = list(range(3, 80))
WINDOW = 0x800

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

md = capstone.Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = True

THIS = {"esi", "ebx", "edi"}

def analyze(handler):
    code = read_va(handler, WINDOW)
    regs = {}
    stack = []
    events = []
    pos = 0
    insns = []
    while pos < len(code):
        chunk = insns_slice = list(md.disasm(code[pos:], handler + pos))
        if not chunk:
            pos += 1
            continue
        insns.extend(chunk)
        pos = chunk[-1].address + chunk[-1].size - handler
        if pos < len(code):
            pos += 1  # resync by 1 byte after desync
    for insn in insns:
        m = insn.mnemonic
        ops = insn.operands
        if m == "push":
            if ops and ops[0].type == CS_OP_IMM:
                stack.append(("imm", ops[0].imm))
            else:
                stack.append(("other", insn.op_str))
        elif m == "mov" and len(ops) == 2:
            d, s = ops
            if d.type == CS_OP_REG and s.type == CS_OP_MEM and s.mem.index == 0 and s.mem.base != 0:
                base = insn.reg_name(s.mem.base)
                disp = s.mem.disp
                dn = insn.reg_name(d.reg)
                if base in THIS and disp == 0:
                    regs[dn] = ("vt", base)
                elif regs.get(base, ("?",))[0] == "vt":
                    regs[dn] = ("slot", disp, base)
                else:
                    regs[dn] = ("field", f"[{base}{disp:+#x}]")
            elif d.type == CS_OP_REG and s.type == CS_OP_REG:
                sn = insn.reg_name(s.reg)
                regs[insn.reg_name(d.reg)] = regs.get(sn, ("copy", sn))
            elif d.type == CS_OP_REG:
                regs[insn.reg_name(d.reg)] = ("const", insn.op_str.split(", ", 1)[-1])
        elif m == "xor" and len(ops) == 2 and ops[0].type == CS_OP_REG and ops[1].type == CS_OP_REG and insn.op_str.startswith("e") is False:
            pass
        elif m == "call":
            if ops and ops[0].type == CS_OP_REG:
                rn = insn.reg_name(ops[0].reg)
                tgt = regs.get(rn)
                if tgt and tgt[0] == "slot":
                    events.append({
                        "kind": "vtcall", "slot": tgt[1], "base": tgt[2],
                        "args": [a[1] for a in stack if a[0] == "imm"],
                        "at": f"0x{insn.address:08x}",
                    })
                else:
                    events.append({
                        "kind": "regcall", "target": str(tgt),
                        "args": [a[1] for a in stack if a[0] == "imm"],
                        "at": f"0x{insn.address:08x}",
                    })
            elif ops and ops[0].type == CS_OP_IMM:
                target = ops[0].imm
                events.append({
                    "kind": "call", "target": f"0x{target:08x}",
                    "args": [a[1] for a in stack if a[0] == "imm"],
                    "at": f"0x{insn.address:08x}",
                })
            stack = []
        elif m == "add" and ops and ops[0].type == CS_OP_REG and insn.reg_name(ops[0].reg) == "esp":
            stack = []
    return events

raw = read_va(TABLE, 4 * len(STATES))
import struct
entries = struct.unpack(f"<{len(STATES)}I", raw)

result = {}
for idx, handler in enumerate(entries):
    state = idx + 3
    result[state] = {"handler": f"0x{handler:08x}", "events": analyze(handler)}

out = os.path.join(BASE, "evidence", "state-handler-events.json")
json.dump(result, open(out, "w"), indent=1)
print(f"analyzed {len(result)} states -> {out}")

# Report: per state, all vtcall slots with imm args + calls to known targets
for state in sorted(result, key=int):
    r = result[state]
    vt = [e for e in r["events"] if e["kind"] == "vtcall" and e["args"]]
    dc = [e for e in r["events"] if e["kind"] == "call"]
    parts = []
    for e in vt:
        parts.append(f"slot{e['slot']:+#x}({','.join(str(a) for a in e['args'])})")
    for e in dc:
        parts.append(f"call{e['target']}({','.join(str(a) for a in e['args'])})")
    print(f"state {state:>2}: " + "  ".join(parts))
