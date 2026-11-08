# 交接包验证

此交接包固定于已验收 demo 的源码及资源版本。原 demo 的11项验证和本包的独立移植检查分别保留，避免把软件自检当作原客户端逐帧一致证据。

| 项目 | 结果/证据 |
| --- | --- |
| 原demo交付 | 11项通过，含正常可见窗口的完整播放；见 [delivery-verification.json](evidence/delivery-verification.json) |
| 源码/绑定一致性 | 打包器对源demo构建清单逐项核对；EXE及源码/配置受原构建SHA约束 |
| 独立构建 | 使用本包source/vendor/data编译成功；不从attack_demo或旧handoff读取构建依赖 |
| 独立渲染 | 新构建程序以`--verify --client`通过6个动画案例、52个基础帧、4个共享死亡案例 |
| 任意怪物查询入口 | 六个不同怪物共469个图节点、1706条引用，全部成功解析，无NPK索引错误 |
| 完整通用资源索引 | 23个ANI/PTL的原字段/哈希，29套石块每套4帧及静态共用图/声音的NPK位置/成员哈希 |
| 原资源导出 | 按MOB路径查询猫妖并使用`--extract`导出PVF/NPK成员，导出内容逐项对照graph哈希 |
| 包内一致性 | `tools/verify_package.py`检查所有manifest文件、文档相对链接、源码符号实际行号、目录/合同版本及六个图闭包 |

机器结果见 [package-verification.json](evidence/package-verification.json)，独立运行的原始状态/资源记录见 [standalone-verification.json](evidence/standalone-verification.json)、[standalone-shared-death-verification.json](evidence/standalone-shared-death-verification.json)、[standalone-resource-reads.json](evidence/standalone-resource-reads.json)。[资源导出校验](evidence/export-verification.json)记录37个PVF成员、10个NPK成员的实际导出哈希匹配。机器报告是生成该包时的验证快照，最终文件清单和哈希以manifest为准；再次运行默认检查只输出结果，不修改交付文件。

校验命令在包根目录执行：

```powershell
python -X utf8 -B .\tools\verify_package.py
# 已执行build_reference.py构建，且具备绑定版本客户端时：
python -X utf8 -B .\tools\verify_package.py --client 'D:\game\DNF1031客户端-20260708\DNF1031客户端' --run-reference --report .\build\verification-result.json
```

验证覆盖已实现的视觉流程、资源定位、冻结白色轮廓、粒子确定性/朝向/omit、结束与reset；不表示2070个MOB全部动态验收，也不表示恢复全部ACT脚本、原生评级、受击物理与HP死亡链。相关未知项已明确保留在主文档及EVIDENCE中。
