// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNGuardWind      主虚表槽位数: 340   字段数: 60
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定（偏移/类型为二进制直证，未改）
// 依据: ①通用偏移表 ②证据行 va ③同族跨类印证 ④src 已精修函数头注释；无据名保留 field_XXXX
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNGuardWind
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGuardWind_Fields {
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
    unsigned int     nBigState7148       ; // +0x1BEC (7148) x1  大状态（0x4DB480 反击前置 / 白名单查询；==22 为守卫架招段）
    unsigned char _unused_0x1BF0      [100]; // +0x1BF0..0x1C53 未观测
    unsigned int     pTarget7252         ; // +0x1C54 (7252) x3  当前目标/关联对象（0x5D0BA0 可架招窗口判定；0x5AD610 取坐标）
    // ---- 区块 5：分身/攻击参数面（+7531..7596；0x4A41C0 配置块） ----
    unsigned char _unused_0x1C58      [264]; // +0x1C58..0x1D5F 未观测
    unsigned int     uCfg7520            ; // +0x1D60 (7520) x1  配置块首（0x4A41C0 整体拷贝 44+ 字节）【推断：装备/染色配置缓存】
    unsigned int     uCfg7524            ; // +0x1D64 (7524) x1  配置块 +4（0x4A41C0）
    unsigned char    bCfg7528            ; // +0x1D68 (7528) x1  配置块 +8（0x4A41C0）
    unsigned char    bCfg7529            ; // +0x1D69 (7529) x1  配置块 +9（0x4A41C0）
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
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1D74      [812]; // +0x1D74..0x209F 未观测
    unsigned int     uPick8352           ; // +0x20A0 (8352) x1  拾取信息槽 A（0x4D94A0 快照；0x4DE700 复位）
    unsigned int     uPick8356           ; // +0x20A4 (8356) x2  拾取信息槽 B（0x4D94A0 写 uArg3）
    unsigned int     pPickInfo8360       ; // +0x20A8 (8360) x5  拾取信息 7 字节对象指针（0x4D94A0 懒创建/释放）
    // ---- 区块 8：子类 AI 状态区（+8600+；相位/事件/特效槽） ----
    unsigned char _unused_0x20AC      [305]; // +0x20AC..0x21DC 未观测
    unsigned char    bGuardActive8669    ; // +0x21DD (8669) x1  守卫激活位（0x5D0070/0x5D0BA0 守卫相位主门三条件之一）
    unsigned char _unused_0x21DE      [170]; // +0x21DE..0x2287 未观测
    unsigned char    bPhase8840          ; // +0x2288 (8840) x1  相位/档位槽（0x5CFC40 伤害门按 0/1 吸收；0x5CFB50 按档取色）
    unsigned char _unused_0x2289      [16]; // +0x2289..0x2298 未观测
    unsigned char    bPhase8857          ; // +0x2299 (8857) x2  相位标志（事件 28 清 8857/8858 后挂 this+8844 时钟）【推断】
    unsigned char    bPhase8858          ; // +0x229A (8858) x2  相位标志（同 8857 成对）【推断】
    unsigned char _unused_0x229B      [13]; // +0x229B..0x22A7 未观测
    unsigned char    bDur8872            ; // +0x22A8 (8872) x1  相位时长槽（0x5D2BB0 读出后经 sub_698F90 重排 8840 时钟；字节写入点见复位 C）【推断】
    unsigned char _unused_0x22A9      [16]; // +0x22A9..0x22B8 未观测
    unsigned char    bPhase8889          ; // +0x22B9 (8889) x1  相位字节（0x5CF7F0 阿莫尔相位复位 C 清）【推断】
    unsigned char    bPhase8890          ; // +0x22BA (8890) x1  相位字节（同 8889 成对）【推断】
    unsigned char _unused_0x22BB      [38]; // +0x22BB..0x22E0 未观测
    unsigned char    bPhase8929          ; // +0x22E1 (8929) x1  相位字节（0x5CF7F0 清）【推断】
    unsigned char    bPhase8930          ; // +0x22E2 (8930) x1  相位字节（同 8929 成对）【推断】
    unsigned char _unused_0x22E3      [26]; // +0x22E3..0x22FC 未观测
    unsigned char    bPhase8957          ; // +0x22FD (8957) x1  相位字节（0x5CF7F0 阿莫尔相位复位 C 清十标志之一）【推断】
    unsigned char    bPhase8958          ; // +0x22FE (8958) x1  相位字节（同 8957 成对）【推断】
    unsigned char _unused_0x22FF      [13]; // +0x22FF..0x230B 未观测
    unsigned int     uEvtState8972       ; // +0x230C (8972) x2  事件档位（事件 26→1、27→2；0x5D1D90）
    unsigned int     uEvtState8976       ; // +0x2310 (8976) x2  事件档位（同 8972 成对；0x5D1D90）
    unsigned int     uEffect8980         ; // +0x2314 (8980) x1  特效/资源槽（0x5D7500 析构释放并清零）
    unsigned char _unused_0x2318      [28]; // +0x2318..0x2333 未观测
    unsigned int     uClockDur9012       ; // +0x2334 (9012) x2  时钟时长（事件 28 挂 this+8844 时钟取此时长）
    unsigned int     uPhaseC9016         ; // +0x2338 (9016) x1  阿莫尔相位第三段（0x5CF7F0 复位区 9012..9048）【推断】
    unsigned int     uPhaseC9020         ; // +0x233C (9020) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9024         ; // +0x2340 (9024) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9028         ; // +0x2344 (9028) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9032         ; // +0x2348 (9032) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9036         ; // +0x234C (9036) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9040         ; // +0x2350 (9040) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9044         ; // +0x2354 (9044) x1  阿莫尔相位第三段复位区【推断】
    unsigned int     uPhaseC9048         ; // +0x2358 (9048) x1  阿莫尔相位第三段复位区末槽（+9048）【推断】
};
#pragma pack(pop)
