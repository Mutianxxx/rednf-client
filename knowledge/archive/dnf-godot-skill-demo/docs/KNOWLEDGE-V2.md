# 新增 pvf-utils-info：通用技能、特效、判定与 UI 复核

2026-10-21。本轮将用户新放入的 `dnf-部分知识库/pvf-utils-info/` 纳入整库复核，并更新项目本地的知识政策和三个技能入口。核心结论：**可以统一动画、图层、实体、攻击包、命中和受击执行，并按宿主 API 类别扩展；资料没有提供一份覆盖所有旧职业硬编码技能的完整原生 caller。** 不能把换 Godot 引擎、资源依赖预览或静态高覆盖矩阵当作全部技能已经恢复。

本文件只报告知识复核和实际架构边界；Godot 的编译、运行、画面与交付结果以父级本轮收据为准。主原生工程保持暂停只读，原始知识包、PVF、NPK、历史候选和用户存档未修改。

## 整库重新检阅的范围与收据

| 项目 | 记录 |
| --- | --- |
| 全库文件 | 6851，268,519,838 bytes |
| 与上一轮差异 | 新增437文件，全部位于 pvf-utils-info；既有6414文件零修改、零移除 |
| 可抽取文本 | 4749份去重文档，26,533,483字符；重复文本2018份 |
| 全文件覆盖 | 每文件原字节哈希、类型/编码、支持的全文抽取、结构/标签/API/不确定性重新扫描 |
| 实际语义阅读 | 本轮44份去重文本、45个来源文件的完整文本或明确选段；上一轮51条来源阅读记录保留。逐条源哈希和实际范围见 semantic-reading.json |
| 提取错误 | 0；两遍源字节核对无变化 |
| 附带程序 | EXE/DLL只读身份/PE头；执行知识包程序、脚本次数0 |
| Options/Defaults镜像 | 39对，37对相同、2对不同；差异为配置/书签层，不把所有镜像默认为一份事实 |
| XML | ItemCodeHoverConfig.xml只做安全XML结构提取，175元素；未执行其配置或外链 |

全字节读取、全文结构扫描、语义阅读和运行验证是四层证据。未逐句核实4749份文档的全部命题；未阅读的图中文字、外链、不可解码二进制和长账本的未选段不算已语义验证。未采用配置中的账号/服务字段，未输出其敏感值。

机器收据位于 `reports/knowledge-v2/corpus/summary.json`、`structure-review.json`、`file-coverage.json`、`semantic-reading.json`、`baseline-comparison.json`。`source-preservation.json` 记录复核后重新读取全部6851个源文件、268,519,838字节，哈希零变化；`REVIEW-RECEIPT.json` 绑定本次知识报告和政策文件。源manifest SHA256：`b49a833b036f47992a7014cd48244ec8f8c9e8a9231e7c04a7914e979580c670`；全文抽取 SHA256：`910aecf5e12fc3fad1dab37a3e08b195ddeb226c6c2321d5830508f76b984bfb`。

## 新资料的含义和版本边界

优先采用新包对文件/入口/API组的解释，保留包自身的“需验证”和禁用边界。它的 `Resources/AgentKnowledge/indexes/skill-state-nut-runtime-high-coverage-matrix.zh-CN.md:9` 明确“100%”指入口矩阵、API族、模式代表、registry规则和研究检查闭环，**不指每个技能完整执行**；同文45–51行要求现有模式不再逐技能深拆。

其“主目标”含 `qf_bloodyrave_bloodsword_common.nut`、`ap_qf_*` 定制链，见 `indexes/skill-state-nut-runtime-boundary-audit.zh-CN.md:28`。文档的当前主目标、辅助对照、历史专项是不同证据层，不能自动并入本项目当前1031（PVF SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`）。所有state/skill/PO编号、动作槽和参数从本1031实读；后期新增职业、定制取消和UI NUT不直接套用。

已发现文档内部快照冲突：`dictionaries/skill-learnability-command-cooldown-fields.zh-CN.md:61` 称 `startSkillCoolTime` 未命中，完整runtime API词典59行与HolongLight索引却记有调用。记录两者；由当前1031调用点裁决，不选便利的解释冒充统一事实。`recovered-source-libraries.txt` 提供 PvfCode/NPK 等工具库名，它没有交付游戏原生所有技能caller实现。

## 动画、特效与贴图的重要补全

新的 `Resources/OfficialAnnotationTranslation/animation.ani.txt` 为非空文本，旧官方样例目录的空文件结论仅适用于旧目录。本次优先读新样例，不继续声称全库缺ANI文本说明。

| 证据 | 可采用语义 | 实现要求与边界 |
| --- | --- | --- |
| animation.ani.txt:23–33 | IMAGE/IMAGE POS/IMAGE RATE/IMAGE ROTATE/RGBA/DELAY是独立字段，原大小为1.0 | 保留IMG裁剪原点、动画偏移、缩放和毫秒，不能把1.0当1% |
| animation.ani.txt:74–88 | 线性插值涉及RGBA、位置、缩放、角度、CLIP；CLIP相对动画基准点 | 按ANI原点裁剪而非图片左上角，颜色与透明度也进入插值 |
| animation.ani.txt:55–71 | 帧声音、flag和局部LOOP START/END为独立事件/控制 | 文本未证明当前1031二进制property25/26枚举；原值保留，不能按文本顺序绑定数字 |
| sample.ani.als.txt:13–35 | sidecar随父ANI自动读取；add/remove首参是父帧；unique name标识实例 | 同一路径不同unique name可同时存在，子时钟、添加与移除时刻分别处理 |
| equipmentsample.equ.txt:264–268、324–356 | EQU→variation/layer variation→LAY；expand ani第三参决定替换攻击框资格 | 不能把所有装备攻击框无条件和身体合并；未查明资格必须标试验策略 |
| equipmentsample.equ.txt:376–407 | attach target/pos、z revision、floor、sync speed等独立选项 | 不能给所有角色和所有特效套同一Z修正 |
| passiveobjectsample.obj.txt:72–110、126–130 | 附层、粒子、延迟、跟随、寿命、销毁后创建分别配置 | 跟随父、保持相对位置、独立世界位置互斥处理，销毁须连带清理所属层/粒子 |
| actionsample.act.txt:1–39、375–388 | ACT主/子ANI、帧声音、默认ATK、生成XYZ/方向/地图坐标 | 保留嵌套作用域和参数顺序，SUB ANI/PO不是SKL预载清单中的顺序播放 |

`animationsamplebytool.ani.txt:87–93` 的六列攻击盒说明把起止/宽高写成二维混合标注，与该包ANI注释及当前三维数据有冲突。不会据此将已核对的XYZ起点+三轴尺寸改成二维矩形。原property25无参/26 int32形状可从现有解析器和社区二进制摘要看到，**尚不足以作为1031原生枚举证明**。

SKL `[skill preloading image]` 仅是预载，见 `skillsample.skl.txt:154`。它不能确定实际出生帧、生成坐标、层级、次数、运动、攻击归属与清理。正确资源链必须来自实际NUT/ACT/native调用者，再递归ANI/ALS/OBJ/PTL以及ImagePacks2中的IMG。

## 采用通用执行链的具体分工

```text
角色/技能 registry + CHR + 学习/输入条件
    → 注册的NUT/ACT或职业native入口
    → state/substate + 动画实例 + 毫秒时钟/flag/timer
    → 身体 + EQU/LAY + ALS + draw-only + PO/AP/PTL
    → AttackInfo + 三维攻击框 或 source direct-hit请求
    → 接受命中事务/去重/次数/目标过滤
    → 伤害 + hitstop + 受击状态 + 视觉/声音
    → 击退/浮空/倒地/起身/死亡 + 生命周期清理
```

共用的是可执行语义、解释器/宿主和事务。动作槽、资源引用、技能表列、state/substate和注册ID是源程序/内容数据，不能把不同技能的参数都当同一列含义。用户要求禁止逐技能手写补丁：缺新能力时补通用API类别；职业native入口不在PVF时按职业恢复并列明尚缺项。不能把一个技能的 `state45/[0,1]` 或几帧后创建物件规则推广给全职业。

新资料按七种模式覆盖：IRDSQR state+PO、state+appendage/buff/throw、CNAvenger专用族、Creator混合鼠标控制、Common循环注册、script-only被动入口、Priest轻state。`script-only` 说明load_state没有直接注册state，**不说明角色没有技能**；旧技能可能由native状态机调用，宿主不能仅因为没有NUT注册就按名字猜动作。

通用宿主需要：注册/解析；skill条件和一次MP/CD事务；state参数包；当前/自定义ANI和AttackInfo；读写帧/flag/速度/插值；对象身份/目标选择；PO创建/receiveData按宽度顺序读写；timer/多段命中列表；appendage/APD及状态；世界/跟随坐标和运动粒子；draw-only/颜色/缩放/震动；中断/死亡/离场/故障清理。源API有弱定义项时保留诊断，而不静默降成相似动画。

编译器的 `executable` 必须覆盖实际可达控制流和行为；遇动态操作数、未知API、未闭合注册/资源或未支持分支则列 `partial`/`dependency_preview` 并拒绝当完整技能释放。通用VM的人工IR测试通过只能证明VM原语，不能证明源编译器已经支持同样语法。所有技能存在依赖图不等于所有技能可执行。

## 攻击与怪物受击

`.atk` 是payload，不是帧级几何；`.ani` 的ATTACK BOX与目标DAMAGE BOX另读。见新包 `dictionaries/attackinfo-atk-fields.zh-CN.md:62`、跨层词典129–151行。draw-only 闪电线、ALS发光、AP视觉不能仅因ANI有攻击框就自动造成伤害。ChainLightning代表链还展示 `sq_SendHitObjectPacket` 对已选目标直接命中；通用系统要允许这条受控入口，不能强制一切伤害都来自视觉外接矩形。

接受命中后才触发受击、声音、派生爆炸与攻击成功回调。每个攻击实例保存命中对象/次数/多段重置周期；独立PO及二级爆炸有独立攻击账本。源指定排除首目标时应保留。miss、无效目标、同实例重复、攻击失败不触发假受击。

`attackinfosample.atk.txt:14–16` 解释push/lift是力度，不能固定理解为像素；33–37行hit info第三项是命中短停、第四是受击延迟倍率。最终力/质量、硬直/保护和伤害公式需要native或运行证据，演示物理参数显式标重建。MOB的两受击动作保留，选择与重播由共用受击状态处理；非循环反应不会永久停在最后帧/循环受击。浮空反应由落地/物理阶段推动后续状态，不能动画结束即空中站立。

怪物适配也分层：MOB注册/动作槽/装备 → AI条件和返回槽 → ACT触发/行为 → ANI/ATK/PO → 同一combat消费者。基础哥布林追踪策略属于demo策略；完整Destination/MoveMethod或特殊AI未实现时不能称全怪物AI已套用。木桶等使用actionobject/OBJ受击/last action/PTL破坏链，不能直接给一个怪物死亡动画。

## UI渲染与事件链

`.ui` 记录窗口/控件/父子/选项/资源；`[common action]` 引用UI ACT；IMG/ANI在ImagePacks2另核。`.lay`在本包是人物motion层模板，不是UI布局。`.pos`有无依具体版本清单，不强行补全。

通用UI读取器需要解析类型、控件名、坐标、string/int计数、父子、tab/radio关系、初始visible/enable，再执行源事件/状态。mouse enter/leave/LBUP、FRAME、ON TIMING、WHICH/CHECKUP/LIMIT、DO BEHAVIOR、插值、rewind、return应有实际消费者。证据：`uiactionsample.act.txt:1–42` 与45–86。计时以相应事件锚点开始，不是全局无条件闪烁。

`CHECK FUNC`/`CALL FUNC` 只给索引和自定义参数（同样例31–34、81–84），业务实现仍在native。可以先完整渲染和验证button/radio/animation基础交互，未知调用显示诊断；不能据此声称背包移动、技能学习、交易、奖励和任务完成。文字“菜单”“商城”的字体目标与资源链分开，现有中文fallback或字体文件存在不等于像素复刻完成。

## 本轮缺口与验收边界

1. 完整Squirrel宿主和所有旧职业native caller尚未由资料补齐；有限源IR编译器必须诚实标注支持边界，不能转成逐技能模板集合。
2. 二进制25/26枚举、完整图形混合/粒子/局部loop以及所有源状态接口仍需当前1031证据和实际消费者。
3. 原版数值、保护/抓取/异常/高级被动、完整AI/UI业务链及声音不由本次文档复核自动完成。
4. Godot体验版的实际可执行技能、UI消费者、测试与截图须按本轮产物清单报告；主原生项目的十职业beta进度不增加为文档数量或demo数量。
5. 用户体验、听音、手感和原版动态比较继续独立记录。交付体验版后等待用户确认，不自动迁移或恢复主工程。

项目入口已同步：`skills/KNOWLEDGE_POLICY.md`、三个SKILL、`skills/dnf-pvf-knowledge/references/10-pvf-utils-info-runtime.md`。原始知识包保持原字节。
