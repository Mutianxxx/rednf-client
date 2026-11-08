// ============================================================
// 【40JP逆向源代码工程】src/nengine/camera_fx.h
// ARAD.exe 镜头与演出系统 —— 接口与数据布局
//
// 三对象架构（反汇编直证，2026-10-06 会话 2 定案）:
//   Camera          渲染相机: 变焦状态/震屏参数/纵向跟随/伤害方向/HUD 时钟
//   CameraFxManager 演出管理器(主模块+16 持有): 震动运行态/用户强度/衰减率
//   全局: 震动域速率 0x79D0C4/C8(时间域1/2)、变焦倍率 0x77F6DC、变焦轴心 0x8F7BD0/D4
//
// 置信度:【已证实】除注明处外全部经 Hex-Rays 反编译 + 反汇编字节校验
// ============================================================

#ifndef ARAD40JP_NENGINE_CAMERA_FX_H
#define ARAD40JP_NENGINE_CAMERA_FX_H

#include "time_system.h"   // PauseClock

// ------------------------------------------------------------
// 全局数据（.data）
// ------------------------------------------------------------
extern int   g_shakeRateX;    // 0x79D0C4 = tickRate[1] 震动 X 像素速度（时间域1）
extern int   g_shakeRateY;    // 0x79D0C8 = tickRate[2] 震动 Y 像素速度（时间域2）
extern int   g_shakeRateAux;  // 0x79D0CC = tickRate[3] = 用户强度×100（Shake1.ani 播放系读）
extern float g_zoomGlobal;    // 0x77F6DC 全局变焦倍率（渲染全链读）
extern int   g_zoomPivotX;    // 0x8F7BD0 变焦轴心 X（屏幕像素）
extern int   g_zoomPivotY;    // 0x8F7BD4 变焦轴心 Y
extern DWORD g_userStrength;  // dword_8F8548+8 用户震动强度档 0..3
extern void* g_localPlayer;   // 0x8F7C04 本地玩家对象
extern void* g_mainManager;   // 0x8F8528 主管理器（CNUser 系）
extern void* g_sceneState;    // 0x8F7A24 (+12 = 场景状态: 1城镇 3/4/6战斗)
extern void* g_socketGlobal;  // 0x8F7B08 网络连接对象（退出时关闭）

// ------------------------------------------------------------
// Camera（渲染相机）—— 字段偏移为反汇编实测
// ------------------------------------------------------------
struct Camera
{
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

// ------------------------------------------------------------
// CameraFxManager（演出管理器，主模块 +16 持有）
// ------------------------------------------------------------
struct CameraFxManager
{
    // +0x00..0x67: 未知
    void*    pOwner;            // +0x68(104) 宿主对象（其 +132 = Camera 指针）
    // +0x4C4(1224)..0x4E0(1248): 震动运行态
    DWORD    smallShakeStart;   // +0x4C4(1224) 小震/长震启动锚（GetTickCount）
    DWORD    smallShakeEnd;     // +0x4C8(1228) = start + duration
    int      longShakeAmp;      // +0x4CC(1232) 长震幅度
    DWORD    critShakeActive;   // +0x4D4(1236) 暴击震启动位（0=空闲）
    DWORD    critShakeLast;     // +0x4D8(1240) 暴击震限流锚（1s）
    DWORD    critShakeEnd;      // +0x4DC(1244) = now + duration
    int      critShakeAmp;      // +0x4E0(1248) 暴击震幅度
    float    userCoeff;         // +0x54C(1356) 用户震动强度系数 0..1（EA0 每帧写入）
    float    decayRateX;        // +0x550(1360) 衰减率 X（静止 = 1.0，震动时 = amp×0.01）
    float    decayRateY;        // +0x554(1364) 衰减率 Y
};

// ------------------------------------------------------------
// Camera 成员（thiscall）
// ------------------------------------------------------------
void camera_shake_param_set(Camera* cam, int a, int b);            // 0x424120
void camera_vertical_follow(Camera* cam);                          // 0x424170
void camera_damage_direction(Camera* cam, void* attacker, int kind);// 0x424270
void camera_hud_clock_arm(Camera* cam, int index);                 // 0x424D80
void camera_reset_all(Camera* cam);                                // 0x4253E0

// ------------------------------------------------------------
// CameraFxManager 成员
// ------------------------------------------------------------
void fxm_crit_shake(CameraFxManager* fm, int durationMs, int amplitude); // 0x424AB0
void fxm_crit_reset(CameraFxManager* fm);                                // 0x424B40
void fxm_small_shake(CameraFxManager* fm, int durationMs, int amp, char withZoom); // 0x424BB0
void fxm_long_shake_tick(CameraFxManager* fm);                           // 0x424C50
void fxm_apply_user_strength(CameraFxManager* fm, float strength);       // 0x424EA0

// ------------------------------------------------------------
// Camera 变焦族
// ------------------------------------------------------------
void camera_zoom_command(Camera* cam, float target, int reachMs, int holdMs,
                         int fx, int fy, int fz, char toGlobal);          // 0x424530
void camera_zoom_restore(Camera* cam);                                    // 0x424F00
void camera_zoom_reset(Camera* cam);                                      // 0x423910
int  camera_zoom_remaining(PauseClock* clk);                              // 0x4238E0
void camera_zoom_tick(Camera* cam);                                       // 0x425570

// ------------------------------------------------------------
// 渲染辅助（自由函数）
// ------------------------------------------------------------
double lerp_f(float from, float to, int t, int tEnd);                      // 0x4049C0
int    lerp_i(int from, int to, int t, int tEnd);                          // 0x423A80
void   zoom_transform_point(int* px, int* py, float offX, float offY);     // 0x424680
void   quad_submit_zoomed(void* tex, int x, int y, void* drawer, float sx,
                          float alpha, float sy, int rot, float ox, float oy); // 0x424760
void   zoom_transform_rect(int* out12, int x, int y, int r, int b);        // 0x424980

// ------------------------------------------------------------
// 未还原辅助函数（保留原 VA 名，待对应模块重建时归位）
// ------------------------------------------------------------
extern int sub_45E490(int a, int b);     // 0x45E490 攻击方向合成（伤害方向指示用）
extern int sub_48B740(int optionId);     // 0x48B740 系统选项查询（2 = 镜头特写开关）
extern int sub_48C1C0(int id);           // 0x48C1C0 变焦渐入端点值（zoom_tick 用）

#endif // ARAD40JP_NENGINE_CAMERA_FX_H
