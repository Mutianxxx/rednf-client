# -*- coding: utf-8 -*-
# 缺口补漏 dumper: 从 missing_functions.txt 精确补漏（不依赖地址扫描, 无跳过风险）
# 用法: MISS_CHUNK=0 idat.exe -A -S this.py -L log ARAD_workN.i64
import idaapi, idc, ida_hexrays, ida_name
import os

MISS = r"E:\DOF LX\【40JP逆向源代码工程】\data\missing_functions.txt"
OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_missing_%s.txt"
PROG = r"E:\DOF LX\【40JP逆向源代码工程】\work\missing_progress.log"

CHUNK = int(os.environ.get("MISS_CHUNK", "0"))       # 分片号
NCHUNKS = int(os.environ.get("MISS_NCHUNKS", "3"))   # 总分片数
MAXLINES = 200

targets = []
for line in open(MISS, encoding="utf-8"):
    parts = line.strip().split("\t")
    if len(parts) >= 2:
        targets.append((int(parts[0], 16), int(parts[1])))

# 按分片取模
my = [va for i, (va, sz) in enumerate(sorted(targets)) if i % NCHUNKS == CHUNK]

def plog(s):
    with open(PROG, "a", encoding="utf-8") as f:
        f.write("chunk%d: %s\n" % (CHUNK, s))

plog("begin %d targets" % len(my))
out_path = OUT % CHUNK
lines = ["### MISSING FUNCS chunk=%d n=%d" % (CHUNK, len(my))]
for idx, va in enumerate(my):
    if idx % 100 == 0:
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
    if idx % 200 == 199:
        open(out_path, "w", encoding="utf-8").write("\n".join(lines))

open(out_path, "w", encoding="utf-8").write("\n".join(lines))
plog("DONE %d" % len(my))
idc.qexit(0)
