// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNGrabbingLegOfLotus 主虚表槽位数: 177   字段数: 29
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> CNRDPassiveObject×4 -> CNGrabbingLegOfLotus
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGrabbingLegOfLotus_Fields {
    // ---- 区块 1：继承 CNRDPassiveObject 基类区（宿主组件/动画对象；继承段） ----
    unsigned char _base_0x0000      [112]; // +0x0000..0x006F 继承 CNRDObject/IRDCollisionObject 前 0x70 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      pHostComp           ; // +0x0070 (112) x2  宿主组件指针（26330/26458 邻链 vt+112 摆位）（证据 va=0061DAD0）
    unsigned char _unused_0x0074    [4]; // +0x0074..0x0077 未观测
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x007C    [20]; // +0x007C..0x008F 未观测
    unsigned int      pFrameList144       ; // +0x0090 (144) x2  帧件列表基址（26722 取 *(*(+144)) 交 vt+196 回帧表[0]）（证据 va=0061DAD0）

    // ---- 区块 2：基类时刻同步与参数灌入区（4 元组槽 / 帧同步槽） ----
    unsigned char _unused_0x0094    [84]; // +0x0094..0x00E7 未观测
    unsigned char     bSyncSwitch         ; // +0x00E8 (232) x2  基类时刻同步开关位（499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9    [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncValue          ; // +0x00F4 (244) x4  基类浮点时刻槽（499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bGrabIdx248         ; // +0x00F8 (248) x1  抓取序号（26440：*(+248) > 1 门）（证据 va=0042A8D0）
    unsigned char _unused_0x00F9    [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nGrabTarget252      ; // +0x00FC (252) x1  抓取目标 id（26440：nArg2 == *(+252) 判命中自身抓取目标；26450 对 *(+252) 调 vt+120）（证据 va=0042A8D0）
    unsigned char     bParamSlotC         ; // +0x0100 (256) x1  基类四元组字节槽 3（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101    [3]; // +0x0101..0x0103 未观测
    unsigned int      nParamSlotD         ; // +0x0104 (260) x1  基类四元组 dword 槽 4（42A8D0）【基类字段】（证据 va=0042A8D0）

    // ---- 区块 3：帧时刻覆盖（基类 4E5C10） ----
    unsigned char _unused_0x0108    [378]; // +0x0108..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）

    // ---- 区块 4：表现/名字快照块与资源表（4E1FE0 28 字节直拷 + 60B3D0 装载） ----
    unsigned char _unused_0x0288    [32]; // +0x0288..0x02A7 未观测
    unsigned int      nSnapshot680        ; // +0x02A8 (680) x1  表现/名字快照[0]（4E1FE0 由 28 字节源块直拷）（证据 va=004E1FE0）
    unsigned int      nSnapshot684        ; // +0x02AC (684) x1  表现/名字快照[1]（4E1FE0）（证据 va=004E1FE0）
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
    unsigned char _unused_0x03CC    [13]; // +0x03CC..0x03D8 未观测
    unsigned char     bGrabLatch985       ; // +0x03D9 (985) x2  抓取一次性门（26478：*(u8*)(+985)==0）（证据 va=0061D650）
    unsigned char _unused_0x03DA    [18]; // +0x03DA..0x03EB 未观测
    unsigned int      pWrap1004           ; // +0x03EC (1004) x1  捕获坐标对象（26487：*(+1004) = pArg3[2] 取第三参）（证据 va=0061D650）
    unsigned int      pVictim1008         ; // +0x03F0 (1008) x6  被抓目标引用（26488：*(+1008)=pArg2；26712 vmt12C：nArg2==*(+1008) 时联动移除）（证据 va=0061DAD0）
    unsigned int      uGrabA1012          ; // +0x03F4 (1012) x1  抓取参数 A（26491：*(+1012)=v5）【推断】（证据 va=0061D650）
    unsigned int      uGrabB1016          ; // +0x03F8 (1016) x1  抓取参数 B（26494：*(+1016)=v7）【推断】（证据 va=0061D650）
    unsigned int      nGrabOwn1020        ; // +0x03FC (1020) x1  目标对象槽（26495：*(+1020)=vt+128()）【推断】（证据 va=0061D650）
};
#pragma pack(pop)

// 统计: 字段行 29 / 已命名 29 / 未命名 0 / 标【推断】3 / 末尾偏移 +0x0400
