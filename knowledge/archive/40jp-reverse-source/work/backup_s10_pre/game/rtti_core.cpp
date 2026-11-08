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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 49);
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
    *(uint32_t *)pThis_353 = *(this + 1);
    goto LABEL_8;
  }
  pThis_352 = (char *)this + 53;
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 4);
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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 57, 4);
  }
  if ( uArg2 >> 30 == 1 )
  {
    *(uint32_t *)((char *)pThis + 61) = 0;
  }
  else if ( uArg2 >> 30 != 0 )
  {
    *(uint32_t *)((char *)pThis + 61) = pThis[3];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 61, 4);
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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 65, 4);
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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 69, 4);
  }
  v10 = ((uArg2 >> 20) & 0x3F) >> 4;
  if ( v10 == 1 )
  {
    *(uint32_t *)((char *)pThis + 73) = 0;
  }
  else if ( v10 != 0 )
  {
    *(uint32_t *)((char *)pThis + 73) = pThis[6];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 73, 4);
  }
  if ( (uint16_t)uArg2 >> 14 == 1 )
  {
    *(uint32_t *)((char *)pThis + 77) = 0;
  }
  else if ( (uint16_t)uArg2 >> 14 != 0 )
  {
    *(uint32_t *)((char *)pThis + 77) = pThis[7];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 77, 4);
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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 81, 4);
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
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 85, 4);
  }
  v13 = BYTE1(uArg2) & 3;
  if ( v13 == 3 )
  {
    *(uint32_t *)((char *)pThis + 89) = -1;
  }
  else if ( v13 == 1 )
  {
    *(uint32_t *)((char *)pThis + 89) = 0;
  }
  else if ( (uArg2 & 0x300) != 0 )
  {
    *(uint32_t *)((char *)pThis + 89) = pThis[10];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 89, 4);
  }
  v14 = (((uArg2 >> 8) & 0x3F) >> 2) & 3;
  if ( v14 == 3 )
  {
    *(uint32_t *)((char *)pThis + 93) = -1;
  }
  else if ( v14 == 1 )
  {
    *(uint32_t *)((char *)pThis + 93) = 0;
  }
  else if ( v14 != 0 )
  {
    *(uint32_t *)((char *)pThis + 93) = pThis[11];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 93, 4);
  }
  v15 = ((uArg2 >> 8) & 0x3F) >> 4;
  if ( v15 == 3 )
  {
    *(uint32_t *)((char *)pThis + 97) = -1;
  }
  else if ( v15 == 1 )
  {
    *(uint32_t *)((char *)pThis + 97) = 0;
  }
  else if ( v15 != 0 )
  {
    *(uint32_t *)((char *)pThis + 97) = pThis[12];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)pThis + 97, 4);
  }
  pThis_35 = (float *)pThis_352;
  *((uint8_t *)pThis + 101) = (uArg2 >> 5) & 7;
LABEL_71:
  result = (uArg2 & 0x10) != 0;
  if ( (uArg2 & 0x10) != 0 )
  {
    qmemcpy(pThis + 1, pThis_35, 0x31u);
  }
  else
  {
    v17 = pThis_35 + 6;
    v18 = (float *)(pThis + 7);
    for ( i = 3; i != 0; --i )
    {
      if ( *(v18 - 6) == *(v17 - 6) )
      {
        *(v18 - 3) = *(v17 - 3);
        *v18 = *v17;
        v18[3] = v17[3];
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
        *(uint32_t *)v18 = v22;
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
    *((uint8_t *)pThis + 52) = result;
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
void /*thiscall*/ sub_4A0550(float *this, int nArg2)
{
  int pThis_9; // eax
  int v5; // eax
  float v6; // [esp+Ch] [ebp+8h]

  pThis_9 = *((uint32_t *)this + 9);
  if ( pThis_9 != 0 || nArg2 == 0 )
  {
    v5 = nArg2 * pThis_9;
    if ( v5 <= 0 )
    {
      v6 = sqrt((double)(-2 * v5));
      if ( nArg2 < 0 )
        v6 = -v6;
      if ( *(uint32_t *)this != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)this + 308))(*(uint32_t *)this) != 0
        && *(this + 6) != v6 )
      {
        *(this + 6) = v6;
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
void /*thiscall*/ sub_4A05C0(int this, int nArg2)
{
  int fld_24; // eax
  float v3; // [esp+0h] [ebp-4h]

  fld_24 = *(uint32_t *)(this + 36);
  if ( fld_24 < 0 && nArg2 >= 0 )
  {
    v3 = (double)-(nArg2 * fld_24) * 0.001;
    sub_494F20((float *)this, 2, v3);
  }
}



// ------------------------------------------------------------
// 0x4A0600 sub_4A0600
// ------------------------------------------------------------
// 【解读】
//   【推断】速率零交叉修正（vmt37C 的伴侣）。this[a2+7] 与浮点 this[a2+4] 异号时，
//   把 this[a2+10] 写为 浮点值×-1000/系数 —— 千分位换算 + 方向翻转。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0600(int *this, int pArg2)
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
int /*thiscall*/ sub_4A0650(int this, int pArg2)
{
  if ( *(uint32_t *)(this + 104) != 0 && *(uint8_t *)(this + 108) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 104) + 40))(*(uint32_t *)(this + 104), pArg2);
  else
    return sub_432F40(*(float *)(this + 4 * pArg2 + 4));
}



// ------------------------------------------------------------
// 0x4A0680 sub_4A0680
// ------------------------------------------------------------
// 【解读】
//   【推断】暂停/继续总开关。this+172 为现状字节；变化时冻结/解冻 this+144 时钟
//   （sub_699030 / sub_698FE0）并向下游 this+104 对象转发 vt+56(a2) 广播。
//   被 CNRDObject_vmtE4（0x49A320）用作"子对象全冻"的施加点。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0680(int this, int nArg2)
{
  int pThis_90; // ecx
  char result; // al
  int fld_68; // ecx

  if ( (uint8_t)nArg2 != *(uint8_t *)(this + 172) )
  {
    *(uint8_t *)(this + 172) = nArg2;
    pThis_90 = this + 144;
    if ( (uint8_t)nArg2 != 0 )
      result = sub_699030(pThis_90);  // 【clock_freeze(clk)】
    else
      result = sub_698FE0(pThis_90);  // 【clock_unfreeze(clk)】
    fld_68 = *(uint32_t *)(this + 104);
    if ( fld_68 != 0 )
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_68 + 56))(fld_68, nArg2);
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
void /*thiscall*/ sub_4A06D0(int this, int nArg2)
{
  int v3; // ebx
  uint64_t fld_8; // rax

  *(uint32_t *)(this + 128) = nArg2;
  if ( nArg2 != 0 )
  {
    *(uint32_t *)(this + 132) = (uint64_t)*(float *)(this + 4)
                            - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
    fld_8 = (uint64_t)*(float *)(this + 8);
    *(uint32_t *)(this + 136) = fld_8 - v3;
    *(uint32_t *)(this + 140) = (uint64_t)*(float *)(this + 12)
                            - (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 128))(nArg2, HIDWORD(fld_8));
  }
}



// ------------------------------------------------------------
// 0x4A0740 sub_4A0740
// ------------------------------------------------------------
// 【解读】
//   【推断】时间域变更深层递归（CNRDObject_vmt48 尾部调用的正是本函数）。
//   sub_699070(a2) 换域后，对 this+104 子对象再调其 vt+68 —— 递归到叶子。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0740(int *this, int nArg2)
{
  int result; // eax

  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  result = *(this + 26);
  if ( result != 0 )
    return (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 68))(nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x4A0770 sub_4A0770
// ------------------------------------------------------------
// 【解读】
//   【推断】设置"宿主/所有者"指针并联动 sub_49FD20（动画归属重绑）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0770(uint32_t *this, int nArg2)
{
  *this = nArg2;
  return sub_49FD20((int)this);
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
void /*thiscall*/ sub_4A0790(uint32_t *this)
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

  if ( *((uint8_t *)this + 172) == 0 )
  {
    fld_e44 = (float *)(sub_699000((int)(this + 36)) - *(this + 44));  // 【clock_now(clk)】
    pThis_24 = sub_699000((int)(this + 36));  // 【clock_now(clk)】
    fld_e32 = *(this + 32);
    *(this + 44) = pThis_24;
    if ( fld_e32 != 0 )
    {
      fld_e33 = *(this + 33) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e32 + 120))(fld_e32);
      v4 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 1) = v4;
      fld_e33 = *(this + 34) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 124))(*(this + 32));
      v5 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 2) = v5;
      fld_e33 = *(this + 35) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 128))(*(this + 32));
      v6 = (double)fld_e33;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 3) = v6;
    }
    pThis_1E = 0;
    pThis_2E = this + 46;
    do
      *pThis_2E++ = sub_49FD80(pThis_1E++, fld_e44);
    while ( pThis_1E < 3 );
    if ( *(this + 26) != 0 && *((uint8_t *)this + 108) != 0 )
    {
      if ( *(this + 28) == 2 && *((uint8_t *)this + 116) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(this + 30));
      }
      else
      {
        fld_e44 = (float *)(this + 1);
        pThis_1E = 0;
        fld_e33 = -4 - (uint32_t)this;
        do
        {
          fld_e26 = *(this + 26);
          if ( fld_e26 != 0 && *((uint8_t *)this + 108) != 0 )
            v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e26 + 40))(fld_e26, pThis_1E);
          else
            v10 = sub_432F40(*fld_e44);
          v11 = *fld_e44;
          fld_e262 = (int *)*(this + 26);
          v34[pThis_1E] = v10;
          v13 = *fld_e262;
          v35 = (uint64_t)v11;
          v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 16))(fld_e262);
          fld_e442 = fld_e44;
          *(uint32_t *)((char *)fld_e44 + fld_e33 + v14) = v35;
          ++pThis_1E;
          fld_e44 = fld_e442 + 1;
        }
        while ( pThis_1E < 3 );
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 26) + 8))(*(this + 26));
        if ( *this != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 40))(*this, 1) != 0
          && (*((uint8_t *)this + 116) == 0 || *(this + 28) == 0) )
        {
          fld_e263 = *(this + 26);
          if ( fld_e263 != 0 && *((uint8_t *)this + 108) != 0 )
            pThis_2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e263 + 40))(fld_e263, 1);
          else
            pThis_2 = sub_432F40(*((float *)this + 2));
          fld_e264 = *(this + 26);
          pThis_22 = pThis_2;
          if ( fld_e264 != 0 && *((uint8_t *)this + 108) != 0 )
            pThis_1 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e264 + 40))(fld_e264, 0);
          else
            pThis_1 = sub_432F40(*((float *)this + 1));
          pThis_1E = (int)(this + 30);
          if ( (*(uint8_t (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)*this + 136))(pThis_1, pThis_22, this + 30) == 0
            || ((fld_e265 = *(this + 26)) == 0 || *((uint8_t *)this + 108) == 0
              ? (v22 = sub_432F40(*((float *)this + 3)))
              : (v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e265 + 40))(fld_e265, 2)),
                (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v22) == 0) )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(uint32_t *)pThis_1E);
            *((uint8_t *)this + 116) = 1;
          }
        }
        if ( *((uint8_t *)this + 116) != 0 && *(this + 28) == 1 && *((uint8_t *)this + 124) == 0 )
        {
          pThis_1E = 0;
          fld_e33 = 0;
          do
          {
            fld_e266 = *(this + 26);
            if ( *((uint8_t *)this + pThis_1E + 117) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)fld_e266 + 36))(fld_e266, pThis_1E, v34[pThis_1E]);
            }
            else
            {
              if ( fld_e266 != 0 && *((uint8_t *)this + 108) != 0 )
                v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e266 + 40))(fld_e266, pThis_1E);
              else
                v24 = sub_432F40(*((float *)this + pThis_1E + 1));
              fld_e44 = (float *)v24;
              if ( v34[pThis_1E] != v24 )
              {
                while ( 1 )
                {
                  v25 = v34[pThis_1E];
                  v34[pThis_1E] = v25 >= (int)fld_e44 ? v25 - 1 : v25 + 1;
                  fld_e267 = *(this + 26);
                  if ( pThis_1E == 2 )
                  {
                    if ( fld_e267 != 0 && *((uint8_t *)this + 108) != 0 )
                    {
                      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e267 + 40))(fld_e267, 2);
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v27);
                    }
                    else
                    {
                      pThis_3 = sub_432F40(*((float *)this + 3));
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, pThis_3);
                    }
                  }
                  else
                  {
                    pThis_6C = fld_e267 != 0 && *((uint8_t *)this + 108) != 0
                        ? (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e267 + 40))(fld_e267, 1)
                        : sub_432F40(*((float *)this + 2));
                    fld_e268 = *(this + 26);
                    pThis_6C2 = pThis_6C;
                    if ( fld_e268 != 0 && *((uint8_t *)this + 108) != 0 )
                      pThis_12 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e268 + 40))(fld_e268, 0);
                    else
                      pThis_12 = sub_432F40(*((float *)this + 1));
                    v28 = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*this + 136))(*this, pThis_12, pThis_6C2, 0);
                    pThis_1E = fld_e33;
                  }
                  if ( v28 == 0 )
                    break;
                  if ( (float *)v34[pThis_1E] == fld_e44 )
                    goto LABEL_68;
                }
                (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + 26) + 36))(*(this + 26), pThis_1E, v25);
                v34[pThis_1E] = v25;
                *((uint8_t *)this + pThis_1E + 117) = 1;
              }
            }
LABEL_68:
            fld_e33 = ++pThis_1E;
          }
          while ( pThis_1E < 3 );
        }
        *((uint8_t *)this + 124) = 0;
      }
    }
    if ( *(this + 50) != 0 && sub_699000((int)(this + 36)) >= (unsigned int)(*(this + 50) + *(this + 45)) )  // 【clock_now(clk)】
      sub_49FFC0(this, pThis_1E, (int)this, 0, 0);
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
int /*thiscall*/ sub_4A0B60(int this, int nArg2)
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

  fld_68 = *(uint32_t *)(this + 104);
  if ( fld_68 != 0 && *(uint8_t *)(this + 108) != 0 )
    fld_4 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_68 + 40))(fld_68, 0);
  else
    fld_4 = sub_432F40(*(float *)(this + 4));
  fld_682 = *(uint32_t *)(this + 104);
  fld_42 = fld_4;
  if ( fld_682 != 0 && *(uint8_t *)(this + 108) != 0 )
    fld_8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_682 + 40))(fld_682, 1);
  else
    fld_8 = sub_432F40(*(float *)(this + 8));
  fld_683 = *(uint32_t *)(this + 104);
  fld_82 = fld_8;
  if ( fld_683 != 0 && *(uint8_t *)(this + 108) != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_683 + 40))(fld_683, 2);
  else
    result = sub_432F40(*(float *)(this + 12));
  pThis_68 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 104);
  v12 = result;
  if ( pThis_68 != nullptr )
    result = (**pThis_68)(pThis_68, 1);
  *(uint32_t *)(this + 104) = nArg2;
  if ( nArg2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 68))(nArg2, *(uint32_t *)(this + 152));
    v11 = 0;
    pThis_4 = (float *)(this + 4);
    do
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + v11);
      *(uint8_t *)(this + 124) = 1;
      v11 += 4;
      *pThis_4++ = (float)v13;
    }
    while ( v11 < 12 );
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 8))(nArg2);
    *(uint8_t *)(this + 116) = 0;
    *(uint16_t *)(this + 117) = 0;
    *(uint8_t *)(this + 119) = 0;
    *(uint32_t *)(this + 120) = 0;
    return 0;
  }
  else
  {
    *(float *)(this + 4) = (float)fld_42;
    *(float *)(this + 8) = (float)fld_82;
    *(uint8_t *)(this + 124) = 1;
    *(float *)(this + 12) = (float)v12;
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
uint32_t */*thiscall*/ sub_4A0CB0(uint32_t *Block, char pszArg2)
{
  *Block = &CNGoblinCommon::`vftable';
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A0CE0 sub_4A0CE0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMonsterFriendShip vftable 写入桩（友方怪物基类析构/构造残片）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0CE0(uint32_t *this)
{
  *this = &CNMonsterFriendShip::`vftable';
}



// ------------------------------------------------------------
// 0x4A0CF0 sub_4A0CF0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek 构造（食尸鬼油商 Olrek）。
//   先调 sub_58E0E0 基类构造 → 写 vftable → sub_58E3B0 收尾。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A0CF0(uint32_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_58E0E0((int)this, ArgList, nArg3, pszArg4);
  *this = &CNGhoulOilSellerOlrek::`vftable';
  sub_58E3B0(this);  // 【CNGhoulOilSellerOlrek__vmt51C】
  return this;
}



// ------------------------------------------------------------
// 0x4A0D70 sub_4A0D70 [RTTI: IRDCollisionObject__vmt174 · 槽位 IRDActiveObject+174,IRDCollisionObject+174]
// ------------------------------------------------------------
// 【解读】
//   【推断】写 this+608（vt+174 对偶槽）——攻击/动作资源句柄缓存。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0D70(uint32_t *this, int nArg2)
{
  *(this + 152) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4A0DC0 sub_4A0DC0 [RTTI: IRDCollisionObject__vmt1B8 · 槽位 IRDActiveObject+1B8,IRDCollisionObject+1B8] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1B8 —— 包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DC0(uint32_t *this)
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - *(this + 79) / 2;
}



// ------------------------------------------------------------
// 0x4A0DE0 sub_4A0DE0 [RTTI: IRDCollisionObject__vmt1BC · 槽位 IRDActiveObject+1BC,IRDCollisionObject+1BC] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1BC [族级] —— 包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 "1B8/1BC/1C0/1C4 包围盒边界计算族" 一行覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DE0(uint32_t *this)
{
  return *(this + 79) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 440))(this);
}



// ------------------------------------------------------------
// 0x4A0E00 sub_4A0E00 [RTTI: IRDCollisionObject__vmt1C0 · 槽位 IRDActiveObject+1C0,IRDCollisionObject+1C0] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1C0 [族级] —— 包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E00(uint32_t *this)
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - *(this + 80) / 2;
}



// ------------------------------------------------------------
// 0x4A0E20 sub_4A0E20 [RTTI: IRDCollisionObject__vmt1C4 · 槽位 IRDActiveObject+1C4,IRDCollisionObject+1C4] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt1C4 [族级] —— 包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E20(uint32_t *this)
{
  return *(this + 80) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 448))(this);
}



// ------------------------------------------------------------
// 0x4A0E40 sub_4A0E40 [RTTI: IRDCollisionObject__vmt22C · 槽位 IRDActiveObject+22C,IRDCollisionObject+22C]
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E40(uint8_t *this, char pszArg2)
{
  *(this + 612) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A0E70 sub_4A0E70 [RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActiveObject+254,IRDCollisionObject+254]
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E70(uint8_t *this, char pszArg2)
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
int /*thiscall*/ sub_4A0EC0(uint32_t *this)
{
  if ( *(this + 142) == -1 )
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
int /*thiscall*/ sub_4A0EF0(uint32_t *this)
{
  return *(this + 143);
}



// ------------------------------------------------------------
// 0x4A0F00 sub_4A0F00 [RTTI: IRDActiveObject__vmt2AC · 槽位 IRDActiveObject+2AC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2AC —— 属性块基址（this+6132，HP 读处）
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F00(char *this)
{
  return this + 6132;
}



// ------------------------------------------------------------
// 0x4A0F10 sub_4A0F10 [RTTI: IRDActiveObject__vmt2B0 · 槽位 IRDActiveObject+2B0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2B0 —— 附加块基址 this+6160
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F10(char *this)
{
  return this + 6160;
}



// ------------------------------------------------------------
// 0x4A0F20 sub_4A0F20 [RTTI: IRDActiveObject__vmt2BC · 槽位 IRDActiveObject+2BC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2BC —— 读 +6296 槽
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F20(uint32_t *this)
{
  return *(this + 1574);
}



// ------------------------------------------------------------
// 0x4A0F30 sub_4A0F30 [RTTI: IRDActiveObject__vmt184 · 槽位 IRDActiveObject+184] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt184 —— 属性块（vt+672(3)）首 DWORD
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F30(void *this)
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
}



// ------------------------------------------------------------
// 0x4A0F40 sub_4A0F40 [RTTI: IRDActiveObject__vmt2D4 · 槽位 IRDActiveObject+2D4] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt2D4 —— 读 +6552 霸体字节
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0F40(uint8_t *this)
{
  return *(this + 6552);
}



// ------------------------------------------------------------
// 0x4A0F50 sub_4A0F50 [RTTI: IRDActiveObject__vmt304 · 槽位 IRDActiveObject+304] [已精修] 见 src/cnrd/IRDActiveObject.h vmt304 —— 17 状态槽数组访问（+6228+4*a2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F50(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 1557);
}



// ------------------------------------------------------------
// 0x4A0F70 sub_4A0F70 [RTTI: IRDActiveObject__vmt318 · 槽位 IRDActiveObject+318] [已精修] 见 src/cnrd/IRDActiveObject.h vmt318 —— 18 观察者槽数组访问（+6468+4*a2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F70(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 1617);
}



// ------------------------------------------------------------
// 0x4A0F90 sub_4A0F90 [RTTI: IRDActiveObject__vmt330 · 槽位 IRDActiveObject+330] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt330 —— 转发 vt+808(a2, 0xFFFF, 0, a3)
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F90(void *this, int nArg2, int nArg3)
{
  return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, int))(*(uint32_t *)this + 808))(this, nArg2, 0xFFFF, 0, nArg3);
}



// ------------------------------------------------------------
// 0x4A0FB0 sub_4A0FB0 [RTTI: IRDActiveObject__vmt334 · 槽位 IRDActiveObject+334] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt334 —— 写 +6740 字节
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0FB0(uint8_t *this, char pszArg2)
{
  *(this + 6740) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A0FC0 sub_4A0FC0 [RTTI: IRDActiveObject__vmt1C8 · 槽位 IRDActiveObject+1C8] [已精修] 见 src/cnrd/IRDActiveObject.h vmt1C8 —— 命中列表追加（vt+676(0) 联动 + 基类）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FC0(void *this, int nArg2, char pszArg3)
{
  int result; // eax

  result = sub_4E8080(nArg2, pszArg3);
  if ( pszArg3 != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x4A0FF0 sub_4A0FF0 [RTTI: IRDActiveObject__vmt1CC · 槽位 IRDActiveObject+1CC] [已精修] 见 src/cnrd/IRDActiveObject.h vmt1CC —— 命中列表移除（IRDCollisionObject_vmt1CC 基类实现 + vt+676(0) 联动；0x4A0FC0=1C8 追加）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FF0(void *this, int nArg2)
{
  sub_4E7040(nArg2);
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
}



// ------------------------------------------------------------
// 0x4A1010 sub_4A1010 [RTTI: IRDActiveObject__vmt348 · 槽位 IRDActiveObject+348] [已精修] 见 src/cnrd/IRDActiveObject.h vmt348 —— 大状态 getter（this+6556）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1010(uint32_t *this)
{
  return *(this + 1639);
}



// ------------------------------------------------------------
// 0x4A1020 sub_4A1020 [RTTI: IRDActiveObject__vmt34C · 槽位 IRDActiveObject+34C] [已精修] 见 src/cnrd/IRDActiveObject.h vmt34C —— 内嵌动作子对象 this+6560
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1020(char *this)
{
  return this + 6560;
}



// ------------------------------------------------------------
// 0x4A1030 sub_4A1030 [RTTI: IRDActiveObject__vmt350 · 槽位 IRDActiveObject+350] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt350 —— 冻结标志写入（+6744，0→-1 / 非0→0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1030(uint32_t *this, char pszArg2)
{
  int result; // eax

  result = (pszArg2 != 0) - 1;
  *(this + 1686) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4A1050 sub_4A1050 [RTTI: IRDActiveObject__vmt354 · 槽位 IRDActiveObject+354] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt354 —— 冻结标志 != -1 查询
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1050(uint32_t *this)
{
  return *(this + 1686) != -1;
}



// ------------------------------------------------------------
// 0x4A10D0 sub_4A10D0 [RTTI: IRDActiveObject__vmt3DC · 槽位 IRDActiveObject+3DC] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3DC —— 非霸体自由条件（vt+724==0 且状态3/8==0）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A10D0(void *this)
{
  return (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 724))(this) == 0
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 3) == 0
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 8) == 0;
}



// ------------------------------------------------------------
// 0x4A1110 sub_4A1110 [RTTI: IRDActiveObject__vmt3E4 · 槽位 IRDActiveObject+3E4] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3E4 —— 复活计时器清零（写 -1）
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1110(uint32_t *this)
{
  *(this + 1774) = -1;
}



// ------------------------------------------------------------
// 0x4A1120 sub_4A1120 [RTTI: IRDActiveObject__vmt3E8 · 槽位 IRDActiveObject+3E8] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3E8 —— 复活计时中判定（!= -1）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1120(uint32_t *this)
{
  return *(this + 1774) != -1;
}



// ------------------------------------------------------------
// 0x4A1130 sub_4A1130 [RTTI: IRDActiveObject__vmt3F0 · 槽位 IRDActiveObject+3F0] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt3F0 —— 复活已计时（clockAux 域差值）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1130(uint32_t *this)
{
  if ( *(this + 1774) == -1 )
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
char */*thiscall*/ sub_4A1150(char *this)
{
  return this + 7232;
}



// ------------------------------------------------------------
// 0x4A1160 sub_4A1160
// ------------------------------------------------------------
// 【解读】
//   【推断】返回 this+7520 —— 与 0x4A1150 成对的内嵌块基址（0x4A11D0 析构其内容）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1160(char *this)
{
  return this + 7520;
}



// ------------------------------------------------------------
// 0x4A1170 sub_4A1170
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this+7260（this+1815*4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1170(uint32_t *this)
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
int /*thiscall*/ sub_4A1180(uint32_t *this)
{
  int fld_e2090; // eax

  fld_e2090 = *(this + 2090);
  if ( fld_e2090 != 0 )
    return *(uint8_t *)(fld_e2090 + 2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11A0 sub_4A11A0
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this[2090]（+8360）指向对象的 +3 DWORD —— 与 0x4A1180 同一对象的两字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A11A0(uint32_t *this)
{
  int fld_e2090; // eax

  fld_e2090 = *(this + 2090);
  if ( fld_e2090 != 0 )
    return *(uint32_t *)(fld_e2090 + 3);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11C0 sub_4A11C0
// ------------------------------------------------------------
// 【解读】
//   【推断】恒等函数（返回入参本身）—— 接口桩/适配器。
// ------------------------------------------------------------
int16_t /*stdcall*/ sub_4A11C0(int16_t uArg1)
{
  return uArg1;
}



// ------------------------------------------------------------
// 0x4A11D0 sub_4A11D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek 析构（调 0x4A1200 + 可选 free）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A11D0(void *Block, char pszArg2)
{
  sub_4A1200();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A1200 sub_4A1200
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGhoulOilSellerOlrek vftable 重置 + sub_58E0D0 基类析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1200(uint32_t *this)
{
  *this = &CNGhoulOilSellerOlrek::`vftable';
  return sub_58E0D0();
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
int /*fastcall*/ sub_4A1210(uint32_t *pArg1, int nArg2)
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
  sub_41A590((unsigned int)(pArg1 + 1), nArg2, 0);
  sub_41A590((unsigned int)pArg1 + 18, v3, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 8), v4, 0);
  sub_41A590((unsigned int)pArg1 + 46, v5, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 15), v6, 0);
  sub_41A590((unsigned int)pArg1 + 74, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 22), v7, 0);
  sub_41A590((unsigned int)pArg1 + 102, v8, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 29), v9, 0);
  sub_41A590((unsigned int)pArg1 + 130, v10, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 36), v11, 0);
  sub_41A590((unsigned int)pArg1 + 158, 1065353216, 1065353216);
  v13 = (unsigned int)(pArg1 + 57);
  for ( i = 4; i != 0; --i )
  {
    sub_41A590(v13 - 56, v12, 0);
    sub_41A590(v13, v15, 1065353216);
    v13 += 14;
  }
  v16 = (unsigned int)(pArg1 + 127);
  for ( j = 16; j != 0; --j )
  {
    sub_41A590(v16 - 224, v12, 0);
    sub_41A590(v16, v18, 1065353216);
    v16 += 14;
  }
  sub_41A590((unsigned int)(pArg1 + 183), v12, 0);
  sub_41A590((unsigned int)pArg1 + 746, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 190), v19, 0);
  sub_41A590((unsigned int)pArg1 + 774, v20, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 197), v21, 0);
  sub_41A590((unsigned int)pArg1 + 802, v22, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 204), v23, 1000);
  sub_41A590((unsigned int)pArg1 + 830, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 211), v24, 1000);
  sub_41A590((unsigned int)pArg1 + 858, v25, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 218), v26, 1000);
  sub_41A590((unsigned int)pArg1 + 886, v27, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 225), v28, 0);
  sub_41A590((unsigned int)pArg1 + 914, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 232), v29, 0);
  sub_41A590((unsigned int)pArg1 + 942, v30, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 239), v31, 100);
  sub_41A590((unsigned int)pArg1 + 970, v32, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 246), v33, 0);
  sub_41A590((unsigned int)pArg1 + 998, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 253), v34, 0);
  sub_41A590((unsigned int)pArg1 + 1026, v35, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 260), v36, 0);
  sub_41A590((unsigned int)pArg1 + 1054, v37, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 267), v38, 0);
  sub_41A590((unsigned int)pArg1 + 1082, 1065353216, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 274), v39, 0);
  sub_41A590((unsigned int)pArg1 + 1110, v40, 1065353216);
  sub_41A590((unsigned int)(pArg1 + 281), v41, 0);
  sub_41A590((unsigned int)pArg1 + 1138, v42, 0);
  sub_41A590((unsigned int)(pArg1 + 288), v43, 0);
  sub_41A590((unsigned int)pArg1 + 1166, v44, 0);
  sub_41A590((unsigned int)(pArg1 + 295), v45, 0);
  sub_41A590((unsigned int)pArg1 + 1194, 0, 0);
  sub_41A590((unsigned int)(pArg1 + 302), v46, 0);
  sub_41A590((unsigned int)pArg1 + 1222, v47, 0);
  sub_41A590((unsigned int)(pArg1 + 309), 0, 0);
  sub_41A590((unsigned int)pArg1 + 1250, v48, 0);
  sub_41A590((unsigned int)(pArg1 + 316), v49, 0);
  sub_41A590((unsigned int)pArg1 + 1278, 0, 0);
  sub_41A590((unsigned int)(pArg1 + 323), v50, 1065353216);
  sub_41A590((unsigned int)pArg1 + 1306, v51, 0);
  sub_41A590((unsigned int)(pArg1 + 330), v52, 0);
  sub_41A590((unsigned int)pArg1 + 1334, v53, 0);
  return sub_41A590((unsigned int)(pArg1 + 337), v54, 0);
}


// ------------------------------------------------------------
// 0x4A1670 sub_4A1670
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性块析构/重置（0x4A1210 的对偶）。逐槽 sub_41A630（解引用计数）
//   后重写 vftable 为 clong/cfloat，最后 `eh vector destructor iterator` 清理 4 元素与
//   16 元素两个内嵌数组 —— 数组元素大小 0xE(14) 字节，与 0x4A1210 的步长直证一致。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1670(uint32_t *this)
{
  uint32_t *pThis_1; // edi
  int v3; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *pThis_1 = &clong::`vftable';
  sub_41A630((unsigned int)this + 18);
  *(uint32_t *)((char *)this + 18) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 8));
  *(this + 8) = &clong::`vftable';
  sub_41A630((unsigned int)this + 46);
  *(uint32_t *)((char *)this + 46) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 15));
  *(this + 15) = &clong::`vftable';
  sub_41A630((unsigned int)this + 74);
  *(uint32_t *)((char *)this + 74) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 22));
  *(this + 22) = &clong::`vftable';
  sub_41A630((unsigned int)this + 102);
  *(uint32_t *)((char *)this + 102) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 29));
  *(this + 29) = &clong::`vftable';
  sub_41A630((unsigned int)this + 130);
  *(uint32_t *)((char *)this + 130) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 36));
  *(this + 36) = &clong::`vftable';
  sub_41A630((unsigned int)this + 158);
  *(uint32_t *)((char *)this + 158) = &cfloat::`vftable';
  `eh vector constructor iterator'(this + 43, 0xEu, 4, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);
  `eh vector constructor iterator'(this + 57, 0xEu, 4, sub_432CD0, sub_432D10);
  `eh vector constructor iterator'(this + 71, 0xEu, 16, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);
  `eh vector constructor iterator'(this + 127, 0xEu, 16, sub_432CD0, sub_432D10);
  sub_41A630((unsigned int)(this + 183));
  *(this + 183) = &clong::`vftable';
  sub_41A630((unsigned int)this + 746);
  *(uint32_t *)((char *)this + 746) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 190));
  *(this + 190) = &clong::`vftable';
  sub_41A630((unsigned int)this + 774);
  *(uint32_t *)((char *)this + 774) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 197));
  *(this + 197) = &clong::`vftable';
  sub_41A630((unsigned int)this + 802);
  *(uint32_t *)((char *)this + 802) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 204));
  *(this + 204) = &clong::`vftable';
  sub_41A630((unsigned int)this + 830);
  *(uint32_t *)((char *)this + 830) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 211));
  *(this + 211) = &clong::`vftable';
  sub_41A630((unsigned int)this + 858);
  *(uint32_t *)((char *)this + 858) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 218));
  *(this + 218) = &clong::`vftable';
  sub_41A630((unsigned int)this + 886);
  *(uint32_t *)((char *)this + 886) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 225));
  *(this + 225) = &clong::`vftable';
  sub_41A630((unsigned int)this + 914);
  *(uint32_t *)((char *)this + 914) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 232));
  *(this + 232) = &clong::`vftable';
  sub_41A630((unsigned int)this + 942);
  *(uint32_t *)((char *)this + 942) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 239));
  *(this + 239) = &clong::`vftable';
  sub_41A630((unsigned int)this + 970);
  *(uint32_t *)((char *)this + 970) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 246));
  *(this + 246) = &clong::`vftable';
  sub_41A630((unsigned int)this + 998);
  *(uint32_t *)((char *)this + 998) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 253));
  *(this + 253) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1026);
  *(uint32_t *)((char *)this + 1026) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 260));
  *(this + 260) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1054);
  *(uint32_t *)((char *)this + 1054) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 267));
  *(this + 267) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1082);
  *(uint32_t *)((char *)this + 1082) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 274));
  *(this + 274) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1110);
  *(uint32_t *)((char *)this + 1110) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 281));
  *(this + 281) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1138);
  *(uint32_t *)((char *)this + 1138) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 288));
  *(this + 288) = &cfloat::`vftable';
  sub_41A630((unsigned int)this + 1166);
  *(uint32_t *)((char *)this + 1166) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 295));
  *(this + 295) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1194);
  *(uint32_t *)((char *)this + 1194) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 302));
  *(this + 302) = &cfloat::`vftable';
  sub_41A630((unsigned int)this + 1222);
  *(uint32_t *)((char *)this + 1222) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 309));
  *(this + 309) = &cfloat::`vftable';
  sub_41A630((unsigned int)this + 1250);
  *(uint32_t *)((char *)this + 1250) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 316));
  *(this + 316) = &cfloat::`vftable';
  sub_41A630((unsigned int)this + 1278);
  *(uint32_t *)((char *)this + 1278) = &cfloat::`vftable';
  sub_41A630((unsigned int)(this + 323));
  *(this + 323) = &cfloat::`vftable';
  sub_41A630((unsigned int)this + 1306);
  *(uint32_t *)((char *)this + 1306) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 330));
  *(this + 330) = &clong::`vftable';
  sub_41A630((unsigned int)this + 1334);
  *(uint32_t *)((char *)this + 1334) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 337));
  *(this + 337) = &clong::`vftable';
  sub_4A1210(this, v3);
}


// ------------------------------------------------------------
// 0x4A1C30 sub_4A1C30
// ------------------------------------------------------------
// 【解读】
//   【推断】双 clong 小构造（设 vftable + 初值 -1）—— 与 0x4A1CA0 同址族，
//   疑为"HP 当前值/上限值"对（vmt188 读的就是 +60/+74 的这对）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A1C30(uint32_t *this)
{
  int v2; // edx
  int v3; // edx

  sub_41A630((unsigned int)this);
  *this = &clong::`vftable';
  sub_41A630((unsigned int)this + 14);
  *(uint32_t *)((char *)this + 14) = &clong::`vftable';
  sub_41A590((unsigned int)this, v2, -1);
  sub_41A590((unsigned int)this + 14, v3, -1);
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

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 60);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 74)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1CE0 sub_4A1CE0 [RTTI: IRDActiveObject__vmt18C · 槽位 IRDActiveObject+18C] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt18C —— MP 类属性读取（+1012 × 浮点壳 +1026）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1CE0(void *this)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 1012);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 1026)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1D20 sub_4A1D20 [RTTI: IRDActiveObject__vmt190 · 槽位 IRDActiveObject+190] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt190 —— 整数属性读取（+1306）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D20(void *this)
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(pThis_2A0 + 1306);
}



// ------------------------------------------------------------
// 0x4A1D40 sub_4A1D40 [RTTI: IRDActiveObject__vmt194 · 槽位 IRDActiveObject+194] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt194 —— 整数属性读取（+1124）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D40(void *this)
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(pThis_2A0 + 1124);
}



// ------------------------------------------------------------
// 0x4A1D60 sub_4A1D60 [RTTI: IRDActiveObject__vmt198 · 槽位 IRDActiveObject+198]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +116 防篡读 × 浮点壳 +130 —— 与 0x4A1CA0/0x4A1CE0 同一族（vmt198）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1D60(void *this)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 116);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 130)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1DA0 sub_4A1DA0 [RTTI: IRDActiveObject__vmt19C · 槽位 IRDActiveObject+19C]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1068 × 浮点壳 +1082（vmt19C 族 —— 与 MP 族 +1012/+1026 相隔 56B）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1DA0(void *this)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 1068);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 1082)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1DE0 sub_4A1DE0 [RTTI: IRDActiveObject__vmt1A0 · 槽位 IRDActiveObject+1A0]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1334 整数读（vmt1A0）。vmt188 族步长 56 字节的规律: 60/116/1012/1068。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1DE0(void *this)
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(pThis_2A0 + 1334);
}



// ------------------------------------------------------------
// 0x4A1E00 sub_4A1E00 [RTTI: IRDActiveObject__vmt1A4 · 槽位 IRDActiveObject+1A4]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +1166 整数读（vmt1A4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E00(void *this)
{
  int pThis_2A0; // eax

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(pThis_2A0 + 1166);
}



// ------------------------------------------------------------
// 0x4A1E20 sub_4A1E20 [RTTI: IRDActiveObject__vmt2E0 · 槽位 IRDActiveObject+2E0] [已精修] 见 src/cnrd/IRDActiveObject.h vmt2E0 —— 属性块首值（GetHP 族，此处索引）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E20(void *this)
{
  return sub_41A5E0((unsigned int)this + 6132);
}



// ------------------------------------------------------------
// 0x4A1E30 sub_4A1E30 [RTTI: IRDActiveObject__vmt2E4 · 槽位 IRDActiveObject+2E4] [已精修] 见 src/cnrd/IRDActiveObject.h vmt2E4 —— 属性块 +4 浮点壳（GetHP 族）
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1E30(void *this)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 4);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 18)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1E70 sub_4A1E70 [RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObject+2EC]
// ------------------------------------------------------------
// 【解读】
//   【推断】属性块 +6146 防篡写封装的 setter（a4 非 0 时同时把 +6604 置 -1 使缓存失效）。
// ------------------------------------------------------------
char /*fastcall*/ sub_4A1E70(int pArg1, int nArg2, int nArg3, char pszArg4)
{
  char result; // al

  sub_41A590(pArg1 + 6146, nArg2, nArg3);
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
uint64_t /*thiscall*/ sub_4A1EB0(void *this)
{
  int pThis_2A0; // esi
  int v3; // [esp+4h] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(pThis_2A0 + 32);
  return (uint64_t)(sub_43B5A0((void *)(pThis_2A0 + 46)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1EF0 sub_4A1EF0 [RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveObject+38C]
// ------------------------------------------------------------
// 【解读】
//   【推断】读 this+7028 的 clong（vmt38C）—— 由 0x4A49B0 构造时以 sub_41A630+clong vftable 初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1EF0(void *this)
{
  return sub_41A5E0((unsigned int)this + 7028);
}



// ------------------------------------------------------------
// 0x4A1F00 sub_4A1F00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 属性块 62 槽全解构（sub_41A580 = clong/cfloat 析构单槽）。
//   顺序 = 0x4A1670 构造的逆序，含 4/16 元素两个 eh vector 数组 ——
//   这是 0x4A49B0（IRDActiveObject 构造）注册的析构回调（eh vector constructor iterator 的第 5 参）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1F00(uint32_t *this)
{
  sub_41A580(this + 337);
  sub_41A580((uint32_t *)((char *)this + 1334));
  sub_41A580(this + 330);
  sub_41A580((uint32_t *)((char *)this + 1306));
  sub_41A580(this + 323);
  sub_41A580((uint32_t *)((char *)this + 1278));
  sub_41A580(this + 316);
  sub_41A580((uint32_t *)((char *)this + 1250));
  sub_41A580(this + 309);
  sub_41A580((uint32_t *)((char *)this + 1222));
  sub_41A580(this + 302);
  sub_41A580((uint32_t *)((char *)this + 1194));
  sub_41A580(this + 295);
  sub_41A580((uint32_t *)((char *)this + 1166));
  sub_41A580(this + 288);
  sub_41A580((uint32_t *)((char *)this + 1138));
  sub_41A580(this + 281);
  sub_41A580((uint32_t *)((char *)this + 1110));
  sub_41A580(this + 274);
  sub_41A580((uint32_t *)((char *)this + 1082));
  sub_41A580(this + 267);
  sub_41A580((uint32_t *)((char *)this + 1054));
  sub_41A580(this + 260);
  sub_41A580((uint32_t *)((char *)this + 1026));
  sub_41A580(this + 253);
  sub_41A580((uint32_t *)((char *)this + 998));
  sub_41A580(this + 246);
  sub_41A580((uint32_t *)((char *)this + 970));
  sub_41A580(this + 239);
  sub_41A580((uint32_t *)((char *)this + 942));
  sub_41A580(this + 232);
  sub_41A580((uint32_t *)((char *)this + 914));
  sub_41A580(this + 225);
  sub_41A580((uint32_t *)((char *)this + 886));
  sub_41A580(this + 218);
  sub_41A580((uint32_t *)((char *)this + 858));
  sub_41A580(this + 211);
  sub_41A580((uint32_t *)((char *)this + 830));
  sub_41A580(this + 204);
  sub_41A580((uint32_t *)((char *)this + 802));
  sub_41A580(this + 197);
  sub_41A580((uint32_t *)((char *)this + 774));
  sub_41A580(this + 190);
  sub_41A580((uint32_t *)((char *)this + 746));
  sub_41A580(this + 183);
  `eh vector destructor iterator'(this + 127, 0xEu, 16, sub_432D10);
  `eh vector destructor iterator'(this + 71, 0xEu, 16, sub_432D10);
  `eh vector destructor iterator'(this + 57, 0xEu, 4, sub_432D10);
  `eh vector destructor iterator'(this + 43, 0xEu, 4, sub_432D10);
  sub_41A580((uint32_t *)((char *)this + 158));
  sub_41A580(this + 36);
  sub_41A580((uint32_t *)((char *)this + 130));
  sub_41A580(this + 29);
  sub_41A580((uint32_t *)((char *)this + 102));
  sub_41A580(this + 22);
  sub_41A580((uint32_t *)((char *)this + 74));
  sub_41A580(this + 15);
  sub_41A580((uint32_t *)((char *)this + 46));
  sub_41A580(this + 8);
  sub_41A580((uint32_t *)((char *)this + 18));
  sub_41A580(this + 1);
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
  sub_41A580((uint32_t *)((char *)this + 14));
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x4A2330 sub_4A2330
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMagmaGhoul（熔岩食尸鬼）构造。基类 sub_58DFE0 → vftable → 内嵌块初始化。
//   新发现字段: +8632 标志字节、+8628 IObject vftable、+8636 int、+8640 字节 =1。
//   RTTI 名（vftable 直证）: CNMagmaGhoul。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2330(int this, char ArgList, int nArg3, char pszArg4)
{
  sub_58DFE0((uint8_t *)this, ArgList, nArg3, pszArg4);
  *(uint32_t *)this = &CNMagmaGhoul::`vftable';
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8628) = &off_6C2B88;
  *(uint32_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8640) = 1;
  *(uint8_t *)(this + 8642) = 0;
  *(uint8_t *)(this + 8641) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = 0;
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
void */*thiscall*/ sub_4A23D0(void *Block, char pszArg2)
{
  sub_4A2400();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A2400 sub_4A2400
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMagmaGhoul vftable 复位 + nengine::IObject 子对象复位 + sub_58E0D0 基类析构。
//   注意 +8628（2157*4）处挂了 nengine::IObject 子对象 —— 怪物类的通用附属组件。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2400(uint32_t *this)
{
  *this = &CNMagmaGhoul::`vftable';
  nullsub_3(this);
  *(this + 2157) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8632) = 0;
  return sub_58E0D0(this);
}



// ------------------------------------------------------------
// 0x4A2460 sub_4A2460 [RTTI: IRDActiveObject__vmt29C · 槽位 IRDActiveObject+29C] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt29C —— 研究族槽位（0x4A2480 转发壳）
// ------------------------------------------------------------
int /*stdcall*/ sub_4A2460(int nArg1, int nArg2)
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
  v4 = sub_41A5E0((unsigned int)(pszArg2 + 4));
  sub_41A590((unsigned int)(this + 4), v5, v4);
  *(float *)&v93 = sub_43B5A0(pszArg2 + 18);
  sub_41A590((unsigned int)(this + 18), v6, v93);
  v7 = sub_41A5E0((unsigned int)(pszArg2 + 32));
  sub_41A590((unsigned int)(this + 32), v8, v7);
  *(float *)&v94 = sub_43B5A0(pszArg2 + 46);
  sub_41A590((unsigned int)(this + 46), v94, v94);
  v9 = sub_41A5E0((unsigned int)(pszArg2 + 60));
  sub_41A590((unsigned int)(this + 60), v10, v9);
  *(float *)&v95 = sub_43B5A0(pszArg2 + 74);
  sub_41A590((unsigned int)(this + 74), v11, v95);
  v12 = sub_41A5E0((unsigned int)(pszArg2 + 88));
  sub_41A590((unsigned int)(this + 88), v13, v12);
  *(float *)&v96 = sub_43B5A0(pszArg2 + 102);
  sub_41A590((unsigned int)(this + 102), v14, v96);
  v15 = sub_41A5E0((unsigned int)(pszArg2 + 116));
  sub_41A590((unsigned int)(this + 116), v16, v15);
  *(float *)&v97 = sub_43B5A0(pszArg2 + 130);
  sub_41A590((unsigned int)(this + 130), v97, v97);
  v17 = sub_41A5E0((unsigned int)(pszArg2 + 144));
  sub_41A590((unsigned int)(this + 144), v18, v17);
  *(float *)&v98 = sub_43B5A0(pszArg2 + 158);
  sub_41A590((unsigned int)(this + 158), v19, v98);
  pThis_AC = (unsigned int)(this + 172);
  v20 = pszArg2 - this;
  v89 = 4;
  do
  {
    v21 = sub_41A5E0(v20 + pThis_AC);
    sub_41A590(pThis_AC, v22, v21);
    v23 = v89 == 1;
    pThis_AC += 14;
    --v89;
  }
  while ( !v23 );
  pThis_E4 = (unsigned int)(this + 228);
  v90 = 4;
  do
  {
    *(float *)&v87 = sub_43B5A0((void *)(v20 + pThis_E4));
    sub_41A590(pThis_E4, v87, v87);
    v23 = v90 == 1;
    pThis_E4 += 14;
    --v90;
  }
  while ( !v23 );
  pThis_11C = (unsigned int)(this + 284);
  v91 = 16;
  do
  {
    v24 = sub_41A5E0(v20 + pThis_11C);
    sub_41A590(pThis_11C, v25, v24);
    v23 = v91 == 1;
    pThis_11C += 14;
    --v91;
  }
  while ( !v23 );
  pThis_1FC = (unsigned int)(this + 508);
  v92 = 16;
  do
  {
    *(float *)&v88 = sub_43B5A0((void *)(v20 + pThis_1FC));
    sub_41A590(pThis_1FC, v26, v88);
    v23 = v92 == 1;
    pThis_1FC += 14;
    --v92;
  }
  while ( !v23 );
  v27 = sub_41A5E0((unsigned int)(pszArg2 + 732));
  sub_41A590((unsigned int)(this + 732), v28, v27);
  *(float *)&v103 = sub_43B5A0(pszArg2 + 746);
  sub_41A590((unsigned int)(this + 746), v103, v103);
  v29 = sub_41A5E0((unsigned int)(pszArg2 + 760));
  sub_41A590((unsigned int)(this + 760), v30, v29);
  *(float *)&v104 = sub_43B5A0(pszArg2 + 774);
  sub_41A590((unsigned int)(this + 774), v31, v104);
  v32 = sub_41A5E0((unsigned int)(pszArg2 + 788));
  sub_41A590((unsigned int)(this + 788), v33, v32);
  *(float *)&v105 = sub_43B5A0(pszArg2 + 802);
  sub_41A590((unsigned int)(this + 802), v34, v105);
  v35 = sub_41A5E0((unsigned int)(pszArg2 + 816));
  sub_41A590((unsigned int)(this + 816), v36, v35);
  *(float *)&v106 = sub_43B5A0(pszArg2 + 830);
  sub_41A590((unsigned int)(this + 830), v106, v106);
  v37 = sub_41A5E0((unsigned int)(pszArg2 + 844));
  sub_41A590((unsigned int)(this + 844), v38, v37);
  *(float *)&v107 = sub_43B5A0(pszArg2 + 858);
  sub_41A590((unsigned int)(this + 858), v39, v107);
  v40 = sub_41A5E0((unsigned int)(pszArg2 + 872));
  sub_41A590((unsigned int)(this + 872), v41, v40);
  *(float *)&v108 = sub_43B5A0(pszArg2 + 886);
  sub_41A590((unsigned int)(this + 886), v42, v108);
  v43 = sub_41A5E0((unsigned int)(pszArg2 + 900));
  sub_41A590((unsigned int)(this + 900), v44, v43);
  *(float *)&v109 = sub_43B5A0(pszArg2 + 914);
  sub_41A590((unsigned int)(this + 914), v109, v109);
  v45 = sub_41A5E0((unsigned int)(pszArg2 + 928));
  sub_41A590((unsigned int)(this + 928), v46, v45);
  *(float *)&v110 = sub_43B5A0(pszArg2 + 942);
  sub_41A590((unsigned int)(this + 942), v47, v110);
  v48 = sub_41A5E0((unsigned int)(pszArg2 + 956));
  sub_41A590((unsigned int)(this + 956), v49, v48);
  *(float *)&v111 = sub_43B5A0(pszArg2 + 970);
  sub_41A590((unsigned int)(this + 970), v50, v111);
  v51 = sub_41A5E0((unsigned int)(pszArg2 + 984));
  sub_41A590((unsigned int)(this + 984), v52, v51);
  *(float *)&v112 = sub_43B5A0(pszArg2 + 998);
  sub_41A590((unsigned int)(this + 998), v112, v112);
  v53 = sub_41A5E0((unsigned int)(pszArg2 + 1012));
  sub_41A590((unsigned int)(this + 1012), v54, v53);
  *(float *)&v113 = sub_43B5A0(pszArg2 + 1026);
  sub_41A590((unsigned int)(this + 1026), v55, v113);
  v56 = sub_41A5E0((unsigned int)(pszArg2 + 1040));
  sub_41A590((unsigned int)(this + 1040), v57, v56);
  *(float *)&v114 = sub_43B5A0(pszArg2 + 1054);
  sub_41A590((unsigned int)(this + 1054), v58, v114);
  v59 = sub_41A5E0((unsigned int)(pszArg2 + 1068));
  sub_41A590((unsigned int)(this + 1068), v60, v59);
  *(float *)&v115 = sub_43B5A0(pszArg2 + 1082);
  sub_41A590((unsigned int)(this + 1082), v115, v115);
  v61 = sub_41A5E0((unsigned int)(pszArg2 + 1096));
  sub_41A590((unsigned int)(this + 1096), v62, v61);
  *(float *)&v116 = sub_43B5A0(pszArg2 + 1110);
  sub_41A590((unsigned int)(this + 1110), v63, v116);
  v64 = sub_41A5E0((unsigned int)(pszArg2 + 1124));
  sub_41A590((unsigned int)(this + 1124), v65, v64);
  v66 = sub_41A5E0((unsigned int)(pszArg2 + 1138));
  sub_41A590((unsigned int)(this + 1138), v67, v66);
  *(float *)&v117 = sub_43B5A0(pszArg2 + 1152);
  sub_41A590((unsigned int)(this + 1152), v68, v117);
  v69 = sub_41A5E0((unsigned int)(pszArg2 + 1166));
  sub_41A590((unsigned int)(this + 1166), v70, v69);
  v71 = sub_41A5E0((unsigned int)(pszArg2 + 1180));
  sub_41A590((unsigned int)(this + 1180), v72, v71);
  *(float *)&v118 = sub_43B5A0(pszArg2 + 1194);
  sub_41A590((unsigned int)(this + 1194), v118, v118);
  *(float *)&v119 = sub_43B5A0(pszArg2 + 1208);
  sub_41A590((unsigned int)(this + 1208), v73, v119);
  *(float *)&v120 = sub_43B5A0(pszArg2 + 1222);
  sub_41A590((unsigned int)(this + 1222), v74, v120);
  *(float *)&v121 = sub_43B5A0(pszArg2 + 1236);
  sub_41A590((unsigned int)(this + 1236), v121, v121);
  *(float *)&v122 = sub_43B5A0(pszArg2 + 1250);
  sub_41A590((unsigned int)(this + 1250), v75, v122);
  *(float *)&v123 = sub_43B5A0(pszArg2 + 1264);
  sub_41A590((unsigned int)(this + 1264), v76, v123);
  *(float *)&v124 = sub_43B5A0(pszArg2 + 1278);
  sub_41A590((unsigned int)(this + 1278), v124, v124);
  *(float *)&v125 = sub_43B5A0(pszArg2 + 1292);
  sub_41A590((unsigned int)(this + 1292), v77, v125);
  v78 = sub_41A5E0((unsigned int)(pszArg2 + 1306));
  sub_41A590((unsigned int)(this + 1306), v79, v78);
  v80 = sub_41A5E0((unsigned int)(pszArg2 + 1320));
  sub_41A590((unsigned int)(this + 1320), v81, v80);
  v82 = sub_41A5E0((unsigned int)(pszArg2 + 1334));
  sub_41A590((unsigned int)(this + 1334), v83, v82);
  v84 = sub_41A5E0((unsigned int)(pszArg2 + 1348));
  sub_41A590((unsigned int)(this + 1348), v85, v84);
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
  pThis_17F4 = (unsigned int)this + 6132;
  v3 = sub_41A5E0(pArg2);
  sub_41A590(pThis_17F4, v4, v3);
  v5 = sub_41A5E0(pArg2 + 14);
  sub_41A590(pThis_17F4 + 14, v6, v5);
  return pThis_17F4;
}



// ------------------------------------------------------------
// 0x4A2B80 sub_4A2B80 [RTTI: IRDActiveObject__vmt270 · 槽位 IRDActiveObject+270] [已精修] 见 src/cnrd/IRDActiveObject.cpp vmt270 —— 基类检查 + 附加条件（+7093 == 0）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A2B80(uint8_t *this)
{
  return (uint8_t)sub_4A2BB0() != 0 && *(this + 7093) == 0;
}



// ------------------------------------------------------------
// 0x4A2BB0 sub_4A2BB0 [RTTI: IRDCollisionObject__vmt270 · 槽位 IRDCollisionObject+270] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt270 —— 攻击使能检查（vt+608 + 动画帧率态 != 2）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2BB0(int *this)
{
  uint32_t *fld_e30; // esi
  int fld_e161; // eax
  int v4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 608))(this) == 0 )
    return 0;
  fld_e30 = (uint32_t *)*(this + 30);
  if ( fld_e30 == nullptr )
    return 0;
  if ( fld_e30[37] == -1 )
    sub_4938F0(*(this + 30));
  if ( (fld_e161 = fld_e30[34]) != 0
    && (fld_e30[35] - fld_e161) / 24 != 0
    && (*((uint8_t *)this + 642) == 0 ? (v4 = sub_4A2C40(this)) : (v4 = *(this + 161)), v4 != 2) )
  {
    return 1;
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
int /*thiscall*/ sub_4A2C40(int *this)
{
  int fld_e30; // esi

  fld_e30 = *(this + 30);
  if ( fld_e30 == 0 )
    return 0;
  if ( *(uint32_t *)(fld_e30 + 148) == -1 )
    sub_4938F0(*(this + 30));
  return *(uint32_t *)(fld_e30 + 112);
}



// ------------------------------------------------------------
// 0x4A2C70 sub_4A2C70
// ------------------------------------------------------------
// 【解读】
//   【推断】链表节点逐项释放（stdcall，Block = 链头）—— 循环 free，供 0x4A2DE0 清链。
// ------------------------------------------------------------
char /*stdcall*/ sub_4A2C70(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4A2C70(i[2]);
    i = (void **)*i;
    j__free(Block2);
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
char /*stdcall*/ sub_4A2CB0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4A2CB0(i[2]);
    i = (void **)*i;
    j__free(Block2);
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
uint32_t *sub_4A2CF0()
{
  uint32_t *result; // eax

  result = operator new(0x10u);
  if ( result != nullptr )
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
uint32_t *sub_4A2D10()
{
  uint32_t *result; // eax

  result = operator new(0x14u);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4A2D30 sub_4A2D30 [RTTI: IRDCollisionObject__vmt180 · 槽位 IRDActiveObject+180,IRDCollisionObject+180] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt180 —— 槽数组 getter（+348 起，越界返回 0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2D30(uint32_t *this, unsigned int uArg2)
{
  int fld_e87; // edx

  fld_e87 = *(this + 87);
  if ( fld_e87 != 0 && uArg2 < (*(this + 88) - fld_e87) >> 2 )
    return *(uint32_t *)(*(this + 87) + 4 * uArg2);
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
unsigned int /*thiscall*/ sub_4A2D70(int this, int nArg2)
{
  int fld_1BA4; // ecx
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_1BA42; // ecx

  *(uint8_t *)(this + 641) = nArg2;
  fld_1BA4 = *(uint32_t *)(this + 7076);
  if ( fld_1BA4 != 0 )
  {
    result = (*(uint32_t *)(this + 7080) - fld_1BA4) >> 2;
    if ( result != 0 )
    {
      for ( i = 0; ; ++i )
      {
        fld_1BA42 = *(uint32_t *)(this + 7076);
        if ( fld_1BA42 == 0 )
          break;
        result = (*(uint32_t *)(this + 7080) - fld_1BA42) >> 2;
        if ( i >= result )
          break;
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_1BA42 + 4 * i) + 604))(*(uint32_t *)(fld_1BA42 + 4 * i), nArg2);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2DE0 sub_4A2DE0 [RTTI: IRDCollisionObject__vmt160 · 槽位 IRDActiveObject+160,IRDCollisionObject+160] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt160 —— 命中列表双链表清空
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A2DE0(uint32_t *this)
{
  uint32_t *pThis_87; // esi
  uint32_t *v3; // eax
  uint32_t *result; // eax

  pThis_87 = this + 135;
  sub_4A2C70(*(void ***)(*(this + 136) + 4));
  *(uint32_t *)(pThis_87[1] + 4) = pThis_87[1];
  v3 = (uint32_t *)pThis_87[1];
  pThis_87[2] = 0;
  *v3 = v3;
  *(uint32_t *)(pThis_87[1] + 8) = pThis_87[1];
  sub_4A2CB0(*(void ***)(*(this + 150) + 4));
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
void /*thiscall*/ sub_4A2E50(int this)
{
  if ( *(uint32_t *)(this + 64) != 0 )
    j__free(*(void **)(this + 64));
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4A2EB0 sub_4A2EB0
// ------------------------------------------------------------
// 【解读】
//   【推断】单个 MSVC std::string 析构（容量 >= 0x10 则 free 堆缓冲，复位为空短串）。
//   被 0x4A3870/0x4A4170 用作"数组元素批量析构"的单位函数（元素步长 152 字节）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2EB0(int this)
{
  if ( *(uint32_t *)(this + 116) >= 0x10u )
    j__free(*(void **)(this + 96));
  *(uint32_t *)(this + 116) = 15;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 96) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4A2EE0 sub_4A2EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】48 字节固定头部 + 双向链表的初始化器（本文件 +0 处 200/1 等常数）。
//   【待验证】字段: +0=200、+4=1000、+18(int)=50 —— 与属性块默认值风格一致。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A2EE0(char *this)
{
  char *pThis_54; // esi
  uint32_t *result; // eax

  *(uint32_t *)this = 200;
  *(this + 8) = 1;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 38) = 0;
  *(this + 37) = 0;
  *(this + 36) = 0;
  *(this + 14) = 0;
  *(this + 13) = 0;
  *(this + 12) = 0;
  *(this + 11) = 0;
  *((uint32_t *)this + 1) = 1000;
  *(uint32_t *)(this + 15) = 0;
  *(uint32_t *)(this + 19) = 0;
  *(uint32_t *)(this + 23) = 0;
  *(uint32_t *)(this + 27) = 0;
  *(uint32_t *)(this + 31) = 0;
  *(this + 35) = 0;
  *((uint32_t *)this + 20) = 1000;
  pThis_54 = this + 84;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 18) = 50;
  *((uint32_t *)this + 19) = 0;
  *(this + 39) = 0;
  *((uint32_t *)this + 10) = 0;
  sub_41CAA0(*(void ***)(*((uint32_t *)this + 22) + 4));
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 4) = *((uint32_t *)pThis_54 + 1);
  result = *((uint32_t **)pThis_54 + 1);
  *((uint32_t *)pThis_54 + 2) = 0;
  *result = result;
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 8) = *((uint32_t *)pThis_54 + 1);
  return result;
}



// ------------------------------------------------------------
// 0x4A2F80 sub_4A2F80
// ------------------------------------------------------------
// 【解读】
//   【推断】按名字查找链表节点（std::map 风格遍历 + sub_40BF00 字符串比较）。
//   找到返回节点 [3]（值），未找到返回 -1。MSVC std::map<CString,int> 的查找模板实例。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2F80(uint32_t *this, const char *pArg2)
{
  uint32_t *fld_e1; // eax
  uint32_t *v3; // ebx
  bool v4; // zf
  uint32_t *v7; // [esp+10h] [ebp-4h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);
  v3 = (uint32_t *)*fld_e1;
  v4 = *fld_e1 == (uint32_t)fld_e1;
  v7 = (uint32_t *)*fld_e1;
  if ( v4 )
    return -1;
  while ( sub_40BF00((std::_String_base *)(v3 + 4), 0, v3[9], pArg2, strlen(pArg2)) != 0 )
  {
    sub_40BEA0((int *)&v7);
    v3 = v7;
    if ( v7 == (uint32_t *)*(this + 1) )
      return -1;
  }
  return v3[3];
}



// ------------------------------------------------------------
// 0x4A2FF0 sub_4A2FF0
// ------------------------------------------------------------
// 【解读】
//   【推断】结构体清零 + 两个 vector 释放（MSVC vector 三指针布局 @+40/+56）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A2FF0(void *this)
{
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  if ( *((uint32_t *)this + 10) != 0 )
    j__free(*((void **)this + 10));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  if ( *((uint32_t *)this + 14) != 0 )
    j__free(*((void **)this + 14));
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x4A3050 sub_4A3050
// ------------------------------------------------------------
// 【解读】
//   【推断】大结构体清零（2×104 字节 memset + 头尾字段）—— 尺寸约 288 字节。
//   【待验证】与 0x4A3EB0 的 72 DWORD 拷贝对应（同为 288 字节对象）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3050(int this)
{
  uint32_t *pThis_118; // esi

  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  memset((void *)(this + 72), 0, 0x68u);
  memset((void *)(this + 176), 0, 0x68u);
  pThis_118 = (uint32_t *)(this + 280);
  *pThis_118 = 0;
  pThis_118[1] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4A30C0 sub_4A30C0
// ------------------------------------------------------------
// 【解读】
//   【推断】std::length_error 抛出桩（"vector<T> too long"）—— MSVC 模板实例。
//   被 0x4A3570/0x4A35C0 在 a2 > 0x15555555（12 字节元素的最大容量）时调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_4A30C0()
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
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
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
int ***/*thiscall*/ sub_4A3130(uint32_t *this, int ***uArg2, int **pDwArg3)
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
    sub_401740(v20);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);
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
        v9 = (int *)sub_52E300(v4);
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
        *(uint32_t *)(v23 + 8) = sub_542490(v4);
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
            sub_433130(v6);
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
              sub_4296E0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);
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
              sub_433130(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);
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
  j__free(Block);
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
  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)this + 1, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  if ( *((uint32_t *)this + 12) != 0 )
    j__free(*((void **)this + 12));
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  if ( *((uint32_t *)this + 16) != 0 )
    j__free(*((void **)this + 16));
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
}



// ------------------------------------------------------------
// 0x4A3450 sub_4A3450
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 攻击上下文默认构造（IRDCollisionObject +388 属；被 IRDActiveObject_vmt158 调用）。
//   IRDCollisionObject.h 记录: "vmt158 攻击上下文设置（sub_4B2970 拷贝 / sub_4A3450 默认）"。
//   本函数即"默认"分支。初值: +5=4、+6/+7/+8=17、+19 字节=1、+21/+22=1120403456(=75.0f)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3450(uint32_t *this)
{
  int result; // eax

  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *((uint8_t *)this + 16) = 0;
  *((uint8_t *)this + 17) = 0;
  *((uint8_t *)this + 18) = 0;
  *((uint8_t *)this + 19) = 1;
  *(this + 5) = 4;
  *(this + 9) = 0;
  *(this + 12) = 0;
  *(this + 10) = 0;
  *(this + 13) = 0;
  *(this + 11) = 0;
  *(this + 14) = 0;
  *(this + 6) = 17;
  *(this + 7) = 17;
  *(this + 8) = 17;
  *(this + 15) = 1;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *((uint8_t *)this + 80) = 0;
  *((uint8_t *)this + 81) = 0;
  *((uint8_t *)this + 82) = 0;
  *(this + 21) = 1120403456;
  *(this + 22) = 1120403456;
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint8_t *)this + 128) = 0;
  *((uint8_t *)this + 140) = 0;
  *((uint8_t *)this + 141) = 0;
  *(this + 36) = 0;
  *(this + 30) = 1;
  *(this + 31) = 4;
  *(this + 33) = -1;
  *(this + 34) = -1082130432;
  *(this + 37) = 1120403456;
  return result;
}



// ------------------------------------------------------------
// 0x4A3520 sub_4A3520
// ------------------------------------------------------------
// 【解读】
//   【推断】攻击上下文重置（string 复位 + 0x4A3450 默认值）—— 复合重置器。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3520(int this)
{
  *(uint32_t *)(this + 116) = 15;
  *(uint32_t *)(this + 112) = 0;
  *(uint8_t *)(this + 96) = 0;
  sub_4A3450((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4A3570 sub_4A3570
// ------------------------------------------------------------
// 【解读】
//   【推断】12 字节元素 vector 的 reserve（a2 > 0x15555555 抛 length_error）。
//   【推断】元素 = 12 字节三元组（坐标/向量点）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A3570(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x15555555 )
    sub_4A30C0();
  pMem = (char *)operator new(12 * uArg2);
  *(this + 3) = &pMem[12 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4A35C0 sub_4A35C0
// ------------------------------------------------------------
// 【解读】
//   【推断】与 0x4A3570 同构的第二个 reserve（另一元素类型/容器）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4A35C0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x7FFFFFF )
    sub_4A30C0();
  pMem = (char *)operator new(32 * uArg2);
  *(this + 3) = &pMem[32 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4A3610 sub_4A3610
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树递归析构（后序 free，MSVC _Tree 模板）—— 与 0x4A36D0 成对实现两种节点类型。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4A3610(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
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
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_4A2C70(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
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
        sub_4A3130(this, (int ***)&pDwArg3, v10);
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
int **/*thiscall*/ sub_4A36D0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
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
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_4A2CB0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
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
        sub_4A3130(this, (int ***)&pDwArg3, v10);
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
int /*thiscall*/ sub_4A3790(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4A3610((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4A37D0 sub_4A37D0
// ------------------------------------------------------------
// 【解读】
//   【推断】含 CString + vector 的对象重置（先清 15/16 容量串，再 sub_4A33F0 初始化）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A37D0(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  sub_4A33F0((void *)this);  // 【std::map/std::set 红黑树模板实例族（MSVC _Tree）】
  return this;
}



// ------------------------------------------------------------
// 0x4A3830 sub_4A3830
// ------------------------------------------------------------
// 【解读】
//   【推断】vector<T> 释放（sub_41DA40 逐元素析构 + free）—— MSVC vector 模板。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3830(int ***this)
{
  int ***pThis_15; // esi
  int *v3; // [esp+4h] [ebp-4h] BYREF

  pThis_15 = this + 21;
  sub_41DA40(this + 21, &v3, **(this + 22), (int *)*(this + 22));
  j__free(pThis_15[1]);
  pThis_15[1] = nullptr;
  pThis_15[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4A3870 sub_4A3870
// ------------------------------------------------------------
// 【解读】
//   【推断】152 字节步长数组的元素批量析构（每元素 = 一个含 string 的结构，见 0x4A2EB0）。
// ------------------------------------------------------------
int /*stdcall*/ sub_4A3870(int nArg1, int nArg2)
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
uint32_t */*thiscall*/ sub_4A38A0(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *pThis_47; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_47 = this + 71;
  *(this + 71) = *pArg2;
  sub_4014D0(this + 72, pArg2 + 1, 0, 0xFFFFFFFF);
  pThis_47[8] = pArg2[8];
  pThis_47[9] = pArg2[9];
  pThis_47[10] = pArg2[10];
  sub_4ED3F0((int)(pThis_47 + 11), (int)(pArg2 + 11));
  sub_4ED3F0((int)(pThis_47 + 15), (int)(pArg2 + 15));
  return pThis_47;
}



// ------------------------------------------------------------
// 0x4A3900 sub_4A3900 [RTTI: IRDCollisionObject__vmt164 · 槽位 IRDActiveObject+164,IRDCollisionObject+164] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt164 —— 记录当前命中目标（研究已定案）
// ------------------------------------------------------------
// 【解读】
//   【推断】命中记录写入（IRDCollisionObject_vmt164，研究已定案）。
//   流程: 目标对象 vt+380 取记录值 → sub_4A3940 在红黑树中取槽 → 回写。
// ------------------------------------------------------------
void /*stdcall*/ sub_4A3900(int nArg1)
{
  int pObj; // esi
  uint32_t *v2; // edi

  pObj = nArg1;
  if ( nArg1 != 0 )
  {
    nArg1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 380))(nArg1);
    v2 = (uint32_t *)sub_4A3940(&nArg1);
    *v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 380))(pObj);
  }
}



// ------------------------------------------------------------
// 0x4A3940 sub_4A3940
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树 lower_bound 式查找/插入（命中记录树的取槽器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3940(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *uArg22; // edi
  int v4; // eax
  uint32_t v6[2]; // [esp+8h] [ebp-8h] BYREF

  uArg22 = uArg2;
  v4 = sub_4A3990(uArg2);
  if ( v4 == *(this + 1) || *uArg22 < *(uint32_t *)(v4 + 12) )
  {
    v6[0] = *uArg22;
    v6[1] = 0;
    v4 = *(uint32_t *)sub_4A39C0(&uArg2, v4, v6);
  }
  return v4 + 16;
}



// ------------------------------------------------------------
// 0x4A3990 sub_4A3990
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树查找（+21 红黑标志，键 @+12）—— MSVC _Tree::lower_bound 模板实例。
// ------------------------------------------------------------
int */*thiscall*/ sub_4A3990(uint32_t *this, uint32_t *uArg2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      result = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A39C0 sub_4A39C0
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树插入重平衡（MSVC _Tree::_Insert 模板实例；多条旋转分支）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A39C0(uint32_t *this, uint32_t *uArg2, int pArg3, uint32_t *uArg4)
{
  int fld_e2; // eax
  uint32_t *fld_e1; // eax
  int v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-Ch] BYREF
  int fld_e12; // [esp+10h] [ebp-4h] BYREF

  fld_e2 = *(this + 2);
  fld_e12 = 0;
  if ( fld_e2 == 0 )
  {
    sub_4A3B90(uArg2, 1, *(this + 1), uArg4);
    return uArg2;
  }
  fld_e1 = (uint32_t *)*(this + 1);
  if ( pArg3 == *fld_e1 )
  {
    if ( *uArg4 < *(uint32_t *)(pArg3 + 12) )
    {
      sub_4A3B90(uArg2, 1, pArg3, uArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( (uint32_t *)pArg3 == fld_e1 )
  {
    v8 = fld_e1[2];
    if ( *(uint32_t *)(v8 + 12) < *uArg4 )
    {
      sub_4A3B90(uArg2, 0, v8, uArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *uArg4 >= *(uint32_t *)(pArg3 + 12) || (fld_e12 = pArg3, sub_4A3B30(&fld_e12), *(uint32_t *)(fld_e12 + 12) >= *uArg4) )
  {
    if ( *(uint32_t *)(pArg3 + 12) >= *uArg4 || (fld_e12 = pArg3, sub_41C5E0(&fld_e12), fld_e12 != *(this + 1)) && *uArg4 >= *(uint32_t *)(fld_e12 + 12) )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4A3D40(v10, uArg4);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(*(uint32_t *)(pArg3 + 8) + 21) != 0 )
      sub_4A3B90(uArg2, 0, pArg3, uArg4);
    else
      sub_4A3B90(uArg2, 1, fld_e12, uArg4);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(*(uint32_t *)(fld_e12 + 8) + 21) != 0 )
      sub_4A3B90(uArg2, 0, fld_e12, uArg4);
    else
      sub_4A3B90(uArg2, 1, pArg3, uArg4);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4A3B30 sub_4A3B30
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树迭代器自减（MSVC _Tree::iterator-- 模板实例）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3B30(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 21) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
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
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 21) == 0 );
        if ( *(uint8_t *)(result + 21) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 21) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
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
uint32_t */*thiscall*/ sub_4A3B90(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
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

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )
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
            sub_433130(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
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
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4A3D40 sub_4A3D40
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树插入查找点（返回可插入位置）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3D40(uint32_t *this, int pArg2, uint32_t *uArg3)
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
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4A3B90(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4A3B90(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4A3E00 sub_4A3E00
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树容器清理（调 0x4A36D0 版析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3E00(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4A36D0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
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

  pThis_54 = this + 84;
  pThis_542 = sub_433AC0(this + 84);
  *((uint32_t *)pThis_54 + 1) = pThis_542;
  *(uint8_t *)(pThis_542 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 4) = *((uint32_t *)pThis_54 + 1);
  **((uint32_t **)pThis_54 + 1) = *((uint32_t *)pThis_54 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_54 + 1) + 8) = *((uint32_t *)pThis_54 + 1);
  *((uint32_t *)pThis_54 + 2) = 0;
  sub_4A2EE0(this);
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
uint32_t */*thiscall*/ sub_4A3EB0(uint32_t *this, char *pszArg2)
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
  sub_4A3F80(pszArg2);
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
  v3 = pThis_710 + 18;
  v4 = pszArg2 - (char *)pThis_710;
  for ( i = 26; i != 0; --i )
  {
    *v3 = *(uint32_t *)((char *)v3 + v4);
    ++v3;
  }
  v6 = pThis_710 + 44;
  for ( j = 26; j != 0; --j )
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
int /*thiscall*/ sub_4A3F80(int this, int pArg2)
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
  v4 = *(uint32_t *)(pArg2 + 4);
  if ( v4 == 0 || (v18 = *(uint32_t **)(pArg2 + 8), (v5 = ((int)v18 - v4) / 12) == 0) )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 12;
  else
    fld_8 = 0;
  if ( v5 > fld_8 )
  {
    if ( fld_4 != nullptr )
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 12;
    else
      fld_C = 0;
    if ( v5 > fld_C )
    {
      if ( fld_4 != nullptr )
        j__free(*(void **)(this + 4));
      v17 = *(uint32_t *)(pArg2 + 4);
      if ( v17 != 0 )
        v17 = (int)(*(uint32_t *)(pArg2 + 8) - v17) / 12;
      if ( sub_4A3570((uint32_t *)this, v17) == 0 )
        return this;
      fld_42 = sub_59EE30(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));
    }
    else
    {
      if ( fld_4 != nullptr )
        fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) / 12;
      else
        fld_82 = 0;
      v14 = *(uint32_t *)(pArg2 + 4) + 12 * fld_82;
      v15 = *(uint32_t **)(pArg2 + 4);
      fld_43 = *(uint32_t *)(this + 4);
      if ( v15 != (uint32_t *)v14 )
      {
        do
        {
          *fld_4 = *v15;
          fld_4[1] = v15[1];
          fld_4[2] = v15[2];
          fld_4 = (uint32_t *)(fld_43 + 12);
          v15 += 3;
          fld_43 += 12;
        }
        while ( v15 != (uint32_t *)v14 );
        pArg22 = pArg2;
      }
      fld_42 = sub_59EE30(v14, *(uint32_t *)(pArg22 + 8), *(uint32_t *)(this + 8));
    }
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  v9 = *(uint32_t **)(pArg2 + 4);
  for ( i = *(uint32_t *)(this + 4); v9 != v18; i += 12 )
  {
    *fld_4 = *v9;
    fld_4[1] = v9[1];
    fld_4[2] = v9[2];
    fld_4 = (uint32_t *)(i + 12);
    v9 += 3;
  }
  v10 = *(uint32_t *)(pArg22 + 4);
  if ( v10 != 0 )
    fld_44 = *(uint32_t *)(this + 4) + 12 * ((*(uint32_t *)(pArg22 + 8) - v10) / 12);
  else
    fld_44 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = fld_44;
  return this;
}



// ------------------------------------------------------------
// 0x4A4170 sub_4A4170
// ------------------------------------------------------------
// 【解读】
//   【推断】152 字节步长数组的析构+释放（每元素走 0x4A2EB0，与 0x4A3870 配对）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4170(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 152 )
      sub_4A2EB0(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
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
int /*thiscall*/ sub_4A41C0(int this, int pArg2)
{
  int pThis_1D60; // esi
  uint8_t *pThis_1D73; // ecx
  int i; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_1D60 = this + 7520;
  *(uint32_t *)(this + 7520) = *(uint32_t *)pArg2;
  *(uint32_t *)(this + 7524) = *(uint32_t *)(pArg2 + 4);
  *(uint8_t *)(this + 7528) = *(uint8_t *)(pArg2 + 8);
  *(uint8_t *)(this + 7529) = *(uint8_t *)(pArg2 + 9);
  *(uint8_t *)(this + 7530) = *(uint8_t *)(pArg2 + 10);
  *(uint8_t *)(this + 7531) = *(uint8_t *)(pArg2 + 11);
  *(uint8_t *)(this + 7532) = *(uint8_t *)(pArg2 + 12);
  *(uint8_t *)(this + 7533) = *(uint8_t *)(pArg2 + 13);
  *(uint8_t *)(this + 7534) = *(uint8_t *)(pArg2 + 14);
  *(uint8_t *)(this + 7535) = *(uint8_t *)(pArg2 + 15);
  *(uint8_t *)(this + 7536) = *(uint8_t *)(pArg2 + 16);
  *(uint8_t *)(this + 7537) = *(uint8_t *)(pArg2 + 17);
  *(uint8_t *)(this + 7538) = *(uint8_t *)(pArg2 + 18);
  pThis_1D73 = (uint8_t *)(this + 7539);
  for ( i = 17; i != 0; --i )
  {
    *pThis_1D73 = pThis_1D73[pArg2 - pThis_1D60];
    ++pThis_1D73;
  }
  *(uint8_t *)(pThis_1D60 + 36) = *(uint8_t *)(pArg2 + 36);
  *(uint8_t *)(pThis_1D60 + 37) = *(uint8_t *)(pArg2 + 37);
  *(uint8_t *)(pThis_1D60 + 38) = *(uint8_t *)(pArg2 + 38);
  *(uint8_t *)(pThis_1D60 + 39) = *(uint8_t *)(pArg2 + 39);
  *(uint32_t *)(pThis_1D60 + 40) = *(uint32_t *)(pArg2 + 40);
  *(uint32_t *)(pThis_1D60 + 44) = *(uint32_t *)(pArg2 + 44);
  *(uint32_t *)(pThis_1D60 + 48) = *(uint32_t *)(pArg2 + 48);
  *(uint32_t *)(pThis_1D60 + 52) = *(uint32_t *)(pArg2 + 52);
  *(uint32_t *)(pThis_1D60 + 56) = *(uint32_t *)(pArg2 + 56);
  *(uint32_t *)(pThis_1D60 + 60) = *(uint32_t *)(pArg2 + 60);
  *(uint32_t *)(pThis_1D60 + 64) = *(uint32_t *)(pArg2 + 64);
  *(uint32_t *)(pThis_1D60 + 68) = *(uint32_t *)(pArg2 + 68);
  *(uint32_t *)(pThis_1D60 + 72) = *(uint32_t *)(pArg2 + 72);
  *(uint32_t *)(pThis_1D60 + 76) = *(uint32_t *)(pArg2 + 76);
  *(uint32_t *)(pThis_1D60 + 80) = *(uint32_t *)(pArg2 + 80);
  sub_4A42B0(pArg2 + 84);
  return pThis_1D60;
}



// ------------------------------------------------------------
// 0x4A42B0 sub_4A42B0
// ------------------------------------------------------------
// 【解读】
//   【推断】关联容器赋值（sub_41DA40 清旧 + 0x4A42E0 建新）—— MSVC map operator= 模板。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4A42B0(int ***this, int ***uArg2)
{
  int ***uArg22; // edi

  uArg22 = uArg2;
  if ( this != uArg2 )
  {
    sub_41DA40(this, (int **)&uArg2, **(this + 1), (int *)*(this + 1));
    sub_4A42E0(uArg22);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4A42E0 sub_4A42E0
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树拷贝（_Copy 模板实例，重挂根 + 极值指针修正）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4A42E0(int ***this, int pArg2)
{
  int fld_e1; // edi
  int **fld_e12; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_e13; // esi
  int **v8; // ecx

  fld_e1 = (int)*(this + 1);
  *(uint32_t *)(fld_e1 + 4) = sub_4A4370(*(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4), fld_e1);
  *(this + 2) = *(int ***)(pArg2 + 8);
  fld_e12 = *(this + 1);
  result = fld_e12[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *fld_e12 = (int *)fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
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
    *fld_e12 = result;
    fld_e13 = (int)*(this + 1);
    v8 = *(int ***)(fld_e13 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_e13 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A4370 sub_4A4370
// ------------------------------------------------------------
// 【解读】
//   【推断】红黑树递归复制（_Copy 模板的递归体，sub_5648C0 分配结点）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4370(void **this, int *pDwArg2, int nArg3)
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)pDwArg2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = (uint32_t *)sub_5648C0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 20));
    if ( *((uint8_t *)Block + 21) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_4A4370(v6, fld_e1);
    fld_e1[2] = sub_4A4370(pDwArg2[2], fld_e1);
  }
  return Block;
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
uint32_t */*thiscall*/ sub_4A4430(uint32_t *this)
{
  int pThis_87; // eax
  int pThis_95; // eax

  sub_42AAB0();
  *this = &IRDCollisionObject::`vftable';
  sub_4A37D0((int)(this + 71));
  *(this + 96) = 15;
  *(this + 95) = 0;
  *((uint8_t *)this + 364) = 0;
  *(this + 126) = 15;
  *(this + 125) = 0;
  *((uint8_t *)this + 484) = 0;
  sub_4A3450(this + 97);
  pThis_87 = sub_433AC0(this + 135);
  *(this + 136) = pThis_87;
  *(uint8_t *)(pThis_87 + 21) = 1;
  *(uint32_t *)(*(this + 136) + 4) = *(this + 136);
  *(uint32_t *)*(this + 136) = *(this + 136);
  *(uint32_t *)(*(this + 136) + 8) = *(this + 136);
  *(this + 137) = 0;
  *(this + 139) = 0;
  *(this + 140) = 0;
  *(this + 141) = 0;
  pThis_95 = sub_433AC0(this + 149);
  *(this + 150) = pThis_95;
  *(uint8_t *)(pThis_95 + 21) = 1;
  *(uint32_t *)(*(this + 150) + 4) = *(this + 150);
  *(uint32_t *)*(this + 150) = *(this + 150);
  *(uint32_t *)(*(this + 150) + 8) = *(this + 150);
  *(this + 151) = 0;
  *(this + 156) = 0;
  *(this + 157) = 0;
  *(this + 158) = 0;
  *(this + 164) = 0;
  *(this + 165) = 0;
  *(this + 166) = 0;
  sub_4E7160((int)this);
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
char /*thiscall*/ sub_4A4560(uint8_t *this, char pszArg2)
{
  *(this + 641) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4A4570 sub_4A4570 [RTTI: IRDCollisionObject__vmt288 · 槽位 IRDCollisionObject+288] [已精修] 见 src/cnrd/IRDCollisionObject.cpp vmt288 —— 写入 100（格挡/减伤基础值槽）
// ------------------------------------------------------------
int /*stdcall*/ sub_4A4570(uint32_t *uArg1, int nArg2)
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
int /*thiscall*/ sub_4A4590(int this)
{
  int *v3; // [esp-Ch] [ebp-28h]
  int *v4; // [esp-Ch] [ebp-28h]
  int *fld_258; // [esp-8h] [ebp-24h]
  int *fld_220; // [esp-8h] [ebp-24h]
  int *v7[2]; // [esp+8h] [ebp-14h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  v7[1] = (int *)this;
  *(uint32_t *)this = &IRDCollisionObject::`vftable';
  v8 = 8;
  nullsub_3(this);
  if ( *(uint32_t *)(this + 656) != 0 )
    j__free(*(void **)(this + 656));
  *(uint32_t *)(this + 656) = 0;
  *(uint32_t *)(this + 660) = 0;
  *(uint32_t *)(this + 664) = 0;
  if ( *(uint32_t *)(this + 624) != 0 )
    j__free(*(void **)(this + 624));
  *(uint32_t *)(this + 624) = 0;
  *(uint32_t *)(this + 628) = 0;
  *(uint32_t *)(this + 632) = 0;
  fld_258 = *(int **)(this + 600);
  v3 = (int *)*fld_258;
  LOBYTE(v8) = 5;
  sub_4A36D0((int ***)(this + 596), v7, v3, fld_258);
  j__free(*(void **)(this + 600));
  *(uint32_t *)(this + 600) = 0;
  *(uint32_t *)(this + 604) = 0;
  sub_4A4170((int *)(this + 552));
  fld_220 = *(int **)(this + 544);
  v4 = (int *)*fld_220;
  LOBYTE(v8) = 3;
  sub_4A3610((int ***)(this + 540), v7, v4, fld_220);
  j__free(*(void **)(this + 544));
  *(uint32_t *)(this + 544) = 0;
  *(uint32_t *)(this + 548) = 0;
  if ( *(uint32_t *)(this + 504) >= 0x10u )
    j__free(*(void **)(this + 484));
  *(uint32_t *)(this + 504) = 15;
  *(uint32_t *)(this + 500) = 0;
  *(uint8_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 384) >= 0x10u )
    j__free(*(void **)(this + 364));
  *(uint32_t *)(this + 384) = 15;
  *(uint32_t *)(this + 380) = 0;
  *(uint8_t *)(this + 364) = 0;
  sub_4A2E50(this + 284);
  v8 = -1;
  return sub_42A450(this);
}



// ------------------------------------------------------------
// 0x4A4710 sub_4A4710 [RTTI: IRDCollisionObject__vmt0 · 槽位 IRDCollisionObject+0] [已精修] 见 src/cnrd/IRDCollisionObject.h vmt0 —— IRDCollisionObject 析构 → 0x4A4590
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4710(void *Block, char pszArg2)
{
  sub_4A4590((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
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
unsigned int /*thiscall*/ sub_4A4740(int this)
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
    sub_42AF90(*(void ***)this);
    sub_657740(v2, 228);
  }
  fld_4 = *(void ***)(this + 4);
  *(uint32_t *)this = 0;
  if ( fld_4 != nullptr )
  {
    sub_42AF90(fld_4);
    sub_657740(fld_4, 228);
  }
  fld_8 = *(void ***)(this + 8);
  *(uint32_t *)(this + 4) = 0;
  if ( fld_8 != nullptr )
  {
    sub_42AF90(fld_8);
    sub_657740(fld_8, 228);
  }
  *(uint32_t *)(this + 8) = 0;
  pThis_C = (void ***)(this + 12);
  v18 = 2;
  do
  {
    v6 = *pThis_C;
    if ( *pThis_C != nullptr )
    {
      sub_42AF90(*pThis_C);
      sub_657740(v6, 228);
    }
    *pThis_C++ = nullptr;
    result = v18 - 1;
    v18 = result;
  }
  while ( result != 0 );
  fld_14 = *(uint32_t *)(this + 20);
  v9 = 0;
  if ( fld_14 != 0 )
  {
    sub_42AF90(*(void ***)(this + 20));
    result = sub_657740(fld_14, 228);
  }
  fld_18 = *(void ***)(this + 24);
  *(uint32_t *)(this + 20) = 0;
  if ( fld_18 != nullptr )
  {
    sub_42AF90(fld_18);
    result = sub_657740(fld_18, 228);
  }
  fld_1C = *(void ***)(this + 28);
  *(uint32_t *)(this + 24) = 0;
  if ( fld_1C != nullptr )
  {
    sub_42AF90(fld_1C);
    result = sub_657740(fld_1C, 228);
  }
  fld_20 = *(void ***)(this + 32);
  *(uint32_t *)(this + 28) = 0;
  if ( fld_20 != nullptr )
  {
    sub_42AF90(fld_20);
    result = sub_657740(fld_20, 228);
  }
  *(uint32_t *)(this + 32) = 0;
  while ( 1 )
  {
    fld_28 = *(uint32_t *)(this + 40);
    if ( fld_28 == 0 )
      break;
    result = (*(uint32_t *)(this + 44) - fld_28) >> 2;
    if ( v9 >= result )
      break;
    v14 = *(void ***)(fld_28 + 4 * v9);
    if ( v14 != nullptr )
    {
      v19 = v14;
      sub_42AF90(v14);
      sub_657740(v19, 228);
    }
    result = 4 * v9 + *(uint32_t *)(this + 40);
    *(uint32_t *)result = 0;
    ++v9;
  }
  for ( i = 0; ; ++i )
  {
    fld_38 = *(uint32_t *)(this + 56);
    if ( fld_38 == 0 )
      break;
    result = (*(uint32_t *)(this + 60) - fld_38) >> 2;
    if ( i >= result )
      break;
    v17 = *(void ***)(fld_38 + 4 * i);
    if ( v17 != nullptr )
    {
      v20 = v17;
      sub_42AF90(v17);
      sub_657740(v20, 228);
    }
    result = 4 * i + *(uint32_t *)(this + 56);
    *(uint32_t *)result = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4A4940 sub_4A4940
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4A4740 的收尾（再补两个 vector 释放）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4A4940(int this)
{
  sub_4A4740(this);
  if ( *(uint32_t *)(this + 56) != 0 )
    j__free(*(void **)(this + 56));
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  if ( *(uint32_t *)(this + 40) != 0 )
    j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
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
int /*thiscall*/ sub_4A49B0(int this)
{
  sub_4A4430((uint32_t *)this);
  *(uint32_t *)this = &IRDActiveObject::`vftable';
  `eh vector constructor iterator'(
    (void *)(this + 676),
    0x554u,
    4,
    (void (/*thiscall*/ *)(void *))sub_4A1670,
    (void (/*thiscall*/ *)(void *))sub_4A1F00);
  sub_4A1C30((uint32_t *)(this + 6132));
  *(uint32_t *)(this + 6200) = 0;
  *(uint32_t *)(this + 6204) = 0;
  *(uint32_t *)(this + 6208) = 0;
  *(uint32_t *)(this + 6216) = 0;
  *(uint32_t *)(this + 6220) = 0;
  *(uint32_t *)(this + 6224) = 0;
  sub_4A2FF0((void *)(this + 6160));
  *(uint32_t *)(this + 6304) = 0;
  *(uint32_t *)(this + 6308) = 0;
  *(uint32_t *)(this + 6312) = 0;
  *(uint32_t *)(this + 6432) = 15;
  *(uint32_t *)(this + 6428) = 0;
  *(uint8_t *)(this + 6412) = 0;
  sub_4A3450((uint32_t *)(this + 6316));
  *(uint32_t *)(this + 6544) = sub_4A2CF0();
  *(uint32_t *)(this + 6548) = 0;
  *(uint8_t *)(this + 6564) = 0;
  *(uint32_t *)(this + 6560) = &off_6C2B88;
  *(uint32_t *)(this + 6568) = 0;
  *(uint8_t *)(this + 6572) = 1;
  *(uint8_t *)(this + 6574) = 0;
  *(uint8_t *)(this + 6573) = 0;
  *(uint32_t *)(this + 6584) = 0;
  *(uint32_t *)(this + 6580) = 0;
  *(uint32_t *)(this + 6576) = 0;
  *(uint32_t *)(this + 6736) = 15;
  *(uint32_t *)(this + 6732) = 0;
  *(uint8_t *)(this + 6716) = 0;
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
  sub_41A630(this + 7028);
  *(uint32_t *)(this + 7028) = &clong::`vftable';
  *(uint32_t *)(this + 7068) = 15;
  *(uint32_t *)(this + 7064) = 0;
  *(uint8_t *)(this + 7048) = 0;
  *(uint32_t *)(this + 7076) = 0;
  *(uint32_t *)(this + 7080) = 0;
  *(uint32_t *)(this + 7084) = 0;
  *(uint8_t *)(this + 7120) = 0;
  *(uint32_t *)(this + 7116) = &off_6C2B88;
  *(uint32_t *)(this + 7124) = 0;
  *(uint8_t *)(this + 7128) = 1;
  *(uint8_t *)(this + 7130) = 0;
  *(uint8_t *)(this + 7129) = 0;
  *(uint32_t *)(this + 7140) = 0;
  *(uint32_t *)(this + 7136) = 0;
  *(uint32_t *)(this + 7132) = 0;
  sub_4D46C0((uint32_t *)this);
  sub_4D7140(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A4BD0 sub_4A4BD0
// ------------------------------------------------------------
// 【解读】
//   【推断】IRDActiveObject 析构（RTTI 直证）。sub_4D7000 先做战斗段清理，
//   再释放 +7076 附属物 vector 与 +7048 串 —— 与 0x4A4E70（vmt0 壳）配对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4BD0(int this)
{
  *(uint32_t *)this = &IRDActiveObject::`vftable';
  sub_4D7000((uint32_t *)this);
  *(uint32_t *)(this + 7116) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 7120) = 0;
  if ( *(uint32_t *)(this + 7076) != 0 )
    j__free(*(void **)(this + 7076));
  *(uint32_t *)(this + 7076) = 0;
  *(uint32_t *)(this + 7080) = 0;
  *(uint32_t *)(this + 7084) = 0;
  if ( *(uint32_t *)(this + 7068) >= 0x10u )
    j__free(*(void **)(this + 7048));
  *(uint32_t *)(this + 7068) = 15;
  *(uint32_t *)(this + 7064) = 0;
  *(uint8_t *)(this + 7048) = 0;
  sub_41A580((uint32_t *)(this + 7028));
  if ( *(uint32_t *)(this + 7024) >= 0x10u )
    j__free(*(void **)(this + 7004));
  *(uint32_t *)(this + 7024) = 15;
  *(uint32_t *)(this + 7020) = 0;
  *(uint8_t *)(this + 7004) = 0;
  if ( *(uint32_t *)(this + 6984) >= 0x10u )
    j__free(*(void **)(this + 6964));
  *(uint32_t *)(this + 6984) = 15;
  *(uint32_t *)(this + 6980) = 0;
  *(uint8_t *)(this + 6964) = 0;
  if ( *(uint32_t *)(this + 6956) >= 0x10u )
    j__free(*(void **)(this + 6936));
  *(uint32_t *)(this + 6956) = 15;
  *(uint32_t *)(this + 6952) = 0;
  *(uint8_t *)(this + 6936) = 0;
  if ( *(uint32_t *)(this + 6928) >= 0x10u )
    j__free(*(void **)(this + 6908));
  *(uint32_t *)(this + 6928) = 15;
  *(uint32_t *)(this + 6924) = 0;
  *(uint8_t *)(this + 6908) = 0;
  if ( *(uint32_t *)(this + 6860) >= 0x10u )
    j__free(*(void **)(this + 6840));
  *(uint32_t *)(this + 6860) = 15;
  *(uint32_t *)(this + 6856) = 0;
  *(uint8_t *)(this + 6840) = 0;
  if ( *(uint32_t *)(this + 6788) >= 0x10u )
    j__free(*(void **)(this + 6768));
  *(uint32_t *)(this + 6788) = 15;
  *(uint32_t *)(this + 6784) = 0;
  *(uint8_t *)(this + 6768) = 0;
  if ( *(uint32_t *)(this + 6736) >= 0x10u )
    j__free(*(void **)(this + 6716));
  *(uint32_t *)(this + 6736) = 15;
  *(uint32_t *)(this + 6732) = 0;
  *(uint8_t *)(this + 6716) = 0;
  *(uint32_t *)(this + 6560) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 6564) = 0;
  sub_6569D0(this + 6540);
  j__free(*(void **)(this + 6544));
  *(uint32_t *)(this + 6544) = 0;
  if ( *(uint32_t *)(this + 6432) >= 0x10u )
    j__free(*(void **)(this + 6412));
  *(uint32_t *)(this + 6432) = 15;
  *(uint32_t *)(this + 6428) = 0;
  *(uint8_t *)(this + 6412) = 0;
  sub_4A4170((int *)(this + 6300));
  sub_4A4940(this + 6160);
  sub_41A580((uint32_t *)(this + 6146));
  sub_41A580((uint32_t *)(this + 6132));
  `eh vector destructor iterator'((void *)(this + 676), 0x554u, 4, (void (/*thiscall*/ *)(void *))sub_4A1F00);
  return sub_4A4590(this);
}



// ------------------------------------------------------------
// 0x4A4E70 sub_4A4E70 [RTTI: IRDActiveObject__vmt0 · 槽位 IRDActiveObject+0]
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4E70(void *Block, char pszArg2)
{
  sub_4A4BD0((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
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
char */*thiscall*/ sub_4A4EA0(char *this, char ArgList, int nArg3)
{
  sub_4A49B0((int)this);
  *(uint32_t *)this = &IRDMonster::`vftable';
  *((uint32_t *)this + 1794) = 15;
  *((uint32_t *)this + 1793) = 0;
  *(this + 7156) = 0;
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
  sub_4A3050((int)(this + 7232));
  sub_4A3E40(this + 7520);  // 【红黑树容器构造/拷贝族 + 288 字节对象深拷贝】
  *((uint32_t *)this + 1905) = 0;
  *((uint32_t *)this + 1906) = 0;
  *((uint32_t *)this + 1907) = 0;
  *(this + 7644) = 0;
  *((uint32_t *)this + 1910) = &off_6C2B88;
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
  *((uint32_t *)this + 1952) = 0;
  *((uint32_t *)this + 1953) = 0;
  *((uint32_t *)this + 1954) = 0;
  `eh vector constructor iterator'(this + 7824, 0x10u, 29, (void (/*thiscall*/ *)(void *))sub_4019A0, sub_401940);
  *((uint32_t *)this + 2085) = 0;
  *((uint32_t *)this + 2086) = 0;
  *((uint32_t *)this + 2087) = 0;
  *(this + 8492) = 0;
  *((uint32_t *)this + 2122) = &off_6C2B88;
  *((uint32_t *)this + 2124) = 0;
  *(this + 8500) = 1;
  *(this + 8502) = 0;
  *(this + 8501) = 0;
  *((uint32_t *)this + 2128) = 0;
  *((uint32_t *)this + 2127) = 0;
  *((uint32_t *)this + 2126) = 0;
  *((uint32_t *)this + 2138) = 15;
  *((uint32_t *)this + 2137) = 0;
  *(this + 8532) = 0;
  *(this + 8560) = 0;
  *((uint32_t *)this + 2139) = &off_6C2B88;
  *((uint32_t *)this + 2141) = 0;
  *(this + 8568) = 1;
  *(this + 8570) = 0;
  *(this + 8569) = 0;
  *((uint32_t *)this + 2145) = 0;
  *((uint32_t *)this + 2144) = 0;
  *((uint32_t *)this + 2143) = 0;
  sub_4DE700(this);
  sub_4DB410(ArgList, nArg3);
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
int /*thiscall*/ sub_4A50F0(int this)
{
  int *v3; // [esp-8h] [ebp-28h]
  int *fld_1DB8; // [esp-4h] [ebp-24h]
  int *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &IRDMonster::`vftable';
  v6 = 13;
  sub_4E3360();
  *(uint32_t *)(this + 8556) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8560) = 0;
  if ( *(uint32_t *)(this + 8552) >= 0x10u )
    j__free(*(void **)(this + 8532));
  *(uint32_t *)(this + 8552) = 15;
  *(uint32_t *)(this + 8548) = 0;
  *(uint8_t *)(this + 8532) = 0;
  *(uint32_t *)(this + 8488) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8492) = 0;
  if ( *(uint32_t *)(this + 8340) != 0 )
    j__free(*(void **)(this + 8340));
  *(uint32_t *)(this + 8340) = 0;
  *(uint32_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8348) = 0;
  LOBYTE(v6) = 8;
  `eh vector destructor iterator'((void *)(this + 7824), 0x10u, 29, sub_401940);
  if ( *(uint32_t *)(this + 7808) != 0 )
    j__free(*(void **)(this + 7808));
  *(uint32_t *)(this + 7808) = 0;
  *(uint32_t *)(this + 7812) = 0;
  *(uint32_t *)(this + 7816) = 0;
  if ( *(uint32_t *)(this + 7760) >= 0x10u )
    j__free(*(void **)(this + 7740));
  *(uint32_t *)(this + 7760) = 15;
  *(uint32_t *)(this + 7756) = 0;
  *(uint8_t *)(this + 7740) = 0;
  *(uint32_t *)(this + 7640) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 7644) = 0;
  if ( *(uint32_t *)(this + 7620) != 0 )
    j__free(*(void **)(this + 7620));
  *(uint32_t *)(this + 7620) = 0;
  *(uint32_t *)(this + 7624) = 0;
  *(uint32_t *)(this + 7628) = 0;
  fld_1DB8 = *(int **)(this + 7608);
  v3 = (int *)*fld_1DB8;
  LOBYTE(v6) = 3;
  sub_41DA40((int ***)(this + 7604), v5, v3, fld_1DB8);
  j__free(*(void **)(this + 7608));
  *(uint32_t *)(this + 7608) = 0;
  *(uint32_t *)(this + 7612) = 0;
  if ( *(uint32_t *)(this + 7236) != 0 )
    j__free(*(void **)(this + 7236));
  *(uint32_t *)(this + 7236) = 0;
  *(uint32_t *)(this + 7240) = 0;
  *(uint32_t *)(this + 7244) = 0;
  if ( *(uint32_t *)(this + 7224) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 7224));
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
  if ( *(uint32_t *)(this + 7176) >= 0x10u )
    j__free(*(void **)(this + 7156));
  *(uint32_t *)(this + 7176) = 15;
  *(uint32_t *)(this + 7172) = 0;
  *(uint8_t *)(this + 7156) = 0;
  v6 = -1;
  return sub_4A4BD0(this);
}



// ------------------------------------------------------------
// 0x4A5350 sub_4A5350
// ------------------------------------------------------------
// 【解读】
//   【推断】析构壳（调 0x4A50F0 + 可选 free）= 某个怪物类的 vmt0。
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5350(void *Block, char pszArg2)
{
  sub_4A50F0((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
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
char */*thiscall*/ sub_4A5380(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNFighterIllusion::`vftable';
  sub_5908C0(this);
  sub_5908E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A53E0 sub_4A53E0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A53E0(void *Block, char pszArg2)
{
  sub_4A5410();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5410 sub_4A5410
// ------------------------------------------------------------
// 【解读】
//   【推断】CNFighterIllusion 析构（vftable 复位 + 0x4A50F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5410(uint32_t *this)
{
  *this = &CNFighterIllusion::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5460 sub_4A5460
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNProvocationDoll（嘲讽人偶）构造（含 a4 参数传递 sub_590F30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5460(char *this, char ArgList, int nArg3, int nArg4)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNProvocationDoll::`vftable';
  sub_590E70(this);
  sub_590F30(nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x4A54C0 sub_4A54C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A54C0(void *Block, char pszArg2)
{
  sub_4A54F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A54F0 sub_4A54F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNProvocationDoll 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A54F0(uint32_t *this)
{
  *this = &CNProvocationDoll::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5540 sub_4A5540
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKeraha 构造（sub_5913F0/592650）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5540(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNKeraha::`vftable';
  sub_5913F0(this);
  sub_592650(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A55A0 sub_4A55A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A55A0(void *Block, char pszArg2)
{
  sub_4A55D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A55D0 sub_4A55D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNKeraha 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A55D0(uint32_t *this)
{
  *this = &CNKeraha::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5620 sub_4A5620
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNVinoshu 构造（sub_5928E0/593FF0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5620(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNVinoshu::`vftable';
  sub_5928E0(this);
  sub_593FF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5680 sub_4A5680
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5680(void *Block, char pszArg2)
{
  sub_4A56B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A56B0 sub_4A56B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNVinoshu 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A56B0(uint32_t *this)
{
  *this = &CNVinoshu::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5700 sub_4A5700
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLuis 构造（sub_592BF0/593680）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5700(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNLuis::`vftable';
  sub_592BF0(this);
  sub_593680(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5760 sub_4A5760
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5760(void *Block, char pszArg2)
{
  sub_4A5790();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5790 sub_4A5790
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLuis 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5790(uint32_t *this)
{
  *this = &CNLuis::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A57E0 sub_4A57E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLugaru 构造（sub_594340/594B10）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A57E0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNLugaru::`vftable';
  sub_594340(this);
  sub_594B10(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5840 sub_4A5840
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLugaru 析构（sub_4E3360 = 战斗段公共清理，见多处怪物析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5840(uint32_t *this)
{
  *this = &CNLugaru::`vftable';
  sub_4E3360();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5890 sub_4A5890
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLugaru 析构壳。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A5890(uint32_t *Block, char pszArg2)
{
  sub_4A5840(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A58C0 sub_4A58C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGardener_Ral（园丁拉尔）构造 —— 继承 CNLugaru。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A58C0(int this, char ArgList, int nArg3)
{
  sub_4A57E0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNGardener_Ral::`vftable';
  *(uint32_t *)(this + 8632) = 0;
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
int /*thiscall*/ sub_4A58F0(int *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e2158; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (int)sub_445870(88771231, 100) < 10 )
  {
    fld_e2158 = *(this + 2158);
    *(this + 2158) = fld_e2158 + 1;
    if ( fld_e2158 < 3 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
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
    sub_4D82D0(0, 0);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GDRAL_01", -1, 0, 0);
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x4A59B0 sub_4A59B0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A59B0(void *Block, char pszArg2)
{
  sub_4A59E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A59E0 sub_4A59E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGardener_Ral 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A59E0(uint32_t *this)
{
  *this = &CNGardener_Ral::`vftable';
  return sub_4A5840(this);
}



// ------------------------------------------------------------
// 0x4A59F0 sub_4A59F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBlackLugaru（黑拉鲁）构造（sub_594F90/595470）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A59F0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNBlackLugaru::`vftable';
  sub_594F90(this);
  sub_595470(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5A50 sub_4A5A50
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5A50(void *Block, char pszArg2)
{
  sub_4A5A80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5A80 sub_4A5A80
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBlackLugaru 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5A80(uint32_t *this)
{
  *this = &CNBlackLugaru::`vftable';
  sub_4E3360();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5AD0 sub_4A5AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWhiteLugaru（白拉鲁）构造（sub_595E10/596990）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5AD0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNWhiteLugaru::`vftable';
  sub_595E10(this);
  sub_596990(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5B30 sub_4A5B30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5B30(void *Block, char pszArg2)
{
  sub_4A5B60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5B60 sub_4A5B60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWhiteLugaru 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5B60(uint32_t *this)
{
  *this = &CNWhiteLugaru::`vftable';
  sub_4E3360();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5BB0 sub_4A5BB0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPenril 构造（sub_598350/598200）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5BB0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNPenril::`vftable';
  sub_598350(this);
  sub_598200(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5C10 sub_4A5C10
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5C10(void *Block, char pszArg2)
{
  sub_4A5C40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5C40 sub_4A5C40
// ------------------------------------------------------------
// 【解读】
//   【推断】CNPenril 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5C40(uint32_t *this)
{
  *this = &CNPenril::`vftable';
  sub_4E3360();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5C90 sub_4A5C90
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBloodLugaru（血拉鲁）构造（+8656 标志字节 / +8652 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5C90(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNBloodLugaru::`vftable';
  *(uint8_t *)(this + 8656) = 0;
  *(uint32_t *)(this + 8652) = &off_6C2B88;
  *(uint32_t *)(this + 8660) = 0;
  *(uint8_t *)(this + 8664) = 1;
  *(uint8_t *)(this + 8666) = 0;
  *(uint8_t *)(this + 8665) = 0;
  *(uint32_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8672) = 0;
  *(uint32_t *)(this + 8668) = 0;
  sub_598350(this);
  sub_5993F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5D30 sub_4A5D30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5D30(void *Block, char pszArg2)
{
  sub_4A5D60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5D60 sub_4A5D60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBloodLugaru 析构（含 nengine::IObject @+8652 复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5D60(uint32_t *this)
{
  *this = &CNBloodLugaru::`vftable';
  sub_4E3360();
  *(this + 2163) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8656) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A5DC0 sub_4A5DC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblin 族构造共享前缀 —— 写 CNGoblinCommon vftable 于 +8600，
//   +8604=0 / +8605=1。**这是全哥布林族的"第二 vftable"位置（this+8600）之直证**，
//   解释了大量 *(this+2150) = &CNGoblinXXX::vftable 的写法（2150*4 = 8600）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5DC0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinStoner::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinStoner::`vftable';
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  sub_59D760(this);
  sub_5998E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5E70 sub_4A5E70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinStoner 析构壳（this−8600 回退到对象头，多继承布局修正）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5E70(char *this, char pszArg2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A5EB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A5EB0 sub_4A5EB0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinStoner 析构（双 vftable 复位 + string 释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5EB0(int this)
{
  *(uint32_t *)this = &CNGoblinStoner::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinStoner::`vftable';
  if ( *(uint32_t *)(this + 8652) >= 0x10u )
    j__free(*(void **)(this + 8632));
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A5F10 sub_4A5F10
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第二版，参数不同）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5F10(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinGoblin::`vftable';
  *(uint32_t *)(this + 8600) = &off_6D0E8C;
  *(uint32_t *)(this + 8648) = 15;
  *(uint32_t *)(this + 8644) = 0;
  *(uint8_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8676) = 15;
  *(uint32_t *)(this + 8672) = 0;
  *(uint8_t *)(this + 8656) = 0;
  sub_599AE0(this);
  sub_59A990(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5FF0 sub_4A5FF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinGoblin 析构（双 vftable；+8600 的 vftable 换为 off_6D0E8C）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A5FF0(int this)
{
  *(uint32_t *)this = &CNGoblinGoblin::`vftable';
  *(uint32_t *)(this + 8600) = &off_6D0E8C;
  nullsub_3(this);
  if ( *(uint32_t *)(this + 8676) >= 0x10u )
    j__free(*(void **)(this + 8656));
  *(uint32_t *)(this + 8676) = 15;
  *(uint32_t *)(this + 8672) = 0;
  *(uint8_t *)(this + 8656) = 0;
  if ( *(uint32_t *)(this + 8648) >= 0x10u )
    j__free(*(void **)(this + 8628));
  *(uint32_t *)(this + 8648) = 15;
  *(uint32_t *)(this + 8644) = 0;
  *(uint8_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A60C0 sub_4A60C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A60C0(void *Block, char pszArg2)
{
  sub_4A5FF0((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A60F0 sub_4A60F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinAssaulter 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A60F0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A5F10((int)this, ArgList, nArg3);
  *this = &CNGoblinAssaulter::`vftable';
  *(this + 2150) = &CNGoblinAssaulter::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A6130 sub_4A6130
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6130(void *Block, char pszArg2)
{
  sub_4A6160();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6160 sub_4A6160
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinAssaulter 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6160(int this)
{
  *(uint32_t *)this = &CNGoblinAssaulter::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinAssaulter::`vftable';
  return sub_4A5FF0(this);
}



// ------------------------------------------------------------
// 0x4A6180 sub_4A6180
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinHodor 构造（+8708 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6180(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A5F10((int)this, ArgList, nArg3);
  *this = &CNGoblinHodor::`vftable';
  *(this + 2150) = &CNGoblinHodor::`vftable';
  *((uint8_t *)this + 8708) = 0;
  *(this + 2176) = &off_6C2B88;
  *(this + 2178) = 0;
  *((uint8_t *)this + 8716) = 1;
  *((uint8_t *)this + 8718) = 0;
  *((uint8_t *)this + 8717) = 0;
  *(this + 2182) = 0;
  *(this + 2181) = 0;
  *(this + 2180) = 0;
  sub_599D50(this);
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6230 sub_4A6230
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6230(char *this, char pszArg2)
{
  return sub_4A6240(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A6240 sub_4A6240
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6240(void *Block, char pszArg2)
{
  sub_4A6270();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6270 sub_4A6270
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinHodor 析构（含 IObject @+8704）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6270(int this)
{
  *(uint32_t *)this = &CNGoblinHodor::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinHodor::`vftable';
  *(uint32_t *)(this + 8704) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8708) = 0;
  return sub_4A5FF0(this);
}



// ------------------------------------------------------------
// 0x4A62A0 sub_4A62A0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第三版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A62A0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinKinol::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinKinol::`vftable';
  *(uint32_t *)(this + 8636) = 15;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8664) = 15;
  *(uint32_t *)(this + 8660) = 0;
  *(uint8_t *)(this + 8644) = 0;
  nullsub_3(this);
  sub_59B8A0(this);
  sub_59BE40(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6370 sub_4A6370
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6370(char *this, char pszArg2)
{
  return sub_4A6450(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A6380 sub_4A6380
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinKinol 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6380(int this)
{
  *(uint32_t *)this = &CNGoblinKinol::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinKinol::`vftable';
  sub_4E3360();
  if ( *(uint32_t *)(this + 8664) >= 0x10u )
    j__free(*(void **)(this + 8644));
  *(uint32_t *)(this + 8664) = 15;
  *(uint32_t *)(this + 8660) = 0;
  *(uint8_t *)(this + 8644) = 0;
  if ( *(uint32_t *)(this + 8636) >= 0x10u )
    j__free(*(void **)(this + 8616));
  *(uint32_t *)(this + 8636) = 15;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6450 sub_4A6450
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6450(void *Block, char pszArg2)
{
  sub_4A6380((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6480 sub_4A6480
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBunker_Woker 构造（sub_59BF90）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6480(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A62A0((int)this, ArgList, nArg3);
  *this = &CNBunker_Woker::`vftable';
  *(this + 2150) = &CNBunker_Woker::`vftable';
  sub_59BF90(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A64F0 sub_4A64F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A64F0(void *Block, char pszArg2)
{
  sub_4A6520();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6520 sub_4A6520
// ------------------------------------------------------------
// 【解读】
//   【推断】CNBunker_Woker 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6520(int this)
{
  *(uint32_t *)this = &CNBunker_Woker::`vftable';
  *(uint32_t *)(this + 8600) = &CNBunker_Woker::`vftable';
  return sub_4A6380(this);
}



// ------------------------------------------------------------
// 0x4A6540 sub_4A6540
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEliteGoblin 构造（+8680 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6540(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A62A0((int)this, ArgList, nArg3);
  *this = &CNEliteGoblin::`vftable';
  *(this + 2150) = &CNEliteGoblin::`vftable';
  *((uint8_t *)this + 8680) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A6580 sub_4A6580
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKingGalok 构造（继承 CNEliteGoblin 前缀布局，+8680 清零）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A6580(uint8_t *this, char ArgList, int nArg3)
{
  sub_4A62A0((int)this, ArgList, nArg3);
  *(this + 8680) = 0;
  *(uint32_t *)this = &CNKingGalok::`vftable';
  *((uint32_t *)this + 2150) = &CNKingGalok::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A65C0 sub_4A65C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A65C0(char *this, char pszArg2)
{
  return sub_4A65D0(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A65D0 sub_4A65D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A65D0(void *Block, char pszArg2)
{
  sub_4A6600();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6600 sub_4A6600
// ------------------------------------------------------------
// 【解读】
//   【推断】CNEliteGoblin 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6600(int this)
{
  *(uint32_t *)this = &CNEliteGoblin::`vftable';
  *(uint32_t *)(this + 8600) = &CNEliteGoblin::`vftable';
  return sub_4A6380(this);
}



// ------------------------------------------------------------
// 0x4A6620 sub_4A6620
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第四版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6620(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinGero::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinGero::`vftable';
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  sub_59C440(this);
  sub_59CEC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A66D0 sub_4A66D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A66D0(char *this, char pszArg2)
{
  return sub_4A6780(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A66E0 sub_4A66E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinGero 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A66E0(int this)
{
  *(uint32_t *)this = &CNGoblinGero::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinGero::`vftable';
  sub_4E3360();
  if ( *(uint32_t *)(this + 8652) >= 0x10u )
    j__free(*(void **)(this + 8632));
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6780 sub_4A6780
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6780(void *Block, char pszArg2)
{
  sub_4A66E0((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A67B0 sub_4A67B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPrag 构造（+8620 = 30076 动作 ID 常量）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A67B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6620((int)this, ArgList, nArg3);
  *this = &CNPrag::`vftable';
  *(this + 2150) = &CNPrag::`vftable';
  *(this + 2155) = 30076;
  *(this + 2167) = 30023;
  return this;
}



// ------------------------------------------------------------
// 0x4A67F0 sub_4A67F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A67F0(char *this, char pszArg2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6830();
  if ( (pszArg2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6830 sub_4A6830
// ------------------------------------------------------------
// 【解读】
//   【推断】CNPrag 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6830(int this)
{
  *(uint32_t *)this = &CNPrag::`vftable';
  *(uint32_t *)(this + 8600) = &CNPrag::`vftable';
  return sub_4A66E0(this);
}



// ------------------------------------------------------------
// 0x4A6850 sub_4A6850
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第五版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6850(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinMountainGab::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinMountainGab::`vftable';
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  sub_59D760(this);
  sub_59D4D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6900 sub_4A6900
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6900(char *this, char pszArg2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6940();
  if ( (pszArg2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6940 sub_4A6940
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinMountainGab 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6940(int this)
{
  *(uint32_t *)this = &CNGoblinMountainGab::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinMountainGab::`vftable';
  sub_4E3360();
  if ( *(uint32_t *)(this + 8652) >= 0x10u )
    j__free(*(void **)(this + 8632));
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A69E0 sub_4A69E0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第六版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A69E0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinIslandGab::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinIslandGab::`vftable';
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  sub_59D760(this);
  sub_59D8F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6A90 sub_4A6A90
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6A90(char *this, char pszArg2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6AD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6AD0 sub_4A6AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinIslandGab 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6AD0(int this)
{
  *(uint32_t *)this = &CNGoblinIslandGab::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinIslandGab::`vftable';
  sub_4E3360();
  if ( *(uint32_t *)(this + 8652) >= 0x10u )
    j__free(*(void **)(this + 8632));
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6B70 sub_4A6B70
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第七版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6B70(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinLupete::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinLupete::`vftable';
  *(uint32_t *)(this + 8660) = 15;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8640) = 0;
  sub_59DB80(this);
  sub_59E230(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6C20 sub_4A6C20
// ------------------------------------------------------------
char */*thiscall*/ sub_4A6C20(char *this, char pszArg2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6C60();
  if ( (pszArg2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6C60 sub_4A6C60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinLupete 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6C60(int this)
{
  *(uint32_t *)this = &CNGoblinLupete::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinLupete::`vftable';
  sub_4E3360();
  if ( *(uint32_t *)(this + 8660) >= 0x10u )
    j__free(*(void **)(this + 8640));
  *(uint32_t *)(this + 8660) = 15;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6D00 sub_4A6D00
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第八版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6D00(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';
  sub_59E550(this);
  sub_59FC80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6DA0 sub_4A6DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6DA0(char *this, char pszArg2)
{
  return sub_4A6DB0(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A6DB0 sub_4A6DB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6DB0(void *Block, char pszArg2)
{
  sub_4A6F40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6DE0 sub_4A6DE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinKagelBase（哥布林炸弹/飞镖 Kagel 系基类）构造（+8648 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6DE0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6D00((int)this, ArgList, nArg3);
  *this = &CNGoblinKagelBase::`vftable';
  *(this + 2150) = &CNGoblinKagelBase::`vftable';
  *((uint8_t *)this + 8648) = 0;
  *(this + 2163) = 0;
  *((uint8_t *)this + 8658) = 0;
  *((uint8_t *)this + 8657) = 0;
  *(this + 2167) = 0;
  *(this + 2166) = 0;
  *(this + 2165) = 0;
  *(this + 2161) = &off_6C2B88;
  *((uint8_t *)this + 8656) = 1;
  *((uint8_t *)this + 8624) = 0;
  *(this + 2157) = 0;
  *(this + 2158) = 0;
  *((uint8_t *)this + 8636) = 0;
  *(this + 2160) = 0;
  *((uint8_t *)this + 8657) = 0;
  *((uint8_t *)this + 8658) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A6E80 sub_4A6E80
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinSharedoBase 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6E80(int this)
{
  *(uint32_t *)(this + 8644) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8648) = 0;
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6EB0 sub_4A6EB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6EB0(void *Block, char pszArg2)
{
  sub_4A6E80((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6EE0 sub_4A6EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinSharedo 构造（sub_5A0530）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6EE0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6D00((int)this, ArgList, nArg3);
  *this = &CNGoblinSharedo::`vftable';
  *(this + 2150) = &CNGoblinSharedo::`vftable';
  sub_5A0530(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6F40 sub_4A6F40
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinSharedoBase 析构（第二版，含 vftable 降级回 CNGoblinCommon 的细节）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A6F40(int this)
{
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A6F60 sub_4A6F60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinBombKagel 构造（sub_5A0780）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6F60(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6DE0(this, ArgList, nArg3);
  *this = &CNGoblinBombKagel::`vftable';
  *(this + 2150) = &CNGoblinBombKagel::`vftable';
  sub_5A0780(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6FD0 sub_4A6FD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6FD0(void *Block, char pszArg2)
{
  sub_4A7000();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7000 sub_4A7000
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinBombKagel 析构（含 IObject @+8644）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7000(uint32_t *this)
{
  *this = &CNGoblinBombKagel::`vftable';
  *(this + 2150) = &CNGoblinBombKagel::`vftable';
  sub_4E3360();
  *(this + 2161) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8648) = 0;
  *this = &CNGoblinSharedoBase::`vftable';
  *(this + 2150) = &CNGoblinSharedoBase::`vftable';
  *(this + 2150) = &CNGoblinCommon::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7090 sub_4A7090
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinSurikenKagel 构造（sub_5A0930）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7090(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6DE0(this, ArgList, nArg3);
  *this = &CNGoblinSurikenKagel::`vftable';
  *(this + 2150) = &CNGoblinSurikenKagel::`vftable';
  sub_5A0930(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7100 sub_4A7100
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoblinBullsEye 构造（+8688 清零）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7100(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A6DE0(this, ArgList, nArg3);
  *this = &CNGoblinBullsEye::`vftable';
  *(this + 2150) = &CNGoblinBullsEye::`vftable';
  *(this + 2172) = 0;
  *(this + 2173) = 0;
  *(this + 2174) = 0;
  sub_5A0AE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7180 sub_4A7180
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7180(char *this, char pszArg2)
{
  return sub_4A7190(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A7190 sub_4A7190
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7190(void *Block, char pszArg2)
{
  sub_4A71C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A71C0 sub_4A71C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoblinBullsEye 析构（含对 +8704 对象的 vt 调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A71C0(int this)
{
  void (/*thiscall*/ ***pThis_2200)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGoblinBullsEye::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinBullsEye::`vftable';
  pThis_2200 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8704);
  if ( pThis_2200 != nullptr )
    (**pThis_2200)(pThis_2200, 1);
  *(uint32_t *)(this + 8704) = 0;
  if ( *(uint32_t *)(this + 8688) != 0 )
    j__free(*(void **)(this + 8688));
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8644) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8648) = 0;
  *(uint32_t *)this = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinSharedoBase::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A7280 sub_4A7280
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第九版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7280(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNLightningKinol::`vftable';
  *(uint32_t *)(this + 8600) = &CNLightningKinol::`vftable';
  sub_5A0D00(this);
  sub_5A1D20(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7320 sub_4A7320
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7320(char *this, char pszArg2)
{
  return sub_4A7330(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A7330 sub_4A7330
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7330(void *Block, char pszArg2)
{
  sub_4A7360();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7360 sub_4A7360
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLightningKinol 析构相关。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7360(uint32_t *this)
{
  *this = &CNLightningKinol::`vftable';
  *(this + 2150) = &CNLightningKinol::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNGoblinCommon::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A73D0 sub_4A73D0
// ------------------------------------------------------------
// 【解读】
//   【推断】哥布林族构造共享前缀（第十版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A73D0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNGoblinCommon::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 1;
  *(uint32_t *)(this + 8608) = rand() % 5000 + 3000;
  *(uint32_t *)this = &CNCowardGoblin::`vftable';
  *(uint32_t *)(this + 8600) = &CNCowardGoblin::`vftable';
  sub_5A2020(this);
  sub_5A2A50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7470 sub_4A7470
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7470(char *this, char pszArg2)
{
  return sub_4A7480(this - 8600, pszArg2);
}



// ------------------------------------------------------------
// 0x4A7480 sub_4A7480
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7480(void *Block, char pszArg2)
{
  sub_4A74B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A74B0 sub_4A74B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCowardGoblin（怯懦哥布林）析构相关（sub_5A20C0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A74B0(uint32_t *this)
{
  *this = &CNCowardGoblin::`vftable';
  *(this + 2150) = &CNCowardGoblin::`vftable';
  sub_5A20C0();
  *(this + 2150) = &CNGoblinCommon::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7520 sub_4A7520
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauArmy（牛头人军团）构造 —— 先写 CNTauFriendShip 再写本类。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7520(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';
  *(uint32_t *)this = &CNTauArmy::`vftable';
  *(uint32_t *)(this + 8600) = &CNTauArmy::`vftable';
  nullsub_3(this);
  sub_5A2F30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A75A0 sub_4A75A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A75A0(void *Block, char pszArg2)
{
  sub_4A75D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A75D0 sub_4A75D0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauArmy 析构（vftable 降级回 CNMonsterFriendShip）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A75D0(uint32_t *this)
{
  *this = &CNTauArmy::`vftable';
  *(this + 2150) = &CNTauArmy::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7640 sub_4A7640
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauBeast（牛头兽）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7640(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';
  *(uint32_t *)this = &CNTauBeast::`vftable';
  *(uint32_t *)(this + 8600) = &CNTauBeast::`vftable';
  sub_5AA340(this);
  sub_5A3510(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A76C0 sub_4A76C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A76C0(void *Block, char pszArg2)
{
  sub_4A76F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A76F0 sub_4A76F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauBeast 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A76F0(uint32_t *this)
{
  *this = &CNTauBeast::`vftable';
  *(this + 2150) = &CNTauBeast::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7760 sub_4A7760
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauAssaulter（牛头突击兵）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7760(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';
  *(uint32_t *)this = &CNTauAssaulter::`vftable';
  *(uint32_t *)(this + 8600) = &CNTauAssaulter::`vftable';
  sub_5A36E0(this);
  sub_5A3C80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A77E0 sub_4A77E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauAssaulter 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A77E0(uint32_t *this)
{
  *this = &CNTauAssaulter::`vftable';
  *(this + 2150) = &CNTauAssaulter::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7850 sub_4A7850
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7850(uint32_t *Block, char pszArg2)
{
  sub_4A77E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7880 sub_4A7880
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRock_Moud 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7880(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7760((int)this, ArgList, nArg3);
  *this = &CNRock_Moud::`vftable';
  *(this + 2150) = &CNRock_Moud::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A78B0 sub_4A78B0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A78B0(void *Block, char pszArg2)
{
  sub_4A78E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A78E0 sub_4A78E0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRock_Moud 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A78E0(uint32_t *this)
{
  *this = &CNRock_Moud::`vftable';
  *(this + 2150) = &CNRock_Moud::`vftable';
  return sub_4A77E0(this);
}



// ------------------------------------------------------------
// 0x4A7900 sub_4A7900
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauGuard（牛头卫兵）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7900(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';
  *(uint32_t *)this = &CNTauGuard::`vftable';
  *(uint32_t *)(this + 8600) = &CNTauGuard::`vftable';
  sub_5A3E50(this);
  sub_5A4E70(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7980 sub_4A7980
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7980(void *Block, char pszArg2)
{
  sub_4A79B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A79B0 sub_4A79B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauGuard 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A79B0(uint32_t *this)
{
  *this = &CNTauGuard::`vftable';
  *(this + 2150) = &CNTauGuard::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7A20 sub_4A7A20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTauTangas（牛头唐加斯）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7A20(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNTauFriendShip::`vftable';
  *(uint32_t *)this = &CNTauTangas::`vftable';
  *(uint32_t *)(this + 8600) = &CNTauTangas::`vftable';
  nullsub_3(this);
  sub_5A5990(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7AA0 sub_4A7AA0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7AA0(void *Block, char pszArg2)
{
  sub_4A7AD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7AD0 sub_4A7AD0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTauTangas 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7AD0(uint32_t *this)
{
  *this = &CNTauTangas::`vftable';
  *(this + 2150) = &CNTauTangas::`vftable';
  nullsub_3(this);
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7B40 sub_4A7B40
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolem（魔像族基类）构造（+8636=15/+8632 归零 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7B40(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNGolem::`vftable';
  *(uint32_t *)(this + 8636) = 15;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8616) = 0;
  sub_5A5BB0(this);
  sub_5A6EA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7BC0 sub_4A7BC0
// ------------------------------------------------------------
// 【解读】
//   【推断】含字符串常量 "STONE_DIE" 的分发调用 —— 魔像族死亡动画/音效触发。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7BC0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "STONE_DIE",
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
int /*thiscall*/ sub_4A7BE0(void **this)
{
  *this = &CNGolem::`vftable';
  sub_5A5BF0();
  if ( (unsigned int)*(this + 2159) >= 0x10 )
    j__free(*(this + 2154));
  *(this + 2159) = (void *)15;
  *(this + 2158) = nullptr;
  *((uint8_t *)this + 8616) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A7C60 sub_4A7C60
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7C60(void **Block, char pszArg2)
{
  sub_4A7BE0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7C90 sub_4A7C90
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemStone（石魔像）构造（sub_5A7770）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7C90(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7B40((int)this, ArgList, nArg3);
  *this = &CNGolemStone::`vftable';
  sub_5A7770(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7CF0 sub_4A7CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7CF0(void **this)
{
  *this = &CNGolemStone::`vftable';
  return sub_4A7BE0(this);
}



// ------------------------------------------------------------
// 0x4A7D00 sub_4A7D00
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7D00(void **Block, char pszArg2)
{
  sub_4A7CF0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7D30 sub_4A7D30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemSteel（钢魔像）构造（sub_5A78E0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7D30(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7B40((int)this, ArgList, nArg3);
  *this = &CNGolemSteel::`vftable';
  sub_5A78E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7D90 sub_4A7D90
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7D90(void **this)
{
  *this = &CNGolemSteel::`vftable';
  return sub_4A7BE0(this);
}



// ------------------------------------------------------------
// 0x4A7DA0 sub_4A7DA0
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A7DA0(void **Block, char pszArg2)
{
  sub_4A7D90(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7DD0 sub_4A7DD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemBronze（青铜魔像）构造（sub_5A7E30）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7DD0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7D30(this, ArgList, nArg3);
  *this = &CNGolemBronze::`vftable';
  sub_5A7E30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7E30 sub_4A7E30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemClay（陶土魔像）构造（sub_5A7B50）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7E30(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7B40((int)this, ArgList, nArg3);
  *this = &CNGolemClay::`vftable';
  sub_5A7B50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7E90 sub_4A7E90
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7E90(void *Block, char pszArg2)
{
  sub_4A7EC0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7EC0 sub_4A7EC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7EC0(void **this)
{
  *this = &CNGolemClay::`vftable';
  return sub_4A7BE0(this);
}



// ------------------------------------------------------------
// 0x4A7ED0 sub_4A7ED0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemGold（金魔像）构造（sub_5A7CC0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7ED0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7B40((int)this, ArgList, nArg3);
  *this = &CNGolemGold::`vftable';
  sub_5A7CC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7F30 sub_4A7F30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7F30(void *Block, char pszArg2)
{
  sub_4A7F60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7F60 sub_4A7F60
// ------------------------------------------------------------
int /*thiscall*/ sub_4A7F60(void **this)
{
  *this = &CNGolemGold::`vftable';
  return sub_4A7BE0(this);
}



// ------------------------------------------------------------
// 0x4A7F70 sub_4A7F70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGolemPlatany（白金魔像）构造（sub_5A80A0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7F70(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7B40((int)this, ArgList, nArg3);
  *this = &CNGolemPlatany::`vftable';
  sub_5A80A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7FD0 sub_4A7FD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7FD0(void *Block, char pszArg2)
{
  sub_4A8000();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8000 sub_4A8000
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8000(void **this)
{
  *this = &CNGolemPlatany::`vftable';
  return sub_4A7BE0(this);
}



// ------------------------------------------------------------
// 0x4A8010 sub_4A8010
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStoneBlade_Razor 构造（继承 CNGolemStone 前缀）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8010(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A7C90(this, ArgList, nArg3);
  *this = &CNStoneBlade_Razor::`vftable';
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
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNDollMaster::`vftable';
  sub_5A82B0(this);
  sub_5A9DA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A80A0 sub_4A80A0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDollMaster 析构（sub_5A8300）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A80A0(uint32_t *this)
{
  *this = &CNDollMaster::`vftable';
  sub_5A8300();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A80F0 sub_4A80F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A80F0(uint32_t *Block, char pszArg2)
{
  sub_4A80A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8120 sub_4A8120
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStoneMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8120(char *this, char ArgList, int nArg3)
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNStoneMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8150 sub_4A8150
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8150(void *Block, char pszArg2)
{
  sub_4A8180();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8180 sub_4A8180
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8180(uint32_t *this)
{
  *this = &CNStoneMaster::`vftable';
  return sub_4A80A0(this);
}



// ------------------------------------------------------------
// 0x4A8190 sub_4A8190
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSteelMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8190(char *this, char ArgList, int nArg3)
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNSteelMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A81C0 sub_4A81C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A81C0(void *Block, char pszArg2)
{
  sub_4A81F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A81F0 sub_4A81F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A81F0(uint32_t *this)
{
  *this = &CNSteelMaster::`vftable';
  return sub_4A80A0(this);
}



// ------------------------------------------------------------
// 0x4A8200 sub_4A8200
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNClayMaster 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8200(char *this, char ArgList, int nArg3)
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNClayMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8230 sub_4A8230
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8230(void *Block, char pszArg2)
{
  sub_4A8260();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8260 sub_4A8260
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8260(uint32_t *this)
{
  *this = &CNClayMaster::`vftable';
  return sub_4A80A0(this);
}



// ------------------------------------------------------------
// 0x4A8270 sub_4A8270
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNMasterDogri 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8270(char *this, char ArgList, int nArg3)
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNMasterDogri::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A82A0 sub_4A82A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A82A0(void *Block, char pszArg2)
{
  sub_4A82D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A82D0 sub_4A82D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A82D0(uint32_t *this)
{
  *this = &CNMasterDogri::`vftable';
  return sub_4A80A0(this);
}



// ------------------------------------------------------------
// 0x4A82E0 sub_4A82E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNIceDoll_Sharedo（冰人偶）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A82E0(char *this, char ArgList, int nArg3)
{
  sub_4A8040(this, ArgList, nArg3);  // 【怪物子类构造/析构批 B（CNDollMaster → CNIceDoll_Shar…】
  *(uint32_t *)this = &CNIceDoll_Sharedo::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8310 sub_4A8310
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8310(void *Block, char pszArg2)
{
  sub_4A8340();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8340 sub_4A8340
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8340(uint32_t *this)
{
  *this = &CNIceDoll_Sharedo::`vftable';
  return sub_4A80A0(this);
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
int /*thiscall*/ sub_4A8350(int this, char ArgList, int nArg3)
{
  int fld_2204; // eax
  unsigned int fld_2208; // edx
  uint32_t *fld_22082; // eax
  int fld_22042; // edx
  unsigned int fld_22083; // ecx
  uint32_t *fld_22084; // eax
  int fld_22043; // edx
  unsigned int fld_22085; // ecx
  uint32_t *fld_22086; // eax

  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNFlyDragon::`vftable';
  *(uint32_t *)(this + 8660) = 15;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8688) = 15;
  *(uint32_t *)(this + 8684) = 0;
  *(uint8_t *)(this + 8668) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  *(uint32_t *)(this + 8716) = 0;
  *(uint8_t *)(this + 8724) = 0;
  *(uint32_t *)(this + 8720) = &off_6C2B88;
  *(uint32_t *)(this + 8728) = 0;
  *(uint8_t *)(this + 8732) = 1;
  *(uint8_t *)(this + 8734) = 0;
  *(uint8_t *)(this + 8733) = 0;
  *(uint32_t *)(this + 8744) = 0;
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8736) = 0;
  *(uint8_t *)(this + 8752) = 0;
  *(uint32_t *)(this + 8748) = &off_6C2B88;
  *(uint32_t *)(this + 8756) = 0;
  *(uint8_t *)(this + 8760) = 1;
  *(uint8_t *)(this + 8762) = 0;
  *(uint8_t *)(this + 8761) = 0;
  *(uint32_t *)(this + 8772) = 0;
  *(uint32_t *)(this + 8768) = 0;
  *(uint32_t *)(this + 8764) = 0;
  nArg3 = 15;
  fld_2204 = *(uint32_t *)(this + 8708);
  if ( fld_2204 != 0 )
    fld_2208 = (*(uint32_t *)(this + 8712) - fld_2204) >> 2;
  else
    fld_2208 = 0;
  if ( fld_2204 != 0 && fld_2208 < (*(uint32_t *)(this + 8716) - fld_2204) >> 2 )
  {
    fld_22082 = *(uint32_t **)(this + 8712);
    *fld_22082 = 15;
    *(uint32_t *)(this + 8712) = fld_22082 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);
  }
  fld_22042 = *(uint32_t *)(this + 8708);
  nArg3 = 80;
  if ( fld_22042 != 0 )
    fld_22083 = (*(uint32_t *)(this + 8712) - fld_22042) >> 2;
  else
    fld_22083 = 0;
  if ( fld_22042 != 0 && fld_22083 < (*(uint32_t *)(this + 8716) - fld_22042) >> 2 )
  {
    fld_22084 = *(uint32_t **)(this + 8712);
    *fld_22084 = 80;
    *(uint32_t *)(this + 8712) = fld_22084 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);
  }
  fld_22043 = *(uint32_t *)(this + 8708);
  nArg3 = 135;
  if ( fld_22043 != 0 )
    fld_22085 = (*(uint32_t *)(this + 8712) - fld_22043) >> 2;
  else
    fld_22085 = 0;
  if ( fld_22043 != 0 && fld_22085 < (*(uint32_t *)(this + 8716) - fld_22043) >> 2 )
  {
    fld_22086 = *(uint32_t **)(this + 8712);
    *fld_22086 = 135;
    *(uint32_t *)(this + 8712) = fld_22086 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&nArg3);
  }
  sub_5A9FF0(this);
  sub_5AC500(this);
  *(uint8_t *)(this + 8733) = 0;
  *(uint8_t *)(this + 8734) = 0;
  *(uint8_t *)(this + 8701) = 0;
  *(uint8_t *)(this + 8700) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8560 sub_4A8560
// ------------------------------------------------------------
// 【解读】
//   【推断】CNFlyDragon 析构（含 IObject @+8748）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8560(int this)
{
  *(uint32_t *)this = &CNFlyDragon::`vftable';
  nullsub_3(this);
  *(uint32_t *)(this + 8748) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8752) = 0;
  *(uint32_t *)(this + 8720) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8724) = 0;
  if ( *(uint32_t *)(this + 8708) != 0 )
    j__free(*(void **)(this + 8708));
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  *(uint32_t *)(this + 8716) = 0;
  if ( *(uint32_t *)(this + 8688) >= 0x10u )
    j__free(*(void **)(this + 8668));
  *(uint32_t *)(this + 8688) = 15;
  *(uint32_t *)(this + 8684) = 0;
  *(uint8_t *)(this + 8668) = 0;
  if ( *(uint32_t *)(this + 8660) >= 0x10u )
    j__free(*(void **)(this + 8640));
  *(uint32_t *)(this + 8660) = 15;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8640) = 0;
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4A8650 sub_4A8650
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8650(void *Block, char pszArg2)
{
  sub_4A8560((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8680 sub_4A8680
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeSerimalion 构造（+8788 标志）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A8680(uint8_t *this, char ArgList, int nArg3)
{
  int pThis_5D4; // [esp+20h] [ebp+Ch]

  sub_4A8350((int)this, ArgList, nArg3);
  *(uint32_t *)this = &CNDrakeSerimalion::`vftable';
  *(this + 8788) = 0;
  *((uint32_t *)this + 2196) = &off_6C2B88;
  *((uint32_t *)this + 2198) = 0;
  *(this + 8796) = 1;
  *(this + 8798) = 0;
  *(this + 8797) = 0;
  *((uint32_t *)this + 2202) = 0;
  *((uint32_t *)this + 2201) = 0;
  *((uint32_t *)this + 2200) = 0;
  *((uint32_t *)this + 2194) = -1;
  pThis_5D4 = sub_41A5E0((unsigned int)(this + 1492));
  *((uint32_t *)this + 2195) = (uint64_t)((double)pThis_5D4 * COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 1506))));
  return this;
}



// ------------------------------------------------------------
// 0x4A8750 sub_4A8750
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8750(void *Block, char pszArg2)
{
  sub_4A8780();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8780 sub_4A8780
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeSerimalion 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8780(int this)
{
  *(uint32_t *)this = &CNDrakeSerimalion::`vftable';
  *(uint32_t *)(this + 8784) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8788) = 0;
  return sub_4A8560(this);
}



// ------------------------------------------------------------
// 0x4A87A0 sub_4A87A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeLooseSerimalion 构造（参数 void* Block 复用）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A87A0(uint8_t *this, char ArgList, void *Block)
{
  uint32_t *pMem; // eax

  sub_4A8350((int)this, ArgList, (int)Block);
  *(uint32_t *)this = &CNDrakeLooseSerimalion::`vftable';
  *(this + 8780) = 0;
  *((uint32_t *)this + 2194) = &off_6C2B88;
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
  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    *((uint32_t *)this + 2203) = sub_428F30(pMem, (int)"PassiveObject/Monster/FlyDragon/Particle/Bouncer.ptl", 0);
  else
    *((uint32_t *)this + 2203) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8890 sub_4A8890
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8890(void *Block, char pszArg2)
{
  sub_4A88C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A88C0 sub_4A88C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeLooseSerimalion 析构（含 +8812 指针的虚调）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A88C0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  *this = &CNDrakeLooseSerimalion::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 2203) = 0;
  *(this + 2194) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8780) = 0;
  return sub_4A8560((int)this);
}



// ------------------------------------------------------------
// 0x4A8940 sub_4A8940
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeHarseSerimalion 构造（+8780=-1/+8776=0 计时器初始化）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8940(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A8350((int)this, ArgList, nArg3);
  *this = &CNDrakeHarseSerimalion::`vftable';
  *(this + 2195) = -1;
  *(this + 2194) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8980 sub_4A8980
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8980(void *Block, char pszArg2)
{
  sub_4A89B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A89B0 sub_4A89B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeHarseSerimalion 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89B0(int this)
{
  *(uint32_t *)this = &CNDrakeHarseSerimalion::`vftable';
  return sub_4A8560(this);
}



// ------------------------------------------------------------
// 0x4A89C0 sub_4A89C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDrakeSelionTheFireBreather（喷火塞利昂）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89C0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNDrakeSelionTheFireBreather::`vftable';
  *(uint8_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8612) = &off_6C2B88;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8624) = 1;
  *(uint8_t *)(this + 8626) = 0;
  *(uint8_t *)(this + 8625) = 0;
  *(uint32_t *)(this + 8636) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8628) = 0;
  sub_5AA340(this);
  sub_5ACE30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8A60 sub_4A8A60
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8A60(void *Block, char pszArg2)
{
  sub_4A8A90();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8A90 sub_4A8A90
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDrakeSelionTheFireBreather 析构（sub_5AA350 + IObject @+8612）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8A90(uint32_t *this)
{
  *this = &CNDrakeSelionTheFireBreather::`vftable';
  sub_5AA350();
  *(this + 2153) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8616) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A8AF0 sub_4A8AF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunter（猎人）构造（+8648=15/+8644 归零 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8AF0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNHunter::`vftable';
  *(uint32_t *)(this + 8648) = 15;
  *(uint32_t *)(this + 8644) = 0;
  *(uint8_t *)(this + 8628) = 0;
  nullsub_3(this);
  sub_5ADB10(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8B70 sub_4A8B70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNHunter 析构（string @+8628 释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8B70(void **this)
{
  *this = &CNHunter::`vftable';
  nullsub_3(this);
  if ( (unsigned int)*(this + 2162) >= 0x10 )
    j__free(*(this + 2157));
  *(this + 2162) = (void *)15;
  *(this + 2161) = nullptr;
  *((uint8_t *)this + 8628) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A8BF0 sub_4A8BF0
// ------------------------------------------------------------
void **/*thiscall*/ sub_4A8BF0(void **Block, char pszArg2)
{
  sub_4A8B70(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8C20 sub_4A8C20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterMaster 构造（sub_5ADFE0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8C20(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A8AF0((int)this, ArgList, nArg3);
  *this = &CNHunterMaster::`vftable';
  sub_5ADFE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8C80 sub_4A8C80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8C80(void *Block, char pszArg2)
{
  sub_4A8CB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8CB0 sub_4A8CB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8CB0(void **this)
{
  *this = &CNHunterMaster::`vftable';
  return sub_4A8B70(this);
}



// ------------------------------------------------------------
// 0x4A8CC0 sub_4A8CC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterAlex 构造（sub_5AE160）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8CC0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A8AF0((int)this, ArgList, nArg3);
  *this = &CNHunterAlex::`vftable';
  sub_5AE160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8D20 sub_4A8D20
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8D20(void *Block, char pszArg2)
{
  sub_4A8D50();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8D50 sub_4A8D50
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8D50(void **this)
{
  *this = &CNHunterAlex::`vftable';
  return sub_4A8B70(this);
}



// ------------------------------------------------------------
// 0x4A8D60 sub_4A8D60
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNHunterHunter 构造（sub_5AE290）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8D60(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A8AF0((int)this, ArgList, nArg3);
  *this = &CNHunterHunter::`vftable';
  sub_5AE290(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8DC0 sub_4A8DC0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8DC0(void *Block, char pszArg2)
{
  sub_4A8DF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8DF0 sub_4A8DF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8DF0(void **this)
{
  *this = &CNHunterHunter::`vftable';
  return sub_4A8B70(this);
}



// ------------------------------------------------------------
// 0x4A8E00 sub_4A8E00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombie（僵尸）构造（sub_5AE3E0/5AF220）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8E00(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNZombie::`vftable';
  sub_5AE3E0(this);
  sub_5AF220(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8E60 sub_4A8E60
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZombie 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8E60(uint32_t *this)
{
  *this = &CNZombie::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A8EB0 sub_4A8EB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8EB0(uint32_t *Block, char pszArg2)
{
  sub_4A8E60(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8EE0 sub_4A8EE0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieZombie 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8EE0(char *this, char ArgList, int nArg3)
{
  sub_4A8E00(this, ArgList, nArg3);
  *(uint32_t *)this = &CNZombieZombie::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8F10 sub_4A8F10
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F10(void *Block, char pszArg2)
{
  sub_4A8F40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8F40 sub_4A8F40
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8F40(uint32_t *this)
{
  *this = &CNZombieZombie::`vftable';
  return sub_4A8E60(this);
}



// ------------------------------------------------------------
// 0x4A8F50 sub_4A8F50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieHollowEye（空洞眼僵尸）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8F50(char *this, char ArgList, int nArg3)
{
  sub_4A8E00(this, ArgList, nArg3);
  *(uint32_t *)this = &CNZombieHollowEye::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8F80 sub_4A8F80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F80(void *Block, char pszArg2)
{
  sub_4A8FB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8FB0 sub_4A8FB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8FB0(uint32_t *this)
{
  *this = &CNZombieHollowEye::`vftable';
  return sub_4A8E60(this);
}



// ------------------------------------------------------------
// 0x4A8FC0 sub_4A8FC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZombieGhoulgwish 构造（sub_5AE830 覆写加载）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8FC0(char *this, char ArgList, int nArg3)
{
  sub_4A8E00(this, ArgList, nArg3);
  *(uint32_t *)this = &CNZombieGhoulgwish::`vftable';
  sub_5AE830(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9020 sub_4A9020
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9020(void *Block, char pszArg2)
{
  sub_4A9050();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9050 sub_4A9050
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9050(uint32_t *this)
{
  *this = &CNZombieGhoulgwish::`vftable';
  return sub_4A8E60(this);
}



// ------------------------------------------------------------
// 0x4A9060 sub_4A9060
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNKalkazak 构造（+8652/+8656 双槽清零）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9060(int this, char ArgList, int nArg3)
{
  sub_4A8E00((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = 0;
  *(uint32_t *)this = &CNKalkazak::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9090 sub_4A9090
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9090(void *Block, char pszArg2)
{
  sub_4A90C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A90C0 sub_4A90C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A90C0(uint32_t *this)
{
  *this = &CNKalkazak::`vftable';
  return sub_4A8E60(this);
}



// ------------------------------------------------------------
// 0x4A90D0 sub_4A90D0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBurningHela（燃烧海拉）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A90D0(char *this, char ArgList, int nArg3)
{
  sub_4A8E00(this, ArgList, nArg3);
  *(uint32_t *)this = &CNBurningHela::`vftable';
  *(this + 8652) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A9100 sub_4A9100
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9100(void *Block, char pszArg2)
{
  sub_4A9130();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9130 sub_4A9130
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9130(uint32_t *this)
{
  *this = &CNBurningHela::`vftable';
  return sub_4A8E60(this);
}



// ------------------------------------------------------------
// 0x4A9140 sub_4A9140
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDraconian（龙人）构造（sub_5AF910/5B0660）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9140(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNDraconian::`vftable';
  sub_5AF910(this);
  sub_5B0660(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A91A0 sub_4A91A0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDraconian 析构（sub_5AF950）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A91A0(uint32_t *this)
{
  *this = &CNDraconian::`vftable';
  sub_5AF950();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A91F0 sub_4A91F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A91F0(uint32_t *Block, char pszArg2)
{
  sub_4A91A0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9220 sub_4A9220
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDracoMirkius 构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9220(char *this, char ArgList, int nArg3)
{
  sub_4A9140(this, ArgList, nArg3);
  *(uint32_t *)this = &CNDracoMirkius::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9250 sub_4A9250
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9250(void *Block, char pszArg2)
{
  sub_4A9280();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9280 sub_4A9280
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9280(uint32_t *this)
{
  *this = &CNDracoMirkius::`vftable';
  return sub_4A91A0(this);
}



// ------------------------------------------------------------
// 0x4A9290 sub_4A9290
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDracoLakius 构造（sub_5B1890）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9290(char *this, char ArgList, int nArg3)
{
  sub_4A9140(this, ArgList, nArg3);
  *(uint32_t *)this = &CNDracoLakius::`vftable';
  sub_5B1890(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A92F0 sub_4A92F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A92F0(uint32_t *this)
{
  *this = &CNDracoLakius::`vftable';
  return sub_4A91A0(this);
}



// ------------------------------------------------------------
// 0x4A9300 sub_4A9300
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9300(uint32_t *Block, char pszArg2)
{
  sub_4A92F0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9330 sub_4A9330
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAuraHunter_Sius（光环猎人西斯）构造（sub_5AFDD0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9330(char *this, char ArgList, int nArg3)
{
  sub_4A9290(this, ArgList, nArg3);
  *(uint32_t *)this = &CNAuraHunter_Sius::`vftable';
  sub_5AFDD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9390 sub_4A9390
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLordofLightBase（光之领主基）构造（sub_5B1910/5B2720）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9390(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNLordofLightBase::`vftable';
  sub_5B1910(this);
  sub_5B2720(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A93F0 sub_4A93F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLordofLightBase 析构（sub_5B1940）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A93F0(uint32_t *this)
{
  *this = &CNLordofLightBase::`vftable';
  sub_5B1940();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A9440 sub_4A9440
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9440(uint32_t *Block, char pszArg2)
{
  sub_4A93F0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9470 sub_4A9470
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLordofLight 构造（sub_5B3100）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9470(char *this, char ArgList, int nArg3)
{
  sub_4A9390(this, ArgList, nArg3);
  *(uint32_t *)this = &CNLordofLight::`vftable';
  sub_5B3100(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A94D0 sub_4A94D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A94D0(void *Block, char pszArg2)
{
  sub_4A9500();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9500 sub_4A9500
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9500(uint32_t *this)
{
  *this = &CNLordofLight::`vftable';
  return sub_4A93F0(this);
}



// ------------------------------------------------------------
// 0x4A9510 sub_4A9510
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishHead（太空鱼头）构造（sub_5B3230/5B3F30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9510(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpaceFishHead::`vftable';
  sub_5B3230(this);
  sub_5B3F30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9570 sub_4A9570
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpaceFishHead 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9570(uint32_t *this)
{
  *this = &CNSpaceFishHead::`vftable';
  nullsub_3(this);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A95C0 sub_4A95C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A95C0(uint32_t *Block, char pszArg2)
{
  sub_4A9570(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A95F0 sub_4A95F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishShort 构造（sub_5B3400）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A95F0(char *this, char ArgList, int nArg3)
{
  sub_4A9510(this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpaceFishShort::`vftable';
  sub_5B3400(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9650 sub_4A9650
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9650(void *Block, char pszArg2)
{
  sub_4A9680();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9680 sub_4A9680
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9680(uint32_t *this)
{
  *this = &CNSpaceFishShort::`vftable';
  return sub_4A9570(this);
}



// ------------------------------------------------------------
// 0x4A9690 sub_4A9690
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishLong 构造（sub_5B34D0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9690(char *this, char ArgList, int nArg3)
{
  sub_4A9510(this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpaceFishLong::`vftable';
  sub_5B34D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A96F0 sub_4A96F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A96F0(void *Block, char pszArg2)
{
  sub_4A9720();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9720 sub_4A9720
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9720(uint32_t *this)
{
  *this = &CNSpaceFishLong::`vftable';
  return sub_4A9570(this);
}



// ------------------------------------------------------------
// 0x4A9730 sub_4A9730
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpaceFishCrocuta 构造（sub_5B35C0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9730(char *this, char ArgList, int nArg3)
{
  sub_4A9510(this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpaceFishCrocuta::`vftable';
  sub_5B35C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9790 sub_4A9790
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9790(void *Block, char pszArg2)
{
  sub_4A97C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A97C0 sub_4A97C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A97C0(uint32_t *this)
{
  *this = &CNSpaceFishCrocuta::`vftable';
  return sub_4A9570(this);
}



// ------------------------------------------------------------
// 0x4A97D0 sub_4A97D0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFish（海星）构造。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A97D0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNStarFishFriendShip::`vftable';
  *(uint32_t *)this = &CNStarFish::`vftable';
  *(uint32_t *)(this + 8600) = &CNStarFish::`vftable';
  sub_5B4700(this);
  sub_5B6630(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9850 sub_4A9850
// ------------------------------------------------------------
// 【解读】
//   【推断】CNStarFish 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9850(uint32_t *this)
{
  *this = &CNStarFish::`vftable';
  *(this + 2150) = &CNStarFish::`vftable';
  sub_4E3360();
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A98C0 sub_4A98C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A98C0(uint32_t *Block, char pszArg2)
{
  sub_4A9850(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A98F0 sub_4A98F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishRukuku 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A98F0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A97D0((int)this, ArgList, nArg3);
  *this = &CNStarFishRukuku::`vftable';
  *(this + 2150) = &CNStarFishRukuku::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9920 sub_4A9920
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9920(void *Block, char pszArg2)
{
  sub_4A9950();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9950 sub_4A9950
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9950(uint32_t *this)
{
  *this = &CNStarFishRukuku::`vftable';
  *(this + 2150) = &CNStarFishRukuku::`vftable';
  return sub_4A9850(this);
}



// ------------------------------------------------------------
// 0x4A9970 sub_4A9970
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishDevourer 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9970(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A97D0((int)this, ArgList, nArg3);
  *this = &CNStarFishDevourer::`vftable';
  *(this + 2150) = &CNStarFishDevourer::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A99A0 sub_4A99A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A99A0(void *Block, char pszArg2)
{
  sub_4A99D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A99D0 sub_4A99D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A99D0(uint32_t *this)
{
  *this = &CNStarFishDevourer::`vftable';
  *(this + 2150) = &CNStarFishDevourer::`vftable';
  return sub_4A9850(this);
}



// ------------------------------------------------------------
// 0x4A99F0 sub_4A99F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStarFishKing 构造（+8664 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A99F0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A97D0((int)this, ArgList, nArg3);
  *this = &CNStarFishKing::`vftable';
  *(this + 2150) = &CNStarFishKing::`vftable';
  *((uint8_t *)this + 8664) = 0;
  *(this + 2167) = 0;
  *((uint8_t *)this + 8674) = 0;
  *((uint8_t *)this + 8673) = 0;
  *(this + 2171) = 0;
  *(this + 2170) = 0;
  *(this + 2169) = 0;
  *(this + 2165) = &off_6C2B88;
  *((uint8_t *)this + 8672) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x4A9A60 sub_4A9A60
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9A60(void *Block, char pszArg2)
{
  sub_4A9A90();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9A90 sub_4A9A90
// ------------------------------------------------------------
// 【解读】
//   【推断】CNStarFishKing 析构（IObject @+8660）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9A90(uint32_t *this)
{
  *this = &CNStarFishKing::`vftable';
  *(this + 2150) = &CNStarFishKing::`vftable';
  *(this + 2165) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8664) = 0;
  return sub_4A9850(this);
}



// ------------------------------------------------------------
// 0x4A9AC0 sub_4A9AC0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZealot（狂信徒）构造 —— 教团系（Raxy/Craxy/Father/Pope/Evangelist）继承基。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9AC0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)(this + 8600) = &CNZealotFriendShip::`vftable';
  *(uint32_t *)this = &CNZealot::`vftable';
  *(uint32_t *)(this + 8600) = &CNZealot::`vftable';
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8608) = &off_6C2B88;
  *(uint32_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8620) = 1;
  *(uint8_t *)(this + 8622) = 0;
  *(uint8_t *)(this + 8621) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8624) = 0;
  sub_5B73B0(this);
  sub_5B8C40(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9B70 sub_4A9B70
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZealot 析构（IObject @+8608，2152*4=8608）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9B70(uint32_t *this)
{
  *this = &CNZealot::`vftable';
  *(this + 2150) = &CNZealot::`vftable';
  nullsub_3(this);
  *(this + 2152) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8612) = 0;
  *(this + 2150) = &CNMonsterFriendShip::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4A9BF0 sub_4A9BF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9BF0(uint32_t *Block, char pszArg2)
{
  sub_4A9B70(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9C20 sub_4A9C20
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRaxy_A 构造（+8600 → off_6E7860 特殊 vftable）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C20(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNRaxy_A::`vftable';
  *(this + 2150) = &off_6E7860;
  return this;
}



// ------------------------------------------------------------
// 0x4A9C50 sub_4A9C50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRaxy_B 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C50(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNRaxy_B::`vftable';
  *(this + 2150) = &CNRaxy_B::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9C80 sub_4A9C80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9C80(void *Block, char pszArg2)
{
  sub_4A9CB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9CB0 sub_4A9CB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9CB0(uint32_t *this)
{
  *this = &CNRaxy_B::`vftable';
  *(this + 2150) = &CNRaxy_B::`vftable';
  return sub_4A9B70(this);
}



// ------------------------------------------------------------
// 0x4A9CD0 sub_4A9CD0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCraxy 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9CD0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNCraxy::`vftable';
  *(this + 2150) = &CNCraxy::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9D00 sub_4A9D00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFather（教父）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9D00(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNFather::`vftable';
  *(this + 2150) = &CNFather::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9D30 sub_4A9D30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9D30(void *Block, char pszArg2)
{
  sub_4A9D60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9D60 sub_4A9D60
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9D60(uint32_t *this)
{
  *this = &CNFather::`vftable';
  *(this + 2150) = &CNFather::`vftable';
  return sub_4A9B70(this);
}



// ------------------------------------------------------------
// 0x4A9D80 sub_4A9D80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPope（教皇）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9D80(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNPope::`vftable';
  *(this + 2150) = &CNPope::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9DB0 sub_4A9DB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9DB0(void *Block, char pszArg2)
{
  sub_4A9DE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9DE0 sub_4A9DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9DE0(uint32_t *this)
{
  *this = &CNPope::`vftable';
  *(this + 2150) = &CNPope::`vftable';
  return sub_4A9B70(this);
}



// ------------------------------------------------------------
// 0x4A9E00 sub_4A9E00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfDawn（黎明传道者）构造（+8672 = 30041 技能/动作 ID）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E00(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNEvangelistOfDawn::`vftable';
  *(this + 2150) = &CNEvangelistOfDawn::`vftable';
  *(this + 2168) = 30041;
  return this;
}



// ------------------------------------------------------------
// 0x4A9E50 sub_4A9E50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfLight（光之传道者）构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E50(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNEvangelistOfLight::`vftable';
  *(this + 2150) = &CNEvangelistOfLight::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9E80 sub_4A9E80
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfTwilight（暮光传道者）构造（+8676 标志）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E80(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNEvangelistOfTwilight::`vftable';
  *(this + 2150) = &CNEvangelistOfTwilight::`vftable';
  *(this + 2169) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A9EC0 sub_4A9EC0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9EC0(void *Block, char pszArg2)
{
  sub_4A9EF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9EF0 sub_4A9EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9EF0(uint32_t *this)
{
  *this = &CNRaxy_A::`vftable';
  *(this + 2150) = &off_6E7860;
  return sub_4A9B70(this);
}



// ------------------------------------------------------------
// 0x4A9F10 sub_4A9F10
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNEvangelistOfDark（暗之传道者）构造（+8672 = 30042）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9F10(uint32_t *this, char ArgList, int nArg3)
{
  sub_4A9AC0((int)this, ArgList, nArg3);
  *this = &CNEvangelistOfDark::`vftable';
  *(this + 2150) = &CNEvangelistOfDark::`vftable';
  *(this + 2168) = 30042;
  return this;
}



// ------------------------------------------------------------
// 0x4A9F50 sub_4A9F50
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9F50(void *Block, char pszArg2)
{
  sub_4A9F80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9F80 sub_4A9F80
// ------------------------------------------------------------
int /*thiscall*/ sub_4A9F80(uint32_t *this)
{
  *this = &CNCraxy::`vftable';
  *(this + 2150) = &CNCraxy::`vftable';
  return sub_4A9B70(this);
}



// ------------------------------------------------------------
// 0x4A9FA0 sub_4A9FA0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNVehicle（载具基）构造（sub_5BA050/5BAC30）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9FA0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNVehicle::`vftable';
  sub_5BA050(this);
  sub_5BAC30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA000 sub_4AA000
// ------------------------------------------------------------
// 【解读】
//   【推断】CNVehicle 析构（sub_5BA090）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA000(uint32_t *this)
{
  *this = &CNVehicle::`vftable';
  sub_5BA090();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AA050 sub_4AA050
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA050(uint32_t *Block, char pszArg2)
{
  sub_4AA000(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA080 sub_4AA080
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCatapult（投石车）构造（sub_5BAD00）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA080(char *this, char ArgList, int nArg3)
{
  sub_4A9FA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNCatapult::`vftable';
  sub_5BAD00(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA0E0 sub_4AA0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA0E0(uint32_t *this)
{
  *this = &CNCatapult::`vftable';
  return sub_4AA000(this);
}



// ------------------------------------------------------------
// 0x4AA0F0 sub_4AA0F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLaserCatapult（激光投石车）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA0F0(char *this, char ArgList, int nArg3)
{
  sub_4AA080(this, ArgList, nArg3);
  *(uint32_t *)this = &CNLaserCatapult::`vftable';
  sub_5BAD00(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA150 sub_4AA150
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNFlameCatapult（火焰投石车）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA150(char *this, char ArgList, int nArg3)
{
  sub_4AA080(this, ArgList, nArg3);
  *(uint32_t *)this = &CNFlameCatapult::`vftable';
  sub_5BAD00(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA1B0 sub_4AA1B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA1B0(uint32_t *Block, char pszArg2)
{
  sub_4AA0E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA1E0 sub_4AA1E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNBattlIngram（战斗英格拉姆/机甲）构造（sub_5BAEF0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA1E0(char *this, char ArgList, int nArg3)
{
  sub_4A9FA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNBattlIngram::`vftable';
  sub_5BAEF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA240 sub_4AA240
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA240(void *Block, char pszArg2)
{
  sub_4AA270();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA270 sub_4AA270
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA270(uint32_t *this)
{
  *this = &CNBattlIngram::`vftable';
  return sub_4AA000(this);
}



// ------------------------------------------------------------
// 0x4AA280 sub_4AA280
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNZepplin（飞艇）构造 —— 含 2 元素×0x1C(28) 字节内嵌数组（eh vector ctor）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA280(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNZepplin::`vftable';
  `eh vector constructor iterator'(this + 8616, 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  nullsub_3(this);
  sub_5BB420(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA300 sub_4AA300
// ------------------------------------------------------------
// 【解读】
//   【推断】CNZepplin 析构（2×28B eh vector dtor @+8616）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA300(uint32_t *this)
{
  *this = &CNZepplin::`vftable';
  nullsub_3(this);
  `eh vector destructor iterator'(this + 2154, 0x1Cu, 2, sub_501490);
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AA370 sub_4AA370
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA370(uint32_t *Block, char pszArg2)
{
  sub_4AA300(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA3A0 sub_4AA3A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNCannonZepplin（炮艇）构造（sub_599D80）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA3A0(char *this, char ArgList, int nArg3)
{
  sub_4AA280(this, ArgList, nArg3);
  *(uint32_t *)this = &CNCannonZepplin::`vftable';
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA400 sub_4AA400
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA400(void *Block, char pszArg2)
{
  sub_4AA430();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA430 sub_4AA430
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA430(uint32_t *this)
{
  *this = &CNCannonZepplin::`vftable';
  return sub_4AA300(this);
}



// ------------------------------------------------------------
// 0x4AA440 sub_4AA440
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNNormalZepplin（普通飞艇）构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA440(char *this, char ArgList, int nArg3)
{
  sub_4AA280(this, ArgList, nArg3);
  *(uint32_t *)this = &CNNormalZepplin::`vftable';
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA4A0 sub_4AA4A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA4A0(void *Block, char pszArg2)
{
  sub_4AA4D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA4D0 sub_4AA4D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA4D0(uint32_t *this)
{
  *this = &CNNormalZepplin::`vftable';
  return sub_4AA300(this);
}



// ------------------------------------------------------------
// 0x4AA4E0 sub_4AA4E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWraith（怨灵）构造（+8624=15/+8620 string）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA4E0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNWraith::`vftable';
  *(uint32_t *)(this + 8624) = 15;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8604) = 0;
  sub_5BD1B0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA560 sub_4AA560
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWraith 析构（string @+8624 区）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA560(void **this)
{
  *this = &CNWraith::`vftable';
  nullsub_3(this);
  if ( (unsigned int)*(this + 2156) >= 0x10 )
    j__free(*(this + 2151));
  *(this + 2156) = (void *)15;
  *(this + 2155) = nullptr;
  *((uint8_t *)this + 8604) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AA5E0 sub_4AA5E0
// ------------------------------------------------------------
void **/*thiscall*/ sub_4AA5E0(void **Block, char pszArg2)
{
  sub_4AA560(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA610 sub_4AA610
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWraithSpectress（女怨灵）构造（+8656/+8660 双槽）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA610(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AA4E0((int)this, ArgList, nArg3);
  *this = &CNWraithSpectress::`vftable';
  *(this + 2164) = 0;
  *(this + 2165) = 0;
  *(this + 2166) = 0;
  *((uint8_t *)this + 8676) = 0;
  *(this + 2168) = &off_6C2B88;
  *(this + 2170) = 0;
  *((uint8_t *)this + 8684) = 1;
  *((uint8_t *)this + 8686) = 0;
  *((uint8_t *)this + 8685) = 0;
  *(this + 2174) = 0;
  *(this + 2173) = 0;
  *(this + 2172) = 0;
  sub_5BD270(this);
  sub_5BDF80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA6C0 sub_4AA6C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA6C0(void *Block, char pszArg2)
{
  sub_4AA6F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA6F0 sub_4AA6F0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNWraithSpectress 析构（sub_5BCFC0 + IObject @+8672）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA6F0(int this)
{
  *(uint32_t *)this = &CNWraithSpectress::`vftable';
  sub_5BCFC0();
  *(uint32_t *)(this + 8672) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8676) = 0;
  if ( *(uint32_t *)(this + 8656) != 0 )
    j__free(*(void **)(this + 8656));
  *(uint32_t *)(this + 8656) = 0;
  *(uint32_t *)(this + 8660) = 0;
  *(uint32_t *)(this + 8664) = 0;
  return sub_4AA560((void **)this);
}



// ------------------------------------------------------------
// 0x4AA780 sub_4AA780
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpider（蜘蛛）构造（sub_5BEC80/5BECA0）—— 蜘蛛族基。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA780(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpider::`vftable';
  sub_5BEC80(this);
  sub_5BECA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA7F0 sub_4AA7F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRollingSpider（滚动蜘蛛）构造（+8628 标志 / +8624 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA7F0(int this, char ArgList, int nArg3)
{
  sub_4AA780((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNRollingSpider::`vftable';
  *(uint8_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8624) = &off_6C2B88;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8636) = 1;
  *(uint8_t *)(this + 8638) = 0;
  *(uint8_t *)(this + 8637) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8640) = 0;
  sub_5C0390(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA890 sub_4AA890
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA890(void *Block, char pszArg2)
{
  sub_4AA8C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA8C0 sub_4AA8C0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRollingSpider/CNSpider 析构（IObject @+8624 复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA8C0(int this)
{
  *(uint32_t *)(this + 8624) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8628) = 0;
  *(uint32_t *)this = &CNSpider::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4AA8E0 sub_4AA8E0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNPoisonSpider（毒蜘蛛）构造（sub_5C0400）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA8E0(char *this, char ArgList, int nArg3)
{
  sub_4AA780(this, ArgList, nArg3);
  *(uint32_t *)this = &CNPoisonSpider::`vftable';
  sub_5C0400(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA940 sub_4AA940
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA940(void *Block, char pszArg2)
{
  sub_4AA7E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA970 sub_4AA970
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAraclothoSpider（阿拉克洛蜘蛛）构造（+8664 标志 / +8660 IObject）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA970(int this, char ArgList, int nArg3)
{
  sub_4AA780((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNAraclothoSpider::`vftable';
  *(uint8_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8660) = &off_6C2B88;
  *(uint32_t *)(this + 8668) = 0;
  *(uint8_t *)(this + 8672) = 1;
  *(uint8_t *)(this + 8674) = 0;
  *(uint8_t *)(this + 8673) = 0;
  *(uint32_t *)(this + 8684) = 0;
  *(uint32_t *)(this + 8680) = 0;
  *(uint32_t *)(this + 8676) = 0;
  *(uint8_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8688) = &off_6C2B88;
  *(uint32_t *)(this + 8696) = 0;
  *(uint8_t *)(this + 8700) = 1;
  *(uint8_t *)(this + 8702) = 0;
  *(uint8_t *)(this + 8701) = 0;
  *(uint32_t *)(this + 8712) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8704) = 0;
  *(uint8_t *)(this + 8720) = 0;
  *(uint32_t *)(this + 8716) = &off_6C2B88;
  *(uint32_t *)(this + 8724) = 0;
  *(uint8_t *)(this + 8728) = 1;
  *(uint8_t *)(this + 8730) = 0;
  *(uint8_t *)(this + 8729) = 0;
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8736) = 0;
  *(uint32_t *)(this + 8732) = 0;
  sub_5C0490(this);
  sub_5C11B0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAA80 sub_4AAA80
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAA80(void *Block, char pszArg2)
{
  sub_4AAAB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AAAB0 sub_4AAAB0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAraclothoSpider 析构（sub_5C1270 + IObject @+8716）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAAB0(uint32_t *this)
{
  *this = &CNAraclothoSpider::`vftable';
  sub_5C1270();
  *(this + 2179) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8720) = 0;
  *(this + 2172) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8692) = 0;
  *(this + 2165) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8664) = 0;
  *this = &CNSpider::`vftable';
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AAB30 sub_4AAB30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotRX78（机器人 RX-78）构造（sub_5C1FC0）—— 机甲族。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAB30(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNRobotRX78::`vftable';
  sub_5C1FC0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAB90 sub_4AAB90
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAB90(void *Block, char pszArg2)
{
  sub_4AABC0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AABC0 sub_4AABC0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotRX78 析构（sub_5C1FF0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AABC0(uint32_t *this)
{
  *this = &CNRobotRX78::`vftable';
  sub_5C1FF0();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AAC10 sub_4AAC10
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotEz8 构造（sub_5C2830/5C2870）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAC10(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNRobotEz8::`vftable';
  sub_5C2830(this);
  sub_5C2870(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAC70 sub_4AAC70
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAC70(void *Block, char pszArg2)
{
  sub_4AACA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AACA0 sub_4AACA0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotEz8 析构（sub_5C28A0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AACA0(uint32_t *this)
{
  *this = &CNRobotEz8::`vftable';
  sub_5C28A0();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AACF0 sub_4AACF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRobotExs 构造（sub_5C3100/5C3760）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AACF0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNRobotExs::`vftable';
  sub_5C3100(this);
  sub_5C3760(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAD50 sub_4AAD50
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotExs 的覆写判定（转发基类 vt 调用 + 多条件）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AAD50(void *this, int nArg2, int nArg3, int nArg4)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 5;
}



// ------------------------------------------------------------
// 0x4AAD70 sub_4AAD70
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAD70(void *Block, char pszArg2)
{
  sub_4AADA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AADA0 sub_4AADA0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNRobotExs 析构（sub_5C3170）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AADA0(uint32_t *this)
{
  *this = &CNRobotExs::`vftable';
  sub_5C3170();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AADF0 sub_4AADF0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDendroidBasic（机械树精基）构造（sub_5C3A30/5C57F0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AADF0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNDendroidBasic::`vftable';
  sub_5C3A30(this);
  sub_5C57F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAE50 sub_4AAE50
// ------------------------------------------------------------
// 【解读】
//   【推断】CNDendroidBasic 析构（sub_5C4780）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAE50(uint32_t *this)
{
  *this = &CNDendroidBasic::`vftable';
  sub_5C4780();
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AAEA0 sub_4AAEA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AAEA0(uint32_t *Block, char pszArg2)
{
  sub_4AAE50(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AAED0 sub_4AAED0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNDendroid 系派生（off_6F04BC vftable）构造（sub_5C4080）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAED0(char *this, char ArgList, int nArg3)
{
  sub_4AADF0(this, ArgList, nArg3);
  *(uint32_t *)this = &off_6F04BC;
  sub_5C4080(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAF30 sub_4AAF30
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAF30(void *Block, char pszArg2)
{
  sub_4AAF60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AAF60 sub_4AAF60
// ------------------------------------------------------------
int /*thiscall*/ sub_4AAF60(uint32_t *this)
{
  *this = &off_6F04BC;
  return sub_4AAE50(this);
}



// ------------------------------------------------------------
// 0x4AAF70 sub_4AAF70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoliden 构造（sub_5C4100）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAF70(char *this, char ArgList, int nArg3)
{
  sub_4AADF0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNGoliden::`vftable';
  sub_5C4100(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAFD0 sub_4AAFD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAFD0(void *Block, char pszArg2)
{
  sub_4AB000();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB000 sub_4AB000
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB000(uint32_t *this)
{
  *this = &CNGoliden::`vftable';
  return sub_4AAE50(this);
}



// ------------------------------------------------------------
// 0x4AB010 sub_4AB010
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNRodinglo 构造（sub_5C41B0）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AB010(char *this, char ArgList, int nArg3)
{
  sub_4AADF0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNRodinglo::`vftable';
  sub_5C41B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB070 sub_4AB070
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB070(void *Block, char pszArg2)
{
  sub_4AB0A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB0A0 sub_4AB0A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB0A0(uint32_t *this)
{
  *this = &CNRodinglo::`vftable';
  return sub_4AAE50(this);
}



// ------------------------------------------------------------
// 0x4AB0B0 sub_4AB0B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpirit（精灵/魂）构造（+8624=15/+8620 string）—— 魂系基。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB0B0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpirit::`vftable';
  *(uint32_t *)(this + 8624) = 15;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8680) = 15;
  *(uint32_t *)(this + 8676) = 0;
  *(uint8_t *)(this + 8660) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8704) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  *(uint32_t *)(this + 8720) = 0;
  *(uint32_t *)(this + 8724) = 0;
  *(uint32_t *)(this + 8728) = 0;
  sub_5C6190(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB180 sub_4AB180
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpirit 析构（52 行，多成员释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB180(int this)
{
  int fld_2200; // eax
  int fld_21F0; // eax

  *(uint32_t *)this = &CNSpirit::`vftable';
  nullsub_3(this);
  if ( *(uint32_t *)(this + 8720) != 0 )
    j__free(*(void **)(this + 8720));
  *(uint32_t *)(this + 8720) = 0;
  *(uint32_t *)(this + 8724) = 0;
  *(uint32_t *)(this + 8728) = 0;
  fld_2200 = *(uint32_t *)(this + 8704);
  if ( fld_2200 != 0 )
  {
    sub_4166A0(fld_2200, *(uint32_t *)(this + 8708));
    j__free(*(void **)(this + 8704));
  }
  *(uint32_t *)(this + 8704) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  fld_21F0 = *(uint32_t *)(this + 8688);
  if ( fld_21F0 != 0 )
  {
    sub_4166A0(fld_21F0, *(uint32_t *)(this + 8692));
    j__free(*(void **)(this + 8688));
  }
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  if ( *(uint32_t *)(this + 8680) >= 0x10u )
    j__free(*(void **)(this + 8660));
  *(uint32_t *)(this + 8680) = 15;
  *(uint32_t *)(this + 8676) = 0;
  *(uint8_t *)(this + 8660) = 0;
  if ( *(uint32_t *)(this + 8652) >= 0x10u )
    j__free(*(void **)(this + 8632));
  *(uint32_t *)(this + 8652) = 15;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8632) = 0;
  if ( *(uint32_t *)(this + 8624) >= 0x10u )
    j__free(*(void **)(this + 8604));
  *(uint32_t *)(this + 8624) = 15;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8604) = 0;
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x4AB2F0 sub_4AB2F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB2F0(void *Block, char pszArg2)
{
  sub_4AB180((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB320 sub_4AB320
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNNaias（水泽仙女）构造（+8744 标志 / sub_5C8290）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4AB320(uint8_t *this, char ArgList, int nArg3)
{
  sub_4AB0B0((int)this, ArgList, nArg3);
  *(uint32_t *)this = &CNNaias::`vftable';
  *(this + 8744) = 0;
  sub_5C8290(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB380 sub_4AB380
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB380(void *Block, char pszArg2)
{
  sub_4AB3B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB3B0 sub_4AB3B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB3B0(int this)
{
  *(uint32_t *)this = &CNNaias::`vftable';
  return sub_4AB180(this);
}



// ------------------------------------------------------------
// 0x4AB3C0 sub_4AB3C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAdor 构造（sub_5C8470）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB3C0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB0B0((int)this, ArgList, nArg3);
  *this = &CNAdor::`vftable';
  sub_5C8470(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB420 sub_4AB420
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB420(int this)
{
  *(uint32_t *)this = &CNAdor::`vftable';
  return sub_4AB180(this);
}



// ------------------------------------------------------------
// 0x4AB430 sub_4AB430
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSoulEter（食魂者）构造（sub_5C6590）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB430(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB3C0(this, ArgList, nArg3);
  *this = &CNSoulEter::`vftable';
  sub_5C6590(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB490 sub_4AB490
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB490(void *Block, char pszArg2)
{
  sub_4AB420((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB4C0 sub_4AB4C0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNStalker（跟踪者）构造（sub_5C8650）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB4C0(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB0B0((int)this, ArgList, nArg3);
  *this = &CNStalker::`vftable';
  sub_5C8650(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB520 sub_4AB520
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB520(void *Block, char pszArg2)
{
  sub_4AB550();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB550 sub_4AB550
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB550(int this)
{
  *(uint32_t *)this = &CNStalker::`vftable';
  return sub_4AB180(this);
}



// ------------------------------------------------------------
// 0x4AB560 sub_4AB560
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNWisp（鬼火）构造（sub_5C8FE0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB560(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB0B0((int)this, ArgList, nArg3);
  *this = &CNWisp::`vftable';
  sub_5C8FE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB5C0 sub_4AB5C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB5C0(void *Block, char pszArg2)
{
  sub_4AB5F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB5F0 sub_4AB5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB5F0(int this)
{
  *(uint32_t *)this = &CNWisp::`vftable';
  return sub_4AB180(this);
}



// ------------------------------------------------------------
// 0x4AB600 sub_4AB600
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLotusBasic（莲花基）构造（+8644 标志 / +8640 IObject）—— 植物族（Lotus/MonsterFlower）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB600(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNLotusBasic::`vftable';
  *(uint8_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8640) = &off_6C2B88;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8652) = 1;
  *(uint8_t *)(this + 8654) = 0;
  *(uint8_t *)(this + 8653) = 0;
  *(uint32_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8660) = 0;
  *(uint32_t *)(this + 8656) = 0;
  nullsub_3(this);
  sub_5CB360(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB6B0 sub_4AB6B0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNLotusBasic 析构（sub_5C92A0 + IObject @+8640）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB6B0(uint32_t *this)
{
  *this = &CNLotusBasic::`vftable';
  sub_5C92A0();
  *(this + 2160) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8644) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AB710 sub_4AB710
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB710(uint32_t *Block, char pszArg2)
{
  sub_4AB6B0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB740 sub_4AB740
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNLotus 构造。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB740(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB600((int)this, ArgList, nArg3);
  *this = &CNLotus::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4AB770 sub_4AB770
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB770(void *Block, char pszArg2)
{
  sub_4AB7A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB7A0 sub_4AB7A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB7A0(uint32_t *this)
{
  *this = &CNLotus::`vftable';
  return sub_4AB6B0(this);
}



// ------------------------------------------------------------
// 0x4AB7B0 sub_4AB7B0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNMonsterFlower（怪物花）构造（sub_5CB970）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4AB7B0(char *this, char ArgList, int nArg3)
{
  sub_4A4EA0(this, ArgList, nArg3);
  *(uint32_t *)this = &CNMonsterFlower::`vftable';
  sub_5CB970(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB810 sub_4AB810
// ------------------------------------------------------------
// 【解读】
//   【推断】CNMonsterFlower 析构壳（sub_5CBD40）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB810(void *Block, char pszArg2)
{
  sub_5CBD40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB840 sub_4AB840
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNSpikeKing（尖刺王）构造 —— +8616 = sub_4A2D10()（20 字节链表头），
//   这是 CNSpikeKing 内嵌链表对象的实证，参照 0x4A2D10 注释。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB840(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNSpikeKing::`vftable';
  *(uint32_t *)(this + 8616) = sub_4A2D10();
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8624) = &off_6C2B88;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8636) = 1;
  *(uint8_t *)(this + 8638) = 0;
  *(uint8_t *)(this + 8637) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8640) = 0;
  *(uint8_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8660) = &off_6C2B88;
  *(uint32_t *)(this + 8668) = 0;
  *(uint8_t *)(this + 8672) = 1;
  *(uint8_t *)(this + 8674) = 0;
  *(uint8_t *)(this + 8673) = 0;
  *(uint32_t *)(this + 8684) = 0;
  *(uint32_t *)(this + 8680) = 0;
  *(uint32_t *)(this + 8676) = 0;
  sub_5CC490(this);
  sub_5CBD50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB930 sub_4AB930
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB930(void *Block, char pszArg2)
{
  sub_4AB960();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB960 sub_4AB960
// ------------------------------------------------------------
// 【解读】
//   【推断】CNSpikeKing 析构（sub_4E3360 + IObject @+8660）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB960(char *this)
{
  *(uint32_t *)this = &CNSpikeKing::`vftable';
  sub_4E3360();
  *((uint32_t *)this + 2165) = &nengine::IObject::`vftable';
  *(this + 8664) = 0;
  *((uint32_t *)this + 2156) = &nengine::IObject::`vftable';
  *(this + 8628) = 0;
  sub_6569D0(this + 8612);
  j__free(*((void **)this + 2154));
  *((uint32_t *)this + 2154) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4AB9F0 sub_4AB9F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAbom（阿波姆）构造（+8600 IObject / +8604 标志）—— 巨人族基（Goliath/Atlas/Titan）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB9F0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0((char *)this, ArgList, nArg3);
  *(uint32_t *)this = &CNAbom::`vftable';
  *(uint8_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8600) = &off_6C2B88;
  *(uint32_t *)(this + 8608) = 0;
  *(uint8_t *)(this + 8612) = 1;
  *(uint8_t *)(this + 8614) = 0;
  *(uint8_t *)(this + 8613) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8648) = &off_6C2B88;
  *(uint32_t *)(this + 8656) = 0;
  *(uint8_t *)(this + 8660) = 1;
  *(uint8_t *)(this + 8662) = 0;
  *(uint8_t *)(this + 8661) = 0;
  *(uint32_t *)(this + 8672) = 0;
  *(uint32_t *)(this + 8668) = 0;
  *(uint32_t *)(this + 8664) = 0;
  sub_5CD100(this);
  sub_5CD8D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABAD0 sub_4ABAD0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAbom 析构（sub_5CD150 + IObject @+8648）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABAD0(uint32_t *this)
{
  *this = &CNAbom::`vftable';
  sub_5CD150();
  *(this + 2162) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8652) = 0;
  *(this + 2150) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8604) = 0;
  return sub_4A50F0((int)this);
}



// ------------------------------------------------------------
// 0x4ABB40 sub_4ABB40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABB40(uint32_t *Block, char pszArg2)
{
  sub_4ABAD0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABB70 sub_4ABB70
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNGoliath（歌利亚）构造（sub_5CD1E0/5CD220）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABB70(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB9F0((int)this, ArgList, nArg3);
  *this = &CNGoliath::`vftable';
  sub_5CD1E0(this);
  sub_5CD220(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABBD0 sub_4ABBD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABBD0(void *Block, char pszArg2)
{
  sub_4ABC00();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABC00 sub_4ABC00
// ------------------------------------------------------------
// 【解读】
//   【推断】CNGoliath 析构（sub_5CD2A0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABC00(uint32_t *this)
{
  *this = &CNGoliath::`vftable';
  sub_5CD2A0();
  return sub_4ABAD0(this);
}



// ------------------------------------------------------------
// 0x4ABC50 sub_4ABC50
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNAtlas（阿特拉斯）构造（sub_5CD360/5CD380）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABC50(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB9F0((int)this, ArgList, nArg3);
  *this = &CNAtlas::`vftable';
  sub_5CD360(this);
  sub_5CD380(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABCB0 sub_4ABCB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABCB0(void *Block, char pszArg2)
{
  sub_4ABCE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABCE0 sub_4ABCE0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNAtlas 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABCE0(uint32_t *this)
{
  *this = &CNAtlas::`vftable';
  nullsub_3(this);
  return sub_4ABAD0(this);
}



// ------------------------------------------------------------
// 0x4ABD30 sub_4ABD30
// ------------------------------------------------------------
// 【解读】
//   【推断】★ CNTitan（泰坦）构造（sub_5CD3C0/599D80）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABD30(uint32_t *this, char ArgList, int nArg3)
{
  sub_4AB9F0((int)this, ArgList, nArg3);
  *this = &CNTitan::`vftable';
  sub_5CD3C0(this);
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABD90 sub_4ABD90
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABD90(void *Block, char pszArg2)
{
  sub_4ABDC0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABDC0 sub_4ABDC0
// ------------------------------------------------------------
// 【解读】
//   【推断】CNTitan 析构（sub_5CD3F0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABDC0(uint32_t *this)
{
  *this = &CNTitan::`vftable';
  sub_5CD3F0();
  return sub_4ABAD0(this);
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
uint32_t */*thiscall*/ sub_4AEA30(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  uint32_t *fld_e2; // edx
  uint32_t *v4; // ecx

  result = (uint32_t *)*(this + 3);
  if ( result != nullptr )
  {
    fld_e2 = (uint32_t *)*(this + 2);
    result = (uint32_t *)*fld_e2;
    if ( (uint32_t *)*fld_e2 != fld_e2 )
    {
      while ( 1 )
      {
        v4 = (uint32_t *)result[2];
        if ( *(uint32_t *)(pArg2 + 8) == v4[1] )
          break;
        result = (uint32_t *)*result;
        if ( result == fld_e2 )
          return result;
      }
      return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v4 + 4))(v4, pArg2);
    }
  }
  return result;
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
int /*thiscall*/ sub_4AEA70(int *this)
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

  while ( 1 )
  {
    result = *(this + 20);
    if ( result == 0 )
      return result;
    fld_e19 = (unsigned int)*(this + 19) >> 2;
    fld_e192 = *(this + 19) - 4 * fld_e19;
    fld_e18 = *(this + 18);
    if ( fld_e18 <= fld_e19 )
      fld_e19 -= fld_e18;
    fld_e17 = *(uint32_t *)(*(uint32_t *)(*(this + 17) + 4 * fld_e19) + 4 * fld_e192);
    fld_e193 = *(this + 19) + 1;
    fld_e182 = 4 * *(this + 18);
    *(this + 19) = fld_e193;
    if ( fld_e182 <= fld_e193 )
      *(this + 19) = 0;
    result = *(this + 20) - 1;
    *(this + 20) = result;
    if ( result == 0 )
      *(this + 19) = 0;
    if ( fld_e17 == 0 )
      return result;
    if ( *(this + 3) != 0 )
    {
      fld_e2 = (uint32_t *)*(this + 2);
      v10 = (uint32_t *)*fld_e2;
      if ( (uint32_t *)*fld_e2 != fld_e2 )
      {
        while ( 1 )
        {
          v11 = (uint32_t *)v10[2];
          if ( *(uint32_t *)(fld_e17 + 8) == v11[1] )
            break;
          v10 = (uint32_t *)*v10;
          if ( v10 == fld_e2 )
            goto LABEL_15;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*v11 + 4))(v11, fld_e17);
      }
    }
LABEL_15:
    fld_e172 = fld_e17;
    sub_49C800((int)&unk_9B9310, &fld_e172);
  }
}



// ------------------------------------------------------------
// 0x4AEB30 sub_4AEB30
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4AEA70 排空 + sub_58B380(this+4) 后续清理。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEB30(int *this)
{
  sub_4AEA70(this);
  return sub_58B380(this + 4);
}



// ------------------------------------------------------------
// 0x4AEB50 sub_4AEB50
// ------------------------------------------------------------
// 【解读】
//   【推断】环形缓冲整体排空（this+4/+8/+12/+16 = 基/容量/头/计数）+ sub_406E40 收尾。
//   与 0x4AEA70 对偶（一个逐格、一个整体）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEB50(unsigned int *this)
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

  fld_e4 = *(this + 4);
  v11[3] = 0;
  if ( fld_e4 != 0 )
  {
    do
    {
      fld_e3 = *(this + 3) >> 2;
      fld_e32 = *(this + 3) - 4 * fld_e3;
      fld_e2 = *(this + 2);
      if ( fld_e2 <= fld_e3 )
        fld_e3 -= fld_e2;
      fld_e1 = *(uint32_t *)(*(uint32_t *)(*(this + 1) + 4 * fld_e3) + 4 * fld_e32);
      fld_e42 = *(this + 4);
      if ( fld_e42 != 0 )
      {
        fld_e33 = *(this + 3) + 1;
        fld_e22 = 4 * *(this + 2);
        *(this + 3) = fld_e33;
        if ( fld_e22 <= fld_e33 )
          *(this + 3) = 0;
        v10 = fld_e42 - 1;
        *(this + 4) = v10;
        if ( v10 == 0 )
          *(this + 3) = 0;
      }
      if ( fld_e1 != 0 )
      {
        v11[0] = fld_e1;
        sub_49C800((int)&unk_9B9310, v11);
      }
    }
    while ( *(this + 4) != 0 );
  }
  sub_406E40((int)this);
}



// ------------------------------------------------------------
// 0x4AEC00 sub_4AEC00
// ------------------------------------------------------------
// 【解读】
//   【推断】容器重置（sub_498A00 + sub_58B450 + 清 4 字段 + 链头释放）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AEC00(uint32_t *this)
{
  uint32_t *pThis_1; // edi

  pThis_1 = this + 1;
  sub_498A00(this + 1);
  sub_58B450(this + 4);
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  if ( pThis_1[2] != 0 )
    sub_6569D0(pThis_1);
  return this;
}



// ------------------------------------------------------------
// 0x4AEC70 sub_4AEC70
// ------------------------------------------------------------
// 【解读】
//   【推断】容器析构（sub_4AEB50 排空 + sub_58B4D0 + sub_4989D0 释放链）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEC70(uint32_t *this)
{
  void **pThis_1; // edi

  pThis_1 = (void **)(this + 1);
  if ( *(this + 3) != 0 )
    sub_6569D0(this + 1);
  sub_4AEB50(this + 16);
  sub_58B4D0(this + 4);
  sub_4989D0(pThis_1);
}



// ------------------------------------------------------------
// 0x4AECE0 sub_4AECE0
// ------------------------------------------------------------
// 【解读】
//   【推断】动画切换: sub_491C70(a2) 取动画资源 → sub_493A60(this, res) 应用。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AECE0(void *this, int nArg2)
{
  int v3; // eax

  v3 = sub_491C70(nArg2);
  return sub_493A60((int)this, v3);
}



// ------------------------------------------------------------
// 0x4AED00 sub_4AED00
// ------------------------------------------------------------
// 【解读】
//   【推断】有效性判定: this+16 字节非 0 或 this+0 浮点 > 0.0。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4AED00(float *this)
{
  return *((uint8_t *)this + 16) != 0 || *this > 0.0;
}



// ------------------------------------------------------------
// 0x4AED20 sub_4AED20
// ------------------------------------------------------------
// 【解读】
//   【推断】帧数据 getter（与 IRDCollisionObject_vmt270 的帧检查同构）:
//   this+642 非 0 → 直接返回 this+644；否则从动画对象 +112 读帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED20(int this)
{
  int fld_78; // esi

  if ( *(uint8_t *)(this + 642) != 0 )
    return *(uint32_t *)(this + 644);
  fld_78 = *(uint32_t *)(this + 120);
  if ( fld_78 == 0 )
    return 0;
  if ( *(uint32_t *)(fld_78 + 148) == -1 )
    sub_4938F0(*(uint32_t *)(this + 120));
  return *(uint32_t *)(fld_78 + 112);
}



// ------------------------------------------------------------
// 0x4AED60 sub_4AED60
// ------------------------------------------------------------
// 【解读】
//   【推断】防篡改浮点自增（读 sub_41A5E0 → +a2 → 写 sub_41A590）。
// ------------------------------------------------------------
double /*thiscall*/ sub_4AED60(void *this, float fArg2)
{
  int v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0((unsigned int)this)) + fArg2;
  sub_41A590((unsigned int)this, v3, v5);
  return *(float *)&v5;
}



// ------------------------------------------------------------
// 0x4AED90 sub_4AED90
// ------------------------------------------------------------
// 【解读】
//   【推断】转发 sub_47EFD0（this, a2, a3, a4, a4, a5）—— 六参版桥接。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED90(char *this, float fArg2, int nArg3, int nArg4, int nArg5)
{
  return sub_47EFD0(this, fArg2, nArg3, nArg4, nArg4, nArg5);
}



// ------------------------------------------------------------
// 0x4AEDB0 sub_4AEDB0
// ------------------------------------------------------------
// 【解读】
//   【推断】全局清理: sub_4C4210 + sub_617B80 + 释放全局对象 dword_9B9410（vt+0(1) 后置空）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEDB0(void *this)
{
  int v1; // ecx
  int result; // eax

  nullsub_3(this);
  nullsub_3(v1);
  sub_4C4210();
  result = sub_617B80();
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
int /*thiscall*/ sub_4AEDD0(int this)
{
  int result; // eax
  uint32_t *pThis_1FEC; // edx
  int i; // edi
  int j; // esi

  result = 0;
  *(uint32_t *)(this + 96) = 273;
  *(uint32_t *)(this + 608) = 0;
  *(uint32_t *)(this + 7512) = -1;
  *(uint32_t *)(this + 7516) = 0;
  *(uint32_t *)(this + 7520) = 0;
  *(uint32_t *)(this + 7524) = 0;
  *(uint32_t *)(this + 7528) = 0;
  *(uint32_t *)(this + 7532) = 0;
  *(uint32_t *)(this + 7536) = 0;
  *(uint32_t *)(this + 7540) = 0;
  *(uint32_t *)(this + 7544) = 0;
  *(uint32_t *)(this + 7548) = 0;
  *(uint32_t *)(this + 7552) = 0;
  *(uint32_t *)(this + 7556) = 0;
  *(uint32_t *)(this + 7560) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7592) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7600) = 0;
  *(uint32_t *)(this + 7604) = 0;
  *(uint8_t *)(this + 7608) = 0;
  *(uint8_t *)(this + 7609) = 0;
  *(uint32_t *)(this + 7692) = 0;
  *(uint32_t *)(this + 7696) = 0;
  *(uint8_t *)(this + 7729) = 0;
  *(uint32_t *)(this + 7760) = 4;
  *(uint8_t *)(this + 7764) = 0;
  *(uint8_t *)(this + 7780) = 0;
  *(uint8_t *)(this + 7730) = 1;
  *(uint32_t *)(this + 7768) = 0;
  *(uint32_t *)(this + 7772) = 0;
  *(uint32_t *)(this + 7776) = 0;
  *(uint32_t *)(this + 7784) = 0;
  *(uint32_t *)(this + 7788) = 0;
  *(uint8_t *)(this + 7792) = 0;
  *(uint32_t *)(this + 7796) = 0;
  *(uint32_t *)(this + 7800) = 0;
  *(uint32_t *)(this + 7804) = 0;
  *(uint32_t *)(this + 7808) = 0;
  *(uint32_t *)(this + 7812) = 0;
  *(uint32_t *)(this + 7816) = 0;
  *(uint32_t *)(this + 7820) = 0;
  *(uint32_t *)(this + 7824) = 0;
  *(uint32_t *)(this + 7828) = 0;
  *(uint32_t *)(this + 7832) = 0;
  *(uint32_t *)(this + 7836) = 1000;
  *(uint32_t *)(this + 7888) = 0;
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
  *(uint32_t *)(this + 7964) = 0;
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
  for ( i = 5; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      *(pThis_1FEC - 10) = 0;
      *pThis_1FEC++ = 0;
    }
  }
  *(uint32_t *)(this + 7428) = 0;
  *(uint32_t *)(this + 8212) = 0;
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
int /*thiscall*/ sub_4AF010(char *this, int pArg2)
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

  qmemcpy(this + 7432, (const void *)pArg2, 0x4Fu);
  sub_41A590((unsigned int)(this + 708), *(uint32_t *)(pArg2 + 4) / 0xAu, *(uint32_t *)(pArg2 + 4) / 0xAu);
  sub_41A590((unsigned int)(this + 722), v3, 1065353216);
  pThis_388 = (unsigned int)(this + 904);
  v21 = (int16_t *)(pArg2 + 16);
  v19 = 4;
  do
  {
    sub_41A590(pThis_388 - 56, (int)((uint64_t)(1717986919LL * *v21) >> 32) >> 2, *v21 / 10);
    sub_41A590(pThis_388, v6, 1065353216);
    pThis_388 += 14;
    v7 = v19 == 1;
    ++v21;
    --v19;
  }
  while ( !v7 );
  pThis_4A0 = (unsigned int)(this + 1184);
  v22 = (int16_t *)(pArg2 + 24);
  v20 = 16;
  do
  {
    sub_41A590(pThis_4A0 - 224, (int)((uint64_t)(1717986919LL * *v22) >> 32) >> 2, *v22 / 10);
    sub_41A590(pThis_4A0, 1065353216, 1065353216);
    pThis_4A0 += 14;
    v7 = v20 == 1;
    ++v22;
    --v20;
  }
  while ( !v7 );
  sub_41A590(
    (unsigned int)(this + 1408),
    (int)((uint64_t)(1717986919LL * *(int *)(pArg2 + 56)) >> 32) >> 2,
    *(uint32_t *)(pArg2 + 56) / 10);
  sub_41A590((unsigned int)(this + 1422), v9, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1436),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 60)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 60) / 10);
  sub_41A590((unsigned int)(this + 1450), v10, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1464),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 62)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 62) / 10);
  sub_41A590((unsigned int)(this + 1478), v11, 1065353216);
  sub_41A590((unsigned int)(this + 1492), *(uint16_t *)(pArg2 + 64) / 10, *(uint16_t *)(pArg2 + 64) / 10);
  sub_41A590((unsigned int)(this + 1506), v12, 1065353216);
  sub_41A590((unsigned int)(this + 1520), *(uint16_t *)(pArg2 + 66) / 10, *(uint16_t *)(pArg2 + 66) / 10);
  sub_41A590((unsigned int)(this + 1534), v13, 1065353216);
  sub_41A590((unsigned int)(this + 1548), *(uint16_t *)(pArg2 + 68) / 10, *(uint16_t *)(pArg2 + 68) / 10);
  sub_41A590((unsigned int)(this + 1562), v14, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1576),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 70)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 70) / 10);
  sub_41A590((unsigned int)(this + 1590), v15, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1604),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(pArg2 + 72)) >> 32) >> 2,
    *(int16_t *)(pArg2 + 72) / 10);
  sub_41A590((unsigned int)(this + 1618), v16, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1660),
    (int)((uint64_t)(1717986919LL * *(int *)(pArg2 + 74)) >> 32) >> 2,
    *(uint32_t *)(pArg2 + 74) / 10);
  sub_41A590((unsigned int)(this + 1674), v17, 1065353216);
  return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
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
char /*thiscall*/ sub_4AF330(unsigned int *this, char pszArg2)
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

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 672))(this, 3);
  v4 = sub_432FD0(*v3, 2);
  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  pThis_1D56 = 100;
  if ( v5 != 4 && v5 != 6 )
    pThis_1D56 = *((uint8_t *)this + 7510);
  fld_e1858 = (uint64_t)((double)*(this + 1858) * v4 * 0.1);
  sub_41A590((unsigned int)(this + 170), SHIDWORD(fld_e1858), fld_e1858);
  sub_41A590(
    (unsigned int)(this + 184),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3720)) >> 32) >> 6,
    pThis_1D56 * *((uint16_t *)this + 3720) / 1000);
  sub_41A590(
    (unsigned int)(this + 191),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3721)) >> 32) >> 6,
    pThis_1D56 * *((uint16_t *)this + 3721) / 1000);
  sub_41A590(
    (unsigned int)(this + 198),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3722)) >> 32) >> 6,
    pThis_1D56 * *((uint16_t *)this + 3722) / 1000);
  sub_41A590(
    (unsigned int)(this + 205),
    (int)((uint64_t)(274877907LL * pThis_1D56 * *((uint16_t *)this + 3723)) >> 32) >> 6,
    pThis_1D56 * *((uint16_t *)this + 3723) / 1000);
  (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 676))(this, 0);
  result = pszArg2;
  if ( pszArg2 != 0 )
  {
    v9 = *this;
    v10 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, int))(*this + 740))(this, 0, 1);
    (*(void (/*thiscall*/ **)(unsigned int *, int))(v9 + 732))(this, pThis_1D56 * v10 / 100);
    v11 = *this;
    v12 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 756))(this, 1);
    return (*(int (/*thiscall*/ **)(unsigned int *, int))(v11 + 748))(this, pThis_1D56 * v12 / 100);
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
char /*thiscall*/ sub_4AF4B0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int fld_e30; // edi
  int v7; // eax
  char result; // al
  int fld_e302; // edi
  int v10; // eax
  int v11; // [esp-4h] [ebp-10h]
  int v12; // [esp-4h] [ebp-10h]

  if ( (uint8_t)nArg2 == 0 )
  {
    fld_e30 = *(this + 30);
    if ( fld_e30 != 0 )
    {
      if ( *(uint32_t *)(fld_e30 + 148) == -1 )
        sub_4938F0(*(this + 30));
      v11 = *(uint8_t *)(fld_e30 + 95);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);
      sub_432600(0, nArg3, nArg4, this, v7, 1, v11);
    }
  }
  sub_58E750(this, nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt148】
  result = nArg2;
  if ( (uint8_t)nArg2 != 0 )
  {
    fld_e302 = *(this + 30);
    if ( fld_e302 != 0 )
    {
      if ( *(uint32_t *)(fld_e302 + 148) == -1 )
        sub_4938F0(*(this + 30));
      v12 = *(uint8_t *)(fld_e302 + 95);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);
      return sub_432600(1, nArg3, nArg4, this, v10, 1, v12);
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
uint32_t */*stdcall*/ sub_4AF560(int nArg1, uint32_t *pArg2, char *pszArg3)
{
  uint32_t *v3; // edi
  uint32_t *v4; // esi
  int v5; // ebx
  uint32_t *result; // eax
  int i; // [esp+Ch] [ebp-4h]

  if ( *pArg2 != 0 && *(uint32_t *)pszArg3 != 0 )
    sub_494240(nArg1, *(uint32_t *)pszArg3);
  v3 = pszArg3 + 20;
  v4 = pArg2 + 1;
  v5 = pszArg3 - (char *)pArg2;
  for ( i = 4; i != 0; --i )
  {
    if ( *v4 != 0 && *(uint32_t *)((char *)v4 + v5) != 0 )
      sub_494240(nArg1, *(uint32_t *)((char *)v4 + v5));
    if ( v4[4] != 0 && *v3 != 0 )
      sub_494240(nArg1, *v3);
    ++v4;
    ++v3;
  }
  if ( pArg2[9] != 0 && *((uint32_t *)pszArg3 + 9) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 9));
  if ( pArg2[10] != 0 && *((uint32_t *)pszArg3 + 10) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 10));
  if ( pArg2[11] != 0 && *((uint32_t *)pszArg3 + 11) != 0 )
    sub_494240(nArg1, *((uint32_t *)pszArg3 + 11));
  result = pArg2;
  if ( pArg2[12] != 0 )
  {
    result = *((uint32_t **)pszArg3 + 12);
    if ( result != nullptr )
      return (uint32_t *)sub_494240(nArg1, *((uint32_t *)pszArg3 + 12));
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
void **/*stdcall*/ sub_4AF650(void ****pArg1, void **pArg2)
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
    sub_492980(*pArg1, *pArg2);
  v2 = pArg2 + 5;
  v3 = pArg1 + 1;
  v4 = (char *)((char *)pArg2 - (char *)pArg1);
  for ( i = 4; i != 0; --i )
  {
    if ( *v3 != nullptr && *(void ****)((char *)v3 + (uint32_t)v4) != nullptr )
      sub_492980(*v3, *(void **)((char *)v3 + (uint32_t)v4));
    v5 = v3[4];
    if ( v5 != nullptr && *v2 != nullptr )
      sub_492980(v5, *v2);
    ++v3;
    ++v2;
  }
  v6 = pArg1[9];
  if ( v6 != nullptr && pArg2[9] != nullptr )
    sub_492980(v6, pArg2[9]);
  v7 = pArg1[10];
  if ( v7 != nullptr && pArg2[10] != nullptr )
    sub_492980(v7, pArg2[10]);
  result = (void **)pArg1;
  v9 = pArg1[11];
  if ( v9 != nullptr )
  {
    result = (void **)pArg2[11];
    if ( result != nullptr )
      result = sub_492980(v9, pArg2[11]);
  }
  v10 = pArg1[12];
  if ( v10 != nullptr )
  {
    result = (void **)pArg2[12];
    if ( result != nullptr )
      return sub_492980(v10, pArg2[12]);
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
void /*thiscall*/ sub_4AF720(uint32_t *this)
{
  int *v2; // esi
  int *fld_e1972; // ecx
  int v4; // eax
  int v5; // edx

  v2 = nullptr;
  if ( *(this + 29) != 0 )
    v2 = (int *)sub_45EAC0(this);
  fld_e1972 = (int *)*(this + 1972);
  if ( fld_e1972 != v2 )
  {
    if ( fld_e1972 != nullptr )
    {
      v4 = *fld_e1972;
      *((uint8_t *)fld_e1972 + 976) = 0;
      (*(void (/*stdcall*/ **)(uint32_t, int, uint32_t, int))(v4 + 284))(0, -16715521, 0, 1);
    }
    if ( v2 != nullptr )
    {
      v5 = *v2;
      *((uint8_t *)v2 + 976) = 1;
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int))(v5 + 284))(v2, 1, -16715521, 0, 1);
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
int /*thiscall*/ sub_4AF790(int *this)
{
  int i; // edi
  int v3; // ebx
  int v4; // eax

  for ( i = 0; i < 190; ++i )
  {
    if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, i) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, i) + 124) == 1 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, i);
      (*(void (/*thiscall*/ **)(int *, int, int))(v3 + 1304))(this, i, v4);
    }
  }
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 676))(this, 2);
}



// ------------------------------------------------------------
// 0x4AF7F0 sub_4AF7F0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 按场景类型发出 UI 通知。vt+308 本地玩家判定通过后按 (dword_8F7A24+12):
//   场景 3 → 事件 43; 场景 4 → 事件 58; 场景 6 → 事件 95 + sub_48FCE0(*(this+8016)) 一字节载荷。
//   sub_423200/sub_423290/sub_423380 = UI 消息构造（类型/载荷/发送，见 0x4AF9A0 同族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF7F0(int *this)
{
  int result; // eax
  int fld_e2004; // eax
  uint8_t v4[4]; // [esp+4h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 12);
    switch ( result )
    {
      case 3:
        sub_423200(dword_8F7B08, 43);  // 【发送网络包API】
        return sub_423380(dword_8F7B08);
      case 4:
        sub_423200(dword_8F7B08, 58);  // 【发送网络包API】
        return sub_423380(dword_8F7B08);
      case 6:
        sub_423200(dword_8F7B08, 95);  // 【发送网络包API】
        fld_e2004 = sub_48FCE0(*(this + 2004));
        if ( fld_e2004 == -1 )
          LOBYTE(fld_e2004) = -1;
        v4[0] = fld_e2004;
        sub_423290(v4, 1);
        return sub_423380(dword_8F7B08);
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
int /*thiscall*/ sub_4AF8B0(uint32_t *this, int pArg2)
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
int /*thiscall*/ sub_4AF8E0(int this, int nArg2)
{
  uint64_t fld_208; // rax
  int pThis_2A0; // eax

  sub_4D4CE0((char *)this, nArg2);
  if ( *(uint32_t *)(this + 512) == 4 )
  {
    *(uint32_t *)(this + 512) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1176))(this);
    *(uint8_t *)(this + 516) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1180))(this);
  }
  if ( *(uint32_t *)(this + 520) == -1 )
    *(uint32_t *)(this + 520) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1184))(this);
  if ( *(uint32_t *)(this + 524) == -1082130432 )
    *(float *)(this + 524) = ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)this + 1188))(this);
  LODWORD(fld_208) = *(uint32_t *)(this + 520);
  if ( (int)fld_208 > 0 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
    fld_208 = (uint64_t)((2.0 - COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1292))) * (double)*(int *)(this + 520));
    *(uint32_t *)(this + 520) = fld_208;
  }
  return fld_208;
}



// ------------------------------------------------------------
// 0x4AF9A0 sub_4AF9A0
// ------------------------------------------------------------
// 【解读】
//   【推断】★ UI 包构造: 事件 50。流程: vt+308 玩家判定 → vt+792(this, a2) 取对象 →
//   发事件 50 → 载荷依次: vt+120(x, 2B)、vt+124(y, 2B)、字节 3(1B)、a2(2B)、1(4B) → 发送。
//   **双坐标 + 类型 + 目标 ID 的纯坐标型通知**（疑似"标记/路径点"）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF9A0(void *this, int nArg2)
{
  char result; // al
  int nArg22; // ebx

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    nArg22 = nArg2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2) != 0 )
    {
      sub_423200(dword_8F7B08, 50);  // 【发送网络包API】
      nArg2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
      sub_423290(&nArg2, 2);
      nArg2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
      sub_423290(&nArg2, 2);
      HIBYTE(nArg2) = 3;
      sub_423290((char *)&nArg2 + 3, 1);
      nArg2 = nArg22;
      sub_423290(&nArg2, 2);
      nArg2 = 1;
      sub_423290(&nArg2, 4);
      sub_423380(dword_8F7B08);
      return 1;
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
char /*thiscall*/ sub_4AFA70(void *this, int nArg2, int nArg3)
{
  char result; // al
  int nArg22; // edi

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    nArg22 = nArg2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2) != 0 )
    {
      sub_423200(dword_8F7B08, 18);  // 【发送网络包API】
      HIBYTE(nArg2) = 3;
      sub_423290((char *)&nArg2 + 3, 1);
      HIBYTE(nArg2) = 1;
      sub_423290((char *)&nArg2 + 3, 1);
      nArg2 = nArg3;
      sub_423290(&nArg2, 2);
      nArg2 = nArg22;
      sub_423290(&nArg2, 2);
      nArg2 = 1;
      sub_423290(&nArg2, 4);
      sub_423380(dword_8F7B08);
      return 1;
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
int /*thiscall*/ sub_4AFB30(int *this, uint32_t *uArg2, int nArg3, int nArg4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *((uint8_t *)this + 404) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 8);
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
int /*thiscall*/ sub_4AFB80(uint32_t *this, int nArg2, int nArg3, char pszArg4)
{
  int fld_e1996; // ecx

  fld_e1996 = *(this + 1996);
  if ( fld_e1996 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1996 + 80))(fld_e1996) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1000))(this) != 0
    && pszArg4 == 0
    && *((float *)this + 1997) * 100.0 > (double)(int)sub_445870(87723146, 10000) )
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
int /*thiscall*/ sub_4AFBF0(uint8_t *this, uint32_t *uArg2, int nArg3)
{
  int result; // eax

  result = sub_4D5A60(this, uArg2, nArg3);
  if ( result != 3 && *(this + 7992) != 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x4AFC30 sub_4AFC30
// ------------------------------------------------------------
// 【解读】
//   【推断】0x4AFBF0 的配对: 清 this+7992 后调 sub_4D4A80（IRDActiveObject_vmt204 观察者广播）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC30(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  *((uint8_t *)this + 7992) = 0;
  return sub_4D4A80(this, nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x4AFC40 sub_4AFC40
// ------------------------------------------------------------
// 【解读】
//   【推断】vt+308 玩家判定 → vt+792(this, a2) 取对象 → 调其 vt+268。
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC40(void *this, int nArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, nArg2);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 268))(result);
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
char /*thiscall*/ sub_4AFC80(uint32_t *this, int nArg2, int nArg3, char pszArg4)
{
  int v5; // ecx
  int v6; // eax
  int v8; // [esp-8h] [ebp-10h]

  if ( nArg2 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) )
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 4 && *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) == 3 )
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) - nArg2;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1216))(this);
      sub_4527A0(v6, v8);
    }
    else if ( v5 == 6 )
    {
      sub_42B510(*(uint32_t *)(dword_8F7A24 + 40));
    }
  }
  return sub_4D5900(this, nArg2, nArg3, pszArg4);
}



// ------------------------------------------------------------
// 0x4AFD00 sub_4AFD00
// ------------------------------------------------------------
// 【解读】
//   【推断】★ 可行动判定: vt+1196 == 0 且 vt+724 == 0（未冻结），
//   且大状态(+6556) ∈ {0, 11} 或 (== 8 且 vt+1140(171) > 0) → true。
//   **大状态 0/11/8 是"可自由行动"状态集**（0=待机、11=??、8=?? 且带 171 号条件）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AFD00(uint32_t *this)
{
  int fld_e1639; // eax
  bool result; // al

  result = false;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1196))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    fld_e1639 = *(this + 1639);
    if ( fld_e1639 == 0 || fld_e1639 == 11 || fld_e1639 == 8 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 171) > 0 )
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
int /*thiscall*/ sub_4AFD50(uint8_t *this, char pszArg2)
{
  int result; // eax
  bool fld_e7730; // al
  char fld_e77302; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    fld_e7730 = *(this + 7730) != 0 && pszArg2 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1140))(this, 170) > 0;
    fld_e77302 = fld_e7730;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 169);
    return sub_47E440(fld_e77302);
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
uint8_t */*thiscall*/ sub_4AFDB0(uint8_t **this, int nArg2, int nArg3)
{
  uint8_t *result; // eax
  uint8_t **pThis_651; // esi
  int i; // ebx

  result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **))*this + 77))(this);
  if ( (uint8_t)result != 0 )
  {
    pThis_651 = this + 1617;
    for ( i = 18; i != 0; --i )
    {
      result = *pThis_651;
      if ( *pThis_651 != nullptr )
        result = (uint8_t *)(*(int (/*stdcall*/ **)(int *, int *))(*(uint32_t *)result + 144))(&nArg2, &nArg3);
      ++pThis_651;
    }
  }
  if ( (uint8_t **)dword_8F7C04 == this )
  {
    result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int))*this + 290))(this, nArg2);
    if ( result[376] != 0 )
      return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int, int))*this + 324))(this, nArg2, nArg3);
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
int /*thiscall*/ sub_4AFE30(uint32_t *this, int nArg2, int nArg3)
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
int /*thiscall*/ sub_4AFE70(uint32_t *this, int nArg2, int nArg3, int nArg4)
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
int /*thiscall*/ sub_4AFEA0(uint8_t *this, char pszArg2)
{
  int v2; // edx

  v2 = *(uint32_t *)this;
  *(this + 7730) = pszArg2;
  return (*(int (**)(void))(v2 + 1316))();
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
char /*thiscall*/ sub_4AFEC0(uint32_t *this)
{
  int fld_e1639; // eax
  int fld_e16392; // esi

  LOBYTE(fld_e1639) = dword_8F7C04;
  if ( (uint32_t *)dword_8F7C04 == this )
  {
    sub_483DF0((int *)dword_8F853C, 0);
    byte_9A0358 = 0;
    byte_9A0384 = 0;
    byte_9A03B0 = 0;
    byte_9A03DC = 0;
    byte_9A0408 = *(this + 1639) != 5;
    byte_9A0434 = *(this + 1639) != 5;
    byte_9A0460 = *(this + 1639) != 5;
    LOBYTE(fld_e1639) = *((uint8_t *)this + 7730);
    if ( (uint8_t)fld_e1639 != 0 )
    {
      fld_e1639 = *(this + 1639);
      switch ( fld_e1639 )
      {
        case 0:
          byte_9A03B0 = 1;
          byte_9A03DC = 1;
          goto LABEL_5;
        case 6:
          fld_e1639 = *(this + 1723);
          if ( fld_e1639 == 1 )
          {
            fld_e1639 = *(this + 1724);
            if ( fld_e1639 < *(this + 1725) )
            {
              LOBYTE(fld_e1639) = *((uint8_t *)this + 6988);
              byte_9A0358 = (uint8_t)fld_e1639 == 0;
            }
          }
          break;
        case 8:
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1328))(this, 1);
          break;
        case 11:
LABEL_5:
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 169);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 175);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 176);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 180);
          LOBYTE(fld_e1639) = sub_47E440(1);
          break;
        default:
          return fld_e1639;
      }
    }
    else
    {
      fld_e16392 = *(this + 1639);
      if ( fld_e16392 != 0 )
      {
        byte_9A0384 = fld_e16392 == 11;
      }
      else
      {
        byte_9A03B0 = 1;
        byte_9A03DC = 1;
        byte_9A0384 = 1;
      }
    }
  }
  return fld_e1639;
}


