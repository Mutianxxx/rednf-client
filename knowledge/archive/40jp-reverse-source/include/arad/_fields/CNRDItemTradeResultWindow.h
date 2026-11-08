// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemTradeResultWindow              主虚表槽位数: 14  字段数: 6
// 继承: CNRDItemTradeResultWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   0063E890  CNRDItemTradeResultWindow__vmt0 构造（103 行：+116/+120 条目向量 52 字节）（src/game/ui/window_party.cpp:11928）
//   0063ECD0  CNRDItemTradeResultWindow__vmtC 收尾（+128 失败原因 id）（src/game/ui/window_party.cpp:12136）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMTRADERESULTWINDOW
#define ARAD40JP_FIELDS_CNRDITEMTRADERESULTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemTradeResultWindow_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0008 (8) x3  va=0063E890 宿主窗口（0x63E890: pArg2 == *(this+8) 走结果绘制；0x63ECD0 居中收尾）
    unsigned char _unused_0x000C      [40]; // +0x000C..0x0033 未观测
    unsigned int     pListCtrl           ; // +0x0034 (52) x2  va=0063E890 列表控件（0x63E890: sub_69C690(*(this+52)) 取滚动偏移；行高 39px）
    unsigned char _unused_0x0038      [56]; // +0x0038..0x006F 未观测
    int              nAnimPayload        ; // +0x0070 (112) x1  va=0063ECD0 动画载荷槽（0x63ECD0: sub_44CA70(this+112) 释放；结果图排序链）【推断】
    unsigned int     pEntryVecBegin      ; // +0x0074 (116) x3  va=0063E890 结果条目向量 begin（0x63E890: result=*(this+116)；元素 52 字节）
    unsigned int     pEntryVecEnd        ; // +0x0078 (120) x1  va=0063E890 结果条目向量 end（0x63E890: (*(this+120)-begin)/52 = 条目数）
    unsigned char _unused_0x007C      [4]; // +0x007C..0x007F 未观测
    unsigned int     nFailReasonId       ; // +0x0080 (128) x4  va=0063E890 失败原因 id（0x63E890: *(this+128)!=0xFFFF 才画图标；0x63ECD0 存 nArg3 并取串 1114/1115）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0084

#endif

