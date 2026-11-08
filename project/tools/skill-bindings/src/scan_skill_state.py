"""Extract skill_id -> state pairs from swordman class code.

Pattern (verified at 0xCC52CB..0xCC5419, skill 11 -> state 29):
  call [vt+0x864] with pushed args [1,1,1,skill]   (eligibility transaction)
  ... within a few instructions ...
  call [vt+0x30c] with pushed args [0,1,0,0,state] (setState queue)

Scan range: swordman class code region 0xCB9980..0xCE1998.
"""
import json
import os
import sys

sys.path.insert(0, r"D:\dnf-rebuild\gba-research\third_party\research-python")
import capstone
from capstone import CS_ARCH_X86, CS_MODE_32, CS_OP_REG, CS_OP_IMM, CS_OP_MEM

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.environ.get("DNF1031_EXE", r"D:\dnf-rebuild\DNF1031客户端\DNF.exe")
IB = 0x400000
START = 0xCB9980
END = 0xCE1998

def va2off(va):
    rva = va - IB
    if 0x1000 <= rva < 0x115A000:
        return rva - 0x1000 + 0x400
    raise ValueError(hex(va))

f = open(EXE, "rb")
f.seek(va2off(START))
code = f.read(END - START)

md = capstone.Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = True

THIS = {"esi", "ebx", "edi"}
regs = {}
stack = []
events = []  # (addr, kind, slot_or_target, args)

for insn in md.disasm(code, START):
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
    elif m == "call":
        if ops and ops[0].type == CS_OP_REG:
            rn = insn.reg_name(ops[0].reg)
            tgt = regs.get(rn)
            if tgt and tgt[0] == "slot":
                events.append((insn.address, "vtcall", tgt[1],
                               [a[1] for a in stack if a[0] == "imm"]))
            else:
                events.append((insn.address, "regcall", str(tgt),
                               [a[1] for a in stack if a[0] == "imm"]))
        elif ops and ops[0].type == CS_OP_IMM:
            events.append((insn.address, "call", ops[0].imm,
                           [a[1] for a in stack if a[0] == "imm"]))
        stack = []
    elif m == "add" and ops and ops[0].type == CS_OP_REG and insn.reg_name(ops[0].reg) == "esp":
        stack = []

# pair +0x864 skill calls with following +0x30c state calls
pairs = []
last_864 = None
for addr, kind, tgt, args in events:
    if kind != "vtcall":
        continue
    if tgt == 0x864 and args and isinstance(args[-1], int) and 0 < args[-1] <= 300:
        last_864 = (addr, args[-1])
    elif tgt == 0x30C and args and isinstance(args[-1], int) and args[-1] > 0:
        if last_864 and addr - last_864[0] < 0x60:
            pairs.append({"skill": last_864[1], "state": args[-1],
                          "elig_at": f"0x{last_864[0]:08x}",
                          "queue_at": f"0x{addr:08x}"})
            last_864 = None
        else:
            pairs.append({"skill": None, "state": args[-1],
                          "queue_at": f"0x{addr:08x}"})

json.dump(pairs, open(os.path.join(BASE, "evidence", "skill-state-pairs.json"), "w"), indent=1)

# report
byskill = {}
for p in pairs:
    if p["skill"] is not None:
        byskill.setdefault(p["skill"], set()).add(p["state"])
print(f"pairs: {len(pairs)}, skills mapped: {len(byskill)}")
for s in sorted(byskill):
    print(f"  skill {s:>3} -> states {sorted(byskill[s])}")
print("\nunpaired state queues (first 30):")
n = 0
for p in pairs:
    if p["skill"] is None:
        print(f"  state {p['state']:>3} at {p['queue_at']}")
        n += 1
        if n >= 30:
            break
