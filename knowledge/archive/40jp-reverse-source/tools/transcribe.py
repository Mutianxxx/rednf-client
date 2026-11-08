# -*- coding: utf-8 -*-
"""
L2 转写引擎 —— 把 IDA 反编译 dump 清洗为规范源码文件
============================================================
输入: work/dump_*.txt (Hex-Rays 批量反编译输出)
输出: src/<模块>/<文件>.cpp —— 每函数带 `// 0xXXXXXX` VA 标记
质量声明: 本层为"转写层"(L2) —— 反编译输出的规范化重排(类型名清洗/格式统一/
VA 标记/文件分模块), 语义与 Hex-Rays 输出逐字对应。
精修层(L1, 人工语义命名/结构注释)见过往前沿文件(src/nengine, src/cnrd, docs/10-15)。
"""
import re, os, io, sys

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
WORK = os.path.join(ROOT, "work")

# 类型名清洗表: Hex-Rays → 标准 C++（长模式必须在前!）
TYPE_CLEAN = [
    (r"\bunsigned __int64\b", "uint64_t"),
    (r"\bunsigned __int32\b", "uint32_t"),
    (r"\bunsigned __int16\b", "uint16_t"),
    (r"\bunsigned __int8\b", "uint8_t"),
    (r"\bsigned __int64\b", "int64_t"),
    (r"\bsigned __int32\b", "int32_t"),
    (r"\bsigned __int16\b", "int16_t"),
    (r"\bsigned __int8\b", "int8_t"),
    (r"\b__int64\b", "int64_t"),
    (r"\b__int32\b", "int32_t"),
    (r"\b__int16\b", "int16_t"),
    (r"\b__int8\b", "int8_t"),
    # 兜底: 修复任何"unsigned intN_t"残形
    (r"\bunsigned int64_t\b", "uint64_t"),
    (r"\bunsigned int32_t\b", "uint32_t"),
    (r"\bunsigned int16_t\b", "uint16_t"),
    (r"\bunsigned int8_t\b", "uint8_t"),
    (r"\b_DWORD\b", "uint32_t"),
    (r"\b_BYTE\b", "uint8_t"),
    (r"\b_WORD\b", "uint16_t"),
    (r"\b_QWORD\b", "uint64_t"),
    (r"\b__thiscall\b", "/*thiscall*/"),
    (r"\b__stdcall\b", "/*stdcall*/"),
    (r"\b__cdecl\b", "/*cdecl*/"),
    (r"\b__fastcall\b", "/*fastcall*/"),
    (r"\b__userpurge\b", "/*userpurge*/"),
    (r"\b__usercall\b", "/*usercall*/"),
    (r"\b__noreturn\b", "/*noreturn*/"),
]

def clean_type(s: str) -> str:
    for pat, rep in TYPE_CLEAN:
        s = re.sub(pat, rep, s)
    return s

# 分区配置: (dump文件, 输出目录, [(输出文件名, (lo, hi)), ...], 模块描述)
PLAN = {
    "parsers": [
        (os.path.join(WORK, "dump_parsers.txt"), os.path.join(ROOT, "src", "game", "parsers"), [
            ("item_parser.cpp",        (0x4F0000, 0x4FC000), "物品 .eqp 定义解析器族"),
            ("monster_parser.cpp",     (0x4FC000, 0x50C000), "怪物/NPC/PassiveObject 定义解析器族"),
            ("attackinfo_parser.cpp",  (0x50C000, 0x510000), "攻击定义解析 / 脚本后端"),
        ]),
    ],
    "combat": [
        (os.path.join(WORK, "dump_combat_a.txt"), os.path.join(ROOT, "src", "game"), [
            ("broadcast_debug.cpp",   (0x420000, 0x440000), "播报层/调试输出/Socket 封装"),
            ("script_string.cpp",     (0x440000, 0x450000), "脚本字符串管理/元素/职业标签/战斗分发器"),
            ("worldmap_reward.cpp",   (0x450000, 0x460000), "世界地图/副本选择/奖励"),
            ("ui_icon_perf.cpp",      (0x460000, 0x470000), "UI图标/性能统计"),
            ("login_channel.cpp",     (0x470000, 0x480000), "登录/频道连接 CNEntranceChannel"),
        ]),
    ],
    "monster": [
        (os.path.join(WORK, "dump_monster_ai.txt"), os.path.join(ROOT, "src", "game", "creature"), [
            ("goblin_fox.cpp",        (0x590000, 0x5A0000), "怪物AI: 哥布林/狐狸/魔法师"),
            ("tau_golem.cpp",         (0x5A0000, 0x5B0000), "怪物AI: 牛头/魔像/飞龙"),
            ("dragonman.cpp",         (0x5B0000, 0x5C0000), "怪物AI: 龙人/信徒/机甲"),
            ("spider_trap.cpp",       (0x5C0000, 0x5D0000), "怪物AI: 蜘蛛/陷阱"),
            ("expeller_guard.cpp",    (0x5D0000, 0x5E0000), "怪物AI: 驱逐者/四属性守卫"),
        ]),
    ],
    "skills": [
        (os.path.join(WORK, "dump_skills.txt"), os.path.join(ROOT, "src", "combat"), [
            ("fighter_skills.cpp",    (0x5E0000, 0x5F0000), "格斗家技能"),
            ("swordman_skills.cpp",   (0x5F0000, 0x600000), "鬼剑士技能"),
            ("passive_object.cpp",    (0x600000, 0x620000), "PassiveObject 生成/召唤/精炼"),
            ("breakable_map.cpp",     (0x620000, 0x630000), "可破坏地图物件"),
        ]),
        (os.path.join(WORK, "dump_skills.txt"), os.path.join(ROOT, "src", "game", "ui"), [
            ("window_party.cpp",      (0x630000, 0x640000), "窗口UI: 组队/强化/赌博"),
            ("aura_create.cpp",       (0x640000, 0x650000), "气功光环/角色创建"),
        ]),
    ],
    "uilogin": [
        (os.path.join(WORK, "dump_ui_login.txt"), os.path.join(ROOT, "src", "game", "ui"), [
            ("trade_shop.cpp",        (0x540000, 0x550000), "摆摊/交易/世界地图UI"),
            ("cashshop.cpp",          (0x550000, 0x570000), "商城/邮件/频道信息"),
            ("http_item_info.cpp",    (0x570000, 0x580000), "HTTP客户端/物品详情"),
            ("char_server_info.cpp",  (0x580000, 0x590000), "角色数据/服务器信息"),
        ]),
    ],
    "engine": [
        (os.path.join(WORK, "dump_engine.txt"), os.path.join(ROOT, "src", "nengine"), [
            ("log_dump.cpp",          (0x400000, 0x410000), "日志/转储/崩溃报告"),
            ("gfx_texture.cpp",       (0x410000, 0x420000), "D3D纹理/图像包/字体"),
        ]),
    ],
    "misca": [
        (os.path.join(WORK, "dump_misc_a.txt"), os.path.join(ROOT, "src", "game"), [
            ("skill_load_tutorial.cpp", (0x480000, 0x490000), "技能加载/教程"),
            ("anim_parser.cpp",         (0x490000, 0x4A0000), ".ani 动画帧解析器 + CNRDObject 族"),
            ("rtti_core.cpp",           (0x4A0000, 0x4B0000), "RTTI 类方法密集区(战斗对象核心)"),
            ("equ_buff.cpp",            (0x4B0000, 0x4C0000), "装备.equ解析/Buff"),
            ("gunner_state.cpp",        (0x4C0000, 0x4D0000), "枪手武器状态机/大状态tick"),
            ("combat_core.cpp",         (0x4D0000, 0x4E0000), "ActiveObject战斗核心/怪物生成"),
            ("hiteff_monster.cpp",      (0x4E0000, 0x4F0000), "命中特效/怪物状态机"),
        ]),
    ],
    "miscb": [
        (os.path.join(WORK, "dump_misc_b.txt"), os.path.join(ROOT, "src", "game"), [
            ("po_effects.cpp",          (0x510000, 0x520000), "PassiveObject 通用特效"),
            ("pvp_ui.cpp",              (0x520000, 0x530000), "PVP接口/UI命令 + 观察者-装备族"),
            ("gunner_skills.cpp",       (0x530000, 0x540000), "枪手技能 PassiveObject"),
        ]),
    ],
    "tail": [
        (os.path.join(WORK, "dump_tail_a.txt"), os.path.join(ROOT, "src", "nengine"), [
            ("zlib_inflate.cpp",        (0x650000, 0x660000), "zlib 解压/内嵌浏览器/寻路"),
            ("sound_script.cpp",        (0x660000, 0x670000), "声音脚本 .str/PAK/XML 解析"),
        ]),
        (os.path.join(WORK, "dump_tail_b.txt"), os.path.join(ROOT, "src", "platform"), [
            ("crt_static.cpp",          (0x670000, 0x68A000), "MSVC 静态 CRT（计划内, 标准库替代）"),
        ]),
        (os.path.join(WORK, "dump_tail_c.txt"), os.path.join(ROOT, "src", "platform"), [
            ("d3d8_loader.cpp",         (0x68A000, 0x690000), "D3D8 加载层/数学库"),
            ("socket_ime.cpp",          (0x690000, 0x6A0000), "ISocket/IME/NCEdit"),
            ("code_tail.cpp",           (0x6A0000, 0x6C1000), "代码尾部/数据混区"),
        ]),
    ],
}

BLOCK_SEP = "// ============================================================"

def parse_dump(path):
    """解析 dump 为 [(va, name, body_lines)]"""
    txt = io.open(path, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    funcs = []
    cur = None
    for line in txt.split("\n"):
        if line == BLOCK_SEP:
            if cur:
                funcs.append(cur)
            cur = {"va": None, "name": "", "body": []}
            continue
        if cur is not None and cur["va"] is None:
            m = re.match(r"// ([0-9A-F]{6,8})\s+(.*)$", line)
            if m:
                cur["va"] = int(m.group(1), 16)
                cur["name"] = m.group(2).strip()
            else:
                # 头部注释行或 SKIPPED-BIG 等, 结束当前块
                cur = None
            continue
        if cur is not None:
            if line.startswith("## SKIPPED-BIG"):
                cur = None
                continue
            cur["body"].append(line)
    if cur and cur["va"]:
        funcs.append(cur)
    return [f for f in funcs if f["va"]]

def write_module(out_dir, fname, fdesc, funcs, part_name, lo=None, hi=None):
    os.makedirs(out_dir, exist_ok=True)
    out_path = os.path.join(out_dir, fname)
    L = []
    L.append("// ============================================================")
    L.append("// 【40JP逆向源代码工程】%s" % os.path.join(os.path.basename(out_dir), fname).replace("\\", "/"))
    L.append("// 模块: %s" % fdesc)
    L.append("// 来源: work/dump_%s.txt  区块: 0x%06X-0x%06X" % (part_name, lo or 0, hi or 0))
    L.append("// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),")
    L.append("//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15")
    L.append("// 函数数: %d" % len(funcs))
    L.append("// ============================================================")
    L.append("")
    L.append('#include "../../common/arad_types.h"')
    L.append("")
    for f in funcs:
        L.append("// ------------------------------------------------------------")
        L.append("// 0x%06X %s" % (f["va"], f["name"] if f["name"] else "sub_%06X" % f["va"]))
        L.append("// ------------------------------------------------------------")
        for bl in f["body"]:
            L.append(clean_type(bl))
        L.append("")
    io.open(out_path, "w", encoding="utf-8").write("\n".join(L))
    return len(funcs), out_path

def main():
    total = 0
    report = []
    only = sys.argv[1:] if len(sys.argv) > 1 else None
    for part, groups in PLAN.items():
        if only and part not in only:
            continue
        for dump_path, out_dir, files in groups:
            if not os.path.exists(dump_path):
                report.append("SKIP %s (dump missing: %s)" % (part, os.path.basename(dump_path)))
                continue
            funcs = parse_dump(dump_path)
            for fname, (lo, hi), fdesc in files:
                sub = [f for f in funcs if lo <= f["va"] < hi]
                if not sub:
                    # 守卫: 空产出告警（docs/22 §五 #2——dump 内容与 PLAN 区间错位时不再静默）
                    report.append("!! 守卫告警: %s/%s 区间 0x%X-0x%X 在 dump 中 0 个函数（dump 与 PLAN 错位？）"
                                  % (part, fname, lo, hi))
                    continue
                n, out_path = write_module(out_dir, fname, fdesc, sub, part, lo, hi)
                total += n
                report.append("OK %-60s %4d funcs" % (out_path.replace(ROOT + "\\", ""), n))
    report.append("TOTAL FUNCS WRITTEN: %d" % total)
    io.open(os.path.join(WORK, "transcribe_report.txt"), "w", encoding="utf-8").write("\n".join(report))
    print("\n".join(report))

if __name__ == "__main__":
    main()
