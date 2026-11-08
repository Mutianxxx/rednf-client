# 地图、城镇、碰撞和传送门

PC地图基准保存在原PVF及 [区域清单](../imports/gba-workspace/dnf-gba/content/source/region-manifest.json)、[原列表](../imports/gba-workspace/dnf-gba/content/source/lists.json)、[城镇补充](../imports/gba-workspace/dnf-gba/content/source/town-links.json)。原DGN/MAP/TWN/TIL/OBJ字节在 `canonical/pc/pvf/`，可解析的有序字段在 `canonical/pc/entities.jsonl`。清单含23个DGN、691个MAP源定义及关联依赖；GBA实际合成688张源图、运行选择664个房间是另外两个计数。

## 世界关系与房间选择

TWN定义城镇区域及连接，MAP定义场景、NPC、对象、地面、背景原点和可行走约束。必须先还原TWN路由，再还原单场景；把若干背景横向拼接不能代表完整赫顿玛尔。莎兰原位置在西海岸魔法街，GBA早期只额外开放部分区域的配置不能作为完整城镇定义。

DGN定义迷宫、地图规格、变体/任务路线、难度与门对象。`[map specification]` 同一坐标后可有多个MAP候选，需保留每个候选、首领标记与门型。目录中的sample/test/PvP地图不会因位置相邻自动进入正式随机池。角色从真实城镇入口进入选关界面，使用DGN所引IMG/帧，不用文件名猜选关图片。

共同地图模型应保留：源路径/ID，城镇区域/出口，原始迷宫坐标和全部候选，原单位坐标，背景原点，地面/扩展TIL及通过网格，各层ANI/物件及参数，MOB/NPC/门依赖，任务变体与未解事件。摄像机、显示缩放、加载预算归平台层。

## 已查明的图层和地面规则

本地天空城相关资源经源数据和GBA修复验证得到以下规则，作用范围须随资源类型记录：

1. `[distantback]`、`[middleback]` 在主地砖之前。云层不能被合成到柱廊和地砖上方；近景另排。
2. 该地图主舞台逻辑高度480，扩展地砖起点需要加MAP背景原点。常见原点80，对应原尺寸y=560，不能直接从480开始覆盖地面。
3. 扩展地砖列表按主地砖列数逐行换行，不能把多排内容延伸到画布右侧。
4. 此类扩展IMG为224×120、通过网格14×10，对应16×12逻辑单元；主TIL网格14×30对应16×16。TIL类型需各自记录尺寸和步长，不能强套一种网格。
5. 背景重复周期依据IMG逻辑画布宽度，不能用trim后的位图宽度。角色移动依据TIL、虚拟区域与实体障碍，不能用天空图片非透明像素猜地面。

这些是本地样本指定地图的解释，不构成全部类型地图的通用硬编码。原视差、背景动画、机关、可破坏物与剧情场景还需要运行逻辑。

## 传送门

[原门关系](../imports/gba-workspace/dnf-gba/content/source/dungeon-portals.json)保留DGN普通/首领门、四方向及OBJ参数。OBJ的整型/字符串参数对决定状态、层和变体；下方向state0是建筑门框，不可按动画序号当树木删除。普通入口蓝光、首领入口红光取各自原资源。

GBA格兰之森32个原门对象覆盖四套皮肤，动态门去除外围大树并限制为两个OBJ，从而扩大门体；相关 [gba-portals.json](../imports/gba-workspace/dnf-gba/content/gba-portals.json)仅属GBA。未来端口恢复完整门口装饰和原尺寸/层序。原参数与原图片始终保留。

## Android对照与验证边界

Android46个ZON已经精确长度解析，`grid_outer_a`只表存储顺序。FIE169、DS716是资源文件数，不能等同副本数；轴向、格子码、全部房间语义和PC对应尚未完成。见[安卓地图说明](../imports/android/docs/04-quests-maps-admission.md)。后续端口采用PC拓扑，在需要输出安卓旧格式时另建带证据的映射。

迁移验收需遍历每个DGN坐标的所有候选MAP与有效门，检查出口可达、碰撞与画面边界一致、切房目标正确，再执行真实操作。已有GBA [map-portals-report.json](../imports/gba-workspace/dnf-gba/build/map-portals-report.json)包含格兰八副本/天空六副本定向路径；[extended-floor-runtime.json](../imports/gba-workspace/dnf-gba/build/extended-floor-runtime.json)是四个明确注入房间夹具的按键测试，不是自然选关覆盖证明。
