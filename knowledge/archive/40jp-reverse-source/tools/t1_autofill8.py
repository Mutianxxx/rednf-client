# -*- coding: utf-8 -*-
"""客观粗注生成器 v8：字段赋值/成员清零/指针重定向/常见 API 调用等客观形态。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^\*\(uint32_t \*\)\(this \+ (\d+)\) = (\d+);$'), lambda m: "this+%s（uint32 槽）= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(uint32_t \*\)\(this \+ (\d+)\) = &(.+);$'), lambda m: "this+%s = vftable/接口 %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(uint32_t \*\)\(this \+ (\d+)\) = nArg(\d);$'), lambda m: "this+%s = 参数%s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(this \+ (\d+)\) = nArg(\d);$'), lambda m: "this+%s = 参数%s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(this \+ (\d+)\) = nullptr;$'), lambda m: "this+%s = 空指针" % m.group(1)),
    (re.compile(r'^\*\(this \+ (\d+)\) = result;$'), lambda m: "this+%s = result" % m.group(1)),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = sub_([0-9A-F]{6})\(this \+ (\d+)\);$'), lambda m: "this 偏移 %d = sub_%s(this+%s)" % (int(m.group(1))*4, m.group(2), m.group(3))),
    (re.compile(r'^\*\(uint32_t \*\)\(this \+ (\d+)\) = sub_([0-9A-F]{6})\(this \+ (\d+)\);$'), lambda m: "this+%s = sub_%s(this+%s)" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = (.+);$'), lambda m: "this 偏移 %s（字节）= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint16_t \*\)this \+ (\d+)\) = (.+);$'), lambda m: "this 偏移 %d（uint16）= %s" % (int(m.group(1))*2, m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = (.+);$'), lambda m: "this 偏移 %d = %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^j__free\(\*\(void \*\*\)\(this \+ (\d+)\)\);$'), lambda m: "free this+%s" % m.group(1)),
    (re.compile(r'^j_j__free\(\*\(void \*\*\)\(this \+ (\d+)\)\);$'), lambda m: "free this+%s" % m.group(1)),
    (re.compile(r'^\*\(\(uint32_t \*\)v(\d+) \+ (\d+)\) = (.+);$'), lambda m: "v%s 偏移 %d = %s" % (m.group(1), int(m.group(2))*4, m.group(3))),
    (re.compile(r'^\*\(\(uint8_t \*\)v(\d+) \+ (\d+)\) = (.+);$'), lambda m: "v%s 偏移 %s（字节）= %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\(\(uint32_t \*\)v(\d+) \+ (\d+)\) = 0;$'), lambda m: "v%s 偏移 %d 清 0" % (m.group(1), int(m.group(2))*4)),
    (re.compile(r'^\*\*\*\(uint32_t \*\*\*\)\(v\d+ \+ (\d+)\) = (.+);$'), lambda m: "v 偏移 %s 双解引用赋值 %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(uint32_t \*\)\((\w+) \+ (\d+)\) = (.+);$'), lambda m: "%s+%s = %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\(uint32_t \*\)\((\w+) \+ (\d+)\) = 0;$'), lambda m: "%s+%s 清 0" % (m.group(1), m.group(2))),
    (re.compile(r'^\*owner_name = (.+);$'), lambda m: "写 owner_name = %s" % m.group(1)),
    (re.compile(r'^return (\w+);$'), lambda m: "返回 %s" % m.group(1)),
    (re.compile(r'^return (-\d+);$'), lambda m: "返回错误码 %s" % m.group(1)),
    (re.compile(r'^goto (LABEL_\d+);$'), lambda m: "跳转 %s" % m.group(1)),
    (re.compile(r'^(\w+) = (nullptr|0);$'), lambda m: "%s = 0/空" % m.group(1)),
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
        if not s:
            continue
        for rx, fn in RULES:
            m = rx.match(s)
            if m:
                try:
                    ann = fn(m)
                except Exception:
                    ann = None
                if ann and '"' not in ann and "'" not in ann and '/*' not in ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto8_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
