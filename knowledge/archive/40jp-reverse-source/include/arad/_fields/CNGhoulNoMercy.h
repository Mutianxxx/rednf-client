// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNGhoulNoMercy         主虚表槽位数: 331   字段数: 47
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名判定
// 置信度: 偏移/类型=二进制直证；语义名=证据推断（【推断】标注无直证者）
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNGhoulNoMercy
// 依据: ①通用偏移表（this+120 动画对象 / +642..644 帧覆盖 / +6556 主状态镜像 / +7096..7104 影身计时 /
//        +7148 大状态 / +7252 目标 / +7772 反击态 / +8352..8364 拾取信息）②证据行 va
//        ③同族跨类印证 ④src 已精修函数头注释：食尸鬼族（0x58C090 技能槽 vmt4A8 复位批）；基类段命名继承 CNZombie.h 与 IRDMonster.h
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGhoulNoMercy_Fields {
    // ---- 区块 1：继承基类区（通用偏移表；动画对象/帧同步/参数灌入/帧时刻覆盖） ----
    unsigned char _base_0x0000        [73]; // +0x0000..0x0048 继承基类区（见 IRDMonster.h / src/cnrd/*.h）
    char             szDigitalName       ; // +0x0049 (73) x1  基类数字名缓冲 SSO 首字节（0x4DE410 sprintf 名称后写 vt+340 动作对象 +4）（证据: va=004DE410）
    unsigned char _unused_0x004A      [46]; // +0x004A..0x0077 未观测
    unsigned int     pAnimObj            ; // +0x0078 (120) x6  基类动画对象指针（0x499020/0x499080 帧时刻同步宿主；全库通用 this+120）（证据: va=00499020）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag           ; // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）（证据: va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参 nArg3）（证据: va=00499020）
    unsigned int     nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参 nArg4）（证据: va=00499020）
    float            fSyncTime           ; // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）（证据: va=00499080）
    unsigned char    bQuad1              ; // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）（证据: va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2              ; // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）（证据: va=0042A8D0）
    unsigned char    bQuad3              ; // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4              ; // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char    bAttackEnable       ; // +0x0282 (642) x5  基类攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；IRDActiveObject 定案 +642）（证据: va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride      ; // +0x0284 (644) x4  基类帧时刻覆盖值（与 +0x282 成对；0x4E5C10 第四参）（证据: va=004E5C10）
    unsigned char _unused_0x0288      [20]; // +0x0288..0x029B 未观测
    unsigned int     nPickPosCache       ; // +0x029C (668) x1  拾取/交互目标坐标缓存（0x4D94A0 由 +8352 拷入，与 +0x2A0 成对）【推断】（证据: va=004D94A0）
    unsigned int     uPickPosValid       ; // +0x02A0 (672) x1  拾取/交互目标有效标志（与 +0x29C 成对置 1）【推断】（证据: va=004D94A0）
    // ---- 区块 3：子类扩展槽区（语音槽组/参数面/相位联动） ----
    unsigned char _unused_0x02A4      [6116]; // +0x02A4..0x1A87 未观测
    unsigned int     uVoice6792          ; // +0x1A88 (6792) x1  语音/技能槽组编号 1（0x58C090 技能槽 vmt4A8 写 1）【推断】（证据: va=0058C090）
    unsigned int     uVoice6796          ; // +0x1A8C (6796) x1  语音/技能槽组编号 2（0x58C090 写 1）【推断】（证据: va=0058C090）
    unsigned int     uVoice6800          ; // +0x1A90 (6800) x1  语音/技能槽组编号 3（0x58C090 写 3）【推断】（证据: va=0058C090）
    unsigned int     uVoice6804          ; // +0x1A94 (6804) x1  语音/技能槽组编号 4（0x58C090 写 4）【推断】（证据: va=0058C090）
    unsigned int     uVoice6808          ; // +0x1A98 (6808) x1  语音/技能槽组编号 5（0x58C090 写 4；同族 0x5AF220 以本组喂 ZOMBIE_* TAG）【推断】（证据: va=0058C090）
    unsigned char _unused_0x1A9C      [284]; // +0x1A9C..0x1BB7 未观测
    unsigned int     nStealthStart       ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻（0x4D5A90 影身计时三连写；clock_now(this+36)）【基类字段】（证据: va=004D5A90）
    unsigned int     nStealthDur         ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 按 1000×时长/+6656 折算剩余量）【基类字段】（证据: va=004D5A90）
    unsigned char    bStealthFlag        ; // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 置位时走折算；0x4D7F30 伪装态切换）【基类字段】（证据: va=004D5A90）
    // ---- 区块 5：攻击参数面（+7531..7596；0x4A41C0 配置块 × 0x5AE6E0 复位面） ----
    unsigned char _unused_0x1BC1      [415]; // +0x1BC1..0x1D5F 未观测
    unsigned int     nSightRange         ; // +0x1D60 (7520) x1  内嵌配置块首 DWORD / 视野值（0x4A41C0 整体拷贝；索敌门算距离衰减）（证据: va=004A41C0）
    unsigned int     uCfgBlock4          ; // +0x1D64 (7524) x1  内嵌配置块 +4 字节（0x4A41C0 整体拷贝）【推断】（证据: va=004A41C0）
    unsigned char    bCfgBlock8          ; // +0x1D68 (7528) x1  内嵌配置块 +8 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCounterEnable      ; // +0x1D69 (7529) x1  反击/架招生效标志（0x4DB480 命中后据此调 vt+1236；本类证据为 0x4A41C0 整拷）【推断】（证据: va=004DB480）
    unsigned char    bCfgBlock10         ; // +0x1D6A (7530) x1  内嵌配置块 +10 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock11         ; // +0x1D6B (7531) x1  内嵌配置块 +11 字节 / 攻击参数面首字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock12         ; // +0x1D6C (7532) x1  内嵌配置块 +12 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock13         ; // +0x1D6D (7533) x1  内嵌配置块 +13 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock14         ; // +0x1D6E (7534) x1  内嵌配置块 +14 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock15         ; // +0x1D6F (7535) x1  内嵌配置块 +15 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock16         ; // +0x1D70 (7536) x1  内嵌配置块 +16 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock17         ; // +0x1D71 (7537) x1  内嵌配置块 +17 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgBlock18         ; // +0x1D72 (7538) x1  内嵌配置块 +18 字节（0x4A41C0）（证据: va=004A41C0）
    unsigned char    bCfgTail            ; // +0x1D73 (7539) x1  配置块 17 字节循环搬运区起点（0x4A41C0）（证据: va=004A41C0）
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364 拾取信息族） ----
    unsigned char _unused_0x1D74      [812]; // +0x1D74..0x209F 未观测
    unsigned int     nRideHost8352       ; // +0x20A0 (8352) x1  骑乘/宿主槽（全库通用 this+8352；0x4D94A0 拾取快照源、0x4DE700 复位）（证据: va=004D94A0）
    unsigned int     uPick8356           ; // +0x20A4 (8356) x2  拾取信息槽 B（0x4D94A0 写 uArg3）（证据: va=004D94A0）
    unsigned int     pPickInfo8360       ; // +0x20A8 (8360) x5  拾取信息 7 字节对象指针（0x4D94A0 懒创建/释放）（证据: va=004D94A0）
    // ---- 区块 8：子类 AI 状态区（+8600+；相位/事件/特效/编队槽） ----
    unsigned char _unused_0x20AC      [256]; // +0x20AC..0x21AB 未观测
    unsigned char    bAI8620             ; // +0x21AC (8620) x1  子类 AI 相位字节（0x58C090 技能槽复位清 0）【推断】（证据: va=0058C090）
    unsigned char _unused_0x21AD      [3]; // +0x21AD..0x21AF 未观测
    unsigned int     uAI8624             ; // +0x21B0 (8624) x1  子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned char _unused_0x21B4      [13]; // +0x21B4..0x21C0 未观测
    unsigned char    bAI8641             ; // +0x21C1 (8641) x1  子类 AI 相位字节（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned char    bAI8642             ; // +0x21C2 (8642) x1  子类 AI 相位字节（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned char _unused_0x21C3      [13]; // +0x21C3..0x21CF 未观测
    unsigned int     uAI8656             ; // +0x21D0 (8656) x1  子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned char _unused_0x21D4      [12]; // +0x21D4..0x21DF 未观测
    unsigned int     uAI8672             ; // +0x21E0 (8672) x1  子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned int     uAI8676             ; // +0x21E4 (8676) x1  子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）
    unsigned int     uAI8680             ; // +0x21E8 (8680) x1  子类 AI 相位槽（0x58C090 复位清 0）【推断】（证据: va=0058C090）
};
#pragma pack(pop)

// 统计: 字段行 47 / 未命名 0 / 标【推断】17 / 末尾偏移 +0x21EC

