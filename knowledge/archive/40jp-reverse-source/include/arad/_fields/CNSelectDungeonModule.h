// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNSelectDungeonModule    主虚表槽位数: 5   字段数: 22
// 继承: CNSelectDungeonModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 5 个）:
//   +4  0x454740 CNSelectDungeonModule__vmt4 副本选择界面帧（src/game/worldmap_reward.cpp:3618）
//       主帧 tick → 选中项命中 sub_454070（1100ms 启动门 +180）→ MOUSE_OVER / MAP_MOUSEOVER
//       / MAP_SELECT；地图条目 16 字节/条于 +276；难度上下档 +32/+36；悬停信息条 dword_8F8528 vt 55
//   +0  0x41E400 删除析构；+8/+12/+16 = 主游戏模块退出 / DllMain 桩 / nullsub
// ============================================================
#ifndef ARAD40JP_FIELDS_CNSELECTDUNGEONMODULE
#define ARAD40JP_FIELDS_CNSELECTDUNGEONMODULE

#include <stdint.h>

#pragma pack(push, 1)
struct CNSelectDungeonModule_Fields {
    // ---- 区块: 控件族（地图/难度按钮；0x454740） ----
    unsigned char _base_0x0000[20]; // +0x0000..0x0013 继承段（CNSelectDungeonModule -> nengine::IModule -> nengine::IObject -> nengine::IAppendDraw）一行带过
    uint32_t         pBtnMapEntry        ; // +0x0014 (20) x1  va=00454740 ★ 地图条目按钮（0x454740: fld_14=+20 命中且 hoverIdx!=-1 → 若 ==已选(+288) 走 MAP_SELECT，否则 sub_454610(hoverIdx,4) + MAP_MOUSEOVER）
    uint32_t         pBtnConfirm         ; // +0x0018 (24) x1  va=00454740 确认/进入按钮（0x454740: 未命中且 sub_453BE0==0 → 落入 LABEL_33 难度调整段）【推断】
    unsigned char _unused_001C[4]; // +0x001C..0x001F 未观测
    uint32_t         pBtnDiffDown        ; // +0x0020 (32) x1  va=00454740 ★ 难度降档按钮（0x454740: fld_20=+32 命中 → sub_454610(已选, 当前难度(+276条目+4) - 1)）
    uint32_t         pBtnDiffUp          ; // +0x0024 (36) x1  va=00454740 ★ 难度升档按钮（0x454740: fld_24=+36 命中 → sub_454610(已选, 当前难度 + 1)）
    unsigned char _unused_0028[28]; // +0x0028..0x0043 未观测
    uint32_t         pFrameTickObj       ; // +0x0044 (68) x1  va=00454740 每帧驱动对象（0x454740: sub_4294E0(fld_44=+68) 逐帧驱动）【推断】
    // ---- 区块: 状态机族（阶段/门/奖励推进；0x454740） ----
    unsigned char _unused_0048[76]; // +0x0048..0x0093 未观测
    uint8_t          bEnterTrigger       ; // +0x0094 (148) x2  va=00454740 ★ 副本进入触发位（0x454740: !=0 → 清 0 并走 MAP_COUNTDOWN 倒计时演出段）
    unsigned char _unused_0095[31]; // +0x0095..0x00B3 未观测
    uint8_t          bStartGate          ; // +0x00B4 (180) x2  va=00454740 ★ 启动门（0x454740: ==0 且 clock_now(this+40) >= 1100 才允许悬停/选择操作）
    unsigned char _unused_00B5[16]; // +0x00B5..0x00C4 未观测
    uint8_t          field_00C5          ; // +0x00C5 (197) x1  va=00454740 复位组字节（0x454740 清 0；与 +198/+212/-1/+216=1 同组，语义未定）
    uint8_t          field_00C6          ; // +0x00C6 (198) x1  va=00454740 复位组字节（0x454740 清 0；与 +197 成组，语义未定）
    unsigned char _unused_00C7[13]; // +0x00C7..0x00D3 未观测
    uint32_t         nCountdownState     ; // +0x00D4 (212) x3  va=00454740 ★ 倒计时阶段值（0x454740: ==-1 且阶段==2 → 转入场演出；清 0 / 置 -1 两态）
    uint8_t          field_00D8          ; // +0x00D8 (216) x1  va=00454740 复位组字节（0x454740 与 +212=-1 同组置 1，语义未定）
    // ---- 区块: 数据缓冲族（地图条目数组；16 字节/条） ----
    unsigned char _unused_00D9[3]; // +0x00D9..0x00DB 未观测
    uint32_t         pRewardHost         ; // +0x00DC (220) x1  va=00454740 ★ 奖励/结算宿主对象（0x454740: sub_476B60(*(this+220)) 取入场演出对象）
    uint32_t         nRewardMapNo        ; // +0x00E0 (224) x2  va=00454740 ★ 奖励地图号（0x454740: sub_475810 / sub_4284C0 首参）
    uint32_t         nRewardDiff         ; // +0x00E4 (228) x2  va=00454740 ★ 奖励难度档（0x454740: sub_475810 / sub_4284C0 次参）
    uint32_t         nPhase              ; // +0x00E8 (232) x4  va=00454740 ★ 阶段状态机（0x454740: 1→2→3→4 推进；==2 且倒计时到点进入入场演出）
    uint8_t          bSendGate           ; // +0x00EC (236) x3  va=00454740 ★ 发包门（0x454740: 置 1 后 clock_now(this+240) >= 1000 即 sub_423200/423380 发 40 号包并清 0）
    unsigned char _unused_00ED[16]; // +0x00ED..0x00FC 未观测
    uint8_t          field_00FD          ; // +0x00FD (253) x1  va=00454740 复位组字节（0x454740 清 0，语义未定）
    uint8_t          field_00FE          ; // +0x00FE (254) x1  va=00454740 复位组字节（0x454740 清 0，语义未定）
    unsigned char _unused_00FF[21]; // +0x00FF..0x0113 未观测
    uint32_t         pMapEntry           ; // +0x0114 (276) x6  va=00454740 ★ 地图条目指针（0x454740: *(this+276) + 16*nSel，16 字节/条；其 [0]=id 与 dword_795314 比较）
    uint32_t         pMapEntryVecEnd     ; // +0x0118 (280) x1  va=00454740 ★ 地图条目数组 end（0x454740: (*(this+280) - *(this+276)) >> 4 = 条目数）
    unsigned char _unused_011C[4]; // +0x011C..0x011F 未观测
    uint32_t         nSelMap             ; // +0x0120 (288) x7  va=00454740 ★ 选中地图索引（0x454740: 与 sub_454070 结果比较；MAP_MOUSEOVER/MAP_SELECT 门）
    uint32_t         nHoverMap           ; // +0x0124 (292) x2  va=00454740 ★ 悬停地图索引（0x454740: v6 != 该值 → sub_432EA0 "MOUSE_OVER" 音）
};
#pragma pack(pop)

// 统计: 字段行 22 / 语义名 15 / 标【推断】2 / 未命名 5 / 末尾偏移 +0x0128

#endif
