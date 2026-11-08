# 技能演示 40JP 公式与数据出处（SPEC）

本文逐条列出 `dnf_skill_previewer` 使用的 40JP 机制，并标注证据等级：

- **直证**：40JP 逆向源码或本项目已复核实现里的明确行号（`file:line`）。
- **推断**：有方向、无直证的规则；使用处与横幅/审计都会标注。
- **待验证**：语义未闭环，本 demo 明确不做。

40JP 源码归档：`knowledge/archive/40jp-reverse-source/`（`src/game/pvp_ui.cpp`、
`src/game/anim_parser.cpp`、`src/game/hiteff_monster.cpp`、`src/game/skill_load_tutorial.cpp`）。

## 1. 时间轴

| 机制 | 等级 | 出处 |
|---|---|---|
| 一切动画进度是累计毫秒值，无固定帧率 | 直证 | 40JP `time_system.h:40-51`（PauseClock）；本项目 `PreviewTimeline::advance` 按 `SDL_GetTicks64` 差值累加 |
| 帧截止 = Σ(每帧 `[DELAY]` × 100 / 速率) | 直证 | `anim_parser.cpp:1707`（`fld_2C2 = Σ delay×100/rate`）；本项目 `AniFrame::duration` 在 rate=100 时即毫秒 |
| 帧间四通道线性插值（位置/缩放/旋转/RGBA），图像、混合、flip 离散 | 直证 | `anim_parser.cpp:1561-1564`；本项目 `AniPose` + `ani_render::samplePose` |
| 尾帧且无 `[LOOP]` 保持当前值 | 直证 | `anim_parser.cpp:1561-1564` 注释；本项目 `frameIndexAt` 钳到末帧 |
| 单帧事件停滞时整段时间照常累计（不按帧丢弃） | 直证 | 40JP 空闲循环累加语义；本项目 `advance` 不再截断 250ms |
| 播完自动循环 | 推断 | 40JP 无"动画停止"概念，演示需要可复看的回卷；回卷保留跨帧余量 |

## 2. 判定盒

| 机制 | 等级 | 出处 |
|---|---|---|
| `.ani` 每帧 88 字节；+40 图形特效、+48 驻留 ms、+52 伤害类型、+56/+72 攻击盒与受击盒 vector | 直证 | `anim_parser.cpp:8-25`（+56/+72 是 vector 起止指针，元素 24B = 6 float，见 `:40`） |
| 攻击盒 = 动画对象 +116，受击盒 = +132，24B/盒 | 直证 | `hiteff_monster.cpp:4903-4908` |
| 朝左镜像 `x = −x − w`，再加本体世界坐标 | 直证 | `hiteff_monster.cpp:4903-4908`；本项目 `include/dnf/collision.hpp:10-13` |
| 命中 = 3D AABB 分离轴测试，零尺寸盒无效，贴面算接触 | 直证 | `anim_parser.cpp:1070-1073`；本项目 `intersectCombatBoxes` |
| 预览把 d=0 的盒按最小深度 1 参与测试 | 推断 | 舞台是单平面，深度不绘制；严格原生测试会让所有接触恒不成立。仅用于演示命中可视化 |
| 木桩受击盒 = 身体 ANI 全帧 `[DAMAGE BOX]`（type 14）并集 | 直证（盒）+ 推断（并集规则） | type 14 语义见 `combat.cpp:3020`；并集是为了让静止木桩在任何相位都有稳定的受击面 |
| 无受击盒时木桩用 60×110 占位 | 推断 | 框上标「推断」 |
| 命中去重键（层, 帧, 木桩） | 推断 | 40JP 用 `Effect::hits`（目标→上次命中 ms）去重（`combat.hpp:218-219`），演示采用等价键 |
| 命中卡肉冻结时长 | 待验证 | `hitStopMs` 在 1031 数据读不到 → 0，不冻结；`PreviewClock::freezeFor` 结构已就位 |
| 伤害类型 +52（0 普通/1 霸体/2 不可打断） | 直证 | `docs/25_同人开发资源完全指南.md:158-161`；演示只渲染几何，不结算伤害 |

## 3. 特效子链（ALS）

| 机制 | 等级 | 出处 |
|---|---|---|
| 子链绘制顺序：索引 <0 先递归 → 本层 → 其余 | 直证 | `anim_parser.cpp:1744-1746, 1828-1844`；本项目 `(order>=0)` 分组 + 稳定插入序 |
| `.als` 的 `[use animation]`/`[add]`/`[remove]`/draw-only 事件、层号、offsetXYZ | 直证 | 本项目 `src/presentation/effects/effect_plan.cpp:15-181`（按原始 token 类型校验载荷，不猜） |
| Add 事件的子动画循环 = 该 ANI `[LOOP]`（globals["0"]） | 直证 | `combat.cpp:2344` 同一规则 |
| draw-only 实例寿命 = 自身 ANI 时长 | 直证 | `combat.cpp:2360-2365`（`expires = now + duration`，注释标注 inferred-single-source-clip-lifetime） |
| 无 `.als` 时回退同目录同前缀特效 ANI，层序标 inferred | 推断 | 回退只在子链为空时发生，避免双画 |

## 4. 粒子

| 机制 | 等级 | 出处 |
|---|---|---|
| 每粒子独立时钟（+33 = sub_699000(+104 时钟)） | 直证 | `pvp_ui.cpp:6248-6254` |
| 轴位移求值器 vmt48：直线（0 = t·v0·0.001，1 = 梯形积分 (v0+vt)·0.5·t·0.001，超段后匀速）、往返、sin/cos 波形 | 直证 | `pvp_ui.cpp:5836-5840, 5940-6060`；直线/keep-last 分支已复核为 `particleStraightKeepLast`（1031 E581E0，VA 1565E18，scale 0.001） |
| 重力二次项 `z += t² × g / −2000000` | 直证 | `pvp_ui.cpp:6330`（`fld_e18 = t*t*+18/-2000000`） |
| vmt8 外层 `位移 = 基准 − 全局 tick × vmt48 值 × 0.01` | **待验证** | `pvp_ui.cpp:6319-6321`。`dword_7930D0`（P9 全局时间域）与 vmt48 输出的相乘语义未闭环：对本项目实测 PTL 速度值（如 700、800）会得到二次爆炸位移。本 demo 采用「vmt48 输出即该轴位移」（与已复核的 E581E0 弹道一致），外层系数不用 |
| `.ptl` 字段：`[object]`(ani,frame)、`[move type] [straight line]`、`[move variable 1]`、`[changing term]`+`[keep last value]`、`[gravity]`、`[life time]`、`[maximum create number]`、`[create area size]`、`[transparent value]` | 直证（字段存在）+ 推断（消费语义） | 字段表与 `object_presentation.cpp:14-47`、`gunner_basic.cpp readGunnerBasicParticle` 对齐；`[transparent value]` 的线性淡出是推断 |
| `[object type] [passive object]` → `passiveobject/passiveobject.lst` id→obj → `[basic motion]` ANI | 直证 | 注册表用法同 `objects.cpp:55-60`；`[basic motion]` 解析同 `objects.cpp` motion 处理 |
| 未恢复字段（持续发射、旋转分布、波形轴、`[display effect rate]`、`[landing type]`） | 待验证 | 读到即拒绝/记入 `particleErrors`，不静默丢弃 |
| burst 发射点 = 演员位置 +(朝向×20, −40) | 推断 | 40JP 由技能逻辑决定发射点，1031 数据不可得；演示取胸前定值 |

## 5. 音效

| 机制 | 等级 | 出处 |
|---|---|---|
| ANI 帧属性 `"16"` 是音效 ID，帧被访问时派发 | 直证 | `combat.cpp:2286-2291`（female-gunner 路径同一字段）；全职业沿用，属跨职业推广 |

## 6. 技能→动作映射

| 规则 | 等级 | 说明 |
|---|---|---|
| CHR motion 槽 stem == SKL 文件 stem | 直证（规则可复核） | `auto_exact` |
| 动作 stem = SKL stem + 阶段词（ready/cast/attack/shoot/finish…） | 推断 | `auto_chain`；阶段词表来自对 1031 两个 animation 目录（161+107 个 stem）的词频统计 |
| 变体前缀（multi/ex/double/triple…）+ SKL stem | 推断 | `auto_chain`；`multiheadshot*` 仍是 `headshot` 的动作 |
| 多段链顺序：60US 客户端 CHR `[etc motion]` 的排列 | 直证（60US `character/swordman/swordman.chr`） | `auto_chain`；池见 `skill_preview_motion_pool.hpp`，97/97 与 1031 stem 重合 |
| 效果 ANI：`effect/animation/` 下同前缀 stem | 推断 | 仅在无 `.als` 时用于建层 |
| 重建判定盒 | 直证（常量出处） | `kManualVolumes`，每条带 `combat.cpp:1846-1850` 行号 |

### 6.1 数据源真相（PVF 发布"花名册"，exe 发布"下标"）

- **任何版本的 PVF 都不把技能绑到动画文件**。1031 的 `skill/gunner/windmill.skl`
  与 60US 的 `skill/swordman/releasewave.skl` 全字段核对：只有 `[name] [name2] [icon]
  [command] [feature skill index] [consume MP] [cool time] [level info] [static data]`
  等数值/文本，无 `.ani`、无 `.atk` 引用。`windmill.skl` 的
  `[feature skill index] = 166` 超出 1031 动画池长度（127），是技能特征表索引，
  不是动画下标。
- **但 PVF 里本来就有权威动画花名册**，本轮实证补上：
  - `character/<job>/<job>.chr` → `[attack motion]` + `[ghost motion]` +
    `[etc motion]` 有序 ANI 列表：剑士 127（3+2+122）、枪手 107（2+2+103）；
  - 同一 CHR 的 `[etc attack info]` → 87 / 26 个 `.atk` 判定数据；
  - `character/<job>/animation/*.ani.als` 特效子链、`attackinfo/*.atk` 判定文件；
  - `skill/swordmanskill.lst` 等 `.lst` 是 skill_id → `.skl` 路径的有序映射表。
  → **动作全集、释放顺序、判定花名册都是源数据，不需要脱壳**。
- **缺的只是"skill_id → 花名册下标"这一张表**，它在 exe 代码里是数字索引/立即数，
  不是字符串：
  - 1031 `DNF.exe`（42MB，2021-09-21）明文 ASCII 字符串 57,896 条
    （`DNFLex::yylex`、`Neople Image File`、RTTI 类名、OpenSSL 参数俱在），
    但 `.ani` 0 条、`skill/` 0 条、`.skl/.chr/.lst/.atk/.als` 0 条、
    动画名（windmill/headshot/ashenfork…）0 条、技能 RTTI 类名 0 条。
    **即使完整脱壳，也不会浮现明文动画名**，仍需在反汇编里定位索引表。
  - 60US `DFO_fixed_v3.exe` 未加壳，RTTI 暴露 1722 个 `CN*` 技能类名；
    `cast-contracts.json` 固化 18 条绑定（12 剑士+1 格斗+5 枪手）。
    **其 `animation_index` 实测取值只有 0/1/3**，是变体号（variant），
    不是动画池下标——上一版 SPEC 把它写成"动画池索引"是错的，已更正。
- **40JP（ARAD.exe，2006）与 1031（2026）资源名重合率仅 1/107（枪手）、2/161（鬼剑士）**
  ——补 40JP/45JP 时期的 PVF 无助于 1031 的绑定。
- 60US 与 1031 动作命名大体一致（重合 97/102 剑士、62/68 枪手），
  但 1031 多出 25 剑士 + 41 枪手动作（FlowMind*、BloodSword*、ChargeBuster*、
  MultiHeadShotEx*…）。本轮已把动作池换成 **1031 自身 CHR**（同源同版本），
  60US 池仅作其余职业兜底。

### 6.2 仍然缺失、需要什么才能补齐

| 缺口 | 现状 | 补齐路径 |
|---|---|---|
| skill_id → 释放动作 的逐条绑定 | 60US 侧 18 条；1031 侧 0 条直证 | 继续逆向 `D:/dnf/60US/DFO/DFO_fixed_v3.exe`（未加壳、有 RTTI），把技能类构造/施放请求里的动作参数扩到全量 |
| 1031 exe 内的技能索引表 | 未定位 | 需要 1031 的**未加壳 DNF.exe / 内存 dump / PDB 符号**；硬脱壳见 6.3 |
| 动作池下标 → ANI 文件 | 1031 CHR `[etc motion]` 顺序即解析表（已接入） | 无需外部补齐，缺的是上面那张"下标"表 |
| 阶段词/变体前缀匹配顺序（池外） | 词频统计的推断 | 无直证来源，保持推断标注 |

### 6.3 给 1031 `DNF.exe` 脱壳的可行性与收益（2026-11-03 实测评估）

**结论：静态解包中等偏高，完整脱壳收益低，且"脱壳能解决所有问题"不成立。**

实测证据（全部来自 `D:/dnf-rebuild/DNF1031客户端/`）：

| 项 | 实测 | 含义 |
|---|---|---|
| `DNF.exe` | 41,978,368 B，2021-09-21，PE32，11 节 | — |
| 节区 | 7 个同名 `nsn`（全 `E00000E0` RWX）、`0x1159000` 大节；另 1 节熵 2.354（解压预留）、2 节熵 7.6/7.9 | 部分加密/压缩 + 反调试，非全盘虚拟化 |
| 入口点 | RVA `0x00FE06BA`，落在首个 `nsn` 节；字节码 `E8…/E9…` 后接标准 CRT 大小写转换代码 | 原程序代码可见，不是壳 stub |
| 导入表 | 完整保留 30 个 DLL（ddraw / d3d9 / fmodex / ijl15 / dbghelp…） | IAT 未重定向，静态解包难度下降 |
| TLS | 2 个 callback（`0x145F2B0`、`0x145F2B8`） | 反调试入口 |
| 明文字符串 | 57,896 条 ASCII，含 RTTI 类名与 `DNFLex::yylex` | 主体代码未被 VM 化 |
| 保护组件 | `TenSLX.dll`（`.tvm0` = Themida VM）、`TerSafe.dll`（`.txt$0~3` 拆分混淆）、`start/TenProtect`、`TenSLX.dat` / `Tenparty.dat` | 运行时驱动级反作弊 + 自校验 |
| `mutian.exe` | UPX0/UPX1/.rsrc，导入 gdiplus/COMCTL32/OLEACC | 是登录/界面工具，不是未保护的 DNF 主程序；脱它无助于绑定 |

分级评估：

| 目标 | 成功率 | 依据 |
|---|---|---|
| 静态解包（OEP + dump + 重建 IAT，得到可反汇编镜像） | **中偏高（约 60–70%）** | 主体明文、IAT 完整、EP 正常；障碍是 stolen bytes / 加密段 / TLS 反调试。本机未登记 x64dbg/Scylla/PE-sieve，需先自举工具 |
| 完整脱壳到可独立运行、可下断点调试 | **低（<20%）** | TenProtect 驱动 + Themida 自校验 + 服务端校验；且该目录是 2026 Script.pvf 与 2013 保护 DLL 的混搭包 |
| 脱壳后直接拿到技能绑定表 | **低，且非必需** | 绑定不是字符串（见 6.1）；脱壳只把"数字立即数"暴露出来，仍要逆 1734 条技能索引表，工作量≈扩 60US 绑定表，但风险高得多 |

**最值得补的材料（按价值排序）**：
1. 1031 的**未加壳 `DNF.exe`、内存 dump 或 PDB/符号** —— 能直接定位技能索引表函数，
   价值远大于让 AI 现场硬脱壳；
2. 允许**运行 1031 客户端并做运行时观测**（hook 动画加载 / dump 解密段），
   可绕开静态脱壳，但需处理 TenProtect；
3. 继续逆 60US `DFO_fixed_v3.exe` 扩绑定表；
4. 40JP/45JP PVF —— 无用（重合率已证）。
