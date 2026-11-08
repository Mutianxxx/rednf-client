# 证据的核对方法与版本

源客户端EXE SHA256：`1f8244d3f7309bbe2fde4299e1863a894f6b28d5707bf01732980585b20b00dd`。

源PVF SHA256：`1cd52a54358738dbfea309f15ee861386f0b32e30f59e58fb4c41d73b911314a`。

快照metadata SHA256：`e836501116c7f8b93dfd4dd03ff797fa20a20662953ff849056fc1bb996eb5e5`。原始成员来自保存的运行态packed PVF，保留解码前token5数据；不是旧客户端的PVF混用。

原保存只读模块SHA256：`722fc966ea4477a3b6c60a854c21c186fa4040fb2da9288332a51f5d71ca0069`。当前包保留5段机器码及各段hash，整份模块未附；故只能独立重算各段和保留调用，不能重算整份原镜像hash。

怪物原文档EXE为另一版本：`246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264`。本包怪物motion/ACT/ALS重新从当前源绑定，未移植其原生地址。

## 一个完整的核对示例：崩山击

1. 查 `docs/skills-index.json` 中 `key=hopsmash`，得到身体阶段、每个效果的begin/end/position/anchor以及来源。
2. 查 `evidence/skill-chain-analysis/skills/hopsmash.json`，将request→relative_entry→core的线程、序号、父对象、descriptor、ID和XYZ核对；调用位置 `0x20BEC22` 的 `E8 C9 E6 56 FF` 按 `target=instruction+5+int32(relative)` 复算指向创建分发。
3. 对照 `code-evidence.json` 的 `dispatch-route-byte-4d` 与 `relative-coordinate-byte-4c`，两个开关的职责不同。
4. 查 `source_object_bindings`：20050由列表绑定到hopsmashsub.obj；原始成员hash和字段偏移可在 sources 的bin/JSON核对。source-graph的边保留原值、源偏移和目标。
5. 对照phase的resource_requests、animation_intervals及verified packet见证：只把本次构造区间内实际绘制的ANI接入正常分支，不以名字相近或时间相邻建立调用因果。
6. 查 `demo/tools/prepare.py` 和 `demo/content/battle.json` 的hopsmash项：源坐标与锚点转为独立运行规格，再由 `point()` 在生成时的位移上加123。运动高度和曲线为已注明推导。
7. 查 `validation/isolated/runtime-artifacts/skills/hopsmash/state.json` 与画面，核对施法实例、时间、帧及锚点。这是实现验收证据，不用该PNG作为素材。

## 机器检查覆盖

`tools/verify_evidence.py` 重算5段机器码、157源节点归档、原始token的type/raw字段及13次E8创建目标。相同原始字节的不同路径以hash共用归档，JSON内记录的path可能是另一个相同内容路径；源图保留各逻辑路径，不能把这种去重当作丢失实例。

`tools/verify_delivery.py` 检查文件hash、35,920个归档原始成员、包内NPK整体和151个逻辑图片引用的原始IMG字节。`verify_asset_closure.py` 检查当前可达身体/特效及外观层的全部帧范围。包内资源目录重新封装后的偏移与源偏移分开保存。

`sample-manifest.json`仍列15个原窗口及全量范围hash/位置，这是历史采集身份；全量原始日志未附。包内逐技能保留选定原字段、原序号和原始dwords/packet/调用摘要，因此能检验当前证据对象和实现，但不能复跑全日志过滤、重算未附日志或证明完整生命周期。

不要把时间表的输出当作其输入证据。控制器缺口要留在controller_complete与basis里；新运行证据应保存独立版本/采集资格，再替换推导规则。
