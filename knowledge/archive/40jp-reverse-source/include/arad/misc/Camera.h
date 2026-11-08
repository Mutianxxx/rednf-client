// ============================================================
// 【40JP逆向源代码工程】include/arad/misc/Camera.h
// 类: Camera
// 主虚表: 0x006C45E0   槽位数: 4
// 来源: RTTI 全表自动生成（data/rtti_hierarchy.txt + class_method_slots.txt）
// 说明: 虚表槽位为二进制实测地址；语义名来自历代精修层；字段见 L1 精修头文件
// ============================================================
#pragma once
#include "../../common/arad_types.h"

struct Camera {
    // ---- 字段（L1 精修层摘录）----

    // +0x00..0x2B: 未知（未在本次范围）
    void*    pView;             // +0x2C(44) 视口/场景对象（+468 = 视口基准 Y）
    void*    pFocusObject;      // +0x34(52) 焦点对象（本地玩家/观战目标）
    PauseClock clockGeneral;    // +0x38(56) 通用时钟（复位时 arm(0,0)）
    BYTE     followY;           // +0x3D(61) 纵向跟随偏移 ∈ [0-35..0]（存的是 v-35）
    BYTE     b69, b70;          // +0x45/46 复位清零
    // +0x54(84)..0x64(100): 视窗矩形（复位 = -1,-1,-1,-1, 4）
    int      viewL, viewT, viewR, viewB, viewMode;
    int      shakeParamA;       // +0xC8(200) [shake screen] 参数 A（0 时清 +236/240）
    int      shakeParamB;       // +0xCC(204) [shake screen] 参数 B
    PauseClock clockShake;      // +0xD0(208) 震屏动画时钟
    int      shakeAuxA;         // +0xEC(236)
    int      shakeAuxB;         // +0xF0(240)
    // +0x2DC(732)..0x305(773): 伤害方向指示器
    int      dmgDirX;           // +0x2DC(732) = f(攻击者坐标) - 50
    int      dmgDirY;           // +0x2E0(736) = 攻击者y - 32
    int      dmgDirZ;           // +0x2E4(740) = 攻击者z
    int      dmgDirTick;        // +0x2E8(744) = 0
    float    dmgDirScale;       // +0x2EC(748) = 1.0f
    int      dmgDirKind;        // +0x2F0(752) = a3
    PauseClock clockDmgDir;     // +0x2F8(760) 1500ms 倒计时
    BYTE     b773, b774;        // +0x305/06
    // +0x3A8(936)[8]: HUD 元素 PauseClock 数组（500ms 臂时）
    PauseClock hudClocks[8];
    BYTE     hudFlags[8];       // +0x488(1160) HUD 臂时标志
    // ---- 变焦状态 ----
    float    zoomTarget;        // +0x490(1168) 目标倍率
    int      zoomReach;         // +0x494(1172) 到达时间 ms
    int      zoomHold;          // +0x498(1176) 保持时间 ms
    int      zoomFocusX;        // +0x49C(1180) 焦点 x（-1 = 跟随玩家）
    int      zoomFocusY;        // +0x4A0(1184) 焦点 y（-1 = 跟随）
    int      zoomFocusZ;        // +0x4A4(1188) 焦点 z（-1 = 跟随）
    int      zoomMode;          // +0x4A8(1192) 0无 1渐入 2保持 3渐出
    PauseClock clockZoom;       // +0x4AC(1196) 变焦进度时钟
    BYTE     b1209, b1210;      // +0x4B9/4A
    int      zoomReachTotal;    // +0x4BC(1220) 变焦进度分母（tick 用）
};