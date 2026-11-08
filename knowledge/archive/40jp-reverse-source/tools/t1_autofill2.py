# -*- coding: utf-8 -*-
"""客观粗注生成器 v2（仅样板/机械赋值行）。
对可 100% 客观陈述的语句生成行尾注释。严禁猜测语义。
"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^\*\(this \+ (\d+)\) = 0;$'), lambda m: "this+%s 清 0" % m.group(1)),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = 0;$'), lambda m: "this 偏移 %d 清 0" % (int(m.group(1))*4)),
    (re.compile(r'^\*\(this \+ (\d+)\) = (\d+);$'), lambda m: "this+%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %d = %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %s 字节 = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = &(.+);$'), lambda m: "this 偏移 %d = 接口/vftable %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint16_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %d（uint16）= %s" % (int(m.group(1))*2, m.group(2))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = 0;$'), lambda m: "this 偏移 %s 清 0" % m.group(1)),
    (re.compile(r'^return 1;$'), lambda m: "返回 1（成功）"),
    (re.compile(r'^return 0;$'), lambda m: "返回 0"),
    (re.compile(r'^return result;$'), lambda m: "返回 result"),
    (re.compile(r'^return this;$'), lambda m: "返回 this"),
    (re.compile(r'^return -2147483646;$'), lambda m: "返回 0x80000002（已初始化）"),
    (re.compile(r'^return -2147483640;$'), lambda m: "返回 0x80000008（内存不足）"),
    (re.compile(r'^return -2147483647;$'), lambda m: "返回 0x80000001（未就绪）"),
    (re.compile(r'^return 0x80000000;$'), lambda m: "返回 0x80000000（失败）"),
    (re.compile(r'^return -2147483641;$'), lambda m: "返回 0x80000007（E_FAIL）"),
    (re.compile(r'^return -2147483646 $'), lambda m: "返回 0x80000002"),
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
                notes.append([i, fn(m)]); break
    d = {"file": rel, "notes": notes}
    out = ROOT + "\\work\\_auto2_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
