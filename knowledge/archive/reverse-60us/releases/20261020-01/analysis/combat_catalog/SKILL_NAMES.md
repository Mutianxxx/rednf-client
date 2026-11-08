# 当前60US技能显示名称

全部688条注册技能的显示名称已从当前 `Script.pvf` 解析成功。没有使用现代版本的中文技能映射覆盖当前资源。
当前档案 SHA256 为 `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。

复用当前 `Pvf60` 的解密/CRC与 `Catalog` 的有序脚本解析，新增 [string_names.py](../../combat-preview/string_names.py) 只处理名称引用：

```text
SKL [name] <12::name_17745>
  → string.usa.lst : 12 `Skill/Skill.usa.str`
  → skill/skill.usa.str : name_17745>@GBK936@<原CP936字节>
  → 鬼斩
```

SKL和注册表沿用已有严格CP949解码。STR每行的 key 是ASCII；值先检查显式编码标记，`@GBK936@` 后按CP936严格解码；无标记值沿用CP949。没有全表先用CP949解码并忽略错误。
遇到重复key、缺key、不支持的编码或非法字节会记录未解析状态，保留原文件键名；当前688条都解析成功。

[skill-name-resolution.json](skill-name-resolution.json) 保留全部结果、原引用、SKL字段offset、string注册行、STR值offset、行号、编码和原内容SHA256。
界面名称、英文副名和图标分别读取原 `[name]`、`[name2]`、`[icon]`，英文文件键名和技能ID继续显示，支持中英文搜索和主动/被动/已定位预览资源筛选。

| class0技能ID | 原文件键名 | 当前资源的[name] | 当前资源的[name2] |
|---|---|---|---|
| 1 | guard | 格挡 | The Guard |
| 2 | reflectguard | 鬼印珠 | Ghost gate return |
| 5 | hardattack | 鬼斩 | Devil Slash |
| 8 | tripleslash | 三段斩 | Triple Slash |
| 32 | releasewave | 波动爆发 | Release Wave |

此前预览及历史逆向报告把 `skill32/releasewave` 写作“裂波斩”。此次界面按当前PVF改为“波动爆发”；历史合同的技能ID、路径、函数地址没有因显示名改变而重绑。
名称是当前资源事实，不能据此推断该技能的完整释放控制器，亦不代表已经逆向了原客户端字体或UI绘制。

参考过 `D:/dnf-rebuild/rep-player-1031-pvf/src/pvf_script_preview.cpp` 的 `displayName()` 链路。
其新版PVF使用 `n_string.lst` 的二进制表达式；当前60US为文本 `string.usa.lst` 和 `<id::key>`，所以复用了查表思路而非其版本格式。

验证包括独立的缺key/重key/显式编码测试，以及 [skill-ui-browser.json](../preview-validation/skill-ui-browser.json) 中的六职业名称检查、中英文搜索、筛选、实际图标、鬼斩合成和1100px界面宽度检查。
