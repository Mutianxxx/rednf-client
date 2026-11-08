# -*- coding: utf-8 -*-
"""
类头文件生成器 —— 从 RTTI 层级数据 + 虚表槽位数据自动生成完整类头文件体系
输入: data/rtti_hierarchy.txt (743 类: TD/主虚表/基链/槽位数)
      data/class_method_slots.txt (97K 行槽位 dump: 类 -> 每槽函数地址)
输出: include/arad/*.h —— 每类一个头（按族分目录），含:
      - 继承声明（从基链还原）
      - 虚方法表（槽偏移 + 函数地址 + 已有语义名）
      - 关键字段注释（从 L1 精修层的 struct 定义摘录）
"""
import io, os, re, collections

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
OUT_BASE = os.path.join(ROOT, "include", "arad")

# ---------- 1. 载入 RTTI 层级 ----------
classes = {}   # name -> {vt, bases(list root->derived names), slots}
cur = None
for ln in io.open(os.path.join(ROOT, "data", "rtti_hierarchy.txt"), encoding="utf-8"):
    ln = ln.rstrip("\n")
    if ln.startswith("CLASS "):
        cur = {"name": ln[6:], "vt": None, "bases": [], "slots": 0}
    elif cur is not None and "TD=" in ln:
        m = re.search(r"primaryVT=(\w+)", ln)
        cur["vt"] = m.group(1) if m else None
        b = ln.split("bases(root->derived): ")
        if len(b) > 1:
            cur["bases"] = [x.strip() for x in b[1].split("<-")]
    elif cur is not None and "slots=" in ln:
        m = re.search(r"slots=(\d+)", ln)
        cur["slots"] = int(m.group(1)) if m else 0
        classes[cur["name"]] = cur
        cur = None

# ---------- 2. 载入虚表槽位 ----------
vtslots = collections.defaultdict(list)  # classname -> [(ofs, func_ea)]
cur = None
for ln in io.open(os.path.join(ROOT, "data", "class_method_slots.txt"), encoding="utf-8"):
    ln = ln.rstrip("\n")
    if ln.startswith("CLASS "):
        cur = ln[6:]
    elif cur and ln.startswith("  +"):
        m = re.match(r"  \+(\d+)\s+([0-9A-F]{8})", ln)
        if m:
            vtslots[cur].append((int(m.group(1)), int(m.group(2), 16)))

# ---------- 3. 从 L1 层摘录已知字段名（struct 定义逐行） ----------
known_fields = {}   # classname -> [field def lines]
for f in ["src/cnrd/CNRDObject.h", "src/cnrd/IRDCollisionObject.h", "src/cnrd/IRDActiveObject.h",
          "src/nengine/time_system.h", "src/nengine/camera_fx.h"]:
    p = os.path.join(ROOT, f)
    if not os.path.exists(p):
        continue
    txt = io.open(p, encoding="utf-8").read()
    for m in re.finditer(r"struct (\w+)(?:\s*:\s*(\w+))?\s*\{(.*?)\n\};", txt, re.S):
        nm, base, body = m.groups()
        known_fields[nm] = (base, body)

# ---------- 4. 头部注释中的语义名（从所有源码收集 类名__vmtN -> 注释语义） ----------
semantic = {}
for dirpath, _, files in os.walk(os.path.join(ROOT, "src")):
    for fn in files:
        if not fn.endswith(".cpp"):
            continue
        p = os.path.join(dirpath, fn)
        txt = io.open(p, encoding="utf-8", errors="replace").read()
        for m in re.finditer(r"//\s*0x([0-9A-F]{6})\s+(\w+__vmt[0-9A-F]+)\s*(?:——|--)?\s*(.{0,80})", txt):
            semantic[m.group(2)] = (int(m.group(1), 16), m.group(3).strip())

# ---------- 5. 生成头文件 ----------
def safe(s):
    return re.sub(r"[^A-Za-z0-9_]", "_", s)

def family_dir(name):
    if name.startswith("nengine__"): return "nengine"
    if name.startswith("std_") or name.startswith("_") or name.startswith("exception"): return "std"
    if name.startswith("IRD"): return "interface"
    if name.startswith("CNRD"): return "cnrd"
    if name.startswith("CN"): return "game"
    return "misc"

os.makedirs(OUT_BASE, exist_ok=True)
index = []
count = 0
for cname, info in sorted(classes.items()):
    fam = family_dir(cname)
    outdir = os.path.join(OUT_BASE, fam)
    os.makedirs(outdir, exist_ok=True)
    fname = safe(cname) + ".h"
    L = []
    L.append("// ============================================================")
    L.append("// 【40JP逆向源代码工程】include/arad/%s/%s" % (fam, fname))
    L.append("// 类: %s" % cname.replace("__", "::"))
    if info["vt"]:
        L.append("// 主虚表: 0x%s   槽位数: %d" % (info["vt"], info["slots"]))
    if len(info["bases"]) > 1:
        L.append("// 继承: %s" % " -> ".join(b.replace("__", "::") for b in info["bases"]))
    L.append("// 来源: RTTI 全表自动生成（data/rtti_hierarchy.txt + class_method_slots.txt）")
    L.append("// 说明: 虚表槽位为二进制实测地址；语义名来自历代精修层；字段见 L1 精修头文件")
    L.append("// ============================================================")
    L.append("#pragma once")
    L.append("#include \"../../common/arad_types.h\"")
    L.append("")
    # 基类（取链上最接近的已定义基）
    base = None
    for b in reversed(info["bases"][:-1]):   # 倒数第二个 = 直接基
        if b.startswith("std_") or b.startswith("_"):
            continue
        base = b
        break
    decl = "struct %s" % safe(cname)
    if base:
        decl += " : %s" % safe(base)
    L.append(decl + " {")
    # 已知字段（L1 摘录）
    kf = known_fields.get(cname)
    if kf:
        L.append("    // ---- 字段（L1 精修层摘录）----")
        for line in kf[1].split("\n"):
            L.append(line)
    # 虚表槽
    slots = vtslots.get(cname, [])
    if slots:
        L.append("    // ---- 虚方法表（槽偏移 -> 二进制地址）----")
        for ofs, ea in slots[:400]:
            sem = semantic.get("%s__vmt%X" % (cname, ofs))
            note = ""
            if sem:
                note = "  // %s" % sem[1][:70] if sem[1] else ""
            L.append("    // +0x%-4X  0x%08X%s" % (ofs, ea, note))
    L.append("};")
    io.open(os.path.join(outdir, fname), "w", encoding="utf-8").write("\n".join(L))
    index.append((fam, cname, fname, info["slots"]))
    count += 1

# ---------- 6. 总索引头 ----------
L = []
L.append("// ============================================================")
L.append("// 【40JP逆向源代码工程】include/arad/arad_all_classes.h")
L.append("// 全类总索引 —— 743 个 RTTI 类（自动生成）")
L.append("// ============================================================")
L.append("#pragma once")
for fam, cname, fname, nslots in sorted(index):
    L.append('#include "%s/%s"   // %s (%d 槽)' % (fam, fname, cname.replace("__", "::"), nslots))
io.open(os.path.join(OUT_BASE, "arad_all_classes.h"), "w", encoding="utf-8").write("\n".join(L))

print("生成类头文件:", count)
byfam = collections.Counter(f for f, _, _, _ in index)
for k, v in byfam.most_common():
    print("  %-12s %d" % (k, v))
