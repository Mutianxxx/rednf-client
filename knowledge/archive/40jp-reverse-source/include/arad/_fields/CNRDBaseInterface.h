// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 · UI 族还原）
// 类: CNRDBaseInterface        主虚表槽位数: 1   字段数: 16
// 继承: CNRDBaseInterface -> nengine::IAppendDraw（基类段见 src/nengine/*）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 已确证上下文: UI 事件锚点 MAP_DISAPPEAR/MAP_MOUSEOVER/MAP_SELECT/MAP_COUNTDOWN/
//   CLICK_BUTTON1-4；频道/选角 ch%02d + game_pass.php HTTP 线程 + 10 槽/页；
//   摆摊=露店 85-90 协议族；仓储=SAFE_CLOSE/点击悬停状态机；
//   通用: sub_432EA0=音效播放包装 / sub_43BEE0=上屏排版 / sub_699000=clock_now /
//   sub_426BD0=nengine::IControl 构造 / sub_44AB50=页签切换 / sub_44BBA0=窗口显示
// 证据主源（本类槽函数 1 个）:
//   +0  0x469170 CNRDBaseInterface__vmt0 基接口构造/HUD 装配（src/game/ui_icon_perf.cpp:7349）
//       本类唯一槽函数 454 行：头像/HP/宠物/倒计时/物品提醒 + Lv.%d 与角色名标签装配；
//       该函数同时是全窗口族的 vmt4 样板（窗口族继承本接口）
// ============================================================
#ifndef ARAD40JP_FIELDS_CNRDBASEINTERFACE
#define ARAD40JP_FIELDS_CNRDBASEINTERFACE

#include <stdint.h>

#pragma pack(push, 1)
struct CNRDBaseInterface_Fields {
    // ---- 区块: 状态机族（宠物/倒计时/提醒；0x469170） ----
    unsigned char _base_0x0000[4]; // +0x0000..0x0003 继承段（CNRDBaseInterface -> nengine::IAppendDraw）一行带过
    uint32_t         pAvatarStatus       ; // +0x0004 (4) x2  va=00469170 ★ 头像状态对象（0x469170: *(this+4) → +2436 → +4 取等级 < 7 判转职显示）
    uint32_t         nBindId             ; // +0x0008 (8) x1  va=00469170 ★ 绑定 id（0x469170: pArg2 == *(this+8) 分派进入主装配分支）
    // ---- 区块: 数据缓冲族（HP 条/槽 id） ----
    unsigned char _unused_000C[84]; // +0x000C..0x005F 未观测
    uint32_t         nHpBarGauge         ; // +0x0060 (96) x1  va=00469170 HP 条刻度（0x469170: pArg2 != *(this+96) 时更新 HP 条控件）【推断】
    unsigned char _unused_0064[408]; // +0x0064..0x01FB 未观测
    uint8_t          bPetFlag            ; // +0x01FC (508) x1  va=00469170 宠物标志（0x469170: *(this+508) == 1 分支）
    unsigned char _unused_01FD[15]; // +0x01FD..0x020B 未观测
    uint8_t          bCountdownOn        ; // +0x020C (524) x1  va=00469170 ★ 倒计时激活位（0x469170: *(this+524) != 0 且 clock_now(this+512) < 截止值）
    // ---- 区块: 计时族（倒计时截止/提醒值；0x469170） ----
    unsigned char _unused_020D[11]; // +0x020D..0x0217 未观测
    uint32_t         nCountdownEnd       ; // +0x0218 (536) x1  va=00469170 ★ 倒计时截止时刻（0x469170: fld_218 = *(this+536)；与 clock_now(this+512) 比较）
    unsigned char _unused_021C[12]; // +0x021C..0x0227 未观测
    uint8_t          bItemAlarm          ; // +0x0228 (552) x1  va=00469170 ★ 物品/耐久提醒位（0x469170: *(this+552)==0 || sub_41C6E0(this+540)!=0 才走提醒分支）
    unsigned char _unused_0229[15]; // +0x0229..0x0237 未观测
    uint32_t         nAlarmVal           ; // +0x0238 (568) x1  va=00469170 提醒数值（0x469170: *(this+568) != v38 时刷新）
    unsigned char _unused_023C[392]; // +0x023C..0x03C3 未观测
    uint32_t         nSlotId             ; // +0x03C4 (964) x1  va=00469170 槽 id（0x469170: pArg2 == *(this+964) 分支）【推断】
    unsigned char _unused_03C8[28]; // +0x03C8..0x03E3 未观测
    uint8_t          bStatusFlag         ; // +0x03E4 (996) x1  va=00469170 状态标志（0x469170: *(this+996) != 0 分支）【推断】
    // ---- 区块: 控件族（等级/名字标签；0x469170） ----
    unsigned char _unused_03E5[223]; // +0x03E5..0x04C3 未观测
    uint32_t         pLvTagCtrl          ; // +0x04C4 (1220) x4  va=00469170 ★ 等级标签控件（0x469170: sprintf("Lv.%d") 后按其 +20/+24 定位绘制）
    uint32_t         field_04C8          ; // +0x04C8 (1224) x1  va=00469170 0x469170 读取槽（与 +1220 等级标签同段，语义未定）
    uint8_t          bLvTagInited        ; // +0x04CC (1228) x2  va=00469170 ★ 等级标签已装配标志（0x469170: ==0 → 置 1 并做一次性装配）
    unsigned char _unused_04CD[3]; // +0x04CD..0x04CF 未观测
    uint32_t         pNameTagCtrl        ; // +0x04D0 (1232) x3  va=00469170 ★ 角色名标签控件（0x469170: *(this+1232) +20+15 / +24+3 定位绘制）
    uint32_t         field_04D4          ; // +0x04D4 (1236) x2  va=00469170 0x469170 读取槽（与 +1232 角色名标签同段，语义未定）
    unsigned char _unused_04D8[4]; // +0x04D8..0x04DB 未观测
    uint32_t         nTagTimer           ; // +0x04DC (1244) x1  va=00469170 标签计时（0x469170: *(this+1244) != -1 分支）【推断】
};
#pragma pack(pop)

// 统计: 字段行 16 / 语义名 10 / 标【推断】4 / 未命名 2 / 末尾偏移 +0x04E0

#endif
