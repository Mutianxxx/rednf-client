// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDQuestInfoWindow      主虚表槽位数: 14   字段数: 13
// 继承: CNRDQuestInfoWindow -> IRDWindow -> nengine::IAppendDraw（基类段见 src/cnrd/*.h）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 14 个）:
//   +0  0x551D10 构造（164 行：47C210 + 418DD0/4F2C10/551C50/44E850/44E8D0/422E70/
//       50EF20/50EB40 + 42B420/491530/43B560/491630）
//   +8  0x552850 Update（140 行：CLICK_BUTTON2/LETTER_FADE_IN_01/WINDOW_CLOSE + 5518A0 打字机
//       + 69C6A0/69C680/69C690/69C400 滚动 + 47B560/47B9E0/44AB50）
//   +12 0x551BD0 打开槽；+16 0x5517A0 状态切换槽（432EE0 + 44E850）
//   +44 0x540360 IRDWindow__vmt2C 页签（44AB50(this+8, this+12, 12)）；+4 = 0x44DEF0 删除析构壳
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDQUESTINFOWINDOW
#define ARAD40JP_FIELDS_CNRDQUESTINFOWINDOW

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDQuestInfoWindow_Fields {
    // ---- 区块: 状态机族（页签/脏位/任务切换；0x551D10） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDQuestInfoWindow -> IRDWindow -> nengine::IAppendDraw）一行带过
    uint32_t         pOwnerWnd           ; // +0x0004 (4) x1  va=00551D10 宿主窗口（0x551D10: nArg2 == *(this+4) 分派）【推断】
    uint32_t         pHostCtrl           ; // +0x0008 (8) x1  va=005517A0 ★ 宿主控件（0x5517A0: *(*(*(this+8)+84)+180) = -1 复位悬停）
    uint32_t         nTabIndex           ; // +0x000C (12) x1  va=00540360 ★ 页签索引（vmt2C 0x540360: 44AB50(this+8, this+12, 12)）
    // ---- 区块: 控件族（列表/详情/奖励图标；0x551D10） ----
    uint32_t         pQuestListCtrl      ; // +0x0010 (16) x2  va=00551D10 ★ 任务列表控件（0x551D10: fld_10 = *(this+16) 装配）
    uint32_t         pQuestDetailCtrl    ; // +0x0014 (20) x1  va=00551D10 ★ 任务详情控件（0x551D10: fld_14 = *(this+20) 装配）
    unsigned char _unused_0018[4]; // +0x0018..0x001B 未观测
    uint8_t          bDirty              ; // +0x001C (28) x1  va=005517A0 ★ 脏/需刷新标志（0x5517A0: *(this+28) != 0 分支）
    unsigned char _unused_001D[95]; // +0x001D..0x007B 未观测
    uint32_t         field_007C          ; // +0x007C (124) x1  va=00551D10 0x551D10 读取槽（语义未定）
    // ---- 区块: 数据缓冲族（任务 id 组） ----
    unsigned char _unused_0080[60]; // +0x0080..0x00BB 未观测
    uint32_t         nCurQuestId         ; // +0x00BC (188) x2  va=00551D10 ★ 当前任务 id（0x551D10: fld_BC = *(this+188)；与 +192 不等则重新加载）
    uint32_t         nPrevQuestId        ; // +0x00C0 (192) x2  va=00551D10 ★ 上一任务 id（0x551D10: *(this+192)；与 +188 成对做变更检测）
    unsigned char _unused_00C4[4]; // +0x00C4..0x00C7 未观测
    uint32_t         field_00C8          ; // +0x00C8 (200) x1  va=00551D10 0x551D10 读取槽（语义未定）
    uint32_t         nAltQuestId         ; // +0x00CC (204) x1  va=00551D10 ★ 备用任务 id（0x551D10: else if (nArg2 == *(this+204))）
    uint32_t         nRewardId           ; // +0x00D0 (208) x2  va=00551D10 ★ 奖励 id（0x551D10: fld_103 != *(this+208) → 写回 +208）
    uint32_t         pRewardIconCtrl     ; // +0x00D4 (212) x1  va=00551D10 ★ 奖励图标控件（0x551D10: sub_50EF20(*(this+212), Buffer, 4, -1) 出图标）
};
#pragma pack(pop)

// 统计: 字段行 13 / 语义名 10 / 标【推断】1 / 未命名 2 / 末尾偏移 +0x00D8

#endif
