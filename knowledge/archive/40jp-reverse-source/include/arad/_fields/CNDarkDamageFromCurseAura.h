// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNDarkDamageFromCurseAura  主虚表槽位数: 31   字段数: 13
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNDarkDamageFromCurseAura -> CNRDAuraMinion -> IRDAppendage
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// 证据函数（src 头注释）:
//   0x649160 CNDarkDamageFromCurseAura__vmt1C —— CNDarkDamageFromCurseAura__vmt1C 生成装配（5F66A0） /
//   0x649170 CNDarkDamageFromCurseAura__vmt78 —— CNDarkDamageFromCurseAura__vmt78 光环生效槽（17 行） /
//   0x6491A0 CNDarkDamageFromCurseAura__vmt4 —— CNDarkDamageFromCurseAura__vmt4 复位/伤害（605840/4E4A50/699000 /
//   0x649670 CNDarkDamageFromCurseAura__vmt0 —— CNDarkDamageFromCurseAura__vmt0 析构（转发 649560）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNDarkDamageFromCurseAura_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     pHost4                ; // +0x0004 (4) x7  宿主对象（0x6491A0 首参：*(this+4) 取 vt+308/128/624 判存活与血量）（证据: va=006491A0）
    unsigned char _unused_0x0008      [28]; // +0x0008..0x0023 未观测
    unsigned int     pEventObj36           ; // +0x0024 (36) x1  事件/表现对象（0x6491A0：sub_4E4A50 第一参 *(this+36)）（证据: va=006491A0）
    unsigned char _unused_0x0028      [12]; // +0x0028..0x0033 未观测
    unsigned char    bApplied52            ; // +0x0034 (52) x2  效果已应用标志（0x64A300 vmt4C：pszArg2==1 时置 1）（证据: va=0064A300）
    unsigned char _unused_0x0035      [19]; // +0x0035..0x0047 未观测
    unsigned int     nSnapshot72           ; // +0x0048 (72) x1  快照槽（0x6491A0：*(this+72) = *(this+100) 备份）【推断】（证据: va=006491A0）
    unsigned char _unused_0x004C      [4]; // +0x004C..0x004F 未观测
    unsigned int     nPhase80              ; // +0x0050 (80) x2  相位号（0x64A300：==2 时且三条件全非 0 才置 2，否则回写 pszArg2）（证据: va=0064A300）
    unsigned int     nCond84               ; // +0x0054 (84) x1  相位条件 1（0x64A300：+84/88/92 三连非 0 与 +80 != 2 联合判定）【推断】（证据: va=0064A300）
    unsigned int     nCond88               ; // +0x0058 (88) x1  相位条件 2（同上三连之二）【推断】（证据: va=0064A300）
    unsigned int     nCond92               ; // +0x005C (92) x1  相位条件 3（同上三连之三）【推断】（证据: va=0064A300）
    unsigned int     nActor96              ; // +0x0060 (96) x1  受方/触发者对象（0x6491A0：sub_4E4A50 第三参 *(this+96)）（证据: va=006491A0）
    unsigned int     nSrc100               ; // +0x0064 (100) x1  源值槽（0x6491A0：result = *(this+100) 供 +72 快照）【推断】（证据: va=006491A0）
    unsigned char _unused_0x0068      [28]; // +0x0068..0x0083 未观测
    unsigned int     nParam132             ; // +0x0084 (132) x1  光环参数槽（0x6491A0 尾部读；同族 CNRDAuraMinion 同区布局）【推断】（证据: va=006491A0）
    unsigned int     nPhase136             ; // +0x0088 (136) x3  相位门（0x6491A0：==2 才进伤害分支；分支结束置 0）（证据: va=006491A0）
    unsigned char    bFired140             ; // +0x008C (140) x1  已触发标志（0x6491A0 分支内置 1）（证据: va=006491A0）
};
#pragma pack(pop)

// 统计: 字段行 13 / 未命名 0 / 标【推断】6 / 末尾偏移 +0x008D
