// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNScriptLoader             主虚表槽位数: 14   字段数: 16
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNScriptLoader -> IFileResourceManager
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// 证据函数（src 头注释）: 0x438F50 CNScriptLoader__vmt0 —— 删除析构转发
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNScriptLoader_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     nPathId4              ; // +0x0004 (4) x1  资源 id/句柄号（0x697B30：*(this+4) = nArg2）（证据: va=00697B30）
    unsigned short   uPathTail7            ; // +0x0007 (7) x1  路径串结尾词（0x697B30：(u16*)(this+7) 补反斜杠+终止符；与 +8 串缓冲尾部重叠）；与上一宽槽（结束于 +0x0007）字节重叠，系字节级别名（两行均直证）】（证据: va=00697B30）
    char             szPath8               ; // +0x0008 (8) x1  路径串缓冲起点（0x697B30 strcpy(this+8, pArg3)）；与上一宽槽（结束于 +0x0008）字节重叠，系字节级别名（两行均直证）】（证据: va=00697B30）
    unsigned char _unused_0x0009      [11]; // +0x0009..0x0013 未观测
    unsigned char    field_0014            ; // +0x0014 (20) x1  工厂产物对象字段（0x4D2D60 属性块解析器工厂 switch：本条为被创建对象 pObj+20 的清零写点，非本类布局 → 保留占位名）（证据: va=004D2D60）
    unsigned char _unused_0x0015      [15]; // +0x0015..0x0023 未观测
    unsigned int     field_0024            ; // +0x0024 (36) x1  工厂产物对象字段（0x4D2D60：pObj+36 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned int     field_0028            ; // +0x0028 (40) x2  工厂产物对象字段（0x4D2D60：pObj+40 容量判据；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x002C      [4]; // +0x002C..0x002F 未观测
    unsigned int     field_0030            ; // +0x0030 (48) x2  工厂产物对象字段（0x4D2D60：pObj+48 指针判据；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned int     field_0034            ; // +0x0034 (52) x1  工厂产物对象字段（0x4D2D60：pObj+52 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned int     field_0038            ; // +0x0038 (56) x1  工厂产物对象字段（0x4D2D60：pObj+56 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x003C      [36]; // +0x003C..0x005F 未观测
    unsigned char    field_0060            ; // +0x0060 (96) x1  工厂产物对象字段（0x4D2D60：pObj+96 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x0061      [15]; // +0x0061..0x006F 未观测
    unsigned int     field_0070            ; // +0x0070 (112) x1  工厂产物对象字段（0x4D2D60：pObj+112 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned int     field_0074            ; // +0x0074 (116) x2  工厂产物对象字段（0x4D2D60：pObj+116 容量判据；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x0078      [80]; // +0x0078..0x00C7 未观测
    unsigned char    field_00C8            ; // +0x00C8 (200) x1  工厂产物对象字段（0x4D2D60：pObj+200 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x00C9      [15]; // +0x00C9..0x00D7 未观测
    unsigned int     field_00D8            ; // +0x00D8 (216) x1  工厂产物对象字段（0x4D2D60：pObj+216 清零；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned int     field_00DC            ; // +0x00DC (220) x2  工厂产物对象字段（0x4D2D60：pObj+220 容量判据；非本类布局 → 占位）（证据: va=004D2D60）
    unsigned char _unused_0x00E0      [40]; // +0x00E0..0x0107 未观测
    unsigned int     nResId264             ; // +0x0108 (264) x2  资源 id 结果槽（0x697B30：*(this+264) = nArg4 收尾）（证据: va=00697B30）
};
#pragma pack(pop)

// 统计: 字段行 16 / 未命名 12 / 标【推断】0 / 末尾偏移 +0x010C
