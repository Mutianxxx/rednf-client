// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDPrivateStoreWindow_Display 主虚表槽位数: 29   字段数: 10
// 继承: CNRDPrivateStoreWindow_Display -> CNRDPrivateStoreWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 29 个）:
//   +8  0x542730 __vmt8 Update（83 行：店铺名输入框(+60)持焦点按键盘态分派 542310；
//       标题按钮(+28)悬停 542270；登记按钮(+56)悬停：无店名→串 1334、14 格全空→串 1350，
//       否则 42FC00 本地建摊并走 vt+92 发 90 包；收购/出售页按钮(+40/+44)→44ABE0(14)/(15) 切页）
//   +12 0x542380 __vmtC 打开槽（展示挂件 +8；店铺名输入框设为串表 1334 默认文案 + 同步 dword_79BE4C/54）
//   +16 0x5423D0 __vmt10 状态切换（把 dword_9B8040 上架列表逐件经 vt+72 重登记）
//   +20 0x5425E0 __vmt14 撤销上架（44BC30 退物品）
//   +64 0x542CA0 __vmt40 上架格子放物品（虚表 +80 校验/+60 同类判定/+44 堆叠合并；多件 540DE0 数量窗）
//   +80/+84/+88 0x541F40/0x541FA0/0x541FD0 发 85 买 / 89 拆摊 / 87 退摊（docs/24 露店协议族）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW_DISPLAY
#define ARAD40JP_FIELDS_CNRDPRIVATESTOREWINDOW_DISPLAY

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDPrivateStoreWindow_Display_Fields {
    // ---- 区块: 控件族（标题/页签/登记/输入框；0x542730） ----
    unsigned char _base_0x0000[8]; // +0x0000..0x0007 继承段（CNRDPrivateStoreWindow_Display -> CNRDPrivateStoreWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pStoreWnd           ; // +0x0008 (8) x1  va=00542730 ★ 摆摊主窗体（0x542730: *(*(*(this+8)+28)+136) +17 = 0 清挂件；0x542380 显示挂件 +8）
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12)）
    // ---- 区块: 数据缓冲族（上架列表与条目数组；0x543190 / 0x542C40） ----
    unsigned char _unused_0010[8]; // +0x0010..0x0017 未观测
    uint32_t         nShopListId         ; // +0x0018 (24) x1  va=00543190 ★ 上架列表 id（0x543190: *(this+24) = dword_9B8044）
    uint32_t         pSellEntryVec       ; // +0x001C (28) x6  va=00543190 ★ 出售条目数组（0x543190: 其 +4/+8 两子控件经 sub_69A5F0 定位、sub_69A840 挂链）
    unsigned char _unused_0020[4]; // +0x0020..0x0023 未观测
    uint32_t         nAvatarListId       ; // +0x0024 (36) x3  va=005443F0 ★ 物品清单 id（0x543190: *(this+36) = dword_9B8040；= 背包上架源列表）
    uint32_t         pBuyTabBtn          ; // +0x0028 (40) x3  va=00542730 ★ 收购页按钮（0x542730: 悬停 → 44ABE0(14) 切到收购页；542270 联动）
    uint32_t         pSellTabBtn         ; // +0x002C (44) x3  va=00542730 ★ 出售页按钮（0x542730: 悬停 → 44ABE0(15) 切到出售页）
    unsigned char _unused_0030[4]; // +0x0030..0x0033 未观测
    uint32_t         pAssistCtrl         ; // +0x0034 (52) x3  va=00543190 0x543190 装配槽（装配后清其 +17 激活位）【推断】
    uint32_t         pRegBtn             ; // +0x0038 (56) x3  va=00542730 ★ 登记（开店）按钮（0x542730: 悬停；无店名→弹串 1334、14 格全空→弹串 1350，否则 42FC00 建摊）
    uint32_t         pShopNameEdit       ; // +0x003C (60) x7  va=00542730 ★ 店铺名输入框（0x542730 持焦点按键盘态分派 542310；0x542380 设串 1334 默认文案 + dword_79BE4C/54）
};
#pragma pack(pop)

// 统计: 字段行 10 / 语义名 9 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x0040

#endif
