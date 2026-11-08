// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNFallingStorage         主虚表槽位数: 177   字段数: 26
// 继承: CNFallingStorage -> CNRDPassiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger（基类段见 src/combat/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 177 个）:
//   +8  0x601FA0 CNFallingStorage__vmt10 落宝箱每帧 tick（按 +243 状态机调 sub_601B00 玩家接近判定 / sub_601C40 着陆）
//   +40 0x601AF0 CNFallingStorage__vmt138 受击槽 thunk（固定以 1 转调 CNRDObject__vmt138）
//   +44 0x601B40 CNFallingStorage__vmt12C 移除槽（自身被移除时清全局跟踪 dword_9B7C88，再转基类）
//       与搬运鸟同组字段：+243 状态机 / +244 事务号（0x601A50 复位）；+112 宿主组件
//       基类段沿用 CNRDPassiveObject/IRDCollisionObject（0x600890 vmt14C / 0x4E1FE0 等）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNFALLINGSTORAGE
#define ARAD40JP_FIELDS_CNFALLINGSTORAGE

#include <stdint.h>

#pragma pack(push, 1)
struct CNFallingStorage_Fields {
    // ---- 区块: 继承基类区（CNRDPassiveObject 通用偏移；动画/时刻同步/参数槽） ----
    unsigned char _base_0x0000[112]; // +0x0000..0x006F 继承段（CNFallingStorage -> CNRDPassiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger）一行带过
    uint32_t         pHostComp           ; // +0x0070 (112) x3  va=00601A70 宿主组件指针（0x601A70: *(this+112)+36 = -(vt+384(0)) 装载高度；0x600890: *(*(this+112)+104) 取宿主激活）
    unsigned char _unused_0074[4]; // +0x0074..0x0077 未观测
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
    uint8_t          bSnapshot700        ; // +0x02BC (700) x2  va=00601A70 ★ 表现/名字块 [20]（0x4E1FE0 由 pArg2[20]；0x601A70 生成时清 0）
    uint8_t          bSnapshot701        ; // +0x02BD (701) x1  va=004E1FE0 ★ 表现/名字块 [21]（0x4E1FE0 由 pArg2[21]）
    unsigned char _unused_02BE[2]; // +0x02BE..0x02BF 未观测
    uint32_t         nSnapshot704        ; // +0x02C0 (704) x1  va=004E1FE0 ★ 表现/名字块 [24]（0x4E1FE0 由 pArg2[24]）
    // ---- 区块: 数据缓冲族（PO 名字缓冲与载荷；0x600890 / 0x5FFF80） ----
    unsigned char _unused_02C4[212]; // +0x02C4..0x0397 未观测
    uint32_t         pNameBuf            ; // +0x0398 (920) x1  va=00600890 ★ PO 名字缓冲（0x600890: 首帧门 +944==0 时以 (this+920 或 *(this+920)) 经 vt+212 播音 —— PO 出生配音只播一次）
    unsigned char _unused_039C[16]; // +0x039C..0x03AB 未观测
    uint32_t         nNameBufCap         ; // +0x03AC (940) x1  va=00600890 ★ 名字缓冲容量（0x600890: <0x10 → 走 SSO 内联分支，即容量判据）
    uint8_t          bNamePlayed         ; // +0x03B0 (944) x2  va=00600890 ★ 名字已播出标志（0x600890: ==0 → vt+212 播放名字后置 1）
    unsigned char _unused_03B1[19]; // +0x03B1..0x03C3 未观测
    uint32_t         nPayloadSize        ; // +0x03C4 (964) x1  va=005FFF80 ★ 载荷缓冲大小字节数（0x5FFF80: = Size）
    uint32_t         pPayloadBuf         ; // +0x03C8 (968) x3  va=005FFF80 ★ 载荷缓冲指针（0x5FFF80: free 旧值 → operator new(Size) → qmemcpy）
    // ---- 区块: 状态机族（落箱激活位；0x601A70 同组） ----
    uint32_t         bFallActive         ; // +0x03CC (972) x1  va=00601A70 ★ 落箱激活位（0x601A70 同组初值写入；配合 +243 状态机与 sub_601B00/sub_601C40）【推断】
};
#pragma pack(pop)

// 统计: 字段行 26 / 语义名 25 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x03D0

#endif
