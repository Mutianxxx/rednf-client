// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDWarRoomResult                      主虚表槽位数: 1   字段数: 8
// 继承: CNRDWarRoomResult -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0049E560  sub_49E560 RESULT_FLASH 演出驱动（+48 亮度插值 → 491530/491630 图层）（src/game/anim_parser.cpp:13001）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDWARROOMRESULT
#define ARAD40JP_FIELDS_CNRDWARROOMRESULT

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDWarRoomResult_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nShowStage          ; // +0x0004 (4) x15 va=0049E560 演出阶段值（0x49E560: >=2 起各档驱动 RESULT_FLASH；==2 走 800ms 亮入门、==4 逾 1100ms 复位、==12 用 +152 亮度）
    unsigned char _unused_0x0008      [40]; // +0x0008..0x002F 未观测
    unsigned int     nDriverId           ; // +0x0030 (48) x1  va=0049E560 演出驱动对象 id（0x49E560: nArg2 == *(this+48) 才进入演出体）
    unsigned char _unused_0x0034      [49]; // +0x0034..0x0064 未观测
    unsigned char    bFlashClearA        ; // +0x0065 (101) x2  va=0049E560 演出复位字节 A（0x49E560: ==4 段逾时与 +124/+126 同组清 0；==5..8 段亦清）
    unsigned char    bFlashClearB        ; // +0x0066 (102) x2  va=0049E560 演出复位字节 B（0x49E560 与 +101 成对清 0）
    unsigned char _unused_0x0067      [21]; // +0x0067..0x007B 未观测
    unsigned int     nFadeFrom           ; // +0x007C (124) x4  va=0049E560 淡出起始亮度（0x49E560: sub_4049C0(*(this+124), 0.0, now, 1000) 插值首参）
    unsigned char _unused_0x0080      [16]; // +0x0080..0x008F 未观测
    int              nFadeTo             ; // +0x0090 (144) x2  va=0049E560 淡出目标亮度（0x49E560: sub_4049C0(0.0, *(this+144), now, 1000) 插值末参）
    unsigned int     nScoreTextVal       ; // +0x0094 (148) x1  va=0049E560 分数/数值文本槽（0x49E560: sub_69A110(273, 352, *(this+148), *(this+152)) 上屏第二参）
    unsigned int     nBrightness         ; // +0x0098 (152) x3  va=0049E560 当前亮度值（0x49E560: ==12 段取本槽作亮度；并作 sub_69A110 第四参，与 +148 成对）
};
#pragma pack(pop)

// 统计: 字段行 8 / 语义名 8 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x009C

#endif

