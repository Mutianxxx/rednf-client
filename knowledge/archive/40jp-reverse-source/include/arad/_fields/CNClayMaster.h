// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNClayMaster       主虚表槽位数: 329   字段数: 68
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注）
// 继承: IRDCollisionObject → IRDCollisionObject → CNRDObject → CNRDObject → KGameMessenger → KMessenger
// 依据: 通用偏移表（本表实命中: 7148 大状态、7256 光环对象、8352 骑乘宿主、7531..7596 攻击/分身参数面、8600..8700 子类AI状态区）
//       + 证据行函数头注释（src 搜 va）+ 同族跨类印证（goblin_fox/tau_golem/dragonman/missing_monster）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；
//       0x2198 起为本类子类 AI 状态区（this+8600 起）
// ============================================================
#pragma once
#include <stdint.h>
#pragma pack(push, 1)
struct CNClayMaster_Fields {
    unsigned char _base_0x0000[73]; // +0x0000..0x0048 继承基类未展开（见 src/cnrd/*.h 与 docs/14）

    // ---- 区块 1：基类公共（帧同步 / 参数灌入 / 动画对象；继承 CNRDObject 段） ----
    char            szNameBuf;                     // +0x0049 (73) x1  名字缓冲 SSO 首字节〔4DE410：名称模板 sprintf 读此〕；〔≙字节 292〕〔证据: va=004DE410〕
    unsigned char _unused_004A[46];
    unsigned int    pAnimObj;                      // +0x0078 (120) x7  动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕〔证据: va=00499020〕
    unsigned char _unused_007C[108];
    unsigned char   bSyncSwitch;                   // +0x00E8 (232) x2  【推断】时刻同步开关〔499020：由开转关时推进帧时刻〕〔证据: va=00499020〕
    unsigned char _unused_00E9[3];
    unsigned int    nSyncArgA;                     // +0x00EC (236) x1  【推断】同步参数A〔499020 写 nArg3〕〔证据: va=00499020〕
    unsigned int    nSyncArgB;                     // +0x00F0 (240) x1  【推断】同步参数B〔499020 写 nArg4〕〔证据: va=00499020〕
    float           fSyncValue;                    // +0x00F4 (244) x4  【推断】浮点同步值〔499080 浮点版；vmt114 非零判定〕〔证据: va=00499080〕
    unsigned char   bParamSlotA;                   // +0x00F8 (248) x1  【推断】四参灌入槽A〔CNRDObject vmt11C 批量写 +248..+260〕〔证据: va=0042A8D0〕
    unsigned char _unused_00F9[3];
    unsigned int    nParamSlotB;                   // +0x00FC (252) x1  【推断】四参灌入槽B〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char   bParamSlotC;                   // +0x0100 (256) x1  【推断】四参灌入槽C〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char _unused_0101[3];
    unsigned int    nParamSlotD;                   // +0x0104 (260) x1  【推断】四参灌入槽D〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char _unused_0108[378];

    // ---- 区块 2：帧时刻覆盖与拾取坐标（基类） ----
    unsigned char   bFrameOverride;                // +0x0282 (642) x5  帧时刻覆盖开关〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0283[1];
    unsigned int    nFrameOverrideTime;            // +0x0284 (644) x4  覆盖帧时刻〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0288[20];
    unsigned int    nPickupXCache;                 // +0x029C (668) x1  【推断】拾取目标坐标缓存〔4D94A0 将 +8352 写入此槽〕〔证据: va=004D94A0〕
    unsigned int    nPickupValid;                  // +0x02A0 (672) x1  【推断】拾取坐标有效标志〔4D94A0 置 1〕〔证据: va=004D94A0〕
    unsigned char _unused_02A4[5880];

    // ---- 区块 3：动作资源 / 语音参数 / 影身计时 / 大状态（基类） ----
    unsigned int    nBigStateMirror;               // +0x199C (6556) x2  主状态镜像〔通用偏移表 this+6556〕〔证据: va=005A9100〕
    unsigned char _unused_19A0[536];
    unsigned int    nInvisibleStart;               // +0x1BB8 (7096) x1  【推断】影身计时-起始〔4D5A90 = clock_now(this+36)〕〔证据: va=004D5A90〕
    unsigned int    nInvisibleDur;                 // +0x1BBC (7100) x1  【推断】影身计时-时长ms〔4D5A90 nArg2〕〔证据: va=004D5A90〕
    unsigned char   bInvisibleSwitch;              // +0x1BC0 (7104) x1  【推断】影身开关字节〔4D5A90 pszArg3〕〔证据: va=004D5A90〕
    unsigned char _unused_1BC1[43];
    unsigned int    nBigState;                     // +0x1BEC (7148) x1  大状态〔4DB480 本文件变量名 nBigState=*(this+7148)；通用表〕〔证据: va=004DB480〕
    unsigned char _unused_1BF0[100];
    unsigned int    pLinkSlot7252;                 // +0x1C54 (7252) x2  【推断】关联对象/主人引用〔5A9620 检 vt+776 关联体；5F150 置 0 清链〕〔证据: va=005A97A0〕
    unsigned int    pAuraObject;                   // +0x1C58 (7256) x1  光环对象槽〔通用偏移表 this+7256；5A020/5A12C0/5A8900 交 ·0x64BDF0 重建〕〔证据: va=005A8900〕
    unsigned char _unused_1C5C[260];

    // ---- 区块 4：攻击/分身参数面 7531..7596（复位族 + 档位配置族交叉直证；= 4A41C0 配置块副本） ----
    unsigned int    uCfgWord0;                     // +0x1D60 (7520) x1  【推断】配置块首字〔4A41C0 48+字节整块拷贝 this+7520 区〕〔证据: va=004A41C0〕
    unsigned int    uCfgWord1;                     // +0x1D64 (7524) x1  【推断】配置块第2字〔4A41C0〕〔证据: va=004A41C0〕
    unsigned char   bRetargetGate;                 // +0x1D68 (7528) x1  【推断】目标重选门〔4E1BE0 门：·this+7528 标志〕〔证据: va=004A41C0〕
    unsigned char   bCounterHookSw;                // +0x1D69 (7529) x2  【推断】反击后续钩子开关〔4DB480：非0 才 vt+1236〕〔证据: va=004DB480〕
    unsigned char   bModeFlag7530;                 // +0x1D6A (7530) x1  【推断】参数面字节旗标〔hiteff_monster：与 7529/7531/7532/7533 同块自怪物表 +452..453 拷贝〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagA;                    // +0x1D6B (7531) x2  【推断】参数面字节旗标A〔7531-7534 旗标族；各复位族整面清零〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagB;                    // +0x1D6C (7532) x2  【推断】参数面字节旗标B〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagC;                    // +0x1D6D (7533) x2  【推断】参数面字节旗标C〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bAggroGate7534;                // +0x1D6E (7534) x2  【推断】威胁打分门〔4DCCB0：非0 时按 vt+672(3)+816/+830 属性对插值累加威胁分〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_0;                // +0x1D6F (7535) x2  【推断】属性对比较使能组[4] 首项〔4DCCB0 逐字节遍历 7535..7538，命中取 vt+672(3)+172/+228 属性对插值〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_1;                // +0x1D70 (7536) x1  【推断】属性对比较使能组[4] 第2项〔4DCCB0；+186/+242 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_2;                // +0x1D71 (7537) x1  【推断】属性对比较使能组[4] 第3项〔4DCCB0；+200/+256〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_3;                // +0x1D72 (7538) x1  【推断】属性对比较使能组[4] 第4项〔4DCCB0；+214/+270〕〔证据: va=004A41C0〕
    unsigned char   abAggroFlags17_0;              // +0x1D73 (7539) x2  【推断】威胁特征位组[17] 首项〔4DCCB0：逐项 vt+776(i) 命中 +100；4A41C0 整拷 17 字节〕〔证据: va=004A41C0〕
    unsigned char _unused_1D74[3];
    unsigned int    abAggroFlags17_4;              // +0x1D77 (7543) x1  【推断】威胁特征位组[17] 第4~7项〔复位族按 uint32 整写 0；4DCCB0 逐字节读〕〔证据: va=005A8790〕
    unsigned int    abAggroFlags17_8;              // +0x1D7B (7547) x1  【推断】威胁特征位组[17] 第8~11项〔复位族整写 0〕〔证据: va=005A8790〕
    unsigned int    abAggroFlags17_12;             // +0x1D7F (7551) x1  【推断】威胁特征位组[17] 第12~15项〔复位族整写 0〕〔证据: va=005A8790〕
    unsigned char   abAggroFlags17_16;             // +0x1D83 (7555) x1  【推断】威胁特征位组[17] 第16项〔7539..7555 数组收尾〕〔证据: va=005A8790〕
    unsigned char   bStrengthMode;                 // +0x1D84 (7556) x1  【推断】强度档标志〔599C30 档2置1；tau_golem 置/清 this+7556＝1〕〔证据: va=005A8790〕
    unsigned char   bAggroBonus1;                  // +0x1D85 (7557) x1  【推断】威胁加分门1〔4DCCB0：==1 时 vt+700()+sub_53FD00 命中再加 100〕〔证据: va=005A8790〕
    unsigned char   bAggroBonus2;                  // +0x1D86 (7558) x1  【推断】威胁加分门2〔4DCCB0：非0 时按目标大状态 ≠4 取 ±100 加分〕〔证据: va=005A8790〕
    unsigned char _unused_1D87[5];
    unsigned int    uForm7564;                     // +0x1D8C (7564) x1  【推断】形态槽〔dragonman：末置形态槽 this+7564=1〕〔证据: va=005A8790〕
    unsigned int    uEnable7568;                   // +0x1D90 (7568) x1  【推断】使能/段选槽〔dragonman：使能槽 this+7568=1/2〕〔证据: va=005A8790〕
    unsigned int    uGrade7572;                    // +0x1D94 (7572) x1  【推断】档位槽〔599C30 档位组合写 7572=2〕〔证据: va=005A8790〕
    unsigned int    uPhase7576;                    // +0x1D98 (7576) x2  相位槽〔tau_golem 直证：2=复位待命；与前槽成对复位〕〔证据: va=005A8790〕
    unsigned int    uSegDefault7580;               // +0x1D9C (7580) x1  【推断】缺省段选〔tau_golem：参数面清零后置 7580=1/2〕〔证据: va=005A8790〕
    unsigned int    uForm7584;                     // +0x1DA0 (7584) x1  【推断】形态槽〔dragonman：末置形态槽 this+7584=1〕〔证据: va=005A8790〕
    unsigned int    uForm7588;                     // +0x1DA4 (7588) x1  【推断】形态槽〔dragonman：末置形态槽 this+7588=1〕〔证据: va=005A8790〕
    unsigned char _unused_1DA8[4];
    unsigned int    nAlignOffset;                  // +0x1DAC (7596) x1  【推断】位移对齐偏置〔±50/-30/-100/-20；dragonman"反向偏置"〕〔证据: va=005A8790〕
    unsigned char _unused_1DB0[172];

    // ---- 区块 5：反击态 / 交互快照 / 落地采样 / 骑乘拾取（基类） ----
    unsigned int    nCounterState;                 // +0x1E5C (7772) x1  反击态〔4DB480 变量名 nCounterState=*(this+7772)，值 1/2〕〔证据: va=004DB480〕
    unsigned char _unused_1E60[576];
    unsigned int    nRideHostSlot;                 // +0x20A0 (8352) x1  骑乘/宿主槽〔通用偏移表 this+8352〕〔证据: va=004D94A0〕
    unsigned int    uPickupParam;                  // +0x20A4 (8356) x2  【推断】拾取参数槽〔4D94A0 写 uArg3〕〔证据: va=004D94A0〕
    unsigned int    pPickupInfo7;                  // +0x20A8 (8360) x5  【推断】拾取信息快照指针〔4D94A0：7 字节对象懒创建〕〔证据: va=004D94A0〕
    unsigned char _unused_20AC[236];

    // ---- 区块 6：子类 AI 状态区（this+8600..8700，本类特化） ----
    unsigned int    nDistThreshold;                // +0x2198 (8600) x2  【推断】距主人距离阈值〔5A97A0：vt+684 距离 > 此值才行动〕〔证据: va=005A82B0〕
    unsigned int    uAI8604;                       // +0x219C (8604) x1  【推断】子类AI相位槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int    uAI8608;                       // +0x21A0 (8608) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int    uAI8612;                       // +0x21A4 (8612) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned int    uAI8616;                       // +0x21A8 (8616) x1  【推断】子类AI槽（5A82B0 复位）〔证据: va=005A82B0〕
    unsigned char   bAlarmFlag;                    // +0x21AC (8620) x3  【推断】警报/唤醒标志〔5A9100 态14 目标空时置1〕〔证据: va=005A9100〕
    unsigned char _unused_21AD[3];
    unsigned int    uPatrolGate;                   // +0x21B0 (8624) x1  【推断】巡视/指令许可门（5A96F0 读侧 +8624 非空 且 15% 概率发巡视指令）〔证据: va=005A96F0〕
    unsigned int    nPoolTime;                     // +0x21B4 (8628) x1  【推断】指挥计时戳〔5A8900 = clock_now〕〔证据: va=005A8900〕
    unsigned char _unused_21B8[4];
    unsigned int    pDollTarget;                   // +0x21BC (8636) x4  【推断】人偶目标槽〔5A9100 态14 写入；0=无目标，-1=哨兵〕〔证据: va=005A9100〕
    unsigned int    uCastSlot8640;                 // +0x21C0 (8640) x2  【推断】施放/目标槽（5A9100 态14 清 0）〔证据: va=005A9100〕
    unsigned char _unused_21C4[4];
    unsigned int    nDistSolve;                    // +0x21C8 (8648) x1  【推断】距离解算缓存〔5A97A0 写 vt+164 距离解算值〕〔证据: va=005A97A0〕
    unsigned char _unused_21CC[4];
    unsigned char   bAI8656;                       // +0x21D0 (8656) x1  【推断】子类AI标记字节（5A82B0 清 0）〔证据: va=005A82B0〕
    unsigned char _unused_21D1[7];
    unsigned char   bAI8664;                       // +0x21D8 (8664) x1  【推断】子类AI相位槽（5A9100 态8 清 0）〔证据: va=005A9100〕
    unsigned char _unused_21D9[3];
    unsigned int    nDollMode;                     // +0x21DC (8668) x3  【推断】人偶行为模式〔5A97A0：1=常态攻击指令5；2=巡视 2% 指令1〕〔证据: va=005A82B0〕
};
#pragma pack(pop)
