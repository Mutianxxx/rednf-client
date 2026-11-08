# -*- coding: utf-8 -*-
# 巨型函数专项 dump: 一次只跑一个, MAXLINES 放宽到 2000
import idaapi, idc, ida_hexrays, ida_funcs, ida_name, os

TARGETS = [0x4471E0, 0x4ABE10, 0x4C5250, 0x4C9950, 0x510F30, 0x51BA00,
           0x53A220, 0x57A980, 0x583B90, 0x5E1000, 0x5E78C0, 0x5EA970,
           0x5F10C0, 0x5F39F0]

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_bigfuncs.txt"
PROG = r"E:\DOF LX\【40JP逆向源代码工程】\work\bigfuncs_progress.log"

# 环境变量选单个目标(避免一次跑 14 个巨型函数时中断)
sel = os.environ.get("BIGVA", "")
if sel:
    TARGETS = [int(sel, 16)]

def plog(s):
    with open(PROG, "a", encoding="utf-8") as f:
        f.write(s + "\n")

mode = "a" if sel else "w"
for va in TARGETS:
    plog("begin %08X" % va)
    nm = ida_name.get_ea_name(va) or ""
    f = ida_funcs.get_func(va)
    sz = f.size() if f else 0
    lines = ["", "// ============================================================",
             "// %08X  %s  size=%d" % (va, nm, sz)]
    try:
        cf = ida_hexrays.decompile(va)
        if cf:
            txt = str(cf).split("\n")
            lines.extend(txt[:2000])
            if len(txt) > 2000:
                lines.append("// (...truncated, total %d lines)" % len(txt))
        else:
            lines.append("// (decomp failed)")
    except Exception as e:
        lines.append("// (exception %s)" % str(e)[:100])
    with open(OUT, mode, encoding="utf-8") as fo:
        fo.write("\n".join(lines))
    plog("done %08X lines=%d" % (va, len(lines)))

idc.qexit(0)
