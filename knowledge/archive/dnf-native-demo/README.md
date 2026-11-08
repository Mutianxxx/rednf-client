# DNF C++ / SDL2 战斗测试版

Windows x64、C++17、SDL2，自定义资源与战斗运行时。当前供测试未转职男鬼剑士和洛兰三房间路线；原版一致性仍在逐项核对。

页面与渲染正在按用户指出的错位修正，当前不能称为视觉验收通过。本轮具体原点、HUD和图层修正及剩余差异见 [渲染记录](docs/RENDERING.md)。

2026-10-17 可玩编译版已放到 [playable/play.cmd](playable/play.cmd)，双击即可启动，无需 Python 或编译器。该目录包含 EXE、SDL2.dll、libunwind.dll、中文说明与 SHA256 清单，与原启动入口共享现有存档。已修复四种武器普攻第二刀漏读 c 图层攻击框的问题。用户已确认字母键失效与输入法有关，本轮暂不处理；游玩前先切换到英文输入法。

从工作区双击 `play-native.cmd`，或在本目录运行：

```powershell
.\play.cmd
.\play.cmd --resolution 1280 720
```

默认需要同级目录 `../DNF1031客户端` 的完整原 PC 客户端。可用 `--client "路径"` 指定其他位置。尚未制作可脱离原客户端的资源子集包。原客户端保持只读。

当前流程：创建/选择角色（20 槽，分两页）→ 赛利亚房间向南出口 → 艾尔文防线向右 → 洛兰入口向右 → 选择进入 → 清完三个房间并走右侧门 → 结算返回。地图来源是 `s0.map → 4.map → b1.map`，属于测试路线。

| 操作 | 按键 |
| --- | --- |
| 移动 / 奔跑 | 方向键 / 连按同一水平方向 |
| 普通攻击 / 跳跃 / 后跳 | X / C / 下+C |
| 技能指令终结 | Z；部分指令使用 X 或 Space |
| 技能快捷键 | A S D F G H Q W E R T Y，Space 后备格挡 |
| 技能配置 / 地图 / 菜单 | K / M / Esc |
| NPC 对话 | 房间内靠近赛利亚按 Enter |
| 调试信息 / 恢复 / 重载当前场景 / 换武器 | F3 / F5 / F6 / F7 |
| 保存反馈包 / 截图 | F8 / F12 |

连突刺需先跑攻；银光落刃、空中连斩需在空中；三段斩、月光斩和空中连斩需续段输入；格挡需保持按键。K 面板可循环调整测试技能等级、交换相邻快捷键、调整四种武器精通。Space 是后备格挡输入；换绑定后使用面板显示的技能键也可格挡。

Esc 菜单支持分辨率、无边框全屏、垂直同步和返回选角。窗口也可拖动调整大小。渲染没有固定 FPS 上限；默认垂直同步，模拟独立使用 60 Hz 时钟。测试 HP/MP 与免冷却默认关闭，开启后不能把结果作为普通战斗验收。

存档在 `saves/characters.json`，保存名称、武器、技能等级、被动等级和技能键顺序，保留 20 槽旧档与未知字段；有效旧档备份到 `characters.bak.json`。正常关闭窗口和返回选角都会保存。F8 反馈包和每次运行报告位于 `reports/runs/<运行 ID>/`，包含截图、输入、事件和状态。

构建和验证：

```powershell
.\build.cmd --test
# 以下命令使用本机已有 Python；构建依赖已保存在 third_party
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools/run_demo.py --audit
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools/verify_flow.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools/run_demo.py --flow-smoke 300
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools/run_demo.py --flow-smoke 30 --flow-scene-seconds 5
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools/run_demo.py --smoke 104
```

普通流程脚本通过 Windows 窗口按键/鼠标消息进入 SDL，使用独立存档并只读观察运行状态。它和直接换场、恢复 HP/MP 的 smoke 各有用途；详细结果见 [实施记录](docs/IMPLEMENTATION.md)、[技能证据矩阵](docs/CONTROLLERS.md) 与 [最新交接](CURRENT_TASK.md)。

`tools/verify_flow.py --physical-keys` 可另行使用 SendInput 键盘输入，只在确认游戏窗口取得前台焦点后发送，并仅为游戏线程选择英文键盘布局。此次 Windows 拒绝焦点请求，物理输入验证未完成；窗口消息流程已通过。需要重新发布已构建产物时运行 `tools/package_playable.py`，游戏运行时脚本拒绝覆盖。

伤害目前采用公开标注的 demo 训练武器参数，技能 MP 仍为基础消耗，装备、防御、暴击、元素与异常流水线仍不完整。轻甲精通已读取原数据，但当前只装备外观层，没有实际轻甲属性贡献。四转职、觉醒、TP、完整洛兰迷宫、任务、商店和掉落不属于已完成内容。UI、控制器时序、深度关系和音频事件仍有差异，不能将此版视为原 PC 完整复刻。

用户显示偏好（2026-10-17）：自动场景/压力/技能测试需前台可见。tools/run_demo.py 对 --smoke/--flow-smoke 会恢复窗口、请求前台，并在测试期间置顶显示；进程关闭后窗口销毁。Windows 若拒绝焦点切换，仍保证测试窗口在上方可见。普通交互不强制置顶。
