// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDLotteryItemWindow    主虚表槽位数: 14   字段数: 10
// 继承: CNRDLotteryItemWindow -> IRDPopupWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x63D510 构造（131 行：554930 + 699000/4049C0/488670）
//   +8  0x63D440 __vmt8 Update（484E80 + 423200 系发包 + CLICK_BUTTON2）
//   +12 0x63D940 __vmtC 播放赌博动画（GAMBLE_OPEN_LOOP 循环 + GAMBLE_RESULT_COMMON/GOOD 结果；
//       69A5F0/698F90/432EA0；页签 A/B 可见位由 +152 驱动）
//   +16 0x63D420 状态切换槽（432EE0）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDLOTTERYITEMWINDOW
#define ARAD40JP_FIELDS_CNRDLOTTERYITEMWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDLotteryItemWindow_Fields {
    // ---- 区块: 控件族（页签按钮/居中基座；0x63D940） ----
    unsigned char _unused_0000[8]; // +0x0000..0x0007 未观测
    uint32_t         pDlgBaseCtrl         // +0x0008 (8) x2  va=0063D940 ★ 弹窗基座控件（0x63D940: (640 - (*(this+8)+28))/2 与 (480 - +32)/2 居中）
    unsigned char _unused_000C[24]; // +0x000C..0x0023 未观测
    uint32_t         pTabBtnA             // +0x0024 (36) x1  va=0063D940 ★ 页签按钮 A（0x63D940: 其 +16 = (*(this+152) == 1)）
    uint32_t         pTabBtnB             // +0x0028 (40) x1  va=0063D940 ★ 页签按钮 B（0x63D940: 其 +16 = (*(this+152) == 0)）
    // ---- 区块: 数据缓冲族（物品 id / 品级；0x63D940） ----
    unsigned char _unused_002C[60]; // +0x002C..0x0067 未观测
    uint32_t         nItemIdA             // +0x0068 (104) x1  va=0063D940 ★ 物品 id A（0x63D940: *(this+104) = *(nArg2 vt+16() + 68) 取物品编号）
    unsigned char _unused_006C[28]; // +0x006C..0x0087 未观测
    uint32_t         nItemGrade           // +0x0088 (136) x1  va=0063D940 ★ 物品品级（0x63D940: *(this+136) = nArg2 vt+24()）
    // ---- 区块: 状态机族（页签选择/动画标志；0x63D940） ----
    unsigned char _unused_008C[12]; // +0x008C..0x0097 未观测
    uint32_t         nTabSel              // +0x0098 (152) x4  va=0063D940 ★ 页签选择值（0x63D940: = nArg3；1→A 可见、0→B 可见，两按钮互斥驱动）
    // ---- 区块: 数据缓冲族（物品 id / 品级；0x63D940） ----
    uint32_t         nItemIdB             // +0x009C (156) x1  va=0063D940 ★ 物品 id B（0x63D940: *(this+156) = *(nArg2 vt+16() + 4)）
    // ---- 区块: 状态机族（页签选择/动画标志；0x63D940） ----
    unsigned char _unused_00A0[13]; // +0x00A0..0x00AC 未观测
    uint8_t          bAnimFlag173         // +0x00AD (173) x1  va=0063D940 动画辅助标志（0x63D940 清 0）
    uint8_t          bAnimFlag174         // +0x00AE (174) x1  va=0063D940 动画辅助标志（0x63D940 清 0）
    unsigned char _unused_00AF[13]; // +0x00AF..0x00BB 未观测
    uint8_t          bLoopOpen            // +0x00BC (188) x1  va=0063D940 ★ 循环开启动画标志（0x63D940 清 0；对应 GAMBLE_OPEN_LOOP 播放段）
};
#pragma pack(pop)

// 统计: 字段行 10 / 语义名 10 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x00BD

#endif
