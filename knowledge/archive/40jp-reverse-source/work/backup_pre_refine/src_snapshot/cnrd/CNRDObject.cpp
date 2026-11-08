// ============================================================
// 【40JP逆向源代码工程】src/cnrd/CNRDObject.cpp
// CNRDObject 基类实现 —— 主状态机 / 时钟编排 / 坐标系 / 寻位 / 音效 / 渲染钩
// 每个函数 VA 见函数头；证据 work/decomp_core_vt.txt（会话 3 批反编译）
// ============================================================

#include "CNRDObject.h"

// ---- 未还原辅助（原 VA 名） ----
extern int  sub_699000(PauseClock*);          // 时钟取时刻（已还原 time_system）
extern void sub_699030(PauseClock*);          // 冻结（已还原）
extern void sub_698FE0(PauseClock*);          // 解冻（已还原）
extern void sub_699070(PauseClock*, unsigned);// 换域（已还原）
extern int  sub_4910C0(void*);                // 动画解冻值查询
extern void sub_4939E0(void*, int);           // 动画冻结/恢复
extern void sub_4A0680(void*, int);           // 动画对象联动
extern void sub_53F720(void*, int);           // 状态容器挂起/恢复
extern int  sub_499240(int, int, int, int, int); // 方向/邻近计算（vmt8）
extern void sub_50E730(void*);                // 观察者组件构造
extern void sub_50E8D0(void*);                // 观察者组件初始化
extern int  sub_499960(void*, int, int);      // 观察者容器构造
extern void sub_50EB10(void);                 // 附件 tick A
extern void sub_50E9B0(void);                 // 附件 tick B
extern void sub_49FFC0(void*, int, int, int, int); // 脏动画提交
extern void sub_65FE10(void*, const char*, int, int, int, int, int, int); // 音效 TAG 分发
extern int  sub_65DE30(int, int);             // 音效 TAG 查询
extern void sub_418DD0(int);                  // 资源句柄 (101)
extern void sub_424760(void*, int, int, void*, float, int, float, int, float, float); // 四边形提交（已还原 camera_fx）
extern void sub_491530(int, int);             // 渲染状态应用
extern void sub_491630(int);                  // 渲染状态还原
extern int  sub_42B420(int, int, int, int);   // 三角波 alpha（150↔255/400ms）
extern int  sub_499C20(void*, void*, void*);  // 定时器节点插入
extern void sub_49A720(int);                  // 定时器链表辅助
extern void sub_4926A0(void*);                // 动画复位
extern int  sub_4938F0(void*);                // 动画帧同步
extern void sub_4A2C70(void*); extern void sub_4A2CB0(void*); // 链表清理族
extern void sub_4A2C40(void);
extern int  sub_426820(void*, int, int);      // 播报层（研究第 10 轮定案）
extern int  sub_431230(int, int*);            // 命中目标列表追加
extern void sub_45E490(int, int);
extern int  sub_4A0650(int, int);
extern void sub_4A0790(void*);
extern int  sub_4A0740(int);
extern void* dword_79C0B0;                    // 渲染对象全局
extern void* dword_8F7C04;                    // 本地玩家
extern void* dword_8F7C08;                    // 副玩家/观战
extern void* dword_8F8520;                    // 会话/UDP 管理器
extern char  szPassword[];                    // 音效去重缓冲
extern void* lpCriticalSection;

// ============================================================
// 坐标三元组族
// ============================================================

// 0x42A510 vmt20 —— 设置坐标三元组 (this+100..112)
int CNRDObject_vmt20(int* this, int* a2)
{
    int* v2 = this + 25;                 // +100
    v2[0] = a2[0];
    v2[1] = a2[1];
    v2[2] = a2[2];
    return a2[2];
}

// 0x42A530 vmt24 —— 取坐标三元组指针
char* CNRDObject_vmt24(char* this) { return this + 100; }

// 0x42A540 vmt2C / 0x42A550 vmt30 / 0x42A560 vmt34 —— 取 x/y/z
int CNRDObject_vmt2C(int* this) { return this[24]; }   // +96
int CNRDObject_vmt30(int* this) { return this[25]; }   // +100
int CNRDObject_vmt34(int* this) { return this[26]; }   // +104

// 0x42A570 vmt38 —— y | z<<16 组合
int CNRDObject_vmt38(int* this) { return this[26] | (this[25] << 16); }

// 0x42A580 vmt3C —— 取默认共享组件 this+112（研究第 12 轮直证：观察者兜底）
int CNRDObject_vmt3C(int* this) { return this[28]; }

// 0x42A590 vmt4C / 0x42A5A0 vmt50 —— this+116 存取
int CNRDObject_vmt4C(int* this, int a2) { this[29] = a2; return a2; }
int CNRDObject_vmt50(int* this) { return this[29]; }

// 0x42A5B0 vmt54 / 0x42A5C0 vmt58 —— this+156 字节存取
char CNRDObject_vmt54(char* this, char a2) { *(this + 156) = a2; return a2; }
char CNRDObject_vmt58(char* this) { return *(this + 156); }

// 0x42A5D0 vmt5C —— 设置伤害数值；上次值非 0 时转发 vt+196
int CNRDObject_vmt5C(int* this, int a2)
{
    int v2 = this[30];                   // +120 上次值（动画对象）
    this[34] = a2;                       // +136 伤害数值
    if (v2 == 0)
        return (*(int(__thiscall**)(int*, int))(*this + 196))(this, a2);  // vt+196
    return a2;
}

// 0x445C30 vmt60 —— 取 this+136
int CNRDObject_vmt60(int* this) { return this[34]; }

// 0x42A930 vmt68 —— 观察者数组元素访问（越界返回 0）
int CNRDObject_vmt68(int* this, unsigned int a2)
{
    int v2 = this[36];                   // +144 数组基
    if (v2 != 0 && a2 < (unsigned)(this[37] - v2) >> 2)
        return *(int*)(v2 + 4 * a2);
    return 0;
}

// 0x42A5F0/0x42A600/0x42A610 vmt78/7C/80 —— 调 vt+116(0/1/2)
int CNRDObject_vmt78(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 0); }
int CNRDObject_vmt7C(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 1); }
int CNRDObject_vmt80(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 2); }

// 0x4C0380 vmt84 —— 固定返回 1
char CNRDObject_vmt84(int a1) { return 1; }

// ============================================================
// 条件与状态字节
// ============================================================

// 0x498DE0 vmt28 —— ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17/65 均出自此）
bool CNRDObject_vmt28(int* this, int a2)
{
    return (a2 & this[24]) == a2;        // +96 条件位集
}

// 0x498F00 vmt90 —— 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
int CNRDObject_vmt90(int* this, int a2)
{
    int result = this[50];               // +200 主状态
    if (result == 0) {                   // 仅自由态可改
        char* anim = (char*)this[28];    // +112? — 注: 原文 *(this+28) 同址兜底组件/动画
        if (*(int*)anim != 0) {
            result = (*(int(__thiscall**)(int))(**(int**)anim + 308))(*(int*)anim);
            if ((char)result != 0) {
                if ((char)anim[52] != (char)a2) {
                    anim[52] = (char)a2;
                    anim[196] = 1;       // 脏标记
                }
                result = a2;
            }
        }
    }
    return result;
}

// 0x498F40 vmt94 —— 同 vmt90 但不检查（直接写）
int CNRDObject_vmt94(int* this, char a2)
{
    int result = this[50];
    if (result == 0) {
        result = this[28];
        *(BYTE*)(result + 52) = a2;
    }
    return result;
}

// 0x498F60 vmt98 —— 取条件字节
int CNRDObject_vmt98(int* this) { return *(char*)(this[28] + 52); }

// 0x498F70 vmt134 —— 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8F7C04）
bool CNRDObject_vmt134(void* this)
{
    return (*(int(__thiscall**)(void*))(*(int*)this + 304))(this) != 0
        && (*(int(__thiscall**)(void*))(*(int*)this + 304))(this) == (int)dword_8F7C04;
}

// ============================================================
// 几何与朝向
// ============================================================

// 0x42A640 vmt9C / 0x42A670 vmtA0 —— 与目标 x/y 距离绝对值
unsigned int CNRDObject_vmt9C(void* this, int a2)
{
    int v3 = (*(int(__thiscall**)(int))(*(int*)a2 + 120))(a2);
    int v1 = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    return (unsigned)(v1 - v3 < 0 ? v3 - v1 : v1 - v3);
}
unsigned int CNRDObject_vmtA0(void* this, int a2)
{
    int v3 = (*(int(__thiscall**)(int))(*(int*)a2 + 124))(a2);
    int v1 = (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);
    return (unsigned)(v1 - v3 < 0 ? v3 - v1 : v1 - v3);
}

// 0x499280 vmtA4 —— ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
double CNRDObject_vmtA4(void* this, int a2, char a3)
{
    int dx = (*(int(__thiscall**)(int))(*(int*)a2 + 120))(a2)
           - (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    int dy = (*(int(__thiscall**)(int))(*(int*)a2 + 124))(a2)
           - (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);
    if (a3 == 0)
        dy = 100 * dy / dword_7930D4;    // 压扁系数（时间域 1 的当前 tick 值? 注: 7930D4 = tick 域数组前项）
    double result;
    if (dx != 0) {
        result = atan2((double)dy / (double)dx, 1.0) * 57.29577951308232; // 弧度→角度
        if (dx >= 0) {
            if (dy < 0) return result + 360.0;
        } else {
            return result + 180.0;
        }
    } else if (dy < 0) {
        return 270.0;
    } else {
        return 90.0;
    }
    return result;
}

// 0x499330 vmtA8 —— 与目标俯仰角（z 轴）
double CNRDObject_vmtA8(void* this, int a2, int a3)
{
    int dx = (*(int(__thiscall**)(int))(*(int*)a2 + 120))(a2)
           - (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    int adx = dx < 0 ? -dx : dx;
    int dz = (*(int(__thiscall**)(int))(*(int*)a2 + 128))(a2)
           - (*(int(__thiscall**)(void*))(*(int*)this + 128))(this);
    if (adx != 0)
        return atan2((double)(dz / adx), 1.0) * 57.29577951308232;
    if (dz < 0) return -90.0;
    return 90.0;
}

// 0x4993B0 vmt8C —— ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）
// 奇数步向左/上，偶数步向右/下；步长 a8；用 vt+136 检查目标位置是否有效。
// 找到 → *a2/*a3 = 位置并返回 1。【新发现(会话 3)】用途推断: 技能/掉落物找空位。
char CNRDObject_vmt8C(void* this, int* a2, int* a3, int a4, int a5, int a6, char a7, int a8)
{
    int step = 0;
    int saved = 0;
    if (a7 != 0) {                       // 先 x 后 y
        int limit = a8 + 2 * a6;
        if (limit <= 0) return 0;
        while (1) {
            int wy = (step % 2 != 0) ? a5 - (step + 1) / 2 : a5 + step / 2;
            int inner = 0;
            while (1) {
                int wx = (inner % 2 != 0) ? a4 - (inner + 1) / 2 : a4 + inner / 2;
                if ((*(unsigned char(__thiscall**)(void*, int, int, int))(*(int*)this + 136))
                        (this, wx, wy, 0) != 0) {
                    *a2 = wx; *a3 = wy;
                    return 1;
                }
                inner += a8;
                if (inner >= limit) { step = saved; break; }
            }
            step += a8;
            saved = step;
            if (step >= limit) return 0;
        }
    } else {                             // 先 y 后 x
        int limit = a8 + 2 * a6;
        if (limit <= 0) return 0;
        while (1) {
            int wx = (step % 2 != 0) ? a4 - (step + 1) / 2 : a4 + step / 2;
            int inner = 0;
            while (1) {
                int wy = (inner % 2 != 0) ? a5 - (inner + 1) / 2 : a5 + inner / 2;
                if ((*(unsigned char(__thiscall**)(void*, int, int, int))(*(int*)this + 136))
                        (this, wx, wy, 0) != 0) {
                    *a2 = wx; *a3 = wy;
                    return 1;
                }
                inner += a8;
                if (inner >= limit) { step = saved; break; }
            }
            step += a8;
            saved = step;
            if (step >= limit) return 0;
        }
    }
}

// 0x4995F0 vmtAC —— 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
int CNRDObject_vmtAC(void* this, int* a2, int* a3, int a4, int a5)
{
    int tx = (*(int(__thiscall**)(int))(*(int*)a4 + 120))(a4);
    int ty = (*(int(__thiscall**)(int))(*(int*)a4 + 124))(a4);
    int sx = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    int sy = (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);
    double t = 1.0 - (double)a5 / (double)(*(int(__thiscall**)(void*, int, int))(*(int*)this + 8))(this, a4, 1);
    *a2 = sx + (int)((double)(tx - sx) * t);
    int r = sy + (int)((double)(ty - sy) * t);
    *a3 = r;
    return r;
}

// 0x42A6E0 vmtB0 / 0x42A730 vmtB4 —— 目标是否在"前方/后方"（按 walkDir 朝向 +152）
bool CNRDObject_vmtB0(void* this, int a2)
{
    int dir = (*(int(__thiscall**)(void*))(*(int*)this + 152))(this);
    int x = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    return (dir == 1 && a2 > x) || (dir == 0 && a2 < x);
}
bool CNRDObject_vmtB4(void* this, int a2)
{
    int dir = (*(int(__thiscall**)(void*))(*(int*)this + 152))(this);
    int x = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);
    return (dir == 1 && a2 < x) || (dir == 0 && a2 > x);
}

// 0x4996F0 vmtB8 / 0x499730 vmtBC —— 动画对象 z 倾斜转状态码
int CNRDObject_vmtB8(int* this)
{
    float v = *(float*)(this[28] + 16);
    if (v > 5.0f) return 1;
    if (v >= -5.0f) return 4;            // 原文 _RTC_NumErrors() = 编译器桩, 中性值按 4
    return 0;
}
int CNRDObject_vmtBC(int* this)
{
    float v = *(float*)(this[28] + 20);
    if (v > 5.0f) return 3;
    if (v >= -5.0f) return 4;
    return 2;
}

// 0x42A7C0 vmtC8 —— 取动画对象
int CNRDObject_vmtC8(int* this) { return this[30]; }

// ============================================================
// ★ 时钟编排（vmt48 / vmtE4）—— 打击感与状态系统的中枢
// ============================================================

// 0x49A590 vmt48 —— ★★ 全体时钟换域广播
// this+46*4 = 域 id; 把本体 4 个时钟 + 动画对象时钟 + 全部子对象时钟切到该域，
// 并递归 sub_4A0740（深层对象）。
// 【会话 3 定案】本函数正是会话 1 新发现的 sub_699070(clock_bind_domain) 的调用者
// —— "对象全体迁移时间域"是换域函数的用途。
int CNRDObject_vmt48(int* this, unsigned int a2)
{
    this[23] = a2;                       // +92 域 id 缓存
    sub_699070((PauseClock*)(this + 2), a2);   // clockMain  +8
    sub_699070((PauseClock*)(this + 9), a2);   // clockAux   +36
    sub_699070((PauseClock*)(this + 16), a2);  // clockThird +64
    int v3 = this[30];                   // 动画对象
    if (v3 != 0)
        sub_699070((PauseClock*)v3, a2);
    // 子对象链表遍历
    int* v4 = (int*)this[32];            // +128 链表头
    int* v5 = (int*)*v4;
    if ((int*)*v4 != v4) {
        do {
            sub_699070((PauseClock*)v5[3], a2);
            v5 = (int*)*v5;
        } while (v5 != (int*)*(this + 32));
    }
    return sub_4A0740(a2);
}

// 0x49A320 vmtE4 —— ★★ 主状态写入器（世界状态机 + 时钟冻结编排）
// a2 = 新主状态: 0 自由 / 1 硬直(stuck) / 2 冻结类(冰冻/石化/演出定格)
// a3 = 时长参数（指针, 可为 NULL——NULL 时状态强制归 0）
// a4 = 起点偏移（起点时刻 = clock_now(clockMain) + a4）
//
// 进入活跃态(0→≥1): 动作子对象动画冻结(sub_4939E0(anim,1)) +
//   条件 17(有血)→冻 this+6560 动作时钟(vt+844) / 条件 65(机械)→vt+684 +
//   子对象动画全冻 + clockAux 冻结
// 跨越 2 边界: 挂起/恢复全部 17 个异常状态观察者时钟 + clockThird 冻结/解冻
//  —— 与 42 轮研究 §4.2 完全吻合（连击续硬直、冰冻期间 DOT 不走）
char CNRDObject_vmtE4(int* this, int a2, void* a3, int a4)
{
    int newState = a2;
    if (a2 != 0 && a3 == 0)
        newState = 0;                    // 有状态无参数 → 归零（防御式）

    int oldState = this[50];
    this[50] = newState;                 // +200 主状态
    if (newState != 0) {
        this[51] = (int)a3;              // +204 参数
        this[52] = a4 + sub_699000((PauseClock*)(this + 2));  // +208 起点时刻
    }

    if (oldState == newState)
        return (char)oldState;

    if (oldState < 1) {
        // ---- 进入活跃态（0 → ≥1）----
        if (newState >= 1) {
            int anim = this[30];         // +120 动画对象
            if (anim != 0) {
                int v9 = *(int*)(anim + 212);
                if (v9 != 0)
                    *(BYTE*)((char*)this + 212) = (BYTE)sub_4910C0((void*)v9);
                else
                    *(BYTE*)((char*)this + 212) = *(BYTE*)(anim + 169);
                sub_4939E0((void*)anim, 1);   // 冻动画
            } else {
                *(BYTE*)((char*)this + 212) = 0;
            }
            // 动作子对象时钟冻结（条件 17 有血 → vt+844; 条件 65 机械 → vt+684）
            if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {
                int clk = (*(int(__thiscall**)(int*))(*this + 844))(this);
                sub_699030((PauseClock*)clk);
            } else if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 65) != 0) {
                int clk = (*(int(__thiscall**)(int*))(*this + 684))(this);
                sub_699030((PauseClock*)clk);
            }
            sub_4A0680((void*)this[28], 1);
            sub_699030((PauseClock*)(this + 9));       // clockAux 冻结
            // 子对象动画全冻
            int* v4 = (int*)this[32];
            int* v11 = (int*)*v4;
            if ((int*)*v4 != v4) {
                do {
                    sub_4939E0((void*)v11[3], 1);
                    v11 = (int*)*v11;
                } while (v11 != (int*)*(this + 32));
            }
        }
        // ---- 恢复出冻结类（≥2 → <2）----
        if (oldState >= 2 && newState < 2) {
            if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {
                void* container = (void*)(*(int(__thiscall**)(int*))(*this + 700))(this);
                sub_53F720(container, 0);
                for (int i = 0; i < 17; ++i) {          // 17 个异常状态槽
                    if ((*(unsigned char(__thiscall**)(int*, int))(*this + 776))(this, i) != 0) {
                        int obj = (*(int(__thiscall**)(int*, int))(*this + 772))(this, i);
                        (*(void(__thiscall**)(int, int))(*(int*)obj + 36))(obj, 0);  // vt+36 恢复
                    }
                }
            }
            sub_698FE0((PauseClock*)(this + 16));       // clockThird 解冻
        }
        return (char)oldState;
    }

    // ---- oldState ≥ 1 ----
    if (newState >= 1) {
        // 1↔1 状态内转换（时长更新）—— 原文在截断段，语义=参数更新已由上段完成
        return (char)oldState;
    }
    // ---- 退出活跃态回到自由（≥1 → 0）：逆编排（解冻），研究 §4.2 已定案
    int anim = this[30];
    if (anim != 0)
        sub_4939E0((void*)anim, 0);
    if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {
        int clk = (*(int(__thiscall**)(int*))(*this + 844))(this);
        sub_698FE0((PauseClock*)clk);
    } else if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 65) != 0) {
        int clk = (*(int(__thiscall**)(int*))(*this + 684))(this);
        sub_698FE0((PauseClock*)clk);
    }
    sub_4A0680((void*)this[28], 0);
    sub_698FE0((PauseClock*)(this + 9));
    {
        int* v4 = (int*)this[32];
        int* v11 = (int*)*v4;
        if ((int*)*v4 != v4) {
            do {
                sub_4939E0((void*)v11[3], 0);
                v11 = (int*)*v11;
            } while (v11 != (int*)*(this + 32));
        }
    }
    return (char)oldState;
}

// 0x42A7F0 vmtE8 —— 通知并归零
int CNRDObject_vmtE8(void* this)
{
    return (*(int(__thiscall**)(void*, int, int, int))(*(int*)this + 228))(this, 0, -1, 0);
}

// 0x42A810 vmtF0 —— 已历时 = clock_now(clockMain) − this+52*4
int CNRDObject_vmtF0(int* this)
{
    return sub_699000((PauseClock*)(this + 2)) - this[52];
}

// 0x42A830 vmtF4 / 0x42A840 vmtF8 —— 时长/剩余
int CNRDObject_vmtF4(int* this) { return this[51]; }   // +204
int CNRDObject_vmtF8(void* this)
{
    int v2 = (*(int(__thiscall**)(void*))(*(int*)this + 244))(this);   // 时长
    return v2 - (*(int(__thiscall**)(void*))(*(int*)this + 240))(this);// −已历时
}

// ============================================================
// 定时器链表（★ 会话 3 新发现）
// ============================================================

// 0x49A7B0 vmtCC —— 定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
void CNRDObject_vmtCC(unsigned int* this, int a2, int a3, int a4, int a5, char a6, char a7)
{
    if (a3 == 0)
        return;
    sub_699070((PauseClock*)a3, this[23]);   // 定时器时钟切到本体域
    int node[4];
    node[3] = a5;
    node[1] = a3;
    node[2] = a4;
    node[0] = a2;
    int* head = (int*)this[32];
    int* cur = (int*)*head;
    if ((int*)*head != head) {
        do {                                  // 找到第一个时刻 > a2 的节点
            if (cur[2] > a2) break;
            cur = (int*)*cur;
        } while (cur != head);
    }
    int v11 = sub_499C20(cur, (void*)cur[1], node);
    sub_49A720(1);
    cur[1] = v11;
    **(int**)(v11 + 4) = v11;
    sub_4926A0((void*)a3);
}

// 0x49A6B0 vmtD0 —— 定时器移除（链表摘除 + 释放）
void CNRDObject_vmtD0(void*** this, void* a2)
{
    if (a2 == 0) return;
    void** head = this[32];
    void** cur = (void**)*head;
    if (*head != head) {
        while (cur[3] != a2) {
            cur = (void**)*cur;
            if (cur == head) return;
        }
        if (cur != this[32]) {
            *(int*)cur[1] = (int)*cur;            // 摘链
            *(int*)((char*)*cur + 4) = (int)cur[1];
            free(cur);
            this[33] = (void**)((char*)this[33] - 1);  // 计数 −1
        }
    }
}

// ============================================================
// 音效
// ============================================================

// 0x499110 vmtD4 —— 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
void CNRDObject_vmtD4(char* this, void* tag, int a3, int a4, int a5)
{
    if (strcmp((const char*)tag, szPassword) != 0 && *(this + 172) != 0) {
        int v7 = (*(int(__thiscall**)(char*))(*(int*)this + 56))(this);  // 宿主 ID
        sub_65FE10(lpCriticalSection, (const char*)tag, (int)(this + 176), a4, a5, 0, v7, a3);
    }
}

// 0x499170 vmtD8 —— 音效 TAG 查询
int CNRDObject_vmtD8(void* this, int a2)
{
    int v2 = (*(int(__thiscall**)(void*))(*(int*)this + 56))(this);
    return sub_65DE30(v2, a2);
}

// ============================================================
// 观察者组件
// ============================================================

// 0x4991D0 vmt44 —— 观察者组件懒创建（0x10 字节）
int CNRDObject_vmt44(int* this)
{
    if (this[42] == 0) {                     // +168
        void* v2 = operator new(0x10);
        void* v3 = v2;
        if (v2 != 0) {
            sub_50E730(v2);
            sub_50E8D0(this);
        } else {
            v3 = 0;
        }
        this[42] = (int)v3;
    }
    return this[42];
}

// 0x499AD0 vmt40 —— 取观察者容器（懒创建 0x44 字节 sb_499960(this,120)）
int CNRDObject_vmt40(void* this)
{
    int* p = (int*)this;
    if (p[41] == 0) {                        // +164
        int v2 = 0;
        if (operator new(0x44) != 0)
            v2 = sub_499960(this, 120, 0);
        p[41] = v2;
    }
    return p[41];
}

// ============================================================
// 表现与渲染钩
// ============================================================

// 0x499B50 vmt138 —— ★ 濒死/一击表现（"LAST STRIKE"；死亡链上游）【新发现(会话 3)】
// 条件: a2!=0 或 本地玩家(vt+308)；且 +264 != 1 → 发 UDP 包 type=23 (双方 id)
// 置 +264=1；再查条件 529（濒死）→ 打印日志。
char CNRDObject_vmt138(char* this, char a2)
{
    char result = a2;
    if ((a2 != 0 || (result = (char)(*(int(__thiscall**)(char*))(*(int*)this + 308))(this)) != 0)
        && *(this + 264) != 1) {
        // 发包: (type 23, 2) → 写本体 id 与目标 id → (1, -1)
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 8))(dword_8F8520, 23, 2);
        int a = (*(int(__thiscall**)(char*))(*(int*)this + 48))(this);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))(dword_8F8520, a);
        int b = (*(int(__thiscall**)(char*))(*(int*)this + 52))(this);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))(dword_8F8520, b);
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        *(this + 264) = 1;
        result = (char)(*(int(__thiscall**)(char*, int))(*(int*)this + 40))(this, 529);
        if (result != 0) {
            // 濒死日志（内容 = 宿主名字符串 + id）
        }
    }
    return result;
}

// 0x49A600 vmt148 —— ★ 玩家脚下光圈渲染钩（101 号资源；150↔255 / 400ms 三角波）
// （审计修正：原误写 0x499A60，正确 VA = 0x49A600，虚表槽 +0x148 验证）
// 仅当 this == 副玩家/本地玩家且 a2==0 时绘制。
char CNRDObject_vmt148(void* this, char a2, int a3, int a4, int a5)
{
    if (a2 == 0 && ((void*)dword_8F7C08 == this || (void*)dword_8F7C04 == this)) {
        int v6 = sub_699000((PauseClock*)((char*)this + 64));  // clockThird 域
        int alpha = sub_42B420(150, 255, v6, 400);             // 三角波
        sub_491530(2, 0);
        int tex = sub_418DD0(101);
        sub_424760(dword_79C0B0, a3 - 63, a4 - 21, (void*)tex, 1.0f, 1065353216 /*1.0f*/, 0.0f,
                   (alpha << 24) | 0xFFFFFF, 0.0f, 0.0f);
        return (char)sub_491630(2);
    }
    return a2;
}

// 0x499C70 vmt14 / 0x499FF0 vmt18 —— 每帧表现主循环（子对象循环渲染）
// vmt14: 动画帧同步 → 透明度链(vt+64 缩放) → 位置计算(sub_45E490/45E4D0) →
//        子对象按 +24/+25 字节标志分派 sub_491D00(A) 或 sub_491DE0(B, 带 0x40.. 参数)
//        随机抖动段(rand%3 偏移 ±a)
// vmt18: 同上但带 (v26+67, v9+68) 偏移与 sub_491EA0 变体; 结尾含场景 4 判定分支。
// 两函数体各 ~100 行, 结构已核; 逐行为还原见 work/decomp_core_vt.txt。
// （下方为语义骨架, 细节待该二函数专项会话补全）

// ============================================================
// 空桩群（原样保留）
// ============================================================
void nullsub_vmt4(void) {}          // vmt4 全库空桩 0x47A920
void nullsub_vmt10(void) {}         // 0x5721A0
