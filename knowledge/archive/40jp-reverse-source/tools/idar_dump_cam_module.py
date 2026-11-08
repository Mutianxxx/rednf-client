# -*- coding: utf-8 -*-
# P4b: 镜头/演出系统 + CNMainGameModule 反编译 dump
import idaapi, idautils, idc, ida_funcs, ida_hexrays

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\decomp_cam_module.txt"
lines = []

def dump_at(ea, tag, maxlines=400):
    lines.append("// ===== %s @ %08X =====" % (tag, ea))
    try:
        cf = ida_hexrays.decompile(ea)
        if cf:
            txt = str(cf).split("\n")
            lines.extend(txt[:maxlines])
            if len(txt) > maxlines:
                lines.append("// (...truncated %d lines)" % len(txt))
        else:
            lines.append("// (decompile failed)")
    except Exception as e:
        lines.append("// (exception %s)" % e)
    lines.append("")

targets = [
    # --- Camera 类虚表方法 ---
    (0x432D70, "Camera seg2 vmt0"),
    (0x4335D0, "Camera vmt0"),
    (0x423A10, "Camera vmt4"),
    (0x432DA0, "Camera vmt8"),
    (0x432DB0, "Camera vmt12"),
    # --- 镜头震动/演出族（自由函数, 操作全局相机 dword_8F7B08）---
    (0x423A80, "lerp helper (区间线性插值)"),
    (0x423200, "cam fx A (fade/flash?)"),
    (0x423380, "cam fx B"),
    (0x424120, "shake entry [shake screen]"),
    (0x424170, "vertical follow"),
    (0x424270, "damage direction indicator"),
    (0x424530, "zoom interpolation"),
    (0x424AB0, "crit shake"),
    (0x424B40, "shake reset 250ms"),
    (0x424BB0, "small shake"),
    (0x424C50, "long shake 3-phase"),
    (0x424D80, "HUD timing"),
    (0x424EA0, "directional shake"),
    # --- CNMainGameModule ---
    (0x41C7C0, "CNMainGameModule vmt0"),
    (0x444C20, "CNMainGameModule vmt8"),
    (0x41F930, "module vmt12 shared"),
    (0x4B1090, "module vmt16 shared"),
    (0x47A920, "CNMainGameModule seg2 vmt0"),
    (0x433690, "main frame loop"),
    (0x41CC80, "module switch handler"),
]
for ea, tag in targets:
    dump_at(ea, tag)

with open(OUT, "w", encoding="utf-8") as fo:
    fo.write("\n".join(lines))
idc.qexit(0)
