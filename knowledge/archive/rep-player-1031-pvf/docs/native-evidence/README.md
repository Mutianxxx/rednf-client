# 本节点保留的静态依据

这些文件是先前 PC 客户端只读逆向报告的逐字节副本，来源与 SHA256 见 `provenance.json`。它们用于独立播放器的来源说明，不是运行时依赖，也不是原版动态画面验收。

本版直接读取用户当前 PVF/NPK。`swordman-controller.json` 说明代表技能的 native 状态、动画槽及对象关系；`particle-straight-keep-last.json` 保留速度积分的算术边界；其余文件记录通用动画、几何接触和命中接受的已知与未知部分。原报告里的相对引用以 provenance 所列的原报告目录为准，没有复制的逆向窗口不得声称已封装于本项目。

预览仅实现当前 README 列出的可执行范围。PTL 显示使用 double 来源曲线近似，不等于复刻 contract 中逐条 float32/整数溢出语义；命中接受、伤害、反应索引和完整技能控制器仍未完成。
