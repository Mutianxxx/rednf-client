// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 · 批 C 装备PO/核心对象/光环族还原）
// 类: CNRDItemToolWindow         主虚表槽位数: 14   字段数: 10
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板语义名判定（tools/gen_field_semantics_batchC.py）
// 置信度: 偏移/类型/访问次数=二进制直证（不可改）；语义名=证据推断（无直证者尾标【推断】；无据者保留 field_XXXX）
// 继承链: CNRDItemToolWindow -> IRDWindow -> nengine__IAppendDraw
// 族属: 单体/窗口/模块族
// 依据: ①本类独占槽函数的 src 精修头注释（证据行 va 逐条对照）②全库通用偏移表（0x499020 帧同步族）
// 证据函数（src 头注释）: 0x44B7F0 CNRDItemToolWindow__vmt4 —— CNRDItemToolWindow::vmt4 删除析构壳 /
//   0x54D020 CNRDItemToolWindow__vmt0 —— CNRDItemToolWindow__vmt0 构造（54CA00 + 54CC00） /
//   0x54D1C0 CNRDItemToolWindow__vmt1C —— CNRDItemToolWindow__vmt1C 刷新槽（44F580/44F670 格子） /
//   0x54D260 CNRDItemToolWindow__vmt10 —— CNRDItemToolWindow__vmt10 状态切换（44ABE0 + 44E850）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemToolWindow_Fields {
    // ---- 区块 1：本段直证点（本类独占槽函数；基类见各 src 精修函数头注释） ----
    unsigned char _base_0x0000        [12]; // +0x0000..0x000B 继承基类区（见 src/cnrd/*.h 与同族语义表；不重复展开）
    unsigned int     nTabIndex12           ; // +0x000C (12) x1  页签索引（IRDWindow__vmt2C 0x540360：44AB50(this+8, this+12, 12) 把 12 号子页设为当前）（证据: va=00540360）
    unsigned int     nCountdown16          ; // +0x0010 (16) x1  倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）
    unsigned int     nState20              ; // +0x0014 (20) x6  状态机（0x54D600：==1 待机；置 2 = 处理中收尾）（证据: va=0054D600）
    unsigned char _unused_0x0018      [40]; // +0x0018..0x003F 未观测
    unsigned int     nItemIdA64            ; // +0x0040 (64) x4  物品 id A（0x54D600：sub_484ED0(*(this+64)) 取物品槽）（证据: va=0054D600）
    unsigned int     nItemIdB68            ; // +0x0044 (68) x2  物品 id B（0x54D600：sub_484ED0(*(this+68))，与 A 联合 486E80 比对）（证据: va=0054D600）
    unsigned int     nSlotReset72          ; // +0x0048 (72) x1  物品槽复位值（0x54D600：*(this+72) = 0）（证据: va=0054D600）
    unsigned char _unused_0x004C      [44]; // +0x004C..0x0077 未观测
    unsigned int     nSentinel120          ; // +0x0078 (120) x1  哨兵槽（0x54D600：*(this+120) = -1）（证据: va=0054D600）
    unsigned char _unused_0x007C      [16]; // +0x007C..0x008B 未观测
    unsigned int     pFocusObj140          ; // +0x008C (140) x1  焦点对象（0x54D600：sub_69C690(*(this+140)) 取焦点再 69C400）（证据: va=0054D600）
    unsigned int     pBtnA144              ; // +0x0090 (144) x1  按钮件 A（0x54D600：点击 → 44ABE0(宿主控件, 18)）（证据: va=0054D600）
    unsigned int     pBtnB148              ; // +0x0094 (148) x1  按钮件 B（0x54D600：点击 → 44ABE0(宿主控件, 7)）（证据: va=0054D600）
};
#pragma pack(pop)

// 统计: 字段行 10 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x0098
