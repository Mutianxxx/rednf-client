// ============================================================
// 【40JP逆向源代码工程】src/nengine/camera_fx.cpp
// ARAD.exe 镜头与演出系统实现 —— 逐函数还原（VA 见各函数头注释）
// 未还原辅助函数以原 VA 名声明于 camera_fx.h 尾部
// ============================================================

#include "camera_fx.h"  // 镜头/演出系统头
#include <math.h>  // C 数学库（fabs 等）

// ---- 全局定义 ----
int   g_shakeRateX   = 100;  // 0x79D0C4
int   g_shakeRateY   = 100;  // 0x79D0C8
int   g_shakeRateAux = 0;    // 0x79D0CC
float g_zoomGlobal   = 1.0f; // 0x77F6DC
int   g_zoomPivotX   = 0;    // 0x8F7BD0
int   g_zoomPivotY   = 0;    // 0x8F7BD4

// ---- 对象虚方法快捷读取（vtable 槽位按字节偏移） ----
static int vcall_get(void* obj, unsigned slot)  // 按 vtable 字节偏移间接调用 getter
{
    return (*(int(__thiscall**)(void*))(*(void**)obj + slot))(obj);  // 按 vtable 字节偏移间接调用(obj 的 slot 槽)
}

// ============================================================
// 通用插值
// ============================================================

// 0x4049C0 —— 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
double lerp_f(float from, float to, int t, int tEnd)  // 函数 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
{
    if (t >= tEnd)  // t 超终点 → 直接取 to
        return to;  // t 超终点 → 直接取 to
    if (t > 0)  // t 为正 → 线性插值
        return (to - from) * (double)t / (double)tEnd + from;  // 0<t<tEnd：线性插值 (to-from)*t/tEnd + from
    return from;  // t ≤ 0 → 取 from
}

// 0x423A80 —— 同上 int 版（FTOL 截断）
int lerp_i(int from, int to, int t, int tEnd)  // 函数：同上 int 版（FTOL 截断）
{
    return (int)lerp_f((float)from, (float)to, t, tEnd);  // float 插值后 FTOL 截断为 int
}

// ============================================================
// Camera：震屏参数 / 跟随 / 方向指示 / HUD / 复位
// ============================================================

// 0x424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
// a/b 为震屏波形参数（Shake1/2.ani 资源系）；a==0 时同时清 +236/240。
// 复位震屏动画时钟(+208)标志并 arm(0,0)。
void camera_shake_param_set(Camera* cam, int a, int b)  // 函数 [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）
{
    PauseClock* clk = &cam->clockShake;              // this+208
    cam->shakeParamA = a;                            // this+200
    cam->shakeParamB = b;                            // this+204
    clk->running = 0;  // 清运行位
    clk->frozen = 0;  // 清冻结位
    clock_set_countdown(clk, 0, 0);                  // sub_698F90(this+208, 0, 0)
    if (a == 0) {
        cam->shakeAuxA = 0;                          // this+236
        cam->shakeAuxB = 0;                          // this+240
    }
}

// 0x424170 —— 镜头纵向跟随（研究 P7 直证）。
// 战斗场景(场景状态 ∈ {3,4,6})且本地玩家存在且非观战时:
//   followY(+61) = clamp(玩家Y(vt+128)/5, <=35) - 35   （值域 [-35, 0]）
void camera_vertical_follow(Camera* cam)  // 函数 镜头纵向跟随（研究 P7 直证）
{
    int sceneState = *(int*)((char*)g_sceneState + 12);   // dword_8F7A24+12
    if (sceneState != 3 && sceneState != 4 && sceneState != 6)  // 场景非战斗态(3/4/6)则跳过
        return;  // 非战斗态(3/4/6 之外)直接返回

    if (g_localPlayer == 0 || *(int*)((char*)g_mainManager + 4) != 0) {  // 无本地玩家或观战中
        cam->followY = 0;                            // 无本地玩家或观战中
    } else {
        int v = vcall_get(g_localPlayer, 128) / 5;   // vt+128 = 世界 Y 坐标 getter
        if (v > 35)  // 上限夹取 35
            v = 35;  // 夹到 35
        cam->followY = (BYTE)(v - 35);  // 跟随 Y = 值 - 35(值域 -35..0)
    }
}

// 0x424270 —— 伤害方向指示器（1500ms）。
// attacker: vt+36 → 锚对象(+8 取值)；vt+120/124/128 = x/y/z getter。
// sub_45E490(x, anchor) = 攻击方向合成（本函数未还原，VA 见 header）。
void camera_damage_direction(Camera* cam, void* attacker, int kind)  // 函数 伤害方向指示器（1500ms）
{
    int anchorVal = *(int*)vcall_get(attacker, 36) + 8;  // [vt+36() 返回对象 + 8]
    // 原文: v7 = *(_DWORD *)((*(vt+36))(uArg2) + 8);  —— 指针解引用后 +8 取值
    int x = vcall_get(attacker, 120);  // 攻击者 vt+120 = 世界 X
    int y = vcall_get(attacker, 124);  // vt+124 = 世界 Y
    int z = vcall_get(attacker, 128);  // vt+128 = 世界 Z

    cam->dmgDirX = sub_45E490(x, anchorVal) - 50;  // 调 屏幕 y → 演出层坐标（减基线）
    cam->dmgDirY = y - 32;  // 方向指示 Y = 攻击者 Y - 32
    cam->dmgDirZ = z;  // 方向指示 Z = 攻击者 Z
    cam->dmgDirKind = kind;  // 记录指示类型
    cam->b773 = 0;  // 清状态位
    cam->b774 = 0;  // 清状态位
    clock_set_countdown(&cam->clockDmgDir, 1500, 0);     // +760 时钟, 1500ms
    cam->dmgDirTick = 0;  // 指示计时归零
    cam->dmgDirScale = 1.0f;  // 指示缩放 1.0
}

// 0x424D80 —— HUD 元素时钟臂时（PauseClock 28 字节布局的直接证据）。
void camera_hud_clock_arm(Camera* cam, int index)  // 函数 HUD 元素时钟臂时（PauseClock 28 字节布局的直接证据）
{
    PauseClock* clk = &cam->hudClocks[index];            // this + 936 + 28*i
    clk->running = 0;  // 清运行位
    clk->frozen = 0;  // 清冻结位
    clock_set_countdown(clk, 500, 0);                    // 500ms 窗
    cam->hudFlags[index] = 1;                            // this + 1160 + i
}

// 0x4253E0 —— 相机全量复位（模块切换路径）。
void camera_reset_all(Camera* cam)  // 函数 相机全量复位（模块切换路径）
{
    cam->shakeParamA = 0;  // 震屏参数 A 清 0
    cam->shakeParamB = 0;  // 震屏参数 B 清 0
    cam->clockShake.running = 0;  // 震屏时钟运行位清 0
    cam->clockShake.frozen = 0;  // 震屏时钟冻结位清 0
    clock_set_countdown(&cam->clockShake, 0, 0);  // 时钟臂时(时长 0)
    cam->shakeAuxA = 0;  // 震屏辅助参数 A 清 0
    cam->shakeAuxB = 0;  // 震屏辅助参数 B 清 0
    g_zoomGlobal = 1.0f;  // 全局变焦复位 1.0
    g_zoomPivotX = 0;  // 变焦轴心 X 清 0
    g_zoomPivotY = 0;  // 变焦轴心 Y 清 0
    cam->viewL = -1; cam->viewT = -1; cam->viewR = -1; cam->viewB = -1;  // 视口四边置 -1(全屏)
    cam->viewMode = 4;                                   // this+100 = 4
    cam->zoomReachTotal = 1;                             // this+1256 = 1
    cam->b69 = 0;  // 清状态位
    cam->b70 = 0;  // 清状态位
    clock_set_countdown(&cam->clockGeneral, 0, 0);       // this+56
}

// ============================================================
// CameraFxManager：震动家族
// ============================================================

// 0x424AB0 —— 暴击震屏（唯一调用点 0x4D7350 = 命中主处理器暴击分支，研究 P2 直证）。
void fxm_crit_shake(CameraFxManager* fm, int durationMs, int amplitude)  // 函数 暴击震屏（唯一调用点 0x4D7350 = 命中主处理器暴击分支，研究 P2 直证）
{
    if (fm->critShakeActive != 0)  // 暴击震屏已激活则退出
        return;  // 暴击震屏已激活则不重入
    if (GetTickCount() - fm->critShakeLast < 1000)       // 1 秒限流
        return;  // 1 秒限流窗内忽略

    DWORD now = GetTickCount();  // 当前时刻
    double amp = (double)amplitude;  // 幅度转 double
    fm->critShakeActive = now;  // 记录激活时刻
    fm->critShakeLast = now;  // 记录限流起点
    fm->decayRateY = (float)(0.0099999998 * amp);        // 衰减率 = amp × 0.01
    fm->critShakeEnd = durationMs + now;  // 震屏结束时刻 = 时长 + now
    fm->decayRateX = (float)(0.0099999998 * amp);  // 衰减率 X = 幅度 × 0.01
    fm->critShakeAmp = amplitude;  // 记录幅度
    g_shakeRateX = (int)(amp * fm->userCoeff);           // 像素速度 = 幅度 × 用户系数
    g_shakeRateY = (int)(amp * fm->userCoeff);  // 像素速度 Y = 幅度 × 用户系数
}

// 0x424B40 —— 暴击震复位（结束后 ≥250ms 清启动位；衰减率回 1.0、基线 = 用户×100）。
void fxm_crit_reset(CameraFxManager* fm)  // 函数 暴击震复位（结束后 ≥250ms 清启动位；衰减率回 1.0、基线 = 用户×100）
{
    if (fm->critShakeActive != 0) {  // 暴击震屏激活中
        if (GetTickCount() - fm->critShakeActive >= 250) {  // 距激活 ≥ 250ms
            fm->critShakeActive = 0;  // 清激活位
            fm->decayRateY = 1.0f;                       // 1065353216 = 1.0f
            fm->decayRateX = 1.0f;  // 衰减率 X 复位 1.0
            g_shakeRateX = (int)(fm->userCoeff * 100.0);  // 像素速度 X = 用户系数 × 100
            g_shakeRateY = (int)(fm->userCoeff * 100.0);  // 像素速度 Y = 用户系数 × 100
        }
    }
}

// 0x424BB0 —— 小震动（受击通用，研究 P3 直证）。
// 幅度 = 用户系数 × 5.0 像素；同时布长震状态（start/end/amp）供 0x424C50 三相位推进。
// withZoom → 1.2× 微特写（100ms 到达 / 150ms 保持）。
// 接收者消歧（反汇编 0x424C37: mov eax,[esi+68h]; mov ecx,[eax+84h]）:
//   变焦调用的 this = [[fm+104]+132]，即宿主对象 +132 处回指的 Camera。
void fxm_small_shake(CameraFxManager* fm, int durationMs, int amp, char withZoom)  // 函数 (布好的 smallShakeStart/longShakeAmp 状态在此推进：) 6000ms 三相位长震
{
    DWORD now = GetTickCount();  // 当前时刻
    double ampPx = fm->userCoeff * 5.0;  // 幅度 = 用户系数 × 5 像素
    fm->smallShakeStart = now;  // 记录起点时刻
    fm->smallShakeEnd = durationMs + now;  // 记录结束时刻
    fm->longShakeAmp = amp;  // 布长震幅度
    fm->decayRateY = 0.05f;                              // 1028443341 = 0.05f (= 5×0.01)
    fm->decayRateX = 0.05f;  // 衰减率 X = 0.05
    g_shakeRateX = (int)ampPx;  // 像素速度 X = 幅度
    g_shakeRateY = (int)(fm->userCoeff * 5.0);  // 像素速度 Y = 用户系数 × 5
    if (withZoom != 0) {  // 带变焦
        Camera* cam = *(Camera**)(*(char**)fm->pOwner + 132);  // 宿主 +132 回指 Camera
        camera_zoom_command(cam, 1.2f, 100, 150, -1, -1, -1, 1);  // 变焦命令 1.2× 微特写(100ms 到达/150ms 保持)
    }
}

// 0x424C50 —— 长震动三相位状态机（研究 P4 直证；边界 3000/5500/5600ms = 0xBB8/0x157C/0x15E0）。
// ·0x424BB0 布好的 smallShakeStart/longShakeAmp 状态在此推进：
//   <3000 静默 / 3000-5500 平台期恒幅 / 5500-5600 线性衰减 amp→100 / ≥5600 复位
void fxm_long_shake_tick(CameraFxManager* fm)  // 函数 长震动三相位状态机（研究 P4 直证；边界 3000/5500/5600ms = 0xBB8/0x157C/0x15E0）
{
    if (fm->smallShakeStart == 0)  // 未布长震则退出
        return;  // 未布长震状态则退出
    DWORD elapsed = GetTickCount() - fm->smallShakeStart;  // 距起点已过毫秒
    if (elapsed < 3000)  // < 3000ms 静默
        return;  // <3000ms 静默段直接返回

    if (elapsed < 5500) {  // 3000-5500ms 平台期
        double amp = (double)fm->longShakeAmp;           // 平台期: 恒定幅度
        fm->decayRateY = (float)(0.0099999998 * amp);  // 衰减率 Y 恒定
        fm->decayRateX = (float)(0.0099999998 * amp);  // 衰减率 X 恒定
        g_shakeRateX = (int)(amp * fm->userCoeff);  // 像素速度 X
        g_shakeRateY = (int)((double)fm->longShakeAmp * fm->userCoeff);  // 像素速度 Y
    } else if (elapsed < 5600) {  // 5500-5600ms 衰减期
        double amp = (double)lerp_i(fm->longShakeAmp, 100, (int)elapsed, 5600);  // 幅度线性衰减 → 100
        fm->decayRateY = (float)(0.0099999998 * amp);  // 衰减率 Y
        fm->decayRateX = (float)(0.0099999998 * amp);  // 衰减率 X
        g_shakeRateX = (int)(amp * fm->userCoeff);  // 像素速度 X
        g_shakeRateY = (int)(amp * fm->userCoeff);  // 像素速度 Y
    } else {
        fm->smallShakeStart = 0;                          // 复位
        fm->decayRateY = 1.0f;  // 衰减率 Y 复位 1.0
        fm->decayRateX = 1.0f;  // 衰减率 X 复位 1.0
        g_shakeRateX = (int)(fm->userCoeff * 100.0);  // 像素速度 X = 系数 × 100
        g_shakeRateY = (int)(fm->userCoeff * 100.0);  // 像素速度 Y = 系数 × 100
    }
}

// 0x424EA0 —— 用户震动强度应用器（主模块 vmt4 每帧以设置档 0/0.3/0.7/1.0 调用）。
// ★ 语义修正（本工程定案）：研究 P5 称"定向震动"，实为每帧基线应用——
//   userCoeff(+1356) = strength；基线像素速度 = decay × coeff × 100；rate[3] = strength×100。
void fxm_apply_user_strength(CameraFxManager* fm, float strength)  // 函数 用户震动强度应用器（主模块 vmt4 每帧以设置档 0/0.3/0.7/1.0 调用）
{
    fm->userCoeff = strength;                             // +1356
    g_shakeRateAux = (int)(strength * 100.0);             // 0x79D0CC = rate[3]
    g_shakeRateX = (int)(fm->decayRateX * fm->userCoeff * 100.0);  // 基线像素速度 X = 衰减 × 系数 × 100
    g_shakeRateY = (int)(fm->decayRateY * fm->userCoeff * 100.0);  // 基线像素速度 Y = 衰减 × 系数 × 100
}

// ============================================================
// Camera：变焦族
// ============================================================

// 0x424530 —— 变焦命令（暴击特写 1.5×/受击微特写 1.2×/连击冲拳 2.0× 的统一入口）。
// 选项门 sub_48B740(2) 关闭 → mode=0 + 全局复位。
// a8(toGlobal)=1: "从全局当前值回到 target"（mode 1）；a8=0: 从 target 回 1.0（mode 3）。
// 斜率（研究 P6）: start = reach × |target − current| / (target − 1.0)
int camera_zoom_command(Camera* cam, float target, int reachMs, int holdMs,  // 签名续行：变焦命令（target/reach/hold/焦点/回全局）
                        int fx, int fy, int fz, char toGlobal)  // 函数 变焦命令（暴击特写 1.5×/受击微特写 1.2×/连击冲拳 2.0× 的统一入口）
{
    if (sub_48B740(2) == 0) {                             // 变焦选项关闭
        cam->zoomMode = 0;  // 变焦选项关闭 → 复位
        g_zoomPivotX = 0;  // 变焦模式清 0
        g_zoomPivotY = 0;  // 轴心 X 清 0
        g_zoomGlobal = 1.0f;  // 轴心 Y 清 0
        return 0;  // 全局变焦复位 1.0
    }

    if (toGlobal != 0 && cam->zoomMode != 0) {  // 回全局且已在变焦中
        if (cam->zoomMode == 1) {  // 模式 1(渐入)
            if (cam->zoomHold <= holdMs)  // 保持时长需延长
                cam->zoomHold = holdMs;                   // 延长保持
        } else if (cam->zoomMode == 2) {  // 模式 2(保持)
            if (holdMs > camera_zoom_remaining(&cam->clockZoom)) {  // 新保持时长 > 剩余
                cam->zoomHold = holdMs;  // 延长保持
                cam->b1209 = 0;  // 清状态位
                cam->b1210 = 0;  // 清状态位
                clock_set_countdown(&cam->clockZoom, cam->zoomHold, 0);  // 时钟重新臂时
            }
        }
        return 1;  // 直接返回 1
    }

    float current = g_zoomGlobal;                         // dword_77F6DC
    cam->zoomTarget = target;  // 变焦目标
    cam->zoomReach = reachMs;  // 到达时长
    cam->zoomHold = holdMs;  // 保持时长
    double delta = (toGlobal != 0) ? fabs(current - 1.0) : fabs(target - current);  // 回全局 → |当前-1|；否则 |目标-当前|
    cam->zoomMode = (toGlobal == 0) ? 3 : 1;              // 2*(uArg8==0)+1
    cam->b1209 = 0;  // 清状态位
    cam->b1210 = 0;  // 清状态位
    clock_set_countdown(&cam->clockZoom, cam->zoomReach,  // 时钟臂时(斜率 = reach×delta/(target-1))
                        (int)((double)reachMs * delta / (target - 1.0)));  // 时钟起点 = reach × delta /(target−1.0)（斜率反解）
    cam->zoomFocusX = fx;  // 焦点 X
    cam->zoomFocusY = fy;  // 焦点 Y
    cam->zoomFocusZ = fz;  // 焦点 Z
    return (int)(char)fx;                                 // 原文返回 uArg5 截断 char
}

// 0x424F00 —— 变焦恢复：以当前全局值重新向 +1168 目标推进（重新臂时，mode 3）。
void camera_zoom_restore(Camera* cam)  // 函数 变焦恢复：以当前全局值重新向 +1168 目标推进（重新臂时，mode 3）
{
    if (sub_48B740(2) != 0) {  // 若 sub_48B740：调试配置项读取并夹取上下限
        float target = cam->zoomTarget;                   // +1168
        int reach = cam->zoomReach;                       // +1172
        int hold = cam->zoomHold;                         // +1176
        int fz = cam->zoomFocusZ;                         // +1188
        int fy = cam->zoomFocusY;                         // +1184
        int fx = cam->zoomFocusX;                         // +1180
        double diff = target - g_zoomGlobal;  // 目标与当前全局差
        cam->zoomMode = 3;  // 模式 3(渐出)
        cam->b1209 = 0;  // 清状态位
        cam->b1210 = 0;  // 清状态位
        clock_set_countdown(&cam->clockZoom, reach,  // 时钟臂时
                            (int)(fabs(diff) * (double)reach / (target - 1.0)));  // 取绝对值
        cam->zoomFocusX = fx;  // 焦点 X
        cam->zoomFocusY = fy;  // 焦点 Y
        cam->zoomFocusZ = fz;  // 焦点 Z
    } else {
        cam->zoomMode = 0;  // 变焦模式清 0
        g_zoomGlobal = 1.0f;  // 全局复位 1.0
        g_zoomPivotX = 0;  // 轴心 X 清 0
        g_zoomPivotY = 0;  // 轴心 Y 清 0
    }
}

// 0x423910 —— 变焦状态小复位。
void camera_zoom_reset(Camera* cam)  // 函数：变焦状态小复位。
{
    cam->zoomMode = 0;                                    // this+1192
    g_zoomGlobal = 1.0f;  // 全局变焦复位 1.0
    g_zoomPivotX = 0;  // 轴心 X 清 0
    g_zoomPivotY = 0;  // 轴心 Y 清 0
}

// 0x4238E0 —— 变焦剩余时间：remaining = clk->duration(+24) - now（≤0 返 0）。
int camera_zoom_remaining(PauseClock* clk)  // 函数 变焦剩余时间：remaining = clk->duration(+24) - now（≤0 返 0）
{
    int duration = clk->duration;  // 时钟时长
    int now = clock_now(clk);  // 当前时刻
    if (duration < now)  // 已超时
        return 0;  // 已超时（duration<now）→ 0
    return duration - now;  // 剩余 = 时长 - 当前
}

// 0x425570 —— ★ 变焦逐帧 tick（演播层每帧调用）。
// 焦点 -1 → 跟随 this+52 对象（vt+120=x/124=y/128=z）:
//   fx' = x-320 / fy' = y + (-120 - z)；否则 +1180-320 / +1184-+1188-120
// mode 1 渐入: zoom = lerp(1.0 → target, now, reachTotal)
// mode 2 保持: zoom = target
// mode 3 渐出: zoom = lerp(target → 1.0, now, reachTotal)
// 注: 函数尾部写全局 77F6DC/轴心的语句在反编译输出截断段，
//     端点值 sub_48C1C0(1) 未还原 —— 见 docs/12 §5 遗留表。【已证实+推断混合】
void camera_zoom_tick(Camera* cam)  // 函数 变焦逐帧 tick（演播层每帧调用）
{
    if (cam->zoomMode == 0 || cam->pView == 0)  // 未变焦或无视图则退出
        return;  // 未变焦或无视图 → 退出

    int zoomFrom = (int)sub_48C1C0(1);                    // 渐入端点（未还原）
    int fxFrom, fyFrom, fxTo, fyTo;  // 渐入端点与四点缓存声明
    int viewBaseY = *(int*)((char*)cam->pView + 468);  // 视图 +468 基准 Y

    if (cam->zoomFocusX == -1) {  // 焦点 X 为 -1(未指定)
        fxTo = (cam->pFocusObject != 0) ? vcall_get(cam->pFocusObject, 120) - 320 : 0;  // 跟随焦点对象 vt+120 减 320(半屏)
    } else {
        fxTo = cam->zoomFocusX - 320;  // 焦点 X 减 320
    }
    if (cam->zoomFocusY == -1 || cam->zoomFocusZ == -1) {  // 焦点 Y/Z 未指定
        fyTo = (cam->pFocusObject != 0)  // 跟随焦点对象
            ? vcall_get(cam->pFocusObject, 124) + (-120 - vcall_get(cam->pFocusObject, 128))  // vt+124 + (-120 - vt+128)
            : viewBaseY;  // 否则取视图基准 Y
    } else {
        fyTo = cam->zoomFocusY - cam->zoomFocusZ - 120;  // 焦点 Y - 焦点 Z - 120
    }
    fxFrom = zoomFrom;  // 起始 X
    fyFrom = viewBaseY;  // 起始 Y

    int now = clock_now(&cam->clockZoom);  // 变焦时钟当前时刻
    float zoom;  // 变焦值（按模式赋值）
    switch (cam->zoomMode) {  // 按变焦模式
    case 1:  // mode 1 = 渐入 1.0→target
        zoom = (float)lerp_f(1.0f, cam->zoomTarget, now, cam->zoomReachTotal);  // 模式 1 渐入: 1.0 → target
        break;  // 跳出 switch
    case 2:  // mode 2 = 保持目标值
        zoom = cam->zoomTarget;  // 模式 2 保持
        break;  // 跳出 switch
    case 3:  // mode 3（渐出）落入 default 同处理
    default:  // default 同渐出
        zoom = (float)lerp_f(cam->zoomTarget, 1.0f, now, cam->zoomReachTotal);  // 模式 3/默认 渐出: target → 1.0
        break;  // 跳出 switch
    }
    // ---- 尾部（反编译截断，结构按 mode 端点 lerp 推断）【推断】----
    g_zoomGlobal = zoom;  // 写全局变焦值
    g_zoomPivotX = lerp_i(fxFrom, fxTo, now, cam->zoomReachTotal);  // 轴心 X = 插值
    g_zoomPivotY = lerp_i(fyFrom, fyTo, now, cam->zoomReachTotal);  // 轴心 Y = 插值
}

// ============================================================
// 渲染辅助
// ============================================================

// 0x424680 —— 变焦点变换: p' = pivot + (p − pivot) × globalZoom
// offX/offY ≠ 0 时为"偏移后变换"变体（先加偏移、变换、减回未变换偏移）。
void zoom_transform_point(int* px, int* py, float offX, float offY)  // 函数 变焦点变换: p = pivot + (p − pivot) × globalZoom
{
    if (offX == 0.0f && offY == 0.0f) {  // 无偏移变体
        *px = g_zoomPivotX + (int)((double)(*px - g_zoomPivotX) * g_zoomGlobal);  // X = 轴心 + (X-轴心)×变焦
        *py = g_zoomPivotY + (int)((double)(*py - g_zoomPivotY) * g_zoomGlobal);  // Y = 轴心 + (Y-轴心)×变焦
    } else {
        double x = *px + offX;  // 有偏移: 先加偏移
        double y = *py + offY;  // Y 加偏移
        double nx = (x - g_zoomPivotX) * g_zoomGlobal + g_zoomPivotX - x + *px;  // 变换后再减回未变换偏移
        double ny = (y - g_zoomPivotY) * g_zoomGlobal + g_zoomPivotY - y + *py;  // Y 同上
        *px = (int)nx;  // 写回 X
        *py = (int)ny;  // 写回 Y
    }
}

// 0x424760 —— 四边形提交（变焦 + 横向剔除 + RGBA 顶点色，研究 P33/P37 直证）。
// 场景状态==1（城镇）或 sy==0 跳过变焦；640 = 屏宽剔除线；vt+156 = 实际绘制虚调用。
void quad_submit_zoomed(void* tex, int x, int y, void* drawer, float sx,  // 签名续行：纹理/位置/绘制器/缩放/透明度
                        float alpha, float sy, int rot, float ox, float oy)  // 函数 四边形提交（变焦 + 横向剔除 + RGBA 顶点色，研究 P33/P37 直证）
{
    BOOL skipZoom = (*(int*)((char*)g_sceneState + 12) == 1) || (sy == 0.0f);  // 城镇场景或 sy==0 跳过变焦

    if (g_zoomGlobal == 1.0f) {  // 全局变焦中性(1.0)
        if (!skipZoom) {  // 需剔除
            float x0 = (double)*(int*)((char*)drawer + 28) - oy;   // 剔除用左右边界
            float x1 = ((double)*(unsigned int*)((char*)drawer + 20) + x0) * sx + x + oy;  // 右边界 x1
            x0 = x0 * sx + x + oy;  // 左边界 x0
            if (sx < 0.0f) {  // sx < 0
                if (x1 >= 640.0f) return;  // 完全越右界则剔除
                if (x0 < 0.0f) return;  // 完全越左界则剔除
            } else {  // sx ≥ 0
                if (x0 >= 640.0f) return;  // 完全越右界则剔除
                if (x1 < 0.0f) return;  // 完全越左界则剔除
            }
        }
        if (drawer != 0)  // 有绘制器
            (*(void(__stdcall**)(int, int, int, float, float, float, int, float, float))  // 绘制器 vt+156 实际提交
                (*(void**)drawer + 156))((int)tex, x, y, sx, alpha, sy, rot, ox, oy);  // 调虚槽 +156：取朝向字节
    } else {
        zoom_transform_point(&x, &y, ox, oy);  // 变焦点变换
        if (!skipZoom) {  // 需剔除
            float x0 = (double)*(int*)((char*)drawer + 28) - oy;  // 剔除用左边界
            float x1 = ((double)*(unsigned int*)((char*)drawer + 20) + x0) * g_zoomGlobal * sx + x + oy;  // 剔除用右边界(含变焦)
            x0 = x0 * g_zoomGlobal * sx + x + oy;  // 左边界(含变焦)
            if (sx < 0.0f) {  // sx < 0
                if (x1 >= 640.0f) return;  // 越右界剔除
                if (x0 < 0.0f) return;  // 越左界剔除
            } else {  // sx ≥ 0
                if (x0 >= 640.0f) return;  // 越右界剔除
                if (x1 < 0.0f) return;  // 越左界剔除
            }
        }
        if (drawer != 0)  // 有绘制器
            (*(void(__stdcall**)(int, int, int, float, float, float, int, float, float))  // 提交(宽/透明度乘变焦)
                (*(void**)drawer + 156))((int)tex, x, y, g_zoomGlobal * sx, g_zoomGlobal * alpha,  // 调虚槽 +156：取朝向字节
                                         sy, rot, ox, oy);  // 续行：sy/rot/ox/oy 透传
    }
}

// 0x424980 —— 矩形变焦变换（屏幕 640×480 边界值保留原样）。
// out 布局 = 原函数写入 a1[12..15]（out[0] 起算偏移 48/52/56/60 字节）。
void zoom_transform_rect(int* out12, int x, int y, int r, int b)  // 函数 矩形变焦变换（屏幕 640×480 边界值保留原样）
{
    if (g_zoomGlobal == 1.0f) {  // 全局变焦中性
        out12[3] = b; out12[2] = r; out12[1] = y; out12[0] = x;  // 直接写矩形(右/下/上/左)
        return;  // 中性变焦：矩形四边原样写回
    }
    int dx = r - x, dy = b - y;  // 宽高差
    BOOL xWas0 = (x == 0), yWas0 = (y == 0), rWas640 = (r == 640), bWas480 = (b == 480);  // 记录四边是否为屏幕边界
    zoom_transform_point(&x, &y, 0.0f, 0.0f);  // 变焦点变换
    r = x + dx;  // 右 = x + dx
    b = y + dy;  // 下 = y + dy
    out12[0] = x;  // 写左
    out12[1] = y;  // 写上
    out12[2] = r;  // 写右
    out12[3] = b;  // 写下
    if (xWas0)   out12[0] = 0;  // 原 x 为 0 则保持 0
    if (yWas0)   out12[1] = 0;  // 原 y 为 0 则保持 0
    if (rWas640) out12[2] = 640;  // 原 r 为 640 则保持 640
    if (bWas480) out12[3] = 480;  // 原 b 为 480 则保持 480
}
