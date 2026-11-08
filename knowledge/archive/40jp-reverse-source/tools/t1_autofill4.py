# -*- coding: utf-8 -*-
"""客观粗注生成器 v4：通用赋值/自增/nullptr 等客观形态（无语义猜测）。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

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
        ann = None
        m = re.match(r'^(v\d+|fld_[0-9A-Fa-f]+|pThis\d*|result|nLen\d*|Time|v\d+_\d+) = (\d+);$', s)
        if m:
            ann = "%s = %s" % (m.group(1), m.group(2))
        elif re.match(r'^(v\d+|fld_[0-9A-Fa-f]+|pThis\d*|result) = nullptr;$', s):
            ann = "%s = 空指针" % s.split('=')[0].strip()
        elif re.match(r'^\+\+(v\d+|i|j|k|m|n|v\d+);$', s):
            ann = "%s 自增" % s[2:-1]
        elif re.match(r'^--(v\d+|i|j|k|n);$', s):
            ann = "%s 自减" % s[2:-1]
        elif re.match(r'^(v\d+|fld_[0-9A-Fa-f]+) = (v\d+|fld_[0-9A-Fa-f]+);$', s):
            ann = s.rstrip(';')
        elif re.match(r'^\*Block = (\d+);$', s):
            ann = "*Block = %s" % re.match(r'^\*Block = (\d+);$', s).group(1)
        elif re.match(r'^v\d+ = result;$', s):
            ann = s.rstrip(';')
        elif re.match(r'^v\d+ = this;$', s):
            ann = "v = this"
        elif re.match(r'^\(void\)\w+;$', s):
            ann = "丢弃返回值"
        elif s == 'default:':
            ann = "默认分支"
        elif s == 'break;':
            ann = "跳出 switch/循环"
        elif re.match(r'^\+\+v\d+;$', s):
            ann = "v 自增"
        else:
            m = re.match(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = (\d+);$', s)
            if m:
                ann = "this 偏移 %d = %s" % (int(m.group(1))*4, m.group(2))
        if ann:
            notes.append([i, ann])
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto4_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
