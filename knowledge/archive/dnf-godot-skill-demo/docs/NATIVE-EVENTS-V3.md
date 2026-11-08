# 1031 ANI 旗标游标与首帧派发

来源为主工程 `src/animation_events.cpp`、`include/dnf/animation_events.hpp` 和
`reports/combat-native-reverse/animation-events/README.md`。原生地址 `109FD9B`
读取 property23 的低16位；`108F370` 生产一个 pending word，`109C5EA` 调用生产器。
跨过多个事件帧只保留最后一个非 FFFF；空帧不清除；相同帧不重新装填；倒退只读取目的帧；
suppression 暂停生产但不清 pending。接受的控制器才清 word。

Godot 新增独立播放实例 `animation_event_cursor.gd`，保留源 int32 不变。
主程序宿主消费 VM 的实际 handler 接受收据，条件为 false 或不匹配时不丢 pending。
实际编译器把回调条件放在 ops 内的 if 中；实验桥以确实执行了叶子操作为接受，
不能因派发了回调却跳过全部分支就清除 pending。此桥没有声称还原原生 NUT 返回值协议。
安装／重置动作后，在同次请求中派发初始帧及零延迟前缀的旗标；
后续 tick 不重复。旗标造成连续重装动作有32次预算。初始安装在私有世界中准备，
成功才发布人物、效果、事件、实体ID与随机流；失败只发布故障诊断，不漏声音／震屏／出生事件，
原人物状态、MP/CD和更早已接受动作的独立效果不变。后续取消按动作实例ID清理自己的实体。
显式 set_frame 保留实例游标历史；倒退只检查目的帧，负数和越界索引报错。
这里没有将声音、攻击接触或全部世界更新强行提前到请求时执行。

两种策略明确区分：

- `source-callback-queue` 保留已有源程序回调策略，是现有 NUT 演示的默认值。
- `1031-single-pending` 使用恢复的原生生产器，并由受限 VM 已接受的 handler 确认消费。
  原生 Squirrel callback 与全部职业控制器的精确轮询顺序尚未恢复，因此该桥仍属可比较实验，
  不能把生产器的静态证据当作全部 NUT 行为等价。可在主界面切换，下一次施放生效。

策略由描述器、内容 profile 或主界面选择，不按职业、技能名或技能 ID 分派。
测试覆盖 skip／consume／sentinel／suppression／backward／reset、初始帧、条件拒绝、
跨帧策略差异及循环故障清理；真实源程序另行运行，不增加完整技能数量声明。
