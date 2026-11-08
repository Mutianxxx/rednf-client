// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: IRDCollisionObject         主虚表槽位数: 167  字段数: 11
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger
// 族属: 核心对象族
// 依据: ①权威 struct src/cnrd/CNRDObject.h（会话 3 逐行精修 84 槽虚表 + 全字段）与
//        src/cnrd/IRDCollisionObject.h（167 槽命中链主战场）②证据行 va 的 src 函数头注释
// 权威 struct: src/cnrd/IRDCollisionObject.h（虚表 @0x006CC52C 167 槽；+642 碰撞盒快照标志 = 表现壳 this+642/644，hiteff_monster.cpp §1.2 定案）
// 证据函数（src 头注释）: 0x42B1E0 IRDCollisionObject__vmt154 —— 三元组基址（+284，vt+340） /
//   0x433640 IRDCollisionObject__vmt28C —— 空桩（恒 0） /
//   0x626610 IRDCollisionObject__vmt168 —— 敌我关系判定（vmt168 槽覆写，研究已定案）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct IRDCollisionObject_Fields {
    // ---- 区块 1：本段直证点（基类布局见 src/cnrd/CNRDObject.h / IRDCollisionObject.h） ----
    unsigned char _base_0x0000        [120]; // +0x0000..0x0077 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pAnimObj              ; // +0x0078 (120) x6  基类动画对象指针（★全库通用 this+120；src/cnrd/CNRDObject.h +0x078 animObj；0x499020/0x499080 帧时刻同步宿主）（证据: va=00499020）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag             ; // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）（证据: va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA             ; // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参 nArg3）（证据: va=00499020）
    unsigned int     nSyncArgB             ; // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参 nArg4）（证据: va=00499020）
    float            fSyncTime             ; // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）（证据: va=00499080）
    unsigned char    bQuad1                ; // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）（证据: va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2                ; // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）（证据: va=0042A8D0）
    unsigned char    bQuad3                ; // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4                ; // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char    bHitBoxSnap642        ; // +0x0282 (642) x5  碰撞盒快照标志（0x4E5C10 读；src/game/hiteff_monster.cpp §1.2 表现壳盒快照 this+642）（证据: va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     uHitBoxSnap644        ; // +0x0284 (644) x4  碰撞盒快照槽（与 +642 成对；hiteff_monster.cpp §1.2 盒快照槽；IRDCollisionObject.h field_0x284）（证据: va=004E5C10）
};
#pragma pack(pop)

// 统计: 字段行 11 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x0288
