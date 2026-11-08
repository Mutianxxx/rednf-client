// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNVoid                     主虚表槽位数: 177  字段数: 19
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNVoid -> CNRDPassiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger
// 族属: PO弹道/投射物族
// 依据: ①PO 通用偏移表（batchB 已定案同名沿用）：this+120 动画对象 / +642..644 帧覆盖 / +680..704 表现名字快照块〔0x4E1FE0〕
//        ②证据行 va 的 src 函数头注释 ③同族 17 类同构（候选偏移签名一致）
// 证据函数（src 头注释）: CNVoid 析构基座 → sub_4E2040
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNVoid_Fields {
    // ---- 区块 1：继承 CNRDPassiveObject 段（动画对象/帧同步/参数灌入/帧覆盖〔0x499020 族〕） ----
    unsigned char _base_0x0000        [120]; // +0x0000..0x0077 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pAnimObj              ; // +0x0078 (120) x6  基类动画对象指针（★全库通用 this+120；src/cnrd/CNRDObject.h +0x078 animObj；0x499020/0x499080 帧时刻同步宿主）（证据: va=00499020）
    unsigned char _unused_0x007C      [108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag             ; // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）（证据: va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA             ; // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参 nArg3）（证据: va=00499020）
    unsigned int     nSyncArgB             ; // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参 nArg4）（证据: va=00499020）
    float            fSyncTime             ; // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）（证据: va=00499080）
    unsigned char    bQuad1                ; // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）（证据: va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2                ; // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）（证据: va=0042A8D0）
    unsigned char    bQuad3                ; // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4                ; // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）（证据: va=0042A8D0）
    unsigned char _unused_0x0108      [378]; // +0x0108..0x0281 未观测
    unsigned char    bFrameOv642           ; // +0x0282 (642) x5  帧时刻覆盖开关（0x4E5C10 = IRDCollisionObject 槽 612：非 0 时用 +644 直写帧时刻）（证据: va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int     uFrameOv644           ; // +0x0284 (644) x4  帧时刻覆盖值（0x4E5C10 第四参；与 +642 成对）（证据: va=004E5C10）
    unsigned char _unused_0x0288      [32]; // +0x0288..0x02A7 未观测
    unsigned int     nSnapshot680          ; // +0x02A8 (680) x1  表现/名字快照[0]（0x4E1FE0 由 pArg2[0] 直拷；28 字节块首）（证据: va=004E1FE0）
    unsigned int     nSnapshot684          ; // +0x02AC (684) x1  表现/名字快照[1]（0x4E1FE0 由 pArg2[4] 直拷）（证据: va=004E1FE0）
    unsigned int     nSnapshot688          ; // +0x02B0 (688) x1  表现/名字快照[2]（0x4E1FE0 由 pArg2[8] 直拷）（证据: va=004E1FE0）
    unsigned int     nSnapshot692          ; // +0x02B4 (692) x1  表现/名字快照[3]（0x4E1FE0 由 pArg2[12] 直拷；PO 弹道族多类证据行单独直读此槽）（证据: va=004E1FE0）
    unsigned int     nSnapshot696          ; // +0x02B8 (696) x1  表现/名字快照[4]（0x4E1FE0 由 pArg2[16] 直拷）（证据: va=004E1FE0）
    unsigned char    bSnapshot700          ; // +0x02BC (700) x1  表现/名字快照[20] 字节槽（0x4E1FE0 由 pArg2[20] 直拷）（证据: va=004E1FE0）
    unsigned char    bSnapshot701          ; // +0x02BD (701) x1  表现/名字快照[21] 字节槽（0x4E1FE0 由 pArg2[21] 直拷）（证据: va=004E1FE0）
    unsigned char _unused_0x02BE      [2]; // +0x02BE..0x02BF 未观测
    unsigned int     nSnapshot704          ; // +0x02C0 (704) x1  表现/名字快照[24]（0x4E1FE0 由 pArg2[24] 直拷；快照块末）（证据: va=004E1FE0）
};
#pragma pack(pop)

// 统计: 字段行 19 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x02C4
