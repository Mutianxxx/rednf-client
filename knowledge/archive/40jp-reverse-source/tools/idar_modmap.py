# -*- coding: utf-8 -*-
# P3: 模块分区扫描 —— 每个 64K 块的函数画像 + 字符串引用采样
# 产出: data/module_partition.txt
import idaapi, idautils, idc, ida_funcs, ida_bytes, ida_name
import struct, collections

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\data\module_partition.txt"

TEXT_LO, TEXT_HI = 0x401000, 0x6C1000

# 字符串地图: data_va -> (len, type)  —— 用 IDA 字符串列表
str_map = {}
sc = idautils.Strings()
for s in sc:
    try:
        str_map[s.ea] = str(s)
    except Exception:
        pass

rep = []
blocks = {}
for fea in idautils.Functions():
    blk = fea >> 16
    b = blocks.setdefault(blk, {"n": 0, "named": 0, "sub": 0, "strs": collections.Counter(), "sf": set()})
    b["n"] += 1
    nm = ida_name.get_ea_name(fea) or ""
    if nm and not nm.startswith("sub_"):
        b["named"] += 1
    else:
        b["sub"] += 1
    # 引用的字符串（遍历函数内全部指令项）
    cnt = 0
    for it in idautils.FuncItems(fea):
        for dr in idautils.DataRefsFrom(it):
            if dr in str_map:
                s = str_map[dr]
                if len(s) >= 4 and cnt < 60:
                    b["strs"][s] += 1
                    cnt += 1
                    b["sf"].add(fea)

rep.append("### MODULE PARTITION (64K blocks)")
for blk in sorted(blocks):
    b = blocks[blk]
    rep.append("")
    rep.append("== %04X0000  funcs=%d named=%d sub=%d strfuncs=%d ==" % (blk, b["n"], b["named"], b["sub"], len(b["sf"])))
    # 该块高频字符串 top25
    for s, c in b["strs"].most_common(25):
        ss = s if len(s) <= 70 else s[:67] + "..."
        rep.append("   [%dx] %r" % (c, ss))

with open(OUT, "w", encoding="utf-8") as f:
    f.write("\n".join(rep))
idc.qexit(0)
