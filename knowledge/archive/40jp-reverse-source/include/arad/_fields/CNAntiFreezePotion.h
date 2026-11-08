// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 物品(堆叠物/PO)族 · 族模板还原）
// 类: CNAntiFreezePotion                     主虚表槽位数: 36  字段数: 6
// 继承: CNAntiFreezePotion -> CNActiveStatusStackable -> CNRDStackable -> IRDItem（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 物品基类布局 IRDItem（0x485F70 深拷贝: +8 id / +12 类型 / +36 状态 / +40 状态标志）；构造析构链 0x485920 IRDItem析构 / 0x485CC0 核心构造 / 0x485D30 CNRDStackable构造（+148=8/+152=-1/+156=0/+160=0）；激活入口统一 vmt88 → 目标 vt+760 状态槽写入；音效/UI 证据: RECIPE_NOTICE/USE_DEBUFF/MP_RECOVERED
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   00485F70  sub_485F70 IRDItem 记录深拷贝（+8/+12 标量 + 字符串区 + 子容器）（src/game/skill_load_tutorial.cpp:5161）
//   004859F0  sub_4859F0 状态判定：+36 为 0 或（3 且 +40 非 0）（src/game/skill_load_tutorial.cpp:4837）
//   00604080  CNAntiFreezePotion__vmt88（+180/+184 解冻判定 + 6029D0 分发）（src/combat/passive_object.cpp:4023）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNANTIFREEZEPOTION
#define ARAD40JP_FIELDS_CNANTIFREEZEPOTION

#include <stdint.h>

#pragma pack(push, 1)
struct CNAntiFreezePotion_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDItem 物品基类布局，见 IRDItem.h）一行带过
    unsigned int     nItemId             ; // +0x0008 (8) x1  va=00485F70 物品 id（0x485F70 IRDItem 记录深拷贝：+8=*(pArg2) 标量首项；全物品族共用基类布局）
    unsigned int     nItemType           ; // +0x000C (12) x1  va=00485F70 物品类型号（0x485F70: +12=*(pArg2+4)；0x4859B0 以 vt+20 判定后比对本槽）
    unsigned char _unused_0x0010      [20]; // +0x0010..0x0023 未观测
    unsigned int     nState              ; // +0x0024 (36) x1  va=004859F0 物品状态字（0x4859F0: ==0 直通 / ==3 时须 +40 字节标志非 0）
    unsigned char    bStateFlag          ; // +0x0028 (40) x1  va=004859F0 物品状态附属标志（0x4859F0 与 +36 状态字成对判定）
    unsigned char _unused_0x0029      [139]; // +0x0029..0x00B3 未观测
    unsigned int     nRadius             ; // +0x00B4 (180) x1  va=00604080 半径/计数（0x604080: *(this+180)==0 走 sub_510230 解冻判定；复用 6029D0 分发管线）
    unsigned char    bSingleTarget       ; // +0x00B8 (184) x2  va=00604080 单目标标志（0x604080: *(uint8_t*)(this+184) 单目标/全队）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00B9

#endif

