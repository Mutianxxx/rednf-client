# -*- coding: utf-8 -*-
# 资源格式与协议侦察: NPK 加载器 + PVF 解析器 + 包名表 + 发包类型穷举
import idaapi, idautils, idc, ida_bytes, ida_funcs, ida_hexrays
import struct

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\recon_npk_pvf.txt"
lines = []
def log(s): lines.append(s)

def dump_func(ea, tag, maxlines=400):
    log("")
    log("// ==================== %s @ %08X ====================" % (tag, ea))
    try:
        cf = ida_hexrays.decompile(ea)
        if cf:
            t = str(cf).split("\n")
            lines.extend(t[:maxlines])
            if len(t) > maxlines:
                log("// (...truncated %d)" % len(t))
        else:
            log("// (decomp failed)")
    except Exception as e:
        log("// (exc %s)" % str(e)[:80])

def find_string(s, seg_lo=0x400000, seg_hi=0x9D6000):
    """全镜像搜 ASCII 串, 返回所有地址"""
    pat = s.encode("ascii")
    hits = []
    ea = seg_lo
    data = ida_bytes.get_bytes(seg_lo, seg_hi - seg_lo)
    i = 0
    while True:
        i = data.find(pat, i)
        if i < 0: break
        # 确认是独立字符串(前一字符为 \0)
        if i == 0 or data[i-1:i] == b"\x00":
            hits.append(seg_lo + i)
        i += 1
    return hits

# ============ 1. 字符串定位 ============
log("### 1. 关键字符串定位")
targets = {}
for s in ["NeoplePack_Bill", "Script.pvf", "_ScriptPacks", "!ScriptPacks",
          "_ImagePacks", "!ImagePacks", "ImagePacks2/"]:
    hits = find_string(s)
    targets[s] = hits
    log("%s -> %s" % (s, ", ".join("%08X" % h for h in hits[:6])))

# ============ 2. NPK: 'NeoplePack_Bill' 的引用者 + 0x40E3E0 ============
log("")
log("### 2. NPK 加载器")
npk_str = targets["NeoplePack_Bill"]
npk_funcs = set()
for sa in npk_str:
    for x in idautils.XrefsTo(sa):
        f = ida_funcs.get_func(x.frm)
        if f:
            npk_funcs.add(f.start_ea)
            log("  str %08X <- ref %08X in func %08X" % (sa, x.frm, f.start_ea))
npk_funcs.add(0x40E3E0)
# 邻域扩展: NPK 函数通常聚集
for fea in sorted(npk_funcs):
    dump_func(fea, "NPK")

# ============ 3. PVF: Script.pvf / _ScriptPacks 引用者 ============
log("")
log("### 3. PVF 解析器")
pvf_funcs = set()
for s in ["Script.pvf", "_ScriptPacks", "!ScriptPacks"]:
    for sa in targets[s]:
        for x in idautils.XrefsTo(sa):
            f = ida_funcs.get_func(x.frm)
            if f:
                pvf_funcs.add(f.start_ea)
                log("  str %08X (%s) <- func %08X" % (sa, s, f.start_ea))
# 一级被调展开（PVF 主加载器调用的解析函数）
primary = sorted(pvf_funcs)
callees = set()
for fea in primary:
    f = ida_funcs.get_func(fea)
    if not f: continue
    ea = f.start_ea
    while ea < f.end_ea:
        for x in idautils.XrefsFrom(ea):
            if x.type in (idaapi.fl_CN, idaapi.fl_CF):
                cf2 = ida_funcs.get_func(x.to)
                if cf2 and 0x400000 <= x.to < 0x6C1000:
                    callees.add(cf2.start_ea)
        ea = ida_bytes.next_head(ea, f.end_ea)
# 过滤掉主函数本身, 取前 12 个被调
new_c = [c for c in sorted(callees) if c not in pvf_funcs][:12]
log("  一级被调: %s" % ", ".join("%08X" % c for c in new_c))
for fea in new_c:
    dump_func(fea, "PVF-callee")

# ============ 4. 包名表 off_790928 ============
log("")
log("### 4. 包名表 off_790928 dump")
base = 0x790928
for i in range(120):
    p = ida_bytes.get_dword(base + i * 4)
    if not (0x400000 <= p < 0x9D6000):
        log("  [%d] invalid ptr %08X -> stop" % (i, p))
        if i > 8: break
        continue
    s = ida_bytes.get_strlit_contents(p, -1, 0)
    log("  [%d] %s" % (i, s.decode("ascii", "replace") if s else "?"))

# ============ 5. 发包类型穷举: 全库 sub_423200 调用点, 向前找 push imm ============
log("")
log("### 5. 发包类型穷举 (sub_423200 的调用者 + 前置 push)")
pkt_types = {}
for x in idautils.XrefsTo(0x423200):
    f = ida_funcs.get_func(x.frm)
    if not f: continue
    # 向前扫 48 字节找 push imm8/imm32（包类型是 Begin 的第二参数 a2... 实际签名 Begin(this, type)
    # thiscall: mov ecx, obj; push/a2 通过寄存器或栈。兼容两种: 找 push imm 与 mov edx/immed
    found = []
    ea = max(f.start_ea, x.frm - 64)
    while ea < x.frm:
        b = ida_bytes.get_byte(ea)
        if b == 0x6A:  # push imm8
            found.append(("push", ida_bytes.get_byte(ea + 1)))
        elif b == 0x68:  # push imm32
            found.append(("push", struct.unpack("<I", ida_bytes.get_bytes(ea+1, 4))[0]))
        ea += 1
    # 取最后一个 push（最靠近 call 的参数压栈顺序: 先高地址参数后低）
    ptype = found[-1][1] if found else None
    key = "0x%02X" % ptype if (ptype is not None and ptype < 0x100) else ("?" if ptype is None else "0x%X" % ptype)
    pkt_types.setdefault(key, []).append("%08X(in %08X)" % (x.frm, f.start_ea))
for k in sorted(pkt_types, key=lambda s: int(s, 16) if s.startswith("0x") else 9999):
    log("  type %s : %d 处  例: %s" % (k, len(pkt_types[k]), pkt_types[k][0]))

open(OUT, "w", encoding="utf-8").write("\n".join(lines))
print("done ->", OUT, len(lines), "lines")
import idc
idc.qexit(0)
