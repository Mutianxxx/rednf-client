# 全量审计复现与验证边界

先保留本地原始输入。本轮没有改动 PC 客户端、PVF、Lua 项目、Android 来源目录或历史导入快照。研究脚本只写 `research/`、新增文档／测试和明确的验证产物。

用户随后提供的服务端和外部 Android 新修订已另建快照；基础链之后须继续执行 [补充链](13-readiness-and-supplement-validation.md)，将新来源合入最终契约和台账。

本机 Python 是 `D:\ProgramData\anaconda3\python.exe`。基础查询和 SQLite／PVF 解析使用标准库；PNG 预览需要 Pillow，契约校验需要 jsonschema；原生执行和缺失符号恢复使用 `unicorn==2.1.4`、`capstone==5.0.7`。本机后两者安装在工作区 `gba-research/third_party/research-python`，也可安装到自己的 Python 环境。没有安装完成的 Ghidra 不计入已具备能力。

在 `dnf-result` 中按依赖顺序执行：

```powershell
python -m pip install unicorn==2.1.4 capstone==5.0.7 Pillow jsonschema
python -X utf8 -B tools/audit_pc.py
python -X utf8 -B tools/audit_assets.py --verify-pixels
python -X utf8 -B tools/audit_code.py
python -X utf8 -B tools/audit_runtime_sources.py
python -X utf8 -B tools/verify_native_rules.py
python -X utf8 -B tools/trace_android_loaders.py
python -X utf8 -B tools/finalize_research.py
python -X utf8 -B tools/build_world_model.py
python -X utf8 -B tools/build_behavior_contracts.py
python -X utf8 -B tools/publish_audit_index.py
python -X utf8 -B tools/verify_research.py --all-bytes
python -X utf8 -B -m unittest discover -s tests -v
python -X utf8 -B tools/validate_bundle.py --check-inputs
python -X utf8 -B tools/verify_artifacts.py
```

`audit_pc.py` 已有相同 PVF 完整扫描时跳过；需要重建才加 `--force`。分项扫描可以使用各自数据库，汇总 `finalize_research.py` 应在扫描完成后运行。全量校验和汇总写入不要同时执行。查询／浏览器为只读；最后的交付清单不包含 SQLite 临时协调文件。

`verify_research.py --all-bytes` 检查全部 PC 条目与 PVF 原字节一致，并对全部 147,267 份 token 脚本重组字节；同时检查全部 BNV 对象、loader 异常、汇编索引、技能文件、系统契约和 SQLite 完整性。`validate_bundle.py --check-inputs` 校验原有 102,741 份导入及其外部来源、PC 文件哈希、全任务导出和新增测试／文档／产物。

原生规则验证先比较实际 ELF 字节，再用合成内存运行原指令，边界输入包含负的 8／16／32 位解释、环绕、各类型成功／失败。加载器追踪使用真实 ELF 与原始资源，`openFile` 强制返回当前输入资源，分配／格式化／清零／释放使用记录过的替身；GOT 对应结构清零。它能证明给定输入在该加载器分支中如何读取，不能证明角色、地图编号或完整游戏运行一致。

各报告中的 `structural`、`consumer-traced`、`isolated-execution-verified` 与 `runtime_equivalence_verified` 含义不同。台账不是全部 FAIL 列表：动态资源绑定、未命名字段、服务端未知、源文件异常、尚未逐分支审核的代码和目标端实际测试分别记录。完整 PC 行为与新平台的游戏验收没有在本轮执行，不能用本轮 PASS 替代。
