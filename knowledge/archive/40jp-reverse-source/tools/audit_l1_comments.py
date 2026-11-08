# -*- coding: utf-8 -*-
"""
L1 注释升级的"零体改动"校验器（audit）
========================================
用途：L1 精修阶段对转写文件做了**纯注释升级**后，证明"函数体零改动"。
方法：把源码文件剥离全部注释行/空白行，与从 dump 重新生成的 L2 基线做**逐 VA 块**
     代码行序列比较 —— 必须完全一致。

基线生成口径（复刻 L2 流水线）：
  transcribe.py 的 parse_dump + clean_type  →  replace_truncated.py 的
  截断替换（用 dump_full_*.txt 的完整体替换含 "truncated, total" 的块）

★ 关键判据：源码块**仍含** "truncated, total" 标记 ⇒ 该块当年未被替换，
  基线必须取 dump_misc_a 原版（含 `(int)` 显式转换等原文形态）；
  源码块**不含**该标记 ⇒ 该块当年被 dump_full 完整版替换过，基线取 dump_full。

用法:
  python tools/audit_l1_comments.py                 # 校验 PLAN 内的关键文件
  python tools/audit_l1_comments.py <dump> <lo> <hi> <src>
"""
import io, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from transcribe import parse_dump, clean_type  # noqa: E402

# 默认目标：(dump 文件名, 区块 lo, hi, 源码相对路径)
DEFAULT_TARGETS = [
    ("dump_misc_a.txt", 0x4D0000, 0x4E0000, "src/game/combat_core.cpp"),
    ("dump_misc_a.txt", 0x4E0000, 0x4F0000, "src/game/hiteff_monster.cpp"),
]


def load_full():
    """dump_full_*.txt = 超长函数的完整反编译输出（replace_truncated.py 的数据源）"""
    full = {}
    for i in range(3):
        p = os.path.join(ROOT, "work", "dump_full_%d.txt" % i)
        if os.path.exists(p):
            for f in parse_dump(p):
                full[f["va"]] = f
    return full


def src_blocks(path):
    """源码 → {va: (代码行列表, 块内是否仍含 truncated 标记)}
    注释行仅在匹配 `// 0xXXXXXX ` 时作为新块边界。"""
    out, cur, trunc = {}, None, {}
    for raw in io.open(path, encoding="utf-8"):
        line = raw.rstrip("\r\n").rstrip()
        s = line.strip()
        if not s:
            continue
        if s.startswith("//"):
            m = re.match(r"^// 0x([0-9A-Fa-f]{6}) ", s)
            if m:
                cur = int(m.group(1), 16)
                out.setdefault(cur, [])
                trunc.setdefault(cur, False)
            elif cur is not None and "truncated, total" in s:
                trunc[cur] = True
            continue
        if cur is not None:
            out[cur].append(line)
    return out, trunc


def baseline_blocks(dump_name, lo, hi, full, src_trunc):
    """dump → {va: [代码行]}（复刻 L2 两段流水线 + 上述关键判据）"""
    out = {}
    for f in parse_dump(os.path.join(ROOT, "work", dump_name)):
        va = f["va"]
        if not (lo <= va < hi):
            continue
        body = f["body"]
        # 仅当源码块已不含截断标记（= 当年被替换过）才取完整版
        if not src_trunc.get(va, True) and va in full:
            body = full[va]["body"]
        # dump 侧的截断标记行在源码里是注释（会被 src_blocks 丢弃），基线同样丢弃
        out[va] = [clean_type(b).rstrip() for b in body
                   if clean_type(b).strip() and "truncated, total" not in b]
    return out


def main():
    args = sys.argv[1:]
    targets = DEFAULT_TARGETS
    if len(args) == 4:
        targets = [(args[0], int(args[1], 0), int(args[2], 0), args[3])]

    full = load_full()
    allok = True
    for dump_name, lo, hi, src_rel in targets:
        src, src_trunc = src_blocks(os.path.join(ROOT, src_rel))
        base = baseline_blocks(dump_name, lo, hi, full, src_trunc)
        name = os.path.basename(src_rel)
        markers = sum(1 for l in io.open(os.path.join(ROOT, src_rel), encoding="utf-8")
                      if re.match(r"^// 0x[0-9A-F]{6}", l))
        only_src = sorted(set(src) - set(base))
        only_base = sorted(set(base) - set(src))
        bad = [v for v in sorted(set(src) & set(base)) if src[v] != base[v]]
        still_trunc = sum(1 for v in src if src_trunc.get(v))
        print("%-22s blocks=%d VA_markers=%d baseline=%d still_truncated=%d" %
              (name, len(src), markers, len(base), still_trunc))
        print("    only_in_src=%s  only_in_baseline=%s" %
              ([hex(v) for v in only_src], [hex(v) for v in only_base]))
        print("    body_diff=%s" % ([hex(v) for v in bad] or "none"))
        if only_src or only_base or bad:
            allok = False
            import difflib
            for va in (only_src + only_base + bad)[:5]:
                print("   --- %06X ---" % va)
                for l in list(difflib.unified_diff(
                        base.get(va, []), src.get(va, []), lineterm="", n=0))[:12]:
                    print("     ", l)
    print("RESULT: " + ("PASS —— 代码行零改动" if allok else "FAIL"))
    return 0 if allok else 1


if __name__ == "__main__":
    sys.exit(main())

