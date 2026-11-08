# -*- coding: utf-8 -*-
# P1 全函数普查：数量/大小分布/地址分区/命名率/段表/导出表
# 运行: idat.exe -A -S this.py -L log ARAD_recon.i64
import idaapi, idautils, idc, ida_funcs, ida_segment, ida_name

OUT = r"E:\DOF LX\【40JP逆向源代码工程】\data\census_functions.txt"

lines = []
def log(s):
    lines.append(s)

# --- 段表 ---
log("### SEGMENTS")
seg = ida_segment.get_first_seg()
while seg:
    log("%-8s %08X-%08X size=%8d perm=%d" % (
        ida_segment.get_segm_name(seg), seg.start_ea, seg.end_ea, seg.size(), seg.perm))
    seg = ida_segment.get_next_seg(seg.start_ea)

# --- 函数普查 ---
funcs = list(idautils.Functions())
log("")
log("### FUNCTION CENSUS")
log("total functions: %d" % len(funcs))

named = 0
sub_count = 0
sizes = []
blocks = {}  # 0x10000 block -> count
for fea in funcs:
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    sz = f.size()
    sizes.append((sz, fea))
    n = ida_name.get_ea_name(fea)
    if n and not n.startswith("sub_") and not n.startswith("nullsub") and not n.startswith("j_") and not n.startswith("??"):
        named += 1
    else:
        sub_count += 1
    blk = fea >> 16
    blocks[blk] = blocks.get(blk, 0) + 1

log("named (meaningful): %d" % named)
log("unnamed sub_*: %d" % sub_count)

sizes.sort(reverse=True)
log("")
log("### TOP 100 LARGEST FUNCTIONS")
for sz, fea in sizes[:100]:
    n = ida_name.get_ea_name(fea) or ""
    log("%08X  size=%7d  %s" % (fea, sz, n))

log("")
log("### SIZE DISTRIBUTION")
buckets = [(0,64),(64,128),(128,256),(256,512),(512,1024),(1024,2048),(2048,4096),(4096,8192),(8192,1<<30)]
for lo, hi in buckets:
    c = sum(1 for s,_ in sizes if lo <= s < hi)
    log("%6d-%6d: %d" % (lo, hi, c))

log("")
log("### FUNCTION COUNT PER 64K BLOCK (address partition)")
for blk in sorted(blocks):
    log("%04X000: %d" % (blk, blocks[blk]))

# --- 导出表 ---
log("")
log("### ENTRY POINT / EXPORTS")
import ida_entry
n = ida_entry.get_entry_qty()
log("entry qty: %d" % n)
for i in range(n):
    ord_ = ida_entry.get_entry_ordinal(i)
    ea = ida_entry.get_entry(ord_)
    log("  ord=%d %08X %s" % (ord_, ea, ida_entry.get_entry_name(ord_)))

with open(OUT, "w", encoding="utf-8") as f:
    f.write("\n".join(lines))

idc.qexit(0)
