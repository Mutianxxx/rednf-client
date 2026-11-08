# -*- coding: utf-8 -*-
"""Extract tag -> write-target mapping from full dump blocks (read-only analysis)."""
import io, re, os, json

DUMP = r"E:\DOF LX\【40JP逆向源代码工程】\work"
FILES = ["dump_full_0.txt", "dump_full_1.txt", "dump_full_2.txt", "dump_parsers.txt"]
HDR = re.compile(r'^// ([0-9A-F]{8})\s+(\S+)')
TAG = re.compile(r'sub_423300\([^,]+,\s*"(\[[A-Za-z][^\]]*\])"\)')

TARGETS = {
    "item": ["004F1A20", "004F5B90", "004F6790", "004F7C60", "004F8E20", "004F8FE0",
             "004F9240", "004FA630", "004FA820", "004FAA40", "004FAC40", "004FB180", "004FBA70"],
    "monster": ["004FC1E0", "004FD040", "004FD4C0", "004FE770", "004FF870", "00500330",
                "00500B30", "00502F00", "00503BA0", "00504500", "00507690", "005078C0",
                "00509C90", "0050AF40", "0050B400", "0050B840"],
    "attackinfo": ["0050C290"],
}

cache = {}
for f in FILES:
    cache[f] = io.open(os.path.join(DUMP, f), encoding='utf-8', errors='replace').read().splitlines()

# build per-file function spans
spans = {}   # (file, va) -> (start, end)
for f, lines in cache.items():
    order = []
    for i, l in enumerate(lines):
        m = HDR.match(l)
        if m:
            order.append((m.group(1), i))
    for idx, (va, s) in enumerate(order):
        e = order[idx + 1][1] if idx + 1 < len(order) else len(lines)
        spans[(f, va)] = (s, e)

out = {}
for grp, vas in TARGETS.items():
    print("=" * 72)
    print("GROUP", grp)
    for va in vas:
        cands = [(fn, sp) for (fn, v), sp in spans.items() if v == va]
        if not cands:
            print(va, "MISSING"); continue
        # pick the longest block
        fn, (s, e) = max(cands, key=lambda t: t[1][1] - t[1][0])
        lines = cache[fn]
        seg = lines[s:e]
        print("-" * 72)
        print("%s (%s L%d, %d lines)" % (va, fn, s + 1, len(seg)))
        for i, l in enumerate(seg):
            m = TAG.search(l)
            if m:
                tag = m.group(1)
                nxt = []
                for j in range(i + 1, min(i + 6, len(seg))):
                    nl = seg[j].strip()
                    if nl in ("{", "}"):
                        continue
                    nxt.append(nl)
                    if len(nxt) >= 2:
                        break
                print("  %-34s %s" % (tag, " | ".join(nxt)[:150]))
        out.setdefault(grp, {})[va] = {"file": fn, "line": s + 1, "nlines": len(seg)}

json.dump(out, io.open(os.path.join(DUMP, "l1_tags", "map_index.json"), "w", encoding="utf-8"), ensure_ascii=False, indent=1)
