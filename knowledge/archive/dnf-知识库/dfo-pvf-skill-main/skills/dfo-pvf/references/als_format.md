# DNF 动画列表文件 (.als) 格式参考

## 概述

`.als`（Animation List）是**动画列表文件**，位于 `character/[job]/animation/` 目录下，用于**组合多个 `.ani` 文件**形成完整动画序列。

- `.ani` — 底层动画片段（单帧序列）
- `.als` — 编排层，负责组合、调度多个 `.ani`

## 文件位置

动画列表文件位于 `character/[job]/animation/` 目录下，如：
- `character/swordman/animation/bloodswordcharge.ani.als`

## 核心指令

| 指令 | 说明 |
|------|------|
| `[use animation]` | 声明引用一个 `.ani` 文件并起别名 |
| `[add]` | 按时间 + 槽位将引用过的动画加入播放序列 |
| `[create draw only object]` | 创建纯渲染对象（无骨骼绑定），常用于特效层 |

## `[use animation]` 格式

```
[use animation]
    `路径/xxx.ani`
    `别名`
```

声明引用一个外部 `.ani` 文件，并为它定义一个别名，后续用别名来引用。

## `[add]` 格式

```
[add]
    开始时间          // 毫秒或游戏内时间单位
    插槽槽位/层级ID    // 同一时刻可叠加多个动画在不同槽位
    `别名`            // 引用 [use animation] 中定义的别名
```

将已引用的动画按时间 + 槽位添加到播放队列。

## `[create draw only object]` 格式

```
[create draw only object]
    渲染层/DrawOrder
    `别名`  参数...
```

创建一个仅渲染的对象（不参与动画骨骼绑定），常用于粒子/特效层。

## 层级设计

同一时刻（`0`）可以分配多个动画到**不同槽位**（如 10000/10001/10002），实现分层渲染和播放优先级控制。

## 示例文件

`character/swordman/animation/bloodswordcharge.ani.als`

```
#PVF_File

[use animation]
    `../Effect/Animation/BloodSword/charge_body.ani`
    `b`

[use animation]
    `../Effect/Animation/BloodSword/charge.ani`
    `charge`

[use animation]
    `../Effect/Animation/BloodSword/charge_dodge.ani`
    `charge_dodge`

[use animation]
    `../Effect/Animation/BloodSword/dust.ani`
    `dust`

[add]
    0   10000
    `b`

[add]
    0   10001
    `charge`

[add]
    0   10002
    `charge_dodge`

[create draw only object]
    8
    `dust`  0  1  0
```

该示例展示了在同一时刻（0）叠加多个动画到不同槽位（10000/10001/10002），以及用 `[create draw only object]` 渲染 dust 特效。

---

## .als 文件的引用方式

**`.als` 不是独立文件，而是 `.ani` 的伴随文件，以 `.ani.als` 双扩展名形式存在。**

- 文件命名规则：`xxx.ani` 的伴随列表文件命名为 `xxx.ani.als`
- 引擎自动加载：游戏引擎在加载 `xxx.ani` 时，会**自动寻找并加载**同目录下的 `xxx.ani.als`
- 无需手动引用：`.skl` 技能文件和 `.cre` 生物文件只引用 `.ani`，引擎自动完成配对

示例：
```
blockbusterdouble.ani         # 主动画文件
blockbusterdouble.ani.als     # 自动被引擎加载的伴随列表文件
```

因此在 `character/[job]/animation/` 目录下，`.ani.als` 文件与 `.ani` 文件**一一对应**，每个动画都可以有一个可选的 `.als` 文件来组合多层动画效果。