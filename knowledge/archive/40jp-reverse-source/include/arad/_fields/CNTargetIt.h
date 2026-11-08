// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNTargetIt                 主虚表槽位数: 37   字段数: 8
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNTargetIt -> CNRDAuraMaster -> IRDAppendage
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// 证据函数（src 头注释）: 0x64F2B0 CNTargetIt__vmt14 —— CNTargetIt__vmt14 生成槽（4938F0/491D00） /
//   0x64F300 CNTargetIt__vmt84 —— CNTargetIt__vmt84 受击事件槽（15 行） /
//   0x64F3E0 CNTargetIt__vmt24 —— CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5 /
//   0x64F600 CNTargetIt__vmt78 —— CNTargetIt__vmt78 生效槽（60FA60）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNTargetIt_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x4  宿主对象（各槽 *(this+4) 取 vt+308/192 判存活与高度）（证据: va=0064F3E0）
    unsigned char _unused_0x0008      [28]; // +0x0008..0x0023 未观测
    unsigned int     nTargetHostId36       ; // +0x0024 (36) x4  目标宿主 id 匹配槽（vmt24：== 命中者 +8352 槽且非 0 才锁定；vmt84 判命中者 +2088 == *(this+9)）【推断】（证据: va=0064F3E0）
    unsigned char _unused_0x0028      [84]; // +0x0028..0x007B 未观测
    unsigned int     pAnimObj124           ; // +0x007C (124) x2  光环/动画对象（0x64A190 族同址：非空且宿主非冻结才 4938F0/491D00）（证据: va=0064A190）
    unsigned char _unused_0x0080      [4]; // +0x0080..0x0083 未观测
    unsigned int     nCfg132               ; // +0x0084 (132) x2  参数槽（vmt24：sub_47EFD0(*(char**)(this+128), 3, *(this+132), ...) 第二参）（证据: va=0064F3E0）
    unsigned char _unused_0x0088      [24]; // +0x0088..0x009F 未观测
    unsigned int     pVec160               ; // +0x00A0 (160) x4  向量 begin（vmt1C/vmt20：非 0 先 free 再三清；0x64F390 (164−160)>>2 = 元素数）（证据: va=0064F940）
    unsigned int     pVec164               ; // +0x00A4 (164) x2  向量 end（vmt1C/vmt20 清 0）（证据: va=0064F940）
    unsigned int     pVec168               ; // +0x00A8 (168) x2  向量 cap（vmt1C/vmt20 清 0）（证据: va=0064F940）
    unsigned int     pAnimObj172           ; // +0x00AC (172) x1  动画件对象（vmt14：sub_4938F0(*(this+172)) + sub_491D00 驱动）（证据: va=0064F2B0）
};
#pragma pack(pop)

// 统计: 字段行 8 / 未命名 0 / 标【推断】1 / 末尾偏移 +0x00B0
