"""Rebuild plan indexes from explicit decisions and the read-only research catalog.

This generates documentation metadata only. It never scans frozen GBA assets,
changes game code, or treats catalog coverage as implemented gameplay.
"""
from pathlib import Path
import hashlib
import json

PLAN = Path(__file__).resolve().parents[1]
WORKSPACE = PLAN.parent
VERSION = "v1.1"


def write(name, obj):
    path = PLAN / "appendices" / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(obj, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def doc(prefix):
    matches = list(PLAN.glob(prefix + "-*.md"))
    if len(matches) != 1:
        raise ValueError((prefix, matches))
    return matches[0].relative_to(PLAN).as_posix()


TASKS = [
    ("P00", "方案与证据基线", [], ["00", "01", "13"], ["A-DOC"]),
    ("P01", "内容配置与身份", ["P00"], ["01", "02"], ["A-SOURCE", "A-ARCH"]),
    ("P02", "全量来源语义与能力", ["P01"], ["02"], ["A-SOURCE", "A-WORLD"]),
    ("P03", "模拟输入实体", ["P01"], ["03"], ["A-TIME", "A-ARCH"]),
    ("P04", "事务与存档基础", ["P01", "P03"], ["10"], ["A-SAVE"]),
    ("P05", "成长属性装备", ["P02", "P04"], ["05"], ["A-STATS", "A-CHAR"]),
    ("P06", "行为与脚本宿主", ["P02", "P03"], ["04", "07"], ["A-SCRIPT"]),
    ("P07", "通用战斗与技能事务", ["P05", "P06"], ["04", "05"], ["A-HIT", "A-STATS"]),
    ("P08", "鬼剑士迁移及完整分支", ["P07"], ["04"], ["A-CHAR"]),
    ("P09", "女格斗男法师样板", ["P07"], ["04"], ["A-CHAR", "A-SCRIPT"]),
    ("P10", "男女枪手", ["P07", "P09"], ["04"], ["A-CHAR"]),
    ("P11", "女法师圣职者", ["P07", "P09"], ["04", "07"], ["A-CHAR", "A-ENTITY"]),
    ("P12", "暗夜男格斗黑暗武士", ["P07", "P09"], ["04"], ["A-CHAR"]),
    ("P13", "通用世界与怪物", ["P02", "P06", "P07"], ["06", "07"], ["A-WORLD", "A-ENTITY"]),
    ("P14", "物件粒子与环境", ["P04", "P06", "P13"], ["07"], ["A-ENTITY", "A-SAVE"]),
    ("P15", "NPC任务经济", ["P04", "P05", "P13"], ["08"], ["A-QUEST", "A-ECONOMY"]),
    ("P16", "必要UI音频", ["P02", "P05", "P15"], ["09"], ["A-UI", "A-AUDIO"]),
    ("P17", "Beta工具", ["P03", "P05"], ["11"], ["A-DEBUG"]),
    ("P18", "完整审计与流程", [f"P{i:02d}" for i in range(8, 18)], ["13"], ["A-FLOW", "A-CHAR", "A-SAVE"]),
    ("P19", "独立候选与发布", ["P18"], ["12"], ["A-RELEASE", "A-PORT"]),
]

MODULES = {
    "source-build": (["00", "02", "12"], ["P01", "P02", "P19"], "required", "来源、兼容与构建是所有内容的基础"),
    "assets-rendering": (["02", "05", "09"], ["P02", "P05", "P16"], "required", "源资源与人物外观必须实际消费"),
    "audio-timing": (["03", "09"], ["P03", "P16"], "required", "声音事件和独立时间域"),
    "input-movement": (["03"], ["P03", "P07"], "required", "正常输入与移动是可玩门槛"),
    "classes-progression": (["04", "05", "10"], ["P05", "P08", "P09", "P10", "P11", "P12"], "required", "十非Creator职业及实际分支完整；Creator只延期运行时"),
    "skills-controllers": (["03", "04", "05"], ["P06", "P07", "P08", "P09", "P10", "P11", "P12"], "required", "主动被动及其依赖不能用禁用绕过最终门槛"),
    "combat-formulas": (["05"], ["P05", "P07"], "required", "成长、装备、攻速与完整伤害阶段"),
    "combat-status": (["03", "05", "07"], ["P07", "P13"], "required", "保护、异常、抓取、死亡复活与清理"),
    "world-topology": (["06"], ["P13"], "required", "按能力开放全部区域；合法候选完整预检"),
    "collision-objects": (["06", "07"], ["P13", "P14"], "required", "通行与XYZ受击分开，物件payload闭环"),
    "monster-ai": (["07"], ["P06", "P13"], "required", "来源行为与关键首领阶段完整"),
    "npc-dialogue": (["08", "09"], ["P15", "P16"], "required", "真实交互与业务服务"),
    "quests": (["08"], ["P15", "P18"], "required", "全部分类，必需普通/转职/觉醒任务链完整"),
    "items-equipment": (["05", "08"], ["P05", "P15"], "required", "实例、资格、属性、外观及物品事务"),
    "economy-drops": (["08", "10"], ["P04", "P15"], "required", "买卖维修掉落结算及幂等"),
    "crafting": (["05", "08"], ["P05", "P15"], "conditional", "源支持的本地加工按能力；必需成长/任务依赖提升为required，不虚构远程业务"),
    "companions": (["04", "07", "08"], ["P07", "P11", "P13", "P15"], "conditional", "技能召唤/APC必需；独立宠物按实际字段和本地能力"),
    "ui-localization": (["09", "11"], ["P16", "P17"], "required", "必要业务与中文输入必需，精细全UI像素复现暂缓"),
    "persistence": (["10"], ["P04", "P18"], "required", "同代保存、恢复和迁移"),
    "services": (["01", "08", "10"], ["P04", "P15"], "deferred_boundary", "实现LocalGameServices；远程登录/组队协议不在本轮，接口与来源保留"),
    "social": (["08", "09"], ["P15", "P16"], "deferred_boundary", "好友公会邮件拍卖等远程业务禁用/诊断，不伪可用"),
    "pvp": (["02", "06", "08"], ["P02", "P13", "P15"], "conditional", "模式数据隔离；竞技远程服务不实现，特殊单机模式仅能力完整时开放"),
    "events-cash": (["08", "10"], ["P04", "P15"], "conditional", "本地周期/时效明确建模；在线活动和真实支付延期边界"),
    "platform-performance": (["01", "12"], ["P03", "P19"], "required", "本轮Windows，未来平台数据完整保留，不宣称其他端通过"),
    "verification": (["13"], ["P18", "P19"], "required", "来源/实现/自动/用户/原版对照分别验证"),
}

REQUIREMENTS = [
    ("U01", "独立客户端基于PVF和1031资源", ["00", "01", "02"], ["P01", "P02"], ["A-SOURCE", "A-RELEASE"]),
    ("U02", "通用逻辑与特殊处理登记", ["01", "02", "04", "06"], ["P02", "P06", "P13"], ["A-ARCH", "A-CHAR"]),
    ("U03", "地图UI优先来源证据渲染", ["02", "06", "09"], ["P02", "P13", "P16"], ["A-SOURCE", "A-UI"]),
    ("U04", "更换PVF及资源版本兼容", ["02", "10", "12"], ["P01", "P02", "P04"], ["A-SOURCE", "A-SAVE"]),
    ("U05", "核心完整且前台由用户测试", ["00", "13"], ["P18", "P19"], ["A-FLOW", "A-DOC"]),
    ("U06", "明确版本完成未完成及后续适配", ["00", "12", "13"], ["P00", "P18", "P19"], ["A-RELEASE", "A-DOC"]),
    ("U07", "v0.x beta独立测试窗口", ["11", "12"], ["P17", "P19"], ["A-DEBUG", "A-RELEASE"]),
    ("U08", "等级属性装备攻速伤害通用计算", ["04", "05"], ["P05", "P07"], ["A-STATS", "A-HIT"]),
    ("U09", "多种推理可切换及反馈", ["05", "11"], ["P05", "P07", "P17"], ["A-DEBUG", "A-STATS"]),
    ("U10", "允许有依据经验推理推进", ["00", "04", "11"], ["P00", "P06", "P17"], ["A-DOC", "A-SCRIPT"]),
    ("U11", "可玩商店交互战斗副本任务", ["04", "05", "06", "07", "08", "10", "13"], ["P07", "P13", "P14", "P15", "P18"], ["A-FLOW", "A-QUEST", "A-ECONOMY"]),
    ("C01", "保留十非Creator完整职业最终门槛", ["00", "04", "13"], ["P08", "P09", "P10", "P11", "P12", "P18"], ["A-CHAR", "A-FLOW"]),
    ("C02", "按能力开放全部区域", ["02", "06", "13"], ["P02", "P13"], ["A-WORLD"]),
    ("C03", "技能装备优先精细UI暂缓", ["00", "09", "13"], ["P05", "P07", "P16"], ["A-CHAR", "A-UI"]),
    ("C04", "完整方案分模块落盘且查漏补缺含伪代码", ["00", "01", "13"], ["P00"], ["A-DOC"]),
    ("C05", "保留原始资料及多端限制D盘产物", ["00", "12"], ["P00", "P19"], ["A-PORT", "A-RELEASE"]),
]

EVIDENCE = [
    ("E01", "agent.md", "用户长期约定与本轮优先级", "instruction"),
    ("E02", "dnf-native-demo/AGENTS.md", "工程边界与协作约定", "instruction"),
    ("E03", "dnf-native-demo/CURRENT_TASK.md", "当前候选和实际缺口，历史hash不是本轮二进制重验", "handoff"),
    ("E04", "dnf-native-demo/include/dnf/resources.hpp", "来源、动画与资源现有接口", "source-interface"),
    ("E05", "dnf-native-demo/include/dnf/character.hpp", "角色及技能身份与来源", "source-interface"),
    ("E06", "dnf-native-demo/include/dnf/character_controller.hpp", "运行资格与旧confirmed gate", "source-interface"),
    ("E07", "dnf-native-demo/include/dnf/skill_data.hpp", "SKL模式/等级表读取", "source-interface"),
    ("E08", "dnf-native-demo/include/dnf/equipment_motion.hpp", "EQU/LAY来源绑定", "source-interface"),
    ("E09", "dnf-native-demo/include/dnf/objects.hpp", "已存在物件三层和pending事件", "source-interface"),
    ("E10", "dnf-native-demo/include/dnf/region.hpp", "世界目录/拓扑模型", "source-interface"),
    ("E11", "dnf-native-demo/include/dnf/progression.hpp", "现有业务窄接口", "source-interface"),
    ("E12", "dnf-native-demo/src/storage.cpp", "现有20槽及原子保存", "source-code"),
    ("E13", "dnf-native-demo/src/session.cpp", "当前恢复和布局策略", "source-code"),
    ("E14", "dnf-native-demo/CMakeLists.txt", "核心和平台构建边界", "source-code"),
    ("E15", "dnf-native-demo/tools/build.py", "D盘构建和运行保护", "source-code"),
    ("E16", "dnf-result/README.md", "全量资料索引及范围限制", "research"),
    ("E17", "dnf-result/research/new-version-readiness.json", "25类系统完整覆盖基准", "research"),
    ("E18", "dnf-result/docs/12-server-and-revised-android.md", "服务端候选规则与26/27差异", "research"),
    ("E19", "dnf-result/docs/13-readiness-and-supplement-validation.md", "已知未决与验证边界", "research"),
    ("E20", "dnf-result/docs/14-android-gunner-and-dfq-mechanics.md", "安卓修改版/DFQ机制范围", "research"),
    ("E21", "dnf-result/research/pc-native-host-api.json", "宿主API导航，不是已实现API", "research"),
    ("E22", "逆向部分结果参考/技能调用效果实现文档/dnf-skill-combat-handoff-v1/README.md", "技能参考包与版本边界", "handoff"),
    ("E23", "逆向部分结果参考/1031怪物受击死亡效果实现文档/dnf1031-monster-effects/README.md", "另一PVF怪物效果包", "handoff"),
    ("E24", "逆向部分结果参考/1031-UI渲染交接包/1031-UI渲染交接包/ui_lab_1031/docs/1031-UI层跨项目复刻规范.md", "另一PVF的UI规则/Qt候选边界", "handoff"),
]


def main():
    tasks = [{"id": i, "title": title, "depends_on": deps, "documents": [doc(d) for d in docs],
              "acceptance": checks, "status": "documentation_delivered" if i == "P00" else "planned"}
             for i, title, deps, docs, checks in TASKS]
    write("task-graph.json", {"plan_version": VERSION, "tasks": tasks,
          "integration_note": "P17早期接入，P18复核完整工具；职业任务在P15后由P18完成实际流程整合；基础接口不依赖最终消费者。"})
    research = json.loads((WORKSPACE / "dnf-result/research/new-version-readiness.json").read_text(encoding="utf-8-sig"))
    domains = {entry["domain"] for entry in research["systems"]}
    if domains != set(MODULES):
        raise ValueError("Research system coverage changed; review MODULES explicitly")
    entries = []
    for source in research["systems"]:
        docs, task_ids, scope, reason = MODULES[source["domain"]]
        entries.append({"domain": source["domain"], "title": source["title"],
                        "source_required_capabilities": source["required_capabilities"],
                        "documents": [doc(d) for d in docs], "tasks": task_ids,
                        "scope": scope, "scope_reason": reason,
                        "plan_coverage": "documented", "runtime_status": "not_revalidated_in_documentation_task"})
    write("module-coverage.json", {"plan_version": VERSION, "modules": entries})
    write("requirements-traceability.json", {"plan_version": VERSION, "requirements": [
        {"id": i, "requirement": title, "documents": [doc(d) for d in docs], "tasks": ts,
         "acceptance": checks, "plan_status": "documented", "runtime_verification": "pending"}
        for i, title, docs, ts, checks in REQUIREMENTS]})
    evidence = []
    for i, path, purpose, kind in EVIDENCE:
        raw = (WORKSPACE / path).read_bytes()
        evidence.append({"id": i, "workspace_relative_path": path, "kind": kind, "purpose": purpose,
                         "bytes": len(raw), "sha256": hashlib.sha256(raw).hexdigest(),
                         "verification_scope": "referenced_file_bytes_only_not_native_runtime"})
    write("evidence-index.json", {"plan_version": VERSION, "source_files": evidence,
          "historical_content_claims": [
              {"origin": "current handoff", "pvf_sha256": "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d"},
              {"origin": "UI and monster handoffs", "pvf_sha256": "ca756b7103a91628cffdf42fb745e9185fd5937deb229289a74831aa30500e1f"}],
          "original_client_rehashed_this_task": False,
          "excluded_inputs": ["frozen GBA implementation and derived assets", "DFQ UI"]})
    print(f"Generated 4 indexes: {len(tasks)} tasks, {len(entries)} systems, {len(REQUIREMENTS)} requirements, {len(evidence)} evidence files")


if __name__ == "__main__":
    main()
