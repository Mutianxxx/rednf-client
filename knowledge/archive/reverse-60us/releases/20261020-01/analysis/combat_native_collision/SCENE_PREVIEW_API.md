# 独立场景预览的只读接口

入口为本目录的 `scene_preview_loader.py`。它读取 `scene-resources.json` 和 `scene-specialized-contract.json`，对将要暴露的 OBJ/ANI 原始导出逐份检查 SHA256，再返回当前 ID 221/224/244 的绑定。它不修改 `combat-preview`、EXE、PVF 或资源，不解码 NPK 图像，不实现 PTL 内部。

`ScenePreviewCatalog.object(id)` 返回 OBJ 来源、精确 RTTI/虚表、basic/etc ANI 原始字段、HP/count/触发参数和初始状态。每份 ANI 的 `frames` 按 `[FRAMEddd]` 分组，`ordered_fields` 保留原始 tag、value、行号及 token；`declared_loop`、`declared_frame_max` 保持 PVF 原值列表。`IMAGE` 等字段可交给已有 ANI/NPK 播放器处理。`raw_export`/`utf8_export` 为绝对导出路径，`pvf_path` 为当前 PVF 内路径。

| ID | 当前 OBJ | 精确控制器 | HP/maxHP 初值 | 计数与触发 |
|---|---|---|---:|---|
| 221 | Barrel.obj | CNMapObject / CCC88C | 1 / 1 | count 初值 0，相等触发 1，上限 1，上限销毁=1，PTL 偏移 (0,0,30) |
| 224 | ActionTree2Lorien.obj | CNActionTree / D4D26C | 1 / 1 | count 初值 0，相等触发 1，上限 2，上限销毁=0，PTL 偏移 (0,0,100) |
| 244 | SmallGrassLorien.obj | CNCutableGrass / CF10F4 | 0 / 0 | contact count 初值 0，阈值 2，pass all，PTL 绝对 Z=32 |

```python
import sys
sys.path.insert(0, r'D:\dnf\60US\analysis\combat_native_collision')
from scene_preview_loader import ScenePreviewCatalog

catalog = ScenePreviewCatalog()
tree_assets = catalog.object(224)
tree_basic = tree_assets['basic_ani']
tree_etc0 = tree_assets['etc_ani'][0]
# tree_etc0['declared_loop'] == [1]
# tree_etc0['frames'][0]['ordered_fields'] 含精确 IMAGE / IMAGE POS / DELAY 等字段。

barrel = catalog.sampler(221, local_authority=True, xyz=(100, 200, 0))
initial = barrel.snapshot()
sample = barrel.sample({
    'kind': 'native_absolute_hp_write',
    'new_absolute_hp': 0,
    'input_provenance': '由外部原生状态事件或明确的人工事件输入提供',
})
# sample['output_events'] 有序输出 HP write、counter、HP reset、PTL、音效和移除请求。
# sample['state']['active'] 仍为 True；移除请求没有假冒为实际移除通知。
removed = barrel.sample({'kind': 'native_self_removed'})

grass = catalog.sampler(244, xyz=(100, 200, 50))
first = grass.sample({'kind': 'native_accepted_contact'})
ended = grass.sample({'kind': 'native_ani_ended'})  # 草不会据此自动移除
second = grass.sample({'kind': 'native_accepted_contact'})
# 草的粒子输出坐标 Z=32，未加上源实体 Z=50。
```

采样事件的语义边界如下：

| 输入 kind | 参数 | 适用对象 | 对应原生消费 |
|---|---|---|---|
| `native_absolute_hp_write` | `new_absolute_hp: int` | 221/224 | state 1 已在 `49D832` 写入绝对 HP，然后 `49D89B -> slot348=5F5B40` |
| `native_hit_visual_gate` | `qualifies: bool` | 221/224 | `5F5FB0` 的攻击方 ATK 视觉 gate；只派发 string[1]/[4]，与数值 HP 分开 |
| `native_accepted_contact` | 无 | 244 | 已经进入草的 `slot260=5F33C0`，子类独立加计数；不从 AABB 推断 |
| `native_bend_direction` | `direction: int` | 244 | 原生 `5F31A0` 的结果作为输入：4/basic，0/etc1，其他/etc2 |
| `native_ani_ended` | 无 | 221/224/244 | 明确观察到当前 ANI `byte+13A==1`；只有 MapObject/ActionTree 的 etc1 标记分支恢复 basic |
| `native_self_removed` | 无 | 221/224/244 | 实际自身移除通知；与此前的 removal request 分开 |

`SceneEventSampler.sample()` 返回 `{input, output_events, state}`，输出列表是本次输入产生的增量。模型不会从时间自动产生事件。`overlap`、`damage`、`elapsed time` 没有入口，未知事件直接抛错；把 accepted contact 传给 221/224，或把 HP 写入传给 244，也会抛错。

`native_absolute_hp_write` 入口已经再次核对，必须传**新的绝对 HP**。`49D7FE` 读取 state 1 payload 的元素 1，`49D832` 原样写入 HP，`49D89B` 随后调用子类 callback。payload 元素 0 的 damage 只作为另一个参数参与显示/回调，不能替代元素 1。该 callback 即使新旧 HP 相同也会执行，因此本模型不额外引入“只有 HP 变化才触发”的条件。

草的两次 contact 是明确进入 `5F33C0` 两次，不等同于两次 AABB 相交、两次挥刀或两次扣血。它先调用通用 `49F310`，随后无论该方法返回值都加自己的计数；当前草 maxHP 默认 0，通用 HP 计算门不会通过，子类计数依然生效。默认 HP/maxHP=0 在 `490758 ->437AD0(this+524)` 及 `437B11/437B13` 已核对。草 tick 的本地碰撞循环也有独立资格逻辑，其最终 `5F36CD` 调用才是本输入的消费边界。

当前树只有 etc0 且 LOOP=1；counter 分支选择它时没有设置 `+93C` 结束恢复标记。不要因 ANI 播到尾就把树切回 basic，也不要在每次事件后主动重置该 ANI。结束恢复 basic 仅属于 `5F5B40` 的 etc1 分支，当前所选树没有 etc1。当前草的 destroy ANI LOOP=0，也不能据此提前删掉草。

模型已恢复的输出包括 `select_ani`（含原生是否 reset）、`native_hp_written`、`counter_increment`、`counter_trigger`、`hp_reset_to_max`、`particle_dispatch`、`sound_request`、`removal_request`、`native_removed`。PTL 输出含 raw path、报告解析后的路径和 XYZ；`internal_simulation_recovered=False` 明确表示不能在预览中补用猜测粒子。last action/通用 destroy particle 的更广链路见 `scene-destruction-contract.json`，本 counter 适配器只给出引用。

执行 `python -X utf8 scene_preview_loader.py` 会把三个对象的完整绑定输出到 stdout。执行 `python -X utf8 scene_state_model.py` 会在本目录重新生成四个示例轨迹；`verify_contract.py` 复验当前 EXE/PVF、原始导出、切片、REA 与关键模型分支。
