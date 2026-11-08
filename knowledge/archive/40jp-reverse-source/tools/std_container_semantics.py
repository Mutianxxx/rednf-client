# -*- coding: utf-8 -*-
"""
std / CRT 本地结构语义表 + 识别器（会话 14）

原理：MSVC 容器的内存布局固定，可用「字段访问模式」识别宿主类型，再给
fld_4/fld_8/fld_C 等标准偏移套用标准名（不是猜，是布局直证）。

已确证的布局（本工程多处直证）：
  std::vector<T>     +0 _Myfirst  +4 _Mylast  +8 _Myend     （元素数 = (last-first)/size）
  std::string (SSO)  +0 _Bx._Ptr 或内联buf  +16 _Mysize  +20 _Myres(15=SSO)
  std::list<T>       +0 哨兵(自环 next/prev 指向自身+0)
  std::map/set       +0 根 + 红黑树头(哨兵 +0/+4 自环)
  zlib z_stream      +0 next_in +4 avail_in +8 total_in +12 next_out ...

输出：
  data/std_container_layouts.tsv     标准布局表（供改名工具套用）
  data/fld_host_classify/<VA>.txt    每函数的宿主类型判定 + 证据
"""
import io, os, re, glob, sys, collections, json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
DATA = os.path.join(ROOT, "data")
OUT = os.path.join(DATA, "fld_host_classify")

VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6,8})(?![0-9A-Za-z])")
FLD = re.compile(r"\bfld_(e(\d+)|([0-9a-fA-F]+))\b")

# ---- 标准布局表（偏移 → 标准字段名 + 说明）----
LAYOUTS = {
    "vector": {
        "sig": [r"\(.{0,40}\)\s*/\s*\d+",           # (end-begin)/N 元素数换算
                r">>\s*2",                           # (end-begin)>>2
                r"\+\s*0x?4\b.*\b0x?8\b"],           # 同时见 +4 与 +8
        "fields": {0: "pVecBegin", 4: "pVecEnd", 8: "pVecCap"},
        "note": "MSVC std::vector<T> 三指针：_Myfirst/_Mylast/_Myend",
    },
    "string_sso": {
        "sig": [r"\bcap\w*\s*[=<>]=?\s*(0x10u?|16)\b",   # 容量比较 16
                r"(0x10u?|15)\b.*\b(len|size)\b",
                r"-\s*1\b.*\b0x10u?\b"],
        "fields": {0: "pStrBuf", 4: "nStrLen", 8: "nStrCap"},
        "note": "MSVC std::string SSO：+0 缓冲/+4 长度/+8 容量（15=内联）",
    },
    "list": {
        "sig": [r"\bnext\b.*\bprev\b", r"自环", r"哨兵"],
        "fields": {0: "pListHead", 4: "pListTail"},
        "note": "MSVC std::list<T>：哨兵双指针自环",
    },
    "map_rb": {
        "sig": [r"\b红黑树\b", r"\b_Rb_tree\b", r"哨兵.*自环", r"lower_bound|upper_bound"],
        "fields": {0: "pRbRoot", 4: "pRbHead"},
        "note": "MSVC std::map/set：+0 根，+4 红黑树头（哨兵自环）",
    },
    "zstream": {
        "sig": [r"z_stream|inflate|deflate|adler32|crc32"],
        "fields": {0: "next_in", 4: "avail_in", 8: "total_in", 12: "next_out",
                   16: "avail_out", 20: "total_out", 24: "msg", 28: "state"},
        "note": "zlib z_stream 标准布局",
    },
}


def offsets_of(line):
    out = []
    for m in FLD.finditer(line):
        if m.group(2) is not None:
            out.append(int(m.group(2)) * 4)
        else:
            out.append(int(m.group(3), 16))
    return out


def classify(func_lines, ctx=""):
    """返回 [(容器类型, 证据)] 候选"""
    text = "\n".join(func_lines) + "\n" + ctx
    hits = []
    for name, spec in LAYOUTS.items():
        for pat in spec["sig"]:
            if re.search(pat, text, re.I):
                hits.append((name, pat))
                break
    return hits


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "--layout"
    if mode == "--layout":
        os.makedirs(DATA, exist_ok=True)
        with io.open(os.path.join(DATA, "std_container_layouts.tsv"), "w",
                     encoding="utf-8", newline="") as w:
            w.write("container\toffset\tfield\tnote\n")
            for name, spec in LAYOUTS.items():
                for off, fld in sorted(spec["fields"].items()):
                    w.write("%s\t0x%04X\t%s\t%s\n" % (name, off, fld, spec["note"]))
        print("标准布局表 -> data/std_container_layouts.tsv")
        for name, spec in LAYOUTS.items():
            print("  %-12s %s" % (name, spec["note"]))
        return

    # --scan: 对每个函数判定宿主类型
    os.makedirs(OUT, exist_ok=True)
    stats = collections.Counter()
    total = 0
    for p in glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True):
        lines = io.open(p, encoding="utf-8", errors="replace").read().split("\n")
        marks = []
        for i, l in enumerate(lines):
            m = VA_HEAD.match(l)
            if m:
                marks.append((int(m.group(1), 16), i))
        for k, (va, i0) in enumerate(marks):
            i1 = marks[k + 1][1] if k + 1 < len(marks) else len(lines)
            body = lines[i0:i1]
            if not any(FLD.search(b) for b in body):
                continue
            ctx = "\n".join(b for b in body[:6] if b.strip().startswith("//"))
            hits = classify(body, ctx)
            if not hits:
                continue
            total += 1
            for hn, pat in hits:
                stats[hn] += 1
            txt = ["VA %08X  %s" % (va, p.replace("\\", "/").split("src/")[-1]),
                   "host: " + ", ".join(h[0] for h in hits)]
            for hn, pat in hits:
                txt.append("  %-12s 证据: %s" % (hn, pat))
                for off, fld in sorted(LAYOUTS[hn]["fields"].items()):
                    txt.append("     +0x%04X → %s" % (off, fld))
            io.open(os.path.join(OUT, "%08X.txt" % va), "w", encoding="utf-8").write("\n".join(txt))
    print("有 fld_ 且判定出宿主类型的函数: %d" % total)
    for k, v in stats.most_common():
        print("  %-12s %d" % (k, v))


if __name__ == "__main__":
    main()
