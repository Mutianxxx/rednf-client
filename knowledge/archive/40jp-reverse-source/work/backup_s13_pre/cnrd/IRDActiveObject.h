// ============================================================
// 【40JP逆向源代码工程】src/cnrd/IRDActiveObject.h
// IRDActiveObject —— 活动对象段（虚表 @ 0x006CC7CC，255 槽）
// 三层状态架构: 主状态(+200) / 受击反应态(+616+636 优先级) / 大状态(+6556)
// 42 轮研究已定案的命中主处理器(+0x200)/HP setter(+0x2D8)/扫掠(+0x1DC)等在此段
// ============================================================
#ifndef ARAD40JP_CNRD_IRDACTIVEOBJECT_H
#define ARAD40JP_CNRD_IRDACTIVEOBJECT_H

#include "IRDCollisionObject.h"

struct IRDActiveObject : IRDCollisionObject
{
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

// ------------------------------------------------------------
// 本会话（会话 3）新分析并还原的槽位:
//   0x4D49E0  vmt220  播报层 HK_ATTACKED —— 42 轮研究 §1.2 已点名, 本会话补精确转写:
//             cond: vt+44 == 273 (濒死?) → sub_426820(会话管理.vt+120().+104 的 +132, 3, a3)
//   0x4D4A20  vmt1F8  18 观察者通知(flag=0), 参数链 (a2,a3,a4,0,this+97*4)
//   0x4D4A80  vmt204  18 观察者 vt+140(受方命中) + 基类调用
//   0x4D4A20 族已由研究 §1.1 定案为"攻方观察者通知(轻量版)"
//   0x4A0C80  vmt2A0  取子对象 #a2 基址 (this + 1364*a2 + 676) —— 结构 sizeof 线索:
//             IRDActiveObject 内嵌 5 个 1364 字节子对象 (角色挂件/武器/披风...)
//   0x4A0F00  vmt2AC  返回 +6132 (属性块 —— 研究定案: HP 读处)
//   0x4A0F10  vmt2B0  返回 +6160
//   0x4A0F20  vmt2BC  读 +6296
//   0x4A0F30  vmt184  属性块 (vt+672(3)) 的首 DWORD
//   0x4A0F40  vmt2D4  读 +6552 (霸体字节)
//   0x4A0F50  vmt304  读 +6228+a2*4 (17 状态槽数组访问!)
//   0x4A0F70  vmt318  读 +6468+a2*4 (18 观察者槽数组访问!)
//   0x4A0F90  vmt330  转发 vt+808(a2, 0xFFFF, 0, a3)
//   0x4A0FB0  vmt334  写 +6740
//   0x4A0FC0  vmt1C8  vt+676(0) 联动 + 基类
//   0x4A1010  vmt348  取大状态 this+6556 (研究定案)
//   0x4A1020  vmt34C  返回内嵌动作子对象 this+6560 (研究定案)
//   0x4A1030  vmt350  写冻结标志 (研究 §1.2: vt+848)
//   0x4A1050  vmt354  冻结标志 != -1
//   0x4A1060  vmt358  读冻结标志 (vmt35C 的 %3 周期用!)
//   0x4A1070  vmt370  读 +6644
//   0x4A1080  vmt374  读 +6648
//   0x4A1090  vmt390  读 +6800
//   0x4A10A0  vmt3A8  读 +7092
//   0x4A10B0  vmt3AC  读 +7105
//   0x4A10C0  vmt3B8  读 +6832
//   0x4A10D0  vmt3DC  非霸体条件 (vt+724==0 && 状态3==0 && 状态8==0 —— 研究条件门)
//   0x4A1110  vmt3E4 / 0x4A1120 vmt3E8 / 0x4A1130 vmt3F0  复活计时器三件套
//   0x4D49A0  vmt3A4  场景 15/16 判定 → +7088 = 0/7
//   0x4D4D40  vmt2D8  ★★ HP setter（研究定案 [13] 锚点）
//   0x4D5140  vmt308  ★ 17 状态查询（研究定案 vt+776）
//   0x4D5170  vmt2D0  ★ 霸体 setter（研究定案 vt+720）
//   0x4D5200  vmt4    析构链
//   0x4D54E0  vmt10   初始化链
//   0x4D5650  vmt2C8 / 0x4D5700 vmt218 / 0x4D5750 vmt394 / 0x4D5820 vmt398
//   0x4D5890  vmt88  (Active 段覆写) / 0x4D58E0 vmt84 (共享研究段)
//   0x4D5900  vmt2DC / 0x4D5940 vmt39C / 0x4D5A50 vmt3A0 / 0x4D5A60 vmt288
//   0x4D5A90  vmt3E0 / 0x4D5AC0 vmt3EC / 0x4D5B00 vmt3F4 / 0x4D5B30 vmt3B4
//   0x4D5C10  vmt338 / 0x4D5C50 vmt140 / 0x4D5C90 vmt1D0 / 0x4D5CF0 vmt1D4
//   0x4D5D70  vmt344 / 0x4D6030 vmt300 / 0x4D6130 vmt3C0 / 0x4D62D0 vmt2C4
//   0x4D6450  vmt2CC / 0x4D65C0 vmt384 / 0x4D6690 vmt2C0 / 0x4D6910 vmt2F8
//   0x4D6970  vmtC   (Active 析构重置)
//   0x4D6A80  vmt1E0  ★ 多命中盒（研究定案） / 0x4D6B10 vmt2A4
//   0x4D6D90  vmt1F4  ★★ 攻方完整反应（研究 §8 定案） / 0x4D6E40 vmt12C
//   0x4D71B0  vmt200  ★★ 命中主处理器（研究 §2 全文定案）
//   0x4D7C60  vmt3F8 / 0x4D7F30 vmt3B0 / 0x4D8170 vmt3BC
//   0x4D9F20  vmt224  ★ 格挡时刻戳（研究定案）
//   0x4E4710  vmt1F4(Collision 段)  ★★ 攻方表现载荷（研究 §8 定案）
//   0x4E48D0  vmt204(Collision)  ★ 最后受击记录（研究定案）
//   0x58E550  vmt144  怪物子类族（0x58Bxxx 家族样板之一）
//   0x58FC30  vmt14C  同上
//   0x52D550..0x52E1C0 vmt2B4-368  子对象/装备状态族（0x52 区, 待专项）
// ------------------------------------------------------------

#endif // ARAD40JP_CNRD_IRDACTIVEOBJECT_H
