// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNEvangelistOfDark  主虚表槽位数: 330   字段数: 47
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注；无直证者保留 field_XXXX）
// 继承: KMessenger → KGameMessenger → CNRDObject×2 → IRDCollisionObject×3 → IRDActiveObject×3
//       → CNMonsterFriendShip → CNZealotFriendShip → CNZealot → CNEvangelistOfDark（构造链 4A9F10←4A9AC0；主/副双 vftable 均换本类）
//       官方名=暗之传道者；同族：CNZealot 骨架（本类共享）+ CNEvangelistOfLight 独立骨架。
// 依据: 通用偏移表（本表实命中: 642/644 帧时刻覆盖、7148 大状态、7520..7539 攻击参数面、7772 反击态、8352 骑乘宿主）
//       证据行函数头注释（src/game/creature/dragonman.cpp 分区 ZGM/信徒 0x5B73B0-0x5B8BD0:
//       5B73B0 ZGM 扩展复位 8604..8660（清 8604/8605/8606/8607 四标记、8640/8656/8660 写 -1 哨兵）
//       + 5B7400 vmt200 命中覆写（8668 计数到期回卷 + 8600 嵌入对象 vt+0）
//       + 5B7660 信徒绑定确认回落（8656/8660 对 → CNZealot cast、写其 8668=5）
//       + 5B7720 大状态三段门（8604 单次门 8/15/14）+ 5B7BE0 相位门（8607/8668）+ 5B7EB0 分身出厂（8664=30/8640）
//       + src/game/rtti_core.cpp 4A9F10 构造（8600 副表、8608 off_6C2B88、8620=1、5B73B0+5B8C40 初装；尾置 *(this+2168)=30042 技能/动作 ID））
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；0x219C 起为信徒子类 AI 状态区（this+8604 起）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNEvangelistOfDark_Fields {
    unsigned char _base_0x0000[73]; // +0x0000..0x0048 继承基类未展开（见 src/cnrd/*.h 与 docs/14）

    // ---- 区块 1：基类公共（帧同步 / 参数灌入 / 动画对象；继承 CNRDObject 段） ----
    char            szNameBuf;                     // +0x0049 (73) x1  名字缓冲 SSO 首字节〔4DE410：名称模板 sprintf 读此〕〔证据: va=004DE410〕
    unsigned char _unused_004A[46];
    unsigned int    pAnimObj;                      // +0x0078 (120) x7  动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕〔证据: va=00499020〕
    unsigned char _unused_007C[108];
    unsigned char   bSyncSwitch;                   // +0x00E8 (232) x2  【推断】时刻同步开关〔499020：由开转关时推进帧时刻〕〔证据: va=00499020〕
    unsigned char _unused_00E9[3];
    unsigned int    nSyncArgA;                     // +0x00EC (236) x1  【推断】同步参数A〔499020 写 nArg3〕〔证据: va=00499020〕
    unsigned int    nSyncArgB;                     // +0x00F0 (240) x1  【推断】同步参数B〔499020 写 nArg4〕〔证据: va=00499020〕
    float           fSyncValue;                    // +0x00F4 (244) x4  【推断】浮点同步值〔499080 浮点版〕〔证据: va=00499080〕
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
    unsigned char _unused_02A4[6420];

    // ---- 区块 3：影身计时与大状态（基类） ----
    unsigned int    nInvisibleStart;               // +0x1BB8 (7096) x1  【推断】影身计时-起始〔4D5A90 = clock_now(this+36)〕〔证据: va=004D5A90〕
    unsigned int    nInvisibleDur;                 // +0x1BBC (7100) x1  【推断】影身计时-时长ms〔4D5A90 nArg2〕〔证据: va=004D5A90〕
    unsigned char   bInvisibleSwitch;              // +0x1BC0 (7104) x1  【推断】影身开关字节〔4D5A90 pszArg3〕〔证据: va=004D5A90〕
    unsigned char _unused_1BC1[43];
    unsigned int    nBigState;                     // +0x1BEC (7148) x1  大状态〔4DB480 变量名 nBigState=*(this+7148)；5B7720 三段门 8/15/14 分派〕〔证据: va=004DB480〕
    unsigned char _unused_1BF0[368];

    // ---- 区块 4：攻击/分身参数面 7520..7539（4A41C0 配置块副本） ----
    unsigned int    uCfgWord0;                     // +0x1D60 (7520) x1  【推断】配置块首字〔4A41C0 48+字节整块拷贝 this+7520 区〕〔证据: va=004A41C0〕
    unsigned int    uCfgWord1;                     // +0x1D64 (7524) x1  【推断】配置块第2字〔4A41C0〕〔证据: va=004A41C0〕
    unsigned char   bRetargetGate;                 // +0x1D68 (7528) x1  【推断】目标重选门〔4E1BE0 门：·this+7528 标志〕〔证据: va=004A41C0〕
    unsigned char   bCounterHookSw;                // +0x1D69 (7529) x2  【推断】反击后续钩子开关〔4DB480：非0 才 vt+1236〕〔证据: va=004DB480〕
    unsigned char   bModeFlag7530;                 // +0x1D6A (7530) x1  【推断】参数面字节旗标〔hiteff_monster：与 7529/7531/7532/7533 同块自怪物表 +452..453 拷贝〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagA;                    // +0x1D6B (7531) x1  【推断】参数面字节旗标A〔7531-7534 旗标族；各复位族整面清零〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagB;                    // +0x1D6C (7532) x1  【推断】参数面字节旗标B〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bModeFlagC;                    // +0x1D6D (7533) x1  【推断】参数面字节旗标C〔旗标族〕〔证据: va=004A41C0〕
    unsigned char   bAggroGate7534;                // +0x1D6E (7534) x1  【推断】威胁打分门〔4DCCB0：非0 时按 vt+672(3)+816/+830 属性对插值累加威胁分〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_0;                // +0x1D6F (7535) x1  【推断】属性对比较使能组[4] 首项〔4DCCB0 逐字节遍历 7535..7538〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_1;                // +0x1D70 (7536) x1  【推断】属性对比较使能组[4] 第2项〔4DCCB0；+186/+242 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_2;                // +0x1D71 (7537) x1  【推断】属性对比较使能组[4] 第3项〔4DCCB0；+200/+256 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroAttr4_3;                // +0x1D72 (7538) x1  【推断】属性对比较使能组[4] 第4项〔4DCCB0；+214/+270 属性对〕〔证据: va=004A41C0〕
    unsigned char   abAggroFlags17_0;              // +0x1D73 (7539) x1  【推断】威胁特征位组[17] 首项〔4DCCB0：逐项 vt+776(i) 命中 +100；4A41C0 整拷 17 字节〕〔证据: va=004A41C0〕
    unsigned char _unused_1D74[232];

    // ---- 区块 5：反击态 / 骑乘拾取（7772 / 8352..8360） ----
    unsigned int    nCounterState;                 // +0x1E5C (7772) x1  反击态〔4DB480 变量名 nCounterState=*(this+7772)，值 1/2〕〔证据: va=004DB480〕
    unsigned char _unused_1E60[576];
    unsigned int    nRideHostSlot;                 // +0x20A0 (8352) x1  骑乘/宿主槽〔通用偏移表 this+8352〕〔证据: va=004D94A0〕
    unsigned int    uPickupParam;                  // +0x20A4 (8356) x2  【推断】拾取参数槽〔4D94A0 写 uArg3〕〔证据: va=004D94A0〕
    unsigned int    pPickupInfo7;                  // +0x20A8 (8360) x5  【推断】拾取信息快照指针〔4D94A0：7 字节对象懒创建〕〔证据: va=004D94A0〕
    unsigned char _unused_20AC[240];

    // ---- 区块 6：信徒子类 AI 状态区（this+8600 起；5B73B0 复位族 / 5B7720 大状态门 / 5B7BE0 相位门） ----
    unsigned char   bAI8604;                       // +0x219C (8604) x3  大状态 8 单次门〔5B7720: 段 8 且 7028∈{1,2}、+148==1 且未置时调 vt+1316 并置 1；5B73B0 复位清 0〕〔证据: va=005B7720〕
    unsigned char   bAI8605;                       // +0x219D (8605) x1  【推断】子类 AI 标志字节〔5B73B0 复位清 0（四标记族之一）〕〔证据: va=005B73B0〕
    unsigned char   bAI8606;                       // +0x219E (8606) x1  【推断】子类 AI 标志字节〔5B73B0 复位清 0〕〔证据: va=005B73B0〕
    unsigned char   bAI8607;                       // +0x219F (8607) x2  非指挥态门〔5B7BE0 门链: vt+308 目标、vt+840 大状态 0、8607 非指挥态、8668 冷却≤0 时分派 14 蓄力架招；5B73B0 清 0〕〔证据: va=005B7BE0〕
    unsigned char _unused_21A0[32];
    unsigned int    pCritSlot8640;                 // +0x21C0 (8640) x1  【推断】附属/配对槽〔5B73B0 写 -1 哨兵；5B7EB0 分身出厂存 vt+384 出场参数〕〔证据: va=005B73B0〕
    unsigned int    uPhase8644;                    // +0x21C4 (8644) x1  【推断】相位槽〔5B73B0 清 0〕〔证据: va=005B73B0〕
    unsigned int    uPhase8648;                    // +0x21C8 (8648) x1  【推断】相位/缓存槽〔5B73B0 清 0〕〔证据: va=005B73B0〕
    unsigned int    uPhase8652;                    // +0x21CC (8652) x1  【推断】相位槽〔5B73B0 清 0〕〔证据: va=005B73B0〕
    unsigned int    uPair8656;                     // +0x21D0 (8656) x1  事件 16/17 配对槽〔5B73B0 写 -1 哨兵；5B7660 与 uEvt8660 成对经 sub_45EBE0 解对象并 RTTI cast 为 CNZealot〕〔证据: va=005B7660〕
    unsigned int    uEvt8660;                      // +0x21D4 (8660) x1  事件配对槽〔5B73B0 写 -1；与 uPair8656 配对消费后两槽归 -1〕〔证据: va=005B7660〕
    unsigned char _unused_21D8[4];
    int             nCool8668;                     // +0x21DC (8668) x1  反击/架招冷却计时〔5B7BE0 门链: this+8668 冷却≤0 才 rand%300<5 进 14 蓄力架招；5B7400 递减至 0 回卷动画帧〕〔证据: va=005B7BE0〕
};
#pragma pack(pop)

// 统计: 字段行 47 / 未命名保留 0 / 标【推断】37 / 末尾偏移 +0x21E0
