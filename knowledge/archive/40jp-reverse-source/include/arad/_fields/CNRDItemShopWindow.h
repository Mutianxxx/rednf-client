// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDItemShopWindow       主虚表槽位数: 14   字段数: 20
// 继承: CNRDItemShopWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x564D30 构造（140 行：69C690/564710/4F2E40/699000/418DD0/491530/491630）
//   +8  0x564900 __vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE_ITEM 分解事件 + 5515A0 文本
//       + 69C340/69C360/69C500/69C3A0 滚动 + 44ABE0/44F400/564710/564600/484ED0）
//   +12 0x5646B0 打开槽（44BBA0 显示 + 69C400）
//   +16 0x564810 状态切换槽（44ABE0/44E850/540960/698F90/432EE0）
//   +28 0x565050 刷新槽（564710 + 44F190/5646D0/422E70/44E8D0/44A980/44F580/44F2E0）
//   +44 0x540360 IRDWindow__vmt2C 页签（44AB50(this+8, this+12, 12)）；+48/+52 = 基类 getter
//   +4  0x44F8C0 删除析构壳
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDITEMSHOPWINDOW
#define ARAD40JP_FIELDS_CNRDITEMSHOPWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDItemShopWindow_Fields {
    // ---- 区块: 状态机族（模式/页签/格子；0x564900） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDItemShopWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pOwnerWnd           ; // +0x0004 (4) x1  va=00564900 宿主/父窗口指针（0x564900: (fld_4 = *(this+4)) + 17 取命中位）【推断】
    uint32_t         pHostCtrl           ; // +0x0008 (8) x2  va=00564900 ★ 宿主控件（0x564900: *(*(this+8) + 2504) 取子页号；0x564810: *(this+8)+116）
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12) 把 12 号子页设为当前）
    uint32_t         nShopMode           ; // +0x0010 (16) x1  va=00564900 ★ 商店模式（0x564900: *(this+16) == 2 参与格子下标 v25 = 2*(==2) + 56 + 32*((v23-7*...) % 7)）
    // ---- 区块: 数据缓冲族（物品向量/价格/货币；0x564900） ----
    unsigned char _unused_0014[4]; // +0x0014..0x0017 未观测
    uint32_t         nScrollMax          ; // +0x0018 (24) x2  va=00564900 滚动上限（0x564900: sub_69C500(*(this+24))；sub_69C3A0 取当前值）
    // ---- 区块: 控件族（列表/价格/提示框；0x564900） ----
    unsigned char _unused_001C[12]; // +0x001C..0x0027 未观测
    uint32_t         pListCtrl           ; // +0x0028 (40) x4  va=00564900 ★ 列表控件（0x564900: 调其 vt+32 定位；0x564810 读其 +17 悬停位）
    unsigned char _unused_002C[12]; // +0x002C..0x0037 未观测
    uint32_t         nGridIdx            ; // +0x0038 (56) x1  va=00564900 ★ 格子下标（0x564900: v25 = 2*(mode==2) + 56 + 32*((v23 - 7*sub_69C690(*(this+56))) % 7)）
    uint32_t         pBtnActionA         ; // +0x003C (60) x1  va=00564900 ★ 动作按钮 A（0x564900: fld_3C=+60 命中 → sub_44ABE0(5) 切页 + CLICK_BUTTON2）
    uint32_t         pBtnActionB         ; // +0x0040 (64) x1  va=00564900 ★ 动作按钮 B（0x564900: fld_40=+64 命中 → sub_44ABE0(4) + CLICK_BUTTON2）
    uint32_t         pBtnActionC         ; // +0x0044 (68) x1  va=00564900 ★ 动作按钮 C（0x564900: fld_44=+68 命中 → sub_44ABE0(6) + CLICK_BUTTON2）
    uint32_t         pBtnActionD         ; // +0x0048 (72) x1  va=00564900 ★ 动作按钮 D（0x564900: fld_48=+72 命中 → sub_44F400(0,1) 执行 + CLICK_BUTTON2）
    uint32_t         pBtnActionE         ; // +0x004C (76) x1  va=00564900 ★ 动作按钮 E（0x564900: fld_4C=+76 命中 → sub_44ABE0(7) + CLICK_BUTTON2）
    unsigned char _unused_0050[16]; // +0x0050..0x005F 未观测
    uint32_t         pItemsVecBegin      ; // +0x0060 (96) x1  va=00564900 ★ 物品向量 begin（0x564900: v24==0 || v23 >= (*(this+100) - v24) >> 2 判越界）
    uint32_t         pItemsVecEnd        ; // +0x0064 (100) x1  va=00564900 ★ 物品向量 end（与 +96 差 >>2 即列表条目数）
    unsigned char _unused_0068[4]; // +0x0068..0x006B 未观测
    uint32_t         pTooltipObj         ; // +0x006C (108) x5  va=00564900 ★ 提示框对象（0x564900: result = *(this+108)，sub_484ED0 释放后置 0）
    unsigned char _unused_0070[13]; // +0x0070..0x007C 未观测
    uint8_t          field_007D          ; // +0x007D (125) x1  va=00564810 复位组字节（0x564810 清 0，语义未定）
    uint8_t          field_007E          ; // +0x007E (126) x1  va=00564810 复位组字节（0x564810 清 0，语义未定）
    unsigned char _unused_007F[53]; // +0x007F..0x00B3 未观测
    uint32_t         nPriceTextId        ; // +0x00B4 (180) x1  va=00564900 ★ 价格文本 id（0x564900: fld_B4 = sub_5515A0(*(this+180), v8) 文本取号）
    uint32_t         nPriceTextCache     ; // +0x00B8 (184) x2  va=00564900 ★ 价格文本缓存（0x564900: *(this+184) != fld_B4 → 写回并刷新显示）
    uint32_t         nTypewriterDur      ; // +0x00BC (188) x1  va=00564900 ★ 打字机时长（0x564900: sub_4049C0(0.0, nLen, clock_now(this+152), fld_BC) 插值终点 —— 文本长度→淡入时长）
};
#pragma pack(pop)

// 统计: 字段行 20 / 语义名 17 / 标【推断】1 / 未命名 2 / 末尾偏移 +0x00C0

#endif
