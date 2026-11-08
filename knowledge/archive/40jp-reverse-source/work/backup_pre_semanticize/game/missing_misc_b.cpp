// ============================================================
// 【40JP逆向源代码工程】game/missing_misc_b.cpp
// 模块: 0x51-0x53 区补漏（会话 5 精确审计后补齐，三轮审计合并）
// 来源: work/dump_missing-audit.txt  区块: 0x510000-0x540000（散装）
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 393
// ------------------------------------------------------------
// ★ 内容定性：主体为各主文件的构造/析构残件（vmt0 删除析构壳、析构基座、thunk 转发）
//   与【技能/机关 PO 构造器】（RTTI 虚表名直证：CNIceWave/CNEnergyField/CNSpiralNen/
//   CNVoid/CNLOLLaser/CNGhoulSkull/CNAraclothoMissile…，注释由虚表名自动标注）。
//   含 PO 构造基座 0x52EA60/0x52ED60（gunner_skills.cpp 全部机关 PO 的基座）与 0x52EE30。
// 音效 TAG/资源证据（本文件字符串字面量，P32/P36）：
//   G_MACHINEGUNA + Particle/ViperBulletShell.ptl（0x5324B0 机枪弹壳）
//   WAVE_CREATE（0x5312C0）/ WAVE_CANCLE（0x532E90）/ QUICK_TURN（0x5340A0）/
//   SIZZLE_LOOP（0x534470）/ SUN_BURST（0x533DD0）/ STONEBLADE_SWING_LOOP（0x534D70）/
//   DENDROID_DRIVE_02（0x535220）/ LAUNCH_FLUORESCENT（0x5334C0）/ VOID（0x5338B0）/
//   SAJAHU_SPREAD（0x52E590）/ PassiveObject/Monster/Spider/Particle/BossMissileSmog.ptl（0x535670）
// 注释体例：构造器/析构基座/thunk 由模式识别自动标注类名；带【】者为手写证据注释；
//   标注"散装小函数"者为无字符串/无名调用证据的 3-10 行残件【语义未逐行展开】。
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============
// 【分区 1】0x51 区残件（0x5149A0-0x51AB80，3 项）
// 装备 PO 虚表残片的 thunk/空桩（对应 po_effects.cpp 分区 4 的装备类）。
// ============

// 0x5149A0 sub_5149A0
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_5149A0()
{
  return sub_5149B0();
}



// ------------------------------------------------------------
// 0x519940 sub_519940
// ------------------------------------------------------------
// 薄转发 → sub_519940

void /*thiscall*/ sub_519940(uint32_t *this)
{
  *(this + 364) = 0;
}



// ------------------------------------------------------------
// 0x51AB80 sub_51AB80
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_51AB80()
{
  return sub_51A0F0();
}



// ------------------------------------------------------------
// ============
// 【分区 2】邮件 UI 残件（0x5226E0-0x523730）
// mail::MailFrame 的图标刷新/点击判定/页签切换辅助（pvp_ui.cpp 分区 2 邮件系统的散件）。
// ============

// 0x5226E0 sub_5226E0
// ------------------------------------------------------------
// 薄转发 → sub_5226E0

void sub_5226E0()
{
  byte_9B7E98 = 1;
}



// ------------------------------------------------------------
// 0x522760 sub_522760
// ------------------------------------------------------------
// 邮件图标区刷新：dword_8F8528[7]（邮件帧）→ +256 使能 → dword_79BE4C/79BE54 = 邮件数据
// → sub_4BF300(0,1) 重绘 + +136 按钮使能

int sub_522760()
{
  int v0; // eax
  int result; // eax

  v0 = *((uint32_t *)dword_8F8528 + 7);
  if ( *(uint8_t *)(v0 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v0 + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  sub_4BF300(0, 1);
  result = *((uint32_t *)dword_8F8528 + 7);
  *(uint8_t *)(*(uint32_t *)(result + 136) + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x522920 sub_522920
// ------------------------------------------------------------
// 邮件图标点击判定：项对象(+32) 非空 → vt+8(坐标,0,1) 拖拽启动 + pt 30×30 格命中

int /*thiscall*/ sub_522920(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // ecx
  int result; // eax
  int v7; // ecx

  v2 = *(this + 32);
  v3 = *(this + 37) + *(this + 5);
  v4 = *(this + 6) + *(this + 38);
  if ( *(int *)(v2 + 8) > 0 )
  {
    v5 = **(uint32_t **)(v2 + 12);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v5 + 8))(v5, v3, v4, 0, 1);
  }
  result = pt.x;
  v7 = *(this + 37) + *(this + 5);
  if ( pt.x >= v7 - 2 && pt.x < v7 + 30 )
  {
    result = *(this + 6) + *(this + 38);
    if ( pt.y >= result - 2 )
    {
      result += 30;
      if ( pt.y < result )
        return sub_4F2E40(v3, v4);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x522B20 sub_522B20
// ------------------------------------------------------------
// 邮件页签切换：a2 ∈ {0,1,2} 三页 → +40/+44 控件组显隐位（+16/+17）互斥切换

char /*thiscall*/ sub_522B20(int this, unsigned int a2)
{
  int *v2; // eax
  char result; // al
  int v4; // esi

  if ( a2 > 2 )
    return 0;
  v2 = *(int **)(this + 40);
  if ( a2 == 0 )
  {
    *(uint8_t *)(*v2 + 17) = 0;
    result = 1;
    *(uint8_t *)(**(uint32_t **)(this + 44) + 17) = 1;
    *(uint8_t *)(**(uint32_t **)(this + 44) + 16) = 1;
LABEL_4:
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 40) + 4) + 17) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 4) + 17) = 0;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 4) + 16) = 0;
    return result;
  }
  v4 = *v2;
  result = 1;
  *(uint8_t *)(v4 + 17) = 1;
  *(uint8_t *)(**(uint32_t **)(this + 44) + 17) = 0;
  *(uint8_t *)(**(uint32_t **)(this + 44) + 16) = 0;
  if ( a2 != 1 )
    goto LABEL_4;
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 40) + 4) + 17) = 0;
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 4) + 17) = 1;
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 4) + 16) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x522C60 sub_522C60
// ------------------------------------------------------------
// 散装补漏小函数（20L）【语义未逐行展开】

char /*cdecl*/ sub_522C60(int a1)
{
  int v1; // edi
  int v2; // edi
  const char *v3; // eax
  double v5; // [esp+0h] [ebp-98h]
  char Buffer[128]; // [esp+14h] [ebp-84h] BYREF
  int v7; // [esp+94h] [ebp-4h]

  v7 = dword_796E50;
  if ( a1 <= 0 )
    return 0;
  v1 = *((uint32_t *)dword_8F852C + 1);
  if ( a1 <= sub_484FA0() - v1 )
    return 0;
  v2 = *((uint32_t *)dword_8F852C + 1);
  v5 = (double)(a1 + v2 - sub_484FA0()) * 0.001;
  v3 = (const char *)sub_422E70(954);
  sprintf(Buffer, v3, v5);
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x522E20 sub_522E20
// ------------------------------------------------------------
// 散装补漏小函数（5L）【语义未逐行展开】

int sub_522E20()
{
  sub_423200(dword_8F7B08, 99);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x522EB0 sub_522EB0
// ------------------------------------------------------------
// 薄转发 → sub_522EB0

int /*thiscall*/ sub_522EB0(uint32_t *this)
{
  int v1; // eax
  int v2; // ecx

  v1 = *(this + 3);
  v2 = *(uint32_t *)(v1 + 4);
  if ( v2 != 0 )
    return (*(uint32_t *)(v1 + 8) - v2) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x5232E0 sub_5232E0
// ------------------------------------------------------------
// 散装补漏小函数（6L）【语义未逐行展开】

int /*thiscall*/ sub_5232E0(uint32_t *this)
{
  const char *v2; // eax

  sub_5227D0();
  v2 = (const char *)sub_69B740(*(this + 29));
  return j__atol(v2);
}



// ------------------------------------------------------------
// 0x523390 sub_523390
// ------------------------------------------------------------
// 散装补漏小函数（30L）【语义未逐行展开】

int /*cdecl*/ sub_523390(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax

  sub_44AC10(dword_8F8528);
  result = a1;
  switch ( a1 )
  {
    case 3:
    case 19:
      v2 = sub_422E70(2059);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v2, 0);
    case 10:
      v2 = sub_422E70(2060);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v2, 0);
    case 17:
      v2 = sub_422E70(2061);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v2, 0);
    case 23:
      v3 = sub_422E70(2062);
      return sub_522E90(v3);
    case 14:
      v4 = sub_422E70(2068);
      return sub_522E90(v4);
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5235E0 sub_5235E0
// ------------------------------------------------------------
// 散装补漏小函数（32L）【语义未逐行展开】

char /*thiscall*/ sub_5235E0(uint32_t *this)
{
  const char *v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ecx

  sub_5227D0();
  v2 = (const char *)sub_69B740(*(this + 29));
  if ( j__atol(v2) != 0 || *(int *)((v3 = *(this + 32)) + 8) > 0 && **(uint32_t **)(v3 + 12) != 0 )
  {
    v5 = *(this + 28);
    v6 = v5 + 160;
    if ( *(uint32_t *)(v5 + 192) != 0 )
      v6 = v5 + 180;
    if ( *(uint32_t *)(v6 + 12) == 0 || *(uint32_t *)(v5 + 192) != 0 && *(uint32_t *)(v5 + 188) != 0 )
    {
      v4 = sub_422E70(2053);
    }
    else
    {
      if ( (int)*(this + 42) >= 0 )
        return 1;
      v4 = sub_422E70(2066);
    }
  }
  else
  {
    v4 = sub_422E70(2054);
  }
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v4, 0);
  return 0;
}



// ------------------------------------------------------------
// 0x523730 sub_523730
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_523730(void *Block, char a2)
{
  sub_523690();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// ============
// 【分区 3】0x52E-0x53 区补漏 A：PO 构造基座 + 机关/技能 PO 族（0x52E560-0x535A50）
// PO 构造基座 0x52EA60/0x52ED60 与析构基座 0x52EE30（gunner_skills.cpp 各 PO 的三件套底座）；
// 大量技能/机关 PO 构造器（类名取自 RTTI 虚表赋值）；枪手系音效/粒子证据见文件头清单。
// ============

// 0x52E560 sub_52E560
// ------------------------------------------------------------
// 附属 vector 线性查找：+2/+3 首/尾，命中 *p==a2 → 1

char /*thiscall*/ sub_52E560(uint32_t *this, int a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // ecx

  v2 = (uint32_t *)*(this + 2);
  v3 = (uint32_t *)*(this + 3);
  if ( v2 == v3 )
    return 0;
  while ( *v2 != a2 )
  {
    if ( ++v2 == v3 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x52E6A0 sub_52E6A0
// ------------------------------------------------------------
// ★ map 操作大函数（211L）：std::map 插入/查找（异常串 "invalid map/set<T> iterator"）

int ***/*thiscall*/ sub_52E6A0(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v25; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  v25 = this;
  if ( *((uint8_t *)a3 + 21) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v26 = 0;
    sub_401740(pExceptionObject, (int)v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C5E0(&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    v7 = v25;
    v8 = v25[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
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
  if ( *((uint8_t *)v3[2] + 21) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v25[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)v3 + 20);
  *((uint8_t *)v3 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
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
            v15 = v25;
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
            v15 = v25;
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
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x52EA60 sub_52EA60
// ------------------------------------------------------------
// ★ CNRDTrap 构造基座（陷阱 PO 底座）：gunner_skills.cpp 全部机关 PO 构造器的第一调用

uint32_t */*thiscall*/ sub_52EA60(uint32_t *this, char ArgList, int a3)
{
  sub_4A4430();
  *this = &CNRDPassiveObject::`vftable';
  sub_4DF060(this + 170);
  *(this + 210) = 15;
  *(this + 209) = 0;
  *((uint8_t *)this + 820) = 0;
  sub_4A3450(this + 181);
  *(this + 235) = 15;
  *(this + 234) = 0;
  *((uint8_t *)this + 920) = 0;
  sub_5FF8E0(this);
  sub_6011B0(ArgList, a3);
  return this;
}



// ------------------------------------------------------------
// 0x52EB90 sub_52EB90
// ------------------------------------------------------------
// 薄转发 → sub_52EB90

int /*thiscall*/ sub_52EB90(void *this)
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this) != 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
  else
    return (int)this;
}



// ------------------------------------------------------------
// 0x52EBF0 sub_52EBF0
// ------------------------------------------------------------
// CNCutableGrass 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52EBF0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNCutableGrass::`vftable';
  *(this + 252) = 0;
  *(this + 253) = 0;
  *(this + 254) = 0;
  *(this + 256) = 0;
  *(this + 257) = 0;
  *(this + 258) = 0;
  sub_609A90(this);
  sub_60A310(this);
  return this;
}



// ------------------------------------------------------------
// 0x52ECC0 sub_52ECC0
// ------------------------------------------------------------
// CNCutableGrass 析构基座 → sub_4E2040

int /*thiscall*/ sub_52ECC0(int this)
{
  *(uint32_t *)this = &CNCutableGrass::`vftable';
  sub_609BA0();
  if ( *(uint32_t *)(this + 1024) != 0 )
    j__free(*(void **)(this + 1024));
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  if ( *(uint32_t *)(this + 1008) != 0 )
    j__free(*(void **)(this + 1008));
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x52EF30 sub_52EF30
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52EF30(void *Block, char a2)
{
  sub_52EE30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F000 sub_52F000
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F000(void *Block, char a2)
{
  sub_52F030();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F070 sub_52F070
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F070(void *Block, char a2)
{
  sub_52F0A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F130 sub_52F130
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F130(void *Block, char a2)
{
  sub_52F160();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F240 sub_52F240
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F240(void *Block, char a2)
{
  sub_52F270();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F340 sub_52F340
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F340(void *Block, char a2)
{
  sub_52F370();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F450 sub_52F450
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F450(void *Block, char a2)
{
  sub_52F480();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F540 sub_52F540
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F540(void *Block, char a2)
{
  sub_52F570();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F620 sub_52F620
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F620(void *Block, char a2)
{
  sub_52F650();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F700 sub_52F700
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F700(void *Block, char a2)
{
  sub_52F730();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F7E0 sub_52F7E0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F7E0(void *Block, char a2)
{
  sub_52F810();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F8D0 sub_52F8D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F8D0(void *Block, char a2)
{
  sub_52F900();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52F9B0 sub_52F9B0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52F9B0(void *Block, char a2)
{
  sub_52F9E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FA90 sub_52FA90
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FA90(void *Block, char a2)
{
  sub_52FAC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FB40 sub_52FB40
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FB40(void *Block, char a2)
{
  sub_52FB70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FC20 sub_52FC20
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FC20(void *Block, char a2)
{
  sub_52FC50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FD10 sub_52FD10
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FD10(void *Block, char a2)
{
  sub_52FD40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FDC0 sub_52FDC0
// ------------------------------------------------------------
// 散装补漏小函数（13L）【语义未逐行展开】

int /*thiscall*/ sub_52FDC0(void *this, int a2, int a3, int a4)
{
  int v5; // ebx
  int v6; // eax

  v5 = sub_600AF0(a2, a3, a4);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( *(uint8_t *)(v6 + 16) != 0 || *(float *)v6 > 0.0 )
  {
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 596))(this, 0);
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 604))(this, 0);
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 84))(this, 0);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x52FEC0 sub_52FEC0
// ------------------------------------------------------------
// CNThrowItemDestroyable 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FEC0(void **this)
{
  *this = &off_707ACC;
  nullsub_3(this);
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FFE0 sub_52FFE0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FFE0(void *Block, char a2)
{
  sub_52FF80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5300A0 sub_5300A0
// ------------------------------------------------------------
// CNCreateOnDestroyObject 析构基座 → sub_4E2040

int /*thiscall*/ sub_5300A0(void **this)
{
  *this = &CNCreateOnDestroyObject::`vftable';
  nullsub_3(this);
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530190 sub_530190
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530190(void *Block, char a2)
{
  sub_5301C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530230 sub_530230
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530230(void *Block, char a2)
{
  sub_530260();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5302D0 sub_5302D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5302D0(void *Block, char a2)
{
  sub_530300();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5303B0 sub_5303B0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5303B0(void *Block, char a2)
{
  sub_5303E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5304C0 sub_5304C0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5304C0(void *Block, char a2)
{
  sub_5304F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530560 sub_530560
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530560(void *Block, char a2)
{
  sub_530590();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530660 sub_530660
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530660(void *Block, char a2)
{
  sub_530690();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530780 sub_530780
// ------------------------------------------------------------
// CNCircleAppendageMaker 析构基座 → sub_4E2040

int /*thiscall*/ sub_530780(void **this)
{
  *this = &CNCircleAppendageMaker::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530830 sub_530830
// ------------------------------------------------------------
// 散装补漏小函数（18L）【语义未逐行展开】

int /*thiscall*/ sub_530830(uint32_t *this)
{
  uint32_t *v2; // edi
  int result; // eax

  sub_600890();
  v2 = (uint32_t *)*(this + 36);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( result == *v2 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x530930 sub_530930
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530930(void *Block, char a2)
{
  sub_530960();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5309D0 sub_5309D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5309D0(void *Block, char a2)
{
  sub_530A00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530AC0 sub_530AC0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530AC0(void *Block, char a2)
{
  sub_530AF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530BB0 sub_530BB0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530BB0(void *Block, char a2)
{
  sub_530BE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530CD0 sub_530CD0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530CD0(void *Block, char a2)
{
  sub_530D00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530DB0 sub_530DB0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530DB0(void *Block, char a2)
{
  sub_530DE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530FA0 sub_530FA0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530FA0(void *Block, char a2)
{
  sub_530FD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5310F0 sub_5310F0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5310F0(void *Block, char a2)
{
  sub_531120();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531230 sub_531230
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531230(void *Block, char a2)
{
  sub_531260();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531330 sub_531330
// ------------------------------------------------------------
// ★ 技能特效初始化（浮点参数）：sub_47E720(0,20) 效果表项 →
// sub_47EF20(2, 状态176, -1,-1, 11)（P38-4 状态 stat 读取）×0.01 →
// sub_4920E0(×,×) 缩放（P11 火花放大同款）+ sub_4921E0 → sub_47EFD0(1,...) →
// +972 已播标志 + +724 存值

char /*thiscall*/ sub_531330(void *this, float a2)
{
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  float v7; // [esp+Ch] [ebp+8h]

  sub_5FFD50(LODWORD(a2));
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 20);
    v7 = (double)(int)sub_47EF20(2, *((uint32_t *)this + 176), -1, -1, 11) * 0.0099999998;
    sub_4920E0(*((uint32_t **)this + 34), v7, v7);
    sub_4921E0(v7);
    v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
    v3 = sub_47EFD0(v4, COERCE_FLOAT(1), *((uint32_t *)this + 176), v5, v5, 0);
    *((uint8_t *)this + 972) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x531420 sub_531420
// ------------------------------------------------------------
// CNIceWave 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531420(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNIceWave::`vftable';
  sub_6129A0(this);
  sub_612B10(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x531500 sub_531500
// ------------------------------------------------------------
// CNSuplexSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531500(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNSuplexSub::`vftable';
  sub_612F70(this);
  sub_6056A0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5315E0 sub_5315E0
// ------------------------------------------------------------
// CNEnergyBall 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5315E0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNEnergyBall::`vftable';
  sub_61BE30(this);
  sub_613590(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x5316C0 sub_5316C0
// ------------------------------------------------------------
// CNEnergyBallSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_5316C0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNEnergyBallSub::`vftable';
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x531800 sub_531800
// ------------------------------------------------------------
// CNEnergyBallSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_531800(void **this)
{
  *this = &CNEnergyBallSub::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5318A0 sub_5318A0
// ------------------------------------------------------------
// CNThrowSand 析构基座 → sub_4E2040

int /*thiscall*/ sub_5318A0(void **this)
{
  *this = &CNThrowSand::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531970 sub_531970
// ------------------------------------------------------------
// ★ 同族特效初始化：sub_47E720(1,15) → sub_47EF20(0/1/2, 状态) 三项 stat ×0.1 →
// sub_4921E0 + sub_47EFD0(3,...) → +972 置位（+760/+772 存值）

char /*thiscall*/ sub_531970(int *this, float a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  float v11; // [esp+Ch] [ebp+8h]

  sub_5FFD50(LODWORD(a2));
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(1, 15);
    v5 = *(this + 176);
    v6 = v4;
    v11 = (double)(int)sub_47EF20(0, v5, -1, -1, 11) * 0.0099999998;
    sub_4921E0(v11);
    *((float *)this + 190) = (double)(int)sub_47EF20(1, v5, -1, -1, 11) * 0.1;
    v7 = sub_47EF20(2, v5, -1, -1, 11);
    v8 = *this;
    *(this + 193) = v7;
    v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(3), v5, v9, v9, 0);
    *((uint8_t *)this + 972) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x531A80 sub_531A80
// ------------------------------------------------------------
// CNEnergyField 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531A80(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNEnergyField::`vftable';
  sub_607240(this + 243);
  sub_607280(this + 243);
  sub_6137F0(this);
  sub_6139F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x531B90 sub_531B90
// ------------------------------------------------------------
// CNBlastBlood 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531B90(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBlastBlood::`vftable';
  sub_607240(this + 243);
  sub_607280(this + 243);
  sub_613A10(this);
  sub_613B70(a3);
  return this;
}



// ------------------------------------------------------------
// 0x531CA0 sub_531CA0
// ------------------------------------------------------------
// CNBlastBloodSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531CA0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBlastBloodSub::`vftable';
  sub_607240(this + 243);
  sub_607280(this + 243);
  nullsub_3(this);
  sub_613CE0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x531DB0 sub_531DB0
// ------------------------------------------------------------
// CNGhost 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531DB0(uint32_t *this, char a2, int a3, int a4)
{
  int v5; // eax

  sub_52EA60(this, a2, a3);
  *this = &CNGhost::`vftable';
  sub_607240(this + 250);
  sub_607280(this + 250);
  v5 = sub_433AC0(this + 259);
  *(this + 260) = v5;
  *(uint8_t *)(v5 + 21) = 1;
  *(uint32_t *)(*(this + 260) + 4) = *(this + 260);
  *(uint32_t *)*(this + 260) = *(this + 260);
  *(uint32_t *)(*(this + 260) + 8) = *(this + 260);
  *(this + 261) = 0;
  sub_613F40(this);
  sub_614460(a4, a3);
  return this;
}



// ------------------------------------------------------------
// 0x531F30 sub_531F30
// ------------------------------------------------------------
// CNFireWave 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531F30(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNFireWave::`vftable';
  sub_614F90(this);
  sub_6152E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x532010 sub_532010
// ------------------------------------------------------------
// CNSpiralNen 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532010(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNSpiralNen::`vftable';
  sub_607240(this + 243);
  sub_607280(this + 243);
  sub_6154A0(this);
  sub_6154C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x532120 sub_532120
// ------------------------------------------------------------
// CNClosePunchSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532120(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNClosePunchSub::`vftable';
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  sub_6156D0(this);
  sub_6056A0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x532250 sub_532250
// ------------------------------------------------------------
// CNGunnerBullet 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532250(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGunnerBullet::`vftable';
  sub_607330(this);
  sub_6073B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x532330 sub_532330
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532330(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGunnerSubWeaponBullet::`vftable';
  sub_607240(this + 248);
  sub_607280(this + 248);
  sub_608EE0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x532440 sub_532440
// ------------------------------------------------------------
// CNExsViperBullet 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_532440(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNExsViperBullet::`vftable';
  sub_5FF8E0(this);
  *(uint32_t *)(this + 972) = 0;
  *(float *)(this + 724) = (float)a3;
  return this;
}



// ------------------------------------------------------------
// 0x532650 sub_532650
// ------------------------------------------------------------
// CNExsViperBullet 析构基座 → sub_4E2040

int /*thiscall*/ sub_532650(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNExsViperBullet::`vftable';
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 972);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 972) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x532750 sub_532750
// ------------------------------------------------------------
// CNGunnerLaser 析构基座 → sub_4E2040

int /*thiscall*/ sub_532750(void **this)
{
  *this = &CNGunnerLaser::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532860 sub_532860
// ------------------------------------------------------------
// CNNenGuard 析构基座 → sub_4E2040

int /*thiscall*/ sub_532860(int this)
{
  int v3; // [esp-8h] [ebp-24h]
  int *v4; // [esp-4h] [ebp-20h]
  uint8_t v5[4]; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+Ch] [ebp-10h]
  int v7; // [esp+18h] [ebp-4h]

  v6 = this;
  *(uint32_t *)this = &CNNenGuard::`vftable';
  v7 = 2;
  nullsub_3(this);
  v4 = *(int **)(this + 1012);
  v3 = *v4;
  LOBYTE(v7) = 1;
  sub_52E960(v5, v3, v4);
  j__free(*(void **)(this + 1012));
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 972) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 976) = 0;
  v7 = -1;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x532990 sub_532990
// ------------------------------------------------------------
// CNTombStoneRain 析构基座 → sub_4E2040

int /*thiscall*/ sub_532990(void **this)
{
  *this = &CNTombStoneRain::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532A70 sub_532A70
// ------------------------------------------------------------
// CNTombStone 析构基座 → sub_4E2040

int /*thiscall*/ sub_532A70(void **this)
{
  *this = &CNTombStone::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532B50 sub_532B50
// ------------------------------------------------------------
// CNDropBomb 析构基座 → sub_4E2040

int /*thiscall*/ sub_532B50(void **this)
{
  *this = &CNDropBomb::`vftable';
  sub_60C870();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532C70 sub_532C70
// ------------------------------------------------------------
// CNTreadShootSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_532C70(int this)
{
  *(uint32_t *)this = &CNTreadShootSub::`vftable';
  nullsub_3(this);
  *(uint32_t *)(this + 976) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 980) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x532D60 sub_532D60
// ------------------------------------------------------------
// CNAshenForkSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_532D60(void **this)
{
  *this = &CNAshenForkSub::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532E40 sub_532E40
// ------------------------------------------------------------
// CNGrabBlastBlood 析构基座 → sub_4E2040

int /*thiscall*/ sub_532E40(void **this)
{
  *this = &CNGrabBlastBlood::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532F30 sub_532F30
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532F30(void *Block, char a2)
{
  sub_532F60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532FD0 sub_532FD0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532FD0(void *Block, char a2)
{
  sub_533000();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5330B0 sub_5330B0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5330B0(void *Block, char a2)
{
  sub_5330E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5331A0 sub_5331A0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5331A0(void *Block, char a2)
{
  sub_5331D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533280 sub_533280
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533280(void *Block, char a2)
{
  sub_5332B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533360 sub_533360
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533360(void *Block, char a2)
{
  sub_533390();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533440 sub_533440
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533440(void *Block, char a2)
{
  sub_533470();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533540 sub_533540
// ------------------------------------------------------------
// 散装补漏小函数（37L）【语义未逐行展开】

int /*thiscall*/ sub_533540(int *this, uint16_t *a2, size_t Size)
{
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-20h]
  float v12; // [esp+0h] [ebp-20h]
  float v13; // [esp+4h] [ebp-1Ch]
  float v14; // [esp+4h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-4h]
  int v16; // [esp+1Ch] [ebp-4h]
  uint16_t v17; // [esp+28h] [ebp+8h]
  size_t Sizea; // [esp+2Ch] [ebp+Ch]
  size_t Sizeb; // [esp+2Ch] [ebp+Ch]

  sub_5FFF80((int)a2, Size);
  v17 = *a2;
  v4 = (char *)sub_47E720(3, 17);
  v5 = *(this + 176);
  v6 = v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v15 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v13 = (float)sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  v11 = (float)v15;
  *(this + 183) += (uint64_t)sub_4049C0(v11, v13, v17, 1000) - 100;
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v16 = sub_47EFD0(v6, COERCE_FLOAT(4), v5, v8, v8, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(5), v5, Sizeb, Sizeb, 0);
  v12 = (float)v16;
  v9 = (uint64_t)sub_4049C0(v12, v14, v17, 1000);
  HIDWORD(v9) = *this;
  *((float *)this + 181) = (double)(100 * (int)v9 / (*(this + 183) + 100)) + *((float *)this + 181);
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x5336C0 sub_5336C0
// ------------------------------------------------------------
// CNThrowWeb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_5336C0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNThrowWeb::`vftable';
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5337C0 sub_5337C0
// ------------------------------------------------------------
// CNThrowWeb 析构基座 → sub_4E2040

int /*thiscall*/ sub_5337C0(void **this)
{
  *this = &CNThrowWeb::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533860 sub_533860
// ------------------------------------------------------------
// CNLaunchBlackCat 析构基座 → sub_4E2040

int /*thiscall*/ sub_533860(void **this)
{
  *this = &CNLaunchBlackCat::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533A00 sub_533A00
// ------------------------------------------------------------
// 散装补漏小函数（53L）【语义未逐行展开】

int /*thiscall*/ sub_533A00(int *this, uint16_t *a2, size_t Size)
{
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  float v10; // edx
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+0h] [ebp-24h]
  float v14; // [esp+0h] [ebp-24h]
  float v15; // [esp+4h] [ebp-20h]
  float v16; // [esp+4h] [ebp-20h]
  float v17; // [esp+4h] [ebp-20h]
  int v18; // [esp+1Ch] [ebp-8h]
  int v19; // [esp+1Ch] [ebp-8h]
  int v20; // [esp+20h] [ebp-4h]
  uint16_t v21; // [esp+2Ch] [ebp+8h]
  int v22; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  float Sizec; // [esp+30h] [ebp+Ch]

  sub_5FFF80((int)a2, Size);
  v21 = *a2;
  v4 = (char *)sub_47E720(3, 26);
  v5 = *(this + 176);
  v6 = v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v18 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v20 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  Sizeb = v21;
  v15 = (float)v20;
  v12 = (float)v18;
  *(this + 183) += (uint64_t)sub_4049C0(v12, v15, v21, 1000) - 100;
  v22 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v19 = sub_47EFD0(v6, COERCE_FLOAT(6), v5, v8, v8, 0);
  v16 = (float)sub_47EFD0(v6, COERCE_FLOAT(7), v5, v22, v22, 0);
  v13 = (float)v19;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v13, v16, Sizeb, 1000))
                                  / (*(this + 183) + 100))
                         + *((float *)this + 181);
  v17 = (float)(int)sub_47EF20(5, v5, -1, -1, 11);
  v14 = (float)(int)sub_47EF20(4, v5, -1, -1, 11);
  Sizec = sub_4049C0(v14, v17, Sizeb, 1000) * 0.001;
  sub_4922F0(Sizec);
  sub_4922F0(Sizec);
  v9 = sub_47E9D0(v6, 1u);
  v10 = *(float *)this;
  *(this + 244) = v9;
  return (*(int (/*thiscall*/ **)(int *, int *))(LODWORD(v10) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x533C10 sub_533C10
// ------------------------------------------------------------
// CNHalloweenBuster 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533C10(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNHalloweenBuster::`vftable';
  sub_61A4E0(this);
  sub_61ABD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x533CF0 sub_533CF0
// ------------------------------------------------------------
// CNHalloweenBusterSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533CF0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNHalloweenBusterSub::`vftable';
  sub_61A520(this);
  sub_61ACA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x533DD0 sub_533DD0
// ------------------------------------------------------------
// 【音效 TAG 实证 SUN_BURST】9L：阳光爆发 PO 触发音（联动 gunner_skills.cpp CNSunBurst）

int /*thiscall*/ sub_533DD0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNSunBurst::`vftable';
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  sub_4015C0("SUN_BURST", 9u);
  return this;
}



// ------------------------------------------------------------
// 0x534060 sub_534060
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534060(void *Block, char a2)
{
  sub_534090();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534110 sub_534110
// ------------------------------------------------------------
// ★ 机关触发主逻辑（50L）：vt+684/vt+128/vt+308 门 → sub_47E720(3,43) +
// sub_47EF20(3, 状态) → 效果施加（P38-4 状态 stat 链）

char /*thiscall*/ sub_534110(uint8_t *this)
{
  int v2; // eax
  int *v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v10; // [esp+4h] [ebp-4h]

  sub_600890();
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
    if ( v2 == 0 )
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
      if ( (uint8_t)v2 != 0 )
      {
        LOBYTE(v2) = *(this + 156);
        if ( (uint8_t)v2 != 0 )
        {
          sub_47E720(3, 43);
          v10 = sub_47EF20(3, *((uint32_t *)this + 176), -1, -1, 11);
          v3 = (int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this);
          v4 = *v3;
          v5 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                 this,
                 0,
                 0,
                 0,
                 0xFFFF,
                 0,
                 1,
                 0,
                 *((uint32_t *)this + 176));
          v6 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, int))(*(uint32_t *)this + 124))(this, 0, v5);
          v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v6);
          v8 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)this + 376))(this, v10, v7);
          (*(void (/*thiscall*/ **)(int *, int, int))(v4 + 592))(v3, 60010, v8);
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
        }
      }
    }
  }
  else
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5343A0 sub_5343A0
// ------------------------------------------------------------
// CNProvocationDollCreater 析构基座 → sub_4E2040

int /*thiscall*/ sub_5343A0(void **this)
{
  *this = &CNProvocationDollCreater::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5344A0 sub_5344A0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5344A0(void *Block, char a2)
{
  sub_5344D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5345E0 sub_5345E0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5345E0(void *Block, char a2)
{
  sub_534610();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5346C0 sub_5346C0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5346C0(void *Block, char a2)
{
  sub_5346F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534760 sub_534760
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534760(void *Block, char a2)
{
  sub_534790();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534800 sub_534800
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534800(void *Block, char a2)
{
  sub_534830();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5348A0 sub_5348A0
// ------------------------------------------------------------
// CNKagelBombSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5348A0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNKagelBombSub::`vftable';
  sub_6106A0(this);
  sub_61C860(this);
  return this;
}



// ------------------------------------------------------------
// 0x534990 sub_534990
// ------------------------------------------------------------
// CNSpaceFishBug 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534990(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNSpaceFishBug::`vftable';
  nullsub_3(this);
  sub_61CB60(a3);
  ++dword_9B9414;
  return this;
}



// ------------------------------------------------------------
// 0x534A90 sub_534A90
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

unsigned int */*thiscall*/ sub_534A90(unsigned int *this, int a2, unsigned int a3)
{
  sub_52EB30(a2, a3);
  *this = (unsigned int)&CNSpaceFishJoint::`vftable';
  *(this + 252) = a3;
  sub_5B3E00(this);
  return this;
}



// ------------------------------------------------------------
// 0x534B80 sub_534B80
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534B80(void *Block, char a2)
{
  sub_534BB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534C20 sub_534C20
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534C20(void *Block, char a2)
{
  sub_534C50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534CC0 sub_534CC0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534CC0(void *Block, char a2)
{
  sub_534CF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534D70 sub_534D70
// ------------------------------------------------------------
// 【音效 TAG 实证 STONEBLADE_SWING_LOOP】23L：石刃挥舞循环音（石化刃机关）

char /*thiscall*/ sub_534D70(uint8_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax

  sub_600890();
  LOBYTE(v2) = *(this + 972);
  if ( (uint8_t)v2 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "STONEBLADE_SWING_LOOP",
      44578,
      0,
      0);
    v3 = *(uint32_t *)this;
    *(this + 972) = 1;
    v4 = (*(int (/*thiscall*/ **)(uint8_t *))(v3 + 576))(this);
    v2 = __RTDynamicCast(v4, 0, &IRDActiveObject `RTTI Type Descriptor', &CNStoneBlade_Razor `RTTI Type Descriptor', 0);
    if ( v2 != 0 )
      LOBYTE(v2) = sub_4DB130(24, 0);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x534E40 sub_534E40
// ------------------------------------------------------------
// CNStoneBlade 析构基座 → sub_4E2040

int /*thiscall*/ sub_534E40(void **this)
{
  *this = &CNStoneBlade::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534F10 sub_534F10
// ------------------------------------------------------------
// CNLegOfLotus 析构基座 → sub_4E2040

int /*thiscall*/ sub_534F10(void **this)
{
  char v1; // al

  v1 = *((uint8_t *)this + 972);
  *this = &CNLegOfLotus::`vftable';
  if ( v1 != 0 && dword_9B9418 > 0 )
    --dword_9B9418;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534FD0 sub_534FD0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534FD0(void *Block, char a2)
{
  sub_535000();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535040 sub_535040
// ------------------------------------------------------------
// ★ 机关触发（57L）：a2==self && vt+340()==30031（状态 ID）&& vt+576() → 存活/坐标 → 效果

int /*thiscall*/ sub_535040(void *this, void *a2)
{
  int v3; // eax
  int v4; // eax
  int i; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  int v13; // [esp-1Ch] [ebp-24h]
  int v14; // [esp-18h] [ebp-20h]
  int v15; // [esp-14h] [ebp-1Ch]
  int v16; // [esp+4h] [ebp-4h]

  if ( a2 == this
    && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 340))(this) == 30031
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this) >= 0 )
        v3 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
      else
        v3 = 0;
      v15 = v3;
      v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
      v13 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
      v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
      sub_4E4A50(v4, 30033, 0, v13, v14, v15, 4, 0, 0, 0);
    }
    for ( i = 0; ; i = v16 + 1 )
    {
      v16 = i;
      v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
      v7 = *(uint32_t *)(v6 + 120);
      v8 = v6 + 116;
      v9 = v7 != 0 ? (*(uint32_t *)(v8 + 8) - v7) >> 2 : 0;
      if ( i >= v9 )
        break;
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
      v10 = sub_425A00(i);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 88))(v10) != 0
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 33) != 0
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 340))(v10) == 30031
        && (*(int (/*thiscall*/ **)(void *, int, uint32_t))(*(uint32_t *)this + 8))(this, v10, 0) < 50 )
      {
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 128))(v10);
        if ( (int)abs32((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this) - v11) < 50
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 308))(v10) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v10 + 312))(v10, 0);
        }
      }
    }
  }
  return sub_600790(a2);
}



// ------------------------------------------------------------
// 0x5351F0 sub_5351F0
// ------------------------------------------------------------
// CNDendroidNeedle 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_5351F0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNDendroidNeedle::`vftable';
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5352C0 sub_5352C0
// ------------------------------------------------------------
// CNDendroidNeedle 析构基座 → sub_4E2040

int /*thiscall*/ sub_5352C0(void **this)
{
  *this = &CNDendroidNeedle::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535390 sub_535390
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535390(void *Block, char a2)
{
  sub_5353C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535410 sub_535410
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535410(void *Block, char a2)
{
  sub_535440();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5354D0 sub_5354D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5354D0(void *Block, char a2)
{
  sub_535500();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535560 sub_535560
// ------------------------------------------------------------
// CNGhoulSkullBomb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_535560(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNGhoulSkullBomb::`vftable';
  *(uint32_t *)(this + 972) = sub_699000(this + 36);
  *(uint8_t *)(this + 976) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x535630 sub_535630
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535630(void *Block, char a2)
{
  sub_535660();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535780 sub_535780
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535780(void *Block, char a2)
{
  sub_5357B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535880 sub_535880
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535880(void *Block, char a2)
{
  sub_5358B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535960 sub_535960
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535960(void *Block, char a2)
{
  sub_535990();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535A50 sub_535A50
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535A50(void *Block, char a2)
{
  sub_535A80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// ============
// 【分区 4】第二轮审计补漏（0x514AD0-0x535A80，散装按审计序排列）
// 与分区 3 同主题的残件补齐：构造/析构对、虚表转发薄壳、容器/字符串辅助。
// ============

// 0x514AD0 sub_514AD0
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_514AD0()
{
  return sub_510960();
}



// ------------------------------------------------------------
// 0x51A240 sub_51A240
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_51A240()
{
  return sub_51A250();
}



// ------------------------------------------------------------
// 0x51AC70 sub_51AC70
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_51AC70()
{
  return sub_510DB0();
}



// ------------------------------------------------------------
// 0x5226F0 sub_5226F0
// ------------------------------------------------------------
// 散装补漏小函数（14L）【语义未逐行展开】

int /*stdcall*/ sub_5226F0(uint32_t *a1)
{
  int result; // eax
  char v2; // [esp+0h] [ebp-4h]

  result = a1[48];
  if ( result != 0 )
  {
    result = a1[47];
    if ( result != 0 )
      result = sub_69BD90((int)a1, (char *)szPassword, v2);
  }
  dword_79BE4C = a1[3];
  dword_79BE54 = dword_79BE4C;
  return result;
}



// ------------------------------------------------------------
// 0x5227B0 sub_5227B0
// ------------------------------------------------------------
// 薄转发 → sub_5227B0

int /*thiscall*/ sub_5227B0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 32);
  if ( *(int *)(v1 + 8) <= 0 )
    return 0;
  else
    return **(uint32_t **)(v1 + 12);
}



// ------------------------------------------------------------
// 0x5229C0 sub_5229C0
// ------------------------------------------------------------
// 散装补漏小函数（40L）【语义未逐行展开】

char /*thiscall*/ sub_5229C0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  v2 = *(this + 32);
  if ( *(int *)(v2 + 8) <= 0 )
    v8 = 0;
  else
    v8 = **(uint32_t **)(v2 + 12);
  v3 = *(this + 6);
  v4 = *(this + 37) + *(this + 5);
  if ( pt.x >= v4 - 2
    && pt.x < v4 + 30
    && (v5 = v3 + *(this + 38), pt.y >= v5 - 2)
    && pt.y < v5 + 30
    && (LOBYTE(v6) = v8, v8 != 0) )
  {
    if ( dword_9B88D0 != v8 || dword_795378 != 12 )
    {
      v6 = sub_44E8D0((char *)dword_8F8528, (void *)0x1A, v8, 12);
      if ( v6 != 0 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v6 + 48))(
                       v6,
                       *(this + 5) + *(this + 37),
                       *(this + 38) + *(this + 6),
                       28,
                       28);
    }
  }
  else
  {
    LOBYTE(v6) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 12 )
      LOBYTE(v6) = sub_44E850(dword_8F8528, 26);
  }
  return v6;
}



// ------------------------------------------------------------
// 0x522BC0 sub_522BC0
// ------------------------------------------------------------
// 散装补漏小函数（17L）【语义未逐行展开】

int /*thiscall*/ sub_522BC0(int *this)
{
  int i; // esi
  int v3; // eax
  int result; // eax

  if ( *(uint32_t *)(*(this + 4) + 2504) != 2 )
    sub_69A650(*(this + 2));
  for ( i = 0; i < 2; ++i )
  {
    v3 = *(uint32_t *)(*(this + 10) + 4 * i);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
      sub_522B20(i);
  }
  result = *(this + 12);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  return result;
}



// ------------------------------------------------------------
// 0x522D20 sub_522D20
// ------------------------------------------------------------
// 散装补漏小函数（6L）【语义未逐行展开】

int /*cdecl*/ sub_522D20(int a1)
{
  sub_423200(dword_8F7B08, 98);
  sub_423290(&a1, 4);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x522E50 sub_522E50
// ------------------------------------------------------------
// 散装补漏小函数（12L）【语义未逐行展开】

int /*cdecl*/ sub_522E50(int a1)
{
  int result; // eax
  int v2; // eax

  result = sub_44AC10(dword_8F8528);
  if ( a1 == 22 )
  {
    v2 = sub_422E70(2064);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1C, v2, 0);
    return sub_44ABF0(dword_8F8528);
  }
  return result;
}



// ------------------------------------------------------------
// 0x522ED0 sub_522ED0
// ------------------------------------------------------------
// 散装补漏小函数（18L）【语义未逐行展开】

void /*thiscall*/ sub_522ED0(Concurrency::details::ExternalContextBase *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  int v5; // eax

  Concurrency::details::ExternalContextBase::SpinYield(this);
  v2 = *((uint32_t *)this + 27);
  if ( v2 != 0 )
  {
    v3 = *((uint32_t *)this + 28);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    {
      v4 = *(uint32_t *)(v2 + 40);
      if ( v4 == 0 || (v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 36))(v4), (uint8_t)sub_522C60(v5) == 0) )
        sub_522D20(*(uint32_t *)(*((uint32_t *)this + 27) + 4));
    }
  }
}



// ------------------------------------------------------------
// 0x523300 sub_523300
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

char /*thiscall*/ sub_523300(uint32_t **this, int a2, int a3)
{
  sub_69A5F0(*(this + 2), 34, 74);
  if ( (uint8_t)sub_522B20(a3) == 0 )
    return 0;
  sub_44BBA0(0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x523420 sub_523420
// ------------------------------------------------------------
// 散装补漏小函数（114L）【语义未逐行展开】

int /*thiscall*/ sub_523420(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  unsigned int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // edi
  unsigned int v24; // eax
  int v25; // edi
  int v26; // edi
  int v27; // [esp+4h] [ebp-8h]
  int v28; // [esp+8h] [ebp-4h]

  result = *(this + 27);
  if ( result != 0 )
  {
    v3 = *(this + 5);
    v4 = *(this + 6);
    v27 = v3;
    v28 = *(uint32_t *)(result + 44);
    if ( v28 != 0 )
    {
      if ( dword_9B7E94 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_9B7E94 + 152))(
          dword_9B7E94,
          v3 + 42,
          v4 + 19,
          dword_79C0B0);
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
      v5 = *(this + 27);
      v6 = *(uint32_t *)(v5 + 36);
      v7 = v5 + 12;
      if ( v6 < 0x10 )
        v8 = v7 + 4;
      else
        v8 = *(uint32_t *)(v7 + 4);
      v9 = v3 + 45;
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v9,
        v4 + 3,
        -9795152,
        v8);
      v10 = *(this + 27);
      v11 = *(uint32_t *)(v10 + 36);
      v12 = v10 + 12;
      if ( v11 < 0x10 )
        v13 = v12 + 4;
      else
        v13 = *(uint32_t *)(v12 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v9,
        v4 + 2,
        -16179413,
        v13);
      v14 = *(uint32_t *)dword_79C0B0;
      v15 = sub_5486B0(v28);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v14 + 80))(dword_79C0B0, v27 + 61, v4 + 21, -9795152, v15);
      v16 = *(uint32_t *)dword_79C0B0;
      v17 = sub_5486B0(v28);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v16 + 80))(dword_79C0B0, v27 + 61, v4 + 20, -16179413, v17);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
      v18 = *(this + 27);
      v19 = *(uint32_t *)(v18 + 36);
      v20 = v18 + 12;
      if ( v19 < 0x10 )
        v21 = v20 + 4;
      else
        v21 = *(uint32_t *)(v20 + 4);
      v22 = v3 + 45;
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v22,
        v4 + 14,
        -9795152,
        v21);
      v23 = *(this + 27);
      v24 = *(uint32_t *)(v23 + 36);
      v25 = v23 + 12;
      if ( v24 < 0x10 )
        v26 = v25 + 4;
      else
        v26 = *(uint32_t *)(v25 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v22,
        v4 + 13,
        -16179413,
        v26);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x523690 sub_523690
// ------------------------------------------------------------
// 散装补漏小函数（13L）【语义未逐行展开】

void /*thiscall*/ sub_523690(void *this)
{
  int v2; // ecx

  *(uint32_t *)this = &mail::Mail::`vftable';
  v2 = *((uint32_t *)this + 10);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 4))(v2, 1);
  *((uint32_t *)this + 10) = 0;
  if ( *((uint32_t *)this + 9) >= 0x10u )
    j__free(*((void **)this + 4));
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 15;
  *((uint8_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x523760 sub_523760
// ------------------------------------------------------------
// 散装补漏小函数（33L）【语义未逐行展开】

char /*thiscall*/ sub_523760(uint32_t *this, int a2)
{
  int v3; // eax
  uint32_t *v4; // edx
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  int v7; // ecx
  int v9; // edi

  if ( a2 < 0 )
    return 0;
  v3 = *(this + 3);
  v4 = *(uint32_t **)(v3 + 4);
  if ( v4 == nullptr || a2 >= (unsigned int)((*(uint32_t *)(v3 + 8) - (int)v4) >> 2) )
    return 0;
  v5 = *(uint32_t **)(v3 + 8);
  v6 = v4;
  v7 = 0;
  if ( v4 == v5 )
    return 0;
  while ( v7 != a2 || v6 == v5 )
  {
    ++v6;
    ++v7;
    if ( v6 == v5 )
      return 0;
  }
  if ( *v6 != 0 )
    (**(void (/*thiscall*/ ***)(uint32_t, int))*v6)(*v6, 1);
  v9 = *(this + 3);
  memcpy_0(v6, v6 + 1, 4 * ((*(uint32_t *)(v9 + 8) - (int)(v6 + 1)) >> 2));
  *(uint32_t *)(v9 + 8) -= 4;
  byte_9B7E98 = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x52E590 sub_52E590
// ------------------------------------------------------------
// 【音效 TAG 实证 SAJAHU_SPREAD】26L：按 a2 索引构造 TAG 串并播放（P32 链）【技能语义待验证】

size_t */*thiscall*/ sub_52E590(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  int v4; // ecx

  v3 = (uint32_t *)*(this + 36);
  *((float *)this + 181) = (float)a2;
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(this, 2, *v3, 0, 0, 0, 1);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
    this,
    1,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    1);
  v4 = *(this + 36);
  if ( v4 != 0 && (unsigned int)((*(this + 37) - v4) >> 2) > 2 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(v4 + 8),
      0,
      0,
      0,
      0);
  return sub_4015C0(this + 229, "SAJAHU_SPREAD", 0xDu);
}



// ------------------------------------------------------------
// 0x52E960 sub_52E960
// ------------------------------------------------------------
// 散装补漏小函数（58L）【语义未逐行展开】

int **/*thiscall*/ sub_52E960(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int *v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_52E4D0(*(void **)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = v5;
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_52E6A0(&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x52EB00 sub_52EB00
// ------------------------------------------------------------
// CNRDPooledPassiveObject 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52EB00(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNRDPooledPassiveObject::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x52EBB0 sub_52EBB0
// ------------------------------------------------------------
// CNRDJoint 析构基座 → sub_4E2040

int /*thiscall*/ sub_52EBB0(void **this)
{
  *this = &CNRDJoint::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52EC80 sub_52EC80
// ------------------------------------------------------------
// 薄转发 → sub_52EC80

void /*thiscall*/ sub_52EC80(uint32_t *this)
{
  ++*(this + 244);
}



// ------------------------------------------------------------
// 0x52ED60 sub_52ED60
// ------------------------------------------------------------
// ★ CNPassiveObject/CNMapObject 构造基座（与 0x52EA60 平行的第二底座）

uint32_t */*thiscall*/ sub_52ED60(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNMapObject::`vftable';
  *(this + 251) = 0;
  *(this + 252) = 0;
  *(this + 253) = 0;
  `eh vector constructor iterator'(this + 258, 4u, 3, sub_432D20, (void (/*thiscall*/ *)(void *))sub_401060);
  *(this + 262) = 0;
  *(this + 263) = 0;
  *(this + 264) = 0;
  *(this + 266) = 0;
  *(this + 267) = 0;
  *(this + 268) = 0;
  *(this + 270) = 0;
  *(this + 271) = 0;
  *(this + 272) = 0;
  sub_60AA00(this);
  sub_60B3D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x52EF60 sub_52EF60
// ------------------------------------------------------------
// CNTreasureBox 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52EF60(uint32_t *this, char a2, int a3)
{
  sub_52ED60(this, a2, a3);
  *this = &CNTreasureBox::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x52F030 sub_52F030
// ------------------------------------------------------------
// CNTreasureBox 析构基座 → sub_52EE30

int /*thiscall*/ sub_52F030(uint32_t *this)
{
  *this = &CNTreasureBox::`vftable';
  return sub_52EE30();
}



// ------------------------------------------------------------
// 0x52F0A0 sub_52F0A0
// ------------------------------------------------------------
// CNUrn 析构基座 → sub_52EE30

int /*thiscall*/ sub_52F0A0(uint32_t *this)
{
  *this = &CNUrn::`vftable';
  return sub_52EE30();
}



// ------------------------------------------------------------
// 0x52F160 sub_52F160
// ------------------------------------------------------------
// CNPathGate 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F160(int this)
{
  *(uint32_t *)this = &CNPathGate::`vftable';
  sub_577F30();
  if ( *(uint32_t *)(this + 980) != 0 )
    j__free(*(void **)(this + 980));
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x52F270 sub_52F270
// ------------------------------------------------------------
// CNFireMissile 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F270(void **this)
{
  *this = &CNFireMissile::`vftable';
  sub_60B8F0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F370 sub_52F370
// ------------------------------------------------------------
// CNFireExplosion 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F370(int this)
{
  *(uint32_t *)this = &CNFireExplosion::`vftable';
  sub_60BC20();
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x52F480 sub_52F480
// ------------------------------------------------------------
// CNIceMissile 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F480(void **this)
{
  *this = &CNIceMissile::`vftable';
  sub_60B8F0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F570 sub_52F570
// ------------------------------------------------------------
// CNThunderBolt 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F570(void **this)
{
  *this = &CNThunderBolt::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F650 sub_52F650
// ------------------------------------------------------------
// CNParticleFactory 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F650(void **this)
{
  *this = &CNParticleFactory::`vftable';
  sub_60C870();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F730 sub_52F730
// ------------------------------------------------------------
// CNBlast 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F730(void **this)
{
  *this = &CNBlast::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F810 sub_52F810
// ------------------------------------------------------------
// CNEarthQuake 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F810(void **this)
{
  *this = &CNEarthQuake::`vftable';
  sub_60D0E0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F900 sub_52F900
// ------------------------------------------------------------
// CNDangerousGas 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F900(void **this)
{
  *this = &CNDangerousGas::`vftable';
  sub_60C870();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52F9E0 sub_52F9E0
// ------------------------------------------------------------
// CNIceNiddleGroup 析构基座 → sub_4E2040

int /*thiscall*/ sub_52F9E0(void **this)
{
  *this = &CNIceNiddleGroup::`vftable';
  sub_60D7C0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FAC0 sub_52FAC0
// ------------------------------------------------------------
// CNIceNiddle 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FAC0(void **this)
{
  *this = &CNIceNiddle::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FB70 sub_52FB70
// ------------------------------------------------------------
// CNEarthFire 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FB70(void **this)
{
  *this = &CNEarthFire::`vftable';
  sub_60D940();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FC50 sub_52FC50
// ------------------------------------------------------------
// CNShootingStar 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FC50(void **this)
{
  *this = &CNShootingStar::`vftable';
  sub_61A500();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FD40 sub_52FD40
// ------------------------------------------------------------
// CNShootingStarExp 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FD40(void **this)
{
  *this = &CNShootingStarExp::`vftable';
  sub_60DD90();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x52FE30 sub_52FE30
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

uint32_t */*thiscall*/ sub_52FE30(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &off_707ACC;
  sub_60E100(this);
  sub_60E230(this);
  return this;
}



// ------------------------------------------------------------
// 0x52FF20 sub_52FF20
// ------------------------------------------------------------
// CNBouncer 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52FF20(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBouncer::`vftable';
  sub_60E260(this);
  sub_60E5D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x530010 sub_530010
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

int /*thiscall*/ sub_530010(int this, char a2, int a3)
{
  sub_52FF20((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNBouncerLooseSerimalion::`vftable';
  *(uint8_t *)(this + 981) = 0;
  *(uint8_t *)(this + 984) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x530100 sub_530100
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_530100(void *Block, char a2)
{
  sub_5300A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5301C0 sub_5301C0
// ------------------------------------------------------------
// CNFlyBombSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_5301C0(void **this)
{
  *this = &CNFlyBombSub::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530260 sub_530260
// ------------------------------------------------------------
// CNSunkenRock 析构基座 → sub_4E2040

int /*thiscall*/ sub_530260(void **this)
{
  *this = &CNSunkenRock::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530300 sub_530300
// ------------------------------------------------------------
// CNRedRock 析构基座 → sub_4E2040

int /*thiscall*/ sub_530300(void **this)
{
  *this = &CNRedRock::`vftable';
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5303E0 sub_5303E0
// ------------------------------------------------------------
// CNDollMasterBubble 析构基座 → sub_4E2040

int /*thiscall*/ sub_5303E0(void **this)
{
  *this = &CNDollMasterBubble::`vftable';
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5304F0 sub_5304F0
// ------------------------------------------------------------
// CNMagicTargetWarning 析构基座 → sub_4E2040

int /*thiscall*/ sub_5304F0(void **this)
{
  *this = &CNMagicTargetWarning::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530590 sub_530590
// ------------------------------------------------------------
// CNTemporaryHit 析构基座 → sub_4E2040

int /*thiscall*/ sub_530590(void **this)
{
  *this = &CNTemporaryHit::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530690 sub_530690
// ------------------------------------------------------------
// CNForceField 析构基座 → sub_4E2040

int /*thiscall*/ sub_530690(int this)
{
  *(uint32_t *)this = &CNForceField::`vftable';
  nullsub_3(this);
  if ( *(uint32_t *)(this + 1016) >= 0x10u )
    j__free(*(void **)(this + 996));
  *(uint32_t *)(this + 1016) = 15;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x5307D0 sub_5307D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5307D0(void *Block, char a2)
{
  sub_530780();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x530880 sub_530880
// ------------------------------------------------------------
// 散装补漏小函数（29L）【语义未逐行展开】

char /*thiscall*/ sub_530880(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax

  sub_600880();
  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
  if ( v2 != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 376))(v3);
    v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
    if ( v2 != v4 )
    {
      v5 = (uint32_t *)*(this + 36);
      v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      if ( v2 != *v5 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
        sub_4938F0(v6);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
        LOBYTE(v2) = sub_491F80(v7, -1, -1, -1, 0, 1);
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x530960 sub_530960
// ------------------------------------------------------------
// 散装补漏小函数（4L）【语义未逐行展开】

int /*thiscall*/ sub_530960(uint32_t *this)
{
  *this = &CNBombMine::`vftable';
  return sub_5300A0();
}



// ------------------------------------------------------------
// 0x530A00 sub_530A00
// ------------------------------------------------------------
// CNToothSFish 析构基座 → sub_4E2040

int /*thiscall*/ sub_530A00(void **this)
{
  *this = &CNToothSFish::`vftable';
  sub_5FF980();
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530AF0 sub_530AF0
// ------------------------------------------------------------
// CNToothKurokuta 析构基座 → sub_4E2040

int /*thiscall*/ sub_530AF0(void **this)
{
  *this = &CNToothKurokuta::`vftable';
  sub_5FF980();
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530BE0 sub_530BE0
// ------------------------------------------------------------
// CNCurseBombSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_530BE0(void **this)
{
  *this = &CNCurseBombSub::`vftable';
  sub_61EFD0();
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530D00 sub_530D00
// ------------------------------------------------------------
// CNSummonMonsterWithEffect 析构基座 → sub_4E2040

int /*thiscall*/ sub_530D00(void **this)
{
  *this = &CNSummonMonsterWithEffect::`vftable';
  sub_610A80();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530DE0 sub_530DE0
// ------------------------------------------------------------
// CNBodyHit 析构基座 → sub_4E2040

int /*thiscall*/ sub_530DE0(void **this)
{
  *this = &CNBodyHit::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530FD0 sub_530FD0
// ------------------------------------------------------------
// CNTrackingIceWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_530FD0(int this)
{
  *(uint32_t *)this = &CNTrackingIceWave::`vftable';
  sub_6119C0();
  *(uint32_t *)(this + 1064) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1068) = 0;
  *(uint32_t *)(this + 1036) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1008) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 980) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x531120 sub_531120
// ------------------------------------------------------------
// CNSingleIceWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_531120(void **this)
{
  *this = &CNSingleIceWave::`vftable';
  nullsub_3(this);
  nullsub_3(this + 248);
  nullsub_3(this + 243);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531260 sub_531260
// ------------------------------------------------------------
// CNEventBarrier 析构基座 → sub_52EE30

int /*thiscall*/ sub_531260(uint32_t *this)
{
  *this = &CNEventBarrier::`vftable';
  nullsub_3(this);
  *(this + 278) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 1116) = 0;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5313E0 sub_5313E0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5313E0(void *Block, char a2)
{
  sub_531410();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531480 sub_531480
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531480(void *Block, char a2)
{
  sub_5314B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531560 sub_531560
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531560(void *Block, char a2)
{
  sub_531590();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531640 sub_531640
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531640(void *Block, char a2)
{
  sub_531670();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5316F0 sub_5316F0
// ------------------------------------------------------------
// 同 0x531330 族特效初始化（28L float 变体）

char /*thiscall*/ sub_5316F0(void *this, float a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  uint64_t v7; // rax
  int v8; // eax
  float v10; // [esp+Ch] [ebp+8h]

  sub_5FFD50(LODWORD(a2));
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(1, 12);
    v5 = *((uint32_t *)this + 176);
    v6 = v4;
    v10 = (double)(int)sub_47EF20(4, v5, -1, -1, 11) * 0.0099999998;
    sub_4922F0(v10);
    *((float *)this + 190) = (double)(int)sub_47EF20(2, v5, -1, -1, 11) * 0.1;
    v7 = (uint64_t)(double)(int)sub_47EF20(3, v5, -1, -1, 11);
    HIDWORD(v7) = *(uint32_t *)this;
    *((uint32_t *)this + 193) = v7;
    v8 = (*(int (/*thiscall*/ **)(void *))(HIDWORD(v7) + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, v8, v8, 0);
    *((uint8_t *)this + 972) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x531810 sub_531810
// ------------------------------------------------------------
// CNThrowSand 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531810(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNThrowSand::`vftable';
  sub_62DC30(this);
  sub_6137D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5318F0 sub_5318F0
// ------------------------------------------------------------
// CNRoarStun 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_5318F0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNRoarStun::`vftable';
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x531A40 sub_531A40
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531A40(void *Block, char a2)
{
  sub_531A70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531B00 sub_531B00
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531B00(void *Block, char a2)
{
  sub_531B30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531C10 sub_531C10
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531C10(void *Block, char a2)
{
  sub_531C40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531D20 sub_531D20
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531D20(void *Block, char a2)
{
  sub_531D50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531E60 sub_531E60
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531E60(void *Block, char a2)
{
  sub_531E90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531F90 sub_531F90
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531F90(void *Block, char a2)
{
  sub_531FC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532090 sub_532090
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532090(void *Block, char a2)
{
  sub_5320C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5321A0 sub_5321A0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5321A0(void *Block, char a2)
{
  sub_5321D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5322B0 sub_5322B0
// ------------------------------------------------------------
// 散装补漏小函数（6L）【语义未逐行展开】

void */*thiscall*/ sub_5322B0(void *this, char a2)
{
  sub_5322E0();
  if ( (a2 & 1) != 0 )
    sub_657740(this, 1040);
  return this;
}



// ------------------------------------------------------------
// 0x5323B0 sub_5323B0
// ------------------------------------------------------------
// 散装补漏小函数（6L）【语义未逐行展开】

void */*thiscall*/ sub_5323B0(void *this, char a2)
{
  sub_5323E0();
  if ( (a2 & 1) != 0 )
    sub_657740(this, 1012);
  return this;
}



// ------------------------------------------------------------
// 0x5324B0 sub_5324B0
// ------------------------------------------------------------
// ★ 机枪弹壳 PO 处理（56L）【资源实证 G_MACHINEGUNA + Particle/ViperBulletShell.ptl】：
// vt+212 播 "G_MACHINEGUNA"（P32）→ sub_4C3640("Particle/ViperBulletShell.ptl") 弹壳粒子
// 发射器挂接（P36 发射器）—— 拦截射弹/机枪抛壳演出

void /*thiscall*/ sub_5324B0(int *this)
{
  void *v2; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  void *v10; // ecx
  int v11; // eax
  int v12; // edx
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  void *v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+20h] [ebp-4h]

  sub_600890();
  if ( *(this + 243) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "G_MACHINEGUNA", -1, 0, 0);
    v2 = operator new(0x12Cu);
    v15 = v2;
    v16 = 0;
    if ( v2 != nullptr )
    {
      if ( (unsigned int)*(this + 96) < 0x10 )
        v3 = (int *)sub_4C3640((int)v2, (int)(this + 91), (int)"Particle/ViperBulletShell.ptl", (int)this);
      else
        v3 = (int *)sub_4C3640((int)v2, *(this + 91), (int)"Particle/ViperBulletShell.ptl", (int)this);
    }
    else
    {
      v3 = nullptr;
    }
    *(this + 243) = (int)v3;
    v4 = *v3;
    v16 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v4 + 12))(v3, 0);
    v5 = *(uint32_t *)*(this + 243);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6 + 21);
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, v7 + 1) != 0 ? -72 : 72;
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v5 + 40))(*(this + 243), v9 + v8);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v13);
    v10 = (void *)*(this + 29);
    v16 = 1;
    sub_4600B0(v10, 2, 0, (int)v13);
    v11 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104));
    v12 = *this;
    *(float *)&v15 = (double)*(int *)(v11 + 76) * 0.0174532925199433;
    (*(void (/*thiscall*/ **)(int *, int, void *))(v12 + 272))(this, 1, v15);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x5326C0 sub_5326C0
// ------------------------------------------------------------
// CNGunnerLaser 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5326C0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGunnerLaser::`vftable';
  sub_5FF8E0(this);
  sub_615890(a3);
  return this;
}



// ------------------------------------------------------------
// 0x532760 sub_532760
// ------------------------------------------------------------
// CNNenGuard 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_532760(int this, char a2, int a3)
{
  int v4; // eax

  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNNenGuard::`vftable';
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = &off_6C2B88;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 1;
  *(uint8_t *)(this + 986) = 0;
  *(uint8_t *)(this + 985) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 988) = 0;
  v4 = sub_433AC0(this + 1008);
  *(uint32_t *)(this + 1012) = v4;
  *(uint8_t *)(v4 + 21) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 1012) + 4) = *(uint32_t *)(this + 1012);
  **(uint32_t **)(this + 1012) = *(uint32_t *)(this + 1012);
  *(uint32_t *)(*(uint32_t *)(this + 1012) + 8) = *(uint32_t *)(this + 1012);
  *(uint32_t *)(this + 1016) = 0;
  sub_615C90(this);
  sub_615D10(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x532900 sub_532900
// ------------------------------------------------------------
// CNTombStoneRain 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532900(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNTombStoneRain::`vftable';
  sub_616130(this);
  sub_616160(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5329E0 sub_5329E0
// ------------------------------------------------------------
// CNTombStone 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5329E0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNTombStone::`vftable';
  sub_616500(this);
  sub_616670(this);
  return this;
}



// ------------------------------------------------------------
// 0x532AC0 sub_532AC0
// ------------------------------------------------------------
// CNDropBomb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532AC0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNDropBomb::`vftable';
  sub_6166D0(this);
  sub_616A10(this);
  return this;
}



// ------------------------------------------------------------
// 0x532BA0 sub_532BA0
// ------------------------------------------------------------
// CNTreadShootSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_532BA0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNTreadShootSub::`vftable';
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 976) = &off_6C2B88;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 1;
  *(uint8_t *)(this + 990) = 0;
  *(uint8_t *)(this + 989) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 992) = 0;
  sub_616D80(this);
  sub_616AD0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x532CD0 sub_532CD0
// ------------------------------------------------------------
// CNAshenForkSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532CD0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNAshenForkSub::`vftable';
  sub_6166D0(this);
  sub_616C60(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x532DB0 sub_532DB0
// ------------------------------------------------------------
// CNGrabBlastBlood 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532DB0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGrabBlastBlood::`vftable';
  sub_616D80(this);
  sub_616E80(a3);
  return this;
}



// ------------------------------------------------------------
// 0x532E90 sub_532E90
// ------------------------------------------------------------
// 【音效 TAG 实证 WAVE_CANCLE】7L：波/机关取消时播 "WAVE_CANCLE"（原拼写如此）

int /*thiscall*/ sub_532E90(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(float *)(this + 724) = (float)a3;
  *(uint32_t *)this = &CNReleaseWave::`vftable';
  sub_4015C0((size_t *)(this + 916), "WAVE_CANCLE", 0xBu);
  return this;
}



// ------------------------------------------------------------
// 0x532F60 sub_532F60
// ------------------------------------------------------------
// CNReleaseWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_532F60(void **this)
{
  *this = &CNReleaseWave::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533000 sub_533000
// ------------------------------------------------------------
// CNGrandWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_533000(void **this)
{
  *this = &CNGrandWave::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5330E0 sub_5330E0
// ------------------------------------------------------------
// CNDecoy 析构基座 → sub_4E2040

int /*thiscall*/ sub_5330E0(void **this)
{
  *this = &CNDecoy::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5331D0 sub_5331D0
// ------------------------------------------------------------
// CNChaser 析构基座 → sub_4E2040

int /*thiscall*/ sub_5331D0(void **this)
{
  *this = &CNChaser::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5332B0 sub_5332B0
// ------------------------------------------------------------
// CNMagicMissile 析构基座 → sub_4E2040

int /*thiscall*/ sub_5332B0(void **this)
{
  *this = &CNMagicMissile::`vftable';
  sub_618930();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533390 sub_533390
// ------------------------------------------------------------
// CNLaunchJOL 析构基座 → sub_4E2040

int /*thiscall*/ sub_533390(void **this)
{
  *this = &CNLaunchJOL::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533470 sub_533470
// ------------------------------------------------------------
// CNLaunchFrostHead 析构基座 → sub_4E2040

int /*thiscall*/ sub_533470(void **this)
{
  *this = &CNLaunchFrostHead::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533680 sub_533680
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533680(void *Block, char a2)
{
  sub_5336B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5336F0 sub_5336F0
// ------------------------------------------------------------
// 散装补漏小函数（21L）【语义未逐行展开】

char /*thiscall*/ sub_5336F0(void *this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax

  sub_5FFD50(a2);
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(1, 52);
    v5 = *((uint32_t *)this + 176);
    v6 = v4;
    v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
    *((float *)this + 181) = (float)sub_47EFD0(v6, COERCE_FLOAT(2), v5, v7, v7, 0);
    *((float *)this + 190) = (double)(int)sub_47EF20(0, v5, -1, -1, 11) * 0.1;
    v3 = sub_47EF20(1, v5, -1, -1, 11);
    *((uint32_t *)this + 193) = v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x5337D0 sub_5337D0
// ------------------------------------------------------------
// CNLaunchBlackCat 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5337D0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNLaunchBlackCat::`vftable';
  sub_619DB0(this);
  sub_61A400(this);
  return this;
}



// ------------------------------------------------------------
// 0x5338B0 sub_5338B0
// ------------------------------------------------------------
// ★ CNVoid 构造器【音效 TAG 实证 VOID】：基座 → vtbl_CNVoid → sub_49A7B0(1, 图像ID,...)
// → sub_4015C0(+229, "VOID", 4)（音效名槽写入）

uint32_t */*thiscall*/ sub_5338B0(uint32_t *this, char a2, int a3)
{
  int *v4; // eax

  sub_52EA60(this, a2, a3);
  v4 = (int *)*(this + 36);
  *(this + 243) = 0;
  *(this + 244) = 0;
  *this = &CNVoid::`vftable';
  sub_49A7B0(this, 1, *v4, 0, 0, 0, 0);
  sub_4015C0(this + 229, "VOID", 4u);
  return this;
}



// ------------------------------------------------------------
// 0x533BD0 sub_533BD0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533BD0(void *Block, char a2)
{
  sub_533C00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533C70 sub_533C70
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533C70(void *Block, char a2)
{
  sub_533CA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533D50 sub_533D50
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533D50(void *Block, char a2)
{
  sub_533D80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533E40 sub_533E40
// ------------------------------------------------------------
// 散装补漏小函数（43L）【语义未逐行展开】

int /*thiscall*/ sub_533E40(int *this, int *a2)
{
  int v3; // eax
  int v4; // esi
  int *v5; // esi
  int i; // ebx
  int **v7; // esi
  int j; // ebx

  if ( a2 == this )
  {
    v3 = __RTDynamicCast(
           *(this + 173),
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNMage `RTTI Type Descriptor',
           0);
    v4 = v3;
    if ( v3 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 840))(v3) == 10
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1288))(v4) == 1
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1284))(v4) == 31 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v4 + 560))(v4, 0, 0, 0, 0);
    }
    v5 = this + 244;
    for ( i = 2; i != 0; --i )
    {
      if ( *v5 != 0 )
        (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)*v5 + 84))(0);
      ++v5;
    }
  }
  v7 = (int **)(this + 244);
  for ( j = 2; j != 0; --j )
  {
    if ( a2 == *v7 )
    {
      *v7 = nullptr;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
    ++v7;
  }
  return sub_600790(a2);
}



// ------------------------------------------------------------
// 0x534090 sub_534090
// ------------------------------------------------------------
// CNSunBurst 析构基座 → sub_4E2040

int /*thiscall*/ sub_534090(void **this)
{
  *this = &CNSunBurst::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534210 sub_534210
// ------------------------------------------------------------
// 散装补漏小函数（60L）【语义未逐行展开】

int /*thiscall*/ sub_534210(uint32_t *this, int a2, int a3, int a4)
{
  int result; // eax
  int v6; // eax
  const void *v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // esi
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // esi
  int v16; // eax
  uint32_t v17[26]; // [esp+4h] [ebp-68h] BYREF

  v17[25] = dword_796E50;
  sub_6001C0(a2, a3, a4);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    sub_423A20(v17);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
    v7 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104));
    v8 = *this;
    qmemcpy(v17, v7, 0x62u);
    *(uint32_t *)((char *)&v17[3] + 3) = 0;
    *(uint32_t *)((char *)&v17[4] + 3) = 0;
    a4 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 120))(this);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v10 = *this;
    a3 = v9;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v10 + 136))(this, a4, v9, 0) != 0
      || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int, int, int))(*this + 140))(
                            this,
                            &a4,
                            &a3,
                            a4,
                            a3,
                            100,
                            1,
                            1)) != 0 )
    {
      v17[0] = a4;
      v17[1] = a3;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v11 = *(uint32_t *)dword_8F8520;
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
      v13 = *(uint32_t *)dword_8F8520;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v17, 98);
      v15 = *(uint32_t *)dword_8F8520;
      v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 44))(*(uint32_t *)(*(this + 28) + 104));
      (*(void (/*thiscall*/ **)(int, int))(v15 + 40))(dword_8F8520, v16);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5343B0 sub_5343B0
// ------------------------------------------------------------
// CNNapalmBomb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5343B0(uint32_t *this, char a2, int a3)
{
  int v4; // eax

  sub_52EA60(this, a2, a3);
  *this = &CNNapalmBomb::`vftable';
  sub_607240(this + 249);
  sub_607280(this + 249);
  v4 = sub_433AC0(this + 257);
  *(this + 258) = v4;
  *(uint8_t *)(v4 + 21) = 1;
  *(uint32_t *)(*(this + 258) + 4) = *(this + 258);
  *(uint32_t *)*(this + 258) = *(this + 258);
  *(uint32_t *)(*(this + 258) + 8) = *(this + 258);
  *(this + 259) = 0;
  sub_607240(this + 262);
  sub_607280(this + 262);
  sub_61AD90(this);
  sub_61B440(this);
  return this;
}



// ------------------------------------------------------------
// 0x5344D0 sub_5344D0
// ------------------------------------------------------------
// CNNapalmBomb 析构基座 → sub_4E2040

int /*thiscall*/ sub_5344D0(int this)
{
  int *v3; // [esp-8h] [ebp-24h]
  int *v4; // [esp-4h] [ebp-20h]
  int *v5[2]; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+18h] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &CNNapalmBomb::`vftable';
  v6 = 2;
  sub_61ADE0();
  nullsub_3(this + 1048);
  v4 = *(int **)(this + 1032);
  v3 = (int *)*v4;
  LOBYTE(v6) = 1;
  sub_4C26A0((int ***)(this + 1028), v5, v3, v4);
  j__free(*(void **)(this + 1032));
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1036) = 0;
  LOBYTE(v6) = 0;
  nullsub_3(this + 996);
  v6 = -1;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x534610 sub_534610
// ------------------------------------------------------------
// CNTargetItBall 析构基座 → sub_4E2040

int /*thiscall*/ sub_534610(void **this)
{
  *this = &CNTargetItBall::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5346F0 sub_5346F0
// ------------------------------------------------------------
// CNHunterSpittle 析构基座 → sub_4E2040

int /*thiscall*/ sub_5346F0(void **this)
{
  *this = &CNHunterSpittle::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534790 sub_534790
// ------------------------------------------------------------
// CNZombieEye 析构基座 → sub_4E2040

int /*thiscall*/ sub_534790(void **this)
{
  *this = &CNZombieEye::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534830 sub_534830
// ------------------------------------------------------------
// CNZombieEyeExplode 析构基座 → sub_4E2040

int /*thiscall*/ sub_534830(void **this)
{
  *this = &CNZombieEyeExplode::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534900 sub_534900
// ------------------------------------------------------------
// CNKagelBombSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_534900(void **this)
{
  *this = &CNKagelBombSub::`vftable';
  sub_61EFD0();
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534A00 sub_534A00
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534A00(void *Block, char a2)
{
  sub_534A30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534AF0 sub_534AF0
// ------------------------------------------------------------
// 散装补漏小函数（5L）【语义未逐行展开】

uint32_t */*thiscall*/ sub_534AF0(uint32_t *this, int a2, int a3)
{
  sub_534A90(a2, a3);
  *this = &CNCrokutaJoint::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x534BB0 sub_534BB0
// ------------------------------------------------------------
// CNLOLLaser 析构基座 → sub_4E2040

int /*thiscall*/ sub_534BB0(void **this)
{
  *this = &CNLOLLaser::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534C50 sub_534C50
// ------------------------------------------------------------
// CNBronzeGolemBullets 析构基座 → sub_4E2040

int /*thiscall*/ sub_534C50(void **this)
{
  *this = &CNBronzeGolemBullets::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534CF0 sub_534CF0
// ------------------------------------------------------------
// CNIceWaveUp 析构基座 → sub_4E2040

int /*thiscall*/ sub_534CF0(void **this)
{
  *this = &CNIceWaveUp::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534DE0 sub_534DE0
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

int /*thiscall*/ sub_534DE0(void *this, void *a2)
{
  int result; // eax

  result = sub_600790(a2);
  if ( a2 == this )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 44578);
  return result;
}



// ------------------------------------------------------------
// 0x534E50 sub_534E50
// ------------------------------------------------------------
// CNLegOfLotus 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534E50(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNLegOfLotus::`vftable';
  sub_61D1D0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x534F40 sub_534F40
// ------------------------------------------------------------
// CNGrabbingLegOfLotus 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534F40(uint32_t *this, char a2, int a3)
{
  sub_534E50(this, a2, a3);
  *this = &CNGrabbingLegOfLotus::`vftable';
  sub_61D3F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x535000 sub_535000
// ------------------------------------------------------------
// CNZepplinBullet 析构基座 → sub_4E2040

int /*thiscall*/ sub_535000(void **this)
{
  *this = &CNZepplinBullet::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5351B0 sub_5351B0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5351B0(void *Block, char a2)
{
  sub_5351E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535220 sub_535220
// ------------------------------------------------------------
// 【音效 TAG 实证 DENDROID_DRIVE_02】26L：树灵驱动音（Dendroid 机关 PO）

char /*thiscall*/ sub_535220(uint8_t *this)
{
  int v2; // eax

  sub_600890();
  if ( *(this + 972) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "DENDROID_DRIVE_02",
      -1,
      0,
      0);
    *(this + 972) = 1;
  }
  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)v2 != 0 )
    {
      LOBYTE(v2) = *(this + 264);
      if ( (uint8_t)v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5352D0 sub_5352D0
// ------------------------------------------------------------
// CNOntoLandMakePassiveObject 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_5352D0(uint32_t *this, char a2, int a3, int a4, int a5)
{
  sub_52EA60(this, a2, a3);
  *(this + 244) = a5;
  *this = &CNOntoLandMakePassiveObject::`vftable';
  *(this + 243) = a4;
  return this;
}



// ------------------------------------------------------------
// 0x5353C0 sub_5353C0
// ------------------------------------------------------------
// CNOntoLandMakePassiveObject 析构基座 → sub_4E2040

int /*thiscall*/ sub_5353C0(void **this)
{
  *this = &CNOntoLandMakePassiveObject::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535440 sub_535440
// ------------------------------------------------------------
// CNRisingShuriken 析构基座 → sub_4E2040

int /*thiscall*/ sub_535440(void **this)
{
  *this = &CNRisingShuriken::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535500 sub_535500
// ------------------------------------------------------------
// CNFallingShuriken 析构基座 → sub_4E2040

int /*thiscall*/ sub_535500(void **this)
{
  *this = &CNFallingShuriken::`vftable';
  *(this + 244) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 980) = 0;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5355D0 sub_5355D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5355D0(void *Block, char a2)
{
  sub_60E8D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535660 sub_535660
// ------------------------------------------------------------
// CNCobWeb 析构基座 → sub_4E2040

int /*thiscall*/ sub_535660(void **this)
{
  *this = &CNCobWeb::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5357B0 sub_5357B0
// ------------------------------------------------------------
// CNAraclothoMissile 析构基座：+976/+980 双发射器 vt+0(1) 释放 → 退 CNThrowItemDestroyable

int /*thiscall*/ sub_5357B0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNAraclothoMissile::`vftable';
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 976);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 980);
  *(uint32_t *)(this + 976) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 988) = 0;
  *(uint32_t *)this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x5358B0 sub_5358B0
// ------------------------------------------------------------
// CNAraclothoSpark 析构基座 → sub_4E2040

int /*thiscall*/ sub_5358B0(void **this)
{
  *this = &CNAraclothoSpark::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535990 sub_535990
// ------------------------------------------------------------
// CNSpectressBat 析构基座 → sub_4E2040

int /*thiscall*/ sub_535990(int this)
{
  *(uint32_t *)this = &CNSpectressBat::`vftable';
  sub_61EFD0();
  *(uint32_t *)(this + 980) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x535A80 sub_535A80
// ------------------------------------------------------------
// CNEvilEyeSmallLOLLaser 析构基座 → sub_4E2040

int /*thiscall*/ sub_535A80(void **this)
{
  *this = &CNEvilEyeSmallLOLLaser::`vftable';
  sub_61F570();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// ============
// 【分区 5】第三轮审计补漏（0x5196C0-0x5398D0，散装按审计序排列）
// 邮件 UI 130L 主刷新（0x522F20）、map/vector 异常路径（0x52E6A0/0x52E630）、
// 其余为构造/析构残件与技能 PO 收尾。
// ============

// 0x5196C0 sub_5196C0
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_5196C0()
{
  return sub_510BF0();
}



// ------------------------------------------------------------
// 0x51A470 sub_51A470
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

// attributes: thunk
int sub_51A470()
{
  return sub_510CD0();
}



// ------------------------------------------------------------
// 0x522660 sub_522660
// ------------------------------------------------------------
// 散装补漏小函数（24L）【语义未逐行展开】

void /*thiscall*/ sub_522660(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int i; // esi
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 116);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);
  *(uint32_t *)(this + 116) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 112) = 0;
  for ( i = 0; i < 20; i += 4 )
  {
    v5 = *(void (/*thiscall*/ ****)(uint32_t, int))(i + *(uint32_t *)(this + 128));
    if ( v5 != nullptr )
      (**v5)(v5, 1);
    *(uint32_t *)(i + *(uint32_t *)(this + 128)) = 0;
  }
  if ( *(uint32_t *)(this + 128) != 0 )
    j_j__free(*(void **)(this + 128));
  *(uint32_t *)(this + 128) = 0;
}



// ------------------------------------------------------------
// 0x522730 sub_522730
// ------------------------------------------------------------
// 散装补漏小函数（7L）【语义未逐行展开】

void *sub_522730()
{
  void *result; // eax

  sub_4BF300(0, 0);
  result = dword_8F8528;
  *(uint8_t *)(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 7) + 136) + 17) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5227D0 sub_5227D0
// ------------------------------------------------------------
// 散装补漏小函数（59L）【语义未逐行展开】

int /*thiscall*/ sub_5227D0(int *this)
{
  int v2; // edi
  const char *v3; // eax
  uint64_t v4; // rax
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  int v8; // eax
  int result; // eax
  int v10; // [esp+10h] [ebp-1Ch]
  int v11; // [esp+14h] [ebp-18h]
  char Buffer[16]; // [esp+18h] [ebp-14h] BYREF
  int v13; // [esp+28h] [ebp-4h]

  v13 = dword_796E50;
  v2 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
  v3 = (const char *)sub_69B740(*(this + 29));
  v10 = j__atol(v3);
  if ( v10 < 0 )
    v10 = 0;
  v4 = (uint64_t)((double)v10 * 0.05);
  *(this + 41) = v4;
  if ( (int)v4 > 10000 )
    *(this + 41) = 10000;
  v5 = *(this + 40);
  v6 = v10;
  v7 = v5 + *(this + 41);
  v11 = v10;
  if ( v10 > v2 - v7 )
  {
    v8 = (v2 - v5) / 21;
    *(this + 41) = v8;
    if ( v8 > 10000 )
      *(this + 41) = 10000;
    v7 = v5 + *(this + 41);
    v11 = v2 - v7;
    v6 = v2 - v7;
  }
  if ( v6 < 0 )
  {
    *(this + 41) = 0;
    v7 = v5;
    v11 = 0;
    v6 = 0;
  }
  result = *(uint32_t *)(*(this + 29) + 12);
  if ( result == dword_79BE4C || v6 != v10 )
  {
    if ( byte_8A6E9B != 0 )
    {
      memset(&byte_8A6698, 0, 0x400u);
      memset(&byte_8A6A98, 0, 0x400u);
    }
    sprintf(Buffer, "%d", v6);
    result = sub_69BD90(*(this + 29), Buffer);
    v6 = v11;
  }
  *(this + 42) = v2 - v6 - v7;
  return result;
}



// ------------------------------------------------------------
// 0x522AA0 sub_522AA0
// ------------------------------------------------------------
// 散装补漏小函数（24L）【语义未逐行展开】

void /*thiscall*/ sub_522AA0(int this)
{
  int i; // esi
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void *v5; // eax

  for ( i = 0; i < 8; i += 4 )
  {
    v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(i + *(uint32_t *)(this + 40));
    if ( v3 != nullptr )
      (**v3)(v3, 1);
    *(uint32_t *)(i + *(uint32_t *)(this + 40)) = 0;
    v4 = *(void (/*thiscall*/ ****)(uint32_t, int))(i + *(uint32_t *)(this + 44));
    if ( v4 != nullptr )
      (**v4)(v4, 1);
    *(uint32_t *)(i + *(uint32_t *)(this + 44)) = 0;
  }
  if ( *(uint32_t *)(this + 40) != 0 )
    j_j__free(*(void **)(this + 40));
  v5 = *(void **)(this + 44);
  *(uint32_t *)(this + 40) = 0;
  if ( v5 != nullptr )
    j_j__free(v5);
  *(uint32_t *)(this + 44) = 0;
}



// ------------------------------------------------------------
// 0x522C30 sub_522C30
// ------------------------------------------------------------
// 散装补漏小函数（11L）【语义未逐行展开】

int /*thiscall*/ sub_522C30(int *this, int a2)
{
  int result; // eax

  result = *(this + 9);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)result + 152))(
             result,
             *(uint32_t *)(*(this + 2) + 20),
             *(uint32_t *)(*(this + 2) + 24),
             dword_79C0B0);
  return result;
}



// ------------------------------------------------------------
// 0x522D60 sub_522D60
// ------------------------------------------------------------
// 散装补漏小函数（30L）【语义未逐行展开】

int /*cdecl*/ sub_522D60(int a1, int a2, char a3, int a4, int a5, int a6)
{
  int v6; // esi
  int v7; // edi
  int result; // eax

  v6 = a2;
  v7 = a6;
  if ( a2 == 0 )
  {
    if ( a6 == 0 )
      return result;
LABEL_5:
    sub_423200(dword_8F7B08, 97);
    sub_41C100(a1);
    a2 = v6;
    sub_423290(&a2, 4);
    HIBYTE(a2) = a3;
    sub_423290((char *)&a2 + 3, 1);
    a2 = a4;
    sub_423290(&a2, 2);
    a2 = a5;
    sub_423290(&a2, 2);
    a2 = v7;
    sub_423290(&a2, 4);
    sub_423380(dword_8F7B08);
    return sub_44ABF0(dword_8F8528, a1, a2);
  }
  if ( a2 >= 0 )
    goto LABEL_5;
  return result;
}



// ------------------------------------------------------------
// 0x522E90 sub_522E90
// ------------------------------------------------------------
// 散装补漏小函数（3L）【语义未逐行展开】

int /*cdecl*/ sub_522E90(int a1)
{
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, a1, 0);
}



// ------------------------------------------------------------
// 0x522F20 sub_522F20
// ------------------------------------------------------------
// 散装补漏小函数（130L）【语义未逐行展开】

int /*thiscall*/ sub_522F20(int *this)
{
  int result; // eax
  int v3; // ebx
  void *v4; // eax
  int v5; // eax
  int v6; // edi
  DWORD Time; // edx
  int v8; // eax
  unsigned int v9; // edi
  unsigned int v10; // edx
  unsigned int v11; // edi
  unsigned int v12; // ecx
  signed int v13; // esi
  signed int v14; // edi
  char *v15; // eax
  char *v16; // eax
  int v17; // eax
  int v18; // ecx
  int v19; // ebx
  int v20; // edx
  char *v21; // eax
  char *v22; // eax
  int v23; // [esp-Ch] [ebp-28h]
  unsigned int v24; // [esp-8h] [ebp-24h]
  int v25; // [esp+8h] [ebp-14h]
  char Buffer[12]; // [esp+Ch] [ebp-10h] BYREF
  int v27; // [esp+18h] [ebp-4h]

  v27 = dword_796E50;
  result = *(this + 27);
  if ( result != 0 )
  {
    v25 = *(this + 6);
    v3 = *(this + 5);
    if ( dword_9B7EA0 == 0 )
    {
      v4 = operator new(0x34u);
      if ( v4 != nullptr )
        sub_416D10(v4);
      else
        v5 = 0;
      *(uint8_t *)(v5 + 2) = 0;
      *(uint32_t *)(v5 + 48) = 0;
      *(uint8_t *)v5 = 0;
      *(uint8_t *)(v5 + 1) = 0;
      *(uint8_t *)(v5 + 3) = 0;
      *(uint32_t *)(v5 + 12) = 0;
      *(uint32_t *)(v5 + 16) = 6;
      *(uint32_t *)(v5 + 20) = 12;
      *(uint32_t *)(v5 + 24) = 0;
      *(uint32_t *)(v5 + 28) = 1600;
      *(uint32_t *)(v5 + 32) = 0;
      *(uint32_t *)(v5 + 36) = 0;
      *(uint32_t *)(v5 + 40) = 0;
      *(uint32_t *)(v5 + 44) = 0;
      dword_9B7EA0 = v5;
      *(uint32_t *)(v5 + 48) = dword_99FCCC;
      *(uint8_t *)(v5 + 2) = 1;
      *(uint32_t *)(v5 + 4) = -16777216;
    }
    v6 = *(this + 27);
    Time = timeGetTime();
    v8 = *(uint32_t *)(v6 + 48);
    v9 = *(uint32_t *)(v6 + 8);
    v10 = (Time - v8) / 0x3E8;
    if ( v9 >= v10 )
      v11 = v9 - v10;
    else
      v11 = 0;
    v12 = v11 / 0x15180;
    v13 = v11 / 0xE10;
    v14 = v11 / 0x3C;
    if ( v12 != 0 )
    {
      v24 = v12;
      v15 = sub_422E70(2050);
      sprintf(Buffer, v15, v24);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, dword_9B7EA0);
      v23 = -1;
LABEL_20:
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v3 + 147,
        v25 + 12,
        v23,
        Buffer);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    if ( v13 != 0 )
    {
      v16 = sub_422E70(2051);
      sprintf(Buffer, v16, v13);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, dword_9B7EA0);
      v17 = dword_79C0B0;
      v18 = *(uint32_t *)dword_79C0B0;
      v19 = v3 + 147;
      v20 = v25 + 12;
      if ( v13 > 5 )
      {
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v18 + 80))(dword_79C0B0, v19, v20, -1, Buffer);
        return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      }
    }
    else
    {
      if ( v14 == 0 )
      {
        v22 = sub_422E70(2052);
        sprintf(Buffer, v22, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, dword_9B7EA0);
        v23 = -13487361;
        goto LABEL_20;
      }
      v21 = sub_422E70(2052);
      sprintf(Buffer, v21, v14);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, dword_9B7EA0);
      v17 = dword_79C0B0;
      v18 = *(uint32_t *)dword_79C0B0;
      v19 = v3 + 147;
      v20 = v25 + 12;
      if ( v14 <= 30 )
      {
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v18 + 80))(dword_79C0B0, v19, v20, -13487361, Buffer);
        return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      }
    }
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v18 + 80))(v17, v19, v20, -16731649, Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x523340 sub_523340
// ------------------------------------------------------------
// 散装补漏小函数（21L）【语义未逐行展开】

int /*cdecl*/ sub_523340(int a1)
{
  int result; // eax
  char *v2; // eax

  sub_44AC10(dword_8F8528);
  result = a1;
  switch ( a1 )
  {
    case 21:
      v2 = sub_422E70(2056);
      break;
    case 4:
      v2 = sub_422E70(2057);
      break;
    case 10:
      v2 = sub_422E70(2058);
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
}



// ------------------------------------------------------------
// 0x5235D0 sub_5235D0
// ------------------------------------------------------------
// 散装补漏小函数（84L）【语义未逐行展开】

int /*thiscall*/ sub_5235D0(uint32_t *this)
{
  int result; // eax
  void *v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // eax

  sub_69DE30((int)this);
  result = dword_9B7EB8;
  if ( dword_9B7EB8 != 0 )
    goto LABEL_7;
  if ( *(this + 27) != 0 )
  {
    v2 = operator new(0x34u);
    if ( v2 != nullptr )
      sub_416D10(v2);
    else
      v3 = 0;
    *(uint8_t *)(v3 + 2) = 0;
    *(uint32_t *)(v3 + 12) = 0;
    *(uint32_t *)(v3 + 28) = 1600;
    *(uint32_t *)(v3 + 48) = 0;
    *(uint8_t *)v3 = 0;
    *(uint8_t *)(v3 + 1) = 0;
    *(uint8_t *)(v3 + 3) = 0;
    *(uint32_t *)(v3 + 16) = 6;
    *(uint32_t *)(v3 + 20) = 12;
    *(uint32_t *)(v3 + 24) = 0;
    *(uint32_t *)(v3 + 32) = 0;
    *(uint32_t *)(v3 + 36) = 0;
    *(uint32_t *)(v3 + 40) = 0;
    *(uint32_t *)(v3 + 44) = 0;
    *(uint32_t *)(v3 + 48) = dword_99FCCC;
    *(uint8_t *)(v3 + 2) = 1;
    *(uint32_t *)(v3 + 4) = -16777216;
    *(uint32_t *)(v3 + 12) = 1;
    v4 = *(uint32_t *)(*(this + 27) + 20);
    dword_9B7EB8 = v3;
    *(uint32_t *)(v3 + 28) = v4;
LABEL_7:
    v5 = *(this + 27);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
        v5,
        *(this + 5) + 74,
        *(this + 6) + 199,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v6 = *(uint32_t *)(*(this + 30) + 12);
    v7 = *(uint32_t *)(v6 + 4);
    if ( v7 != 0 )
      v8 = (*(uint32_t *)(v6 + 8) - v7) >> 2;
    else
      v8 = 0;
    v9 = v8 / 5;
    v10 = *(uint32_t *)(v6 + 4);
    if ( v10 != 0 )
      v11 = (*(uint32_t *)(v6 + 8) - v10) >> 2;
    else
      v11 = 0;
    if ( v11 % 5 != 0 )
      ++v9;
    sprintf(byte_9B7EA4, off_79300C, *(this + 31), v9);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, dword_9B7EB8);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      *(this + 5) + 74,
      *(this + 6) + 204,
      -1,
      byte_9B7EA4);
    __asm { jmp     dword ptr [eax+4Ch] }
  }
  return result;
}



// ------------------------------------------------------------
// 0x523700 sub_523700
// ------------------------------------------------------------
// 散装补漏小函数（11L）【语义未逐行展开】

uint32_t */*stdcall*/ sub_523700(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // eax
  int i; // ecx

  v3 = a1;
  if ( a2 != 0 )
  {
    for ( i = a2; i != 0; --i )
      *v3++ = *a3;
  }
  return &a1[a2];
}



// ------------------------------------------------------------
// 0x523800 sub_523800
// ------------------------------------------------------------
// 散装补漏小函数（22L）【语义未逐行展开】

int /*thiscall*/ sub_523800(uint32_t *this)
{
  int result; // eax
  uint32_t *v3; // edi
  int v4; // esi

  result = *(this + 3);
  v3 = *(uint32_t **)(result + 4);
  if ( v3 != *(uint32_t **)(result + 8) )
  {
    do
    {
      if ( *v3 != 0 )
        (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
      v4 = *(this + 3);
      memcpy_0(v3, v3 + 1, 4 * ((*(uint32_t *)(v4 + 8) - (int)(v3 + 1)) >> 2));
      *(uint32_t *)(v4 + 8) -= 4;
      result = *(uint32_t *)(*(this + 3) + 8);
    }
    while ( v3 != (uint32_t *)result );
  }
  byte_9B7E98 = 1;
  return result;
}



// ------------------------------------------------------------
// 0x52E630 sub_52E630
// ------------------------------------------------------------
// noreturn：vector<T> too long —— std::length_error 抛出路径（MSVC 容器溢出）

void /*noreturn*/ sub_52E630()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(pExceptionObject, (int)v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x52EA20 sub_52EA20
// ------------------------------------------------------------
// 散装补漏小函数（8L）【语义未逐行展开】

int /*thiscall*/ sub_52EA20(int this)
{
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  sub_52E960(v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x52EB30 sub_52EB30
// ------------------------------------------------------------
// CNRDJoint 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52EB30(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNRDJoint::`vftable';
  sub_609600(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52EBC0 sub_52EBC0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52EBC0(void *Block, char a2)
{
  sub_52EBB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52EC90 sub_52EC90
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52EC90(void *Block, char a2)
{
  sub_52ECC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52EE30 sub_52EE30
// ------------------------------------------------------------
// ★ PO 析构基座（gunner_skills.cpp 机关 PO 析构链的公共出口）

int /*thiscall*/ sub_52EE30(int this)
{
  *(uint32_t *)this = &CNMapObject::`vftable';
  sub_60A950();
  if ( *(uint32_t *)(this + 1080) != 0 )
    j__free(*(void **)(this + 1080));
  *(uint32_t *)(this + 1080) = 0;
  *(uint32_t *)(this + 1084) = 0;
  *(uint32_t *)(this + 1088) = 0;
  if ( *(uint32_t *)(this + 1064) != 0 )
    j__free(*(void **)(this + 1064));
  *(uint32_t *)(this + 1064) = 0;
  *(uint32_t *)(this + 1068) = 0;
  *(uint32_t *)(this + 1072) = 0;
  if ( *(uint32_t *)(this + 1048) != 0 )
    j__free(*(void **)(this + 1048));
  *(uint32_t *)(this + 1048) = 0;
  *(uint32_t *)(this + 1052) = 0;
  *(uint32_t *)(this + 1056) = 0;
  `eh vector destructor iterator'((void *)(this + 1032), 4u, 3, sub_401060);
  if ( *(uint32_t *)(this + 1004) != 0 )
    j__free(*(void **)(this + 1004));
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x52EF90 sub_52EF90
// ------------------------------------------------------------
// CNBlueBallBox 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52EF90(uint32_t *this, int a2, int a3)
{
  uint32_t *v4; // eax

  sub_52ED60(a2, a3);
  v4 = (uint32_t *)*(this + 36);
  *this = &CNBlueBallBox::`vftable';
  sub_49A7B0(100, *v4, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x52F040 sub_52F040
// ------------------------------------------------------------
// CNUrn 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52F040(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &CNUrn::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x52F0B0 sub_52F0B0
// ------------------------------------------------------------
// CNPathGate 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52F0B0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNPathGate::`vftable';
  *(this + 245) = 0;
  *(this + 246) = 0;
  *(this + 247) = 0;
  sub_577960(this);
  sub_577C80(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F1E0 sub_52F1E0
// ------------------------------------------------------------
// CNFireMissile 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F1E0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNFireMissile::`vftable';
  sub_60B8D0(this);
  sub_60BA80(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F2C0 sub_52F2C0
// ------------------------------------------------------------
// CNFireExplosion 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F2C0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNFireExplosion::`vftable';
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  sub_60BB90(this);
  sub_60BFF0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F3F0 sub_52F3F0
// ------------------------------------------------------------
// CNIceMissile 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F3F0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNIceMissile::`vftable';
  sub_60C130(this);
  sub_60C230(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F4D0 sub_52F4D0
// ------------------------------------------------------------
// CNThunderBolt 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F4D0(uint32_t *this, char a2, int a3, int a4)
{
  sub_52EA60(this, a2, a3);
  *this = &CNThunderBolt::`vftable';
  sub_60C3D0(this);
  sub_60C590(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x52F5C0 sub_52F5C0
// ------------------------------------------------------------
// CNParticleFactory 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F5C0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNParticleFactory::`vftable';
  sub_60C850(this);
  sub_60CA50(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F6A0 sub_52F6A0
// ------------------------------------------------------------
// CNBlast 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F6A0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBlast::`vftable';
  sub_60CB40(this);
  sub_60CB70(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F780 sub_52F780
// ------------------------------------------------------------
// CNEarthQuake 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F780(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNEarthQuake::`vftable';
  sub_61BE30(this);
  sub_60D040(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52F860 sub_52F860
// ------------------------------------------------------------
// CNDangerousGas 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F860(uint32_t *this, char a2, int a3, int a4)
{
  sub_52EA60(this, a2, a3);
  *this = &CNDangerousGas::`vftable';
  sub_60D120(this);
  sub_60D1D0(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x52F950 sub_52F950
// ------------------------------------------------------------
// CNIceNiddleGroup 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52F950(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNIceNiddleGroup::`vftable';
  nullsub_3(this);
  sub_60D6A0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52FA30 sub_52FA30
// ------------------------------------------------------------
// CNIceNiddle 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52FA30(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNIceNiddle::`vftable';
  sub_52E240(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52FAD0 sub_52FAD0
// ------------------------------------------------------------
// CNEarthFire 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52FAD0(uint32_t *this, char a2, int a3, int a4, int a5, int a6)
{
  sub_52EA60(this, a2, a3);
  *this = &CNEarthFire::`vftable';
  sub_60D810(this);
  sub_60D840(a3, a4, a5, a6);
  return this;
}



// ------------------------------------------------------------
// 0x52FBC0 sub_52FBC0
// ------------------------------------------------------------
// CNShootingStar 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52FBC0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNShootingStar::`vftable';
  sub_60DB10(this);
  sub_60DC60(a3);
  return this;
}



// ------------------------------------------------------------
// 0x52FCA0 sub_52FCA0
// ------------------------------------------------------------
// CNShootingStarExp 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_52FCA0(uint32_t *this, char a2, int a3, int a4)
{
  sub_52EA60(this, a2, a3);
  *this = &CNShootingStarExp::`vftable';
  sub_60DD80(this);
  sub_60DFA0(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x52FD90 sub_52FD90
// ------------------------------------------------------------
// CNThrowItemDestroyable 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_52FD90(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNThrowItemDestroyable::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x52FE90 sub_52FE90
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_52FE90(void *Block, char a2)
{
  sub_52FEC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x52FF80 sub_52FF80
// ------------------------------------------------------------
// CNBouncer 析构基座 → sub_4E2040

int /*thiscall*/ sub_52FF80(void **this)
{
  *this = &CNBouncer::`vftable';
  nullsub_3(this);
  *this = &CNThrowItemDestroyable::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x530040 sub_530040
// ------------------------------------------------------------
// CNCreateOnDestroyObject 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530040(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNCreateOnDestroyObject::`vftable';
  sub_60E8E0(this);
  sub_60E9A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x530130 sub_530130
// ------------------------------------------------------------
// CNFlyBombSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_530130(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNFlyBombSub::`vftable';
  sub_52E590(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5301D0 sub_5301D0
// ------------------------------------------------------------
// CNSunkenRock 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5301D0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNSunkenRock::`vftable';
  sub_60EC70(a3);
  return this;
}



// ------------------------------------------------------------
// 0x530270 sub_530270
// ------------------------------------------------------------
// CNRedRock 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530270(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNRedRock::`vftable';
  sub_60EF20(a3);
  return this;
}



// ------------------------------------------------------------
// 0x530350 sub_530350
// ------------------------------------------------------------
// CNDollMasterBubble 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530350(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNDollMasterBubble::`vftable';
  sub_60EFD0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x530430 sub_530430
// ------------------------------------------------------------
// CNMagicTargetWarning 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_530430(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNMagicTargetWarning::`vftable';
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint16_t *)(this + 988) = 0;
  *(uint8_t *)(this + 983) = 4;
  *(uint16_t *)(this + 984) = 100;
  sub_423A20(this + 990);
  sub_5FF8E0(this);
  sub_60F3A0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x530500 sub_530500
// ------------------------------------------------------------
// CNTemporaryHit 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530500(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNTemporaryHit::`vftable';
  nullsub_3(this);
  sub_6056A0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5305E0 sub_5305E0
// ------------------------------------------------------------
// CNForceField 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_5305E0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNForceField::`vftable';
  *(uint32_t *)(this + 1016) = 15;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  sub_60F3E0(this);
  sub_60F4E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x530710 sub_530710
// ------------------------------------------------------------
// CNCircleAppendageMaker 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530710(uint32_t *this, char a2, int a3, int a4)
{
  sub_52EA60(this, a2, a3);
  *this = &CNCircleAppendageMaker::`vftable';
  sub_60F8A0(this);
  sub_60F8C0(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x530800 sub_530800
// ------------------------------------------------------------
// 散装补漏小函数（5L）【语义未逐行展开】

uint32_t */*thiscall*/ sub_530800(uint32_t *this, char a2, int a3)
{
  sub_530040(this, a2, a3);
  *this = &CNBombMine::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x530910 sub_530910
// ------------------------------------------------------------
// 薄转发 → sub_530910

int /*thiscall*/ sub_530910(uint32_t **this, int a2, int a3, int a4)
{
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));
  return 0;
}



// ------------------------------------------------------------
// 0x530970 sub_530970
// ------------------------------------------------------------
// CNToothSFish 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530970(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNToothSFish::`vftable';
  sub_5FF8E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x530A60 sub_530A60
// ------------------------------------------------------------
// CNToothKurokuta 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530A60(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNToothKurokuta::`vftable';
  sub_5FF8E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x530B50 sub_530B50
// ------------------------------------------------------------
// CNCurseBombSub 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530B50(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNCurseBombSub::`vftable';
  sub_6106A0(this);
  sub_610740(this);
  return this;
}



// ------------------------------------------------------------
// 0x530C40 sub_530C40
// ------------------------------------------------------------
// CNSummonMonsterWithEffect 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_530C40(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNSummonMonsterWithEffect::`vftable';
  *(uint16_t *)(this + 973) = -1;
  *(uint16_t *)(this + 978) = -1;
  *(uint8_t *)(this + 972) = 0;
  *(uint16_t *)(this + 975) = 0;
  *(uint8_t *)(this + 977) = 0;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 0;
  sub_610A50(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x530D50 sub_530D50
// ------------------------------------------------------------
// CNBodyHit 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_530D50(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBodyHit::`vftable';
  sub_610F40(this);
  sub_610F90(a3);
  return this;
}



// ------------------------------------------------------------
// 0x530E30 sub_530E30
// ------------------------------------------------------------
// CNTrackingIceWave 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_530E30(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNTrackingIceWave::`vftable';
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 980) = &off_6C2B88;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 992) = 1;
  *(uint8_t *)(this + 994) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1008) = &off_6C2B88;
  *(uint32_t *)(this + 1016) = 0;
  *(uint8_t *)(this + 1020) = 1;
  *(uint8_t *)(this + 1022) = 0;
  *(uint8_t *)(this + 1021) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint8_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1036) = &off_6C2B88;
  *(uint32_t *)(this + 1044) = 0;
  *(uint8_t *)(this + 1048) = 1;
  *(uint8_t *)(this + 1050) = 0;
  *(uint8_t *)(this + 1049) = 0;
  *(uint32_t *)(this + 1060) = 0;
  *(uint32_t *)(this + 1056) = 0;
  *(uint32_t *)(this + 1052) = 0;
  *(uint8_t *)(this + 1068) = 0;
  *(uint32_t *)(this + 1064) = &off_6C2B88;
  *(uint32_t *)(this + 1072) = 0;
  *(uint8_t *)(this + 1076) = 1;
  *(uint8_t *)(this + 1078) = 0;
  *(uint8_t *)(this + 1077) = 0;
  *(uint32_t *)(this + 1088) = 0;
  *(uint32_t *)(this + 1084) = 0;
  *(uint32_t *)(this + 1080) = 0;
  *(uint32_t *)(this + 1092) = 0;
  *(uint32_t *)(this + 1096) = 0;
  *(uint32_t *)(this + 1100) = 0;
  *(uint32_t *)(this + 1104) = 0;
  *(uint32_t *)(this + 1108) = 0;
  *(uint32_t *)(this + 1112) = 0;
  *(uint32_t *)(this + 1116) = 0;
  sub_611980(this);
  sub_6120F0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x531060 sub_531060
// ------------------------------------------------------------
// CNSingleIceWave 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_531060(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNSingleIceWave::`vftable';
  sub_607240(this + 243);
  sub_607280(this + 243);
  sub_607240(this + 248);
  sub_607280(this + 248);
  sub_612250(this);
  sub_612270(a3);
  return this;
}



// ------------------------------------------------------------
// 0x531190 sub_531190
// ------------------------------------------------------------
// CNEventBarrier 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint8_t */*thiscall*/ sub_531190(uint8_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *(uint32_t *)this = &CNEventBarrier::`vftable';
  *(this + 1116) = 0;
  *((uint32_t *)this + 278) = &off_6C2B88;
  *((uint32_t *)this + 280) = 0;
  *(this + 1124) = 1;
  *(this + 1126) = 0;
  *(this + 1125) = 0;
  *((uint32_t *)this + 284) = 0;
  *((uint32_t *)this + 283) = 0;
  *((uint32_t *)this + 282) = 0;
  sub_6126D0(this);
  sub_612700(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5312C0 sub_5312C0
// ------------------------------------------------------------
// 【音效 TAG 实证 WAVE_CREATE】7L：机关/技能 PO 触发时播 "WAVE_CREATE"

int /*thiscall*/ sub_5312C0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNNormalWave::`vftable';
  *(uint8_t *)(this + 972) = 0;
  sub_4015C0("WAVE_CREATE", 0xBu);
  return this;
}



// ------------------------------------------------------------
// 0x531410 sub_531410
// ------------------------------------------------------------
// CNNormalWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_531410(void **this)
{
  *this = &CNNormalWave::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5314B0 sub_5314B0
// ------------------------------------------------------------
// CNIceWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_5314B0(void **this)
{
  *this = &CNIceWave::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531590 sub_531590
// ------------------------------------------------------------
// CNSuplexSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_531590(void **this)
{
  *this = &CNSuplexSub::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531670 sub_531670
// ------------------------------------------------------------
// CNEnergyBall 析构基座 → sub_4E2040

int /*thiscall*/ sub_531670(void **this)
{
  *this = &CNEnergyBall::`vftable';
  nullsub_3(this);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5317D0 sub_5317D0
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_5317D0(void *Block, char a2)
{
  sub_531800();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531870 sub_531870
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_531870(void *Block, char a2)
{
  sub_5318A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x531920 sub_531920
// ------------------------------------------------------------
// 散装补漏小函数（17L）【语义未逐行展开】

int /*thiscall*/ sub_531920(int *this)
{
  int v2; // eax
  int result; // eax

  sub_600890();
  v2 = __RTDynamicCast(
         *(this + 173),
         0,
         &IRDCollisionObject `RTTI Type Descriptor',
         &CNFighter `RTTI Type Descriptor',
         0);
  if ( v2 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 840))(v2);
  if ( result != 17 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x531A70 sub_531A70
// ------------------------------------------------------------
// CNRoarStun 析构基座 → sub_4E2040

int /*thiscall*/ sub_531A70(void **this)
{
  *this = &CNRoarStun::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531B30 sub_531B30
// ------------------------------------------------------------
// CNEnergyField 析构基座 → sub_4E2040

int /*thiscall*/ sub_531B30(void **this)
{
  *this = &CNEnergyField::`vftable';
  nullsub_3(this);
  nullsub_3(this + 243);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531C40 sub_531C40
// ------------------------------------------------------------
// CNBlastBlood 析构基座 → sub_4E2040

int /*thiscall*/ sub_531C40(void **this)
{
  *this = &CNBlastBlood::`vftable';
  nullsub_3(this);
  nullsub_3(this + 243);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531D50 sub_531D50
// ------------------------------------------------------------
// CNBlastBloodSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_531D50(void **this)
{
  *this = &CNBlastBloodSub::`vftable';
  nullsub_3(this);
  nullsub_3(this + 243);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x531E90 sub_531E90
// ------------------------------------------------------------
// CNGhost 析构基座 → sub_4E2040

int /*thiscall*/ sub_531E90(int this)
{
  int v3; // [esp-8h] [ebp-24h]
  int *v4; // [esp-4h] [ebp-20h]
  uint8_t v5[4]; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+Ch] [ebp-10h]
  int v7; // [esp+18h] [ebp-4h]

  v6 = this;
  *(uint32_t *)this = &CNGhost::`vftable';
  v7 = 2;
  nullsub_3(this);
  v4 = *(int **)(this + 1040);
  v3 = *v4;
  LOBYTE(v7) = 1;
  sub_52E960(v5, v3, v4);
  j__free(*(void **)(this + 1040));
  *(uint32_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1044) = 0;
  LOBYTE(v7) = 0;
  nullsub_3(this + 1000);
  v7 = -1;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x531FC0 sub_531FC0
// ------------------------------------------------------------
// CNFireWave 析构基座 → sub_4E2040

int /*thiscall*/ sub_531FC0(void **this)
{
  *this = &CNFireWave::`vftable';
  sub_614FD0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5320C0 sub_5320C0
// ------------------------------------------------------------
// CNSpiralNen 析构基座 → sub_4E2040

int /*thiscall*/ sub_5320C0(void **this)
{
  *this = &CNSpiralNen::`vftable';
  nullsub_3(this);
  nullsub_3(this + 243);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5321D0 sub_5321D0
// ------------------------------------------------------------
// CNClosePunchSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_5321D0(int this)
{
  *(uint32_t *)this = &CNClosePunchSub::`vftable';
  nullsub_3(this);
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x5322E0 sub_5322E0
// ------------------------------------------------------------
// CNGunnerBullet 析构基座 → sub_4E2040

int /*thiscall*/ sub_5322E0(void **this)
{
  *this = &CNGunnerBullet::`vftable';
  sub_6073C0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5323E0 sub_5323E0
// ------------------------------------------------------------
// CNGunnerSubWeaponBullet 析构基座 → sub_4E2040

int /*thiscall*/ sub_5323E0(void **this)
{
  *this = &CNGunnerSubWeaponBullet::`vftable';
  nullsub_3(this);
  nullsub_3(this + 248);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x532620 sub_532620
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532620(void *Block, char a2)
{
  sub_532650();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532720 sub_532720
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532720(void *Block, char a2)
{
  sub_532750();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532830 sub_532830
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532830(void *Block, char a2)
{
  sub_532860();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532960 sub_532960
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532960(void *Block, char a2)
{
  sub_532990();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532A40 sub_532A40
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532A40(void *Block, char a2)
{
  sub_532A70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532B20 sub_532B20
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532B20(void *Block, char a2)
{
  sub_532B50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532C40 sub_532C40
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532C40(void *Block, char a2)
{
  sub_532C70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532D30 sub_532D30
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532D30(void *Block, char a2)
{
  sub_532D60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532E10 sub_532E10
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_532E10(void *Block, char a2)
{
  sub_532E40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x532F00 sub_532F00
// ------------------------------------------------------------
// 散装补漏小函数（12L）【语义未逐行展开】

char /*thiscall*/ sub_532F00(uint32_t *this)
{
  int v2; // eax

  sub_600890();
  v2 = *(this + 30);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    LOBYTE(v2) = *((uint8_t *)this + 264);
    if ( (uint8_t)v2 == 0 )
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x532F70 sub_532F70
// ------------------------------------------------------------
// CNGrandWave 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_532F70(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGrandWave::`vftable';
  sub_616EB0(this);
  sub_6170E0(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x533050 sub_533050
// ------------------------------------------------------------
// CNDecoy 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533050(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNDecoy::`vftable';
  sub_6171F0(this);
  sub_617310(a3);
  return this;
}



// ------------------------------------------------------------
// 0x533130 sub_533130
// ------------------------------------------------------------
// CNChaser 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533130(uint32_t *this, char a2, int a3, int a4)
{
  sub_52EA60(this, a2, a3);
  *this = &CNChaser::`vftable';
  sub_617520(this);
  sub_617C20(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x533220 sub_533220
// ------------------------------------------------------------
// CNMagicMissile 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533220(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNMagicMissile::`vftable';
  sub_618920(this);
  sub_618B60(this);
  return this;
}



// ------------------------------------------------------------
// 0x533300 sub_533300
// ------------------------------------------------------------
// CNLaunchJOL 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_533300(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNLaunchJOL::`vftable';
  sub_618BE0(this);
  sub_6193B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5333E0 sub_5333E0
// ------------------------------------------------------------
// CNLaunchFrostHead 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5333E0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNLaunchFrostHead::`vftable';
  sub_6193F0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x5334C0 sub_5334C0
// ------------------------------------------------------------
// 【音效 TAG 实证 LAUNCH_FLUORESCENT】9L：荧光发射机关音效

uint32_t */*thiscall*/ sub_5334C0(uint32_t *this, char a2, int a3)
{
  uint32_t *v4; // eax

  sub_52EA60(this, a2, a3);
  v4 = (uint32_t *)*(this + 36);
  *this = &CNLaunchFluorescent::`vftable';
  sub_49A7B0(1, *v4, 0, 0, 0, 0);
  sub_4015C0("LAUNCH_FLUORESCENT", 0x12u);
  return this;
}



// ------------------------------------------------------------
// 0x5336B0 sub_5336B0
// ------------------------------------------------------------
// CNLaunchFluorescent 析构基座 → sub_4E2040

int /*thiscall*/ sub_5336B0(void **this)
{
  *this = &CNLaunchFluorescent::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533790 sub_533790
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533790(void *Block, char a2)
{
  sub_5337C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533830 sub_533830
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_533830(void *Block, char a2)
{
  sub_533860();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x533940 sub_533940
// ------------------------------------------------------------
// 散装补漏小函数（51L）【语义未逐行展开】

int /*thiscall*/ sub_533940(void *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // edi
  bool v6; // cc
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int result; // eax
  int v13; // [esp-4h] [ebp-Ch]

  sub_600890();
  v2 = *(uint32_t *)(*((uint32_t *)this + 28) + 104);
  if ( v2 == 0 )
    goto LABEL_8;
  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 16))(v2) + 85) - 300;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 44))(v2);
  v5 = *((uint32_t *)this + 30);
  v6 = v4 < v3;
  v7 = *(uint32_t *)(v5 + 148);
  if ( v6 )
  {
    if ( v7 != 7 )
      goto LABEL_8;
    v9 = sub_491C70(v5, 3);
    sub_493A60(v5, v9);
    v13 = 3;
  }
  else
  {
    if ( v7 >= 8 )
      goto LABEL_8;
    v8 = sub_491C70(v5, 8);
    sub_493A60(v5, v8);
    v13 = 8;
  }
  v10 = **((uint32_t **)this + 36);
  v11 = sub_491C70(v10, v13);
  sub_493A60(v10, v11);
LABEL_8:
  result = sub_699000((int)this + 36);
  if ( result >= *((uint32_t *)this + 244) + *((uint32_t *)this + 243) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 352))(this);
    result = *((uint32_t *)this + 244);
    *((uint32_t *)this + 243) += result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x533C00 sub_533C00
// ------------------------------------------------------------
// CNVoid 析构基座 → sub_4E2040

int /*thiscall*/ sub_533C00(void **this)
{
  *this = &CNVoid::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533CA0 sub_533CA0
// ------------------------------------------------------------
// CNHalloweenBuster 析构基座 → sub_4E2040

int /*thiscall*/ sub_533CA0(void **this)
{
  *this = &CNHalloweenBuster::`vftable';
  sub_61A500();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533D80 sub_533D80
// ------------------------------------------------------------
// CNHalloweenBusterSub 析构基座 → sub_4E2040

int /*thiscall*/ sub_533D80(void **this)
{
  *this = &CNHalloweenBusterSub::`vftable';
  sub_61A540();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x533F20 sub_533F20
// ------------------------------------------------------------
// 散装补漏小函数（37L）【语义未逐行展开】

int /*thiscall*/ sub_533F20(int *this, uint16_t *a2, size_t Size)
{
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-20h]
  float v12; // [esp+0h] [ebp-20h]
  float v13; // [esp+4h] [ebp-1Ch]
  float v14; // [esp+4h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-4h]
  int v16; // [esp+1Ch] [ebp-4h]
  uint16_t v17; // [esp+28h] [ebp+8h]
  size_t Sizea; // [esp+2Ch] [ebp+Ch]
  size_t Sizeb; // [esp+2Ch] [ebp+Ch]

  sub_5FFF80((int)a2, Size);
  v17 = *a2;
  v4 = (char *)sub_47E720(3, 31);
  v5 = *(this + 176);
  v6 = v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v15 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v13 = (float)sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  v11 = (float)v15;
  *(this + 183) += (uint64_t)sub_4049C0(v11, v13, v17, 1000) - 100;
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v16 = sub_47EFD0(v6, COERCE_FLOAT(2), v5, v8, v8, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(3), v5, Sizeb, Sizeb, 0);
  v12 = (float)v16;
  v9 = (uint64_t)sub_4049C0(v12, v14, v17, 1000);
  HIDWORD(v9) = *this;
  *((float *)this + 181) = (double)(100 * (int)v9 / (*(this + 183) + 100)) + *((float *)this + 181);
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x5340A0 sub_5340A0
// ------------------------------------------------------------
// 【音效 TAG 实证 QUICK_TURN】8L：快速转身 PO 音效（枪手 QUICK_TURN 指令）

int /*thiscall*/ sub_5340A0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNProvocationDollCreater::`vftable';
  *(uint8_t *)(this + 701) = 1;
  *(uint8_t *)(this + 700) = 0;
  sub_4015C0("QUICK_TURN", 0xAu);
  return this;
}



// ------------------------------------------------------------
// 0x534370 sub_534370
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534370(void *Block, char a2)
{
  sub_5343A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534470 sub_534470
// ------------------------------------------------------------
// 【音效 TAG 实证 SIZZLE_LOOP】13L：灼烧循环音效（燃烧地面/火焰持续音）

char /*thiscall*/ sub_534470(uint8_t *this)
{
  char result; // al

  sub_5FFE70();
  result = *(this + 980);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "SIZZLE_LOOP",
             10000,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x534580 sub_534580
// ------------------------------------------------------------
// CNTargetItBall 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534580(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNTargetItBall::`vftable';
  sub_61BE30(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x534660 sub_534660
// ------------------------------------------------------------
// CNHunterSpittle 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534660(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNHunterSpittle::`vftable';
  sub_5FF8E0(this);
  sub_61BE30(this);
  return this;
}



// ------------------------------------------------------------
// 0x534700 sub_534700
// ------------------------------------------------------------
// CNZombieEye 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534700(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNZombieEye::`vftable';
  sub_5FF8E0(this);
  sub_61C360(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5347A0 sub_5347A0
// ------------------------------------------------------------
// CNZombieEyeExplode 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5347A0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNZombieEyeExplode::`vftable';
  sub_5FF8E0(this);
  sub_61C490(this);
  return this;
}



// ------------------------------------------------------------
// 0x534840 sub_534840
// ------------------------------------------------------------
// CNKagelBomb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534840(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNKagelBomb::`vftable';
  sub_5FF8E0(this);
  sub_61C830(a3);
  return this;
}



// ------------------------------------------------------------
// 0x534960 sub_534960
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534960(void *Block, char a2)
{
  sub_534900();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534A30 sub_534A30
// ------------------------------------------------------------
// CNSpaceFishBug 析构基座 → sub_4E2040

int /*thiscall*/ sub_534A30(void **this)
{
  *this = &CNSpaceFishBug::`vftable';
  nullsub_3(this);
  --dword_9B9414;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x534B20 sub_534B20
// ------------------------------------------------------------
// CNLOLLaser 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534B20(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNLOLLaser::`vftable';
  sub_5FF8E0(this);
  sub_61CCE0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x534BC0 sub_534BC0
// ------------------------------------------------------------
// CNBronzeGolemBullets 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534BC0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNBronzeGolemBullets::`vftable';
  sub_5FF8E0(this);
  sub_61CD50(a3);
  return this;
}



// ------------------------------------------------------------
// 0x534C60 sub_534C60
// ------------------------------------------------------------
// CNIceWaveUp 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534C60(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNIceWaveUp::`vftable';
  sub_616500(this);
  sub_61CF30(this);
  return this;
}



// ------------------------------------------------------------
// 0x534D40 sub_534D40
// ------------------------------------------------------------
// CNStoneBlade 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_534D40(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNStoneBlade::`vftable';
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x534E10 sub_534E10
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_534E10(void *Block, char a2)
{
  sub_534E40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x534EB0 sub_534EB0
// ------------------------------------------------------------
// CNPierceHeadLegOfLotus 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_534EB0(uint32_t *this, int a2, int a3)
{
  sub_534E50(a2, a3);
  *this = &CNPierceHeadLegOfLotus::`vftable';
  sub_61D280(this);
  return this;
}



// ------------------------------------------------------------
// 0x534FA0 sub_534FA0
// ------------------------------------------------------------
// CNZepplinBullet 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_534FA0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNZepplinBullet::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x535010 sub_535010
// ------------------------------------------------------------
// CNDendroidSeed 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_535010(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNDendroidSeed::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x5351E0 sub_5351E0
// ------------------------------------------------------------
// CNDendroidSeed 析构基座 → sub_4E2040

int /*thiscall*/ sub_5351E0(void **this)
{
  *this = &CNDendroidSeed::`vftable';
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535290 sub_535290
// ------------------------------------------------------------
// 删除析构壳（vmt0 标准形：a2&1 → free）

void */*thiscall*/ sub_535290(void *Block, char a2)
{
  sub_5352C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535310 sub_535310
// ------------------------------------------------------------
// ★ 死亡施加状态：a2==self && vt+128()<=0（坠落/到达）&& 存活 →
// sub_4E4A50(宿主, +243 状态ID, +244 强度, x, y, 0, 4, 0,0,0)

int /*thiscall*/ sub_535310(uint32_t *this, uint32_t *a2)
{
  int v3; // eax
  int v5; // [esp-24h] [ebp-2Ch]
  int v6; // [esp-20h] [ebp-28h]
  int v7; // [esp-1Ch] [ebp-24h]
  int v8; // [esp-18h] [ebp-20h]

  if ( a2 == this
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v6 = *(this + 244);
    v5 = *(this + 243);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    sub_4E4A50(v3, v5, v6, v7, v8, 0, 4, 0, 0, 0);
  }
  return sub_600790(a2);
}



// ------------------------------------------------------------
// 0x5353D0 sub_5353D0
// ------------------------------------------------------------
// CNRisingShuriken 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_5353D0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)(this + 972) = a3;
  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 0;
  *(uint32_t *)this = &CNRisingShuriken::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x535450 sub_535450
// ------------------------------------------------------------
// CNFallingShuriken 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

int /*thiscall*/ sub_535450(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNFallingShuriken::`vftable';
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 990) = 0;
  *(uint8_t *)(this + 989) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 976) = &off_6C2B88;
  *(uint8_t *)(this + 988) = 1;
  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 0;
  *(uint8_t *)(this + 972) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x535520 sub_535520
// ------------------------------------------------------------
// CNGhoulSkull 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_535520(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNGhoulSkull::`vftable';
  sub_423A20(this + 244);
  *(this + 243) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x535600 sub_535600
// ------------------------------------------------------------
// CNCobWeb 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_535600(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNCobWeb::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x535670 sub_535670
// ------------------------------------------------------------
// ★ 蜘蛛 BOSS 导弹烟雾（37L）【资源实证】：sub_4C3640("PassiveObject/Monster/Spider/
// Particle/BossMissileSmog.ptl")（P36 发射器）

int /*thiscall*/ sub_535670(int this, char a2, void *Block)
{
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // ecx
  int v7; // eax

  sub_52EA60((uint32_t *)this, a2, (int)Block);
  *(uint32_t *)this = &CNAraclothoMissile::`vftable';
  *(uint8_t *)(this + 988) = 0;
  *(uint32_t *)(this + 984) = &off_6C2B88;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 1;
  *(uint8_t *)(this + 998) = 0;
  *(uint8_t *)(this + 997) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 972) = Block;
  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    v5 = sub_428F30(v4, (int)"PassiveObject/Monster/Spider/Particle/BossMissileSmog.ptl", 0);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 976) = v5;
  *(uint8_t *)(this + 997) = 0;
  *(uint8_t *)(this + 998) = 0;
  sub_698F90(this + 984, 50, 0);
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 1012) = sub_699000(this + 36);
  v6 = *(uint32_t *)(this + 348);
  if ( v6 != 0 && (unsigned int)((*(uint32_t *)(this + 352) - v6) >> 2) > 1 )
    v7 = *(uint32_t *)(v6 + 4);
  else
    v7 = 0;
  *(uint32_t *)(this + 680) = v7;
  *(uint32_t *)(this + 684) = v7;
  return this;
}



// ------------------------------------------------------------
// 0x535850 sub_535850
// ------------------------------------------------------------
// CNAraclothoSpark 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 无

uint32_t */*thiscall*/ sub_535850(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNAraclothoSpark::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x5358C0 sub_5358C0
// ------------------------------------------------------------
// CNSpectressBat 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

int /*thiscall*/ sub_5358C0(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &CNSpectressBat::`vftable';
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 980) = &off_6C2B88;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 992) = 1;
  *(uint8_t *)(this + 994) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1008) = a3;
  sub_616D80(this);
  sub_61F240(this);
  return this;
}



// ------------------------------------------------------------
// 0x5359F0 sub_5359F0
// ------------------------------------------------------------
// CNEvilEyeSmallLOLLaser 构造器（PO 类，虚表名直证）：基座 sub_52EA60/52ED60 系 → 数据解析 sub_6xxxxx

uint32_t */*thiscall*/ sub_5359F0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &CNEvilEyeSmallLOLLaser::`vftable';
  sub_5FF8E0(this);
  sub_61F4C0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5398D0 sub_5398D0
// ------------------------------------------------------------
// CNRDPooledPassiveObject 析构基座 thunk（→ 池归还，P33）

// attributes: thunk
int /*thiscall*/ sub_5398D0(void **this)
{
  return sub_4E2040(this);
}


