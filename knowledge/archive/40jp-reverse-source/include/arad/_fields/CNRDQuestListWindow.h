// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDQuestListWindow      主虚表槽位数: 14   字段数: 1
// 继承: CNRDQuestListWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x553490 构造（319 行：553170 + 432EA0 MOUSE_OVER 悬停音 + 422E70/418DD0/69C690/47C210
//       + 491530/491630/47B470/463F10/468FC0/4049C0/56CFE0）
//   +8  0x553260 __vmt8 Update（115 行：CLICK_BUTTON1/CLICK_BUTTON2/WINDOW_CLOSE + 69C380/69C400/
//       69C3A0/69C500 滚动 + 463ED0/552BD0/44BBA0 联动）
//   +12 0x553130 打开槽（15 行）；+16 0x553150 状态切换槽（44AB50）
//   +44 0x540360 IRDWindow__vmt2C 页签（44AB50(this+8, this+12, 12)）；+4 = 0x44E590 删除析构壳
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDQUESTLISTWINDOW
#define ARAD40JP_FIELDS_CNRDQUESTLISTWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDQuestListWindow_Fields {
    // ---- 区块: 状态机族（页签；vmt2C） ----
    unsigned char _base_0x0000[12]; // +0x0000..0x000B 继承段（CNRDQuestListWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12) 把 12 号子页设为当前；本类唯一字段直证）
};
#pragma pack(pop)

// 统计: 字段行 1 / 语义名 1 / 标【推断】0 / 未命名 0 / 末尾偏移 +0x0010

#endif
