# -*- coding: utf-8 -*-
# P5c: 三核心虚表(CNRDObject/IRDCollisionObject/IRDActiveObject)全槽位去重批反编译
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_hexrays, ida_name

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\decomp_core_vt.txt"

VTS = {
    "CNRDObject": 0x6C3B7C,
    "IRDCollisionObject": 0x6CC52C,
    "IRDActiveObject": 0x6CC7CC,
}

# 收集: 每个虚表 -> [(slot_ofs, func_ea)]
vt_slots = {}
all_funcs = {}   # ea -> set of "VT+slot"
for name, vt in VTS.items():
    slots = []
    a = vt
    while True:
        v = ida_bytes.get_dword(a)
        f = ida_funcs.get_func(v) if v else None
        if v and 0x401000 <= v < 0x6C1000 and f and f.start_ea == v:
            slot_ofs = a - vt
            slots.append((slot_ofs, v))
            all_funcs.setdefault(v, set()).add("%s+%X" % (name, slot_ofs))
            a += 4
        else:
            break
    vt_slots[name] = slots

lines = []
lines.append("### CORE VTABLES")
for name, vt in VTS.items():
    lines.append("%s vt=%08X slots=%d" % (name, vt, len(vt_slots[name])))
lines.append("total unique funcs: %d" % len(all_funcs))
lines.append("")

# 反编译每个去重函数
for ea in sorted(all_funcs):
    tags = ",".join(sorted(all_funcs[ea]))
    nm = ida_name.get_ea_name(ea) or ""
    lines.append("// ============================================================")
    lines.append("// %08X  slots: %s" % (ea, tags))
    lines.append("// name: %s" % nm)
    try:
        cf = ida_hexrays.decompile(ea)
        if cf:
            txt = str(cf).split("\n")
            lines.extend(txt[:120])
            if len(txt) > 120:
                lines.append("// (...truncated %d lines)" % len(txt))
        else:
            lines.append("// (decompile failed)")
    except Exception as e:
        lines.append("// (exception %s)" % e)
    lines.append("")

open(OUT, "w", encoding="utf-8").write("\n".join(lines))
idc.qexit(0)
