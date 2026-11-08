# -*- coding: utf-8 -*-
"""
package_release.py —— 一键打包交付 zip（含分类）

打包范围（7 大类，见 目录分类说明.md）：
  1. 顶层入口：README.md / 速查表.md / 目录分类说明.md
  2. docs/        大白话文档区
  3. src/         还原源代码（6 分层 77 文件）
  4. include/     类库头文件（743 类 + 总索引）
  5. tools/       工具箱（IDA 批处理 + Python 流水线 + 资源格式参考实现）
  6. data/        逆向数据档案
  7. ARAD40JP_完整逆向源码合集.cpp  单文件合订本
  8. work/        过程存档（备份/侦察证据/原始 dump/日志）

排除（编译缓存与可再生派生库）：
  - __pycache__/ 与 *.pyc        （Python 编译缓存）
  - *.i64 / *.id0 / *.id1 / *.nam / *.til  （IDA 派生工作库，母本在
    DfoVibration_OLD_40JP\\work\\ida\\ARAD_hitstop.i64，需要时重拷）
  - .tmp 中间文件

用法：
  python tools/package_release.py                # 打包到 E:\\DOF LX\\40JP逆向源代码工程_完整交付包.zip
  python tools/package_release.py --out 路径.zip  # 指定输出
"""
import os
import sys
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))  # 工程根
DEFAULT_OUT = os.path.join(os.path.dirname(ROOT), "40JP逆向源代码工程_完整交付包.zip")
TOP = "【40JP逆向源代码工程】"  # zip 内顶层目录名

# 顶层收录项（目录整体收录；文件单列）
INCLUDE_DIRS = ["docs", "src", "include", "tools", "data", "work"]
INCLUDE_FILES = ["README.md", "速查表.md", "目录分类说明.md",
                 "ARAD40JP_完整逆向源码合集.cpp"]

# 排除模式：编译缓存 / IDA 派生库 / 临时文件
# func_cards = 会话 10 精修流水线的工作卡（7 千个小文件，可随时用
# tools/gen_func_cards.py 再生，不进交付包）；fld_host_classify = 会话 14 的
# 宿主类型判定中间产物（可随时用 tools/std_container_semantics.py --scan 再生）
EXCLUDE_DIRS = {"__pycache__", "func_cards", "fld_host_classify", "img_export"}
EXCLUDE_EXT = {".pyc", ".i64", ".id0", ".id1", ".nam", ".til", ".tmp"}


def is_excluded(name: str) -> bool:
    return os.path.splitext(name)[1].lower() in EXCLUDE_EXT


def collect_files():
    """按分类收集待打包文件，返回 [(绝对路径, zip内路径)]。"""
    items = []
    for f in INCLUDE_FILES:
        p = os.path.join(ROOT, f)
        if not os.path.isfile(p):
            print(f"[警告] 顶层文件缺失: {f}")
            continue
        items.append((p, f"{TOP}/{f}"))
    for d in INCLUDE_DIRS:
        base = os.path.join(ROOT, d)
        if not os.path.isdir(base):
            print(f"[警告] 目录缺失: {d}/")
            continue
        for dirpath, dirnames, filenames in os.walk(base):
            dirnames[:] = [x for x in dirnames if x not in EXCLUDE_DIRS]
            for fn in sorted(filenames):
                if is_excluded(fn):
                    continue
                p = os.path.join(dirpath, fn)
                arc = f"{TOP}/{d}/{os.path.relpath(p, base).replace(os.sep, '/')}"
                items.append((p, arc))
    return items


def main():
    out = sys.argv[sys.argv.index("--out") + 1] if "--out" in sys.argv else DEFAULT_OUT
    items = collect_files()
    tmp = out + ".tmp"
    total_in = 0
    with zipfile.ZipFile(tmp, "w", zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        for p, arc in items:
            z.write(p, arc)
            total_in += os.path.getsize(p)
    if os.path.exists(out):  # 覆盖旧包（临时文件写完整后再替换，防中断出半包）
        os.remove(out)
    os.replace(tmp, out)

    n = len(items)
    print(f"打包完成: {out}")
    print(f"  文件数 : {n}")
    print(f"  原始   : {total_in/1024/1024:.1f} MB")
    print(f"  压缩后 : {os.path.getsize(out)/1024/1024:.1f} MB")
    # 分类统计
    stat = {}
    for _, arc in items:
        key = arc.split("/")[1] if "/" in arc else "(顶层)"
        stat[key] = stat.get(key, 0) + 1
    print("  分类   : " + ", ".join(f"{k} {v}" for k, v in sorted(stat.items())))


if __name__ == "__main__":
    main()
