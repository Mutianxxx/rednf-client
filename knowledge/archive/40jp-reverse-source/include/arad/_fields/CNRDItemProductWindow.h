// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemProductWindow                  主虚表槽位数: 14  字段数: 4
// 继承: CNRDItemProductWindow -> IRDWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 3 个 / 同族共享）:
//   00540360  IRDWindow__vmt2C 页签显示 44AB50(this+8, this+12, 12)（src/game/ui/trade_shop.cpp:186）
//   00566640  CNRDItemProductWindow__vmtC 商品橱窗打开（69C680/69C400）（src/game/ui/cashshop.cpp:19109）
//   00567430  CNRDItemProductWindow__vmt10 状态切换槽（44ABE0/44E850/566B80/432EE0）（src/game/ui/cashshop.cpp:19857）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMPRODUCTWINDOW
#define ARAD40JP_FIELDS_CNRDITEMPRODUCTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemProductWindow_Fields {
    unsigned char _base_0x0000        [12]; // +0x0000..0x000B 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nTabIndex           ; // +0x000C (12) x1  va=00540360 页签索引（0x540360 vmt2C: 44AB50(this+8, this+12, 12)）
    unsigned char _unused_0x0010      [4]; // +0x0010..0x0013 未观测
    unsigned int     nSelIndex           ; // +0x0014 (20) x2  va=00566640 选中项索引（0x566640: 16**(*(this+20)+104)+this+140 取选中项向量三点区）
    unsigned char _unused_0x0018      [32]; // +0x0018..0x0037 未观测
    unsigned int     pListCtrl           ; // +0x0038 (56) x1  va=00567430 列表控件（0x567430: *(this+56) 其 +17==0 时 432EE0(5) 收尾）
    unsigned char _unused_0x003C      [12]; // +0x003C..0x0047 未观测
    unsigned int     pScrollCtrl         ; // +0x0048 (72) x1  va=00566640 文本滚动控件（0x566640: *(this+72) 经 vt+32 滚到中位；0x567470 打字机）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x004C

#endif

