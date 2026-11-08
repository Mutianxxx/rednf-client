// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNRDParticleCreater        主虚表槽位数: 23   字段数: 14
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDParticleCreater
// 族属: 核心对象族
// 依据: ①权威 struct src/cnrd/CNRDObject.h（会话 3 逐行精修 84 槽虚表 + 全字段）与
//        src/cnrd/IRDCollisionObject.h（167 槽命中链主战场）②证据行 va 的 src 函数头注释
// 证据函数（src 头注释）: 0x425210 CNRDParticleCreater__vmt14 —— 虚槽14 发射随机化 /
//   0x425230 CNRDParticleCreater__vmt20 —— 虚槽20 参数块写入 / 0x425260 CNRDParticleCreater__vmt28 —— 虚槽28 区间设置 /
//   0x4252A0 CNRDParticleCreater__vmt40 —— 虚槽40 标志写
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDParticleCreater_Fields {
    // ---- 区块 1：本段直证点（基类布局见 src/cnrd/CNRDObject.h / IRDCollisionObject.h） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     nSnapSrc4             ; // +0x0004 (4) x2  快照源值 A（0x490370：写入 +220）（证据: va=00490370）
    unsigned int     nSnapSrc8             ; // +0x0008 (8) x1  快照源值 B（0x490370：写入 +224）（证据: va=00490370）
    unsigned int     nSnapSrc12            ; // +0x000C (12) x1  快照源值 C（0x490370：写入 +228）（证据: va=00490370）
    unsigned char _unused_0x0010      [88]; // +0x0010..0x0067 未观测
    unsigned int     aParamBlk104          ; // +0x0068 (104) x1  参数块起址（0x425230 vmt20：qmemcpy 72 字节至 +104；候选表 void 系取址式误判，按 32 位占位声明）（候选表 void 按 32 位目标 4 字节占位声明）（证据: va=00425230）
    unsigned char _unused_0x006C      [81]; // +0x006C..0x00BC 未观测
    unsigned char    bFlag189              ; // +0x00BD (189) x1  复位字节 A（0x490370 清 0）【推断】（证据: va=00490370）
    unsigned char    bFlag190              ; // +0x00BE (190) x1  复位字节 B（0x490370 清 0）【推断】（证据: va=00490370）
    unsigned char _unused_0x00BF      [13]; // +0x00BF..0x00CB 未观测
    unsigned int     pSubAnim204           ; // +0x00CC (204) x1  子动画链指针（0x490370：*(this+204) = nArg2 子链挂接）（证据: va=00490370）
    unsigned int     nField208             ; // +0x00D0 (208) x1  子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）
    unsigned int     nField212             ; // +0x00D4 (212) x1  子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）
    unsigned char    bField216             ; // +0x00D8 (216) x1  子链标志字节（0x490370 清 0；0x4903D0 开关位 +217 相邻）【推断】（证据: va=00490370）
    unsigned char _unused_0x00D9      [3]; // +0x00D9..0x00DB 未观测
    unsigned int     nSnapDst220           ; // +0x00DC (220) x1  快照副本 A（0x490370：← this+4）（证据: va=00490370）
    unsigned int     nSnapDst224           ; // +0x00E0 (224) x1  快照副本 B（0x490370：← this+8）（证据: va=00490370）
    unsigned int     nSnapDst228           ; // +0x00E4 (228) x1  快照副本 C（0x490370：← this+12）（证据: va=00490370）
    unsigned int     nSentinel232          ; // +0x00E8 (232) x1  哨兵槽（0x490370 置 -1）（证据: va=00490370）
};
#pragma pack(pop)

// 统计: 字段行 14 / 未命名 0 / 标【推断】5 / 末尾偏移 +0x00EC
