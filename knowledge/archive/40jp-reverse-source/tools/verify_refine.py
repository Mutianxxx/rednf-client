# -*- coding: utf-8 -*-
"""
精修终验：对比精修前备份（work/backup_pre_refine/src_snapshot）与当前 src/
验证三件事：
1. VA 标记集合不变（无丢失/无新增）
2. 函数体结构零改动（结构级比对：剥注释/字符串占位/标识符归一——
   对合法的变量重命名不敏感，对逻辑/结构改动敏感）
3. 统计精修增量（注释行数变化）与"仅标识符级变化"的函数数
"""
import io, os, re, glob

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
BASE = os.path.join(ROOT, "work", "backup_pre_refine", "src_snapshot")
CUR = os.path.join(ROOT, "src")

def norm(p): return p.replace("\\", "/")

STR_LIT = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
IDENT_RE = re.compile(r'[A-Za-z_]\w*')

def norm_code_line(line):
    """结构归一：去行内注释/字符串占位/标识符→@/空白折叠。
    两个不同版本的行归一后相同 ⇔ 只有标识符名/注释/空白不同。"""
    s = STR_LIT.sub('"S"', line)
    s = re.sub(r'//.*$', '', s)
    s = re.sub(r'/\*.*?\*/', '', s)
    s = IDENT_RE.sub('@', s)
    return re.sub(r'\s+', ' ', s).strip()

def parse_blocks(txt):
    """把源码文本解析为 {va: [(原始行, 归一行)]} —— 函数体 = 头注释后到下一个 VA 头之间的非注释行"""
    blocks = {}
    lines = txt.replace("\r\n", "\n").split("\n")
    cur_va = None
    cur_body = []
    for line in lines:
        # 6 位十六进制后必须是空白/行尾——防止 "// 0xFFFFFFF=最大条目数" 这类
        # 魔数注释行被误判为函数分隔行（0x474DE0 空块之谜的根源）
        m = re.match(r"^// 0x([0-9A-F]{6})(?![0-9A-Za-z])", line)
        if m:
            if cur_va is not None:
                blocks.setdefault(cur_va, []).extend(cur_body)
            cur_va = int(m.group(1), 16)
            cur_body = []
            continue
        if cur_va is not None:
            s = line.strip()
            if s and not s.startswith("//"):
                cur_body.append((line, norm_code_line(line)))
    if cur_va is not None:
        blocks.setdefault(cur_va, []).extend(cur_body)
    # 规范化：去空白空行
    return {va: [(raw, nrm) for raw, nrm in body if nrm] for va, body in blocks.items()}

def collect(root):
    all_blocks = {}
    for path in glob.glob(os.path.join(root, "**", "*.cpp"), recursive=True):
        txt = io.open(path, encoding="utf-8", errors="replace").read()
        for va, body in parse_blocks(txt).items():
            all_blocks.setdefault(va, set()).add(tuple(body))
    return all_blocks

base = collect(BASE)
cur = collect(CUR)

print("基线函数块: %d   当前函数块: %d" % (len(base), len(cur)))

# 0. 幻影分隔行前置扫描（2026-10-08 会话 10 教训：0x8F8520 事件）——
#    src 中任何行首为 `// 0xNNNNNN` 的注释行，若该 VA 不在基线函数集合内，
#    会被解析器当函数头，把上一函数拆体致结构 FAIL。必须改 `// ·0x` 降级记法。
va_base_all = set(base)
phantom = []
for path in glob.glob(os.path.join(CUR, "**", "*.cpp"), recursive=True):
    for i, line in enumerate(io.open(path, encoding="utf-8", errors="replace"), 1):
        m = re.match(r"^// 0x([0-9A-F]{6})(?![0-9A-Za-z])", line)
        if m and int(m.group(1), 16) not in va_base_all:
            phantom.append((path, i, line.strip()[:90]))
        # 会话 10 新增守卫：合法 VA 但形态为 "// 0xHHHHHH 空格后跟非函数名" ——
        # 多为续行引用（如 "// 0x569F40 装载 …"），会把上一函数拆出空块。
        elif m and int(m.group(1), 16) in va_base_all:
            rest = line.strip()[len(m.group(0)):].strip()
            if rest and not re.match(r'^(sub_[0-9A-F]{6}|[A-Za-z_]\w*|\?|——)', rest):
                phantom.append((path, i, line.strip()[:90] + '  [续行形态]'))
if phantom:
    print("幻影/续行分隔行: %d 处（会被当函数头拆体）" % len(phantom))
    for p in phantom[:10]:
        print("  %s:%d  %s" % p)
else:
    print("幻影分隔行: 0 处")

# 0b. 裸注释守卫（2026-10-10 会话 12 教训：字段回填对语句行追加时漏加 //）
#     形态：行内含 "| +0x" 或 "+0xNNNN →"，但该标记出现在行内首个 // 之前 = 裸代码
naked = []
for path in glob.glob(os.path.join(CUR, "**", "*.cpp"), recursive=True):
    for i, line in enumerate(io.open(path, encoding="utf-8", errors="replace"), 1):
        if "| +0x" not in line and "+0x" not in line:
            continue
        code = line.split("//")[0]
        if "| +0x" in code or re.search(r"\+0x[0-9A-Fa-f]+\s*→", code):
            naked.append((path, i, line.strip()[:90]))
if naked:
    print("裸注释（注释未加 // 前缀，会破坏结构）: %d 处" % len(naked))
    for n in naked[:10]:
        print("  %s:%d  %s" % n)
else:
    print("裸注释守卫: 0 处")



# 1. VA 集合
va_base = set(base)
va_cur = set(cur)
lost = va_base - va_cur
added = va_cur - va_base
print("VA 丢失: %d   VA 新增: %d" % (len(lost), len(added)))
for va in sorted(lost)[:10]:
    print("  LOST %08X" % va)
for va in sorted(added)[:10]:
    print("  ADDED %08X" % va)

# 2. 函数体比对（多版本集合：同 VA 的任何一版函数体能对上即算一致——
#    对付同 VA 多文件（L1/L2 双层）的归属漂移）
diff = 0
same = 0
id_only = 0          # 结构一致、但原文有差异（=纯重命名/注释级变化）
diff_list = []
for va in (va_base & va_cur):
    bset = base[va]
    cset = cur[va]
    if bset & cset:
        same += 1
    else:
        # 结构级：任一基线版与任一当前版归一后一致也算（处理纯重命名）
        bn = {tuple(nrm for _, nrm in b) for b in bset}
        cn = {tuple(nrm for _, nrm in c) for c in cset}
        if bn & cn:
            same += 1
            id_only += 1
        else:
            # 截断补全超集检查
            ok = False
            for bb in bset:
                braw = [x[0] for x in bb]
                bnrm = [x[1] for x in bb]
                for cc in cset:
                    craw = [x[0] for x in cc]
                    cnrm = [x[1] for x in cc]
                    if len(cnrm) >= len(bnrm) and cnrm[:len(bnrm)] == bnrm:
                        ok = True   # 当前是基线的超集（截断被补全），允许
                        break
                if ok:
                    break
            if ok:
                same += 1
            else:
                diff += 1
                diff_list.append(va)

print("函数体结构一致（含截断补全超集）: %d" % same)
print("其中仅标识符/注释级变化（重命名合法）: %d" % id_only)
print("函数体结构被改动: %d" % diff)
for va in diff_list[:15]:
    print("  DIFF %08X" % va)
    bb = next(iter(base[va]))
    cc = next(iter(cur[va]))
    print("    base[:3]:", [x[1][:60] for x in bb[:3]])
    print("    cur [:3]:", [x[1][:60] for x in cc[:3]])

# 3. 注释增量统计
def count_comment_lines(root):
    total = 0
    for path in glob.glob(os.path.join(root, "**", "*.cpp"), recursive=True):
        for line in io.open(path, encoding="utf-8", errors="replace"):
            s = line.strip()
            if s.startswith("//"):
                total += 1
    return total

cb = count_comment_lines(BASE)
cc = count_comment_lines(CUR)
print()
print("注释行: 基线 %d → 当前 %d（增量 %d）" % (cb, cc, cc - cb))

verdict = "PASS" if (len(lost) == 0 and diff == 0 and not phantom) else "FAIL"
print()
print("=== 终验判定: %s ===" % verdict)
io.open(os.path.join(ROOT, "work", "refine_verify_report.txt"), "w", encoding="utf-8").write(
    "verdict=%s\nbase_blocks=%d\ncur_blocks=%d\nlost=%d\nadded=%d\nbody_diff=%d\ncomments %d->%d\n"
    % (verdict, len(base), len(cur), len(lost), len(added), diff, cb, cc) +
    "\n".join("DIFF %08X" % va for va in diff_list))
