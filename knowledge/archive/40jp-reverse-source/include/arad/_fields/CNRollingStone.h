// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNRollingStone     主虚表槽位数: 177   字段数: 30
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> CNRDPassiveObject×4 -> CNRollingStone
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRollingStone_Fields {
    // ---- 区块 1：继承 CNRDPassiveObject 基类区（宿主组件/动画对象；继承段） ----
    unsigned char _base_0x0000      [112]; // +0x0000..0x006F 继承 CNRDObject/IRDCollisionObject 前 0x70 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      pHostComp           ; // +0x0070 (112) x5  宿主组件指针（620A10 vmtC 尾调 sub_49FD20(*(+112))）（证据 va=00620A10）
    unsigned char _unused_0x0074    [4]; // +0x0074..0x0077 未观测
    unsigned int      pAnimObj            ; // +0x0078 (120) x7  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00620A10）

    // ---- 区块 2：基类时刻同步与参数灌入区（4 元组槽 / 帧同步槽） ----
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
    unsigned int      pAnimNameStr        ; // +0x016C (364) x1  动画件名缓冲 SSO 内联首址（60B3D0：+384<0x10 时取 this+364 名交 sub_4C3640 建动画）（证据 va=00620A10）
    unsigned char _unused_0x0170    [16]; // +0x0170..0x017F 未观测
    unsigned int      nAnimNameCap        ; // +0x0180 (384) x1  动画件名 SSO 容量判据（<0x10 走内联缓冲；60B3D0）【推断】（证据 va=00620A10）

    // ---- 区块 3：帧时刻覆盖（基类 4E5C10） ----
    unsigned char _unused_0x0184    [254]; // +0x0184..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）

    // ---- 区块 4：表现/名字快照块与资源表（4E1FE0 28 字节直拷 + 60B3D0 装载） ----
    unsigned char _unused_0x0288    [32]; // +0x0288..0x02A7 未观测
    unsigned int      nHpCur680           ; // +0x02A8 (680) x2  当前 HP（620960 vmt2B4：*(+680) > 0 才算受击）（证据 va=004E1FE0）
    unsigned int      nSnapshot684        ; // +0x02AC (684) x1  表现/名字快照[1]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      nStoneKind688       ; // +0x02B0 (688) x2  滚石种类档（620A10 vmtC 置 2）【推断】（证据 va=00620A10）
    unsigned int      nSnapshot692        ; // +0x02B4 (692) x1  表现/名字快照[3]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      nSnapshot696        ; // +0x02B8 (696) x1  表现/名字快照[4]（4E1FE0）（证据 va=004E1FE0）
    unsigned char     bSnapshot700        ; // +0x02BC (700) x1  表现/名字快照[20]（4E1FE0）（证据 va=004E1FE0）
    unsigned char     bSnapshot701        ; // +0x02BD (701) x1  表现/名字快照[21]（4E1FE0）（证据 va=004E1FE0）
    unsigned char _unused_0x02BE    [2]; // +0x02BE..0x02BF 未观测
    unsigned int      nSnapshot704        ; // +0x02C0 (704) x1  表现/名字快照[24]（4E1FE0）（证据 va=004E1FE0）
    unsigned char _unused_0x02C4    [4]; // +0x02C4..0x02C7 未观测
    unsigned int      pResTbl712          ; // +0x02C8 (712) x3  资源/动画句柄表基指针（620A10 读 *(+712)）（证据 va=00620A10）

    // ---- 区块 5：载荷缓冲与配置表直拷面（5FFF80 / 60B3D0） ----
    unsigned char _unused_0x02CC    [248]; // +0x02CC..0x03C3 未观测
    unsigned int      nBlobSize           ; // +0x03C4 (964) x1  载荷缓冲字节数（5FFF80：*(this+964)=Size）（证据 va=005FFF80）
    unsigned int      pBlobData           ; // +0x03C8 (968) x3  载荷缓冲指针（5FFF80：旧块 free 后 operator new(Size) 存入）（证据 va=005FFF80）
    unsigned char     bActivate972        ; // +0x03CC (972) x1  激活位（620680：*((u8*)+972)!=0 才进受击分支；620A10 置 1）（证据 va=00620A10）
    unsigned char _unused_0x03CD    [7]; // +0x03CD..0x03D3 未观测
    float             fSpeed980           ; // +0x03D4 (980) x1  速率/HP 比浮点（620960：fld_3D4 = nArg3 / *(float*)(+980) * 100）（证据 va=00620960）
    unsigned char     bStateBit984        ; // +0x03D8 (984) x1  状态字节（620680/620A10 读写）【推断】（证据 va=00620A10）
    unsigned char _unused_0x03D9    [3]; // +0x03D9..0x03DB 未观测
    unsigned int      pFrameObj988        ; // +0x03DC (988) x1  当前帧件对象（620A10 写 pThis_16C）（证据 va=00620A10）
    unsigned char _unused_0x03E0    [8]; // +0x03E0..0x03E7 未观测
    unsigned int      pAttacker1000       ; // +0x03E8 (1000) x1  攻击者引用（620960 vmt2B4：*(+1000)=命中者 vt+576()）（证据 va=00620960）
};
#pragma pack(pop)

// 统计: 字段行 30 / 已命名 30 / 未命名 0 / 标【推断】3 / 末尾偏移 +0x03EC
