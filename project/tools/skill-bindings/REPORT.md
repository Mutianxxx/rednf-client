# DNF 1031 skill_id → 动画绑定提取（结案报告）

日期：2026-11-04（会话延续 2026-11-03 晚间）
结论：**绑定表已提取** → `swordman-skill-binding.json`（176 技能；56 个含 exe state 证据、58 个含动画、24 个含效果层）。

## 成果

### 机制还原（磁盘 exe 静态分析，全部锚点验证）

| 组件 | 地址/槽位 | 语义 |
|---|---|---|
| setState 分发表 | `0xCE1998[state-3]` → handler | 磁盘明文，覆盖 state 3..79；29→0xCD9FE7、35→0xCD476E 与既有合同吻合 |
| 角色类 vtable | `0x1706a24` | 剑士 |
| 选 etc-motion | vtable `+0x49C`（→0x84CE20，角色+0x2C64 数组）；`+0x498` = 索引+0x5B | **身体动画选择**（动画索引立即数在此） |
| 按 skill_id 取技能对象 | `+0x804`（→0x84B100，角色+0x4414+growtype*0x3FC+id*4）、`+0x7D0`、`+0xA14` | 参数即 skill_id |
| 技能效果查找/附加 | `0x690420(skillId, index)` / `0x690210`，映射表 角色+0x5E38[skillId] | 效果层由 sqr/common.nut 预注册 |
| ATK 选择器 | `call 0x70213F(imm)` | 受 Themida VM 保护，立即数→.atk 的翻译未恢复（与既有合同一致） |
| 状态排队 | 资格 `+0x864(skill,1,1,1)` 成功后 `+0x30C(state,…)` | skill→state 的运行时来源 |

### 实测四技能验证（用户在图内依次施放）

| 技能 | skill_id | state | 身体动画（CHR etc_motion） | 效果层（PVF common.nut） |
|---|---|---|---|---|
| 鬼斩 | 5 (HardAttack.skl) | 20（排队证据 0xCC2D5E） | motion 1 `HardAttack.ani`；蓄力变体 17 `HardAttackChargeAfter.ani` | `Effect/Animation/HardAttack1/2.ani` |
| 崩山击 | 65 (HopSmash.skl) | 36（handler 0xCD4E97） | motion 26→27 `HopSmashReady.ani`→`HopSmash.ani` | `HopSmash/Sword.ani`、`HopSmash/Smash.ani` |
| 裂波斩 | 58 (VaneSlash.skl) | 32（handler 0xCD413D） | motion 14 `VaneSlashTry.ani`（+15 `VaneSlash.ani`） | `VaneSlash/Upper/Dust/Smash.ani` |
| 刀魂之卡赞 | 25 (Khazan.skl) | buff：通用施放态 | 召唤物 `passiveobject/.../khazan.obj` etc_motion 6 个（Appear/Stay/Disappear） | 施放瞬间懒加载（runtime dt=67.312s 观测） |

### 与 PVF 的关系修正

- PVF **含有** CHR etc_motion 表（索引→.ani）、skilllist（id→.skl）、效果层（sqr/common.nut）、被动对象动画（.obj）。
- PVF **不含**：state 编号（剑士 .skl 无 executable_states）与 state→motion 索引——即 exe 内立即数。本次已从磁盘 exe 提取。
- 名称转码坑：n_string 韩文区实际是 GBK 中文被按 CP949 误读，`encode('cp949').decode('gbk')` 还原（如 HardAttack.skl = 鬼斩）。

## 关键文件

- `swordman-skill-binding.json` — 最终交付（含 _meta 机制说明、证据分级、已知边界）
- `state-handler-events.json` — 77 个 state handler 的 vtcall/direct-call 事件流（capstone 5.0.7，来源 gba-research/third_party）
- `state-handler-scan.json`、`skill-state-pairs.json`、`skill-names.json` — 中间产物
- `pvf-out/` — PVF 子集提取（2048 文件：skill/*.lst、skill/<class>/*.skl、character/*.chr、sqr/**、khazan.obj）
- `src/` — 全部工具脚本（pvf_subset_extract.mjs 及 node 兼容 shim、analyze_handlers.py、scan_skill_state.py、build_binding_final.py 等）
- `client-scene-restore/` — 从客户端移出的自注入 DLL 与 dump 数据存档
- 运行时数据：`客户端/trace-ui-lab-1031/20261103T164022-37108/resources*.jsonl`（解析事件流，卡赞懒加载观测）；`skill-bind-dump/ck3-exe-image.bin`（施放后 63MB 运行时映像，已移入 client-scene-restore）

## 已知边界

1. ATK 选择器立即数→.atk 路径翻译在 VM 区内，未恢复（沿用既有合同结论）。
2. proc 分发表 CCA368 磁盘与运行时 dump 均为字节编码，未完全解码；phase motion 部分以 CHR 名字表推断（已在 JSON 中分级标注）。
3. 基础移动 state（3..18 默认 handler 0xCD8CA8）不含 skill id；buff 技能走通用施放态。
4. 仅完成剑士；其他职业的 setState 表地址不同，方法可直接复用（vtable+0x49C 模式跨类一致）。

## 现场恢复

- plugins/ 移出 `zz_skill_binding_dump.dll`、`zz_skill_binding_probe2.dll`（→ client-scene-restore/plugins/）
- 客户端根目录 skill-bind-dump/、skill-bind-dump2/ 整体移出；probe2 worker 经 stop2.txt 停止后文件解锁
- 游戏进程 37108 未受影响，仍在运行；其内存中残留的 probe2 实例已停止写入

---

## 扩展（2026-11-04 续）：全职业泛化提取 + 预览器接入

### 全职业 setState 表定位

- 跳转表识别：各职业 setState 调度为 `jmp [idx*4 + base]`（FF 24 SIB disp32），扫全部代码指针 run（≥40 连续）得 42 个候选，其中 6 个 run 的 handler 含 vtable+0x49C 动画选择模式。
- 6 区归属（对齐证据 = state handler 动作名与 lst 技能名互证）：
  - A 0xBF2FF0 → fighter + atfighter（格斗家男女）
  - B 0xC2F180 → gunner + atgunner
  - C 0xC2F... → mage
  - D 0xC90480 → 未定（thief 证据最强：ChainSaw 等 13 个技能名在盗贼 CHR 中存在，但动作索引表映射未闭合，暂不产出）
  - E 0xCA5004 → priest
  - F 0xCE18A8 → swordman + demonicswordman（F 区内子表 0xCE1998 即原合同 setState 表，off=3 得 31 票复核）
- 创造者（creatormage）无原生控制器（鼠标施法特殊职业）；atmage 部分复用 mage 区。
- 全职业 skill→state 配对：资格代码 `+0x864(skill,1,1,1) → +0x30C(state)` 全区扫描，363 对；handler 内 skill 槽引用（+0x7D0/+0x804/+0xA14）补充反向证据。

### 产物

- `bindings/<class>-skill-binding.json` ×10（8 职业有 exe 对齐证据；thief/atmage 仅名字推断并已标注）
- `include/dnf/skill_exe_bindings.hpp`（生成，8 职业 299 技能，收录"资格对 / 名对齐 / 独占 state"
  三类 state，每条带 `basis` 标注）
- `src/extract_all_classes.py`、`src/gen_exe_bindings_header.py` 可重跑（换 PVF/exe 后全量再生）

### 预览器接入（dnf-c++-project/project）

- `skill_preview_mapping.cpp` resolve()：CHR stem + skill_id 查 `exe_bindings::find`，命中则以 exe 链整体替换名字推断链（confidence=Manual、evidence=state/handler 地址），效果链并入。
- 已知边界：ATK 判定仍不受影响（VM 保护）；盗贼绑定缺失；magic 类效果层在 common.nut 中无函数（仅剑士系有 sq_LoadSkillEffect_*）。
