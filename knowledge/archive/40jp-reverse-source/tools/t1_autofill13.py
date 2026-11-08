# -*- coding: utf-8 -*-
"""客观粗注生成器 v13：vtable 分派调用 + 常见残片。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    # vtable 调用形态: (*(...))(obj, ...);  ——客观描述为 调用虚函数
    (re.compile(r'^\(\*\*?\(.*?\)\)\(.*\);$'), lambda m: "调用虚函数/间接调用"),
    (re.compile(r'^result = \(\*\*?\(.*?\)\)\(.*\);$'), lambda m: "调用虚函数/间接调用"),
    (re.compile(r'^return \(\*\*?\(.*?\)\)\(.*\);$'), lambda m: "调用虚函数并返回"),
    # 简单 var = var op var
    (re.compile(r'^(\w+) = (\w+) \+ (\w+);$'), lambda m: "%s = %s + %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^(\w+) = (\w+) - (\w+);$'), lambda m: "%s = %s - %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^(\w+) \+= (\w+);$'), lambda m: "%s += %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) -= (\w+);$'), lambda m: "%s -= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = (\w+)\[(.+)\];$'), lambda m: "%s = %s[...]" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+)\[(.+)\] = (\w+);$'), lambda m: "%s[...] = %s" % (m.group(1), m.group(3))),
    (re.compile(r'^\*\(this \+ (\d+)\) = -(\d+);$'), lambda m: "this+%s = -%s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = \*\((\w+) \+ (\d+)\);$'), lambda m: "%s = %s+%s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^(\w+) = \((\w+) \*\)(\w+)\[(\w+)\];$'), lambda m: "%s = (%s*)%s[%s]" % (m.group(1), m.group(2), m.group(3), m.group(4))),
    (re.compile(r'^v(\d+) = uArg(\d)\[(.+)\] \+ v\1;$'), lambda m: "v%s = uArg%s[...] + v%s" % (m.group(1), m.group(2), m.group(1))),
    (re.compile(r'^v(\d+) = uArg(\d)\[(.+)\];$'), lambda m: "v%s = uArg%s[...]" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( \(v(\d+)\[(\w+)\] & (\d+)\) != (\d+) \)$'), lambda m: "若 v%s[%s] 位测试" % (m.group(1), m.group(2))),
    (re.compile(r'^while \( v(\d+) != (\w+) \);$'), lambda m: "当 v%s != %s 循环" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = \((\w+)\)(\w+);$'), lambda m: "%s = 类型转换(%s)" % (m.group(1), m.group(3))),
]

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    path = ROOT + "\\src\\" + rel.replace("/", "\\")
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    for i, l in enumerate(lines, 1):
        if '//' in l:
            continue
        s = l.strip()
        if not s or s in ('{', '}'):
            continue
        for rx, fn in RULES:
            m = rx.match(s)
            if m:
                try:
                    ann = fn(m)
                except Exception:
                    ann = None
                if ann and '"' not in ann and "'" not in ann and '/*' not in ann and '*/' not in ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto13_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
