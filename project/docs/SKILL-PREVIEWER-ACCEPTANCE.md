# 技能演示（dnf_skill_previewer）— 40JP 口径

独立可执行程序，**只包含技能的渲染与判定**：人物动作、ALS 特效子链、粒子、技能图标、
攻击/受击判定盒。没有等级、MP、冷却、学习账本、状态机门禁，也没有 World ——
40JP 决定一个技能长什么样的是 `.ani` 帧表本身，时间轴是一条累计毫秒值，
同一时刻永远画出同一画面，与帧率无关。

公式与数据出处的逐条标注见 `docs/SKILL-DEMO-40JP-SPEC.md`。

## 启动

```
Play-Skill-Preview.cmd
```

或直接：

```
..\checkpoints\build\dnf_skill_previewer.exe --content-profile content-profile.json
```

`Play-Skill-Preview.cmd` 是纯 ASCII + CRLF 外壳，调用 `tools\play_skill_preview.py`
优先找 `..\checkpoints\build\`，其次 `cache\**` 里最新的 `dnf_skill_previewer.exe`。中文提示只出现在 python / C++，
`.cmd` 里出现 UTF-8 中文会让 cmd.exe 解析错位（`'not' 不是内部或外部命令`）。

参数：

| 参数 | 说明 |
|---|---|
| `--client DIR` | 直接指定 1031 客户端目录（覆盖 content-profile） |
| `--job ID` | 启动即选中该职业 |
| `--skill ID` | 启动即播放该技能（**技能 ID，不是列表序号**） |
| `--report-dir DIR` | 退出报告目录，默认 `reports/skill-previewer` |
| `--no-audio` | 不初始化音频设备 |
| `--capture PNG` | 无头截图（`--capture-frames N` 或 `--capture-after-ms MS` 后退出） |
| `--audit-map` | 不建窗口，遍历全部职业技能生成 `skill-map-audit.json` 后退出 |

## 分级（列表左侧色条）

| 级 | 含义 | 依据 |
|---|---|---|
| A | 动作 + 判定 + 特效 | CHR 槽（或 animation 目录同名文件）命中身体 ANI，且 ANI 内有 `[ATTACK BOX]`（或映射表登记的重建盒） |
| B | 仅动作 | 身体 ANI 命中，无特效 ANI 或该 ANI 无攻击盒 |
| C | 仅特效 | 只有同前缀特效 ANI / 粒子 PTL 命中 |
| D | 无资源 | 被动技能或 CHR 槽、目录、特效目录全部未命中 |

每条映射都带 `confidence`（`auto_exact` / `auto_prefix` / `auto_directory` /
`auto_effect` / `reconstructed`）与 `evidence`。**没有任何"拿别的技能动作代填"的规则**；
D 级点开视口会显示「无可用资源（不是绘制失败）」和缺失原因。

## 操作

| 按键/鼠标 | 作用 |
|---|---|
| 点击职业 | 切换职业（只重建外观，不建 World） |
| 点击技能 | 选中并立即播放；双击同一行从头重放 |
| 滚轮 | 列表滚动 |
| 空格 | 暂停 / 继续 |
| ← / → | 逐帧（毫秒寻址到帧边界；特效层与粒子一起寻址） |
| 1 / 2 / 3 / 4 | 1x / 0.5x / 0.25x / 2x |
| R | 重放当前技能 |
| F | 左右翻转（判定盒与木桩一起镜像） |
| B | 判定框开关 |
| H | 木桩数量 0 → 1 → 3 循环 |
| L | 播完自动循环开关（默认开） |
| ↑ / ↓ | 上/下一个技能并播放 |
| F12 | 截图到报告目录 |
| Esc | 退出（写 `skill-preview-report.json`） |

## 渲染层次（自底向上）

1. **粒子**：`.ptl` 一次性 burst，每粒子独立时钟；轴位移用已复核的
   `particleStraightKeepLast`（40JP vmt48 直线/梯形分支），重力项
   `z += age² × g / −2000000`（40JP vmt8）。
2. **`order < 0` 的特效层**：来自身体 ANI 的 `.als` 子链（`animationEffectEvents`），
   层号、偏移 XYZ、出现帧全部是源数据；无 `.als` 时回退到同目录同前缀特效 ANI，
   `order=0` 且 evidence 标注 `stem-prefix; order inferred`。
3. **人物本体**：`CharacterPresentation`，只依赖毫秒值。
4. **`order ≥ 0` 的特效层**。
5. **木桩与命中反馈**、判定框叠加层。

## 判定

- **红框**：源数据攻击盒。身体 ANI 或 ALS 特效层 ANI 每帧 `[ATTACK BOX]`（type 15），
  按层出生时间平移到动作时间轴。
- **黄框**：重建盒。只来自映射表登记的、带出处行号的常量（`kManualVolumes`）。
- **蓝框**：木桩受击盒，取身体 ANI 全帧 `[DAMAGE BOX]`（type 14）的并集（源数据）；
  动画没有任何受击盒时用 60×110 占位并在框上标「推断」。
- 世界盒一律 `combatBox(box, x, y, z, facing)`（朝左 `x = −x − w`），绘制 `y −= z`。
- 命中：攻击盒 × 受击盒分离轴测试（`intersectCombatBoxes`；预览把 d=0 的盒按最小深度
  1 处理，见 SPEC「推断」节），按（层, 帧, 木桩）去重；命中处在 150ms 内红色填充闪烁，
  底部显示命中计数。
- 命中**不**触发卡肉冻结：`hitStopMs` 在 1031 数据里读不到，宁可不做（SPEC「待验证」）。

## 音效

ANI 帧属性 `properties["16"]`（`[SOUND]`）在帧被访问时派发给音频汇
（与 World 同一字段）。没有推断的音效表。

## 覆盖率现状（`--audit-map` 实测）

全部 11 职业 1734 条技能：**A 54 / B 248 / C 88 / D 1344**。
本轮新增 **释放链（release chain）**：多段技能按客户端 CHR `[etc motion]` 的权威顺序
串联成一个连续动作时钟播放（如三段斩 1→5 全程 2900ms、暗天波动眼
cast→start→attack1→2→3），不再是单段碎片。鬼剑士/神枪手各 26 条技能挂上链；
阶段词（ready/cast/attack/shoot/finish…）与变体前缀（multi/ex…）匹配又救回
25 条 D 级（多重爆头、X-1压缩量子炮、幻影剑舞、极·鬼剑术等）。
鬼剑士（job 0）A 3 / B 10，神枪手（job 2）A 4 / B 5。
这是 1031 数据的真实边界：`.skl` 不引用动画，CHR 槽与 animation 目录同名规则
只能覆盖这么多；提升覆盖率需要客户端技能→动作表（exe 内），属未恢复证据。

## 验收清单

对鬼剑士 / 神枪手逐条 A 级技能核对：

| 技能 | 检查项 |
|---|---|
| 鬼斩（0/5）、连突刺（0/11）、鬼影鞭（0/111） | 动作相位、ALS 特效层、红框出现帧、翻转镜像、命中闪烁 |
| 膝撞（2/4）、瞬踢（2/7）、乱射（2/9）、浮空劫击（2/35） | 同上 |
| M-137 格林机枪（2/12，C 级） | 子弹粒子（passive object → .lst → .obj → [basic motion]）飞行方向与重力 |
| 任一 D 级 | 横幅给出缺失原因，不是空白 |

自动化：`dnf_skill_preview_tests.exe <客户端目录> <输出目录>`，30 项检查
（技能枚举、A 级可解码、D 级有原因、累加时钟不漂移、冻结语义、帧窗口连续、
镜像公式、循环回卷、毫秒帧定位、A 级体量在动作窗内、粒子位移/重力公式、
PTL 解析与拒绝、ALS 层挂接、命中就绪、截图非空）。`build.py --test` 已注册该分组。

## 数据源与脱壳评估（2026-11-03 补）

- 动作池改用 **1031 客户端自己的 `character/<job>/<job>.chr`**（`[attack/ghost/etc motion]`
  剑士 127 / 枪手 107 条有序 ANI），其余职业保留 60US 兜底。此前用 60US 池是跨版本数据源
  错配；**实测切换后分级与全部链顺序均无变化**（池只负责排序），属正确性修复。
- 同一 CHR 还发布 `[etc attack info]`（87/26 个 `.atk`）与 `animation/*.ani.als` 特效链，
  即动作全集、顺序、判定花名册都在 PVF 里，**不需要脱壳**。
- 1031 `DNF.exe` 脱壳评估见 `docs/SKILL-DEMO-40JP-SPEC.md` §6.3：静态解包中偏高、
  完整脱壳到可运行 <20%、靠脱壳拿绑定低且非必需（绑定是数字立即数，脱壳后仍是反汇编活）。
- **结论**：不优先脱壳；优先扩 60US 未加壳 exe 的绑定表，或提供 1031 未加壳 exe / PDB。

## 已知边界（证据缺失，不是待办）

- 命中卡肉冻结时长：无源数据，不做。
- `.ptl` 的持续发射（`[creation frequency] ≠ −1`）、`[sin]/[cos]` 波形轴、旋转分布、
  `[display effect rate]`：未恢复，命中即拒绝并写入 `particleErrors`。
- 混合模式只有 BLEND 与 ADD（40JP 的 DARK/MONOCHROME 未实现）。
- 技能立绘：1031 只有 28×28 图标。
