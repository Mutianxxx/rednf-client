# -*- coding: utf-8 -*-
# P4b-3: 相机每帧更新(41C1E0) + 变焦推进族 + 475810
import idaapi, idautils, idc, ida_hexrays

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\decomp_cam_verify2.txt"
lines = []
def dump_at(ea, tag, maxlines=300):
    lines.append("// ===== %s @ %08X =====" % (tag, ea))
    try:
        cf = ida_hexrays.decompile(ea)
        lines.append(str(cf) if cf else "// (failed)")
    except Exception as e:
        lines.append("// (exception %s)" % e)
    lines.append("")

for ea, tag in [
    (0x41C1E0, "camera frame update (main loop byte_77F280 branch)"),
    (0x475810, "one-shot shake 85/100"),
    (0x424680, "zoom per-frame A"),
    (0x424760, "quad submit / zoom per-frame B"),
    (0x423910, "global zoom getter?"),
    (0x424980, "zoom consumer C"),
    (0x424F00, "zoom consumer D"),
    (0x4253E0, "zoom consumer E"),
]:
    dump_at(ea, tag)

with open(OUT, "w", encoding="utf-8") as fo:
    fo.write("\n".join(lines))
idc.qexit(0)
