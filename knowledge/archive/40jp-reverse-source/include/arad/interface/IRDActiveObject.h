// ============================================================
// 【40JP逆向源代码工程】include/arad/interface/IRDActiveObject.h
// 类: IRDActiveObject
// 主虚表: 0x006CC7CC   槽位数: 255
// 继承: IRDActiveObject -> IRDActiveObject -> IRDActiveObject -> IRDActiveObject -> IRDCollisionObject -> IRDCollisionObject -> IRDCollisionObject -> CNRDObject -> CNRDObject -> KGameMessenger -> KMessenger
// 来源: RTTI 全表自动生成（data/rtti_hierarchy.txt + class_method_slots.txt）
// 说明: 虚表槽位为二进制实测地址；语义名来自历代精修层；字段见 L1 精修头文件
// ============================================================
#pragma once
#include "../../common/arad_types.h"

struct IRDActiveObject : KGameMessenger {
    // ---- 字段（L1 精修层摘录）----

    // ---- 三层状态（42 轮研究第 15 轮定案）----
    int    reactionState;        // +0x268(616) 受击反应态 3硬直/4击退/5击倒
    int    reactionPriority;     // +0x27C(636) 反应优先级（只升不降）
    int    bigState;             // +0x199C(6556) 角色大状态 ID (vt+348=0x4A1010)
    char   actionObject[0];      // +0x19A0(6560) 内嵌动作子对象（硬直时其时钟冻结）
    // ---- 异常状态 17 槽 ----
    // +0x1854(6228)..+0x18A8(6312) 42 轮研究定案
    // ---- 观察者 18 槽 ----
    // +0x1944(6468)..+0x198C(6540) 42 轮研究定案
    BYTE   superArmor;           // +0x1998(6552) 霸体（vt+720 setter）
    // ---- 阵营 ----
    int    faction;              // +0x220(544)（vt+168 敌我判定用 —— 研究定案）
    BYTE   hitBoxEnable;         // +0x281(641) 受击盒使能 = 无敌开关（研究 P35）
    BYTE   attackEnable;         // +0x282(642)
    int    damageInfo;           // +0x2C4(708)
    // ---- 复活链（研究 P35）----
    // vt+604: 附属物无敌广播; vt+632: 距上次受击毫秒（研究第 15 轮）
    BYTE   frozenFlag;           // +0x1A58(6744) 冻结标志 (vt+848 写 -1/0)
    int    reviveTimer;          // +0x1A60(6752)
    BYTE   sightFlags[2];        // +0x19EA/0x19EB(6634/6635) vmt214 双条件
    // ---- 渲染（本会话新分析）----
    int    renderFlag7088;       // +0x1BB0(7088)
    BYTE   flag7092;             // +0x1BB4(7092)
    BYTE   flag7093;             // +0x1BB5(7093) vmt270 覆写追加条件
    BYTE   flag7105;             // +0x1BC1(7105) vmt3AC
    int    field_6832;           // vmt3B8 读
};