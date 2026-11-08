# -*- coding: utf-8 -*-
"""客观粗注生成器 v12：剩余客观形态（IObject 虚表复位/成员清零/指针重定向）。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^\*\(uint32_t \*\)this = &nengine::IObject::`vftable\';$'), lambda m: "vftable 复位 IObject"),
    (re.compile(r'^\*this = &nengine::IObject::`vftable\';$'), lambda m: "vftable 复位 IObject"),
    (re.compile(r'^\*\(uint32_t \*\)this = &(off_[0-9A-F]+);$'), lambda m: "vftable = %s" % m.group(1)),
    (re.compile(r'^\*this = &(off_[0-9A-F]+);$'), lambda m: "vftable = %s" % m.group(1)),
    (re.compile(r'^\(\(uint32_t \*\)this\)\[?(\d+)\]? = &(nengine::IObject::`vftable\'|off_[0-9A-F]+);$'), lambda m: "this 偏移 %d = vftable %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = &nengine::IObject::`vftable\';$'), lambda m: "this 偏移 %d = IObject vftable" % (int(m.group(1))*4)),
    (re.compile(r'^\*\(this \+ (\d+)\) = &nengine::IObject::`vftable\';$'), lambda m: "this 偏移 %s = IObject vftable" % m.group(1)),
    (re.compile(r'^\*\(uint32_t \*\)\(this \+ (\d+)\) = &nengine::IObject::`vftable\';$'), lambda m: "this 偏移 %s = IObject vftable" % m.group(1)),
    (re.compile(r'^\*\(uint8_t \*\)\(this \+ (\d+)\) = 0;$'), lambda m: "this 偏移 %s 清 0" % m.group(1)),
    (re.compile(r'^\*\(this \+ (\d+)\) = (off_[0-9A-F]+);$'), lambda m: "this 偏移 %s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = (\w+) \+ (\d+);$'), lambda m: "%s = %s + %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\(uint32_t \*\)\((\w+) \+ (\d+)\) = (\w+);$'), lambda m: "%s+%s = %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = \((\w+) \*\)(\w+);$'), lambda m: "this 偏移 %d = (%s*)" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = \((\w+) \*\)\((\w+) \+ (\d+)\);$'), lambda m: "this 偏移 %d = 指针" % (int(m.group(1))*4)),
    (re.compile(r'^while \( (\w+) \)$'), lambda m: "当 %s 非 0 循环" % m.group(1)),
    (re.compile(r'^for \(', ), None),
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
            if fn is None:
                continue
            m = rx.match(s)
            if m:
                try:
                    ann = fn(m)
                except Exception:
                    ann = None
                if ann and '"' not in ann and "'" not in ann and '/*' not in ann and '*/' not in ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto12_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
