# -*- coding: utf-8 -*-
"""客观粗注生成器 v11：else/do/label/结构控制与剩余客观形态。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^else$'), lambda m: "否则分支"),
    (re.compile(r'^do$'), lambda m: "do 循环体"),
    (re.compile(r'^(LABEL_\d+):$'), lambda m: "%s（跳转目标）" % m.group(1)),
    (re.compile(r'^while \( (\w+) \)$'), lambda m: "当 %s 非 0 循环" % m.group(1)),
    (re.compile(r'^while \( (\w+) < (\w+) \);$'), lambda m: "当 %s < %s 循环" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = \((\w+ \*)\*\)\*(\w+);$'), lambda m: "%s = 解引用跟踪 %s" % (m.group(1), m.group(3))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = (.+);$'), lambda m: "this 偏移 %s（字节）= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(fld_[0-9A-Fa-f]+) = \*\(\(uint32_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %d" % (m.group(1), int(m.group(2)))),
    (re.compile(r'^(fld_[0-9A-Fa-f]+) = \*\(\(uint8_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(pThis\w*) = \((\w+ \*)\)\(this \+ (\d+)\);$'), lambda m: "%s = this+%s 指针" % (m.group(1), m.group(3))),
    (re.compile(r'^(\w+) = \((\w+) \*\)(\w+);$'), lambda m: "%s = (%s*)%s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^j__free\(\*\(this \+ (\d+)\)\);$'), lambda m: "free this+%s" % m.group(1)),
    (re.compile(r'^nullsub_\d+\(this\);$'), lambda m: "nullsub（空桩）"),
    (re.compile(r'^(\w+) = sub_([0-9A-F]{6})\((\w+), \*\(uint32_t \*\)\((\w+) \+ (\d+)\), (\w+)\);$'), lambda m: "%s = sub_%s(...)" % (m.group(1), m.group(2))),
    (re.compile(r'^\w+ = GetTickCount\(\);$'), lambda m: "= GetTickCount()"),
    (re.compile(r'^\w+ = timeGetTime\(\);$'), lambda m: "= timeGetTime()"),
    (re.compile(r'^(\w+) = (\w+)\[(\w+)\];$'), lambda m: "%s = %s[%s]" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^\*\w+ = (\w+);$'), lambda m: "写指针 = %s" % m.group(1)),
    (re.compile(r'^(\w+) = \((uint8_t|uint16_t|int16_t|char|int)\)(\w+);$'), lambda m: "%s = 截断(%s)" % (m.group(1), m.group(3))),
    (re.compile(r'^if \( (\w+) & (\d+) \)$'), lambda m: "若 %s 位 %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( \(\w+ & \d+\) != 0 \)$'), lambda m: "若位测试非 0"),
    (re.compile(r'^if \( (\w+) > (\d+) \)$'), lambda m: "若 %s > %s" % (m.group(1), m.group(2))),
    (re.compile(r'^if \( (\w+) > 0 \)$'), lambda m: "若 %s > 0" % m.group(1)),
    (re.compile(r'^if \( (\w+) >= (\w+) \)$'), lambda m: "若 %s >= %s" % (m.group(1), m.group(2))),
    (re.compile(r'^v(\d+) = pArg(\d)\[(\w+)\];$'), lambda m: "v%s = pArg%s[%s]" % (m.group(1), m.group(2), m.group(3))),
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
                if ann and '"' not in ann and "'" not in ann and '/*' not in ann and '*/' not in ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto11_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
