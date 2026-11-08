// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDCursor                             主虚表槽位数: 1   字段数: 3
// 继承: CNRDCursor -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00545290  CNRDCursor__vmt0 摆摊光标构造（Donkey/Store.img 小毛驴贴图）（src/game/ui/trade_shop.cpp:4976）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDCURSOR
#define ARAD40JP_FIELDS_CNRDCURSOR

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDCursor_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0004 (4) x1  va=00545290 宿主窗口（0x545290: nArg2 == *(this+4) 才绘制光标贴图）
    unsigned char _unused_0x0008      [32]; // +0x0008..0x0027 未观测
    unsigned int     pDragObj            ; // +0x0028 (40) x1  va=00545290 拖动对象（0x545290: fld_28=*(this+40)；其 +2504 模式 1/2 走 +2520 件拖影、16 模式走 Store.img）
    unsigned char    bCursorOn           ; // +0x002C (44) x1  va=00545290 光标激活位（0x545290: *(uint8_t*)(this+44)!=0 才进入绘制段）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x002D

#endif

