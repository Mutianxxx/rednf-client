// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDPVPChannelListWindow               主虚表槽位数: 14  字段数: 4
// 继承: CNRDPVPChannelListWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 2 个 / 同族共享）:
//   00631FF0  CNRDPVPChannelListWindow__vmt0 构造（171 行：标题 + 44 起 5 槽）（src/game/ui/window_party.cpp:1722）
//   00632540  CNRDPVPChannelListWindow__vmt8 Update（+124 就绪位 + 5 槽点击 + 471CC0）（src/game/ui/window_party.cpp:1980）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPVPCHANNELLISTWINDOW
#define ARAD40JP_FIELDS_CNRDPVPCHANNELLISTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPVPChannelListWindow_Fields {
    unsigned char _base_0x0000        [8]; // +0x0000..0x0007 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0008 (8) x2  va=00631FF0 宿主窗口（0x631FF0: pArg2 == *(this+8) 走标题图 20 绘制）
    unsigned char _unused_0x000C      [28]; // +0x000C..0x0027 未观测
    unsigned int     pBtnClose           ; // +0x0028 (40) x1  va=00632540 关闭/返回按钮（0x632540: *(this+40) 其 +17 命中 → vt+32 关窗 + CLICK_BUTTON2）
    int              apEntrySlot         ; // +0x002C (44) x1  va=00632540 条目槽数组首（0x632540: (int*)(this+44) 起 5 槽循环点击；0x631FF0 同址 5 槽比对）
    unsigned char _unused_0x0030      [76]; // +0x0030..0x007B 未观测
    unsigned char    bListReady          ; // +0x007C (124) x5  va=00631FF0 列表就绪位（0x632540: !=0 走 5 槽点击分发；==0 且 46E350 → 632470 载入置 1，否则 471CC0 轮询）
};
#pragma pack(pop)

// 统计: 字段行 4 / 语义名 4 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x007D

#endif

