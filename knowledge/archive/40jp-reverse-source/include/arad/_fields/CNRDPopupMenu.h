// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDPopupMenu                          主虚表槽位数: 1   字段数: 6
// 继承: CNRDPopupMenu -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 1 个 / 同族共享）:
//   00525AD0  CNRDPopupMenu__vmt0 右键菜单构造（126 行：菜单项数组构建）（src/game/pvp_ui.cpp:2188）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPOPUPMENU
#define ARAD40JP_FIELDS_CNRDPOPUPMENU

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPopupMenu_Fields {
    unsigned char _base_0x0000        [24]; // +0x0000..0x0017 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     szMenuTitleBuf      ; // +0x0018 (24) x1  va=00525AD0 菜单标题串内嵌缓冲（0x525AD0: *(this+44)<0x10 时 pThis_18=this+24 即 SSO 就地缓冲）
    unsigned char _unused_0x001C      [16]; // +0x001C..0x002B 未观测
    unsigned int     nTitleCapacity      ; // +0x002C (44) x1  va=00525AD0 标题串 SSO 容量（0x525AD0: *(this+44)<0x10 判就地/堆指针两态，容量 15 为 SSO 门）
    unsigned int     pOwnerNode          ; // +0x0030 (48) x1  va=00525AD0 菜单归属对象/命令表根（0x525AD0: pArg2 == *(this+48) 走标题绘制；另 sub_472E30(this+48,...) 红黑树查项）
    unsigned char _unused_0x0034      [96]; // +0x0034..0x0093 未观测
    unsigned int     pItemVecBegin       ; // +0x0094 (148) x1  va=00525AD0 菜单项向量 begin（0x525AD0: *(this+148) 逐项 4 字节遍历点击；析构 free 并清 0）
    unsigned int     pItemVecEnd         ; // +0x0098 (152) x1  va=00525AD0 菜单项向量 end（0x525AD0: (*(this+152)-begin)>>2 = 项数）
    unsigned char _unused_0x009C      [4]; // +0x009C..0x009F 未观测
    unsigned int     nHoverIndex         ; // +0x00A0 (160) x1  va=00525AD0 悬停项索引（0x525AD0: i == *(this+160) 判高亮；复位置 -1）
};
#pragma pack(pop)

// 统计: 字段行 6 / 语义名 6 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00A4

#endif

