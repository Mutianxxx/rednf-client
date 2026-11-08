# 1031 PVF 独立预览进度 · 节点 03

当前已交付可运行的 GUI 预览，不再只有静态分析或命令行审计器。项目独立于 dnf-native-demo；未经用户验证确认，未向主项目迁移本逻辑。此前 P01–P19 主任务仍按用户要求记录暂停。

## 启动

双击 `Start-1031.cmd`，或 `build/rep_pvf_preview.exe`。默认从 `D:\dnf-rebuild\DNF1031客户端\Script.pvf` 与 `ImagePacks2` 加载；顶部可改路径。说明见 [README-1031.md](../README-1031.md)。源码入口为 `src/pvf_preview.cpp`，重建用 `build-preview.ps1`。

## 本节点实际实现

- 复用 rep-player 的 IMG/NPK 解码与原有 GPU 路径，以 PVF ANI 帧数据驱动画面；不需要 REP 录像。
- 原生窗口先打开，再后台加载 PVF；完整 SHA256 与索引解码以两个独立任务重叠执行，来源缓存不并发修改。进度、错误可见，错误另存独立会话日志。
- 无损 ANI 模型保留原 bytes、SHA256、图集原文、属性顺序、重复属性、字节偏移、时长、事件和几何盒；未知长度和损坏格式明确拒绝。
- 十字斩组合：身体、4条已注册技能效果、对象基础/附加 ANI，独立时钟；Slash2 来源事件500ms触发对象预览。slot2/3默认关闭，资格未恢复。PTL读取当前来源首末速度与变化时间，当前显示是double曲线近似，未叠加角色修正，也未宣称原生最终距离。
- 十职业 CHR 共1388条记录：1321条非空ANI引用、67个空槽，保留源顺序、重复和缺失诊断。另有完整PVF ANI浏览入口。
- 当前 common.nut 的明确技能注册映射：两职业共49组；其他8职业保留“本文件无显式loader”的缺口，继续从其他脚本/native消费者分析，不能推断它们没有特效。组内同播和层序属于资源检查策略，不是技能状态机。右上角可以单独选择某个来源轨。
- Goblin动作按MOB标签实际读取；手动待机、两种受击、倒地、起身。红/蓝框显示来源攻击/受击几何；可选接触触发受击测试策略，不计算原生伤害、HP、硬直、异常。
- 暂停/重播/定位、16.7ms步进、速率、方向、缩放、基础皮肤模板编号与分层开关可用。图像模板绑定是工具配置，不是完整装备系统。
- 导出JSON可追溯NUT/SKL/CHR/OBJ/PTL关联、ANI/member哈希、源帧、事件、原始和实际IMG、NPK/PVF容器、偏移及IMG哈希。缺失资源不会用默认图标掩盖。

## 自动验收

- 最终构建完成，无编译警告；EXE SHA256：`d52a1e00c805f9d51479c17f2f2a7575cb4f8869395c07284ecd5acbd7067553`。
- 真实1031来源、解析拒绝、时间边界、来源身份、30/60/144Hz预览事件区间遍历及补tick、双向离屏渲染、移除人物/效果/对象的像素差、重复定位、手动受击测试：**41项通过，0失败**。这是预览时间线检查，不是游戏战斗调度验收。最新报告由 `validation/latest-preview.json` 指向。
- 十职业各一个源待机和攻击动作：**20/20资源完整、20/20离屏可见，139/139图像帧解码、0缺失**，报告 `validation/character-preview-audit.json`，保存20张离屏BMP。
- GUI隐藏窗口自动检查通过：消息循环、异步读取、真实筛选/模式切换/应用所选源动作、时间条暂停定位、步进和方向；`validation/ui-check-final.json`。前台画面仍待用户。
- 无效PVF路径负例通过：界面错误处理和日志生效，返回预期失败；`validation/negative-load-check.json`。
- 注册特效资源/像素审计：**49/49组完整加载且离屏可见，223/223条循环展开后的ANI轨存在并加载，1315/1315图像帧有效、0缺失**；Kalla两组各16条来源轨。`validation/registered-effect-render-audit.json` 与 `validation/skill-effect-registration-audit.json` 保留逐组与来源覆盖，目录合计1450项（含缺口诊断和空槽）。
- zlib独立静态构建及上游示例通过，253份第三方源码复制哈希一致。来源/构建日志在 `tools/dependency-build/`。
- `validation/final-build-identity.json` 记录当前源码、EXE与编译manifest一致性；系统DLL导入见 `validation/executable-imports.json`，无主项目游戏程序运行依赖。
- 首轮错误帧号断言和不支持Kalla循环拼接的失败报告保留；后续修正只改错误断言/有界来源抽取，不修改PVF去迎合检查。

## 待用户及未完成

前台画面、声音、手感及原版动态对照均未验收。建议先测试默认十字斩各层、500ms附近的血十字、朝向、怪物动作以及其他职业源动作，并用导出来源报告反馈。

完整技能调度/资格、ALS组合、装备与武器层、音效、精确混合、伤害结算、反应索引、受击暂停、死亡效果、PVP UI逐帧映射与“菜单”“商城”字体复刻尚未完成。资源注册检查、单条ANI浏览、可见像素和几何相交均不能算这些机制完成，也不算全十职业beta验收。

## 节点备份与恢复

节点03使用 `tools/checkpoint-preview.ps1` 在 `D:\dnf-rebuild\rep-player-1031-pvf-checkpoints` 新建目录，完整保存源码、EXE、依赖源码、构建和验证产物、本文及逐文件SHA256。精确目录与恢复启动器由 `validation/latest-checkpoint.json` 记录；备份根有 PROGRESS.md、CHECKPOINT.json、SHA256SUMS.csv，`source`就是可恢复的项目根。原PVF/NPK仅通过只读路径引用，不复制或改写原客户端。

历史节点01、02a–02d保持不覆盖；当时只有静态分析及审计EXE，详细记录保留在 [PROGRESS-node02-history.md](PROGRESS-node02-history.md)。本节点才新增GUI实现。

继续时阅读 `CURRENT_TASK.md`、本文、技能渲染追踪和静态依据。下一步按用户画面验证结果处理时序/坐标/装备层差异，继续闭合其他职业真正的技能消费者及命中因果；用户确认后才迁移到主项目。