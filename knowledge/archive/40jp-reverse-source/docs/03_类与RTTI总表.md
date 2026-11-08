# 03 · 类与 RTTI 总表

> 更新：2026-10-06。数据源：data/rtti_hierarchy.txt（743 类全表）、
> data/class_method_slots.txt（97K 行槽位 dump）、data/rtti_naming_summary.txt。
> 命名回写：tools/idar_rtti_hierarchy_names.py → IDA 工作库（3,540 函数）。

## 1. 总量

| 项 | 值 |
|---|---|
| TypeDescriptor（类） | 746 扫描 / 743 入层级表（3 个 std 边角未入表） |
| Complete Object Locator | 1,518（多继承多段） |
| 虚表 | 783 张 |
| 虚方法槽位（跨子类累计） | 95,686 |
| 有虚表的类 | 720 |

## 2. 类族分布

| 族 | 类数 | 槽位合计 | 定位 |
|---|---|---|---|
| `CN*` 业务层 | 518 | 91,255 | 职业/怪物/技能/装备/UI 具体类（虚接口巨大，怪物类 340+ 槽） |
| `CNRD*` RD 对象层 | 140 | 2,866 | Neople 引擎游戏对象基类 |
| `IRD*` 接口层 | 10 | 1,176 | 纯虚接口（IRDCollisionObject/IRDActiveObject/IRDMonster/IRDAppendage…） |
| `nengine` 引擎接口 | 22 | 120 | IObject/IModule/ISocket/CNString/CNTimer… |
| std/CRT | 25 | 69 | std:: 容器与异常类 |
| 其他 | 28 | 97 | KMessenger/KGameMessenger/UdpPacketHandler/crypt4byte/clong/cfloat… |

## 3. 槽位分桶

| 槽位数 | 类数 | 说明 |
|---|---|---|
| 0 | 23 | 纯数据类（std 异常等） |
| 1-16 | 195 | 简单组件/观察者 |
| 17-64 | 101 | 中型 UI/管理器 |
| 65-128 | 79 | 模块/窗口类 |
| 129-256 | 195 | 大型对象类 |
| 257+ | 150 | **怪物/职业类农场**（虚接口最重） |

## 4. 继承体系（实测骨架）

### 战斗对象线（怪物/角色）
```
KMessenger（根，消息基座）
 └ KGameMessenger
    └ CNRDObject（+200 主状态/+228 vmtE4 状态写入器/+512 家族命中回调…）
       ├ IRDCollisionObject（碰撞段：vmt1DC 本地扫掠 / vmt200 表现壳 / vmt274 伤害流水线）
       │  └ IRDActiveObject（活动段：vmt200 命中主处理器 / vmt2D8 HP setter）
       │     └ IRDMonster
       │        └ CN 系怪物/职业子类（~340 槽，vmt200 命中处理器各自覆写 0x58Bxxx 家族）
```

### 地图对象线
```
CNRDObject → IRDCollisionObject → CNRDPassiveObject → CNMapObject
   └ CNActionTree / CNActiveObserver / 各种场景物件
```

### nengine 引擎线
```
nengine::IObject → nengine::IModule → CN 各游戏模块（CNMainGameModule/CNEntranceChannel/
   CNSelectDungeonModule/CNPVPModule/CNWarRoomModule/CNChaosModule/CNRoomListModule…）
```

## 5. 命名回写结果（P2）

- 命名函数：**3,540**（`类名__vmt槽偏移` 格式），失败 0
- 保留既有命名：91,979 槽位指向已命名函数（多数为基实现共享）
- 抽查验证：0x4D71B0=IRDActiveObject__vmt200（命中主处理器）等五点与研究定案全吻合
- 副产品：RTTI_COL_* / vftbl_* 名已入库（部分 tail-byte 警告无害）

## 6. 重建归档规则（源码树组织）

- `src/nengine/` ← nengine 命名空间 + IObject/IModule 体系
- `src/cnrd/` ← CNRDObject/IRD* 接口/CNRD 引擎对象
- `src/game/creature/` ← 怪物与职业类（340+ 槽农场）
- `src/game/module/` ← CN*Module 业务模块（登录/选区/房间/PVP/战争 room…）
- `src/game/misc/` ← 装备/技能/Item/Window/UI 类
- 每类一个 `.cpp`（大族可拆多文件），函数携带 VA；虚方法按 vmt 槽偏移排列并标 `// vt+0x200`
- 数据文件另见 `data/rtti_hierarchy.txt`（全 743 类：TD/主虚表/基链/槽位数）
