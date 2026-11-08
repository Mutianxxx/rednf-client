// ============================================================
// 【40JP逆向源代码工程】include/arad/cnrd/CNRDObject.h
// 类: CNRDObject
// 主虚表: 0x006C3B7C   槽位数: 84
// 继承: CNRDObject -> CNRDObject -> KGameMessenger -> KMessenger
// 来源: RTTI 全表自动生成（data/rtti_hierarchy.txt + class_method_slots.txt）
// 说明: 虚表槽位为二进制实测地址；语义名来自历代精修层；字段见 L1 精修头文件
// ============================================================
#pragma once
#include "../../common/arad_types.h"

struct CNRDObject : KGameMessenger {
    // ---- 字段（L1 精修层摘录）----

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