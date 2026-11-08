// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDPartyListWindow                    主虚表槽位数: 14  字段数: 6
// 继承: CNRDPartyListWindow -> IRDPopupWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00631980  CNRDPartyListWindow__vmtC 打开槽（+36 模式 1/0 切换两组按钮 +16）（src/game/ui/window_party.cpp:1391）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPARTYLISTWINDOW
#define ARAD40JP_FIELDS_CNRDPARTYLISTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPartyListWindow_Fields {
    unsigned char _base_0x0000        [36]; // +0x0000..0x0023 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     nListMode           ; // +0x0024 (36) x5  va=00631980 列表模式（0x631980: *(this+36) ==1 走组队列表 630750 / ==0 走 PVP 6312F0，切换时 vt+24 换页 19/14）
    unsigned char _unused_0x0028      [8]; // +0x0028..0x002F 未观测
    unsigned int     pPartyTabA          ; // +0x0030 (48) x2  va=00631980 组队页签按钮 A（0x631980: *(this+48) 其 +16 双态 1/0 随模式翻转）
    unsigned int     pPartyTabB          ; // +0x0034 (52) x2  va=00631980 组队页签按钮 B（0x631980: *(this+52) 同上成组）
    unsigned int     pPartyTabC          ; // +0x0038 (56) x2  va=00631980 组队页签按钮 C（0x631980: *(this+56) 同上成组）
    unsigned char _unused_0x003C      [28]; // +0x003C..0x0057 未观测
    unsigned int     pPvpTabA            ; // +0x0058 (88) x2  va=00631980 PVP 页签按钮 A（0x631980: *(this+88) 其 +16 与组队组反相）
    unsigned int     pPvpTabB            ; // +0x005C (92) x2  va=00631980 PVP 页签按钮 B（0x631980: *(this+92) 同上成组）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0060

#endif

