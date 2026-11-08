// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDDialogueWindow       主虚表槽位数: 14   字段数: 14
// 继承: CNRDDialogueWindow -> IRDPopupWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x605FD0 构造（装配对话文本行表 +176、页数组 +132/+160、行表 +180）
//   +8  0x607020 Update（打字机/滚动推进 sub_69C690(this+60)；行表条目 8 字节）
//   +12 0x6071B0 打开/重定位（(640-(+8)+28)/2 居中；+192 = *uArg2 对话 id；this+120 = uArg2+74 计时）
//   +16 0x5721A0 nullsub；+24/+28 = IRDPopupWindow 位置/事件槽；+44 = IRDWindow 页签槽
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDDIALOGUEWINDOW
#define ARAD40JP_FIELDS_CNRDDIALOGUEWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDDialogueWindow_Fields {
    // ---- 区块: 控件族（对话框/滚动/父窗；0x605FD0 / 0x607020） ----
    unsigned char _base_0x0000[8]; // +0x0000..0x0007 继承段（CNRDDialogueWindow -> IRDPopupWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pParentWnd          ; // +0x0008 (8) x5  va=00605FD0 ★ 父窗口指针（0x605FD0: pArg2 == *(this+8) 分派；0x6071B0: (640-(*(*this+8)+28))/2 居中）
    unsigned char _unused_000C[28]; // +0x000C..0x0027 未观测
    uint32_t         field_0028          ; // +0x0028 (40) x1  va=00607020 0x607020 读取槽（控件槽位，语义未定）
    uint32_t         field_002C          ; // +0x002C (44) x1  va=00607020 0x607020 读取槽（控件槽位，语义未定）
    unsigned char _unused_0030[12]; // +0x0030..0x003B 未观测
    uint32_t         nTypewriterPos      ; // +0x003C (60) x4  va=00605FD0 ★ 打字机位置（0x607020: sub_69C690(*(this+60)) 当前显示到第几行）
    // ---- 区块: 计时族（对话步进计时；0x6071B0） ----
    unsigned char _unused_0040[56]; // +0x0040..0x0077 未观测
    uint32_t         nDlgTimer           ; // +0x0078 (120) x1  va=006071B0 ★ 对话计时（0x6071B0: *(this+120) = uArg2 + 74，配合 clock 驱动打字机）
    unsigned char _unused_007C[8]; // +0x007C..0x0083 未观测
    uint32_t         pPageVecAddr        ; // +0x0084 (132) x1  va=00605FD0 页数据地址（0x605FD0: pThis_84 = *(this+132)）【推断】
    // ---- 区块: 数据缓冲族（页数组 / 文本行表；8 字节/条） ----
    unsigned char _unused_0088[16]; // +0x0088..0x0097 未观测
    uint32_t         nPageVecCap         ; // +0x0098 (152) x1  va=00605FD0 ★ 页数组容量（0x605FD0: <0x10 走内联 SSO 分支，即容量判据）
    unsigned char _unused_009C[4]; // +0x009C..0x009F 未观测
    uint32_t         pPagesBegin         ; // +0x00A0 (160) x3  va=00607020 ★ 页数组 begin（0x607020: fld_A0 = *(this+160)）
    uint32_t         pPagesEnd           ; // +0x00A4 (164) x3  va=00607020 ★ 页数组 end（0x607020: (*(this+164) - fld_A0) >> 2 即页数）
    // ---- 区块: 状态机族（页索引/自动翻页/对话 id；0x6071B0） ----
    uint32_t         nPageIndex          ; // +0x00A8 (168) x1  va=006071B0 ★ 当前页索引（0x6071B0: *(this+168) = 0 复位到首页）
    unsigned char _unused_00AC[4]; // +0x00AC..0x00AF 未观测
    uint32_t         pLineTableA         ; // +0x00B0 (176) x5  va=00605FD0 ★ 文本行表 A（0x605FD0: fld_B0 = *(this+176)；0x607020 以其 +8 步进取行）
    uint32_t         nLineCount          ; // +0x00B4 (180) x2  va=00605FD0 ★ 行数（0x605FD0: (*(this+180) - fld_B0) >> 3，行条目 8 字节）
    unsigned char _unused_00B8[4]; // +0x00B8..0x00BB 未观测
    uint8_t          bAutoNext           ; // +0x00BC (188) x2  va=00605FD0 ★ 自动翻页/继续标志（0x607020: *(this+188) != 0 分支）
    unsigned char _unused_00BD[3]; // +0x00BD..0x00BF 未观测
    uint32_t         nDlgId              ; // +0x00C0 (192) x1  va=006071B0 ★ 对话 id（0x6071B0: *(this+192) = *uArg2 本次打开的对白编号）
};
#pragma pack(pop)

// 统计: 字段行 14 / 语义名 11 / 标【推断】1 / 未命名 2 / 末尾偏移 +0x00C4

#endif
