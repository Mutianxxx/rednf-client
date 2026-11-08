# 来源、编码与阅读边界

## 来源定位

默认源根：`D:/dnf-rebuild/pvf官方文档/sample(官方注释)`。2026-10-17 编目为 85 个文件：文件大小、SHA256、类型、严格解码结果和纯文本行数保存在工作区 `dnf-native-demo/reports/pvf-docs/source-inventory.json`。重新接收或移动资料后先重建清单，引用前核对文件哈希。

样例没有统一发行号。`equipmentsamplebytool.equ:2` 写有 20120625；`newmonstersample.mob:757` 含 2012-02-21 开发状态说明；另有 `090302stackablesample.stk`、`actionlibrary/080324ver/` 和新旧 monster 样例。文件名中的日期只能作为该文件标签。不能据此证明用户中文客户端对应同一构建。

## 编码和格式

- 有韩文注释的纯文本主要是 CP949；不少也能以 EUC-KR 严格解码。不要用 GBK 读这套韩文样例，也不要因此改变中文客户端已知的 GBK/CP936。
- `equipmentsamplebytool.equ` 是 UTF-8，可严格 UTF-8 解码而不能严格 CP949 解码。纯 ASCII 的 ACT/ANI 小例子标记为 ASCII；“某编码解码成功”本身不能证明来源编码。
- 11 个 `ai_doc/*.rtf` 是 RTF，头部声明 `ansicpg949`。CP949 字节通过 RTF 转义保存，不能当普通文本替换反斜线后直接解释。
- `manual for adding ui action system.doc` 是 OLE Word97 文档，手册内部标题为 UI 动作系统 Revision 1.0。用格式感知方式提取正文；图片、表格布局及页码需保留区别。
- 3 个零字节文件：`animation.ani`、`animationsamplebytool.ani`、`actionlibrary/guide.txt`。`actionlibrary/throwdown2.ani` 非空，只是小实例，不能充当完整 ANI 规格。

禁止使用 replacement 解码掩盖坏字节。出现新编码或未知二进制时先分类并记录，再选相应读取方式。

## 工具

技能自带的 `scripts/read_source.py` 只读取源；`show` 限制在根目录内，二进制 DOC/RTF 明确拒绝作为纯文本输出。目录命令可以生成 JSON 清单，输出不能位于源目录。

```powershell
python -X utf8 -B <skill>/scripts/read_source.py --root 'D:/dnf-rebuild/pvf官方文档' catalog --output <工作报告目录>/source-inventory.json
python -X utf8 -B <skill>/scripts/read_source.py --root 'D:/dnf-rebuild/pvf官方文档/sample(官方注释)' show mapsample.map --start 62 --end 80
python -X utf8 -B <skill>/scripts/read_source.py --root 'D:/dnf-rebuild/pvf官方文档/sample(官方注释)' show actionsample.act --find 'LAYER'
```

本次 Word 主文本的可重复提取工具位于工作区 `dnf-native-demo/reports/pvf-docs/extract_ui_manual.py`，限定本文件的 Word97 FIB/CLX 结构；结果和提取限制保存在同目录。导出文本的行号不是原文页码，嵌入截图未提取。

## 已读范围和证据不足

本技能重点读取 MAP、TIL、ALS、SKL、UI、UI ACT、OBJ、ATK、CHR、DGN、TWN 和 UI 手册；ACT/MOB 大文件按相关章节阅读。逐文件覆盖记录在工作区 `dnf-native-demo/reports/pvf-docs/review.json`。其他任务、商店、装备、RTF AI 等文件已编目，不能说都已逐字读完，后续需要时返回原文件。

当前摘要没有证明：完整 ANI 二进制布局、IMG 裁剪原点、全部图层数值顺序、Y 排序比较器、480→600 的完整坐标公式、全套 HUD 固定坐标、技能插值舍入或完整伤害公式。这些仍需当前客户端资源/代码研究及实际画面对照。
