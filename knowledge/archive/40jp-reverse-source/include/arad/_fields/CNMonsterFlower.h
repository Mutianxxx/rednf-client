// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNMonsterFlower    主虚表槽位数: 328   字段数: 45
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNMonsterFlower
//        （基类字段精修见 src/cnrd/*.h；IRDMonster 语义表见 include/arad/_fields/IRDMonster.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定（偏移/类型为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 依据: ①通用偏移表（IRDMonster.h/CNGuardWind.h/CNGolemGold.h）②证据行 va（取自 src 已精修函数头注释）③同族跨类印证 ④src/cnrd/*.h 原始 struct
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNMonsterFlower_Fields {
    // ---- 区块 1：继承段公共字段（通用偏移表；动画对象/帧时刻同步/参数灌入/帧覆盖） ----
    unsigned char _base_0x0000        [73]; // +0x0000..0x0048 继承 KGameMessenger/CNRDObject/IRDCollisionObject/IRDActiveObject 前 0x49 字节（见 src/cnrd/*.h；不重复展开）
    char szNameBuf;                     // +0x0049 (73) x1  基类数字名缓冲 SSO 首字节（0x4DE410 sprintf 名称后写 vt+340() 动作对象 +4）【基类字段】（证据 va=004DE410）
    unsigned char _unused_0x004A      [46]; // +0x004A..0x0077 未观测
    unsigned int pAnimObj;              // +0x0078 (120) x6  基类动画对象指针（0x499020/0x499080 帧时刻同步宿主；全库通用 this+120）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char bSyncSwitch;          // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int nSyncArgA;             // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int nSyncArgB;             // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参）【基类字段】（证据 va=00499020）
    float fSyncValue;                   // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char bParamSlotA;          // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int nParamSlotB;           // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char bParamSlotC;          // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int nParamSlotD;           // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char bFrameOverride;       // +0x0282 (642) x5  基类攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；IRDActiveObject 定案 +642）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int nFrameOverrideTime;    // +0x0284 (644) x4  基类帧时刻覆盖值（与 +0x282 成对；0x4E5C10 第四参）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0288      [20]; // +0x0288..0x029B 未观测
    unsigned int nPickupXCache;         // +0x029C (668) x1  拾取/交互目标坐标缓存（0x4D94A0 由 +8352 拷入，与 +0x2A0 成对）【推断】（证据 va=004D94A0）
    unsigned int nPickupValid;          // +0x02A0 (672) x1  拾取/交互目标有效标志（与 +0x29C 成对置 1）【推断】（证据 va=004D94A0）

    // ---- 区块 4：子类扩展槽区（出生复位批/影身计时/参数面） ----
    unsigned char _unused_0x02A4      [6420]; // +0x02A4..0x1BB7 未观测
    unsigned int nInvisibleStart;       // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻（0x4D5A90 影身计时三连写；clock_now(this+36)）【基类字段】（证据 va=004D5A90）
    unsigned int nInvisibleDur;         // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 按 1000×时长/+6656 折算剩余量）【基类字段】（证据 va=004D5A90）
    unsigned char bInvisibleSwitch;     // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 置位时走折算；0x4D7F30 伪装态切换）【基类字段】（证据 va=004D5A90）

    // ---- 区块 5：主状态/目标/计时门区（大状态/反击态/待机时刻戳） ----
    unsigned char _unused_0x1BC1      [39]; // +0x1BC1..0x1BE7 未观测
    unsigned char bFlower7144;          // +0x1BE8 (7144) x1  单次门字节（0x5CB970 复位族；与莲花 0x5CB690 段 16 同偏移域）（证据 va=005CB970）
    unsigned char _unused_0x1BE9      [3]; // +0x1BE9..0x1BEB 未观测
    unsigned int nBigState;             // +0x1BEC (7148) x1  ★大状态 ID（0x4DB480 反击判定 11/12→切 4；0x4D9000 白名单/0x4D9040 setter）（证据 va=004DB480）

    // ---- 区块 6：内嵌配置块/攻击参数面（0x4A41C0 配置块整体拷贝） ----
    unsigned char _unused_0x1BF0      [368]; // +0x1BF0..0x1D5F 未观测
    unsigned int uCfgWord0;             // +0x1D60 (7520) x1  内嵌配置块首 DWORD / 视野值（0x4A41C0 整体拷贝；0x4DA5F0 索敌门算距离衰减）（证据 va=004A41C0）
    unsigned int uCfgWord1;             // +0x1D64 (7524) x1  内嵌配置块 +4（0x4A41C0 整体拷贝）【推断】（证据 va=004A41C0）
    unsigned char bRetargetGate;        // +0x1D68 (7528) x1  内嵌配置块 +8 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char bCounterHookSw;       // +0x1D69 (7529) x2  反击/架招生效标志（0x4DB480 命中后据此调 vt+1236）【推断】（证据 va=004DB480）
    unsigned char bModeFlag7530;        // +0x1D6A (7530) x1  内嵌配置块 +10 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char bModeFlagA;           // +0x1D6B (7531) x1  内嵌配置块 +11 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char bModeFlagB;           // +0x1D6C (7532) x1  内嵌配置块 +12 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char bModeFlagC;           // +0x1D6D (7533) x1  内嵌配置块 +13 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char bAggroGate7534;       // +0x1D6E (7534) x1  内嵌配置块 +14 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char abAggroAttr4_0;       // +0x1D6F (7535) x1  内嵌配置块 +15 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char abAggroAttr4_1;       // +0x1D70 (7536) x1  内嵌配置块 +16 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char abAggroAttr4_2;       // +0x1D71 (7537) x1  内嵌配置块 +17 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char abAggroAttr4_3;       // +0x1D72 (7538) x1  内嵌配置块 +18 字节（0x4A41C0）（证据 va=004A41C0）
    unsigned char abAggroFlags17_0;     // +0x1D73 (7539) x1  配置块 17 字节循环搬运区起点（0x4A41C0）（证据 va=004A41C0）

    // ---- 区块 7：子类相位/资源对象槽区 ----
    unsigned char _unused_0x1D74      [232]; // +0x1D74..0x1E5B 未观测
    unsigned int nCounterState;         // +0x1E5C (7772) x1  ★反击态（0x4DB480 变量名 nCounterState=*(this+7772)，值 1/2；==3 困难级）（证据 va=004DB480）
    unsigned char _unused_0x1E60      [44]; // +0x1E60..0x1E8B 未观测
    unsigned int pInteractSnap;         // +0x1E8C (7820) x2  文案类别表目录 vector cap / 待释放槽（0x4DE700 29 条 ×16 字节；0x4E3360 释放 +7820）（证据 va=004E3360）

    // ---- 区块 8：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1E90      [528]; // +0x1E90..0x209F 未观测
    unsigned int nRideHostSlot;         // +0x20A0 (8352) x1  骑乘/宿主槽（★全库通用 this+8352；0x4D94A0 拾取快照源，0x4DE700 复位）（证据 va=004D94A0）
    unsigned int uPickupParam;          // +0x20A4 (8356) x2  拾取信息槽 B（0x4D94A0 写 uArg3）（证据 va=004D94A0）
    unsigned int pPickupInfo7;          // +0x20A8 (8360) x6  拾取信息 7 字节对象指针（0x4D94A0 懒创建/释放）（证据 va=004D94A0）
    unsigned int pFrameObject;          // +0x20AC (8364) x1  拾取/坐标缓存槽（0x4E3360 释放；0x4DE700 vt+112(this,+8364,+8368,0)）（证据 va=004E3360）

    // ---- 区块 9：子类 AI 状态区（+8600+；相位/事件/特效槽） ----
    unsigned char _unused_0x20B0      [232]; // +0x20B0..0x2197 未观测
    unsigned char bAI8600;              // +0x2198 (8600) x1  子类 AI 状态字节 1（0x5CB970 清；同族莲花 5CB690 同址 idle 段门）（证据 va=005CB970）
    unsigned char bAI8601;              // +0x2199 (8601) x1  子类 AI 状态字节 2（0x5CB970 清；与 8600 成对）（证据 va=005CB970）
    unsigned char bAI8602;              // +0x219A (8602) x1  子类 AI 状态字节 3（0x5CB970 清；与 8600/8601 成组）（证据 va=005CB970）
    unsigned char _unused_0x219B      [1]; // +0x219B..0x219B 未观测
    unsigned int uAI8604;               // +0x219C (8604) x1  子类 AI 状态槽（0x5CB970 按 dword 即 8604..8607 四字节清零）（证据 va=005CB970）
    unsigned char bAI8608;              // +0x21A0 (8608) x1  攻击/触发一次性门（0x5CB970 清；同族陷阱莲花 5CB690 同址一次门：置 1 后播 TRAP_GRASS_UP）（证据 va=005CB970）
    unsigned char bAI8609;              // +0x21A1 (8609) x1  攻击/触发一次性门伴位（0x5CB970 清；与 8608 成对）（证据 va=005CB970）
};
#pragma pack(pop)

// 统计: 字段行 45 / 已命名 45 / 未命名 0 / 标【推断】4 / 末尾偏移 +0x21A2
