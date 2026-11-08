// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNGuardIce           主虚表槽位数: 340   字段数: 45
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定（偏移/类型为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNGuardIce
// 依据: ①通用偏移表 ②证据行 va ③同族跨类印证 ④src 已精修函数头注释
//   （人偶师族命名继承 CNStoneMaster.h/CNClayMaster.h；守卫/魔像族继承 CNGuardWind.h/CNGoliden.h）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGuardIce_Fields {
    // ---- 区块 1：继承 IRDMonster 基类区（通用偏移表；动画/帧时刻/参数槽） ----
    unsigned char _base_0x0000        [73]; // +0x0000..0x0048 继承 IRDMonster 基类区
    char             bFlag0049           ; // +0x0049 (73) x1  标志字节（与 +74 成对清零：0x49A9A0/0x49DCF0；0x4DE410 名称装配取址）【推断】
    unsigned char _unused_0x004A      [46]; // +0x004A..0x0077 未观测
    unsigned int     pAnim120            ; // +0x0078 (120) x6  动画/帧对象指针（全库通用：动画对象 = this+120）
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
    // ---- 区块 3：子类扩展槽区（计数槽/隐身计时） ----
    unsigned char _unused_0x02A4      [6420]; // +0x02A4..0x1BB7 未观测
    unsigned int     uStealthT0_7096     ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻 clock_now(this+36)（0x4D5A90）【推断】
    unsigned int     uStealthDur7100     ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 写 nArg2）【推断】
    unsigned char    bStealthOn7104      ; // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 写 pszArg3）【推断】
    // ---- 区块 4：主状态/目标/计时门区 ----
    unsigned char _unused_0x1BC1      [43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nBigState7148       ; // +0x1BEC (7148) x1  大状态/攻击段槽（0x4DB480 反击前置 / 白名单查询；==22 为守卫架招段）
    // ---- 区块 5：分身/攻击参数面（+7531..7596；0x4A41C0 配置块） ----
    unsigned char _unused_0x1BF0      [368]; // +0x1BF0..0x1D5F 未观测
    unsigned int     uCfg7520            ; // +0x1D60 (7520) x1  配置块首（0x4A41C0 整体拷贝 44+ 字节）【推断：装备/染色配置缓存】
    unsigned int     uCfg7524            ; // +0x1D64 (7524) x1  配置块 +4（0x4A41C0）
    unsigned char    bCfg7528            ; // +0x1D68 (7528) x1  配置块 +8（0x4A41C0）
    unsigned char    bCfg7529            ; // +0x1D69 (7529) x2  配置块 +9 / 反击门（0x4DB480：非 0 才 vt+1236 后续钩子）
    unsigned char    bCfg7530            ; // +0x1D6A (7530) x1  配置块 +10（0x4A41C0）
    unsigned char    bCfg7531            ; // +0x1D6B (7531) x1  配置块 +11 / 攻击参数面首字节（0x594A20 整块清零）
    unsigned char    bCfg7532            ; // +0x1D6C (7532) x1  配置块 +12（0x4A41C0）
    unsigned char    bCfg7533            ; // +0x1D6D (7533) x1  配置块 +13（0x4A41C0）
    unsigned char    bCfg7534            ; // +0x1D6E (7534) x1  配置块 +14 / 段选门（0x594A20 nArg3==2→1；0x5B7F90 形态槽）
    unsigned char    bCfg7535            ; // +0x1D6F (7535) x1  配置块 +15 / 门（0x594A20 面整块清零族；0x5CD2C0 按档置位）
    unsigned char    bCfg7536            ; // +0x1D70 (7536) x1  配置块 +16（0x4A41C0）
    unsigned char    bCfg7537            ; // +0x1D71 (7537) x1  配置块 +17 / 门（0x595380 置 1）
    unsigned char    bCfg7538            ; // +0x1D72 (7538) x1  配置块 +18 / 门（0x5968D0 nArg2∈1..2→1）
    unsigned char    bCfg7539            ; // +0x1D73 (7539) x1  配置块 +19（0x4A41C0 循环拷贝起点）
    // ---- 区块 6：子类相位/资源对象槽区 ----
    unsigned char _unused_0x1D74      [232]; // +0x1D74..0x1E5B 未观测
    unsigned int     nCounterState       ; // +0x1E5C (7772) x1  反击态（0x4DB480 变量名 nCounterState=*(this+7772)，值 1/2；==3 困难级）
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1E60      [436]; // +0x1E60..0x2013 未观测
    unsigned int     pHintText8212       ; // +0x2014 (8212) x1  提示文案格式化对象（0x5D2BB0：sub_41ACF0(this+8212 + 4) 取模板串 sprintf 写提示）【推断】
    unsigned char _unused_0x2018      [136]; // +0x2018..0x209F 未观测
    unsigned int     uPick8352           ; // +0x20A0 (8352) x1  拾取信息槽 A（0x4D94A0 快照；0x4DE700 复位）
    unsigned int     uPick8356           ; // +0x20A4 (8356) x2  拾取信息槽 B（0x4D94A0 写 uArg3）
    unsigned int     pPickInfo8360       ; // +0x20A8 (8360) x5  拾取信息 7 字节对象指针（0x4D94A0 懒创建/释放）
    // ---- 区块 8：子类 AI 状态区（+8600+；相位/事件/特效槽） ----
    unsigned char _unused_0x20AC      [489]; // +0x20AC..0x2294 未观测
    unsigned char    bFlag8853           ; // +0x2295 (8853) x2  相位标志（0x5D2BB0 冰守卫事件收尾清 8853/8854）【推断】
    unsigned char    bFlag8854           ; // +0x2296 (8854) x2  相位标志（同 8853 成对）【推断】
    unsigned char _unused_0x2297      [13]; // +0x2297..0x22A3 未观测
    unsigned char    bGate8868           ; // +0x22A4 (8868) x3  冰守卫交互门（0x5D2BB0：为 0 时才写提示与播报 R_ICE_GUARD；收尾清 0）【推断】
    unsigned char _unused_0x22A5      [3]; // +0x22A5..0x22A7 未观测
    unsigned int     uDur8872            ; // +0x22A8 (8872) x2  相位时长槽（0x5D2BB0 读出后经 sub_698F90 重排 8840 时钟）【推断】
    unsigned int     uPhase8876          ; // +0x22AC (8876) x1  相位区槽（0x5CFAA0 相位复位 D 清零）【推断】
    unsigned int     uPhase8880          ; // +0x22B0 (8880) x1  相位区槽（0x5CFAA0 清零；0x5D7100 构造置 1）【推断】
    unsigned int     uPhase8884          ; // +0x22B4 (8884) x1  相位区槽（0x5CFAA0 清零）【推断】
    unsigned int     uPhase8888          ; // +0x22B8 (8888) x1  相位区槽（0x5CFAA0 清零）【推断】
};
#pragma pack(pop)

// 统计: 字段行 45 / 未命名 0 / 标【推断】13 / 末尾偏移 +0x22BC

