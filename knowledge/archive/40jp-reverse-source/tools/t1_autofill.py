# -*- coding: utf-8 -*-
"""为机械式字段赋值/清零行生成客观行尾注释（粗注）。
仅覆盖可 100% 客观陈述的形态；输出 spec.json 供 t1_annotate.py 使用。
"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    maxn = int(sys.argv[2]) if len(sys.argv) > 2 else 10**9
    path = ROOT + "\\src\\" + rel.replace("/", "\\")
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    pat_this0 = re.compile(r'^\*\(this \+ (\d+)\) = 0;$')
    pat_this32_0 = re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = 0;$')
    pat_thisv = re.compile(r'^\*\(this \+ (\d+)\) = (\d+);$')
    pat_this32v = re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = (\d+);$')
    pat_uint8 = re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = (\d+);$')
    for i, l in enumerate(lines, 1):
        if '//' in l:
            continue
        s = l.strip()
        if not s:
            continue
        m = pat_this0.match(s)
        if m:
            notes.append([i, "this+%s 清 0" % m.group(1)]); continue
        m = pat_this32_0.match(s)
        if m:
            off = int(m.group(1)) * 4
            notes.append([i, "this 偏移 %d 清 0" % off]); continue
        m = pat_thisv.match(s)
        if m:
            notes.append([i, "this+%s = %s" % (m.group(1), m.group(2))]); continue
        m = pat_this32v.match(s)
        if m:
            off = int(m.group(1)) * 4
            notes.append([i, "this 偏移 %d = %s" % (off, m.group(2))]); continue
        m = pat_uint8.match(s)
        if m:
            notes.append([i, "this 偏移 %s 字节 = %s" % (m.group(1), m.group(2))]); continue
        if len(notes) >= maxn:
            break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
