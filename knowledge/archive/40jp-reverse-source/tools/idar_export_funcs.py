# -*- coding: utf-8 -*-
# 精确差距审计: 从 IDA 导出全函数表 -> 与源码 VA 覆盖对比
import idaapi, idautils, idc, ida_funcs, ida_name

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\data\ida_all_functions.txt"
lines = []
for fea in sorted(set(idautils.Functions())):
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    nm = ida_name.get_ea_name(fea) or ""
    lines.append("%08X\t%d\t%s" % (fea, f.size(), nm))
open(OUT, "w", encoding="utf-8").write("\n".join(lines))
idc.qexit(0)
