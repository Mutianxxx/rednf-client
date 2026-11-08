# -*- coding: utf-8 -*-
"""客观粗注生成器 v3：含结构花括号 + 删除壳/样板赋值等客观形态。"""
import io, re, sys, json

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

RULES = [
    (re.compile(r'^\*\(this \+ (\d+)\) = 0;$'), lambda m: "this+%s 清 0" % m.group(1)),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = 0;$'), lambda m: "this 偏移 %d 清 0" % (int(m.group(1))*4)),
    (re.compile(r'^\*\(this \+ (\d+)\) = (\d+);$'), lambda m: "this+%s = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %d = %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %s 字节 = %s" % (m.group(1), m.group(2))),
    (re.compile(r'^\*\(\(uint8_t \*\)this \+ (\d+)\) = 0;$'), lambda m: "this 偏移 %s 清 0" % m.group(1)),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = &(.+);$'), lambda m: "this 偏移 %d = vftable/接口 %s" % (int(m.group(1))*4, m.group(2))),
    (re.compile(r'^\*\(\(uint16_t \*\)this \+ (\d+)\) = (\d+);$'), lambda m: "this 偏移 %d（uint16）= %s" % (int(m.group(1))*2, m.group(2))),
    (re.compile(r'^\*\(\(uint32_t \*\)this \+ (\d+)\) = nArg(\d);$'), lambda m: "this 偏移 %d = 参数%d" % (int(m.group(1))*4, int(m.group(2)))),
    # generic returns
    (re.compile(r'^return 1;$'), lambda m: "返回 1（成功）"),
    (re.compile(r'^return 0;$'), lambda m: "返回 0"),
    (re.compile(r'^return result;$'), lambda m: "返回 result"),
    (re.compile(r'^return this;$'), lambda m: "返回 this"),
    (re.compile(r'^return -2147483646;$'), lambda m: "返回 0x80000002（已初始化）"),
    (re.compile(r'^return -2147483640;$'), lambda m: "返回 0x80000008（内存不足）"),
    (re.compile(r'^return -2147483647;$'), lambda m: "返回 0x80000001（未就绪）"),
    (re.compile(r'^return 0x80000000;$'), lambda m: "返回 0x80000000（失败）"),
    (re.compile(r'^return -2147483641;$'), lambda m: "返回 0x80000007（E_FAIL）"),
    (re.compile(r'^return -2147483639;$'), lambda m: "返回 0x80000009（类型错）"),
    (re.compile(r'^return Block;$'), lambda m: "返回 Block"),
    (re.compile(r'^return nArg\d;$'), lambda m: "返回入参"),
    # delete shells / common boilerplate
    (re.compile(r'^if \( \(pszArg2 & 1\) != 0 \)$'), lambda m: "scalar deleting 位 0 置位（是否 free）"),
    (re.compile(r'^j__free\(Block\);$'), lambda m: "free 堆对象"),
    (re.compile(r'^dword_796E502 = dword_796E50;$'), lambda m: "栈检 cookie"),
    (re.compile(r'^break;$'), lambda m: "跳出 switch"),
    (re.compile(r'^default:$'), lambda m: "默认分支"),
    # throw helpers
    (re.compile(r'^pExceptionObject\[0\] = &std::length_error::`vftable\';$'), lambda m: "设 length_error vftable"),
    (re.compile(r'^_CxxThrowException\(pExceptionObject, \(_ThrowInfo \*\)&_TI3_AVlength_error_std__\);$'), lambda m: "抛 length_error 异常"),
    (re.compile(r'^pExceptionObject\[0\] = &std::out_of_range::`vftable\';$'), lambda m: "设 out_of_range vftable"),
    (re.compile(r'^_CxxThrowException\(pExceptionObject, \(_ThrowInfo \*\)&_TI3_AVout_of_range_std__\);$'), lambda m: "抛 out_of_range 异常"),
    (re.compile(r'^sub_401740\(pExceptionObject, &v1\);$'), lambda m: "构造异常对象"),
    (re.compile(r'^sub_401740\(pExceptionObject, \(int\)v22\);$'), lambda m: "构造异常对象"),
    (re.compile(r'^v4 = 15;$'), lambda m: "临时串容量 15"),
    (re.compile(r'^v3 = 0;$'), lambda m: "v3 = 0"),
    (re.compile(r'^v2 = 0;$'), lambda m: "v2 = 0"),
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
    out = ROOT + "\\work\\_auto3_" + rel.replace("/", "_") + ".json"
    io.open(out, "w", encoding="utf-8").write(json.dumps(d, ensure_ascii=False))
    print("generated %d notes -> %s" % (len(notes), out))

if __name__ == "__main__":
    main()
