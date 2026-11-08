// ============================================================
// 【40JP逆向源代码工程】src/game/creature/missing_monster.cpp
// 模块: 0x590000-0x5E0000 补漏
// 来源: work/dump 素材  区块: 0x598430-0x5D7CD1 §A 0x59 补漏
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 122
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 0x59 补漏
// ============================================================
// 0x598430 sub_598430
// ------------------------------------------------------------
// 调: sub_598430 sub_4DA3B0
int /*stdcall*/ sub_598430(int nArg1, int nArg2, int nArg3)
{
  return sub_4DA3B0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// ============================================================
// §B 0x5A 补漏
// ============================================================
// 0x5A36E0 sub_5A36E0
// ------------------------------------------------------------
// 调: sub_5A36E0
void /*thiscall*/ sub_5A36E0(uint32_t *this)
{
  *(this + 2151) = 600;
}



// ------------------------------------------------------------
// 0x5A5160 sub_5A5160
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5A5160 sub_498F60
int /*thiscall*/ sub_5A5160(uint32_t *this)
{
  return sub_498F60(this);
}



// ------------------------------------------------------------
// 0x5AA350 sub_5AA350
// ------------------------------------------------------------
// 调: sub_5AA350
int /*thiscall*/ sub_5AA350(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2151)(uint32_t, int); // ecx
  int result; // eax

  fld_e2151 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2151);
  if ( fld_e2151 != nullptr )
    result = (**fld_e2151)(fld_e2151, 1);
  *(this + 2151) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5AA420 sub_5AA420
// ------------------------------------------------------------
// 调: sub_5AA420 sub_41A5E0
int /*thiscall*/ sub_5AA420(uint32_t *this)
{
  int nRand; // edi
  int nRand2; // eax
  int nRand23; // ebx
  int v5; // edi
  int v6; // edi
  uint64_t v7; // rax
  int v8; // edi
  int v9; // edi
  uint64_t v10; // rax
  int result; // eax
  int *fld_e28; // esi
  int pObj; // ecx
  bool v14; // zf
  int nRand22; // [esp+Ch] [ebp-18h]
  int v16; // [esp+Ch] [ebp-18h]
  float v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]

  nRand = rand() % 2;
  nRand2 = rand() % 2;
  nRand22 = nRand2;
  if ( nRand != 0 )
  {
    if ( nRand == 1 )
      nRand23 = 0;
    else
      nRand23 = nRand2;
  }
  else
  {
    nRand23 = 1;
  }
  if ( nRand2 != 0 )
  {
    if ( nRand2 == 1 )
      v22 = 2;
  }
  else
  {
    v22 = 3;
  }
  if ( nRand != 4 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    v21 = sub_41A5E0(v5 + 816);
    v20 = COERCE_FLOAT(sub_41A5E0(v5 + 830));
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    v18 = sub_41A5E0(v6 + 816);
    v7 = (uint64_t)((double)(int)(uint64_t)((double)v18 * COERCE_FLOAT(sub_41A5E0(v6 + 830))) * 0.5);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      HIDWORD(v7),
      0,
      v7,
      (uint64_t)((double)(int)(uint64_t)((double)v21 * v20) * 0.5),
      0,
      0,
      0);
    nRand2 = nRand22;
  }
  if ( nRand2 != 4 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    v16 = sub_41A5E0(v8 + 816);
    v17 = COERCE_FLOAT(sub_41A5E0(v8 + 830));
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    v19 = sub_41A5E0(v9 + 816);
    v10 = (uint64_t)((double)(int)(uint64_t)((double)v19 * COERCE_FLOAT(sub_41A5E0(v9 + 830))) * 0.175);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      HIDWORD(v10),
      1,
      v10,
      (uint64_t)((double)(int)(uint64_t)((double)v16 * v17) * 0.175),
      0,
      0,
      0);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, nRand23, v22);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, nRand23);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 144))(this, nRand23);
  fld_e28 = (int *)*(this + 28);
  pObj = *fld_e28;
  v14 = *fld_e28 == 0;
  *((uint8_t *)fld_e28 + 124) = 1;
  if ( !v14 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
    if ( (uint8_t)result != 0 )
    {
      result = 1106247680;
      if ( fld_e28[3] != 1106247680 )
      {
        fld_e28[3] = 1106247680;
        *((uint8_t *)fld_e28 + 196) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA750 sub_5AA750
// ------------------------------------------------------------
// 调: sub_5AA750 sub_699000 sub_698F90
char /*thiscall*/ sub_5AA750(int *this, char pszArg2)
{
  int pThis_884; // ebx
  int fld_e2186; // edi
  int fld_e2193; // edi
  int v6; // eax
  int fld_e2177; // eax
  unsigned int fld_e2178; // edi

  pThis_884 = (int)(this + 2180);
  fld_e2186 = *(this + 2186);
  if ( sub_699000((int)(this + 2180)) >= fld_e2186  // 【clock_now(clk)】
    || (fld_e2193 = *(this + 2193), (v6 = sub_699000((int)(this + 2187))) >= fld_e2193) && pszArg2 == 1 )  // 【clock_now(clk)】
  {
    LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)v6 != 0 )
    {
      if ( rand() % 100 >= 50 )
      {
        fld_e2177 = *(this + 2177);
        if ( fld_e2177 != 0 )
          fld_e2178 = (*(this + 2178) - fld_e2177) >> 2;
        else
          fld_e2178 = 0;
        *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % fld_e2178));
      }
      else
      {
        *(this + 81) = 135;
      }
      *(uint8_t *)(pThis_884 + 13) = 0;
      *(uint8_t *)(pThis_884 + 14) = 0;
      sub_698F90(pThis_884, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      *((uint8_t *)this + 8761) = 0;
      *((uint8_t *)this + 8762) = 0;
      LOBYTE(v6) = sub_698F90((int)(this + 2187), 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5AABB0 sub_5AABB0
// ------------------------------------------------------------
// 调: sub_5AABB0 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AABB0(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int fld_e1554; // edi
  int v7; // edx
  int v8; // eax

  result = *(this + 2153);
  if ( result != 0 )
  {
    if ( result == 1 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
      if ( *(uint8_t *)(result + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
          return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result >= 130 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 130);
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
      (*(void (/*thiscall*/ **)(int *, int))(v3 + 108))(this, v5);
      *(uint32_t *)(*(this + 28) + 24) = 0;
      *(uint32_t *)(*(this + 28) + 36) = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      if ( *((uint8_t *)this + 8701) == 0 )
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 500;
        fld_e1554 = *(uint32_t *)(*(this + 1554) + 52);
        sub_4910E0(fld_e1554);
        sub_493A60(fld_e1554, *(uint32_t *)(fld_e1554 + 32));
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 52));
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 52));
      }
      v7 = *this;
      *(this + 2153) = 1;
      v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 80))(this);
      return sub_424120(*(uint32_t **)(v8 + 132), 2, 300);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AAED0 sub_5AAED0
// ------------------------------------------------------------
// 证: "FLYDRAGON_CRY"
// 调: sub_5AAED0 sub_41A5E0 sub_495890 sub_4926A0
int /*thiscall*/ sub_5AAED0(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edi
  int v7; // edi
  uint64_t v8; // rax
  uint32_t *fld_e28; // edi
  int v10; // eax
  int v11; // eax
  int v13; // [esp+Ch] [ebp-Ch]
  float v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]

  v2 = *this;
  *(this + 2155) = *(this + 81);
  if ( (*(int (**)(void))(v2 + 184))() == 4 )
    v3 = 5;
  else
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);
  v4 = *this;
  *(this + 2157) = v3;
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 188))(this);
  v5 = *this;
  *(this + 2154) = 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3);
  v15 = sub_41A5E0(v6 + 816);
  v14 = COERCE_FLOAT(sub_41A5E0(v6 + 830));
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v13 = sub_41A5E0(v7 + 816);
  v8 = (uint64_t)((double)(int)(uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v7 + 830))) * 1.5);
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    HIDWORD(v8),
    0,
    v8,
    (uint64_t)((double)(int)(uint64_t)((double)v15 * v14) * 1.5),
    0,
    0,
    0);
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[6] != -1005191168 )
  {
    fld_e28[6] = -1005191168;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 200);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v10);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 304);
  v11 = *this;
  *((uint8_t *)this + 8700) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v11 + 212))(
           this,
           "FLYDRAGON_CRY",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB3E0 sub_5AB3E0
// ------------------------------------------------------------
// 调: sub_5AB3E0 sub_5AA190 sub_41C6E0 sub_5AA0A0 sub_699000
char /*thiscall*/ sub_5AB3E0(uint32_t *this)
{
  int fld_e1554; // eax
  int v4; // edx

  if ( *(this + 2201) != 18 && *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 )
  {
    if ( sub_5AA190(this, 200, 1) != 0 || sub_5AA190(this, 300, 1) != 1 )
    {
      fld_e1554 = *(this + 1554);
      v4 = *this;
      *(this + 2201) = -1;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 208))(this, *(uint32_t *)(fld_e1554 + 16));
    }
    else if ( (uint8_t)sub_41C6E0(this + 2194) == 1 )
    {
      sub_5AA0A0(this, 18);
      *(this + 2151) = sub_699000((int)(this + 9));
      *((uint8_t *)this + 8789) = 0;
      *((uint8_t *)this + 8790) = 0;
      sub_698F90((int)(this + 2194), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      return 0;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5AB600 sub_5AB600
// ------------------------------------------------------------
// 调: sub_5AB600 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5AB600(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+14h] [ebp+Ch]
  int v10; // [esp+14h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      if ( nArg2 == 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
        *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v5)) + 0.30000001;
        sub_41A590(v5, v6, v9);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
      }
    }
  }
  else
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;
    sub_41A590(v7, v8, v10);
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(uint8_t *)(*(this + 1905) + 64) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AB9B0 sub_5AB9B0
// ------------------------------------------------------------
// 证: "B_FLYDRAGON_FLAP" | "FLYDRAGON_FLAP"
// 调: sub_5AB9B0 sub_4E1780 sub_699000 sub_5AAED0 sub_5AB180
char /*thiscall*/ sub_5AB9B0(int *this)
{
  int v1; // eax
  int v2; // eax
  int v4; // eax
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi
  int fld_e28; // ecx
  uint32_t *fld_e15543; // edi
  int fld_e1541; // [esp+0h] [ebp-Ch]

  sub_4E1780(this);
  (*(void (/*thiscall*/ **)(int *))(*this + 1264))(this);
  if ( *(this + 2156) + *(this + 2174) < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);
    *(this + 2156) = sub_699000((int)(this + 9));
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < 140 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 )
    {
      if ( *(this + 2154) == 2 )
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 16);
        if ( (*(int (/*fastcall*/ **)(int *))(*this + 200))(this) == *fld_e1554
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )
        {
          sub_5AAED0(this);
        }
      }
      else
      {
        sub_5AB180(this);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 16 )
    {
      if ( *(this + 2153) == 2 )
      {
        fld_e15542 = (uint32_t *)(*(this + 1554) + 48);
        if ( (*(int (/*fastcall*/ **)(int *))(*this + 200))(this) == *fld_e15542
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )
        {
          sub_5AAA20(this);
        }
      }
      else
      {
        sub_5AABB0(this);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == *(this + 1541) )
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) != 3 || *((uint8_t *)this + 8692) != 0 )
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 )
            *((uint8_t *)this + 8692) = 0;
        }
        else
        {
          if ( *(this + 1943) == 3 )
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
              this,
              "B_FLYDRAGON_FLAP",
              -1,
              0,
              0);
          else
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
              this,
              "FLYDRAGON_FLAP",
              -1,
              0,
              0);
          *((uint8_t *)this + 8692) = 1;
        }
      }
      fld_e28 = *(this + 28);
      if ( *(uint32_t *)(fld_e28 + 36) == 0 && *(float *)(fld_e28 + 24) != 0.0 )
        sub_494F20(2, 0.0);
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 && *(this + 2154) == 2 && *(this + 2153) == 2 )
      sub_5AA010(this);
    LOBYTE(v4) = *((uint8_t *)this + 8608);
    if ( (uint8_t)v4 != 0 )
    {
      fld_e15543 = (uint32_t *)*(this + 1554);
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
      if ( v4 == *fld_e15543 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
        if ( *(uint8_t *)(v4 + 170) != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
          v1 = *this;
          fld_e1541 = *(this + 1541);
          *((uint8_t *)this + 8608) = 0;
          (*(void (/*thiscall*/ **)(int *, int))(v1 + 196))(this, fld_e1541);
          v2 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
          LOBYTE(v4) = sub_4926A0(v2);
        }
      }
    }
  }
  else
  {
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *))(*this + 1256))(this);
  }
  return v4;
}



// ------------------------------------------------------------
// 0x5ABD90 sub_5ABD90
// ------------------------------------------------------------
// 调: sub_5ABD90 sub_5AB800 sub_41A5E0 sub_4926A0 sub_698F90
int /*thiscall*/ sub_5ABD90(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  char v5; // di
  int result; // eax
  int pThis_6DD; // eax
  int v9; // edx
  int v10; // edi
  int v11; // eax

  v5 = ArgList;
  if ( ArgList == 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 80
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v5 = 0;
    *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % 100 < 50));
    *(this + 1813) = 0;
  }
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
    v9 = *this;
    if ( pThis_6DD != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v9 + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 32));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        100,
        *(uint32_t *)(*(this + 1554) + 32),
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8797) = 0;
      *((uint8_t *)this + 8798) = 0;
      sub_698F90((int)(this + 2196), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(v9 + 876))(this, 0, 700, 700, 0, -2000, 1);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    v10 = *this;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v10 + 896))(this, v11);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC110 sub_5AC110
// ------------------------------------------------------------
// 调: sub_5AC110 sub_5ABC20 sub_5AB4A0
int /*thiscall*/ sub_5AC110(uint32_t *this)
{
  int v2; // eax

  v2 = sub_5ABC20();
  *(this + 2201) = v2;
  if ( v2 == 18 )
    sub_5AB4A0(this);
  return *(this + 2201);
}



// ------------------------------------------------------------
// 0x5AFCF0 sub_5AFCF0
// ------------------------------------------------------------
// 调: sub_5AFCF0 sub_4E0120
int /*thiscall*/ sub_5AFCF0(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
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
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand2 = rand();
        v4 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v4 < 30 )
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



// ------------------------------------------------------------
// 0x5AFE80 sub_5AFE80
// ------------------------------------------------------------
// 证: "DRAGONMAN_ILLUSION_LOOP" | "DRGM_ATK2" | "DRGM_ATK1"
// 调: sub_5AFE80 sub_4E1780 sub_41A5E0 sub_5AFAB0 sub_4926A0
char /*usercall*/ sub_5AFE80@<al>(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // ecx
  uint32_t *v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax

  sub_4E1780(pDwArg1);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0
    && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 15
    && *((uint8_t *)pDwArg1 + 8614) == 1
    && (pObj = pDwArg1[2154]) != 0
    && pDwArg1[2159] != 0 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 200))(pObj) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 16, 0, 2, 0);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 )
  {
    sub_5AFAB0(pDwArg1);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 0 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) == pDwArg1[1541]
      || (v4 = (uint32_t *)pDwArg1[1554], (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) == *v4) )
    {
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 184))(pDwArg1, nArg2);
      v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      v7 = *pDwArg1;
      if ( v6 == v5 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(v7 + 196))(pDwArg1, pDwArg1[1541]);
        v8 = *(uint32_t *)pDwArg1[1554];
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(v7 + 196))(pDwArg1, *(uint32_t *)pDwArg1[1554]);
        v8 = pDwArg1[1541];
      }
      sub_4926A0(v8);
    }
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 184))(pDwArg1) == 4 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 188))(pDwArg1) == 4 )
    {
      if ( *((uint8_t *)pDwArg1 + 8613) == 1 )
      {
        v9 = *pDwArg1;
        *((uint8_t *)pDwArg1 + 8613) = 0;
        (*(void (/*thiscall*/ **)(int *, int))(v9 + 216))(pDwArg1, 12);
      }
    }
    else if ( *((uint8_t *)pDwArg1 + 8613) == 0 )
    {
      v10 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8613) = 1;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v10 + 212))(
        pDwArg1,
        "DRAGONMAN_ILLUSION_LOOP",
        12,
        0,
        0);
    }
  }
  v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);
  if ( v11 == 8 )
  {
    v12 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
    if ( v12 != 0 )
    {
      v11 = v12 - 2;
      if ( v11 == 0 )
      {
        v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
        if ( *(int *)(v11 + 148) >= 4 )
        {
          LOBYTE(v11) = *((uint8_t *)pDwArg1 + 8612);
          if ( (uint8_t)v11 == 0 )
          {
            LOBYTE(v11) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
                            pDwArg1,
                            "DRGM_ATK2",
                            -1,
                            0,
                            0);
            *((uint8_t *)pDwArg1 + 8612) = 1;
          }
        }
      }
    }
    else
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      if ( *(int *)(v11 + 148) >= 3 )
      {
        LOBYTE(v11) = *((uint8_t *)pDwArg1 + 8612);
        if ( (uint8_t)v11 == 0 )
        {
          LOBYTE(v11) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
                          pDwArg1,
                          "DRGM_ATK1",
                          -1,
                          0,
                          0);
          *((uint8_t *)pDwArg1 + 8612) = 1;
        }
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// ============================================================
// §C 0x5B 补漏(含空骨鱼反击)
// ============================================================
// 0x5B1CD0 sub_5B1CD0
// ------------------------------------------------------------
// 证: "ZIEG_LASER_READY_LOOP" | "ZIEG_CAST_LASER"
// 调: sub_5B1CD0
int /*thiscall*/ sub_5B1CD0(uint8_t *this)
{
  int v2; // eax

  v2 = *(uint32_t *)this;
  *(this + 8621) = 0;
  *(this + 8622) = 0;
  *(this + 8623) = 0;
  (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(v2 + 212))("ZIEG_LASER_READY_LOOP", 45567, 0, 0);
  return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "ZIEG_CAST_LASER",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5B4A00 sub_5B4A00
// ------------------------------------------------------------
// 调: sub_5B4A00
bool /*stdcall*/ sub_5B4A00(int nArg1)
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 260
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 263
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 264;
}



// ------------------------------------------------------------
// 0x5B4CE0 sub_5B4CE0
// ------------------------------------------------------------
// 调: sub_5B4CE0 sub_4D9760
int /*thiscall*/ sub_5B4CE0(uint32_t *this)
{
  sub_4D9760();
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
  *(this + 2164) = 0;
  *((uint8_t *)this + 8632) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5B4ED0 sub_5B4ED0
// ------------------------------------------------------------
// 调: sub_5B4ED0 sub_5B4A00 sub_41A5E0
int /*thiscall*/ sub_5B4ED0(int *this, float *pArg2, float *pArg3, float *pArg4)
{
  int fld_e21524; // edi
  int v6; // eax
  int fld_e21525; // ecx
  int v8; // eax
  double fld_e21522; // st7
  int v10; // eax
  int fld_e21526; // ecx
  int v12; // eax
  int v13; // eax
  int fld_e21527; // ecx
  int v15; // eax
  int v16; // eax
  int fld_e21528; // ecx
  int v18; // eax
  int fld_e2152; // ecx
  int v20; // eax
  int fld_e21523; // edi
  int result; // eax
  int v23; // [esp+14h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 40))(*(this + 2152), 273) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 40))(*(this + 2152), 529) != 0
      && sub_5B4A00(*(this + 2152)) )
    {
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e2152 = *(this + 2152);
      if ( v18 != 0 )
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152) - 11;
      else
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152) + 11;
      *pArg2 = (float)v20;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 60);
    }
    else
    {
      *pArg2 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);
      fld_e21523 = *(this + 2152);
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 192))(fld_e21523) + v23);
    }
    goto LABEL_28;
  }
  fld_e21524 = *(this + 2152);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 1 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    fld_e21525 = *(this + 2152);
    if ( v6 != 0 )
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21525 + 120))(fld_e21525) - 20;
    else
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21525 + 120))(fld_e21525) + 20;
  }
  else
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 0 )
    {
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21526 = *(this + 2152);
      if ( v10 != 0 )
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21526 + 120))(fld_e21526) - 5;
      else
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21526 + 120))(fld_e21526) + 5;
      *pArg2 = (float)v12;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 75);
      goto LABEL_28;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) == 2 )
    {
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21527 = *(this + 2152);
      if ( v13 != 0 )
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21527 + 120))(fld_e21527) - 7;
      else
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21527 + 120))(fld_e21527) + 7;
      *pArg2 = (float)v15;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);
      fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 100);
      goto LABEL_28;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21524 + 1032))(fld_e21524) != 3 )
      goto LABEL_29;
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    fld_e21528 = *(this + 2152);
    if ( v16 != 0 )
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21528 + 120))(fld_e21528) - 10;
    else
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21528 + 120))(fld_e21528) + 10;
  }
  *pArg2 = (float)v8;
  *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 124))(*(this + 2152)) + 1);
  fld_e21522 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 128))(*(this + 2152)) + 70);
LABEL_28:
  *pArg4 = fld_e21522;
LABEL_29:
  result = sub_41A5E0((unsigned int)(this + 1757));
  if ( result == 6 )
    *pArg4 = *pArg4 * 0.5 + *pArg4;
  return result;
}



// ------------------------------------------------------------
// 0x5B57E0 sub_5B57E0
// ------------------------------------------------------------
// 调: sub_5B57E0 sub_41A5E0
bool /*thiscall*/ sub_5B57E0(uint32_t *this, int nArg2)
{
  uint32_t *fld_e1550; // edi
  bool result; // al
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0
    || rand() % 100 >= 30
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 )
  {
    return false;
  }
  switch ( sub_41A5E0((unsigned int)(this + 1757)) )
  {
    case 1:
    case 4:
      fld_e1554 = (uint32_t *)(*(this + 1554) + 8);
      goto LABEL_10;
    case 3:
      fld_e1550 = (uint32_t *)(*(this + 1550) + 12);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e1550;
    case 5:
      fld_e15542 = (uint32_t *)(*(this + 1554) + 20);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e15542;
    case 6:
      fld_e1554 = (uint32_t *)(*(this + 1554) + 24);
LABEL_10:
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e1554;
      break;
    default:
      return false;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B5DC0 sub_5B5DC0
// ------------------------------------------------------------
// 调: sub_5B5DC0 sub_432E50 sub_495890 sub_4A0550
int /*thiscall*/ sub_5B5DC0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2152; // eax
  int fld_e21522; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int result; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )
  {
    fld_e2152 = *(this + 2152);
    if ( fld_e2152 != 0 )
    {
      fld_e21522 = *(this + 2152);
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2152 + 128))();
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522, v10 + 40);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 120))(fld_e21522, v11);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  v15 = sub_432E50(v14);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);
  sub_495890(2, 0);
  result = sub_4A0550(10);
  *((uint8_t *)this + 8605) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5B6000 sub_5B6000
// ------------------------------------------------------------
// 调: sub_5B6000
char /*thiscall*/ sub_5B6000(uint8_t **this)
{
  int fld_e1905; // esi
  char result; // al

  (*((void (/*thiscall*/ **)(uint8_t **, uint32_t))*this + 288))(this, *(this + 2164));
  (*((void (/*thiscall*/ **)(uint8_t **, int))*this + 276))(this, 5);
  *(uint8_t *)((*((int (/*thiscall*/ **)(uint8_t **))*this + 260))(this) + 8) = 0;
  **(this + 1905) = **(this + 1905) == 0;
  (*(this + 1905))[32] = (*(this + 1905))[32] == 0;
  (*(this + 1905))[64] = (*(this + 1905))[64] == 0;
  fld_e1905 = (int)*(this + 1905);
  result = *(uint8_t *)(fld_e1905 + 96);
  *(uint8_t *)(fld_e1905 + 96) = result == 0;
  return result;
}



// ------------------------------------------------------------
// 0x5B6180 sub_5B6180
// ------------------------------------------------------------
// 调: sub_5B6180
int /*thiscall*/ sub_5B6180(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7568) = 2;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
  {
    *(uint32_t *)(this + 7596) = 50;
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4)
                                             + *(float *)(*(uint32_t *)(this + 7620) + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B62E0 sub_5B62E0
// ------------------------------------------------------------
// 调: sub_5B62E0
int /*thiscall*/ sub_5B62E0(int this, int nArg2, int nArg3)
{
  int result; // eax

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
      *(uint8_t *)(this + 7534) = 0;
  }
  else
  {
    result = *(uint32_t *)(this + 7620) + 160;
    *(uint32_t *)(this + 7568) = 0;
    *(uint32_t *)(this + 7596) = 0;
    *(float *)(result + 4) = *(float *)(result + 4) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBD70 sub_5BBD70
// ------------------------------------------------------------
// 调: sub_5BBD70
int /*thiscall*/ sub_5BBD70(int *this)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi
  int nRand; // eax
  int v6; // et2

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 0 )
    {
      result = *(this + 1813);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        if ( result >= *(this + 2150) )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
          result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e1813);
          if ( result < 30 )
          {
            fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
            result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e18132);
            if ( result < 90 )
            {
              nRand = rand();
              v6 = nRand % 300;
              result = nRand / 300;
              if ( v6 < 15 )
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBF50 sub_5BBF50
// ------------------------------------------------------------
// 调: sub_5BBF50 sub_4D54E0 sub_41A5E0 sub_4938F0 sub_492080
int /*thiscall*/ sub_5BBF50(int *this)
{
  int result; // eax
  int fld_e2171; // ecx
  int fld_e21712; // eax
  float v5; // [esp+4h] [ebp-4h]

  sub_4D54E0(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      sub_4938F0(*(this + 2175));
      sub_4938F0(*(this + 2176));
      sub_4938F0(*(this + 2179));
      sub_4938F0(*(this + 2180));
      fld_e2171 = *(this + 2171);
      if ( fld_e2171 <= 10 )
        fld_e21712 = *(this + 2171);
      else
        fld_e21712 = 20 - fld_e2171;
      *(this + 2174) = -10 * fld_e21712;
      v5 = (double)(-10 * fld_e21712) * 0.01745328888888889;
      sub_492080(v5);
      sub_492080(v5);
      sub_492080(v5);
      return sub_492080(v5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// ============================================================
// §D 0x5C 补漏
// ============================================================
// 0x5C3190 sub_5C3190
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5C3190 sub_4D9760
int sub_5C3190()
{
  return sub_4D9760();
}



// ------------------------------------------------------------
// 0x5C4F00 sub_5C4F00
// ------------------------------------------------------------
// 调: sub_5C4F00 sub_4926A0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C4F00(int *this, int nArg2)
{
  int v3; // edx
  uint32_t *fld_e1554; // eax
  unsigned int v5; // esi
  int v6; // edx
  int v8; // [esp+Ch] [ebp+8h]

  --*(this + 2162);
  v3 = *this;
  *(this + 2150) = nArg2;
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int, int))(v3 + 888))(0, 0, 1000, 1000);
  sub_4926A0(*(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  fld_e1554 = (uint32_t *)*(this + 1554);
  *(this + 1543) = fld_e1554[2];
  *(this + 1544) = fld_e1554[3];
  *(this + 1540) = fld_e1554[7];
  *(uint8_t *)*(this + 1905) = 0;
  *(uint8_t *)(*(this + 1905) + 32) = 0;
  *(uint8_t *)(*(this + 1905) + 64) = 0;
  if ( *(this + 2150) == 1 )
  {
    *(uint8_t *)(*(this + 1905) + 96) = 1;
    *(uint8_t *)(*(this + 1905) + 128) = 1;
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) + 102;
  *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) + 1.0;
  return sub_41A590(v5, v6, v8);
}



// ------------------------------------------------------------
// 0x5C51E0 sub_5C51E0
// ------------------------------------------------------------
// 调: sub_5C51E0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C51E0(char *this, int nArg2, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  int pThis_771; // eax
  unsigned int pThis_2A0; // edi
  int v8; // edx
  int v9; // [esp+14h] [ebp+Ch]

  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;
  *((uint32_t *)this + 1892) = 0;
  *((uint32_t *)this + 1891) = 0;
  *((uint32_t *)this + 1897) = 0;
  *((uint32_t *)this + 1896) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1899) = 0;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      *((uint32_t *)this + 1894) = 1;
      if ( nArg2 == 0 )
        *((uint32_t *)this + 1899) = 50;
    }
  }
  else
  {
    pThis_771 = *((uint32_t *)this + 1905) + 32;
    *((uint32_t *)this + 1895) = 1;
    *((uint32_t *)this + 1899) = 50;
    *(float *)(pThis_771 + 4) = *(float *)(pThis_771 + 4) + *(float *)(pThis_771 + 4);
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;
    sub_41A590(pThis_2A0, v8, v9);
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5450 sub_5C5450
// ------------------------------------------------------------
// 调: sub_5C5450
int /*thiscall*/ sub_5C5450(int this, int nArg2, int nArg3)
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
    {
      *(uint32_t *)(this + 7564) = 1;
      if ( nArg2 == 0 )
        *(uint32_t *)(this + 7596) = -50;
    }
  }
  else
  {
    *(uint32_t *)(this + 7564) = 1;
    *(uint32_t *)(this + 7596) = -50;
    *(float *)(*(uint32_t *)(this + 7620) + 36) = *(float *)(*(uint32_t *)(this + 7620) + 36)
                                              + *(float *)(*(uint32_t *)(this + 7620) + 36);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C55C0 sub_5C55C0
// ------------------------------------------------------------
// 调: sub_5C55C0
int /*thiscall*/ sub_5C55C0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      *(this + 1892) = 2;
      if ( nArg2 == 0 )
        *(this + 1899) = 50;
    }
  }
  else
  {
    fld_e1905 = *(this + 1905);
    *(this + 1892) = 1;
    *(this + 1899) = 50;
    v5 = *(float *)(fld_e1905 + 36) * 0.5;
    result = fld_e1905 + 32;
    *(float *)(result + 4) = v5;
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C6330 sub_5C6330
// ------------------------------------------------------------
// 调: sub_5C6330 sub_4DA3B0
int /*thiscall*/ sub_5C6330(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // ebx
  int v7; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && rand() % 100 < 5
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2);
    if ( v5 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this)
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )
    {
      v6 = *this;
      v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 192))(this, 4, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(v6 + 580))(
        this,
        48023,
        10,
        0,
        0,
        0,
        0,
        v7 / 2);
    }
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x5C6560 sub_5C6560
// ------------------------------------------------------------
// 调: sub_5C6560
bool /*thiscall*/ sub_5C6560(void *this, void *pArg2)
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 601;
}



// ------------------------------------------------------------
// 0x5C65D0 sub_5C65D0
// ------------------------------------------------------------
// 调: sub_5C65D0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C65D0(uint32_t *this, char pszArg2)
{
  unsigned int v3; // edi
  int v4; // eax
  int v5; // edx

  *(this + 2186) = 1084227584;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;
  if ( pszArg2 != 0 )
    v4 = sub_41A5E0(v3) + 5;
  else
    v4 = sub_41A5E0(v3) - 5;
  sub_41A590(v3, v5, v4);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
}



// ------------------------------------------------------------
// 0x5C6700 sub_5C6700
// ------------------------------------------------------------
// 调: sub_5C6700
int /*thiscall*/ sub_5C6700(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint8_t *)(this + 7537) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = -50;
  return result;
}



// ------------------------------------------------------------
// 0x5C6940 sub_5C6940
// ------------------------------------------------------------
// 调: sub_5C6940 sub_4E5AF0 sub_4DB480
int /*thiscall*/ sub_5C6940(void *this, int nArg2, int nArg3, int nArg4)
{
  if ( (uint8_t)sub_4E5AF0(nArg2, this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 308))(nArg2) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, void *, uint32_t))(*(uint32_t *)nArg2 + 760))(nArg2, 3, 1092616192, 3, this, 0);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x5C6A90 sub_5C6A90
// ------------------------------------------------------------
// 调: sub_5C6A90
int /*thiscall*/ sub_5C6A90(int *this, int16_t uArg2)
{
  int fld_e2; // esi
  int v3; // ecx
  int result; // eax

  *(uint16_t *)(*(this + 1) + *(this + 2)) = uArg2;
  fld_e2 = *(this + 2) + 2;
  *(this + 2) = fld_e2;
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )
    return off_77F3FC(aCriticalError_40, v3);
  return result;
}



// ------------------------------------------------------------
// 0x5CBD40 sub_5CBD40
// ------------------------------------------------------------
// 调: sub_5CBD40 sub_4A50F0
int /*thiscall*/ sub_5CBD40(uint32_t *this)
{
  *this = &CNMonsterFlower::`vftable';
  return sub_4A50F0(this);
}



// ------------------------------------------------------------
// 0x5CF730 sub_5CF730
// ------------------------------------------------------------
// 调: sub_5CF730 sub_5CF520
int /*thiscall*/ sub_5CF730(int *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  return sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);
}



// ------------------------------------------------------------
// ============================================================
// §E 0x5D 补漏
// ============================================================
// 0x5D7730 sub_5D7730
// ------------------------------------------------------------
// 调: sub_5D7730 sub_5D6F80
int /*thiscall*/ sub_5D7730(void ***this)
{
  *this = &CNGuardBlock::`vftable';
  return sub_5D6F80(this);
}



// ------------------------------------------------------------
// 0x5DA8C0 sub_5DA8C0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5DA8C0 sub_4B2270
int /*thiscall*/ sub_5DA8C0(uint32_t *this)
{
  return sub_4B2270(this);
}



// ------------------------------------------------------------
// 0x59E780 sub_59E780
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_59E780 sub_59E570
int sub_59E780()
{
  return sub_59E570();
}



// ------------------------------------------------------------
// 0x5A4030 sub_5A4030
// ------------------------------------------------------------
// 调: sub_5A4030 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5A4030(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int v5; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )
  {
    v5 = *this;
    *(this + 1899) = 0;
    v6 = (*(int (/*stdcall*/ **)(uint32_t))(v5 + 672))(0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) - 0.30000001;
    sub_41A590(v6, v7, v8);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5A5170 sub_5A5170
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5A5170 sub_4DA1D0
int /*usercall*/ sub_5A5170@<eax>(uint32_t *uArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  return sub_4DA1D0(uArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x5AA370 sub_5AA370
// ------------------------------------------------------------
// 调: sub_5AA370 sub_41A5E0
int /*thiscall*/ sub_5AA370(int *this)
{
  int v2; // edi
  int fld_e1813; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 2 )
  {
    fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813;
  }
  result = *(this + 1639);
  if ( result == 0 && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA640 sub_5AA640
// ------------------------------------------------------------
// 调: sub_5AA640 sub_495250 sub_41A5E0 sub_5AA420 sub_699000
int /*thiscall*/ sub_5AA640(int this, unsigned int uArg2, int nArg3, int nArg4)
{
  int result; // eax

  sub_495250((uint8_t *)this, uArg2, nArg3, nArg4);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 2 )
    {
      sub_5AA420(this);
      result = sub_699000(this + 7640);  // 【clock_now(clk)】
      *(uint32_t *)(this + 8608) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA830 sub_5AA830
// ------------------------------------------------------------
// 调: sub_5AA830 sub_4E0120 sub_4926A0
char /*thiscall*/ sub_5AA830(int this)
{
  int pThis_348; // eax

  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 != 14 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_348 != 16 )
    {
      sub_4E0120((uint32_t *)this);
      switch ( *(uint32_t *)(this + 7148) )
      {
        case 0:
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1284))(this);
          break;
        case 4:
          (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(8);
          break;
        case 5:
          if ( *(uint32_t *)(this + 7252) != 0 )
          {
            if ( rand() % 100 < 10 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
              goto LABEL_21;
          }
          else
          {
            (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(13);
          }
          break;
        case 8:
          if ( *(uint32_t *)(this + 7252) != 0 )
          {
            if ( rand() % 100 < 10 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 17);
          }
          goto LABEL_14;
        case 0xD:
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 17);
          break;
        case 0xE:
        case 0xF:
          if ( *(uint32_t *)(this + 7252) != 0 )
LABEL_21:
            (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 1104))(4);
          else
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
          break;
        case 0x11:
          if ( *(uint32_t *)(this + 7252) != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 8);
LABEL_14:
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1308))(this, 0);
          break;
        default:
          break;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);
      }
      LOBYTE(pThis_348) = *(uint8_t *)(this + 8608);
      if ( (uint8_t)pThis_348 == 0 )
      {
        pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
        if ( pThis_348 == 0 )
        {
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this) == 4 )
          {
            sub_4926A0(*(uint32_t *)(this + 6164));
            LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 6164));
          }
          else
          {
            sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 12));
            LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(
                           this,
                           *(uint32_t *)(*(uint32_t *)(this + 6216) + 12));
          }
        }
      }
    }
  }
  return pThis_348;
}



// ------------------------------------------------------------
// 0x5AAD10 sub_5AAD10
// ------------------------------------------------------------
// 调: sub_5AAD10 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AAD10(int *this)
{
  int v2; // edx
  int fld_e1543; // eax
  int fld_e15432; // edi
  int v5; // eax

  v2 = *this;
  *(this + 81) = *(this + 2155);
  *(this + 2153) = 2;
  (*(void (/*stdcall*/ **)(int, uint32_t, int, int))(v2 + 888))(1, 0, 1000, 1000);
  fld_e1543 = sub_4924C0((int *)*(this + 1543), 0);
  *(int *)(fld_e1543 + 48) /= 10;
  fld_e15432 = *(this + 1543);
  sub_4910E0(fld_e15432);
  sub_493A60(fld_e15432, *(uint32_t *)(fld_e15432 + 32));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1541));
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  sub_4926A0(v5);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
}



// ------------------------------------------------------------
// 0x5AB060 sub_5AB060
// ------------------------------------------------------------
// 调: sub_5AB060 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*thiscall*/ sub_5AB060(int *this)
{
  int v2; // edx
  int fld_e1543; // eax
  int fld_e15432; // edi
  int v5; // eax

  v2 = *this;
  *(this + 81) = *(this + 2155);
  *(this + 2154) = 2;
  (*(void (/*stdcall*/ **)(int, uint32_t, int, int))(v2 + 888))(1, 0, 1000, 1000);
  fld_e1543 = sub_4924C0((int *)*(this + 1543), 0);
  *(int *)(fld_e1543 + 48) /= 10;
  fld_e15432 = *(this + 1543);
  sub_4910E0(fld_e15432);
  sub_493A60(fld_e15432, *(uint32_t *)(fld_e15432 + 32));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1541));
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  sub_4926A0(v5);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  return (*(int (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
}



// ------------------------------------------------------------
// 0x5AB4A0 sub_5AB4A0
// ------------------------------------------------------------
// 证: "FLYDRAGON_BITE"
// 调: sub_5AB4A0 sub_4926A0 sub_698F90
int /*thiscall*/ sub_5AB4A0(uint32_t *this)
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edi
  uint32_t *pThis_89C; // ebx

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
  fld_e1554 = (uint32_t *)*(this + 1554);
  v3 = *this;
  *((uint8_t *)this + 8608) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 196))(this, *fld_e1554);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "FLYDRAGON_BITE", -1, 0, 0);
  v5 = *this;
  *((uint8_t *)this + 8808) = 1;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 184))(this) == 4 )
    v6 = 5;
  else
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);
  v7 = *this;
  *(this + 2157) = v6;
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 188))(this);
  v8 = 0;
  pThis_89C = this + 2204;
  do
    *pThis_89C++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, v8++);
  while ( v8 < 3 );
  *(this + 2207) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  *((uint8_t *)this + 8789) = 0;
  *((uint8_t *)this + 8790) = 0;
  sub_698F90((int)(this + 2194), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 1554) + 16),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB6C0 sub_5AB6C0
// ------------------------------------------------------------
// 调: sub_5AB6C0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5AB6C0(char *this, int nArg2, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v7; // edx
  unsigned int pThis_2A02; // edi
  int v9; // edx
  int v10; // [esp+18h] [ebp+Ch]
  int v11; // [esp+18h] [ebp+Ch]

  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;
  *((uint32_t *)this + 1892) = 0;
  *((uint32_t *)this + 1891) = 0;
  *((uint32_t *)this + 1897) = 0;
  *((uint32_t *)this + 1896) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1899) = 0;
  *((uint32_t *)this + 1897) = 1;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 && nArg2 == 0 )
    {
      pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
      *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.30000001;
      sub_41A590(pThis_2A0, v7, v10);
      return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    }
  }
  else
  {
    pThis_2A02 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 0.30000001;
    sub_41A590(pThis_2A02, v9, v11);
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    *(uint8_t *)(*((uint32_t *)this + 1905) + 64) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5ABC20 sub_5ABC20
// ------------------------------------------------------------
// 调: sub_5ABC20 sub_4DC630 sub_5AAE70
int /*thiscall*/ sub_5ABC20(uint32_t *this)
{
  int result; // eax
  int v3; // edi
  uint16_t v4; // [esp+8h] [ebp-8h] BYREF
  uint16_t v5; // [esp+Ch] [ebp-4h] BYREF

  result = sub_4DC630(this);
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v5);
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v4);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, v5);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 23);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 896))(this, v5, v4);
    }
    else if ( result == 15 )
    {
      sub_5AAE70(this);
      return 15;
    }
    return v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5ABEF0 sub_5ABEF0
// ------------------------------------------------------------
// 调: sub_5ABEF0 sub_5AB800
int /*thiscall*/ sub_5ABEF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  char v5; // di
  int fld_e1554; // eax
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v5 = ArgList;
  if ( ArgList == 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 80
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v5 = 0;
    *(this + 81) = *(uint32_t *)(*(this + 2177) + 4 * (rand() % 100 < 50));
    *(this + 1813) = 0;
  }
  if ( *(this + 2201) == 18 )
  {
    fld_e1554 = *(this + 1554);
    v8 = *this;
    *((uint8_t *)this + 8808) = 0;
    *(this + 2201) = -1;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v8 + 208))(this, *(uint32_t *)(fld_e1554 + 16));
  }
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, 700, 700, 0, -2000, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    v10 = *this;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v10 + 896))(this, v11);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC140 sub_5AC140
// ------------------------------------------------------------
// 调: sub_5AC140 sub_5AB800
int /*thiscall*/ sub_5AC140(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  char v5; // di
  int result; // eax
  int v8; // edi
  int v9; // eax

  v5 = ArgList;
  if ( ArgList == 8 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) != 80 )
    v5 = 0;
  result = sub_5AB800(v5, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, 700, 700, 0, -2000, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    v8 = *this;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 896))(this, v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AFDD0 sub_5AFDD0
// ------------------------------------------------------------
// 调: sub_5AFDD0 sub_41A5E0
uint64_t /*thiscall*/ sub_5AFDD0(char *this)
{
  int pThis_2A0; // edi
  uint64_t result; // rax
  int v4; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 7539) = 16843009;
  *(uint32_t *)(this + 7543) = 16843009;
  *(uint32_t *)(this + 7547) = 16843009;
  *(uint32_t *)(this + 7551) = 16843009;
  *(this + 7555) = 1;
  pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0);
  v4 = sub_41A5E0(pThis_2A0 + 60);
  result = (uint64_t)((double)v4 * COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 74)));
  *((uint32_t *)this + 2160) = result;
  return result;
}



// ------------------------------------------------------------
// 0x5B1A60 sub_5B1A60
// ------------------------------------------------------------
// 调: sub_5B1A60 sub_4DC630 sub_4ABE10 sub_45FE80
int /*thiscall*/ sub_5B1A60(int *this)
{
  int result; // eax
  int v3; // edi
  void **v4; // eax
  int pObj; // eax
  int v6; // eax
  int fld_e21602; // ebx
  int v8; // eax
  int fld_e21603; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // [esp-14h] [ebp-20h]
  int fld_e2160; // [esp-10h] [ebp-1Ch]
  uint16_t v14; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630(this);
  v3 = result;
  if ( result != -1 )
  {
    if ( (uint16_t)result == 14 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v14);
      v4 = (void **)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
      pObj = sub_4ABE10((void *)0xBB8, *v4, 0);
      *(this + 2160) = pObj;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);
      *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2160) + 1040))(*(this + 2160)) = -1;
      *(uint8_t *)(*(this + 2160) + 8638) = 0;
      *(uint32_t *)(*(this + 2160) + 8640) = 1;
      fld_e2160 = *(this + 2160);
      v12 = v14;
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
      sub_45FE80(v6, v3, 0, v12, fld_e2160, 0, 0);
      fld_e21602 = *(uint32_t *)*(this + 2160);
      v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e21602 + 148))(*(this + 2160), v8);
      fld_e21603 = *(uint32_t *)*(this + 2160);
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(fld_e21603 + 112))(*(this + 2160), -3000, v11);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2160) + 1120))(*(this + 2160));
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2160) + 596))(*(this + 2160), 0);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2160) + 604))(*(this + 2160), 0);
    }
    return v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B1D20 sub_5B1D20
// ------------------------------------------------------------
// 调: sub_5B1D20
int /*thiscall*/ sub_5B1D20(int *this)
{
  int v2; // eax
  int v3; // edi
  int nRand; // edi
  int v5; // ebx
  int nRand2; // ebx
  int v8; // eax
  int v9; // eax
  int fld_e2153; // ecx
  int result; // eax
  uint32_t v12[10]; // [esp+8h] [ebp-2Ch]
  int v13; // [esp+30h] [ebp-4h]

  v2 = *this;
  v12[0] = 1;
  v12[1] = 2;
  v12[2] = 3;
  v12[3] = 4;
  v12[4] = 5;
  v12[5] = 6;
  v12[6] = 7;
  v12[7] = 8;
  v12[8] = 9;
  v12[9] = 10;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v2 + 200))(this) + 148) == v12[*(this + 2153)]
    && *((uint8_t *)this + 8608) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      v13 = 100;
      do
      {
        v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        nRand = v3 + rand() % 400 - 201;
        v5 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
        nRand2 = v5 + rand() % 100 - 51;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, nRand, nRand2, 0) != 0 )
          break;
      }
      while ( v13-- > 0 );
      v13 = *this;
      v8 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v13 + 152))(this, 150, 1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, uint32_t, uint32_t, int))(v13 + 584))(
        this,
        nRand,
        nRand2,
        0,
        nRand,
        nRand2,
        30072,
        *(this + 2150),
        0,
        v8);
    }
    *((uint8_t *)this + 8608) = 1;
  }
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  fld_e2153 = *(this + 2153);
  if ( *(uint32_t *)(v9 + 148) == v12[fld_e2153] + 1 )
  {
    *((uint8_t *)this + 8608) = 0;
    *(this + 2153) = fld_e2153 + 1;
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 15, 0, 2, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4A50 sub_5B4A50
// ------------------------------------------------------------
// 调: sub_5B4A50 sub_460230
int /*userpurge*/ sub_5B4A50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int result; // eax
  int nRand; // eax
  int v10; // edi
  int v11; // et2
  int v12; // edx
  int v13; // edi
  int nRand2; // ebx
  int v15; // edi
  int nRand3; // eax
  int v17; // edx
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  uint32_t v26[3]; // [esp+4h] [ebp-1Ch]
  uint16_t v27[3]; // [esp+10h] [ebp-10h] BYREF
  bool nRand4; // [esp+16h] [ebp-Ah]
  char nRand5; // [esp+17h] [ebp-9h]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]
  int v32; // [esp+28h] [ebp+8h]
  int nRand6; // [esp+28h] [ebp+8h]
  int nArg72; // [esp+2Ch] [ebp+Ch]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v10 = nArg4 - nArg5 + 1;
    v11 = nRand % v10;
    result = nRand / v10;
    v12 = nArg5 + v11;
    if ( nArg5 + v11 > 0 )
    {
      v26[0] = 250;
      v26[1] = 252;
      v26[2] = 253;
      v31 = v12;
      do
      {
        if ( nArg7 == -1 )
          nArg72 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1) + 132) + 108) + 112);
        else
          nArg72 = nArg7;
        v32 = 100;
        do
        {
          v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
          nRand2 = v13 + rand() % 40 - 20;
          v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
          nRand3 = rand();
          v17 = *pArg1;
          v30 = v15 + nRand3 % 20 - 10;
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v17 + 136))(pArg1, nRand2, v30, 0) != 0 )
            break;
        }
        while ( v32-- > 0 );
        v27[0] = rand() % 200 + 100;
        v27[1] = rand() % 100 + 50;
        nRand4 = rand() % 2 == 0;
        nRand5 = 3 - (rand() % 2 != 0);
        v27[2] = rand() % 60 + 40;
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 80))(pArg1, nArg2, nArg3);
        pArg1[2159] = sub_460230(v19);
        if ( nArg6 == -1 )
          nRand6 = v26[rand() % 3];
        else
          nRand6 = nArg6;
        v20 = *pArg1;
        nArg3 = 0;
        nArg2 = 0;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint16_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 152))(
                pArg1,
                1,
                v27,
                8,
                pArg1[2159],
                0,
                0);
        v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, v21);
        v23 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*pArg1 + 376))(pArg1, nArg72, nRand2, v30, v22 + 10);
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v20 + 592))(pArg1, nRand6, v23);
        --v31;
      }
      while ( v31 != 0 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4D10 sub_5B4D10
// ------------------------------------------------------------
// 调: sub_5B4D10 sub_41A5E0
int /*thiscall*/ sub_5B4D10(int *this)
{
  int v2; // edi
  int fld_e1813; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 5 )
  {
    fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813;
  }
  result = *(this + 1639);
  if ( result == 0 && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B51D0 sub_5B51D0
// ------------------------------------------------------------
// 调: sub_5B51D0 sub_41A5E0
int /*thiscall*/ sub_5B51D0(void *this)
{
  int nRand; // ebx
  int nRand2; // eax
  int v4; // edi
  int pThis_2A0; // ebx
  int pThis_2A02; // ebx
  uint64_t v7; // rax
  int pThis_2A03; // ebx
  int pThis_2A04; // ebx
  uint64_t v10; // rax
  int nRand22; // [esp+Ch] [ebp-18h]
  int v13; // [esp+Ch] [ebp-18h]
  float v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+14h] [ebp-10h]
  float v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  BOOL v19; // [esp+20h] [ebp-4h]

  nRand = rand() % 2;
  nRand2 = rand() % 2;
  v4 = 3 - (nRand2 != 0);
  nRand22 = nRand2;
  v19 = nRand == 0;
  if ( nRand != 4 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
    v18 = sub_41A5E0(pThis_2A0 + 816);
    v17 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 830));
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
    v15 = sub_41A5E0(pThis_2A02 + 816);
    v7 = (uint64_t)(double)(int)(uint64_t)((double)v15 * COERCE_FLOAT(sub_41A5E0(pThis_2A02 + 830)));
    (*(void (/*fastcall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
      this,
      HIDWORD(v7),
      0,
      v7,
      (uint64_t)(double)(int)(uint64_t)((double)v18 * v17),
      0,
      0,
      0);
    nRand2 = nRand22;
  }
  if ( nRand2 != 4 )
  {
    pThis_2A03 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
    v13 = sub_41A5E0(pThis_2A03 + 816);
    v14 = COERCE_FLOAT(sub_41A5E0(pThis_2A03 + 830));
    pThis_2A04 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
    v16 = sub_41A5E0(pThis_2A04 + 816);
    v10 = (uint64_t)((double)(int)(uint64_t)((double)v16 * COERCE_FLOAT(sub_41A5E0(pThis_2A04 + 830)))
                           * 0.34999999);
    (*(void (/*fastcall*/ **)(void *, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
      this,
      HIDWORD(v10),
      1,
      v10,
      (uint64_t)((double)(int)(uint64_t)((double)v13 * v14) * 0.34999999),
      0,
      0,
      0);
  }
  (*(void (/*thiscall*/ **)(void *, BOOL, int))(*(uint32_t *)this + 896))(this, v19, v4);
  (*(void (/*thiscall*/ **)(void *, BOOL))(*(uint32_t *)this + 148))(this, v19);
  return (*(int (/*thiscall*/ **)(void *, BOOL))(*(uint32_t *)this + 144))(this, v19);
}



// ------------------------------------------------------------
// 0x5B58D0 sub_5B58D0
// ------------------------------------------------------------
// 调: sub_5B58D0 sub_491C10
int /*thiscall*/ sub_5B58D0(int **this, int nArg2)
{
  int result; // eax
  int fld_e2152; // ecx
  int v5; // edi
  int fld_e21522; // eax
  int *v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax

  result = nArg2;
  if ( (int *)nArg2 == *(this + 2152) )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this);
    if ( result == 14 && (int)*(this + 2154) > 1 )
    {
      sub_491C10(**(this + 1554));
      fld_e2152 = (int)*(this + 2152);
      *(this + 2154) = (int *)((char *)*(this + 2154) - 1);
      *(this + 2156) = nullptr;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2152) + 916))(*(this + 2152));
      fld_e21522 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2152) + 120))(*(this + 2152));
      v7 = *this;
      v8 = v5 - fld_e21522;
      v9 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v10 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v9);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v10);
      return ((int (/*thiscall*/ *)(int **, int))v7[28])(this, v11 - v8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B5EE0 sub_5B5EE0
// ------------------------------------------------------------
// 调: sub_5B5EE0
int /*thiscall*/ sub_5B5EE0(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7584) = 2;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4)
                                             + *(float *)(*(uint32_t *)(this + 7620) + 4);
  return result;
}



// ------------------------------------------------------------
// 0x5B6080 sub_5B6080
// ------------------------------------------------------------
// 调: sub_5B6080
int /*thiscall*/ sub_5B6080(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 260
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 263
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 264)
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) != 0 )
      {
        return pObj;
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5B6240 sub_5B6240
// ------------------------------------------------------------
// 调: sub_5B6240 sub_4EB2C0
char /*thiscall*/ sub_5B6240(uint32_t *this)
{
  int *v2; // eax
  char result; // al

  v2 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  result = sub_4EB2C0(v2, 4.0);
  *(this + 2157) = 1065353216;
  *(this + 1822) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x5B6330 sub_5B6330
// ------------------------------------------------------------
// 调: sub_5B6330
int /*thiscall*/ sub_5B6330(int this, int nArg2, int nArg3)
{
  int result; // eax

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
      *(uint8_t *)(this + 7534) = 1;
  }
  else
  {
    result = *(uint32_t *)(this + 7620) + 160;
    *(uint32_t *)(this + 7568) = 2;
    *(uint32_t *)(this + 7596) = 50;
    *(float *)(result + 4) = *(float *)(result + 4) + *(float *)(result + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBE20 sub_5BBE20
// ------------------------------------------------------------
// 调: sub_5BBE20 sub_5BB450
int /*thiscall*/ sub_5BBE20(void *this)
{
  sub_5BB450();
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1320))(this);
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1312))(this);
}



// ------------------------------------------------------------
// 0x5BCFB0 sub_5BCFB0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5BCFB0 sub_594370
int sub_5BCFB0()
{
  return sub_594370();
}



// ------------------------------------------------------------
// 0x5C4C00 sub_5C4C00
// ------------------------------------------------------------
// 调: sub_5C4C00 sub_491C10
void /*thiscall*/ sub_5C4C00(uint32_t *this, int nArg2)
{
  int fld_e1554; // eax
  int fld_e2159; // edx

  if ( *(this + 2154) == 1
    && nArg2 == *(this + 2155)
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14
    && (int)*(this + 2157) > 1 )
  {
    fld_e1554 = sub_491C10(*(uint32_t *)(*(this + 1554) + 16));
    fld_e2159 = *(this + 2159) + 1;
    *(this + 2159) = fld_e2159;
    if ( fld_e2159 >= 5 * fld_e1554 / 1000 )
    {
      --*(this + 2157);
      *(this + 2159) = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 120))(*(this + 2155));
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 916))(*(this + 2155));
  }
}



// ------------------------------------------------------------
// 0x5C5020 sub_5C5020
// ------------------------------------------------------------
// 调: sub_5C5020 sub_4926A0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5020(uint32_t *this)
{
  int fld_e2151; // ecx
  int fld_e2152; // edx
  uint8_t *fld_e1905; // eax
  int v5; // edx
  unsigned int v6; // esi
  int v7; // edx
  int v9; // [esp+4h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  fld_e2151 = *(this + 2151);
  fld_e2152 = *(this + 2152);
  *(this + 1540) = *(this + 2153);
  fld_e1905 = (uint8_t *)*(this + 1905);
  *(this + 1543) = fld_e2151;
  *(this + 1544) = fld_e2152;
  *fld_e1905 = 1;
  *(uint8_t *)(*(this + 1905) + 32) = 1;
  *(uint8_t *)(*(this + 1905) + 64) = 1;
  if ( *(this + 2150) == 1 )
  {
    *(uint8_t *)(*(this + 1905) + 96) = 0;
    *(uint8_t *)(*(this + 1905) + 128) = 0;
  }
  v5 = *this;
  *(this + 2150) = 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3) + 102;
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;
  return sub_41A590(v6, v7, v9);
}



// ------------------------------------------------------------
// 0x5C5300 sub_5C5300
// ------------------------------------------------------------
// 调: sub_5C5300 sub_5C4F00 sub_432FA0 sub_4D9210 sub_4E4A50
int /*thiscall*/ sub_5C5300(uint32_t *this, int nArg2)
{
  int result; // eax
  int nRand; // eax
  int v5; // et2
  int v6; // edx
  int v7; // edi
  int nRand2; // edi
  int v9; // ebx
  int nRand3; // ebx
  int nRand4; // eax
  int v12; // [esp+4h] [ebp-4h]
  int v13; // [esp+10h] [ebp+8h]

  sub_5C4F00(nArg2);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    nRand = rand();
    v5 = nRand % 3;
    result = nRand / 3;
    v6 = v5 + 3;
    if ( v5 + 3 > 0 )
    {
      v12 = v6;
      do
      {
        v13 = 100;
        while ( 1 )
        {
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          nRand2 = v7 + rand() % 200 - 100;
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
          nRand3 = v9 + rand() % 70 - 35;
          if ( sub_4D9210(this, nRand2, nRand3, nullptr) )
            break;
          result = --v13;
          if ( v13 <= 0 )
            goto LABEL_9;
        }
        nRand4 = rand() % 2;
        result = sub_4E4A50(nRand2, (int)this, 1007 - (nRand4 != 0), 1, nRand2, nRand3, 0, 4, 0, 0, 0);
LABEL_9:
        --v12;
      }
      while ( v12 != 0 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5520 sub_5C5520
// ------------------------------------------------------------
// 调: sub_5C5520 sub_5C4F00 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5520(void *this, int nArg2)
{
  unsigned int pThis_2A0; // esi
  int v4; // edx
  int v6; // [esp+Ch] [ebp+8h]

  sub_5C4F00(nArg2);
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 158;
  *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;
  return sub_41A590(pThis_2A0, v4, v6);
}



// ------------------------------------------------------------
// 0x5C5640 sub_5C5640
// ------------------------------------------------------------
// 调: sub_5C5640
int /*thiscall*/ sub_5C5640(int this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_1DC4; // eax
  double v5; // st7

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
    {
      *(uint32_t *)(this + 7568) = 2;
      if ( nArg2 == 0 )
        *(uint32_t *)(this + 7596) = 50;
    }
  }
  else
  {
    fld_1DC4 = *(uint32_t *)(this + 7620);
    *(uint32_t *)(this + 7568) = 1;
    *(uint32_t *)(this + 7596) = 50;
    v5 = *(float *)(fld_1DC4 + 36);
    result = fld_1DC4 + 32;
    *(float *)(result + 4) = v5 + v5;
    *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68)
                                              + *(float *)(*(uint32_t *)(this + 7620) + 68);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C63E0 sub_5C63E0
// ------------------------------------------------------------
// 调: sub_5C63E0 sub_4E4A50
int /*thiscall*/ sub_5C63E0(uint8_t *this)
{
  int result; // eax
  int pThis_715; // ebx
  int v4; // edi
  int pThis_98; // eax
  int pThis_7152; // [esp+4h] [ebp-4h]

  result = *((uint32_t *)this + 1813);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      pThis_715 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1813) + 120))(*((uint32_t *)this + 1813));
      pThis_7152 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1813) + 124))(*((uint32_t *)this + 1813));
      v4 = 30094;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this) == 60006 )
        v4 = 30380;
      pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
      result = sub_4E4A50(v4, (int)this, v4, 1, pThis_715, pThis_7152, 0, pThis_98, 0, 0, 0);
      *(this + 8744) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C6590 sub_5C6590
// ------------------------------------------------------------
// 调: sub_5C6590
int /*thiscall*/ sub_5C6590(uint8_t *this)
{
  int v1; // eax

  v1 = *(uint32_t *)this;
  *(this + 8748) = 0;
  return (*(int (**)(void))(v1 + 1312))();
}



// ------------------------------------------------------------
// 0x5C6640 sub_5C6640
// ------------------------------------------------------------
// 调: sub_5C6640 sub_4E5B50 sub_4DB480
int /*thiscall*/ sub_5C6640(void *this, uint32_t *pArg2, int nArg3, int nArg4)
{
  int pObj; // eax

  if ( sub_4E5B50((int)pArg2, (int)this) && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )
  {
    pObj = __RTDynamicCast(
           (int)pArg2,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDActiveObject `RTTI Type Descriptor',
           0);
    (*(void (/*thiscall*/ **)(int, int, int, int, void *, uint32_t))(*(uint32_t *)pObj + 760))(pObj, 4, 1120403456, 10, this, 0);
  }
  return sub_4DB480((int)this, pArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x5C67B0 sub_5C67B0
// ------------------------------------------------------------
// 调: sub_5C67B0
bool /*thiscall*/ sub_5C67B0(void *this, void *pArg2)
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 603;
}



// ------------------------------------------------------------
// 0x5C69A0 sub_5C69A0
// ------------------------------------------------------------
// 调: sub_5C69A0
int /*thiscall*/ sub_5C69A0(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint8_t *)(this + 7538) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// ------------------------------------------------------------
// 0x5C6AD0 sub_5C6AD0
// ------------------------------------------------------------
// 调: sub_5C6AD0 sub_4D9760
int /*thiscall*/ sub_5C6AD0(uint32_t *this)
{
  uint32_t *pThis_867; // eax

  sub_4D9760(this);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
  if ( *(this + 2156) < 0x10u )
    pThis_867 = this + 2151;
  else
    pThis_867 = (uint32_t *)*(this + 2151);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_867, 9, 0, 0);
  if ( *(this + 2163) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2158, -1, 0, 0);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(this, *(this + 2158), -1, 0, 0);
}



// ------------------------------------------------------------
// 0x5CDA70 sub_5CDA70
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5CDA70 sub_5CD9B0
int sub_5CDA70()
{
  return sub_5CD9B0();
}



// ------------------------------------------------------------
// 0x5CF7D0 sub_5CF7D0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_5CF7D0 sub_4DC630
int /*thiscall*/ sub_5CF7D0(uint32_t *this)
{
  return sub_4DC630(this);
}



// ------------------------------------------------------------
// 0x5D7AD0 sub_5D7AD0
// ------------------------------------------------------------
// 调: sub_5D7AD0 sub_5D6E40
int /*thiscall*/ sub_5D7AD0(uint32_t *this)
{
  *this = &CNHeavenExpeller::`vftable';
  return sub_5D6E40();
}



// ------------------------------------------------------------
// 0x592BF0 sub_592BF0
// ------------------------------------------------------------
// 调: sub_592BF0
void /*thiscall*/ sub_592BF0(uint8_t *this)
{
  *(this + 8600) = 0;
}



// ------------------------------------------------------------
// 0x5A1540 sub_5A1540
// ------------------------------------------------------------
// 调: sub_5A1540 sub_59B130
int sub_5A1540()
{
  return sub_59B130(0);
}



// ------------------------------------------------------------
// 0x5A4090 sub_5A4090
// ------------------------------------------------------------
// 调: sub_5A4090 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5A4090(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int v5; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )
  {
    v5 = *this;
    *(this + 1899) = 30;
    v6 = (*(int (/*stdcall*/ **)(uint32_t))(v5 + 672))(0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) + 0.30000001;
    sub_41A590(v6, v7, v8);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AA340 sub_5AA340
// ------------------------------------------------------------
// 调: sub_5AA340
void /*thiscall*/ sub_5AA340(uint32_t *this)
{
  *(this + 2151) = 0;
}



// ------------------------------------------------------------
// 0x5AA3F0 sub_5AA3F0
// ------------------------------------------------------------
// 调: sub_5AA3F0 sub_4D9170
int /*thiscall*/ sub_5AA3F0(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( pArg2 == this )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 45230);
  return result;
}



// ------------------------------------------------------------
// 0x5AA6A0 sub_5AA6A0
// ------------------------------------------------------------
// 调: sub_5AA6A0 sub_699000 sub_698F90
char /*thiscall*/ sub_5AA6A0(int this, char pszArg2)
{
  int fld_2228; // ebx
  int pThis_2210; // edi
  int fld_2244; // ebx
  int v6; // eax
  int fld_2204; // eax
  unsigned int fld_2208; // ebx

  fld_2228 = *(uint32_t *)(this + 8744);
  pThis_2210 = this + 8720;
  if ( sub_699000(this + 8720) >= fld_2228 || (fld_2244 = *(uint32_t *)(this + 8772), (v6 = sub_699000(this + 8748)) >= fld_2244) && pszArg2 == 1 )  // 【clock_now(clk)】
  {
    fld_2204 = *(uint32_t *)(this + 8708);
    if ( fld_2204 != 0 )
      fld_2208 = (*(uint32_t *)(this + 8712) - fld_2204) >> 2;
    else
      fld_2208 = 0;
    *(uint32_t *)(this + 324) = *(uint32_t *)(*(uint32_t *)(this + 8708) + 4 * (rand() % fld_2208));
    *(uint8_t *)(pThis_2210 + 13) = 0;
    *(uint8_t *)(pThis_2210 + 14) = 0;
    sub_698F90(pThis_2210, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint8_t *)(this + 8761) = 0;
    *(uint8_t *)(this + 8762) = 0;
    LOBYTE(v6) = sub_698F90(this + 8748, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5AAA20 sub_5AAA20
// ------------------------------------------------------------
// 证: "FLYDRAGON_CRY"
// 调: sub_5AAA20 sub_41A5E0 sub_495890 sub_4926A0
int /*thiscall*/ sub_5AAA20(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edi
  int v7; // edi
  uint64_t v8; // rax
  uint32_t *fld_e28; // edi
  int v10; // eax
  int v11; // eax
  int v13; // [esp+Ch] [ebp-Ch]
  float v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]

  v2 = *this;
  *(this + 2155) = *(this + 81);
  if ( (*(int (**)(void))(v2 + 184))() == 4 )
    v3 = 5;
  else
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this);
  v4 = *this;
  *(this + 2157) = v3;
  *(this + 2158) = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 188))(this);
  v5 = *this;
  *(this + 2153) = 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 672))(this, 3);
  v15 = sub_41A5E0(v6 + 816);
  v14 = COERCE_FLOAT(sub_41A5E0(v6 + 830));
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v13 = sub_41A5E0(v7 + 816);
  v8 = (uint64_t)((double)(int)(uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v7 + 830))) * 1.5);
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    HIDWORD(v8),
    0,
    v8,
    (uint64_t)((double)(int)(uint64_t)((double)v15 * v14) * 1.5),
    0,
    0,
    0);
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[6] != 1142292480 )
  {
    fld_e28[6] = 1142292480;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 200);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 44));
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v10);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 608);
  v11 = *this;
  *((uint8_t *)this + 8701) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v11 + 212))(
           this,
           "FLYDRAGON_CRY",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AAE70 sub_5AAE70
// ------------------------------------------------------------
// 证: "FLYDRAGON_BITE"
// 调: sub_5AAE70 sub_4926A0
int /*thiscall*/ sub_5AAE70(uint32_t *this)
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
  fld_e1554 = (uint32_t *)*(this + 1554);
  v3 = *this;
  *((uint8_t *)this + 8608) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 196))(this, *fld_e1554);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "FLYDRAGON_BITE",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB180 sub_5AB180
// ------------------------------------------------------------
// 调: sub_5AB180 sub_4924C0 sub_4910E0 sub_493A60 sub_4926A0
int /*usercall*/ sub_5AB180@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int result; // eax
  int v4; // edi
  int v5; // edi
  int v6; // edx
  int v7; // eax

  result = pArg1[2154];
  if ( result != 0 )
  {
    if ( result == 1 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
      if ( *(uint8_t *)(result + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 604))(pArg1, 0);
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
        if ( (uint8_t)result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    if ( result == 0 )
    {
      *(uint32_t *)(pArg1[28] + 24) = 0;
      *(uint32_t *)(pArg1[28] + 36) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0,
        nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      if ( *((uint8_t *)pArg1 + 8700) != 0 )
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 500;
        v5 = *(uint32_t *)(pArg1[1554] + 20);
        sub_4910E0(v5);
        sub_493A60(v5, *(uint32_t *)(v5 + 32));
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 20));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 20));
      }
      else
      {
        *(uint32_t *)(sub_4924C0(0) + 48) = 2000;
        v4 = *(uint32_t *)(pArg1[1554] + 20);
        sub_4910E0(v4);
        sub_493A60(v4, *(uint32_t *)(v4 + 32));
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 20));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 20));
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 24));
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 28));
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(
          pArg1,
          -100,
          *(uint32_t *)(pArg1[1554] + 24),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(
          pArg1,
          100,
          *(uint32_t *)(pArg1[1554] + 28),
          0,
          0,
          0,
          0);
      }
      sub_4926A0(*(uint32_t *)(pArg1[1554] + 36));
      sub_4926A0(*(uint32_t *)(pArg1[1554] + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(
        pArg1,
        -200,
        *(uint32_t *)(pArg1[1554] + 36),
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(
        pArg1,
        200,
        *(uint32_t *)(pArg1[1554] + 40),
        0,
        0,
        0,
        0);
      v6 = *pArg1;
      pArg1[2154] = 1;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 80))(pArg1);
      return sub_424120(*(uint32_t **)(v7 + 132), 2, 300);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AB5B0 sub_5AB5B0
// ------------------------------------------------------------
// 调: sub_5AB5B0 sub_698F90 sub_4926A0
int /*thiscall*/ sub_5AB5B0(int **this)
{
  int pThis_869; // ecx

  pThis_869 = (int)(this + 2153);
  *(uint8_t *)(pThis_869 + 13) = 0;
  *(uint8_t *)(pThis_869 + 14) = 0;
  sub_698F90(pThis_869, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_4926A0(**(this + 1554));
  return ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
           this,
           100,
           **(this + 1554),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5AB800 sub_5AB800
// ------------------------------------------------------------
// 调: sub_5AB800 sub_4E33D0 sub_4926A0 sub_5AB060 sub_5AAD10
void /*userpurge*/ sub_5AB800(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // edi
  int v8; // eax
  int v9; // eax

  v7 = pDwArg1[1639];
  pDwArg1[2174] = 1000;
  sub_4E33D0(pDwArg1, ArgList, fArg2, ArgList, nArg4, *(float *)&nArg5, *(float *)&nArg6);
  if ( ArgList != 5 )
  {
    if ( ArgList == 3 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1308))(pDwArg1, 1);
    if ( v7 != 14 && ArgList == 14 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 16));
      v8 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      sub_4926A0(v8);
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 32));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
        pDwArg1,
        100,
        *(uint32_t *)(pDwArg1[1554] + 32),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
    }
    if ( v7 != 16 && ArgList == 16 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 48));
      v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      sub_4926A0(v9);
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 32));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
        pDwArg1,
        100,
        *(uint32_t *)(pDwArg1[1554] + 32),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
    }
    if ( v7 == 14 )
    {
      if ( ArgList != 14 )
        sub_5AB060(pDwArg1);
    }
    else if ( v7 == 16 && ArgList != 16 )
    {
      sub_5AAD10(pDwArg1);
    }
  }
}



// ------------------------------------------------------------
// 0x5ABCC0 sub_5ABCC0
// ------------------------------------------------------------
// 调: sub_5ABCC0 sub_5AB9B0 sub_41A5E0 sub_699000
int /*thiscall*/ sub_5ABCC0(uint8_t *this)
{
  int result; // eax
  int pThis_612; // eax
  int v4; // ecx
  int v5; // edi
  int pThis_98; // eax

  sub_5AB9B0();
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 7028));
    if ( result == 1 )
    {
      result = sub_699000((int)(this + 8784));  // 【clock_now(clk)】
      if ( result > 0 )
      {
        pThis_612 = *((uint32_t *)this + 1554);
        v4 = *(uint32_t *)(pThis_612 + 32);
        result = pThis_612 + 32;
        if ( *(uint8_t *)(v4 + 170) == 1 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
            this,
            0,
            1400,
            1400,
            0,
            -4000,
            1);
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);
          v5 = *(uint32_t *)this;
          pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, 4);
          result = (*(int (/*thiscall*/ **)(uint8_t *, int))(v5 + 896))(this, pThis_98);
          *(this + 8797) = 0;
          *(this + 8798) = 0;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5AC000 sub_5AC000
// ------------------------------------------------------------
// 调: sub_5AC000 sub_5AB9B0
int /*thiscall*/ sub_5AC000(char *this)
{
  int result; // eax
  int v3; // ebx
  int *pThis_1C; // edi
  int pObj; // ecx
  bool v6; // zf
  double v7; // st7
  int v8; // edx
  int pThis_89B; // eax
  int v10; // [esp+4h] [ebp-8h]
  int *pThis_2270; // [esp+8h] [ebp-4h]

  result = sub_5AB9B0();
  if ( *((uint32_t *)this + 2201) != 18 )
  {
LABEL_11:
    *(this + 8808) = 0;
    return result;
  }
  v3 = 0;
  pThis_2270 = (int *)(this + 8816);
  do
  {
    pThis_1C = *((int **)this + 28);
    pObj = *pThis_1C;
    v6 = *pThis_1C == 0;
    v10 = *pThis_2270;
    *((uint8_t *)pThis_1C + 124) = 1;
    if ( !v6 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
    {
      v7 = (double)v10;
      if ( *(float *)&pThis_1C[v3 + 1] != v7 )
      {
        *(float *)&pThis_1C[v3 + 1] = v7;
        *((uint8_t *)pThis_1C + 196) = 1;
      }
    }
    ++v3;
    ++pThis_2270;
  }
  while ( v3 < 3 );
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, *((uint32_t *)this + 2207));
  v8 = *(uint32_t *)this;
  if ( *(this + 8808) == 1 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(v8 + 200))(this);
    if ( *(int *)(result + 148) <= 2 )
      return result;
    pThis_89B = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 2203) + 28))(*((uint32_t *)this + 2203));
    result = (*(int (/*thiscall*/ **)(char *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
               this,
               50806,
               0,
               pThis_89B,
               0,
               50,
               0,
               20,
               4,
               0,
               0,
               0);
    goto LABEL_11;
  }
  result = (*(int (/*thiscall*/ **)(char *, uint32_t))(v8 + 208))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  *((uint32_t *)this + 1639) = 0;
  *((uint32_t *)this + 2201) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x5AFCC0 sub_5AFCC0
// ------------------------------------------------------------
// 调: sub_5AFCC0 sub_4E6770
int /*thiscall*/ sub_5AFCC0(uint32_t *this, uint8_t *uArg2, uint32_t *uArg3, int nArg4, int *pDwArg5, float *pArg6, int nArg7)
{
  int result; // eax

  result = sub_4E6770(this, uArg2, uArg3, nArg4, pDwArg5, pArg6, 0);  // 【伤害流水线 vt+628（研究 P14 九步公式）】
  if ( *uArg2 != 0 )
    result *= 2;
  return result;
}



// ------------------------------------------------------------
// 0x5AFE40 sub_5AFE40
// ------------------------------------------------------------
// 调: sub_5AFE40
char /*cdecl*/ sub_5AFE40(int nArg1)
{
  unsigned int i; // edx

  for ( i = 0; dword_9B9424 != 0 && i < (dword_9B9428 - dword_9B9424) >> 2; ++i )
  {
    if ( *(uint32_t *)(dword_9B9424 + 4 * i) == nArg1 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5B1BA0 sub_5B1BA0
// ------------------------------------------------------------
// 调: sub_5B1BA0 sub_4E0120
int /*thiscall*/ sub_5B1BA0(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787) - 4;
  switch ( *(this + 1787) )
  {
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_8;
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand2 = rand();
        v4 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v4 < 30 )
          goto LABEL_12;
      }
      else
      {
LABEL_8:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
      result = *(this + 1813);
      if ( result != 0 )
        goto LABEL_12;
      break;
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_12:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B1EC0 sub_5B1EC0
// ------------------------------------------------------------
// 调: sub_5B1EC0 sub_4DC390
int /*thiscall*/ sub_5B1EC0(uint8_t *this, int *pDwArg2, int nArg3)
{
  int result; // eax

  result = sub_4DC390(pDwArg2, nArg3);
  if ( result != 3 && *(this + 8644) != 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3);
    *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.69999999);
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B4C30 sub_5B4C30
// ------------------------------------------------------------
// 调: sub_5B4C30
int /*thiscall*/ sub_5B4C30(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7580) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// ------------------------------------------------------------
// 0x5B4D90 sub_5B4D90
// ------------------------------------------------------------
// 调: sub_5B4D90 sub_5B4A50 sub_4DA3B0
int /*thiscall*/ sub_5B4D90(void (/*thiscall*/ ***this)(int, void *, uint32_t), int nArg2, int nArg3, int nArg4)  // 【一类的覆写仅存在于 0x59-0x5B 段（见各文件头）】
{
  int v5; // edi
  uint32_t *v6; // eax

  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && rand() % 100 < 10 )
  {
    (**(this + 2150))((int)(this + 2150), this, *(this + 1814));
  }
  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) == 0
    && rand() % 100 < 15
    && __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishKing `RTTI Type Descriptor', 0) != 0 )
  {
    sub_5B4A50(1, 1, -1, -1);
  }
  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  if ( ((int (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[184])(this) > 0
    && ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) == 1
    && *(this + 2159) == (void (/*thiscall*/ **)(int, void *, uint32_t))0xFFFF
    && rand() % 100 < 2
    && __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishRukuku `RTTI Type Descriptor', 0) != 0 )
  {
    v6 = (uint32_t *)((int (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[85])(this);
    sub_5B4A50(1, 1, *v6, -1);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x5B5390 sub_5B5390
// ------------------------------------------------------------
// 证: "ZGM_ATTACK" | "ZGM_ATTACH"
// 调: sub_5B5390 sub_5B4ED0 sub_4E5F70 sub_5B4A50 sub_41A5E0
int /*usercall*/ sub_5B5390@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  uint8_t *pMem; // edi
  int v9; // ebx
  uint8_t *v10; // eax
  int v11; // edx
  int pObj2; // eax
  int v13; // ebx
  int pObj3; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp+4Ch] [ebp-40h]
  float v23; // [esp+5Ch] [ebp-30h]
  int v24; // [esp+60h] [ebp-2Ch] BYREF
  int v25; // [esp+64h] [ebp-28h] BYREF
  void *pBuf[5]; // [esp+68h] [ebp-24h] BYREF
  int v27; // [esp+7Ch] [ebp-10h]
  int v28; // [esp+88h] [ebp-4h]

  pObj = pDwArg1[2152];
  if ( pObj == 0 )
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) != 9 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]);
    if ( (uint8_t)result == 0 )
      return result;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 840))(pDwArg1[2152]) != 5 )
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 9, 0, 0, 0);
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 200))(pDwArg1, nArg3, nArg2) + 170) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
    {
      v24 = 0;
      v25 = 0;
      memset(pBuf, 0, 16);
      sub_5B4ED0(&v24, &v25, pBuf);
      sub_4E5F70(nArg2, (int)pDwArg1, pDwArg1[2152], (float *)&v24, 1, 1);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATTACK", -1, 0, 0);
    }
    if ( pDwArg1[2153] == 0
      && __RTDynamicCast((int)pDwArg1, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishKing `RTTI Type Descriptor', 0) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 && rand() % 100 < 20 )
        sub_5B4A50(1, 1, -1, -1);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(
          pDwArg1[2152],
          15,
          1106247680,
          7,
          pDwArg1,
          0);
    }
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATTACH", -1, 0, 0);
    v5 = pDwArg1[2154];
    v6 = pDwArg1[2153] + 1;
    pDwArg1[2153] = v6;
    if ( v6 >= v5 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 724))(pDwArg1[2152]) != 0 )
    {
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 40))(pDwArg1[2152], 529) != 0
        && (uint8_t)sub_5B4A00(pDwArg1[2152]) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pDwArg1[2152] + 732))(pDwArg1[2152], 0, 0, 1);
        pMem = operator new(0x80u);
        pBuf[4] = pMem;
        v28 = 0;
        if ( pMem != nullptr )
        {
          v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);
          v27 = v9 - (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);
          *(float *)&v22 = (float)v27;
          v10 = sub_4D6810(pMem, v22, 500, 1, 1);
        }
        else
        {
          v10 = nullptr;
        }
        v11 = *(uint32_t *)v10;
        v28 = -1;
        (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v11 + 56))(
          v10,
          pDwArg1,
          pDwArg1,
          0,
          0,
          0,
          -1);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1056964608);
        sub_4AED60(v23);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);
        *((uint8_t *)pDwArg1 + 8632) = 1;
      }
      if ( pDwArg1[2153] < pDwArg1[2155] )
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 772))(pDwArg1[2152], 5) != 0
          && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
        }
      }
      else if ( __RTDynamicCast(
                  (int)pDwArg1,
                  0,
                  &CNStarFish `RTTI Type Descriptor',
                  &CNStarFishDevourer `RTTI Type Descriptor',
                  0) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(
          pDwArg1[2152],
          11,
          1120403456,
          1,
          pDwArg1,
          0);
      }
      else if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 6 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)pDwArg1[2152] + 760))(
          pDwArg1[2152],
          5,
          1120403456,
          5,
          pDwArg1,
          0);
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 15, 0, 0, 0);
    }
    else
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      sub_4926A0(v7);
    }
  }
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 604))(pDwArg1[2152], 0);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 1, 1);
  pObj2 = pDwArg1[2152];
  v13 = *(uint32_t *)pObj2;
  pObj3 = pObj2;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);
  v16 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v15);
  v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 120))(pObj3, v16 - 1);
  (*(void (/*thiscall*/ **)(int, int))(v13 + 112))(pDwArg1[2152], v17);
  v18 = *(uint32_t *)pDwArg1[2152];
  v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
  v20 = sub_432E50(v19);
  return (*(int (/*thiscall*/ **)(int, int))(v18 + 148))(pDwArg1[2152], v20);
}



// ------------------------------------------------------------
// 0x5B5B90 sub_5B5B90
// ------------------------------------------------------------
// 证: "ZGM_ATTACK" | "HOLD"
// 调: sub_5B5B90 sub_45EBE0 sub_5B4ED0 sub_41A5E0 sub_495890
int /*thiscall*/ sub_5B5B90(int *this, float fArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2152; // ecx
  int v6; // eax
  int fld_e21522; // ecx
  int v8; // eax
  int fld_e21523; // ecx
  bool pThis_6DD; // zf
  uint32_t *fld_e1554; // eax
  uint32_t *fld_e28; // edi
  int pThis_6DD2; // eax
  int v14; // edx
  int fld_e2155; // eax
  int fld_e139; // eax
  float v18; // [esp+Ch] [ebp-8h] BYREF
  float v19; // [esp+10h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(LODWORD(fArg2) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg2) + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2152) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2152) = 0;
  }
  fld_e2152 = *(this + 2152);
  if ( fld_e2152 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);
    fld_e21522 = *(this + 2152);
    *(this + 2160) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522);
    fld_e21523 = *(this + 2152);
    *(this + 2161) = v8;
    *(this + 2162) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);
    sub_5B4ED0(&v18, &v19, &fArg2);
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(
      this,
      (uint64_t)v18 >> 32,
      (uint64_t)v18,
      (uint64_t)v19,
      (uint64_t)fArg2);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 848))(*(this + 2152), 1);
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int *))(*(uint32_t *)*(this + 2152) + 768))(*(this + 2152), 5, 40, this);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ZGM_ATTACK", -1, 0, 0);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
  }
  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) == 6;
  fld_e1554 = (uint32_t *)*(this + 1554);
  if ( pThis_6DD )
    fld_e1554 += 6;
  (*(void (/*stdcall*/ **)(uint32_t))(*this + 196))(*fld_e1554);
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));
  v14 = *this;
  pThis_6DD = pThis_6DD2 == 6;
  fld_e2155 = *(this + 2155);
  if ( pThis_6DD )
  {
    *(this + 2154) = 3 * fld_e2155;
    fld_e139 = *(this + 139) + 304;
  }
  else
  {
    *(this + 2154) = fld_e2155;
    fld_e139 = *(this + 139);
  }
  (*(void (/*stdcall*/ **)(int))(v14 + 344))(fld_e139);
  *(this + 2153) = 0;
  *(this + 2156) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5B5F90 sub_5B5F90
// ------------------------------------------------------------
// 调: sub_5B5F90
char /*thiscall*/ sub_5B5F90(uint32_t *this)
{
  int v2; // eax
  int fld_e1905; // esi
  char result; // al

  v2 = *this;
  *(this + 2164) = 0;
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 1152))(0);
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1040))(this) + 8) = 1;
  *(uint8_t *)*(this + 1905) = *(uint8_t *)*(this + 1905) == 0;
  *(uint8_t *)(*(this + 1905) + 32) = *(uint8_t *)(*(this + 1905) + 32) == 0;
  *(uint8_t *)(*(this + 1905) + 64) = *(uint8_t *)(*(this + 1905) + 64) == 0;
  fld_e1905 = *(this + 1905);
  result = *(uint8_t *)(fld_e1905 + 96);
  *(uint8_t *)(fld_e1905 + 96) = result == 0;
  return result;
}



// ------------------------------------------------------------
// 0x5B6150 sub_5B6150
// ------------------------------------------------------------
// 调: sub_5B6150
int /*thiscall*/ sub_5B6150(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg3;
  if ( nArg3 == 2 )
    result = nArg2;
  if ( result == 0 )
  {
    result = *(this + 1905);
    *(float *)(result + 4) = *(float *)(result + 4) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5B6270 sub_5B6270
// ------------------------------------------------------------
// 调: sub_5B6270 sub_495250 sub_41A5E0 sub_5B51D0
char /*thiscall*/ sub_5B6270(int this, unsigned int uArg2, int nArg3, int nArg4)
{
  int pThis_348; // eax
  uint32_t *fld_1848; // edi

  LOBYTE(pThis_348) = sub_495250((uint8_t *)this, uArg2, nArg3, nArg4);
  if ( uArg2 != 2 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_348 == 8 )
    {
      pThis_348 = sub_41A5E0(this + 7028);
      if ( pThis_348 == 5 )
      {
        fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 20);
        pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
        if ( pThis_348 == *fld_1848 )
          LOBYTE(pThis_348) = sub_5B51D0(this);
      }
    }
  }
  return pThis_348;
}



// ------------------------------------------------------------
// 0x5B7BE0 sub_5B7BE0
// ------------------------------------------------------------
// 调: sub_5B7BE0 sub_4D8F90 sub_699000 sub_42B420 sub_491690
int /*thiscall*/ sub_5B7BE0(int this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int pThis_21A0; // eax
  uint8_t v8; // al
  int pThis_21A02; // eax
  uint8_t v10; // al

  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(uint8_t *)(this + 8607) != 0 && *(uint32_t *)(this + 120) != 0 )
    {
      pThis_21A0 = sub_699000(this + 8608);  // 【clock_now(clk)】
      v8 = sub_42B420(50, 150, pThis_21A0, 500);
      sub_491690(1, 2, 1, -16776961, (v8 << 24) | 0xFFFFFF, 1);
    }
    if ( *(int *)(this + 8668) > 0 )
    {
      pThis_21A02 = sub_699000(this + 8608);  // 【clock_now(clk)】
      v10 = sub_42B420(50, 150, pThis_21A02, 500);
      sub_491690(1, 2, 1, -65536, (v10 << 24) | 0xFFFFFF, 1);
    }
    return sub_4D8F90(0, nArg3, nArg4, nArg5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BBE40 sub_5BBE40
// ------------------------------------------------------------
// 调: sub_5BBE40 sub_41A5E0 sub_699000
int /*thiscall*/ sub_5BBE40(int *this)
{
  int fld_e2153; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // edi
  float v9; // eax
  int result; // eax
  int v11; // [esp+Ch] [ebp-Ch]
  float v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]

  fld_e2153 = *(this + 2153);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= fld_e2153 && *((uint8_t *)this + 8608) == 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, fld_e2153);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);
    v6 = *this;
    *((uint8_t *)this + 8608) = 1;
    v7 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 672))(this, 3);
    v13 = sub_41A5E0(v7 + 816);
    v12 = COERCE_FLOAT(sub_41A5E0(v7 + 830));
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v11 = sub_41A5E0(v8 + 816);
    v9 = COERCE_FLOAT(sub_41A5E0(v8 + 830));
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      (uint64_t)((double)v11 * v9) >> 32,
      0,
      (uint64_t)((double)v11 * v9),
      (uint64_t)((double)v13 * v12),
      0,
      0,
      0);
  }
  result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
  if ( result > 1000 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5BDF70 sub_5BDF70
// ------------------------------------------------------------
// 调: sub_5BDF70 sub_5BDF10
int /*stdcall*/ sub_5BDF70(int nArg1)
{
  return sub_5BDF10(nArg1);
}



// ------------------------------------------------------------
// 0x5C4CA0 sub_5C4CA0
// ------------------------------------------------------------
// 证: "HOLD"
// 调: sub_5C4CA0 sub_45EBE0 sub_424A40
int /*thiscall*/ sub_5C4CA0(int *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2155; // ecx
  int v6; // eax
  int fld_e21552; // ecx
  int v8; // eax
  int fld_e21553; // ecx
  int v10; // eax
  int fld_e21554; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int result; // eax
  int fld_e2158; // eax
  int v18; // edx
  int fld_e21555; // edi
  unsigned int v20; // eax
  int v21; // eax
  unsigned int v22; // [esp-4h] [ebp-10h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
  {
    *(this + 2155) = pObj;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 50 )
      *(this + 2155) = 0;
    *(this + 2154) = *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 8);
  }
  else
  {
    *(this + 2155) = 0;
  }
  fld_e2155 = *(this + 2155);
  if ( fld_e2155 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 120))(fld_e2155);
    fld_e21552 = *(this + 2155);
    *(this + 2164) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21552 + 124))(fld_e21552);
    fld_e21553 = *(this + 2155);
    *(this + 2165) = v8;
    *(this + 2166) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21553 + 128))(fld_e21553);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    fld_e21554 = *(uint32_t *)*(this + 2155);
    v12 = v10 != 1 ? -350 : 350;
    v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 - 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e21554 + 112))(*(this + 2155), v12 + v14);
    if ( *(this + 2154) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2155) + 848))(*(this + 2155), 1);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v15 = *this;
  *(this + 2156) = 0;
  *(this + 2159) = 0;
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v15 + 212))(this, "HOLD", -1, 0, 0);
  result = *(this + 2154);
  if ( result == 1 )
  {
    fld_e2158 = *(this + 2158);
    if ( *(this + 1908) != 2 )
      fld_e2158 /= 2;
    v18 = *this;
    *(this + 2157) = fld_e2158;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v18 + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  }
  else if ( result == 2 )
  {
    if ( *(this + 1908) == 2 )
    {
      *(this + 2157) = 1;
    }
    else
    {
      fld_e21555 = *(this + 2155);
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
      if ( fld_e21555 != 0 )
      {
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21555 + 52))(fld_e21555) + v20;
        srand(v22);
      }
      else
      {
        srand(v20);
      }
      *(this + 2157) = rand() % 3 + 1;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 20));
    (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);
    result = *(this + 2155);
    if ( result == dword_8F7C04 )
    {
      v21 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
      return sub_424A40(*(uint32_t **)(v21 + 132), 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5130 sub_5C5130
// ------------------------------------------------------------
// 调: sub_5C5130 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5130(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      *(this + 1894) = 1;
      if ( nArg2 == 0 )
        *(this + 1899) = 50;
    }
  }
  else
  {
    fld_e1905 = *(this + 1905) + 32;
    *(this + 1895) = 1;
    *(this + 1899) = 50;
    *(float *)(fld_e1905 + 4) = *(float *)(fld_e1905 + 4) * 0.5;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;
    sub_41A590(v6, v7, v8);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C53F0 sub_5C53F0
// ------------------------------------------------------------
// 调: sub_5C53F0
int /*thiscall*/ sub_5C53F0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg3;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      *(this + 1891) = 1;
      if ( nArg2 == 0 )
        *(this + 1899) = -50;
    }
  }
  else
  {
    *(this + 1891) = 1;
    *(this + 1899) = -50;
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C5570 sub_5C5570
// ------------------------------------------------------------
// 调: sub_5C5570 sub_5C5020 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C5570(void *this)
{
  unsigned int pThis_2A0; // esi
  int v3; // edx
  int v5; // [esp+4h] [ebp-4h]

  sub_5C5020();
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 158;
  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 1.0;
  return sub_41A590(pThis_2A0, v3, v5);
}



// ------------------------------------------------------------
// 0x5C6300 sub_5C6300
// ------------------------------------------------------------
// 调: sub_5C6300
bool /*thiscall*/ sub_5C6300(void *this, void *pArg2)
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 600;
}



// ------------------------------------------------------------
// 0x5C6470 sub_5C6470
// ------------------------------------------------------------
// 调: sub_5C6470 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C6470(void *this, char pszArg2)
{
  unsigned int pThis_2A0; // edi
  int v4; // edx
  unsigned int pThis_2A02; // esi
  int v6; // edx
  int v8; // edx
  int v9; // [esp+10h] [ebp+8h]
  int v10; // [esp+10h] [ebp+8h]
  int v11; // [esp+10h] [ebp+8h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1054;
  if ( pszArg2 != 0 )
  {
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.07;
    sub_41A590(pThis_2A0, v4, v9);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1110;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 0.07;
  }
  else
  {
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.07;
    sub_41A590(pThis_2A0, v8, v11);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 1110;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) - 0.07;
  }
  return sub_41A590(pThis_2A02, v6, v10);
}



// ------------------------------------------------------------
// 0x5C65A0 sub_5C65A0
// ------------------------------------------------------------
// 调: sub_5C65A0
bool /*thiscall*/ sub_5C65A0(void *this, void *pArg2)
{
  return pArg2 != this && *(uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pArg2 + 340))(pArg2) == 602;
}



// ------------------------------------------------------------
// 0x5C66B0 sub_5C66B0
// ------------------------------------------------------------
// 调: sub_5C66B0 sub_4DC390
int /*stdcall*/ sub_5C66B0(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
      return 0;
    }
    else
    {
      return v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5C67E0 sub_5C67E0
// ------------------------------------------------------------
// 调: sub_5C67E0 sub_41A5E0 sub_41A590
int /*thiscall*/ sub_5C67E0(float *this, char pszArg2)
{
  unsigned int pThis_2A0; // edi
  int v4; // eax
  int v5; // edx
  int fld_e2186; // ebx
  unsigned int pThis_2A02; // edi
  int v8; // eax
  int v9; // edx
  unsigned int pThis_2A03; // edi
  int v11; // edx
  int fld_e21862; // ebx
  unsigned int fld_e21863; // edi
  int v14; // eax
  int v15; // edx
  float fld_e2187; // [esp+Ch] [ebp-4h]
  float fld_e21872; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]

  *(this + 2186) = 10.0;
  *(this + 2187) = 20.0;
  pThis_2A0 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 60;
  v4 = sub_41A5E0(pThis_2A0);
  if ( pszArg2 != 0 )
  {
    sub_41A590(pThis_2A0, v5, v4 + 10);
    fld_e2186 = (uint64_t)*(this + 2186);
    pThis_2A02 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 116;
    v8 = sub_41A5E0(pThis_2A02);
    sub_41A590(pThis_2A02, v9, fld_e2186 + v8);
    fld_e2187 = *(this + 2187) * 0.001;
    pThis_2A03 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) + fld_e2187;
  }
  else
  {
    sub_41A590(pThis_2A0, v5, v4 - 10);
    fld_e21862 = (uint64_t)*(this + 2186);
    fld_e21863 = (*(int (/*fastcall*/ **)(float *, uint32_t, uint32_t))(*(uint32_t *)this + 672))(
            this,
            (uint64_t)*(this + 2186) >> 32,
            0)
        + 116;
    v14 = sub_41A5E0(fld_e21863);
    sub_41A590(fld_e21863, v15, v14 - fld_e21862);
    fld_e21872 = *(this + 2187) * 0.001;
    pThis_2A03 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) - fld_e21872;
  }
  sub_41A590(pThis_2A03, v11, v19);
  return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
}



// ------------------------------------------------------------
// 0x5C6A50 sub_5C6A50
// ------------------------------------------------------------
// 调: sub_5C6A50
int /*thiscall*/ sub_5C6A50(int *this, char pszArg2)
{
  int fld_e2; // ebx
  int v3; // ecx
  int result; // eax

  *(uint8_t *)(*(this + 1) + *(this + 2)) = pszArg2;
  fld_e2 = *(this + 2) + 1;
  *(this + 2) = fld_e2;
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )
    return off_77F3FC(aCriticalError_40, v3);
  return result;
}



// ------------------------------------------------------------
// 0x5C92C0 sub_5C92C0
// ------------------------------------------------------------
// 调: sub_5C92C0 sub_498F00
int /*stdcall*/ sub_5C92C0(int nArg1)
{
  return sub_498F00(0);
}



// ------------------------------------------------------------
// 0x5CF720 sub_5CF720
// ------------------------------------------------------------
// 调: sub_5CF720 sub_4DB480
int /*stdcall*/ sub_5CF720(int nArg1, int nArg2, int nArg3)
{
  return sub_4DB480(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x5D2010 sub_5D2010
// ------------------------------------------------------------
// 调: sub_5D2010 sub_5D19C0
int /*stdcall*/ sub_5D2010(char pszArg1, float fArg2, int nArg3, int nArg4)
{
  return sub_5D19C0(pszArg1, fArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x5D7CD0 sub_5D7CD0
// ------------------------------------------------------------
// 调: sub_5D7CD0 sub_5D6E40
int /*thiscall*/ sub_5D7CD0(uint32_t *this)
{
  *this = &CNSandorExpeller::`vftable';
  return sub_5D6E40();
}


