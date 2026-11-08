# -*- coding: utf-8 -*-
"""
【40JP逆向源代码工程】一键全流程脚本
====================================================================
干什么的：把"从 EXE 到完整源码工程"的全部步骤串起来，一条命令跑通。
用大白话说：这个脚本就是工厂流水线的总开关。

整个流水线分 7 个阶段（编号 P1-P7）：

  P1  函数普查     —— 问 IDA：这个 exe 里一共有多少个函数？都叫什么？
  P2  RTTI 命名    —— 从二进制里挖出"类名表"，给几千个函数起名字
  P3  批量反编译   —— 把全部函数的机器码翻译成类似 C 的代码（存到 work/dump_*.txt）
  P4  源码转写     —— 把反编译文本清洗成规范的 .cpp 源码（src/ 目录）
  P5  类头文件     —— 从类名表自动生成 743 个类的 .h 头文件（include/arad/）
  P6  证据标注     —— 给每个函数补上"它用了哪些资源/调了谁"的证据注释
  P7  交付打包     —— 全部源码合并成单文件合订本 + 打 zip 交付包

怎么用：
  python tools/run_all.py            # 跑 P4-P7（不需要 IDA，日常最常用）
  python tools/run_all.py --full     # 全部 7 个阶段（P1-P3 需要 IDA，见下）
  python tools/run_all.py --check    # 只做终验（检查函数体有没有被改坏）

关于 IDA（P1-P3）：
  IDA 是商业逆向软件，不能用命令行直接调 Python。
  需要手动跑这样的命令（每个阶段一条）：
    "G:\\Program Files\\IDA Professional 9.4\\idat.exe" -A -S"tools/idar_xxx.py" -L"日志" work\\ARAD_recon.i64
  详见 docs/60 和 tools/ 下各 idar_*.py 开头的注释。

注意事项（血泪教训，详见 docs/90）：
  1. IDA 运行中千万别 kill 进程，会留锁文件导致后续打不开
  2. 大函数（>8KB）反编译很慢，批量时会自动跳过（记在 SKIPPED-BIG 清单里）
  3. 所有脚本都是"幂等"的：跑一遍和跑两遍结果一样，放心重复执行
====================================================================
"""
import os
import sys
import subprocess
import glob

# 工程根目录（就是本脚本往上跳一级）
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# IDA 的安装位置（如果你机器上路径不同，改这里）
IDA_EXE = r"G:\Program Files\IDA Professional 9.4\idat.exe"
IDA_DB = os.path.join(ROOT, "work", "ARAD_recon.i64")


def run(desc, func):
    """跑一个阶段，打印开始/结束，出错不中断后面的阶段。"""
    print()
    print("=" * 68)
    print("  阶段: %s" % desc)
    print("=" * 68)
    try:
        func()
        print("  -> 完成")
    except Exception as e:
        print("  -> 失败: %s" % e)
        print("     （不影响后续阶段继续跑；修复后可单独重跑本阶段）")


def p1_census():
    """P1 函数普查：让 IDA 列出全部函数清单，存到 data/ida_all_functions.txt"""
    out = os.path.join(ROOT, "data", "ida_all_functions.txt")
    _ida_run(os.path.join(ROOT, "tools", "idar_export_funcs.py"))
    n = len(io_open(out).readlines()) if os.path.exists(out) else 0
    print("  全函数表: %d 个函数 -> data/ida_all_functions.txt" % n)


def p2_rtti():
    """P2 RTTI 命名：扫出全部类名和虚表，给函数起名（生成 data/rtti_*.txt）"""
    _ida_run(os.path.join(ROOT, "tools", "idar_rtti_map.py"))
    _ida_run(os.path.join(ROOT, "tools", "idar_rtti_hierarchy_names.py"))
    print("  产出: data/rtti_hierarchy.txt（743 类）+ data/class_method_slots.txt（虚表槽位）")


def p3_dump():
    """P3 批量反编译：把全部函数翻译成 C 风格文本（work/dump_*.txt）"""
    # 分区表见 tools/idar_bulk_dump2.py 顶部 CONFIG；每区一条 IDA 命令
    parts = ["parsers", "engine", "combat", "misca", "miscb", "uilogin",
             "monster", "skills", "tail_a", "tail_b", "tail_c"]
    for part in parts:
        print("  反编译分区: %s" % part)
        _ida_run_env(os.path.join(ROOT, "tools", "idar_bulk_dump2.py"),
                     {"DUMP_PARTS": part})
    print("  巨型函数专项（>8KB 的 14 个，单独跑防止卡死）:")
    for va in ["4471E0", "4ABE10", "4C5250", "4C9950", "510F30", "51BA00",
               "53A220", "57A980", "583B90", "5E1000", "5E78C0", "5EA970",
               "5F10C0", "5F39F0"]:
        _ida_run_env(os.path.join(ROOT, "tools", "idar_bigfuncs.py"), {"BIGVA": va})


def p4_transcribe():
    """P4 源码转写：dump 文本 -> src/ 的规范 .cpp 文件"""
    _py(os.path.join(ROOT, "tools", "transcribe.py"))
    _py(os.path.join(ROOT, "tools", "transcribe_missing.py"))
    print("  产出: src/ 全部 .cpp（每函数带 // 0x地址 标记）")


def p5_headers():
    """P5 类头文件：从 RTTI 数据生成 743 个类的 .h（include/arad/）"""
    _py(os.path.join(ROOT, "tools", "gen_class_headers.py"))


def p6_annotate():
    """P6 证据标注：给每个函数补"用了什么资源/调了谁"的注释"""
    _py(os.path.join(ROOT, "tools", "annotate_evidence.py"))


def p7_package():
    """P7 交付打包：合订本 + zip"""
    _py(os.path.join(ROOT, "tools", "build_omnibus.py"))
    # zip 打包逻辑内联在这里（3 行核心代码，不单独建脚本）
    import zipfile
    out = os.path.join(os.path.dirname(ROOT), "40JP逆向源代码工程_完整交付包.zip")
    count = 0
    with zipfile.ZipFile(out, "w", zipfile.ZIP_DEFLATED, compresslevel=6) as z:
        for f in ["README.md", "ARAD40JP_完整逆向源码合集.cpp"]:
            p = os.path.join(ROOT, f)
            if os.path.exists(p):
                z.write(p, os.path.join("40JP逆向源代码工程", f)); count += 1
        for d in ["docs", "src", "include", "data", "tools"]:
            for dp, _, fs in os.walk(os.path.join(ROOT, d)):
                for fn in fs:
                    p = os.path.join(dp, fn)
                    z.write(p, os.path.join("40JP逆向源代码工程",
                                            os.path.relpath(p, ROOT))); count += 1
    print("  交付包: %d 文件 / %.1f MB -> %s" % (count, os.path.getsize(out) / 1048576, out))


def check():
    """终验：对比精修前备份，确认函数体没被改坏（语义级零改动）"""
    _py(os.path.join(ROOT, "tools", "verify_refine.py"))


# ---------------- 底层工具函数（不用看） ----------------
def io_open(p):
    import io
    return io.open(p, encoding="utf-8", errors="replace")


def _py(script):
    print("  运行: python %s" % os.path.basename(script))
    r = subprocess.run([sys.executable, script], cwd=ROOT,
                       capture_output=True, text=True, timeout=1800)
    tail = (r.stdout or "").strip().split("\n")[-3:]
    for t in tail:
        print("    " + t)
    if r.returncode != 0:
        print("    [stderr] " + (r.stderr or "")[-300:])


def _ida_run(script):
    if not os.path.exists(IDA_EXE):
        print("    [跳过] IDA 不在 %s —— 手动执行见脚本头注释" % IDA_EXE)
        return
    log = os.path.join(ROOT, "work", "run_all_ida.log")
    subprocess.run([IDA_EXE, "-A", "-S%s" % script, "-L%s" % log, IDA_DB],
                   timeout=1800)


def _ida_run_env(script, env):
    e = dict(os.environ); e.update(env)
    if not os.path.exists(IDA_EXE):
        print("    [跳过] IDA 不可用（env=%s）" % env)
        return
    log = os.path.join(ROOT, "work", "run_all_ida.log")
    subprocess.run([IDA_EXE, "-A", "-S%s" % script, "-L%s" % log, IDA_DB],
                   env=e, timeout=1800)


if __name__ == "__main__":
    arg = sys.argv[1] if len(sys.argv) > 1 else ""
    print("【40JP逆向源代码工程】一键全流程  根目录: %s" % ROOT)
    if arg == "--full":
        run("P1 函数普查", p1_census)
        run("P2 RTTI 命名", p2_rtti)
        run("P3 批量反编译", p3_dump)
    if arg == "--check":
        run("终验", check)
        sys.exit(0)
    run("P4 源码转写", p4_transcribe)
    run("P5 类头文件", p5_headers)
    run("P6 证据标注", p6_annotate)
    run("P7 交付打包", p7_package)
    print()
    print("全部完成。交付物：")
    print("  - ARAD40JP_完整逆向源码合集.cpp（单文件合订本）")
    print("  - ../40JP逆向源代码工程_完整交付包.zip")
    print("  - docs/20_大白话总导读.md <- 新人从这里开始读")
