# -*- coding: utf-8 -*-
"""
函数卡片流水线（会话 10 · 回应"整文件代理太烧 token"教训）

用法：
  python tools/gen_func_cards.py                 # 扫描 src/ 全部函数，生成 data/func_cards/
  python tools/gen_func_cards.py --clean         # 清空卡片目录重建
  python tools/gen_func_cards.py --stats         # 只看统计
  python tools/gen_func_cards.py --batch FILE START COUNT [OUT]
                                                 # 为某文件第 START 张起的 COUNT 张未完成卡
                                                 # 生成批量工单 _batch.txt（子代理输入）

设计（承接会话 9 教训：代理反复整读 1.2-1.4 万行文件，65.8M token 只精修 5 文件）：
1. 卡片 = data/func_cards/<VA8>.txt（~12 行）：VA、文件+行区间、签名、字符串证据、
   被调函数（带全库语义名）、行数、优先级。子代理读 1 卡 ~200 token，只需 Read 函数
   自身 30-80 行再 Edit，单函数 ~2-4K token，比整文件代理省 ~30 倍。
2. 卡片即台账：做完一批删一批（data/func_cards/_done.txt 记账），天然断点续作。
3. 优先级 HIGH：行数 >40 或含资源串证据（.ani/.str/.img/.equ/... 或全大写错误串）。
4. 安全：只生成卡片不碰 src/；精修由子代理按 docs/60 规范执行，
   每批后必须跑 tools/verify_refine.py（结构级终验，违规则按 VA 回滚）。

铁律（Git Bash 教训）：行首扫描一律用 Python 正则，不用 grep ^//。
"""
import io, os, re, sys, glob, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
CARDS = os.path.join(ROOT, "data", "func_cards")

VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6})(?![0-9A-Za-z])")   # 分隔行：0x 后必须空白/行尾
BARE_HEAD = re.compile(r"^// 0x[0-9A-F]{6} (sub_[0-9A-F]{6}|[A-Za-z_][\w]*)$")
STR_LIT = re.compile(r'"((?:\\.|[^"\\])*)"')
SUB_CALL = re.compile(r'\b(sub_[0-9A-F]{6}|[A-Za-z_]\w*__vmt[0-9A-Fa-f]+)\b')
VT_CALL = re.compile(r'\bvt\+([0-9A-Fa-f]{2,4})\b')
RES_EXT = re.compile(r'\.(ani|str|img|equ|skl|npk|bmp|tga|wav|lst|pkg|jpg|png|dds)\b', re.I)
ALLCAPS = re.compile(r'^[A-Z0-9_ /\.\-%]{6,}$')

# 文件价值分层（会话 10 决策：missing_tail = CRT/平台尾部，最低价值）
LOW_VALUE_FILES = {"platform/missing_tail.cpp"}


def norm_key(p):
    return p.replace("\\", "/").split("src/")[-1]


def parse_file(path):
    """解析一个 cpp → [(va, marker_line_idx, body_lines, sig_line, strings, calls, title)]"""
    txt = io.open(path, encoding="utf-8", errors="replace").read()
    lines = txt.split("\n")
    funcs = []
    labels = {}          # va -> title（本文件分隔行标题）
    i = 0
    n = len(lines)
    while i < n:
        m = VA_HEAD.match(lines[i])
        if not m:
            # 顺带收集本文件的分隔行标题（含历史已精修函数）
            m2 = VA_HEAD.match(lines[i]) or re.match(r"^// 0x([0-9A-F]{6})(?![0-9A-Za-z])", lines[i])
            i += 1
            continue
        va = int(m.group(1), 16)
        marker = lines[i].strip()
        # 找签名行（跳过分隔线与注释块）
        j = i + 1
        sig = ""
        body_start = None
        blank_or_comment = 0
        while j < n:
            s = lines[j].strip()
            if VA_HEAD.match(lines[j]):
                break
            if not s:
                j += 1
                continue
            if s.startswith("//"):
                blank_or_comment += 1
                j += 1
                continue
            sig = s
            body_start = j + 1
            break
        # 函数体行区间 = 签名行后到下一个 VA 头前；再裁掉尾部注释/空行
        #（函数之间的过渡注释行属于下一个函数的头注释，泄漏进本函数会污染证据列）
        end = j
        body = []
        if body_start:
            p = body_start
            while p < n:
                if VA_HEAD.match(lines[p]):
                    break
                end = p
                p += 1
            while end >= body_start:
                s = lines[end].strip()
                if s and not s.startswith("//"):
                    break
                end -= 1
            body = lines[body_start:end + 1]
        nlines = sum(1 for l in body if l.strip() and not l.strip().startswith("//"))
        strings = []
        for l in body:
            for sm in STR_LIT.finditer(l):
                sv = sm.group(1)
                if 3 <= len(sv) <= 120 and not sv.startswith("S"):
                    strings.append(sv)
        # 去重保序
        seen = set()
        strings = [s for s in strings if not (s in seen or seen.add(s))]
        calls = []
        callset = set()
        for l in body:
            for cm in SUB_CALL.finditer(l):
                if cm.group(1) not in callset:
                    callset.add(cm.group(1))
                    calls.append(cm.group(1))
        vts = []
        for l in body:
            for vm in VT_CALL.finditer(l):
                v = "vt+" + vm.group(1).upper()
                if v not in vts:
                    vts.append(v)
        # 现有头注释（marker 行之后的连续注释块，跳过纯分隔线，最多 3 行采样）
        head_cmt = []
        q = i + 1
        while q < n and len(head_cmt) < 3:
            s = lines[q].strip()
            if not s or re.match(r"^// ?-+ ?$", s):
                q += 1
                continue
            if s.startswith("//"):
                head_cmt.append(s)
                q += 1
            else:
                break
        funcs.append(dict(va=va, file=norm_key(path), marker=marker, sig=sig,
                          nlines=nlines, strings=strings, calls=calls, vts=vts,
                          head_cmt=head_cmt, line_range=(i + 1, end + 1)))
        i = j if j > i else i + 1
    return funcs


def global_labels():
    """全库分隔行标题图：VA -> 语义名（来源：所有 cpp 的 `// 0xNNNNNN 标题` 行）"""
    lab = {}
    for path in glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True):
        txt = io.open(path, encoding="utf-8", errors="replace").read()
        for line in txt.split("\n"):
            m = VA_HEAD.match(line)
            if m:
                va = int(m.group(1), 16)
                title = line.strip()[len(m.group(0)):].strip(" -—")
                if title and va not in lab:
                    lab[va] = title
    return lab


def prio_of(f):
    res = [s for s in f["strings"] if RES_EXT.search(s)]
    caps = [s for s in f["strings"] if ALLCAPS.match(s)]
    if f["nlines"] > 40 or res or caps:
        return "HIGH"
    return "NORM"


def card_text(f, lab, prio):
    calls_str = ""
    for c in f["calls"][:8]:
        t = ""
        if c.startswith("sub_"):
            va = int(c[4:], 16)
            t = lab.get(va, "")
        elif "__vmt" in c:
            t = "(RTTI 虚方法)"
        calls_str += "  %s%s\n" % (c, (" = " + t[:40]) if t else " = (无语义名)")
    vts_str = " ".join(f["vts"][:8])
    strs = " ".join('"%s"' % s[:60] for s in f["strings"][:6])
    old_cmt = "\n".join("  " + c[:70] for c in f["head_cmt"][:2])
    return (
        "VA 0x%08X | %d 行代码 | %s L%d-%d\n"
        "sig: %s\n"
        "现有头注释: %s\n"
        "字符串证据: %s\n"
        "被调函数:\n%s"
        "虚表调用: %s\n"
        "优先级: %s\n"
    ) % (f["va"], f["nlines"], f["file"], f["line_range"][0], f["line_range"][1],
         f["sig"][:110] if f["sig"] else "?", old_cmt if old_cmt else "(无)",
         strs if strs else "(无)", calls_str if calls_str else "  (无)\n",
         vts_str if vts_str else "(无)", prio)


def main():
    args = sys.argv[1:]
    lab = global_labels()
    print("全库语义标签: %d 个" % len(lab))

    all_funcs = []
    for path in sorted(glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True)):
        all_funcs.extend(parse_file(path))

    # 同 VA 多文件：保留首个（L1/L2 双层场景罕见于裸函数）
    seen_va = {}
    uniq = []
    for f in all_funcs:
        if f["va"] in seen_va:
            continue
        seen_va[f["va"]] = f
        uniq.append(f)

    # "需处理"定义：marker 是裸形式（`// 0xNNNNNN sub_NNNNNN`，无语义标题）
    # 且其后无注释块。标题写在 marker 行内（已精修文件的常见形态）也算已完成。
    needs = [f for f in uniq
             if re.match(r"^// 0x[0-9A-F]{6} (sub_[0-9A-F]{6}|[A-Za-z_]\w*)$", f["marker"])
             and not f["head_cmt"]]

    for f in needs:
        f["prio"] = prio_of(f)
        f["low"] = f["file"] in LOW_VALUE_FILES

    hi = [f for f in needs if f["prio"] == "HIGH"]
    hi_in = [f for f in hi if not f["low"]]
    print("全库唯一函数: %d" % len(uniq))
    print("无头注释需处理: %d  (HIGH %d, 其中非低价值文件 HIGH %d)" % (len(needs), len(hi), len(hi_in)))

    if args and args[0] == "--stats":
        return
    if args and args[0] == "--batch":
        path, start, count = args[1], int(args[2]), int(args[3])
        out = args[4] if len(args) > 4 else os.path.join(CARDS, "_batch.txt")
        pool = [f for f in needs if f["file"] == norm_key(path)]
        seg = pool[start:start + count]
        buf = []
        for f in seg:
            buf.append(card_text(f, lab, f["prio"]))
        io.open(out, "w", encoding="utf-8").write("\n".join(buf))
        print("批量工单: %d 张 -> %s" % (len(seg), out))
        return

    if args and args[0] == "--clean":
        if os.path.isdir(CARDS):
            shutil.rmtree(CARDS)

    os.makedirs(CARDS, exist_ok=True)
    for f in needs:
        io.open(os.path.join(CARDS, "%08X.txt" % f["va"]), "w", encoding="utf-8").write(
            card_text(f, lab, f["prio"]))
    # 索引台账
    with io.open(os.path.join(CARDS, "_index.tsv"), "w", encoding="utf-8") as w:
        w.write("VA\tfile\tnlines\tprio\tlow_value\tline_start\tline_end\tsig\n")
        for f in sorted(needs, key=lambda x: (x["low"], {"HIGH": 0, "NORM": 1}[x["prio"]],
                                              -x["nlines"], x["va"])):
            w.write("%08X\t%s\t%d\t%s\t%d\t%d\t%d\t%s\n" % (
                f["va"], f["file"], f["nlines"], f["prio"], 1 if f["low"] else 0,
                f["line_range"][0], f["line_range"][1], f["sig"][:80]))
    print("卡片目录: %s (%d 张 + _index.tsv)" % (CARDS, len(needs)))


if __name__ == "__main__":
    main()
