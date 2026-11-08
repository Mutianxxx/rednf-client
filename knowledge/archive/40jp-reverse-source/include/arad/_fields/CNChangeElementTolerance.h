// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNChangeElementTolerance   主虚表槽位数: 30   字段数: 8
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNChangeElementTolerance -> IRDAppendage
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// 证据函数（src 头注释）: CNChangeElementTolerance 构造器（元素抗性变更 PO）：a6=标签串存 +27 字符串（+32=容量15）；
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNChangeElementTolerance_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x4  宿主对象（0x603AF0 经 *(this+4) 取宿主 vt+128/124/120 坐标；IRDAppendage 附着宿主）（证据: va=00603AF0）
    unsigned char _unused_0x0008      [72]; // +0x0008..0x004F 未观测
    unsigned int     pParticle80           ; // +0x0050 (80) x4  粒子发射器句柄（0x603AF0 惰性 operator new(0x12C) + sub_428F30("Common/CommonEffect/Particle/RemoveActiveStatus.ptl")）（证据: va=00603AF0）
    unsigned char _unused_0x0054      [4]; // +0x0054..0x0057 未观测
    unsigned int     pVecBegin88           ; // +0x0058 (88) x2  效果条目向量 begin（0x603AF0：(+92 − +88)/12 = 元素数，12 字节步距）（证据: va=00603AF0）
    unsigned int     pVecEnd92             ; // +0x005C (92) x1  效果条目向量 end（证据: va=00603AF0）
    unsigned char _unused_0x0060      [4]; // +0x0060..0x0063 未观测
    unsigned char    bActive100            ; // +0x0064 (100) x1  生效门字节（0x603AF0：非 0 才走粒子演出；场景 4 时须为本机玩家）（证据: va=00603AF0）
    unsigned char    bFired101             ; // +0x0065 (101) x2  已播标志（0x603AF0 末段：非 0 时跳过宿主播音并置 1）（证据: va=00603AF0）
    unsigned char _unused_0x0066      [6]; // +0x0066..0x006B 未观测
    unsigned int     pNameStr108           ; // +0x006C (108) x1  名称串缓冲（0x603AF0：+128 < 0x10 时取 this+108 内联串交宿主 vt+212 播音）（证据: va=00603AF0）
    unsigned char _unused_0x0070      [16]; // +0x0070..0x007F 未观测
    unsigned int     nNameCap128           ; // +0x0080 (128) x1  串容量字段（<0x10 走 SSO 内联分支）（证据: va=00603AF0）
};
#pragma pack(pop)

// 统计: 字段行 8 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x0084
