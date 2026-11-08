// ============================================================
// 【40JP逆向源代码工程】src/cnrd/CNRDObject.h
// CNRDObject —— 全游戏对象基类（消息基座 KGameMessenger 之下的第一层）
// 虚表 @ 0x006C3B7C（84 槽），对象头由 IRDCollisionObject/IRDActiveObject 继承续写
//
// 来源: work/decomp_core_vt.txt（279 函数去重批反编译, 会话 3）
// 置信度: 槽位映射【已证实】；字段语义【已证实】为主，个别标注【推断】
// ============================================================
#ifndef ARAD40JP_CNRD_CNRDOBJECT_H
#define ARAD40JP_CNRD_CNRDOBJECT_H

#include "../nengine/time_system.h"   // PauseClock

// ------------------------------------------------------------
// 字段布局（按反编译实测偏移；前 16 字节为 KMessenger/KGameMessenger 头）
// ------------------------------------------------------------
struct CNRDObject
{
    void** vftable;             // +0x000
    int    field_004;           // +0x004  (vmt4 空桩占位)
    // 时钟族（PauseClock 28 字节）
    PauseClock clockMain;       // +0x008  主时钟 (vmtF0 已历时 = now − +0x30)
    PauseClock clockAux;        // +0x024  (vmt1C 周期检查用; vmtE8 归零用)
    PauseClock clockThird;      // +0x040  (vmtE4 主状态冻结用; vmtF0 基准域)
    // 状态与标志
    int    stateTimerVal;       // +0x030  主时钟起点值 (vmtF0: now − 此值)
    int    field_034;           // +0x034
    int    field_038;           // +0x038
    int    field_03C;           // +0x03C
    int    field_040;           // +0x040
    bool   condSet2;            // +0x052  vmt90/94/98: byte 状态位（受击动画黑白?）
    int    damageReaction;      // +0x058  vmt5C→stateTimerVal 双写对; 非 0 时 vmt5C 转发 vt+196
    // vmt20: 写 [+0x064..0x06C] 三元组（int3）
    int    triple[3];           // +0x064
    int*   observerVec;         // +0x070  vector<int*> 起始 (vmt68 元素访问)
    int*   observerVecEnd;      // +0x074
    // ...
    int    field_078;           // +0x078  派生类数据起 (vmt8C 螺旋寻位用 +120 处则不同)
    int    field_07C;           // +0x07C
    int    field_080;           // +0x080
    int    field_084;           // +0x084
    // ---- 通用状态机 ----
    int    mainState;           // +0x0C8(200) 主状态: 0自由/1硬直stuck/2冻结类 (vmtE4 a2)
    int    mainStateArg;        // +0x0CC(204) vmtE4 a3 (指针参数备份)
    int    mainStateStart;      // +0x0D0(208) vmtE4 起点时刻 (now + a4)
    // vmtD4/D8: 音效标签广播 (经 sub_65FE10)
    char   soundTagBuf;         // +0x0B0(176) 标签缓冲起点
    BYTE   soundEnable;         // +0x0AC(172) vmtD4 门: 0 则静默
    BYTE   animFreezeFlag;      // +0x0D4(212) vmtE4 冻结时写入动画解冻值 (sub_4910C0)
    // vmt1C 周期: +0x0C8(200)?  — vmt1C 用 +200/+204/+208 同址主状态 (周期任务)
    int    periodNow;           // +0x0C8  别名: vmt1C 的 now 阈值来源 (+51 = +204)
    // ---- 几何/行走 ----
    int    field_0F0;           // +0x0F0(240)
    BYTE   walkDir;             // +0x098(152) vmtB0/B4: 朝向 (1 或 0, 决定"前方"方向)
    int    animObj;             // +0x078(120) 动画对象指针 (vmtB0/74 等大量使用)
    // 动画对象内部: +52 状态字节 / +104 宿主回指 / +124 脏标记 / +196 更新标志
    BYTE   faceDir;             // +0x09C(156) vmt54/58 字节
    int    field_10C;           // +0x10C(268)
    // ---- vmt8C 寻路参数 ----
    int    searchParamA;        // 由调用方传入
    // ---- vmtCC 定时器链表 ----
    int*   timerListHead;       // +0x080(128)?  — vmtCC/D0 链表 (按 a2 时刻有序)
    int    timerCount;          // +0x084(132)
    BYTE   notifyFlag1;         // +0x174(372) vmt148 用? (dword_8F7C08/04 玩家判定)
    // ---- 渲染钩 (vmt148: 玩家脚下光圈) ----
    // 0x49A600: 当 this == 本地玩家或副玩家 时绘制 101 号资源 (150-255/400ms 三角波 alpha)
    int    renderState;         // +0x180(384)
    // ---- 危险区标记 ----
    BYTE   dangerFlag;          // +0x114(276) vmt140 清零
    // ---- vmt138 (受击/濒死表现) ----
    BYTE   killedFlag;          // +0x108(264)
    int    playerData;          // +0x118(280)
    // ---- 位置缓存 (vmt14C: 每 100ms 记录前两帧位置) ----
    int    lastPosSampleTime;   // +0x24C(588)
    int    prevPos;             // +0x244(580)
    int    posHistory[2];       // +0x248/0x24C  (v2-2, v2 双写对)
};

// ------------------------------------------------------------
// 虚方法（编号 = 虚表字节偏移，全部 thiscall）
// ------------------------------------------------------------
// 0x42A970   vmt0    标量删除析构 → 0x42A450 实析构
// 0x42A6A0   vmt8    与目标(a2)的方向/邻近计算 → sub_499240
// 0x498DE0   vmt28   条件查询: (a2 & this+96)==a2 位掩码测试（研究第 20 轮直证）
// 0x42A510   vmt20   设置坐标三元组 (this+100 = a2[0..2])
// 0x42A530   vmt24   取坐标三元组指针 (this+100)
// 0x42A540   vmt2C   取三元的 x
// 0x42A550   vmt30   取三元的 y
// 0x42A560   vmt34   取三元的 z
// 0x42A570   vmt38   取 y|z<<16 组合
// 0x42A580   vmt3C   取 this+112（默认共享组件/兜底观察者 —— 研究第 12 轮直证）
// 0x49A590   vmt48   ★ 全体时钟换域广播（含 sub_699070 —— 会话 1 新发现函数的调用者）
// 0x42A590   vmt4C   设置 this+116
// 0x42A5A0   vmt50   取 this+116
// 0x42A5B0   vmt54   设置 this+156 (byte)
// 0x42A5C0   vmt58   取 this+156 (byte)
// 0x42A5D0   vmt5C   设置伤害数值 + 转发 vt+196
// 0x445C30   vmt60   取 this+136
// 0x42ABC0   vmt64   转发 sub_42ABE0
// 0x42A930   vmt68   观察者数组元素访问
// 0x498E00   vmt6C   设置世界坐标三元组（三时钟检查 + 脏标记）
// 0x498EC0   vmt70   强制设置坐标三元组（不检查）
// 0x498EF0   vmt74   坐标设置（含动画对象）
// 0x42A5F0   vmt78   调用 vt+116(0)
// 0x42A600   vmt7C   调用 vt+116(1)
// 0x42A610   vmt80   调用 vt+116(2)
// 0x4C0380   vmt84   返回 1（空实现）
// 0x4D58E0   vmt88   （在 Collision 段覆写）
// 0x4993B0   vmt8C   ★ 螺旋式寻找空位（同心方环扫描，每环步差 a8）【新发现】
// 0x4C0380   vmt90?  （注：vmt90/94/98 = 0x498F00/40/60 条件字节）
// 0x498F00   vmt90   设置 this+52 条件字节（经动画对象 +52）
// 0x498F40   vmt94   同 vmt90 但不检查玩家
// 0x498F60   vmt98   取 this+52
// 0x42A640   vmt9C   与目标 x 距离绝对值
// 0x42A670   vmtA0   与目标 y 距离绝对值
// 0x499280   vmtA4   ★ 与目标的朝向角度（atan2 角度制 0..360）【新发现】
// 0x499330   vmtA8   与目标的俯仰角
// 0x4995F0   vmtAC   朝目标方向按距离比例取点
// 0x42A6E0   vmtB0   判断 a2 是否在"前方"（按 walkDir 朝向）
// 0x42A730   vmtB4   判断 a2 是否在"后方"
// 0x4996F0   vmtB8   动画对象 +16 值转状态 0/1（>5→1, <-5→0）
// 0x499730   vmtBC   动画对象 +20 值转状态 2/3/4
// 0x42A780   vmtC0   取 this+160（文档误标 Concurrency 名）
// 0x49C?      vmtC4   vmtC4 设置动画对象 (sub_699070 换域; sub_4938F0 重置)
// 0x42A7C0   vmtC8   取动画对象
// 0x49A7B0   vmtCC   ★ 定时器链表插入（按时刻有序 + sub_4926A0 复位）【新发现】
// 0x49A6B0   vmtD0   定时器链表移除
// 0x499110   vmtD4   音效标签播放（sub_65FE10 分发；szPassword 去重）
// 0x499170   vmtD8   音效 TAG 查询（sub_65DE30）
// 0x42A7D0   vmtDC   设置 this+172 (byte)
// 0x42A7E0   vmtE0   取 this+172 (byte)
// 0x49A320   vmtE4   ★★ 主状态写入器（进入 stuck 的时钟冻结编排 —— 42 轮研究主角）
// 0x42A7F0   vmtE8   通知 + 归零（vt+228(0,-1,0)）
// 0x42A810   vmtF0   已历时 = clock_now(+8) − this+52*4
// 0x42A830   vmtF4   取 this+51*4 (时长)
// 0x42A840   vmtF8   剩余 = vt+244 − vt+240
// 0x498FA0   vmtFC   周期任务存根槽（−1 重置 / 设置）
// 0x42A860   vmt100  取 this+54*4+i（4 元素数组）
// 0x499020   vmt104  列表任务开关
// 0x42A880   vmt108  取 this+232
// 0x499080   vmt110  透明度设置
// 0x42A890   vmt10C  取 this+236（文档误标名）
// 0x42A8A0   vmt114  取 this+244 是否非 0
// 0x42A8C0   vmt118  取 this+244 (float)
// 0x42A8D0   vmt11C  设置 4 元组 (248/252/256/260)
// 0x42A900   vmt120  取 this+248
// 0x42A910   vmt124  取 this+252
// 0x42A920   vmt13C  取 this+264
// 0x42A930   vmt140  危险区清零
// 0x4991D0   vmt44   观察者组件懒创建 (sub_50E730/50E8D0, 0x10 字节)
// 0x499B50   vmt138  ★ 濒死/最后一击表现（"LAST STRIKE" 系列; 研究 P35 的死亡链上游）【新发现】
// 0x0?       vmt134  是否本地玩家 (vt+304 == 0x8F7C04 —— 研究第 10 轮直证)
// 0x499AD0   vmt40   取观察者组件（懒创建 0x44 字节 sub_499960(120)）
// 0x40AFF0   vmt130  返回 0 空实现
// 0x499920?  vmt144  空桩（nullsub_2）
// 0x499A60   vmt148  ★ 玩家脚下光圈渲染钩（101 号资源 400ms 三角波）
// 0x5721A0   vmt10/14C  空桩
// 0x499370?  vmt18/14/1C 每帧表现主循环 A/B（子对象循环渲染）

#endif // ARAD40JP_CNRD_CNRDOBJECT_H
