# -*- coding: utf-8 -*-
# P4b-2: 镜头族求证 —— 4238E0/4049C0 反编译; 8F7B08/79D0C4 引用者; 424BB0 调用点反汇编
import idaapi, idautils, idc, ida_funcs, ida_hexrays, ida_bytes

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\work\decomp_cam_verify.txt"
lines = []
def log(s): lines.append(s)

def dump_at(ea, tag, maxlines=200):
    log("// ===== %s @ %08X =====" % (tag, ea))
    try:
        cf = ida_hexrays.decompile(ea)
        log(str(cf) if cf else "// (failed)")
    except Exception as e:
        log("// (exception %s)" % e)
    log("")

dump_at(0x4238E0, "zoom remaining getter?")
dump_at(0x4049C0, "float lerp (全库通用)")

log("### A. 函数级引用: dword_8F7B08 (相机全局指针)")
for x in idautils.XrefsTo(0x8F7B08):
    f = ida_funcs.get_func(x.frm)
    log("  %08X in %s" % (x.frm, ("%08X" % f.start_ea) if f else "data"))
log("")

log("### B. 函数级引用: dword_79D0C4/C8 (震动域速率)")
for tgt in (0x79D0C4, 0x79D0C8):
    log(" -- %08X --" % tgt)
    for x in idautils.XrefsTo(tgt):
        f = ida_funcs.get_func(x.frm)
        log("  %08X in %s" % (x.frm, ("%08X" % f.start_ea) if f else "data"))
log("")

log("### C. 424BB0 尾部调用点反汇编 (BB0 接收者消歧)")
ea = 0x424BB0
end = 0x424C50
cur = ea
while cur < end:
    if ida_bytes.get_byte(cur) == 0xE8:  # call rel32
        import struct
        rel = struct.unpack_from("<i", ida_bytes.get_bytes(cur + 1, 4), 0)[0]
        tgt = cur + 5 + rel
        if tgt == 0x424530:
            # 反汇编前 32 字节
            start = max(ea, cur - 32)
            log("call site %08X -> 424530, 前 32 字节:" % cur)
            b = ida_bytes.get_bytes(start, cur - start)
            log("  " + " ".join("%02X" % x for x in b))
    cur += 1
log("")
log("### D. 424530 调用者清单")
for x in idautils.XrefsTo(0x424530):
    f = ida_funcs.get_func(x.frm)
    log("  %08X in %s" % (x.frm, ("%08X" % f.start_ea) if f else "data"))
log("")

# E. 衰减率 +1360/+1364 的读者(找每帧衰减应用者): 扫 0x424000-0x432000 中的
#    FLD [reg+1360h] / 模式过于复杂 —— 改为: 全库引用 8F7BD0/8F7BD4 (424530 关闭分支写 0 的全局)
log("### E. dword_77F6DC (全局变焦倍率) 引用者")
for x in idautils.XrefsTo(0x77F6DC):
    f = ida_funcs.get_func(x.frm)
    log("  %08X in %s" % (x.frm, ("%08X" % f.start_ea) if f else "data"))

with open(OUT, "w", encoding="utf-8") as fo:
    fo.write("\n".join(lines))
idc.qexit(0)
