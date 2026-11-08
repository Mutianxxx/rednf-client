// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDImportantItemUseConfirmWindow      主虚表槽位数: 17  字段数: 3
// 继承: CNRDImportantItemUseConfirmWindow -> CNRDYesNoConfirmWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   006330F0  CNRDImportantItemUseConfirmWindow__vmt38 确认（+80/+84/+88 道具三元组）（src/game/ui/window_party.cpp:2715）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDIMPORTANTITEMUSECONFIRMWINDOW
#define ARAD40JP_FIELDS_CNRDIMPORTANTITEMUSECONFIRMWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDImportantItemUseConfirmWindow_Fields {
    unsigned char _base_0x0000        [80]; // +0x0000..0x004F 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pItemObj            ; // +0x0050 (80) x2  va=006330F0 重要道具对象（0x6330F0: *(this+80)==pObj（dword_8F852C 列表命中项）才执行；其 vt+16/+32）
    unsigned int     nItemId             ; // +0x0054 (84) x1  va=006330F0 道具 id（0x6330F0: fld_54=*(this+84)；与 vt+16()+4 比对）
    unsigned int     nConfirmIdx         ; // +0x0058 (88) x3  va=006330F0 确认索引（0x6330F0: *(this+88) 与 dword_8F852C 计数比对；作 sub_484E80/sub_602C00 第三参）
};
#pragma pack(pop)

// 统计: 字段行 3 / 语义名 3 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x005C

#endif

