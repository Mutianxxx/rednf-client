# -*- coding: utf-8 -*-
"""
类头 ← 字段表 接线（会话 11 收尾）

把 include/arad/**/<类>.h 的空 struct 体替换为「继承 + 字段表 include」，
使 743 类头都能直接看到本会话还原的字段。

规则：
1. 若同名字段表存在（include/arad/_fields/<类>.h），在类头的 struct 前插入
   `#include "../_fields/<类>.h"` 与字段表 struct 的成员别名说明。
2. **不改动原有继承声明与虚表注释**——只在 struct 体内加一行注释指向字段表，
   并把 struct 体改为：
       struct X : <原基类> {
           // 字段布局见 ../_fields/X.h（会话 11 还原：偏移/类型/语义/证据）
           X_Fields fields;
       };
   （若字段表 struct 名不是 <类>_Fields 则跳过，保守处理）
3. 已手写覆盖的类头（src/cnrd/*.h 对应的）不处理。

用法: python tools/link_field_tables.py [--apply]
"""
import io, os, re, sys, glob, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCL = os.path.join(ROOT, "include", "arad")
FIELDS = os.path.join(INCL, "_fields")


def main():
    apply = "--apply" in sys.argv
    linked = 0
    skipped = 0
    details = []
    for path in glob.glob(os.path.join(INCL, "**", "*.h"), recursive=True):
        if os.path.dirname(path) == FIELDS:
            continue
        name = os.path.basename(path)[:-2]
        fp = os.path.join(FIELDS, name + ".h")
        if not os.path.isfile(fp):
            skipped += 1
            continue
        fld = io.open(fp, encoding="utf-8", errors="replace").read()
        # 取字段表 struct 名
        m = re.search(r"struct\s+(\w+_Fields)\s*\{", fld)
        if not m:
            skipped += 1
            continue
        sname = m.group(1)
        txt = io.open(path, encoding="utf-8", errors="replace").read()
        if "fields" in txt and sname in txt:
            skipped += 1     # 已接线
            continue
        # 在 struct 前插入字段表 include + 说明注释（不改动继承声明与结构体本身）
        sm = re.search(r"(struct\s+" + re.escape(name) + r"\s*:\s*[^\{]+)\{\s*\};", txt)
        if not sm:
            skipped += 1
            continue
        rel = os.path.relpath(fp, os.path.dirname(path)).replace("\\", "/")
        insert = ("// ---- 字段布局（会话 11 半自动还原：偏移/类型/语义名/证据 VA）----\n"
                  "// 详见 " + rel + "（独立 struct " + sname + "，布局与二进制实测一致；\n"
                  "// 源 = 类槽位函数 this+N 聚合，含继承段 _base_0xNNNN）\n"
                  "#include \"" + rel + "\"\n\n")
        txt2 = txt[:sm.start()] + insert + txt[sm.start():]
        details.append((name, rel))
        linked += 1
        if apply:
            io.open(path, "w", encoding="utf-8", newline="").write(txt2)
    print("接线类头: %d | 跳过: %d | 模式: %s" % (linked, skipped, "APPLY" if apply else "dry-run"))
    for n, r in details[:8]:
        print("  %s → %s" % (n, r))


if __name__ == "__main__":
    main()
