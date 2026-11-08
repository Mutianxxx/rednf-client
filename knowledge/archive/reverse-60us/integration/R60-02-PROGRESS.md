# R60-02：名称、图标与通用渲染候选

2026-10-20。R60-01差异审查已完成；本节点已经实现并编译两份隔离候选。60US原生算术/变换用于1031时标为 `inferred60us1031`，可切回 `legacy1031`。本节点不宣称恢复1031原生技能控制器、原生时钟或全职业beta。

## 打开预览

独立播放器启动器：`D:\dnf-rebuild\rep-player-1031-pvf\Start-R60-02.cmd`。

EXE：`D:\dnf-rebuild\rep-player-1031-pvf\candidate-r60-02-final\build\rep_pvf_preview.exe`，SHA256 `5ce28085505260006a2d5664920e681109b6d7818ac74ceccaac8540ea647ea7`。旧 `Start-1031.cmd` 及节点05产物未覆盖。

主客户端EXE：`D:\dnf-rebuild\dnf-native-demo\cache\r60-02-build\dnf_native.exe`，SHA256 `128fdb1a2a3b533f973179061a8a5bcaa9ef06900592c0f71b2bd05ac0d608eb`。本节点备份内 `runtime/native/Play-R60-02.cmd` 指定独立存档/报告及推断渲染策略；普通直接启动仍默认legacy，避免无标记改变旧行为。它不导入独立播放器的技能模板。

## 实际接入

- 两工程共用 `reverse-60us/integration/include/dnf_ani_render.hpp`。位置/颜色对完整插值结果向零截断，RGBA保留低8位；rate和角度落float32，保留整圈角度；图片、效果枚举、碰撞框和事件保持离散。
- inferred普通原点链为 `T(actorX,actorY-Z) * S(direction*rateX,rateY) * R(-radians) * T(IMAGE POS) * IMG crop`。源原点、延时、角度和裁剪不改写；generic sprite、TIL和PTL度数接口保持legacy。
- RGBA由实际D3D/SDL顶点调制，alpha只乘一次。inferred只确认NONE及LINEARDODGE(enum2)的60US局部合同，其他effect明确诊断并用普通透明回退；旧effect1/2加色比较路径保留。
- 独立播放器新增渲染策略和源插值开关；身体、效果、被动对象、ALS子轨和怪物共用采样/变换入口。切换不推进场景时间、不改变几何接触或事件记录。
- 模板SKL `[icon]` 的首对原路径/帧实际加载并绘制，导出源tag序号与IMG提供方/hash/偏移；完整四值仍在SKL原bytes/token中。当前仅模板条目显示技能图标，四个来源流程及raw ANI没有伪造图标。loaded表示成功取得Frame，不等于像素验收。
- 名称继续各版本来源链：1031二进制n_string.lst与有序token，60US独立文本字符串/编码链。688项60US主名/副名已核对，不使用现代译名重绑技能ID。

## 自动验证与实测边界

1. 冻结24条原指令输出、C++17便携合同145项通过；8份真实1031 ANI的独立适配353项通过。记录：`integration/validation/render-contract-20261020-010654-864068-54da53f6/manifest.json`。
2. 最终独立EXE离屏D3D11检查48项通过，包括真实GPU读回的普通/LINEARDODGE RGBA、alpha只乘一次、插值/legacy比较及重播确定性。隐藏GUI78帧通过，包含十角色实际选择、四流程、朝向、定位/单步、渲染和插值开关。
3. 四个既有来源流程184项通过；十角色1677模板全量回归24104项通过，64个代表场景离屏检查通过。最终来源/产物身份见本目录 `R60-02-VERIFICATION.json`；模板可播放不等于该技能完整实现，原10条资源缺口不删除。
4. 主工程完整核心/音频回归通过；同EXE来源profile审计通过。额外3秒SDL dummy渲染smoke exit0、render_errors为空且报告记录inferred策略。这是部分诊断，不是完整15种受击/死亡fixture跑完或画面验收。
5. 688项60US名称与icon字段身份审计通过；没有宣称688图标全部像素验收。独立代码审查三项交付/诊断问题已修复，见 `R60-02-REVIEW.md`。

前台画面、声音、手感和原游戏动态对照均待用户；不因自动检查通过改成原生confirmed。PVP非文字UI及【菜单】【商城】字体目标继续保留，当前没有新增像素级UI/字体完成声明。

## 用户比较步骤

1. 运行 `Start-R60-02.cmd`，默认十角色模板模式；任选同一技能，暂停并拖动时间轴。
2. 下方切换“60US渲染算法→1031（推断候选）”与“原1031绘制（对照）”，观察旋转/非均匀缩放/偏移；源帧有INTERPOLATION时再切“源帧插值”。源帧无此标记应保持离散。
3. ANI资源浏览中可筛选 `illusionslash`，逐帧比较；切换左右朝向、缩放和循环，留意原点和最后一帧。十角色模板的技能图标应出现在画布左上。
4. 四来源流程仍单独显示；红/蓝框仅为源XYZ盒投影。“接触触发受击”是比较fixture，未证明原生命中接受/伤害。
5. 用“导出来源/反馈”保存当前策略和源身份，说明角色/技能、时刻、朝向以及与旧策略/原版差异。新候选自己的validation/runtime接收报告，旧候选不改。

## 备份与恢复

各节点备份位于 `D:\dnf-rebuild\reverse-60us\checkpoints\`，目录内含本进度、源码、编译产物、报告和逐文件SHA256 manifest。R60-02源布局为 `source/{dnf-native-demo,rep-player-1031-pvf,reverse-60us}`，保留共享header相对include；runtime独立，用户原存档不复制或覆盖。原始PVF/NPK及D盘第三方编译器/SDK作为外部只读依赖，不打包客户端资料。

恢复先读 `reverse-60us/CURRENT_TASK.md` 和 `PORTING_PLAN.md`。R60-03原生时钟/附层已完成差异方案，03A便携算术/游标正在实现；尚未接入身体/装备/攻击盒/声音统一快照，不计R60-03完成。后续顺序保持R60-03→R60-04→R60-05，R60-06伤害后置，最终1031十职业范围不缩减。
