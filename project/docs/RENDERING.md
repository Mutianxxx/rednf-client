# 渲染合同

本节点从 457 保留现有表现语义；详见
`REFACTOR-NODE-A0-A2a.md` 和 `../../knowledge/architecture/ARCHITECTURE-REFACTOR-OUTLINE.md`。

- 角色、装备、时装与技能附属层由 `CharacterPresentation` 组合；源层序交织，不分三批重排。
- ANI 原始毫秒和每轨时钟、帧覆盖、独立/跟随时钟策略保持；显示不得推进模拟或重复发出帧事件。
- 保留 IMG 原点、源偏移、朝向/镜像、缩放、混合、局部附着和世界投影的区别。
- `ICharacterDrawSink` 只同步消费动画请求和诊断，SDL 纹理/设备仍归 Renderer。
- 地图、怪物与独立效果代码已按职责归档；其 Renderer 内剩余高层实现仍待下一表现节点提取。
- UI 绘制和命中应共享源布局变换；当前继承窗口/HUD实现，完整布局内核收敛尚未完成。

模拟维持 60 Hz，绘制帧率不固定为 60。保留补 tick、hitstop、实例清理和已有坐标策略。
本轮没有重新定义全职业 Z 修正、地图偏移或技能特效绑定。

`runtime.json` 中 median/p95 现在明确表示最近窗口，`frame_statistics` 记录容量、样本数和
全程计数/峰值。此诊断内存有界修改不构成游戏 FPS 提升声明。
实际画面/音效/手感和同机帧时间对照按 `USER-TEST-CHECKLIST.md` 由用户执行。
