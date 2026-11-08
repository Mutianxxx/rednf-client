// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDOptionWindow                       主虚表槽位数: 14  字段数: 4
// 继承: CNRDOptionWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00562480  CNRDOptionWindow__vmt0 设置窗构造（164 行：按按钮命中分组布件）（src/game/ui/cashshop.cpp:15699）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDOPTIONWINDOW
#define ARAD40JP_FIELDS_CNRDOPTIONWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDOptionWindow_Fields {
    unsigned char _base_0x0000        [36]; // +0x0000..0x0023 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pTabBtnA            ; // +0x0024 (36) x1  va=00562480 页签按钮 A（0x562480: pArg2 == *(this+36) 走图 0x12/0x21/0x15 一组布件）
    unsigned int     apPageCtrl          ; // +0x0028 (40) x1  va=00562480 页控件组首（0x562480: pThis_28=(uint32_t*)(this+40) 起多档控件；+144 作校验值）
    unsigned char _unused_0x002C      [20]; // +0x002C..0x003F 未观测
    unsigned int     pTabBtnB            ; // +0x0040 (64) x1  va=00562480 页签按钮 B（0x562480: pArg2 == *(this+64) 走第二组布件）
    unsigned char _unused_0x0044      [76]; // +0x0044..0x008F 未观测
    unsigned int     nPageCheck          ; // +0x0090 (144) x1  va=00562480 页校验值（0x562480: pArg22==*pThis_28 且 *(this+144)==result 时跳过重装）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0094

#endif

