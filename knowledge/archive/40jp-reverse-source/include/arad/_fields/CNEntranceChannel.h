// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNEntranceChannel        主虚表槽位数: 5   字段数: 34
// 继承: CNEntranceChannel -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 5 个）:
//   +4  0x471280 CNEntranceChannel__vmt4 选区界面帧 tick（src/game/login_channel.cpp:901）
//       一次性 M_CHARACTER_SELECT / 服务器页签×6(BUTTON_04) / 频道型×5(BUTTON_03) /
//       翻页(CLICK_BUTTON1, 页容量 10) / 频道单击(BUTTON_02) / 双击(timeGetTime 差<+1744)
//   +8  0x46E1F0 CNEntranceChannel__vmt8 离开选区清理（src/game/ui_icon_perf.cpp）
//   +0  0x41E090 标量删除析构；+12/+16 = DllMain 桩 / nullsub
// ============================================================
#ifndef ARAD40JP_FIELDS_CNENTRANCECHANNEL
#define ARAD40JP_FIELDS_CNENTRANCECHANNEL

#include <stdint.h>

#pragma pack(push, 1)
struct CNEntranceChannel_Fields {
    // ---- 区块: 状态机族（页签/频道型/页号；0x471280） ----
    unsigned char _base_0x0000[12]; // +0x0000..0x000B 继承段（CNEntranceChannel -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw）一行带过
    uint32_t         nServerSel          ; // +0x000C (12) x8  va=00471280 ★ 服务器页签选中索引（vmt4 0..5 循环比较命中后写 +12=v5；==6 时跳过频道型段）
    uint32_t         nChannelTypeSel     ; // +0x0010 (16) x5  va=00471280 ★ 频道型选中索引（vmt4 0..4 循环命中后写 +16=v8；==5 时跳过翻页段）
    uint32_t         nPage               ; // +0x0014 (20) x5  va=00471280 ★ 频道页号（vmt4 --/++；fld_14 = 10 * *(this+20) 即页容量 10）
    uint32_t         nPageMax            ; // +0x0018 (24) x1  va=00471280 页数上限（vmt4: *(this+20) < *(this+24) - 1 才允许 ++）
    // ---- 区块: 控件族（按钮组与频道条目槽；0x471280） ----
    unsigned char _unused_001C[36]; // +0x001C..0x003F 未观测
    int              apServerTabBtn      ; // +0x0040 (64) x1  va=00471280 ★ 服务器页签按钮组 6 个（+64 起连号；vmt4 "BUTTON_04" 命中 → sub_46E810 刷新）
    unsigned char _unused_0044[24]; // +0x0044..0x005B 未观测
    int              apChannelTypeBtn    ; // +0x005C (92) x1  va=00471280 ★ 频道型按钮组 5 个（+92 起连号；vmt4 "BUTTON_03" 命中 → sub_46E810）
    unsigned char _unused_0060[16]; // +0x0060..0x006F 未观测
    uint32_t         pChannelListCtrl    ; // +0x0070 (112) x2  va=00471280 ★ 频道列表控件（vmt4 翻页时 sub_69CEB0(*(this+112)) 滚动复位）
    uint32_t         apChannelSlot00     ; // +0x0074 (116) x3  va=00471280 频道条目槽 0（vmt4 翻页清零其 +16 高亮位）
    uint32_t         apChannelSlot01     ; // +0x0078 (120) x2  va=00471280 频道条目槽 1（同上成组）
    uint32_t         apChannelSlot02     ; // +0x007C (124) x2  va=00471280 频道条目槽 2（同上成组）
    uint32_t         apChannelSlot03     ; // +0x0080 (128) x2  va=00471280 频道条目槽 3（同上成组）
    uint32_t         apChannelSlot04     ; // +0x0084 (132) x2  va=00471280 频道条目槽 4（同上成组）
    uint32_t         apChannelSlot05     ; // +0x0088 (136) x2  va=00471280 频道条目槽 5（同上成组）
    uint32_t         apChannelSlot06     ; // +0x008C (140) x2  va=00471280 频道条目槽 6（同上成组）
    uint32_t         apChannelSlot07     ; // +0x0090 (144) x2  va=00471280 频道条目槽 7（同上成组）
    uint32_t         apChannelSlot08     ; // +0x0094 (148) x2  va=00471280 频道条目槽 8（同上成组）
    uint32_t         apChannelSlot09     ; // +0x0098 (152) x2  va=00471280 频道条目槽 9（同上成组；10 槽/页 = 频道页容量）
    uint32_t         pBtnChannelA        ; // +0x009C (156) x1  va=00471280 频道按钮 A（vmt4: 其 +132==1 → connectServer(this, 服务器, 2, 0)）
    uint32_t         pBtnChannelB        ; // +0x00A0 (160) x1  va=00471280 频道按钮 B（vmt4: 其 +132==1 → connectServer(this, 服务器, 3, 0)）
    uint32_t         pBtnRefresh         ; // +0x00A4 (164) x1  va=00471280 ★ 频道列表刷新按钮（vmt4: fld_A4=+164 命中 → CLICK_BUTTON1 音 + sub_46F3E0 手动刷新）
    uint32_t         pBtnChannelList     ; // +0x00A8 (168) x1  va=00471280 ★ 频道列表按钮（vmt4: fld_A8=+168 命中 → BUTTON_02 音；按 +156/+160 控件 +132 判直连 2/3 频道型，否则扫 10 槽连号）
    uint32_t         pBtnPagePrev        ; // +0x00AC (172) x1  va=00471280 ★ 上一页按钮（vmt4: fld_AC=+172 命中 → 页号>0 时 --并 sub_69CEB0 清 10 槽高亮）
    uint32_t         pBtnPageNext        ; // +0x00B0 (176) x1  va=00471280 ★ 下一页按钮（vmt4: fld_B0=+176 命中 → 页号 < 上限-1 时 ++并清 10 槽高亮）
    uint32_t         pBtnExit            ; // +0x00B4 (180) x1  va=00471280 ★ 退出按钮（vmt4: fld_B4=+180 命中 → CLICK_BUTTON3 音 + sub_41C860 退出确认）
    unsigned char _unused_00B8[148]; // +0x00B8..0x014B 未观测
    uint8_t          bReservedConn       ; // +0x014C (332) x1  va=00471280 ★ 预约重连激活位（vmt4: 非 0 → clock_now(this+320) >= 预约时刻即 processReservedConnection 0x470A80）
    unsigned char _unused_014D[11]; // +0x014D..0x0157 未观测
    uint32_t         nReservedDelay      ; // +0x0158 (344) x1  va=00471280 ★ 预约重连延迟 ms（vmt4: sub_699000(this+320) >= *(this+344) 判到点）
    // ---- 区块: 数据缓冲族（UDP 上报字段） ----
    unsigned char _unused_015C[1108]; // +0x015C..0x05AF 未观测
    uint32_t         nUdpReportField     ; // +0x05B0 (1456) x1  va=00471280 UDP 上报字段（vmt4: *((uint32_t*)dword_8F8528 + 621) = *(this+1456)）
    uint8_t          bCharSelSent        ; // +0x05B4 (1460) x2  va=00471280 ★ M_CHARACTER_SELECT 一次性发送标志（vmt4: ==0 → sub_432EA0 发事件后置 1）
    unsigned char _unused_05B5[3]; // +0x05B5..0x05B7 未观测
    uint32_t         nSelState           ; // +0x05B8 (1464) x1  va=00471280 选区阶段状态（vmt4: ==1 时进入服务器/频道按钮扫描段）【推断】
    // ---- 区块: 计时族（双击时间戳与阈值；0x471280） ----
    unsigned char _unused_05BC[260]; // +0x05BC..0x06BF 未观测
    uint32_t         nDblClickSlotA      ; // +0x06C0 (1728) x8  va=00471280 ★ 双击检测槽位 A（vmt4: ==-1 或 != 本次序号 → 记新起点 + timeGetTime）
    uint32_t         nDblClickSlotB      ; // +0x06C4 (1732) x8  va=00471280 ★ 双击检测槽位 B（vmt4: 与该槽配对的第二击槽位）
    uint32_t         nDblClickTimeA      ; // +0x06C8 (1736) x6  va=00471280 ★ 双击时间戳 A（vmt4: = timeGetTime()）+1
    uint32_t         nDblClickTimeB      ; // +0x06CC (1740) x6  va=00471280 ★ 双击时间戳 B（vmt4: = Time / dwNow）
    uint32_t         nDblClickThresh     ; // +0x06D0 (1744) x2  va=00471280 ★ 双击判定阈值 ms（vmt4: (B - A) < *(this+1744) 即 connectServer）
};
#pragma pack(pop)

// 统计: 字段行 34 / 语义名 33 / 标【推断】1 / 未命名 0 / 末尾偏移 +0x06D4

#endif
