# -*- coding: utf-8 -*-
"""客观粗注生成器 v9：守卫判定/指针重定向/字段读取等客观形态。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    # 守卫: if ( *(uint...*)this + N ) ... 语义: 读 this 偏移字段
    (re.compile(r'^if \( \*\(uint8_t \*\)\(this \+ (\d+)\) == 0 \)$'), lambda m: "若 this 偏移 %s 为 0" % m.group(1)),
    (re.compile(r'^if \( \*\(uint8_t \*\)\(this \+ (\d+)\) != 0 \)$'), lambda m: "若 this 偏移 %s 非 0" % m.group(1)),
    (re.compile(r'^if \( \*\(uint32_t \*\)\(this \+ (\d+)\) != 0 \)$'), lambda m: "若 this 偏移 %d 非 0" % (int(m.group(1)))),
    (re.compile(r'^if \( \*\(uint32_t \*\)\(this \+ (\d+)\) == 0 \)$'), lambda m: "若 this 偏移 %d 为 0" % (int(m.group(1)))),
    # 指针成员重定向: **(uint32_t **)(X + N) = X
    (re.compile(r'^\*\*\(uint32_t \*\*\)\((\w+) \+ (\d+)\) = (\w+);$'), lambda m: "%s 偏移 %s 指向自身（自环）" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\*\(uint32_t \*\*\)\((\w+) \+ (\d+)\) = (\w+)\[(\w+)\];$'), lambda m: "%s 偏移 %s 指向 %s[%s]" % (m.group(1), m.group(2), m.group(3), m.group(4))),
    # 数组写
    (re.compile(r'^(\w+)\[(\w+)\] = (\w+);$'), lambda m: "%s[%s] = %s" % (m.group(1), m.group(2), m.group(3))),
    # 复杂 vtable 调用
    (re.compile(r'^\(\*\(void \(\/\*thiscall\*\/ \*\*\)\(char \*, int, int\)\)\(\*\(uint32_t \*\)this \+ (\d+)\)\)\(this, (\d+), (\d+)\);$'), lambda m: "调 this 虚表 +%s 槽 (this, %s, %s)" % (m.group(1), m.group(2), m.group(3))),
    # 字段读守卫
    (re.compile(r'^if \( \*\(uint32_t \*\)\((\w+) \+ (\d+)\) != (\d+) \)$'), lambda m: "若 %s 偏移 %s != %s" % (m.group(1), m.group(2), m.group(3))),
    (re.compile(r'^if \( \*\(uint32_t \*\)\((\w+) \+ (\d+)\) == (\d+) \)$'), lambda m: "若 %s 偏移 %s == %s" % (m.group(1), m.group(2), m.group(3))),
    # 指针跟随
    (re.compile(r'^(\w+) = \((\w+ \*)\*\)\*(\w+);$'), lambda m: "%s = 解引用跟踪 %s" % (m.group(1), m.group(3))),
    # 增量指针
    (re.compile(r'^(\w+) \+= (\d+);$'), lambda m: "%s 前进 %s" % (m.group(1), m.group(2))),
    # 简单 this 字段读取赋值给局部
    (re.compile(r'^(\w+) = \*\(this \+ (\d+)\);$'), lambda m: "%s = this+%s" % (m.group(1), m.group(2))),
    (re.compile(r'^(\w+) = \*\(\(uint32_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %d" % (m.group(1), int(m.group(2)))),
    (re.compile(r'^(\w+) = \*\(\(uint8_t \*\)this \+ (\d+)\);$'), lambda m: "%s = this 偏移 %s" % (m.group(1), m.group(2))),
    # 本地数组写
    (re.compile(r'^(\w+)\[(\w+) \+ (\w+)\] = (\w+);$'), lambda m: "%s[%s+%s] = %s" % (m.group(1), m.group(2), m.group(3), m.group(4))),
    # 全局变量写
    (re.compile(r'^(dword_[0-9A-F]+) = (\d+);$'), lambda m: "%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(byte_[0-9A-F]+) = (\d+);$'), lambda m: "%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(word_[0-9A-F]+) = (\d+);$'), lambda m: "%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^(dword_[0-9A-F]+) = nullptr;$'), lambda m: "%s = 空指针" % m.group(1)),
    (re.compile(r'^(dword_[0-9A-F]+) = \((\w+)\)(\w+);$'), lambda m: "%s = %s" % (m.group(1), m.group(3))),
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
    out = ROOT + "\\work\\_auto9_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
