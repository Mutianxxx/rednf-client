# PVF / NPK / IMG 格式速查（PVFTools 逆向结论）

> 本文档是 `DNF-Porting/` 对 DNF 私有格式的逆向结论沉淀，来源为源码解读
> （2025 代码审阅）。所有偏移/常量以源码为准；改动解析逻辑时先对照本文，
> 改完格式相关逻辑必须同步更新本文。

## 1. PVF 容器（PvfReader）

### 1.1 头部（PvfHeader，共 56 字节）

| 偏移 | 类型 | 字段 | 说明 |
|---|---|---|---|
| 0 | int32 | sizeGUID | 恒为 0x24 (36) |
| 4 | uint8[0x24] | GUID | |
| 40 | int32 | fileVersion | |
| 44 | int32 | dirTreeLength | 目录树区总字节数 |
| 48 | int32 | dirTreeChecksum | 目录树 CRC32（解密参数） |
| 52 | int32 | numFilesInDirTree | 文件条目数 |

### 1.2 目录树加密

- 解密算法（`PvfReader::decrypt`）：按 4 字节字处理，
  `word = ROR32(word ^ 0x81A79011 ^ crc32, 6)`。
- 常量 `PASSWORD_PVF = 0x81A79011`；crc32 取头部 dirTreeChecksum。
- 不足 4 字节倍数的尾部不处理。

### 1.3 目录树条目（变长，循环 numFilesInDirTree 次）

| 偏移(相对条目) | 类型 | 字段 |
|---|---|---|
| +0 | uint32 | fileNumber |
| +4 | int32 | filePathLength |
| +8 | bytes | 路径（源编码见 1.4），rtrim 后作 key |
| +8+pathLen | int32 | fileLength（实际字节数，非 4 对齐） |
| +12+pathLen | uint32 | fileCrc32（该文件数据区解密参数） |
| +16+pathLen | int32 | relativeOffset（相对 header+dirTree 结束处） |

条目步进：`filePathLength + 20`。文件数据区的解密与目录树同算法，
crc32 换成条目的 fileCrc32。实际读出长度按 4 对齐：
`computed = (fileLength + 3) & ~3`，尾部补零。

### 1.4 文本编码

- PVF 内字符串源编码按客户端区域不同（TW=950/CN=936/KR=949/JP=932）。
- 本库当前硬编码 `ENCODING = "BIG5HKSCS"` 转 UTF-8（`PvfReader.h:41`），
  因为 libiconv 在纯 BIG5 下转"恒"字会中断。改编码前先确认样本文件区域。

### 1.5 双层字符串索引

1. **stringtable.bin**：首 int32 = count；随后每 4 字节一个 int，
   第 i 对 `(startPos, endPos)` 位于 `i*4+4` 与 `i*4+8`；
   字符串本体在 `startPos+4` 起、长 `endPos-startPos`（为什么 +4：区段前 4 字节
   是内容指示位）。取出的串 toLower + trim 后进 `stringBinMap`。
2. **n_string.lst**：magic uint16 = 53424；之后按 10 字节记录步进，
   记录内偏移 +6 的 int32 是 stringtable 的键。取出的文件名再 unpack 成文本，
   逐行找 `>` 分隔的 `key>value` 对存入 `stringStringMap`
   （供 ValueType::StringLink 解引用）。

### 1.6 PVF 脚本字节流（PvfDocument 解析）

流 = `int16 header` + 一串 `(int8 type, payload)`。type ∈ ValueType：

| 值 | 枚举 | payload |
|---|---|---|
| 2 | Int | int32（数值） |
| 3 | IntEx | int32（同 Int 处理） |
| 4 | Float | int32（位模式即 float） |
| 5 | Section | int32 → stringBinMap 下标，得到 `[name]` / `[/name]` 节点标记 |
| 6 | Command | int32 → 字符串下标 |
| 7 | String | int32 → 字符串下标 |
| 8 | CommandSeparator | int32 → 字符串下标 |
| 9 | StringLinkIndex | （本库未实现，仅占位） |
| 10 | StringLink | int32 → 经 stringStringMap 二次解引用 |

解析要点：先整流扫一遍收集所有 Section 串判断哪些节点有闭合标签
（`hasEndTag`），再正式解析。闭合判定：start 串 `[x]` 插入 `/` 得 `[/x]`
是否存在于收集集。

## 2. .ani 动画（PvfAnimation）

```
uint16 framesCount
uint16 countOfResources
  资源名 × countOfResources：int32 len + bytes（ASCII 路径，toLower）
uint16 paramCount
  帧全局参数 × paramCount：uint16 type + 按 type 读
    0 LOOP: int8      1 SHADOW: int8
帧 × framesCount：
  uint16 boxCount
    box × boxCount：uint16 type(14 DAMAGE_BOX / 15 ATTACK_BOX) + int32×6
  uint16 imgId + uint16 imgParam     → 帧贴图 = sprites[imgId]
  int32 x, int32 y
  uint16 propertyCount
    property × propertyCount：uint16 type + 按 type 读，常见：
      3 Ani_COORD: uint16        7 IMAGE_RATE: float×2
      8 IMAGE_ROTATE: int32      9 RGBA: uint32
      10 INTERPOLATION: int8    11 GRAPHIC_EFFECT: uint16 effectType
           （4 MONOCHROME 再读 uint8×3；6 SPACEDISTORT 再读 uint16×2）
      12 DELAY: int32           13 DAMAGE_TYPE: uint16
      16 PLAY_SOUND: int32 len + bytes
      23 SET_FLAG: int32        24 FLIP_TYPE: uint16
      25 LOOP_START: 无参       26 LOOP_END: int32
      27 CLIP: int16×4
      已知无参/跳过：2,4,5,6,14,15,17(PRELOAD),18(SPECTRUM),19,20,21,22
```

注意：type 表是 TLV 但**未知 type 无法确定长度**，遇到未收录 type 只能报错，
不能静默跳过（会流错位）。

## 3. NPK 包（NpkFile / Npk.h）

- 头：`char flag[16]`（"NeoplePack_Bill"）+ `int32 count`。
- 索引条目（264 字节 × count）：`uint32 offset; uint32 size; char fileName[256]`。
- **文件名混淆**：逐字节 XOR 常量串
  `"puchikon@neople dungeon and fighter DNF"` 循环填充至 256 字节
  （`ImgFile.cpp: FileNameFlag`）。注意 XOR 后原终止符位置恢复为 0。

## 4. IMG 图像（ImgFile）

- 新版 flag `"Neople Img File"`（15B），旧版 `"Neople Image File"`（17B）。
  新版读 flag 后**回退 2 字节**再读 int32 indexSize；旧版直接读 uint16 indexSize。
- 头部后续：int32 keep, version, indexCount。
- 版本分支：
  - v4：调色板（colorBoard）：int32 count + uint32×count。
  - v5：额外 int32 mapCount、int32 fileSize；调色板 + MapImage×mapCount
    （28 字节/条：keep,fmt,index,dataSize,rawSize,w,h）。
  - v6：int32 colorBoardCount + 多块调色板。
- 纹理条目循环 indexCount 次：uint32 format；
  format==17 (ARGB_LINK) 时再读 int32 linkId（指向本 IMG 内另一条目）；
  否则读 NpkTexture（28B：extra,width,height,size,x,y,maxWidth,maxWeight）。
  - extra==7 (COMPRESS_MAP_ZLIB) 再读 zlibInfo 28B。
  - v1：数据紧跟条目内联（记 offset 后 seek 跳过 size）。
- v2 的数据基址 = metaInfo.offset + indexSize + 32；其余版本 = 条目表结束处。
- BitmapType：14=1555 15=4444 16=8888 17=LINK 18=DXT1 19=DXT3 20=DXT5。
- CompressType：5=无压缩 6=zlib 7=map_zlib。
- 像素展开：1555/4444 → 8888 用 `table5`/`table4` 查表（源码内置）；
  zlib 解压后大小 = width*height*(8888?4:2)。
- v1/v2 无压缩时 size 需按 `width*height*(fmt==8888?4:2)` 重算。

## 5. 快速校验值

| 对象 | 期望值 |
|---|---|
| PVF sizeGUID | 0x24 |
| n_string.lst magic | 53424 |
| NPK flag | "NeoplePack_Bill" |
| IMG flag | "Neople Img File" / "Neople Image File" |
| PVF 解密常量 | 0x81A79011, ROR 6 |
| NPK 文件名 XOR key | "puchikon@neople dungeon and fighter DNF" 循环 |
