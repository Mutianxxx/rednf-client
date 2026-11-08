// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNDendroidBasic  主虚表槽位数: 332   字段数: 51
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注；无直证者保留 field_XXXX）
// 继承: CNRDObject → IRDCollisionObject → IRDActiveObject → IRDMonster → CNDendroidBasic（构造链 4AADF0←4A4EA0；5C3A30 复位 + 5C57F0 初始化）
// 依据: 通用偏移表（本表实命中: 6200 段表、6216 资源表、6556 主状态镜像、7096..7104 影身计时、7520..7539 攻击参数面、8352 骑乘宿主）
//       证据行函数头注释（src/game/creature/spider_trap.cpp 分区3 树精 5C3A30/5C4810/5C3AF0/5C4780/5C57F0 + src/game/rtti_core.cpp 构造链）+ 同族跨类印证（CNGoliden/CNRodinglo 同 5C4810 主循环）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；0x2198 起为子类 AI 状态区（this+8600 起；机械树精基）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNDendroidBasic_Fields {
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
    unsigned char _unused_02A4[5524];

    // ---- 区块 3：段表 / 资源表 / 主状态镜像（6200 / 6216 / 6556） ----
    unsigned int    pTbl6200;                      // +0x1838 (6200) x1  【推断】段表对象〔5C4810 按攻击段号 7028 取 6200 表条目〕〔证据: va=005C4810〕
    unsigned char _unused_183C[12];
    unsigned int    pTbl6216;                      // +0x1848 (6216) x4  【推断】资源/帧游标表〔+24 帧游标；5C4810 sub_4926A0 复位〕〔证据: va=005C4810〕
    unsigned char _unused_184C[336];
    unsigned int    nMainState6556;                // +0x199C (6556) x1  主状态镜像〔5C4810 switch 总闸；==8 攻击/14 缠绕/15/16/17 收位〕〔证据: va=005C4810〕
    unsigned char _unused_19A0[536];

    // ---- 区块 4：影身计时（基类；4D5A90 影身计时三连） ----
    unsigned int    nInvisibleStart;               // +0x1BB8 (7096) x1  【推断】影身计时-起始〔4D5A90 = clock_now(this+36)〕〔证据: va=004D5A90〕
    unsigned int    nInvisibleDur;                 // +0x1BBC (7100) x1  【推断】影身计时-时长ms〔4D5A90 nArg2〕〔证据: va=004D5A90〕
    unsigned char   bInvisibleSwitch;              // +0x1BC0 (7104) x1  【推断】影身开关字节〔4D5A90 pszArg3〕〔证据: va=004D5A90〕
    unsigned char _unused_1BC1[415];

    // ---- 区块 5：攻击/分身参数面 7520..7539（4A41C0 配置块副本） ----
    unsigned int    uCfgWord0;                     // +0x1D60 (7520) x1  【推断】配置块首字〔4A41C0 48+字节整块拷贝 this+7520 区〕〔证据: va=004A41C0〕
    unsigned int    uCfgWord1;                     // +0x1D64 (7524) x1  【推断】配置块第2字〔4A41C0〕〔证据: va=004A41C0〕
    unsigned char   bRetargetGate;                 // +0x1D68 (7528) x1  【推断】目标重选门〔4E1BE0 门：·this+7528 标志〕〔证据: va=004A41C0〕
    unsigned char   bCounterHookSw;                // +0x1D69 (7529) x1  【推断】反击后续钩子开关〔4DB480：非0 才 vt+1236〕〔证据: va=004A41C0〕
    unsigned char   bModeFlag7530;                 // +0x1D6A (7530) x1  【推断】参数面字节旗标〔hiteff_monster：与 7529/7531/7532/7533 同块自怪物表 +452..453 拷贝〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagA;                    // +0x1D6B (7531) x1  【推断】参数面字节旗标A〔7531-7534 旗标族；各复位族整面清零〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagB;                    // +0x1D6C (7532) x1  【推断】参数面字节旗标B〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagC;                    // +0x1D6D (7533) x1  【推断】参数面字节旗标C〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bAggroGate7534;                // +0x1D6E (7534) x1  【推断】威胁打分门〔4DCCB0：非0 时按 vt+672(3)+816/+830 属性对插值累加威胁分〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_0;                // +0x1D6F (7535) x1  【推断】属性对比较使能组[4] 首项〔4DCCB0 逐字节遍历 7535..7538，命中取 vt+672(3)+172/+228 属性对插值〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_1;                // +0x1D70 (7536) x1  【推断】属性对比较使能组[4] 第2项〔4DCCB0；+186/+242 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_2;                // +0x1D71 (7537) x1  【推断】属性对比较使能组[4] 第3项〔4DCCB0；+200/+256 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_3;                // +0x1D72 (7538) x1  【推断】属性对比较使能组[4] 第4项〔4DCCB0；+214/+270 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroFlags17_0;              // +0x1D73 (7539) x1  【推断】威胁特征位组[17] 首项〔4DCCB0：逐项 vt+776(i) 命中 +100；4A41C0 整拷 17 字节〕〔证据: va=004A41C0〕
    unsigned char _unused_1D74[812];

    // ---- 区块 6：骑乘拾取（基类） ----
    unsigned int    nRideHostSlot;                 // +0x20A0 (8352) x1  骑乘/宿主槽〔通用偏移表 this+8352〕〔证据: va=004D94A0〕
    unsigned int    uPickupParam;                  // +0x20A4 (8356) x2  【推断】拾取参数槽〔4D94A0 写 uArg3〕〔证据: va=004D94A0〕
    unsigned int    pPickupInfo7;                  // +0x20A8 (8360) x5  【推断】拾取信息快照指针〔4D94A0：7 字节对象懒创建〕〔证据: va=004D94A0〕
    unsigned char _unused_20AC[236];

    // ---- 区块 7：树精子类 AI 状态区（this+8600..8685；动作号快照/绑定/一次性门） ----
    unsigned int    nBondPhase8600;                // +0x2198 (8600) x2  【推断】绑定相位〔5C4810 ==2 且挂点 +170 时 setState(17) 绑定 / setState(9) 待机；5C3A30 清零〕〔证据: va=005C4810〕
    unsigned int    nActSnapA8604;                 // +0x219C (8604) x1  动作号快照A〔5C57F0 写 this+1543 值；5C4780 用于还原比对〕〔证据: va=005C3A30〕
    unsigned int    nActSnapB8608;                 // +0x21A0 (8608) x1  动作号快照B〔5C57F0 写 this+1544 值；5C4780 还原比对〕〔证据: va=005C3A30〕
    unsigned int    nActSnapC8612;                 // +0x21A4 (8612) x1  动作号快照C〔5C57F0 写 this+1540 值；5C4780 还原比对〕〔证据: va=005C3A30〕
    unsigned int    nSentinel8616;                 // +0x21A8 (8616) x1  【推断】无索引哨兵槽（5C3A30 复位置 -1；候选表其余 va 未直读此槽）〔证据: va=005C3A30〕
    unsigned int    uSegSwitchLatch8620;           // +0x21AC (8620) x2  【推断】段帧切换一次性门〔5C4810 段 1/2 且 200 对象为当前段时先查此门，未置才复位 6216+24 并 vt+196 切帧〕〔证据: va=005C4810〕
    unsigned int    uAI8624;                       // +0x21B0 (8624) x1  【推断】子类AI槽（5C3A30 清零）〔证据: va=005C3A30〕
    unsigned char _unused_21B4[12];
    unsigned char   uOneShotLatch8640;             // +0x21C0 (8640) x1  【推断】一次性锁存〔5C3AF0 贴合 / 5C3E20 种子散射 / 5C41E0 蓄雷共用；5C3A30 清零〕〔证据: va=005C3A30〕
    unsigned char _unused_21C1[3];
    unsigned int    nSpawnParam8644;               // +0x21C4 (8644) x1  【推断】出场参数槽〔5C57F0 vt+384(this,2) 写入；5C3A30 置 -1 哨兵〕〔证据: va=005C3A30〕
    unsigned int    uAI8648;                       // +0x21C8 (8648) x1  【推断】子类AI槽（5C3A30 清零）〔证据: va=005C3A30〕
    unsigned int    nHitTag8652;                   // +0x21CC (8652) x1  【推断】命中标记〔5C4650 存攻击方档位块 +20；5C3A30 置 -1；5C5E20 ArgList==5 按 8652==0 强制散射〕〔证据: va=005C3A30〕
    unsigned int    pVecBegin8656;                 // +0x21D0 (8656) x1  【推断】向量缓存首针〔5C3A30 对 8656/8660/8664 三元组清零〕〔证据: va=005C3A30〕
    unsigned char _unused_21D4[24];
    unsigned char   bLoopLatch8684;                // +0x21EC (8684) x4  【推断】循环音锁存〔5C4810 空闲播 DENDROID_01_LOOP 置 1；非空闲 vt+216(9) 停并清 0〕〔证据: va=005C4810〕
    unsigned char   bSwishLatch8685;               // +0x21ED (8685) x6  【推断】挥击/散射语音锁存〔5C4810 播 DENDROID_SWISH_01/02/DRIVE_01 置 1；5C3E20 播 DENDROID_SPIT；5C57F0 清 0〕〔证据: va=005C4810〕
};
#pragma pack(pop)

// 统计: 字段行 51 / 未命名保留 0 / 标【推断】42 / 末尾偏移 +0x21EE
