# -*- coding: utf-8 -*-
# P4 试点: 时钟/时间系统反编译 dump
# 目标: 16域积分器(4051A0/4052D0) + 可暂停时钟族(698Fxx-699060) + 引擎消费示例(444C60)
import idaapi, idautils, idc, ida_funcs, ida_hexrays

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\decomp_time.txt"
lines = []

def dump_at(ea, tag):
    lines.append("// ===== %s @ %08X =====" % (tag, ea))
    try:
        cf = ida_hexrays.decompile(ea)
        lines.append(str(cf) if cf else "// (decompile failed)")
    except Exception as e:
        lines.append("// (exception %s)" % e)
    lines.append("")

# 指定函数
for ea, tag in [
    (0x4051A0, "tick_domains_init"),
    (0x4052D0, "tick_domains_step"),
    (0x444C60, "engine_dt_consumer"),
]:
    dump_at(ea, tag)

# 时钟族: 枚举 0x698F00-0x699100 内全部函数
ea = 0x698F00
seen = set()
while ea < 0x699100:
    f = ida_funcs.get_func(ea)
    if f and f.start_ea not in seen:
        seen.add(f.start_ea)
        dump_at(f.start_ea, "clock_region")
    ea += 4

with open(OUT, "w", encoding="utf-8") as fo:
    fo.write("\n".join(lines))
idc.qexit(0)
