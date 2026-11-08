# R60-03：固定动画时钟与实际消费者

本节点实现可比较的时钟策略和实际身体/装备/攻击/声音/附层消费者。1031 使用 60US 算术与装备树合同仍是跨版本推断；不增加完整技能控制器数量，不声称恢复了原生 timer 通道或实机像素/音频等价性。精确构建、报告身份与最终自动状态见同目录 `R60-03-VERIFICATION.json`；该文件只有在全部所需检查通过后生成。

最终自动状态：**automated_pass_user_comparison_pending**。主工程285输入/84报告，完整核心/音频30项、实际clock消费者1541项/九实验职业往返、同EXE来源profile与3秒dummy部分smoke通过；主EXE SHA256 `7c12c8ca38b717d6da5ec2eeb16ac1f25df372a965e03de836417bfe174db4a0`。独立预览EXE SHA256 `d87406f0b25fa7a1cc303816ba9df71aa6025f68a4905ba46016ff2c91df69f3`，72项D3D、78帧隐藏GUI、184四流程及1677模板24104项通过。便携46向量/157项、ALS24项、adapter20项及精确输入/报告/二进制闭包均由最终清单重新核验。3秒fixture未跑完全部15生命周期，前台与听音仍待用户。

主工程增加独立 `--ani-clock-policy`：`legacy-scaled-local-age`（默认）、`source-delay-rate100`、`inferred60us-percent-deadlines`。渲染 profile 与 clock 分开选择。普通/冲刺/跳跃攻击以一次模拟 tick 的 frame/local/span/ended 驱动身体、同 motion 装备、攻击盒、声音和连击；正常 clock 动作不再用 poseFrame 冻结插值。实际有效攻速截断为 Sani 的映射明确为推断；安装与变化后的刷新保留不同表达式，暂停中延后刷新。

等待/移动等普通姿态有独立 source-rate100 根时钟，同 motion 装备子层用 min(body, child) decoded DELAY 视图和根 elapsed/rate 投影。子层原帧/图像/多余延时不改写。诊断显式 frameOverride 仍可冻结。九个实验职业使用同一个游标接口及自己的 CHR/ANI/ATK/EQU/LAY；其临时技能模板仍保留原分类。

效果实例分别声明位置跟随、玩家暂停绑定、独立 source-rate100 时钟及外层寿命。ALS 由父 FrameVisit 按原记录顺序执行 add/remove，同名替换与父移除清理后代，完整原 ALS bytes/token/path/hash/offset 保留。动态子层保留当前位置与剩余限时轨迹；ANI ended 只保持末帧，由外层 expires/remove 负责销毁。已有显式 animationOffset 跳转实例采用具名 legacy 回退并输出诊断，避免伪装成已恢复的原生 seek。

ACT 的 SourceMilliseconds/ExternalAnimationDelta 互斥接口继续使用；World 的 ACT 每 tick 只提交一次 source delta 或0，没有把百分 deadline elapsed 再当 source-age 二次缩放。怪物、物件、技能专用阶段仍保留各自 source-milliseconds 消费者，后续按 R60-04/05 核实，不能由普通攻击接入扩大原生恢复范围。普通存档仍取消瞬态，未改变 schema 为动作续演。

独立播放器增加时钟下拉选择。共享 Cursor 提交60Hz整数毫秒；播放倍率仅作用于墙钟提交，暂停不推进、单步一 tick、拖动确定性重建。主轨/ALS/怪物/命中特效按实际 clock 采样；两策略的几何接触时间分别计算。配方阶段/位移和命中特效出生位置仍是推断夹具；没有用装备 delay 视图支持冒充完整装备生成器。

自动验证包含：冻结46原生输出/157便携检查；真实/合成ALS帧事件24项；独立播放器clock adapter 20项及生产D3D/UI、四流程和十角色模板；主工程完整核心/音频，以及真实World暂停、改速、连击同tick首帧、武器盒、复制游标、不同渲染Hz/补tick、动态ALS和清理。九实验职业另覆盖待机→完整普攻→自然返回同一待机来源的所有权交接，防止旧游标跳过tick后复用。审查与修复依据见 `R60-03-REVIEW.md`。计数与最终状态以 VERIFICATION 为准。前台画面、听音、手感和原版动态对照仍待用户，自动检查不代替这些体验。

新增往返用例的首轮失败已保留：固定4秒测试预算不足以等待神枪手当前源ANI的9,999毫秒长尾帧。修正为按实际DELAY、安装速率和policy计算结束预算后，隔离真实World检查1541项、9/9实验职业通过；不裁剪来源、不强行idle、不改生产动作时长。最终完整核心/音频状态仍以VERIFICATION为准。播放器首轮183/184的失败也保留，修正的是复制轨道的显式重定时，原审计断言没有降低。

## 用户打开与比较

1. 双击 `D:\dnf-rebuild\rep-player-1031-pvf\Start-R60-03.cmd`。选择同一个技能，先暂停并拖动，切换“来源 delay / 旧 ratio”与“60US percent deadlines → 1031（推断）”；两种渲染策略可另外切换。
2. 用空格暂停、右箭头单步、R重播。检查动作、特效生成/移除、怪物反应和命中特效时间；在反馈中保留导出的来源/clock报告。模板仍不表示完整技能。
3. 主工程用本节点备份里的 `runtime/native/Play-R60-03.cmd`，它指定独立存档/报告并默认候选 clock+render。普通攻击、连续X、冲刺/跳跃攻击、切换有效攻速装备、受击停顿、F7暂停/单步及切图/切角色后重载分别测试。
4. 与R60-02备份比较；旧候选和原存档保持原位。记录自动通过、用户测试结果、原版动态比较三种状态。

## 备份与恢复

节点完成后 `reverse-60us/checkpoints/LATEST.json` 指向新的独立备份，包含源码、编译产物、进度、证据与逐文件SHA256。`source/{dnf-native-demo,rep-player-1031-pvf,reverse-60us}` 保留共享两个头文件的相对 include 布局；`runtime` 是直接预览/游玩的隔离入口，原始PVF/NPK及已安装D盘编译器/SDK为外部只读依赖。

主构建命令：`D:\ProgramData\anaconda3\python.exe -B -X utf8 dnf-native-demo\tools\build.py --build-dir cache/r60-03-build --test --test-dir cache/r60-03-tests-final-r4-checked`。独立播放器：`powershell -NoProfile -ExecutionPolicy Bypass -File rep-player-1031-pvf\build-preview.ps1 -BuildDirectory candidate-r60-03-final2\build`。新修改必须另建候选/备份，不覆盖历史节点。

下一项为R60-04：鬼斩→三段斩→波动爆发的逐来源阶段和视觉实例；保留1031技能32“波动爆发”与技能20地裂/NormalWave的区别。之后R60-05受击/死亡/场景破坏，再安排R60-06完整伤害扩展，1031十非Creator最终门槛不缩减。
