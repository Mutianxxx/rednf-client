# skill-bindings：1031 exe 技能绑定表

从 1031 `DNF.exe`（磁盘明文段，未脱壳）提取「skill_id → state → 身体动画链」，
再与 PVF 的 CHR `etc_motion` 表、`skill/*.lst`、`sqr/common.nut` 效果层结合，
生成 `include/dnf/skill_exe_bindings.hpp` 供技能预览器查表。

生成物是**数据**，渲染与查表消费方在 `src/tools/skill_preview_mapping.cpp`：
`resolve()` 里按 CHR stem + skill_id 查表，命中则整体替换名字推断链。

## 目录

| 路径 | 内容 |
| --- | --- |
| `bindings/<class>-skill-binding.json` | 每职业的 skill_id → states → entry_motions / effect_anis |
| `evidence/all-class-skill-state-pairs.json` | 已通过资格代码对齐验证的 (skill, state) 对，生成器的白名单 |
| `evidence/state-handler-events.json` | 每个 state handler 的 vtable 调用事件原始扫描结果 |
| `evidence/judgment-events.json` | 每个技能 setState handler 的 **ATK 选择器 `0x70213F` 调用**（state → 攻击序号 + 调用点地址），exe→PVF 判定派发链 |
| `evidence/skill-commands.json` | 每个 `.skl` 的 **`[command]` 操作指令**（按键序列 token + 中文说明），PVF 源数据 |
| `evidence/skill-names.json` | PVF 技能名（韩文按 CP949 误读，已还原 GBK） |
| `evidence/all-class-report.json` | 各职业控制区、setState 表基址、命中统计 |
| `src/extract_all_classes.py` | 主提取脚本：扫描 handler、region 配对、offset 投票、两级归属评分 |
| `src/extract_judgment.py` | 把 `state-handler-events.json` 的 ATK 选择器调用按 `(handler, state)` 双键精确关联到技能（剑士族），产出 `judgment-events.json` |
| `src/extract_commands.py` | 从 1031 `Script.pvf` 抽取全部 `.skl` 的 `[command]` / `[command key explain]`，产出 `skill-commands.json`（781 项） |
| `src/gen_exe_bindings_header.py` | 生成 C++ 头文件 |
| `src/analyze_handlers.py`、`src/build_binding_final.py` | 剑士单职业的逐 handler 分析与早期绑定构建 |
| `src/pvf_*.mjs`、`src/extract_obj.mjs`、`src/hook*.mjs` | PVF 子集抽取（`.lst` 需 `convertNameList`） |
| `REPORT.md` | 机制说明、证据链、已知边界 |

## 重新生成头文件

```bash
python -X utf8 -B tools/skill-bindings/src/gen_exe_bindings_header.py
```

脚本按自身路径解析输入输出，可在任意工作目录运行；输出 8 职业 299 技能。
产物只收「资格代码对齐验证 / 动作名与 .skl 完整 stem 吻合 / 本职业独占 state」三类 state，
每条记录在 `evidence` 里写明 `basis`（`eligibility pair` / `motion name` / `sole state owner`）。
被多个技能共享的 state（13/19/69/71..78/75）若名字也不吻合则不入表，运行时会打印丢弃条数
（当前 185 条）。这三个条件都能单独成立：独占 state 意味着资格代码已把它唯一绑定到该技能。

## 重新提取需要的东西

- `DNF1031客户端/DNF.exe`（41,978,368 B，2021-09-21，PE32）—— 只读，不会改动
- 1031 PVF（`content-profile.json` 指向的原始客户端）
- Python 3 + capstone 5.0.7（`gba-research/third_party/research-python`）
- Node 22（`--experimental-strip-types --experimental-transform-types` + `src/hook-register.mjs` + `src/bun-shim.mjs`）

## 已知边界（不要当成已完成）

- 盗贼区（控制区 D，`0xC90480`）动作索引映射未闭合，`thief-skill-binding.json` 不参与生成。
- creatormage 没有原生 setState 控制器，无绑定。
- ATK 判定 thunk `0x70213F` 落在 VM 区未恢复；**已提取**其对每个 state 的调用与攻击序号
  （`judgment-events.json`），但立即数 → `.atk` 文件名的翻译仍未恢复，判定框几何仍沿用 ANI/PVF。
- 非剑士系 `common.nut` 无 `sq_LoadSkillEffect_*` 函数，效果链只对剑士系成立。

细节与逐条证据见 `REPORT.md`、`scope.md`。
