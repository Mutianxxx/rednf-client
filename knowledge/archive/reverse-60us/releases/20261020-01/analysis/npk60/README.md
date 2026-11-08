# 当前 60US 的 NPK / IMG 解码证据

原始文件仅以只读方式打开，数据源为 `D:\dnf\60US\DFO\ImagePacks2`。
这部分恢复的是资源封包和像素，不能据此认定技能控制器、攻击判定或原客户端补丁加载优先级已经恢复。

## 当前文件实测

`parse-validation.json` 记录全量结构验证：708 个 NPK，24,053 个 IMG 条目，23,693 个不同逻辑路径，2,987,218 帧。
每条 NPK 范围、IMG 帧表及像素块长度均经过检查；没有解析错误，也没有未消费尾随字节。

| IMG 版本 | 条目数 | 确认的布局 |
| --- | ---: | --- |
| 1 | 23,498 | 32 字节头，帧记录与像素数据交错 |
| 2 | 555 | 32 字节头，完整帧表后顺序存放像素数据 |

NPK 文件以 `NeoplePack_Bill\0` 开始，`+16` 为小端 `u32` 条目数。
每条目录记录 264 字节：小端 `u32` 绝对偏移、`u32` 长度、256 字节异或名称。
名称密钥前缀为 `puchikon@neople dungeon and fighter `，随后重复 `DNF`，截为 255 字节后追加零字节。
当前路径以 ASCII 为主；读取器允许严格 CP949，并保留名称原始字节。

v1 签名为 `Neople Image File\0`，版本位于 `+24`，帧数位于 `+28`。
v2 签名为 `Neople Img File\0`，`+16` 为帧表长度、`+20` 为原始保留字段、`+24` 为版本、`+28` 为帧数。
普通帧为 9 个有符号小端 32 位字段：颜色格式、压缩类型、裁剪宽高、存储长度、裁剪 X/Y、完整画布宽高。
链接帧颜色格式为 17，只有颜色格式与目标帧索引两个字段，不占像素块。

| 字段 | 当前实测值 | 实现 |
| --- | --- | --- |
| 颜色格式 | 14 / 15 / 16 | ARGB1555 / ARGB4444 / 字节序 BGRA8888 转 RGBA |
| 链接格式 | 17 | 解引用并保留链及原请求帧，检测越界和环 |
| 压缩类型 | 5 / 6 | 原始像素 / zlib，解压长度必须严格吻合 |

这套颜色解释以独立已知通道测试及当前实际图片核验支持，不能仅凭美术效果推导原引擎的纹理缩放、混合与渲染状态。
`pixel-validation.json` 对 127 个 IMG 的 2,318 帧进行了实际像素解码，覆盖两份 Swordman body、Goblin 与 HardAttack 特效，错误数为零。
没有对所有近 300 万帧执行像素展开，不能将全量结构通过表述为全量像素解码通过。
另外 `empty-sentinel-validation.json` 检查全部 622,251 个 1 × 1、X 等于完整宽度、Y 为零的候选空帧，其原始或解压像素全部为零；没有用非零图片替换透明空帧。

## 路径冲突不能静默处理

当前目录有 360 个重复逻辑路径；`conflict-validation.json` 逐份 SHA256 检查确认这些冲突全部存在字节差异。
没有 `ImagePacks2/NpkIndex.etc`。尚未恢复当前客户端对这些文件的原生加载优先级。

例如 `sprite/character/swordman/equipment/avatar/skin/sm_body0000.img` 同时存在于：

- `sprite_character_swordman_equipment_avatar_skin.npk`，IMG 偏移 3,748，长度 305,925。
- `sprite_character_swordman_equipment_avatar_skin1.NPK`，IMG 偏移 33,702，长度 306,694。

两者第 139 帧尺寸同为 71 × 107，裁剪坐标 (189, 231)，完整画布 500 × 500；像素不同。
`contact-sheet.png` 从左到右是这两份 body 的 139 帧、Goblin body0 第 0 / 15 帧、HardAttackblade1 第 0 帧。
此图用于核验图片读取；不是技能组合的运行截图。

## 独立预览使用接口

实现位于 `combat-preview/resources.py`，仅依赖 Python 标准库。

```python
from resources import Assets, ResourceConflict
assets = Assets(r'D:\dnf\60US\DFO\ImagePacks2')
logical = 'character/swordman/equipment/avatar/skin/sm_body0000.img'
try:
    frame = assets.frame(logical, 139)
except ResourceConflict as conflict:
    print(conflict.candidates)
    # 仅为显式预览配置，不代表已确认原客户端优先级。
    frame = assets.frame(logical, 139,
        package='sprite_character_swordman_equipment_avatar_skin.npk')
png_bytes = frame['png']
```

- `Assets(root, selections=None)` 可传入 `逻辑路径: NPK 文件名` 的显式选择。
- `resolve(logical, package=None)` 返回映射；冲突异常包含 `logical` 和 `candidates`。
- `frames(logical, package=None)` 返回完整帧表、版本、原始字段及来源。
- `frame(logical, index, package=None)` 返回 PNG 字节、尺寸、裁剪坐标、来源。
- `select(logical, package)` 对该实例保存显式选择。
- 路径标准化处理斜杠、ASCII 大小写和可选 `sprite/` 前缀；`%04d` 等未完成替换一律拒绝，调用者必须提供确切装备路径。
- 来源包含 NPK 完整 SHA256、IMG SHA256、目录记录偏移、帧记录及像素块的相对/绝对偏移、原始字段、链接帧链。
- 未知版本、颜色、压缩、损坏数据、缺资源和未选定冲突均明确报错，不输出代替图片。

验证命令：

```powershell
python -X utf8 -m unittest discover -s combat-preview/tests -p test_resources.py -v
```

7 项测试覆盖已知通道像素、独立 PNG 块 CRC / 解压、v1/v2 位置、链接环、损坏 zlib、资源越界、路径冲突和来源保留。
`source-identities.json` 记录全部 NPK 源文件身份；`samples.json` 记录导出的各样本来源。

`dnf-rebuild/rep-player/.../src/resources.cpp` 用作格式线索；当前实现以本目录实际 60US 字节检查为接受依据，未接受其后期版本、DDS、调色板、atlas 或隐式 fallback 分支。
