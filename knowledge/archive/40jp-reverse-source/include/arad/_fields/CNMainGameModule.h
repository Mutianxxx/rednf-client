// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNMainGameModule           主虚表槽位数: 5    字段数: 9
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNMainGameModule -> nengine__IModule -> nengine__IObject -> nengine__IAppendDraw
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNMainGameModule_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [16]; // +0x0000..0x000F 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pFxManager16          ; // +0x0010 (16) x2  演出/镜头管理器指针（CameraFxManager*；CNMainGameModule.cpp +0x10 定案，0x4294E0 接收者）（证据: va=00444C60）
    unsigned int     nFadeState20          ; // +0x0014 (20) x3  fade 状态（0 无 / 1 进场淡入 / 2 过场 / 3 退场淡出 / 4 黑屏；0x444C60）（证据: va=00444C60）
    unsigned char _unused_0x0018      [13]; // +0x0018..0x0024 未观测
    unsigned char    bFadeFlag37           ; // +0x0025 (37) x1  淡入收尾标志 A（0x444C60 case 1 置 0）【推断】（证据: va=00444C60）
    unsigned char    bFadeFlag38           ; // +0x0026 (38) x1  淡入收尾标志 B（0x444C60 与 +37 同批清 0）【推断】（证据: va=00444C60）
    unsigned char _unused_0x0027      [13]; // +0x0027..0x0033 未观测
    unsigned int     nEnterParam52         ; // +0x0034 (52) x2  进副本参数对 A（0x444C60：sub_475810(..., this+52, this+56)）（证据: va=00444C60）
    unsigned int     nEnterParam56         ; // +0x0038 (56) x2  进副本参数对 B（0x444C60 同批；sub_4284C0 收尾）（证据: va=00444C60）
    unsigned int     nFadeValue60          ; // +0x003C (60) x7  fade 值（0..255；0x444C60 镜像到 8F8528+2484）（证据: va=00444C60）
    unsigned char _unused_0x0040      [42]; // +0x0040..0x0069 未观测
    unsigned char    bClockUnfreeze106     ; // +0x006A (106) x1  模块时钟解冻门（0x444C60：非 0 才 clock_unfreeze(this+92)）（证据: va=00444C60）
    unsigned char _unused_0x006B      [13]; // +0x006B..0x0077 未观测
    unsigned int     nLastClock120         ; // +0x0078 (120) x2  模块时钟上次读数（0x444C60：dt = (now − last) × 0.001 供场景推进）（证据: va=00444C60）
};
#pragma pack(pop)

// 统计: 字段行 9 / 未命名 0 / 标【推断】2 / 末尾偏移 +0x007C
