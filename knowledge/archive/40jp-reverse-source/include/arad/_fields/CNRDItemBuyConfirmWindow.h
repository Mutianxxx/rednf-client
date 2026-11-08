// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemBuyConfirmWindow               主虚表槽位数: 14  字段数: 7
// 继承: CNRDItemBuyConfirmWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00563CB0  CNRDItemBuyConfirmWindow__vmtC 打开转发（563940 文案装配）（src/game/ui/cashshop.cpp:16892）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMBUYCONFIRMWINDOW
#define ARAD40JP_FIELDS_CNRDITEMBUYCONFIRMWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemBuyConfirmWindow_Fields {
    unsigned char _base_0x0000        [48]; // +0x0000..0x002F 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pEntryVecBegin      ; // +0x0030 (48) x2  va=00563CB0 条目向量 begin（0x563CB0: *(this+48) 非空先 free 再清 0，随后 563940 重装）
    unsigned int     pEntryVecEnd        ; // +0x0034 (52) x1  va=00563CB0 条目向量 end（0x563CB0: 清 0，与 +48 同组三端点）
    unsigned int     pEntryVecCap        ; // +0x0038 (56) x1  va=00563CB0 条目向量 cap（0x563CB0: 清 0，与 +48/+52 同组三端点）
    unsigned int     nTotalPrice         ; // +0x003C (60) x1  va=00563CB0 总价（0x563940: pDwArg1[15] += 件数 × 物品 vt+16()+36）
    unsigned int     nTotalCash          ; // +0x0040 (64) x1  va=00563CB0 总点券（0x563940: pDwArg1[16] += 件数 × 物品 vt+16()+44）
    unsigned int     nTotalMedal         ; // +0x0044 (68) x1  va=00563CB0 总奖章（0x563940: pDwArg1[17] += 件数 × 物品 vt+16()+40）
    unsigned int     nTotalWeight        ; // +0x0048 (72) x1  va=00563CB0 总重量（0x563940: pDwArg1[18] += 件数 × 物品 vt+16()+52）
};
#pragma pack(pop)

// 统计: 字段行 7 / 语义名 7 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x004C

#endif

