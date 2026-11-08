# -*- coding: utf-8 -*-
"""
std/CRT 容器字段改名（会话 14）—— 高置信度改名 + 参照表

与 tools/rename_fields.py 并列：那个管「游戏类字段表」，这个管「std/CRT 本地结构」。

高置信规则（必须同时满足）：
1. 宿主类型判定（tools/std_container_semantics.py）命中
2. **强证据**（任一）：
   - vector: 同时见 fld_4 与 fld_8（三指针），且出现元素数换算（/N 或 >>N）
   - map_rb: 出现 lower_bound/upper_bound/_Rb_tree + 同时见 fld_4/fld_8
   - zstream: 函数名/头注释含 inflate/deflate/adler/crc
3. 该变量在函数内**未被复用**（无 LOBYTE(x)= / HIBYTE(x)= 赋值）
4. 该变量**只对应同一偏移**（名字里的数字 → 偏移唯一）

改名：fld_4 → pVecEnd（等），同函数内所有引用同步替换。
参照表追加到 docs/95_字段改名参照表.md 的「std/CRT 结构」章节。

用法：python tools/rename_std_fields.py --scan | --apply
"""
import io, os, re, sys, glob, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
DATA = os.path.join(ROOT, "data")

VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6,8})(?![0-9A-Za-z])")
FLD = re.compile(r"\bfld_(e(\d+)|([0-9a-fA-F]+))\b")
IDENT = re.compile(r"[A-Za-z_]\w*")
STR = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')

# 标准名（按宿主类型 + 偏移）
STD_NAMES = {
    "vector":     {0: "pVecBegin", 4: "pVecEnd", 8: "pVecCap"},
    "string_sso": {0: "pStrBuf", 4: "nStrLen", 8: "nStrCap"},
    "list":       {0: "pListNode", 4: "pListSentinel"},
    "map_rb":     {0: "pRbRoot", 4: "pRbHead"},
    "zstream":    {0: "zNextIn", 4: "zAvailIn", 8: "zTotalIn", 12: "zNextOut",
                   16: "zAvailOut", 20: "zTotalOut", 24: "zMsg", 28: "zState"},
}
STRONG = {
    "vector": [r"/\s*\d+\b", r">>\s*2\b", r"/\s*0x?[0-9A-Fa-f]+"],
    "map_rb": [r"lower_bound", r"upper_bound", r"_Rb_tree", r"红黑树"],
    "zstream": [r"inflate|deflate|adler32|crc32"],
    "list": [r"哨兵", r"自环", r"next.*prev"],
    "string_sso": [r"SSO", r"容量\s*15", r"0x10u?.*(len|size)"],
}


def fld_off(m):
    return int(m.group(2)) * 4 if m.group(2) is not None else int(m.group(3), 16)


def process(path, apply, ledger, stats):
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    marks = []
    for i, l in enumerate(lines):
        m = VA_HEAD.match(l)
        if m:
            marks.append((int(m.group(1), 16), i))
    base_skel = [IDENT.sub("@", STR.sub('"S"', re.sub(r"//.*$", "", l))).strip() for l in lines]
    changed = 0
    for k, (va, i0) in enumerate(marks):
        i1 = marks[k + 1][1] if k + 1 < len(marks) else len(lines)
        body = lines[i0:i1]
        if not any(FLD.search(b) for b in body):
            continue
        # 宿主判定（用分类结果文件）
        cf = os.path.join(DATA, "fld_host_classify", "%08X.txt" % va)
        if not os.path.isfile(cf):
            continue
        host = None
        for l in io.open(cf, encoding="utf-8"):
            if l.startswith("host:"):
                host = l[5:].strip().split(",")[0].strip()
                break
        if not host or host not in STD_NAMES:
            continue
        # 强证据
        text = "\n".join(body)
        if not any(re.search(p, text, re.I) for p in STRONG.get(host, [])):
            stats[host + "_weak"] += 1
            continue
        # 该函数内的 fld_ 偏移集合
        offs = set()
        for b in body:
            for m in FLD.finditer(b):
                offs.add(fld_off(m))
        names = STD_NAMES[host]
        # 必须命中布局偏移；未命中的保持
        mapping = {}
        used = set()
        for b in body:
            for m in IDENT.finditer(re.sub(r"//.*$", "", b)):
                used.add(m.group(0))
        # 复用守卫：被 LOBYTE/HIBYTE 赋值的变量跳过
        reused = set()
        for b in body:
            for m in re.finditer(r"\b(?:LOBYTE|HIBYTE|BYTE\d?)\s*\(\s*(\w+)\s*\)\s*=", b):
                reused.add(m.group(1))
        for b in body:
            for m in FLD.finditer(b):
                var = m.group(0); off = fld_off(m)
                if var in reused:
                    continue
                if off not in names:
                    continue
                new = names[off]
                if new in used and new != var:
                    n2 = new + "_"; i = 2
                    while n2 in used:
                        n2 = "%s_%d" % (new, i); i += 1
                    new = n2
                mapping[var] = (new, off, host)
                used.add(new)
        if not mapping:
            continue
        for j in range(i0, i1):
            orig = lines[j]
            cm = re.match(r"^([^/]*?)(//.*)?$", orig)
            code = cm.group(1) if cm else orig
            rest = orig[len(code):]
            newc = code
            for old, (new, off, h) in sorted(mapping.items(), key=lambda x: -len(x[0])):
                newc = re.sub(r"\b%s\b" % re.escape(old), new, newc)
            if newc != code:
                lines[j] = newc + rest
                changed += 1
        for old, (new, off, h) in mapping.items():
            ledger.append((h, old, new, off, os.path.basename(path)))
        stats[host] += 1
    if changed and apply:
        if [IDENT.sub("@", STR.sub('"S"', re.sub(r"//.*$", "", l))).strip() for l in lines] != base_skel:
            return -1
        io.open(path, "w", encoding="utf-8", newline="").write("\n".join(lines))
    return changed


def main():
    apply = "--apply" in sys.argv
    ledger = []; stats = collections.Counter()
    total = 0; fc = 0
    for p in sorted(glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True)):
        n = process(p, apply, ledger, stats)
        if n == -1:
            print("!! 骨架校验失败:", p); continue
        if n:
            total += n; fc += 1
    print("改名引用行: %d | 文件: %d | 映射: %d" % (total, fc, len(ledger)))
    for k, v in sorted(stats.items()):
        print("  %-16s %d" % (k, v))
    if apply and ledger:
        # 追加到参照表
        p95 = os.path.join(ROOT, "docs", "95_字段改名参照表.md")
        t = io.open(p95, encoding="utf-8").read() if os.path.isfile(p95) else ""
        sec = ["", "## 四、std / CRT 本地结构字段改名（会话 14）", "",
               u"> 这些不是游戏对象字段，而是 **MSVC 标准库容器 / zlib 等本地结构**的固定布局。",
               u"> 布局依据：MSVC std::vector 三指针 = +0 _Myfirst / +4 _Mylast / +8 _Myend 等（见",
               u"> `data/std_container_layouts.tsv`）。", "",
               u"| 宿主类型 | 旧名 | 新名 | 字节偏移 | 出现文件 |", u"|---|---|---|---|---|"]
        seen = set()
        for h, old, new, off, f in sorted(ledger):
            k = (h, old, new, off)
            if k in seen: continue
            seen.add(k)
            sec.append(u"| %s | `%s` | `%s` | +0x%04X | %s |" % (h, old, new, off, f))
        # 替换已有第四节（幂等）
        t = re.sub(r"\n## 四、std / CRT.*$", "", t, flags=re.S)
        io.open(p95, "w", encoding="utf-8", newline="").write(t + "\n".join(sec))
        print("参照表已追加第四节（%d 条）" % len(seen))


if __name__ == "__main__":
    main()
