// ============================================================
// 【40JP逆向源代码工程】game/rtti_core.cpp
// 模块: RTTI 类方法密集区(战斗对象核心)
// 来源: work/dump_misca.txt  区块: 0x4A0000-0x4B0000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 531
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4A0180 sub_4A0180
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0180(uint32_t *this, unsigned int a2)
{
  uint32_t *v2; // ebx
  float *v3; // esi
  int v4; // eax
  char *v5; // eax
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
  char *v26; // [esp+18h] [ebp-8h]
  int v27; // [esp+28h] [ebp+8h]

  v2 = this;
  if ( (a2 & 0x10) != 0 )
  {
    v3 = (float *)((char *)this + 53);
    v26 = (char *)this + 53;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 49);
    goto LABEL_71;
  }
  v4 = (a2 >> 26) & 3;
  if ( v4 == 1 )
  {
    v5 = (char *)this + 53;
    *(uint32_t *)((char *)this + 53) = 0;
LABEL_8:
    v26 = v5;
    goto LABEL_9;
  }
  v6 = v4 == 0;
  v5 = (char *)this + 53;
  if ( !v6 )
  {
    *(uint32_t *)v5 = *(this + 1);
    goto LABEL_8;
  }
  v26 = (char *)this + 53;
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)this + 53, 4);
LABEL_9:
  v7 = (a2 >> 28) & 3;
  if ( v7 == 1 )
  {
    *(uint32_t *)((char *)v2 + 57) = 0;
  }
  else if ( v7 != 0 )
  {
    *(uint32_t *)((char *)v2 + 57) = v2[2];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 57, 4);
  }
  if ( a2 >> 30 == 1 )
  {
    *(uint32_t *)((char *)v2 + 61) = 0;
  }
  else if ( a2 >> 30 != 0 )
  {
    *(uint32_t *)((char *)v2 + 61) = v2[3];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 61, 4);
  }
  v8 = (a2 >> 20) & 3;
  if ( v8 == 1 )
  {
    *(uint32_t *)((char *)v2 + 65) = 0;
  }
  else if ( v8 != 0 )
  {
    *(uint32_t *)((char *)v2 + 65) = v2[4];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 65, 4);
  }
  v9 = (((a2 >> 20) & 0x3F) >> 2) & 3;
  if ( v9 == 1 )
  {
    *(uint32_t *)((char *)v2 + 69) = 0;
  }
  else if ( v9 != 0 )
  {
    *(uint32_t *)((char *)v2 + 69) = v2[5];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 69, 4);
  }
  v10 = ((a2 >> 20) & 0x3F) >> 4;
  if ( v10 == 1 )
  {
    *(uint32_t *)((char *)v2 + 73) = 0;
  }
  else if ( v10 != 0 )
  {
    *(uint32_t *)((char *)v2 + 73) = v2[6];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 73, 4);
  }
  if ( (uint16_t)a2 >> 14 == 1 )
  {
    *(uint32_t *)((char *)v2 + 77) = 0;
  }
  else if ( (uint16_t)a2 >> 14 != 0 )
  {
    *(uint32_t *)((char *)v2 + 77) = v2[7];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 77, 4);
  }
  v11 = (((a2 >> 14) & 0x3F) >> 2) & 3;
  if ( v11 == 1 )
  {
    *(uint32_t *)((char *)v2 + 81) = 0;
  }
  else if ( v11 != 0 )
  {
    *(uint32_t *)((char *)v2 + 81) = v2[8];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 81, 4);
  }
  v12 = ((a2 >> 14) & 0x3F) >> 4;
  if ( v12 == 1 )
  {
    *(uint32_t *)((char *)v2 + 85) = 0;
  }
  else if ( v12 != 0 )
  {
    *(uint32_t *)((char *)v2 + 85) = v2[9];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 85, 4);
  }
  v13 = BYTE1(a2) & 3;
  if ( v13 == 3 )
  {
    *(uint32_t *)((char *)v2 + 89) = -1;
  }
  else if ( v13 == 1 )
  {
    *(uint32_t *)((char *)v2 + 89) = 0;
  }
  else if ( (a2 & 0x300) != 0 )
  {
    *(uint32_t *)((char *)v2 + 89) = v2[10];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 89, 4);
  }
  v14 = (((a2 >> 8) & 0x3F) >> 2) & 3;
  if ( v14 == 3 )
  {
    *(uint32_t *)((char *)v2 + 93) = -1;
  }
  else if ( v14 == 1 )
  {
    *(uint32_t *)((char *)v2 + 93) = 0;
  }
  else if ( v14 != 0 )
  {
    *(uint32_t *)((char *)v2 + 93) = v2[11];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 93, 4);
  }
  v15 = ((a2 >> 8) & 0x3F) >> 4;
  if ( v15 == 3 )
  {
    *(uint32_t *)((char *)v2 + 97) = -1;
  }
  else if ( v15 == 1 )
  {
    *(uint32_t *)((char *)v2 + 97) = 0;
  }
  else if ( v15 != 0 )
  {
    *(uint32_t *)((char *)v2 + 97) = v2[12];
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (int)v2 + 97, 4);
  }
  v3 = (float *)v26;
  *((uint8_t *)v2 + 101) = (a2 >> 5) & 7;
LABEL_71:
  result = (a2 & 0x10) != 0;
  if ( (a2 & 0x10) != 0 )
  {
    qmemcpy(v2 + 1, v3, 0x31u);
  }
  else
  {
    v17 = v3 + 6;
    v18 = (float *)(v2 + 7);
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
        if ( v26 != (char *)-24 && *((int *)v17 + 3) > 0 )
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
        v2 = this;
      }
      ++v18;
      ++v17;
    }
    result = v26[48];
    *((uint8_t *)v2 + 52) = result;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4A0550 sub_4A0550
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0550(float *this, int a2)
{
  int v3; // eax
  int v5; // eax
  float v6; // [esp+Ch] [ebp+8h]

  v3 = *((uint32_t *)this + 9);
  if ( v3 != 0 || a2 == 0 )
  {
    v5 = a2 * v3;
    if ( v5 <= 0 )
    {
      v6 = sqrt((double)(-2 * v5));
      if ( a2 < 0 )
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
void /*thiscall*/ sub_4A05C0(int this, int a2)
{
  int v2; // eax
  float v3; // [esp+0h] [ebp-4h]

  v2 = *(uint32_t *)(this + 36);
  if ( v2 < 0 && a2 >= 0 )
  {
    v3 = (double)-(a2 * v2) * 0.001;
    sub_494F20((float *)this, 2, v3);
  }
}



// ------------------------------------------------------------
// 0x4A0600 sub_4A0600
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0600(int *this, int a2)
{
  double v2; // st6

  v2 = (double)*(this + a2 + 7);
  if ( v2 * *((float *)this + a2 + 4) < 0.0 )
    *(this + a2 + 10) = (uint64_t)(*((float *)this + a2 + 4) * -1000.0 / v2);
}



// ------------------------------------------------------------
// 0x4A0650 sub_4A0650
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0650(int this, int a2)
{
  if ( *(uint32_t *)(this + 104) != 0 && *(uint8_t *)(this + 108) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 104) + 40))(*(uint32_t *)(this + 104), a2);
  else
    return sub_432F40(*(float *)(this + 4 * a2 + 4));
}



// ------------------------------------------------------------
// 0x4A0680 sub_4A0680
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0680(int this, int a2)
{
  int v3; // ecx
  char result; // al
  int v5; // ecx

  if ( (uint8_t)a2 != *(uint8_t *)(this + 172) )
  {
    *(uint8_t *)(this + 172) = a2;
    v3 = this + 144;
    if ( (uint8_t)a2 != 0 )
      result = sub_699030(v3);
    else
      result = sub_698FE0(v3);
    v5 = *(uint32_t *)(this + 104);
    if ( v5 != 0 )
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 56))(v5, a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A06D0 sub_4A06D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4A06D0(int this, int a2)
{
  int v3; // ebx
  uint64_t v4; // rax

  *(uint32_t *)(this + 128) = a2;
  if ( a2 != 0 )
  {
    *(uint32_t *)(this + 132) = (uint64_t)*(float *)(this + 4)
                            - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
    v4 = (uint64_t)*(float *)(this + 8);
    *(uint32_t *)(this + 136) = v4 - v3;
    *(uint32_t *)(this + 140) = (uint64_t)*(float *)(this + 12)
                            - (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 128))(a2, HIDWORD(v4));
  }
}



// ------------------------------------------------------------
// 0x4A0740 sub_4A0740
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0740(int *this, int a2)
{
  int result; // eax

  sub_699070(a2);
  result = *(this + 26);
  if ( result != 0 )
    return (*(int (/*stdcall*/ **)(int))(*(uint32_t *)result + 68))(a2);
  return result;
}



// ------------------------------------------------------------
// 0x4A0770 sub_4A0770
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0770(uint32_t *this, int a2)
{
  *this = a2;
  return sub_49FD20((int)this);
}



// ------------------------------------------------------------
// 0x4A0790 sub_4A0790
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0790(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  double v4; // st7
  double v5; // st7
  double v6; // st7
  int v7; // edi
  uint32_t *v8; // ebx
  int v9; // ecx
  int v10; // eax
  double v11; // st7
  int *v12; // ebx
  int v13; // edx
  int v14; // ecx
  float *v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ebx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // ebx
  int v26; // ecx
  int v27; // eax
  char v28; // al
  int v29; // eax
  int v30; // eax
  int v31; // ecx
  int v32; // edi
  int v33; // eax
  uint32_t v34[3]; // [esp+4h] [ebp-18h]
  int v35; // [esp+10h] [ebp-Ch]
  int v36; // [esp+14h] [ebp-8h]
  float *v37; // [esp+18h] [ebp-4h]

  if ( *((uint8_t *)this + 172) == 0 )
  {
    v37 = (float *)(sub_699000((int)(this + 36)) - *(this + 44));
    v2 = sub_699000((int)(this + 36));
    v3 = *(this + 32);
    *(this + 44) = v2;
    if ( v3 != 0 )
    {
      v36 = *(this + 33) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
      v4 = (double)v36;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 1) = v4;
      v36 = *(this + 34) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 124))(*(this + 32));
      v5 = (double)v36;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 2) = v5;
      v36 = *(this + 35) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 32) + 128))(*(this + 32));
      v6 = (double)v36;
      *((uint8_t *)this + 124) = 1;
      *((float *)this + 3) = v6;
    }
    v7 = 0;
    v8 = this + 46;
    do
      *v8++ = sub_49FD80(v7++, v37);
    while ( v7 < 3 );
    if ( *(this + 26) != 0 && *((uint8_t *)this + 108) != 0 )
    {
      if ( *(this + 28) == 2 && *((uint8_t *)this + 116) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(this + 30));
      }
      else
      {
        v37 = (float *)(this + 1);
        v7 = 0;
        v36 = -4 - (uint32_t)this;
        do
        {
          v9 = *(this + 26);
          if ( v9 != 0 && *((uint8_t *)this + 108) != 0 )
            v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, v7);
          else
            v10 = sub_432F40(*v37);
          v11 = *v37;
          v12 = (int *)*(this + 26);
          v34[v7] = v10;
          v13 = *v12;
          v35 = (uint64_t)v11;
          v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 16))(v12);
          v15 = v37;
          *(uint32_t *)((char *)v37 + v36 + v14) = v35;
          ++v7;
          v37 = v15 + 1;
        }
        while ( v7 < 3 );
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 26) + 8))(*(this + 26));
        if ( *this != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 40))(*this, 1) != 0
          && (*((uint8_t *)this + 116) == 0 || *(this + 28) == 0) )
        {
          v16 = *(this + 26);
          if ( v16 != 0 && *((uint8_t *)this + 108) != 0 )
            v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 40))(v16, 1);
          else
            v17 = sub_432F40(*((float *)this + 2));
          v18 = *(this + 26);
          v19 = v17;
          if ( v18 != 0 && *((uint8_t *)this + 108) != 0 )
            v20 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v18 + 40))(v18, 0);
          else
            v20 = sub_432F40(*((float *)this + 1));
          v7 = (int)(this + 30);
          if ( (*(uint8_t (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)*this + 136))(v20, v19, this + 30) == 0
            || ((v21 = *(this + 26)) == 0 || *((uint8_t *)this + 108) == 0
              ? (v22 = sub_432F40(*((float *)this + 3)))
              : (v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 40))(v21, 2)),
                (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v22) == 0) )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*this + 532))(*this, -1, 0, *(uint32_t *)v7);
            *((uint8_t *)this + 116) = 1;
          }
        }
        if ( *((uint8_t *)this + 116) != 0 && *(this + 28) == 1 && *((uint8_t *)this + 124) == 0 )
        {
          v7 = 0;
          v36 = 0;
          do
          {
            v23 = *(this + 26);
            if ( *((uint8_t *)this + v7 + 117) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)v23 + 36))(v23, v7, v34[v7]);
            }
            else
            {
              if ( v23 != 0 && *((uint8_t *)this + 108) != 0 )
                v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v23 + 40))(v23, v7);
              else
                v24 = sub_432F40(*((float *)this + v7 + 1));
              v37 = (float *)v24;
              if ( v34[v7] != v24 )
              {
                while ( 1 )
                {
                  v25 = v34[v7];
                  v34[v7] = v25 >= (int)v37 ? v25 - 1 : v25 + 1;
                  v26 = *(this + 26);
                  if ( v7 == 2 )
                  {
                    if ( v26 != 0 && *((uint8_t *)this + 108) != 0 )
                    {
                      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 40))(v26, 2);
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v27);
                    }
                    else
                    {
                      v29 = sub_432F40(*((float *)this + 3));
                      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*this + 132))(*this, v29);
                    }
                  }
                  else
                  {
                    v30 = v26 != 0 && *((uint8_t *)this + 108) != 0
                        ? (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 40))(v26, 1)
                        : sub_432F40(*((float *)this + 2));
                    v31 = *(this + 26);
                    v32 = v30;
                    if ( v31 != 0 && *((uint8_t *)this + 108) != 0 )
                      v33 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v31 + 40))(v31, 0);
                    else
                      v33 = sub_432F40(*((float *)this + 1));
                    v28 = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*this + 136))(*this, v33, v32, 0);
                    v7 = v36;
                  }
                  if ( v28 == 0 )
                    break;
                  if ( (float *)v34[v7] == v37 )
                    goto LABEL_68;
                }
                (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + 26) + 36))(*(this + 26), v7, v25);
                v34[v7] = v25;
                *((uint8_t *)this + v7 + 117) = 1;
              }
            }
LABEL_68:
            v36 = ++v7;
          }
          while ( v7 < 3 );
        }
        *((uint8_t *)this + 124) = 0;
      }
    }
    if ( *(this + 50) != 0 && sub_699000((int)(this + 36)) >= (unsigned int)(*(this + 50) + *(this + 45)) )
      sub_49FFC0(this, v7, (int)this, 0, 0);
  }
}


// ------------------------------------------------------------
// 0x4A0B60 sub_4A0B60
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0B60(int this, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int result; // eax
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int v11; // ebx
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+8h] [ebp-Ch]
  int v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]
  float *v16; // [esp+1Ch] [ebp+8h]

  v3 = *(uint32_t *)(this + 104);
  if ( v3 != 0 && *(uint8_t *)(this + 108) != 0 )
    v4 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v3 + 40))(v3, 0);
  else
    v4 = sub_432F40(*(float *)(this + 4));
  v5 = *(uint32_t *)(this + 104);
  v15 = v4;
  if ( v5 != 0 && *(uint8_t *)(this + 108) != 0 )
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, 1);
  else
    v6 = sub_432F40(*(float *)(this + 8));
  v7 = *(uint32_t *)(this + 104);
  v14 = v6;
  if ( v7 != 0 && *(uint8_t *)(this + 108) != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 2);
  else
    result = sub_432F40(*(float *)(this + 12));
  v9 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 104);
  v12 = result;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(uint32_t *)(this + 104) = a2;
  if ( a2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 68))(a2, *(uint32_t *)(this + 152));
    v11 = 0;
    v16 = (float *)(this + 4);
    do
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + v11);
      *(uint8_t *)(this + 124) = 1;
      v11 += 4;
      *v16++ = (float)v13;
    }
    while ( v11 < 12 );
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 8))(a2);
    *(uint8_t *)(this + 116) = 0;
    *(uint16_t *)(this + 117) = 0;
    *(uint8_t *)(this + 119) = 0;
    *(uint32_t *)(this + 120) = 0;
    return 0;
  }
  else
  {
    *(float *)(this + 4) = (float)v15;
    *(float *)(this + 8) = (float)v14;
    *(uint8_t *)(this + 124) = 1;
    *(float *)(this + 12) = (float)v12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A0C80 sub_4A0C80
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0C80(void *this, int a2)
{
  return (int)this + 1364 * a2 + 676;
}



// ------------------------------------------------------------
// 0x4A0CB0 sub_4A0CB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A0CB0(uint32_t *Block, char a2)
{
  *Block = &CNGoblinCommon::`vftable';
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A0CE0 sub_4A0CE0
// ------------------------------------------------------------
void /*thiscall*/ sub_4A0CE0(uint32_t *this)
{
  *this = &CNMonsterFriendShip::`vftable';
}



// ------------------------------------------------------------
// 0x4A0CF0 sub_4A0CF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A0CF0(uint32_t *this, char ArgList, int a3, char a4)
{
  sub_58E0E0((int)this, ArgList, a3, a4);
  *this = &CNGhoulOilSellerOlrek::`vftable';
  sub_58E3B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A0D70 sub_4A0D70
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0D70(uint32_t *this, int a2)
{
  *(this + 152) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4A0DC0 sub_4A0DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DC0(uint32_t *this)
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - *(this + 79) / 2;
}



// ------------------------------------------------------------
// 0x4A0DE0 sub_4A0DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0DE0(uint32_t *this)
{
  return *(this + 79) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 440))(this);
}



// ------------------------------------------------------------
// 0x4A0E00 sub_4A0E00
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E00(uint32_t *this)
{
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - *(this + 80) / 2;
}



// ------------------------------------------------------------
// 0x4A0E20 sub_4A0E20
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0E20(uint32_t *this)
{
  return *(this + 80) + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 448))(this);
}



// ------------------------------------------------------------
// 0x4A0E40 sub_4A0E40
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E40(uint8_t *this, char a2)
{
  *(this + 612) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4A0E70 sub_4A0E70
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0E70(uint8_t *this, char a2)
{
  *(this + 640) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4A0EC0 sub_4A0EC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0EC0(uint32_t *this)
{
  if ( *(this + 142) == -1 )
    return 1000000000;
  else
    return sub_699000((int)(this + 2)) - *(this + 142);
}



// ------------------------------------------------------------
// 0x4A0EF0 sub_4A0EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0EF0(uint32_t *this)
{
  return *(this + 143);
}



// ------------------------------------------------------------
// 0x4A0F00 sub_4A0F00
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F00(char *this)
{
  return this + 6132;
}



// ------------------------------------------------------------
// 0x4A0F10 sub_4A0F10
// ------------------------------------------------------------
char */*thiscall*/ sub_4A0F10(char *this)
{
  return this + 6160;
}



// ------------------------------------------------------------
// 0x4A0F20 sub_4A0F20
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F20(uint32_t *this)
{
  return *(this + 1574);
}



// ------------------------------------------------------------
// 0x4A0F30 sub_4A0F30
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F30(void *this)
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
}



// ------------------------------------------------------------
// 0x4A0F40 sub_4A0F40
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0F40(uint8_t *this)
{
  return *(this + 6552);
}



// ------------------------------------------------------------
// 0x4A0F50 sub_4A0F50
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F50(uint32_t *this, int a2)
{
  return *(this + a2 + 1557);
}



// ------------------------------------------------------------
// 0x4A0F70 sub_4A0F70
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F70(uint32_t *this, int a2)
{
  return *(this + a2 + 1617);
}



// ------------------------------------------------------------
// 0x4A0F90 sub_4A0F90
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0F90(void *this, int a2, int a3)
{
  return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, int))(*(uint32_t *)this + 808))(this, a2, 0xFFFF, 0, a3);
}



// ------------------------------------------------------------
// 0x4A0FB0 sub_4A0FB0
// ------------------------------------------------------------
char /*thiscall*/ sub_4A0FB0(uint8_t *this, char a2)
{
  *(this + 6740) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4A0FC0 sub_4A0FC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FC0(void *this, int a2, char a3)
{
  int result; // eax

  result = sub_4E8080(a2, a3);
  if ( a3 != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x4A0FF0 sub_4A0FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A0FF0(void *this, int a2)
{
  sub_4E7040(a2);
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
}



// ------------------------------------------------------------
// 0x4A1010 sub_4A1010
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1010(uint32_t *this)
{
  return *(this + 1639);
}



// ------------------------------------------------------------
// 0x4A1020 sub_4A1020
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1020(char *this)
{
  return this + 6560;
}



// ------------------------------------------------------------
// 0x4A1030 sub_4A1030
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1030(uint32_t *this, char a2)
{
  int result; // eax

  result = (a2 != 0) - 1;
  *(this + 1686) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4A1050 sub_4A1050
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1050(uint32_t *this)
{
  return *(this + 1686) != -1;
}



// ------------------------------------------------------------
// 0x4A10D0 sub_4A10D0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A10D0(void *this)
{
  return (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 724))(this) == 0
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 3) == 0
      && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 8) == 0;
}



// ------------------------------------------------------------
// 0x4A1110 sub_4A1110
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1110(uint32_t *this)
{
  *(this + 1774) = -1;
}



// ------------------------------------------------------------
// 0x4A1120 sub_4A1120
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A1120(uint32_t *this)
{
  return *(this + 1774) != -1;
}



// ------------------------------------------------------------
// 0x4A1130 sub_4A1130
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1130(uint32_t *this)
{
  if ( *(this + 1774) == -1 )
    return 0;
  else
    return sub_699000((int)(this + 9)) - *(this + 1774);
}



// ------------------------------------------------------------
// 0x4A1150 sub_4A1150
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1150(char *this)
{
  return this + 7232;
}



// ------------------------------------------------------------
// 0x4A1160 sub_4A1160
// ------------------------------------------------------------
char */*thiscall*/ sub_4A1160(char *this)
{
  return this + 7520;
}



// ------------------------------------------------------------
// 0x4A1170 sub_4A1170
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1170(uint32_t *this)
{
  return *(this + 1815);
}



// ------------------------------------------------------------
// 0x4A1180 sub_4A1180
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1180(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 2090);
  if ( v1 != 0 )
    return *(uint8_t *)(v1 + 2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11A0 sub_4A11A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A11A0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 2090);
  if ( v1 != 0 )
    return *(uint32_t *)(v1 + 3);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A11C0 sub_4A11C0
// ------------------------------------------------------------
int16_t /*stdcall*/ sub_4A11C0(int16_t a1)
{
  return a1;
}



// ------------------------------------------------------------
// 0x4A11D0 sub_4A11D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A11D0(void *Block, char a2)
{
  sub_4A1200();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A1200 sub_4A1200
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1200(uint32_t *this)
{
  *this = &CNGhoulOilSellerOlrek::`vftable';
  return sub_58E0D0();
}



// ------------------------------------------------------------
// 0x4A1210 sub_4A1210
// ------------------------------------------------------------
int /*fastcall*/ sub_4A1210(uint32_t *a1, int a2)
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

  *a1 = 0;
  sub_41A590((unsigned int)(a1 + 1), a2, 0);
  sub_41A590((unsigned int)a1 + 18, v3, 1065353216);
  sub_41A590((unsigned int)(a1 + 8), v4, 0);
  sub_41A590((unsigned int)a1 + 46, v5, 1065353216);
  sub_41A590((unsigned int)(a1 + 15), v6, 0);
  sub_41A590((unsigned int)a1 + 74, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 22), v7, 0);
  sub_41A590((unsigned int)a1 + 102, v8, 1065353216);
  sub_41A590((unsigned int)(a1 + 29), v9, 0);
  sub_41A590((unsigned int)a1 + 130, v10, 1065353216);
  sub_41A590((unsigned int)(a1 + 36), v11, 0);
  sub_41A590((unsigned int)a1 + 158, 1065353216, 1065353216);
  v13 = (unsigned int)(a1 + 57);
  for ( i = 4; i != 0; --i )
  {
    sub_41A590(v13 - 56, v12, 0);
    sub_41A590(v13, v15, 1065353216);
    v13 += 14;
  }
  v16 = (unsigned int)(a1 + 127);
  for ( j = 16; j != 0; --j )
  {
    sub_41A590(v16 - 224, v12, 0);
    sub_41A590(v16, v18, 1065353216);
    v16 += 14;
  }
  sub_41A590((unsigned int)(a1 + 183), v12, 0);
  sub_41A590((unsigned int)a1 + 746, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 190), v19, 0);
  sub_41A590((unsigned int)a1 + 774, v20, 1065353216);
  sub_41A590((unsigned int)(a1 + 197), v21, 0);
  sub_41A590((unsigned int)a1 + 802, v22, 1065353216);
  sub_41A590((unsigned int)(a1 + 204), v23, 1000);
  sub_41A590((unsigned int)a1 + 830, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 211), v24, 1000);
  sub_41A590((unsigned int)a1 + 858, v25, 1065353216);
  sub_41A590((unsigned int)(a1 + 218), v26, 1000);
  sub_41A590((unsigned int)a1 + 886, v27, 1065353216);
  sub_41A590((unsigned int)(a1 + 225), v28, 0);
  sub_41A590((unsigned int)a1 + 914, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 232), v29, 0);
  sub_41A590((unsigned int)a1 + 942, v30, 1065353216);
  sub_41A590((unsigned int)(a1 + 239), v31, 100);
  sub_41A590((unsigned int)a1 + 970, v32, 1065353216);
  sub_41A590((unsigned int)(a1 + 246), v33, 0);
  sub_41A590((unsigned int)a1 + 998, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 253), v34, 0);
  sub_41A590((unsigned int)a1 + 1026, v35, 1065353216);
  sub_41A590((unsigned int)(a1 + 260), v36, 0);
  sub_41A590((unsigned int)a1 + 1054, v37, 1065353216);
  sub_41A590((unsigned int)(a1 + 267), v38, 0);
  sub_41A590((unsigned int)a1 + 1082, 1065353216, 1065353216);
  sub_41A590((unsigned int)(a1 + 274), v39, 0);
  sub_41A590((unsigned int)a1 + 1110, v40, 1065353216);
  sub_41A590((unsigned int)(a1 + 281), v41, 0);
  sub_41A590((unsigned int)a1 + 1138, v42, 0);
  sub_41A590((unsigned int)(a1 + 288), v43, 0);
  sub_41A590((unsigned int)a1 + 1166, v44, 0);
  sub_41A590((unsigned int)(a1 + 295), v45, 0);
  sub_41A590((unsigned int)a1 + 1194, 0, 0);
  sub_41A590((unsigned int)(a1 + 302), v46, 0);
  sub_41A590((unsigned int)a1 + 1222, v47, 0);
  sub_41A590((unsigned int)(a1 + 309), 0, 0);
  sub_41A590((unsigned int)a1 + 1250, v48, 0);
  sub_41A590((unsigned int)(a1 + 316), v49, 0);
  sub_41A590((unsigned int)a1 + 1278, 0, 0);
  sub_41A590((unsigned int)(a1 + 323), v50, 1065353216);
  sub_41A590((unsigned int)a1 + 1306, v51, 0);
  sub_41A590((unsigned int)(a1 + 330), v52, 0);
  sub_41A590((unsigned int)a1 + 1334, v53, 0);
  return sub_41A590((unsigned int)(a1 + 337), v54, 0);
}


// ------------------------------------------------------------
// 0x4A1670 sub_4A1670
// ------------------------------------------------------------
void /*thiscall*/ sub_4A1670(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // edx

  v2 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *v2 = &clong::`vftable';
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



// ------------------------------------------------------------
// 0x4A1CA0 sub_4A1CA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1CA0(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 60);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 74)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1CE0 sub_4A1CE0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1CE0(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 1012);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 1026)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1D20 sub_4A1D20
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D20(void *this)
{
  int v1; // eax

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(v1 + 1306);
}



// ------------------------------------------------------------
// 0x4A1D40 sub_4A1D40
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1D40(void *this)
{
  int v1; // eax

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(v1 + 1124);
}



// ------------------------------------------------------------
// 0x4A1D60 sub_4A1D60
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1D60(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 116);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 130)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1DA0 sub_4A1DA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1DA0(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 1068);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 1082)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1DE0 sub_4A1DE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1DE0(void *this)
{
  int v1; // eax

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(v1 + 1334);
}



// ------------------------------------------------------------
// 0x4A1E00 sub_4A1E00
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E00(void *this)
{
  int v1; // eax

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  return sub_41A5E0(v1 + 1166);
}



// ------------------------------------------------------------
// 0x4A1E20 sub_4A1E20
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1E20(void *this)
{
  return sub_41A5E0((unsigned int)this + 6132);
}



// ------------------------------------------------------------
// 0x4A1E30 sub_4A1E30
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1E30(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 4);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 18)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1E70 sub_4A1E70
// ------------------------------------------------------------
char /*fastcall*/ sub_4A1E70(int a1, int a2, int a3, char a4)
{
  char result; // al

  sub_41A590(a1 + 6146, a2, a3);
  result = a4;
  if ( a4 != 0 )
    *(uint32_t *)(a1 + 6604) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4A1EB0 sub_4A1EB0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4A1EB0(void *this)
{
  int v1; // esi
  int v3; // [esp+4h] [ebp-4h]

  v1 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v3 = sub_41A5E0(v1 + 32);
  return (uint64_t)(sub_43B5A0((void *)(v1 + 46)) * (double)v3);
}



// ------------------------------------------------------------
// 0x4A1EF0 sub_4A1EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A1EF0(void *this)
{
  return sub_41A5E0((unsigned int)this + 7028);
}



// ------------------------------------------------------------
// 0x4A1F00 sub_4A1F00
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



// ------------------------------------------------------------
// 0x4A22E0 sub_4A22E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4A22E0(uint32_t *this)
{
  sub_41A580((uint32_t *)((char *)this + 14));
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x4A2330 sub_4A2330
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2330(int this, char ArgList, int a3, char a4)
{
  sub_58DFE0((uint8_t *)this, ArgList, a3, a4);
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
  sub_58C6B0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A23D0 sub_4A23D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A23D0(void *Block, char a2)
{
  sub_4A2400();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A2400 sub_4A2400
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
// 0x4A2460 sub_4A2460
// ------------------------------------------------------------
int /*stdcall*/ sub_4A2460(int a1, int a2)
{
  return sub_4A2480(a2);
}



// ------------------------------------------------------------
// 0x4A2480 sub_4A2480
// ------------------------------------------------------------
char */*thiscall*/ sub_4A2480(char *this, char *a2)
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
  unsigned int v99; // [esp+1Ch] [ebp+8h]
  unsigned int v100; // [esp+1Ch] [ebp+8h]
  unsigned int v101; // [esp+1Ch] [ebp+8h]
  unsigned int v102; // [esp+1Ch] [ebp+8h]
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

  *(uint32_t *)this = *(uint32_t *)a2;
  v4 = sub_41A5E0((unsigned int)(a2 + 4));
  sub_41A590((unsigned int)(this + 4), v5, v4);
  *(float *)&v93 = sub_43B5A0(a2 + 18);
  sub_41A590((unsigned int)(this + 18), v6, v93);
  v7 = sub_41A5E0((unsigned int)(a2 + 32));
  sub_41A590((unsigned int)(this + 32), v8, v7);
  *(float *)&v94 = sub_43B5A0(a2 + 46);
  sub_41A590((unsigned int)(this + 46), v94, v94);
  v9 = sub_41A5E0((unsigned int)(a2 + 60));
  sub_41A590((unsigned int)(this + 60), v10, v9);
  *(float *)&v95 = sub_43B5A0(a2 + 74);
  sub_41A590((unsigned int)(this + 74), v11, v95);
  v12 = sub_41A5E0((unsigned int)(a2 + 88));
  sub_41A590((unsigned int)(this + 88), v13, v12);
  *(float *)&v96 = sub_43B5A0(a2 + 102);
  sub_41A590((unsigned int)(this + 102), v14, v96);
  v15 = sub_41A5E0((unsigned int)(a2 + 116));
  sub_41A590((unsigned int)(this + 116), v16, v15);
  *(float *)&v97 = sub_43B5A0(a2 + 130);
  sub_41A590((unsigned int)(this + 130), v97, v97);
  v17 = sub_41A5E0((unsigned int)(a2 + 144));
  sub_41A590((unsigned int)(this + 144), v18, v17);
  *(float *)&v98 = sub_43B5A0(a2 + 158);
  sub_41A590((unsigned int)(this + 158), v19, v98);
  v99 = (unsigned int)(this + 172);
  v20 = a2 - this;
  v89 = 4;
  do
  {
    v21 = sub_41A5E0(v20 + v99);
    sub_41A590(v99, v22, v21);
    v23 = v89 == 1;
    v99 += 14;
    --v89;
  }
  while ( !v23 );
  v100 = (unsigned int)(this + 228);
  v90 = 4;
  do
  {
    *(float *)&v87 = sub_43B5A0((void *)(v20 + v100));
    sub_41A590(v100, v87, v87);
    v23 = v90 == 1;
    v100 += 14;
    --v90;
  }
  while ( !v23 );
  v101 = (unsigned int)(this + 284);
  v91 = 16;
  do
  {
    v24 = sub_41A5E0(v20 + v101);
    sub_41A590(v101, v25, v24);
    v23 = v91 == 1;
    v101 += 14;
    --v91;
  }
  while ( !v23 );
  v102 = (unsigned int)(this + 508);
  v92 = 16;
  do
  {
    *(float *)&v88 = sub_43B5A0((void *)(v20 + v102));
    sub_41A590(v102, v26, v88);
    v23 = v92 == 1;
    v102 += 14;
    --v92;
  }
  while ( !v23 );
  v27 = sub_41A5E0((unsigned int)(a2 + 732));
  sub_41A590((unsigned int)(this + 732), v28, v27);
  *(float *)&v103 = sub_43B5A0(a2 + 746);
  sub_41A590((unsigned int)(this + 746), v103, v103);
  v29 = sub_41A5E0((unsigned int)(a2 + 760));
  sub_41A590((unsigned int)(this + 760), v30, v29);
  *(float *)&v104 = sub_43B5A0(a2 + 774);
  sub_41A590((unsigned int)(this + 774), v31, v104);
  v32 = sub_41A5E0((unsigned int)(a2 + 788));
  sub_41A590((unsigned int)(this + 788), v33, v32);
  *(float *)&v105 = sub_43B5A0(a2 + 802);
  sub_41A590((unsigned int)(this + 802), v34, v105);
  v35 = sub_41A5E0((unsigned int)(a2 + 816));
  sub_41A590((unsigned int)(this + 816), v36, v35);
  *(float *)&v106 = sub_43B5A0(a2 + 830);
  sub_41A590((unsigned int)(this + 830), v106, v106);
  v37 = sub_41A5E0((unsigned int)(a2 + 844));
  sub_41A590((unsigned int)(this + 844), v38, v37);
  *(float *)&v107 = sub_43B5A0(a2 + 858);
  sub_41A590((unsigned int)(this + 858), v39, v107);
  v40 = sub_41A5E0((unsigned int)(a2 + 872));
  sub_41A590((unsigned int)(this + 872), v41, v40);
  *(float *)&v108 = sub_43B5A0(a2 + 886);
  sub_41A590((unsigned int)(this + 886), v42, v108);
  v43 = sub_41A5E0((unsigned int)(a2 + 900));
  sub_41A590((unsigned int)(this + 900), v44, v43);
  *(float *)&v109 = sub_43B5A0(a2 + 914);
  sub_41A590((unsigned int)(this + 914), v109, v109);
  v45 = sub_41A5E0((unsigned int)(a2 + 928));
  sub_41A590((unsigned int)(this + 928), v46, v45);
  *(float *)&v110 = sub_43B5A0(a2 + 942);
  sub_41A590((unsigned int)(this + 942), v47, v110);
  v48 = sub_41A5E0((unsigned int)(a2 + 956));
  sub_41A590((unsigned int)(this + 956), v49, v48);
  *(float *)&v111 = sub_43B5A0(a2 + 970);
  sub_41A590((unsigned int)(this + 970), v50, v111);
  v51 = sub_41A5E0((unsigned int)(a2 + 984));
  sub_41A590((unsigned int)(this + 984), v52, v51);
  *(float *)&v112 = sub_43B5A0(a2 + 998);
  sub_41A590((unsigned int)(this + 998), v112, v112);
  v53 = sub_41A5E0((unsigned int)(a2 + 1012));
  sub_41A590((unsigned int)(this + 1012), v54, v53);
  *(float *)&v113 = sub_43B5A0(a2 + 1026);
  sub_41A590((unsigned int)(this + 1026), v55, v113);
  v56 = sub_41A5E0((unsigned int)(a2 + 1040));
  sub_41A590((unsigned int)(this + 1040), v57, v56);
  *(float *)&v114 = sub_43B5A0(a2 + 1054);
  sub_41A590((unsigned int)(this + 1054), v58, v114);
  v59 = sub_41A5E0((unsigned int)(a2 + 1068));
  sub_41A590((unsigned int)(this + 1068), v60, v59);
  *(float *)&v115 = sub_43B5A0(a2 + 1082);
  sub_41A590((unsigned int)(this + 1082), v115, v115);
  v61 = sub_41A5E0((unsigned int)(a2 + 1096));
  sub_41A590((unsigned int)(this + 1096), v62, v61);
  *(float *)&v116 = sub_43B5A0(a2 + 1110);
  sub_41A590((unsigned int)(this + 1110), v63, v116);
  v64 = sub_41A5E0((unsigned int)(a2 + 1124));
  sub_41A590((unsigned int)(this + 1124), v65, v64);
  v66 = sub_41A5E0((unsigned int)(a2 + 1138));
  sub_41A590((unsigned int)(this + 1138), v67, v66);
  *(float *)&v117 = sub_43B5A0(a2 + 1152);
  sub_41A590((unsigned int)(this + 1152), v68, v117);
  v69 = sub_41A5E0((unsigned int)(a2 + 1166));
  sub_41A590((unsigned int)(this + 1166), v70, v69);
  v71 = sub_41A5E0((unsigned int)(a2 + 1180));
  sub_41A590((unsigned int)(this + 1180), v72, v71);
  *(float *)&v118 = sub_43B5A0(a2 + 1194);
  sub_41A590((unsigned int)(this + 1194), v118, v118);
  *(float *)&v119 = sub_43B5A0(a2 + 1208);
  sub_41A590((unsigned int)(this + 1208), v73, v119);
  *(float *)&v120 = sub_43B5A0(a2 + 1222);
  sub_41A590((unsigned int)(this + 1222), v74, v120);
  *(float *)&v121 = sub_43B5A0(a2 + 1236);
  sub_41A590((unsigned int)(this + 1236), v121, v121);
  *(float *)&v122 = sub_43B5A0(a2 + 1250);
  sub_41A590((unsigned int)(this + 1250), v75, v122);
  *(float *)&v123 = sub_43B5A0(a2 + 1264);
  sub_41A590((unsigned int)(this + 1264), v76, v123);
  *(float *)&v124 = sub_43B5A0(a2 + 1278);
  sub_41A590((unsigned int)(this + 1278), v124, v124);
  *(float *)&v125 = sub_43B5A0(a2 + 1292);
  sub_41A590((unsigned int)(this + 1292), v77, v125);
  v78 = sub_41A5E0((unsigned int)(a2 + 1306));
  sub_41A590((unsigned int)(this + 1306), v79, v78);
  v80 = sub_41A5E0((unsigned int)(a2 + 1320));
  sub_41A590((unsigned int)(this + 1320), v81, v80);
  v82 = sub_41A5E0((unsigned int)(a2 + 1334));
  sub_41A590((unsigned int)(this + 1334), v83, v82);
  v84 = sub_41A5E0((unsigned int)(a2 + 1348));
  sub_41A590((unsigned int)(this + 1348), v85, v84);
  return this;
}


// ------------------------------------------------------------
// 0x4A2B30 sub_4A2B30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A2B30(void *this, unsigned int a2)
{
  unsigned int v2; // esi
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = (unsigned int)this + 6132;
  v3 = sub_41A5E0(a2);
  sub_41A590(v2, v4, v3);
  v5 = sub_41A5E0(a2 + 14);
  sub_41A590(v2 + 14, v6, v5);
  return v2;
}



// ------------------------------------------------------------
// 0x4A2B80 sub_4A2B80
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4A2B80(uint8_t *this)
{
  return (uint8_t)sub_4A2BB0() != 0 && *(this + 7093) == 0;
}



// ------------------------------------------------------------
// 0x4A2BB0 sub_4A2BB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2BB0(int *this)
{
  uint32_t *v2; // esi
  int v3; // eax
  int v4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 608))(this) == 0 )
    return 0;
  v2 = (uint32_t *)*(this + 30);
  if ( v2 == nullptr )
    return 0;
  if ( v2[37] == -1 )
    sub_4938F0(*(this + 30));
  if ( (v3 = v2[34]) != 0
    && (v2[35] - v3) / 24 != 0
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
int /*thiscall*/ sub_4A2C40(int *this)
{
  int v1; // esi

  v1 = *(this + 30);
  if ( v1 == 0 )
    return 0;
  if ( *(uint32_t *)(v1 + 148) == -1 )
    sub_4938F0(*(this + 30));
  return *(uint32_t *)(v1 + 112);
}



// ------------------------------------------------------------
// 0x4A2C70 sub_4A2C70
// ------------------------------------------------------------
char /*stdcall*/ sub_4A2C70(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4A2C70(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2CB0 sub_4A2CB0
// ------------------------------------------------------------
char /*stdcall*/ sub_4A2CB0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4A2CB0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2CF0 sub_4A2CF0
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
// 0x4A2D30 sub_4A2D30
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2D30(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 87);
  if ( v2 != 0 && a2 < (*(this + 88) - v2) >> 2 )
    return *(uint32_t *)(*(this + 87) + 4 * a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4A2D70 sub_4A2D70
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A2D70(int this, int a2)
{
  int v3; // ecx
  unsigned int result; // eax
  unsigned int i; // edi
  int v6; // ecx

  *(uint8_t *)(this + 641) = a2;
  v3 = *(uint32_t *)(this + 7076);
  if ( v3 != 0 )
  {
    result = (*(uint32_t *)(this + 7080) - v3) >> 2;
    if ( result != 0 )
    {
      for ( i = 0; ; ++i )
      {
        v6 = *(uint32_t *)(this + 7076);
        if ( v6 == 0 )
          break;
        result = (*(uint32_t *)(this + 7080) - v6) >> 2;
        if ( i >= result )
          break;
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v6 + 4 * i) + 604))(*(uint32_t *)(v6 + 4 * i), a2);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A2DE0 sub_4A2DE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A2DE0(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax
  uint32_t *result; // eax

  v2 = this + 135;
  sub_4A2C70(*(void ***)(*(this + 136) + 4));
  *(uint32_t *)(v2[1] + 4) = v2[1];
  v3 = (uint32_t *)v2[1];
  v2[2] = 0;
  *v3 = v3;
  *(uint32_t *)(v2[1] + 8) = v2[1];
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
uint32_t */*thiscall*/ sub_4A2EE0(char *this)
{
  char *v1; // esi
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
  v1 = this + 84;
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
  *(uint32_t *)(*((uint32_t *)v1 + 1) + 4) = *((uint32_t *)v1 + 1);
  result = *((uint32_t **)v1 + 1);
  *((uint32_t *)v1 + 2) = 0;
  *result = result;
  *(uint32_t *)(*((uint32_t *)v1 + 1) + 8) = *((uint32_t *)v1 + 1);
  return result;
}



// ------------------------------------------------------------
// 0x4A2F80 sub_4A2F80
// ------------------------------------------------------------
int /*thiscall*/ sub_4A2F80(uint32_t *this, const char *a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // ebx
  bool v4; // zf
  uint32_t *v7; // [esp+10h] [ebp-4h] BYREF

  v2 = (uint32_t *)*(this + 1);
  v3 = (uint32_t *)*v2;
  v4 = *v2 == (uint32_t)v2;
  v7 = (uint32_t *)*v2;
  if ( v4 )
    return -1;
  while ( sub_40BF00((std::_String_base *)(v3 + 4), 0, v3[9], a2, strlen(a2)) != 0 )
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
int /*thiscall*/ sub_4A3050(int this)
{
  uint32_t *v3; // esi

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
  v3 = (uint32_t *)(this + 280);
  *v3 = 0;
  v3[1] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4A30C0 sub_4A30C0
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4A3130 sub_4A3130
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4A3130(uint32_t *this, int ***a2, int **a3)
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
// 0x4A33F0 sub_4A33F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4A33F0(void *this)
{
  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)this + 1, szPassword, 0);
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
  result = sub_4015C0((void *)szPassword, 0);
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
char /*thiscall*/ sub_4A3570(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x15555555 )
    sub_4A30C0();
  v4 = (char *)operator new(12 * a2);
  *(this + 3) = &v4[12 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x4A35C0 sub_4A35C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4A35C0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x7FFFFFF )
    sub_4A30C0();
  v4 = (char *)operator new(32 * a2);
  *(this + 3) = &v4[32 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x4A3610 sub_4A3610
// ------------------------------------------------------------
int **/*thiscall*/ sub_4A3610(int ***this, int **a2, int *a3, int *a4)
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
    sub_4A2C70(*(void ***)(v7 + 4));
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
        sub_4A3130(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4A36D0 sub_4A36D0
// ------------------------------------------------------------
int **/*thiscall*/ sub_4A36D0(int ***this, int **a2, int *a3, int *a4)
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
    sub_4A2CB0(*(void ***)(v7 + 4));
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
        sub_4A3130(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4A3790 sub_4A3790
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
  sub_4A33F0((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4A3830 sub_4A3830
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3830(int ***this)
{
  int ***v1; // esi
  int *v3; // [esp+4h] [ebp-4h] BYREF

  v1 = this + 21;
  sub_41DA40(this + 21, &v3, **(this + 22), (int *)*(this + 22));
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4A3870 sub_4A3870
// ------------------------------------------------------------
int /*stdcall*/ sub_4A3870(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 152 )
    result = sub_4A2EB0(i);
  return result;
}



// ------------------------------------------------------------
// 0x4A38A0 sub_4A38A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A38A0(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = this + 71;
  *(this + 71) = *a2;
  sub_4014D0(this + 72, a2 + 1, 0, 0xFFFFFFFF);
  v2[8] = a2[8];
  v2[9] = a2[9];
  v2[10] = a2[10];
  sub_4ED3F0((int)(v2 + 11), (int)(a2 + 11));
  sub_4ED3F0((int)(v2 + 15), (int)(a2 + 15));
  return v2;
}



// ------------------------------------------------------------
// 0x4A3900 sub_4A3900
// ------------------------------------------------------------
void /*stdcall*/ sub_4A3900(int a1)
{
  int v1; // esi
  uint32_t *v2; // edi

  v1 = a1;
  if ( a1 != 0 )
  {
    a1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 380))(a1);
    v2 = (uint32_t *)sub_4A3940(&a1);
    *v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v1 + 380))(v1);
  }
}



// ------------------------------------------------------------
// 0x4A3940 sub_4A3940
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3940(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edi
  int v4; // eax
  uint32_t v6[2]; // [esp+8h] [ebp-8h] BYREF

  v2 = a2;
  v4 = sub_4A3990(a2);
  if ( v4 == *(this + 1) || *v2 < *(uint32_t *)(v4 + 12) )
  {
    v6[0] = *v2;
    v6[1] = 0;
    v4 = *(uint32_t *)sub_4A39C0(&a2, v4, v6);
  }
  return v4 + 16;
}



// ------------------------------------------------------------
// 0x4A3990 sub_4A3990
// ------------------------------------------------------------
int */*thiscall*/ sub_4A3990(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *a2 )
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
uint32_t */*thiscall*/ sub_4A39C0(uint32_t *this, uint32_t *a2, int a3, uint32_t *a4)
{
  int v5; // eax
  uint32_t *v7; // eax
  int v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-Ch] BYREF
  int v11; // [esp+10h] [ebp-4h] BYREF

  v5 = *(this + 2);
  v11 = 0;
  if ( v5 == 0 )
  {
    sub_4A3B90(a2, 1, *(this + 1), a4);
    return a2;
  }
  v7 = (uint32_t *)*(this + 1);
  if ( a3 == *v7 )
  {
    if ( *a4 < *(uint32_t *)(a3 + 12) )
    {
      sub_4A3B90(a2, 1, a3, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( (uint32_t *)a3 == v7 )
  {
    v8 = v7[2];
    if ( *(uint32_t *)(v8 + 12) < *a4 )
    {
      sub_4A3B90(a2, 0, v8, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= *(uint32_t *)(a3 + 12) || (v11 = a3, sub_4A3B30(&v11), *(uint32_t *)(v11 + 12) >= *a4) )
  {
    if ( *(uint32_t *)(a3 + 12) >= *a4 || (v11 = a3, sub_41C5E0(&v11), v11 != *(this + 1)) && *a4 >= *(uint32_t *)(v11 + 12) )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4A3D40(v10, a4);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(*(uint32_t *)(a3 + 8) + 21) != 0 )
      sub_4A3B90(a2, 0, a3, a4);
    else
      sub_4A3B90(a2, 1, v11, a4);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(*(uint32_t *)(v11 + 8) + 21) != 0 )
      sub_4A3B90(a2, 0, v11, a4);
    else
      sub_4A3B90(a2, 1, a3, a4);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4A3B30 sub_4A3B30
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
uint32_t */*thiscall*/ sub_4A3B90(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
{
  int v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
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
  int v22; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
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
  v6 = sub_5648C0(*(this + 1), a4, *(this + 1), a5, 0);
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
  v10 = (uint32_t *)(v6 + 4);
  v11 = v6;
  if ( *(uint8_t *)(*(uint32_t *)(v6 + 4) + 20) == 0 )
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
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_433130(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4296E0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) != 0 )
      {
        v6 = v22;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4A3D40 sub_4A3D40
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3D40(uint32_t *this, int a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v5; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = (uint32_t *)*(this + 1);
  v6 = (int *)v5[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
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
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4A3B90(this, &a3, 1, v5, (int)v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_4A3B30(&a3);
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
    v12 = *sub_4A3B90(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4A3E00 sub_4A3E00
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



// ------------------------------------------------------------
// 0x4A3E40 sub_4A3E40
// ------------------------------------------------------------
char */*thiscall*/ sub_4A3E40(char *this)
{
  char *v2; // esi
  int v3; // eax

  v2 = this + 84;
  v3 = sub_433AC0(this + 84);
  *((uint32_t *)v2 + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
  sub_4A2EE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A3EB0 sub_4A3EB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A3EB0(uint32_t *this, char *a2)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax
  int v4; // ecx
  int i; // edx
  uint32_t *v6; // eax
  int j; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = this + 1808;
  sub_4A3F80(a2);
  v2[4] = *((uint32_t *)a2 + 4);
  v2[5] = *((uint32_t *)a2 + 5);
  v2[6] = *((uint32_t *)a2 + 6);
  v2[7] = *((uint32_t *)a2 + 7);
  v2[8] = *((uint32_t *)a2 + 8);
  v2[9] = *((uint32_t *)a2 + 9);
  v2[10] = *((uint32_t *)a2 + 10);
  v2[11] = *((uint32_t *)a2 + 11);
  v2[12] = *((uint32_t *)a2 + 12);
  v2[13] = *((uint32_t *)a2 + 13);
  v2[14] = *((uint32_t *)a2 + 14);
  v2[15] = *((uint32_t *)a2 + 15);
  v2[16] = *((uint32_t *)a2 + 16);
  v2[17] = *((uint32_t *)a2 + 17);
  v3 = v2 + 18;
  v4 = a2 - (char *)v2;
  for ( i = 26; i != 0; --i )
  {
    *v3 = *(uint32_t *)((char *)v3 + v4);
    ++v3;
  }
  v6 = v2 + 44;
  for ( j = 26; j != 0; --j )
  {
    *v6 = *(uint32_t *)((char *)v6 + v4);
    ++v6;
  }
  v2[70] = *((uint32_t *)a2 + 70);
  v2[71] = *((uint32_t *)a2 + 71);
  return v2;
}



// ------------------------------------------------------------
// 0x4A3F80 sub_4A3F80
// ------------------------------------------------------------
int /*thiscall*/ sub_4A3F80(int this, int a2)
{
  int v2; // ebx
  int v4; // eax
  unsigned int v5; // edi
  uint32_t *v7; // ecx
  unsigned int v8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int v11; // edx
  unsigned int v12; // eax
  int v13; // eax
  int v14; // edx
  uint32_t *v15; // eax
  int v16; // eax
  unsigned int v17; // eax
  uint32_t *v18; // [esp+8h] [ebp-4h]
  int v19; // [esp+8h] [ebp-4h]
  int i; // [esp+14h] [ebp+8h]

  v2 = a2;
  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v18 = *(uint32_t **)(a2 + 8), (v5 = ((int)v18 - v4) / 12) == 0) )
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
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 12;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
      v12 = (*(uint32_t *)(this + 12) - (int)v7) / 12;
    else
      v12 = 0;
    if ( v5 > v12 )
    {
      if ( v7 != nullptr )
        j__free(*(void **)(this + 4));
      v17 = *(uint32_t *)(a2 + 4);
      if ( v17 != 0 )
        v17 = (int)(*(uint32_t *)(a2 + 8) - v17) / 12;
      if ( sub_4A3570((uint32_t *)this, v17) == 0 )
        return this;
      v16 = sub_59EE30(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    }
    else
    {
      if ( v7 != nullptr )
        v13 = (*(uint32_t *)(this + 8) - (int)v7) / 12;
      else
        v13 = 0;
      v14 = *(uint32_t *)(a2 + 4) + 12 * v13;
      v15 = *(uint32_t **)(a2 + 4);
      v19 = *(uint32_t *)(this + 4);
      if ( v15 != (uint32_t *)v14 )
      {
        do
        {
          *v7 = *v15;
          v7[1] = v15[1];
          v7[2] = v15[2];
          v7 = (uint32_t *)(v19 + 12);
          v15 += 3;
          v19 += 12;
        }
        while ( v15 != (uint32_t *)v14 );
        v2 = a2;
      }
      v16 = sub_59EE30(v14, *(uint32_t *)(v2 + 8), *(uint32_t *)(this + 8));
    }
    *(uint32_t *)(this + 8) = v16;
    return this;
  }
  v9 = *(uint32_t **)(a2 + 4);
  for ( i = *(uint32_t *)(this + 4); v9 != v18; i += 12 )
  {
    *v7 = *v9;
    v7[1] = v9[1];
    v7[2] = v9[2];
    v7 = (uint32_t *)(i + 12);
    v9 += 3;
  }
  v10 = *(uint32_t *)(v2 + 4);
  if ( v10 != 0 )
    v11 = *(uint32_t *)(this + 4) + 12 * ((*(uint32_t *)(v2 + 8) - v10) / 12);
  else
    v11 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = v11;
  return this;
}



// ------------------------------------------------------------
// 0x4A4170 sub_4A4170
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4170(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 152 )
      sub_4A2EB0(v2);
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
int /*thiscall*/ sub_4A41C0(int this, int a2)
{
  int v2; // esi
  uint8_t *v3; // ecx
  int i; // edx
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = this + 7520;
  *(uint32_t *)(this + 7520) = *(uint32_t *)a2;
  *(uint32_t *)(this + 7524) = *(uint32_t *)(a2 + 4);
  *(uint8_t *)(this + 7528) = *(uint8_t *)(a2 + 8);
  *(uint8_t *)(this + 7529) = *(uint8_t *)(a2 + 9);
  *(uint8_t *)(this + 7530) = *(uint8_t *)(a2 + 10);
  *(uint8_t *)(this + 7531) = *(uint8_t *)(a2 + 11);
  *(uint8_t *)(this + 7532) = *(uint8_t *)(a2 + 12);
  *(uint8_t *)(this + 7533) = *(uint8_t *)(a2 + 13);
  *(uint8_t *)(this + 7534) = *(uint8_t *)(a2 + 14);
  *(uint8_t *)(this + 7535) = *(uint8_t *)(a2 + 15);
  *(uint8_t *)(this + 7536) = *(uint8_t *)(a2 + 16);
  *(uint8_t *)(this + 7537) = *(uint8_t *)(a2 + 17);
  *(uint8_t *)(this + 7538) = *(uint8_t *)(a2 + 18);
  v3 = (uint8_t *)(this + 7539);
  for ( i = 17; i != 0; --i )
  {
    *v3 = v3[a2 - v2];
    ++v3;
  }
  *(uint8_t *)(v2 + 36) = *(uint8_t *)(a2 + 36);
  *(uint8_t *)(v2 + 37) = *(uint8_t *)(a2 + 37);
  *(uint8_t *)(v2 + 38) = *(uint8_t *)(a2 + 38);
  *(uint8_t *)(v2 + 39) = *(uint8_t *)(a2 + 39);
  *(uint32_t *)(v2 + 40) = *(uint32_t *)(a2 + 40);
  *(uint32_t *)(v2 + 44) = *(uint32_t *)(a2 + 44);
  *(uint32_t *)(v2 + 48) = *(uint32_t *)(a2 + 48);
  *(uint32_t *)(v2 + 52) = *(uint32_t *)(a2 + 52);
  *(uint32_t *)(v2 + 56) = *(uint32_t *)(a2 + 56);
  *(uint32_t *)(v2 + 60) = *(uint32_t *)(a2 + 60);
  *(uint32_t *)(v2 + 64) = *(uint32_t *)(a2 + 64);
  *(uint32_t *)(v2 + 68) = *(uint32_t *)(a2 + 68);
  *(uint32_t *)(v2 + 72) = *(uint32_t *)(a2 + 72);
  *(uint32_t *)(v2 + 76) = *(uint32_t *)(a2 + 76);
  *(uint32_t *)(v2 + 80) = *(uint32_t *)(a2 + 80);
  sub_4A42B0(a2 + 84);
  return v2;
}



// ------------------------------------------------------------
// 0x4A42B0 sub_4A42B0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4A42B0(int ***this, int ***a2)
{
  int ***v2; // edi

  v2 = a2;
  if ( this != a2 )
  {
    sub_41DA40(this, (int **)&a2, **(this + 1), (int *)*(this + 1));
    sub_4A42E0(v2);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4A42E0 sub_4A42E0
// ------------------------------------------------------------
int */*thiscall*/ sub_4A42E0(int ***this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = (int)*(this + 1);
  *(uint32_t *)(v3 + 4) = sub_4A4370(*(uint32_t *)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(this + 2) = *(int ***)(a2 + 8);
  v4 = *(this + 1);
  result = v4[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *v4 = (int *)v4;
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
    *v4 = result;
    v7 = (int)*(this + 1);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4A4370 sub_4A4370
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4370(void **this, int *a2, int a3)
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
    *v4 = sub_4A4370(v6, v4);
    v4[2] = sub_4A4370(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x4A4430 sub_4A4430
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A4430(uint32_t *this)
{
  int v2; // eax
  int v3; // eax

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
  v2 = sub_433AC0(this + 135);
  *(this + 136) = v2;
  *(uint8_t *)(v2 + 21) = 1;
  *(uint32_t *)(*(this + 136) + 4) = *(this + 136);
  *(uint32_t *)*(this + 136) = *(this + 136);
  *(uint32_t *)(*(this + 136) + 8) = *(this + 136);
  *(this + 137) = 0;
  *(this + 139) = 0;
  *(this + 140) = 0;
  *(this + 141) = 0;
  v3 = sub_433AC0(this + 149);
  *(this + 150) = v3;
  *(uint8_t *)(v3 + 21) = 1;
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
// 0x4A4560 sub_4A4560
// ------------------------------------------------------------
char /*thiscall*/ sub_4A4560(uint8_t *this, char a2)
{
  *(this + 641) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4A4570 sub_4A4570
// ------------------------------------------------------------
int /*stdcall*/ sub_4A4570(uint32_t *a1, int a2)
{
  *a1 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x4A4590 sub_4A4590
// ------------------------------------------------------------
int /*thiscall*/ sub_4A4590(int this)
{
  int *v3; // [esp-Ch] [ebp-28h]
  int *v4; // [esp-Ch] [ebp-28h]
  int *v5; // [esp-8h] [ebp-24h]
  int *v6; // [esp-8h] [ebp-24h]
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
  v5 = *(int **)(this + 600);
  v3 = (int *)*v5;
  LOBYTE(v8) = 5;
  sub_4A36D0((int ***)(this + 596), v7, v3, v5);
  j__free(*(void **)(this + 600));
  *(uint32_t *)(this + 600) = 0;
  *(uint32_t *)(this + 604) = 0;
  sub_4A4170((int *)(this + 552));
  v6 = *(int **)(this + 544);
  v4 = (int *)*v6;
  LOBYTE(v8) = 3;
  sub_4A3610((int ***)(this + 540), v7, v4, v6);
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
// 0x4A4710 sub_4A4710
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4710(void *Block, char a2)
{
  sub_4A4590((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A4740 sub_4A4740
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4A4740(int this)
{
  void **v2; // edi
  void **v3; // edi
  void **v4; // edi
  void ***v5; // edi
  void **v6; // ebx
  unsigned int result; // eax
  int v8; // edi
  unsigned int v9; // ebx
  void **v10; // edi
  void **v11; // edi
  void **v12; // edi
  int v13; // ecx
  void **v14; // ecx
  unsigned int i; // ebx
  int v16; // ecx
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
  v3 = *(void ***)(this + 4);
  *(uint32_t *)this = 0;
  if ( v3 != nullptr )
  {
    sub_42AF90(v3);
    sub_657740(v3, 228);
  }
  v4 = *(void ***)(this + 8);
  *(uint32_t *)(this + 4) = 0;
  if ( v4 != nullptr )
  {
    sub_42AF90(v4);
    sub_657740(v4, 228);
  }
  *(uint32_t *)(this + 8) = 0;
  v5 = (void ***)(this + 12);
  v18 = 2;
  do
  {
    v6 = *v5;
    if ( *v5 != nullptr )
    {
      sub_42AF90(*v5);
      sub_657740(v6, 228);
    }
    *v5++ = nullptr;
    result = v18 - 1;
    v18 = result;
  }
  while ( result != 0 );
  v8 = *(uint32_t *)(this + 20);
  v9 = 0;
  if ( v8 != 0 )
  {
    sub_42AF90(*(void ***)(this + 20));
    result = sub_657740(v8, 228);
  }
  v10 = *(void ***)(this + 24);
  *(uint32_t *)(this + 20) = 0;
  if ( v10 != nullptr )
  {
    sub_42AF90(v10);
    result = sub_657740(v10, 228);
  }
  v11 = *(void ***)(this + 28);
  *(uint32_t *)(this + 24) = 0;
  if ( v11 != nullptr )
  {
    sub_42AF90(v11);
    result = sub_657740(v11, 228);
  }
  v12 = *(void ***)(this + 32);
  *(uint32_t *)(this + 28) = 0;
  if ( v12 != nullptr )
  {
    sub_42AF90(v12);
    result = sub_657740(v12, 228);
  }
  *(uint32_t *)(this + 32) = 0;
  while ( 1 )
  {
    v13 = *(uint32_t *)(this + 40);
    if ( v13 == 0 )
      break;
    result = (*(uint32_t *)(this + 44) - v13) >> 2;
    if ( v9 >= result )
      break;
    v14 = *(void ***)(v13 + 4 * v9);
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
    v16 = *(uint32_t *)(this + 56);
    if ( v16 == 0 )
      break;
    result = (*(uint32_t *)(this + 60) - v16) >> 2;
    if ( i >= result )
      break;
    v17 = *(void ***)(v16 + 4 * i);
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



// ------------------------------------------------------------
// 0x4A49B0 sub_4A49B0
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
// 0x4A4E70 sub_4A4E70
// ------------------------------------------------------------
void */*thiscall*/ sub_4A4E70(void *Block, char a2)
{
  sub_4A4BD0((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A4EA0 sub_4A4EA0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A4EA0(char *this, char ArgList, int a3)
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
  sub_4A3E40(this + 7520);
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
  sub_4DB410(ArgList, a3);
  return this;
}



// ------------------------------------------------------------
// 0x4A50F0 sub_4A50F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A50F0(int this)
{
  int *v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-4h] [ebp-24h]
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
  v4 = *(int **)(this + 7608);
  v3 = (int *)*v4;
  LOBYTE(v6) = 3;
  sub_41DA40((int ***)(this + 7604), v5, v3, v4);
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
void */*thiscall*/ sub_4A5350(void *Block, char a2)
{
  sub_4A50F0((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5380 sub_4A5380
// ------------------------------------------------------------
char */*thiscall*/ sub_4A5380(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNFighterIllusion::`vftable';
  sub_5908C0(this);
  sub_5908E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A53E0 sub_4A53E0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A53E0(void *Block, char a2)
{
  sub_4A5410();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5410 sub_4A5410
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
char */*thiscall*/ sub_4A5460(char *this, char ArgList, int a3, int a4)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNProvocationDoll::`vftable';
  sub_590E70(this);
  sub_590F30(a4);
  return this;
}



// ------------------------------------------------------------
// 0x4A54C0 sub_4A54C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A54C0(void *Block, char a2)
{
  sub_4A54F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A54F0 sub_4A54F0
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
char */*thiscall*/ sub_4A5540(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNKeraha::`vftable';
  sub_5913F0(this);
  sub_592650(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A55A0 sub_4A55A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A55A0(void *Block, char a2)
{
  sub_4A55D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A55D0 sub_4A55D0
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
char */*thiscall*/ sub_4A5620(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNVinoshu::`vftable';
  sub_5928E0(this);
  sub_593FF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5680 sub_4A5680
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5680(void *Block, char a2)
{
  sub_4A56B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A56B0 sub_4A56B0
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
char */*thiscall*/ sub_4A5700(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNLuis::`vftable';
  sub_592BF0(this);
  sub_593680(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5760 sub_4A5760
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5760(void *Block, char a2)
{
  sub_4A5790();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5790 sub_4A5790
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
char */*thiscall*/ sub_4A57E0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNLugaru::`vftable';
  sub_594340(this);
  sub_594B10(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5840 sub_4A5840
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
uint32_t */*thiscall*/ sub_4A5890(uint32_t *Block, char a2)
{
  sub_4A5840(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A58C0 sub_4A58C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A58C0(int this, char ArgList, int a3)
{
  sub_4A57E0((char *)this, ArgList, a3);
  *(uint32_t *)this = &CNGardener_Ral::`vftable';
  *(uint32_t *)(this + 8632) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A58F0 sub_4A58F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A58F0(int *this, int a2, int a3, int a4)
{
  int v5; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (int)sub_445870(88771231, 100) < 10 )
  {
    v5 = *(this + 2158);
    *(this + 2158) = v5 + 1;
    if ( v5 < 3 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
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
  return sub_4DA3B0(a2, a3, a4);
}



// ------------------------------------------------------------
// 0x4A59B0 sub_4A59B0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A59B0(void *Block, char a2)
{
  sub_4A59E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A59E0 sub_4A59E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A59E0(uint32_t *this)
{
  *this = &CNGardener_Ral::`vftable';
  return sub_4A5840(this);
}



// ------------------------------------------------------------
// 0x4A59F0 sub_4A59F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A59F0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNBlackLugaru::`vftable';
  sub_594F90(this);
  sub_595470(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5A50 sub_4A5A50
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5A50(void *Block, char a2)
{
  sub_4A5A80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5A80 sub_4A5A80
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
char */*thiscall*/ sub_4A5AD0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNWhiteLugaru::`vftable';
  sub_595E10(this);
  sub_596990(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5B30 sub_4A5B30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5B30(void *Block, char a2)
{
  sub_4A5B60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5B60 sub_4A5B60
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
char */*thiscall*/ sub_4A5BB0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNPenril::`vftable';
  sub_598350(this);
  sub_598200(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A5C10 sub_4A5C10
// ------------------------------------------------------------
void */*thiscall*/ sub_4A5C10(void *Block, char a2)
{
  sub_4A5C40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5C40 sub_4A5C40
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
int /*thiscall*/ sub_4A5C90(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A5D30(void *Block, char a2)
{
  sub_4A5D60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A5D60 sub_4A5D60
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
int /*thiscall*/ sub_4A5DC0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
char */*thiscall*/ sub_4A5E70(char *this, char a2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A5EB0();
  if ( (a2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A5EB0 sub_4A5EB0
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
int /*thiscall*/ sub_4A5F10(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A60C0(void *Block, char a2)
{
  sub_4A5FF0((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A60F0 sub_4A60F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A60F0(uint32_t *this, char ArgList, int a3)
{
  sub_4A5F10((int)this, ArgList, a3);
  *this = &CNGoblinAssaulter::`vftable';
  *(this + 2150) = &CNGoblinAssaulter::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A6130 sub_4A6130
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6130(void *Block, char a2)
{
  sub_4A6160();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6160 sub_4A6160
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
uint32_t */*thiscall*/ sub_4A6180(uint32_t *this, char ArgList, int a3)
{
  sub_4A5F10((int)this, ArgList, a3);
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
int /*thiscall*/ sub_4A6230(char *this, char a2)
{
  return sub_4A6240(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A6240 sub_4A6240
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6240(void *Block, char a2)
{
  sub_4A6270();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6270 sub_4A6270
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
int /*thiscall*/ sub_4A62A0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4A6370(char *this, char a2)
{
  return sub_4A6450(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A6380 sub_4A6380
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
void */*thiscall*/ sub_4A6450(void *Block, char a2)
{
  sub_4A6380((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6480 sub_4A6480
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6480(uint32_t *this, char ArgList, int a3)
{
  sub_4A62A0((int)this, ArgList, a3);
  *this = &CNBunker_Woker::`vftable';
  *(this + 2150) = &CNBunker_Woker::`vftable';
  sub_59BF90(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A64F0 sub_4A64F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A64F0(void *Block, char a2)
{
  sub_4A6520();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6520 sub_4A6520
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
uint32_t */*thiscall*/ sub_4A6540(uint32_t *this, char ArgList, int a3)
{
  sub_4A62A0((int)this, ArgList, a3);
  *this = &CNEliteGoblin::`vftable';
  *(this + 2150) = &CNEliteGoblin::`vftable';
  *((uint8_t *)this + 8680) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A6580 sub_4A6580
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A6580(uint8_t *this, char ArgList, int a3)
{
  sub_4A62A0((int)this, ArgList, a3);
  *(this + 8680) = 0;
  *(uint32_t *)this = &CNKingGalok::`vftable';
  *((uint32_t *)this + 2150) = &CNKingGalok::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A65C0 sub_4A65C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A65C0(char *this, char a2)
{
  return sub_4A65D0(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A65D0 sub_4A65D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A65D0(void *Block, char a2)
{
  sub_4A6600();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6600 sub_4A6600
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
int /*thiscall*/ sub_4A6620(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4A66D0(char *this, char a2)
{
  return sub_4A6780(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A66E0 sub_4A66E0
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
void */*thiscall*/ sub_4A6780(void *Block, char a2)
{
  sub_4A66E0((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A67B0 sub_4A67B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A67B0(uint32_t *this, char ArgList, int a3)
{
  sub_4A6620((int)this, ArgList, a3);
  *this = &CNPrag::`vftable';
  *(this + 2150) = &CNPrag::`vftable';
  *(this + 2155) = 30076;
  *(this + 2167) = 30023;
  return this;
}



// ------------------------------------------------------------
// 0x4A67F0 sub_4A67F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A67F0(char *this, char a2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6830();
  if ( (a2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6830 sub_4A6830
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
int /*thiscall*/ sub_4A6850(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
char */*thiscall*/ sub_4A6900(char *this, char a2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6940();
  if ( (a2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6940 sub_4A6940
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
int /*thiscall*/ sub_4A69E0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
char */*thiscall*/ sub_4A6A90(char *this, char a2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6AD0();
  if ( (a2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6AD0 sub_4A6AD0
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
int /*thiscall*/ sub_4A6B70(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
char */*thiscall*/ sub_4A6C20(char *this, char a2)
{
  char *v2; // esi

  v2 = this - 8600;
  sub_4A6C60();
  if ( (a2 & 1) != 0 )
    j__free(v2);
  return v2;
}



// ------------------------------------------------------------
// 0x4A6C60 sub_4A6C60
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
int /*thiscall*/ sub_4A6D00(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4A6DA0(char *this, char a2)
{
  return sub_4A6DB0(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A6DB0 sub_4A6DB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6DB0(void *Block, char a2)
{
  sub_4A6F40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6DE0 sub_4A6DE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6DE0(uint32_t *this, char ArgList, int a3)
{
  sub_4A6D00((int)this, ArgList, a3);
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
void */*thiscall*/ sub_4A6EB0(void *Block, char a2)
{
  sub_4A6E80((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A6EE0 sub_4A6EE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A6EE0(uint32_t *this, char ArgList, int a3)
{
  sub_4A6D00((int)this, ArgList, a3);
  *this = &CNGoblinSharedo::`vftable';
  *(this + 2150) = &CNGoblinSharedo::`vftable';
  sub_5A0530(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6F40 sub_4A6F40
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
uint32_t */*thiscall*/ sub_4A6F60(uint32_t *this, char ArgList, int a3)
{
  sub_4A6DE0(this, ArgList, a3);
  *this = &CNGoblinBombKagel::`vftable';
  *(this + 2150) = &CNGoblinBombKagel::`vftable';
  sub_5A0780(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A6FD0 sub_4A6FD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A6FD0(void *Block, char a2)
{
  sub_4A7000();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7000 sub_4A7000
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
uint32_t */*thiscall*/ sub_4A7090(uint32_t *this, char ArgList, int a3)
{
  sub_4A6DE0(this, ArgList, a3);
  *this = &CNGoblinSurikenKagel::`vftable';
  *(this + 2150) = &CNGoblinSurikenKagel::`vftable';
  sub_5A0930(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7100 sub_4A7100
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7100(uint32_t *this, char ArgList, int a3)
{
  sub_4A6DE0(this, ArgList, a3);
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
int /*thiscall*/ sub_4A7180(char *this, char a2)
{
  return sub_4A7190(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A7190 sub_4A7190
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7190(void *Block, char a2)
{
  sub_4A71C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A71C0 sub_4A71C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A71C0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGoblinBullsEye::`vftable';
  *(uint32_t *)(this + 8600) = &CNGoblinBullsEye::`vftable';
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8704);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
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
int /*thiscall*/ sub_4A7280(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4A7320(char *this, char a2)
{
  return sub_4A7330(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A7330 sub_4A7330
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7330(void *Block, char a2)
{
  sub_4A7360();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7360 sub_4A7360
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
int /*thiscall*/ sub_4A73D0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4A7470(char *this, char a2)
{
  return sub_4A7480(this - 8600, a2);
}



// ------------------------------------------------------------
// 0x4A7480 sub_4A7480
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7480(void *Block, char a2)
{
  sub_4A74B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A74B0 sub_4A74B0
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
int /*thiscall*/ sub_4A7520(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A75A0(void *Block, char a2)
{
  sub_4A75D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A75D0 sub_4A75D0
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
int /*thiscall*/ sub_4A7640(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A76C0(void *Block, char a2)
{
  sub_4A76F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A76F0 sub_4A76F0
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
int /*thiscall*/ sub_4A7760(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4A7850(uint32_t *Block, char a2)
{
  sub_4A77E0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7880 sub_4A7880
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7880(uint32_t *this, char ArgList, int a3)
{
  sub_4A7760((int)this, ArgList, a3);
  *this = &CNRock_Moud::`vftable';
  *(this + 2150) = &CNRock_Moud::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A78B0 sub_4A78B0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A78B0(void *Block, char a2)
{
  sub_4A78E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A78E0 sub_4A78E0
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
int /*thiscall*/ sub_4A7900(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A7980(void *Block, char a2)
{
  sub_4A79B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A79B0 sub_4A79B0
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
int /*thiscall*/ sub_4A7A20(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A7AA0(void *Block, char a2)
{
  sub_4A7AD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7AD0 sub_4A7AD0
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
int /*thiscall*/ sub_4A7B40(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void **/*thiscall*/ sub_4A7C60(void **Block, char a2)
{
  sub_4A7BE0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7C90 sub_4A7C90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7C90(uint32_t *this, char ArgList, int a3)
{
  sub_4A7B40((int)this, ArgList, a3);
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
void **/*thiscall*/ sub_4A7D00(void **Block, char a2)
{
  sub_4A7CF0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7D30 sub_4A7D30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7D30(uint32_t *this, char ArgList, int a3)
{
  sub_4A7B40((int)this, ArgList, a3);
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
void **/*thiscall*/ sub_4A7DA0(void **Block, char a2)
{
  sub_4A7D90(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A7DD0 sub_4A7DD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7DD0(uint32_t *this, char ArgList, int a3)
{
  sub_4A7D30(this, ArgList, a3);
  *this = &CNGolemBronze::`vftable';
  sub_5A7E30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7E30 sub_4A7E30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A7E30(uint32_t *this, char ArgList, int a3)
{
  sub_4A7B40((int)this, ArgList, a3);
  *this = &CNGolemClay::`vftable';
  sub_5A7B50(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7E90 sub_4A7E90
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7E90(void *Block, char a2)
{
  sub_4A7EC0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A7ED0(uint32_t *this, char ArgList, int a3)
{
  sub_4A7B40((int)this, ArgList, a3);
  *this = &CNGolemGold::`vftable';
  sub_5A7CC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7F30 sub_4A7F30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7F30(void *Block, char a2)
{
  sub_4A7F60();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A7F70(uint32_t *this, char ArgList, int a3)
{
  sub_4A7B40((int)this, ArgList, a3);
  *this = &CNGolemPlatany::`vftable';
  sub_5A80A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A7FD0 sub_4A7FD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A7FD0(void *Block, char a2)
{
  sub_4A8000();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A8010(uint32_t *this, char ArgList, int a3)
{
  sub_4A7C90(this, ArgList, a3);
  *this = &CNStoneBlade_Razor::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8040 sub_4A8040
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8040(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNDollMaster::`vftable';
  sub_5A82B0(this);
  sub_5A9DA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A80A0 sub_4A80A0
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
uint32_t */*thiscall*/ sub_4A80F0(uint32_t *Block, char a2)
{
  sub_4A80A0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8120 sub_4A8120
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8120(char *this, char ArgList, int a3)
{
  sub_4A8040(this, ArgList, a3);
  *(uint32_t *)this = &CNStoneMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8150 sub_4A8150
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8150(void *Block, char a2)
{
  sub_4A8180();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8190(char *this, char ArgList, int a3)
{
  sub_4A8040(this, ArgList, a3);
  *(uint32_t *)this = &CNSteelMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A81C0 sub_4A81C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A81C0(void *Block, char a2)
{
  sub_4A81F0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8200(char *this, char ArgList, int a3)
{
  sub_4A8040(this, ArgList, a3);
  *(uint32_t *)this = &CNClayMaster::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8230 sub_4A8230
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8230(void *Block, char a2)
{
  sub_4A8260();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8270(char *this, char ArgList, int a3)
{
  sub_4A8040(this, ArgList, a3);
  *(uint32_t *)this = &CNMasterDogri::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A82A0 sub_4A82A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A82A0(void *Block, char a2)
{
  sub_4A82D0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A82E0(char *this, char ArgList, int a3)
{
  sub_4A8040(this, ArgList, a3);
  *(uint32_t *)this = &CNIceDoll_Sharedo::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8310 sub_4A8310
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8310(void *Block, char a2)
{
  sub_4A8340();
  if ( (a2 & 1) != 0 )
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



// ------------------------------------------------------------
// 0x4A8350 sub_4A8350
// ------------------------------------------------------------
int /*thiscall*/ sub_4A8350(int this, char ArgList, int a3)
{
  int v4; // eax
  unsigned int v5; // edx
  uint32_t *v6; // eax
  int v7; // edx
  unsigned int v8; // ecx
  uint32_t *v9; // eax
  int v10; // edx
  unsigned int v11; // ecx
  uint32_t *v12; // eax

  sub_4A4EA0((char *)this, ArgList, a3);
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
  a3 = 15;
  v4 = *(uint32_t *)(this + 8708);
  if ( v4 != 0 )
    v5 = (*(uint32_t *)(this + 8712) - v4) >> 2;
  else
    v5 = 0;
  if ( v4 != 0 && v5 < (*(uint32_t *)(this + 8716) - v4) >> 2 )
  {
    v6 = *(uint32_t **)(this + 8712);
    *v6 = 15;
    *(uint32_t *)(this + 8712) = v6 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&a3);
  }
  v7 = *(uint32_t *)(this + 8708);
  a3 = 80;
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(this + 8712) - v7) >> 2;
  else
    v8 = 0;
  if ( v7 != 0 && v8 < (*(uint32_t *)(this + 8716) - v7) >> 2 )
  {
    v9 = *(uint32_t **)(this + 8712);
    *v9 = 80;
    *(uint32_t *)(this + 8712) = v9 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&a3);
  }
  v10 = *(uint32_t *)(this + 8708);
  a3 = 135;
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(this + 8712) - v10) >> 2;
  else
    v11 = 0;
  if ( v10 != 0 && v11 < (*(uint32_t *)(this + 8716) - v10) >> 2 )
  {
    v12 = *(uint32_t **)(this + 8712);
    *v12 = 135;
    *(uint32_t *)(this + 8712) = v12 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8712), 1, (int)&a3);
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
void */*thiscall*/ sub_4A8650(void *Block, char a2)
{
  sub_4A8560((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8680 sub_4A8680
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4A8680(uint8_t *this, char ArgList, int a3)
{
  int v5; // [esp+20h] [ebp+Ch]

  sub_4A8350((int)this, ArgList, a3);
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
  v5 = sub_41A5E0((unsigned int)(this + 1492));
  *((uint32_t *)this + 2195) = (uint64_t)((double)v5 * COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 1506))));
  return this;
}



// ------------------------------------------------------------
// 0x4A8750 sub_4A8750
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8750(void *Block, char a2)
{
  sub_4A8780();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8780 sub_4A8780
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
uint8_t */*thiscall*/ sub_4A87A0(uint8_t *this, char ArgList, void *Block)
{
  uint32_t *v4; // eax

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
  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    *((uint32_t *)this + 2203) = sub_428F30(v4, (int)"PassiveObject/Monster/FlyDragon/Particle/Bouncer.ptl", 0);
  else
    *((uint32_t *)this + 2203) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8890 sub_4A8890
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8890(void *Block, char a2)
{
  sub_4A88C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A88C0 sub_4A88C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A88C0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

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
uint32_t */*thiscall*/ sub_4A8940(uint32_t *this, char ArgList, int a3)
{
  sub_4A8350((int)this, ArgList, a3);
  *this = &CNDrakeHarseSerimalion::`vftable';
  *(this + 2195) = -1;
  *(this + 2194) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A8980 sub_4A8980
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8980(void *Block, char a2)
{
  sub_4A89B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A89B0 sub_4A89B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89B0(int this)
{
  *(uint32_t *)this = &CNDrakeHarseSerimalion::`vftable';
  return sub_4A8560(this);
}



// ------------------------------------------------------------
// 0x4A89C0 sub_4A89C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4A89C0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4A8A60(void *Block, char a2)
{
  sub_4A8A90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8A90 sub_4A8A90
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
int /*thiscall*/ sub_4A8AF0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void **/*thiscall*/ sub_4A8BF0(void **Block, char a2)
{
  sub_4A8B70(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8C20 sub_4A8C20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A8C20(uint32_t *this, char ArgList, int a3)
{
  sub_4A8AF0((int)this, ArgList, a3);
  *this = &CNHunterMaster::`vftable';
  sub_5ADFE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8C80 sub_4A8C80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8C80(void *Block, char a2)
{
  sub_4A8CB0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A8CC0(uint32_t *this, char ArgList, int a3)
{
  sub_4A8AF0((int)this, ArgList, a3);
  *this = &CNHunterAlex::`vftable';
  sub_5AE160(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8D20 sub_4A8D20
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8D20(void *Block, char a2)
{
  sub_4A8D50();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A8D60(uint32_t *this, char ArgList, int a3)
{
  sub_4A8AF0((int)this, ArgList, a3);
  *this = &CNHunterHunter::`vftable';
  sub_5AE290(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8DC0 sub_4A8DC0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8DC0(void *Block, char a2)
{
  sub_4A8DF0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8E00(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNZombie::`vftable';
  sub_5AE3E0(this);
  sub_5AF220(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A8E60 sub_4A8E60
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
uint32_t */*thiscall*/ sub_4A8EB0(uint32_t *Block, char a2)
{
  sub_4A8E60(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A8EE0 sub_4A8EE0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A8EE0(char *this, char ArgList, int a3)
{
  sub_4A8E00(this, ArgList, a3);
  *(uint32_t *)this = &CNZombieZombie::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8F10 sub_4A8F10
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F10(void *Block, char a2)
{
  sub_4A8F40();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8F50(char *this, char ArgList, int a3)
{
  sub_4A8E00(this, ArgList, a3);
  *(uint32_t *)this = &CNZombieHollowEye::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A8F80 sub_4A8F80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A8F80(void *Block, char a2)
{
  sub_4A8FB0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A8FC0(char *this, char ArgList, int a3)
{
  sub_4A8E00(this, ArgList, a3);
  *(uint32_t *)this = &CNZombieGhoulgwish::`vftable';
  sub_5AE830(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9020 sub_4A9020
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9020(void *Block, char a2)
{
  sub_4A9050();
  if ( (a2 & 1) != 0 )
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
int /*thiscall*/ sub_4A9060(int this, char ArgList, int a3)
{
  sub_4A8E00((char *)this, ArgList, a3);
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = 0;
  *(uint32_t *)this = &CNKalkazak::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9090 sub_4A9090
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9090(void *Block, char a2)
{
  sub_4A90C0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A90D0(char *this, char ArgList, int a3)
{
  sub_4A8E00(this, ArgList, a3);
  *(uint32_t *)this = &CNBurningHela::`vftable';
  *(this + 8652) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A9100 sub_4A9100
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9100(void *Block, char a2)
{
  sub_4A9130();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9140(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNDraconian::`vftable';
  sub_5AF910(this);
  sub_5B0660(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A91A0 sub_4A91A0
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
uint32_t */*thiscall*/ sub_4A91F0(uint32_t *Block, char a2)
{
  sub_4A91A0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9220 sub_4A9220
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9220(char *this, char ArgList, int a3)
{
  sub_4A9140(this, ArgList, a3);
  *(uint32_t *)this = &CNDracoMirkius::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9250 sub_4A9250
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9250(void *Block, char a2)
{
  sub_4A9280();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9290(char *this, char ArgList, int a3)
{
  sub_4A9140(this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4A9300(uint32_t *Block, char a2)
{
  sub_4A92F0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9330 sub_4A9330
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9330(char *this, char ArgList, int a3)
{
  sub_4A9290(this, ArgList, a3);
  *(uint32_t *)this = &CNAuraHunter_Sius::`vftable';
  sub_5AFDD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9390 sub_4A9390
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9390(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNLordofLightBase::`vftable';
  sub_5B1910(this);
  sub_5B2720(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A93F0 sub_4A93F0
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
uint32_t */*thiscall*/ sub_4A9440(uint32_t *Block, char a2)
{
  sub_4A93F0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9470 sub_4A9470
// ------------------------------------------------------------
char */*thiscall*/ sub_4A9470(char *this, char ArgList, int a3)
{
  sub_4A9390(this, ArgList, a3);
  *(uint32_t *)this = &CNLordofLight::`vftable';
  sub_5B3100(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A94D0 sub_4A94D0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A94D0(void *Block, char a2)
{
  sub_4A9500();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9510(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNSpaceFishHead::`vftable';
  sub_5B3230(this);
  sub_5B3F30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9570 sub_4A9570
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
uint32_t */*thiscall*/ sub_4A95C0(uint32_t *Block, char a2)
{
  sub_4A9570(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A95F0 sub_4A95F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4A95F0(char *this, char ArgList, int a3)
{
  sub_4A9510(this, ArgList, a3);
  *(uint32_t *)this = &CNSpaceFishShort::`vftable';
  sub_5B3400(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9650 sub_4A9650
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9650(void *Block, char a2)
{
  sub_4A9680();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9690(char *this, char ArgList, int a3)
{
  sub_4A9510(this, ArgList, a3);
  *(uint32_t *)this = &CNSpaceFishLong::`vftable';
  sub_5B34D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A96F0 sub_4A96F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A96F0(void *Block, char a2)
{
  sub_4A9720();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9730(char *this, char ArgList, int a3)
{
  sub_4A9510(this, ArgList, a3);
  *(uint32_t *)this = &CNSpaceFishCrocuta::`vftable';
  sub_5B35C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4A9790 sub_4A9790
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9790(void *Block, char a2)
{
  sub_4A97C0();
  if ( (a2 & 1) != 0 )
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
int /*thiscall*/ sub_4A97D0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4A98C0(uint32_t *Block, char a2)
{
  sub_4A9850(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A98F0 sub_4A98F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A98F0(uint32_t *this, char ArgList, int a3)
{
  sub_4A97D0((int)this, ArgList, a3);
  *this = &CNStarFishRukuku::`vftable';
  *(this + 2150) = &CNStarFishRukuku::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9920 sub_4A9920
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9920(void *Block, char a2)
{
  sub_4A9950();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A9970(uint32_t *this, char ArgList, int a3)
{
  sub_4A97D0((int)this, ArgList, a3);
  *this = &CNStarFishDevourer::`vftable';
  *(this + 2150) = &CNStarFishDevourer::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A99A0 sub_4A99A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A99A0(void *Block, char a2)
{
  sub_4A99D0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A99F0(uint32_t *this, char ArgList, int a3)
{
  sub_4A97D0((int)this, ArgList, a3);
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
void */*thiscall*/ sub_4A9A60(void *Block, char a2)
{
  sub_4A9A90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9A90 sub_4A9A90
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
int /*thiscall*/ sub_4A9AC0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4A9BF0(uint32_t *Block, char a2)
{
  sub_4A9B70(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4A9C20 sub_4A9C20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C20(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNRaxy_A::`vftable';
  *(this + 2150) = &off_6E7860;
  return this;
}



// ------------------------------------------------------------
// 0x4A9C50 sub_4A9C50
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9C50(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNRaxy_B::`vftable';
  *(this + 2150) = &CNRaxy_B::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9C80 sub_4A9C80
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9C80(void *Block, char a2)
{
  sub_4A9CB0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A9CD0(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNCraxy::`vftable';
  *(this + 2150) = &CNCraxy::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9D00 sub_4A9D00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9D00(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNFather::`vftable';
  *(this + 2150) = &CNFather::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9D30 sub_4A9D30
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9D30(void *Block, char a2)
{
  sub_4A9D60();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A9D80(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNPope::`vftable';
  *(this + 2150) = &CNPope::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9DB0 sub_4A9DB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9DB0(void *Block, char a2)
{
  sub_4A9DE0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A9E00(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNEvangelistOfDawn::`vftable';
  *(this + 2150) = &CNEvangelistOfDawn::`vftable';
  *(this + 2168) = 30041;
  return this;
}



// ------------------------------------------------------------
// 0x4A9E50 sub_4A9E50
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E50(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNEvangelistOfLight::`vftable';
  *(this + 2150) = &CNEvangelistOfLight::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4A9E80 sub_4A9E80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4A9E80(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNEvangelistOfTwilight::`vftable';
  *(this + 2150) = &CNEvangelistOfTwilight::`vftable';
  *(this + 2169) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4A9EC0 sub_4A9EC0
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9EC0(void *Block, char a2)
{
  sub_4A9EF0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4A9F10(uint32_t *this, char ArgList, int a3)
{
  sub_4A9AC0((int)this, ArgList, a3);
  *this = &CNEvangelistOfDark::`vftable';
  *(this + 2150) = &CNEvangelistOfDark::`vftable';
  *(this + 2168) = 30042;
  return this;
}



// ------------------------------------------------------------
// 0x4A9F50 sub_4A9F50
// ------------------------------------------------------------
void */*thiscall*/ sub_4A9F50(void *Block, char a2)
{
  sub_4A9F80();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4A9FA0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNVehicle::`vftable';
  sub_5BA050(this);
  sub_5BAC30(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA000 sub_4AA000
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
uint32_t */*thiscall*/ sub_4AA050(uint32_t *Block, char a2)
{
  sub_4AA000(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA080 sub_4AA080
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA080(char *this, char ArgList, int a3)
{
  sub_4A9FA0(this, ArgList, a3);
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
char */*thiscall*/ sub_4AA0F0(char *this, char ArgList, int a3)
{
  sub_4AA080(this, ArgList, a3);
  *(uint32_t *)this = &CNLaserCatapult::`vftable';
  sub_5BAD00(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA150 sub_4AA150
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA150(char *this, char ArgList, int a3)
{
  sub_4AA080(this, ArgList, a3);
  *(uint32_t *)this = &CNFlameCatapult::`vftable';
  sub_5BAD00(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA1B0 sub_4AA1B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA1B0(uint32_t *Block, char a2)
{
  sub_4AA0E0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA1E0 sub_4AA1E0
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA1E0(char *this, char ArgList, int a3)
{
  sub_4A9FA0(this, ArgList, a3);
  *(uint32_t *)this = &CNBattlIngram::`vftable';
  sub_5BAEF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA240 sub_4AA240
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA240(void *Block, char a2)
{
  sub_4AA270();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4AA280(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNZepplin::`vftable';
  `eh vector constructor iterator'(this + 8616, 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  nullsub_3(this);
  sub_5BB420(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA300 sub_4AA300
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
uint32_t */*thiscall*/ sub_4AA370(uint32_t *Block, char a2)
{
  sub_4AA300(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA3A0 sub_4AA3A0
// ------------------------------------------------------------
char */*thiscall*/ sub_4AA3A0(char *this, char ArgList, int a3)
{
  sub_4AA280(this, ArgList, a3);
  *(uint32_t *)this = &CNCannonZepplin::`vftable';
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA400 sub_4AA400
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA400(void *Block, char a2)
{
  sub_4AA430();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4AA440(char *this, char ArgList, int a3)
{
  sub_4AA280(this, ArgList, a3);
  *(uint32_t *)this = &CNNormalZepplin::`vftable';
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA4A0 sub_4AA4A0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA4A0(void *Block, char a2)
{
  sub_4AA4D0();
  if ( (a2 & 1) != 0 )
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
int /*thiscall*/ sub_4AA4E0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void **/*thiscall*/ sub_4AA5E0(void **Block, char a2)
{
  sub_4AA560(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA610 sub_4AA610
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AA610(uint32_t *this, char ArgList, int a3)
{
  sub_4AA4E0((int)this, ArgList, a3);
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
void */*thiscall*/ sub_4AA6C0(void *Block, char a2)
{
  sub_4AA6F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA6F0 sub_4AA6F0
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
char */*thiscall*/ sub_4AA780(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNSpider::`vftable';
  sub_5BEC80(this);
  sub_5BECA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA7F0 sub_4AA7F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA7F0(int this, char ArgList, int a3)
{
  sub_4AA780((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4AA890(void *Block, char a2)
{
  sub_4AA8C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA8C0 sub_4AA8C0
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
char */*thiscall*/ sub_4AA8E0(char *this, char ArgList, int a3)
{
  sub_4AA780(this, ArgList, a3);
  *(uint32_t *)this = &CNPoisonSpider::`vftable';
  sub_5C0400(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AA940 sub_4AA940
// ------------------------------------------------------------
void */*thiscall*/ sub_4AA940(void *Block, char a2)
{
  sub_4AA7E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AA970 sub_4AA970
// ------------------------------------------------------------
int /*thiscall*/ sub_4AA970(int this, char ArgList, int a3)
{
  sub_4AA780((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4AAA80(void *Block, char a2)
{
  sub_4AAAB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AAAB0 sub_4AAAB0
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
char */*thiscall*/ sub_4AAB30(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNRobotRX78::`vftable';
  sub_5C1FC0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAB90 sub_4AAB90
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAB90(void *Block, char a2)
{
  sub_4AABC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AABC0 sub_4AABC0
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
char */*thiscall*/ sub_4AAC10(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNRobotEz8::`vftable';
  sub_5C2830(this);
  sub_5C2870(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAC70 sub_4AAC70
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAC70(void *Block, char a2)
{
  sub_4AACA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AACA0 sub_4AACA0
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
char */*thiscall*/ sub_4AACF0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNRobotExs::`vftable';
  sub_5C3100(this);
  sub_5C3760(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAD50 sub_4AAD50
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AAD50(void *this, int a2, int a3, int a4)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 5;
}



// ------------------------------------------------------------
// 0x4AAD70 sub_4AAD70
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAD70(void *Block, char a2)
{
  sub_4AADA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AADA0 sub_4AADA0
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
char */*thiscall*/ sub_4AADF0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNDendroidBasic::`vftable';
  sub_5C3A30(this);
  sub_5C57F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAE50 sub_4AAE50
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
uint32_t */*thiscall*/ sub_4AAEA0(uint32_t *Block, char a2)
{
  sub_4AAE50(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AAED0 sub_4AAED0
// ------------------------------------------------------------
char */*thiscall*/ sub_4AAED0(char *this, char ArgList, int a3)
{
  sub_4AADF0(this, ArgList, a3);
  *(uint32_t *)this = &off_6F04BC;
  sub_5C4080(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAF30 sub_4AAF30
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAF30(void *Block, char a2)
{
  sub_4AAF60();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4AAF70(char *this, char ArgList, int a3)
{
  sub_4AADF0(this, ArgList, a3);
  *(uint32_t *)this = &CNGoliden::`vftable';
  sub_5C4100(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AAFD0 sub_4AAFD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AAFD0(void *Block, char a2)
{
  sub_4AB000();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4AB010(char *this, char ArgList, int a3)
{
  sub_4AADF0(this, ArgList, a3);
  *(uint32_t *)this = &CNRodinglo::`vftable';
  sub_5C41B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB070 sub_4AB070
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB070(void *Block, char a2)
{
  sub_4AB0A0();
  if ( (a2 & 1) != 0 )
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
int /*thiscall*/ sub_4AB0B0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
int /*thiscall*/ sub_4AB180(int this)
{
  int v2; // eax
  int v3; // eax

  *(uint32_t *)this = &CNSpirit::`vftable';
  nullsub_3(this);
  if ( *(uint32_t *)(this + 8720) != 0 )
    j__free(*(void **)(this + 8720));
  *(uint32_t *)(this + 8720) = 0;
  *(uint32_t *)(this + 8724) = 0;
  *(uint32_t *)(this + 8728) = 0;
  v2 = *(uint32_t *)(this + 8704);
  if ( v2 != 0 )
  {
    sub_4166A0(v2, *(uint32_t *)(this + 8708));
    j__free(*(void **)(this + 8704));
  }
  *(uint32_t *)(this + 8704) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  v3 = *(uint32_t *)(this + 8688);
  if ( v3 != 0 )
  {
    sub_4166A0(v3, *(uint32_t *)(this + 8692));
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
void */*thiscall*/ sub_4AB2F0(void *Block, char a2)
{
  sub_4AB180((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB320 sub_4AB320
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4AB320(uint8_t *this, char ArgList, int a3)
{
  sub_4AB0B0((int)this, ArgList, a3);
  *(uint32_t *)this = &CNNaias::`vftable';
  *(this + 8744) = 0;
  sub_5C8290(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB380 sub_4AB380
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB380(void *Block, char a2)
{
  sub_4AB3B0();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4AB3C0(uint32_t *this, char ArgList, int a3)
{
  sub_4AB0B0((int)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4AB430(uint32_t *this, char ArgList, int a3)
{
  sub_4AB3C0(this, ArgList, a3);
  *this = &CNSoulEter::`vftable';
  sub_5C6590(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB490 sub_4AB490
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB490(void *Block, char a2)
{
  sub_4AB420((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB4C0 sub_4AB4C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB4C0(uint32_t *this, char ArgList, int a3)
{
  sub_4AB0B0((int)this, ArgList, a3);
  *this = &CNStalker::`vftable';
  sub_5C8650(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB520 sub_4AB520
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB520(void *Block, char a2)
{
  sub_4AB550();
  if ( (a2 & 1) != 0 )
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
uint32_t */*thiscall*/ sub_4AB560(uint32_t *this, char ArgList, int a3)
{
  sub_4AB0B0((int)this, ArgList, a3);
  *this = &CNWisp::`vftable';
  sub_5C8FE0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB5C0 sub_4AB5C0
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB5C0(void *Block, char a2)
{
  sub_4AB5F0();
  if ( (a2 & 1) != 0 )
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
int /*thiscall*/ sub_4AB600(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4AB710(uint32_t *Block, char a2)
{
  sub_4AB6B0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB740 sub_4AB740
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AB740(uint32_t *this, char ArgList, int a3)
{
  sub_4AB600((int)this, ArgList, a3);
  *this = &CNLotus::`vftable';
  return this;
}



// ------------------------------------------------------------
// 0x4AB770 sub_4AB770
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB770(void *Block, char a2)
{
  sub_4AB7A0();
  if ( (a2 & 1) != 0 )
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
char */*thiscall*/ sub_4AB7B0(char *this, char ArgList, int a3)
{
  sub_4A4EA0(this, ArgList, a3);
  *(uint32_t *)this = &CNMonsterFlower::`vftable';
  sub_5CB970(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x4AB810 sub_4AB810
// ------------------------------------------------------------
void */*thiscall*/ sub_4AB810(void *Block, char a2)
{
  sub_5CBD40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB840 sub_4AB840
// ------------------------------------------------------------
int /*thiscall*/ sub_4AB840(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
void */*thiscall*/ sub_4AB930(void *Block, char a2)
{
  sub_4AB960();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4AB960 sub_4AB960
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
int /*thiscall*/ sub_4AB9F0(int this, char ArgList, int a3)
{
  sub_4A4EA0((char *)this, ArgList, a3);
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
uint32_t */*thiscall*/ sub_4ABB40(uint32_t *Block, char a2)
{
  sub_4ABAD0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABB70 sub_4ABB70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ABB70(uint32_t *this, char ArgList, int a3)
{
  sub_4AB9F0((int)this, ArgList, a3);
  *this = &CNGoliath::`vftable';
  sub_5CD1E0(this);
  sub_5CD220(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABBD0 sub_4ABBD0
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABBD0(void *Block, char a2)
{
  sub_4ABC00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABC00 sub_4ABC00
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
uint32_t */*thiscall*/ sub_4ABC50(uint32_t *this, char ArgList, int a3)
{
  sub_4AB9F0((int)this, ArgList, a3);
  *this = &CNAtlas::`vftable';
  sub_5CD360(this);
  sub_5CD380(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABCB0 sub_4ABCB0
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABCB0(void *Block, char a2)
{
  sub_4ABCE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABCE0 sub_4ABCE0
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
uint32_t */*thiscall*/ sub_4ABD30(uint32_t *this, char ArgList, int a3)
{
  sub_4AB9F0((int)this, ArgList, a3);
  *this = &CNTitan::`vftable';
  sub_5CD3C0(this);
  sub_599D80(this);
  return this;
}



// ------------------------------------------------------------
// 0x4ABD90 sub_4ABD90
// ------------------------------------------------------------
void */*thiscall*/ sub_4ABD90(void *Block, char a2)
{
  sub_4ABDC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4ABDC0 sub_4ABDC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4ABDC0(uint32_t *this)
{
  *this = &CNTitan::`vftable';
  sub_5CD3F0();
  return sub_4ABAD0(this);
}



// ------------------------------------------------------------
// 0x4AEA30 sub_4AEA30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4AEA30(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  uint32_t *v3; // edx
  uint32_t *v4; // ecx

  result = (uint32_t *)*(this + 3);
  if ( result != nullptr )
  {
    v3 = (uint32_t *)*(this + 2);
    result = (uint32_t *)*v3;
    if ( (uint32_t *)*v3 != v3 )
    {
      while ( 1 )
      {
        v4 = (uint32_t *)result[2];
        if ( *(uint32_t *)(a2 + 8) == v4[1] )
          break;
        result = (uint32_t *)*result;
        if ( result == v3 )
          return result;
      }
      return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v4 + 4))(v4, a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AEA70 sub_4AEA70
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEA70(int *this)
{
  int result; // eax
  unsigned int v3; // eax
  int v4; // edx
  unsigned int v5; // edi
  int v6; // ebx
  unsigned int v7; // eax
  unsigned int v8; // ecx
  uint32_t *v9; // edx
  uint32_t *v10; // eax
  uint32_t *v11; // ecx
  int v12; // [esp+Ch] [ebp-4h] BYREF

  while ( 1 )
  {
    result = *(this + 20);
    if ( result == 0 )
      return result;
    v3 = (unsigned int)*(this + 19) >> 2;
    v4 = *(this + 19) - 4 * v3;
    v5 = *(this + 18);
    if ( v5 <= v3 )
      v3 -= v5;
    v6 = *(uint32_t *)(*(uint32_t *)(*(this + 17) + 4 * v3) + 4 * v4);
    v7 = *(this + 19) + 1;
    v8 = 4 * *(this + 18);
    *(this + 19) = v7;
    if ( v8 <= v7 )
      *(this + 19) = 0;
    result = *(this + 20) - 1;
    *(this + 20) = result;
    if ( result == 0 )
      *(this + 19) = 0;
    if ( v6 == 0 )
      return result;
    if ( *(this + 3) != 0 )
    {
      v9 = (uint32_t *)*(this + 2);
      v10 = (uint32_t *)*v9;
      if ( (uint32_t *)*v9 != v9 )
      {
        while ( 1 )
        {
          v11 = (uint32_t *)v10[2];
          if ( *(uint32_t *)(v6 + 8) == v11[1] )
            break;
          v10 = (uint32_t *)*v10;
          if ( v10 == v9 )
            goto LABEL_15;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*v11 + 4))(v11, v6);
      }
    }
LABEL_15:
    v12 = v6;
    sub_49C800((int)&unk_9B9310, &v12);
  }
}



// ------------------------------------------------------------
// 0x4AEB30 sub_4AEB30
// ------------------------------------------------------------
int /*thiscall*/ sub_4AEB30(int *this)
{
  sub_4AEA70(this);
  return sub_58B380(this + 4);
}



// ------------------------------------------------------------
// 0x4AEB50 sub_4AEB50
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEB50(unsigned int *this)
{
  int v2; // eax
  unsigned int v3; // eax
  int v4; // ecx
  unsigned int v5; // edi
  int v6; // ecx
  int v7; // eax
  unsigned int v8; // edx
  unsigned int v9; // edi
  unsigned int v10; // eax
  uint32_t v11[4]; // [esp+Ch] [ebp-10h] BYREF

  v2 = *(this + 4);
  v11[3] = 0;
  if ( v2 != 0 )
  {
    do
    {
      v3 = *(this + 3) >> 2;
      v4 = *(this + 3) - 4 * v3;
      v5 = *(this + 2);
      if ( v5 <= v3 )
        v3 -= v5;
      v6 = *(uint32_t *)(*(uint32_t *)(*(this + 1) + 4 * v3) + 4 * v4);
      v7 = *(this + 4);
      if ( v7 != 0 )
      {
        v8 = *(this + 3) + 1;
        v9 = 4 * *(this + 2);
        *(this + 3) = v8;
        if ( v9 <= v8 )
          *(this + 3) = 0;
        v10 = v7 - 1;
        *(this + 4) = v10;
        if ( v10 == 0 )
          *(this + 3) = 0;
      }
      if ( v6 != 0 )
      {
        v11[0] = v6;
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
uint32_t */*thiscall*/ sub_4AEC00(uint32_t *this)
{
  uint32_t *v2; // edi

  v2 = this + 1;
  sub_498A00(this + 1);
  sub_58B450(this + 4);
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  if ( v2[2] != 0 )
    sub_6569D0(v2);
  return this;
}



// ------------------------------------------------------------
// 0x4AEC70 sub_4AEC70
// ------------------------------------------------------------
void /*thiscall*/ sub_4AEC70(uint32_t *this)
{
  void **v2; // edi

  v2 = (void **)(this + 1);
  if ( *(this + 3) != 0 )
    sub_6569D0(this + 1);
  sub_4AEB50(this + 16);
  sub_58B4D0(this + 4);
  sub_4989D0(v2);
}



// ------------------------------------------------------------
// 0x4AECE0 sub_4AECE0
// ------------------------------------------------------------
char /*thiscall*/ sub_4AECE0(void *this, int a2)
{
  int v3; // eax

  v3 = sub_491C70(a2);
  return sub_493A60((int)this, v3);
}



// ------------------------------------------------------------
// 0x4AED00 sub_4AED00
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4AED00(float *this)
{
  return *((uint8_t *)this + 16) != 0 || *this > 0.0;
}



// ------------------------------------------------------------
// 0x4AED20 sub_4AED20
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED20(int this)
{
  int v2; // esi

  if ( *(uint8_t *)(this + 642) != 0 )
    return *(uint32_t *)(this + 644);
  v2 = *(uint32_t *)(this + 120);
  if ( v2 == 0 )
    return 0;
  if ( *(uint32_t *)(v2 + 148) == -1 )
    sub_4938F0(*(uint32_t *)(this + 120));
  return *(uint32_t *)(v2 + 112);
}



// ------------------------------------------------------------
// 0x4AED60 sub_4AED60
// ------------------------------------------------------------
double /*thiscall*/ sub_4AED60(void *this, float a2)
{
  int v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0((unsigned int)this)) + a2;
  sub_41A590((unsigned int)this, v3, v5);
  return *(float *)&v5;
}



// ------------------------------------------------------------
// 0x4AED90 sub_4AED90
// ------------------------------------------------------------
int /*thiscall*/ sub_4AED90(char *this, float a2, int a3, int a4, int a5)
{
  return sub_47EFD0(this, a2, a3, a4, a4, a5);
}



// ------------------------------------------------------------
// 0x4AEDB0 sub_4AEDB0
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
int /*thiscall*/ sub_4AEDD0(int this)
{
  int result; // eax
  uint32_t *v2; // edx
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
  v2 = (uint32_t *)(this + 8172);
  for ( i = 5; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      *(v2 - 10) = 0;
      *v2++ = 0;
    }
  }
  *(uint32_t *)(this + 7428) = 0;
  *(uint32_t *)(this + 8212) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4AF010 sub_4AF010
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF010(char *this, int a2)
{
  int v3; // edx
  unsigned int v5; // edi
  int v6; // edx
  bool v7; // zf
  unsigned int v8; // edi
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

  qmemcpy(this + 7432, (const void *)a2, 0x4Fu);
  sub_41A590((unsigned int)(this + 708), *(uint32_t *)(a2 + 4) / 0xAu, *(uint32_t *)(a2 + 4) / 0xAu);
  sub_41A590((unsigned int)(this + 722), v3, 1065353216);
  v5 = (unsigned int)(this + 904);
  v21 = (int16_t *)(a2 + 16);
  v19 = 4;
  do
  {
    sub_41A590(v5 - 56, (int)((uint64_t)(1717986919LL * *v21) >> 32) >> 2, *v21 / 10);
    sub_41A590(v5, v6, 1065353216);
    v5 += 14;
    v7 = v19 == 1;
    ++v21;
    --v19;
  }
  while ( !v7 );
  v8 = (unsigned int)(this + 1184);
  v22 = (int16_t *)(a2 + 24);
  v20 = 16;
  do
  {
    sub_41A590(v8 - 224, (int)((uint64_t)(1717986919LL * *v22) >> 32) >> 2, *v22 / 10);
    sub_41A590(v8, 1065353216, 1065353216);
    v8 += 14;
    v7 = v20 == 1;
    ++v22;
    --v20;
  }
  while ( !v7 );
  sub_41A590(
    (unsigned int)(this + 1408),
    (int)((uint64_t)(1717986919LL * *(int *)(a2 + 56)) >> 32) >> 2,
    *(uint32_t *)(a2 + 56) / 10);
  sub_41A590((unsigned int)(this + 1422), v9, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1436),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(a2 + 60)) >> 32) >> 2,
    *(int16_t *)(a2 + 60) / 10);
  sub_41A590((unsigned int)(this + 1450), v10, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1464),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(a2 + 62)) >> 32) >> 2,
    *(int16_t *)(a2 + 62) / 10);
  sub_41A590((unsigned int)(this + 1478), v11, 1065353216);
  sub_41A590((unsigned int)(this + 1492), *(uint16_t *)(a2 + 64) / 10, *(uint16_t *)(a2 + 64) / 10);
  sub_41A590((unsigned int)(this + 1506), v12, 1065353216);
  sub_41A590((unsigned int)(this + 1520), *(uint16_t *)(a2 + 66) / 10, *(uint16_t *)(a2 + 66) / 10);
  sub_41A590((unsigned int)(this + 1534), v13, 1065353216);
  sub_41A590((unsigned int)(this + 1548), *(uint16_t *)(a2 + 68) / 10, *(uint16_t *)(a2 + 68) / 10);
  sub_41A590((unsigned int)(this + 1562), v14, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1576),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(a2 + 70)) >> 32) >> 2,
    *(int16_t *)(a2 + 70) / 10);
  sub_41A590((unsigned int)(this + 1590), v15, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1604),
    (int)((uint64_t)(1717986919LL * *(int16_t *)(a2 + 72)) >> 32) >> 2,
    *(int16_t *)(a2 + 72) / 10);
  sub_41A590((unsigned int)(this + 1618), v16, 1065353216);
  sub_41A590(
    (unsigned int)(this + 1660),
    (int)((uint64_t)(1717986919LL * *(int *)(a2 + 74)) >> 32) >> 2,
    *(uint32_t *)(a2 + 74) / 10);
  sub_41A590((unsigned int)(this + 1674), v17, 1065353216);
  return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
}



// ------------------------------------------------------------
// 0x4AF330 sub_4AF330
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF330(unsigned int *this, char a2)
{
  uint32_t *v3; // eax
  double v4; // st7
  int v5; // eax
  int v6; // edi
  uint64_t v7; // rax
  char result; // al
  unsigned int v9; // ebx
  int v10; // eax
  unsigned int v11; // ebx
  int v12; // eax

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 672))(this, 3);
  v4 = sub_432FD0(*v3, 2);
  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  v6 = 100;
  if ( v5 != 4 && v5 != 6 )
    v6 = *((uint8_t *)this + 7510);
  v7 = (uint64_t)((double)*(this + 1858) * v4 * 0.1);
  sub_41A590((unsigned int)(this + 170), SHIDWORD(v7), v7);
  sub_41A590(
    (unsigned int)(this + 184),
    (int)((uint64_t)(274877907LL * v6 * *((uint16_t *)this + 3720)) >> 32) >> 6,
    v6 * *((uint16_t *)this + 3720) / 1000);
  sub_41A590(
    (unsigned int)(this + 191),
    (int)((uint64_t)(274877907LL * v6 * *((uint16_t *)this + 3721)) >> 32) >> 6,
    v6 * *((uint16_t *)this + 3721) / 1000);
  sub_41A590(
    (unsigned int)(this + 198),
    (int)((uint64_t)(274877907LL * v6 * *((uint16_t *)this + 3722)) >> 32) >> 6,
    v6 * *((uint16_t *)this + 3722) / 1000);
  sub_41A590(
    (unsigned int)(this + 205),
    (int)((uint64_t)(274877907LL * v6 * *((uint16_t *)this + 3723)) >> 32) >> 6,
    v6 * *((uint16_t *)this + 3723) / 1000);
  (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 676))(this, 0);
  result = a2;
  if ( a2 != 0 )
  {
    v9 = *this;
    v10 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, int))(*this + 740))(this, 0, 1);
    (*(void (/*thiscall*/ **)(unsigned int *, int))(v9 + 732))(this, v6 * v10 / 100);
    v11 = *this;
    v12 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 756))(this, 1);
    return (*(int (/*thiscall*/ **)(unsigned int *, int))(v11 + 748))(this, v6 * v12 / 100);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF4B0 sub_4AF4B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF4B0(int *this, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  int v7; // eax
  char result; // al
  int v9; // edi
  int v10; // eax
  int v11; // [esp-4h] [ebp-10h]
  int v12; // [esp-4h] [ebp-10h]

  if ( (uint8_t)a2 == 0 )
  {
    v6 = *(this + 30);
    if ( v6 != 0 )
    {
      if ( *(uint32_t *)(v6 + 148) == -1 )
        sub_4938F0(*(this + 30));
      v11 = *(uint8_t *)(v6 + 95);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);
      sub_432600(0, a3, a4, this, v7, 1, v11);
    }
  }
  sub_58E750(this, a2, a3, a4, a5);
  result = a2;
  if ( (uint8_t)a2 != 0 )
  {
    v9 = *(this + 30);
    if ( v9 != 0 )
    {
      if ( *(uint32_t *)(v9 + 148) == -1 )
        sub_4938F0(*(this + 30));
      v12 = *(uint8_t *)(v9 + 95);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 792))(this, 9);
      return sub_432600(1, a3, a4, this, v10, 1, v12);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF560 sub_4AF560
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4AF560(int a1, uint32_t *a2, char *a3)
{
  uint32_t *v3; // edi
  uint32_t *v4; // esi
  int v5; // ebx
  uint32_t *result; // eax
  int i; // [esp+Ch] [ebp-4h]

  if ( *a2 != 0 && *(uint32_t *)a3 != 0 )
    sub_494240(a1, *(uint32_t *)a3);
  v3 = a3 + 20;
  v4 = a2 + 1;
  v5 = a3 - (char *)a2;
  for ( i = 4; i != 0; --i )
  {
    if ( *v4 != 0 && *(uint32_t *)((char *)v4 + v5) != 0 )
      sub_494240(a1, *(uint32_t *)((char *)v4 + v5));
    if ( v4[4] != 0 && *v3 != 0 )
      sub_494240(a1, *v3);
    ++v4;
    ++v3;
  }
  if ( a2[9] != 0 && *((uint32_t *)a3 + 9) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 9));
  if ( a2[10] != 0 && *((uint32_t *)a3 + 10) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 10));
  if ( a2[11] != 0 && *((uint32_t *)a3 + 11) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 11));
  result = a2;
  if ( a2[12] != 0 )
  {
    result = *((uint32_t **)a3 + 12);
    if ( result != nullptr )
      return (uint32_t *)sub_494240(a1, *((uint32_t *)a3 + 12));
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF650 sub_4AF650
// ------------------------------------------------------------
void **/*stdcall*/ sub_4AF650(void ****a1, void **a2)
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

  if ( *a1 != nullptr && *a2 != nullptr )
    sub_492980(*a1, *a2);
  v2 = a2 + 5;
  v3 = a1 + 1;
  v4 = (char *)((char *)a2 - (char *)a1);
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
  v6 = a1[9];
  if ( v6 != nullptr && a2[9] != nullptr )
    sub_492980(v6, a2[9]);
  v7 = a1[10];
  if ( v7 != nullptr && a2[10] != nullptr )
    sub_492980(v7, a2[10]);
  result = (void **)a1;
  v9 = a1[11];
  if ( v9 != nullptr )
  {
    result = (void **)a2[11];
    if ( result != nullptr )
      result = sub_492980(v9, a2[11]);
  }
  v10 = a1[12];
  if ( v10 != nullptr )
  {
    result = (void **)a2[12];
    if ( result != nullptr )
      return sub_492980(v10, a2[12]);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AF720 sub_4AF720
// ------------------------------------------------------------
void /*thiscall*/ sub_4AF720(uint32_t *this)
{
  int *v2; // esi
  int *v3; // ecx
  int v4; // eax
  int v5; // edx

  v2 = nullptr;
  if ( *(this + 29) != 0 )
    v2 = (int *)sub_45EAC0(this);
  v3 = (int *)*(this + 1972);
  if ( v3 != v2 )
  {
    if ( v3 != nullptr )
    {
      v4 = *v3;
      *((uint8_t *)v3 + 976) = 0;
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
int /*thiscall*/ sub_4AF7F0(int *this)
{
  int result; // eax
  int v3; // eax
  uint8_t v4[4]; // [esp+4h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 12);
    switch ( result )
    {
      case 3:
        sub_423200(dword_8F7B08, 43);
        return sub_423380(dword_8F7B08);
      case 4:
        sub_423200(dword_8F7B08, 58);
        return sub_423380(dword_8F7B08);
      case 6:
        sub_423200(dword_8F7B08, 95);
        v3 = sub_48FCE0(*(this + 2004));
        if ( v3 == -1 )
          LOBYTE(v3) = -1;
        v4[0] = v3;
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
int /*thiscall*/ sub_4AF8B0(uint32_t *this, int a2)
{
  return *(this + a2 + 1617) == *(this + a2 + 1879) ? 0 : *(this + a2 + 1617);
}



// ------------------------------------------------------------
// 0x4AF8E0 sub_4AF8E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AF8E0(int this, int a2)
{
  uint64_t v3; // rax
  int v4; // eax

  sub_4D4CE0((char *)this, a2);
  if ( *(uint32_t *)(this + 512) == 4 )
  {
    *(uint32_t *)(this + 512) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1176))(this);
    *(uint8_t *)(this + 516) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1180))(this);
  }
  if ( *(uint32_t *)(this + 520) == -1 )
    *(uint32_t *)(this + 520) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1184))(this);
  if ( *(uint32_t *)(this + 524) == -1082130432 )
    *(float *)(this + 524) = ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)this + 1188))(this);
  LODWORD(v3) = *(uint32_t *)(this + 520);
  if ( (int)v3 > 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
    v3 = (uint64_t)((2.0 - COERCE_FLOAT(sub_41A5E0(v4 + 1292))) * (double)*(int *)(this + 520));
    *(uint32_t *)(this + 520) = v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4AF9A0 sub_4AF9A0
// ------------------------------------------------------------
char /*thiscall*/ sub_4AF9A0(void *this, int a2)
{
  char result; // al
  int v4; // ebx

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    v4 = a2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, a2) != 0 )
    {
      sub_423200(dword_8F7B08, 50);
      a2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
      sub_423290(&a2, 2);
      a2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
      sub_423290(&a2, 2);
      HIBYTE(a2) = 3;
      sub_423290((char *)&a2 + 3, 1);
      a2 = v4;
      sub_423290(&a2, 2);
      a2 = 1;
      sub_423290(&a2, 4);
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
char /*thiscall*/ sub_4AFA70(void *this, int a2, int a3)
{
  char result; // al
  int v5; // edi

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    v5 = a2;
    if ( (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, a2) != 0 )
    {
      sub_423200(dword_8F7B08, 18);
      HIBYTE(a2) = 3;
      sub_423290((char *)&a2 + 3, 1);
      HIBYTE(a2) = 1;
      sub_423290((char *)&a2 + 3, 1);
      a2 = a3;
      sub_423290(&a2, 2);
      a2 = v5;
      sub_423290(&a2, 2);
      a2 = 1;
      sub_423290(&a2, 4);
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
int /*thiscall*/ sub_4AFB30(int *this, uint32_t *a2, int a3, int a4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *((uint8_t *)this + 404) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 8);
  }
  return sub_4D6D90(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x4AFB80 sub_4AFB80
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFB80(uint32_t *this, int a2, int a3, char a4)
{
  int v5; // ecx

  v5 = *(this + 1996);
  if ( v5 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1000))(this) != 0
    && a4 == 0
    && *((float *)this + 1997) * 100.0 > (double)(int)sub_445870(87723146, 10000) )
  {
    *((uint8_t *)this + 7992) = 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4AFBF0 sub_4AFBF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFBF0(uint8_t *this, uint32_t *a2, int a3)
{
  int result; // eax

  result = sub_4D5A60(this, a2, a3);
  if ( result != 3 && *(this + 7992) != 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x4AFC30 sub_4AFC30
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC30(uint32_t *this, int a2, int a3, int a4)
{
  *((uint8_t *)this + 7992) = 0;
  return sub_4D4A80(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x4AFC40 sub_4AFC40
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFC40(void *this, int a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 792))(this, a2);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 268))(result);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFC80 sub_4AFC80
// ------------------------------------------------------------
char /*thiscall*/ sub_4AFC80(uint32_t *this, int a2, int a3, char a4)
{
  int v5; // ecx
  int v6; // eax
  int v8; // [esp-8h] [ebp-10h]

  if ( a2 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) )
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 4 && *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) == 3 )
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) - a2;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1216))(this);
      sub_4527A0(v6, v8);
    }
    else if ( v5 == 6 )
    {
      sub_42B510(*(uint32_t *)(dword_8F7A24 + 40));
    }
  }
  return sub_4D5900(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x4AFD00 sub_4AFD00
// ------------------------------------------------------------
bool /*thiscall*/ sub_4AFD00(uint32_t *this)
{
  int v2; // eax
  bool result; // al

  result = false;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1196))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    v2 = *(this + 1639);
    if ( v2 == 0 || v2 == 11 || v2 == 8 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 171) > 0 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFD50 sub_4AFD50
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFD50(uint8_t *this, char a2)
{
  int result; // eax
  bool v4; // al
  char v5; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v4 = *(this + 7730) != 0 && a2 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1140))(this, 170) > 0;
    v5 = v4;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 169);
    return sub_47E440(v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFDB0 sub_4AFDB0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4AFDB0(uint8_t **this, int a2, int a3)
{
  uint8_t *result; // eax
  uint8_t **v5; // esi
  int i; // ebx

  result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **))*this + 77))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = this + 1617;
    for ( i = 18; i != 0; --i )
    {
      result = *v5;
      if ( *v5 != nullptr )
        result = (uint8_t *)(*(int (/*stdcall*/ **)(int *, int *))(*(uint32_t *)result + 144))(&a2, &a3);
      ++v5;
    }
  }
  if ( (uint8_t **)dword_8F7C04 == this )
  {
    result = (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int))*this + 290))(this, a2);
    if ( result[376] != 0 )
      return (uint8_t *)(*((int (/*thiscall*/ **)(uint8_t **, int, int))*this + 324))(this, a2, a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4AFE30 sub_4AFE30
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFE30(uint32_t *this, int a2, int a3)
{
  int result; // eax

  if ( a3 == 1 )
    result = 0;
  else
    result = dword_9B7410[a3];
  *(this + 1797) = a2 - result;
  *(this + 1798) = dword_9B7414[a3] - result;
  *(this + 1799) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x4AFE70 sub_4AFE70
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFE70(uint32_t *this, int a2, int a3, int a4)
{
  *(this + 1800) = a2;
  *(this + 1802) = a3;
  *(this + 1801) = a4;
  return a4;
}



// ------------------------------------------------------------
// 0x4AFEA0 sub_4AFEA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4AFEA0(uint8_t *this, char a2)
{
  int v2; // edx

  v2 = *(uint32_t *)this;
  *(this + 7730) = a2;
  return (*(int (**)(void))(v2 + 1316))();
}



// ------------------------------------------------------------
// 0x4AFEC0 sub_4AFEC0
// ------------------------------------------------------------
char /*thiscall*/ sub_4AFEC0(uint32_t *this)
{
  int v1; // eax
  int v3; // esi

  LOBYTE(v1) = dword_8F7C04;
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
    LOBYTE(v1) = *((uint8_t *)this + 7730);
    if ( (uint8_t)v1 != 0 )
    {
      v1 = *(this + 1639);
      switch ( v1 )
      {
        case 0:
          byte_9A03B0 = 1;
          byte_9A03DC = 1;
          goto LABEL_5;
        case 6:
          v1 = *(this + 1723);
          if ( v1 == 1 )
          {
            v1 = *(this + 1724);
            if ( v1 < *(this + 1725) )
            {
              LOBYTE(v1) = *((uint8_t *)this + 6988);
              byte_9A0358 = (uint8_t)v1 == 0;
            }
          }
          break;
        case 8:
          byte_9A0358 = 1;
          byte_9A0384 = 1;
          LOBYTE(v1) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1328))(this, 1);
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
          LOBYTE(v1) = sub_47E440(1);
          break;
        default:
          return v1;
      }
    }
    else
    {
      v3 = *(this + 1639);
      if ( v3 != 0 )
      {
        byte_9A0384 = v3 == 11;
      }
      else
      {
        byte_9A03B0 = 1;
        byte_9A03DC = 1;
        byte_9A0384 = 1;
      }
    }
  }
  return v1;
}


