# -*- coding: utf-8 -*-
# 缺口函数转写: dump_missing_*.txt -> src/ 对应区块文件(补录进 L2 层)
import io, os, sys, re
sys.path.insert(0, os.path.dirname(__file__))
from importlib import util
spec = util.spec_from_file_location("tr", os.path.join(os.path.dirname(__file__), "transcribe.py"))
tr = util.module_from_spec(spec); spec.loader.exec_module(tr)

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

# 区块 -> (输出目录, 补录文件名)
BLOCK_MAP = [
    ((0x400000, 0x420000), ("src/nengine", "missing_engine.cpp")),
    ((0x420000, 0x480000), ("src/game", "missing_combat_a.cpp")),
    ((0x480000, 0x4F0000), ("src/game", "missing_misc_a.cpp")),
    ((0x4F0000, 0x510000), ("src/game/parsers", "missing_parsers.cpp")),
    ((0x510000, 0x540000), ("src/game", "missing_misc_b.cpp")),
    ((0x540000, 0x590000), ("src/game/ui", "missing_ui_login.cpp")),
    ((0x590000, 0x5E0000), ("src/game/creature", "missing_monster.cpp")),
    ((0x5E0000, 0x650000), ("src/combat", "missing_skills.cpp")),
    ((0x650000, 0x6C1000), ("src/platform", "missing_tail.cpp")),
]

def dst_of(va):
    for (lo, hi), (d, name) in BLOCK_MAP:
        if lo <= va < hi:
            return d, name
    return "src/game", "missing_unknown.cpp"

all_funcs = []
for i in range(3):
    p = os.path.join(ROOT, "work", "dump_missing_%d.txt" % i)
    if os.path.exists(p):
        all_funcs.extend(tr.parse_dump(p))

print("parsed total:", len(all_funcs))

buckets = {}
for f in all_funcs:
    d, name = dst_of(f["va"])
    key = (d, name)
    buckets.setdefault(key, []).append(f)

grand = 0
for (d, name), funcs in sorted(buckets.items()):
    outdir = os.path.join(ROOT, d)
    # 来源描述
    fdesc = "缺口补漏（会话 5 精确审计后补齐）"
    n, op = tr.write_module(outdir, name, fdesc, funcs, "missing-audit")
    grand += n
    print("OK %-60s %4d funcs" % (op.replace(ROOT + "\\", ""), n))
print("GRAND:", grand)
