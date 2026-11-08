# 数据模型、查询和离线检查

主库是 `research/dnf-evidence.sqlite3`。可用 Python 标准库 SQLite 打开，不依赖原 GBA 工程。`research/pc-assets.sqlite3`、`code-evidence.sqlite3` 和 `android-loader-traces.sqlite3` 是可重建的分项审计结果，汇总数据已合入主库。搬运时不需要 SQLite 的 `-wal`／`-shm` 临时文件，停止写入并完成 checkpoint 后复制主库即可。

| 表／输出 | 主要内容 |
|---|---|
| `files` | 来源、路径、格式、状态、哈希、zlib 原字节、zlib JSON 模型、错误 |
| `tags` | 每次标签出现的顺序、偏移、值；重复项不合并 |
| `registrations` | 列表命名空间、原局部 ID、原顺序、原值和路径；不同列表 ID 不互换 |
| `refs` | 每次路径／声音引用及其解析状态；动态引用、多个候选和缺失资源分别保留 |
| `assets` | NPK、偏移／长度、IMG 原尺寸帧／链接／像素位置、哈希和检查状态 |
| `code_units`／`call_edges` | 词法函数、native 符号、行号／地址、来源和调用观察；不是完整语义反编译 |
| `gaps` | 稳定 ID、领域、来源对象、状态、阻塞类型、证据与验收条件 |
| `all-skill-files.jsonl` | 全 2,008 个技能文件及其注册关系；与四职业旧导出区分 |
| `world-model.jsonl` | 原世界字段，DGN 的所有房间候选及 TWN 的全部 area；不含缩放 |
| `audio-events.json` | XML 原顺序及所有属性，不只导出文件名 |
| `behavior-contracts.json` | 已用原生执行检查的来源专属规则；PC 适用性明确为 false |

`raw_z` 是 `zlib.compress(raw)`，`model_z` 和 `values_z` 是 UTF-8 JSON 再 zlib 压缩。恢复 token 字节时使用 `header_hex + pack('<Bi', type, raw_int)`，浮点的原始位型也由 `raw_int` 保留，不能从显示小数反推。ANI 模型保留全部属性而非只用最终属性覆盖重复项。

在 `dnf-result` 目录执行：

```powershell
python -X utf8 -B tools/research_query.py summary
python -X utf8 -B tools/research_query.py search --q skill/atmage
python -X utf8 -B tools/research_query.py object --path character/swordman/swordman.chr
python -X utf8 -B tools/research_query.py refs --path dungeon/ancient/ghosttrain.dgn
python -X utf8 -B tools/research_query.py code --source all --q checkRequire
python -X utf8 -B tools/research_query.py gaps --q 30037.fra
python -X utf8 -B tools/research_query.py raw --path character/swordman/swordman.chr --output research/exports/swordman.chr
python -X utf8 -B tools/evidence_viewer.py
```

浏览器打开 `http://127.0.0.1:8765`，可检索源文件、代码和台账，下载解密原字节，播放 ANI 帧时间轴并读取原尺寸 IMG。图片需要工作区外部只读的 `DNF1031客户端` NPK；每次读取核验资源哈希。多包存在同名资源时 API 要求明确 archive，不静默覆盖。界面是研究工具，原尺寸单层预览不模拟 PC 混合、完整层序、旋转、镜像和控制器，不是游戏截图。播放循环也是浏览器查看方式，不是原动作循环契约。

迁移资料目录后，数据库查询仍可独立工作；PC 原图输入可用 `tools/evidence_viewer.py --client-root D:\原客户端目录` 指定。客户端必须与资源哈希清单一致。

## 后续新端契约

[runtime-contract.schema.json](../schemas/runtime-contract.schema.json)要求身份命名空间、样本哈希、规则状态、证据、单位、未知项／影响／验收条件和运行等价性状态。当前 [behavior-contracts.json](../research/behavior-contracts.json)是真实已恢复规则的样例，没有用模板填入未知 PC 数值。

技能的新端实现应在契约中分别明确：输入序列和缓冲、状态资格／取消、每段动作／帧、扣蓝与 CD 起点、位移／方向、攻击体／多次命中的独立计数、持续／召唤实体、霸体与无敌各自生效区间、命中与空放、音画事件、结束／死亡／换场清理。未知字段不得通过默认 0 或 null 伪装为“无效果”。

世界模型保留每个 `[map specification]` 的全部候选，包括重复 ID。源 `dungeon/dungeonsample.dgn` 的一个空 section 也保留原值。通行、门开启条件、随机权重和地图可用性不由文件名猜测；TIL／背景／虚拟区域仍须原消费者解释与实际场景核验。

任务原 JSON 列表可用作新端数据源。现 APK 的列表显示、225 字节二进制注入、新建解释器是三种不同实现路径，不能混称为“任务已经可执行”。GBA 的免材料、提前开放技能、CD 调整和按键／图像限制继续放在平台策略层。
