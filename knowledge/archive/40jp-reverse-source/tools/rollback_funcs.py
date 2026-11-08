# -*- coding: utf-8 -*-
"""
违规函数回滚（会话 10）：按 VA 把当前文件中的函数块整体替换为
work/backup_s10_pre（会话 10 开始时快照）的版本。

函数块定义：VA marker 行起，到下一个 VA marker 行前（含头注释/签名/函数体）。
从后往前替换，行号不失效。

用法：python tools/rollback_funcs.py <src相对路径> VA1 VA2 ...
例：  python tools/rollback_funcs.py game/creature/goblin_fox.cpp 5908C0 5908E0
"""
import io, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = os.path.join(ROOT, "work", "backup_s10_pre")
VA_HEAD = re.compile(r"^// 0x([0-9A-F]{6})(?![0-9A-Za-z])")


def load_blocks(path):
    txt = io.open(path, encoding="utf-8", errors="replace").read()
    lines = txt.split("\n")
    marks = []
    for i, l in enumerate(lines):
        m = VA_HEAD.match(l)
        if m:
            marks.append((int(m.group(1), 16), i))
    out = {}
    for k, (va, i) in enumerate(marks):
        end = marks[k + 1][1] if k + 1 < len(marks) else len(lines)
        out[va] = (i, end)
    return lines, out


def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    vas = [int(v, 16) for v in sys.argv[2:]]
    cur_path = os.path.join(ROOT, "src", rel)
    bak_path = os.path.join(BASE, rel)
    if not os.path.isfile(bak_path):
        print("FAIL 备份不存在: %s" % bak_path)
        sys.exit(1)
    cur_lines, cur_blocks = load_blocks(cur_path)
    bak_lines, bak_blocks = load_blocks(bak_path)
    done = 0
    for va in sorted(vas, reverse=True):
        if va not in cur_blocks:
            print("SKIP 当前文件无 VA %08X" % va)
            continue
        if va not in bak_blocks:
            print("SKIP 备份无 VA %08X" % va)
            continue
        cs, ce = cur_blocks[va]
        bs, be = bak_blocks[va]
        cur_lines[cs:ce] = bak_lines[bs:be]
        done += 1
        print("回滚 %08X (行 %d-%d)" % (va, cs + 1, ce))
    io.open(cur_path, "w", encoding="utf-8", newline="").write("\n".join(cur_lines))
    print("完成: %d/%d 个函数已回滚到会话10起点快照" % (done, len(vas)))


if __name__ == "__main__":
    main()
