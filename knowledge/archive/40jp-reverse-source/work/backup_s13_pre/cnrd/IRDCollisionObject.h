// ============================================================
// 【40JP逆向源代码工程】src/cnrd/IRDCollisionObject.h
// IRDCollisionObject —— 战斗/碰撞段（虚表 @ 0x006CC52C，167 槽）
// 命中链主战场: 命中盒 / 扫掠 / 表现壳 / 伤害流水线 / 特效 全在此段
//
// 槽位语义来源: 会话 3 批反编译 + 42 轮打击感研究（文档 20/21）双重证据
// ============================================================
#ifndef ARAD40JP_CNRD_IRDCOLLISIONOBJECT_H
#define ARAD40JP_CNRD_IRDCOLLISIONOBJECT_H

#include "CNRDObject.h"

struct IRDCollisionObject : CNRDObject
{
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

// ------------------------------------------------------------
// 本段槽位索引（含来源标注）:
//   0x4A4710  vmt0    析构 → 0x4A4590
//   0x4E73B0  vmtC    复活/出生重置（研究 P35 直证 sub_4E73B0）
//   0x4E7480  vmt12C  目标移除联动（命中列表抽除）
//   0x4E7440  vmt158  攻击上下文设置（sub_4B2970 拷贝 / sub_4A3450 默认）
//   0x4A0D50  vmt15C  取攻击信息 attackinfo 指针 (this+388)  ← 研究已定案
//   0x4A2DE0  vmt160  队列清空（双链表清理）
//   0x4A3900  vmt164  记录当前命中目标（研究已定案）
//   0x626610  vmt168  敌我关系判定（研究已定案）
//   0x4E5AC0  vmt170  条件 33 查询（研究已定案）
//   0x4A2D30  vmt180  无敌开关 setter 转发（研究 P35 直证）
//   0x66AA82  vmt184..1A4 纯虚（本类不实现）
//   0x4E57E0  vmt1A8  深度/缩放修正伤害输入（★ 新分析, 见 cpp）
//   0x4A0D90  vmt1AC / 1B0 / 1B4  取宽/高/深三字段 (this+316/320/324)
//   0x4A0DC0  vmt1B8 / 1BC / 1C0 / 1C4  包围盒边界计算族（中心±尺寸/2）
//   0x4E8080  vmt1C8  命中目标列表追加（重复检测 + sub_431230）
//   0x4E7040  vmt1CC  命中目标列表移除（memmove + vt+468 回调）
//   0x4E82B0  vmt1DC  ★ 本地扫掠（研究第 11 轮定案）
//   0x4E6570  vmt1E0  多命中盒测试（sub_4D6A80 主盒+附加盒）
//   0x4E65A0  vmt1E4  （研究: 扫掠族）
//   0x4E54D0  vmt1E8  ★ 3D AABB 重叠测试（四轴区间重叠; 见 cpp 逐行还原）
//   0x4E5560  vmt1EC  ★ 动画盒世界坐标重叠测试（sub_4918E0 四边界提取）【新分析】
//   0x00401A70 vmt1F0/1F8/1FC  空桩
//   0x4E5DC0  vmt200  ★★ 表现壳（hit stop 施加点 — 研究 §3 已全文定案）
//   0x4E48D0  vmt204  受击者最后受击记录（研究§1.1 定案）
//   0x4E85E0  vmt208  CRITHIT / 0x4E8770 vmt20C UNIONHIT（研究定案）
//   0x004B1090 vmt214 空桩
//   0x4E5CE0  vmt21C  命中语音（研究定案）
//   0x4D49E0  vmt220  播报层 HK_ATTACKED（研究定案）
//   0x4E7A80  vmt230  ★ 受击反应 setState（研究 §1.2 定案）
//   0x4E8130  vmt234  ★ UDP 包 type=5（位移同步）【会话 3 新分析】
//   0x4E4DE0  vmt244  ★ 位置化动作分发（相对偏移 → sub_4E4A50 执行 / a4 上下文暂改）
//   0x4E4F20  vmt248  ★ 动作数据包（48012 类型, 0x6E 字节结构 → sub_4E4A50）【新分析】
//   0x4E5F30  vmt24C  （研究: 硬直掷族）
//   0x4E5030  vmt250  （研究族）
//   0x4E5410  vmt14C  ★ 位置采样（100ms 节流双缓冲）【新分析】
//   0x4E6770  vmt274  ★★ 伤害流水线（研究 P14 九步全文定案）
//   0x4E88A0  vmt280  HITEFF（研究 P33 定案）
//   0x4E9760  vmt284  格挡特效（研究定案）
//   0x4A4570  vmt288  置 100 空实现（本文档实测: *a1=100）
//   0x4E5920  vmt290  朝向决策（依据宿主 +1316 模式）【新分析】
//   0x4E59C0  vmt294 / 0x4E5A20  vmt298 / 0x4A2460 vmt29C  研究族
//   0x4A2BB0  vmt270  ★ 动画使能检查（+608 条件 + 帧率检查）【新分析】
// ------------------------------------------------------------

#endif // ARAD40JP_CNRD_IRDCOLLISIONOBJECT_H
