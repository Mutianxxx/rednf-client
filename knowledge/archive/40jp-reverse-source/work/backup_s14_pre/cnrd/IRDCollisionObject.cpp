// ============================================================
// 【40JP逆向源代码工程】src/cnrd/IRDCollisionObject.cpp
// 战斗/碰撞段实现 —— 会话 3 新分析函数（逐行还原）
// 42 轮研究已全文定案的命中链函数不重复列出（见 docs/14 交叉引用表）
// ============================================================

#include "IRDCollisionObject.h"

extern int  sub_699000(PauseClock*);  // 【clock_now(clk)】
extern void sub_4938F0(void*);                    // 动画帧同步
extern int  sub_4918E0(void*, int);               // 动画盒四边界提取（研究 P29 族）
extern int  sub_4A2C40(void*);                    // 动画率状态查询
extern int  sub_4E4A50(void*, int, int, int, int, int, int, int, int, void*); // 动作执行核心
extern int  sub_4E4C10(void*, int, int, int*, int, int, int, int);  // sub_4E4C10 —— 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
extern void sub_4E80E0(void*);                    // 位移序列化
extern int  sub_48D1E0(void*);                    // 数据流写出
extern int  sub_431230(int, int*);                // 命中列表追加
extern void sub_4E6FD0(int);                      // 移动停止联动
extern int  sub_4BE520(void*, int*);              // vector 查找辅助
extern void sub_4A3130(void*, int);
extern int  sub_472D40(int);                      // 宿主对象查询
extern void sub_4E80E0_reserved();
extern void* dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
extern void* dword_8F7C04;

// ------------------------------------------------------------
// 0x4E54D0 vmt1E8 —— ★ 3D AABB 重叠测试（无 z 轴；俯视平面）
// 判据: A.min ≤ B.max 且 B.min ≤ A.max 在 x/y 两轴同时成立。
// 四边取法: vt+440/444 = x 左右边界? 实际语义: 440=xmin 444=xmax 448=ymin 452=ymax
// （与 vmt1B8/1BC = 中心±宽/2 的边界族配套）
// ------------------------------------------------------------
bool IRDCollisionObject_vmt1E8(void* this_, int nArg2)  // 函数：★ 3D AABB 重叠测试（无 z 轴；俯视平面）
{
    // 第一轴: this.min < other.max? （判定链：三段 all-true 才重合）
    int bMax = (*(int(__thiscall**)(int))(*(int*)nArg2 + 440))(nArg2);
    if ((*(int(__thiscall**)(void*))(*(int*)this_ + 444))(this_) < bMax)
        return false;
    int bMin = (*(int(__thiscall**)(int))(*(int*)nArg2 + 444))(nArg2);
    if (bMin < (*(int(__thiscall**)(void*))(*(int*)this_ + 440))(this_))
        return false;
    // 第二轴
    int bMax2 = (*(int(__thiscall**)(int))(*(int*)nArg2 + 448))(nArg2);
    if ((*(int(__thiscall**)(void*))(*(int*)this_ + 452))(this_) < bMax2)
        return false;
    int bMin2 = (*(int(__thiscall**)(int))(*(int*)nArg2 + 452))(nArg2);
    return bMin2 >= (*(int(__thiscall**)(void*))(*(int*)this_ + 448))(this_);
}

// ------------------------------------------------------------
// 0x4E5560 vmt1EC —— ★ 动画攻击盒世界坐标重叠测试【会话 3 新分析】
// 双方各自的动画对象(sub_4918E0 obj+60, 边界槽 0..3)给出四个边界:
//   this: 左=15−E(0)? 右=E(1)−15? 上=15−E(2)? 下=E(3)+?  ← 原文逐条:
//   v27 = 中心x + (15 − E0)     v30 = E1 + 中心x − 15
//   v29 = 中心y + (15 − E2)     v28 = 中心y + E3
// 目标: v26 = 中心x − E0'      v31 = 中心x + E1'
//       v23 = 中心y + E3' + E2'?（原文链: y+E3 之和不直读, 按边界比较）
// 判据: 目标 y 区间与本体 y 区间相交 且 x 区间相交（含"完全包含"分支）。
// 语义: 挥砍矩形 vs 受击矩形 的世界空间相交（研究 P29 的盒迭代下层实现）。
// ------------------------------------------------------------
char IRDCollisionObject_vmt1EC(int* this_, int* pDwArg2)  // 函数：★ 动画攻击盒世界坐标重叠测试【会话 3 新分析】
{
    int anim = this_[30];                              // +120 动画对象
    if (*(int*)(anim + 148) == -1)
        sub_4938F0((void*)anim);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int e0 = 15 - sub_4918E0((void*)(anim + 60), 0);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int cx = (*(int(__thiscall**)(int*))(*this_ + 120))(this_);  // 虚调用 vt+120（this_）转发(对象+缓冲)
    int xL = cx + e0;                                  // 左界
    anim = this_[30];  // this+120〔动画对象〕
    if (*(int*)(anim + 148) == -1)
        sub_4938F0((void*)anim);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int e1 = sub_4918E0((void*)(anim + 60), 1);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int xR = e1 + cx - 15;                             // 右界
    anim = this_[30];  // this+120〔动画对象〕
    if (*(int*)(anim + 148) == -1)
        sub_4938F0((void*)anim);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int e2 = 15 - sub_4918E0((void*)(anim + 60), 2);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int cy = (*(int(__thiscall**)(int*))(*this_ + 124))(this_);  // 虚调用 vt+124（this_）目标坐标y下界
    int yT = cy + e2;                                  // 上界
    anim = this_[30];  // this+120〔动画对象〕
    if (*(int*)(anim + 148) == -1)
        sub_4938F0((void*)anim);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int e3 = sub_4918E0((void*)(anim + 60), 3);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int yB = cy + e3;                                  // 下界

    // ---- 目标侧 ----
    int ta = pDwArg2[30];
    if (*(int*)(ta + 148) == -1)
        sub_4938F0((void*)ta);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int f0 = sub_4918E0((void*)(ta + 60), 0);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int tcx = (*(int(__thiscall**)(int*))(*pDwArg2 + 120))(pDwArg2);  // 虚调用 vt+120（pDwArg2）转发(对象+缓冲)
    int tXL = tcx - f0;
    ta = pDwArg2[30];
    if (*(int*)(ta + 148) == -1)
        sub_4938F0((void*)ta);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int f1 = sub_4918E0((void*)(ta + 60), 1);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int tXR = tcx + f1;
    ta = pDwArg2[30];
    if (*(int*)(ta + 148) == -1)
        sub_4938F0((void*)ta);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    sub_4918E0((void*)(ta + 60), 2);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    (*(void(__thiscall**)(int*))(*pDwArg2 + 124))(pDwArg2);  // 虚调用 vt+124（pDwArg2）目标坐标y下界
    (*(void(__thiscall**)(int*))(*pDwArg2 + 128))(pDwArg2);  // 虚调用 vt+128（pDwArg2）目标坐标y上界
    ta = pDwArg2[30];
    if (*(int*)(ta + 148) == -1)
        sub_4938F0((void*)ta);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int f3 = sub_4918E0((void*)(ta + 60), 3);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    int tY2 = (*(int(__thiscall**)(int*))(*pDwArg2 + 124))(pDwArg2) + f3;  // 目标 y 下界
    int tY1 = (*(int(__thiscall**)(int*))(*pDwArg2 + 128))(pDwArg2) + tY2; // 注: 原文含 z getter, 语义待核

    // ---- 判据（原文嵌套比较链）----
    if (tY1 > yT && tY1 < yB) {                        // 目标下界落于本体 y 区间内
        if (tXR > xL && tXR < xR)
            return 1;                                  // 目标右界在本体 x 区间内
        if (tXL > xL) {
            if (tXL < xR)
                return 1;                              // 目标左界在本体 x 区间内
        }
        if (tXL < xL && tXR > xR)
            return 1;                                  // 本体 x 区间被目标完全包含
    }
    return 0;
}

// ------------------------------------------------------------
// 0x4E57E0 vmt1A8 —— ★ 深度/属性修正伤害输入【会话 3 新分析】
// a2 = 参数结构 {float base; int a8; int type(+12); byte flag(+16)}
// type 0/2 → 用 vt+396/+400 加成; type 1 → vt+412/+416。
// 再乘属性项: (a8×0.01+1) × base，并按 type 叠 vt+392/+408 属性系数
// （经 sub_433F60 PVP 平衡路由除 flt_9A05F4/9A060C —— 研究第 17/27 轮的表）。
// 返回 sub_433F60(this,0) × 结果 = 最终伤害基值。
// ------------------------------------------------------------
double IRDCollisionObject_vmt1A8(void* this_, int pArg2, int nArg3)  // 函数：★ 深度/属性修正伤害输入【会话 3 新分析】
{
    if (nArg3 == 0) {
        sub_699000((PauseClock*)((char*)this_ + 36));  // this+36
        sub_699000((PauseClock*)((char*)this_ + 8));   // this+8
    }
    float base = *(float*)pArg2;
    if (*(BYTE*)(pArg2 + 16) != 0) {
        int v5 = *(int*)(pArg2 + 12);  // 读字段 v5 = pArg2+12（nSkillRec12）
        if (v5 == 0 || v5 == 2) {
            base = (float)(*(int(__thiscall**)(void*))(*(int*)this_ + 396))(this_) + base;
        } else if (v5 == 1) {
            base = (float)(*(int(__thiscall**)(void*))(*(int*)this_ + 412))(this_) + base;
        }
    }
    int type = *(int*)(pArg2 + 12);  // 读字段 type = pArg2+12（nSkillRec12）
    float v15 = ((double)*(int*)(pArg2 + 8) * 0.0099999998 + 1.0) * base;  // 常量 0.01f
    if (type == 0) {
        v15 = ((double)(*(int(__thiscall**)(void*))(*(int*)this_ + 400))(this_) * 0.0099999998 + 1.0) * v15;  // 常量 0.01f
    } else if (type == 1) {
        v15 = ((double)(*(int(__thiscall**)(void*))(*(int*)this_ + 416))(this_) * 0.0099999998 + 1.0) * v15;  // 常量 0.01f
    }
    if (type == 0) {
        float attr = (float)(*(int(__thiscall**)(void*))(*(int*)this_ + 392))(this_);
        double v10 = sub_433F60((int)this_, 3) * attr / flt_9A05F4;  // sub_433F60 —— PVP 平衡系数路由（研究第 17/27 轮）
        v15 = (v10 + 1.0) * v15;
    } else if (type == 1) {
        float attr = (float)(*(int(__thiscall**)(void*))(*(int*)this_ + 408))(this_);
        double v10 = sub_433F60((int)this_, 5) * attr / flt_9A060C;  // sub_433F60 —— PVP 平衡系数路由（研究第 17/27 轮）
        v15 = (v10 + 1.0) * v15;
    }
    return sub_433F60((int)this_, 0) * v15;  // sub_433F60 —— PVP 平衡系数路由（研究第 17/27 轮）
}

// ------------------------------------------------------------
// 0x4E5920 vmt290 —— ★ 朝向决策（依据宿主模式 +1316）【会话 3 新分析】
// 宿主 = this+29*4 的 +132 链; 模式 <4 且查询成功时:
//   模式 0 → 朝左(条件字节 0); 模式 1 → 朝右(1);
//   模式 2/3 → 比较自身 x 与宿主 x，大于则左否则右。
// ------------------------------------------------------------
int IRDCollisionObject_vmt290(int* this_)  // 函数：★ 朝向决策（依据宿主模式 +1316）【会话 3 新分析】
{
    int result = this_[29];                            // +116
    if (result != 0) {
        result = *(int*)(result + 132);  // 读字段 result = result+132（nAdd132）
        if (result != 0 && *(int*)(result + 108) != 0) {
            int mode = *(int*)(result + 1316);         // 宿主模式
            if (mode < 4) {
                result = sub_472D40(mode);  // sub_472D40 —— 宿主对象查询
                if (result != 0) {
                    switch (mode) {
                    case 0:  // case 0 分派
                        {
                            int anim = (*(int(__thiscall**)(int*))(*this_ + 60))(this_);  // 虚调用 vt+60（this_）对象销毁/释放
                            *(BYTE*)(anim + 52) = 0;   // 朝左
                        }
                        break;
                    case 1:  // case 1 分派
                        {
                            int anim = (*(int(__thiscall**)(int*))(*this_ + 60))(this_);  // 虚调用 vt+60（this_）对象销毁/释放
                            *(BYTE*)(anim + 52) = 1;   // 朝右
                        }
                        break;
                    case 2:  // case 2 分派
                    case 3:  // case 3 分派
                        {
                            int ox = (*(int(__thiscall**)(int))(*(int*)result + 120))(result);  // 调虚槽 +120：取坐标x
                            int mine = (*(int(__thiscall**)(int*))(*this_ + 120))(this_);  // 虚调用 vt+120（this_）转发(对象+缓冲)
                            int anim = (*(int(__thiscall**)(int*))(*this_ + 60))(this_);  // 虚调用 vt+60（this_）对象销毁/释放
                            *(BYTE*)(anim + 52) = (mine > ox) ? 0 : 1;  // 写字段 anim+52（bAuraState） ← (mine > ox) ? 0 : 1
                        }
                        break;
                    }
                }
            }
        }
    }
    return result;
}

// ------------------------------------------------------------
// 0x4E7440 vmt158 —— 攻击上下文设置（研究 P29 已引: sub_4B2970 拷贝/4A3450 默认）
// ------------------------------------------------------------
int IRDCollisionObject_vmt158(char* this_, int nArg2)  // 函数：攻击上下文设置（研究 P29 已引: sub_4B2970 拷贝/4A3450 默认）
{
    char* ctx = this_ + 388;                           // +388 攻击上下文
    if (nArg2 != 0)
        sub_4B2970(ctx, nArg2);  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
    else
        sub_4A3450(ctx);  // sub_4A3450 —— attackinfo 默认值（sub_4A3450 @0x4A3450，由 sub_4A3520 构造函数先行调用）：
    return (*(int(__thiscall**)(char*))(*(int*)this_ + 352))(this_);  // vt+352 联动
}

// ------------------------------------------------------------
// 0x4E7480 vmt12C —— 目标移除联动（命中列表清除 + 双向链表更新）
// ------------------------------------------------------------
int IRDCollisionObject_vmt12C(int* this_, int nArg2)  // 函数：目标移除联动（命中列表清除 + 双向链表更新）
{
    int pObj = nArg2;
    CNRDObject_vmt12C(this_, nArg2);                      // 基类行为（观察者通知族）
    if ((*(unsigned char(__thiscall**)(int, int))(*(int*)pObj + 40))(pObj, 1) != 0)  // 若 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        sub_4E6FD0(pObj);                                // 移动停止联动
    int v5;
    sub_4BE520(&v5, &nArg2);  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
    if (v5 != this_[136])                              // +544
        sub_4A3130(&v5, v5);
    sub_4BE520(&v5, &nArg2);  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
    if (v5 != this_[150])                              // +600
        sub_4A3130(&nArg2, v5);
    if (this_[143] == pObj)                              // +572 最后命中敌 = 目标则清
        this_[143] = 0;  // this+572〔最后命中敌记录〕
    if (this_[167] == pObj)                              // +668
        this_[167] = 0;  // this+668〔第二命中目标槽〕
    return 0;
}

// ------------------------------------------------------------
// 0x4E8080 vmt1C8 —— 命中目标列表追加（去重 + vt+464 回调）
// ------------------------------------------------------------
char IRDCollisionObject_vmt1C8(int* this_, int nArg2, char pszArg3)  // 函数：命中目标列表追加（去重 + vt+464 回调）
{
    int* begin = (int*)this_[83];                      // +332
    int* end = (int*)this_[84];                        // +336
    int* cur = begin;
    while (cur != end) {  // 循环直到 cur != end
        if (*cur == nArg2) break;
        ++cur;  // 计数自增 cur
    }
    if (cur == end) {                                  // 未命中过 → 追加
        sub_431230((int)(this_ + 82), &nArg2);            // vector 追加
        if (pszArg3 != 0)
            return (char)(*(int(__thiscall**)(int*, int))(*this_ + 464))(this_, nArg2);  // vt+464
    }
    return (char)(cur != end);
}

// ------------------------------------------------------------
// 0x4E7040 vmt1CC —— 命中目标列表移除
// ------------------------------------------------------------
int* IRDCollisionObject_vmt1CC(int* this_, int nArg2)  // 函数：命中目标列表移除
{
    int* begin = (int*)this_[83];
    int* end = (int*)this_[84];
    int* cur = begin;
    if (begin != end) {
        while (*cur != nArg2) {  // 循环直到 cur != nArg2
            ++cur;  // 计数自增 cur
            if (cur == end) return cur;
        }
        memmove(cur, cur + 1, 4 * ((this_[84] - (int)(cur + 1)) >> 2));  // 内存块搬移（重叠安全）
        this_[84] -= 4;
        (*(int(__thiscall**)(int*, int))(*this_ + 468))(this_, nArg2);  // vt+468 联动
    }
    return cur;
}

// ------------------------------------------------------------
// 0x4A2BB0 vmt270 —— ★ 攻击使能检查（动画率 + 帧检查）【会话 3 新分析】
// 条件: vt+608（攻击使能）非 0 且动画对象存在；
//   动画帧率 != -1 时同步；帧数非 0 且 帧率态 != 2 时返回 1（可攻击）。
//   IRDActiveObject 覆写追加 +7093 字节检查。
// ------------------------------------------------------------
int IRDCollisionObject_vmt270(int* this_)  // 函数：★ 攻击使能检查（动画率 + 帧检查）【会话 3 新分析】
{
    if ((*(unsigned char(__thiscall**)(int*))(*this_ + 608))(this_) == 0)  // 虚调用 vt+608（this_ 虚表槽）
        return 0;
    int* anim = (int*)this_[30];  // this+120〔动画对象〕
    if (anim == 0)
        return 0;
    if (anim[37] == -1)                                // +148
        sub_4938F0(anim);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    int v3 = anim[34];                                 // +136 帧数组
    if (v3 == 0)
        return 0;
    if ((anim[35] - v3) / 24 == 0)                     // 帧数 = (end-begin)/24
        return 0;
    int v4 = (*((BYTE*)this_ + 642) == 0)  // this+642〔攻击使能〕
        ? sub_4A2C40(this_)  // sub_4A2C40 —— 动画率状态查询
        : this_[161];                                  // +644
    return v4 != 2;                                    // 帧率态 2 = 冻结帧
}

// ------------------------------------------------------------
// 0x4A4570 vmt288 —— 写入 100（格挡/减伤基础值槽）
// ------------------------------------------------------------
int IRDCollisionObject_vmt288(int* pDwArg1, int nArg2)  // 函数：写入 100（格挡/减伤基础值槽）
{
    *pDwArg1 = 100;
    return 0;
}

// ------------------------------------------------------------
// ·0x4E7440 后族 / 0x4E5410 vmt14C 位置采样 / 0x4E8130 vmt234 位移同步
// / 0x4E4F20 vmt248 动作数据包 —— 已在头文件注释中索引;
// 完整逐行版见 work/decomp_core_vt.txt（对应 VA 段落），
// 本文档保留已在研究文档 20/21 全文定案的实现（表现壳/伤害流水线/命中判定几何）。
// ------------------------------------------------------------

// 0x4E5410 vmt14C —— 位置采样（每 100ms 节流，双缓冲）
int IRDCollisionObject_vmt14C(int* this_)  // 函数：位置采样（每 100ms 节流，双缓冲）
{
    // 开场: 若选项 86/87 未开则触发 88（镜头/记录选项）
    if ((*(unsigned char(__thiscall**)(int, int))(*(int*)dword_79C0B4 + 16))(dword_79C0B4, 86) != 1  // dword_79C0B4 —— 驱动设备 dword_79C0B4 vt+12
        && (*(unsigned char(__thiscall**)(int, int))(*(int*)dword_79C0B4 + 16))(dword_79C0B4, 87) != 1) {  // dword_79C0B4 —— 驱动设备 dword_79C0B4 vt+12
        (*(void(__thiscall**)(int, int))(*(int*)dword_79C0B4 + 16))(dword_79C0B4, 88);  // dword_79C0B4 —— 驱动设备 dword_79C0B4 vt+12
    }
    nullsub_3((void*)this_);
    int result;
    if (this_[148] == -1) {                            // +592 采样时刻
        int* v2 = this_ + 147;  // this+588〔位置采样时刻〕
        for (int i = 2; i != 0; --i) {
            *(v2 - 2) = (*(int(__thiscall**)(int*))(*this_ + 120))(this_);  // 虚调用 vt+120（this_）转发(对象+缓冲)
            result = sub_699000((PauseClock*)(this_ + 2));  // 【clock_now(clk)】
            *v2++ = result;
        }
    } else {
        int v5 = this_[148];  // this+592〔位置采样时刻(副本)〕
        result = sub_699000((PauseClock*)(this_ + 2));  // 【clock_now(clk)】
        if (result >= v5 + 100) {                      // 100ms 节流
            this_[145] = this_[146];                   // 移位: prev = hist
            this_[147] = v5;  // this+588〔位置采样时刻〕
            this_[146] = (*(int(__thiscall**)(int*))(*this_ + 120))(this_);  // 虚调用 vt+120（this_）转发(对象+缓冲)
            this_[148] = sub_699000((PauseClock*)(this_ + 2));  // 【clock_now(clk)】
        }
    }
    return result;
}
