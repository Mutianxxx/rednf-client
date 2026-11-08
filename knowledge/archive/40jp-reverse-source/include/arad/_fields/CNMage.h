// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNMage   主虚表槽位数: 333
// 继承: CNMage -> IRDCharacter -> IRDActiveObject -> IRDCollisionObject -> CNRDObject
//        -> KGameMessenger -> KMessenger（基类段见 src/cnrd/*.h）
// 本类覆写 25 个槽（+0/+12/+16/+296/+300/+324/+332/+472/+496/+500/+504/+508/+512/+516
//   /+648/+904/+1020/+1152/+1164/+1208/+1296/+1300/+1304/+1316/+1328）。
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 f_XXXX 占位）
// 证据主源（本类 333 槽函数）:
//   +332 0x5DE690 法师每帧主状态机总入口（src/game/creature/expeller_guard.cpp:12566，1082 行）
//   +472 0x5E1000 法师技能总表巨型函数（src/combat/bigfunc_5E1000_sub_5E1000.cpp:20，13379 字节）
//   +516 0x5DD700 召唤物受击转发（expeller_guard.cpp:11764）
//   +344 0x4AF8E0 能力槽惰性初始化（src/game/rtti_core.cpp:11793）
//   +1300 0x5E0090 法师技能派生槽（src/combat/fighter_skills.cpp:18）
//   基类共享: 0x499020(+260)/0x499080/0x42A8D0/0x4D5A90(+1BB8 影身)/0x5796C0(+1BEC)
// ============================================================
#ifndef ARAD40JP_FIELDS_CNMAGE
#define ARAD40JP_FIELDS_CNMAGE

#include <stdint.h>

#pragma pack(push, 1)
struct CNMage_Fields {
    unsigned char _base_head[112]; // +0x0000..0x006F 继承自 CNRDObject/IRDCollisionObject/IRDActiveObject/IRDCharacter（见 src/cnrd/*.h；首个观测偏移之前）（不重复展开）
    // ---- 区块: 宿主组件与动画资源族（0x5DE690） ----
    unsigned int     pHostComp;       // +0x0070 (112) x3  va=005DE690 【推断】默认共享组件/宿主对象指针（0x5DE690 经 `*(this+112)+20` 取浮点判 |·|>=20.0 的距离门；CNRDObject__vmt3C 兜底）【基类字段】
    unsigned int     f_0074;          // +0x0074 (116) x1  va=005DE690 0x5DE690 读取槽（fld_74）
    unsigned int     pAnimObj;        // +0x0078 (120) x24 va=00499020 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】
    unsigned char _unused_007C[36]; // +0x007C..0x009F 未观测
    unsigned int     nPhaseArg;       // +0x00A0 (160) x2  va=005DE690 【推断】相位参数（0x5DE690: sub_4BA730(1, fld_2178, 0, -*(this+160)) 的入参源）
    unsigned char _unused_00A4[36]; // +0x00A4..0x00C7 未观测
    unsigned int     nMainState;      // +0x00C8 (200) x1  va=005DE690 主状态（0x5DE690: dword_8F7C04==this 且此槽 != 2 —— 与基类 +200 主状态同址，基类三层状态）【基类字段】
    unsigned char _unused_00CC[28]; // +0x00CC..0x00E7 未观测
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
    unsigned char _unused_0108[100]; // +0x0108..0x016B 未观测
    unsigned int     pAnimPool;       // +0x016C (364) x1  va=005DE690 ★ 场景动画池指针（0x5DE690 case 14 经 sub_431920 加载 FollowMeCast.ani；+384<0x10 时改用 this+108 内联）
    unsigned char _unused_0170[16]; // +0x0170..0x017F 未观测
    unsigned int     nAnimPoolCap;    // +0x0180 (384) x1  va=005DE690 【推断】动画池容量字段（0x5DE690 以 <0x10 择「内联 / 堆指针」的 SSO 容量判据，与 CNFighter +0x180 同法）
    // ---- 区块: 能力槽（状态时长）族（0x4AF8E0 惰性初始化；研究 §8 冻结时长） ----
    unsigned char _unused_0184[124]; // +0x0184..0x01FF 未观测
    unsigned int     nAbilityId;      // +0x0200 (512) x2  va=004AF8E0 ★ 能力槽 id（0x4AF8E0 惰性初始化: ==4 时用 vt+1176/vt+1180 重取两值）【基类字段】
    unsigned char    bAbilityFlag;    // +0x0204 (516) x1  va=004AF8E0 ★ 能力槽标志字节（0x4AF8E0 由 vt+1180() 写入）【基类字段】
    unsigned char _unused_0205[3]; // +0x0205..0x0207 未观测
    unsigned int     nAbilityDur;     // +0x0208 (520) x5  va=004AF8E0 ★ 能力槽时长/基础值（0x4AF8E0: ==-1 时用 vt+1184 取初值；>0 时按 (2.0−属性块+1292)×它修正；研究 §8 冻结时长用它在 hiteff_monster.cpp:6860 直证）【基类字段】
    unsigned int     fAbilityScale;   // +0x020C (524) x2  va=004AF8E0 ★ 能力槽浮点缩放（0x4AF8E0: ==-4.0f 时用 vt+1188 取初值；0x5E47A0/伤害管线按倍率乘它）【基类字段】
    // ---- 区块: 受击反应态与表现壳族（0x5DE690 / 0x5DD700） ----
    unsigned char _unused_0210[88]; // +0x0210..0x0267 未观测
    unsigned int     nReactionState;  // +0x0268 (616) x2  va=005DE690 ★ 受击反应态（0x5DE690 与 -1 比较判定解除；IRDActiveObject 定案 +616 三层状态）
    unsigned char _unused_026C[22]; // +0x026C..0x0281 未观测
    unsigned char    bAttackEnable;   // +0x0282 (642) x6  va=005DD700 攻击使能/表现壳开关（0x5DD700 读 !=0；基类定案 +642）【基类字段】
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride;  // +0x0284 (644) x5  va=005DD700 帧时刻覆盖值（0x5DD700 读）【基类字段】
    // ---- 区块: 施法对象族（0x5E0090） ----
    unsigned char _unused_0288[1434]; // +0x0288..0x0821 未观测
    int              pCaster;         // +0x0822 (2082) x1  va=005E0090 【推断】施法对象指针槽（0x5E0090 经 `pThis_822=(int*)(this+2082)` 后按 -5 相对索引扫 5 项喂 sub_4926A0）
    // ---- 区块: 大状态与变体族（0x5DE690 switch 总闸） ----
    unsigned char _unused_0826[4470]; // +0x0826..0x199B 未观测
    unsigned int     nBigState;       // +0x199C (6556) x21 va=005DE690 ★ 法师大状态 ID（0x5DE690 switch(this+6556) 总闸：0/7/8/10/12/14/18/19/20/21 分派）
    unsigned char _unused_19A0[84]; // +0x19A0..0x19F3 未观测
    unsigned int     nSubGate;        // +0x19F4 (6644) x1  va=005DE690 【推断】子门（0x5DE690: +8568!=-1 && +6644!=0 时走 sub_5DACE0）
    unsigned char _unused_19F8[448]; // +0x19F8..0x1BB7 未观测
    unsigned int     nStealthStart;   // +0x1BB8 (7096) x1  va=004D5A90 【推断】隐身/伪装窗口起始时刻（0x4D5A90 影身计时三连写）【基类字段】
    unsigned int     nStealthDur;     // +0x1BBC (7100) x1  va=004D5A90 【推断】隐身/伪装窗口时长 ms（0x4D5AC0 折算）【基类字段】
    unsigned char    bStealthFlag;    // +0x1BC0 (7104) x1  va=004D5A90 【推断】隐身/伪装开关字节【基类字段】
    unsigned char _unused_1BC1[43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nSubState;       // +0x1BEC (7148) x2  va=005796C0 大状态镜像槽（0x5796C0 写 this+7148；与 IRDActiveObject +7148 同址）【基类字段】
    unsigned int     nParam2;         // +0x1BF0 (7152) x1  va=005796C0 0x5796C0 写入槽（基类参数块 +4）【基类字段】
    unsigned char    bParam3;         // +0x1BF4 (7156) x1  va=005796C0 0x5796C0 写入字节（基类参数块 +8）【基类字段】
    unsigned char _unused_1BF5[259]; // +0x1BF5..0x1CF7 未观测
    unsigned int     map7416;         // +0x1CF8 (7416) x1  va=004B4EE0 键到值 map 起始（0x4B4EE0 在此插入/删除）【基类字段】
    unsigned int     map7416End;      // +0x1CFC (7420) x1  va=004B4EE0 键到值 map 尾指针（0x4B4EE0 与 +7420 比较判命中）【基类字段】
    unsigned char _unused_1D00[384]; // +0x1D00..0x1E7F 未观测
    unsigned int     nVariantSel;     // +0x1E80 (7808) x3  va=005DE690 ★ 变体选择（0x5DE690: +7808==1 分支）
    unsigned int     nSubStateA;      // +0x1E84 (7812) x2  va=005DE690 ★ 子状态 A（0x5DE690: +7812==0 分支）
    unsigned int     nSubStateB;      // +0x1E88 (7816) x1  va=005DE690 ★ 子状态 B（0x5DE690: +7816==11 判据）
    unsigned int     nSubStateC;      // +0x1E8C (7820) x1  va=005DE690 ★ 子状态 C（0x5DE690: +7820==-1 判据）
    unsigned char _unused_1E90[4]; // +0x1E90..0x1E93 未观测
    unsigned int     nSubStateD;      // +0x1E94 (7828) x1  va=005DE690 ★ 子状态 D（0x5DE690: +7828==0 判据）
    unsigned char _unused_1E98[132]; // +0x1E98..0x1F1B 未观测
    unsigned int     nSkillNo;        // +0x1F1C (7964) x1  va=005DE690 ★ 技能号（0x5DE690: ==30 时走 case 14 的 FollowMeCast 召集演出）
    // ---- 区块: 召唤与相位计时段族（0x5DE690 相位时钟块） ----
    unsigned char _unused_1F20[148]; // +0x1F20..0x1FB3 未观测
    unsigned int     pParamBlock;     // +0x1FB4 (8116) x2  va=005DE690 【推断】参数块指针（0x5DE690 经 sub_4842B0(dword_7958E8[v57], this+8116) 取得）（类型勘误：候选表 void 系取址式误判，按 4 字节占位）
    unsigned char _unused_1FB8[100]; // +0x1FB8..0x201B 未观测
    unsigned char    bCastFlag;       // +0x201C (8220) x4  va=005DE690 ★ 施法标志字节（0x5DE690: ==0 分支；0x5E1000/5F39F0 同址清零）
    unsigned char _unused_201D[7]; // +0x201D..0x2023 未观测
    unsigned char    f_2024;          // +0x2024 (8228) x1  va=005DE690 0x5DE690: !=0 条件字节
    // ---- 区块: 召唤物与技能上下文族（0x5DE690 / 0x5DD700） ----
    unsigned char _unused_2025[143]; // +0x2025..0x20B3 未观测
    unsigned int     nAddVal;         // +0x20B4 (8372) x2  va=005DE690 0x5DE690 累加值（fld_20B4，写入前读取）
    unsigned char    bSummonFlag;     // +0x20B8 (8376) x2  va=005DE690 ★ 召唤/挂件标志（0x5DE690: ==0 判据；0x5DD700 头注「this+8372 挂件存活时」全量收集召唤物）
    unsigned char _unused_20B9[19]; // +0x20B9..0x20CB 未观测
    unsigned int     nSummonVal;      // +0x20CC (8396) x1  va=005DE690 【推断】召唤数值槽（0x5DE690: ==17 且 clock_now(this+6560) 比较）
    unsigned char _unused_20D0[4]; // +0x20D0..0x20D3 未观测
    unsigned char    bPhaseGate;      // +0x20D4 (8404) x2  va=005DE690 0x5DE690: ==0 且 *(this+1...)+... 组合条件
    unsigned char _unused_20D5[23]; // +0x20D5..0x20EB 未观测
    unsigned int     pSkillCtx;       // +0x20EC (8428) x1  va=005DE690 【推断】技能上下文指针（0x5DE690 经 `*(this+8428)+148 >= 1` 取剩余次数门）
    unsigned char _unused_20F0[8]; // +0x20F0..0x20F7 未观测
    unsigned int     f_20F8;          // +0x20F8 (8440) x2  va=005DE690 0x5DE690: *(this+8440)!=0 门
    unsigned int     nCfgVal;         // +0x20FC (8444) x2  va=005DE690 0x5DE690: *(this+8444)!=-1 判据
    // ---- 区块: 相位时间戳族（0x5DE690 clock_now(this+6560) 比较对） ----
    unsigned char _unused_2100[56]; // +0x2100..0x2137 未观测
    unsigned char    f_2138;          // +0x2138 (8504) x3  va=005DE690 0x5DE690: ==0 判据字节
    unsigned char _unused_2139[3]; // +0x2139..0x213B 未观测
    unsigned int     nPhaseEndA;      // +0x213C (8508) x2  va=005DE690 ★ 相位段 A 结束时刻（0x5DE690: clock_now(this+6560) >= +8508 + 150 门）
    unsigned int     nPhaseRefA;      // +0x2140 (8512) x1  va=005DE690 0x5DE690: sub_432E50(*(this+8512)) 取值
    unsigned int     nPhaseValA;      // +0x2144 (8516) x1  va=005DE690 0x5DE690 相位值 A
    unsigned char    bUseCtx;         // +0x2148 (8520) x2  va=005DE690 0x5DE690: ==0 且 *(this+1...)+... 组合
    unsigned char _unused_2149[11]; // +0x2149..0x2153 未观测
    unsigned int     nPhaseValB;      // +0x2154 (8532) x3  va=005DE690 0x5DE690 相位值 B（fld_2154）
    unsigned char _unused_2158[4]; // +0x2158..0x215B 未观测
    unsigned int     nPhaseStamp;     // +0x215C (8540) x4  va=005DE690 ★ 相位时间戳（0x5DE690: = clock_now(this+6560)，配合 +2164 的 +200ms 门）
    unsigned int     nFxCtx;          // +0x2160 (8544) x1  va=005DE690 0x5DE690 经 sub_4939E0(*(this+8544), 1) 消费
    unsigned int     nPhaseEndB;      // +0x2164 (8548) x2  va=005DE690 ★ 相位段 B 结束时刻（0x5DE690: clock_now >= +8548 + 200 门）
    // ---- 区块: 相位组与渐变族（0x5DE690 clock_now(this+36) 比较对） ----
    unsigned char _unused_2168[16]; // +0x2168..0x2177 未观测
    unsigned int     nPhaseGroupIdx;  // +0x2178 (8568) x4  va=005DE690 ★ 相位组索引（0x5DE690: +8568!=-1 门；经 sub_5DA1E0 映射组号后喂 sub_4BA730 广播）
    unsigned int     nPhaseElapsed;   // +0x217C (8572) x7  va=005DE690 ★ 相位已历时（0x5DE690: clock_now(this+36) - +8572，打包经 sub_431230 上报）
    unsigned int     nFadeAlpha;      // +0x2180 (8576) x3  va=005DE690 ★ 渐变 alpha（0x5DE690: sub_42B420(255,220,…,100) 插值 → vt+252(0/1, alpha) 双通道）
    unsigned int     nPhaseStage;     // +0x2184 (8580) x9  va=005DE690 ★ 相位阶段号（0x5DE690: 0→1→2 状态推进，驱动 sub_4BA730 与渐变）
    unsigned char    bPhaseDone;      // +0x2188 (8584) x1  va=005DE690 0x5DE690: !=0 判据字节
};
#pragma pack(pop)

// 统计: 字段行 63 / 未命名 4 / 标【推断】11 / 末尾偏移 +0x2189

#endif
