// ============================================================
// 【40JP逆向源代码工程】include/arad/interface/IRDCollisionObject.h
// 类: IRDCollisionObject
// 主虚表: 0x006CC52C   槽位数: 167
// 继承: IRDCollisionObject -> IRDCollisionObject -> IRDCollisionObject -> CNRDObject -> CNRDObject -> KGameMessenger -> KMessenger
// 来源: RTTI 全表自动生成（data/rtti_hierarchy.txt + class_method_slots.txt）
// 说明: 虚表槽位为二进制实测地址；语义名来自历代精修层；字段见 L1 精修头文件
// ============================================================
#pragma once
#include "../../common/arad_types.h"

struct IRDCollisionObject : KGameMessenger {
    // ---- 字段（L1 精修层摘录）----

    // ---- 位置缓存（vmt14C: 每 100ms 记录）----
    // +0x244(580) prevX / +0x248(584) histX[0] / +0x24C(588) sampleTime
    // +0x3A0(592+) ...
    // ---- 命中目标列表（vector<object*>）----
    int*   hitTargetsBegin;      // +0x20C(524)   原文 *(this+83)*4
    int*   hitTargetsEnd;        // +0x210(528)   原文 *(this+84)*4
    // ---- 攻击上下文（sub_4B2970 拷贝 / sub_4A3450 默认）----
    // +0x184(388) 起, vmt150/158/15C 访问族
    // ---- 队列/链表（vmt160/234）----
    // +0x21C(540) vmt16C 返回基址链表
    // ---- 危险标记 ----
    BYTE   dangerFlag;           // +0x281(641)   vmt25C 写 / vmt260 读（无敌/危险窗口）
    BYTE   shortFlag2;           // +0x282(642)   vmt268 读（vmt270 参与判定）
    int    field_0x284;          // +0x284(644)   vmt26C
    int    field_0x288;          // vmt27C
    // +0x238(568) lastHitTime / +0x23C(572) lastHitEnemy（vmt204 写入, 击杀归属）
    // +0x230 vmt288: 置 100（格挡率?）
};