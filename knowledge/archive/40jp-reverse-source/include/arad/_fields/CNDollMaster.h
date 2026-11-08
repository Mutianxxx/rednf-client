// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNDollMaster         主虚表槽位数: 329   字段数: 51
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定（偏移/类型为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDMonster -> CNDollMaster
// 依据: ①通用偏移表 ②证据行 va ③同族跨类印证 ④src 已精修函数头注释
//   （人偶师族命名继承 CNStoneMaster.h/CNClayMaster.h；守卫/魔像族继承 CNGuardWind.h/CNGoliden.h）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNDollMaster_Fields {
    // ---- 区块 1：继承 IRDMonster 基类区（通用偏移表；动画/帧时刻/参数槽） ----
    unsigned char _base_0x0000        [73]; // +0x0000..0x0048 继承 IRDMonster 基类区
    char             szNameBuf           ; // +0x0049 (73) x1  名字缓冲 SSO 首字节〔4DE410：名称模板 sprintf 读此〕；〔≙字节 292〕
    unsigned char _unused_0x004A      [46]; // +0x004A..0x0077 未观测
    unsigned int     pAnimObj            ; // +0x0078 (120) x7  动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncSwitch         ; // +0x00E8 (232) x2  时刻同步开关〔499020：由开转关时推进帧时刻〕
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA           ; // +0x00EC (236) x1  同步参数A〔499020 写 nArg3〕
    unsigned int     nSyncArgB           ; // +0x00F0 (240) x1  同步参数B〔499020 写 nArg4〕
    float            fSyncValue          ; // +0x00F4 (244) x4  浮点同步值〔499080 浮点版；vmt114 非零判定〕
    unsigned char    bParamSlotA         ; // +0x00F8 (248) x1  四参灌入槽A〔CNRDObject vmt11C 批量写 +248..+260〕
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     nParamSlotB         ; // +0x00FC (252) x1  四参灌入槽B〔vmt11C〕
    unsigned char    bParamSlotC         ; // +0x0100 (256) x1  四参灌入槽C〔vmt11C〕
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     nParamSlotD         ; // +0x0104 (260) x1  四参灌入槽D〔vmt11C〕
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char    bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关〔4E5C10 直证〕
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverrideTime  ; // +0x0284 (644) x4  覆盖帧时刻〔4E5C10 直证〕
    unsigned char _unused_0x0288      [20]; // +0x0288..0x029B 未观测
    unsigned int     nPickupXCache       ; // +0x029C (668) x1  拾取目标坐标缓存〔4D94A0 将 +8352 写入此槽〕【推断】
    unsigned int     nPickupValid        ; // +0x02A0 (672) x1  拾取坐标有效标志〔4D94A0 置 1〕【推断】
    // ---- 区块 2：子类对象与帧表区（主状态镜像/状态表） ----
    unsigned char _unused_0x02A4      [5880]; // +0x02A4..0x199B 未观测
    unsigned int     nBigStateMirror     ; // +0x199C (6556) x2  主状态镜像〔通用偏移表 this+6556〕
    // ---- 区块 3：子类扩展槽区（计数槽/隐身计时） ----
    unsigned char _unused_0x19A0      [536]; // +0x19A0..0x1BB7 未观测
    unsigned int     nInvisibleStart     ; // +0x1BB8 (7096) x1  影身计时-起始〔4D5A90 = clock_now(this+36)〕【推断】
    unsigned int     nInvisibleDur       ; // +0x1BBC (7100) x1  影身计时-时长ms〔4D5A90 nArg2〕【推断】
    unsigned char    bInvisibleSwitch    ; // +0x1BC0 (7104) x1  影身开关字节〔4D5A90 pszArg3〕【推断】
    // ---- 区块 4：主状态/目标/计时门区 ----
    unsigned char _unused_0x1BC1      [43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nBigState           ; // +0x1BEC (7148) x1  大状态〔4DB480 本文件变量名 nBigState=*(this+7148)；通用表〕
    unsigned char _unused_0x1BF0      [104]; // +0x1BF0..0x1C57 未观测
    unsigned int     pAuraObject         ; // +0x1C58 (7256) x1  光环对象槽〔通用偏移表 this+7256；5A8900 指令下发清 0 后交 ·0x64BDF0 重建〕
    // ---- 区块 5：分身/攻击参数面（+7531..7596；0x4A41C0 配置块） ----
    unsigned char _unused_0x1C5C      [260]; // +0x1C5C..0x1D5F 未观测
    unsigned int     uCfgWord0           ; // +0x1D60 (7520) x1  配置块首字〔4A41C0 48+字节整块拷贝 this+7520 区〕【推断】
    unsigned int     uCfgWord1           ; // +0x1D64 (7524) x1  配置块第2字〔4A41C0〕【推断】
    unsigned char    bRetargetGate       ; // +0x1D68 (7528) x1  目标重选门〔4E1BE0 门：·this+7528 标志〕【推断】
    unsigned char    bCounterHookSw      ; // +0x1D69 (7529) x2  反击后续钩子开关〔4DB480：非0 才 vt+1236〕【推断】
    unsigned char    bModeFlag7530       ; // +0x1D6A (7530) x1  参数面字节旗标〔hiteff_monster：与 7529/7531/7532/7533 同块自怪物表 +452..453 拷贝〕【推断】
    unsigned char    bModeFlagA          ; // +0x1D6B (7531) x1  参数面字节旗标A〔7531-7534 旗标族；各复位族整面清零〕【推断】
    unsigned char    bModeFlagB          ; // +0x1D6C (7532) x1  参数面字节旗标B〔旗标族〕【推断】
    unsigned char    bModeFlagC          ; // +0x1D6D (7533) x1  参数面字节旗标C〔旗标族〕【推断】
    unsigned char    bAggroGate7534      ; // +0x1D6E (7534) x1  威胁打分门〔4DCCB0：非0 时按 vt+672(3)+816/+830 属性对插值累加威胁分〕【推断】
    unsigned char    abAggroAttr4_0      ; // +0x1D6F (7535) x1  属性对比较使能组[4] 首项〔4DCCB0 逐字节遍历 7535..7538，命中取 vt+672(3)+172/+228 属性对插值〕【推断】
    unsigned char    abAggroAttr4_1      ; // +0x1D70 (7536) x1  属性对比较使能组[4] 第2项〔4DCCB0；+186/+242 属性对〕【推断】
    unsigned char    abAggroAttr4_2      ; // +0x1D71 (7537) x1  属性对比较使能组[4] 第3项〔4DCCB0；+200/+256〕【推断】
    unsigned char    abAggroAttr4_3      ; // +0x1D72 (7538) x1  属性对比较使能组[4] 第4项〔4DCCB0；+214/+270〕【推断】
    unsigned char    abAggroFlags17_0    ; // +0x1D73 (7539) x1  威胁特征位组[17] 首项〔4DCCB0：逐项 vt+776(i) 命中 +100；4A41C0 整拷 17 字节〕【推断】
    // ---- 区块 6：子类相位/资源对象槽区 ----
    unsigned char _unused_0x1D74      [232]; // +0x1D74..0x1E5B 未观测
    unsigned int     nCounterState       ; // +0x1E5C (7772) x1  反击态〔4DB480 变量名 nCounterState=*(this+7772)，值 1/2〕
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364） ----
    unsigned char _unused_0x1E60      [576]; // +0x1E60..0x209F 未观测
    unsigned int     nRideHostSlot       ; // +0x20A0 (8352) x1  骑乘/宿主槽〔通用偏移表 this+8352〕
    unsigned int     uPickupParam        ; // +0x20A4 (8356) x2  拾取参数槽〔4D94A0 写 uArg3〕【推断】
    unsigned int     pPickupInfo7        ; // +0x20A8 (8360) x5  拾取信息快照指针〔4D94A0：7 字节对象懒创建〕【推断】
    // ---- 区块 8：子类 AI 状态区（+8600+；相位/事件/特效槽） ----
    unsigned char _unused_0x20AC      [236]; // +0x20AC..0x2197 未观测
    unsigned int     nDistThreshold      ; // +0x2198 (8600) x1  距主人距离阈值〔5A9620：vt+684 距离 > 此值才行动〕【推断】
    unsigned int     uAI8604          ;    // +0x219C (8604) x1  【推断】子类AI相位槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int     uAI8608          ;    // +0x21A0 (8608) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int     uAI8612          ;    // +0x21A4 (8612) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int     uAI8616          ;    // +0x21A8 (8616) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned char    bAlarmFlag          ; // +0x21AC (8620) x2  警报/唤醒标志〔5A9100 态14 目标空时置1；置位即行动〕【推断】
    unsigned char _unused_0x21AD      [3]; // +0x21AD..0x21AF 未观测
    unsigned int     uPatrolGate          ; // +0x21B0 (8624) x1  【推断】巡视/指令许可门（5A96F0 读侧 +8624 非空 且 15% 概率发巡视指令）〔证据: va=005A96F0〕
    unsigned int     nPoolTime           ; // +0x21B4 (8628) x1  指挥计时戳〔5A8900 = clock_now；与 5A8C70 500ms 门同区〕【推断】
    unsigned char _unused_0x21B8      [4]; // +0x21B8..0x21BB 未观测
    unsigned int     pDollTarget         ; // +0x21BC (8636) x4  人偶目标槽〔5A9100 态14 写入；0=无目标，-1=哨兵〕【推断】
    unsigned int     uCastSlot8640          ; // +0x21C0 (8640) x2  【推断】施放/目标槽（5A9100 态14 清 0）〔证据: va=005A9100〕
    unsigned char _unused_0x21C4      [12]; // +0x21C4..0x21CF 未观测
    unsigned char    bAI8656          ;    // +0x21D0 (8656) x1  【推断】子类AI标记字节（5A82B0 清 0）〔证据: va=005A82B0〕
    unsigned char _unused_0x21D1      [7]; // +0x21D1..0x21D7 未观测
    unsigned char    bAI8664          ;    // +0x21D8 (8664) x1  【推断】子类AI相位槽（5A9100 态8 清 0）〔证据: va=005A9100〕
    unsigned char _unused_0x21D9      [3]; // +0x21D9..0x21DB 未观测
    unsigned int     nDollMode           ; // +0x21DC (8668) x1  人偶行为模式〔5A9620：1=常态攻击指令5；2=巡视 2% 指令1〕【推断】
};
#pragma pack(pop)

// 统计: 字段行 51 / 未命名保留 0 / 标【推断】34 / 末尾偏移 +0x21E0

