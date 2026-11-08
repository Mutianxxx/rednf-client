// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNGrenselosBunker  主虚表槽位数: 189   字段数: 34
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> CNRDPassiveObject×4 -> CNMapObject -> CNGrenselosBunker
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGrenselosBunker_Fields {
    // ---- 区块 1：继承 CNMapObject/CNRDPassiveObject 基类区（继承段） ----
    unsigned char _base_0x0000      [96]; // +0x0000..0x005F 继承 CNMapObject 族（CNRDPassiveObject） 前 0x60 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      nKindId96           ; // +0x0060 (96) x1  物件类别 id 字（62BB60 重置写 545 标识）（证据 va=0062BB60）
    unsigned char _unused_0x0064    [20]; // +0x0064..0x0077 未观测
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00499020）

    // ---- 区块 2：基类时刻同步与参数灌入区 ----
    unsigned char _unused_0x007C    [108]; // +0x007C..0x00E7 未观测
    unsigned char     bSyncSwitch         ; // +0x00E8 (232) x2  基类时刻同步开关位（499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9    [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncValue          ; // +0x00F4 (244) x4  基类浮点时刻槽（499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bParamSlotA         ; // +0x00F8 (248) x1  基类四元组字节槽 1（42A8D0 CNRDObject__vmt11C 批量写 +248..+260）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9    [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nParamSlotB         ; // +0x00FC (252) x1  基类四元组 dword 槽 2（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char     bParamSlotC         ; // +0x0100 (256) x1  基类四元组字节槽 3（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101    [3]; // +0x0101..0x0103 未观测
    unsigned int      nParamSlotD         ; // +0x0104 (260) x1  基类四元组 dword 槽 4（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0108    [100]; // +0x0108..0x016B 未观测
    unsigned int      pAnimNameStr        ; // +0x016C (364) x1  动画件名 SSO 内联首址（62BB60 取址交 sub_4C3640）（证据 va=0062BB60）
    unsigned char _unused_0x0170    [16]; // +0x0170..0x017F 未观测
    unsigned int      nAnimNameCap        ; // +0x0180 (384) x1  动画件名 SSO 容量判据（62BB60 <0x10 走内联）（证据 va=0062BB60）

    // ---- 区块 3：帧时刻覆盖（基类 4E5C10） ----
    unsigned char _unused_0x0184    [254]; // +0x0184..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）

    // ---- 区块 4：基类表现壳槽区 ----
    unsigned char _unused_0x0288    [28]; // +0x0288..0x02A3 未观测
    unsigned int      nResetFlag676       ; // +0x02A4 (676) x1  重置标志（62BB60 置 1）（证据 va=0062BB60）
    unsigned int      nHpCur680           ; // +0x02A8 (680) x3  当前 HP（62B890 受击比对：< +684/2 触发半血演出）（证据 va=004E1FE0）
    unsigned int      nHpMax684           ; // +0x02AC (684) x3  最大 HP（62B890 半血阈值分母）（证据 va=004E1FE0）
    unsigned int      nSnapshot688        ; // +0x02B0 (688) x1  表现/名字快照[2]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      nSnapshot692        ; // +0x02B4 (692) x1  表现/名字快照[3]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      nSnapshot696        ; // +0x02B8 (696) x1  表现/名字快照[4]（4E1FE0）（证据 va=004E1FE0）
    unsigned char     bSnapshot700        ; // +0x02BC (700) x1  表现/名字快照[20]（4E1FE0）（证据 va=004E1FE0）
    unsigned char     bSnapshot701        ; // +0x02BD (701) x1  表现/名字快照[21]（4E1FE0）（证据 va=004E1FE0）
    unsigned char _unused_0x02BE    [2]; // +0x02BE..0x02BF 未观测
    unsigned int      nSnapshot704        ; // +0x02C0 (704) x1  表现/名字快照[24]（4E1FE0）（证据 va=004E1FE0）

    // ---- 区块 5：载荷缓冲与配置表直拷面（5FFF80 / 60B3D0） ----
    unsigned char _unused_0x02C4    [256]; // +0x02C4..0x03C3 未观测
    unsigned int      nBlobSize           ; // +0x03C4 (964) x1  载荷缓冲字节数（5FFF80：*(this+964)=Size）（证据 va=005FFF80）
    unsigned int      pBlobData           ; // +0x03C8 (968) x3  载荷缓冲指针（5FFF80：旧块 free 后 operator new(Size) 存入）（证据 va=005FFF80）
    unsigned char _unused_0x03CC    [108]; // +0x03CC..0x0437 未观测
    unsigned int      nAnimIdx1080        ; // +0x0438 (1080) x1  开合插值起始帧号（62B890）（证据 va=0062B890）
    unsigned int      nAnimIdx1084        ; // +0x043C (1084) x1  开合插值结束帧号（62B890：(+1084 − +1080)/12）（证据 va=0062B890）

    // ---- 区块 6：子类状态/时钟/名单槽区（开合插值 / 投掷名单） ----
    unsigned char _unused_0x0440    [12]; // +0x0440..0x044B 未观测
    unsigned char     bOpenDoor1100       ; // +0x044C (1100) x5  开门位（62B890/62BC70）（证据 va=0062B890）
    unsigned char _unused_0x044D    [3]; // +0x044D..0x044F 未观测
    unsigned int      nResetClock1104     ; // +0x0450 (1104) x1  重置时刻戳（62BB60 写 clock_now(this+36)）（证据 va=0062BB60）
    unsigned int      pAttach1108         ; // +0x0454 (1108) x1  挂件对象（62BB60 new 重建后存入）（证据 va=0062BB60）
    unsigned int      nThrowTick1112      ; // +0x0458 (1112) x4  投掷节拍计数（62BB60/62BEF0 清 0）（证据 va=0062BEF0）
    unsigned char _unused_0x045C    [4]; // +0x045C..0x045F 未观测
    unsigned int      pThrowList1120      ; // +0x0460 (1120) x2  投掷名单缓冲（62BB60 free 后清 0）（证据 va=0062BB60）
    unsigned int      nThrowCnt1124       ; // +0x0464 (1124) x1  投掷名单计数（62BB60 清 0）（证据 va=0062BB60）
    unsigned int      nThrowCap1128       ; // +0x0468 (1128) x1  投掷名单容量（62BB60 清 0）（证据 va=0062BB60）
};
#pragma pack(pop)

// 统计: 字段行 34 / 已命名 34 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x046C
