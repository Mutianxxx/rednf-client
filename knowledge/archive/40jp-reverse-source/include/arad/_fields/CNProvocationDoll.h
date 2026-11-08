// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNProvocationDoll  主虚表槽位数: 327   字段数: 36
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> IRDActiveObject×4 -> IRDMonster -> CNProvocationDoll（RTTI bases 直证同段；同族 CNGuardWind/CNGolemGold 同链）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNProvocationDoll_Fields {
    // ---- 区块 1：继承 IRDMonster/IRDActiveObject 基类区（通用偏移表；动画对象/帧时刻同步/参数灌入） ----
    unsigned char _base_0x0000      [73]; // +0x0000..0x0048 继承 IRDMonster/IRDActiveObject 前 0x49 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    char              szDigitalName       ; // +0x0049 (73) x1  基类名字缓冲 SSO 首字节（4DE410 名称模板 sprintf 写此）【基类字段】（证据 va=004DE410）
    unsigned char _unused_0x004A    [46]; // +0x004A..0x0077 未观测
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
    unsigned char _unused_0x0108    [378]; // +0x0108..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0288    [20]; // +0x0288..0x029B 未观测
    unsigned int      nPickupXCache       ; // +0x029C (668) x1  拾取/交互目标坐标缓存（4D94A0：由 +8352 拷入，与 +672 成对）【推断】（证据 va=004D94A0）
    unsigned int      nPickupValid        ; // +0x02A0 (672) x1  拾取/交互目标有效标志（4D94A0 置 1）【推断】（证据 va=004D94A0）

    // ---- 区块 2：子类扩展槽区（出生复位批/影身计时） ----
    unsigned char _unused_0x02A4    [6420]; // +0x02A4..0x1BB7 未观测
    unsigned int      nInvisibleStart     ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻 clock_now(this+36)（4D5A90 影身计时三连）【推断】（证据 va=004D5A90）
    unsigned int      nInvisibleDur       ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（4D5A90 第二参）【推断】（证据 va=004D5A90）
    unsigned char     bInvisibleSwitch    ; // +0x1BC0 (7104) x1  影身开关字节（4D5A90 第三参）【推断】（证据 va=004D5A90）

    // ---- 区块 3：主状态/计时门区（大状态/反击态） ----
    unsigned char _unused_0x1BC1    [43]; // +0x1BC1..0x1BEB 未观测
    unsigned int      nBigState           ; // +0x1BEC (7148) x1  ★大状态 ID（★全库通用 this+7148；4DB480 反击判定 11/12→切 4）（证据 va=004DB480）

    // ---- 区块 4：内嵌配置块/攻击参数面（4A41C0 整体拷贝） ----
    unsigned char _unused_0x1BF0    [368]; // +0x1BF0..0x1D5F 未观测
    unsigned int      nSightRange         ; // +0x1D60 (7520) x1  内嵌配置块首 DWORD / 视野值（4A41C0 整体拷贝；4DA5F0 索敌门算距离衰减）（证据 va=004A41C0）
    unsigned int      uCfgBlock4          ; // +0x1D64 (7524) x1  内嵌配置块 +4（4A41C0 整体拷贝）【推断】（证据 va=004A41C0）
    unsigned char     bCfgBlock8          ; // +0x1D68 (7528) x1  内嵌配置块 +8 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCounterEnable      ; // +0x1D69 (7529) x2  反击/架招生效标志（4DB480 命中后据此调 vt+1236）【推断】（证据 va=004DB480）
    unsigned char     bCfgBlock10         ; // +0x1D6A (7530) x1  内嵌配置块 +10 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock11         ; // +0x1D6B (7531) x1  内嵌配置块 +11 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock12         ; // +0x1D6C (7532) x1  内嵌配置块 +12 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock13         ; // +0x1D6D (7533) x1  内嵌配置块 +13 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock14         ; // +0x1D6E (7534) x1  内嵌配置块 +14 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock15         ; // +0x1D6F (7535) x1  内嵌配置块 +15 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock16         ; // +0x1D70 (7536) x1  内嵌配置块 +16 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock17         ; // +0x1D71 (7537) x1  内嵌配置块 +17 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgBlock18         ; // +0x1D72 (7538) x1  内嵌配置块 +18 字节（4A41C0）（证据 va=004A41C0）
    unsigned char     bCfgTail            ; // +0x1D73 (7539) x1  配置块 17 字节循环搬运区起点（4A41C0）（证据 va=004A41C0）

    // ---- 区块 5：子类相位/资源对象槽区 ----
    unsigned char _unused_0x1D74    [232]; // +0x1D74..0x1E5B 未观测
    unsigned int      nCounterState       ; // +0x1E5C (7772) x1  ★反击态/难度槽（★全库通用 this+7772；4DB480 变量名 nCounterState，值 1/2；==3 困难级）（证据 va=004DB480）

    // ---- 区块 6：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1E60    [576]; // +0x1E60..0x209F 未观测
    unsigned int      nRideHost8352       ; // +0x20A0 (8352) x1  骑乘/宿主槽（★全库通用 this+8352）（证据 va=004D94A0）
    unsigned int      uPick8356           ; // +0x20A4 (8356) x2  拾取信息槽 B（4D94A0 写 uArg3）【推断】（证据 va=004D94A0）
    unsigned int      pPickInfo8360       ; // +0x20A8 (8360) x5  拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）
};
#pragma pack(pop)

// 统计: 字段行 36 / 已命名 36 / 未命名 0 / 标【推断】9 / 末尾偏移 +0x20AC
