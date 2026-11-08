# 可复用模块与证据入口

当前R60-03已接实际clock消费者，自动结果见 [VERIFICATION](integration/R60-03-VERIFICATION.json)，范围/备份/恢复见 [PROGRESS](integration/R60-03-PROGRESS.md)。共享C++17接口位于 `integration/include/dnf_ani_render.hpp`、`dnf_ani_clock.hpp`；主工程身体/装备/攻击/声音、动态ALS与独立播放器接入均有实际检查。源技能阶段/ACT/怪物等尚未覆盖的时钟仍按显式旧路径运行，不将本节点扩大为完整控制器恢复。下表描述冻结60US研究资料，文末代码定位是R60-01的历史审查基线。

下列路径均在固定快照 `releases/20261020-01/` 中。可执行模型是Python/JavaScript实现，REA导出的 `.c` 是伪代码；接入C++时按已核实语义实现适配，不直接当原始源码编译。

| 模块 | 源码 / 合同 / 证据入口 | 接入提示 |
|---|---|---|
| PVF档案消费 | [pvf60.py](releases/20261020-01/analysis/pvf60.py)、[消费链](releases/20261020-01/analysis/PVF消费链分析.md) | key=0与当前60US文本格式；1031已有解析器保留其版本 |
| 有序脚本/目录 | [pvf_model.py](releases/20261020-01/combat-preview/pvf_model.py)、[catalog.py](releases/20261020-01/combat-preview/catalog.py)、[目录报告](releases/20261020-01/analysis/combat_catalog/README.md) | 保留offset、重复/空字段与未知项 |
| 名称与图标 | [string_names.py](releases/20261020-01/combat-preview/string_names.py)、[名称来源](releases/20261020-01/analysis/combat_catalog/SKILL_NAMES.md) | `<list::key>`→string.usa.lst→STR；显式@GBK936@按CP936，其余严格CP949；688条已解析 |
| NPK/IMG | [resources.py](releases/20261020-01/combat-preview/resources.py)、[npk60](releases/20261020-01/analysis/npk60/README.md) | 链接帧/裁剪偏移/原点保留，同路径资源冲突显式选源 |
| 通用绘制 | [renderer.js](releases/20261020-01/combat-preview/web/renderer.js)、[变换证据](releases/20261020-01/analysis/combat_render/transform/README.md)、[混合证据](releases/20261020-01/analysis/combat_render/README.md) | 正常原点、负弧度、输出轴缩放、RGBA纹理调制、SRCALPHA/ONE；其他效果未完全恢复 |
| 连续插值 | [插值证据/REA](releases/20261020-01/analysis/combat_render/interpolation/README.md)、[原指令向量](releases/20261020-01/analysis/combat_render/interpolation/native-vectors.json) | A24950/473F20/B099B0；位置/RGBA向零截断，rate/angle落float32，图片与盒不插值；24组局部核对 |
| 时间轴/附层 | [timeline.js](releases/20261020-01/combat-preview/web/timeline.js)、[timeline](releases/20261020-01/analysis/combat_timeline/README.md)、[motion](releases/20261020-01/analysis/combat_motion/README.md) | 源DELAY rate100预览已接；真实角色clock、有效速率与hit pause仍需接入 |
| 技能入口与实例 | [controllers.py](releases/20261020-01/combat-preview/controllers.py)、[dispatch](releases/20261020-01/analysis/combat_skill_dispatch/README.md)、[鬼斩](releases/20261020-01/analysis/combat_hardattack/README.md)、[三段斩](releases/20261020-01/analysis/combat_tripleslash/README.md) | 130请求路径不是130完整技能；完整控制器0；三段斩未自动续段 |
| 通用施法与生成物 | [casting.py](releases/20261020-01/combat-preview/casting.py)、[cast](releases/20261020-01/analysis/combat_cast_state/README.md)、[spawned.py](releases/20261020-01/combat-preview/spawned.py)、[spawn](releases/20261020-01/analysis/combat_spawned_object/README.md) | 21注册variant/42主体资源；波动爆发两视觉和无图攻击对象独立；时序未等效实机 |
| 判定与命中历史 | [geometry.js](releases/20261020-01/combat-preview/web/geometry.js)、[几何合同](releases/20261020-01/analysis/combat_native_collision/geometry-contract.json)、[命中历史](releases/20261020-01/analysis/combat_hit_lifecycle/README.md) | XYZ包含边界、朝向和float32平移；资格/去重/接受命中与几何分开 |
| 受击和死亡 | [reactions.py](releases/20261020-01/combat-preview/reactions.py)、[reaction_motion](releases/20261020-01/analysis/combat_reaction_motion/README.md)、[死亡合同](releases/20261020-01/analysis/combat_native_collision/death-lifecycle-contract.json) | 状态0/3/4与ACT优先；state5不是统一death ANI；完整last action与残余保护仍有缺口 |
| 场景破坏 | [scene_objects.py](releases/20261020-01/combat-preview/scene_objects.py)、[场景API](releases/20261020-01/analysis/combat_native_collision/SCENE_PREVIEW_API.md)、[scene_state_model.py](releases/20261020-01/analysis/combat_native_collision/scene_state_model.py) | 桶树草显式事件模型；移除请求与实际移除分开，PTL仅列调用 |
| 原件身份/运行时替换 | [executable_source.py](releases/20261020-01/combat-preview/executable_source.py)、[启动器补丁来源](releases/20261020-01/analysis/unpack_attempts/001/patcher-source/README.md) | 原v3/v4静态身份分开；launcher替换受保护战斗分支，不声明完整脱壳 |

## R60-01审查时的目标代码定位（历史）

- [dnf-native-demo/src/resources.cpp](../dnf-native-demo/src/resources.cpp)：`Animation::samplePose` 已有插值；当前实现的位置、RGBA用double mix。先做profile差异审查，不能全局换成60US截断后宣称1031已证实。
- [dnf-native-demo/src/renderer.cpp](../dnf-native-demo/src/renderer.cpp)：消费pose、纹理颜色、alpha、混合与层。已有功能先核对，避免重复实现。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp](../rep-player-1031-pvf/src/pvf_preview_scene.cpp)：保留ANI/ALS插值标志，目前有离散采样诊断；本包可提供采样算法与用例，但1031适用性单独登记。
- [rep-player-1031-pvf/src/pvf_script_preview.cpp](../rep-player-1031-pvf/src/pvf_script_preview.cpp)：已有 `displayName()` 和新版n_string.lst消费；借鉴同一查表接口，保留60US文本与1031二进制格式分支。

不要重新全量反编译本包已保留的函数。只有出现具体矛盾或缺口时再做定点REA查询，并保留新证据与失败原因。完整旧REA返回位于快照 `analysis/rea/results/`；原指令与实际模型的局限见各模块README。
