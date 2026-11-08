// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNAraclothoSpider      主虚表槽位数: 330   字段数: 45
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注；无直证者保留 field_XXXX）
// 继承: CNRDObject → IRDCollisionObject → IRDActiveObject → IRDMonster → CNSpider → CNAraclothoSpider（阿拉克洛蜘蛛；KSPIDER 大相位区）
// 构造链: 4AA970←4AA780←4A4EA0（+8660/8688/8716 三个 IObject、+8672/+8700/+8728=1；调 5C0490 语音 + 5C11B0 三向吐酸）
// 依据: 通用偏移表（本表实命中: 7148 大状态、7256 光环对象、7772 反击态、8352 骑乘宿主、7531..7596 攻击参数面、8600..8700 子类AI状态区）
//       + 证据行函数头注释（src 搜 va）+ 同族跨类印证（CNGoblinHodor/BullsEye/KagelBase 族命名沿用）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；
//       0x2198（this+8600）起为本类子类 AI 状态区
// ============================================================
#pragma once
#include <stdint.h>
#pragma pack(push, 1)
struct CNAraclothoSpider_Fields {
    unsigned char _base_0x0000[73]; // +0x0000..0x0048 继承基类未展开（见 src/cnrd/*.h 与 docs/14）
    // ---- 区块 1：基类公共（帧同步 / 参数灌入 / 动画对象；继承 CNRDObject 段） ----
    char            szNameBuf;              // +0x0049 (73) x1  名字缓冲 SSO 首字节〔4DE410：名称模板 sprintf 读此〕；〔≙字节 292〕〔证据: va=004DE410〕
    unsigned char _unused_004A[46];
    unsigned int    pAnimObj;               // +0x0078 (120) x6  动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕〔证据: va=00499020〕
    unsigned char _unused_007C[108];
    unsigned char   bSyncSwitch;            // +0x00E8 (232) x2  【推断】时刻同步开关〔499020：由开转关时推进帧时刻〕〔证据: va=00499020〕
    unsigned char _unused_00E9[3];
    unsigned int    nSyncArgA;              // +0x00EC (236) x1  【推断】同步参数A〔499020 写 nArg3〕〔证据: va=00499020〕
    unsigned int    nSyncArgB;              // +0x00F0 (240) x1  【推断】同步参数B〔499020 写 nArg4〕〔证据: va=00499020〕
    float           fSyncValue;             // +0x00F4 (244) x4  【推断】浮点同步值〔499080 浮点版；vmt114 非零判定〕〔证据: va=00499080〕
    unsigned char   bParamSlotA;            // +0x00F8 (248) x1  【推断】四参灌入槽A〔CNRDObject vmt11C 批量写 +248..+260〕〔证据: va=0042A8D0〕
    unsigned char _unused_00F9[3];
    unsigned int    nParamSlotB;            // +0x00FC (252) x1  【推断】四参灌入槽B〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char   bParamSlotC;            // +0x0100 (256) x1  【推断】四参灌入槽C〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char _unused_0101[3];
    unsigned int    nParamSlotD;            // +0x0104 (260) x1  【推断】四参灌入槽D〔vmt11C〕〔证据: va=0042A8D0〕
    unsigned char _unused_0108[378];

    // ---- 区块 2：帧时刻覆盖与拾取坐标（基类） ----
    unsigned char   bFrameOverride;         // +0x0282 (642) x5  帧时刻覆盖开关〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0283[1];
    unsigned int    nFrameOverrideTime;     // +0x0284 (644) x4  覆盖帧时刻〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0288[20];
    unsigned int    nPickupXCache;          // +0x029C (668) x1  【推断】拾取目标坐标缓存〔4D94A0 将 +8352 写入此槽〕〔证据: va=004D94A0〕
    unsigned int    nPickupValid;           // +0x02A0 (672) x1  【推断】拾取坐标有效标志〔4D94A0 置 1〕〔证据: va=004D94A0〕
    unsigned char _unused_02A4[6420];

    // ---- 区块 3：影身计时 / 大状态（基类） ----
    unsigned int    nInvisibleStart;        // +0x1BB8 (7096) x1  【推断】影身计时-起始〔4D5A90 = clock_now(this+36)〕〔证据: va=004D5A90〕
    unsigned int    nInvisibleDur;          // +0x1BBC (7100) x1  【推断】影身计时-时长ms〔4D5A90 nArg2〕〔证据: va=004D5A90〕
    unsigned char   bInvisibleSwitch;       // +0x1BC0 (7104) x1  【推断】影身开关字节〔4D5A90 pszArg3〕〔证据: va=004D5A90〕
    unsigned char _unused_1BC1[43];
    unsigned int    nBigState;              // +0x1BEC (7148) x1  大状态〔4DB480 本文件变量名 nBigState=*(this+7148)；通用表〕〔证据: va=004DB480〕
    unsigned char _unused_1BF0[368];

    // ---- 区块 4：攻击/分身参数面 7520..7539（4A41C0 配置块副本） ----
    unsigned int    uCfgWord0;              // +0x1D60 (7520) x1  【推断】配置块首字〔4A41C0 48+字节整块拷贝 this+7520 区〕〔证据: va=004A41C0〕
    unsigned int    uCfgWord1;              // +0x1D64 (7524) x1  【推断】配置块第2字〔4A41C0〕〔证据: va=004A41C0〕
    unsigned char   bRetargetGate;          // +0x1D68 (7528) x1  【推断】目标重选门〔4E1BE0 门：·this+7528 标志〕〔证据: va=004A41C0〕
    unsigned char   bCounterHookSw;         // +0x1D69 (7529) x2  【推断】反击后续钩子开关〔4DB480：非0 才 vt+1236〕〔证据: va=004DB480〕
    unsigned char   bModeFlag7530;          // +0x1D6A (7530) x1  【推断】参数面字节旗标〔hiteff_monster：与 7529/7531/7532/7533 同块自怪物表 +452..453 拷贝〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagA;             // +0x1D6B (7531) x1  【推断】参数面字节旗标A〔7531-7534 旗标族；各复位族整面清零〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagB;             // +0x1D6C (7532) x1  【推断】参数面字节旗标B〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagC;             // +0x1D6D (7533) x1  【推断】参数面字节旗标C〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bAggroGate7534;         // +0x1D6E (7534) x1  【推断】威胁打分门〔4DCCB0：非0 时按 vt+672(3)+816/+830 属性对插值累加威胁分〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_0;         // +0x1D6F (7535) x1  【推断】属性对比较使能组[4] 首项〔4DCCB0 逐字节遍历 7535..7538，命中取 vt+672(3)+172/+228 属性对插值〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_1;         // +0x1D70 (7536) x1  【推断】属性对比较使能组[4] 第2项〔4DCCB0；+186/+242 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_2;         // +0x1D71 (7537) x1  【推断】属性对比较使能组[4] 第3项〔4DCCB0；+200/+256〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_3;         // +0x1D72 (7538) x1  【推断】属性对比较使能组[4] 第4项〔4DCCB0；+214/+270〕〔证据: va=004A41C0〕
    unsigned char   abAggroFlags17_0;       // +0x1D73 (7539) x1  【推断】威胁特征位组[17] 首项〔4DCCB0：逐项 vt+776(i) 命中 +100；4A41C0 整拷 17 字节〕〔证据: va=004A41C0〕
    unsigned char _unused_1D74[232];

    // ---- 区块 5：反击态 / 骑乘拾取（7772 / 8352..8360） ----
    unsigned int    nCounterState;          // +0x1E5C (7772) x1  反击态〔4DB480 变量名 nCounterState=*(this+7772)，值 1/2〕〔证据: va=004DB480〕
    unsigned char _unused_1E60[576];
    unsigned int    nRideHostSlot;          // +0x20A0 (8352) x1  骑乘/宿主槽〔通用偏移表 this+8352〕〔证据: va=004D94A0〕
    unsigned int    uPickupParam;           // +0x20A4 (8356) x2  【推断】拾取参数槽〔4D94A0 写 uArg3〕〔证据: va=004D94A0〕
    unsigned int    pPickupInfo7;           // +0x20A8 (8360) x5  【推断】拾取信息快照指针〔4D94A0：7 字节对象懒创建〕〔证据: va=004D94A0〕
    unsigned char _unused_20AC[252];

    // ---- 区块 6：蜘蛛族子类 AI 状态区（滚动/钻地/传送相位槽 this+8600..8764） ----
    unsigned char   bPhase8616;             // +0x21A8 (8616) x1  【推断】钻地相位字节1〔5C0490（KSPIDER 语音装载 + 大相位区清零）清 0；同族蜘蛛 5C0220 同址滞空/滚动标志〕〔证据: va=005C0490〕
    unsigned char   bPhase8617;             // +0x21A9 (8617) x1  【推断】钻地相位字节2〔5C0490 清 0；与 8616 成对（同族 5C0220 同址）〕〔证据: va=005C0490〕
    unsigned char _unused_21AA[14];
    unsigned int    nTpCount;               // +0x21B8 (8632) x1  【推断】传送次数槽〔5C0490 清 0；同族蜘蛛王 5C1750 同址 = 传送次数（全局 dword_9A05D4>2 归零）〕〔证据: va=005C0490〕
    unsigned int    nTpPhase;               // +0x21BC (8636) x1  【推断】传送/钻地相位槽〔5C0490 清 0；同族蜘蛛王 5C1750 同址相位 1..6〕〔证据: va=005C0490〕
    unsigned int    nBurrowPhase;           // +0x21C0 (8640) x1  【推断】出土相位槽〔5C0490 清 0；同族蜘蛛王 5C12B0 同址钻地出土相位 1..3〕〔证据: va=005C0490〕
    unsigned int    uPhase8644;             // +0x21C4 (8644) x1  【推断】相位计数槽〔5C0490 清 0（无其他直证读点）〕〔证据: va=005C0490〕
    unsigned char _unused_21C8[4];
    unsigned char   bGate8652;              // +0x21CC (8652) x1  【推断】相位门字节〔5C0490 清 0；同族蜘蛛 5C0220 同址滚动相位一次性门（==0 且 clock>2000 触发）〕〔证据: va=005C0490〕
    unsigned char   bGate8653;              // +0x21CD (8653) x1  【推断】相位门字节〔5C0490 清 0；与 8652 成对〕〔证据: va=005C0490〕
    unsigned char _unused_21CE[110];
    unsigned int    uPhase8764;             // +0x223C (8764) x1  【推断】滚动/传送相位槽〔5C0490 大相位区清零收尾槽〕〔证据: va=005C0490〕
};
#pragma pack(pop)

// 统计: 字段行 45 / 未命名 0 / 标【推断】38 / 末尾偏移 +0x2240
