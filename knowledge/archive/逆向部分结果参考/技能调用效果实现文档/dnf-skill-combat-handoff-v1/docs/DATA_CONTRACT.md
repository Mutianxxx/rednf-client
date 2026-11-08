# 数据和时序契约

## 运行时主要结构

| 字段/结构 | 当前语义 |
| --- | --- |
| `Cast.id/start/x/y/face` | 唯一施法实例、全局毫秒起点、施法原点与冻结朝向 |
| `BodyStage.path/begin/end` | 身体ANI、相对施法的毫秒半开区间 |
| `Cast.lock/duration` | 输入动作锁；效果整体结束；二者分开 |
| `Track.path` | 归一化PVF ANI路径，不是IMG路径 |
| `Track.begin/end/spawn` | 相对施法毫秒时间；spawn只决定固定生成锚点取哪个时刻的运动 |
| `Track.position` | `[x,y,z]`局部偏移；`projection_only`时包含明确标注的投影推导 |
| `Track.anchor` | `actor`、`spawn`、`cast`；见实现文档 |
| `Track.layer/repeat` | 相对层序、当前播放时间表是否循环 |
| `Track.basis/source` | 源规则或校准的出处；source可为路径、字段对象或采集见证集合 |
| `Monster.id/generation` | 稳定实例身份/本次生成代号，拒绝过期命中 |
| `Monster.state/age` | idle、damage1、damage2、death及独立毫秒时钟 |
| `Monster.frozen/fragments` | 致死时冻结播放计划与当前姿态时钟；该实例独立粒子 |

## 文件契约

`content/battle.json` schema=1：`source_exe_sha256`绑定源版本；`skills[]`八个已接入核心规格；`monsters[]`三种同源绑定；`diagnostics[]`源缺口；`policy`声明重建策略。`controller_complete=false`应保留，替换为完整原生事件需新增证据。

`content/skills.json`：231记录，含源SKL、源字段/偏移、职业groups及classification_basis、身体序列、效果时间表和未映射候选。运行UI仅显示88主动；嗜魂封魔斩排除。职业编号见同文件 `jobs`，不能用技能名推职业归属。

`content/profile.json`：冻结外观、12层绘制顺序、skin图片替换、同名NPK覆盖规则。当前太刀/鬼剑士族专用；换角色时需替换CHR及其motion根和外观规则。

`content/cache/index.json`：路径→resources.bin偏移/长度、源raw_sha256/record，以及字符串表、源EXE/PVF/snapshot身份。ANI成员为UTF8 JSON：globals、frames、source_fields。每帧image/imageFrame/x/y/duration/boxes/properties；攻击type15，伤害type14；未消费字段保留，不能丢弃重复标签。

其他脚本成员：两字节 `B0 D0`，后续每项1字节类型+4字节小端值。2为int32，4为float32，5标签字符串ID，6普通字符串ID。该格式是项目中间格式，不能写回原PVF并宣称原生格式。

`derivation/raw/`的成员没有中间格式头：原始token5中的类型0为有符号整数、2为float、3为标签、5/6/7/8/10为字符串引用。offset是该成员内字节偏移；引用查冻结strings映射。归一化前后offset不要混用。

`client-assets/asset-manifest.json`：包内每个档的hash/size和所有逻辑IMG成员映射。NPK子集只改目录/偏移，IMG内容未重编码。默认运行会核对档hash；独立工具逐成员再核对。原档目录哈希不等于原档全文件哈希。

## 事件接入约束

外部命中模块调用契约是 `targetId,generation,eventId,reaction,damage`；原C++函数接收解析后的Monster引用。eventId在目标生命周期内不可重复，generation必须对应当前实例。使用原判定模块时应关闭本demo几何结算或保证统一去重，防止重复扣血。

资源可共享，状态不可共享。相同ANI路径不构成实例ID；同一内存地址不同构造区间也不代表同一资源生命周期。暂停时全部模拟时钟停止；从F5的时间点复查时先核对build-manifest和源版本。
