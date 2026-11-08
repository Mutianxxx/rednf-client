// ============================================================
// 【40JP逆向源代码工程】src/nengine/time_system.h
// ARAD.exe (Ver. 200606130k0515) 时间系统 —— 接口与数据布局
//
// 范围: 16 域全局时间积分器 + 每对象可暂停时钟 (hit stop 的实现基座)
// 置信度: 【已证实】全部函数经 Hex-Rays 反编译 + 42 轮研究交叉验证
// 对应二进制: .text 0x4051A0 / 0x4052D0 / 0x698F90-0x699070
//            .data  0x79D080-0x79D144
// ============================================================

#ifndef ARAD40JP_NENGINE_TIME_SYSTEM_H
#define ARAD40JP_NENGINE_TIME_SYSTEM_H

#include <windows.h>

// ------------------------------------------------------------
// 全局数据布局 (.data，全部为静态分配)
// ------------------------------------------------------------

// 0x79D080 [16] float —— 每域小数累积器（tick 增量的小数余量，防精度丢失）
extern float g_tickFrac[16];

// 0x79D0C0 [16] int —— 每域速率（百分比；100 = 恒速）。
// 已知写者: 初始化(0x4051A0)、模块切换复位(0x41CC80 写100)、镜头震动家族
// (0x424AB0/B40/BB0/C50/EA0 写域1/2 = 震动像素速度)、sub_475810。
// 【已证实(第16轮研究)】战斗代码从不改写域速率 —— 无全局慢动作。
extern int g_tickRate[16];

// 0x79D100 [16] int —— 每域累计 tick。全库所有"游戏内当前时刻"皆由此派生。
// 域 0 = 恒速主时钟；域 1/2 = 镜头震动像素积分通道；其余域闲置。
extern int g_domainTick[16];

// 0x79D140 DWORD —— 上一帧 timeGetTime()（积分步进的帧间隔基准）
extern DWORD g_lastFrameTime;

// ------------------------------------------------------------
// 可暂停时钟对象（28 字节载体，内嵌于各业务对象）
// hit stop / 异常状态 / 演出定格 全部经由本结构实现
// ------------------------------------------------------------
struct PauseClock
{
    // +0x00 .. +0x07: 未使用/未知（反编译未见访问）【待验证】
    int  domainId;      // +0x08 时间域 id（0-15，越界值将被 bindDomain 拒绝）
    BYTE enabled;       // +0x0C 时钟已初始化
    BYTE running;       // +0x0D 正在计时
    BYTE frozen;        // +0x0E 冻结中（时间对该对象停止流动）
    BYTE pad;
    int  offset;        // +0x10 未冻结时: now = offset + tick[domainId]
    int  frozenValue;   // +0x14 冻结期间返回的定格时刻
    int  duration;      // +0x18 最近一次 setCountdown 的时长（倒计时基准）
};                      // sizeof == 28

// ------------------------------------------------------------
// 可暂停时钟原语（thiscall，本文件以第一参数显式传入）
// ------------------------------------------------------------

// 0x698F90 —— 设倒计时：running=1，记录时长与起点时刻。
//   已冻结: frozenValue = startTime（绝对值语义）
//   未冻结: offset = startTime - tick[domain]（相对值语义）
//   门: 未 enabled 或已 running 时静默忽略。
void clock_set_countdown(PauseClock* clk, int duration, int startTime);

// 0x698FE0 —— 解冻：从定格值继续（offset = frozenValue - tick[domain]）
void clock_unfreeze(PauseClock* clk);

// 0x699000 —— 取"当前时刻"：冻结中返回定格值（时间停止流动的直接实现）。
//   未 enabled 或未 running 返回 0。
int  clock_now(const PauseClock* clk);

// 0x699030 —— 冻结：定格当前时刻。enabled+running 才记录真实时刻，
//   否则定格为 0。重复冻结为无操作。
void clock_freeze(PauseClock* clk);

// 0x699070 —— 【新发现（本工程 P4）】换绑时间域并保持当前时刻连续：
//   先按旧域算出 now，再切换 domainId；未冻结时重算 offset = now - tick[新域]。
//   新域 id >= 16 时整体拒绝。42 轮研究未记载本函数。
void clock_bind_domain(PauseClock* clk, unsigned int newDomainId);

// ------------------------------------------------------------
// 16 域全局积分器
// ------------------------------------------------------------

// 0x4051A0 —— 初始化：零点 = timeGetTime()；全部域 tick=0、累积器=0、速率=100。
void tick_domains_init(void);

// 0x4052D0 —— 主循环逐帧调用：
//   dt = timeGetTime() - g_lastFrameTime
//   每域: acc = rate[i]*0.01*dt + frac[i]; tick[i] += int(acc); frac[i] = acc - int(acc)
//   返回本帧 timeGetTime() 并写入 g_lastFrameTime。
DWORD tick_domains_step(void);

#endif // ARAD40JP_NENGINE_TIME_SYSTEM_H
