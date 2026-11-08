# -*- coding: utf-8 -*-
"""
合订本生成器 —— 把整个工程源码树合并为单文件交付版
输出: ARAD40JP_完整逆向源码合集.cpp
"""
import io, os, glob, re

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"
OUT = os.path.join(ROOT, "ARAD40JP_完整逆向源码合集.cpp")

# 分区顺序（按子系统逻辑组织，非字母序）
SECTIONS = [
    ("第一部分 · 工程说明与总目录", []),
    ("第二部分 · 基础设施：类型与时间系统", ["src/common/arad_types.h", "src/nengine/time_system.h", "src/nengine/time_system.cpp"]),
    ("第三部分 · 引擎层：镜头/演出/网络", ["src/nengine/camera_fx.h", "src/nengine/camera_fx.cpp", "src/nengine/net_socket.cpp", "src/nengine/log_dump.cpp", "src/nengine/gfx_texture.cpp", "src/nengine/zlib_inflate.cpp", "src/nengine/sound_script.cpp"]),
    ("第四部分 · 核心对象层（CNRDObject / Collision / Active / 装备）",
     ["src/cnrd/CNRDObject.h", "src/cnrd/CNRDObject.cpp",
      "src/cnrd/IRDCollisionObject.h", "src/cnrd/IRDCollisionObject.cpp",
      "src/cnrd/IRDActiveObject.h", "src/cnrd/IRDActiveObject.cpp",
      "src/cnrd/ActiveObjectEquipment.cpp"]),
    ("第五部分 · 游戏模块层：主模块与帧循环", ["src/game/module/CNMainGameModule.cpp"]),
    ("第六部分 · 战斗核心（命中链/伤害/特效）", ["src/game/combat_core.cpp", "src/game/hiteff_monster.cpp", "src/game/gunner_state.cpp"]),
    ("第七部分 · 数据解析器群", ["src/game/parsers/item_parser.cpp", "src/game/parsers/monster_parser.cpp", "src/game/parsers/attackinfo_parser.cpp"]),
    ("第八部分 · 战斗与技能", ["src/combat/fighter_skills.cpp", "src/combat/swordman_skills.cpp", "src/combat/passive_object.cpp", "src/combat/breakable_map.cpp", "src/combat/gunner_skills.cpp"]),
    ("第九部分 · 怪物 AI（五族）", ["src/game/creature/goblin_fox.cpp", "src/game/creature/tau_golem.cpp", "src/game/creature/dragonman.cpp", "src/game/creature/spider_trap.cpp", "src/game/creature/expeller_guard.cpp"]),
    ("第十部分 · UI 与登录链路", ["src/game/broadcast_debug.cpp", "src/game/script_string.cpp", "src/game/worldmap_reward.cpp", "src/game/ui_icon_perf.cpp", "src/game/login_channel.cpp",
      "src/game/ui/trade_shop.cpp", "src/game/ui/cashshop.cpp", "src/game/ui/http_item_info.cpp", "src/game/ui/char_server_info.cpp",
      "src/game/ui/window_party.cpp", "src/game/ui/aura_create.cpp"]),
    ("第十一部分 · 其余业务模块", ["src/game/skill_load_tutorial.cpp", "src/game/anim_parser.cpp", "src/game/rtti_core.cpp", "src/game/equ_buff.cpp", "src/game/po_effects.cpp", "src/game/pvp_ui.cpp"]),
    ("第十二部分 · 平台层（PAK/Socket/IME/D3D8）", ["src/platform/d3d8_loader.cpp", "src/platform/socket_ime.cpp", "src/platform/code_tail.cpp"]),
    ("第十三部分 · 巨型函数专项（14 个 >8KB 函数）", sorted(glob.glob(os.path.join(ROOT, "src", "game", "bigfunc_*.cpp"))) + sorted(glob.glob(os.path.join(ROOT, "src", "combat", "bigfunc_*.cpp")))),
    ("第十四部分 · 审计追补（缺口补漏函数）", sorted(glob.glob(os.path.join(ROOT, "src", "**", "missing_*.cpp"), recursive=True))),
]

def read(path):
    if not os.path.exists(path):
        return None
    return io.open(path, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")

# 统计
total_funcs = 0
total_lines = 0

buf = []
buf.append("// ############################################################################")
buf.append("// #")
buf.append("// #   ARAD.exe（DNF 2006-06-13 日服客户端）完整逆向源码合集")
buf.append("// #   版本: Ver. 200606130k0515 | 大小: 3,948,544 B | i386 | ImageBase 0x400000")
buf.append("// #")
buf.append("// #   本文件 = 全工程源码树的单文件合订本（自动生成）")
buf.append("// #   生成: 【40JP逆向源代码工程】tools/build_omnibus.py")
buf.append("// #   权威树: src/ + include/  |  进度与文档: docs/00_进度总览.md")
buf.append("// #")
buf.append("// #   覆盖: 12,172 / 12,172 个函数 = 100.000%（审计验证）")
buf.append("// #   分层: T1 精修 130 / T2 精修注释+证据标注 10,829 / T3 CRT 转写 1,334")
buf.append("// #")
buf.append("// #   ★ 新人导航（大白话）：docs/20_大白话总导读.md —— 先读它！")
buf.append("// #   ★ 按功能查函数：docs/21_系统速查手册.md —— 战斗/网络/UI/怪物…全部功能→地址")
buf.append("// #   ★ 一页速查：速查表.md（工程根目录）")
buf.append("// #")
buf.append("// #   读这份代码的三把钥匙：")
buf.append("// #   1. 每个函数头都有 // 0xXXXXXX —— 那是它在 exe 里的地址，可回 IDA 对照")
buf.append("// #   2. 函数体是反编译工具的忠实输出（v1/v2 是临时变量名），")
buf.append("// #      函数头注释才是'这段代码干什么'的人话翻译")
buf.append("// #   3. 想懂游戏架构先读 docs/20 §2（游戏客户端怎么工作的 5 分钟版）")
buf.append("// #")
buf.append("// ############################################################################")
buf.append("")
buf.append("// ===== 总目录 =====")
for i, (title, files) in enumerate(SECTIONS, 1):
    buf.append("//   %-52s %d 个文件" % (title, len(files)))
buf.append("")

for title, files in SECTIONS:
    buf.append("")
    buf.append("// ############################################################################")
    buf.append("// #  %s" % title)
    buf.append("// ############################################################################")
    buf.append("")
    for rel in files:
        # 相对路径可能已是绝对
        path = rel if os.path.isabs(rel) else os.path.join(ROOT, rel)
        txt = read(path)
        if txt is None:
            buf.append("// [缺失文件: %s]" % rel)
            continue
        nf = len(re.findall(r"^// 0x[0-9A-F]{6}", txt, re.M))
        nl = txt.count("\n") + 1
        total_funcs += nf
        total_lines += nl
        disp = rel.replace(ROOT + os.sep, "").replace("\\", "/")
        buf.append("// ---------------------------------------------------------------------------")
        buf.append("// ## 文件: %s   (%d 函数 / %d 行)" % (disp, nf, nl))
        buf.append("// ---------------------------------------------------------------------------")
        buf.append(txt)
        buf.append("")

io.open(OUT, "w", encoding="utf-8").write("\n".join(buf))
size = os.path.getsize(OUT)
print("合订本生成: %s" % OUT)
print("  文件数: %d" % sum(len(f) for _, f in SECTIONS))
print("  函数计数器合计: %d" % total_funcs)
print("  源码行数: %d" % total_lines)
print("  合订本大小: %.1f MB" % (size / 1024 / 1024))
