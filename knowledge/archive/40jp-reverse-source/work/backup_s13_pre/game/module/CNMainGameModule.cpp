// ============================================================
// 【40JP逆向源代码工程】src/game/module/CNMainGameModule.cpp
// ARAD.exe 主游戏模块 + 主帧循环 + 模块切换处理器
//
// 虚表布局（RTTI 实测）:
//   段1 VT 0x006C2B98（IModule 系，5 槽）:
//     vmt+0x00 0x41C7C0 标量删除析构 → 0x41C7F0 实析构
//     vmt+0x04 0x444C60 ★ 每帧 tick（模块心跳）
//     vmt+0x08 0x444C20 模块退出清理
//     vmt+0x0C 0x41F930 存根（返 true）—— 各模块共享基实现
//     vmt+0x10 0x4B1090 空桩        —— 各模块共享基实现
//   段2 VT 0x006C2B90（1 槽，次接口）: vmt+0 0x47A920 空桩
//
// 模块类型枚举（switch 直证 + 日志字符串自证）:
//   1 = MAIN_GAME / 2 = SELECT_DUNGEON / 4 = PVP / 6 = WARROOM
//   0/3/5 未在字符串中自证【待验证】
// ============================================================

#include "../../nengine/time_system.h"
#include "../../nengine/camera_fx.h"
#include <string.h>

extern char g_szPassword[];   // szPassword 全局缓冲（IDA 名；快门去重用）

// ============================================================
// 虚调用辅助（vtable 槽位按字节偏移）
// ============================================================
static int vcall(void* obj, unsigned byteSlot)
{
    return (*(int(__thiscall**)(void*))(*(void**)obj + byteSlot))(obj);
}
static int vcall1(void* obj, unsigned byteSlot, int a)
{
    return (*(int(__thiscall**)(void*, int))(*(void**)obj + byteSlot))(obj, a);
}
static int vcall2(void* obj, unsigned byteSlot, int a, int b)
{
    return (*(int(__thiscall**)(void*, int, int))(*(void**)obj + byteSlot))(obj, a, b);
}

// ---- 引擎输出（off_77F3FC 函数指针槽 = 引擎错误/调试输出，42 轮研究已定案） ----
extern int engine_log(const char* fmt, ...);

// ---- 全局对象指针（.data；身份随对应模块重建逐步定案） ----
static void* addr_79C0A0   = (void*)0x79C0A0;  // (+32 = 快门特性开关)
static void* addr_79C0A4   = (void*)0x79C0A4;  // (vt+4 = 退出提交)
static void* addr_79C0B0   = (void*)0x79C0B0;  // (vt+28/84/88 = 场景管理)
static void* addr_79C0B4   = (void*)0x79C0B4;  // (vt+16/20 = 退出确认对话)
static void* addr_8F8520   = (void*)0x8F8520;  // 会话/UDP 管理器（vt+152 = 停 UDP）
static void* addr_8F8524   = (void*)0x8F8524;
static void* addr_8F8528   = (void*)0x8F8528;  // 主管理器（+2484 fade 镜像 / +4 观战标志）
static void* addr_8F850C   = (void*)0x8F850C;  // 模块上下文表 [16..32)
static DWORD g_8F8760      = 0;                // 主循环帧锚
static DWORD g_8F8764      = 0;                // 主循环锚初始化标志
static BYTE  g_8F8554      = 0;                // 声音延迟队列使能
static BYTE  g_8F875C      = 0;                // 快门参数
static BYTE  g_77F280      = 0;                // 退出请求标志
static DWORD g_77F488      = 0;                // 战斗类模块标志（to 3/4/6 → 0，其余 1）
static CRITICAL_SECTION g_cs_8F8258;           // 主帧临界区 0x8F8258
extern void* g_socketGlobal;                   // 0x8F7B08 网络连接对象（camera_fx.h）
extern void* g_localPlayer;                    // 0x8F7C04
static DWORD g_8F7C08      = 0;
static DWORD g_978998      = 0;
static unsigned short g_77F804 = 0;            // word_77F804（选区 id）

// ============================================================
// 未还原辅助函数（保留原 VA 名；对应模块重建时归位）
// ============================================================
extern void sub_4AEB30(void*);                 // 0x4AEB30 帧开始钩
extern void sub_655A90(float dt);              // 0x655A90 场景推进（秒）
extern void sub_4294E0(void*);                 // 0x4294E0 演出管理器 tick
extern void sub_475810(void*, void*, int, int);// 0x475810 进副本一次性震屏+物件生成
extern void sub_4284C0(int, int);              // 0x4284C0 进副本坐标提交
extern void sub_423200(void*, char);           // 0x423200 发包开始（网络对象）
extern void sub_423380(void*);                 // 0x423380 发包提交（网络对象）
extern int  sub_444B30(int);                   // 0x444B30 退场完成回调
extern int  sub_41D300(int);                   // 0x41D300 黑屏完成回调
extern void sub_65FAF0(void*, int);            // 0x65FAF0 声音延迟队列打点（研究 P32/P34）
extern int  sub_656710(void);                  // 0x656710 声音通道表获取
extern void sub_656AA0(int);                   // 0x656AA0 声音通道 tick
extern void sub_45E1A0(void*);                 // 0x45E1A0
extern void CNCommandChecker_vmt4(void*);      // RTTI 自证类 CNCommandChecker 的帧 tick
extern void sub_451D50(void*);                 // 0x451D50 主管理器 tick
extern int  sub_415660(int, char);             // 0x415660 特性开关查询
extern int  sub_6997C0(void*);                 // 0x6997C0
extern void sub_65FE10(void*, const char*, int, int, int, int, int, int); // 0x65FE10 音效 TAG 分发
extern void sub_43BEE0(void*, int, int, int, int); // 0x43BEE0 屏幕彩色横幅
extern void sub_41C1E0(void*);                 // 0x41C1E0 退出清理（文末）
extern void sub_41A170(void);                  // 0x41A170
extern void sub_69AB00(void*);                 // 0x69AB00
extern void sub_41FD50(void);                  // 0x41FD50
extern void sub_6989F0(void*);                 // 0x6989F0 ISocket 关闭/析构
extern void sub_4772A0(int);                   // 0x4772A0
extern void sub_45A420(int);                   // 0x45A420
extern void sub_425500(int);                   // 0x425500
extern void sub_424100(int);                   // 0x424100
extern void sub_475760(void);                  // 0x475760
extern void sub_472AF0(void);                  // 0x472AF0
extern void sub_44E850(void*, int);            // 0x44E850 播报层横幅（模式切换）
extern void sub_44E8D0(void*, void*, void*, int); // 0x44E8D0 播报层横幅（带内容）
extern void sub_46E3B0(void*);                 // 0x46E3B0
extern void* sub_422E70(int);                  // 0x422E70 字符串表取串
extern void sub_46D300(void*);                 // 0x46D300
extern void sub_45B250(void*);                 // 0x45B250
extern void sub_445830(int);                   // 0x445830
extern void sub_461110(int);                   // 0x461110
extern void sub_65DC70(void*);                 // 0x65DC70 声音全停
extern int  sub_429830(unsigned short);        // 0x429830 选区表查找
extern void sub_657230(void*);                 // 0x657230
extern void sub_45DF90(void*);                 // 0x45DF90
extern void sub_4461F0(void*);                 // 0x4461F0
extern void sub_45B0A0(void*);                 // 0x45B0A0
extern void sub_425960(int, int, int);         // 0x425960
extern void sub_458400(void*);                 // 0x458400
extern void sub_42FC50(void);                  // 0x42FC50
extern void sub_41C3D0(unsigned char);         // 0x41C3D0
extern void sub_453A60(void*);                 // 0x453A60
extern void sub_432EA0(const char*, int, int, int); // 0x432EA0 音效标签发送器（研究 P9c）
extern void sub_453AC0(void*);                 // 0x453AC0
extern void sub_456210(void*);                 // 0x456210
extern void sub_445960(void*);                 // 0x445960
extern void sub_6560A0(void*);                 // 0x6560A0
extern void sub_656630(int);                   // 0x656630
extern int  sub_656840(int);                   // 0x656840
extern void sub_656090(void*);                 // 0x656090
extern void sub_444BE0(void*);                 // 0x444BE0
extern void sub_425460(void*);                 // 0x425460
extern void sub_41C190(int);                   // 0x41C190
extern void sub_453230(void*);                 // 0x453230
extern void sub_42EE80(void*);                 // 0x42EE80
extern void sub_46EF40(void*);                 // 0x46EF40
extern void sub_44EA20(int, int);              // 0x44EA20 模块切换收尾
extern void sub_45F4D0(int);                   // 0x45F4D0
extern int  sub_456420(void*);                 // 0x456420

// ============================================================
// CNMainGameModule —— 已知字段（反汇编实测，对象大小未定案）【部分】
//
//   +0x10(16) 演出管理器指针（CameraFxManager*，EA0/4294E0 接收者）
//   +0x14(20) fade 状态: 0无 / 1进场淡入 / 2过场 / 3退场淡出 / 4黑屏
//   +0x18(24) fade 时钟（PauseClock）
//   +0x34(52) / +0x38(56) 进副本参数对（sub_475810/4284C0）
//   +0x3C(60) fade 值（镜像到 dword_8F8528+2484）
//   +0x5C(92) 模块时钟（PauseClock；演出期间冻结）
//   +0x6A(106) 模块时钟解冻门（byte）
//   +0x78(120) 模块时钟上次读数
//   +0x11C(284) / +0x128(296) / +0x15C(348) 上下文（switch 用）
//   +0x14..0x28 各模块上下文指针（switch: +20/+24/+28/+32/+36/+40）
// ============================================================

// ------------------------------------------------------------
// 0x444C60 —— CNMainGameModule::vmt4 每帧 tick（模块心跳）
// ------------------------------------------------------------
int CNMainGameModule_onFrameTick(void* thisp)
{
    char* this = (char*)thisp;
    CameraFxManager* fxm = *(CameraFxManager**)(this + 16);

    sub_4AEB30((void*)0x9A02B0);          // 帧开始（原文参数 &unk_9A02B0）
    main_frame_loop();                    // 0x433690

    if (*(int*)(this + 20) != 0) {        // fade 状态非 0 → 演出期间冻结模块时钟
        clock_freeze((PauseClock*)(this + 92));
    } else {
        if (*(BYTE*)(this + 106) != 0)
            clock_unfreeze((PauseClock*)(this + 92));
        int now = clock_now((PauseClock*)(this + 92));
        int last = *(int*)(this + 120);  // 读字段 last = this+120（pAnimObj）
        *(int*)(this + 120) = now;  // 写字段 this+120（pAnimObj） ← now
        float dt = (float)((now - last) * 0.001);
        sub_655A90(dt);                   // 场景推进（dt 单位 = 秒）
    }

    // 镜头震动用户设置四档（研究第 27 轮直证：0/30/70/100%）
    switch (*(DWORD*)((char*)0x8F8548 + 8)) {
    case 0: fxm_apply_user_strength(fxm, 0.0f);        break;  // case 0 分派
    case 1: fxm_apply_user_strength(fxm, 0.30000001f); break;  // case 1 分派
    case 2: fxm_apply_user_strength(fxm, 0.69999999f); break;  // case 2 分派
    case 3: fxm_apply_user_strength(fxm, 1.0f);        break;  // case 3 分派
    default: break;
    }
    sub_4294E0(fxm);  // sub_4294E0 —— HUD 每帧总 tick（尾段）

    // ---- fade 状态机（时钟 this+24；fade 值 this+60 镜像 8F8528+2484）----
    int state = *(int*)(this + 20);  // 读字段 state = this+20（nPage）
    if (state != 0) {
        switch (state) {
        case 1: {   // 进场淡入 0→255 / 250ms
            if (*(int*)(this + 60) == 255) {
                sub_475810(*(void**)(*(char**)fxm + 108), thisp,
                           *(int*)(this + 52), *(int*)(this + 56));
                sub_4284C0(*(int*)(this + 52), *(int*)(this + 56));  // sub_4284C0 —— 场景格切换装配
                sub_423200(g_socketGlobal, 40);   // 发包 type=40（进副本完成）
                sub_423380(g_socketGlobal);  // sub_423380 —— 发包提交：Commit()
                *(int*)(this + 20) = 2;  // 写字段 this+20（nPage） ← 2
                *(BYTE*)(this + 37) = 0;  // 写字段 this+37（bFadeFlag37） ← 0
                *(BYTE*)(this + 38) = 0;  // 写字段 this+38（bFadeFlag38） ← 0
                clock_set_countdown((PauseClock*)(this + 24), 0, 0);
                *(int*)(this + 60) = 0;  // 写字段 this+60（nFadeValue60） ← 0
            } else {
                int now = clock_now((PauseClock*)(this + 24));
                int v = (int)lerp_f(0.0f, 255.0f, now, 250);
                *(int*)(this + 60) = v;  // 写字段 this+60（nFadeValue60） ← v
                *(int*)((char*)addr_8F8528 + 2484) = v;
            }
            break;
        }
        case 2:                                     // 过场（无动作）
            break;
        case 3: {   // 退场淡出 255→0 / 250ms
            int now = clock_now((PauseClock*)(this + 24));
            int v = (int)lerp_f(255.0f, 0.0f, now, 250);
            *(int*)(this + 60) = v;  // 写字段 this+60（nFadeValue60） ← v
            *(int*)((char*)addr_8F8528 + 2484) = v;
            if (v == 0)
                sub_444B30(0);  // sub_444B30 —— fade 状态机复位 写 fade 状态
            break;
        }
        case 4: {   // 黑屏 0→255 / 500ms → sub_41D300(1)
            if (*(int*)(this + 60) == 255) {
                sub_41D300(1);  // sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
            } else {
                int now = clock_now((PauseClock*)(this + 24));
                int v = lerp_i(0, 255, now, 500);
                *(int*)(this + 60) = v;  // 写字段 this+60（nFadeValue60） ← v
                *(int*)((char*)addr_8F8528 + 2484) = v;
            }
            break;
        }
        default:
            break;
        }
    }
    return state;
}

// ------------------------------------------------------------
// 0x444C20 —— CNMainGameModule::vmt8 模块退出清理
// ------------------------------------------------------------
int CNMainGameModule_onExit(void* thisp)
{
    char* this = (char*)thisp;
    vcall1(addr_79C0B0, 28, 0);  // 虚调用 vt+28（addr_79C0B0 虚表槽）
    vcall(addr_79C0B0, 84);  // 虚调用 vt+84（addr_79C0B0）退出可视/停止
    sub_69AB00(*(void**)(this + 12));
    vcall(addr_79C0B0, 88);  // 虚调用 vt+88（addr_79C0B0 虚表槽）
    return vcall2(addr_79C0A4, 4, 0, 0);
}

// ------------------------------------------------------------
// 0x433690 —— 主帧循环（引擎心跳，被模块 vmt4 调用）
// ------------------------------------------------------------
char main_frame_loop(void)
{
    LeaveCriticalSection(&g_cs_8F8258);   // 让网络线程进临界区
    EnterCriticalSection(&g_cs_8F8258);

    if ((g_8F8764 & 1) == 0) {            // 首帧建立时间锚
        g_8F8764 |= 1;
        g_8F8760 = timeGetTime();
    }
    int elapsed = timeGetTime() - g_8F8760;

    if (g_8F8554 != 0) {                  // 声音延迟队列打点（研究 P32 直证调用点）
        sub_65FAF0(0, elapsed);           // （原文首参 = 声音临界区全局）
        g_8F8760 = timeGetTime();
    }

    sub_656AA0(sub_656710());             // 声音通道 tick
    vcall(addr_8F8520, 116);              // 会话管理 vt+116 tick
    sub_45E1A0(addr_8F8524);
    CNCommandChecker_vmt4((void*)0x8F8558);   // RTTI 自证：CNCommandChecker
    sub_451D50(addr_8F8528);              // 主管理器 tick

    // 快门/拍照特性（0x79C0A0+32 开关 + 特性 44 查询；防重复播报）
    if (*(int*)((char*)0x79C0A0 + 32) != 0 && sub_415660(44, g_8F875C) != 0) {  // sub_415660 —— GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
        int v2 = sub_6997C0((void*)0x9D3BE0);
        if (strcmp("SHUTTER_ON", g_szPassword) != 0)   // szPassword 全局缓冲
            sub_65FE10(0, "SHUTTER_ON", 0, 0, 0, 0, 0xFFFF, -1);  // sub_65FE10 —— 按标签名播声音：命中则立即播或入延迟队列，否则打 Tag Missing
        sub_43BEE0(*(void**)((char*)addr_8F8528 + 28), v2, -5000269, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    }

    char result = g_77F280;               // 退出请求
    if (result != 0) {
        if (vcall1(addr_79C0B4, 20, 10) != 0) {       // vt+20(10) 确认对话
            if (vcall1(addr_79C0B4, 16, 84) != 0) {   // vt+16(84)
                sub_41C1E0(g_socketGlobal);           // 退出清理
            }
        }
    }
    return result;
}

// ------------------------------------------------------------
// 0x41CC80 —— 模块切换处理器（from=ArgList, to=a3；巨型迁移矩阵）
// 未还原被调函数保留原 VA 名；结构/条件/日志串逐条对齐反编译原文。
// ------------------------------------------------------------
void on_change_module(void* mgr, int fromModule, int toModule)
{
    char* this = (char*)mgr;
    if (fromModule == toModule)
        return;
    engine_log("[onChangeModule] %d -> %d", fromModule, toModule);  // byte_6C2CE8 格式串
    sub_41A170();  // sub_41A170 —— 登记表整体重置（遍历元素 + 清空 deque）

    if (toModule == 3 || toModule == 4 || toModule == 6)  // 判定 toModule == 3 或 toModule == 4 或 toModule == 6
        g_77F488 = 0;                     // 战斗类模块 → 标志 0
    else
        g_77F488 = 1;

    switch (fromModule) {
    case 1:  // case 1 分派
        if (*(int*)(*(int*)(this + 20) + 216) == 1)
            *(int*)(*(int*)(this + 20) + 216) = -1;
        break;
    case 3:  // case 3 分派
        sub_4772A0(0);  // sub_4772A0 —— 结算事件：M_RESULT 打开结算界面
        sub_45A420(0);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
        if (*(int*)(*(int*)(this + 28) + 16) != 0) {
            sub_425500(0);  // sub_425500 —— 锚定对象换绑
            sub_424100(0);  // sub_424100 —— 关联对象 setter
            sub_475760();
            *(int*)(*(int*)(*(int*)(this + 28) + 16) + 108) = 0;
            sub_472AF0();
        }
        break;
    case 4:   // 离开 PVP
        *(int*)((char*)addr_8F8528 + 2484) = 0;
        engine_log("@@UDP STOP - onChangeModule(), MODULE_TYPE_PVP 1");
        vcall(addr_8F8520, 152);          // 停 UDP
        break;
    case 5:  // case 5 分派
        sub_44E850(addr_8F8528, 27);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
        sub_46E3B0(*(int*)(this + 36));  // sub_46E3B0 —— 退出模块 5 清场（频道状态清零）
        break;
    case 6:   // 离开 WARROOM
        *(int*)((char*)addr_8F8528 + 2484) = 0;
        engine_log("@@UDP STOP - onChangeModule(), MODULE_TYPE_WARROOM 1");
        vcall(addr_8F8520, 152);  // 虚调用 vt+152（addr_8F8520）取值(参数)
        if (*(int*)(*(int*)(this + 40) + 188) == 1)
            sub_44E8D0(addr_8F8528, (void*)0x1B, sub_422E70(1925), 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）；sub_422E70 —— 存 CStringManager::getStr 取本地化串
        else if (*(int*)(*(int*)(this + 40) + 188) == 2)
            sub_44E8D0(addr_8F8528, (void*)0x1B, sub_422E70(1926), 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）；sub_422E70 —— 存 CStringManager::getStr 取本地化串
        break;
    default:
        break;
    }

    // ---- 目标模块初始化 ----
    switch (toModule) {
    case 0:  // case 0 分派
        *(int*)(this + 284) = *(int*)(*(int*)(this + 36) + 12);  // 写字段 this+284（bBindGate284） ← *(int*)(*(int*)(this + 36) + 12)
        sub_46D300(*(int*)(this + 16));  // sub_46D300 —— 选角界面复位与资源释放
        break;
    case 1:   // 进 MAIN_GAME
        sub_45B250(*(int*)(this + 20));  // sub_45B250 —— 激活态重置 + 锚定当前角色
        vcall1(addr_8F8520, 124, *(int*)(*(int*)(this + 20) + 44));  // 虚调用 vt+124（addr_8F8520）目标坐标y下界
        sub_445830(0);  // sub_445830 —— 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
        vcall(addr_8F8520, 112);  // 虚调用 vt+112（addr_8F8520）坐标三元组写入
        sub_461110(0);  // sub_461110 —— 按钮选中态 setter（+1236）
        if (*(int*)(this + 348) == 4) {
            sub_44E8D0(addr_8F8528, (void*)2, 0, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
            sub_43BEE0(*(void**)((char*)addr_8F8528 + 28), (int)sub_422E70(1249),  // sub_43BEE0 —— 【播报上屏】；sub_422E70 —— 存 CStringManager::getStr 取本地化串
                       -6567706, 0, -1);
        }
        if (fromModule != 0) {
            switch (fromModule) {
            case 2:  // case 2 分派
            case 3: {   // 从选区/入场进副本
                sub_65DC70(0);                    // 声音全停
                g_shakeRateX = 100;               // 0x79D0C4 复位基线（仅 X！）
                for (int i = 16; i < 32; i += 4) { // 4 个模块上下文槽
                    int ctx = *(int*)(i + (char*)addr_8F850C);
                    if (ctx != 0) {
                        int obj = *(int*)(ctx + 196);  // 读字段 obj = ctx+196
                        if (obj != 0)
                            vcall(obj, 1020);     // vt+1020
                    }
                }
                if (*(int*)(sub_429830(g_77F804) + 184) == 0) {  // sub_429830 —— 结果 = 表按键查找（uint16）
                    engine_log("@@UDP STOP - onChangeModule(), MODULE_TYPE_MAIN_GAME || "
                               "MODULE_TYPE_SELECT_DUNGEON 1");
                    vcall(addr_8F8520, 152);  // 虚调用 vt+152（addr_8F8520）取值(参数)
                }
                sub_657230(*(void**)((char*)addr_8F8520 + 1049988));  // sub_657230 —— 关闭网络（断连标记 + 清理 + closesocket）
                sub_45DF90(addr_8F8524);  // sub_45DF90 —— 中继(relay) 连接（_RELAY 自证）
                sub_4461F0(addr_8F8520);  // sub_4461F0 —— PVP ping/SNAT 日志上报（包 105）
                sub_45B0A0(*(int*)(this + 20));  // sub_45B0A0 —— 引导（教程）对象登记转发
                sub_425960(0,  // sub_425960 —— 播放/暂停级联广播
                           *(int*)(*(int*)(*(int*)(this + 20) + 44) + 44),
                           *(int*)(*(int*)(*(int*)(this + 20) + 44) + 104));
                vcall(addr_8F8520, 164);  // 虚调用 vt+164（addr_8F8520 虚表槽）
                sub_458400(*(void**)((char*)addr_8F8528 + 2436));  // sub_458400 —— 奖励模式执行
                break;
            }
            case 4:   // PVP → 副本
                sub_45F4D0(273);  // sub_45F4D0 —— 按类型批量注销
                vcall1(g_localPlayer, 1056, 1);  // 虚调用 vt+1056（g_localPlayer 虚表槽）
                sub_432EA0("LADDER_DOWN", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
                break;
            case 6:   // WARROOM → 副本
                sub_45F4D0(273);  // sub_45F4D0 —— 按类型批量注销
                vcall1(g_localPlayer, 1056, 1);  // 虚调用 vt+1056（g_localPlayer 虚表槽）
                break;
            default:
                break;
            }
        }
        if (g_8F7C08 != 0)
            sub_42FC50();  // sub_42FC50 —— 商店查询转发（+656）
        sub_41C3D0(*(BYTE*)(this + 296));  // sub_41C3D0 —— 状态提示刷新（资源 843/844 文本 + 条件触发）
        break;
    case 2:   // 进 SELECT_DUNGEON
        sub_453A60(*(int*)(this + 24));  // sub_453A60 —— (this+24 对象)
        sub_65DC70(0);  // sub_65DC70 —— FSOUND 全停：50 个 48B 通道槽逐个 sub_65D8B0 停止，再摘 +2560 处播放链所有结点
        engine_log("STOP SOUND");
        sub_432EA0("MAP_APPEAR", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        for (int j = 16, idx = 0; j < 32; j += 4, ++idx) {
            int ctx = *(int*)(j + (char*)addr_8F850C);
            if (ctx != 0) {
                int obj = *(int*)(ctx + 196);  // 读字段 obj = ctx+196
                if (obj != 0) {
                    vcall(obj, 1020);  // 虚调用 vt+1020（obj 虚表槽）
                    vcall1(obj, 1200, 1);  // 虚调用 vt+1200（obj）(nArg1) —— 全体广播族。
                    vcall1(obj, 1212, 0);  // 虚调用 vt+1212（obj 虚表槽）
                }
            }
            (void)idx;
        }
        if (vcall(addr_8F8520, 156) == 0) {
            int seat = sub_456420(addr_8F850C);  // sub_456420 —— 存 座位查找
            engine_log("@@UDP START - onChangeModule(), MODULE_TYPE_SELECT_DUNGEON : "
                       "seatIndex %d /// 1", seat);
            vcall1(addr_8F8520, 148, seat);  // 虚调用 vt+148（addr_8F8520）位置/朝向写入
        }
        sub_453AC0(*(int*)(*(int*)(this + 20) + 44));  // sub_453AC0 —— 锚定对象换装
        sub_425960(1,  // sub_425960 —— 播放/暂停级联广播
                   *(int*)(*(int*)(*(int*)(this + 24) + 68) + 44),
                   *(int*)(*(int*)(*(int*)(this + 24) + 68) + 104));
        sub_456210(*(void**)(*(int*)(*(int*)(this + 20) + 104) + 40));
        sub_4461F0(addr_8F8520);  // sub_4461F0 —— PVP ping/SNAT 日志上报（包 105）
        sub_445960(addr_8F8520);  // sub_445960 —— 四槽状态快照刷新
        sub_6560A0((void*)0x8F8548);  // sub_6560A0 —— 释放记录表后整表复位（主状态归 0）
        for (int k = 0; k < 8; ++k) {
            if (*(int*)(sub_656710() + 4 * k) != -1)  // sub_656710 —— 取全局单例地址（返回 unk_9BD5D0）
                sub_656630(k);  // sub_656630 —— 单条复位（+4 置 60.0 + 统计非 3 条数）
        }
        sub_656630(sub_656840(sub_656710()));
        sub_656090((void*)0x8F8548);  // sub_656090 —— 整表复位后主状态置 1
        break;
    case 3:  // case 3 分派
        sub_444BE0(*(int*)(this + 28));  // sub_444BE0 —— (this+28 场景对象)
        sub_461110(0);  // sub_461110 —— 按钮选中态 setter（+1236）
        sub_44E850(addr_8F8528, 55);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
        vcall1(addr_8F8520, 124, *(int*)(*(int*)(this + 28) + 16));  // 虚调用 vt+124（addr_8F8520）目标坐标y下界
        if (fromModule == 2) {
            sub_425460(*(int*)(*(int*)(this + 28) + 16));  // sub_425460 —— 模式切换清理
            sub_41C190(0);  // sub_41C190 —— 级联通知转发（this+44 / this+104 作上下文）【推断】
            *(int*)((char*)addr_8F8528 + 2484) = 0;
            vcall(addr_8F8520, 160);  // 虚调用 vt+160（addr_8F8520 虚表槽）
        }
        break;
    case 4:   // 进 PVP
        sub_461110(1);  // sub_461110 —— 按钮选中态 setter（+1236）
        sub_453230(*(int*)(this + 32));  // sub_453230 —— (this+32 对象)
        vcall1(addr_8F8520, 124, *(int*)(*(int*)(this + 32) + 16));  // 虚调用 vt+124（addr_8F8520）目标坐标y下界
        sub_432EA0("LADDER_DOWN", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        break;
    case 5:  // case 5 分派
        *(BYTE*)(this + 60) = 0;          // 原文按字节写 this+60（与 fade 值同址）
        g_978998 = 0;
        sub_46EF40(*(int*)(this + 36));  // sub_46EF40 —— CNEntranceChannel 数据/HTTP 线程初始化（进模块 5）
        break;
    case 6:   // 进 WARROOM
        sub_461110(1);  // sub_461110 —— 按钮选中态 setter（+1236）
        sub_42EE80(*(int*)(this + 40));  // sub_42EE80 —— (this+40 对象)
        vcall1(addr_8F8520, 124, *(int*)(*(int*)(this + 40) + 16));  // 虚调用 vt+124（addr_8F8520）目标坐标y下界
        break;
    default:
        break;
    }

    sub_44EA20(fromModule, toModule);     // 收尾
}

// ------------------------------------------------------------
// 0x41C1E0 —— 退出清理（__noreturn；PostQuitMessage + exit(0)）
// dword_8F7B08 = 网络连接对象（ISocket 族，0x6989F0 = 其关闭/析构）
// ------------------------------------------------------------
void game_shutdown_and_exit(void* socketObj)
{
    sub_65DC70(0);                        // 声音全停（原文传声音临界区全局）
    sub_6989F0(socketObj);                // ISocket 关闭
    PostQuitMessage(0);
    sub_41FD50();  // sub_41FD50 —— 引擎管理器群关停/反初始化
    exit(0);
}
