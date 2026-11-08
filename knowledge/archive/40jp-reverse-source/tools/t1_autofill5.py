# -*- coding: utf-8 -*-
"""客观粗注生成器 v5：GBK 前导字节比较链 + case/标签等客观形态。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^\|\| (v\d+|v\d+_\d+|fld_[0-9A-Fa-f]+) == -(\d+)\)?$'), lambda m: "GBK 双字节前导字节表项 -%s" % m.group(2)),
    (re.compile(r'^\|\| (v\d+) == -(\d+)$'), lambda m: "GBK 双字节前导字节表项 -%s" % m.group(2)),
    (re.compile(r'^case (\d+)u?:$'), lambda m: "case 分支 %s" % m.group(1)),
    (re.compile(r'^case (0x[0-9A-Fa-f]+)u?:$'), lambda m: "case 分支 %s" % m.group(1)),
    (re.compile(r'^(v\d+|fld_[0-9A-Fa-f]+|pThis\d*|result) = (\d+);$'), lambda m: "%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(v\d+|fld_[0-9A-Fa-f]+|pThis\d*|result) = nullptr;$'), lambda m: "%s = 空指针" % m.group(1)),
    (re.compile(r'^\+\+(v\d+|i|j|k|m|n);$'), lambda m: "%s 自增" % m.group(1)),
    (re.compile(r'^--(v\d+|i|j|k|n);$'), lambda m: "%s 自减" % m.group(1)),
    (re.compile(r'^(v\d+|pThis\d*)(\[[^\]]+\])? = (v\d+|pThis\d*)(\[[^\]]+\])?;$'), lambda m: m.group(0).rstrip(';')),
    (re.compile(r'^\*\(this \+ (\d+)\) = nArg(\d);$'), lambda m: "this+%s = 参数%s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = nArg(\d);$'), lambda m: "this 偏移 %d = 参数%s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^sub_([0-9A-F]{6})\(this \+ (\d+)\);$'), lambda m: "sub_%s(this+%s)" % (m.group(1), m.group(2))),
    (re.compile(r'^sub_([0-9A-F]{6})\(\);$'), lambda m: "调 sub_%s" % m.group(1)),
    (re.compile(r'^j__free\(\((void )?\*\*\)\(this \+ (\d+)\)\);$'), lambda m: "free this+%s" % m.group(2)),
    (re.compile(r'^sub_6569D0\(this \+ (\d+)\);$'), lambda m: "sub_6569D0 清哨兵链(this+%s)" % m.group(1)),
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
                if ann:
                    notes.append([i, ann]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto5_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
