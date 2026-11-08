# -*- coding: utf-8 -*-
# 深度补全: 对截断函数(work/truncated_funcs.txt)以 8000 行上限重新反编译
# 用法: FULL_CHUNK=0 FULL_NCHUNKS=3 idat.exe ...
import idaapi, idc, ida_hexrays, ida_name
import os

SRC = r"E:\DOF LX\【40JP逆向源代码工程】\work\truncated_funcs.txt"
OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_full_%s.txt"
PROG = r"E:\DOF LX\【40JP逆向源代码工程】\work\full_progress.log"

CHUNK = int(os.environ.get("FULL_CHUNK", "0"))
NCHUNKS = int(os.environ.get("FULL_NCHUNKS", "3"))
MAXLINES = 8000

targets = []
for line in open(SRC, encoding="utf-8"):
    parts = line.strip().split("\t")
    if parts and parts[0]:
        targets.append(int(parts[0], 16))

my = [va for i, va in enumerate(sorted(targets)) if i % NCHUNKS == CHUNK]

def plog(s):
    with open(PROG, "a", encoding="utf-8") as f:
        f.write("chunk%d: %s\n" % (CHUNK, s))

plog("begin %d" % len(my))
out_path = OUT % CHUNK
lines = ["### FULL FUNCS chunk=%d n=%d" % (CHUNK, len(my))]
for idx, va in enumerate(my):
    if idx % 50 == 0:
        plog("progress %d/%d" % (idx, len(my)))
    nm = ida_name.get_ea_name(va) or ""
    lines.append("")
    lines.append("// ============================================================")
    lines.append("// %08X  %s" % (va, nm))
    try:
        cf = ida_hexrays.decompile(va)
        if cf:
            txt = str(cf).split("\n")
            lines.extend(txt[:MAXLINES])
            if len(txt) > MAXLINES:
                lines.append("// (...truncated, total %d lines)" % len(txt))
        else:
            lines.append("// (decomp failed)")
    except Exception as e:
        lines.append("// (exception %s)" % str(e)[:80])
    if idx % 50 == 49:
        open(out_path, "w", encoding="utf-8").write("\n".join(lines))

open(out_path, "w", encoding="utf-8").write("\n".join(lines))
plog("DONE %d" % len(my))
idc.qexit(0)
