// ============================================================
// 【40JP逆向源代码工程】字段语义表（批量 D · UI 窗口族 · 族模板还原）
// 类: CNRDItemTradeWindow                    主虚表槽位数: 14  字段数: 8
// 继承: CNRDItemTradeWindow -> IRDWindow -> nengine__IAppendDraw（基类段见 src/cnrd/*.h / src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 族模板批量语义判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/CLICK_BUTTON1-4/WINDOW_CLOSE；通用: sub_699000=clock_now / sub_69A5F0=窗口定位居中 / sub_69A840=控件挂链 / sub_42B340=图件 / sub_432EA0=音效播放 / 44AB50=页签切换 / 44ABE0=页签激活 / 44BBA0=窗口显示；同族命名继承 CNRDItemShopWindow.h / CNRDPrivateStoreWindow_Display.h / CNRDQuestInfoWindow.h
// 证据主源（本类槽函数 4 个 / 同族共享）:
//   0054A820  CNRDItemTradeWindow__vmt14 关闭槽（549FD0 + 44BC30）（src/game/ui/trade_shop.cpp:9554）
//   00549E10  CNRDItemTradeWindow__vmt1C 刷新槽（重排双方物品格 83 行）（src/game/ui/trade_shop.cpp:9067）
//   00540360  IRDWindow__vmt2C 页签显示 44AB50(this+8, this+12, 12)（src/game/ui/trade_shop.cpp:186）
//   0054A7A0  CNRDItemTradeWindow__vmtC 打开槽（44BBA0 显示 + 429830 动画）（src/game/ui/trade_shop.cpp:9530）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMTRADEWINDOW
#define ARAD40JP_FIELDS_CNRDITEMTRADEWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemTradeWindow_Fields {
    unsigned char _base_0x0000        [4]; // +0x0000..0x0003 继承基类段（IRDWindow -> nengine::IAppendDraw / IRDPopupWindow 族，见 IRDWindow.h）一行带过
    unsigned int     pOwnerWnd           ; // +0x0004 (4) x2  va=0054A820 宿主窗口指针（0x54A820: fld_4=*(this+4)；其 +17 命中且 +12==dword_79BE3C 才走关闭执行）
    unsigned int     pHostCtrl           ; // +0x0008 (8) x1  va=00549E10 宿主控件（0x549E10: fld_8=*(this+8)；[626] 模式==2、[627] 子页、[628] 物品 id、[629] 槽下标）
    unsigned int     nTabIndex           ; // +0x000C (12) x1  va=00540360 页签索引（0x540360 vmt2C: 44AB50(this+8, this+12, 12)）
    unsigned char _unused_0x0010      [4]; // +0x0010..0x0013 未观测
    unsigned int     pLockCtrl           ; // +0x0014 (20) x1  va=0054A7A0 就绪/锁定控件（0x54A7A0: *(uint8_t*)(*(this+20)+17)=1 置激活显示）
    unsigned char _unused_0x0018      [116]; // +0x0018..0x008B 未观测
    unsigned int     pTradeSelf          ; // +0x008C (140) x2  va=0054A7A0 交易己方对象（0x54A7A0: *(this+140)=sub_429830(dword_8F8500, word_77F804) 取本机视图）
    unsigned int     pTradePeer          ; // +0x0090 (144) x1  va=0054A7A0 交易对方对象（0x54A7A0: *(this+144)=sub_429830(dword_8F8500, dword_8F8538+4) 取对方视图）
    unsigned char _unused_0x0094      [72]; // +0x0094..0x00DB 未观测
    unsigned int     pSelfReadyTag       ; // +0x00DC (220) x1  va=0054A7A0 己方就绪标签控件（0x54A7A0: *(uint8_t*)(*(this+220)+40)=0 清就绪）
    unsigned int     pPeerReadyTag       ; // +0x00E0 (224) x1  va=0054A7A0 对方就绪标签控件（0x54A7A0: *(uint8_t*)(*(this+224)+40)=0 清就绪）
};
#pragma pack(pop)

// 统计: 字段行 8 / 语义名 8 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00E4

#endif

