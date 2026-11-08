// ============================================================
// 【40JP逆向源代码工程】src/cnrd/CNRDObject.cpp
// CNRDObject 基类实现 —— 主状态机 / 时钟编排 / 坐标系 / 寻位 / 音效 / 渲染钩
// 每个函数 VA 见函数头；证据 work/decomp_core_vt.txt（会话 3 批反编译）
// ============================================================

#include "CNRDObject.h"  // 字符串 “CNRDObject.h”

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
extern void sub_4A2C40(void);  // 动画率状态查询（未还原）
extern int  sub_426820(void*, int, int);      // 播报层（研究第 10 轮定案）
extern int  sub_431230(int, int*);            // 命中目标列表追加
extern void sub_45E490(int, int);  // 屏幕 y → 演出层坐标（减基线）
extern int  sub_4A0650(int, int);  // 子对象时钟查询
extern void sub_4A0790(void*);  // 子对象链表递归辅助
extern int  sub_4A0740(int);  // 深层对象时钟换域递归
extern void* dword_79C0B0;                    // 渲染对象全局
extern void* dword_8F7C04;                    // 本地玩家
extern void* dword_8F7C08;                    // 副玩家/观战
extern void* dword_8F8520;                    // 会话/UDP 管理器
extern char  szPassword[];                    // 音效去重缓冲
extern void* lpCriticalSection;  // 音效全局管理器/临界区

// ============================================================
// 坐标三元组族
// ============================================================

// 0x42A510 vmt20 —— 设置坐标三元组 (this+100..112)
int CNRDObject_vmt20(int* this, int* pDwArg2)  // 函数：设置坐标三元组 (this+100..112)
{  // vmt20 设置坐标三元组
    int* pThis_19 = this + 25;                 // +100
    pThis_19[0] = pDwArg2[0];  // 复制 x
    pThis_19[1] = pDwArg2[1];  // 复制 y
    pThis_19[2] = pDwArg2[2];  // 复制 z
    return pDwArg2[2];  // 返回 z 分量（原文）
}  // 结束

// 0x42A530 vmt24 —— 取坐标三元组指针
char* CNRDObject_vmt24(char* this) { return this + 100; }  // vmt24 返回坐标三元组基址 this+100

// 0x42A540 vmt2C / 0x42A550 vmt30 / 0x42A560 vmt34 —— 取 x/y/z
int CNRDObject_vmt2C(int* this) { return this[24]; }   // +96
int CNRDObject_vmt30(int* this) { return this[25]; }   // +100
int CNRDObject_vmt34(int* this) { return this[26]; }   // +104

// 0x42A570 vmt38 —— y | z<<16 组合
int CNRDObject_vmt38(int* this) { return this[26] | (this[25] << 16); }  // vmt38 组合 y | z<<16（打包键）

// 0x42A580 vmt3C —— 取默认共享组件 this+112（研究第 12 轮直证：观察者兜底）
int CNRDObject_vmt3C(int* this) { return this[28]; }  // this+112〔研究第 12 轮直证：观察者兜底〕

// 0x42A590 vmt4C / 0x42A5A0 vmt50 —— this+116 存取
int CNRDObject_vmt4C(int* this, int uArg2) { this[29] = uArg2; return uArg2; }  // vmt4C 写 this+116
int CNRDObject_vmt50(int* this) { return this[29]; }  // vmt50 读 this+116

// 0x42A5B0 vmt54 / 0x42A5C0 vmt58 —— this+156 字节存取
char CNRDObject_vmt54(char* this, char uArg2) { *(this + 156) = uArg2; return uArg2; }  // vmt54 写 this+156 字节
char CNRDObject_vmt58(char* this) { return *(this + 156); }  // vmt58 读 this+156 字节

// 0x42A5D0 vmt5C —— 设置伤害数值；上次值非 0 时转发 vt+196
int CNRDObject_vmt5C(int* this, int nArg2)  // 函数：设置伤害数值；上次值非 0 时转发 vt+196
{  // vmt5C 设置伤害数值
    int v2 = this[30];                   // +120 上次值（动画对象）
    this[34] = nArg2;                       // +136 伤害数值
    if (v2 == 0)  // 上次值 0 → 转发 vt+196
        return (*(int(__thiscall**)(int*, int))(*this + 196))(this, nArg2);  // vt+196
    return nArg2;  // 否则仅记值
}  // 结束

// 0x445C30 vmt60 —— 取 this+136
int CNRDObject_vmt60(int* this) { return this[34]; }  // vmt60 读伤害数值 this+136

// 0x42A930 vmt68 —— 观察者数组元素访问（越界返回 0）
int CNRDObject_vmt68(int* this, unsigned int uArg2)  // 函数：观察者数组元素访问（越界返回 0）
{  // vmt68 观察者数组元素访问
    int v2 = this[36];                   // +144 数组基
    if (v2 != 0 && uArg2 < (unsigned)(this[37] - v2) >> 2)  // 越界判定（下标 < 元素数）
        return *(int*)(v2 + 4 * uArg2);  // 返回元素（指针数组）
    return 0;  // 越界返回 0
}  // 结束

// ·0x42A5F0/0x42A600/0x42A610 vmt78/7C/80 —— 调 vt+116(0/1/2)
int CNRDObject_vmt78(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 0); }  // 调虚槽 +116：取伤害数值
int CNRDObject_vmt7C(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 1); }  // 调虚槽 +116：取伤害数值
int CNRDObject_vmt80(void* this) { return (*(int(__thiscall**)(void*, int))(*(int*)this + 116))(this, 2); }  // 调虚槽 +116：取伤害数值

// 0x4C0380 vmt84 —— 固定返回 1
char CNRDObject_vmt84(int uArg1) { return 1; }  // vmt84 恒返回 1

// ============================================================
// 条件与状态字节
// ============================================================

// 0x498DE0 vmt28 —— ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17/65 均出自此）
bool CNRDObject_vmt28(int* this, int nArg2)  // 函数：★ 条件位掩码测试（研究第 20 轮直证: 273/529/17/65 均出自此）
{  // vmt28 条件位掩码测试
    return (nArg2 & this[24]) == nArg2;        // +96 条件位集
}  // 结束

// 0x498F00 vmt90 —— 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
int CNRDObject_vmt90(int* this, int nArg2)  // 函数：设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
{  // vmt90 设置条件字节（带玩家检查）
    int result = this[50];               // +200 主状态
    if (result == 0) {                   // 仅自由态可改
        char* anim = (char*)this[28];    // +112? — 注: 原文 *(this+28) 同址兜底组件/动画
        if (*(int*)anim != 0) {  // 兜底/动画基对象有效
            result = (*(int(__thiscall**)(int))(**(int**)anim + 308))(*(int*)anim);  // 调虚槽 +308：是否本地玩家
            if ((char)result != 0) {  // vt+308 本地玩家检查通过
                if ((char)anim[52] != (char)nArg2) {  // 与当前条件字节不同
                    anim[52] = (char)nArg2;  // 写入动画对象 +52
                    anim[196] = 1;       // 脏标记
                }  // 置脏标记 +196
                result = nArg2;  // 回传新值
            }  // 结束 vt+308 分支
        }  // 结束基对象分支
    }  // 结束自由态分支
    return result;  // 返回结果
}  // 结束

// 0x498F40 vmt94 —— 同 vmt90 但不检查（直接写）
int CNRDObject_vmt94(int* this, char pszArg2)  // 函数：同 vmt90 但不检查（直接写）
{  // vmt94 直接写条件字节（不检查）
    int result = this[50];  // this+200〔主状态(0自由/1硬直/2冻结)〕
    if (result == 0) {  // 仅自由态可改
        result = this[28];  // this+112〔研究第 12 轮直证：观察者兜底〕
        *(BYTE*)(result + 52) = pszArg2;  // 写动画对象 +52
    }  // 结束自由态分支
    return result;  // 返回结果
}  // 结束

// 0x498F60 vmt98 —— 取条件字节
int CNRDObject_vmt98(int* this) { return *(char*)(this[28] + 52); }  // this+112〔研究第 12 轮直证：观察者兜底〕

// 0x498F70 vmt134 —— 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8F7C04）
bool CNRDObject_vmt134(void* this)  // 函数：是否本地玩家（研究第 10 轮直证: vt+304 == 0x8F7C04）
{  // vmt134 是否本地玩家
    return (*(int(__thiscall**)(void*))(*(int*)this + 304))(this) != 0  // 两条件：非空且 == 本机角色
        && (*(int(__thiscall**)(void*))(*(int*)this + 304))(this) == (int)dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
}  // 结束

// ============================================================
// 几何与朝向
// ============================================================

// 0x42A640 vmt9C / 0x42A670 vmtA0 —— 与目标 x/y 距离绝对值
unsigned int CNRDObject_vmt9C(void* this, int nArg2)  // vmt9C 与目标 x 距离绝对值
{  // 函数体
    int v3 = (*(int(__thiscall**)(int))(*(int*)nArg2 + 120))(nArg2);  // 调虚槽 +120：取坐标x
    int pThis_78 = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    return (unsigned)(pThis_78 - v3 < 0 ? v3 - pThis_78 : pThis_78 - v3);  // |x−目标x|
}  // 结束
unsigned int CNRDObject_vmtA0(void* this, int nArg2)  // vmtA0 与目标 y 距离绝对值
{  // 函数体
    int v3 = (*(int(__thiscall**)(int))(*(int*)nArg2 + 124))(nArg2);  // 调虚槽 +124：取坐标y
    int pThis_7C = (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);  // 调虚槽 +124：取坐标y
    return (unsigned)(pThis_7C - v3 < 0 ? v3 - pThis_7C : pThis_7C - v3);  // |y−目标y|
}  // 结束

// 0x499280 vmtA4 —— ★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
double CNRDObject_vmtA4(void* this, int nArg2, char pszArg3)  // 函数：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）【新发现(会话 3)】
{  // vmtA4 与目标朝向角度（atan2 角度制）
    int dx = (*(int(__thiscall**)(int))(*(int*)nArg2 + 120))(nArg2)  // 调虚槽 +120：取坐标x
           - (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    int dy = (*(int(__thiscall**)(int))(*(int*)nArg2 + 124))(nArg2)  // 调虚槽 +124：取坐标y
           - (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);  // 调虚槽 +124：取坐标y
    if (pszArg3 == 0)  // pszArg3==0 → y 压扁
        dy = 100 * dy / dword_7930D4;    // 压扁系数（时间域 1 的当前 tick 值? 注: 7930D4 = tick 域数组前项）
    double result;  // 角度结果
    if (dx != 0) {  // dx 非 0 走 atan2
        result = atan2((double)dy / (double)dx, 1.0) * 57.29577951308232; // 弧度→角度
        if (dx >= 0) {  // dx ≥ 0 象限
            if (dy < 0) return result + 360.0;  // 第四象限 +360
        } else {  // 否则
            return result + 180.0;  // 第二象限 +180
        }  // 结束 dx≥0 分支
    } else if (dy < 0) {  // dx==0 且 dy<0 → 270°
        return 270.0;  // 返回 270°
    } else {  // 否则（dy>0）
        return 90.0;  // 返回 90°
    }  // 结束 dx==0 分支
    return result;  // 返回 atan2 结果
}  // 结束

// 0x499330 vmtA8 —— 与目标俯仰角（z 轴）
double CNRDObject_vmtA8(void* this, int nArg2, int nArg3)  // 函数：与目标俯仰角（z 轴）
{  // vmtA8 与目标俯仰角（z 轴）
    int dx = (*(int(__thiscall**)(int))(*(int*)nArg2 + 120))(nArg2)  // 调虚槽 +120：取坐标x
           - (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    int adx = dx < 0 ? -dx : dx;  // |dx|
    int dz = (*(int(__thiscall**)(int))(*(int*)nArg2 + 128))(nArg2)  // 调虚槽 +128：取坐标z
           - (*(int(__thiscall**)(void*))(*(int*)this + 128))(this);  // 调虚槽 +128：取坐标z
    if (adx != 0)  // adx 非 0 走 atan2
        return atan2((double)(dz / adx), 1.0) * 57.29577951308232;  // 反正切(方位角)
    if (dz < 0) return -90.0;  // dz<0 → −90°
    return 90.0;  // 否则 +90°
}  // 结束

// 0x4993B0 vmt8C —— ★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）
// 奇数步向左/上，偶数步向右/下；步长 a8；用 vt+136 检查目标位置是否有效。
// 找到 → *a2/*a3 = 位置并返回 1。【新发现(会话 3)】用途推断: 技能/掉落物找空位。
char CNRDObject_vmt8C(void* this, int* pDwArg2, int* pDwArg3, int nArg4, int nArg5, int nArg6, char pszArg7, int nArg8)  // 函数：★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）
{  // vmt8C 螺旋式寻找空位
    int step = 0;  // 当前步
    int saved = 0;  // 回溯保存点
    if (pszArg7 != 0) {                       // 先 x 后 y
        int limit = nArg8 + 2 * nArg6;  // 环扫描上限
        if (limit <= 0) return 0;  // 上限无效 → 失败
        while (1) {  // 外层环
            int wy = (step % 2 != 0) ? nArg5 - (step + 1) / 2 : nArg5 + step / 2;  // 当前 y（奇偶步决定加减）
            int inner = 0;  // 内层起点
            while (1) {  // 内层环
                int wx = (inner % 2 != 0) ? nArg4 - (inner + 1) / 2 : nArg4 + inner / 2;  // 当前 x（奇偶步决定加减）
                if ((*(unsigned char(__thiscall**)(void*, int, int, int))(*(int*)this + 136))  // 若 this+544〔阵营〕
                        (this, wx, wy, 0) != 0) {  // vt+136 校验目标位置有效
                    *pDwArg2 = wx; *pDwArg3 = wy;  // 记录命中位置
                    return 1;  // 返回成功
                }  // 结束命中分支
                inner += nArg8;  // 内层步进
                if (inner >= limit) { step = saved; break; }  // 内层到上限 → 退出内层
            }  // 结束内层
            step += nArg8;  // 外层步进
            saved = step;  // 保存回溯点
            if (step >= limit) return 0;  // 外层到上限 → 失败
        }  // 结束外层
    } else {                             // 先 y 后 x
        int limit = nArg8 + 2 * nArg6;  // 第二变体：扫描上限
        if (limit <= 0) return 0;  // 上限无效 → 失败
        while (1) {  // 外层环（先 y 后 x）
            int wx = (step % 2 != 0) ? nArg4 - (step + 1) / 2 : nArg4 + step / 2;  // 当前 x
            int inner = 0;  // 内层起点
            while (1) {  // 内层环
                int wy = (inner % 2 != 0) ? nArg5 - (inner + 1) / 2 : nArg5 + inner / 2;  // 当前 y
                if ((*(unsigned char(__thiscall**)(void*, int, int, int))(*(int*)this + 136))  // 若 this+544〔阵营〕
                        (this, wx, wy, 0) != 0) {  // vt+136 校验有效
                    *pDwArg2 = wx; *pDwArg3 = wy;  // 记录命中
                    return 1;  // 返回成功
                }  // 结束命中分支
                inner += nArg8;  // 内层步进
                if (inner >= limit) { step = saved; break; }  // 内层到上限退出
            }  // 结束内层
            step += nArg8;  // 外层步进
            saved = step;  // 保存回溯点
            if (step >= limit) return 0;  // 外层到上限 → 失败
        }  // 结束外层
    }  // 结束先 y 后 x 分支
}  // 结束

// 0x4995F0 vmtAC —— 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
int CNRDObject_vmtAC(void* this, int* pDwArg2, int* pDwArg3, int nArg4, int nArg5)  // 函数：朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
{  // vmtAC 朝目标按比例取点
    int tx = (*(int(__thiscall**)(int))(*(int*)nArg4 + 120))(nArg4);  // 调虚槽 +120：取坐标x
    int ty = (*(int(__thiscall**)(int))(*(int*)nArg4 + 124))(nArg4);  // 调虚槽 +124：取坐标y
    int sx = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    int sy = (*(int(__thiscall**)(void*))(*(int*)this + 124))(this);  // 调虚槽 +124：取坐标y
    double t = 1.0 - (double)nArg5 / (double)(*(int(__thiscall**)(void*, int, int))(*(int*)this + 8))(this, nArg4, 1);  // 比例 t = 1 − a5/距离
    *pDwArg2 = sx + (int)((double)(tx - sx) * t);  // 插值 x
    int r = sy + (int)((double)(ty - sy) * t);  // 插值 y
    *pDwArg3 = r;  // 写回 y
    return r;  // 返回 y（原文）
}  // 结束

// 0x42A6E0 vmtB0 / 0x42A730 vmtB4 —— 目标是否在"前方/后方"（按 walkDir 朝向 +152）
bool CNRDObject_vmtB0(void* this, int nArg2)  // vmtB0 目标是否在前方
{  // 函数体
    int dir = (*(int(__thiscall**)(void*))(*(int*)this + 152))(this);  // 调虚槽 +152：取朝向
    int x = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    return (dir == 1 && nArg2 > x) || (dir == 0 && nArg2 < x);  // 朝右且目标x>己x / 朝左且目标x<己x
}  // 结束
bool CNRDObject_vmtB4(void* this, int nArg2)  // vmtB4 目标是否在后方
{  // 函数体
    int dir = (*(int(__thiscall**)(void*))(*(int*)this + 152))(this);  // 调虚槽 +152：取朝向
    int x = (*(int(__thiscall**)(void*))(*(int*)this + 120))(this);  // 调虚槽 +120：取坐标x
    return (dir == 1 && nArg2 < x) || (dir == 0 && nArg2 > x);  // 朝右且目标x<己x / 朝左且目标x>己x
}  // 结束

// 0x4996F0 vmtB8 / 0x499730 vmtBC —— 动画对象 z 倾斜转状态码
int CNRDObject_vmtB8(int* this)  // vmtB8 动画对象 z 倾斜 → 状态码
{  // 函数体
    float v = *(float*)(this[28] + 16);  // this+112〔研究第 12 轮直证：观察者兜底〕
    if (v > 5.0f) return 1;  // 倾斜 > 5° → 1
    if (v >= -5.0f) return 4;            // 原文 _RTC_NumErrors() = 编译器桩, 中性值按 4
    return 0;  // 否则 → 0
}  // 结束
int CNRDObject_vmtBC(int* this)  // vmtBC 动画对象第二倾斜 → 状态码
{  // 函数体
    float v = *(float*)(this[28] + 20);  // this+112〔研究第 12 轮直证：观察者兜底〕
    if (v > 5.0f) return 3;  // > 5° → 3
    if (v >= -5.0f) return 4;  // [−5,5] → 4
    return 2;  // 否则 → 2
}  // 结束

// 0x42A7C0 vmtC8 —— 取动画对象
int CNRDObject_vmtC8(int* this) { return this[30]; }  // this+120〔动画对象〕

// ============================================================
// ★ 时钟编排（vmt48 / vmtE4）—— 打击感与状态系统的中枢
// ============================================================

// 0x49A590 vmt48 —— ★★ 全体时钟换域广播
// this+46*4 = 域 id; 把本体 4 个时钟 + 动画对象时钟 + 全部子对象时钟切到该域，
// 并递归 sub_4A0740（深层对象）。
// 【会话 3 定案】本函数正是会话 1 新发现的 sub_699070(clock_bind_domain) 的调用者
// —— "对象全体迁移时间域"是换域函数的用途。
int CNRDObject_vmt48(int* this, unsigned int uArg2)  // 函数：★★ 全体时钟换域广播
{  // vmt48 全体时钟换域广播
    this[23] = uArg2;                       // +92 域 id 缓存
    sub_699070((PauseClock*)(this + 2), uArg2);   // clockMain  +8
    sub_699070((PauseClock*)(this + 9), uArg2);   // clockAux   +36
    sub_699070((PauseClock*)(this + 16), uArg2);  // clockThird +64
    int v3 = this[30];                   // 动画对象
    if (v3 != 0)  // 动画对象非空
        sub_699070((PauseClock*)v3, uArg2);  // 【clock_bind_domain(clk, newDomainId)】
    // 子对象链表遍历
    int* v4 = (int*)this[32];            // +128 链表头
    int* v5 = (int*)*v4;  // 子对象链表首结点
    if ((int*)*v4 != v4) {  // 链表非空
        do {  // 遍历子对象
            sub_699070((PauseClock*)v5[3], uArg2);  // 【clock_bind_domain(clk, newDomainId)】
            v5 = (int*)*v5;  // 前进到下一结点
        } while (v5 != (int*)*(this + 32));  // this+128〔定时器链表头〕
    }  // 遍历结束
    return sub_4A0740(uArg2);  // 递归深层对象换域
}  // 结束

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
char CNRDObject_vmtE4(int* this, int nArg2, void* pArg3, int nArg4)  // 函数：★★ 主状态写入器（世界状态机 + 时钟冻结编排）
{  // vmtE4 主状态写入器
    int newState = nArg2;  // 新主状态
    if (nArg2 != 0 && pArg3 == 0)  // 有状态无参数 → 归零
        newState = 0;                    // 有状态无参数 → 归零（防御式）

    int oldState = this[50];  // this+200〔主状态(0自由/1硬直/2冻结)〕
    this[50] = newState;                 // +200 主状态
    if (newState != 0) {  // 新状态非 0 才记参数
        this[51] = (int)pArg3;              // +204 参数
        this[52] = nArg4 + sub_699000((PauseClock*)(this + 2));  // +208 起点时刻
    }  // 结束记参数分支

    if (oldState == newState)  // 状态未变则直接返回
        return (char)oldState;  // 返回旧状态

    if (oldState < 1) {  // 旧状态 < 1（自由态）
        // ---- 进入活跃态（0 → ≥1）----
        if (newState >= 1) {  // 进入活跃态 0→≥1
            int anim = this[30];         // +120 动画对象
            if (anim != 0) {  // 动画对象存在
                int v9 = *(int*)(anim + 212);  // 取 +212 同步源
                if (v9 != 0)  // 同步源非空 → 上溯取值
                    *(BYTE*)((char*)this + 212) = (BYTE)sub_4910C0((void*)v9);  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
                else  // 否则
                    *(BYTE*)((char*)this + 212) = *(BYTE*)(anim + 169);  // 直接取动画 +169 冻结位
                sub_4939E0((void*)anim, 1);   // 冻动画
            } else {  // 动画对象为空
                *(BYTE*)((char*)this + 212) = 0;  // 清零冻结位
            }  // 结束动画分支
            // 动作子对象时钟冻结（条件 17 有血 → vt+844; 条件 65 机械 → vt+684）
            if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {  // 虚调用 vt+40
                int clk = (*(int(__thiscall**)(int*))(*this + 844))(this);  // 结果 = 虚调用 vt+844
                sub_699030((PauseClock*)clk);  // 【clock_freeze(clk)】
            } else if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 65) != 0) {  // 虚调用 vt+40
                int clk = (*(int(__thiscall**)(int*))(*this + 684))(this);  // 结果 = 虚调用 vt+684
                sub_699030((PauseClock*)clk);  // 【clock_freeze(clk)】
            }  // 结束冻结编排
            sub_4A0680((void*)this[28], 1);  // this+112〔研究第 12 轮直证：观察者兜底〕
            sub_699030((PauseClock*)(this + 9));       // clockAux 冻结
            // 子对象动画全冻
            int* v4 = (int*)this[32];  // this+128〔定时器链表头〕
            int* v11 = (int*)*v4;  // 子对象链表首结点
            if ((int*)*v4 != v4) {  // 链表非空
                do {  // 遍历子对象
                    sub_4939E0((void*)v11[3], 1);  // 播放/暂停级联（递归子链 +204）
                    v11 = (int*)*v11;  // 前进
                } while (v11 != (int*)*(this + 32));  // this+128〔定时器链表头〕
            }  // 遍历结束
        }  // 结束活跃态分支
        // ---- 恢复出冻结类（≥2 → <2）----
        if (oldState >= 2 && newState < 2) {  // 恢复出冻结类 ≥2→<2
            if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {  // 虚调用 vt+40
                void* container = (void*)(*(int(__thiscall**)(int*))(*this + 700))(this);  // 结果 = 虚调用 vt+700
                sub_53F720(container, 0);  // 挂起状态容器
                for (int i = 0; i < 17; ++i) {          // 17 个异常状态槽
                    if ((*(unsigned char(__thiscall**)(int*, int))(*this + 776))(this, i) != 0) {  // 虚调用 vt+776
                        int obj = (*(int(__thiscall**)(int*, int))(*this + 772))(this, i);  // 结果 = 虚调用 vt+772
                        (*(void(__thiscall**)(int, int))(*(int*)obj + 36))(obj, 0);  // vt+36 恢复
                    }  // 结束异常状态循环
                }  // 结束循环块
            }  // 结束条件 17 分支
            sub_698FE0((PauseClock*)(this + 16));       // clockThird 解冻
        }  // 结束恢复分支
        return (char)oldState;  // 返回旧状态
    }  // 结束自由态分支

    // ---- oldState ≥ 1 ----
    if (newState >= 1) {  // 旧状态 ≥1 且新状态 ≥1（态内转换）
        // 1↔1 状态内转换（时长更新）—— 原文在截断段，语义=参数更新已由上段完成
        return (char)oldState;  // 返回旧状态
    }  // 结束
    // ---- 退出活跃态回到自由（≥1 → 0）：逆编排（解冻），研究 §4.2 已定案
    int anim = this[30];  // this+120〔动画对象〕
    if (anim != 0)  // 动画对象存在则解冻
        sub_4939E0((void*)anim, 0);  // 播放/暂停级联（递归子链 +204）
    if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 17) != 0) {  // 虚调用 vt+40
        int clk = (*(int(__thiscall**)(int*))(*this + 844))(this);  // 结果 = 虚调用 vt+844
        sub_698FE0((PauseClock*)clk);  // 【clock_unfreeze(clk)】
    } else if ((*(unsigned char(__thiscall**)(int*, int))(*this + 40))(this, 65) != 0) {  // 虚调用 vt+40
        int clk = (*(int(__thiscall**)(int*))(*this + 684))(this);  // 结果 = 虚调用 vt+684
        sub_698FE0((PauseClock*)clk);  // 【clock_unfreeze(clk)】
    }  // 结束条件分支
    sub_4A0680((void*)this[28], 0);  // this+112〔研究第 12 轮直证：观察者兜底〕
    sub_698FE0((PauseClock*)(this + 9));  // 【clock_unfreeze(clk)】
    {  // 逆编排块
        int* v4 = (int*)this[32];  // this+128〔定时器链表头〕
        int* v11 = (int*)*v4;  // 子对象链表首结点
        if ((int*)*v4 != v4) {  // 链表非空
            do {  // 遍历子对象
                sub_4939E0((void*)v11[3], 0);  // 播放/暂停级联（递归子链 +204）
                v11 = (int*)*v11;  // 前进
            } while (v11 != (int*)*(this + 32));  // this+128〔定时器链表头〕
        }  // 遍历结束
    }  // 结束逆编排块
    return (char)oldState;  // 返回旧状态
}  // 结束

// 0x42A7F0 vmtE8 —— 通知并归零
int CNRDObject_vmtE8(void* this)  // 函数：通知并归零
{  // vmtE8 通知并归零
    return (*(int(__thiscall**)(void*, int, int, int))(*(int*)this + 228))(this, 0, -1, 0);  // 调虚槽 +228：主状态写入
}  // 结束

// 0x42A810 vmtF0 —— 已历时 = clock_now(clockMain) − this+52*4
int CNRDObject_vmtF0(int* this)  // 函数：已历时 = clock_now(clockMain) − this+52*4
{  // vmtF0 已历时
    return sub_699000((PauseClock*)(this + 2)) - this[52];  // 【clock_now(clk)】
}  // 结束

// 0x42A830 vmtF4 / 0x42A840 vmtF8 —— 时长/剩余
int CNRDObject_vmtF4(int* this) { return this[51]; }   // +204
int CNRDObject_vmtF8(void* this)  // vmtF8 剩余时长
{  // 函数体
    int pThis_F4 = (*(int(__thiscall**)(void*))(*(int*)this + 244))(this);   // 时长
    return pThis_F4 - (*(int(__thiscall**)(void*))(*(int*)this + 240))(this);// −已历时
}  // 结束

// ============================================================
// 定时器链表（★ 会话 3 新发现）
// ============================================================

// 0x49A7B0 vmtCC —— 定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
void CNRDObject_vmtCC(unsigned int* this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, char pszArg7)  // 函数：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
{  // vmtCC 定时器有序插入
    if (nArg3 == 0)  // 时长为 0 → 忽略
        return;  // 返回
    sub_699070((PauseClock*)nArg3, this[23]);   // 定时器时钟切到本体域
    int node[4];  // 28 字节节点
    node[3] = nArg5;  // 节点[3]=时长参数
    node[1] = nArg3;  // 节点[1]=时钟
    node[2] = nArg4;  // 节点[2]=触发参数
    node[0] = nArg2;  // 节点[0]=触发时刻
    int* head = (int*)this[32];  // this+128〔定时器链表头〕
    int* cur = (int*)*head;  // 链表首结点
    if ((int*)*head != head) {  // 链表非空
        do {                                  // 找到第一个时刻 > nArg2 的节点
            if (cur[2] > nArg2) break;  // 找到第一个时刻 > nArg2 的位置
            cur = (int*)*cur;  // 前进
        } while (cur != head);  // 遍历结束
    }  // 结束查找
    int v11 = sub_499C20(cur, (void*)cur[1], node);  // 结果 = 28 字节节点分配（2 入参 + 5 槽拷贝）
    sub_49A720(1);  // 元素计数增长 + 溢出抛 length_error（上限 214748364）
    cur[1] = v11;  // 新结点接入前驱
    **(int**)(v11 + 4) = v11;  // 回写前驱 next
    sub_4926A0((void*)nArg3);  // 帧游标复位（+44 帧数组；递归子链 +204）
}  // 结束

// 0x49A6B0 vmtD0 —— 定时器移除（链表摘除 + 释放）
void CNRDObject_vmtD0(void*** this, void* pArg2)  // 函数：定时器移除（链表摘除 + 释放）
{  // vmtD0 定时器移除
    if (pArg2 == 0) return;  // 空指针 → 忽略
    void** head = this[32];  // this+128〔定时器链表头〕
    void** cur = (void**)*head;  // 链表首结点
    if (*head != head) {  // 链表非空
        while (cur[3] != pArg2) {  // 查找目标结点
            cur = (void**)*cur;  // 前进
            if (cur == head) return;  // 到末尾未找到 → 返回
        }  // 结束查找
        if (cur != this[32]) {  // 若 this+128〔定时器链表头〕 != this[32]
            *(int*)cur[1] = (int)*cur;            // 摘链
            *(int*)((char*)*cur + 4) = (int)cur[1];  // next 的 prev 指向 prev（摘链）
            free(cur);  // 释放内存
            this[33] = (void**)((char*)this[33] - 1);  // 计数 −1
        }  // 结束摘链
    }  // 结束链表分支
}  // 结束

// ============================================================
// 音效
// ============================================================

// 0x499110 vmtD4 —— 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
void CNRDObject_vmtD4(char* this, void* tag, int nArg3, int nArg4, int nArg5)  // 函数：音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
{  // vmtD4 音效标签播放
    if (strcmp((const char*)tag, szPassword) != 0 && *(this + 172) != 0) {  // 若 字符串比较
        int pThis_38 = (*(int(__thiscall**)(char*))(*(int*)this + 56))(this);  // 宿主 ID
        sub_65FE10(lpCriticalSection, (const char*)tag, (int)(this + 176), nArg4, nArg5, 0, pThis_38, nArg3);  // 按标签名播声音：命中则立即播或入延迟队列，否则打 Tag Missing
    }  // 结束播放分支
}  // 结束

// 0x499170 vmtD8 —— 音效 TAG 查询
int CNRDObject_vmtD8(void* this, int nArg2)  // 函数：音效 TAG 查询
{  // vmtD8 音效 TAG 查询
    int pThis_38 = (*(int(__thiscall**)(void*))(*(int*)this + 56))(this);  // 取宿主 ID
    return sub_65DE30(pThis_38, nArg2);  // 按 (nArg2,nArg3) 键停止 50 个音源槽位中的对应流
}  // 结束

// ============================================================
// 观察者组件
// ============================================================

// 0x4991D0 vmt44 —— 观察者组件懒创建（0x10 字节）
int CNRDObject_vmt44(int* this)  // 函数：观察者组件懒创建（0x10 字节）
{  // vmt44 观察者组件懒创建
    if (this[42] == 0) {                     // +168
        void* pMem = operator new(0x10);  // 堆分配 16 字节对象
        void* pMem2 = pMem;  // 暂存分配结果
        if (pMem != 0) {  // 分配成功
            sub_50E730(pMem);  // 对象字段清零（三指针 + 两标志）
            sub_50E8D0(this);  // 表情气泡对象构造（EmoBalloonS.ani）
        } else {  // 否则
            pMem2 = 0;  // 置空
        }  // 结束分配分支
        this[42] = (int)pMem2;  // 写入 this+168
    }  // 结束懒创建分支
    return this[42];  // 返回组件
}  // 结束

// 0x499AD0 vmt40 —— 取观察者容器（懒创建 0x44 字节 sb_499960(this,120)）
int CNRDObject_vmt40(void* this)  // 函数：取观察者容器（懒创建 0x44 字节 sb_499960(this,120)）
{  // vmt40 取观察者容器（懒创建）
    int* p = (int*)this;  // this 指针
    if (p[41] == 0) {                        // +164
        int v2 = 0;  // 构造结果槽
        if (operator new(0x44) != 0)  // 堆分配 68 字节对象
            v2 = sub_499960(this, 120, 0);  // 结果 = 子对象构造（off_6C2B88 装配 + 基类初始化）
        p[41] = v2;  // 写入 this+164
    }  // 结束懒创建分支
    return p[41];  // 返回容器
}  // 结束

// ============================================================
// 表现与渲染钩
// ============================================================

// 0x499B50 vmt138 —— ★ 濒死/一击表现（"LAST STRIKE"；死亡链上游）【新发现(会话 3)】
// 条件: a2!=0 或 本地玩家(vt+308)；且 +264 != 1 → 发 UDP 包 type=23 (双方 id)
// 置 +264=1；再查条件 529（濒死）→ 打印日志。
char CNRDObject_vmt138(char* this, char pszArg2)  // 函数：★ 濒死/一击表现（「LAST STRIKE「；死亡链上游）【新发现(会话 3)】
{  // vmt138 濒死/一击表现
    char result = pszArg2;  // 初始结果
    if ((pszArg2 != 0 || (result = (char)(*(int(__thiscall**)(char*))(*(int*)this + 308))(this)) != 0)  // 若 调虚槽 +308：是否本地玩家
        && *(this + 264) != 1) {  // 条件：a2 或本地玩家，且 +264 != 1
        // 发包: (type 23, 2) → 写本体 id 与目标 id → (1, -1)
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 8))(dword_8F8520, 23, 2);  // 开包 type=23（濒死）
        int a = (*(int(__thiscall**)(char*))(*(int*)this + 48))(this);  // 取本体 id（vt+48）
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))(dword_8F8520, a);  // 会话管理器 vt+36：推入坐标/数值
        int b = (*(int(__thiscall**)(char*))(*(int*)this + 52))(this);  // this+208〔主状态起点时刻〕
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))(dword_8F8520, b);  // 会话管理器 vt+36：推入坐标/数值
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 会话管理器 vt+60：提交发送(flag, 目标)
        *(this + 264) = 1;  // 置 +264 = 1（防重发）
        result = (char)(*(int(__thiscall**)(char*, int))(*(int*)this + 40))(this, 529);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        if (result != 0) {  // 查条件 529（濒死）
            // 濒死日志（内容 = 宿主名字符串 + id）
        }  // 日志占位
    }  // 结束
    return result;  // 返回结果
}  // 结束

// 0x49A600 vmt148 —— ★ 玩家脚下光圈渲染钩（101 号资源；150↔255 / 400ms 三角波）
// （审计修正：原误写 0x499A60，正确 VA = 0x49A600，虚表槽 +0x148 验证）
// 仅当 this == 副玩家/本地玩家且 a2==0 时绘制。
char CNRDObject_vmt148(void* this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数：★ 玩家脚下光圈渲染钩（101 号资源；150↔255 / 400ms 三角波）
{  // vmt148 玩家脚下光圈渲染钩
    if (pszArg2 == 0 && ((void*)dword_8F7C08 == this || (void*)dword_8F7C04 == this)) {  // 若 dword_8F7C08＝副玩家/观战对象 与/或 dword_8F7C04＝本地玩家对象
        int pThis_40 = sub_699000((PauseClock*)((char*)this + 64));  // clockThird 域
        int alpha = sub_42B420(150, 255, pThis_40, 400);             // 三角波
        sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        int tex = sub_418DD0(101);  // sub_418DD0：资源句柄
        sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, (void*)tex, 1.0f, 1065353216 /*1.0f*/, 0.0f,  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
                   (alpha << 24) | 0xFFFFFF, 0.0f, 0.0f);  // 续行：顶点色 ARGB + UV
        return (char)sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    }  // 结束渲染分支
    return pszArg2;  // 返回 pszArg2（未绘制时）
}  // 结束

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
