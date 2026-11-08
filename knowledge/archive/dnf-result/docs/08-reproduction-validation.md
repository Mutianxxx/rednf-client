# 复现和校验

基础合并使用本机Python3.13.9，原合并工具依赖标准库。后续全量审计、原生执行和图像查看的附加依赖及完整顺序见[全量审计复现](11-full-audit-reproduction.md)。PowerShell在本目录执行，替换输入目录即可。源码使用UTF-8；PVF文本明确GBK。基础查询、重新转换和核验资料无需网络。

```powershell
# 原证据导入：只读输入，字节相同的已有输出可复用，不同内容会拒绝覆盖。
python -X utf8 -B tools/import_evidence.py --workspace .. --android 'D:\dnf安卓优化\android-dnf-result'
# 从当前PC PVF重新建立无损归档、任务和哈希更正。
python -X utf8 -B tools/consolidate_pc.py --workspace .. --android 'D:\dnf安卓优化\android-dnf-result'
# 共同技能/实体/系统索引及所有外部PC文件哈希。
python -X utf8 -B tools/build_catalog.py --workspace ..
python -X utf8 -B tools/convert_quests.py
python -X utf8 -B tools/build_registry.py
python -X utf8 -B -m unittest discover -s tests -v
python -X utf8 -B tools/validate_bundle.py
# 输入仍在原位置时，另外重验所有原输入哈希（包括外部PC客户端）。
python -X utf8 -B tools/validate_bundle.py --check-inputs
# 交付后仅检查清单，不重写任何产物：
python -X utf8 -B tools/verify_artifacts.py
```

`consolidate_pc.py`、`build_catalog.py`、`convert_quests.py`和`build_registry.py`会重新写明确的派生文件。输入变更时应先固定新版本，保留旧结果，再生成新包。导入工具不写原客户端、APK、安卓结果或GBA工程。

查询示例：

```powershell
python -X utf8 -B tools/query.py quest --name 铁匠林纳斯
python -X utf8 -B tools/query.py skill --name 波动
python -X utf8 -B tools/query.py file --path character/swordman/swordman.chr
```

导入包含安卓完整55,850个文件及GBA资料等；原始导入与补充测试/许可分别登记在 [import-manifest.jsonl](../inventory/import-manifest.jsonl)、[supplemental-import-manifest.jsonl](../inventory/supplemental-import-manifest.jsonl)。21,228个当前PVF内文件由 [pc-evidence.jsonl](../catalog/pc-evidence.jsonl)绑定来源和各旧副本哈希。

最新校验见 [validation-report.json](../inventory/validation-report.json)。它包括文件复制完整性、PC原字节核验、全部任务token原字节重组、列表字段保留、原安卓任务重解析、冲突引用、JSON和新增文档本地链接。`--check-inputs`额外比较现存原输入及5.30GB PC客户端；不带该参数时不声称外部源仍未改变。

[artifact-manifest.jsonl](../inventory/artifact-manifest.jsonl)记录本轮产物的最终哈希（排除其自身及验证报告，避免自引用；导入快照另用导入清单验证）。若修改文档/工具，需重新运行校验生成最新清单。

安卓历史验证仍是静态分析：没有运行APK、设备测帧、实机音画/战斗/存档回归。GBA报告绑定各自ROM与夹具；本次未重新编译或测试游戏，也没有将历史运行结果升级为PC或新端口结果。历史文档原有链接/工具绝对路径保留，合并入口及本轮新增文档的链接另行校验。
