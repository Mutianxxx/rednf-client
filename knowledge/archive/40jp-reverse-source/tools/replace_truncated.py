# -*- coding: utf-8 -*-
# 截断替换: 用 dump_full_*.txt 的完整函数体替换源码中被截断的函数块
import io, os, re, glob, sys
sys.path.insert(0, os.path.dirname(__file__))
from importlib import util
spec = util.spec_from_file_location("tr", os.path.join(os.path.dirname(__file__), "transcribe.py"))
tr = util.module_from_spec(spec); spec.loader.exec_module(tr)

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

# 1) 收集完整函数
full = {}
for i in range(3):
    p = os.path.join(ROOT, "work", "dump_full_%d.txt" % i)
    if os.path.exists(p):
        for f in tr.parse_dump(p):
            full[f["va"]] = f
print("完整函数载入:", len(full))

# 2) 逐文件替换
replaced = 0
counts = {}
for path in glob.glob(os.path.join(ROOT, "src", "**", "*.cpp"), recursive=True):
    src = io.open(path, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    lines = src.split("\n")
    out = []
    i = 0
    file_repl = 0
    while i < len(lines):
        line = lines[i]
        # 头注释行: // 0xXXXXXX name
        m = re.match(r"^// 0x([0-9A-F]{6})\s*(.*)$", line)
        if m:
            va = int(m.group(1), 16)
            # 找函数块边界: 从本行到下一个 "// ----" 分隔线(或文件尾)
            j = i + 1
            # 跳过 "// ----" 包装线
            while j < len(lines) and lines[j].startswith("// ---"):
                j += 1
            body_start = j
            # 找块结束: 下一个 "// ---" 或下一个 "// 0x"
            k = body_start
            while k < len(lines):
                if lines[k].startswith("// ---") or re.match(r"^// 0x([0-9A-F]{6})", lines[k]):
                    break
                k += 1
            # 检查体内是否有截断标记
            body = "\n".join(lines[body_start:k])
            has_trunc = "truncated, total" in body
            if has_trunc and va in full:
                # 用完整版替换 body
                new_body = "\n".join(tr.clean_type(l) for l in full[va]["body"])
                out.append(line)  # 保留头注释
                # 保留包装线
                for w in range(i + 1, body_start):
                    out.append(lines[w])
                out.extend(new_body.split("\n"))
                i = k
                replaced += 1
                file_repl += 1
                continue
        out.append(line)
        i += 1
    if file_repl:
        io.open(path, "w", encoding="utf-8").write("\n".join(out))
        rel = path.replace(ROOT + "\\", "")
        counts[rel] = file_repl
        print("%-60s replaced %d" % (rel, file_repl))

print()
print("总替换:", replaced)

# 守卫: 替换数必须等于清单数（docs/22 §五 #1——防静默跳过）
import io as _io
expect = sum(1 for _l in _io.open(os.path.join(ROOT, "work", "truncated_funcs.txt"), encoding="utf-8") if _l.strip())
if replaced != expect:
    raise SystemExit("!! 守卫触发: 期望替换 %d 个，实际 %d 个——有函数被静默跳过，请人工检查" % (expect, replaced))
io.open(os.path.join(ROOT, "work", "trunc_replace_report.txt"), "w", encoding="utf-8").write(
    "replaced=%d\n" % replaced + "\n".join("%s\t%d" % kv for kv in sorted(counts.items())))
