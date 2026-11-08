// ============================================================
// 【40JP逆向源代码工程】creature/expeller_guard.cpp
// 模块: 怪物AI 0x5D —— 驱逐者八型/四属性守卫/锤王/邪眼/白魔 WZ 主状态机
// 来源: work/dump_monster.txt  区块: 0x5D0000-0x5E0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 251
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：本文件【无】—— 0x5D 段全部虚表在 +512 槽
//     继承基类 0x4D71B0（纯 Python 直读 PE 全域扫描证实）；守卫族行为差异 = 数据 + 技能函数
//   · ★ AI 大状态机总定案：0x5DE690（1082L, 本工程最大函数）= 白魔 WZ 大型主状态机 ——
//     switch(this+6556) 大状态 6/10/16/17/18/19/20/21 分派 + this+616 反应态 == -1 空闲门
//     （研究 15 三层状态架构的最完整客户端样本）；0x5D9BF0 亦读 this+612/616
//   · SUPERARMOR 霸体（0x5D47D0, 研究 20 §1.2 vt+720 霸体 setter 的调用侧）；
//     0x5D44D0/0x5D59B0 读 this+568 最后受击时刻
//   · 语音 TAG 组（R_DEFEN_GUARD_*/R_ICE_GUARD/R_HAMMER_KING/R_EXPELLER_*/EVIL_*/WZ_*）经
//     sub_4015C0 写语音槽，vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_699000=clock_now /
//     sub_47EF20=数据表读数 / sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽
//   · 驱逐者八型外观（0x5D7F80-0x5D88C0）：Expeller/AxeExpeller/HeavenExpeller/AxionExpeller/
//     TSMExpeller/LegionExpeller/SandorExpeller + Guard + HammerKing；四属性守卫特效族
//     ksguard_{light,wind,ice,protection,flame}.ani（0x5D6590-0x5D6AF0）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】守卫基础与蓄雷（0x5D0070-0x5D0DB0）
// 证据：this+8601/8603/8669 守卫字段区、BEFORE_THUNDER 蓄雷（0x5D0330 175L, 雷守卫）

// 子类扩展字段复位（this+8601/8603/8669 —— 守卫字段区）
// ------------------------------------------------------------
// 0x5D0070 sub_5D0070
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0070(int this)
{
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  sub_5CF180((uint32_t *)this);
  LOBYTE(v2) = 1;
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )
  {
    v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( v2 == 0 )
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
  }
  return v2;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D00D0 sub_5D00D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00D0(uint8_t *this, char a2, float a3, int a4, int a5)
{
  int result; // eax

  if ( *(this + 8669) == 1 )
    return sub_4E33D0(a2, a3, a4, a5);
  return result;
}



// AI 字段访问（this+8601/8812/8816）
// ------------------------------------------------------------
// 0x5D00F0 sub_5D00F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00F0(int this)
{
  *(uint8_t *)(this + 8601) = 0;
  *(uint32_t *)(this + 8816) = 0;
  *(uint32_t *)(this + 8812) = 0;
  return 0;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D0110 sub_5D0110
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0110(uint32_t *this, int a2)
{
  char result; // al
  int v4; // edi
  int v5; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17);
  if ( result == 1 )
  {
    v4 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 700))(v4);
    if ( (uint8_t)sub_53F660(*(this + 2203)) == 1 )
    {
      v5 = *(this + 2203) + 8;
      *(uint8_t *)(v5 + 13) = 0;
      *(uint8_t *)(v5 + 14) = 0;
      return sub_698F90(*(this + 2203) + 8, 20000, 0);
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2203) + 56))(
               *(this + 2203),
               v4,
               this,
               1,
               0,
               0,
               -1);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D01B0 sub_5D01B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D01B0(void *this, int a2, int a3, int a4)
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0((unsigned int)this + 7028) == 2 )
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1360))(this, a2);
  return sub_4DB480(a2, a3, a4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0200 sub_5D0200
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0200(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);
  *(this + 2204) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 2203) = 0;
  return result;
}



// 时钟门 AI（sub_699000; this+8600/8812..8837 守卫相位）
// ------------------------------------------------------------
// 0x5D0240 sub_5D0240
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0240(int this)
{
  int result; // eax

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8829) = 0;
  *(uint32_t *)(this + 8832) = 0;
  *(uint8_t *)(this + 8812) = 0;
  result = sub_699000(this + 36);
  *(uint32_t *)(this + 8824) = 0;
  *(uint8_t *)(this + 8837) = 0;
  *(uint32_t *)(this + 8816) = result;
  *(uint32_t *)(this + 8820) = 30;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0290 sub_5D0290
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0290(char *this, int a2)
{
  int result; // eax
  uint32_t *i; // ecx

  sub_4D4CE0(this, a2);
  result = 0;
  for ( i = this + 412; *i != 17; ++i )
  {
    if ( ++result >= 3 )
      return result;
  }
  *((uint32_t *)this + result + 103) = 6;
  *((uint32_t *)this + result + 109) = 8;
  *((uint32_t *)this + result + 106) = 1097859072;
  return result;
}



// AI 字段访问（this+8812/8824）
// ------------------------------------------------------------
// 0x5D02E0 sub_5D02E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D02E0(int this, int a2, int a3, int a4)
{
  unsigned int v5; // edi

  v5 = this + 7028;
  *(uint8_t *)(this + 8812) = sub_41A5E0(this + 7028) == 1;
  if ( sub_41A5E0(v5) == 1 )
    ++*(uint32_t *)(this + 8824);
  return sub_4DB480(a2, a3, a4);
}



// 蓄雷 AI：BEFORE_THUNDER 播报（175L；雷守卫蓄雷循环 —— 与 0x5A1BF0 基诺尔同族）
// ------------------------------------------------------------
// 0x5D0330 sub_5D0330
// ------------------------------------------------------------
int /*usercall*/ sub_5D0330@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // ecx
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  bool v13; // zf
  bool v14; // sf
  bool v15; // of
  int v16; // eax
  int v17; // ecx
  int v18; // [esp-38h] [ebp-108h]
  int v19; // [esp+4h] [ebp-CCh]
  uint32_t v20[23]; // [esp+8h] [ebp-C8h]
  uint32_t v21[12]; // [esp+64h] [ebp-6Ch]
  uint32_t v22[12]; // [esp+94h] [ebp-3Ch]
  float v23; // [esp+C4h] [ebp-Ch]
  int v24; // [esp+C8h] [ebp-8h]
  int v25; // [esp+CCh] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    v5 = *a1;
    v22[10] = 10;
    v21[0] = 10;
    v22[0] = 0;
    v22[1] = 1;
    v22[2] = 2;
    v22[3] = 3;
    v22[4] = 4;
    v22[5] = 5;
    v22[6] = 6;
    v22[7] = 7;
    v22[8] = 8;
    v22[9] = 9;
    v22[11] = 11;
    v19 = 50;
    v20[0] = 0;
    v20[1] = 150;
    v20[2] = 0;
    v20[3] = 250;
    v20[4] = 0;
    v20[5] = 350;
    v20[6] = 0;
    v20[7] = 450;
    v20[8] = 0;
    v20[9] = 550;
    v20[10] = 0;
    v20[11] = 650;
    v20[12] = 0;
    v20[13] = 750;
    v20[14] = 0;
    v20[15] = 850;
    v20[16] = 0;
    v20[17] = 950;
    v20[18] = 0;
    v20[19] = 1050;
    v20[20] = 0;
    v20[21] = 1150;
    v20[22] = 0;
    v21[1] = 20;
    v21[2] = 30;
    v21[3] = 40;
    v21[4] = 50;
    v21[5] = 60;
    v21[6] = 70;
    v21[7] = 80;
    v21[8] = 90;
    v21[9] = 100;
    v21[10] = 110;
    v21[11] = 120;
    v25 = (*(int (/*thiscall*/ **)(int *))(v5 + 152))(a1) != 1 ? -1 : 1;
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1) + 148) == v22[a1[2208]]
      && *((uint8_t *)a1 + 8829) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "BEFORE_THUNDER", -1, 0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 && a1[2208] > 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 120))(a1, a2, a3);
        v7 = a1[2208];
        v24 = v6;
        v8 = (uint64_t)((double)v6 + (double)v20[2 * v7 - 1] * 0.5 * (double)v25);
        v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
        v9 = a1[1813];
        v10 = (uint64_t)((double)v25 + (double)(int)v20[2 * a1[2208]] * 0.5);
        v25 = v10;
        v24 = 1;
        if ( v9 != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 124))(v9);
          v12 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
          v15 = __OFSUB__(v11, v12);
          v13 = v11 == v12;
          v14 = v11 - v12 < 0;
          v10 = v25;
          v24 = 2 * !(v14 ^ v15 | v13) - 1;
        }
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*a1 + 584))(
          a1,
          v8,
          v10,
          0,
          v8,
          v10,
          30070,
          10,
          0,
          4,
          a1[1908] != 0 ? 100 : 130,
          1);
        v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 740))(a1);
        v16 = *a1;
        v23 = (double)v25 * 0.5;
        v25 = (*(int (/*thiscall*/ **)(int *))(v16 + 736))(a1);
        if ( (double)v25 < v23 )
        {
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 584))(
            a1,
            v8,
            v24 * v21[a1[2208]] + v10,
            0,
            v8,
            v24 * v21[a1[2208]] + v10,
            30070,
            10,
            0,
            4,
            a1[1908] != 0 ? 100 : 130,
            1,
            0,
            0);
          if ( *((uint8_t *)a1 + 8836) == 1 )
          {
            v18 = v10 - v24 * v21[a1[2208]];
            (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 584))(
              a1,
              v8,
              v18,
              0,
              v8,
              v18,
              30070,
              10,
              0,
              4,
              a1[1908] != 0 ? 100 : 130,
              1,
              0,
              0);
          }
        }
      }
      *((uint8_t *)a1 + 8829) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
    v17 = a1[2208];
    if ( *(uint32_t *)(result + 148) == v22[v17] + 1 )
    {
      *((uint8_t *)a1 + 8829) = 0;
      a1[2208] = v17 + 1;
    }
  }
  return result;
}


// AI 字段访问（this+8603）
// ------------------------------------------------------------
// 0x5D06E0 sub_5D06E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D06E0(uint8_t *this, int a2, int a3, int a4)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 && (uint8_t)a4 == 0 && *(this + 8603) == 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, a2, a3, 0);
  return sub_5CEFF0(this, a2, a3, a4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0730 sub_5D0730
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0730(void *this, int a2)
{
  int result; // eax

  result = sub_4DBA80(a2);
  if ( a2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, 0, 0, 0);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0760 sub_5D0760
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0760(void *this, int a2)
{
  int result; // eax

  result = sub_4DBC20(a2);
  if ( a2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0790 sub_5D0790
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0790(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 2213) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D07B0 sub_5D07B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07B0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 2207) = 0;
  return result;
}



// AI 相位字段（this+8600/8812..8820）
// ------------------------------------------------------------
// 0x5D07D0 sub_5D07D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07D0(int this)
{
  *(uint8_t *)(this + 8812) = 0;
  *(uint32_t *)(this + 8816) = 0;
  *(uint8_t *)(this + 8820) = 0;
  *(uint8_t *)(this + 8600) = 0;
  return 0;
}



// AI 字段访问（this+8722）
// ------------------------------------------------------------
// 0x5D07F0 sub_5D07F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07F0(uint8_t *this, uint8_t *a2)
{
  int result; // eax

  if ( a2 == *((uint8_t **)this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 316))(this) != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  result = sub_4D9170(a2);
  if ( a2 == this && *(this + 8722) == 1 )
    return (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0850 sub_5D0850
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D0850(uint32_t *this, int a2, int a3)
{
  *this = &CNRDParticleCreater::`vftable';
  sub_423A20(this + 1);
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *((uint8_t *)this + 156) = 0;
  *(this + 40) = 100;
  *(this + 41) = 100;
  *(this + 42) = 100;
  *((uint8_t *)this + 172) = 1;
  *((uint8_t *)this + 180) = 0;
  *(this + 44) = &off_6C2B88;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 1;
  *((uint8_t *)this + 190) = 0;
  *((uint8_t *)this + 189) = 0;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *(this + 48) = 0;
  sub_4902C0(this);
  sub_490D40(a2, a3);
  return this;
}



// AI 相位字段（this+8669/8722）
// ------------------------------------------------------------
// 0x5D0950 sub_5D0950
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0950(uint32_t *this)
{
  char *v2; // eax
  uint32_t *v3; // ecx

  if ( *((uint8_t *)this + 8669) == 1 )
  {
    sub_4E0120();
    if ( *(this + 1787) == 5 )
      goto LABEL_6;
    if ( *((uint8_t *)this + 8722) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
      *((uint8_t *)this + 8722) = 0;
    }
    if ( *(this + 1787) == 5 )
    {
LABEL_6:
      if ( *((uint8_t *)this + 8722) == 0 )
      {
        if ( *(this + 2202) < 0x10u )
          v2 = (char *)(this + 2197);
        else
          v2 = (char *)*(this + 2197);
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(this, v2, 10, 0, 0);
        *((uint8_t *)this + 8722) = 1;
      }
    }
    switch ( *(this + 1787) )
    {
      case 0:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
        break;
      case 4:
        v3 = this;
        if ( *(this + 1813) != 0 )
          goto LABEL_19;
        goto LABEL_14;
      case 5:
        if ( *(this + 1813) == 0 )
LABEL_14:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
        break;
      case 0xD:
      case 0xE:
      case 0xF:
        if ( *(this + 1813) != 0 )
        {
          v3 = this;
LABEL_19:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(v3, 5);
        }
        break;
      default:
        return;
    }
  }
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5D0A60 sub_5D0A60
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0A60(uint32_t *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // ebx
  BOOL v9; // [esp+Ch] [ebp-8h]
  uint32_t *v10; // [esp+10h] [ebp-4h]

  v2 = *(this + 2187);
  v3 = (int)(this + 2181);
  v10 = this + 2181;
  v4 = sub_699000((int)(this + 2181));
  if ( v4 >= v2 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
      && *(this + 1787) != 22 )
    {
      v5 = *(this + 1813);
      if ( v5 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)v5 + 40))(17) != 0 )
      {
        v6 = *(this + 1813);
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 840))(v6) == 8
          || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 840))(v6) == 7
          || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 273) != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 840))(v6) == 12;
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 152))(*(this + 1813));
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != v7
          && v9
          && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v6, 0) < 150
          && rand() % 100 < *(this + 2179) )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 22);
        }
        v3 = (int)v10;
      }
    }
    *(uint8_t *)(v3 + 13) = 0;
    *(uint8_t *)(v3 + 14) = 0;
    LOBYTE(v4) = sub_698F90(v3, 100, 0);
  }
  return v4;
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0BA0 sub_5D0BA0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0BA0(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
    else
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
        {
          v2 = *(uint32_t *)(this + 7252);
          if ( v2 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)v2 + 120))();
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
              && ((v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < v4)
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
            {
              if ( rand() % 100 < 10 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0CC0 sub_5D0CC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0CC0(float *this, int a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // ebx
  uint64_t v8; // rax
  float v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // [esp+4h] [ebp-Ch]
  int v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 && a2 <= 5 )
  {
    v4 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 29) + 132) + 44);
    v5 = *(uint32_t *)(v4 + 364);
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(v4 + 368) - v5) >> 5;
    else
      v6 = 0;
    v7 = 224 * v6 / (a2 + 1);
    v12 = v7;
    result = 120 * (sub_424FF0() + 3) / 2;
    v14 = result;
    if ( a2 > 0 )
    {
      do
      {
        v8 = (uint64_t)((double)*(int *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(
                                                  this,
                                                  0)
                              * *(this + 2233));
        v9 = *this;
        v13 = v8;
        v10 = (*(int (/*fastcall*/ **)(float *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                this,
                HIDWORD(v8),
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        v11 = (*(int (/*thiscall*/ **)(float *, int, int, int, uint32_t, int))(*(uint32_t *)this + 376))(
                this,
                v13,
                v7,
                v14,
                0,
                v10);
        (*(void (/*thiscall*/ **)(float *, int, int))(LODWORD(v9) + 592))(this, 50068, v11);
        v7 += v12;
        result = --a2;
      }
      while ( a2 != 0 );
    }
  }
  return result;
}



// ============================================================
// 【分区 2】驱逐者碎片与防御守卫（0x5D0DB0-0x5D2470）
// 证据：Particle/{HeavenExpellerBrokenParts,ExpellerBrokenParts,TSMShattered,AxeExpeller-
//       BrokenParts}.ptl 破碎粒子四型、R_DEFEN_GUARD_LAUGH 防御守卫笑声、LIGHT_GUARD_SHINE
//       光守卫闪耀、FIRE_GUARD_LAUGH 火守卫笑声、CONDITION_HASTE/SLOW 状态播报

// AI 字段访问
// ------------------------------------------------------------
// 0x5D0DB0 sub_5D0DB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0DB0(void *this)
{
  int result; // eax

  sub_5D0BA0((int)this);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result == 1 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  return result;
}



// 天界驱逐者破碎：引用 Particle/HeavenExpellerBrokenParts.ptl（23L）
// ------------------------------------------------------------
// 0x5D0DE0 sub_5D0DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0DE0(uint32_t *this)
{
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
             this,
             this + 91,
             "Particle/HeavenExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(
             this,
             *(this + 91),
             "Particle/HeavenExpellerBrokenParts.ptl");
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0E40 sub_5D0E40
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0E40(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
        {
          v2 = *(uint32_t *)(this + 7252);
          if ( v2 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)v2 + 120))();
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
              && ((v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < v4)
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
            {
              if ( rand() % 100 < 20 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0F80 sub_5D0F80
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0F80(int this)
{
  int v2; // edi
  int v3; // edi
  int v4; // [esp+4h] [ebp-4h]

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 )
        {
          v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
          if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v2
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
            && ((v3 = *(uint32_t *)(this + 7252),
                 (v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3))
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
          {
            if ( rand() % 100 < 1 )
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}



// 破碎粒子：Particle/ExpellerBrokenParts.ptl + Particle/TSMShattered.ptl（TSM 型专用碎屑）
// ------------------------------------------------------------
// 0x5D10A0 sub_5D10A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D10A0(int *this)
{
  int *v2; // eax
  uint32_t *v3; // eax
  uint32_t *result; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  if ( (unsigned int)*(this + 96) < 0x10 )
    v2 = this + 91;
  else
    v2 = (int *)*(this + 91);
  (*(void (/*thiscall*/ **)(int *, int *, const char *))(*this + 1352))(this, v2, "Particle/ExpellerBrokenParts.ptl");
  v3 = operator new(0xECu);
  if ( v3 != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      result = sub_5D0850(v3, (int)(this + 91), (int)"Particle/TSMShattered.ptl");
    else
      result = sub_5D0850(v3, *(this + 91), (int)"Particle/TSMShattered.ptl");
  }
  else
  {
    result = nullptr;
  }
  *(this + 2213) = (int)result;
  return result;
}



// 斧驱逐者破碎：引用 Particle/AxeExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D1160 sub_5D1160
// ------------------------------------------------------------
int /*thiscall*/ sub_5D1160(uint32_t *this)
{
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
             this,
             this + 91,
             "Particle/AxeExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(
             this,
             *(this + 91),
             "Particle/AxeExpellerBrokenParts.ptl");
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D11C0 sub_5D11C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D11C0(uint32_t *this)
{
  if ( *((uint8_t *)this + 8669) == 1 )
    sub_5D0950(this);
}



// 防御守卫笑声：R_DEFEN_GUARD_LAUGH 播报（168L；嘲讽循环【推断】）
// ------------------------------------------------------------
// 0x5D11D0 sub_5D11D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D11D0(uint32_t *this, int a2, float *a3, int a4)
{
  int v4; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  float v11; // edx
  float v12; // eax
  float v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int v19; // edx
  int v20; // eax
  int v21; // ebx
  int v22; // edx
  int v23; // eax
  int v24; // ebx
  uint8_t *v25; // eax
  uint8_t *v26; // eax
  int v27; // edx
  int v28; // eax
  uint32_t *v29; // eax
  int v31; // [esp+10h] [ebp-60h]
  int v32; // [esp+14h] [ebp-5Ch]
  int v33; // [esp+18h] [ebp-58h]
  int v34; // [esp+20h] [ebp-50h]
  int v35; // [esp+24h] [ebp-4Ch]
  float v36; // [esp+34h] [ebp-3Ch] BYREF
  float v37; // [esp+38h] [ebp-38h]
  float v38; // [esp+3Ch] [ebp-34h]
  int v39; // [esp+40h] [ebp-30h]
  int v40; // [esp+44h] [ebp-2Ch]
  int v41; // [esp+48h] [ebp-28h]
  uint8_t v42[4]; // [esp+4Ch] [ebp-24h] BYREF
  void *Block; // [esp+50h] [ebp-20h]
  int v44; // [esp+54h] [ebp-1Ch]
  int v45; // [esp+58h] [ebp-18h]
  int v46; // [esp+5Ch] [ebp-14h] BYREF
  char v47; // [esp+63h] [ebp-Dh] BYREF
  int v48; // [esp+6Ch] [ebp-4h]

  v4 = a2;
  if ( a2 != 0 )
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
  else
    v6 = 0;
  if ( *(this + 2175) == -1
    && *(this + 2210) != 2
    && v6 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 308))(v6) == 1 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
    if ( v7 != 0 )
    {
      v8 = *(this + 2210);
      LODWORD(v37) = 42004;
      LODWORD(v38) = 42003;
      v39 = 42005;
      v40 = 42006;
      v41 = 48011;
      if ( v8 == 0 && *(uint32_t *)(v7 + 12) == 0 )
      {
        v44 = 48011;
        goto LABEL_15;
      }
      if ( v8 == 1 && *(uint32_t *)(v7 + 12) == 1 )
      {
        v44 = *((uint32_t *)&v37 + *(uint32_t *)(v7 + 20));
        if ( v44 != 0 )
        {
LABEL_15:
          v9 = *this;
          v46 = 0;
          v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, float *, uint32_t))(v9 + 628))(
                  this,
                  &v47,
                  v42,
                  100,
                  a2,
                  a3,
                  0);
          v11 = *a3;
          v45 = v10;
          v12 = a3[1];
          v36 = v11;
          v13 = a3[2];
          v37 = v12;
          v14 = *((uint32_t *)a3 + 3);
          v38 = v13;
          v15 = *((uint32_t *)a3 + 4);
          v39 = v14;
          v16 = *((uint32_t *)a3 + 5);
          v40 = v15;
          v17 = *(uint32_t *)v6;
          v41 = v16;
          v18 = (*(int (/*thiscall*/ **)(int))(v17 + 120))(v6);
          v19 = rand() % 60;
          v20 = *(uint32_t *)v6;
          Block = (void *)(v18 + v19 - 30);
          v36 = (float)(int)Block;
          v21 = (*(int (/*thiscall*/ **)(int))(v20 + 124))(v6);
          v22 = rand() % 60;
          v23 = *(uint32_t *)v6;
          Block = (void *)(v21 + v22 - 30);
          v37 = (float)(int)Block;
          v24 = (*(int (/*thiscall*/ **)(int))(v23 + 128))(v6);
          Block = (void *)(v24 + rand() % 60 - 30);
          v38 = (float)(int)Block;
          v25 = operator new(0x80u);
          Block = v25;
          v48 = 0;
          if ( v25 != nullptr )
          {
            *(float *)&v33 = (float)v45;
            v26 = sub_4D6810(v25, v33, 500, 1, 1);
          }
          else
          {
            v26 = nullptr;
          }
          v27 = *(uint32_t *)v26;
          v48 = -1;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v27 + 56))(
            v26,
            this,
            this,
            0,
            0,
            0,
            -1);
          v35 = sub_605840(&v46, v6, &v36, 1);
          v34 = v46;
          v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 128))(v6);
          v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 124))(v6);
          v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6);
          sub_4E4A50(this, v44, v45, v28, v31, v32, 1, 0, v34, v35);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "R_DEFEN_GUARD_LAUGH",
            -1,
            0,
            0);
          v4 = a2;
          goto LABEL_23;
        }
      }
    }
    if ( *(this + 1697) < 0x10u )
      v29 = this + 1692;
    else
      v29 = (uint32_t *)*(this + 1692);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v29, -1, 0, 0);
  }
LABEL_23:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)a4 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, float *, uint32_t))(*this + 1336))(this, v4, a3, 0);
  return sub_5CEFF0(v4, a3, a4);
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D1490 sub_5D1490
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5D1490(int a1, int a2, uint32_t *a3)
{
  uint32_t *result; // eax

  result = operator new(0x14u);
  if ( result != nullptr )
  {
    *result = a1;
    result[1] = a2;
    result[2] = *a3;
    result[3] = a3[1];
    result[4] = a3[2];
  }
  return result;
}



// 时钟门 AI（sub_699000, 101L）
// ------------------------------------------------------------
// 0x5D14D0 sub_5D14D0
// ------------------------------------------------------------
char /*usercall*/ sub_5D14D0@<al>(int *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  bool v5; // al
  int v6; // eax
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // eax
  uint32_t *v11; // edi
  int i; // ebx
  int v13; // eax
  int *v14; // eax
  uint32_t *v15; // edi
  int j; // ebx
  float v19; // [esp-4h] [ebp-Ch]

  if ( *((uint8_t *)a1 + 8668) == 1 && a1[2175] == 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*a1 + 144))(a1);
    v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 200))(a1, 0);
    sub_493400(v3, 1);
    v4 = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
    sub_4939E0(v4, 1);
    v5 = sub_4E7F30(a1, 200, 200, 0) == 0;
    *((uint8_t *)a1 + 8668) = v5;
    if ( !v5 )
    {
      *((uint8_t *)a1 + 8685) = 0;
      *((uint8_t *)a1 + 8686) = 0;
      sub_698F90((int)(a1 + 2168), 2000, 0);
      a1[2175] = 1;
    }
  }
  v6 = a1[2175];
  if ( v6 == 1 )
  {
    v7 = a1[2174];
    v6 = sub_699000((int)(a1 + 2168));
    if ( v6 >= v7 )
    {
      v8 = *a1;
      a1[2175] = 2;
      v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 200))(a1);
      sub_4926A0(v9);
      v10 = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
      LOBYTE(v6) = sub_4939E0(v10, 0);
    }
  }
  else if ( v6 == 2 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
    if ( *(uint8_t *)(v6 + 170) == 1 )
    {
      v11 = a1 + 2156;
      for ( i = 8; i != 0; --i )
      {
        if ( *v11 != 0 )
        {
          v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 784))(a1, *v11);
          if ( v13 != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 4))(v13, 1);
        }
        ++v11;
      }
      a1[1639] = 0;
      *((uint8_t *)a1 + 8669) = 1;
      a1[2175] = -1;
      if ( (unsigned int)a1[2195] < 0x10 )
        v14 = a1 + 2190;
      else
        v14 = (int *)a1[2190];
      (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*a1 + 212))(a1, v14, -1, 0, 0, a2);
      if ( *((uint8_t *)a1 + 7801) != 0 && *((uint8_t *)a1 + 8723) == 1 )
        sub_4DB130(24, 0);
      if ( a1[2188] != 1065353216 )
      {
        v19 = *((float *)a1 + 2188);
        (*(void (/*thiscall*/ **)(int *))(*a1 + 688))(a1);
        sub_4EB2C0(v19);
        v15 = a1 + 2156;
        for ( j = 8; j != 0; --j )
        {
          if ( *v15 != 0 )
            sub_4EB6A0(*((float *)a1 + 2188));
          ++v15;
        }
        a1[40] = (uint64_t)((double)a1[40] * *((float *)a1 + 2188));
      }
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 820))(a1, 1);
    }
  }
  return v6;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D16D0 sub_5D16D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D16D0(uint32_t *this)
{
  uint32_t *v2; // edi
  int i; // ebx
  uint32_t *j; // edi
  uint32_t *k; // edi
  uint32_t *v6; // ebx
  int v7; // eax
  uint32_t *v8; // edi
  uint32_t *v9; // ebx
  uint32_t *n; // ebx
  uint32_t *ii; // ebx
  bool v12; // zf
  int result; // eax
  int v14; // [esp+Ch] [ebp-10h]
  int v15; // [esp+10h] [ebp-Ch]
  uint32_t *v16; // [esp+14h] [ebp-8h]
  int m; // [esp+18h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1540));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1541));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1542));
  v2 = this + 1543;
  for ( i = 2; i != 0; --i )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *v2++);
  for ( j = (uint32_t *)*(this + 1550); j != (uint32_t *)*(this + 1551); ++j )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *j);
  for ( k = (uint32_t *)*(this + 1554); k != (uint32_t *)*(this + 1555); ++k )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *k);
  v6 = this + 1617;
  v16 = this + 1617;
  v15 = 18;
  do
  {
    if ( *v6 != 0 )
    {
      v7 = (*(int (**)(void))(*(uint32_t *)*v6 + 248))();
      v8 = *(uint32_t **)(v7 + 4);
      v14 = v7;
      if ( v8 != *(uint32_t **)(v7 + 8) )
      {
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[1]);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[2]);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[3]);
          v9 = v8 + 4;
          for ( m = 2; m != 0; --m )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *v9++);
          for ( n = (uint32_t *)v8[11]; n != (uint32_t *)v8[12]; ++n )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *n);
          for ( ii = (uint32_t *)v8[15]; ii != (uint32_t *)v8[16]; ++ii )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *ii);
          v8 += 31;
        }
        while ( v8 != *(uint32_t **)(v14 + 8) );
        v6 = v16;
      }
    }
    ++v6;
    result = v15 - 1;
    v12 = v15 == 1;
    v16 = v6;
    --v15;
  }
  while ( !v12 );
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D1880 sub_5D1880
// ------------------------------------------------------------
int /*stdcall*/ sub_5D1880(int a1)
{
  int result; // eax
  int v2; // ecx

  result = a1;
  if ( a1 != 0 && a1 != -40 )
  {
    v2 = *(uint32_t *)(a1 + 44);
    if ( v2 != *(uint32_t *)(a1 + 48) )
    {
      do
      {
        *(uint32_t *)(v2 + 16) += 40;
        result = *(uint32_t *)(a1 + 48);
        v2 += 88;
      }
      while ( v2 != result );
    }
  }
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl（this+8600 相位）
// ------------------------------------------------------------
// 0x5D18E0 sub_5D18E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D18E0(uint8_t *this)
{
  char *v2; // eax
  int v3; // eax
  uint32_t *result; // eax

  *(this + 8600) = 0;
  *((uint32_t *)this + 1802) = 150;
  *((uint32_t *)this + 2176) = -1;
  *((uint32_t *)this + 2177) = -1;
  *((uint32_t *)this + 2178) = -1;
  if ( *((uint32_t *)this + 96) < 0x10u )
    v2 = this + 364;
  else
    v2 = *((char **)this + 91);
  (*(void (/*thiscall*/ **)(uint8_t *, char *, const char *))(*(uint32_t *)this + 1352))(
    this,
    v2,
    "Particle/ExpellerBrokenParts.ptl");
  if ( operator new(0x84u) != nullptr )
    v3 = sub_5FE2C0(1120403456);
  else
    v3 = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v3 + 56))(
    v3,
    this,
    this,
    0,
    0,
    0,
    -1);
  result = *((uint32_t **)this + 2153);
  *((uint32_t *)this + 2188) = 1066192077;
  *result = 900;
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1400;
  return result;
}



// AI 相位字段（this+8669）
// ------------------------------------------------------------
// 0x5D19C0 sub_5D19C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D19C0(int **this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  int v7; // eax
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp-10h] [ebp-18h]

  result = ((int (/*thiscall*/ *)(int **))(*this)[184])(this);
  if ( result <= 0 || (result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this)) != 14 || ArgList == 0 )
  {
    if ( ArgList == 14 && *((uint8_t *)this + 8669) == 1 )
    {
      sub_4926A0(**(this + 1554));
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[49])(this, **(this + 1554));
      ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    if ( *(this + 1639) == (int *)4 && ArgList == 0 )
    {
      result = ((int (/*thiscall*/ *)(int **))(*this)[235])(this);
      if ( (uint8_t)result == 0 )
      {
        result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
        if ( (uint8_t)result == 1 && *(this + 2207) == (int *)1 )
        {
          v9 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
          v8 = ((int (/*thiscall*/ *)(int **))(*this)[31])(this);
          v7 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this);
          result = sub_4E4A50(this, 30022, 0, v7, v8, 0, v9, 0, 0, 0);
        }
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, a3, a4, a5);
  }
  return result;
}



// 光守卫闪耀：LIGHT_GUARD_SHINE 播报（61L）
// ------------------------------------------------------------
// 0x5D1AD0 sub_5D1AD0
// ------------------------------------------------------------
int /*userpurge*/ sub_5D1AD0@<eax>(int a1@<ecx>, int a2@<ebx>, int ArgList, float a4, int a5, int a6)
{
  int result; // eax
  int v8; // eax
  uint64_t v9; // rax
  int *v10; // ebx
  int v11; // edi
  int v12; // eax

  result = ArgList;
  if ( ArgList == 32 )
  {
    if ( *(int *)(a1 + 8840) < 3 )
    {
      sub_4DB130(24, 1);
      result = *(uint32_t *)(a1 + 8840) + 1;
      *(uint32_t *)(a1 + 8840) = result;
      *(uint32_t *)(a1 + 8844) = result;
    }
  }
  else
  {
    sub_5D19C0((int **)a1, ArgList, a4, a5, a6);
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 840))(a1, a2) == 8
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 908))(a1) == 2 )
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        "LIGHT_GUARD_SHINE",
        -1,
        0);
      sub_4DB200(24, 2);
      *(uint8_t *)(a1 + 8848) = 0;
      sub_698F90(a1 + 8852, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 888))(a1, 4, 4, 1000, 1000);
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 672))(a1, 3);
      v9 = (uint64_t)((double)*(int *)(a1 + 8916) / (double)sub_41A5E0(v8 + 872) * 1000.0);
      v10 = *(int **)a1;
      v11 = *(uint32_t *)(a1 + 6216);
      *(uint32_t *)(a1 + 8880) = v9;
      v12 = ((int (/*fastcall*/ *)(int, uint32_t, uint32_t, uint32_t))v10[48])(a1, HIDWORD(v9), 0, 0);
      ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))v10[51])(a1, 1, *(uint32_t *)(v11 + 20), 0, -v12);
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 820))(a1, 0);
    }
    else
    {
      *(uint8_t *)(a1 + 8865) = 0;
      *(uint8_t *)(a1 + 8866) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *(uint32_t *)(*(uint32_t *)(a1 + 6216) + 20));
      *((uint32_t *)dword_8F8528 + 623) = 0;
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 820))(a1, 1);
    }
  }
  return result;
}



// 时钟门 AI（sub_699000; this+200/208）
// ------------------------------------------------------------
// 0x5D1C50 sub_5D1C50
// ------------------------------------------------------------
int /*thiscall*/ sub_5D1C50(int *this, int a2, int a3, int a4, float a5)
{
  uint64_t v6; // rax
  unsigned int v7; // edi
  int v8; // eax
  uint8_t v9; // bl
  unsigned int v10; // edi
  int v12; // [esp-24h] [ebp-30h]

  LODWORD(v6) = sub_5CF520(this, a2, a3, a4, a5);
  if ( (uint8_t)a2 != 0 )
  {
    v7 = sub_699000((int)(this + 2213));
    LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( (uint32_t)v6 == 8 )
    {
      LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);
      if ( (uint32_t)v6 == 2 && v7 != 0 )
      {
        LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
        if ( (uint32_t)v6 != 0 )
        {
          v8 = *(this + 2220);
          if ( v7 >= v8 )
          {
            v10 = v7 - v8;
            if ( v10 >= 0x1F4 )
              v9 = 0;
            else
              v9 = (uint64_t)((1.0 - sin((double)v10 * 0.003141592)) * 250.0);
            LODWORD(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
          }
          else
          {
            v6 = (uint64_t)((double)v7 * 250.0 / (double)v8);
            v9 = v6;
          }
          if ( v9 != 0 )
          {
            v12 = dword_79C0B0;
            (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
            LODWORD(v6) = sub_491DE0(v12, a3, a4, a5, 2, 1, -1, (v9 << 24) | 0xFFFFFF);
          }
        }
      }
    }
  }
  return v6;
}



// 守卫相位字段（this+8857/8858/8972/8976/9012）
// ------------------------------------------------------------
// 0x5D1D90 sub_5D1D90
// ------------------------------------------------------------
char /*thiscall*/ sub_5D1D90(int this, int ArgList, float a3, int a4, int a5)
{
  int v7; // eax

  if ( ArgList == 26 )
  {
    v7 = 1;
    goto LABEL_7;
  }
  if ( ArgList == 27 )
  {
    v7 = 2;
LABEL_7:
    *(uint32_t *)(this + 8972) = v7;
    *(uint32_t *)(this + 8976) = v7;
    return sub_5CF880((int *)this);
  }
  if ( ArgList != 28 )
    return sub_5D19C0((int **)this, ArgList, a3, a4, a5);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 944))(this, 1, 100000);
  *(uint8_t *)(this + 8857) = 0;
  *(uint8_t *)(this + 8858) = 0;
  sub_698F90(this + 8844, *(uint32_t *)(this + 9012), 0);
  return sub_698F90(this + 8944, 0, 0);
}



// 时钟门 AI（sub_699000; this+200）
// ------------------------------------------------------------
// 0x5D1E30 sub_5D1E30
// ------------------------------------------------------------
void /*thiscall*/ sub_5D1E30(int *this, int a2, int a3, int a4, float a5)
{
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // edi
  uint64_t v12; // rax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  uint8_t v16; // [esp+1Bh] [ebp+Bh]
  float v17; // [esp+1Ch] [ebp+Ch]
  int v18; // [esp+20h] [ebp+10h]
  int v19; // [esp+24h] [ebp+14h]

  sub_5CF520(this, a2, a3, a4, a5);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0 )
  {
    v7 = *(this + 2243);
    if ( (uint8_t)a2 == 1 )
    {
      if ( v7 != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )
      {
        sub_4938F0(*(this + 2245));
        v8 = a4 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        sub_491D00(dword_79C0B0, a3 + (LOBYTE(a5) != 0 ? 3 : -3), v8, a5);
      }
    }
    else if ( v7 == 2 )
    {
      v19 = *(this + 2254);
      v17 = 1.0;
      (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 1
        || (v9 = sub_699000((int)(this + 9)) - *(this + 1777)) <= 1000
        && (v17 = (double)(int)sub_423A80(255, 0, v9, 1000) * 0.0039215689) != 0.0 )
      {
        v10 = (uint32_t *)*(this + 2227);
        v11 = (uint32_t *)*v10;
        if ( (uint32_t *)*v10 != v10 )
        {
          do
          {
            v12 = (uint64_t)((double)v19 * 150.0 / (double)*(this + 2254) * v17);
            v16 = v12;
            --v19;
            if ( (uint8_t)v12 == 0 )
              break;
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
            v18 = sub_45E490(v11[2], *(uint32_t *)(v13 + 8));
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
            v15 = sub_45E4D0(v11[3], v11[4], *(uint32_t *)(v14 + 8), 1.0);
            sub_491DE0(dword_79C0B0, v18, v15, a5, 0, 0, 0, (v16 << 24) | 0xFFFFFF);
            v11 = (uint32_t *)*v11;
          }
          while ( v11 != (uint32_t *)*(this + 2227) );
        }
      }
    }
  }
}



// 状态播报：CONDITION_HASTE + CONDITION_SLOW + FIRE_GUARD_LAUGH 火守卫笑声（67L）
// ------------------------------------------------------------
// 0x5D2020 sub_5D2020
// ------------------------------------------------------------
int /*fastcall*/ sub_5D2020(uint8_t *a1, int a2, int ArgList, float a4, int a5, int a6)
{
  char v7; // bl
  void *v8; // ecx
  int result; // eax

  switch ( ArgList )
  {
    case 21:
    case 23:
      if ( ArgList == 21 )
      {
        v7 = a1[8840] + 1;
        if ( (unsigned int)(uint8_t)a1[8840] + 1 >= 2 )
          v7 = 2;
        sub_4DB200(24, 1);
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "CONDITION_HASTE",
          -1,
          0,
          0);
      }
      else
      {
        v7 = (a1[8840] - 1) & (((uint8_t)a1[8840] <= 1u) - 1);
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "CONDITION_SLOW",
          -1,
          0,
          0);
      }
      if ( v7 != a1[8840] )
      {
        LOBYTE(v8) = ArgList == 21;
        a1[8840] = v7;
        sub_5CFD80(a1, v8);
      }
      goto LABEL_9;
    case 22:
LABEL_9:
      sub_41A590((unsigned int)(a1 + 8841), a2, 0);
      result = sub_699000((int)(a1 + 36));
      *((uint32_t *)a1 + 2217) = result;
      break;
    case 31:
      sub_4DB130(24, 2);
      result = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
                 a1,
                 "FIRE_GUARD_LAUGH",
                 -1,
                 0,
                 0);
      break;
    default:
      result = sub_5D19C0((int **)a1, ArgList, a4, a5, a5);
      break;
  }
  return result;
}



// 守卫相位字段（this+8669/8828/8829/8836）
// ------------------------------------------------------------
// 0x5D2140 sub_5D2140
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2140(void *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  int v7; // eax
  int v8; // et2

  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) <= 0
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 14
    || (result = ArgList, ArgList == 0)
    || ArgList == 9 )
  {
    result = ArgList;
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )
        return result;
      sub_4926A0(**((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    else if ( ArgList == 8 )
    {
      *((uint8_t *)this + 8828) = 0;
      *((uint8_t *)this + 8836) = rand() % 100 < 30;
      if ( sub_41A5E0((unsigned int)this + 7028) != 0 )
      {
        result = sub_41A5E0((unsigned int)this + 7028);
        if ( result == 1 )
        {
          *((uint32_t *)this + 2206) = 0;
        }
        else
        {
          result = sub_41A5E0((unsigned int)this + 7028);
          if ( result == 3 )
          {
            *((uint8_t *)this + 8829) = 0;
            *((uint32_t *)this + 2208) = 0;
          }
        }
      }
      else
      {
        v7 = rand();
        v8 = v7 % 100;
        result = v7 / 100;
        if ( v8 < 10 )
          *((uint8_t *)this + 8828) = 1;
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, a3, a4, a5);
  }
  return result;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D2270 sub_5D2270
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2270(void *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this);
  if ( result <= 0
    || (result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this)) != 14
    || ArgList == 0
    || ArgList == 9 )
  {
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )
        return result;
      sub_4926A0(**((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, a3, a4, a5);
  }
  return result;
}



// 斧驱逐者破碎 2：Particle/AxeExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D2320 sub_5D2320
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2320(uint32_t *this)
{
  uint32_t *v2; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    v2 = this + 91;
  else
    v2 = (uint32_t *)*(this + 91);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
    this,
    v2,
    "Particle/AxeExpellerBrokenParts.ptl");
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5D2380 sub_5D2380
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2380(uint32_t *this)
{
  int v2; // edi
  int result; // eax
  uint32_t *v4; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(10));
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  result = sub_4EB2C0(v8);
  v4 = this + 2156;
  for ( i = 6; i != 0; --i )
  {
    if ( *v4 != 0 )
    {
      sub_4EB6E0(1.0);
      result = sub_4EB6A0(v8);
    }
    ++v4;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D2440 sub_5D2440
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5D2440(uint32_t *this)
{
  int v2; // ecx
  uint32_t **result; // eax

  v2 = *(this + 1);
  result = *(uint32_t ***)(v2 + 4);
  if ( result != (uint32_t **)v2 )
  {
    *result[1] = *result;
    (*result)[1] = result[1];
    j__free(result);
    result = (uint32_t **)(*(this + 2) - 1);
    *(this + 2) = result;
  }
  return result;
}



// ============================================================
// 【分区 3】锤王三连与四属性守卫语音（0x5D2470-0x5D3400）
// 证据：HAMMER_KING_01/02/03 三连段、R_ICE_GUARD 冰守卫语音、LEGION_SHOUT 军团呐喊、
//       this+8840/8853..8872 守卫相位字段

// RTTI cast 目标解算（this+8601/8603/8669, 76L）
// ------------------------------------------------------------
// 0x5D2470 sub_5D2470
// ------------------------------------------------------------
char /*thiscall*/ sub_5D2470(int this)
{
  int v2; // eax
  int v3; // eax
  unsigned int i; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v17; // [esp-8h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 2) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 2);
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v2 + 4))(v2, 0, this);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 11) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 11);
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v3 + 4))(v3, 0, this);
  }
  for ( i = 0; ; ++i )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
    v6 = *(uint32_t *)(v5 + 4);
    v7 = v6 != 0 ? (*(uint32_t *)(v5 + 8) - v6) >> 2 : 0;
    if ( (int)i >= v7 )
      break;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
    v9 = *(uint32_t *)(v8 + 4);
    if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * i);
    else
      v10 = 0;
    if ( *(uint32_t *)(v10 + 4) == this )
    {
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
      v12 = *(uint32_t *)(v11 + 4);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 8) - v12) >> 2 )
        v13 = *(uint32_t *)(v12 + 4 * i);
      else
        v13 = 0;
      v14 = __RTDynamicCast(v13, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeHp `RTTI Type Descriptor', 0);
      if ( v14 != 0 && *(float *)(v14 + 80) < 0.0 )
      {
        v17 = v14;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
        sub_53FE50(v17);
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  sub_5CF180((uint32_t *)this);
  LOBYTE(v15) = 1;
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )
  {
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( v15 == 0 )
      LOBYTE(v15) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
  }
  return v15;
}



// AI 字段访问（this+8723）
// ------------------------------------------------------------
// 0x5D25D0 sub_5D25D0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D25D0(float *this)
{
  double v2; // st7
  int v3; // eax
  double v4; // st7
  int v5; // eax
  float v6; // edx
  int v7; // eax
  float v8; // edx
  int v9; // eax
  float v10; // edx
  int v11; // eax
  float v12; // edx
  int v13; // eax
  float v14; // edx
  uint8_t *v15; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  v2 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v3 = *(uint32_t *)this;
  v4 = v2 * 0.0099999998;
  *(this + 2242) = v4;
  *(this + 2188) = v4;
  v5 = (*(int (/*thiscall*/ **)(float *, int))(v3 + 384))(this, 1);
  v6 = *this;
  *((uint32_t *)this + 2243) = v5;
  *((uint32_t *)this + 2244) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v6) + 384))(this, 2);
  v7 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v8 = *this;
  *((uint32_t *)this + 2245) = v7;
  *((uint32_t *)this + 2246) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v8) + 384))(this, 4);
  v9 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  v10 = *this;
  *(this + 2247) = (double)v9 * 0.0099999998;
  *((uint32_t *)this + 2248) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v10) + 384))(this, 6);
  v11 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v12 = *this;
  *((uint32_t *)this + 2249) = v11;
  *((uint32_t *)this + 2250) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v12) + 384))(this, 8);
  v13 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);
  v14 = *this;
  *((uint32_t *)this + 2251) = v13;
  *((uint32_t *)this + 2252) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v14) + 384))(this, 10);
  **((uint32_t **)this + 2153) = 1000;
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1600;
  v15 = (uint8_t *)(*((uint32_t *)this + 1905) + 96);
  *((uint8_t *)this + 8723) = 0;
  *v15 = 0;
  return sub_698F90((int)(this + 2210), 1000, 0);
}



// 锤王三连：HAMMER_KING_02 + HAMMER_KING_03 + HAMMER_KING_01 播报组（77L；
//   三段连击音序 —— 与 0x5D5F10 崩地全演出配套）
// ------------------------------------------------------------
// 0x5D2710 sub_5D2710
// ------------------------------------------------------------
int /*userpurge*/ sub_5D2710@<eax>(int a1@<ecx>, int a2@<edi>, int ArgList, float a4, int a5, int a6)
{
  int v7; // eax
  const char *v8; // eax
  bool v9; // zf
  uint32_t *v10; // edi
  int v11; // eax
  int v12; // eax
  uint64_t v13; // rax
  int v14; // ecx
  int v15; // eax
  int *v17; // [esp+18h] [ebp+14h]

  sub_5D19C0((int **)a1, ArgList, a4, a5, a6);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) == 8
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 908))(a1) == 3 )
  {
    sub_4DB130(24, *(uint32_t *)(a1 + 8932) + 2);
    v7 = *(uint32_t *)(a1 + 8932);
    if ( v7 != 0 )
    {
      v9 = v7 == 1;
      v8 = "HAMMER_KING_02";
      if ( !v9 )
        v8 = "HAMMER_KING_03";
    }
    else
    {
      v8 = "HAMMER_KING_01";
    }
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 212))(
      dword_8F7C04,
      v8,
      -1,
      0,
      0,
      a2);
    *(uint8_t *)(a1 + 8924) = 0;
    *(uint8_t *)(a1 + 8881) = 0;
    *(uint8_t *)(a1 + 8882) = 0;
    sub_698F90(a1 + 8868, 0, 0);
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 888))(a1, 4, 4, 1000, 1000);
    sub_4926A0(*(uint32_t *)(*(uint32_t *)(a1 + 6216) + 4));
    v10 = (uint32_t *)(*(uint32_t *)(a1 + 6216) + 4);
    v17 = *(int **)a1;
    v11 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1 + 192))(a1, 0, 0);
    ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))v17[51])(a1, 1, *v10, 0, -v11);
    v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 672))(a1, 3);
    v13 = (uint64_t)((double)*(int *)(a1 + 8992) / (double)sub_41A5E0(v12 + 872) * 1000.0);
    v14 = *(uint32_t *)(a1 + 8932) + 1;
    *(uint32_t *)(a1 + 8928) = v13;
    *(uint32_t *)(a1 + 8932) = v14;
    if ( v14 == 3 )
    {
      v15 = *(uint32_t *)(a1 + 7620);
      *(uint32_t *)(a1 + 8932) = 0;
      *(uint8_t *)(v15 + 96) = 0;
      *(uint8_t *)(a1 + 8953) = 0;
      *(uint8_t *)(a1 + 8954) = 0;
      sub_698F90(a1 + 8940, *(uint32_t *)(a1 + 9008), 0);
    }
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 820))(a1, 0);
  }
  else
  {
    *(uint8_t *)(a1 + 8881) = 0;
    *(uint8_t *)(a1 + 8882) = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *(uint32_t *)(*(uint32_t *)(a1 + 6216) + 4));
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 820))(a1, 1);
  }
}



// 时钟门 AI（sub_699000, 119L）
// ------------------------------------------------------------
// 0x5D28D0 sub_5D28D0
// ------------------------------------------------------------
char /*usercall*/ sub_5D28D0@<al>(int a1@<ecx>, int a2@<edi>)
{
  uint64_t v3; // rax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  unsigned int v8; // ecx
  unsigned int v9; // eax
  int v10; // edi
  int v11; // edi
  float v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  float v18; // [esp+4h] [ebp-8h]
  float v19; // [esp+8h] [ebp-4h]

  sub_5D2470(a1);
  LOBYTE(v3) = *(uint8_t *)(a1 + 7801);
  if ( (uint8_t)v3 == 0 )
    *(uint32_t *)(a1 + 8752) = 1065353216;
  if ( *(uint32_t *)(a1 + 8700) == -1 )
  {
    v18 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 736))(a1);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 740))(a1);
    v5 = *(uint32_t *)(a1 + 8840);
    v19 = v18 / (double)v4;
    if ( v19 < (double)*(float *)(a1 + 4 * v5 + 8884)
      && v5 == *(uint32_t *)(a1 + 8844)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) == 1
      && *(uint8_t *)(a1 + 7801) == 1
      && *(int *)(a1 + 8840) < 3
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1) != 5 )
    {
      v6 = *(uint32_t *)(a1 + 8840);
      ++*(uint32_t *)(a1 + 8844);
      sub_5D0CC0((float *)a1, *(uint32_t *)(a1 + 4 * v6 + 8900));
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)a1 + 560))(a1, 32, 0, 2, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 564))(a1);
    }
    *(uint8_t *)(*(uint32_t *)(a1 + 7620) + 64) = (double)*(int *)(a1 + 8924) >= v19;
    LODWORD(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1);
    if ( (uint32_t)v3 == 8 )
    {
      LODWORD(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 908))(a1);
      if ( (uint32_t)v3 == 2 )
      {
        if ( sub_699000(a1 + 8852) <= *(uint32_t *)(a1 + 8880) )
        {
          LOBYTE(v3) = (uint8_t)dword_8F8528;
          *((uint32_t *)dword_8F8528 + 623) = 0;
        }
        else
        {
          v7 = sub_699000(a1 + 8852);
          v8 = *(uint32_t *)(a1 + 8920);
          v9 = v7 - *(uint32_t *)(a1 + 8880);
          if ( v9 >= v8 )
            LOBYTE(v3) = 0;
          else
            v3 = (uint64_t)(sin((double)(v8 + v9) * 6.2831841 / (double)(int)(4 * v8)) * 250.0);
          *((uint32_t *)dword_8F8528 + 623) = (uint8_t)v3;
          LOBYTE(v3) = *(uint8_t *)(a1 + 8848);
          if ( (uint8_t)v3 == 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 608))(dword_8F7C04, a2) == 1 )
            {
              if ( (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) >= v10)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 1
                || (v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) < v11)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 0 )
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 764))(
                  dword_8F7C04,
                  3,
                  *(uint32_t *)(a1 + 8928),
                  a1,
                  0);
              }
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 764))(
              dword_8F7C04,
              6,
              *(uint32_t *)(a1 + 8928),
              a1);
            v12 = *(float *)a1;
            v13 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04
                                                                                                 + 124))(
                    dword_8F7C04,
                    30311,
                    0,
                    0,
                    4,
                    100,
                    2,
                    0,
                    0);
            v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, v13);
            v15 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 124))(dword_8F7C04, 0, v14);
            v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, v15);
            (*(void (/*thiscall*/ **)(int, int))(LODWORD(v12) + 584))(a1, v16);
            LOBYTE(v3) = sub_424120(*(uint32_t **)(*(uint32_t *)(a1 + 116) + 132), 3, *(uint32_t *)(a1 + 8920));
            *(uint8_t *)(a1 + 8848) = 1;
          }
        }
      }
    }
  }
  return v3;
}


// 冰守卫：R_ICE_GUARD 语音（91L；RTTI cast + this+8853/8854/8868/8872 相位；
//   8212 字段亦现 —— 守卫/邪眼共享字段区）
// ------------------------------------------------------------
// 0x5D2BB0 sub_5D2BB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2BB0(int this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  const char *v10; // eax
  uint32_t *v11; // [esp-Ch] [ebp-A0h]
  int v12; // [esp+4h] [ebp-90h] BYREF
  int v13; // [esp+8h] [ebp-8Ch]
  int v14; // [esp+Ch] [ebp-88h] BYREF
  char Buffer[128]; // [esp+10h] [ebp-84h] BYREF
  int v16; // [esp+90h] [ebp-4h]

  v16 = dword_796E50;
  v13 = -1;
  result = sub_4DC630();
  if ( result != -1 )
  {
    if ( result == 15 )
    {
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v12);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v14);
      v3 = sub_45EBE0(v12, v14);
      if ( __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )
      {
        v4 = 16;
        while ( 1 )
        {
          v5 = *(uint32_t **)(v4 + dword_8F850C);
          if ( v5 != nullptr )
          {
            v6 = v5[49];
            if ( v6 != 0 )
            {
              v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 48))(v6);
              if ( v7 == v12 )
              {
                v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v5[49] + 52))(v5[49]);
                if ( v8 == v14 )
                  break;
              }
            }
          }
          v4 += 4;
          if ( v4 >= 32 )
            goto LABEL_18;
        }
        if ( *(uint8_t *)(this + 8868) == 0 )
        {
          if ( v5[10] < 0x10u )
            v9 = v5 + 5;
          else
            v9 = (uint32_t *)v5[5];
          v11 = v9;
          v10 = (const char *)sub_41ACF0(*(uint32_t *)(this + 8212) + 4);
          sprintf(Buffer, v10, v11);
          sub_4D9F00(Buffer);
        }
        sub_4D84F0(0, 0);
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v5[49] + 212))(
          v5[49],
          "R_ICE_GUARD",
          -1,
          0,
          0);
      }
LABEL_18:
      *(uint8_t *)(this + 8868) = 0;
      *(uint8_t *)(this + 8853) = 0;
      *(uint8_t *)(this + 8854) = 0;
      sub_698F90(this + 8840, *(uint32_t *)(this + 8872), 0);
      return v13;
    }
    else
    {
      v13 = result;
    }
  }
  return result;
}



// RTTI cast 大型 AI（168L；this+8840 相位）
// ------------------------------------------------------------
// 0x5D2D50 sub_5D2D50
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2D50(uint32_t *this, int a2, int a3, int a4)
{
  int v4; // ebx
  int v6; // eax
  int v7; // esi
  void *v8; // eax
  double v9; // st7
  double v10; // st7
  float v11; // eax
  float v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  int v26; // ecx
  void *v27; // eax
  int *v28; // eax
  int v29; // edx
  int v31; // [esp-1Ch] [ebp-58h]
  int v32; // [esp-18h] [ebp-54h]
  int v33; // [esp-Ch] [ebp-48h]
  int v34; // [esp-8h] [ebp-44h]
  float v35; // [esp+8h] [ebp-34h] BYREF
  float v36; // [esp+Ch] [ebp-30h]
  float v37; // [esp+10h] [ebp-2Ch]
  int v38; // [esp+14h] [ebp-28h]
  int v39; // [esp+18h] [ebp-24h]
  int v40; // [esp+1Ch] [ebp-20h]
  uint8_t v41[4]; // [esp+20h] [ebp-1Ch] BYREF
  void *Block; // [esp+24h] [ebp-18h]
  int v43; // [esp+28h] [ebp-14h] BYREF
  char v44; // [esp+2Fh] [ebp-Dh] BYREF
  int v45; // [esp+38h] [ebp-4h]

  v4 = a2;
  if ( a2 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v7 = v6;
    if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 17) != 0 )
    {
      if ( *((uint8_t *)this + 8840) == 2 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )
      {
        v8 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, int, uint32_t))(*this + 628))(
                       this,
                       &v44,
                       v41,
                       100,
                       a2,
                       a3,
                       0);
        v9 = (double)(int)*(this + 2231);
        Block = v8;
        v10 = v9 * 0.0099999998 * (double)(int)v8;
        if ( v10 < 1.0 )
          v10 = 1.0;
        v11 = *(float *)(a3 + 4);
        v35 = *(float *)a3;
        v12 = *(float *)(a3 + 8);
        v36 = v11;
        v13 = *(uint32_t *)(a3 + 12);
        v37 = v12;
        v14 = *(uint32_t *)(a3 + 16);
        v38 = v13;
        v15 = *(uint32_t *)(a3 + 20);
        v43 = 0;
        v39 = v14;
        v40 = v15;
        Block = (void *)(rand() % 60 - 30);
        v35 = (double)(int)Block + v35;
        Block = (void *)(rand() % 60 - 30);
        v36 = (double)(int)Block + v36;
        Block = (void *)(rand() % 60 - 30);
        v37 = (double)(int)Block + v37;
        v34 = sub_605840(&v43, v7, &v35, 0);
        v33 = v43;
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 128))(v7);
        v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
        sub_4E4A50((int)this, (int)this, 42004, (uint64_t)v10, v16, v31, v32, 1, 0, v33, v34);
        v4 = a2;
      }
      if ( *(this + 2175) == -1 )
      {
        v17 = 0;
        Block = nullptr;
        while ( 1 )
        {
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
          v19 = *(uint32_t *)(v18 + 4);
          v20 = v19 != 0 ? (*(uint32_t *)(v18 + 8) - v19) >> 2 : 0;
          if ( (int)v17 >= v20 )
            break;
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
          v22 = *(uint32_t *)(v21 + 4);
          if ( v22 != 0 && v17 < (*(uint32_t *)(v21 + 8) - v22) >> 2 )
            v23 = *(uint32_t *)(v22 + 4 * v17);
          else
            v23 = 0;
          if ( *(uint32_t *)(v23 + 4) == v7 )
          {
            v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
            v25 = *(uint32_t *)(v24 + 4);
            if ( v25 != 0 && v17 < (*(uint32_t *)(v24 + 8) - v25) >> 2 )
              v26 = *(uint32_t *)(v25 + 4 * v17);
            else
              v26 = 0;
            v27 = (void *)__RTDynamicCast(
                            v26,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNFireBomb `RTTI Type Descriptor',
                            0);
            Block = v27;
            if ( v27 != nullptr )
            {
              if ( (uint8_t)sub_64D310(v27) == 1
                && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 308))(v7) == 1 )
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 31, 0, 2, 0);
                (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
              }
              break;
            }
          }
          ++v17;
        }
        if ( Block == nullptr )
        {
          Block = operator new(0x1C0u);
          v45 = 0;
          if ( Block != nullptr )
            v28 = (int *)sub_64D6A0(*(this + 2232), *(this + 2233), *(this + 2234));
          else
            v28 = nullptr;
          v29 = *v28;
          v45 = -1;
          (*(void (/*thiscall*/ **)(int *, int, uint32_t *, uint32_t, uint32_t, int, int))(v29 + 56))(
            v28,
            v7,
            this,
            0,
            0,
            39,
            -1);
        }
        v4 = a2;
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)a4 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 1336))(this, v4, a3, 0);
  return sub_5CEFF0(v4, a3, a4);
}


// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3060 sub_5D3060
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3060(int *this)
{
  int result; // eax
  unsigned int i; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = *(this + 29);
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *(this + 29);
      v5 = *(uint32_t *)(v4 + 8);
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
      {
        v8 = *(this + 29);
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v11 != 0 )
        {
          v12 = __RTDynamicCast(v11, 0, &IRDMonster `RTTI Type Descriptor', &CNSoldier `RTTI Type Descriptor', 0);
          if ( v12 != 0 && (int *)v12 != this )
            sub_5CF0F0(v12);
        }
      }
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3130 sub_5D3130
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3130(uint32_t *this)
{
  unsigned int i; // esi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(
              v10,
              0,
              &CNRDObject `RTTI Type Descriptor',
              &CNTinSwordManExpeller `RTTI Type Descriptor',
              0);
      if ( v11 != 0 )
        *(uint8_t *)(v11 + 8848) = 0;
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D31D0 sub_5D31D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D31D0(uint32_t *this)
{
  unsigned int v1; // edi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v1 = 0;
  v15 = 99999;
  v14 = 0;
  while ( 1 )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v1);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v1);
      else
        v10 = 0;
      v11 = __RTDynamicCast(
              v10,
              0,
              &CNRDObject `RTTI Type Descriptor',
              &CNTinSwordManExpeller `RTTI Type Descriptor',
              0);
      v12 = v11;
      if ( v11 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11) < v15 )
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
        v14 = v12;
      }
    }
    ++v1;
  }
  return v14;
}



// 军团呐喊：LEGION_SHOUT 播报（72L）
// ------------------------------------------------------------
// 0x5D32A0 sub_5D32A0
// ------------------------------------------------------------
uint32_t */*userpurge*/ sub_5D32A0@<eax>(int a1@<ecx>, int a2@<ebx>, int ArgList, float a4, int a5, int a6)
{
  uint32_t *result; // eax
  char v8; // di
  int *v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // edi

  result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1);
  v8 = ArgList;
  if ( result != (uint32_t *)20 || ArgList != 20 )
  {
    if ( ArgList == 8 )
    {
      result = *(uint32_t **)(LODWORD(a4) + 4);
      if ( *result == 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
                             a1,
                             "LEGION_SHOUT",
                             -1,
                             0,
                             0);
    }
    else if ( ArgList == 20 )
    {
      if ( *(uint8_t *)(a1 + 8669) != 1 )
        return result;
      v9 = (int *)(*(uint32_t *)(a1 + 6216) + 20);
      *(uint8_t *)(a1 + 8832) = 1;
      sub_4926A0(*v9);
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)a1 + 196))(a1, *(uint32_t *)(*(uint32_t *)(a1 + 6216) + 20), a2);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 344))(a1, *(uint32_t *)(a1 + 556));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 876))(
        a1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 876))(
        a1,
        1,
        0,
        0,
        0,
        0,
        0);
      *(uint8_t *)(a1 + 8812) = 1;
      *(uint32_t *)(a1 + 8816) = 4;
      v10 = sub_45EBE0(**(uint32_t **)(LODWORD(a4) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(a4) + 4) + 4));
      v11 = v10;
      if ( v10 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 17) != 0 )
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11);
        *(uint32_t *)(a1 + 8816) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) < v12;
      }
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 144))(a1, *(uint32_t *)(a1 + 8816));
      v8 = 20;
    }
    if ( *(uint8_t *)(a1 + 8669) == 1 )
      return (uint32_t *)sub_4E33D0(v8, a4, a5, a6);
  }
  return result;
}



// ============================================================
// 【分区 4】守卫核心 AI 与霸体（0x5D3400-0x5D5C30）
// 证据：AMOR_HIT 阿莫尔命中三连（0x5D4340/0x5D4420/0x5D4480）、SUPERARMOR 霸体播报
//       （0x5D47D0 —— 研究 20 §1.2 vt+720 霸体 setter 的调用侧）、REPAIR_OBJECT

// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3400 sub_5D3400
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3400(uint32_t *this)
{
  unsigned int v1; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v11; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  v1 = 0;
  v11 = 0;
  v12 = 99999;
  while ( 1 )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 120);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 124) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 120);
    if ( v6 != 0 && v1 < (*(uint32_t *)(v3 + 124) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v1);
    else
      v7 = 0;
    v8 = __RTDynamicCast(v7, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);
    v9 = v8;
    if ( (uint32_t *)v8 != this
      && v8 != 0
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 340))(v8) == 704
      && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v9, 0) < v12 )
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v9, 0);
      v11 = v9;
    }
    ++v1;
  }
  return v11;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D34C0 sub_5D34C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D34C0(uint32_t *this, int a2, int a3)
{
  unsigned int i; // esi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // eax

  for ( i = 0; ; ++i )
  {
    v5 = *(this + 29);
    v6 = *(uint32_t *)(v5 + 8);
    v7 = v6 != 0 ? (*(uint32_t *)(v5 + 12) - v6) >> 2 : 0;
    if ( (int)i >= v7 )
      break;
    v8 = *(uint32_t *)(v5 + 8);
    if ( v8 != 0 && i < (*(uint32_t *)(v5 + 12) - v8) >> 2 )
      v9 = *(uint32_t *)(v8 + 4 * i);
    else
      v9 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 529) != 0 )
    {
      v10 = *(this + 29);
      v11 = *(uint32_t *)(v10 + 8);
      if ( v11 != 0 && i < (*(uint32_t *)(v10 + 12) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      v13 = __RTDynamicCast(v12, 0, &CNRDObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);
      if ( v13 != 0 && *(uint32_t *)(v13 + 8820) == a2 && *(uint32_t *)(v13 + 8824) == a3 )
        return 0;
    }
  }
  return 1;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3590 sub_5D3590
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3590(uint32_t *this)
{
  int v1; // ebx
  unsigned int i; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // eax

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    v4 = *(this + 29);
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
    if ( (int)i >= v6 )
      break;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
      v8 = *(uint32_t *)(v7 + 4 * i);
    else
      v8 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 529) != 0 )
    {
      v9 = *(this + 29);
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      v12 = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) == 704 )
        ++v1;
    }
  }
  return v1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D3640 sub_5D3640
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3640(int *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);
  if ( result > 0 )
  {
    if ( result > 5 )
    {
      if ( result > 10 )
      {
        if ( result > 15 )
        {
          if ( result > 20 )
            return result;
          goto LABEL_6;
        }
LABEL_5:
        *(uint8_t *)(*(this + 1905) + 128) = 0;
LABEL_6:
        result = *(this + 1905);
        *(uint8_t *)(result + 160) = 0;
        return result;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 1905) + 32) = 0;
    }
    *(uint8_t *)(*(this + 1905) + 64) = 0;
    *(uint8_t *)(*(this + 1905) + 96) = 0;
    goto LABEL_5;
  }
  return result;
}



// AI 相位字段（this+8602..8604）
// ------------------------------------------------------------
// 0x5D36C0 sub_5D36C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D36C0(uint8_t *this, int a2)
{
  char v3; // cl
  char v4; // al
  char v5; // al
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint8_t v11[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-4h]

  v3 = 0;
  if ( a2 == 0 )
    goto LABEL_8;
  if ( a2 == 1 )
  {
LABEL_6:
    if ( *(this + 8603) != 0 )
      goto LABEL_10;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 16);
    v5 = *(this + 8602);
    *(this + 8603) = 1;
    v3 = 1;
    if ( v5 != 0 )
      goto LABEL_11;
LABEL_8:
    if ( *(this + 8602) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 788))(this, 0);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 1);
      *(this + 8602) = 1;
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 2166) + 12))(*((uint32_t *)this + 2166), 0);
      v6 = **((uint32_t **)this + 2166);
      v7 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v7 + 65);
      v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*((uint32_t *)this + 2166), v9);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + 2166) + 92))(*((uint32_t *)this + 2166), v11);
      v10 = *((void **)this + 29);
      v13 = 0;
      sub_4600B0(v10, 2, 0, (int)v11);
      if ( Block != nullptr )
        j__free(Block);
      return;
    }
LABEL_10:
    if ( v3 != 1 )
      return;
    goto LABEL_11;
  }
  if ( a2 == 2 && *(this + 8604) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 13);
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1324))(this);
    v4 = *(this + 8603);
    *(this + 8604) = 1;
    v3 = 1;
    if ( v4 != 0 )
      goto LABEL_11;
    goto LABEL_6;
  }
}



// 主状态门（this+200/8604/8660, 105L）
// ------------------------------------------------------------
// 0x5D3810 sub_5D3810
// ------------------------------------------------------------
void /*thiscall*/ sub_5D3810(uint8_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // edi
  uint32_t *v13; // edi
  void *v14; // ecx
  void *v15; // eax
  int v16; // [esp-Ch] [ebp-34h]
  char v17[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  uint32_t *v19; // [esp+14h] [ebp-14h]
  bool v20; // [esp+1Bh] [ebp-Dh]
  int v21; // [esp+24h] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148);
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      if ( sub_41A5E0((unsigned int)(this + 7028)) != 0 )
      {
        if ( sub_41A5E0((unsigned int)(this + 7028)) == 1 )
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(
            this,
            0,
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),
            0,
            -3000,
            1);
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(
          this,
          0,
          **((uint32_t **)this + 2153),
          **((uint32_t **)this + 2153),
          0,
          -2000,
          1);
      }
      if ( *(this + 8604) == 0 )
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);
        v3 = *(uint32_t *)this;
        v4 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, 4);
        (*(void (/*thiscall*/ **)(uint8_t *, int))(v3 + 896))(this, v4);
      }
      if ( *(this + 8660) == 1 )
      {
        v5 = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 924))(this, 2)];
        v6 = *(uint32_t *)this;
        v19 = v5;
        v7 = (*(int (/*thiscall*/ **)(uint8_t *))(v6 + 152))(this);
        v8 = *(uint32_t *)this;
        v9 = *v5;
        v20 = v7 == 0;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *))(v8 + 128))(this);
        v11 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v10);
        v12 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, v11 + 1) != 0 ? -20 : 20;
        v16 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) + v12;
        v13 = v19;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(v19, v16);
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 28))(v19) + 84) = v20;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v13 + 12))(v13, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v13 + 92))(v13, v17);
        v14 = *((void **)this + 29);
        v21 = 0;
        sub_4600B0(v14, 2, 0, (int)v17);
        v15 = Block;
        *(this + 8660) = 0;
        if ( v15 != nullptr )
          j__free(v15);
      }
    }
  }
  else
  {
    *(this + 8660) = 1;
  }
}



// 时钟门 AI（sub_699000; this+8840/8841 相位, 130L）
// ------------------------------------------------------------
// 0x5D39D0 sub_5D39D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5D39D0(int *this)
{
  unsigned int result; // eax
  int v3; // edx
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // edx
  void *v10; // eax
  double v12; // st7
  uint8_t v13; // c0
  uint8_t v14; // c3
  double v15; // st7
  float v16; // ebx
  uint32_t *v17; // edi
  int v18; // edi
  int v19; // ebx
  int v20; // [esp-14h] [ebp-38h]
  int v21; // [esp-10h] [ebp-34h]
  float v22; // [esp-Ch] [ebp-30h]
  char v23[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v25; // [esp+Ch] [ebp-18h]
  int v26; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int v28; // [esp+20h] [ebp-4h]

  result = sub_5D2470();
  if ( *(this + 2175) != -1 )
    return result;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 68))(*(this + 2214)) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2214) + 12))(*(this + 2214), 0);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0 )
  {
    v3 = *(this + 2226) * *((uint8_t *)this + 8840) / 100 + 1;
    v4 = v3 * *(this + 2218);
    v5 = v3 * *(this + 2219);
    v6 = rand();
    v7 = *this;
    i = v6 % v4 - v4 / 2;
    i += (*(int (/*thiscall*/ **)(int *))(v7 + 120))(this);
    v8 = rand() % v5 - v5 / 2;
    v21 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + v8;
    v20 = i;
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 40))(*(this + 2214));
    (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 2214) + 92))(*(this + 2214), v23);
    v9 = *this;
    v28 = 0;
    v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v9 + 80))(this, 2, 0, v23);
    sub_4600B0(v10, v20, v21, 0);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v25 = 0;
    v26 = 0;
  }
  if ( *((float *)this + 2216) != *((float *)this + 2215) )
  {
    i = *(this + 2216);
    v12 = *((float *)this + 2216);
    if ( (v13 | v14) != 0 )
    {
      v15 = v12 - 0.02;
      if ( v15 >= *((float *)this + 2215) )
        goto LABEL_14;
    }
    else
    {
      v15 = v12 + 0.02;
      if ( v15 <= *((float *)this + 2215) )
        goto LABEL_14;
    }
    v15 = *((float *)this + 2215);
LABEL_14:
    v16 = *(float *)&i;
    *((float *)this + 2216) = v15;
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);
    sub_4EB4B0(v16);
    v22 = *((float *)this + 2216);
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);
    sub_4EB2C0(v22);
    v17 = this + 1617;
    for ( i = 18; i != 0; --i )
    {
      if ( *v17 != 0 )
      {
        sub_4EB6E0(v16);
        sub_4EB6A0(*((float *)this + 2216));
      }
      ++v17;
    }
  }
  v18 = *(this + 2217);
  result = sub_699000((int)(this + 9));
  if ( v18 + *(this + 2220) < result || v18 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      v19 = 22;
      if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) )
      {
        if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) && *((uint8_t *)this + 8840) != 0 )
          v19 = 23;
      }
      else if ( *((uint8_t *)this + 8840) != 2 )
      {
        v19 = 21;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, v19, 0, 2, 0);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 564))(this);
      *(this + 2217) = -1;
    }
    else
    {
      result = sub_699000((int)(this + 9));
      *(this + 2217) = result;
    }
  }
  return result;
}


// 时钟门 AI（this+8601/8603/8669/8812..8837, 73L）
// ------------------------------------------------------------
// 0x5D3CB0 sub_5D3CB0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D3CB0(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 1 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
    }
    else if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )
    {
      if ( sub_41A5E0(this + 7028) == 3 )
        sub_5D0330((int *)this, 1, this + 7028);
      sub_4D9360(this);
    }
  }
  if ( *(uint8_t *)(this + 8812) == 1
    && sub_41A5E0(this + 7028) == 1
    && *(int *)(this + 8824) < 3
    && *(uint32_t *)(this + 8816) + *(uint32_t *)(this + 8820) < (unsigned int)sub_699000(this + 36) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
    *(uint32_t *)(this + 8816) = sub_699000(this + 36);
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 8 )
    sub_4D93D0(this);
  LOBYTE(v2) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(v2) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)v2 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
    if ( *(uint8_t *)(this + 8669) == 1 )
    {
      LOBYTE(v2) = *(uint8_t *)(this + 8837);
      if ( (uint8_t)v2 == 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
        v3 = *(uint32_t *)dword_8F8520;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
        v5 = *(uint32_t *)dword_8F8520;
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        LOBYTE(v2) = sub_5D3060((int *)this);
        *(uint8_t *)(this + 8837) = 1;
      }
    }
  }
  return v2;
}



// AI 字段访问（this+8837）
// ------------------------------------------------------------
// 0x5D3E70 sub_5D3E70
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3E70(int this)
{
  int result; // eax
  int v3; // edi

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 && *(uint8_t *)(this + 8837) == 0 )
    {
      sub_5D3060((int *)this);
      *(uint8_t *)(this + 8837) = 1;
    }
    return v3;
  }
  return result;
}



// AI 相位字段（this+8603/8664）
// ------------------------------------------------------------
// 0x5D3EB0 sub_5D3EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3EB0(int this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  void *v9; // ecx
  uint8_t v11[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v13; // [esp+Ch] [ebp-14h]
  int v14; // [esp+10h] [ebp-10h]
  int v15; // [esp+1Ch] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
  {
    if ( (uint8_t)a4 != 0 )
      return sub_5CEFF0((uint8_t *)this, a2, a3, a4);
    if ( *(uint8_t *)(this + 8603) == 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, a2, a3, 0);
  }
  else if ( (uint8_t)a4 != 0 )
  {
    return sub_5CEFF0((uint8_t *)this, a2, a3, a4);
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8664) + 12))(*(uint32_t *)(this + 8664), 0);
  v5 = **(uint32_t **)(this + 8664);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v6 + 65);
  v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v7);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v5 + 40))(*(uint32_t *)(this + 8664), v8);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 8664) + 92))(*(uint32_t *)(this + 8664), v11);
  v9 = *(void **)(this + 116);
  v15 = 0;
  sub_4600B0(v9, 2, 0, (int)v11);
  v15 = -1;
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v13 = 0;
  v14 = 0;
  return sub_5CEFF0((uint8_t *)this, a2, a3, a4);
}



// 时钟门+RTTI AI（122L）
// ------------------------------------------------------------
// 0x5D3FD0 sub_5D3FD0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D3FD0(int *this)
{
  int v2; // esi
  int v3; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int v12; // edi
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // esi
  int v22; // edx
  int v23; // [esp+Ch] [ebp-10h]
  int v24; // [esp+10h] [ebp-Ch]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]

  v2 = (int)(this + 2205);
  v3 = *(this + 2211);
  if ( sub_699000((int)(this + 2205)) < v3 )
    return 0;
  sub_5D3130(this);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 10000, 0);
  v5 = sub_5D31D0(this);
  v6 = v5;
  v24 = v5;
  if ( v5 != 0 && (int *)v5 == this )
  {
    v7 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
    v8 = *(uint32_t *)(v7 + 364);
    v9 = v7 + 360;
    v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 5 : 0;
    v11 = 224 * v10;
    v23 = 224 * v10;
    v25 = 48 * ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6) / 48);
    if ( v25 < v11 )
    {
LABEL_9:
      v26 = 0;
      while ( 1 )
      {
        v12 = 0;
        while ( 1 )
        {
          v13 = *(this + 29);
          v14 = *(uint32_t *)(v13 + 8);
          v15 = v14 != 0 ? (*(uint32_t *)(v13 + 12) - v14) >> 2 : 0;
          if ( (int)v12 >= v15 )
            break;
          v16 = *(uint32_t *)(v13 + 8);
          if ( v16 != 0 && v12 < (*(uint32_t *)(v13 + 12) - v16) >> 2 )
            v17 = *(uint32_t *)(v16 + 4 * v12);
          else
            v17 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 40))(v17, 529) == 0 )
            goto LABEL_31;
          v18 = *(this + 29);
          v19 = *(uint32_t *)(v18 + 8);
          if ( v19 != 0 && v12 < (*(uint32_t *)(v18 + 12) - v19) >> 2 )
            v20 = *(uint32_t *)(v19 + 4 * v12);
          else
            v20 = 0;
          v21 = __RTDynamicCast(
                  v20,
                  0,
                  &CNRDObject `RTTI Type Descriptor',
                  &CNTinSwordManExpeller `RTTI Type Descriptor',
                  0);
          if ( v24 == v21 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
            ++v12;
          }
          else
          {
            if ( v21 != 0
              && *(uint8_t *)(v21 + 8848) == 0
              && *(uint32_t *)(v21 + 8812) != v25
              && *(uint32_t *)(v21 + 8816) != v26
              && (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v25, v26, 0) != 0 )
            {
              v22 = *(uint32_t *)v21;
              *(uint32_t *)(v21 + 8816) = v26;
              *(uint32_t *)(v21 + 8812) = v25;
              *(uint8_t *)(v21 + 8848) = 1;
              (*(void (/*thiscall*/ **)(int, int, int))(v22 + 1144))(v21, v25, v26);
              break;
            }
LABEL_31:
            ++v12;
          }
        }
        v26 += 48;
        if ( v26 >= 480 )
        {
          v25 += 48;
          if ( v25 >= v23 )
            return 1;
          goto LABEL_9;
        }
      }
    }
  }
  return 1;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D41E0 sub_5D41E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D41E0(uint32_t *this, int *a2, int *a3)
{
  int v4; // esi
  int i; // ebx
  int v6; // eax
  int v8; // [esp+Ch] [ebp-40h]
  uint32_t v9[15]; // [esp+10h] [ebp-3Ch]

  v4 = sub_5D3400(this);
  v8 = 0;
  v9[0] = -48;
  v9[1] = 0;
  v9[2] = 48;
  v9[3] = 48;
  v9[4] = 0;
  v9[5] = -48;
  v9[6] = 0;
  v9[7] = 48;
  v9[8] = -48;
  v9[9] = -48;
  v9[10] = 48;
  v9[11] = -48;
  v9[12] = -48;
  v9[13] = 48;
  v9[14] = 48;
  for ( i = 0; i < 8; ++i )
  {
    if ( v4 != 0 )
    {
      *a2 = v9[2 * i - 1] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 120))(v4);
      v6 = v9[2 * i] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
      *a3 = v6;
      if ( sub_5D34C0(this, *a2, v6) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 136))(this, *a2, *a3, 0) != 0 )
      {
        break;
      }
    }
  }
  return v4;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D42A0 sub_5D42A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D42A0(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edx
  int v5; // [esp+4h] [ebp-8h] BYREF
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = sub_5D3590(this);
  if ( *(this + 1813) == 0 && result > 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v4 = *this;
    v5 = v3;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 124))(this);
    result = sub_5D41E0(this, &v5, &v6);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, result, 0);
      if ( result > 100 || result < 64 )
      {
        if ( *(this + 1787) != 25 )
          return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1144))(this, v5, v6);
      }
      else if ( *(this + 1787) == 25 )
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
      }
    }
  }
  return result;
}



// 阿莫尔命中 1：AMOR_HIT + Particle/ExpellerBrokenParts.ptl（24L；受击掉碎屑）
// ------------------------------------------------------------
// 0x5D4340 sub_5D4340
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4340(uint8_t *this)
{
  *(this + 8600) = 0;
  sub_4015C0("AMOR_HIT", 8u);
  *((uint32_t *)this + 2176) = -1;
  *((uint32_t *)this + 2177) = -1;
  *((uint32_t *)this + 2178) = -1;
  if ( *((uint32_t *)this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *, const char *))(*(uint32_t *)this + 1352))(
             this,
             this + 364,
             "Particle/ExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, const char *))(*(uint32_t *)this + 1352))(
             this,
             *((uint32_t *)this + 91),
             "Particle/ExpellerBrokenParts.ptl");
}



// AI 相位字段（this+8601/8603/8669）
// ------------------------------------------------------------
// 0x5D43B0 sub_5D43B0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D43B0(int this)
{
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  if ( *(uint8_t *)(this + 8669) == 1 )
    sub_5D3FD0((int *)this);
  LOBYTE(v2) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(v2) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)v2 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
  }
  return v2;
}



// 阿莫尔命中 2：AMOR_HIT 播报（this+8600/8820/8833/8834/8848 相位）
// ------------------------------------------------------------
// 0x5D4420 sub_5D4420
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4420(uint8_t *this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2204) = v3;
  *((uint32_t *)this + 2203) = v3;
  *(this + 8833) = 0;
  *(this + 8834) = 0;
  sub_698F90((int)(this + 8820), 10000, 0);
  *(this + 8848) = 0;
  *((uint32_t *)this + 2213) = 0;
  return sub_4015C0("AMOR_HIT", 8u);
}



// 阿莫尔命中 3：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D4480 sub_5D4480
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4480(uint8_t *this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8601) = 0;
  *(this + 8812) = 0;
  *(this + 8600) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2206) = v3;
  *((uint32_t *)this + 2205) = v3;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;
  return sub_4015C0("AMOR_HIT", 8u);
}



// 复合门（this+200/568/8669/8812/8832 —— this+568 最后受击时刻, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5D44D0 sub_5D44D0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D44D0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // edi
  bool v5; // bl
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  int v12; // [esp-8h] [ebp-30h]
  void *v13[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v14; // [esp+24h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v2 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);
    else
      sub_41A5E0((unsigned int)(this + 1757));
  }
  else if ( v2 == 20 )
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) <= 1 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        if ( *((uint8_t *)this + 8812) == 1 )
        {
          v3 = *this;
          v12 = *(this + 2204);
          *((uint8_t *)this + 8812) = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v3 + 896))(this, v12, 4);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(
            this,
            0,
            1400,
            1400,
            0,
            -2000,
            1);
        }
        v4 = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 2)];
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 28))(v4) + 84) = v5;
        v6 = *(uint32_t *)v4;
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(v4, v9);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 12))(v4, 0);
        (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v4 + 92))(v4, v13);
        v10 = (void *)*(this + 29);
        v14 = 0;
        sub_4600B0(v10, 2, 0, (int)v13);
        v14 = -1;
        sub_5E5260(v13);
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  if ( *((uint8_t *)this + 8669) == 1 )
    sub_5D42A0(this);
  if ( *((uint8_t *)this + 8832) != 0 )
  {
    sub_4D83E0(0, 0);
    *((uint8_t *)this + 8832) = 0;
  }
  return sub_5CF180(this);
}



// 语音注册（sub_4015C0; 容器越界串为 STL 断言文本, 非游戏资源）
// ------------------------------------------------------------
// 0x5D46D0 sub_5D46D0
// ------------------------------------------------------------
void /*noreturn*/ sub_5D46D0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// 语音注册（sub_4015C0）
// ------------------------------------------------------------
// 0x5D4740 sub_5D4740
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4740(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 357913941 - v2 < a2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);
    v8 = 0;
    sub_401740(v5);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
  *(this + 2) = result;
  return result;
}



// ★ 霸体：SUPERARMOR 播报（32L；sub_699000 时钟门 —— 研究 20 §1.2 vt+720 霸体 setter
//   的怪物侧调用场景, 霸体开启演出）
// ------------------------------------------------------------
// 0x5D47D0 sub_5D47D0
// ------------------------------------------------------------
int /*userpurge*/ sub_5D47D0@<eax>(int a1@<ecx>, int a2@<edi>, int ArgList, float a4, int a5, int a6)
{
  uint64_t v7; // rax
  uint32_t *v8; // edi
  int *v9; // edx
  float v11; // [esp+1Ch] [ebp+14h]

  if ( ArgList < 24 || ArgList > 25 )
    return sub_5D19C0((int **)a1, ArgList, a4, a5, a6);
  v11 = (float)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 736))(a1, a2);
  v7 = (uint64_t)((1.0 - v11 / (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 740))(a1))
                        * (double)*(int *)(a1 + 8864));
  v8 = *(uint32_t **)(LODWORD(a4) + 4);
  if ( v8 == nullptr || (*(uint32_t *)(LODWORD(a4) + 8) - (int)v8) >> 2 == 0 )
    sub_454B50();
  *(uint32_t *)(a1 + 8844) = *(uint32_t *)(a1 + 4 * *v8 + 8852) - v7;
  *(uint32_t *)(a1 + 8848) = sub_699000(a1 + 36);
  if ( *(uint32_t *)(a1 + 8700) == -1 )
  {
    sub_4DB200(24, (ArgList != 24) + 1);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(a1, "SUPERARMOR", -1, 0, 0);
  }
  v9 = *(int **)a1;
  *(uint32_t *)(a1 + 8840) = ArgList != 24;
  return ((int (/*thiscall*/ *)(int, uint32_t))v9[248])(a1, *(uint32_t *)(a1 + 8844));
}



// 大型 AI（183L；sub_699000 + this+8840..8998 守卫相位字段）
// ------------------------------------------------------------
// 0x5D48D0 sub_5D48D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D48D0(int *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // edi
  int v15; // ebx
  int v16; // edx
  int v17; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edx
  uint32_t *v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  int v26; // edi
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  void *v33; // ecx
  int v34; // eax
  char v35[4]; // [esp+4h] [ebp-38h] BYREF
  void *Block; // [esp+8h] [ebp-34h]
  uint32_t v37[3]; // [esp+14h] [ebp-28h] BYREF
  int v38; // [esp+20h] [ebp-1Ch]
  float v39; // [esp+24h] [ebp-18h]
  int v40; // [esp+28h] [ebp-14h]
  bool v41; // [esp+2Fh] [ebp-Dh]
  int v42; // [esp+38h] [ebp-4h]

  sub_5D2470();
  if ( *(this + 2175) == -1 )
  {
    v2 = *(this + 2217);
    if ( sub_699000((int)(this + 2211)) >= v2 && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1
        && *((uint8_t *)this + 8840) == 0
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 28, 0, 2, 0);
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
      }
      *((uint8_t *)this + 8840) = 0;
      *((uint8_t *)this + 8857) = 0;
      *((uint8_t *)this + 8858) = 0;
      sub_698F90((int)(this + 2211), *(this + 2253), 0);
    }
    v3 = *(this + 2243);
    v40 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
    v4 = *this;
    v39 = (float)v40;
    v40 = (*(int (/*thiscall*/ **)(int *))(v4 + 740))(this);
    if ( v39 / (double)v40 < *((float *)this + v3 + 2256)
      && v3 == *(this + 2244)
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      v5 = *(this + 2243);
      if ( v5 != 2 )
      {
        if ( v5 != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 27, 0, 2, 0);
          *(this + 2244) = 2;
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 26, 0, 2, 0);
          *(this + 2244) = 1;
        }
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
      }
    }
    if ( sub_699000((int)(this + 2236)) > 1000 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
      {
        v6 = *(uint32_t *)dword_8F8520;
        v40 = 100;
        (*(void (/*thiscall*/ **)(int, int, int))(v6 + 8))(dword_8F8520, 29, 2);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        v9 = *(uint32_t *)dword_8F8520;
        v10 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
        v11 = *(uint32_t *)dword_8F8520;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
        v13 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        v39 = COERCE_FLOAT(sub_425050(v13));
        v14 = 120 * (sub_424FF0(v13) + 3);
        do
        {
          v15 = rand() % SLODWORD(v39);
          v16 = rand() % v14;
          v17 = *this;
          v38 = v16;
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(v17 + 136))(this, v15, v16, 0) == 1 )
            break;
        }
        while ( v40-- != 0 );
        if ( v40 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 17);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v15);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v38);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      *((uint8_t *)this + 8957) = 0;
      *((uint8_t *)this + 8958) = 0;
    }
    v19 = *(this + 2235);
    if ( sub_699000((int)(this + 2229)) >= v19 )
    {
      if ( *(this + 2228) == *(this + 2254) )
        sub_5D2440(this + 2226);
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v21 = *this;
      v37[0] = v20;
      v37[1] = (*(int (/*thiscall*/ **)(int *))(v21 + 124))(this);
      v37[2] = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v22 = (uint32_t *)*(this + 2227);
      v23 = *v22;
      v38 = sub_5D1490(*v22, *(uint32_t *)(*v22 + 4), v37);
      sub_5D4740(1);
      v24 = v38;
      *(uint32_t *)(v23 + 4) = v38;
      **(uint32_t **)(v24 + 4) = v24;
      *((uint8_t *)this + 8929) = 0;
      *((uint8_t *)this + 8930) = 0;
      sub_698F90((int)(this + 2229), *(this + 2255), 0);
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1 )
    {
      v25 = *(this + 2252);
      if ( sub_699000((int)(this + 2246)) >= v25 )
      {
        v26 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
        v27 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        v28 = *(uint32_t *)v26;
        v41 = v27 == 0;
        v29 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v30 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v29);
        v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v30);
        (*(void (/*thiscall*/ **)(int, int))(v28 + 40))(v26, v31);
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v26 + 28))(v26);
        *(uint8_t *)(v32 + 84) = v41;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v26 + 12))(v26, 0);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v26 + 92))(v26, v35);
        v33 = (void *)*(this + 29);
        v42 = 0;
        sub_4600B0(v33, 2, 0, (int)v35);
        *((uint8_t *)this + 8997) = 0;
        *((uint8_t *)this + 8998) = 0;
        v34 = rand();
        sub_698F90((int)(this + 2246), *(this + 2261) + v34 % *(this + 2262), 0);
        if ( Block != nullptr )
          j__free(Block);
      }
    }
  }
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D4D00 sub_5D4D00
// ------------------------------------------------------------
char /*thiscall*/ sub_5D4D00(uint32_t *this)
{
  void *v2; // eax
  int v3; // eax
  int v4; // ecx

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
    {
      if ( *(this + 2204) == 0 )
      {
        v2 = operator new(0x64u);
        if ( v2 != nullptr )
          v3 = sub_51A7D0(v2);
        else
          v3 = 0;
        *(this + 2204) = v3;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 64))(v3) + 36) = 0;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2204) + 80))(*(this + 2204)) == 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2204) + 56))(
          *(this + 2204),
          this,
          this,
          0,
          0,
          0,
          -1);
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 2 )
  {
    v4 = *(this + 2204);
    if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2204) + 76))(*(this + 2204), 0);
  }
  return sub_5CF180(this);
}



// 斧驱逐者破碎 3：Particle/AxeExpellerBrokenParts.ptl（32L）
// ------------------------------------------------------------
// 0x5D4E30 sub_5D4E30
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4E30(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  v2 = operator new(0x7Cu);
  if ( v2 != nullptr )
    v3 = sub_4B3DF0(v2, 5, 1, -1035468800, 20000, 0);
  else
    v3 = nullptr;
  *(this + 2203) = v3;
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 64))(v3) + 36) = 0;
  if ( *(this + 96) < 0x10u )
    v4 = this + 91;
  else
    v4 = (uint32_t *)*(this + 91);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
           this,
           v4,
           "Particle/AxeExpellerBrokenParts.ptl");
}



// AI 相位辅助（126L）
// ------------------------------------------------------------
// 0x5D4EF0 sub_5D4EF0
// ------------------------------------------------------------
char /*usercall*/ sub_5D4EF0@<al>(uint8_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  uint8_t *v7; // edi
  int *v8; // eax
  int v9; // edi
  uint32_t *v10; // eax
  int v11; // edx
  int v12; // edi
  int v13; // ebx
  int *v14; // eax
  int v15; // edx
  int v16; // eax
  int v18; // [esp+8h] [ebp-38h]
  int v19; // [esp+Ch] [ebp-34h]
  int v21; // [esp+1Ch] [ebp-24h] BYREF
  char v22; // [esp+20h] [ebp-20h]
  float v23; // [esp+24h] [ebp-1Ch]
  void *Block; // [esp+28h] [ebp-18h]
  float v25; // [esp+2Ch] [ebp-14h]
  int v26; // [esp+30h] [ebp-10h]
  int v27; // [esp+3Ch] [ebp-4h]

  if ( *((uint32_t *)a1 + 2090) != 0 && a1[8820] == 0 && a1[8669] != 0 )
  {
    v4 = *(uint32_t *)a1;
    a1[8820] = 1;
    (*(void (**)(void))(v4 + 1360))();
  }
  v5 = *(uint32_t *)(*((uint32_t *)a1 + 30) + 148);
  if ( *((uint32_t *)a1 + 1639) == 8 )
  {
    switch ( sub_41A5E0((unsigned int)(a1 + 7028)) )
    {
      case 0:
      case 1:
        (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 1332))(a1);
        break;
      case 2:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1) != 0 && a1[8812] != 0 )
        {
          v6 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)a1 + 384))(a1, 11, a3);
          v26 = v6;
          a1[8812] = 0;
          v25 = (double)v6 * 0.0099999998;
          v7 = operator new(0x80u);
          Block = v7;
          v27 = 0;
          if ( v7 == nullptr )
            goto LABEL_18;
          v26 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 740))(a1);
          *(float *)&v18 = (double)v26 * v25;
          v8 = (int *)sub_4D6810(v7, v18, 500, 1, 1);
          goto LABEL_19;
        }
        break;
      case 3:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1) != 0 && a1[8812] != 0 )
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)a1 + 384))(a1, 2, a3));
          v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 384))(a1, 3);
          a1[8812] = 0;
          v10 = operator new(0x7Cu);
          Block = v10;
          v27 = 1;
          if ( v10 != nullptr )
          {
            *(float *)&v19 = (float)SLODWORD(v25);
            v8 = sub_4B3DF0(v10, 21, 1, v19, v9, 0);
          }
          else
          {
LABEL_18:
            v8 = nullptr;
          }
LABEL_19:
          v11 = *v8;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t))(v11 + 56))(v8, a1, a1, 0, 0, 0);
        }
        break;
      case 5:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1) != 0 && a1[8812] != 0 )
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)a1 + 384))(a1, 6, a2, a3));
          v12 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 384))(a1, 7);
          v13 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 384))(a1, 8);
          v23 = (float)SLODWORD(v25);
          a1[8812] = 0;
          v21 = 5;
          v22 = 1;
          Block = operator new(0x1D0u);
          v27 = 2;
          if ( Block != nullptr )
            v14 = (int *)sub_64B6C0(v12, &v21, 1, v13, 1, 0);
          else
            v14 = nullptr;
          v15 = *v14;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t))(v15 + 56))(v14, a1, a1, 0, 0);
        }
        break;
      default:
        break;
    }
  }
  LOBYTE(v16) = sub_5CF180(a1);
  if ( a1[8669] == 1 )
  {
    LOBYTE(v16) = a1[8603];
    if ( (uint8_t)v16 == 0 && a1[8601] == 1 )
    {
      v16 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 840))(a1);
      if ( v16 == 0 )
        LOBYTE(v16) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 1344))(a1);
    }
  }
  return v16;
}


// 守卫字段大复位（this+8600..8738 全区, 88L）
// ------------------------------------------------------------
// 0x5D51D0 sub_5D51D0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D51D0(char *this)
{
  char *v2; // edi
  int v3; // eax
  unsigned int v4; // edx
  uint32_t *v5; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // eax
  char result; // al
  int v11; // [esp+Ch] [ebp-4h] BYREF

  *((uint32_t *)this + 1639) = 19;
  *(this + 8668) = 1;
  *(this + 8669) = 0;
  *(this + 8660) = 0;
  *(this + 8600) = 1;
  *(this + 8601) = 1;
  *((uint16_t *)this + 4301) = 0;
  *(this + 8604) = 0;
  *((uint32_t *)this + 2156) = 0;
  *((uint32_t *)this + 2157) = 0;
  *((uint32_t *)this + 2158) = 0;
  *((uint32_t *)this + 2159) = 0;
  *((uint32_t *)this + 2160) = 0;
  *((uint32_t *)this + 2161) = 0;
  *((uint32_t *)this + 2162) = 0;
  *((uint32_t *)this + 2163) = 0;
  v2 = this + 8608;
  *((uint32_t *)this + 1698) = 0;
  *((uint32_t *)this + 1699) = 1;
  *((uint32_t *)this + 1700) = 1;
  *((uint32_t *)this + 1701) = 2;
  *((uint32_t *)this + 1702) = 3;
  v3 = *((uint32_t *)this + 2153);
  v11 = 700;
  if ( v3 != 0 )
    v4 = (*((uint32_t *)this + 2154) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*((uint32_t *)this + 2155) - v3) >> 2 )
  {
    v5 = *((uint32_t **)this + 2154);
    *v5 = 700;
    *((uint32_t *)this + 2154) = v5 + 1;
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&v11);
  }
  v6 = *((uint32_t *)v2 + 1);
  v11 = 1000;
  if ( v6 != 0 )
    v7 = (*((uint32_t *)v2 + 2) - v6) >> 2;
  else
    v7 = 0;
  if ( v6 != 0 && v7 < (*((uint32_t *)v2 + 3) - v6) >> 2 )
  {
    v8 = *((uint32_t **)v2 + 2);
    *v8 = 1000;
    *((uint32_t *)v2 + 2) = v8 + 1;
  }
  else
  {
    sub_430C80(*((void **)v2 + 2), 1, (int)&v11);
  }
  *(this + 8685) = 0;
  *(this + 8686) = 0;
  v9 = *(uint32_t *)this;
  *((uint32_t *)this + 2175) = 0;
  *(this + 8721) = 0;
  *(this + 8722) = 0;
  (*(void (/*thiscall*/ **)(char *, uint32_t))(v9 + 820))(this, 0);
  *(this + 8737) = 0;
  *(this + 8738) = 0;
  result = sub_698F90((int)(this + 8724), 100, 0);
  *((uint32_t *)this + 2179) = 3;
  *((uint32_t *)this + 2188) = 1065353216;
  *(this + 8723) = 1;
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5D5370 sub_5D5370
// ------------------------------------------------------------
void /*thiscall*/ sub_5D5370(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 150 )
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 1;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 时钟门 AI（sub_699000; this+8853/8854）
// ------------------------------------------------------------
// 0x5D5420 sub_5D5420
// ------------------------------------------------------------
char /*thiscall*/ sub_5D5420(int *this)
{
  int v2; // eax
  int v3; // edi
  int i; // ebx
  int v5; // edi
  int v6; // ecx
  int v8; // [esp+4h] [ebp-3Ch]
  int v9; // [esp+8h] [ebp-38h]
  int v10; // [esp+Ch] [ebp-34h]
  int v11; // [esp+10h] [ebp-30h]
  int v12; // [esp+14h] [ebp-2Ch]
  int v13; // [esp+18h] [ebp-28h]
  int v14; // [esp+1Ch] [ebp-24h]
  void *Block; // [esp+24h] [ebp-1Ch]
  int v16; // [esp+28h] [ebp-18h]
  int v17; // [esp+2Ch] [ebp-14h]
  int v18; // [esp+30h] [ebp-10h] BYREF
  int v19; // [esp+3Ch] [ebp-4h]

  LOBYTE(v2) = sub_5D2470((int)this);
  if ( *(this + 2175) == -1 )
  {
    v3 = *(this + 2216);
    v2 = sub_699000((int)(this + 2210));
    if ( v2 >= v3 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
      {
        Block = nullptr;
        v16 = 0;
        v17 = 0;
        v19 = 0;
        v8 = 0;
        v9 = 0;
        v10 = 0;
        v11 = 0;
        v12 = 0;
        v13 = 0;
        v14 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v5 = *(uint32_t *)(i + dword_8F850C);
          if ( v5 != 0 )
          {
            v6 = *(uint32_t *)(v5 + 196);
            if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 724))(v6) == 0 )
            {
              v18 = *(uint32_t *)(v5 + 196);
              sub_487F60(&v18);
            }
          }
        }
        v19 = -1;
      }
      *((uint8_t *)this + 8853) = 0;
      *((uint8_t *)this + 8854) = 0;
      LOBYTE(v2) = sub_698F90((int)(this + 2210), *(this + 2218), 0);
    }
  }
  return v2;
}



// 参数打包+时钟门 AI（sub_431230+sub_699000）
// ------------------------------------------------------------
// 0x5D56A0 sub_5D56A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5D56A0(uint32_t *this)
{
  int v2; // edi
  unsigned int result; // eax
  int v4; // eax
  uint8_t v5[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h]
  int v8; // [esp+18h] [ebp-14h]
  int v9; // [esp+1Ch] [ebp-10h] BYREF
  int v10; // [esp+28h] [ebp-4h]

  sub_5D2470((int)this);
  v2 = *(this + 2212);
  result = sub_699000((int)(this + 9));
  if ( v2 + *(this + 2211) < result || v2 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )
    {
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v10 = 0;
      v9 = rand() % 3;
      sub_431230((int)v5, &v9);
      v4 = *(this + 2210);
      if ( v4 == 2 || v4 == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 24, v5, 2, 0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 25, v5, 2, 0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      v10 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v7 = 0;
      v8 = 0;
    }
    *(this + 2211) = *(this + 2213);
    result = sub_699000((int)(this + 9));
    *(this + 2212) = result;
  }
  return result;
}



// 参数打包+RTTI AI（sub_431230+cast）
// ------------------------------------------------------------
// 0x5D57B0 sub_5D57B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D57B0(uint32_t *this)
{
  int result; // eax
  unsigned int i; // ebx
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // esi
  int v12; // ecx
  void *v13[4]; // [esp+4h] [ebp-20h] BYREF
  int v14; // [esp+14h] [ebp-10h] BYREF
  int v15; // [esp+20h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *(this + 29);
      v5 = *(uint32_t *)(v4 + 8);
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
      {
        v8 = *(this + 29);
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v11 != 0
          && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 340))(v11) == 704
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 568))(v11) != 20
          && *(this + 1813) != 0 )
        {
          memset(&v13[1], 0, 12);
          v12 = *(this + 1813);
          v15 = 0;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 48))(v12);
          sub_431230((int)v13, &v14);
          v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 52))(*(this + 1813));
          sub_431230((int)v13, &v14);
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)v11 + 560))(v11, 20, v13, 0, 0);
          v15 = -1;
          sub_5E5260(v13);
        }
      }
    }
  }
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl（24L）
// ------------------------------------------------------------
// 0x5D5920 sub_5D5920
// ------------------------------------------------------------
int /*thiscall*/ sub_5D5920(uint32_t *this, int a2, int a3)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/ExpellerBrokenParts.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/ExpellerBrokenParts.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2166) = result;
  return result;
}



// 复合门（this+200/568/8601/8603/8669 —— 最后受击时刻联动）
// ------------------------------------------------------------
// 0x5D59B0 sub_5D59B0
// ------------------------------------------------------------
char /*thiscall*/ sub_5D59B0(int this)
{
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 1 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
    }
    else if ( sub_41A5E0(this + 7028) == 2
           && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 4
           && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 568))(this) != 20 )
    {
      sub_5D57B0((uint32_t *)this);
    }
  }
  LOBYTE(v2) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(v2) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)v2 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
  }
  return v2;
}



// RTTI cast 大型 AI（100L）
// ------------------------------------------------------------
// 0x5D5A60 sub_5D5A60
// ------------------------------------------------------------
int /*userpurge*/ sub_5D5A60@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>, int ArgList, float a5, int a6, int a7)
{
  int result; // eax
  int v9; // eax
  unsigned int i; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int v20; // ebx
  uint32_t *v21; // eax
  uint32_t *v22; // edi
  int v23; // [esp-8h] [ebp-1Ch]
  int v24; // [esp-4h] [ebp-18h]

  result = *(uint32_t *)(a1 + 8816);
  if ( result == 0 )
  {
    sub_5D3640((int *)a1);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1172))(a1);
    *(uint32_t *)(a1 + 8816) = v9;
    if ( v9 > 5 )
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 384))(a1, 1);
    else
      result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 384))(a1, 0);
    *(uint32_t *)(a1 + 8716) = result;
  }
  if ( ArgList == 8 )
  {
    result = **(uint32_t **)(LODWORD(a5) + 4) - 2;
    switch ( **(uint32_t **)(LODWORD(a5) + 4) )
    {
      case 2:
      case 3:
      case 5:
        *(uint8_t *)(a1 + 8812) = 1;
        break;
      case 4:
        v24 = a2;
        v23 = a3;
        for ( i = 0; ; ++i )
        {
          v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 700))(a1, v23, v24);
          v12 = *(uint32_t *)(v11 + 4);
          v13 = v12 != 0 ? (*(uint32_t *)(v11 + 8) - v12) >> 2 : 0;
          if ( (int)i >= v13 )
            break;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
          v15 = *(uint32_t *)(v14 + 4);
          if ( v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2 )
            v16 = *(uint32_t *)(v15 + 4 * i);
          else
            v16 = 0;
          if ( *(uint32_t *)(v16 + 4) == a1 )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
            v17 = sub_517740(i);
            v18 = __RTDynamicCast(
                    v17,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNProvocationDollAura `RTTI Type Descriptor',
                    0);
            if ( v18 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v18 + 76))(v18, 0);
              break;
            }
          }
        }
        v19 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 384))(a1, 4, v23, v24);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 384))(a1, 5);
        v21 = operator new(0x98u);
        if ( v21 != nullptr )
          v22 = sub_591260(v21, v19, 0);
        else
          v22 = nullptr;
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*v22 + 56))(v22, a1, a1, 0, 0);
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*v22 + 64))(v22);
        *(uint32_t *)(result + 40) = v20;
        break;
      default:
        break;
    }
  }
  if ( *(uint8_t *)(a1 + 8669) == 1 )
    return sub_4E33D0(ArgList, a5, a6, a7);
  return result;
}



// ============================================================
// 【分区 5】锤王崩地与格挡（0x5D5C30-0x5D6590）
// 证据：GuardSpark/GuardCircle.ani 格挡特效（0x5D5C30）、R_HAMMER_KING 语音 +
//       PassiveObject/Common/Animation/{EarthQuake,EarthQuakeRing}.ani + HAMMER_KING_CRASH
//       （0x5D5F10 304L 锤王大地崩全演出）

// 格挡特效：Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani（104L；
//   研究 20 §3 vt+644 格挡特效族的守卫侧调用, 普通槽位版本）
// ------------------------------------------------------------
// 0x5D5C30 sub_5D5C30
// ------------------------------------------------------------
uint8_t /*userpurge*/ sub_5D5C30@<al>(int *a1@<ecx>, int a2@<ebx>, int a3, float *a4, int a5)
{
  uint8_t result; // al
  unsigned int v7; // edi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  char *v15; // eax
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  char *v20; // edi
  int v21; // eax
  int v22; // [esp+Ch] [ebp-10h]
  int v23; // [esp+24h] [ebp+8h]
  int v24; // [esp+24h] [ebp+8h]
  int v25; // [esp+24h] [ebp+8h]
  int v26; // [esp+28h] [ebp+Ch]

  result = *((uint8_t *)a1 + 642);
  if ( result != 0 )
  {
    v7 = a1[161];
    goto LABEL_7;
  }
  v8 = a1[30];
  if ( v8 != 0 )
  {
    if ( *(uint32_t *)(v8 + 148) == -1 )
      result = (uint8_t)sub_4938F0(a1[30]);
    v7 = *(uint32_t *)(v8 + 112);
LABEL_7:
    if ( v7 > 1 )
      return result;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 348))(a3, a2) + 12) != 0
    || (v9 = *a1,
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 120))(a3),
        (*(uint8_t (/*thiscall*/ **)(int *, int))(v9 + 180))(a1, v10) != 0) )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*a1 + 1104))(a1, 13);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*a1 + 876))(a1, 0, 300, 300, 0, -3000, 1);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(a1, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*a1 + 888))(a1, 0, 0, 1000, 1000);
  v11 = *a1;
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 152))(a1, 4);
  v13 = sub_432E50(v12);
  (*(void (/*thiscall*/ **)(int *, int))(v11 + 896))(a1, v13);
  v23 = (uint64_t)(a4[3] * 0.5 + *a4);
  v22 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*a1 + 124))(a1, (uint64_t)(a4[3] * 0.5 + *a4) >> 32);
  v26 = (uint64_t)(a4[5] * 0.5 + a4[2]);
  if ( sub_42FCB0(228) != 0 )
    v14 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
  else
    v14 = 0;
  v15 = (char *)sub_44B6C0(284);
  v16 = (int)v15;
  if ( v15 != nullptr )
  {
    sub_44E0D0(v15, v14, 1);
    *(uint32_t *)v16 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v16 = 0;
  }
  sub_45FE80(a1[29], v16, 2, 0, v16, (int)a1, 0);
  v17 = *(uint32_t *)v16;
  v18 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
  (*(void (/*thiscall*/ **)(int, int))(v17 + 148))(v16, v18);
  v19 = v23;
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 112))(v16, v23, v22, v26);
  if ( sub_42FCB0(228) != 0 )
    v24 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
  else
    v24 = 0;
  v20 = (char *)sub_44B6C0(284);
  if ( v20 != nullptr )
  {
    sub_44E0D0(v20, v24, 1);
    *(uint32_t *)v20 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v20 = nullptr;
  }
  sub_45FE80(a1[29], (int)v20, 2, 0, (int)v20, (int)a1, 0);
  v25 = *(uint32_t *)v20;
  v21 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
  (*(void (/*thiscall*/ **)(char *, int))(v25 + 148))(v20, v21);
  return (*(int (/*thiscall*/ **)(char *, int, int, int))(*(uint32_t *)v20 + 112))(v20, v19, v22, v26);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D5ED0 sub_5D5ED0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D5ED0(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 2209);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 2209));
    result = sub_657740(v2, 228);
  }
  *(this + 2209) = nullptr;
  return result;
}



// 锤王大地崩（304L）：R_HAMMER_KING 语音 + PassiveObject/Common/Animation/
//   {EarthQuake,EarthQuakeRing}.ani 双段震地 + HAMMER_KING_CRASH 播报
//   （this+200/208 + 8853..8936 相位 —— 与 0x5D2710 三连段配套的全演出）
// ------------------------------------------------------------
// 0x5D5F10 sub_5D5F10
// ------------------------------------------------------------
void /*thiscall*/ sub_5D5F10(int *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // edi
  int v5; // edi
  unsigned int v6; // edi
  int v7; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // ebx
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int *v23; // edi
  int v24; // edx
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int *v30; // edi
  int v31; // edx
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  unsigned int i; // ebx
  int v37; // ecx
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // eax
  int v43; // edi
  int v44; // edx
  int v45; // ebx
  int v46; // edx
  int v47; // eax
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // [esp-18h] [ebp-64h]
  int v52; // [esp-14h] [ebp-60h]
  BOOL v53; // [esp-10h] [ebp-5Ch]
  float v54; // [esp-8h] [ebp-54h]
  int v55; // [esp-4h] [ebp-50h]
  float v56; // [esp+Ch] [ebp-40h] BYREF
  float v57; // [esp+10h] [ebp-3Ch]
  int v58; // [esp+14h] [ebp-38h]
  int v59; // [esp+18h] [ebp-34h]
  int v60; // [esp+1Ch] [ebp-30h]
  int v61; // [esp+20h] [ebp-2Ch]
  void *v62[4]; // [esp+24h] [ebp-28h] BYREF
  int v63; // [esp+34h] [ebp-18h] BYREF
  int v64; // [esp+38h] [ebp-14h]
  float v65; // [esp+3Ch] [ebp-10h] BYREF
  int v66; // [esp+48h] [ebp-4h]

  sub_5D2470((int)this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v3 = *this;
  v64 = v2;
  v65 = (float)v2;
  v64 = (*(int (/*thiscall*/ **)(int *))(v3 + 740))(this);
  if ( v65 / (double)v64 <= *((float *)this + 2247) )
  {
    v4 = *(this + 2241);
    if ( sub_699000((int)(this + 2235)) >= v4 )
      *(uint8_t *)(*(this + 1905) + 96) = 1;
  }
  v5 = *(this + 2216);
  if ( sub_699000((int)(this + 2210)) >= v5 && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 5 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      v6 = 0;
      v7 = 0;
      while ( 1 )
      {
        v8 = *(this + 29);
        v9 = *(uint32_t *)(v8 + 8);
        v10 = v9 != 0 ? (*(uint32_t *)(v8 + 12) - v9) >> 2 : 0;
        if ( (int)v6 >= v10 )
          break;
        v11 = *(uint32_t *)(v8 + 8);
        if ( v11 != 0 && v6 < (*(uint32_t *)(v8 + 12) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * v6);
        else
          v12 = 0;
        if ( __RTDynamicCast(
               v12,
               0,
               &CNRDObject `RTTI Type Descriptor',
               &CNTinSwordManExpeller `RTTI Type Descriptor',
               0) != 0 )
          ++v7;
        ++v6;
      }
      if ( v7 < *(this + 2245) )
      {
        v13 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        v14 = *(uint32_t *)(v13 + 364);
        if ( v14 != 0 )
          v15 = (*(uint32_t *)(v13 + 368) - v14) >> 5;
        else
          v15 = 0;
        v64 = 224 * v15;
        v16 = sub_424FF0(v13);
        v17 = *this;
        v18 = 120 * (v16 + 3);
        v19 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 152))(
                this,
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        v20 = (*(int (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int))(*this + 376))(
                this,
                *(this + 2244),
                v64 / 2,
                v18 / 2,
                0,
                v19);
        (*(void (/*thiscall*/ **)(int *, int, int))(v17 + 592))(this, 705, v20);
      }
    }
    if ( *((uint8_t *)this + 8936) == 0 )
    {
      sub_4DB130(24, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_HAMMER_KING", -1, 0, 0);
      *((uint8_t *)this + 8936) = 1;
    }
    *((uint8_t *)this + 8853) = 0;
    *((uint8_t *)this + 8854) = 0;
    sub_698F90((int)(this + 2210), *(this + 2243), 0);
  }
  v21 = *(this + 2230);
  if ( sub_699000((int)(this + 2224)) >= v21 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 308))(this);
    *((uint8_t *)this + 8909) = 0;
    *((uint8_t *)this + 8910) = 0;
    sub_698F90((int)(this + 2224), *(this + 2246), 0);
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 3
    && sub_699000((int)(this + 2217)) > *(this + 2232)
    && *((uint8_t *)this + 8924) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
    v64 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? 1 : -1;
    LODWORD(v65) = (uint64_t)((double)v64 * *((float *)this + 2188) * 125.0);
    v63 = sub_44B6C0(284);
    v66 = 0;
    if ( v63 != 0 )
    {
      v64 = sub_42FCB0(228);
      LOBYTE(v66) = 1;
      if ( v64 != 0 )
        v22 = sub_431860((char)"PassiveObject/Common/Animation/EarthQuake.ani", 1);
      else
        v22 = 0;
      LOBYTE(v66) = 0;
      v23 = (int *)sub_44E1F0(v22, 1);
    }
    else
    {
      v23 = nullptr;
    }
    v24 = *v23;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v24 + 72))(v23, 2);
    sub_45FE80(*(this + 29), (int)v23, 2, 0, (int)v23, (int)this, 0);
    v25 = *v23;
    v26 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v26);
    v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v27 - 1);
    (*(void (/*thiscall*/ **)(int *, int))(v25 + 112))(v23, LODWORD(v65) + v28);
    v63 = sub_44B6C0(284);
    v66 = 2;
    if ( v63 != 0 )
    {
      v64 = sub_42FCB0(228);
      LOBYTE(v66) = 3;
      if ( v64 != 0 )
      {
        v29 = sub_431860((char)"PassiveObject/Common/Animation/EarthQuakeRing.ani", 1);
        LOBYTE(v66) = 2;
        v30 = (int *)sub_44E1F0(v29, 1);
      }
      else
      {
        LOBYTE(v66) = 2;
        v30 = (int *)sub_44E1F0(0, 1);
      }
    }
    else
    {
      v30 = nullptr;
    }
    v31 = *v30;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v31 + 72))(v30, 2);
    sub_45FE80(*(this + 29), (int)v30, 2, 0, (int)v30, (int)this, 0);
    v32 = *v30;
    v33 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v34 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v33);
    v35 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v34 - 2);
    (*(void (/*thiscall*/ **)(int *, int))(v32 + 112))(v30, LODWORD(v65) + v35);
    for ( i = 0; ; ++i )
    {
      v37 = *(this + 29);
      v38 = *(uint32_t *)(v37 + 8);
      v64 = i;
      v39 = v38 != 0 ? (*(uint32_t *)(v37 + 12) - v38) >> 2 : 0;
      if ( (int)i >= v39 )
        break;
      v40 = *(uint32_t *)(v37 + 8);
      if ( v40 != 0 && i < (*(uint32_t *)(v37 + 12) - v40) >> 2 )
        v41 = *(uint32_t *)(v40 + 4 * i);
      else
        v41 = 0;
      v42 = __RTDynamicCast(v41, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      v43 = v42;
      if ( (int *)v42 != this
        && v42 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v42 + 308))(v42) == 1
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v43 + 128))(v43) <= *(this + 2251) )
      {
        v44 = *(uint32_t *)v43;
        v65 = 0.0;
        v56 = 0.0;
        v57 = 0.0;
        v58 = 0;
        v59 = 0;
        v60 = 0;
        v61 = 0;
        v45 = (*(int (/*thiscall*/ **)(int))(v44 + 120))(v43);
        v46 = rand() % 60;
        v47 = *(uint32_t *)v43;
        v63 = v45 + v46 - 30;
        v56 = (float)v63;
        v48 = (*(int (/*thiscall*/ **)(int))(v47 + 124))(v43);
        v49 = *(uint32_t *)v43;
        v63 = v48;
        v58 = 1092616192;
        v57 = (float)v48;
        v59 = 1106247680;
        v60 = 1106247680;
        v61 = 1084227584;
        (*(void (/*thiscall*/ **)(int))(v49 + 44))(v43);
        v55 = sub_605840(&v65, v43, &v56, 1);
        v54 = v65;
        v53 = rand() % 2 == 0;
        v52 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v43 + 128))(v43);
        v51 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v43 + 124))(v43);
        v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v43 + 120))(v43);
        sub_4E4A50(this, 30312, 0, v50, v51, v52, v53, 0, LODWORD(v54), v55);
        i = v64;
      }
    }
    sub_424120(*(uint32_t **)(*(this + 29) + 132), *(this + 2249), *(this + 2250));
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
      dword_8F7C04,
      "HAMMER_KING_CRASH",
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
    *((uint8_t *)this + 8924) = 1;
  }
  if ( *(this + 2233) != 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
  {
    memset(&v62[1], 0, 12);
    v66 = 4;
    v63 = 3;
    sub_431230((int)v62, &v63);
    (*(void (/*thiscall*/ **)(int *, int, void **, int, uint32_t))(*this + 560))(this, 8, v62, 2, 0);
    (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
    sub_5E5260(v62);
  }
}


// ============================================================
// 【分区 6】四属性守卫特效族（ksguard_*）（0x5D6590-0x5D6CF0）
// 证据：equipment/character/common/title/titleanimation/ksguard_{light,wind,ice,protection,
//       flame}.ani 五系守卫特效 + Common/ActiveStatus/Animation/Haste.ani +
//       Particle/TrackingFire.ptl 追踪火 + R_DEFEN_GUARD_{DIE,DMG,ALIVE,AMB} 语音组

// 光守卫特效：ksguard_light.ani（58L；titleanimation 目录复用 —— 光属性守卫）
// ------------------------------------------------------------
// 0x5D6590 sub_5D6590
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6590(float *this)
{
  double v2; // st7
  int v3; // eax
  int v4; // eax
  float v5; // edx
  double v6; // st7
  float v7; // eax
  int v8; // eax
  float v9; // edx
  int v10; // eax
  float v11; // edx
  int v12; // eax
  float v13; // edx
  int v14; // eax
  float v15; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  *(uint8_t *)(*((uint32_t *)this + 1905) + 64) = 0;
  v2 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v3 = *(uint32_t *)this;
  *(this + 2221) = v2 * 0.0099999998;
  v4 = (*(int (/*thiscall*/ **)(float *, int))(v3 + 384))(this, 1);
  v5 = *this;
  *(this + 2222) = (double)v4 * 0.0099999998;
  v6 = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v5) + 384))(this, 2);
  v7 = *this;
  *(this + 2223) = v6 * 0.0099999998;
  v8 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v7) + 384))(this, 3);
  v9 = *this;
  *((uint32_t *)this + 2225) = v8;
  *((uint32_t *)this + 2226) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 4);
  v10 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  v11 = *this;
  *((uint32_t *)this + 2227) = v10;
  *((uint32_t *)this + 2229) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);
  v12 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v13 = *this;
  *((uint32_t *)this + 2230) = v12;
  *((uint32_t *)this + 2231) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);
  v14 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);
  v15 = *this;
  *((uint32_t *)this + 2232) = v14;
  *(this + 2233) = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v15) + 384))(this, 10) * 0.0099999998;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_light.ani", 1);
  else
    result = 0;
  *((uint32_t *)this + 2209) = result;
  return result;
}



// 风守卫特效：Common/ActiveStatus/Animation/Haste.ani + ksguard_wind.ani（加速/风）
// ------------------------------------------------------------
// 0x5D6700 sub_5D6700
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6700(float *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  double v8; // st7
  float v9; // eax
  int v10; // eax
  float v11; // edx
  int v12; // eax
  float v13; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);
  else
    v2 = 0;
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 2245) = v2;
  *((uint32_t *)this + 2253) = (*(int (/*thiscall*/ **)(float *, uint32_t))(v3 + 384))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 2254) = v4;
  *((uint32_t *)this + 2255) = (*(int (/*thiscall*/ **)(float *, int))(v5 + 384))(this, 2);
  v6 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v7 = *(uint32_t *)this;
  *(this + 2256) = (double)v6 * 0.0099999998;
  v8 = (double)(*(int (/*thiscall*/ **)(float *, int))(v7 + 384))(this, 4);
  v9 = *this;
  *(this + 2257) = v8 * 0.0099999998;
  v10 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 5);
  v11 = *this;
  *((uint32_t *)this + 2259) = v10;
  *((uint32_t *)this + 2260) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);
  v12 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v13 = *this;
  *((uint32_t *)this + 2261) = v12;
  *((uint32_t *)this + 2262) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_wind.ani", 1);
  else
    result = 0;
  *((uint32_t *)this + 2209) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D6860 sub_5D6860
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6860(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 2245);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 2245));
    result = sub_657740(v2, 228);
  }
  *(this + 2245) = nullptr;
  return result;
}



// 冰守卫特效：ksguard_ice.ani（31L）
// ------------------------------------------------------------
// 0x5D68A0 sub_5D68A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D68A0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v3 = *this;
  *(this + 2219) = v2;
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 2);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v5 = *this;
  *(this + 2221) = v4;
  *(this + 2222) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_ice.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// 防御守卫语音组：R_DEFEN_GUARD_DIE/DMG/ALIVE/AMB 四件套 + ksguard_protection.ani（60L）
// ------------------------------------------------------------
// 0x5D6960 sub_5D6960
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6960(uint32_t *this)
{
  int v2; // edi
  uint32_t *v3; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // ecx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  v2 = 0;
  v3 = this + 2213;
  do
    *v3++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v2++);
  while ( v2 < 3 );
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v5 = *this;
  *(this + 2216) = v4;
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v7 = *this;
  *(this + 2226) = v6;
  *(this + 2179) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 6);
  v8 = 8;
  v9 = this + 2219;
  do
  {
    *(v9 - 2) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 - 1);
    *v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 + 1);
    v11 = *((uint8_t *)v9 - 8);
    v9[2] = v10;
    v9[4] = v11 | ((*(uint8_t *)v9 | ((v10 | 0xFFFFFF00) << 8)) << 8);
    v8 += 3;
    ++v9;
  }
  while ( v8 < 14 );
  sub_4015C0("R_DEFEN_GUARD_DIE", 0x11u);
  sub_4015C0("R_DEFEN_GUARD_DMG", 0x11u);
  sub_4015C0("R_DEFEN_GUARD_ALIVE", 0x13u);
  sub_4015C0("R_DEFEN_GUARD_AMB", 0x11u);
  *(this + 2208) = 0;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_protection.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// 火守卫特效：Particle/TrackingFire.ptl 追踪火 + ksguard_flame.ani（79L）
// ------------------------------------------------------------
// 0x5D6AF0 sub_5D6AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6AF0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v2 = sub_4C3640(this + 91, "Particle/TrackingFire.ptl", this);
    else
      v2 = sub_4C3640(*(this + 91), "Particle/TrackingFire.ptl", this);
  }
  else
  {
    v2 = 0;
  }
  v3 = *this;
  *(this + 2214) = v2;
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 384))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v5 = *this;
  *(this + 2219) = v4;
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 2);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v7 = *this;
  *(this + 2221) = v6;
  *(this + 2223) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 4);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v9 = *this;
  *(this + 2224) = v8;
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v9 + 384))(this, 6);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 7);
  v11 = *this;
  *(this + 2226) = v10;
  *(this + 2227) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 384))(this, 8);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v13 = *this;
  *(this + 2228) = v12;
  *(this + 2229) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 384))(this, 10);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 11);
  v15 = *this;
  *(this + 2230) = v14;
  *(this + 2231) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v15 + 384))(this, 12);
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);
  v17 = *this;
  *(this + 2232) = v16;
  *(this + 2233) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v17 + 384))(this, 14);
  *(this + 2234) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 15);
  *(this + 2188) = 1065353216;
  *(this + 2207) = 0;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_flame.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// ============================================================
// 【分区 7】驱逐者 AMOR 命中与相位字段区（0x5D6CF0-0x5D7F80）
// 证据：AMOR_HIT + R_EXPELLER_ALIVE/R_EXPELLER_AMB_LOOP 语音、this+8840..9012 扩展字段区
//       （与 0x5CF 分区阿莫尔同构）、AMOR_HIT 复现群

// 驱逐者命中+语音：AMOR_HIT + R_EXPELLER_ALIVE + R_EXPELLER_AMB_LOOP（44L；
//   this+8612..8728 相位字段）
// ------------------------------------------------------------
// 0x5D6CF0 sub_5D6CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6CF0(int this, char ArgList, int a3)
{
  sub_4A4EA0(ArgList, a3);
  *(uint32_t *)this = &CNSoldier::`vftable';
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8672) = &off_6C2B88;
  *(uint32_t *)(this + 8680) = 0;
  *(uint8_t *)(this + 8684) = 1;
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint8_t *)(this + 8728) = 0;
  *(uint32_t *)(this + 8724) = &off_6C2B88;
  *(uint32_t *)(this + 8732) = 0;
  *(uint8_t *)(this + 8736) = 1;
  *(uint8_t *)(this + 8738) = 0;
  *(uint8_t *)(this + 8737) = 0;
  *(uint32_t *)(this + 8748) = 0;
  *(uint32_t *)(this + 8744) = 0;
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8780) = 15;
  *(uint32_t *)(this + 8776) = 0;
  *(uint8_t *)(this + 8760) = 0;
  *(uint32_t *)(this + 8808) = 15;
  *(uint32_t *)(this + 8804) = 0;
  *(uint8_t *)(this + 8788) = 0;
  sub_5D51D0((char *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, 0);
  sub_4015C0("AMOR_HIT", 8u);
  sub_4015C0("R_EXPELLER_ALIVE", 0x10u);
  sub_4015C0("R_EXPELLER_AMB_LOOP", 0x13u);
  return this;
}



// 相位字段（this+8676/8728/8760/8788）
// ------------------------------------------------------------
// 0x5D6E40 sub_5D6E40
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6E40(void *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNSoldier::`vftable';
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2166);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *((uint32_t *)this + 2166) = 0;
  if ( *((uint32_t *)this + 2202) >= 0x10u )
    j__free(*((void **)this + 2197));
  *((uint32_t *)this + 2202) = 15;
  *((uint32_t *)this + 2201) = 0;
  *((uint8_t *)this + 8788) = 0;
  if ( *((uint32_t *)this + 2195) >= 0x10u )
    j__free(*((void **)this + 2190));
  *((uint32_t *)this + 2195) = 15;
  *((uint32_t *)this + 2194) = 0;
  *((uint8_t *)this + 8760) = 0;
  *((uint32_t *)this + 2181) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8728) = 0;
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8676) = 0;
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F50 sub_5D6F50
// ------------------------------------------------------------
void */*thiscall*/ sub_5D6F50(void *Block, char a2)
{
  sub_5D6E40(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F80 sub_5D6F80
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6F80(void ***this)
{
  void **v2; // edi

  *this = &CNKingGuard::`vftable';
  v2 = *(this + 2209);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_657740(v2, 228);
  }
  *(this + 2209) = nullptr;
  return sub_5D6E40(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7000 sub_5D7000
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7000(void ***Block, char a2)
{
  sub_5D6F80(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D7030 sub_5D7030
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7030(uint32_t *this, char ArgList, int a3, char a4)
{
  sub_5D6CF0(ArgList, a3);
  *this = &CNKingGuard::`vftable';
  *(this + 2203) = 1;
  *(this + 2204) = 1;
  *(this + 2205) = 1;
  *(this + 2206) = 1;
  *(this + 2207) = 1;
  *(this + 2208) = 1;
  *(this + 2209) = 0;
  sub_5D18E0(this);
  if ( a4 == 1 )
  {
    sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  }
  else
  {
    sub_4D50A0(*(this + 1540));
    sub_5CF120(this);
  }
  return this;
}



// 驱逐者相位字段 A（this+8840..8881）
// ------------------------------------------------------------
// 0x5D7100 sub_5D7100
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7100(int this, char ArgList, int a3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, a3, 0);
  *(uint32_t *)this = &CNHammerKing::`vftable';
  *(uint8_t *)(this + 8844) = 0;
  *(uint32_t *)(this + 8840) = &off_6C2B88;
  *(uint32_t *)(this + 8848) = 0;
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8868) = &off_6C2B88;
  *(uint32_t *)(this + 8876) = 0;
  *(uint8_t *)(this + 8880) = 1;
  *(uint8_t *)(this + 8882) = 0;
  *(uint8_t *)(this + 8881) = 0;
  *(uint32_t *)(this + 8892) = 0;
  *(uint32_t *)(this + 8888) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint8_t *)(this + 8900) = 0;
  *(uint32_t *)(this + 8896) = &off_6C2B88;
  *(uint32_t *)(this + 8904) = 0;
  *(uint8_t *)(this + 8908) = 1;
  *(uint8_t *)(this + 8910) = 0;
  *(uint8_t *)(this + 8909) = 0;
  *(uint32_t *)(this + 8920) = 0;
  *(uint32_t *)(this + 8916) = 0;
  *(uint32_t *)(this + 8912) = 0;
  *(uint8_t *)(this + 8944) = 0;
  *(uint32_t *)(this + 8940) = &off_6C2B88;
  *(uint32_t *)(this + 8948) = 0;
  *(uint8_t *)(this + 8952) = 1;
  *(uint8_t *)(this + 8954) = 0;
  *(uint8_t *)(this + 8953) = 0;
  *(uint32_t *)(this + 8964) = 0;
  *(uint32_t *)(this + 8960) = 0;
  *(uint32_t *)(this + 8956) = 0;
  sub_5CF690(this);
  sub_5D25D0(v4);
  return this;
}



// 驱逐者相位字段 B（this+8844/8872/8900/8944）
// ------------------------------------------------------------
// 0x5D7240 sub_5D7240
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7240(void ***this)
{
  *this = &CNHammerKing::`vftable';
  *(this + 2235) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8944) = 0;
  *(this + 2224) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8900) = 0;
  *(this + 2217) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8872) = 0;
  *(this + 2210) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8844) = 0;
  return sub_5D6F80(this);
}



// 驱逐者相位字段 C（this+8852..8876）
// ------------------------------------------------------------
// 0x5D7290 sub_5D7290
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7290(int this, char ArgList, int a3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, a3, 1);
  *(uint32_t *)this = &CNGuardLight::`vftable';
  *(uint8_t *)(this + 8856) = 0;
  *(uint32_t *)(this + 8852) = &off_6C2B88;
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8864) = 1;
  *(uint8_t *)(this + 8866) = 0;
  *(uint8_t *)(this + 8865) = 0;
  *(uint32_t *)(this + 8876) = 0;
  *(uint32_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8868) = 0;
  sub_5CF740(this);
  sub_5D6590(v4);
  return this;
}



// AI 字段访问（this+8856）
// ------------------------------------------------------------
// 0x5D7330 sub_5D7330
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7330(void ***this)
{
  *this = &CNGuardLight::`vftable';
  *((uint32_t *)dword_8F8528 + 623) = 0;
  *(this + 2213) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8856) = 0;
  return sub_5D6F80(this);
}



// 驱逐者相位字段 D（this+8844..8889）
// ------------------------------------------------------------
// 0x5D7360 sub_5D7360
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7360(int this, char ArgList, int a3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, a3, 1);
  *(uint32_t *)this = &CNGuardWind::`vftable';
  *(uint8_t *)(this + 8848) = 0;
  *(uint32_t *)(this + 8844) = &off_6C2B88;
  *(uint32_t *)(this + 8852) = 0;
  *(uint8_t *)(this + 8856) = 1;
  *(uint8_t *)(this + 8858) = 0;
  *(uint8_t *)(this + 8857) = 0;
  *(uint32_t *)(this + 8868) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8876) = &off_6C2B88;
  *(uint32_t *)(this + 8884) = 0;
  *(uint8_t *)(this + 8888) = 1;
  *(uint8_t *)(this + 8890) = 0;
  *(uint8_t *)(this + 8889) = 0;
  *(uint32_t *)(this + 8900) = 0;
  *(uint32_t *)(this + 8896) = 0;
  *(uint32_t *)(this + 8892) = 0;
  *(uint32_t *)(this + 8908) = sub_4A2D10(this + 8904);
  *(uint32_t *)(this + 8912) = 0;
  *(uint8_t *)(this + 8920) = 0;
  *(uint32_t *)(this + 8916) = &off_6C2B88;
  *(uint32_t *)(this + 8924) = 0;
  *(uint8_t *)(this + 8928) = 1;
  *(uint8_t *)(this + 8930) = 0;
  *(uint8_t *)(this + 8929) = 0;
  *(uint32_t *)(this + 8940) = 0;
  *(uint32_t *)(this + 8936) = 0;
  *(uint32_t *)(this + 8932) = 0;
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8944) = &off_6C2B88;
  *(uint32_t *)(this + 8952) = 0;
  *(uint8_t *)(this + 8956) = 1;
  *(uint8_t *)(this + 8958) = 0;
  *(uint8_t *)(this + 8957) = 0;
  *(uint32_t *)(this + 8968) = 0;
  *(uint32_t *)(this + 8964) = 0;
  *(uint32_t *)(this + 8960) = 0;
  *(uint8_t *)(this + 8988) = 0;
  *(uint32_t *)(this + 8984) = &off_6C2B88;
  *(uint32_t *)(this + 8992) = 0;
  *(uint8_t *)(this + 8996) = 1;
  *(uint8_t *)(this + 8998) = 0;
  *(uint8_t *)(this + 8997) = 0;
  *(uint32_t *)(this + 9008) = 0;
  *(uint32_t *)(this + 9004) = 0;
  *(uint32_t *)(this + 9000) = 0;
  sub_5CF7F0(this);
  sub_5D6700(v4);
  return this;
}



// 驱逐者相位字段 E（this+8844..8988）
// ------------------------------------------------------------
// 0x5D7500 sub_5D7500
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7500(int this)
{
  void **v2; // edi

  *(uint32_t *)this = &CNGuardWind::`vftable';
  v2 = *(void ***)(this + 8980);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_657740(v2, 228);
  }
  *(uint32_t *)(this + 8980) = 0;
  *(uint32_t *)(this + 8984) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8988) = 0;
  *(uint32_t *)(this + 8944) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8916) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8920) = 0;
  sub_6569D0(this + 8904);
  j__free(*(void **)(this + 8908));
  *(uint32_t *)(this + 8908) = 0;
  *(uint32_t *)(this + 8876) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8844) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8848) = 0;
  return sub_5D6F80((void ***)this);
}



// 驱逐者相位字段 F（this+8840..8884）
// ------------------------------------------------------------
// 0x5D75E0 sub_5D75E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D75E0(int this, char ArgList, int a3)
{
  sub_5D7030((uint32_t *)this, ArgList, a3, 1);
  *(uint32_t *)this = &CNGuardIce::`vftable';
  *(uint8_t *)(this + 8844) = 0;
  *(uint32_t *)(this + 8840) = &off_6C2B88;
  *(uint32_t *)(this + 8848) = 0;
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8868) = 1;
  *(uint32_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8876) = 0;
  *(uint32_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint32_t *)(this + 8888) = 0;
  sub_5D68A0((uint32_t *)this);
  return this;
}



// AI 字段访问（this+8844）
// ------------------------------------------------------------
// 0x5D76B0 sub_5D76B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D76B0(void ***this)
{
  *this = &CNGuardIce::`vftable';
  *(this + 2210) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8844) = 0;
  return sub_5D6F80(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D76D0 sub_5D76D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D76D0(uint32_t *this, char ArgList, int a3)
{
  uint32_t *v4; // ecx

  sub_5D7030(this, ArgList, a3, 1);
  *this = &CNGuardBlock::`vftable';
  sub_5CFAE0(this);
  sub_5D6960(v4);
  return this;
}



// AI 字段访问（this+8841）
// ------------------------------------------------------------
// 0x5D7740 sub_5D7740
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7740(uint32_t *this, char ArgList, int a3)
{
  int v4; // edx

  sub_5D7030(this, ArgList, a3, 1);
  *this = &CNGuardFire::`vftable';
  sub_41A630((unsigned int)this + 8841);
  *(uint32_t *)((char *)this + 8841) = &clong::`vftable';
  sub_5CFCC0((int)this, v4);
  sub_5D6AF0(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D77C0 sub_5D77C0
// ------------------------------------------------------------
void */*thiscall*/ sub_5D77C0(void *Block, char a2)
{
  sub_5D77F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问（this+8841/8856）
// ------------------------------------------------------------
// 0x5D77F0 sub_5D77F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D77F0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGuardFire::`vftable';
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8856);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 8856) = 0;
  sub_41A580(this + 8841);
  return sub_5D6F80((void ***)this);
}



// AI 字段访问（this+8601）
// ------------------------------------------------------------
// 0x5D7870 sub_5D7870
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7870(uint8_t *this, char ArgList, int a3)
{
  sub_5D6CF0(ArgList, a3);
  *(uint32_t *)this = &CNAxeExpeller::`vftable';
  *(this + 8601) = 0;
  *((uint32_t *)this + 2204) = 0;
  *((uint32_t *)this + 2203) = 0;
  sub_5D4E30(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  return this;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D78F0 sub_5D78F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D78F0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *this = &CNAxeExpeller::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);
  *(this + 2204) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 2203) = 0;
  return sub_5D6E40(this);
}



// 时钟门 AI（sub_699000; this+8600/8812/8829/8837）
// ------------------------------------------------------------
// 0x5D7970 sub_5D7970
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7970(void *this, char ArgList, int a3)
{
  int v4; // edx
  unsigned int v5; // ecx
  uint32_t *v6; // eax

  sub_5D6CF0(ArgList, a3);
  *(uint32_t *)this = &CNHeavenExpeller::`vftable';
  *((uint8_t *)this + 8600) = 0;
  *((uint8_t *)this + 8829) = 0;
  *((uint32_t *)this + 2208) = 0;
  *((uint8_t *)this + 8812) = 0;
  *((uint32_t *)this + 2204) = sub_699000((int)this + 36);
  *((uint32_t *)this + 2206) = 0;
  *((uint32_t *)this + 2205) = 30;
  *((uint8_t *)this + 8837) = 0;
  sub_5D0DE0(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  a3 = 1000;
  sub_430C80(*((void **)this + 2154), 1, (int)&a3);
  v4 = *((uint32_t *)this + 2153);
  a3 = 2000;
  if ( v4 != 0 )
    v5 = (*((uint32_t *)this + 2154) - v4) >> 2;
  else
    v5 = 0;
  if ( v4 != 0 && v5 < (*((uint32_t *)this + 2155) - v4) >> 2 )
  {
    v6 = *((uint32_t **)this + 2154);
    *v6 = 2000;
    *((uint32_t *)this + 2154) = v6 + 1;
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&a3);
  }
  return this;
}



// 阿莫尔命中 4：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D7AE0 sub_5D7AE0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7AE0(uint8_t *this, char ArgList, int a3, char a4)
{
  int v5; // eax

  sub_5D6CF0(ArgList, a3);
  *(uint32_t *)this = &CNLegionExpeller::`vftable';
  *(this + 8601) = 0;
  *(this + 8812) = 0;
  *(this + 8600) = 0;
  v5 = sub_42A560(this);
  *((uint32_t *)this + 2206) = v5;
  *((uint32_t *)this + 2205) = v5;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;
  sub_4015C0("AMOR_HIT", 8u);
  sub_5D1160(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( a4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BA0 sub_5D7BA0
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7BA0(void *Block, char a2)
{
  sub_5D7BD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BD0 sub_5D7BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7BD0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &CNLegionExpeller::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 2207) = 0;
  return sub_5D6E40(this);
}



// AI 相位字段（this+8600/8812/8820）
// ------------------------------------------------------------
// 0x5D7C40 sub_5D7C40
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7C40(uint8_t *this, char ArgList, int a3, char a4)
{
  sub_5D6CF0(ArgList, a3);
  *(uint32_t *)this = &CNSandorExpeller::`vftable';
  *(this + 8812) = 0;
  *((uint32_t *)this + 2204) = 0;
  *(this + 8820) = 0;
  *(this + 8600) = 0;
  sub_5D2320(this);
  if ( a4 == 1 )
  {
    sub_4D50A0(*((uint32_t *)this + 1540));
    sub_5CF120(this);
  }
  sub_5D3640(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7CE0 sub_5D7CE0
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7CE0(void ***Block, char a2)
{
  sub_5D7240(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D10 sub_5D7D10
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D10(void ***Block, char a2)
{
  sub_5D7330(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D40 sub_5D7D40
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7D40(void *Block, char a2)
{
  sub_5D7500((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D70 sub_5D7D70
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D70(void ***Block, char a2)
{
  sub_5D76B0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DA0 sub_5D7DA0
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7DA0(void *Block, char a2)
{
  sub_5D7730();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DD0 sub_5D7DD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7DD0(uint32_t *Block, char a2)
{
  sub_5D78F0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E00 sub_5D7E00
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E00(void *Block, char a2)
{
  sub_5D7AD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E30 sub_5D7E30
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E30(void *Block, char a2)
{
  sub_5D7CD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D7E60 sub_5D7E60
// ------------------------------------------------------------
char */*thiscall*/ sub_5D7E60(char *this, void *Block, int a3, int a4, int a5)
{
  sub_485CC0();
  *(uint32_t *)this = &CNRDEquipment::`vftable';
  sub_4B3BE0(this + 148);
  sub_437E70(this + 212);
  sub_4E9A50(this + 1160);
  *(this + 1224) = 0;
  *((uint32_t *)this + 305) = &off_6C2B88;
  *((uint32_t *)this + 307) = 0;
  *(this + 1232) = 1;
  *(this + 1234) = 0;
  *(this + 1233) = 0;
  *((uint32_t *)this + 311) = 0;
  *((uint32_t *)this + 310) = 0;
  *((uint32_t *)this + 309) = 0;
  *((uint32_t *)this + 314) = 0;
  *((uint32_t *)this + 315) = 0;
  *((uint32_t *)this + 316) = 0;
  *((uint32_t *)this + 318) = 0;
  sub_41BFE0((void **)this + 318, szPassword);
  *((uint32_t *)this + 323) = 0;
  *((uint32_t *)this + 324) = 0;
  *((uint32_t *)this + 325) = 0;
  *((uint32_t *)this + 327) = 0;
  *((uint32_t *)this + 328) = 0;
  *((uint32_t *)this + 329) = 0;
  sub_4E9D70(this);
  sub_4EE580(Block, a3, a4, a5);
  return this;
}



// ============================================================
// 【分区 8】驱逐者八型外观装载（0x5D7F80-0x5D89A0）
// 证据：Monster/Soldier/{HammerKing 七件, Expeller 六件, AxeExpeller 六件, HeavenExpeller 七件,
//       AxionExpeller 七件, TSMExpeller 六件, LegionExpeller 六件, SandorExpeller 六件}.equ +
//       Monster/Soldier/Guard/GuardHandle.equ 双载入 + Particle/ExpellerBrokenParts.ptl

// 锤王装载：Monster/Soldier/HammerKing/{Cloak1,Cloak2,Leg,Head1,Head2,Shield,Weapon}.equ
//   七件（46L）
// ------------------------------------------------------------
// 0x5D7F80 sub_5D7F80
// ------------------------------------------------------------
void /*thiscall*/ sub_5D7F80(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HammerKing/Cloak1.equ";
  v6[1] = "Monster/Soldier/HammerKing/Cloak2.equ";
  v6[2] = "Monster/Soldier/HammerKing/Leg.equ";
  v6[3] = "Monster/Soldier/HammerKing/Head1.equ";
  v6[4] = "Monster/Soldier/HammerKing/Head2.equ";
  v6[5] = "Monster/Soldier/HammerKing/Shield.equ";
  v6[6] = "Monster/Soldier/HammerKing/Weapon.equ";
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 守卫装载：Monster/Soldier/Guard/GuardHandle.equ（45L；守卫持械）
// ------------------------------------------------------------
// 0x5D8040 sub_5D8040
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8040(char **this)
{
  void **v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  char *result; // eax

  v1 = (void **)off_795608;
  v2 = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      v3 = (char *)operator new(0x544u);
      if ( v3 != nullptr )
        v4 = sub_5D7E60(v3, *v1, 0, 0, 3);
      else
        v4 = nullptr;
      *v2 = v4;
    }
    ++v1;
    ++v2;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
  {
    result = sub_5D7E60(v5, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
    *(this + 2162) = result;
  }
  else
  {
    *(this + 2162) = nullptr;
    return nullptr;
  }
  return result;
}



// 守卫装载 2：Monster/Soldier/Guard/GuardHandle.equ（48L）
// ------------------------------------------------------------
// 0x5D8120 sub_5D8120
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8120(char **this)
{
  void **v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  char *result; // eax

  v1 = (void **)off_795608;
  v2 = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      v3 = (char *)operator new(0x544u);
      if ( v3 != nullptr )
        v4 = sub_5D7E60(v3, *v1, 0, 0, 4);
      else
        v4 = nullptr;
      *v2 = v4;
    }
    ++v1;
    ++v2;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_5D7E60(v5, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
  else
    v6 = nullptr;
  *(this + 2162) = v6;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    result = sub_5D7E60(v7, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
  else
    result = nullptr;
  *(this + 2163) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8230 sub_5D8230
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8230(char **this)
{
  void **v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  v2 = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      v3 = (char *)operator new(0x544u);
      if ( v3 != nullptr )
        v4 = sub_5D7E60(v3, *v1, 0, 0, 1);
      else
        v4 = nullptr;
      *v2 = v4;
    }
    ++v1;
    ++v2;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D82C0 sub_5D82C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D82C0(char **this)
{
  void **v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  v2 = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      v3 = (char *)operator new(0x544u);
      if ( v3 != nullptr )
        v4 = sub_5D7E60(v3, *v1, 0, 0, 2);
      else
        v4 = nullptr;
      *v2 = v4;
    }
    ++v1;
    ++v2;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8350 sub_5D8350
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8350(char **this)
{
  void **v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  v2 = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      v3 = (char *)operator new(0x544u);
      if ( v3 != nullptr )
        v4 = sub_5D7E60(v3, *v1, 0, 0, 0);
      else
        v4 = nullptr;
      *v2 = v4;
    }
    ++v1;
    ++v2;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// 驱逐者装载：Monster/Soldier/Expeller/{Leg,Head,RightArm,LeftArm,HeadEnd,Glow}.equ 六件
// ------------------------------------------------------------
// 0x5D83E0 sub_5D83E0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D83E0(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/Expeller/ExpellerLeg.equ";
  v6[1] = "Monster/Soldier/Expeller/ExpellerHead.equ";
  v6[2] = "Monster/Soldier/Expeller/ExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/Expeller/ExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/Expeller/ExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/Expeller/ExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 斧驱逐者装载：Monster/Soldier/AxeExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8490 sub_5D8490
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8490(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxeExpeller/AxeExpellerLeg.equ";
  v6[1] = "Monster/Soldier/AxeExpeller/AxeExpellerHead.equ";
  v6[2] = "Monster/Soldier/AxeExpeller/AxeExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/AxeExpeller/AxeExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/AxeExpeller/AxeExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/AxeExpeller/AxeExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 天界驱逐者装载：Monster/Soldier/HeavenExpeller/ 七件套（含 LeftArmHandle）
// ------------------------------------------------------------
// 0x5D8540 sub_5D8540
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8540(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeg.equ";
  v6[1] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHead.equ";
  v6[2] = "Monster/Soldier/HeavenExpeller/HeavenExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArmHandle.equ";
  v6[5] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHeadEnd.equ";
  v6[6] = "Monster/Soldier/HeavenExpeller/HeavenExpellerGlow.equ";
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 冲击驱逐者装载：Monster/Soldier/AxionExpeller/ 七件套（含 LeftArmHandle）
// ------------------------------------------------------------
// 0x5D8600 sub_5D8600
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8600(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxionExpeller/AxionExpellerLeg.equ";
  v6[1] = "Monster/Soldier/AxionExpeller/AxionExpellerHead.equ";
  v6[2] = "Monster/Soldier/AxionExpeller/AxionExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArmHandle.equ";
  v6[5] = "Monster/Soldier/AxionExpeller/AxionExpellerHeadEnd.equ";
  v6[6] = "Monster/Soldier/AxionExpeller/AxionExpellerGlow.equ";
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// TSM 驱逐者装载：Monster/Soldier/TSMExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D86C0 sub_5D86C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5D86C0(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/TSMExpeller/TSMExpellerLeg.equ";
  v6[1] = "Monster/Soldier/TSMExpeller/TSMExpellerHead.equ";
  v6[2] = "Monster/Soldier/TSMExpeller/TSMExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/TSMExpeller/TSMExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/TSMExpeller/TSMExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/TSMExpeller/TSMExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 军团驱逐者装载：Monster/Soldier/LegionExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8770 sub_5D8770
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8770(char **this)
{
  int v1; // edi
  char **v2; // ebx
  void *v3; // esi
  char *v4; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/LegionExpeller/LegionExpellerLeg.equ";
  v6[1] = "Monster/Soldier/LegionExpeller/LegionExpellerHead.equ";
  v6[2] = "Monster/Soldier/LegionExpeller/LegionExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/LegionExpeller/LegionExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/LegionExpeller/LegionExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/LegionExpeller/LegionExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  v2 = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      v4 = (char *)operator new(0x544u);
      v6[8] = v4;
      v7 = 0;
      if ( v4 != nullptr )
        v5 = sub_4BA9E0(v4, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *v2 = v5;
    }
    ++v1;
    ++v2;
  }
  while ( v1 < 8 );
}



// 桑德尔驱逐者装载：Monster/Soldier/SandorExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8820 sub_5D8820
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8820(char **this)
{
  int v1; // esi
  char **v2; // edi
  char *v3; // eax
  char *result; // eax
  uint32_t v5[7]; // [esp+8h] [ebp-28h]
  int v6; // [esp+2Ch] [ebp-4h]

  v5[0] = "Monster/Soldier/SandorExpeller/SandorExpellerLeg.equ";
  v5[1] = "Monster/Soldier/SandorExpeller/SandorExpellerHead.equ";
  v5[2] = "Monster/Soldier/SandorExpeller/SandorExpellerRightArm.equ";
  v5[3] = "Monster/Soldier/SandorExpeller/SandorExpellerLeftArm.equ";
  v5[4] = "Monster/Soldier/SandorExpeller/SandorExpellerHeadEnd.equ";
  v5[5] = "Monster/Soldier/SandorExpeller/SandorExpellerGlow.equ";
  v1 = 0;
  v2 = this + 2156;
  do
  {
    v3 = (char *)operator new(0x544u);
    v5[6] = v3;
    v6 = 0;
    if ( v3 != nullptr )
      result = sub_4BA9E0(v3, (void *)v5[v1], 0);
    else
      result = nullptr;
    *v2 = result;
    ++v1;
    ++v2;
    v6 = -1;
  }
  while ( v1 < 6 );
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D88C0 sub_5D88C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D88C0(uint32_t *this, char ArgList, int a3)
{
  uint32_t *v4; // eax

  sub_5D6CF0(ArgList, a3);
  *this = &CNExpeller::`vftable';
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  if ( *(this + 96) < 0x10u )
    v4 = this + 91;
  else
    v4 = (uint32_t *)*(this + 91);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
    this,
    v4,
    "Particle/ExpellerBrokenParts.ptl");
  sub_5D83E0(this);
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8970 sub_5D8970
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8970(void *Block, char a2)
{
  sub_5D89A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// 【分区 9】邪眼 EvilEye（0x5D89A0-0x5DC170）
// 证据：EYE_APPEAR/EYE_SHOT/EYE_WRIGGLE、STONE_LASER_READY/STONE_LASER_FIRE（复用石激光）、
//       BEFORE_THUNDER、EVIL_SHOUT/EVIL_DMG、Monster/Common/Particle/MonsterDieSmoke.ptl +
//       PassiveObject/Monster/EvilEye/Particle/MissileGero{Center,CenterLeft,CenterRight,Left,
//       Right}.ptl 五向泪弹、CHASER_LAUNCH/CHASER_EXPLOSION 追击弹

// AI 字段访问
// ------------------------------------------------------------
// 0x5D89A0 sub_5D89A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D89A0(void *this)
{
  *(uint32_t *)this = &CNExpeller::`vftable';
  return sub_5D6E40(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D89B0 sub_5D89B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D89B0(uint32_t *this, char ArgList, int a3, char a4)
{
  sub_5D6CF0(ArgList, a3);
  *this = &CNAxionExpeller::`vftable';
  sub_5D4340(this);
  sub_5D8600(this);
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  if ( a4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A30 sub_5D8A30
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8A30(void *Block, char a2)
{
  sub_5D8A60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A60 sub_5D8A60
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8A60(void *this)
{
  *(uint32_t *)this = &CNAxionExpeller::`vftable';
  return sub_5D6E40(this);
}



// 相位字段（this+8824/8832/8833/8834）
// ------------------------------------------------------------
// 0x5D8A70 sub_5D8A70
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D8A70(uint8_t *this, char ArgList, int a3, char a4)
{
  sub_5D6CF0(ArgList, a3);
  *(uint32_t *)this = &CNTinSwordManExpeller::`vftable';
  *(this + 8824) = 0;
  *((uint32_t *)this + 2205) = &off_6C2B88;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 1;
  *(this + 8834) = 0;
  *(this + 8833) = 0;
  *((uint32_t *)this + 2211) = 0;
  *((uint32_t *)this + 2210) = 0;
  *((uint32_t *)this + 2209) = 0;
  sub_5D4420(this);
  sub_5D10A0(this);
  sub_5D86C0(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( a4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8B40 sub_5D8B40
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8B40(void *Block, char a2)
{
  sub_5D8B70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问（this+8824）
// ------------------------------------------------------------
// 0x5D8B70 sub_5D8B70
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8B70(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &CNTinSwordManExpeller::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 2213) = 0;
  *(this + 2205) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8824) = 0;
  return sub_5D6E40(this);
}



// AI 字段访问（this+8600/8604）
// ------------------------------------------------------------
// 0x5D8BF0 sub_5D8BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8BF0(int this)
{
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8C00 sub_5D8C00
// ------------------------------------------------------------
char /*thiscall*/ sub_5D8C00(uint32_t *this)
{
  if ( sub_4E7F30(this, 300, 0, 0) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
  return sub_4E1780(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8C30 sub_5D8C30
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8C30(uint32_t *this, int a2, int a3, int a4, int a5)
{
  uint32_t *v6; // esi

  if ( a2 == 14 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
    v6 = (uint32_t *)*(this + 28);
    if ( *v6 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 308))(*v6) != 0 && v6[5] != 1065353216 )
    {
      v6[5] = 1065353216;
      *((uint8_t *)v6 + 196) = 1;
    }
  }
}



// AI 相位字段（this+8600/8624）
// ------------------------------------------------------------
// 0x5D8C80 sub_5D8C80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D8C80(uint32_t *this, char ArgList, int a3, char a4)
{
  sub_4A4EA0(ArgList, a3);
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *this = &CNBat::`vftable';
  *((uint8_t *)this + 8600) = 0;
  *(this + 2151) = 0;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *((uint8_t *)this + 8624) = 0;
  if ( a4 == 1 )
  {
    *(this + 1639) = 0;
    *(this + 2151) = -1;
    *((uint8_t *)this + 8600) = 1;
  }
  sub_4D50A0(*(uint32_t *)*(this + 1554));
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D40 sub_5D8D40
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D40(uint32_t *this)
{
  *this = &CNBat::`vftable';
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D50 sub_5D8D50
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D8D50(uint32_t *Block, char a2)
{
  sub_5D8D40(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D80 sub_5D8D80
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D80(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2159);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 2159) = 0;
  return result;
}



// AI 相位字段（this+8600/8604/8628）
// ------------------------------------------------------------
// 0x5D8DA0 sub_5D8DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DA0(int this)
{
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8628) = 5;
  *(uint8_t *)(this + 7144) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8DE0 sub_5D8DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DE0(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2
  int v5; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      v3 = rand();
      v4 = v3 % 100;
      result = v3 / 100;
      if ( v4 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        v5 = rand();
        v6 = v5 % 100;
        result = v5 / 100;
        if ( v6 < 10 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8EC0 sub_5D8EC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8EC0(void *this, int a2)
{
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0 )
    return 0;
  if ( rand() % 100 >= 50 )
    return rand() % a2;
  return -(rand() % a2);
}



// 时钟门 AI（sub_699000, 79L）
// ------------------------------------------------------------
// 0x5D8F10 sub_5D8F10
// ------------------------------------------------------------
int /*usercall*/ sub_5D8F10@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // [esp+4h] [ebp-8h] BYREF
  int v10; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
    if ( result == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 184))(a1, a2);
      (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 188))(a1);
      v4 = a1[1787] - 4;
      v9 = 4;
      v10 = 4;
      switch ( v4 )
      {
        case 0:
          if ( rand() % 100 >= 80 || (uint8_t)sub_4DA6B0(&v9) != 0 )
            goto LABEL_7;
          goto LABEL_6;
        case 1:
        case 5:
LABEL_6:
          sub_4DBDB0(&v9, &v10);
          goto LABEL_7;
        case 9:
          if ( rand() % 100 >= 40 )
          {
LABEL_7:
            v5 = v10;
          }
          else
          {
            if ( (uint8_t)sub_4DA6B0(&v9) == 0 )
              v9 = rand() % 2;
            v5 = rand() % 2 + 2;
            v10 = v5;
          }
          if ( v9 == 4 && v5 == 4 )
            goto LABEL_10;
          v6 = sub_699000((int)(a1 + 9)) + 1000;
          break;
        default:
LABEL_10:
          v6 = sub_699000((int)(a1 + 9)) + 300;
          break;
      }
      v7 = a1[1813];
      a1[1818] = v6;
      v9 = 4;
      if ( v7 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
        (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 124))(a1);
      }
      v8 = a1[1787];
      if ( rand() % 100 < SHIWORD(a1[v8 + 2092]) )
        v10 = 4;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 896))(a1, v9);
      sub_5FDFE0(a1[1932]);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 1080))(a1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D90F0 sub_5D90F0
// ------------------------------------------------------------
int /*userpurge*/ sub_5D90F0@<eax>(uint32_t *a1@<ecx>, int a2@<edi>, int a3, int a4, int a5, int a6, void *Block, int a8)
{
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // eax

  if ( a1[1943] != 3 )
    return sub_4E22E0(a3, a4, a5, a6, Block, a8);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 152))(a1, a2);
  v10 = *a1;
  if ( v9 != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(a1);
    v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v19);
    v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v20);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(a1, v21 + 115);
    sub_4E22E0(a3, a4, a5, a6, Block, a8);
    v22 = *a1;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v23);
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v24);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v22 + 112))(a1, v25 - 115);
  }
  else
  {
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(a1);
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v11);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v12);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(a1, v13 - 115);
    sub_4E22E0(a3, a4, a5, a6, Block, a8);
    v14 = *a1;
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
    v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v15);
    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v16);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v14 + 112))(a1, v17 + 115);
  }
}



// 邪眼现身：EYE_APPEAR 播报（79L；this+204/208/8685/8686 相位）
// ------------------------------------------------------------
// 0x5D9210 sub_5D9210
// ------------------------------------------------------------
char /*thiscall*/ sub_5D9210(int *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // edi
  int v5; // ebx
  int v6; // edi

  v2 = *(this + 2175);
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
        && (unsigned int)(sub_699000((int)(this + 2168)) - *(this + 2176)) > 0x1F4 )
      {
        v3 = *(this + 1813);
        if ( v3 != 0 )
        {
          v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
          v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 128))(*(this + 1813));
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(
            this,
            v4,
            v5,
            0,
            v4,
            v5,
            30303,
            10,
            0,
            4,
            100,
            1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "EYE_APPEAR", -1, 0, 0);
        }
        *(this + 2176) = sub_699000((int)(this + 2168));
      }
      v6 = *(this + 2174);
      v2 = sub_699000((int)(this + 2168));
      if ( v2 >= v6 )
        *(this + 2175) = 2;
    }
    else if ( v2 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      *(this + 2175) = 3;
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 12),
      0,
      0,
      0,
      0);
    *(this + 2175) = 1;
    sub_49C620(3, 1, 5000);
    sub_49C5F0(3, 0, 0, 5000);
    *((uint8_t *)this + 8685) = 0;
    *((uint8_t *)this + 8686) = 0;
    LOBYTE(v2) = sub_698F90((int)(this + 2168), 5000, 0);
    *(this + 2176) = 0;
  }
  return v2;
}



// 邪眼主技能状态机（295L）：STONE_LASER_READY/EYE_SHOT/EYE_APPEAR/BEFORE_THUNDER/
//   STONE_LASER_FIRE 五段播报（sub_699000 时钟门 —— 石激光/落雷/射击三相【推断】）
// ------------------------------------------------------------
// 0x5D93A0 sub_5D93A0
// ------------------------------------------------------------
char /*usercall*/ sub_5D93A0@<al>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // edx
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int64_t v10; // rax
  int v11; // edi
  bool v12; // zf
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int64_t v20; // rax
  int v21; // edi
  int v22; // edi
  uint32_t *v23; // edi
  int v25; // [esp-2Ch] [ebp-30h]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
  v5 = *a1;
  if ( v4 == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 840))(a1) == 17 )
      goto LABEL_6;
    v6 = (uint32_t *)(a1[1554] + 12);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v5 + 208))(a1, *(uint32_t *)(a1[1554] + 4));
    v6 = (uint32_t *)(a1[1554] + 20);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 208))(a1, *v6);
LABEL_6:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 8 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 908))(a1);
    v8 = *a1;
    if ( v7 == 1 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v8 + 200))(a1) + 148) >= 3 && *((uint8_t *)a1 + 8600) == 1 )
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 152))(a1, a3, a2);
        if ( v9 != 0 )
        {
          v11 = sub_425050(*(uint32_t *)(*(uint32_t *)(a1[29] + 132) + 44));
          v10 = 1374389535LL * (v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1));
        }
        else
        {
          v10 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1);
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t))(*a1 + 580))(
          a1,
          48029,
          (SHIDWORD(v10) >> 5) + (HIDWORD(v10) >> 31),
          0,
          0,
          85,
          0,
          107,
          v9,
          0);
        *((uint8_t *)a1 + 8600) = 0;
        sub_432EA0("STONE_LASER_READY", -1, 0, 0);
      }
      else if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 148) >= 8
             && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 568))(a1) != 14 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 14, 0, 0, 0);
      }
    }
    else
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 908))(a1) == 2;
      v13 = *a1;
      if ( v12 )
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v13 + 200))(a1) + 148) >= 5 && *((uint8_t *)a1 + 8600) == 1 )
        {
          v14 = *a1;
          v25 = a1[2177];
          *((uint8_t *)a1 + 8600) = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v14 + 580))(
            a1,
            30302,
            0,
            v25,
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
            a1,
            30302,
            0,
            a1[2178],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
            a1,
            30302,
            0,
            a1[2179],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
            a1,
            30302,
            0,
            a1[2180],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
            a1,
            30302,
            0,
            a1[2181],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "EYE_SHOT", -1, 0, 0);
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v13 + 908))(a1) == 3 )
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 148) >= 5 && *((uint8_t *)a1 + 8600) == 1 )
        {
          v15 = a1[1813];
          *((uint8_t *)a1 + 8600) = 0;
          if ( v15 != 0 )
          {
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 120))(v15);
            v17 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[1813] + 124))(a1[1813]);
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[1813] + 128))(a1[1813]);
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 584))(
              a1,
              v16,
              v17,
              0,
              v16,
              v17,
              30303,
              10,
              0,
              4,
              100,
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(
              a1,
              "EYE_APPEAR",
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(
              a1,
              "BEFORE_THUNDER",
              -1,
              0,
              0);
          }
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 908))(a1) == 0
             && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 148) >= 5
             && *((uint8_t *)a1 + 8600) == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
          a1,
          30305,
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
        *((uint8_t *)a1 + 8600) = 0;
      }
    }
  }
  else
  {
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 14;
    v18 = *a1;
    if ( v12 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v18 + 200))(a1) + 148) >= 0 && *((uint8_t *)a1 + 8600) == 1 )
      {
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 152))(a1, a3, a2);
        if ( v19 != 0 )
        {
          v21 = sub_425050(*(uint32_t *)(*(uint32_t *)(a1[29] + 132) + 44));
          v20 = 1374389535LL * (v21 - (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1));
        }
        else
        {
          v20 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1);
        }
        v22 = (SHIDWORD(v20) >> 5) + (HIDWORD(v20) >> 31);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 212))(a1, "STONE_LASER_FIRE", -1);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
          a1,
          30301,
          v22,
          0,
          0,
          85,
          0,
          107,
          v19,
          0,
          0,
          0);
        *((uint8_t *)a1 + 8600) = 0;
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 170) != 0
        && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 568))(a1) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 0, 0, 0, 0);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v18 + 840))(a1) == 17 )
    {
      sub_5D9210(a1);
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 9 && a1[2151] == 1 )
    {
      v23 = (uint32_t *)(a1[1554] + 8);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) != *v23 )
      {
        sub_4926A0(*(uint32_t *)(a1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 8));
      }
      if ( (unsigned int)(sub_699000((int)(a1 + 9)) - a1[2156]) > 0xFA0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t *, uint32_t, uint32_t))(*a1 + 560))(a1, 5, a1 + 2152, 0, 0);
        a1[2151] = 2;
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 8 || (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) >= 14 )
  {
    sub_4D9360(a1);
    return sub_4E1780(a1);
  }
  else
  {
    sub_4D93D0(a1);
    return sub_4E1780(a1);
  }
}


// 时钟门+插值 AI（sub_699000+sub_4049C0; this+200）
// ------------------------------------------------------------
// 0x5D9950 sub_5D9950
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9950(uint32_t *this, int a2, int a3, int a4, int a5)
{
  unsigned int v6; // eax
  uint64_t v7; // rax
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // edi
  int v14; // edi
  int v15; // eax
  void *v16; // ecx
  uint32_t *v17; // edi
  int v19; // [esp-8h] [ebp-50h]
  int v20; // [esp-8h] [ebp-50h]
  int v21; // [esp-4h] [ebp-4Ch]
  float v22; // [esp+Ch] [ebp-3Ch] BYREF
  float v23; // [esp+10h] [ebp-38h]
  float v24; // [esp+14h] [ebp-34h]
  int v25; // [esp+18h] [ebp-30h]
  int v26; // [esp+1Ch] [ebp-2Ch]
  int v27; // [esp+20h] [ebp-28h]
  uint8_t v28[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  uint32_t *v30; // [esp+2Ch] [ebp-1Ch]
  int v31; // [esp+30h] [ebp-18h]
  int v32; // [esp+34h] [ebp-14h]
  int v33; // [esp+38h] [ebp-10h] BYREF
  int v34; // [esp+44h] [ebp-4h]

  if ( (uint8_t)a2 == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 9 )
    {
      v6 = sub_699000((int)(this + 9)) - *(this + 2156);
      if ( v6 >= 0x3E8 )
        LOBYTE(v7) = 0;
      else
        v7 = (uint64_t)sub_4049C0(255.0, 0.0, v6, 1000);
      v19 = ((uint8_t)v7 << 24) | 0xFFFFFF;
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      sub_491690(1, 5, 1, -1, v19, 1);
      if ( (int)*(this + 2157) <= 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 1 ? -50 : 50;
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2159) + 40))(*(this + 2159), v14, v15, 60);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2159) + 92))(*(this + 2159), v28);
        v16 = (void *)*(this + 29);
        v34 = 0;
        sub_4600B0(v16, 2, 0, (int)v28);
        v17 = Block;
        if ( Block != v30 )
        {
          do
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v17 + 200))(*v17);
            *(uint32_t *)(sub_4924C0(0) + 48) = *(this + 2160);
            ++v17;
          }
          while ( v17 != v30 );
          v17 = Block;
        }
        v34 = -1;
        if ( v17 != nullptr )
          j__free(v17);
        Block = nullptr;
        v30 = nullptr;
        v31 = 0;
      }
      else if ( (unsigned int)(sub_699000((int)(this + 9)) - *(this + 2158)) > 0x12C )
      {
        v33 = 0;
        v22 = 0.0;
        v23 = 0.0;
        v24 = 0.0;
        v25 = 0;
        v26 = 0;
        v27 = 0;
        v8 = sub_5D8EC0(this, 100);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        v10 = *this;
        v32 = v9 + v8;
        v22 = (float)(v9 + v8);
        v32 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(this);
        v23 = (float)v32;
        v11 = sub_5D8EC0(this, 50);
        v32 = v11 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 50;
        v24 = (float)v32;
        v21 = sub_605840(&v33, this, &v22, 1);
        v20 = v33;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
        sub_4E4A50(this, 42005, 1, 0, 0, 0, v12, 0, v20, v21);
        *(this + 2158) = sub_699000((int)(this + 9));
        --*(this + 2157);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 9
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      sub_491690(1, 5, 1, -1, -1, 1);
    }
  }
  return sub_4D8F90(a2, a3, a4, a5);
}



// 复合门（114L；this+612/616 反应态 + 8600/8657/8658 —— 反应态空闲门样本, 研究 15）
// ------------------------------------------------------------
// 0x5D9BF0 sub_5D9BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9BF0(uint32_t *this, int ArgList, int a3, int a4, int a5)
{
  char v5; // di
  int v7; // edx
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // ebx

  v5 = ArgList;
  switch ( ArgList )
  {
    case 5:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        *(this + 2151) = 2;
      if ( *(this + 2151) == 0 )
      {
        *(this + 2151) = 1;
        LOBYTE(ArgList) = 9;
        sub_4ED3F0((int)(this + 2152), a3);
        *(this + 2156) = sub_699000((int)(this + 9));
        v5 = 9;
        *(this + 2158) = sub_699000((int)(this + 9));
      }
      break;
    case 8:
      *((uint8_t *)this + 8600) = 1;
      v7 = *this;
      v8 = *(this + 1554);
      if ( **(uint32_t **)(a3 + 4) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          this,
          1,
          *(uint32_t *)(v8 + 4),
          0,
          0,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          this,
          1,
          *(uint32_t *)(v8 + 20),
          0,
          0,
          0,
          0);
      break;
    case 14:
      v9 = (uint32_t *)*(this + 1554);
      v10 = *this;
      *((uint8_t *)this + 8600) = 1;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v10 + 196))(this, *v9);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 612))(this, 1, 1);
      break;
    case 17:
      *(this + 2175) = 0;
      *((uint8_t *)this + 8657) = 0;
      *((uint8_t *)this + 8658) = 0;
      sub_698F90((int)(this + 2161), 30000, 0);
      break;
    default:
      break;
  }
  v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v11 != 0 )
  {
    if ( v11 == 14 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
  }
  else
  {
    v12 = *(this + 2167);
    if ( sub_699000((int)(this + 2161)) >= v12 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
      *(this + 2175) = 0;
      *((uint8_t *)this + 8657) = 0;
      *((uint8_t *)this + 8658) = 0;
      sub_698F90((int)(this + 2161), 30000, 0);
    }
    v5 = ArgList;
  }
  return sub_4E33D0(v5, *(float *)&a3, a4, a5);
}



// 邪眼死亡演出：Monster/Common/Particle/MonsterDieSmoke.ptl + PassiveObject/Monster/
//   EvilEye/Particle/MissileGero{Center,CenterLeft,CenterRight,Left,Right}.ptl 五向泪弹（58L）
// ------------------------------------------------------------
// 0x5D9DA0 sub_5D9DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9DA0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int v4; // edi
  int v5; // ebx
  uint64_t v6; // rax
  int v7; // ebx
  uint64_t v8; // rax
  uint64_t v9; // rax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  int v12; // [esp+10h] [ebp-10h]

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"Monster/Common/Particle/MonsterDieSmoke.ptl", 0);
  else
    v3 = nullptr;
  *(this + 2159) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3);
  v4 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2159) + 36))(*(this + 2159));
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = sub_41A5E0(v5 + 984);
  v6 = (uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v5 + 998)));
  *(float *)v4 = sub_4049C0(20.0, 60.0, (int)v6 - 30000, 140000);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  Block = (void *)sub_41A5E0(v7 + 984);
  v8 = (uint64_t)((double)(int)Block * COERCE_FLOAT(sub_41A5E0(v7 + 998)));
  v9 = (uint64_t)sub_4049C0(50.0, 150.0, (int)v8 - 30000, 140000);
  *(uint32_t *)(v4 + 12) = v9;
  *(uint32_t *)(v4 + 16) = 2 * v9;
  *(uint32_t *)(v4 + 20) = v9;
  *(this + 2160) = 3000;
  *(this + 2177) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenter.ptl");
  *(this + 2178) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterLeft.ptl");
  *(this + 2179) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterRight.ptl");
  *(this + 2180) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroLeft.ptl");
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
             dword_8F84E4,
             "PassiveObject/Monster/EvilEye/Particle/MissileGeroRight.ptl");
  *(this + 2181) = result;
  return result;
}



// 邪眼语音：EVIL_SHOUT + EVIL_DMG + EYE_WRIGGLE 蠕动（57L；this+8600..8664 相位）
// ------------------------------------------------------------
// 0x5D9F50 sub_5D9F50
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9F50(int this, char ArgList, int a3)
{
  char v5; // [esp-24h] [ebp-3Ch]
  void *v6; // [esp-20h] [ebp-38h]
  int v7; // [esp-1Ch] [ebp-34h]
  int v8; // [esp-18h] [ebp-30h]
  int v9; // [esp-14h] [ebp-2Ch]

  sub_4A4EA0(ArgList, a3);
  *(uint32_t *)this = &CNEvilEye::`vftable';
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = &off_6C2B88;
  *(uint32_t *)(this + 8652) = 0;
  *(uint8_t *)(this + 8656) = 1;
  *(uint8_t *)(this + 8658) = 0;
  *(uint8_t *)(this + 8657) = 0;
  *(uint32_t *)(this + 8668) = 0;
  *(uint32_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8660) = 0;
  *(uint8_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8672) = &off_6C2B88;
  *(uint32_t *)(this + 8680) = 0;
  *(uint8_t *)(this + 8684) = 1;
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8628) = 5;
  *(uint8_t *)(this + 7144) = 0;
  sub_5D9DA0((uint32_t *)this);
  *(uint8_t *)(this + 8657) = 0;
  *(uint8_t *)(this + 8658) = 0;
  sub_4015C0("EVIL_SHOUT", 0xAu);
  sub_4015C0("EVIL_SHOUT", 0xAu);
  sub_4015C0("EVIL_DMG", 8u);
  LOBYTE(v6) = 0;
  sub_4015C0("EYE_WRIGGLE", 0xBu);
  sub_4DE5E0(v5, v6, v7, v8, v9, 0, 15, 5000, 10000);
  return this;
}



// AI 字段访问（this+8648/8676）
// ------------------------------------------------------------
// 0x5DA0E0 sub_5DA0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA0E0(void *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNEvilEye::`vftable';
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2159);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *((uint32_t *)this + 2159) = 0;
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8676) = 0;
  *((uint32_t *)this + 2161) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8648) = 0;
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA190 sub_5DA190
// ------------------------------------------------------------
void */*thiscall*/ sub_5DA190(void *Block, char a2)
{
  sub_5DA0E0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1C0 sub_5DA1C0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_5DA1C0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 2093);
  return v1 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v1 + 80))() != 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1E0 sub_5DA1E0
// ------------------------------------------------------------
int /*cdecl*/ sub_5DA1E0(int a1)
{
  if ( a1 >= 55 )
    return 4;
  else
    return dword_738048[a1];
}



// 邪眼相位字段大区（this+8216..8308, 112L —— 邪眼专用 82xx 字段块）
// ------------------------------------------------------------
// 0x5DA220 sub_5DA220
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA220(int this)
{
  int result; // eax
  uint32_t *v2; // esi
  uint32_t *v3; // edx
  int i; // [esp+Ch] [ebp-4h]

  result = 0;
  *(uint32_t *)(this + 8216) = -1;
  *(uint8_t *)(this + 8220) = 0;
  *(uint32_t *)(this + 8224) = 0;
  *(uint8_t *)(this + 8228) = 0;
  *(uint32_t *)(this + 8232) = 0;
  *(uint32_t *)(this + 8236) = 0;
  *(uint32_t *)(this + 8240) = 0;
  *(uint32_t *)(this + 8244) = 5;
  *(uint32_t *)(this + 8248) = 0;
  *(uint32_t *)(this + 8252) = 4;
  *(uint32_t *)(this + 8256) = 0;
  v2 = (uint32_t *)(this + 8276);
  v3 = (uint32_t *)(this + 8260);
  for ( i = 4; i != 0; --i )
  {
    *v3 = -1;
    *v2 = 0;
    v2[1] = 0;
    ++v3;
    v2 += 2;
  }
  *(uint32_t *)(this + 8308) = 0;
  *(uint32_t *)(this + 8328) = 0;
  *(uint32_t *)(this + 8348) = 0;
  *(uint32_t *)(this + 8312) = 0;
  *(uint32_t *)(this + 8332) = 0;
  *(uint32_t *)(this + 8352) = 0;
  *(uint32_t *)(this + 8316) = 0;
  *(uint32_t *)(this + 8336) = 0;
  *(uint32_t *)(this + 8356) = 0;
  *(uint32_t *)(this + 8320) = 0;
  *(uint32_t *)(this + 8340) = 0;
  *(uint32_t *)(this + 8360) = 0;
  *(uint32_t *)(this + 8324) = 0;
  *(uint32_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8364) = 0;
  *(uint8_t *)(this + 8368) = 0;
  *(uint32_t *)(this + 8372) = 0;
  *(uint8_t *)(this + 8376) = 0;
  *(uint32_t *)(this + 8380) = 0;
  *(uint32_t *)(this + 8384) = 0;
  *(uint32_t *)(this + 8392) = 100;
  *(uint32_t *)(this + 8396) = 0;
  *(uint8_t *)(this + 8404) = 0;
  *(uint32_t *)(this + 8400) = -1;
  *(uint32_t *)(this + 8388) = 1065353216;
  *(uint32_t *)(this + 8408) = 0;
  *(uint32_t *)(this + 8416) = 0;
  *(uint32_t *)(this + 8424) = 0;
  *(uint32_t *)(this + 8432) = 0;
  *(uint32_t *)(this + 8412) = 0;
  *(uint32_t *)(this + 8420) = 0;
  *(uint32_t *)(this + 8428) = 0;
  *(uint32_t *)(this + 8436) = 0;
  *(uint32_t *)(this + 8440) = 0;
  *(uint32_t *)(this + 8444) = -1;
  *(uint32_t *)(this + 8448) = 0;
  *(uint32_t *)(this + 8452) = 0;
  *(uint32_t *)(this + 8456) = 0;
  *(uint32_t *)(this + 8460) = 0;
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;
  *(uint32_t *)(this + 8472) = 0;
  *(uint32_t *)(this + 8476) = 0;
  *(uint32_t *)(this + 8480) = 0;
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 1065353216;
  *(uint32_t *)(this + 8492) = 0;
  *(uint32_t *)(this + 8496) = -1;
  *(uint32_t *)(this + 8500) = 0;
  *(uint8_t *)(this + 8504) = 0;
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 4;
  *(uint32_t *)(this + 8516) = -1;
  *(uint8_t *)(this + 8520) = 0;
  *(uint32_t *)(this + 8524) = 0;
  *(uint32_t *)(this + 8528) = 4;
  *(uint32_t *)(this + 8532) = 0;
  *(uint32_t *)(this + 8536) = -1;
  *(uint32_t *)(this + 8540) = 0;
  *(uint32_t *)(this + 8544) = 0;
  *(uint32_t *)(this + 8548) = 0;
  *(uint32_t *)(this + 8552) = 0;
  *(uint32_t *)(this + 8556) = 0;
  *(uint32_t *)(this + 8560) = 0;
  *(uint32_t *)(this + 8564) = 0;
  *(uint32_t *)(this + 8568) = -1;
  *(uint32_t *)(this + 8572) = 0;
  *(uint32_t *)(this + 8576) = 0;
  *(uint32_t *)(this + 8580) = 0;
  *(uint8_t *)(this + 8584) = 0;
  *(uint8_t *)(this + 8585) = 0;
  *(uint32_t *)(this + 8588) = 0;
  *(uint32_t *)(this + 8592) = -1;
  *(uint32_t *)(this + 8596) = -1;
  *(uint8_t *)(this + 8628) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA490 sub_5DA490
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA490(uint32_t *this)
{
  sub_4B32E0();
  *(this + 2148) = -1;
  *(this + 2149) = -1;
  return -1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA4B0 sub_5DA4B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4B0(uint32_t *this)
{
  int result; // eax

  result = sub_4B1670();
  *(this + 2061) = 5;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA4D0 sub_5DA4D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4D0(float *this, int a2, int a3, int a4)
{
  unsigned int v5; // edi
  int v6; // edx
  float v8; // [esp+4h] [ebp-8h]
  int v9; // [esp+4h] [ebp-8h]

  if ( *(this + 2056) != 0.0 )
  {
    v8 = *(this + 2056);
    v5 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3) + 1026;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v5)) - v8;
    sub_41A590(v5, v6, v9);
    *(this + 2056) = 0.0;
  }
  return sub_4D4A20(this, a2, a3, a4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA550 sub_5DA550
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA550(float *this, int a2, int a3, int a4)
{
  int v4; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  float v13; // [esp+20h] [ebp-20h]
  float v14; // [esp+20h] [ebp-20h]
  float v15; // [esp+20h] [ebp-20h]
  float v16; // [esp+20h] [ebp-20h]
  int v17; // [esp+30h] [ebp-10h] BYREF
  float v18; // [esp+34h] [ebp-Ch]
  int v19; // [esp+38h] [ebp-8h] BYREF
  int v20; // [esp+3Ch] [ebp-4h]

  v4 = a2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 736))(this);
  v6 = *((uint32_t *)this + 2095);
  if ( v6 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6) != 0
    && (uint8_t)a4 == 0
    && (unsigned int)sub_4AED20((int)this) <= 1 )
  {
    v7 = *(uint32_t *)this;
    v19 = 100;
    (*(void (/*thiscall*/ **)(float *, int *, int))(v7 + 648))(this, &v19, v4);
    v8 = *(uint32_t *)this;
    HIBYTE(a2) = 0;
    v17 = 0;
    v18 = (float)(*(int (/*thiscall*/ **)(float *, char *, int *, int, int, int, uint32_t))(v8 + 628))(
                   this,
                   (char *)&a2 + 3,
                   &v17,
                   v19,
                   v4,
                   a3,
                   0);
    v13 = (double)*((int *)this + 2096) * v18 * 0.0099999998;
    v20 = sub_432F40(v13);
    v14 = (double)v20 * *(this + 2097);
    v9 = sub_432F40(v14);
    if ( v9 > (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this) )
    {
      v9 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this);
      v20 = v9;
      v15 = (double)v9 / *(this + 2097);
      v20 = sub_432F40(v15);
      v16 = 100.0 - (double)v20 * 100.0 / v18;
      v10 = sub_432F40(v16);
    }
    else
    {
      v10 = 100 - *((uint32_t *)this + 2096);
    }
    *((uint32_t *)this + 2098) = v10;
    if ( v9 != 0 )
    {
      v18 = *this;
      v11 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 752))(this, 1);
      (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 744))(this, v11 - v9);
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 2095) + 120))(*((uint32_t *)this + 2095));
    }
  }
  return sub_4AFB80(v4, a3, a4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA6D0 sub_5DA6D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA6D0(uint32_t *this, int a2, int a3, int a4)
{
  *(this + 2098) = 100;
  return sub_4AFC30(a2, a3, a4);
}



// AI 字段访问（this+8584）
// ------------------------------------------------------------
// 0x5DA6F0 sub_5DA6F0
// ------------------------------------------------------------
char /*thiscall*/ sub_5DA6F0(uint32_t *this)
{
  int v2; // eax
  float v4; // [esp+0h] [ebp-8h]

  LOBYTE(v2) = sub_4D54E0(this);
  if ( *(this + 1639) == 10 )
  {
    v2 = *(this + 1953);
    if ( v2 == 0 && *(this + 1954) == 15 )
    {
      LOBYTE(v2) = *((uint8_t *)this + 8584);
      if ( (uint8_t)v2 != 0 )
      {
        v4 = (double)dword_9B9344 * 0.017444445;
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 272))(this, 1, LODWORD(v4));
      }
    }
  }
  return v2;
}



// 数据表读数（sub_47EF20, 41L）
// ------------------------------------------------------------
// 0x5DA740 sub_5DA740
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA740(int *this, int *a2, int a3)
{
  int result; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // [esp-Ch] [ebp-18h]

  result = sub_4AFBF0(a2, a3);
  v5 = result;
  if ( result != 3 )
  {
    v6 = *(this + 2095);
    if ( v6 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v6 + 80))() != 0 )
    {
      v7 = *a2;
      if ( *a2 >= *(this + 2098) )
        v7 = *(this + 2098);
      *a2 = v7;
    }
    if ( *(this + 2142) != -1 )
    {
      v8 = *(this + 1639);
      if ( v8 == 0 || v8 == 11 )
      {
        v9 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 38, -1);
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
        *a2 = (sub_47EF20(38, 1, v9, -1, 11) + 1000) * *a2 / 1000;
      }
    }
    return v5;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA7F0 sub_5DA7F0
// ------------------------------------------------------------
int /*userpurge*/ sub_5DA7F0@<eax>(uint8_t *a1@<ecx>, char a2@<bl>, char a3)
{
  int result; // eax
  char v5; // bl
  int v6; // eax
  bool v7; // al
  char v9; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    if ( a1[7730] != 0 )
    {
      v5 = a3;
    }
    else
    {
      v5 = 0;
      a3 = 0;
    }
    v6 = sub_4AFD50(a3);
    LOBYTE(v6) = v5 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 32)) > 0;
    (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)a1 + 1160))(a1, 11, v6);
    sub_47E440(a2);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 33);
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 1160))(a1);
    sub_47E440(14);
    v7 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 34) > 0;
    v9 = v7;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 12);
    return sub_47E440(v9);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8D0 sub_5DA8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8D0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8E0 sub_5DA8E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8E0(uint32_t *this, uint32_t *a2)
{
  int result; // eax

  result = sub_4B0530(a2);
  if ( a2 == (uint32_t *)*(this + 2110) )
    *(this + 2110) = 0;
  if ( a2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA920 sub_5DA920
// ------------------------------------------------------------
int /*stdcall*/ sub_5DA920(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 6:
      result = 0;
      break;
    case 7:
      result = 1;
      break;
    case 8:
      result = 2;
      break;
    case 9:
      result = 3;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA980 sub_5DA980
// ------------------------------------------------------------
int /*cdecl*/ sub_5DA980(int a1)
{
  int v1; // eax

  v1 = 0;
  while ( a1 != dword_738020[v1] )
  {
    if ( ++v1 >= 4 )
      return -1;
  }
  return dword_738030[v1];
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA9B0 sub_5DA9B0
// ------------------------------------------------------------
char /*stdcall*/ sub_5DA9B0(int a1)
{
  uint32_t *v1; // eax

  v1 = &unk_737FFC;
  while ( a1 != *v1 )
  {
    if ( (int)++v1 >= (int)dword_738020 )
      return 0;
  }
  return 1;
}



// 时钟门+数据表 AI（sub_699000+sub_47EF20, 46L）
// ------------------------------------------------------------
// 0x5DA9E0 sub_5DA9E0
// ------------------------------------------------------------
void /*thiscall*/ sub_5DA9E0(int *this, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // ecx
  int *v8; // esi
  int i; // edi
  int v10; // [esp-14h] [ebp-18h]

  v3 = *(this + 2062);
  if ( v3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3) != 0 )
  {
    v4 = *(this + 2063);
    if ( v4 != a2 )
    {
      if ( v4 != 4 )
      {
        v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 29, -1);
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
        v5 = sub_47EF20(29, 1, v10, -1, 11);
        v6 = sub_699000((int)(this + 9));
        v7 = *(this + a2 + 2087);
        *(this + a2 + 2065) = v5 + v6;
        sub_4926A0(v7);
        sub_4926A0(*(this + a2 + 2082));
        if ( a2 == 2 )
        {
          sub_4926A0(*(this + 2091));
          sub_4926A0(*(this + 2086));
        }
      }
      *(this + 2063) = a2;
      v8 = this + 2 * a2 + 2069;
      for ( i = 2; i != 0; --i )
        sub_4926A0(*v8++);
    }
  }
}



// 时钟门 AI（sub_699000, 79L）
// ------------------------------------------------------------
// 0x5DAAC0 sub_5DAAC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAAC0(int *this, char a2, int a3, int a4, int a5)
{
  int result; // eax
  int i; // edi
  int j; // ebx
  int v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // [esp+4h] [ebp-4h]

  result = *(this + 2062);
  if ( result != 0 )
  {
    result = (*(int (**)(void))(*(uint32_t *)result + 80))();
    if ( (uint8_t)result != 0 )
    {
      if ( a2 != 0 && *(this + 2063) != 4 )
      {
        for ( i = 0; i < 2; ++i )
        {
          sub_4938F0(*(this + 2 * *(this + 2063) + i + 2069));
          sub_491D00(dword_79C0B0, a3, a4 - *(this + 40), 0.0);
        }
      }
      for ( j = 0; j < 5; ++j )
      {
        if ( j == 4 )
        {
          result = 2;
          v12 = 2;
        }
        else
        {
          v12 = j;
          result = j;
        }
        if ( byte_737FF4[result] != a2 )
          continue;
        v9 = *(this + result + 2065);
        if ( v9 == -1 )
        {
          v10 = *(this + j + 2077);
          if ( *(uint8_t *)(v10 + 170) != 0 )
            goto LABEL_17;
        }
        else
        {
          if ( sub_699000((int)(this + 9)) >= v9 )
          {
            v10 = *(this + j + 2087);
            if ( *(uint8_t *)(v10 + 170) == 0 )
            {
              if ( *(int *)(v10 + 148) < 3 )
              {
                v11 = sub_491C70(v10, 3);
                sub_493A60(v10, v11);
              }
              goto LABEL_18;
            }
LABEL_17:
            v10 = *(this + j + 2082);
            goto LABEL_18;
          }
          v10 = *(this + j + 2087);
        }
LABEL_18:
        sub_4938F0(v10);
        result = sub_491D00(dword_79C0B0, a3 + dword_737FD4[v12], a4 + dword_737FE4[v12], 0.0);
      }
    }
  }
  return result;
}



// 时钟门+数据表 AI（sub_699000+sub_47EF20, 45L）
// ------------------------------------------------------------
// 0x5DAC20 sub_5DAC20
// ------------------------------------------------------------
void /*usercall*/ sub_5DAC20(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // ecx
  int v5; // ebx
  int *v6; // edi
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v12; // [esp+14h] [ebp-8h]
  float v13; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  v4 = a1[2062];
  if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) != 0 )
  {
    v5 = 0;
    v6 = a1 + 2065;
    for ( i = 4; i != 0; --i )
    {
      if ( *v6 != -1 && sub_699000((int)(a1 + 9)) < *v6 )
        ++v5;
      ++v6;
    }
    if ( v5 != a1[2064] )
    {
      v7 = a1[2062];
      a1[2064] = v5;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
      if ( v5 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 1140))(a1, 29, -1);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*a1 + 1160))(a1, 29, v5 + 1, v8);
        v9 = sub_47EF20(-1, 11, a3, a2, v12);
        v13 = (float)v9;
        (*(void (/*cdecl*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)a1[2062] + 120))(1, 0, LODWORD(v13), v9);
      }
    }
  }
}



// 数据表+变速换锚 AI（sub_47EF20+sub_493D00, 39L）
// ------------------------------------------------------------
// 0x5DACE0 sub_5DACE0
// ------------------------------------------------------------
void /*usercall*/ sub_5DACE0(uint32_t *a1@<ecx>, int a2@<edi>)
{
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int *v8; // esi
  int i; // edi

  if ( a1[2142] != -1 )
  {
    v3 = a1[1639];
    if ( v3 == 0 || v3 == 11 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 1140))(a1);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*a1 + 1160))(a1, 38, 0, v4);
      v5 = sub_47EF20(38, -1, -1, 11, a2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*a1 + 888))(a1, 0, 0, v5 * a1[1663] / 1000);
      v6 = a1[2142];
      if ( v6 >= 55 )
        v7 = 4;
      else
        v7 = dword_738048[v6];
      v8 = &a1[2 * v7 + 2043];
      for ( i = 2; i != 0; --i )
      {
        sub_493D00(*(v8 - 10), 100.0);
        sub_493D00(*v8++, 100.0);
      }
    }
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DADE0 sub_5DADE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DADE0(uint8_t *this, int a2)
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);
  v3 = *(uint32_t *)this;
  *(this + 8628) = 0;
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v3 + 212))(this, a2, 11, 0, 0);
  *((uint32_t *)this + 2148) = dword_79D100[0];
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAE20 sub_5DAE20
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAE20(int *this, int a2)
{
  int v2; // esi
  int v3; // ecx
  int result; // eax

  *(uint32_t *)(*(this + 1) + *(this + 2)) = a2;
  v2 = *(this + 2) + 4;
  *(this + 2) = v2;
  v3 = *this;
  result = v2;
  if ( v2 > v3 )
    return off_77F3FC(aCriticalError_40, v3);
  return result;
}



// 追击弹发射：CHASER_LAUNCH 播报（14L）
// ------------------------------------------------------------
// 0x5DAE60 sub_5DAE60
// ------------------------------------------------------------
void /*thiscall*/ sub_5DAE60(int *this, int a2, int a3)
{
  sub_4AFDB0((uint8_t **)this, a2, a3);
  if ( a2 < 55 && dword_738048[a2] != 4 )
    sub_5DA9E0(this, dword_738048[a2]);
  if ( a2 == 39 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CHASER_LAUNCH", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAEB0 sub_5DAEB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAEB0(int *this, int a2, int a3, int a4, int a5)
{
  if ( (uint8_t)a2 != 0 )
  {
    sub_4B1E50(a2, a3, a4, a5);
    return sub_5DAAC0(this, a2, a3, a4, a5);
  }
  else
  {
    sub_5DAAC0(this, 0, a3, a4, a5);
    return sub_4B1E50(0, a3, a4, a5);
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DAF10 sub_5DAF10
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAF10(int *this)
{
  int result; // eax
  uint32_t *v3; // eax

  result = *(this + 2149);
  if ( result != -1 && dword_79D100[0] >= result )
  {
    if ( *((uint8_t *)this + 8628) != 0 )
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);
    if ( (unsigned int)*(this + 2156) < 0x10 )
      v3 = this + 2151;
    else
      v3 = (uint32_t *)*(this + 2151);
    result = (*(int (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v3, -1, 0, 0);
    *(this + 2149) = -1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAF70 sub_5DAF70
// ------------------------------------------------------------
void */*cdecl*/ sub_5DAF70(void *Src, int a2, int a3)
{
  return memcpy_0((void *)(a3 - 4 * ((a2 - (int)Src) >> 2)), Src, 4 * ((a2 - (int)Src) >> 2));
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAFA0 sub_5DAFA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DAFA0(uint32_t *this, char a2, int a3)
{
  sub_4B1030();
  *this = &CNWhipped::`vftable';
  sub_64D880(this);
  sub_64DC00((int)this, a2, a3);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB000 sub_5DB000
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB000(void *Block, char a2)
{
  sub_5DB030();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB030 sub_5DB030
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB030(uint32_t *this)
{
  int result; // eax

  *this = &CNWhipped::`vftable';
  sub_6509F0();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB090 sub_5DB090
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB090(uint32_t *this, int a2)
{
  sub_4B1030();
  *this = &CNFollowMe::`vftable';
  sub_64D910(this);
  sub_64D940((int)this, a2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB0F0 sub_5DB0F0
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB0F0(void *Block, char a2)
{
  sub_5DB120();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB120 sub_5DB120
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB120(uint32_t *this)
{
  int result; // eax

  *this = &CNFollowMe::`vftable';
  sub_64E920();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB180 sub_5DB180
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB180(uint32_t *this)
{
  sub_4B1030();
  *this = &CNAuraShield::`vftable';
  sub_6509D0(this);
  sub_64ED00(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB1D0 sub_5DB1D0
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB1D0(void *Block, char a2)
{
  sub_5DB200();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB200 sub_5DB200
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB200(uint32_t *this)
{
  int result; // eax

  *this = &CNAuraShield::`vftable';
  sub_64EE40();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB260 sub_5DB260
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB260(void *this, void *Block)
{
  uint32_t *v3; // edi
  uint32_t *v4; // eax
  int v5; // eax

  if ( Block != nullptr )
  {
    v3 = operator new(0x7Cu);
    v4 = nullptr;
    if ( v3 != nullptr )
    {
      v5 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 30);
      v4 = sub_5DB090(v3, v5);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, int, int))(*v4 + 56))(
      v4,
      Block,
      this,
      0,
      0,
      12,
      -1);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB2E0 sub_5DB2E0
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB2E0(uint32_t *this, void *Block)
{
  int v3; // eax

  nullsub_1(Block);
  v3 = *(this + 2093);
  if ( v3 != 0
    && (*(uint8_t (**)(void))(*(uint32_t *)v3 + 80))() != 0
    && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529) != 0
    && *((uint32_t **)Block + 2088) == this )
  {
    sub_5DB260(this, Block);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB330 sub_5DB330
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB330(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = (uint32_t *)sub_5648C0(*(this + 1), a3, *(this + 1), a2 + 3, *((uint8_t *)a2 + 20));
    if ( *((uint8_t *)Block + 21) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_5DB330(v6, v4);
    v4[2] = sub_5DB330(a2[2], v4);
  }
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB3E0 sub_5DB3E0
// ------------------------------------------------------------
int sub_5DB3E0()
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(3, 3);
  dword_795850 = sub_47E9D0(v0, 1u);
  dword_795854 = dword_795850 * dword_7930D4[0] / 100;
  v1 = (uint32_t *)sub_47E720(3, 14);
  dword_9B9338 = sub_47E9D0(v1, 0);
  v2 = (uint32_t *)sub_47E720(3, 14);
  dword_9B933C = sub_47E9D0(v2, 1u);
  v3 = (uint32_t *)sub_47E720(3, 14);
  dword_9B9340 = sub_47E9D0(v3, 2u);
  v4 = (uint32_t *)sub_47E720(3, 42);
  result = sub_47E9D0(v4, 3u);
  dword_9B9344 = result;
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5DB490 sub_5DB490
// ------------------------------------------------------------
char /*thiscall*/ sub_5DB490(uint32_t *this)
{
  uint32_t *v1; // edx
  int v2; // eax
  int v4; // ecx
  int v5; // ebx
  unsigned int v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // esi

  v1 = this;
  v2 = *(this + 29);
  if ( v2 == 0 )
    return 0;
  v4 = *(uint32_t *)(v2 + 120);
  if ( v4 != 0 )
    v5 = (*(uint32_t *)(v2 + 124) - v4) >> 2;
  else
    v5 = 0;
  v6 = 0;
  if ( v5 <= 0 )
    return 0;
  while ( 1 )
  {
    v7 = v1[29];
    v8 = *(uint32_t *)(v7 + 120);
    if ( v8 != 0 && v6 < (*(uint32_t *)(v7 + 124) - v8) >> 2 )
      v9 = *(uint32_t *)(v8 + 4 * v6);
    else
      v9 = 0;
    v10 = __RTDynamicCast(v9, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);
    v11 = v10;
    if ( v10 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 688))(v10) == 2
      && (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 684))(v11) == this )
    {
      break;
    }
    if ( (int)++v6 >= v5 )
      return 0;
    v1 = this;
  }
  return 1;
}



// AI 相位辅助（65L）
// ------------------------------------------------------------
// 0x5DB550 sub_5DB550
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB550(uint32_t *this, int a2, int a3)
{
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int *v7; // ebx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  void *v11; // ecx
  uint8_t v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  bool v18; // [esp+27h] [ebp-Dh]
  int v19; // [esp+30h] [ebp-4h]

  v4 = 0;
  do
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
      v5 = a2 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    else
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - a2;
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v6 = a3 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v17 = v6;
    if ( v4 == 1 )
    {
      v5 += (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 ? -30 : 30;
      v6 = v17;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + v4 + 2104) + 40))(
      *(this + v4 + 2104),
      v5,
      v16,
      v6);
    v7 = (int *)*(this + v4 + 2104);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v9 = *v7;
    v18 = v8 == 0;
    v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 28))(v7);
    *(uint8_t *)(v10 + 84) = v18;
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + v4 + 2104) + 92))(*(this + v4 + 2104), v12);
    v11 = (void *)*(this + 29);
    v19 = 0;
    sub_4600B0(v11, 2, 0, (int)v12);
    v19 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v4;
    Block = nullptr;
    v14 = 0;
    v15 = 0;
  }
  while ( v4 < 2 );
}



// 数据表读数（sub_47EF20, 47L）
// ------------------------------------------------------------
// 0x5DB670 sub_5DB670
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB670(uint32_t *this, int a2, int a3)
{
  int result; // eax
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = *(this + 2058);
    if ( v5 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v5 + 80))() != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);
      v11 = sub_41A5E0(14 * a3 + *(uint32_t *)(v6 + 348) - 14);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 1160))(this, 2, 1, v7);
      v8 = sub_47EF20(2, -1, -1, 11, a2);
      sub_41A590(
        14 * a3 + *(uint32_t *)(v6 + 348) - 14,
        (int)((uint64_t)(274877907LL * v11 * (1000 - v8)) >> 32) >> 6,
        v11 * (1000 - v8) / 1000);
      sub_579650(a2, a3);
      return sub_41A590(14 * a3 + *(uint32_t *)(v6 + 348) - 14, v9, v11);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, a2);
        return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, a3);
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB780 sub_5DB780
// ------------------------------------------------------------
int */*thiscall*/ sub_5DB780(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_5DB330((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
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
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// 时钟门 AI（sub_699000, 134L）
// ------------------------------------------------------------
// 0x5DB810 sub_5DB810
// ------------------------------------------------------------
char /*thiscall*/ sub_5DB810(uint32_t *this)
{
  int v2; // eax
  int *v3; // edi

  LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)v2 != 0 )
  {
    sub_4AFEC0(this);
    if ( *(this + 2111) != -1
      && *(this + 2110) != 0
      && sub_699000((int)(this + 9)) < *(this + 2111)
      && (uint8_t)sub_5DB490(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 39);
      sub_47E440(1);
    }
    LOBYTE(v2) = *((uint8_t *)this + 7730);
    if ( (uint8_t)v2 != 0 )
    {
      v2 = *(this + 1639);
      switch ( v2 )
      {
        case 0:
        case 11:
          if ( *(this + 2142) == -1 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 2);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 4);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 6);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 7);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 9);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 8);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 10);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 11);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 12);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 13);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 14);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 16);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 17);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 18);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 20);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 26);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 27);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 28);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 29);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 30);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 31);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 37);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 40);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 41);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 43);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 49);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 50);
            sub_47E440(1);
            v3 = (int *)&unk_737FFC;
            do
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, *v3);
              LOBYTE(v2) = sub_47E440(1);
              ++v3;
            }
            while ( (int)v3 < (int)&dword_738020 );
          }
          else
          {
            byte_9A0358 = 0;
            byte_9A0384 = 0;
            LOBYTE(v2) = sub_483DF0(0);
          }
          break;
        case 3:
        case 4:
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 8);
          if ( (uint8_t)v2 == 0 )
          {
            LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 16);
            if ( (uint8_t)v2 == 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 3);
              LOBYTE(v2) = sub_47E440(1);
            }
          }
          break;
        case 6:
          v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 42);
          if ( v2 > 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);
            LOBYTE(v2) = sub_47E440(1);
          }
          break;
        default:
          return v2;
      }
    }
  }
  return v2;
}


// 语音注册（sub_4015C0; this+8628）
// ------------------------------------------------------------
// 0x5DBBD0 sub_5DBBD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DBBD0(uint32_t *this, void *Src, int a3)
{
  int result; // eax
  int v5; // eax

  result = *(this + 2148);
  if ( result != -1 )
  {
    v5 = a3 + result;
    if ( dword_79D100[0] < v5 )
    {
      *(this + 2149) = v5;
      result = sub_4015C0(Src, strlen((const char *)Src));
      *((uint8_t *)this + 8628) = 1;
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
      result = (*(int (/*thiscall*/ **)(uint32_t *, void *, int, uint32_t, uint32_t))(*this + 212))(this, Src, -1, 0, 0);
    }
    *(this + 2148) = -1;
  }
  return result;
}



// 语音注册（sub_4015C0; STL 断言串为符号文本非资源）
// ------------------------------------------------------------
// 0x5DBC60 sub_5DBC60
// ------------------------------------------------------------
void /*noreturn*/ sub_5DBC60()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5DBCD0 sub_5DBCD0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DBCD0(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_5DBC60(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5DBEB0 sub_5DBEB0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DBEB0(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_4DE680(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC090 sub_5DC090
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DC090(uint32_t *this, int a2)
{
  int v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_433AC0(this);
  *(this + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_5DB780((int)this, a2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC120 sub_5DC120
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DC120(uint32_t *this, int a2)
{
  sub_5DC090(this, a2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC140 sub_5DC140
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5DC140(uint32_t **this, uint32_t **a2)
{
  int v2; // edi

  v2 = (int)a2;
  if ( this != a2 )
  {
    sub_4A3610(&a2, **(this + 1), *(this + 1));
    sub_5DB780((int)this, v2);
  }
  return this;
}



// ============================================================
// 【分区 10】追击弹与 AI 群（0x5DC170-0x5DD470）
// 证据：sub_47EF20 数据表读数群、sub_493D00 动画变速换锚、RTTI cast 目标解算群

// RTTI cast 目标解算（89L）
// ------------------------------------------------------------
// 0x5DC170 sub_5DC170
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC170(uint32_t *this, int a2)
{
  unsigned int v3; // ebx
  uint32_t *v4; // esi
  int v5; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  uint32_t *v12; // esi
  int v13; // eax
  int v14; // eax
  int v15; // esi
  int v16; // [esp+Ch] [ebp-Ch] BYREF
  uint32_t *v17; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]
  int v19; // [esp+20h] [ebp+8h]

  v3 = 0;
  v4 = this;
  v17 = this;
  v18 = 0;
  if ( a2 != 0 )
  {
    if ( *(uint32_t *)(a2 + 4) != 0 )
      j__free(*(void **)(a2 + 4));
    *(uint32_t *)(a2 + 4) = 0;
    *(uint32_t *)(a2 + 8) = 0;
    *(uint32_t *)(a2 + 12) = 0;
  }
  v5 = v4[29];
  if ( v5 == 0 )
    return 0;
  v7 = *(uint32_t *)(v5 + 120);
  if ( v7 != 0 )
    v19 = (*(uint32_t *)(v5 + 124) - v7) >> 2;
  else
    v19 = 0;
  if ( v19 > 0 )
  {
    while ( 1 )
    {
      v8 = v4[29];
      v9 = *(uint32_t *)(v8 + 120);
      if ( v9 != 0 && v3 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v3);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);
      v12 = (uint32_t *)v11;
      v16 = v11;
      if ( v11 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 688))(v11) == 2 )
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v12 + 684))(v12);
        if ( (uint32_t *)v13 == v17 )
        {
          if ( a2 != 0 )
          {
            v14 = *(uint32_t *)(a2 + 4);
            if ( v14 != *(uint32_t *)(a2 + 8) )
            {
              v15 = v12[251];
              do
              {
                if ( *(uint32_t *)(*(uint32_t *)v14 + 1004) >= v15 )
                  break;
                v14 += 4;
              }
              while ( v14 != *(uint32_t *)(a2 + 8) );
            }
            sub_5DBCD0(a2, v14, 1u, &v16);
          }
          ++v18;
        }
      }
      if ( (int)++v3 >= v19 )
        break;
      v4 = v17;
    }
  }
  return v18;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC290 sub_5DC290
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC290(uint32_t *this)
{
  unsigned int v1; // esi
  int v2; // ebx
  void *v3; // edi
  int v4; // eax
  bool v5; // zf
  uint8_t v6[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+24h] [ebp-4h]

  v1 = 0;
  Block = nullptr;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  sub_5DC170(this, (int)v6);
  v2 = v8;
  v3 = Block;
  while ( v3 != nullptr )
  {
    if ( v1 >= (v2 - (int)v3) >> 2 )
    {
      j__free(v3);
      return;
    }
    v4 = *((uint32_t *)v3 + v1);
    v5 = *(uint32_t *)(v4 + 960) == 3;
    *(uint32_t *)(v4 + 1004) = v1;
    if ( !v5 )
      sub_617720(v4 + 984, v4 + 988, v4 + 992, v1);
    ++v1;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC330 sub_5DC330
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC330(uint32_t *this, int a2, int a3, int a4)
{
  unsigned int v4; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // ebx
  uint8_t v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Src; // [esp+10h] [ebp-24h]
  int v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h] BYREF
  unsigned int v17; // [esp+20h] [ebp-14h]
  int v18; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  v4 = 0;
  v16 = 0;
  Src = nullptr;
  v14 = 0;
  v15 = 0;
  v6 = *(this + 29);
  v19 = 0;
  if ( v6 != 0 )
  {
    v7 = *(uint32_t *)(v6 + 120);
    v18 = v7 != 0 ? (*(uint32_t *)(v6 + 124) - v7) >> 2 : 0;
    v17 = 0;
    if ( v18 > 0 )
    {
      do
      {
        v8 = *(this + 29);
        v9 = *(uint32_t *)(v8 + 120);
        if ( v9 != 0 && v4 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * v4);
        else
          v10 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 33) != 0
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 348))(v10) + 20) == a4 )
        {
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v10, 0);
          if ( v16 <= a3 / 2 )
          {
            v16 = v10;
            sub_45F8A0(Src, 1, (int)&v16);
            v4 = v17;
          }
        }
        v17 = ++v4;
      }
      while ( (int)v4 < v18 );
    }
  }
  sub_4982B0(v12);
  return a2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC480 sub_5DC480
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC480(uint32_t *this, int a2, char a3)
{
  unsigned int v4; // edi
  void *v5; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+Ch] [ebp-14h]
  int v13; // [esp+10h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v4 = 0;
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    sub_5DC170(this, (int)v10);
    v5 = Block;
    if ( Block != nullptr )
      v4 = (v12 - (int)Block) >> 2;
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);
    if ( v4 < sub_47E9D0(v6, 1u) )
    {
      v9 = 0;
      if ( v5 != nullptr && (v12 - (int)v5) >> 2 != 0 )
        v9 = *(uint32_t *)(*(uint32_t *)(v12 - 4) + 1004) + 1;
      if ( a3 != 0 )
        v9 += 10000;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        dword_737FB0[a2],
        v9,
        0,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0);
    }
    else
    {
      v7 = *((uint32_t **)dword_8F8528 + 7);
      v8 = sub_422E70(1205);
      sub_43BEE0(v7, v8, -6567706, 0, -1);
    }
    if ( v5 != nullptr )
      j__free(v5);
  }
}



// 数据表读数（sub_47EF20, 49L）
// ------------------------------------------------------------
// 0x5DC590 sub_5DC590
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC590(int *this, int a2)
{
  uint32_t *v3; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  uint32_t *v12; // ecx
  char v13; // [esp-Ch] [ebp-14h]
  int v14; // [esp+4h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    sub_432FA0();
    v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 2061));
    if ( (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061)) <= 1 )
      v14 = 1;
    else
      v14 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061));
    v4 = sub_5DC170(this, 0);
    if ( v4 < sub_47E9D0(v3, 1u) )
    {
      v5 = sub_47EA80(v14);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 752))(this) >= v5 && rand() % 1000 < a2 )
      {
        v6 = *this;
        v7 = sub_47EA80(v14);
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 752))(this);
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 744))(this, v8 - v7);
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*this + 1160))(this, 40, 1, v9);
        v10 = sub_47EF20(40, -1, -1, 11, 1);
        v13 = rand() % 1000 < v10;
        v11 = sub_5DA920(*(this + 2061));
        sub_5DC480(v12, v11, v13);
      }
    }
  }
}



// 数据表读数（sub_47EF20, 21L）
// ------------------------------------------------------------
// 0x5DC6D0 sub_5DC6D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC6D0(int *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // [esp-Ch] [ebp-10h]

  v4 = *(this + 2060);
  if ( v4 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v4 + 80))() != 0 && a3 > 0 && a2 <= 5 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
    v5 = sub_47EF20(40, 4, v6, -1, 11);
    sub_5DC590(this, v5);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC730 sub_5DC730
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DC730(int *this, int *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  int *v4; // eax
  unsigned int result; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
    v3 = (*(this + 2) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= (*(this + 3) - v2) >> 2 )
    return sub_5DBEB0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// AI 相位辅助（104L）
// ------------------------------------------------------------
// 0x5DC780 sub_5DC780
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC780(float *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // edx
  char *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  uint8_t *v14; // ecx
  char v15; // al
  int v16; // ecx
  float v17; // edx
  float v18; // edx
  int v20; // [esp-8h] [ebp-38h]
  int v21; // [esp-8h] [ebp-38h]
  int v22; // [esp-8h] [ebp-38h]
  uint8_t v23[12]; // [esp+8h] [ebp-28h] BYREF
  uint8_t v24[12]; // [esp+14h] [ebp-1Ch] BYREF
  int v25; // [esp+20h] [ebp-10h]
  int v26; // [esp+2Ch] [ebp-4h]

  if ( *((uint32_t *)this + 1639) == 8 && sub_41A5E0(this + 1757) == 0 && *((uint32_t *)this + 2054) == -1 )
  {
    v25 = sub_445870(37712398, 10000);
    if ( (double)v25 < 100.0 )
    {
      v5 = *(uint32_t *)this;
      *(this + 2056) = 9.0;
      (*(void (/*thiscall*/ **)(float *, int))(v5 + 672))(this, 3);
      sub_4AED60(9.0);
    }
  }
  if ( *((uint32_t *)this + 1639) == 20 && *((uint32_t *)this + 2129) == 20 )
  {
    if ( (uint8_t)sub_4E4630(a2) != 0 )
    {
      if ( *((uint32_t *)this + 2132) != 6 )
      {
        *((uint32_t *)this + 2132) = 6;
        sub_5DC090(this + 135);
        v6 = *(uint32_t *)this;
        v20 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
        v26 = 0;
        (*(void (/*thiscall*/ **)(float *, int))(v6 + 344))(this, v20);
        sub_5DC140(v24);
        v7 = (char *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1160))(this, 20);
        v8 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1140))(this, 20);
        v9 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 388))(this);
        v10 = sub_47EFD0(v7, COERCE_FLOAT(8), v8, v9, v9, 11) - 100 + *((uint32_t *)this + 99);
        v11 = *(uint32_t *)this;
        *((uint32_t *)this + 99) = v10;
        v12 = (*(int (/*thiscall*/ **)(float *))(v11 + 388))(this);
        v13 = 100 * sub_47EFD0(v7, COERCE_FLOAT(9), v8, v12, v12, 0) / (*((uint32_t *)this + 99) + 100);
        v14 = v24;
        *(this + 97) = (double)v13 + *(this + 97);
LABEL_16:
        v26 = -1;
        sub_4A3790(v14);
      }
    }
    else
    {
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529);
      v16 = *((uint32_t *)this + 2132);
      if ( v15 != 0 )
      {
        if ( v16 != 4 )
        {
          *((uint32_t *)this + 2132) = 4;
          sub_5DC120(this + 135);
          v17 = *this;
          v21 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
          v26 = 1;
          (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v17) + 344))(this, v21);
          sub_5DC140(v24);
          v14 = v24;
          goto LABEL_16;
        }
      }
      else if ( v16 != 5 )
      {
        *((uint32_t *)this + 2132) = 5;
        sub_5DC120(this + 135);
        v18 = *this;
        v22 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
        v26 = 2;
        (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 344))(this, v22);
        sub_5DC140(v23);
        v14 = v23;
        goto LABEL_16;
      }
    }
  }
  return 0;
}



// 数据表+插值 AI（sub_47EF20+sub_4049C0, 175L）
// ------------------------------------------------------------
// 0x5DCA10 sub_5DCA10
// ------------------------------------------------------------
void /*userpurge*/ sub_5DCA10(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edi
  float v13; // eax
  float v14; // edi
  float v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // eax
  int v20; // edx
  int v21; // ebx
  int v22; // edi
  uint64_t v23; // rax
  int v24; // ebx
  uint64_t v25; // rax
  int v26; // edi
  bool v27; // cc
  uint32_t *v28; // eax
  int v29; // [esp-10h] [ebp-50h]
  char v30; // [esp+0h] [ebp-40h]
  uint8_t v31[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *Block; // [esp+8h] [ebp-38h]
  void *Src; // [esp+Ch] [ebp-34h]
  int v34; // [esp+10h] [ebp-30h]
  int v35; // [esp+14h] [ebp-2Ch] BYREF
  float v36; // [esp+18h] [ebp-28h]
  int v37; // [esp+1Ch] [ebp-24h] BYREF
  int v38; // [esp+20h] [ebp-20h]
  float v39; // [esp+24h] [ebp-1Ch]
  int v40; // [esp+28h] [ebp-18h] BYREF
  float v41; // [esp+2Ch] [ebp-14h]
  float v42; // [esp+30h] [ebp-10h]
  int v43; // [esp+3Ch] [ebp-4h]

  v5 = a1[1639];
  if ( v5 != 4 && v5 != 3 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 724))(a1) != 0 )
    return;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 776))(a1, 8);
  LOBYTE(v6) = (uint8_t)v6 == 0 && (uint8_t)(v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 776))(a1, 16)) == 0;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 1160))(a1, 3, v6);
  sub_47E440(v30);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1312))(a1, 3) == 0 )
    return;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*a1 + 1132))(a1, 0, a3, a2);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1132))(a1, 1);
  v37 = v8;
  if ( v7 == 4 && v8 == 4 )
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1);
    v7 = sub_432E50(v9);
  }
  *(float *)&v10 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1));
  v11 = *a1;
  v12 = v10;
  v41 = *(float *)&v10;
  v13 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v11 + 124))(a1));
  v42 = v13;
  if ( v7 != 0 )
  {
    if ( v7 != 1 )
      goto LABEL_17;
    LODWORD(v14) = dword_795850 + v12;
  }
  else
  {
    LODWORD(v14) = v12 - dword_795850;
  }
  v41 = v14;
LABEL_17:
  if ( v37 == 2 )
  {
    LODWORD(v15) = LODWORD(v13) - dword_795854;
LABEL_21:
    v42 = v15;
    goto LABEL_22;
  }
  if ( v37 == 3 )
  {
    LODWORD(v15) = dword_795854 + LODWORD(v13);
    goto LABEL_21;
  }
LABEL_22:
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1);
  v17 = *a1;
  v18 = v16;
  v38 = v16;
  v39 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v17 + 124))(a1));
  v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1);
  v20 = *a1;
  v37 = v19;
  v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v20 + 124))(a1);
  if ( v7 == 4 )
  {
    v24 = abs32(LODWORD(v39) - LODWORD(v42));
    v38 = 0;
    if ( v24 >= 0 )
    {
      v42 = (float)SLODWORD(v42);
      v39 = (float)SLODWORD(v39);
      do
      {
        v25 = (uint64_t)sub_4049C0(v39, v42, v38, v24);
        v26 = v25;
        if ( (*(uint8_t (/*fastcall*/ **)(uint32_t *, uint32_t, float, uint32_t, uint32_t))(*a1 + 136))(
               a1,
               HIDWORD(v25),
               COERCE_FLOAT(LODWORD(v41)),
               v25,
               0) == 0 )
          break;
        v27 = v38 + 1 <= v24;
        v40 = v26;
        ++v38;
      }
      while ( v27 );
    }
  }
  else
  {
    v21 = 0;
    v22 = abs32(v18 - LODWORD(v41));
    if ( v22 >= 0 )
    {
      v41 = (float)SLODWORD(v41);
      v36 = (float)v38;
      v42 = (float)SLODWORD(v42);
      v39 = (float)SLODWORD(v39);
      do
      {
        v38 = (uint64_t)sub_4049C0(v36, v41, v21, v22);
        v23 = (uint64_t)sub_4049C0(v39, v42, v21, v22);
        HIDWORD(v23) = *a1;
        v35 = v23;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(HIDWORD(v23) + 136))(a1, v38, v23, 0) == 0 )
          break;
        ++v21;
        v37 = v38;
        v40 = v35;
      }
      while ( v21 <= v22 );
    }
  }
  Block = nullptr;
  Src = nullptr;
  v34 = 0;
  v43 = 0;
  v35 = 3;
  sub_430C80(nullptr, 1, (int)&v35);
  sub_430C80(nullptr, 1, (int)&v37);
  sub_430C80(nullptr, 1, (int)&v40);
  v28 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1160))(a1, 3);
  v35 = sub_47E9D0(v28, 0);
  sub_430C80(nullptr, 1, (int)&v35);
  v29 = a4;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1160))(a1, 3);
  v35 = sub_47EF20(0, v29, -1, -1, 11);
  sub_430C80(nullptr, 1, (int)&v35);
  sub_430C80(nullptr, 1, (int)&a4);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *))(*a1 + 560))(a1, 17, v31);
  if ( Block != nullptr )
    j__free(Block);
}


// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5DCE00 sub_5DCE00
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCE00(uint32_t *this, int a2)
{
  int v2; // edi
  uint32_t *v3; // esi
  int v4; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-30h] BYREF
  void *v6; // [esp+Ch] [ebp-2Ch]
  int v7; // [esp+10h] [ebp-28h]
  int v8; // [esp+14h] [ebp-24h]
  uint8_t v9[4]; // [esp+18h] [ebp-20h] BYREF
  void *Block; // [esp+1Ch] [ebp-1Ch]
  int v11; // [esp+20h] [ebp-18h]
  int v12; // [esp+24h] [ebp-14h]
  uint32_t *v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+34h] [ebp-4h]

  v2 = a2;
  v13 = this;
  if ( a2 != 0 )
  {
    v6 = nullptr;
    v7 = 0;
    v8 = 0;
    v14 = 0;
    sub_5DC170(this, (int)v5);
    v3 = v6;
    if ( v6 != nullptr )
    {
      if ( (v7 - (int)v6) >> 2 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*v13 + 212))(
          v13,
          off_79583C[*(uint32_t *)(*(uint32_t *)v6 + 980)],
          -1,
          0,
          0);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v3 + 308))(*v3) != 0 )
        {
          Block = nullptr;
          v11 = 0;
          v12 = 0;
          v4 = *(uint32_t *)v2;
          LOBYTE(v14) = 1;
          a2 = (*(int (/*thiscall*/ **)(int))(v4 + 48))(v2);
          sub_431230((int)v9, &a2);
          a2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 52))(v2);
          sub_431230((int)v9, &a2);
          a2 = 400;
          sub_431230((int)v9, &a2);
          (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)*v3 + 560))(*v3, 3, v9, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v11 = 0;
          v12 = 0;
        }
      }
      j__free(v3);
    }
  }
}



// 追击弹爆炸：CHASER_EXPLOSION 播报（81L）
// ------------------------------------------------------------
// 0x5DCF20 sub_5DCF20
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCF20(uint32_t *this)
{
  uint32_t *v1; // esi
  unsigned int v2; // eax
  unsigned int v3; // ecx
  int v4; // edi
  int v5; // esi
  uint8_t v6[4]; // [esp+8h] [ebp-3Ch] BYREF
  void *Block; // [esp+Ch] [ebp-38h]
  int v8; // [esp+10h] [ebp-34h]
  int v9; // [esp+14h] [ebp-30h]
  uint8_t v10[4]; // [esp+18h] [ebp-2Ch] BYREF
  void *v11; // [esp+1Ch] [ebp-28h]
  int v12; // [esp+20h] [ebp-24h]
  int v13; // [esp+24h] [ebp-20h]
  uint32_t *v14; // [esp+28h] [ebp-1Ch]
  unsigned int v15; // [esp+2Ch] [ebp-18h]
  int v16; // [esp+30h] [ebp-14h] BYREF
  int v17; // [esp+34h] [ebp-10h]
  int v18; // [esp+40h] [ebp-4h]

  v14 = this;
  Block = nullptr;
  v8 = 0;
  v9 = 0;
  v18 = 0;
  sub_5DC170(this, (int)v6);
  v1 = Block;
  if ( Block != nullptr )
  {
    v2 = (v8 - (int)Block) >> 2;
    v15 = v2;
    if ( v2 != 0 )
    {
      v3 = 0;
      v17 = 0;
      v4 = 0;
      while ( v3 < v2 )
      {
        v5 = v1[v3];
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 308))(v5) != 0 )
        {
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
          LOBYTE(v18) = 1;
          v16 = v4;
          sub_430C80(nullptr, 1, (int)&v16);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)v5 + 560))(v5, 4, v10, 0, 0);
          LOBYTE(v18) = 0;
          if ( v11 != nullptr )
            j__free(v11);
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
        }
        v1 = Block;
        v2 = v15;
        v3 = ++v17;
        v4 += 80;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*v14 + 212))(
        v14,
        "CHASER_EXPLOSION",
        -1,
        0,
        0);
      j__free(v1);
    }
    else
    {
      j__free(Block);
    }
  }
}



// RTTI cast 大型 AI（139L）
// ------------------------------------------------------------
// 0x5DD040 sub_5DD040
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD040(uint32_t *this, int a2, int a3, char a4)
{
  uint32_t *v4; // esi
  int v5; // eax
  unsigned int v6; // ebx
  int *v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // edi
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // esi
  int v23; // eax
  int *v24; // eax
  uint32_t *v25; // [esp+8h] [ebp-14h] BYREF
  int v26; // [esp+Ch] [ebp-10h]
  int v27; // [esp+10h] [ebp-Ch]
  uint32_t *v28; // [esp+14h] [ebp-8h]
  char v29; // [esp+1Bh] [ebp-1h]

  v4 = this;
  v5 = *(this + 29);
  v6 = 0;
  v28 = this;
  if ( v5 == 0 )
    return 0;
  if ( a3 != 0 )
  {
    if ( *(uint32_t *)(a3 + 4) != 0 )
      j__free(*(void **)(a3 + 4));
    *(uint32_t *)(a3 + 4) = 0;
    *(uint32_t *)(a3 + 8) = 0;
    *(uint32_t *)(a3 + 12) = 0;
  }
  v8 = &dword_738020;
  while ( a2 != *v8 )
  {
    if ( (int)++v8 >= (int)&dword_738030 )
    {
      v29 = 0;
      goto LABEL_11;
    }
  }
  v29 = 1;
LABEL_11:
  v9 = v4[29];
  v10 = *(uint32_t *)(v9 + 120);
  v11 = v9 + 116;
  v26 = 0;
  if ( v10 != 0 )
    v27 = (*(uint32_t *)(v11 + 8) - v10) >> 2;
  else
    v27 = 0;
  if ( v27 > 0 )
  {
    do
    {
      v12 = v4[29];
      v13 = *(uint32_t *)(v12 + 120);
      if ( v13 != 0 && v6 < (*(uint32_t *)(v12 + 124) - v13) >> 2 )
        v14 = *(uint32_t *)(v13 + 4 * v6);
      else
        v14 = 0;
      v15 = (uint32_t *)__RTDynamicCast(
                        v14,
                        0,
                        &IRDCollisionObject `RTTI Type Descriptor',
                        &IRDMonster `RTTI Type Descriptor',
                        0);
      v16 = v15;
      v25 = v15;
      if ( v15 != nullptr )
      {
        if ( (uint32_t *)v15[2088] != v4
          || (*(int (/*thiscall*/ **)(uint32_t *))(*v15 + 840))(v15) == 13
          || (*(int (/*thiscall*/ **)(uint32_t *))(*v16 + 840))(v16) == 5 )
        {
          goto LABEL_44;
        }
        v17 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v16 + 340))(v16);
      }
      else
      {
        v18 = v4[29];
        v19 = *(uint32_t *)(v18 + 120);
        if ( v19 != 0 && v6 < (*(uint32_t *)(v18 + 124) - v19) >> 2 )
          v20 = *(uint32_t *)(v19 + 4 * v6);
        else
          v20 = 0;
        v21 = __RTDynamicCast(
                v20,
                0,
                &IRDCollisionObject `RTTI Type Descriptor',
                &CNSummonMonsterWithEffect `RTTI Type Descriptor',
                0);
        v22 = v21;
        if ( v21 == 0 || (uint32_t *)(v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 576))(v21)) != v28 )
        {
          v4 = v28;
          goto LABEL_44;
        }
        v17 = *(uint16_t *)(v22 + 973);
        v4 = v28;
      }
      if ( a2 == 0xFFFF || a2 == v17 )
        goto LABEL_40;
      if ( v29 != 0 && a4 != 0 )
      {
        v24 = &dword_738020;
        while ( v17 != *v24 )
        {
          if ( (int)++v24 >= (int)&dword_738030 )
            goto LABEL_44;
        }
LABEL_40:
        ++v26;
        if ( a3 != 0 && v16 != nullptr )
          sub_5DC730(&v25);
      }
LABEL_44:
      ++v6;
    }
    while ( (int)v6 < v27 );
  }
  return v26;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5DD210 sub_5DD210
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD210(uint32_t *this, int a2, int a3, int a4)
{
  sub_5910D0(this, 0, 18, 250, 1);
  *this = &CNSummonMonsterAura::`vftable';
  sub_64EE80(this);
  sub_64F170(a2, a3, a4);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD280 sub_5DD280
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD280(uint32_t *this, int a2, int a3, int a4)
{
  *(this + 21) = a2;
  *(this + 32) = a3;
  *(this + 33) = a4;
  return a4;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2A0 sub_5DD2A0
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD2A0(void *Block, char a2)
{
  sub_5DD2D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2D0 sub_5DD2D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD2D0(char *this)
{
  *(uint32_t *)this = &CNSummonMonsterAura::`vftable';
  sub_64F1F0();
  return sub_591190(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD320 sub_5DD320
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD320(uint32_t *this)
{
  sub_5910D0(this, 0, 18, 250, 0);
  *this = &CNTargetIt::`vftable';
  sub_607240(this + 34);
  sub_607280(this + 34);
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  sub_64F230(this);
  sub_64FB80(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD3B0 sub_5DD3B0
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD3B0(void *Block, char a2)
{
  sub_5DD3E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD3E0 sub_5DD3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD3E0(int this)
{
  *(uint32_t *)this = &CNTargetIt::`vftable';
  sub_64FC00();
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  nullsub_3(this + 136);
  return sub_591190((char *)this);
}



// ============================================================
// 【分区 11】白魔 WZ（大型主状态机）（0x5DD470-0x5E0000）
// 证据：WZ_JUMP_ATK/WZ_JUMP/WZ_BACKSTEP/WZ_DASH_ATK/WZ_DASH_HIT/WZ_DIE/WZ_NOMANA +
//       R_WZ_DMG/R_WZ_THROW/R_WZ_LESSON_START、Effect/Particle/HandHit{1,2}.ptl、
//       Effect/Animation/WhipToMonsterHit.ani 鞭击、FollowMeCast.ani/PRICK/HEAVEN_HIT、
//       ★ 0x5DE690（1082L 本工程最大函数）= switch(this+6556) 大状态 6/10/16-21 分派

// 白魔技能语音组：WZ_JUMP_ATK/R_WZ_DMG/WZ_DIE/WZ_JUMP/WZ_BACKSTEP/WZ_DASH_ATK/
//   WZ_NOMANA/R_WZ_THROW 八件套 + Effect/Particle/HandHit{1,2}.ptl（93L）
// ------------------------------------------------------------
// 0x5DD470 sub_5DD470
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD470(int this)
{
  int v2; // ecx
  int v3; // eax
  unsigned int v4; // edi
  uint32_t *v5; // eax
  int v6; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-10h] BYREF
  int v9; // [esp+18h] [ebp-4h]

  v2 = this + 7892;
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6868) = 8;
  *(uint32_t *)(this + 6872) = 14;
  v3 = *(uint32_t *)(v2 + 4);
  Block = (void *)3;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(v2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(v2 + 12) - v3) >> 2 )
  {
    v5 = *(uint32_t **)(v2 + 8);
    *v5 = 3;
    *(uint32_t *)(v2 + 8) = v5 + 1;
  }
  else
  {
    sub_430C80(*(void **)(v2 + 8), 1, (int)&Block);
  }
  *(uint32_t *)(this + 7908) = 100;
  *(uint32_t *)(this + 7912) = -300;
  *(uint32_t *)(this + 7916) = 200;
  *(uint32_t *)(this + 7920) = -300;
  *(uint32_t *)(this + 7844) = 43;
  *(uint32_t *)(this + 7848) = 60;
  *(uint32_t *)(this + 7852) = 1;
  *(uint8_t *)(this + 7924) = 0;
  *(uint32_t *)(this + 7928) = 3;
  sub_4015C0("WZ_JUMP_ATK", 0xBu);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("R_WZ_DMG", 8u);
  sub_4015C0("WZ_DIE", 6u);
  sub_4015C0("WZ_JUMP", 7u);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("WZ_BACKSTEP", 0xBu);
  sub_4015C0("WZ_DASH_ATK", 0xBu);
  sub_4015C0("WZ_NOMANA", 9u);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("R_WZ_THROW", 0xAu);
  Block = operator new(0x12Cu);
  v9 = 0;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v6 = sub_4C3640(this + 364, "Effect/Particle/HandHit1.ptl", this);
    else
      v6 = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit1.ptl", this);
  }
  else
  {
    v6 = 0;
  }
  v9 = -1;
  *(uint32_t *)(this + 8416) = v6;
  Block = operator new(0x12Cu);
  v9 = 1;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      result = sub_4C3640(this + 364, "Effect/Particle/HandHit2.ptl", this);
    else
      result = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit2.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(uint32_t *)(this + 8420) = result;
  return result;
}



// AI 字段访问（this+8372）
// ------------------------------------------------------------
// 0x5DD700 sub_5DD700
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD700(int this, int a2, int a3, int a4)
{
  int v5; // eax
  uint32_t *v6; // esi
  uint32_t *v7; // ebx
  int v8; // esi
  int v9; // esi
  char v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  v5 = *(uint32_t *)(this + 8372);
  if ( v5 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v5 + 80))() != 0 )
  {
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
    v15 = 0;
    sub_5DD040((uint32_t *)this, 0xFFFF, (int)v11, 1);
    v6 = Block;
    v7 = v13;
    if ( Block != v13 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*v6 + 1052))(*v6, this, a2, a3, a4);
        ++v6;
      }
      while ( v6 != v7 );
      v6 = Block;
    }
    v15 = -1;
    if ( v6 != nullptr )
      j__free(v6);
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 60) != 0 )
  {
    if ( *(uint8_t *)(this + 642) != 0 )
    {
      v8 = *(uint32_t *)(this + 644);
    }
    else
    {
      v9 = *(uint32_t *)(this + 120);
      if ( v9 == 0 )
      {
LABEL_16:
        if ( (uint8_t)a4 == 0 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);
        return sub_4B9720(a2, a3, a4);
      }
      if ( *(uint32_t *)(v9 + 148) == -1 )
        sub_4938F0(*(uint32_t *)(this + 120));
      v8 = *(uint32_t *)(v9 + 112);
    }
    if ( v8 != 0 )
      return sub_4B9720(a2, a3, a4);
    goto LABEL_16;
  }
  return sub_4B9720(a2, a3, a4);
}



// 参数打包+数据表 AI（sub_431230+sub_47EF20, 160L）
// ------------------------------------------------------------
// 0x5DD810 sub_5DD810
// ------------------------------------------------------------
void /*thiscall*/ sub_5DD810(int *this, void *a2, int Block)
{
  int v3; // edi
  int v5; // edx
  void *v6; // eax
  int v7; // eax
  int v8; // eax
  int *v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // ecx
  BOOL v17; // edi
  void *v18; // eax
  int v19; // eax
  int v20; // ecx
  float v21; // [esp+4h] [ebp-20h]
  float v22; // [esp+8h] [ebp-1Ch]
  float v23; // [esp+8h] [ebp-1Ch]

  v3 = Block;
  sub_4B3E70(this, a2, Block);
  if ( a2 == (void *)1 )
  {
    if ( v3 <= 0 )
    {
      sub_505FF0(1, 0);
    }
    else
    {
      v5 = *(this + 1974);
      if ( v5 == 0 || (unsigned int)((*(this + 1975) - v5) >> 2) < 2 )
      {
        Block = 4;
        sub_431230((int)(this + 1973), &Block);
      }
    }
    return;
  }
  if ( a2 == (void *)19 )
  {
    if ( v3 > 0 )
    {
      if ( *(this + 2138) == 0 )
      {
        v6 = operator new(0x7Cu);
        Block = (int)v6;
        if ( v6 != nullptr )
          v7 = sub_4B3C90((int)v6, 0, 0);
        else
          v7 = 0;
        *(this + 2138) = v7;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 64))(v7) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 19);
      v8 = sub_47EF20(0, v3, -1, -1, 11);
      v9 = (int *)*(this + 2138);
      v10 = *v9;
      Block = v8;
      (*(void (/*thiscall*/ **)(int *))(v10 + 124))(v9);
      v22 = (float)Block;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2138) + 120))(9, 0, LODWORD(v22));
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2138) + 56))(
        *(this + 2138),
        this,
        this,
        0,
        0,
        0,
        -1);
      return;
    }
    v11 = *(this + 2138);
    if ( v11 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 80))(v11) == 0 )
      return;
    v12 = *(this + 2138);
LABEL_41:
    sub_53FE50(v12);
    return;
  }
  if ( a2 == (void *)35 || a2 == (void *)36 )
  {
    v17 = a2 == (void *)36;
    if ( Block <= 0 )
    {
      v20 = *(this + v17 + 2139);
      if ( v20 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 80))(v20) == 0 )
        return;
      v12 = *(this + v17 + 2139);
      goto LABEL_41;
    }
    if ( *(this + v17 + 2139) == 0 )
    {
      v18 = operator new(0x88u);
      if ( v18 != nullptr )
        v19 = sub_4C2820((int)v18, 3, (int)a2);
      else
        v19 = 0;
      *(this + v17 + 2139) = v19;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 64))(v19) + 36) = 0;
    }
    sub_5F9DD0(Block);
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + v17 + 2139) + 56))(
      *(this + v17 + 2139),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  else
  {
    if ( a2 != (void *)48 )
      return;
    if ( v3 <= 0 )
    {
      v16 = *(this + 2141);
      if ( v16 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 80))(v16) == 0 )
        return;
      v12 = *(this + 2141);
      goto LABEL_41;
    }
    if ( *(this + 2141) == 0 )
    {
      if ( operator new(0x8Cu) != nullptr )
        v13 = sub_5DD210(0, 0, 0);
      else
        v13 = 0;
      *(this + 2141) = v13;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 64))(v13) + 36) = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 48);
    v14 = *(uint32_t *)*(this + 2141);
    v23 = (double)(int)sub_47EF20(2, Block, -1, -1, 11) * 0.1;
    v21 = (double)(int)sub_47EF20(1, Block, -1, -1, 11) * 0.1;
    v15 = sub_47EF20(0, Block, -1, -1, 11);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(v14 + 148))(
      *(this + 2141),
      v15 / 2,
      LODWORD(v21),
      LODWORD(v23));
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2141) + 56))(
      *(this + 2141),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
}


// 数据表读数（sub_47EF20, 43L）
// ------------------------------------------------------------
// 0x5DDBA0 sub_5DDBA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DDBA0(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi

  if ( *(this + 2123) == 0 )
  {
    v3 = operator new(0xB0u);
    if ( v3 != nullptr )
      v4 = sub_5DD320(v3);
    else
      v4 = nullptr;
    *(this + 2123) = v4;
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 64))(v4) + 36) = 0;
  }
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
  sub_64F250(v5);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 1160))(this, 50, 0, v6);
  v7 = sub_47EF20(50, -1, -1, 11, 50);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2123) + 80))(*(this + 2123)) == 0
    || *(uint32_t *)(*(this + 2123) + 4) != a2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2123) + 56))(
      *(this + 2123),
      a2,
      this,
      1,
      0,
      0,
      -1);
  }
  return sub_64FAC0(v7);
}



// 白魔相位字段大区（this+8232..8480, 247L —— WZ 专用字段块）
// ------------------------------------------------------------
// 0x5DDCA0 sub_5DDCA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5DDCA0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void ***v6; // esi
  void **v7; // edi
  void ***v8; // esi
  int v9; // edi
  void **v10; // edi
  bool v11; // zf
  void **v12; // edi
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  int v15; // esi
  int v16; // edi
  void (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  void **v18; // edi
  void **v19; // edi
  int v20; // esi
  void **v21; // esi
  void ***v22; // esi
  void **v23; // edi
  int v24; // esi
  void ***v25; // esi
  void **v26; // edi
  void ***v27; // esi
  void **v28; // edi
  int result; // eax
  int (/*thiscall*/ ***v30)(uint32_t, int); // ecx
  void **v31; // esi
  void **v32; // esi
  void **v33; // esi
  int (/*thiscall*/ ***v34)(uint32_t, int); // ecx
  uint32_t *v35; // esi
  int jj; // edi
  int (/*thiscall*/ ***v37)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-8h]
  int k; // [esp+8h] [ebp-8h]
  int m; // [esp+8h] [ebp-8h]
  int n; // [esp+8h] [ebp-8h]
  int ii; // [esp+8h] [ebp-8h]
  int v43; // [esp+8h] [ebp-8h]
  int j; // [esp+Ch] [ebp-4h]

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8232);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8236);
  *(uint32_t *)(this + 8232) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8240);
  *(uint32_t *)(this + 8236) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8248);
  *(uint32_t *)(this + 8240) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(uint32_t *)(this + 8248) = 0;
  v6 = (void ***)(this + 8276);
  for ( i = 4; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      v7 = *v6;
      if ( *v6 != nullptr )
      {
        sub_42AF90(*v6);
        sub_657740(v7, 228);
      }
      *v6++ = nullptr;
    }
  }
  v8 = (void ***)(this + 8328);
  for ( k = 5; k != 0; --k )
  {
    v9 = (int)*(v8 - 5);
    if ( v9 != 0 )
    {
      sub_42AF90(*(v8 - 5));
      sub_657740(v9, 228);
    }
    v10 = *v8;
    v11 = *v8 == nullptr;
    *(v8 - 5) = nullptr;
    if ( !v11 )
    {
      sub_42AF90(v10);
      sub_657740(v10, 228);
    }
    v12 = v8[5];
    *v8 = nullptr;
    if ( v12 != nullptr )
    {
      sub_42AF90(v12);
      sub_657740(v12, 228);
    }
    v8[5] = nullptr;
    ++v8;
  }
  v13 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8372);
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  v14 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8380);
  *(uint32_t *)(this + 8372) = 0;
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  *(uint32_t *)(this + 8380) = 0;
  v15 = this + 8416;
  for ( m = 2; m != 0; --m )
  {
    v16 = *(uint32_t *)(v15 - 8);
    if ( v16 != 0 )
    {
      sub_42AF90(*(void ***)(v15 - 8));
      sub_657740(v16, 228);
    }
    v17 = *(void (/*thiscall*/ ****)(uint32_t, int))v15;
    v11 = *(uint32_t *)v15 == 0;
    *(uint32_t *)(v15 - 8) = 0;
    if ( !v11 )
      (**v17)(v17, 1);
    v18 = *(void ***)(v15 + 8);
    *(uint32_t *)v15 = 0;
    if ( v18 != nullptr )
    {
      sub_42AF90(v18);
      sub_657740(v18, 228);
    }
    v19 = *(void ***)(v15 + 16);
    *(uint32_t *)(v15 + 8) = 0;
    if ( v19 != nullptr )
    {
      sub_42AF90(v19);
      sub_657740(v19, 228);
    }
    *(uint32_t *)(v15 + 16) = 0;
    v15 += 4;
  }
  v20 = *(uint32_t *)(this + 8448);
  if ( v20 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8448));
    sub_657740(v20, 228);
  }
  v21 = *(void ***)(this + 8452);
  *(uint32_t *)(this + 8448) = 0;
  if ( v21 != nullptr )
  {
    sub_42AF90(v21);
    sub_657740(v21, 228);
  }
  *(uint32_t *)(this + 8452) = 0;
  v22 = (void ***)(this + 8456);
  for ( n = 2; n != 0; --n )
  {
    v23 = *v22;
    if ( *v22 != nullptr )
    {
      sub_42AF90(*v22);
      sub_657740(v23, 228);
    }
    *v22++ = nullptr;
  }
  v24 = *(uint32_t *)(this + 8464);
  if ( v24 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8464));
    sub_657740(v24, 228);
  }
  *(uint32_t *)(this + 8464) = 0;
  v25 = (void ***)(this + 8468);
  for ( ii = 3; ii != 0; --ii )
  {
    v26 = *v25;
    if ( *v25 != nullptr )
    {
      sub_42AF90(*v25);
      sub_657740(v26, 228);
    }
    *v25++ = nullptr;
  }
  v27 = (void ***)(this + 8480);
  v43 = 2;
  do
  {
    v28 = *v27;
    if ( *v27 != nullptr )
    {
      sub_42AF90(*v27);
      sub_657740(v28, 228);
    }
    *v27++ = nullptr;
    result = v43 - 1;
    v43 = result;
  }
  while ( result != 0 );
  v30 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8492);
  if ( v30 != nullptr )
    result = (**v30)(v30, 1);
  v31 = *(void ***)(this + 8500);
  *(uint32_t *)(this + 8492) = 0;
  if ( v31 != nullptr )
  {
    sub_42AF90(v31);
    result = sub_657740(v31, 228);
  }
  v32 = *(void ***)(this + 8524);
  *(uint32_t *)(this + 8500) = 0;
  if ( v32 != nullptr )
  {
    sub_42AF90(v32);
    result = sub_657740(v32, 228);
  }
  v33 = *(void ***)(this + 8544);
  *(uint32_t *)(this + 8524) = 0;
  if ( v33 != nullptr )
  {
    sub_42AF90(v33);
    result = sub_657740(v33, 228);
  }
  v34 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8552);
  *(uint32_t *)(this + 8544) = 0;
  if ( v34 != nullptr )
    result = (**v34)(v34, 1);
  *(uint32_t *)(this + 8552) = 0;
  v35 = (uint32_t *)(this + 8556);
  for ( jj = 2; jj != 0; --jj )
  {
    if ( *v35 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v35)(*v35, 1);
    *v35++ = 0;
  }
  v37 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8564);
  if ( v37 != nullptr )
    result = (**v37)(v37, 1);
  *(uint32_t *)(this + 8564) = 0;
  return result;
}


// 冲刺命中（255L）：WZ_DASH_HIT 播报 + Effect/Animation/WhipToMonsterHit.ani 鞭击特效
//   （sub_431920+sub_699000+sub_47EF20+RTTI cast; this+8228 相位）
// ------------------------------------------------------------
// 0x5DE100 sub_5DE100
// ------------------------------------------------------------
int /*thiscall*/ sub_5DE100(int *this, int a2, float *a3, int a4)
{
  uint32_t *v5; // edi
  int v6; // eax
  uint32_t *v7; // eax
  int v8; // ebx
  int v9; // ecx
  int v10; // eax
  char v11; // bl
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // edx
  int *v16; // edi
  int v17; // ecx
  int v18; // ebx
  uint64_t v19; // rax
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int *v25; // eax
  int v26; // edx
  int v27; // ebx
  uint32_t *v28; // eax
  int v29; // eax
  int *v30; // eax
  int v31; // eax
  int v33; // eax
  int v34; // edi
  int v35; // ebx
  int v36; // eax
  int v37; // eax
  char *v38; // edi
  int v39; // ebx
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // edi
  int v49; // eax
  int v50; // [esp-Ch] [ebp-74h]
  int v51; // [esp-4h] [ebp-6Ch]
  unsigned int v52; // [esp+0h] [ebp-68h]
  int v53; // [esp+Ch] [ebp-5Ch]
  void *Block; // [esp+10h] [ebp-58h]
  int v55; // [esp+14h] [ebp-54h] BYREF
  int v56; // [esp+18h] [ebp-50h] BYREF
  int16_t v57; // [esp+1Ch] [ebp-4Ch]
  int16_t v58; // [esp+1Eh] [ebp-4Ah]
  int16_t v59; // [esp+20h] [ebp-48h]
  int v60; // [esp+22h] [ebp-46h]
  int v61; // [esp+58h] [ebp-10h]
  int v62; // [esp+64h] [ebp-4h]

  v61 = dword_796E50;
  v5 = (uint32_t *)a2;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0
    && sub_4E4630(this, a2)
    && (uint8_t)sub_5DB490(this) != 0
    && (uint8_t)a4 == 0 )
  {
    v6 = *this;
    *(this + 2110) = a2;
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(this, 39);
    v8 = sub_47E9D0(v7, 0);
    *(this + 2111) = sub_699000((int)(this + 9)) + v8;
  }
  v9 = *(this + 2060);
  if ( v9 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 80))(v9) != 0
    && (uint8_t)a4 == 0
    && sub_4E4630(this, a2) )
  {
    v10 = *(this + 1639);
    v11 = 0;
    if ( v10 == 8 && *(this + 2054) == -1 || v10 == 12 || v10 == 7 )
      v11 = 1;
    v50 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
    v12 = sub_47EF20(40, 3 - (v11 != 0), v50, -1, 11);
    sub_5DC590(v12);
  }
  v13 = *(this + 1639);
  switch ( v13 )
  {
    case 12:
      if ( *((uint8_t *)this + 8228) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WZ_DASH_HIT", -1, 0, 0);
        *((uint8_t *)this + 8228) = 1;
      }
      return sub_4AFB30(this, v5, (int)a3, a4);
    case 20:
      if ( *(this + 2129) != 20 || (uint8_t)a4 != 0 )
        return sub_4AFB30(this, v5, (int)a3, a4);
      v14 = 0;
      v62 = 0;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v15) = (uint8_t)this + 108;
        else
          v15 = *(this + 91);
        v14 = sub_431920(v15, (char)"Effect/Animation/WhipToMonsterHit.ani", 1);
      }
      v62 = 1;
      if ( sub_44B6C0(284) != 0 )
        v16 = (int *)sub_44E1F0(v14, 1);
      else
        v16 = nullptr;
      v17 = *(this + 29);
      v62 = -1;
      sub_45FE80(v17, (int)v16, 2, 0, (int)v16, a2, 0);
      v18 = *v16;
      v51 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 124))(a2, (uint64_t)(a3[5] * 0.5 + a3[2]));
      v19 = (uint64_t)(a3[3] * 0.5 + *a3);
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int))(v18 + 112))(v16, HIDWORD(v19), v19, v51);
      v20 = *v16;
      v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 660))(this, a2);
      v22 = sub_432E50(v21);
      (*(void (/*thiscall*/ **)(int *, int))(v20 + 148))(v16, v22);
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
      if ( v23 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 273) != 0 )
        {
          v62 = 2;
          if ( operator new(0x70u) != nullptr )
          {
            v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);
            v25 = (int *)sub_5DAFA0(0, v24);
          }
          else
          {
            v25 = nullptr;
          }
          v26 = *this;
          v27 = *v25;
          v55 = (int)v25;
          v62 = -1;
          v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(v26 + 1160))(this, 20, 1);
LABEL_42:
          sub_47E9D0(v28, v52);
          (*(void (/*thiscall*/ **)(int, int, int *, int, uint32_t, int))(v27 + 56))(v55, a2, this, 1, 0, 11);
          goto LABEL_43;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) != 0 )
        {
          v62 = 3;
          if ( operator new(0x70u) != nullptr )
          {
            v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);
            v30 = (int *)sub_5DAFA0(1, v29);
          }
          else
          {
            v30 = nullptr;
          }
          v27 = *v30;
          v55 = (int)v30;
          v31 = *this;
          v62 = -1;
          v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(v31 + 1160))(this, 20, 0);
          goto LABEL_42;
        }
      }
LABEL_43:
      v5 = (uint32_t *)a2;
      return sub_4AFB30(this, v5, (int)a3, a4);
    case 21:
      if ( *(this + 2134) != 14 || (uint8_t)a4 != 0 || *(this + 2133) != 1 )
        return sub_4AFB30(this, v5, (int)a3, a4);
      v33 = __RTDynamicCast(
              a2,
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &IRDActiveObject `RTTI Type Descriptor',
              0);
      v34 = v33;
      Block = (void *)v33;
      if ( v33 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v33 + 308))(v33) != 0 )
      {
        v35 = sub_4AED20(a2);
        v36 = *(uint32_t *)a2;
        v55 = 100;
        v37 = (*(int (/*thiscall*/ **)(int, int *, int *))(v36 + 648))(a2, &v55, this);
        if ( v35 == 0 && v37 == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v34 + 688))(v34) + 20) != 0 )
        {
          v38 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
          v39 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 14);
          v40 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
          v53 = sub_47EFD0(v38, COERCE_FLOAT(6), v39, v40, v40, 0);
          v41 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
          v42 = sub_47EFD0(v38, COERCE_FLOAT(5), v39, v41, v41, 0);
          v43 = sub_423A80(v42, v53, *(this + 2135), dword_9B9340);
          v44 = *(this + 2135);
          v56 = v43;
          v45 = 4;
          if ( v44 >= dword_9B9340 )
          {
            v57 = sub_47E9D0(v38, 4u);
            v58 = sub_47E9D0(v38, 3u);
            v46 = *this;
            v59 = 15;
            v47 = (*(int (/*thiscall*/ **)(int *))(v46 + 388))(this);
            v60 = sub_47EFD0(v38, COERCE_FLOAT(7), v39, v47, v47, 0);
            v45 = 14;
          }
          v48 = *this;
          v49 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*(uint32_t *)Block + 56))(
                  Block,
                  0,
                  0,
                  0,
                  0,
                  0,
                  4,
                  0,
                  v45,
                  &v56);
          (*(void (/*thiscall*/ **)(int *, int, int))(v48 + 580))(this, 48028, v49);
        }
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
      sub_47DCD0(this, -1);
      goto LABEL_43;
    default:
      break;
  }
  if ( v13 == 18
    && *(this + 2100) == 4
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 12);
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 13);
    sub_47E440(1);
  }
  return sub_4AFB30(this, v5, (int)a3, a4);
}


// ★★ 白魔 WZ 大型主状态机（1082L, 本工程最大函数）：switch(this+6556) 大状态分派
//   （case 6/10/16/17/18/19/20/21 可见）+ this+616 反应态 == -1 空闲门 + this+612 门；
//   内含 FollowMeCast.ani 召集/PRICK 刺击/HEAVEN_HIT 天击/MAGE_SWING/WZ_SWING 挥击/
//   LESSON_START + R_WZ_LESSON_START 教程语音（sub_431920+sub_431230+sub_699000+sub_47EF20）
//   —— 研究 15 三层状态架构（+200/+616/+6556）的最完整客户端样本
// ------------------------------------------------------------
// 0x5DE690 sub_5DE690
// ------------------------------------------------------------
void /*thiscall*/ sub_5DE690(int this)
{
  double v2; // st7
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // edi
  bool v9; // cc
  int v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // edi
  int *v14; // edi
  int v15; // ecx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  void *v31; // ecx
  int v32; // ecx
  bool v33; // cc
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // edi
  int v38; // eax
  int v39; // eax
  int v40; // edi
  int v41; // eax
  int v42; // edx
  int v43; // ebx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  void *v48; // ecx
  int *v49; // edi
  int v50; // eax
  int v51; // ecx
  int v52; // eax
  bool v53; // al
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // edi
  int v58; // ecx
  int v59; // eax
  int v60; // ebx
  uint32_t *v61; // ebx
  int v62; // eax
  int v63; // ebx
  int v64; // edi
  int v65; // eax
  int v66; // ebx
  int v67; // eax
  bool v68; // zf
  int v69; // eax
  char *v70; // edx
  uint32_t *v71; // edx
  int v72; // edi
  uint32_t *v73; // edx
  uint32_t *v74; // edx
  uint32_t *v75; // edx
  uint32_t *v76; // edx
  uint32_t *v77; // edx
  uint32_t *v78; // edx
  uint32_t *v79; // edx
  uint32_t *v80; // edx
  bool v81; // al
  int v82; // eax
  uint32_t *v83; // ebx
  int v84; // edi
  int v85; // ebx
  int v86; // eax
  int v87; // eax
  int v88; // eax
  int *v89; // ecx
  uint32_t *v90; // ecx
  char v91; // al
  uint32_t *v92; // edi
  int v93; // eax
  int v94; // ebx
  uint32_t *v95; // ebx
  char *v96; // edx
  uint32_t *v97; // edx
  int v98; // eax
  int v99; // eax
  char *v100; // ebx
  int v101; // eax
  char *v102; // ebx
  char *v103; // eax
  int v104; // eax
  int v105; // eax
  int v106; // eax
  int v107; // eax
  char v108; // [esp-4h] [ebp-58h]
  char v109; // [esp-4h] [ebp-58h]
  char v110[4]; // [esp+Ch] [ebp-48h] BYREF
  void *v111; // [esp+10h] [ebp-44h]
  int v112; // [esp+14h] [ebp-40h]
  int v113; // [esp+18h] [ebp-3Ch]
  char v114[4]; // [esp+1Ch] [ebp-38h] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  void *Src; // [esp+24h] [ebp-30h]
  int v117; // [esp+28h] [ebp-2Ch]
  int v118; // [esp+2Ch] [ebp-28h] BYREF
  int v119; // [esp+30h] [ebp-24h] BYREF
  int v120; // [esp+34h] [ebp-20h]
  int v121; // [esp+38h] [ebp-1Ch] BYREF
  int v122; // [esp+3Ch] [ebp-18h] BYREF
  int v123; // [esp+40h] [ebp-14h] BYREF
  bool v124; // [esp+47h] [ebp-Dh]
  int v125; // [esp+50h] [ebp-4h]

  sub_5DAC20();
  v2 = sub_5DAF10(this);
  sub_4B7430((int *)this, v2);
  if ( *(uint32_t *)(this + 8568) != -1 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
      && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)
      && (uint8_t)sub_4BFC10(this + 8116) == 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 0;
      v119 = 1;
      sub_431230(&v119);
      v119 = sub_699000(this + 36) - *(uint32_t *)(this + 8572);
      sub_431230(&v119);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v110, 0, 0);
      v125 = -1;
      sub_5E5260(v110);
    }
    v3 = *(uint32_t *)(this + 8580);
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
      {
        if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) + *(uint32_t *)(this + 8576)
          && *(uint32_t *)(this + 616) == -1 )
        {
          v5 = sub_5DA1E0(*(uint32_t *)(this + 8568));
          sub_4BA730(1, v5, 0, -*(uint32_t *)(this + 160));
          *(uint32_t *)(this + 8580) = 2;
        }
      }
      else if ( v3 == 2 && sub_699000(this + 36) >= *(uint32_t *)(this + 8576) + *(uint32_t *)(this + 8572) + 200 )
      {
        v6 = sub_699000(this + 36);
        v7 = sub_42B420(255, 220, -200 - *(uint32_t *)(this + 8576) - *(uint32_t *)(this + 8572) + v6, 100);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, v7);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 1, v7);
      }
    }
    else if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) && *(uint32_t *)(this + 616) == -1 )
    {
      v4 = sub_5DA1E0(*(uint32_t *)(this + 8568));
      sub_4BA730(0, v4, 0, -*(uint32_t *)(this + 160));
      *(uint32_t *)(this + 8580) = 1;
    }
  }
  switch ( *(uint32_t *)(this + 6556) )
  {
    case 0:
      if ( *(uint32_t *)(this + 8568) != -1 && *(uint32_t *)(this + 6644) != 0 )
        sub_5DACE0(this);
      break;
    case 7:
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        v9 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;
        goto LABEL_32;
      }
      break;
    case 8:
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        v8 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148);
        v9 = v8 < dword_738604[sub_41A5E0(this + 7028)];
        goto LABEL_32;
      }
      break;
    case 0xA:
      if ( *(uint32_t *)(this + 7812) == 0
        && *(uint32_t *)(this + 7828) == 0
        && *(uint32_t *)(this + 7816) == 11
        && *(uint32_t *)(this + 7808) == 1
        && *(int *)(*(uint32_t *)(this + 8428) + 148) >= 1 )
      {
        sub_5DB550(44, 60);
      }
      break;
    case 0xC:
      if ( *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 3 )
      {
        if ( *(uint8_t *)(this + 8228) != 0 )
        {
          sub_4AECE0(4);
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)this + 560))(this, 16, 0, 1, 0);
        }
      }
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        v9 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;
LABEL_32:
        if ( !v9 )
        {
          v10 = *(uint32_t *)this;
          v11 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
          (*(void (/*thiscall*/ **)(int, int))(v10 + 212))(this, v11);
          *(uint8_t *)(this + 8220) = 1;
        }
      }
      break;
    case 0xE:
      if ( *(uint32_t *)(this + 7964) == 30
        && *(uint8_t *)(this + 8376) == 0
        && *(int *)(*(uint32_t *)(this + 120) + 148) >= 2 )
      {
        v118 = sub_42FCB0(228);
        v125 = 1;
        if ( v118 != 0 )
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )
            LOBYTE(v12) = this + 108;
          else
            v12 = *(uint32_t *)(this + 364);
          v13 = sub_431920(v12, (char)"Effect/Animation/FollowMeCast.ani", 1);
        }
        else
        {
          v13 = 0;
        }
        v125 = -1;
        v118 = sub_44B6C0(284);
        v125 = 2;
        if ( v118 != 0 )
          v14 = (int *)sub_44E1F0(v13, 1);
        else
          v14 = nullptr;
        v15 = *(uint32_t *)(this + 116);
        v125 = -1;
        sub_45FE80(v15, (int)v14, 2, 0, (int)v14, 0, 0);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0 )
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 17;
        else
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 17;
        v17 = *v14;
        v119 = v16;
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v18 + 81);
        (*(void (/*thiscall*/ **)(int *, int, int))(v17 + 112))(v14, v119, v19);
        v20 = *v14;
        v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int *, int))(v20 + 148))(v14, v21);
        *(uint8_t *)(this + 8376) = 1;
      }
      break;
    case 0x12:
      if ( *(uint8_t *)(this + 8404) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 4 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "PRICK",
          -1,
          0,
          0);
        *(uint8_t *)(this + 8404) = 1;
      }
      break;
    case 0x13:
      if ( *(uint8_t *)(this + 8504) == 0 )
      {
        if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
              this,
              0,
              500,
              500,
              0,
              -1500,
              1);
            v37 = *(uint32_t *)this;
            v38 = sub_432E50(*(uint32_t *)(this + 8512));
            v39 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, v38);
            (*(void (/*thiscall*/ **)(int, int))(v37 + 896))(this, v39);
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "HEAVEN_HIT",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "WZ_HEAVEN_HIT",
            -1,
            0,
            0);
          *(uint8_t *)(this + 8504) = 1;
        }
        if ( *(uint8_t *)(this + 8504) == 0
          && fabs(*(float *)(*(uint32_t *)(this + 112) + 20)) >= 20.0
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8508) + 150 )
        {
          v40 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];
          v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          v42 = *(uint32_t *)this;
          v43 = *(uint32_t *)v40;
          v124 = v41 == 0;
          v44 = (*(int (/*thiscall*/ **)(int))(v42 + 128))(this);
          v45 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v44);
          v46 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v45);
          (*(void (/*thiscall*/ **)(int, int))(v43 + 40))(v40, v46);
          v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v40 + 28))(v40);
          *(uint8_t *)(v47 + 84) = v124;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v40 + 12))(v40, 0);
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v40 + 92))(v40, v114);
          v48 = *(void **)(this + 116);
          v125 = 4;
          sub_4600B0(v48, 2, 0, (int)v114);
          *(uint32_t *)(this + 8508) = sub_699000(this + 6560);
          v125 = -1;
          sub_5E5260(v114);
        }
      }
      break;
    case 0x14:
      if ( *(uint8_t *)(this + 8520) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 )
      {
        v36 = *(uint32_t *)(this + 8516);
        if ( v36 == 13 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "MAGE_SWING",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(
            this,
            "WZ_SWING",
            -1,
            0,
            0,
            v111,
            v112,
            v113);
        }
        else if ( v36 == 20 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "LESSON_START",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(
            this,
            "R_WZ_LESSON_START",
            -1,
            0,
            0,
            v111,
            v112,
            v113);
        }
        *(uint8_t *)(this + 8520) = 1;
      }
      break;
    case 0x15:
      v22 = *(uint32_t *)(this + 8532);
      if ( v22 != 0 )
      {
        if ( v22 == 1 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 10 )
          sub_5DB550(57, 63);
      }
      else
      {
        if ( fabs(*(float *)(*(uint32_t *)(this + 112) + 16)) >= 20.0
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8548) + 200 )
        {
          v23 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];
          v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          v124 = v24 == 0;
          if ( v24 != 0 )
            v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 20;
          else
            v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 20;
          v26 = *(uint32_t *)this;
          v27 = *(uint32_t *)v23;
          v119 = v25;
          v28 = (*(int (/*thiscall*/ **)(int))(v26 + 128))(this);
          v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v28);
          (*(void (/*thiscall*/ **)(int, int, int))(v27 + 40))(v23, v119, v29);
          v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 28))(v23);
          *(uint8_t *)(v30 + 84) = v124;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v23 + 12))(v23, 0);
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v23 + 92))(v23, v114);
          v31 = *(void **)(this + 116);
          v125 = 3;
          sub_4600B0(v31, 2, 0, (int)v114);
          *(uint32_t *)(this + 8548) = sub_699000(this + 6560);
          v125 = -1;
          sub_5E5260(v114);
        }
        v32 = *(uint32_t *)(this + 120);
        if ( *(int *)(v32 + 148) >= 7 && *(uint32_t *)(this + 8580) == 0 )
        {
          sub_4939E0(v32, 1);
          sub_4AECE0(7);
          sub_4939E0(*(uint32_t *)(this + 8544), 1);
          *(uint32_t *)(this + 8540) = sub_699000(this + 6560);
          sub_4BA610(4);
          sub_4BA730(0, 4, 0, -106);
          *(uint32_t *)(this + 8580) = 1;
        }
        v33 = *(uint32_t *)(this + 8580) < 1;
        if ( *(uint32_t *)(this + 8580) == 1 )
        {
          if ( sub_699000(this + 6560) >= dword_9B9340 + *(uint32_t *)(this + 8540) )
          {
            sub_4BA730(1, 4, 0, -106);
            *(uint32_t *)(this + 8580) = 2;
          }
          v33 = *(uint32_t *)(this + 8580) < 1;
        }
        if ( !v33 )
        {
          v34 = sub_699000(this + 6560);
          v35 = sub_42B420(150, 255, v34, 150);
          sub_491F80(-1, -1, -1, v35, 1);
        }
      }
      break;
    default:
      break;
  }
  if ( dword_8F7C04 == this && *(uint32_t *)(this + 200) != 2 )
  {
    if ( *(uint32_t *)(this + 6556) == 10 && *(uint32_t *)(this + 7812) == 0 )
    {
      if ( *(uint32_t *)(this + 7808) == 0
        && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 38) > 0
        && *(uint32_t *)(this + 7820) == -1
        && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)
        && ((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1132))(this, 0) != 4
         || (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1132))(this, 1) != 4) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
      }
      if ( *(uint32_t *)(this + 7808) == 1
        && *(uint8_t *)(this + 8584) != 0
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 )
      {
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
        v125 = 5;
        v119 = 2;
        sub_431230(&v119);
        v119 = 0;
        sub_431230(&v119);
        v119 = 0;
        sub_431230(&v119);
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 6, v110, 0, 0);
        v125 = -1;
        sub_5E5260(v110);
      }
    }
    if ( *(uint32_t *)(this + 6556) == 16 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 1, 0, 0, 0);
    v49 = (int *)&unk_795930;
    do
    {
      v50 = *(uint32_t *)(this + 6556);
      if ( (v50 == 0 || v50 == 11)
        && sub_4842B0(*v49, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, *v49) != 0 )
      {
        Block = nullptr;
        Src = nullptr;
        v117 = 0;
        v119 = *v49;
        v125 = 6;
        sub_431230(&v119);
        if ( *v49 == 30 )
        {
          v51 = *(uint32_t *)(this + 8372);
          if ( v51 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v51 + 80))(v51) != 0 )
          {
            v119 = 0;
            sub_431230(&v119);
          }
          else
          {
            v119 = 1;
            sub_431230(&v119);
          }
        }
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, v114, 0, 0);
        v125 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        Src = nullptr;
        v117 = 0;
      }
      ++v49;
    }
    while ( (int)v49 < (int)&dword_795948 );
    v52 = *(uint32_t *)(this + 6556);
    if ( (v52 == 4 || v52 == 3) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )
    {
      v53 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 8) == 0
         && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 16) == 0;
      v108 = v53;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);
      sub_47E440(v108);
      if ( sub_4842B0(3, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 3) != 0 )
      {
        v54 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);
        sub_5DCA10(v54);
      }
    }
    if ( *(uint32_t *)(this + 6556) == 17 && sub_699000(this + 6560) >= *(uint32_t *)(this + 8396) )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    v55 = *(uint32_t *)(this + 6556);
    if ( (v55 == 0 || v55 == 11)
      && sub_4842B0(4, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 4) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 7;
      v119 = 4;
      sub_431230(&v119);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 18, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 18 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    v56 = *(uint32_t *)(this + 6556);
    if ( v56 == 0 || v56 == 11 || v56 == 8 || v56 == 6 )
    {
      v57 = 0;
      v120 = 0;
      do
      {
        v58 = sub_4842B0(dword_7958E8[v57], (void *)(this + 8116));
        v59 = dword_7958E8[v57];
        v119 = v58;
        if ( v59 == 5 || v59 == 6 || v59 == 7 || v59 == 9 || v59 == 8 )
        {
          if ( v58 == -1 )
            goto LABEL_246;
          v60 = sub_5DC170(0);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[v57]);
          if ( v60 >= sub_47E9D0(1) )
          {
            v61 = *((uint32_t **)dword_8F8528 + 7);
            v62 = sub_422E70(1205);
            sub_43BEE0(v61, v62, -6567706, 0, -1);
            goto LABEL_246;
          }
          v58 = v119;
        }
        if ( v58 != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, dword_7958E8[v57]) != 0 )
        {
          v63 = v120;
          v64 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[v120]);
          v65 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, dword_7958E8[v63]);
          v66 = 0;
          v122 = 0;
          v123 = 0;
          v121 = 0;
          if ( v65 == -1 )
            v65 = sub_41A5E0(v64 + 510);
          v119 = sub_41A5E0(*(uint32_t *)(v64 + 316) + 14 * (v65 - 1));
          v67 = dword_7958E8[v120];
          switch ( v67 )
          {
            case 5:
            case 6:
            case 7:
            case 9:
            case 8:
            case 10:
              v69 = sub_47E9D0(0);
LABEL_197:
              v123 = 3;
LABEL_198:
              v66 = v69;
              v122 = v69;
              break;
            case 11:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 0;
              v121 = sub_47E9D0(3);
              break;
            case 15:
              v66 = sub_47E9D0(0);
              v68 = *(uint32_t *)(this + 6556) == 6;
              v122 = v66;
              v123 = 1;
              if ( v68 || (v121 = sub_47E9D0(1), *(uint32_t *)(this + 6556) == 6) )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 42);
                v119 = v119 * sub_47E9D0(2) / 100;
              }
              break;
            case 16:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 3;
              v121 = sub_47E9D0(5);
              break;
            case 17:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 2;
              v121 = sub_47E9D0(2);
              break;
            case 18:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 0;
              v121 = sub_47E9D0(1);
              break;
            case 26:
            case 27:
              v66 = sub_47E9D0(0);
              v123 = 1;
              v122 = v66;
              v121 = sub_47E9D0(2);
              break;
            case 28:
              v69 = sub_47E9D0(0);
              v123 = 2;
              goto LABEL_198;
            case 31:
              v66 = 10000;
              v123 = 3;
              v122 = 10000;
              v121 = sub_47E9D0(0);
              break;
            case 43:
              goto LABEL_195;
            case 49:
              v69 = sub_47E9D0(2);
              goto LABEL_197;
            case 50:
LABEL_195:
              v69 = sub_47E9D0(0);
              v123 = 0;
              goto LABEL_198;
            default:
              break;
          }
          Block = nullptr;
          Src = nullptr;
          v117 = 0;
          v125 = 8;
          v118 = 0;
          sub_430C80(nullptr, 1, (int)&v118);
          v70 = (char *)Src;
          v118 = 0;
          if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *(uint32_t *)Src = 0;
            v71 = v70 + 4;
            Src = v71;
          }
          else
          {
            sub_430C80(Src, 1, (int)&v118);
            v71 = Src;
          }
          v72 = dword_7958E8[v120];
          v118 = v72;
          if ( Block != nullptr && ((char *)v71 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v71 = v72;
            v73 = v71 + 1;
            Src = v73;
          }
          else
          {
            sub_430C80(v71, 1, (int)&v118);
            v73 = Src;
          }
          if ( Block != nullptr && ((char *)v73 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v73 = v119;
            v74 = v73 + 1;
            Src = v74;
          }
          else
          {
            sub_430C80(v73, 1, (int)&v119);
            v74 = Src;
          }
          if ( Block != nullptr && ((char *)v74 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v74 = v66;
            v75 = v74 + 1;
            Src = v75;
          }
          else
          {
            sub_430C80(v74, 1, (int)&v122);
            v75 = Src;
          }
          if ( Block != nullptr && ((char *)v75 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v75 = v123;
            v76 = v75 + 1;
            Src = v76;
          }
          else
          {
            sub_430C80(v75, 1, (int)&v123);
            v76 = Src;
          }
          v118 = 4;
          if ( Block != nullptr && ((char *)v76 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v76 = 4;
            v77 = v76 + 1;
            Src = v77;
          }
          else
          {
            sub_430C80(v76, 1, (int)&v118);
            v77 = Src;
          }
          v118 = 4;
          if ( Block != nullptr && ((char *)v77 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v77 = 4;
            v78 = v77 + 1;
            Src = v78;
          }
          else
          {
            sub_430C80(v77, 1, (int)&v118);
            v78 = Src;
          }
          if ( v121 > 0 || *(uint32_t *)(this + 6556) == 6 )
          {
            v118 = 1000;
            if ( Block != nullptr && ((char *)v78 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *v78 = 1000;
              v79 = v78 + 1;
              Src = v79;
            }
            else
            {
              sub_430C80(v78, 1, (int)&v118);
              v79 = Src;
            }
            v118 = 1000;
            if ( Block != nullptr && ((char *)v79 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *v79 = 1000;
              v80 = v79 + 1;
              Src = v80;
            }
            else
            {
              sub_430C80(v79, 1, (int)&v118);
              v80 = Src;
            }
            if ( Block != nullptr && ((char *)v80 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *v80 = v121;
              Src = v80 + 1;
            }
            else
            {
              sub_430C80(v80, 1, (int)&v121);
            }
            if ( *(uint32_t *)(this + 6556) == 6 )
            {
              v118 = 1;
              sub_431230(&v118);
            }
          }
          (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v114, 0, 0);
          v125 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          Src = nullptr;
          v117 = 0;
          v57 = v120;
        }
LABEL_246:
        v120 = ++v57;
      }
      while ( v57 < 18 );
    }
    v81 = *(uint32_t *)(this + 8444) != -1
       && *(uint32_t *)(this + 8440) != 0
       && sub_699000(this + 36) < *(uint32_t *)(this + 8444)
       && (uint8_t)sub_5DB490(this) != 0;
    v109 = v81;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 39);
    sub_47E440(v109);
    if ( sub_4842B0(39, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 39) != 0 )
    {
      sub_5DCE00(*(uint32_t *)(this + 8440));
    }
    v82 = *(uint32_t *)(this + 6556);
    if ( v82 == 0 || v82 == 11 )
    {
      v120 = (int)&unk_737FFC;
      do
      {
        if ( sub_4842B0(*(uint32_t *)v120, nullptr) != -1 )
        {
          v83 = (uint32_t *)v120;
          v84 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)v120);
          v85 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *v83);
          v119 = v85;
          v86 = sub_47E9D0(2);
          v118 = sub_5DD040(v86, 0, 1);
          v87 = sub_47EF20(2, v85, -1, -1, 11);
          if ( v118 < v87 )
          {
            if ( (int)sub_47E9D0(7) <= 0 || (v94 = sub_5DD040(60006, 0, 1)) >= sub_47E9D0(7) )
            {
              v95 = (uint32_t *)v120;
              if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1312))(this, *(uint32_t *)v120) != 0 )
              {
                Block = nullptr;
                Src = nullptr;
                v117 = 0;
                v125 = 9;
                v118 = 0;
                sub_430C80(nullptr, 1, (int)&v118);
                v96 = (char *)Src;
                v118 = 0;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = 0;
                  v97 = v96 + 4;
                  Src = v97;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&v118);
                  v97 = Src;
                }
                if ( Block != nullptr && ((char *)v97 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *v97 = *v95;
                  Src = v97 + 1;
                }
                else
                {
                  sub_430C80(v97, 1, (int)v95);
                }
                v98 = v119;
                if ( v119 == -1 )
                  v98 = sub_41A5E0(v84 + 510);
                v99 = sub_41A5E0(*(uint32_t *)(v84 + 316) + 14 * (v98 - 1));
                v100 = (char *)Src;
                v119 = v99;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = v119;
                  Src = v100 + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&v119);
                }
                v101 = sub_47E9D0(4);
                v102 = (char *)Src;
                v119 = v101;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = v119;
                  Src = v102 + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&v119);
                }
                v119 = sub_47E9D0(3);
                v103 = (char *)Src;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = v119;
                  Src = v103 + 4;
                }
                else
                {
                  sub_430FB0((int)&v118, Src, (int)&v119);
                }
                v118 = 4;
                sub_431230(&v118);
                v118 = 4;
                sub_431230(&v118);
                (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v114, 0, 0);
                v125 = -1;
                if ( Block != nullptr )
                  j__free(Block);
                Block = nullptr;
                Src = nullptr;
                v117 = 0;
              }
              goto LABEL_300;
            }
            v92 = *((uint32_t **)dword_8F8528 + 7);
            v93 = sub_422E70(2104);
          }
          else
          {
            v88 = sub_47E9D0(2);
            v89 = &dword_738020;
            while ( v88 != *v89 )
            {
              if ( (int)++v89 >= (int)&dword_738030 )
              {
                v90 = &unk_738040;
                while ( v88 != *v90 )
                {
                  if ( (int)++v90 >= (int)&dword_738044 )
                  {
                    v91 = 0;
                    goto LABEL_268;
                  }
                }
                break;
              }
            }
            v91 = 1;
LABEL_268:
            v92 = *((uint32_t **)dword_8F8528 + 7);
            v93 = sub_422E70(v91 != 0 ? 2103 : 1);
          }
          sub_43BEE0(v92, v93, -6567706, 0, -1);
        }
LABEL_300:
        v120 += 4;
      }
      while ( v120 < (int)&dword_738020 );
    }
    v104 = *(uint32_t *)(this + 6556);
    if ( (v104 == 0 || v104 == 11 || v104 == 8 || v104 == 18)
      && sub_4842B0(12, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 12) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 10;
      v118 = 12;
      sub_431230(&v118);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 19, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 19 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    v105 = *(uint32_t *)(this + 6556);
    if ( (v105 == 0 || v105 == 11 || v105 == 18)
      && sub_4842B0(13, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 13) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 11;
      v118 = 13;
      sub_431230(&v118);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    v106 = *(uint32_t *)(this + 6556);
    if ( (v106 == 0 || v106 == 11)
      && sub_4842B0(20, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 20) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 12;
      v118 = 20;
      sub_431230(&v118);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 20 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    v107 = *(uint32_t *)(this + 6556);
    if ( (v107 == 0 || v107 == 11 || v107 == 8 || v107 == 18)
      && sub_4842B0(14, (void *)(this + 8116)) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 14) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 13;
      v118 = 0;
      sub_431230(&v118);
      v118 = 14;
      sub_431230(&v118);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 21 )
    {
      if ( *(uint32_t *)(this + 8532) == 0
        && *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 7
        && (uint8_t)sub_4BFC10(this + 8116) == 0 )
      {
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
        v125 = 14;
        v118 = 1;
        sub_431230(&v118);
        v118 = sub_699000(this + 6560) - *(uint32_t *)(this + 8540);
        sub_431230(&v118);
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, v110, 0, 0);
        if ( sub_699000(this + 6560) == *(uint32_t *)(this + 8540) )
          sub_4BA730(2, 4, 0, 0);
        v125 = -1;
        if ( v111 != nullptr )
          j__free(v111);
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
      }
      if ( *(uint32_t *)(this + 8532) == 1 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}

