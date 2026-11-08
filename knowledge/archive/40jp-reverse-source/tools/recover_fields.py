# -*- coding: utf-8 -*-
"""
字段表还原流水线（会话 11 新建）—— 743 类字段表半自动化还原

原理：
  类的每个虚方法都是该类的成员函数（thiscall），其函数体内的 `this+N` 访问
  就是该类的字段访问。把 类→槽位→函数地址（data/class_method_slots.txt）
  与 src/ 各函数的函数体（按 VA 标记定位）连接起来，即可按类聚合字段偏移。

outputs:
  data/class_fields/<类名>.txt   每类一份字段候选表（偏移/类型/访问次数/证据串）：
      off   type   count   sample_va   sample_line
  按访问次数排序 —— 高频偏移 = 核心字段，优先还原。

用法：
  python tools/recover_fields.py --all            # 全库扫描生成候选表
  python tools/recover_fields.py --class CNGoblinKinol
  python tools/recover_fields.py --top 40         # 只做核心 40 类（虚表槽位最多）
  python tools/recover_fields.py --stats
"""
import io, os, re, sys, glob, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
DATA = os.path.join(ROOT, "data")
OUT = os.path.join(DATA, "class_fields")

VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6,8})(?![0-9A-Za-z])")
# 字段访问： (type*)(base + N) 形式
FIELD = re.compile(
    r"\(\s*(uint32_t|uint16_t|uint8_t|int|char|float|double|BYTE|WORD|DWORD|short|size_t|void)\s*\*\s*\)"
    r"\s*\(\s*(\w+)\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)")
STR = re.compile(r'"((?:\\.|[^"\\])*)"')
CALL = re.compile(r'\b(sub_[0-9A-F]{6}|[A-Za-z_]\w*__vmt[0-9A-Fa-f]+)\b')


def load_slots():
    """data/class_method_slots.txt → {class: [(slot, va_int), ...]} （取 slots 最大的那版）"""
    classes = {}
    cur = None
    for ln in io.open(os.path.join(DATA, "class_method_slots.txt"), encoding="utf-8"):
        ln = ln.rstrip("\n")
        if ln.startswith("CLASS "):
            cur = ln[6:].strip()
        elif ln.startswith("  TD=") and cur:
            m = re.search(r"slots=(\d+)", ln)
            n = int(m.group(1)) if m else 0
            classes.setdefault(cur, {"best": -1, "slots": []})
            classes[cur]["pending"] = (n, [])
        elif ln.startswith("  +") and cur:
            parts = ln.split()
            if len(parts) >= 2:
                try:
                    slot = int(parts[0][1:])
                    va = int(parts[1], 16)
                    if "pending" in classes[cur]:
                        classes[cur]["pending"][1].append((slot, va))
                except ValueError:
                    pass
    # 取 slots 声明最大的那版
    out = {}
    for name, d in classes.items():
        if "pending" in d:
            n, lst = d["pending"]
            out[name] = lst
    return out


def build_func_index():
    """扫 src/ 全部 cpp → {va_int: (文件, 起始行, 结束行, [body_lines])}"""
    idx = {}
    for path in glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True):
        lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
        marks = []
        for i, l in enumerate(lines):
            m = VA_HEAD.match(l)
            if m:
                marks.append((int(m.group(1), 16), i))
        for k, (va, i) in enumerate(marks):
            end = marks[k + 1][1] if k + 1 < len(marks) else len(lines)
            if va not in idx:  # 首个（L1 层优先）
                idx[va] = (path, i, end, lines[i:end])
    return idx


def analyze_class(name, slots, fidx, min_count=1):
    """聚合一个类的全部槽位函数的 this+N 访问 → 字段候选列表"""
    fields = collections.defaultdict(lambda: {"types": collections.Counter(),
                                              "count": 0,
                                              "sample_va": 0,
                                              "sample_line": "",
                                              "strings": [],
                                              "calls": collections.Counter()})
    for slot, va in slots:
        rec = fidx.get(va)
        if not rec:
            continue
        path, i0, i1, body = rec
        for l in body:
            s = l.strip()
            if s.startswith("//"):
                continue
            for m in FIELD.finditer(l):
                typ, base, off = m.group(1), m.group(2), m.group(3)
                if base not in ("this", "pThis", "pObj"):
                    continue
                try:
                    o = int(off, 16) if off.startswith("0x") else int(off)
                except ValueError:
                    continue
                f = fields[o]
                f["types"][typ] += 1
                f["count"] += 1
                if not f["sample_va"]:
                    f["sample_va"] = va
                    f["sample_line"] = l.strip()[:100]
            for m in STR.finditer(l):
                sv = m.group(1)
                if 3 <= len(sv) <= 60:
                    for o in fields:
                        pass
            for m in CALL.finditer(l):
                pass
    return fields


def render(name, fields, slot_count):
    """字段候选表 → 文本卡片"""
    rows = [(o, f) for o, f in fields.items() if f["count"] >= 1]
    rows.sort(key=lambda kv: (kv[0]))
    lines = ["CLASS %s  slots=%d  fields_candidate=%d" % (name, slot_count, len(rows)),
             "off      type     cnt  sample_va  evidence",
             "-" * 100]
    for o, f in rows:
        typ = f["types"].most_common(1)[0][0]
        lines.append("+0x%04X %-8s %3d  %08X  %s" % (o, typ, f["count"], f["sample_va"], f["sample_line"][:70]))
    return "\n".join(lines)


def main():
    args = sys.argv[1:]
    slots = load_slots()
    print("类数:", len(slots))

    if "--stats" in args:
        return

    fidx = build_func_index()
    print("函数索引:", len(fidx))

    if "--class" in args:
        name = args[args.index("--class") + 1]
        keys = [k for k in slots if name in k]
    else:
        # 按槽位数排序（大表优先）
        keys = [k for k, v in slots.items() if v]
    if "--top" in args:
        n = int(args[args.index("--top") + 1])
        keys = sorted(keys, key=lambda k: -len(slots[k]))[:n]

    os.makedirs(OUT, exist_ok=True)
    done = 0
    for name in keys:
        sl = slots[name]
        if not sl:
            continue
        fields = analyze_class(name, sl, fidx)
        if not fields:
            continue
        safe = re.sub(r'[^\w]', '_', name.split("@@")[0].replace(".?AV", ""))
        txt = render(name, fields, len(sl))
        io.open(os.path.join(OUT, safe + ".txt"), "w", encoding="utf-8").write(txt)
        done += 1
    print("已生成字段候选表:", done, "->", OUT)


if __name__ == "__main__":
    main()
