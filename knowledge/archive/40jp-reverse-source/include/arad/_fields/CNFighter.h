// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNFighter   主虚表槽位数: 226
// 继承: CNFighter -> IRDCharacter -> IRDActiveObject -> IRDCollisionObject -> CNRDObject
//        -> KGameMessenger -> KMessenger（基类段见 src/cnrd/*.h）
// 本类仅覆写 8 个槽（+0/+300/+332/+344/+472/+500/+504/+512），其余沿用基类实现。
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 f_XXXX 占位）
// 证据主源（本类 226 槽函数）:
//   +472 0x5EA970 技能基础与投技巨型函数（src/combat/bigfunc_5EA970_sub_5EA970.cpp:20，10856 字节）
//   +344 0x5E47A0 CNFighter__vmt158 攻击倍率门（src/combat/fighter_skills.cpp:918）
//   +332 0x5E78C0 转职/升级演出与逐帧 tick（src/combat/bigfunc_5E78C0_sub_5E78C0.cpp:32）
//   基类共享: 0x499020(+260 时刻同步)/0x499080/0x42A8D0(基类vmt11C)/0x4E5C10(+612)
// ============================================================
#ifndef ARAD40JP_FIELDS_CNFIGHTER
#define ARAD40JP_FIELDS_CNFIGHTER

#include <stdint.h>

#pragma pack(push, 1)
struct CNFighter_Fields {
    unsigned char _base_head[112]; // +0x0000..0x006F 继承自 CNRDObject/IRDCollisionObject/IRDActiveObject/IRDCharacter（见 src/cnrd/*.h；前 0x70 字节）（不重复展开）
    // ---- 区块: 宿主组件与动画资源族（0x5EA970 / 0x5E47A0） ----
    unsigned int     pHostComp;       // +0x0070 (112) x3  va=005EA970 【推断】默认共享组件/宿主对象指针（0x5EA970 经此 +16 取浮点做位移判定；CNRDObject__vmt3C 兜底取 this+112）【基类字段】
    unsigned char _unused_0074[4]; // +0x0074..0x0077 未观测
    unsigned int     pAnimObj;        // +0x0078 (120) x7  va=00499020 动画对象指针（0x499020 帧时刻同步宿主；基类同址）【基类字段】
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
    // ---- 区块: 动画池与攻击上下文族（0x5EA970 vt+344/vt+388 对） ----
    unsigned char _unused_0108[100]; // +0x0108..0x016B 未观测
    unsigned int     pAnimPool;       // +0x016C (364) x8  va=005EA970 ★ 场景动画池指针（0x5EA970 经 sub_431920 由此加载 RoarStun/EnergyCharge/ClosePunchExecute 等 .ani；+384<0x10 时改用 this+108 内联）
    unsigned char _unused_0170[16]; // +0x0170..0x017F 未观测
    unsigned int     nAnimPoolCap;    // +0x0180 (384) x8  va=005EA970 【推断】动画池容量字段（0x5EA970 反复以 <0x10 择「内联缓冲 / 堆指针」，即 SSO 容量判据）
    float            fAtkCtxVal;      // +0x0184 (388) x13 va=005EA970 【推断】攻击上下文浮点值（0x5EA970 多处写 *(float*)(this+388) = sub_47EFD0 计算结果；注意与「vt+388 虚槽调用」是两回事，同号纯属巧合 —— 本槽是数据字段，由 vt+388 系列函数写入）
    unsigned char _unused_0188[4]; // +0x0188..0x018B 未观测
    unsigned int     nSkillParamIdx;   // +0x018C (396) x1  va=005EA970 ★ 技能参数索引槽（0x5EA970 case19/case23 起手清零后重取；★同址 0x509C90 怪物解析器按"[hit recovery]"标签写 +396/+400 对 —— 本类为技能/受击恢复量透传槽）【推断】
    unsigned char _unused_0190[24]; // +0x0190..0x01A7 未观测
    float            f_AtkRateX10;    // +0x01A8 (424) x1  va=005EA970 【推断】攻击倍率 ×10 换算（0x5EA970: *(this+424)=(int)v44*0.1，v44 来自 sub_47EF20 数据表读数）
    unsigned char _unused_01AC[8]; // +0x01AC..0x01B3 未观测
    unsigned int     nAtkTableVal;    // +0x01B4 (436) x1  va=005EA970 【推断】攻击数据表取值（0x5EA970 由 sub_47EF20(3,...) 写 +436）
    unsigned char _unused_01B8[12]; // +0x01B8..0x01C3 未观测
    unsigned int     nAtkRollVal;     // +0x01C4 (452) x1  va=005EA970 【推断】攻击计算中间值（0x5EA970 由 sub_47EF20(0,...) 写 +452）
    unsigned int     f_01C8;          // +0x01C8 (456) x2  【保留占位】仅见写（case8/case17 由 sub_47EF20 读表写入 +456，无读侧消费点）〔证据: va=005EA970〕
    float            f_AccDmg;        // +0x01CC (460) x2  va=005EA970 【推断】累积量（0x5EA970: *(this+460) = Block + *(this+460) 自累加；passive_object 同族累加）
    unsigned int     f_01D0;          // +0x01D0 (464) x1  【保留占位】仅见复位（5EA970 写 -998637568=-1000.0f 位型初值，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_01D4[56]; // +0x01D4..0x020B 未观测
    float            f_DmgScale;      // +0x020C (524) x2  va=005E47A0 ★ 伤害缩放中间量（0x5E47A0: *(this+524) = *(this+8460) * *(this+524)，+8460 为倍率）【基类字段】
    unsigned char _unused_0210[28]; // +0x0210..0x022B 未观测
    unsigned int     nGrabAnimBase;   // +0x022C (556) x12 va=005EA970 ★ 投技/抓取动画偏移基（0x5EA970 反复 vt+344(*(this+556)+N)：N∈{304,456,760,912,1368,1520} 为阶段动画偏移）
    unsigned char _unused_0230[82]; // +0x0230..0x0281 未观测
    unsigned char    bAttackEnable;   // +0x0282 (642) x5  va=004E5C10 攻击使能/表现壳开关（基类定案 +642；0x4E5C10）【基类字段】
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride;  // +0x0284 (644) x4  va=004E5C10 帧时刻覆盖值（0x4E5C10）【基类字段】
    // ---- 区块: 技能参数子上下文族（0x5EA970 经 *(this+6216)+N 取参） ----
    unsigned char _unused_0288[5568]; // +0x0288..0x1847 未观测
    unsigned int     pSubCtx;         // +0x1848 (6216) x15 va=005EA970 ★ 技能参数/子上下文指针（0x5EA970 经 *(this+6216)+N 取参喂 vt+196 应用帧：N∈{0,4,12,16,20,48,52,64}）
    // ---- 区块: 大状态与速率基准族（0x5EA970 switch 总闸） ----
    unsigned char _unused_184C[336]; // +0x184C..0x199B 未观测
    unsigned int     nBigState;       // +0x199C (6556) x1  va=005EA970 ★ 角色大状态 ID（0x5EA970 switch 总闸；IRDActiveObject +6556 定案）
    unsigned char _unused_19A0[92]; // +0x19A0..0x19FB 未观测
    unsigned int     nRateNum;        // +0x19FC (6652) x1  va=005EA970 【推断】速率分子（0x5EA970: 2 * *(this+6652) 作 vt+888 入参）
    unsigned int     nRateDen;        // +0x1A00 (6656) x2  va=005EA970 【推断】速率分母/基准（0x5EA970: 2 * *(this+6652) / *(this+6656)）
    unsigned char _unused_1A04[232]; // +0x1A04..0x1AEB 未观测
    unsigned int     nSkillCtxVal;    // +0x1AEC (6892) x1  【推断】技能上下文取值（第三重 case6 起跳预备读；0 则经 vt+1140(17) 重取）〔证据: va=005EA970〕
    unsigned int     nTickCount;      // +0x1AF0 (6896) x1  va=005EA970 【推断】计数器自增（0x5EA970: ++*(this+6896)）
    // ---- 区块: 抓取/投技分支族（0x5EA970 case 10/12/16/17/19/20） ----
    unsigned char _unused_1AF4[908]; // +0x1AF4..0x1E7F 未观测
    unsigned int     nStyleSel;       // +0x1E80 (7808) x7  va=005EA970 ★ 风格/分支选择（0x5EA970 case 10 反复 ==0/==1 选资源与动画分支）
    unsigned int     nSubStateA;      // +0x1E84 (7812) x3  va=005EA970 ★ 子状态 A（0x5EA970: +7812==1 进入段；0x5DE690 同址大状态判据）
    unsigned int     nSubStateB;      // +0x1E88 (7816) x4  va=005EA970 ★ 子状态 B（0x5EA970: ==12/16/49 三值分派；==16 → vt+1160(16)+sub_47DCD0）
    int              nGrabW;          // +0x1E8C (7820) x1  va=005EA970 【推断】抓取宽度（0x5EA970: +7820 /= 2）
    int              nGrabH;          // +0x1E90 (7824) x1  va=005EA970 【推断】抓取高度（与 +7820 成对折半）
    unsigned char _unused_1E94[136]; // +0x1E94..0x1F1B 未观测
    unsigned int     nSkillNo;        // +0x1F1C (7964) x1  va=005EA970 ★ 技能号（0x5EA970 case 14: switch(*(this+7964)) 176/... 分派技能语音与效果）
    // ---- 区块: 抓取参数与对象族 ----
    unsigned char _unused_1F20[248]; // +0x1F20..0x2017 未观测
    unsigned int     nAtkActionType;  // +0x2018 (8216) x4  【推断】攻击动作类型（case8 由 pArg3[1][1] 写；==46 → FT_HAMMER_KICK；!=-1 触发 vt+1328）〔证据: va=005EA970〕
    unsigned int     nGrabTargetSel;  // +0x201C (8220) x3  va=005EA970 ★ 抓取目标选择（0x5EA970: *(this+8220)=结果，==1/==2 走两套 vt+1160/vt+1140 取参）
    unsigned int     f_2020;          // +0x2020 (8224) x1  【保留占位】仅见复位（case12 清零；复位族写 -1 哨兵，无读侧消费点）〔证据: va=005EA970〕
    unsigned char    bGrabFlag;       // +0x2024 (8228) x1  va=005EA970 0x5EA970 清零字节槽
    unsigned char _unused_2025[3]; // +0x2025..0x2027 未观测
    unsigned int     nGrabTable;      // +0x2028 (8232) x1  va=005EA970 【推断】抓取数据表读数（0x5EA970 由 sub_47EF20(0,...) 写 +8232）
    unsigned char _unused_202C[4]; // +0x202C..0x202F 未观测
    unsigned int     nParamCnt;       // +0x2030 (8240) x3  va=005EA970 ★ 抓取参数个数（0x5EA970: *(this+8240)=v259，作 pArg3 索引）
    unsigned int     nVariantSel;     // +0x2034 (8244) x6  va=005EA970 ★ 变体选择（0x5EA970: +8244==1 && +8248==15 特例）
    unsigned int     nVariantVal;     // +0x2038 (8248) x3  va=005EA970 ★ 变体值（0x5EA970 与 +8244 配对判定）
    unsigned int     nParam2;         // +0x203C (8252) x2  va=005EA970 抓取参数元组 [1]（0x5EA970 由 pArg3[1][2] 写）
    unsigned int     nParam3;         // +0x2040 (8256) x1  va=005EA970 抓取参数元组 [2]（由 pArg3[1][3] 写）
    unsigned int     nPhaseA;         // +0x2044 (8260) x2  va=005EA970 ★ 相位值 A（0x5EA970: 与 +8244 配对，==4 特例）
    unsigned int     nPhaseB;         // +0x2048 (8264) x3  va=005EA970 ★ 相位值 B（0x5EA970: +8248==15 组合）
    unsigned int     nParamArr;       // +0x204C (8268) x4  va=005EA970 ★ 抓取参数数组基址（0x5EA970: pThis_204C=(this+8268)，元素 4 字节）
    unsigned int     pAnimPool2;      // +0x2050 (8272) x2  va=005EA970 【推断】第二动画池指针（0x5EA970 写 pThis_6C2，配合 +204C 数组）
    unsigned char    f_2054;          // +0x2054 (8276) x1  【保留占位】仅见复位（FT_SAJAHU_CAST 收尾清 0，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_2055[3]; // +0x2055..0x2057 未观测
    unsigned int     pStatusObj;      // +0x2058 (8280) x4  va=005EA970 【推断】状态/属性对象指针（0x5EA970: +8280==0 时经 vt+588 创建）
    unsigned int     nGrabSkillNo;    // +0x205C (8284) x3  【推断】抓取技能号（case18 写 pArg3[1][0]；读侧 9/18/49 三值分派动画与参）〔证据: va=005EA970〕
    unsigned int     nGrabDataVal;    // +0x2060 (8288) x3  【推断】抓取数据值（读作累加基：sub_47EF20 读表结果 += 本槽）〔证据: va=005EA970〕
    unsigned char    bModeFlag;       // +0x2064 (8292) x2  va=005EA970 0x5EA970 条件字节（非 0 走分支）
    unsigned char _unused_2065[3]; // +0x2065..0x2067 未观测
    unsigned int     nOffsetVal;      // +0x2068 (8296) x1  va=005EA970 0x5EA970 写 -250（【推断】偏移/延迟值）
    // ---- 区块: 抱人对象与坐标族（0x5EA970 case 19） ----
    unsigned int     pHoldObj;        // +0x206C (8300) x28 va=005EA970 ★ 被擒/被抱对象指针（0x5EA970 反复 *(this+8300) 调其 vt+308/192/124/136/140/560/564/596）
    unsigned int     nHoldPosX;       // +0x2070 (8304) x4  va=005EA970 抱人坐标 X（0x5EA970 case 19 读 +8304 兜底写目标位）
    unsigned int     nHoldPosY;       // +0x2074 (8308) x4  va=005EA970 抱人坐标 Y（读 +8308）
    unsigned int     nHoldPosZ;       // +0x2078 (8312) x4  va=005EA970 抱人坐标 Z（读 +8312）
    unsigned int     nHoldSrc;        // +0x207C (8316) x4  va=005EA970 抱人朝向/源对象（0x5EA970 读 +8316 经 sub_432E50 转换）
    unsigned int     pHoldHost;       // +0x2080 (8320) x6  va=005EA970 【推断】抱人宿主/锚（0x5EA970 收尾 *(this+8320) 调 vt+76(0)）
    unsigned char    bHoldMode;       // +0x2084 (8324) x7  va=005EA970 ★ 抱人模式字节（0x5EA970: !=0 选 18 号参数否则 9 号 → vt+1160）
    unsigned char    bSubMode;        // +0x2085 (8325) x6  va=005EA970 ★ 抱人子模式（0x5EA970: !=0 时按 vt+192()/10 算目标 X）
    unsigned char    f_2086;          // +0x2086 (8326) x1  【保留占位】仅见复位（case19 抓取初始化批量清零，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_2087[1]; // +0x2087..0x2087 未观测
    unsigned int     f_2088;          // +0x2088 (8328) x1  【保留占位】仅见复位（case19 抓取初始化批量清零，无读侧消费点）〔证据: va=005EA970〕
    unsigned char    f_208C;          // +0x208C (8332) x1  【保留占位】仅见复位（case19 抓取初始化批量清零，无读侧消费点）〔证据: va=005EA970〕
    unsigned char    f_208D;          // +0x208D (8333) x1  【保留占位】仅见复位（case19 抓取初始化批量清零，无读侧消费点）〔证据: va=005EA970〕
    unsigned char    bPairOk;         // +0x208E (8334) x3  va=005EA970 0x5EA970 组合条件（+8324 && +8334）
    unsigned char _unused_208F[1]; // +0x208F..0x208F 未观测
    unsigned int     pVtStack;        // +0x2090 (8336) x2  va=005EA970 0x5EA970: pThis_2090=(this+8336)，2 次 vt+208 入参
    // ---- 区块: 动画资源句柄与附属物族 ----
    unsigned int     pAnimA;          // +0x2094 (8340) x1  va=005EA970 【推断】动画对象 A（0x5EA970 写 RoarStun2.ani 句柄）
    unsigned int     nRideMode;       // +0x2098 (8344) x2  【推断】骑乘模式（case20 写 pArg3[1][0]；读侧 ==1 为维持支）〔证据: va=005EA970〕
    unsigned int     nPhaseParity;    // +0x209C (8348) x3  va=005EA970 ★ 相位奇偶（0x5EA970: +8348 % 2 != 0 分支）
    unsigned int     nVtRet;          // +0x20A0 (8352) x1  va=005EA970 0x5EA970 写入槽（sub_47E9D0 结果）
    unsigned int     pHoldTarget;     // +0x20A4 (8356) x14 va=005EA970 ★ 抱人目标对象（0x5EA970 反复读 *(this+8356) 调其 vt+308/560/564/612，用后清零）
    unsigned char    bHoldClear;      // +0x20A8 (8360) x1  va=005EA970 0x5EA970 清零字节
    unsigned char _unused_20A9[3]; // +0x20A9..0x20AB 未观测
    unsigned int     nCoordA;         // +0x20AC (8364) x2  va=005EA970 0x5EA970 读 +8364 作 vt+112 入参三元组首项
    unsigned int     nCoordB;         // +0x20B0 (8368) x2  va=005EA970 同三元组第 2 项（+8368）
    unsigned int     nDiffVal;        // +0x20B4 (8372) x4  va=005EA970 0x5EA970: *(this+8372) = v129 - v130（差值写入）
    unsigned char    pFxObjB;         // +0x20B8 (8376) x1  【推断】特效/技能对象B（swordman_skills 读后经 sub_42AF90/sub_657740 释放）〔证据: va=005EA970〕
    unsigned char    f_20B9;          // +0x20B9 (8377) x1  【保留占位】仅见复位（case10 能量弹子型收尾清 0，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_20BA[2]; // +0x20BA..0x20BB 未观测
    unsigned int     pAnimC;          // +0x20BC (8380) x8  va=005EA970 【推断】动画对象 C（vt+208 调用 *(this+8380)）
    unsigned char    f_20C0;          // +0x20C0 (8384) x2  【保留占位】仅见复位（EnergyCharge/ENERGYING 分支清 0，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_20C1[3]; // +0x20C1..0x20C3 未观测
    unsigned int     pAnimD;          // +0x20C4 (8388) x4  va=005EA970 【推断】动画对象 D（vt+208 调用 *(this+8384)）
    unsigned char    f_20C8;          // +0x20C8 (8392) x1  【保留占位】仅见复位（EnergyBallShoot 分支清 0，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_20C9[3]; // +0x20C9..0x20CB 未观测
    unsigned int     nNameLookup;     // +0x20CC (8396) x1  va=005EA970 0x5EA970 经 vt+1172(this,...) 查名（技能名/id 换算）
    unsigned int     pAppendage;      // +0x20D0 (8400) x1  va=005EA970 ★ 附属物/状态组件指针（0x5EA970 非 0 且其 vt+80 通过时执行加算分支）
    unsigned int     pFxObjD;         // +0x20D4 (8404) x1  【推断】特效/技能对象D（5F39F0/swordman_skills 取址调 vt+208；expeller 读 ==0 门）〔证据: va=005EA970〕
    unsigned int     pRoplingObj;     // +0x20D8 (8408) x3  【推断】抓取挂接对象（FT_ROPLING 惰性 new 0x68 sub_5E4FC0；读侧 ==0 才建）〔证据: va=005EA970〕
    unsigned int     pAnimE;          // +0x20DC (8412) x4  va=005EA970 【推断】动画对象 E（vt+208 调用 *(this+8412)）
    unsigned char _unused_20E0[4]; // +0x20E0..0x20E3 未观测
    unsigned int     pVecBegin;       // +0x20E4 (8420) x2  【推断】对象数组 begin（case22 读边界 for 遍历后 j__free）〔证据: va=005EA970〕
    unsigned int     pVecEnd;         // +0x20E8 (8424) x1  【推断】对象数组 end（case22 读遍历边界；释放后清零）〔证据: va=005EA970〕
    unsigned int     pVecCap;         // +0x20EC (8428) x1  【推断】对象数组 cap（case22 释放后三槽清零之尾）〔证据: va=005EA970〕
    unsigned int     pBuffObjA;       // +0x20F0 (8432) x1  【推断】Buff 挂件A（swordman case 读侧 ==0 惰性 new 0x70 sub_5EE850）〔证据: va=005EA970〕
    unsigned char    pBuffObjB;       // +0x20F4 (8436) x1  【推断】Buff 挂件B（swordman case 读侧 ==0 惰性 new 0x50 sub_4B1030）〔证据: va=005EA970〕
    unsigned char    f_20F5;          // +0x20F5 (8437) x1  【保留占位】仅见复位（case17 收尾清 0，无读侧消费点）〔证据: va=005EA970〕
    // ---- 区块: 技能门与倍率组件族（0x5EA970 / 0x5E47A0） ----
    unsigned char _unused_20F6[6]; // +0x20F6..0x20FB 未观测
    unsigned int     nSkillGate;      // +0x20FC (8444) x5  va=005EA970 ★ 0x5EA970: nArg2!=21 && nArg2!=6 && *(this+8444)>0 门
    unsigned int     nFinishVal;      // +0x2100 (8448) x1  【推断】收招数据值（第三重 case6 由 sub_47EF20(17,..) 读表写；expeller 读并释放）〔证据: va=005EA970〕
    unsigned char _unused_2104[4]; // +0x2104..0x2107 未观测
    unsigned int     pAtkRateObj;     // +0x2108 (8456) x1  va=005E47A0 ★ 攻击倍率组件（0x5E47A0: 非 0 且其 vt+80 通过 → *(this+524) *= *(this+8460)）
    float            f_AtkRate;       // +0x210C (8460) x1  va=005E47A0 ★ 攻击倍率浮点（0x5E47A0: *(float*)(this+8460) 作 +524 乘数；默认 1.0f=1065353216）
    unsigned char _unused_2110[4]; // +0x2110..0x2113 未观测
    unsigned int     pSkillObj;       // +0x2114 (8468) x1  va=005EA970 【推断】技能对象指针（0x5EA970 读 *(this+8468)，非 0 时经 vt+64 写 +40）
    unsigned int     nFinishFlag;     // +0x2118 (8472) x3  【推断】收束标志（读侧 ==1 → sub_5E6640 收束例程）〔证据: va=005EA970〕
    unsigned char    bFinishFlag;     // +0x211C (8476) x1  【推断】收束门字节（0x5E78C0 置位；复位族清）〔证据: va=005EA970〕
    unsigned char    f_211D;          // +0x211D (8477) x1  【保留占位】仅见复位（case19 收尾清 0，无读侧消费点）〔证据: va=005EA970〕
    unsigned char _unused_211E[2]; // +0x211E..0x211F 未观测
    unsigned int     pAtkObj;         // +0x2120 (8480) x3  【推断】攻击挂接对象（case19 读侧 ==0 惰性 new 并 vt+56 挂接）〔证据: va=005EA970〕
    unsigned char _unused_2124[12]; // +0x2124..0x212F 未观测
    unsigned int     nChargeState;    // +0x2130 (8496) x3  【推断】魔能充能态（case26 读：0 → sub_4BA730 充能；1 → 回挂 +8512 动画）〔证据: va=005EA970〕
    unsigned int     nChargeTime;     // +0x2134 (8500) x4  【推断】充能计时（读侧 >= dword_9B9348 → 收束 vt+284）〔证据: va=005EA970〕
    unsigned int     f_2138;          // +0x2138 (8504) x1  【保留占位】仅见写（case26 写 -200 延迟值，与 +2068 同法；无读侧消费点）〔证据: va=005EA970〕
    unsigned int     f_213C;          // +0x213C (8508) x1  【保留占位】仅见复位（case26 清零，无读侧消费点）〔证据: va=005EA970〕
    unsigned int     pAnimF;          // +0x2140 (8512) x4  va=005EA970 【推断】动画对象 F（vt+208 调用 *(this+8512)）
    unsigned int     f_2144;          // +0x2144 (8516) x1  【保留占位】仅见复位（case26 清零，无读侧消费点）〔证据: va=005EA970〕
};
#pragma pack(pop)

// 统计: 字段行 111 / 未命名保留 16 / 标【推断】43 / 末尾偏移 +0x2148

#endif
