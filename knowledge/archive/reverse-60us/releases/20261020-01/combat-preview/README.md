# 60US PVF 技能研究预览

独立、可修改源码的本地预览，直接读取当前目录上级 `DFO/Script.pvf` 和 `DFO/ImagePacks2`。
当前可以检查六职业 688 条注册技能的名称、图标、SKL、原动作资源，以及有原生绑定证据的普通鬼斩、三段斩单段资源、波动爆发视觉与攻击实体。
这里的完整技能控制器覆盖仍是 **0**；普通鬼斩是部分重建，不能视作全职业战斗已完成。

## 启动

双击 `Start.cmd`，等资源目录载入后浏览器打开 `http://127.0.0.1:8760`。
启动脚本优先使用本机现有 `G:\ProgramData\miniconda3\python.exe`，否则使用 `py -3`。
Python 核心实现仅使用标准库，不需要安装 Web 框架、Pillow 或第三方 PVF 包。

也可以在工作区根目录运行：

```powershell
python -X utf8 combat-preview/server.py --port 8760 --open-browser
```

`--client D:\路径\DFO` 可改变只读客户端目录。原生控制器合同会校验 EXE/PVF 的 SHA256，来源不符时不套用状态编号。
当前导入修复 v4 可在核对精确哈希、原 v3 备份身份、入口和原七节完整字节后复用历史静态合同；API 分别记录实际 EXE 哈希与静态证据哈希。这不证明启动器运行时替换逻辑等同原实现。
服务仅监听 `127.0.0.1`。关闭控制台或 Ctrl+C 停止，不启动原游戏，也不修改原客户端或 `dnf-native-demo`。

## 查看普通鬼斩

技能目录已显示当前PVF的中文名、英文副名和原技能图标，支持中英文/ID搜索及主动、被动、已有预览资源筛选。688条注册技能的名称都已解析；名称可见不表示释放链已恢复。

1. 选择鬼剑士，在技能目录点击 `#5 hardattack`。
2. 选择“斧棍 EQU：variation 2 / 6”，点击“预览普通鬼斩分支”。这是技能 6 未学习、dungeon 模式、基准动画速率 1 的范围。
3. 身体 IMG 存在不同 NPK 的同路径冲突时，显式选源。本次文件系统枚举与原生首命中规则支持选择 `sprite_character_swordman_equipment_avatar_skin.npk`；相同文件名永久按字典序优先并未得到证明。
4. 点击“读取 MOB”，再点击哥布林 `waiting motion` 作为对照。
5. 跳到第 3 帧，150 ms。可以看到身体、clubb/clubc 两个武器层、HardAttack1/2 两个特效，以及武器的原始攻击盒。
   此处 `clubc` 的框在 X 距离 100、Y 距离 0 时与哥布林受击盒相交。

两层的图像名由 EQU 的 `2 6` 格式化为 `club0206b.img`、`club0206c.img`。
武器层共享身体帧与延时；特效使用独立已重置的时间轴，按原生绑定向朝向偏移 40 像素。
LINEARDODGE 依据当前 EXE 的 D3D8 SRCALPHA/ONE 重建加色运算。

播放/暂停、重播、前后帧、时间拖动、速度、缩放和判定框均可直接操作。
空格播放/暂停，左右箭头切帧。左侧“动作资源”和全包 ANI 搜索可检查其他资源。
MOB 面板可按当前原生状态0/3/4选择待机、受击、倒地资源，两个受击索引为0/1。
ACT 优先时只播放其初始 BASE ANI，保留 ACT 目录拼接与预览路径规范化的区别，不执行 ACT 条件和事件。
对象有独立时间轴、播放和逐帧按钮。当前没有自动扣血、击飞或死亡状态；场景物件支持下面的明确事件采样。

鬼斩等级可选1～30；面板显示当前 PVF 等级列值、写入 ATK 的 bonus 和早期倍率。
这不是最终伤害数值：运行时修正、暴击、抗性、随机和最终取整尚未执行。

部分技能可点击“检查施法阶段0/1主体”：18条原生请求路径对应21个当前注册职业 variant、42个主体阶段资源。
这是手动资源检查，阶段时长、动作速度、装备和最终技能效果尚未执行。枪手共享控制器的变体条件待核对，界面标明资源候选。
ATGunner skill54/70当前未注册，预览拒绝按这些ID套用技能绑定。

三段斩 `#8 tripleslash` 可分别手动检查三段身体、同槽武器和特效；第3段 ATK 槽为7，不能按槽号连续猜成4。当前未自动模拟位移和接续。

波动爆发 `#32 releasewave` 点击“检查波动爆发视觉与攻击实体”：主体冻结在 phase0 第0帧作为位置参考，两个 actor 视觉与 passiveobject20018 的无图攻击 ANI 各走自己的时间轨。攻击对象每帧有原 XYZ 盒，源 DELAY 累加400后按本地模型移除；视觉轨保留末尾空图帧。可取消“攻击对象生成门通过”来核对视觉仍在、攻击实体不生成的分支。时间采用源 DELAY 基准模型，尚未模拟原角色速率、消息到达和场景 tick；不能当实机毫秒对齐结果。历史报告中的“裂波斩”指向同一ID/路径；本次名称改按当前PVF原表显示。

## 检查木桶、树与草

“场景物件事件检查”选择 ID221 木桶、224 洛兰树或244 洛兰草，点击“载入 / 重置物件”。物件显示在对照对象的位置，使用原 OBJ/ANI/NPK。先处理上方可能出现的身体 NPK 选源，再用“播放对象”或对象时间轴检查图像。

- 木桶：新绝对 HP 输入0，点击“输入 HP 写入”，显示计数、HP回满、BarrelDestroy粒子调用和移除请求。只有点击“输入实际移除通知”才移除显示。
- 树：第一次写HP0切换 etcANI0；第二次到计数上限；第三次写0保持HP0、计数2。已选择的摇动动画不因后两次事件重播；“输入 ANI 结束”也不会切回basic，因为当前资源没有etcANI1恢复分支。
- 草：第一次“输入草受击入口”切到原破坏ANI；第二次产生移除请求。ANI结束和移除请求均不会自动冒充实际移除。

这些输入是明确的人工测试事件，未声称由几何相交或游戏实测产生。HP输入为**新绝对HP**，不是伤害量。当前界面只列出PTL与音效调用，未播放猜测粒子或音效。每次采样保留输入、原生地址、输出顺序及资源哈希；最多保留64个事件，重置可重新检查。

播放器统一使用 PVF DELAY 的基准资源时间。原生动作速率、时钟、暂停和调度尚未接入，界面中的时间不能作为原客户端实际播放耗时证明。

## 当前渲染工作

按最新要求暂停扩展伤害公式，优先恢复动画显示。本次从原客户端核实并接入：

- `[IMAGE ROTATE]` 按原值弧度取负旋转，修正此前的度转弧度错误。
- `[IMAGE RATE]`、朝向、旋转和正常 `[IMAGE POS]` 原点按原矩阵顺序组合；支持非均匀/负缩放。
- `[RGBA]` 对纹理 RGB 和 alpha 分别调制，frame alpha 只在合成时使用一次；继续支持 NONE 与 LINEARDODGE。
- `[INTERPOLATION]` 按当前客户端 `A24950` 更新位置、缩放、原角度和RGBA；位置/颜色向零截断，图片和判定盒保持当前帧。可切换“ANI 插值”对照。

全包 ANI 搜索可查看 `character/swordman/effect/animation/hundredsword/finishcircle1.ani` 的实际旋转特效，以及 `character/swordman/effect/animation/soulbringer2.ani` 的紫色调制和缩放。
右侧当前帧输出 `render` 参数、原 ANI 和 IMG/NPK 来源。实现见 [renderer.js](web/renderer.js)，逆向依据见 [transform/README.md](../analysis/combat_render/transform/README.md)。

插值使用源DELAY、rate100的资源时钟，原生角色时钟、其他图形效果和居中原点模式仍未接入；全职业完整技能控制器、完整怪物受击/死亡、场景粒子仍未完成。浏览器截图尚未与原游戏逐帧对照。新增核对见 [interpolation/README.md](../analysis/combat_render/interpolation/README.md)。

## 已实现与待恢复

| 层次 | 当前状态 |
|---|---|
| PVF 解密、路径索引、完整路径冲突、CRC | 当前 key=0；99,501 payload 全量校验通过 |
| 有序 CP949 脚本、CHR/SKL/ANI | 保留空槽、重复字段、作用域、未知字段、解密后字节偏移 |
| NPK/IMG | 当前包结构、链接帧、像素解码与来源；冲突要求显式选源 |
| 全职业目录 | 6 职业、688 注册技能，可读取 SKL 与动作资源 |
| 普通鬼斩部分控制器 | 技能5→pending state20→CHR motion1/ATK0；真实 EQU→LAY 同槽附层、两张原生特效 |
| 三段斩单段检查 | 3段各自身体、装备、特效、ATK与等级列；运动和接续未执行 |
| 波动爆发效果轨 | phase0→20018→OBJ/ANI/ATK；两条原视觉与独立无图攻击对象，几何接触；主体冻结作参考 |
| 通用施法阶段 | 18条请求→21个注册variant/42个主体资源；手动选择阶段，职业效果未执行 |
| 技能等级消费 | 鬼斩原等级列→ATK bonus→早期倍率；完整伤害公式未实现 |
| 几何判定 | 原 XYZ 框、方向镜像、float32 平移、AABB 含边界接触；与接受命中分开 |
| 接受命中到 HP 的逆向证据 | 静态链已定位，完整数值/状态行为尚未移植进预览 |
| 怪物反应、死亡 | 状态0/3/4资源优先级可检查，独立时间轴；完整反应/死亡执行器待恢复 |
| 场景物件 | 木桶/树/草的明确事件采样、计数/HP回满/ANI切换/移除请求；PTL仅列调用 |
| ANI 通用渲染 | 正常原点、负弧度旋转、非均匀缩放、朝向、RGB/alpha 调制、连续插值、NONE/LINEARDODGE；角色时钟和其他效果待恢复 |
| 全职业技能执行、UI 原生绘制 | 尚未完成 |

运行成功、资源可播、浏览器没有异常，均不能替代原游戏视觉与行为对照。
当前使用的是已有 `DFO_fixed_v3.exe` 展开文件，本轮没有独立完成 Themida 脱壳，也没有恢复原始 C++ 源码。

## 源码与证据

- `pvf_model.py` / `catalog.py`：无损有序脚本与源数据目录。
- `string_names.py`：当前文本字符串注册表、显式编码和名称来源；不替换为其他版本译名。
- `resources.py`：NPK/IMG 只读解码。
- `controllers.py` / `contracts.json`：只有来源匹配且明确绑定的控制器片段进入预览。
- `casting.py` / `cast-contracts.json`：手动施法阶段主体资源，来源不符/未注册技能拒绝套用。
- `spawned.py` / `spawn-contract.json`：波动爆发来源绑定、视觉/攻击实体的独立资源时间轨；生成门为显式预览条件。
- `reactions.py` / `monster-contract.json`：状态0/3/4资源选择与ACT初始BASE ANI检查，不执行受击状态机。
- `scene_objects.py`：来源绑定的木桶/树/草状态采样，复用 `analysis/combat_native_collision/scene_state_model.py`，原件保持只读。
- `web/timeline.js`：身体、装备共享帧与独立特效时间轴。
- `web/geometry.js`：几何变换和相交，原始框不被视觉缩放改变。
- `web/renderer.js`：原 ANI 旋转/缩放/位置与纹理颜色调制。
- `web/app.js`：播放和证据检查界面。
- `../analysis/combat_skill_dispatch/`：职业工厂、技能命令、状态收发；130 条局部成功路径不等于130条完整技能。
- `../analysis/combat_native_skill_slots/`：CHR 槽、装备绑定、同步、真实 EQU 样本。
- `../analysis/combat_hardattack/`：普通分支身体/ATK/生成特效。
- `../analysis/combat_native_collision/`：几何、命中接受、消息、HP、反应链。
- `../analysis/combat_render/`：ANI 变换、RGBA 顶点颜色与 D3D8 混合因子。
- `../analysis/combat_attackinfo/`：技能等级表、ATK与早期伤害参数消费者。
- `../analysis/combat_cast_state/`：通用施法向量、phase切换和CHR throw motion。
- `../analysis/combat_tripleslash/`、`../analysis/combat_spawned_object/`：三段斩、波动爆发实例的独立原生合同（后者的历史报告仍使用旧标签“裂波斩”）。
- `../analysis/combat_hit_lifecycle/`：ATK安装、显式清理、canonical owner共享与重复命中表。
- `../analysis/combat_timeline/`、`../analysis/combat_motion/`：ANI末帧/附层顺序、原生运动与速率算术；尚未完整接进技能执行。
- `../analysis/combat_motion/owner/`：普通移动owner的位置阻挡与地形合同，74组独立原指令fixture验证。
- `../analysis/combat_reaction_motion/`：受击持续时间/水平推退、重力与纵向冲量的局部模型，126组独立原指令fixture验证。
- `../analysis/combat_progress/README.md`：统一进展、各层覆盖、函数主链和下一阶段缺口。
- `../analysis/rea/`：REA 6.7.0 / Ghidra 12.1.4 完整 Evidence、反编译文本和局限。

当前客户端逆向结果优先于 `dnf-rebuild`。不把其他版本的常数、Squirrel 控制器或参考项目猜测直接写入此预览。

## 验证

```powershell
python -X utf8 -m unittest discover -s combat-preview/tests -v
node combat-preview/tests/check_geometry.mjs
node combat-preview/tests/check_timeline.mjs
node combat-preview/tests/check_renderer.mjs
node combat-preview/tests/check_interpolation.mjs
node combat-preview/tests/check_skill_ui.mjs
node --check combat-preview/web/app.js
```

本机浏览器集成验证 `check_preview.mjs`、`check_controller.mjs`、`check_tripleslash.mjs`、`check_spawned.mjs` 和 `check_scene_objects.mjs` 使用已有 `playwright-core`、Chrome，
脚本中的安装路径需要在另一台机器上调整。它们检查六职业切换、帧控制、身体/武器/特效图像来源和真实框接触。
输出保存在 `../analysis/preview-validation/`，包括 `hardattack-controller.png`，未与原游戏截图比较。
`check_renderer.mjs` 另检查实际 PVF 的旋转、着色样本和浏览器像素运算，保存 `renderer-browser.json` 与 `finishcircle1-render.png`；它验证本地实现，不构成原游戏像素等效性证据。
