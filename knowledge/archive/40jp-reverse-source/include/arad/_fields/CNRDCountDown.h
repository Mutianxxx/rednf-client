// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDCountDown                          主虚表槽位数: 1   字段数: 3
// 继承: CNRDCountDown -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   0049BEF0  sub_49BEF0 COUNT_DOWN 事件（+44 图像、+208 状态、48FD80）（src/game/anim_parser.cpp:10902）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDCOUNTDOWN
#define ARAD40JP_FIELDS_CNRDCOUNTDOWN

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDCountDown_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0008 (8) x1  va=0049BEF0 宿主窗口（0x49BEF0: nArg2 == *(this+8) 才分派 COUNT_DOWN 事件）
    unsigned char _unused_0x000C      [88]; // +0x000C..0x0063 未观测
    unsigned int     nCountState         ; // +0x0064 (100) x2  va=0049BEF0 倒计时状态（0x49BEF0: *(this+100) 1/2 两态分派 blink 与文本）
    unsigned int     nLastCount          ; // +0x0068 (104) x2  va=0049BEF0 上次计数（0x49BEF0: *(this+104) != pThis_48 时写回并刷新）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x006C

#endif

