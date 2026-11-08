# -*- coding: utf-8 -*-
# 批量反编译 v3: 多分区链式 + 大小过滤 + 进度日志
# 运行: DUMP_PARTS=engine,combat,uilogin idat.exe -A -S this.py -L ... ARAD_workN.i64
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_hexrays, ida_name
import os

PARTS = os.environ.get("DUMP_PARTS", "parsers").split(",")
PROG = r"E:\DOF LX\【40JP逆向源代码工程】\work\bulk_progress.log"

CONFIG = {
    "parsers":  (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_parsers.txt",  [(0x4F0000, 0x510000)]),
    "monster":  (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_monster_ai.txt", [(0x590000, 0x5E0000)]),
    "engine":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_engine.txt",   [(0x400000, 0x420000)]),
    "combat":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_combat_a.txt", [(0x420000, 0x480000)]),
    "uilogin":  (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_ui_login.txt", [(0x540000, 0x590000)]),
    "skills":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_skills.txt",   [(0x5E0000, 0x650000)]),
    "misca":    (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_misc_a.txt",   [(0x480000, 0x4F0000)]),
    "miscb":    (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_misc_b.txt",   [(0x510000, 0x540000)]),
    # 会话 5: 剩余区域 (zlib/PAK/CRT/D3D8/Socket/数据尾)
    "tail_a":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_tail_a.txt",   [(0x650000, 0x6C1000)]),
    "tail_b":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_tail_b.txt",   [(0x650000, 0x68A000)]),
    "tail_c":   (r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_tail_c.txt",   [(0x68A000, 0x6C1000)]),
}

MAXLINES = 110
MAXSIZE = 8000
TOTAL = 0

def plog(s):
    with open(PROG, "a", encoding="utf-8") as f:
        f.write(s + "\n")

for PART in PARTS:
    if PART not in CONFIG:
        plog("SKIP unknown %s" % PART)
        continue
    out_path, ranges = CONFIG[PART]
    plog("=== PART=%s begin ===" % PART)

    seen = set()
    funcs = []
    skipped = []
    for lo, hi in ranges:
        ea = lo
        while ea < hi:
            f = ida_funcs.get_func(ea)
            if f:
                if f.start_ea not in seen:
                    seen.add(f.start_ea)
                    if f.size() <= MAXSIZE:
                        funcs.append(f.start_ea)
                    else:
                        skipped.append((f.start_ea, f.size()))
                ea = f.end_ea if f.end_ea > ea + 16 else ea + 16   # 防死循环
            else:
                ea += 16

    plog("funcs=%d skipped_big=%d" % (len(funcs), len(skipped)))
    lines = ["### BATCH DECOMPILE part=%s" % PART,
             "### funcs=%d (skipped >%dB: %d)" % (len(funcs), MAXSIZE, len(skipped))]
    for ea, sz in sorted(skipped):
        lines.append("## SKIPPED-BIG %08X size=%d (待专项)" % (ea, sz))

    for idx, fea in enumerate(sorted(funcs)):
        if idx % 50 == 0:
            plog("part %s %d/%d" % (PART, idx, len(funcs)))
        nm = ida_name.get_ea_name(fea) or ""
        lines.append("")
        lines.append("// ============================================================")
        lines.append("// %08X  %s" % (fea, nm))
        try:
            cf = ida_hexrays.decompile(fea)
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
    n_trunc = sum(1 for l in lines if "truncated, total" in l)
    if n_trunc > 0:
        plog("!! 守卫: part %s 有 %d 个函数被 MAXLINES 截断——需深度补全通道" % (PART, n_trunc))
    plog("part %s DONE %d" % (PART, len(funcs)))
    TOTAL += len(funcs)

plog("ALL DONE total=%d" % TOTAL)
idc.qexit(0)
