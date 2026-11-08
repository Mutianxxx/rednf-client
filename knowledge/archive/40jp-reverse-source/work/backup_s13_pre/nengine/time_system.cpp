// ============================================================
// 【40JP逆向源代码工程】src/nengine/time_system.cpp
// ARAD.exe 时间系统实现 —— 逐函数还原
// 每个函数保留原 VA，供字节级对照回验。
// ============================================================

#include "time_system.h"

// ------------------------------------------------------------
// 全局定义（.data 落位）
// ------------------------------------------------------------
float g_tickFrac[16]   = {0};   // @0x79D080
int   g_tickRate[16]   = {0};   // @0x79D0C0
int   g_domainTick[16] = {0};   // @0x79D100
DWORD g_lastFrameTime  = 0;     // @0x79D140

// ------------------------------------------------------------
// 0x4051A0  tick_domains_init
// 反编译直证: 零点=timeGetTime; 16 域 tick/累积器清零; 速率全部 100。
// ------------------------------------------------------------
void tick_domains_init(void)  // 实现：帧时钟域初始化（基准 = timeGetTime；16 组三表清零：倍率 100 / 残留 0 / 累加 0）
{
    g_lastFrameTime = timeGetTime();          // dword_79D140
    for (int i = 0; i < 16; ++i) {  // 循环：i 从 0 递增到 16
        g_domainTick[i] = 0;                  // dword_79D100[i]
        g_tickFrac[i]   = 0.0f;               // 0x79D080[i]
        g_tickRate[i]   = 100;                // dword_79D0C0[i]
    }
}

// ------------------------------------------------------------
// 0x4052D0  tick_domains_step
// 反编译直证（IDA for 循环旋转后的累加器写回落在 i++ 之后的表达式里,
// 语义 = 逐域积分）:
//   dt_ms = timeGetTime() - 上帧时刻
//   newAcc = rate[i] * dt_ms * 0.01 + frac[i]     // double 中间精度
//   delta  = (int)newAcc
//   tick[i] += delta; frac[i] = newAcc - delta
// ------------------------------------------------------------
DWORD tick_domains_step(void)  // 实现：帧时钟域步进（按 timeGetTime 帧差推进 16 槽累加器，更新基准）
{
    double dtMs = (double)(int)(timeGetTime() - g_lastFrameTime);  // dtMs = timeGetTime 帧时刻

    for (int i = 0; i < 16; ++i) {  // 循环：i 从 0 递增到 16
        double newAcc = (double)g_tickRate[i] * dtMs * 0.0099999998 + (double)g_tickFrac[i];  // ×0.01f：速率(百分之一 tick/ms) × 毫秒 → tick 增量
        int delta = (int)newAcc;
        g_domainTick[i] += delta;
        g_tickFrac[i] = (float)(newAcc - (double)delta);  // 保存不足 1 tick 的小数残量（下帧续算，防丢精度）
    }

    DWORD now = timeGetTime();  // now = timeGetTime 帧时刻
    g_lastFrameTime = now;
    return now;
}

// ------------------------------------------------------------
// 0x698F90  clock_set_countdown(clk, duration=a2, startTime=a3)
// 反编译直证:
//   if (!enabled || running) return;
//   running = 1;
//   if (frozen) frozenValue = startTime;            // 冻结中: 绝对值
//   else        offset    = startTime - tick[domain];
//   duration = duration;
// (注: 反编译里 frozenValue 写了两次, 编译器冗余, 语义一次)
// ------------------------------------------------------------
void clock_set_countdown(PauseClock* clk, int duration, int startTime)  // 实现：clock_set_countdown(clk, duration=a2, startTime=a3)
{
    if (clk->enabled == 0)  // 若 clk.enabled == 0
        return;
    if (clk->running != 0)  // 若 clk.running != 0
        return;

    clk->running = 1;
    if (clk->frozen != 0)  // 若 clk.frozen != 0
        clk->frozenValue = startTime;
    else  // 否则分支
        clk->offset = startTime - g_domainTick[clk->domainId];  // 折算偏移：绝对时刻 − 域计数（后续 now = offset + 域计数）
    clk->duration = duration;
}

// ------------------------------------------------------------
// 0x698FE0  clock_unfreeze(clk)
// 反编译直证: 仅当 frozen 时动作: frozen=0; offset = frozenValue - tick[domain]
// ------------------------------------------------------------
void clock_unfreeze(PauseClock* clk)  // 实现：clock_unfreeze(clk)
{
    if (clk->frozen != 0) {  // 若 clk.frozen != 0
        clk->frozen = 0;
        clk->offset = clk->frozenValue - g_domainTick[clk->domainId];  // 解冻：以定格值重算偏移，保持 now 连续
    }
}

// ------------------------------------------------------------
// 0x699000  clock_now(clk)
// 反编译直证:
//   if (!enabled || !running) return 0;
//   if (frozen) return frozenValue;          // ★ hit stop: 时间停在这里
//   return offset + tick[domain];
// ------------------------------------------------------------
int clock_now(const PauseClock* clk)  // 实现：clock_now(clk)
{
    if (clk->enabled == 0 || clk->running == 0)  // 若 clk.enabled == 0 || clk->running …
        return 0;
    if (clk->frozen != 0)  // 若 clk.frozen != 0
        return clk->frozenValue;  // 返回 clk->frozenValue
    return clk->offset + g_domainTick[clk->domainId];
}

// ------------------------------------------------------------
// 0x699030  clock_freeze(clk)
// 反编译直证: 未冻结才动作:
//   enabled && running -> frozenValue = offset + tick[domain]; frozen = 1
//   否则               -> frozenValue = 0; frozen = 1; (返回 0)
// 引擎级效果: dt = clock_now() - last 恒为 0 → 一切按时间推进的更新停摆。
// ------------------------------------------------------------
void clock_freeze(PauseClock* clk)  // 实现：clock_freeze(clk)
{
    if (clk->frozen != 0)  // 若 clk.frozen != 0
        return;

    if (clk->enabled != 0 && clk->running != 0) {  // 若 clk.enabled != 0 && clk->running …
        clk->frozenValue = clk->offset + g_domainTick[clk->domainId];  // 冻结：把当前 now 存入定格值（此后 now 恒定）
        clk->frozen = 1;
    } else {
        clk->frozenValue = 0;
        clk->frozen = 1;
    }
}

// ------------------------------------------------------------
// 0x699070  clock_bind_domain(clk, newDomainId)   【新发现】
// 反编译直证: 仅 newDomainId < 16 时动作:
//   now = (enabled && running) ? (frozen ? frozenValue : offset + tick[domain]) : 0;
//   wasNotFrozen = !frozen;
//   domainId = newDomainId;
//   if (wasNotFrozen) offset = now - tick[domainId];   // 未冻结: 保持 now 连续
//   else              frozenValue = now;               // 冻结中: 定格值保持
// 语义: 运行中把时钟换到另一条时间域（如主时钟域 ↔ 某演出域）而不跳变。
// ------------------------------------------------------------
void clock_bind_domain(PauseClock* clk, unsigned int newDomainId)  // 实现：clock_bind_domain(clk, newDomainId)   (新发现)
{
    if (newDomainId >= 16)  // 若 newDomainId >= 16
        return;

    int now = 0;
    if (clk->enabled != 0 && clk->running != 0) {  // 若 clk.enabled != 0 && clk->running …
        if (clk->frozen != 0)  // 若 clk.frozen != 0
            now = clk->frozenValue;
        else  // 否则分支
            now = clk->offset + g_domainTick[clk->domainId];
    }

    int wasNotFrozen = (clk->frozen == 0);
    clk->domainId = (int)newDomainId;
    if (wasNotFrozen)
        clk->offset = now - g_domainTick[clk->domainId];  // 未冻结换域：重算偏移使 now 不跳变
    else  // 否则分支
        clk->frozenValue = now;  // 冻结中换域：定格值随域平移
}
