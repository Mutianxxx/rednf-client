# ANI 动态、死亡与目标血条（2026-10-17）

本页记录本轮代码和来源边界。原 PC 客户端、PVF、官方注释文件与研究数据库保持只读；未参考旧 GBA 实现或 DFQ UI。单元检查通过也不能代表整体验收通过，实际 SDL 对照结果由运行报告另记。

## 连续采样与单位

`Animation::samplePose(double ms, bool loop, int frameOverride=-1)` 是不依赖 SDL 的采样接口。每帧先由 global 和默认值生成有效状态，再覆盖该帧的属性；不继承上一帧的缺省 RGBA/scale。属性10启用时，在该帧原始毫秒区间内向下一帧插值 x/y、scale、rotation、RGBA；图片帧、混合、碰撞框与事件保持离散。循环尾接首帧，非循环末帧保持；负时间钳到起点，零时长帧跳过，显式 poseFrame 不插值。直接线性角度插值保留作者写入的整圈旋转，不做最短圆弧改写。

右门原 `passiveobject/mapobject/pathgate/act1/animation/granflorisrightlight.ani` 为两帧各500ms：首帧alpha0、次帧省略RGBA而恢复255，两帧都含interpolation；循环为0→255→0。旧代码离散选帧导致半秒开关。本轮通用采样同样应用到赛利亚 gatepillarlight/gateoutlight、艾尔文 elvenlight1 与 serialight00/01，不为每个光源新增手写正弦周期。

ANI rotation 原浮点保留为 `rotationRadians`，在 Renderer 调用 geometry 的角度接口前用 `radiansToDegrees` 转换一次。支持依据为本客户端 `monsterdieflashyoung.ani` 的6.28及 `monsterdiepiece.ani` 的4.0，以及本地解析器字段布局；原官方 ANI 注释文件为空，不能称此单位由官方样例直接定义。`imageQuad` 和显式 sprite API 仍用角度，保留旧调用兼容性。新增测试用π/2→90°检查后端边界及完整6.28旋转插值。

## 绘制模式与未支持项

`Renderer::animation` 使用采样结果，支持带符号scale、RGBA、旋转、FLIP和IMG crop。LINEARDODGE采用SDL ADD；DODGE也只能暂用ADD，但会写入 `Renderer::unsupported`，不再静默等同。DARK/XOR/SPACEDISTORT用显式报告的普通透明混合回退；MONOCHROME使用保留源alpha的纯色纹理。完整PC混合公式尚无同步金标。

SHADOW、COORD、SPECTRUM、局部LOOP_START/END、CLIP、OPERATION等未消费的绘制控制进入 `unsupported`。该数组应由主进程写运行报告。原 PLAY_SOUND/SET_FLAG 属事件消费者，不能因渲染没消费便从源模型删除。现有ANI sidecar ALS仍未通用接入；本轮三技能相关目录没有ALS，缺少的是OBJ附层和硬编码阶段。完整ALS需要另按unique name和父帧事件实现。

`Renderer::effect(const Effect&, ms, interpolation, cameraX, cameraY)` 独立使用 `loop` 与 `animationOffset`，不再用skill25猜循环、用skill58猜时间。父附着、局部运动由模拟维护，渲染不再次叠offset。主队列读取 `layer=-100`地面、`-1`父后、`+1`父前和 `parentId`；这些是重建运行时接口，不写回源ANI/OBJ。

技能配层源：Khazan OBJ保留Khazan1/2、appear1/2、stay/disappear；GoreCross OBJ主1+附2(-1)，3/4是附加状态；HopSmashSub OBJ为Front1+Front2(+1)，Back1/2须按控制器用途核对。未转职不可无条件获得SKL注明需血气旺盛的冲击波。原AVI只作为阶段/观感辅助，不能把预览中的资格、装备或数值当当前角色规则。

## 怪物死亡

`Renderer::monster(Pvf&, const Actor&, ms, interpolation, cameraX, cameraY)` 接受 `ActorLife::Alive/Dying/DeathEffect/Removed`。控制器持有 `animationPath`、`deathPoseTime`、`deathStart`、`lifeStart`、`hitFlashUntil`；渲染冻结致死姿态，保留实际IMG crop与alpha。纯白纹理以源图每像素alpha为遮罩，RGB写255，仅在纹理缓存首次请求时建立；透明轮廓外不会变成白色矩形，且不修改原图。

DeathEffect阶段用实际死者IMG的5×2裁片、确定性散射与白色淡出，父队列只画一份。**5×2切分、散射速度和320ms退场是明确的重建近似，不能称已恢复原PC通用碎尸算法。** 原 `MonsterDiePiece.ani` 无资源/图像而有旋转与淡出，支持运行时注入图像的方向，但未证明原始分片策略。本轮裁片保留其源图标识；PTL生命、源动画时间与控制器生命分别存留，不改写原数据。

原公用死亡数据位于 `monster/common/animation/monsterdie*.ani`、`monster/common/particle/monsterdie*.ptl`。flash原200ms，scale0.5→2、alpha255→0；piece PTL最大10、初速400/400、重力1500、生命3000ms。哥布林两MOB均`[die effect]0 1 0`。官方 `monstersample.mob:169–178` 明确第三项是禁用位：1碎片、2血、4烟、8闪光；0全显示，第二项为碎片颜色。当前轮廓碎片并未完整实现所有分级/颜色/血烟规则，不能把0,1,0当只要求白色。

用户授权的DFQ死亡机制只用于辅助：`source/actor/service/battle.lua::DieTick/Flash`白色pureColor由255在175ms退0；`source/actor/system/drawing.lua:176`及`asset/shader/white.sc`重画源alpha内纯色；另生成11帧×50ms预制death/normal与flash。未发现其按死者贴图实时切块的实现，未读取其UI模块/资源。175ms是DFQ参数，非PC已验证常数。

## 目标血条

`TargetHealthState` 是无SDL显示状态；`TargetHud::hit(actor, now, previousHp)`接受包括致死在内的命中，`draw(renderer,pvf,now)`绘制，换房调用reset。若事件给出实际伤害，可用min(maxHp,hp+value)恢复上一显示血量。模型不改真实HP。

原参考截图1000×750归一800×600后，左上肖像约(4,98)、目标框宽140。原 `interface/newstyle/windows/monster_hp/monster_hp.img` frame1是626×32边框，frame2/3是597×9填充，本轮保留角和边框厚度、只伸缩中段为compact布局。肖像读取MOB `[face image]`（哥布林0、投掷哥布林4）。普通红条、首领橙条；损失段先用暗色半透明显示，再收缩到当前HP。180ms保持+420ms收缩、致死700ms显示及最后180ms淡出均为重建显示参数，待原实录逐帧标定。无命中不显示本目标，目标切换和场景切换清理旧尾血。

源图联系表 `reports/dynamics/render-target-source.png` 是源IMG导出，不是实际SDL效果；compact截图原文件仍只读。原先顶部600px长血条的尺寸与其IMG相符，问题不是解码少像素，而是目标生命周期和布局不符。不能仅因另有bossmonsterhp_cn的名称就擅自换成该资源。

## 视频工具与证据

运行 `tools/reference_videos.py` 只读取原客户端/实录，在 `reports/dynamics/render-reference-videos` 写派生资料：13基础技能原AVI的源hash、纯解密AVI及hash、square-pixel展示MP4及hash、每0.1秒帧；另保存用户150.921966秒800×600/55fps实录的每1秒采样和源hash。原文件不修改。`decode_neople`只做32B包装/XOR，检查RIFF长度；不会改纯解密AVI的MPEG1 aspect或vprp。展示版本通过ffmpeg setsar=1重新编码，不能与解密字节混称。

已实际执行工具，13项加实录全部探测/采样成功；`manifest.json`保存精确probe。已查看三技能代表联系图和实录每10秒联系图；没有逐帧审完全部视频。客户端技能预览160×90、30000/1001fps；实录可见现代版本选角/创建等，与本地旧客户端布局存在版本差异，实录辅助不覆盖本地PVF来源。

`tests/test_animation_dynamics.cpp` 导出 `dnf::Json runAnimationDynamicsTests(Pvf&,Assets&)`，覆盖原门alpha周期、global/default复位、非循环末帧、显式帧、signed scale、连续/离散属性、弧度边界、源死亡flash与无图piece采样、未支持节点报告和血条生存状态。新增代码尚需主进程统一构建、实际前台截图/输入复核；文档不预写通过结果。

验收需覆盖门光至少完整周期、左右13技能与四武器、技能前中后和重施、地面/空中/同时死亡、换房清理、非致死/连击/换靶/一击杀/首领血条。至少800×600与1280×720，比较30/60/144/240渲染下相同模拟时刻；错误数组为空不是视觉正确证据。
