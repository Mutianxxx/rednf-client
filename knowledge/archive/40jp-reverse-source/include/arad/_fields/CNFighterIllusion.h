// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNFighterIllusion   主虚表槽位数: 327
// 继承: CNFighterIllusion -> IRDMonster -> IRDActiveObject -> IRDCollisionObject -> CNRDObject
//        -> KGameMessenger -> KMessenger（基类段见 src/cnrd/*.h）
// 本类覆写 8 个槽（+0/+332/+472/+512/+768/+1164/+1192/+1208）；基类 IRDMonster 的 89 个字段全部可见。
// 语义: 剑魂/格斗家幻影（KENSIN 系）—— 出场演出 0x590970 / 消散 0x590C40 / 受击 0x590AD0。
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 f_XXXX 占位）
// 证据主源（本类 327 槽函数）:
//   +1192 0x5908C0 子类 AI 状态复位（src/game/creature/goblin_fox.cpp:35）
//   +332  0x590970 出场技能演出 KENSIN_APPEAR（goblin_fox.cpp:100）
//   +472  0x590C40 幻影消散演出 KENSIN_DISAPPEAR（goblin_fox.cpp:245）
//   +512  0x590AD0 受击处理·直接伤害版（goblin_fox.cpp:179）
//   +1164 0x590900 阈值装载（宿主 CNFighter 战斗读数，goblin_fox.cpp:71）
//   继承自 IRDMonster: 0x4DE410/0x4A41C0/0x4DB480/0x4D94A0/0x4D5A90/0x499020/0x4E5C10
// ============================================================
#ifndef ARAD40JP_FIELDS_CNFIGHTERILLUSION
#define ARAD40JP_FIELDS_CNFIGHTERILLUSION

#include <stdint.h>

#pragma pack(push, 1)
struct CNFighterIllusion_Fields {
    unsigned char _base_head[73]; // +0x0000..0x0048 继承自 CNRDObject/IRDCollisionObject/IRDActiveObject（见 src/cnrd/*.h；首个观测偏移之前）（不重复展开）
    char             szDigitalName;   // +0x0049 (73) x1  va=004DE410 基类数字名缓冲起点（0x4DE410 sprintf 名称后写 vt+340() 动作对象 +4）【基类字段：IRDMonster 同址】
    unsigned char _unused_004A[46]; // +0x004A..0x0077 未观测
    unsigned int     pAnimObj;        // +0x0078 (120) x6  va=00499020 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】
    unsigned char _unused_007C[108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag;       // +0x00E8 (232) x2  va=00499020 基类时刻同步开关位（0x499020）【基类字段】
    unsigned char _unused_00E9[3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA;       // +0x00EC (236) x1  va=00499020 基类时刻同步参数 A【基类字段】
    unsigned int     nSyncArgB;       // +0x00F0 (240) x1  va=00499020 基类时刻同步参数 B【基类字段】
    float            fSyncTime;       // +0x00F4 (244) x4  va=00499080 基类浮点时刻槽（0x499080）【基类字段】
    unsigned char    bQuad1;          // +0x00F8 (248) x1  va=0042A8D0 基类四元组字节槽 1（CNRDObject__vmt11C）【基类字段】
    unsigned char _unused_00F9[3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2;          // +0x00FC (252) x1  va=0042A8D0 基类四元组 dword 槽 2【基类字段】
    unsigned char    bQuad3;          // +0x0100 (256) x1  va=0042A8D0 基类四元组字节槽 3【基类字段】
    unsigned char _unused_0101[3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4;          // +0x0104 (260) x1  va=0042A8D0 基类四元组 dword 槽 4【基类字段】
    // ---- 区块: 表现壳与拾取族（继承 IRDMonster 槽函数） ----
    unsigned char _unused_0108[378]; // +0x0108..0x0281 未观测
    unsigned char    bAttackEnable;   // +0x0282 (642) x5  va=004E5C10 攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；基类定案 +642）【基类字段】
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride;  // +0x0284 (644) x4  va=004E5C10 帧时刻覆盖值（0x4E5C10）【基类字段】
    unsigned char _unused_0288[20]; // +0x0288..0x029B 未观测
    unsigned int     nPickPosCache;   // +0x029C (668) x1  va=004D94A0 拾取/交互目标坐标缓存（sub_4D94A0 由 +8352 拷入，与 +672 成对）【推断】【基类字段】
    unsigned int     bPickPosValid;   // +0x02A0 (672) x1  va=004D94A0 拾取/交互目标有效标志（与 +668 成对置 1）【推断】【基类字段】
    unsigned char _unused_02A4[6420]; // +0x02A4..0x1BB7 未观测
    unsigned int     nStealthStart;   // +0x1BB8 (7096) x1  va=004D5A90 【推断】隐身/伪装窗口起始时刻（0x4D5A90 影身计时三连写）【基类字段】
    unsigned int     nStealthDur;     // +0x1BBC (7100) x1  va=004D5A90 【推断】隐身/伪装窗口时长 ms（0x4D5AC0 折算）【基类字段】
    unsigned char    bStealthFlag;    // +0x1BC0 (7104) x1  va=004D5A90 【推断】隐身/伪装开关字节【基类字段】
    // ---- 区块: 大状态与配置块族（继承 IRDMonster 0x4DB480/0x4A41C0） ----
    unsigned char _unused_1BC1[43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nBigState;       // +0x1BEC (7148) x1  va=004DB480 ★ 幻影大状态 ID（0x4DB480 反击判定 11/12→切 4；IRDMonster +7148 定案）【基类字段】
    unsigned char _unused_1BF0[368]; // +0x1BF0..0x1D5F 未观测
    unsigned int     nSightRange;     // +0x1D60 (7520) x1  va=004A41C0 ★ 内嵌配置块首 DWORD / 视野值（0x4A41C0 整体拷贝；IRDMonster 同址定案）【基类字段】
    unsigned int     nCfgBlock4;      // +0x1D64 (7524) x1  va=004A41C0 内嵌配置块 +4（0x4A41C0）【推断】【基类字段】
    unsigned char    bCfgBlock8;      // +0x1D68 (7528) x1  va=004A41C0 内嵌配置块 +8 字节【基类字段】
    unsigned char    bCounterEnable;  // +0x1D69 (7529) x2  va=004DB480 【推断】反击/架招生效标志（0x4DB480 命中后据此调 vt+1236）【基类字段】
    unsigned char    bCfgBlock10;     // +0x1D6A (7530) x1  va=004A41C0 内嵌配置块 +10 字节【基类字段】
    unsigned char    bCfgBlock11;     // +0x1D6B (7531) x1  va=004A41C0 内嵌配置块 +11 字节【基类字段】
    unsigned char    bCfgBlock12;     // +0x1D6C (7532) x1  va=004A41C0 内嵌配置块 +12 字节【基类字段】
    unsigned char    bCfgBlock13;     // +0x1D6D (7533) x1  va=004A41C0 内嵌配置块 +13 字节【基类字段】
    unsigned char    bCfgBlock14;     // +0x1D6E (7534) x1  va=004A41C0 内嵌配置块 +14 字节【基类字段】
    unsigned char    bCfgBlock15;     // +0x1D6F (7535) x1  va=004A41C0 内嵌配置块 +15 字节【基类字段】
    unsigned char    bCfgBlock16;     // +0x1D70 (7536) x1  va=004A41C0 内嵌配置块 +16 字节【基类字段】
    unsigned char    bCfgBlock17;     // +0x1D71 (7537) x1  va=004A41C0 内嵌配置块 +17 字节【基类字段】
    unsigned char    bCfgBlock18;     // +0x1D72 (7538) x1  va=004A41C0 内嵌配置块 +18 字节【基类字段】
    unsigned char    bCfgTail;        // +0x1D73 (7539) x1  va=004A41C0 配置块 17 字节循环搬运区起点（0x4A41C0）【基类字段】
    // ---- 区块: 反击态族（继承 IRDMonster 0x4DB480） ----
    unsigned char _unused_1D74[232]; // +0x1D74..0x1E5B 未观测
    unsigned int     nCounterState;   // +0x1E5C (7772) x1  va=004DB480 ★ 反击态（1/2 时 0x4DB480 走架招档位判定）【基类字段】
    // ---- 区块: 拾取信息族（继承 IRDMonster 0x4D94A0） ----
    unsigned char _unused_1E60[576]; // +0x1E60..0x209F 未观测
    unsigned int     nPickSrcPos;     // +0x20A0 (8352) x1  va=004D94A0 拾取/交互源坐标缓存（对象首字节非 0 时被写入 +668）【推断】【基类字段】
    unsigned int     pPickTarget;     // +0x20A4 (8356) x2  va=004D94A0 拾取目标对象指针（0x5EA970 同族用后清零）【基类字段】
    unsigned int     pPickInfo;       // +0x20A8 (8360) x5  va=004D94A0 ★ 拾取信息块指针（7 字节=dword+word+byte；0x4D94A0 懒创建/释放）【基类字段】
    // ---- 区块: 幻影出场/消散族（本类独有 0x5908C0 + 0x590970） ----
    unsigned char _unused_20AC[236]; // +0x20AC..0x2197 未观测
    unsigned int     nAppearCnt;      // +0x2198 (8600) x1  va=005908C0 ★ 出场/消散计数器（0x5908C0 复位为 0；0x590900 阈值装载关系槽）
    unsigned char    bAppearSet;      // +0x219C (8604) x1  va=005908C0 ★ 出场动作已设标志（0x5908C0 清 0；0x590970 出场演出的一次性门）
    unsigned char    bAppearPlayed;   // +0x219D (8605) x1  va=005908C0 ★ KENSIN_APPEAR 已播标志（0x5908C0 清 0 允许重播；0x5908E0 亦清它）
};
#pragma pack(pop)

// 统计: 字段行 39 / 未命名 0 / 标【推断】8 / 末尾偏移 +0x219E

#endif
