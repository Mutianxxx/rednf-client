// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · 物品(堆叠物/PO)族 · 族模板还原）
// 类: CNAppendageStackable                   主虚表槽位数: 36  字段数: 10
// 继承: CNAppendageStackable -> CNRDStackable -> IRDItem（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: 物品基类布局 IRDItem（0x485F70 深拷贝: +8 id / +12 类型 / +36 状态 / +40 状态标志）；构造析构链 0x485920 IRDItem析构 / 0x485CC0 核心构造 / 0x485D30 CNRDStackable构造（+148=8/+152=-1/+156=0/+160=0）；激活入口统一 vmt88 → 目标 vt+760 状态槽写入；音效/UI 证据: RECIPE_NOTICE/USE_DEBUFF/MP_RECOVERED
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   00485F70  sub_485F70 IRDItem 记录深拷贝（+8/+12 标量 + 字符串区 + 子容器）（src/game/skill_load_tutorial.cpp:5161）
//   004859F0  sub_4859F0 状态判定：+36 为 0 或（3 且 +40 非 0）（src/game/skill_load_tutorial.cpp:4837）
//   006030D0  CNAppendageStackable__vmt88（168..176 向量逐件 vt+56 + 180/184/188 触发）（src/combat/passive_object.cpp:3030）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNAPPENDAGESTACKABLE
#define ARAD40JP_FIELDS_CNAPPENDAGESTACKABLE

#include <stdint.h>

#pragma pack(push, 1)
struct CNAppendageStackable_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDItem 物品基类布局，见 IRDItem.h）一行带过
    unsigned int     nItemId             ; // +0x0008 (8) x1  va=00485F70 物品 id（0x485F70 IRDItem 记录深拷贝：+8=*(pArg2) 标量首项；全物品族共用基类布局）
    unsigned int     nItemType           ; // +0x000C (12) x1  va=00485F70 物品类型号（0x485F70: +12=*(pArg2+4)；0x4859B0 以 vt+20 判定后比对本槽）
    unsigned char _unused_0x0010      [20]; // +0x0010..0x0023 未观测
    unsigned int     nState              ; // +0x0024 (36) x1  va=004859F0 物品状态字（0x4859F0: ==0 直通 / ==3 时须 +40 字节标志非 0）
    unsigned char    bStateFlag          ; // +0x0028 (40) x1  va=004859F0 物品状态附属标志（0x4859F0 与 +36 状态字成对判定）
    unsigned char _unused_0x0029      [127]; // +0x0029..0x00A7 未观测
    unsigned int     pAppendVec          ; // +0x00A8 (168) x5  va=006030D0 附属对象向量 begin（0x6030D0: +168 起；元素 8 字节，(end-begin)>>3 判空）
    unsigned int     pAppendVecEnd       ; // +0x00AC (172) x3  va=006030D0 附属对象向量 end（0x6030D0: (end-begin)>>3 != 0 才逐件 vt+56 绑定宿主）
    unsigned int     pAppendVecCap       ; // +0x00B0 (176) x1  va=006030D0 附属对象向量 cap（0x50F910 析构 free +168 段）
    unsigned int     nAuraType           ; // +0x00B4 (180) x3  va=006030D0 光环/附属类型字（0x6030D0: !=17 且命中概率时走 sub_602770 新建 0x68 附属对象；构造 0x50F850 置 17）
    float            fProcChance         ; // +0x00B8 (184) x1  va=006030D0 触发概率（0x6030D0: srand(Seed) 后 (rand()%10000) < *(float*)(this+184) 判命中）
    unsigned int     nStatusIdx          ; // +0x00BC (188) x1  va=006030D0 状态槽索引（0x6030D0: ==-1 走新建附属对象；否则宿主 vt+760(180, 100.0f, idx) 状态写入）
};
#pragma pack(pop)

// 统计: 字段行 10 / 语义名 10 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00C0

#endif

