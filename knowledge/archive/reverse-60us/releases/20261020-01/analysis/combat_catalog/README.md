# 60US PVF 注册和文本结构证据

本目录来自 `D:/dnf/60US/DFO/Script.pvf`，SHA256
`23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。
2026-10-20补充：688条注册技能的中文显示名和英文副名已从当前字符串表解析，见 [SKILL_NAMES.md](SKILL_NAMES.md)。名称解析与技能控制器恢复分开计数。
读取复用 `analysis/pvf60.py` 的已验证解密和 CRC 实现，原档案只读。

当前 `character/character.usa.lst` 和 `skill/skilllist.usa.lst` 注册 6 职业：
Swordman、Fighter、Gunner、Mage、Priest、ATGunner。它们注册 688 条技能，
其中 `[type]` 为 active 的 362 条、passive 的 326 条。PVF 共含 690 个 SKL，
另两个位于 `sample/`，没有出现在职业技能注册表。

这些数据证明注册、字段和资源存在。**所有 688 条技能控制器、技能到动画/ATK
的绑定、命中接受规则仍标为 unknown。** 同名资源不能证明函数调用和特效生成。
当前客户端的逆向证据优先于 `dnf-rebuild` 的重建代码或推测；本目录没有导入
1031 的字段解释或技能映射。

`combat-preview/pvf_model.py` 无第三方依赖。`parse_document(raw, path=None)`
严格使用 CP949，返回原字节、源 SHA256、有序 token 和 tag 事件、显式块嵌套、
重复字段、原始字节 offset 和行列，以及异常列表。没有关闭标签的字段保持有序
属性；不会把 CHR 的 growtype、ANI 的 frame 等隐式域擅自改写成已知语义。
字符串中的 `[active]` 和注释内的标签不会识别为结构标签。

`Catalog(pvf_path)` 提供 `.summary()`、`.characters`、`.skills`、
`.document(path)`、`.animation(path)`。所有路径索引使用完整规范化路径。
每个来源记录原 PVF 目录项的路径 hash、CRC、原档案绝对偏移、逻辑长度和
解密内容 SHA256。属性和资源引用的 offset 指解密后脚本中的字节位置。

CHR 共有 778 个有序资源槽，其中 11 个是空字符串（Gunner 2、ATGunner 9）。
空槽保留其索引，`empty=true`、`path=null`。非空引用有 547 个 ANI 槽、220 个
ATK 槽，均在当前 PVF 中存在。547 个 ANI 槽去重后为 533 个文件，共解析出
2,817 个 frame 段、454 个 ATTACK BOX、4,275 个 DAMAGE BOX。box 保留原始
六数值，坐标约定及原生碰撞消费语义仍需 EXE 证据。

一个 ANI 文件有声明差异：`character/priest/animation/rest.ani` 的
`[FRAME MAX]` 为 16，实际存在 17 个 frame 段。解析器保留全部并报错；原生
客户端是否忽略多出的帧还未确定。两个注册 SKL 有未正确闭合的 `[level info]`：
`skill/fighter/dashpunch.skl` offset 2714、
`skill/mage/summonspiritwaterhigher.skl` offset 3985。原数据与词法顺序保留，
不会静默修改其作用域。

全包扫描读取了 54,531 个 ANI，CRC 和 strict CP949 解码均成功，共识别
265,633 个 frame 段、12,076 个 ATTACK BOX、40,348 个 DAMAGE BOX。
这不等于所有资源均可正常播放：保留了 84 项 FRAME MAX 差异、3 个原文漏
`]` 的 FRAME 标签、1 个以单引号错误结尾的反引号字符串、10 个无 frame 的
资源（其中两个空文件）。另有一个 DAMAGE BOX 行以单斜线写韩文注释，故保留
了六个数后的三个词并报告异常；解析器没有把原文改成推测的注释语法。

输出：

- `summary.json`：档案身份、职业/技能计数、未知覆盖、异常。
- `characters.json`：6 职业来源和逐字段逐索引的 CHR 槽，包含空槽。
- `skills.json`：688 技能的全部有序字段、mode 块、static data、level info 和 token 证据。
- `skill-coverage.csv`：适合人工审阅的轻量覆盖表，每技能一行。
- `document-index.json`：已读取脚本的档案目录项与 SHA256。
- `chr-animation-validation.json`：533 个 CHR 引用 ANI 的逐文件结构校验。
- `all-animation-validation.json`：全包 ANI 结构扫描结果，存在时以其实际计数为准。
- `character__swordman__animation__hardattack.ani.json`：逐帧示例，18 帧。

复现：

```powershell
python -X utf8 combat-preview/catalog.py --animation character/swordman/animation/hardattack.ani
python -X utf8 -m unittest discover -s combat-preview/tests -p test_pvf_model.py -v
python -X utf8 analysis/combat_catalog/validate.py
python -X utf8 analysis/combat_catalog/validate.py --all
```

`skills.json` 包含重复的完整证据，约 80 MB；界面应投影需要的字段后传输，
避免把完整证据对象当作下拉列表数据。动画每帧的 `images`、`image_positions`、
`delays`、`attack_boxes`、`damage_boxes` 都是按出现顺序保留的数组；
`fields` 保留所有字段，`unknown_fields` 保留未提供便捷视图的字段。
