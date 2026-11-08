// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDWarRoomListWindow    主虚表槽位数: 14   字段数: 11
// 继承: CNRDWarRoomListWindow -> IRDPopupWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x62E870 列表窗口绘制（IRDPopupWindow__vmt0 后每 24px 画 6 行底；
//       页脚 %d/%d 与 %2d/%2d 人数比；图标 74/75、选中框 46）
//   +8  0x62E640 __vmt8 Update（CLICK_BUTTON2 按钮音；6 行/页滚动 --/+）
//   +12 0x62E830 __vmtC 初始化（记入 dword_9B9454、+228=nArg3、sub_62E460(this,1) 强制刷新、
//       清页号 +180 与页数 +184）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDWARROOMLISTWINDOW
#define ARAD40JP_FIELDS_CNRDWARROOMLISTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDWarRoomListWindow_Fields {
    // ---- 区块: 控件族（列表/滚动条/标题按钮；0x62E640） ----
    unsigned char _unused_0000[8]; // +0x0000..0x0007 未观测
    uint32_t         pListCtrl            // +0x0008 (8) x2  va=0062E640 ★ 列表控件（0x62E640: sub_69A650(*(this+8)) 拖动；0x62E830: sub_69A5F0(列表件,191,92) 设位）
    unsigned char _unused_000C[28]; // +0x000C..0x0027 未观测
    uint32_t         pScrollBarCtrl       // +0x0028 (40) x1  va=0062E640 滚动条控件（0x62E640: fld_28 = *(this+40)）【推断】
    uint32_t         pTitleBtn            // +0x002C (44) x1  va=0062E640 标题按钮（0x62E640: *(*(this+44)+17) = 0 取消其激活位）【推断】
    uint32_t         pRowCtrlA            // +0x0030 (48) x1  va=0062E640 行控件 A（0x62E640: fld_30 = *(this+48)，每行 6 个控件槽）【推断】
    uint32_t         pRowCtrlB            // +0x0034 (52) x1  va=0062E640 行控件 B（0x62E640: fld_34 = *(this+52)）【推断】
    // ---- 区块: 数据缓冲族（行数组；4 字节/行） ----
    unsigned char _unused_0038[112]; // +0x0038..0x00A7 未观测
    uint32_t         pRowVecBegin         // +0x00A8 (168) x2  va=0062E640 ★ 行数组 begin（0x62E640: fld_A8 = *(this+168)；+168 + 4*nCurRow 取行）
    uint32_t         nRowCount            // +0x00AC (172) x1  va=0062E640 ★ 行数（0x62E640: (*(this+172) - fld_A8) >> 2）
    // ---- 区块: 状态机族（当前行/页号/上限/悬停；0x62E640） ----
    unsigned char _unused_00B0[4]; // +0x00B0..0x00B3 未观测
    uint32_t         nCurRow              // +0x00B4 (180) x6  va=0062E640 ★ 当前行（0x62E640: 6 * *(this+180) 换算控件槽，页容量 6 行；--/+1）
    uint32_t         nRowMax              // +0x00B8 (184) x2  va=0062E640 ★ 行数上限（0x62E640: fld_B43 < *(this+184) 才允许 ++）
    unsigned char _unused_00BC[4]; // +0x00BC..0x00BF 未观测
    uint32_t         nHoverRowId          // +0x00C0 (192) x1  va=0062E640 ★ 悬停行 id（0x62E640: v16 != *(this+192) → 重设）
    unsigned char _unused_00C4[32]; // +0x00C4..0x00E3 未观测
    uint32_t         nRoomType            // +0x00E4 (228) x1  va=0062E830 ★ 房间类型参数（0x62E830 初始化: *(this+228) = nArg3）
};
#pragma pack(pop)

// 统计: 字段行 11 / 语义名 7 / 标【推断】4 / 未命名 0 / 末尾偏移 +0x00E8

#endif
