# -*- coding: utf-8 -*-
# 批量反编译: 按地址区间导出全部函数 (for 子代理源码转写)
# 用法模板: 修改 SECTIONS 后运行
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_hexrays, ida_name

# (输出文件, [(lo, hi, 排除lo, 排除hi)])  —— 排除区用于扣除已还原/CRT
SECTIONS = {
    # 解析器群: 0x4F/0x50 (物品/怪物/NPC/PO 解析器) —— P6
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_parsers.txt": [(0x4F0000, 0x510000)],
    # 怪物 AI: 0x59-0x5D —— P7
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_monster_ai.txt": [(0x590000, 0x5E0000)],
    # 引擎核心: 0x40/0x41 (日志/图像/字体/纹理) —— P6
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_engine.txt": [(0x400000, 0x420000)],
    # 战斗核心其余 + 技能: 0x42-0x47 —— 分批
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_combat_a.txt": [(0x420000, 0x480000)],
    # UI 与登录: 0x54-0x58
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_ui_login.txt": [(0x540000, 0x590000)],
    # 技能区: 0x5E-0x64 (格斗/鬼剑/通用PO/可破坏物/窗口/光环)
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_skills.txt": [(0x5E0000, 0x650000)],
    # 剩余: 0x48-0x4E (技能加载/动画/装备/战斗/特效), 0x51-0x53 (PO/特效/PVP/枪手)
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_misc_a.txt": [(0x480000, 0x4F0000)],
    r"E:\DOF LX\【40JP逆向源代码工程】\work\dump_misc_b.txt": [(0x510000, 0x540000)],
}

MAXLINES = 100   # 每函数截断行数

for out_path, ranges in SECTIONS.items():
    lines = ["### BATCH DECOMPILE"]
    seen = set()
    funcs = []
    for lo, hi in ranges:
        ea = lo
        while ea < hi:
            f = ida_funcs.get_func(ea)
            if f:
                if f.start_ea not in seen:
                    seen.add(f.start_ea)
                    funcs.append(f.start_ea)
                ea = f.end_ea
            else:
                ea += 16
    lines.append("funcs: %d" % len(funcs))
    for fea in sorted(funcs):
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
            lines.append("// (exception)")
    open(out_path, "w", encoding="utf-8").write("\n".join(lines))
    print(out_path, len(funcs))

idc.qexit(0)
