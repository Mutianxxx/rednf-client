# 23 · 资源格式大白话 —— NPK 与 PVF 完全破译

> 2026-10-06 会话 7。方法：逆向 ARAD.exe 的加载器（NPK=0x40E9E0，PVF=0x528DB0+0x527AC0+0x528650）
> → 写参考实现（tools/npk_reader.py + tools/pvf_reader.py）→ 用真实游戏文件验证通过。
> **两个格式都 100% 破译并实证**（NPK 验证于 ACT1 版 sprite_character_common.NPK；
> PVF 验证于 DNF2008_ACT1/Client/Script.pvf 全 48,326 条目录 + 内容解密）。

---

## 一、NPK —— 图片/声音的"行李箱"

### 大白话
NPK 就是把几百张图片打包成一个文件。像一个行李箱：门口有一张"行李清单"（目录），
清单上写着每件行李的位置和大小，打开箱子按位置拿就行。
**2006 年版连名字都是明文的，也不锁箱子**（后来的版本才给清单加了密码）。

### 二进制布局

```
偏移 0x00: "NeoplePack_Bill\0"     16 字节魔法（15 字符名 + NUL 终止）
偏移 0x10: DWORD 文件数 N
偏移 0x14: 目录条目 × N，每条 264 字节：
             DWORD  数据偏移（从这个文件的哪个字节开始读内容）
             DWORD  数据大小（内容多少字节）
             256字节 文件名（明文，如 "sprite/character/common/skillicon.img"）
偏移 0x14 + 264×N: 文件内容区（按目录里的偏移依次排布）
```

### 读取流程（代码级）

1. 读 16 字节魔法，`strncmp == 0` 校验（sub_40E9E0 @0x40E9E0）
2. 读文件数 N
3. 循环 N 次读 264 字节条目 → {偏移, 大小, 名字} 插入按名字排序的红黑树
4. 要读某个文件：按名字查树 → fseek(偏移) → fread(大小) → 交给 IMG 解析器（0x418CD0）

### 实证记录

```
文件: G:\game\DNF2008_ACT1\Client\ImagePacks2\sprite_character_common.NPK
条目数: 1（单文件包）
条目: 偏移=284  大小=30608  名字="sprite/character/common/skillicon.img"
验证: 16(魔法)+4(数量)+264(条目) = 284 = 内容起始偏移 —— 数学自洽 ✓
```

### 注意事项

- **版本差异**：2006 版（本工程目标）名字明文、无加密；后来（90US 等）版本
  名字字段有 XOR 加密（实测 90US 的 sprite.NPK 名字乱码，出现 "DNFDNFDNF" 填充模式）
- IMG 内容解析（0x418CD0）：校验 32 字节魔法 "Neople Image File"，
  记录流 = 4B 图像 ID + zlib 压缩块；ID 0x11 = 别名条目

---

## 二、PVF —— 游戏的"数据大脑"

### 大白话
PVF（Script.pvf）是整个游戏的数据库：所有物品属性、技能数值、怪物定义、任务文本
全在里面。它分两层：
- **目录层**（加密的行李清单）：列出了游戏里每个数据文件的名字和位置（实测 48,326 个文件）
- **内容层**（每个数据文件的正文）：.ani 动画脚本 / .equ 装备定义 / .str 文字表 /
  .atk 攻击定义 / .skr 技能……全部是文本格式

两层都有密码，但密码就藏在文件头里（密钥不藏他处）。

### 二进制布局

```
偏移 0x00: "DNF_SCRIPT_PACK"        15 字节魔法（无 NUL！紧跟数据）
偏移 0x0F: DWORD S                   加密目录块大小（ACT1 实测 3,618,328）
偏移 0x13: DWORD A                   解密 XOR 密钥 + 目录完整性校验值
偏移 0x17: DWORD B                   目录条目数（ACT1 实测 48,326）
偏移 0x1B: 加密目录块（S 字节）       ← 解密后 = B 条目录
之后:      文件内容区（按目录里的偏移定位）
```

### 目录块解密算法（sub_527AC0，汇编级精确转写）

```
状态 = ~B                              （CRC 初值 = 条目数取反）
对目录块里每 4 字节（大端序无所谓，按 LE 读）：
    解密值 = ROR32( A XOR 密文值, 6 )    （循环右移 6 位）
    把解密值写回（就地解密）
    状态 = 标准 CRC32 更新（状态, 解密值的 4 字节 LE）  ← poly 0xEDB88320 表驱动
全部解完后校验：状态 == ~A  （头部自带的完整性校验，实测吻合）
```

### 解密后的目录条目（可变长）

```
每条 = 5 个 u32 + 名字：
    u32 索引（0,1,2,...）
    u32 内容偏移（相对"目录块结束+S"？实测=内容在文件中的位置-游标27-S）
    u32 内容大小
    u32 内容密钥（同时也是内容解密的 XOR 密钥和校验值——一字三用）
    u32 名字长度
    字节 名字（如 "passiveobject/monster/ghoul/animation/skullbombsub.ani"）
```

### 文件内容读取（sub_528650）

1. 算路径哈希：DJB2（初值 5381，乘 33 加字节）→ 在红黑树里找条目
2. seek 位置 = 内容偏移 + 游标(27) + S
3. 读取大小 = (内容大小 + 3) & ~3（向上对齐 4 字节）
4. 解密：同 sub_527AC0，但参数换成：初值 = ~内容偏移，XOR 密钥 = 条目里的内容密钥
5. 解密后按实际大小截断 → 得到明文

### 实证记录（DNF2008_ACT1/Client/Script.pvf，66MB）

```
头部: S=3,618,328  A=0xB9077EC4  B=48,326
目录 CRC 校验: PASS（终态 0x46F8813B == ~A ✓）
48,326 条目录全部解出，路径样例：
  passiveobject/monster/ghoul/animation/skullbombsub.ani
  equipment/character/fighter/avatar/belt/atrinketry_gbtfly.equ
  monster/monster.kor.str
内容解密实测（3 种类型全通过）：
  .ani → "[LOOP] 0\r\n[SHADOW] 1\r\n[FRAME MAX] 7\r\n[FRAME000]\r\n[IMAGE] ..."
  .str → EUC-KR 韩文文字表（"한국스크립트용 문자열 데이터 파일"）
  .equ → "[name] `카옥...`\r\n[name2] `Gray Jade Butterfly...`\r\n[grade] 2 ..."
```

### 注意事项

- `readScriptFromPVF`（0x442950）= 按路径读脚本的对外接口，缓冲区 0x80000
- `sub_4422C0` = PVF 加载总入口（检查 `_ScriptPacks` 开发目录 / `!ScriptPacks` 禁用标志）
- 目录块如果 CRC 校验失败，客户端直接拒绝加载（不降级）
- 本文档对应 **2008 ACT1 版**（与 2006 40JP 客户端同为 v1 格式）；后来版本的
  PVF（"Neople Seal File" 头 + 类型标记树）格式不同

---

## 三、参考实现（可直接运行）

| 文件 | 用法 |
|---|---|
| `tools/npk_reader.py` | `python tools/npk_reader.py <文件.npk>` 列目录+验证 |
| `tools/pvf_reader.py` | `python tools/pvf_reader.py <Script.pvf>` 列目录+验证 |
| （代码内） | `NpkReader(path).read(name)` / `PvfReader(path).read(path)` 返回字节 |

两个读取器都带 `validate()` 方法：自动检查偏移单调性、边界、CRC 校验。
PVF 读取器含解密穷举自检（如果头部参数被改动会明确报错而不是输出乱码）。
