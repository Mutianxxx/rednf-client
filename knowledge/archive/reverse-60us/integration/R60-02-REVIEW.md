# R60-02 独立代码审查

审查日期：2026-10-20。按 R60-01 冻结基线，对当前共享数值内核、主客户端和独立播放器的实际消费者作只读审查。此次未修改生产源码、未启动原客户端，也未另外构建游戏。构建、离屏像素与打包验证由整合者单独执行；本报告不替代这些结果。

静态审查通过，没有发现剩余的采样、四顶点变换或交付源码路径阻断。初审发现的三项问题已经由整合者修复并通过只读代码复查：独立播放器历史备份工具遗漏共享头文件、legacy 导出策略与实际行为不一致、ALS/怪物未知混合诊断覆盖不足。以下保留初审位置和影响，修复位置与核对结果见末尾；实际构建、离屏和整包验收仍单独记录。

## 初审问题

| 编号 | 位置 | 实际问题与影响 | 建议 | 初审状态 |
|---|---|---|---|---|
| RV02-01 | `rep-player-1031-pvf/src/pvf_animation.hpp:4`；`tools/checkpoint-preview.ps1:24` | 头文件通过 `../../reverse-60us/integration/include/dnf_ani_render.hpp` 引用工作区外文件，旧工具仅复制播放器工程根。只备份该目录可运行现有 EXE，但不能独立重建源码。 | 节点整包保留 `source/{dnf-native-demo,rep-player-1031-pvf,reverse-60us/integration/include}` 相对布局；历史单工程备份工具另复制同级共享头并纳入 hash 清单。主工程 checkpoint 工具已考虑此路径。 | 已报告整合者；专用整包方案已确认，产物闭包仍须实际验证。 |
| RV02-02 | `rep-player-1031-pvf/src/pvf_preview_scene.cpp:298` | `render_policy` 无条件写 `algorithm_evidence_version=60US`、`unknown_blend_fallback=normal-with-diagnostic`，但 legacy 仍离散采样且 effect1/2 都加色。导出无法准确表达选中策略。 | 按 profile 输出算法版本、混合回退及其推断状态；保留实际 additive 比较开关。 | 已报告整合者，等待修改复查。 |
| RV02-03 | `rep-player-1031-pvf/src/pvf_preview_scene.cpp:198` 和怪物动作加载路径 | 基础轨已用 `classifyBlend()==Unsupported` 检查；ALS 子轨仍用 `interpolate || effect>2`，无插值的 effect1 子轨会在 inferred profile 从旧加色改为普通透明但无诊断。怪物动作也没有对应检查。 | 统一按当前支持范围诊断所有实际绘制来源。inferred profile 只承认 NONE/LINEARDODGE 的 60US 局部证据；effect1 不可借 effect2 批量确认。 | 已报告整合者，等待修改复查。 |

这些问题不要求停止正在运行的主工程构建；涉及播放器生产文件的修复应在其统一重建前完成，禁止修改构建中的同一输入。

## 已核对的调用路径

共享内核 `include/dnf_ani_render.hpp` 不含 EXE 地址、保护浮点布局、职业/技能常量或渲染依赖。位置插值截断完整结果，RGBA 独立截断并保留低八位，rate/angle 显式落 float32，角度直接数值插值保留整圈；图片、图形效果、box 和事件均不在连续 Pose 内。负值、末端、关闭插值、冻结和 ended 的控制参数清晰。

`makeQuad` 的 inferred 分支执行 `T(actorX, actorY-Z) * S(output axes) * R(-sourceRadians) * T(IMAGE POS) * crop`，负缩放和朝向保留。legacy 分支保持先局部缩放、再正角旋转、最后朝向。该算法迁到 1031 继续是跨版本推断；原点仅覆盖普通 IMAGE POS 模式，不能延伸为所有居中/裁剪模式已恢复。

主工程 `Animation::samplePose` 消费共享内核，`Renderer::animation` 将所选 profile 传到采样并把连续位置、rate、角度、RGBA 送入 `drawImage`。普通 sprite/粒子 API 的角度仍以度为单位，只有 ANI 路径传原始弧度。`drawImage` 按 `sourceAni` 选择 profile，避免新矩阵悄然影响 TIL、UI、普通 sprite。legacy 默认、显式 CLI profile 与诊断报告均已接线。旧值保留包括 double 插值、RGBA 四舍五入、effect1/2 的加色比较策略和原 MONOCHROME 路径。

独立播放器 `Animation::samplePose` 在 legacy 下保持离散帧；inferred 仅在源帧标记、调用开关、非冻结且有下一帧时插值。实际 `drawTrack` 已调用采样，并用结果参与四顶点和 RGBA 绘制；未停留在模型或未调用算法。UV、atlas rotated 约定沿用原路径；`quadCorner={0,1,3,2}` 正确对应原 TL/TR/BL/BR 网格。独立 `imageScale` 是整体比例，放在 quad 外与同一均匀比例的矩阵运算相容。碰撞框仍取离散源帧并使用原 attackScale，未被渲染插值改写。

GUI 提供 inferred/legacy 与插值开关，策略变更不改 source raw、播放时刻或技能账本；导出由当前 `SceneOptions` 传入。主客户端的默认 legacy 和独立候选默认 inferred 分别明确，不能把这两个默认值混写成同一行为。

## 图标与内容范围

图标来自当前模板绑定的 SKL `[icon]`，记录路径、帧号与 tag token ordinal；图像加载走本项目 Assets 和当前 PVF/NPK provider，来源 observer 会记录 IMG hash/容器/偏移。图标 draw 方法保留原 IMG crop 和 atlas UV，无现代技能映射或 86JP 图标迁移表替代。

目前新增图标消费者只在 `recipe.templateBinding` 存在时执行。四条专用来源流程、原始 CHR/ANI 浏览等 recipe 没有因此自动获得图标，交付说明应限定此范围。`skill_icon.loaded` 初审时表示 `Frame` 指针存在；源空帧仍会被 `icon()` 跳过，不能把该布尔当作可见像素验收。`complete_resources` 和模板可播放也不能升级为技能控制器或完整资源像素一致。

现有名称解析按 1031 自身 `n_string.lst` 和 token5 保留，未把 60US 文本格式或六职业目录移入 1031。`native_controller_verified=false`、`cross_version_verified=false`、资源时钟限制和手动几何接触范围仍保留。十职业与最终技能门槛没有因通用渲染模块而减少。

## 证据与测试界限

只读查看了 `validation/render-contract-20261020-010654-864068-54da53f6` 的既有共享内核/播放器 adapter 报告。其保留的 24 个 60US 原指令输出用于局部数值比较，8 条 1031 ANI 用于适配采样；没有据此认定 1031 原生调用链或 GPU 像素等效。测试代码还包含真实 D3D 读回验证 normal/LINEARDODGE 的 RGBA 与 alpha 一次调制、插值开关、legacy 离散和重播确定性，但实际本轮执行结果必须以整合者的最终构建与离屏报告为准。

主工程 `tools/build.py` 与播放器 `build-preview.ps1` 均将共享头文件纳入输入 hash；播放器 build 在结束时重新核对源输入，避免构建中改源码被错误接受。最终整包仍需核对复制后 `#include` 路径、构建工具、源码 manifest、EXE 和运行资产；工作区内构建成功不等于独立备份可重建。

当前仍后置：真实角色/附层 clock、变速、hit pause、未知混合、居中原点、binary effect6 与本版本 parser 差异、技能完整阶段/视觉对象生命周期、受击死亡/场景破坏。PVP 非文字 UI 和用户指定【菜单】【商城】字体继续在最终范围内，不能把本轮渲染数值检查记作这些内容完成。

## 复查记录

初审建议已及时发送整合者，整合者完成修复后已逐项只读复查：

- RV02-01：`tools/checkpoint-preview.ps1:27` 起复制共享头至 checkpoint 的同级 `reverse-60us/integration/include`，核对原/复制 hash，并将其纳入 `SHA256SUMS.csv`。此布局可解析 `source/src/pvf_animation.hpp` 的相对 include。专用节点整包也由整合者明确保留两个工程与共享头的原相对位置；实际包的重建检查属于打包验收。
- RV02-02：`pvf_preview_scene.cpp:299` 起按选中 profile 写算法版本、有效插值与混合回退。legacy 不再被错误标成60US插值/普通透明策略。当前尚未把 additive 开关写入 JSON；此为反馈复现信息的小缺口，不阻止本次静态通过，后续可附带保存。
- RV02-03：`pvf_preview_scene.cpp:282` 起统一遍历普通轨、怪物轨和接触生成轨，按 `(ANI path, effect)` 去重后诊断所有 `Unsupported` 效果。ALS 子轨也在上述容器内，无插值的 effect1 已覆盖。

结论限于本报告所核对的源码身份：可继续对当前源进行统一构建与离屏验证。未进行原版实机对照，不把静态通过追认为1031原生算术或完整职业技能验收。

## Reviewed source identities

UTC: `2026-10-19T17:11:57.292945+00:00`. Further source changes require the integrator to reconcile these hashes with the final build manifest.

| File | SHA256 |
|---|---|
| [reverse-60us/integration/include/dnf_ani_render.hpp](../../reverse-60us/integration/include/dnf_ani_render.hpp) | `9a5684dac2224fc774ed98813926928267e26c05f3417732b9125ca9117e4c46` |
| [dnf-native-demo/src/resources.cpp](../../dnf-native-demo/src/resources.cpp) | `7d0b5cf9335217dcb8cecabf1f149de8f3731c535a8e73d06546f644c99cabed` |
| [dnf-native-demo/src/renderer.cpp](../../dnf-native-demo/src/renderer.cpp) | `e25cfd1cff10fdfe984ba66cebfdf008a4c371b7a7e3709e7f4c5db83c463ea6` |
| [dnf-native-demo/src/main.cpp](../../dnf-native-demo/src/main.cpp) | `f505a1d6e63199dbbc945329778419a9d9412c02f697f7c33faec78e2fc7cde1` |
| [dnf-native-demo/src/skill_preview.cpp](../../dnf-native-demo/src/skill_preview.cpp) | `3e49bb842a3f33a1e3e5e0bf915b0794ee41edbef1aca2b488ffd3c6f1cdc766` |
| [dnf-native-demo/include/dnf/resources.hpp](../../dnf-native-demo/include/dnf/resources.hpp) | `7cee6b6ee8671570acabb4c43a4e58351fbc488591a82e133246653733799a0e` |
| [dnf-native-demo/include/dnf/renderer.hpp](../../dnf-native-demo/include/dnf/renderer.hpp) | `3acc861b55daa3969f4500b93375bebd140dd7ac11bd227bf336d68647242a7c` |
| [dnf-native-demo/tools/build.py](../../dnf-native-demo/tools/build.py) | `df1e0c708613a6f0c489f90dcf5864c5c44e4de12702a87f2d7b1d9028e2ddc7` |
| [dnf-native-demo/tools/checkpoint_node.py](../../dnf-native-demo/tools/checkpoint_node.py) | `ef0197dc62ec4a489be3a5ef17b1d073ed253f0d312bf10b66422d0aec015cb7` |
| [rep-player-1031-pvf/src/pvf_animation.hpp](../../rep-player-1031-pvf/src/pvf_animation.hpp) | `0a78c8691dbc001b222dfa649455c55a5d0c7e97ced60c13b14d5f76e9830b20` |
| [rep-player-1031-pvf/src/pvf_animation.cpp](../../rep-player-1031-pvf/src/pvf_animation.cpp) | `369d4823fa12911daf72f12c9a780af195cb2f0c8bac5e2898def9d8ca73cd1f` |
| [rep-player-1031-pvf/src/pvf_preview_scene.hpp](../../rep-player-1031-pvf/src/pvf_preview_scene.hpp) | `af70d53fca598a943887e15484aaaed0e377c5dfbe11c61e4579cf6b1fe50685` |
| [rep-player-1031-pvf/src/pvf_preview_scene.cpp](../../rep-player-1031-pvf/src/pvf_preview_scene.cpp) | `4c19d1ceebbd3bc2753e67aa4b19f63203a8a9d0658318b3f0b7dae2ed4724ee` |
| [rep-player-1031-pvf/src/pvf_template_preview.cpp](../../rep-player-1031-pvf/src/pvf_template_preview.cpp) | `6198da0879406f5510709450740d3c12b96c647666ae75970e6245ea593e42c1` |
| [rep-player-1031-pvf/src/pvf_preview_catalog.hpp](../../rep-player-1031-pvf/src/pvf_preview_catalog.hpp) | `1ac11a9af505e056beed6c60d34e0476f0e456aa145fc08386ccdf4754a6b379` |
| [rep-player-1031-pvf/src/pvf_preview.cpp](../../rep-player-1031-pvf/src/pvf_preview.cpp) | `7aa79def8d0a4d9bf8cdaf0cb9b9915aa418e5136b2ab07437ca57fce83e146e` |
| [rep-player-1031-pvf/src/pvf_preview_verify.cpp](../../rep-player-1031-pvf/src/pvf_preview_verify.cpp) | `a83010b831332e7597fbc320404e9304976b3eb046db129288a7e3b9efa895ce` |
| [rep-player-1031-pvf/build-preview.ps1](../../rep-player-1031-pvf/build-preview.ps1) | `86fd4abba7a747462ac3011542104ef0f782c5b19e2ff6d8e45addc014311b40` |
| [rep-player-1031-pvf/tools/checkpoint-preview.ps1](../../rep-player-1031-pvf/tools/checkpoint-preview.ps1) | `59abcca1a76ae3f441d9dab262aadb7d4815711f8b99045e692050759556f090` |

## Existing local-check records read during review

| Record | Passed | Count / boundary | SHA256 |
|---|---|---|---|
| [contract-report.json](../../reverse-60us/integration/validation/render-contract-20261020-010654-864068-54da53f6/contract-report.json) | true | 145 result rows; existing report, no execution by this reviewer | `dd955b5eb2cdad5df532371d8064c2707f8ae8771fc08950824ccd4077748594` |
| [rep-adapter-report.json](../../reverse-60us/integration/validation/render-contract-20261020-010654-864068-54da53f6/rep-adapter-report.json) | true | 353 result rows; existing report, no execution by this reviewer | `b75406b40e4aee464b06a3990141bc268c3db97448ff66c9abd9c162f140b3e9` |
