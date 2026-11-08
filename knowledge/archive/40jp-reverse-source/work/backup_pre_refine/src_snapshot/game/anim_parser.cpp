// ============================================================
// 【40JP逆向源代码工程】game/anim_parser.cpp
// 模块: .ani 动画帧解析器 + CNRDObject 族
// 来源: work/dump_misca.txt  区块: 0x490000-0x4A0000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 325
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4900E0 sub_4900E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4900E0(uint32_t *this, int ArgList, int a3, int a4)
{
  int result; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // ebx
  uint32_t *v10; // eax
  int v11; // ebx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int ArgLista; // [esp+14h] [ebp+8h]
  int ArgListb; // [esp+14h] [ebp+8h]
  char ArgListc; // [esp+14h] [ebp+8h]

  ArgLista = *(this + ArgList + 10);
  result = ArgLista;
  if ( ArgLista != a3 || (result = *(this + ArgList + 2)) != a4 )
  {
    *(this + ArgList + 10) = a3;
    *(this + ArgList + 2) = a4;
    if ( (uint32_t *)dword_99FF08 == this )
    {
      *(this + ArgList + 20) = 0;
      *(this + ArgList + 28) = 0;
      *((uint8_t *)this + ArgList + 144) = 0;
      sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
      if ( ArgLista != a3 )
      {
        if ( a3 == 0xFFFF )
        {
          v7 = sub_429830(ArgLista);
          v8 = v7;
          ArgListb = v7;
          if ( v7 != 0 && *(uint32_t *)(v7 + 196) != 0 )
            sub_4B05C0(0);
          if ( *(uint32_t *)(sub_656710() + 40) == ArgList )
          {
            v9 = 0;
            v10 = this + 10;
            while ( v9 == ArgList || *v10 == 0xFFFF )
            {
              ++v9;
              ++v10;
              if ( v9 >= 8 )
                goto LABEL_16;
            }
            *(uint32_t *)(sub_656710() + 40) = v9;
            off_77F3FC("@@SET HOST %d", v9);
LABEL_16:
            v8 = ArgListb;
          }
          sub_42B580(*(uint32_t *)(dword_8F7A24 + 40), ArgList, v8);
        }
        else
        {
          v11 = sub_429830(a3);
          sub_42E120(ArgList, v11, 1);
          v12 = *(uint32_t *)(v11 + 196);
          if ( v12 != 0 )
            sub_4B05B0(v12);
          sub_432EA0("LADDER_DOWN", -1, 0, 0);
        }
      }
      v13 = sub_48F660(this + 1, ArgList);
      if ( v13 != 0 )
      {
        v14 = *(uint32_t *)(v13 + 196);
        if ( v14 != 0 )
        {
          ArgListc = 0;
          switch ( a4 )
          {
            case 0:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 372))(v14, ArgList + 3);
              break;
            case 1:
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v14 + 372))(v14, 0);
              break;
            case 2:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 372))(v14, 1);
              break;
            case 3:
            case 4:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 372))(v14, 2);
              ArgListc = 1;
              break;
            default:
              break;
          }
          sub_4B12B0(ArgListc);
        }
      }
      return sub_49CA80(*((uint32_t *)dword_8F8528 + 9));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4902A0 sub_4902A0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4902A0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 18);
  return v1 != -1 && (v1 == 2 || v1 == 3 || v1 == 4);
}



// ------------------------------------------------------------
// 0x4902C0 sub_4902C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4902C0(int this)
{
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint8_t *)(this + 216) = 1;
  *(uint8_t *)(this + 217) = 0;
  *(uint32_t *)(this + 232) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x4902F0 sub_4902F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4902F0(void *this, const char *ArgList, const char *a3)
{
  int v4; // eax

  v4 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", ArgList, a3);
  if ( v4 != 0 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 8))(this, v4);
  else
    return off_77F3FC("PARTICLE CREATER CREATE FAIL! FILENAME[%s%s]", ArgList, a3);
}



// ------------------------------------------------------------
// 0x490340 sub_490340
// ------------------------------------------------------------
int /*thiscall*/ sub_490340(void *this, int a2)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 24))(this, a2);
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, a2 + 100);
}



// ------------------------------------------------------------
// 0x490370 sub_490370
// ------------------------------------------------------------
int /*thiscall*/ sub_490370(int this, int a2)
{
  int v2; // edx
  int result; // eax

  *(uint8_t *)(this + 189) = 0;
  *(uint8_t *)(this + 190) = 0;
  *(uint32_t *)(this + 204) = a2;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint8_t *)(this + 216) = 0;
  v2 = *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 220) = *(uint32_t *)(this + 4);
  result = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 224) = v2;
  *(uint32_t *)(this + 228) = result;
  *(uint32_t *)(this + 232) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4903D0 sub_4903D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4903D0(uint8_t *this, char a2)
{
  int v3; // ecx
  char result; // al

  v3 = (int)(this + 176);
  if ( a2 != 0 )
  {
    result = sub_699030(v3);
    *(this + 217) = a2;
  }
  else
  {
    result = sub_698FE0(v3);
    *(this + 217) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x490410 sub_490410
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_490410(uint32_t *a1, int a2, int a3, uint32_t *a4)
{
  int v4; // esi
  int v5; // ecx
  int v6; // eax

  v4 = a2;
  v5 = (a3 - a2) >> 2;
  while ( v5 > 0 )
  {
    v6 = v5 / 2;
    if ( *(uint32_t *)(v4 + 4 * (v5 / 2)) >= *a4 )
    {
      v5 /= 2;
    }
    else
    {
      v4 += 4 * v6 + 4;
      v5 += -1 - v6;
    }
  }
  *a1 = v4;
  return a1;
}



// ------------------------------------------------------------
// 0x490460 sub_490460
// ------------------------------------------------------------
int /*cdecl*/ sub_490460(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int v4; // eax
  uint32_t *v5; // ebx
  uint32_t *v6; // edi
  int *v7; // eax
  int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int i; // esi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int v19; // esi
  double v20; // st7
  double v21; // st7
  int result; // eax
  int v23; // edx
  int v24; // eax
  int *v25; // esi
  char v26; // al
  int v27; // ebx
  int v28; // ebx
  int v29; // ecx
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  bool v33; // zf
  int v34; // esi
  int v35; // edx
  int v36; // ebx
  float v37; // [esp+Ch] [ebp-18h] BYREF
  char v38[4]; // [esp+10h] [ebp-14h] BYREF
  char v39[4]; // [esp+14h] [ebp-10h] BYREF
  int v40; // [esp+18h] [ebp-Ch] BYREF
  int v41; // [esp+1Ch] [ebp-8h] BYREF
  int v42; // [esp+20h] [ebp-4h]

  v3 = a1;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 12))(a1, a2);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
  v5 = a3;
  v6 = (uint32_t *)v4;
  v7 = a3 + 3;
  v8 = 0;
  v42 = (int)(a3 + 3);
  do
  {
    if ( *v7 <= 0 )
    {
      *(float *)&v38[4 * v8 - 4] = 0.0;
    }
    else
    {
      v9 = *v7;
      v10 = rand() % (v9 + 1) - v9 / 2;
      v7 = (int *)v42;
      a1 = v10;
      *(float *)&v38[4 * v8 - 4] = (float)v10;
    }
    ++v8;
    v42 = (int)++v7;
  }
  while ( v8 < 3 );
  sub_52A1A0(v39, v38, v5[8]);
  sub_52A1A0(&v37, v39, v5[7]);
  sub_52A1A0(&v37, v38, v5[6]);
  for ( i = 0; i < 3; ++i )
  {
    if ( *(uint8_t *)(a2 + 84) == 0 || i != 0 )
      v6[i] += (int)(dword_7930D0[i] * (uint64_t)*(float *)&v38[4 * i - 4]) / 100;
    else
      *v6 += (int)(dword_7930D0[0] * (uint64_t)v37) / -100;
  }
  v12 = v5[9];
  if ( v12 != 0 )
  {
    if ( v12 == 1 )
    {
      sub_432FA0();
      v15 = rand() % 360;
      v6[20] = 90 - v15;
      v16 = v5[10];
      v42 = v15;
      if ( v16 != 0 )
      {
        v17 = v16 / 2;
        v40 = rand();
        a1 = dword_9A011C + 4 * v17;
        v18 = sub_4D33A0(&v40);
        a1 = v18 % (*(uint32_t *)a1 + 1);
        sub_490410(&v41, dword_9A011C, dword_9A011C + 4 * v17, &a1);
        v19 = v42;
        a1 = (v41 - dword_9A011C) >> 2;
        *(float *)&a1 = (float)a1;
        v20 = sub_405400(v42);
        v6[18] += (uint64_t)(v20 * *(float *)&a1);
        v21 = sub_4053E0(v19);
        v6[19] += (uint64_t)(v21 * *(float *)&a1);
      }
    }
  }
  else
  {
    v13 = v5[10];
    if ( v13 != 0 )
    {
      v6[18] += v13 / -2;
      v6[18] += rand() % (v5[10] + 1);
    }
    v14 = v5[11];
    if ( v14 != 0 )
    {
      v6[19] += v14 / -2;
      v6[19] += rand() % (v5[11] + 1);
    }
  }
  result = v5[12];
  if ( result != 0 )
  {
    v42 = rand() % (10 * v5[12] + 1) - 5 * v5[12];
    v23 = rand() % (10 * v5[12] + 1);
    v24 = 5 * v5[12];
    a1 = (int)(v6 + 3);
    v25 = (uint32_t *)((char *)v6 + 15);
    v40 = 3;
    v41 = v23 - v24;
    do
    {
      v26 = *(uint8_t *)a1;
      if ( *(uint8_t *)a1 == 1 )
      {
        v27 = v5[12];
        v28 = rand() % (10 * v27 + 1) - 5 * v27 + 1000;
        *v25 = v28 * *v25 / 1000;
        v29 = v28 * v25[1];
        v5 = a3;
        v25[1] = v29 / 1000;
      }
      else if ( v26 == 2 || v26 == 3 )
      {
        v30 = v41 + 1000;
        *v25 = (v42 + 1000) * *v25 / 1000;
        v31 = v25[1];
        v25[6] = v30 * v25[6] / 1000;
        v32 = v41 + 1000;
        v25[1] = (v42 + 1000) * v31 / 1000;
        v25[7] = v32 * v25[7] / 1000;
      }
      v25 += 2;
      v33 = v40 == 1;
      ++a1;
      --v40;
    }
    while ( !v33 );
    v34 = v5[12];
    v35 = (uint64_t)(274877907LL * *(uint32_t *)((char *)v6 + 63) * (5 * (200 - v34) + rand() % (10 * v34 + 1))) >> 32;
    result = *(uint32_t *)((char *)v6 + 85);
    *(uint32_t *)((char *)v6 + 63) = (v35 >> 6) + ((unsigned int)v35 >> 31);
    if ( result != 0 )
    {
      v36 = v5[12];
      result = *(uint32_t *)((char *)v6 + 85) * (5 * (200 - v36) + rand() % (10 * v36 + 1)) / 1000;
      *(uint32_t *)((char *)v6 + 85) = result;
      if ( result <= 0 )
        *(uint32_t *)((char *)v6 + 85) = 1;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x490880 sub_490880
// ------------------------------------------------------------
void /*noreturn*/ sub_490880()
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
// 0x4908F0 sub_4908F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4908F0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_490880(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x490950 sub_490950
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_490950(int this, int Src, unsigned int a3, int *a4)
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
      sub_490880(this);
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



// ------------------------------------------------------------
// 0x490B30 sub_490B30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_490B30(uint32_t *this, int a2)
{
  int v3; // ecx
  unsigned int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int v8; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *v10; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(a2 + 4);
  v11 = &v9;
  v10 = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( sub_4908F0(this, v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = *(uint32_t *)(a2 + 8);
    v6 = *(uint32_t *)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x490BD0 sub_490BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_490BD0(uint32_t *this)
{
  uint32_t *v1; // esi
  char *v2; // edx
  int v3; // eax
  int v4; // ebx
  int *v5; // esi
  uint64_t v6; // rax
  char *v7; // edi
  uint32_t *v8; // edx
  int v11; // [esp+8h] [ebp-4h] BYREF

  v1 = this;
  *(this + 55) = -1;
  *(this + 56) = -1;
  *(this + 57) = -1;
  if ( byte_9A0110 == 0 )
  {
    v2 = (char *)dword_9A0120;
    v11 = 0;
    if ( dword_9A011C != 0
      && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
    {
      *(uint32_t *)dword_9A0120 = 0;
      dword_9A0120 = v2 + 4;
    }
    else
    {
      sub_430C80(dword_9A0120, 1, (int)&v11);
    }
    v3 = 0;
    do
    {
      v4 = v3 + 1;
      v5 = (int *)(dword_9A011C + 4 * v3);
      v6 = (uint64_t)(sub_4053E0(v3 + 1) * 1000.0 + (double)*v5);
      v7 = (char *)dword_9A0120;
      v11 = v6;
      if ( dword_9A011C != 0
        && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
      {
        v8 = (char *)dword_9A0120 + 4;
        *(uint32_t *)dword_9A0120 = v6;
        dword_9A0120 = v7 + 4;
      }
      else
      {
        sub_430C80(dword_9A0120, 1, (int)&v11);
        v8 = dword_9A0120;
      }
      v3 = v4;
    }
    while ( v4 < 180 );
    v11 = 0;
    if ( dword_9A011C != 0 && ((int)v8 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
    {
      *v8 = 0;
      dword_9A0120 = v8 + 1;
    }
    else
    {
      sub_430C80(v8, 1, (int)&v11);
    }
    v1 = this;
    byte_9A0110 = 1;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v1 + 88))(v1, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v1 + 12))(v1, 0);
}



// ------------------------------------------------------------
// 0x490D40 sub_490D40
// ------------------------------------------------------------
int /*thiscall*/ sub_490D40(uint32_t *this, int a2, int a3)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 4))(this, a2, a3);
  return sub_490BD0(this);
}



// ------------------------------------------------------------
// 0x490D70 sub_490D70
// ------------------------------------------------------------
int /*thiscall*/ sub_490D70(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // ecx
  void *v5; // edi
  char v6; // al
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ebx
  double v13; // st7
  int v14; // edi
  int v15; // eax
  double v16; // st7
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int *v20; // eax
  int v21; // edx
  bool v22; // zf
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // ecx
  char *v27; // eax
  int v28; // ecx
  int v29; // edx
  int v30; // esi
  float v32; // [esp+Ch] [ebp-60h]
  float v33; // [esp+10h] [ebp-5Ch]
  int v34; // [esp+18h] [ebp-54h]
  int v35; // [esp+18h] [ebp-54h]
  int v36; // [esp+18h] [ebp-54h]
  int v37; // [esp+18h] [ebp-54h]
  char v38[4]; // [esp+28h] [ebp-44h] BYREF
  uint8_t *v39; // [esp+2Ch] [ebp-40h]
  void *Src; // [esp+30h] [ebp-3Ch]
  int v41; // [esp+34h] [ebp-38h]
  int v42; // [esp+38h] [ebp-34h] BYREF
  int v43; // [esp+3Ch] [ebp-30h]
  int v44; // [esp+40h] [ebp-2Ch]
  int v45; // [esp+44h] [ebp-28h]
  int v46; // [esp+48h] [ebp-24h]
  int v47; // [esp+4Ch] [ebp-20h]
  int *v48; // [esp+50h] [ebp-1Ch]
  int v49; // [esp+54h] [ebp-18h]
  int v50; // [esp+58h] [ebp-14h]
  int v51; // [esp+5Ch] [ebp-10h]
  int v52; // [esp+68h] [ebp-4h]

  v3 = (int)(this + 44);
  v42 = 0;
  sub_698F90((int)(this + 44), 0, 0);
  v4 = sub_699000(v3) + *(this + 51);
  v5 = nullptr;
  *(this + 52) = v4;
  v39 = nullptr;
  Src = nullptr;
  v41 = 0;
  v6 = *((uint8_t *)this + 216);
  v52 = 0;
  if ( v6 != 0 )
    goto LABEL_39;
  if ( *(this + 58) == -1 )
    *(this + 58) = dword_9A0114;
  if ( *((float *)this + 26) == 0.0 || *(this + *(this + 58) + 40) == 0 )
  {
    *((uint8_t *)this + 216) = 1;
LABEL_39:
    v30 = a2;
    sub_490B30(v38);
    return v30;
  }
  if ( *(this + 26) == -1082130432 )
  {
    v7 = *this;
    v34 = *(this + 27);
    *((uint8_t *)this + 216) = 1;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 84))(this, v34);
  }
  else
  {
    v9 = *(this + 28);
    v49 = v4;
    if ( v9 > 0 && v4 >= v9 )
    {
      *((uint8_t *)this + 216) = 1;
      v49 = v9;
    }
    v10 = 1 - (uint64_t)((double)v49 * *((float *)this + 26) * -0.001);
    v11 = *(this + 27);
    if ( v11 != 0 && v10 >= v11 )
    {
      *((uint8_t *)this + 216) = 1;
      v10 = v11;
    }
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 84))(this, v10);
  }
  v12 = *(this + 53);
  v50 = v8;
  v46 = v12;
  if ( v12 < v8 )
  {
    v49 = 1000 * v12;
    do
    {
      v13 = *((float *)this + 26);
      v14 = 0;
      v51 = 0;
      if ( v13 <= 0.0 )
      {
        if ( *(this + 26) == -1082130432 )
          v51 = *(this + 52);
      }
      else
      {
        v15 = *this;
        v35 = *(this + 26);
        *(float *)&v47 = (float)v49;
        v16 = ((double (/*thiscall*/ *)(uint32_t *, int))*(uint32_t *)(v15 + 80))(this, v35);
        v51 = *(this + 52) - (uint64_t)(*(float *)&v47 / v16);
      }
      v17 = *(uint32_t *)((char *)this + 89);
      if ( v17 == 0 || v17 > v51 )
      {
        v18 = sub_445D00(156);
        v42 = v18;
        LOBYTE(v52) = 1;
        if ( v18 != 0 )
          v14 = sub_445B90(v18);
        v19 = *(uint32_t *)v14;
        v36 = *(this + 46);
        LOBYTE(v52) = 0;
        v42 = v14;
        (*(void (/*thiscall*/ **)(int, int))(v19 + 68))(v14, v36);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 20))(this, v14);
        if ( *((uint8_t *)this + 156) != 0 )
        {
          v20 = this + 55;
          v48 = this + 55;
          v43 = -220 - (uint32_t)this;
          v47 = 3;
          do
          {
            v21 = *v20;
            v22 = *v20 == *(v20 - 54);
            v45 = *(v20 - 54);
            if ( !v22 )
            {
              v23 = v12 - *(this + 53) + 1;
              v37 = v50 - *(this + 53);
              v44 = v21;
              v33 = (float)v45;
              v32 = (float)v21;
              v24 = (uint64_t)sub_4049C0(v32, v33, v23, v37);
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14);
              v26 = v43 + v25;
              v20 = v48;
              *(int *)((char *)v48 + v26) = v24;
              v12 = v46;
            }
            ++v20;
            v22 = v47 == 1;
            v48 = v20;
            --v47;
          }
          while ( !v22 );
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, v51);
        if ( v39 != nullptr && ((uint8_t *)Src - v39) >> 2 < (unsigned int)((v41 - (int)v39) >> 2) )
        {
          v27 = (char *)Src;
          *(uint32_t *)Src = v14;
          Src = v27 + 4;
        }
        else
        {
          sub_490950(Src, 1, (int)&v42);
        }
      }
      v8 = v50;
      v46 = ++v12;
      v49 += 1000;
    }
    while ( v12 < v50 );
    v5 = v39;
  }
  *(this + 53) = v8;
  v28 = *(this + 2);
  v29 = *(this + 3);
  *(this + 55) = *(this + 1);
  *(this + 56) = v28;
  *(this + 57) = v29;
  v30 = a2;
  sub_490B30(v38);
  if ( v5 != nullptr )
    j__free(v5);
  return v30;
}


// ------------------------------------------------------------
// 0x4910A0 sub_4910A0
// ------------------------------------------------------------
int /*fastcall*/ sub_4910A0(int a1)
{
  int v1; // eax

  do
  {
    v1 = a1;
    a1 = *(uint32_t *)(a1 + 212);
  }
  while ( a1 != 0 );
  return *(uint32_t *)(v1 + 32);
}



// ------------------------------------------------------------
// 0x4910C0 sub_4910C0
// ------------------------------------------------------------
char /*fastcall*/ sub_4910C0(int a1)
{
  int v1; // eax

  do
  {
    v1 = a1;
    a1 = *(uint32_t *)(a1 + 212);
  }
  while ( a1 != 0 );
  return *(uint8_t *)(v1 + 169);
}



// ------------------------------------------------------------
// 0x4910E0 sub_4910E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4910E0(int this)
{
  int v2; // ecx
  char v3; // al
  int v5; // eax

  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);
  v2 = *(uint32_t *)(this + 212);
  if ( v2 != 0 )
    v3 = sub_4910C0(v2);
  else
    v3 = *(uint8_t *)(this + 169);
  if ( v3 != 0 )
    return 0;
  v5 = *(uint32_t *)(this + 28) + sub_699000(this);
  if ( v5 == *(uint32_t *)(this + 32) )
    return 0;
  *(uint32_t *)(this + 32) = v5;
  return 1;
}



// ------------------------------------------------------------
// 0x491130 sub_491130
// ------------------------------------------------------------
char /*cdecl*/ sub_491130(float *a1, float *a2, float *a3)
{
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double v8; // st7
  double v9; // st6
  float v11; // [esp+8h] [ebp+8h]
  float v12; // [esp+8h] [ebp+8h]
  float v13; // [esp+8h] [ebp+8h]

  if ( a1[3] == 0.0
    || a1[4] == 0.0
    || a1[5] == 0.0
    || a2[3] == 0.0
    || a2[4] == 0.0
    || a2[5] == 0.0
    || *a1 + a1[3] < *a2
    || *a2 + a2[3] < *a1
    || a1[4] + a1[1] < a2[1]
    || a2[4] + a2[1] < a1[1]
    || a1[2] + a1[5] < a2[2]
    || a2[2] + a2[5] < a1[2] )
  {
    return 0;
  }
  if ( a3 != nullptr )
  {
    if ( *a1 <= (double)*a2 )
      v4 = *a2;
    else
      v4 = *a1;
    *a3 = v4;
    v5 = *a1 + a1[3];
    v11 = *a2 + a2[3];
    if ( v5 >= v11 )
      v5 = v11;
    a3[3] = v5 - v4;
    if ( a1[1] <= (double)a2[1] )
      v6 = a2[1];
    else
      v6 = a1[1];
    a3[1] = v6;
    v7 = a1[4] + a1[1];
    v12 = a2[4] + a2[1];
    if ( v7 >= v12 )
      v7 = v12;
    a3[4] = v7 - v6;
    if ( a1[2] <= (double)a2[2] )
      v8 = a2[2];
    else
      v8 = a1[2];
    a3[2] = v8;
    v9 = a1[2] + a1[5];
    v13 = a2[2] + a2[5];
    if ( v9 >= v13 )
      v9 = v13;
    a3[5] = v9 - v8;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x491300 sub_491300
// ------------------------------------------------------------
void /*thiscall*/ sub_491300(uint8_t *this, int a2, int a3, int a4, float a5, int a6, int a7, float a8, float a9, int a10)
{
  int v10; // eax
  uint64_t v12; // rax
  double v13; // st7
  int v14; // edi
  int v15; // ebx
  float v16; // ecx
  double v17; // st7
  uint8_t v18; // al
  double v19; // st7
  int v20; // ebx
  double v21; // st7
  int v22; // [esp+4h] [ebp-20h]
  float v23; // [esp+8h] [ebp-1Ch]
  float v24; // [esp+8h] [ebp-1Ch]
  float v25; // [esp+Ch] [ebp-18h]
  int v26; // [esp+Ch] [ebp-18h]
  float v27; // [esp+10h] [ebp-14h]
  float v28; // [esp+10h] [ebp-14h]
  float v29; // [esp+14h] [ebp-10h]
  float v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+18h] [ebp-Ch]
  float v32; // [esp+38h] [ebp+14h]
  float v33; // [esp+38h] [ebp+14h]
  float v34; // [esp+38h] [ebp+14h]
  float v35; // [esp+44h] [ebp+20h]
  float v36; // [esp+44h] [ebp+20h]

  v10 = *(uint32_t *)(a6 + 4);
  if ( v10 != -1 )
  {
    v31 = *(uint32_t *)(a6 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v10);
    *(uint32_t *)a6 = sub_418DD0(v31);
  }
  if ( byte_790AD0 != 0 && *(this + 161) != 0 && *(uint32_t *)a6 != 0 )
  {
    v25 = (float)a10;
    v12 = (uint64_t)sub_4049C0(0.0, v25, *(uint8_t *)(a6 + 35), 255);
    if ( dword_9A012C == 0 )
    {
      if ( LOBYTE(a5) != 0 )
      {
        v32 = *(float *)(a6 + 28) - a8;
        v35 = -*(float *)(a6 + 20);
      }
      else
      {
        v13 = a8 + *(float *)(a6 + 28);
        v35 = *(float *)(a6 + 20);
        v32 = v13;
      }
      v14 = *(uint32_t *)(a6 + 16);
      v15 = *(uint32_t *)(a6 + 12);
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = (uint8_t)v12 << 24;
      v23 = v32;
      v16 = v35;
LABEL_21:
      *(float *)&v22 = a9 * *(float *)(a6 + 24);
      sub_424760(
        dword_79C0B0,
        a3 + v15,
        a4 + v14 - (uint64_t)((double)a7 * 0.1),
        *(uint32_t *)a6,
        v16,
        v22,
        v23,
        v26,
        v27,
        v29);
      return;
    }
    if ( dword_9A012C != 1 )
    {
      if ( dword_9A012C != 2 )
        return;
      if ( LOBYTE(a5) != 0 )
      {
        v34 = *(float *)(a6 + 28) - a8;
        v36 = -*(float *)(a6 + 20);
      }
      else
      {
        v21 = a8 + *(float *)(a6 + 28);
        v36 = *(float *)(a6 + 20);
        v34 = v21;
      }
      v14 = *(uint32_t *)(a6 + 16);
      v15 = *(uint32_t *)(a6 + 12);
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = -16777216;
      v23 = v34;
      v16 = v36;
      goto LABEL_21;
    }
    v17 = *(float *)(a6 + 28);
    v18 = (v12 - 50) & (((int)v12 - 50 < 0) - 1);
    if ( LOBYTE(a5) != 0 )
    {
      v19 = v17 - 3.14;
      v33 = *(float *)(a6 + 20);
    }
    else
    {
      v19 = v17 + 3.14;
      v33 = -*(float *)(a6 + 20);
    }
    v20 = *(uint32_t *)(a6 + 12);
    v30 = (float)-*(uint32_t *)(a6 + 16);
    v28 = (float)-v20;
    v24 = v19;
    sub_424760(
      dword_79C0B0,
      a3 + v20,
      a4 + *(uint32_t *)(a6 + 16) - (uint64_t)((double)a7 * -0.1),
      *(uint32_t *)a6,
      v33,
      *(uint32_t *)(a6 + 24),
      v24,
      (v18 << 24) | 0xFFFFFF,
      v28,
      v30);
  }
}


// ------------------------------------------------------------
// 0x491530 sub_491530
// ------------------------------------------------------------
int /*cdecl*/ sub_491530(int a1, int a2)
{
  int result; // eax

  result = a1 - 1;
  switch ( a1 )
  {
    case 1:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 9);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 5);
      break;
    case 2:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 2);
      break;
    case 3:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 4);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);
      break;
    case 4:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 10);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 1);
      break;
    case 5:
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(
        dword_79C0A4,
        60,
        a2 & 0xFF00FF00 | ((uint8_t)a2 << 16) | BYTE2(a2));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x491630 sub_491630
// ------------------------------------------------------------
int /*cdecl*/ sub_491630(int a1)
{
  int result; // eax

  result = a1;
  if ( a1 > 0 )
  {
    if ( a1 <= 4 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);
    }
    else if ( a1 == 5 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);
      return (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x491690 sub_491690
// ------------------------------------------------------------
char /*thiscall*/ sub_491690(int this, char a2, int a3, char a4, int a5, int a6, char a7)
{
  char result; // al

  result = a2;
  *(uint8_t *)(this + 176) = a2;
  if ( a2 != 0 )
  {
    *(uint32_t *)(this + 180) = a3;
    *(uint8_t *)(this + 184) = a4;
    *(uint32_t *)(this + 188) = a5;
    *(uint32_t *)(this + 192) = a6;
    *(uint8_t *)(this + 196) = a7;
    return a7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4916E0 sub_4916E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4916E0(int a1, int a2, int a3, float a4, int a5)
{
  int result; // eax
  int v6; // ecx
  float v7; // [esp+4h] [ebp-Ch]
  int v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+8h] [ebp-8h]
  float v10; // [esp+24h] [ebp+14h]

  result = *(uint32_t *)(a5 + 4);
  if ( result != -1 )
  {
    v8 = *(uint32_t *)(a5 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, result);
    result = sub_418DD0(v8);
    *(uint32_t *)a5 = result;
  }
  if ( *(uint32_t *)a5 != 0 )
  {
    sub_491530(*(uint32_t *)(a5 + 40), *(uint32_t *)(a5 + 44));
    if ( LOBYTE(a4) != 0 )
      v10 = -*(float *)(a5 + 20);
    else
      v10 = *(float *)(a5 + 20);
    v6 = *(uint32_t *)(a5 + 12);
    v9 = (float)-*(uint32_t *)(a5 + 16);
    v7 = (float)-v6;
    sub_424760(
      dword_79C0B0,
      a2 + v6,
      a3 + *(uint32_t *)(a5 + 16),
      *(uint32_t *)a5,
      v10,
      *(uint32_t *)(a5 + 24),
      *(float *)(a5 + 28),
      *(uint32_t *)(a5 + 32),
      v7,
      v9);
    return sub_491630(*(uint32_t *)(a5 + 40));
  }
  return result;
}



// ------------------------------------------------------------
// 0x4917A0 sub_4917A0
// ------------------------------------------------------------
char /*stdcall*/ sub_4917A0(int a1, int a2, int a3, float a4, int a5, int a6, char a7, int a8, int a9)
{
  int v9; // eax
  int v10; // edi
  int v11; // ecx
  float v13; // [esp+24h] [ebp-10h]
  float v14; // [esp+28h] [ebp-Ch]
  int v15; // [esp+2Ch] [ebp-8h]
  float v16; // [esp+48h] [ebp+14h]

  v9 = *(uint32_t *)(a5 + 4);
  if ( v9 != -1 )
  {
    v15 = *(uint32_t *)(a5 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v9);
    v9 = sub_418DD0(v15);
    *(uint32_t *)a5 = v9;
  }
  if ( *(uint32_t *)a5 != 0 )
  {
    v10 = a6;
    if ( a6 != 0 )
      sub_491530(a6, 0);
    if ( a7 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(
        dword_79C0A4,
        60,
        a8 & 0xFF00FF00 | ((uint8_t)a8 << 16) | BYTE2(a8));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);
      v10 = a6;
    }
    if ( LOBYTE(a4) != 0 )
      v16 = -*(float *)(a5 + 20);
    else
      v16 = *(float *)(a5 + 20);
    v11 = *(uint32_t *)(a5 + 12);
    v14 = (float)-*(uint32_t *)(a5 + 16);
    v13 = (float)-v11;
    sub_424760(
      dword_79C0B0,
      a2 + v11,
      a3 + *(uint32_t *)(a5 + 16),
      *(uint32_t *)a5,
      v16,
      *(uint32_t *)(a5 + 24),
      *(float *)(a5 + 28),
      a9,
      v13,
      v14);
    if ( v10 != 0 )
      sub_491630(v10);
    LOBYTE(v9) = a7;
    if ( a7 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);
      LOBYTE(v9) = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);
    }
  }
  return v9;
}



// ------------------------------------------------------------
// 0x4918E0 sub_4918E0
// ------------------------------------------------------------
int /*cdecl*/ sub_4918E0(int *a1, int a2)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint64_t v4; // rax
  unsigned int v6; // [esp-4h] [ebp-8h]

  if ( a1 != nullptr && *a1 != 0 )
  {
    v2 = a1[1];
    if ( v2 != -1 )
    {
      v6 = a1[2];
      v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v2);
      *a1 = sub_418DD0(v3, v6);
    }
    LODWORD(v4) = 0;
    switch ( a2 )
    {
      case 0:
        LODWORD(v4) = -(a1[3] + *(uint32_t *)(*a1 + 28));
        goto LABEL_7;
      case 1:
        LODWORD(v4) = a1[3] + *(uint32_t *)(*a1 + 20) + *(uint32_t *)(*a1 + 28);
LABEL_7:
        if ( a1[5] != 1065353216 )
          return (uint64_t)((double)(int)v4 * *((float *)a1 + 5));
        return v4;
      case 2:
        LODWORD(v4) = -(a1[4] + *(uint32_t *)(*a1 + 32));
        goto LABEL_12;
      case 3:
        LODWORD(v4) = a1[4] + *(uint32_t *)(*a1 + 24) + *(uint32_t *)(*a1 + 32);
LABEL_12:
        if ( a1[6] != 1065353216 )
          v4 = (uint64_t)((double)(int)v4 * *((float *)a1 + 6));
        break;
      default:
        return v4;
    }
  }
  else
  {
    LODWORD(v4) = 0;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4919B0 sub_4919B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4919B0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_48C4B0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4919D0 sub_4919D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4919D0(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // esi
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  uint16_t v18; // cx
  float v20; // [esp+0h] [ebp-38h]
  float v21; // [esp+0h] [ebp-38h]
  float v22; // [esp+0h] [ebp-38h]
  float v23; // [esp+0h] [ebp-38h]
  float v24; // [esp+0h] [ebp-38h]
  float v25; // [esp+0h] [ebp-38h]
  float v26; // [esp+4h] [ebp-34h]
  float v27; // [esp+4h] [ebp-34h]
  float v28; // [esp+4h] [ebp-34h]
  float v29; // [esp+4h] [ebp-34h]
  float v30; // [esp+4h] [ebp-34h]
  float v31; // [esp+4h] [ebp-34h]
  int v32; // [esp+1Ch] [ebp-1Ch]
  int v33; // [esp+20h] [ebp-18h]
  int v34; // [esp+24h] [ebp-14h]
  int v35; // [esp+30h] [ebp-8h]
  int v36; // [esp+34h] [ebp-4h]

  LOBYTE(v2) = *(uint8_t *)(this + 96);
  if ( (uint8_t)v2 != 0 )
  {
    v3 = *(uint32_t *)(this + 44);
    if ( v3 != 0 )
      v4 = (*(uint32_t *)(this + 48) - v3) / 88;
    else
      v4 = 0;
    v2 = *(uint32_t *)(this + 148);
    if ( v2 == v4 - 1 )
    {
      if ( *(uint8_t *)(this + 160) == 0 )
        return v2;
      v5 = *(uint32_t *)(this + 44);
      v6 = v5;
    }
    else
    {
      v5 = *(uint32_t *)(this + 44);
      v6 = v5 + 88 * (v2 + 1);
    }
    v7 = v5 + 88 * v2;
    v8 = *(uint32_t *)(this + 212);
    v36 = v7;
    if ( v8 != 0 )
      v9 = sub_4910A0(v8);
    else
      v9 = *(uint32_t *)(this + 32);
    v10 = *(uint32_t *)(this + 152);
    v11 = *(uint32_t *)(this + 156) - v10;
    v26 = (float)*(int *)(v6 + 12);
    v12 = (double)*(int *)(v36 + 12);
    v35 = v9 - v10;
    v20 = v12;
    sub_4049C0(v20, v26, v9 - v10, v11);
    *(uint32_t *)(this + 72) = (uint64_t)v12;
    v27 = (float)*(int *)(v6 + 16);
    v13 = (double)*(int *)(v36 + 16);
    v21 = v13;
    sub_4049C0(v21, v27, v35, v11);
    *(uint32_t *)(this + 76) = (uint64_t)v13;
    sub_4049C0(*(float *)(v36 + 20), *(float *)(v6 + 20), v35, v11);
    *(float *)(this + 80) = v13;
    sub_4049C0(*(float *)(v36 + 24), *(float *)(v6 + 24), v35, v11);
    *(float *)(this + 84) = v13;
    sub_4049C0(*(float *)(v36 + 28), *(float *)(v6 + 28), v35, v11);
    *(float *)(this + 88) = v13;
    v28 = (float)*(uint8_t *)(v6 + 32);
    v14 = (double)*(uint8_t *)(v36 + 32);
    v22 = v14;
    sub_4049C0(v22, v28, v35, v11);
    v32 = (uint64_t)v14;
    v29 = (float)*(uint8_t *)(v6 + 33);
    v15 = (double)*(uint8_t *)(v36 + 33);
    v23 = v15;
    sub_4049C0(v23, v29, v35, v11);
    v33 = (uint64_t)v15;
    v30 = (float)*(uint8_t *)(v6 + 34);
    v16 = (double)*(uint8_t *)(v36 + 34);
    v24 = v16;
    sub_4049C0(v24, v30, v35, v11);
    v34 = (uint64_t)v16;
    v31 = (float)*(uint8_t *)(v6 + 35);
    v17 = (double)*(uint8_t *)(v36 + 35);
    v25 = v17;
    sub_4049C0(v25, v31, v35, v11);
    HIBYTE(v18) = (uint64_t)v17;
    LOBYTE(v18) = v34;
    *(uint32_t *)(this + 92) = (uint8_t)v32 | (((uint8_t)v33 | (v18 << 8)) << 8);
    LOBYTE(v2) = v32;
  }
  return v2;
}


// ------------------------------------------------------------
// 0x491C10 sub_491C10
// ------------------------------------------------------------
int /*thiscall*/ sub_491C10(int this)
{
  int v1; // eax
  int v2; // ebx
  int *v3; // esi
  int i; // edi

  v1 = *(uint32_t *)(this + 44);
  v2 = 0;
  if ( v1 != 0 )
    v1 = (*(uint32_t *)(this + 48) - v1) / 88;
  if ( v1 > 0 )
  {
    v3 = (int *)(*(uint32_t *)(this + 44) + 48);
    for ( i = v1; i != 0; --i )
    {
      v2 += (uint64_t)((double)*v3 * (1.0 / *(float *)(this + 164)) * 100.0);
      v3 += 22;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x491C70 sub_491C70
// ------------------------------------------------------------
int /*thiscall*/ sub_491C70(int this, int a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // ecx
  int v8; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]

  v3 = *(uint32_t *)(this + 44);
  v4 = 0;
  v9 = 0;
  if ( v3 != 0 )
    v8 = (*(uint32_t *)(this + 48) - v3) / 88;
  else
    v8 = 0;
  v5 = 0;
  if ( a2 <= 0 )
    return 0;
  do
  {
    if ( v5 >= v8 )
      break;
    v6 = (uint64_t)((double)*(int *)(*(uint32_t *)(this + 44) + v4 + 48) / *(float *)(this + 164) * 100.0) + v9;
    ++v5;
    v4 += 88;
    v9 = v6;
  }
  while ( v5 < a2 );
  return v9;
}



// ------------------------------------------------------------
// 0x491D00 sub_491D00
// ------------------------------------------------------------
char /*thiscall*/ sub_491D00(int this, int a2, int a3, int a4, float a5)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  char result; // al

  v6 = *(uint32_t **)(this + 204);
  v7 = (uint32_t *)*v6;
  if ( (uint32_t *)*v6 != v6 )
  {
    do
    {
      if ( (int)v7[2] >= 0 )
        break;
      sub_491D00(a2, a3, a4, a5);
      v7 = (uint32_t *)*v7;
    }
    while ( v7 != *(uint32_t **)(this + 204) );
  }
  sub_4916E0(a2, a3, a4, a5, this + 60);
  result = *(uint8_t *)(this + 176);
  if ( result != 0 )
  {
    sub_4917A0(
      a2,
      a3,
      a4,
      a5,
      this + 60,
      *(uint32_t *)(this + 180),
      *(uint8_t *)(this + 184),
      *(uint32_t *)(this + 188),
      *(uint32_t *)(this + 192));
    result = *(uint8_t *)(this + 196);
    if ( result != 0 )
      *(uint8_t *)(this + 176) = 0;
  }
  for ( ; v7 != *(uint32_t **)(this + 204); v7 = (uint32_t *)*v7 )
    result = sub_491D00(a2, a3, a4, a5);
  return result;
}



// ------------------------------------------------------------
// 0x491DE0 sub_491DE0
// ------------------------------------------------------------
char /*thiscall*/ sub_491DE0(uint32_t *this, int a2, int a3, int a4, float a5, int a6, char a7, int a8, int a9)
{
  uint32_t *v10; // eax
  uint32_t *v11; // esi
  char result; // al

  v10 = (uint32_t *)*(this + 51);
  v11 = (uint32_t *)*v10;
  if ( (uint32_t *)*v10 != v10 )
  {
    do
    {
      if ( (int)v11[2] >= 0 )
        break;
      sub_491DE0(a2, a3, a4, a5, a6, a7, a8, a9);
      v11 = (uint32_t *)*v11;
    }
    while ( v11 != (uint32_t *)*(this + 51) );
  }
  for ( result = sub_4917A0(a2, a3, a4, a5, (int)(this + 15), a6, a7, a8, a9);
        v11 != (uint32_t *)*(this + 51);
        v11 = (uint32_t *)*v11 )
  {
    result = sub_491DE0(a2, a3, a4, a5, a6, a7, a8, a9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x491EA0 sub_491EA0
// ------------------------------------------------------------
void /*thiscall*/ sub_491EA0(int this, int a2, int a3, int a4, float a5, int a6, float a7, float a8, int a9)
{
  uint32_t *v10; // eax
  uint32_t *v11; // esi

  if ( byte_790AD0 != 0 && *(uint8_t *)(this + 161) != 0 )
  {
    v10 = *(uint32_t **)(this + 204);
    v11 = (uint32_t *)*v10;
    if ( (uint32_t *)*v10 != v10 )
    {
      do
      {
        if ( (int)v11[2] >= 0 )
          break;
        sub_491EA0(a2, a3, a4, a5, a6, a7, a8, a9);
        v11 = (uint32_t *)*v11;
      }
      while ( v11 != *(uint32_t **)(this + 204) );
    }
    sub_491300((uint8_t *)this, a2, a3, a4, a5, this + 60, a6, a7, a8, a9);
    for ( ; v11 != *(uint32_t **)(this + 204); v11 = (uint32_t *)*v11 )
      sub_491EA0(a2, a3, a4, a5, a6, a7, a8, a9);
  }
}



// ------------------------------------------------------------
// 0x491F80 sub_491F80
// ------------------------------------------------------------
char /*thiscall*/ sub_491F80(int this, int a2, int a3, int a4, int a5, int a6)
{
  int v6; // ebx
  uint32_t **v7; // eax
  uint16_t v9; // cx
  uint32_t *v10; // esi

  v6 = a2;
  LOBYTE(v7) = -1;
  if ( a2 == -1 )
  {
    if ( a3 == -1 && a4 == -1 && a5 == -1 )
      return (char)v7;
    v6 = *(uint8_t *)(this + 92);
  }
  if ( a3 == -1 )
    a3 = *(uint8_t *)(this + 93);
  if ( a4 == -1 )
    a4 = *(uint8_t *)(this + 94);
  if ( a5 == -1 )
    a5 = *(uint8_t *)(this + 95);
  HIBYTE(v9) = a5;
  LOBYTE(v9) = a4;
  LOBYTE(v7) = a6;
  *(uint32_t *)(this + 92) = (uint8_t)v6 | (((uint8_t)a3 | (v9 << 8)) << 8);
  if ( (uint8_t)a6 != 0 )
  {
    v7 = *(uint32_t ***)(this + 204);
    v10 = *v7;
    if ( *v7 != v7 )
    {
      do
      {
        LOBYTE(v7) = sub_491F80(v6, a3, a4, a5, a6);
        v10 = (uint32_t *)*v10;
      }
      while ( v10 != *(uint32_t **)(this + 204) );
    }
  }
  return (char)v7;
}



// ------------------------------------------------------------
// 0x492030 sub_492030
// ------------------------------------------------------------
char /*thiscall*/ sub_492030(uint32_t *this, int a2, int a3, int a4)
{
  uint32_t **v5; // eax
  uint32_t *v6; // esi

  *(this + 26) = a3;
  LOBYTE(v5) = a4;
  *(this + 25) = a2;
  if ( (uint8_t)a4 != 0 )
  {
    v5 = (uint32_t **)*(this + 51);
    v6 = *v5;
    if ( *v5 != v5 )
    {
      do
      {
        LOBYTE(v5) = sub_492030(a2, a3, a4);
        v6 = (uint32_t *)*v6;
      }
      while ( v6 != (uint32_t *)*(this + 51) );
    }
  }
  return (char)v5;
}



// ------------------------------------------------------------
// 0x492080 sub_492080
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492080(int this, float a2)
{
  double v3; // st7
  uint32_t *result; // eax
  uint32_t *v5; // esi

  if ( *(float *)(this + 172) != a2 )
  {
    v3 = a2 - *(float *)(this + 172);
    *(float *)(this + 172) = a2;
    *(float *)(this + 88) = v3 + *(float *)(this + 88);
  }
  result = *(uint32_t **)(this + 204);
  v5 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_492080(a2);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4920E0 sub_4920E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4920E0(uint32_t *this, float a2, float a3)
{
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  unsigned int v8; // edx
  int v9; // eax
  int v10; // ecx
  uint32_t *result; // eax
  uint32_t *v12; // edi

  v4 = *(this + 11);
  if ( v4 != 0 )
    v5 = (*(this + 12) - v4) / 88;
  else
    v5 = 0;
  v6 = 0;
  if ( v5 >= 4 )
  {
    v7 = 0;
    v8 = ((unsigned int)(v5 - 4) >> 2) + 1;
    v6 = 4 * v8;
    do
    {
      *(float *)(*(this + 11) + v7 + 20) = a2;
      v7 += 352;
      --v8;
      *(float *)(*(this + 11) + v7 - 328) = a3;
      *(float *)(*(this + 11) + v7 - 244) = a2;
      *(float *)(*(this + 11) + v7 - 240) = a3;
      *(float *)(*(this + 11) + v7 - 156) = a2;
      *(float *)(*(this + 11) + v7 - 152) = a3;
      *(float *)(*(this + 11) + v7 - 68) = a2;
      *(float *)(*(this + 11) + v7 - 64) = a3;
    }
    while ( v8 != 0 );
  }
  if ( v6 < v5 )
  {
    v9 = 88 * v6;
    v10 = v5 - v6;
    do
    {
      *(float *)(*(this + 11) + v9 + 20) = a2;
      v9 += 88;
      --v10;
      *(float *)(*(this + 11) + v9 - 64) = a3;
    }
    while ( v10 != 0 );
  }
  result = (uint32_t *)*(this + 51);
  v12 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4920E0(a2, a3);
      v12 = (uint32_t *)*v12;
    }
    while ( v12 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4921E0 sub_4921E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4921E0(int *this, float a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int i; // edi
  int v7; // eax
  int j; // eax
  uint32_t *result; // eax
  uint32_t *v10; // edi

  v3 = *(this + 11);
  if ( v3 != 0 )
    v3 = (*(this + 12) - v3) / 88;
  if ( v3 > 0 )
  {
    v4 = *(this + 11);
    v5 = 0;
    for ( i = v3; i != 0; --i )
    {
      v7 = *(uint32_t *)(v5 + v4 + 60);
      if ( v7 != *(uint32_t *)(v5 + v4 + 64) )
      {
        do
        {
          v7 += 24;
          *(float *)(v7 - 24) = a2 * *(float *)(v7 - 24);
          *(float *)(v7 - 20) = a2 * *(float *)(v7 - 20);
          *(float *)(v7 - 16) = a2 * *(float *)(v7 - 16);
          *(float *)(v7 - 12) = a2 * *(float *)(v7 - 12);
          *(float *)(v7 - 8) = a2 * *(float *)(v7 - 8);
          *(float *)(v7 - 4) = a2 * *(float *)(v7 - 4);
        }
        while ( v7 != *(uint32_t *)(*(this + 11) + v5 + 64) );
      }
      v4 = *(this + 11);
      for ( j = *(uint32_t *)(v5 + v4 + 76); j != *(uint32_t *)(v5 + v4 + 80); v4 = *(this + 11) )
      {
        j += 24;
        *(float *)(j - 24) = a2 * *(float *)(j - 24);
        *(float *)(j - 20) = a2 * *(float *)(j - 20);
        *(float *)(j - 16) = a2 * *(float *)(j - 16);
        *(float *)(j - 12) = a2 * *(float *)(j - 12);
        *(float *)(j - 8) = a2 * *(float *)(j - 8);
        *(float *)(j - 4) = a2 * *(float *)(j - 4);
      }
      v5 += 88;
    }
  }
  result = (uint32_t *)*(this + 51);
  v10 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4921E0(a2);
      v10 = (uint32_t *)*v10;
    }
    while ( v10 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4922F0 sub_4922F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4922F0(uint32_t *this, float a2)
{
  int v2; // edx
  int i; // ecx
  int j; // eax
  int k; // eax

  v2 = *(this + 11);
  for ( i = *(this + 12); v2 != i; v2 += 88 )
  {
    *(float *)(v2 + 20) = a2 * *(float *)(v2 + 20);
    *(float *)(v2 + 24) = a2 * *(float *)(v2 + 24);
    for ( j = *(uint32_t *)(v2 + 60); j != *(uint32_t *)(v2 + 64); *(float *)(j - 4) = a2 * *(float *)(j - 4) )
    {
      j += 24;
      *(float *)(j - 24) = a2 * *(float *)(j - 24);
      *(float *)(j - 20) = a2 * *(float *)(j - 20);
      *(float *)(j - 16) = a2 * *(float *)(j - 16);
      *(float *)(j - 12) = a2 * *(float *)(j - 12);
      *(float *)(j - 8) = a2 * *(float *)(j - 8);
    }
    for ( k = *(uint32_t *)(v2 + 76); k != *(uint32_t *)(v2 + 80); *(float *)(k - 4) = a2 * *(float *)(k - 4) )
    {
      k += 24;
      *(float *)(k - 24) = a2 * *(float *)(k - 24);
      *(float *)(k - 20) = a2 * *(float *)(k - 20);
      *(float *)(k - 16) = a2 * *(float *)(k - 16);
      *(float *)(k - 12) = a2 * *(float *)(k - 12);
      *(float *)(k - 8) = a2 * *(float *)(k - 8);
    }
  }
}



// ------------------------------------------------------------
// 0x4923C0 sub_4923C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4923C0(uint32_t *this, int a2)
{
  int result; // eax
  int i; // ecx

  result = *(this + 11);
  for ( i = *(this + 12); result != i; result += 88 )
  {
    *(uint32_t *)(result + 20) = a2;
    *(uint32_t *)(result + 24) = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4923F0 sub_4923F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4923F0(uint32_t *this, float a2)
{
  int v2; // edx
  int v3; // ecx
  double v4; // st7
  int i; // eax
  int j; // eax

  v2 = *(this + 11);
  v3 = *(this + 12);
  if ( v2 != v3 )
  {
    v4 = 1.0 / a2;
    do
    {
      *(float *)(v2 + 20) = v4 * *(float *)(v2 + 20);
      *(float *)(v2 + 24) = v4 * *(float *)(v2 + 24);
      for ( i = *(uint32_t *)(v2 + 60); i != *(uint32_t *)(v2 + 64); *(float *)(i - 4) = v4 * *(float *)(i - 4) )
      {
        i += 24;
        *(float *)(i - 24) = v4 * *(float *)(i - 24);
        *(float *)(i - 20) = v4 * *(float *)(i - 20);
        *(float *)(i - 16) = v4 * *(float *)(i - 16);
        *(float *)(i - 12) = v4 * *(float *)(i - 12);
        *(float *)(i - 8) = v4 * *(float *)(i - 8);
      }
      for ( j = *(uint32_t *)(v2 + 76); j != *(uint32_t *)(v2 + 80); *(float *)(j - 4) = v4 * *(float *)(j - 4) )
      {
        j += 24;
        *(float *)(j - 24) = v4 * *(float *)(j - 24);
        *(float *)(j - 20) = v4 * *(float *)(j - 20);
        *(float *)(j - 16) = v4 * *(float *)(j - 16);
        *(float *)(j - 12) = v4 * *(float *)(j - 12);
        *(float *)(j - 8) = v4 * *(float *)(j - 8);
      }
      v2 += 88;
    }
    while ( v2 != v3 );
  }
}



// ------------------------------------------------------------
// 0x4924C0 sub_4924C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4924C0(int *this, int a2)
{
  int v3; // eax
  int *v4; // ebx
  int v5; // eax
  uint32_t *v6; // eax
  unsigned int v8; // [esp-8h] [ebp-10h]

  v3 = *(this + 11);
  if ( v3 != 0 )
    v3 = (*(this + 12) - v3) / 88;
  if ( a2 >= v3 )
    return 0;
  v4 = (int *)(*(this + 11) + 88 * a2);
  v5 = v4[1];
  if ( v5 != -1 )
  {
    v8 = v4[2];
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v5);
    *v4 = sub_418DD0(v6, v8);
  }
  return 88 * a2 + *(this + 11);
}



// ------------------------------------------------------------
// 0x492530 sub_492530
// ------------------------------------------------------------
int /*stdcall*/ sub_492530(int a1, int a2, int a3)
{
  return sub_4FF050(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x492550 sub_492550
// ------------------------------------------------------------
char /*thiscall*/ sub_492550(int this, int a2, int a3, int a4, float a5, int a6)
{
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // edx
  uint32_t *v13; // eax
  int v14; // ecx
  char result; // al
  int v16; // eax
  int v17; // [esp-10h] [ebp-20h]
  char v18; // [esp-Ch] [ebp-1Ch]
  int v19; // [esp-8h] [ebp-18h]
  unsigned int v20; // [esp-4h] [ebp-14h]
  int v21; // [esp-4h] [ebp-14h]
  int *v22; // [esp+20h] [ebp+10h]

  v8 = *(uint32_t **)(this + 204);
  v9 = (uint32_t *)*v8;
  if ( (uint32_t *)*v8 != v8 )
  {
    do
    {
      if ( (int)v9[2] >= 0 )
        break;
      sub_492550(a2, a3, a4, a5, a6);
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *(uint32_t **)(this + 204) );
  }
  v10 = *(uint32_t *)(this + 44);
  if ( v10 != 0 )
    v10 = (*(uint32_t *)(this + 48) - v10) / 88;
  if ( a6 >= v10 )
  {
    v14 = 0;
  }
  else
  {
    v11 = 88 * a6;
    v12 = 88 * a6 + *(uint32_t *)(this + 44);
    v22 = (int *)v12;
    if ( *(uint32_t *)(v12 + 4) != -1 )
    {
      v20 = *(uint32_t *)(v12 + 8);
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(
                        dword_8F84BC,
                        *(uint32_t *)(v12 + 4));
      *v22 = sub_418DD0(v13, v20);
      v11 = 88 * a6;
    }
    v14 = v11 + *(uint32_t *)(this + 44);
  }
  sub_4916E0(a2, a3, a4, a5, v14);
  result = *(uint8_t *)(this + 176);
  if ( result != 0 )
  {
    v21 = *(uint32_t *)(this + 192);
    v19 = *(uint32_t *)(this + 188);
    v18 = *(uint8_t *)(this + 184);
    v17 = *(uint32_t *)(this + 180);
    v16 = sub_4924C0((int *)this, a6);
    sub_4917A0(a2, a3, a4, a5, v16, v17, v18, v19, v21);
    result = *(uint8_t *)(this + 196);
    if ( result != 0 )
      *(uint8_t *)(this + 176) = 0;
  }
  for ( ; v9 != *(uint32_t **)(this + 204); v9 = (uint32_t *)*v9 )
    result = sub_492550(a2, a3, a4, a5, a6);
  return result;
}



// ------------------------------------------------------------
// 0x4926A0 sub_4926A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4926A0(int this)
{
  int v2; // ebx
  uint32_t *v3; // eax
  uint32_t *v4; // edi
  int i; // edi
  int result; // eax

  v2 = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint8_t *)(this + 14) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint8_t *)(this + 168) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint8_t *)(this + 170) = 0;
  sub_430B70(this + 60);
  v3 = *(uint32_t **)(this + 204);
  *(uint32_t *)(this + 148) = -1;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  v4 = (uint32_t *)*v3;
  if ( (uint32_t *)*v3 != v3 )
  {
    do
    {
      sub_4926A0(v4[3]);
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != *(uint32_t **)(this + 204) );
  }
  *(uint32_t *)(this + 36) = 0;
  for ( i = 0; ; i += 88 )
  {
    result = *(uint32_t *)(this + 44);
    if ( result != 0 )
      result = (*(uint32_t *)(this + 48) - result) / 88;
    if ( v2 >= result )
      break;
    ++v2;
    *(uint32_t *)(this + 36) += *(uint32_t *)(i + *(uint32_t *)(this + 44) + 48);
  }
  return result;
}



// ------------------------------------------------------------
// 0x492750 sub_492750
// ------------------------------------------------------------
int /*thiscall*/ sub_492750(int this, size_t *a2, uint32_t *a3)
{
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((size_t *)this, a2, 0, 0xFFFFFFFF);
  *(uint32_t *)(this + 28) = *a3;
  return this;
}



// ------------------------------------------------------------
// 0x492780 sub_492780
// ------------------------------------------------------------
int /*thiscall*/ sub_492780(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x1FFFFFFF - v2 < a2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x492810 sub_492810
// ------------------------------------------------------------
void /*noreturn*/ sub_492810()
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
// 0x492880 sub_492880
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492880(size_t *a1, size_t *a2, size_t *a3)
{
  size_t *v3; // esi
  size_t *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 8;
    v4 -= 8;
    sub_4014D0(v4, v3, 0, 0xFFFFFFFF);
    v4[7] = v3[7];
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4928C0 sub_4928C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4928C0(size_t *a1, size_t *a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((size_t *)v3, a1, 0, 0xFFFFFFFF);
      *(uint32_t *)(v3 + 28) = a1[7];
    }
    v3 += 32;
    LOBYTE(v7) = 0;
    a1 += 8;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x492980 sub_492980
// ------------------------------------------------------------
void **/*thiscall*/ sub_492980(void ***this, void *a2)
{
  void **v3; // ecx
  void **result; // eax
  uint32_t *v5; // ecx

  v3 = *(this + 51);
  result = (void **)*v3;
  if ( *v3 != v3 )
  {
    while ( result[3] != a2 )
    {
      result = (void **)*result;
      if ( result == v3 )
        return result;
    }
    v5 = result[3];
    if ( v5 != nullptr )
      v5[53] = 0;
    if ( result != *(this + 51) )
    {
      *(uint32_t *)result[1] = *result;
      *((uint32_t *)*result + 1) = result[1];
      j__free(result);
      result = (void **)((char *)*(this + 52) - 1);
      *(this + 52) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4929F0 sub_4929F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4929F0(int *this, int a2, unsigned int a3, uint32_t *Block)
{
  int result; // eax
  int v6; // edx
  int v7; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  unsigned int v12; // ecx
  int v14; // eax
  int v15; // eax
  unsigned int v16; // ecx
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  unsigned int v20; // edi
  void *v21; // ecx
  int v23; // edi
  int v24; // [esp-18h] [ebp-4Ch]
  int v25; // [esp-Ch] [ebp-40h]
  unsigned int v26; // [esp-8h] [ebp-3Ch]
  int v27; // [esp+0h] [ebp-34h] BYREF
  uint32_t v28[7]; // [esp+Ch] [ebp-28h] BYREF
  int v29; // [esp+30h] [ebp-4h]
  int v30; // [esp+3Ch] [ebp+8h]
  int v31; // [esp+40h] [ebp+Ch]
  char *Blocka; // [esp+44h] [ebp+10h]
  void *Blockb; // [esp+44h] [ebp+10h]

  result = (int)Block;
  v6 = Block[1];
  v7 = *(this + 1);
  v28[0] = *Block;
  v8 = Block[2];
  v28[1] = v6;
  v9 = Block[3];
  v28[2] = v8;
  v10 = Block[4];
  v28[3] = v9;
  v11 = Block[5];
  v28[6] = &v27;
  v28[4] = v10;
  v28[5] = v11;
  if ( v7 != 0 )
  {
    result = 715827883 * (*(this + 3) - v7);
    v12 = (*(this + 3) - v7) / 24;
  }
  else
  {
    v12 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v14 = (*(this + 2) - v7) / 24;
    else
      v14 = 0;
    if ( 178956970 - v14 < a3 )
      sub_430A90(this);
    if ( v7 != 0 )
      v15 = (*(this + 2) - v7) / 24;
    else
      v15 = 0;
    if ( v12 >= a3 + v15 )
    {
      v21 = (void *)*(this + 2);
      Blockb = v21;
      if ( ((int)v21 - a2) / 24 >= a3 )
      {
        v30 = (int)v21 - 24 * a3;
        *(this + 2) = sub_4FF050(v30, v21, v21);
        sub_504430(a2, v30, Blockb);
        return sub_4FEF50(a2, a2 + 24 * a3, v28);
      }
      else
      {
        sub_4FF050(a2, v21, a2 + 24 * a3);
        v26 = a3 - (*(this + 2) - a2) / 24;
        v25 = *(this + 2);
        v29 = 2;
        sub_504620(v25, v26, v28);
        v23 = 24 * a3 + *(this + 2);
        *(this + 2) = v23;
        return sub_4FEF50(a2, v23 - 24 * a3, v28);
      }
    }
    else
    {
      if ( 178956970 - (v12 >> 1) >= v12 )
        v16 = (v12 >> 1) + v12;
      else
        v16 = 0;
      if ( v7 != 0 )
        v17 = (*(this + 2) - v7) / 24;
      else
        v17 = 0;
      if ( v16 < a3 + v17 )
        v16 = a3 + sub_4FEF30(this);
      v18 = 24 * v16;
      Blocka = (char *)operator new(24 * v16);
      v24 = *(this + 1);
      v29 = 0;
      v31 = sub_4FF050(v24, a2, Blocka);
      sub_5044B0(v31, a3, v28);
      sub_4FF050(a2, *(this + 2), v31 + 24 * a3);
      v19 = *(this + 1);
      if ( v19 != 0 )
        v19 = (*(this + 2) - v19) / 24;
      v20 = v19 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v18];
      *(this + 2) = (int)&Blocka[24 * v20];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x492CC0 sub_492CC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492CC0(uint32_t *this, int a2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int v7; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *v9; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(a2 + 4);
  v10 = &v8;
  v9 = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(a2 + 8) - v2) / 24;
  if ( (uint8_t)sub_430BE0(v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(uint32_t *)(a2 + 8);
    v5 = *(uint32_t *)(a2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FF050(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x492D60 sub_492D60
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492D60(size_t *a1, size_t *a2, size_t *a3)
{
  size_t *i; // esi
  size_t result; // eax

  for ( i = a1; i != a2; i += 8 )
  {
    sub_4014D0(i, a3, 0, 0xFFFFFFFF);
    result = a3[7];
    i[7] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492DA0 sub_492DA0
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492DA0(size_t *a1, size_t *a2, size_t *a3)
{
  return sub_492880(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x492DC0 sub_492DC0
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492DC0(int a1, int a2, size_t *a3)
{
  int v3; // esi
  size_t result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = a1;
  v5[5] = v5;
  v5[4] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    v5[3] = v3;
    LOBYTE(v6) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((size_t *)v3, a3, 0, 0xFFFFFFFF);
      result = a3[7];
      *(uint32_t *)(v3 + 28) = result;
    }
    v3 += 32;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492E80 sub_492E80
// ------------------------------------------------------------
int /*thiscall*/ sub_492E80(int this, int a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *v7; // edi
  unsigned int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  int v11; // eax
  uint32_t *v12; // [esp+10h] [ebp+8h]

  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 24) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v7 = *(uint32_t **)(this + 4);
  if ( v7 != nullptr )
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 24;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
      v10 = (*(uint32_t *)(this + 12) - (int)v7) / 24;
    else
      v10 = 0;
    if ( v5 <= v10 )
    {
      v12 = (uint32_t *)(*(uint32_t *)(a2 + 4) + 24 * sub_4FEF30(this));
      sub_4919B0(*(uint32_t **)(a2 + 4), v12, v7);
      *(uint32_t *)(this + 8) = sub_4FF050(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
      j__free(*(void **)(this + 4));
    v11 = sub_4FEF30(a2);
    if ( (uint8_t)sub_430BE0(v11) != 0 )
      *(uint32_t *)(this + 8) = sub_492530(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  sub_48C4B0(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), v7);
  v9 = *(uint32_t *)(a2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 24 * ((*(uint32_t *)(a2 + 8) - v9) / 24);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x493000 sub_493000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493000(int *this, uint32_t *a2, int a3, uint32_t *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 24 != 0 )
    v6 = (a3 - v5) / 24;
  else
    v6 = 0;
  sub_4929F0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 24 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x493070 sub_493070
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493070(uint32_t *this, int a2)
{
  *this = *(uint32_t *)a2;
  *(this + 1) = *(uint32_t *)(a2 + 4);
  *(this + 2) = *(uint32_t *)(a2 + 8);
  *(this + 3) = *(uint32_t *)(a2 + 12);
  *(this + 4) = *(uint32_t *)(a2 + 16);
  *(this + 5) = *(uint32_t *)(a2 + 20);
  *(this + 6) = *(uint32_t *)(a2 + 24);
  *(this + 7) = *(uint32_t *)(a2 + 28);
  *(this + 8) = *(uint32_t *)(a2 + 32);
  *((uint8_t *)this + 36) = *(uint8_t *)(a2 + 36);
  *(this + 10) = *(uint32_t *)(a2 + 40);
  *(this + 11) = *(uint32_t *)(a2 + 44);
  *(this + 12) = *(uint32_t *)(a2 + 48);
  *(this + 13) = *(uint32_t *)(a2 + 52);
  sub_492CC0(this + 14, a2 + 56);
  sub_492CC0(this + 18, a2 + 72);
  return this;
}



// ------------------------------------------------------------
// 0x493120 sub_493120
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493120(uint32_t *this, int a2)
{
  *this = *(uint32_t *)a2;
  *(this + 1) = *(uint32_t *)(a2 + 4);
  *(this + 2) = *(uint32_t *)(a2 + 8);
  *(this + 3) = *(uint32_t *)(a2 + 12);
  *(this + 4) = *(uint32_t *)(a2 + 16);
  *(this + 5) = *(uint32_t *)(a2 + 20);
  *(this + 6) = *(uint32_t *)(a2 + 24);
  *(this + 7) = *(uint32_t *)(a2 + 28);
  *(this + 8) = *(uint32_t *)(a2 + 32);
  *((uint8_t *)this + 36) = *(uint8_t *)(a2 + 36);
  *(this + 10) = *(uint32_t *)(a2 + 40);
  *(this + 11) = *(uint32_t *)(a2 + 44);
  *(this + 12) = *(uint32_t *)(a2 + 48);
  *(this + 13) = *(uint32_t *)(a2 + 52);
  sub_492E80(a2 + 56);
  sub_492E80(a2 + 72);
  return this;
}



// ------------------------------------------------------------
// 0x4931A0 sub_4931A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4931A0(int *this, void *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  int result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 24;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 24 )
    return sub_493000((int)&Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = sub_5044B0(v5, 1, Block);
  *(this + 2) = v5 + 24;
  return result;
}



// ------------------------------------------------------------
// 0x493230 sub_493230
// ------------------------------------------------------------
int /*stdcall*/ sub_493230(int a1, int a2, size_t *a3)
{
  sub_492DC0(a1, a2, a3);
  return a1 + 32 * a2;
}



// ------------------------------------------------------------
// 0x493260 sub_493260
// ------------------------------------------------------------
void /*stdcall*/ sub_493260(char *a1, char *a2)
{
  char *i; // esi

  for ( i = a1; i != a2; i += 32 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x493290 sub_493290
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493290(uint32_t *a1, uint32_t *a2, int a3)
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = a1; i != a2; i += 22 )
    result = sub_493120(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x4932C0 sub_4932C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4932C0(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_493120(v4, v3);
    v3 += 88;
    v4 += 22;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x493300 sub_493300
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493300(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 88;
    v4 -= 22;
    sub_493120(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x493340 sub_493340
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493340(int a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      sub_493070(v3, a1);
    v3 += 22;
    LOBYTE(v7) = 0;
    a1 += 88;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x493400 sub_493400
// ------------------------------------------------------------
void /*thiscall*/ sub_493400(int this, int a2)
{
  int v3; // eax
  int v4; // edi

  if ( a2 != *(uint32_t *)(this + 148) )
  {
    v3 = *(uint32_t *)(this + 44);
    *(uint32_t *)(this + 148) = a2;
    v4 = *(uint32_t *)(this + 156);
    *(uint32_t *)(this + 152) = v4;
    *(uint32_t *)(this + 156) = v4
                            - (uint64_t)((double)*(int *)(88 * a2 + v3 + 48) / *(float *)(this + 164) * -100.0);
    sub_430B70(this + 60);
    sub_493120(88 * a2 + *(uint32_t *)(this + 44));
    *(uint32_t *)(this + 172) = 0;
  }
}



// ------------------------------------------------------------
// 0x493480 sub_493480
// ------------------------------------------------------------
void /*thiscall*/ sub_493480(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ecx
  unsigned int v6; // eax
  int v8; // edx
  int v9; // edx
  unsigned int v10; // eax
  int v11; // edx
  int v12; // eax
  char *v13; // ebx
  void *v14; // ecx
  int v15; // eax
  unsigned int v16; // edi
  void *v17; // eax
  int v18; // edi
  int v19; // edi
  int v20; // eax
  int v21; // [esp-18h] [ebp-64h]
  void *v22; // [esp-18h] [ebp-64h]
  int v23; // [esp-10h] [ebp-5Ch]
  int v24; // [esp-Ch] [ebp-58h]
  unsigned int v25; // [esp-8h] [ebp-54h]
  uint32_t v26[4]; // [esp+0h] [ebp-4Ch] BYREF
  void *Block; // [esp+10h] [ebp-3Ch]
  char *v28; // [esp+14h] [ebp-38h]
  char v29[4]; // [esp+18h] [ebp-34h] BYREF
  void *v30; // [esp+1Ch] [ebp-30h]
  int v31; // [esp+2Ch] [ebp-20h]
  unsigned int v32; // [esp+30h] [ebp-1Ch]
  int v33; // [esp+34h] [ebp-18h]
  int v34; // [esp+38h] [ebp-14h]
  uint32_t *v35; // [esp+3Ch] [ebp-10h]
  int v36; // [esp+48h] [ebp-4h]
  int v37; // [esp+58h] [ebp+Ch]

  v35 = v26;
  v34 = dword_796E50;
  v26[3] = this;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  sub_4014D0((std::_String_base *)v29, a4, 0, -1);
  v33 = *(uint32_t *)(a4 + 28);
  v5 = *(this + 1);
  v36 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) >> 5;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) >> 5;
    else
      v8 = 0;
    if ( 0x7FFFFFF - v8 < a3 )
      sub_492810(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) >> 5;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v17 = (void *)*(this + 2);
      Block = v17;
      if ( ((int)v17 - a2) >> 5 >= a3 )
      {
        v19 = (int)v17 - 32 * a3;
        v20 = sub_4928C0(v19, (int)v17, (int)v17);
        v22 = Block;
        *(this + 2) = v20;
        sub_492DA0(a2, v19, v22);
        sub_492D60(a2, a2 + 32 * a3, v29);
      }
      else
      {
        sub_4928C0(a2, (int)v17, a2 + 32 * a3);
        v25 = a3 - ((*(this + 2) - a2) >> 5);
        v24 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_493230(v24, v25, v29);
        v18 = 32 * a3 + *(this + 2);
        *(this + 2) = v18;
        v36 = 0;
        sub_492D60(a2, v18 - 32 * a3, v29);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) >> 5;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(this + 2) - v5) >> 5;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v37 = 32 * v10;
      v13 = (char *)operator new(32 * v10);
      v21 = *(this + 1);
      Block = v13;
      v28 = v13;
      LOBYTE(v36) = 1;
      v28 = (char *)sub_4928C0(v21, a2, (int)v13);
      sub_492DC0((int)v28, a3, (int)v29);
      v23 = *(this + 2);
      v28 += 32 * a3;
      sub_4928C0(a2, v23, (int)v28);
      v14 = (void *)*(this + 1);
      if ( v14 != nullptr )
        v15 = (*(this + 2) - (int)v14) >> 5;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != nullptr )
      {
        sub_493260(v14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v13[v37];
      *(this + 2) = (int)&v13[32 * v16];
      *(this + 1) = (int)v13;
    }
  }
  if ( v32 >= 0x10 )
    j__free(v30);
}


// ------------------------------------------------------------
// 0x493740 sub_493740
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493740(int a1, int a2, uint32_t *a3)
{
  return sub_4932C0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x493760 sub_493760
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493760(int a1, int a2, uint32_t *a3)
{
  return sub_493300(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x493780 sub_493780
// ------------------------------------------------------------
void /*cdecl*/ sub_493780(uint32_t *a1, int a2, int a3)
{
  uint32_t *v3; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v5[4] = v5;
  v5[3] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( v3 != nullptr )
      sub_493070(v3, a3);
    --a2;
    v3 += 22;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x493840 sub_493840
// ------------------------------------------------------------
char /*thiscall*/ sub_493840(int this)
{
  int v2; // ecx
  int v3; // ebx
  unsigned int v4; // eax
  int v5; // edi
  int v6; // eax

  v2 = *(uint32_t *)(this + 212);
  if ( v2 != 0 )
    v3 = sub_4910A0(v2);
  else
    v3 = *(uint32_t *)(this + 32);
  LOBYTE(v4) = *(uint8_t *)(this + 170);
  v5 = *(uint32_t *)(this + 148);
  if ( (uint8_t)v4 == 0 )
  {
    while ( v3 >= *(uint32_t *)(this + 156) )
    {
      v6 = *(uint32_t *)(this + 44);
      if ( v6 != 0 )
        v6 = (*(uint32_t *)(this + 48) - v6) / 88;
      if ( v5 == v6 - 1 )
      {
        LOBYTE(v4) = *(uint8_t *)(this + 160);
        if ( (uint8_t)v4 == 0 )
        {
          *(uint8_t *)(this + 170) = 1;
          return v4;
        }
        v4 = *(uint32_t *)(this + 44);
        if ( v4 == 0 )
          return v4;
        v4 = (int)(*(uint32_t *)(this + 48) - v4) / 88;
        if ( v4 <= 1 )
          return v4;
        v5 = 0;
      }
      else
      {
        ++v5;
      }
      sub_493400(this, v5);
      LOBYTE(v4) = *(uint8_t *)(this + 170);
      if ( (uint8_t)v4 != 0 )
        return v4;
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4938F0 sub_4938F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4938F0(int this)
{
  int v2; // ecx
  char v3; // al
  uint32_t *result; // eax
  uint32_t *v5; // esi

  v2 = *(uint32_t *)(this + 212);
  if ( v2 != 0 )
    v3 = sub_4910C0(v2);
  else
    v3 = *(uint8_t *)(this + 169);
  if ( v3 == 0 && sub_4910E0(this) != 0 || *(uint32_t *)(this + 148) == -1 )
  {
    sub_493840(this);
    sub_4919D0(this);
  }
  result = *(uint32_t **)(this + 204);
  v5 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4938F0(v5[3]);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x493960 sub_493960
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493960(int *this, uint32_t *a2, uint32_t *a3, int a4)
{
  uint32_t *v5; // ecx
  uint32_t *v6; // eax
  uint32_t *v7; // ebx
  uint32_t *v8; // edi
  uint32_t *i; // esi
  int *v11; // [esp+4h] [ebp-4h]

  v5 = a3;
  v11 = this;
  if ( a3 != (uint32_t *)a4 )
  {
    v6 = sub_4932C0(a4, *(this + 2), a3);
    v7 = (uint32_t *)*(this + 2);
    v8 = v6;
    for ( i = v6; i != v7; i += 22 )
      sub_42AA10(i);
    v5 = a3;
    v11[2] = (int)v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x4939C0 sub_4939C0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4939C0(int a1, int a2, uint32_t *a3)
{
  return sub_493340(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4939E0 sub_4939E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4939E0(int this, char a2)
{
  char result; // al
  char v4; // bl
  int v5; // edi

  result = a2;
  v4 = *(uint8_t *)(this + 169);
  if ( a2 != v4 )
  {
    if ( a2 != 0 )
    {
      result = sub_4938F0(this);
      *(uint8_t *)(this + 169) = a2;
    }
    else
    {
      if ( *(uint32_t *)(this + 212) != 0 )
        v5 = sub_4910A0();
      else
        v5 = *(uint32_t *)(this + 32);
      sub_4926A0(this);
      *(uint32_t *)(this + 28) = v5;
      sub_4910E0(this);
      result = sub_4939E0(v4);
      *(uint8_t *)(this + 169) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x493A60 sub_493A60
// ------------------------------------------------------------
char /*thiscall*/ sub_493A60(int this, int a2)
{
  int v3; // ecx
  char v4; // al
  int v5; // eax
  char v7; // [esp+4h] [ebp-4h]

  v7 = *(uint8_t *)(this + 169);
  sub_4926A0(this);
  *(uint32_t *)(this + 28) = a2;
  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);
  v3 = *(uint32_t *)(this + 212);
  if ( v3 != 0 )
    v4 = sub_4910C0(v3);
  else
    v4 = *(uint8_t *)(this + 169);
  if ( v4 == 0 )
  {
    v5 = *(uint32_t *)(this + 28) + sub_699000(this);
    if ( v5 != *(uint32_t *)(this + 32) )
      *(uint32_t *)(this + 32) = v5;
  }
  return sub_4939E0(this, v7);
}



// ------------------------------------------------------------
// 0x493AD0 sub_493AD0
// ------------------------------------------------------------
void /*thiscall*/ sub_493AD0(int this, size_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 5;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 5 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_492DC0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 32;
  }
  else
  {
    sub_493480(this, *(size_t **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x493B40 sub_493B40
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_493B40(uint32_t *a1, int a2, int a3)
{
  sub_493780(a1, a2, a3);
  return &a1[22 * a2];
}



// ------------------------------------------------------------
// 0x493B70 sub_493B70
// ------------------------------------------------------------
char /*thiscall*/ sub_493B70(int this)
{
  int v2; // ecx
  char v3; // al
  int v4; // eax

  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);
  v2 = *(uint32_t *)(this + 212);
  if ( v2 != 0 )
    v3 = sub_4910C0(v2);
  else
    v3 = *(uint8_t *)(this + 169);
  if ( v3 == 0 )
  {
    v4 = *(uint32_t *)(this + 28) + sub_699000(this);
    if ( v4 != *(uint32_t *)(this + 32) )
      *(uint32_t *)(this + 32) = v4;
  }
  return sub_493A60(this, *(uint32_t *)(this + 32));
}



// ------------------------------------------------------------
// 0x493BD0 sub_493BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_493BD0(int this)
{
  int result; // eax

  sub_699070(1);
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_42AF40(this + 40);
  sub_430B70(this + 60);
  *(uint32_t *)(this + 148) = -1;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint8_t *)(this + 160) = 0;
  *(uint8_t *)(this + 161) = 1;
  *(uint32_t *)(this + 164) = 1120403456;
  *(uint8_t *)(this + 168) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint8_t *)(this + 170) = 0;
  *(uint8_t *)(this + 56) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint8_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = -1;
  *(uint8_t *)(this + 196) = 0;
  result = sub_6569D0(this + 200);
  *(uint32_t *)(this + 212) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x493C80 sub_493C80
// ------------------------------------------------------------
void ***/*thiscall*/ sub_493C80(void ****this)
{
  void ***v2; // ecx
  void ****v3; // ecx
  void ***v4; // eax
  void ****v5; // ecx
  void ***result; // eax
  bool v7; // zf
  void ***v8; // edi

  sub_42AF40(this + 10);
  sub_430B70(this + 15);
  v2 = *(this + 53);
  if ( v2 != nullptr )
    sub_492980(v2, this);
  v3 = (void ****)*(this + 51);
  v4 = *v3;
  if ( *v3 != (void ***)v3 )
  {
    do
    {
      v4[3][53] = nullptr;
      v4 = (void ***)*v4;
    }
    while ( v4 != *(this + 51) );
  }
  v5 = (void ****)*(this + 51);
  result = *v5;
  *v5 = (void ***)v5;
  (*(this + 51))[1] = (void **)*(this + 51);
  v7 = result == *(this + 51);
  *(this + 52) = nullptr;
  if ( !v7 )
  {
    do
    {
      v8 = (void ***)*result;
      j__free(result);
      result = v8;
    }
    while ( v8 != *(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x493D00 sub_493D00
// ------------------------------------------------------------
void /*thiscall*/ sub_493D00(int this, float a2)
{
  double v3; // st7
  uint32_t **v4; // eax
  uint32_t *v5; // esi

  if ( a2 == 0.0 )
    a2 = 1.0;
  if ( a2 != *(float *)(this + 164) )
  {
    v3 = *(float *)(this + 164);
    *(float *)(this + 164) = a2;
    if ( *(uint32_t *)(this + 212) != 0 )
      sub_493B70(this);
    else
      sub_493A60(this, (uint64_t)((double)*(int *)(this + 32) / a2 * v3));
    v4 = *(uint32_t ***)(this + 204);
    v5 = *v4;
    if ( *v4 != v4 )
    {
      do
      {
        sub_493D00(a2);
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != *(uint32_t **)(this + 204) );
    }
    sub_4938F0(this);
  }
}



// ------------------------------------------------------------
// 0x493DB0 sub_493DB0
// ------------------------------------------------------------
int /*thiscall*/ sub_493DB0(int this, int a2)
{
  int v3; // eax
  unsigned int v4; // ecx
  uint32_t *v6; // ebx
  unsigned int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  int v11; // edi
  int v12; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) / 88) == 0 )
  {
    sub_42AF40(this);
    return this;
  }
  v6 = *(uint32_t **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) / 88;
  else
    v7 = 0;
  if ( v4 > v7 )
  {
    if ( v6 != nullptr )
      v10 = (*(uint32_t *)(this + 12) - (int)v6) / 88;
    else
      v10 = 0;
    if ( v4 <= v10 )
    {
      v11 = *(uint32_t *)(a2 + 4) + 88 * sub_42FC70(this);
      sub_493740(*(uint32_t *)(a2 + 4), v11, v6);
      *(uint32_t *)(this + 8) = sub_493340(v11, *(uint32_t *)(a2 + 8), *(uint32_t **)(this + 8));
      return this;
    }
    if ( v6 != nullptr )
    {
      sub_42AF10(v6, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v12 = sub_42FC70(a2);
    if ( (uint8_t)sub_430C30(v12) != 0 )
      *(uint32_t *)(this + 8) = sub_4939C0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  v8 = sub_4932C0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), v6);
  sub_42AF10(v8, *(uint32_t *)(this + 8));
  v9 = *(uint32_t *)(a2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 88 * ((*(uint32_t *)(a2 + 8) - v9) / 88);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x493F30 sub_493F30
// ------------------------------------------------------------
void /*thiscall*/ sub_493F30(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v18; // edi
  int v19; // [esp-18h] [ebp-94h]
  int v20; // [esp-Ch] [ebp-88h]
  unsigned int v21; // [esp-8h] [ebp-84h]
  int v22; // [esp+0h] [ebp-7Ch] BYREF
  uint8_t v23[60]; // [esp+Ch] [ebp-70h] BYREF
  void *v24; // [esp+48h] [ebp-34h]
  void *v25; // [esp+58h] [ebp-24h]
  int v26; // [esp+5Ch] [ebp-20h]
  int v27; // [esp+60h] [ebp-1Ch]
  void *Block; // [esp+64h] [ebp-18h]
  int *v29; // [esp+68h] [ebp-14h]
  int *v30; // [esp+6Ch] [ebp-10h]
  int v31; // [esp+78h] [ebp-4h]
  int v32; // [esp+84h] [ebp+8h]
  int v33; // [esp+88h] [ebp+Ch]
  int v34; // [esp+8Ch] [ebp+10h]
  int v35; // [esp+8Ch] [ebp+10h]

  v30 = &v22;
  v29 = this;
  sub_493070(a4);
  v5 = *(this + 1);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 88;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 88;
    else
      v8 = 0;
    if ( 48806446 - v8 < a3 )
      sub_430A90(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 88;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v35 = v16;
      if ( (v16 - a2) / 88 >= a3 )
      {
        v32 = v16 - 88 * a3;
        *(this + 2) = sub_493340(v32, v16, v16);
        sub_493760(a2, v32, v35);
        sub_493290(a2, a2 + 88 * a3, v23);
      }
      else
      {
        sub_493340(a2, v16, a2 + 88 * a3);
        v21 = a3 - (*(this + 2) - a2) / 88;
        v20 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_493B40(v20, v21, v23);
        v18 = 88 * a3 + *(this + 2);
        *(this + 2) = v18;
        v31 = 0;
        sub_493290(a2, v18 - 88 * a3, v23);
      }
    }
    else
    {
      if ( 48806446 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 88;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_42FC70(this);
      v34 = 88 * v10;
      v12 = (char *)operator new(88 * v10);
      v19 = *(this + 1);
      Block = v12;
      LOBYTE(v31) = 1;
      v33 = sub_493340(v19, a2, v12);
      sub_493780(v33, a3, v23);
      sub_493340(a2, *(this + 2), 88 * a3 + v33);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 88;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_42AF10(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[88 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v25 != nullptr )
    j__free(v25);
  v25 = nullptr;
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )
    j__free(v24);
}


// ------------------------------------------------------------
// 0x494240 sub_494240
// ------------------------------------------------------------
void /*thiscall*/ sub_494240(int this, int a2, int a3)
{
  uint32_t *v4; // eax
  uint32_t *v5; // esi
  bool v6; // zf
  int v7; // edi
  uint32_t v8[2]; // [esp+4h] [ebp-8h] BYREF

  if ( a3 != 0 )
  {
    v8[1] = a3;
    v4 = *(uint32_t **)(this + 204);
    v5 = (uint32_t *)*v4;
    v6 = *v4 == (uint32_t)v4;
    v8[0] = a2;
    if ( !v6 )
    {
      do
      {
        if ( v5[2] > a2 )
          break;
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != v4 );
    }
    v7 = sub_52DAA0(v5, v5[1], v8);
    sub_492780(1);
    v5[1] = v7;
    **(uint32_t **)(v7 + 4) = v7;
    *(uint32_t *)(a3 + 212) = this;
    sub_4926A0(a3);
    sub_493D00(a3, *(float *)(this + 164));
  }
}



// ------------------------------------------------------------
// 0x4942D0 sub_4942D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4942D0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // esi
  int v4; // ebx
  uint32_t **v5; // ecx
  uint32_t *result; // eax
  bool v7; // zf
  uint32_t *v8; // esi

  v2 = (uint32_t *)*(this + 51);
  v3 = (uint32_t *)*v2;
  if ( (uint32_t *)*v2 != v2 )
  {
    do
    {
      *(uint32_t *)(v3[3] + 212) = 0;
      v4 = v3[3];
      if ( v4 != 0 )
      {
        sub_42AF90((void **)v3[3]);
        sub_657740(v4, 228);
      }
      v3[3] = 0;
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 51) );
  }
  v5 = (uint32_t **)*(this + 51);
  result = *v5;
  *v5 = v5;
  *(uint32_t *)(*(this + 51) + 4) = *(this + 51);
  v7 = result == (uint32_t *)*(this + 51);
  *(this + 52) = 0;
  if ( !v7 )
  {
    do
    {
      v8 = (uint32_t *)*result;
      j__free(result);
      result = v8;
    }
    while ( v8 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x494370 sub_494370
// ------------------------------------------------------------
void /*thiscall*/ sub_494370(int this, int a2)
{
  int v2; // edi
  unsigned int v3; // ebx
  int v4; // eax
  int *v5; // esi
  uint32_t *v6; // eax
  unsigned int v7; // [esp-Ch] [ebp-14h]
  int i; // [esp+10h] [ebp+8h]

  if ( a2 != 0 )
  {
    *(uint8_t *)(this + 160) = *(uint8_t *)(a2 + 160);
    v2 = this + 40;
    *(uint8_t *)(this + 161) = *(uint8_t *)(a2 + 161);
    sub_42AF40(this + 40);
    sub_493DB0(v2, a2 + 40);
    v3 = 0;
    for ( i = 0; ; i += 88 )
    {
      v4 = *(uint32_t *)(v2 + 4);
      if ( v4 == 0 || v3 >= (*(uint32_t *)(v2 + 8) - v4) / 88 )
        break;
      v5 = (int *)(*(uint32_t *)(this + 44) + i);
      if ( v5[1] != -1 )
      {
        v7 = v5[2];
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v5[1]);
        *v5 = sub_418DD0(v6, v7);
      }
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x494420 sub_494420
// ------------------------------------------------------------
void /*thiscall*/ sub_494420(
        int *this,
        unsigned int a2,
        char a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        void *a18,
        int a19,
        int a20,
        int a21,
        void *Block,
        int a23,
        int a24)
{
  int v24; // edi
  unsigned int v25; // eax
  int v26; // eax

  v24 = *(this + 1);
  if ( v24 != 0 )
    v25 = (*(this + 2) - v24) / 88;
  else
    v25 = 0;
  if ( v25 >= a2 )
  {
    if ( v24 != 0 && a2 < (*(this + 2) - v24) / 88 )
      sub_493960(this, &a2, (uint32_t *)(v24 + 88 * a2), *(this + 2));
  }
  else
  {
    if ( v24 != 0 )
      v26 = (*(this + 2) - v24) / 88;
    else
      v26 = 0;
    sub_493F30(this, (char *)*(this + 2), a2 - v26, (int)&a3);
  }
  if ( Block != nullptr )
    j__free(Block);
  if ( a18 != nullptr )
    j__free(a18);
}



// ------------------------------------------------------------
// 0x494500 sub_494500
// ------------------------------------------------------------
int /*thiscall*/ sub_494500(int *this, int a2)
{
  int result; // eax
  uint32_t *v4; // esi
  int v5; // edi
  uint32_t *v6; // edi

  result = *(this + 51);
  v4 = *(uint32_t **)result;
  if ( *(uint32_t *)result != result )
  {
    do
    {
      result = v4[2];
      if ( result == a2 )
      {
        result = v4[3];
        *(uint32_t *)(result + 212) = 0;
        v5 = v4[3];
        if ( v5 != 0 )
        {
          sub_42AF90((void **)v4[3]);
          result = sub_657740(v5, 228);
        }
        v4[3] = 0;
        v6 = (uint32_t *)*v4;
        if ( v4 != (uint32_t *)*(this + 51) )
        {
          *(uint32_t *)v4[1] = v6;
          *(uint32_t *)(*v4 + 4) = v4[1];
          j__free(v4);
          result = *(this + 52) - 1;
          *(this + 52) = result;
        }
        v4 = v6;
      }
      else
      {
        if ( result > a2 )
          return result;
        v4 = (uint32_t *)*v4;
      }
    }
    while ( v4 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4945A0 sub_4945A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4945A0(int *this, unsigned int a2)
{
  int v3[15]; // [esp-58h] [ebp-70h] BYREF
  void *v4; // [esp-1Ch] [ebp-34h]
  int v5; // [esp-18h] [ebp-30h]
  int v6; // [esp-14h] [ebp-2Ch]
  int v7; // [esp-10h] [ebp-28h]
  void *v8; // [esp-Ch] [ebp-24h]
  int v9; // [esp-8h] [ebp-20h]
  int v10; // [esp-4h] [ebp-1Ch]
  int *v11; // [esp+8h] [ebp-10h]
  int v12; // [esp+14h] [ebp-4h]

  v11 = v3;
  v4 = nullptr;
  v5 = 0;
  v6 = 0;
  v8 = nullptr;
  v9 = 0;
  v10 = 0;
  sub_430B70(v3);
  v12 = -1;
  sub_494420(
    this,
    a2,
    v3[0],
    v3[1],
    v3[2],
    v3[3],
    v3[4],
    v3[5],
    v3[6],
    v3[7],
    v3[8],
    v3[9],
    v3[10],
    v3[11],
    v3[12],
    v3[13],
    v3[14],
    v4,
    v5,
    v6,
    v7,
    v8,
    v9,
    v10);
}



// ------------------------------------------------------------
// 0x494610 sub_494610
// ------------------------------------------------------------
int /*thiscall*/ sub_494610(int *this, unsigned int a2)
{
  sub_4945A0(this + 10, a2);
  return sub_4926A0((int)this);
}



// ------------------------------------------------------------
// 0x494630 sub_494630
// ------------------------------------------------------------
int /*thiscall*/ sub_494630(int this, int a2)
{
  sub_4945A0((int *)(this + 40), 1u);
  **(uint32_t **)(this + 44) = a2;
  *(uint32_t *)(*(uint32_t *)(this + 44) + 12) = *(uint32_t *)(a2 + 20) / -2;
  *(uint32_t *)(*(uint32_t *)(this + 44) + 16) = *(uint32_t *)(a2 + 24) / -2;
  return sub_4926A0(this);
}



// ------------------------------------------------------------
// 0x494680 sub_494680
// ------------------------------------------------------------
char /*thiscall*/ sub_494680(uint8_t *this, char ArgList, int a3, char a4, int a5, int a6, int a7)
{
  uint8_t *v7; // esi
  char result; // al
  int v9; // edi
  int v10; // esi
  int v11; // edi
  int v12; // eax
  void **v13; // eax
  void **v14; // eax
  int v15; // eax
  uint8_t v16; // bl
  uint16_t v17; // dx
  uint8_t v18; // bl
  bool v19; // cc
  char v20[32]; // [esp+4h] [ebp-290h] BYREF
  float v21[6]; // [esp+24h] [ebp-270h] BYREF
  uint8_t *v22; // [esp+3Ch] [ebp-258h]
  int v23; // [esp+40h] [ebp-254h]
  int v24; // [esp+44h] [ebp-250h]
  int v25; // [esp+48h] [ebp-24Ch]
  char Buffer[256]; // [esp+4Ch] [ebp-248h] BYREF
  char Src[256]; // [esp+14Ch] [ebp-148h] BYREF
  char v28[4]; // [esp+24Ch] [ebp-48h] BYREF
  void *Block[4]; // [esp+250h] [ebp-44h] BYREF
  int v30; // [esp+260h] [ebp-34h]
  unsigned int v31; // [esp+264h] [ebp-30h]
  char v32[4]; // [esp+268h] [ebp-2Ch] BYREF
  void *v33; // [esp+26Ch] [ebp-28h]
  unsigned int v34; // [esp+27Ch] [ebp-18h]
  unsigned int v35; // [esp+280h] [ebp-14h]
  int v36; // [esp+284h] [ebp-10h]
  int v37; // [esp+290h] [ebp-4h]
  int ArgLista; // [esp+29Ch] [ebp+8h]

  v36 = dword_796E50;
  v7 = this;
  v22 = this;
  result = sub_442A10(ArgList, a3);
  if ( result == 0 )
    return result;
  v35 = 15;
  v34 = 0;
  LOBYTE(v33) = 0;
  v37 = 1;
  v31 = 15;
  v30 = 0;
  LOBYTE(Block[0]) = 0;
  if ( (uint8_t)sub_443430(v32) == 0 || sub_40BF00((std::_String_base *)v32, 0, v34, "[LOOP]", 6u) != 0 )
  {
    v31 = 15;
    v30 = 0;
    LOBYTE(Block[0]) = 0;
    if ( v35 >= 0x10 )
      j__free(v33);
    return 0;
  }
  v7[160] = sub_4423D0(0) != 0;
  if ( (uint8_t)sub_443430(v32) == 0
    || (uint8_t)sub_423340(v32, "[SHADOW]") != 0
    || (v7[161] = sub_4423D0(0) != 0, (uint8_t)sub_443430(v32) == 0)
    || (uint8_t)sub_423340(v32, "[FRAME MAX]") != 0
    || (v9 = sub_4423D0(0), v24 = v9, sub_4945A0(v9), (uint8_t)sub_443430(v32) == 0)
    || (uint8_t)sub_423340(v32, "[FRAME000]") != 0 )
  {
LABEL_66:
    sub_501490(v28);
    sub_501490(v32);
    return 0;
  }
  v25 = 0;
  if ( v9 > 0 )
  {
    ArgLista = 0;
    while ( 1 )
    {
      v10 = ArgLista + *((uint32_t *)v7 + 11);
      sub_430B70(v10);
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[IMAGE]") != 0 )
        goto LABEL_66;
      sub_443370();
      v11 = sub_4423D0(0);
      a3 = v11;
      if ( (uint8_t)sub_423340(v28, szPassword) != 0 )
      {
        if ( a4 == 0 )
        {
          v15 = sub_4BC700(v28);
LABEL_25:
          *(uint32_t *)(v10 + 8) = v11;
          *(uint32_t *)(v10 + 4) = v15;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v15);
          *(uint32_t *)v10 = sub_418DD0(v11);
          goto LABEL_26;
        }
        if ( a5 == 0 )
        {
          v14 = (void **)Block[0];
          if ( v31 < 0x10 )
            v14 = Block;
          sprintf(Src, (const char *const)v14, a6, a7);
          sub_406D60(Src);
          v15 = sub_4BC700(v28);
          goto LABEL_25;
        }
        *(uint32_t *)v10 = 0;
        v12 = sub_492750(v28, &a3);
        LOBYTE(v37) = 2;
        sub_493AD0(v12);
        LOBYTE(v37) = 1;
        sub_501490(v20);
        v13 = (void **)Block[0];
        if ( v31 < 0x10 )
          v13 = Block;
        sprintf(Buffer, (const char *const)v13, a6, a7);
        sub_406D60(Buffer);
        *(uint32_t *)(v10 + 4) = sub_4BC700(v28);
        *(uint32_t *)(v10 + 8) = v11;
      }
LABEL_26:
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE POS]") != 0 )
        goto LABEL_66;
      *(uint32_t *)(v10 + 12) = sub_4423D0(0);
      *(uint32_t *)(v10 + 16) = sub_4423D0(0);
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE RATE]") != 0 )
        goto LABEL_66;
      *(float *)(v10 + 20) = sub_442480(0);
      *(float *)(v10 + 24) = sub_442480(0);
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE ROTATE]") != 0 )
        goto LABEL_66;
      *(float *)(v10 + 28) = sub_442480(0);
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[RGBA]") != 0 )
        goto LABEL_66;
      v16 = sub_4423D0(0);
      a3 = sub_4423D0(0);
      v23 = sub_4423D0(0);
      HIBYTE(v17) = sub_4423D0(0);
      LOBYTE(v17) = v23;
      *(uint32_t *)(v10 + 32) = v16 | (((uint8_t)a3 | (v17 << 8)) << 8);
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[INTERPOLATION]") != 0 )
        goto LABEL_66;
      *(uint8_t *)(v10 + 36) = sub_4423D0(0) != 0;
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[GRAPHIC EFFECT]") != 0 )
        goto LABEL_66;
      sub_443370();
      if ( (uint8_t)sub_423300(v28, "NONE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 0;
      }
      else if ( (uint8_t)sub_423300(v28, "DODGE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 1;
      }
      else if ( (uint8_t)sub_423300(v28, "LINEARDODGE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 2;
      }
      else if ( (uint8_t)sub_423300(v28, "DARK") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 3;
      }
      else if ( (uint8_t)sub_423300(v28, &off_6CAF88) != 0 )
      {
        *(uint32_t *)(v10 + 40) = 4;
      }
      else if ( (uint8_t)sub_423300(v28, "MONOCHROME") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 5;
        v18 = sub_4423D0(0);
        a3 = sub_4423D0(0);
        *(uint32_t *)(v10 + 44) = v18 | (((uint8_t)a3 | ((sub_4423D0(0) | 0xFFFFFF00) << 8)) << 8);
      }
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[DELAY]") != 0 )
        goto LABEL_66;
      *(uint32_t *)(v10 + 48) = sub_4423D0(0);
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[DAMAGE TYPE]") != 0 )
        goto LABEL_66;
      sub_443370();
      if ( (uint8_t)sub_423300(v28, "NORMAL") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 0;
      }
      else if ( (uint8_t)sub_423300(v28, "SUPERARMOR") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 1;
      }
      else if ( (uint8_t)sub_423300(v28, "UNBREAKABLE") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 2;
      }
      while ( (uint8_t)sub_443430(v32) != 0 )
      {
        if ( (uint8_t)sub_423340(v32, "[ATTACK BOX]") != 0
          && (uint8_t)sub_423340(v32, "[DAMAGE BOX]") != 0 )
        {
          break;
        }
        a3 = sub_4423D0(0);
        v21[0] = (float)a3;
        a3 = sub_4423D0(0);
        v21[1] = (float)a3;
        a3 = sub_4423D0(0);
        v21[2] = (float)a3;
        a3 = sub_4423D0(0);
        v21[3] = (float)a3;
        a3 = sub_4423D0(0);
        v21[4] = (float)a3;
        a3 = sub_4423D0(0);
        v21[5] = (float)a3;
        sub_423300(v32, "[ATTACK BOX]");
        sub_4931A0(v21);
      }
      v19 = ++v25 < v24;
      ArgLista += 88;
      if ( !v19 )
        break;
      v7 = v22;
    }
  }
  sub_501490(v28);
  sub_501490(v32);
  return 1;
}


// ------------------------------------------------------------
// 0x494E40 sub_494E40
// ------------------------------------------------------------
int /*thiscall*/ sub_494E40(uint8_t *this, const char *a2, const char *ArgList, char a4, int a5, int a6, int a7, int a8)
{
  int v8; // esi
  int v9; // eax

  v8 = (int)this;
  if ( (uint8_t)a5 != 0 && (a7 == -1 || a8 == -1) )
    LOBYTE(a5) = 0;
  if ( a4 != 0 )
  {
    if ( strcmp(a2, szPassword) == 0 )
      v9 = sub_4F3BA0(ArgList, a5, a7, a8);
    else
      v9 = sub_4F3D60((char)a2, (int)ArgList, a5, a7, a8);
    if ( v9 == 0 )
      return off_77F3FC("ANIMATION CREATE FAIL1! FILENAME[%s]", ArgList);
    v8 = (int)this;
    sub_494370(v9);
  }
  else if ( sub_494680(this, (char)a2, (int)ArgList, a5, a6, a7, a8) == 0 )
  {
    return off_77F3FC("ANIMATION CREATE FAIL2! FILENAME[%s]", ArgList);
  }
  return sub_4926A0(v8);
}



// ------------------------------------------------------------
// 0x494F20 sub_494F20
// ------------------------------------------------------------
void /*thiscall*/ sub_494F20(float *this, int a2, float a3)
{
  float v4; // ecx

  v4 = *this;
  if ( v4 != 0.0
    && (*(uint8_t (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 308))(COERCE_FLOAT(LODWORD(v4))) != 0
    && *(this + a2 + 4) != a3 )
  {
    *(this + a2 + 4) = a3;
    *((uint8_t *)this + 196) = 1;
  }
}



// ------------------------------------------------------------
// 0x494F60 sub_494F60
// ------------------------------------------------------------
void /*thiscall*/ sub_494F60(uint32_t *this, int a2, int a3)
{
  int v4; // ecx

  v4 = *this;
  if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 308))(v4) != 0 && *(this + a2 + 10) != a3 )
  {
    *(this + a2 + 10) = a3;
    *((uint8_t *)this + 196) = 1;
  }
}



// ------------------------------------------------------------
// 0x494FA0 sub_494FA0
// ------------------------------------------------------------
int /*thiscall*/ sub_494FA0(int *this, int a2, int a3)
{
  int result; // eax
  char v5; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 50);
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16);
      if ( (uint8_t)result == 0 )
      {
        v5 = 1;
        if ( a2 == 4 || a3 == 4 )
          v5 = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, char))(*this + 892))(this, 0, a2, v5);
        return (*(int (/*thiscall*/ **)(int *, int, int, char))(*this + 892))(this, 1, a3, v5);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495010 sub_495010
// ------------------------------------------------------------
void /*userpurge*/ sub_495010(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4)
{
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int *v8; // ebx
  int v9; // eax
  int v10; // edx
  int *v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edi
  int v16; // edx
  bool v17; // cc
  int v18; // ebx
  int v19; // edx
  int v20; // eax
  int v23; // [esp+4h] [ebp-1Ch] BYREF
  int v24; // [esp+8h] [ebp-18h] BYREF
  int v25; // [esp+Ch] [ebp-14h]
  int v26; // [esp+10h] [ebp-10h]
  int v27; // [esp+14h] [ebp-Ch]
  int v28; // [esp+18h] [ebp-8h]
  int v29; // [esp+1Ch] [ebp-4h]

  if ( a1[1674] == -1 )
  {
    v5 = a4;
    if ( a4 != 0 )
    {
      if ( a4 != 1 )
        return;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 188))(a1);
    }
    else
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 184))(a1);
    }
    v29 = v6;
    if ( v6 != 4 )
    {
      v7 = a4 != 0
         ? (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 184))(a1)
         : (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 188))(a1);
      v28 = v7;
      if ( v7 == 4 )
      {
        v27 = 0;
        v25 = 4 * (a4 != 0) + 13;
        if ( 4 * (a4 != 0) != -13 )
        {
          v8 = &v24 - a4;
          v26 = 0;
          while ( 1 )
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 120))(a1, a2, a3);
            v10 = *a1;
            v23 = v9;
            v24 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(a1);
            if ( v29 == 0 || v29 == 2 )
            {
              v11 = &v23 + v5;
              v12 = *v11 - 1;
            }
            else
            {
              v11 = &v23 + v5;
              v12 = *v11 + 1;
            }
            v13 = *a1;
            *v11 = v12;
            v14 = v27 + 1 + *v8;
            *v8 = v14;
            a3 = 0;
            v15 = v14;
            a2 = v24;
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v13 + 136))(a1, v23) != 0 )
            {
              v28 = 2 * (a4 == 0) + 1;
              goto LABEL_23;
            }
            v16 = *a1;
            *v8 = v15 - v26 - 2;
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v16 + 136))(a1, v23, v24, 0) != 0 )
              break;
            v5 = a4;
            v17 = ++v27 < v25;
            v26 += 2;
            if ( !v17 )
              goto LABEL_24;
          }
          v28 = a4 != 0 ? 0 : 2;
LABEL_23:
          v5 = a4;
        }
LABEL_24:
        v18 = v28;
        v19 = v29;
        a1[1674] = 1 - v5;
        a1[1675] = v18;
        a1[1676] = v19;
        if ( v5 != 0 )
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 124))(a1, a2, a3);
        else
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 120))(a1, a2, a3);
        a1[1677] = v20;
        if ( v5 != 0 )
          (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 896))(a1);
        else
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 896))(a1, v29, v18);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4951F0 sub_4951F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4951F0(int *this)
{
  int result; // eax

  result = *(this + 1674);
  if ( result != -1 )
  {
    result = result != 0
           ? (*(int (/*thiscall*/ **)(int *))(*this + 184))(this)
           : (*(int (/*thiscall*/ **)(int *))(*this + 188))(this);
    if ( *(this + 1676) != result
      || (*(this + 1674) != 0
        ? (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this))
        : (result = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)),
          *(this + 1677) != result) )
    {
      *(this + 1674) = -1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495250 sub_495250
// ------------------------------------------------------------
char /*thiscall*/ sub_495250(uint8_t *this, unsigned int a2, int a3, int a4)
{
  char result; // al

  result = *(this + 6634);
  if ( result != 0 )
  {
    result = *(this + 6635);
    if ( result != 0 && *((uint32_t *)this + 1674) == -1 )
    {
      result = a2;
      if ( a2 <= 1 )
        return (*(int (/*thiscall*/ **)(uint8_t *, unsigned int))(*(uint32_t *)this + 968))(this, a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495290 sub_495290
// ------------------------------------------------------------
int /*thiscall*/ sub_495290(uint32_t *this, int a2, int a3, int a4, int a5, int a6, char a7)
{
  *(this + a2 + 1652) = a3;
  *(this + a2 + 1654) = a4;
  *((uint8_t *)this + a2 + 6634) = a5;
  *(this + a2 + 1656) = a6;
  *((uint8_t *)this + a2 + 6632) = a7;
  if ( a6 != 0 )
    *((uint8_t *)this + a2 + 6634) = 0;
  LOBYTE(a5) = 1;
  if ( *(this + 1659) == 4 || *(this + 1660) == 4 )
    LOBYTE(a5) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 892))(this, a2, *(this + a2 + 1659), a5);
}



// ------------------------------------------------------------
// 0x495310 sub_495310
// ------------------------------------------------------------
int /*thiscall*/ sub_495310(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // ebx
  int v7; // edi

  *(this + 1661) = a2;
  *(this + 1662) = a3;
  if ( a2 != 0 )
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, a2);
  else
    v6 = a4;
  if ( a3 != 0 )
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, a3);
  else
    v7 = a5;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 980))(this, v6);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 984))(this, v7);
}



// ------------------------------------------------------------
// 0x495380 sub_495380
// ------------------------------------------------------------
int /*thiscall*/ sub_495380(int *this, int a2)
{
  int v2; // edx

  v2 = *this;
  *(this + 1663) = a2;
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t))(v2 + 896))(*(this + 1659), *(this + 1660));
}



// ------------------------------------------------------------
// 0x4953B0 sub_4953B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4953B0(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 852))(this);
  if ( (uint8_t)result != 0 )
  {
    v3 = *(this + 1686) + 1;
    *(this + 1686) = v3;
    v4 = v3 % 3;
    result = v3 / 3;
    if ( v4 == 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 33, 2);
      v5 = *(uint32_t *)dword_8F8520;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
      v7 = *(uint32_t *)dword_8F8520;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
      return (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495430 sub_495430
// ------------------------------------------------------------
double /*cdecl*/ sub_495430(int a1, int a2, int a3)
{
  return (double)(4000 * a1) / ((double)(100 * a2 / a3 - 10000) * 0.0121 + 2100.0);
}



// ------------------------------------------------------------
// 0x495470 sub_495470
// ------------------------------------------------------------
char /*thiscall*/ sub_495470(int this, int a2)
{
  char result; // al

  result = *(uint8_t *)(this + 6668);
  if ( result != 0 )
  {
    *(uint32_t *)(this + 6672) = a2;
    return a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x495490 sub_495490
// ------------------------------------------------------------
char /*thiscall*/ sub_495490(int this, int a2)
{
  char result; // al

  result = *(uint8_t *)(this + 6681);
  if ( result != 0 )
  {
    result = *(uint8_t *)(this + 6682);
    if ( result != 0 )
    {
      *(uint32_t *)(this + 6684) = a2;
      return a2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4954C0 sub_4954C0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4954C0(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 816);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 830)));
}



// ------------------------------------------------------------
// 0x495500 sub_495500
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495500(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 844);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 858)));
}



// ------------------------------------------------------------
// 0x495540 sub_495540
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495540(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 872);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 886)));
}



// ------------------------------------------------------------
// 0x495580 sub_495580
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495580(void *this)
{
  int v3; // [esp+8h] [ebp-4h]

  v3 = sub_41A5E0((unsigned int)this + 956);
  return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 970)));
}



// ------------------------------------------------------------
// 0x4955C0 sub_4955C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4955C0(int *this, int a2, int a3)
{
  int v4; // ecx

  v4 = *this;
  if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 308))(v4) != 0 && *(this + a2 + 7) != a3 )
  {
    *(this + a2 + 7) = a3;
    *((uint8_t *)this + 196) = 1;
    sub_494F60(this, a2, -1);
  }
}



// ------------------------------------------------------------
// 0x495600 sub_495600
// ------------------------------------------------------------
char /*thiscall*/ sub_495600(uint32_t *this, int a2, int a3, char a4)
{
  uint8_t *v6; // ebx
  uint32_t *v7; // ebx
  char result; // al
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+18h] [ebp+8h]
  float v11; // [esp+18h] [ebp+8h]
  float v12; // [esp+20h] [ebp+10h]
  int v13; // [esp+20h] [ebp+10h]

  if ( a4 != 0 )
    v10 = *(this + a2 + 1654);
  else
    v10 = *(this + a2 + 1652);
  v9 = *(this + a2 + 1656);
  v12 = 0.0;
  if ( a3 == 0 || a3 == 2 )
  {
    v12 = -1.0;
  }
  else if ( a3 == 1 || a3 == 3 )
  {
    v12 = 1.0;
  }
  if ( *(this + 1663) != 1000 )
    v12 = (double)(int)*(this + 1663) * v12 * 0.001;
  v6 = (uint8_t *)*(this + 28);
  v11 = (double)v10 * v12;
  if ( *(uint32_t *)v6 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v6 + 308))(*(uint32_t *)v6) != 0
    && *(float *)&v6[4 * a2 + 16] != v11 )
  {
    *(float *)&v6[4 * a2 + 16] = v11;
    v6[196] = 1;
  }
  v7 = (uint32_t *)*(this + 28);
  v13 = (uint64_t)((double)v9 * v12);
  if ( *v7 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 308))(*v7) != 0 && v7[a2 + 7] != v13 )
  {
    v7[a2 + 7] = v13;
    *((uint8_t *)v7 + 196) = 1;
    sub_494F60(v7, a2, -1);
  }
  result = *((uint8_t *)this + a2 + 6632);
  if ( result != 0 )
  {
    sub_4A0600(a2);
    result = a3;
  }
  *(this + a2 + 1659) = a3;
  return result;
}



// ------------------------------------------------------------
// 0x495740 sub_495740
// ------------------------------------------------------------
int /*thiscall*/ sub_495740(void *this, int a2)
{
  int v2; // esi
  int v3; // eax
  unsigned int v4; // ecx
  int v5; // esi
  int64_t v6; // rax
  void *v7; // eax

  switch ( a2 )
  {
    case 1:
      v2 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      v3 = sub_41A5E0(v2 + 816);
      v4 = v2 + 830;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));
    case 2:
      v5 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      v3 = sub_41A5E0(v5 + 844);
      v4 = v5 + 858;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));
    case 3:
      LODWORD(v6) = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 900))(this, 3);
      break;
    case 4:
      v7 = (void *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      LODWORD(v6) = sub_495540(v7);
      break;
    default:
      LODWORD(v6) = 1000;
      break;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4957F0 sub_4957F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4957F0(int *this, char a2)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v6; // esi
  int v7; // [esp+14h] [ebp+8h]

  if ( a2 != 0 )
  {
    v2 = -1500;
  }
  else
  {
    v2 = *(this + 1666);
    if ( v2 == 0 )
      goto LABEL_9;
  }
  v3 = *(this + 29);
  if ( v3 != 0 )
  {
    v4 = *(uint32_t *)(v3 + 132);
    if ( v4 != 0 )
      v2 += *(this + 1669) + *(uint32_t *)(v4 + 1324);
  }
  if ( a2 != 0 )
    return v2;
LABEL_9:
  v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v7 = sub_41A5E0(v6 + 956);
  return (int)(v2 * (uint64_t)((double)v7 * COERCE_FLOAT(sub_41A5E0(v6 + 970)))) / 100;
}



// ------------------------------------------------------------
// 0x495890 sub_495890
// ------------------------------------------------------------
void /*thiscall*/ sub_495890(int *this, int a2, int a3)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // esi

  *(this + 1665) = a2;
  if ( a2 == 1 )
  {
    v4 = *(this + 29);
    v5 = -1500;
    if ( v4 != 0 )
    {
      v6 = *(uint32_t *)(v4 + 132);
      if ( v6 != 0 )
        v5 = *(uint32_t *)(v6 + 1324) + *(this + 1669) - 1500;
    }
  }
  else if ( a2 == 2 )
  {
    v5 = sub_4957F0(this, 0);
  }
  else
  {
    v5 = a3;
  }
  v7 = (uint32_t *)*(this + 28);
  if ( *v7 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 308))(*v7) != 0 && v7[9] != v5 )
  {
    v7[9] = v5;
    *((uint8_t *)v7 + 196) = 1;
    sub_494F60(v7, 2, -1);
  }
}



// ------------------------------------------------------------
// 0x495920 sub_495920
// ------------------------------------------------------------
void /*thiscall*/ sub_495920(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  double v4; // st7
  int v5; // eax
  float v6; // [esp+4h] [ebp-8h]

  if ( *((uint8_t *)this + 6668) != 0 )
  {
    v2 = *(this + 1639);
    v3 = 0;
    if ( v2 == 4 || v2 == 9 || (int)*(this + 81) <= 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 0 )
    {
      v6 = (double)(int)*(this + 1668) * 100.0;
      v4 = v6 / (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);
      if ( v4 > 20.0 )
        v3 = (uint64_t)((v4 - 20.0) * -300.0);
      *((uint8_t *)this + 6680) = 1;
    }
    else if ( *((uint8_t *)this + 6680) != 0 )
    {
      if ( *((uint8_t *)this + 6668) != 0 )
        *(this + 1668) = 0;
      *((uint8_t *)this + 6680) = 0;
    }
    if ( *(this + 1669) != v3 )
    {
      v5 = *(this + 1665);
      *(this + 1669) = v3;
      if ( v5 == 1 || v5 == 2 )
        sub_495890(this, v5, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x495A10 sub_495A10
// ------------------------------------------------------------
void /*thiscall*/ sub_495A10(int *this, int a2)
{
  int v3; // ecx
  uint32_t *v4; // eax
  uint32_t *v5; // esi
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+0h] [ebp-Ch]

  v3 = *(this + 30);
  *(this + 1664) = a2;
  if ( v3 != 0 )
  {
    v6 = (double)a2 * 0.1;
    sub_493D00(v3, v6);
  }
  v4 = (uint32_t *)*(this + 32);
  v5 = (uint32_t *)*v4;
  if ( (uint32_t *)*v4 != v4 )
  {
    do
    {
      v7 = (double)*(this + 1664) * 0.1;
      sub_493D00(v5[3], v7);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != (uint32_t *)*(this + 32) );
  }
}



// ------------------------------------------------------------
// 0x495A70 sub_495A70
// ------------------------------------------------------------
char /*thiscall*/ sub_495A70(uint8_t *this, int a2, int ArgList, int a4)
{
  char result; // al
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax

  result = *(this + 1004);
  if ( result != 0 )
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 4 )
    {
      if ( sub_48F5E0(a4) == -1 )
      {
        return off_77F3FC(aPvp_2, ArgList);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a4);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a2);
        v6 = *(uint32_t *)dword_8F8520;
        v7 = sub_48F5E0(a4);
        return (*(int (/*thiscall*/ **)(int, int, int))(v6 + 60))(dword_8F8520, 1, v7);
      }
    }
    else if ( v5 == 6 )
    {
      if ( sub_48FCE0(a4) == -1 )
      {
        return off_77F3FC(aWarroom, ArgList);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a4);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a2);
        v8 = *(uint32_t *)dword_8F8520;
        v9 = sub_48FCE0(a4);
        return (*(int (/*thiscall*/ **)(int, int, int))(v8 + 60))(dword_8F8520, 1, v9);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a4);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a2);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C00 sub_495C00
// ------------------------------------------------------------
char /*thiscall*/ sub_495C00(uint8_t *this, int a2)
{
  char result; // al
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // edx

  result = *(this + 1004);
  if ( result != 0 )
  {
    result = dword_8F7A24;
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 )
    {
      v4 = sub_41A5E0((unsigned int)(this + 864));
      sub_41A590((unsigned int)(this + 864), v5, a2 + v4);
      sub_41A590((unsigned int)(this + 990), 1124859904, 1124859904);
      sub_41A590((unsigned int)(this + 892), v6, 1116471296);
      return sub_41A590((unsigned int)(this + 920), v7, 1116471296);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C80 sub_495C80
// ------------------------------------------------------------
int /*thiscall*/ sub_495C80(char *this)
{
  void *v1; // esi

  v1 = this + 976;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 976))) >= 105.0 )
    return 105;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)v1)) >= 95.0 )
    return 95;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)v1)) >= 85.0 )
    return 85;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)v1)) >= 70.0 )
    return 70;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)v1)) >= 55.0 )
    return 55;
  if ( sub_43B5A0(v1) >= 45.0 )
    return 45;
  if ( sub_43B5A0(v1) >= 40.0 )
    return 40;
  if ( sub_43B5A0(v1) < 35.0 )
    return 0;
  return 35;
}



// ------------------------------------------------------------
// 0x495DA0 sub_495DA0
// ------------------------------------------------------------
char */*thiscall*/ sub_495DA0(char *this, int a2)
{
  char *result; // eax

  result = this + 96 * a2;
  *((uint32_t *)result + 6) = 0;
  *((uint32_t *)result + 18) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x495DC0 sub_495DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_495DC0(float *this)
{
  int i; // edi
  int v3; // eax
  uint32_t *v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // eax
  double v8; // st7
  float *v9; // ebx
  bool v10; // zf
  double v11; // st6
  uint32_t *v12; // ecx
  int v13; // edx
  int v14; // eax
  double v15; // st7
  float *v16; // ebx
  double v17; // st6
  int result; // eax
  bool v19; // cc
  uint32_t v20[3]; // [esp+Ch] [ebp-38h] BYREF
  uint32_t v21[3]; // [esp+1Ah] [ebp-2Ah] BYREF
  int v22; // [esp+28h] [ebp-1Ch]
  int v23; // [esp+2Ch] [ebp-18h]
  float *v24; // [esp+30h] [ebp-14h]
  int v25; // [esp+34h] [ebp-10h]
  int v26; // [esp+40h] [ebp-4h]

  v25 = 0;
  memset(this + 192, 0, 0x60u);
  v23 = 12;
  v24 = this + 18;
  do
  {
    for ( i = 0; i < 12; ++i )
    {
      v3 = sub_41A5E0((unsigned int)(this + 216));
      if ( i == 6 )
      {
        if ( v3 <= 1 )
        {
          sub_41A630((unsigned int)v21);
          v26 = 0;
          v21[0] = &clong::`vftable';
          sub_41A590((unsigned int)v21, v5, 1);
          v4 = v21;
          v26 = 1;
          v25 |= 1u;
        }
        else
        {
          v4 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)v4);
        v6 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v6 == 4 || v6 == 6 )
        {
          v8 = flt_790B4C;
        }
        else
        {
          v7 = sub_41A5E0((unsigned int)(this + 216));
          v8 = flt_790AEC;
          if ( v7 <= 10 )
            v8 = v8 * 0.33333334;
        }
        v9 = v24;
        v10 = (v25 & 1) == 0;
        v11 = *v24 / (double)v22;
        v26 = -1;
        *(this + 198) = v11 * v8 + *(this + 198);
        if ( !v10 )
        {
          v25 &= ~1u;
          sub_41A580(v21);
        }
        *(this + 210) = *(this + 210) + *v9;
      }
      else
      {
        if ( v3 <= 1 )
        {
          sub_41A630((unsigned int)v20);
          v26 = 2;
          v20[0] = &clong::`vftable';
          sub_41A590((unsigned int)v20, v13, 1);
          v12 = v20;
          v26 = 3;
          v25 |= 2u;
        }
        else
        {
          v12 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)v12);
        v14 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v14 == 4 || v14 == 6 )
          v15 = flt_790B34[i];
        else
          v15 = flt_790AD4[i];
        v16 = this + i + v23;
        v17 = flt_790B04[i] / (double)v22;
        v10 = (v25 & 2) == 0;
        v26 = -1;
        *(this + i + 192) = v17 * *v16 * v15 + *(this + i + 192);
        if ( !v10 )
        {
          v25 &= ~2u;
          sub_41A580(v20);
        }
        *(this + i + 204) = *(this + i + 204) + *v16;
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(this + i + 192) > (double)flt_790B04[i] )
          *(this + i + 192) = flt_790B04[i];
      }
    }
    result = v23 + 24;
    v19 = v23 + 24 < 204;
    v24 += 24;
    v23 += 24;
  }
  while ( v19 );
  return result;
}


// ------------------------------------------------------------
// 0x496010 sub_496010
// ------------------------------------------------------------
int /*thiscall*/ sub_496010(int this, int a2, int a3, int a4)
{
  int v4; // eax
  int result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  uint64_t v11; // rax
  int v12; // eax
  int v13; // eax
  float v14; // [esp-8h] [ebp-18h]
  int v15; // [esp-8h] [ebp-18h]
  int v16; // [esp-8h] [ebp-18h]
  float v17; // [esp+8h] [ebp-8h]
  float v18; // [esp+8h] [ebp-8h]
  float v19; // [esp+Ch] [ebp-4h]
  float v20; // [esp+Ch] [ebp-4h]
  int v21; // [esp+18h] [ebp+8h]
  float v22; // [esp+20h] [ebp+10h]
  float v23; // [esp+20h] [ebp+10h]
  float v24; // [esp+20h] [ebp+10h]
  float v25; // [esp+20h] [ebp+10h]

  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v4 == 4 )
  {
    result = dword_99FEC0;
    if ( dword_99FEC0 == 0 )
      return result;
    v7 = sub_48F5E0(a2);
  }
  else if ( v4 == 6 )
  {
    result = dword_99FF08;
    if ( dword_99FF08 == 0 )
      return result;
    v7 = sub_48FCE0(a2);
  }
  else
  {
    result = sub_429830(a2);
    if ( result == 0 )
      return result;
    result = sub_429830(a2);
    if ( *(uint32_t *)(result + 196) == 0 )
      return result;
    v8 = sub_429830(a2);
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 196) + 1216))(*(uint32_t *)(v8 + 196));
  }
  v21 = v7;
  *(float *)(this + 4 * (a3 + 24 * v7) + 48) = (double)a4 + *(float *)(this + 4 * (a3 + 24 * v7) + 48);
  sub_495DC0(this);
  v22 = *(float *)(this + 776) + *(float *)(this + 772) + *(float *)(this + 768);
  sub_41A590(LODWORD(v22));
  v23 = *(float *)(this + 788) + *(float *)(this + 784) + *(float *)(this + 780);
  sub_41A590(LODWORD(v23));
  sub_41A590(*(uint32_t *)(this + 792));
  sub_41A590(*(uint32_t *)(this + 840));
  if ( *(uint32_t *)(this + 964) != -956156672 )
    sub_41A590(*(uint32_t *)(this + 964));
  if ( *(uint32_t *)(this + 968) != -956156672 )
    sub_41A590(*(uint32_t *)(this + 968));
  v9 = *(uint32_t *)(this + 972);
  if ( v9 != -956156672 )
    sub_41A590(v9);
  v10 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v10 == 4 || v10 == 6 )
  {
    v20 = COERCE_FLOAT(sub_41A5E0(this + 878));
    v18 = COERCE_FLOAT(sub_41A5E0(this + 906));
    v25 = *(float *)(this + 812)
        + *(float *)(this + 808)
        + *(float *)(this + 804)
        + *(float *)(this + 800)
        + *(float *)(this + 796)
        + COERCE_FLOAT(sub_41A5E0(this + 934))
        + v18
        + v20;
    v14 = v25;
  }
  else
  {
    v17 = COERCE_FLOAT(sub_41A5E0(this + 878));
    v19 = COERCE_FLOAT(sub_41A5E0(this + 906));
    v24 = COERCE_FLOAT(sub_41A5E0(this + 934)) + v19 + v17;
    v14 = v24;
  }
  sub_41A590(LODWORD(v14));
  if ( COERCE_FLOAT(sub_41A5E0(this + 976)) < 0.0 )
    sub_41A590(0);
  result = dword_8F8500;
  if ( dword_8F8500 != 0 )
  {
    result = sub_456420(dword_8F850C);
    if ( result == v21 && dword_8F8520 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      if ( result != 0 )
      {
        result = a3;
        switch ( a3 )
        {
          case 0:
          case 1:
          case 2:
            v16 = (uint64_t)sub_43B5A0(this + 878);
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
            result = sub_426820(v13, 6, v16);
            break;
          case 3:
          case 4:
          case 5:
            v11 = (uint64_t)sub_43B5A0(this + 906);
            v15 = v11;
            v12 = (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520, HIDWORD(v11));
            result = sub_426820(v12, 7, v15);
            break;
          default:
            return result;
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x496320 sub_496320
// ------------------------------------------------------------
int /*thiscall*/ sub_496320(void *this)
{
  int v3; // [esp+4h] [ebp-Ch] BYREF
  uint16_t v4[3]; // [esp+8h] [ebp-8h] BYREF
  uint8_t v5; // [esp+Fh] [ebp-1h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, v4);
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v5);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v3);
  if ( v4[0] == (uint16_t)word_77F804
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104) != 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( (uint8_t)sub_45E680(dword_8F7C04) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 1208))(dword_8F7C04, v5, v3);
  }
  return sub_496010((int)this, v4[0], v5, v3);
}



// ------------------------------------------------------------
// 0x4963E0 sub_4963E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4963E0(uint32_t *this)
{
  uint32_t *v2; // ecx
  unsigned int v3; // edx
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  uint32_t v7[5]; // [esp+Ch] [ebp-14h] BYREF

  v2 = this + 3;
  v2[6] = 15;
  v2[5] = 0;
  v7[1] = this;
  *((uint8_t *)v2 + 4) = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = 0;
  v3 = v2[6];
  v7[4] = 0;
  v4 = v2 + 1;
  if ( v3 < 0x10 )
    v5 = v2 + 1;
  else
    v5 = (uint32_t *)*v4;
  if ( v3 >= 0x10 )
    v4 = (uint32_t *)*v4;
  sub_406D00(v2, v7, (int)v4, (unsigned int)v5 + v2[5]);
  return this;
}



// ------------------------------------------------------------
// 0x496470 sub_496470
// ------------------------------------------------------------
int /*cdecl*/ sub_496470(int a1, int a2, int a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v6[7] = 0;
  while ( a2 != 0 )
  {
    result = sub_459690(v3, a3);
    --a2;
    v3 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x496510 sub_496510
// ------------------------------------------------------------
int /*stdcall*/ sub_496510(int a1, int a2, int a3)
{
  sub_496470(a1, a2, a3);
  return a1 + 40 * a2;
}



// ------------------------------------------------------------
// 0x496540 sub_496540
// ------------------------------------------------------------
void /*thiscall*/ sub_496540(int *this, char *a2, unsigned int a3, int *a4)
{
  int v4; // edx
  int v6; // ecx
  int v7; // ebx
  unsigned int v8; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char *v14; // ebx
  uint32_t *v15; // ecx
  int v16; // eax
  unsigned int v17; // edi
  void *v18; // eax
  char *v19; // ecx
  int v21; // edi
  uint32_t *v22; // [esp-18h] [ebp-6Ch]
  int v23; // [esp-Ch] [ebp-60h]
  unsigned int v24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *v27; // [esp+10h] [ebp-44h]
  char *v28; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int v34; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  char *v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  char *v39; // [esp+64h] [ebp+10h]

  v34 = dword_796E50;
  v4 = a4[1];
  v6 = *a4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = a4[2];
  v27 = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, a4 + 3, 0, -1);
  v7 = *(this + 1);
  v36 = 0;
  if ( v7 != 0 )
    v8 = (*(this + 3) - v7) / 40;
  else
    v8 = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(this + 2) - v7) / 40;
    else
      v10 = 0;
    if ( 107374182 - v10 < a3 )
      sub_434730(this);
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 40;
    else
      v11 = 0;
    if ( v8 >= a3 + v11 )
    {
      v19 = (char *)*(this + 2);
      v39 = v19;
      if ( (v19 - a2) / 40 >= a3 )
      {
        v37 = &v19[-40 * a3];
        *(this + 2) = sub_459860(v37, v19, (int)v19);
        sub_572550(a2, v37, v39);
        sub_570610(a2, &a2[40 * a3], v29);
      }
      else
      {
        sub_459860(a2, v19, (int)&a2[40 * a3]);
        v24 = a3 - (*(this + 2) - (int)a2) / 40;
        v23 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_496510(v23, v24, v29);
        v21 = 40 * a3 + *(this + 2);
        *(this + 2) = v21;
        v36 = 0;
        sub_570610(a2, v21 - 40 * a3, v29);
      }
    }
    else
    {
      if ( 107374182 - (v8 >> 1) >= v8 )
        v12 = (v8 >> 1) + v8;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(this + 2) - v7) / 40;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
        v12 = a3 + sub_5721D0(this);
      v38 = 40 * v12;
      v14 = (char *)operator new(40 * v12);
      v22 = (uint32_t *)*(this + 1);
      Block = v14;
      v28 = v14;
      LOBYTE(v36) = 1;
      v28 = (char *)sub_459860(v22, a2, (int)v14);
      sub_496470((int)v28, a3, v29);
      v15 = (uint32_t *)*(this + 2);
      v28 += 40 * a3;
      sub_459860(a2, v15, (int)v28);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 40;
      v17 = v16 + a3;
      v18 = (void *)*(this + 1);
      if ( v18 != nullptr )
      {
        sub_55A010(v18, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v14[v38];
      *(this + 2) = (int)&v14[40 * v17];
      *(this + 1) = (int)v14;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x496870 sub_496870
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496870(int *this, uint32_t *a2, int a3, uint32_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 40 != 0 )
    v6 = (a3 - v5) / 40;
  else
    v6 = 0;
  sub_496540(this, a3, 1u, a4);
  *a2 = *(this + 1) + 40 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4968E0 sub_4968E0
// ------------------------------------------------------------
int /*fastcall*/ sub_4968E0(int a1, int a2)
{
  int v3; // eax
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  char *v15; // edi
  char *i; // ebx
  char *v17; // edi
  char *j; // ebx

  memset((void *)a1, 0, 0x300u);
  memset((void *)(a1 + 768), 0, 0x60u);
  v3 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v3 == 4 || v3 == 6 )
  {
    sub_41A590(a1 + 976, a2, 0);
    sub_41A590(a1 + 864, v9, 0);
    sub_41A590(a1 + 934, v10, 0);
    sub_41A590(a1 + 906, 0, 0);
    sub_41A590(a1 + 878, v11, 0);
    sub_41A590(a1 + 892, v12, -1082130432);
    sub_41A590(a1 + 920, -1082130432, -1082130432);
    sub_41A590(a1 + 990, v13, -1082130432);
    sub_41A590(a1 + 948, v14, 0);
  }
  else
  {
    sub_41A590(a1 + 990, a2, 0);
    sub_41A590(a1 + 920, 0, 0);
    sub_41A590(a1 + 892, v4, 0);
    sub_41A590(a1 + 976, v5, 0);
    sub_41A590(a1 + 864, v6, 0);
    sub_41A590(a1 + 934, 0, 0);
    sub_41A590(a1 + 906, v7, 0);
    sub_41A590(a1 + 878, v8, 0);
    sub_41A590(a1 + 948, 0, 0);
  }
  v15 = *(char **)(a1 + 1012);
  if ( v15 != nullptr )
  {
    for ( i = *(char **)(a1 + 1016); v15 != i; v15 += 40 )
      sub_5014C0(v15);
    j__free(*(void **)(a1 + 1012));
  }
  *(uint32_t *)(a1 + 1012) = 0;
  *(uint32_t *)(a1 + 1016) = 0;
  *(uint32_t *)(a1 + 1020) = 0;
  v17 = *(char **)(a1 + 1028);
  if ( v17 != nullptr )
  {
    for ( j = *(char **)(a1 + 1032); v17 != j; v17 += 40 )
      sub_5014C0(v17);
    j__free(*(void **)(a1 + 1028));
  }
  *(uint32_t *)(a1 + 1028) = 0;
  *(uint32_t *)(a1 + 1032) = 0;
  *(uint32_t *)(a1 + 1036) = 0;
  *(uint32_t *)(a1 + 964) = -956156672;
  *(uint32_t *)(a1 + 968) = -956156672;
  *(uint32_t *)(a1 + 972) = -956156672;
  return -956156672;
}



// ------------------------------------------------------------
// 0x496B40 sub_496B40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496B40(int *this, uint32_t *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 40;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 40 )
    return sub_496870(this, &a2, *(this + 2), a2);
  v5 = *(this + 2);
  result = (uint32_t *)sub_496470(v5, 1, (int)a2);
  *(this + 2) = v5 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x496BD0 sub_496BD0
// ------------------------------------------------------------
void /*thiscall*/ sub_496BD0(int *this, uint32_t *a2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  uint32_t *v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // esi
  uint32_t v11[3]; // [esp+Ch] [ebp-38h] BYREF
  size_t v12[6]; // [esp+18h] [ebp-2Ch] BYREF
  unsigned int v13; // [esp+30h] [ebp-14h]
  int v14; // [esp+34h] [ebp-10h]
  int v15; // [esp+40h] [ebp-4h]

  v14 = dword_796E50;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 376))(a2);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v3 )
  {
    sub_4963E0(v11);
    v4 = *a2;
    v15 = 0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 1032))(a2);
    v6 = *a2;
    v11[2] = *(uint32_t *)(v5 + 68);
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(v6 + 340))(a2);
    v8 = *a2;
    v11[1] = *v7;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 340))(a2);
    sub_4014D0(v12, (size_t *)(v9 + 4), 0, 0xFFFFFFFF);
    v11[0] = a2[1943];
    if ( v11[0] == 3 )
    {
      sub_496B40(this + 252, v11);
    }
    else
    {
      v10 = a2[1943];
      if ( v10 != 1 && v10 != 2 )
      {
        if ( v13 < 0x10 )
          return;
        goto LABEL_10;
      }
      sub_496B40(this + 256, v11);
    }
    if ( v13 < 0x10 )
      return;
LABEL_10:
    j__free((void *)v12[1]);
  }
}



// ------------------------------------------------------------
// 0x496CE0 sub_496CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_496CE0(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 17;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 56) = 0;
  sub_699070(1);
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 96) = 0;
  *(uint8_t *)(this + 97) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 100) = 4;
  *(uint32_t *)(this + 104) = 1065353216;
  *(uint32_t *)(this + 108) = 1065353216;
  *(uint32_t *)(this + 112) = 1065353216;
  *(uint32_t *)(this + 116) = 1065353216;
  *(uint32_t *)(this + 120) = 1065353216;
  return 1065353216;
}



// ------------------------------------------------------------
// 0x496DA0 sub_496DA0
// ------------------------------------------------------------
char /*thiscall*/ sub_496DA0(uint32_t *this, int a2)
{
  int v3; // esi

  v3 = (int)(this + 15);
  sub_698FE0((int)(this + 15));
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  *(this + 23) = a2;
  return sub_698F90(v3, a2, 0);
}



// ------------------------------------------------------------
// 0x496DD0 sub_496DD0
// ------------------------------------------------------------
void /*cdecl*/ sub_496DD0(char a1)
{
  int v1; // esi
  uint32_t *v2; // ebx
  int v3; // ebx
  int v4; // edi
  int v5; // edi
  int v6; // ebx
  int v7; // ecx
  int v8; // esi
  int v9; // ecx
  int v10; // edi
  int v11; // edx
  int v12; // eax
  int v13; // [esp+4h] [ebp-Ch]
  unsigned int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]

  v1 = dword_8F7C04;
  if ( dword_8F7C04 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 80))(dword_8F7C04) != 0 )
  {
    if ( dword_9A0130[0] == 0 )
    {
      v2 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                       dword_8F84B8,
                       "Common/ActiveStatus/Blind1.img");
      dword_9A0130[0] = sub_418DD0(v2, 0);
      dword_9A0134 = sub_418DD0(v2, 1u);
      dword_9A0138 = sub_418DD0(v2, 2u);
    }
    v3 = sub_4239A0(v1);
    if ( a1 != 0 )
      v4 = sub_4239D0(v1, 0.0);
    else
      v4 = sub_4239D0(v1, 1.0);
    v5 = v4 - 345;
    v6 = v3 - 245;
    v15 = v5;
    v7 = dword_9A0130[a1 == 0];
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v6, v5, dword_79C0B0);
    v8 = v6;
    v14 = v6;
    v9 = v5;
    if ( v6 > 0 )
    {
      v14 = v6 - 50 * ((v6 - 1) / 0x32u + 1);
      v8 = v14;
    }
    if ( v5 > 0 )
      v9 = v5 - 50 * ((v5 - 1) / 0x32u + 1);
    v10 = v9;
    if ( v9 < 480 )
    {
      v11 = dword_9A0138;
      v13 = v9;
      do
      {
        v12 = v8;
        if ( v8 < 640 )
        {
          do
          {
            if ( (v12 < v6 || v12 >= v6 + 500 || v10 < v15 || v10 >= v15 + 500) && v11 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(dword_9A0138, v12, v10, dword_79C0B0);
              v11 = dword_9A0138;
            }
            v8 += 50;
            v12 = v8;
          }
          while ( v8 < 640 );
          v8 = v14;
          v9 = v13;
        }
        v9 += 50;
        v13 = v9;
        v10 = v9;
      }
      while ( v9 < 480 );
    }
  }
}



// ------------------------------------------------------------
// 0x496F80 sub_496F80
// ------------------------------------------------------------
int /*cdecl*/ sub_496F80(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 0:
      result = 0;
      break;
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      result = 3;
      break;
    case 4:
      result = 4;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 6;
      break;
    case 7:
      result = 7;
      break;
    case 8:
      result = 8;
      break;
    case 9:
      result = 9;
      break;
    case 10:
      result = 10;
      break;
    case 11:
      result = 11;
      break;
    case 15:
      result = 14;
      break;
    case 16:
      result = 15;
      break;
    default:
      result = 16;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497040 sub_497040
// ------------------------------------------------------------
int /*cdecl*/ sub_497040(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 0:
      result = 0;
      break;
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      result = 3;
      break;
    case 4:
      result = 4;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 6;
      break;
    case 7:
      result = 7;
      break;
    case 8:
      result = 8;
      break;
    case 9:
      result = 9;
      break;
    case 10:
      result = 10;
      break;
    case 11:
      result = 11;
      break;
    case 14:
      result = 15;
      break;
    case 15:
      result = 16;
      break;
    default:
      result = 17;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497100 ?_Get_future_error_what@std@@YAPBDH@Z_0
// ------------------------------------------------------------
const char */*cdecl*/ std::_Get_future_error_what(int a1)
{
  return (const char *)dword_9A0140[a1];
}



// ------------------------------------------------------------
// 0x497110 sub_497110
// ------------------------------------------------------------
int /*thiscall*/ sub_497110(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);
}



// ------------------------------------------------------------
// 0x497120 sub_497120
// ------------------------------------------------------------
int /*cdecl*/ sub_497120(int a1, int a2)
{
  return sub_4049C0(*(&flt_6CB268 + 2 * a1), flt_6CB26C[2 * a1], a2 - 1, 39);
}



// ------------------------------------------------------------
// 0x497150 sub_497150
// ------------------------------------------------------------
void /*cdecl*/ sub_497150(int a1, int a2)
{
  sub_4049C0(*(&flt_6CB2F0 + 2 * a1), flt_6CB2F4[2 * a1], a2 - 1, 39);
}



// ------------------------------------------------------------
// 0x497190 sub_497190
// ------------------------------------------------------------
char /*thiscall*/ sub_497190(int *this)
{
  return sub_4939E0(*(this + 5), sub_497180 != nullptr);
}



// ------------------------------------------------------------
// 0x4971B0 sub_4971B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4971B0(int a1, int a2, int a3)
{
  int v3; // edi
  unsigned int v4; // eax
  int v5; // ebx
  int v6; // esi
  float v8; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+Ch] [ebp-4h]
  int v11; // [esp+18h] [ebp+8h]

  v3 = 0;
  v10 = 0;
  switch ( a1 )
  {
    case 0:
    case 2:
    case 4:
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
      v3 = 1000 * dword_6CB220[a1];
      goto LABEL_5;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 15:
    case 16:
      v3 = (uint64_t)(sub_4049C0(*(&flt_6CB268 + 2 * a1), flt_6CB26C[2 * a1], a2 - 1, 39) * 1000.0);
      goto LABEL_5;
    case 10:
    case 14:
      v3 = 0;
LABEL_5:
      v10 = v3;
      break;
    default:
      break;
  }
  if ( a3 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 40))(a3, 529) != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 684))(a3);
    sub_41A5E0(v4);
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 672))(a3, 3);
    v9 = sub_41A5E0(v5 + 4);
    v8 = COERCE_FLOAT(sub_41A5E0(v5 + 18));
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 672))(a3, 3);
    v11 = sub_41A5E0(v6 + 4);
    v3 -= (uint64_t)((double)((int)(uint64_t)((double)v11 * COERCE_FLOAT(sub_41A5E0(v6 + 18)))
                                    / 2
                                    / (int)(uint64_t)((double)v9 * v8))
                           * (double)v10);
  }
  if ( v3 >= 0 )
    return v3;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x497300 sub_497300
// ------------------------------------------------------------
int /*thiscall*/ sub_497300(int *this, int ArgList, int a3)
{
  int v4; // ebx
  unsigned int v5; // edi
  int v7; // edi
  int v8; // eax
  int v9; // ecx

  v4 = *(this + 3);
  *(this + 3) = ArgList;
  if ( ArgList > 40 )
  {
    off_77F3FC((char *)&byte_6CB378, ArgList, 40);
    *(this + 3) = 40;
  }
  *(this + 4) = a3;
  if ( ArgList > 0 )
  {
    v7 = *this;
    v8 = sub_4971B0(*(this + 2), *(this + 3), *(this + 1));
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 84))(this, v8);
    LOBYTE(v9) = v4 == 0;
    (*(void (/*thiscall*/ **)(int *, int))(*this + 60))(this, v9);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);
  }
  else
  {
    v5 = *(this + 23);
    if ( v5 > sub_699000((int)(this + 15)) && *(this + 2) == 7 )
      *(this + 22) = v5;
    (*(void (/*thiscall*/ **)(int *))(*this + 64))(this);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);
  }
}



// ------------------------------------------------------------
// 0x4973B0 sub_4973B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4973B0(int this, char a2)
{
  int v3; // ecx
  int *v4; // esi
  int i; // edi
  int *v6; // esi
  int j; // edi
  int *v8; // esi
  int k; // edi

  if ( *(uint8_t *)(this + 96) != a2 )
  {
    *(uint8_t *)(this + 96) = a2;
    v3 = this + 60;
    if ( a2 != 0 )
      sub_699030(v3);
    else
      sub_698FE0(v3);
    switch ( *(uint32_t *)(this + 8) )
    {
      case 0:
        sub_4939E0(*(uint32_t *)(this + 20), 1);
        break;
      case 1:
        v4 = (int *)(this + 20);
        for ( i = 3; i != 0; --i )
          sub_4939E0(*v4++, a2);
        break;
      case 3:
        v6 = (int *)(this + 20);
        for ( j = 2; j != 0; --j )
          sub_4939E0(*v6++, a2);
        break;
      case 5:
        v8 = (int *)(this + 20);
        for ( k = 2; k != 0; --k )
          sub_4939E0(*v8++, a2);
        break;
      case 6:
      case 8:
      case 0xC:
        sub_4939E0(*(uint32_t *)(this + 20), a2);
        break;
      case 7:
        sub_497190(this);
        break;
      case 0xF:
        sub_4939E0(*(uint32_t *)(this + 20), a2);
        sub_4939E0(*(uint32_t *)(this + 24), a2);
        break;
      case 0x10:
        sub_4939E0(*(uint32_t *)(this + 20), a2);
        sub_4939E0(*(uint32_t *)(this + 24), a2);
        sub_4939E0(*(uint32_t *)(this + 28), a2);
        break;
      default:
        return;
    }
  }
}



// ------------------------------------------------------------
// 0x497500 sub_497500
// ------------------------------------------------------------
int /*thiscall*/ sub_497500(char *this)
{
  int (/*thiscall*/ ****v1)(uint32_t, int); // esi
  int i; // ebx
  int v3; // edi
  int result; // eax
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  bool v6; // zf

  v1 = (int (/*thiscall*/ ****)(uint32_t, int))(this + 40);
  for ( i = 5; i != 0; --i )
  {
    v3 = (int)*(v1 - 5);
    if ( v3 != 0 )
    {
      sub_42AF90((void **)*(v1 - 5));
      result = sub_657740(v3, 228);
    }
    v5 = *v1;
    v6 = *v1 == nullptr;
    *(v1 - 5) = nullptr;
    if ( !v6 )
      result = (**v5)(v5, 1);
    *v1++ = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497560 sub_497560
// ------------------------------------------------------------
float */*thiscall*/ sub_497560(int this)
{
  int v2; // eax
  int v3; // ecx
  float *result; // eax
  int v5; // eax
  double v6; // st7
  float v7; // eax
  uint32_t *v8; // ecx
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  float Block; // [esp+4h] [ebp-10h]

  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/StoneCurse.ani", 1);
  else
    v2 = 0;
  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 20) = v2;
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 688))(v3);
  if ( *((uint32_t *)result + 3) != 0 )
  {
    result = (float *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
    if ( *((uint32_t *)result + 3) != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
      result = (float *)sub_4924C0(*(int **)(v5 + 12), 0);
      if ( result != nullptr && *(uint32_t *)result != 0 )
      {
        *(float *)(this + 116) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.016666668;
        v6 = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6];
        v7 = *(float *)(this + 116);
        v8 = *(uint32_t **)(this + 20);
        Block = v6 * 0.016666668;
        *(float *)(this + 120) = Block;
        sub_4920E0(v8, v7, Block);
        v9 = operator new(0x12Cu);
        if ( v9 != nullptr )
          v10 = sub_428F30(v9, (int)"Common/ActiveStatus/Particle/StoneCursing.ptl", 0);
        else
          v10 = nullptr;
        *(uint32_t *)(this + 40) = v10;
        v11 = operator new(0x12Cu);
        if ( v11 != nullptr )
        {
          result = (float *)sub_428F30(v11, (int)"Common/ActiveStatus/Particle/StoneCurseDestroy.ptl", 0);
          *(uint32_t *)(this + 44) = result;
        }
        else
        {
          *(uint32_t *)(this + 44) = 0;
          return nullptr;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4976E0 sub_4976E0
// ------------------------------------------------------------
float */*thiscall*/ sub_4976E0(int this)
{
  int v2; // eax
  uint32_t **v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  float *result; // eax
  int v8; // eax
  int v9; // ebx

  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze1.ani", 1);
  else
    v2 = 0;
  v3 = (uint32_t **)(this + 20);
  *(uint32_t *)(this + 20) = v2;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze2.ani", 1);
  else
    v4 = 0;
  *(uint32_t *)(this + 24) = v4;
  if ( sub_42FCB0(228) != 0 )
    v5 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze3.ani", 1);
  else
    v5 = 0;
  v6 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 28) = v5;
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 688))(v6);
  if ( *((uint32_t *)result + 3) != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
    result = (float *)sub_4924C0(*(int **)(v8 + 12), 0);
    if ( result != nullptr && *(uint32_t *)result != 0 )
    {
      *(float *)(this + 108) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.0076923077;
      v9 = 3;
      *(float *)(this + 112) = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6] * 0.0071428572;
      do
      {
        result = (float *)sub_4920E0(*v3++, *(float *)(this + 108), *(float *)(this + 112));
        --v9;
      }
      while ( v9 != 0 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x497840 sub_497840
// ------------------------------------------------------------
void /*thiscall*/ sub_497840(int *this, void *Block, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t *v18; // eax
  uint32_t *v19; // eax
  int v20; // ecx
  int v21; // eax
  uint32_t *v22; // eax
  uint32_t *v23; // eax
  int v24; // ecx
  uint32_t *v25; // eax
  uint32_t *v26; // eax
  int v27; // ecx

  *(this + 2) = (int)Block;
  *(this + 1) = a3;
  switch ( (unsigned int)Block )
  {
    case 0u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Slow.ani", 1);
      goto LABEL_62;
    case 1u:
      sub_4976E0(this);
      return;
    case 2u:
      v16 = operator new(0x12Cu);
      if ( v16 != nullptr )
        *(this + 10) = (int)sub_428F30(v16, (int)"Common/ActiveStatus/Particle/PoisonParticle.ptl", *(this + 1));
      else
        *(this + 10) = 0;
      return;
    case 3u:
      if ( sub_42FCB0(228) != 0 )
        v17 = sub_431860((char)"Common/ActiveStatus/Animation/Stun1.ani", 1);
      else
        v17 = 0;
      *(this + 5) = v17;
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Stun2.ani", 1);
      return;
    case 4u:
      v18 = operator new(0x12Cu);
      if ( v18 != nullptr )
        v19 = sub_428F30(v18, (int)"Common/ActiveStatus/Particle/CurseParticle.ptl", *(this + 1));
      else
        v19 = nullptr;
      v20 = *(this + 1);
      *(this + 10) = (int)v19;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v19 + 112))(v19, v20);
      return;
    case 5u:
      if ( sub_42FCB0(228) != 0 )
        v21 = sub_431860((char)"Common/ActiveStatus/Animation/Blind1.ani", 1);
      else
        v21 = 0;
      *(this + 5) = v21;
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Blind2.ani", 1);
      return;
    case 6u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Lightning.ani", 1);
      goto LABEL_62;
    case 7u:
      sub_497560(this);
      return;
    case 8u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Sleep.ani", 1);
      goto LABEL_62;
    case 9u:
      if ( sub_42FCB0(228) != 0 )
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/ActiveStatus_BurnDamage_Effect.ani", 1);
      else
        v5 = 0;
      *(this + 25) = 0;
      goto LABEL_62;
    case 0xBu:
      if ( *(uint32_t *)(dword_8F7A24 + 244) == 1 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding.ani", 1);
          goto LABEL_62;
        }
      }
      else if ( sub_42FCB0(228) != 0 )
      {
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding12Age.ani", 1);
        goto LABEL_62;
      }
LABEL_61:
      v5 = 0;
LABEL_62:
      *(this + 5) = v5;
      return;
    case 0xCu:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);
      goto LABEL_62;
    case 0xDu:
      v22 = operator new(0x12Cu);
      if ( v22 != nullptr )
        v23 = sub_428F30(v22, (int)"Common/ActiveStatus/Particle/BlessParticle1.ptl", *(this + 1));
      else
        v23 = nullptr;
      v24 = *(this + 1);
      *(this + 10) = (int)v23;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v23 + 112))(v23, v24);
      v25 = operator new(0x12Cu);
      if ( v25 != nullptr )
        v26 = sub_428F30(v25, (int)"Common/ActiveStatus/Particle/BlessParticle2.ptl", *(this + 1));
      else
        v26 = nullptr;
      v27 = *(this + 1);
      *(this + 11) = (int)v26;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v26 + 112))(v26, v27);
      return;
    case 0xFu:
      if ( sub_42FCB0(228) != 0 )
        v4 = sub_431860((char)"Common/ActiveStatus/Animation/Confuse.ani", 1);
      else
        v4 = 0;
      *(this + 5) = v4;
      if ( sub_42FCB0(228) != 0 )
        *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/ConfuseGlow.ani", 1);
      else
LABEL_44:
        *(this + 6) = 0;
      return;
    case 0x10u:
      if ( sub_42FCB0(228) != 0 )
        v6 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v6 = 0;
      *(this + 5) = v6;
      if ( sub_42FCB0(228) != 0 )
        v7 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v7 = 0;
      *(this + 6) = v7;
      if ( sub_42FCB0(228) != 0 )
        v8 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v8 = 0;
      v9 = *(this + 5);
      *(this + 7) = v8;
      v10 = sub_42FC90(v9);
      v11 = rand();
      sub_493400(*(this + 5), v11 % v10);
      v12 = sub_42FC90(*(this + 6));
      v13 = rand();
      sub_493400(*(this + 6), v13 % v12);
      v14 = sub_42FC90(*(this + 7));
      v15 = rand();
      sub_493400(*(this + 7), v15 % v14);
      return;
    default:
      return;
  }
}


// ------------------------------------------------------------
// 0x497E40 sub_497E40
// ------------------------------------------------------------
int /*thiscall*/ sub_497E40(void *this, int a2, int a3, int a4)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 96))(this, a4);
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 4))(this, a2, a3);
}



// ------------------------------------------------------------
// 0x497E70 sub_497E70
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_497E70(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; ++result )
  {
    if ( result != nullptr )
      *result = *v3;
    ++v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497EA0 sub_497EA0
// ------------------------------------------------------------
void /*usercall*/ sub_497EA0(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  void (/*thiscall*/ ***v23)(uint32_t, int); // ecx
  int v25; // [esp-4h] [ebp-34h]
  int v26; // [esp+0h] [ebp-30h]
  uint8_t v27[4]; // [esp+8h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-24h]
  int v29; // [esp+10h] [ebp-20h]
  int v30; // [esp+18h] [ebp-18h] BYREF
  int v31; // [esp+1Ch] [ebp-14h]
  int v32; // [esp+20h] [ebp-10h]
  int v33; // [esp+2Ch] [ebp-4h]

  v3 = a1[59];
  if ( v3 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v3 + 308))() != 0 && a1[61] == 33 )
  {
    v4 = a1[63];
    if ( v4 != 0 && (v31 = (a1[64] - v4) >> 5, v5 = v31, v31 != 0) )
    {
      sub_490D70(a1, (int)v27);
      v33 = 0;
      if ( Block != nullptr )
        v32 = (v29 - (int)Block) >> 2;
      else
        v32 = 0;
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, a2);
      v6 = *(uint32_t *)dword_8F8520;
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[59] + 48))(a1[59]);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
      v8 = *(uint32_t *)dword_8F8520;
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[59] + 52))(a1[59]);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
      v10 = a1[67];
      if ( v10 != 0 )
        v11 = (*(int (**)(void))(*(uint32_t *)v10 + 48))();
      else
        v11 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v11);
      v12 = a1[67];
      if ( v12 != 0 )
        v13 = (*(int (**)(void))(*(uint32_t *)v12 + 52))();
      else
        v13 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v13);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v32);
      v14 = 0;
      if ( v32 > 0 )
      {
        while ( 1 )
        {
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 36))(a1) + 68) != 0 )
          {
            v15 = rand() % v5;
          }
          else
          {
            v15 = v14;
            if ( v14 >= v5 )
              v15 = v5;
          }
          v25 = *(uint16_t *)(a1[63] + 32 * v15 + 28);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          v16 = *(uint32_t *)dword_8F8520;
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
          (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          v19 = *(uint32_t *)dword_8F8520;
          v20 = sub_460230(*(uint32_t *)(v18 + 104));
          (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(uint32_t, void *, int *))(**((uint32_t **)Block + v14) + 16))(
            *((uint32_t *)Block + v14),
            &unk_9A0188,
            &v30);
          v26 = sub_529A80(v25, v26);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520);
          (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A0188, v30);
          v21 = *(uint32_t *)dword_8F8520;
          v22 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v14) + 44))(*((uint32_t *)Block + v14));
          (*(void (/*thiscall*/ **)(int, int))(v21 + 40))(dword_8F8520, v22);
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, 0, 0);
          v23 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v14);
          if ( v23 != nullptr )
            (**v23)(v23, 1);
          if ( ++v14 >= v32 )
            break;
          v5 = v31;
        }
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      if ( Block != nullptr )
        j__free(Block);
    }
    else
    {
      off_77F3FC((char *)&byte_6CB800);
    }
  }
}


// ------------------------------------------------------------
// 0x498150 sub_498150
// ------------------------------------------------------------
size_t */*cdecl*/ sub_498150(size_t *a1, size_t *a2, size_t *a3)
{
  size_t *v3; // esi
  size_t *v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_4014D0(v4, v3, 0, 0xFFFFFFFF);
    v4[7] = v3[7];
    v3 += 8;
    v4 += 8;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x498190 sub_498190
// ------------------------------------------------------------
size_t */*thiscall*/ sub_498190(size_t *this)
{
  *(this + 59) = 0;
  *(this + 60) = 4;
  *(this + 61) = 2;
  *(this + 66) = 1;
  *(this + 67) = 0;
  return sub_4015C0(this + 68, szPassword, 0);
}



// ------------------------------------------------------------
// 0x4981D0 sub_4981D0
// ------------------------------------------------------------
size_t */*cdecl*/ sub_4981D0(size_t *a1, size_t *a2, size_t *a3)
{
  return sub_498150(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4981F0 sub_4981F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4981F0(size_t *a1, size_t *a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((size_t *)v3, a1, 0, 0xFFFFFFFF);
      *(uint32_t *)(v3 + 28) = a1[7];
    }
    v3 += 32;
    LOBYTE(v7) = 0;
    a1 += 8;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4982B0 sub_4982B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4982B0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  uint32_t *v8; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *v10; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(a2 + 4);
  v11 = &v9;
  v10 = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( (uint8_t)sub_42CFD0(v4) != 0 )
  {
    v8 = (uint32_t *)*(this + 1);
    v7 = *(uint32_t **)(a2 + 8);
    v6 = *(uint32_t **)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x498350 sub_498350
// ------------------------------------------------------------
int /*stdcall*/ sub_498350(size_t *a1, size_t *a2, int a3)
{
  return sub_4981F0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x498370 sub_498370
// ------------------------------------------------------------
int /*thiscall*/ sub_498370(int this, int a2)
{
  size_t *v3; // ebx
  unsigned int v4; // eax
  size_t *v6; // ecx
  unsigned int v7; // edx
  char *v8; // eax
  int v9; // eax
  int v10; // edi
  unsigned int v11; // edx
  int v12; // eax
  size_t *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == a2 )
    return this;
  v3 = *(size_t **)(a2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(a2 + 8) - (int)v3) >> 5) == 0 )
  {
    sub_428480(this);
    return this;
  }
  v6 = *(size_t **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 5;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    v8 = (char *)sub_498150(v3, *(size_t **)(a2 + 8), v6);
    sub_493260(v8, *(char **)(this + 8));
    v9 = *(uint32_t *)(a2 + 4);
    if ( v9 != 0 )
      v10 = *(uint32_t *)(this + 4) + 32 * ((*(uint32_t *)(a2 + 8) - v9) >> 5);
    else
      v10 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v10;
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 12) - (int)v6) >> 5;
  else
    v11 = 0;
  if ( v4 > v11 )
  {
    if ( v6 != nullptr )
    {
      sub_493260((char *)v6, *(char **)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v14 = *(uint32_t *)(a2 + 4);
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(a2 + 8) - v14) >> 5;
    else
      v15 = 0;
    if ( (uint8_t)sub_4281D0(v15) != 0 )
      *(uint32_t *)(this + 8) = sub_498350(*(size_t **)(a2 + 4), *(size_t **)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v12 = (*(uint32_t *)(this + 8) - (int)v6) >> 5;
  else
    v12 = 0;
  v13 = (size_t *)(*(uint32_t *)(a2 + 4) + 32 * v12);
  sub_4981D0(*(size_t **)(a2 + 4), v13, *(size_t **)(this + 4));
  *(uint32_t *)(this + 8) = sub_4981F0(v13, *(size_t **)(a2 + 8), *(uint32_t *)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x4984D0 sub_4984D0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4984D0(size_t *this, uint32_t *a2)
{
  sub_490340(this, (int)a2);
  *(this + 61) = a2[43];
  sub_498370((int)(this + 62), (int)(a2 + 45));
  *(this + 66) = a2[44];
  return sub_4014D0(this + 68, a2 + 49, 0, 0xFFFFFFFF);
}



// ------------------------------------------------------------
// 0x498530 sub_498530
// ------------------------------------------------------------
char */*thiscall*/ sub_498530(char *this, int a2)
{
  uint32_t *v3; // ecx

  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B88;
  *((uint32_t *)this + 2) = 0;
  *(this + 12) = 1;
  *(this + 14) = 0;
  *(this + 13) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  v3 = this + 60;
  v3[15] = 0;
  v3[16] = 0;
  v3[17] = 0;
  v3[19] = 0;
  v3[20] = 0;
  v3[21] = 0;
  sub_430B70(v3);
  *((uint32_t *)this + 51) = sub_4A2CF0(this + 200);
  *((uint32_t *)this + 52) = 0;
  sub_493BD0((int)this);
  sub_494630((int)this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x4985E0 sub_4985E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4985E0(uint32_t *this, uint32_t *a2)
{
  int v2; // edi
  char v4; // al
  uint32_t *v5; // esi
  int v6; // ecx
  int v7; // eax
  char v8; // cl
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // esi
  uint32_t *v13; // esi
  char *v14; // esi
  char *v15; // edi
  char *v16; // eax
  uint32_t *v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  uint32_t *v21; // eax
  void (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  int v23; // ecx
  int v24; // edi
  int v25; // eax
  int v27; // [esp-4h] [ebp-50h]
  int v28; // [esp-4h] [ebp-50h]
  int v29; // [esp-4h] [ebp-50h]
  char v30[4]; // [esp+Ch] [ebp-40h] BYREF
  void *v31; // [esp+10h] [ebp-3Ch]
  int v32; // [esp+14h] [ebp-38h]
  int v33; // [esp+18h] [ebp-34h]
  char v34[4]; // [esp+1Ch] [ebp-30h] BYREF
  void *Block; // [esp+20h] [ebp-2Ch]
  int v36; // [esp+24h] [ebp-28h]
  int v37; // [esp+28h] [ebp-24h]
  int v38; // [esp+2Ch] [ebp-20h]
  int v39; // [esp+30h] [ebp-1Ch]
  int v40; // [esp+34h] [ebp-18h]
  char *v41; // [esp+38h] [ebp-14h] BYREF
  int v42; // [esp+3Ch] [ebp-10h]
  int v43; // [esp+48h] [ebp-4h]

  v2 = 0;
  v39 = 0;
  v31 = nullptr;
  v32 = 0;
  v33 = 0;
  v4 = *((uint8_t *)this + 216);
  v43 = 0;
  if ( v4 != 0 )
  {
    v5 = a2;
    sub_4982B0(a2, (int)v30);
    return v5;
  }
  v6 = *(this + 59);
  if ( v6 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 236))(v6);
    v8 = *((uint8_t *)this + 217);
    LOBYTE(v40) = v7 == 2;
    if ( (v7 == 2) != v8 )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, v40);
  }
  v9 = *(this + 60);
  if ( v9 != 0 )
  {
    if ( v9 == 1 )
    {
      *((uint8_t *)this + 88) = 0;
    }
    else
    {
      v10 = *(this + 59);
      if ( v10 != 0 )
        *((uint8_t *)this + 88) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 152))(v10) == 0;
    }
  }
  else
  {
    *((uint8_t *)this + 88) = 1;
  }
  if ( *(this + 59) != 0 && *(this + 61) == 33 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v5 = a2;
    sub_4982B0(a2, (int)v30);
    return v5;
  }
  v11 = *(this + 63);
  if ( v11 == 0 || (v39 = (*(this + 64) - v11) >> 5, v12 = v39, v39 == 0) )
  {
    off_77F3FC(aFail_1);
    v5 = a2;
    sub_4982B0(a2, (int)v30);
    return v5;
  }
  sub_490D70(this, (int)v34);
  LOBYTE(v43) = 1;
  if ( Block != nullptr )
    v40 = (v36 - (int)Block) >> 2;
  else
    v40 = 0;
  v42 = 0;
  if ( v40 > 0 )
  {
    while ( 1 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 68) != 0 )
      {
        v13 = (uint32_t *)(*(this + 63) + 32 * (rand() % v12));
      }
      else
      {
        if ( v2 < v12 )
          v12 = v2;
        v13 = (uint32_t *)(*(this + 63) + 32 * v12);
      }
      if ( *(this + 61) == 2 )
        break;
      if ( *(this + 61) != 33 )
        goto LABEL_54;
      v14 = (char *)sub_53A220(v13[7], nullptr);
      v41 = v14;
LABEL_53:
      if ( v14 != nullptr )
      {
        v28 = *(this + 46);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)v14 + 72))(v14);
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v14 + 60))(v14, *((uint32_t *)Block + v2));
        sub_4A0B60(v28);
        v29 = *(this + 67);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)v14 + 60))(v14);
        sub_4A06D0(v29);
        v23 = *((uint32_t *)Block + v2);
        v24 = *(uint32_t *)v14;
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 16))(v23);
        (*(void (/*thiscall*/ **)(char *, bool))(v24 + 148))(v14, *(uint8_t *)(v25 + 84) == 0);
        *((uint32_t *)Block + v42) = 0;
        sub_45FC10(&v41);
        v2 = v42;
        goto LABEL_58;
      }
LABEL_54:
      v21 = Block;
      v22 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v2);
      if ( v22 != nullptr )
      {
        (**v22)(v22, 1);
        v21 = Block;
      }
      v21[v2] = 0;
LABEL_58:
      v42 = ++v2;
      if ( v2 >= v40 )
        goto LABEL_59;
      v12 = v39;
    }
    if ( v13[7] == -1 )
    {
      v15 = (char *)sub_44B6C0(284);
      v41 = v15;
      LOBYTE(v43) = 2;
      if ( v15 != nullptr )
      {
        v38 = sub_42FCB0(228);
        LOBYTE(v43) = 3;
        if ( v38 != 0 )
        {
          if ( v13[6] < 0x10u )
            LOBYTE(v13) = (uint8_t)v13 + 4;
          else
            v13 = (uint32_t *)v13[1];
          if ( *(this + 74) < 0x10u )
            v16 = (char *)sub_431920((uint8_t)this + 20, (char)v13, 1);
          else
            v16 = (char *)sub_431920(*(this + 69), (char)v13, 1);
        }
        else
        {
          v16 = nullptr;
        }
        LOBYTE(v43) = 2;
        goto LABEL_43;
      }
    }
    else
    {
      v15 = (char *)sub_44B6C0(284);
      v38 = (int)v15;
      LOBYTE(v43) = 4;
      if ( v15 != nullptr )
      {
        v41 = (char *)sub_42FCB0(228);
        LOBYTE(v43) = 5;
        if ( v41 != nullptr )
        {
          if ( v13[6] < 0x10u )
            v17 = v13 + 1;
          else
            v17 = (uint32_t *)v13[1];
          v27 = v13[7];
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v17);
          v18 = sub_418DD0(v27);
          v16 = sub_498530(v41, v18);
          LOBYTE(v43) = 4;
        }
        else
        {
          v16 = nullptr;
          LOBYTE(v43) = 4;
        }
LABEL_43:
        sub_44E0D0(v15, (int)v16, 0);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
LABEL_52:
        v14 = v15;
        v19 = *(uint32_t *)v15;
        LOBYTE(v43) = 1;
        v41 = v15;
        v20 = (*(int (/*thiscall*/ **)(char *))(v19 + 36))(v15);
        v2 = v42;
        *(uint32_t *)(v20 + 8) = *(this + 66);
        goto LABEL_53;
      }
    }
    v15 = nullptr;
    goto LABEL_52;
  }
LABEL_59:
  v5 = a2;
  sub_4982B0(a2, (int)v30);
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v36 = 0;
  v37 = 0;
  if ( v31 != nullptr )
    j__free(v31);
  return v5;
}


// ------------------------------------------------------------
// 0x4989B0 sub_4989B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4989B0(void *this)
{
  void *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = this;
  return sub_407EA0(&dword_9A02B4, &v2);
}



// ------------------------------------------------------------
// 0x4989D0 sub_4989D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4989D0(void **this)
{
  sub_6569D0(this);
  sub_6569D0(this);
  j__free(*(this + 1));
  *(this + 1) = nullptr;
}



// ------------------------------------------------------------
// 0x498A00 sub_498A00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498A00(uint32_t *this)
{
  *(this + 1) = sub_425940(this);
  *(this + 2) = 0;
  sub_6569D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x498A20 sub_498A20
// ------------------------------------------------------------
int /*thiscall*/ sub_498A20(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x3FFFFFFF - v2 < a2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x498AB0 sub_498AB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498AB0(uint32_t *this)
{
  int v1; // edx
  int v2; // esi
  int v3; // edx
  uint32_t *v4; // edi
  uint32_t *result; // eax
  uint32_t *v6; // [esp+8h] [ebp-4h] BYREF

  v1 = dword_9A02A8++;
  *(this + 1) = v1;
  v2 = *(uint32_t *)dword_9A02B8;
  v3 = *(uint32_t *)(*(uint32_t *)dword_9A02B8 + 4);
  v6 = this;
  v4 = sub_40C0F0(v2, v3, &v6);
  sub_498A20(&dword_9A02B4, 1u);
  *(uint32_t *)(v2 + 4) = v4;
  result = (uint32_t *)v4[1];
  *result = v4;
  return result;
}



// ------------------------------------------------------------
// 0x498B00 sub_498B00
// ------------------------------------------------------------
void /*thiscall*/ sub_498B00(float *this, int a2, int a3)
{
  int v4; // ecx
  double v5; // st7

  v4 = *(uint32_t *)this;
  *((uint8_t *)this + 124) = 1;
  if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 308))(v4) != 0 )
  {
    v5 = (double)a3;
    if ( *(this + a2 + 1) != v5 )
    {
      *(this + a2 + 1) = v5;
      *((uint8_t *)this + 196) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x498B50 sub_498B50
// ------------------------------------------------------------
int /*cdecl*/ sub_498B50(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x498B70 sub_498B70
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_498B70(int this)
{
  DWORD result; // eax

  *(uint32_t *)(this + 92) = 1;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 156) = 1;
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 160) = -1;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint8_t *)(this + 172) = 1;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint8_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = -1;
  *(uint32_t *)(this + 220) = -1;
  *(uint32_t *)(this + 224) = -1;
  *(uint32_t *)(this + 228) = -1;
  *(uint8_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint8_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint8_t *)(this + 256) = 1;
  *(uint32_t *)(this + 260) = 2;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint8_t *)(this + 276) = 1;
  *(uint8_t *)(this + 277) = 0;
  result = timeGetTime();
  *(uint32_t *)(this + 280) = result;
  return result;
}



// ------------------------------------------------------------
// 0x498C40 sub_498C40
// ------------------------------------------------------------
int /*thiscall*/ sub_498C40(void *this)
{
  int i; // edi

  (*(void (/*thiscall*/ **)(void *, uint32_t, int, uint32_t))(*(uint32_t *)this + 228))(this, 0, -1, 0);
  for ( i = 0; i < 4; ++i )
    (*(void (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 252))(this, i, -1);
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 260))(this, 0, 0, 0);
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 272))(this, 0, 0);
  return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 284))(this, 0, 0, 1, 2);
}



// ------------------------------------------------------------
// 0x498CA0 sub_498CA0
// ------------------------------------------------------------
int /*usercall*/ sub_498CA0@<eax>(float *a1@<ecx>, int a2@<edi>)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int result; // eax
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  if ( *((uint32_t *)a1 + 50) != 0
    && *((uint32_t *)a1 + 51) != -1
    && sub_699000((int)(a1 + 2)) >= *((uint32_t *)a1 + 51) + *((uint32_t *)a1 + 52) )
  {
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 232))(a1);
  }
  sub_4A0790(*((uint32_t *)a1 + 28));
  v7 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 128))(a1);
  v8 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 124))(a1);
  v9 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 120))(a1);
  a1[45] = v8;
  a1[46] = v7;
  a1[44] = (float)v9;
  if ( (*(uint8_t (/*thiscall*/ **)(float *, int))(*(uint32_t *)a1 + 40))(a1, 2) != 0 )
  {
    v3 = *(uint32_t *)(*((uint32_t *)a1 + 28) + 104);
    if ( v3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 52))(v3) == 0 )
      (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 84))(a1, 0);
    if ( *((uint8_t *)a1 + 157) != 0 )
    {
      v4 = *((uint32_t *)a1 + 30);
      if ( v4 != 0 && *(uint8_t *)(v4 + 170) != 0 )
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 84))(a1, 0);
    }
  }
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 332))(a1);
  if ( *((uint32_t *)a1 + 41) != 0 )
    sub_50EB10();
  if ( *((uint32_t *)a1 + 42) != 0 )
    sub_50E9B0();
  v5 = *((uint32_t *)a1 + 28);
  if ( *(uint8_t *)(v5 + 196) != 0 )
    sub_49FFC0((uint32_t *)v5, a2, (int)a1, 0, 0);
  result = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)a1 + 40))(a1, 1);
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 564))(a1);
  return result;
}



// ------------------------------------------------------------
// 0x498DE0 sub_498DE0
// ------------------------------------------------------------
bool /*thiscall*/ sub_498DE0(uint32_t *this, int a2)
{
  return (a2 & *(this + 24)) == a2;
}



// ------------------------------------------------------------
// 0x498E00 sub_498E00
// ------------------------------------------------------------
void /*thiscall*/ sub_498E00(uint32_t *this, int a2, int a3, int a4)
{
  int *v5; // esi
  int v6; // ecx
  bool v7; // zf
  double v8; // st7
  int *v9; // esi
  int v10; // ecx
  double v11; // st7
  int *v12; // esi
  int v13; // ecx
  double v14; // st7

  v5 = (int *)*(this + 28);
  v6 = *v5;
  v7 = *v5 == 0;
  *((uint8_t *)v5 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 308))(v6) != 0 )
  {
    v8 = (double)a2;
    if ( *((float *)v5 + 1) != v8 )
    {
      *((float *)v5 + 1) = v8;
      *((uint8_t *)v5 + 196) = 1;
    }
  }
  v9 = (int *)*(this + 28);
  v10 = *v9;
  v7 = *v9 == 0;
  *((uint8_t *)v9 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 308))(v10) != 0 )
  {
    v11 = (double)a3;
    if ( *((float *)v9 + 2) != v11 )
    {
      *((float *)v9 + 2) = v11;
      *((uint8_t *)v9 + 196) = 1;
    }
  }
  v12 = (int *)*(this + 28);
  v13 = *v12;
  v7 = *v12 == 0;
  *((uint8_t *)v12 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 308))(v13) != 0 )
  {
    v14 = (double)a4;
    if ( *((float *)v12 + 3) != v14 )
    {
      *((float *)v12 + 3) = v14;
      *((uint8_t *)v12 + 196) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x498EC0 sub_498EC0
// ------------------------------------------------------------
int /*thiscall*/ sub_498EC0(uint32_t *this, int a2, int a3, int a4)
{
  int v4; // eax
  int result; // eax
  int v6; // ecx

  v4 = *(this + 28);
  *(uint8_t *)(v4 + 124) = 1;
  *(float *)(v4 + 4) = (float)a2;
  result = *(this + 28);
  *(uint8_t *)(result + 124) = 1;
  *(float *)(result + 8) = (float)a3;
  v6 = *(this + 28);
  *(uint8_t *)(v6 + 124) = 1;
  *(float *)(v6 + 12) = (float)a4;
  return result;
}



// ------------------------------------------------------------
// 0x498F00 sub_498F00
// ------------------------------------------------------------
int /*thiscall*/ sub_498F00(int *this, int a2)
{
  int result; // eax
  uint8_t *v3; // esi

  result = *(this + 50);
  if ( result == 0 )
  {
    v3 = (uint8_t *)*(this + 28);
    if ( *(uint32_t *)v3 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v3 + 308))(*(uint32_t *)v3);
      if ( (uint8_t)result != 0 )
      {
        result = a2;
        if ( (char)v3[52] != a2 )
        {
          v3[52] = a2;
          v3[196] = 1;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x498F40 sub_498F40
// ------------------------------------------------------------
int /*thiscall*/ sub_498F40(uint32_t *this, char a2)
{
  int result; // eax

  result = *(this + 50);
  if ( result == 0 )
  {
    result = *(this + 28);
    *(uint8_t *)(result + 52) = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x498F70 sub_498F70
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_498F70(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) != 0
      && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) == dword_8F7C04;
}



// ------------------------------------------------------------
// 0x498FA0 sub_498FA0
// ------------------------------------------------------------
char /*thiscall*/ sub_498FA0(int *this, int a2, int a3)
{
  char result; // al
  int v5; // edi

  if ( *(this + a2 + 54) == -1 )
  {
    *(this + a2 + 54) = a3;
  }
  else
  {
    result = a3;
    if ( a3 == -1 )
    {
      v5 = *(this + 30);
      if ( v5 != 0 )
      {
        sub_4910E0(*(this + 30));
        result = sub_493A60(v5, *(uint32_t *)(v5 + 32));
        *(this + a2 + 54) = -1;
      }
      else
      {
        *(this + a2 + 54) = -1;
      }
    }
    else
    {
      *(this + a2 + 54) = a3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499020 sub_499020
// ------------------------------------------------------------
char /*thiscall*/ sub_499020(int this, char a2, int a3, int a4)
{
  char result; // al
  int v6; // edi

  result = *(uint8_t *)(this + 232);
  if ( result != 0 && a2 == 0 )
  {
    v6 = *(uint32_t *)(this + 120);
    if ( v6 != 0 )
    {
      sub_4910E0(*(uint32_t *)(this + 120));
      result = sub_493A60(v6, *(uint32_t *)(v6 + 32));
    }
  }
  *(uint8_t *)(this + 232) = a2;
  *(uint32_t *)(this + 236) = a3;
  *(uint32_t *)(this + 240) = a4;
  return result;
}



// ------------------------------------------------------------
// 0x499080 sub_499080
// ------------------------------------------------------------
void /*thiscall*/ sub_499080(int this, char a2, float a3)
{
  double v4; // st7
  int v5; // esi

  if ( a2 != 0 )
  {
    v4 = a3;
  }
  else
  {
    v4 = 0.0;
    a3 = 0.0;
  }
  if ( *(float *)(this + 244) == 0.0 || v4 != 0.0 )
  {
    *(float *)(this + 244) = v4;
  }
  else
  {
    v5 = *(uint32_t *)(this + 120);
    if ( v5 != 0 )
    {
      sub_4910E0(*(uint32_t *)(this + 120));
      sub_493A60(v5, *(uint32_t *)(v5 + 32));
      *(float *)(this + 244) = a3;
    }
    else
    {
      *(float *)(this + 244) = v4;
    }
  }
}



// ------------------------------------------------------------
// 0x499110 sub_499110
// ------------------------------------------------------------
char /*thiscall*/ sub_499110(uint8_t *this, void *Src, int a3, int a4, int a5)
{
  char result; // al
  int v7; // eax

  result = 0;
  if ( strcmp((const char *)Src, szPassword) != 0 )
  {
    result = *(this + 172);
    if ( result != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 56))(this);
      return sub_65FE10(Src, (int)(this + 176), a4, a5, 0, v7, a3);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499170 sub_499170
// ------------------------------------------------------------
int /*thiscall*/ sub_499170(void *this, int a2)
{
  int v2; // eax

  v2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
  return sub_65DE30(v2, a2);
}



// ------------------------------------------------------------
// 0x499190 sub_499190
// ------------------------------------------------------------
int /*thiscall*/ sub_499190(uint32_t *this, int a2)
{
  int result; // eax

  result = a2;
  if ( *(uint32_t *)(*(this + 28) + 128) == a2 && a2 != 0 )
  {
    sub_4A06D0(0);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 2);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 84))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4991D0 sub_4991D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4991D0(uint32_t *this)
{
  void *v2; // eax
  void *v3; // esi

  if ( *(this + 42) == 0 )
  {
    v2 = operator new(0x10u);
    v3 = v2;
    if ( v2 != nullptr )
    {
      sub_50E730(v2);
      sub_50E8D0(this);
    }
    else
    {
      v3 = nullptr;
    }
    *(this + 42) = v3;
  }
  return *(this + 42);
}



// ------------------------------------------------------------
// 0x499240 sub_499240
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_499240(int a1, int a2, int a3, int a4, char a5)
{
  int v5; // eax

  v5 = a2 - a4;
  if ( a5 == 0 )
    v5 = 100 * v5 / dword_7930D4[0];
  return (uint64_t)sqrt((double)((a1 - a3) * (a1 - a3) + v5 * v5));
}



// ------------------------------------------------------------
// 0x499280 sub_499280
// ------------------------------------------------------------
double /*thiscall*/ sub_499280(void *this, int a2, char a3)
{
  int v4; // ebx
  int v5; // ebx
  int v6; // edi
  int v7; // edi
  double result; // st7
  int v9; // [esp+18h] [ebp+8h]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  v5 = v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
  v7 = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  v9 = v7;
  if ( a3 == 0 )
  {
    v7 = 100 * v7 / dword_7930D4[0];
    v9 = v7;
  }
  if ( v5 != 0 )
  {
    result = atan2((double)v9 / (double)v5, 1.0) * 57.29577951308232;
    if ( v5 >= 0 )
    {
      if ( v7 < 0 )
        return result + 360.0;
    }
    else
    {
      return result + 180.0;
    }
  }
  else if ( v7 < 0 )
  {
    return 270.0;
  }
  else
  {
    return 90.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x499330 sub_499330
// ------------------------------------------------------------
long double /*thiscall*/ sub_499330(void *this, int a2, int a3)
{
  int v4; // esi
  signed int v5; // esi
  int v6; // ebx
  int v7; // ebx

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  v5 = abs32(v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this));
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2);
  v7 = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
  if ( v5 != 0 )
    return atan2((double)(v7 / v5), 1.0) * 57.29577951308232;
  if ( v7 < 0 )
    return -90.0;
  return 90.0;
}



// ------------------------------------------------------------
// 0x4993B0 sub_4993B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4993B0(void *this, int *a2, int *a3, int a4, int a5, int a6, char a7, int a8)
{
  int v8; // esi
  int v9; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // esi
  int v14; // ecx
  int v15; // ebx
  int v16; // edi
  int v17; // esi
  int v19; // [esp+10h] [ebp-4h]
  int v20; // [esp+30h] [ebp+1Ch]
  int v21; // [esp+30h] [ebp+1Ch]

  v8 = 0;
  v19 = 0;
  if ( a7 != 0 )
  {
    v9 = a8 + 2 * a6;
    v20 = v9;
    if ( v9 > 0 )
    {
      while ( 1 )
      {
        v10 = v8 % 2 != 0 ? a5 - (v8 + 1) / 2 : a5 + v8 / 2;
        v11 = 0;
        if ( v9 > 0 )
          break;
LABEL_13:
        v8 += a8;
        v19 = v8;
        if ( v8 >= v9 )
          return 0;
      }
      while ( 1 )
      {
        v12 = v11 % 2 != 0 ? a4 - (v11 + 1) / 2 : a4 + v11 / 2;
        if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v12, v10, 0) != 0 )
          break;
        v11 += a8;
        if ( v11 >= v20 )
        {
          v8 = v19;
          v9 = v20;
          goto LABEL_13;
        }
      }
      *a2 = v12;
      *a3 = v10;
      return 1;
    }
    return 0;
  }
  v14 = a8 + 2 * a6;
  v21 = v14;
  if ( v14 <= 0 )
    return 0;
  while ( 1 )
  {
    v15 = v8 % 2 != 0 ? a4 - (v8 + 1) / 2 : a4 + v8 / 2;
    v16 = 0;
    if ( v14 > 0 )
      break;
LABEL_27:
    v8 += a8;
    v19 = v8;
    if ( v8 >= v14 )
      return 0;
  }
  while ( 1 )
  {
    v17 = v16 % 2 != 0 ? a5 - (v16 + 1) / 2 : a5 + v16 / 2;
    if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v15, v17, 0) != 0 )
      break;
    v16 += a8;
    if ( v16 >= v21 )
    {
      v8 = v19;
      v14 = v21;
      goto LABEL_27;
    }
  }
  *a2 = v15;
  *a3 = v17;
  return 1;
}



// ------------------------------------------------------------
// 0x499560 sub_499560
// ------------------------------------------------------------
char /*cdecl*/ sub_499560(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int v6; // edi
  int v8; // [esp+Ch] [ebp-4h]

  v8 = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)a1 + 140))(
         a1,
         a2,
         a3,
         a4,
         a5,
         30,
         1,
         1) != 0 )
    return 1;
  v6 = 30;
  while ( 1 )
  {
    v6 += 10;
    if ( ++v8 >= a6 )
      break;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)a1 + 140))(
           a1,
           a2,
           a3,
           a4,
           a5,
           v6,
           1,
           1) != 0 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4995F0 sub_4995F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4995F0(void *this, uint32_t *a2, uint32_t *a3, int a4, int a5)
{
  int v6; // ebx
  double v7; // st7
  int result; // eax
  int v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int v11; // [esp+14h] [ebp-4h]
  float v12; // [esp+2Ch] [ebp+14h]

  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 120))(a4);
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 124))(a4);
  v11 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  v9 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  v12 = (float)a5;
  v7 = 1.0 - v12 / (double)(*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 8))(this, a4, 1);
  *a2 = v11 + (uint64_t)((double)(v6 - v11) * v7);
  result = v9 + (uint64_t)((double)(v10 - v9) * v7);
  *a3 = result;
  return result;
}



// ------------------------------------------------------------
// 0x499690 sub_499690
// ------------------------------------------------------------
void /*cdecl*/ sub_499690(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        float a6,
        int a7,
        float a8,
        int a9,
        float a10,
        int a11,
        float a12,
        float a13)
{
  int v13; // eax
  float v14; // [esp+1Ch] [ebp+1Ch]

  if ( LOBYTE(a6) != 0 )
  {
    v14 = -a8;
    v13 = a2 - a4;
  }
  else
  {
    v14 = a8;
    v13 = a2 + a4;
  }
  sub_424760(a1, v13, a5 + a3, a7, v14, a9, a10, a11, a12, a13);
}



// ------------------------------------------------------------
// 0x4996F0 sub_4996F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4996F0(uint32_t *this)
{
  double v1; // st7

  v1 = *(float *)(*(this + 28) + 16);
  if ( v1 > 5.0 )
    return 1;
  if ( v1 >= -5.0 )
    return _RTC_NumErrors();
  return 0;
}



// ------------------------------------------------------------
// 0x49971B __RTC_NumErrors
// ------------------------------------------------------------
int /*cdecl*/ _RTC_NumErrors()
{
  return 4;
}



// ------------------------------------------------------------
// 0x499730 sub_499730
// ------------------------------------------------------------
int /*thiscall*/ sub_499730(uint32_t *this)
{
  double v1; // st7
  int result; // eax

  v1 = *(float *)(*(this + 28) + 20);
  if ( v1 > 5.0 )
    return 3;
  result = 2;
  if ( v1 >= -5.0 )
    return 4;
  return result;
}



// ------------------------------------------------------------
// 0x499770 sub_499770
// ------------------------------------------------------------
int /*thiscall*/ sub_499770(uint32_t *this, int a2, int a3)
{
  *(this + 67) = a2;
  *(this + 68) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x4997A0 sub_4997A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4997A0(int this, int a2)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint32_t *)(this + 44) = -1;
  *(uint32_t *)(this + 48) = -1;
  *(uint8_t *)(this + 52) = 1;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 65) = 0;
  *(uint32_t *)(this + 77) = 0;
  *(uint32_t *)(this + 89) = -1;
  *(uint32_t *)(this + 57) = 0;
  *(uint32_t *)(this + 69) = 0;
  *(uint32_t *)(this + 81) = 0;
  *(uint32_t *)(this + 93) = -1;
  *(uint32_t *)(this + 61) = 0;
  *(uint32_t *)(this + 73) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint32_t *)(this + 97) = -1;
  *(uint8_t *)(this + 101) = 1;
  *(uint8_t *)(this + 148) = 0;
  *(uint32_t *)(this + 144) = &off_6C2B88;
  *(uint32_t *)(this + 152) = 0;
  *(uint8_t *)(this + 156) = 1;
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 160) = 0;
  sub_49FC60(this);
  sub_4A0770(a2);
  return this;
}



// ------------------------------------------------------------
// 0x499880 sub_499880
// ------------------------------------------------------------
int /*thiscall*/ sub_499880(int this)
{
  int result; // eax

  result = sub_649170();
  *(uint32_t *)(this + 144) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 148) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4998D0 sub_4998D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4998D0(int a1)
{
  if ( dword_9A0268 == 0 )
  {
    if ( (dword_9A024C & 1) == 0 )
    {
      dword_9A024C |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BF9D0);
    }
    dword_9A0268 = (int)&unk_9A022C;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x499960 sub_499960
// ------------------------------------------------------------
int /*thiscall*/ sub_499960(int this, void *Block, int a3, int a4)
{
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 4) = &off_6C2B88;
  *(uint32_t *)(this + 12) = 0;
  *(uint8_t *)(this + 16) = 1;
  *(uint8_t *)(this + 18) = 0;
  *(uint8_t *)(this + 17) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  sub_50EAD0();
  sub_50F1C0(Block, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x4999D0 sub_4999D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4999D0(int this)
{
  int result; // eax

  result = sub_50EAF0();
  *(uint32_t *)(this + 4) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x499A20 sub_499A20
// ------------------------------------------------------------
int /*thiscall*/ sub_499A20(uint32_t *this, int a2, char a3)
{
  int v4; // eax
  int v5; // eax
  int result; // eax

  sub_698F90((int)(this + 2), 0, 0);
  sub_698F90((int)(this + 9), 0, 0);
  sub_698F90((int)(this + 16), 0, 0);
  if ( sub_4998D0(204) != 0 )
    v4 = sub_4997A0(this);
  else
    v4 = 0;
  *(this + 28) = v4;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 92))(this, a2);
  v5 = *this;
  *(this + 24) = 2;
  *((uint8_t *)this + 157) = a3;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 72))(this, 1);
  *((uint8_t *)this + 264) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x499AD0 sub_499AD0
// ------------------------------------------------------------
int /*thiscall*/ sub_499AD0(void *Block)
{
  void *v2; // eax
  int v3; // eax

  if ( *((uint32_t *)Block + 41) == 0 )
  {
    v2 = operator new(0x44u);
    if ( v2 != nullptr )
      v3 = sub_499960((int)v2, Block, 120, 0);
    else
      v3 = 0;
    *((uint32_t *)Block + 41) = v3;
  }
  return *((uint32_t *)Block + 41);
}



// ------------------------------------------------------------
// 0x499B40 sub_499B40
// ------------------------------------------------------------
int /*thiscall*/ sub_499B40(uint32_t *this)
{
  return sub_499A20(this, 0, 0);
}



// ------------------------------------------------------------
// 0x499B50 sub_499B50
// ------------------------------------------------------------
char /*thiscall*/ sub_499B50(char *this, char a2)
{
  char result; // al
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edx
  char *v9; // edi
  int v10; // eax

  result = a2;
  if ( (a2 != 0 || (result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this)) != 0) && *(this + 264) != 1 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 23, 2);
    v4 = *(uint32_t *)dword_8F8520;
    v5 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
    v6 = *(uint32_t *)dword_8F8520;
    v7 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    v8 = *(uint32_t *)this;
    *(this + 264) = 1;
    result = (*(int (/*thiscall*/ **)(char *, int))(v8 + 40))(this, 529);
    if ( result != 0 )
    {
      if ( *((uint32_t *)this + 78) < 0x10u )
        v9 = this + 292;
      else
        v9 = *((char **)this + 73);
      v10 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
      return off_77F3FC((char *)&byte_6CB870, v9, v10);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499C20 sub_499C20
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_499C20(int a1, int a2, uint32_t *a3)
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
  {
    *result = a1;
    result[1] = a2;
    result[2] = *a3;
    result[3] = a3[1];
    result[4] = a3[2];
    result[5] = a3[3];
    result[6] = a3[4];
  }
  return result;
}



// ------------------------------------------------------------
// 0x499C70 sub_499C70
// ------------------------------------------------------------
int /*thiscall*/ sub_499C70(uint8_t *this)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int result; // eax
  int v18; // [esp-Ch] [ebp-28h]
  int v19; // [esp-8h] [ebp-24h]
  int v20; // [esp-4h] [ebp-20h]
  int v21; // [esp+Ch] [ebp-10h]
  int v22; // [esp+10h] [ebp-Ch]
  int v23; // [esp+10h] [ebp-Ch]
  int v24; // [esp+14h] [ebp-8h]
  int v25; // [esp+14h] [ebp-8h]
  float v26; // [esp+18h] [ebp-4h]

  v2 = *((uint32_t *)this + 30);
  if ( v2 != 0 )
  {
    sub_4938F0(v2);
    v3 = *(uint32_t *)(*((uint32_t *)this + 28) + 104);
    v4 = *((uint32_t *)this + 57);
    v24 = v4;
    if ( v3 != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)v3 + 64))(v3) )
    {
      if ( v4 == -1 )
        v24 = 255;
      v4 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)this + 28) + 104)
                                                                        + 64))(*(uint32_t *)(*((uint32_t *)this + 28) + 104))
                            * (double)v24
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)this + 54), *((uint32_t *)this + 55), *((uint32_t *)this + 56), v4, 1);
    if ( *(this + 232) != 0 )
      sub_492030(*((uint32_t *)this + 59), *((uint32_t *)this + 60), 1);
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 276))(this) != 0 )
      sub_492080(*((float *)this + 61));
  }
  v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this);
  v6 = sub_45E490(v5, v20);
  v21 = v6;
  v19 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);
  v18 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  v7 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
  v25 = sub_45E4D0(v7, v18, v19, 1.0);
  LOBYTE(v26) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 1;
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int, int, uint8_t))(*(uint32_t *)this + 324))(
    this,
    0,
    v6,
    v25,
    LOBYTE(v26));
  v8 = *((uint32_t **)this + 32);
  v9 = (uint32_t *)*v8;
  if ( (uint32_t *)*v8 != v8 )
  {
    do
    {
      if ( (int)v9[2] >= 0 )
        break;
      if ( *((uint8_t *)v9 + 25) == 0 )
      {
        sub_4938F0(v9[3]);
        if ( LOBYTE(v26) != 0 )
          v11 = v6 - v9[4];
        else
          v11 = v6 + v9[4];
        LOBYTE(v10) = (*((uint8_t *)v9 + 24) != 0) - 1;
        sub_491D00(dword_79C0B0, v11, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v10));
      }
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *((uint32_t **)this + 32) );
  }
  if ( *((uint32_t *)this + 30) != 0 )
  {
    if ( *(this + 248) != 0 )
    {
      if ( *(this + 256) != 0 )
      {
        v12 = rand();
        v22 = v12 % 3 - 1;
        if ( v12 % 3 == 1 )
          v13 = rand() % 2 != 0 ? 2 : 0;
        else
          v13 = rand() % 3;
        sub_491DE0(
          dword_79C0B0,
          v6 + v22 * *((uint32_t *)this + 65),
          v25 + (v13 - 1) * *((uint32_t *)this + 65),
          v26,
          0,
          1,
          *((uint32_t *)this + 63),
          -1761607681);
      }
      else
      {
        v14 = 0;
        v23 = 0;
        do
        {
          if ( v14 != 4 )
          {
            v6 = v21;
            sub_491DE0(
              dword_79C0B0,
              v21 + *((uint32_t *)this + 65) * (v14 / 3u - 1),
              v25 + *((uint32_t *)this + 65) * (v14 % 3u - 1),
              v26,
              0,
              1,
              *((uint32_t *)this + 63),
              (*(this + 255) << 24) | 0xFFFFFF);
            v14 = v23;
          }
          v23 = ++v14;
        }
        while ( v14 < 9 );
      }
    }
    sub_491D00(dword_79C0B0, v6 + *((uint32_t *)this + 67), v25 + *((uint32_t *)this + 68), v26);
  }
  for ( ; v9 != *((uint32_t **)this + 32); v9 = (uint32_t *)*v9 )
  {
    if ( *((uint8_t *)v9 + 25) == 0 )
    {
      sub_4938F0(v9[3]);
      if ( LOBYTE(v26) != 0 )
      {
        v15 = v9[4];
        v16 = v6 - v15;
      }
      else
      {
        v16 = v6 + v9[4];
      }
      LOBYTE(v15) = (*((uint8_t *)v9 + 24) != 0) - 1;
      sub_491D00(dword_79C0B0, v16, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v15));
    }
  }
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int, uint8_t))(*(uint32_t *)this + 324))(
             this,
             1,
             v6,
             v25,
             LOBYTE(v26));
  if ( *((uint32_t *)this + 41) != 0 )
    result = sub_50EB40(v6, v25, 255);
  if ( *((uint32_t *)this + 42) != 0 )
    return sub_50E750(v6, v25);
  return result;
}


// ------------------------------------------------------------
// 0x499FF0 sub_499FF0
// ------------------------------------------------------------
int /*usercall*/ sub_499FF0@<eax>(float *a1@<ecx>, float a2@<ebx>)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  uint32_t *v10; // eax
  uint32_t *v11; // edi
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // esi
  int v23; // [esp-Ch] [ebp-20h]
  int v24; // [esp-8h] [ebp-1Ch]
  int v25; // [esp+8h] [ebp-Ch]
  int v26; // [esp+8h] [ebp-Ch]
  int v27; // [esp+Ch] [ebp-8h]
  float v28; // [esp+10h] [ebp-4h]

  v3 = *((uint32_t *)a1 + 30);
  if ( v3 != 0 )
  {
    sub_4938F0(v3);
    v4 = *(uint32_t *)(*((uint32_t *)a1 + 28) + 104);
    v5 = *((uint32_t *)a1 + 57);
    v25 = v5;
    if ( v4 != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)v4 + 64))(v4) )
    {
      if ( v5 == -1 )
        v25 = 255;
      v5 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)a1 + 28) + 104) + 64))(*(uint32_t *)(*((uint32_t *)a1 + 28) + 104))
                            * (double)v25
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)a1 + 30), *((uint32_t *)a1 + 54), *((uint32_t *)a1 + 55), *((uint32_t *)a1 + 56), v5, 1);
    if ( (*(uint8_t (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 276))(a1) != 0 )
      sub_492080(*((uint32_t *)a1 + 30), a1[61]);
  }
  v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 36))(a1) + 8);
  v6 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 120))(a1);
  v27 = sub_45E490(v6, v24);
  v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 36))(a1) + 8);
  v7 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 128))(a1);
  v8 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)a1 + 124))(a1, v7);
  v9 = sub_45E4D0(v8, v23, 0, a2);
  v26 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 128))(a1);
  LOBYTE(v28) = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 152))(a1) != 1;
  (*(void (/*thiscall*/ **)(float *, uint32_t, int, int, uint8_t))(*(uint32_t *)a1 + 328))(
    a1,
    0,
    v27 + *((uint32_t *)a1 + 67),
    v9 + *((uint32_t *)a1 + 68),
    LOBYTE(v28));
  v10 = *((uint32_t **)a1 + 32);
  v11 = (uint32_t *)*v10;
  if ( (uint32_t *)*v10 != v10 )
  {
    do
    {
      if ( (int)v11[2] >= 0 )
        break;
      sub_4938F0(v11[3]);
      if ( *((uint8_t *)v11 + 25) != 0 )
      {
        v14 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];
        LOBYTE(v13) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491D00(v11[3], dword_79C0B0, v14, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v13));
      }
      else
      {
        v15 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];
        LOBYTE(v12) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491EA0(
          v11[3],
          dword_79C0B0,
          v15,
          v9 + v11[5],
          COERCE_FLOAT(LODWORD(v28) & v12),
          v26,
          0.40000001,
          0.30000001,
          100);
      }
      v11 = (uint32_t *)*v11;
    }
    while ( v11 != *((uint32_t **)a1 + 32) );
  }
  v16 = *((uint32_t *)a1 + 30);
  if ( v16 != 0 )
    sub_491EA0(v16, dword_79C0B0, v27, v9, v28, v26, 0.40000001, 0.30000001, 100);
  for ( ; v11 != *((uint32_t **)a1 + 32); v11 = (uint32_t *)*v11 )
  {
    sub_4938F0(v11[3]);
    if ( *((uint8_t *)v11 + 25) != 0 )
    {
      if ( LOBYTE(v28) != 0 )
        v19 = v27 - v11[4];
      else
        v19 = v27 + v11[4];
      LOBYTE(v18) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491D00(v11[3], dword_79C0B0, v19, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v18));
    }
    else
    {
      if ( LOBYTE(v28) != 0 )
        v20 = v27 - v11[4];
      else
        v20 = v27 + v11[4];
      LOBYTE(v17) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491EA0(
        v11[3],
        dword_79C0B0,
        v20,
        v9 + v11[5],
        COERCE_FLOAT(LODWORD(v28) & v17),
        v26,
        0.40000001,
        0.30000001,
        100);
    }
  }
  (*(void (/*thiscall*/ **)(float *, int, int, int))(*(uint32_t *)a1 + 328))(a1, 1, v27, v9);
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( *(uint32_t *)(result + 44) != 0 )
    {
      result = *((uint32_t *)a1 + 24);
      if ( result == 273 || result == 529 )
      {
        v22 = *((uint32_t *)a1 + 30);
        if ( v22 != 0 )
          *(uint8_t *)(v22 + 161) = 1;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x49A320 sub_49A320
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_49A320(uint32_t *this, int a2, uint32_t **a3, int a4)
{
  uint32_t **result; // eax
  int v5; // ebx
  int v7; // edi
  int v8; // edi
  int v9; // eax
  uint32_t *v10; // edi
  int v11; // eax
  uint32_t *v12; // edi
  int j; // edi
  int v14; // eax
  int i; // edi
  int v16; // eax
  int v17; // [esp+14h] [ebp+8h]

  result = a3;
  v5 = a2;
  if ( a2 != 0 && a3 == nullptr )
    v5 = 0;
  v7 = *(this + 50);
  v17 = v7;
  *(this + 50) = v5;
  if ( v5 != 0 )
  {
    *(this + 51) = a3;
    result = (uint32_t **)(a4 + sub_699000(this + 2));
    *(this + 52) = result;
  }
  if ( v7 != v5 )
  {
    if ( v7 < 1 )
    {
      if ( v5 >= 1 )
      {
        v8 = *(this + 30);
        if ( v8 != 0 )
        {
          if ( *(uint32_t *)(v8 + 212) != 0 )
            *((uint8_t *)this + 212) = sub_4910C0();
          else
            *((uint8_t *)this + 212) = *(uint8_t *)(v8 + 169);
          sub_4939E0(1);
        }
        else
        {
          *((uint8_t *)this + 212) = 0;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )
            goto LABEL_20;
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
        }
        sub_699030(v9);
LABEL_20:
        sub_4A0680(1);
        sub_699030(this + 9);
        result = (uint32_t **)*(this + 32);
        v10 = *result;
        if ( *result != result )
        {
          do
          {
            result = (uint32_t **)sub_4939E0(1);
            v10 = (uint32_t *)*v10;
          }
          while ( v10 != (uint32_t *)*(this + 32) );
        }
      }
LABEL_34:
      if ( v17 >= 2 )
      {
        if ( v5 < 2 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);
            sub_53F720(0);
            for ( i = 0; i < 17; ++i )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, i) != 0 )
              {
                v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, i);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v16 + 36))(v16, 0);
              }
            }
          }
          return (uint32_t **)sub_698FE0(this + 16);
        }
      }
      else if ( v5 >= 2 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);
          sub_53F720(1);
          for ( j = 0; j < 17; ++j )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, j) != 0 )
            {
              v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, j);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 36))(v14, 1);
            }
          }
        }
        return (uint32_t **)sub_699030(this + 16);
      }
      return result;
    }
    if ( v5 >= 1 )
      goto LABEL_34;
    if ( *((uint8_t *)this + 212) == 0 && *(this + 30) != 0 )
      sub_4939E0(0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )
        goto LABEL_32;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    }
    sub_698FE0(v11);
LABEL_32:
    sub_4A0680(0);
    sub_698FE0(this + 9);
    result = (uint32_t **)*(this + 32);
    v12 = *result;
    if ( *result != result )
    {
      do
      {
        result = (uint32_t **)sub_4939E0(0);
        v12 = (uint32_t *)*v12;
      }
      while ( v12 != (uint32_t *)*(this + 32) );
    }
    goto LABEL_34;
  }
  return result;
}


// ------------------------------------------------------------
// 0x49A590 sub_49A590
// ------------------------------------------------------------
int /*thiscall*/ sub_49A590(uint32_t *this, int a2)
{
  uint32_t **v3; // eax
  uint32_t *v4; // esi

  *(this + 23) = a2;
  sub_699070(a2);
  sub_699070(a2);
  sub_699070(a2);
  if ( *(this + 30) != 0 )
    sub_699070(a2);
  v3 = (uint32_t **)*(this + 32);
  v4 = *v3;
  if ( *v3 != v3 )
  {
    do
    {
      sub_699070(a2);
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != (uint32_t *)*(this + 32) );
  }
  return sub_4A0740(a2);
}



// ------------------------------------------------------------
// 0x49A600 sub_49A600
// ------------------------------------------------------------
char /*thiscall*/ sub_49A600(void *this, char a2, int a3, int a4, int a5)
{
  char result; // al
  int v6; // eax
  uint8_t v7; // bl
  int v8; // eax

  result = a2;
  if ( a2 == 0 && ((void *)dword_8F7C08 == this || (void *)dword_8F7C04 == this) )
  {
    v6 = sub_699000((int)this + 64);
    v7 = sub_42B420(150, 255, v6, 400);
    sub_491530(2, 0);
    v8 = sub_418DD0(101);
    sub_424760(dword_79C0B0, a3 - 63, a4 - 21, v8, 1.0, 1065353216, 0.0, (v7 << 24) | 0xFFFFFF, 0.0, 0.0);
    return sub_491630(2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49A6B0 sub_49A6B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A6B0(void ***this, void *a2)
{
  void **v3; // ecx
  void **v4; // eax

  if ( a2 != nullptr )
  {
    v3 = *(this + 32);
    v4 = (void **)*v3;
    if ( *v3 != v3 )
    {
      while ( v4[3] != a2 )
      {
        v4 = (void **)*v4;
        if ( v4 == v3 )
          return;
      }
      if ( v4 != *(this + 32) )
      {
        *(uint32_t *)v4[1] = *v4;
        *((uint32_t *)*v4 + 1) = v4[1];
        j__free(v4);
        *(this + 33) = (void **)((char *)*(this + 33) - 1);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x49A720 sub_49A720
// ------------------------------------------------------------
int /*thiscall*/ sub_49A720(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 214748364 - v2 < a2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x49A7B0 sub_49A7B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A7B0(uint32_t *this, int a2, int a3, int a4, int a5, char a6, char a7)
{
  uint32_t **v8; // eax
  uint32_t *v9; // esi
  bool v10; // zf
  uint32_t *v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // edi
  uint32_t v14[4]; // [esp+8h] [ebp-14h] BYREF
  char v15; // [esp+18h] [ebp-4h]
  char v16; // [esp+19h] [ebp-3h]

  if ( a3 != 0 )
  {
    sub_699070(*(this + 23));
    v14[3] = a5;
    v16 = a7;
    v8 = (uint32_t **)*(this + 32);
    v14[1] = a3;
    v9 = *v8;
    v10 = *v8 == v8;
    v14[2] = a4;
    v14[0] = a2;
    v15 = a6;
    if ( !v10 )
    {
      do
      {
        if ( v9[2] > a2 )
          break;
        v9 = (uint32_t *)*v9;
      }
      while ( v9 != v8 );
    }
    v11 = sub_499C20((int)v9, v9[1], v14);
    v12 = this + 31;
    v13 = v11;
    sub_49A720(v12, 1u);
    v9[1] = v13;
    *(uint32_t *)v13[1] = v13;
    sub_4926A0(a3);
  }
}



// ------------------------------------------------------------
// 0x49A850 sub_49A850
// ------------------------------------------------------------
void /*thiscall*/ sub_49A850(void *this)
{
  int v2; // eax
  int v3; // ebx
  void **v4; // ebx
  unsigned int i; // ebx
  int v6; // ecx
  int v7; // edi
  void **v8; // ecx
  void *v9; // ebx
  void *v10; // ebx
  void **v11; // [esp+Ch] [ebp-4h]

  if ( lpCriticalSection != nullptr )
  {
    v2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
    sub_65DF60(v2);
  }
  if ( *((uint32_t *)this + 29) != 0 )
    sub_45F1E0(this);
  v3 = *((uint32_t *)this + 28);
  if ( v3 != 0 )
  {
    sub_499880(*((uint32_t *)this + 28));
    sub_657740(v3, 204);
  }
  v4 = *((void ***)this + 34);
  *((uint32_t *)this + 28) = 0;
  if ( v4 != nullptr )
  {
    sub_42AF90(v4);
    sub_657740(v4, 228);
  }
  *((uint32_t *)this + 34) = 0;
  for ( i = 0; ; ++i )
  {
    v6 = *((uint32_t *)this + 36);
    if ( v6 == 0 || i >= (*((uint32_t *)this + 37) - v6) >> 2 )
      break;
    v7 = 4 * i;
    v8 = *(void ***)(v6 + 4 * i);
    if ( v8 != nullptr )
    {
      v11 = v8;
      sub_42AF90(v8);
      sub_657740(v11, 228);
    }
    *(uint32_t *)(v7 + *((uint32_t *)this + 36)) = 0;
  }
  if ( *((uint32_t *)this + 36) != 0 )
    j__free(*((void **)this + 36));
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  v9 = *((void **)this + 41);
  if ( v9 != nullptr )
  {
    sub_4999D0(*((uint32_t *)this + 41));
    j__free(v9);
  }
  v10 = *((void **)this + 42);
  *((uint32_t *)this + 41) = 0;
  if ( v10 != nullptr )
  {
    sub_50E950(v10);
    j__free(v10);
  }
  *((uint32_t *)this + 42) = 0;
}



// ------------------------------------------------------------
// 0x49A9A0 sub_49A9A0
// ------------------------------------------------------------
char /*thiscall*/ sub_49A9A0(int this)
{
  *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49A9D0 sub_49A9D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49A9D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax

  for ( result = a1; result != a2; ++result )
    *result = *a3;
  return result;
}



// ------------------------------------------------------------
// 0x49A9F0 sub_49A9F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49A9F0(uint32_t *this)
{
  unsigned int i; // edx
  int v2; // esi
  unsigned int result; // eax

  *(this + 7) = 0;
  for ( i = 0; ; ++i )
  {
    v2 = *(this + 9);
    if ( v2 == 0 )
      break;
    result = (*(this + 10) - v2) >> 2;
    if ( i >= result )
      break;
    result = *(uint32_t *)(v2 + 4 * i);
    *(uint32_t *)(result + 12) = 0;
    *(uint8_t *)(result + 16) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49AA30 sub_49AA30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AA30(uint32_t *this, int a2, char a3)
{
  unsigned int i; // edi
  int v4; // edx
  int v5; // esi
  unsigned int result; // eax

  for ( i = 0; ; ++i )
  {
    v4 = *(this + 12) + 4 * *(this + 10);
    v5 = *(uint32_t *)(*(uint32_t *)v4 + 36);
    result = *(uint32_t *)v4 + 32;
    if ( v5 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)v4 + 40) - v5) >> 2;
    if ( i >= result )
      break;
    if ( **(int16_t **)(4 * i + *(uint32_t *)(*(uint32_t *)v4 + 36)) == a2 )
      *(uint8_t *)(*(uint32_t *)(4 * i + *(uint32_t *)(*(uint32_t *)v4 + 36)) + 16) = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49AA90 sub_49AA90
// ------------------------------------------------------------
char /*thiscall*/ sub_49AA90(int this, const char *a2)
{
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int v7; // esi

  for ( i = 0; ; ++i )
  {
    v4 = *(uint32_t *)(this + 48);
    if ( v4 == 0 || i >= (*(uint32_t *)(this + 52) - v4) >> 2 )
      break;
    if ( sub_40BF00(*(std::_String_base **)(v4 + 4 * i), 0, *(uint32_t *)(*(uint32_t *)(v4 + 4 * i) + 20), a2, strlen(a2)) == 0 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 1;
      *(uint8_t *)(this + 8) = 1;
      *(uint8_t *)(this + 73) = 0;
      *(uint8_t *)(this + 74) = 0;
      sub_698F90(this + 60, 0, 0);
      v5 = *(uint32_t *)(this + 48);
      *(uint32_t *)(this + 40) = i;
      sub_49A9F0(*(uint32_t **)(v5 + 4 * i));
      return 1;
    }
  }
  if ( *(uint32_t *)(this + 36) < 0x10u )
    v7 = this + 16;
  else
    v7 = *(uint32_t *)(this + 16);
  off_77F3FC(aErrorS, v7, a2);
  return 0;
}



// ------------------------------------------------------------
// 0x49AB50 sub_49AB50
// ------------------------------------------------------------
int /*thiscall*/ sub_49AB50(uint32_t *this)
{
  uint32_t *v1; // edx
  uint32_t *v2; // eax
  int v3; // esi
  int v4; // edi
  unsigned int v5; // edx
  unsigned int v6; // esi

  v1 = *(uint32_t **)(*(this + 12) + 4 * *(this + 10));
  v2 = v1;
  v3 = v1[9];
  v4 = v1[7];
  if ( v3 != 0 )
    v5 = (v1[10] - v3) >> 2;
  else
    v5 = 0;
  v6 = v2[7] + 1;
  if ( v6 < v5 )
    v2[7] = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 12))(
           this,
           v4,
           *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28));
}



// ------------------------------------------------------------
// 0x49ABA0 sub_49ABA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49ABA0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  unsigned int result; // eax
  int v7; // esi

  v3 = *(this + 12);
  v4 = *(this + 10);
  v5 = *(uint32_t *)(v3 + 4 * v4);
  result = v3 + 4 * v4;
  if ( a2 == *(uint32_t *)(v5 + 28) )
  {
    v7 = *(uint32_t *)(*(uint32_t *)(v5 + 36) + 4 * a2);
    result = sub_699000((int)(this + 15)) - *(uint32_t *)(v7 + 12);
    if ( result >= *(uint32_t *)(v7 + 8) )
      return sub_49AB50(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ABF0 sub_49ABF0
// ------------------------------------------------------------
char /*thiscall*/ sub_49ABF0(uint32_t *this, int a2)
{
  int v2; // esi
  int v3; // eax
  int v4; // eax
  uint32_t *v5; // eax

  v3 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * a2;
  v2 = *(uint32_t *)v3;
  LOBYTE(v3) = *(uint8_t *)(*(uint32_t *)v3 + 20);
  if ( (uint8_t)v3 == 0 )
  {
    if ( *(uint32_t *)(v2 + 52) < 0x10u )
      v4 = v2 + 32;
    else
      v4 = *(uint32_t *)(v2 + 32);
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v4);
    v3 = sub_418DD0(v5, *(uint32_t *)(v2 + 24));
    if ( v3 != 0 )
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v3 + 152))(
                     v3,
                     dword_6CB988[*(int16_t *)(v2 + 22)],
                     dword_6CB990[*(int16_t *)(v2 + 22)],
                     dword_79C0B0);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x49AC70 sub_49AC70
// ------------------------------------------------------------
int /*thiscall*/ sub_49AC70(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // esi
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  int v8; // eax
  int result; // eax
  float v10; // [esp+4h] [ebp-34h]
  float v11; // [esp+8h] [ebp-30h]
  int v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+2Ch] [ebp-Ch]
  int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]
  int v17; // [esp+34h] [ebp-4h]

  v3 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * a2;
  v4 = *(uint32_t *)v3;
  if ( *(uint32_t *)(*(uint32_t *)v3 + 44) < 0x10u )
    v5 = v4 + 24;
  else
    v5 = *(uint32_t *)(v4 + 24);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
  v14 = *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 20);
  v16 = 0;
  v17 = 0;
  v13 = 480 - *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 24);
  v7 = sub_699000((int)(this + 15)) - *(uint32_t *)(v4 + 12);
  switch ( *(uint32_t *)(v4 + 4) )
  {
    case 3:
      v16 = -v14;
      v17 = 0;
      break;
    case 4:
      v16 = 0;
      v17 = -v14;
      break;
    case 5:
      v16 = 640;
      v17 = 640 - v14;
      break;
    case 6:
      v16 = 640 - v14;
      v17 = 640;
      break;
    default:
      break;
  }
  v11 = (float)v17;
  v10 = (float)v16;
  v15 = (uint64_t)sub_4049F0(v10, v11, v7, 300, 1);
  v8 = sub_418DD0(v6, *(uint32_t *)(v4 + 48));
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v15, v13, dword_79C0B0);
  result = a2;
  if ( *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28) == a2 && (*(uint8_t *)(v4 + 52) == 1 || v7 >= 300) )
    return sub_49AB50(this);
  return result;
}



// ------------------------------------------------------------
// 0x49ADF0 sub_49ADF0
// ------------------------------------------------------------
int /*thiscall*/ sub_49ADF0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int result; // eax
  float v12; // [esp+4h] [ebp-28h]
  float v13; // [esp+8h] [ebp-24h]
  uint32_t *v14; // [esp+20h] [ebp-Ch]
  int v15; // [esp+24h] [ebp-8h]
  int v16; // [esp+24h] [ebp-8h]
  int v17; // [esp+28h] [ebp-4h]

  v3 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * a2;
  v4 = *(uint32_t *)v3;
  if ( *(uint32_t *)(*(uint32_t *)v3 + 44) < 0x10u )
    v5 = v4 + 24;
  else
    v5 = *(uint32_t *)(v4 + 24);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
  v15 = 0;
  v17 = 0;
  v6 = sub_699000((int)(this + 15)) - *(uint32_t *)(v4 + 12);
  if ( *(uint32_t *)(v4 + 4) == 7 )
  {
    v15 = 0;
    v17 = 255;
  }
  else if ( *(uint32_t *)(v4 + 4) == 8 )
  {
    v15 = 255;
    v17 = 0;
  }
  v13 = (float)v17;
  v12 = (float)v15;
  v16 = (uint64_t)sub_4049C0(v12, v13, v6, 300);
  v7 = sub_418DD0(v14, *(uint32_t *)(v4 + 48));
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
      v7,
      0,
      397,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)v16 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v8 = *(this + 10);
  v9 = *(this + 12);
  v10 = *(uint32_t *)(v9 + 4 * v8);
  result = v9 + 4 * v8;
  if ( *(uint32_t *)(v10 + 28) == a2 && (*(uint8_t *)(v4 + 52) == 1 || v6 >= 300) )
    return sub_49AB50(this);
  return result;
}



// ------------------------------------------------------------
// 0x49AF20 sub_49AF20
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AF20(uint32_t *this)
{
  uint32_t *v1; // ebx
  unsigned int v2; // esi
  int v3; // ecx
  int v4; // edx
  unsigned int result; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  unsigned int v14; // [esp+10h] [ebp-4h]

  v1 = this;
  v2 = 0;
  v14 = 0;
  do
  {
    v3 = v1[12] + 4 * v1[10];
    v4 = *(uint32_t *)(*(uint32_t *)v3 + 36);
    result = *(uint32_t *)v3 + 32;
    if ( v4 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)v3 + 40) - v4) >> 2;
    if ( v2 >= result )
      break;
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)v3 + 36)) + 16) != 0
      && *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)v3 + 36)) + 4) == 9 )
    {
      v6 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)v3 + 36) + 4 * v2);
      if ( *(uint16_t *)(v6 + 22) == 0 && (int)v1[22] > -1 )
      {
        if ( *(uint32_t *)(v6 + 52) < 0x10u )
          v7 = v6 + 32;
        else
          v7 = *(uint32_t *)(v6 + 32);
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);
        v9 = v1[22];
        if ( v9 >= 10 )
        {
          v11 = sub_418DD0(v8, v9 % 10 + 2);
          if ( v11 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(
              v11,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
            v1 = this;
          }
          v12 = sub_418DD0(v8, v1[22] / 10 + 2);
          if ( v12 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(
              v12,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 31,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
        }
        else
        {
          v10 = sub_418DD0(v8, v9 + 2);
          if ( v10 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(
              v10,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
        }
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(v1[12] + 4 * v1[10]) + 28);
    v2 = ++v14;
  }
  while ( v14 <= result );
  return result;
}



// ------------------------------------------------------------
// 0x49B0C0 sub_49B0C0
// ------------------------------------------------------------
void /*thiscall*/ sub_49B0C0(int this)
{
  unsigned int i; // ebx
  int v3; // ecx
  int v4; // edi
  void *v5; // ecx

  for ( i = 0; ; ++i )
  {
    v3 = *(uint32_t *)(this + 36);
    if ( v3 == 0 || i >= (*(uint32_t *)(this + 40) - v3) >> 2 )
      break;
    v4 = 4 * i;
    v5 = *(void **)(v3 + 4 * i);
    if ( v5 != nullptr )
      j__free(v5);
    *(uint32_t *)(v4 + *(uint32_t *)(this + 36)) = 0;
  }
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x49B150 sub_49B150
// ------------------------------------------------------------
int /*thiscall*/ sub_49B150(uint32_t *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  int result; // eax

  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(this + 1) = v3;
  *((uint32_t *)v3 + 7) = 0;
  *((uint32_t *)v3 + 8) = 0;
  sub_69A5F0((uint32_t *)*(this + 1), 0, 0);
  result = *(this + 1);
  *(uint32_t *)(result + 68) = this;
  return result;
}



// ------------------------------------------------------------
// 0x49B1D0 sub_49B1D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B1D0(uint32_t *this)
{
  unsigned int v2; // edi
  int v3; // ecx
  int v4; // edx
  unsigned int result; // eax

  v2 = 0;
  do
  {
    v3 = *(this + 12) + 4 * *(this + 10);
    v4 = *(uint32_t *)(*(uint32_t *)v3 + 36);
    result = *(uint32_t *)v3 + 32;
    if ( v4 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)v3 + 40) - v4) >> 2;
    if ( v2 >= result )
      break;
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)v3 + 36)) + 16) != 0 )
    {
      switch ( *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)v3 + 36)) + 4) )
      {
        case 2:
          sub_49ABA0(this, v2);
          break;
        case 3:
        case 4:
        case 5:
        case 6:
          sub_49AC70(this, v2);
          break;
        case 7:
        case 8:
          sub_49ADF0(this, v2);
          break;
        case 9:
          sub_49ABF0(this, v2);
          break;
        default:
          break;
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28);
    ++v2;
  }
  while ( v2 <= result );
  return result;
}



// ------------------------------------------------------------
// 0x49B290 sub_49B290
// ------------------------------------------------------------
char /*thiscall*/ sub_49B290(int this, int a2, int a3)
{
  int v4; // ebx
  uint32_t *v5; // edi
  int v6; // eax

  v4 = this + 60;
  v5 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 48) + 4 * *(uint32_t *)(this + 40)) + 36) + 4 * a3);
  v5[3] = sub_699000(this + 60);
  v6 = v5[1];
  switch ( v6 )
  {
    case 0:
    case 9:
      goto LABEL_5;
    case 1:
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;
      *(uint8_t *)(this + 8) = 0;
      *(uint8_t *)(v4 + 13) = 0;
      *(uint8_t *)(v4 + 14) = 0;
      LOBYTE(v6) = 0;
      return v6;
    case 10:
      sub_49AA30((uint32_t *)this, v5[2], 0);
      goto LABEL_5;
    case 11:
      sub_49AA30((uint32_t *)this, v5[2], 1);
LABEL_5:
      LOBYTE(v6) = sub_49AB50((uint32_t *)this);
      break;
    default:
      return v6;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49B330 sub_49B330
// ------------------------------------------------------------
char /*thiscall*/ sub_49B330(uint32_t *this, int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // edx

  result = sub_49B290((int)this, a2, a3);
  if ( *(this + 10) == 1 )
  {
    v5 = *(this + 12);
    v6 = *(uint32_t *)(v5 + 4);
    result = v5 + 4;
    if ( *(uint32_t *)(v6 + 28) == 9 )
      *(this + 22) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B370 sub_49B370
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B370(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  unsigned int v3; // ebx
  unsigned int result; // eax
  int v5; // ecx
  int v6; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  v3 = 0;
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 1) = 0;
  while ( 1 )
  {
    v5 = *(this + 12);
    if ( v5 == 0 )
      break;
    result = (*(this + 13) - v5) >> 2;
    if ( v3 >= result )
      break;
    v6 = *(uint32_t *)(4 * v3 + v5);
    if ( v6 != 0 )
    {
      Block = (void *)v6;
      sub_49B0C0(v6);
      j__free(Block);
    }
    result = 4 * v3 + *(this + 12);
    *(uint32_t *)result = 0;
    ++v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B3F0 sub_49B3F0
// ------------------------------------------------------------
char /*thiscall*/ sub_49B3F0(int this, int a2)
{
  char result; // al

  result = a2;
  if ( a2 == *(uint32_t *)(this + 4) )
  {
    result = *(uint8_t *)(this + 8);
    if ( result != 0 )
    {
      sub_49B1D0((uint32_t *)this);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 8))(this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B420 sub_49B420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B420(uint32_t *this, int a2, int a3)
{
  char *v4; // ecx

  *(this + 1) = a3;
  v4 = (char *)(this + 7);
  *(uint16_t *)this = -1;
  *(this + 2) = -1;
  *(this + 3) = 0;
  *((uint8_t *)this + 16) = 1;
  *((uint32_t *)v4 + 6) = 15;
  *((uint32_t *)v4 + 5) = 0;
  v4[4] = 0;
  *((uint8_t *)this + 20) = -1;
  *((uint16_t *)this + 11) = 0;
  *(this + 6) = 0;
  sub_4015C0((size_t *)v4, szPassword, 0);
  return this;
}



// ------------------------------------------------------------
// 0x49B4A0 sub_49B4A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B4A0(uint32_t *this, int a2, int a3)
{
  char *v4; // ecx

  v4 = (char *)(this + 5);
  *(uint16_t *)this = -1;
  *(this + 1) = a3;
  *(this + 2) = -1;
  *(this + 3) = 0;
  *((uint8_t *)this + 16) = 1;
  *((uint32_t *)v4 + 6) = 15;
  *((uint32_t *)v4 + 5) = 0;
  v4[4] = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 12) = 0;
  *((uint8_t *)this + 52) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x49B520 sub_49B520
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B520(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 40) = -1;
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);
}



// ------------------------------------------------------------
// 0x49B570 sub_49B570
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B570(int this)
{
  unsigned int i; // ebx
  int v3; // ecx
  int v4; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v3 = *(uint32_t *)(this + 48);
    if ( v3 == 0 || i >= (*(uint32_t *)(this + 52) - v3) >> 2 )
      break;
    v4 = *(uint32_t *)(v3 + 4 * i);
    if ( v4 != 0 )
    {
      Block = (void *)v4;
      sub_49B0C0(v4);
      j__free(Block);
    }
    *(uint32_t *)(4 * i + *(uint32_t *)(this + 48)) = 0;
  }
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);
}



// ------------------------------------------------------------
// 0x49B610 sub_49B610
// ------------------------------------------------------------
void /*noreturn*/ sub_49B610()
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
// 0x49B680 sub_49B680
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B680(int this, uint32_t *Src, unsigned int a3, int *a4)
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
      sub_49B610(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (v19 - (uint8_t *)Src) >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70(Src, v24, v29);
        return (unsigned int)sub_49A9D0(Src, &Srca[(uint32_t)Src], &a4);
      }
      else
      {
        sub_55E7F0(Src, (int)v19, &Src[v22 / 4u]);
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return (unsigned int)sub_49A9D0(Src, (uint32_t *)(v23 - Srca), &a4);
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
      Srcb = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
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



// ------------------------------------------------------------
// 0x49B860 sub_49B860
// ------------------------------------------------------------
int /*thiscall*/ sub_49B860(int this)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  sub_4015C0((size_t *)this, szPassword, 0);
  *(uint32_t *)(this + 28) = 0;
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x49B8E0 sub_49B8E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B8E0(int **this, int *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  int *v4; // eax
  unsigned int result; // eax

  v2 = (int)*(this + 1);
  if ( v2 != 0 )
    v3 = ((int)*(this + 2) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= ((int)*(this + 3) - v2) >> 2 )
    return sub_49B680((int)this, *(this + 2), 1u, a2);
  v4 = *(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = (int *)result;
  return result;
}



// ------------------------------------------------------------
// 0x49B930 sub_49B930
// ------------------------------------------------------------
char /*thiscall*/ sub_49B930(uint32_t *this, void *ArgList)
{
  void *v2; // esi
  void *v5; // eax
  void *v6; // ecx
  void *p_Src; // esi
  int v8; // eax
  int j; // edi
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *v12; // eax
  int v13; // esi
  int i; // [esp+8h] [ebp-78h]
  void *v16; // [esp+14h] [ebp-6Ch] BYREF
  void *v17; // [esp+18h] [ebp-68h] BYREF
  uint8_t v18[4]; // [esp+1Ch] [ebp-64h] BYREF
  void *v19; // [esp+20h] [ebp-60h]
  unsigned int v20; // [esp+30h] [ebp-50h]
  unsigned int v21; // [esp+34h] [ebp-4Ch]
  uint8_t v22[4]; // [esp+38h] [ebp-48h] BYREF
  void *Block; // [esp+3Ch] [ebp-44h]
  unsigned int v24; // [esp+4Ch] [ebp-34h]
  unsigned int v25; // [esp+50h] [ebp-30h]
  uint8_t v26[4]; // [esp+54h] [ebp-2Ch] BYREF
  void *Src; // [esp+58h] [ebp-28h] BYREF
  unsigned int v28; // [esp+68h] [ebp-18h]
  unsigned int v29; // [esp+6Ch] [ebp-14h]
  int v30; // [esp+70h] [ebp-10h]
  int v31; // [esp+7Ch] [ebp-4h]

  v2 = ArgList;
  v30 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)ArgList) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 4))(this);
    sub_4015C0(v2, strlen((const char *)v2));
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v31 = 2;
    v29 = 15;
    v28 = 0;
    LOBYTE(Src) = 0;
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    v16 = nullptr;
    while ( (uint8_t)sub_443430(v18) != 0 )
    {
      sub_442BC0(v18);
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[talk name]", 0xBu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[commands]", 0xAu) == 0 )
        {
          HIBYTE(ArgList) = 0;
          for ( i = sub_4423D0((uint8_t *)&ArgList + 3); HIBYTE(ArgList) != 0; i = sub_4423D0((uint8_t *)&ArgList + 3) )
          {
            sub_443370();
            for ( j = 0; j < 12; ++j )
            {
              if ( sub_40BF00((std::_String_base *)v26, 0, v28, off_790B94[j], strlen(off_790B94[j])) == 0 )
              {
                switch ( j )
                {
                  case 0:
                  case 1:
                    v10 = operator new(0x14u);
                    if ( v10 != nullptr )
                    {
                      *(uint16_t *)v10 = -1;
                      v10[1] = j;
                      v10[2] = -1;
                      v10[3] = 0;
                      *((uint8_t *)v10 + 16) = 1;
                      v17 = v10;
                    }
                    else
                    {
                      v17 = nullptr;
                    }
                    goto LABEL_33;
                  case 2:
                  case 10:
                  case 11:
                    v11 = sub_4423D0(nullptr);
                    v12 = operator new(0x14u);
                    if ( v12 != nullptr )
                    {
                      *(uint16_t *)v12 = -1;
                      v12[1] = j;
                      v12[2] = v11;
                      v12[3] = 0;
                      *((uint8_t *)v12 + 16) = 1;
                      v17 = v12;
                    }
                    else
                    {
                      v17 = nullptr;
                    }
                    goto LABEL_33;
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                  case 8:
                    v17 = operator new(0x38u);
                    LOBYTE(v31) = 4;
                    if ( v17 != nullptr )
                      v13 = sub_49B4A0(i, j);
                    else
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    *(uint32_t *)(v13 + 48) = sub_4423D0(nullptr);
                    sub_443370();
                    sub_443370();
                    *(uint8_t *)(v13 + 52) = sub_40BF00((std::_String_base *)v22, 0, v24, "[pass next command]", 0x13u) == 0;
                    goto LABEL_32;
                  case 9:
                    v17 = operator new(0x38u);
                    LOBYTE(v31) = 5;
                    if ( v17 != nullptr )
                      v13 = sub_49B420(i, 9);
                    else
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    sub_443370();
                    *(uint8_t *)(v13 + 20) = sub_40BF00((std::_String_base *)v22, 0, v24, "[img]", 5u) != 0;
                    *(uint16_t *)(v13 + 22) = sub_4423D0(nullptr);
                    *(uint32_t *)(v13 + 24) = sub_4423D0(nullptr);
                    sub_443370();
LABEL_32:
                    v17 = (void *)v13;
LABEL_33:
                    sub_49B8E0(&v17);
                    break;
                  default:
                    continue;
                }
              }
            }
          }
        }
      }
      else
      {
        sub_443370();
        v5 = operator new(0x30u);
        v16 = v5;
        LOBYTE(v31) = 3;
        if ( v5 != nullptr )
          v6 = (void *)sub_49B860(v5);
        else
          v6 = nullptr;
        p_Src = Src;
        LOBYTE(v31) = 2;
        v16 = v6;
        if ( v29 < 0x10 )
          p_Src = &Src;
        sub_4015C0(p_Src, strlen((const char *)p_Src));
        sub_5660C0(&v16);
        v8 = *(this + 12);
        if ( v8 != 0 )
          v16 = (void *)(((*(this + 13) - v8) >> 2) - 1);
        else
          v16 = (void *)-1;
      }
    }
    if ( v25 >= 0x10 )
      j__free(Block);
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    if ( v29 >= 0x10 )
      j__free(Src);
    v28 = 0;
    LOBYTE(Src) = 0;
    v29 = 15;
    if ( v21 >= 0x10 )
      j__free(v19);
    return 1;
  }
  else
  {
    off_77F3FC(aErrorS_0, v2);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x49BD60 sub_49BD60
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD60(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 25) = 0;
  *(this + 26) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x49BD80 sub_49BD80
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD80(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49BDB0 sub_49BDB0
// ------------------------------------------------------------
char /*thiscall*/ sub_49BDB0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax

  v3 = (int)(this + 18);
  *(this + 25) = a2;
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  LOBYTE(v4) = sub_698F90(v3, 0, 0);
  if ( a2 != 0 )
  {
    *(uint8_t *)(*(this + 2) + 16) = 1;
  }
  else
  {
    v4 = *(this + 2);
    *(uint8_t *)(v4 + 16) = 0;
  }
  *(this + 26) = -1;
  return v4;
}



// ------------------------------------------------------------
// 0x49BE00 sub_49BE00
// ------------------------------------------------------------
int sub_49BE00()
{
  int result; // eax
  int v1; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  if ( result != 0 )
  {
    v1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    return sub_41A5E0(v1 + 134);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49BE30 sub_49BE30
// ------------------------------------------------------------
int sub_49BE30()
{
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )
  {
    return *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108)
                     + 108);
  }
  else
  {
    return -1;
  }
}



// ------------------------------------------------------------
// 0x49BE70 sub_49BE70
// ------------------------------------------------------------
bool sub_49BE70()
{
  int v0; // esi
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )
    return false;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) == 0 )
    return false;
  v0 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) + 108);
  if ( v0 == -1 )
    return false;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )
    return v0 <= 0;
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  return sub_41A5E0(v2 + 134) >= v0;
}



// ------------------------------------------------------------
// 0x49BEF0 sub_49BEF0
// ------------------------------------------------------------
char /*thiscall*/ sub_49BEF0(int this, int a2)
{
  int v2; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // eax
  uint32_t *v26; // ecx
  unsigned int v28; // [esp-8h] [ebp-Ch]

  LOBYTE(v2) = a2;
  if ( a2 != *(uint32_t *)(this + 8) )
    return v2;
  v2 = *(uint32_t *)(this + 100);
  if ( v2 == 1 || v2 == 2 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
    if ( v2 != 0 )
    {
      v4 = sub_49BE30();
      if ( v4 == -1 )
      {
        v5 = sub_418DD0(*(uint32_t **)(this + 12), 0);
        if ( v5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, 213, 236, dword_79C0B0);
        if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )
        {
          v6 = sub_418DD0(*(uint32_t **)(this + 12), 1u);
          sub_40FC80((void *)dword_79C0B0, 215, 238, v6);
        }
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
        LOBYTE(v2) = sub_69A110(338, 276, v7, -1);
        goto LABEL_24;
      }
      LOBYTE(v2) = sub_49BE70();
      if ( (uint8_t)v2 == 0 )
      {
        LOBYTE(v2) = *(uint8_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520)
                                          + 108)
                              + 464);
        if ( (uint8_t)v2 != 0 )
        {
          v8 = sub_418DD0(*(uint32_t **)(this + 12), 0x26u);
          sub_40FC80((void *)dword_79C0B0, 209, 206, v8);
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )
          {
            v9 = sub_418DD0(*(uint32_t **)(this + 12), 0x27u);
            sub_40FC80((void *)dword_79C0B0, 213, 248, v9);
          }
          v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
          sub_69A110(338, 267, v10, -1);
          v11 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);
          sub_40FC80((void *)dword_79C0B0, 365 - (*(uint32_t *)(v11 + 20) >> 1), 310 - (*(uint32_t *)(v11 + 24) >> 1), v11);
          v12 = sub_49BE00();
          v13 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v12 + 25);
          sub_40FC80((void *)dword_79C0B0, 352 - (*(uint32_t *)(v13 + 20) >> 1), 310 - (*(uint32_t *)(v13 + 24) >> 1), v13);
          v14 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);
          v15 = 310;
        }
        else
        {
          if ( *(uint32_t *)(dword_8F7A24 + 12) != 6 )
            goto LABEL_24;
          v16 = sub_418DD0(*(uint32_t **)(this + 12), 0x28u);
          sub_40FC80((void *)dword_79C0B0, 211, 237, v16);
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )
          {
            v17 = sub_418DD0(*(uint32_t **)(this + 12), 0x29u);
            sub_40FC80((void *)dword_79C0B0, 213, 239, v17);
          }
          v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
          sub_69A110(338, 267, v18, -1);
          v19 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);
          sub_40FC80((void *)dword_79C0B0, 363 - (*(uint32_t *)(v19 + 20) >> 1), 311 - (*(uint32_t *)(v19 + 24) >> 1), v19);
          v20 = sub_49BE00();
          v21 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v20 + 25);
          sub_40FC80((void *)dword_79C0B0, 347 - (*(uint32_t *)(v21 + 20) >> 1), 311 - (*(uint32_t *)(v21 + 24) >> 1), v21);
          v14 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);
          v15 = 311;
        }
        LOBYTE(v2) = sub_40FC80(
                       (void *)dword_79C0B0,
                       378 - (*(uint32_t *)(v14 + 20) >> 1),
                       v15 - (*(uint32_t *)(v14 + 24) >> 1),
                       v14);
      }
    }
  }
LABEL_24:
  if ( *(uint32_t *)(this + 100) == 2 )
  {
    if ( (9999 - sub_699000(this + 72)) / 1000 <= 0 )
      v22 = 0;
    else
      v22 = (9999 - sub_699000(this + 72)) / 1000;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 && dword_99FF08 != 0 && sub_48FD80((uint8_t *)dword_99FF08) == 0 )
    {
      v23 = sub_418DD0(*(uint32_t **)(this + 12), v22 + 2);
      sub_40FC80((void *)dword_79C0B0, 271, 105, v23);
      v24 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208), 0x4Cu);
      LOBYTE(v2) = sub_40FC80((void *)dword_79C0B0, 115, 194, v24);
    }
    else
    {
      v25 = sub_49BE30();
      v26 = *(uint32_t **)(this + 12);
      v28 = v22 + 2;
      if ( v25 == -1 )
      {
        v2 = sub_418DD0(v26, v28);
        if ( v2 != 0 )
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v2 + 152))(v2, 282, 121, dword_79C0B0);
      }
      else
      {
        v2 = sub_418DD0(v26, v28);
        if ( v2 != 0 )
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v2 + 152))(v2, 282, 116, dword_79C0B0);
      }
    }
    if ( *(uint32_t *)(this + 104) != v22 )
    {
      LOBYTE(v2) = (uint8_t)sub_432EA0("COUNT_DOWN", -1, 0, 0);
      *(uint32_t *)(this + 104) = v22;
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x49C380 sub_49C380
// ------------------------------------------------------------
int /*thiscall*/ sub_49C380(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  int v5; // eax
  int result; // eax

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 68);
  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 8) = v4;
  *((uint32_t *)v4 + 17) = this;
  if ( operator new(0x2Cu) != nullptr )
    v5 = sub_423B30(dword_79C0B0, *(uint32_t *)(this + 12), 13, 4);
  else
    v5 = 0;
  *(uint32_t *)(this + 16) = v5;
  *(uint8_t *)(this + 20) = 0;
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  *(uint8_t *)(this + 23) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 6;
  *(uint32_t *)(this + 40) = 12;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 1600;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 68) = dword_99FCCC;
  *(uint32_t *)(this + 24) = -16777216;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 85) = 0;
  *(uint8_t *)(this + 86) = 0;
  sub_698F90(this + 72, 0, 0);
  result = *(uint32_t *)(this + 8);
  *(uint8_t *)(result + 16) = 0;
  *(uint32_t *)(this + 104) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x49C4A0 sub_49C4A0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C4A0(void *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v8; // eax

  sub_58B2A0(a2);
  v8 = sub_699000((int)this + 20);
  sub_58B2A0(v8);
  sub_58B2A0(a3);
  sub_58B2A0(4);
  sub_58B2A0(a4);
  sub_58B2A0(a5);
  sub_58B2A0(a6);
  return sub_58B2A0(a7);
}



// ------------------------------------------------------------
// 0x49C510 sub_49C510
// ------------------------------------------------------------
int /*cdecl*/ sub_49C510(int a1, int a2, int a3, int a4, int a5)
{
  if ( (dword_9A0264 & 1) == 0 )
  {
    dword_9A0264 |= 1u;
    dword_9A0250 = 0;
    dword_9A0254 = 0;
    dword_9A0258 = 0;
    dword_9A025C = 0;
    dword_9A0260 = 0;
    atexit(nullsub_4);
  }
  dword_9A0254 = a2;
  dword_9A0250 = a1;
  dword_9A0260 = a5;
  dword_9A0258 = a3;
  dword_9A025C = a4;
  return sub_4AEA30(&dword_9A0250);
}



// ------------------------------------------------------------
// 0x49C5A0 sub_49C5A0
// ------------------------------------------------------------
int sub_49C5A0()
{
  int v0; // edx
  int v1; // esi
  int v2; // edi
  int v4; // [esp-4h] [ebp-Ch]

  v0 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v1 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v2 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v4 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  return sub_49C510(v1, 0, v0, v2, v4);
}



// ------------------------------------------------------------
// 0x49C5F0 sub_49C5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C5F0(int *this, int a2, int a3, int a4, int a5)
{
  return sub_49C4A0(&dword_9A02C0, (int)sub_49C5A0, a5, *(this + 1), a2, a3, a4);
}



// ------------------------------------------------------------
// 0x49C620 sub_49C620
// ------------------------------------------------------------
int /*thiscall*/ sub_49C620(int *this, int a2, int a3, int a4)
{
  return sub_49C510(a2, *(this + 1), *(this + 1), a3, a4);
}



// ------------------------------------------------------------
// 0x49C640 sub_49C640
// ------------------------------------------------------------
void /*noreturn*/ sub_49C640()
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
  sub_4015C0(&v1, "deque<T> too long", 0x11u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x49C6B0 sub_49C6B0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49C6B0(int this, unsigned int a2)
{
  unsigned int v2; // edx
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // edi
  int v7; // esi
  char *v8; // eax
  const void *v9; // ecx
  char *v10; // eax
  char *v11; // edx
  unsigned int v12; // ecx
  char *v13; // edi
  size_t v14; // esi
  char *v15; // eax
  unsigned int result; // eax
  size_t v17; // [esp+8h] [ebp-Ch]
  char *v18; // [esp+10h] [ebp-4h]

  v2 = a2;
  v4 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - v4 < a2 )
    sub_49C640(this);
  v5 = v4 >> 1;
  if ( v4 >> 1 < 8 )
    v5 = 8;
  if ( a2 < v5 && v4 <= 0xFFFFFFF - v5 )
  {
    a2 = v5;
    v2 = v5;
  }
  v6 = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * v6;
  v18 = (char *)operator new(4 * (v2 + v4));
  v17 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * v6) >> 2);
  v8 = (char *)memcpy_0(&v18[4 * v6], (const void *)(4 * v6 + *(uint32_t *)(this + 4)), v17);
  v9 = *(const void **)(this + 4);
  v10 = &v8[v17];
  if ( v6 > a2 )
  {
    memcpy_0(v10, v9, 4 * ((int)(4 * a2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * a2) >> 2);
    v15 = (char *)memcpy_0(v18, (const void *)(4 * a2 + *(uint32_t *)(this + 4)), v14);
    v12 = a2;
    v13 = &v15[v14];
    if ( a2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  v11 = (char *)memcpy_0(v10, v9, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( a2 != v6 )
    memset(v11, 0, 4 * (a2 - v6));
  if ( v6 != 0 )
  {
    v12 = v6;
    v13 = v18;
LABEL_14:
    memset(v13, 0, 4 * v12);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = a2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = v18;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x49C800 sub_49C800
// ------------------------------------------------------------
int /*thiscall*/ sub_49C800(int this, uint32_t *a2)
{
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // ebx
  uint32_t *v7; // edi
  int result; // eax

  v3 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)v3 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(v3 + 4) >> 2 )
    sub_49C6B0(this, 1u);
  v4 = *(uint32_t *)(this + 8);
  v5 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = v5 >> 2;
  if ( v4 <= v5 >> 2 )
    v6 -= v4;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  v7 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (v5 & 3));
  if ( v7 != nullptr )
    *v7 = *a2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x49C880 sub_49C880
// ------------------------------------------------------------
void */*thiscall*/ sub_49C880(size_t *this, size_t Size)
{
  void *result; // eax
  int i; // edi
  size_t *v5; // ecx
  unsigned int v6; // edx
  unsigned int v7; // eax
  size_t *v8; // esi
  unsigned int v9; // edx
  unsigned int v10; // edi
  size_t v11; // edx
  size_t v12; // edx

  if ( Size != *this )
    return operator new(Size);
  if ( *(this + 5) == 0 )
  {
    for ( i = 512; i != 0; --i )
    {
      Size = (size_t)operator new(*this);
      sub_49C800((int)(this + 1), &Size);
    }
  }
  v5 = this + 1;
  v6 = *(this + 4) + *(this + 5) - 1;
  v7 = v6 >> 2;
  v8 = this + 1;
  v9 = v6 - 4 * (v6 >> 2);
  v10 = v8[2];
  if ( v10 <= v7 )
    v7 -= v10;
  result = *(void **)(*(uint32_t *)(v8[1] + 4 * v7) + 4 * v9);
  v11 = v5[4];
  if ( v11 != 0 )
  {
    v12 = v11 - 1;
    v5[4] = v12;
    if ( v12 == 0 )
      v5[3] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49C920 sub_49C920
// ------------------------------------------------------------
int /*cdecl*/ sub_49C920(int a1, int a2, int a3, int a4, int a5)
{
  uint32_t *v5; // ecx
  uint32_t *v6; // eax
  uint32_t *v8; // [esp+0h] [ebp-4h] BYREF

  v8 = v5;
  v6 = sub_49C880(&dword_9B930C, 0x14u);
  if ( v6 != nullptr )
  {
    *v6 = a1;
    v6[1] = a2;
    v6[2] = a3;
    v6[3] = a4;
    v6[4] = a5;
  }
  else
  {
    v6 = nullptr;
  }
  v8 = v6;
  return sub_49C800((int)&unk_9A02F0, &v8);
}



// ------------------------------------------------------------
// 0x49C970 sub_49C970
// ------------------------------------------------------------
int /*thiscall*/ sub_49C970(int *this, int a2, int a3, int a4)
{
  return sub_49C920(a2, *(this + 1), *(this + 1), a3, a4);
}



// ------------------------------------------------------------
// 0x49C990 sub_49C990
// ------------------------------------------------------------
int /*thiscall*/ sub_49C990(uint32_t *this)
{
  uint32_t *v2; // ecx

  *(this + 1) = 0;
  *(this + 6) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  v2 = this + 58;
  *v2 = -1;
  v2[1] = -1;
  v2[2] = -1;
  v2[3] = -1;
  v2[4] = -1;
  v2[5] = -1;
  v2[6] = -1;
  v2[7] = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x49C9E0 sub_49C9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C9E0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  uint32_t *v9; // edi
  int i; // ebx
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  *(this + 6) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 11) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  *(this + 14) = 0;
  v9 = this + 15;
  for ( i = 3; i != 0; --i )
  {
    if ( *v9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v9)(*v9, 1);
    *v9++ = 0;
  }
  v11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  if ( v11 != nullptr )
    result = (**v11)(v11, 1);
  *(this + 18) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49CA80 sub_49CA80
// ------------------------------------------------------------
int /*thiscall*/ sub_49CA80(int *this)
{
  int v2; // ecx
  int v3; // esi
  int v4; // ebx
  uint32_t *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  bool v9; // zf
  int result; // eax
  uint32_t *v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  int *v13; // [esp+18h] [ebp-4h]

  v2 = dword_99FF08;
  *(this + 58) = -1;
  *(this + 59) = -1;
  *(this + 60) = -1;
  *(this + 61) = -1;
  *(this + 62) = -1;
  *(this + 63) = -1;
  *(this + 64) = -1;
  *(this + 65) = -1;
  v3 = 0;
  v4 = 1;
  v5 = (uint32_t *)(v2 + 8);
  v12 = 1;
  v13 = this + 58;
  v11 = v5;
  do
  {
    if ( *v5 != 255 )
    {
      if ( v3 == sub_48FCA0() )
      {
        *v13 = 0;
      }
      else
      {
        v6 = sub_578E80(v3);
        if ( v6 != 0 )
        {
          v7 = *(uint32_t *)(v6 + 196);
          if ( v7 != 0 )
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 376))(v7);
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == v8;
            v4 = v12;
            if ( v9 )
            {
              *v13 = v12;
              v4 = ++v12;
            }
          }
        }
      }
    }
    ++v3;
    v5 = ++v11;
    ++v13;
  }
  while ( v3 < 8 );
  result = -1;
  if ( *(this + 58) == -1 )
    *(this + 58) = v4++;
  if ( *(this + 59) == -1 )
    *(this + 59) = v4++;
  if ( *(this + 60) == -1 )
    *(this + 60) = v4++;
  if ( *(this + 61) == -1 )
    *(this + 61) = v4++;
  if ( *(this + 62) == -1 )
    *(this + 62) = v4++;
  if ( *(this + 63) == -1 )
    *(this + 63) = v4++;
  if ( *(this + 64) == -1 )
    *(this + 64) = v4++;
  if ( *(this + 65) == -1 )
    *(this + 65) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x49CBD0 sub_49CBD0
// ------------------------------------------------------------
int /*thiscall*/ sub_49CBD0(int *this)
{
  int result; // eax
  uint32_t *v3; // edi
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  uint32_t v14[3]; // [esp+4h] [ebp-Ch]

  result = *(this + 6);
  if ( *(uint8_t *)(result + 16) != 0 )
  {
    result = dword_99FF08;
    if ( dword_99FF08 != 0 )
    {
      v3 = (uint32_t *)*(this + 1);
      v4 = v3[202];
      if ( v4 == 0 || (result = (v3[203] - v4) >> 2) == 0 )
      {
        v5 = *(this + 11);
        if ( *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
        {
          v6 = *(this + 3);
          if ( v6 != 0 && (*(this + 4) - v6) >> 2 != 0 )
          {
            sub_44E8D0((char *)dword_8F8528, (void *)0x2A, (int)(this + 2), 0);
          }
          else
          {
            v7 = (uint32_t *)v3[7];
            v8 = sub_422E70(448);
            sub_43BEE0(v7, v8, -6567706, 0, -1);
          }
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        v9 = *(this + 10);
        if ( *(uint8_t *)(v9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) )
        {
          v10 = sub_48FCA0();
          if ( v10 != -1 )
            sub_48FC30(v10, 255);
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        v11 = *(this + 14);
        if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
        {
          *(uint8_t *)(*(this + 13) + 16) = *(uint8_t *)(*(this + 13) + 16) == 0;
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        v12 = 0;
        v14[0] = 1;
        v14[1] = 2;
        v14[2] = 0;
        while ( 1 )
        {
          result = *(this + v14[v12] + 15);
          if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
            break;
          if ( ++v12 >= 3 )
            return result;
        }
        *(uint8_t *)(*(this + 13) + 16) = 0;
        v13 = sub_48FCA0();
        if ( v13 != -1 )
          sub_48FC30(v13, v14[v12]);
        return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49CD70 sub_49CD70
// ------------------------------------------------------------
int /*thiscall*/ sub_49CD70(uint32_t *this, char a2)
{
  int result; // eax
  int v4; // edi

  result = *(this + 6);
  if ( *(uint8_t *)(result + 16) != a2 )
  {
    *(uint8_t *)(result + 16) = a2;
    if ( a2 != 0 )
    {
      if ( sub_48FCA0() != -1 )
      {
        *(uint8_t *)(*(this + 14) + 16) = 1;
        *(uint8_t *)(*(this + 13) + 16) = 0;
      }
      v4 = 22 * sub_48FCA0();
      sub_69A5F0((uint32_t *)*(this + 14), 603, v4 + 150);
      sub_69A5F0((uint32_t *)*(this + 13), 577, v4 + 164);
      *(uint8_t *)(*(this + 13) + 16) = 0;
      *(uint8_t *)(*(this + 14) + 16) = 0;
      *(uint8_t *)(*(this + 9) + 16) = 1;
      result = *(this + 11);
      *(uint8_t *)(result + 16) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49CE00 sub_49CE00
// ------------------------------------------------------------
int /*thiscall*/ sub_49CE00(uint32_t **this)
{
  int v2; // esi
  int v3; // eax
  uint32_t *v4; // edi
  int v5; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int result; // eax
  int v13; // [esp+Ch] [ebp-4h]

  v2 = 30000 - sub_699000(*(uint32_t *)(dword_8F7A24 + 40) + 36);
  v3 = sub_418DD0(*(this + 8), 0x35u);
  if ( v3 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v3 + 152))(v3, 424, 111, dword_79C0B0);
  v4 = *(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208);
  v13 = v2 % 1000;
  v5 = v2 / 1000 % 60;
  v6 = v2 / 60000;
  if ( v6 > 0 )
  {
    if ( v6 > 10 )
    {
      v7 = sub_418DD0(v4, v6 / 10 + 43);
      if ( v7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, 456, 118, dword_79C0B0);
    }
    v8 = sub_418DD0(v4, v6 % 10 + 43);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, 470, 118, dword_79C0B0);
LABEL_11:
    v9 = sub_418DD0(v4, v5 / 10 + 43);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, 504, 118, dword_79C0B0);
    goto LABEL_13;
  }
  if ( v5 > 0 )
  {
    if ( v5 >= 10 )
      goto LABEL_11;
LABEL_13:
    v10 = sub_418DD0(v4, v5 % 10 + 43);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, 518, 118, dword_79C0B0);
  }
  v11 = sub_418DD0(v4, v13 / 100 + 43);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, 544, 118, dword_79C0B0);
  result = sub_418DD0(v4, v13 / 10 % 10 + 43);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, 558, 118, dword_79C0B0);
  return result;
}



// ------------------------------------------------------------
// 0x49CFF0 sub_49CFF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49CFF0(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // edi
  uint32_t *v10; // ecx
  bool v11; // cc
  uint8_t *v12; // eax
  uint32_t *v13; // edi
  uint8_t *v14; // eax
  uint32_t *v15; // edi
  uint8_t *v16; // eax
  uint32_t *v17; // edi
  uint32_t *v18; // ecx
  uint8_t *v19; // eax
  uint8_t *v20; // eax
  uint32_t *v21; // ecx
  uint32_t *result; // eax
  int v23; // esi
  int v24; // [esp+Ch] [ebp-24h]
  int v25; // [esp+10h] [ebp-20h]
  int v26; // [esp+14h] [ebp-1Ch]
  int v27; // [esp+18h] [ebp-18h]
  uint32_t *v28; // [esp+1Ch] [ebp-14h]
  int v29; // [esp+20h] [ebp-10h]
  int *Blocka; // [esp+38h] [ebp+8h]
  void *Blockb; // [esp+38h] [ebp+8h]
  void *Blockc; // [esp+38h] [ebp+8h]
  void *Blockd; // [esp+38h] [ebp+8h]

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);
  *(uint32_t *)(this + 32) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);
  v3 = operator new(0x6Cu);
  if ( v3 != nullptr )
    v4 = sub_43C250(v3, *(uint32_t *)(this + 32), 45);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 24) = v4;
  *((uint32_t *)v4 + 17) = this;
  v5 = operator new(0x68u);
  if ( v5 != nullptr )
    v6 = sub_426BD0(v5);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 36) = v6;
  sub_69A840(v6);
  v7 = operator new(0x6Cu);
  if ( v7 != nullptr )
    v8 = sub_43C250(v7, *(uint32_t *)(this + 28), 75);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 52) = v8;
  sub_69A840(v8);
  v29 = 2;
  Blocka = (int *)&unk_6CBA30;
  v28 = (uint32_t *)(this + 60);
  do
  {
    v9 = operator new(0x84u);
    if ( v9 != nullptr )
    {
      v27 = *Blocka;
      v24 = *(uint32_t *)(this + 28);
      v26 = Blocka[2];
      v25 = Blocka[1];
      sub_426BD0(v9);
      *(uint32_t *)v9 = &nengine::CNButton::`vftable';
      sub_69C780(v9);
      sub_69C7B0(v24, v27, v25, v26, v27, 0, 0);
      v10 = v9;
    }
    else
    {
      v10 = nullptr;
    }
    *v28 = v10;
    sub_69A5F0(v10, 2, v29);
    sub_69A840(*v28);
    v11 = (int)(Blocka + 3) < (int)&unk_6CBA54;
    ++v28;
    Blocka += 3;
    v29 += 13;
  }
  while ( v11 );
  v12 = operator new(0x84u);
  v13 = v12;
  if ( v12 != nullptr )
  {
    Blockb = *(void **)(this + 28);
    sub_426BD0(v12);
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780(v13);
    sub_69C7B0(Blockb, 4, 5, 6, 4, 0, 0);
  }
  else
  {
    v13 = nullptr;
  }
  *(uint32_t *)(this + 56) = v13;
  sub_69A840(v13);
  v14 = operator new(0x84u);
  v15 = v14;
  if ( v14 != nullptr )
  {
    Blockc = *(void **)(this + 32);
    sub_426BD0(v14);
    *v15 = &nengine::CNButton::`vftable';
    sub_69C780(v15);
    sub_69C7B0(Blockc, 46, 47, 48, 46, 0, 0);
  }
  else
  {
    v15 = nullptr;
  }
  *(uint32_t *)(this + 40) = v15;
  v15[17] = this;
  sub_69A5F0(*(uint32_t **)(this + 40), 86, 388);
  sub_69A840(*(uint32_t *)(this + 40));
  v16 = operator new(0x84u);
  v17 = v16;
  if ( v16 != nullptr )
  {
    Blockd = *(void **)(this + 28);
    sub_426BD0(v16);
    *v17 = &nengine::CNButton::`vftable';
    sub_69C780(v17);
    sub_69C7B0(Blockd, 46, 47, 48, 46, 0, 0);
    v18 = v17;
  }
  else
  {
    v18 = nullptr;
  }
  *(uint32_t *)(this + 44) = v18;
  sub_69A5F0(v18, 110, 332);
  sub_69A840(*(uint32_t *)(this + 44));
  v19 = operator new(0x68u);
  if ( v19 != nullptr )
    v20 = sub_426BD0(v19);
  else
    v20 = nullptr;
  *(uint32_t *)(this + 72) = v20;
  *((uint32_t *)v20 + 17) = this;
  sub_69A840(*(uint32_t *)(this + 72));
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  *(uint8_t *)(this + 79) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 92) = 6;
  *(uint32_t *)(this + 96) = 12;
  *(uint32_t *)(this + 104) = 1600;
  *(uint32_t *)(this + 124) = dword_99FCCC;
  *(uint32_t *)(this + 80) = -16777216;
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 130) = 0;
  *(uint8_t *)(this + 131) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 6;
  *(uint32_t *)(this + 148) = 12;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 1600;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 176) = dword_99FCCC;
  *(uint32_t *)(this + 156) = 72;
  *(uint32_t *)(this + 140) = 1;
  *(uint8_t *)(this + 180) = 0;
  *(uint8_t *)(this + 181) = 0;
  *(uint8_t *)(this + 182) = 0;
  *(uint8_t *)(this + 183) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 6;
  *(uint32_t *)(this + 200) = 12;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 1600;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  v21 = *(uint32_t **)(this + 24);
  *(uint32_t *)(this + 228) = dword_99FCCC;
  *(uint32_t *)(this + 208) = 156;
  *(uint32_t *)(this + 192) = 1;
  *(uint8_t *)(this + 182) = 1;
  *(uint32_t *)(this + 184) = -16777216;
  result = sub_69A5F0(v21, 365, 0);
  v23 = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(v23 + 16) != 0 )
    *(uint8_t *)(v23 + 16) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x49D4B0 sub_49D4B0
// ------------------------------------------------------------
void /*userpurge*/ sub_49D4B0(uint32_t *a1@<ecx>, uint32_t *a2@<esi>, int a3)
{
  int v3; // edi
  uint32_t *v4; // ebx
  int v5; // edx
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // edx
  uint32_t *v13; // ecx
  int v14; // esi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // esi
  int v26; // eax
  bool v27; // cc
  int v28; // eax
  int v29; // esi
  int v30; // edi
  int v31; // eax
  int v32; // eax
  char v33; // al
  int v34; // ebx
  int v35; // esi
  int v36; // ebx
  int v37; // eax
  int v38; // eax
  char *v40; // [esp+8h] [ebp-1Ch]
  int v41; // [esp+Ch] [ebp-18h]
  int v42; // [esp+14h] [ebp-10h]
  int v43; // [esp+18h] [ebp-Ch]
  int *v44; // [esp+1Ch] [ebp-8h]
  int v46; // [esp+2Ch] [ebp+8h]
  int v47; // [esp+2Ch] [ebp+8h]

  v3 = dword_99FF08;
  v4 = a1;
  if ( dword_99FF08 != 0 )
  {
    v5 = *(uint32_t *)(a1[1] + 4);
    if ( a3 == a1[6] )
    {
      if ( v5 == 0 )
      {
        v6 = dword_99FF08 + 4;
        v7 = sub_418DD0(41);
        if ( v7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, 383, 57, dword_79C0B0);
        v8 = sub_418DD0(54);
        if ( v8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, 387, 83, dword_79C0B0);
        v9 = sub_418DD0(35);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, 394, 84, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v4 + 45);
        v46 = *(uint32_t *)dword_79C0B0;
        v10 = sub_48FE30(v3);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v46 + 80))(dword_79C0B0, 424, 27, -1, v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) == 1 )
          sub_49CE00(v4);
        v47 = *(uint32_t *)(v4[6] + 20) + 30;
        v11 = 0;
        v12 = 1048644 - v6;
        v13 = (uint32_t *)(v6 + 4);
        v43 = 0;
        v44 = (int *)(v6 + 4);
        v42 = 1048644 - v6;
        v41 = -4 - v6;
        while ( 1 )
        {
          v40 = (char *)v13 + v12;
          v14 = dword_790BC8 + dword_790BCC * *(uint32_t *)((char *)v4 + (uint32_t)v13 + v12 - 1048416);
          if ( *v13 != 255 )
          {
            v15 = sub_578E80(v11);
            v16 = v15;
            if ( v15 != 0 )
            {
              v17 = sub_42B340(v15);
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)v17 + 384))(
                v17,
                v47,
                v14,
                16,
                16,
                1065353216,
                a2);
              v18 = *v44;
              if ( *v44 == 1 || v18 == 2 )
              {
                v19 = sub_418DD0(v18 + 73);
                if ( v19 != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 152))(v19, v47, v14, dword_79C0B0);
              }
              a2 = v4 + 32;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v20 = v16 + 20;
              else
                v20 = *(uint32_t *)(v16 + 20);
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v47 + 55,
                v14 + 4,
                -9795152,
                v20);
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v21 = v16 + 20;
              else
                v21 = *(uint32_t *)(v16 + 20);
              v22 = v14 + 3;
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v47 + 55,
                v14 + 3,
                -16179413,
                v21);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
              v23 = *v44;
              if ( *v44 == 1 || v23 == 2 )
                v24 = sub_418DD0(v23 + 99);
              else
                v24 = sub_418DD0(112);
              if ( v24 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(
                  v24,
                  v47 + 180,
                  v14 + 2,
                  dword_79C0B0);
              v25 = dword_8F8520;
              if ( *(uint32_t *)((char *)sub_656710() + (uint32_t)v44 + v41) != -1 && *(uint32_t *)&v40[v25] != 0 )
              {
                v26 = sub_418DD0(44);
                if ( v26 != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, v47 + 130, v22, dword_79C0B0);
              }
              v4 = a1;
            }
          }
          v11 = v43 + 1;
          v13 = v44 + 1;
          v27 = ++v43 < 8;
          ++v44;
          if ( !v27 )
            break;
          v12 = v42;
        }
      }
    }
    else
    {
      v28 = a1[10];
      if ( a3 != v28 || v5 != 0 )
      {
        if ( a3 == a1[18] && v5 == 0 )
        {
          if ( (uint8_t)sub_43BCB0(a1[11]) != 0 )
          {
            v32 = sub_422E70(449);
            sub_4649B0(510, 321, -1, -16777216, 2, v32, 0, 0, 1600, 0);
          }
          else if ( (uint8_t)sub_43BCB0(v4[14]) != 0 )
          {
            v33 = sub_48FD20(v3);
            v34 = v4[14];
            v35 = *(uint32_t *)(v34 + 24);
            v36 = *(uint32_t *)(v34 + 20);
            if ( v33 != 0 )
              v37 = sub_422E70(452);
            else
              v37 = sub_422E70(453);
            sub_4649B0(v36 - 10, v35, -1, -16777216, 2, v37, 0, 0, 1600, 0);
          }
          else if ( (uint8_t)sub_43BCB0(v4[17]) != 0 )
          {
            v38 = sub_422E70(455);
            sub_4649B0(505, 202, -1, -16777216, 2, v38, 0, 0, 1600, 0);
          }
        }
      }
      else if ( *(uint8_t *)(v28 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v28 + 12) )
      {
        v29 = *(uint32_t *)(v28 + 24);
        v30 = *(uint32_t *)(v28 + 20);
        v31 = sub_418DD0(87);
        sub_40FC80(v30 + 24, v29 - 33, v31);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x49D920 sub_49D920
// ------------------------------------------------------------
void /*thiscall*/ sub_49D920(uint32_t *this)
{
  void *v1; // eax
  uint32_t *v2; // esi
  uint32_t *v3; // ecx
  int **v4; // eax
  int *v5; // edi
  int **v6; // edx
  bool v7; // zf
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // esi
  signed int i; // eax
  int v12; // ebx
  int **v13; // eax
  int *k; // eax
  int *j; // eax
  uint32_t *v16; // ebx
  int v17; // ecx
  unsigned int v18; // edx
  uint32_t *v19; // eax
  uint32_t *v20; // eax
  uint32_t *v21; // esi
  int v22; // [esp-14h] [ebp-44h]
  uint8_t v23[4]; // [esp+0h] [ebp-30h] BYREF
  uint32_t *v24; // [esp+4h] [ebp-2Ch]
  int v25; // [esp+8h] [ebp-28h]
  uint32_t v26[2]; // [esp+Ch] [ebp-24h] BYREF
  uint32_t *v27; // [esp+14h] [ebp-1Ch]
  int v28; // [esp+18h] [ebp-18h]
  int v29; // [esp+1Ch] [ebp-14h]
  int v30; // [esp+20h] [ebp-10h]
  int v31; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(*(this + 6) + 16) != 0 )
  {
    v1 = (void *)*(this + 3);
    v2 = this + 2;
    v27 = this + 2;
    if ( v1 != nullptr )
      j__free(v1);
    v2[1] = 0;
    v2[2] = 0;
    v2[3] = 0;
    v30 = sub_429830((uint16_t)word_77F804);
    v29 = sub_41A5E0(v30 + 53);
    v3 = (uint32_t *)sub_4A2CF0(v23);
    v24 = v3;
    v25 = 0;
    v4 = *(int ***)(dword_8F8500 + 8);
    v5 = *v4;
    v6 = (int **)(dword_8F8500 + 8);
    v7 = *v4 == (int *)v4;
    v31 = 0;
    v28 = dword_8F8500 + 8;
    if ( !v7 )
    {
      do
      {
        v8 = v5[4];
        if ( *(uint32_t *)(v8 + 68) == 0 && v8 != v30 )
        {
          v9 = sub_41A5E0(v8 + 53);
          v10 = (uint32_t *)*v24;
          for ( i = abs32(v29 - v9); v10 != v24; v10 = (uint32_t *)*v10 )
          {
            if ( v10[2] >= i )
              break;
          }
          v26[0] = i;
          v22 = v10[1];
          v26[1] = *(uint16_t *)(v5[4] + 4);
          v12 = sub_52DAA0(v10, v22, v26);
          sub_468240(1);
          v6 = (int **)v28;
          v10[1] = v12;
          v2 = v27;
          **(uint32_t **)(v12 + 4) = v12;
          v3 = v24;
        }
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v13 = (int **)v5[2];
          if ( *((uint8_t *)v13 + 21) != 0 )
          {
            for ( j = (int *)v5[1]; *((uint8_t *)j + 21) == 0; j = (int *)j[1] )
            {
              if ( v5 != (int *)j[2] )
                break;
              v5 = j;
            }
            v5 = j;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( k = *v13; *((uint8_t *)k + 21) == 0; k = (int *)*k )
              v5 = k;
          }
        }
      }
      while ( v5 != *v6 );
    }
    v16 = (uint32_t *)*v3;
    if ( (uint32_t *)*v3 != v3 )
    {
      do
      {
        v17 = v2[1];
        if ( v17 != 0 )
          v18 = (v2[2] - v17) >> 2;
        else
          v18 = 0;
        if ( v17 != 0 && v18 < (v2[3] - v17) >> 2 )
        {
          v19 = (uint32_t *)v2[2];
          *v19 = v16[3];
          v2[2] = v19 + 1;
        }
        else
        {
          sub_430C80((void *)v2[2], 1, (int)(v16 + 3));
        }
        v16 = (uint32_t *)*v16;
      }
      while ( v16 != v24 );
      v3 = v24;
    }
    v20 = (uint32_t *)*v3;
    v7 = *v3 == (uint32_t)v3;
    *v3 = v3;
    v3[1] = v3;
    if ( !v7 )
    {
      do
      {
        v21 = (uint32_t *)*v20;
        j__free(v20);
        v3 = v24;
        v20 = v21;
      }
      while ( v21 != v24 );
    }
    j__free(v3);
  }
}


// ------------------------------------------------------------
// 0x49DB10 sub_49DB10
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB10(uint32_t *this)
{
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 1) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49DB30 sub_49DB30
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB30(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 13) = 0;
  v5 = this + 9;
  for ( i = 3; i != 0; --i )
  {
    if ( *v5 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49DB80 sub_49DB80
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB80(uint32_t **this, int a2)
{
  uint8_t v2; // bl
  int v4; // eax
  int result; // eax

  v2 = a2;
  if ( a2 >= 220 )
    v2 = -36;
  v4 = sub_418DD0(*(this + 14), 0);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
      v4,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  result = sub_418DD0(*(this + 14), 3u);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             264,
             12,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             ((uint8_t)a2 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49DC30 sub_49DC30
// ------------------------------------------------------------
int /*thiscall*/ sub_49DC30(uint32_t *this)
{
  int64_t v2; // rax
  int v3; // edi
  int v4; // eax

  v2 = 1717986919LL * (sub_699000((int)(this + 2)) % 640);
  v3 = (SHIDWORD(v2) >> 5) + (HIDWORD(v2) >> 31);
  if ( v3 < 8 )
  {
    sub_491530(2, 0);
    v4 = sub_418DD0(v3 + 15);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(v4, 43, 328, dword_79C0B0);
    LODWORD(v2) = sub_491630(2);
    if ( v3 == 0 )
    {
      LODWORD(v2) = *(this + 37);
      if ( (uint32_t)v2 == 0 )
      {
        *(this + 37) = *(this + 32) + *(this + 33) + *(this + 34) + *(this + 35) + *(this + 36);
        LODWORD(v2) = sub_432EA0("RESULT_FLASH", -1, 0, 0);
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x49DCF0 sub_49DCF0
// ------------------------------------------------------------
char /*thiscall*/ sub_49DCF0(int this)
{
  uint32_t *v2; // edi
  char result; // al

  v2 = (uint32_t *)(this + 128);
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  sub_432FA0();
  *(uint32_t *)(this + 144) = 0;
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 152) = 255;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  result = sub_698F90(this + 60, 0, 0);
  *v2 = 5000;
  *(uint32_t *)(this + 144) = 30000;
  *(uint32_t *)(this + 132) = 3000;
  *(uint32_t *)(this + 136) = 2000;
  *(uint32_t *)(this + 140) = 1000;
  *(uint32_t *)(this + 124) = 254;
  return result;
}



// ------------------------------------------------------------
// 0x49DD80 sub_49DD80
// ------------------------------------------------------------
int /*thiscall*/ sub_49DD80(int this, int a2)
{
  int v3; // edi
  uint32_t *v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int result; // eax
  unsigned int v10; // [esp-4h] [ebp-Ch]

  v3 = *(uint8_t *)(this + 152);
  v4 = *(uint32_t **)(this + 56);
  v5 = (v3 << 24) | 0xFFFFFF;
  if ( a2 >= 80 )
  {
    v7 = sub_418DD0(v4, 0xEu);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        304,
        108,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 13;
  }
  else
  {
    v6 = sub_418DD0(v4, 0xDu);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
        v6,
        304,
        108,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 14;
  }
  v8 = (*(uint8_t *)(this + 152) << 24) | 0xFFFFFF;
  result = sub_418DD0(*(uint32_t **)(this + 56), v10);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             315,
             108,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             v8,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49DE70 sub_49DE70
// ------------------------------------------------------------
int /*thiscall*/ sub_49DE70(void *this, int a2)
{
  int v2; // esi
  int i; // edi
  uint8_t v4; // bl
  int v5; // eax
  int v6; // eax
  uint8_t v7; // bl
  int v8; // eax
  int result; // eax
  uint32_t v10[5]; // [esp+Ch] [ebp-14h]

  v2 = 0;
  v10[4] = this;
  v10[0] = 6;
  v10[1] = 7;
  v10[2] = 8;
  v10[3] = 9;
  for ( i = 0; i < 4; ++i )
  {
    sub_491530(2, 0);
    v4 = a2;
    if ( a2 >= 150 )
      v4 = -106;
    v5 = sub_418DD0(4);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
        v5,
        166,
        v2 + 160,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v4 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
    v6 = sub_418DD0(v10[i]);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
        v6,
        180,
        v2 + 166,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v2 += 46;
  }
  sub_491530(2, 0);
  v7 = a2;
  if ( a2 >= 150 )
    v7 = -106;
  v8 = sub_418DD0(5);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
      v8,
      113,
      349,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v7 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);
  result = sub_418DD0(10);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             180,
             v2 + 170,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             ((uint8_t)a2 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49E050 sub_49E050
// ------------------------------------------------------------
int /*thiscall*/ sub_49E050(uint32_t *this, int a2)
{
  int v3; // ecx
  int result; // eax
  int i; // esi

  v3 = (int)(this + 2);
  *(this + 1) = a2;
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  sub_698F90(v3, 0, 0);
  if ( *(this + 1) != 0 )
  {
    if ( a2 == 1 )
    {
      *(uint8_t *)(*(this + 12) + 16) = 0;
      for ( i = 0; i < 4; ++i )
        result = sub_432EE0(i);
    }
    else
    {
      if ( *(uint8_t *)(*(this + 12) + 16) == 0 )
      {
        sub_65DC70(lpCriticalSection);
        sub_432EA0("M_RESULT", -1, 0, 0);
      }
      result = *(this + 12);
      *(uint8_t *)(result + 16) = 1;
    }
  }
  else
  {
    sub_49DCF0((int)this);
    result = *(this + 12);
    *(uint8_t *)(result + 16) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E0E0 sub_49E0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49E0E0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 && --result == 0 )
  {
    result = sub_699000((int)(this + 2));
    if ( result >= 4000 )
      return sub_49E050(this, *(this + 1) + 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E110 sub_49E110
// ------------------------------------------------------------
int /*thiscall*/ sub_49E110(int *this, int Value, int a3)
{
  int v4; // esi
  int v5; // eax

  sub_69A110(284, 102, Value, *(this + 38));
  v4 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
  v5 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 64), 0xACu);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
      v5,
      339,
      103,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v4,
      1333788672,
      1333788672);
  return sub_69A110(359, 99, a3, *(this + 38));
}



// ------------------------------------------------------------
// 0x49E1B0 sub_49E1B0
// ------------------------------------------------------------
int /*thiscall*/ sub_49E1B0(int *this, int a2)
{
  int result; // eax
  int v4; // ebx
  bool v5; // zf
  bool v6; // cc
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // [esp+4h] [ebp-8h]
  int *v12; // [esp+8h] [ebp-4h]

  result = a2;
  v11 = 0;
  if ( a2 >= 0 )
  {
    v4 = 161;
    v12 = this + 32;
    v5 = a2 == 0;
    v6 = a2 > 0;
    do
    {
      if ( v6 )
      {
        v7 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
        v8 = sub_418DD0(172);
        if ( v8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
            v8,
            279,
            v4 + 3,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            v7,
            1333788672,
            1333788672);
        sub_69A110(301, v4, *v12, *(this + 38));
      }
      else
      {
        if ( !v5 || result == 4 )
          goto LABEL_16;
        if ( sub_699000((int)(this + 22)) < 100 )
          sub_491530(5, -1);
        v9 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
        v10 = sub_418DD0(172);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
            v10,
            279,
            v4 + 3,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            v9,
            1333788672,
            1333788672);
        sub_69A110(301, v4, *v12, *(this + 38));
        if ( sub_699000((int)(this + 22)) < 100 )
          sub_491630(5);
      }
      result = a2;
LABEL_16:
      v4 += 46;
      v5 = v11 + 1 == result;
      v6 = ++v11 < result;
      ++v12;
    }
    while ( v6 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E340 sub_49E340
// ------------------------------------------------------------
char /*thiscall*/ sub_49E340(int this, void *Block, int a3)
{
  uint8_t *v4; // eax
  int v5; // edi
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  int v9; // edx
  uint8_t *v10; // eax
  uint8_t *v11; // esi
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  int v16; // [esp-8h] [ebp-50h]
  uint32_t v17[3]; // [esp+8h] [ebp-40h]
  uint32_t v18[3]; // [esp+14h] [ebp-34h]
  uint32_t v19[3]; // [esp+20h] [ebp-28h]
  void *v20[4]; // [esp+2Ch] [ebp-1Ch]
  int v21; // [esp+44h] [ebp-4h]
  char *Blocka; // [esp+50h] [ebp+8h]
  int v23; // [esp+54h] [ebp+Ch]

  *(uint32_t *)(this + 116) = Block;
  *(uint32_t *)(this + 120) = a3;
  *(uint32_t *)(this + 56) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 208);
  v4 = operator new(0x68u);
  v5 = 0;
  v21 = 0;
  if ( v4 != nullptr )
    v6 = sub_426BD0(v4);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 48) = v6;
  *((uint32_t *)v6 + 7) = 640;
  *((uint32_t *)v6 + 8) = 480;
  *(uint32_t *)(*(uint32_t *)(this + 48) + 68) = this;
  v7 = operator new(0x68u);
  v21 = 1;
  if ( v7 != nullptr )
    v8 = sub_426BD0(v7);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 52) = v8;
  *((uint32_t *)v8 + 17) = this;
  v16 = *(uint32_t *)(this + 52);
  v21 = -1;
  sub_69A840(v16);
  v9 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 64);
  v18[0] = -5;
  v18[1] = -5;
  v18[2] = -5;
  v19[0] = *(uint32_t *)(this + 56);
  v19[2] = v19[0];
  v20[0] = (void *)22;
  v20[1] = (void *)36;
  v20[2] = (void *)32;
  v17[0] = 0;
  v17[1] = 0;
  v17[2] = 2;
  v19[1] = v9;
  Blocka = (char *)(this + 36);
  do
  {
    v10 = operator new(0x2Cu);
    v11 = v10;
    v20[3] = v10;
    v21 = 2;
    if ( v10 != nullptr )
    {
      v23 = dword_79C0B0;
      v10[4] = 0;
      LOBYTE(v21) = 3;
      *(uint32_t *)v10 = &nengine::CNNumberSet::`vftable';
      sub_699E20(v10);
      sub_699E40(v23, v19[v5], v20[v5], 9);
    }
    else
    {
      v11 = nullptr;
    }
    v12 = v18[v5];
    *(uint32_t *)Blocka = v11;
    *((uint32_t *)v11 + 10) = v12;
    *(uint32_t *)(*(uint32_t *)Blocka + 36) = v17[v5];
    v13 = *(uint32_t *)Blocka;
    ++v5;
    v21 = -1;
    *(uint8_t *)(v13 + 24) = 0;
    Blocka += 4;
  }
  while ( v5 < 3 );
  sub_698F90(this + 60, 0, 0);
  *(uint32_t *)(this + 4) = 0;
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  sub_698F90(this + 8, 0, 0);
  if ( *(uint32_t *)(this + 4) != 0 )
  {
    LOBYTE(v14) = *(uint8_t *)(*(uint32_t *)(this + 48) + 16);
    if ( (uint8_t)v14 == 0 )
    {
      sub_65DC70(lpCriticalSection);
      LOBYTE(v14) = (uint8_t)sub_432EA0("M_RESULT", -1, 0, 0);
    }
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;
  }
  else
  {
    sub_49DCF0(this);
    v14 = *(uint32_t *)(this + 48);
    *(uint8_t *)(v14 + 16) = 0;
  }
  return v14;
}


// ------------------------------------------------------------
// 0x49E560 sub_49E560
// ------------------------------------------------------------
int /*thiscall*/ sub_49E560(int this, int a2)
{
  uint64_t v2; // rax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  uint8_t v7; // bl
  int v8; // eax
  uint8_t v9; // bl
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  double v16; // st7
  int v17; // eax
  int v18; // edi
  int v19; // eax
  float v21; // [esp+48h] [ebp-1Ch]
  float v22; // [esp+4Ch] [ebp-18h]
  int v23; // [esp+54h] [ebp-10h]
  float v24; // [esp+6Ch] [ebp+8h]

  LODWORD(v2) = a2;
  if ( a2 == *(uint32_t *)(this + 48) )
  {
    v4 = *(uint32_t *)(this + 4);
    if ( v4 >= 2 )
    {
      v5 = 255;
      if ( v4 == 2 )
      {
        v6 = sub_699000(this + 8);
        v5 = (uint64_t)sub_4049C0(0.0, 255.0, v6, 800);
      }
      else if ( v4 == 12 )
      {
        v5 = *(uint32_t *)(this + 152);
      }
      sub_49DB80(v5);
      v24 = (double)sub_699000(this + 60) * 0.000033333334;
      sub_491530(2, 0);
      v7 = v5;
      if ( v5 >= 120 )
        v7 = 120;
      v8 = sub_418DD0(1);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)v8 + 128))(
          v8,
          111,
          31,
          dword_79C0B0,
          1065353216,
          1065353216,
          COERCE_FLOAT(LODWORD(v24)),
          (v7 << 24) | 0xFFFFFF,
          1129447424,
          1129447424);
      sub_491630(2);
      v9 = v5;
      if ( v5 >= 220 )
        v9 = -36;
      v10 = sub_418DD0(2);
      if ( v10 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
          v10,
          122,
          71,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v9 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_49DE70((void *)this, v5);
      if ( *(uint32_t *)(this + 4) == 2 && sub_699000(this + 8) >= 800 )
        goto LABEL_41;
    }
    v11 = *(uint32_t *)(this + 4);
    if ( v11 >= 3 )
    {
      if ( v11 == 3 )
      {
        sub_49E110(*(uint32_t *)(this + 124), 0);
        sub_49DD80(0);
      }
      sub_69A110(273, 352, *(uint32_t *)(this + 148), *(uint32_t *)(this + 152));
      if ( *(uint32_t *)(this + 4) == 3 && sub_699000(this + 8) >= 1000 )
        goto LABEL_41;
    }
    v12 = *(uint32_t *)(this + 4);
    if ( v12 >= 4 )
    {
      if ( v12 == 4 )
      {
        v13 = sub_699000(this + 8);
        v21 = (float)*(int *)(this + 124);
        v14 = (uint64_t)sub_4049C0(v21, 0.0, v13, 1000);
        v15 = sub_699000(this + 8);
        v22 = (float)*(int *)(this + 144);
        v16 = sub_4049C0(0.0, v22, v15, 1000);
        sub_49E110(v14, (uint64_t)v16);
        v23 = sub_699000(this + 8) % 160;
        sub_49DD80(v23);
      }
      else
      {
        sub_49E110(*(uint32_t *)(this + 124), *(uint32_t *)(this + 144));
        sub_49DD80(0);
      }
      if ( *(uint32_t *)(this + 4) == 4 && (double)sub_699000(this + 8) >= 1100.0 )
      {
        *(uint32_t *)(this + 124) = 0;
        *(uint8_t *)(this + 101) = 0;
        *(uint8_t *)(this + 102) = 0;
        sub_698F90(this + 88, 0, 0);
LABEL_41:
        LODWORD(v2) = sub_49E050(*(uint32_t *)(this + 4) + 1);
        return v2;
      }
    }
    v17 = *(uint32_t *)(this + 4);
    if ( v17 == 5 || v17 == 6 || v17 == 7 || v17 == 8 )
    {
      v18 = v17 - 5;
      sub_49E1B0((int *)this, v17 - 5);
      if ( *(uint32_t *)(this + 4) == v18 + 5 && sub_699000(this + 8) >= 1000 )
      {
        *(uint8_t *)(this + 101) = 0;
        *(uint8_t *)(this + 102) = 0;
        sub_698F90(this + 88, 0, 0);
        goto LABEL_41;
      }
    }
    if ( *(int *)(this + 4) >= 9 )
    {
      sub_49E1B0((int *)this, 4);
      if ( *(uint32_t *)(this + 4) == 9 && sub_699000(this + 8) >= 1000 )
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 10 )
    {
      sub_49DC30((uint32_t *)this);
      if ( sub_699000(this + 8) >= 560 )
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 11 && sub_699000(this + 8) >= 3000 )
      goto LABEL_41;
    LODWORD(v2) = *(uint32_t *)(this + 4);
    if ( (int)v2 >= 12 )
    {
      v19 = sub_699000(this + 8);
      v2 = (uint64_t)sub_4049C0(255.0, 0.0, v19, 1000);
      *(uint32_t *)(this + 152) = v2;
      if ( *(uint32_t *)(this + 4) == 12 )
      {
        LODWORD(v2) = sub_699000(this + 8);
        if ( (int)v2 >= 1000 )
          LODWORD(v2) = sub_49E050(0);
      }
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x49E930 sub_49E930
// ------------------------------------------------------------
int /*thiscall*/ sub_49E930(int this)
{
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = -1;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 148) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x49E990 sub_49E990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E990(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 255;
  *(this + 2) = 255;
  *(this + 3) = 255;
  *(this + 4) = 255;
  *(this + 5) = 255;
  *(this + 6) = 255;
  *(this + 7) = 255;
  *(this + 8) = 255;
  *(this + 9) = 0xFFFF;
  *(this + 10) = 0xFFFF;
  *(this + 11) = 0xFFFF;
  *(this + 12) = 0xFFFF;
  *(this + 13) = 0xFFFF;
  *(this + 14) = 0xFFFF;
  *(this + 15) = 0xFFFF;
  *(this + 16) = 0xFFFF;
  sub_49E930((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x49E9E0 sub_49E9E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E9E0(uint32_t *Block, char a2)
{
  *Block = &CNWarRoom::`vftable';
  nullsub_3(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x49EA10 sub_49EA10
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA10(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49EA20 sub_49EA20
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA20(uint32_t *this)
{
  uint32_t *v1; // ecx

  v1 = this + 1;
  *v1 = &CNWarRoom::`vftable';
  return nullsub_3(v1);
}



// ------------------------------------------------------------
// 0x49EA30 sub_49EA30
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA30(uint32_t *this, int a2)
{
  return *(this + 1) + 12 * a2;
}



// ------------------------------------------------------------
// 0x49EA50 sub_49EA50
// ------------------------------------------------------------
int /*cdecl*/ sub_49EA50(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 173) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x49EA80 sub_49EA80
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49EA80(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 173) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 173) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EAB0 sub_49EAB0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EAB0(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 173) == 0 )
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
// 0x49EB20 sub_49EB20
// ------------------------------------------------------------
int /*thiscall*/ sub_49EB20(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 173) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 173) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 173) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 173) == 0 );
        if ( *(uint8_t *)(result + 173) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 173) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EBA0 sub_49EBA0
// ------------------------------------------------------------
int */*thiscall*/ sub_49EBA0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 173) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 173) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 173) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 173) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 173) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC10 sub_49EC10
// ------------------------------------------------------------
int /*thiscall*/ sub_49EC10(int *this)
{
  int v1; // edx
  int result; // eax
  uint32_t *v3; // ecx

  v1 = *(this + 2);
  result = 0;
  if ( v1 > 0 )
  {
    v3 = (uint32_t *)(*(this + 1) + 8);
    do
    {
      result += *v3;
      v3 += 3;
      --v1;
    }
    while ( v1 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC30 sub_49EC30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49EC30(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 173) == 0 )
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
// 0x49EC90 sub_49EC90
// ------------------------------------------------------------
int */*thiscall*/ sub_49EC90(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 173) == 0 )
  {
    if ( v3[3] >= *a2 )
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
// 0x49ECD0 sub_49ECD0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_49ECD0(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *result; // eax

  result = operator new(0xB0u);
  if ( result != nullptr )
  {
    *result = a1;
    result[2] = a3;
    result[1] = a2;
    result[3] = *a4;
    result[4] = &CNWarRoom::`vftable';
    qmemcpy(result + 5, a4 + 2, 0x98u);
    *((uint8_t *)result + 172) = a5;
    *((uint8_t *)result + 173) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ED30 sub_49ED30
// ------------------------------------------------------------
uint32_t *sub_49ED30()
{
  uint32_t *result; // eax

  result = operator new(0xB0u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 172) = 1;
  *((uint8_t *)result + 173) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49ED70 sub_49ED70
// ------------------------------------------------------------
int **/*thiscall*/ sub_49ED70(int **this, int **a2, uint32_t *a3)
{
  int *v5; // eax
  int *v6; // esi
  int *v8; // [esp+18h] [ebp+Ch]

  v5 = sub_49EC90(this, a3);
  v6 = *(this + 1);
  v8 = v5;
  if ( v5 == v6 || *a3 < v5[3] )
  {
    *a2 = v6;
    return a2;
  }
  else
  {
    *a2 = v8;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x49EDC0 sub_49EDC0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EDC0(int *this, int a2, int *a3)
{
  int v3; // ebx
  int v4; // esi
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int *v8; // eax
  int *v9; // eax
  int *v10; // eax
  int v11; // eax
  uint32_t *v13; // esi
  int *v14; // eax
  int *v15; // ecx
  int *v16; // eax
  int v17; // eax

  if ( a3 == (int *)-1 )
  {
    v3 = *(this + 2);
    v4 = 0;
    if ( v3 <= 0 )
    {
      return 0;
    }
    else
    {
      v5 = *(this + 1);
      v6 = a2;
      while ( 1 )
      {
        v7 = *(uint32_t *)(v5 + 4);
        v8 = *(int **)(v7 + 4);
        while ( *((uint8_t *)v8 + 173) == 0 )
        {
          if ( v8[3] >= v6 )
          {
            v7 = (int)v8;
            v8 = (int *)*v8;
          }
          else
          {
            v8 = (int *)v8[2];
          }
        }
        v9 = *(int **)(v5 + 4);
        a2 = v7;
        if ( (int *)v7 == v9 || v6 < *(uint32_t *)(v7 + 12) )
        {
          a3 = v9;
          v10 = (int *)&a3;
        }
        else
        {
          v10 = &a2;
        }
        v11 = *v10;
        if ( v11 != *(uint32_t *)(v5 + 4) )
          break;
        ++v4;
        v5 += 12;
        if ( v4 >= v3 )
          return 0;
      }
      return v11 + 16;
    }
  }
  else
  {
    v13 = (uint32_t *)(*(this + 1) + 12 * (uint32_t)a3);
    v14 = sub_49EC90(v13, &a2);
    v15 = (int *)v13[1];
    a3 = v14;
    if ( v14 == v15 || a2 < v14[3] )
    {
      a2 = (int)v15;
      v16 = &a2;
    }
    else
    {
      v16 = (int *)&a3;
    }
    v17 = *v16;
    if ( v17 == v13[1] )
      return 0;
    else
      return v17 + 16;
  }
}



// ------------------------------------------------------------
// 0x49EE90 sub_49EE90
// ------------------------------------------------------------
int /*thiscall*/ sub_49EE90(uint32_t *this, uint32_t *a2)
{
  int v3; // esi
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  int v6; // ebx

  v3 = 12 * (uint32_t)a2;
  v4 = *(uint32_t **)(12 * (uint32_t)a2 + *(this + 1) + 4);
  v5 = (uint32_t *)*v4;
  v6 = 0;
  a2 = (uint32_t *)*v4;
  if ( a2 != v4 )
  {
    do
    {
      if ( sub_48FD50(v5 + 4) )
        ++v6;
      sub_49EBA0((int *)&a2);
      v5 = a2;
    }
    while ( a2 != *(uint32_t **)(v3 + *(this + 1) + 4) );
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49EEE0 sub_49EEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EEE0(uint32_t *this, int a2)
{
  int v3; // esi
  int *v4; // ecx
  int v5; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * a2;
  v4 = *(int **)(12 * a2 + *(this + 1) + 4);
  v5 = *v4;
  v6 = *v4 == (uint32_t)v4;
  v9 = 0;
  a2 = *v4;
  if ( v6 )
    return 0;
  do
  {
    v7 = (uint32_t *)(v5 + 16);
    if ( sub_48FD50((uint32_t *)(v5 + 16)) )
      v9 += sub_48FBB0(v7);
    sub_49EBA0(&a2);
    v5 = a2;
  }
  while ( a2 != *(uint32_t *)(v3 + *(this + 1) + 4) );
  return v9;
}



// ------------------------------------------------------------
// 0x49EF60 sub_49EF60
// ------------------------------------------------------------
int /*thiscall*/ sub_49EF60(uint32_t *this, int a2)
{
  int v3; // esi
  int *v4; // ecx
  int v5; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * a2;
  v4 = *(int **)(12 * a2 + *(this + 1) + 4);
  v5 = *v4;
  v6 = *v4 == (uint32_t)v4;
  v9 = 0;
  a2 = *v4;
  if ( v6 )
    return 0;
  do
  {
    v7 = (uint32_t *)(v5 + 16);
    if ( sub_48FD50((uint32_t *)(v5 + 16)) )
      v9 += sub_48F4C0(v7);
    sub_49EBA0(&a2);
    v5 = a2;
  }
  while ( a2 != *(uint32_t *)(v3 + *(this + 1) + 4) );
  return v9;
}



// ------------------------------------------------------------
// 0x49EFE0 sub_49EFE0
// ------------------------------------------------------------
char /*thiscall*/ sub_49EFE0(int *this, int a2, uint32_t *a3, uint32_t *a4, uint32_t *a5)
{
  int v6; // ecx
  int *v7; // eax
  int v8; // esi
  bool v9; // cc
  int *v11; // [esp+Ch] [ebp-Ch] BYREF
  int v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]

  v6 = *(this + 2);
  v12 = 0;
  if ( v6 <= 0 )
    return 0;
  v13 = 0;
  while ( 1 )
  {
    v7 = *(int **)(v13 + *(this + 1) + 4);
    v8 = *v7;
    v11 = (int *)*v7;
    if ( v11 != v7 )
      break;
LABEL_6:
    v9 = ++v12 < *(this + 2);
    v13 += 12;
    if ( !v9 )
      return 0;
  }
  while ( sub_48FB60((uint32_t *)(v8 + 16), a2, nullptr) == 0 )
  {
    sub_49EBA0((int *)&v11);
    v8 = (int)v11;
    if ( v11 == *(int **)(v13 + *(this + 1) + 4) )
      goto LABEL_6;
  }
  if ( a4 != nullptr )
    *a4 = *(uint32_t *)(v8 + 12);
  if ( a5 != nullptr )
    *a5 = v12;
  if ( a3 != nullptr )
    *a3 = v8 + 16;
  return 1;
}



// ------------------------------------------------------------
// 0x49F090 sub_49F090
// ------------------------------------------------------------
char /*stdcall*/ sub_49F090(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 173);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_49F090(i[2]);
    i = (void **)*i;
    sub_49EC00(v1);
    j__free(v1);
    result = *((uint8_t *)i + 173);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F0E0 sub_49F0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49F0E0(uint32_t *this)
{
  int v2; // ebx
  int v3; // esi
  int v4; // eax
  int v5; // esi
  uint32_t *v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  v2 = 0;
  if ( (int)*(this + 2) > 0 )
  {
    v8 = 0;
    do
    {
      v3 = *(this + 1);
      v4 = *(uint32_t *)(v3 + v8 + 4);
      v5 = v8 + v3;
      sub_49F090(*(void ***)(v4 + 4));
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 4) = *(uint32_t *)(v5 + 4);
      v6 = *(uint32_t **)(v5 + 4);
      *(uint32_t *)(v5 + 8) = 0;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 8) = *(uint32_t *)(v5 + 4);
      ++v2;
      v8 += 12;
    }
    while ( v2 < *(this + 2) );
  }
  return sub_48FE80(0);
}



// ------------------------------------------------------------
// 0x49F150 sub_49F150
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49F150(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  uint32_t *v22; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x1999998 )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  v6 = sub_49ECD0(*(this + 1), (int)a4, *(this + 1), a5, 0);
  v7 = (uint32_t *)*(this + 1);
  v22 = v6;
  ++*(this + 2);
  if ( a4 == v7 )
  {
    v7[1] = v6;
    *(uint32_t *)*(this + 1) = v6;
    *(uint32_t *)(*(this + 1) + 8) = v6;
  }
  else if ( a3 != 0 )
  {
    *a4 = v6;
    v8 = (uint32_t *)*(this + 1);
    if ( a4 == (uint32_t *)*v8 )
      *v8 = v6;
  }
  else
  {
    a4[2] = v6;
    v9 = *(this + 1);
    if ( a4 == *(uint32_t **)(v9 + 8) )
      *(uint32_t *)(v9 + 8) = v6;
  }
  v10 = v6 + 1;
  v11 = (int)v6;
  if ( *(uint8_t *)(v6[1] + 172) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 172) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_49EC30(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
          sub_49EAB0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 172) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_49EAB0(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
        sub_49EC30(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 172) = 1;
      *(uint8_t *)(v14 + 172) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 172) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) != 0 )
      {
        v6 = v22;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 172) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x49F330 sub_49F330
// ------------------------------------------------------------
int /*thiscall*/ sub_49F330(int *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 173) == 0 )
  {
    v8 = *a3;
    do
    {
      v7 = v8 < v6[3];
      v5 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 173) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_49F150(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_49EB20(&a3);
    v9 = a3;
  }
  if ( v9[3] >= *v3 )
  {
    *(uint8_t *)(a2 + 4) = 0;
    *(uint32_t *)a2 = v9;
    return a2;
  }
  else
  {
    v12 = *sub_49F150(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x49F3F0 sub_49F3F0
// ------------------------------------------------------------
int */*thiscall*/ sub_49F3F0(uint32_t *this, int *a2, int a3)
{
  int *v3; // ebx
  int v4; // edi
  int v5; // ecx
  int v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int *v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint8_t *v16; // eax
  char *v17; // ecx
  int v18; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v21; // [esp+34h] [ebp-34h] BYREF
  char v22; // [esp+38h] [ebp-30h]
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v27; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  v27 = this;
  if ( *(uint8_t *)(a3 + 173) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22 = 0;
    sub_4015C0(&v21, "invalid map/set<T> iterator", 0x1Bu);
    v28 = 0;
    sub_401740(pExceptionObject, &v21);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = (int *)a3;
  Block = (void *)a3;
  sub_49EBA0(&a3);
  if ( *(uint8_t *)(*v3 + 173) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    v7 = v27;
    v8 = v27[1];
    if ( *(int **)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( *(int **)v6 == v3 )
    {
      *(uint32_t *)v6 = v4;
    }
    else
    {
      *(uint32_t *)(v6 + 8) = v4;
    }
    if ( *(int **)v7[1] == v3 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
      {
        v9 = (uint32_t *)v6;
      }
      else
      {
        v9 = sub_49EA80((uint32_t *)v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_49EA50(v4);
    }
    goto LABEL_35;
  }
  if ( *(uint8_t *)(v3[2] + 173) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = a3;
  v4 = *(uint32_t *)(a3 + 8);
  if ( (int *)a3 == v3 )
    goto LABEL_8;
  *(uint32_t *)(*v3 + 4) = a3;
  *(uint32_t *)v5 = *v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = *(uint32_t *)(v5 + 4);
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    *(uint32_t *)v6 = v4;
    *(uint32_t *)(v5 + 8) = v3[2];
    *(uint32_t *)(v3[2] + 4) = v5;
  }
  v12 = v27[1];
  if ( *(int **)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int *)v3[1];
    if ( (int *)*v13 == v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  *(uint32_t *)(v5 + 4) = v3[1];
  v14 = *(uint8_t *)(v5 + 172);
  *(uint8_t *)(v5 + 172) = *((uint8_t *)v3 + 172);
  *((uint8_t *)v3 + 172) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 172) == 1 )
  {
    v15 = v27;
    if ( v4 != *(uint32_t *)(v27[1] + 4) )
    {
      do
      {
        if ( *(uint8_t *)(v4 + 172) != 1 )
          break;
        v16 = *(uint8_t **)v6;
        if ( v4 == *(uint32_t *)v6 )
        {
          v16 = *(uint8_t **)(v6 + 8);
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EC30(v15, v6);
            v16 = *(uint8_t **)(v6 + 8);
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 || *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
              v16[172] = 0;
              sub_49EAB0(v15, v16);
              v16 = *(uint8_t **)(v6 + 8);
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
            sub_49EC30(v15, v6);
            break;
          }
        }
        else
        {
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EAB0(v15, (uint32_t *)v6);
            v16 = *(uint8_t **)v6;
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 || *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v16 + 172) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
              v16[172] = 0;
              sub_49EC30(v15, (int)v16);
              v16 = *(uint8_t **)v6;
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
            sub_49EAB0(v15, (uint32_t *)v6);
            break;
          }
        }
        v16[172] = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(uint32_t *)(v15[1] + 4);
        v6 = *(uint32_t *)(v6 + 4);
      }
      while ( !v11 );
    }
    *(uint8_t *)(v4 + 172) = 1;
  }
  v17 = (char *)Block + 16;
  *((uint32_t *)Block + 4) = &CNWarRoom::`vftable';
  nullsub_3(v17);
  j__free(Block);
  v18 = v27[2];
  if ( v18 != 0 )
    v27[2] = v18 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x49F750 sub_49F750
// ------------------------------------------------------------
int */*thiscall*/ sub_49F750(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v6; // eax
  int v7; // ecx
  uint32_t *v8; // eax
  int v10; // edi

  v4 = a4;
  v6 = (int)*(this + 1);
  v7 = a3;
  if ( a3 == *(uint32_t *)v6 && a4 == v6 )
  {
    sub_49F090(*(void ***)(v6 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = v7;
        sub_49EBA0(&a3);
        sub_49F3F0(this, &a4, v10);
        v7 = a3;
      }
      while ( a3 != v4 );
    }
    *a2 = v7;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x49F7D0 sub_49F7D0
// ------------------------------------------------------------
int /*thiscall*/ sub_49F7D0(int *this, int a2, int *a3)
{
  int v3; // esi
  int result; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // ebx
  int *v7; // eax
  int *v8; // edi
  int v9; // esi
  int *v10; // ecx
  uint32_t *v11; // edi
  int *v12; // eax
  int *v13; // edi
  int **v14; // eax
  int v15; // [esp+4h] [ebp-B8h] BYREF
  uint32_t v16[39]; // [esp+8h] [ebp-B4h] BYREF
  char v17[4]; // [esp+A4h] [ebp-18h] BYREF
  void *Block; // [esp+A8h] [ebp-14h]
  int *v19; // [esp+ACh] [ebp-10h]
  int v20; // [esp+B8h] [ebp-4h]

  v3 = a2;
  v19 = this;
  result = sub_49EDC0(this, a2, a3);
  if ( result == 0 )
  {
    v5 = operator new(0x9Cu);
    v6 = v5;
    Block = v5;
    v20 = 0;
    if ( v5 != nullptr )
    {
      *v5 = &CNWarRoom::`vftable';
      sub_49E990(v5 + 1);
      nullsub_3(v6);
      unknown_libname_7(v3);
    }
    else
    {
      v6 = nullptr;
    }
    v7 = a3;
    v15 = v3;
    *((uint8_t *)v6 + 152) = (uint8_t)a3;
    v16[0] = &CNWarRoom::`vftable';
    qmemcpy(&v16[1], v6 + 1, 0x98u);
    v8 = v19;
    v9 = 12 * (uint32_t)v7;
    v10 = (int *)(12 * (uint32_t)v7 + v19[1]);
    v20 = 1;
    sub_49F330(v10, (int)v17, &v15);
    v20 = -1;
    v16[0] = &CNWarRoom::`vftable';
    nullsub_3(v16);
    (*(void (/*thiscall*/ **)(uint32_t *, int))*v6)(v6, 1);
    v11 = (uint32_t *)(v9 + v8[1]);
    v12 = sub_49EC90(v11, &a2);
    v13 = (int *)v11[1];
    a3 = v12;
    if ( v12 == v13 || a2 < v12[3] )
    {
      a2 = (int)v13;
      v14 = (int **)&a2;
    }
    else
    {
      v14 = &a3;
    }
    return (int)(*v14 + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F900 sub_49F900
// ------------------------------------------------------------
void /*thiscall*/ sub_49F900(int **this)
{
  int v2; // [esp+4h] [ebp-4h] BYREF

  sub_49F750(this, &v2, **(this + 1), (int)*(this + 1));
  j__free(*(this + 1));
  *(this + 1) = nullptr;
  *(this + 2) = nullptr;
}



// ------------------------------------------------------------
// 0x49F940 sub_49F940
// ------------------------------------------------------------
void /*thiscall*/ sub_49F940(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_49ED30();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 173) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
}



// ------------------------------------------------------------
// 0x49F970 sub_49F970
// ------------------------------------------------------------
int /*thiscall*/ sub_49F970(uint32_t *this, int Block)
{
  int *v3; // eax
  uint32_t *v4; // edi

  *(this + 2) = Block;
  v3 = (int *)operator new(12 * Block + 4);
  v4 = nullptr;
  if ( v3 != nullptr )
  {
    v4 = v3 + 1;
    *v3 = Block;
    `eh vector constructor iterator'(
      v3 + 1,
      0xCu,
      Block,
      (void (/*thiscall*/ *)(void *))sub_49F940,
      (void (/*thiscall*/ *)(void *))sub_49F900);
  }
  *(this + 1) = v4;
  return sub_49F0E0(this);
}



// ------------------------------------------------------------
// 0x49F9F0 sub_49F9F0
// ------------------------------------------------------------
void /*thiscall*/ sub_49F9F0(uint32_t *this)
{
  char *v1; // eax
  char *v2; // esi

  v1 = (char *)*(this + 1);
  if ( v1 != nullptr )
  {
    v2 = v1 - 4;
    `eh vector destructor iterator'(v1, 0xCu, *((uint32_t *)v1 - 1), (void (/*thiscall*/ *)(void *))sub_49F900);
    j_j__free(v2);
  }
}



// ------------------------------------------------------------
// 0x49FA20 sub_49FA20
// ------------------------------------------------------------
int /*thiscall*/ sub_49FA20(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  int v4; // ebx
  int v5; // edi
  float *v6; // esi
  int v7; // ebx
  int v8; // edi
  float *v9; // esi
  int v10; // ecx
  int v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // edx
  int v14; // esi
  int v15; // esi
  int v16; // esi
  int v17; // eax
  int v18; // esi
  int v19; // eax
  int v20; // eax
  char *v23; // [esp+10h] [ebp-Ch]
  int v24; // [esp+14h] [ebp-8h]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]
  int v27; // [esp+18h] [ebp-4h]
  int v28; // [esp+18h] [ebp-4h]

  *a4 = 0;
  v4 = 0;
  v5 = 0;
  v6 = (float *)this;
  v23 = (char *)a2 - this;
  do
  {
    v24 = (uint64_t)(*v6 * 10.0);
    if ( v24 != 0 )
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)v6] * 10.0) == v24 )
      {
        v4 |= 2 << v5;
      }
      else
      {
        *a3++ = *(uint32_t *)v6;
        *a4 += 4;
      }
    }
    else
    {
      v4 |= 1 << v5;
    }
    v5 += 2;
    ++v6;
  }
  while ( v5 < 6 );
  v26 = v4 << 26;
  v7 = 0;
  v8 = 0;
  v9 = (float *)(this + 12);
  do
  {
    v25 = (uint64_t)(*v9 * 10.0);
    if ( v25 != 0 )
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)v9] * 10.0) == v25 )
      {
        v7 |= 2 << v8;
      }
      else
      {
        *a3++ = *(uint32_t *)v9;
        *a4 += 4;
      }
    }
    else
    {
      v7 |= 1 << v8;
    }
    v8 += 2;
    ++v9;
  }
  while ( v8 < 6 );
  v10 = *(uint32_t *)(this + 24);
  v11 = 0;
  v27 = (v7 << 20) | v26;
  if ( v10 != 0 )
  {
    v13 = a3;
    if ( a2[6] == v10 )
    {
      v12 = a4;
      v11 = 2;
    }
    else
    {
      *a3 = v10;
      v12 = a4;
      v13 = a3 + 1;
      *a4 += 4;
    }
  }
  else
  {
    v12 = a4;
    v13 = a3;
    v11 = 1;
  }
  v14 = *(uint32_t *)(this + 28);
  if ( v14 != 0 )
  {
    if ( a2[7] == v14 )
    {
      v11 |= 8u;
    }
    else
    {
      *v13++ = v14;
      *v12 += 4;
    }
  }
  else
  {
    v11 |= 4u;
  }
  v15 = *(uint32_t *)(this + 32);
  if ( v15 != 0 )
  {
    if ( a2[8] == v15 )
    {
      v11 |= 0x20u;
    }
    else
    {
      *v13++ = v15;
      *v12 += 4;
    }
  }
  else
  {
    v11 |= 0x10u;
  }
  v16 = (v11 << 14) | v27;
  v17 = *(uint32_t *)(this + 36);
  v28 = v16;
  v18 = 0;
  if ( v17 != 0 )
  {
    if ( a2[9] == v17 )
    {
      v18 = 2;
    }
    else if ( v17 == -1 )
    {
      v18 = 3;
    }
    else
    {
      *v13++ = v17;
      *v12 += 4;
    }
  }
  else
  {
    v18 = 1;
  }
  v19 = *(uint32_t *)(this + 40);
  if ( v19 != 0 )
  {
    if ( a2[10] == v19 )
    {
      v18 |= 8u;
    }
    else if ( v19 == -1 )
    {
      v18 |= 0xCu;
    }
    else
    {
      *v13++ = v19;
      *v12 += 4;
    }
  }
  else
  {
    v18 |= 4u;
  }
  v20 = *(uint32_t *)(this + 44);
  if ( v20 != 0 )
  {
    if ( a2[11] == v20 )
    {
      v18 |= 0x20u;
    }
    else if ( v20 == -1 )
    {
      v18 |= 0x30u;
    }
    else
    {
      *v13 = v20;
      *v12 += 4;
    }
  }
  else
  {
    v18 |= 0x10u;
  }
  return v28 | (32 * ((8 * v18) | *(uint8_t *)(this + 48) & 7));
}


// ------------------------------------------------------------
// 0x49FC60 sub_49FC60
// ------------------------------------------------------------
int /*thiscall*/ sub_49FC60(char *this)
{
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 26) = 0;
  *(this + 108) = 1;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 0;
  *(uint16_t *)(this + 117) = 0;
  *(this + 119) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *(this + 172) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  *(this + 196) = 0;
  *((uint32_t *)this + 50) = 0;
  *(this + 124) = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = -1;
  *((uint32_t *)this + 11) = -1;
  *((uint32_t *)this + 12) = -1;
  *(this + 52) = 1;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 65) = 0;
  *(uint32_t *)(this + 77) = 0;
  *(uint32_t *)(this + 89) = -1;
  *(uint32_t *)(this + 57) = 0;
  *(uint32_t *)(this + 69) = 0;
  *(uint32_t *)(this + 81) = 0;
  *(uint32_t *)(this + 93) = -1;
  *(uint32_t *)(this + 61) = 0;
  *(uint32_t *)(this + 73) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint32_t *)(this + 97) = -1;
  *(this + 101) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x49FD20 sub_49FD20
// ------------------------------------------------------------
char /*thiscall*/ sub_49FD20(int this)
{
  int v2; // ecx
  char result; // al
  int v4; // ecx

  v2 = *(uint32_t *)(this + 104);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 4))(v2, 0);
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  result = sub_698F90(this + 144, 0, 0);
  v4 = *(uint32_t *)(this + 200);
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = -v4;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint8_t *)(this + 196) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49FD80 sub_49FD80
// ------------------------------------------------------------
int /*thiscall*/ sub_49FD80(float *this, int a2, float *a3)
{
  int result; // eax
  int v6; // eax
  double v7; // st7
  int v8; // edx
  float *v9; // ecx
  double v10; // st6
  double v11; // st6
  int v12; // ebx
  int v13; // eax
  float *v14; // ecx
  int v15; // ebx
  int v16; // eax
  int *v17; // ecx
  int v18; // eax
  char v19; // al
  float *v20; // eax
  double v21; // st7
  float v22; // [esp+0h] [ebp-20h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+14h] [ebp-Ch]
  int v25; // [esp+18h] [ebp-8h]
  int v26; // [esp+1Ch] [ebp-4h]
  int v27; // [esp+28h] [ebp+8h]
  float v28; // [esp+28h] [ebp+8h]

  if ( *(this + a2 + 4) == 0.0 && *((uint32_t *)this + a2 + 7) == 0 )
    return 0;
  v6 = *((uint32_t *)this + a2 + 7);
  v7 = *(this + a2 + 4);
  v8 = *((uint32_t *)this + a2 + 10);
  v26 = v8;
  if ( v6 != 0 )
  {
    v9 = a3;
    if ( v8 == -1 || v8 >= (int)a3 )
    {
      v11 = (double)((int)a3 * v6) * 0.001 + *(this + a2 + 4);
      *(this + a2 + 4) = v11;
      v7 = (v7 + v11) * 0.5;
      if ( v8 != -1 )
      {
        *((uint32_t *)this + a2 + 10) = v8 - (uint32_t)v9;
        if ( (float *)v8 == v9 )
          *(this + a2 + 7) = 0.0;
      }
    }
    else
    {
      v27 = (int)a3 - v8;
      *(this + a2 + 10) = 0.0;
      *(this + a2 + 7) = 0.0;
      v10 = (double)(v6 * v8) * 0.001 + *(this + a2 + 4);
      *(this + a2 + 4) = v10;
      v7 = ((v7 + v10) * 0.5 * (double)v26 + (double)v27 * v10) / (double)(int)a3;
    }
  }
  v12 = 0;
  v28 = (double)(int)a3 * v7 * 0.001;
  if ( *((uint32_t *)this + 26) != 0 && *((uint8_t *)this + 108) != 0 )
    goto LABEL_25;
  if ( *(uint32_t *)this == 0 )
    goto LABEL_25;
  v23 = 0;
  v24 = 0;
  v25 = 0;
  a3 = this + 1;
  do
  {
    v13 = sub_432F40(*a3);
    v14 = a3;
    *(&v23 + v12++) = v13;
    a3 = v14 + 1;
  }
  while ( v12 < 3 );
  v22 = v28 + *(this + a2 + 1);
  v15 = sub_432F40(v22);
  if ( *(&v23 + a2) == v15 )
  {
LABEL_25:
    v21 = v28 + *(this + a2 + 1);
    a3 = *((float **)this + a2 + 7);
    v20 = a3;
    *(this + a2 + 1) = v21;
    if ( v20 != nullptr )
    {
      result = 1;
      if ( (double)(int)a3 * *(this + a2 + 4) >= 0.0 )
        return 3;
    }
    else if ( *(this + a2 + 4) == 0.0 )
    {
      return 0;
    }
    else
    {
      return 2;
    }
  }
  else
  {
    while ( 1 )
    {
      v26 = *(&v23 + a2);
      v16 = v26 >= v15 ? v26 - 1 : v26 + 1;
      v17 = *(int **)this;
      *(&v23 + a2) = v16;
      a3 = nullptr;
      v18 = *v17;
      v19 = a2 == 2
          ? (*(int (/*stdcall*/ **)(int))(v18 + 132))(v25)
          : (*(unsigned int (/*stdcall*/ **)(int, int, float **))(v18 + 136))(v23, v24, &a3);
      if ( v19 == 0 )
        break;
      if ( *(&v23 + a2) == v15 )
        goto LABEL_25;
    }
    *(this + a2 + 1) = (float)v26;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)this + 40))(*(uint32_t *)this, 1) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, float *))(**(uint32_t **)this + 532))(
        *(uint32_t *)this,
        a2,
        *((uint32_t *)this + a2 + 4),
        a3);
    return 4;
  }
  return result;
}


// ------------------------------------------------------------
// 0x49FFC0 sub_49FFC0
// ------------------------------------------------------------
void /*userpurge*/ sub_49FFC0(uint32_t *a1@<ecx>, int a2@<edi>, int a3@<esi>, int a4, char a5)
{
  int v6; // ecx
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  const void *v17; // esi
  void *v18; // edi
  int v19; // eax

  v6 = *a1;
  if ( v6 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 308))(v6) != 0
    && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 80))(*a1) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 80))(*a1) + 132) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 4, 1, a2, a3);
    v7 = *(uint32_t *)dword_8F8520;
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 48))(*a1);
    (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
    v9 = *(uint32_t *)dword_8F8520;
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 52))(*a1);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    v13 = *(uint32_t *)dword_8F8520;
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
    v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 80))(*a1);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(
      dword_8F8520,
      *(uint8_t *)(*(uint32_t *)(v15 + 132) + 112));
    v16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*a1 + 80))(*a1);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(
      dword_8F8520,
      *(uint8_t *)(*(uint32_t *)(v16 + 132) + 116));
    if ( (uint8_t)a4 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 16);
      v17 = a1 + 1;
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a1 + 1, 49);
      if ( a5 == 1 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
      v18 = (char *)a1 + 53;
    }
    else
    {
      v18 = (char *)a1 + 53;
      v17 = a1 + 1;
      v19 = sub_49FA20((char *)a1 + 53, &unk_9A026C, &a4);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v19);
      (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A026C, a4);
      if ( a5 == 1 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
    }
    qmemcpy(v18, v17, 0x31u);
    a1[45] = sub_699000((int)(a1 + 36));
    *((uint8_t *)a1 + 196) = 0;
  }
}


