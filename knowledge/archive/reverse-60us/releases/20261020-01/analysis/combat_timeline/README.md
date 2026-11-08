# 60US ANI 结束与附层顺序

当前 `A27DC0` 检查 ANI `+13A`，已为1时不再推进；当前帧为最后帧且 `+130==0` 时写 `+13A=1`，不把 frame index 清零或隐藏。大步追赶路径也先选择末帧，再写 ended。因此预览中的普通非循环视觉轨保留末帧；移除或解除挂载由外层控制器另行决定。

裂波斩攻击对象有明确外层结束消费者：`5CE7A0` 先通用 tick，再检查 current ANI 的 `+13A` 和对象 `+1E8`，调用 `+164` 请求移除。预览把这种实体移除与纯 ANI 末帧保留区分开；源 DELAY 时间400之后停止其几何盒是本地资源模型，原客户端消息及场景清理可能延后，尚无实机调度观测。

帧推进的 deadline `+12C` 不能凭反编译中的减法判断为反向时钟。`A27932` 除 ANI rate `+134`，`A27938` 乘 **DF053C 的原生 float32 -100.0**，`A2793E` 截断，最后从 deadline 减去结果，保留原式 `deadline -= trunc(delay / rate * -100)`。初始化/刷新 rate 的浮点次序有差别，`rate=100` 的源 DELAY 模型不等同完整角色攻速；原始指令数值核对见 [combat_motion](../combat_motion/)。

Entity 层挂载 `49B7B0` 将首参数存 attachment record key，按其大小插入列表。`49A359` 先绘制负 key 部分，主体之后 `49A5B7` 绘制余下部分；各自调用 `A26990`。这支持裂波斩第二视觉 key -1 在主体前、第一视觉 key +1 在主体后。它不是统一的背景/前景语义，也不等同世界 Y 排序。当前 Canvas 对这个局部 attachment 顺序进行了重建。

[evidence-index.json](evidence-index.json) 绑定原 PE、原切片与 REA060 Evidence。此目录没有证明全部 ANI 回调、ACT 帧事件、hit pause、视觉 detach 或原游戏像素一致性。
