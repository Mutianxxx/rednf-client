// ============================================================
// 【40JP逆向源代码工程】src/cnrd/IRDActiveObject.cpp
// 活动对象段实现 —— 会话 3 新分析函数（逐行还原）
// 42 轮研究已全文定案的命中链（vmt200 命中主处理器 / vmt1F4 攻方载荷 /
// vmt2D8 HP setter / vmt308 状态查询 / vmt2D0 霸体 setter / vmt1E0 多盒）
// 见 研究文档 20 与 docs/14 交叉引用表，本文件不重复。
// ============================================================

#include "IRDActiveObject.h"

extern int  sub_699000(PauseClock*);
extern void sub_493D00(void*, float);              // 动画速率写入（研究 P38 全链）
extern int  sub_4A2C40(void*);
extern int  sub_41A5E0(int);                       // 防篡改数值读取（研究第 17 轮）
extern float sub_43B5A0(void*);                    // 防篡改浮点壳（研究第 27 轮）
extern void sub_426820(void*, int, int);           // 播报层（研究第 10 轮）
extern void sub_4A0600(int);
extern void sub_494F60(int, int);
extern void sub_495540(int);
extern int  sub_49A320_vt228;                      // （已还原为 CNRDObject_vmtE4）
extern void sub_4A45xx_reserved();
extern void* dword_8F8520;

// ============================================================
// 观察者通知族（研究 §1.1 的"六回调"之受方侧实现）
// ============================================================

// 0x4D4A20 vmt1F8 —— 18 观察者通知（flag=0 轻量版；受击包五号回调）
// 每个非空观察者 → 观察者->vt+136(a2, a3, a4, 0, this+97*4)
int IRDActiveObject_vmt1F8(int* this_, int a2, int a3, int a4)
{
    int* obs = this_ + 1617;                           // +6468 观察者数组
    for (int i = 18; i != 0; --i) {
        if (*obs != 0)
            (*(void(__thiscall**)(int, int, int, int, int, int*))(*(int*)*obs + 136))(
                *obs, a2, a3, a4, 0, this_ + 97);      // +388 攻击上下文指针
        ++obs;
    }
    return 0;
}

// 0x4D4A80 vmt204 —— 18 观察者 vt+140（受方命中通知）+ 基类
int IRDActiveObject_vmt204(int* this_, int a2, int a3, int a4)
{
    int* obs = this_ + 1617;
    for (int i = 18; i != 0; --i) {
        if (*obs != 0)
            (*(void(__thiscall**)(int, int, int, int, int))(*(int*)*obs + 140))(*obs, a2, a3, a4, 0);
        ++obs;
    }
    return IRDCollisionObject_vmt204(this_, a2, a3, a4);
}

// 0x4D49E0 vmt220 —— 播报层 HK_ATTACKED（受击包链路终点，42 轮研究 §1.1 定案）
// cond: vt+44 == 273（受击态条件位）→ 播报层 sub_426820(会话.vt+120().+104 的 +132, 3, a3)
int IRDActiveObject_vmt220(void* this_, int a2, int a3)
{
    int mgr = *(int*)((*(int(__thiscall**)(int))(*(int*)0x8F8520 + 120))(0x8F8520) + 104);
    int result = (*(int(__thiscall**)(void*))(*(int*)this_ + 44))(this_);   // vt+44 条件查询
    if (result == 273)
        return sub_426820(*(void**)(mgr + 132), 3, a3);
    return result;
}

// ============================================================
// 子对象与槽位访问
// ============================================================

// 0x4A0C80 vmt2A0 —— 取第 a2 个子对象基址（步长 1364 字节）
// 结构线索: IRDActiveObject 内嵌 5 个子对象（每 1364B = 0x554）
int IRDActiveObject_vmt2A0(void* this_, int a2)
{
    return (int)this_ + 1364 * a2 + 676;
}

// 0x4A0F00 vmt2AC / 0x4A0F10 vmt2B0 / 0x4A0F20 vmt2BC —— 属性块/附加块/槽读
char* IRDActiveObject_vmt2AC(char* this_) { return this_ + 6132; }   // 属性块（HP 读处）
char* IRDActiveObject_vmt2B0(char* this_) { return this_ + 6160; }
int   IRDActiveObject_vmt2BC(int* this_)  { return this_[1574]; }    // +6296

// 0x4A0F50 vmt304 —— ★ 17 异常状态槽访问（研究定案的 +6228 数组）
int IRDActiveObject_vmt304(int* this_, int a2) { return this_[a2 + 1557]; }  // +6228+4a2

// 0x4A0F70 vmt318 —— ★ 18 观察者槽访问（研究定案的 +6468 数组）
int IRDActiveObject_vmt318(int* this_, int a2) { return this_[a2 + 1617]; }  // +6468+4a2

// 0x4A0F30 vmt184 / 0x4A0F40 vmt2D4 / 0x4A0FB0 vmt334
int IRDActiveObject_vmt184(void* this_)
{
    return *(int*)(*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
}
char IRDActiveObject_vmt2D4(char* this_) { return *(this_ + 6552); }        // 霸体字节
char IRDActiveObject_vmt334(char* this_, char a2) { *(this_ + 6740) = a2; return a2; }

// 0x4A0F90 vmt330 —— 转发 vt+808
int IRDActiveObject_vmt330(void* this_, int a2, int a3)
{
    return (*(int(__thiscall**)(void*, int, int, int, int))(*(int*)this_ + 808))
        (this_, a2, 0xFFFF, 0, a3);
}

// ============================================================
// 复活链 + 冻结标志（研究 P35 配套）
// ============================================================

// 0x4A1110 vmt3E4 / 0x4A1120 vmt3E8 / 0x4A1130 vmt3F0 —— 复活计时器三件套
void  IRDActiveObject_vmt3E4(int* this_) { this_[1774] = -1; }             // 清计时
bool  IRDActiveObject_vmt3E8(int* this_) { return this_[1774] != -1; }     // 计时中否
int   IRDActiveObject_vmt3F0(int* this_)                                   // 已计时
{
    if (this_[1774] == -1)
        return 0;
    return sub_699000((PauseClock*)(this_ + 9)) - this_[1774];             // clockAux 域
}

// 0x4A1030 vmt350 / 0x4A1050 vmt354 / 0x4A1060 vmt358 —— 冻结标志(+6744)链
int IRDActiveObject_vmt350(int* this_, char a2)
{
    int result = (a2 != 0) - 1;                        // 0→-1 / 非0→0
    this_[1686] = result;
    return result;
}
bool IRDActiveObject_vmt354(int* this_) { return this_[1686] != -1; }
int  IRDActiveObject_vmt358(int* this_) { return this_[1686]; }

// 0x4A10D0 vmt3DC —— 非霸体自由条件: vt+724==0 && 状态3==0 && 状态8==0（睡眠/眩晕不在）
bool IRDActiveObject_vmt3DC(void* this_)
{
    return (*(unsigned char(__thiscall**)(void*))(*(int*)this_ + 724))(this_) == 0
        && (*(unsigned char(__thiscall**)(void*, int))(*(int*)this_ + 776))(this_, 3) == 0
        && (*(unsigned char(__thiscall**)(void*, int))(*(int*)this_ + 776))(this_, 8) == 0;
}

// 0x4D49A0 vmt3A4 —— 场景 15/16 判定 → +7088 = 0 / 7
int IRDActiveObject_vmt3A4(int* this_)
{
    int result = **(int**)((*(int(__thiscall**)(int))(*(int*)0x8F8520 + 120))(0x8F8520) + 108);
    if (result < 15 || result > 16)
        this_[1772] = 0;
    else
        this_[1772] = 7;
    return result;
}

// ============================================================
// 受击盒使能广播（研究 P35 定案: 无敌开关 = this+641）
// ============================================================

// 0x4A2D70 vmt25C —— 受击盒使能 setter + 向全部附属物（+7076 数组）广播 vt+604
unsigned int IRDActiveObject_vmt25C(int this_, int a2)
{
    *(BYTE*)(this_ + 641) = (BYTE)a2;
    int v3 = *(int*)(this_ + 7076);
    unsigned int result = 0;
    if (v3 != 0) {
        result = (*(unsigned int*)(this_ + 7080) - v3) >> 2;
        if (result != 0) {
            for (unsigned int i = 0; ; ++i) {
                int v6 = *(int*)(this_ + 7076);
                if (v6 == 0) break;
                result = (*(unsigned int*)(this_ + 7080) - v6) >> 2;
                if (i >= result) break;
                result = (*(int(__thiscall**)(int, int))(***(int**)(v6 + 4 * i) + 604))(
                    *(int*)(v6 + 4 * i), a2);
            }
        }
    }
    return result;
}

// 0x4A2B80 vmt270 —— 基类检查 + 附加条件（+7093 == 0）
int IRDActiveObject_vmt270(char* this_)
{
    return IRDCollisionObject_vmt270((int*)this_) != 0 && *(this_ + 7093) == 0;
}

// ============================================================
// 动作速率族（研究 P38 全链的对象侧接口）
// ============================================================

// 0x495310 vmt378 —— 速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
int IRDActiveObject_vmt378(int* this_, int a2, int a3, int a4, int a5)
{
    this_[1661] = a2;                                  // +6644
    this_[1662] = a3;                                  // +6648
    int v6 = (a2 != 0)
        ? (*(int(__thiscall**)(int*, int))(*(int*)this_ + 976))(this_, a2)
        : a4;
    int v7 = (a3 != 0)
        ? (*(int(__thiscall**)(int*, int))(*(int*)this_ + 976))(this_, a3)
        : a5;
    (*(void(__thiscall**)(int*, int))(*(int*)this_ + 980))(this_, v6);
    return (*(int(__thiscall**)(int*, int))(*(int*)this_ + 984))(this_, v7);
}

// 0x495380 vmt3D4 —— 速率档位应用: 写 +6652 后按 (6636/6640) 调 vt+896
int IRDActiveObject_vmt3D4(int* this_, int a2)
{
    int v2 = *this_;
    this_[1663] = a2;                                  // +6652 速率千分档
    return (*(int(__stdcall**)(int, int))(v2 + 896))(this_[1659], this_[1660]);
}

// 0x495740 vmt3D0 —— ★ 速率查询（分四类）【会话 3 还原】
//   1 = 移动速度: 属性块(vt+672(3)) +816 防篡读 × +830 浮点系数
//   2 = 攻击速度: +844 × +858
//   3 = vt+900(3) 返回值
//   4 = sub_495540(属性块)
//   default = 1000（千分基准）
int IRDActiveObject_vmt3D0(void* this_, int a2)
{
    switch (a2) {
    case 1: {
        int v2 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
        int v3 = sub_41A5E0(v2 + 816);
        return (int)((double)v3 * COERCE_FLOAT(sub_41A5E0(v2 + 830)));
    }
    case 2: {
        int v5 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
        int v3 = sub_41A5E0(v5 + 844);
        return (int)((double)v3 * COERCE_FLOAT(sub_41A5E0(v5 + 858)));
    }
    case 3:
        return (*(int(__thiscall**)(void*, int))(*(int*)this_ + 900))(this_, 3);
    case 4:
        return sub_495540((*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3));
    default:
        return 1000;
    }
}

// 0x495A10 vmt3D8 —— ★ 动作速率应用（千分值 ×0.1 → sub_493D00 写动画速率；
// 同时传播到 +128 子对象链全部动画 —— 研究 P38 "部件树全传播"的对象侧入口）
void IRDActiveObject_vmt3D8(int* this_, int a2)
{
    int v3 = this_[30];                                // 动画对象
    this_[1664] = a2;                                  // +6656
    if (v3 != 0) {
        float v6 = (double)a2 * 0.1;                   // 千分 → 百分
        sub_493D00((void*)v3, v6);
    }
    int* v4 = (int*)this_[32];                         // +128 子对象链表头
    int* v5 = (int*)*v4;
    if ((int*)*v4 != v4) {
        do {
            float v7 = (double)this_[1664] * 0.1;
            sub_493D00((void*)v5[3], v7);
            v5 = (int*)*v5;
        } while (v5 != (int*)*(this_ + 32));
    }
}

// 0x495600 vmt37C —— ★ 动画速率缓存写入【会话 3 还原】
// 依据朝向 a3(0/2左 1/3右 → ±1.0) × 档位 +6652(非1000时 ×0.001) 得速率;
// 写入动画对象 +16+a2*4 (浮点) 与 +28+a2*4 (整型, sub_494F60 联动)，带脏标记 +196。
// +6632[a2] 标志非 0 → sub_4A0600。
char IRDActiveObject_vmt37C(int* this_, int a2, int a3, char a4)
{
    int v10 = a4 != 0 ? this_[a2 + 1654] : this_[a2 + 1652];
    int v9 = this_[a2 + 1656];
    float v12 = 0.0f;
    if (a3 == 0 || a3 == 2) v12 = -1.0f;
    else if (a3 == 1 || a3 == 3) v12 = 1.0f;
    if (this_[1663] != 1000)                           // 变速档 ≠ 基准
        v12 = (float)((double)this_[1663] * v12 * 0.001);
    char* v6 = (char*)this_[28];                       // 兜底/动画基对象
    float v11 = (float)((double)v10 * v12);
    if (*(int*)v6 != 0
        && (*(unsigned char(__thiscall**)(int))(**(int**)v6 + 308))(*(int*)v6) != 0
        && *(float*)&v6[4 * a2 + 16] != v11) {
        *(float*)&v6[4 * a2 + 16] = v11;
        v6[196] = 1;
    }
    char* v7 = (char*)this_[28];
    int v13 = (int)((double)v9 * v12);
    if (*(int*)v7 != 0
        && (*(unsigned char(__thiscall**)(int))(**(int**)v7 + 308))(*(int*)v7) != 0
        && *(int*)&v7[4 * a2 + 28] != v13) {
        *(int*)&v7[4 * a2 + 28] = v13;
        v7[196] = 1;
        sub_494F60(a2, -1);
    }
    char result = *((BYTE*)this_ + a2 + 6632);
    if (result != 0) {
        sub_4A0600(a2);
        result = (char)a3;
    }
    this_[a2 + 1659] = a3;                             // +6636+a2 = 当前方向档
    return result;
}

// 0x495290 vmt36C —— 参数组写入（+6608 族 5 元组 + 转发 vt+892）
int IRDActiveObject_vmt36C(int* this_, int a2, int a3, int a4, int a5, int a6, char a7)
{
    this_[a2 + 1652] = a3;
    this_[a2 + 1654] = a4;
    *((BYTE*)this_ + a2 + 6634) = (BYTE)a5;
    this_[a2 + 1656] = a6;
    *((BYTE*)this_ + a2 + 6632) = a7;
    if (a6 != 0)
        *((BYTE*)this_ + a2 + 6634) = 0;
    int flag = 1;
    if (this_[1659] == 4 || this_[1660] == 4)
        flag = 0;
    return (*(int(__thiscall**)(int*, int, int, int))(*(int*)this_ + 892))(
        this_, a2, *(int*)((char*)this_ + a2 * 4 + 6636), flag);
}

// 0x495250 vmt214 —— 双标志门 + 转发 vt+968
char IRDActiveObject_vmt214(BYTE* this_, unsigned int a2, int a3, int a4)
{
    char result = *(this_ + 6634);
    if (result != 0) {
        result = *(this_ + 6635);
        if (result != 0 && *((int*)this_ + 1674) == -1) {
            if (a2 <= 1)
                return (*(char(__thiscall**)(BYTE*, unsigned int))(*(int*)this_ + 968))(this_, a2);
            result = (char)a2;
        }
    }
    return result;
}

// 0x4953B0 vmt35C —— ★ 每 3 次调用发一次 UDP（%3 周期）【会话 3 新发现】
// +6744(1686*4) 冻结标志自增; %3==0 时: 会话.vt+8(33,2) → 写 vt+48/vt+52 两 ID → (0,-1)
int IRDActiveObject_vmt35C(int* this_)
{
    int result = (*(int(__thiscall**)(int*))(*this_ + 852))(this_);   // vt+852 门
    if ((char)result != 0) {
        int v3 = this_[1686] + 1;
        this_[1686] = v3;
        int v4 = v3 % 3;
        result = v3 / 3;
        if (v4 == 0) {
            (*(void(__thiscall**)(int, int, int))(*(int*)0x8F8520 + 8))(0x8F8520, 33, 2);
            int v5 = *(int*)0x8F8520;
            int v6 = (*(int(__thiscall**)(int*))(*this_ + 48))(this_);
            (*(void(__thiscall**)(int, int))(v5 + 36))(0x8F8520, v6);
            int v7 = *(int*)0x8F8520;
            int v8 = (*(int(__thiscall**)(int*))(*this_ + 52))(this_);
            (*(void(__thiscall**)(int, int))(v7 + 36))(0x8F8520, v8);
            return (*(int(__thiscall**)(int, int, int))(*(int*)0x8F8520 + 60))(0x8F8520, 0, -1);
        }
    }
    return result;
}

// 0x494FA0 vmt380 —— 双目标检查（双方均需条件 16 不在 且 vt+308 通过）
int IRDActiveObject_vmt380(int* this_, int a2, int a3)
{
    int result = (*(int(__thiscall**)(int*))(*this_ + 308))(this_);
    if ((char)result != 0) {
        result = this_[50];
        if (result == 0) {
            result = (*(int(__thiscall**)(int*, int))(*this_ + 776))(this_, 16);
            if ((char)result == 0) {
                char v5 = 1;
                if (a2 == 4 || a3 == 4)
                    v5 = 0;
                (*(void(__thiscall**)(int*, int, int, char))(*(int*)this_ + 892))(this_, 0, a2, v5);
                return (*(int(__thiscall**)(int*, int, int, char))(*(int*)this_ + 892))(this_, 1, a3, v5);
            }
        }
    }
    return result;
}

// ============================================================
// 武器/装备模式状态机（vmt3C8 族，+6696..6708）
// ============================================================

// 0x495010 vmt3C8 —— ★ 装备/武器模式切换状态机【会话 3 还原骨架】
// +6696(1674) 模式位: -1 空闲 / 0 / 1
// 依赖 vt+184/vt+188（双当前值）、vt+120/124（坐标）、vt+136（有效性检查）、
// vt+896（应用）、+6700(1675)/+6704(1676)/+6708(1677) 缓存。
// （完整逐行见 work/decomp_core_vt.txt; 篇幅大, 语义=武器切换的序列化校验）
void IRDActiveObject_vmt3C8(int* a1, int a2, int a3, int a4)
{
    if (a1[1674] != -1)
        return;
    if (a4 != 0 && a4 != 1)
        return;
    int v6 = a4 != 0
        ? (*(int(__thiscall**)(int*))(*a1 + 188))(a1)
        : (*(int(__thiscall**)(int*))(*a1 + 184))(a1);
    if (v6 == 4)
        return;
    int v7 = a4 != 0
        ? (*(int(__thiscall**)(int*))(*a1 + 184))(a1)
        : (*(int(__thiscall**)(int*))(*a1 + 188))(a1);
    if (v7 != 4)
        return;
    // 扫描区间: 以 a4 方向从当前位置向外探测有效目标（vt+136 调用）
    // 命中 → 记录模式 1/2 → +6696..6708 缓存 → vt+896 应用
    // （骨干部已对齐; 逐行版在证据文件中）
}

// 0x4951F0 vmt3CC —— 模式有效期校验（依赖值变化则失效）
int IRDActiveObject_vmt3CC(int* this_)
{
    int result = this_[1674];
    if (result != -1) {
        result = result != 0
            ? (*(int(__thiscall**)(int*))(*this_ + 184))(this_)
            : (*(int(__thiscall**)(int*))(*this_ + 188))(this_);
        if (this_[1676] != result
            || (this_[1674] != 0
                ? (result = (*(int(__thiscall**)(int*))(*this_ + 120))(this_))
                : (result = (*(int(__thiscall**)(int*))(*this_ + 124))(this_)),
                this_[1677] != result)) {
            this_[1674] = -1;                          // 失效
        }
    }
    return result;
}

// ============================================================
// 属性读取族（防篡改管线的消费侧 —— 研究第 17 轮闭环）
// ============================================================

// 0x4A1CA0 vmt188 —— HP 类属性: 属性块 +60 防篡读 × 浮点壳(+74)
// （研究 P14 九步公式的原料之一）
double IRDActiveObject_vmt188(void* this_)
{
    int v1 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
    int v3 = sub_41A5E0(v1 + 60);
    return sub_43B5A0((void*)(v1 + 74)) * (double)v3;
}

// 0x4A1CE0 vmt18C —— MP 类属性: +1012 × 浮点壳(+1026)
double IRDActiveObject_vmt18C(void* this_)
{
    int v1 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
    int v3 = sub_41A5E0(v1 + 1012);
    return sub_43B5A0((void*)(v1 + 1026)) * (double)v3;
}

// 0x4A1D20 vmt190 / 0x4A1D40 vmt194 —— 纯整数属性读取
int IRDActiveObject_vmt190(void* this_)
{
    int v1 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
    return sub_41A5E0(v1 + 1306);
}
int IRDActiveObject_vmt194(void* this_)
{
    int v1 = (*(int(__thiscall**)(void*, int))(*(int*)this_ + 672))(this_, 3);
    return sub_41A5E0(v1 + 1124);
}

// 0x4A1E20/0x4A1E30 vmt2E0/2E4 等 —— 研究已引（GetHP 族），此处索引。
