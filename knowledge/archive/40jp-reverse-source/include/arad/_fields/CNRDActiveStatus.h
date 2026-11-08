// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNRDActiveStatus           主虚表槽位数: 22   字段数: 11
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDActiveStatus
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDActiveStatus_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x35 宿主/关联对象（0x5FA7E0 vmt50 入口门：nArg2 == *(this+4)）（证据: va=005FA7E0）
    unsigned int     nMode8                ; // +0x0008 (8) x8  状态模式号（0x4973B0 switch 按此分派 1..3 条子动画链；0x5FA7E0 仅模式 1/3/7 推进）（证据: va=004973B0）
    unsigned char _unused_0x000C      [8]; // +0x000C..0x0013 未观测
    unsigned int     pAnimLink20           ; // +0x0014 (20) x15 子动画链 1（0x4973B0：sub_4939E0(*(this+20), 冻结/解冻) 广播）（证据: va=004973B0）
    unsigned int     pAnimLink24           ; // +0x0018 (24) x6  子动画链 2（模式 1/15 参与广播）（证据: va=004973B0）
    unsigned int     pAnimLink28           ; // +0x001C (28) x3  子动画链 3（模式 1 三条全广播）（证据: va=004973B0）
    unsigned char _unused_0x0020      [41]; // +0x0020..0x0048 未观测
    unsigned char    bResetA73             ; // +0x0049 (73) x1  复位字节 A（0x5FA7E0 倒计时推进时清 0）【推断】（证据: va=005FA7E0）
    unsigned char    bResetB74             ; // +0x004A (74) x1  复位字节 B（与 +73 成对清 0）【推断】（证据: va=005FA7E0）
    unsigned char _unused_0x004B      [9]; // +0x004B..0x0053 未观测
    unsigned int     nEndTime84            ; // +0x0054 (84) x2  状态结束时刻（0x5FA7E0：与 clock_now(this+60) 相减得剩余；< 则剩余 0）（证据: va=005FA7E0）
    unsigned int     nElapsed88            ; // +0x0058 (88) x3  累计推进量（0x5FA7E0：+88 += 500 逐段推进；对照 +92 上限 0.8 门）（证据: va=005FA7E0）
    unsigned char _unused_0x005C      [4]; // +0x005C..0x005F 未观测
    unsigned char    bStateSwitch96        ; // +0x0060 (96) x2  状态开关字节（0x4973B0：!= pszArg2 才处理 → 冻结/解冻 this+60 时钟）（证据: va=004973B0）
    unsigned char    bFlag97               ; // +0x0061 (97) x11 附加门字节（0x5FA8B0 vmt38 读 +97 判是否跳过分支）【推断】（证据: va=005FAFC0）
};
#pragma pack(pop)

// 统计: 字段行 11 / 未命名 0 / 标【推断】3 / 末尾偏移 +0x0062
