# 当前任务：1031 exe 绑定表接入（2026-11-04）

节点：`skill-previewer-exe-bindings-20261104`。1031 DNF.exe 的技能 setState 表
（磁盘明文）已逆向完成并泛化到全职业：剑士系(剑士/鬼剑士)、格斗家系、神枪手系、
魔法师、圣职者共 8 职业 298 技能的 skill_id→state→身体动画链（vtable+0x49C 立即数）
与效果链（sqr/common.nut）已固化到生成头文件
`include/dnf/skill_exe_bindings.hpp`（生成脚本与绑定数据已随主线归档在
`tools/skill-bindings/`，重新生成：
`python -X utf8 -B tools/skill-bindings/src/gen_exe_bindings_header.py`）。

`skill_preview_mapping.cpp` resolve() 中以 CHR stem+skill_id 查表，命中则整体
替换名字推断链（confidence=Manual，evidence 带 state/handler 地址），效果链并入。
测试 37/37 绿（新增 3 条：绑定≥20 且 0 坏、鬼斩链 hardattack 领头、崩山击
ready→smash 两段）。构建 `cache/refactor-build` 通过。

来源与证据：`tools/skill-bindings/`（REPORT.md、bindings/*.json、evidence/*）。已知边界：
盗贼区(D)动作表映射未闭合未产出；ATK 判定 thunk
仍在 VM 区（攻击框沿用既有来源）；魔法/圣职等效果层 common.nut 无函数（沿用
目录前缀匹配）；ATK 立即数→.atk 翻译未解决。

# 当前任务：40JP 技能演示 Demo（仅渲染与判定）

节点：`skill-previewer-40jp-20261103`。目标：`dnf_skill_previewer` 完全按 40JP 指导内容
演示技能——人物、粒子、特效、技能图标、动作、判定，不含等级/MP/CD/学习账本/状态机门禁，
不限帧率。先做鬼剑士（job 0）与神枪手（job 2）。

## 节点：技能演示链播放与数据源定稿（2026-11-03 22:55）

**问题定案（为什么部分技能效果不对）**：
1. 任何版本的 PVF 都不绑定技能动作（1031 与 60US 的 .skl 全字段核对均无 .ani/.atk 引用）；
   绑定是 exe 内的动画池索引。1031 DNF.exe 加壳提不出；60US DFO_fixed_v3.exe 未加壳，
   reverse-60us 已固化 18 条绑定（cast-contracts.json），但 index→ANI 未闭环。
2. 40JP(2006) 与 1031(2026) 资源名重合率 1/107、2/161 —— 补 40JP 系 PVF 无助益。
3. 已落地改进：阶段词+变体前缀匹配（救回 25 条 D 级）、60US CHR 权威动作池
   （97/97 重合，`skill_preview_motion_pool.hpp`）驱动链顺序、多段链连续播放
   （26+26 条技能挂链）、UI 横幅显示链证据。分级 A54/B248/C88/D1344。
4. 测试 34/34 绿；verify_architecture 通过（139 单元）。既有 core 组失败与本节点无关。

**下一步最优路径**：继续逆向 D:/dnf/60US/DFO/DFO_fixed_v3.exe 扩展绑定表（见 SPEC 6.2）。

## 节点：1031 脱壳可行性评估 + 动作池改用同源数据（2026-11-03 23:20）

**用户问题**：给 1031 `DNF.exe` 脱壳成功率？如果成功是否解决所有问题？

**结论**：静态解包中偏高（约 60–70%）；完整脱壳到可独立运行/可调试 <20%；
靠脱壳拿技能绑定「低且非必需」。**「脱壳能解决所有问题」不成立。**

**实测证据**（`D:/dnf-rebuild/DNF1031客户端/`）：
- `DNF.exe` 41,978,368 B / 2021-09-21 / PE32 / 11 节；7 节同名 `nsn` 且全 RWX；
  熵 7.9/7.6 两节 + 熵 2.354 一节（解压预留）；EP RVA `0x00FE06BA` 是标准 CRT
  大小写转换代码而非壳 stub；导入表完整保留 30 个 DLL；2 个 TLS callback；
  **57,896 条明文 ASCII 字符串**（RTTI、`DNFLex::yylex`、OpenSSL 参数）
  → 部分加密 + 反调试，**不是全盘虚拟化**。
- 保护组件：`TenSLX.dll`（`.tvm0` = Themida VM）、`TerSafe.dll`（`.txt$0~3` 拆分混淆）、
  `start/TenProtect` 驱动级、`TenSLX.dat`/`Tenparty.dat`。
- 明文字符串里 `.ani` 0、`skill/` 0、`.skl/.chr/.lst/.atk/.als` 0、
  动画名 0、技能 RTTI 类名 0 → **绑定是 exe 里的数字立即数，脱壳也不会浮现明文动画名**。
- **PVF 自己就有权威花名册**：1031 `character/<job>/<job>.chr` 的
  `[attack motion]+[ghost motion]+[etc motion]` = 剑士 127 / 枪手 107 条有序 ANI，
  `[etc attack info]` = 87 / 26 个 `.atk`，还有 `animation/*.ani.als` 特效子链、
  `skill/*.lst` 技能 ID→路径表。缺的只是 skill_id→花名册下标这一张表。
- 60US `cast-contracts.json` 的 `animation_index` 实测只有 **0/1/3**，是变体号，
  不是动画池下标 —— 已更正 SPEC 6.1 旧措辞。
- `mutian.exe` 是 UPX 壳的登录/界面工具（gdiplus/COMCTL32/OLEACC），不是未保护主程序。

**落地改动（只报事实）**：
- `include/dnf/skill_preview_motion_pool.hpp` 改用 **1031 自身 CHR** 池（127/107，
  同源同版本），其余职业保留 60US 兜底。**实测当前无行为变化**：分级
  A54/B248/C88/D1344 与全部 26+26 条链的逐步顺序逐条一致 —— 池只用于链排序，
  现有链用到的 stem 在两版池里相对位置相同。属数据源正确性修复，为将来接
  skill_id→池下标绑定做准备。
- 编译通过、`dnf_skill_preview_tests` 34/34 绿、审计刷新、`verify_architecture` 通过。
- `docs/SKILL-DEMO-40JP-SPEC.md` 6.1/6.2 更正 + 新增 **6.3 脱壳可行性评估**；
  验收文档增补数据源说明。

**最值得补的材料（价值降序）**：
1. 1031 的**未加壳 `DNF.exe` / 内存 dump / PDB 符号** —— 能直接定位技能索引表函数；
2. 允许**运行 1031 客户端做运行时观测**（hook 动画加载 / dump 解密段）；
3. 继续逆 60US `DFO_fixed_v3.exe` 把 18 条绑定扩到全量；
4. 40JP/45JP PVF —— 无用（重合率 1/107、2/161 已证）。

