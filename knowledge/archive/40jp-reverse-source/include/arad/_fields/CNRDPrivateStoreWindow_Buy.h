// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDPrivateStoreWindow_Buy             主虚表槽位数: 29  字段数: 5
// 继承: CNRDPrivateStoreWindow_Buy -> CNRDPrivateStoreWindow -> IRDWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   00540360  IRDWindow__vmt2C 页签显示 44AB50(this+8, this+12, 12)（src/game/ui/trade_shop.cpp:186）
//   005446F0  CNRDPrivateStoreWindow_Buy__vmt68 收购页装配（+ 4354D0/433AC0 列表件）（src/game/ui/trade_shop.cpp:4302）
//   005443F0  CNRDPrivateStoreWindow__vmt44 条目动作槽（484880 + 5441B0 + 4850B0）（src/game/ui/trade_shop.cpp:4130）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW_BUY
#define ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW_BUY

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPrivateStoreWindow_Buy_Fields {
    unsigned char _base_0x0000        [12]; // +0x0000..0x000B 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nTabIndex           ; // +0x000C (12) x1  va=00540360 页签索引（0x540360 vmt2C: 44AB50(this+8, this+12, 12)）
    unsigned char _unused_0x0010      [8]; // +0x0010..0x0017 未观测
    unsigned int     pBuyListVec         ; // +0x0018 (24) x2  va=005446F0 收购清单向量（0x5446F0: *(this+24)=sub_433AC0 建链；+0/+4/+8 三端点）
    unsigned int     pPanelVec           ; // +0x001C (28) x6  va=005446F0 面板图件向量（0x5446F0: *(this+28) 起三个 43C250 图件（帧 2/5/7））
    unsigned char _unused_0x0020      [4]; // +0x0020..0x0023 未观测
    unsigned int     pBuyListItem        ; // +0x0024 (36) x3  va=005443F0 收购列表件（0x5446F0: *(this+36)=sub_4354D0(5,14)）
    unsigned int     pBuyBtn             ; // +0x0028 (40) x2  va=005446F0 收购按钮（0x5446F0: *(this+40)=sub_43C410(帧 4..6)，位于 (128,192)）
};
#pragma pack(pop)

// 统计: 字段行 5 / 语义名 5 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x002C

#endif

