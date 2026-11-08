// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNHunterHunter  主虚表槽位数: 329   字段数: 45
// 还原方法: 类槽位函数 this+N 聚合 + 语义名手工判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注；无直证者保留 field_XXXX）
// 继承: KMessenger → KGameMessenger → CNRDObject×2 → IRDCollisionObject×3 → IRDActiveObject×4 → IRDMonster → CNHunter → CNHunterHunter
//       （构造链 4A8D60←4A8AF0←4A4EA0；基类 CNHunter 构造置 +8648=15/+8644=0/+8628=0 → 5ADB10 语音装载）
//       官方名=猎手（HA 型）；同族派生：CNHunterMaster 4A8C20 / CNHunterAlex 4A8CC0 均以 4A8AF0 为基
// 依据: 通用偏移表（本表实命中: 642/644 帧时刻覆盖、7148 大状态、7252 当前目标、7520..7539 攻击参数面、7772 反击态、8352 骑乘宿主）
//       证据行函数头注释（src/game/creature/tau_golem.cpp 分区11 猎人 Hunter 0x5ACF40-0x5AE3C0:
//       5AD9E0 酸液/AI 总调度（8604 相位 + 8616 帧型 → 单发 5AD5A0 / 三连 5AD610；8620 起手门；8622 相位互锁；8628 播音串）
//       + 5ADB10 猎人语音装载表（6792..6872 索引 + HUNTER_FIND/DMG/DIE/ATK + HUNT_BREATH_LOOP；清 8622/8604）
//       + 5ADBD0 重呼吸 HUNT_HARD_BREATH_LOOP + 5ADC00 扑跳 HUNT_JUMP + 5ADCF0 主状态钩子（1639 镜像 + 1757 动作字）
//       + 5ADFE0 HH / 5AE160 HM / 5AE290 HA 三型外观装载（各自 .equ 三~四件：horn/hair/clothes/claws，
//         尾置 8621、2150(8600)、7576/7537、1895 相位；HA 型以 blindfold 蒙眼布代 hair/claws）
//       + src/game/rtti_core.cpp 4A8D60 构造（4A8AF0 基 + sub_5AE290 HA 外观）/ 4A8DF0 析构（→ 4A8B70））
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；0x219C 起为猎人子类 AI 状态区（this+8604 起）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNHunterHunter_Fields {
    unsigned char _base_0x0000[73]; // +0x0000..0x0048 继承基类未展开（见 src/cnrd/*.h 与 docs/14）

    // ---- 区块 1：基类公共（帧同步 / 参数灌入 / 动画对象；继承 CNRDObject 段） ----
    char            szNameBuf;                     // +0x0049 (73) x1  名字缓冲 SSO 首字节〔4DE410：名称模板 sprintf 读此〕〔证据: va=004DE410〕
    unsigned char _unused_004A[46];
    unsigned int    pAnimObj;                      // +0x0078 (120) x6  动画对象指针〔CNRDObject.h +0x078；499020/499080 帧推进对象〕〔证据: va=00499020〕
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

    // ---- 区块 3：影身计时 / 大状态 / 当前目标（基类；7096..7104 / 7148 / 7252） ----
    unsigned int    nInvisibleStart;               // +0x1BB8 (7096) x1  【推断】影身计时-起始〔4D5A90 = clock_now(this+36)〕〔证据: va=004D5A90〕
    unsigned int    nInvisibleDur;                 // +0x1BBC (7100) x1  【推断】影身计时-时长ms〔4D5A90 nArg2〕〔证据: va=004D5A90〕
    unsigned char   bInvisibleSwitch;              // +0x1BC0 (7104) x1  【推断】影身开关字节〔4D5A90 pszArg3〕〔证据: va=004D5A90〕
    unsigned char _unused_1BC1[43];
    unsigned int    nBigState;                     // +0x1BEC (7148) x1  大状态〔4DB480 变量名 nBigState=*(this+7148)；5AD9E0 6/0/其它三分支门〕〔证据: va=004DB480〕
    unsigned char _unused_1BF0[100];
    unsigned int    pTarget7252;                   // +0x1C54 (7252) x1  【推断】当前目标/关联对象〔5AD9E0: 非 0 才进单发/三连吐酸分支〕〔证据: va=005AD9E0〕
    unsigned char _unused_1C58[264];

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
    unsigned char   abAggroAttr4_2;                // +0x1D71 (7537) x1  【推断】属性对比较使能组[4] 第3项〔4DCCB0；+200/+256 属性对；5AE160 HM 型尾置 7537=1〕〔证据: va=004A41C0〕
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

    // ---- 区块 6：猎人子类 AI 状态区（this+8604 起；5AD9E0 总调度族） ----
    unsigned char   bSpitPhase8604;                // +0x219C (8604) x2  吐酸相位开〔5AD9E0: 开则按 8616 帧型分派单发/三连；动画 +170 终止位则清 0；5ADB10 装载时清 0〕〔证据: va=005AD9E0〕
    unsigned char _unused_219D[11];
    unsigned int    nFrameType8616;                // +0x21A8 (8616) x1  【推断】吐酸帧型（14=单发 / 其余=三连）〔5AD9E0: this+8616==14 走 5AD5A0 单发，否则 5AD610 三连〕〔证据: va=005AD9E0〕
    unsigned char   bAttackStart8620;              // +0x21AC (8620) x2  【推断】待机起手门〔5AD9E0: 大状态 6 且帧 +148>=3 且 8620==0 时 vt+352 起手并置 1〕〔证据: va=005AD9E0〕
    unsigned char   bLoopLatch8622;                // +0x21AE (8622) x4  【推断】循环音锁存〔5AD9E0: 反应态 4/4 时 vt+216(9) 停并清 0；否则 8622==0 时播 8628 串并置 1〕〔证据: va=005AD9E0〕
    unsigned char _unused_21AF[5];
    unsigned int    pVoiceName8628;                // +0x21B4 (8628) x1  【推断】语音名 std::string 基址（SSO 缓冲首字）〔5AD9E0: +8648<0x10 时取 this+8628 内联名交 vt+212 播报，否则取堆指针；4A8AF0 构造置首字节 0〕〔证据: va=005AD9E0〕
    unsigned char _unused_21B8[16];
    unsigned int    nVoiceNameCap8648;             // +0x21C8 (8648) x1  【推断】语音名 SSO 容量判据〔5AD9E0 以 <0x10 择内联；4A8AF0 构造置 15、4A8B70 析构按 >=0x10 free〕〔证据: va=004A8AF0〕
};
#pragma pack(pop)

// 统计: 字段行 43 / 未命名保留 0 / 标【推断】37 / 末尾偏移 +0x21CC
