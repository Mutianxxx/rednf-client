// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDWarRoomDifficultListWindow         主虚表槽位数: 14  字段数: 2
// 继承: CNRDWarRoomDifficultListWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0063CA70  CNRDWarRoomDifficultListWindow__vmtC 打开槽（+52 数组 + +108 计数）（src/game/ui/window_party.cpp:10374）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDWARROOMDIFFICULTLISTWINDOW
#define ARAD40JP_FIELDS_CNRDWARROOMDIFFICULTLISTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDWarRoomDifficultListWindow_Fields {
    unsigned char _base_0x0000        [52]; // +0x0000..0x0033 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pItemArray          ; // +0x0034 (52) x1  va=0063CA70 条目数组指针（0x63CA70: *(*(this+52)+4*i)=0 逐项清零）
    unsigned char _unused_0x0038      [52]; // +0x0038..0x006B 未观测
    unsigned int     nItemCount          ; // +0x006C (108) x1  va=0063CA70 条目数（0x63CA70: *(this+108) 清零循环上界）
};
#pragma pack(pop)

// 统计: 字段行 2 / 语义名 2 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0070

#endif

