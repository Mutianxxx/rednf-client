# -*- coding: utf-8 -*-
# 重新反编译 combat 区块被截断的函数 + 巨型跳过函数（0x4471E0 战斗分发器）
# 运行: DUMP_LIST=... idat.exe -A -S this.py -L ... <db.i64>
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_hexrays, ida_name
import os, re

LIST = os.environ.get("DUMP_LIST", r"E:\DOF LX\【40JP逆向源代码工程】\work\redump_list.txt")
OUT  = os.environ.get("DUMP_OUT",  r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_combat_full.txt")
NOSPLIT = int(os.environ.get("DUMP_NOSPLIT", "0"))   # 1 = 不截断

vas = []
for ln in open(LIST, encoding="utf-8"):
    ln = ln.strip()
    if not ln: continue
    vas.append(int(ln, 16))

lines = ["### FULL DECOMPILE combat (truncated + big)"]
lines.append("### funcs=%d" % len(vas))

for n, fea in enumerate(vas):
    nm = ida_name.get_ea_name(fea) or ""
    lines.append("")
    lines.append("// ============================================================")
    lines.append("// %08X  %s" % (fea, nm))
    try:
        cf = ida_hexrays.decompile(fea)
        if cf:
            txt = str(cf).split("\n")
            lines.extend(txt)
            lines.append("// (end total %d lines)" % len(txt))
        else:
            lines.append("// (decomp failed)")
    except Exception as e:
        lines.append("// (exception %s)" % str(e)[:120])
    if n % 10 == 0:
        open(OUT + ".part", "w", encoding="utf-8").write("\n".join(lines))

open(OUT, "w", encoding="utf-8").write("\n".join(lines))
print("DONE full redump %d funcs" % len(vas))
