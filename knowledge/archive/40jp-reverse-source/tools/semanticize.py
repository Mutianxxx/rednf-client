# -*- coding: utf-8 -*-
"""
semanticize.py —— 全库语义化变量重命名 + 调用点语义名标注

回应批评："就是 IDA 反编译拿出来，变量名都没写，纯伪代码导出"。
本工具对 src/ 全部 .cpp 做两件事（不改任何逻辑，只改可读性）：

  Pass A  变量语义重命名（按证据推断，逐函数作用域）：
          - 赋值来源:   v3 = fopen(..)      -> pFile
                       v5 = strlen(..)     -> nLen
                       v2 = (char*)(this+16) -> pThis_10
                       v8 = malloc(..)     -> pMem ...
          - 参数类型:   const char *a1 -> pszArg1 / FILE *a3 -> pFile /
                       指针型 aN -> pArgN / 整型值参 -> nArgN(有符号)/uArgN(无符号)
          - 循环下标:   for( v10 = 0; ...; ++v10 ) -> i / j / k
          - 无证据不改名（保持 vN 原样，可回溯），这是本工程的命名铁律。

  Pass B  调用点标注: 行内 sub_XXXX( 若该 VA 在全库有语义标签（分隔行注释
          / 研究锚点别名），行尾追加  // 【语义名】；已有注释的行不动。

  安全性: 内置"骨架校验"——去掉注释/字符串后把标识符全部替换为 '@'，
          前后骨架必须完全一致才允许写盘；否则保留原文件并报错。
          另校验: 行数不变、函数分隔行（// 0xVA）数量不变。

用法:
  python tools/semanticize.py            # 就地改造 src/（先自动备份到 work/backup_pre_semanticize）
  python tools/semanticize.py --verify   # 备份 vs 当前，复检骨架/行数/VA 数
"""
import os
import re
import sys
import shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
BACKUP = os.path.join(ROOT, "work", "backup_pre_semanticize")

# ---------------------------------------------------------------- 基础工具

STR_OR_CHAR = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


def strip_strings(text: str) -> str:
    return STR_OR_CHAR.sub(lambda m: '"' if m.group(0).startswith('"') else "'", text)


def strip_comments(text: str) -> str:
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = re.sub(r'//[^\n]*', '', text)
    return text


IDENT = re.compile(r'[A-Za-z_]\w*')


def skeleton(text: str) -> str:
    """去注释+去字符串(留占位)+标识符→@+行尾空白归一。
    前后一致 ⇔ 只有标识符/注释/行尾空白变了。"""
    t = STR_OR_CHAR.sub('"S"', text)
    t = strip_comments(t)
    t = IDENT.sub('@', t)
    return "\n".join(l.rstrip() for l in t.split("\n"))


def map_outside_strings(line: str, fn) -> str:
    """对一行里非字符串字面量片段逐段应用 fn。"""
    out, pos = [], 0
    for m in STR_OR_CHAR.finditer(line):
        out.append(fn(line[pos:m.start()]))
        out.append(m.group(0))
        pos = m.end()
    out.append(fn(line[pos:]))
    return "".join(out)


# ---------------------------------------------------------------- Pass 0: VA→语义标签

SEP_RE = re.compile(r'^//\s*0x([0-9A-Fa-f]{6})\s+(.+?)\s*$')
SECOND_VA = re.compile(r'0x[0-9A-Fa-f]{6}')

# 研究锚点别名（全部来自各会话文档定案；sub_ 原名保持不变，仅作行尾标注）
CURATED = {
    "423200": "发送网络包API",
    "433690": "主帧循环",
    "41CC80": "模块切换矩阵",
    "528DB0": "打开PVF包",
    "528650": "读取PVF内容",
    "527AC0": "PVF目录块解密",
    "57A1C0": "CRC32表初始化",
    "4422C0": "PVF主加载器",
    "442950": "readScriptFromPVF",
    "40E3E0": "NPK按名取数据流",
    "40DED0": "NPK缓存查找",
    "40DB60": "NPK条目构造",
    "40E700": "NPK名字树插入",
    "418CD0": "IMG文件头打开校验",
    "66BD5A": "fread封装",
    "4015C0": "std::string构造赋值",
    "528D50": "PVF读取入口",
    "40E9E0": "NPK名字树查找",
}


def clean_label(raw: str) -> str:
    """分隔行标签 → 简短可读的行尾标注文本。"""
    lab = raw.split("——")[0] if "——" in raw else (raw.split("──")[0] if "──" in raw else raw)
    lab = lab.strip()
    lab = re.sub(r'^vmt[0-9A-Fa-f]+\s*', '', lab)
    lab = lab.replace("★", "").strip(" -—─、。")
    lab = re.sub(r'【[^】]*】', '', lab).strip()
    lab = lab.replace('"', '').replace('*/', '')
    if len(lab) > 44:
        lab = lab[:42].rstrip() + "…"
    return lab


def build_va_map() -> dict:
    vamap = {}
    for dirpath, _, files in os.walk(SRC):
        for fn in files:
            if not fn.endswith(".cpp"):
                continue
            with open(os.path.join(dirpath, fn), encoding="utf-8") as f:
                for line in f:
                    m = SEP_RE.match(line)
                    if not m:
                        continue
                    va, lab = m.group(1).lower(), m.group(2).strip()
                    if lab.startswith("sub_"):
                        continue                      # 纯 sub_XXXX 无语义
                    if SECOND_VA.search(lab):
                        continue                      # 一行多 VA 的备注行不取
                    lab = clean_label(lab)
                    if lab and va not in vamap:
                        vamap[va] = lab
    for va, lab in CURATED.items():
        vamap.setdefault(va.lower(), lab)
    return vamap


# ---------------------------------------------------------------- Pass A: 变量重命名

VTOK = re.compile(r'\b(v\d+|a\d+)\b')
ASSIGN = re.compile(r'\b(v\d+)\s*=(?!=)\s*([^;{}]+)')
SIG_START = re.compile(r'^[A-Za-z_`].*\(')

# RHS 来源规则（按序匹配，先命中先得）
RHS_RULES = [
    (re.compile(r'\b(?:_wfopen|fopen)\s*\('), "pFile"),
    (re.compile(r'\b(?:malloc|calloc|realloc|HeapAlloc|VirtualAlloc)\s*\('), "pMem"),
    (re.compile(r'\boperator new\s*\('), "pMem"),
    (re.compile(r'\b(?:_mbslen|strlen)\s*\('), "nLen"),
    (re.compile(r'\b(?:_mbscmp|_mbsncmp|memcmp|strncmp|strcmp)\s*\('), "nCmp"),
    (re.compile(r'\b(?:strrchr|strtok|strstr|strchr)\s*\('), "pFound"),
    (re.compile(r'\b(?:_atoi64|strtol|atol|atoi)\s*\('), "nVal"),
    (re.compile(r'\b(?:timeGetTime|GetTickCount)\s*\('), "dwNow"),
    (re.compile(r'\brand\s*\('), "nRand"),
    (re.compile(r'\bftell\s*\('), "nPos"),
    (re.compile(r'\b(?:fgetc|fgets|fread|getline)\s*\('), "nRead"),
    (re.compile(r'\bGetDlgItem\s*\('), "hCtrl"),
    (re.compile(r'\b(?:SendDlgItemMessage|SendMessage)\s*\('), "lRet"),
    (re.compile(r'\bLoadLibrary[AW]?\s*\('), "hLib"),
    (re.compile(r'\bGetProcAddress\s*\('), "pFn"),
    (re.compile(r'\bGetModuleHandle[AW]?\s*\('), "hMod"),
    (re.compile(r'\bCreateThread\s*\('), "hThread"),
    (re.compile(r'\b(?:GetDC|BeginPaint)\s*\('), "hDC"),
    (re.compile(r'\bDirect3DCreate8\s*\('), "pD3D"),
    (re.compile(r'\bCreateDevice\s*\('), "hr"),
    (re.compile(r'\bsub_423200\s*\('), "nSend"),
    (re.compile(r'\bsub_66BD5A\s*\('), "nRead"),
]
THIS_OFF = re.compile(r'\(\s*(?:\w+\s*\*+\s*)*this\s*\+\s*(0x[0-9a-fA-F]+|\d+)\s*\)')
THIS_OFF2 = re.compile(r'this\s*\)\s*\+\s*(0x[0-9a-fA-F]+|\d+)')
THIS_PLAIN = re.compile(r'this\s*\+\s*(0x[0-9a-fA-F]+|\d+)')
LOOP_FOR = re.compile(r'\bfor\s*\(\s*(v\d+)\s*=\s*(\d+)\b')

# 二级"用法证据"规则（对一级规则没命名的 vN 做补救，按序命中；%s=变量名占位）
USAGE_RULES = [
    # 虚表调用对象基址: (*(int *)v2 + 140))(v2, ...) → pObj
    (r'\(\s*\*\s*\(\s*[\w\s]+\*+\s*\)\s*%s\s*\+', "pObj"),
    # FILE* 族（首参；fgets/fread/fwrite 首参是缓冲区，不在此列）
    (r'\b(?:fclose|fseek|ftell|fgetc|fputs|fprintf|feof|rewind|ungetc)\s*\([^;()]*%s', "pFile"),
    # 字符串只读用法
    (r'\b(?:_mbslen|strlen)\s*\(\s*[^,()]*%s', "psz"),
    (r'\b(?:_mbscmp|_mbsncmp|strcmp|strncmp|strstr|strchr|strrchr|strcat|atoi|atol|strtol)\s*\([^;()]*%s', "psz"),
    (r'\b(?:strcpy|strncpy)\s*\(\s*[^,()]*\s*,[^;()]*%s', "psz"),
    # 缓冲区写/读用法
    (r'\b(?:memcpy|memmove|strcpy|strncpy|strcat|fread|fwrite|fgets)\s*\(\s*[^,()]*%s', "pBuf"),
    (r'\bmemset\s*\([^;()]*%s', "pBuf"),
]


def DerefUse(tok: str, body: str) -> bool:
    e = re.escape(tok)
    return bool(
        re.search(r'\*\s*\([^;()]*\b%s\s*[\+)]' % e, body)
        or re.search(r'\b%s\s*\[\s*\d' % e, body)
        or re.search(r'\(\s*[^;()]*\b%s\s*\+\s*(0x)?\d' % e, body))


TYPE_OF_PARAM = (
    r'((?:const\s+|unsigned\s+|signed\s+)*(?:__int\d+|_BYTE|_WORD|_DWORD|_QWORD|size_t|'
    r'BOOL|bool|int|char|short|long|float|double|void|FILE|HANDLE|HWND|HINSTANCE|DWORD|'
    r'WORD|BYTE|UINT)\s*\*{0,2})\s*')


def param_type(prelude: str, tok: str):
    m = re.search(TYPE_OF_PARAM + re.escape(tok) + r'\b(?!\w)(?!\s*\()', prelude)
    if not m:
        m = re.search(TYPE_OF_PARAM + re.escape(tok) + r'\b', prelude)
    return m.group(1) if m else None


def param_name(tok: str, typ, body: str) -> str:
    n = tok[1:]
    # 函数指针参数: 形如 (回调签名)aN —— 名字前紧跟 ')'
    if re.search(r'\)\s*' + re.escape(tok) + r'\s*[,)]', _prelude_now[0]):
        return "pFn" + n
    if typ is None:
        return "pArg" + n if DerefUse(tok, body) else "uArg" + n
    typ_norm = re.sub(r'\s+', ' ', typ).strip()
    stars = typ_norm.count('*')
    base = typ_norm.replace('*', '').strip()
    if base == 'FILE':
        return "pFile"
    if base == 'char':
        return "pszArg" + n
    if stars:
        if base in ('void', '_BYTE', 'BYTE', 'char'):
            return "pArg" + n
        if base in ('_DWORD', 'DWORD', 'int', 'unsigned int', 'UINT'):
            return "pDwArg" + n
        return "pArg" + n
    if DerefUse(tok, body):
        return "pArg" + n
    if 'unsigned' in typ_norm or base in ('_DWORD', 'DWORD', 'UINT', 'size_t', '_QWORD'):
        return "uArg" + n
    if base in ('float', 'double'):
        return "fArg" + n
    if base in ('bool', 'BOOL'):
        return "bArg" + n
    return "nArg" + n


# 当前块 prelude 的传递（避免改 param_name 签名的全局槽）
_prelude_now = [""]


def collect_blocks(lines):
    """返回 [(prelude文本, body文本, 起行, 止行)]；块=列0签名到配对'}'。"""
    blocks, i, n = [], 0, len(lines)
    while i < n:
        line = lines[i]
        if SIG_START.match(line) and '(' in line and not line.rstrip().endswith(';'):
            j, ok = i, True
            while '{' not in lines[j]:
                if lines[j].rstrip().endswith(';') or j - i > 3:
                    ok = False
                    break
                j += 1
                if j >= n:
                    ok = False
                    break
            if ok:
                depth, k = 0, j
                while k < n:
                    code = strip_comments(strip_strings(lines[k]))
                    depth += code.count('{') - code.count('}')
                    if depth <= 0:
                        break
                    k += 1
                if depth == 0 and k < n:
                    # 用 "".join 保留每行原行尾符，行边界不增不减
                    blocks.append(("".join(lines[i:j]), "".join(lines[j:k + 1]), i, k))
                    i = k + 1
                    continue
        i += 1
    return blocks


def rename_block(prelude: str, body: str):
    """返回 (新prelude, 新body, 重命名数)。"""
    toks = set(VTOK.findall(prelude + "\n" + body))
    if not toks:
        return prelude, body, 0

    forbidden = set(IDENT.findall(strip_comments(strip_strings(prelude + "\n" + body)))) - toks
    mapping = {}

    def take(name):
        base, k = name, 1
        while name in forbidden or name in mapping.values():
            k += 1
            name = "%s%d" % (base, k)
        forbidden.add(name)
        return name

    # 1) 参数 aN：按类型/用法
    _prelude_now[0] = prelude
    for t in sorted(toks):
        if t.startswith('a'):
            mapping[t] = take(param_name(t, param_type(prelude, t), body))
    # 2) 局部 vN：按赋值 RHS
    for m in ASSIGN.finditer(body):
        t, rhs = m.group(1), m.group(2)
        if t in mapping:
            continue
        for rx, name in RHS_RULES:
            if rx.search(rhs):
                mapping[t] = take(name)
                break
        else:
            stripped = rhs.strip()
            # 读字段值，必须括号包裹:
            #   *(uint32_t *)(this + 344) → fld_158（字节偏移）   *(this + 1) → fld_e1（元素下标）
            NAMED = r'(?:pArg|pObj|pThis|pDwArg|psz|pBuf|pFile|pMem|pFn)[\w]*'
            READ_CAST_THIS = r'\*\s*\([\w\s\*]+\)\s*\(\s*this\s*\+\s*(0x[0-9a-fA-F]+|\d+)\s*\)'
            READ_IDX_THIS = r'\*\s*\(\s*this\s*\+\s*(0x[0-9a-fA-F]+|\d+)\s*\)'
            READ_CAST_NAMED = r'\*\s*\([\w\s\*]+\)\s*\(\s*(%s)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\s*\)' % NAMED
            READ_IDX_NAMED = r'\*\s*\(\s*(%s)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\s*\)' % NAMED
            mo = re.search(READ_CAST_THIS, rhs)
            if mo:
                mapping[t] = take("fld_%X" % int(mo.group(1), 0))
                continue
            mo = re.search(READ_IDX_THIS, rhs)
            if mo:
                mapping[t] = take("fld_e%d" % int(mo.group(1), 0))
                continue
            mo = re.search(READ_CAST_NAMED, rhs)
            if mo:
                mapping[t] = take("fld_%s_%X" % (mo.group(1), int(mo.group(2), 0)))
                continue
            mo = re.search(READ_IDX_NAMED, rhs)
            if mo:
                mapping[t] = take("fld_%s_e%d" % (mo.group(1), int(mo.group(2), 0)))
                continue
            # 链表/指针自追踪: v4 = (int *)*v4 → pNext
            if re.fullmatch(r'\(?\s*[\w\s]*\*+\s*\)?\s*%s' % re.escape(t), stripped):
                mapping[t] = take("pNext")
                continue
            # *this + N 之类的值算术 —— 无字段语义，不命名
            if re.search(r'\*\s*this\b', stripped):
                pass
            else:
                mo = THIS_OFF.search(rhs) or THIS_OFF2.search(rhs) or THIS_PLAIN.search(rhs)
                if mo:
                    mapping[t] = take("pThis_%X" % int(mo.group(1), 0))
                elif re.search(r'\(\s*FILE\s*\*', rhs):
                    mapping[t] = take("pFile")
                elif re.fullmatch(r'(\([\w\s\*]+\))?\s*this\s*', rhs):
                    mapping[t] = take("pThis")
    # 2b) 二级用法证据补救（仍未命名的 vN）
    for t in list(toks):
        if t in mapping or not t.startswith('v'):
            continue
        guard = r'(?<![A-Za-z0-9_])' + re.escape(t) + r'(?![0-9])'
        for rx_tpl, name in USAGE_RULES:
            if re.search(rx_tpl.replace('%s', guard), body):
                mapping[t] = take(name)
                break
    # 2c) 继承命名: v3 = pszArg1 → 沿用来源名; v2 = dword_79D080 → 直接继承全局名
    changed = True
    while changed:
        changed = False
        for m in ASSIGN.finditer(body):
            t, rhs = m.group(1), m.group(2).strip()
            if t in mapping or not re.fullmatch(r'[A-Za-z_]\w*', rhs):
                continue
            src_name = mapping.get(rhs)
            if src_name is None and (re.match(r'(?:dword|word|byte|float|double|off|unk)_', rhs)
                                     or rhs.startswith('g_')
                                     or re.match(r'(?:Block|Ptr|Memory|String)$', rhs)):
                src_name = rhs
            if src_name and src_name != t:
                mapping[t] = take(src_name)
                changed = True
    # 3) 循环下标：for( vN = 数字; ...
    idx_names = ["i", "j", "k", "m", "n", "i2", "j2", "k2", "i3"]
    li = 0
    for m in LOOP_FOR.finditer(body):
        t = m.group(1)
        if t not in mapping:
            mapping[t] = take(idx_names[li % len(idx_names)])
            li += 1
    # 4) 剩余 vN 保留原名（无证据不改名）

    mapping = {k2: v2 for k2, v2 in mapping.items() if v2 != k2}
    if not mapping:
        return prelude, body, 0

    def sub_fn(seg):
        return re.sub(r'\b(v\d+|a\d+)\b', lambda m: mapping.get(m.group(0), m.group(0)), seg)

    def apply(text):
        return map_outside_strings(text, sub_fn)

    return apply(prelude), apply(body), len(mapping)


# ---------------------------------------------------------------- Pass B: 调用点标注

CALL_SUB = re.compile(r'\bsub_([0-9A-Fa-f]{6})\s*\(')


def annotate_calls(lines, vamap):
    hits = 0
    for idx, line in enumerate(lines):
        if '//' in line or line.lstrip().startswith('*'):
            continue
        m = CALL_SUB.search(line)
        if not m:
            continue
        lab = vamap.get(m.group(1).lower())
        if not lab:
            continue
        lines[idx] = line.rstrip("\n") + "  // 【%s】\n" % lab
        hits += 1
    return hits


# ---------------------------------------------------------------- 主流程

def run_pipeline(path, vamap, annotate=True, dry=False):
    """跑一遍 Pass A (+可选 Pass B)，返回 (结果, 问题列表)。"""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    lines = text.splitlines(keepends=True)
    n_va = sum(1 for l in lines if SEP_RE.match(l))
    skel = skeleton(text)
    n_lines = len(lines)

    renamed_total = 0
    for prelude, body, i0, i1 in collect_blocks(lines):
        new_pre, new_body, k = rename_block(prelude, body)
        if not k:
            continue
        merged = (new_pre + new_body).splitlines(keepends=True)
        if len(merged) != i1 - i0 + 1:      # 行数对不上则放弃该块（安全第一）
            continue
        lines[i0:i1 + 1] = merged
        renamed_total += k

    annotated = annotate_calls(lines, vamap) if annotate else 0

    new_text = "".join(lines)
    problems = []
    if len(lines) != n_lines:
        problems.append("行数变化 %d→%d" % (n_lines, len(lines)))
    if sum(1 for l in lines if SEP_RE.match(l)) != n_va:
        problems.append("分隔行数量变化")
    if skeleton(new_text) != skel:
        problems.append("骨架不一致(结构被改)")
    if problems:
        return None, renamed_total, annotated, problems
    if not dry:
        with open(path, "w", encoding="utf-8", newline="") as f:
            f.write(new_text)
    return n_lines, renamed_total, annotated, []


def process_file(path, vamap, dry=False):
    """带降级重试：标注引发校验失败 → 退回仅变量重命名；仍失败 → 拒绝写盘。
    返回 (行数, 重命名数, 标注数, 问题列表)；问题里 "(标注降级)" 只是提示不是失败。"""
    res, nren, nann, errs = run_pipeline(path, vamap, annotate=True, dry=dry)
    if not errs:
        return res, nren, nann, []
    res, nren2, _, errs2 = run_pipeline(path, vamap, annotate=False, dry=dry)
    if errs2:
        return None, 0, 0, errs2
    return res, nren2, 0, ["(标注降级)"]


def main():
    if "--verify" in sys.argv:
        bad = 0
        checked = 0
        for dirpath, _, fns in os.walk(SRC):
            for fn in sorted(fns):
                if not fn.endswith(".cpp"):
                    continue
                p = os.path.join(dirpath, fn)
                rel = os.path.relpath(p, SRC)
                bak = os.path.join(BACKUP, rel)
                if not os.path.exists(bak):
                    continue
                checked += 1
                a = open(bak, encoding="utf-8").read()
                b = open(p, encoding="utf-8").read()
                errs = []
                if len(a.splitlines()) != len(b.splitlines()):
                    errs.append("行数")
                if sum(1 for l in a.splitlines() if SEP_RE.match(l)) != \
                   sum(1 for l in b.splitlines() if SEP_RE.match(l)):
                    errs.append("VA分隔行")
                if skeleton(a) != skeleton(b):
                    errs.append("骨架")
                if errs:
                    bad += 1
                    print("[FAIL]", rel, errs)
        print("verify: 检查 %d 文件，%s" % (checked, "全部骨架/行数/VA 校验通过 ✓" if not bad else "%d 个有问题" % bad))
        return

    if not os.path.isdir(BACKUP):
        shutil.copytree(SRC, BACKUP)
        print("已备份原 src/ → work/backup_pre_semanticize/")

    vamap = build_va_map()
    print("VA 语义标签: %d 个（分隔行语义标签 + 研究锚点 %d）" % (len(vamap), len(CURATED)))

    files = []
    for dirpath, _, fns in os.walk(SRC):
        for fn in sorted(fns):
            if fn.endswith(".cpp"):
                files.append(os.path.join(dirpath, fn))
    files.sort()

    tot_r = tot_a = tot_f = fail = degr = 0
    for p in files:
        rel = os.path.relpath(p, SRC)
        _, nren, nann, errs = process_file(p, vamap)
        hard = [e for e in errs if not e.startswith("(标注")]
        if hard:
            fail += 1
            print("[拒绝写盘]", rel, hard)
            continue
        tot_f += 1
        tot_r += nren
        tot_a += nann
        if errs:
            degr += 1
            print("  %-56s 变量重命名%5d  调用标注%4d  (标注降级)" % (rel, nren, nann))
        elif nren or nann:
            print("  %-56s 变量重命名%5d  调用标注%4d" % (rel, nren, nann))
    print("\n完成: %d 文件 / 重命名 %d 个变量标识 / 标注 %d 个调用点 / 标注降级 %d / 拒绝 %d"
          % (tot_f, tot_r, tot_a, degr, fail))
    left = sum(len(VTOK.findall(open(p, encoding="utf-8").read())) for p in files)
    print("剩余 vN/aN 引用（无证据保留原样）: %d（改造前 381,012）" % left)


if __name__ == "__main__":
    main()
