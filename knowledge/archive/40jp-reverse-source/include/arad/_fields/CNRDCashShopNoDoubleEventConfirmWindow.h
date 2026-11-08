// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDCashShopNoDoubleEventConfirmWindow 主虚表槽位数: 17  字段数: 2
// 继承: CNRDCashShopNoDoubleEventConfirmWindow -> CNRDYesNoConfirmWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00633410  CNRDCashShopNoDoubleEventConfirmWindow__vmt40 文案槽（+80/+84）（src/game/ui/window_party.cpp:2865）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDCASHSHOPNODOUBLEEVENTCONFIRMWINDOW
#define ARAD40JP_FIELDS_CNRDCASHSHOPNODOUBLEEVENTCONFIRMWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDCashShopNoDoubleEventConfirmWindow_Fields {
    unsigned char _base_0x0000        [80]; // +0x0000..0x004F 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pItemObj            ; // +0x0050 (80) x1  va=00633410 道具对象（0x633410: *(this+80)=nArg2）
    unsigned char    bEventFlag          ; // +0x0054 (84) x1  va=00633410 双倍事件标志（0x633410: *(uint8_t*)(this+84)=(nArg3==0)；串 3011 文案）
};
#pragma pack(pop)

// 统计: 字段行 2 / 语义名 2 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0055

#endif

