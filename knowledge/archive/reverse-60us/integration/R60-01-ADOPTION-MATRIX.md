# R60-01 - 1031 / 60US adoption matrix

按冻结的1031主工程build30和独立播放器节点05源码审查名称、图标、ANI采样、变换、混合和时钟；R60-02并行施工不计入本基线。

## Review boundary

- Baseline native source: `dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source`.
- Baseline independent player: `rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source`.
- Line numbers and SHA256 below refer to these immutable node sources. Working R60-02 source is changing concurrently; it is not certified here.
- `same` is limited to the stated behavior; `missing` is limited to inspected paths; `conflict` identifies an explicit source or policy difference.
- 60US static/local-native evidence is separate from 1031 inference, original-game execution, pixel acceptance, and complete skill controllers.
- This review installs no tools, repeats no full decompilation, modifies no release, and builds/runs no game.

## Source identities

| Profile | Artifact | SHA256 |
|---|---|---|
| 60us | pvf_sha256 | `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98` |
| 60us | static_exe_sha256 | `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b` |
| 60us | selected_v4_exe_sha256 | `bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e` |
| 1031 | pvf_sha256 | `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d` |
| 1031 | exe_sha256 | `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` |

## Decisions

| ID / topic | Native baseline | Player baseline | Decision / next task |
|---|---|---|---|
| R60-01-01 / 技能名称引用与编码 | same | same | retain / R60-02 |
| R60-01-02 / 重名、缺名与技能稳定身份 | conflict | same | adopt / R60-02 |
| R60-01-03 / 原技能图标 | same | missing | retain-and-extend / R60-02 |
| R60-01-04 / 连续插值真实消费者 | same | missing | adopt / R60-02 |
| R60-01-05 / 位置插值向零截断 | conflict | missing | adopt / R60-02 |
| R60-01-06 / RGBA插值与8bit打包 | conflict | missing | adopt / R60-02 |
| R60-01-07 / 缩放与角度float32落栈 | conflict | missing | adopt / R60-02 |
| R60-01-08 / 保留整圈角度 | same | missing | retain-and-extend / R60-02 |
| R60-01-09 / 关闭插值、冻结与ended | same | missing | retain-and-extend / R60-02 |
| R60-01-10 / 末帧、循环边界与零延时 | same | same | retain / R60-02/R60-03 |
| R60-01-11 / 图片、效果、碰撞盒保持离散和每帧默认 | same | same | retain / R60-02 |
| R60-01-12 / 负弧度旋转 | conflict | conflict | adopt / R60-02 |
| R60-01-13 / 非均匀缩放与朝向次序 | conflict | conflict | adopt / R60-02 |
| R60-01-14 / IMAGE POS与IMG裁剪原点 | same | conflict | retain-and-extend / R60-02 |
| R60-01-15 / RGBA顶点调制与alpha仅乘一次 | same | same | retain / R60-02 |
| R60-01-16 / NONE与LINEARDODGE混合证据边界 | same | same | retain-and-adopt-by-profile / R60-02 |
| R60-01-17 / 未知效果与1031 binary effect6冲突 | conflict | conflict | verify-and-preserve-raw / R60-02/follow-up-version-adapter |
| R60-01-18 / 源DELAY与实际原生时钟/速率 | missing | missing | verify-by-version / R60-03 |
| R60-01-19 / 身体/装备共享帧与附层独立时间映射 | conflict | conflict | retain-version-specific-and-verify / R60-03 |
| R60-01-20 / 末帧保留与外层销毁分离 | conflict | conflict | verify-and-separate / R60-03/R60-04 |
| R60-01-21 / 附层顺序与世界排序 | same | same | retain-and-verify-world-order / R60-03/R60-04 |
| R60-01-22 / PVP非文字UI与菜单/商城字体目标 | missing | missing | retain-explicit-user-target-and-verify / P16/UI-follow-up |

### R60-01-01 技能名称引用与编码

- [dnf-native-demo/src/resources.cpp:134-170](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - stringtable和n_string表按GBK读取，使用二进制token5引用。
- [rep-player-1031-pvf/src/pvf_preview_catalog.cpp:606-641](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_catalog.cpp) - 支持单type7名称和type9/type10经n_string.lst查表；按archive代码页解码。
- [rep-player-1031-pvf/src/pvf_script_preview.cpp:210-224](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_script_preview.cpp) - displayName要求唯一引用和唯一非空名称。
- [rep-player-1031-pvf/src/pvf_template_preview.cpp:128-145](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_template_preview.cpp) - 模板保留1031名称链，缺失或歧义返回诊断身份。

Source contract: 共用查表语义；60US文本<list::key>走string.usa.lst，STR值显式@GBK936@用CP936，其余严格CP949；1031保留自身二进制格式和CP936。688只是60US解析结果。

Evidence: `E60-NAMES`.

60US: `source-data-confirmed`; 1031: `current-implementation-fact; keep-own-format`.

Action: 复用名称接口，不复制60US文本parser替换1031解析器；未来新增60US profile时新增明确格式分支。

### R60-01-02 重名、缺名与技能稳定身份

- [dnf-native-demo/src/resources.cpp:162-169](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - translations_[id][key]赋值覆盖重复键；Script::text取首字段，未提供名称歧义状态。
- [dnf-native-demo/src/resources.cpp:216-231](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 保留raw token；缺译名时保留原key。
- [rep-player-1031-pvf/src/pvf_preview_catalog.cpp:637-641](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_catalog.cpp) - 收集全部同键项，唯一且非空才返回显示名。
- [rep-player-1031-pvf/src/pvf_script_preview.cpp:218-224](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_script_preview.cpp) - 重复或缺键明确失败。

Source contract: 60US重复/缺键不选择任意一条；class0/skill32/releasewave当前名为波动爆发，历史裂波斩仅为旧标签，不按显示名重绑ID。

Evidence: `E60-NAMES`.

60US: `source-data-confirmed`; 1031: `generic-validation-rule; not-a-native-controller-claim`.

Action: 将主工程名称歧义作为可诊断状态；保留职业/技能ID/路径身份。不得把60US skill32的中文名写成1031内容常量。

### R60-01-03 原技能图标

- [dnf-native-demo/src/hud.cpp:46-69](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/hud.cpp) - 从所选SKL [icon]读取正常/禁用图标，并保留IMG逻辑尺寸。
- [dnf-native-demo/src/hud.cpp:131-139](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/hud.cpp) - 真实消费者依MP选择图标并绘制。
- [rep-player-1031-pvf/src/pvf_preview_catalog.cpp:606-641](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_catalog.cpp) - 所审查名称解析接口不读取[icon]；不能仅凭名称成功认为图标已接入。

Source contract: 60US catalog分别读取[name]/[name2]/[icon]，图标使用当前PVF和NPK；名称不决定资源身份。

Evidence: `E60-NAMES`, `E60-CATALOG-CODE`.

60US: `source-data-confirmed`; 1031: `source-driven-existing-native-HUD; player-consumer-gap-in-reviewed-interface`.

Action: 保留主HUD读取；独立播放器需要专门的SKL图标来源和UI消费者，不能把86JP图标迁移表当1031图标来源。

### R60-01-04 连续插值真实消费者

- [dnf-native-demo/src/resources.cpp:443-459](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - samplePose按当前帧插值标记更新位置、缩放、角度、RGBA。
- [dnf-native-demo/src/renderer.cpp:299-319](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - animation实际调用samplePose并绘制。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:115-118](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 诊断明确保留插值标记但仅离散采样。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:313-332](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - drawTrack直接frameAt后读取源帧属性，没有姿态插值消费者。

Source contract: 60US A27F60→A24950→A26990更新并绘制连续snapshot，不能只保留INTERPOLATION标记。

Evidence: `E60-INTERPOLATION`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `inferred-cross-version-candidate`.

Action: 接共用pose采样接口至实际绘制；1031采用60US算法需显式比较profile，保留原行为可比较。

### R60-01-05 位置插值向零截断

- [dnf-native-demo/src/resources.cpp:453-454](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - double mix保留小数，例如-3到0四分之一为-2.25。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:316-328](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 位置用离散f.x/f.y。

Source contract: 60US 473F20在完整插值结果上C01544向零截断；-3→0四分之一应为-2，不能先截断增量。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `inferred-cross-version-candidate`.

Action: 仅在证据profile采用整结果trunc；不得全局修改后称1031原生已证实。

### R60-01-06 RGBA插值与8bit打包

- [dnf-native-demo/src/resources.cpp:453-458](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - RGBA保留double插值。
- [dnf-native-demo/src/renderer.cpp:308-318](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 夹紧后lround，例如0→255中点成为128。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:332](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 按离散源RGBA生成顶点色。

Source contract: 四通道各自调用整数helper，取低8bit；0→255中点为127。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `inferred-cross-version-candidate`.

Action: pose采样阶段执行逐通道截断与字节语义，额外显示alpha策略另行应用；不把GPU像素结果等同算术fixture。

### R60-01-07 缩放与角度float32落栈

- [dnf-native-demo/src/resources.cpp:453-457](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 缩放和角度均以double mix，不强制float32结果。
- [dnf-native-demo/include/dnf/resources.hpp:88-98](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/resources.hpp) - AniPose字段为double。
- [rep-player-1031-pvf/src/pvf_animation.cpp:178-185](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp) - 源值保存float，尚无连续采样。

Source contract: 60US B099B0分支先t>=d再t<=0；scale/angle结果落float32，原指令24向量已核对。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `inferred-cross-version-candidate`.

Action: 实现显式float32边界并保留分支顺序；检查正常、负值、零span及端点，不声称穷尽所有x87极端输入。

### R60-01-08 保留整圈角度

- [dnf-native-demo/src/resources.cpp:456-457](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 直接插值原角度，不走最短角。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:324-328](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 离散角度绘制，未处理连续整圈。

Source contract: 0→6.28中点约3.14，不归一化；60US flybomb.ani为真实来源样本。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `existing-native-demo-choice; inferred-cross-version-for-player`.

Action: 保留主工程直接角度插值；独立播放器接同算法，不加入最短角优化。

### R60-01-09 关闭插值、冻结与ended

- [dnf-native-demo/src/resources.cpp:406](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - frameOverride直接选固定帧。
- [dnf-native-demo/src/resources.cpp:447-450](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 固定帧localTime=0且关闭插值；非循环末帧无下一目标。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:313-316](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 整个播放器为离散采样，没有独立插值开关。

Source contract: 60US updater检查源插值标记与ended；冻结参考主体不执行时间插值，预览支持显式关闭。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `generic-preview-control; native-updater-applicability-unverified`.

Action: 共用接口明确requested/enabled/frozen/ended，逐项对照；角色poseFrame带来的持续冻结另归R60-03。

### R60-01-10 末帧、循环边界与零延时

- [dnf-native-demo/src/resources.cpp:385-397](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 按累计delay跳过零时长帧，非循环返回末帧。
- [dnf-native-demo/src/resources.cpp:402-412](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 循环先fmod再查帧。
- [dnf-native-demo/src/resources.cpp:445-450](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 循环末帧next=0；单帧next同当前时不做插值。
- [rep-player-1031-pvf/src/pvf_animation.cpp:292-303](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp) - 已有零delay、fmod和非循环保留末帧的离散查帧。

Source contract: 60US非循环ended保留末帧；循环末帧目标可为第0帧。finishcircle1真实首帧DELAY=0，时间0选第1帧。

Evidence: `E60-INTERPOLATION`, `E60-TIMELINE`, `E60-TRANSFORM`.

60US: `confirmed-static-with-stated-outer-lifecycle-limits`; 1031: `current-resource-sampler-fact; full-native-clock-unverified`.

Action: 沿用现有资源查帧；回归末帧/循环/单帧/零delay。外部loop选择、时钟和清理仍需R60-03独立核实。

### R60-01-11 图片、效果、碰撞盒保持离散和每帧默认

- [dnf-native-demo/src/resources.cpp:414-432](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 每帧由globals+本帧属性重建，图片帧和blend在插值外。
- [dnf-native-demo/src/resources.cpp:451-458](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - 只混合五类连续量，不混合boxes。
- [rep-player-1031-pvf/src/pvf_animation.cpp:250-264](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp) - 逐帧从defaults+globals开始，原boxes带offset/raw保留。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:336-338](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 攻击/受击几何使用当前源帧boxes。

Source contract: 60US A24950不修改image pointer/image frame/effect/boxes；46E390与66F900证据保留默认与snapshot拷贝。

Evidence: `E60-INTERPOLATION`, `E60-NATIVE-VECTORS`.

60US: `confirmed-static-plus-local-native-vectors`; 1031: `current-source-model-fact; no-new-native-claim`.

Action: 只新增render pose，不改源ANI/box/event；未知字段继续保留与诊断。

### R60-01-12 负弧度旋转

- [dnf-native-demo/src/renderer.cpp:314-319](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 源弧度转正角度后送imageQuad。
- [dnf-native-demo/include/dnf/geometry.hpp:19-27](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/geometry.hpp) - 使用正角sin/cos。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:324-328](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 同样使用源正角旋转。

Source contract: 60US A29133直接读float弧度，ADD3F6..ADD402 fchs后送矩阵；应rotate(-sourceRadians)。

Evidence: `E60-TRANSFORM`.

60US: `confirmed-static`; 1031: `inferred-cross-version-candidate`.

Action: profile决定角度符号；不改原字节，不把60US地址写入1031运行时。

### R60-01-13 非均匀缩放与朝向次序

- [dnf-native-demo/include/dnf/geometry.hpp:24-27](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/geometry.hpp) - 先局部XY乘scale，再旋转，最后仅X乘facing。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:326-328](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 裁剪顶点先分别缩放再旋转，facing作用于最终X。

Source contract: 60US ADD46D..ADD494对旋转矩阵输出X/Y分别乘rateX/rateY；朝向反映rateX符号。非均匀缩放时运算不交换。

Evidence: `E60-TRANSFORM`.

60US: `confirmed-static`; 1031: `inferred-cross-version-candidate`.

Action: 统一四顶点接口按profile执行scale(output)*rotate(-angle)，覆盖负rate、非均匀rate和双朝向。

### R60-01-14 IMAGE POS与IMG裁剪原点

- [dnf-native-demo/include/dnf/geometry.hpp:24-27](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/geometry.hpp) - IMAGE POS与crop相加后一起缩放/旋转，偏移参与通用变换。
- [dnf-native-demo/src/renderer.cpp:252-253](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 传IMG crop与ANI offset至quad。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:326-328](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 只变换crop；ANI IMAGE POS在变换外叠加。

Source contract: 60US正常原点pivot=-IMAGE POS，crop-pivot变换后加position+pivot；等价于把IMAGE POS和crop一起变换。其他居中原点模式未恢复。

Evidence: `E60-TRANSFORM`.

60US: `confirmed-static-normal-origin-only`; 1031: `existing-native-demo-offset-model; inferred-cross-version-for-player`.

Action: 保留主工程偏移参与变换的通道；播放器改用同quad接口。不得宣称居中原点/全局裁剪模式完成。

### R60-01-15 RGBA顶点调制与alpha仅乘一次

- [dnf-native-demo/src/renderer.cpp:270-281](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 清纹理历史modulation，以四顶点色调制；alphaMultiplier在animation边界应用。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:320-334](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - f.rgba/255写入每个顶点，交rep GPU绘制。

Source contract: 60US RGBA低8bit打包后R/B交换送diffuse，纹理stage MODULATE；texture alpha*frame alpha只应用一次。

Evidence: `E60-TRANSFORM`.

60US: `confirmed-static`; 1031: `current-vertex-modulation-fact; GPU-pixel-parity-unverified`.

Action: 复用现有顶点调制路径，只替换采样后的pose颜色；alpha mask、死亡白剪影等用户策略保留单独来源。

### R60-01-16 NONE与LINEARDODGE混合证据边界

- [dnf-native-demo/src/renderer.cpp:264-268](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - effect1和2都映射SDL ADD并诊断为approximation；NONE使用alpha blend。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:321-322](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - additive开关下1/2都映射material.blend=2，注释明确1031公式未恢复。

Source contract: 60US effect2有D3D8 SRCALPHA/ONE静态证据，NONE是SRCALPHA/INVSRCALPHA。1031现有合同只确证枚举，不确证DODGE/LINEARDODGE的公式。

Evidence: `E60-BLEND`, `E1031-RESOURCE`.

60US: `confirmed-static-for-NONE-and-LINEARDODGE-only`; 1031: `inferred-cross-version-for-effect2; effect1-still-unknown`.

Action: 候选effect2可采用60US公式但必须标1031推断；effect1保持单独未知/比较策略，不能两者批量confirmed。

### R60-01-17 未知效果与1031 binary effect6冲突

- [dnf-native-demo/src/resources.cpp:285-296](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - binary effect6额外读两个i16，未按本版本EXE拒绝。
- [rep-player-1031-pvf/src/pvf_animation.cpp:127-136](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp) - 同样把effect6解成额外两个i16。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:117-118](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 大于2效果诊断，使用raw sprite比较。

Source contract: 1031本身109FC99比较6，109FCA9清返回值并跳failure；没有再读两个i16。文本SPACEDISTORT另消费两个整数并写effect2，不能混为binary支持。60US只恢复0/2。

Evidence: `E1031-RESOURCE`, `E60-BLEND`.

60US: `other-effects-unknown`; 1031: `confirmed-static-binary6-rejection; current-extension-inferred`.

Action: 保留原字节与扩展来源标记，不能宣称native effect6已支持；后续版本适配应拒绝或显式扩展策略。此次渲染候选不得偷偷把它升级为支持。

### R60-01-18 源DELAY与实际原生时钟/速率

- [dnf-native-demo/src/resources.cpp:399-412](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) - samplePose接受资源毫秒并按原duration查帧，没有内部原生percent速率映射。
- [dnf-native-demo/src/renderer.cpp:477-484](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 使用ms-animStart，另传poseFrame覆盖。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:162](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - ALS birth由源frame.startMs/ratio计算。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:315-316](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - local*animationRate查帧；ratio预览不等于逐帧trunc原生deadline。

Source contract: 60US保留deadline-=trunc(delay/rate*-100)原算术，预览仍仅rate100。1031独立5BA3A0确证trunc(float(rawDelay)*100/ratePercent)，变速还须重定位并递归附层。两版本算术次序不可直接合并。

Evidence: `E60-TIMELINE`, `E1031-RESOURCE`.

60US: `confirmed-static-local-deadline-contract; full-actor-clock-unknown`; 1031: `confirmed-static-percent-delay-contract; target-full-clock-incomplete`.

Action: R60-02仅称资源时钟渲染候选；R60-03单独做Clock/Rate/Instance，保留1031百分比边界、变速连续性、pause/hit pause未知。

### R60-01-19 身体/装备共享帧与附层独立时间映射

- [dnf-native-demo/src/renderer.cpp:480-514](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 身体/装备均传p.poseFrame；override使所有层的插值关闭。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:170-177](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - ALS child按显式birth继承rate并独立查帧，属于比较策略。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:315-316](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 每track局部clock，不是原生live child实例。

Source contract: 60US timeline.js装备用身体帧/延时是该预览局部合同。1031 109CC10/109CA20确认child按自己的累计delay查共同时间，不能统一复制父frame；延迟add双重reset后的净birthOffset仍未知。

Evidence: `E60-TIMELINE-CODE`, `E1031-RESOURCE`.

60US: `preview-equipment-policy-with-native-clock-limit`; 1031: `confirmed-static-own-child-delay; equipment-full-binding-and-delayed-birth-unknown`.

Action: 区分装备层与ALS附层；不要把60US装备索引规则推广到所有1031child。R60-03显式parent clock/birth策略和插值进度。

### R60-01-20 末帧保留与外层销毁分离

- [dnf-native-demo/src/effect_plan.cpp:29-33](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/effect_plan.cpp) - bounded effect plan统一把track截到一个ANI duration或父limit。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:64-69](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 特效role可在非循环ANI末端自动失活。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:195](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - draw-only生命周期人为限制一遍源ANI，并明确诊断未恢复native销毁。

Source contract: 60US A27DC0 ended保留末帧，5CE7A0再由特定外层控制器请求移除；不能把任何ANI ended等同对象销毁。

Evidence: `E60-TIMELINE`.

60US: `confirmed-static-local-ANI-and-releasewave-contract`; 1031: `bounded-inspection-policy; full-native-lifecycle-unverified`.

Action: 保留有限预览防泄漏策略并明确标签；R60-03/04分别表达ANI ended、detach、remove request和移除完成，不批量套releasewave控制器。

### R60-01-21 附层顺序与世界排序

- [dnf-native-demo/src/renderer.cpp:507-515](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 按appearance有序层与bodyOrder绘制。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:224-225](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 所有scene tracks按layer stable_sort。
- [rep-player-1031-pvf/src/pvf_preview_scene.cpp:350-364](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) - 怪物先绘制，再遍历tracks；不是通用世界Y排序。

Source contract: 60US attachment key升序，负key在主体前非负在后；1031 addLayerAnimation也按layer升序。两者都不证明全世界深度排序或所有装备顺序已恢复。

Evidence: `E60-TIMELINE`, `E1031-RESOURCE`.

60US: `confirmed-static-local-attachment-order`; 1031: `confirmed-static-ALS-layer-order; full-world-order-unverified`.

Action: 复用有序局部挂载模型，保留同层原序；世界Y排序、独立draw-only分类、装备原生全层序另列缺口。

### R60-01-22 PVP非文字UI与菜单/商城字体目标

- [dnf-native-demo/src/renderer.cpp:337-356](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - 使用当前GDI或stb字体mask与重建描边；并非目标字形像素已验收。
- [dnf-native-demo/src/renderer.cpp:442-448](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) - fontReport明确PC_pixel_parity=false。
- [rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md:58-88](../../rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md) - 现有报告已记录REP文字opcode→glyph链、客户端字体身份、Tahoma回退、目标词和未核实样式。

Source contract: 本次60US名称和渲染证据没有恢复原UI/字体。用户只指定菜单、商城两个词为字体目标；PVP UI继续参考有序非文字绘制。86JP代表54 REP的723条文字引用未包含目标词，该有界阴性结果不能扩大到全部录像。

Evidence: `E60-NAMES`, `E1031-UI-SCOPE`.

60US: `native-UI-font-unknown`; 1031: `user-designated-glyph-target; original-font-call-size-baseline-outline-unknown`.

Action: 后续以菜单/商城分别记录字体文件hash、字号/字重、基线、字距、描边/颜色和像素；其他文字暂不参考，不能拿系统字体成功显示当复刻完成。

## Evidence ledger

Every source/evidence file hash, raw byte range, original evidence ID, per-reference excerpt hash and EXE/PVF binding is retained in the companion [JSON](R60-01-ADOPTION-MATRIX.json).

### E60-TRANSFORM

- [reverse-60us/releases/20261020-01/analysis/combat_render/transform/evidence-index.json](../../reverse-60us/releases/20261020-01/analysis/combat_render/transform/evidence-index.json)
- SHA256: `3433a102399c21561afa9e836ddd3707e70f8319546d09a69530b9b6847a63c6`.
- Kind: `static-PE-bytes-and-REA`.
- Evidence ID: `ev_d7062f931a7f0b1868e46746fc93b88b6e853b7425cc61669a2f0dfa0f2a7aad`.
- Evidence ID: `ev_9f2dc5bde894b9592c30b1abdc470d98945f00059383e3a715de9dad92b24a20`.
- Evidence ID: `ev_0936b3ddf6298ca577f5f4591db312b782b62e44eff851b1c23b6098208d0e3d`.
- Evidence ID: `ev_4e8256395d0ddabfdbf0a9055c0a47e5dacd6d9d9f0932e93e92e6d19df9e3f0`.

### E60-INTERPOLATION

- [reverse-60us/releases/20261020-01/analysis/combat_render/interpolation/evidence-index.json](../../reverse-60us/releases/20261020-01/analysis/combat_render/interpolation/evidence-index.json)
- SHA256: `0bf3edb1d59455198a82203aae8063a276ce0a59717b986d828c3c7f7b5b32e4`.
- Kind: `static-PE-bytes-REA-and-local-native-verification`.
- Evidence ID: `ev_3ffcf83d3186fc6604fc0875302c104b32e7bdc08b8526c04bf2efce617a7f71`.
- Evidence ID: `ev_be0751c3ea40e8f82eb388c82a49c0e09455628824714bd49160a78f9e89e194`.
- Evidence ID: `ev_660c8d1343152f17a854226f940dba06271ccccbdf35b49ada97793a9a5c3aa3`.

### E60-NATIVE-VECTORS

- [reverse-60us/releases/20261020-01/analysis/combat_render/interpolation/native-vectors.json](../../reverse-60us/releases/20261020-01/analysis/combat_render/interpolation/native-vectors.json)
- SHA256: `718ef24816382b08fd4f575ff7ca6a78c4816ae10d286d320245c5fc4926da58`.
- Kind: `retained-local-native-instruction-output`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

### E60-TIMELINE

- [reverse-60us/releases/20261020-01/analysis/combat_timeline/evidence-index.json](../../reverse-60us/releases/20261020-01/analysis/combat_timeline/evidence-index.json)
- SHA256: `0934fe078feae3482e3d06cb94ea7e655e5a224d8f5850e84bfa380deed7046a`.
- Kind: `static-PE-bytes-and-REA`.
- Evidence ID: `ev_eb4d3736a0582b425f42d433493c70e1ca2b7cd272717881ded62b1bbfaee4c2`.

### E60-BLEND

- [reverse-60us/releases/20261020-01/analysis/combat_render/evidence-index.json](../../reverse-60us/releases/20261020-01/analysis/combat_render/evidence-index.json)
- SHA256: `3ee333070fed07e81e542d5cd50f921d2eb2aa1920b60591076295412a4375b2`.
- Kind: `static-PE-bytes-and-external-D3D8-API-reference`.
- Evidence ID: `ev_9f2dc5bde894b9592c30b1abdc470d98945f00059383e3a715de9dad92b24a20`.
- Evidence ID: `ev_7a6f17a3eedff96bbbdf6e7c3189856e6770fd99208a7777178d9bb46ea0790e`.
- Evidence ID: `ev_4e8256395d0ddabfdbf0a9055c0a47e5dacd6d9d9f0932e93e92e6d19df9e3f0`.

### E60-NAMES

- [reverse-60us/releases/20261020-01/analysis/combat_catalog/skill-name-resolution.json](../../reverse-60us/releases/20261020-01/analysis/combat_catalog/skill-name-resolution.json)
- SHA256: `616aca5364c71444e07bf3bc3909d6c2967e6a3a48ce78d59fd3fc7928236af0`.
- Kind: `current-PVF-source-data`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

### E60-CATALOG-CODE

- [reverse-60us/releases/20261020-01/combat-preview/catalog.py](../../reverse-60us/releases/20261020-01/combat-preview/catalog.py)
- SHA256: `b9b2430c0d4bb187c0ee09a2b53bd7d1bb5a51244966632ea5b7f65a61a76bc2`.
- Kind: `reference-source-implementation`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

### E60-TIMELINE-CODE

- [reverse-60us/releases/20261020-01/combat-preview/web/timeline.js](../../reverse-60us/releases/20261020-01/combat-preview/web/timeline.js)
- SHA256: `49c3fe0aab14a5161d68a843f055409bb6b6da67b108b242969bb083eba7b106`.
- Kind: `reference-preview-policy-not-complete-native-clock`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

### E1031-RESOURCE

- [dnf-native-demo/reports/combat-native-reverse/resource-render/evidence-manifest.json](../../dnf-native-demo/reports/combat-native-reverse/resource-render/evidence-manifest.json)
- SHA256: `bb651df2efa62409344844f4ec0e5eecf45b58aa0b93a7dfbd5864f754c134d9`.
- Kind: `1031-static-PE-byte-segment-manifest`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

### E1031-UI-SCOPE

- [rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md](../../rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md)
- SHA256: `5edf7cae134defb493d49b89dbbb7fc19627ba18d309718658830e230fa94fc6`.
- Kind: `bounded-86JP-PVP-analysis-and-user-designated-font-target`.
- No REA Evidence ID is asserted for this source-data/document record; use the exact file/hash and retained offsets.

## Frozen source ledger

| Key | Snapshot file | SHA256 |
|---|---|---|
| native-resources | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/resources.cpp) | `610975276b601c6236a39b5f7cd8546c8d1ee263a44a7cad1ff8d645aba59193` |
| native-resources-hpp | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/resources.hpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/resources.hpp) | `99a6ac04b9ef01bdf28bec4a6f5bb1904de05732a45be9601676c70795ffa375` |
| native-renderer | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/renderer.cpp) | `97407e9d5b87e77393f0892e48ca536cfe9753bbee2155cb4f7d755ea4458a76` |
| native-geometry | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/geometry.hpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/include/dnf/geometry.hpp) | `cd4329234a1f08903899cefe7a1fadb11e39c5fbae313ffd89f6e2b471591115` |
| native-hud | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/hud.cpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/hud.cpp) | `78cc0a013f47fe20dfe5ca79b30d75e8cf5a6fde94aa1b5fa8cd972fb995b975` |
| native-effect-plan | [dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/effect_plan.cpp](../../dnf-native-demo/checkpoints/20261018T201028867867Z-source-camera-nut-skill-feedback/source/src/effect_plan.cpp) | `71208cb8da791ca055a73f9559838a37c43c4e3beedaca1e9b93eb0663227695` |
| player-catalog | [rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_catalog.cpp](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_catalog.cpp) | `e600b012fab977130fa762f84e8bcee63097028e2503b0e694192f0c137ede9e` |
| player-script | [rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_script_preview.cpp](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_script_preview.cpp) | `d2611f74ffecf60bf7377de275a539de0fa68f4343aac82eb948a3c0b56d091e` |
| player-template | [rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_template_preview.cpp](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_template_preview.cpp) | `459c6cc5dcc4c6c71541fad9ab092d28f0473e98ea51d19827386157368db673` |
| player-animation | [rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_animation.cpp) | `b84c5fe3cbb33ce7c1dbfed912d4fd72cab412f964058a7d239582b065f136f2` |
| player-scene | [rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp](../../rep-player-1031-pvf-checkpoints/node-05-cross-character-templates-20261019-171855/source/src/pvf_preview_scene.cpp) | `84c5b6f08378b14b1cca1f1e98192ac7a5aa3972b10ba7d92294621c8be0bb63` |
| player-font-scope | [rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md](../../rep-player-1031-pvf/docs/PVP_UI_AND_FONT_SCOPE.md) | `5edf7cae134defb493d49b89dbbb7fc19627ba18d309718658830e230fa94fc6` |

## Verification and continuation

22 rows, 67 source ranges, 12 source files and 10 evidence records validated; 8 release evidence hashes match the immutable package manifest.

Retained local-native vectors: 24 matches, 0 mismatches (x87 64/53-bit precision); these were read from the release, not rerun or observed in the original game.

独立构建的源码/EXE manifest、当前源行号、正常和负值/末帧/循环/关闭插值原生向量、实际渲染消费者、用户操作步骤由R60-02报告记录。

保留1031 legacy比较路径；60US原证据算法迁往1031标inferred，不能设置native_controller_verified=true。

1031十个非缔造者职业及实际分支、觉醒、全部技能门槛继续保留。

R60-03 must close actor clock/rate, per-instance children, selective events and end/detach/removal semantics. PVP non-text UI and the two user-designated font targets remain open; damage is still later work.
