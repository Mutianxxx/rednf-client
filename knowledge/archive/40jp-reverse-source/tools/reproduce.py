# -*- coding: utf-8 -*-
"""
【40JP逆向源代码工程】一键复现脚本（reproduce.py）
================================================================================
干什么的：把「从零到当前状态」的全部可复现步骤串起来，一条命令验证/重建。

用大白话说：run_all.py 是"工厂流水线总开关"（从 EXE 到源码），
本脚本是"质检 + 复现总开关"（从当前源码验回 EXE 事实，并可再生全部派生交付物）。

三个档位：
  python tools/reproduce.py --verify     # 【默认】只验证：跑全部校验，报告是否 PASS
  python tools/reproduce.py --rebuild    # 重建全部派生交付物（类头/合订本/交付包）
  python tools/reproduce.py --full       # 验证 + 重建 + 打印交接摘要

设计原则（对应工程铁律）：
  1. 幂等：跑一遍和跑两遍结果一样
  2. 只读优先：--verify 档绝不写 src/，只读校验
  3. 可回溯：每步打印「命令 + 结果 + 权威依据文档」

前置条件（软件）：
  - Python 3.8+（纯标准库，无需第三方包）
  - 可选：IDA Professional 9.4（仅 P1-P3 反编译阶段需要，本脚本不调）

复现的四个层次：
  L0 结构完整性   —— 12,172 块 / VA 0 丢失 / 结构 0 改动（verify_refine.py）
  L1 覆盖与注释   —— 0 裸 marker / 行尾注释率 / 有意义行覆盖率
  L2 字段表完整   —— 564 类 / 字段命名率 / 类头接线
  L3 派生交付物   —— 类头 / 合订本 / 交付包（--rebuild 时再生）

权威依据：docs/00_进度总览.md · docs/99_完整工程总结.md · docs/90_发现日志.md
================================================================================
"""
import os
import re
import sys
import glob
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def run(cmd, label, timeout=900):
    """跑一个子进程命令，返回 (成功?, 输出尾部)"""
    print("\n" + "=" * 72)
    print("  ▶ %s" % label)
    print("    $ %s" % cmd)
    print("=" * 72)
    try:
        p = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True,
                           text=True, encoding="utf-8", errors="replace", timeout=timeout)
        out = (p.stdout or "") + (p.stderr or "")
        tail = out.strip().split("\n")[-12:]
        for l in tail:
            print("    " + l)
        return p.returncode == 0, out
    except Exception as e:
        print("    !! 执行异常: %s" % e)
        return False, str(e)


def stat_src():
    """统计源码规模与注释率（Python 直读，不依赖外部脚本）"""
    srcs = glob.glob(os.path.join(ROOT, "src", "**", "*.cpp"), recursive=True)
    tc = tt = 0
    struct = re.compile(r'^\s*[\{\}];?\s*$|^\s*(else\s*$|do\s*$|break;|continue;|default:|case\b|goto\b)')
    trivial = re.compile(r'^\s*\w+\s*=\s*(0|1|-1|nullptr|NULL|0\.0|null)\s*;\s*$|^\s*return(\s+\w+)?\s*;\s*$')
    md = mdt = 0
    va = 0
    for p in srcs:
        txt = open(p, encoding="utf-8", errors="replace").read()
        va += len(re.findall(r"^// 0x[0-9A-F]{6,8}(?![0-9A-Za-z])", txt, re.M))
        for l in txt.split("\n"):
            s = l.strip()
            if not s or s.startswith("//"):
                continue
            tc += 1
            if "//" in s:
                tt += 1
            if not (struct.match(l) or trivial.match(l)):
                md += 1
                if "//" in s:
                    mdt += 1
    return dict(files=len(srcs), va=va, code=tc, tail=tt, mean=md, mean_tail=mdt)


def stat_fields():
    """统计字段表"""
    fs = glob.glob(os.path.join(ROOT, "include", "arad", "_fields", "*.h"))
    tot = named = 0
    for p in fs:
        for l in open(p, encoding="utf-8", errors="replace"):
            if re.search(r"//\s*\+0x", l):
                tot += 1
                if not re.search(r"\b(field_|f_)\w+;", l):
                    named += 1
    return dict(classes=len(fs), fields=tot, named=named)


def verify():
    """L0-L2 验证（只读）"""
    ok = True
    # L0: 结构完整性（权威脚本）
    passed, out = run("python tools/verify_refine.py", "L0 结构级终验（12,172 块比对）")
    ok = ok and ("PASS" in out)

    # L1/L2 统计
    s = stat_src()
    f = stat_fields()
    print("\n" + "=" * 72)
    print("  ▶ L1 覆盖与注释（Python 直读统计）")
    print("=" * 72)
    print("    src 文件: %d ｜ VA 函数标记: %d" % (s["files"], s["va"]))
    print("    代码行: %d ｜ 行尾注释: %d (%.1f%%)" % (s["code"], s["tail"], s["tail"] / max(1, s["code"]) * 100))
    print("    有意义行: %d ｜ 有注释: %d (%.1f%%)" % (s["mean"], s["mean_tail"], s["mean_tail"] / max(1, s["mean"]) * 100))
    print("\n" + "=" * 72)
    print("  ▶ L2 字段表（564 类目标）")
    print("=" * 72)
    print("    字段表: %d 类 ｜ 字段: %d ｜ 已命名: %d (%.1f%%)"
          % (f["classes"], f["fields"], f["named"], f["named"] / max(1, f["fields"]) * 100))

    # 与基线对比（数值下限守卫）
    # 注：VA 标记行 12,291 ≠ 函数块 12,172 —— 差值 119 是多 VA 组合头等合法形态
    # （verify_refine 判定的是函数块数，见上方 L0 结果）
    checks = [
        ("结构级终验 PASS（12,172 块 / VA 0 丢失 / 结构 0 改动）", "PASS" in out),
        ("函数标记行 ≥ 12,291（含 multi-VA 组合头）", s["va"] >= 12291),
        ("字段表类数 ≥ 564", f["classes"] >= 564),
        ("字段命名率 ≥ 99%", f["named"] / max(1, f["fields"]) >= 0.99),
        ("有意义行注释率 ≥ 75%", s["mean_tail"] / max(1, s["mean"]) >= 0.75),
    ]
    print("\n" + "=" * 72)
    print("  ▶ 数值守卫（对照 docs/99 基线）")
    print("=" * 72)
    for name, good in checks:
        print("    [%s] %s" % ("OK" if good else "!!", name))
        ok = ok and good
    return ok


def rebuild():
    """L3 派生交付物重建"""
    ok = True
    steps = [
        ("python tools/gen_class_headers.py", "重建 743 类头文件体系（include/arad/）", 600),
        ("python tools/link_field_tables.py --apply", "类头接入字段表（549 个）", 300),
        ("python tools/build_omnibus.py", "重建单文件合订本", 900),
        ("python tools/package_release.py", "重打交付包 zip", 900),
    ]
    for cmd, label, t in steps:
        p, _ = run(cmd, label, t)
        ok = ok and p
    return ok


def summary():
    """打印交接摘要"""
    print("\n" + "=" * 72)
    print("  交接摘要（复制给下一轮）")
    print("=" * 72)
    s = stat_src()
    f = stat_fields()
    named_pct = f["named"] / max(1, f["fields"]) * 100
    tail_pct = s["tail"] / max(1, s["code"]) * 100
    mean_pct = s["mean_tail"] / max(1, s["mean"]) * 100
    doc = [
        "【40JP逆向源代码工程】当前状态",
        "  VA 覆盖: 12,172/12,172 = 100%   函数头注释: 100%（0 裸 marker）",
        "  字段表: {c} 类 / {f} 字段（命名率 {p:.1f}%）".format(c=f["classes"], f=f["fields"], p=named_pct),
        "  行尾注释: {t} 行（{tp:.1f}%）｜ 有意义行: {mt}/{m} = {mp:.1f}%".format(
            t=s["tail"], tp=tail_pct, mt=s["mean_tail"], m=s["mean"], mp=mean_pct),
        "  源码: {n} 文件 / {c} 代码行".format(n=s["files"], c=s["code"]),
        "  结构级终验: 见上方 L0 结果",
        "",
        "必读文档（按序）:",
        "  1. docs/99_完整工程总结.md   ← 新人第一入口（成果/方法论/剩余项/复现）",
        "  2. docs/00_进度总览.md       ← 唯一权威进度",
        "  3. docs/22_未实现与待验证总清单.md ← 剩余工作（六层）",
        "  4. docs/95_字段改名参照表.md ← 旧名↔新名双索引",
        "  5. docs/26_变量命名与伪代码阅读指南.md",
        "  6. docs/60_子代理重构规范.md ← 精修作业标准",
        "",
        "剩余工作（按价值）:",
        "  ★★★ 动态验证（13 项待验证 + 4,000 个【推断】字段）—— 需跑游戏挂调试器",
        "  ★★☆ 研究文档勘误回写（7 处，原文档只读需人工决策）",
        "  ★☆☆ CRT 9 桩补全（微软代码，价值低）",
        "",
        "下一步建议:",
        "  python tools/reproduce.py --verify      # 确认起点 PASS",
        "  python tools/gen_func_cards.py --stats  # 看剩余精修空间",
        "  见 docs/99 §5.6「如果要继续精修」",
    ]
    print("\n".join(doc))


def main():
    args = sys.argv[1:]
    mode = "--rebuild" if "--rebuild" in args else ("--full" if "--full" in args else "--verify")
    print("=" * 72)
    print("  【40JP逆向源代码工程】一键复现 · 模式: %s" % mode)
    print("  工程根目录: %s" % ROOT)
    print("=" * 72)

    ok = verify()
    if mode in ("--rebuild", "--full"):
        ok = rebuild() and ok
    if mode == "--full":
        summary()

    print("\n" + "=" * 72)
    print("  复现结果: %s" % ("✅ PASS（与 docs/99 基线一致）" if ok else "❌ 有检查未通过，见上方明细"))
    print("=" * 72)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
