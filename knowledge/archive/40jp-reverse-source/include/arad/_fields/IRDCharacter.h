// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: IRDCharacter       主虚表槽位数: 333   字段数: 23
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> IRDActiveObject×3 -> IRDCharacter（本表）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct IRDCharacter_Fields {
    // ---- 区块 1：继承 IRDActiveObject 基类区（动画对象/参数灌入/能力槽前置） ----
    unsigned char _base_0x0000      [120]; // +0x0000..0x0077 继承 IRDActiveObject 前 0x78 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x007C    [108]; // +0x007C..0x00E7 未观测
    unsigned char     bSyncSwitch         ; // +0x00E8 (232) x2  基类时刻同步开关位（499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9    [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncValue          ; // +0x00F4 (244) x4  基类浮点时刻槽（499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bParamSlotA         ; // +0x00F8 (248) x1  基类四元组字节槽 1（42A8D0 CNRDObject__vmt11C 批量写 +248..+260）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9    [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nParamSlotB         ; // +0x00FC (252) x1  基类四元组 dword 槽 2（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char     bParamSlotC         ; // +0x0100 (256) x1  基类四元组字节槽 3（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101    [3]; // +0x0101..0x0103 未观测
    unsigned int      nParamSlotD         ; // +0x0104 (260) x1  基类四元组 dword 槽 4（42A8D0）【基类字段】（证据 va=0042A8D0）

    // ---- 区块 2：能力槽与受击表现区（4AF8E0 能力槽 4 件） ----
    unsigned char _unused_0x0108    [248]; // +0x0108..0x01FF 未观测
    unsigned int      nAbilityId          ; // +0x0200 (512) x2  ★能力槽 id（4AF8E0 惰性初始化：==4 时用 vt+1176/vt+1180 重取两值）【基类字段】（证据 va=004AF8E0）
    unsigned char     bAbilityFlag        ; // +0x0204 (516) x1  ★能力槽标志字节（4AF8E0 由 vt+1180() 写入）【基类字段】（证据 va=004AF8E0）
    unsigned char _unused_0x0205    [3]; // +0x0205..0x0207 未观测
    unsigned int      nAbilityDur         ; // +0x0208 (520) x5  ★能力槽时长/基础值（4AF8E0：==-1 用 vt+1184；>0 按 (2.0−属性块+1292)×它修正）【基类字段】（证据 va=004AF8E0）
    unsigned int      fAbilityScale       ; // +0x020C (524) x2  ★能力槽浮点缩放（4AF8E0：==-4.0f 用 vt+1188 取初值）【基类字段】（证据 va=004AF8E0）
    unsigned char _unused_0x0210    [114]; // +0x0210..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）

    // ---- 区块 3：影身计时（4D5A90） ----
    unsigned char _unused_0x0288    [6448]; // +0x0288..0x1BB7 未观测
    unsigned int      nInvisibleStart     ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻 clock_now(this+36)（4D5A90 影身计时三连）【推断】（证据 va=004D5A90）
    unsigned int      nInvisibleDur       ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（4D5A90 第二参）【推断】（证据 va=004D5A90）
    unsigned char     bInvisibleSwitch    ; // +0x1BC0 (7104) x1  影身开关字节（4D5A90 第三参）【推断】（证据 va=004D5A90）

    // ---- 区块 4：大状态/映射表区（+7148 大状态 / +7416 键值表） ----
    unsigned char _unused_0x1BC1    [43]; // +0x1BC1..0x1BEB 未观测
    unsigned int      nBigState           ; // +0x1BEC (7148) x2  ★大状态 ID（★全库通用 this+7148；5796C0 默认虚槽桩写 *(u32*)(this+7148)=*(pArg2+4)）（证据 va=005796C0）
    unsigned int      uChar7152           ; // +0x1BF0 (7152) x1  状态扩展字（5796C0：*(u32*)(this+7152)=*(pArg2+4)）【推断】（证据 va=005796C0）
    unsigned char     bChar7156           ; // +0x1BF4 (7156) x1  状态扩展字节（5796C0：*(u8*)(this+7156)=*(pArg2+8)）【推断】（证据 va=005796C0）
    unsigned char _unused_0x1BF5    [259]; // +0x1BF5..0x1CF7 未观测
    unsigned int      map7416             ; // +0x1CF8 (7416) x1  键值表（4B4EE0：键到值 map 插入/删除，this+7416 处 map）（证据 va=004B4EE0）
    unsigned int      map7416End          ; // +0x1CFC (7420) x1  键值表尾（4B4EE0：nArg3 != *(this+7420) 判定）【推断】（证据 va=004B4EE0）
};
#pragma pack(pop)

// 统计: 字段行 23 / 已命名 23 / 未命名 0 / 标【推断】6 / 末尾偏移 +0x1D00
