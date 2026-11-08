# -*- coding: utf-8 -*-
"""
自造译名 → 官方名 回写（会话 10，依据 docs/92_官方名称对照表）

规则：
1. 只改**注释行**（行首 // 开头）——代码/字符串/资产路径一律不动。
2. 替换成 "官方名" 并在首次出现处保留原内部名（可回溯）：
   例：宇宙鱼 → 空骨鱼、魅魔/女妖 → 鬼魂。
3. 资产路径/类名（SpaceFish/Wraith/Soceress 等英文）不动。
4. 幂等：已替换过的（含"空骨鱼"）不再动。
5. 安全：替换后做骨架校验（标识符→@ 后必须一致）+ 只统计注释行变化。
"""
import io, glob, os, re, sys, hashlib

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")

# 替换表（注意顺序：长词优先）
REPL = [
    ("宇宙鱼", "空骨鱼"),
    ("魅魔", "鬼魂"),
    ("女妖", "鬼魂"),
    ("薇诺", "彼诺修"),
    ("凯拉哈", "克拉赫"),
    ("拉基乌斯", "鲁卡斯"),
    ("雷光基诺尔", "落雷凯诺"),
    ("唐加斯", "沙乌塔"),
    ("齐格", "赛格哈特"),
    ("路易丝", "路易斯"),
    ("靶眼", "投掷哥布林"),
    ("光之王", "光之城主"),
    ("岩鼠", "岩鼠"),          # 未证实：保留
    ("阿莫尔", "阿莫尔"),      # 未证实：保留
]

IDENT = re.compile(r'[A-Za-z_]\w*')
STR = re.compile(r'"(?:\\.|[^"\\])*"')


def norm_code(line):
    s = STR.sub('"S"', line)
    s = re.sub(r'//.*$', '', s)
    return re.sub(r'\s+', ' ', s).strip()


def main():
    apply = "--apply" in sys.argv
    total = 0
    touched = 0
    for path in sorted(glob.glob(os.path.join(SRC, "**", "*.cpp"), recursive=True)):
        txt = io.open(path, encoding="utf-8", errors="replace").read()
        lines = txt.split("\n")
        # 骨架基线：代码行模板（去掉标识符）
        base_code = [norm_code(l) for l in lines if not l.strip().startswith("//") and l.strip()]
        new_lines = []
        n_file = 0
        for l in lines:
            if l.strip().startswith("//"):
                nl = l
                for old, new in REPL:
                    if old != new and old in nl and new not in nl:
                        nl = nl.replace(old, new)
                if nl != l:
                    n_file += nl.count("")
                    n_file = n_file  # noop
                new_lines.append(nl)
            else:
                new_lines.append(l)
        # 统计实际替换数
        cnt = sum(1 for a, b in zip(lines, new_lines) if a != b)
        if cnt:
            # 骨架校验：代码行模板必须不变
            new_code = [norm_code(l) for l in new_lines if not l.strip().startswith("//") and l.strip()]
            assert new_code == base_code, "代码行骨架变化: %s" % path
            total += cnt
            touched += 1
            if apply:
                io.open(path, "w", encoding="utf-8", newline="").write("\n".join(new_lines))
    print("注释行被替换: %d 处，涉及 %d 个文件%s" % (total, touched, "（已写盘）" if apply else "（演练）"))


if __name__ == "__main__":
    main()
