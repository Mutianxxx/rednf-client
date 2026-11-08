# 1031 原生证据与实现边界

本文地址来自固定1031的32位映像，基址 `0x00400000`。只用于追溯数据流和后续校准，重制引擎调用本包资源播放器；不能把这里的地址当作64位 demo 的函数地址。

| 来源 | 标识 |
| --- | --- |
| 原1031 EXE SHA256 | `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` |
| 原1031 PVF SHA256 | `ca756b7103a91628cffdf42fb745e9185fd5937deb229289a74831aa30500e1f` |
| 研究内存快照 | `combat_ui_1031/reports/baseline/main-readonly-57440-20261017T185135629631Z.mem` |
| 快照 SHA256 | `ab950286ad291236086beae21ef75b1732d4cd5e52db482e261f4c548969ea44` |

快照来自当时研究进程，包含 `plugins/0725.dll`、`stringtable.dll`，不是无插件环境。大体积原快照留在原工作区，本包带相关反汇编和机器报告。不能将文件中的旧对象指针视为当前进程活指针。

## 1. 受击动画接口

完整接口注册、覆盖分派、字段路径见 [native-reaction-interfaces.json](evidence/native/native-reaction-interfaces.json)，本包附 [native getter反汇编](evidence/native/code-00818bf0.asm)。以下 slot 为虚表字节偏移。

```text
getDamageAnimation(index) / slot +0x480
    脚本覆盖实现 0x006815B0
        若脚本已处理：返回脚本结果（包括 nullptr）
        未处理：走 native getter
    native 0x00818BF0
        direct = [object + 0x2C34 + index*4]
        direct非空 → direct
        否则 act = [object + 0x2CF0 + index*4]
        act非空 → [act + 0x24]
        否则 nullptr

getDownAnimation / slot +0x484
    脚本实现 0x00681730；native 0x00818C20
    [object+0x2C3C]，否则 [object+0x2CF8] → [act+0x24]

getOverturnAni / slot +0x488
    脚本实现 0x006818B0；native 0x00818C40
    [object+0x2C40]，否则 [object+0x2CFC] → [act+0x24]
```

这证明“直接受击 ANI 优先，ACT 动画成员兜底”有本版本内存代码支持。port 中应限制 index 为0/1；原 native 有 signed `<2` 判断而无完整负数保护，不应复制成可越界访问。脚本覆盖若返回“已处理但空”，不得继续 fallback。overturn 是单独接口，不能用它替代死亡动画。

这条链不证明攻击判定已经成功，更不证明不同伤害类型如何选 index；它是**取受击资源的接口**。上游攻击/碰撞合同另附 [native-collision-contract.json](evidence/native/native-collision-contract.json)，其中保留尚未恢复的上下游边界。本包的 onAcceptedHit 是建议重制接口，不是上述原生函数的同名ABI封装。

## 2. 死亡标志与回调

```text
setter slot +0x4FC → 0x0081B9F0
    输入低字节与现值不同才写入
    通过保护值写入器 0x011A0930 写 object+0x3088
    转为非零时：for i=0..17
        当 virtual+0x540(i) 为真
        对 [object+0x2C8C+i*4] 调 virtual+0x40

getter slot +0x500 → 0x00D106D0
    通过保护值读器读取 object+0x3088，再布尔化
```

对应 [setter反汇编](evidence/native/code-0081b9f0.asm) 和 [getter反汇编](evidence/native/code-00d106d0.asm)。回调的具体对象类型、HP归零到setter的所有入口、召唤物/特殊脚本的绕路尚未恢复。`+0x3088` 是受保护字段，不是可任意按普通bool读取的裸值。

报告还记录 HP reader `0x00D10700 → virtual+0x460 → 0x00D10070 → object+0x2BEC`、状态 reader `0x0067E810 → object+0x3094`；保护读器为 `0x011A0DE0`。对象类型及接口必须匹配，状态枚举含义没有由截图或名称推断。本文不据此宣称完成全场怪物枚举、HP与MOB ID绑定或原生死亡事件枚举。

## 3. 共享石块死亡的原生链

| 位置 | 已确认的指令/数据流 | 文件 |
| --- | --- | --- |
| `0x012AD2F1` | `[die effect]` 标签注册，编号 `0xBFA` | [code-012ad2c0.asm](evidence/native/code-012ad2c0.asm) |
| `0x00899E93` | 从怪物 `+0x3A74` 取掩码后 NOT | [code-00899c00.asm](evidence/native/code-00899c00.asm) |
| `0x00899EBE` | 读取怪物 `+0x3A70`，传入共享效果构造路径 | 同上 |
| `0x00899F0A` | 调用 `0x00E3C420` | 同上 |
| `0x00E3C420` | 参数保存到效果对象 `+0x208/+0x20C/+0x210/+0x214/+0x22C` | [code-00e3b100.asm](evidence/native/code-00e3b100.asm) |
| `0x00E3B2D4` | 检查效果对象 `+0x22C` bit8，加载 `MonsterDieFlash.ani` | 同上 |
| `0x00E3B609` | 检查 bit1，碎块分支 | 同上 |
| `0x00E3B892` | 格式化 `Monster/Common/m%04d.img` | 同上 |
| `0x00E3BB11` | 检查 bit4，烟雾分支 | 同上 |
| `0x00E3C4AD` | 加载 `MonsterDieSmoke.ptl` | 同上 |

原生可表达为：

```text
怪物死亡相关路径（上游尚未全追通）
  → 从怪物字段读取省略掩码/图号
  → mask取反，构造独立共享死亡效果对象 E3C420
  → 对象保存配置（不是怪物字段布局）
  → 按启用bit分支：flash / pieces / smoke
  → piece分支按palette生成m%04d.img路径
  → 原ANI/PTL/IMG被加载和绘制
```

MOB `[die effect]` 参数到 `+0x3A70/+0x3A74` 的完整解析写入链尚未闭合；报告保留这段缺口，不能只因成员值相似就宣称已证明所有 parser 字段。`0x00899F82..0x00899F92` 还以 `(1,5,-1)` 调 virtual `+0x180`，但接口身份/枚举5尚未充分证明为“白色化”。当前 demo 的白色轮廓是明确的重建绘制实现。

`0x00E3BB68` 调 `0x00706410()` 并读取其返回对象 `+0x38C`，与分级条件有关但分支具体含义未恢复。Young/VeryYoung/Teen 资源存在，不能因文件名就把其中一组统一套到所有怪物。原生调用有0.5、1.0浮点常量，完整随机映射/单位未核对；本实现的尺寸分布和弹道另列于主文档。

## 4. 资源与官方注释样例

相关23个 ANI/PTL 的**本版本实际数据**见 [common-death-resources.json](evidence/common-death-resources.json)。石块图已实际解码并查看，见 [death-img-index.json](evidence/death-img-index.json) 和 [图集](images/death-resources.jpg)，不是只凭piece命名判断。任意模型从 catalog绑定和 query工具取得真实资源，不能把猫妖测试结果外推成每个特殊怪物都使用相同 ACT。

应用技能：[dnf-pvf-reference](C:/Users/16908/.codex/skills/dnf-pvf-reference/SKILL.md)。参考语料位于 `D:\dnf-rebuild\pvf官方文档\sample(官方注释)`，原样例采用 CP949。样例提供字段语义，时代差异保留，不能替代1031二进制行为证据。

| 样例 | 位置/结论 | 原文件 SHA256 |
| --- | --- | --- |
| `actionsample.act` | 1–14：SUB ANI 路径、父动作开始帧、layer；WITH XY补x/y | `4dc013c7b56e42f81add3ad2b6bacb42ac8c1ee63cbeaa1436608f95dd703039` |
| `newmonstersample.mob` | 13–17：die effect第二项碎块颜色，第三项省略1碎块/2血/4烟/8闪；第一项与分级/强制有关 | `b37eb5e8dc0014c320e3a4596c457e5a2d56d431522ef0c020f74af251172bda` |
| 同文件 | 282：last action在销毁前执行一次 | 同上 |
| `sample.ani.als` | 17–43：父ANI附带`.als`、命名实例、add/remove父帧事件，remove忽略layer | `5f913724e9dc623d9bce61b7706a9235e1765dd420e6d6208b8bba12232af980` |

ANI二进制枚举不从空的样例说明补猜；本包的结构读取器来自已在资源上检查完整字节消耗的解码器。节点7/8/9/10/11/12/24的消费规则和未执行节点在主文档第6节公开列出。

## 5. 交接时应保留的证据等级

机器合同使用 `native_verified`（本版本内存指令）、`data_observed`（本版本资源）、`reconstruction_policy`（已验收重建策略）、`unresolved`（待恢复）四类。它们不能互相升格：截图认可代表效果可用；资源可解析代表字节结构可读；接口存在代表能够取得动画。均不自动证明完整碰撞/伤害/死亡状态机和原版像素时序一致。

后续若校准原生流程，替换路由与策略配置，保留原始资源图、字段偏移、哈希及验收图片。这样已有技能研究可以独立接入本实现，再按证据更新尚未恢复的部分。
