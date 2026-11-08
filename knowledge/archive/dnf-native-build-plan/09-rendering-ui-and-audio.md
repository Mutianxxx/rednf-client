# 09 渲染、必要业务 UI、音频与输入

版本：v1.1；日期：2026-10-18；状态：技术设计，待实施。对应任务 P16。本文的建议接口并不表示工程已经实现。技能、装备和完整业务闭环优先，UI 精细图层复刻可以延期。

## 1. 实际起点与证据边界

- [Renderer 当前接口](../dnf-native-demo/include/dnf/renderer.hpp)直接消费 Actor、Scene、装备外观及效果；持有单一 SDL_Window、SDL_Renderer 和纹理缓存。[主入口](../dnf-native-demo/src/main.cpp)当前事件处理未按窗口 ID 全面分流。
- [资源模型](../dnf-native-demo/include/dnf/resources.hpp)已有 Pixels 的裁剪尺寸、crop 原点、逻辑尺寸，以及 Animation::samplePose；保留这些数据，禁止把所有图片统一脚底对齐。
- [音频接口](../dnf-native-demo/include/dnf/audio.hpp)已有音乐、环境、效果总线和同步 snapshot，解码不持有回调状态锁；[内容目录](../dnf-native-demo/include/dnf/audio_catalog.hpp)与 SDL 分离。
- [UI 交接规范](../逆向部分结果参考/1031-UI渲染交接包/1031-UI渲染交接包/ui_lab_1031/docs/1031-UI层跨项目复刻规范.md)提供 322 UI、36 配置、4013 控件记录，4006 个通用前缀可解。所有窗口标记 full_native_reconstruction=false；Qt 合成图属于 candidate，不能作为原生截图或业务已实现证据。
- UI 包 PVF SHA256 为 `ca756b7103a91628cffdf42fb745e9185fd5937deb229289a74831aa30500e1f`，当前工程交接 PVF 为 `D13CE454567197BB4617CAD4D0E472F609A1EC5CF2256462D780547BE878607D`。包中 EXE 为 `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264`，其内存基线带既有插件。必须比对现用成员和字段后采用规则，不能直接把包内映射当当前 PVF 的解析结果。

## 2. 内容到画面的执行链

推荐引入只读 `RenderSnapshot` 与有序 `DrawCommand`，增量接入现有 Renderer，避免为架构改写阻塞战斗。World 完成 tick 后发布上一帧／当前帧位置及离散姿态；渲染只插值允许的连续量，不提交伤害、声音、生成或拾取事件。

```text
SourceReference → Pixels / Animation / LayoutDefinition
World tick → RenderSnapshot(previous,current,simulationTime)
Presentation clock → UI animation state
Scene composer → ordered DrawCommand[] → SDL backend
```

DrawCommand 至少保存：实例 ID、源引用、请求 IMG 帧、逻辑锚点、crop、源矩形、镜像、scaleXY、旋转单位、RGBA、blend、请求局部 clip、层组和组内序。原 ANI 旋转保持弧度，到后端才转换。身体、武器、附层、子弹、物件、PTL 使用各自实例时钟；贴图共享不合并实例。透明、加色和未知混合分别报告支持度，不能把 Qt/SDL 近似结果标为 D3D 原生一致。

地图按源层语义组织远景、地砖、地面物件、实体和前景；同层可见实体按明确地面排序键稳定排序，不能将源有序绘制请求按资源名称重新排序。未知排序作为策略并保存依据。地图遮挡不修改伤害框，角色 z 投影不改变地面 y 排序。物件动画与粒子生命周期由模拟控制器推进，Renderer 不负责移除对象。

纹理 atlas 如有必要仅在平台缓存层构建，另存原 crop、逻辑尺寸与 atlas UV。窗口 GPU 纹理按 renderer 分离，允许共享不可变解码像素。未知帧、链接循环、非法矩形、资源冲突输出结构化诊断，不使用相似文件替代。

## 3. UI 数据模型与基础业务

建议接口：`UiDocument` 保存原始有序字段；`UiInstance` 保存加载边、独立身份、父条件、状态；`UiLayout` 输出绘制与命中共用几何；`UiAction` 向业务服务提交意图；`UiDrawOp` 保存有序绘制请求。控件身份采用实例 ID 加源偏移，同 child 加载两次生成两个实例，不能按 name 合并。

优先移植有原生证据的 board/loop、图像几何、CBT/EVN 有限选帧和 WDM/STM 结构。控件整数参数按类型解析，禁止统一认作帧号。配置父偏移、已求值的运行请求锚点、IMG crop 三套坐标分开；重复父关系只累加一次位移。包内根 `(20,40)` 是观察画布偏移，不能固化进游戏。根窗口 size 不一定是像素，未恢复的 tile/标题/边框规则需单独标注。

本轮必要窗口及消费者必须闭环：

| 窗口 | 必需行为 | 业务接口边界 |
| --- | --- | --- |
| 创建、选角 | 职业状态、命名、删除确认、失败提示 | CharacterService；未实现职业明确禁用 |
| 背包、装备 | 分类、容量、堆叠、穿脱、比较、耐久、消耗品 | Inventory/EquipmentService，操作后属性重算 |
| 技能、快捷栏 | 学习条件、等级、消耗、拖放或键盘配置、空槽 | SkillService，UI 不修改技能表 |
| NPC、商店、维修 | 对话选项、价格、买卖数量、余额、维修结果 | Interaction/ShopService，确认与执行共用校验 |
| 任务 | 接取、进度、条件、提交、奖励选择 | QuestService；一次性事务结果 |
| 选图、结算 | 来源条目、等级/开放限制、选择、取消、单次入场、返城 | Entry/SessionService |
| HUD、设置 | HP/MP、目标状态、CD、装备提示、音量、显示模式 | 只读快照与设置命令 |

缺少来源证据但必须操作的控件可采用明确标为重建的简单布局；正常内容优先使用原资源。金库、邮件、活动等未支持服务必须禁用并解释，不能显示有效按钮后无行为。独立测试窗口见 [11](11-beta-tools-and-rule-strategies.md)。

模态栈统一处理 Esc、焦点、鼠标捕获和穿透。关闭选图后入口锁存，角色离开入口再进入才重新弹出。UI 事件附序号，入场/购买等同一次点击只提交一个业务命令。绘制与点击使用同一 viewport 变换；逻辑 UI 参考 800×600，实际窗口/DPI/letterbox 坐标通过唯一正逆变换换算。

## 4. 输入、中文命名与时间

使用 SDL_TEXTEDITING 展示 IME 预编辑串，SDL_TEXTINPUT 仅提交已确认文本；命名窗口开启 SDL_StartTextInput 并更新候选窗矩形，离开输入框调用 SDL_StopTextInput。组合输入期间 Enter 优先提交输入法，不同时创建角色；Escape 先取消组合再按模态规则关闭。删除按 UTF-8 字符边界，光标按可见字素簇处理，不能按字节切中文。游戏按键绑定使用物理键码/动作层，文本输入聚焦时禁止战斗快捷键。

命名验证按[推荐决策 D22](appendices/recommended-decisions.md)：来源规则优先；未确认时去首尾 Unicode 空白，拒绝空串、控制字符、换行、路径分隔符和不可显示输入。trim 后的显示串保留用户拼写，长度为 1–12 个 Unicode 标量且 UTF-8 ≤48 字节；重名键采用 Unicode 15.1 的 NFC 后默认 casefold，再 NFC。Unicode及命名规则版本进入profile，不依赖系统locale或库默认版本。该限制是离线beta重建策略，允许中文，不沿用旧发布说明要求英文输入法。输入法组合取消、粘贴过长串、重名和保存后重载均需检查。

UI 动画使用 presentation clock，菜单打开仍可推进光标、hover和加载提示；战斗模拟是否暂停由明确 PausePolicy 决定。主窗失焦立即清 held keys，但只有主窗和测试窗均失焦才默认暂停本地战斗；切到测试窗不自动暂停，测试窗提供显式 Pause。统一处理本轮窗口事件后再计算应用焦点，避免主窗失焦/子窗获焦两事件间误判。恢复时重设 wall-clock 基准，不能补算失焦期间数分钟的 tick。窗口 resize/fullscreen/vsync 改变不修改模拟步长；不能以渲染一帧等于模拟一步实现限速。仅主窗采用用户选择的vsync，测试窗禁用vsync且默认30Hz刷新（可配置），避免两个present串行阻塞。

## 5. 音频事件、循环与加载

引入 `AudioEventId(session,entity,actionInstance,eventOrdinal)`。模拟事件被后端消费一次，渲染重复采样不重新播放；加载存档恢复持续循环而不重放一次性命中/死亡音。循环环境音以场景实例和声源身份拥有，换房停止旧 owner，再按新 MAP 有序 sound 计划创建；相同资源的不同声源不错误合并。

NPC 接近语音使用进入范围边沿、离开重置和可配置冷却；默认同一 NPC 一次接近只发一次，不能每 tick 播放。环境循环、NPC对白、武器音和 BGM 分组，限制并发时优先保留音乐/关键提示；丢弃低优先效果必须有计数。音量在混音阶段作用，不修改源 PCM。音频设备丢失可重建设备并恢复循环，不能阻塞模拟；未知源音量单位保持未知。

异步加载只在 worker 做文件读取、解压、解析、图片/音频解码；SDL 纹理创建、销毁及窗口事件留主线程。任务带 profile generation 与取消 token，切角色/房间取消旧批次；完成结果 generation 不匹配即丢弃。所需关键资源全部 ready 才原子切换场景，失败保持原场景并显示具体依赖；加载期间继续泵事件。缓存资源引用计数归零后分批释放，避免单帧大量 GPU 析构。

## 6. 执行子任务与验收

P16.1 审计并比对 UI 包成员，登记可采用规则和未知消费者；P16.2 提取共用 viewport、UI实例及业务事件；P16.3 接通必要窗口与 IME；P16.4 独立 draw/audio 事件与加载取消；P16.5 自动回归并提供用户测试步骤。

自动检查覆盖 crop 切帧、镜像与旋转、源逻辑尺寸、非对称九片 loop/stretch、两份子 UI、请求局部裁剪、DPI 正逆映射、重复按钮输入、IME 预编辑不提交命令、中文重名、音频事件去重、循环换房与加载取消。UI 包 golden 仅证明对应规则；dummy 音频仅证明路由/解码。用户验证真实画面、输入法候选窗、听音、商店/任务/副本流程；不得把合成 PNG 或自动通过称原版视觉验收。
