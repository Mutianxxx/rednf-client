// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNSwordman             主虚表槽位数: 333   字段数: 41
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名判定
// 置信度: 偏移/类型=二进制直证；语义名=证据推断（【推断】标注无直证者）
// 继承链: CNRDObject -> IRDCollisionObject -> IRDActiveObject -> IRDCharacter -> CNSwordman
// 依据: ①通用偏移表（this+120 动画对象 / +642..644 帧覆盖 / +6556 主状态镜像 / +7096..7104 影身计时 /
//        +7148 大状态 / +7252 目标 / +7772 反击态 / +8352..8364 拾取信息）②证据行 va
//        ③同族跨类印证 ④src 已精修函数头注释：职业族命名继承 CNFighter.h/CNMage.h/CNGunner.h（攻击参数面 7531..7596；能力槽 512..524；参数块 7152..7420）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNSwordman_Fields {
    // ---- 区块 1：继承基类区（通用偏移表；动画对象/帧同步/参数灌入/帧时刻覆盖） ----
    unsigned char _base_0x0000        [116]; // +0x0000..0x0073 继承基类区（见 IRDMonster.h / src/cnrd/*.h）
    unsigned int     pFxContainer        ; // +0x0074 (116) x2  特效容器对象（0x5F07A0 经此 +120/+124 取元素区间做动态转型遍历）【推断】（证据: va=005F07A0）
    unsigned int     pAnimObj            ; // +0x0078 (120) x7  基类动画对象指针（0x499020/0x499080 帧时刻同步宿主；全库通用 this+120）（证据: va=00499020）
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
    unsigned char _unused_0x0108      [124]; // +0x0108..0x0183 未观测
    float            fAtkCtxVal          ; // +0x0184 (388) x1  攻击上下文浮点值（0x5EE040 case11 写 sub_47EFD0(vt+1140/vt+1160 取参) 结果）【推断】（证据: va=005EE040）
    unsigned char _unused_0x0188      [4]; // +0x0188..0x018B 未观测
    unsigned int     uReflectCtx         ; // +0x018C (396) x1  反射上下文清零槽（0x5EE040 case11 写 0 后重建攻击上下文；同 case 播 SWD_REFLECT）【推断】（证据: va=005EE040）
    unsigned char _unused_0x0190      [48]; // +0x0190..0x01BF 未观测
    unsigned int     uReflectStage       ; // +0x01C0 (448) x1  反射阶段号（0x5EE040 case11：连击计数达 dword_7959FC 时写 2）【推断】（证据: va=005EE040）
    unsigned char _unused_0x01C4      [60]; // +0x01C4..0x01FF 未观测
    unsigned int     nAbilityId          ; // +0x0200 (512) x2  能力槽 id（0x4AF8E0 惰性初始化：==4 时用 vt+1176/vt+1180 重取两值）【基类字段】（证据: va=004AF8E0）
    unsigned char    bAbilityFlag        ; // +0x0204 (516) x1  能力槽标志字节（0x4AF8E0 由 vt+1180() 写入）【基类字段】（证据: va=004AF8E0）
    unsigned char _unused_0x0205      [3]; // +0x0205..0x0207 未观测
    unsigned int     nAbilityDur         ; // +0x0208 (520) x5  能力槽时长/基础值（0x4AF8E0：==-1 用 vt+1184 取初值；>0 按 (2.0−属性块+1292)×它修正）【基类字段】（证据: va=004AF8E0）
    unsigned int     fAbilityScale       ; // +0x020C (524) x2  能力槽浮点缩放（0x4AF8E0：==-4.0f 用 vt+1188 取初值；0x5E47A0 按倍率乘它）【基类字段】（证据: va=004AF8E0）
    unsigned char _unused_0x0210      [88]; // +0x0210..0x0267 未观测
    unsigned int     nReactionState      ; // +0x0268 (616) x3  受击反应态（0x5EFBD0 读此并排除 3/4/5 后才发全局事件；IRDActiveObject 定案 +616）（证据: va=005EFBD0）
    unsigned char _unused_0x026C      [22]; // +0x026C..0x0281 未观测
    unsigned char    bAttackEnable       ; // +0x0282 (642) x6  基类攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；IRDActiveObject 定案 +642）（证据: va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride      ; // +0x0284 (644) x5  基类帧时刻覆盖值（与 +0x282 成对；0x4E5C10 第四参）（证据: va=004E5C10）
    // ---- 区块 3：子类扩展槽区（语音槽组/参数面/相位联动） ----
    unsigned char _unused_0x0288      [6448]; // +0x0288..0x1BB7 未观测
    unsigned int     nStealthStart       ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻（0x4D5A90 影身计时三连写；clock_now(this+36)）【基类字段】（证据: va=004D5A90）
    unsigned int     nStealthDur         ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 按 1000×时长/+6656 折算剩余量）【基类字段】（证据: va=004D5A90）
    unsigned char    bStealthFlag        ; // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 置位时走折算；0x4D7F30 伪装态切换）【基类字段】（证据: va=004D5A90）
    // ---- 区块 4：主状态/目标/计时门区（大状态 7148 / 目标 7252） ----
    unsigned char _unused_0x1BC1      [43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nBigState           ; // +0x1BEC (7148) x2  大状态 ID（0x4DB480 反击判定 11/12→切 4；0x4D9000 白名单 / 0x4D9040 setter）（证据: va=004DB480）
    unsigned int     nParam2             ; // +0x1BF0 (7152) x1  0x5796C0 参数块写入槽（基类参数块 +4）【基类字段】（证据: va=005796C0）
    unsigned char    bParam3             ; // +0x1BF4 (7156) x1  0x5796C0 参数块写入字节（基类参数块 +8）【基类字段】（证据: va=005796C0）
    unsigned char _unused_0x1BF5      [259]; // +0x1BF5..0x1CF7 未观测
    unsigned int     map7416             ; // +0x1CF8 (7416) x1  键到值 map 起始（0x4B4EE0 在此插入/删除；键为资源/状态 id）【基类字段】（证据: va=004B4EE0）
    unsigned int     map7416End          ; // +0x1CFC (7420) x1  键到值 map 尾指针（0x4B4EE0 与 +7420 比较判命中）【基类字段】（证据: va=004B4EE0）
    // ---- 区块 7：拾取信息/扩展资源区（+8352..8364 拾取信息族） ----
    unsigned char _unused_0x1D00      [804]; // +0x1D00..0x2023 未观测
    unsigned int     nReflectT0          ; // +0x2024 (8228) x1  反射起手时间戳（0x5EE040 case11 写 clock_now(this+6560)；0x5EA970 同址清零）【推断】（证据: va=005EE040）
    unsigned char _unused_0x2028      [4]; // +0x2028..0x202B 未观测
    unsigned int     nReflectCnt         ; // +0x202C (8236) x3  反射/连击计数（0x5EE040 case11 自增，达表值 7959FC 时写 +448=2）（证据: va=005EE040）
    unsigned char _unused_0x2030      [24]; // +0x2030..0x2047 未观测
    unsigned int     nAbsorbCap          ; // +0x2048 (8264) x2  伤害吸收上限（0x5EE170：入伤 >= 本槽则钳到本槽并返 2；0x5EE010 置 100）（证据: va=005EE170）
    unsigned char    bAbsorbOn           ; // +0x204C (8268) x3  伤害吸收开关字节（0x5EE170 非 0 才走上限钳制；0x5EF3F0 命中无敌门后置 1）（证据: va=005EE170）
    unsigned char _unused_0x204D      [36]; // +0x204D..0x2070 未观测
    unsigned char    bImmune8305         ; // +0x2071 (8305) x3  无敌门 8305（0x5EF3F0 技能 7 达标时置 1；0x5EE170 非 0 即伤害无效化返 1；0x5EFBD0 后续发 27 号全局事件）（证据: va=005EF3F0）
    unsigned char _unused_0x2072      [106]; // +0x2072..0x20DB 未观测
    unsigned char    bImmune8412         ; // +0x20DC (8412) x3  无敌门 8412（0x5EF3F0 技能 47 达标时置 1；0x5EE170 非 0 即伤害无效化返 1；0x5EFBD0 后续发 10 号 setState 带参）（证据: va=005EF3F0）
    unsigned char _unused_0x20DD      [15]; // +0x20DD..0x20EB 未观测
    unsigned int     pBuffOverdriveObj   ; // +0x20EC (8428) x5  Buff 表现对象·过载（0x5F07A0 case38 懒创建 0x7C 字节对象，BuffIcon.img 帧 7 + 播 BUFF_OVERDRIVE）（证据: va=005F07A0）
    unsigned int     pBuffCongestionObj  ; // +0x20F0 (8432) x4  Buff 表现对象·气血（0x5F07A0 case40 懒创建 0x70 字节对象，BuffIcon.img 帧 12 + 播 BUFF_CONGESTION）（证据: va=005F07A0）
    unsigned int     pBuffGhostStepObj   ; // +0x20F4 (8436) x4  Buff 表现对象·鬼步（0x5F07A0 case18 懒创建 0x50 字节对象，BuffIcon.img 帧 20）（证据: va=005F07A0）
    unsigned char    bGhostStepFlag      ; // +0x20F8 (8440) x2  鬼步/隐身标志字节（0x5F07A0 case18 置 1 并播 G_GHOSTSTEP_DISAPPEAR；0x5EDFF0 复位清 0）（证据: va=005F07A0）
    unsigned char    bGhostStepFlag2     ; // +0x20F9 (8441) x1  鬼步联动标志字节 2（0x5EDFF0/0x5EDDC0 与 +8440 成对清零）【推断】（证据: va=005EDFF0）
    unsigned char _unused_0x20FA      [2]; // +0x20FA..0x20FB 未观测
    unsigned int     pStealObj           ; // +0x20FC (8444) x6  Buff 表现对象·夺取（0x5F07A0 case52 懒创建 0xBC 字节对象经 vt+148 配置；0x5EE040 case52 检其 vt+80 后调 vt+76(0) 释放）（证据: va=005F07A0）
    unsigned char _unused_0x2100      [72]; // +0x2100..0x2147 未观测
    unsigned int     pBuffCtx8520        ; // +0x2148 (8520) x2  Buff 上下文槽（0x5F07A0 case38 写 sub_47EF20 表值；0x5E6C50 按对象指针经 vtable[0](1) 释放；0x5EDFF0 清 0）【推断】（证据: va=005F07A0）
};
#pragma pack(pop)

// 统计: 字段行 41 / 未命名 0 / 标【推断】7 / 末尾偏移 +0x214C

