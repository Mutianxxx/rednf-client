// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNNapalmBomb       主虚表槽位数: 177   字段数: 32
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> CNRDPassiveObject×4 -> CNNapalmBomb
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNNapalmBomb_Fields {
    // ---- 区块 1：继承 CNRDPassiveObject 基类区（宿主组件/动画对象；继承段） ----
    unsigned char _base_0x0000      [120]; // +0x0000..0x0077 继承 CNRDObject/IRDCollisionObject 前 0x78 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x007C    [20]; // +0x007C..0x008F 未观测
    unsigned int      pFrameList144       ; // +0x0090 (144) x1  帧件列表基址（61AFC0 vmt10 循环 *(*(+144)+i*4) 复位动画件）（证据 va=0061AFC0）

    // ---- 区块 2：基类时刻同步与参数灌入区（4 元组槽 / 帧同步槽） ----
    unsigned char _unused_0x0094    [84]; // +0x0094..0x00E7 未观测
    unsigned char     bSyncSwitch         ; // +0x00E8 (232) x2  基类时刻同步开关位（499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9    [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncValue          ; // +0x00F4 (244) x4  基类浮点时刻槽（499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bBombParam248       ; // +0x00F8 (248) x1  燃烧参数（61AE90 vmt2A8：fld_e248 = *(u8*)(+248)² 面积换算）【推断】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9    [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nParamSlotB         ; // +0x00FC (252) x1  基类四元组 dword 槽 2（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char     bParamSlotC         ; // +0x0100 (256) x1  基类四元组字节槽 3（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101    [3]; // +0x0101..0x0103 未观测
    unsigned int      pBuf260             ; // +0x0104 (260) x1  参数缓冲地址（61B980 vmt14C pThis_104 = this+260）【推断】（证据 va=0042A8D0）

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
    unsigned int      nSize704            ; // +0x02C0 (704) x2  尺寸/体积档（61AE90：fld_2C0 = *(this+704) 传几何族尺寸参）（证据 va=004E1FE0）
    unsigned char _unused_0x02C4    [16]; // +0x02C4..0x02D3 未观测
    float             fArea724            ; // +0x02D4 (724) x1  燃烧面积浮点（61AE90：*(float*)(+724) = sub_47EFD0(...)）（证据 va=0061AE90）

    // ---- 区块 5：载荷缓冲与配置表直拷面（5FFF80 / 60B3D0） ----
    unsigned char _unused_0x02D8    [236]; // +0x02D8..0x03C3 未观测
    unsigned int      nBlobSize           ; // +0x03C4 (964) x1  载荷缓冲字节数（5FFF80：*(this+964)=Size）（证据 va=005FFF80）
    unsigned int      pBlobData           ; // +0x03C8 (968) x3  载荷缓冲指针（5FFF80：旧块 free 后 operator new(Size) 存入）（证据 va=005FFF80）
    unsigned char _unused_0x03CC    [1]; // +0x03CC..0x03CC 未观测
    unsigned char     bLanded973          ; // +0x03CD (973) x2  落地一次性门（61AE90：==0 才做落点初始化并置 1）（证据 va=0061AE90）
    unsigned char _unused_0x03CE    [2]; // +0x03CE..0x03CF 未观测
    unsigned int      pTarget976          ; // +0x03D0 (976) x3  落点目标引用（61AE90：*(+976)=命中者 vt+388()）（证据 va=0061AE90）
    unsigned char _unused_0x03D4    [4]; // +0x03D4..0x03D7 未观测
    unsigned int      nBurnClock984       ; // +0x03D8 (984) x3  燃烧时钟基准（61AFC0 vmt10：clock_now 与 (+984)+1000 / (+1016)−1000 双向判窗口）（证据 va=0061AFC0）
    float             fBurnRise988        ; // +0x03DC (988) x1  燃烧上升率（61AE90：fld = sub_47EF20(1,...)/sub_47EF20(1,1,...) 归一）（证据 va=0061AE90）
    unsigned int      nBurnTicks992       ; // +0x03E0 (992) x1  燃烧跳动数（61AE90：*(+992)=sub_47EF20(2,...)/2）（证据 va=0061AE90）
    unsigned int      pEmitter996         ; // +0x03E4 (996) x1  燃烧发射器句柄（61AE90 交 sub_607260(+996,...) 建发射器）（证据 va=0061AE90）
    unsigned char _unused_0x03E8    [16]; // +0x03E8..0x03F7 未观测
    unsigned int      nBurnT0_1016        ; // +0x03F8 (1016) x2  燃烧窗口起始时刻（61AFC0 vmt10：clock_now < +1016 − 1000 判窗口）（证据 va=0061AFC0）
    float             pAnimHandleArr      ; // +0x03FC (1020) x1  【推断】动画对象句柄数组起点（3 元素；60B3D0 循环 3 次逐个填充）（证据 va=0061AE90）
    float             nBurnT1_1024        ; // +0x0400 (1024) x1  燃烧窗口结束时刻（61AFC0 同源；61AE90 写 *(float*)(+1024)）（证据 va=0061AE90）
};
#pragma pack(pop)

// 统计: 字段行 32 / 已命名 32 / 未命名 0 / 标【推断】3 / 末尾偏移 +0x0404
