# 12 平台边界、性能预算、构建与交付

版本：v1.1；日期：2026-10-18；状态：设计待实施；对应 P19。当前目标为 Windows C++17/SDL2；未来端口保留数据与接口，不以 PC 自动测试替代 PSP/GBA 验收。

## 1. 工程实际起点

[CMakeLists](../dnf-native-demo/CMakeLists.txt)已经分开 dnf_core 与 SDL 应用，但资源转码仍有 Windows 分支、Cursor 读取依赖本机字节序；[移植约定](../dnf-native-demo/docs/PORTING.md)明确源字节、坐标、时间、资源身份及未知字段须保留。旧冻结 GBA 源码和派生资产禁止读取/复用，本设计未读取它们。

[build.py](../dnf-native-demo/tools/build.py)支持项目内独立 build-dir，并将 TEMP/TMP/TMPDIR 及编译缓存放项目 D 盘；当前 require_game_closed 全局检查仍可能阻挡隔离候选。后续精确核对待写目标 EXE，允许其他路径的原客户端/候选继续运行，绝不杀进程。无法证明目标可安全写入时改用新的构建目录。

[package_playable.py](../dnf-native-demo/tools/package_playable.py)当前内置鬼剑士洛兰说明及旧路径假设，需要改为读取真实 release manifest。历史 playable、1c55ec60及后续候选保持身份，不覆盖为“新版已完成”。

## 2. 可移植分层与资源 Profile

建议稳定边界为 `IResourceReader`、`ITextDecoder`、`IRenderBackend`、`IAudioBackend`、`IInputAdapter`、`IStorage`、`IMonotonicClock`。核心层只持源身份、纯数据和命令，不持 SDL、Win32、GPU纹理或设备句柄。源时间保持毫秒/明确单位，模拟tick是运行策略，不能覆写 ANI delay。

`ContentProfile` 独立指定 PVF 文件、静态资源根、编码、解析器版本、兼容规则集；记录PVF SHA、归档清单与实际读取成员SHA、证据EXE身份。更换PVF后重启加载，首版不支持副本中热换。解析器、行为能力与内容ID分离；新增内容仅在所需格式和行为已支持时直接运行，未知能力给具体依赖诊断，不作地图白名单补丁。

缓存键由源profile generation、规范路径及原字面路径、物理归档/offset/length/memberHash、decoderVersion、帧号和平台格式组成。三级缓存分别为源字节、平台无关解码结果、GPU/PCM派生；不拿旧PNG存在当源未变化。整包启动不要求每次重解码全部资源，但索引缓存必须核对文件身份，实际读成员继续核对哈希。同名不同字节资源拒绝隐式选择；显式物理选择仍保留歧义记录。

源格式读取使用显式little-endian及固定宽度类型，float32按源合同保存，必要时禁止fast-math/FMA重排；不序列化指针、size_t、SDL结构或系统绝对tick。CP936和CP949由profile明确指定，非Windows后端需要可验证转码，不用本机默认编码。源数据与平台压缩/缩放导出分别存储，任何派生资源都能反查原PVF/NPK/IMG帧。

## 3. 端口限制与性能默认预算

以下是工程初始预算，不是已测性能或原版数值；正式候选输出实测统计，超预算先优化缓存和调度，不删源字段或碰撞语义。

| 维度 | Windows beta 初始推荐 | 后续 PSP/GBA 边界 |
| --- | --- | --- |
| 模拟 | 固定60Hz，tick p95目标≤8ms，p99≤16.67ms | 根据端口实测调度，保留源时长与事件；不能直接宣称同数值精度 |
| 渲染 | 无固定FPS上限，默认vsync；输出分辨率用户可改 | 各端显示/调色板/图元预算独立配置 |
| 内存缓存 | CPU解码512MiB、GPU纹理256MiB软预算，按字节LRU | 平台预算外置，保留未量化源；不从旧GBA派生导入 |
| GPU上传 | 每帧4MiB/2ms软预算，达到任一阈值后停止追加上传任务 | 大资源分块，单次调用无法中断，记录超时 |
| 加载线程 | 默认2个worker，阻塞IO与解码任务有上限 | 按设备能力调整，不改变核心结果 |
| 音频 | 默认64个效果voice上限，循环/关键音优先 | 采样率、声道、压缩属后端，源ID不变 |

缓存软预算允许必要场景资源被pin；不能为了LRU淘汰当前动作纹理造成缺帧。超过软预算记录超出量，关键资源不足时暂停加载并报告，不擅自省略技能效果。后台无上限IO、每帧全量JSON、每次draw解码均列为禁止实现。

按[推荐决策 D23](appendices/recommended-decisions.md)，大纹理在主线程创建后用分块SDL_UpdateTexture跨帧上传；资源句柄保持pending，所有分块完成且generation仍有效才发布ready。单次SDL/GPU调用可能超过2ms，无法中途抢占，必须计入超时统计并调整后续块大小；不能把软预算宣称硬实时保证。取消任务在主线程销毁尚未发布纹理。

长帧补tick默认每轮事件循环最多执行8个tick，再回到事件泵并继续偿还积压；不静默丢模拟时间。负载持续超限时显示性能诊断；失焦/明确暂停期间按PausePolicy停止时间提交，恢复重置基准。输入按时间戳入队，补tick不得重复按下沿。渲染插值仅消费快照，帧率变化不改变CD/伤害/奖励。

窗口化、全屏、分辨率/DPI变化重建viewport；vsync切换若需重建renderer必须重新上传本窗口纹理并保留CPU缓存。系统事件继续处理，主线程不因加载等待future而卡死。GPU丢失/音频设备失败通过后端重建，核心实体状态保持一致。

仅主窗启用用户选择的vsync；测试窗renderer关闭vsync、默认30Hz刷新（可配置），避免两个present串行等待。主窗失焦清键，应用两窗均失焦才默认暂停；切到测试窗继续模拟或由用户显式Pause。窗口表现频率不改变模拟60Hz。

未来PSP/GBA需要独立工具链、资源编译器、输入映射、音频/存储和实际硬件或对应模拟器验收。GBA240×160、色板/对象/ROM预算等仅作为平台约束，不能回写PC内容；PSP不能继承GBA减CD或提前开技能等旧策略。本轮不承诺这些端口已交付。

## 4. 构建、候选目录与清单

构建输出采用 `dnf-native-demo/cache/build-v0.1-beta-candidate.N`，打包暂存和报告留D盘项目内。编译、测试、打包串行；各工作线只提交源码或报告，不同时覆盖公共入口和输出。保留编译器/CMake/依赖版本及构建参数，固定候选ID，禁止在同一已验收ID下换二进制。

推荐 release manifest：

```json
{
  "schemaVersion": 1,
  "version": "v0.1 beta",
  "candidate": "candidate.N",
  "status": "candidate",
  "build": {"compiler": "record-at-build", "sourceDigest": "computed", "files": []},
  "contentProfile": {"pvfSha256": "computed", "resourceManifestSha256": "computed"},
  "saveSchema": "actual-schema",
  "ruleset": "actual-effective-ruleset",
  "coverage": {"implemented": [], "disabled": [], "inferred": [], "pending": []},
  "verification": {"automated": [], "userPlaytest": "pending"}
}
```

示例占位值仅说明结构，打包器必须写实际数据，禁止原样发布。coverage分别记录来源可读、运行实现、自动测试和用户验证；仅鬼剑士可玩时就写这一事实，不用全职业来源索引数量充当完成数。正式满足十职业及转职觉醒技能门槛后才更新正式包状态。

包内包括EXE、实际依赖DLL、profile模板、必要兼容配置、manifest、中文启动说明、已知缺口、用户测试清单与反馈入口。用户持有的原客户端资源保持外置只读，不重复搬入候选；启动器使用自身路径和显式参数，支持独立PVF/资源根/save-dir，从任意cwd运行。缺资源时报告具体路径与期望，不自动修改原客户端。

存档默认定位规则需明确到版本配置，不依赖“exe两级父目录”。候选默认隔离存档目录，显式导入旧档前备份和校验，禁止直接覆盖用户原存档。新profile检测不兼容ID/字段时保留原档并给诊断，不能静默套上另一个职业/装备。发布失败保留暂存诊断，不替换已验证候选。

## 5. P19 执行与验收

前置实施归属：P01/P02完成profile、端序/编码、缓存身份；P03完成时钟、平台输入接口与异步generation合同；P16/P17集成渲染、音频、双窗口及预算统计。上述基础不得延后到最终打包。P19.1复核这些基础与实际依赖；P19.2复核预算/加载取消/设备恢复测试记录；P19.3构建隔离候选并生成manifest；P19.4核对包内文件哈希与任意cwd启动；P19.5交付隔离存档入口和用户测试清单。P19只整合、验证和打包已实现能力。

自动验收包含：全部核心测试、目标变更相关专项、依赖DLL清单、哈希一致、不同cwd和路径含中文空格、配置错误、profile变化缓存失效、同名资源冲突、旧存档迁移、失败不破坏原档、不同渲染帧率和补tick结果一致、异步取消后无旧generation提交、预算指标可追踪。逻辑测试不用前台试玩，音频dummy/离屏图仅记录其实际证明范围。

交付给用户的测试清单至少含创建中文角色、十职业覆盖矩阵对应动作、学习/装备/商店/维修/任务/副本/结算/重载、双窗口测试设置、分辨率/DPI/全屏/vsync、声音和加载取消。用户负责真实画面、输入法和手感反馈；报告标记未验收，不能自动填通过。所有历史候选、原始源文件、旧失败证据保留，发布不得关闭用户原客户端或覆盖运行中的EXE。
