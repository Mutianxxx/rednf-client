// ============================================================
// 【40JP逆向源代码工程】src/cnrd/ActiveObjectEquipment.cpp
// ★ 观察者-装备体系（0x52Dxxx 区 14 函数，会话 3 新分析）
//
// 实锤结论：18 观察者槽 = 装备/称号/附魔等"属性来源组件"的挂载点。
//   - vmt324 直证 RTDynamicCast → CNRDEquipment + 等级/职业检查
//   - vmt328 = UDP 包 type=10（物品使用请求，含 4 个防篡读字段）
//   - vmt310/314 = 装备挂载/卸下
//   - vmt31C = 全观察者属性求和
//   - vmt368 = 1 秒窗光环/标记显示链（+6544 链表）
// 研究文档 §13（观察者注册点未定位）就此收账：注册点 = vmt310；
// 身份 = 装备对象（IRDItem→CNRDEquipment 链）。
// ============================================================

#include "IRDActiveObject.h"

extern int   sub_41A5E0(int);                     // 防篡改数值读取
extern int   sub_41ACF0(int);                     // 字符串对象取值
extern int   sub_43B5A0(void*);
extern void  sub_44ACC0(int);
extern void  sub_445150(void*);                   // 包体容器析构
extern void  sub_4E9A50(void*);                   // 包体容器构造 (60B)
extern void  sub_4F32A0(int);                     // 事件→对象转换
extern void  sub_494240(void*, int, void*);       // 组件槽挂载（源, 宿主, 目标）
extern int   sub_492980(int);                     // 组件槽卸载/释放
extern void  sub_499690(void*, int, int, int, int, float, int, float, int, float, int, float, float); // 特效绘制
extern double sub_4049C0_f(float, float, int, int); // lerp（已还原 camera_fx）
extern int   sub_4049F0(float, float, int, int, int);
extern int   sub_52DAA0(int, int, int*);          // 事件链表有序插入
extern void  sub_52E130(int);
extern int   sub_699000(PauseClock*);
extern void* dword_8F8520;
extern void* dword_8F7C04;
extern void* dword_79C0B0;
extern char  szPassword[];
extern void* operator_new(unsigned);

// ============================================================
// 属性汇总与装备检查
// ============================================================

// 0x52D550 vmt31C —— ★ 全观察者属性求和
// 遍历 18 槽，vt+792 非空者：sum += observer->vt+16()（属性块）-> +56（某项数值）
int IRDActiveObject_vmt31C(int* this_)
{
    int sum = 0;
    int* obs = this_ + 1617;                          // +6468
    for (int i = 0; i < 18; ++i) {
        if ((*(int(__thiscall**)(int*, int))(*this_ + 792))(this_, i) != 0) {
            int statBlock = (*(int(__thiscall**)(int))(*(int*)*obs + 16))(*obs);
            sum += *(int*)(statBlock + 56);           // 属性块 +56 项
        }
        ++obs;
    }
    return sum;
}

// 0x52D5A0 vmt324 —— ★ 装备可用性检查（含 CNRDEquipment RTTI 直证）
// 1) 大状态 == 2（冰冻类）→ false
// 2) RTDynamicCast(this → IRDCharacter)；职业限制字节 [statBlock + 物品类型 + 60] == 0 → false
// 3) 本地玩家使用时: RTDynamicCast(a2 → CNRDEquipment)；
//    +32 防篡读 != -1 时: vt+1160(等级) 检查 + sub_44ACC0(1)
// 4) 最终: 属性块值 >= CNRDParticleCreater__vmt30(a2)（需 求等级）
//    || (a2->vt+20(1) != 0 && a2->vt+132() == 2)
bool IRDActiveObject_vmt324(int* this_, int a2)
{
    if (this_[50] == 2)                               // 大状态冰冻
        return false;

    int v14 = (*(int(__thiscall**)(int))(*(int*)a2 + 16))(a2);
    int v6 = RTDynamicCast(this_, 0, IRDActiveObject_RTTI, IRDCharacter_RTTI, 0);
    if (v6 != 0) {
        int statBlock = *(int*)(*(int(__thiscall**)(int))(*(int*)v6 + 1032))(v6);
        if (*(BYTE*)(statBlock + v14 + 60) == 0)      // 职业限制字节
            return false;
        if ((int)dword_8F7C04 == v6) {                // 本地玩家自己用
            int v8 = RTDynamicCast(a2, 0, IRDItem_RTTI, CNRDEquipment_RTTI, 0);
            if (v8 != 0) {
                int v9 = (*(int(__thiscall**)(int))(*(int*)v8 + 172))(v8);
                if (sub_41A5E0(v9 + 32) != -1) {      // 装备需求等级 +32
                    int v10 = (*(int(__thiscall**)(int))(*(int*)v8 + 172))(v8);
                    int v11 = sub_41A5E0(v10 + 32);
                    if ((*(int(__thiscall**)(int, int))(*(int*)v6 + 1160))(v6, v11) == 0
                        || sub_44ACC0(1) == 0)
                        return false;                 // 等级不够
                }
            }
        }
    }
    int* stat = (int*)(*(int(__thiscall**)(int, int))(*this_ + 672))(this_, 3);
    return *stat >= CNRDParticleCreater_vmt30(a2)
        || ((*(unsigned char(__thiscall**)(int, int))(*(int*)a2 + 20))(a2, 1) != 0
            && *(int*)(*(int(__thiscall**)(int))(*(int*)a2 + 132))(a2) == 2);
}

// 0x52D6D0 vmt32C —— 装备动作转发（取物品类型/索引 → vt+808 应用）
int IRDActiveObject_vmt32C(int* this_, int a2, int a3)
{
    int v6 = *this_;
    int itemType = (*(int(__thiscall**)(int))(*(int*)a2 + 172))(a2);
    int v7 = (*(int(__thiscall**)(int, int))(*(int*)a2 + 188))(a2, a3);
    int v8 = (*(int(__thiscall**)(int, int))(*(int*)a2 + 16))(a2, v7);
    return (*(int(__thiscall**)(int*, int, int))(v6 + 808))(this_, *(int*)itemType, *(int*)(v8 + 4));
}

// ============================================================
// ★ UDP 包发射族（本区两个新包类型）
// ============================================================

// 0x52D720 vmt328 —— ★ UDP 包 type=10「物品使用请求」
// 载荷: (this+48, this+52, a2, a3, 防篡读×3, v7[0..2] 三元组)
// a5 = 目标槽(-1 = 无); 60 字节包体容器 sub_4E9A50。
int IRDActiveObject_vmt328(void* this_, int a2, int a3, int* a4, int a5)
{
    int result = (*(int(__thiscall**)(void*))(*(int*)this_ + 308))(this_);
    if ((char)result != 0) {
        char pkt[60];
        sub_4E9A50(pkt);
        int* v7 = a4;
        if (a4 == 0)
            v7 = (int*)pkt;
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 8))(
            (int)dword_8F8520, 10, a5 == -1);
        int v8 = *(int*)dword_8F8520;
        int v9 = (*(int(__thiscall**)(void*))(*(int*)this_ + 48))(this_);
        (*(void(__thiscall**)(int, int))(v8 + 36))((int)dword_8F8520, v9);
        int v10 = *(int*)dword_8F8520;
        int v11 = (*(int(__thiscall**)(void*))(*(int*)this_ + 52))(this_);
        (*(void(__thiscall**)(int, int))(v10 + 36))((int)dword_8F8520, v11);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 32))((int)dword_8F8520, a2);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))((int)dword_8F8520, a3);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 40))((int)dword_8F8520, *v7);
        int val1 = sub_41A5E0((int)(v7 + 1));
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 40))((int)dword_8F8520, val1);
        int val2 = sub_41A5E0((int)v7 + 18);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 40))((int)dword_8F8520, val2);
        int val3 = sub_41A5E0((int)(v7 + 8));
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 40))((int)dword_8F8520, val3);
        if (a5 == -1)
            (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 60))((int)dword_8F8520, 1, -1);
        else
            (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 60))((int)dword_8F8520, 1, a5);
        return sub_445150(pkt);
    }
    return result;
}

// 0x52D860 vmt360 —— ★ UDP 包 type=25「时钟同步/事件计时」
// 载荷: (this+48, this+52, a2, clock_now(+36))
int IRDActiveObject_vmt360(void* this_, int a2)
{
    int result = (*(int(__thiscall**)(void*))(*(int*)this_ + 308))(this_);
    if ((char)result != 0) {
        (*(void(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 8))((int)dword_8F8520, 25, 2);
        int v4 = *(int*)dword_8F8520;
        int v5 = (*(int(__thiscall**)(void*))(*(int*)this_ + 48))(this_);
        (*(void(__thiscall**)(int, int))(v4 + 36))((int)dword_8F8520, v5);
        int v6 = *(int*)dword_8F8520;
        int v7 = (*(int(__thiscall**)(void*))(*(int*)this_ + 52))(this_);
        (*(void(__thiscall**)(int, int))(v6 + 36))((int)dword_8F8520, v7);
        (*(void(__thiscall**)(int, int))(*(int*)dword_8F8520 + 36))((int)dword_8F8520, a2);
        int v8 = *(int*)dword_8F8520;
        int v9 = sub_699000((PauseClock*)((char*)this_ + 36));   // clockAux 当前时刻
        (*(void(__thiscall**)(int, int))(v8 + 40))((int)dword_8F8520, v9);
        return (*(int(__thiscall**)(int, int, int))(*(int*)dword_8F8520 + 60))((int)dword_8F8520, 1, -1);
    }
    return result;
}

// ============================================================
// 观察者（装备）挂载 / 卸下 —— 研究 §13 悬案的答案
// ============================================================

// 0x52DAD0 vmt310 —— ★ 装备观察者挂载
// a3 = 观察者对象（装备/称号）; a2 = 附加参数
// 1) vt+172 取槽位; 槽位 == 18 → 直接返回
// 2) 对象初始化链: vt+16(a2) / vt+264()==0 → vt+256() / vt+788(槽位) /
//    写入 this+6468+4*槽位 = 观察者 / vt+208(this 宿主) / vt+148 激活 /
//    清 [vt+16()+32] / vt+800 / vt+676(0)
// 3) 遍历观察者内嵌记录数组（vt+248 容器, 步长 124 字节）:
//    每项 → vt+692(this, 记录[0], this+6160, 记录+1)
int IRDActiveObject_vmt310(int this_, int a2, int a3)
{
    if (a3 == 0 || *(int*)(*(int(__thiscall**)(int))(*(int*)a3 + 172))(a3) == 18)
        return a3;
    (*(void(__thiscall**)(int, int))(*(int*)a3 + 16))(a3, a2);
    int slot = *(int*)(*(int(__thiscall**)(int))(*(int*)a3 + 172))(a3);
    if ((*(unsigned char(__thiscall**)(int))(*(int*)a3 + 264))(a3) == 0)
        (*(void(__thiscall**)(int))(*(int*)a3 + 256))(a3);
    int v6 = (*(int(__thiscall**)(int, int))(*(int*)this_ + 788))(this_, slot);
    *(int*)(this_ + 4 * slot + 6468) = a3;            // ★ 观察者槽写入
    (*(void(__thiscall**)(int, int))(*(int*)a3 + 208))(a3, this_);   // 回指宿主
    (*(void(__thiscall**)(int))(*(int*)a3 + 148))(a3);
    *(BYTE*)((*(int(__thiscall**)(int))(*(int*)a3 + 16))(a3) + 32) = 0;
    (*(void(__thiscall**)(int))(*(int*)this_ + 800))(this_);
    (*(void(__thiscall**)(int, int))(*(int*)this_ + 676))(this_, 0);
    int v7 = (*(int(__thiscall**)(int))(*(int*)a3 + 248))(a3);        // 内嵌记录容器
    for (int* i = *(int**)(v7 + 4); i != *(int**)(v7 + 8); i += 31) {  // 124B 步长
        (*(void(__thiscall**)(int, int, int, int*))(*(int*)this_ + 692))(
            this_, *i, this_ + 6160, i + 1);
    }
    return v6;
}

// 0x52DBC0 vmt314 —— ★ 装备观察者卸下
int IRDActiveObject_vmt314(int* this_, int a2)
{
    if (a2 == 18)
        return 0;
    int v4 = this_[a2 + 1617];                        // 槽内对象
    if (v4 == 0)
        return 0;
    this_[a2 + 1617] = 0;                             // 清槽
    (*(void(__thiscall**)(int))(*(int*)v4 + 152))(v4);
    (*(void(__thiscall**)(int, int))(*(int*)v4 + 208))(v4, 0);       // 断回指
    (*(void(__thiscall**)(int*))(*this_ + 800))(this_);
    (*(void(__thiscall**)(int*, int))(*this_ + 676))(this_, 0);
    int v5 = (*(int(__thiscall**)(int))(*(int*)v4 + 248))(v4);
    int v6 = *(int*)(v5 + 4);
    for (int i = v5; v6 != *(int*)(i + 8); v6 += 124) {               // 逐记录清理
        (*(int(__thiscall**)(int*, int*, int))(*this_ + 696))(this_, this_ + 1540, v6 + 4);
    }
    return v4;
}

// ============================================================
// 观察者组件槽复制 / 卸载（this+6160 区）
// ============================================================

// 0x52DC70 vmt2B4 —— ★ 观察者组件逐槽挂载
// 结构: 9 个单指针（+0..8）+ 两段数组（+40..44 / +56..60）。
// 每对 (源, 目标) 非空 → sub_494240(源, 宿主, 目标) 挂载。
void IRDActiveObject_vmt2B4(int a1, int* a2, char* a3)
{
    if (*a2 != 0 && *(int*)a3 != 0)
        sub_494240((void*)*a2, a1, (void*)*(int*)a3);
    if (a2[1] != 0 && *((int*)a3 + 1) != 0)
        sub_494240((void*)a2[1], a1, (void*)*((int*)a3 + 1));
    if (a2[2] != 0 && *((int*)a3 + 2) != 0)
        sub_494240((void*)a2[2], a1, (void*)*((int*)a3 + 2));
    for (int i = 2, *p = a2 + 3; i != 0; --i, ++p) {
        if (*p != 0 && *(int*)((char*)p + (a3 - (char*)a2)) != 0)
            sub_494240((void*)*p, a1, (void*)*(int*)((char*)p + (a3 - (char*)a2)));
    }
    if (a2[5] != 0 && *((int*)a3 + 5) != 0) sub_494240((void*)a2[5], a1, (void*)*((int*)a3 + 5));
    if (a2[6] != 0 && *((int*)a3 + 6) != 0) sub_494240((void*)a2[6], a1, (void*)*((int*)a3 + 6));
    if (a2[7] != 0 && *((int*)a3 + 7) != 0) sub_494240((void*)a2[7], a1, (void*)*((int*)a3 + 7));
    if (a2[8] != 0 && *((int*)a3 + 8) != 0) sub_494240((void*)a2[8], a1, (void*)*((int*)a3 + 8));
    // 数组段 1（+40/+44 = 基/尾）
    int n1 = a2[10] != 0 ? (a2[11] - a2[10]) >> 2 : 0;
    int m1 = *((int*)a3 + 10) != 0 ? (*((int*)a3 + 11) - *((int*)a3 + 10)) >> 2 : 0;
    int cnt1 = (n1 != 0 && m1 > n1) ? m1 : (m1 != 0 ? m1 : n1);   // 取较长段
    for (int j = 0; j < cnt1; ++j) {
        int src = *(int*)(a2[10] + 4 * j);
        if (src != 0) {
            int dst = *(int*)(*((int*)a3 + 10) + 4 * j);
            if (dst != 0)
                sub_494240((void*)src, a1, (void*)dst);
        }
    }
    // 数组段 2（+56/+60）
    int n2 = a2[14] != 0 ? (a2[15] - a2[14]) >> 2 : 0;
    int m2 = *((int*)a3 + 14) != 0 ? (*((int*)a3 + 15) - *((int*)a3 + 14)) >> 2 : 0;
    int cnt2 = (n2 != 0 && m2 > n2) ? m2 : (m2 != 0 ? m2 : n2);
    for (int k = 0; k < cnt2; ++k) {
        int src = *(int*)(a2[14] + 4 * k);
        if (src != 0) {
            int dst = *(int*)(*((int*)a3 + 14) + 4 * k);
            if (dst != 0)
                sub_494240((void*)src, a1, (void*)dst);
        }
    }
}

// 0x52DE60 vmt2B8 —— ★ 观察者组件卸载（同结构逐项 sub_492980 释放）
void IRDActiveObject_vmt2B8(int* a1, char* a2)
{
    if (*a1 != 0 && *(int*)a2 != 0) sub_492980(*(int*)a2);
    if (a1[1] != 0 && *((int*)a2 + 1) != 0) sub_492980(*((int*)a2 + 1));
    if (a1[2] != 0 && *((int*)a2 + 2) != 0) sub_492980(*((int*)a2 + 2));
    for (int i = 2, *p = a1 + 3; i != 0; --i, ++p) {
        if (*p != 0 && *(int*)((char*)p + (a2 - (char*)a1)) != 0)
            sub_492980(*(int*)((char*)p + (a2 - (char*)a1)));
    }
    if (a1[5] != 0 && *((int*)a2 + 5) != 0) sub_492980(*((int*)a2 + 5));
    if (a1[6] != 0 && *((int*)a2 + 6) != 0) sub_492980(*((int*)a2 + 6));
    if (a1[7] != 0 && *((int*)a2 + 7) != 0) sub_492980(*((int*)a2 + 7));
    if (a1[8] != 0 && *((int*)a2 + 8) != 0) sub_492980(*((int*)a2 + 8));
    int n1 = a1[10] != 0 ? (a1[11] - a1[10]) >> 2 : 0;
    int m1 = *((int*)a2 + 10) != 0 ? (*((int*)a2 + 11) - *((int*)a2 + 10)) >> 2 : 0;
    int cnt1 = (n1 != 0 && m1 > n1) ? m1 : (m1 != 0 ? m1 : n1);
    for (int j = 0; j < cnt1; ++j) {
        if (*(int*)(a1[10] + 4 * j) != 0) {
            int v = *(int*)(*((int*)a2 + 10) + 4 * j);
            if (v != 0) sub_492980(v);
        }
    }
    int n2 = a1[14] != 0 ? (a1[15] - a1[14]) >> 2 : 0;
    int m2 = *((int*)a2 + 14) != 0 ? (*((int*)a2 + 15) - *((int*)a2 + 14)) >> 2 : 0;
    int cnt2 = (n2 != 0 && m2 > n2) ? m2 : (m2 != 0 ? m2 : n2);
    for (int k = 0; k < cnt2; ++k) {
        if (*(int*)(a1[14] + 4 * k) != 0) {
            int v = *(int*)(*((int*)a2 + 14) + 4 * k);
            if (v != 0) sub_492980(v);
        }
    }
}

// ============================================================
// 光环/标记显示链（+6544 链表，1 秒窗）
// ============================================================

// 0x52E020 vmt368 —— ★ 1 秒窗特效链逐帧推进
// 链表 this+6544（6548 = 计数）；节点: [0]next [1]prev [2]资源 [3]启动时刻。
// elapsed = clock_now(clockThird +64) − 启动; ≤1000ms → 绘制（alpha 50→255 淡入）;
// >1000ms → 摘链释放。
void** IRDActiveObject_vmt368(int this_, int a3, int a4, float a5)
{
    if (*(int*)(this_ + 6548) == 0)
        return 0;
    void** head = *(void***)(this_ + 6544);
    int* node = (int*)*head;
    while ((void**)node != head) {
        int now = sub_699000((PauseClock*)(this_ + 64));
        int elapsed = now - node[3];
        if (elapsed <= 1000) {
            sub_4049F0(0.0f, 50.0f, elapsed, 1000, 1);
            int alpha = (int)sub_4049C0_f(255.0f, 0.0f, elapsed, 1000);   // 淡出
            // 绘制: (渲染器, a3, a4, 0, a2−166|elapsed, a5, 资源, 0.5, 0.5f, ...)
            sub_499690(dword_79C0B0, a3, a4, 0, elapsed, a5, node[2],
                       0.5, 1056964608, 0.0, (alpha << 24) | 0xFFFFFF, 0.0, 0.0);
            node = (int*)*node;
        } else {
            int* next = (int*)*node;                 // 摘链释放
            if ((void**)node != head) {
                *(int*)node[1] = (int)next;
                *(int*)(*node + 4) = node[1];
                free(node);
                *(int*)(this_ + 6548) -= 1;
            }
            node = next;
        }
    }
    return (void**)node;
}

// 0x52E1C0 vmt364 —— ★ 光环/标记显示入链
// 事件 sub_4F32A0(a2) → 插入 +6544 链表（有序插入 sub_52DAA0，时刻 = clockThird.now）
int* IRDActiveObject_vmt364(int* this_, int a2)
{
    int v8[2];
    v8[0] = sub_4F32A0(a2);
    int v3 = sub_699000((PauseClock*)(this_ + 16));
    int v4 = this_[1636];                            // +6544 链表头
    v8[1] = v3;
    int v5 = sub_52DAA0(v4, *(int*)(v4 + 4), v8);
    sub_52E130(1);
    *(int*)(v4 + 4) = v5;
    int* result = *(int**)(v5 + 4);
    *result = v5;
    return result;
}

// ============================================================
// 观察者名字与状态
// ============================================================

// 0x52D8F0 vmt33C —— 取观察者名（称号字符串; 空则 szPassword）
const char* IRDActiveObject_vmt33C(int* this_)
{
    int v1 = this_[1626];                            // +6504 当前称号观察者
    if (v1 == 0)
        return szPassword;
    int v2 = (*(int(**)(void))(*(int*)v1 + 16))();
    return (const char*)sub_41ACF0(v2 + 8);
}

// 0x52D920 vmt340 —— 转发 +6504 观察者的 vt+252(0)
int IRDActiveObject_vmt340(int* this_)
{
    int v1 = this_[1626];
    if (v1 != 0)
        return (*(int(__stdcall**)(int))(*(int*)v1 + 252))(0);
    return 0;
}

// 0x52D940 vmt320 —— 18 观察者 vt+216 全广播
int IRDActiveObject_vmt320(int* this_)
{
    int* obs = this_ + 1617;
    int result = 0;
    for (int i = 18; i != 0; --i) {
        result = *obs;
        if (*obs != 0)
            result = (*(int(**)(void))(*(int*)result + 216))();
        ++obs;
    }
    return result;
}
