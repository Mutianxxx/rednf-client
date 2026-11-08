# -*- coding: utf-8 -*-
# P2b: RTTI 继承链解析 + 虚方法"定义者"判定 + 函数命名回写 IDA
#
# MSVC x86 RTTI 布局:
#   TypeDescriptor:      +0 vfptr +4 spare +8 name(".?AVxxx@@")
#   COL(x86):            +0 sig +4 vtableOffsetInObject +8 cdOffset +12 pTD +16 pCHD
#   CHD:                 +0 sig +4 attrs +8 numBases +12 pBaseClassArray
#   BaseClassDescriptor: +0 pTD +4 numContainedBases +8 mdisp +12 pdisp +16 vdisp +20 attrs +24 pCHD
#
# 定义者算法: 类 C 槽 i 值为 f，沿基链 root->C 找第一个主虚表槽 i == f 的类 A，
#   definer = A（基优先；即该方法在 A 处引入，C 只是继承）。
# 命名纪律: 只命名当前为 sub_*/unnamed 的函数，绝不覆盖前人已有命名。
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_name
import struct

OUT_HIER = r"E:\DOF LX\【40JP逆向源代码工程】\data\rtti_hierarchy.txt"
OUT_NAMED = r"E:\DOF LX\【40JP逆向源代码工程】\data\rtti_naming_summary.txt"

TEXT_LO, TEXT_HI = 0x401000, 0x6C1000
RD_LO, RD_HI = 0x6C14F8, 0x77F000
DT_LO, DT_HI = 0x77F000, 0x9D6000

def rd(va):
    return ida_bytes.get_dword(va)

def demangle(td_name):
    # ".?AVIObject@nengine@@" -> "nengine::IObject"; ".?AV?$CNString@D@@" -> "CNString<D>"
    n = td_name
    if not n.startswith(".?A"):
        return None
    body = n[4:]
    templ = body.startswith("?$")
    if templ:
        body = body[2:]
    parts = [p for p in body.split("@") if p]
    parts = list(reversed(parts))
    if templ:
        return "_".join(parts)
    return "__".join(parts)

def ida_safe(s):
    out = []
    for ch in s:
        out.append(ch if (ch.isalnum() or ch == "_") else "_")
    return "".join(out)

# ---------- 1. TypeDescriptors ----------
tds = {}  # va -> raw name
for lo, hi in [(RD_LO, RD_HI), (DT_LO, DT_HI)]:
    buf = ida_bytes.get_bytes(lo, hi - lo) or b""
    i = 0
    while True:
        i = buf.find(b".?A", i)
        if i < 0:
            break
        j = buf.find(b"\x00", i)
        if j < 0 or j - i > 300:
            i += 3
            continue
        tds[lo + i - 8] = buf[i:j].decode("ascii", "replace")
        i = j

# ---------- 2. COLs (.rdata) ----------
buf = img = ida_bytes.get_bytes(RD_LO, RD_HI - RD_LO) or b""
td_va_set = set(tds)
cols = {}  # col_va -> (offset_in_obj, td_va, chd_va)
for off in range(0, len(buf) - 20, 4):
    tdv = struct.unpack_from("<I", buf, off + 12)[0]
    if tdv in td_va_set:
        col_va = RD_LO + off
        sig = struct.unpack_from("<I", buf, off)[0]
        if sig != 0:
            continue
        voff = struct.unpack_from("<I", buf, off + 4)[0]
        chd = struct.unpack_from("<I", buf, off + 16)[0]
        cols[col_va] = (voff, tdv, chd)

# ---------- 3. vtables: dword==COL VA in .rdata/.data ----------
vt_by_col = {}  # col_va -> vt_va
for lo, hi in [(RD_LO, RD_HI), (DT_LO, DT_HI)]:
    b2 = ida_bytes.get_bytes(lo, hi - lo) or b""
    for off in range(0, len(b2) - 4, 4):
        v = struct.unpack_from("<I", b2, off)[0]
        if v in cols and (lo + off + 4) not in vt_by_col:
            vt_by_col[v] = lo + off + 4

# ---------- 4. dump vtable slots ----------
def vt_slots(vt_va):
    slots = []
    a = vt_va
    while True:
        v = rd(a)
        f = ida_funcs.get_func(v) if v else None
        if v and TEXT_LO <= v < TEXT_HI and f and f.start_ea == v:
            slots.append(v)
            a += 4
        else:
            break
    return slots

# ---------- 5. 继承链 (CHD -> base class array) ----------
chd_cache = {}
def base_chain(chd_va):
    if chd_va in chd_cache:
        return chd_cache[chd_va]
    try:
        nb = rd(chd_va + 8)
        arr = rd(chd_va + 12)
        chain = []  # root -> ... -> most derived (RTTI 数组顺序即 DFS: 派生在前?)
        # MSVC BaseClassArray: index 0 = most derived self, 然后 base-first DFS
        raw = []
        for i in range(min(nb, 64)):
            bcd = rd(arr + i * 4)
            t = rd(bcd)
            ncb = rd(bcd + 4)
            raw.append((t, ncb))
        # 展开重复基(numContainedBases)生成 root->derived 链
        flat = []
        for t, ncb in raw:
            flat.append(t)
            for _ in range(ncb - 1):
                flat.append(t)
        chain = flat
    except Exception:
        chain = []
    chd_cache[chd_va] = chain
    return chain

# ---------- 6. 组织类: 主 COL(偏移0) -> 主虚表 ----------
class_info = {}  # td_va -> dict
for col_va, (voff, tdv, chd) in cols.items():
    ci = class_info.setdefault(tdv, {"cols": [], "primary_col": None, "vts": []})
    ci["cols"].append(col_va)
    if voff == 0:
        if ci["primary_col"] is None or col_va < ci["primary_col"]:
            ci["primary_col"] = col_va
    ci["vts"].append((voff, vt_by_col.get(col_va)))

for tdv, ci in class_info.items():
    pc = ci["primary_col"]
    ci["primary_vt"] = vt_by_col.get(pc) if pc else None
    ci["chain"] = base_chain(cols[pc][2]) if pc else []
    ci["slots"] = vt_slots(ci["primary_vt"]) if ci["primary_vt"] else []

# ---------- 7. 定义者判定 + 命名 ----------
# 主虚表快照: td_va -> slots (仅主虚表)
pri_slots = {tdv: ci["slots"] for tdv, ci in class_info.items() if ci["slots"]}

def find_definer(chain, slot_idx, fval):
    # chain: root -> C (含 C 自身，RTTI flat 数组顺序: 后段为更派生? 须验证)
    # 实测: BaseClassArray[0] = 自身(most derived)，其后按基优先 —— 因此反转得到 root->C
    for anc in reversed(chain):
        s = pri_slots.get(anc)
        if s is None:
            continue
        if slot_idx < len(s) and s[slot_idx] == fval:
            return anc
    return chain[-1] if chain else None

renamed = 0
kept = 0
naming_log = []
for tdv, ci in sorted(class_info.items()):
    cname = demangle(tds.get(tdv, ""))
    if not cname or cname.startswith("std"):
        continue
    safe = ida_safe(cname)
    # 命名虚表/COL
    if ci["primary_vt"]:
        ida_name.set_name(ci["primary_vt"], "vftbl_%s" % safe, ida_name.SN_CHECK)
    for c in ci["cols"]:
        ida_name.set_name(c, "RTTI_COL_%s_%X" % (safe, c & 0xFFFF), ida_name.SN_WEAK)
    slots = ci["slots"]
    for i, f in enumerate(slots):
        if i * 4 > 0x2000:
            break
        cur = ida_name.get_ea_name(f)
        if cur and not (cur.startswith("sub_") or cur.startswith("unk_") or cur == "" or cur.startswith("loc_")):
            kept += 1
            continue
        dtd = find_definer(ci["chain"], i, f)
        dname = demangle(tds.get(dtd, "")) if dtd else None
        who = ida_safe(dname) if dname else safe
        newname = "%s__vmt%X" % (who, i * 4)
        if ida_name.set_name(f, newname, ida_name.SN_CHECK):
            renamed += 1
            naming_log.append("%s -> %s" % (newname, "%08X" % f))
        else:
            naming_log.append("FAIL %s %08X" % (newname, f))

# ---------- 8. 层级文档 ----------
hier = []
for tdv, ci in sorted(class_info.items(), key=lambda kv: tds.get(kv[0], "")):
    raw = tds.get(tdv, "?")
    nm = demangle(raw) or raw
    chain_names = []
    for a in ci["chain"][-12:]:
        chain_names.append((demangle(tds.get(a, "")) or tds.get(a, "?")[-24:]))
    hier.append("CLASS %s" % nm)
    hier.append("  TD=%08X primaryVT=%s bases(root->derived): %s" % (
        tdv,
        ("%08X" % ci["primary_vt"]) if ci["primary_vt"] else "none",
        " <- ".join(chain_names) if chain_names else "(root)"))
    hier.append("  cols=%d vts=%d slots=%d" % (len(ci["cols"]), len(ci["vts"]), len(ci["slots"])))

with open(OUT_HIER, "w", encoding="utf-8") as f:
    f.write("\n".join(hier))
with open(OUT_NAMED, "w", encoding="utf-8") as f:
    f.write("\n".join([
        "renamed=%d" % renamed,
        "kept_existing=%d" % kept,
        "",
    ] + naming_log[:50]))

idc.qexit(0)
