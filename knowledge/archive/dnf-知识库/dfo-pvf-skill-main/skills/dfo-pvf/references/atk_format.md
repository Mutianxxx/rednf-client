# DNF 攻击判定文件 (.atk) 格式参考

## 概述

`.atk`（Attack Info）文件位于 `character/[job]/attackinfo/` 目录下，定义**攻击的伤害属性、击退效果、元素属性、攻击类型**等。

## 文件位置

攻击判定文件位于 `character/[job]/attackinfo/` 目录下，如：
- `character/swordman/attackinfo/attack1.atk`

## 核心字段

| 字段 | 示例值 | 说明 |
|------|--------|------|
| `[damage bonus]` | `-15` | 伤害修正值（可正可负，百分比） |
| `[attack type]` | `[physic]` / `[magic]` | 物理或魔法攻击 |
| `[weapon damage apply]` | `1` | 武器伤害是否参与计算（1=参与） |
| `[attack enemy]` | `1` | 是否可攻击敌人（1=是） |
| `[elemental property]` | `[no element]` | 属性伤害类型（无/火/冰/光/暗） |
| `[damage reaction]` | `[damage]` | 伤害反应类型 |
| `[push aside]` | `30` | 横向击退力 |
| `[lift up]` | `75` | 垂直浮空力 |
| `[attack direction]` | `[hit down]` / `[hit up]` | 攻击方向（下压/上挑） |

## 攻击方向类型

| 值 | 含义 |
|----|------|
| `[hit down]` | 下压攻击（斜向下挥砍） |
| `[hit up]` | 上挑攻击（斜向上挑起） |
| `[hit front]` | 正面直击 |

## 元素属性类型

| 值 | 含义 |
|----|------|
| `[no element]` | 无属性 |
| `[fire]` | 火属性 |
| `[ice]` | 冰属性 |
| `[light]` | 光属性 |
| `[dark]` | 暗属性 |

## 示例文件

`character/swordman/attackinfo/attack1.atk`

```
#PVF_File

[damage bonus]
    -15

[attack type]
[physic]

[weapon damage apply]
    1

[attack enemy]
    1

[elemental property]
[no element]

[damage reaction]
[damage]

[push aside]
    30

[lift up]
    75

[attack direction]
[hit down]
```

该示例定义了剑魂平攻第一击（Z键第一下）的攻击判定：
- 伤害修正 -15%
- 物理攻击，武器伤害参与
- 无属性
- 击退 30 + 浮空 75
- 攻击方向下压