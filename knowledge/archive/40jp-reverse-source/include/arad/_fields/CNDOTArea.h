// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNDOTArea                  主虚表槽位数: 38   字段数: 16
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNDOTArea -> CNRDAuraMaster -> IRDAppendage
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNDOTArea_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x12 宿主对象（0x6510D0 经 *(this+4) vt+40/+80；光环附着宿主）（证据: va=00651000）
    unsigned char _unused_0x0008      [76]; // +0x0008..0x0053 未观测
    unsigned int     nFrameBase84          ; // +0x0054 (84) x1  帧/时长基准值（0x651000：*(this+84) = nArg2 后按 120 帧制折算新基准写 +152）（证据: va=00651000）
    unsigned char _unused_0x0058      [36]; // +0x0058..0x007B 未观测
    unsigned int     pAnimObj124           ; // +0x007C (124) x2  光环/动画对象（0x64A190 族：非空且宿主非冻结态才 sub_4938F0/491D00）（证据: va=0064A190）
    unsigned int     nParam128             ; // +0x0080 (128) x1  参数字（0x651000：*(this+128) = nArg3）【推断】（证据: va=00651000）
    unsigned int     nField132             ; // +0x0084 (132) x1  清零槽（0x6511E0 复位为 0）【推断】（证据: va=006511E0）
    unsigned int     nField136             ; // +0x0088 (136) x1  清零槽（0x6511E0 复位为 0）【推断】（证据: va=006511E0）
    float            fDmgLo140             ; // +0x008C (140) x2  延滞伤害量 A（0x6510D0：非 273 态取 +140 取负构造 sub_4D6810(CNChangeHp)）（证据: va=006510D0）
    float            fDmgHi144             ; // +0x0090 (144) x2  延滞伤害量 B（0x6510D0：273 态取 +144）（证据: va=006510D0）
    unsigned int     nParam148             ; // +0x0094 (148) x1  参数字（0x651000：*(this+148) = nArg6）【推断】（证据: va=00651000）
    float            fBasis152             ; // +0x0098 (152) x2  时间基准比值浮点（0x651000：新基准/旧基准，用于 +160 两对象变换块 12/16/20 三标量缩放）（证据: va=00651000）
    unsigned int     pSubObj156            ; // +0x009C (156) x1  子对象 1（0x6511E0：循环 3 次对其 vt+12(0)）（证据: va=006511E0）
    unsigned int     pSubObj160            ; // +0x00A0 (160) x1  子对象 2（0x651000：循环 2 个对象的 vt+36 变换块缩放）（证据: va=00651000）
    unsigned char _unused_0x00A4      [8]; // +0x00A4..0x00AB 未观测
    unsigned int     pVec172               ; // +0x00AC (172) x6  向量 begin（0x6511E0：非 0 先 free 再三清）（证据: va=006511E0）
    unsigned int     pVec176               ; // +0x00B0 (176) x6  向量 end（0x6511E0 清 0）（证据: va=006511E0）
    unsigned int     pVec180               ; // +0x00B4 (180) x3  向量 cap（0x6511E0 清 0）（证据: va=006511E0）
    unsigned char    bReady184             ; // +0x00B8 (184) x2  就绪标志字节（0x6510A0/0x6511E0/0x651260 均置 0；QUAKE_WAVE_READY_LOOP 就绪门）【推断】（证据: va=00651260）
};
#pragma pack(pop)

// 统计: 字段行 16 / 未命名 0 / 标【推断】5 / 末尾偏移 +0x00B9
