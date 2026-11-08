// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNGardener_Ral   主虚表槽位数: 327   字段数: 60
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定（偏移/类型为二进制直证，未改）
// 依据: ①通用偏移表 ②证据行 va ③同族跨类印证 ④src 已精修函数头注释；无据名保留 field_XXXX
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNGardener_Ral
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGardener_Ral_Fields {
    // ---- 区块 1：继承 IRDMonster 基类区（通用偏移表；动画/帧时刻/参数槽） ----
    unsigned char _base_0x0000        [73]; // +0x0000..0x0048 继承 IRDMonster 基类区
    char             bFlag0049           ; // +0x0049 (73) x1  标志字节（与 +74 成对清零：0x49A9A0/0x49DCF0；0x4DE410 名称装配取址）【推断】
    unsigned char _unused_0x004A      [38]; // +0x004A..0x006F 未观测
    unsigned int     pShared112          ; // +0x0070 (112) x3  默认共享组件/坐标三元组指针（vmt3C 取 this+112；0x594490 读其 +192）
    unsigned char _unused_0x0074      [4]; // +0x0074..0x0077 未观测
    unsigned int     pAnim120            ; // +0x0078 (120) x8  动画/帧对象指针（全库通用：动画对象 = this+120）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bAnimSync232        ; // +0x00E8 (232) x2  动画时刻同步开关（0x499020 关→开时同步帧时刻；0x498B70 复位）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     uAnimSync236        ; // +0x00EC (236) x1  动画同步参数 A（0x499020 写 nArg3）
    unsigned int     uAnimSync240        ; // +0x00F0 (240) x1  动画同步参数 B（0x499020 写 nArg4）
    float            fAnimSync244        ; // +0x00F4 (244) x4  动画同步浮点参数（0x499080 浮点版：非 0→0 时推帧）
    unsigned char    bParam248           ; // +0x00F8 (248) x1  参数灌入槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     uParam252           ; // +0x00FC (252) x1  参数灌入槽 2（0x42A8D0）
    unsigned char    bParam256           ; // +0x0100 (256) x1  参数灌入槽 3（0x42A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     uParam260           ; // +0x0104 (260) x1  参数灌入槽 4（0x42A8D0）
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char    bFrameOv642         ; // +0x0282 (642) x5  帧时刻覆盖开关（0x4E5C10：非 0 时用 +644 直写帧时刻）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     uFrameOv644         ; // +0x0284 (644) x4  帧时刻覆盖值（0x4E5C10）
    unsigned char _unused_0x0288      [20]; // +0x0288..0x029B 未观测
    unsigned int     uPick668            ; // +0x029C (668) x1  拾取目标坐标缓存 A（0x4D94A0 写 668/672；0x4E7160 复位）
    unsigned int     uPick672            ; // +0x02A0 (672) x1  拾取目标坐标缓存 B（0x4D94A0）
    // ---- 区块 2：子类对象与帧表区（主状态镜像/状态表） ----
    unsigned char _unused_0x02A4      [5880]; // +0x02A4..0x199B 未观测
    unsigned int     nMainState6556      ; // +0x199C (6556) x3  主状态镜像（全库通用；vt+840 读取器 / 0x4A1010 对应）
    // ---- 区块 3：子类扩展槽区（计数槽/隐身计时） ----
    unsigned char _unused_0x19A0      [536]; // +0x19A0..0x1BB7 未观测
    unsigned int     uStealthT0_7096     ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻 clock_now(this+36)（0x4D5A90）【推断】
    unsigned int     uStealthDur7100     ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 写 nArg2）【推断】
    unsigned char    bStealthOn7104      ; // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 写 pszArg3）【推断】
    // ---- 区块 5：分身/攻击参数面（+7531..7596；0x4A41C0 配置块） ----
    unsigned char _unused_0x1BC1      [415]; // +0x1BC1..0x1D5F 未观测
    unsigned int     uCfg7520            ; // +0x1D60 (7520) x1  配置块首（0x4A41C0 整体拷贝 44+ 字节）【推断：装备/染色配置缓存】
    unsigned int     uCfg7524            ; // +0x1D64 (7524) x1  配置块 +4（0x4A41C0）
    unsigned char    bCfg7528            ; // +0x1D68 (7528) x1  配置块 +8（0x4A41C0）
    unsigned char    bCfg7529            ; // +0x1D69 (7529) x1  配置块 +9（0x4A41C0）
    unsigned char    bCfg7530            ; // +0x1D6A (7530) x1  配置块 +10（0x4A41C0）
    unsigned char    bCfg7531            ; // +0x1D6B (7531) x2  配置块 +11 / 攻击参数面首字节（0x594A20 整块清零）
    unsigned char    bCfg7532            ; // +0x1D6C (7532) x2  配置块 +12（0x4A41C0）
    unsigned char    bCfg7533            ; // +0x1D6D (7533) x2  配置块 +13（0x4A41C0）
    unsigned char    bCfg7534            ; // +0x1D6E (7534) x3  配置块 +14 / 段选门（0x594A20 nArg3==2→1；0x5B7F90 形态槽）
    unsigned char    bCfg7535            ; // +0x1D6F (7535) x2  配置块 +15 / 门（0x594A20 面整块清零族；0x5CD2C0 按档置位）
    unsigned char    bCfg7536            ; // +0x1D70 (7536) x1  配置块 +16（0x4A41C0）
    unsigned char    bCfg7537            ; // +0x1D71 (7537) x1  配置块 +17 / 门（0x595380 置 1）
    unsigned char    bCfg7538            ; // +0x1D72 (7538) x1  配置块 +18 / 门（0x5968D0 nArg2∈1..2→1）
    unsigned char    bCfg7539            ; // +0x1D73 (7539) x2  配置块 +19（0x4A41C0 循环拷贝起点）
    unsigned char _unused_0x1D74      [3]; // +0x1D74..0x1D76 未观测
    unsigned int     uAtk7543            ; // +0x1D77 (7543) x1  攻击参数面槽（整面清零族 0x594A20/0x5BA730/0x5CD2C0）【推断】
    unsigned int     uAtk7547            ; // +0x1D7B (7547) x1  攻击参数面槽（整面清零族）【推断】
    unsigned int     uAtk7551            ; // +0x1D7F (7551) x1  攻击参数面槽（整面清零族）【推断】
    unsigned char    bAtk7555            ; // +0x1D83 (7555) x1  攻击参数面字节槽【推断】
    unsigned char    bAtk7556            ; // +0x1D84 (7556) x1  攻击面模式字节（0x599C30 按档写）【推断】
    unsigned char    bAtk7557            ; // +0x1D85 (7557) x1  攻击面门字节（0x5B3420 置 1）【推断】
    unsigned char    bAtk7558            ; // +0x1D86 (7558) x1  攻击参数面字节槽【推断】
    unsigned char _unused_0x1D87      [5]; // +0x1D87..0x1D8B 未观测
    unsigned int     uAtk7564            ; // +0x1D8C (7564) x1  形态/模式槽（0x5B7E00 置 1、0x5BA810 置 2）【推断】
    unsigned int     uMode7568           ; // +0x1D90 (7568) x3  激活/模式槽（0x594A20 置 1、0x595380 置 2）【推断】
    unsigned int     uMode7572           ; // +0x1D94 (7572) x1  模式 2 档（0x59C4C0 置 2）【推断】
    unsigned int     uAtk7576            ; // +0x1D98 (7576) x1  攻击参数面槽【推断】
    unsigned int     uAtk7580            ; // +0x1D9C (7580) x1  攻击面门字节（0x59C4C0 置 1）【推断】
    unsigned int     uForm7584           ; // +0x1DA0 (7584) x1  形态槽（0x5B7CD0 清面后置 1）【推断】
    unsigned int     uForm7588           ; // +0x1DA4 (7588) x1  形态槽（0x5B7D60/0x5B3420 置 1）【推断】
    unsigned char _unused_0x1DA8      [4]; // +0x1DA8..0x1DAB 未观测
    unsigned int     nOffset7596         ; // +0x1DAC (7596) x3  段号横向偏置（±50 / -30 / -100；换目标对齐）【推断】
    // ---- 区块 6：子类相位/资源对象槽区 ----
    unsigned char _unused_0x1DB0      [20]; // +0x1DB0..0x1DC3 未观测
    unsigned int     pParamObj7620       ; // +0x1DC4 (7620) x2  速度/属性参数对象（其 +4/+68/+100/+132 浮点被倍率改写）【推断】
    unsigned char _unused_0x1DC8      [196]; // +0x1DC8..0x1E8B 未观测
    unsigned int     pFrame7820          ; // +0x1E8C (7820) x2  帧/资源对象槽（0x4E3360 析构释放；0x4DE700 复位）【推断】
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1E90      [528]; // +0x1E90..0x209F 未观测
    unsigned int     uPick8352           ; // +0x20A0 (8352) x1  拾取信息槽 A（0x4D94A0 快照；0x4DE700 复位）
    unsigned int     uPick8356           ; // +0x20A4 (8356) x2  拾取信息槽 B（0x4D94A0 写 uArg3）
    unsigned int     pPickInfo8360       ; // +0x20A8 (8360) x6  拾取信息 7 字节对象指针（0x4D94A0 懒创建/释放）
    unsigned int     pSlot8364           ; // +0x20AC (8364) x1  扩展资源槽（0x4E3360 析构释放；0x4DE700 复位）【推断】
    // ---- 区块 8：子类 AI 状态区（+8600+；相位/事件/特效槽） ----
    unsigned char _unused_0x20B0      [232]; // +0x20B0..0x2197 未观测
    unsigned char    bAI8600             ; // +0x2198 (8600) x3  相位门（0x594490：相位 0 且帧≥3 且本槽空 → 起手并置 1）
    unsigned char    bAI8601             ; // +0x2199 (8601) x6  相位门（0x594490：this+112→+24 浮点>0 时置 1）
    unsigned char    bAI8602             ; // +0x219A (8602) x4  收尾相位门（0x594490：this+112→+192==4 时置 1）
    unsigned char _unused_0x219B      [1]; // +0x219B..0x219B 未观测
    unsigned int     uAI8604             ; // +0x219C (8604) x1  附属物槽/相位（0x595C40：非 0 走獠牙变身，瞬移对齐其位置）
    unsigned int     uAI8608             ; // +0x21A0 (8608) x1  子类 AI 槽（0x594340 九字段复位区）【推断】
    unsigned char _unused_0x21A4      [8]; // +0x21A4..0x21AB 未观测
    unsigned int     uFlag8620           ; // +0x21AC (8620) x1  换目标横向补偿标志（0x5B32C0 0↔1；0x5C4810 未置位门）【推断】
};
#pragma pack(pop)
