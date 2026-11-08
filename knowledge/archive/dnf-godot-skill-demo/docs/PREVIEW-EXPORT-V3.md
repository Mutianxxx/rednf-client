# V3：保留缺口的诊断预览导出

按用户“调用链不阻塞，只提示，按当前链展示”的要求，技能包现在同时保存真实闭包状态与独立诊断预览。未添加逐技能/逐职业分支，主原生工程仍只读。本文记录导出合同；实际运行与通过数由父级串行测试报告提供。

`export_skill` 继续保存原 `status`、`program_status` 和严格编译得到的 `program`。只有严格程序为 `executable` 时才加入正式 actor skills；`partial`、`missing-native-caller`、`passive` 不会因可预览而计入完整技能。真实 executable IR 不改写。

新 `skill.preview` 包含：

- `program`：有可解释无条件 entry play 时生成的诊断 IR；无此入口时为 null。`skill.preview_program` 是供运行时使用的同一描述，缺失时为空字典。
- `actions`：仅来自保存的精确 `action_ids`，通过 CHR tag/occurrence/slot 生成装备动作组合；附人物 SourceRef、完整 source_action，以及存在精确对应时的基础攻击描述。资源相似或技能名不能产生动作关联。
- `resources`：仅来自当前技能已有显式依赖的 ANI/OBJ，重复路径合并但保留每一引用的 owner/offset/role。OBJ 仅使用其显式 basic motion 和 attack info。每项附自身 SourceRef、clip 或错误，不给它捏造技能调用顺序、生成时间或坐标。
- `diagnostics`：省略语句/控制块和资源失败，含来源及 offset。预览整体 `execution_proven:false`；完整原程序的诊断副本可保留其已有执行证据，仍不增加计数。

`PreviewProgramCompiler` 独立于严格编译路径。它消费相同通用 API，但遇不支持语句时记录诊断并省略。未知 if 条件会省略 then/else 整体；循环、switch、try/catch、函数等未知控制块保持不透明，禁止把块内动作提为无条件操作。省略块内被赋值的变量会失效，避免后续使用旧值猜测分支结果。无法解释的 return 表达式仍保留流程终止边界。已支持的旗标条件仍为条件 IR，不摊平为每个旗标都执行。

只有 entry 中存在可解释的无条件 play 才返回 `diagnostic_preview` 程序，保留 `original_status`、来源、诊断及 `source_ani_end_fallback:true`。父级运行时在源 ANI 结束而程序未终止时结束预览，不无限等待。PO 仍要求既有严格 lifetime/packet/source 闭包；不能为诊断预览创造缺失的 PO 行为。

本次只对选中的技能做按需导出，不扫描全目录动作、不预载全部职业依赖。动作/资源列表是供用户独立选择的证据，不是按列表顺序播放的完整技能。

父级先运行：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tests\test_preview_export_v3.py --report reports\native-preview-v3\python-contract.json
```

再刷新既存 16 包并按需增加三个样例：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools\catalog_pipeline.py refresh-cached --progress-file reports\native-preview-v3\refresh.json
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools\catalog_pipeline.py export-skill --job 8 --skill '8:26:25' --progress-file reports\native-preview-v3\watercannon-export.json
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools\catalog_pipeline.py export-skill --job 8 --skill '8:33:32' --progress-file reports\native-preview-v3\diehard-export.json
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools\catalog_pipeline.py export-skill --job 0 --skill '0:1:0' --progress-file reports\native-preview-v3\guard-export.json
```

样例是源登记 ID，不是代码中的适配分支：男魔法师魔法冰球真实状态保持 partial，可展示可解释片段及精确动作；不死之身保持 passive，可独立查看其三个精确动作关联；鬼剑士格挡保持 missing-native-caller。当前所有 missing-native-caller 保存索引都没有已解析 ANI/OBJ 依赖，不能诚实制造完整预览；该样例验证可导出并提示缺口，用户仍可另选来源目录中的动作。

本子任务未运行测试、导出器、引擎或构建。所有验证须由父级持串行锁执行；冻结 V2 checkpoint 不改。画面、音效与手感仍待用户体验。
