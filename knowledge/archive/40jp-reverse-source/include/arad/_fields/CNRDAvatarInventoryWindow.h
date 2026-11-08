// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDAvatarInventoryWindow 主虚表槽位数: 14   字段数: 11
// 继承: CNRDAvatarInventoryWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x5497A0 构造（141 行：4CE8A0/549000/4F2E40/548E20/4938F0/491D00/422E70）
//   +8  0x549580 Update（93 行：CLICK_BUTTON2/WINDOW_CLOSE + 69C690/560610；
//       悬停格 44E8D0 消息 0x1A 模式 2 弹时装提示，无则解除 26 号）
//   +12 0x548DE0 打开槽（429830 + 42B340）；+16 0x548EC0 状态切换（44AB50 + 44E850 + 540960）
//   +20/+24/+28/+40 子页槽（单元格 32px、7 列网格）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDAVATARINVENTORYWINDOW
#define ARAD40JP_FIELDS_CNRDAVATARINVENTORYWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDAvatarInventoryWindow_Fields {
    // ---- 区块: 控件族（列表/提示/滚动；0x549580） ----
    unsigned char _unused_0000[4]; // +0x0000..0x0003 未观测
    uint32_t         pOwnerWnd            // +0x0004 (4) x5  va=005497A0 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】
    uint32_t         pHostCtrl            // +0x0008 (8) x3  va=005497A0 ★ 宿主控件（0x5497A0: *(*(this+8)+2504) == 2 判定当前页；0x5494C0 同址）
    uint32_t         nTabIndex            // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12)）
    // ---- 区块: 状态机族（选中/悬停/页；0x5497A0） ----
    uint32_t         nSelSlot             // +0x0010 (16) x1  va=00549580 选中格子下标（0x549580: fld_10 = *(this+16)）【推断】
    uint32_t         nHoverSlot           // +0x0014 (20) x1  va=00549580 悬停格子下标（0x549580: fld_14 = *(this+20)；44E8D0 消息 0x1A 用）【推断】
    uint32_t         nPageIdx             // +0x0018 (24) x1  va=00549580 页索引（0x549580: result = *(this+24)）【推断】
    // ---- 区块: 数据缓冲族（格子几何） ----
    uint32_t         nSlotCount           // +0x001C (28) x1  va=00549580 ★ 格子总数（0x549580: fld_1C = *(this+28)）
    uint32_t         nCellPx              // +0x0020 (32) x1  va=00549580 ★ 格子像素尺寸（0x549580: fld_20 = *(this+32)；0x5497A0 32px/格）
    // ---- 区块: 控件族（列表/提示/滚动；0x549580） ----
    unsigned char _unused_0024[4]; // +0x0024..0x0027 未观测
    uint32_t         nScrollRow           // +0x0028 (40) x2  va=00549580 ★ 滚动行（0x549580: *(this+48) = sub_69C690(*(this+40))）
    // ---- 区块: 状态机族（选中/悬停/页；0x5497A0） ----
    uint32_t         pAvatar              // +0x002C (44) x6  va=005497A0 ★ 角色对象（0x548DE0: *(this+44) = dword_8F7C04；0x5497A0 调其 vt+792 取时装项）
    uint32_t         nGridCols            // +0x0030 (48) x4  va=005497A0 ★ 网格列数（0x5497A0: 7 * *(this+48) 换算格子下标；32 像素/格）
};
#pragma pack(pop)

// 统计: 字段行 11 / 语义名 7 / 标【推断】4 / 未命名 0 / 末尾偏移 +0x0034

#endif
