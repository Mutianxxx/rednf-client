// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNStorageSub             主虚表槽位数: 177   字段数: 21
// 继承: CNStorageSub -> CNRDPassiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger（基类段见 src/combat/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 177 个）:
//   +12 0x601DA0 CNStorageSub__vmtC 状态选动画（按 +245 状态 0..3 从 +139 记录的 152 字节步长四件动画组选件，经 vt+344 绑定）
//   +16 0x600880 CNRDPassiveObject__vmt10 thunk → sub_6004B0（PO 数量自适应透明度 tick）
//       载荷缓冲 0x5FFF80（+964 大小 / +968 指针；free + new + qmemcpy）
//       基类段沿用 CNRDPassiveObject/IRDCollisionObject（0x499020/0x42A8D0/0x4E5C10 等）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSTORAGESUB
#define ARAD40JP_FIELDS_CNSTORAGESUB

#include <stdint.h>

#pragma pack(push, 1)
struct CNStorageSub_Fields {
    // ---- 区块: 继承基类区（CNRDPassiveObject 通用偏移；动画/时刻同步/参数槽） ----
    unsigned char _base_0x0000[120]; // +0x0000..0x0077 继承段（CNStorageSub -> CNRDPassiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger）一行带过
    uint32_t         pAnimObj            ; // +0x0078 (120) x6  va=00499020 动画对象指针（全库通用：动画对象 = this+120；0x499020 时刻同步宿主）
    unsigned char _unused_007C[108]; // +0x007C..0x00E7 未观测
    uint8_t          bAnimSync232        ; // +0x00E8 (232) x2  va=00499020 动画时刻同步开关（0x499020 关→开时同步帧时刻）
    unsigned char _unused_00E9[3]; // +0x00E9..0x00EB 未观测
    uint32_t         uAnimSync236        ; // +0x00EC (236) x1  va=00499020 动画同步参数 A（0x499020 写 nArg3）
    uint32_t         uAnimSync240        ; // +0x00F0 (240) x1  va=00499020 动画同步参数 B（0x499020 写 nArg4）
    float            fAnimSync244        ; // +0x00F4 (244) x4  va=00499080 动画同步浮点参数（0x499080 浮点版：非 0→0 时推帧）
    uint8_t          bParam248           ; // +0x00F8 (248) x1  va=0042A8D0 参数灌入槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）
    unsigned char _unused_00F9[3]; // +0x00F9..0x00FB 未观测
    uint32_t         uParam252           ; // +0x00FC (252) x1  va=0042A8D0 参数灌入槽 2（0x42A8D0）
    uint8_t          bParam256           ; // +0x0100 (256) x1  va=0042A8D0 参数灌入槽 3（0x42A8D0）
    unsigned char _unused_0101[3]; // +0x0101..0x0103 未观测
    uint32_t         uParam260           ; // +0x0104 (260) x1  va=0042A8D0 参数灌入槽 4（0x42A8D0）
    unsigned char _unused_0108[378]; // +0x0108..0x0281 未观测
    uint8_t          bFrameOv642         ; // +0x0282 (642) x5  va=004E5C10 帧时刻覆盖开关（0x4E5C10：非 0 时用 +644 直写帧时刻）
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    uint32_t         uFrameOv644         ; // +0x0284 (644) x4  va=004E5C10 帧时刻覆盖值（0x4E5C10 nArg3）
    // ---- 区块: 数据缓冲族（表现/名字块 28 字节直拷；0x4E1FE0） ----
    unsigned char _unused_0288[32]; // +0x0288..0x02A7 未观测
    uint32_t         nSnapshot680        ; // +0x02A8 (680) x1  va=004E1FE0 ★ 表现/名字块 [0]（0x4E1FE0 由 pArg2[0] 直拷，28 字节 7 字段块首）
    uint32_t         nSnapshot684        ; // +0x02AC (684) x1  va=004E1FE0 ★ 表现/名字块 [1]（0x4E1FE0 由 pArg2[1]）
    uint32_t         nSnapshot688        ; // +0x02B0 (688) x1  va=004E1FE0 ★ 表现/名字块 [2]（0x4E1FE0 由 pArg2[2]）
    uint32_t         nSnapshot692        ; // +0x02B4 (692) x1  va=004E1FE0 ★ 表现/名字块 [3]（0x4E1FE0 由 pArg2[3]）
    uint32_t         nSnapshot696        ; // +0x02B8 (696) x1  va=004E1FE0 ★ 表现/名字块 [4]（0x4E1FE0 由 pArg2[4]）
    uint8_t          bSnapshot700        ; // +0x02BC (700) x1  va=004E1FE0 ★ 表现/名字块 [20]（0x4E1FE0 由 pArg2[20]；0x601A70 生成时清 0）
    uint8_t          bSnapshot701        ; // +0x02BD (701) x1  va=004E1FE0 ★ 表现/名字块 [21]（0x4E1FE0 由 pArg2[21]）
    unsigned char _unused_02BE[2]; // +0x02BE..0x02BF 未观测
    uint32_t         nSnapshot704        ; // +0x02C0 (704) x1  va=004E1FE0 ★ 表现/名字块 [24]（0x4E1FE0 由 pArg2[24]）
    // ---- 区块: 数据缓冲族（载荷缓冲；0x5FFF80） ----
    unsigned char _unused_02C4[256]; // +0x02C4..0x03C3 未观测
    uint32_t         nPayloadSize        ; // +0x03C4 (964) x1  va=005FFF80 ★ 载荷缓冲大小字节数（0x5FFF80: = Size）
    uint32_t         pPayloadBuf         ; // +0x03C8 (968) x3  va=005FFF80 ★ 载荷缓冲指针（0x5FFF80: free 旧值 → operator new(Size) → qmemcpy）
};
#pragma pack(pop)

// 统计: 字段行 21 / 语义名 21 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x03CC

#endif
