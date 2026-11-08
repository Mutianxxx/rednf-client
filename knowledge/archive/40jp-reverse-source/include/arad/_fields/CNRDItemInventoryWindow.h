// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemInventoryWindow                主虚表槽位数: 14  字段数: 4
// 继承: CNRDItemInventoryWindow -> IRDWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   005474B0  CNRDItemInventoryWindow__vmt14 物品拖出分发（页签 14 摆摊模式）（src/game/ui/trade_shop.cpp:6986）
//   00540360  IRDWindow__vmt2C 页签显示 44AB50(this+8, this+12, 12)（src/game/ui/trade_shop.cpp:186）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMINVENTORYWINDOW
#define ARAD40JP_FIELDS_CNRDITEMINVENTORYWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemInventoryWindow_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0004 (4) x2  va=005474B0 宿主窗口（0x5474B0: fld_4=*(this+4)）【推断】
    unsigned int     pHostCtrl           ; // +0x0008 (8) x3  va=005474B0 宿主控件（0x5474B0: *(*(this+8)+2504)==14 判摆摊模式页签）
    unsigned int     nTabIndex           ; // +0x000C (12) x1  va=00540360 页签索引（0x540360 vmt2C: 44AB50(this+8, this+12, 12)）
    unsigned char _unused_0x0010      [40]; // +0x0010..0x0037 未观测
    unsigned int     nSlotIndex          ; // +0x0038 (56) x13 va=005474B0 槽下标（0x5474B0: fld_38 = v4 + sub_547300(*(this+56))；映射到背包物品数组 dword_8F852C）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x003C

#endif

