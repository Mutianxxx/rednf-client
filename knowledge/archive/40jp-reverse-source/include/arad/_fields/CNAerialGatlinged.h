// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNAerialGatlinged          主虚表槽位数: 30   字段数: 10
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNAerialGatlinged -> IRDAppendage
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNAerialGatlinged_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x1  宿主对象（vmt4/vmt10 经 *(this+4) 调 vt+144/152 播动作与取动作号）（证据: va=005F9970）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     pActor80              ; // +0x0050 (80) x11 关联角色对象（vmt10：*(this+80) vt+152 取动作号；其 +9368 为门标志）（证据: va=005F9530）
    unsigned int     nFromX84              ; // +0x0054 (84) x5  插值起点 X（vmt10 sub_4049C0(值, 起点, t, 段长) 起点参）（证据: va=005F9530）
    unsigned int     nFromY88              ; // +0x0058 (88) x5  插值起点 Y（证据: va=005F9530）
    unsigned int     nFromZ92              ; // +0x005C (92) x4  插值起点 Z（证据: va=005F9530）
    unsigned int     nToX96                ; // +0x0060 (96) x4  插值终点 X / 落点偏移（vmt4：*(this+96) + 宿主 vt+120 取世界 X）（证据: va=005F9970）
    int              nToY100               ; // +0x0064 (100) x4  插值终点 Y（证据: va=005F9530）
    unsigned int     nToZ104               ; // +0x0068 (104) x4  插值终点 Z（vmt4：*(this+104) + 宿主 y + 高/2）（证据: va=005F9970）
    unsigned char _unused_0x006C      [12]; // +0x006C..0x0077 未观测
    unsigned char    bGate120              ; // +0x0078 (120) x2  近段修正门字节（vmt10：非 0 且 clock_now(this+108) ≤ 50 时 ±1 修正）（证据: va=005F9530）
    unsigned char _unused_0x0079      [15]; // +0x0079..0x0087 未观测
    unsigned char    bFired136             ; // +0x0088 (136) x3  演出已播标志（vmt4 播 KnockSmall.ani + "BBQ_STUCK" 后置 1 防重播）（证据: va=005F9970）
};
#pragma pack(pop)

// 统计: 字段行 10 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x0089
