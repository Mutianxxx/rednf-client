# 新版本资料入口与补充复现

新端口应从 [new-version-readiness.json](../research/new-version-readiness.json)、[25 类系统契约](../research/system-contracts.json)、[逐项台账](../research/gap-ledger.jsonl)开始，而不是从旧 GBA 技能子集推断整个游戏。原版数据、源码观察、已验证规则和平台配置分别保留。

## 可以据此开始的工作

完整 PVF、NPK／IMG／ANI／音频索引、全部任务与技能原字段、世界模型、三方代码、服务端源码及检索工具现已集中在本目录。新版本无需重新猜测源文件位置、ID 命名空间、地图候选、随机语音子节点或原图尺寸。PC 原数据全部保留，GBA 缩放、CD、免材料、按键和 SRAM 策略不进入原版定义。

安卓可采用完整 JSON 列表实现任务运行时，也可对现有二进制任务结构做扩展。前者读取有序字段、动态长度条件／奖励和稳定 PC ID；后者必须另做编号映射、编码、消费者逻辑、额外存储及迁移。现有 225 字节、三个条件槽的结构不能无损容纳所有 PC 任务，两条实现路线均不意味着把当前导出直接注入 APK 就能运行。

## 尚不能声明原版一致的部分

这些是本次已定位并保存验收条件的剩余证据／实现工作，不藏在“资源已齐”之后：

| 类别 | 目前具备 | 仍须验证 |
|---|---|---|
| 版本对应 | PC／PVF／APK／源码文件哈希和修订历史 | rednf 原 ELF 及其同版 PVF；27／26 常量差异；ID 与协议对应 |
| 技能与动作 | 全部 SKL／ANI／CHR、可读 NUT、12 条补充 PC 实现研究、宿主 API 调用点 | PC 原生宿主语义、内建技能状态机、取消／输入窗口、多段命中与清理；不能用 ANI 存在替代控制器 |
| 战斗与成长 | 服务端伤害管线／结构、经验与任务奖励消费者、隔离规则模型 | 全部调用者赋值、原 x87 舍入／整数宽度、PvP 与活动分支、原运行对照 |
| 世界与 AI | 全 MAP／TWN／DGN／TIL、候选房间、AI／ACT、原装饰与动态对象 | 概率／调度／仇恨／机关原生消费者、完整场景合成与通路实测 |
| 装备经济 | 全物品脚本、掉落／强化／商店／修理源码及参数 | 随机数、权重、事务、归属、消耗、保护、回滚和时效的完整运行规则 |
| UI、声音与交互 | 原资源、UI 字段、音频组和平台实现参照 | 原生布局／混合／焦点／距离语音／混音和用户操作轨迹 |
| 保存与联网 | 平台旧存档、服务器 DB／消息处理源码和注册 | 目标端统一存储格式与迁移、事务边界、同版协议／组队同步和断线恢复 |
| 目标端验收 | 资料结构、原生隔离函数及工具验证 | 选定引擎／硬件后，角色全流程、录像／音频对照、性能、长期存档与实际设备验证 |

可读源码中的每个候选函数仍带有词法或展开状态；未恢复的宿主接口各有调用点和 gap。第三方库、内部／测试对象、空文件和源数据异常也保持明确处置。台账中的 open 数量是研究对象与证据问题数量，不是游戏缺陷数，也不是还原进度百分比。

## 本轮补充复现

在 `dnf-result` 目录运行。先完成 [基础审计链](11-full-audit-reproduction.md) 到 `finalize_research.py`，再依次执行：

```powershell
python -X utf8 -B tools/import_revisions.py
python -X utf8 -B tools/audit_server.py
python -X utf8 -B tools/expand_server_aggregators.py
python -X utf8 -B tools/merge_android_revision.py
python -X utf8 -B tools/verify_server_rules.py
python -X utf8 -B tools/build_server_contracts.py
python -X utf8 -B tools/publish_research_supplement.py
python -X utf8 -B tools/verify_research.py
python -X utf8 -B tools/validate_bundle.py --check-inputs
python -X utf8 -B tools/verify_artifacts.py
```

`import_revisions.py` 拒绝覆盖不同内容。本次修订固定在 `android-revision-20261016`；今后来源再变应建立下一修订目录，不能覆盖此目录重新定义历史。当前源码快照也只接受相同字节，来源更新应另建快照。

`verify_server_rules.py` 使用工作区原有 `dnf-gba/third_party/xpack-arm-none-eabi-gcc-15.2.1-1.1`，以及 `unicorn==2.1.4`、`pyelftools==0.32`。编译器路径、哈希、版本、编译命令、六份输入哈希和 ELF／包装文件哈希都在报告中。迁移主机可以调整工具位置并重新生成报告，不能把旧报告当作新编译器已验证。

`verify_research.py --all-bytes` 的全 PC 字节／token 核对已保存于 [全字节报告](../research/verification-full-byte-report.json)。补充没有改 PC 原字节；普通 `verify_research.py` 会再核对新增归档字节、系统台账与 SQLite 完整性。`validate_bundle.py --check-inputs` 包括旧／新安卓快照、完整服务端快照、全部外部当前源文件哈希、PC 来源、任务转换、链接与回归测试。`verify_artifacts.py` 只读核验最终清单。

## 查询和浏览

```powershell
python -X utf8 -B tools/research_query.py server-text --q "compute_quest_basic_reward_exp" --limit 10
python -X utf8 -B tools/research_query.py server-tags --q "damage fomula constant"
python -X utf8 -B tools/research_query.py server-includes --q "STQuestScript"
python -X utf8 -B tools/research_query.py code --source rednf-expanded --q "importQuestScript"
python -X utf8 -B tools/research_query.py gaps --q "native-host"
```

`browse.cmd` 启动 localhost 浏览器服务后，手动打开 `http://127.0.0.1:8765`。可以选 `rednf-server` 查文件／原文，使用服务端全文和 PVF 标签按钮寻找消费者；图像时间轴仍使用 PC 原尺寸资源。此浏览器是资料工具，未模拟完整客户端渲染和技能控制器。
