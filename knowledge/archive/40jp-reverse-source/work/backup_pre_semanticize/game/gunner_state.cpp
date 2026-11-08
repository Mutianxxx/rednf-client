// ============================================================
// 【40JP逆向源代码工程】src/game/gunner_state.cpp
// 模块: 0x4C0000-0x4D0000
// 来源: work/dump 素材  区块: 0x4C0070-0x4CFEE1 §A 武器状态 TAG 组
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 123
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 武器状态 TAG 组
// ============================================================
// 0x4C0070 sub_4C0070
// ------------------------------------------------------------
// 调: sub_4C0070 sub_698F90 sub_4BFFA0
char */*thiscall*/ sub_4C0070(void *this)
{
  sub_698F90((int)this + 4, 0, 0);
  return sub_4BFFA0((int)this + 44, 0x10u);
}



// ------------------------------------------------------------
// 0x4C0090 sub_4C0090
// ------------------------------------------------------------
// 调: sub_4C0090 sub_40C0F0 sub_4BFCB0
uint32_t */*thiscall*/ sub_4C0090(uint32_t *this, int a2)
{
  uint32_t **v3; // ecx
  uint32_t *v4; // esi
  uint32_t *result; // eax
  int v6; // edi
  uint32_t *v7; // edi
  uint32_t *v8; // ecx
  int i; // edx
  int v10; // esi

  v3 = (uint32_t **)*(this + 21);
  v4 = *v3;
  result = *v3;
  if ( *v3 == v3 )
  {
    v6 = a2;
  }
  else
  {
    do
    {
      v6 = a2;
      if ( result[2] == a2 )
        break;
      result = (uint32_t *)*result;
    }
    while ( result != v3 );
  }
  if ( result == v3 )
  {
    if ( v4 != v3 )
    {
      do
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 120))(this, v6, v4[2]) == 1 )
          break;
        v4 = (uint32_t *)*v4;
      }
      while ( v4 != (uint32_t *)*(this + 21) );
    }
    v7 = sub_40C0F0((int)v4, v4[1], &a2);
    sub_4BFCB0(this + 20, 1u);
    v4[1] = v7;
    *(uint32_t *)v7[1] = v7;
    result = *(uint32_t **)(a2 + 4);
    v8 = *(uint32_t **)(a2 + 8);
    for ( i = 0; result != v8; i += v10 )
    {
      v10 = result[5] + 2 * result[4];
      result += 6;
    }
    if ( i > *(this + 15) )
      *(this + 15) = i;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0140 sub_4C0140
// ------------------------------------------------------------
// 调: sub_4C0140 sub_699000
char /*thiscall*/ sub_4C0140(uint32_t *this)
{
  uint32_t *v1; // edi
  int v2; // eax
  uint32_t *v3; // ecx
  uint32_t *v4; // edx
  int v5; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edx
  uint32_t *v8; // edi
  int v9; // esi
  int j; // eax
  int *k; // eax
  int *v12; // ebx
  int v13; // esi
  char v14; // al
  uint32_t *v15; // edx
  uint32_t *v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // esi
  int v23; // ecx
  int *v24; // ecx
  uint32_t Block[3]; // [esp+Ch] [ebp-18h] BYREF
  char v27; // [esp+18h] [ebp-Ch]
  char v28; // [esp+19h] [ebp-Bh]
  uint32_t *v29; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  v1 = this;
  v29 = this;
  v2 = sub_699000((int)(this + 1));
  v3 = (uint32_t *)v1[12];
  v4 = (uint32_t *)v1[13];
  v5 = v2;
  v6 = v3;
  for ( i = v5; v6 != v4; v6 += 4 )
  {
    if ( *((uint8_t *)v6 + 12) != 0 )
      break;
    if ( v6[1] + v1[15] >= v5 )
      break;
  }
  if ( v6 != v3 )
  {
    v7 = (uint32_t *)v1[13];
    if ( v6 != v7 )
    {
      do
      {
        v8 = v3;
        *v3 = *v6;
        v3[1] = v6[1];
        v3[2] = v6[2];
        v9 = v6[3];
        v6 += 4;
        v3 += 4;
        v8[3] = v9;
      }
      while ( v6 != v7 );
      v1 = v29;
      v5 = i;
    }
    v1[13] = v3;
  }
  for ( j = v1[12]; j != v1[13]; j += 16 )
  {
    if ( *(uint8_t *)(j + 13) != 0 )
      *(uint8_t *)(j + 13) = 0;
    if ( *(uint8_t *)(j + 12) != 0 )
      *(uint32_t *)(j + 8) = v5 - *(uint32_t *)(j + 4);
  }
  k = (int *)v1[9];
  v12 = (int *)*k;
  if ( (int *)*k != k )
  {
    do
    {
      v13 = v12[3];
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, int *))(*v1 + 48))(v1, v12 + 4);
      if ( v14 == 0 && *((uint8_t *)v1 + 66) != 0 )
      {
        v15 = (uint32_t *)v1[18];
        v16 = (uint32_t *)*v15;
        if ( (uint32_t *)*v15 != v15 )
        {
          do
          {
            if ( v16[2] == v13 )
              break;
            v16 = (uint32_t *)*v16;
          }
          while ( v16 != v15 );
          if ( v16 != v15 )
            v14 = 1;
        }
      }
      v17 = v1[12];
      if ( v17 != 0 )
        v18 = (v1[13] - v17) >> 4;
      else
        v18 = 0;
      v19 = v18 - 1;
      if ( v19 >= 0 )
      {
        v20 = v1[12] + 16 * v19;
        do
        {
          if ( *(uint32_t *)v20 == v13 && *(uint8_t *)(v20 + 12) != 0 )
            break;
          --v19;
          v20 -= 16;
        }
        while ( v19 >= 0 );
      }
      if ( v14 != 0 )
      {
        if ( v19 == -1 )
        {
          Block[1] = i;
          v21 = v1[12];
          Block[2] = 0;
          Block[0] = v13;
          v27 = 1;
          v28 = 1;
          if ( v21 != 0 && (v1[13] - v21) >> 4 < (unsigned int)((v1[14] - v21) >> 4) )
          {
            v22 = v1[13];
            sub_4BF340(v22, 1, Block);
            v1[13] = v22 + 16;
          }
          else
          {
            sub_4BFD40(v1[13], 1, Block);
          }
        }
      }
      else if ( v19 != -1 )
      {
        v23 = 16 * v19;
        *(uint8_t *)(v23 + v1[12] + 12) = 0;
        *(uint8_t *)(v23 + v1[12] + 13) = 1;
      }
      LOBYTE(k) = *((uint8_t *)v12 + 25);
      if ( (uint8_t)k == 0 )
      {
        v24 = (int *)v12[2];
        if ( *((uint8_t *)v24 + 25) != 0 )
        {
          for ( k = (int *)v12[1]; *((uint8_t *)k + 25) == 0; k = (int *)k[1] )
          {
            if ( v12 != (int *)k[2] )
              break;
            v12 = k;
          }
          v12 = k;
        }
        else
        {
          k = (int *)*v24;
          if ( *(uint8_t *)(*v24 + 25) == 0 )
          {
            do
            {
              v24 = k;
              k = (int *)*k;
            }
            while ( *((uint8_t *)k + 25) == 0 );
          }
          v12 = v24;
        }
      }
    }
    while ( v12 != (int *)v1[9] );
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x4C0360 sub_4C0360
// ------------------------------------------------------------
// 调: sub_4C0360 sub_41A5E0
double /*thiscall*/ sub_4C0360(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 524));
}



// ------------------------------------------------------------
// 0x4C0390 sub_4C0390
// ------------------------------------------------------------
// 调: sub_4C0390 sub_699000
int /*thiscall*/ sub_4C0390(uint32_t *this)
{
  return *(this + 2185) + *(this + 1664) * sub_699000((int)(this + 1640)) / 1000;
}



// ------------------------------------------------------------
// 0x4C03D0 sub_4C03D0
// ------------------------------------------------------------
// 调: sub_4C03D0 sub_699000
int /*thiscall*/ sub_4C03D0(uint32_t *this)
{
  return *(this + 1664) * sub_699000((int)(this + 1640)) / 1000;
}



// ------------------------------------------------------------
// 0x4C0400 sub_4C0400
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C0400
char /*cdecl*/ sub_4C0400(int a1)
{
  uint32_t *v1; // eax

  v1 = &unk_6F6CC8;
  while ( a1 != *v1 )
  {
    if ( (int)++v1 >= (int)"LANDRUNNER_OUT" )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4C0430 sub_4C0430
// ------------------------------------------------------------
// 调: sub_4C0430 sub_41A590
int /*fastcall*/ sub_4C0430(int a1, int a2)
{
  int v3; // edx

  *(uint32_t *)(a1 + 8216) = 0;
  *(uint32_t *)(a1 + 8516) = -1;
  *(uint32_t *)(a1 + 8532) = 0;
  *(uint32_t *)(a1 + 8536) = -1;
  *(uint32_t *)(a1 + 8540) = -1;
  sub_41A590(a1 + 8544, a2, 0);
  *(uint32_t *)(a1 + 8560) = -1;
  *(uint32_t *)(a1 + 8564) = 0;
  *(uint32_t *)(a1 + 8568) = 0;
  *(uint32_t *)(a1 + 8572) = 0;
  *(uint8_t *)(a1 + 8576) = 0;
  sub_41A590(a1 + 8577, v3, 0);
  *(uint32_t *)(a1 + 8592) = 0;
  *(uint8_t *)(a1 + 8596) = 0;
  *(uint8_t *)(a1 + 8597) = 0;
  *(uint32_t *)(a1 + 8600) = 0;
  *(uint32_t *)(a1 + 8604) = 0;
  *(uint32_t *)(a1 + 8648) = -1;
  *(uint32_t *)(a1 + 8664) = -1;
  *(uint8_t *)(a1 + 8608) = 0;
  *(uint32_t *)(a1 + 8612) = 0;
  *(uint32_t *)(a1 + 8616) = 0;
  *(uint32_t *)(a1 + 8620) = 0;
  *(uint32_t *)(a1 + 8624) = 0;
  *(uint32_t *)(a1 + 8628) = 0;
  *(uint32_t *)(a1 + 8632) = 0;
  *(uint32_t *)(a1 + 8636) = 0;
  *(uint32_t *)(a1 + 8640) = 0;
  *(uint32_t *)(a1 + 8644) = 0;
  *(uint32_t *)(a1 + 8652) = 0;
  *(uint32_t *)(a1 + 8656) = 0;
  *(uint32_t *)(a1 + 8660) = 0;
  *(uint32_t *)(a1 + 8668) = 0;
  *(uint32_t *)(a1 + 8672) = 0;
  *(uint8_t *)(a1 + 8676) = 0;
  *(uint32_t *)(a1 + 8680) = 0;
  *(uint32_t *)(a1 + 8684) = 0;
  *(uint32_t *)(a1 + 8688) = -1;
  *(uint8_t *)(a1 + 8692) = 0;
  *(uint8_t *)(a1 + 8693) = 0;
  *(uint8_t *)(a1 + 8694) = 0;
  *(uint32_t *)(a1 + 8696) = 0;
  *(uint32_t *)(a1 + 8700) = 0;
  *(uint32_t *)(a1 + 8704) = 0;
  *(uint32_t *)(a1 + 8708) = 0;
  *(uint32_t *)(a1 + 8712) = 0;
  *(uint32_t *)(a1 + 8716) = 0;
  *(uint32_t *)(a1 + 8720) = 0;
  *(uint32_t *)(a1 + 8724) = 0;
  *(uint32_t *)(a1 + 8732) = -1;
  *(uint8_t *)(a1 + 8728) = 0;
  *(uint32_t *)(a1 + 8736) = 0;
  *(uint32_t *)(a1 + 8740) = 0;
  *(uint32_t *)(a1 + 8744) = 0;
  *(uint32_t *)(a1 + 8748) = 0;
  *(uint32_t *)(a1 + 8752) = 0;
  *(uint32_t *)(a1 + 8756) = 0;
  memset((void *)(a1 + 8760), 0, 0xC8u);
  *(uint32_t *)(a1 + 8964) = 100;
  *(uint8_t *)(a1 + 8960) = 0;
  *(uint32_t *)(a1 + 8968) = 0;
  memset((void *)(a1 + 8972), 0, 0x140u);
  *(uint32_t *)(a1 + 9292) = 0;
  *(uint32_t *)(a1 + 9296) = 0;
  *(uint8_t *)(a1 + 9300) = 0;
  *(uint8_t *)(a1 + 9301) = 0;
  *(uint32_t *)(a1 + 9304) = 0;
  *(uint32_t *)(a1 + 9308) = 0;
  *(uint32_t *)(a1 + 9312) = 0;
  *(uint32_t *)(a1 + 9316) = 0;
  *(uint32_t *)(a1 + 9320) = 0;
  *(uint32_t *)(a1 + 9324) = 0;
  *(uint32_t *)(a1 + 9328) = 0;
  *(uint32_t *)(a1 + 9332) = 0;
  *(uint32_t *)(a1 + 9336) = 0;
  *(uint32_t *)(a1 + 9340) = 0;
  *(uint32_t *)(a1 + 9344) = 0;
  *(uint32_t *)(a1 + 9348) = 0;
  *(uint32_t *)(a1 + 9352) = 0;
  *(uint32_t *)(a1 + 9356) = 0;
  *(uint32_t *)(a1 + 9360) = 0;
  *(uint32_t *)(a1 + 9364) = 0;
  *(uint8_t *)(a1 + 9368) = 0;
  *(uint32_t *)(a1 + 9372) = 0;
  *(uint32_t *)(a1 + 9376) = 0;
  *(uint32_t *)(a1 + 9396) = 0;
  *(uint32_t *)(a1 + 9380) = 0;
  *(uint32_t *)(a1 + 9388) = 0;
  *(uint32_t *)(a1 + 9400) = 0;
  *(uint32_t *)(a1 + 9408) = 0;
  *(uint32_t *)(a1 + 9384) = 0;
  *(uint32_t *)(a1 + 9392) = 0;
  *(uint32_t *)(a1 + 9404) = 0;
  *(uint32_t *)(a1 + 9412) = 0;
  *(uint8_t *)(a1 + 9416) = 0;
  *(uint32_t *)(a1 + 9420) = 0;
  *(uint32_t *)(a1 + 9424) = 0;
  *(uint8_t *)(a1 + 9428) = 0;
  *(uint32_t *)(a1 + 9432) = 0;
  *(uint32_t *)(a1 + 9440) = 0;
  *(uint32_t *)(a1 + 9444) = 0;
  *(uint32_t *)(a1 + 9452) = 0;
  *(uint32_t *)(a1 + 9456) = 0;
  *(uint32_t *)(a1 + 9460) = 0;
  *(uint32_t *)(a1 + 9464) = 0;
  *(uint32_t *)(a1 + 9476) = 0;
  *(uint32_t *)(a1 + 9472) = 0;
  *(uint8_t *)(a1 + 9500) = 0;
  *(uint32_t *)(a1 + 9516) = 0;
  *(uint32_t *)(a1 + 9436) = 4;
  *(uint32_t *)(a1 + 9448) = -1;
  *(uint32_t *)(a1 + 9468) = 1;
  *(uint32_t *)(a1 + 9480) = 0xFFFF;
  *(uint32_t *)(a1 + 9484) = -1;
  return -1;
}


// ------------------------------------------------------------
// 0x4C0730 sub_4C0730
// ------------------------------------------------------------
// 调: sub_4C0730 sub_4AFC30
int /*thiscall*/ sub_4C0730(uint32_t *this, int a2, int a3, int a4)
{
  *((uint8_t *)this + 8960) = 0;
  *(this + 2241) = 100;
  *((uint8_t *)this + 8597) = 0;
  return sub_4AFC30(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x4C0760 sub_4C0760
// ------------------------------------------------------------
// 调: sub_4C0760 sub_4AFBF0
int /*thiscall*/ sub_4C0760(int this, int *a2, int a3)
{
  int result; // eax
  int v5; // eax
  int v6; // esi

  result = sub_4AFBF0((uint8_t *)this, a2, a3);
  if ( result != 3 )
  {
    if ( *(uint8_t *)(this + 8960) != 0 )
    {
      v5 = *a2;
      v6 = *(uint32_t *)(this + 8964);
      if ( *a2 >= v6 )
        v5 = v6;
      *a2 = v5;
      return 2;
    }
    else if ( *(uint8_t *)(this + 8597) != 0 )
    {
      return 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C07C0 sub_4C07C0
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C07C0 sub_4AFDB0 sub_432E50
uint8_t */*thiscall*/ sub_4C07C0(uint8_t **this, int a2, int a3)
{
  uint8_t *result; // eax
  uint8_t *v5; // edi
  int v6; // eax
  int v7; // eax

  result = sub_4AFDB0(this, a2, a3);
  if ( a2 == 32 )
  {
    v5 = *this;
    v6 = (*((int (/*thiscall*/ **)(uint8_t **))*this + 38))(this);
    v7 = sub_432E50(v6);
    return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int))v5 + 36))(this, v7);
  }
  else if ( a2 == 42 )
  {
    return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, const char *, int, uint32_t, uint32_t))*this + 53))(
                      this,
                      "LANDRUNNER_OUT",
                      -1,
                      0,
                      0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0820 sub_4C0820
// ------------------------------------------------------------
// 调: sub_4C0820 sub_4AFD50 sub_47E440
int /*userpurge*/ sub_4C0820@<eax>(uint8_t *a1@<ecx>, char a2@<bl>, char a3)
{
  int result; // eax
  char v5; // bl
  int v6; // eax
  bool v7; // al
  bool v8; // al
  bool v9; // al
  bool v10; // al
  bool v11; // al
  bool v12; // al
  bool v13; // al
  bool v14; // al
  char v16; // [esp-4h] [ebp-8h]
  char v17; // [esp-4h] [ebp-8h]
  char v18; // [esp-4h] [ebp-8h]
  char v19; // [esp-4h] [ebp-8h]
  char v20; // [esp-4h] [ebp-8h]
  char v21; // [esp-4h] [ebp-8h]
  char v22; // [esp-4h] [ebp-8h]
  char v23; // [esp-4h] [ebp-8h]

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
    v6 = sub_4AFD50(a1, a3);
    LOBYTE(v6) = v5 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 16)) > 0;
    (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)a1 + 1160))(a1, 12, v6);
    sub_47E440(a2);
    v7 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 17) > 0;
    v16 = v7;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 13);
    sub_47E440(v16);
    v8 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 17) > 0;
    v17 = v8;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 36);
    sub_47E440(v17);
    v9 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 18) > 0;
    v18 = v9;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 7);
    sub_47E440(v18);
    v10 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 19) > 0;
    v19 = v10;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 6);
    sub_47E440(v19);
    v11 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 24) > 0;
    v20 = v11;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 20);
    sub_47E440(v20);
    v12 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 24) > 0;
    v21 = v12;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 5);
    sub_47E440(v21);
    v13 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 25) > 0;
    v22 = v13;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 14);
    sub_47E440(v22);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 39);
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 1160))(a1);
    sub_47E440(39);
    v14 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 40) > 0;
    v23 = v14;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 40);
    return sub_47E440(v23);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0A30 sub_4C0A30
// ------------------------------------------------------------
// 调: sub_4C0A30 sub_4AFEC0 sub_47E440
char /*thiscall*/ sub_4C0A30(int this)
{
  int v2; // eax

  LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)v2 != 0 )
  {
    sub_4AFEC0((uint32_t *)this);
    LOBYTE(v2) = *(uint8_t *)(this + 7730);
    if ( (uint8_t)v2 != 0 )
    {
      v2 = *(uint32_t *)(this + 6556);
      switch ( v2 )
      {
        case 0:
        case 11:
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 1);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 4);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 5);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 6);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 7);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 9);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 12);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 13);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 15);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 20);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 30);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 27);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 28);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 29);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 33);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 36);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 37);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 39);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 40);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 43);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 45);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 46);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 47);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 48);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 50);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 51);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 53);
          LOBYTE(v2) = sub_47E440(1);
          break;
        case 7:
        case 20:
          goto LABEL_7;
        case 22:
          if ( *(uint32_t *)(this + 8516) == 12 && *(uint32_t *)(this + 8968) == 1 )
LABEL_7:
            byte_9A0358 = 1;
          break;
        case 23:
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 15);
          sub_47E440(1);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 32);
          LOBYTE(v2) = sub_47E440(1);
          break;
        default:
          return v2;
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4C0D90 sub_4C0D90
// ------------------------------------------------------------
// 调: sub_4C0D90 sub_4B0530
int /*thiscall*/ sub_4C0D90(uint32_t *this, uint32_t *a2)
{
  int result; // eax

  sub_4B0530(this, a2);
  result = 0;
  if ( (uint32_t *)*(this + 2175) == a2 )
    *(this + 2175) = 0;
  if ( (uint32_t *)*(this + 2336) == a2 )
    *(this + 2336) = 0;
  if ( a2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0DF0 sub_4C0DF0
// ------------------------------------------------------------
// 调: sub_4C0DF0 sub_41A5E0 sub_47EF20
uint64_t /*thiscall*/ sub_4C0DF0(void *this, int a2)
{
  int v4; // eax
  int v6; // [esp-Ch] [ebp-1Ch]
  int v7; // [esp+8h] [ebp-8h]
  float v8; // [esp+18h] [ebp+8h]

  v7 = sub_41A5E0((unsigned int)this + 14 * a2 + 8460);
  v4 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v8 = 1.0 - (COERCE_FLOAT(sub_41A5E0(v4 + 1292)) - 1.0);
  if ( a2 == 1
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) == 0
    && (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 22) > 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 22, -1);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);
    v8 = v8 - (double)(int)sub_47EF20(22, 0, v6, -1, 11) * 0.0099999998;
  }
  return (uint64_t)((double)v7 * v8);
}



// ------------------------------------------------------------
// 0x4C0EB0 sub_4C0EB0
// ------------------------------------------------------------
// 调: sub_4C0EB0 sub_41A5E0 sub_47EF20
uint64_t /*thiscall*/ sub_4C0EB0(void *this)
{
  int v2; // eax
  int v4; // [esp-Ch] [ebp-1Ch]
  int v5; // [esp+4h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-4h]

  v5 = sub_41A5E0((unsigned int)this + 8488);
  v2 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v6 = COERCE_FLOAT(sub_41A5E0(v2 + 1292)) - 1.0 + 1.0;
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) != 0
    || (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 23) <= 0 )
  {
    return (uint64_t)((double)v5 * v6);
  }
  v4 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 23, -1);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);
  return (uint64_t)((double)v5 * ((double)(int)sub_47EF20(23, 0, v4, -1, 11) * 0.0099999998 + v6));
}



// ------------------------------------------------------------
// 0x4C0F70 sub_4C0F70
// ------------------------------------------------------------
// 调: sub_4C0F70
char /*thiscall*/ sub_4C0F70(uint32_t *this, int a2)
{
  char result; // al

  if ( a2 != 8 )
    return 1;
  switch ( *(this + 1639) )
  {
    case 7:
    case 8:
    case 0x12:
    case 0x14:
    case 0x17:
    case 0x1B:
      result = 0;
      break;
    default:
      return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C0FD0 sub_4C0FD0
// ------------------------------------------------------------
// 调: sub_4C0FD0
int /*thiscall*/ sub_4C0FD0(uint32_t *this)
{
  int v2; // eax

  v2 = *(this + 2156);
  if ( v2 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v2 + 80))() != 0 )
    return *(this + 2157);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4C1000 sub_4C1000
// ------------------------------------------------------------
// 调: sub_4C1000 sub_41A5E0
int /*thiscall*/ sub_4C1000(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int result; // eax
  bool v6; // zf

  v2 = *(this + 2164);
  if ( v2 == 0
    || (*(uint8_t (**)(void))(*(uint32_t *)v2 + 80))() == 0
    || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 140))(*(this + 2164)) <= 0 )
  {
    return 4;
  }
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2164) + 128))(*(this + 2164));
  v4 = sub_41A5E0(v3 + 4);
  if ( v4 == 1 )
    return 0;
  if ( v4 == 2 )
    return 1;
  v6 = v4 == 30;
  result = 3;
  if ( !v6 )
    return 4;
  return result;
}



// ------------------------------------------------------------
// 0x4C1070 sub_4C1070
// ------------------------------------------------------------
// 调: sub_4C1070
bool /*thiscall*/ sub_4C1070(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 314);
  return v1 != 0 && (*(this + 315) - v1) >> 2 != 0;
}



// ------------------------------------------------------------
// 0x4C10A0 sub_4C10A0
// ------------------------------------------------------------
// 调: sub_4C10A0 sub_4B1030 sub_650D20 sub_5F9160
uint8_t */*thiscall*/ sub_4C10A0(uint8_t *this)
{
  sub_4B1030(this);
  *(uint32_t *)this = &CNBulletBuff::`vftable';
  sub_650D20(this);
  sub_5F9160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4C10F0 sub_4C10F0
// ------------------------------------------------------------
// 调: sub_4C10F0
int /*thiscall*/ sub_4C10F0(uint32_t *this, int a2, int a3)
{
  *(this + 20) = a2;
  *(this + 21) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x4C1110 sub_4C1110
// ------------------------------------------------------------
// 调: sub_4C1110
int /*thiscall*/ sub_4C1110(uint32_t *this, int a2)
{
  *(this + 22) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4C1120 sub_4C1120
// ------------------------------------------------------------
// 调: sub_4C1120
int /*thiscall*/ sub_4C1120(uint32_t *this)
{
  return *(this + 20);
}



// ------------------------------------------------------------
// 0x4C1130 sub_4C1130
// ------------------------------------------------------------
// 调: sub_4C1130
int /*thiscall*/ sub_4C1130(uint32_t *this)
{
  return *(this + 23);
}



// ------------------------------------------------------------
// 0x4C1140 sub_4C1140
// ------------------------------------------------------------
// 调: sub_4C1140 sub_4C1170
void */*thiscall*/ sub_4C1140(void *Block, char a2)
{
  sub_4C1170();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4C1170 sub_4C1170
// ------------------------------------------------------------
// 调: sub_4C1170 sub_5F6640
int /*thiscall*/ sub_4C1170(uint32_t *this)
{
  int result; // eax

  *this = &CNBulletBuff::`vftable';
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4C11D0 sub_4C11D0
// ------------------------------------------------------------
// 调: sub_4C11D0 sub_4B1030 sub_5F91F0 sub_650D30
uint8_t */*thiscall*/ sub_4C11D0(uint8_t *this, int a2)
{
  sub_4B1030(this);
  *(uint32_t *)this = &CNTrodden::`vftable';
  sub_5F91F0(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x4C1230 sub_4C1230
// ------------------------------------------------------------
// 调: sub_4C1230 sub_4C1260
void */*thiscall*/ sub_4C1230(void *Block, char a2)
{
  sub_4C1260();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4C1260 sub_4C1260
// ------------------------------------------------------------
// 调: sub_4C1260 sub_5F6640
int /*thiscall*/ sub_4C1260(uint32_t *this)
{
  int result; // eax

  *this = &CNTrodden::`vftable';
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4C12C0 sub_4C12C0
// ------------------------------------------------------------
// 调: sub_4C12C0 sub_4B1030 sub_5F9510 sub_650D30
int /*thiscall*/ sub_4C12C0(int this, int a2)
{
  sub_4B1030((uint8_t *)this);
  *(uint32_t *)this = &CNAerialGatlinged::`vftable';
  *(uint8_t *)(this + 112) = 0;
  *(uint32_t *)(this + 108) = &off_6C2B88;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 120) = 1;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 124) = 0;
  sub_5F9510(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x4C1340 sub_4C1340
// ------------------------------------------------------------
// 调: sub_4C1340 sub_698F90
char /*thiscall*/ sub_4C1340(uint8_t *this, int a2, int a3, int a4)
{
  int v4; // ecx

  *(this + 120) = 1;
  v4 = (int)(this + 108);
  *(uint8_t *)(v4 + 13) = 0;
  *(uint8_t *)(v4 + 14) = 0;
  return sub_698F90(v4, 0, 0);
}



// ------------------------------------------------------------
// 0x4C1360 sub_4C1360
// ------------------------------------------------------------
// 调: sub_4C1360 sub_4C1390
void */*thiscall*/ sub_4C1360(void *Block, char a2)
{
  sub_4C1390();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4C1390 sub_4C1390
// ------------------------------------------------------------
// 调: sub_4C1390 sub_5F6640
int /*thiscall*/ sub_4C1390(uint32_t *this)
{
  int result; // eax

  *this = &CNAerialGatlinged::`vftable';
  nullsub_3(this);
  *(this + 27) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 112) = 0;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4C1400 sub_4C1400
// ------------------------------------------------------------
// 调: sub_4C1400
char /*stdcall*/ sub_4C1400(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4C1400(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C1440 sub_4C1440
// ------------------------------------------------------------
// 调: sub_4C1440 sub_6569D0 sub_699000
int /*thiscall*/ sub_4C1440(uint32_t *this)
{
  int result; // eax

  sub_6569D0(this + 2130);
  result = sub_699000((int)(this + 2));
  *(this + 2133) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4C1460 sub_4C1460
// ------------------------------------------------------------
// 调: sub_4C1460 sub_4B2270 sub_47E9D0 sub_4B1BA0 sub_47DCC0
int /*thiscall*/ sub_4C1460(int this)
{
  int result; // eax
  uint32_t *v3; // edi
  unsigned int v4; // ebx
  int *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int *v9; // [esp+4h] [ebp-10h] BYREF
  uint32_t *v10; // [esp+8h] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-8h] BYREF
  int v12; // [esp+10h] [ebp-4h]

  sub_4B2270((uint32_t *)this);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 44);
  if ( result > 0 )
  {
    v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 44);
    result = v3[103];
    v4 = 0;
    v10 = v3;
    if ( result != 0 )
    {
      result = (v3[104] - result) / 14;
      v12 = result;
    }
    else
    {
      v12 = 0;
    }
    if ( v12 > 0 )
    {
      while ( 1 )
      {
        v11 = sub_47E9D0(v3, v4);
        sub_4B1BA0((int **)(this + 7416), &v9, &v11);
        v5 = v9;
        if ( v9 != *(int **)(this + 7420) )
        {
          v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, v11);
          v7 = sub_47DCC0(v6);
          v8 = v5[5];
          if ( v8 < v7 )
            v5[5] = v8 + 1;
        }
        result = v12;
        if ( (int)++v4 >= v12 )
          break;
        v3 = v10;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C1530 sub_4C1530
// ------------------------------------------------------------
// 调: sub_4C1530 sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
signed int /*usercall*/ sub_4C1530@<eax>(int *a1@<ecx>, int a2@<edi>)
{
  signed int result; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // edx
  uint32_t *v11; // ebx
  int v12; // eax
  double v13; // st7
  int v14; // eax
  int v15; // edi
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // edx
  double v19; // st7
  float v20; // [esp+4h] [ebp-14h]
  int v21; // [esp+8h] [ebp-10h]
  uint32_t *v22; // [esp+Ch] [ebp-Ch]
  uint32_t *v23; // [esp+Ch] [ebp-Ch]
  int v24; // [esp+10h] [ebp-8h]
  int v25; // [esp+10h] [ebp-8h]
  unsigned int v26; // [esp+14h] [ebp-4h]
  int v27; // [esp+14h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 1160))(a1, 44, a2);
    v22 = v4;
    if ( sub_41A5E0((unsigned int)v4 + 510) > 0 )
    {
      v5 = v4[103];
      v24 = v5 != 0 ? (v4[104] - v5) / 14 : 0;
      v26 = 0;
      if ( v24 > 0 )
      {
        while ( 1 )
        {
          v6 = *a1;
          v7 = sub_47E9D0(v4, v26);
          v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(a1, v7);
          v9 = sub_41A5E0(v8 + 510);
          if ( v9 > 0 && v9 < sub_47DCC0(v8) )
            sub_41A590(v8 + 510, v10, v9 + 1);
          if ( (int)++v26 >= v24 )
            break;
          v4 = v22;
        }
      }
    }
    v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*a1 + 1160))(a1, 21);
    v23 = v11;
    result = sub_41A5E0((unsigned int)v11 + 510);
    if ( result > 0 )
    {
      v12 = sub_41A5E0((unsigned int)v11 + 510);
      v13 = (double)(int)sub_47EF20(0, v12, -1, -1, 11);
      v14 = v11[103];
      v20 = v13 * 0.0099999998;
      v15 = v14 != 0 ? (v11[104] - v14) / 14 : 0;
      result = 0;
      v27 = 0;
      if ( v15 > 0 )
      {
        while ( 1 )
        {
          v21 = *a1;
          v16 = sub_47E9D0(v11, result);
          v17 = (*(int (/*thiscall*/ **)(int *, int))(v21 + 1160))(a1, v16) + 524;
          v19 = COERCE_FLOAT(sub_41A5E0(v17)) - v20;
          if ( v19 <= 0.0 )
          {
            sub_41A590(v17, v18, 0);
          }
          else
          {
            *(float *)&v25 = v19;
            sub_41A590(v17, v18, v25);
          }
          result = ++v27;
          if ( v27 >= v15 )
            break;
          v11 = v23;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C16F0 sub_4C16F0
// ------------------------------------------------------------
// 调: sub_4C16F0 sub_699000
double /*thiscall*/ sub_4C16F0(int this)
{
  int v2; // edi
  uint32_t ***v3; // ecx
  uint32_t **v4; // eax
  int v5; // eax
  double result; // st7
  int v7; // [esp+8h] [ebp-4h]

  while ( *(uint32_t *)(this + 8528) != 0 )
  {
    v2 = **(uint32_t **)(this + 8524);
    if ( *(uint32_t *)(v2 + 8) >= sub_699000(this + 8) - 1000 )
      break;
    v3 = *(uint32_t ****)(this + 8524);
    v4 = *v3;
    if ( *v3 != v3 )
    {
      *v4[1] = *v4;
      (*v4)[1] = v4[1];
      j__free(v4);
      --*(uint32_t *)(this + 8528);
    }
  }
  v5 = sub_699000(this + 8);
  result = (double)*(int *)(this + 8528);
  v7 = v5 - *(uint32_t *)(this + 8532);
  if ( v7 >= 1000 )
  {
    if ( *(int *)(this + 8528) < 0 )
      return result + 4294967300.0;
  }
  else
  {
    if ( *(int *)(this + 8528) < 0 )
      result = result + 4294967300.0;
    return result * 1000.0 / (double)v7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C17C0 sub_4C17C0
// ------------------------------------------------------------
// 调: sub_4C17C0 sub_41A5E0
int /*thiscall*/ sub_4C17C0(uint32_t *this, uint32_t *a2, uint32_t *a3, uint32_t *a4, int a5, int a6, int a7)
{
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int result; // eax

  v8 = *(this + 1639);
  if ( v8 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      if ( *((uint8_t *)this + 8596) != 0 )
      {
        v9 = a5 + 34;
        v10 = a7 - 5;
      }
      else
      {
        v9 = a5 + 38;
        v10 = a7 - 7;
      }
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  if ( v8 == 7 )
  {
    if ( *(this + 2154) == 1 )
    {
      v9 = a5 + 7;
      v10 = a7 + 7;
      goto LABEL_17;
    }
    goto LABEL_16;
  }
  if ( v8 != 23 )
  {
LABEL_16:
    v10 = a7;
    v9 = a5;
    goto LABEL_17;
  }
  v11 = *(this + 1554);
  v12 = *(this + 30);
  v13 = 0;
  if ( v12 == *(uint32_t *)(v11 + 96) )
  {
    v13 = *(uint32_t *)(v12 + 148) + 1;
  }
  else if ( v12 == *(uint32_t *)(v11 + 100) )
  {
    v13 = 8 - *(uint32_t *)(v12 + 148);
  }
  v9 = dword_6F6C74[v13] + a5;
  v10 = dword_6F6C98[v13] + a7;
  if ( *(this + 2360) == 1 )
  {
    v9 -= 5;
    v10 -= 3;
  }
LABEL_17:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    v14 = v9 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  else
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v9;
  *a2 = v14;
  *a3 = a6 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  result = v10 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  *a4 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4C18E0 sub_4C18E0
// ------------------------------------------------------------
// 调: sub_4C18E0 sub_4C17C0 sub_4B2580
int /*thiscall*/ sub_4C18E0(uint8_t *this, uint32_t *a2, int *a3)
{
  int v5; // edi
  int v6; // edx
  int *v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int *v11; // eax
  int v12; // edx
  int v13; // [esp+4h] [ebp-20h]
  int *v14; // [esp+4h] [ebp-20h]
  int v15; // [esp+8h] [ebp-1Ch]
  int v16; // [esp+8h] [ebp-1Ch]
  int v17; // [esp+Ch] [ebp-18h] BYREF
  int v18; // [esp+10h] [ebp-14h] BYREF
  int v19; // [esp+14h] [ebp-10h] BYREF
  int v20; // [esp+18h] [ebp-Ch] BYREF
  int v21; // [esp+1Ch] [ebp-8h] BYREF
  char v22; // [esp+23h] [ebp-1h]

  if ( *((uint32_t *)this + 2129) == 53 )
    return 1;
  *a2 = 0;
  *a3 = 0;
  v13 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 1132))(this, 0);
  v15 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1132))(this, 1);
  v5 = -1;
  if ( v13 == (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) )
  {
    v5 = 0;
  }
  else if ( v15 == 3 )
  {
    v5 = 1;
  }
  v16 = -1;
  v14 = nullptr;
  v22 = *(this + 8596);
  if ( v5 == 0 || v5 == -1 )
  {
    v19 = 0;
    v20 = 0;
    v21 = 0;
    *(this + 8596) = 0;
    sub_4C17C0(this, &v19, &v20, &v21, 47, 0, 119);
    v6 = *((uint32_t *)this + 2055);
    *(this + 8596) = v22;
    v18 = 0;
    v17 = 0;
    v7 = sub_4B2580(&v18, &v17, (int)this, v19, v20, v21, 0, *(uint32_t *)(v6 + 76), 4, 4, -1, 480, 34, 34, 34);
    if ( v7 != nullptr )
    {
      v14 = v7;
      v8 = (*(int (/*thiscall*/ **)(uint8_t *, int *))(*(uint32_t *)this + 156))(this, v7);
      v9 = v17;
      v16 = v8;
      *a2 = v18;
      *a3 = v9;
    }
  }
  if ( v5 == 1 || v5 == -1 )
  {
    v19 = 0;
    v18 = 0;
    v17 = 0;
    *(this + 8596) = 1;
    sub_4C17C0(this, &v19, &v18, &v17, 47, 0, 119);
    v10 = v16;
    *(this + 8596) = v22;
    v20 = 0;
    v21 = 0;
    if ( v16 != -1 )
      v10 = v16 + 1;
    v11 = sub_4B2580(
            &v20,
            &v21,
            (int)this,
            v19,
            v18,
            v17,
            0,
            *(uint32_t *)(*((uint32_t *)this + 2056) + 76),
            4,
            4,
            v10,
            480,
            34,
            34,
            34);
    if ( v11 != nullptr && (v11 != v14 || (int)abs32(v21) < (int)abs32(*a3)) )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int *))(*(uint32_t *)this + 156))(this, v11);
      v12 = v21;
      *a2 = v20;
      *a3 = v12;
      return 1;
    }
    if ( v5 == -1 )
      return 0;
  }
  return v5;
}



// ------------------------------------------------------------
// 0x4C1AF0 sub_4C1AF0
// ------------------------------------------------------------
// 证: "LANDRUNNER_OUT"
// 调: sub_4C1AF0
int /*thiscall*/ sub_4C1AF0(uint32_t *this)
{
  int v1; // ebx
  unsigned int v3; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  uint32_t *v11; // eax

  v1 = 0;
  v3 = 0;
LABEL_2:
  while ( 1 )
  {
    v4 = *(this + 29);
    v5 = *(uint32_t *)(v4 + 120);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 124) - v5) >> 2 : 0;
    if ( (int)v3 >= v6 )
      return v1;
    v7 = *(uint32_t *)(v4 + 120);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
      v8 = *(uint32_t *)(v7 + 4 * v3);
    else
      v8 = 0;
    v9 = (uint32_t *)__RTDynamicCast(
                     v8,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDMonster `RTTI Type Descriptor',
                     0);
    if ( v9 != nullptr && (uint32_t *)v9[2088] == this )
    {
      v10 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 340))(v9);
      v11 = &unk_6F6CC8;
      while ( v10 != *v11 )
      {
        if ( (int)++v11 >= (int)"LANDRUNNER_OUT" )
        {
          ++v3;
          goto LABEL_2;
        }
      }
      ++v1;
    }
    ++v3;
  }
}



// ------------------------------------------------------------
// 0x4C1BA0 sub_4C1BA0
// ------------------------------------------------------------
// 调: sub_4C1BA0 sub_41A590 sub_4015C0
int /*fastcall*/ sub_4C1BA0(uint32_t *a1, int a2)
{
  int v3; // edx
  int v4; // edx
  unsigned int v5; // edi
  int i; // ebx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  unsigned int v10; // ebx
  size_t *v11; // edi
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int j; // [esp+Ch] [ebp-4h]

  *a1 = 0;
  a1[1] = 0;
  sub_41A590((unsigned int)(a1 + 2), a2, 0);
  a1[6] = 0;
  sub_41A590((unsigned int)(a1 + 7), v3, 0);
  v5 = (unsigned int)a1 + 42;
  for ( i = 2; i != 0; --i )
  {
    sub_41A590(v5, v4, 0);
    v5 += 14;
  }
  sub_41A590((unsigned int)a1 + 70, v4, 0);
  sub_41A590((unsigned int)(a1 + 21), v7, 0);
  sub_41A590((unsigned int)a1 + 98, v8, 0);
  sub_41A590((unsigned int)(a1 + 28), v9, 0);
  v10 = (unsigned int)(a1 + 60);
  v11 = a1 + 46;
  for ( j = 2; j != 0; --j )
  {
    sub_4015C0(v11 - 14, szPassword, 0);
    sub_4015C0(v11, szPassword, 0);
    sub_41A590(v10, v12, 0);
    v11 += 7;
    v10 += 14;
  }
  sub_41A590((unsigned int)(a1 + 67), v13, 1000);
  return sub_41A590((unsigned int)a1 + 282, v14, 0);
}



// ------------------------------------------------------------
// 0x4C1C80 sub_4C1C80
// ------------------------------------------------------------
// 调: sub_4C1C80 sub_4C1BA0 sub_41A5E0 sub_41A590 sub_41C150
int /*cdecl*/ sub_4C1C80(uint32_t *a1, int a2)
{
  int result; // eax
  int v3; // edi
  unsigned int v4; // esi
  int v5; // eax
  unsigned int v6; // eax
  char *v7; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  unsigned int v16; // ecx
  int v17; // ecx
  unsigned int v18; // esi
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  void *v24; // eax
  int v25; // eax
  int v26; // edx
  unsigned int v27; // [esp+8h] [ebp-38h]
  int v28; // [esp+Ch] [ebp-34h]
  int v29; // [esp+10h] [ebp-30h]
  int v30; // [esp+10h] [ebp-30h]

  result = dword_796E50;
  v3 = a2;
  v4 = 0;
  if ( a2 != 0 )
  {
    sub_4C1BA0(a1);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 172))(a2);
    v6 = sub_41A5E0(v5 + 4);
    if ( dword_9A05AC != nullptr
      && (dword_9A05B0 - (int)dword_9A05AC) >> 4 > v6
      && (v7 = (char *)dword_9A05BC, dword_9A05BC != nullptr)
      && (dword_9A05C0 - (int)dword_9A05BC) >> 4 > v6 )
    {
      v8 = 16 * v6;
      v9 = *((uint32_t *)dword_9A05AC + 4 * v6 + 1);
      v28 = v8;
      if ( v9 != 0 )
        v29 = (*(uint32_t *)((char *)dword_9A05AC + v8 + 8) - v9) >> 2;
      else
        v29 = 0;
      if ( v29 > 0 )
      {
        while ( 1 )
        {
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2);
          v12 = *(uint32_t *)(v10 + 92);
          v13 = v10 + 88;
          if ( v12 == 0
            || (*(uint32_t *)(v13 + 8) - v12) >> 2 <= v4
            || *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 92) + 4 * v4) == -1 )
          {
            v14 = *(uint32_t *)((char *)dword_9A05AC + v28 + 4);
          }
          else
          {
            v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 92);
          }
          v15 = *(uint32_t *)(v14 + 4 * v4);
          if ( v4 != 0 )
          {
            switch ( v4 )
            {
              case 1u:
                sub_41A590((unsigned int)(a1 + 7), v11, v15);
                break;
              case 2u:
                sub_41A590((unsigned int)a1 + 70, v11, v15);
                break;
              case 3u:
                sub_41A590((unsigned int)a1 + 42, v11, v15);
                break;
              case 4u:
                v16 = (unsigned int)(a1 + 60);
LABEL_37:
                sub_41C150(v16, v11, v15);
                break;
              case 5u:
                v16 = (unsigned int)a1 + 254;
                goto LABEL_37;
              case 6u:
                v16 = (unsigned int)(a1 + 67);
                goto LABEL_37;
              case 7u:
                v16 = (unsigned int)(a1 + 21);
                goto LABEL_37;
              case 8u:
                v16 = (unsigned int)a1 + 98;
                goto LABEL_37;
              case 9u:
                v16 = (unsigned int)(a1 + 28);
                goto LABEL_37;
              case 0xAu:
                v16 = (unsigned int)a1 + 282;
                goto LABEL_37;
              default:
                break;
            }
          }
          else
          {
            sub_41A590((unsigned int)(a1 + 2), v11, v15);
          }
          if ( (int)++v4 >= v29 )
          {
            v7 = (char *)dword_9A05BC;
            v8 = v28;
            break;
          }
        }
      }
      v17 = *(uint32_t *)&v7[v8 + 4];
      if ( v17 != 0 )
        v30 = (*(uint32_t *)&v7[v8 + 8] - v17) >> 2;
      else
        v30 = 0;
      v18 = 0;
      v27 = 0;
      if ( v30 > 0 )
      {
        while ( 1 )
        {
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
          v20 = *(uint32_t *)(v19 + 108);
          v21 = v19 + 104;
          if ( v20 == 0 || (*(uint32_t *)(v21 + 8) - v20) >> 2 <= v18 )
            goto LABEL_49;
          v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
          if ( strcmp((const char *)sub_41ACF0(4 * v18 + *(uint32_t *)(v22 + 108)), szPassword) == 0 )
            break;
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2);
          v24 = (void *)sub_41ACF0(4 * v18 + *(uint32_t *)(v23 + 108));
          v18 = v27;
          v3 = a2;
LABEL_50:
          if ( v18 != 0 )
          {
            switch ( v18 )
            {
              case 1u:
                a1[1] = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);
                break;
              case 2u:
                a1[6] = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);
                break;
              case 3u:
                sub_4015C0(v24, strlen((const char *)v24));
                break;
              case 4u:
              case 5u:
              case 6u:
                sub_406D60(v24);
                break;
              default:
                break;
            }
          }
          else
          {
            *a1 = (*(int (/*cdecl*/ **)(int, void *))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, v24);
          }
          v27 = ++v18;
          if ( (int)v18 >= v30 )
            goto LABEL_63;
        }
        v18 = v27;
        v3 = a2;
LABEL_49:
        v24 = (void *)sub_41ACF0(*(uint32_t *)((char *)dword_9A05BC + v28 + 4) + 4 * v18);
        goto LABEL_50;
      }
LABEL_63:
      v25 = sub_41A5E0((unsigned int)a1 + 42);
      return sub_41A590((unsigned int)(a1 + 14), v26, v25);
    }
    else
    {
      return off_77F3FC(aCriticalErrorS, v6);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4C2020 sub_4C2020
// ------------------------------------------------------------
// 证: "GUN_IN" | "BOWGUN_IN"
// 调: sub_4C2020 sub_4015C0
int /*cdecl*/ sub_4C2020(int a1, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 >= 0 )
  {
    if ( a2 <= 3 )
    {
      return sub_4015C0("GUN_IN", 6u);
    }
    else if ( a2 == 4 )
    {
      return sub_4015C0("BOWGUN_IN", 9u);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2060 sub_4C2060
// ------------------------------------------------------------
// 证: "GUN_GRAB" | "BOWGUN_GRAB"
// 调: sub_4C2060 sub_4015C0
size_t */*cdecl*/ sub_4C2060(size_t *a1, int a2)
{
  size_t *result; // eax

  result = (size_t *)a2;
  if ( a2 >= 0 )
  {
    if ( a2 <= 3 )
    {
      return sub_4015C0(a1, "GUN_GRAB", 8u);
    }
    else if ( a2 == 4 )
    {
      return sub_4015C0(a1, "BOWGUN_GRAB", 0xBu);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C20A0 sub_4C20A0
// ------------------------------------------------------------
// 调: sub_4C20A0 sub_4015C0 sub_401740 sub_41C5E0 sub_52E300
int ***/*thiscall*/ sub_4C20A0(uint32_t *this, int ***a2, int **a3)
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
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
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
    sub_401740(v20);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
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
// 0x4C2360 sub_4C2360
// ------------------------------------------------------------
// 调: sub_4C2360 sub_4B36A0 sub_4C1C80
int */*thiscall*/ sub_4C2360(int this, int *a2)
{
  unsigned int v3; // ebx
  int v4; // edx
  int *v5; // edi
  int v6; // eax

  v3 = *(uint32_t *)(this + 6500);
  v5 = sub_4B36A0((int **)this, v3, a2);
  v6 = *(uint32_t *)(this + 6500);
  if ( v6 != 0 && v6 != v3 )
    sub_4C1C80(v4, (size_t *)(this + 8220), *(uint32_t *)(this + 6500));
  return v5;
}



// ------------------------------------------------------------
// 0x4C23A0 sub_4C23A0
// ------------------------------------------------------------
// 证: "BOWGUN_DRAW1" | "GUN_LOAD" | "BOWGUN_LOAD" | "GUN_DRAW1"
// 调: sub_4C23A0 sub_4CE8A0 sub_406D60 sub_4C2020 sub_4015C0
void /*cdecl*/ sub_4C23A0(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void **v6; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v9; // [esp+1Ch] [ebp-14h]
  int v10; // [esp+20h] [ebp-10h]
  int v11; // [esp+2Ch] [ebp-4h]

  v10 = dword_796E50;
  if ( a2 == 9 || a2 == 12 || a2 == 14 || a2 == 15 || a2 == 16 )
  {
    v3 = sub_4CE8A0(a3);
    if ( v3 != 0 )
    {
      v9 = 15;
      Block[4] = nullptr;
      LOBYTE(Block[0]) = 0;
      v11 = 0;
      if ( a2 == 9 )
      {
        v4 = *(uint32_t *)(v3 + 96);
        if ( v4 < 0 )
          goto LABEL_29;
        if ( v4 > 3 )
        {
          if ( v4 == 4 )
          {
LABEL_11:
            sub_406D60("BOWGUN_DRAW1");
            goto LABEL_28;
          }
LABEL_29:
          v6 = Block;
LABEL_30:
          (*(void (/*thiscall*/ **)(int, void **, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(a1, v6, -1, 0, 0);
          if ( v9 >= 0x10 )
            j__free(Block[0]);
          return;
        }
        goto LABEL_19;
      }
      if ( a2 == 16 )
      {
        sub_4C2020(v7, *(uint32_t *)(v3 + 96));
        goto LABEL_28;
      }
      v5 = *(uint32_t *)(v3 + 96);
      if ( v5 < 0 )
        goto LABEL_29;
      if ( v5 <= 2 )
      {
        if ( a2 == 12 )
        {
          sub_406D60("GUN_LOAD");
          goto LABEL_28;
        }
      }
      else
      {
        if ( v5 != 4 )
          goto LABEL_29;
        if ( a2 == 12 )
        {
          sub_406D60("BOWGUN_LOAD");
          goto LABEL_28;
        }
      }
      if ( a2 == 14 )
      {
        if ( v5 > 3 )
          goto LABEL_11;
LABEL_19:
        sub_4015C0("GUN_DRAW1", 9u);
        goto LABEL_28;
      }
      if ( v5 <= 3 )
        sub_406D60("GUN_DRAW2");
      else
        sub_406D60("BOWGUN_DRAW2");
LABEL_28:
      v6 = (void **)Block[0];
      if ( v9 >= 0x10 )
        goto LABEL_30;
      goto LABEL_29;
    }
  }
}



// ------------------------------------------------------------
// 0x4C2530 sub_4C2530
// ------------------------------------------------------------
// 证: "GUN_DRAW1" | "BOWGUN_DRAW1" | "GUN_ROTATE" | "BOWGUN_ROTATE"
// 调: sub_4C2530 sub_4015C0 sub_406D60 sub_4C2020 sub_4C2060
void /*thiscall*/ sub_4C2530(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void **v7; // eax
  uint8_t v8[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v10; // [esp+1Ch] [ebp-14h]
  int v11; // [esp+20h] [ebp-10h]
  int v12; // [esp+2Ch] [ebp-4h]

  v11 = dword_796E50;
  if ( (a2 == 10 || a2 == 11 || a2 == 13 || a2 == 15) && *(this + 1625) != 0 )
  {
    v10 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    v12 = 0;
    switch ( a2 )
    {
      case 10:
        v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);
        if ( v3 >= 0 )
        {
          if ( v3 <= 3 )
          {
            sub_4015C0("GUN_DRAW1", 9u);
          }
          else if ( v3 == 4 )
          {
            sub_406D60("BOWGUN_DRAW1");
          }
        }
        break;
      case 15:
        v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);
        sub_4C2020(v8, v4);
        break;
      case 11:
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);
        if ( v5 >= 0 )
        {
          if ( v5 <= 3 )
          {
            sub_406D60("GUN_ROTATE");
          }
          else if ( v5 == 4 )
          {
            sub_406D60("BOWGUN_ROTATE");
          }
        }
        break;
      default:
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this);
        sub_4C2060(v8, v6);
        break;
    }
    v7 = (void **)Block[0];
    if ( v10 < 0x10 )
      v7 = Block;
    (*(void (/*thiscall*/ **)(uint32_t *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v7, -1, 0, 0);
    if ( v10 >= 0x10 )
      j__free(Block[0]);
  }
}



// ------------------------------------------------------------
// 0x4C26A0 sub_4C26A0
// ------------------------------------------------------------
// 调: sub_4C26A0 sub_4C1400 sub_4C20A0
int **/*thiscall*/ sub_4C26A0(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_4C1400(*(void ***)(v7 + 4));
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
        v10 = (int **)v5;
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
        sub_4C20A0(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4C2760 sub_4C2760
// ------------------------------------------------------------
// 调: sub_4C2760 sub_41DC80
int /*cdecl*/ sub_4C2760(int a1, int a2, int a3)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 16 )
    result = sub_41DC80(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x4C2790 sub_4C2790
// ------------------------------------------------------------
// 调: sub_4C2790 sub_41DC80
int /*cdecl*/ sub_4C2790(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 16;
    v4 -= 16;
    sub_41DC80(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4C27D0 sub_4C27D0
// ------------------------------------------------------------
// 调: sub_4C27D0 sub_699000 sub_40C0F0 sub_437320
int /*thiscall*/ sub_4C27D0(int *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ecx
  uint32_t *v5; // ebx
  int result; // eax
  int v7; // [esp+Ch] [ebp-4h] BYREF

  v2 = sub_699000((int)(this + 2));
  v3 = *(this + 2131);
  v4 = *(uint32_t *)(v3 + 4);
  v7 = v2;
  v5 = sub_40C0F0(v3, v4, &v7);
  result = sub_437320(1);
  *(uint32_t *)(v3 + 4) = v5;
  *(uint32_t *)v5[1] = v5;
  return result;
}



// ------------------------------------------------------------
// 0x4C2820 sub_4C2820
// ------------------------------------------------------------
// 调: sub_4C2820 sub_4B1030 sub_5F9AE0 sub_5F9B20
int /*thiscall*/ sub_4C2820(int this, int a2, int a3)
{
  sub_4B1030((uint8_t *)this);
  *(uint32_t *)this = &CNWeaponMastery::`vftable';
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  sub_5F9AE0(this);
  sub_5F9B20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x4C2890 sub_4C2890
// ------------------------------------------------------------
// 调: sub_4C2890 sub_4C28C0
void */*thiscall*/ sub_4C2890(void *Block, char a2)
{
  sub_4C28C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4C28C0 sub_4C28C0
// ------------------------------------------------------------
// 调: sub_4C28C0 sub_5F6640
int /*thiscall*/ sub_4C28C0(void **this)
{
  int result; // eax

  *this = &CNWeaponMastery::`vftable';
  nullsub_3(this);
  if ( *(this + 21) != nullptr )
    j__free(*(this + 21));
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x4C2940 sub_4C2940
// ------------------------------------------------------------
// 调: sub_4C2940 sub_4B3E70 sub_53FE50 sub_4C2820 sub_5F9DD0
void /*thiscall*/ sub_4C2940(int *this, void *a2, void *Block)
{
  void *v4; // eax
  int v5; // eax
  int v6; // ecx

  sub_4B3E70(this, a2, (int)Block);
  if ( a2 == (void *)52 )
  {
    if ( (int)Block <= 0 )
    {
      v6 = *(this + 2379);
      if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6) != 0 )
        sub_53FE50(*(this + 2379));
    }
    else
    {
      if ( *(this + 2379) == 0 )
      {
        v4 = operator new(0x88u);
        if ( v4 != nullptr )
          v5 = sub_4C2820((int)v4, 2, 52);
        else
          v5 = 0;
        *(this + 2379) = v5;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 64))(v5) + 36) = 0;
      }
      sub_5F9DD0(Block);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2379) + 56))(
        *(this + 2379),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
}



// ------------------------------------------------------------
// 0x4C2A30 sub_4C2A30
// ------------------------------------------------------------
// 调: sub_4C2A30 sub_4C1070 sub_4B3DF0
int /*thiscall*/ sub_4C2A30(uint32_t *this, void *Block)
{
  int result; // eax
  int v4; // esi
  bool v5; // bl
  int v6; // esi
  int v7; // eax
  float v8; // [esp+Ch] [ebp-28h]
  int v9; // [esp+24h] [ebp-10h]

  nullsub_1(Block);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 52))(Block);
  if ( result == *(this + 2370) )
  {
    result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529);
    if ( (uint8_t)result == 1 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 792))(this, 8);
      if ( v4 != 0
        || (result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 792))(this, 10), v4 = result, result != 0) )
      {
        result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4) + 4);
        v5 = false;
        v9 = 20;
        if ( result == 32240 || result == 32265 )
          goto LABEL_11;
        if ( result == 10095 )
        {
          result = sub_4C1070(v4);
          if ( (uint8_t)result != 0 )
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 224))(v4);
            v5 = (uint8_t)result != 0;
          }
          v9 = 15;
          if ( v5 )
          {
LABEL_11:
            v6 = __RTDynamicCast(
                   (int)Block,
                   0,
                   &CNRDObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
            if ( operator new(0x7Cu) != nullptr )
            {
              v8 = (float)v9;
              v7 = sub_4B3DF0(8, 1, LODWORD(v8), 0, 0);
            }
            else
            {
              v7 = 0;
            }
            result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v7 + 56))(
                       v7,
                       v6,
                       v6,
                       0,
                       0,
                       0,
                       -1);
          }
        }
        *(this + 2370) = 0xFFFF;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2B80 sub_4C2B80
// ------------------------------------------------------------
// 调: sub_4C2B80 sub_4C2790
int /*cdecl*/ sub_4C2B80(int a1, int a2, int a3)
{
  return sub_4C2790(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4C2BA0 sub_4C2BA0
// ------------------------------------------------------------
// 调: sub_4C2BA0 sub_4B3600
unsigned int ***/*cdecl*/ sub_4C2BA0(unsigned int ***a1, int a2, int a3)
{
  unsigned int ***v3; // esi
  unsigned int ***result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      result = sub_4B3600(v3, a3);
    --a2;
    v3 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C2C30 sub_4C2C30
// ------------------------------------------------------------
// 调: sub_4C2C30 sub_4C26A0
int /*thiscall*/ sub_4C2C30(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4C26A0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4C2C70 sub_4C2C70
// ------------------------------------------------------------
// 调: sub_4C2C70 sub_47E9D0 sub_699000 sub_47E440 sub_4AED20
int /*thiscall*/ sub_4C2C70(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // esi
  int v6; // esi
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *v14; // [esp+Ch] [ebp-20h] BYREF
  int v15; // [esp+10h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-18h]
  int v17; // [esp+18h] [ebp-14h]
  int v18; // [esp+1Ch] [ebp-10h] BYREF
  int v19; // [esp+28h] [ebp-4h]

  if ( *(this + 1639) == 12
    && (uint32_t *)dword_8F7C04 == this
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 8) > 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 8);
    v5 = sub_47E9D0(1);
    v6 = sub_699000((int)(this + 1640)) + v5;
    v7 = *this;
    *(this + 2162) = v6;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 1160))(this, 3);
    sub_47E440(1);
    byte_9A0358 = 1;
  }
  v8 = a2;
  if ( *(this + 1639) == 17
    && *(this + 154) == -1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v9 = __RTDynamicCast(v8, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( v9 != 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 824))(v9) != 0
      && (unsigned int)sub_4AED20(v8) <= 1 )
    {
      v15 = 0;
      v16 = 0;
      v17 = 0;
      v19 = 0;
      a2 = 0;
      sub_431230(&a2);
      a2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 48))(v8);
      sub_431230(&a2);
      a2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 52))(v8);
      sub_431230(&a2);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 18, &v14, 0, 0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 596))(v8, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
      v19 = -1;
      sub_5E5260(&v14);
    }
  }
  if ( *(this + 1639) == 16
    && *(this + 2172) == 14
    && *(this + 154) == -1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v10 = __RTDynamicCast(v8, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( v10 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 824))(v10) != 0 )
    {
      v18 = sub_4AED20(v8);
      v11 = *(uint32_t *)v8;
      a2 = 100;
      v12 = (*(int (/*thiscall*/ **)(int, int *, uint32_t *))(v11 + 648))(v8, &a2, this);
      if ( v18 == 0 && v12 == 0 )
      {
        v15 = 0;
        v16 = 0;
        v17 = 0;
        v19 = 1;
        v18 = 14;
        sub_431230(&v18);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 48))(v8);
        sub_431230(&v18);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 52))(v8);
        sub_431230(&v18);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, &v14, 0, 0);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 596))(v8, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
        v19 = -1;
        sub_5E5260(&v14);
      }
    }
  }
  return sub_4AFB30(v8, a3, a4);
}



// ------------------------------------------------------------
// 0x4C2F40 sub_4C2F40
// ------------------------------------------------------------
// 调: sub_4C2F40 sub_47EF20 sub_445870 sub_431230 sub_5E5260
int /*thiscall*/ sub_4C2F40(uint32_t *this, int a2, float *a3, char a4)
{
  int v4; // ebx
  float *v6; // eax
  int v7; // edx
  float *v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // edx
  float *v12; // ecx
  int v13; // eax
  int v14; // eax
  float *v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v30; // [esp-Ch] [ebp-40h]
  int v31; // [esp-Ch] [ebp-40h]
  int v32; // [esp-4h] [ebp-38h]
  int v33; // [esp+0h] [ebp-34h]
  int v34; // [esp+4h] [ebp-30h]
  int v35; // [esp+8h] [ebp-2Ch]
  void *v36; // [esp+Ch] [ebp-28h] BYREF
  int v37; // [esp+10h] [ebp-24h]
  int v38; // [esp+14h] [ebp-20h] BYREF
  int v39; // [esp+18h] [ebp-1Ch]
  int v40; // [esp+1Ch] [ebp-18h]
  float *v41; // [esp+20h] [ebp-14h]
  int v42; // [esp+24h] [ebp-10h]
  int v43; // [esp+30h] [ebp-4h]

  v4 = a2;
  v6 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  v7 = *(uint32_t *)v4;
  v8 = v6;
  v41 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(v7 + 368))(v4) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 10) <= 0
    || *((uint8_t *)v8 + 16) == 0 && *v8 <= 0.0 )
  {
    goto LABEL_20;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) != 0 )
    goto LABEL_20;
  v9 = *(this + 1639);
  if ( v9 == 4 )
    goto LABEL_20;
  if ( v9 == 9 )
    goto LABEL_20;
  if ( a4 != 0 )
    goto LABEL_20;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 10);
  v11 = *this;
  v42 = v10;
  a2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 1140))(this, 10);
  v40 = sub_47EF20(0, a2, -1, -1, 11);
  if ( sub_445870(&unk_6D0B57, 10000) >= (signed int)(100 * (uint64_t)(double)v40)
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 10) == 0 )
  {
    goto LABEL_20;
  }
  v12 = v41;
  *((uint8_t *)this + 8960) = 1;
  v13 = *((uint32_t *)v12 + 3);
  if ( v13 == 1 )
  {
    v14 = sub_47EF20(2, a2, -1, -1, 11);
  }
  else
  {
    if ( v13 != 0 )
    {
      if ( v13 == 2 )
        *(this + 2241) = 100;
      goto LABEL_18;
    }
    v14 = sub_47EF20(1, a2, -1, -1, 11);
  }
  *(this + 2241) = 100 - v14;
LABEL_18:
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v37 = 0;
    v38 = 0;
    v39 = 0;
    v43 = 0;
    a2 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)v4 + 660))(v4, this);
    sub_431230((int)&v36, &a2);
    v15 = a3;
    a2 = (uint64_t)(a3[3] * 0.5 + *a3);
    sub_431230((int)&v36, &a2);
    a2 = (uint64_t)(v15[5] * 0.5 + v15[2]);
    sub_431230((int)&v36, &a2);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 21, &v36, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 8);
    v43 = -1;
    sub_5E5260(&v36);
  }
LABEL_20:
  if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 26) > 0
    && *((uint8_t *)this + 8960) == 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 0 )
  {
    v16 = *(this + 1639);
    if ( v16 != 4 && v16 != 9 && sub_4AED00(v41) && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 576))(v4) != 0 )
    {
      v30 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, 26, -1);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);
      v17 = sub_47EF20(26, 0, v30, -1, 11);
      if ( sub_445870(28748541, 10000) < 100 * v17
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 26) != 0 )
      {
        *((uint8_t *)this + 8597) = 1;
      }
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 42) > 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 348))(v4);
    if ( *(uint8_t *)(v18 + 16) != 0 || *(float *)v18 > 0.0 )
    {
      v31 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, 42, -1);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);
      v19 = sub_47EF20(42, 0, v31, -1, 11);
      v32 = sub_445870(253547152, 0);
      v20 = sub_445870(253547151, 0);
      off_77F3FC("RAND %d %d", v20, v32);
      if ( sub_445870(253547151, 100) < v19
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 42) != 0 )
      {
        LOWORD(v38) = rand() % 50 + 25;
        HIWORD(v38) = rand() % 50 + 25;
        BYTE2(v39) = rand() % 2 == 0;
        HIBYTE(v39) = 3 - (rand() % 2 != 0);
        LOWORD(v39) = rand() % 60 + 40;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 1140))(this, 27, -1, -1, 11);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 1160))(this, 27, 0, v21);
        v22 = sub_47EF20(v33, v34, v35, v36, v37);
        v23 = *this;
        v37 = 0;
        v36 = nullptr;
        a2 = v22;
        v24 = (*(int (/*thiscall*/ **)(uint32_t *, int, int *, int))(v23 + 152))(this, 1, &v38, 8);
        v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, v24);
        v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v25);
        v27 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v26);
        v28 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 376))(this, a2, v27);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v23 + 592))(this, 60002, v28);
      }
    }
  }
  return sub_4AFB80(this, v4, (int)a3, a4);
}


// ------------------------------------------------------------
// 0x4C3400 sub_4C3400
// ------------------------------------------------------------
// 调: sub_4C3400 sub_4B9720 sub_431230 sub_5E5260
int /*thiscall*/ sub_4C3400(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax
  void *v8[7]; // [esp+Ch] [ebp-1Ch] BYREF

  v5 = sub_4B9720(a2, a3, a4);
  if ( *((uint8_t *)this + 8597) != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v6 = *(this + 154);
    if ( v6 != 3 && v6 != 4 && v6 != 5 )
    {
      memset(&v8[1], 0, 12);
      v8[6] = nullptr;
      a4 = 0;
      sub_431230(&a4);
      a4 = 26;
      sub_431230(&a4);
      a4 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)a2 + 660))(a2, this);
      sub_431230(&a4);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 24, v8, 0, 0);
      sub_5E5260(v8);
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x4C34F0 sub_4C34F0
// ------------------------------------------------------------
// 调: sub_4C34F0 sub_431230
void /*thiscall*/ sub_4C34F0(uint32_t *this, int a2)
{
  uint8_t v3[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v5; // [esp+Ch] [ebp-14h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    if ( a2 < 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
    else
    {
      Block = nullptr;
      v5 = 0;
      v6 = 0;
      v7 = 0;
      sub_431230((int)v3, this + 2129);
      sub_431230((int)v3, this + 2242);
      sub_431230((int)v3, &a2);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 26, v3, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x4C35C0 sub_4C35C0
// ------------------------------------------------------------
// 调: sub_4C35C0 sub_425120 sub_498190 sub_497E30
int /*thiscall*/ sub_4C35C0(int this, int a2)
{
  sub_425120();
  *(uint32_t *)this = &CNRDObjectParticleCreater::`vftable';
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 296) = 15;
  *(uint32_t *)(this + 292) = 0;
  *(uint8_t *)(this + 276) = 0;
  sub_498190((size_t *)this);
  sub_497E30(this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x4C3640 sub_4C3640
// ------------------------------------------------------------
// 调: sub_4C3640 sub_425120 sub_498190 sub_497E40
int /*thiscall*/ sub_4C3640(int this, int a2, int a3, int a4)
{
  sub_425120();
  *(uint32_t *)this = &CNRDObjectParticleCreater::`vftable';
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 296) = 15;
  *(uint32_t *)(this + 292) = 0;
  *(uint8_t *)(this + 276) = 0;
  sub_498190((size_t *)this);
  sub_497E40((void *)this, a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x4C36D0 sub_4C36D0
// ------------------------------------------------------------
// 调: sub_4C36D0 sub_4B1030 sub_433AC0 sub_5FA160 sub_5F9160
int /*thiscall*/ sub_4C36D0(int this)
{
  int v2; // eax

  sub_4B1030((uint8_t *)this);
  *(uint32_t *)this = &CNRobotics::`vftable';
  v2 = sub_433AC0(this + 80);
  *(uint32_t *)(this + 84) = v2;
  *(uint8_t *)(v2 + 21) = 1;
  *(uint32_t *)(*(uint32_t *)(this + 84) + 4) = *(uint32_t *)(this + 84);
  **(uint32_t **)(this + 84) = *(uint32_t *)(this + 84);
  *(uint32_t *)(*(uint32_t *)(this + 84) + 8) = *(uint32_t *)(this + 84);
  *(uint32_t *)(this + 88) = 0;
  sub_5FA160(this);
  sub_5F9160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4C3750 sub_4C3750
// ------------------------------------------------------------
// 调: sub_4C3750 sub_4C3780
void */*thiscall*/ sub_4C3750(void *Block, char a2)
{
  sub_4C3780();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4C3780 sub_4C3780
// ------------------------------------------------------------
// 调: sub_4C3780 sub_4C26A0 sub_5F6640
int /*thiscall*/ sub_4C3780(int this)
{
  int result; // eax
  int *v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-4h] [ebp-24h]
  int *v5[2]; // [esp+Ch] [ebp-14h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &CNRobotics::`vftable';
  v6 = 1;
  nullsub_3(this);
  v4 = *(int **)(this + 84);
  v3 = (int *)*v4;
  LOBYTE(v6) = 0;
  sub_4C26A0((int ***)(this + 80), v5, v3, v4);
  j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)this = &IRDAppendage::`vftable';
  v6 = 2;
  result = sub_5F6640(this);
  *(uint8_t *)(this + 12) = 0;
  *(uint32_t *)(this + 8) = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x4C3810 sub_4C3810
// ------------------------------------------------------------
// 证: "R_GN_DMG" | "R_GN_DIE" | "GN_JUMP" | "GN_BACK_STEP"
// 调: sub_4C3810 sub_4015C0 sub_4C35C0
void */*thiscall*/ sub_4C3810(uint32_t *this)
{
  void *result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *(this + 1716) = 1;
  *(this + 1717) = 7;
  *(this + 1718) = 13;
  *(this + 1977) = 0;
  *(this + 1978) = 0;
  *(this + 1979) = 0;
  *(this + 1980) = 0;
  *(this + 1961) = 44;
  *(this + 1962) = 65;
  *(this + 1963) = 2;
  *(this + 1982) = 8;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("R_GN_DMG", 8u);
  sub_4015C0("R_GN_DIE", 8u);
  sub_4015C0("GN_JUMP", 7u);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("GN_BACK_STEP", 0xCu);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("R_GN_NOMANA", 0xBu);
  sub_4015C0("R_GN_COMMAND_PET", 0x10u);
  sub_4015C0("GN_THROW", 8u);
  result = operator new(0x12Cu);
  if ( result != nullptr )
  {
    result = (void *)sub_4C35C0(this);
    *(this + 2054) = result;
  }
  else
  {
    *(this + 2054) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4C39D0 sub_4C39D0
// ------------------------------------------------------------
// 证: "BUFF_FLAMESHOT" | "BUFF_ICESHOT" | "BUFF_SILVERSHOT" | "Common/CommonEffect/BuffIcon.img"
// 调: sub_4C39D0 sub_4B4170 sub_41A5E0 sub_4C10A0 sub_47EF20
int /*thiscall*/ sub_4C39D0(int this, uint32_t *Block, void *a3)
{
  int result; // eax
  int v5; // edi
  void *v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // ecx
  int **v13; // ebx
  uint8_t *v14; // eax
  int *v15; // eax
  int *v16; // ebx
  int v17; // ebx
  int v18; // edi
  int v19; // ebx
  char *v20; // eax
  int v21; // ebx
  uint8_t *v22; // eax
  uint8_t *v23; // eax
  int v24; // edi
  int v25; // eax
  int v26; // eax
  int v27; // [esp-Ch] [ebp-28h]
  int v28; // [esp+0h] [ebp-1Ch]
  void *v29; // [esp+Ch] [ebp-10h]
  int Blocka; // [esp+24h] [ebp+8h]
  int **v31; // [esp+28h] [ebp+Ch]

  sub_4B4170((float *)this, Block, a3);
  result = sub_41A5E0((unsigned int)(Block + 1));
  v5 = result;
  switch ( result )
  {
    case 1:
    case 2:
    case 30:
      v21 = 0;
      if ( *(uint32_t *)(this + 8656) == 0 )
      {
        v22 = operator new(0x60u);
        if ( v22 != nullptr )
          v23 = sub_4C10A0(v22);
        else
          v23 = nullptr;
        *(uint32_t *)(this + 8656) = v23;
      }
      switch ( v5 )
      {
        case 1:
          v21 = 13;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "BUFF_FLAMESHOT",
            -1,
            0,
            0);
          break;
        case 2:
          v21 = 14;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "BUFF_ICESHOT",
            -1,
            0,
            0);
          break;
        case 30:
          v21 = 15;
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "BUFF_SILVERSHOT",
            -1,
            0,
            0);
          break;
        default:
          break;
      }
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 49) <= 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8656) + 124))(*(uint32_t *)(this + 8656), 0);
      }
      else
      {
        v24 = **(uint32_t **)(this + 8656);
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1140))(this);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)this + 1160))(this, 49, 0, v25);
        v26 = sub_47EF20(49, -1, -1, 11, v28);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v24 + 124))(*(uint32_t *)(this + 8656), v26);
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(**(uint32_t **)(this + 8656) + 120))(*(uint32_t *)(this + 8656), Block);
      v10 = **(uint32_t **)(this + 8656);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img",
        v21,
        0,
        -1);
      v11 = sub_418DD0(a3);
      v12 = *(uint32_t *)(this + 8656);
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(v10 + 56))(v12, this, this, 1, v11);
    case 46:
      if ( *(uint32_t *)(this + 8660) == 0 )
      {
        v6 = operator new(0x6Cu);
        if ( v6 != nullptr )
          v7 = sub_4C36D0((int)v6);
        else
          v7 = 0;
        *(uint32_t *)(this + 8660) = v7;
      }
      v8 = *(uint32_t *)(this + 8660);
      v9 = sub_47EF20(0, a3, -1, -1, 11);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 64))(v8) + 40) = v9;
      v10 = **(uint32_t **)(this + 8660);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);
      v11 = sub_418DD0("Common/CommonEffect/BuffIcon.img");
      v12 = *(uint32_t *)(this + 8660);
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(v10 + 56))(v12, this, this, 1, v11);
    case 33:
    case 37:
      if ( result == 33 )
      {
        v13 = (int **)(this + 8624);
        Blocka = 17;
      }
      else
      {
        v13 = (int **)(this + 8652);
        Blocka = 18;
      }
      v31 = v13;
      if ( *v13 == nullptr )
      {
        v14 = operator new(0x50u);
        if ( v14 != nullptr )
          v15 = (int *)sub_4B1030(v14);
        else
          v15 = nullptr;
        *v13 = v15;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v15 + 64))(v15) + 36) = 0;
      }
      v16 = *v13;
      v27 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, v5, -1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);
      v29 = (void *)sub_47EF20(v5, 0, v27, -1, 11);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v16 + 64))(v16) + 40) = v29;
      v17 = **v31;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img",
        Blocka,
        0,
        -1);
      sub_418DD0(v28);
      result = (*(int (/*thiscall*/ **)(int *, int, int, int))(v17 + 56))(*v31, this, this, 1);
      if ( v5 == 33 )
      {
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 33);
        v20 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 33);
        result = sub_47EFD0(v20, COERCE_FLOAT(1), v19, v18, v18, 0);
        *(uint32_t *)(this + 8628) = result;
      }
      break;
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4C3D40 sub_4C3D40
// ------------------------------------------------------------
// 调: sub_4C3D40 sub_4C2BA0
unsigned int ***/*stdcall*/ sub_4C3D40(unsigned int ***a1, int a2, int a3)
{
  sub_4C2BA0(a1, a2, a3);
  return &a1[4 * a2];
}



// ------------------------------------------------------------
// 0x4C3D70 sub_4C3D70
// ------------------------------------------------------------
// 调: sub_4C3D70 sub_4B3B60 sub_4B4950
int */*thiscall*/ sub_4C3D70(int *this, int *a2, int a3, int a4)
{
  int v5; // edi

  if ( a3 != a4 )
  {
    v5 = sub_4B3B60(a4, *(this + 2), a3);
    sub_4B4950(v5, *(this + 2));
    *(this + 2) = v5;
  }
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x4C3DC0 sub_4C3DC0
// ------------------------------------------------------------
// 调: sub_4C3DC0 sub_4B3600 sub_4B2F20 sub_4B5060 sub_4C2B80
void /*thiscall*/ sub_4C3DC0(int this, int a2, unsigned int a3, int a4)
{
  int v5; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v13; // ebx
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // edi
  char *v17; // eax
  int v18; // edi
  char *v19; // edi
  int v20; // eax
  void *v21; // ebx
  void **v22; // edi
  void **v23; // esi
  int v24; // [esp-18h] [ebp-4Ch]
  void *v25; // [esp-18h] [ebp-4Ch]
  int v26; // [esp-Ch] [ebp-40h]
  unsigned int v27; // [esp-8h] [ebp-3Ch]
  int v28; // [esp+0h] [ebp-34h] BYREF
  char v29[4]; // [esp+Ch] [ebp-28h] BYREF
  void *v30; // [esp+10h] [ebp-24h]
  void **v31; // [esp+14h] [ebp-20h]
  void *Block; // [esp+1Ch] [ebp-18h]
  int v33; // [esp+20h] [ebp-14h]
  int *v34; // [esp+24h] [ebp-10h]
  int v35; // [esp+30h] [ebp-4h]
  int v36; // [esp+40h] [ebp+Ch]
  int v37; // [esp+44h] [ebp+10h]

  v34 = &v28;
  v33 = this;
  sub_4B3600(a4);
  v5 = *(uint32_t *)(this + 4);
  v6 = 0;
  v35 = 0;
  if ( v5 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v5) >> 4;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(this + 8) - v5) >> 4;
    if ( 0xFFFFFFF - v6 < a3 )
      sub_4B2F20(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 4;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v17 = *(char **)(this + 8);
      Block = v17;
      if ( (int)&v17[-a2] >> 4 >= a3 )
      {
        v19 = &v17[-16 * a3];
        v20 = sub_4B5060(v19, v17, v17);
        v25 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_4C2B80(a2, v19, v25);
        sub_4C2760(a2, a2 + 16 * a3, v29);
      }
      else
      {
        sub_4B5060(a2, v17, a2 + 16 * a3);
        v27 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 4);
        v26 = *(uint32_t *)(this + 8);
        LOBYTE(v35) = 3;
        sub_4C3D40(v26, v27, v29);
        v18 = 16 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v18;
        v35 = 0;
        sub_4C2760(a2, v18 - 16 * a3, v29);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 4;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 4;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v37 = 16 * v10;
      v13 = (char *)operator new(16 * v10);
      v24 = *(uint32_t *)(this + 4);
      Block = v13;
      LOBYTE(v35) = 1;
      v36 = sub_4B5060(v24, a2, v13);
      sub_4C2BA0(v36, a3, v29);
      sub_4B5060(a2, *(uint32_t *)(this + 8), 16 * a3 + v36);
      v14 = *(uint32_t *)(this + 4);
      v35 = 0;
      if ( v14 != 0 )
        v15 = (*(uint32_t *)(this + 8) - v14) >> 4;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != 0 )
      {
        sub_4B4950(v14, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v13[v37];
      *(uint32_t *)(this + 8) = &v13[16 * v16];
      *(uint32_t *)(this + 4) = v13;
    }
  }
  v21 = v30;
  v35 = -1;
  if ( v30 != nullptr )
  {
    v22 = v31;
    v23 = (void **)v30;
    if ( v30 != v31 )
    {
      do
        sub_41B010(v23++);
      while ( v23 != v22 );
    }
    j__free(v21);
  }
}


// ------------------------------------------------------------
// 0x4C4080 sub_4C4080
// ------------------------------------------------------------
// 调: sub_4C4080 sub_4C3D70 sub_4C3DC0 sub_41B010
void /*thiscall*/ sub_4C4080(int *this, unsigned int a2, char a3, void *Block, void *a5, int a6)
{
  int v6; // esi
  unsigned int v7; // edx
  int v8; // edx
  void *v9; // ebx
  int v10; // edi
  void **v11; // esi

  v6 = *(this + 1);
  if ( v6 != 0 )
    v7 = (*(this + 2) - v6) >> 4;
  else
    v7 = 0;
  if ( v7 >= a2 )
  {
    if ( v6 != 0 && a2 < (*(this + 2) - v6) >> 4 )
      sub_4C3D70(this, (int *)&a2, v6 + 16 * a2, *(this + 2));
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) >> 4;
    else
      v8 = 0;
    sub_4C3DC0((int)this, *(this + 2), a2 - v8, (int)&a3);
  }
  v9 = Block;
  if ( Block != nullptr )
  {
    v10 = (int)a5;
    v11 = (void **)Block;
    if ( Block != a5 )
    {
      do
        sub_41B010(v11++);
      while ( v11 != (void **)v10 );
    }
    j__free(v9);
  }
}



// ------------------------------------------------------------
// 0x4C4150 sub_4C4150
// ------------------------------------------------------------
// 调: sub_4C4150 sub_430B70 sub_4A2CF0 sub_493BD0 sub_494E40
int /*thiscall*/ sub_4C4150(int this, int a2, int a3, const char *ArgList, char a5)
{
  uint32_t *v6; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B88;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  v6 = (uint32_t *)(this + 60);
  v6[15] = 0;
  v6[16] = 0;
  v6[17] = 0;
  v6[19] = 0;
  v6[20] = 0;
  v6[21] = 0;
  sub_430B70(v6);
  *(uint32_t *)(this + 204) = sub_4A2CF0();
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, szPassword, ArgList, a5, 1, 0, a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x4C4210 sub_4C4210
// ------------------------------------------------------------
// 调: sub_4C4210 sub_42AF90 sub_657740
int sub_4C4210()
{
  void ***v0; // esi
  int i; // ebx
  void **v2; // edi
  int result; // eax

  v0 = (void ***)&dword_9A0598;
  do
  {
    for ( i = 2; i != 0; --i )
    {
      v2 = *v0;
      if ( *v0 != nullptr )
      {
        sub_42AF90(*v0);
        result = sub_657740(v2, 228);
      }
      *v0++ = nullptr;
    }
  }
  while ( (int)v0 < (int)&dword_9A05A8 );
  return result;
}



// ------------------------------------------------------------
// 0x4C4260 sub_4C4260
// ------------------------------------------------------------
// 调: sub_4C4260 sub_42AF90 sub_657740
int /*thiscall*/ sub_4C4260(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void ***v3; // edi
  void **v4; // ebx
  int v5; // edi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  void ***v10; // edi
  void **v11; // ebx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  void ***v13; // edi
  void **v14; // ebx
  void ***v15; // esi
  int ii; // ebx
  void **v17; // edi
  void ***v18; // esi
  int mm; // ebx
  void **v20; // edi
  int v21; // edi
  void (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  void ***v23; // esi
  void **v24; // ebx
  void (/*thiscall*/ ***v25)(uint32_t, int); // ecx
  void **v26; // esi
  void **v27; // esi
  void **v28; // esi
  void **v29; // esi
  void ***v30; // esi
  int v31; // ebx
  void **v32; // ebx
  bool v33; // zf
  void **v34; // ebx
  void **v35; // ebx
  int result; // eax
  int v37; // esi
  int (/*thiscall*/ ***v38)(uint32_t, int); // ecx
  int v39; // [esp+Ch] [ebp-Ch]
  int nn; // [esp+Ch] [ebp-Ch]
  int v41; // [esp+Ch] [ebp-Ch]
  int m; // [esp+10h] [ebp-8h]
  int kk; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  int j; // [esp+14h] [ebp-4h]
  int k; // [esp+14h] [ebp-4h]
  int n; // [esp+14h] [ebp-4h]
  int jj; // [esp+14h] [ebp-4h]

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8216);
  v39 = this;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 8216) = 0;
  v3 = (void ***)(this + 8600);
  for ( i = 2; i != 0; --i )
  {
    v4 = *v3;
    if ( *v3 != nullptr )
    {
      sub_42AF90(*v3);
      sub_657740(v4, 228);
    }
    *v3++ = nullptr;
  }
  v5 = *(uint32_t *)(this + 8612);
  if ( v5 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8612));
    sub_657740(v5, 228);
  }
  v6 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8624);
  *(uint32_t *)(this + 8612) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8652);
  *(uint32_t *)(this + 8624) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8656);
  *(uint32_t *)(this + 8652) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8660);
  *(uint32_t *)(this + 8656) = 0;
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  *(uint32_t *)(this + 8660) = 0;
  v10 = (void ***)(this + 8680);
  for ( j = 2; j != 0; --j )
  {
    v11 = *v10;
    if ( *v10 != nullptr )
    {
      sub_42AF90(*v10);
      sub_657740(v11, 228);
    }
    *v10++ = nullptr;
  }
  v12 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8716);
  if ( v12 != nullptr )
    (**v12)(v12, 1);
  *(uint32_t *)(this + 8716) = 0;
  v13 = (void ***)(this + 8720);
  for ( k = 2; k != 0; --k )
  {
    v14 = *v13;
    if ( *v13 != nullptr )
    {
      sub_42AF90(*v13);
      sub_657740(v14, 228);
    }
    *v13++ = nullptr;
  }
  v15 = (void ***)(this + 8760);
  for ( m = 5; m != 0; --m )
  {
    for ( n = 5; n != 0; --n )
    {
      for ( ii = 2; ii != 0; --ii )
      {
        v17 = *v15;
        if ( *v15 != nullptr )
        {
          sub_42AF90(*v15);
          sub_657740(v17, 228);
        }
        *v15++ = nullptr;
      }
    }
  }
  v18 = (void ***)(v39 + 8972);
  for ( jj = 5; jj != 0; --jj )
  {
    for ( kk = 8; kk != 0; --kk )
    {
      for ( mm = 2; mm != 0; --mm )
      {
        v20 = *v18;
        if ( *v18 != nullptr )
        {
          sub_42AF90(*v18);
          sub_657740(v20, 228);
        }
        *v18++ = nullptr;
      }
    }
  }
  v21 = v39;
  v22 = *(void (/*thiscall*/ ****)(uint32_t, int))(v39 + 9328);
  if ( v22 != nullptr )
    (**v22)(v22, 1);
  *(uint32_t *)(v39 + 9328) = 0;
  v23 = (void ***)(v39 + 9332);
  for ( nn = 3; nn != 0; --nn )
  {
    v24 = *v23;
    if ( *v23 != nullptr )
    {
      sub_42AF90(*v23);
      sub_657740(v24, 228);
    }
    *v23++ = nullptr;
  }
  v25 = *(void (/*thiscall*/ ****)(uint32_t, int))(v21 + 9360);
  if ( v25 != nullptr )
    (**v25)(v25, 1);
  v26 = *(void ***)(v21 + 9364);
  *(uint32_t *)(v21 + 9360) = 0;
  if ( v26 != nullptr )
  {
    sub_42AF90(v26);
    sub_657740(v26, 228);
  }
  v27 = *(void ***)(v21 + 9372);
  *(uint32_t *)(v21 + 9364) = 0;
  if ( v27 != nullptr )
  {
    sub_42AF90(v27);
    sub_657740(v27, 228);
  }
  v28 = *(void ***)(v21 + 9376);
  *(uint32_t *)(v21 + 9372) = 0;
  if ( v28 != nullptr )
  {
    sub_42AF90(v28);
    sub_657740(v28, 228);
  }
  v29 = *(void ***)(v21 + 9396);
  *(uint32_t *)(v21 + 9376) = 0;
  if ( v29 != nullptr )
  {
    sub_42AF90(v29);
    sub_657740(v29, 228);
  }
  *(uint32_t *)(v21 + 9396) = 0;
  v30 = (void ***)(v21 + 9388);
  v41 = 2;
  do
  {
    v31 = (int)*(v30 - 2);
    if ( v31 != 0 )
    {
      sub_42AF90(*(v30 - 2));
      sub_657740(v31, 228);
    }
    v32 = *v30;
    v33 = *v30 == nullptr;
    *(v30 - 2) = nullptr;
    if ( !v33 )
    {
      sub_42AF90(v32);
      sub_657740(v32, 228);
    }
    v34 = v30[3];
    *v30 = nullptr;
    if ( v34 != nullptr )
    {
      sub_42AF90(v34);
      sub_657740(v34, 228);
    }
    v35 = v30[5];
    v30[3] = nullptr;
    if ( v35 != nullptr )
    {
      sub_42AF90(v35);
      sub_657740(v35, 228);
    }
    v30[5] = nullptr;
    ++v30;
    result = v41 - 1;
    v41 = result;
  }
  while ( result != 0 );
  v37 = *(uint32_t *)(v21 + 9432);
  if ( v37 != 0 )
  {
    sub_42AF90(*(void ***)(v21 + 9432));
    result = sub_657740(v37, 228);
  }
  v38 = *(int (/*thiscall*/ ****)(uint32_t, int))(v21 + 9516);
  *(uint32_t *)(v21 + 9432) = 0;
  if ( v38 != nullptr )
    result = (**v38)(v38, 1);
  *(uint32_t *)(v21 + 9516) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x4C46B0 sub_4C46B0
// ------------------------------------------------------------
// 证: "Character/Gunner/Effect/Animation/ShootEffec" | "Down" | "Jump" | "Tread"
// 调: sub_4C46B0 sub_4015C0 sub_4022F0 sub_402410 sub_501490
int /*thiscall*/ sub_4C46B0(void *this, int a2)
{
  int v3; // edi
  void **v4; // ecx
  int v5; // esi
  int i; // edi
  int v7; // eax
  int v8; // eax
  int v10; // [esp+Ch] [ebp-30h]
  uint8_t v11[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+14h] [ebp-28h] BYREF
  unsigned int v13; // [esp+28h] [ebp-14h]
  int v14; // [esp+2Ch] [ebp-10h]
  int v15; // [esp+38h] [ebp-4h]

  v14 = dword_796E50;
  v13 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/ShootEffect/", 0x2Eu);
  v15 = 0;
  if ( a2 != 0 )
  {
    switch ( a2 )
    {
      case 1:
        sub_4022F0((std::_String_base *)v11, "Down", 4);
        break;
      case 2:
        sub_4022F0((std::_String_base *)v11, "Jump", 4);
        break;
      case 3:
        sub_402410("Tread");
        break;
      default:
        sub_501490(v11);
        return 0;
    }
  }
  else
  {
    sub_4022F0((std::_String_base *)v11, "Up", 2);
  }
  switch ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1096))(this) )
  {
    case 0:
      if ( a2 != 3 )
        goto LABEL_14;
      sub_402410("Revolver.ani");
      break;
    case 1:
      if ( a2 == 3 )
        sub_402410("Automatic.ani");
      else
LABEL_14:
        sub_402410("Pistol.ani");
      break;
    case 2:
      sub_4022F0((std::_String_base *)v11, "Musket.ani", 10);
      break;
    case 3:
      sub_4022F0((std::_String_base *)v11, "HandCannon.ani", 14);
      break;
    case 4:
      sub_4022F0((std::_String_base *)v11, "BowGun.ani", 10);
      break;
    default:
      break;
  }
  v3 = sub_4C1000(this);
  v10 = sub_42FCB0(228);
  LOBYTE(v15) = 1;
  if ( v10 != 0 )
  {
    LOBYTE(v4) = Block[0];
    if ( v13 < 0x10 )
      v4 = Block;
    v5 = sub_4C4150(0, v3, (char)v4, 1);
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v15) = 0;
  if ( v3 == 1 )
  {
    for ( i = 0; ; ++i )
    {
      v7 = *(uint32_t *)(v5 + 44);
      v8 = v7 != 0 ? (*(uint32_t *)(v5 + 48) - v7) / 88 : 0;
      if ( i >= v8 )
        break;
      *(uint32_t *)(sub_4924C0(i) + 40) = 2;
    }
  }
  if ( v13 >= 0x10 )
    j__free(Block[0]);
  return v5;
}



// ------------------------------------------------------------
// 0x4C4890 sub_4C4890
// ------------------------------------------------------------
// 证: "Effect/Animation/SubWeapon/SubWeaponFrontOnc" | "Effect/Animation/SubWeapon/SubWeaponFrontRap" |
//  "Effect/Animation/SubWeapon/SubWeaponUpOnce1a" | "Effect/Animation/SubWeapon/SubWeaponUpOnce1b"
// 调: sub_4C4890 sub_4015C0 sub_406D60 sub_42FCB0 sub_4319E0
int /*thiscall*/ sub_4C4890(uint32_t *this, int a2, int a3)
{
  int v4; // edi
  int v5; // edx
  int v6; // eax
  void **p_Block; // edx
  int v8; // ecx
  int v9; // eax
  int result; // eax
  int v11; // [esp+Ch] [ebp-4Ch]
  void *v12; // [esp+14h] [ebp-44h] BYREF
  int v13; // [esp+24h] [ebp-34h]
  unsigned int v14; // [esp+28h] [ebp-30h]
  void *Block; // [esp+30h] [ebp-28h] BYREF
  int v16; // [esp+40h] [ebp-18h]
  unsigned int v17; // [esp+44h] [ebp-14h]
  int v18; // [esp+48h] [ebp-10h]
  int v19; // [esp+54h] [ebp-4h]

  v18 = dword_796E50;
  v4 = a3 + 8 * a2;
  if ( *(this + 2 * v4 + 2213) == 0 )
  {
    v14 = 15;
    v13 = 0;
    LOBYTE(v12) = 0;
    v19 = 1;
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    switch ( a3 )
    {
      case 15:
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce1a.ani", 0x33u);
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce1b.ani", 0x33u);
        break;
      case 16:
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce2a.ani", 0x33u);
        sub_4015C0("Effect/Animation/SubWeapon/SubWeaponFrontOnce2b.ani", 0x33u);
        break;
      case 17:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid1a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid1b.ani");
        break;
      case 18:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid2a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponFrontRapid2b.ani");
        break;
      case 19:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce1a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce1b.ani");
        break;
      case 20:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce2a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpOnce2b.ani");
        break;
      case 21:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid1a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid1b.ani");
        break;
      case 22:
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid2a.ani");
        sub_406D60("Effect/Animation/SubWeapon/SubWeaponUpRapid2b.ani");
        break;
      default:
        break;
    }
    LOBYTE(v19) = 2;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( *(this + 96) < 0x10u )
        LOBYTE(v5) = (uint8_t)this + 108;
      else
        v5 = *(this + 91);
      v6 = sub_4319E0(a2, 0, v5, (char)&v12, 1);
    }
    else
    {
      v6 = 0;
    }
    LOBYTE(v19) = 1;
    *(this + 2 * v4 + 2213) = v6;
    v11 = sub_42FCB0(228);
    LOBYTE(v19) = 3;
    if ( v11 != 0 )
    {
      LOBYTE(p_Block) = (uint8_t)Block;
      if ( v17 < 0x10 )
        p_Block = &Block;
      if ( *(this + 96) < 0x10u )
        LOBYTE(v8) = (uint8_t)this + 108;
      else
        v8 = *(this + 91);
      v9 = sub_4319E0(a2, 0, v8, (char)p_Block, 1);
    }
    else
    {
      v9 = 0;
    }
    *(this + 2 * v4 + 2214) = v9;
    if ( v17 >= 0x10 )
      j__free(Block);
    v17 = 15;
    v16 = 0;
    LOBYTE(Block) = 0;
    v19 = -1;
    if ( v14 >= 0x10 )
      j__free(v12);
    v14 = 15;
    v13 = 0;
    LOBYTE(v12) = 0;
  }
  sub_494240(2151, *(this + 2 * v4 + 2213));
  sub_494240(651, *(this + 2 * v4 + 2214));
  result = *(this + 2 * v4 + 2213);
  *(this + 2323) = result;
  *(this + 2324) = *(this + 2 * v4 + 2214);
  return result;
}


// ------------------------------------------------------------
// 0x4C4B40 sub_4C4B40
// ------------------------------------------------------------
// 证: "Etc/GunnerDefaultGunInfo.etc"
// 调: sub_4C4B40 sub_442A10 sub_41BFE0 sub_42CC00 sub_4B4950
void sub_4C4B40()
{
  int v0; // ecx
  const char *p_Block; // esi
  int v2; // eax
  unsigned int v3; // esi
  int v4; // ebx
  uint32_t *v5; // esi
  int v6; // eax
  int v7; // esi
  char *v8; // ecx
  unsigned int v9; // edi
  int *v10; // edx
  int v11; // ebx
  char *v12; // esi
  int v13; // ecx
  unsigned int v14; // edx
  int v15; // edi
  char v16[8]; // [esp-10h] [ebp-58h] BYREF
  char *v17; // [esp-8h] [ebp-50h]
  void **i; // [esp-4h] [ebp-4Ch]
  unsigned int v19; // [esp+Ch] [ebp-3Ch]
  void *v20; // [esp+10h] [ebp-38h] BYREF
  int j; // [esp+14h] [ebp-34h] BYREF
  char v22; // [esp+1Bh] [ebp-2Dh] BYREF
  uint8_t v23[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+20h] [ebp-28h] BYREF
  unsigned int v25; // [esp+30h] [ebp-18h]
  unsigned int v26; // [esp+34h] [ebp-14h]
  int v27; // [esp+38h] [ebp-10h]
  int v28; // [esp+44h] [ebp-4h]

  v27 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/GunnerDefaultGunInfo.etc") != 0 )
  {
    v26 = 15;
    v25 = 0;
    LOBYTE(Block) = 0;
    v28 = 0;
    v20 = nullptr;
    sub_41BFE0(&v20, szPassword);
    LOBYTE(v28) = 1;
    v22 = 0;
    if ( dword_9A05AC != nullptr )
    {
      i = (void **)j;
      v17 = (char *)&unk_9A05A8;
      sub_42CC00(dword_9A05AC, dword_9A05B0);
      j__free(dword_9A05AC);
    }
    dword_9A05AC = nullptr;
    dword_9A05B0 = 0;
    dword_9A05B4 = 0;
    if ( dword_9A05BC != nullptr )
    {
      i = (void **)j;
      v17 = (char *)&unk_9A05B8;
      sub_4B4950(dword_9A05BC, dword_9A05C0);
      j__free(dword_9A05BC);
    }
    dword_9A05BC = nullptr;
    dword_9A05C0 = 0;
    dword_9A05C4 = 0;
    v19 = 0;
    if ( (uint8_t)sub_443430(v23) != 0 )
    {
      while ( 1 )
      {
        sub_442B20(v23);
        if ( v25 == 0 )
          goto LABEL_22;
        v0 = v25;
        if ( v25 >= 0xA )
          v0 = 10;
        p_Block = (const char *)Block;
        if ( v26 < 0x10 )
          p_Block = (const char *)&Block;
        v2 = memcmp(p_Block, "[sub type]", v0);
        if ( v2 != 0 || v25 < 0xA || (LOBYTE(v2) = v25 != 10, v2 != 0) )
        {
LABEL_22:
          if ( sub_40BF00((std::_String_base *)v23, 0, v25, "[integer]", 9u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v23, 0, v25, "[string]", 8u) == 0 )
            {
              v11 = 16 * v19;
              sub_4017E0((char *)dword_9A05BC + 16 * v19);
              for ( i = &v20; sub_442E10() != 0; i = &v20 )
              {
                v12 = (char *)dword_9A05BC + v11;
                v13 = *(uint32_t *)((char *)dword_9A05BC + v11 + 4);
                if ( v13 != 0 )
                  v14 = (*((uint32_t *)v12 + 2) - v13) >> 2;
                else
                  v14 = 0;
                if ( v13 != 0 && v14 < (*((uint32_t *)v12 + 3) - v13) >> 2 )
                {
                  v15 = *((uint32_t *)v12 + 2);
                  i = (void **)j;
                  v17 = (char *)dword_9A05BC + v11;
                  sub_41FFE0(v15, 1, &v20);
                  *((uint32_t *)v12 + 2) = v15 + 4;
                }
                else
                {
                  sub_4206D0(*((uint32_t *)v12 + 2), 1, &v20);
                }
              }
            }
          }
          else
          {
            v4 = 16 * v19;
            v5 = (char *)dword_9A05AC + 16 * v19;
            if ( v5[1] != 0 )
              j__free(*((void **)dword_9A05AC + 4 * v19 + 1));
            i = (void **)&v22;
            v5[1] = 0;
            v5[2] = 0;
            v5[3] = 0;
            v6 = sub_4423D0(i);
            for ( j = v6; v22 != 0; j = v6 )
            {
              v7 = *(uint32_t *)((char *)dword_9A05AC + v4 + 4);
              v8 = (char *)dword_9A05AC + v4;
              if ( v7 != 0 )
                v9 = (*((uint32_t *)v8 + 2) - v7) >> 2;
              else
                v9 = 0;
              if ( v7 != 0 && v9 < (*((uint32_t *)v8 + 3) - v7) >> 2 )
              {
                v10 = *((int **)v8 + 2);
                *v10 = v6;
                *((uint32_t *)v8 + 2) = v10 + 1;
              }
              else
              {
                sub_430C80(*((void **)v8 + 2), 1, (int)&j);
              }
              v6 = sub_4423D0(&v22);
            }
          }
          goto LABEL_45;
        }
        v3 = sub_4423D0(nullptr);
        v19 = v3;
        if ( dword_9A05AC == nullptr || (dword_9A05B0 - (int)dword_9A05AC) >> 4 <= v3 )
        {
          j = (int)v16;
          sub_489720(v3 + 1, v16[0], nullptr, 0, 0);
        }
        if ( dword_9A05BC == nullptr )
          goto LABEL_21;
        if ( (dword_9A05C0 - (int)dword_9A05BC) >> 4 <= v3 )
          break;
LABEL_45:
        if ( (uint8_t)sub_443430(v23) == 0 )
          goto LABEL_46;
      }
      v3 = v19;
LABEL_21:
      j = (int)v16;
      sub_4C4080(v3 + 1, v16[0], nullptr, 0, 0);
      goto LABEL_45;
    }
LABEL_46:
    LOBYTE(v28) = 0;
    sub_41B010(&v20);
    if ( v26 >= 0x10 )
      j__free(Block);
  }
}


// ------------------------------------------------------------
// 0x4C4EF0 sub_4C4EF0
// ------------------------------------------------------------
// 证: "Character/Gunner/Effect/Animation/MechanicSt" | "Character/Gunner/Effect/Animation/MechanicFr"
// 调: sub_4C4EF0 sub_42FCB0 sub_431860 sub_4053E0 sub_4938F0
int /*cdecl*/ sub_4C4EF0(int a1, int a2, int a3, char a4, int a5)
{
  int result; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  DWORD Time; // eax
  int v11; // edi
  int v12; // eax
  BOOL v13; // esi
  int *v14; // esi
  int v15; // eax
  int i; // [esp+0h] [ebp-18h]
  int v17; // [esp+4h] [ebp-14h]
  float v18; // [esp+8h] [ebp-10h]

  result = a5;
  if ( a5 != 0
    && (a4 == 0
     || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) == 0
     || *(uint8_t *)((result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1)) + 161) != 0) )
  {
    if ( dword_9A0598 == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v6 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicStay1.ani", 1);
      else
        v6 = 0;
      dword_9A0598 = v6;
      if ( sub_42FCB0(228) != 0 )
        v7 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicStay2.ani", 1);
      else
        v7 = 0;
      dword_9A059C = v7;
      if ( sub_42FCB0(228) != 0 )
        v8 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicFront1.ani", 1);
      else
        v8 = 0;
      dword_9A05A0 = v8;
      if ( sub_42FCB0(228) != 0 )
        v9 = sub_431860((char)"Character/Gunner/Effect/Animation/MechanicFront2.ani", 1);
      else
        v9 = 0;
      dword_9A05A4 = v9;
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != 0 )
      v17 = a2 - 40;
    else
      v17 = a2 + 40;
    Time = timeGetTime();
    v11 = 150 - (uint64_t)(sub_4053E0(Time / 5 % 0x168) * -10.0);
    LOBYTE(v18) = 0;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 184))(a1);
    v13 = v12 != 4;
    if ( v12 == 0 || v12 == 4 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) == 0 )
      LOBYTE(v18) = 1;
    v14 = (int *)(8 * v13 + 10093976);
    for ( i = 2; i != 0; --i )
    {
      sub_4938F0(*v14);
      sub_491F80(*v14, -1, -1, -1, a5, 1);
      if ( a4 != 0 )
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
        sub_491EA0(*v14, dword_79C0B0, v17, a3, v18, v11 + v15, 0.40000001, 0.30000001, 100);
      }
      else
      {
        sub_491D00(*v14, dword_79C0B0, v17, a3 - v11, v18);
      }
      ++v14;
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// ============================================================
// §B 大状态 tick 区(含 0x4C5250)
// ============================================================
// 0x4C5160 sub_4C5160
// ------------------------------------------------------------
// 调: sub_4C5160 sub_4938F0 sub_4C4EF0 sub_4B1E50
uint32_t */*thiscall*/ sub_4C5160(int *this, int a2, int a3, int a4, uint32_t *a5)
{
  int v6; // edi

  if ( (uint8_t)a2 != 0 && *(this + 1788) == 3 )
  {
    v6 = *(this + 30);
    if ( v6 != 0 )
    {
      if ( *(uint32_t *)(v6 + 148) == -1 )
        sub_4938F0(*(this + 30));
      sub_4C4EF0((int)this, a3, a4, 0, *(uint8_t *)(v6 + 95));
    }
  }
  return sub_4B1E50(this, a4, a2, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x4C51D0 sub_4C51D0
// ------------------------------------------------------------
// 调: sub_4C51D0 sub_4938F0 sub_4C4EF0 sub_4AF4B0
char /*thiscall*/ sub_4C51D0(int *this, int a2, int a3, int a4, int a5)
{
  int v6; // edi

  if ( (uint8_t)a2 != 0 && *(this + 1788) == 3 )
  {
    v6 = *(this + 30);
    if ( v6 != 0 )
    {
      if ( *(uint32_t *)(v6 + 148) == -1 )
        sub_4938F0(*(this + 30));
      sub_4C4EF0((int)this, a3, a4, 1, *(uint8_t *)(v6 + 95));
    }
  }
  return sub_4AF4B0(this, a2, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x4C5240 sub_4C5240
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_4C5240 sub_4C4B40
void sub_4C5240(void)
{
  sub_4C4B40();
}



// ------------------------------------------------------------
// ============================================================
// §C 弹尘与特效
// ============================================================
// 0x4CE550 sub_4CE550
// ------------------------------------------------------------
// 调: sub_4CE550
int /*thiscall*/ sub_4CE550(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *((uint16_t *)this + 4) = 0;
  *((uint16_t *)this + 5) = 0;
  *((uint16_t *)this + 6) = 0;
  *((uint16_t *)this + 7) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *((uint16_t *)this + 30) = 0;
  *((uint16_t *)this + 31) = 0;
  *((uint16_t *)this + 32) = 0;
  *((uint16_t *)this + 33) = 0;
  *((uint16_t *)this + 34) = 0;
  *((uint16_t *)this + 35) = 0;
  *((uint16_t *)this + 36) = 0;
  *(uint32_t *)((char *)this + 74) = 0;
  *((uint8_t *)this + 78) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4CE5B0 sub_4CE5B0
// ------------------------------------------------------------
// 调: sub_4CE5B0
int /*cdecl*/ sub_4CE5B0(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 69) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4CE5D0 sub_4CE5D0
// ------------------------------------------------------------
// 调: sub_4CE5D0
uint32_t */*cdecl*/ sub_4CE5D0(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 69) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 69) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE5F0 sub_4CE5F0
// ------------------------------------------------------------
// 调: sub_4CE5F0
int */*thiscall*/ sub_4CE5F0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 69) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 69) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 69) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 69) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 69) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE650 sub_4CE650
// ------------------------------------------------------------
// 调: sub_4CE650
uint32_t */*thiscall*/ sub_4CE650(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 69) == 0 )
    *(uint32_t *)(*result + 4) = a2;
  result[1] = *(uint32_t *)(a2 + 4);
  v3 = *(this + 1);
  if ( a2 == *(uint32_t *)(v3 + 4) )
  {
    *(uint32_t *)(v3 + 4) = result;
    *result = a2;
    *(uint32_t *)(a2 + 4) = result;
  }
  else
  {
    v4 = *(uint32_t **)(a2 + 4);
    if ( a2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = a2;
    *(uint32_t *)(a2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE6B0 sub_4CE6B0
// ------------------------------------------------------------
// 调: sub_4CE6B0
int /*thiscall*/ sub_4CE6B0(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 69) == 0 )
    *(uint32_t *)(v3 + 4) = a2;
  *(uint32_t *)(result + 4) = a2[1];
  v4 = *(this + 1);
  if ( a2 == *(uint32_t **)(v4 + 4) )
  {
    *(uint32_t *)(v4 + 4) = result;
    *(uint32_t *)(result + 8) = a2;
    a2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)a2[1];
    if ( a2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = a2;
    a2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE710 sub_4CE710
// ------------------------------------------------------------
// 调: sub_4CE710
uint32_t *sub_4CE710()
{
  uint32_t *result; // eax

  result = operator new(0x34u);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE730 sub_4CE730
// ------------------------------------------------------------
// 调: sub_4CE730
uint32_t *sub_4CE730()
{
  uint32_t *result; // eax

  result = operator new(0x18u);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE750 sub_4CE750
// ------------------------------------------------------------
// 调: sub_4CE750
uint32_t *sub_4CE750()
{
  uint32_t *result; // eax

  result = operator new(0x3Cu);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE770 sub_4CE770
// ------------------------------------------------------------
// 调: sub_4CE770
uint32_t *sub_4CE770()
{
  uint32_t *result; // eax

  result = operator new(0x28u);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4CE790 sub_4CE790
// ------------------------------------------------------------
// 调: sub_4CE790
uint32_t *sub_4CE790()
{
  uint32_t *result; // eax

  result = operator new(0x48u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 68) = 1;
  *((uint8_t *)result + 69) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4CE7D0 sub_4CE7D0
// ------------------------------------------------------------
// 调: sub_4CE7D0
void /*thiscall*/ sub_4CE7D0(int this)
{
  if ( *(uint32_t *)(this + 40) != 0 )
    j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CE820 sub_4CE820
// ------------------------------------------------------------
// 调: sub_4CE820
void /*thiscall*/ sub_4CE820(int this)
{
  if ( *(uint32_t *)(this + 44) != 0 )
    j__free(*(void **)(this + 44));
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
}



// ------------------------------------------------------------
// 0x4CE850 sub_4CE850
// ------------------------------------------------------------
// 调: sub_4CE850
void /*thiscall*/ sub_4CE850(int this)
{
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  if ( *(uint32_t *)(this + 40) >= 0x10u )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 15;
  *(uint8_t *)(this + 20) = 0;
}



// ------------------------------------------------------------
// 0x4CE8A0 sub_4CE8A0
// ------------------------------------------------------------
// 调: sub_4CE8A0 sub_442D00
int /*thiscall*/ sub_4CE8A0(uint32_t *this, int a2)
{
  uint32_t *v3; // esi
  int v4; // eax
  int result; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  switch ( *(this + 72) )
  {
    case 0:
      v3 = &unk_9B7C3C;
      goto LABEL_14;
    case 1:
      v3 = &unk_9B7C30;
      goto LABEL_14;
    case 2:
      v3 = &unk_9B7C48;
      goto LABEL_14;
    case 3:
      v3 = &unk_9B7C70;
      goto LABEL_14;
    case 4:
      v3 = &unk_9B6C6C;
      goto LABEL_14;
    case 5:
      v3 = &unk_9B6C60;
      goto LABEL_14;
    case 7:
      v3 = &unk_9B7408;
      goto LABEL_14;
    case 0xA:
      v3 = &unk_9B71B8;
      goto LABEL_14;
    case 0xB:
      v3 = &unk_9B70A8;
      goto LABEL_14;
    case 0xC:
      v3 = &unk_9B6D78;
      goto LABEL_14;
    case 0xD:
      v3 = &unk_9B6E88;
      goto LABEL_14;
    case 0xE:
      v3 = &unk_9B7C54;
LABEL_14:
      sub_442D00(&v6, &a2);
      if ( v6 == v3[1] )
        goto LABEL_20;
      v4 = *(uint32_t *)(v6 + 40) < 0x10u ? v6 + 20 : *(uint32_t *)(v6 + 20);
      if ( v4 == 0 )
        goto LABEL_20;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 4))(this, v4);
      break;
    default:
LABEL_20:
      result = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CE9A0 sub_4CE9A0
// ------------------------------------------------------------
// 调: sub_4CE9A0
void /*thiscall*/ sub_4CE9A0(int this)
{
  if ( *(uint32_t *)(this + 44) != 0 )
    j__free(*(void **)(this + 44));
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  if ( *(uint32_t *)(this + 32) >= 0x10u )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 15;
  *(uint8_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x4CE9F0 sub_4CE9F0
// ------------------------------------------------------------
// 调: sub_4CE9F0 sub_406D00
uint32_t */*thiscall*/ sub_4CE9F0(uint32_t *this)
{
  uint8_t *v2; // ecx
  unsigned int v3; // edx
  uint8_t *v4; // edi
  void *v6[5]; // [esp+8h] [ebp-14h] BYREF

  v2 = this + 1;
  *(this + 6) = 15;
  *(this + 5) = 0;
  v6[1] = this;
  *v2 = 0;
  v3 = *(this + 6);
  v6[4] = nullptr;
  if ( v3 < 0x10 )
    v4 = v2;
  else
    v4 = *(uint8_t **)v2;
  if ( v3 >= 0x10 )
    v2 = *(uint8_t **)v2;
  sub_406D00(this, v6, (int)v2, (unsigned int)&v4[*(this + 5)]);
  return this;
}



// ------------------------------------------------------------
// 0x4CEA60 sub_4CEA60
// ------------------------------------------------------------
// 调: sub_4CEA60
void /*thiscall*/ sub_4CEA60(int this)
{
  if ( *(uint32_t *)(this + 56) != 0 )
    j__free(*(void **)(this + 56));
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  if ( *(uint32_t *)(this + 44) >= 0x10u )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 15;
  *(uint8_t *)(this + 24) = 0;
}



// ------------------------------------------------------------
// 0x4CEAB0 sub_4CEAB0
// ------------------------------------------------------------
// 调: sub_4CEAB0 sub_4015C0 sub_401740
void /*noreturn*/ sub_4CEAB0()
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4CEB20 sub_4CEB20
// ------------------------------------------------------------
// 调: sub_4CEB20
void /*thiscall*/ sub_4CEB20(int this)
{
  if ( *(uint32_t *)(this + 40) != 0 )
    j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
}



// ------------------------------------------------------------
// 0x4CEB50 sub_4CEB50
// ------------------------------------------------------------
// 调: sub_4CEB50
void /*thiscall*/ sub_4CEB50(int this)
{
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
}



// ------------------------------------------------------------
// 0x4CEB80 sub_4CEB80
// ------------------------------------------------------------
// 调: sub_4CEB80 sub_4015C0
void /*thiscall*/ sub_4CEB80(char *this)
{
  char *v2; // edi
  uint32_t *v3; // edx
  uint32_t *v4; // eax
  uint32_t *v5; // ecx
  int k; // edi
  uint32_t *v7; // ecx
  int m; // edi
  char *v9; // edi
  void **v10; // edi
  void **v11; // edi
  void **v12; // edi
  void **v13; // edi
  char *v14; // eax
  void **v15; // edi
  void **v16; // [esp+8h] [ebp-Ch]
  void **ii; // [esp+Ch] [ebp-8h]
  void **jj; // [esp+Ch] [ebp-8h]
  void **kk; // [esp+Ch] [ebp-8h]
  void **mm; // [esp+Ch] [ebp-8h]
  int nn; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]
  int n; // [esp+10h] [ebp-4h]
  char *v25; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 1;
  if ( *((uint32_t *)this + 13) != 0 )
    j__free(*((void **)this + 13));
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  v2 = this + 68;
  for ( i = 4; i != 0; --i )
  {
    if ( *(uint32_t *)v2 != 0 )
      j__free(*(void **)v2);
    *(uint32_t *)v2 = 0;
    *((uint32_t *)v2 + 1) = 0;
    *((uint32_t *)v2 + 2) = 0;
    v2 += 16;
  }
  if ( *((uint32_t *)this + 33) != 0 )
    j__free(*((void **)this + 33));
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 0;
  v3 = this + 432;
  v4 = this + 228;
  for ( j = 2; j != 0; --j )
  {
    v5 = v4 - 8;
    for ( k = 4; k != 0; --k )
    {
      *v5 = 0;
      v5 += 2;
    }
    v7 = v4;
    for ( m = 16; m != 0; --m )
    {
      *v7 = 0;
      v7 += 2;
    }
    v4[32] = 0;
    v4[34] = 0;
    v4[36] = 0;
    v4[38] = 0;
    v4[40] = 0;
    v4[42] = 0;
    v4[44] = 0;
    v4[46] = 100;
    v4[48] = 0;
    *(v3 - 1) = 0;
    *v3 = 0;
    ++v4;
    v3 += 2;
  }
  *((uint32_t *)this + 111) = 200;
  *((uint32_t *)this + 112) = 1000;
  *(this + 452) = 0;
  *(this + 453) = 0;
  *((uint32_t *)this + 114) = 0;
  *((uint32_t *)this + 115) = 0;
  *((uint32_t *)this + 116) = 0;
  *(this + 468) = 0;
  *(this + 469) = 0;
  *(this + 470) = 0;
  *((uint32_t *)this + 118) = 0;
  *((uint32_t *)this + 119) = 0;
  *((uint32_t *)this + 120) = 0;
  *((uint32_t *)this + 121) = 0;
  *(this + 488) = 0;
  *((uint32_t *)this + 123) = 50;
  *((uint32_t *)this + 124) = 1000;
  *(this + 500) = 0;
  *((uint32_t *)this + 126) = 0;
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 134) = 0;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  v9 = this + 624;
  for ( n = 2; n != 0; --n )
  {
    sub_4015C0((void *)szPassword, 0);
    v9 += 28;
  }
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  v10 = *((void ***)this + 199);
  if ( v10 != nullptr )
  {
    for ( ii = *((void ***)this + 200); v10 != ii; ++v10 )
      sub_41B010(v10);
    j__free(*((void **)this + 199));
  }
  *((uint32_t *)this + 199) = 0;
  *((uint32_t *)this + 200) = 0;
  *((uint32_t *)this + 201) = 0;
  v11 = *((void ***)this + 203);
  if ( v11 != nullptr )
  {
    for ( jj = *((void ***)this + 204); v11 != jj; ++v11 )
      sub_41B010(v11);
    j__free(*((void **)this + 203));
  }
  *((uint32_t *)this + 203) = 0;
  *((uint32_t *)this + 204) = 0;
  *((uint32_t *)this + 205) = 0;
  sub_4015C0((void *)szPassword, 0);
  v12 = *((void ***)this + 214);
  if ( v12 != nullptr )
  {
    for ( kk = *((void ***)this + 215); v12 != kk; ++v12 )
      sub_41B010(v12);
    j__free(*((void **)this + 214));
  }
  *((uint32_t *)this + 214) = 0;
  *((uint32_t *)this + 215) = 0;
  *((uint32_t *)this + 216) = 0;
  v13 = *((void ***)this + 218);
  if ( v13 != nullptr )
  {
    for ( mm = *((void ***)this + 219); v13 != mm; ++v13 )
      sub_41B010(v13);
    j__free(*((void **)this + 218));
  }
  *((uint32_t *)this + 218) = 0;
  *((uint32_t *)this + 219) = 0;
  *((uint32_t *)this + 220) = 0;
  if ( *((uint32_t *)this + 222) != 0 )
    j__free(*((void **)this + 222));
  *((uint32_t *)this + 222) = 0;
  *((uint32_t *)this + 223) = 0;
  *((uint32_t *)this + 224) = 0;
  if ( *((uint32_t *)this + 226) != 0 )
    j__free(*((void **)this + 226));
  *((uint32_t *)this + 226) = 0;
  *((uint32_t *)this + 227) = 0;
  *((uint32_t *)this + 228) = 0;
  *((uint32_t *)this + 229) = -1;
  *((uint32_t *)this + 230) = 0;
  *((uint32_t *)this + 231) = 0;
  sub_4015C0((void *)szPassword, 0);
  v14 = this + 960;
  v25 = this + 960;
  for ( nn = 29; nn != 0; --nn )
  {
    v15 = *(void ***)v14;
    if ( *(uint32_t *)v14 != 0 )
    {
      v16 = *((void ***)v14 + 1);
      if ( v15 != v16 )
      {
        do
          sub_41B010(v15++);
        while ( v15 != v16 );
        v14 = v25;
      }
      j__free(*(void **)v14);
      v14 = v25;
    }
    *(uint32_t *)v14 = 0;
    *((uint32_t *)v14 + 1) = 0;
    *((uint32_t *)v14 + 2) = 0;
    v14 += 16;
    v25 = v14;
  }
  if ( *((uint32_t *)this + 356) != 0 )
    j__free(*((void **)this + 356));
  *((uint32_t *)this + 356) = 0;
  *((uint32_t *)this + 357) = 0;
  *((uint32_t *)this + 358) = 0;
  *((uint32_t *)this + 359) = 0;
}


// ------------------------------------------------------------
// 0x4CF050 sub_4CF050
// ------------------------------------------------------------
// 调: sub_4CF050 sub_4015C0 sub_4017E0
size_t */*thiscall*/ sub_4CF050(void *this)
{
  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)this + 1, szPassword, 0);
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 1;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  if ( *((uint32_t *)this + 15) != 0 )
    j__free(*((void **)this + 15));
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  sub_4015C0((size_t *)this + 18, szPassword, 0);
  sub_4017E0((int)this + 100);
  sub_4015C0((size_t *)this + 29, szPassword, 0);
  sub_4015C0((size_t *)this + 36, szPassword, 0);
  sub_4017E0((int)this + 172);
  if ( *((uint32_t *)this + 48) != 0 )
    j__free(*((void **)this + 48));
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 0;
  *((uint32_t *)this + 50) = 0;
  sub_4017E0((int)this + 204);
  return sub_4015C0((size_t *)this + 55, szPassword, 0);
}



// ------------------------------------------------------------
// 0x4CF120 sub_4CF120
// ------------------------------------------------------------
// 调: sub_4CF120 sub_4015C0 sub_41B010
size_t */*thiscall*/ sub_4CF120(char *this)
{
  uint32_t *v2; // eax
  int i; // ecx
  void **v4; // edi
  void **v5; // edi
  void **v6; // edi
  void **j; // [esp+Ch] [ebp-4h]
  void **k; // [esp+Ch] [ebp-4h]
  void **m; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)this + 1, szPassword, 0);
  *((uint32_t *)this + 11) = 1;
  *(this + 52) = 1;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 12) = 0;
  v2 = this + 64;
  for ( i = 2; i != 0; --i )
  {
    *(v2 - 2) = 0;
    *v2++ = 0;
  }
  *((uint32_t *)this + 18) = 0;
  sub_4015C0((size_t *)this + 20, szPassword, 0);
  v4 = *((void ***)this + 28);
  if ( v4 != nullptr )
  {
    for ( j = *((void ***)this + 29); v4 != j; ++v4 )
      sub_41B010(v4);
    j__free(*((void **)this + 28));
  }
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 30) = 0;
  v5 = *((void ***)this + 32);
  if ( v5 != nullptr )
  {
    for ( k = *((void ***)this + 33); v5 != k; ++v5 )
      sub_41B010(v5);
    j__free(*((void **)this + 32));
  }
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  if ( *((uint32_t *)this + 36) != 0 )
    j__free(*((void **)this + 36));
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  v6 = *((void ***)this + 40);
  if ( v6 != nullptr )
  {
    for ( m = *((void ***)this + 41); v6 != m; ++v6 )
      sub_41B010(v6);
    j__free(*((void **)this + 40));
  }
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  return sub_4015C0((size_t *)this + 43, szPassword, 0);
}



// ------------------------------------------------------------
// 0x4CF290 sub_4CF290
// ------------------------------------------------------------
// 调: sub_4CF290 sub_4015C0 sub_41B010
size_t */*thiscall*/ sub_4CF290(char *this)
{
  uint32_t *v2; // eax
  int i; // ecx
  void **v4; // edi
  void **v5; // edi
  void **v6; // edi
  void **j; // [esp+Ch] [ebp-4h]
  void **k; // [esp+Ch] [ebp-4h]
  void **m; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)this + 1, szPassword, 0);
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 1;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *(this + 56) = 1;
  v2 = this + 68;
  for ( i = 2; i != 0; --i )
  {
    *(v2 - 2) = 0;
    *v2++ = 0;
  }
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 1500;
  *((uint32_t *)this + 21) = 1;
  *((uint32_t *)this + 22) = 1;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 1;
  sub_4015C0((size_t *)this + 25, szPassword, 0);
  sub_4015C0((size_t *)this + 32, szPassword, 0);
  sub_4015C0((size_t *)this + 39, szPassword, 0);
  sub_4015C0((size_t *)this + 46, szPassword, 0);
  sub_4015C0((size_t *)this + 53, szPassword, 0);
  sub_4015C0((size_t *)this + 60, szPassword, 0);
  v4 = *((void ***)this + 68);
  if ( v4 != nullptr )
  {
    for ( j = *((void ***)this + 69); v4 != j; ++v4 )
      sub_41B010(v4);
    j__free(*((void **)this + 68));
  }
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  v5 = *((void ***)this + 72);
  if ( v5 != nullptr )
  {
    for ( k = *((void ***)this + 73); v5 != k; ++v5 )
      sub_41B010(v5);
    j__free(*((void **)this + 72));
  }
  *((uint32_t *)this + 72) = 0;
  *((uint32_t *)this + 73) = 0;
  *((uint32_t *)this + 74) = 0;
  if ( *((uint32_t *)this + 76) != 0 )
    j__free(*((void **)this + 76));
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  v6 = *((void ***)this + 80);
  if ( v6 != nullptr )
  {
    for ( m = *((void ***)this + 81); v6 != m; ++v6 )
      sub_41B010(v6);
    j__free(*((void **)this + 80));
  }
  *((uint32_t *)this + 80) = 0;
  *((uint32_t *)this + 81) = 0;
  *((uint32_t *)this + 82) = 0;
  return sub_4015C0((size_t *)this + 83, szPassword, 0);
}



// ------------------------------------------------------------
// 0x4CF480 sub_4CF480
// ------------------------------------------------------------
// 调: sub_4CF480 sub_41BFE0 sub_41B010
void /*thiscall*/ sub_4CF480(void *this)
{
  void **v2; // eax
  void **v3; // edi
  void **v4; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_41BFE0((void **)this + 1, szPassword);
  sub_41BFE0((void **)this + 2, szPassword);
  sub_41BFE0((void **)this + 3, szPassword);
  sub_41BFE0((void **)this + 4, szPassword);
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = -1;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = -1;
  *((uint8_t *)this + 76) = 0;
  sub_41BFE0((void **)this + 20, szPassword);
  *((uint32_t *)this + 21) = 0;
  sub_41BFE0((void **)this + 22, szPassword);
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 8;
  sub_41BFE0((void **)this + 26, szPassword);
  sub_41BFE0((void **)this + 29, szPassword);
  if ( *((uint32_t *)this + 31) != 0 )
    j__free(*((void **)this + 31));
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 0;
  v2 = *((void ***)this + 35);
  if ( v2 != nullptr )
  {
    v3 = *((void ***)this + 35);
    v4 = *((void ***)this + 36);
    if ( v2 != v4 )
    {
      do
        sub_41B010(v3++);
      while ( v3 != v4 );
    }
    j__free(*((void **)this + 35));
  }
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 40) = -1;
  *((uint8_t *)this + 152) = 0;
  *((uint32_t *)this + 39) = 0;
}



// ------------------------------------------------------------
// 0x4CF5C0 sub_4CF5C0
// ------------------------------------------------------------
// 调: sub_4CF5C0 sub_401940 sub_4017E0 sub_501490 sub_5E5260
void /*thiscall*/ sub_4CF5C0(int this)
{
  void *v2; // eax

  v2 = *(void **)(this + 1424);
  if ( v2 != nullptr )
    j__free(v2);
  *(uint32_t *)(this + 1424) = 0;
  *(uint32_t *)(this + 1428) = 0;
  *(uint32_t *)(this + 1432) = 0;
  `eh vector destructor iterator'((void *)(this + 956), 0x10u, 29, sub_401940);
  if ( *(uint32_t *)(this + 952) >= 0x10u )
    j__free(*(void **)(this + 932));
  *(uint32_t *)(this + 952) = 15;
  *(uint32_t *)(this + 948) = 0;
  *(uint8_t *)(this + 932) = 0;
  if ( *(uint32_t *)(this + 904) != 0 )
    j__free(*(void **)(this + 904));
  *(uint32_t *)(this + 904) = 0;
  *(uint32_t *)(this + 908) = 0;
  *(uint32_t *)(this + 912) = 0;
  if ( *(uint32_t *)(this + 888) != 0 )
    j__free(*(void **)(this + 888));
  *(uint32_t *)(this + 888) = 0;
  *(uint32_t *)(this + 892) = 0;
  *(uint32_t *)(this + 896) = 0;
  sub_4017E0(this + 868);
  sub_4017E0(this + 852);
  if ( *(uint32_t *)(this + 848) >= 0x10u )
    j__free(*(void **)(this + 828));
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  sub_4017E0(this + 808);
  sub_4017E0(this + 792);
  if ( *(uint32_t *)(this + 788) >= 0x10u )
    j__free(*(void **)(this + 768));
  *(uint32_t *)(this + 788) = 15;
  *(uint32_t *)(this + 784) = 0;
  *(uint8_t *)(this + 768) = 0;
  if ( *(uint32_t *)(this + 760) >= 0x10u )
    j__free(*(void **)(this + 740));
  *(uint32_t *)(this + 760) = 15;
  *(uint32_t *)(this + 756) = 0;
  *(uint8_t *)(this + 740) = 0;
  if ( *(uint32_t *)(this + 732) >= 0x10u )
    j__free(*(void **)(this + 712));
  *(uint32_t *)(this + 732) = 15;
  *(uint32_t *)(this + 728) = 0;
  *(uint8_t *)(this + 712) = 0;
  if ( *(uint32_t *)(this + 704) >= 0x10u )
    j__free(*(void **)(this + 684));
  *(uint32_t *)(this + 704) = 15;
  *(uint32_t *)(this + 700) = 0;
  *(uint8_t *)(this + 684) = 0;
  `eh vector destructor iterator'((void *)(this + 624), 0x1Cu, 2, sub_501490);
  if ( *(uint32_t *)(this + 620) >= 0x10u )
    j__free(*(void **)(this + 600));
  *(uint32_t *)(this + 620) = 15;
  *(uint32_t *)(this + 616) = 0;
  *(uint8_t *)(this + 600) = 0;
  if ( *(uint32_t *)(this + 592) >= 0x10u )
    j__free(*(void **)(this + 572));
  *(uint32_t *)(this + 592) = 15;
  *(uint32_t *)(this + 588) = 0;
  *(uint8_t *)(this + 572) = 0;
  if ( *(uint32_t *)(this + 564) >= 0x10u )
    j__free(*(void **)(this + 544));
  *(uint32_t *)(this + 564) = 15;
  *(uint32_t *)(this + 560) = 0;
  *(uint8_t *)(this + 544) = 0;
  if ( *(uint32_t *)(this + 532) >= 0x10u )
    j__free(*(void **)(this + 512));
  *(uint32_t *)(this + 532) = 15;
  *(uint32_t *)(this + 528) = 0;
  *(uint8_t *)(this + 512) = 0;
  if ( *(uint32_t *)(this + 132) != 0 )
    j__free(*(void **)(this + 132));
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  `eh vector destructor iterator'((void *)(this + 64), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 52) != 0 )
    j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CF8F0 sub_4CF8F0
// ------------------------------------------------------------
// 调: sub_4CF8F0 sub_4017E0
void /*thiscall*/ sub_4CF8F0(int this)
{
  if ( *(uint32_t *)(this + 244) >= 0x10u )
    j__free(*(void **)(this + 224));
  *(uint32_t *)(this + 244) = 15;
  *(uint32_t *)(this + 240) = 0;
  *(uint8_t *)(this + 224) = 0;
  sub_4017E0(this + 204);
  if ( *(uint32_t *)(this + 192) != 0 )
    j__free(*(void **)(this + 192));
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  sub_4017E0(this + 172);
  if ( *(uint32_t *)(this + 168) >= 0x10u )
    j__free(*(void **)(this + 148));
  *(uint32_t *)(this + 168) = 15;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 148) = 0;
  if ( *(uint32_t *)(this + 140) >= 0x10u )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 140) = 15;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 120) = 0;
  sub_4017E0(this + 100);
  if ( *(uint32_t *)(this + 96) >= 0x10u )
    j__free(*(void **)(this + 76));
  *(uint32_t *)(this + 96) = 15;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 76) = 0;
  if ( *(uint32_t *)(this + 60) != 0 )
    j__free(*(void **)(this + 60));
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CFA50 sub_4CFA50
// ------------------------------------------------------------
// 调: sub_4CFA50 sub_4017E0
void /*thiscall*/ sub_4CFA50(int this)
{
  if ( *(uint32_t *)(this + 196) >= 0x10u )
    j__free(*(void **)(this + 176));
  *(uint32_t *)(this + 196) = 15;
  *(uint32_t *)(this + 192) = 0;
  *(uint8_t *)(this + 176) = 0;
  sub_4017E0(this + 156);
  if ( *(uint32_t *)(this + 144) != 0 )
    j__free(*(void **)(this + 144));
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  sub_4017E0(this + 124);
  sub_4017E0(this + 108);
  if ( *(uint32_t *)(this + 104) >= 0x10u )
    j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 104) = 15;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 84) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CFB40 sub_4CFB40
// ------------------------------------------------------------
// 调: sub_4CFB40 sub_4017E0 sub_41B010
void /*thiscall*/ sub_4CFB40(int this)
{
  sub_4017E0(this + 136);
  if ( *(uint32_t *)(this + 124) != 0 )
    j__free(*(void **)(this + 124));
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  sub_41B010((void **)(this + 116));
  sub_41B010((void **)(this + 112));
  sub_41B010((void **)(this + 108));
  sub_41B010((void **)(this + 104));
  sub_41B010((void **)(this + 88));
  sub_41B010((void **)(this + 80));
  sub_41B010((void **)(this + 16));
  sub_41B010((void **)(this + 12));
  sub_41B010((void **)(this + 8));
  sub_41B010((void **)(this + 4));
}



// ------------------------------------------------------------
// 0x4CFC20 sub_4CFC20
// ------------------------------------------------------------
// 调: sub_4CFC20
void /*thiscall*/ sub_4CFC20(int this)
{
  if ( *(uint32_t *)(this + 68) != 0 )
    j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  if ( *(uint32_t *)(this + 56) >= 0x10u )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 15;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CFC80 sub_4CFC80
// ------------------------------------------------------------
// 调: sub_4CFC80 sub_4017E0
void /*thiscall*/ sub_4CFC80(int this)
{
  if ( *(uint32_t *)(this + 356) >= 0x10u )
    j__free(*(void **)(this + 336));
  *(uint32_t *)(this + 356) = 15;
  *(uint32_t *)(this + 352) = 0;
  *(uint8_t *)(this + 336) = 0;
  sub_4017E0(this + 316);
  if ( *(uint32_t *)(this + 304) != 0 )
    j__free(*(void **)(this + 304));
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  sub_4017E0(this + 284);
  sub_4017E0(this + 268);
  if ( *(uint32_t *)(this + 264) >= 0x10u )
    j__free(*(void **)(this + 244));
  *(uint32_t *)(this + 264) = 15;
  *(uint32_t *)(this + 260) = 0;
  *(uint8_t *)(this + 244) = 0;
  if ( *(uint32_t *)(this + 236) >= 0x10u )
    j__free(*(void **)(this + 216));
  *(uint32_t *)(this + 236) = 15;
  *(uint32_t *)(this + 232) = 0;
  *(uint8_t *)(this + 216) = 0;
  if ( *(uint32_t *)(this + 208) >= 0x10u )
    j__free(*(void **)(this + 188));
  *(uint32_t *)(this + 208) = 15;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 188) = 0;
  if ( *(uint32_t *)(this + 180) >= 0x10u )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 180) = 15;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 160) = 0;
  if ( *(uint32_t *)(this + 152) >= 0x10u )
    j__free(*(void **)(this + 132));
  *(uint32_t *)(this + 152) = 15;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 132) = 0;
  if ( *(uint32_t *)(this + 124) >= 0x10u )
    j__free(*(void **)(this + 104));
  *(uint32_t *)(this + 124) = 15;
  *(uint32_t *)(this + 120) = 0;
  *(uint8_t *)(this + 104) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4CFE40 sub_4CFE40
// ------------------------------------------------------------
// 调: sub_4CFE40
void /*thiscall*/ sub_4CFE40(int this)
{
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
}



// ------------------------------------------------------------
// 0x4CFE70 sub_4CFE70
// ------------------------------------------------------------
// 调: sub_4CFE70
void /*thiscall*/ sub_4CFE70(int this)
{
  if ( *(uint32_t *)(this + 28) != 0 )
    j__free(*(void **)(this + 28));
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
}



// ------------------------------------------------------------
// 0x4CFEA0 sub_4CFEA0
// ------------------------------------------------------------
// 调: sub_4CFEA0 sub_40D9A0
uint32_t */*thiscall*/ sub_4CFEA0(uint32_t *this)
{
  uint32_t **v2; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool v5; // zf
  uint32_t *v6; // ebx

  v2 = (uint32_t **)*(this + 1);
  v3 = *v2;
  *v2 = v2;
  result = (uint32_t *)*(this + 1);
  result[1] = result;
  v5 = v3 == (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  if ( !v5 )
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_40D9A0((int)v3);
      j__free(v3);
      result = (uint32_t *)*(this + 1);
      v3 = v6;
    }
    while ( v6 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4CFEE0 sub_4CFEE0
// ------------------------------------------------------------
// 调: sub_4CFEE0 sub_4015C0 sub_401740 sub_4CE5F0 sub_4CE5D0
int **/*thiscall*/ sub_4CFEE0(uint32_t *this, int **a2, int *Block)
{
  int *v3; // ebx
  char v4; // al
  int v5; // edi
  int *v6; // ecx
  int v7; // esi
  uint32_t *v8; // ecx
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // eax
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint8_t *v15; // eax
  bool v16; // zf
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+8h] [ebp-54h] BYREF
  size_t v20; // [esp+30h] [ebp-2Ch] BYREF
  char v21; // [esp+34h] [ebp-28h]
  int v22; // [esp+44h] [ebp-18h]
  int v23; // [esp+48h] [ebp-14h]
  uint32_t *v24; // [esp+4Ch] [ebp-10h]
  int v25; // [esp+58h] [ebp-4h]

  v3 = Block;
  v4 = *((uint8_t *)Block + 69);
  v24 = this;
  if ( v4 != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v25 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  sub_4CE5F0((int *)&Block);
  if ( *(uint8_t *)(*v3 + 69) != 0 )
  {
    v5 = v3[2];
LABEL_8:
    v7 = v3[1];
    if ( *(uint8_t *)(v5 + 69) == 0 )
      *(uint32_t *)(v5 + 4) = v7;
    v8 = v24;
    v9 = v24[1];
    if ( *(int **)(v9 + 4) == v3 )
    {
      *(uint32_t *)(v9 + 4) = v5;
    }
    else if ( *(int **)v7 == v3 )
    {
      *(uint32_t *)v7 = v5;
    }
    else
    {
      *(uint32_t *)(v7 + 8) = v5;
    }
    if ( *(int **)v8[1] == v3 )
    {
      if ( *(uint8_t *)(v5 + 69) != 0 )
      {
        v10 = (uint32_t *)v7;
      }
      else
      {
        v10 = sub_4CE5D0((uint32_t *)v5);
        v8 = v24;
      }
      *(uint32_t *)v8[1] = v10;
    }
    if ( *(int **)(v8[1] + 8) == v3 )
    {
      if ( *(uint8_t *)(v5 + 69) != 0 )
      {
        *(uint32_t *)(v8[1] + 8) = v7;
      }
      else
      {
        v11 = sub_4CE5B0(v5);
        v8 = v24;
        *(uint32_t *)(v24[1] + 8) = v11;
      }
    }
    goto LABEL_35;
  }
  if ( *(uint8_t *)(v3[2] + 69) != 0 )
  {
    v5 = *v3;
    goto LABEL_8;
  }
  v6 = Block;
  v5 = Block[2];
  if ( Block == v3 )
    goto LABEL_8;
  *(uint32_t *)(*v3 + 4) = Block;
  *v6 = *v3;
  if ( v6 == (int *)v3[2] )
  {
    v7 = (int)v6;
  }
  else
  {
    v7 = v6[1];
    if ( *(uint8_t *)(v5 + 69) == 0 )
      *(uint32_t *)(v5 + 4) = v7;
    *(uint32_t *)v7 = v5;
    v6[2] = v3[2];
    *(uint32_t *)(v3[2] + 4) = v6;
  }
  v12 = v24[1];
  if ( *(int **)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v6;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == v3 )
      *v13 = v6;
    else
      v13[2] = v6;
  }
  v6[1] = v3[1];
  v14 = *((uint8_t *)v6 + 68);
  *((uint8_t *)v6 + 68) = *((uint8_t *)v3 + 68);
  v8 = v24;
  *((uint8_t *)v3 + 68) = v14;
LABEL_35:
  if ( *((uint8_t *)v3 + 68) == 1 )
  {
    if ( v5 != *(uint32_t *)(v8[1] + 4) )
    {
      do
      {
        if ( *(uint8_t *)(v5 + 68) != 1 )
          break;
        v15 = *(uint8_t **)v7;
        if ( v5 == *(uint32_t *)v7 )
        {
          v15 = *(uint8_t **)(v7 + 8);
          if ( v15[68] == 0 )
          {
            v15[68] = 1;
            *(uint8_t *)(v7 + 68) = 0;
            sub_4CE650(v8, v7);
            v15 = *(uint8_t **)(v7 + 8);
            v8 = v24;
          }
          if ( v15[69] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v15 + 68) != 1 || *(uint8_t *)(*((uint32_t *)v15 + 2) + 68) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)v15 + 2) + 68) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v15 + 68) = 1;
              v15[68] = 0;
              sub_4CE6B0(v8, v15);
              v15 = *(uint8_t **)(v7 + 8);
              v8 = v24;
            }
            v15[68] = *(uint8_t *)(v7 + 68);
            *(uint8_t *)(v7 + 68) = 1;
            *(uint8_t *)(*((uint32_t *)v15 + 2) + 68) = 1;
            sub_4CE650(v8, v7);
            break;
          }
        }
        else
        {
          if ( v15[68] == 0 )
          {
            v15[68] = 1;
            *(uint8_t *)(v7 + 68) = 0;
            sub_4CE6B0(v8, (uint32_t *)v7);
            v15 = *(uint8_t **)v7;
            v8 = v24;
          }
          if ( v15[69] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)v15 + 2) + 68) != 1 || *(uint8_t *)(*(uint32_t *)v15 + 68) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v15 + 68) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)v15 + 2) + 68) = 1;
              v15[68] = 0;
              sub_4CE650(v8, (int)v15);
              v15 = *(uint8_t **)v7;
              v8 = v24;
            }
            v15[68] = *(uint8_t *)(v7 + 68);
            *(uint8_t *)(v7 + 68) = 1;
            *(uint8_t *)(*(uint32_t *)v15 + 68) = 1;
            sub_4CE6B0(v8, (uint32_t *)v7);
            break;
          }
        }
        v15[68] = 0;
LABEL_53:
        v5 = v7;
        v16 = v7 == *(uint32_t *)(v8[1] + 4);
        v7 = *(uint32_t *)(v7 + 4);
      }
      while ( !v16 );
    }
    *(uint8_t *)(v5 + 68) = 1;
  }
  if ( v3[14] != 0 )
    j__free((void *)v3[14]);
  v3[14] = 0;
  v3[15] = 0;
  v3[16] = 0;
  if ( (unsigned int)v3[11] >= 0x10 )
    j__free((void *)v3[6]);
  v3[11] = 15;
  v3[10] = 0;
  *((uint8_t *)v3 + 24) = 0;
  j__free(v3);
  v17 = v24[2];
  if ( v17 != 0 )
    v24[2] = v17 - 1;
  *a2 = Block;
  return a2;
}

