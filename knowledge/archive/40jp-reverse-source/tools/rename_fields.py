# -*- coding: utf-8 -*-
"""
字段名真改名（会话 13）：fld_XXX → 语义名 + 参照表留存

核心安全设计：
1. **按「函数所属类」精确匹配**（VA→类 映射 + 该类字段表），杜绝跨类同名偏移串味。
2. **只改一次**：`fld_16C` → `nPhaseTimer`（不是 fld_16C_nPhaseTimer 这种拼接，
   而是真改名），但**同一变量在同一函数内全部引用同步替换**。
3. **冲突消解**：一个新名在函数内已存在 → 追加 `_` 后缀；仍冲突 → 加数字。
4. **参照表留存**（用户明确要求）：`docs/95_字段改名参照表.md`
   —— 记录 旧名 → 新名 + 偏移 + 类 + 证据，供未来开发者回溯。
5. **骨架校验**：改名前后的「结构骨架」（标识符→@）必须一致；只在标识符级变化。

用法：
  python tools/rename_fields.py --scan                 # 统计可改名量
  python tools/rename_fields.py --apply                # 全库落盘 + 生成参照表
  python tools/rename_fields.py --file src/x.cpp --apply
"""
import io, os, re, sys, glob, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
DATA = os.path.join(ROOT, "data")
FIELDS = os.path.join(ROOT, "include", "arad", "_fields")

VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6,8})(?![0-9A-Za-z])")
DECL = re.compile(r"^(\s*)([A-Za-z_][\w \*]*?)\s+(fld_[0-9a-fA-F]+|fld_e\d+)\s*;(.*)$")
IDENT = re.compile(r"[A-Za-z_]\w*")
STR = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


def load_slots():
    """VA(int) → 类名"""
    va2class = {}
    cur = None
    for ln in io.open(os.path.join(DATA, "class_method_slots.txt"), encoding="utf-8"):
        ln = ln.rstrip("\n")
        if ln.startswith("CLASS "):
            cur = ln[6:].strip().split("@@")[0].replace(".?AV", "")
        elif ln.startswith("  +") and cur:
            parts = ln.split()
            if len(parts) >= 2:
                try:
                    va2class.setdefault(int(parts[1], 16), cur)
                except ValueError:
                    pass
    return va2class


def load_fields():
    """类名 → {字节偏移: 语义名}（只用非占位名）"""
    per = {}
    for p in glob.glob(os.path.join(FIELDS, "*.h")):
        name = os.path.basename(p)[:-2]
        tbl = {}
        for l in io.open(p, encoding="utf-8", errors="replace"):
            m = re.search(r"//\s*\+0x([0-9A-Fa-f]+)\s*\((\d+)\)\s*x\d+\s+", l)
            if not m:
                continue
            dm = re.match(r"^\s*[A-Za-z_][\w\s\*]*?\s+(\w+)\s*;", l)
            if not dm:
                continue
            nm = dm.group(1)
            if nm.startswith(("field_", "f_", "_")):
                continue
            tbl[int(m.group(1), 16)] = nm
        if tbl:
            per[name] = tbl
    return per


def parse_blocks(lines):
    marks = []
    for i, l in enumerate(lines):
        m = VA_HEAD.match(l)
        if m:
            marks.append((int(m.group(1), 16), i))
    out = []
    for k, (va, i) in enumerate(marks):
        end = marks[k + 1][1] if k + 1 < len(marks) else len(lines)
        out.append((va, i, end))
    return out


def rename_in_file(path, va2class, per, apply, ledger, conflicts):
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    # 骨架基线（代码行标识符→@）
    def skel(ls):
        out = []
        for l in ls:
            s = STR.sub('"S"', l)
            s = re.sub(r"//.*$", "", s)
            out.append(IDENT.sub("@", s).strip())
        return out
    base_skel = skel(lines)
    changed = 0
    for va, i0, i1 in parse_blocks(lines):
        cls = va2class.get(va)
        if not cls or cls not in per:
            continue
        tbl = per[cls]
        # 收集本函数内所有 fld_ 声明的映射
        mapping = {}
        used_names = set()
        for j in range(i0, min(i1, len(lines))):
            for m in IDENT.finditer(re.sub(r"//.*$", "", lines[j])):
                used_names.add(m.group(0))
        for j in range(i0, min(i1, len(lines))):
            m = DECL.match(lines[j])
            if not m:
                continue
            var = m.group(3)
            try:
                off = int(var[5:], 10) * 4 if var.startswith("fld_e") else int(var[4:], 16)
            except ValueError:
                continue
            sem = tbl.get(off)
            if not sem:
                continue
            new = sem
            if new in used_names and new != var:
                new2 = new + "_"
                k = 2
                while new2 in used_names:
                    new2 = "%s_%d" % (new, k); k += 1
                conflicts.append((cls, var, new, new2))
                new = new2
            used_names.add(new)
            mapping[var] = new
            ledger.append((var, new, off, cls, os.path.basename(path)))
        if not mapping:
            continue
        # 在本函数区间内替换所有引用（含声明行）
        for j in range(i0, min(i1, len(lines))):
            orig = lines[j]
            # 保护字符串与行尾注释（只替换代码部分）
            code_m = re.match(r"^([^/]*?)(//.*)?$", orig)
            code = code_m.group(1) if code_m else orig
            rest = orig[len(code):]
            newc = code
            for old, new in sorted(mapping.items(), key=lambda x: -len(x[0])):
                newc = re.sub(r"\b%s\b" % re.escape(old), new, newc)
            if newc != code:
                lines[j] = newc + rest
                changed += 1
    if changed and apply:
        # 骨架校验
        if skel(lines) != base_skel:
            return -1
        io.open(path, "w", encoding="utf-8", newline="").write("\n".join(lines))
    return changed


def main():
    args = sys.argv[1:]
    apply = "--apply" in args
    va2class = load_slots()
    per = load_fields()
    print("VA→类: %d | 有语义名的类: %d | 名字总数: %d"
          % (len(va2class), len(per), sum(len(v) for v in per.values())))
    files = ([args[args.index("--file") + 1]] if "--file" in args
             else sorted(glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True)))
    ledger = []; conflicts = []
    total = 0; files_changed = 0
    for p in files:
        n = rename_in_file(p, va2class, per, apply, ledger, conflicts)
        if n == -1:
            print("!! 骨架校验失败（跳过）: %s" % p)
            continue
        if n:
            total += n; files_changed += 1
    print("改名引用行: %d | 涉及文件: %d | 映射条目: %d | 冲突消解: %d"
          % (total, files_changed, len(ledger), len(conflicts)))
    if apply and ledger:
        # 生成参照表
        by_cls = collections.defaultdict(list)
        for old, new, off, cls, f in ledger:
            by_cls[cls].append((old, new, off, f))
        out = [u"# 95 · 字段改名参照表（会话 13 生成）", "",
               u"> **用途**：本工程把源码里的 `fld_XXX`（字段偏移占位名）**真改名**为字段表还原出的",
               u"> 语义名。本表记录全部改名的 **旧名 → 新名** 对照，供未来开发者回溯原二进制偏移。",
               u"> ", u"> - 旧名规则：`fld_HH` = 字节偏移 0xHH；`fld_eN` = int 下标（字节 N×4）",
               u"> - 新名来源：`include/arad/_fields/<类>.h`（会话 11 还原，每字段带证据 VA）",
               u"> - 改名仅在同一函数（同类）内进行，避免跨类同名偏移串味",
               u"> - 生成：`python tools/rename_fields.py --apply`（幂等）", "",
               u"| 类 | 旧名 | 新名 | 字节偏移 | 出现文件 |", u"|---|---|---|---|---|"]
        for cls in sorted(by_cls):
            for old, new, off, f in sorted(by_cls[cls], key=lambda x: x[2]):
                out.append(u"| %s | `%s` | `%s` | +0x%04X | %s |" % (cls, old, new, off, f))
        io.open(os.path.join(ROOT, "docs", "95_字段改名参照表.md"), "w",
                encoding="utf-8", newline="").write("\n".join(out))
        print("参照表已生成: docs/95_字段改名参照表.md（%d 条映射）" % len(ledger))


if __name__ == "__main__":
    main()
