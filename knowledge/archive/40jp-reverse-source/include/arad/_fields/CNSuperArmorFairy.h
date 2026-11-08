// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNSuperArmorFairy  主虚表槽位数: 190   字段数: 37
// 还原方法: 类槽位函数 this+N 聚合 + 语义名人工判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注；无直证者保留 field_XXXX）
// 继承: KMessenger → KGameMessenger → CNRDObject×2 → IRDCollisionObject×3 → CNRDPassiveObject×4 → CNMapObject → CNFairy → CNSuperArmorFairy
//       （构造链 538700←5383C0；基类 CNFairy 构造 5383C0 ← 52ED60）
// 依据: 通用偏移表（本表实命中: 642/644 帧时刻覆盖、680..704 表现/名字快照块、964/968 载荷缓冲）
//       证据行函数头注释（src/combat/breakable_map.cpp 分区17 妖精族 0x62C220-0x62D0B0: 62CAD0 施加（sub_51A7D0 造 Barrier 霸体 PO、时长写 vt+64 结果 +40）
//       + 62C510 漂浮音循环 + 62C5F0 参数装载（末位档/十位多目标）+ 62CB70 双件动画；src/game/gunner_skills.cpp 5383C0 构造器）
// 说明: 0x0000 起为基类继承段（本候选表首直证点自 +0x0078 起）；无 this+8600 之后子类 AI 状态区直证点
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSUPERARMORFAIRY
#define ARAD40JP_FIELDS_CNSUPERARMORFAIRY

#include <stdint.h>

#pragma pack(push, 1)
struct CNSuperArmorFairy_Fields {
    unsigned char _base_0x0000[120]; // +0x0000..0x0077 继承段未展开（CNMapObject/CNRDPassiveObject 族，见 src/cnrd/*.h）

    // ---- 区块 1：基类公共（帧同步 / 参数灌入；继承 CNRDObject 段） ----
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
    unsigned char _unused_0108[60];

    // ---- 区块 2：机件槽与动画名 SSO（60B3D0 装载驱动） ----
    unsigned int    nAnchor324;                    // +0x0144 (324) x1  【推断】帧/层参数槽〔62C510：作 vt+124 第二参换出坐标链 vt+124→vt+120→vt+112〕〔证据: va=0062C510〕
    unsigned char _unused_0148[36];
    unsigned int    pAnimNameStr;                  // +0x016C (364) x1  动画件名缓冲 SSO 内联首址〔60B3D0：+384<0x10 时取 this+364 名交 sub_4C3640 建动画〕〔证据: va=0060B3D0〕
    unsigned char _unused_0170[16];
    unsigned int    nAnimNameCap;                  // +0x0180 (384) x1  【推断】动画件名 SSO 容量判据（<0x10 走内联缓冲）〔60B3D0〕〔证据: va=0060B3D0〕
    unsigned char _unused_0184[254];

    // ---- 区块 3：帧时刻覆盖（基类 4E5C10） ----
    unsigned char   bFrameOverride;                // +0x0282 (642) x5  帧时刻覆盖开关〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0283[1];
    unsigned int    nFrameOverrideTime;            // +0x0284 (644) x4  覆盖帧时刻〔4E5C10 直证〕〔证据: va=004E5C10〕
    unsigned char _unused_0288[32];

    // ---- 区块 4：表现/名字快照块（4E1FE0 28 字节直拷） ----
    unsigned int    nSnapshot680;                  // +0x02A8 (680) x2  表现/名字快照[0]〔4E1FE0 由 pArg2[0] 直拷〕〔证据: va=004E1FE0〕
    unsigned int    nSnapshot684;                  // +0x02AC (684) x2  表现/名字快照[1]〔4E1FE0 由 pArg2[1]〕〔证据: va=004E1FE0〕
    unsigned int    nSnapshot688;                  // +0x02B0 (688) x1  表现/名字快照[2]〔4E1FE0 由 pArg2[2]〕〔证据: va=004E1FE0〕
    unsigned int    nSnapshot692;                  // +0x02B4 (692) x1  表现/名字快照[3]〔4E1FE0 由 pArg2[3]〕〔证据: va=004E1FE0〕
    unsigned int    nSnapshot696;                  // +0x02B8 (696) x1  表现/名字快照[4]〔4E1FE0 由 pArg2[4]〕〔证据: va=004E1FE0〕
    unsigned char   bSnapshot700;                  // +0x02BC (700) x1  表现/名字快照[20]〔4E1FE0 由 pArg2[20]〕〔证据: va=004E1FE0〕
    unsigned char   bSnapshot701;                  // +0x02BD (701) x1  表现/名字快照[21]〔4E1FE0 由 pArg2[21]〕〔证据: va=004E1FE0〕
    unsigned char _unused_02BE[2];
    unsigned int    nSnapshot704;                  // +0x02C0 (704) x1  表现/名字快照[24]〔4E1FE0 由 pArg2[24]〕〔证据: va=004E1FE0〕
    unsigned char _unused_02C4[4];
    unsigned int    pResTbl712;                    // +0x02C8 (712) x4  【推断】资源/动画句柄表基指针〔60B3D0 逐 4 字节取子句柄交 sub_41ACF0；62C510 以 +712+4*档+32 取档位件〕〔证据: va=0062C510〕
    unsigned char _unused_02CC[248];

    // ---- 区块 5：配置块直拷面与载荷缓冲（60B3D0 由 this+348 表项填充；5FFF80 缓冲管理） ----
    unsigned int    nBlobSize;                     // +0x03C4 (964) x1  载荷缓冲字节数〔5FFF80: *(this+964)=Size〕〔证据: va=005FFF80〕
    unsigned int    pBlobData;                     // +0x03C8 (968) x3  载荷缓冲指针〔5FFF80: 旧块 free 后 operator new(Size) 存入〕〔证据: va=005FFF80〕
    unsigned int    uCfgD972;                      // +0x03CC (972) x1  【推断】配置表项[3]〔60B3D0 由 *(this+348)[3] 直拷入 +972〕〔证据: va=0060B3D0〕
    unsigned int    uCfgE976;                      // +0x03D0 (976) x1  【推断】配置表项[4]〔60B3D0 直拷 +976〕〔证据: va=0060B3D0〕
    unsigned int    uCfgF980;                      // +0x03D4 (980) x1  【推断】配置表项[5]〔60B3D0 直拷 +980〕〔证据: va=0060B3D0〕
    unsigned char _unused_03D8[4];
    unsigned int    uCfgA988;                      // +0x03DC (988) x1  【推断】配置表项[0]〔60B3D0 直拷 +988〕〔证据: va=0060B3D0〕
    unsigned int    uCfgB992;                      // +0x03E0 (992) x1  【推断】配置表项[1]〔60B3D0 直拷 +992〕〔证据: va=0060B3D0〕
    unsigned char   bCfgC996;                      // +0x03E4 (996) x1  【推断】配置表项[2] 非零化标志〔60B3D0: *(this+996)=result[2]!=0〕〔证据: va=0060B3D0〕
    unsigned char _unused_03E5[23];
    unsigned int    pAnimHandleArr;                // +0x03FC (1020) x1  【推断】动画对象句柄数组起点（3 元素；60B3D0 循环 3 次逐个填充）〔证据: va=0060B3D0〕
    unsigned char _unused_0400[76];

    // ---- 区块 6：妖精档位与漂浮循环（62C5F0 参数装载 / 62C510 漂浮音驱动） ----
    unsigned int    nFairyGrade;                   // +0x044C (1100) x1  【推断】妖精档位/缩放档（编号末位 0/1/2）〔62C5F0 解析末位写入；62CAD0 按档取 7000/15000/30000 ms 霸体时长；62C510 参与资源索引 +712+4*档+32〕〔证据: va=0062C510〕
    unsigned char _unused_0450[1];                 // +0x0450.. 同区 +1104 为多目标吸取开关（62C5F0 由十位写、（本类无多目标吸取分支）），本候选表未收录该行
    unsigned char   bFloatLoopLatch;               // +0x0451 (1105) x2  漂浮音一次性门〔62C510 首帧播 TINGKERBELL_FLOAT_LOOP 后置 1；62C5F0 装载时清 0〕〔证据: va=0062C510〕
    unsigned char _unused_0452[15];                // +0x0452.. 同区 +1106 为吸取一次性门（（本类无吸取门）），本候选表未收录
    unsigned char   bCycleRstA;                    // +0x0461 (1121) x2  【推断】漂浮周期复位字节A〔62C510 首播与 10s 周期到期时清 0〕〔证据: va=0062C510〕
    unsigned char   bCycleRstB;                    // +0x0462 (1122) x2  【推断】漂浮周期复位字节B〔62C510 同上成对清 0〕〔证据: va=0062C510〕
    unsigned char _unused_0463[9];
    unsigned int    nCycleDeadline;                // +0x046C (1132) x1  【推断】漂浮循环周期截止时刻〔62C510: clock_now(内嵌计时器 +1108) >= 此值 → 重发并续期 10000ms〕〔证据: va=0062C510〕
};
#pragma pack(pop)

// 统计: 字段行 37 / 未命名保留 0 / 标【推断】24 / 末尾偏移 +0x0470

#endif
