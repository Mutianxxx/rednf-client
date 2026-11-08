// ============================================================
// 【40JP逆向源代码工程】src/game/rtti_core.cpp
// 模块: RTTI 类方法密集区（战斗对象核心 · 0x4A 区）
// 来源: work/dump_misc_a.txt  区块: 0x4A0000-0x4B0000（531 函数）
// 判定素材: work/decomp_core_vt.txt（核心三虚表 279 函数，含 RTTI 槽位名）
//
// 【L1 精修层】本文件已完成 rtti_core 段的 L1 精修（注释级），内容:
//   1) 与 src/cnrd/ 已精修函数的交叉引用（40 处，标 [已精修]，不重复正文）
//   2) RTTI 槽位名应用（55 处 IRDActiveObject__vmtXXX / IRDCollisionObject__vmtXXX）
//   3) 按功能块分区（17 段，见下方 SECTION 注记）
//   4) 30+ 行重点函数的开头解读注释（【推断】标记）
// 函数体逻辑与 L2 转写层逐字一致，未做任何改动。
//
// 本区的重要结构结论（本次精修推理）:
//   - 0x4A49B0 的 eh vector constructor iterator(this+676, 0x554, 4, ...) 直证
//     **IRDActiveObject 内嵌 4 个 1364 字节子对象**（0x554=1364），
//     与 vmt2A0（0x4A0C80: this+1364*a2+676）互证（docs/14 §4 记 5 个，本处实测 4）。
//   - 0x4AEDD0 写 +96 = 273（条件位集初值）—— 与 CNRDObject_vmt28（0x498DE0）的
//     273 掩码直证对应（docs/14 §2 交叉验证表闭环）。
//   - 0x4A5DC0 等哥布林族构造写 this+8600 第二 vftable，解释 (this+2150)=vftable 写法的由来。
//   - 0x4AF8B0 揭示两套 18 槽表（+6468 与 +7516）—— 当前值/基准值差分。
//   - 0x4AFEC0 七个全局字节（byte_9A0358..9A0460）按大状态 switch —— 本地玩家 UI 权限总闸。
//
// 函数数: 531（L1 精修覆盖 531；其中引用重复 40 / RTTI 命名 55 / 重点解读 331）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// SECTION 索引（按 VA 升序）
// ============================================================
//   0x4A0180 — 属性/渲染值同步族（对象子块: 挂点跟随 / 重力抛物线 / 时钟暂停桥 / 属性脏位同步）
//   0x4A0C80 — IRDActiveObject & IRDCollisionObject 槽位 getter 族（本批 40 处与 src/cnrd L1 精修重复）
//   0x4A1210 — clong/cfloat 属性块（构造 0x4A1210 / 析构 0x4A1670 / 62 槽解构 0x4A1F00）
//   0x4A1CA0 — 属性读取族（vmt188/18C/190/194/198/19C/1A0/1A4/2E0/2E4/2EC/2F4/38C —— 防篡改管线消费侧）
//   0x4A22E0 — 小结构解构族 + CNMagmaGhoul
//   0x4A2480 — 怪物属性块大拷贝（vmt29C）
//   0x4A2B30 — 关联容器/链表基础设施（refcount 封装 / 环形缓冲 / 红黑树模板实例 / std::string 辅助）
//   0x4A33F0 — std::map/std::set 红黑树模板实例族（MSVC _Tree）
//   0x4A3E40 — 红黑树容器构造/拷贝族 + 288 字节对象深拷贝
//   0x4A4430 — ★ IRDCollisionObject 构造/析构（0x4A4430 / 0x4A4590 / 0x4A4710）
//   0x4A49B0 — ★★ IRDActiveObject 构造/析构（0x4A49B0 / 0x4A4BD0 / 0x4A4E70）
//   0x4A4EA0 — ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
//   0x4A5380 — 怪物子类构造/析构批 A（CNFighterIllusion → CNGolemPlatany，0x4A5380-0x4A8010）
//   0x4A8040 — 怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Sharedo）
//   0x4A8350 — 怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350-0x4ABDC0）
//   0x4AEA30 — 环形缓冲/容器排空族（0x4AEA30-0x4AF010，CNMonster 家族的回收/重置）
//   0x4AF010 — ★★ IRDActiveObject 属性表导入/重算 + 本地玩家操作权限三位一体（0x4AF010-0x4AFEC0）
// ============================================================


// ============================================================
// SECTION 0x4A0180 — 属性/渲染值同步族（对象子块: 挂点跟随 / 重力抛物线 / 时钟暂停桥 / 属性脏位同步）
// ============================================================
// ------------------------------------------------------------
// 0x4A0180 sub_4A0180
// ------------------------------------------------------------
// 【解读】
//   【推断】属性同步主写器（IDA 原名 sub_4A0180）—— 单入口批量"脏位同步"。
//   a2 是 32 位脏位掩码，每 2 位控制一个属性字段的三种写模式:
//     00 → 向会话管理器(dword_8F8520.vt+88)请求服务端值回填（拉取）
//     01 → 写 0（清零）  10/11 → 从浅拷贝 this+4.. 复制（本地域）
//   字段布局: this+53 起 49 字节内串行排布；首段 a2&0x10 → 整块 49 字节拉取。
//   【待验证】这是防篡改属性管线的"批量提交侧"，具体字段名待属性块专项。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0180(uint32_t *this, unsigned int uArg2)  // 【属性/渲染值同步族（对象子块: 挂点跟随 / 重力抛物线 / 时钟暂停桥 / 属性脏…】
{
  uint32_t *pThis; // ebx
  float *pThis_35; // esi
  int v4; // eax
  char *pThis_353; // eax
  bool v6; // zf
  int v7; // eax
  int v8; // eax
  unsigned int v9; // eax
  unsigned int v10; // esi
  unsigned int v11; // eax
  unsigned int v12; // esi
  int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // esi
  char result; // al
  float *v17; // edi
  float *v18; // esi
  int v19; // ebx
  double v20; // st7
  double v21; // st5
  uint64_t v22; // rax
  int v23; // eax
  int i; // [esp+10h] [ebp-10h]
  char *pThis_352; // [esp+18h] [ebp-8h]
  int v27; // [esp+28h] [ebp+8h]

  pThis = this;
  if ( (uArg2 & 0x10) != 0 )
  {
    pThis_35 = (float *)((char *)this + 53);
    pThis_352 = (char *)this + 53;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 49);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
    goto LABEL_71;
  }
  v4 = (uArg2 >> 26) & 3;
  if ( v4 == 1 )
  {
    pThis_353 = (char *)this + 53;
    *(uint32_t *)((char *)this + 53) = 0;
LABEL_8:
    pThis_352 = pThis_353;
    goto LABEL_9;
  }
  v6 = v4 == 0;
  pThis_353 = (char *)this + 53;
  if ( !v6 )
  {
    *(uint32_t *)pThis_353 = *(this + 1);  // this+4 = pHostObj
    goto LABEL_8;
  }
  pThis_352 = (char *)this + 53;
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
LABEL_9:
  v7 = (uArg2 >> 28) & 3;
  if ( v7 == 1 )
  {
    *(uint32_t *)((char *)pThis + 57) = 0;
  }
  else if ( v7 != 0 )
  {
    *(uint32_t *)((char *)pThis + 57) = pThis[2];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 57, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  if ( uArg2 >> 30 == 1 )
  {
    *(uint32_t *)((char *)pThis + 61) = 0;  // this+61 就绪标志 A
  }
  else if ( uArg2 >> 30 != 0 )
  {
    *(uint32_t *)((char *)pThis + 61) = pThis[3];  // this+61 就绪标志 A
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 61, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v8 = (uArg2 >> 20) & 3;
  if ( v8 == 1 )
  {
    *(uint32_t *)((char *)pThis + 65) = 0;
  }
  else if ( v8 != 0 )
  {
    *(uint32_t *)((char *)pThis + 65) = pThis[4];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 65, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v9 = (((uArg2 >> 20) & 0x3F) >> 2) & 3;
  if ( v9 == 1 )
  {
    *(uint32_t *)((char *)pThis + 69) = 0;
  }
  else if ( v9 != 0 )
  {
    *(uint32_t *)((char *)pThis + 69) = pThis[5];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 69, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v10 = ((uArg2 >> 20) & 0x3F) >> 4;
  if ( v10 == 1 )
  {
    *(uint32_t *)((char *)pThis + 73) = 0;  // this+73 基类名字缓冲 SSO 首字节
  }
  else if ( v10 != 0 )
  {
    *(uint32_t *)((char *)pThis + 73) = pThis[6];  // this+73 基类名字缓冲 SSO 首字节
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 73, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  if ( (uint16_t)uArg2 >> 14 == 1 )
  {
    *(uint32_t *)((char *)pThis + 77) = 0;  // this+77 【推断】公会标志字节 B
  }
  else if ( (uint16_t)uArg2 >> 14 != 0 )
  {
    *(uint32_t *)((char *)pThis + 77) = pThis[7];  // this+77 【推断】公会标志字节 B
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 77, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v11 = (((uArg2 >> 14) & 0x3F) >> 2) & 3;
  if ( v11 == 1 )
  {
    *(uint32_t *)((char *)pThis + 81) = 0;
  }
  else if ( v11 != 0 )
  {
    *(uint32_t *)((char *)pThis + 81) = pThis[8];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 81, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v12 = ((uArg2 >> 14) & 0x3F) >> 4;
  if ( v12 == 1 )
  {
    *(uint32_t *)((char *)pThis + 85) = 0;
  }
  else if ( v12 != 0 )
  {
    *(uint32_t *)((char *)pThis + 85) = pThis[9];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 85, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v13 = BYTE1(uArg2) & 3;  // 调 取 32 位值的第 2 字节
  if ( v13 == 3 )
  {
    *(uint32_t *)((char *)pThis + 89) = -1;  // this+89 寿命上限门
  }
  else if ( v13 == 1 )
  {
    *(uint32_t *)((char *)pThis + 89) = 0;  // this+89 寿命上限门
  }
  else if ( (uArg2 & 0x300) != 0 )
  {
    *(uint32_t *)((char *)pThis + 89) = pThis[10];  // this+89 寿命上限门
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 89, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v14 = (((uArg2 >> 8) & 0x3F) >> 2) & 3;
  if ( v14 == 3 )
  {
    *(uint32_t *)((char *)pThis + 93) = -1;  // this+93 使能/暂停标志
  }
  else if ( v14 == 1 )
  {
    *(uint32_t *)((char *)pThis + 93) = 0;  // this+93 使能/暂停标志
  }
  else if ( v14 != 0 )
  {
    *(uint32_t *)((char *)pThis + 93) = pThis[11];  // this+93 使能/暂停标志
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 93, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  v15 = ((uArg2 >> 8) & 0x3F) >> 4;
  if ( v15 == 3 )
  {
    *(uint32_t *)((char *)pThis + 97) = -1;  // this+97 【推断】附加门字节
  }
  else if ( v15 == 1 )
  {
    *(uint32_t *)((char *)pThis + 97) = 0;  // this+97 【推断】附加门字节
  }
  else if ( v15 != 0 )
  {
    *(uint32_t *)((char *)pThis + 97) = pThis[12];  // this+97 【推断】附加门字节
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 97, 4);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  }
  pThis_35 = (float *)pThis_352;
  *((uint8_t *)pThis + 101) = (uArg2 >> 5) & 7;  // this+101 已播标志
LABEL_71:
  result = (uArg2 & 0x10) != 0;
  if ( (uArg2 & 0x10) != 0 )
  {
    qmemcpy(pThis + 1, pThis_35, 0x31u);  // 调 内存块拷贝(内联展开)
  }
  else
  {
    v17 = pThis_35 + 6;
    v18 = (float *)(pThis + 7);  // pThis+7〔uPathTerm(推断)〕
    for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
    {
      if ( *(v18 - 6) == *(v17 - 6) )
      {
        *(v18 - 3) = *(v17 - 3);
        *v18 = *v17;
        v18[3] = v17[3];  // v18[3] = 取 v17[3]
      }
      else
      {
        v19 = 500;
        v27 = 500;
        if ( pThis_352 != (char *)-24 && *((int *)v17 + 3) > 0 )
        {
          v19 = *((uint32_t *)v17 + 3);
          v27 = v19;
        }
        v20 = (double)(v19 * *(uint32_t *)v17) * 0.001 + *(v17 - 3);
        v21 = (double)v27 * v20 * 0.001 - ((v20 + *(v17 - 3)) * (double)v27 * 0.00050000002 + *(v17 - 6) - *(v18 - 6));
        v22 = (uint64_t)((v21 + v21) / ((double)(v19 * v19) * 0.000001));
        *(uint32_t *)v18 = v22;  // *v18 = v22
        *(v18 - 3) = v20 - (double)(v19 * (int)v22) * 0.001;
        if ( *(uint32_t *)v17 != 0 && (v23 = *((uint32_t *)v17 + 3)) != 0 )
          *((uint32_t *)v18 + 3) = v23;
        else
          *((uint32_t *)v18 + 3) = v19;
        pThis = this;
      }
      ++v18;
      ++v17;
    }
    result = pThis_352[48];
    *((uint8_t *)pThis + 52) = result;  // this+52 光环状态字节
  }
  return result;
}


// ------------------------------------------------------------
// 0x4A0550 sub_4A0550
// ------------------------------------------------------------
// 【解读】
//   【推断】重力/抛物线速度写入器。this+36 保存重力系数（int），
//   a2 = 施加系数；v5 = a2*grav 为负时取 v6 = sqrt(-2*v5)（v = sqrt(2gh)），
//   写动画对象 this+24（浮点）+ 脏标记 +196。a2<0 时取负根 —— 上行/下坠两向。
//   【待验证】用途可能是击退抛物线的初速计算。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0550(float *this, int nArg2)  // 实现：(待验证)用途可能是击退抛物线的初速计算
{
  int pThis_9; // eax
  int v5; // eax
  float v6; // [esp+Ch] [ebp+8h]

  pThis_9 = *((uint32_t *)this + 9);  // this+36 = 状态字
  if ( pThis_9 != 0 || nArg2 == 0 )  // 若 pThis_9 != 0 与/或 nArg2 == 0
  {
    v5 = nArg2 * pThis_9;
    if ( v5 <= 0 )
    {
      v6 = sqrt((double)(-2 * v5));  // 调 平方根
      if ( nArg2 < 0 )
        v6 = -v6;
      if ( *(uint32_t *)this != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)this + 308))(*(uint32_t *)this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
        && *(this + 6) != v6 )  // this+24〔nPageMax(推断)〕
      {
        *(this + 6) = v6;  // this+24〔nPageMax(推断)〕
        *((uint8_t *)this + 196) = 1;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4A05C0 sub_4A05C0
// ------------------------------------------------------------
// 【解读】
//   【推断】零点过冲补偿。this+36 为负且 a2 转正时，计算 -a2*v2*0.001
//   并交 sub_494F20(this, 2, v3) —— 与 vmt37C 的方向速率写入族同构。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A05C0(int this, int nArg2)  // 实现：并交 sub_494F20(this, 2, v3) —— 与 vmt37C 的方向速率写入族同构
{
  int fld_24; // eax
  float v3; // [esp+0h] [ebp-4h]

  fld_24 = *(uint32_t *)(this + 36);  // this+144 = pFrameList144
  if ( fld_24 < 0 && nArg2 >= 0 )  // 若 fld_24 < 0 与/或 nArg2 >= 0
  {
    v3 = (double)-(nArg2 * fld_24) * 0.001;  // fld_24=this+144 第 4 组·+1040 增量子倍率
    sub_494F20((float *)this, 2, v3);  // 调 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
  }
}



// ------------------------------------------------------------
// 0x4A0600 sub_4A0600
// ------------------------------------------------------------
// 【解读】
//   【推断】速率零交叉修正（vmt37C 的伴侣）。this[a2+7] 与浮点 this[a2+4] 异号时，
//   把 this[a2+10] 写为 浮点值×-1000/系数 —— 千分位换算 + 方向翻转。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0600(int *this, int pArg2)  // 实现：把 this[a2+10] 写为 浮点值×-1000/系数 —— 千分位换算 + 方向翻转
{
  double v2; // st6

  v2 = (double)*(this + pArg2 + 7);
  if ( v2 * *((float *)this + pArg2 + 4) < 0.0 )
    *(this + pArg2 + 10) = (uint64_t)(*((float *)this + pArg2 + 4) * -1000.0 / v2);
}



// ------------------------------------------------------------
// 0x4A0650 sub_4A0650
// ------------------------------------------------------------
// 【解读】
//   【推断】坐标轴分量读取（a2 = 0/1/2）。this+104 为"控制对象"指针，
//   存在且 +108 标志非 0 时走其 vt+40 接口，否则回退 sub_432F40(本地浮点)。
//   与 0x4A0790 的 v10/v17/v20 读法完全一致 —— 同一族。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0650(int this, int pArg2)  // 实现：与 0x4A0790 的 v10/v17/v20 读法完全一致 —— 同一族
{
  if ( *(uint32_t *)(this + 104) != 0 && *(uint8_t *)(this + 108) != 0 )  // this+104〔nTimerEnd(推断)〕等 2 字段
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 104) + 40))(*(uint32_t *)(this + 104), pArg2);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  else
    return sub_432F40(*(float *)(this + 4 * pArg2 + 4));  // 调 舍入取整（float → int）
}



// ------------------------------------------------------------
// 0x4A0680 sub_4A0680
// ------------------------------------------------------------
// 【解读】
//   【推断】暂停/继续总开关。this+172 为现状字节；变化时冻结/解冻 this+144 时钟
//   （sub_699030 / sub_698FE0）并向下游 this+104 对象转发 vt+56(a2) 广播。
//   被 CNRDObject_vmtE4（0x49A320）用作"子对象全冻"的施加点。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0680(int this, int nArg2)  // 实现：被 CNRDObject_vmtE4（0x49A320）用作子对象全冻的施加点
{
  int pThis_90; // ecx
  char result; // al
  int fld_68; // ecx

  if ( (uint8_t)nArg2 != *(uint8_t *)(this + 172) )  // this+688 = 表现/名字快照[2]
  {
    *(uint8_t *)(this + 172) = nArg2;  // this+688 = 表现/名字快照[2]
    pThis_90 = this + 144;  // this+144 第 4 组·+1040 增量子倍率
    if ( (uint8_t)nArg2 != 0 )
      result = sub_699030(pThis_90);  // 【clock_freeze(clk)】
    else
      result = sub_698FE0(pThis_90);  // 【clock_unfreeze(clk)】
    fld_68 = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
    if ( fld_68 != 0 )  // fld_68=this+104 nTimerEnd
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_68 + 56))(fld_68, nArg2);  // 调用虚函数（虚表槽 +56）【推断: y | z<<16 组合】
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A06D0 sub_4A06D0
// ------------------------------------------------------------
// 【解读】
//   【推断】绑定目标对象并记录相对偏移。this+128 = 目标指针；
//   this+132/136/140 = 本坐标 − 目标坐标（x/y/z 三条）。
//   与 0x4A0790（每帧用偏移重算世界坐标）配对 —— 是"挂点/跟随"机制。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A06D0(int this, int nArg2)  // 实现：与 0x4A0790（每帧用偏移重算世界坐标）配对 —— 是挂点/跟随机制
{
  int v3; // ebx
  uint64_t fld_8; // rax

  *(uint32_t *)(this + 128) = nArg2;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  if ( nArg2 != 0 )
  {
    *(uint32_t *)(this + 132) = (uint64_t)*(float *)(this + 4)  // this+132〔nAgeTicks〕等 3 字段
                            - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 调用虚函数（虚表槽 +124）
    fld_8 = (uint64_t)*(float *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 136) = fld_8 - v3;  // this+136〔nCtx136(推断)〕等 2 字段
    *(uint32_t *)(this + 140) = (uint64_t)*(float *)(this + 12)  // this+140〔nAdd140(推断)〕等 3 字段
                            - (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 128))(nArg2, HIDWORD(fld_8));  // 调用虚函数（虚表槽 +128）
  }
}



// ------------------------------------------------------------
// 0x4A0740 sub_4A0740
// ------------------------------------------------------------
// 【解读】
//   【推断】时间域变更深层递归（CNRDObject_vmt48 尾部调用的正是本函数）。
//   sub_699070(a2) 换域后，对 this+104 子对象再调其 vt+68 —— 递归到叶子。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0740(int *this, int nArg2)  // 实现：sub_699070(a2) 换域后，对 this+104 子对象再调其 vt+68 —— 递归到叶子
{
  int result; // eax

  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  result = *(this + 26);  // this+104〔nTimerEnd(推断)〕
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 68))(nArg2);  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
  return result;  // result=this+104 nTimerEnd
}



// ------------------------------------------------------------
// 0x4A0770 sub_4A0770
// ------------------------------------------------------------
// 【解读】
//   【推断】设置"宿主/所有者"指针并联动 sub_49FD20（动画归属重绑）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0770(uint32_t *this, int nArg2)  // 实现：(推断)设置宿主/所有者指针并联动 sub_49FD20（动画归属重绑）
{
  *this = nArg2;
  return sub_49FD20((int)this);  // 调 +200 状态位（sub_698F90 复位）
}



// ------------------------------------------------------------
// 0x4A0790 sub_4A0790
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 挂点对象每帧世界坐标刷新 —— 三段式:
//    ① 若 this+172（暂停标志）为 0: 用 this+32 目标坐标 + 偏移(33/34/35) 重算
//       this+4/+8/+12 浮点世界坐标，并置脏标记 this+124；
//    ② 对 3 个轴分量调 sub_49FD80（逐轴深化）；
//    ③ 当 this+26 子对象有效且 this+108 使能: 若 (this+28==2 且 this+116 非 0) 走
//       vt+532 快捷分支；否则逐轴 vt+40 读值 → vt+16 写入 + 置脏 → vt+8 提交。
//   条件分支里再读 this+116/this+28 决定二次写轴 —— 这是"挂件跟随 + 延迟提交"循环。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0790(uint32_t *this)  // 实现：条件分支里再读 this+116/this+28 决定二次写轴 —— 这是挂件跟随 + 延迟提交循环
{
  int pThis_24; // eax
  int fld_e32; // ecx
  double v4; // st7
  double v5; // st7
  double v6; // st7
  int pThis_1E; // edi
  uint32_t *pThis_2E; // ebx
  int fld_e26; // ecx
  int v10; // eax
  double v11; // st7
  int *fld_e262; // ebx
  int v13; // edx
  int v14; // ecx
  float *fld_e442; // eax
  int fld_e263; // ecx
  int pThis_2; // eax
  int fld_e264; // ecx
  int pThis_22; // ebx
  int pThis_1; // eax
  int fld_e265; // ecx
  int v22; // eax
  int fld_e266; // ecx
  int v24; // eax
  int v25; // ebx
  int fld_e267; // ecx
  int v27; // eax
  char v28; // al
  int pThis_3; // eax
  int pThis_6C; // eax
  int fld_e268; // ecx
  int pThis_6C2; // edi
  int pThis_12; // eax
  uint32_t v34[3]; // [esp+4h] [ebp-18h]
  int v35; // [esp+10h] [ebp-Ch]
  int fld_e33; // [esp+14h] [ebp-8h]
  float *fld_e44; // [esp+18h] [ebp-4h]

  if ( *((uint8_t *)this + 172) == 0 )  // this+172〔pAppendVecEnd(推断)〕
  {
    fld_e44 = (float *)(sub_699000((int)(this + 36)) - *(this + 44));  // 【clock_now(clk)】
    pThis_24 = sub_699000((int)(this + 36));  // 【clock_now(clk)】
    fld_e32 = *(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    *(this + 44) = pThis_24;  // this+176〔pAppendVecCap(推断)〕
    if ( fld_e32 != 0 )  // fld_e32=this+128 szStatusKeyBuf
    {
      fld_e33 = *(this + 33) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 120))(fld_e32);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v4 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
      *((float *)this + 1) = v4;  // this+4 = pHostObj
      fld_e33 = *(this + 34) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 124))(*(this + 32));  // 调用虚函数（虚表槽 +124）
      v5 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
      *((float *)this + 2) = v5;  // this+8 = 技能槽记录首字
      fld_e33 = *(this + 35) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 128))(*(this + 32));  // 调用虚函数（虚表槽 +128）
      v6 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
      *((float *)this + 3) = v6;  // this+12 = 技能槽记录次字
    }
    pThis_1E = 0;
    pThis_2E = this + 46;
    do
      *pThis_2E++ = sub_49FD80(pThis_1E++, fld_e44);  // 调 渲染参数（+40 → sub_432F40）
    while ( pThis_1E < 3 );
    if ( *(this + 26) != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕等 2 字段
    {
      if ( *(this + 28) == 2 && *((uint8_t *)this + 116) != 0 )  // this+112 = pHostComp
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(this + 30));  // this+120 = 动画对象指针
      }
      else
      {
        fld_e44 = (float *)(this + 1);  // this+4 = pHostObj
        pThis_1E = 0;
        fld_e33 = -4 - (uint32_t)this;
        do
        {
          fld_e26 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
          if ( fld_e26 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
            v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e26 + 40))(fld_e26, pThis_1E);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          else
            v10 = sub_432F40(*fld_e44);  // 调 舍入取整（float → int）
          v11 = *fld_e44;  // fld_e44=this+4 宿主对象
          fld_e262 = (int *)*(this + 26);  // this+104〔nTimerEnd(推断)〕
          v34[pThis_1E] = v10;
          v13 = *fld_e262;  // fld_e262=this+104 nTimerEnd
          v35 = (uint64_t)v11;
          v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 16))(fld_e262);  // 调用虚函数（虚表槽 +16）
          fld_e442 = fld_e44;  // fld_e44=this+4 宿主对象
          *(uint32_t *)((char *)fld_e44 + fld_e33 + v14) = v35;  // fld_e44=this+4 宿主对象
          ++pThis_1E;
          fld_e44 = fld_e442 + 1;  // fld_e44=this+4 宿主对象
        }
        while ( pThis_1E < 3 );
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 26) + 8))(*(this + 26));  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
        if ( *this != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 40))(*this, 1) != 0  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          && (*((uint8_t *)this + 116) == 0 || *(this + 28) == 0) )  // this+112 = pHostComp
        {
          fld_e263 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
          if ( fld_e263 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
            pThis_2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e263 + 40))(fld_e263, 1);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          else
            pThis_2 = sub_432F40(*((float *)this + 2));  // 调 舍入取整（float → int）
          fld_e264 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
          pThis_22 = pThis_2;
          if ( fld_e264 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
            pThis_1 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e264 + 40))(fld_e264, 0);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
          else
            pThis_1 = sub_432F40(*((float *)this + 1));  // 调 舍入取整（float → int）
          pThis_1E = (int)(this + 30);  // this+120 = 动画对象指针
          if ( (*(uint8_t (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)*this + 136))(pThis_1, pThis_22, this + 30) == 0  // 调用虚函数（虚表槽 +136）
            || ((fld_e265 = *(this + 26)) == 0 || *((uint8_t *)this + 108) == 0  // this+108〔nAdd108(推断)〕等 2 字段
              ? (v22 = sub_432F40(*((float *)this + 3)))  // 调 舍入取整（float → int）
              : (v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e265 + 40))(fld_e265, 2)),  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
                (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v22) == 0) )  // 调用虚函数（虚表槽 +132）
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(uint32_t *)pThis_1E);  // 调用虚函数（虚表槽 +532）【推断: 双标志门 + 转发 vt+968】
            *((uint8_t *)this + 116) = 1;  // this+116〔会话上下文〕
          }
        }
        if ( *((uint8_t *)this + 116) != 0 && *(this + 28) == 1 && *((uint8_t *)this + 124) == 0 )  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
        {
          pThis_1E = 0;  // pThis_1E=this+120 动画对象指针
          fld_e33 = 0;
          do
          {
            fld_e266 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
            if ( *((uint8_t *)this + pThis_1E + 117) != 0 )  // pThis_1E=this+120 动画对象指针
            {
              (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)fld_e266 + 36))(fld_e266, pThis_1E, v34[pThis_1E]);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
            }
            else
            {
              if ( fld_e266 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
                v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e266 + 40))(fld_e266, pThis_1E);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
              else
                v24 = sub_432F40(*((float *)this + pThis_1E + 1));  // 调 舍入取整（float → int）
              fld_e44 = (float *)v24;  // fld_e44=this+4 宿主对象
              if ( v34[pThis_1E] != v24 )  // pThis_1E=this+120 动画对象指针
              {
                while ( 1 )  // 无限循环
                {
                  v25 = v34[pThis_1E];  // pThis_1E=this+120 动画对象指针
                  v34[pThis_1E] = v25 >= (int)fld_e44 ? v25 - 1 : v25 + 1;  // pThis_1E=this+120 动画对象指针
                  fld_e267 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
                  if ( pThis_1E == 2 )  // pThis_1E=this+120 动画对象指针
                  {
                    if ( fld_e267 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
                    {
                      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e267 + 40))(fld_e267, 2);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v27);  // 调用虚函数（虚表槽 +132）
                    }
                    else
                    {
                      pThis_3 = sub_432F40(*((float *)this + 3));  // 调 舍入取整（float → int）
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, pThis_3);  // 调用虚函数（虚表槽 +132）
                    }
                  }
                  else
                  {
                    pThis_6C = fld_e267 != 0 && *((uint8_t *)this + 108) != 0  // this+108〔nAdd108(推断)〕
                        ? (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e267 + 40))(fld_e267, 1)  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
                        : sub_432F40(*((float *)this + 2));  // 调 舍入取整（float → int）
                    fld_e268 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
                    pThis_6C2 = pThis_6C;
                    if ( fld_e268 != 0 && *((uint8_t *)this + 108) != 0 )  // this+108〔nAdd108(推断)〕
                      pThis_12 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e268 + 40))(fld_e268, 0);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
                    else
                      pThis_12 = sub_432F40(*((float *)this + 1));  // 调 舍入取整（float → int）
                    v28 = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*this + 136))(*this, pThis_12, pThis_6C2, 0);  // 调用虚函数（虚表槽 +136）
                    pThis_1E = fld_e33;  // pThis_1E=this+120 动画对象指针
                  }
                  if ( v28 == 0 )
                    break;
                  if ( (float *)v34[pThis_1E] == fld_e44 )  // pThis_1E=this+120 动画对象指针
                    goto LABEL_68;
                }
                (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + 26) + 36))(*(this + 26), pThis_1E, v25);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
                v34[pThis_1E] = v25;  // pThis_1E=this+120 动画对象指针
                *((uint8_t *)this + pThis_1E + 117) = 1;  // pThis_1E=this+120 动画对象指针
              }
            }
LABEL_68:
            fld_e33 = ++pThis_1E;  // pThis_1E=this+120 动画对象指针
          }
          while ( pThis_1E < 3 );  // pThis_1E=this+120 动画对象指针
        }
        *((uint8_t *)this + 124) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
      }
    }
    if ( *(this + 50) != 0 && sub_699000((int)(this + 36)) >= (unsigned int)(*(this + 50) + *(this + 45)) )  // 【clock_now(clk)】
      sub_49FFC0(this, pThis_1E, (int)this, 0, 0);  // 调 播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
  }
}


// ------------------------------------------------------------
// 0x4A0B60 sub_4A0B60
// ------------------------------------------------------------
// 【解读】
//   【推断】控制对象换绑（0x4A0650/0x4A0790 族的核心）。
//   ① 先用旧对象 this+104 逐轴 vt+40 读出 v15/v14/v12 三个分量；
//   ② 旧对象非空时调 (**v9)(v9,1) 一次（推测为"释放/引用减"）；
//   ③ 换写 this+104 = a2；a2 非空 → 向新对象 vt+68(this+152) 传参、逐轴 vt+16 读入
//      本次坐标、清除短暂标志（+116/+117..+119/+120）并 vt+8 提交，返回 0；
//   ④ a2 == 0（解绑）→ 把先前读出的三分量回写本地浮点 + 置脏 —— 保留最后位置。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0B60(int this, int nArg2)  // 实现：④ a2 == 0（解绑）→ 把先前读出的三分量回写本地浮点 + 置脏 —— 保留最后位置
{
  int fld_68; // ecx
  int fld_4; // eax
  int fld_682; // ecx
  int fld_8; // eax
  int fld_683; // ecx
  int result; // eax
  int (/*thiscall*/ ***pThis_68)(uint32_t, int); // ecx
  int v11; // ebx
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+8h] [ebp-Ch]
  int fld_82; // [esp+Ch] [ebp-8h]
  int fld_42; // [esp+10h] [ebp-4h]
  float *pThis_4; // [esp+1Ch] [ebp+8h]

  fld_68 = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
  if ( fld_68 != 0 && *(uint8_t *)(this + 108) != 0 )  // this+108〔nAdd108(推断)〕
    fld_4 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_68 + 40))(fld_68, 0);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  else
    fld_4 = sub_432F40(*(float *)(this + 4));  // 调 舍入取整（float → int）
  fld_682 = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
  fld_42 = fld_4;
  if ( fld_682 != 0 && *(uint8_t *)(this + 108) != 0 )  // this+108〔nAdd108(推断)〕
    fld_8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_682 + 40))(fld_682, 1);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  else
    fld_8 = sub_432F40(*(float *)(this + 8));  // 调 舍入取整（float → int）
  fld_683 = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
  fld_82 = fld_8;
  if ( fld_683 != 0 && *(uint8_t *)(this + 108) != 0 )  // this+108〔nAdd108(推断)〕
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_683 + 40))(fld_683, 2);  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
  else
    result = sub_432F40(*(float *)(this + 12));  // 调 舍入取整（float → int）
  pThis_68 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 104);  // this+104 插值终点 Z
  v12 = result;
  if ( pThis_68 != nullptr )  // 若 pThis_68 有效（非空）
    result = (**pThis_68)(pThis_68, 1);  // 调 pThis_68 的虚函数（vt+0）
  *(uint32_t *)(this + 104) = nArg2;  // this+104〔nTimerEnd(推断)〕
  if ( nArg2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 68))(nArg2, *(uint32_t *)(this + 152));  // 调用虚函数（虚表槽 +68）【推断: 观察者组件懒创建（0x10 字节）】
    v11 = 0;
    pThis_4 = (float *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    do
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + v11);  // 调用虚函数（虚表槽 +16）
      *(uint8_t *)(this + 124) = 1;  // this+124〔pAuraAnim(推断)〕
      v11 += 4;
      *pThis_4++ = (float)v13;  // pThis_4=this+4 宿主对象
    }
    while ( v11 < 12 );
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 8))(nArg2);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
    *(uint8_t *)(this + 116) = 0;  // this+116〔会话上下文〕
    *(uint16_t *)(this + 117) = 0;
    *(uint8_t *)(this + 119) = 0;
    *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
    return 0;
  }
  else
  {
    *(float *)(this + 4) = (float)fld_42;  // this+4〔宿主对象〕等 2 字段
    *(float *)(this + 8) = (float)fld_82;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint8_t *)(this + 124) = 1;  // this+124〔pAuraAnim(推断)〕
    *(float *)(this + 12) = (float)v12;  // this+12〔nSkillRec12(推断)〕等 2 字段
  }
  return result;
}



// ============================================================
// SECTION 0x4A0C80 — IRDActiveObject & IRDCollisionObject 槽位 getter 族（本批 40 处与 src/cnrd L1 精修重复）
// ============================================================
// ------------------------------------------------------------
// 0x4A0C80 sub_4A0C80 [RTTI: IRDActiveObject__vmt2A0 · 槽位 IRDActiveObject+2A0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2A0 —— 子对象基址 getter（1364 字节步长，this+1364*a2+676）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0C80(void *this, int nArg2)  // 【IRDActiveObject & IRDCollisionObject 槽位 ge…】
{
  return (int)this + 1364 * nArg2 + 676;
}



// ------------------------------------------------------------
// 0x4A0CB0 sub_4A0CB0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinCommon 构造函数残留桩（写 vftable；a2&1 → free）。
//   IDA 符号里 RTTI 名在本文件缺失，按 vftable 归属推断为哥布林通用基类。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A0CB0(uint32_t *Block, char pszArg2)  // 实现：IDA 符号里 RTTI 名在本文件缺失，按 vftable 归属推断为哥布林通用基类
{
  *Block = &CNGoblinCommon::`vftable';  // vftable 复位
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A0CE0 sub_4A0CE0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMonsterFriendShip vftable 写入桩（友方怪物基类析构/构造残片）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0CE0(uint32_t *this)  // 实现：(推断)CNMonsterFriendShip vftable 写入桩（友方怪物基类析构/构造残片）
{
  *this = &CNMonsterFriendShip::`vftable';  // vftable 复位
}



// ------------------------------------------------------------
// 0x4A0CF0 sub_4A0CF0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek 构造（食尸鬼油商 Olrek）。
//   先调 sub_58E0E0 基类构造 → 写 vftable → sub_58E3B0 收尾。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A0CF0(uint32_t *this, char ArgList, int nArg3, char pszArg4)  // 实现：先调 sub_58E0E0 基类构造 → 写 vftable → sub_58E3B0 收尾
{
  sub_58E0E0((int)this, ArgList, nArg3, pszArg4);  // 调 CNGhoul 构造：调用 58DFE0 注册部件标签
  *this = &CNGhoulOilSellerOlrek::`vftable';  // vftable 复位
  sub_58E3B0(this);  // 【CNGhoulOilSellerOlrek__vmt51C】
  return this;
}



// ------------------------------------------------------------
// 0x4A0D70 sub_4A0D70 [RTTI: IRDCollisionObject__vmt174 · 槽位 IRDActiveObject+174,IRDCollisionObject+174]
// ------------------------------------------------------------
// 【解读】
//   【推断】写 this+608（vt+174 对偶槽）——攻击/动作资源句柄缓存。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0D70(uint32_t *this, int nArg2)  // 函数 sub_4A0D70：[RTTI IRDCollisionObject__vmt174 槽位 IRDActiveObject+174,IRDCol…
{
  *(this + 152) = nArg2;  // this+608〔nAttackGate〕
  return nArg2;
}



// ------------------------------------------------------------
// 0x4A0DC0 sub_4A0DC0 [RTTI: IRDCollisionObject__vmt1B8 · 槽位 IRDActiveObject+1B8,IRDCollisionObject+1B8] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1B8 —— 包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DC0(uint32_t *this)  // 实现：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - *(this + 79) / 2;  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
}



// ------------------------------------------------------------
// 0x4A0DE0 sub_4A0DE0 [RTTI: IRDCollisionObject__vmt1BC · 槽位 IRDActiveObject+1BC,IRDCollisionObject+1BC] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1BC [族级] —— 包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 "1B8/1BC/1C0/1C4 包围盒边界计算族" 一行覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DE0(uint32_t *this)  // 实现：包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 1B8/1BC/1C0/1C4 包围盒边界计算族 一行覆盖）
{
  return *(this + 79) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 440))(this);  // 调用虚函数（虚表槽 +440）【推断: [RTTI: IRDCollisionObject__vmt1B…】
}



// ------------------------------------------------------------
// 0x4A0E00 sub_4A0E00 [RTTI: IRDCollisionObject__vmt1C0 · 槽位 IRDActiveObject+1C0,IRDCollisionObject+1C0] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1C0 [族级] —— 包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E00(uint32_t *this)  // 实现：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - *(this + 80) / 2;  // 调用虚函数（虚表槽 +124）
}



// ------------------------------------------------------------
// 0x4A0E20 sub_4A0E20 [RTTI: IRDCollisionObject__vmt1C4 · 槽位 IRDActiveObject+1C4,IRDCollisionObject+1C4] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1C4 [族级] —— 包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E20(uint32_t *this)  // 实现：包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
{
  return *(this + 80) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 448))(this);  // 调用虚函数（虚表槽 +448）【推断: [RTTI: IRDCollisionObject__vmt1C…】
}



// ------------------------------------------------------------
// 0x4A0E40 sub_4A0E40 [RTTI: IRDCollisionObject__vmt22C · 槽位 IRDActiveObject+22C,IRDCollisionObject+22C]
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E40(uint8_t *this, char pszArg2)  // 函数 sub_4A0E40：[RTTI IRDCollisionObject__vmt22C 槽位 IRDActiveObject+22C,IRDCol…
{
  *(this + 612) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A0E70 sub_4A0E70 [RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActiveObject+254,IRDCollisionObject+254]
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E70(uint8_t *this, char pszArg2)  // 函数 sub_4A0E70：[RTTI IRDCollisionObject__vmt254 槽位 IRDActiveObject+254,IRDCol…
{
  *(this + 640) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A0EC0 sub_4A0EC0 [RTTI: IRDCollisionObject__vmt278 · 槽位 IRDActiveObject+278,IRDCollisionObject+278]
// ------------------------------------------------------------
// 【解读】
//   【推断】"距上次事件毫秒"读取器。this+568 为上次时刻（-1 = 无记录 → 返回 1e9）。
//   与 CNRDObject_vmtE4 的 +204/+208 时刻族同构（clockMain 域差值）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0EC0(uint32_t *this)  // 函数 sub_4A0EC0：[RTTI IRDCollisionObject__vmt278 槽位 IRDActiveObject+278,IRDCol…
{
  if ( *(this + 142) == -1 )  // this+568〔nAlarmVal〕
    return 1000000000;
  else
    return sub_699000((int)(this + 2)) - *(this + 142);  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4A0EF0 sub_4A0EF0 [RTTI: IRDCollisionObject__vmt27C · 槽位 IRDActiveObject+27C,IRDCollisionObject+27C]
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this+572（最后一次受击/命中记录槽，见 IRDCollisionObject.h +572 注释）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0EF0(uint32_t *this)  // 函数 sub_4A0EF0：[RTTI IRDCollisionObject__vmt27C 槽位 IRDActiveObject+27C,IRDCol…
{
  return *(this + 143);
}



// ------------------------------------------------------------
// 0x4A0F00 sub_4A0F00 [RTTI: IRDActiveObject__vmt2AC · 槽位 IRDActiveObject+2AC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2AC —— 属性块基址（this+6132，HP 读处）
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F00(char *this)  // 实现：属性块基址（this+6132，HP 读处）
{
  return this + 6132;  // this+6132〔nAttrBlock6132〕
}



// ------------------------------------------------------------
// 0x4A0F10 sub_4A0F10 [RTTI: IRDActiveObject__vmt2B0 · 槽位 IRDActiveObject+2B0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2B0 —— 附加块基址 this+6160
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F10(char *this)  // 实现：附加块基址 this+6160
{
  return this + 6160;  // 返回 this + 6160
}



// ------------------------------------------------------------
// 0x4A0F20 sub_4A0F20 [RTTI: IRDActiveObject__vmt2BC · 槽位 IRDActiveObject+2BC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2BC —— 读 +6296 槽
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F20(uint32_t *this)  // 实现：读 +6296 槽
{
  return *(this + 1574);
}



// ------------------------------------------------------------
// 0x4A0F30 sub_4A0F30 [RTTI: IRDActiveObject__vmt184 · 槽位 IRDActiveObject+184] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt184 —— 属性块（vt+672(3)）首 DWORD
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F30(void *this)  // 实现：属性块（vt+672(3)）首 DWORD
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
}



// ------------------------------------------------------------
// 0x4A0F40 sub_4A0F40 [RTTI: IRDActiveObject__vmt2D4 · 槽位 IRDActiveObject+2D4] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2D4 —— 读 +6552 霸体字节
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0F40(uint8_t *this)  // 实现：读 +6552 霸体字节
{
  return *(this + 6552);  // 返回 this + 26208 处指针
}



// ------------------------------------------------------------
// 0x4A0F50 sub_4A0F50 [RTTI: IRDActiveObject__vmt304 · 槽位 IRDActiveObject+304] [已精修] 见 src/cnrd/IRDActiveObject.h vmt304 —— 17 状态槽数组访问（+6228+4*a2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F50(uint32_t *this, int pArg2)  // 函数: ★ 17 异常状态槽访问（研究定案的 +6228 数组）
{
  return *(this + pArg2 + 1557);
}



// ------------------------------------------------------------
// 0x4A0F70 sub_4A0F70 [RTTI: IRDActiveObject__vmt318 · 槽位 IRDActiveObject+318] [已精修] 见 src/cnrd/IRDActiveObject.h vmt318 —— 18 观察者槽数组访问（+6468+4*a2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F70(uint32_t *this, int pArg2)  // 函数: ★ 18 观察者槽访问（研究定案的 +6468 数组）
{
  return *(this + pArg2 + 1617);
}



// ------------------------------------------------------------
// 0x4A0F90 sub_4A0F90 [RTTI: IRDActiveObject__vmt330 · 槽位 IRDActiveObject+330] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt330 —— 转发 vt+808(a2, 0xFFFF, 0, a3)
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F90(void *this, int nArg2, int nArg3)  // 函数: 转发 vt+808
{
  return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, int))(*(uint32_t *)this + 808))(this, nArg2, 0xFFFF, 0, nArg3);  // 调用虚函数（虚表槽 +808）【推断: ★ UDP 包 type=10「物品使用请求」】
}



// ------------------------------------------------------------
// 0x4A0FB0 sub_4A0FB0 [RTTI: IRDActiveObject__vmt334 · 槽位 IRDActiveObject+334] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt334 —— 写 +6740 字节
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0FB0(uint8_t *this, char pszArg2)  // 实现：写 +6740 字节
{
  *(this + 6740) = pszArg2;  // this+6740 【推断】落地/使能位
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A0FC0 sub_4A0FC0 [RTTI: IRDActiveObject__vmt1C8 · 槽位 IRDActiveObject+1C8] [已精修] 见 src/cnrd/IRDActiveObject.h vmt1C8 —— 命中列表追加（vt+676(0) 联动 + 基类）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FC0(void *this, int nArg2, char pszArg3)  // 实现：命中列表追加（vt+676(0) 联动 + 基类）
{
  int result; // eax

  result = sub_4E8080(nArg2, pszArg3);  // 调 命中目标列表追加（去重 + vt+464 回调）
  if ( pszArg3 != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  return result;
}



// ------------------------------------------------------------
// 0x4A0FF0 sub_4A0FF0 [RTTI: IRDActiveObject__vmt1CC · 槽位 IRDActiveObject+1CC] [已精修] 见 src/cnrd/IRDActiveObject.h vmt1CC —— 命中列表移除（IRDCollisionObject_vmt1CC 基类实现 + vt+676(0) 联动；0x4A0FC0=1C8 追加）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FF0(void *this, int nArg2)  // 实现：命中列表移除（IRDCollisionObject_vmt1CC 基类实现 + vt+676(0) 联动；0x4A0FC0=1C8 追加）
{
  sub_4E7040(nArg2);  // 调 命中目标列表移除
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
}



// ------------------------------------------------------------
// 0x4A1010 sub_4A1010 [RTTI: IRDActiveObject__vmt348 · 槽位 IRDActiveObject+348] [已精修] 见 src/cnrd/IRDActiveObject.h vmt348 —— 大状态 getter（this+6556）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1010(uint32_t *this)  // 实现：大状态 getter（this+6556）
{
  return *(this + 1639);  // this+6556 = 主状态镜像
}



// ------------------------------------------------------------
// 0x4A1020 sub_4A1020 [RTTI: IRDActiveObject__vmt34C · 槽位 IRDActiveObject+34C] [已精修] 见 src/cnrd/IRDActiveObject.h vmt34C —— 内嵌动作子对象 this+6560
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1020(char *this)  // 实现：内嵌动作子对象 this+6560
{
  return this + 6560;  // this+6560〔bActionObjHead〕
}



// ------------------------------------------------------------
// 0x4A1030 sub_4A1030 [RTTI: IRDActiveObject__vmt350 · 槽位 IRDActiveObject+350] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt350 —— 冻结标志写入（+6744，0→-1 / 非0→0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1030(uint32_t *this, char pszArg2)  // 实现：冻结标志写入（+6744，0→-1 / 非0→0）
{
  int result; // eax

  result = (pszArg2 != 0) - 1;
  *(this + 1686) = result;  // this+6744〔nFrozenFlag〕
  return result;
}



// ------------------------------------------------------------
// 0x4A1050 sub_4A1050 [RTTI: IRDActiveObject__vmt354 · 槽位 IRDActiveObject+354] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt354 —— 冻结标志 != -1 查询
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1050(uint32_t *this)  // 冻结标志 != -1 查询
{
  return *(this + 1686) != -1;  // this+6744〔nFrozenFlag〕
}



// ------------------------------------------------------------
// 0x4A10D0 sub_4A10D0 [RTTI: IRDActiveObject__vmt3DC · 槽位 IRDActiveObject+3DC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3DC —— 非霸体自由条件（vt+724==0 且状态3/8==0）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A10D0(void *this)  // 函数: 非霸体自由条件: vt+724==0 && 状态3==0 && 状态8==0（睡眠/眩晕不在）
{
  return (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 3) == 0  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 8) == 0;  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
}



// ------------------------------------------------------------
// 0x4A1110 sub_4A1110 [RTTI: IRDActiveObject__vmt3E4 · 槽位 IRDActiveObject+3E4] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3E4 —— 复活计时器清零（写 -1）
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1110(uint32_t *this)  // 实现：复活计时器清零（写 -1）
{
  *(this + 1774) = -1;  // this+7096 = 影身/伪装窗口起始时刻 clock_now
}



// ------------------------------------------------------------
// 0x4A1120 sub_4A1120 [RTTI: IRDActiveObject__vmt3E8 · 槽位 IRDActiveObject+3E8] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3E8 —— 复活计时中判定（!= -1）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1120(uint32_t *this)  // 复活计时中判定（!= -1）
{
  return *(this + 1774) != -1;  // this+7096 = 影身/伪装窗口起始时刻 clock_now
}



// ------------------------------------------------------------
// 0x4A1130 sub_4A1130 [RTTI: IRDActiveObject__vmt3F0 · 槽位 IRDActiveObject+3F0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3F0 —— 复活已计时（clockAux 域差值）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1130(uint32_t *this)  // 实现：复活已计时（clockAux 域差值）
{
  if ( *(this + 1774) == -1 )  // this+7096 = 影身/伪装窗口起始时刻 clock_now
    return 0;
  else
    return sub_699000((int)(this + 9)) - *(this + 1774);  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4A1150 sub_4A1150
// ------------------------------------------------------------
// 【解读】
//   【推断】返回 this+7232 —— IRDActiveObject 尾部另一内嵌子块基址。
//   【待验证】7232 与 +7520（0x4A1160）成对，疑为 288 字节/双份的装备模式缓存区。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1150(char *this)  // 实现：(待验证)7232 与 +7520（0x4A1160）成对，疑为 288 字节/双份的装备模式缓存区
{
  return this + 7232;  // 返回 this + 7232
}



// ------------------------------------------------------------
// 0x4A1160 sub_4A1160
// ------------------------------------------------------------
// 【解读】
//   【推断】返回 this+7520 —— 与 0x4A1150 成对的内嵌块基址（0x4A11D0 析构其内容）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1160(char *this)  // 实现：(推断)返回 this+7520 —— 与 0x4A1150 成对的内嵌块基址（0x4A11D0 析构其内容）
{
  return this + 7520;  // 返回 this + 7520
}



// ------------------------------------------------------------
// 0x4A1170 sub_4A1170
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this+7260（this+1815*4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1170(uint32_t *this)  // 实现：(推断)读 this+7260（this+1815*4）
{
  return *(this + 1815);
}



// ------------------------------------------------------------
// 0x4A1180 sub_4A1180
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this[2090]（+8360）指向对象的 +2 字节。2090*4 = +8360。
//   【待验证】8360 接近 IRDActiveObject 尺寸尾段，疑为"配件/宠物"子对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1180(uint32_t *this)  // 实现：(待验证)8360 接近 IRDActiveObject 尺寸尾段，疑为配件/宠物子对象
{
  int pPickInfo8360; // eax  | +0x20A8 → 拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）

  pPickInfo8360 = *(this + 2090);  // this+8360 = 拾取信息 7 字节对象指针
  if ( pPickInfo8360 != 0 )  // fld_e2090=this+8360 pPickInfo8360
    return *(uint8_t *)(pPickInfo8360 + 2);  // fld_e2090=this+8360 pPickInfo8360
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11A0 sub_4A11A0
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this[2090]（+8360）指向对象的 +3 DWORD —— 与 0x4A1180 同一对象的两字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A11A0(uint32_t *this)  // 实现：(推断)读 this[2090]（+8360）指向对象的 +3 DWORD —— 与 0x4A1180 同一对象的两字段
{
  int pPickInfo8360; // eax  | +0x20A8 → 拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）

  pPickInfo8360 = *(this + 2090);  // this+8360 = 拾取信息 7 字节对象指针
  if ( pPickInfo8360 != 0 )  // fld_e2090=this+8360 pPickInfo8360
    return *(uint32_t *)(pPickInfo8360 + 3);  // fld_e2090=this+8360 pPickInfo8360
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11C0 sub_4A11C0
// ------------------------------------------------------------
// 【解读】
//   【推断】恒等函数（返回入参本身）—— 接口桩/适配器。
// ------------------------------------------------------------
int16_t /*stdcall*/ sub_4A11C0(int16_t uArg1)  // [RTTI: IRDActiveObject__vmt3F0 · 槽位 IRDActiveObject+3F0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3F0 —— 复活已计时（clockAux 域差值）
{
  return uArg1;
}



// ------------------------------------------------------------
// 0x4A11D0 sub_4A11D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek 析构（调 0x4A1200 + 可选 free）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A11D0(void *Block, char pszArg2)  // 实现：(推断)CNGhoulOilSellerOlrek 析构（调 0x4A1200 + 可选 free）
{
  sub_4A1200();  // 调 (推断)CNGhoulOilSellerOlrek vftable 重置 + sub_58E0D0 基类析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A1200 sub_4A1200
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek vftable 重置 + sub_58E0D0 基类析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1200(uint32_t *this)  // 实现：(推断)CNGhoulOilSellerOlrek vftable 重置 + sub_58E0D0 基类析构
{
  *this = &CNGhoulOilSellerOlrek::`vftable';  // vftable 复位
  return sub_58E0D0();  // 调 CNGhoul 析构成员清理（4A50F0）
}



// ============================================================
// SECTION 0x4A1210 — clong/cfloat 属性块（构造 0x4A1210 / 析构 0x4A1670 / 62 槽解构 0x4A1F00）
// ============================================================
// ------------------------------------------------------------
// 0x4A1210 sub_4A1210
// ------------------------------------------------------------
// 【解读】
//   【推断】★ clong/cfloat 混合属性块的批量初始化序列（IDA 展开 100+ 次 sub_41A590）。
//   模式: 每对 (偏移, 值) —— 先写 clong 槽再写 cfloat 槽（1065353216 = 1.0f 的位模式）。
//   结构证据: +1/+18、+8/+46、+15/+74... 步长 14 字节 与 0x14 单位交错；
//   内嵌 4 元素循环（a1+57 起，步长 14）与 16 元素循环（a1+127 起）——
//   对应 0x4A1670 析构的 eh vector destructor iterator(...,0xEu,4/16,...)。
//   初值 1000 出现在 +204/+211/+218（千分基准）与 100 在 +239 —— 属性默认值表。
//   【待验证】这是 IRDActiveObject 属性块 (+6132 处, vt+672 返回) 的构造体（vmt10 初始化链）。
// ------------------------------------------------------------
int /*fastcall*/ sub_4A1210(uint32_t *pArg1, int nArg2)  // 函数 sub_4A1210：clong/cfloat 属性块（构造 0x4A1210 / 析构 0x4A1670 / 62 槽解构 0x4A1F00）
{
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  unsigned int v13; // edi
  int i; // ebx
  int v15; // edx
  unsigned int v16; // edi
  int j; // ebx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // edx
  int v27; // edx
  int v28; // edx
  int v29; // edx
  int v30; // edx
  int v31; // edx
  int v32; // edx
  int v33; // edx
  int v34; // edx
  int v35; // edx
  int v36; // edx
  int v37; // edx
  int v38; // edx
  int v39; // edx
  int v40; // edx
  int v41; // edx
  int v42; // edx
  int v43; // edx
  int v44; // edx
  int v45; // edx
  int v46; // edx
  int v47; // edx
  int v48; // edx
  int v49; // edx
  int v50; // edx
  int v51; // edx
  int v52; // edx
  int v53; // edx
  int v54; // edx

  *pArg1 = 0;
  sub_41A590((unsigned int)(pArg1 + 1), nArg2, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 18, v3, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 8), v4, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 46, v5, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 15), v6, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 74, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 22), v7, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 102, v8, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 29), v9, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 130, v10, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 36), v11, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 158, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v13 = (unsigned int)(pArg1 + 57);
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    sub_41A590(v13 - 56, v12, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(v13, v15, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v13 += 14;
  }
  v16 = (unsigned int)(pArg1 + 127);
  for ( j = 16; j != 0; --j )  // 循环：j 从 16 递减到 0
  {
    sub_41A590(v16 - 224, v12, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(v16, v18, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v16 += 14;
  }
  sub_41A590((unsigned int)(pArg1 + 183), v12, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 746, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 190), v19, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 774, v20, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 197), v21, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 802, v22, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 204), v23, 1000);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 830, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 211), v24, 1000);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 858, v25, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 218), v26, 1000);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 886, v27, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 225), v28, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 914, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 232), v29, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 942, v30, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 239), v31, 100);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 970, v32, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 246), v33, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 998, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 253), v34, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1026, v35, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 260), v36, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1054, v37, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 267), v38, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1082, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 274), v39, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1110, v40, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 281), v41, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1138, v42, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 288), v43, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1166, v44, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 295), v45, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1194, 0, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 302), v46, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1222, v47, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 309), 0, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1250, v48, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 316), v49, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1278, 0, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 323), v50, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1306, v51, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(pArg1 + 330), v52, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)pArg1 + 1334, v53, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590((unsigned int)(pArg1 + 337), v54, 0);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
}


// ------------------------------------------------------------
// 0x4A1670 sub_4A1670
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性块析构/重置（0x4A1210 的对偶）。逐槽 sub_41A630（解引用计数）
//   后重写 vftable 为 clong/cfloat，最后 `eh vector destructor iterator` 清理 4 元素与
//   16 元素两个内嵌数组 —— 数组元素大小 0xE(14) 字节，与 0x4A1210 的步长直证一致。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1670(uint32_t *this)  // 实现：16 元素两个内嵌数组 —— 数组元素大小 0xE(14) 字节，与 0x4A1210 的步长直证一致
{
  uint32_t *pThis_1; // edi
  int v3; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));  // this+4 = pHostObj
  *pThis_1 = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 18);  // this+18〔bDragChild〕
  *(uint32_t *)((char *)this + 18) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 8));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 8) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 46);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 46) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 15));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 15) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 74);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 74) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 22));  // this+88 = pFxObjB
  *(this + 22) = &clong::`vftable';  // this+88 = pFxObjB
  sub_41A630((unsigned int)this + 102);  // this+102〔bFlashClearB〕
  *(uint32_t *)((char *)this + 102) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 29));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 29) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 130);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 130) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 36));  // this+144 = pFrameList144
  *(this + 36) = &clong::`vftable';  // this+144 = pFrameList144
  sub_41A630((unsigned int)this + 158);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 158) = &cfloat::`vftable';  // vftable 复位
  `eh vector constructor iterator'(this + 43, 0xEu, 4, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  `eh vector constructor iterator'(this + 57, 0xEu, 4, sub_432CD0, sub_432D10);  // cfloat 构造
  `eh vector constructor iterator'(this + 71, 0xEu, 16, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  `eh vector constructor iterator'(this + 127, 0xEu, 16, sub_432CD0, sub_432D10);  // cfloat 构造
  sub_41A630((unsigned int)(this + 183));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 183) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 746);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 746) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 190));  // this+190〔bFlag190〕
  *(this + 190) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 774);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 774) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 197));  // this+197〔field_00C5〕
  *(this + 197) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 802);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 802) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 204));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 204) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 830);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 830) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 211));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 211) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 858);  // this+858〔fSpeed858〕
  *(uint32_t *)((char *)this + 858) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 218));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 218) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 886);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 886) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 225));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 225) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 914);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 914) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 232));  // this+232〔bSyncFlag〕
  *(this + 232) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 942);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 942) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 239));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 239) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 970);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 970) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 246));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 246) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 998);  // this+998〔nTargetZ998〕
  *(uint32_t *)((char *)this + 998) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 253));  // this+253〔field_00FD〕
  *(this + 253) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1026);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1026) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 260));  // this+260〔nQuad4〕
  *(this + 260) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1054);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1054) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 267));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 267) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1082);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1082) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 274));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 274) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1110);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1110) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 281));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 281) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1138);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1138) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 288));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 288) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1166);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1166) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 295));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 295) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1194);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1194) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 302));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 302) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1222);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1222) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 309));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 309) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1250);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1250) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 316));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 316) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 1278);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1278) = &cfloat::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 323));  // this+1292 = 动画行表基址
  *(this + 323) = &cfloat::`vftable';  // this+1292 = 动画行表基址
  sub_41A630((unsigned int)this + 1306);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1306) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 330));  // this+1320 = 动画件已装配门
  *(this + 330) = &clong::`vftable';  // this+1320 = 动画件已装配门
  sub_41A630((unsigned int)this + 1334);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 1334) = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)(this + 337));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 337) = &clong::`vftable';  // vftable 复位
  sub_4A1210(this, v3);  // 调 clong/cfloat 属性块（构造 0x4A1210 / 析构 0x4A1670 / 62 槽解构 0x4A1F00…
}


// ------------------------------------------------------------
// 0x4A1C30 sub_4A1C30
// ------------------------------------------------------------
// 【解读】
//   【推断】双 clong 小构造（设 vftable + 初值 -1）—— 与 0x4A1CA0 同址族，
//   疑为"HP 当前值/上限值"对（vmt188 读的就是 +60/+74 的这对）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A1C30(uint32_t *this)  // 实现：疑为HP 当前值/上限值对（vmt188 读的就是 +60/+74 的这对）
{
  int v2; // edx
  int v3; // edx

  sub_41A630((unsigned int)this);  // 调 防篡改字段读校验（crypt 逆运算链）
  *this = &clong::`vftable';  // vftable 复位
  sub_41A630((unsigned int)this + 14);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 14) = &clong::`vftable';  // vftable 复位
  sub_41A590((unsigned int)this, v2, -1);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 14, v3, -1);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ============================================================
// SECTION 0x4A1CA0 — 属性读取族（vmt188/18C/190/194/198/19C/1A0/1A4/2E0/2E4/2EC/2F4/38C —— 防篡改管线消费侧）
// ============================================================
// ------------------------------------------------------------
// 0x4A1CA0 sub_4A1CA0 [RTTI: IRDActiveObject__vmt188 · 槽位 IRDActiveObject+188] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt188 —— HP 类属性读取（属性块 +60 防篡读 × 浮点壳 +74）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1CA0(void *this)  // 【属性读取族（vmt188/18C/190/194/198/19C/1A0/1A4/2…】
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 60);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 74)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1CE0 sub_4A1CE0 [RTTI: IRDActiveObject__vmt18C · 槽位 IRDActiveObject+18C] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt18C —— MP 类属性读取（+1012 × 浮点壳 +1026）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1CE0(void *this)  // 函数: MP 类属性: +1012 × 浮点壳(+1026)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 1012);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 1026)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1D20 sub_4A1D20 [RTTI: IRDActiveObject__vmt190 · 槽位 IRDActiveObject+190] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt190 —— 整数属性读取（+1306）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D20(void *this)  // 实现：整数属性读取（+1306）
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  return sub_41A5E0(pThis_2A0 + 1306);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1D40 sub_4A1D40 [RTTI: IRDActiveObject__vmt194 · 槽位 IRDActiveObject+194] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt194 —— 整数属性读取（+1124）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D40(void *this)  // 实现：整数属性读取（+1124）
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  return sub_41A5E0(pThis_2A0 + 1124);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1D60 sub_4A1D60 [RTTI: IRDActiveObject__vmt198 · 槽位 IRDActiveObject+198]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +116 防篡读 × 浮点壳 +130 —— 与 0x4A1CA0/0x4A1CE0 同一族（vmt198）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1D60(void *this)  // 函数 sub_4A1D60：[RTTI IRDActiveObject__vmt198 槽位 IRDActiveObject+198]
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 116);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 130)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1DA0 sub_4A1DA0 [RTTI: IRDActiveObject__vmt19C · 槽位 IRDActiveObject+19C]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1068 × 浮点壳 +1082（vmt19C 族 —— 与 MP 族 +1012/+1026 相隔 56B）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1DA0(void *this)  // 函数 sub_4A1DA0：[RTTI IRDActiveObject__vmt19C 槽位 IRDActiveObject+19C]
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 1068);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 1082)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1DE0 sub_4A1DE0 [RTTI: IRDActiveObject__vmt1A0 · 槽位 IRDActiveObject+1A0]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1334 整数读（vmt1A0）。vmt188 族步长 56 字节的规律: 60/116/1012/1068。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1DE0(void *this)  // 函数 sub_4A1DE0：[RTTI IRDActiveObject__vmt1A0 槽位 IRDActiveObject+1A0]
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  return sub_41A5E0(pThis_2A0 + 1334);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1E00 sub_4A1E00 [RTTI: IRDActiveObject__vmt1A4 · 槽位 IRDActiveObject+1A4]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1166 整数读（vmt1A4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E00(void *this)  // 函数 sub_4A1E00：[RTTI IRDActiveObject__vmt1A4 槽位 IRDActiveObject+1A4]
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  return sub_41A5E0(pThis_2A0 + 1166);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1E20 sub_4A1E20 [RTTI: IRDActiveObject__vmt2E0 · 槽位 IRDActiveObject+2E0] [已精修] 见 src/cnrd/IRDActiveObject.h vmt2E0 —— 属性块首值（GetHP 族，此处索引）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E20(void *this)  // 实现：属性块首值（GetHP 族，此处索引）
{
  return sub_41A5E0((unsigned int)this + 6132);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1E30 sub_4A1E30 [RTTI: IRDActiveObject__vmt2E4 · 槽位 IRDActiveObject+2E4] [已精修] 见 src/cnrd/IRDActiveObject.h vmt2E4 —— 属性块 +4 浮点壳（GetHP 族）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1E30(void *this)  // 实现：属性块 +4 浮点壳（GetHP 族）
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 4);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 18)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1E70 sub_4A1E70 [RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObject+2EC]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +6146 防篡写封装的 setter（a4 非 0 时同时把 +6604 置 -1 使缓存失效）。
// ------------------------------------------------------------
char /*fastcall*/ sub_4A1E70(int pArg1, int nArg2, int nArg3, char pszArg4)  // 函数 sub_4A1E70：[RTTI IRDActiveObject__vmt2EC 槽位 IRDActiveObject+2EC]
{
  char result; // al

  sub_41A590(pArg1 + 6146, nArg2, nArg3);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  result = pszArg4;
  if ( pszArg4 != 0 )
    *(uint32_t *)(pArg1 + 6604) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4A1EB0 sub_4A1EB0 [RTTI: IRDActiveObject__vmt2F4 · 槽位 IRDActiveObject+2F4]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +32 × 浮点壳 +46（vmt2F4）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1EB0(void *this)  // 函数 sub_4A1EB0：[RTTI IRDActiveObject__vmt2F4 槽位 IRDActiveObject+2F4]
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v3 = sub_41A5E0(pThis_2A0 + 32);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 46)) * (double)v3);  // 调 防篡读壳（槽值转 float）
}



// ------------------------------------------------------------
// 0x4A1EF0 sub_4A1EF0 [RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveObject+38C]
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this+7028 的 clong（vmt38C）—— 由 0x4A49B0 构造时以 sub_41A630+clong vftable 初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1EF0(void *this)  // 函数 sub_4A1EF0：[RTTI IRDActiveObject__vmt38C 槽位 IRDActiveObject+38C]
{
  return sub_41A5E0((unsigned int)this + 7028);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4A1F00 sub_4A1F00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性块 62 槽全解构（sub_41A580 = clong/cfloat 析构单槽）。
//   顺序 = 0x4A1670 构造的逆序，含 4/16 元素两个 eh vector 数组 ——
//   这是 0x4A49B0（IRDActiveObject 构造）注册的析构回调（eh vector constructor iterator 的第 5 参）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1F00(uint32_t *this)  // 实现：这是 0x4A49B0（IRDActiveObject 构造）注册的析构回调（eh vector constructor itera…
{
  sub_41A580(this + 337);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1334));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 330);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1306));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 323);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1278));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 316);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1250));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 309);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1222));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 302);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1194));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 295);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1166));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 288);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1138));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 281);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1110));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 274);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1082));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 267);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1054));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 260);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 1026));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 253);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 998));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 246);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 970));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 239);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 942));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 232);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 914));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 225);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 886));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 218);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 858));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 211);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 830));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 204);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 802));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 197);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 774));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 190);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 746));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 183);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'(this + 127, 0xEu, 16, sub_432D10);  // 调 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递
  `eh vector destructor iterator'(this + 71, 0xEu, 16, sub_432D10);  // this+71〔bMoveType〕
  `eh vector destructor iterator'(this + 57, 0xEu, 4, sub_432D10);  // 调 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递
  `eh vector destructor iterator'(this + 43, 0xEu, 4, sub_432D10);  // 调 转发 → ·sub_41A580 挂 crypt4byte::vftable 并递
  sub_41A580((uint32_t *)((char *)this + 158));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 36);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 130));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 29);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 102));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 22);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 74));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 15);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 46));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 8);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 18));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 1);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ============================================================
// SECTION 0x4A22E0 — 小结构解构族 + CNMagmaGhoul
// ============================================================
// ------------------------------------------------------------
// 0x4A22E0 sub_4A22E0
// ------------------------------------------------------------
// 【解读】
//   【推断】双槽解构（+14 与 +0）—— 小块的 clong 对清理。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A22E0(uint32_t *this)  // 【小结构解构族 + CNMagmaGhoul】
{
  sub_41A580((uint32_t *)((char *)this + 14));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x4A2330 sub_4A2330
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMagmaGhoul（熔岩食尸鬼）构造。基类 sub_58DFE0 → vftable → 内嵌块初始化。
//   新发现字段: +8632 标志字节、+8628 IObject vftable、+8636 int、+8640 字节 =1。
//   RTTI 名（vftable 直证）: CNMagmaGhoul。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2330(int this, char ArgList, int nArg3, char pszArg4)  // 实现：RTTI 名（vftable 直证）: CNMagmaGhoul
{
  sub_58DFE0((uint8_t *)this, ArgList, nArg3, pszArg4);  // 调 R_GHOUL 部件标签注册：R_GHOUL/R_GHOUL_ATK/R_GHOUL_DIE/R_GHOUL_DMG（4A4…
  *(uint32_t *)this = &CNMagmaGhoul::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8628) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8636) = 0;  // this+8636〔pDollTarget(推断)〕
  *(uint8_t *)(this + 8640) = 1;  // this+8640〔uCastSlot8640(推断)〕
  *(uint8_t *)(this + 8642) = 0;  // this+8642〔bAI8642〕
  *(uint8_t *)(this + 8641) = 0;  // this+8641〔bSwingGate8641(推断)〕
  *(uint32_t *)(this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  sub_58C6B0(this);  // 【CNMagmaGhoul__vmt4A8】
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A23D0 sub_4A23D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMagmaGhoul 析构（调 0x4A2400 + 可选 free）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A23D0(void *Block, char pszArg2)  // 实现：(推断)CNMagmaGhoul 析构（调 0x4A2400 + 可选 free）
{
  sub_4A2400();  // 调 注意 +8628（2157*4）处挂了 nengine::IObject 子对象 —— 怪物类的通用附属组件
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A2400 sub_4A2400
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMagmaGhoul vftable 复位 + nengine::IObject 子对象复位 + sub_58E0D0 基类析构。
//   注意 +8628（2157*4）处挂了 nengine::IObject 子对象 —— 怪物类的通用附属组件。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2400(uint32_t *this)  // 实现：注意 +8628（2157*4）处挂了 nengine::IObject 子对象 —— 怪物类的通用附属组件
{
  *this = &CNMagmaGhoul::`vftable';  // vftable 复位
  nullsub_3(this);
  *(this + 2157) = &nengine::IObject::`vftable';  // this+8628 = 指挥计时戳
  *((uint8_t *)this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  return sub_58E0D0(this);  // 调 CNGhoul 析构成员清理（4A50F0）
}



// ------------------------------------------------------------
// 0x4A2460 sub_4A2460 [RTTI: IRDActiveObject__vmt29C · 槽位 IRDActiveObject+29C] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt29C —— 研究族槽位（0x4A2480 转发壳）
// ------------------------------------------------------------
int /*stdcall*/ sub_4A2460(int nArg1, int nArg2)  // 实现：研究族槽位（0x4A2480 转发壳）
{
  return sub_4A2480(nArg2);  // 【怪物属性块大拷贝（vmt29C）】
}



// ============================================================
// SECTION 0x4A2480 — 怪物属性块大拷贝（vmt29C）
// ============================================================
// ------------------------------------------------------------
// 0x4A2480 sub_4A2480
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 怪物属性块大拷贝（vmt29C 槽的实现，0x4A2460 是它的 stdcall 壳）。
//   逐字段 memcpy 式搬运 a2 → this（偏移+4 起），含 26+26 DWORD 的两段连续区 ——
//   对应 sub_58DFE0 族构造里的属性表初始化。IDA 展开 115 行。
//   【待验证】a2 来源（疑为 protocol/regen 表的静态实例）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A2480(char *this, char *pszArg2)  // 【怪物属性块大拷贝（vmt29C）】
{
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int v17; // eax
  int v18; // edx
  int v19; // edx
  int v20; // ebx
  int v21; // eax
  int v22; // edx
  bool v23; // zf
  int v24; // eax
  int v25; // edx
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // edx
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // edx
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // eax
  int v49; // edx
  int v50; // edx
  int v51; // eax
  int v52; // edx
  int v53; // eax
  int v54; // edx
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // edx
  int v59; // eax
  int v60; // edx
  int v61; // eax
  int v62; // edx
  int v63; // edx
  int v64; // eax
  int v65; // edx
  int v66; // eax
  int v67; // edx
  int v68; // edx
  int v69; // eax
  int v70; // edx
  int v71; // eax
  int v72; // edx
  int v73; // edx
  int v74; // edx
  int v75; // edx
  int v76; // edx
  int v77; // edx
  int v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v87; // [esp+Ch] [ebp-8h]
  int v88; // [esp+Ch] [ebp-8h]
  int v89; // [esp+10h] [ebp-4h]
  int v90; // [esp+10h] [ebp-4h]
  int v91; // [esp+10h] [ebp-4h]
  int v92; // [esp+10h] [ebp-4h]
  int v93; // [esp+1Ch] [ebp+8h]
  int v94; // [esp+1Ch] [ebp+8h]
  int v95; // [esp+1Ch] [ebp+8h]
  int v96; // [esp+1Ch] [ebp+8h]
  int v97; // [esp+1Ch] [ebp+8h]
  int v98; // [esp+1Ch] [ebp+8h]
  unsigned int pThis_AC; // [esp+1Ch] [ebp+8h]
  unsigned int pThis_E4; // [esp+1Ch] [ebp+8h]
  unsigned int pThis_11C; // [esp+1Ch] [ebp+8h]
  unsigned int pThis_1FC; // [esp+1Ch] [ebp+8h]
  int v103; // [esp+1Ch] [ebp+8h]
  int v104; // [esp+1Ch] [ebp+8h]
  int v105; // [esp+1Ch] [ebp+8h]
  int v106; // [esp+1Ch] [ebp+8h]
  int v107; // [esp+1Ch] [ebp+8h]
  int v108; // [esp+1Ch] [ebp+8h]
  int v109; // [esp+1Ch] [ebp+8h]
  int v110; // [esp+1Ch] [ebp+8h]
  int v111; // [esp+1Ch] [ebp+8h]
  int v112; // [esp+1Ch] [ebp+8h]
  int v113; // [esp+1Ch] [ebp+8h]
  int v114; // [esp+1Ch] [ebp+8h]
  int v115; // [esp+1Ch] [ebp+8h]
  int v116; // [esp+1Ch] [ebp+8h]
  int v117; // [esp+1Ch] [ebp+8h]
  int v118; // [esp+1Ch] [ebp+8h]
  int v119; // [esp+1Ch] [ebp+8h]
  int v120; // [esp+1Ch] [ebp+8h]
  int v121; // [esp+1Ch] [ebp+8h]
  int v122; // [esp+1Ch] [ebp+8h]
  int v123; // [esp+1Ch] [ebp+8h]
  int v124; // [esp+1Ch] [ebp+8h]
  int v125; // [esp+1Ch] [ebp+8h]

  *(uint32_t *)this = *(uint32_t *)pszArg2;
  v4 = sub_41A5E0((unsigned int)(pszArg2 + 4));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 4), v5, v4);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v93 = sub_43B5A0(pszArg2 + 18);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 18), v6, v93);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v7 = sub_41A5E0((unsigned int)(pszArg2 + 32));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 32), v8, v7);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v94 = sub_43B5A0(pszArg2 + 46);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 46), v94, v94);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v9 = sub_41A5E0((unsigned int)(pszArg2 + 60));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 60), v10, v9);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v95 = sub_43B5A0(pszArg2 + 74);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 74), v11, v95);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v12 = sub_41A5E0((unsigned int)(pszArg2 + 88));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 88), v13, v12);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v96 = sub_43B5A0(pszArg2 + 102);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 102), v14, v96);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v15 = sub_41A5E0((unsigned int)(pszArg2 + 116));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 116), v16, v15);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v97 = sub_43B5A0(pszArg2 + 130);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 130), v97, v97);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v17 = sub_41A5E0((unsigned int)(pszArg2 + 144));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 144), v18, v17);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v98 = sub_43B5A0(pszArg2 + 158);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 158), v19, v98);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_AC = (unsigned int)(this + 172);  // this+688 = 表现/名字快照[2]
  v20 = pszArg2 - this;
  v89 = 4;
  do
  {
    v21 = sub_41A5E0(v20 + pThis_AC);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_AC, v22, v21);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v23 = v89 == 1;
    pThis_AC += 14;  // pThis_AC=this+688 表现/名字快照
    --v89;
  }
  while ( !v23 );
  pThis_E4 = (unsigned int)(this + 228);  // this+228 快照副本 C
  v90 = 4;
  do
  {
    *(float *)&v87 = sub_43B5A0((void *)(v20 + pThis_E4));  // 调 防篡读壳（槽值转 float）
    sub_41A590(pThis_E4, v87, v87);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v23 = v90 == 1;
    pThis_E4 += 14;  // pThis_E4=this+228 快照副本 C
    --v90;
  }
  while ( !v23 );
  pThis_11C = (unsigned int)(this + 284);  // this+284 绑定/记录门字节
  v91 = 16;
  do
  {
    v24 = sub_41A5E0(v20 + pThis_11C);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_11C, v25, v24);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v23 = v91 == 1;
    pThis_11C += 14;  // pThis_11C=this+284 绑定/记录门字节
    --v91;
  }
  while ( !v23 );
  pThis_1FC = (unsigned int)(this + 508);  // this+508 【推断】伙伴/弹体标志
  v92 = 16;
  do
  {
    *(float *)&v88 = sub_43B5A0((void *)(v20 + pThis_1FC));  // 调 防篡读壳（槽值转 float）
    sub_41A590(pThis_1FC, v26, v88);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    v23 = v92 == 1;
    pThis_1FC += 14;  // pThis_1FC=this+508 伙伴/弹体标志
    --v92;
  }
  while ( !v23 );
  v27 = sub_41A5E0((unsigned int)(pszArg2 + 732));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 732), v28, v27);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v103 = sub_43B5A0(pszArg2 + 746);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 746), v103, v103);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v29 = sub_41A5E0((unsigned int)(pszArg2 + 760));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 760), v30, v29);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v104 = sub_43B5A0(pszArg2 + 774);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 774), v31, v104);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v32 = sub_41A5E0((unsigned int)(pszArg2 + 788));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 788), v33, v32);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v105 = sub_43B5A0(pszArg2 + 802);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 802), v34, v105);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v35 = sub_41A5E0((unsigned int)(pszArg2 + 816));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 816), v36, v35);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v106 = sub_43B5A0(pszArg2 + 830);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 830), v106, v106);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v37 = sub_41A5E0((unsigned int)(pszArg2 + 844));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 844), v38, v37);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v107 = sub_43B5A0(pszArg2 + 858);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 858), v39, v107);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v40 = sub_41A5E0((unsigned int)(pszArg2 + 872));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 872), v41, v40);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v108 = sub_43B5A0(pszArg2 + 886);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 886), v42, v108);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v43 = sub_41A5E0((unsigned int)(pszArg2 + 900));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 900), v44, v43);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v109 = sub_43B5A0(pszArg2 + 914);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 914), v109, v109);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v45 = sub_41A5E0((unsigned int)(pszArg2 + 928));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 928), v46, v45);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v110 = sub_43B5A0(pszArg2 + 942);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 942), v47, v110);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v48 = sub_41A5E0((unsigned int)(pszArg2 + 956));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 956), v49, v48);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v111 = sub_43B5A0(pszArg2 + 970);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 970), v50, v111);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v51 = sub_41A5E0((unsigned int)(pszArg2 + 984));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 984), v52, v51);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v112 = sub_43B5A0(pszArg2 + 998);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 998), v112, v112);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v53 = sub_41A5E0((unsigned int)(pszArg2 + 1012));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1012), v54, v53);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v113 = sub_43B5A0(pszArg2 + 1026);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1026), v55, v113);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v56 = sub_41A5E0((unsigned int)(pszArg2 + 1040));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1040), v57, v56);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v114 = sub_43B5A0(pszArg2 + 1054);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1054), v58, v114);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v59 = sub_41A5E0((unsigned int)(pszArg2 + 1068));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1068), v60, v59);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v115 = sub_43B5A0(pszArg2 + 1082);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1082), v115, v115);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v61 = sub_41A5E0((unsigned int)(pszArg2 + 1096));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1096), v62, v61);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v116 = sub_43B5A0(pszArg2 + 1110);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1110), v63, v116);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v64 = sub_41A5E0((unsigned int)(pszArg2 + 1124));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1124), v65, v64);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v66 = sub_41A5E0((unsigned int)(pszArg2 + 1138));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1138), v67, v66);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v117 = sub_43B5A0(pszArg2 + 1152);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1152), v68, v117);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v69 = sub_41A5E0((unsigned int)(pszArg2 + 1166));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1166), v70, v69);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v71 = sub_41A5E0((unsigned int)(pszArg2 + 1180));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1180), v72, v71);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v118 = sub_43B5A0(pszArg2 + 1194);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1194), v118, v118);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v119 = sub_43B5A0(pszArg2 + 1208);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1208), v73, v119);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v120 = sub_43B5A0(pszArg2 + 1222);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1222), v74, v120);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v121 = sub_43B5A0(pszArg2 + 1236);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1236), v121, v121);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v122 = sub_43B5A0(pszArg2 + 1250);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1250), v75, v122);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v123 = sub_43B5A0(pszArg2 + 1264);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1264), v76, v123);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v124 = sub_43B5A0(pszArg2 + 1278);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1278), v124, v124);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(float *)&v125 = sub_43B5A0(pszArg2 + 1292);  // 调 防篡读壳（槽值转 float）
  sub_41A590((unsigned int)(this + 1292), v77, v125);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v78 = sub_41A5E0((unsigned int)(pszArg2 + 1306));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1306), v79, v78);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v80 = sub_41A5E0((unsigned int)(pszArg2 + 1320));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1320), v81, v80);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v82 = sub_41A5E0((unsigned int)(pszArg2 + 1334));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1334), v83, v82);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v84 = sub_41A5E0((unsigned int)(pszArg2 + 1348));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1348), v85, v84);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}


// ============================================================
// SECTION 0x4A2B30 — 关联容器/链表基础设施（refcount 封装 / 环形缓冲 / 红黑树模板实例 / std::string 辅助）
// ============================================================
// ------------------------------------------------------------
// 0x4A2B30 sub_4A2B30 [RTTI: IRDActiveObject__vmt2A8 · 槽位 IRDActiveObject+2A8]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 2 槽赋值（vmt2A8）: 把 a2/a2+14 的 clong 值 push 进 this+6132/+6146。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A2B30(void *this, unsigned int pArg2)  // 【关联容器/链表基础设施（refcount 封装 / 环形缓冲 / 红黑树模板实例 /…】
{
  unsigned int pThis_17F4; // esi
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_17F4 = (unsigned int)this + 6132;  // this+6132〔nAttrBlock6132〕
  v3 = sub_41A5E0(pArg2);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_17F4, v4, v3);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  v5 = sub_41A5E0(pArg2 + 14);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_17F4 + 14, v6, v5);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return pThis_17F4;  // pThis_17F4=this+6132 nAttrBlock6132
}



// ------------------------------------------------------------
// 0x4A2B80 sub_4A2B80 [RTTI: IRDActiveObject__vmt270 · 槽位 IRDActiveObject+270] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt270 —— 基类检查 + 附加条件（+7093 == 0）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A2B80(uint8_t *this)  // 函数: 基类检查 + 附加条件（+7093 == 0）
{
  return (uint8_t)sub_4A2BB0() != 0 && *(this + 7093) == 0;  // 调 ★ 攻击使能检查（动画率 + 帧检查）【会话 3 新分析】
}



// ------------------------------------------------------------
// 0x4A2BB0 sub_4A2BB0 [RTTI: IRDCollisionObject__vmt270 · 槽位 IRDCollisionObject+270] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt270 —— 攻击使能检查（vt+608 + 动画帧率态 != 2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2BB0(int *this)  // 函数: ★ 攻击使能检查（动画率 + 帧检查）【会话 3 新分析】
{
  uint32_t *pAnimObj; // esi
  int uHitBoxSnap644; // eax
  int v4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 608))(this) == 0 )  // 调用虚函数（虚表槽 +608）
    return 0;
  pAnimObj = (uint32_t *)*(this + 30);  // this+120 = 动画对象指针
  if ( pAnimObj == nullptr )  // 若 fld_e30 为空
    return 0;
  if ( pAnimObj[37] == -1 )  // fld_e30=this+120 pAnimObj
    sub_4938F0(*(this + 30));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  if ( (uHitBoxSnap644 = pAnimObj[34]) != 0  // fld_e30=this+120 pAnimObj
    && (pAnimObj[35] - uHitBoxSnap644) / 24 != 0  // fld_e30=this+120 pAnimObj
    && (*((uint8_t *)this + 642) == 0 ? (v4 = sub_4A2C40(this)) : (v4 = *(this + 161)), v4 != 2) )  // this+642 = 帧时刻覆盖开关
  {
    return 1;  // 返回 1(成功)
  }
  else
  {
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4A2C40 sub_4A2C40
// ------------------------------------------------------------
// 【解读】
//   【推断】动画对象帧率态查询（vmt270 判定链的叶子）。返回动画对象 +112（帧率态）。
//   【待验证】返回 2 = 冻结帧（见 IRDCollisionObject_vmt270 判据）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2C40(int *this)  // 实现：(待验证)返回 2 = 冻结帧（见 IRDCollisionObject_vmt270 判据）
{
  int fld_e30; // esi

  fld_e30 = *(this + 30);  // this+120 = 动画对象指针
  if ( fld_e30 == 0 )  // fld_e30=this+120 动画对象指针
    return 0;
  if ( *(uint32_t *)(fld_e30 + 148) == -1 )  // fld_e30=this+120 动画对象指针
    sub_4938F0(*(this + 30));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  return *(uint32_t *)(fld_e30 + 112);  // fld_e30=this+120 动画对象指针
}



// ------------------------------------------------------------
// 0x4A2C70 sub_4A2C70
// ------------------------------------------------------------
// 【解读】
//   【推断】链表节点逐项释放（stdcall，Block = 链头）—— 循环 free，供 0x4A2DE0 清链。
// ------------------------------------------------------------
char /*stdcall*/ sub_4A2C70(void **Block)  // 实现：(推断)链表节点逐项释放（stdcall，Block = 链头）—— 循环 free，供 0x4A2DE0 清链
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4A2C70(i[2]);  // 调 链表清理族
    i = (void **)*i;
    j__free(Block2);  // 调 堆释放
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2CB0 sub_4A2CB0
// ------------------------------------------------------------
// 【解读】
//   【推断】链表节点逐项释放（第二种节点布局，同 0x4A2C70 对偶）—— 见 0x4A2DE0 双链清空。
// ------------------------------------------------------------
char /*stdcall*/ sub_4A2CB0(void **Block)  // 实现：(推断)链表节点逐项释放（第二种节点布局，同 0x4A2C70 对偶）—— 见 0x4A2DE0 双链清空
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4A2CB0(i[2]);  // 调 链表清理族
    i = (void **)*i;
    j__free(Block2);  // 调 堆释放
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2CF0 sub_4A2CF0
// ------------------------------------------------------------
// 【解读】
//   【推断】申请 16 字节双向链表哨兵头（首/末指针自指）—— 0x4A49B0 用它初始化 +6544 光环链表。
//   （与 docs/15 §3 "宿主 +6544/6548 = 光环显示链表头/计数" 对照）
// ------------------------------------------------------------
uint32_t *sub_4A2CF0()  // 实现：（与 docs/15 §3 宿主 +6544/6548 = 光环显示链表头/计数 对照）
{
  uint32_t *result; // eax

  result = operator new(0x10u);  // operator new 分配 16 字节
  if ( result != nullptr )  // 若 result 有效（非空）
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4A2D10 sub_4A2D10
// ------------------------------------------------------------
// 【解读】
//   【推断】申请 20 字节双向链表哨兵头 —— 比 0x4A2CF0 多一个计数/类型字段。
//   被 0x4AB840（CNSpikeKing 构造）用作 +8616 的内嵌链表初始化。
// ------------------------------------------------------------
uint32_t *sub_4A2D10()  // 实现：被 0x4AB840（CNSpikeKing 构造）用作 +8616 的内嵌链表初始化
{
  uint32_t *result; // eax

  result = operator new(0x14u);  // operator new 分配 20 字节
  if ( result != nullptr )  // 若 result 有效（非空）
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4A2D30 sub_4A2D30 [RTTI: IRDCollisionObject__vmt180 · 槽位 IRDActiveObject+180,IRDCollisionObject+180] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt180 —— 槽数组 getter（+348 起，越界返回 0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2D30(uint32_t *this, unsigned int uArg2)  // 实现：槽数组 getter（+348 起，越界返回 0）
{
  int fld_e87; // edx

  fld_e87 = *(this + 87);  // this+348〔pParamTbl348〕
  if ( fld_e87 != 0 && uArg2 < (*(this + 88) - fld_e87) >> 2 )  // this+352〔uHitCtx352〕
    return *(uint32_t *)(*(this + 87) + 4 * uArg2);  // this+348〔pParamTbl348〕
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A2D70 sub_4A2D70 [RTTI: IRDActiveObject__vmt25C · 槽位 IRDActiveObject+25C] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt25C —— 受击盒使能 setter（+641）+ 附属物 vt+604 广播
// ------------------------------------------------------------
// 【解读】
//   【已精修】受击盒使能 setter（vmt25C）—— 写 this+641（无敌开关）后遍历 +7076 附属物 vector，
//   对每个附属物调其 vt+604(a2) 广播（研究 P35 定案）。完整逐行版见
//   src/cnrd/IRDActiveObject.cpp IRDActiveObject_vmt25C。此处保留 L2 原文以维持本区函数计数。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A2D70(int this, int nArg2)  // 函数: 受击盒使能 setter + 向全部附属物（+7076 数组）广播 vt+604
{
  int fld_1BA4; // ecx
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_1BA42; // ecx

  *(uint8_t *)(this + 641) = nArg2;  // this+641〔bHitBoxEnable〕
  fld_1BA4 = *(uint32_t *)(this + 7076);
  if ( fld_1BA4 != 0 )
  {
    result = (*(uint32_t *)(this + 7080) - fld_1BA4) >> 2;
    if ( result != 0 )  // 若结果非 0（成功）
    {
      for ( i = 0; ; ++i )
      {
        fld_1BA42 = *(uint32_t *)(this + 7076);
        if ( fld_1BA42 == 0 )
          break;
        result = (*(uint32_t *)(this + 7080) - fld_1BA42) >> 2;
        if ( i >= result )
          break;
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_1BA42 + 4 * i) + 604))(*(uint32_t *)(fld_1BA42 + 4 * i), nArg2);  // 调用虚函数（虚表槽 +604）【推断: [RTTI: IRDActiveObject__vmt25C ·…】
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2DE0 sub_4A2DE0 [RTTI: IRDCollisionObject__vmt160 · 槽位 IRDActiveObject+160,IRDCollisionObject+160] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt160 —— 命中列表双链表清空
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A2DE0(uint32_t *this)  // 实现：命中列表双链表清空
{
  uint32_t *pThis_87; // esi
  uint32_t *v3; // eax
  uint32_t *result; // eax

  pThis_87 = this + 135;
  sub_4A2C70(*(void ***)(*(this + 136) + 4));  // this+544〔nFaction〕
  *(uint32_t *)(pThis_87[1] + 4) = pThis_87[1];
  v3 = (uint32_t *)pThis_87[1];
  pThis_87[2] = 0;
  *v3 = v3;
  *(uint32_t *)(pThis_87[1] + 8) = pThis_87[1];
  sub_4A2CB0(*(void ***)(*(this + 150) + 4));  // 调 链表清理族
  *(uint32_t *)(*(this + 150) + 4) = *(this + 150);
  result = (uint32_t *)*(this + 150);
  *(this + 151) = 0;
  *result = result;
  *(uint32_t *)(*(this + 150) + 8) = *(this + 150);
  return result;
}



// ------------------------------------------------------------
// 0x4A2E50 sub_4A2E50
// ------------------------------------------------------------
// 【解读】
//   【推断】std::string 三元组 + vector 清理（this+64/48/8 三块，MSVC string 的 15/16 容量布局）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A2E50(int this)  // 实现：(推断)std::string 三元组 + vector 清理（this+64/48/8 三块，MSVC string 的 15/1…
{
  if ( *(uint32_t *)(this + 64) != 0 )  // this+256 = 基类四元组字节槽 3
    j__free(*(void **)(this + 64));  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 调 堆释放
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+112 = pHostComp
    j__free(*(void **)(this + 8));  // 调 堆释放
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 15;  // this+112 = pHostComp
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x4A2EB0 sub_4A2EB0
// ------------------------------------------------------------
// 【解读】
//   【推断】单个 MSVC std::string 析构（容量 >= 0x10 则 free 堆缓冲，复位为空短串）。
//   被 0x4A3870/0x4A4170 用作"数组元素批量析构"的单位函数（元素步长 152 字节）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2EB0(int this)  // 实现：被 0x4A3870/0x4A4170 用作数组元素批量析构的单位函数（元素步长 152 字节）
{
  if ( *(uint32_t *)(this + 116) >= 0x10u )  // this+116〔会话上下文〕
    j__free(*(void **)(this + 96));  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 116) = 15;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint8_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  return 0;
}



// ------------------------------------------------------------
// 0x4A2EE0 sub_4A2EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】48 字节固定头部 + 双向链表的初始化器（本文件 +0 处 200/1 等常数）。
//   【待验证】字段: +0=200、+4=1000、+18(int)=50 —— 与属性块默认值风格一致。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A2EE0(char *this)  // 实现：(待验证)字段: +0=200、+4=1000、+18(int)=50 —— 与属性块默认值风格一致
{
  char *pThis_54; // esi
  uint32_t *result; // eax

  *(uint32_t *)this = 200;  // *this = 200
  *(this + 8) = 1;  // this+8 = 技能槽记录首字
  *(this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  *(this + 10) = 0;  // this+40〔bStateSub40(推断)〕
  *(this + 38) = 0;  // this+152〔nAdd152(推断)〕
  *(this + 37) = 0;  // this+148〔fAdd148(推断)〕
  *(this + 36) = 0;  // this+36 = 状态字
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 12) = 0;  // this+12 = 技能槽记录次字
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *((uint32_t *)this + 1) = 1000;  // this+4 = pHostObj
  *(uint32_t *)(this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *(uint32_t *)(this + 19) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(uint32_t *)(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 31) = 0;  // this+124〔pAuraAnim(推断)〕
  *(this + 35) = 0;  // this+140〔nAdd140(推断)〕
  *((uint32_t *)this + 20) = 1000;  // this+80 = nAuraStage
  pThis_54 = this + 84;  // this+84 插值起点 X
  *((uint32_t *)this + 13) = 0;  // this+52 = bAuraState
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *((uint32_t *)this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *((uint32_t *)this + 18) = 50;  // this+72〔nSnapshot72(推断)〕
  *((uint32_t *)this + 19) = 0;  // this+76〔pBtnActionE〕
  *(this + 39) = 0;  // this+156〔nAdd156(推断)〕
  *((uint32_t *)this + 10) = 0;  // this+40 = 状态子标志
  sub_41CAA0(*(void ***)(*((uint32_t *)this + 22) + 4));  // 调 同构实例三
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 4) = *((uint32_t *)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  result = *((uint32_t **)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  *((uint32_t *)pThis_54 + 2) = 0;  // pThis_54=this+84 插值起点 X
  *result = result;
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 8) = *((uint32_t *)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  return result;
}



// ------------------------------------------------------------
// 0x4A2F80 sub_4A2F80
// ------------------------------------------------------------
// 【解读】
//   【推断】按名字查找链表节点（std::map 风格遍历 + sub_40BF00 字符串比较）。
//   找到返回节点 [3]（值），未找到返回 -1。MSVC std::map<CString,int> 的查找模板实例。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2F80(uint32_t *this, const char *pArg2)  // 实现：找到返回节点 [3]（值），未找到返回 -1。MSVC std::map<CString,int> 的查找模板实例
{
  uint32_t *fld_e1; // eax
  uint32_t *v3; // ebx
  bool v4; // zf
  uint32_t *v7; // [esp+10h] [ebp-4h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v3 = (uint32_t *)*fld_e1;  // fld_e1=this+4 宿主对象
  v4 = *fld_e1 == (uint32_t)fld_e1;  // fld_e1=this+4 宿主对象
  v7 = (uint32_t *)*fld_e1;  // fld_e1=this+4 宿主对象
  if ( v4 )
    return -1;
  while ( sub_40BF00((std::_String_base *)(v3 + 4), 0, v3[9], pArg2, strlen(pArg2)) != 0 )  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    sub_40BEA0((int *)&v7);  // 调 红黑树迭代器自增（后继；哨兵位 +45）
    v3 = v7;
    if ( v7 == (uint32_t *)*(this + 1) )  // this+4 = pHostObj
      return -1;
  }
  return v3[3];  // 返回 取 v3[3]
}



// ------------------------------------------------------------
// 0x4A2FF0 sub_4A2FF0
// ------------------------------------------------------------
// 【解读】
//   【推断】结构体清零 + 两个 vector 释放（MSVC vector 三指针布局 @+40/+56）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A2FF0(void *this)  // 实现：(推断)结构体清零 + 两个 vector 释放（MSVC vector 三指针布局 @+40/+56）
{
  *(uint32_t *)this = 0;  // *this = 0
  *((uint32_t *)this + 1) = 0;  // this+4 = pHostObj
  *((uint32_t *)this + 2) = 0;  // this+8 = 技能槽记录首字
  *((uint32_t *)this + 3) = 0;  // this+12 = 技能槽记录次字
  *((uint32_t *)this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *((uint32_t *)this + 5) = 0;  // this+20〔nPage(推断)〕
  *((uint32_t *)this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *((uint32_t *)this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  *((uint32_t *)this + 8) = 0;  // this+32〔nHeight(推断)〕
  if ( *((uint32_t *)this + 10) != 0 )  // this+40 = 状态子标志
    j__free(*((void **)this + 10));  // 调 堆释放
  *((uint32_t *)this + 10) = 0;  // this+40 = 状态子标志
  *((uint32_t *)this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  if ( *((uint32_t *)this + 14) != 0 )  // this+56〔pCmdVecCap56(推断)〕
    j__free(*((void **)this + 14));  // 调 堆释放
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *((uint32_t *)this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *((uint32_t *)this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
}



// ------------------------------------------------------------
// 0x4A3050 sub_4A3050
// ------------------------------------------------------------
// 【解读】
//   【推断】大结构体清零（2×104 字节 memset + 头尾字段）—— 尺寸约 288 字节。
//   【待验证】与 0x4A3EB0 的 72 DWORD 拷贝对应（同为 288 字节对象）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3050(int this)  // 实现：(待验证)与 0x4A3EB0 的 72 DWORD 拷贝对应（同为 288 字节对象）
{
  uint32_t *pThis_118; // esi

  if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
    j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+112 = pHostComp
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  memset((void *)(this + 72), 0, 0x68u);  // 调 内存按字节填充
  memset((void *)(this + 176), 0, 0x68u);  // this+704 = 表现/名字快照[24]
  pThis_118 = (uint32_t *)(this + 280);  // this+280〔pMapEntryVecEnd〕
  *pThis_118 = 0;  // pThis_118=this+280 pMapEntryVecEnd
  pThis_118[1] = 0;  // pThis_118=this+280 pMapEntryVecEnd
  return 0;
}



// ------------------------------------------------------------
// 0x4A30C0 sub_4A30C0
// ------------------------------------------------------------
// 【解读】
//   【推断】std::length_error 抛出桩（"vector<T> too long"）—— MSVC 模板实例。
//   被 0x4A3570/0x4A35C0 在 a2 > 0x15555555（12 字节元素的最大容量）时调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_4A30C0()  // 实现：被 0x4A3570/0x4A35C0 在 a2 > 0x15555555（12 字节元素的最大容量）时调用
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
  pExceptionObject[0] = &std::length_error::`vftable';  // vftable 复位
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4A3130 sub_4A3130
// ------------------------------------------------------------
// 【解读】
//   【推断】★ std::map/std::set 红黑树 single-node erase（MSVC _Tree::erase 模板实例）。
//   特征: "invalid map/set<T> iterator" 异常对象、+21 红黑标志字节、+12 排序键、
//   左右子指针 [0]/[1]/[2] 与 rebalance 调用链 —— 被 IRDCollisionObject_vmt12C（0x4E7480）
//   用于命中目标集的移除。完整语义 = 标准库实现，本层只保留结构。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4A3130(uint32_t *this, int ***uArg2, int **pDwArg3)  // 实现：用于命中目标集的移除。完整语义 = 标准库实现，本层只保留结构
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(v20);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
    pExceptionObject = &std::out_of_range::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);  // 调 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);  // 调 v9 = sub_52E300(v4) 最左
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);  // 调 展示子窗口辅助（16 行）
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);  // 调 红黑树左旋（节点 0x18 版）
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);  // 调 STL 内联红黑树节点摘除重连
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);  // 调 红黑树左旋（节点 0x18 版）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);  // 调 STL 内联红黑树节点摘除重连
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);  // 调 红黑树左旋（节点 0x18 版）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);  // 调 STL 内联红黑树节点摘除重连
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);  // 调 堆释放
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ============================================================
// SECTION 0x4A33F0 — std::map/std::set 红黑树模板实例族（MSVC _Tree）
// ============================================================
// ------------------------------------------------------------
// 0x4A33F0 sub_4A33F0
// ------------------------------------------------------------
// 【解读】
//   【推断】含 CString(MSVC string @+4) 与两个 vector(@+48/@+64) 的对象初始化。
//   sub_4015C0(ptr, szPassword, 0) = 空 CString 构造 —— szPassword 在此为空串模板。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A33F0(void *this)  // 【std::map/std::set 红黑树模板实例族（MSVC _Tree）】
{
  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((size_t *)this + 1, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;  // this+32〔nHeight(推断)〕
  *((uint32_t *)this + 9) = 0;  // this+36 = 状态字
  *((uint32_t *)this + 10) = 0;  // this+40 = 状态子标志
  if ( *((uint32_t *)this + 12) != 0 )  // this+48〔pCmdVecBegin48(推断)〕
    j__free(*((void **)this + 12));  // 调 堆释放
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52 = bAuraState
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  if ( *((uint32_t *)this + 16) != 0 )  // this+64〔apServerTabBtn(推断)〕
    j__free(*((void **)this + 16));  // 调 堆释放
  *((uint32_t *)this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
}



// ------------------------------------------------------------
// 0x4A3450 sub_4A3450
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 攻击上下文默认构造（IRDCollisionObject +388 属；被 IRDActiveObject_vmt158 调用）。
//   IRDCollisionObject.h 记录: "vmt158 攻击上下文设置（sub_4B2970 拷贝 / sub_4A3450 默认）"。
//   本函数即"默认"分支。初值: +5=4、+6/+7/+8=17、+19 字节=1、+21/+22=1120403456(=75.0f)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3450(uint32_t *this)  // 实现：本函数即默认分支。初值: +5=4、+6/+7/+8=17、+19 字节=1、+21/+22=1120403456(=75.0f…
{
  int result; // eax

  *this = 0;
  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  *((uint8_t *)this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *((uint8_t *)this + 17) = 0;  // this+17〔bEnable〕
  *((uint8_t *)this + 18) = 0;  // this+18〔bDragChild〕
  *((uint8_t *)this + 19) = 1;
  *(this + 5) = 4;  // this+20〔nPage(推断)〕
  *(this + 9) = 0;  // this+36 = 状态字
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 10) = 0;  // this+40 = 状态子标志
  *(this + 13) = 0;  // this+52 = bAuraState
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 6) = 17;  // this+24〔nPageMax(推断)〕
  *(this + 7) = 17;  // this+28〔pPanelVec(推断)〕
  *(this + 8) = 17;  // this+32〔nHeight(推断)〕
  *(this + 15) = 1;  // this+60〔nFadeValue60(推断)〕
  *(this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *(this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 19) = 0;  // this+76〔pBtnActionE〕
  *((uint8_t *)this + 80) = 0;  // this+80 = nAuraStage
  *((uint8_t *)this + 81) = 0;  // this+81 高度提交槽
  *((uint8_t *)this + 82) = 0;
  *(this + 21) = 1120403456;  // this+84 = pFxObjA
  *(this + 22) = 1120403456;  // this+88 = pFxObjB
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint8_t *)this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕
  *((uint8_t *)this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *((uint8_t *)this + 141) = 0;  // this+141〔bFadeFlagA〕
  *(this + 36) = 0;  // this+144 = pFrameList144
  *(this + 30) = 1;  // this+120 = 动画对象指针
  *(this + 31) = 4;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(this + 33) = -1;  // this+132〔nAgeTicks〕
  *(this + 34) = -1082130432;  // this+136〔nCtx136(推断)〕
  *(this + 37) = 1120403456;  // this+148 = 100.0f
  return result;
}



// ------------------------------------------------------------
// 0x4A3520 sub_4A3520
// ------------------------------------------------------------
// 【解读】
//   【推断】攻击上下文重置（string 复位 + 0x4A3450 默认值）—— 复合重置器。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3520(int this)  // 实现：(推断)攻击上下文重置（string 复位 + 0x4A3450 默认值）—— 复合重置器
{
  *(uint32_t *)(this + 116) = 15;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint8_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  sub_4A3450((uint32_t *)this);  // 调 attackinfo 默认值（sub_4A3450 @0x4A3450…
  return this;
}



// ------------------------------------------------------------
// 0x4A3570 sub_4A3570
// ------------------------------------------------------------
// 【解读】
//   【推断】12 字节元素 vector 的 reserve（a2 > 0x15555555 抛 length_error）。
//   【推断】元素 = 12 字节三元组（坐标/向量点）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A3570(uint32_t *this, unsigned int uArg2)  // 实现：(推断)元素 = 12 字节三元组（坐标/向量点）
{
  char *pMem; // eax

  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x15555555 )
    sub_4A30C0();
  pMem = (char *)operator new(12 * uArg2);
  *(this + 3) = &pMem[12 * uArg2];  // this+12 = 技能槽记录次字
  *(this + 1) = pMem;  // this+4 = pHostObj
  *(this + 2) = pMem;  // this+8 = 技能槽记录首字
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4A35C0 sub_4A35C0
// ------------------------------------------------------------
// 【解读】
//   【推断】与 0x4A3570 同构的第二个 reserve（另一元素类型/容器）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A35C0(uint32_t *this, unsigned int uArg2)  // 实现：(推断)与 0x4A3570 同构的第二个 reserve（另一元素类型/容器）
{
  char *pMem; // eax

  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x7FFFFFF )
    sub_4A30C0();
  pMem = (char *)operator new(32 * uArg2);
  *(this + 3) = &pMem[32 * uArg2];  // this+12 = 技能槽记录次字
  *(this + 1) = pMem;  // this+4 = pHostObj
  *(this + 2) = pMem;  // this+8 = 技能槽记录首字
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4A3610 sub_4A3610
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树递归析构（后序 free，MSVC _Tree 模板）—— 与 0x4A36D0 成对实现两种节点类型。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4A3610(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // 实现：(推断)红黑树递归析构（后序 free，MSVC _Tree 模板）—— 与 0x4A36D0 成对实现两种节点类型
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);  // this+4 = pHostObj
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4A2C70(*(void ***)(fld_e1 + 4));  // 调 链表清理族
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4 = pHostObj
    fld_e12 = *(this + 1);  // this+4 = pHostObj
    *(this + 2) = nullptr;  // this+8 = 技能槽记录首字
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4 = pHostObj
    *pDwArg2 = **(this + 1);  // this+4 = pHostObj
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4A3130(this, (int ***)&pDwArg3, v10);  // 调 用于命中目标集的移除。完整语义 = 标准库实现，本层只保留结构
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4A36D0 sub_4A36D0
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树递归析构（第二版）—— 与 0x4A3610 对偶（不同节点大小）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4A36D0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // 实现：(推断)红黑树递归析构（第二版）—— 与 0x4A3610 对偶（不同节点大小）
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);  // this+4 = pHostObj
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4A2CB0(*(void ***)(fld_e1 + 4));  // 调 链表清理族
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4 = pHostObj
    fld_e12 = *(this + 1);  // this+4 = pHostObj
    *(this + 2) = nullptr;  // this+8 = 技能槽记录首字
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4 = pHostObj
    *pDwArg2 = **(this + 1);  // this+4 = pHostObj
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4A3130(this, (int ***)&pDwArg3, v10);  // 调 用于命中目标集的移除。完整语义 = 标准库实现，本层只保留结构
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4A3790 sub_4A3790
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树容器清理（调 0x4A3610 析构全树 + free 头结点）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3790(int this)  // 实现：(推断)红黑树容器清理（调 0x4A3610 析构全树 + free 头结点）
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4A3610((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // 调 释放旧树后·sub
  j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return 0;
}



// ------------------------------------------------------------
// 0x4A37D0 sub_4A37D0
// ------------------------------------------------------------
// 【解读】
//   【推断】含 CString + vector 的对象重置（先清 15/16 容量串，再 sub_4A33F0 初始化）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A37D0(int this)  // 实现：(推断)含 CString + vector 的对象重置（先清 15/16 容量串，再 sub_4A33F0 初始化）
{
  *(uint32_t *)(this + 28) = 15;  // this+112 = pHostComp
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  sub_4A33F0((void *)this);  // 【std::map/std::set 红黑树模板实例族（MSVC _Tree）】
  return this;
}



// ------------------------------------------------------------
// 0x4A3830 sub_4A3830
// ------------------------------------------------------------
// 【解读】
//   【推断】vector<T> 释放（sub_41DA40 逐元素析构 + free）—— MSVC vector 模板。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3830(int ***this)  // 实现：(推断)vector<T> 释放（sub_41DA40 逐元素析构 + free）—— MSVC vector 模板
{
  int ***pThis_15; // esi
  int *v3; // [esp+4h] [ebp-4h] BYREF

  pThis_15 = this + 21;  // this+21〔bArmorState〕
  sub_41DA40(this + 21, &v3, **(this + 22), (int *)*(this + 22));  // 调 同族实例二（回调 0x41CAA0）
  j__free(pThis_15[1]);  // 调 堆释放
  pThis_15[1] = nullptr;  // pThis_15=this+21 bArmorState
  pThis_15[2] = nullptr;  // pThis_15=this+21 bArmorState
  return 0;
}



// ------------------------------------------------------------
// 0x4A3870 sub_4A3870
// ------------------------------------------------------------
// 【解读】
//   【推断】152 字节步长数组的元素批量析构（每元素 = 一个含 string 的结构，见 0x4A2EB0）。
// ------------------------------------------------------------
int /*stdcall*/ sub_4A3870(int nArg1, int nArg2)  // 实现：(推断)152 字节步长数组的元素批量析构（每元素 = 一个含 string 的结构，见 0x4A2EB0）
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 152 )
    result = sub_4A2EB0(i);
  return result;
}



// ------------------------------------------------------------
// 0x4A38A0 sub_4A38A0 [RTTI: IRDCollisionObject__vmt150 · 槽位 IRDActiveObject+150,IRDCollisionObject+150]
// ------------------------------------------------------------
// 【解读】
//   【推断】结构体拷贝赋值（含 CString @+4 sub_4014D0 与两个子对象 @+44/+60 sub_4ED3F0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A38A0(uint32_t *this, uint32_t *pArg2)  // 函数 sub_4A38A0：[RTTI IRDCollisionObject__vmt150 槽位 IRDActiveObject+150,IRDCol…
{
  uint32_t *pThis_47; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_47 = this + 71;  // this+71〔bMoveType〕
  *(this + 71) = *pArg2;  // this+284〔bBindGate284(推断)〕
  sub_4014D0(this + 72, pArg2 + 1, 0, 0xFFFFFFFF);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  pThis_47[8] = pArg2[8];  // pThis_47[8] = 取 pArg2[8]
  pThis_47[9] = pArg2[9];  // pThis_47[9] = 取 pArg2[9]
  pThis_47[10] = pArg2[10];  // pThis_47[10] = 取 pArg2[10]
  sub_4ED3F0((int)(pThis_47 + 11), (int)(pArg2 + 11));  // 调 int 向量拷贝赋值（全容量路径）
  sub_4ED3F0((int)(pThis_47 + 15), (int)(pArg2 + 15));  // 调 int 向量拷贝赋值（全容量路径）
  return pThis_47;  // pThis_47=this+71 bMoveType
}



// ------------------------------------------------------------
// 0x4A3900 sub_4A3900 [RTTI: IRDCollisionObject__vmt164 · 槽位 IRDActiveObject+164,IRDCollisionObject+164] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt164 —— 记录当前命中目标（研究已定案）
// ------------------------------------------------------------
// 【解读】
//   【推断】命中记录写入（IRDCollisionObject_vmt164，研究已定案）。
//   流程: 目标对象 vt+380 取记录值 → sub_4A3940 在红黑树中取槽 → 回写。
// ------------------------------------------------------------
void /*stdcall*/ sub_4A3900(int nArg1)  // 实现：记录当前命中目标（研究已定案）
{
  int pObj; // esi
  uint32_t *v2; // edi

  pObj = nArg1;
  if ( nArg1 != 0 )
  {
    nArg1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 380))(nArg1);  // 调用虚函数（虚表槽 +380）
    v2 = (uint32_t *)sub_4A3940(&nArg1);  // 调 在红黑树中取槽 → 回写
    *v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 380))(pObj);  // 调用虚函数（虚表槽 +380）
  }
}



// ------------------------------------------------------------
// 0x4A3940 sub_4A3940
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树 lower_bound 式查找/插入（命中记录树的取槽器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3940(uint32_t *this, uint32_t *uArg2)  // 实现：(推断)红黑树 lower_bound 式查找/插入（命中记录树的取槽器）
{
  uint32_t *uArg22; // edi
  int v4; // eax
  uint32_t v6[2]; // [esp+8h] [ebp-8h] BYREF

  uArg22 = uArg2;
  v4 = sub_4A3990(uArg2);  // 调 (推断)红黑树查找（+21 红黑标志，键 @+12）—— MSVC _Tree::lower_bound 模板实例
  if ( v4 == *(this + 1) || *uArg22 < *(uint32_t *)(v4 + 12) )  // this+4 = pHostObj
  {
    v6[0] = *uArg22;
    v6[1] = 0;
    v4 = *(uint32_t *)sub_4A39C0(&uArg2, v4, v6);  // 调 (推断)红黑树插入重平衡（MSVC _Tree::_Insert 模板实例；多条旋转分支）
  }
  return v4 + 16;  // 返回 v4 + 16
}



// ------------------------------------------------------------
// 0x4A3990 sub_4A3990
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树查找（+21 红黑标志，键 @+12）—— MSVC _Tree::lower_bound 模板实例。
// ------------------------------------------------------------
int */*thiscall*/ sub_4A3990(uint32_t *this, uint32_t *uArg2)  // 实现：(推断)红黑树查找（+21 红黑标志，键 @+12）—— MSVC _Tree::lower_bound 模板实例
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);  // this+4 = pHostObj
  v3 = (int *)result[1];  // result=this+4 宿主对象
  while ( *((uint8_t *)v3 + 21) == 0 )  // 当 *((uint8_t *)v3 + 21) == 0 循环
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      result = v3;  // result=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4A39C0 sub_4A39C0
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树插入重平衡（MSVC _Tree::_Insert 模板实例；多条旋转分支）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A39C0(uint32_t *this, uint32_t *uArg2, int pArg3, uint32_t *uArg4)  // 实现：(推断)红黑树插入重平衡（MSVC _Tree::_Insert 模板实例；多条旋转分支）
{
  int fld_e2; // eax
  uint32_t *fld_e1; // eax
  int v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-Ch] BYREF
  int fld_e12; // [esp+10h] [ebp-4h] BYREF

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  fld_e12 = 0;
  if ( fld_e2 == 0 )  // fld_e2=this+8 物品 id
  {
    sub_4A3B90(uArg2, 1, *(this + 1), uArg4);  // this+4 = pHostObj
    return uArg2;
  }
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  if ( pArg3 == *fld_e1 )  // fld_e1=this+4 宿主对象
  {
    if ( *uArg4 < *(uint32_t *)(pArg3 + 12) )  // pArg3+12〔nSkillRec12(推断)〕
    {
      sub_4A3B90(uArg2, 1, pArg3, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( (uint32_t *)pArg3 == fld_e1 )  // fld_e1=this+4 宿主对象
  {
    v8 = fld_e1[2];  // fld_e1=this+4 宿主对象
    if ( *(uint32_t *)(v8 + 12) < *uArg4 )
    {
      sub_4A3B90(uArg2, 0, v8, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *uArg4 >= *(uint32_t *)(pArg3 + 12) || (fld_e12 = pArg3, sub_4A3B30(&fld_e12), *(uint32_t *)(fld_e12 + 12) >= *uArg4) )  // 若 fld_e12 = pArg3
  {
    if ( *(uint32_t *)(pArg3 + 12) >= *uArg4 || (fld_e12 = pArg3, sub_41C5E0(&fld_e12), fld_e12 != *(this + 1)) && *uArg4 >= *(uint32_t *)(fld_e12 + 12) )  // 调 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4A3D40(v10, uArg4);  // 调 (推断)红黑树插入查找点（返回可插入位置）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(*(uint32_t *)(pArg3 + 8) + 21) != 0 )  // pArg3+8〔nSkillRec8(推断)〕
      sub_4A3B90(uArg2, 0, pArg3, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
    else
      sub_4A3B90(uArg2, 1, fld_e12, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(*(uint32_t *)(fld_e12 + 8) + 21) != 0 )
      sub_4A3B90(uArg2, 0, fld_e12, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
    else
      sub_4A3B90(uArg2, 1, pArg3, uArg4);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4A3B30 sub_4A3B30
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树迭代器自减（MSVC _Tree::iterator-- 模板实例）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3B30(void *this)  // 实现：(推断)红黑树迭代器自减（MSVC _Tree::iterator-- 模板实例）
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 21) != 0 )  // this+21〔bArmorState〕
  {
    result = v1[2];
    *(uint32_t *)this = result;  // *this = result
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 21) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 21) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;  // *this = result
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 21) == 0 );
        if ( *(uint8_t *)(result + 21) == 0 )
          *(uint32_t *)this = result;  // *this = result
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 21) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;  // *this = v3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A3B90 sub_4A3B90
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树插结点 + 全树重平衡（MSVC _Tree::_Insert 的完整实现，110+ 行）。
//   含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A3B90(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // 实现：含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )  // this+8 = 技能槽记录首字
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
    pExceptionObject[0] = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // 调 商店文本（23 行）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8 = 技能槽记录首字
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // this+4 = pHostObj
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // this+4 = pHostObj
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14=this+4 宿主对象
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )  // 无限循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);  // 调 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // 调 STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4 = pHostObj
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4A3D40 sub_4A3D40
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树插入查找点（返回可插入位置）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3D40(uint32_t *this, int pArg2, uint32_t *uArg3)  // 实现：(推断)红黑树插入查找点（返回可插入位置）
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4 = pHostObj
    {
      v10 = *sub_4A3B90(this, &uArg3, 1, fld_e1, (int)uArg32);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 取后继再插
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_4A3B90(this, &uArg3, v13, fld_e1, (int)uArg32);  // 调 含 length_error 抛出路径 —— 标准库模板，语义与 STL 源码一致
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4A3E00 sub_4A3E00
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树容器清理（调 0x4A36D0 版析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3E00(int this)  // 实现：(推断)红黑树容器清理（调 0x4A36D0 版析构）
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4A36D0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // this+16〔nChannelTypeSel(推断)〕
  j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return 0;
}



// ============================================================
// SECTION 0x4A3E40 — 红黑树容器构造/拷贝族 + 288 字节对象深拷贝
// ============================================================
// ------------------------------------------------------------
// 0x4A3E40 sub_4A3E40
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树头结点初始化（sub_433AC0 分配 + 自指 + 红黑标志置 1=黑）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A3E40(char *this)  // 【红黑树容器构造/拷贝族 + 288 字节对象深拷贝】
{
  char *pThis_54; // esi
  int pThis_542; // eax

  pThis_54 = this + 84;  // this+84 插值起点 X
  pThis_542 = sub_433AC0(this + 84);  // 调 map 节点分配（0x18）
  *((uint32_t *)pThis_54 + 1) = pThis_542;  // pThis_54=this+84 插值起点 X
  *(uint8_t *)(pThis_542 + 21) = 1;  // pThis_542+21〔bArmorState(推断)〕
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 4) = *((uint32_t *)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  **((uint32_t **)pThis_54 + 1) = *((uint32_t *)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 8) = *((uint32_t *)pThis_54 + 1);  // pThis_54=this+84 插值起点 X
  *((uint32_t *)pThis_54 + 2) = 0;  // pThis_54=this+84 插值起点 X
  sub_4A2EE0(this);  // 调 (待验证)字段: +0=200、+4=1000、+18(int)=50 —— 与属性块默认值风格一致
  return this;
}



// ------------------------------------------------------------
// 0x4A3EB0 sub_4A3EB0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 288 字节对象深拷贝（72 DWORD 搬运，含 26+26 两段循环）。
//   与 0x4A3050（288 字节清零）配对；先调 0x4A3F80 做扩容/赋值准备。
//   【待验证】本对象与"命中记录/伤害上下文"的关系（0x4A3F80 内含 vector reserve 逻辑）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A3EB0(uint32_t *this, char *pszArg2)  // 实现：(待验证)本对象与命中记录/伤害上下文的关系（0x4A3F80 内含 vector reserve 逻辑）
{
  uint32_t *pThis_710; // esi
  uint32_t *v3; // eax
  int v4; // ecx
  int i; // edx
  uint32_t *v6; // eax
  int j; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_710 = this + 1808;
  sub_4A3F80(pszArg2);  // 调 ③ 否则原地拷贝（多余元素截断）。被 0x4A3EB0 调用于深拷贝准备
  pThis_710[4] = *((uint32_t *)pszArg2 + 4);
  pThis_710[5] = *((uint32_t *)pszArg2 + 5);
  pThis_710[6] = *((uint32_t *)pszArg2 + 6);
  pThis_710[7] = *((uint32_t *)pszArg2 + 7);
  pThis_710[8] = *((uint32_t *)pszArg2 + 8);
  pThis_710[9] = *((uint32_t *)pszArg2 + 9);
  pThis_710[10] = *((uint32_t *)pszArg2 + 10);
  pThis_710[11] = *((uint32_t *)pszArg2 + 11);
  pThis_710[12] = *((uint32_t *)pszArg2 + 12);
  pThis_710[13] = *((uint32_t *)pszArg2 + 13);
  pThis_710[14] = *((uint32_t *)pszArg2 + 14);
  pThis_710[15] = *((uint32_t *)pszArg2 + 15);
  pThis_710[16] = *((uint32_t *)pszArg2 + 16);
  pThis_710[17] = *((uint32_t *)pszArg2 + 17);
  v3 = pThis_710 + 18;  // this+18 子项可拖动标志
  v4 = pszArg2 - (char *)pThis_710;
  for ( i = 26; i != 0; --i )  // 循环：i 从 26 递减到 0
  {
    *v3 = *(uint32_t *)((char *)v3 + v4);
    ++v3;
  }
  v6 = pThis_710 + 44;  // this+44 剩余时间 ms
  for ( j = 26; j != 0; --j )  // 循环：j 从 26 递减到 0
  {
    *v6 = *(uint32_t *)((char *)v6 + v4);
    ++v6;
  }
  pThis_710[70] = *((uint32_t *)pszArg2 + 70);
  pThis_710[71] = *((uint32_t *)pszArg2 + 71);
  return pThis_710;
}



// ------------------------------------------------------------
// 0x4A3F80 sub_4A3F80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 12 字节元素 vector 的拷贝赋值（MSVC operator= 模板）。
//   三段式: ① 源空 → 清目标；② 源 > 现有容量 → 重新 reserve(0x4A3570) + 拷贝；
//   ③ 否则原地拷贝（多余元素截断）。被 0x4A3EB0 调用于深拷贝准备。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3F80(int this, int pArg2)  // 实现：③ 否则原地拷贝（多余元素截断）。被 0x4A3EB0 调用于深拷贝准备
{
  int pArg22; // ebx
  int v4; // eax
  unsigned int v5; // edi
  uint32_t *fld_4; // ecx
  unsigned int fld_8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int fld_44; // edx
  unsigned int fld_C; // eax
  int fld_82; // eax
  int v14; // edx
  uint32_t *v15; // eax
  int fld_42; // eax
  unsigned int v17; // eax
  uint32_t *v18; // [esp+8h] [ebp-4h]
  int fld_43; // [esp+8h] [ebp-4h]
  int i; // [esp+14h] [ebp+8h]

  pArg22 = pArg2;
  if ( this == pArg2 )
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v4 == 0 || (v18 = *(uint32_t **)(pArg2 + 8), (v5 = ((int)v18 - v4) / 12) == 0) )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 调 堆释放
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 12;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v5 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 12;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v5 > fld_C )  // fld_C=this+12 nSkillRec12
    {
      if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
        j__free(*(void **)(this + 4));  // 调 堆释放
      v17 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
      if ( v17 != 0 )
        v17 = (int)(*(uint32_t *)(pArg2 + 8) - v17) / 12;  // pArg2+8〔nSkillRec8(推断)〕
      if ( sub_4A3570((uint32_t *)this, v17) == 0 )  // 调 (推断)元素 = 12 字节三元组（坐标/向量点）
        return this;
      fld_42 = sub_59EE30(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 调 三元组块搬移辅助
    }
    else
    {
      if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
        fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) / 12;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_82 = 0;  // fld_82=this+8 nSkillRec8
      v14 = *(uint32_t *)(pArg2 + 4) + 12 * fld_82;  // pArg2+4〔宿主对象〕
      v15 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
      fld_43 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
      if ( v15 != (uint32_t *)v14 )
      {
        do
        {
          *fld_4 = *v15;  // fld_4=this+16 nChannelTypeSel
          fld_4[1] = v15[1];  // fld_4[1] = 取 v15[1]
          fld_4[2] = v15[2];  // fld_4[2] = 取 v15[2]
          fld_4 = (uint32_t *)(fld_43 + 12);  // fld_4=this+16 nChannelTypeSel
          v15 += 3;
          fld_43 += 12;  // fld_43=this+4 宿主对象
        }
        while ( v15 != (uint32_t *)v14 );
        pArg22 = pArg2;
      }
      fld_42 = sub_59EE30(v14, *(uint32_t *)(pArg22 + 8), *(uint32_t *)(this + 8));  // 调 三元组块搬移辅助
    }
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;
  }
  v9 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  for ( i = *(uint32_t *)(this + 4); v9 != v18; i += 12 )  // this+4〔宿主对象〕等 2 字段
  {
    *fld_4 = *v9;  // fld_4=this+16 nChannelTypeSel
    fld_4[1] = v9[1];  // fld_4[1] = 取 v9[1]
    fld_4[2] = v9[2];  // fld_4[2] = 取 v9[2]
    fld_4 = (uint32_t *)(i + 12);  // fld_4=this+16 nChannelTypeSel
    v9 += 3;
  }
  v10 = *(uint32_t *)(pArg22 + 4);  // pArg22+4〔宿主对象〕
  if ( v10 != 0 )
    fld_44 = *(uint32_t *)(this + 4) + 12 * ((*(uint32_t *)(pArg22 + 8) - v10) / 12);  // this+4〔宿主对象〕等 2 字段
  else
    fld_44 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = fld_44;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return this;
}



// ------------------------------------------------------------
// 0x4A4170 sub_4A4170
// ------------------------------------------------------------
// 【解读】
//   【推断】152 字节步长数组的析构+释放（每元素走 0x4A2EB0，与 0x4A3870 配对）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4170(int *this)  // 实现：(推断)152 字节步长数组的析构+释放（每元素走 0x4A2EB0，与 0x4A3870 配对）
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);  // this+4 = pHostObj
  result = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 152 )  // this+8 = 技能槽记录首字
      sub_4A2EB0(fld_e1);  // fld_e1=this+4 宿主对象
    j__free((void *)*(this + 1));  // this+4 = pHostObj
    result = 0;
  }
  *(this + 1) = 0;  // this+4 = pHostObj
  *(this + 2) = 0;  // this+8 = 技能槽记录首字
  *(this + 3) = 0;  // this+12 = 技能槽记录次字
  return result;
}



// ------------------------------------------------------------
// 0x4A41C0 sub_4A41C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 48+ 字节配置块整体拷贝（this+7520 区）。逐字节搬运 17 字节后接
//   连续 DWORD 段 —— 与 0x4A1160（返回 this+7520）同址，即 0x4A1150/0x4A1160 描述的内嵌块。
//   【推断】装备/染色配置缓存，本函数 = 其"应用副本"。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A41C0(int this, int pArg2)  // 实现：(推断)装备/染色配置缓存，本函数 = 其应用副本
{
  int pThis_1D60; // esi
  uint8_t *pThis_1D73; // ecx
  int i; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_1D60 = this + 7520;  // this+7520 内嵌配置块首 DWORD / 视野值
  *(uint32_t *)(this + 7520) = *(uint32_t *)pArg2;  // this+7520〔nSightRange(推断)〕
  *(uint32_t *)(this + 7524) = *(uint32_t *)(pArg2 + 4);  // this+7524〔uCfgBlock4(推断)〕
  *(uint8_t *)(this + 7528) = *(uint8_t *)(pArg2 + 8);  // this+7528〔bCfgBlock8(推断)〕
  *(uint8_t *)(this + 7529) = *(uint8_t *)(pArg2 + 9);  // this+7529〔bCounterEnable(推断)〕
  *(uint8_t *)(this + 7530) = *(uint8_t *)(pArg2 + 10);  // this+7530〔bCfgBlock10(推断)〕
  *(uint8_t *)(this + 7531) = *(uint8_t *)(pArg2 + 11);  // this+7531〔bCfgBlock11(推断)〕
  *(uint8_t *)(this + 7532) = *(uint8_t *)(pArg2 + 12);  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7533) = *(uint8_t *)(pArg2 + 13);  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7534) = *(uint8_t *)(pArg2 + 14);  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7535) = *(uint8_t *)(pArg2 + 15);  // this+7535〔bCfgBlock15(推断)〕
  *(uint8_t *)(this + 7536) = *(uint8_t *)(pArg2 + 16);  // this+7536〔bCfgBlock16(推断)〕
  *(uint8_t *)(this + 7537) = *(uint8_t *)(pArg2 + 17);  // this+7537〔bCfgBlock17(推断)〕
  *(uint8_t *)(this + 7538) = *(uint8_t *)(pArg2 + 18);  // this+7538〔bCfgBlock18(推断)〕
  pThis_1D73 = (uint8_t *)(this + 7539);  // this+7539〔bCfgTail(推断)〕
  for ( i = 17; i != 0; --i )  // 循环：i 从 17 递减到 0
  {
    *pThis_1D73 = pThis_1D73[pArg2 - pThis_1D60];  // pThis_1D73=this+7539 bCfgTail
    ++pThis_1D73;  // pThis_1D73=this+7539 bCfgTail
  }
  *(uint8_t *)(pThis_1D60 + 36) = *(uint8_t *)(pArg2 + 36);  // pThis_1D60+36〔nStateWord36(推断)〕
  *(uint8_t *)(pThis_1D60 + 37) = *(uint8_t *)(pArg2 + 37);  // pThis_1D60+37〔bFadeFlag37(推断)〕
  *(uint8_t *)(pThis_1D60 + 38) = *(uint8_t *)(pArg2 + 38);  // pThis_1D60+38〔bFadeFlag38(推断)〕
  *(uint8_t *)(pThis_1D60 + 39) = *(uint8_t *)(pArg2 + 39);  // pThis_1D60=this+7520 nSightRange
  *(uint32_t *)(pThis_1D60 + 40) = *(uint32_t *)(pArg2 + 40);  // pThis_1D60+40〔bStateSub40(推断)〕
  *(uint32_t *)(pThis_1D60 + 44) = *(uint32_t *)(pArg2 + 44);  // pThis_1D60+44〔nExpireMs(推断)〕
  *(uint32_t *)(pThis_1D60 + 48) = *(uint32_t *)(pArg2 + 48);  // pThis_1D60+48〔pCmdVecBegin48(推断)〕
  *(uint32_t *)(pThis_1D60 + 52) = *(uint32_t *)(pArg2 + 52);  // pThis_1D60+52〔bAuraState(推断)〕
  *(uint32_t *)(pThis_1D60 + 56) = *(uint32_t *)(pArg2 + 56);  // pThis_1D60+56〔pCmdVecCap56(推断)〕
  *(uint32_t *)(pThis_1D60 + 60) = *(uint32_t *)(pArg2 + 60);  // pThis_1D60+60〔nFadeValue60(推断)〕
  *(uint32_t *)(pThis_1D60 + 64) = *(uint32_t *)(pArg2 + 64);  // pThis_1D60+64〔apServerTabBtn(推断)〕
  *(uint32_t *)(pThis_1D60 + 68) = *(uint32_t *)(pArg2 + 68);  // pThis_1D60+68〔nCharCount(推断)〕
  *(uint32_t *)(pThis_1D60 + 72) = *(uint32_t *)(pArg2 + 72);  // pThis_1D60+72〔nSnapshot72(推断)〕
  *(uint32_t *)(pThis_1D60 + 76) = *(uint32_t *)(pArg2 + 76);  // pThis_1D60+76〔pBtnActionE〕
  *(uint32_t *)(pThis_1D60 + 80) = *(uint32_t *)(pArg2 + 80);  // pThis_1D60+80〔nAuraStage(推断)〕
  sub_4A42B0(pArg2 + 84);  // pArg2+84〔pFxObjA(推断)〕
  return pThis_1D60;  // pThis_1D60=this+7520 nSightRange
}



// ------------------------------------------------------------
// 0x4A42B0 sub_4A42B0
// ------------------------------------------------------------
// 【解读】
//   【推断】关联容器赋值（sub_41DA40 清旧 + 0x4A42E0 建新）—— MSVC map operator= 模板。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4A42B0(int ***this, int ***uArg2)  // 实现：(推断)关联容器赋值（sub_41DA40 清旧 + 0x4A42E0 建新）—— MSVC map operator= 模板
{
  int ***uArg22; // edi

  uArg22 = uArg2;
  if ( this != uArg2 )
  {
    sub_41DA40(this, (int **)&uArg2, **(this + 1), (int *)*(this + 1));  // 调 同族实例二（回调 0x41CAA0）
    sub_4A42E0(uArg22);  // 调 (推断)红黑树拷贝（_Copy 模板实例，重挂根 + 极值指针修正）
  }
  return this;
}



// ------------------------------------------------------------
// 0x4A42E0 sub_4A42E0
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树拷贝（_Copy 模板实例，重挂根 + 极值指针修正）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4A42E0(int ***this, int pArg2)  // 实现：(推断)红黑树拷贝（_Copy 模板实例，重挂根 + 极值指针修正）
{
  int fld_e1; // edi
  int **fld_e12; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_e13; // esi
  int **v8; // ecx

  fld_e1 = (int)*(this + 1);  // this+4 = pHostObj
  *(uint32_t *)(fld_e1 + 4) = sub_4A4370(*(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4), fld_e1);  // pArg2+4〔宿主对象〕
  *(this + 2) = *(int ***)(pArg2 + 8);  // this+8 = 技能槽记录首字
  fld_e12 = *(this + 1);  // this+4 = pHostObj
  result = fld_e12[1];  // fld_e12=this+4 宿主对象
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *fld_e12 = (int *)fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4 = pHostObj
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 21) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 21) == 0 );
    }
    *fld_e12 = result;  // fld_e12=this+4 宿主对象
    fld_e13 = (int)*(this + 1);  // this+4 = pHostObj
    v8 = *(int ***)(fld_e13 + 4);  // fld_e13=this+4 宿主对象
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_e13 + 8) = v8;  // fld_e13=this+4 宿主对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A4370 sub_4A4370
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树递归复制（_Copy 模板的递归体，sub_5648C0 分配结点）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4370(void **this, int *pDwArg2, int nArg3)  // 实现：(推断)红黑树递归复制（_Copy 模板的递归体，sub_5648C0 分配结点）
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);  // this+4〔宿主对象〕
  v3 = *((uint8_t *)pDwArg2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = (uint32_t *)sub_5648C0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 20));  // 调 商店文本（23 行）
    if ( *((uint8_t *)Block + 21) != 0 )  // Block=this+4 宿主对象
      Block = fld_e1;  // Block=this+4 宿主对象
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_4A4370(v6, fld_e1);  // 调 (推断)红黑树递归复制（_Copy 模板的递归体，sub_5648C0 分配结点）
    fld_e1[2] = sub_4A4370(pDwArg2[2], fld_e1);  // fld_e1[2] = 调 sub_4A4370 返回值
  }
  return Block;  // Block=this+4 宿主对象
}



// ============================================================
// SECTION 0x4A4430 — ★ IRDCollisionObject 构造/析构（0x4A4430 / 0x4A4590 / 0x4A4710）
// ============================================================
// ------------------------------------------------------------
// 0x4A4430 sub_4A4430
// ------------------------------------------------------------
// 【解读】
//   【推断】★ IRDCollisionObject 构造函数 —— 写 vftable（RTTI 直证）并调 sub_42AAB0 基类。
//   被 0x4A49B0（IRDActiveObject 构造）作为第一步调用 —— 继承链构造顺序的实物证据。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A4430(uint32_t *this)  // 函数 sub_4A4430：★ IRDCollisionObject 构造/析构（0x4A4430 / 0x4A4590 / 0x4A4710）
{
  int pThis_87; // eax
  int pThis_95; // eax

  sub_42AAB0();  // 调 CNRDObject 构造（三内嵌 CNTimer）
  *this = &IRDCollisionObject::`vftable';  // vftable 复位
  sub_4A37D0((int)(this + 71));  // this+71〔bMoveType〕
  *(this + 96) = 15;  // this+384 = 动画件名 SSO 容量判据
  *(this + 95) = 0;
  *((uint8_t *)this + 364) = 0;  // this+364 = 动画件名缓冲 SSO 内联首址
  *(this + 126) = 15;  // this+126 复位组字节
  *(this + 125) = 0;  // this+125 复位组字节
  *((uint8_t *)this + 484) = 0;
  sub_4A3450(this + 97);  // this+97〔bFlag97〕
  pThis_87 = sub_433AC0(this + 135);  // 调 map 节点分配（0x18）
  *(this + 136) = pThis_87;  // this+544〔nFaction〕
  *(uint8_t *)(pThis_87 + 21) = 1;  // pThis_87+21〔bArmorState(推断)〕
  *(uint32_t *)(*(this + 136) + 4) = *(this + 136);  // this+544〔nFaction〕
  *(uint32_t *)*(this + 136) = *(this + 136);  // this+544〔nFaction〕
  *(uint32_t *)(*(this + 136) + 8) = *(this + 136);  // this+544〔nFaction〕
  *(this + 137) = 0;  // this+548〔pEqVec548〕
  *(this + 139) = 0;  // this+556〔nGrabAnimBase〕
  *(this + 140) = 0;  // this+140 第 3 组·+900 增量
  *(this + 141) = 0;  // this+141 淡出标志 A
  pThis_95 = sub_433AC0(this + 149);  // 调 map 节点分配（0x18）
  *(this + 150) = pThis_95;
  *(uint8_t *)(pThis_95 + 21) = 1;  // pThis_95+21〔bArmorState(推断)〕
  *(uint32_t *)(*(this + 150) + 4) = *(this + 150);
  *(uint32_t *)*(this + 150) = *(this + 150);
  *(uint32_t *)(*(this + 150) + 8) = *(this + 150);
  *(this + 151) = 0;
  *(this + 156) = 0;  // this+156 第 4 组·+858/+1292 增量
  *(this + 157) = 0;
  *(this + 158) = 0;
  *(this + 164) = 0;  // this+164 第 5 组·+88 增量子倍率
  *(this + 165) = 0;
  *(this + 166) = 0;
  sub_4E7160((int)this);  // 调 受击/动作字段复位（研究 §1.2 字段表坐标逐个可读）
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A4560 sub_4A4560 [RTTI: IRDCollisionObject__vmt25C · 槽位 IRDCollisionObject+25C]
// ------------------------------------------------------------
// 【解读】
//   【推断】写 this+641 —— IRDCollisionObject_vmt25C（受击盒使能）的单字节写版本
//   （无附属物广播）。IRDCollisionObject.h: "dangerFlag +0x281(641)"。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A4560(uint8_t *this, char pszArg2)  // 函数 sub_4A4560：[RTTI IRDCollisionObject__vmt25C 槽位 IRDCollisionObject+25C]
{
  *(this + 641) = pszArg2;  // this+641 受击盒使能 = 无敌开关
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A4570 sub_4A4570 [RTTI: IRDCollisionObject__vmt288 · 槽位 IRDCollisionObject+288] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt288 —— 写入 100（格挡/减伤基础值槽）
// ------------------------------------------------------------
int /*stdcall*/ sub_4A4570(uint32_t *uArg1, int nArg2)  // 函数: 写入 100（格挡/减伤基础值槽）
{
  *uArg1 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x4A4590 sub_4A4590 [已精修] 见 src/cnrd/IRDCollisionObject.h vmt0 实体 —— IRDCollisionObject 析构本体（0x4A4710 vmt0 转发至此）
// ------------------------------------------------------------
// 【解读】
//   【推断】IRDCollisionObject 析构体（被 0x4A4710 = vmt0 调用）。
//   逐段释放命中列表/红黑树/vector —— 尺寸线索汇总在 docs/14。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4590(int this)  // 实现：IRDCollisionObject 析构本体（0x4A4710 vmt0 转发至此）
{
  int *v3; // [esp-Ch] [ebp-28h]
  int *v4; // [esp-Ch] [ebp-28h]
  int *fld_258; // [esp-8h] [ebp-24h]
  int *fld_220; // [esp-8h] [ebp-24h]
  int *v7[2]; // [esp+8h] [ebp-14h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  v7[1] = (int *)this;
  *(uint32_t *)this = &IRDCollisionObject::`vftable';  // vftable 复位
  v8 = 8;
  nullsub_3(this);
  if ( *(uint32_t *)(this + 656) != 0 )
    j__free(*(void **)(this + 656));  // 调 堆释放
  *(uint32_t *)(this + 656) = 0;
  *(uint32_t *)(this + 660) = 0;
  *(uint32_t *)(this + 664) = 0;
  if ( *(uint32_t *)(this + 624) != 0 )
    j__free(*(void **)(this + 624));  // 调 堆释放
  *(uint32_t *)(this + 624) = 0;
  *(uint32_t *)(this + 628) = 0;
  *(uint32_t *)(this + 632) = 0;
  fld_258 = *(int **)(this + 600);
  v3 = (int *)*fld_258;
  LOBYTE(v8) = 5;  // 调 取 16 位值低 8 位
  sub_4A36D0((int ***)(this + 596), v7, v3, fld_258);  // 调 (推断)红黑树递归析构（第二版）—— 与 0x4A3610 对偶（不同节点大小）
  j__free(*(void **)(this + 600));  // 调 堆释放
  *(uint32_t *)(this + 600) = 0;
  *(uint32_t *)(this + 604) = 0;
  sub_4A4170((int *)(this + 552));  // this+552〔bItemAlarm(推断)〕
  fld_220 = *(int **)(this + 544);  // this+544〔nFaction〕
  v4 = (int *)*fld_220;  // fld_220=this+544 nFaction
  LOBYTE(v8) = 3;  // 调 取 16 位值低 8 位
  sub_4A3610((int ***)(this + 540), v7, v4, fld_220);  // 调 释放旧树后·sub
  j__free(*(void **)(this + 544));  // 调 堆释放
  *(uint32_t *)(this + 544) = 0;  // this+544〔nFaction〕
  *(uint32_t *)(this + 548) = 0;  // this+548〔pEqVec548〕
  if ( *(uint32_t *)(this + 504) >= 0x10u )
    j__free(*(void **)(this + 484));  // 调 堆释放
  *(uint32_t *)(this + 504) = 15;
  *(uint32_t *)(this + 500) = 0;
  *(uint8_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 384) >= 0x10u )  // this+384〔nAnimNameCap(推断)〕
    j__free(*(void **)(this + 364));  // 调 堆释放
  *(uint32_t *)(this + 384) = 15;  // this+384〔nAnimNameCap(推断)〕
  *(uint32_t *)(this + 380) = 0;
  *(uint8_t *)(this + 364) = 0;  // this+364〔pAnimNameStr(推断)〕等 2 字段
  sub_4A2E50(this + 284);  // this+284 绑定/记录门字节
  v8 = -1;
  return sub_42A450(this);  // 调 CNRDObject 析构主体
}



// ------------------------------------------------------------
// 0x4A4710 sub_4A4710 [RTTI: IRDCollisionObject__vmt0 · 槽位 IRDCollisionObject+0] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt0 —— IRDCollisionObject 析构 → 0x4A4590
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4710(void *Block, char pszArg2)  // 实现：IRDCollisionObject 析构 → 0x4A4590
{
  sub_4A4590((int)Block);  // IRDCollisionObject 析构本体（0x4A4710 vmt0 转发至此）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A4740 sub_4A4740
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 对象成员批量析构的第一段（IRDActiveObject 析构链前置）。
//   连续对 this+0/4/8/12/16/20/24 等 8 个指针槽做 sub_42AF90（解绑）+ sub_657740（释放），
//   再处理内嵌数组 —— 130 行 = 成员数量最多的析构段。
//   【待验证】sub_42AF90 语义（疑为场景/渲染对象注销）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A4740(int this)  // 实现：(待验证)sub_42AF90 语义（疑为场景/渲染对象注销）
{
  void **v2; // edi
  void **fld_4; // edi
  void **fld_8; // edi
  void ***pThis_C; // edi
  void **v6; // ebx
  unsigned int result; // eax
  int fld_14; // edi
  unsigned int v9; // ebx
  void **fld_18; // edi
  void **fld_1C; // edi
  void **fld_20; // edi
  int fld_28; // ecx
  void **v14; // ecx
  unsigned int i; // ebx
  int fld_38; // ecx
  void **v17; // ecx
  int v18; // [esp+Ch] [ebp-4h]
  void **v19; // [esp+Ch] [ebp-4h]
  void **v20; // [esp+Ch] [ebp-4h]

  v2 = *(void ***)this;
  if ( *(uint32_t *)this != 0 )
  {
    sub_42AF90(*(void ***)this);  // 调 帧对象析构（帧数组 + 元素数组）
    sub_657740(v2, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_4 = *(void ***)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  *(uint32_t *)this = 0;  // *this = 0
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
  {
    sub_42AF90(fld_4);  // 调 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_4, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_8 = *(void ***)(this + 8);  // this+32〔nHeight(推断)〕
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  if ( fld_8 != nullptr )  // 若 fld_8 有效（非空）
  {
    sub_42AF90(fld_8);  // 调 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_8, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  pThis_C = (void ***)(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  v18 = 2;
  do
  {
    v6 = *pThis_C;  // pThis_C=this+48 pCmdVecBegin48
    if ( *pThis_C != nullptr )  // pThis_C=this+48 pCmdVecBegin48
    {
      sub_42AF90(*pThis_C);  // 调 帧对象析构（帧数组 + 元素数组）
      sub_657740(v6, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_C++ = nullptr;  // pThis_C=this+48 pCmdVecBegin48
    result = v18 - 1;
    v18 = result;
  }
  while ( result != 0 );
  fld_14 = *(uint32_t *)(this + 20);  // this+80 = nAuraStage
  v9 = 0;
  if ( fld_14 != 0 )  // fld_14=this+80 关联角色对象
  {
    sub_42AF90(*(void ***)(this + 20));  // 调 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_14, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_18 = *(void ***)(this + 24);  // this+96〔nStatusMode(推断)〕
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  if ( fld_18 != nullptr )  // 若 fld_18 有效（非空）
  {
    sub_42AF90(fld_18);  // 调 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_18, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_1C = *(void ***)(this + 28);  // this+112 = pHostComp
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  if ( fld_1C != nullptr )  // 若 fld_1C 有效（非空）
  {
    sub_42AF90(fld_1C);  // 调 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_1C, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_20 = *(void ***)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
  *(uint32_t *)(this + 28) = 0;  // this+112 = pHostComp
  if ( fld_20 != nullptr )  // 若 fld_20 有效（非空）
  {
    sub_42AF90(fld_20);  // 调 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_20, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  while ( 1 )  // 无限循环
  {
    fld_28 = *(uint32_t *)(this + 40);  // this+40〔bStateSub40(推断)〕等 2 字段
    if ( fld_28 == 0 )  // fld_28=this+40 bStateSub40
      break;
    result = (*(uint32_t *)(this + 44) - fld_28) >> 2;  // this+44〔nExpireMs(推断)〕等 2 字段
    if ( v9 >= result )  // result=this+44 nExpireMs
      break;
    v14 = *(void ***)(fld_28 + 4 * v9);  // fld_28=this+40 bStateSub40
    if ( v14 != nullptr )  // 若 v14 有效（非空）
    {
      v19 = v14;
      sub_42AF90(v14);  // 调 帧对象析构（帧数组 + 元素数组）
      sub_657740(v19, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    result = 4 * v9 + *(uint32_t *)(this + 40);
    *(uint32_t *)result = 0;  // *result = 0
    ++v9;
  }
  for ( i = 0; ; ++i )
  {
    fld_38 = *(uint32_t *)(this + 56);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    if ( fld_38 == 0 )  // fld_38=this+56 pCmdVecCap56
      break;
    result = (*(uint32_t *)(this + 60) - fld_38) >> 2;  // this+240 = 基类时刻同步参数 B
    if ( i >= result )  // result=this+240 动画同步参数 B
      break;
    v17 = *(void ***)(fld_38 + 4 * i);  // fld_38=this+56 pCmdVecCap56
    if ( v17 != nullptr )  // 若 v17 有效（非空）
    {
      v20 = v17;
      sub_42AF90(v17);  // 调 帧对象析构（帧数组 + 元素数组）
      sub_657740(v20, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    result = 4 * i + *(uint32_t *)(this + 56);
    *(uint32_t *)result = 0;  // *result = 0
  }
  return result;  // result=this+240 动画同步参数 B
}


// ------------------------------------------------------------
// 0x4A4940 sub_4A4940
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4A4740 的收尾（再补两个 vector 释放）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A4940(int this)  // 实现：(推断)0x4A4740 的收尾（再补两个 vector 释放）
{
  sub_4A4740(this);  // 调 (待验证)sub_42AF90 语义（疑为场景/渲染对象注销）
  if ( *(uint32_t *)(this + 56) != 0 )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 56));  // 调 堆释放
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  if ( *(uint32_t *)(this + 40) != 0 )  // this+40〔bStateSub40(推断)〕等 2 字段
    j__free(*(void **)(this + 40));  // 调 堆释放
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
}



// ============================================================
// SECTION 0x4A49B0 — ★★ IRDActiveObject 构造/析构（0x4A49B0 / 0x4A4BD0 / 0x4A4E70）
// ============================================================
// ------------------------------------------------------------
// 0x4A49B0 sub_4A49B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★★ IRDActiveObject 构造函数（RTTI 直证）。完整成员布局直证点:
//   ① sub_4A4430 基类构造（IRDCollisionObject）→ 写 IRDActiveObject vftable；
//   ② eh vector constructor iterator(this+676, 0x554, 4, 0x4A1670, 0x4A1F00)
//      = **4 个 0x554(1364) 字节内嵌子对象**，构造 0x4A1670 / 析构 0x4A1F00；
//      —— 与 vmt2A0（0x4A0C80: this+1364*a2+676）完全互证！
//   ③ sub_4A1C30(this+6132) = 属性块（vt+672 返回处）；
//   ④ +6160 块（sub_4A2FF0）、+6316（sub_4A3450 攻击上下文）、+6544（sub_4A2CF0 光环链表）；
//   ⑤ +6560 内嵌动作子对象（off_6C2B88 内嵌对象 vftable）、+7076 附属物 vector；
//   ⑥ 收尾 sub_4D46C0 / sub_4D7140（0x4D 区战斗段初始化）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A49B0(int this)  // 函数 sub_4A49B0：★★ IRDActiveObject 构造/析构（0x4A49B0 / 0x4A4BD0 / 0x4A4E70）
{
  sub_4A4430((uint32_t *)this);  // 调 ★ IRDCollisionObject 构造/析构（0x4A4430 / 0x4A4590 / 0x4A4710）
  *(uint32_t *)this = &IRDActiveObject::`vftable';  // vftable 复位
  `eh vector constructor iterator'(
    (void *)(this + 676),  // this+676〔nResetFlag676〕
    0x554u,
    4,
    (void (/*thiscall*/ *)(void *))sub_4A1670,  // 调 16 元素两个内嵌数组 —— 数组元素大小 0xE(14) 字节，与 0x4A1210 的步长直证一致
    (void (/*thiscall*/ *)(void *))sub_4A1F00);  // 调 这是 0x4A49B0（IRDActiveObject 构造）注册的析构回调（eh vector constructor itera…
  sub_4A1C30((uint32_t *)(this + 6132));  // this+6132〔nAttrBlock6132〕
  *(uint32_t *)(this + 6200) = 0;  // this+6200〔pTbl6200〕
  *(uint32_t *)(this + 6204) = 0;
  *(uint32_t *)(this + 6208) = 0;
  *(uint32_t *)(this + 6216) = 0;  // this+6216〔pTbl6216(推断)〕
  *(uint32_t *)(this + 6220) = 0;  // this+6220〔pFrameVecEnd(推断)〕
  *(uint32_t *)(this + 6224) = 0;
  sub_4A2FF0((void *)(this + 6160));  // 调 (推断)结构体清零 + 两个 vector 释放（MSVC vector 三指针布局 @+40/+56）
  *(uint32_t *)(this + 6304) = 0;
  *(uint32_t *)(this + 6308) = 0;
  *(uint32_t *)(this + 6312) = 0;
  *(uint32_t *)(this + 6432) = 15;
  *(uint32_t *)(this + 6428) = 0;
  *(uint8_t *)(this + 6412) = 0;
  sub_4A3450((uint32_t *)(this + 6316));  // 调 attackinfo 默认值（sub_4A3450 @0x4A3450…
  *(uint32_t *)(this + 6544) = sub_4A2CF0();  // 调 注册为 +204
  *(uint32_t *)(this + 6548) = 0;
  *(uint8_t *)(this + 6564) = 0;
  *(uint32_t *)(this + 6560) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 6568) = 0;
  *(uint8_t *)(this + 6572) = 1;
  *(uint8_t *)(this + 6574) = 0;
  *(uint8_t *)(this + 6573) = 0;
  *(uint32_t *)(this + 6584) = 0;
  *(uint32_t *)(this + 6580) = 0;
  *(uint32_t *)(this + 6576) = 0;
  *(uint32_t *)(this + 6736) = 15;  // this+6736〔nBirthSndCap〕
  *(uint32_t *)(this + 6732) = 0;
  *(uint8_t *)(this + 6716) = 0;  // this+6716〔szBirthSnd6716〕
  *(uint32_t *)(this + 6788) = 15;
  *(uint32_t *)(this + 6784) = 0;
  *(uint8_t *)(this + 6768) = 0;
  *(uint32_t *)(this + 6860) = 15;
  *(uint32_t *)(this + 6856) = 0;
  *(uint8_t *)(this + 6840) = 0;
  *(uint32_t *)(this + 6928) = 15;
  *(uint32_t *)(this + 6924) = 0;
  *(uint8_t *)(this + 6908) = 0;
  *(uint32_t *)(this + 6956) = 15;
  *(uint32_t *)(this + 6952) = 0;
  *(uint8_t *)(this + 6936) = 0;
  *(uint32_t *)(this + 6984) = 15;
  *(uint32_t *)(this + 6980) = 0;
  *(uint8_t *)(this + 6964) = 0;
  *(uint32_t *)(this + 7024) = 15;
  *(uint32_t *)(this + 7020) = 0;
  *(uint8_t *)(this + 7004) = 0;
  sub_41A630(this + 7028);  // this+7028〔nAttackSegSlot〕
  *(uint32_t *)(this + 7028) = &clong::`vftable';  // vftable 复位
  *(uint32_t *)(this + 7068) = 15;
  *(uint32_t *)(this + 7064) = 0;
  *(uint8_t *)(this + 7048) = 0;
  *(uint32_t *)(this + 7076) = 0;
  *(uint32_t *)(this + 7080) = 0;
  *(uint32_t *)(this + 7084) = 0;
  *(uint8_t *)(this + 7120) = 0;
  *(uint32_t *)(this + 7116) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 7124) = 0;
  *(uint8_t *)(this + 7128) = 1;
  *(uint8_t *)(this + 7130) = 0;
  *(uint8_t *)(this + 7129) = 0;
  *(uint32_t *)(this + 7140) = 0;
  *(uint32_t *)(this + 7136) = 0;
  *(uint32_t *)(this + 7132) = 0;
  sub_4D46C0((uint32_t *)this);  // 调 ★ ActiveObject 构造初始化（研究 20 §13 定案）
  sub_4D7140(this);  // 调 （this+112）的 +200 写 500（(推断)默认值：HP/计时参数），置 this+6740 使能位
  return this;
}



// ------------------------------------------------------------
// 0x4A4BD0 sub_4A4BD0
// ------------------------------------------------------------
// 【解读】
//   【推断】IRDActiveObject 析构（RTTI 直证）。sub_4D7000 先做战斗段清理，
//   再释放 +7076 附属物 vector 与 +7048 串 —— 与 0x4A4E70（vmt0 壳）配对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4BD0(int this)  // 实现：再释放 +7076 附属物 vector 与 +7048 串 —— 与 0x4A4E70（vmt0 壳）配对
{
  *(uint32_t *)this = &IRDActiveObject::`vftable';  // vftable 复位
  sub_4D7000((uint32_t *)this);  // 调 ★ ActiveObject 析构（研究 20 §13 定案）
  *(uint32_t *)(this + 7116) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 7120) = 0;
  if ( *(uint32_t *)(this + 7076) != 0 )
    j__free(*(void **)(this + 7076));  // 调 堆释放
  *(uint32_t *)(this + 7076) = 0;
  *(uint32_t *)(this + 7080) = 0;
  *(uint32_t *)(this + 7084) = 0;
  if ( *(uint32_t *)(this + 7068) >= 0x10u )
    j__free(*(void **)(this + 7048));  // 调 堆释放
  *(uint32_t *)(this + 7068) = 15;
  *(uint32_t *)(this + 7064) = 0;
  *(uint8_t *)(this + 7048) = 0;
  sub_41A580((uint32_t *)(this + 7028));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  if ( *(uint32_t *)(this + 7024) >= 0x10u )
    j__free(*(void **)(this + 7004));  // 调 堆释放
  *(uint32_t *)(this + 7024) = 15;
  *(uint32_t *)(this + 7020) = 0;
  *(uint8_t *)(this + 7004) = 0;
  if ( *(uint32_t *)(this + 6984) >= 0x10u )
    j__free(*(void **)(this + 6964));  // 调 堆释放
  *(uint32_t *)(this + 6984) = 15;
  *(uint32_t *)(this + 6980) = 0;
  *(uint8_t *)(this + 6964) = 0;
  if ( *(uint32_t *)(this + 6956) >= 0x10u )
    j__free(*(void **)(this + 6936));  // 调 堆释放
  *(uint32_t *)(this + 6956) = 15;
  *(uint32_t *)(this + 6952) = 0;
  *(uint8_t *)(this + 6936) = 0;
  if ( *(uint32_t *)(this + 6928) >= 0x10u )
    j__free(*(void **)(this + 6908));  // 调 堆释放
  *(uint32_t *)(this + 6928) = 15;
  *(uint32_t *)(this + 6924) = 0;
  *(uint8_t *)(this + 6908) = 0;
  if ( *(uint32_t *)(this + 6860) >= 0x10u )
    j__free(*(void **)(this + 6840));  // 调 堆释放
  *(uint32_t *)(this + 6860) = 15;
  *(uint32_t *)(this + 6856) = 0;
  *(uint8_t *)(this + 6840) = 0;
  if ( *(uint32_t *)(this + 6788) >= 0x10u )
    j__free(*(void **)(this + 6768));  // 调 堆释放
  *(uint32_t *)(this + 6788) = 15;
  *(uint32_t *)(this + 6784) = 0;
  *(uint8_t *)(this + 6768) = 0;
  if ( *(uint32_t *)(this + 6736) >= 0x10u )  // this+6736〔nBirthSndCap〕
    j__free(*(void **)(this + 6716));  // 调 堆释放
  *(uint32_t *)(this + 6736) = 15;  // this+6736〔nBirthSndCap〕
  *(uint32_t *)(this + 6732) = 0;
  *(uint8_t *)(this + 6716) = 0;  // this+6716〔szBirthSnd6716〕
  *(uint32_t *)(this + 6560) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 6564) = 0;
  sub_6569D0(this + 6540);  // 调 清 +28
  j__free(*(void **)(this + 6544));  // 调 堆释放
  *(uint32_t *)(this + 6544) = 0;
  if ( *(uint32_t *)(this + 6432) >= 0x10u )
    j__free(*(void **)(this + 6412));  // 调 堆释放
  *(uint32_t *)(this + 6432) = 15;
  *(uint32_t *)(this + 6428) = 0;
  *(uint8_t *)(this + 6412) = 0;
  sub_4A4170((int *)(this + 6300));  // 调 (推断)152 字节步长数组的析构+释放（每元素走 0x4A2EB0，与 0x4A3870 配对）
  sub_4A4940(this + 6160);  // 调 析构 —— ·0x4EF9D0 按动画行数对齐 +1288 行向量
  sub_41A580((uint32_t *)(this + 6146));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)(this + 6132));  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'((void *)(this + 676), 0x554u, 4, (void (/*thiscall*/ *)(void *))sub_4A1F00);  // this+676〔nResetFlag676〕
  return sub_4A4590(this);  // IRDCollisionObject 析构本体（0x4A4710 vmt0 转发至此）
}



// ------------------------------------------------------------
// 0x4A4E70 sub_4A4E70 [RTTI: IRDActiveObject__vmt0 · 槽位 IRDActiveObject+0]
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4E70(void *Block, char pszArg2)  // 函数 sub_4A4E70：[RTTI IRDActiveObject__vmt0 槽位 IRDActiveObject+0]
{
  sub_4A4BD0((int)Block);  // 调 再释放 +7076 附属物 vector 与 +7048 串 —— 与 0x4A4E70（vmt0 壳）配对
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ============================================================
// SECTION 0x4A4EA0 — ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
// ============================================================
// ------------------------------------------------------------
// 0x4A4EA0 sub_4A4EA0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ IRDMonster 构造（怪物基类，RTTI 直证）。继承链: IRDActiveObject ← IRDMonster。
//   ① sub_4A49B0（IRDActiveObject 构造）→ 写 IRDMonster vftable；
//   ② +7172 置 15 / +7176 归零 —— 内嵌 string 初始化；
//   后续大段成员初始化（84 行）。所有具体怪物类（CNGoblin*/CNSpider/...）的构造都从本函数出发。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A4EA0(char *this, char ArgList, int nArg3)  // 函数 sub_4A4EA0：★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
{
  sub_4A49B0((int)this);  // 调 ★★ IRDActiveObject 构造/析构（0x4A49B0 / 0x4A4BD0 / 0x4A4E70）
  *(uint32_t *)this = &IRDMonster::`vftable';  // vftable 复位
  *((uint32_t *)this + 1794) = 15;  // this+7176〔nNameStrCap〕
  *((uint32_t *)this + 1793) = 0;  // this+7172〔nNameStrSize〕
  *(this + 7156) = 0;  // this+7156 0x5796C0 写入字节
  *(this + 7180) = 0;
  *(this + 7181) = 0;
  *(this + 7182) = 0;
  *(this + 7183) = 0;
  *((uint32_t *)this + 1798) = 0;
  *((uint32_t *)this + 1799) = 6;
  *((uint32_t *)this + 1800) = 12;
  *((uint32_t *)this + 1801) = 0;
  *((uint32_t *)this + 1802) = 1600;
  *((uint32_t *)this + 1803) = 0;
  *((uint32_t *)this + 1804) = 0;
  *((uint32_t *)this + 1805) = 0;
  *((uint32_t *)this + 1806) = 0;
  *((uint32_t *)this + 1807) = 0;
  *((uint32_t *)this + 1809) = 0;
  *((uint32_t *)this + 1810) = 0;
  *((uint32_t *)this + 1811) = 0;
  sub_4A3050((int)(this + 7232));  // 调 (待验证)与 0x4A3EB0 的 72 DWORD 拷贝对应（同为 288 字节对象）
  sub_4A3E40(this + 7520);  // 【红黑树容器构造/拷贝族 + 288 字节对象深拷贝】
  *((uint32_t *)this + 1905) = 0;  // this+7620 = 速度/属性参数对象
  *((uint32_t *)this + 1906) = 0;
  *((uint32_t *)this + 1907) = 0;
  *(this + 7644) = 0;
  *((uint32_t *)this + 1910) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 1912) = 0;
  *(this + 7652) = 1;
  *(this + 7654) = 0;
  *(this + 7653) = 0;
  *((uint32_t *)this + 1916) = 0;
  *((uint32_t *)this + 1915) = 0;
  *((uint32_t *)this + 1914) = 0;
  *((uint32_t *)this + 1940) = 15;
  *((uint32_t *)this + 1939) = 0;
  *(this + 7740) = 0;
  *(uint32_t *)(this + 7777) = 0;
  *(uint32_t *)(this + 7781) = 0;
  *(uint32_t *)(this + 7785) = 0;
  *(uint32_t *)(this + 7789) = 0;
  *(uint32_t *)(this + 7793) = 0;
  *(uint32_t *)(this + 7797) = 0;
  *((uint32_t *)this + 1952) = 0;  // this+7808〔风格/分支选择〕
  *((uint32_t *)this + 1953) = 0;  // this+7812〔nSubStateA(推断)〕
  *((uint32_t *)this + 1954) = 0;  // this+7816〔nSubStateB(推断)〕
  `eh vector constructor iterator'(this + 7824, 0x10u, 29, (void (/*thiscall*/ *)(void *))sub_4019A0, sub_401940);  // 指针 vector 三字段清零（起/止/容量 = 0）
  *((uint32_t *)this + 2085) = 0;  // this+8340〔pAnimA(推断)〕
  *((uint32_t *)this + 2086) = 0;  // this+8344〔nRideMode(推断)〕
  *((uint32_t *)this + 2087) = 0;  // this+8348〔nPhaseParity(推断)〕
  *(this + 8492) = 0;
  *((uint32_t *)this + 2122) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 2124) = 0;  // this+8496〔nChargeState〕
  *(this + 8500) = 1;  // this+8500 【推断】充能计时
  *(this + 8502) = 0;
  *(this + 8501) = 0;
  *((uint32_t *)this + 2128) = 0;  // this+8512〔pAnimF(推断)〕
  *((uint32_t *)this + 2127) = 0;
  *((uint32_t *)this + 2126) = 0;  // this+8504〔f_2138〕
  *((uint32_t *)this + 2138) = 15;
  *((uint32_t *)this + 2137) = 0;  // this+8548〔nPhaseEndB〕
  *(this + 8532) = 0;  // this+8532 0x5DE690 相位值 B
  *(this + 8560) = 0;
  *((uint32_t *)this + 2139) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 2141) = 0;
  *(this + 8568) = 1;  // this+8568 相位组索引
  *(this + 8570) = 0;  // this+8570 仅见复位
  *(this + 8569) = 0;  // this+8569 仅见复位
  *((uint32_t *)this + 2145) = 0;  // this+8580〔nPhaseStage〕
  *((uint32_t *)this + 2144) = 0;  // this+8576〔nFadeAlpha〕
  *((uint32_t *)this + 2143) = 0;  // this+8572〔nPhaseElapsed〕
  sub_4DE700(this);  // 调 怪物扩展字段重置（+ 飞行/召唤标记图懒加载）
  sub_4DB410(ArgList, nArg3);  // 调 怪物生成入口（MONSTER CREATE）
  return this;
}



// ------------------------------------------------------------
// 0x4A50F0 sub_4A50F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ IRDMonster 析构体。逆向释放序: IObject 子对象(+8556)、string(+8532)、
//   IObject(+8488)、vector(+8340)、29 元素×16 字节 eh vector(+7824)、string(+7740)...
//   **元素计数直证: 29 × 0x10** 与 +8488/+8556 两处 nengine::IObject —— IRDMonster 尺寸 >8600B。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A50F0(int this)  // 实现：**元素计数直证: 29 × 0x10** 与 +8488/+8556 两处 nengine::IObject —— IRDMons…
{
  int *v3; // [esp-8h] [ebp-28h]
  int *fld_1DB8; // [esp-4h] [ebp-24h]
  int *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &IRDMonster::`vftable';  // vftable 复位
  v6 = 13;
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  *(uint32_t *)(this + 8556) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8560) = 0;
  if ( *(uint32_t *)(this + 8552) >= 0x10u )
    j__free(*(void **)(this + 8532));  // 调 堆释放
  *(uint32_t *)(this + 8552) = 15;
  *(uint32_t *)(this + 8548) = 0;  // this+8548〔nPhaseEndB〕
  *(uint8_t *)(this + 8532) = 0;  // this+8532〔nPhaseValB〕
  *(uint32_t *)(this + 8488) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8492) = 0;
  if ( *(uint32_t *)(this + 8340) != 0 )  // this+8340〔pAnimA(推断)〕
    j__free(*(void **)(this + 8340));  // 调 堆释放
  *(uint32_t *)(this + 8340) = 0;  // this+8340〔pAnimA(推断)〕
  *(uint32_t *)(this + 8344) = 0;  // this+8344〔nRideMode(推断)〕
  *(uint32_t *)(this + 8348) = 0;  // this+8348〔nPhaseParity(推断)〕
  LOBYTE(v6) = 8;  // 调 取 16 位值低 8 位
  `eh vector destructor iterator'((void *)(this + 7824), 0x10u, 29, sub_401940);  // this+7824〔nGrabH〕
  if ( *(uint32_t *)(this + 7808) != 0 )  // this+7808〔风格/分支选择〕
    j__free(*(void **)(this + 7808));  // 调 堆释放
  *(uint32_t *)(this + 7808) = 0;  // this+7808〔风格/分支选择〕
  *(uint32_t *)(this + 7812) = 0;  // this+7812〔nSubStateA(推断)〕
  *(uint32_t *)(this + 7816) = 0;  // this+7816〔nSubStateB(推断)〕
  if ( *(uint32_t *)(this + 7760) >= 0x10u )
    j__free(*(void **)(this + 7740));  // 调 堆释放
  *(uint32_t *)(this + 7760) = 15;
  *(uint32_t *)(this + 7756) = 0;
  *(uint8_t *)(this + 7740) = 0;
  *(uint32_t *)(this + 7640) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 7644) = 0;
  if ( *(uint32_t *)(this + 7620) != 0 )  // this+7620〔pStatusPanel(推断)〕
    j__free(*(void **)(this + 7620));  // 调 堆释放
  *(uint32_t *)(this + 7620) = 0;  // this+7620〔pStatusPanel(推断)〕
  *(uint32_t *)(this + 7624) = 0;
  *(uint32_t *)(this + 7628) = 0;
  fld_1DB8 = *(int **)(this + 7608);
  v3 = (int *)*fld_1DB8;
  LOBYTE(v6) = 3;  // 调 取 16 位值低 8 位
  sub_41DA40((int ***)(this + 7604), v5, v3, fld_1DB8);  // 调 同族实例二（回调 0x41CAA0）
  j__free(*(void **)(this + 7608));  // 调 堆释放
  *(uint32_t *)(this + 7608) = 0;
  *(uint32_t *)(this + 7612) = 0;
  if ( *(uint32_t *)(this + 7236) != 0 )
    j__free(*(void **)(this + 7236));  // 调 堆释放
  *(uint32_t *)(this + 7236) = 0;
  *(uint32_t *)(this + 7240) = 0;
  *(uint32_t *)(this + 7244) = 0;
  if ( *(uint32_t *)(this + 7224) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 7224));  // 调 删除 GDI 对象
    *(uint32_t *)(this + 7224) = 0;
  }
  *(uint8_t *)(this + 7180) = 0;
  *(uint8_t *)(this + 7181) = 0;
  *(uint8_t *)(this + 7182) = 0;
  *(uint8_t *)(this + 7183) = 0;
  *(uint32_t *)(this + 7192) = 0;
  *(uint32_t *)(this + 7196) = 0;
  *(uint32_t *)(this + 7200) = 0;
  *(uint32_t *)(this + 7204) = 0;
  *(uint32_t *)(this + 7208) = 0;
  *(uint32_t *)(this + 7212) = 0;
  *(uint32_t *)(this + 7216) = 0;
  *(uint32_t *)(this + 7220) = 0;
  *(uint32_t *)(this + 7224) = 0;
  *(uint32_t *)(this + 7228) = 0;
  if ( *(uint32_t *)(this + 7176) >= 0x10u )  // this+7176〔nNameStrCap〕
    j__free(*(void **)(this + 7156));  // 调 堆释放
  *(uint32_t *)(this + 7176) = 15;  // this+7176〔nNameStrCap〕
  *(uint32_t *)(this + 7172) = 0;  // this+7172〔nNameStrSize〕
  *(uint8_t *)(this + 7156) = 0;  // this+7156〔bParam3(推断)〕
  v6 = -1;
  return sub_4A4BD0(this);  // 返回 再释放 +7076 附属物 vector 与 +7048 串 —— 与 0x4A4E70（vmt0 壳）配对
}



// ------------------------------------------------------------
// 0x4A5350 sub_4A5350
// ------------------------------------------------------------
// 【解读】
//   【推断】析构壳（调 0x4A50F0 + 可选 free）= 某个怪物类的 vmt0。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5350(void *Block, char pszArg2)  // 实现：(推断)析构壳（调 0x4A50F0 + 可选 free）= 某个怪物类的 vmt0
{
  sub_4A50F0((int)Block);  // 调 IRDMonster 基类析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ============================================================
// SECTION 0x4A5380 — 怪物子类构造/析构批 A（CNFighterIllusion → CNGolemPlatany，0x4A5380-0x4A8010）
// ============================================================
// ------------------------------------------------------------
// 0x4A5380 sub_4A5380
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFighterIllusion（斗士幻影）构造 —— sub_5908C0/5908E0 专属初始化。
//   构造链: sub_4A4EA0（IRDMonster）。RTTI 直证。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5380(char *this, char ArgList, int nArg3)  // 函数 sub_4A5380：怪物子类构造/析构批 A（CNFighterIllusion → CNGolemPlatany，0x4A5380 0x4A8…
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNFighterIllusion::`vftable';  // vftable 复位
  sub_5908C0(this);  // 调 子类 AI 状态复位（出场演出标志清零）
  sub_5908E0(this);  // 调 标志复位（APPEAR 已播标志清零）
  return this;
}



// ------------------------------------------------------------
// 0x4A53E0 sub_4A53E0 —— CNFighterIllusion 删除析构壳（vt 槽0 · 本批壳族基准）
// 【推断】VC++ 标量删除析构形: 先调类析构体 ·0x4A5410（内写 CNFighterIllusion::vftable，RTTI 直证），
// 再按 pszArg2 bit0 真值时 free 对象 —— 本批各怪物子类的 6 行壳（自 ·0x4A54C0 起）均为此形。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A53E0(void *Block, char pszArg2)  // 函数: CNFighterIllusion 删除析构壳（vt 槽0 · 本批壳族基准）
{
  sub_4A5410();  // 调 (推断)CNFighterIllusion 析构（vftable 复位 + 0x4A50F0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5410 sub_4A5410
// ------------------------------------------------------------
// 【解读】
//   【推断】CNFighterIllusion 析构（vftable 复位 + 0x4A50F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5410(uint32_t *this)  // 实现：(推断)CNFighterIllusion 析构（vftable 复位 + 0x4A50F0）
{
  *this = &CNFighterIllusion::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5460 sub_4A5460
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNProvocationDoll（嘲讽人偶）构造（含 a4 参数传递 sub_590F30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5460(char *this, char ArgList, int nArg3, int nArg4)  // 实现：(推断)★ CNProvocationDoll（嘲讽人偶）构造（含 a4 参数传递 sub_590F30）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNProvocationDoll::`vftable';  // vftable 复位
  sub_590E70(this);  // 调 AI 阈值组清零
  sub_590F30(nArg4);  // 调 AI 阈值装载·数据表(3,43)
  return this;
}



// ------------------------------------------------------------
// 0x4A54C0 sub_4A54C0 —— CNProvocationDoll 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A54F0，CNProvocationDoll::vftable）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A54C0(void *Block, char pszArg2)  // 函数: CNProvocationDoll 删除析构壳
{
  sub_4A54F0();  // 调 (推断)CNProvocationDoll 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A54F0 sub_4A54F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNProvocationDoll 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A54F0(uint32_t *this)  // 实现：(推断)CNProvocationDoll 析构
{
  *this = &CNProvocationDoll::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5540 sub_4A5540
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKeraha 构造（sub_5913F0/592650）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5540(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNKeraha 构造（sub_5913F0/592650）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNKeraha::`vftable';  // vftable 复位
  sub_5913F0(this);  // 调 克拉赫子类 AI 字段复位
  sub_592650(this);  // 调 克拉赫初始化·语音/外观/AI 参数装载
  return this;
}



// ------------------------------------------------------------
// 0x4A55A0 sub_4A55A0 —— CNKeraha（克拉赫）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A55D0，CNKeraha::vftable）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A55A0(void *Block, char pszArg2)  // 函数: CNKeraha（克拉赫）删除析构壳
{
  sub_4A55D0();  // 调 (推断)CNKeraha 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A55D0 sub_4A55D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNKeraha 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A55D0(uint32_t *this)  // 实现：(推断)CNKeraha 析构
{
  *this = &CNKeraha::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5620 sub_4A5620
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNVinoshu 构造（sub_5928E0/593FF0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5620(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNVinoshu 构造（sub_5928E0/593FF0）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNVinoshu::`vftable';  // vftable 复位
  sub_5928E0(this);  // 调 子类扩展AI字段整块复位（this+8600..8660）
  sub_593FF0(this);  // 调 彼诺修资源装载（语音四槽 + .equ 四件外观 + 攻击参数初始化）
  return this;
}



// ------------------------------------------------------------
// 0x4A5680 sub_4A5680 —— CNVinoshu（彼诺修）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A56B0，CNVinoshu::vftable）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5680(void *Block, char pszArg2)  // 函数: CNVinoshu（彼诺修）删除析构壳
{
  sub_4A56B0();  // 调 (推断)CNVinoshu 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A56B0 sub_4A56B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNVinoshu 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A56B0(uint32_t *this)  // 实现：(推断)CNVinoshu 析构
{
  *this = &CNVinoshu::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5700 sub_4A5700
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLuis 构造（sub_592BF0/593680）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5700(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLuis 构造（sub_592BF0/593680）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNLuis::`vftable';  // vftable 复位
  sub_592BF0(this);
  sub_593680(this);  // 调 路易斯（Soceress）语音注册（R_LUIS 三件套 + SOR_APPEAR）
  return this;
}



// ------------------------------------------------------------
// 0x4A5760 sub_4A5760 —— CNLuis 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5790，CNLuis::vftable）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5760(void *Block, char pszArg2)  // 函数: CNLuis 删除析构壳
{
  sub_4A5790();  // 调 (推断)CNLuis 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5790 sub_4A5790
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLuis 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5790(uint32_t *this)  // 实现：(推断)CNLuis 析构
{
  *this = &CNLuis::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A57E0 sub_4A57E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLugaru 构造（sub_594340/594B10）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A57E0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLugaru 构造（sub_594340/594B10）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNLugaru::`vftable';  // vftable 复位
  sub_594340(this);  // 调 子类扩展字段复位（this+8600..8628 九个字段清零）
  sub_594B10(this);  // 调 狐狸语音注册（R_FOX_TALK / R_FOX_DMG / FOX_DIE 三件套）
  return this;
}



// ------------------------------------------------------------
// 0x4A5840 sub_4A5840
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLugaru 析构（sub_4E3360 = 战斗段公共清理，见多处怪物析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5840(uint32_t *this)  // 实现：(推断)CNLugaru 析构（sub_4E3360 = 战斗段公共清理，见多处怪物析构）
{
  *this = &CNLugaru::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5890 sub_4A5890
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLugaru 析构壳。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A5890(uint32_t *Block, char pszArg2)  // 实现：(推断)CNLugaru 析构壳
{
  sub_4A5840(Block);  // 调 (推断)CNLugaru 析构（sub_4E3360 = 战斗段公共清理，见多处怪物析构）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A58C0 sub_4A58C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGardener_Ral（园丁拉尔）构造 —— 继承 CNLugaru。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A58C0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNGardener_Ral（园丁拉尔）构造 —— 继承 CNLugaru
{
  sub_4A57E0((char *)this, ArgList, nArg3);  // 调 CNLugaru 构造并把指针直接返回
  *(uint32_t *)this = &CNGardener_Ral::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  return this;
}



// ------------------------------------------------------------
// 0x4A58F0 sub_4A58F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 怪物 AI 决策函数（CNGardener_Ral 或其他某怪物覆写）。
//   判据: vt+128 == 某值、vt+724 == 0（非冻结）、rand(88771231,100) < 10% 概率 ——
//   随机触发分支。rand 种子 88771231 是 DFO 的固定全局随机源之一。
//   【待验证】具体触发动作（在 10% 命中后做什么）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A58F0(int *this, int nArg2, int nArg3, int nArg4)  // 实现：(待验证)具体触发动作（在 10% 命中后做什么）
{
  int fld_e2158; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0  // 调用虚函数（虚表槽 +128）
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    && (int)sub_445870(88771231, 100) < 10 )  // 调 槽表随机数
  {
    fld_e2158 = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    *(this + 2158) = fld_e2158 + 1;  // this+8632〔bDevourFlag(推断)〕
    if ( fld_e2158 < 3 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调用虚函数（虚表槽 +580）【推断: ★ 位置化动作发布（会话 3 定案：位置化动作）】
        this,
        261,
        0,
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    sub_4D82D0(0, 0);  // 头顶气泡 Command.ani（a2/a3 = 定位偏移）
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GDRAL_01", -1, 0, 0);  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 调 ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
}



// ------------------------------------------------------------
// 0x4A59B0 sub_4A59B0 —— CNGardener_Ral（园丁拉尔）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A59E0，CNGardener_Ral::vftable 覆盖后转 CNLugaru 析构链）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A59B0(void *Block, char pszArg2)  // 函数: CNGardener_Ral（园丁拉尔）删除析构壳
{
  sub_4A59E0();  // 调 (推断)CNGardener_Ral 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A59E0 sub_4A59E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGardener_Ral 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A59E0(uint32_t *this)  // 实现：(推断)CNGardener_Ral 析构
{
  *this = &CNGardener_Ral::`vftable';  // vftable 复位
  return sub_4A5840(this);  // 返回 (推断)CNLugaru 析构（sub_4E3360 = 战斗段公共清理，见多处怪物析构）
}



// ------------------------------------------------------------
// 0x4A59F0 sub_4A59F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBlackLugaru（黑拉鲁）构造（sub_594F90/595470）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A59F0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNBlackLugaru（黑拉鲁）构造（sub_594F90/595470）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNBlackLugaru::`vftable';  // vftable 复位
  sub_594F90(this);  // 调 狐狸系子类AI字段复位（this+8600..8632 九个字段清零）
  sub_595470(this);  // 调 第二只狐狸实例参数初始化（语音注册+登场插值）
  return this;
}



// ------------------------------------------------------------
// 0x4A5A50 sub_4A5A50 —— CNBlackLugaru 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5A80，含 ·0x4E3360 战斗段清理）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5A50(void *Block, char pszArg2)  // 函数: CNBlackLugaru 删除析构壳
{
  sub_4A5A80();  // 调 (推断)CNBlackLugaru 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5A80 sub_4A5A80
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBlackLugaru 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5A80(uint32_t *this)  // 实现：(推断)CNBlackLugaru 析构
{
  *this = &CNBlackLugaru::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5AD0 sub_4A5AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWhiteLugaru（白拉鲁）构造（sub_595E10/596990）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5AD0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNWhiteLugaru（白拉鲁）构造（sub_595E10/596990）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNWhiteLugaru::`vftable';  // vftable 复位
  sub_595E10(this);  // 调 子类 AI 状态区整块复位
  sub_596990(this);  // 调 第三只狐狸实例参数初始化（治愈狐）
  return this;
}



// ------------------------------------------------------------
// 0x4A5B30 sub_4A5B30 —— CNWhiteLugaru 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5B60，含 ·0x4E3360 战斗段清理）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5B30(void *Block, char pszArg2)  // 函数: CNWhiteLugaru 删除析构壳
{
  sub_4A5B60();  // 调 (推断)CNWhiteLugaru 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5B60 sub_4A5B60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWhiteLugaru 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5B60(uint32_t *this)  // 实现：(推断)CNWhiteLugaru 析构
{
  *this = &CNWhiteLugaru::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5BB0 sub_4A5BB0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPenril 构造（sub_598350/598200）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5BB0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNPenril 构造（sub_598350/598200）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNPenril::`vftable';  // vftable 复位
  sub_598350(this);  // 调 子类 AI 区清零
  sub_598200(this);  // 调 牙齿装备型狐狸资源装载（出厂初始化）
  return this;
}



// ------------------------------------------------------------
// 0x4A5C10 sub_4A5C10 —— CNPenril 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5C40，含 ·0x4E3360 战斗段清理）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5C10(void *Block, char pszArg2)  // 函数: CNPenril 删除析构壳
{
  sub_4A5C40();  // 调 (推断)CNPenril 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5C40 sub_4A5C40
// ------------------------------------------------------------
// 【解读】
//   【推断】CNPenril 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5C40(uint32_t *this)  // 实现：(推断)CNPenril 析构
{
  *this = &CNPenril::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5C90 sub_4A5C90
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBloodLugaru（血拉鲁）构造（+8656 标志字节 / +8652 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5C90(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNBloodLugaru（血拉鲁）构造（+8656 标志字节 / +8652 IObject）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNBloodLugaru::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint32_t *)(this + 8652) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint8_t *)(this + 8664) = 1;  // this+8664〔uAI8664(推断)〕
  *(uint8_t *)(this + 8666) = 0;
  *(uint8_t *)(this + 8665) = 0;
  *(uint32_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  *(uint32_t *)(this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
  *(uint32_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  sub_598350(this);  // 调 子类 AI 区清零
  sub_5993F0(this);  // 调 狐狸(Lugaru)装载：R_FOX_TALK/DMG、FOX_DIE 语音 + Monster/Lugaru/Teeth.…
  return this;
}



// ------------------------------------------------------------
// 0x4A5D30 sub_4A5D30 —— CNBloodLugaru 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5D60，含 IObject @+8652 vftable 复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5D30(void *Block, char pszArg2)  // 函数: CNBloodLugaru 删除析构壳
{
  sub_4A5D60();  // 调 (推断)CNBloodLugaru 析构（含 nengine::IObject @+8652 复位）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A5D60 sub_4A5D60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBloodLugaru 析构（含 nengine::IObject @+8652 复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5D60(uint32_t *this)  // 实现：(推断)CNBloodLugaru 析构（含 nengine::IObject @+8652 复位）
{
  *this = &CNBloodLugaru::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  *(this + 2163) = &nengine::IObject::`vftable';  // this+8652 = 相位槽
  *((uint8_t *)this + 8656) = 0;  // this+8656 = 事件 16/17 配对槽
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5DC0 sub_4A5DC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblin 族构造共享前缀 —— 写 CNGoblinCommon vftable 于 +8600，
//   +8604=0 / +8605=1。**这是全哥布林族的"第二 vftable"位置（this+8600）之直证**，
//   解释了大量 *(this+2150) = &CNGoblinXXX::vftable 的写法（2150*4 = 8600）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5DC0(int this, char ArgList, int nArg3)  // 实现：解释了大量 *(this+2150) = &CNGoblinXXX::vftable 的写法（2150*4 = 8600）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinStoner::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinStoner::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  sub_59D760(this);  // 调 子类扩展字段复位（同构 ·0x59C440，差异：无 this+8656）
  sub_5998E0(this);  // 调 投石哥布林装载：R_GOBLIN_TALK/DMG/DIE 语音 + tcc2/acc2/hcc3/gcc1.equ 四件外…
  return this;
}



// ------------------------------------------------------------
// 0x4A5E70 sub_4A5E70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinStoner 析构壳（this−8600 回退到对象头，多继承布局修正）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5E70(char *this, char pszArg2)  // 实现：(推断)CNGoblinStoner 析构壳（this−8600 回退到对象头，多继承布局修正）
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A5EB0();  // 调 (推断)CNGoblinStoner 析构（双 vftable 复位 + string 释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(v2);  // 调 堆释放
  return v2;
}



// ------------------------------------------------------------
// 0x4A5EB0 sub_4A5EB0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinStoner 析构（双 vftable 复位 + string 释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5EB0(int this)  // 实现：(推断)CNGoblinStoner 析构（双 vftable 复位 + string 释放）
{
  *(uint32_t *)this = &CNGoblinStoner::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinStoner::`vftable';  // vftable 复位
  if ( *(uint32_t *)(this + 8652) >= 0x10u )  // this+8652〔uPhase8652(推断)〕
    j__free(*(void **)(this + 8632));  // 调 堆释放
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A5F10 sub_4A5F10
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第二版，参数不同）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5F10(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第二版，参数不同）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinGoblin::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &off_6D0E8C;  // 写 vftable 指针 off_6D0E8C
  *(uint32_t *)(this + 8648) = 15;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8676) = 15;  // this+8676〔uAI8676(推断)〕
  *(uint32_t *)(this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
  *(uint8_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  sub_599AE0(this);  // 调 投石槽复位：this+8616/8620 双字清零（装载与事件流程使用的槽位）
  sub_59A990(this);  // 调 自杀哥布林装载：R_GOBLIN_* + GOBLIN_SUICIDAL/GOBLIN_SCARED 语音、gcc1/Wea…
  return this;
}



// ------------------------------------------------------------
// 0x4A5FF0 sub_4A5FF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5FF0(int this)  // 实现：(推断)★ CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）
{
  *(uint32_t *)this = &CNGoblinGoblin::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &off_6D0E8C;  // 写 vftable 指针 off_6D0E8C
  nullsub_3(this);
  if ( *(uint32_t *)(this + 8676) >= 0x10u )  // this+8676〔uAI8676(推断)〕
    j__free(*(void **)(this + 8656));  // 调 堆释放
  *(uint32_t *)(this + 8676) = 15;  // this+8676〔uAI8676(推断)〕
  *(uint32_t *)(this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
  *(uint8_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  if ( *(uint32_t *)(this + 8648) >= 0x10u )  // this+8648〔uPhase8648(推断)〕
    j__free(*(void **)(this + 8628));  // 调 堆释放
  *(uint32_t *)(this + 8648) = 15;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A60C0 sub_4A60C0 —— CNGoblinGoblin 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A5FF0 CNGoblinGoblin 位于本壳之前，地址序与源序不一致）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A60C0(void *Block, char pszArg2)  // 函数: CNGoblinGoblin 删除析构壳
{
  sub_4A5FF0((int)Block);  // 调 (推断) CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A60F0 sub_4A60F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinAssaulter 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A60F0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinAssaulter 构造
{
  sub_4A5F10((int)this, ArgList, nArg3);  // 调 CNGoblinGoblin 构造，结果存 result
  *this = &CNGoblinAssaulter::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinAssaulter::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A6130 sub_4A6130 —— CNGoblinAssaulter 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6160，复位双 vftable 头与 this+8600）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6130(void *Block, char pszArg2)  // 函数: CNGoblinAssaulter 删除析构壳
{
  sub_4A6160();  // 调 (推断)CNGoblinAssaulter 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6160 sub_4A6160
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinAssaulter 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6160(int this)  // 实现：(推断)CNGoblinAssaulter 析构
{
  *(uint32_t *)this = &CNGoblinAssaulter::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinAssaulter::`vftable';  // vftable 复位
  return sub_4A5FF0(this);  // 返回 (推断) CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）
}



// ------------------------------------------------------------
// 0x4A6180 sub_4A6180
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinHodor 构造（+8708 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6180(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinHodor 构造（+8708 标志）
{
  sub_4A5F10((int)this, ArgList, nArg3);  // 调 CNGoblinGoblin 构造，结果存 result
  *this = &CNGoblinHodor::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinHodor::`vftable';  // this+8600 = uAI8600
  *((uint8_t *)this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2176) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(this + 2178) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  *((uint8_t *)this + 8716) = 1;  // this+8716〔uArr8716〕
  *((uint8_t *)this + 8718) = 0;
  *((uint8_t *)this + 8717) = 0;
  *(this + 2182) = 0;  // this+8728〔nSegThrCap8728〕
  *(this + 2181) = 0;  // this+8724〔nSegThrEnd8724〕
  *(this + 2180) = 0;  // this+8720〔pSegThrTbl8720〕
  sub_599D50(this);  // 调 子类扩展字段复位：清 this+8612/8616/8680/8696/8700
  sub_599D80(this);  // 调 虚表转发垫片：调用 vt+1308 并原样返回其结果
  return this;
}



// ------------------------------------------------------------
// 0x4A6230 sub_4A6230 —— CNGoblinHodor 第二 vftable 子对象删除析构 thunk
// 【推断】this-8600 回退到对象头后转发 ·0x4A6240；8600 为哥布林族第二 vftable 偏移
// （·0x4A5DC0 直证 this+8600 写 CNGoblinCommon::vftable，2150*4 = 8600）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6230(char *this, char pszArg2)  // 函数: CNGoblinHodor 第二 vftable 子对象删除析构 thunk
{
  return sub_4A6240(this - 8600, pszArg2);  // 调 CNGoblinHodor 删除析构壳
}



// ------------------------------------------------------------
// 0x4A6240 sub_4A6240 —— CNGoblinHodor 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6270，含 IObject @+8704 vftable 复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6240(void *Block, char pszArg2)  // 函数: CNGoblinHodor 删除析构壳
{
  sub_4A6270();  // 调 (推断)CNGoblinHodor 析构（含 IObject @+8704）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6270 sub_4A6270
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinHodor 析构（含 IObject @+8704）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6270(int this)  // 实现：(推断)CNGoblinHodor 析构（含 IObject @+8704）
{
  *(uint32_t *)this = &CNGoblinHodor::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinHodor::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8704) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  return sub_4A5FF0(this);  // 返回 (推断) CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）
}



// ------------------------------------------------------------
// 0x4A62A0 sub_4A62A0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第三版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A62A0(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第三版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinKinol::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinKinol::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8636) = 15;  // this+8636〔pDollTarget(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8664) = 15;  // this+8664〔uAI8664(推断)〕
  *(uint32_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint8_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  nullsub_3(this);
  sub_59B8A0(this);  // 调 哥布林恐惧 AI 初始化（语音 TAG + 恐惧参数面 + 相位时钟）
  sub_59BE40(this);  // 调 狼牙棒哥布林外观装载（标准四件套）
  return this;
}



// ------------------------------------------------------------
// 0x4A6370 sub_4A6370 —— CNGoblinKinol 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A6450 CNGoblinKinol 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6370(char *this, char pszArg2)  // 函数: CNGoblinKinol 第二 vftable 子对象删除析构 thunk
{
  return sub_4A6450(this - 8600, pszArg2);  // 调 CNGoblinKinol 删除析构壳
}



// ------------------------------------------------------------
// 0x4A6380 sub_4A6380
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinKinol 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6380(int this)  // 实现：(推断)★ CNGoblinKinol 析构相关
{
  *(uint32_t *)this = &CNGoblinKinol::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinKinol::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  if ( *(uint32_t *)(this + 8664) >= 0x10u )  // this+8664〔uAI8664(推断)〕
    j__free(*(void **)(this + 8644));  // 调 堆释放
  *(uint32_t *)(this + 8664) = 15;  // this+8664〔uAI8664(推断)〕
  *(uint32_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint8_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  if ( *(uint32_t *)(this + 8636) >= 0x10u )  // this+8636〔pDollTarget(推断)〕
    j__free(*(void **)(this + 8616));  // 调 堆释放
  *(uint32_t *)(this + 8636) = 15;  // this+8636〔pDollTarget(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6450 sub_4A6450 —— CNGoblinKinol 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6380，双 vftable 头与 this+8600 复位，两处 string 释放）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6450(void *Block, char pszArg2)  // 函数: CNGoblinKinol 删除析构壳
{
  sub_4A6380((int)Block);  // 调 (推断) CNGoblinKinol 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6480 sub_4A6480
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBunker_Woker 构造（sub_59BF90）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6480(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNBunker_Woker 构造（sub_59BF90）
{
  sub_4A62A0((int)this, ArgList, nArg3);  // 调 CNGoblinKinol 构造并把指针直接返回
  *this = &CNBunker_Woker::`vftable';  // vftable 复位
  *(this + 2150) = &CNBunker_Woker::`vftable';  // this+8600 = uAI8600
  sub_59BF90(this);  // 调 圣诞哥布林换装（CwGobSantaBeard.equ 圣诞胡装）
  return this;
}



// ------------------------------------------------------------
// 0x4A64F0 sub_4A64F0 —— CNBunker_Woker 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6520，双 vftable 后转 ·0x4A6380 析构链）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A64F0(void *Block, char pszArg2)  // 函数: CNBunker_Woker 删除析构壳
{
  sub_4A6520();  // 调 (推断)CNBunker_Woker 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6520 sub_4A6520
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBunker_Woker 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6520(int this)  // 实现：(推断)CNBunker_Woker 析构
{
  *(uint32_t *)this = &CNBunker_Woker::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNBunker_Woker::`vftable';  // vftable 复位
  return sub_4A6380(this);  // 返回 (推断) CNGoblinKinol 析构相关
}



// ------------------------------------------------------------
// 0x4A6540 sub_4A6540
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEliteGoblin 构造（+8680 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6540(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNEliteGoblin 构造（+8680 标志）
{
  sub_4A62A0((int)this, ArgList, nArg3);  // 调 CNGoblinKinol 构造并把指针直接返回
  *this = &CNEliteGoblin::`vftable';  // vftable 复位
  *(this + 2150) = &CNEliteGoblin::`vftable';  // this+8600 = uAI8600
  *((uint8_t *)this + 8680) = 0;  // this+8680〔uGate8680(推断)〕
  return this;
}



// ------------------------------------------------------------
// 0x4A6580 sub_4A6580
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKingGalok 构造（继承 CNEliteGoblin 前缀布局，+8680 清零）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A6580(uint8_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNKingGalok 构造（继承 CNEliteGoblin 前缀布局，+8680 清零）
{
  sub_4A62A0((int)this, ArgList, nArg3);  // 调 CNGoblinKinol 构造并把指针直接返回
  *(this + 8680) = 0;  // this+8680 【推断】子类 AI 门字节
  *(uint32_t *)this = &CNKingGalok::`vftable';  // vftable 复位
  *((uint32_t *)this + 2150) = &CNKingGalok::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A65C0 sub_4A65C0 —— CNEliteGoblin 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A65D0 CNEliteGoblin 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A65C0(char *this, char pszArg2)  // 函数: CNEliteGoblin 第二 vftable 子对象删除析构 thunk
{
  return sub_4A65D0(this - 8600, pszArg2);  // 调 CNEliteGoblin 删除析构壳
}



// ------------------------------------------------------------
// 0x4A65D0 sub_4A65D0 —— CNEliteGoblin 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6600，双 vftable 后转 ·0x4A6380）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A65D0(void *Block, char pszArg2)  // 函数: CNEliteGoblin 删除析构壳
{
  sub_4A6600();  // 调 (推断)CNEliteGoblin 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6600 sub_4A6600
// ------------------------------------------------------------
// 【解读】
//   【推断】CNEliteGoblin 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6600(int this)  // 实现：(推断)CNEliteGoblin 析构
{
  *(uint32_t *)this = &CNEliteGoblin::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNEliteGoblin::`vftable';  // vftable 复位
  return sub_4A6380(this);  // 返回 (推断) CNGoblinKinol 析构相关
}



// ------------------------------------------------------------
// 0x4A6620 sub_4A6620
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第四版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6620(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第四版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinGero::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinGero::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  sub_59C440(this);  // 调 子类扩展字段复位（this+8612..8656）
  sub_59CEC0(this);  // 调 速投哥布林装载（语音 + 六件套 + FastThrowStone 粒子槽）
  return this;
}



// ------------------------------------------------------------
// 0x4A66D0 sub_4A66D0 —— CNGoblinGero 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A6780 CNGoblinGero 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A66D0(char *this, char pszArg2)  // 函数: CNGoblinGero 第二 vftable 子对象删除析构 thunk
{
  return sub_4A6780(this - 8600, pszArg2);  // 调 CNGoblinGero 删除析构壳
}



// ------------------------------------------------------------
// 0x4A66E0 sub_4A66E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinGero 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A66E0(int this)  // 实现：(推断)★ CNGoblinGero 析构相关
{
  *(uint32_t *)this = &CNGoblinGero::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinGero::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  if ( *(uint32_t *)(this + 8652) >= 0x10u )  // this+8652〔uPhase8652(推断)〕
    j__free(*(void **)(this + 8632));  // 调 堆释放
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6780 sub_4A6780 —— CNGoblinGero 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A66E0 定义于本壳之前，含 string@+8632 释放）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6780(void *Block, char pszArg2)  // 函数: CNGoblinGero 删除析构壳
{
  sub_4A66E0((int)Block);  // 调 (推断) CNGoblinGero 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A67B0 sub_4A67B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPrag 构造（+8620 = 30076 动作 ID 常量）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A67B0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNPrag 构造（+8620 = 30076 动作 ID 常量）
{
  sub_4A6620((int)this, ArgList, nArg3);  // 调 CNGoblinGero 构造并把指针直接返回
  *this = &CNPrag::`vftable';  // vftable 复位
  *(this + 2150) = &CNPrag::`vftable';  // this+8600 = uAI8600
  *(this + 2155) = 30076;  // this+8620 = uAI8620
  *(this + 2167) = 30023;  // this+8668 = nCool8668
  return this;
}



// ------------------------------------------------------------
// 0x4A67F0 sub_4A67F0 —— CNPrag 删除析构（this-8600 自调整版）
// 【推断】先算 v2 = this-8600 得对象头（第二 vftable 子对象入口），调 ·0x4A6830（CNPrag::vftable 析构体），
// 再按 pszArg2 bit0 释放调整后指针 —— 与 ·0x4A6230 的转发型 thunk 互补（此形把释放内联）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A67F0(char *this, char pszArg2)  // 函数: CNPrag 删除析构（this-8600 自调整版）
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6830();  // 调 (推断)CNPrag 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(v2);  // 调 堆释放
  return v2;
}



// ------------------------------------------------------------
// 0x4A6830 sub_4A6830
// ------------------------------------------------------------
// 【解读】
//   【推断】CNPrag 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6830(int this)  // 实现：(推断)CNPrag 析构
{
  *(uint32_t *)this = &CNPrag::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNPrag::`vftable';  // vftable 复位
  return sub_4A66E0(this);  // 返回 (推断) CNGoblinGero 析构相关
}



// ------------------------------------------------------------
// 0x4A6850 sub_4A6850
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第五版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6850(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第五版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinMountainGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinMountainGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  sub_59D760(this);  // 调 子类扩展字段复位（同构 ·0x59C440，差异：无 this+8656）
  sub_59D4D0(this);  // 调 火导弹哥布林装载（语音 + 五件套 + FireMissile 粒子）
  return this;
}



// ------------------------------------------------------------
// 0x4A6900 sub_4A6900 —— CNGoblinMountainGab 删除析构（this-8600 自调整版）
// 与 ·0x4A67F0 同构（差异：析构体 ·0x4A6940，CNGoblinMountainGab::vftable）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6900(char *this, char pszArg2)  // 函数: CNGoblinMountainGab 删除析构（this-8600 自调整版）
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6940();  // 调 (推断) CNGoblinMountainGab 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(v2);  // 调 堆释放
  return v2;
}



// ------------------------------------------------------------
// 0x4A6940 sub_4A6940
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinMountainGab 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6940(int this)  // 实现：(推断)★ CNGoblinMountainGab 析构相关
{
  *(uint32_t *)this = &CNGoblinMountainGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinMountainGab::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  if ( *(uint32_t *)(this + 8652) >= 0x10u )  // this+8652〔uPhase8652(推断)〕
    j__free(*(void **)(this + 8632));  // 调 堆释放
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A69E0 sub_4A69E0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第六版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A69E0(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第六版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinIslandGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinIslandGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  sub_59D760(this);  // 调 子类扩展字段复位（同构 ·0x59C440，差异：无 this+8656）
  sub_59D8F0(this);  // 调 冰导弹哥布林装载（同构 ·0x59D4D0，差异：冰系资源面）
  return this;
}



// ------------------------------------------------------------
// 0x4A6A90 sub_4A6A90 —— CNGoblinIslandGab 删除析构（this-8600 自调整版）
// 与 ·0x4A67F0 同构（差异：析构体 ·0x4A6AD0，CNGoblinIslandGab::vftable）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6A90(char *this, char pszArg2)  // 函数: CNGoblinIslandGab 删除析构（this-8600 自调整版）
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6AD0();  // 调 (推断) CNGoblinIslandGab 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(v2);  // 调 堆释放
  return v2;
}



// ------------------------------------------------------------
// 0x4A6AD0 sub_4A6AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinIslandGab 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6AD0(int this)  // 实现：(推断)★ CNGoblinIslandGab 析构相关
{
  *(uint32_t *)this = &CNGoblinIslandGab::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinIslandGab::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  if ( *(uint32_t *)(this + 8652) >= 0x10u )  // this+8652〔uPhase8652(推断)〕
    j__free(*(void **)(this + 8632));  // 调 堆释放
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6B70 sub_4A6B70
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第七版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6B70(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第七版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinLupete::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinLupete::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8660) = 15;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint8_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  sub_59DB80(this);  // 调 子类扩展字段复位（同构 ·0x59D760，差异：8620 清零、多 8628=0xFFFF/8632）
  sub_59E230(this);  // 调 卢佩特（Lupete）装载：语音 + 六件套 + 三向喷吐粒子
  return this;
}



// ------------------------------------------------------------
// 0x4A6C20 sub_4A6C20 —— CNGoblinLupete 删除析构（this-8600 自调整版）
// 与 ·0x4A67F0 同构（差异：析构体 ·0x4A6C60，CNGoblinLupete::vftable）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6C20(char *this, char pszArg2)  // 函数: CNGoblinLupete 删除析构（this-8600 自调整版）
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6C60();  // 调 (推断) CNGoblinLupete 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(v2);  // 调 堆释放
  return v2;
}



// ------------------------------------------------------------
// 0x4A6C60 sub_4A6C60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinLupete 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6C60(int this)  // 实现：(推断)★ CNGoblinLupete 析构相关
{
  *(uint32_t *)this = &CNGoblinLupete::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinLupete::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  if ( *(uint32_t *)(this + 8660) >= 0x10u )  // this+8660〔uEvt8660(推断)〕
    j__free(*(void **)(this + 8640));  // 调 堆释放
  *(uint32_t *)(this + 8660) = 15;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint8_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6D00 sub_4A6D00
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第八版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6D00(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第八版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  sub_59E550(this);  // 调 子类扩展字段复位（同构 ·0x59D760，差异：仅 8612/8616/8620 三字段且 8620 清零）
  sub_59FC80(this);  // 调 岛哥布林语音三件套注册（R_GOBLIN_TALK/DMG/DIE）
  return this;
}



// ------------------------------------------------------------
// 0x4A6DA0 sub_4A6DA0 —— CNGoblinSharedo 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A6DB0 CNGoblinSharedo 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6DA0(char *this, char pszArg2)  // 函数: CNGoblinSharedo 第二 vftable 子对象删除析构 thunk
{
  return sub_4A6DB0(this - 8600, pszArg2);  // 调 CNGoblinSharedo 删除析构壳
}



// ------------------------------------------------------------
// 0x4A6DB0 sub_4A6DB0 —— CNGoblinSharedo 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6F40 为 CNGoblinSharedo/SharedoBase 共享析构体，仅降级 vftable）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6DB0(void *Block, char pszArg2)  // 函数: CNGoblinSharedo 删除析构壳
{
  sub_4A6F40();  // 调 (推断)CNGoblinSharedoBase 析构（第二版，含 vftable 降级回 CNGoblinCommon 的细节）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6DE0 sub_4A6DE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6DE0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）
{
  sub_4A6D00((int)this, ArgList, nArg3);  // 调 (推断)哥布林族构造共享前缀（第八版）
  *this = &CNGoblinKagelBase::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinKagelBase::`vftable';  // this+8600 = uAI8600
  *((uint8_t *)this + 8648) = 0;  // this+8648 = 相位/缓存槽
  *(this + 2163) = 0;  // this+8652 = 相位槽
  *((uint8_t *)this + 8658) = 0;  // this+8658〔bAI8658〕
  *((uint8_t *)this + 8657) = 0;  // this+8657〔bAI8657〕
  *(this + 2167) = 0;  // this+8668 = nCool8668
  *(this + 2166) = 0;  // this+8664 = 子类 AI 槽
  *(this + 2165) = 0;  // this+8660 = uEvt8660
  *(this + 2161) = &off_6C2B88;  // this+8644 = 相位槽
  *((uint8_t *)this + 8656) = 1;  // this+8656 = 事件 16/17 配对槽
  *((uint8_t *)this + 8624) = 0;  // this+8624 = uAI8624
  *(this + 2157) = 0;  // this+8628 = 指挥计时戳
  *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  *((uint8_t *)this + 8636) = 0;  // this+8636 = pDollTarget
  *(this + 2160) = 0;  // this+8640 = uCastSlot8640
  *((uint8_t *)this + 8657) = 0;  // this+8657〔bAI8657〕
  *((uint8_t *)this + 8658) = 0;  // this+8658〔bAI8658〕
  return this;
}



// ------------------------------------------------------------
// 0x4A6E80 sub_4A6E80
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinSharedoBase 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6E80(int this)  // 实现：(推断)CNGoblinSharedoBase 析构
{
  *(uint32_t *)(this + 8644) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6EB0 sub_4A6EB0 —— CNGoblinKagelBase 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A6E80，含 IObject @+8644 复位，
// 与 ·0x4A6DE0 CNGoblinKagelBase 构造写 +8644 = off_6C2B88 的布局一致【推断】）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6EB0(void *Block, char pszArg2)  // 函数: CNGoblinKagelBase 删除析构壳
{
  sub_4A6E80((int)Block);  // 调 (推断)CNGoblinSharedoBase 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A6EE0 sub_4A6EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinSharedo 构造（sub_5A0530）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6EE0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinSharedo 构造（sub_5A0530）
{
  sub_4A6D00((int)this, ArgList, nArg3);  // 调 (推断)哥布林族构造共享前缀（第八版）
  *this = &CNGoblinSharedo::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinSharedo::`vftable';  // this+8600 = uAI8600
  sub_5A0530(this);  // 调 哥布林近战型六件 .equ 挂装 + 效果值插值
  return this;
}



// ------------------------------------------------------------
// 0x4A6F40 sub_4A6F40
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinSharedoBase 析构（第二版，含 vftable 降级回 CNGoblinCommon 的细节）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6F40(int this)  // 实现：(推断)CNGoblinSharedoBase 析构（第二版，含 vftable 降级回 CNGoblinCommon 的细节）
{
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A6F60 sub_4A6F60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinBombKagel 构造（sub_5A0780）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6F60(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinBombKagel 构造（sub_5A0780）
{
  sub_4A6DE0(this, ArgList, nArg3);  // 调 (推断) CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）
  *this = &CNGoblinBombKagel::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinBombKagel::`vftable';  // this+8600 = uAI8600
  sub_5A0780(this);  // 调 炸弹加格尔（BombKagel）五件套挂装
  return this;
}



// ------------------------------------------------------------
// 0x4A6FD0 sub_4A6FD0 —— CNGoblinBombKagel 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A7000，含 IObject @+8644 复位与 ·0x4E3360 清理）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6FD0(void *Block, char pszArg2)  // 函数: CNGoblinBombKagel 删除析构壳
{
  sub_4A7000();  // 调 (推断)CNGoblinBombKagel 析构（含 IObject @+8644）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7000 sub_4A7000
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinBombKagel 析构（含 IObject @+8644）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7000(uint32_t *this)  // 实现：(推断)CNGoblinBombKagel 析构（含 IObject @+8644）
{
  *this = &CNGoblinBombKagel::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinBombKagel::`vftable';  // this+8600 = uAI8600
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  *(this + 2161) = &nengine::IObject::`vftable';  // this+8644 = 相位槽
  *((uint8_t *)this + 8648) = 0;  // this+8648 = 相位/缓存槽
  *this = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinSharedoBase::`vftable';  // this+8600 = uAI8600
  *(this + 2150) = &CNGoblinCommon::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7090 sub_4A7090
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinSurikenKagel 构造（sub_5A0930）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7090(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinSurikenKagel 构造（sub_5A0930）
{
  sub_4A6DE0(this, ArgList, nArg3);  // 调 (推断) CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）
  *this = &CNGoblinSurikenKagel::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinSurikenKagel::`vftable';  // this+8600 = uAI8600
  sub_5A0930(this);  // 调 与 ·0x5A0780 同构
  return this;
}



// ------------------------------------------------------------
// 0x4A7100 sub_4A7100
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinBullsEye 构造（+8688 清零）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7100(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoblinBullsEye 构造（+8688 清零）
{
  sub_4A6DE0(this, ArgList, nArg3);  // 调 (推断) CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）
  *this = &CNGoblinBullsEye::`vftable';  // vftable 复位
  *(this + 2150) = &CNGoblinBullsEye::`vftable';  // this+8600 = uAI8600
  *(this + 2172) = 0;  // this+8688〔bVec8688(推断)〕
  *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
  *(this + 2174) = 0;  // this+8696〔uVec8696(推断)〕
  sub_5A0AE0(this);  // 调 投掷哥布林（BullsEye）挂装 + 子类状态复位 + 落石粒子创建
  return this;
}



// ------------------------------------------------------------
// 0x4A7180 sub_4A7180 —— CNGoblinBullsEye 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A7190 CNGoblinBullsEye 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7180(char *this, char pszArg2)  // 函数: CNGoblinBullsEye 第二 vftable 子对象删除析构 thunk
{
  return sub_4A7190(this - 8600, pszArg2);  // 调 CNGoblinBullsEye 删除析构壳
}



// ------------------------------------------------------------
// 0x4A7190 sub_4A7190 —— CNGoblinBullsEye 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A71C0，含 +8704 子对象虚调释放与 +8688 缓冲 free）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7190(void *Block, char pszArg2)  // 函数: CNGoblinBullsEye 删除析构壳
{
  sub_4A71C0();  // 调 (推断)CNGoblinBullsEye 析构（含对 +8704 对象的 vt 调用）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A71C0 sub_4A71C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinBullsEye 析构（含对 +8704 对象的 vt 调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A71C0(int this)  // 实现：(推断)CNGoblinBullsEye 析构（含对 +8704 对象的 vt 调用）
{
  void (/*thiscall*/ ***pThis_2200)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGoblinBullsEye::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinBullsEye::`vftable';  // vftable 复位
  pThis_2200 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8704);  // this+8704 【推断】动态数组/表首指针
  if ( pThis_2200 != nullptr )  // 若 pThis_2200 有效（非空）
    (**pThis_2200)(pThis_2200, 1);  // 调 pThis_2200 的虚函数（vt+0）
  *(uint32_t *)(this + 8704) = 0;  // this+8704〔pSegNameTbl8704(推断)〕
  if ( *(uint32_t *)(this + 8688) != 0 )  // this+8688〔bVec8688(推断)〕
    j__free(*(void **)(this + 8688));  // 调 堆释放
  *(uint32_t *)(this + 8688) = 0;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  *(uint32_t *)(this + 8644) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7280 sub_4A7280
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第九版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7280(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第九版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNLightningKinol::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNLightningKinol::`vftable';  // vftable 复位
  sub_5A0D00(this);  // 调 AI 字段访问
  sub_5A1D20(this);  // 调 落雷凯诺（型 1）装载
  return this;
}



// ------------------------------------------------------------
// 0x4A7320 sub_4A7320 —— CNLightningKinol 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A7330 CNLightningKinol 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7320(char *this, char pszArg2)  // 函数: CNLightningKinol 第二 vftable 子对象删除析构 thunk
{
  return sub_4A7330(this - 8600, pszArg2);  // 调 CNLightningKinol（落雷凯诺）删除析构壳
}



// ------------------------------------------------------------
// 0x4A7330 sub_4A7330 —— CNLightningKinol（落雷凯诺）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A7360，vftable 降级回 CNGoblinCommon）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7330(void *Block, char pszArg2)  // 函数: CNLightningKinol（落雷凯诺）删除析构壳
{
  sub_4A7360();  // 调 (推断) CNLightningKinol 析构相关
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7360 sub_4A7360
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLightningKinol 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7360(uint32_t *this)  // 实现：(推断)★ CNLightningKinol 析构相关
{
  *this = &CNLightningKinol::`vftable';  // vftable 复位
  *(this + 2150) = &CNLightningKinol::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNGoblinCommon::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A73D0 sub_4A73D0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第十版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A73D0(int this, char ArgList, int nArg3)  // 实现：(推断)哥布林族构造共享前缀（第十版）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;  // 调 以 16 位种子状态递推并返回 15 位结果
  *(uint32_t *)this = &CNCowardGoblin::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNCowardGoblin::`vftable';  // vftable 复位
  sub_5A2020(this);  // 调 胆小鬼子类扩展字段复位
  sub_5A2A50(this);  // 调 胆小鬼哥布林装载
  return this;
}



// ------------------------------------------------------------
// 0x4A7470 sub_4A7470 —— CNCowardGoblin 第二 vftable 子对象删除析构 thunk
// 与 ·0x4A6230 同构（差异：转发 ·0x4A7480 CNCowardGoblin 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7470(char *this, char pszArg2)  // 函数: CNCowardGoblin 第二 vftable 子对象删除析构 thunk
{
  return sub_4A7480(this - 8600, pszArg2);  // 调 CNCowardGoblin（怯懦哥布林）删除析构壳
}



// ------------------------------------------------------------
// 0x4A7480 sub_4A7480 —— CNCowardGoblin（怯懦哥布林）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A74B0，含 ·0x5A20C0 专属清理后降级 CNGoblinCommon）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7480(void *Block, char pszArg2)  // 函数: CNCowardGoblin（怯懦哥布林）删除析构壳
{
  sub_4A74B0();  // 调 (推断) CNCowardGoblin（怯懦哥布林）析构相关（sub_5A20C0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A74B0 sub_4A74B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCowardGoblin（怯懦哥布林）析构相关（sub_5A20C0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A74B0(uint32_t *this)  // 实现：(推断)★ CNCowardGoblin（怯懦哥布林）析构相关（sub_5A20C0）
{
  *this = &CNCowardGoblin::`vftable';  // vftable 复位
  *(this + 2150) = &CNCowardGoblin::`vftable';  // this+8600 = uAI8600
  sub_5A20C0();  // 调 释放双粒子句柄
  *(this + 2150) = &CNGoblinCommon::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7520 sub_4A7520
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauArmy（牛头人军团）构造 —— 先写 CNTauFriendShip 再写本类。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7520(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNTauArmy（牛头人军团）构造 —— 先写 CNTauFriendShip 再写本类
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNTauArmy::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNTauArmy::`vftable';  // vftable 复位
  nullsub_3(this);
  sub_5A2F30(this);  // 调 牛头兵标准型装载
  return this;
}



// ------------------------------------------------------------
// 0x4A75A0 sub_4A75A0 —— CNTauArmy（牛头人军团）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A75D0，vftable 降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A75A0(void *Block, char pszArg2)  // 函数: CNTauArmy（牛头人军团）删除析构壳
{
  sub_4A75D0();  // 调 (推断)CNTauArmy 析构（vftable 降级回 CNMonsterFriendShip）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A75D0 sub_4A75D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauArmy 析构（vftable 降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A75D0(uint32_t *this)  // 实现：(推断)CNTauArmy 析构（vftable 降级回 CNMonsterFriendShip）
{
  *this = &CNTauArmy::`vftable';  // vftable 复位
  *(this + 2150) = &CNTauArmy::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7640 sub_4A7640
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauBeast（牛头兽）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7640(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNTauBeast（牛头兽）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNTauBeast::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNTauBeast::`vftable';  // vftable 复位
  sub_5AA340(this);
  sub_5A3510(this);  // 调 牛头兽装载（Hair-Beast / Horn-Beast）
  return this;
}



// ------------------------------------------------------------
// 0x4A76C0 sub_4A76C0 —— CNTauBeast（牛头兽）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A76F0，降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A76C0(void *Block, char pszArg2)  // 函数: CNTauBeast（牛头兽）删除析构壳
{
  sub_4A76F0();  // 调 (推断)CNTauBeast 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A76F0 sub_4A76F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauBeast 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A76F0(uint32_t *this)  // 实现：(推断)CNTauBeast 析构
{
  *this = &CNTauBeast::`vftable';  // vftable 复位
  *(this + 2150) = &CNTauBeast::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7760 sub_4A7760
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauAssaulter（牛头突击兵）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7760(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNTauAssaulter（牛头突击兵）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNTauAssaulter::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNTauAssaulter::`vftable';  // vftable 复位
  sub_5A36E0(this);
  sub_5A3C80(this);  // 调 牛头·透装型装载 2（wrap02 / Horn02）
  return this;
}



// ------------------------------------------------------------
// 0x4A77E0 sub_4A77E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauAssaulter 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A77E0(uint32_t *this)  // 实现：(推断)CNTauAssaulter 析构
{
  *this = &CNTauAssaulter::`vftable';  // vftable 复位
  *(this + 2150) = &CNTauAssaulter::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7850 sub_4A7850 —— CNTauAssaulter（牛头突击兵）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A77E0，降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7850(uint32_t *Block, char pszArg2)  // 函数: CNTauAssaulter（牛头突击兵）删除析构壳
{
  sub_4A77E0(Block);  // 调 (推断)CNTauAssaulter 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7880 sub_4A7880
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRock_Moud 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7880(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRock_Moud 构造
{
  sub_4A7760((int)this, ArgList, nArg3);  // 调 CNTauAssaulter 构造，结果存 result
  *this = &CNRock_Moud::`vftable';  // vftable 复位
  *(this + 2150) = &CNRock_Moud::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A78B0 sub_4A78B0 —— CNRock_Moud 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A78E0，尾调 ·0x4A77E0 CNTauAssaulter 析构）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A78B0(void *Block, char pszArg2)  // 函数: CNRock_Moud 删除析构壳
{
  sub_4A78E0();  // 调 (推断)CNRock_Moud 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A78E0 sub_4A78E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRock_Moud 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A78E0(uint32_t *this)  // 实现：(推断)CNRock_Moud 析构
{
  *this = &CNRock_Moud::`vftable';  // vftable 复位
  *(this + 2150) = &CNRock_Moud::`vftable';  // this+8600 = uAI8600
  return sub_4A77E0(this);  // 返回 (推断)CNTauAssaulter 析构
}



// ------------------------------------------------------------
// 0x4A7900 sub_4A7900
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauGuard（牛头卫兵）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7900(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNTauGuard（牛头卫兵）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNTauGuard::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNTauGuard::`vftable';  // vftable 复位
  sub_5A3E50(this);  // 调 子类相位字节复位（this+8604/8608/8612）
  sub_5A4E70(this);  // 调 牛头精英装载 3（六件 .equ）
  return this;
}



// ------------------------------------------------------------
// 0x4A7980 sub_4A7980 —— CNTauGuard（牛头卫兵）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A79B0，降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7980(void *Block, char pszArg2)  // 函数: CNTauGuard（牛头卫兵）删除析构壳
{
  sub_4A79B0();  // 调 (推断)CNTauGuard 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A79B0 sub_4A79B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauGuard 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A79B0(uint32_t *this)  // 实现：(推断)CNTauGuard 析构
{
  *this = &CNTauGuard::`vftable';  // vftable 复位
  *(this + 2150) = &CNTauGuard::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7A20 sub_4A7A20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauTangas（牛头沙乌塔）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7A20(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNTauTangas（牛头沙乌塔）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNTauTangas::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNTauTangas::`vftable';  // vftable 复位
  nullsub_3(this);
  sub_5A5990(this);  // 调 沙乌塔装载（五件 .equ）
  return this;
}



// ------------------------------------------------------------
// 0x4A7AA0 sub_4A7AA0 —— CNTauTangas 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A7AD0，降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7AA0(void *Block, char pszArg2)  // 函数: CNTauTangas 删除析构壳
{
  sub_4A7AD0();  // 调 (推断)CNTauTangas 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7AD0 sub_4A7AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauTangas 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7AD0(uint32_t *this)  // 实现：(推断)CNTauTangas 析构
{
  *this = &CNTauTangas::`vftable';  // vftable 复位
  *(this + 2150) = &CNTauTangas::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7B40 sub_4A7B40
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7B40(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNGolem::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8636) = 15;  // this+8636〔pDollTarget(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  sub_5A5BB0(this);  // 调 石魔像子类字段复位（this+8600/8604/8644..8672）
  sub_5A6EA0(this);  // 调 埋伏型魔像语音组装载（伏击埋地配置）
  return this;
}



// ------------------------------------------------------------
// 0x4A7BC0 sub_4A7BC0
// ------------------------------------------------------------
// 【解读】
//   【推断】含字符串常量 "STONE_DIE" 的分发调用 —— 魔像族死亡动画/音效触发。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7BC0(void *this)  // 实现：(推断)含字符串常量 STONE_DIE 的分发调用 —— 魔像族死亡动画/音效触发
{
  return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用虚函数（虚表槽 +212）【推断: 音效标签播放（szPassword 去重 → sub_65FE1…】
           this,
           "STONE_DIE",  // 资源/动画 TAG STONE_DIE
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x4A7BE0 sub_4A7BE0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGolem 析构（sub_5A5BF0 + string 释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7BE0(void **this)  // 实现：(推断)CNGolem 析构（sub_5A5BF0 + string 释放）
{
  *this = &CNGolem::`vftable';  // vftable 复位
  sub_5A5BF0();  // 调 槽对象释放（this+2166..2168）
  if ( (unsigned int)*(this + 2159) >= 0x10 )  // this+8636 = pDollTarget
    j__free(*(this + 2154));  // this+8616 = uAI8616
  *(this + 2159) = (void *)15;  // this+8636 = pDollTarget
  *(this + 2158) = nullptr;  // this+8632〔bDevourFlag(推断)〕
  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A7C60 sub_4A7C60 —— CNGolem（魔像族基类）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A7BE0 CNGolem，含 ·0x5A5BF0 与 string@+8616 释放）。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7C60(void **Block, char pszArg2)  // 函数: CNGolem（魔像族基类）删除析构壳
{
  sub_4A7BE0(Block);  // 调 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7C90 sub_4A7C90
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemStone（石魔像）构造（sub_5A7770）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7C90(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemStone（石魔像）构造（sub_5A7770）
{
  sub_4A7B40((int)this, ArgList, nArg3);  // 调 (推断) CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
  *this = &CNGolemStone::`vftable';  // vftable 复位
  sub_5A7770(this);  // 调 SG 魔像四件套装（.equ 挂装面 vt+784）
  return this;
}



// ------------------------------------------------------------
// 0x4A7CF0 sub_4A7CF0 —— CNGolemStone（石魔像）析构体（本批最小析构形基准）
// 【推断】VC++ 派生类析构体最小形态: 复位本类 vftable → 尾调基类析构 ·0x4A7BE0
// （CNGolem 析构: ·0x5A5BF0 专属清理 + string@+8616 释放 + IRDMonster 收尾 ·0x4A50F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7CF0(void **this)  // 函数: CNGolemStone（石魔像）析构体（本批最小析构形基准）
{
  *this = &CNGolemStone::`vftable';  // vftable 复位
  return sub_4A7BE0(this);  // 返回 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
}



// ------------------------------------------------------------
// 0x4A7D00 sub_4A7D00 —— CNGolemStone 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A7CF0 CNGolemStone 析构体）。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7D00(void **Block, char pszArg2)  // 函数: CNGolemStone 删除析构壳
{
  sub_4A7CF0(Block);  // 调 CNGolemStone（石魔像）析构体（本批最小析构形基准）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7D30 sub_4A7D30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemSteel（钢魔像）构造（sub_5A78E0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7D30(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemSteel（钢魔像）构造（sub_5A78E0）
{
  sub_4A7B40((int)this, ArgList, nArg3);  // 调 (推断) CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
  *this = &CNGolemSteel::`vftable';  // vftable 复位
  sub_5A78E0(this);  // 调 ST 魔像四件套 + 三粒子装载（石魔像标准型）
  return this;
}



// ------------------------------------------------------------
// 0x4A7D90 sub_4A7D90 —— CNGolemSteel（钢魔像）析构体
// 与 ·0x4A7CF0 同构（差异：本类 vftable CNGolemSteel）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7D90(void **this)  // 函数: CNGolemSteel（钢魔像）析构体
{
  *this = &CNGolemSteel::`vftable';  // vftable 复位
  return sub_4A7BE0(this);  // 返回 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
}



// ------------------------------------------------------------
// 0x4A7DA0 sub_4A7DA0 —— CNGolemSteel 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A7D90 CNGolemSteel 析构体）。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7DA0(void **Block, char pszArg2)  // 函数: CNGolemSteel 删除析构壳
{
  sub_4A7D90(Block);  // 调 CNGolemSteel（钢魔像）析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7DD0 sub_4A7DD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemBronze（青铜魔像）构造（sub_5A7E30）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7DD0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemBronze（青铜魔像）构造（sub_5A7E30）
{
  sub_4A7D30(this, ArgList, nArg3);  // 调 CNGolemSteel 构造，结果存 result
  *this = &CNGolemBronze::`vftable';  // vftable 复位
  sub_5A7E30(this);  // 调 BR 魔像四件套 + 三粒子（红/铜分色型）
  return this;
}



// ------------------------------------------------------------
// 0x4A7E30 sub_4A7E30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemClay（陶土魔像）构造（sub_5A7B50）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7E30(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemClay（陶土魔像）构造（sub_5A7B50）
{
  sub_4A7B40((int)this, ArgList, nArg3);  // 调 (推断) CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
  *this = &CNGolemClay::`vftable';  // vftable 复位
  sub_5A7B50(this);  // 调 CL 魔像四件套装
  return this;
}



// ------------------------------------------------------------
// 0x4A7E90 sub_4A7E90 —— CNGolemClay 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A7EC0 CNGolemClay 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7E90(void *Block, char pszArg2)  // 函数: CNGolemClay 删除析构壳
{
  sub_4A7EC0();  // 调 CNGolemClay（陶土魔像）析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7EC0 sub_4A7EC0 —— CNGolemClay（陶土魔像）析构体
// 与 ·0x4A7CF0 同构（差异：本类 vftable CNGolemClay）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7EC0(void **this)  // 函数: CNGolemClay（陶土魔像）析构体
{
  *this = &CNGolemClay::`vftable';  // vftable 复位
  return sub_4A7BE0(this);  // 返回 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
}



// ------------------------------------------------------------
// 0x4A7ED0 sub_4A7ED0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemGold（金魔像）构造（sub_5A7CC0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7ED0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemGold（金魔像）构造（sub_5A7CC0）
{
  sub_4A7B40((int)this, ArgList, nArg3);  // 调 (推断) CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
  *this = &CNGolemGold::`vftable';  // vftable 复位
  sub_5A7CC0(this);  // 调 GD 魔像四件套装
  return this;
}



// ------------------------------------------------------------
// 0x4A7F30 sub_4A7F30 —— CNGolemGold 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A7F60 CNGolemGold 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7F30(void *Block, char pszArg2)  // 函数: CNGolemGold 删除析构壳
{
  sub_4A7F60();  // 调 CNGolemGold（金魔像）析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A7F60 sub_4A7F60 —— CNGolemGold（金魔像）析构体
// 与 ·0x4A7CF0 同构（差异：本类 vftable CNGolemGold）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7F60(void **this)  // 函数: CNGolemGold（金魔像）析构体
{
  *this = &CNGolemGold::`vftable';  // vftable 复位
  return sub_4A7BE0(this);  // 返回 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
}



// ------------------------------------------------------------
// 0x4A7F70 sub_4A7F70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemPlatany（白金魔像）构造（sub_5A80A0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7F70(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGolemPlatany（白金魔像）构造（sub_5A80A0）
{
  sub_4A7B40((int)this, ArgList, nArg3);  // 调 (推断) CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）
  *this = &CNGolemPlatany::`vftable';  // vftable 复位
  sub_5A80A0(this);  // 调 GD/PT 五件套 + 部件缩放/攻击系数（1.5 倍档）
  return this;
}



// ------------------------------------------------------------
// 0x4A7FD0 sub_4A7FD0 —— CNGolemPlatany 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8000 CNGolemPlatany 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7FD0(void *Block, char pszArg2)  // 函数: CNGolemPlatany 删除析构壳
{
  sub_4A8000();  // 调 CNGolemPlatany（白金魔像）析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8000 sub_4A8000 —— CNGolemPlatany（白金魔像）析构体
// 与 ·0x4A7CF0 同构（差异：本类 vftable CNGolemPlatany）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8000(void **this)  // 函数: CNGolemPlatany（白金魔像）析构体
{
  *this = &CNGolemPlatany::`vftable';  // vftable 复位
  return sub_4A7BE0(this);  // 返回 (推断)CNGolem 析构（sub_5A5BF0 + string 释放）
}



// ------------------------------------------------------------
// 0x4A8010 sub_4A8010
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStoneBlade_Razor 构造（继承 CNGolemStone 前缀）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8010(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStoneBlade_Razor 构造（继承 CNGolemStone 前缀）
{
  sub_4A7C90(this, ArgList, nArg3);  // 调 CNGolemStone 构造，结果存 result
  *this = &CNStoneBlade_Razor::`vftable';  // vftable 复位
  return this;
}



// ============================================================
// SECTION 0x4A8040 — 怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Sharedo）
// ============================================================
// ------------------------------------------------------------
// 0x4A8040 sub_4A8040
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDollMaster（人偶大师）构造（sub_5A82B0/5A9DA0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8040(char *this, char ArgList, int nArg3)  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNDollMaster::`vftable';  // vftable 复位
  sub_5A82B0(this);  // 调 人偶师子类字段复位（this+8600..8668）
  sub_5A9DA0(this);  // 调 人偶师装载初始化（DOLL_DMG/DOLL_DIE 语音池 + DollMaster.equ 外观）
  return this;
}



// ------------------------------------------------------------
// 0x4A80A0 sub_4A80A0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDollMaster 析构（sub_5A8300）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A80A0(uint32_t *this)  // 实现：(推断)CNDollMaster 析构（sub_5A8300）
{
  *this = &CNDollMaster::`vftable';  // vftable 复位
  sub_5A8300();  // 调 this+2163 槽对象释放
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A80F0 sub_4A80F0 —— CNDollMaster（人偶大师）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A80A0，含 ·0x5A8300 专属清理）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A80F0(uint32_t *Block, char pszArg2)  // 函数: CNDollMaster（人偶大师）删除析构壳
{
  sub_4A80A0(Block);  // 调 (推断)CNDollMaster 析构（sub_5A8300）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8120 sub_4A8120
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStoneMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8120(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStoneMaster 构造
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNStoneMaster::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A8150 sub_4A8150 —— CNStoneMaster 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8180 CNStoneMaster 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8150(void *Block, char pszArg2)  // 函数: CNStoneMaster 删除析构壳
{
  sub_4A8180();  // 调 CNStoneMaster 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8180 sub_4A8180 —— CNStoneMaster 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A80A0 CNDollMaster 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8180(uint32_t *this)  // 函数: CNStoneMaster 析构体
{
  *this = &CNStoneMaster::`vftable';  // vftable 复位
  return sub_4A80A0(this);  // 返回 (推断)CNDollMaster 析构（sub_5A8300）
}



// ------------------------------------------------------------
// 0x4A8190 sub_4A8190
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSteelMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8190(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSteelMaster 构造
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNSteelMaster::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A81C0 sub_4A81C0 —— CNSteelMaster 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A81F0 CNSteelMaster 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A81C0(void *Block, char pszArg2)  // 函数: CNSteelMaster 删除析构壳
{
  sub_4A81F0();  // 调 CNSteelMaster 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A81F0 sub_4A81F0 —— CNSteelMaster 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A80A0 CNDollMaster 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A81F0(uint32_t *this)  // 函数: CNSteelMaster 析构体
{
  *this = &CNSteelMaster::`vftable';  // vftable 复位
  return sub_4A80A0(this);  // 返回 (推断)CNDollMaster 析构（sub_5A8300）
}



// ------------------------------------------------------------
// 0x4A8200 sub_4A8200
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNClayMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8200(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNClayMaster 构造
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNClayMaster::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A8230 sub_4A8230 —— CNClayMaster 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8260 CNClayMaster 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8230(void *Block, char pszArg2)  // 函数: CNClayMaster 删除析构壳
{
  sub_4A8260();  // 调 CNClayMaster 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8260 sub_4A8260 —— CNClayMaster 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A80A0 CNDollMaster 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8260(uint32_t *this)  // 函数: CNClayMaster 析构体
{
  *this = &CNClayMaster::`vftable';  // vftable 复位
  return sub_4A80A0(this);  // 返回 (推断)CNDollMaster 析构（sub_5A8300）
}



// ------------------------------------------------------------
// 0x4A8270 sub_4A8270
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNMasterDogri 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8270(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNMasterDogri 构造
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNMasterDogri::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A82A0 sub_4A82A0 —— CNMasterDogri 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A82D0 CNMasterDogri 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A82A0(void *Block, char pszArg2)  // 函数: CNMasterDogri 删除析构壳
{
  sub_4A82D0();  // 调 CNMasterDogri 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A82D0 sub_4A82D0 —— CNMasterDogri 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A80A0 CNDollMaster 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A82D0(uint32_t *this)  // 函数: CNMasterDogri 析构体
{
  *this = &CNMasterDogri::`vftable';  // vftable 复位
  return sub_4A80A0(this);  // 返回 (推断)CNDollMaster 析构（sub_5A8300）
}



// ------------------------------------------------------------
// 0x4A82E0 sub_4A82E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNIceDoll_Sharedo（冰人偶）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A82E0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNIceDoll_Sharedo（冰人偶）构造
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNIceDoll_Sharedo::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A8310 sub_4A8310 —— CNIceDoll_Sharedo（冰人偶）删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8340 CNIceDoll_Sharedo 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8310(void *Block, char pszArg2)  // 函数: CNIceDoll_Sharedo（冰人偶）删除析构壳
{
  sub_4A8340();  // 调 CNIceDoll_Sharedo 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8340 sub_4A8340 —— CNIceDoll_Sharedo 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A80A0 CNDollMaster 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8340(uint32_t *this)  // 函数: CNIceDoll_Sharedo 析构体
{
  *this = &CNIceDoll_Sharedo::`vftable';  // vftable 复位
  return sub_4A80A0(this);  // 返回 (推断)CNDollMaster 析构（sub_5A8300）
}



// ============================================================
// SECTION 0x4A8350 — 怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350-0x4ABDC0）
// ============================================================
// ------------------------------------------------------------
// 0x4A8350 sub_4A8350
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFlyDragon（飞龙）构造 —— 龙族继承链基。
//   100 行初始化（内嵌结构多）。后续 CNDrakeSerimalion 等经此继承。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8350(int this, char ArgList, int nArg3)  // 函数 sub_4A8350：怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350 0x4ABDC0）
{
  int pCandTbl8708; // eax  | +0x2204 → 【推断】候选表首针（4 字节元素；4A8350 构造推入 15/80/135 三项）〔5AA6A0 随机抽取源〕（CNFlyDragon；va=005AA6A0）
  unsigned int fld_2208; // edx  | +0x2208 → 【推断】候选表尾针（元素数=(8712-8708)>>2）〔5AA6A0 rand()%n 上界〕（CNFlyDragon；va=005AA6A0）
  uint32_t *nCandTblEnd8712; // eax
  int pCandTbl8708_; // edx  | +0x2204 → 【推断】候选表首针（4 字节元素；4A8350 构造推入 15/80/135 三项）〔5AA6A0 随机抽取源〕（CNFlyDragon；va=005AA6A0）
  unsigned int fld_22083; // ecx  | +0x2208 → 【推断】候选表尾针（元素数=(8712-8708)>>2）〔5AA6A0 rand()%n 上界〕（CNFlyDragon；va=005AA6A0）
  uint32_t *nCandTblEnd8712_; // eax
  int pCandTbl8708_2; // edx  | +0x2204 → 【推断】候选表首针（4 字节元素；4A8350 构造推入 15/80/135 三项）〔5AA6A0 随机抽取源〕（CNFlyDragon；va=005AA6A0）
  unsigned int fld_22085; // ecx  | +0x2208 → 【推断】候选表尾针（元素数=(8712-8708)>>2）〔5AA6A0 rand()%n 上界〕（CNFlyDragon；va=005AA6A0）
  uint32_t *nCandTblEnd8712_2; // eax

  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNFlyDragon::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8660) = 15;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint8_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  *(uint32_t *)(this + 8688) = 15;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8684) = 0;  // this+8684〔bGate8684(推断)〕
  *(uint8_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  *(uint32_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(uint32_t *)(this + 8712) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  *(uint32_t *)(this + 8716) = 0;  // this+8716〔uArr8716〕
  *(uint8_t *)(this + 8724) = 0;  // this+8724〔nSegThrEnd8724〕
  *(uint32_t *)(this + 8720) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8728) = 0;  // this+8728〔nSegThrCap8728〕
  *(uint8_t *)(this + 8732) = 1;  // this+8732〔bSegLatch8732〕
  *(uint8_t *)(this + 8734) = 0;
  *(uint8_t *)(this + 8733) = 0;
  *(uint32_t *)(this + 8744) = 0;  // this+8744〔nCountdown8744(推断)〕
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8736) = 0;
  *(uint8_t *)(this + 8752) = 0;
  *(uint32_t *)(this + 8748) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8756) = 0;
  *(uint8_t *)(this + 8760) = 1;
  *(uint8_t *)(this + 8762) = 0;  // this+8762〔bAI8762〕
  *(uint8_t *)(this + 8761) = 0;  // this+8761〔bAI8761〕
  *(uint32_t *)(this + 8772) = 0;  // this+8772〔nAltDeadline8772〕
  *(uint32_t *)(this + 8768) = 0;
  *(uint32_t *)(this + 8764) = 0;  // this+8764〔uPhase8764〕
  nArg3 = 15;
  pCandTbl8708 = *(uint32_t *)(this + 8708);  // this+8708〔pCandTbl8708(推断)〕
  if ( pCandTbl8708 != 0 )  // fld_2204=this+8708 pCandTbl8708
    fld_2208 = (*(uint32_t *)(this + 8712) - pCandTbl8708) >> 2;  // this+8712〔nCandTblEnd8712(推断)〕
  else
    fld_2208 = 0;  // fld_2208=this+8712 nCandTblEnd8712
  if ( pCandTbl8708 != 0 && fld_2208 < (*(uint32_t *)(this + 8716) - pCandTbl8708) >> 2 )  // this+8716〔uArr8716〕
  {
    nCandTblEnd8712 = *(uint32_t **)(this + 8712);  // this+8712 【推断】候选表尾针
    *nCandTblEnd8712 = 15;  // fld_22082=this+8712 【推断】候选表尾针
    *(uint32_t *)(this + 8712) = nCandTblEnd8712 + 1;  // this+8712〔nCandTblEnd8712(推断)〕
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);  // 调 uint32 vector 区间插入（同值填充）
  }
  pCandTbl8708_ = *(uint32_t *)(this + 8708);  // this+8708〔pCandTbl8708(推断)〕
  nArg3 = 80;
  if ( pCandTbl8708_ != 0 )  // fld_22042=this+8708 pCandTbl8708
    fld_22083 = (*(uint32_t *)(this + 8712) - pCandTbl8708_) >> 2;  // this+8712〔nCandTblEnd8712(推断)〕
  else
    fld_22083 = 0;  // fld_22083=this+8712 nCandTblEnd8712
  if ( pCandTbl8708_ != 0 && fld_22083 < (*(uint32_t *)(this + 8716) - pCandTbl8708_) >> 2 )  // this+8716〔uArr8716〕
  {
    nCandTblEnd8712_ = *(uint32_t **)(this + 8712);  // this+8712 【推断】候选表尾针
    *nCandTblEnd8712_ = 80;  // fld_22084=this+8712 【推断】候选表尾针
    *(uint32_t *)(this + 8712) = nCandTblEnd8712_ + 1;  // this+8712〔nCandTblEnd8712(推断)〕
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);  // 调 uint32 vector 区间插入（同值填充）
  }
  pCandTbl8708_2 = *(uint32_t *)(this + 8708);  // this+8708〔pCandTbl8708(推断)〕
  nArg3 = 135;
  if ( pCandTbl8708_2 != 0 )  // fld_22043=this+8708 pCandTbl8708
    fld_22085 = (*(uint32_t *)(this + 8712) - pCandTbl8708_2) >> 2;  // this+8712〔nCandTblEnd8712(推断)〕
  else
    fld_22085 = 0;  // fld_22085=this+8712 nCandTblEnd8712
  if ( pCandTbl8708_2 != 0 && fld_22085 < (*(uint32_t *)(this + 8716) - pCandTbl8708_2) >> 2 )  // this+8716〔uArr8716〕
  {
    nCandTblEnd8712_2 = *(uint32_t **)(this + 8712);  // this+8712 【推断】候选表尾针
    *nCandTblEnd8712_2 = 135;  // fld_22086=this+8712 【推断】候选表尾针
    *(uint32_t *)(this + 8712) = nCandTblEnd8712_2 + 1;  // this+8712〔nCandTblEnd8712(推断)〕
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);  // 调 uint32 vector 区间插入（同值填充）
  }
  sub_5A9FF0(this);  // 调 蓄力阈值与倒计时复位（this+8600 = 0, this+8696 = 1000）
  sub_5AC500(this);  // 调 飞龙语音装载（FLYDRAGON_HIT/DMG/DIE + FLYDRAGON_CRY 龙吟）
  *(uint8_t *)(this + 8733) = 0;
  *(uint8_t *)(this + 8734) = 0;
  *(uint8_t *)(this + 8701) = 0;
  *(uint8_t *)(this + 8700) = 0;  // this+8700〔uPhase8700(推断)〕
  return this;
}



// ------------------------------------------------------------
// 0x4A8560 sub_4A8560
// ------------------------------------------------------------
// 【解读】
//   【推断】CNFlyDragon 析构（含 IObject @+8748）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8560(int this)  // 实现：(推断)CNFlyDragon 析构（含 IObject @+8748）
{
  *(uint32_t *)this = &CNFlyDragon::`vftable';  // vftable 复位
  nullsub_3(this);
  *(uint32_t *)(this + 8748) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8752) = 0;
  *(uint32_t *)(this + 8720) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8724) = 0;  // this+8724〔nSegThrEnd8724〕
  if ( *(uint32_t *)(this + 8708) != 0 )  // this+8708〔pCandTbl8708(推断)〕
    j__free(*(void **)(this + 8708));  // 调 堆释放
  *(uint32_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(uint32_t *)(this + 8712) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  *(uint32_t *)(this + 8716) = 0;  // this+8716〔uArr8716〕
  if ( *(uint32_t *)(this + 8688) >= 0x10u )  // this+8688〔bVec8688(推断)〕
    j__free(*(void **)(this + 8668));  // 调 堆释放
  *(uint32_t *)(this + 8688) = 15;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8684) = 0;  // this+8684〔bGate8684(推断)〕
  *(uint8_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  if ( *(uint32_t *)(this + 8660) >= 0x10u )  // this+8660〔uEvt8660(推断)〕
    j__free(*(void **)(this + 8640));  // 调 堆释放
  *(uint32_t *)(this + 8660) = 15;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint8_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A8650 sub_4A8650 —— CNFlyDragon（飞龙）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A8560，含 IObject @+8720/+8748 复位、
// 动态数组 @+8708 与两处 string 释放、IRDMonster 收尾 ·0x4A50F0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8650(void *Block, char pszArg2)  // 函数: CNFlyDragon（飞龙）删除析构壳
{
  sub_4A8560((int)Block);  // 调 (推断)CNFlyDragon 析构（含 IObject @+8748）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8680 sub_4A8680
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeSerimalion 构造（+8788 标志）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A8680(uint8_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDrakeSerimalion 构造（+8788 标志）
{
  int pThis_5D4; // [esp+20h] [ebp+Ch]

  sub_4A8350((int)this, ArgList, nArg3);  // 调 怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350 0x4ABDC0）
  *(uint32_t *)this = &CNDrakeSerimalion::`vftable';  // vftable 复位
  *(this + 8788) = 0;
  *((uint32_t *)this + 2196) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 2198) = 0;
  *(this + 8796) = 1;
  *(this + 8798) = 0;
  *(this + 8797) = 0;
  *((uint32_t *)this + 2202) = 0;
  *((uint32_t *)this + 2201) = 0;
  *((uint32_t *)this + 2200) = 0;
  *((uint32_t *)this + 2194) = -1;
  pThis_5D4 = sub_41A5E0((unsigned int)(this + 1492));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  *((uint32_t *)this + 2195) = (uint64_t)((double)pThis_5D4 * COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 1506))));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  return this;
}



// ------------------------------------------------------------
// 0x4A8750 sub_4A8750 —— CNDrakeSerimalion 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A8780，含 IObject @+8784 复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8750(void *Block, char pszArg2)  // 函数: CNDrakeSerimalion 删除析构壳
{
  sub_4A8780();  // 调 (推断)CNDrakeSerimalion 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8780 sub_4A8780
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeSerimalion 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8780(int this)  // 实现：(推断)CNDrakeSerimalion 析构
{
  *(uint32_t *)this = &CNDrakeSerimalion::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8784) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8788) = 0;
  return sub_4A8560(this);  // 返回 (推断)CNFlyDragon 析构（含 IObject @+8748）
}



// ------------------------------------------------------------
// 0x4A87A0 sub_4A87A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeLooseSerimalion 构造（参数 void* Block 复用）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A87A0(uint8_t *this, char ArgList, void *Block)  // 实现：(推断)★ CNDrakeLooseSerimalion 构造（参数 void* Block 复用）
{
  uint32_t *pMem; // eax

  sub_4A8350((int)this, ArgList, (int)Block);  // 调 怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350 0x4ABDC0）
  *(uint32_t *)this = &CNDrakeLooseSerimalion::`vftable';  // vftable 复位
  *(this + 8780) = 0;  // this+8780 相位镜像
  *((uint32_t *)this + 2194) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *((uint32_t *)this + 2196) = 0;
  *(this + 8788) = 1;
  *(this + 8790) = 0;
  *(this + 8789) = 0;
  *((uint32_t *)this + 2200) = 0;
  *((uint32_t *)this + 2199) = 0;
  *((uint32_t *)this + 2198) = 0;
  *(this + 8808) = 0;
  *((uint32_t *)this + 2201) = -1;
  *(this + 8789) = 0;
  *(this + 8790) = 0;
  pMem = operator new(0x12Cu);  // operator new 分配 300 字节
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    *((uint32_t *)this + 2203) = sub_428F30(pMem, (int)"PassiveObject/Monster/FlyDragon/Particle/Bouncer.ptl", 0);  // 调 CNRDObjectParticleCreater 构造
  else
    *((uint32_t *)this + 2203) = 0;  // this+8812〔uCharge8812(推断)〕
  return this;
}



// ------------------------------------------------------------
// 0x4A8890 sub_4A8890 —— CNDrakeLooseSerimalion 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A88C0，虚调释放 +8812 粒子对象后转 ·0x4A8560）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8890(void *Block, char pszArg2)  // 函数: CNDrakeLooseSerimalion 删除析构壳
{
  sub_4A88C0();  // 调 (推断)CNDrakeLooseSerimalion 析构（含 +8812 指针的虚调）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A88C0 sub_4A88C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeLooseSerimalion 析构（含 +8812 指针的虚调）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A88C0(uint32_t *this)  // 实现：(推断)CNDrakeLooseSerimalion 析构（含 +8812 指针的虚调）
{
  void (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  *this = &CNDrakeLooseSerimalion::`vftable';  // vftable 复位
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);  // this+8812〔uCharge8812(推断)〕
  if ( v2 != nullptr )  // 若 v2 有效（非空）
    (**v2)(v2, 1);  // 调 v2 的虚函数（vt+0）
  *(this + 2203) = 0;  // this+8812〔uCharge8812(推断)〕
  *(this + 2194) = &nengine::IObject::`vftable';  // vftable 复位
  *((uint8_t *)this + 8780) = 0;  // this+8780 相位镜像
  return sub_4A8560((int)this);  // 返回 (推断)CNFlyDragon 析构（含 IObject @+8748）
}



// ------------------------------------------------------------
// 0x4A8940 sub_4A8940
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeHarseSerimalion 构造（+8780=-1/+8776=0 计时器初始化）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8940(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDrakeHarseSerimalion 构造（+8780=-1/+8776=0 计时器初始化）
{
  sub_4A8350((int)this, ArgList, nArg3);  // 调 怪物子类构造/析构批 C（CNFlyDragon 龙族 → CNTitan 巨人族，0x4A8350 0x4ABDC0）
  *this = &CNDrakeHarseSerimalion::`vftable';  // vftable 复位
  *(this + 2195) = -1;
  *(this + 2194) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8980 sub_4A8980 —— CNDrakeHarseSerimalion 删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A89B0，仅复位 vftable 后转 ·0x4A8560）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8980(void *Block, char pszArg2)  // 函数: CNDrakeHarseSerimalion 删除析构壳
{
  sub_4A89B0();  // 调 (推断)CNDrakeHarseSerimalion 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A89B0 sub_4A89B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeHarseSerimalion 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89B0(int this)  // 实现：(推断)CNDrakeHarseSerimalion 析构
{
  *(uint32_t *)this = &CNDrakeHarseSerimalion::`vftable';  // vftable 复位
  return sub_4A8560(this);  // 返回 (推断)CNFlyDragon 析构（含 IObject @+8748）
}



// ------------------------------------------------------------
// 0x4A89C0 sub_4A89C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeSelionTheFireBreather（喷火塞利昂）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89C0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNDrakeSelionTheFireBreather（喷火塞利昂）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNDrakeSelionTheFireBreather::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8612) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8624) = 1;  // this+8624〔uAI8624(推断)〕
  *(uint8_t *)(this + 8626) = 0;
  *(uint8_t *)(this + 8625) = 0;
  *(uint32_t *)(this + 8636) = 0;  // this+8636〔pDollTarget(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  sub_5AA340(this);
  sub_5ACE30(this);  // 调 飞龙火息装载（FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + FireBreath 粒子）
  return this;
}



// ------------------------------------------------------------
// 0x4A8A60 sub_4A8A60 —— CNDrakeSelionTheFireBreather（喷火塞利昂）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A8A90，含 ·0x5AA350 与 IObject @+8612 复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8A60(void *Block, char pszArg2)  // 函数: CNDrakeSelionTheFireBreather（喷火塞利昂）删除析构壳
{
  sub_4A8A90();  // 调 (推断)CNDrakeSelionTheFireBreather 析构（sub_5AA350 + IObject @+8612）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8A90 sub_4A8A90
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeSelionTheFireBreather 析构（sub_5AA350 + IObject @+8612）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8A90(uint32_t *this)  // 实现：(推断)CNDrakeSelionTheFireBreather 析构（sub_5AA350 + IObject @+8612）
{
  *this = &CNDrakeSelionTheFireBreather::`vftable';  // vftable 复位
  sub_5AA350();
  *(this + 2153) = &nengine::IObject::`vftable';  // this+8612 = uAI8612
  *((uint8_t *)this + 8616) = 0;  // this+8616 = uAI8616
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A8AF0 sub_4A8AF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunter（猎人）构造（+8648=15/+8644 归零 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8AF0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNHunter（猎人）构造（+8648=15/+8644 归零 string）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNHunter::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8648) = 15;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  nullsub_3(this);
  sub_5ADB10(this);  // 调 猎人语音装载表（6792..6872 索引面 + 五 TAG 写槽）
  return this;
}



// ------------------------------------------------------------
// 0x4A8B70 sub_4A8B70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNHunter 析构（string @+8628 释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8B70(void **this)  // 实现：(推断)CNHunter 析构（string @+8628 释放）
{
  *this = &CNHunter::`vftable';  // vftable 复位
  nullsub_3(this);
  if ( (unsigned int)*(this + 2162) >= 0x10 )  // this+8648 = 相位/缓存槽
    j__free(*(this + 2157));  // this+8628 = 指挥计时戳
  *(this + 2162) = (void *)15;  // this+8648 = 相位/缓存槽
  *(this + 2161) = nullptr;  // this+8644 = 相位槽
  *((uint8_t *)this + 8628) = 0;  // this+8628 = 指挥计时戳
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A8BF0 sub_4A8BF0 —— CNHunter（猎人）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A8B70，含 string@+8628 释放）。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A8BF0(void **Block, char pszArg2)  // 函数: CNHunter（猎人）删除析构壳
{
  sub_4A8B70(Block);  // 调 (推断)CNHunter 析构（string @+8628 释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8C20 sub_4A8C20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterMaster 构造（sub_5ADFE0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8C20(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNHunterMaster 构造（sub_5ADFE0）
{
  sub_4A8AF0((int)this, ArgList, nArg3);  // 调 (推断) CNHunter（猎人）构造（+8648=15/+8644 归零 string）
  *this = &CNHunterMaster::`vftable';  // vftable 复位
  sub_5ADFE0(this);  // 调 HH 猎人外观装载（.equ 面 + 8648/8600/7576 相位）
  return this;
}



// ------------------------------------------------------------
// 0x4A8C80 sub_4A8C80 —— CNHunterMaster 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8CB0 CNHunterMaster 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8C80(void *Block, char pszArg2)  // 函数: CNHunterMaster 删除析构壳
{
  sub_4A8CB0();  // 调 CNHunterMaster 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8CB0 sub_4A8CB0 —— CNHunterMaster 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8B70 CNHunter 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8CB0(void **this)  // 函数: CNHunterMaster 析构体
{
  *this = &CNHunterMaster::`vftable';  // vftable 复位
  return sub_4A8B70(this);  // 返回 (推断)CNHunter 析构（string @+8628 释放）
}



// ------------------------------------------------------------
// 0x4A8CC0 sub_4A8CC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterAlex 构造（sub_5AE160）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8CC0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNHunterAlex 构造（sub_5AE160）
{
  sub_4A8AF0((int)this, ArgList, nArg3);  // 调 (推断) CNHunter（猎人）构造（+8648=15/+8644 归零 string）
  *this = &CNHunterAlex::`vftable';  // vftable 复位
  sub_5AE160(this);  // 调 HM 猎人外观装载（三件 .equ：horn/hair/clothes）
  return this;
}



// ------------------------------------------------------------
// 0x4A8D20 sub_4A8D20 —— CNHunterAlex 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8D50 CNHunterAlex 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8D20(void *Block, char pszArg2)  // 函数: CNHunterAlex 删除析构壳
{
  sub_4A8D50();  // 调 CNHunterAlex 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8D50 sub_4A8D50 —— CNHunterAlex 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8B70 CNHunter 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8D50(void **this)  // 函数: CNHunterAlex 析构体
{
  *this = &CNHunterAlex::`vftable';  // vftable 复位
  return sub_4A8B70(this);  // 返回 (推断)CNHunter 析构（string @+8628 释放）
}



// ------------------------------------------------------------
// 0x4A8D60 sub_4A8D60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterHunter 构造（sub_5AE290）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8D60(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNHunterHunter 构造（sub_5AE290）
{
  sub_4A8AF0((int)this, ArgList, nArg3);  // 调 (推断) CNHunter（猎人）构造（+8648=15/+8644 归零 string）
  *this = &CNHunterHunter::`vftable';  // vftable 复位
  sub_5AE290(this);  // 调 HA 猎人外观装载（三件 .equ：horn/clothes/blindfold 蒙眼布）
  return this;
}



// ------------------------------------------------------------
// 0x4A8DC0 sub_4A8DC0 —— CNHunterHunter 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8DF0 CNHunterHunter 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8DC0(void *Block, char pszArg2)  // 函数: CNHunterHunter 删除析构壳
{
  sub_4A8DF0();  // 调 CNHunterHunter 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8DF0 sub_4A8DF0 —— CNHunterHunter 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8B70 CNHunter 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8DF0(void **this)  // 函数: CNHunterHunter 析构体
{
  *this = &CNHunterHunter::`vftable';  // vftable 复位
  return sub_4A8B70(this);  // 返回 (推断)CNHunter 析构（string @+8628 释放）
}



// ------------------------------------------------------------
// 0x4A8E00 sub_4A8E00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombie（僵尸）构造（sub_5AE3E0/5AF220）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8E00(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNZombie::`vftable';  // vftable 复位
  sub_5AE3E0(this);  // 调 攻击相位面清零（2150/2151/2158 + 2160 三连清）
  sub_5AF220(this);  // 调 僵尸四段语音装载与相位解除
  return this;
}



// ------------------------------------------------------------
// 0x4A8E60 sub_4A8E60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZombie 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8E60(uint32_t *this)  // 实现：(推断)CNZombie 析构
{
  *this = &CNZombie::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A8EB0 sub_4A8EB0 —— CNZombie（僵尸）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A8E60，含 nullsub_3 与 IRDMonster 收尾 ·0x4A50F0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8EB0(uint32_t *Block, char pszArg2)  // 函数: CNZombie（僵尸）删除析构壳
{
  sub_4A8E60(Block);  // 调 (推断)CNZombie 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8EE0 sub_4A8EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieZombie 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8EE0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNZombieZombie 构造
{
  sub_4A8E00(this, ArgList, nArg3);  // 调 (推断) CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
  *(uint32_t *)this = &CNZombieZombie::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A8F10 sub_4A8F10 —— CNZombieZombie 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8F40 CNZombieZombie 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F10(void *Block, char pszArg2)  // 函数: CNZombieZombie 删除析构壳
{
  sub_4A8F40();  // 调 CNZombieZombie 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8F40 sub_4A8F40 —— CNZombieZombie 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8E60 CNZombie 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8F40(uint32_t *this)  // 函数: CNZombieZombie 析构体
{
  *this = &CNZombieZombie::`vftable';  // vftable 复位
  return sub_4A8E60(this);  // 返回 (推断)CNZombie 析构
}



// ------------------------------------------------------------
// 0x4A8F50 sub_4A8F50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieHollowEye（空洞眼僵尸）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8F50(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNZombieHollowEye（空洞眼僵尸）构造
{
  sub_4A8E00(this, ArgList, nArg3);  // 调 (推断) CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
  *(uint32_t *)this = &CNZombieHollowEye::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A8F80 sub_4A8F80 —— CNZombieHollowEye（空洞眼僵尸）删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A8FB0 CNZombieHollowEye 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F80(void *Block, char pszArg2)  // 函数: CNZombieHollowEye（空洞眼僵尸）删除析构壳
{
  sub_4A8FB0();  // 调 CNZombieHollowEye 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A8FB0 sub_4A8FB0 —— CNZombieHollowEye 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8E60 CNZombie 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8FB0(uint32_t *this)  // 函数: CNZombieHollowEye 析构体
{
  *this = &CNZombieHollowEye::`vftable';  // vftable 复位
  return sub_4A8E60(this);  // 返回 (推断)CNZombie 析构
}



// ------------------------------------------------------------
// 0x4A8FC0 sub_4A8FC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieGhoulgwish 构造（sub_5AE830 覆写加载）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8FC0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNZombieGhoulgwish 构造（sub_5AE830 覆写加载）
{
  sub_4A8E00(this, ArgList, nArg3);  // 调 (推断) CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
  *(uint32_t *)this = &CNZombieGhoulgwish::`vftable';  // vftable 复位
  sub_5AE830(this);  // 调 属性注册（196613 号 + 100000 参）
  return this;
}



// ------------------------------------------------------------
// 0x4A9020 sub_4A9020 —— CNZombieGhoulgwish 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A9050 CNZombieGhoulgwish 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9020(void *Block, char pszArg2)  // 函数: CNZombieGhoulgwish 删除析构壳
{
  sub_4A9050();  // 调 CNZombieGhoulgwish 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9050 sub_4A9050 —— CNZombieGhoulgwish 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8E60 CNZombie 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9050(uint32_t *this)  // 函数: CNZombieGhoulgwish 析构体
{
  *this = &CNZombieGhoulgwish::`vftable';  // vftable 复位
  return sub_4A8E60(this);  // 返回 (推断)CNZombie 析构
}



// ------------------------------------------------------------
// 0x4A9060 sub_4A9060
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKalkazak 构造（+8652/+8656 双槽清零）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9060(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNKalkazak 构造（+8652/+8656 双槽清零）
{
  sub_4A8E00((char *)this, ArgList, nArg3);  // 调 (推断) CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
  *(uint32_t *)(this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint32_t *)this = &CNKalkazak::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A9090 sub_4A9090 —— CNKalkazak 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A90C0 CNKalkazak 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9090(void *Block, char pszArg2)  // 函数: CNKalkazak 删除析构壳
{
  sub_4A90C0();  // 调 CNKalkazak 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A90C0 sub_4A90C0 —— CNKalkazak 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8E60 CNZombie 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A90C0(uint32_t *this)  // 函数: CNKalkazak 析构体
{
  *this = &CNKalkazak::`vftable';  // vftable 复位
  return sub_4A8E60(this);  // 返回 (推断)CNZombie 析构
}



// ------------------------------------------------------------
// 0x4A90D0 sub_4A90D0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBurningHela（燃烧海拉）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A90D0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNBurningHela（燃烧海拉）构造
{
  sub_4A8E00(this, ArgList, nArg3);  // 调 (推断) CNZombie（僵尸）构造（sub_5AE3E0/5AF220）
  *(uint32_t *)this = &CNBurningHela::`vftable';  // vftable 复位
  *(this + 8652) = 0;  // this+8652 【推断】相位门字节
  return this;
}



// ------------------------------------------------------------
// 0x4A9100 sub_4A9100 —— CNBurningHela（燃烧海拉）删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A9130 CNBurningHela 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9100(void *Block, char pszArg2)  // 函数: CNBurningHela（燃烧海拉）删除析构壳
{
  sub_4A9130();  // 调 CNBurningHela 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9130 sub_4A9130 —— CNBurningHela 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A8E60 CNZombie 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9130(uint32_t *this)  // 函数: CNBurningHela 析构体
{
  *this = &CNBurningHela::`vftable';  // vftable 复位
  return sub_4A8E60(this);  // 返回 (推断)CNZombie 析构
}



// ------------------------------------------------------------
// 0x4A9140 sub_4A9140
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDraconian（龙人）构造（sub_5AF910/5B0660）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9140(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDraconian（龙人）构造（sub_5AF910/5B0660）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNDraconian::`vftable';  // vftable 复位
  sub_5AF910(this);  // 调 子类扩展字段整块复位
  sub_5B0660(this);  // 调 龙人·语音槽与属性注册（构造期）
  return this;
}



// ------------------------------------------------------------
// 0x4A91A0 sub_4A91A0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDraconian 析构（sub_5AF950）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A91A0(uint32_t *this)  // 实现：(推断)CNDraconian 析构（sub_5AF950）
{
  *this = &CNDraconian::`vftable';  // vftable 复位
  sub_5AF950();  // 调 两挂装槽释放
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A91F0 sub_4A91F0 —— CNDraconian（龙人）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A91A0，含 ·0x5AF950 专属清理后转 IRDMonster 收尾）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A91F0(uint32_t *Block, char pszArg2)  // 函数: CNDraconian（龙人）删除析构壳
{
  sub_4A91A0(Block);  // 调 (推断)CNDraconian 析构（sub_5AF950）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9220 sub_4A9220
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDracoMirkius 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9220(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDracoMirkius 构造
{
  sub_4A9140(this, ArgList, nArg3);  // 调 (推断) CNDraconian（龙人）构造（sub_5AF910/5B0660）
  *(uint32_t *)this = &CNDracoMirkius::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4A9250 sub_4A9250 —— CNDracoMirkius 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A9280 CNDracoMirkius 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9250(void *Block, char pszArg2)  // 函数: CNDracoMirkius 删除析构壳
{
  sub_4A9280();  // 调 CNDracoMirkius 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9280 sub_4A9280 —— CNDracoMirkius 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A91A0 CNDraconian 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9280(uint32_t *this)  // 函数: CNDracoMirkius 析构体
{
  *this = &CNDracoMirkius::`vftable';  // vftable 复位
  return sub_4A91A0(this);  // 返回 (推断)CNDraconian 析构（sub_5AF950）
}



// ------------------------------------------------------------
// 0x4A9290 sub_4A9290
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDracoLakius 构造（sub_5B1890）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9290(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDracoLakius 构造（sub_5B1890）
{
  sub_4A9140(this, ArgList, nArg3);  // 调 (推断) CNDraconian（龙人）构造（sub_5AF910/5B0660）
  *(uint32_t *)this = &CNDracoLakius::`vftable';  // vftable 复位
  sub_5B1890(this);  // 调 鲁卡斯·外观装载（armor.equ）
  return this;
}



// ------------------------------------------------------------
// 0x4A92F0 sub_4A92F0 —— CNDracoLakius 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A91A0 CNDraconian 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A92F0(uint32_t *this)  // 函数: CNDracoLakius 析构体
{
  *this = &CNDracoLakius::`vftable';  // vftable 复位
  return sub_4A91A0(this);  // 返回 (推断)CNDraconian 析构（sub_5AF950）
}



// ------------------------------------------------------------
// 0x4A9300 sub_4A9300 —— CNDracoLakius 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A92F0 CNDracoLakius 析构体）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9300(uint32_t *Block, char pszArg2)  // 函数: CNDracoLakius 删除析构壳
{
  sub_4A92F0(Block);  // 调 CNDracoLakius 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9330 sub_4A9330
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAuraHunter_Sius（光环猎人西斯）构造（sub_5AFDD0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9330(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNAuraHunter_Sius（光环猎人西斯）构造（sub_5AFDD0）
{
  sub_4A9290(this, ArgList, nArg3);  // 调 CNDracoLakius 构造，结果存 result
  *(uint32_t *)this = &CNAuraHunter_Sius::`vftable';  // vftable 复位
  sub_5AFDD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9390 sub_4A9390
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLordofLightBase（光之领主基）构造（sub_5B1910/5B2720）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9390(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLordofLightBase（光之领主基）构造（sub_5B1910/5B2720）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNLordofLightBase::`vftable';  // vftable 复位
  sub_5B1910(this);  // 调 赛格哈特·子类扩展字段复位
  sub_5B2720(this);  // 调 赛格哈特·受伤/死亡语音装载
  return this;
}



// ------------------------------------------------------------
// 0x4A93F0 sub_4A93F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLordofLightBase 析构（sub_5B1940）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A93F0(uint32_t *this)  // 实现：(推断)CNLordofLightBase 析构（sub_5B1940）
{
  *this = &CNLordofLightBase::`vftable';  // vftable 复位
  sub_5B1940();  // 调 赛格哈特·附属对象双槽释放
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A9440 sub_4A9440 —— CNLordofLightBase（光之领主基）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A93F0，含 ·0x5B1940 专属清理）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9440(uint32_t *Block, char pszArg2)  // 函数: CNLordofLightBase（光之领主基）删除析构壳
{
  sub_4A93F0(Block);  // 调 (推断)CNLordofLightBase 析构（sub_5B1940）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9470 sub_4A9470
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLordofLight 构造（sub_5B3100）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9470(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLordofLight 构造（sub_5B3100）
{
  sub_4A9390(this, ArgList, nArg3);  // 调 (推断) CNLordofLightBase（光之领主基）构造（sub_5B1910/5B2720）
  *(uint32_t *)this = &CNLordofLight::`vftable';  // vftable 复位
  sub_5B3100(this);  // 调 赛格哈特·外观三件套装载（Armor/Glow/Wing）
  return this;
}



// ------------------------------------------------------------
// 0x4A94D0 sub_4A94D0 —— CNLordofLight 删除析构壳
// 与 ·0x4A53E0 同构（差异：转发本文件内 ·0x4A9500 CNLordofLight 析构体）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A94D0(void *Block, char pszArg2)  // 函数: CNLordofLight 删除析构壳
{
  sub_4A9500();  // 调 CNLordofLight 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9500 sub_4A9500 —— CNLordofLight 析构体
// 与 ·0x4A7CF0 同构（差异：尾调 ·0x4A93F0 CNLordofLightBase 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9500(uint32_t *this)  // 函数: CNLordofLight 析构体
{
  *this = &CNLordofLight::`vftable';  // vftable 复位
  return sub_4A93F0(this);  // 返回 (推断)CNLordofLightBase 析构（sub_5B1940）
}



// ------------------------------------------------------------
// 0x4A9510 sub_4A9510
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9510(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNSpaceFishHead::`vftable';  // vftable 复位
  sub_5B3230(this);  // 调 空骨鱼·子类字段复位
  sub_5B3F30(this);  // 调 空骨鱼语音四件套 + 时间戳（this+8608）
  return this;
}



// ------------------------------------------------------------
// 0x4A9570 sub_4A9570
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpaceFishHead 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9570(uint32_t *this)  // 实现：(推断)CNSpaceFishHead 析构
{
  *this = &CNSpaceFishHead::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A95C0 sub_4A95C0 —— CNSpaceFishHead（空骨鱼）删除析构壳
// 与 ·0x4A53E0 同构（差异：析构体 ·0x4A9570，含 nullsub_3 与 IRDMonster 收尾 ·0x4A50F0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A95C0(uint32_t *Block, char pszArg2)  // 函数: CNSpaceFishHead（空骨鱼）删除析构壳
{
  sub_4A9570(Block);  // 调 (推断)CNSpaceFishHead 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A95F0 sub_4A95F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishShort 构造（sub_5B3400）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A95F0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpaceFishShort 构造（sub_5B3400）
{
  sub_4A9510(this, ArgList, nArg3);  // 调 (推断) CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）
  *(uint32_t *)this = &CNSpaceFishShort::`vftable';  // vftable 复位
  sub_5B3400(this);  // 调 空骨鱼·技能变体甲装填
  return this;
}



// ------------------------------------------------------------
// 0x4A9650 sub_4A9650 —— CNSpaceFishShort 删除析构壳
// 与 ·0x4A53E0 同构（标量删除析构形；析构体 ·0x4A9680）。
// 空骨鱼族 Short/Long/Crocuta 三变体均直承 ·0x4A9510 CNSpaceFishHead 构造。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9650(void *Block, char pszArg2)  // 函数: CNSpaceFishShort 删除析构壳
{
  sub_4A9680();  // 调 CNSpaceFishShort 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9680 sub_4A9680 —— CNSpaceFishShort 析构
// vftable 复位 + 转发 ·0x4A9570（CNSpaceFishHead 析构；含 nullsub_3 与 ·0x4A50F0 IRDMonster 收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9680(uint32_t *this)  // 函数: CNSpaceFishShort 析构
{
  *this = &CNSpaceFishShort::`vftable';  // vftable 复位
  return sub_4A9570(this);  // 返回 (推断)CNSpaceFishHead 析构
}



// ------------------------------------------------------------
// 0x4A9690 sub_4A9690
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishLong 构造（sub_5B34D0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9690(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpaceFishLong 构造（sub_5B34D0）
{
  sub_4A9510(this, ArgList, nArg3);  // 调 (推断) CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）
  *(uint32_t *)this = &CNSpaceFishLong::`vftable';  // vftable 复位
  sub_5B34D0(this);  // 调 空骨鱼·技能变体乙装填与属性注册
  return this;
}



// ------------------------------------------------------------
// 0x4A96F0 sub_4A96F0 —— CNSpaceFishLong 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9720）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A96F0(void *Block, char pszArg2)  // 函数: CNSpaceFishLong 删除析构壳
{
  sub_4A9720();  // 调 CNSpaceFishLong 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9720 sub_4A9720 —— CNSpaceFishLong 析构
// vftable 复位 + 转发 ·0x4A9570（CNSpaceFishHead 析构链）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9720(uint32_t *this)  // 函数: CNSpaceFishLong 析构
{
  *this = &CNSpaceFishLong::`vftable';  // vftable 复位
  return sub_4A9570(this);  // 返回 (推断)CNSpaceFishHead 析构
}



// ------------------------------------------------------------
// 0x4A9730 sub_4A9730
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishCrocuta 构造（sub_5B35C0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9730(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpaceFishCrocuta 构造（sub_5B35C0）
{
  sub_4A9510(this, ArgList, nArg3);  // 调 (推断) CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）
  *(uint32_t *)this = &CNSpaceFishCrocuta::`vftable';  // vftable 复位
  sub_5B35C0(this);  // 调 空骨鱼·技能变体丙（出场参数插值装填）
  return this;
}



// ------------------------------------------------------------
// 0x4A9790 sub_4A9790 —— CNSpaceFishCrocuta 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A97C0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9790(void *Block, char pszArg2)  // 函数: CNSpaceFishCrocuta 删除析构壳
{
  sub_4A97C0();  // 调 CNSpaceFishCrocuta 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A97C0 sub_4A97C0 —— CNSpaceFishCrocuta 析构
// vftable 复位 + 转发 ·0x4A9570（CNSpaceFishHead 析构链）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A97C0(uint32_t *this)  // 函数: CNSpaceFishCrocuta 析构
{
  *this = &CNSpaceFishCrocuta::`vftable';  // vftable 复位
  return sub_4A9570(this);  // 返回 (推断)CNSpaceFishHead 析构
}



// ------------------------------------------------------------
// 0x4A97D0 sub_4A97D0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFish（海星）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A97D0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNStarFish（海星）构造
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNStarFishFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNStarFish::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNStarFish::`vftable';  // vftable 复位
  sub_5B4700(this);  // 调 子类扩展清零（含 6792..6808 计数槽）
  sub_5B6630(this);  // 调 ZGM 死亡插值（ZGM_DIE 语音 + this+8620 槽）
  return this;
}



// ------------------------------------------------------------
// 0x4A9850 sub_4A9850
// ------------------------------------------------------------
// 【解读】
//   【推断】CNStarFish 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9850(uint32_t *this)  // 实现：(推断)CNStarFish 析构
{
  *this = &CNStarFish::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFish::`vftable';  // this+8600 = uAI8600
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A98C0 sub_4A98C0 —— CNStarFish 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9850，+2150 副槽以 CNMonsterFriendShip 收尾）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A98C0(uint32_t *Block, char pszArg2)  // 函数: CNStarFish 删除析构壳
{
  sub_4A9850(Block);  // 调 (推断)CNStarFish 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A98F0 sub_4A98F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishRukuku 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A98F0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStarFishRukuku 构造
{
  sub_4A97D0((int)this, ArgList, nArg3);  // 调 CNStarFish 构造，结果存 result
  *this = &CNStarFishRukuku::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishRukuku::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9920 sub_4A9920 —— CNStarFishRukuku 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9950）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9920(void *Block, char pszArg2)  // 函数: CNStarFishRukuku 删除析构壳
{
  sub_4A9950();  // 调 CNStarFishRukuku 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9950 sub_4A9950 —— CNStarFishRukuku 析构
// 主/副双 vftable 复位 → ·0x4A9850（CNStarFish 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9950(uint32_t *this)  // 函数: CNStarFishRukuku 析构
{
  *this = &CNStarFishRukuku::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishRukuku::`vftable';  // this+8600 = uAI8600
  return sub_4A9850(this);  // 返回 (推断)CNStarFish 析构
}



// ------------------------------------------------------------
// 0x4A9970 sub_4A9970
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishDevourer 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9970(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStarFishDevourer 构造
{
  sub_4A97D0((int)this, ArgList, nArg3);  // 调 CNStarFish 构造，结果存 result
  *this = &CNStarFishDevourer::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishDevourer::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A99A0 sub_4A99A0 —— CNStarFishDevourer 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A99D0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A99A0(void *Block, char pszArg2)  // 函数: CNStarFishDevourer 删除析构壳
{
  sub_4A99D0();  // 调 CNStarFishDevourer 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A99D0 sub_4A99D0 —— CNStarFishDevourer 析构
// 主/副双 vftable 复位 → ·0x4A9850（CNStarFish 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A99D0(uint32_t *this)  // 函数: CNStarFishDevourer 析构
{
  *this = &CNStarFishDevourer::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishDevourer::`vftable';  // this+8600 = uAI8600
  return sub_4A9850(this);  // 返回 (推断)CNStarFish 析构
}



// ------------------------------------------------------------
// 0x4A99F0 sub_4A99F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishKing 构造（+8664 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A99F0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStarFishKing 构造（+8664 标志）
{
  sub_4A97D0((int)this, ArgList, nArg3);  // 调 CNStarFish 构造，结果存 result
  *this = &CNStarFishKing::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishKing::`vftable';  // this+8600 = uAI8600
  *((uint8_t *)this + 8664) = 0;  // this+8664 = 子类 AI 槽
  *(this + 2167) = 0;  // this+8668 = nCool8668
  *((uint8_t *)this + 8674) = 0;  // this+8674〔bAI8674〕
  *((uint8_t *)this + 8673) = 0;  // this+8673〔bAI8673〕
  *(this + 2171) = 0;  // this+8684〔bGate8684(推断)〕
  *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
  *(this + 2169) = 0;  // this+8676〔uAI8676(推断)〕
  *(this + 2165) = &off_6C2B88;  // this+8660 = uEvt8660
  *((uint8_t *)this + 8672) = 1;  // this+8672 = 子类 AI 槽
  return this;
}



// ------------------------------------------------------------
// 0x4A9A60 sub_4A9A60 —— CNStarFishKing 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9A90，IObject @+8660 复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9A60(void *Block, char pszArg2)  // 函数: CNStarFishKing 删除析构壳
{
  sub_4A9A90();  // 调 (推断)CNStarFishKing 析构（IObject @+8660）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9A90 sub_4A9A90
// ------------------------------------------------------------
// 【解读】
//   【推断】CNStarFishKing 析构（IObject @+8660）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9A90(uint32_t *this)  // 实现：(推断)CNStarFishKing 析构（IObject @+8660）
{
  *this = &CNStarFishKing::`vftable';  // vftable 复位
  *(this + 2150) = &CNStarFishKing::`vftable';  // this+8600 = uAI8600
  *(this + 2165) = &nengine::IObject::`vftable';  // this+8660 = uEvt8660
  *((uint8_t *)this + 8664) = 0;  // this+8664 = 子类 AI 槽
  return sub_4A9850(this);  // 返回 (推断)CNStarFish 析构
}



// ------------------------------------------------------------
// 0x4A9AC0 sub_4A9AC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9AC0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)(this + 8600) = &CNZealotFriendShip::`vftable';  // vftable 复位
  *(uint32_t *)this = &CNZealot::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8600) = &CNZealot::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8608) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint8_t *)(this + 8620) = 1;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8622) = 0;  // this+8622〔bLoopLatch8622〕
  *(uint8_t *)(this + 8621) = 0;
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  sub_5B73B0(this);  // 调 ZGM 扩展复位（8604..8660）
  sub_5B8C40(this);  // 调 信徒初始化（语音组装载 + 技能参数）
  return this;
}



// ------------------------------------------------------------
// 0x4A9B70 sub_4A9B70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZealot 析构（IObject @+8608，2152*4=8608）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9B70(uint32_t *this)  // 实现：(推断)CNZealot 析构（IObject @+8608，2152*4=8608）
{
  *this = &CNZealot::`vftable';  // vftable 复位
  *(this + 2150) = &CNZealot::`vftable';  // this+8600 = uAI8600
  nullsub_3(this);
  *(this + 2152) = &nengine::IObject::`vftable';  // this+8608 = uAI8608
  *((uint8_t *)this + 8612) = 0;  // this+8612 = uAI8612
  *(this + 2150) = &CNMonsterFriendShip::`vftable';  // this+8600 = uAI8600
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4A9BF0 sub_4A9BF0 —— CNZealot 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9B70）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9BF0(uint32_t *Block, char pszArg2)  // 函数: CNZealot 删除析构壳
{
  sub_4A9B70(Block);  // 调 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9C20 sub_4A9C20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRaxy_A 构造（+8600 → off_6E7860 特殊 vftable）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C20(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRaxy_A 构造（+8600 → off_6E7860 特殊 vftable）
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNRaxy_A::`vftable';  // vftable 复位
  *(this + 2150) = &off_6E7860;  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9C50 sub_4A9C50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRaxy_B 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C50(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRaxy_B 构造
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNRaxy_B::`vftable';  // vftable 复位
  *(this + 2150) = &CNRaxy_B::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9C80 sub_4A9C80 —— CNRaxy_B 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9CB0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9C80(void *Block, char pszArg2)  // 函数: CNRaxy_B 删除析构壳
{
  sub_4A9CB0();  // 调 CNRaxy_B 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9CB0 sub_4A9CB0 —— CNRaxy_B 析构
// 主/副双 vftable 复位 → ·0x4A9B70（CNZealot 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9CB0(uint32_t *this)  // 函数: CNRaxy_B 析构
{
  *this = &CNRaxy_B::`vftable';  // vftable 复位
  *(this + 2150) = &CNRaxy_B::`vftable';  // this+8600 = uAI8600
  return sub_4A9B70(this);  // 返回 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
}



// ------------------------------------------------------------
// 0x4A9CD0 sub_4A9CD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCraxy 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9CD0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNCraxy 构造
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNCraxy::`vftable';  // vftable 复位
  *(this + 2150) = &CNCraxy::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9D00 sub_4A9D00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFather（教父）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9D00(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNFather（教父）构造
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNFather::`vftable';  // vftable 复位
  *(this + 2150) = &CNFather::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9D30 sub_4A9D30 —— CNFather 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9D60）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9D30(void *Block, char pszArg2)  // 函数: CNFather 删除析构壳
{
  sub_4A9D60();  // 调 CNFather 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9D60 sub_4A9D60 —— CNFather 析构
// 主/副双 vftable 复位 → ·0x4A9B70（CNZealot 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9D60(uint32_t *this)  // 函数: CNFather 析构
{
  *this = &CNFather::`vftable';  // vftable 复位
  *(this + 2150) = &CNFather::`vftable';  // this+8600 = uAI8600
  return sub_4A9B70(this);  // 返回 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
}



// ------------------------------------------------------------
// 0x4A9D80 sub_4A9D80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPope（教皇）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9D80(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNPope（教皇）构造
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNPope::`vftable';  // vftable 复位
  *(this + 2150) = &CNPope::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9DB0 sub_4A9DB0 —— CNPope 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9DE0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9DB0(void *Block, char pszArg2)  // 函数: CNPope 删除析构壳
{
  sub_4A9DE0();  // 调 CNPope 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9DE0 sub_4A9DE0 —— CNPope 析构
// 主/副双 vftable 复位 → ·0x4A9B70（CNZealot 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9DE0(uint32_t *this)  // 函数: CNPope 析构
{
  *this = &CNPope::`vftable';  // vftable 复位
  *(this + 2150) = &CNPope::`vftable';  // this+8600 = uAI8600
  return sub_4A9B70(this);  // 返回 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
}



// ------------------------------------------------------------
// 0x4A9E00 sub_4A9E00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfDawn（黎明传道者）构造（+8672 = 30041 技能/动作 ID）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E00(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNEvangelistOfDawn（黎明传道者）构造（+8672 = 30041 技能/动作 ID）
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNEvangelistOfDawn::`vftable';  // vftable 复位
  *(this + 2150) = &CNEvangelistOfDawn::`vftable';  // this+8600 = uAI8600
  *(this + 2168) = 30041;  // this+8672 = 子类 AI 槽
  return this;
}



// ------------------------------------------------------------
// 0x4A9E50 sub_4A9E50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfLight（光之传道者）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E50(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNEvangelistOfLight（光之传道者）构造
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNEvangelistOfLight::`vftable';  // vftable 复位
  *(this + 2150) = &CNEvangelistOfLight::`vftable';  // this+8600 = uAI8600
  return this;
}



// ------------------------------------------------------------
// 0x4A9E80 sub_4A9E80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfTwilight（暮光传道者）构造（+8676 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E80(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNEvangelistOfTwilight（暮光传道者）构造（+8676 标志）
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNEvangelistOfTwilight::`vftable';  // vftable 复位
  *(this + 2150) = &CNEvangelistOfTwilight::`vftable';  // this+8600 = uAI8600
  *(this + 2169) = 0;  // this+8676〔uAI8676(推断)〕
  return this;
}



// ------------------------------------------------------------
// 0x4A9EC0 sub_4A9EC0 —— CNRaxy_A 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9EF0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9EC0(void *Block, char pszArg2)  // 函数: CNRaxy_A 删除析构壳
{
  sub_4A9EF0();  // 调 CNRaxy_A 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9EF0 sub_4A9EF0 —— CNRaxy_A 析构
// 主 vftable + 副槽 off_6E7860（RTTI 表记 CNRaxy_A 副 vt）复位 → ·0x4A9B70（CNZealot 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9EF0(uint32_t *this)  // 函数: CNRaxy_A 析构
{
  *this = &CNRaxy_A::`vftable';  // vftable 复位
  *(this + 2150) = &off_6E7860;  // this+8600 = uAI8600
  return sub_4A9B70(this);  // 返回 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
}



// ------------------------------------------------------------
// 0x4A9F10 sub_4A9F10
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfDark（暗之传道者）构造（+8672 = 30042）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9F10(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNEvangelistOfDark（暗之传道者）构造（+8672 = 30042）
{
  sub_4A9AC0((int)this, ArgList, nArg3);  // 调 (推断) CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基
  *this = &CNEvangelistOfDark::`vftable';  // vftable 复位
  *(this + 2150) = &CNEvangelistOfDark::`vftable';  // this+8600 = uAI8600
  *(this + 2168) = 30042;  // this+8672 = 子类 AI 槽
  return this;
}



// ------------------------------------------------------------
// 0x4A9F50 sub_4A9F50 —— CNCraxy 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4A9F80）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9F50(void *Block, char pszArg2)  // 函数: CNCraxy 删除析构壳
{
  sub_4A9F80();  // 调 CNCraxy 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4A9F80 sub_4A9F80 —— CNCraxy 析构
// 主/副双 vftable 复位 → ·0x4A9B70（CNZealot 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9F80(uint32_t *this)  // 函数: CNCraxy 析构
{
  *this = &CNCraxy::`vftable';  // vftable 复位
  *(this + 2150) = &CNCraxy::`vftable';  // this+8600 = uAI8600
  return sub_4A9B70(this);  // 返回 (推断)CNZealot 析构（IObject @+8608，2152*4=8608）
}



// ------------------------------------------------------------
// 0x4A9FA0 sub_4A9FA0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNVehicle（载具基）构造（sub_5BA050/5BAC30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9FA0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNVehicle（载具基）构造（sub_5BA050/5BAC30）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNVehicle::`vftable';  // vftable 复位
  sub_5BA050(this);  // 调 子类扩展字段复位（this+8600 指针 + 8604/8605 状态字节 + 6792..6808）
  sub_5BAC30(this);  // 调 载具破坏音效（DRGCANNON_BREAK）
  return this;
}



// ------------------------------------------------------------
// 0x4AA000 sub_4AA000
// ------------------------------------------------------------
// 【解读】
//   【推断】CNVehicle 析构（sub_5BA090）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA000(uint32_t *this)  // 实现：(推断)CNVehicle 析构（sub_5BA090）
{
  *this = &CNVehicle::`vftable';  // vftable 复位
  sub_5BA090();  // 调 资源对象释放（this+8600 经 vtable[0](obj,1)）并清槽
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AA050 sub_4AA050 —— CNVehicle 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA000）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA050(uint32_t *Block, char pszArg2)  // 函数: CNVehicle 删除析构壳
{
  sub_4AA000(Block);  // 调 (推断)CNVehicle 析构（sub_5BA090）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA080 sub_4AA080
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCatapult（投石车）构造（sub_5BAD00）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA080(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNCatapult（投石车）构造（sub_5BAD00）
{
  sub_4A9FA0(this, ArgList, nArg3);  // 调 (推断) CNVehicle（载具基）构造（sub_5BA050/5BAC30）
  *(uint32_t *)this = &CNCatapult::`vftable';  // vftable 复位
  sub_5BAD00(this);  // 调 载具·破坏粒子族装载（4 槽 + 出场参数）
  return this;
}



// ------------------------------------------------------------
// 0x4AA0E0 sub_4AA0E0 —— CNCatapult 析构
// vftable 复位 → ·0x4AA000（CNVehicle 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA0E0(uint32_t *this)  // 函数: CNCatapult 析构
{
  *this = &CNCatapult::`vftable';  // vftable 复位
  return sub_4AA000(this);  // 返回 (推断)CNVehicle 析构（sub_5BA090）
}



// ------------------------------------------------------------
// 0x4AA0F0 sub_4AA0F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLaserCatapult（激光投石车）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA0F0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLaserCatapult（激光投石车）构造
{
  sub_4AA080(this, ArgList, nArg3);  // 调 CNCatapult 构造并把指针直接返回
  *(uint32_t *)this = &CNLaserCatapult::`vftable';  // vftable 复位
  sub_5BAD00(this);  // 调 载具·破坏粒子族装载（4 槽 + 出场参数）
  return this;
}



// ------------------------------------------------------------
// 0x4AA150 sub_4AA150
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFlameCatapult（火焰投石车）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA150(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNFlameCatapult（火焰投石车）构造
{
  sub_4AA080(this, ArgList, nArg3);  // 调 CNCatapult 构造并把指针直接返回
  *(uint32_t *)this = &CNFlameCatapult::`vftable';  // vftable 复位
  sub_5BAD00(this);  // 调 载具·破坏粒子族装载（4 槽 + 出场参数）
  return this;
}



// ------------------------------------------------------------
// 0x4AA1B0 sub_4AA1B0 —— CNCatapult 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA0E0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA1B0(uint32_t *Block, char pszArg2)  // 函数: CNCatapult 删除析构壳
{
  sub_4AA0E0(Block);  // 调 CNCatapult 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA1E0 sub_4AA1E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBattlIngram（战斗英格拉姆/机甲）构造（sub_5BAEF0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA1E0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNBattlIngram（战斗英格拉姆/机甲）构造（sub_5BAEF0）
{
  sub_4A9FA0(this, ArgList, nArg3);  // 调 (推断) CNVehicle（载具基）构造（sub_5BA050/5BAC30）
  *(uint32_t *)this = &CNBattlIngram::`vftable';  // vftable 复位
  sub_5BAEF0(this);  // 调 载具·坠落破坏粒子装载（BATIDestroy）
  return this;
}



// ------------------------------------------------------------
// 0x4AA240 sub_4AA240 —— CNBattlIngram 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA270）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA240(void *Block, char pszArg2)  // 函数: CNBattlIngram 删除析构壳
{
  sub_4AA270();  // 调 CNBattlIngram 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA270 sub_4AA270 —— CNBattlIngram 析构
// vftable 复位 → ·0x4AA000（CNVehicle 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA270(uint32_t *this)  // 函数: CNBattlIngram 析构
{
  *this = &CNBattlIngram::`vftable';  // vftable 复位
  return sub_4AA000(this);  // 返回 (推断)CNVehicle 析构（sub_5BA090）
}



// ------------------------------------------------------------
// 0x4AA280 sub_4AA280
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZepplin（飞艇）构造 —— 含 2 元素×0x1C(28) 字节内嵌数组（eh vector ctor）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA280(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNZepplin（飞艇）构造 —— 含 2 元素×0x1C(28) 字节内嵌数组（eh vector ctor）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNZepplin::`vftable';  // vftable 复位
  `eh vector constructor iterator'(this + 8616, 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  nullsub_3(this);
  sub_5BB420(this);  // 调 载具/飞艇·高度起点受理（vt+1308 覆写）
  return this;
}



// ------------------------------------------------------------
// 0x4AA300 sub_4AA300
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZepplin 析构（2×28B eh vector dtor @+8616）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA300(uint32_t *this)  // 实现：(推断)CNZepplin 析构（2×28B eh vector dtor @+8616）
{
  *this = &CNZepplin::`vftable';  // vftable 复位
  nullsub_3(this);
  `eh vector destructor iterator'(this + 2154, 0x1Cu, 2, sub_501490);  // 调 对象析构后释放堆块
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AA370 sub_4AA370 —— CNZepplin 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA300，含 2×28B 内嵌数组析构）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA370(uint32_t *Block, char pszArg2)  // 函数: CNZepplin 删除析构壳
{
  sub_4AA300(Block);  // 调 (推断)CNZepplin 析构（2×28B eh vector dtor @+8616）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA3A0 sub_4AA3A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCannonZepplin（炮艇）构造（sub_599D80）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA3A0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNCannonZepplin（炮艇）构造（sub_599D80）
{
  sub_4AA280(this, ArgList, nArg3);  // 调 (推断) CNZepplin（飞艇）构造 —— 含 2 元素×0x1C(28) 字节内嵌数组（eh vector ctor）
  *(uint32_t *)this = &CNCannonZepplin::`vftable';  // vftable 复位
  sub_599D80(this);  // 调 虚表转发垫片：调用 vt+1308 并原样返回其结果
  return this;
}



// ------------------------------------------------------------
// 0x4AA400 sub_4AA400 —— CNCannonZepplin 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA430）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA400(void *Block, char pszArg2)  // 函数: CNCannonZepplin 删除析构壳
{
  sub_4AA430();  // 调 CNCannonZepplin 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA430 sub_4AA430 —— CNCannonZepplin 析构
// vftable 复位 → ·0x4AA300（CNZepplin 析构，含内嵌数组析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA430(uint32_t *this)  // 函数: CNCannonZepplin 析构
{
  *this = &CNCannonZepplin::`vftable';  // vftable 复位
  return sub_4AA300(this);  // 返回 (推断)CNZepplin 析构（2×28B eh vector dtor @+8616）
}



// ------------------------------------------------------------
// 0x4AA440 sub_4AA440
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNNormalZepplin（普通飞艇）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA440(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNNormalZepplin（普通飞艇）构造
{
  sub_4AA280(this, ArgList, nArg3);  // 调 (推断) CNZepplin（飞艇）构造 —— 含 2 元素×0x1C(28) 字节内嵌数组（eh vector ctor）
  *(uint32_t *)this = &CNNormalZepplin::`vftable';  // vftable 复位
  sub_599D80(this);  // 调 虚表转发垫片：调用 vt+1308 并原样返回其结果
  return this;
}



// ------------------------------------------------------------
// 0x4AA4A0 sub_4AA4A0 —— CNNormalZepplin 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA4D0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA4A0(void *Block, char pszArg2)  // 函数: CNNormalZepplin 删除析构壳
{
  sub_4AA4D0();  // 调 CNNormalZepplin 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA4D0 sub_4AA4D0 —— CNNormalZepplin 析构
// vftable 复位 → ·0x4AA300（CNZepplin 析构，含内嵌数组析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA4D0(uint32_t *this)  // 函数: CNNormalZepplin 析构
{
  *this = &CNNormalZepplin::`vftable';  // vftable 复位
  return sub_4AA300(this);  // 返回 (推断)CNZepplin 析构（2×28B eh vector dtor @+8616）
}



// ------------------------------------------------------------
// 0x4AA4E0 sub_4AA4E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWraith（怨灵）构造（+8624=15/+8620 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA4E0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNWraith（怨灵）构造（+8624=15/+8620 string）
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNWraith::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8624) = 15;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  sub_5BD1B0(this);  // 调 幽灵·语音/死亡特效资源装载与相位复位
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA560 sub_4AA560
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWraith 析构（string @+8624 区）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA560(void **this)  // 实现：(推断)CNWraith 析构（string @+8624 区）
{
  *this = &CNWraith::`vftable';  // vftable 复位
  nullsub_3(this);
  if ( (unsigned int)*(this + 2156) >= 0x10 )  // this+8624 = uAI8624
    j__free(*(this + 2151));  // this+8604 = bAI8604
  *(this + 2156) = (void *)15;  // this+8624 = uAI8624
  *(this + 2155) = nullptr;  // this+8620 = uAI8620
  *((uint8_t *)this + 8604) = 0;  // this+8604 = bAI8604
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AA5E0 sub_4AA5E0 —— CNWraith 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA560，含 std::string 缓冲释放）。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4AA5E0(void **Block, char pszArg2)  // 函数: CNWraith 删除析构壳
{
  sub_4AA560(Block);  // 调 (推断)CNWraith 析构（string @+8624 区）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA610 sub_4AA610
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWraithSpectress（女怨灵）构造（+8656/+8660 双槽）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA610(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNWraithSpectress（女怨灵）构造（+8656/+8660 双槽）
{
  sub_4AA4E0((int)this, ArgList, nArg3);  // 调 CNWraith 构造，结果存 result
  *this = &CNWraithSpectress::`vftable';  // vftable 复位
  *(this + 2164) = 0;  // this+8656 = 事件 16/17 配对槽
  *(this + 2165) = 0;  // this+8660 = uEvt8660
  *(this + 2166) = 0;  // this+8664 = 子类 AI 槽
  *((uint8_t *)this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  *(this + 2168) = &off_6C2B88;  // this+8672 = 子类 AI 槽
  *(this + 2170) = 0;  // this+8680〔uGate8680(推断)〕
  *((uint8_t *)this + 8684) = 1;  // this+8684〔bGate8684(推断)〕
  *((uint8_t *)this + 8686) = 0;
  *((uint8_t *)this + 8685) = 0;  // this+8685〔bGate8685(推断)〕
  *(this + 2174) = 0;  // this+8696〔uVec8696(推断)〕
  *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
  *(this + 2172) = 0;  // this+8688〔bVec8688(推断)〕
  sub_5BD270(this);  // 调 鬼魂·死亡特效装载（Die.ani + 相位置 1）
  sub_5BDF80(this);  // 调 爱心特效装载（KissHeart.ptl 挂 this+2167）
  return this;
}



// ------------------------------------------------------------
// 0x4AA6C0 sub_4AA6C0 —— CNWraithSpectress 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA6F0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA6C0(void *Block, char pszArg2)  // 函数: CNWraithSpectress 删除析构壳
{
  sub_4AA6F0();  // 调 (推断)CNWraithSpectress 析构（sub_5BCFC0 + IObject @+8672）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA6F0 sub_4AA6F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWraithSpectress 析构（sub_5BCFC0 + IObject @+8672）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA6F0(int this)  // 实现：(推断)CNWraithSpectress 析构（sub_5BCFC0 + IObject @+8672）
{
  *(uint32_t *)this = &CNWraithSpectress::`vftable';  // vftable 复位
  sub_5BCFC0();  // 调 飞艇·破坏粒子对象释放（this+8668 槽）
  *(uint32_t *)(this + 8672) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  if ( *(uint32_t *)(this + 8656) != 0 )  // this+8656〔uPair8656(推断)〕
    j__free(*(void **)(this + 8656));  // 调 堆释放
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint32_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8664) = 0;  // this+8664〔uAI8664(推断)〕
  return sub_4AA560((void **)this);  // 返回 (推断)CNWraith 析构（string @+8624 区）
}



// ------------------------------------------------------------
// 0x4AA780 sub_4AA780
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA780(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNSpider::`vftable';  // vftable 复位
  sub_5BEC80(this);  // 调 蜘蛛·吐丝相位复位（this+8600 清 0、this+8608 置 -1）
  sub_5BECA0(this);  // 调 蜘蛛·动作号/相位预置（返回 3 帧段阈值）
  return this;
}



// ------------------------------------------------------------
// 0x4AA7F0 sub_4AA7F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRollingSpider（滚动蜘蛛）构造（+8628 标志 / +8624 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA7F0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNRollingSpider（滚动蜘蛛）构造（+8628 标志 / +8624 IObject）
{
  sub_4AA780((char *)this, ArgList, nArg3);  // 调 (推断) CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基
  *(uint32_t *)this = &CNRollingSpider::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8624) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8636) = 1;  // this+8636〔pDollTarget(推断)〕
  *(uint8_t *)(this + 8638) = 0;  // this+8638〔bRes8638〕
  *(uint8_t *)(this + 8637) = 0;  // this+8637〔bSwingGate8637〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  sub_5C0390(this);  // 调 蜘蛛本体语音装载（R_SPIDER_ATK/DMG + SPIDER_DIE）
  return this;
}



// ------------------------------------------------------------
// 0x4AA890 sub_4AA890 —— CNRollingSpider 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA8C0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA890(void *Block, char pszArg2)  // 函数: CNRollingSpider 删除析构壳
{
  sub_4AA8C0();  // 调 (推断)CNRollingSpider/CNSpider 析构（IObject @+8624 复位）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA8C0 sub_4AA8C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRollingSpider/CNSpider 析构（IObject @+8624 复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA8C0(int this)  // 实现：(推断)CNRollingSpider/CNSpider 析构（IObject @+8624 复位）
{
  *(uint32_t *)(this + 8624) = &nengine::IObject::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)this = &CNSpider::`vftable';  // vftable 复位
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AA8E0 sub_4AA8E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPoisonSpider（毒蜘蛛）构造（sub_5C0400）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA8E0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNPoisonSpider（毒蜘蛛）构造（sub_5C0400）
{
  sub_4AA780(this, ArgList, nArg3);  // 调 (推断) CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基
  *(uint32_t *)this = &CNPoisonSpider::`vftable';  // vftable 复位
  sub_5C0400(this);  // 调 毒蜘蛛（PSPIDER）出场参数与语音装配
  return this;
}



// ------------------------------------------------------------
// 0x4AA940 sub_4AA940 —— CNSpider 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AA7E0，见 missing_misc_a.cpp）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA940(void *Block, char pszArg2)  // 函数: CNSpider 删除析构壳
{
  sub_4AA7E0();
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AA970 sub_4AA970
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAraclothoSpider（阿拉克洛蜘蛛）构造（+8664 标志 / +8660 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA970(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNAraclothoSpider（阿拉克洛蜘蛛）构造（+8664 标志 / +8660 IObject）
{
  sub_4AA780((char *)this, ArgList, nArg3);  // 调 (推断) CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基
  *(uint32_t *)this = &CNAraclothoSpider::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8664) = 0;  // this+8664〔uAI8664(推断)〕
  *(uint32_t *)(this + 8660) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  *(uint8_t *)(this + 8672) = 1;  // this+8672〔uAI8672(推断)〕
  *(uint8_t *)(this + 8674) = 0;  // this+8674〔bAI8674〕
  *(uint8_t *)(this + 8673) = 0;  // this+8673〔bAI8673〕
  *(uint32_t *)(this + 8684) = 0;  // this+8684〔bGate8684(推断)〕
  *(uint32_t *)(this + 8680) = 0;  // this+8680〔uGate8680(推断)〕
  *(uint32_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  *(uint8_t *)(this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(uint32_t *)(this + 8688) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  *(uint8_t *)(this + 8700) = 1;  // this+8700〔uPhase8700(推断)〕
  *(uint8_t *)(this + 8702) = 0;
  *(uint8_t *)(this + 8701) = 0;
  *(uint32_t *)(this + 8712) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  *(uint32_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(uint32_t *)(this + 8704) = 0;  // this+8704〔pSegNameTbl8704(推断)〕
  *(uint8_t *)(this + 8720) = 0;  // this+8720〔pSegThrTbl8720〕
  *(uint32_t *)(this + 8716) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8724) = 0;  // this+8724〔nSegThrEnd8724〕
  *(uint8_t *)(this + 8728) = 1;  // this+8728〔nSegThrCap8728〕
  *(uint8_t *)(this + 8730) = 0;
  *(uint8_t *)(this + 8729) = 0;
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8736) = 0;
  *(uint32_t *)(this + 8732) = 0;  // this+8732〔bSegLatch8732〕
  sub_5C0490(this);  // 调 黑蜘蛛（KSPIDER）语音装载与大相位区清零
  sub_5C11B0(this);  // 调 蜘蛛王·三向吐酸资源装载（吐丝序列 30100 前置）
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAA80 sub_4AAA80 —— CNAraclothoSpider 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AAAB0，3 处 IObject 副槽复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAA80(void *Block, char pszArg2)  // 函数: CNAraclothoSpider 删除析构壳
{
  sub_4AAAB0();  // 调 (推断)CNAraclothoSpider 析构（sub_5C1270 + IObject @+8716）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AAAB0 sub_4AAAB0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAraclothoSpider 析构（sub_5C1270 + IObject @+8716）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAAB0(uint32_t *this)  // 实现：(推断)CNAraclothoSpider 析构（sub_5C1270 + IObject @+8716）
{
  *this = &CNAraclothoSpider::`vftable';  // vftable 复位
  sub_5C1270();  // 调 蜘蛛王·Thread.ani 三句柄槽释放（与 ·0x5C11B0 成对）
  *(this + 2179) = &nengine::IObject::`vftable';  // vftable 复位
  *((uint8_t *)this + 8720) = 0;  // this+8720〔pSegThrTbl8720〕
  *(this + 2172) = &nengine::IObject::`vftable';  // vftable 复位
  *((uint8_t *)this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(this + 2165) = &nengine::IObject::`vftable';  // this+8660 = uEvt8660
  *((uint8_t *)this + 8664) = 0;  // this+8664 = 子类 AI 槽
  *this = &CNSpider::`vftable';  // vftable 复位
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AAB30 sub_4AAB30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotRX78（机器人 RX-78）构造（sub_5C1FC0）—— 机甲族。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAB30(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRobotRX78（机器人 RX-78）构造（sub_5C1FC0）—— 机甲族
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNRobotRX78::`vftable';  // vftable 复位
  sub_5C1FC0(this);  // 调 机器人·子类扩展字段复位（this+8600..8616，出怪初始化）
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAB90 sub_4AAB90 —— CNRobotRX78 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AABC0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAB90(void *Block, char pszArg2)  // 函数: CNRobotRX78 删除析构壳
{
  sub_4AABC0();  // 调 (推断)CNRobotRX78 析构（sub_5C1FF0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AABC0 sub_4AABC0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotRX78 析构（sub_5C1FF0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AABC0(uint32_t *this)  // 实现：(推断)CNRobotRX78 析构（sub_5C1FF0）
{
  *this = &CNRobotRX78::`vftable';  // vftable 复位
  sub_5C1FF0();  // 调 机器人·挂载对象释放（this+8608 槽，与 ·0x5C28A0/·0x5C3170 同构）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AAC10 sub_4AAC10
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotEz8 构造（sub_5C2830/5C2870）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAC10(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRobotEz8 构造（sub_5C2830/5C2870）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNRobotEz8::`vftable';  // vftable 复位
  sub_5C2830(this);  // 调 机器人二型·子类扩展字段复位（this+8600..8630）
  sub_5C2870(this);  // 调 机器人二型·Ez8 号码牌资源装配（Monster/Gunner/Ez8/Ez8_Num.img）
  return this;
}



// ------------------------------------------------------------
// 0x4AAC70 sub_4AAC70 —— CNRobotEz8 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AACA0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAC70(void *Block, char pszArg2)  // 函数: CNRobotEz8 删除析构壳
{
  sub_4AACA0();  // 调 (推断)CNRobotEz8 析构（sub_5C28A0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AACA0 sub_4AACA0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotEz8 析构（sub_5C28A0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AACA0(uint32_t *this)  // 实现：(推断)CNRobotEz8 析构（sub_5C28A0）
{
  *this = &CNRobotEz8::`vftable';  // vftable 复位
  sub_5C28A0();  // 调 机器人二型·爆点对象释放（this+8620 槽）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AACF0 sub_4AACF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotExs 构造（sub_5C3100/5C3760）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AACF0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRobotExs 构造（sub_5C3100/5C3760）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNRobotExs::`vftable';  // vftable 复位
  sub_5C3100(this);  // 调 机器人二型·子类扩展字段全区复位（this+8600..8656）
  sub_5C3760(this);  // 调 机动炮怪初始化：载入 Exs_Bullet 弹体资源
  return this;
}



// ------------------------------------------------------------
// 0x4AAD50 sub_4AAD50
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotExs 的覆写判定（转发基类 vt 调用 + 多条件）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AAD50(void *this, int nArg2, int nArg3, int nArg4)  // 实现：(推断)CNRobotExs 的覆写判定（转发基类 vt 调用 + 多条件）
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 5;  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
}



// ------------------------------------------------------------
// 0x4AAD70 sub_4AAD70 —— CNRobotExs 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AADA0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAD70(void *Block, char pszArg2)  // 函数: CNRobotExs 删除析构壳
{
  sub_4AADA0();  // 调 (推断)CNRobotExs 析构（sub_5C3170）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AADA0 sub_4AADA0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotExs 析构（sub_5C3170）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AADA0(uint32_t *this)  // 实现：(推断)CNRobotExs 析构（sub_5C3170）
{
  *this = &CNRobotExs::`vftable';  // vftable 复位
  sub_5C3170();  // 调 机器人二型·出土/挂载对象释放（this+8640 槽）
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AADF0 sub_4AADF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AADF0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNDendroidBasic::`vftable';  // vftable 复位
  sub_5C3A30(this);  // 调 子类扩展字段整块复位（this+8600..8664）
  sub_5C57F0(this);  // 调 树精初始化：语音 TAG 注册 + 动作号快照
  return this;
}



// ------------------------------------------------------------
// 0x4AAE50 sub_4AAE50
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDendroidBasic 析构（sub_5C4780）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAE50(uint32_t *this)  // 实现：(推断)CNDendroidBasic 析构（sub_5C4780）
{
  *this = &CNDendroidBasic::`vftable';  // vftable 复位
  sub_5C4780();  // 调 动作号修复：占用态收手 + 索引回填
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AAEA0 sub_4AAEA0 —— CNDendroidBasic 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AAE50）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AAEA0(uint32_t *Block, char pszArg2)  // 函数: CNDendroidBasic 删除析构壳
{
  sub_4AAE50(Block);  // 调 (推断)CNDendroidBasic 析构（sub_5C4780）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AAED0 sub_4AAED0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDendroid 系派生（off_6F04BC vftable）构造（sub_5C4080）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAED0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNDendroid 系派生（off_6F04BC vftable）构造（sub_5C4080）
{
  sub_4AADF0(this, ArgList, nArg3);  // 调 (推断) CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）
  *(uint32_t *)this = &off_6F04BC;  // 写 vftable 指针 off_6F04BC
  sub_5C4080(this);  // 调 技能参数预设 A：效果号 30038
  return this;
}



// ------------------------------------------------------------
// 0x4AAF30 sub_4AAF30 —— CNDendroid 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AAF60；vt=off_6F04BC）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAF30(void *Block, char pszArg2)  // 函数: CNDendroid 删除析构壳
{
  sub_4AAF60();  // 调 CNDendroid 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AAF60 sub_4AAF60 —— CNDendroid 析构
// off_6F04BC（RTTI 表记 CNDendroid）vftable 复位 → ·0x4AAE50（CNDendroidBasic 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAF60(uint32_t *this)  // 函数: CNDendroid 析构
{
  *this = &off_6F04BC;  // 写 vftable 指针 off_6F04BC
  return sub_4AAE50(this);  // 返回 (推断)CNDendroidBasic 析构（sub_5C4780）
}



// ------------------------------------------------------------
// 0x4AAF70 sub_4AAF70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoliden 构造（sub_5C4100）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAF70(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoliden 构造（sub_5C4100）
{
  sub_4AADF0(this, ArgList, nArg3);  // 调 (推断) CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）
  *(uint32_t *)this = &CNGoliden::`vftable';  // vftable 复位
  sub_5C4100(this);  // 调 技能参数预设 B：效果号 30039
  return this;
}



// ------------------------------------------------------------
// 0x4AAFD0 sub_4AAFD0 —— CNGoliden 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB000）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAFD0(void *Block, char pszArg2)  // 函数: CNGoliden 删除析构壳
{
  sub_4AB000();  // 调 CNGoliden 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB000 sub_4AB000 —— CNGoliden 析构
// vftable 复位 → ·0x4AAE50（CNDendroidBasic 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB000(uint32_t *this)  // 函数: CNGoliden 析构
{
  *this = &CNGoliden::`vftable';  // vftable 复位
  return sub_4AAE50(this);  // 返回 (推断)CNDendroidBasic 析构（sub_5C4780）
}



// ------------------------------------------------------------
// 0x4AB010 sub_4AB010
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRodinglo 构造（sub_5C41B0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AB010(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNRodinglo 构造（sub_5C41B0）
{
  sub_4AADF0(this, ArgList, nArg3);  // 调 (推断) CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）
  *(uint32_t *)this = &CNRodinglo::`vftable';  // vftable 复位
  sub_5C41B0(this);  // 调 技能参数预设 C：效果号 30040 + 超时常量
  return this;
}



// ------------------------------------------------------------
// 0x4AB070 sub_4AB070 —— CNRodinglo 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB0A0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB070(void *Block, char pszArg2)  // 函数: CNRodinglo 删除析构壳
{
  sub_4AB0A0();  // 调 CNRodinglo 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB0A0 sub_4AB0A0 —— CNRodinglo 析构
// vftable 复位 → ·0x4AAE50（CNDendroidBasic 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB0A0(uint32_t *this)  // 函数: CNRodinglo 析构
{
  *this = &CNRodinglo::`vftable';  // vftable 复位
  return sub_4AAE50(this);  // 返回 (推断)CNDendroidBasic 析构（sub_5C4780）
}



// ------------------------------------------------------------
// 0x4AB0B0 sub_4AB0B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB0B0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNSpirit::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8624) = 15;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 8680) = 15;  // this+8680〔uGate8680(推断)〕
  *(uint32_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  *(uint8_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8688) = 0;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  *(uint32_t *)(this + 8704) = 0;  // this+8704〔pSegNameTbl8704(推断)〕
  *(uint32_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(uint32_t *)(this + 8712) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  *(uint32_t *)(this + 8720) = 0;  // this+8720〔pSegThrTbl8720〕
  *(uint32_t *)(this + 8724) = 0;  // this+8724〔nSegThrEnd8724〕
  *(uint32_t *)(this + 8728) = 0;  // this+8728〔nSegThrCap8728〕
  sub_5C6190(this);  // 调 替身槽清空
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB180 sub_4AB180
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpirit 析构（52 行，多成员释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB180(int this)  // 实现：(推断)CNSpirit 析构（52 行，多成员释放）
{
  int pSegNameTbl8704; // eax  | +0x2200 → 【推断】段名表数据指针（std::string 28 字节/条）〔5C6DC0 取段名交 vt+212 播报〕（CNSpirit；va=005C6DC0）
  int fld_21F0; // eax

  *(uint32_t *)this = &CNSpirit::`vftable';  // vftable 复位
  nullsub_3(this);
  if ( *(uint32_t *)(this + 8720) != 0 )  // this+8720〔pSegThrTbl8720〕
    j__free(*(void **)(this + 8720));  // 调 堆释放
  *(uint32_t *)(this + 8720) = 0;  // this+8720〔pSegThrTbl8720〕
  *(uint32_t *)(this + 8724) = 0;  // this+8724〔nSegThrEnd8724〕
  *(uint32_t *)(this + 8728) = 0;  // this+8728〔nSegThrCap8728〕
  pSegNameTbl8704 = *(uint32_t *)(this + 8704);  // this+8704〔pSegNameTbl8704(推断)〕
  if ( pSegNameTbl8704 != 0 )  // fld_2200=this+8704 pSegNameTbl8704
  {
    sub_4166A0(pSegNameTbl8704, *(uint32_t *)(this + 8708));  // 调 析构区间内 28B string 元素
    j__free(*(void **)(this + 8704));  // 调 堆释放
  }
  *(uint32_t *)(this + 8704) = 0;  // this+8704〔pSegNameTbl8704(推断)〕
  *(uint32_t *)(this + 8708) = 0;  // this+8708〔pCandTbl8708(推断)〕
  *(uint32_t *)(this + 8712) = 0;  // this+8712〔nCandTblEnd8712(推断)〕
  fld_21F0 = *(uint32_t *)(this + 8688);  // this+8688〔bVec8688(推断)〕
  if ( fld_21F0 != 0 )  // fld_21F0=this+8688 bVec8688
  {
    sub_4166A0(fld_21F0, *(uint32_t *)(this + 8692));  // 调 析构区间内 28B string 元素
    j__free(*(void **)(this + 8688));  // 调 堆释放
  }
  *(uint32_t *)(this + 8688) = 0;  // this+8688〔bVec8688(推断)〕
  *(uint32_t *)(this + 8692) = 0;  // this+8692〔uVec8692(推断)〕
  *(uint32_t *)(this + 8696) = 0;  // this+8696〔uVec8696(推断)〕
  if ( *(uint32_t *)(this + 8680) >= 0x10u )  // this+8680〔uGate8680(推断)〕
    j__free(*(void **)(this + 8660));  // 调 堆释放
  *(uint32_t *)(this + 8680) = 15;  // this+8680〔uGate8680(推断)〕
  *(uint32_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  *(uint8_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  if ( *(uint32_t *)(this + 8652) >= 0x10u )  // this+8652〔uPhase8652(推断)〕
    j__free(*(void **)(this + 8632));  // 调 堆释放
  *(uint32_t *)(this + 8652) = 15;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  if ( *(uint32_t *)(this + 8624) >= 0x10u )  // this+8624〔uAI8624(推断)〕
    j__free(*(void **)(this + 8604));  // 调 堆释放
  *(uint32_t *)(this + 8624) = 15;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  return sub_4A50F0(this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AB2F0 sub_4AB2F0 —— CNSpirit 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB180，含 3×std::string 与 3×缓冲释放）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB2F0(void *Block, char pszArg2)  // 函数: CNSpirit 删除析构壳
{
  sub_4AB180((int)Block);  // 调 (推断)CNSpirit 析构（52 行，多成员释放）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB320 sub_4AB320
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNNaias（水泽仙女）构造（+8744 标志 / sub_5C8290）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4AB320(uint8_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNNaias（水泽仙女）构造（+8744 标志 / sub_5C8290）
{
  sub_4AB0B0((int)this, ArgList, nArg3);  // 调 (推断) CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基
  *(uint32_t *)this = &CNNaias::`vftable';  // vftable 复位
  *(this + 8744) = 0;  // this+8744 【推断】主倒计时截止
  sub_5C8290(this);  // 调 水精灵语音注册（id 196613）
  return this;
}



// ------------------------------------------------------------
// 0x4AB380 sub_4AB380 —— CNNaias 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB3B0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB380(void *Block, char pszArg2)  // 函数: CNNaias 删除析构壳
{
  sub_4AB3B0();  // 调 CNNaias 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB3B0 sub_4AB3B0 —— CNNaias 析构
// vftable 复位 → ·0x4AB180（CNSpirit 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB3B0(int this)  // 函数: CNNaias 析构
{
  *(uint32_t *)this = &CNNaias::`vftable';  // vftable 复位
  return sub_4AB180(this);  // 返回 (推断)CNSpirit 析构（52 行，多成员释放）
}



// ------------------------------------------------------------
// 0x4AB3C0 sub_4AB3C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAdor 构造（sub_5C8470）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB3C0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNAdor 构造（sub_5C8470）
{
  sub_4AB0B0((int)this, ArgList, nArg3);  // 调 (推断) CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基
  *this = &CNAdor::`vftable';  // vftable 复位
  sub_5C8470(this);  // 调 火精灵语音注册（id 196612）
  return this;
}



// ------------------------------------------------------------
// 0x4AB420 sub_4AB420 —— CNAdor 析构
// vftable 复位 → ·0x4AB180（CNSpirit 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB420(int this)  // 函数: CNAdor 析构
{
  *(uint32_t *)this = &CNAdor::`vftable';  // vftable 复位
  return sub_4AB180(this);  // 返回 (推断)CNSpirit 析构（52 行，多成员释放）
}



// ------------------------------------------------------------
// 0x4AB430 sub_4AB430
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSoulEter（食魂者）构造（sub_5C6590）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB430(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNSoulEter（食魂者）构造（sub_5C6590）
{
  sub_4AB3C0(this, ArgList, nArg3);  // 调 CNAdor 构造，结果存 result
  *this = &CNSoulEter::`vftable';  // vftable 复位
  sub_5C6590(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB490 sub_4AB490 —— CNAdor 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB420）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB490(void *Block, char pszArg2)  // 函数: CNAdor 删除析构壳
{
  sub_4AB420((int)Block);  // 调 CNAdor 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB4C0 sub_4AB4C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStalker（跟踪者）构造（sub_5C8650）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB4C0(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNStalker（跟踪者）构造（sub_5C8650）
{
  sub_4AB0B0((int)this, ArgList, nArg3);  // 调 (推断) CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基
  *this = &CNStalker::`vftable';  // vftable 复位
  sub_5C8650(this);  // 调 暗精灵语音注册（id 196615）
  return this;
}



// ------------------------------------------------------------
// 0x4AB520 sub_4AB520 —— CNStalker 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB550）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB520(void *Block, char pszArg2)  // 函数: CNStalker 删除析构壳
{
  sub_4AB550();  // 调 CNStalker 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB550 sub_4AB550 —— CNStalker 析构
// vftable 复位 → ·0x4AB180（CNSpirit 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB550(int this)  // 函数: CNStalker 析构
{
  *(uint32_t *)this = &CNStalker::`vftable';  // vftable 复位
  return sub_4AB180(this);  // 返回 (推断)CNSpirit 析构（52 行，多成员释放）
}



// ------------------------------------------------------------
// 0x4AB560 sub_4AB560
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWisp（鬼火）构造（sub_5C8FE0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB560(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNWisp（鬼火）构造（sub_5C8FE0）
{
  sub_4AB0B0((int)this, ArgList, nArg3);  // 调 (推断) CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基
  *this = &CNWisp::`vftable';  // vftable 复位
  sub_5C8FE0(this);  // 调 光精灵语音注册（id 196614）+ 发光外观挂装
  return this;
}



// ------------------------------------------------------------
// 0x4AB5C0 sub_4AB5C0 —— CNWisp 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB5F0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB5C0(void *Block, char pszArg2)  // 函数: CNWisp 删除析构壳
{
  sub_4AB5F0();  // 调 CNWisp 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB5F0 sub_4AB5F0 —— CNWisp 析构
// vftable 复位 → ·0x4AB180（CNSpirit 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB5F0(int this)  // 函数: CNWisp 析构
{
  *(uint32_t *)this = &CNWisp::`vftable';  // vftable 复位
  return sub_4AB180(this);  // 返回 (推断)CNSpirit 析构（52 行，多成员释放）
}



// ------------------------------------------------------------
// 0x4AB600 sub_4AB600
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLotusBasic（莲花基）构造（+8644 标志 / +8640 IObject）—— 植物族（Lotus/MonsterFlower）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB600(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNLotusBasic（莲花基）构造（+8644 标志 / +8640 IObject）—— 植物族（Lotus/Mo…
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNLotusBasic::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8640) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8652) = 1;  // this+8652〔uPhase8652(推断)〕
  *(uint8_t *)(this + 8654) = 0;
  *(uint8_t *)(this + 8653) = 0;  // this+8653〔bGate8653〕
  *(uint32_t *)(this + 8664) = 0;  // this+8664〔uAI8664(推断)〕
  *(uint32_t *)(this + 8660) = 0;  // this+8660〔uEvt8660(推断)〕
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  nullsub_3(this);
  sub_5CB360(this);  // 调 莲花初始化/受击演出复位
  return this;
}



// ------------------------------------------------------------
// 0x4AB6B0 sub_4AB6B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLotusBasic 析构（sub_5C92A0 + IObject @+8640）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB6B0(uint32_t *this)  // 实现：(推断)CNLotusBasic 析构（sub_5C92A0 + IObject @+8640）
{
  *this = &CNLotusBasic::`vftable';  // vftable 复位
  sub_5C92A0();  // 调 挂接对象释放
  *(this + 2160) = &nengine::IObject::`vftable';  // this+8640 = uCastSlot8640
  *((uint8_t *)this + 8644) = 0;  // this+8644 = 相位槽
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AB710 sub_4AB710 —— CNLotusBasic 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB6B0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB710(uint32_t *Block, char pszArg2)  // 函数: CNLotusBasic 删除析构壳
{
  sub_4AB6B0(Block);  // 调 (推断)CNLotusBasic 析构（sub_5C92A0 + IObject @+8640）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB740 sub_4AB740
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLotus 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB740(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNLotus 构造
{
  sub_4AB600((int)this, ArgList, nArg3);  // 调 (推断) CNLotusBasic（莲花基）构造（+8644 标志 / +8640 IObject）—— 植物族（Lotus/Mo…
  *this = &CNLotus::`vftable';  // vftable 复位
  return this;
}



// ------------------------------------------------------------
// 0x4AB770 sub_4AB770 —— CNLotus 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB7A0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB770(void *Block, char pszArg2)  // 函数: CNLotus 删除析构壳
{
  sub_4AB7A0();  // 调 CNLotus 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB7A0 sub_4AB7A0 —— CNLotus 析构
// vftable 复位 → ·0x4AB6B0（CNLotusBasic 析构，含 IObject @+8640 复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB7A0(uint32_t *this)  // 函数: CNLotus 析构
{
  *this = &CNLotus::`vftable';  // vftable 复位
  return sub_4AB6B0(this);  // 返回 (推断)CNLotusBasic 析构（sub_5C92A0 + IObject @+8640）
}



// ------------------------------------------------------------
// 0x4AB7B0 sub_4AB7B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNMonsterFlower（怪物花）构造（sub_5CB970）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AB7B0(char *this, char ArgList, int nArg3)  // 实现：(推断)★ CNMonsterFlower（怪物花）构造（sub_5CB970）
{
  sub_4A4EA0(this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNMonsterFlower::`vftable';  // vftable 复位
  sub_5CB970(this);  // 调 章鱼/莲花子类状态复位
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB810 sub_4AB810
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMonsterFlower 析构壳（sub_5CBD40）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB810(void *Block, char pszArg2)  // 实现：(推断)CNMonsterFlower 析构壳（sub_5CBD40）
{
  sub_5CBD40();
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB840 sub_4AB840
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpikeKing（尖刺王）构造 —— +8616 = sub_4A2D10()（20 字节链表头），
//   这是 CNSpikeKing 内嵌链表对象的实证，参照 0x4A2D10 注释。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB840(int this, char ArgList, int nArg3)  // 实现：这是 CNSpikeKing 内嵌链表对象的实证，参照 0x4A2D10 注释
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNSpikeKing::`vftable';  // vftable 复位
  *(uint32_t *)(this + 8616) = sub_4A2D10();  // this+8616〔uAI8616(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint8_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8624) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8636) = 1;  // this+8636〔pDollTarget(推断)〕
  *(uint8_t *)(this + 8638) = 0;  // this+8638〔bRes8638〕
  *(uint8_t *)(this + 8637) = 0;  // this+8637〔bSwingGate8637〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  *(uint8_t *)(this + 8664) = 0;  // this+8664〔uAI8664(推断)〕
  *(uint32_t *)(this + 8660) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  *(uint8_t *)(this + 8672) = 1;  // this+8672〔uAI8672(推断)〕
  *(uint8_t *)(this + 8674) = 0;  // this+8674〔bAI8674〕
  *(uint8_t *)(this + 8673) = 0;  // this+8673〔bAI8673〕
  *(uint32_t *)(this + 8684) = 0;  // this+8684〔bGate8684(推断)〕
  *(uint32_t *)(this + 8680) = 0;  // this+8680〔uGate8680(推断)〕
  *(uint32_t *)(this + 8676) = 0;  // this+8676〔uAI8676(推断)〕
  sub_5CC490(this);  // 调 刺王语音注册与相位复位
  sub_5CBD50(this);  // 调 参数装载与倒计时
  return this;
}



// ------------------------------------------------------------
// 0x4AB930 sub_4AB930 —— CNSpikeKing 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4AB960，含内嵌链表存储释放）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB930(void *Block, char pszArg2)  // 函数: CNSpikeKing 删除析构壳
{
  sub_4AB960();  // 调 (推断)CNSpikeKing 析构（sub_4E3360 + IObject @+8660）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4AB960 sub_4AB960
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpikeKing 析构（sub_4E3360 + IObject @+8660）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB960(char *this)  // 实现：(推断)CNSpikeKing 析构（sub_4E3360 + IObject @+8660）
{
  *(uint32_t *)this = &CNSpikeKing::`vftable';  // vftable 复位
  sub_4E3360();  // 调 怪物资源侧析构（释放三块 + 全局怪物计数递减）
  *((uint32_t *)this + 2165) = &nengine::IObject::`vftable';  // this+8660 = uEvt8660
  *(this + 8664) = 0;  // this+8664 【推断】子类AI相位槽
  *((uint32_t *)this + 2156) = &nengine::IObject::`vftable';  // this+8624 = uAI8624
  *(this + 8628) = 0;  // this+8628 【推断】指挥计时戳
  sub_6569D0(this + 8612);  // 调 清 +28
  j__free(*((void **)this + 2154));  // 调 堆释放
  *((uint32_t *)this + 2154) = 0;  // this+8616 = uAI8616
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4AB9F0 sub_4AB9F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas/Titan）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB9F0(int this, char ArgList, int nArg3)  // 实现：(推断)★ CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas…
{
  sub_4A4EA0((char *)this, ArgList, nArg3);  // 调 ★ IRDMonster 构造/析构（0x4A4EA0 / 0x4A50F0 / 0x4A5350）
  *(uint32_t *)this = &CNAbom::`vftable';  // vftable 复位
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8600) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
  *(uint8_t *)(this + 8614) = 0;  // this+8614〔bLockC8614(推断)〕
  *(uint8_t *)(this + 8613) = 0;  // this+8613〔bLockB8613(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  *(uint8_t *)(this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8648) = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8656) = 0;  // this+8656〔uPair8656(推断)〕
  *(uint8_t *)(this + 8660) = 1;  // this+8660〔uEvt8660(推断)〕
  *(uint8_t *)(this + 8662) = 0;
  *(uint8_t *)(this + 8661) = 0;
  *(uint32_t *)(this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
  *(uint32_t *)(this + 8668) = 0;  // this+8668〔nCool8668(推断)〕
  *(uint32_t *)(this + 8664) = 0;  // this+8664〔uAI8664(推断)〕
  sub_5CD100(this);  // 调 相位字段初始化
  sub_5CD8D0(this);  // 调 巨人语音装载
  return this;
}



// ------------------------------------------------------------
// 0x4ABAD0 sub_4ABAD0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAbom 析构（sub_5CD150 + IObject @+8648）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABAD0(uint32_t *this)  // 实现：(推断)CNAbom 析构（sub_5CD150 + IObject @+8648）
{
  *this = &CNAbom::`vftable';  // vftable 复位
  sub_5CD150();  // 调 派生对象槽释放
  *(this + 2162) = &nengine::IObject::`vftable';  // this+8648 = 相位/缓存槽
  *((uint8_t *)this + 8652) = 0;  // this+8652 = 相位槽
  *(this + 2150) = &nengine::IObject::`vftable';  // this+8600 = uAI8600
  *((uint8_t *)this + 8604) = 0;  // this+8604 = bAI8604
  return sub_4A50F0((int)this);  // 调 IRDMonster 基类析构
}



// ------------------------------------------------------------
// 0x4ABB40 sub_4ABB40 —— CNAbom 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4ABAD0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABB40(uint32_t *Block, char pszArg2)  // 函数: CNAbom 删除析构壳
{
  sub_4ABAD0(Block);  // 调 (推断)CNAbom 析构（sub_5CD150 + IObject @+8648）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4ABB70 sub_4ABB70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoliath（歌利亚）构造（sub_5CD1E0/5CD220）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABB70(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNGoliath（歌利亚）构造（sub_5CD1E0/5CD220）
{
  sub_4AB9F0((int)this, ArgList, nArg3);  // 调 (推断) CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas…
  *this = &CNGoliath::`vftable';  // vftable 复位
  sub_5CD1E0(this);  // 调 相位字段复位
  sub_5CD220(this);  // 调 六阈值装载
  return this;
}



// ------------------------------------------------------------
// 0x4ABBD0 sub_4ABBD0 —— CNGoliath 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4ABC00）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABBD0(void *Block, char pszArg2)  // 函数: CNGoliath 删除析构壳
{
  sub_4ABC00();  // 调 (推断)CNGoliath 析构（sub_5CD2A0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4ABC00 sub_4ABC00
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoliath 析构（sub_5CD2A0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABC00(uint32_t *this)  // 实现：(推断)CNGoliath 析构（sub_5CD2A0）
{
  *this = &CNGoliath::`vftable';  // vftable 复位
  sub_5CD2A0();  // 调 派生对象槽释放
  return sub_4ABAD0(this);  // 返回 (推断)CNAbom 析构（sub_5CD150 + IObject @+8648）
}



// ------------------------------------------------------------
// 0x4ABC50 sub_4ABC50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAtlas（阿特拉斯）构造（sub_5CD360/5CD380）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABC50(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNAtlas（阿特拉斯）构造（sub_5CD360/5CD380）
{
  sub_4AB9F0((int)this, ArgList, nArg3);  // 调 (推断) CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas…
  *this = &CNAtlas::`vftable';  // vftable 复位
  sub_5CD360(this);  // 调 轻量相位复位
  sub_5CD380(this);  // 调 双阈值装载
  return this;
}



// ------------------------------------------------------------
// 0x4ABCB0 sub_4ABCB0 —— CNAtlas 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4ABCE0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABCB0(void *Block, char pszArg2)  // 函数: CNAtlas 删除析构壳
{
  sub_4ABCE0();  // 调 (推断)CNAtlas 析构
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4ABCE0 sub_4ABCE0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAtlas 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABCE0(uint32_t *this)  // 实现：(推断)CNAtlas 析构
{
  *this = &CNAtlas::`vftable';  // vftable 复位
  nullsub_3(this);
  return sub_4ABAD0(this);  // 返回 (推断)CNAbom 析构（sub_5CD150 + IObject @+8648）
}



// ------------------------------------------------------------
// 0x4ABD30 sub_4ABD30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTitan（泰坦）构造（sub_5CD3C0/599D80）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABD30(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)★ CNTitan（泰坦）构造（sub_5CD3C0/599D80）
{
  sub_4AB9F0((int)this, ArgList, nArg3);  // 调 (推断) CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas…
  *this = &CNTitan::`vftable';  // vftable 复位
  sub_5CD3C0(this);  // 调 三字节门复位
  sub_599D80(this);  // 调 虚表转发垫片：调用 vt+1308 并原样返回其结果
  return this;
}



// ------------------------------------------------------------
// 0x4ABD90 sub_4ABD90 —— CNTitan 删除析构壳
// 与 ·0x4A53E0 同构（析构体 ·0x4ABDC0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABD90(void *Block, char pszArg2)  // 函数: CNTitan 删除析构壳
{
  sub_4ABDC0();  // 调 (推断)CNTitan 析构（sub_5CD3F0）
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4ABDC0 sub_4ABDC0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTitan 析构（sub_5CD3F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABDC0(uint32_t *this)  // 实现：(推断)CNTitan 析构（sub_5CD3F0）
{
  *this = &CNTitan::`vftable';  // vftable 复位
  sub_5CD3F0();  // 调 派生对象槽释放
  return sub_4ABAD0(this);  // 返回 (推断)CNAbom 析构（sub_5CD150 + IObject @+8648）
}



// ============================================================
// SECTION 0x4AEA30 — 环形缓冲/容器排空族（0x4AEA30-0x4AF010，CNMonster 家族的回收/重置）
// ============================================================
// ------------------------------------------------------------
// 0x4AEA30 sub_4AEA30
// ------------------------------------------------------------
// 【解读】
//   【推断】链表按"容器+4"标签查找（命中对象列表的成员函数; a2+8 为键）。
//   找到后调目标 vt+4(a2) —— 疑为"按类型分发通知"。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AEA30(uint32_t *this, int pArg2)  // 函数 sub_4AEA30：环形缓冲/容器排空族（0x4AEA30 0x4AF010，CNMonster 家族的回收/重置）
{
  uint32_t *result; // eax
  uint32_t *fld_e2; // edx
  uint32_t *v4; // ecx

  result = (uint32_t *)*(this + 3);  // this+12 = 技能槽记录次字
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
    result = (uint32_t *)*fld_e2;  // result=this+12 物品类型号
    if ( (uint32_t *)*fld_e2 != fld_e2 )  // fld_e2=this+8 物品 id
    {
      while ( 1 )  // 无限循环
      {
        v4 = (uint32_t *)result[2];  // result=this+12 物品类型号
        if ( *(uint32_t *)(pArg2 + 8) == v4[1] )  // pArg2+8〔nSkillRec8(推断)〕
          break;
        result = (uint32_t *)*result;  // result=this+12 物品类型号
        if ( result == fld_e2 )  // result=this+12 物品类型号
          return result;  // result=this+12 物品类型号
      }
      return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v4 + 4))(v4, pArg2);  // 调用虚函数（虚表槽 +4）
    }
  }
  return result;  // result=this+12 物品类型号
}



// ------------------------------------------------------------
// 0x4AEA70 sub_4AEA70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 环形缓冲逐格弹出（this+68/72/76/80 四字段 = 缓冲基/容量/头下标/计数）。
//   每轮: 取缓冲[头] → 头++ (%容量) → 计数-- → 计数归 0 时下标清零 →
//   弹出对象非空则先在双向链表中查找匹配节点（容器+4 键）并 vt+4 通知，
//   再交全局 sub_49C800(&unk_9B9310, obj) —— 全局队列投递。
//   语义 = 对象回收队列的逐帧排空（unk_9B9310 = 全局延迟释放/重生池）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEA70(int *this)  // 实现：语义 = 对象回收队列的逐帧排空（unk_9B9310 = 全局延迟释放/重生池）
{
  int result; // eax
  unsigned int fld_e19; // eax
  int fld_e192; // edx
  unsigned int fld_e18; // edi
  int fld_e17; // ebx
  unsigned int fld_e193; // eax
  unsigned int fld_e182; // ecx
  uint32_t *fld_e2; // edx
  uint32_t *v10; // eax
  uint32_t *v11; // ecx
  int fld_e172; // [esp+Ch] [ebp-4h] BYREF

  while ( 1 )  // 无限循环
  {
    result = *(this + 20);  // this+80 = nAuraStage
    if ( result == 0 )  // result=this+80 关联角色对象
      return result;  // result=this+80 关联角色对象
    fld_e19 = (unsigned int)*(this + 19) >> 2;  // this+76〔pBtnActionE〕
    fld_e192 = *(this + 19) - 4 * fld_e19;  // this+76〔pBtnActionE〕
    fld_e18 = *(this + 18);  // this+72〔nSnapshot72(推断)〕
    if ( fld_e18 <= fld_e19 )  // fld_e18=this+72 nSnapshot72
      fld_e19 -= fld_e18;
    fld_e17 = *(uint32_t *)(*(uint32_t *)(*(this + 17) + 4 * fld_e19) + 4 * fld_e192);  // this+68〔nCharCount(推断)〕
    fld_e193 = *(this + 19) + 1;  // this+76〔pBtnActionE〕
    fld_e182 = 4 * *(this + 18);
    *(this + 19) = fld_e193;  // this+76〔pBtnActionE〕
    if ( fld_e182 <= fld_e193 )  // fld_e193=this+76 pBtnActionE
      *(this + 19) = 0;  // this+76〔pBtnActionE〕
    result = *(this + 20) - 1;  // this+80 = nAuraStage
    *(this + 20) = result;  // this+80 = nAuraStage
    if ( result == 0 )  // result=this+80 关联角色对象
      *(this + 19) = 0;  // this+76〔pBtnActionE〕
    if ( fld_e17 == 0 )  // fld_e17=this+68 nCharCount
      return result;  // result=this+80 关联角色对象
    if ( *(this + 3) != 0 )  // this+12 = 技能槽记录次字
    {
      fld_e2 = (uint32_t *)*(this + 2);  // this+8 = 技能槽记录首字
      v10 = (uint32_t *)*fld_e2;  // fld_e2=this+8 物品 id
      if ( (uint32_t *)*fld_e2 != fld_e2 )  // fld_e2=this+8 物品 id
      {
        while ( 1 )  // 无限循环
        {
          v11 = (uint32_t *)v10[2];
          if ( *(uint32_t *)(fld_e17 + 8) == v11[1] )  // fld_e17=this+68 nCharCount
            break;
          v10 = (uint32_t *)*v10;
          if ( v10 == fld_e2 )  // fld_e2=this+8 物品 id
            goto LABEL_15;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*v11 + 4))(v11, fld_e17);  // 调用虚函数（虚表槽 +4）
      }
    }
LABEL_15:
    fld_e172 = fld_e17;  // fld_e17=this+68 nCharCount
    sub_49C800((int)&unk_9B9310, &fld_e172);  // 调 deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
  }
}



// ------------------------------------------------------------
// 0x4AEB30 sub_4AEB30
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4AEA70 排空 + sub_58B380(this+4) 后续清理。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEB30(int *this)  // 实现：(推断)0x4AEA70 排空 + sub_58B380(this+4) 后续清理
{
  sub_4AEA70(this);  // 调 语义 = 对象回收队列的逐帧排空（unk_9B9310 = 全局延迟释放/重生池）
  return sub_58B380(this + 4);  // 调 时间线解释器主循环：读[函数指针][时刻][参数个数][参数...]，到点执行否则重排队
}



// ------------------------------------------------------------
// 0x4AEB50 sub_4AEB50
// ------------------------------------------------------------
// 【解读】
//   【推断】环形缓冲整体排空（this+4/+8/+12/+16 = 基/容量/头/计数）+ sub_406E40 收尾。
//   与 0x4AEA70 对偶（一个逐格、一个整体）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEB50(unsigned int *this)  // 实现：与 0x4AEA70 对偶（一个逐格、一个整体）
{
  int fld_e4; // eax
  unsigned int fld_e3; // eax
  int fld_e32; // ecx
  unsigned int fld_e2; // edi
  int fld_e1; // ecx
  int fld_e42; // eax
  unsigned int fld_e33; // edx
  unsigned int fld_e22; // edi
  unsigned int v10; // eax
  uint32_t v11[4]; // [esp+Ch] [ebp-10h] BYREF

  fld_e4 = *(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  v11[3] = 0;
  if ( fld_e4 != 0 )  // fld_e4=this+16 nChannelTypeSel
  {
    do
    {
      fld_e3 = *(this + 3) >> 2;  // this+12 = 技能槽记录次字
      fld_e32 = *(this + 3) - 4 * fld_e3;  // this+12 = 技能槽记录次字
      fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
      if ( fld_e2 <= fld_e3 )  // fld_e2=this+8 物品 id
        fld_e3 -= fld_e2;
      fld_e1 = *(uint32_t *)(*(uint32_t *)(*(this + 1) + 4 * fld_e3) + 4 * fld_e32);  // this+4 = pHostObj
      fld_e42 = *(this + 4);  // this+16〔nChannelTypeSel(推断)〕
      if ( fld_e42 != 0 )  // fld_e42=this+16 nChannelTypeSel
      {
        fld_e33 = *(this + 3) + 1;  // this+12 = 技能槽记录次字
        fld_e22 = 4 * *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 3) = fld_e33;  // this+12 = 技能槽记录次字
        if ( fld_e22 <= fld_e33 )  // fld_e22=this+8 物品 id
          *(this + 3) = 0;  // this+12 = 技能槽记录次字
        v10 = fld_e42 - 1;
        *(this + 4) = v10;  // this+16〔nChannelTypeSel(推断)〕
        if ( v10 == 0 )
          *(this + 3) = 0;  // this+12 = 技能槽记录次字
      }
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      {
        v11[0] = fld_e1;  // fld_e1=this+4 宿主对象
        sub_49C800((int)&unk_9B9310, v11);  // 调 deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
      }
    }
    while ( *(this + 4) != 0 );  // this+16〔nChannelTypeSel(推断)〕
  }
  sub_406E40((int)this);  // 调 动态缓冲整体释放（+16 计数递减归零 → +4 槽指针表逐项 free → 计数与表指针清零）
}



// ------------------------------------------------------------
// 0x4AEC00 sub_4AEC00
// ------------------------------------------------------------
// 【解读】
//   【推断】容器重置（sub_498A00 + sub_58B450 + 清 4 字段 + 链头释放）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AEC00(uint32_t *this)  // 实现：(推断)容器重置（sub_498A00 + sub_58B450 + 清 4 字段 + 链头释放）
{
  uint32_t *pThis_1; // edi

  pThis_1 = this + 1;
  sub_498A00(this + 1);  // 调 容器重置（首指针重建 + 计数清零）
  sub_58B450(this + 4);  // 调 时间线构造：CNTimer 虚表装配 + operator new(0xFA0) 指令缓冲 + 时标 1000
  *(this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 19) = 0;  // this+76〔pBtnActionE〕
  *(this + 20) = 0;  // this+80 = nAuraStage
  if ( pThis_1[2] != 0 )
    sub_6569D0(pThis_1);  // 调 清 +28
  return this;
}



// ------------------------------------------------------------
// 0x4AEC70 sub_4AEC70
// ------------------------------------------------------------
// 【解读】
//   【推断】容器析构（sub_4AEB50 排空 + sub_58B4D0 + sub_4989D0 释放链）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEC70(uint32_t *this)  // 实现：(推断)容器析构（sub_4AEB50 排空 + sub_58B4D0 + sub_4989D0 释放链）
{
  void **pThis_1; // edi

  pThis_1 = (void **)(this + 1);  // this+4 = pHostObj
  if ( *(this + 3) != 0 )  // this+12 = 技能槽记录次字
    sub_6569D0(this + 1);  // this+4 = pHostObj
  sub_4AEB50(this + 16);  // this+64〔apServerTabBtn(推断)〕
  sub_58B4D0(this + 4);  // 调 时间线析构：释放指令缓冲，+20 恢复 nengine::IObject 虚表
  sub_4989D0(pThis_1);  // 调 容器双清 + 缓冲释放
}



// ------------------------------------------------------------
// 0x4AECE0 sub_4AECE0
// ------------------------------------------------------------
// 【解读】
//   【推断】动画切换: sub_491C70(a2) 取动画资源 → sub_493A60(this, res) 应用。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AECE0(void *this, int nArg2)  // 实现：(推断)动画切换: sub_491C70(a2) 取动画资源 → sub_493A60(this, res) 应用
{
  int v3; // eax

  v3 = sub_491C70(nArg2);  // 调 ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
  return sub_493A60((int)this, v3);  // 调 时间推进包装（累计 +32；+212 同步源优先）
}



// ------------------------------------------------------------
// 0x4AED00 sub_4AED00
// ------------------------------------------------------------
// 【解读】
//   【推断】有效性判定: this+16 字节非 0 或 this+0 浮点 > 0.0。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4AED00(float *this)  // 实现：(推断)有效性判定: this+16 字节非 0 或 this+0 浮点 > 0.0
{
  return *((uint8_t *)this + 16) != 0 || *this > 0.0;  // this+16〔nChannelTypeSel(推断)〕
}



// ------------------------------------------------------------
// 0x4AED20 sub_4AED20
// ------------------------------------------------------------
// 【解读】
//   【推断】帧数据 getter（与 IRDCollisionObject_vmt270 的帧检查同构）:
//   this+642 非 0 → 直接返回 this+644；否则从动画对象 +112 读帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED20(int this)  // 实现：this+642 非 0 → 直接返回 this+644；否则从动画对象 +112 读帧
{
  int fld_78; // esi

  if ( *(uint8_t *)(this + 642) != 0 )  // this+642〔bHitBoxSnap642〕
    return *(uint32_t *)(this + 644);  // this+644〔uHitBoxSnap644〕
  fld_78 = *(uint32_t *)(this + 120);  // this+120〔pAnimObj〕
  if ( fld_78 == 0 )  // fld_78=this+120 pAnimObj
    return 0;
  if ( *(uint32_t *)(fld_78 + 148) == -1 )  // fld_78=this+120 pAnimObj
    sub_4938F0(*(uint32_t *)(this + 120));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  return *(uint32_t *)(fld_78 + 112);  // fld_78=this+120 pAnimObj
}



// ------------------------------------------------------------
// 0x4AED60 sub_4AED60
// ------------------------------------------------------------
// 【解读】
//   【推断】防篡改浮点自增（读 sub_41A5E0 → +a2 → 写 sub_41A590）。
// ------------------------------------------------------------
double /*thiscall*/ sub_4AED60(void *this, float fArg2)  // 实现：(推断)防篡改浮点自增（读 sub_41A5E0 → +a2 → 写 sub_41A590）
{
  int v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0((unsigned int)this)) + fArg2;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, v3, v5);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return *(float *)&v5;
}



// ------------------------------------------------------------
// 0x4AED90 sub_4AED90
// ------------------------------------------------------------
// 【解读】
//   【推断】转发 sub_47EFD0（this, a2, a3, a4, a4, a5）—— 六参版桥接。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED90(char *this, float fArg2, int nArg3, int nArg4, int nArg5)  // 实现：(推断)转发 sub_47EFD0（this, a2, a3, a4, a4, a5）—— 六参版桥接
{
  return sub_47EFD0(this, fArg2, nArg3, nArg4, nArg4, nArg5);  // 返回 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）(推断)
}



// ------------------------------------------------------------
// 0x4AEDB0 sub_4AEDB0
// ------------------------------------------------------------
// 【解读】
//   【推断】全局清理: sub_4C4210 + sub_617B80 + 释放全局对象 dword_9B9410（vt+0(1) 后置空）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEDB0(void *this)  // 实现：(推断)全局清理: sub_4C4210 + sub_617B80 + 释放全局对象 dword_9B9410（vt+0(1) 后置…
{
  int v1; // ecx
  int result; // eax

  nullsub_3(this);
  nullsub_3(v1);
  sub_4C4210();
  result = sub_617B80();  // 调 珠体参数块读取：dword_9B93C4/9B93C8 ——(推断：珠体全局参数（与 9B93xx 活动装备块相邻）)
  if ( dword_9B9410 != 0 )
    result = (**(int (/*thiscall*/ ***)(int, int))dword_9B9410)(dword_9B9410, 1);
  dword_9B9410 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4AEDD0 sub_4AEDD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ IRDActiveObject 状态区大重置（vmt10 类初始化链的核心，109 行）。
//   写入: +96 = 273（条件位集，与 CNRDObject_vmt28 的 273 掩码直证对应！）、
//   +608 归零、+7512 = -1、+7516..+7608 连续清零、+7760 = 4（模式）、+7836 = 1000（千分基准）、
//   +7924 = 1、+7728/+7730 标志、+8172 区 5×2 循环清 20 个 DWORD、+7428/+8212 收尾。
//   **+96 = 273 是条件位掩码的初始值（受击态条件位）—— 与 docs/14 §2 "vt+40 条件位掩码"闭环。**
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEDD0(int this)  // 实现：**+96 = 273 是条件位掩码的初始值（受击态条件位）—— 与 docs/14 §2 vt+40 条件位掩码闭环。**
{
  int result; // eax
  uint32_t *pThis_1FEC; // edx
  int i; // edi
  int j; // esi

  result = 0;
  *(uint32_t *)(this + 96) = 273;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 608) = 0;  // this+608〔nAttackGate〕
  *(uint32_t *)(this + 7512) = -1;
  *(uint32_t *)(this + 7516) = 0;
  *(uint32_t *)(this + 7520) = 0;  // this+7520〔nSightRange(推断)〕
  *(uint32_t *)(this + 7524) = 0;  // this+7524〔uCfgBlock4(推断)〕
  *(uint32_t *)(this + 7528) = 0;  // this+7528〔bCfgBlock8(推断)〕
  *(uint32_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint32_t *)(this + 7536) = 0;  // this+7536〔bCfgBlock16(推断)〕
  *(uint32_t *)(this + 7540) = 0;
  *(uint32_t *)(this + 7544) = 0;
  *(uint32_t *)(this + 7548) = 0;
  *(uint32_t *)(this + 7552) = 0;
  *(uint32_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint32_t *)(this + 7560) = 0;
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7592) = 0;  // this+7592〔nAtkSegSlot7592〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7600) = 0;
  *(uint32_t *)(this + 7604) = 0;
  *(uint8_t *)(this + 7608) = 0;
  *(uint8_t *)(this + 7609) = 0;
  *(uint32_t *)(this + 7692) = 0;
  *(uint32_t *)(this + 7696) = 0;  // this+7696 getter
  *(uint8_t *)(this + 7729) = 0;
  *(uint32_t *)(this + 7760) = 4;
  *(uint8_t *)(this + 7764) = 0;  // this+7764〔bTimerObj〕
  *(uint8_t *)(this + 7780) = 0;
  *(uint8_t *)(this + 7730) = 1;  // this+7730〔bSubEnable〕
  *(uint32_t *)(this + 7768) = 0;  // this+7768〔pObj7768〕
  *(uint32_t *)(this + 7772) = 0;  // this+7772〔nCounterState〕
  *(uint32_t *)(this + 7776) = 0;  // this+7776〔bPeerInit〕
  *(uint32_t *)(this + 7784) = 0;
  *(uint32_t *)(this + 7788) = 0;
  *(uint8_t *)(this + 7792) = 0;
  *(uint32_t *)(this + 7796) = 0;
  *(uint32_t *)(this + 7800) = 0;
  *(uint32_t *)(this + 7804) = 0;
  *(uint32_t *)(this + 7808) = 0;  // this+7808〔风格/分支选择〕
  *(uint32_t *)(this + 7812) = 0;  // this+7812〔nSubStateA(推断)〕
  *(uint32_t *)(this + 7816) = 0;  // this+7816〔nSubStateB(推断)〕
  *(uint32_t *)(this + 7820) = 0;  // this+7820〔pInteractSnap(推断)〕
  *(uint32_t *)(this + 7824) = 0;  // this+7824〔nGrabH〕
  *(uint32_t *)(this + 7828) = 0;  // this+7828〔nSubStateD〕
  *(uint32_t *)(this + 7832) = 0;
  *(uint32_t *)(this + 7836) = 1000;
  *(uint32_t *)(this + 7888) = 0;  // this+7888 getter
  *(uint32_t *)(this + 7908) = 0;
  *(uint32_t *)(this + 7912) = 0;
  *(uint32_t *)(this + 7916) = 0;
  *(uint32_t *)(this + 7920) = 0;
  *(uint8_t *)(this + 7924) = 1;
  *(uint8_t *)(this + 7840) = 0;
  *(uint32_t *)(this + 7844) = 0;
  *(uint32_t *)(this + 7848) = 0;
  *(uint32_t *)(this + 7852) = 0;
  *(uint32_t *)(this + 7884) = 0;
  *(uint32_t *)(this + 7928) = 0;
  *(uint8_t *)(this + 7960) = 0;
  *(uint32_t *)(this + 7964) = 0;  // this+7964〔nSkillNo〕
  *(uint32_t *)(this + 7968) = 0;
  *(uint32_t *)(this + 7972) = 0;
  *(uint32_t *)(this + 7976) = 0;
  *(uint32_t *)(this + 7980) = 0;
  *(uint32_t *)(this + 7984) = 0;
  *(uint32_t *)(this + 7988) = 0;
  *(uint8_t *)(this + 7992) = 0;
  *(uint32_t *)(this + 7996) = 0;
  *(uint32_t *)(this + 8000) = 0;
  *(uint32_t *)(this + 8004) = 0;
  *(uint8_t *)(this + 7728) = 0;
  *(uint8_t *)(this + 8052) = 0;
  *(uint32_t *)(this + 8068) = 0;
  *(uint32_t *)(this + 8072) = 0;
  *(uint32_t *)(this + 8080) = 0;
  *(uint32_t *)(this + 8076) = 0;
  *(uint32_t *)(this + 8084) = 0;
  pThis_1FEC = (uint32_t *)(this + 8172);
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
  {
    for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
    {
      *(pThis_1FEC - 10) = 0;
      *pThis_1FEC++ = 0;
    }
  }
  *(uint32_t *)(this + 7428) = 0;
  *(uint32_t *)(this + 8212) = 0;  // this+8212〔pHintText8212〕
  return result;
}



// ============================================================
// SECTION 0x4AF010 — ★★ IRDActiveObject 属性表导入/重算 + 本地玩家操作权限三位一体（0x4AF010-0x4AFEC0）
// ============================================================
// ------------------------------------------------------------
// 0x4AF010 sub_4AF010
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性表整体导入（93 行）。从 a2 结构体读值批量写属性块:
//   ① qmemcpy(this+7432, a2, 0x4F) = 79 字节原样拷贝（原始表区）；
//   ② (a2+4)/10 → this+708 双写（int + cfloat）/1.0；
//   ③ 4 元素循环（a2+16 起 int16，每项 /10）→ this+848 族；
//   ④ 16 元素循环（a2+24 起）→ this+960 族；
//   ⑤ 单项: a2+56/60/62/64/66/68/70/72/74 逐个 /10 换算写入 +1408..+1660 族；
//   ⑥ 最后 vt+676(0) 刷新。**模式 = 服务端属性表 → 客户端防篡改壳写入**（研究第 17 轮闭环）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF010(char *this, int pArg2)  // 函数 sub_4AF010：★★ IRDActiveObject 属性表导入/重算 + 本地玩家操作权限三位一体（0x4AF010 0x4AFEC0）
{
  int v3; // edx
  unsigned int pThis_388; // edi
  int v6; // edx
  bool v7; // zf
  unsigned int pThis_4A0; // edi
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v19; // [esp+10h] [ebp-4h]
  int v20; // [esp+10h] [ebp-4h]
  int16_t *v21; // [esp+1Ch] [ebp+8h]
  int16_t *v22; // [esp+1Ch] [ebp+8h]

  qmemcpy(this + 7432, (const void *)pArg2, 0x4Fu);  // 调 内存块拷贝(内联展开)
  sub_41A590((unsigned int)(this + 708), *(uint32_t *)(pArg2 + 4) / 0xAu, *(uint32_t *)(pArg2 + 4) / 0xAu);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 722), v3, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_388 = (unsigned int)(this + 904);
  v21 = (int16_t *)(pArg2 + 16);  // pArg2+16〔nChannelTypeSel(推断)〕
  v19 = 4;
  do
  {
    sub_41A590(pThis_388 - 56, (int)((uint64_t)(1717986919LL * *v21) >> 32) >> 2, *v21 / 10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pThis_388, v6, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_388 += 14;
    v7 = v19 == 1;
    ++v21;
    --v19;
  }
  while ( !v7 );
  pThis_4A0 = (unsigned int)(this + 1184);
  v22 = (int16_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
  v20 = 16;
  do
  {
    sub_41A590(pThis_4A0 - 224, (int)((uint64_t)(1717986919LL * *v22) >> 32) >> 2, *v22 / 10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pThis_4A0, 1065353216, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_4A0 += 14;
    v7 = v20 == 1;
    ++v22;
    --v20;
  }
  while ( !v7 );
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1408),
    (int)((uint64_t)(1717986919LL * *(int *)(pArg2 + 56)) >> 32) >> 2,
    *(uint32_t *)(pArg2 + 56) / 10);  // pArg2+56〔pCmdVecCap56(推断)〕
  sub_41A590((unsigned int)(this + 1422), v9, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1436),  // this+1436〔nSceneType1436〕
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 60)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 60) / 10);  // pArg2+60〔nFadeValue60(推断)〕
  sub_41A590((unsigned int)(this + 1450), v10, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1464),  // this+1464〔nSelState〕
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 62)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 62) / 10);  // pArg2+62〔bReadyFlagB(推断)〕
  sub_41A590((unsigned int)(this + 1478), v11, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1492), *(uint16_t *)(pArg2 + 64) / 10, *(uint16_t *)(pArg2 + 64) / 10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1506), v12, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1520), *(uint16_t *)(pArg2 + 66) / 10, *(uint16_t *)(pArg2 + 66) / 10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1534), v13, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1548), *(uint16_t *)(pArg2 + 68) / 10, *(uint16_t *)(pArg2 + 68) / 10);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 1562), v14, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1576),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 70)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 70) / 10);
  sub_41A590((unsigned int)(this + 1590), v15, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1604),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 72)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 72) / 10);  // pArg2+72〔nSnapshot72(推断)〕
  sub_41A590((unsigned int)(this + 1618), v16, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 1660),
    (int)((uint64_t)(1717986919LL * *(int *)(pArg2 + 74)) >> 32) >> 2,
    *(uint32_t *)(pArg2 + 74) / 10);  // pArg2+74〔bResetB74(推断)〕
  sub_41A590((unsigned int)(this + 1674), v17, 1065353216);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
}



// ------------------------------------------------------------
// 0x4AF330 sub_4AF330
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性重算 + 广播（vmt 链）。
//   ① sub_432FD0((*v3), 2) 取系数 v4；(dword_8F7A24+12) 是当前场景/频道类型，
//      非 4/6 时 v6 = this+7510（本对象自定义值），否则 v6 = 100；
//   ② this+7432 的 int × v4 × 0.1 → +680（双写）；
//   ③ v6 × this+7440/7442/7444/7446（4 个 int16） / 1000 → +736/+772/+808/+844（四属性）；
//   ④ vt+676(0) 刷新；⑤ a2 非 0 时: vt+740 + vt+732、vt+756 + vt+748 两组百分比应用。
//   【推断】这是"属性表 → 实际战斗数值"的换算器（/10 与 /1000 两类比例）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF330(unsigned int *this, char pszArg2)  // 实现：(推断)这是属性表 → 实际战斗数值的换算器（/10 与 /1000 两类比例）
{
  uint32_t *v3; // eax
  double v4; // st7
  int v5; // eax
  int pThis_1D56; // edi
  uint64_t fld_e1858; // rax
  char result; // al
  unsigned int v9; // ebx
  int v10; // eax
  unsigned int v11; // ebx
  int v12; // eax

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
  v4 = sub_432FD0(*v3, 2);  // 调 场景平衡系数分发
  v5 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
  pThis_1D56 = 100;
  if ( v5 != 4 && v5 != 6 )  // 若 v5 != 4 与/或 v5 != 6
    pThis_1D56 = *((uint8_t *)this + 7510);  // this+7510 本对象自定义值
  fld_e1858 = (uint64_t)((double)*(this + 1858) * v4 * 0.1);
  sub_41A590((unsigned int)(this + 170), SHIDWORD(fld_e1858), fld_e1858);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 184),  // this+184 单目标标志
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3720)) >> 32) >> 6,  // pThis_1D56=this+7510 本对象自定义值
    pThis_1D56 * *((uint16_t *)this + 3720) / 1000);  // pThis_1D56=this+7510 本对象自定义值
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 191),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3721)) >> 32) >> 6,  // pThis_1D56=this+7510 本对象自定义值
    pThis_1D56 * *((uint16_t *)this + 3721) / 1000);  // pThis_1D56=this+7510 本对象自定义值
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 198),  // this+198〔field_00C6〕
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3722)) >> 32) >> 6,  // pThis_1D56=this+7510 本对象自定义值
    pThis_1D56 * *((uint16_t *)this + 3722) / 1000);  // pThis_1D56=this+7510 本对象自定义值
  sub_41A590(  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
    (unsigned int)(this + 205),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3723)) >> 32) >> 6,  // pThis_1D56=this+7510 本对象自定义值
    pThis_1D56 * *((uint16_t *)this + 3723) / 1000);  // pThis_1D56=this+7510 本对象自定义值
  (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 676))(this, 0);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    v9 = *this;
    v10 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, int))(*this + 740))(this, 0, 1);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    (*(void (/*thiscall*/ **)(unsigned int *, int))(v9 + 732))(this, pThis_1D56 * v10 / 100);  // 调用虚函数（虚表槽 +732）
    v11 = *this;
    v12 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 756))(this, 1);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
    return (*(int (/*thiscall*/ **)(unsigned int *, int))(v11 + 748))(this, pThis_1D56 * v12 / 100);  // 调用虚函数（虚表槽 +748）【推断: [RTTI: IRDActiveObject__vmt2EC ·…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF4B0 sub_4AF4B0
// ------------------------------------------------------------
// 【解读】
//   【推断】两态切换外壳（a2 = 0/非0）: 每态里若有动画对象则先 sub_4938F0 同步帧，
//   取 anim+95 字节作参数、vt+792(this,9) 取值、调 sub_432600(态, a3, a4, this, v, 1, b) ——
//   对偶形态的成对触发（进入/退出）。sub_58E750 是基类同名实现（前后各调一次）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF4B0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：对偶形态的成对触发（进入/退出）。sub_58E750 是基类同名实现（前后各调一次）
{
  int pAnimObj; // edi  | +0x0078 → 动画对象指针（IRDCharacter；va=00499020）
  int v7; // eax
  char result; // al
  int pAnimObj_; // edi  | +0x0078 → 动画对象指针（IRDCharacter；va=00499020）
  int v10; // eax
  int v11; // [esp-4h] [ebp-10h]
  int v12; // [esp-4h] [ebp-10h]

  if ( (uint8_t)nArg2 == 0 )
  {
    pAnimObj = *(this + 30);  // this+120 = 动画对象指针
    if ( pAnimObj != 0 )  // fld_e30=this+120 pAnimObj
    {
      if ( *(uint32_t *)(pAnimObj + 148) == -1 )  // fld_e30=this+120 pAnimObj
        sub_4938F0(*(this + 30));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v11 = *(uint8_t *)(pAnimObj + 95);  // fld_e30=this+120 pAnimObj
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);  // 调用虚函数（虚表槽 +792）
      sub_432600(0, nArg3, nArg4, this, v7, 1, v11);  // 调 称号气球触发包装
    }
  }
  sub_58E750(this, nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt148】
  result = nArg2;
  if ( (uint8_t)nArg2 != 0 )
  {
    pAnimObj_ = *(this + 30);  // this+120 = 动画对象指针
    if ( pAnimObj_ != 0 )  // fld_e302=this+120 pAnimObj
    {
      if ( *(uint32_t *)(pAnimObj_ + 148) == -1 )  // fld_e302=this+120 pAnimObj
        sub_4938F0(*(this + 30));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v12 = *(uint8_t *)(pAnimObj_ + 95);  // fld_e302=this+120 pAnimObj
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);  // 调用虚函数（虚表槽 +792）
      return sub_432600(1, nArg3, nArg4, this, v10, 1, v12);  // 调 称号气球触发包装
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF560 sub_4AF560
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 双结构体差异应用（stdcall, a1=上下文, a2/a3=新旧两份表）。
//   对 a2/a3 逐字段: 双方非空时 sub_494240(a1, a3.field) —— **只对"新表存在的项"做提交**。
//   布局: a3+0..+16 与 a2+1..+4×4（交错 4 元素循环）、+36/+40/+44/+48 四尾项。
//   【推断】装备/外观部件表差分应用（与 docs/15 的 vmt2B4 组件槽结构 9 单指针+数组段一致）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4AF560(int nArg1, uint32_t *pArg2, char *pszArg3)  // 实现：(推断)装备/外观部件表差分应用（与 docs/15 的 vmt2B4 组件槽结构 9 单指针+数组段一致）
{
  uint32_t *v3; // edi
  uint32_t *v4; // esi
  int v5; // ebx
  uint32_t *result; // eax
  int i; // [esp+Ch] [ebp-4h]

  if ( *pArg2 != 0 && *(uint32_t *)pszArg3 != 0 )
    sub_494240(nArg1, *(uint32_t *)pszArg3);  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  v3 = pszArg3 + 20;
  v4 = pArg2 + 1;
  v5 = pszArg3 - (char *)pArg2;
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    if ( *v4 != 0 && *(uint32_t *)((char *)v4 + v5) != 0 )
      sub_494240(nArg1, *(uint32_t *)((char *)v4 + v5));  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
    if ( v4[4] != 0 && *v3 != 0 )
      sub_494240(nArg1, *v3);  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
    ++v4;
    ++v3;
  }
  if ( pArg2[9] != 0 && *((uint32_t *)pszArg3 + 9) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 9));  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  if ( pArg2[10] != 0 && *((uint32_t *)pszArg3 + 10) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 10));  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  if ( pArg2[11] != 0 && *((uint32_t *)pszArg3 + 11) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 11));  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  result = pArg2;
  if ( pArg2[12] != 0 )
  {
    result = *((uint32_t **)pszArg3 + 12);
    if ( result != nullptr )  // 若 result 有效（非空）
      return (uint32_t *)sub_494240(nArg1, *((uint32_t *)pszArg3 + 12));  // 调 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF650 sub_4AF650
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 0x4AF560 的逆操作 —— 双结构体差异卸载（sub_492980 释放旧资源）。
//   同样 4 元素交错循环 + +36..+48 尾项 —— 挂载/卸载对称对。
// ------------------------------------------------------------
void **/*stdcall*/ sub_4AF650(void ****pArg1, void **pArg2)  // 实现：同样 4 元素交错循环 + +36..+48 尾项 —— 挂载/卸载对称对
{
  void **v2; // edi
  void ****v3; // esi
  char *v4; // ebx
  void ***v5; // ecx
  void ***v6; // ecx
  void ***v7; // ecx
  void **result; // eax
  void ***v9; // ecx
  void ***v10; // ecx
  int i; // [esp+Ch] [ebp-4h]

  if ( *pArg1 != nullptr && *pArg2 != nullptr )
    sub_492980(*pArg1, *pArg2);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
  v2 = pArg2 + 5;
  v3 = pArg1 + 1;
  v4 = (char *)((char *)pArg2 - (char *)pArg1);
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    if ( *v3 != nullptr && *(void ****)((char *)v3 + (uint32_t)v4) != nullptr )
      sub_492980(*v3, *(void **)((char *)v3 + (uint32_t)v4));  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
    v5 = v3[4];
    if ( v5 != nullptr && *v2 != nullptr )
      sub_492980(v5, *v2);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
    ++v3;
    ++v2;
  }
  v6 = pArg1[9];
  if ( v6 != nullptr && pArg2[9] != nullptr )
    sub_492980(v6, pArg2[9]);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
  v7 = pArg1[10];
  if ( v7 != nullptr && pArg2[10] != nullptr )
    sub_492980(v7, pArg2[10]);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
  result = (void **)pArg1;
  v9 = pArg1[11];
  if ( v9 != nullptr )  // 若 v9 有效（非空）
  {
    result = (void **)pArg2[11];
    if ( result != nullptr )  // 若 result 有效（非空）
      result = sub_492980(v9, pArg2[11]);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
  }
  v10 = pArg1[12];
  if ( v10 != nullptr )  // 若 v10 有效（非空）
  {
    result = (void **)pArg2[12];
    if ( result != nullptr )  // 若 result 有效（非空）
      return sub_492980(v10, pArg2[12]);  // 调 子链节点按对象指针摘除（组件槽卸载/释放）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF720 sub_4AF720
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 高亮目标切换。this+7892(1973*4=7892) 保存当前高亮对象指针；
//   v2 = this+29 非 0 时 sub_45EAC0(this) 求新对象；不同则: 旧对象 +976 标志清 0 且
//   调其 vt+284(0, -16715521, 0, 1)（-16715521 = 0xFF00FFFF 颜色值），
//   新对象 +976 置 1 且调 vt+284(1, 颜色, 0, 1)。**这是"选中高亮描边"的着色调用**。
// ------------------------------------------------------------
void /*thiscall*/ sub_4AF720(uint32_t *this)  // 实现：新对象 +976 置 1 且调 vt+284(1, 颜色, 0, 1)。**这是选中高亮描边的着色调用**
{
  int *v2; // esi
  int *fld_e1972; // ecx
  int v4; // eax
  int v5; // edx

  v2 = nullptr;
  if ( *(this + 29) != 0 )  // this+116〔会话上下文〕
    v2 = (int *)sub_45EAC0(this);  // 调 拖拽落点目标搜索（·+56 表，48x36 框）
  fld_e1972 = (int *)*(this + 1972);
  if ( fld_e1972 != v2 )
  {
    if ( fld_e1972 != nullptr )  // 若 fld_e1972 有效（非空）
    {
      v4 = *fld_e1972;
      *((uint8_t *)fld_e1972 + 976) = 0;
      (*(void (/*stdcall*/ **)(uint32_t, int, uint32_t, int))(v4 + 284))(0, -16715521, 0, 1);  // 调用虚函数（虚表槽 +284）【推断: 四字段批量写（+248..+260）】
    }
    if ( v2 != nullptr )  // 若 v2 有效（非空）
    {
      v5 = *v2;
      *((uint8_t *)v2 + 976) = 1;
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int))(v5 + 284))(v2, 1, -16715521, 0, 1);  // 调用虚函数（虚表槽 +284）【推断: 四字段批量写（+248..+260）】
    }
    *(this + 1972) = v2;
  }
}



// ------------------------------------------------------------
// 0x4AF790 sub_4AF790
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 状态覆写批量扫描。对 190 个索引: 若 vt+1160(i) 返回对象的 +124 == 1，
//   则 vt+1140(i) 取新值 → vt+1304(this, i, 值) 覆写；最后 vt+676(2) 刷新。
//   **190 = 状态槽总数候选**（与 17 异常状态槽不同层）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF790(int *this)  // 实现：**190 = 状态槽总数候选**（与 17 异常状态槽不同层）
{
  int i; // edi
  int v3; // ebx
  int v4; // eax

  for ( i = 0; i < 190; ++i )  // 循环：i 从 0 递增到 190
  {
    if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, i) != 0  // 调用虚函数（虚表槽 +1160）
      && *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, i) + 124) == 1 )  // 调用虚函数（虚表槽 +1160）
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, i);  // 调用虚函数（虚表槽 +1140）
      (*(void (/*thiscall*/ **)(int *, int, int))(v3 + 1304))(this, i, v4);  // 调用虚函数（虚表槽 +1304）
    }
  }
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 676))(this, 2);  // 调用虚函数（虚表槽 +676）【推断: 观察者/状态的对象绑定与解绑（a2 = 0/1/2）】
}



// ------------------------------------------------------------
// 0x4AF7F0 sub_4AF7F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 按场景类型发出 UI 通知。vt+308 本地玩家判定通过后按 (dword_8F7A24+12):
//   场景 3 → 事件 43; 场景 4 → 事件 58; 场景 6 → 事件 95 + sub_48FCE0(*(this+8016)) 一字节载荷。
//   sub_423200/sub_423290/sub_423380 = UI 消息构造（类型/载荷/发送，见 0x4AF9A0 同族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF7F0(int *this)  // 实现：sub_423200/sub_423290/sub_423380 = UI 消息构造（类型/载荷/发送，见 0x4AF9A0 同族）
{
  int result; // eax
  int fld_e2004; // eax
  uint8_t v4[4]; // [esp+4h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
    switch ( result )  // 按 result 分派
    {
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        sub_423200(dword_8F7B08, 43);  // 【发送网络包API】
        return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        sub_423200(dword_8F7B08, 58);  // 【发送网络包API】
        return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        sub_423200(dword_8F7B08, 95);  // 【发送网络包API】
        fld_e2004 = sub_48FCE0(*(this + 2004));  // 调 座位下标按 id 查找（表 dword_99FF08）
        if ( fld_e2004 == -1 )
          LOBYTE(fld_e2004) = -1;  // 调 取 16 位值低 8 位
        v4[0] = fld_e2004;
        sub_423290(v4, 1);  // 调 写 4B 长度
        return sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      default:
        break;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF8B0 sub_4AF8B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 观察者槽差分读: (this[a2+1617] == this[a2+1879]) ? 0 : 前者。
//   **+6468 与 +7516 是两套 18 槽表（1617 与 1879 = 相差 262 DWORD = 1048 字节）**，
//   本函数返回"两表不同则取前者"—— 疑为"当前值 vs 基准值"的差分比较器。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF8B0(uint32_t *this, int pArg2)  // 实现：本函数返回两表不同则取前者—— 疑为当前值 vs 基准值的差分比较器
{
  return *(this + pArg2 + 1617) == *(this + pArg2 + 1879) ? 0 : *(this + pArg2 + 1617);
}



// ------------------------------------------------------------
// 0x4AF8E0 sub_4AF8E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 状态槽的惰性初始化（vmt 覆写）。先调基类 sub_4D4CE0(this, a2)；
//   若 this+512 == 4: 用 vt+1176/vt+1180 重新取两值；若 this+520 == -1: 用 vt+1184 取初值；
//   若 this+524 == -1082130432（-4.0f 位模式）: vt+1188 取浮点初值；
//   最后: this+520 > 0 时用 (2.0 − 属性块+1292 的浮点) × this+520 修正 ——
//   **防篡改壳（+1292）参与状态时长的缩放**。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF8E0(int this, int nArg2)  // 实现：**防篡改壳（+1292）参与状态时长的缩放**
{
  uint64_t nAbilityDur_; // rax  | +0x0208 → ★能力槽时长/基础值（IRDCharacter；va=004AF8E0）
  int pThis_2A0; // eax

  sub_4D4CE0((char *)this, nArg2);  // 调 参见 0x4D4A20 尾参 this+97*4），尾调 sub_53F7A0(this+388) 做该上下文的收束并返回
  if ( *(uint32_t *)(this + 512) == 4 )  // this+512〔nAbilityId〕
  {
    *(uint32_t *)(this + 512) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1176))(this);  // 调用虚函数（虚表槽 +1176）
    *(uint8_t *)(this + 516) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1180))(this);  // 调用虚函数（虚表槽 +1180）
  }
  if ( *(uint32_t *)(this + 520) == -1 )  // this+520〔nAbilityDur〕
    *(uint32_t *)(this + 520) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1184))(this);  // 调用虚函数（虚表槽 +1184）
  if ( *(uint32_t *)(this + 524) == -1082130432 )  // this+524〔fAbilityScale(推断)〕
    *(float *)(this + 524) = ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)this + 1188))(this);  // 调用虚函数（虚表槽 +1188）
  LODWORD(nAbilityDur_) = *(uint32_t *)(this + 520);  // 调 取 64 位值低 32 位
  if ( (int)nAbilityDur_ > 0 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
    nAbilityDur_ = (uint64_t)((2.0 - COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1292))) * (double)*(int *)(this + 520));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
    *(uint32_t *)(this + 520) = nAbilityDur_;  // this+520〔nAbilityDur〕
  }
  return nAbilityDur_;  // | +0x0208 → ★能力槽时长/基础值（IRDCharacter；va=004AF8E0）
}



// ------------------------------------------------------------
// 0x4AF9A0 sub_4AF9A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ UI 包构造: 事件 50。流程: vt+308 玩家判定 → vt+792(this, a2) 取对象 →
//   发事件 50 → 载荷依次: vt+120(x, 2B)、vt+124(y, 2B)、字节 3(1B)、a2(2B)、1(4B) → 发送。
//   **双坐标 + 类型 + 目标 ID 的纯坐标型通知**（疑似"标记/路径点"）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF9A0(void *this, int nArg2)  // 实现：**双坐标 + 类型 + 目标 ID 的纯坐标型通知**（疑似标记/路径点）
{
  char result; // al
  int nArg22; // ebx

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nArg22 = nArg2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2) != 0 )  // 调用虚函数（虚表槽 +792）
    {
      sub_423200(dword_8F7B08, 50);  // 【发送网络包API】
      nArg2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      nArg2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);  // 调用虚函数（虚表槽 +124）
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      HIBYTE(nArg2) = 3;  // 调 取 16 位值高 8 位
      sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
      nArg2 = nArg22;
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      nArg2 = 1;
      sub_423290(&nArg2, 4);  // 调 写 4B 长度
      sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      return 1;  // 返回 1(成功)
    }
    else
    {
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFA70 sub_4AFA70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ UI 包构造: 事件 18（与 0x4AF9A0 同族但载荷布局不同）:
//   字节 3(1B) + 字节 1(1B) + a3(2B) + a2(2B) + 1(4B)。**a3 是新增参数**。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AFA70(void *this, int nArg2, int nArg3)  // 实现：字节 3(1B) + 字节 1(1B) + a3(2B) + a2(2B) + 1(4B)。**a3 是新增参数**
{
  char result; // al
  int nArg22; // edi

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nArg22 = nArg2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2) != 0 )  // 调用虚函数（虚表槽 +792）
    {
      sub_423200(dword_8F7B08, 18);  // 【发送网络包API】
      HIBYTE(nArg2) = 3;  // 调 取 16 位值高 8 位
      sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
      HIBYTE(nArg2) = 1;  // 调 取 16 位值高 8 位
      sub_423290((char *)&nArg2 + 3, 1);  // 调 写 4B 长度
      nArg2 = nArg3;
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      nArg2 = nArg22;
      sub_423290(&nArg2, 2);  // 调 写 4B 长度
      nArg2 = 1;
      sub_423290(&nArg2, 4);  // 调 写 4B 长度
      sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
      return 1;  // 返回 1(成功)
    }
    else
    {
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFB30 sub_4AFB30
// ------------------------------------------------------------
// 【解读】
//   【推断】攻击反应前置钩: 若 vt+724 == 0（非冻结）且 vt+308 本地玩家且 this+404 非 0，
//   先 vt+1104(this, 8)；再转发基类 sub_4D6D90（=IRDActiveObject_vmt1F4 攻方完整反应）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFB30(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 实现：先 vt+1104(this, 8)；再转发基类 sub_4D6D90（=IRDActiveObject_vmt1F4 攻方完整反应…
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
    && *((uint8_t *)this + 404) != 0 )  // CNTitan 删除析构壳
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 8);  // 调用虚函数（虚表槽 +1104）
  }
  return sub_4D6D90(this, uArg2, nArg3, nArg4);  // 【攻方完整反应 vt+500（§8 双向卡肉入口）】
}



// ------------------------------------------------------------
// 0x4AFB80 sub_4AFB80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 随机触发状态: 五重条件（this+7984 对象非空且其 vt+80 通过 + vt+1000 通过 +
//   a4==0 + this+7988 浮点 ×100 > rand(87723146,10000)）→ this+7992 = 1。
//   rand 种子 87723146 —— 第二处固定随机源（与 0x4A58F0 的 88771231 并列）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFB80(uint32_t *this, int nArg2, int nArg3, char pszArg4)  // 实现：rand 种子 87723146 —— 第二处固定随机源（与 0x4A58F0 的 88771231 并列）
{
  int fld_e1996; // ecx

  fld_e1996 = *(this + 1996);
  if ( fld_e1996 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1996 + 80))(fld_e1996) != 0  // 调用虚函数（虚表槽 +80）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1000))(this) != 0  // 调用虚函数（虚表槽 +1000）
    && pszArg4 == 0
    && *((float *)this + 1997) * 100.0 > (double)(int)sub_445870(87723146, 10000) )  // 调 槽表随机数
  {
    *((uint8_t *)this + 7992) = 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4AFBF0 sub_4AFBF0
// ------------------------------------------------------------
// 【解读】
//   【推断】受击反应包装: 调 sub_4D5A60(this, a2, a3)（0x4D5A60 = IRDActiveObject vmt288）；
//   结果 != 3 且 this+7992 置位 → 返回 1（强制生效）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFBF0(uint8_t *this, uint32_t *uArg2, int nArg3)  // 实现：结果 != 3 且 this+7992 置位 → 返回 1（强制生效）
{
  int result; // eax

  result = sub_4D5A60(this, uArg2, nArg3);  // 调 ★ 伤害类型/命中类型计算 vt+648（研究 §1.2 定案 6 版本之一）
  if ( result != 3 && *(this + 7992) != 0 )
    return 1;  // 返回 1(成功)
  return result;
}



// ------------------------------------------------------------
// 0x4AFC30 sub_4AFC30
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4AFBF0 的配对: 清 this+7992 后调 sub_4D4A80（IRDActiveObject_vmt204 观察者广播）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC30(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：(推断)0x4AFBF0 的配对: 清 this+7992 后调 sub_4D4A80（IRDActiveObject_vmt204…
{
  *((uint8_t *)this + 7992) = 0;
  return sub_4D4A80(this, nArg2, nArg3, nArg4);  // 调 受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
}



// ------------------------------------------------------------
// 0x4AFC40 sub_4AFC40
// ------------------------------------------------------------
// 【解读】
//   【推断】vt+308 玩家判定 → vt+792(this, a2) 取对象 → 调其 vt+268。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC40(void *this, int nArg2)  // 实现：(推断)vt+308 玩家判定 → vt+792(this, a2) 取对象 → 调其 vt+268
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2);  // 调用虚函数（虚表槽 +792）
    if ( result != 0 )  // 若结果非 0（成功）
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 268))(result);  // 调用虚函数（虚表槽 +268）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFC80 sub_4AFC80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 血量低于阈值时的场景分支。若 a2 < vt+736():
//   场景 4 且 (dword_8F7A24+32)+36 == 3 → sub_4527A0(vt+1216 值, 差值)（疑为镜头/提示）；
//   场景 6 → sub_42B510((dword_8F7A24+40))；最后转发 sub_4D5900（vmt2DC）。
//   **这是"濒死镜头"或"低血提示"的触发点候选。**
// ------------------------------------------------------------
char /*thiscall*/ sub_4AFC80(uint32_t *this, int nArg2, int nArg3, char pszArg4)  // 实现：**这是濒死镜头或低血提示的触发点候选。**
{
  int v5; // ecx
  int v6; // eax
  int v8; // [esp-8h] [ebp-10h]

  if ( nArg2 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) )  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
    if ( v5 == 4 && *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) == 3 )  // dword_8F7A24 = 当前场景状态对象
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) - nArg2;  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1216))(this);  // 调用虚函数（虚表槽 +1216）
      sub_4527A0(v6, v8);  // 调 计数累加
    }
    else if ( v5 == 6 )
    {
      sub_42B510(*(uint32_t *)(dword_8F7A24 + 40));  // 调 场景类别判定（+32 属 2/3/4）
    }
  }
  return sub_4D5900(this, nArg2, nArg3, pszArg4);  // 调 HP setter（落地）
}



// ------------------------------------------------------------
// 0x4AFD00 sub_4AFD00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 可行动判定: vt+1196 == 0 且 vt+724 == 0（未冻结），
//   且大状态(+6556) ∈ {0, 11} 或 (== 8 且 vt+1140(171) > 0) → true。
//   **大状态 0/11/8 是"可自由行动"状态集**（0=待机、11=??、8=?? 且带 171 号条件）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AFD00(uint32_t *this)  // 实现：**大状态 0/11/8 是可自由行动状态集**（0=待机、11=??、8=?? 且带 171 号条件）
{
  int fld_e1639; // eax
  bool result; // al

  result = false;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1196))(this) == 0  // 调用虚函数（虚表槽 +1196）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
  {
    fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
    if ( fld_e1639 == 0 || fld_e1639 == 11 || fld_e1639 == 8 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 171) > 0 )  // 调用虚函数（虚表槽 +1140）
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFD50 sub_4AFD50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 收招/起身触发: vt+308 判定后，v4 = (this+7730 != 0) && a2 != 0 && vt+1140(170) > 0；
//   先 vt+1160(this, 169) 做一次查询（忽略结果），再 sub_47E440(v4)。
//   **条件编号 169/170 与 0x4AFEC0 的 169/175/176/180 同族 —— 动作抑制条件集**。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFD50(uint8_t *this, char pszArg2)  // 实现：**条件编号 169/170 与 0x4AFEC0 的 169/175/176/180 同族 —— 动作抑制条件集**
{
  int result; // eax
  bool fld_e7730; // al
  char fld_e77302; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调用虚函数（虚表槽 +308）【推断: 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8…】
  if ( (uint8_t)result != 0 )
  {
    fld_e7730 = *(this + 7730) != 0 && pszArg2 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1140))(this, 170) > 0;  // 调用虚函数（虚表槽 +1140）
    fld_e77302 = fld_e7730;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 169);  // 调用虚函数（虚表槽 +1160）
    return sub_47E440(fld_e77302);  // 返回 条目可见性旗标联动(推断)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFDB0 sub_4AFDB0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 18 观察者 vt+144 广播 + 本地玩家的 vt+290/vt+324 链。
//   ① vt+77（=0x4C 字节，vt+308 玩家判定）通过 → 对 18 个观察者槽逐个调 vt+144(&a2, &a3)；
//   ② 若 this == dword_8F7C04（本地玩家）→ vt+290(this, a2) 取对象，其 +376 非 0 时
//   调 vt+324(this, a2, a3)。**与 docs/15 的 vmt310/324 装备链呼应。**
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4AFDB0(uint8_t **this, int nArg2, int nArg3)  // 函数定义: 基类发射后
{
  uint8_t *result; // eax
  uint8_t **pThis_651; // esi
  int i; // ebx

  result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **))*this + 77))(this);  // 调用虚函数（虚表槽 +77）
  if ( (uint8_t)result != 0 )
  {
    pThis_651 = this + 1617;
    for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
    {
      result = *pThis_651;
      if ( *pThis_651 != nullptr )
        result = (uint8_t *)(*(int (/*stdcall*/ **)(int *, int *))(*(uint32_t *)result + 144))(&nArg2, &nArg3);  // 调用虚函数（虚表槽 +144）【推断: 设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查…】
      ++pThis_651;
    }
  }
  if ( (uint8_t **)dword_8F7C04 == this )  // dword_8F7C04 = 本地玩家对象
  {
    result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int))*this + 290))(this, nArg2);  // 调用虚函数（虚表槽 +290）
    if ( result[376] != 0 )
      return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int, int))*this + 324))(this, nArg2, nArg3);  // 调用虚函数（虚表槽 +324）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFE30 sub_4AFE30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 三点标尺计算（a3 = 索引 0..N）。this+7188/+7192/+7196 = 三值:
//   a2 − dword_9B7410[a3]、dword_9B7414[a3] − 基准、a2。a3==1 时基准 = 0。
//   **dword_9B7410/9B7414 是两张全局标尺表（按 a3 索引）—— 血条/进度条刻度候选。**
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFE30(uint32_t *this, int nArg2, int nArg3)  // 实现：**dword_9B7410/9B7414 是两张全局标尺表（按 a3 索引）—— 血条/进度条刻度候选。**
{
  int result; // eax

  if ( nArg3 == 1 )
    result = 0;
  else
    result = dword_9B7410[nArg3];
  *(this + 1797) = nArg2 - result;
  *(this + 1798) = dword_9B7414[nArg3] - result;
  *(this + 1799) = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x4AFE70 sub_4AFE70
// ------------------------------------------------------------
// 【解读】
//   【推断】三槽写入（+7200/+7208/+7204）—— 与 0x4AFE30 三元组同区。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFE70(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：(推断)三槽写入（+7200/+7208/+7204）—— 与 0x4AFE30 三元组同区
{
  *(this + 1800) = nArg2;
  *(this + 1802) = nArg3;
  *(this + 1801) = nArg4;
  return nArg4;
}



// ------------------------------------------------------------
// 0x4AFEA0 sub_4AFEA0
// ------------------------------------------------------------
// 【解读】
//   【推断】写 this+7730 标志后调 vt+1316() —— 状态变更通知（0x4AFEC0 会读 +7730）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFEA0(uint8_t *this, char pszArg2)  // 实现：(推断)写 this+7730 标志后调 vt+1316() —— 状态变更通知（0x4AFEC0 会读 +7730）
{
  int v2; // edx

  v2 = *(uint32_t *)this;
  *(this + 7730) = pszArg2;  // this+7730 子类使能字节
  return (*(int (**)(void))(v2 + 1316))();  // 调用虚函数（虚表槽 +1316）
}



// ------------------------------------------------------------
// 0x4AFEC0 sub_4AFEC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★★ 全局 UI/表现标志同步器（仅当 this == dword_8F7C04 本地玩家）。
//   置全局字节矩阵: byte_9A0358/9A0384/9A03B0/9A03DC/9A0408/9A0434/9A0460 ——
//   前四个初值 0，后三个 = (大状态 != 5)。
//   再看 this+7730 分两支: 非 0 → 按大状态(+6556) switch:
//     case 0 → 9A03B0=1, 9A03DC=1（落入 LABEL_5: 9A0358=1, 9A0384=1 + 关 169/175/176/180 四条件）;
//     case 6 → 读 +6892/+6896/+6900 三级联 + this+6988 → 9A0358 = (6988==0);
//     case 8 → 9A0358=1, 9A0384=1 + vt+1328(this,1);
//     case 11 → LABEL_5 全开;
//   否则（+7730 == 0）→ 大状态非 0 时 9A0384 = (状态==11)，为 0 时 9A03B0/9A03DC/9A0384 全置 1。
//   **这七个全局字节是"UI 元素可见性/可交互性"总闸（本地玩家专属）—— 与 0x4AFD00/FD50/FEC0
//    构成"本地玩家操作权限"三位一体。**
// ------------------------------------------------------------
char /*thiscall*/ sub_4AFEC0(uint32_t *this)  // 实现：构成本地玩家操作权限三位一体。**
{
  int fld_e1639; // eax
  int fld_e16392; // esi

  LOBYTE(fld_e1639) = dword_8F7C04;  // 调 取 16 位值低 8 位
  if ( (uint32_t *)dword_8F7C04 == this )  // dword_8F7C04 = 本地玩家对象
  {
    sub_483DF0((int *)dword_8F853C, 0);  // 调 遍历技能槽对非空项调用 ·sub_47E440
    byte_9A0358 = 0;
    byte_9A0384 = 0;
    byte_9A03B0 = 0;
    byte_9A03DC = 0;
    byte_9A0408 = *(this + 1639) != 5;  // this+6556 = 主状态镜像
    byte_9A0434 = *(this + 1639) != 5;  // this+6556 = 主状态镜像
    byte_9A0460 = *(this + 1639) != 5;  // this+6556 = 主状态镜像
    LOBYTE(fld_e1639) = *((uint8_t *)this + 7730);  // 调 取 16 位值低 8 位
    if ( (uint8_t)fld_e1639 != 0 )
    {
      fld_e1639 = *(this + 1639);  // this+6556 = 主状态镜像
      switch ( fld_e1639 )  // 按 fld_e1639 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          byte_9A03B0 = 1;
          byte_9A03DC = 1;
          goto LABEL_5;
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          fld_e1639 = *(this + 1723);  // this+6892〔nSkillCtxVal〕
          if ( fld_e1639 == 1 )  // fld_e1639=this+6892 nSkillCtxVal
          {
            fld_e1639 = *(this + 1724);  // this+6896〔nTickCount〕
            if ( fld_e1639 < *(this + 1725) )  // fld_e1639=this+6896 nTickCount
            {
              LOBYTE(fld_e1639) = *((uint8_t *)this + 6988);  // 调 取 16 位值低 8 位
              byte_9A0358 = (uint8_t)fld_e1639 == 0;  // fld_e1639=this+6896 nTickCount
            }
          }
          break;
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1328))(this, 1);  // 调用虚函数（虚表槽 +1328）
          break;
        case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
LABEL_5:
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 169);  // 调用虚函数（虚表槽 +1160）
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 175);  // 调用虚函数（虚表槽 +1160）
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 176);  // 调用虚函数（虚表槽 +1160）
          sub_47E440(1);  // 调 条目可见性旗标联动(推断)
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 180);  // 调用虚函数（虚表槽 +1160）
          LOBYTE(fld_e1639) = sub_47E440(1);  // 调 取 16 位值低 8 位
          break;
        default:
          return fld_e1639;  // fld_e1639=this+6896 nTickCount
      }
    }
    else
    {
      fld_e16392 = *(this + 1639);  // this+6556 = 主状态镜像
      if ( fld_e16392 != 0 )  // fld_e16392=this+6556 主状态镜像
      {
        byte_9A0384 = fld_e16392 == 11;  // fld_e16392=this+6556 主状态镜像
      }
      else
      {
        byte_9A03B0 = 1;
        byte_9A03DC = 1;
        byte_9A0384 = 1;
      }
    }
  }
  return fld_e1639;  // fld_e1639=this+6896 nTickCount
}


