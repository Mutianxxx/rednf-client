# -*- coding: utf-8 -*-
"""
自研精修流水线：字符串证据自动标注
原理: 从 work/dump_*.txt 的函数体提取字符串字面量（.ani/.ptl/音效 TAG/协议串）与被调函数，
      生成 `// 证: ...` 注释行插入 VA 头之后 —— 纯二进制事实，零臆造。
      文件头按主代理的区块知识重写。
只插入整行注释，绝不触碰代码行。
"""
import io, os, re, sys, glob

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

# ---------- 载入全部 dump 素材（函数体来源） ----------
def load_dumps():
    bodies = {}
    for p in glob.glob(os.path.join(ROOT, "work", "dump_*.txt")):
        txt = io.open(p, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
        cur = None; body = []
        for line in txt.split("\n"):
            m = re.match(r"^// ([0-9A-F]{6,8})\s+(.*)$", line)
            if m and not line.startswith("// ==="):
                if cur: bodies[cur[0]] = body
                cur = (int(m.group(1), 16), m.group(2)); body = []
                continue
            if line.startswith("## "): cur = None; continue
            if cur: body.append(line)
        if cur: bodies[cur[0]] = body
    return bodies

BODIES = load_dumps()

STR_RE = re.compile(r'"([^"\n]{4,60})"')
CALL_RE = re.compile(r"\bsub_([0-9A-F]{6})\b")

def evidence(body_lines):
    strs, calls = [], []
    seen = set()
    for line in body_lines:
        for m in STR_RE.finditer(line):
            s = m.group(1)
            if s in seen: continue
            seen.add(s)
            # 过滤噪音
            if re.match(r"^[a-zA-Z0-9_ %\\.\\/:*-]+$", s) and not s.startswith("%") or \
               s.endswith(".ani") or s.endswith(".ptl") or s.endswith(".img") or s.endswith(".etc") or \
               s.endswith(".equ") or s.endswith(".tbl") or s.endswith(".trc") or s.endswith(".dmp"):
                strs.append(s[:44])
        for m in CALL_RE.finditer(line):
            calls.append(m.group(1))
    # 去重保序
    seen2 = set(); strs2 = []
    for s in strs:
        if s not in seen2:
            seen2.add(s); strs2.append(s)
    calls2 = []
    seen3 = set()
    for c in calls:
        if c not in seen3:
            seen3.add(c); calls2.append(c)
    return strs2[:5], calls2[:6]

def make_annotation(va):
    body = BODIES.get(va)
    if not body:
        return ["// 证: (dump 素材未含此函数体——审计补漏通道)"]
    strs, calls = evidence(body)
    parts = []
    if strs:
        parts.append("证: " + " | ".join('"%s"' % s for s in strs[:4]))
    if calls:
        parts.append("调: " + " ".join("sub_" + c for c in calls[:5]))
    if not parts:
        # 无字符串无调用的叶子函数
        nlines = len([l for l in body if l.strip()])
        return ["// 证: 叶子函数（%d 行，无外调无字符串）" % nlines]
    out = []
    for p in parts:
        for chunk in [p[i:i+100] for i in range(0, len(p), 100)]:
            out.append("// " + chunk)
    return out

# ---------- 目标文件配置（文件头知识来自本会话研究） ----------
FILES = [
    # (路径, dump来源描述, 模块定性, 区块)
    ("src/combat/swordman_skills.cpp", "0x5F0000-0x600000",
     "鬼剑士技能 PO/特效（0x5F 区）：GHOSTSLASH 蓄力/HardAttack/grandWave 三系波/IceWave/FireWave/"
     "GiveBlood 血爆/附魔 CONDITION_*/G_POISON——大剑士技能演出的资源调用层",
     [(0x5F0000, "§A 技能 PO 基础与波系"), (0x5F4000, "§B 蓄力与血系"), (0x5F8000, "§C 状态与buff")]),
    ("src/combat/fighter_skills.cpp", "0x5E0000-0x5F0000",
     "格斗家技能 PO/特效（0x5E 区）：GrabExplosion 三段爆/RoarStun/Suplex 翻摔/Thrust 上下刺/"
     "WarpCloud 瞬影/HandStrike/OneHandThrow/LaunchFrostHead/LaunchBlackCat/DisenchantCast",
     [(0x5E0000, "§A 技能基础与投技"), (0x5E4000, "§B 抓爆/吼 stun"), (0x5E8000, "§C Launch 系召唤")]),
    ("src/game/gunner_state.cpp", "0x4C0000-0x4D0000",
     "枪手武器状态机 + 大状态 tick（0x4C 区）：GUN_/BOWGUN_ 双枪系动作 TAG 全套（DRAW/IN/GRAB/LOAD/ROTATE）、"
     "MusketDust/WindmillDust 弹尘、GatlingShell 弹壳、CrossShoot/FireCharge 特效——"
     "docs/14 已定案 0x4C5250 大状态 tick 在本区（12 case 枚举：枪手技能执行器）",
     [(0x4C0000, "§A 武器状态 TAG 组"), (0x4C5000, "§B 大状态 tick 区(含 0x4C5250)"), (0x4CA000, "§C 弹尘与特效")]),
    ("src/game/creature/missing_monster.cpp", "0x590000-0x5E0000 补漏",
     "怪物 AI 补漏（0x59-0x5D 区审计追回 122 函数）：**含 vmt200 命中处理器覆写实本体**——"
     "0x598430（stdcall thunk 续接 sub_4DA3B0）与 0x5B4D90（宇宙鱼反击 proc：10%/15%/2% 随机 + "
     "CNStarFishKing/CNStarFishRukuku RTTI 分型，怪物 AI 代理定案）及 0x5B4820-0x5B6380 缺口区",
     [(0x590000, "§A 0x59 补漏"), (0x5A0000, "§B 0x5A 补漏"), (0x5B0000, "§C 0x5B 补漏(含宇宙鱼反击)"),
      (0x5C0000, "§D 0x5C 补漏"), (0x5D0000, "§E 0x5D 补漏")]),
    ("src/game/missing_combat_a.cpp", "0x420000-0x480000 补漏",
     "战斗/登录区补漏（0x42-0x47 区审计追回 63 函数）：播报层/Socket/世界地图/登录链散件",
     [(0x420000, "§A 0x42 补漏"), (0x440000, "§B 0x44 补漏"), (0x450000, "§C 0x45-0x47 补漏")]),
    ("src/combat/missing_skills.cpp", "0x5E0000-0x650000 补漏",
     "技能区补漏（0x5E-0x64 区审计追回 46 函数）",
     [(0x5E0000, "§A 0x5E 补漏"), (0x600000, "§B 0x60-0x64 补漏")]),
    ("src/game/ui/missing_ui_login.cpp", "0x540000-0x590000 补漏",
     "UI/登录区补漏（0x54-0x58 区审计追回 38 函数）",
     [(0x540000, "§A 0x54-0x56 补漏"), (0x570000, "§B 0x57-0x58 补漏")]),
    ("src/nengine/missing_engine.cpp", "0x400000-0x420000 补漏",
     "引擎区补漏（0x40-0x41 区审计追回 34 函数）",
     [(0x400000, "§A 0x40 补漏"), (0x410000, "§B 0x41 补漏")]),
    ("src/game/parsers/missing_parsers.cpp", "0x4F0000-0x510000 补漏",
     "解析器区补漏（0x4F-0x50 区审计追回 5 函数）",
     [(0x4F0000, "§A 全部")]),
]

HEADER_TMPL = """// ============================================================
// 【40JP逆向源代码工程】{rel}
// 模块: {desc}
// 来源: work/dump 素材  区块: {block}
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: {nfuncs}
// ============================================================"""

def process(rel_path, block_desc, sections):
    path = os.path.join(ROOT, rel_path)
    txt = io.open(path, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    lines = txt.split("\n")

    # 1) 统计 VA
    vas = [(i, m.group(1)) for i, m in
           [(i, re.match(r"^// 0x([0-9A-F]{6})", l)) for i, l in enumerate(lines)] if m]
    nfuncs = len(vas)

    # 2) 找到原文件头结束位置（第二个 "// ====" 行）
    header_end = 0
    seps = [i for i, l in enumerate(lines) if l.startswith("// ====")]
    if len(seps) >= 2:
        header_end = seps[1] + 1  # 保留到第二个分隔线（含）

    # 3) 新文件头
    # 区块范围: 从第一个与最后一个 VA 推断
    lo = int(vas[0][1], 16) if vas else 0
    hi = int(vas[-1][1], 16) + 1 if vas else 0
    new_header = HEADER_TMPL.format(
        rel=rel_path.replace("\\", "/"), desc=block_desc,
        block="0x%06X-0x%06X %s" % (lo, hi, sections[0][1] if sections else ""),
        nfuncs=nfuncs)

    # 4) 重建文件体：新头 + 分区横幅 + 带证据注释的函数
    out = new_header.split("\n")
    out.append("")
    # 分区横幅位置（按 VA 区间）
    sec_at = {}
    for slo, sdesc in sections:
        sec_at[slo] = sdesc

    i = header_end
    inserted_banner = set()
    while i < len(lines):
        line = lines[i]
        m = re.match(r"^// 0x([0-9A-F]{6})", line)
        if m:
            va = int(m.group(1), 16)
            # 分区横幅
            for slo, sdesc in sections:
                if va >= slo and slo not in inserted_banner:
                    out.append("// ============================================================")
                    out.append("// %s" % sdesc)
                    out.append("// ============================================================")
                    inserted_banner.add(slo)
            out.append(line)
            # 跳过包装线与既有注释（到第一个非注释行 = 函数签名）
            j = i + 1
            while j < len(lines) and (lines[j].startswith("//") or not lines[j].strip()):
                out.append(lines[j])
                j += 1
                if j < len(lines) and re.match(r"^// 0x[0-9A-F]{6}", lines[j]):
                    break
            # 插入证据注释（若该函数还没有 "证:" 注释）
            if not any("证:" in lines[k] for k in range(i, j)):
                for al in make_annotation(va):
                    out.append(al)
            i = j
            continue
        out.append(line)
        i += 1

    new_txt = "\n".join(out)
    # CRLF 归一（原文件多为 CRLF）
    if "\r\n" in txt and "\r\n" not in new_txt:
        new_txt = new_txt.replace("\n", "\r\n")
    io.open(path, "w", encoding="utf-8", newline="").write(new_txt)
    print("%-45s %4d funcs  头+证据完成" % (rel_path, nfuncs))
    return nfuncs

# bigfunc 专项：路标注释（case/switch/资源引用点）
def process_bigfuncs():
    files = sorted(glob.glob(os.path.join(ROOT, "src", "**", "bigfunc_*.cpp"), recursive=True))
    skip = os.path.join(ROOT, "src", "game", "bigfunc_4471E0_sub_4471E0.cpp")  # 已精修
    total = 0
    for p in files:
        if norm(p) == norm(skip):
            continue
        txt = io.open(p, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
        if "路标注释" in txt[:2000] or "证:" in txt[:3000]:
            # 已处理过（幂等）
            continue
        lines = txt.split("\n")
        vas = [i for i, l in enumerate(lines) if re.match(r"^// 0x[0-9A-F]{6}", l)]
        if not vas:
            continue
        va = int(re.match(r"^// 0x([0-9A-F]{6})", lines[vas[0]]).group(1), 16)
        body = BODIES.get(va, [])
        strs, calls = evidence(body)
        # 在文件头后插入路标头注
        seps = [i for i, l in enumerate(lines) if l.startswith("// ====")]
        he = seps[1] + 1 if len(seps) >= 2 else 0
        landmark = ["// ------------------------------------------------------------",
                    "// 路标注释（主代理自研流水线自动生成）：",
                    "//   函数体 %d 行；字符串证据 %d 条；外调 %d 个" % (len(body), len(strs), len(calls))]
        for s in strs[:8]:
            landmark.append('//   串: "%s"' % s)
        if calls:
            landmark.append("//   调: " + " ".join("sub_" + c for c in calls[:10]))
        # case 分支地图（switch 巨函数的路标）
        cases = [(i, l.strip()[:70]) for i, l in enumerate(lines) if re.match(r"\s*case 0x[0-9A-Fa-f]+:", l)]
        if cases:
            landmark.append("//   case 分支地图（共 %d 处）:" % len(cases))
            for i, cl in cases[:40]:
                landmark.append("//     L%d  %s" % (i + 1, cl))
        landmark.append("// ------------------------------------------------------------")
        new_lines = lines[:he] + landmark + lines[he:]
        new_txt = "\n".join(new_lines)
        if "\r\n" in txt and "\r\n" not in new_txt:
            new_txt = new_txt.replace("\n", "\r\n")
        io.open(p, "w", encoding="utf-8", newline="").write(new_txt)
        total += 1
        print("bigfunc %08X 路标完成 (%d case)" % (va, len(cases)))
    print("bigfunc 合计:", total)

if __name__ == "__main__":
    total = 0
    for rel, block, desc, secs in FILES:
        total += process(rel, block, secs)
    print("常规文件小计:", total)
    process_bigfuncs()
