# -*- coding: utf-8 -*-
# P2: 全库 RTTI TypeDescriptor + Complete Object Locator + vtable 完整扫描
# 产出: 类名 -> TD/COL/vftable 地址 + 全部方法槽位
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_segment

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\data\rtti_vtable_map.txt"
OUT2 = r"E:\DOF LX\【40JP逆向源代码工程】\data\class_method_slots.txt"

TEXT_LO, TEXT_HI = 0x401000, 0x6C1000
RD_LO, RD_HI = 0x6C14F8, 0x77F000
DT_LO, DT_HI = 0x77F000, 0x9D6000

def img_bytes(lo, hi):
    return ida_bytes.get_bytes(lo, hi - lo) or b""

# ---------- 1. 扫 TypeDescriptor: ".?AV"/".?AU" (class/struct) ----------
td_map = {}  # td_va -> name
for lo, hi, tag in [(RD_LO, RD_HI, ".rdata"), (DT_LO, DT_HI, ".data")]:
    buf = img_bytes(lo, hi)
    i = 0
    while True:
        i = buf.find(b".?A", i)
        if i < 0:
            break
        # 提取名字 (ASCII 至 \0)
        j = buf.find(b"\x00", i)
        if j < 0 or j - i > 256:
            i += 3
            continue
        name = buf[i:j].decode("ascii", "replace")
        td_va = lo + i - 8  # TypeDescriptor: vfptr(0) spare(4) name(8)
        td_map[td_va] = name
        i = j
log = []
log.append("### TYPE DESCRIPTORS: %d" % len(td_map))

# ---------- 2. 扫 COL: .rdata 中 dword == TD VA (COL+0xC) ----------
td_va_set = set(td_map)
col_map = {}  # col_va -> td_va
buf = img_bytes(RD_LO, RD_HI)
import struct
for off in range(0, len(buf) - 4, 4):
    v = struct.unpack_from("<I", buf, off)[0]
    if v in td_va_set:
        col_va = RD_LO + off - 0xC
        sig = struct.unpack_from("<I", buf, off - 0xC)[0] if off >= 0xC else 0
        if sig == 0:  # COL signature (x86 = 0)
            col_map[col_va] = v
log.append("### COMPLETE OBJECT LOCATORS: %d" % len(col_map))

# ---------- 3. 找 vtable: .rdata 中 dword == COL VA, vtable 起始于其后 4 字节 ----------
col_va_set = set(col_map)
vtables = {}  # vt_va -> col_va
for off in range(0, len(buf) - 4, 4):
    v = struct.unpack_from("<I", buf, off)[0]
    if v in col_va_set:
        vtables[RD_LO + off + 4] = v
log.append("### VTABLES FOUND: %d" % len(vtables))

# ---------- 4. dump 每张虚表的槽位 ----------
def is_func(va):
    f = ida_funcs.get_func(va)
    return f is not None and f.start_ea == va

slot_lines = []
for vt_va in sorted(vtables):
    col_va = vtables[vt_va]
    td_va = col_map[col_va]
    name = td_map.get(td_va, "?")
    slots = []
    a = vt_va
    # 前向读槽位
    while True:
        v = ida_bytes.get_dword(a)
        if TEXT_LO <= v < TEXT_HI and is_func(v):
            slots.append(v)
            a += 4
        else:
            break
    slot_lines.append("CLASS %s" % name)
    slot_lines.append("  TD=%08X COL=%08X VT=%08X slots=%d" % (td_va, col_va, vt_va, len(slots)))
    for i, s in enumerate(slots):
        slot_lines.append("  +%-5d %08X" % (i * 4, s))
    log.append("VT %08X  TD %08X  slots=%-4d %s" % (vt_va, td_va, len(slots), name))

with open(OUT, "w", encoding="utf-8") as f:
    f.write("\n".join(log))
with open(OUT2, "w", encoding="utf-8") as f:
    f.write("\n".join(slot_lines))

idc.qexit(0)
