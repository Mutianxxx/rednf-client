# -*- coding: utf-8 -*-
"""
字段候选表 → struct 头文件骨架（会话 11）

把 data/class_fields/<类>.txt 的候选字段（偏移/类型/访问次数）渲染成
C struct 骨架，供子代理/人工补充语义名。生成到 include/arad/_fields/<类>.h。

用法:
  python tools/gen_field_struct.py --class CNFighter
  python tools/gen_field_struct.py --top 60        # 字段最多的 60 类
  python tools/gen_field_struct.py --all
"""
import io, os, re, sys, glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CF = os.path.join(ROOT, "data", "class_fields")
OUT = os.path.join(ROOT, "include", "arad", "_fields")

C_TYPES = {"uint32_t": "unsigned int", "uint16_t": "unsigned short", "uint8_t": "unsigned char",
           "int": "int", "char": "char", "float": "float", "double": "double",
           "BYTE": "unsigned char", "WORD": "unsigned short", "DWORD": "unsigned int",
           "short": "short", "size_t": "unsigned int", "void": "void *"}


def parse_card(path):
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    head = lines[0]
    m = re.match(r"CLASS (\S+)\s+slots=(\d+)\s+fields_candidate=(\d+)", head)
    name = m.group(1).replace(".?AV", "").replace("@@", "") if m else os.path.basename(path)[:-4]
    slots = int(m.group(2)) if m else 0
    rows = []
    for l in lines:
        mm = re.match(r"\+0x([0-9A-Fa-f]{4})\s+(\w+)\s+(\d+)\s+([0-9A-Fa-f]{8})\s+(.*)", l)
        if mm:
            rows.append((int(mm.group(1), 16), mm.group(2), int(mm.group(3)), mm.group(4), mm.group(5)))
    return name, slots, rows


def render_struct(name, slots, rows):
    out = []
    out.append("// ============================================================")
    out.append("// 【40JP逆向源代码工程】字段候选表（会话 11 半自动还原）")
    out.append("// 类: %s   主虚表槽位数: %d   候选字段: %d" % (name, slots, len(rows)))
    out.append("// 来源: tools/recover_fields.py（类槽位函数 this+N 聚合）")
    out.append("// 说明: 偏移与类型为二进制直证；语义名待补（推断字段标【推断】）")
    out.append("// ============================================================")
    out.append("#ifndef ARAD40JP_FIELDS_%s" % re.sub(r"\W", "_", name).upper())
    out.append("#define ARAD40JP_FIELDS_%s" % re.sub(r"\W", "_", name).upper())
    out.append("")
    out.append("#include <stdint.h>")
    out.append("")
    out.append("#pragma pack(push, 1)")
    out.append("struct %s_Fields {" % name)
    cur = 0
    for off, typ, cnt, sva, ev in rows:
        if off > cur:
            out.append("    unsigned char _unused_%04X[%d]; // +0x%04X..0x%04X 未观测" % (cur, off - cur, cur, off - 1))
            cur = off
        ct = C_TYPES.get(typ, "unsigned int")
        w = {"unsigned char": 1, "char": 1, "unsigned short": 2, "short": 2,
             "unsigned int": 4, "int": 4, "float": 4, "unsigned long": 4, "void *": 4}.get(ct, 4)
        out.append("    %-16s f_%04X;  // +0x%04X x%-3d va=%s  %s" % (ct, off, off, cnt, sva, ev[:60]))
        cur = off + w
    out.append("};")
    out.append("#pragma pack(pop)")
    out.append("")
    out.append("#endif")
    return "\n".join(out)


def main():
    args = sys.argv[1:]
    os.makedirs(OUT, exist_ok=True)
    cards = sorted(glob.glob(os.path.join(CF, "*.txt")))
    if "--class" in args:
        key = args[args.index("--class") + 1]
        cards = [c for c in cards if key.lower() in os.path.basename(c).lower()]
    elif "--top" in args:
        n = int(args[args.index("--top") + 1])
        cards = sorted(cards, key=lambda c: -len(parse_card(c)[2]))[:n]
    elif "--all" not in args:
        print("用法: --class X | --top N | --all"); return
    done = 0
    for c in cards:
        name, slots, rows = parse_card(c)
        if not rows:
            continue
        txt = render_struct(name, slots, rows)
        io.open(os.path.join(OUT, name + ".h"), "w", encoding="utf-8").write(txt)
        done += 1
    print("已生成 struct 骨架:", done, "->", OUT)


if __name__ == "__main__":
    main()
