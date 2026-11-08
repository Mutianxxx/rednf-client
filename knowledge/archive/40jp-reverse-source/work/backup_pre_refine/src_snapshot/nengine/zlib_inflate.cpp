// ============================================================
// 【40JP逆向源代码工程】nengine/zlib_inflate.cpp
// 模块: zlib 解压/内嵌浏览器/寻路
// 来源: work/dump_tail.txt  区块: 0x650000-0x660000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 153
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x650030 sub_650030
// ------------------------------------------------------------
int /*thiscall*/ sub_650030(int this)
{
  int v2; // ecx
  int result; // eax

  v2 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 88) = -1;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 1;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 776))(v2, 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 768))(
      *(uint32_t *)(this + 4),
      3,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6500A0 sub_6500A0
// ------------------------------------------------------------
char /*thiscall*/ sub_6500A0(uint32_t *this, char a2)
{
  char result; // al
  int v3; // esi

  result = a2;
  if ( a2 == 0 )
  {
    v3 = *(this + 1);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v3 + 272))(v3, 0, 0);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v3 + 612))(v3, 0, 0);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 820))(v3, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6500E0 sub_6500E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6500E0(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = -1;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650100 sub_650100
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650100@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  uint32_t *result; // eax
  int *v5; // edi
  int v6; // ebx
  int v7; // ebx
  int *v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  char v16; // bl
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v24; // [esp+4h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 840))(*(uint32_t *)(a1 + 80));
  if ( result == (uint32_t *)24 )
  {
    v5 = *(int **)(a1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 200))(*(uint32_t *)(a1 + 80));
      v6 = (int)result;
      if ( result != nullptr )
      {
        if ( (*(int (/*thiscall*/ **)(int *, int, int))(*v5 + 236))(v5, a2, a3) == 1 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
        sub_4938F0(v6);
        v7 = *(uint32_t *)(v6 + 148);
        if ( v7 != *(uint32_t *)(a1 + 84) )
        {
          v8 = *(int **)(a1 + 80);
          if ( v7 >= 9 )
          {
            v9 = *v8;
            if ( v7 == 9 )
            {
              v10 = (*(int (**)(void))(v9 + 152))();
              v11 = *(uint32_t *)(a1 + 4);
              *(uint32_t *)(a1 + 88) = v10 != 0 ? 37 : -37;
              *(uint32_t *)(a1 + 92) = -1;
              if ( 65 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 192))(v11) <= 0 )
                v12 = 0;
              else
                v12 = 65 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 192))(*(uint32_t *)(a1 + 4));
            }
            else
            {
              v13 = (*(int (**)(void))(v9 + 152))();
              v14 = *(uint32_t *)(a1 + 4);
              *(uint32_t *)(a1 + 88) = v13 != 0 ? 58 : -58;
              *(uint32_t *)(a1 + 92) = -1;
              if ( 113 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 192))(v14) <= 20 )
                v12 = 20;
              else
                v12 = 113 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 192))(*(uint32_t *)(a1 + 4));
            }
            *(uint32_t *)(a1 + 96) = v12;
          }
          else
          {
            *(uint32_t *)(a1 + 88) = (*(int (/*thiscall*/ **)(int *))(*v8 + 152))(v8) != 0 ? 80 : -80;
            *(uint32_t *)(a1 + 92) = -1;
            *(uint32_t *)(a1 + 96) = 0;
          }
          *(uint32_t *)(a1 + 84) = v7;
        }
        v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80));
        v16 = sub_432E50(v15);
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v16;
        v17 = *v5;
        v24 = *(uint32_t *)(a1 + 80);
        v18 = (*(int (**)(void))(*(uint32_t *)v24 + 128))();
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v24 + 124))(v24, *(uint32_t *)(a1 + 96) + v18);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v24 + 120))(v24, *(uint32_t *)(a1 + 92) + v19);
        (*(void (/*thiscall*/ **)(int *, int))(v17 + 112))(v5, *(uint32_t *)(a1 + 88) + v20);
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        if ( result != nullptr )
        {
          v21 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
          return sub_4938F0(v21);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6502E0 sub_6502E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6502E0(uint32_t *this)
{
  int v2; // ecx
  int result; // eax

  v2 = *(this + 1);
  *(this + 21) = -1;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 776))(v2, 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 768))(*(this + 1), 3, 0, 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 556))(*(this + 1), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650340 sub_650340
// ------------------------------------------------------------
int /*thiscall*/ sub_650340(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = -1;
  *(this + 22) = -1;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650360 sub_650360
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650360@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<esi>)
{
  uint32_t *result; // eax
  int *v5; // esi
  uint32_t *v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  char v10; // bl
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v18; // [esp+4h] [ebp-4h]
  int v19; // [esp+4h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 840))(*(uint32_t *)(a1 + 80));
  if ( result == (uint32_t *)10 )
  {
    v5 = *(int **)(a1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 200))(*(uint32_t *)(a1 + 80));
      v6 = result;
      if ( result != nullptr )
      {
        sub_4938F0((int)result);
        v18 = v6[37];
        v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 80) + 1288))(*(uint32_t *)(a1 + 80), a2, a3);
        if ( v7 != *(uint32_t *)(a1 + 84) || v18 != *(uint32_t *)(a1 + 88) )
        {
          if ( v7 != 0 )
          {
            *(uint32_t *)(a1 + 92) = 0;
            *(uint32_t *)(a1 + 96) = 1;
            if ( 93 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) / 2 <= 40 )
              v8 = 40;
            else
              v8 = 93 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) / 2;
            *(uint32_t *)(a1 + 100) = v8;
          }
          else
          {
            *(uint32_t *)(a1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80)) != 0
                                 ? 60
                                 : -60;
            *(uint32_t *)(a1 + 96) = -1;
            if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )
              *(uint32_t *)(a1 + 100) = 0;
            else
              *(uint32_t *)(a1 + 100) = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);
          }
          *(uint32_t *)(a1 + 84) = v7;
          *(uint32_t *)(a1 + 88) = v18;
        }
        v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80));
        v10 = sub_432E50(v9);
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v10;
        v11 = *v5;
        v19 = *(uint32_t *)(a1 + 80);
        v12 = (*(int (**)(void))(*(uint32_t *)v19 + 128))();
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v19 + 124))(v19, *(uint32_t *)(a1 + 100) + v12);
        v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v19 + 120))(v19, *(uint32_t *)(a1 + 96) + v13);
        (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v5, *(uint32_t *)(a1 + 92) + v14);
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        if ( result != nullptr )
        {
          v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
          return sub_4938F0(v15);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x650540 sub_650540
// ------------------------------------------------------------
int /*thiscall*/ sub_650540(int this)
{
  *(uint32_t *)(this + 80) = 17;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint8_t *)(this + 92) = 0;
  *(uint8_t *)(this + 93) = 1;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650560 sub_650560
// ------------------------------------------------------------
int /*thiscall*/ sub_650560(void *this, int a2, float a3, int a4, int a5, int a6, int a7)
{
  return (*(int (/*fastcall*/ **)(void *, uint32_t, int, uint32_t, int, int, int, int))(*(uint32_t *)this + 120))(
           this,
           (uint64_t)a3 >> 32,
           a2,
           (uint64_t)a3,
           a4,
           a5,
           a6,
           a7);
}



// ------------------------------------------------------------
// 0x6505A0 sub_6505A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6505A0(uint32_t *this, int a2)
{
  int result; // eax
  uint32_t *v3; // edx

  result = 0;
  v3 = (uint32_t *)(a2 + 24);
  while ( *v3 != 17 )
  {
    ++result;
    ++v3;
    if ( result >= 3 )
    {
      result = 2;
      break;
    }
  }
  *(uint32_t *)(a2 + 4 * result + 24) = *(this + 20);
  *(uint32_t *)(a2 + 4 * result + 36) = *(this + 21);
  *(uint32_t *)(a2 + 4 * result + 48) = *(this + 22);
  return result;
}



// ------------------------------------------------------------
// 0x6505F0 sub_6505F0
// ------------------------------------------------------------
char /*thiscall*/ sub_6505F0(uint32_t *this, int a2)
{
  char result; // al
  int v3; // eax
  uint8_t v4; // al

  result = *(uint8_t *)(a2 + 176);
  if ( result == 0 && *(this + 20) == 2 )
  {
    v3 = sub_699000((int)(this + 2));
    v4 = sub_42B420(50, 170, v3, 500);
    return sub_491690(1, 0, 1, -4449923, (v4 << 24) | 0xFFFFFF, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650650 sub_650650
// ------------------------------------------------------------
void /*thiscall*/ sub_650650(int this)
{
  int v1; // ebx
  int v2; // esi
  int v3; // esi
  int v4; // ecx
  int v5; // eax
  uint32_t *v6; // edx
  int v7; // ecx
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  uint32_t *v12; // eax
  int v13; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  uint32_t *i; // [esp+14h] [ebp-10h]
  int v17; // [esp+1Ch] [ebp-8h]
  char v18; // [esp+23h] [ebp-1h]

  v1 = this;
  v18 = 0;
  if ( *(uint32_t *)(this + 96) != (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) )
  {
    v18 = 1;
    *(uint32_t *)(v1 + 96) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v1 + 4) + 200))(*(uint32_t *)(v1 + 4));
  }
  v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 792))(*(uint32_t *)(v1 + 4), 8);
  if ( v2 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 40))(*(uint32_t *)(v1 + 4), 273) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 1084))(*(uint32_t *)(v1 + 4), 8);
  }
  if ( *(uint32_t *)(v1 + 100) == v2 )
  {
    if ( v18 == 0 )
      return;
  }
  else
  {
    *(uint32_t *)(v1 + 100) = v2;
  }
  v3 = v1 + 104;
  if ( *(uint32_t *)(v1 + 108) != 0 )
    j__free(*(void **)(v1 + 108));
  *(uint32_t *)(v1 + 108) = 0;
  *(uint32_t *)(v1 + 112) = 0;
  *(uint32_t *)(v1 + 116) = 0;
  if ( *(uint32_t *)(v1 + 96) != 0 )
  {
    v4 = *(uint32_t *)(v1 + 100);
    if ( v4 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 248))(v4);
      v6 = *(uint32_t **)(v5 + 4);
      v13 = v5;
      for ( i = v6; v6 != *(uint32_t **)(v13 + 8); i = v6 )
      {
        v7 = *(uint32_t *)(v1 + 96) + 200;
        v14 = *v6;
        v8 = *(uint32_t **)(*(uint32_t *)(v1 + 96) + 204);
        v9 = (uint32_t *)*v8;
        v17 = v7;
        if ( (uint32_t *)*v8 != v8 )
        {
          do
          {
            if ( v9[2] == v14 )
            {
              v10 = *(uint32_t *)(v3 + 4);
              if ( v10 != 0 )
                v11 = (*(uint32_t *)(v3 + 8) - v10) >> 2;
              else
                v11 = 0;
              if ( v10 != 0 && v11 < (*(uint32_t *)(v3 + 12) - v10) >> 2 )
              {
                v12 = *(uint32_t **)(v3 + 8);
                *v12 = v9[3];
                *(uint32_t *)(v3 + 8) = v12 + 1;
              }
              else
              {
                sub_42AC90(*(void **)(v3 + 8), 1, (int)(v9 + 3));
              }
              v7 = v17;
              v1 = this;
            }
            v9 = (uint32_t *)*v9;
          }
          while ( v9 != *(uint32_t **)(v7 + 4) );
          v6 = i;
        }
        v6 += 31;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x6507C0 sub_6507C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6507C0(int this, char a2, int a3, int a4, int a5)
{
  int *i; // esi

  if ( a2 == 0 && *(uint8_t *)(this + 93) != 0 )
  {
    sub_650650(this);
    for ( i = *(int **)(this + 108); i != *(int **)(this + 112); ++i )
      sub_6505F0((uint32_t *)this, *i);
  }
}



// ------------------------------------------------------------
// 0x650800 sub_650800
// ------------------------------------------------------------
int /*thiscall*/ sub_650800(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 22) = 0;
  *(this + 24) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650820 sub_650820
// ------------------------------------------------------------
void /*thiscall*/ sub_650820(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // edx
  double v7; // st7
  int v8; // eax
  int v9; // edx
  float v10; // [esp+0h] [ebp-28h]
  float v11; // [esp+0h] [ebp-28h]
  float v12; // [esp+4h] [ebp-24h]
  float v13; // [esp+4h] [ebp-24h]
  float v14; // [esp+20h] [ebp-8h]
  float v15; // [esp+24h] [ebp-4h]

  v3 = *(this + 1);
  v14 = (double)(*(int (/*fastcall*/ **)(int))(*(uint32_t *)v3 + 736))(v3) * 100.0;
  v15 = v14 / (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 740))(v3);
  if ( (double)(int)*(this + 20) >= v15 )
  {
    v12 = (float)(int)*(this + 22);
    v10 = (float)(int)*(this + 21);
    v4 = (uint64_t)sub_4049C0(
                             v10,
                             v12,
                             (uint64_t)(((double)(int)*(this + 20) - v15) * 1000.0),
                             (uint64_t)(1000.0 * (double)(int)*(this + 20)));
    v5 = sub_41A5E0(a2 + 60);
    sub_41A590(a2 + 60, v6, v4 + v5);
    v13 = (float)(int)*(this + 24);
    v11 = (float)(int)*(this + 23);
    v7 = sub_4049C0(
           v11,
           v13,
           (uint64_t)(((double)(int)*(this + 20) - v15) * 1000.0),
           (uint64_t)(1000.0 * (double)(int)*(this + 20)));
    v8 = sub_41A5E0(a2 + 466);
    sub_41A590(a2 + 466, v9, (uint64_t)v7 + v8);
  }
}



// ------------------------------------------------------------
// 0x650950 sub_650950
// ------------------------------------------------------------
int /*thiscall*/ sub_650950(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  int result; // eax

  v3 = (uint32_t *)sub_47E720(0, 19);
  *(this + 20) = sub_47E9D0(v3, 0);
  *(this + 21) = sub_47EF20(0, a2, -1, -1, 11);
  *(this + 22) = sub_47EF20(1, a2, -1, -1, 11);
  *(this + 23) = sub_47EF20(2, a2, -1, -1, 11);
  result = sub_47EF20(3, a2, -1, -1, 11);
  *(this + 24) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6509D0 sub_6509D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6509D0(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6509F0 sub_6509F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6509F0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 27) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x650A10 sub_650A10
// ------------------------------------------------------------
int /*thiscall*/ sub_650A10(int this, int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // edx
  int v10; // ebx
  unsigned int v11; // edi
  int result; // eax
  int v13; // eax
  int v14; // [esp+Ch] [ebp-4h]
  float v15; // [esp+Ch] [ebp-4h]
  float v16; // [esp+Ch] [ebp-4h]
  float v17; // [esp+Ch] [ebp-4h]
  float v18; // [esp+Ch] [ebp-4h]
  int v19; // [esp+18h] [ebp+8h]
  int v20; // [esp+18h] [ebp+8h]
  int v21; // [esp+18h] [ebp+8h]
  int v22; // [esp+18h] [ebp+8h]
  int v23; // [esp+18h] [ebp+8h]
  int v24; // [esp+18h] [ebp+8h]

  v14 = *(uint32_t *)(this + 80);
  v4 = sub_41A5E0(a2 + 60);
  sub_41A590(a2 + 60, v5, v14 + v4);
  v15 = *(float *)(this + 100);
  *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(a2 + 1054)) + v15;
  sub_41A590(a2 + 1054, v6, v19);
  v20 = *(uint32_t *)(this + 84);
  v7 = sub_41A5E0(a2 + 116);
  sub_41A590(a2 + 116, v20, v20 + v7);
  v16 = *(float *)(this + 104);
  *(float *)&v21 = COERCE_FLOAT(sub_41A5E0(a2 + 1110)) + v16;
  sub_41A590(a2 + 1110, v8, v21);
  v17 = (double)*(int *)(this + 88) * 0.001;
  *(float *)&v22 = COERCE_FLOAT(sub_41A5E0(a2 + 830)) + v17;
  sub_41A590(a2 + 830, v22, v22);
  v18 = (double)*(int *)(this + 92) * 0.001;
  *(float *)&v23 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v18;
  sub_41A590(a2 + 858, v9, v23);
  v10 = 0;
  v11 = a2 + 284;
  do
  {
    result = sub_497040(v10);
    if ( result != 17 )
    {
      v24 = *(uint32_t *)(this + 96);
      v13 = sub_41A5E0(v11);
      result = sub_41A590(v11, v24, v24 + v13);
    }
    ++v10;
    v11 += 14;
  }
  while ( v10 < 16 );
  return result;
}



// ------------------------------------------------------------
// 0x650B50 sub_650B50
// ------------------------------------------------------------
int /*thiscall*/ sub_650B50(int this, int a2)
{
  int result; // eax

  sub_47E720(0, 40);
  *(uint32_t *)(this + 44) = sub_47EF20(0, a2, -1, -1, 11);
  *(uint32_t *)(this + 80) = sub_47EF20(1, a2, -1, -1, 11);
  *(float *)(this + 100) = (double)(int)sub_47EF20(2, a2, -1, -1, 11) * -0.0099999998;
  *(float *)(this + 104) = (double)(int)sub_47EF20(3, a2, -1, -1, 11) * -0.0099999998;
  *(uint32_t *)(this + 84) = -sub_47EF20(4, a2, -1, -1, 11);
  *(uint32_t *)(this + 88) = sub_47EF20(5, a2, -1, -1, 11);
  *(uint32_t *)(this + 92) = sub_47EF20(6, a2, -1, -1, 11);
  result = sub_47EF20(7, a2, -1, -1, 11);
  *(uint32_t *)(this + 96) = result;
  return result;
}



// ------------------------------------------------------------
// 0x650C30 sub_650C30
// ------------------------------------------------------------
void /*thiscall*/ sub_650C30(int *this)
{
  int v2; // esi
  uint32_t *v3; // eax
  int *v4; // eax
  int v5; // edx
  int v6; // ebx
  int v7; // eax
  void *v8; // eax
  int v9; // [esp-Ch] [ebp-38h]
  int v10; // [esp-8h] [ebp-34h]
  int v11; // [esp-4h] [ebp-30h]
  uint8_t v12[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *v14; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  sub_5F66C0();
  v2 = *(this + 1);
  if ( *(this + 27) == 0 )
  {
    v3 = operator new(0x12Cu);
    v14 = v3;
    v15 = 0;
    if ( v3 != nullptr )
      v4 = sub_428F30(v3, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", v2);
    else
      v4 = nullptr;
    *(this + 27) = (int)v4;
    v5 = *v4;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(v4, v2);
  }
  v6 = *(uint32_t *)*(this + 27);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 128))(v2) + 50;
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 124))(v2);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
  (*(void (/*thiscall*/ **)(uint32_t))(v6 + 40))(*(this + 27));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 27) + 92))(*(this + 27), v12);
  v7 = *(uint32_t *)v2;
  v15 = 1;
  v8 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, uint8_t *))(v7 + 80))(v2, 2, 0, v12);
  sub_4600B0(v8, v9, v10, v11);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x650D20 sub_650D20
// ------------------------------------------------------------
int /*thiscall*/ sub_650D20(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650D30 sub_650D30
// ------------------------------------------------------------
int /*thiscall*/ sub_650D30(int this, int a2)
{
  *(uint32_t *)(this + 80) = a2;
  *(uint8_t *)(this + 40) = 0;
  return a2;
}



// ------------------------------------------------------------
// 0x650D50 sub_650D50
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_650D50@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<esi>)
{
  uint32_t *result; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  char v10; // bl
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v17; // [esp+8h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 840))(*(uint32_t *)(a1 + 80));
  if ( result == (uint32_t *)22 )
  {
    v5 = *(int **)(a1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      if ( (*(int (/*thiscall*/ **)(int *, int))(*v5 + 236))(v5, a3) == 1 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*v5 + 688))(v5, a2) + 16) != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
        if ( *(uint32_t *)(v6 + 16) != (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) )
        {
          v7 = *v5;
          v8 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v7 + 196))(v5, *(uint32_t *)(v8 + 16));
        }
      }
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80));
      v10 = sub_432E50(v9);
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v10;
      v11 = *v5;
      v17 = *(uint32_t *)(a1 + 80);
      v12 = (*(int (**)(void))(*(uint32_t *)v17 + 128))();
      v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 124))(v17, *(uint32_t *)(a1 + 92) + v12);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 120))(v17, *(uint32_t *)(a1 + 88) + v13);
      (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v5, *(uint32_t *)(a1 + 84) + v14);
      (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
      if ( result != nullptr )
      {
        v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        return sub_4938F0(v15);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x650E80 sub_650E80
// ------------------------------------------------------------
int /*thiscall*/ sub_650E80(int this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80));
  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 84) = v2 != 0 ? 43 : -43;
  *(uint32_t *)(this + 88) = -1;
  if ( 110 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 192))(v3) <= 10 )
    v4 = 10;
  else
    v4 = 110 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
  *(uint32_t *)(this + 92) = v4;
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 3);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 768))(
      *(uint32_t *)(this + 4),
      3,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 556))(*(uint32_t *)(this + 4), 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x650F20 sub_650F20
// ------------------------------------------------------------
int /*thiscall*/ sub_650F20(int this)
{
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 1065353216;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 184) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x650F70 sub_650F70
// ------------------------------------------------------------
int /*thiscall*/ sub_650F70(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 39;
  for ( i = 3; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x650FA0 sub_650FA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_650FA0(uint32_t *this, int a2)
{
  return (uint8_t)sub_4E4630(a2) != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2) <= *(this + 37)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 624))(a2) != 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 724))(a2) == 0;
}



// ------------------------------------------------------------
// 0x651000 sub_651000
// ------------------------------------------------------------
int /*thiscall*/ sub_651000(int this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  double v7; // st7
  uint32_t *v8; // ebx
  int i; // esi
  int *v10; // edi
  int v11; // [esp+8h] [ebp+8h]
  float v12; // [esp+Ch] [ebp+Ch]

  result = a2;
  *(uint32_t *)(this + 128) = a3;
  *(uint32_t *)(this + 140) = a4;
  *(uint32_t *)(this + 144) = a5;
  *(uint32_t *)(this + 84) = a2;
  *(uint32_t *)(this + 148) = a6;
  if ( a2 != 0 )
  {
    v7 = (double)a2 * 0.0083333338;
    v8 = (uint32_t *)(this + 160);
    v11 = 2;
    v12 = v7 / *(float *)(this + 152);
    *(float *)(this + 152) = v7;
    do
    {
      for ( i = 12; i < 24; i += 4 )
      {
        v10 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 36))(*v8) + i);
        *v10 = (uint64_t)((double)*v10 * v12);
      }
      ++v8;
      result = --v11;
    }
    while ( v11 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x6510A0 sub_6510A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6510A0(int this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
             *(uint32_t *)(this + 4),
             "QUAKE_WAVE_READY_LOOP",
             7,
             0,
             0);
  *(uint8_t *)(this + 184) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6510D0 sub_6510D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6510D0(int this, uint32_t *a2)
{
  int v4; // eax
  float v5; // [esp+4h] [ebp-28h]
  float v6; // [esp+34h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 273) != 0 )
    v6 = *(float *)(this + 144);
  else
    v6 = *(float *)(this + 140);
  if ( operator new(0x80u) != nullptr )
  {
    v5 = -v6;
    v4 = sub_4D6810(LODWORD(v5), -1, 1, 2);
  }
  else
  {
    v4 = 0;
  }
  (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v4 + 56))(
    v4,
    a2,
    *(uint32_t *)(this + 4),
    0,
    0,
    0,
    -1);
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0
    && *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4))
                             + 132)
                 + 52) == *(uint32_t *)(this + 4) )
  {
    sub_4684F0(*((uint32_t *)dword_8F8528 + 4), a2);
  }
}



// ------------------------------------------------------------
// 0x6511B0 sub_6511B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_6511B0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; ++result )
    *result = *v3++;
  return result;
}



// ------------------------------------------------------------
// 0x6511E0 sub_6511E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6511E0(int this)
{
  uint32_t *v2; // edi
  int i; // ebx

  sub_64A570();
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  v2 = (uint32_t *)(this + 156);
  for ( i = 3; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v2 + 12))(*v2, 0);
    ++v2;
  }
  if ( *(uint32_t *)(this + 172) != 0 )
    j__free(*(void **)(this + 172));
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
           *(uint32_t *)(this + 4),
           "QUAKE_WAVE_READY_LOOP",
           7,
           0,
           0);
}



// ------------------------------------------------------------
// 0x651260 sub_651260
// ------------------------------------------------------------
void /*thiscall*/ sub_651260(int this, int a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  uint32_t *i; // edi

  sub_64A360(a2);
  if ( (uint8_t)a2 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4)) != 0 )
    {
      v3 = __RTDynamicCast(
             *(uint32_t *)(this + 4),
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNSwordman `RTTI Type Descriptor',
             0);
      v4 = v3;
      if ( v3 != 0 )
      {
        v5 = *(uint32_t *)v3;
        v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1140))(v3, 52);
        (*(void (/*thiscall*/ **)(int, int, int))(v5 + 1296))(v4, 52, v6);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v4 + 212))(
          v4,
          "SM_GHOSTSTEP",
          -1,
          0,
          0);
      }
    }
    for ( i = *(uint32_t **)(this + 172); i != *(uint32_t **)(this + 176); ++i )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 84))(*i, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 7);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 8);
    *(uint8_t *)(this + 184) = 0;
  }
  if ( *(uint32_t *)(this + 172) != 0 )
    j__free(*(void **)(this + 172));
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
}



// ------------------------------------------------------------
// 0x651350 sub_651350
// ------------------------------------------------------------
void /*thiscall*/ sub_651350(uint32_t *this, int a2)
{
  unsigned int i; // ebx
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // edi
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  uint32_t *v16; // eax

  if ( a2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == a2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * i);
        else
          v11 = 0;
        v12 = *(this + 1);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 64))(v11) + 32) == v12 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
            v15 = *(uint32_t *)(v14 + 4 * i);
          else
            v15 = 0;
          v16 = (uint32_t *)__RTDynamicCast(
                            v15,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNChangeHp `RTTI Type Descriptor',
                            0);
          if ( v16 != nullptr && v16[25] == 2 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v16 + 76))(v16, 0);
            return;
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x651450 sub_651450
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_651450(int this, int a2)
{
  int v2; // edi
  uint32_t *i; // edi
  uint32_t *v5; // ecx
  uint32_t *result; // eax

  v2 = a2;
  sub_64A5E0(a2);
  if ( a2 == *(uint32_t *)(this + 4) )
  {
    for ( i = *(uint32_t **)(this + 172); i != *(uint32_t **)(this + 176); ++i )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 84))(*i, 0);
    if ( *(uint32_t *)(this + 172) != 0 )
      j__free(*(void **)(this + 172));
    v2 = a2;
    *(uint32_t *)(this + 172) = 0;
    *(uint32_t *)(this + 176) = 0;
    *(uint32_t *)(this + 180) = 0;
  }
  v5 = *(uint32_t **)(this + 176);
  result = *(uint32_t **)(this + 172);
  if ( result != v5 )
  {
    do
    {
      if ( *result == v2 )
        break;
      ++result;
    }
    while ( result != v5 );
    if ( result != v5 )
    {
      memcpy_0(result, result + 1, 4 * ((*(uint32_t *)(this + 176) - (int)(result + 1)) >> 2));
      result = (uint32_t *)(*(uint32_t *)(this + 176) - 4);
      *(uint32_t *)(this + 176) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x651510 sub_651510
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_651510(int this, uint32_t *Src, uint32_t *a3, uint32_t *a4, int a5)
{
  int v6; // edx
  unsigned int v7; // ecx
  unsigned int result; // eax
  int v9; // edi
  int v10; // edi
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax
  char *v14; // ebx
  size_t v15; // edi
  char *v16; // eax
  uint32_t *v17; // eax
  int v18; // ecx
  int v19; // eax
  unsigned int v20; // edi
  int v21; // ebx
  uint32_t *v23; // ebx
  const void *v24; // [esp-Ch] [ebp-34h]
  uint32_t *v25; // [esp-Ch] [ebp-34h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  unsigned int v29; // [esp+14h] [ebp-14h]
  int *v30; // [esp+18h] [ebp-10h]
  int v31; // [esp+24h] [ebp-4h]
  int Srca; // [esp+30h] [ebp+8h]
  void *Srcb; // [esp+30h] [ebp+8h]

  v6 = *(uint32_t *)(this + 4);
  v7 = a4 - a3;
  v30 = &v26;
  v29 = v7;
  if ( v6 != 0 )
    result = (*(uint32_t *)(this + 12) - v6) >> 2;
  else
    result = 0;
  if ( v7 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 2;
    else
      v9 = 0;
    if ( 0x3FFFFFFF - v9 < v7 )
      sub_42CB90(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 2;
    else
      v10 = 0;
    if ( result >= v7 + v10 )
    {
      v21 = *(uint32_t *)(this + 8);
      if ( (v21 - (int)Src) >> 2 >= v7 )
      {
        Srcb = (void *)(v21 - 4 * v7);
        *(uint32_t *)(this + 8) = sub_55E7F0(Srcb, v21, *(void **)(this + 8));
        sub_5DAF70(Src, (int)Srcb, v21);
        return (unsigned int)sub_6511B0(a3, a4, Src);
      }
      else
      {
        Srca = 4 * v7;
        sub_55E7F0(Src, v21, &Src[v7]);
        v23 = &a3[(*(uint32_t *)(this + 8) - (int)Src) >> 2];
        v25 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_497E70(v23, a4, v25);
        *(uint32_t *)(this + 8) += Srca;
        return (unsigned int)sub_6511B0(a3, v23, Src);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v11 = (result >> 1) + result;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 2;
      else
        v12 = 0;
      if ( v11 < v7 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 2;
        else
          v13 = 0;
        v11 = v7 + v13;
      }
      v28 = 4 * v11;
      v14 = (char *)operator new(4 * v11);
      v15 = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      v24 = *(const void **)(this + 4);
      Block = v14;
      v31 = 0;
      v16 = (char *)memcpy_0(v14, v24, v15);
      v17 = sub_497E70(a3, a4, &v16[v15]);
      memcpy_0(v17, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
      v18 = *(uint32_t *)(this + 4);
      if ( v18 != 0 )
        v19 = (*(uint32_t *)(this + 8) - v18) >> 2;
      else
        v19 = 0;
      v20 = v19 + v29;
      if ( v18 != 0 )
        j__free(*(void **)(this + 4));
      result = (unsigned int)&v14[v28];
      *(uint32_t *)(this + 12) = &v14[v28];
      *(uint32_t *)(this + 8) = &v14[4 * v20];
      *(uint32_t *)(this + 4) = v14;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x651760 sub_651760
// ------------------------------------------------------------
char /*thiscall*/ sub_651760(void *this)
{
  double v2; // st7
  double v3; // st7
  char v5; // c0
  int v6; // ecx
  int v7; // edi
  int *v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int *v12; // edi
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  uint32_t *v17; // edi
  int v18; // eax
  void *v19; // eax
  int **v20; // eax
  bool v21; // zf
  int *v22; // eax
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // ecx
  char result; // al
  float v29; // [esp-4h] [ebp-34h]
  uint8_t v30[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int v35; // [esp+20h] [ebp-10h]
  int v36; // [esp+2Ch] [ebp-4h]

  sub_64A790();
  v35 = sub_699000((int)this + 8) - *((uint32_t *)this + 34);
  v2 = (double)v35;
  *((uint32_t *)this + 34) = sub_699000((int)this + 8);
  v3 = v2 * *((float *)this + 32) * 0.001 + *((float *)this + 33);
  *((float *)this + 33) = v3;
  if ( v5 == 0 )
  {
    v6 = *((uint32_t *)this + 1);
    v7 = (uint64_t)v3;
    v35 = v7;
    *((float *)this + 33) = v3 - (double)v7;
    if ( v7 > (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)v6 + 752))(v6, (uint64_t)v3 >> 32) )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 752))(*((uint32_t *)this + 1));
      v35 = v7;
    }
    if ( v7 > 0 )
    {
      v8 = *((int **)this + 1);
      v9 = *v8;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v8 + 752))(v8, 0);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 744))(v8, v10 - v35);
    }
  }
  v11 = 0;
  v35 = 0;
  do
  {
    v12 = *((int **)this + 1);
    v13 = *v12;
    v34 = **((uint32_t **)this + v11 + 39);
    v14 = (*(int (/*thiscall*/ **)(int *, bool))(v13 + 124))(v12, v11 == 1);
    v15 = (*(int (/*thiscall*/ **)(int *, int))(*v12 + 120))(v12, v14);
    v16 = v35;
    (*(void (/*thiscall*/ **)(uint32_t, int))(v34 + 40))(*((uint32_t *)this + v35 + 39), v15);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + v16 + 39) + 92))(*((uint32_t *)this + v16 + 39), v30);
    v36 = 0;
    if ( v16 == 0 )
    {
      v17 = Block;
      v18 = v32;
      if ( Block != (void *)v32 )
      {
        do
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v17 + 36))(*v17) + 8) = 2;
          v29 = *((float *)this + 38);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v17 + 96))(*v17);
          sub_4922F0(v29);
          v18 = v32;
          ++v17;
        }
        while ( v17 != (uint32_t *)v32 );
        v17 = Block;
      }
      sub_651510(*((void **)this + 44), (int)v17, v18, v34);
    }
    v19 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 80))(*((uint32_t *)this + 1));
    sub_4600B0(v19, 2, 0, (int)v30);
    v36 = -1;
    if ( Block != nullptr )
      j__free(Block);
    v11 = v16 + 1;
    Block = nullptr;
    v32 = 0;
    v33 = 0;
    v35 = v11;
  }
  while ( v11 < 3 );
  v20 = *((int ***)this + 43);
  v21 = v20 == *((int ***)this + 44);
  v35 = (int)v20;
  if ( !v21 )
  {
    do
    {
      v22 = *v20;
      v23 = *((uint32_t *)this + 1);
      v24 = *v22;
      v34 = (int)v22;
      v25 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v23 + 124))(v23, 0);
      v26 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v23 + 120))(v23, v25);
      (*(void (/*thiscall*/ **)(int, int))(v24 + 112))(v34, v26);
      v27 = *((uint32_t *)this + 44);
      v20 = (int **)(v35 + 4);
      v35 += 4;
    }
    while ( v35 != v27 );
  }
  result = *((uint8_t *)this + 184);
  if ( *((uint32_t *)this + 30) != 0 )
  {
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
                 *((uint32_t *)this + 1),
                 "QUAKE_WAVE_LOOP",
                 8,
                 0,
                 0);
      *((uint8_t *)this + 184) = 1;
    }
  }
  else if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 1) + 216))(*((uint32_t *)this + 1), 8);
    *((uint8_t *)this + 184) = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x6519E0 sub_6519E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6519E0(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax

  v7 = operator new(0x12Cu);
  if ( v7 != nullptr )
    v8 = sub_428F30(v7, (int)"Character/Swordman/Effect/Particle/DOTAreaQuake.ptl", 0);
  else
    v8 = nullptr;
  *(this + 39) = v8;
  v9 = operator new(0x12Cu);
  if ( v9 != nullptr )
    v10 = sub_428F30(v9, (int)"Character/Swordman/Effect/Particle/DOTAreaRock.ptl", 0);
  else
    v10 = nullptr;
  *(this + 40) = v10;
  v11 = operator new(0x12Cu);
  if ( v11 != nullptr )
    v12 = sub_428F30(v11, (int)"Character/Swordman/Effect/Particle/DOTAreaDust.ptl", 0);
  else
    v12 = nullptr;
  *(this + 41) = v12;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int, int))(*this + 148))(this, a2, a3, a4, a5, a6);
}



// ------------------------------------------------------------
// 0x651AF0 sub_651AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_651AF0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 25) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x651B10 sub_651B10
// ------------------------------------------------------------
int /*thiscall*/ sub_651B10(int this)
{
  int v1; // ecx
  int result; // eax

  *(uint8_t *)(this + 80) = 0;
  v1 = *(uint32_t *)(this + 100);
  if ( v1 != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v1 + 12))(v1, 0);
  return result;
}



// ------------------------------------------------------------
// 0x651B30 sub_651B30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_651B30(int a1, int a2, uint32_t *a3)
{
  int v3; // ecx
  uint32_t *result; // eax
  int v5; // esi

  v3 = a2;
  for ( result = a3; v3 != a1; *result = v5 )
  {
    v5 = *(uint32_t *)(v3 - 4);
    v3 -= 4;
    --result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x651B60 sub_651B60
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_651B60(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ecx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
        *result = *a3;
      ++result;
      v4 = (uint32_t *)((char *)v4 - 1);
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x651B90 sub_651B90
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_651B90(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  sub_651B60(a1, a2, a3);
  return &a1[(uint32_t)a2];
}



// ------------------------------------------------------------
// 0x651BC0 sub_651BC0
// ------------------------------------------------------------
void /*thiscall*/ sub_651BC0(uint32_t *this)
{
  int *v2; // esi
  uint32_t *i; // ebx
  int *v4; // eax
  int v5; // ebx
  int v6; // edx
  void *v7; // eax
  int v8; // [esp-Ch] [ebp-34h]
  int v9; // [esp-8h] [ebp-30h]
  int v10; // [esp-4h] [ebp-2Ch]
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v13; // [esp+24h] [ebp-4h]

  sub_5F66C0();
  v2 = (int *)*(this + 1);
  if ( *((uint8_t *)this + 80) == 0 )
  {
    for ( i = (uint32_t *)*(this + 22); i != (uint32_t *)*(this + 23); ++i )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(*v2 + 776))(v2, *i) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int *, uint32_t))(*v2 + 764))(v2, *i, 0, v2, 0);
    }
    *((uint8_t *)this + 80) = 1;
  }
  v4 = (int *)*(this + 25);
  if ( v4 != nullptr )
  {
    v5 = *v4;
    v10 = (*(int (/*thiscall*/ **)(int *))(*v2 + 128))(v2) + 90;
    v9 = (*(int (/*thiscall*/ **)(int *))(*v2 + 124))(v2) + 30;
    v8 = (*(int (/*thiscall*/ **)(int *))(*v2 + 120))(v2);
    (*(void (/*thiscall*/ **)(uint32_t))(v5 + 40))(*(this + 25));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 25) + 92))(*(this + 25), v11);
    v6 = *v2;
    v13 = 0;
    v7 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v6 + 80))(v2, 2, 0, v11);
    sub_4600B0(v7, v8, v9, v10);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 25) + 68))(*(this + 25)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 76))(this, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x651CC0 sub_651CC0
// ------------------------------------------------------------
void /*thiscall*/ sub_651CC0(int this, int a2, unsigned int a3, uint32_t *a4)
{
  int v5; // edx
  uint32_t *v6; // ecx
  unsigned int v7; // eax
  int v9; // ecx
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // ecx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  uint32_t *v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-3Ch]
  uint32_t *v25; // [esp-Ch] [ebp-30h]
  uint32_t *v26; // [esp-8h] [ebp-2Ch]
  int v27; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v29; // [esp+10h] [ebp-14h]
  int *v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+20h] [ebp-4h]
  int v32; // [esp+2Ch] [ebp+8h]
  uint32_t *v33; // [esp+30h] [ebp+Ch]
  uint32_t *v34; // [esp+30h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  v6 = (uint32_t *)*a4;
  v30 = &v27;
  a4 = v6;
  if ( v5 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( 0x3FFFFFFF - v9 < a3 )
      sub_6024A0(this);
    if ( v5 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t **)(this + 8);
      v20 = ((int)v18 - a2) >> 2 < a3;
      v21 = 4 * a3;
      v32 = 4 * a3;
      v34 = v18;
      if ( v20 )
      {
        sub_497E70(a2, v18, a2 + v21);
        v26 = (uint32_t *)(a3 - ((*(uint32_t *)(this + 8) - a2) >> 2));
        v25 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_651B90(v25, v26, &a4);
        v22 = v32 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_49A9D0(a2, v22 - v32, &a4);
      }
      else
      {
        v23 = (int)&v18[v21 / 0xFFFFFFFC];
        *(uint32_t *)(this + 8) = sub_497E70(&v18[v21 / 0xFFFFFFFC], v18, v18);
        sub_651B30(a2, v23, v34);
        sub_49A9D0(a2, a2 + v32, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v5 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v5 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v29 = 4 * v11;
      v14 = (char *)operator new(4 * v11);
      v24 = *(uint32_t *)(this + 4);
      Block = v14;
      v31 = 0;
      v33 = (uint32_t *)sub_497E70(v24, a2, v14);
      sub_651B60(v33, (uint32_t *)a3, &a4);
      sub_497E70(a2, *(uint32_t *)(this + 8), &v33[a3]);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 2;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v29];
      *(uint32_t *)(this + 8) = &v14[4 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x651F00 sub_651F00
// ------------------------------------------------------------
void /*thiscall*/ sub_651F00(int *this, uint32_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) >> 2 )
  {
    v5 = (uint32_t *)*(this + 2);
    sub_651B60(v5, (uint32_t *)1, a2);
    *(this + 2) = (int)(v5 + 1);
  }
  else
  {
    sub_651CC0((int)this, *(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x651F70 sub_651F70
// ------------------------------------------------------------
char /*thiscall*/ sub_651F70(int *this, int a2, void *Block)
{
  char result; // al
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // ecx

  sub_651F00(this + 21, &a2);
  result = (char)Block;
  if ( (uint8_t)Block != 0 )
  {
    v5 = operator new(0x12Cu);
    Block = v5;
    if ( v5 != nullptr )
      v6 = sub_428F30(v5, (int)"Common/CommonEffect/Particle/RemoveActiveStatus.ptl", *(this + 1));
    else
      v6 = nullptr;
    v7 = *(this + 1);
    *(this + 25) = (int)v6;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v6 + 112))(v6, v7);
  }
  else
  {
    *(this + 25) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x652010 sub_652010
// ------------------------------------------------------------
int /*thiscall*/ sub_652010(uint32_t *this, int a2, int a3)
{
  *(this + 11) = a2;
  *(this + 20) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x652030 sub_652030
// ------------------------------------------------------------
int /*thiscall*/ sub_652030(float *this, int a2)
{
  unsigned int v2; // esi
  int v3; // edx
  float v5; // [esp+4h] [ebp-4h]
  int v6; // [esp+10h] [ebp+8h]

  v2 = a2 + 1264;
  v5 = *(this + 20);
  *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(a2 + 1264)) + v5;
  return sub_41A590(v2, v3, v6);
}



// ------------------------------------------------------------
// 0x652070 sub_652070
// ------------------------------------------------------------
char /*thiscall*/ sub_652070(int *this, char a2)
{
  uint8_t *v2; // eax

  LOBYTE(v2) = a2;
  if ( a2 == 0 )
  {
    v2 = (uint8_t *)__RTDynamicCast(
                    *(this + 1),
                    0,
                    &IRDActiveObject `RTTI Type Descriptor',
                    &IRDMonster `RTTI Type Descriptor',
                    0);
    if ( v2 != nullptr )
    {
      v2 = (uint8_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v2 + 1040))(v2);
      v2[8] = 1;
    }
  }
  return (char)v2;
}



// ------------------------------------------------------------
// 0x6520B0 sub_6520B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6520B0(int *this)
{
  int v1; // ebx
  int v3; // esi
  char *v4; // eax
  char *v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int result; // eax
  int v12; // [esp-4h] [ebp-2Ch]
  int v14; // [esp+10h] [ebp-18h]
  int v15; // [esp+14h] [ebp-14h]
  char *v16; // [esp+18h] [ebp-10h]

  v1 = 0;
  v3 = *(this + 1);
  v15 = __RTDynamicCast(v3, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
  v14 = __RTDynamicCast(
          *(this + 9),
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  if ( sub_42FCB0(228) != 0 )
    v1 = sub_431860((char)"Character/Fighter/Effect/Animation/Provocationed.ani", 1);
  v4 = (char *)sub_44B6C0(284);
  v5 = v4;
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, v1, 1);
    *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v5 = nullptr;
  }
  v16 = v5;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3);
  sub_45FE80(v6, (int)v5, 2, 0, (int)v5, 0, 0);
  v7 = *(uint32_t *)v5;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 192))(v3);
  v12 = v8 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3) + 30;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, v9);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v16, v10);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v16 + 60))(v16, v3);
  result = sub_4A06D0(v12);
  if ( v15 != 0 )
  {
    result = v14;
    if ( v14 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v15 + 1152))(v15, *(this + 9));
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 1040))(v15) + 8) = 0;
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 1104))(v15, 9);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652220 sub_652220
// ------------------------------------------------------------
int /*thiscall*/ sub_652220(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x652230 sub_652230
// ------------------------------------------------------------
int /*thiscall*/ sub_652230(int this, int a2)
{
  int result; // eax

  sub_47E720(1, 39);
  *(float *)(this + 80) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.1;
  *(uint32_t *)(this + 84) = sub_47EF20(3, a2, -1, -1, 11);
  result = sub_47EF20(1, a2, -1, -1, 11);
  *(uint32_t *)(this + 44) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6522A0 sub_6522A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6522A0(int this, int a2)
{
  unsigned int v4; // edi
  int v5; // edx
  int v6; // esi
  int v7; // eax
  int v8; // edx
  float v10; // [esp+Ch] [ebp-4h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = a2 + 1278;
  v10 = *(float *)(this + 80);
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(a2 + 1278)) - v10;
  sub_41A590(v4, v5, v11);
  v6 = *(uint32_t *)(this + 84);
  v7 = sub_41A5E0(a2 + 466);
  return sub_41A590(a2 + 466, v8, v7 - v6);
}



// ------------------------------------------------------------
// 0x652300 sub_652300
// ------------------------------------------------------------
char /*thiscall*/ sub_652300(int this, char a2, int a3, int a4, int a5)
{
  char result; // al
  int v7; // eax

  result = a2;
  if ( a2 != 0 )
  {
    sub_4938F0(*(uint32_t *)(this + 88));
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
    return sub_491D00(dword_79C0B0, a3, a4 - v7 - 30, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x652350 sub_652350
// ------------------------------------------------------------
int /*thiscall*/ sub_652350(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 22);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 22));
    result = sub_657740(v2, 228);
  }
  *(this + 22) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x652380 sub_652380
// ------------------------------------------------------------
int /*thiscall*/ sub_652380(int *this)
{
  int v2; // eax

  if ( *(this + 22) == 0 )
  {
    if ( sub_42FCB0(228) != 0 )
      v2 = sub_431860((char)"Character/Fighter/Effect/Animation/AimedVitalPoint.ani", 1);
    else
      v2 = 0;
    *(this + 22) = v2;
  }
  return sub_4926A0(*(this + 22));
}



// ------------------------------------------------------------
// 0x652400 sub_652400
// ------------------------------------------------------------
int /*thiscall*/ sub_652400(uint32_t *this, int a2, int a3)
{
  *(this + 21) = a2;
  *(this + 22) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x652420 sub_652420
// ------------------------------------------------------------
// attributes: thunk
int sub_652420()
{
  return sub_5F66C0();
}



// ------------------------------------------------------------
// 0x652430 sub_652430
// ------------------------------------------------------------
int /*thiscall*/ sub_652430(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  unsigned int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // edi
  unsigned int v8; // esi
  int result; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  int i; // [esp+10h] [ebp-4h]

  v2 = this;
  v3 = a2 + 172;
  for ( i = 4; i != 0; --i )
  {
    v4 = v2[21];
    v5 = sub_41A5E0(v3);
    sub_41A590(v3, v6, v5 - v4);
    v3 += 14;
  }
  v7 = 0;
  v8 = a2 + 284;
  do
  {
    result = sub_497040(v7);
    if ( result != 17 )
    {
      v10 = v2[22];
      v11 = sub_41A5E0(v8);
      result = sub_41A590(v8, v12, v11 - v10);
      v2 = this;
    }
    ++v7;
    v8 += 14;
  }
  while ( v7 < 16 );
  return result;
}



// ------------------------------------------------------------
// 0x6524C0 sub_6524C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6524C0(uint32_t *this, float *a2, int *a3)
{
  int result; // eax

  if ( *a3 == 0 )
    *a2 = -*a2;
  if ( a3[1] == 2 )
    a2[1] = -a2[1];
  *(this + 21) = *(uint32_t *)a2;
  *(this + 22) = *((uint32_t *)a2 + 1);
  result = *a3;
  *(this + 23) = *a3;
  *(this + 24) = a3[1];
  return result;
}



// ------------------------------------------------------------
// 0x652500 sub_652500
// ------------------------------------------------------------
char /*userpurge*/ sub_652500@<al>(int a1@<ecx>, int a2@<edi>, int a3)
{
  double v3; // st7
  int v5; // ebx
  int v6; // edi
  int *v7; // ecx
  int v8; // ebx
  int v9; // eax
  int *v11; // [esp+0h] [ebp-4h]
  int v12; // [esp+Ch] [ebp+8h]
  int v13; // [esp+Ch] [ebp+8h]

  v3 = (double)a3;
  v5 = (uint64_t)(v3 * *(float *)(a1 + 84) * 0.033333335);
  v12 = (uint64_t)(v3 * *(float *)(a1 + 88) * 0.033333335);
  v6 = v5
     + (*(int (/*fastcall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(a1 + 4) + 120))(
         *(uint32_t *)(a1 + 4),
         (uint64_t)(v3 * *(float *)(a1 + 88) * 0.033333335) >> 32,
         a2);
  v13 = v12 + (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 124))(*(uint32_t *)(a1 + 4));
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(a1 + 4) + 136))(
         *(uint32_t *)(a1 + 4),
         v6,
         v13,
         0) != 0 )
  {
    v7 = *(int **)(a1 + 4);
    v8 = *v7;
    v11 = v7;
    v9 = (*(int (**)(void))(*v7 + 128))();
    (*(void (/*thiscall*/ **)(int *, int, int, int))(v8 + 112))(v11, v6, v13, v9);
  }
  *(uint8_t *)(a1 + 21) = 0;
  *(uint8_t *)(a1 + 22) = 0;
  return sub_698F90(a1 + 8, 0, 0);
}



// ------------------------------------------------------------
// 0x6525A0 sub_6525A0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525A0(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6525B0 sub_6525B0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525B0(int a1, int a2)
{
  return 0;
}



// ------------------------------------------------------------
// 0x6525C0 sub_6525C0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525C0(int a1, uint32_t *a2)
{
  *a2 = *(uint32_t *)(a1 + 4);
  return 0;
}



// ------------------------------------------------------------
// 0x6525E0 sub_6525E0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525E0(int a1, int a2, int a3, int a4)
{
  return 0;
}



// ------------------------------------------------------------
// 0x6525F0 sub_6525F0
// ------------------------------------------------------------
int /*stdcall*/ sub_6525F0(int a1, const void *a2, uint32_t *a3)
{
  int result; // eax

  if ( memcmp(a2, &dword_743370, 0x10u) == 0 || memcmp(a2, &unk_743360, 0x10u) == 0 )
  {
    *a3 = a1;
    return 0;
  }
  else
  {
    result = 0;
    if ( memcmp(a2, &unk_743340, 0x10u) == 0 )
    {
      *a3 = a1 + 4;
    }
    else
    {
      *a3 = 0;
      return -2147467262;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652670 sub_652670
// ------------------------------------------------------------
int /*stdcall*/ sub_652670(int a1, uint32_t *a2)
{
  *a2 = *(uint32_t *)(*(uint32_t *)(a1 + 4) + 4);
  return 0;
}



// ------------------------------------------------------------
// 0x652690 sub_652690
// ------------------------------------------------------------
int /*stdcall*/ sub_652690(int a1, int a2, uint32_t *a3, LPRECT lpRect, LPRECT a5, int a6)
{
  HWND v6; // edx

  *(uint32_t *)a2 = *(uint32_t *)(a1 + 4);
  *a3 = 0;
  *(uint32_t *)(a6 + 4) = 0;
  v6 = *(HWND *)(*(uint32_t *)a2 + 4);
  *(uint32_t *)(a6 + 12) = 0;
  *(uint32_t *)(a6 + 16) = 0;
  *(uint32_t *)(a6 + 8) = v6;
  GetClientRect(v6, lpRect);
  GetClientRect(*(HWND *)(a6 + 8), a5);
  return 0;
}



// ------------------------------------------------------------
// 0x6526F0 sub_6526F0
// ------------------------------------------------------------
int /*stdcall*/ sub_6526F0(int a1, uint32_t *a2)
{
  *a2 = 0;
  return -2147467262;
}



// ------------------------------------------------------------
// 0x652720 sub_652720
// ------------------------------------------------------------
int /*stdcall*/ sub_652720(int a1, int *a2, uint32_t *a3)
{
  int v3; // ecx

  v3 = *a2;
  if ( (*a2 != 0 || *((uint16_t *)a2 + 2) != 0 || *((uint16_t *)a2 + 3) != 0)
    && (v3 != 132096 || *((uint16_t *)a2 + 2) != 0 || *((uint16_t *)a2 + 3) != 0)
    && (v3 != 883365280 || *((uint16_t *)a2 + 2) != 25991 || *((uint16_t *)a2 + 3) != 4560) )
  {
    return -2147467262;
  }
  *a3 = a1;
  return 0;
}



// ------------------------------------------------------------
// 0x6527B0 sub_6527B0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527B0(int a1)
{
  return 1;
}



// ------------------------------------------------------------
// 0x6527C0 sub_6527C0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527C0(int a1, int a2)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6527D0 sub_6527D0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527D0(int a1, int a2, int a3, int a4)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6527E0 sub_6527E0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527E0(int a1, int a2, int a3, int a4, int a5, int a6)
{
  return -2147467263;
}



// ------------------------------------------------------------
// 0x6527F0 sub_6527F0
// ------------------------------------------------------------
int /*stdcall*/ sub_6527F0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  int v10; // eax

  switch ( a2 )
  {
    case 263:
      PostMessageA(*(HWND *)(a1 + 4), 0x10u, 0, 0);
      return 0;
    case 252:
      if ( *(uint32_t *)(a1 + 8) == 0 )
      {
        *(uint32_t *)(a1 + 8) = *(uint32_t *)(*(uint32_t *)a6 + 24);
        OutputDebugStringA("************** NAVIGATION START **************\n");
        return 0;
      }
      break;
    case 259:
      v10 = *(uint32_t *)(a1 + 8);
      if ( v10 != 0 && v10 == *(uint32_t *)(*(uint32_t *)a6 + 24) )
      {
        *(uint32_t *)(a1 + 8) = 0;
        OutputDebugStringA("************** NAVIGATION END **************\n");
      }
      break;
    default:
      break;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x652880 sub_652880
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_652880(HWND hWnd)
{
  uint32_t *result; // eax
  void *v2; // edi
  int v3; // esi

  result = (uint32_t *)GetWindowLongA(hWnd, -21);
  v2 = result;
  if ( result != nullptr )
  {
    v3 = *result;
    (*(void (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)*result + 24))(*result, 1);
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 8))(v3);
    GlobalFree(v2);
    return (uint32_t *)SetWindowLongA(hWnd, -21, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6528C0 sub_6528C0
// ------------------------------------------------------------
int /*cdecl*/ sub_6528C0(HWND hWnd)
{
  IOleClientSite *v1; // eax
  IOleClientSite *v2; // edi
  IOleClientSite *v4; // ebx
  struct tagRECT Rect; // [esp+4h] [ebp-28h] BYREF
  uint8_t v6[4]; // [esp+14h] [ebp-18h] BYREF
  IOleClientSite *v7; // [esp+18h] [ebp-14h]
  int v8; // [esp+1Ch] [ebp-10h] BYREF
  int v9; // [esp+20h] [ebp-Ch] BYREF
  LPVOID ppvObj; // [esp+24h] [ebp-8h] BYREF
  int v11; // [esp+28h] [ebp-4h] BYREF

  v1 = (IOleClientSite *)GlobalAlloc(0, 0x24u);
  v2 = v1;
  if ( v1 == nullptr )
    return -1;
  v1[1].lpVtbl = (struct IOleClientSiteVtbl *)&off_79602C;
  v1[2].lpVtbl = (struct IOleClientSiteVtbl *)hWnd;
  v4 = v1 + 3;
  v1[5].lpVtbl = (struct IOleClientSiteVtbl *)&v1[1];
  v1[3].lpVtbl = (struct IOleClientSiteVtbl *)&off_7960A4;
  v1[4].lpVtbl = (struct IOleClientSiteVtbl *)&off_796068;
  v7 = v1 + 6;
  v1[6].lpVtbl = (struct IOleClientSiteVtbl *)&off_7960C8;
  v1[7].lpVtbl = (struct IOleClientSiteVtbl *)hWnd;
  v1[8].lpVtbl = nullptr;
  if ( OleCreate(&stru_743310, &stru_743350, 1u, nullptr, v1 + 3, &pStg, &ppvObj) != 0 )
  {
    GlobalFree(v2);
    return -2;
  }
  else
  {
    v2->lpVtbl = (struct IOleClientSiteVtbl *)ppvObj;
    SetWindowLongA(hWnd, -21, (LONG)v2);
    (*(void (/*stdcall*/ **)(LPVOID, _UNKNOWN **, uint32_t))(*(uint32_t *)ppvObj + 20))(ppvObj, &off_73F25C, 0);
    GetClientRect(hWnd, &Rect);
    if ( OleSetContainedObject((LPUNKNOWN)ppvObj, true) != 0
      || (*(int (/*stdcall*/ **)(LPVOID, int, uint32_t, IOleClientSite *, int, HWND, struct tagRECT *))(*(uint32_t *)ppvObj
                                                                                                  + 44))(
           ppvObj,
           -1,
           0,
           v4,
           -1,
           hWnd,
           &Rect) != 0
      || (**(int (/*stdcall*/ ***)(LPVOID, const IID *, int *))ppvObj)(ppvObj, &stru_743330, &v11) != 0 )
    {
      sub_652880(hWnd);
      return -3;
    }
    else
    {
      GetClientRect(hWnd, &Rect);
      (*(void (/*stdcall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 88))(v11, 0);
      (*(void (/*stdcall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 96))(v11, 0);
      (*(void (/*stdcall*/ **)(int, LONG))(*(uint32_t *)v11 + 104))(v11, Rect.right);
      (*(void (/*stdcall*/ **)(int, LONG))(*(uint32_t *)v11 + 112))(v11, Rect.bottom);
      (**(void (/*stdcall*/ ***)(int, void *, int *))v11)(v11, &unk_743390, &v9);
      (*(void (/*stdcall*/ **)(int, int *, int *))(*(uint32_t *)v9 + 16))(v9, &dword_743320, &v8);
      (*(void (/*stdcall*/ **)(int, IOleClientSite *, uint8_t *))(*(uint32_t *)v8 + 20))(v8, v7, v6);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v9 + 8))(v9);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v11 + 8))(v11);
      return 0;
    }
  }
}



// ------------------------------------------------------------
// 0x652A70 sub_652A70
// ------------------------------------------------------------
int /*cdecl*/ sub_652A70(HWND hWnd, LPCCH lpMultiByteStr)
{
  uint32_t *WindowLongA; // eax
  int v3; // edi
  WCHAR *v4; // eax
  OLECHAR *v5; // esi
  VARIANTARG pvarg; // [esp+0h] [ebp-14h] BYREF
  int v8; // [esp+10h] [ebp-4h] BYREF

  WindowLongA = (uint32_t *)GetWindowLongA(hWnd, -21);
  if ( (**(int (/*stdcall*/ ***)(uint32_t, const IID *, int *))*WindowLongA)(*WindowLongA, &stru_743330, &v8) != 0 )
    return -5;
  VariantInit(&pvarg);
  pvarg.vt = 8;
  v3 = MultiByteToWideChar(0, 0, lpMultiByteStr, -1, nullptr, 0);
  v4 = (WCHAR *)GlobalAlloc(0, 2 * v3);
  v5 = v4;
  if ( v4 != nullptr
    && (MultiByteToWideChar(0, 0, lpMultiByteStr, -1, v4, v3),
        pvarg.lVal = (LONG)SysAllocString(v5),
        GlobalFree(v5),
        pvarg.lVal != 0) )
  {
    (*(void (/*stdcall*/ **)(int, VARIANTARG *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v8 + 208))(
      v8,
      &pvarg,
      0,
      0,
      0,
      0);
    VariantClear(&pvarg);
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v8 + 8))(v8);
    return 0;
  }
  else
  {
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v8 + 8))(v8);
    return -6;
  }
}



// ------------------------------------------------------------
// 0x652B50 sub_652B50
// ------------------------------------------------------------
LRESULT /*stdcall*/ sub_652B50(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  UINT v4; // ebx
  HWND Parent; // eax
  HWND v7; // esi
  void (/*stdcall*/ ****WindowLongA)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v9)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v10)(uint32_t, void *, UINT *); // [esp+4h] [ebp-Ch] BYREF
  void (/*stdcall*/ ***v11)(uint32_t, void *, LPARAM *); // [esp+8h] [ebp-8h] BYREF
  int v12; // [esp+Ch] [ebp-4h] BYREF

  v4 = Msg;
  switch ( Msg )
  {
    case 1u:
      if ( sub_6528C0(hWnd) != 0 )
        return -1;
      ++byte_9B9548;
      return 0;
    case 0x10u:
      sub_652880(hWnd);
      if ( --byte_9B9548 == 0 )
        OleUninitialize();
      Parent = GetParent(hWnd);
      v7 = Parent;
      if ( Parent != nullptr )
      {
        SetFocus(Parent);
        EnableWindow(v7, true);
      }
      break;
    case 0x317u:
      v12 = 0;
      v11 = nullptr;
      lParam = 0;
      v10 = nullptr;
      Msg = 0;
      WindowLongA = (void (/*stdcall*/ ****)(uint32_t, const IID *, int *))GetWindowLongA(hWnd, -21);
      if ( WindowLongA == nullptr )
        return 0;
      v9 = *WindowLongA;
      if ( v9 == nullptr )
        return 0;
      (**v9)(v9, &stru_743330, &v12);
      if ( v12 == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(int, void (/*stdcall*/ ****)(uint32_t, void *, LPARAM *)))(*(uint32_t *)v12 + 72))(v12, &v11);
      if ( v11 == nullptr )
        return 0;
      (**v11)(v11, &unk_7433A0, &lParam);
      if ( lParam == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(LPARAM, void (/*stdcall*/ ****)(uint32_t, void *, UINT *)))(*(uint32_t *)lParam + 36))(
        lParam,
        &v10);
      if ( v10 == nullptr )
        return 0;
      (**v10)(v10, &unk_7433B0, &Msg);
      if ( Msg == 0 )
        return 0;
      (*(void (/*stdcall*/ **)(UINT, WPARAM))(*(uint32_t *)Msg + 12))(Msg, wParam);
      (*(void (/*stdcall*/ **)(UINT))(*(uint32_t *)Msg + 8))(Msg);
      (*(void (/*stdcall*/ **)(LPARAM))(*(uint32_t *)lParam + 8))(lParam);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v12 + 8))(v12);
      return 1;
    default:
      break;
  }
  return DefWindowProcA(hWnd, v4, wParam, lParam);
}



// ------------------------------------------------------------
// 0x652CC0 sub_652CC0
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_652CC0(HWND hWnd)
{
  void (/*stdcall*/ ****WindowLongA)(uint32_t, const IID *, int *); // eax
  void (/*stdcall*/ ***v2)(uint32_t, const IID *, int *); // eax
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = 0;
  WindowLongA = (void (/*stdcall*/ ****)(uint32_t, const IID *, int *))GetWindowLongA(hWnd, -21);
  if ( WindowLongA == nullptr )
    return false;
  v2 = *WindowLongA;
  if ( v2 == nullptr )
    return false;
  (**v2)(v2, &stru_743330, &v4);
  if ( v4 == 0 )
    return false;
  (*(void (/*stdcall*/ **)(int, HWND *, int))(*(uint32_t *)v4 + 224))(v4, &hWnd, v4);
  (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v4 + 8))(v4);
  return hWnd != (HWND)4;
}



// ------------------------------------------------------------
// 0x652D30 sub_652D30
// ------------------------------------------------------------
HWND /*stdcall*/ sub_652D30(HWND hWndParent, HINSTANCE hInstance, int *a3, int a4)
{
  HWND Window; // edi
  WNDCLASSEXA v6; // [esp+0h] [ebp-30h] BYREF

  if ( byte_9B9548 != 0 && OleInitialize(nullptr) != 0 )
    return nullptr;
  memset(&v6, 0, sizeof(v6));
  v6.cbSize = 48;
  v6.hInstance = hInstance;
  v6.lpfnWndProc = sub_652B50;
  v6.lpszClassName = "Browser Example";
  RegisterClassExA(&v6);
  Window = CreateWindowExA(
             0,
             "Browser Example",
             "NEOPLE_WEB",
             0x80000000,
             *a3,
             a3[1],
             a3[2],
             a3[3],
             hWndParent,
             nullptr,
             hInstance,
             nullptr);
  if ( a4 == 1 )
    EnableWindow(hWndParent, false);
  return Window;
}



// ------------------------------------------------------------
// 0x652DE0 sub_652DE0
// ------------------------------------------------------------
int /*stdcall*/ sub_652DE0(HWND hWnd, LPCCH lpMultiByteStr)
{
  return sub_652A70(hWnd, lpMultiByteStr);
}



// ------------------------------------------------------------
// 0x652E00 sub_652E00
// ------------------------------------------------------------
int /*cdecl*/ sub_652E00(int a1, int *a2, uint8_t *a3, int a4)
{
  int v4; // eax
  int result; // eax
  int v6; // esi
  uint8_t *v7; // [esp+4h] [ebp-38h] BYREF
  int v8; // [esp+8h] [ebp-34h]
  int v9; // [esp+10h] [ebp-2Ch]
  int v10; // [esp+14h] [ebp-28h]
  int v11; // [esp+18h] [ebp-24h]
  int v12; // [esp+24h] [ebp-18h]
  int v13; // [esp+28h] [ebp-14h]

  v8 = a4;
  v7 = a3;
  v4 = *a2;
  v9 = a1;
  v10 = v4;
  v12 = 0;
  v13 = 0;
  result = sub_652FE0(&v7, "1.2.3", 56);
  if ( result == 0 )
  {
    v6 = sub_653120(&v7, 4);
    if ( v6 == 1 )
    {
      *a2 = v11;
      return sub_654750(&v7);
    }
    else
    {
      sub_654750(&v7);
      if ( v6 == 2 || v6 == -5 && v8 == 0 )
        return -3;
      else
        return v6;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x652EB0 sub_652EB0
// ------------------------------------------------------------
int /*cdecl*/ sub_652EB0(uint32_t *a1)
{
  uint32_t *v1; // eax

  if ( a1 == nullptr )
    return -2;
  v1 = (uint32_t *)a1[7];
  if ( v1 == nullptr )
    return -2;
  v1[7] = 0;
  a1[5] = 0;
  a1[2] = 0;
  a1[6] = 0;
  a1[12] = 1;
  *v1 = 0;
  v1[1] = 0;
  v1[3] = 0;
  v1[8] = 0;
  v1[10] = 0;
  v1[11] = 0;
  v1[12] = 0;
  v1[14] = 0;
  v1[15] = 0;
  v1[5] = 0x8000;
  v1[27] = v1 + 332;
  v1[20] = v1 + 332;
  v1[19] = v1 + 332;
  return 0;
}



// ------------------------------------------------------------
// 0x652F10 sub_652F10
// ------------------------------------------------------------
int /*cdecl*/ sub_652F10(uint32_t *a1, int a2, uint8_t *a3, int a4)
{
  bool v4; // zf
  uint32_t *v5; // eax
  int v7; // ecx

  if ( a3 == nullptr || *a3 != 49 || a4 != 56 )
    return -6;
  if ( a1 != nullptr )
  {
    v4 = a1[8] == 0;
    a1[6] = 0;
    if ( v4 )
    {
      a1[8] = sub_6547A0;
      a1[10] = 0;
    }
    if ( a1[9] == 0 )
      a1[9] = sub_6547C0;
    v5 = (uint32_t *)((int (/*cdecl*/ *)(uint32_t, int, int))a1[8])(a1[10], 1, 9520);
    if ( v5 == nullptr )
      return -4;
    v7 = a2;
    a1[7] = v5;
    if ( a2 >= 0 )
    {
      v5[2] = (a2 >> 4) + 1;
      if ( a2 < 48 )
        v7 = a2 & 0xF;
    }
    else
    {
      v5[2] = 0;
      v7 = -a2;
    }
    if ( v7 >= 8 && v7 <= 15 )
    {
      v5[9] = v7;
      v5[13] = 0;
      return sub_652EB0(a1);
    }
    ((void (/*cdecl*/ *)(uint32_t, uint32_t *))a1[9])(a1[10], v5);
    a1[7] = 0;
  }
  return -2;
}



// ------------------------------------------------------------
// 0x652FE0 sub_652FE0
// ------------------------------------------------------------
int /*cdecl*/ sub_652FE0(uint32_t *a1, uint8_t *a2, int a3)
{
  return sub_652F10(a1, 15, a2, a3);
}



// ------------------------------------------------------------
// 0x653000 sub_653000
// ------------------------------------------------------------
int /*usercall*/ sub_653000@<eax>(int a1@<eax>, int a2)
{
  int v3; // ebx
  int v5; // eax
  int v7; // edx
  unsigned int v8; // ecx
  unsigned int v9; // esi
  int v10; // ecx
  unsigned int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // eax
  unsigned int v14; // edx
  unsigned int v15; // edx
  unsigned int v16; // [esp+14h] [ebp+4h]

  v3 = *(uint32_t *)(a2 + 28);
  if ( *(uint32_t *)(v3 + 52) == 0 )
  {
    v5 = (*(int (/*cdecl*/ **)(uint32_t, int, int))(a2 + 32))(*(uint32_t *)(a2 + 40), 1 << *(uint32_t *)(v3 + 36), 1);
    *(uint32_t *)(v3 + 52) = v5;
    if ( v5 == 0 )
      return 1;
  }
  if ( *(uint32_t *)(v3 + 40) == 0 )
  {
    v7 = 1 << *(uint32_t *)(v3 + 36);
    *(uint32_t *)(v3 + 48) = 0;
    *(uint32_t *)(v3 + 44) = 0;
    *(uint32_t *)(v3 + 40) = v7;
  }
  v8 = *(uint32_t *)(v3 + 40);
  v9 = a1 - *(uint32_t *)(a2 + 16);
  if ( v9 < v8 )
  {
    v11 = v8 - *(uint32_t *)(v3 + 48);
    v16 = v11;
    if ( v11 > v9 )
    {
      v11 = v9;
      v16 = v9;
    }
    qmemcpy((void *)(*(uint32_t *)(v3 + 48) + *(uint32_t *)(v3 + 52)), (const void *)(*(uint32_t *)(a2 + 12) - v9), v11);
    v12 = v9 - v16;
    if ( v9 == v16 )
    {
      v13 = *(uint32_t *)(v3 + 40);
      v14 = v16 + *(uint32_t *)(v3 + 48);
      *(uint32_t *)(v3 + 48) = v14;
      if ( v14 == v13 )
        *(uint32_t *)(v3 + 48) = 0;
      v15 = *(uint32_t *)(v3 + 44);
      if ( v15 < v13 )
        *(uint32_t *)(v3 + 44) = v16 + v15;
      return 0;
    }
    else
    {
      qmemcpy(*(void **)(v3 + 52), (const void *)(*(uint32_t *)(a2 + 12) - v12), v12);
      *(uint32_t *)(v3 + 48) = v12;
      *(uint32_t *)(v3 + 44) = *(uint32_t *)(v3 + 40);
      return 0;
    }
  }
  else
  {
    qmemcpy(*(void **)(v3 + 52), (const void *)(*(uint32_t *)(a2 + 12) - *(uint32_t *)(v3 + 40)), *(uint32_t *)(v3 + 40));
    v10 = *(uint32_t *)(v3 + 40);
    *(uint32_t *)(v3 + 48) = 0;
    *(uint32_t *)(v3 + 44) = v10;
    return 0;
  }
}



// ------------------------------------------------------------
// 0x653120 sub_653120
// ------------------------------------------------------------
int /*cdecl*/ sub_653120(uint8_t **a1, int a2)
{
  int *v2; // ebx
  unsigned int v3; // edx
  unsigned int v4; // ebp
  uint8_t *v5; // esi
  unsigned int v6; // edi
  unsigned int v7; // eax
  int v8; // ecx
  int result; // eax
  int v10; // edx
  int v11; // eax
  uint8_t v12; // cl
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // edx
  uint32_t *v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  unsigned int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // edi
  unsigned int v28; // edx
  int v29; // edi
  int v30; // eax
  unsigned int v31; // ecx
  int v32; // edx
  int v33; // ecx
  unsigned int v34; // edx
  unsigned int v35; // ecx
  int v36; // ecx
  unsigned int v37; // ecx
  int v38; // edx
  int v39; // ecx
  unsigned int v40; // edx
  unsigned int v41; // ecx
  int v42; // ecx
  int v43; // edx
  int v44; // eax
  int v45; // eax
  int v46; // edx
  uint16_t v47; // dx
  int v48; // eax
  int v49; // eax
  int v50; // ecx
  int v51; // edx
  int v52; // ecx
  unsigned int v53; // eax
  unsigned int v54; // ebp
  int v55; // ecx
  int v56; // edx
  int v57; // ecx
  unsigned int v58; // ecx
  unsigned int v59; // edx
  int v60; // edx
  int v61; // ecx
  unsigned int v62; // eax
  char v63; // dl
  unsigned int v64; // ecx
  unsigned int v65; // edx
  int v66; // edx
  char v67; // cl
  unsigned int v68; // ecx
  unsigned int v69; // edx
  unsigned int v70; // ecx
  int v71; // edx
  unsigned int v72; // ecx
  int v73; // edx
  int v74; // ecx
  int v75; // edx
  int v76; // ecx
  int v77; // ecx
  int v78; // edx
  int v79; // edx
  unsigned int v80; // eax
  int v81; // edi
  int v82; // edx
  unsigned int v83; // eax
  int16_t v84; // dx
  int v85; // edx
  int v86; // ecx
  char *v87; // ecx
  unsigned int v88; // edx
  unsigned int v89; // edx
  uint8_t *v90; // edx
  int v91; // edx
  int v92; // ecx
  int v93; // edx
  unsigned int v94; // ecx
  int v95; // edx
  int v96; // ecx
  uint8_t *v97; // edx
  int v98; // edx
  int v99; // ecx
  int v100; // edx
  unsigned int v101; // ecx
  int v102; // edx
  int v103; // ecx
  unsigned int v104; // ecx
  unsigned int v105; // ecx
  unsigned int v106; // edx
  int v107; // edx
  char *v108; // edx
  char *v109; // ecx
  bool v110; // zf
  char *v111; // ecx
  int v112; // edx
  unsigned int v113; // ecx
  int v114; // edx
  int v115; // edx
  int v116; // eax
  int v117; // ecx
  uint16_t v118; // dx
  int v119; // edx
  int v120; // eax
  unsigned int v121; // ebp
  unsigned int v122; // edi
  uint8_t *v123; // edx
  int v124; // eax
  int v125; // eax
  unsigned int i; // [esp+4h] [ebp-38h]
  unsigned int v127; // [esp+8h] [ebp-34h]
  uint8_t *v128; // [esp+Ch] [ebp-30h]
  unsigned int v129; // [esp+10h] [ebp-2Ch]
  unsigned int v130; // [esp+10h] [ebp-2Ch]
  unsigned int v131; // [esp+10h] [ebp-2Ch]
  unsigned int v132; // [esp+10h] [ebp-2Ch]
  unsigned int v133; // [esp+10h] [ebp-2Ch]
  int v134; // [esp+10h] [ebp-2Ch]
  int v135; // [esp+10h] [ebp-2Ch]
  int v136; // [esp+10h] [ebp-2Ch]
  unsigned int v137; // [esp+10h] [ebp-2Ch]
  unsigned int v138; // [esp+14h] [ebp-28h]
  unsigned int v139; // [esp+18h] [ebp-24h] BYREF
  char *v140; // [esp+1Ch] [ebp-20h]
  int v141; // [esp+20h] [ebp-1Ch]
  unsigned int v142; // [esp+24h] [ebp-18h]
  int v143; // [esp+28h] [ebp-14h]
  unsigned int v144; // [esp+2Ch] [ebp-10h]
  unsigned int v145; // [esp+30h] [ebp-Ch]
  unsigned int v146; // [esp+34h] [ebp-8h]

  if ( a1 == nullptr )
    return -2;
  v2 = (int *)a1[7];
  if ( v2 == nullptr || a1[3] == nullptr || *a1 == nullptr && a1[1] != nullptr )
    return -2;
  if ( *v2 == 11 )
    *v2 = 12;
  v3 = (unsigned int)a1[4];
  v4 = v2[15];
  v5 = *a1;
  v6 = (unsigned int)a1[1];
  v7 = v2[14];
  v140 = (char *)a1[3];
  v8 = *v2;
  v138 = v3;
  v128 = v5;
  v127 = v6;
  i = v7;
  v145 = v6;
  v142 = v3;
  v143 = 0;
  while ( 2 )
  {
    switch ( v8 )
    {
      case 0:
        if ( v2[2] == 0 )
        {
          *v2 = 12;
          goto LABEL_297;
        }
        for ( ; v4 < 0x10; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v10 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v10;
          ++v5;
          i = v7;
        }
        if ( (v2[2] & 2) != 0 && v7 == 35615 )
        {
          v4 = 0;
          v2[6] = sub_655990(0, 0, 0);
          LOWORD(v139) = -29921;
          v2[6] = sub_655990(v2[6], &v139, 2);
          i = 0;
          *v2 = 1;
          v7 = 0;
          goto LABEL_297;
        }
        v11 = v2[8];
        v2[4] = 0;
        if ( v11 != 0 )
          *(uint32_t *)(v11 + 48) = -1;
        if ( (v2[2] & 1) == 0 || ((i >> 8) + ((uint8_t)i << 8)) % 0x1F != 0 )
        {
          a1[6] = "incorrect header check";
          v7 = i;
          goto LABEL_296;
        }
        v12 = i;
        if ( (i & 0xF) != 8 )
        {
          a1[6] = "unknown compression method";
          v7 = i;
          goto LABEL_296;
        }
        i >>= 4;
        v13 = (v12 >> 4) + 8;
        v4 -= 4;
        if ( v13 > v2[9] )
        {
          v7 = i;
          a1[6] = "invalid window size";
          goto LABEL_296;
        }
        v4 = 0;
        v2[5] = 1 << v13;
        v14 = sub_655460(0, 0, 0);
        v2[6] = v14;
        a1[12] = (uint8_t *)v14;
        *v2 = ~BYTE1(i) & 2 | 9;
        i = 0;
        v7 = 0;
        goto LABEL_297;
      case 1:
        for ( ; v4 < 0x10; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v15 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v15;
          ++v5;
          i = v7;
        }
        v2[4] = v7;
        if ( (uint8_t)v7 != 8 )
        {
          a1[6] = "unknown compression method";
          goto LABEL_296;
        }
        if ( (v7 & 0xE000) != 0 )
        {
          a1[6] = "unknown header flags set";
          goto LABEL_296;
        }
        v16 = (uint32_t *)v2[8];
        if ( v16 != nullptr )
          *v16 = (v7 & 0x100) != 0;
        if ( (v2[4] & 0x200) != 0 )
        {
          LOWORD(v139) = i;
          v2[6] = sub_655990(v2[6], &v139, 2);
        }
        v7 = 0;
        v4 = 0;
        *v2 = 2;
        do
        {
LABEL_44:
          if ( v6 == 0 )
            goto LABEL_304;
          v17 = *v5 << v4;
          --v6;
          v4 += 8;
          v7 += v17;
          ++v5;
          i = v7;
        }
        while ( v4 < 0x20 );
LABEL_46:
        v18 = v2[8];
        if ( v18 != 0 )
          *(uint32_t *)(v18 + 4) = v7;
        if ( (v2[4] & 0x200) != 0 )
        {
          v139 = i;
          v2[6] = sub_655990(v2[6], &v139, 4);
        }
        v7 = 0;
        v4 = 0;
        *v2 = 3;
        do
        {
LABEL_52:
          if ( v6 == 0 )
            goto LABEL_304;
          v19 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v19;
          ++v5;
          LOWORD(i) = v7;
          v128 = v5;
        }
        while ( v4 < 0x10 );
LABEL_54:
        v20 = v2[8];
        if ( v20 != 0 )
        {
          *(uint32_t *)(v20 + 8) = (uint8_t)v7;
          *(uint32_t *)(v2[8] + 12) = v7 >> 8;
        }
        if ( (v2[4] & 0x200) != 0 )
        {
          LOWORD(v139) = i;
          v2[6] = sub_655990(v2[6], &v139, 2);
        }
        v7 = 0;
        i = 0;
        v4 = 0;
        *v2 = 4;
LABEL_59:
        if ( (v2[4] & 0x400) != 0 )
        {
          if ( v4 < 0x10 )
          {
            while ( v6 != 0 )
            {
              v21 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v21;
              ++v5;
              LOWORD(i) = v7;
              v128 = v5;
              if ( v4 >= 0x10 )
                goto LABEL_63;
            }
            goto LABEL_304;
          }
LABEL_63:
          v22 = v2[8];
          v2[16] = v7;
          if ( v22 != 0 )
            *(uint32_t *)(v22 + 20) = v7;
          if ( (v2[4] & 0x200) != 0 )
          {
            LOWORD(v139) = i;
            v2[6] = sub_655990(v2[6], &v139, 2);
          }
          v7 = 0;
          i = 0;
          v4 = 0;
        }
        else
        {
          v23 = v2[8];
          if ( v23 != 0 )
            *(uint32_t *)(v23 + 16) = 0;
        }
        *v2 = 5;
LABEL_71:
        if ( (v2[4] & 0x400) != 0 )
        {
          v24 = v2[16];
          v129 = v24;
          if ( v24 > v6 )
          {
            v24 = v6;
            v129 = v6;
          }
          if ( v24 != 0 )
          {
            v25 = v2[8];
            if ( v25 != 0 )
            {
              v144 = *(uint32_t *)(v25 + 16);
              if ( v144 != 0 )
              {
                v26 = v2[8];
                v27 = *(uint32_t *)(v26 + 20);
                v28 = *(uint32_t *)(v26 + 24);
                v29 = v27 - v2[16];
                if ( v24 + v29 > v28 )
                  v24 = v28 - v29;
                qmemcpy((void *)(v144 + v29), v128, v24);
                v24 = v129;
                v6 = v127;
                v5 = v128;
              }
            }
            if ( (v2[4] & 0x200) != 0 )
            {
              v30 = sub_655990(v2[6], v5, v129);
              v24 = v129;
              v2[6] = v30;
              v7 = i;
            }
            v6 -= v24;
            v5 += v24;
            v127 = v6;
            v128 = v5;
            v2[16] -= v24;
          }
          if ( v2[16] != 0 )
            goto LABEL_304;
        }
        v2[16] = 0;
        *v2 = 6;
LABEL_85:
        if ( (v2[4] & 0x800) != 0 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v31 = 0;
          do
          {
            v32 = v5[v31];
            v130 = v31 + 1;
            v33 = v2[8];
            v141 = v32;
            if ( v33 != 0 )
            {
              v144 = *(uint32_t *)(v33 + 28);
              if ( v144 != 0 )
              {
                v34 = v2[16];
                if ( v34 < *(uint32_t *)(v33 + 32) )
                {
                  v35 = v144;
                  v6 = v127;
                  v144 = v7;
                  *(uint8_t *)(v35 + v34) = v141;
                  ++v2[16];
                  v7 = v144;
                }
              }
            }
            if ( v141 == 0 )
              break;
            v31 = v130;
          }
          while ( v130 < v6 );
          if ( (v2[4] & 0x200) != 0 )
          {
            v2[6] = sub_655990(v2[6], v5, v130);
            v7 = i;
          }
          v6 -= v130;
          v5 += v130;
          v127 = v6;
          v128 = v5;
          if ( v141 != 0 )
            goto LABEL_304;
        }
        else
        {
          v36 = v2[8];
          if ( v36 != 0 )
            *(uint32_t *)(v36 + 28) = 0;
        }
        v2[16] = 0;
        *v2 = 7;
LABEL_101:
        if ( (v2[4] & 0x1000) != 0 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v37 = 0;
          do
          {
            v38 = v5[v37];
            v131 = v37 + 1;
            v39 = v2[8];
            v141 = v38;
            if ( v39 != 0 )
            {
              v144 = *(uint32_t *)(v39 + 36);
              if ( v144 != 0 )
              {
                v40 = v2[16];
                if ( v40 < *(uint32_t *)(v39 + 40) )
                {
                  v41 = v144;
                  v6 = v127;
                  v144 = v7;
                  *(uint8_t *)(v41 + v40) = v141;
                  ++v2[16];
                  v7 = v144;
                }
              }
            }
            if ( v141 == 0 )
              break;
            v37 = v131;
          }
          while ( v131 < v6 );
          if ( (v2[4] & 0x200) != 0 )
          {
            v2[6] = sub_655990(v2[6], v5, v131);
            v7 = i;
          }
          v6 -= v131;
          v5 += v131;
          v127 = v6;
          v128 = v5;
          if ( v141 != 0 )
            goto LABEL_304;
        }
        else
        {
          v42 = v2[8];
          if ( v42 != 0 )
            *(uint32_t *)(v42 + 36) = 0;
        }
        *v2 = 8;
LABEL_117:
        if ( (v2[4] & 0x200) != 0 )
        {
          if ( v4 < 0x10 )
          {
            while ( v6 != 0 )
            {
              v43 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v43;
              ++v5;
              i = v7;
              v128 = v5;
              if ( v4 >= 0x10 )
                goto LABEL_121;
            }
            goto LABEL_304;
          }
LABEL_121:
          if ( v7 != (uint16_t)v2[6] )
          {
            a1[6] = "header crc mismatch";
            goto LABEL_296;
          }
          v4 = 0;
          i = 0;
        }
        v44 = v2[8];
        if ( v44 != 0 )
        {
          *(uint32_t *)(v44 + 44) = (v2[4] >> 9) & 1;
          *(uint32_t *)(v2[8] + 48) = 1;
        }
        v45 = sub_655990(0, 0, 0);
        v2[6] = v45;
        a1[12] = (uint8_t *)v45;
        v7 = i;
        *v2 = 11;
        goto LABEL_297;
      case 2:
        if ( v4 < 0x20 )
          goto LABEL_44;
        goto LABEL_46;
      case 3:
        if ( v4 < 0x10 )
          goto LABEL_52;
        goto LABEL_54;
      case 4:
        goto LABEL_59;
      case 5:
        goto LABEL_71;
      case 6:
        goto LABEL_85;
      case 7:
        goto LABEL_101;
      case 8:
        goto LABEL_117;
      case 9:
        for ( ; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v46 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v46;
          ++v5;
          BYTE2(i) = BYTE2(v7);
        }
        LOBYTE(v47) = 0;
        HIBYTE(v47) = BYTE2(i);
        v48 = v47 + (((v7 << 16) + (v7 & 0xFF00)) << 8) + HIBYTE(v7);
        v2[6] = v48;
        a1[12] = (uint8_t *)v48;
        v7 = 0;
        i = 0;
        v4 = 0;
        *v2 = 10;
LABEL_131:
        if ( v2[3] == 0 )
        {
          a1[3] = (uint8_t *)v140;
          a1[1] = (uint8_t *)v6;
          *a1 = v5;
          a1[4] = (uint8_t *)v138;
          v2[15] = v4;
          v2[14] = v7;
          return 2;
        }
        v49 = sub_655460(0, 0, 0);
        v2[6] = v49;
        a1[12] = (uint8_t *)v49;
        v7 = i;
        *v2 = 11;
LABEL_133:
        if ( a2 == 5 )
          goto LABEL_304;
LABEL_134:
        if ( v2[1] != 0 )
        {
          v50 = v4 & 7;
          v7 >>= v50;
          v4 -= v50;
          *v2 = 24;
          i = v7;
        }
        else
        {
          if ( v4 < 3 )
          {
            while ( v6 != 0 )
            {
              v51 = *v5 << v4;
              --v6;
              v4 += 8;
              v127 = v6;
              v7 += v51;
              v128 = ++v5;
              if ( v4 >= 3 )
                goto LABEL_139;
            }
            goto LABEL_304;
          }
LABEL_139:
          v52 = v7 & 1;
          v53 = v7 >> 1;
          v2[1] = v52;
          v54 = v4 - 1;
          switch ( v53 & 3 )
          {
            case 0u:
              v7 = v53 >> 2;
              *v2 = 13;
              i = v7;
              v4 = v54 - 2;
              break;
            case 1u:
              v7 = v53 >> 2;
              v2[19] = (int)"`\a";
              v2[21] = 9;
              v2[20] = (int)&unk_73FA80;
              v2[22] = 5;
              *v2 = 18;
              i = v7;
              v4 = v54 - 2;
              break;
            case 2u:
              v7 = v53 >> 2;
              *v2 = 15;
              i = v7;
              v4 = v54 - 2;
              break;
            case 3u:
              a1[6] = "invalid block type";
              *v2 = 27;
              v7 = v53 >> 2;
              i = v7;
              v4 = v54 - 2;
              break;
          }
        }
        goto LABEL_297;
      case 10:
        goto LABEL_131;
      case 11:
        goto LABEL_133;
      case 12:
        goto LABEL_134;
      case 13:
        v55 = v4 & 7;
        v7 >>= v55;
        v4 -= v55;
        for ( i = v7; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v56 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v56;
          ++v5;
          i = v7;
        }
        v57 = (uint16_t)v7;
        if ( (uint16_t)v7 != ~v7 >> 16 )
        {
          a1[6] = "invalid stored block lengths";
          goto LABEL_296;
        }
        v7 = 0;
        v2[16] = v57;
        i = 0;
        v4 = 0;
        *v2 = 14;
LABEL_150:
        v58 = v2[16];
        v132 = v58;
        if ( v58 == 0 )
          goto LABEL_228;
        if ( v58 > v6 )
        {
          v58 = v6;
          v132 = v6;
        }
        if ( v58 > v138 )
        {
          v58 = v138;
          v132 = v138;
        }
        if ( v58 == 0 )
          goto LABEL_304;
        qmemcpy(v140, v128, v58);
        v127 -= v132;
        v128 += v132;
        v59 = v2[16] - v132;
        v138 -= v132;
        v6 = v127;
        v140 += v132;
        v5 = v128;
        v2[16] = v59;
        goto LABEL_297;
      case 14:
        goto LABEL_150;
      case 15:
        for ( ; v4 < 0xE; v128 = ++v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v60 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v60;
        }
        v61 = (v7 & 0x1F) + 257;
        v62 = v7 >> 5;
        v63 = v62;
        v2[24] = v61;
        v62 >>= 5;
        v2[23] = (v62 & 0xF) + 4;
        v64 = v2[24];
        v65 = (v63 & 0x1F) + 1;
        v7 = v62 >> 4;
        v4 -= 14;
        v2[25] = v65;
        i = v7;
        if ( v64 > 0x11E || v65 > 0x1E )
        {
          a1[6] = "too many length or distance symbols";
          goto LABEL_296;
        }
        v2[26] = 0;
        *v2 = 16;
LABEL_163:
        if ( v2[26] < (unsigned int)v2[23] )
        {
          while ( v4 >= 3 )
          {
LABEL_167:
            v67 = v7;
            v7 >>= 3;
            v4 -= 3;
            i = v7;
            *((uint16_t *)v2 + (uint16_t)word_73FB00[v2[26]] + 56) = v67 & 7;
            v68 = v2[26] + 1;
            v2[26] = v68;
            if ( v68 >= v2[23] )
              goto LABEL_168;
          }
          while ( v6 != 0 )
          {
            v66 = *v5 << v4;
            --v6;
            v4 += 8;
            v127 = v6;
            v7 += v66;
            v128 = ++v5;
            if ( v4 >= 3 )
              goto LABEL_167;
          }
          goto LABEL_304;
        }
LABEL_168:
        if ( (unsigned int)v2[26] < 0x13 )
        {
          do
          {
            *((uint16_t *)v2 + (uint16_t)word_73FB00[v2[26]] + 56) = 0;
            v69 = v2[26] + 1;
            v2[26] = v69;
          }
          while ( v69 < 0x13 );
        }
        v2[27] = (int)(v2 + 332);
        v2[19] = (int)(v2 + 332);
        v2[21] = 7;
        v143 = sub_654F70(0, v2 + 28, 19, v2 + 27, v2 + 21, v2 + 188);
        v7 = i;
        if ( v143 != 0 )
        {
          a1[6] = "invalid code lengths set";
          goto LABEL_296;
        }
        v2[26] = 0;
        *v2 = 17;
LABEL_174:
        if ( v2[26] < (unsigned int)(v2[24] + v2[25]) )
        {
          while ( 1 )
          {
            v146 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            BYTE1(v70) = BYTE1(v146);
            if ( BYTE1(v146) > v4 )
              break;
LABEL_178:
            if ( HIWORD(v146) >= 0x10u )
            {
              if ( HIWORD(v146) == 16 )
              {
                v74 = BYTE1(v70);
                v134 = v74;
                if ( v4 < v74 + 2 )
                {
                  while ( v6 != 0 )
                  {
                    v75 = *v5 << v4;
                    v74 = v134;
                    --v6;
                    v4 += 8;
                    v7 += v75;
                    ++v5;
                    v127 = v6;
                    v128 = v5;
                    if ( v4 >= v134 + 2 )
                      goto LABEL_187;
                  }
                  goto LABEL_304;
                }
LABEL_187:
                v7 >>= v74;
                v4 -= v74;
                v76 = v2[26];
                i = v7;
                if ( v76 == 0 )
                {
                  a1[6] = "invalid bit length repeat";
                  goto LABEL_296;
                }
                v141 = *((uint16_t *)v2 + v76 + 55);
                v77 = (v7 & 3) + 3;
                v7 >>= 2;
                v4 -= 2;
              }
              else
              {
                v78 = BYTE1(v70);
                if ( HIWORD(v146) == 17 )
                {
                  if ( v4 < (unsigned int)BYTE1(v70) + 3 )
                  {
                    while ( v6 != 0 )
                    {
                      v79 = *v5 << v4;
                      --v6;
                      v4 += 8;
                      v127 = v6;
                      v7 += v79;
                      v78 = BYTE1(v70);
                      v128 = ++v5;
                      if ( v4 >= (unsigned int)BYTE1(v70) + 3 )
                        goto LABEL_193;
                    }
                    goto LABEL_304;
                  }
LABEL_193:
                  v80 = v7 >> v78;
                  v81 = -3;
                  v77 = (v80 & 7) + 3;
                  v7 = v80 >> 3;
                }
                else
                {
                  if ( v4 < (unsigned int)BYTE1(v70) + 7 )
                  {
                    while ( v6 != 0 )
                    {
                      v82 = *v5 << v4;
                      --v6;
                      v4 += 8;
                      v127 = v6;
                      v7 += v82;
                      v78 = BYTE1(v70);
                      v128 = ++v5;
                      if ( v4 >= (unsigned int)BYTE1(v70) + 7 )
                        goto LABEL_197;
                    }
                    goto LABEL_304;
                  }
LABEL_197:
                  v83 = v7 >> v78;
                  v81 = -7;
                  v77 = (v83 & 0x7F) + 11;
                  v7 = v83 >> 7;
                }
                v141 = 0;
                v4 += v81 - v78;
              }
              i = v7;
              if ( v77 + v2[26] > (unsigned int)(v2[24] + v2[25]) )
              {
                v6 = v127;
                a1[6] = "invalid bit length repeat";
                goto LABEL_296;
              }
              if ( v77 != 0 )
              {
                v84 = v141;
                do
                {
                  *((uint16_t *)v2 + v2[26] + 56) = v84;
                  --v77;
                  ++v2[26];
                }
                while ( v77 != 0 );
              }
              v6 = v127;
            }
            else
            {
              v72 = BYTE1(v70);
              v133 = v72;
              if ( v4 < v72 )
              {
                while ( v6 != 0 )
                {
                  v73 = *v5 << v4;
                  v72 = v133;
                  --v6;
                  v4 += 8;
                  v7 += v73;
                  ++v5;
                  v127 = v6;
                  v128 = v5;
                  if ( v4 >= v133 )
                    goto LABEL_182;
                }
                goto LABEL_304;
              }
LABEL_182:
              v7 >>= v72;
              v4 -= v72;
              *((uint16_t *)v2 + v2[26] + 56) = HIWORD(v146);
              i = v7;
              ++v2[26];
            }
            if ( v2[26] >= (unsigned int)(v2[24] + v2[25]) )
              goto LABEL_205;
          }
          while ( v6 != 0 )
          {
            v71 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v71;
            ++v5;
            v127 = v6;
            v70 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            v128 = v5;
            v146 = v70;
            if ( BYTE1(v70) <= v4 )
              goto LABEL_178;
          }
          goto LABEL_304;
        }
LABEL_205:
        if ( *v2 == 27 )
          goto LABEL_297;
        v2[27] = (int)(v2 + 332);
        v2[19] = (int)(v2 + 332);
        v85 = v2[24];
        v2[21] = 9;
        v143 = sub_654F70(1, v2 + 28, v85, v2 + 27, v2 + 21, v2 + 188);
        if ( v143 != 0 )
        {
          v7 = i;
          a1[6] = "invalid literal/lengths set";
          goto LABEL_296;
        }
        v2[20] = v2[27];
        v86 = v2[24];
        v2[22] = 6;
        v143 = sub_654F70(2, (char *)v2 + 2 * v86 + 112, v2[25], v2 + 27, v2 + 22, v2 + 188);
        if ( v143 != 0 )
        {
          a1[6] = "invalid distances set";
          v7 = i;
          goto LABEL_296;
        }
        v7 = i;
        *v2 = 18;
LABEL_213:
        if ( v6 >= 6 && v138 >= 0x102 )
        {
          v87 = v140;
          a1[4] = (uint8_t *)v138;
          v88 = v142;
          a1[3] = (uint8_t *)v87;
          *a1 = v5;
          a1[1] = (uint8_t *)v6;
          v2[14] = i;
          v2[15] = v4;
          sub_6547D0(a1, v88);
          v89 = (unsigned int)a1[4];
          v5 = *a1;
          v6 = (unsigned int)a1[1];
          v7 = v2[14];
          v4 = v2[15];
          v140 = (char *)a1[3];
          v138 = v89;
          v128 = v5;
          v127 = v6;
          i = v7;
          goto LABEL_297;
        }
        v146 = *(uint32_t *)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
        v90 = (uint8_t *)v146;
        if ( BYTE1(v146) > v4 )
        {
          while ( v6 != 0 )
          {
            v91 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v91;
            ++v5;
            v127 = v6;
            v90 = *(uint8_t **)(v2[19] + 4 * (v7 & ((1 << v2[21]) - 1)));
            v128 = v5;
            v146 = (unsigned int)v90;
            if ( BYTE1(v90) <= v4 )
              goto LABEL_219;
          }
          goto LABEL_304;
        }
LABEL_219:
        if ( (uint8_t)v90 != 0 && ((uint8_t)v90 & 0xF0) == 0 )
        {
          v141 = (int)v90;
          v146 = *(uint32_t *)(v2[19] + 4
                                    * (HIWORD(v146) + ((v7 & ((1 << (BYTE1(v90) + (uint8_t)v90)) - 1)) >> SBYTE1(v90))));
          v92 = BYTE1(v90);
          v135 = BYTE1(v90);
          if ( BYTE1(v90) + (unsigned int)BYTE1(v146) > v4 )
          {
            while ( v6 != 0 )
            {
              --v6;
              v7 += *v5++ << v4;
              v4 += 8;
              v127 = v6;
              v128 = v5;
              v93 = (uint8_t)BYTE1(*(uint32_t *)(v2[19]
                                                     + 4 * (HIWORD(v141) + ((v7 & ((1 << (v135 + v141)) - 1)) >> v135))));
              v146 = *(uint32_t *)(v2[19] + 4 * (HIWORD(v141) + ((v7 & ((1 << (v135 + v141)) - 1)) >> v135)));
              v92 = v135;
              if ( v135 + v93 <= v4 )
                goto LABEL_224;
            }
            goto LABEL_304;
          }
LABEL_224:
          LOWORD(v90) = v146;
          v7 >>= v92;
          v4 -= v92;
        }
        v7 >>= SBYTE1(v90);
        v4 -= BYTE1(v90);
        i = v7;
        v2[16] = HIWORD(v146);
        if ( (uint8_t)v90 == 0 )
        {
          *v2 = 23;
          goto LABEL_297;
        }
        if ( ((uint8_t)v90 & 0x20) != 0 )
        {
LABEL_228:
          *v2 = 11;
          goto LABEL_297;
        }
        if ( ((uint8_t)v90 & 0x40) != 0 )
        {
          a1[6] = "invalid literal/length code";
          goto LABEL_296;
        }
        v2[18] = (uint8_t)v90 & 0xF;
        *v2 = 19;
LABEL_232:
        v94 = v2[18];
        if ( v94 != 0 )
        {
          if ( v4 < v94 )
          {
            while ( v6 != 0 )
            {
              v95 = *v5 << v4;
              --v6;
              v4 += 8;
              v7 += v95;
              ++v5;
              v127 = v6;
              v128 = v5;
              if ( v4 >= v2[18] )
                goto LABEL_236;
            }
            goto LABEL_304;
          }
LABEL_236:
          v2[16] += v7 & ((1 << v2[18]) - 1);
          v96 = v2[18];
          v7 >>= v96;
          v4 -= v96;
        }
        *v2 = 20;
LABEL_238:
        v146 = *(uint32_t *)(v2[20] + 4 * (v7 & ((1 << v2[22]) - 1)));
        v97 = (uint8_t *)v146;
        if ( BYTE1(v146) > v4 )
        {
          while ( v6 != 0 )
          {
            v98 = *v5 << v4;
            --v6;
            v4 += 8;
            v7 += v98;
            ++v5;
            v127 = v6;
            v97 = *(uint8_t **)(v2[20] + 4 * (v7 & ((1 << v2[22]) - 1)));
            v128 = v5;
            v146 = (unsigned int)v97;
            if ( BYTE1(v97) <= v4 )
              goto LABEL_241;
          }
          goto LABEL_304;
        }
LABEL_241:
        if ( ((uint8_t)v97 & 0xF0) == 0 )
        {
          v141 = (int)v97;
          v146 = *(uint32_t *)(v2[20] + 4
                                    * (HIWORD(v146) + ((v7 & ((1 << (BYTE1(v97) + (uint8_t)v97)) - 1)) >> SBYTE1(v97))));
          v99 = BYTE1(v97);
          v136 = BYTE1(v97);
          if ( BYTE1(v97) + (unsigned int)BYTE1(v146) > v4 )
          {
            while ( v6 != 0 )
            {
              --v6;
              v7 += *v5++ << v4;
              v4 += 8;
              v127 = v6;
              v128 = v5;
              v100 = (uint8_t)BYTE1(*(uint32_t *)(v2[20]
                                                      + 4 * (HIWORD(v141) + ((v7 & ((1 << (v136 + v141)) - 1)) >> v136))));
              v146 = *(uint32_t *)(v2[20] + 4 * (HIWORD(v141) + ((v7 & ((1 << (v136 + v141)) - 1)) >> v136)));
              v99 = v136;
              if ( v136 + v100 <= v4 )
                goto LABEL_245;
            }
            goto LABEL_304;
          }
LABEL_245:
          LOWORD(v97) = v146;
          v7 >>= v99;
          v4 -= v99;
        }
        v7 >>= SBYTE1(v97);
        v4 -= BYTE1(v97);
        i = v7;
        if ( ((uint8_t)v97 & 0x40) != 0 )
        {
          a1[6] = "invalid distance code";
          goto LABEL_296;
        }
        v2[17] = HIWORD(v146);
        v2[18] = (uint8_t)v97 & 0xF;
        *v2 = 21;
LABEL_249:
        v101 = v2[18];
        if ( v101 != 0 )
        {
          if ( v4 < v101 )
          {
            while ( v6 != 0 )
            {
              v102 = *v5 << v4;
              --v6;
              v4 += 8;
              v7 += v102;
              ++v5;
              v127 = v6;
              v128 = v5;
              if ( v4 >= v2[18] )
                goto LABEL_253;
            }
            goto LABEL_304;
          }
LABEL_253:
          v2[17] += v7 & ((1 << v2[18]) - 1);
          v103 = v2[18];
          v7 >>= v103;
          v4 -= v103;
          i = v7;
        }
        if ( v2[17] > v142 + v2[11] - v138 )
        {
          a1[6] = "invalid distance too far back";
          goto LABEL_296;
        }
        *v2 = 22;
LABEL_257:
        if ( v138 == 0 )
          goto LABEL_304;
        v104 = v2[17];
        if ( v104 <= v142 - v138 )
        {
          v108 = &v140[-v104];
          v105 = v2[16];
          v141 = (int)v108;
          v144 = v105;
          goto LABEL_265;
        }
        v105 = v104 - (v142 - v138);
        v106 = v2[12];
        v137 = v105;
        if ( v105 <= v106 )
        {
          v107 = v2[12] + v2[13] - v105;
        }
        else
        {
          v105 -= v106;
          v137 = v105;
          v107 = v2[10] + v2[13] - v105;
        }
        v141 = v107;
        v144 = v2[16];
        if ( v105 > v144 )
        {
          v105 = v144;
LABEL_265:
          v137 = v105;
        }
        if ( v105 > v138 )
        {
          v105 = v138;
          v137 = v138;
        }
        v138 -= v105;
        v2[16] = v144 - v105;
        do
        {
          v109 = v140;
          *v140 = *(uint8_t *)v141;
          v140 = v109 + 1;
          v110 = v137 == 1;
          ++v141;
          --v137;
        }
        while ( !v110 );
        if ( v2[16] == 0 )
          *v2 = 18;
        goto LABEL_297;
      case 16:
        goto LABEL_163;
      case 17:
        goto LABEL_174;
      case 18:
        goto LABEL_213;
      case 19:
        goto LABEL_232;
      case 20:
        goto LABEL_238;
      case 21:
        goto LABEL_249;
      case 22:
        goto LABEL_257;
      case 23:
        if ( v3 == 0 )
          goto LABEL_304;
        v111 = v140;
        *v140 = *((uint8_t *)v2 + 64);
        v140 = v111 + 1;
        --v138;
        *v2 = 18;
        goto LABEL_297;
      case 24:
        if ( v2[2] == 0 )
          goto LABEL_288;
        for ( ; v4 < 0x20; v128 = v5 )
        {
          if ( v6 == 0 )
            goto LABEL_304;
          v112 = *v5 << v4;
          --v6;
          v4 += 8;
          v127 = v6;
          v7 += v112;
          ++v5;
          i = v7;
        }
        v113 = v142 - v138;
        a1[5] += v142 - v138;
        v114 = v113 + v2[7];
        v142 = v113;
        v2[7] = v114;
        if ( v113 != 0 )
        {
          v115 = v2[6];
          if ( v2[4] != 0 )
            v116 = sub_655990(v115, &v140[-v142], v142);
          else
            v116 = sub_655460(v115, &v140[-v142], v142);
          v2[6] = v116;
          a1[12] = (uint8_t *)v116;
          v7 = i;
        }
        v110 = v2[4] == 0;
        v142 = v138;
        v117 = v7;
        if ( v110 )
        {
          LOBYTE(v118) = 0;
          HIBYTE(v118) = BYTE2(i);
          v117 = HIBYTE(v7) + v118 + (((v7 << 16) + (v7 & 0xFF00)) << 8);
          v144 = v117;
        }
        if ( v117 != v2[6] )
        {
          a1[6] = "incorrect data check";
LABEL_296:
          *v2 = 27;
LABEL_297:
          v8 = *v2;
          if ( (unsigned int)*v2 > 0x1C )
            return -2;
          v3 = v138;
          continue;
        }
        v7 = 0;
        i = 0;
        v4 = 0;
LABEL_288:
        *v2 = 25;
LABEL_289:
        if ( v2[2] == 0 || v2[4] == 0 )
          goto LABEL_301;
        if ( v4 < 0x20 )
        {
          while ( v6 != 0 )
          {
            v119 = *v5 << v4;
            --v6;
            v4 += 8;
            v127 = v6;
            v7 += v119;
            ++v5;
            i = v7;
            v128 = v5;
            if ( v4 >= 0x20 )
              goto LABEL_294;
          }
          goto LABEL_304;
        }
LABEL_294:
        if ( v7 != v2[7] )
        {
          a1[6] = "incorrect length check";
          goto LABEL_296;
        }
        v7 = 0;
        v4 = 0;
LABEL_301:
        *v2 = 26;
LABEL_302:
        v143 = 1;
LABEL_304:
        a1[3] = (uint8_t *)v140;
        a1[4] = (uint8_t *)v138;
        *a1 = v5;
        a1[1] = (uint8_t *)v6;
        v2[14] = v7;
        v120 = v2[10];
        v2[15] = v4;
        if ( (v120 != 0 || *v2 < 24 && (uint8_t *)v142 != a1[4]) && sub_653000(a1) != 0 )
        {
          *v2 = 28;
          return -4;
        }
        else
        {
          v121 = v145 - (uint32_t)a1[1];
          v122 = v142 - (uint32_t)a1[4];
          v123 = &a1[5][v122];
          a1[2] += v121;
          a1[5] = v123;
          v124 = v2[2];
          v2[7] += v122;
          if ( v124 != 0 && v122 != 0 )
          {
            if ( v2[4] != 0 )
              v125 = sub_655990(v2[6], &a1[3][-v122], v122);
            else
              v125 = sub_655460(v2[6], &a1[3][-v122], v122);
            v2[6] = v125;
            a1[12] = (uint8_t *)v125;
          }
          a1[11] = (uint8_t *)(v2[15] + (*v2 != 11 ? 0 : 0x80) + (v2[1] != 0 ? 0x40 : 0));
          if ( (v121 != 0 || v122 != 0) && a2 != 4 )
          {
            return v143;
          }
          else
          {
            result = v143;
            if ( v143 == 0 )
              return -5;
          }
        }
        return result;
      case 25:
        goto LABEL_289;
      case 26:
        goto LABEL_302;
      case 27:
        v143 = -3;
        goto LABEL_304;
      case 28:
        return -4;
      default:
        return -2;
    }
  }
}


// ------------------------------------------------------------
// 0x654750 sub_654750
// ------------------------------------------------------------
int /*cdecl*/ sub_654750(uint32_t *a1)
{
  int v1; // eax
  void (/*cdecl*/ *v2)(uint32_t, int); // ecx
  int v3; // eax

  if ( a1 == nullptr )
    return -2;
  v1 = a1[7];
  if ( v1 == 0 )
    return -2;
  v2 = (void (/*cdecl*/ *)(uint32_t, int))a1[9];
  if ( v2 == nullptr )
    return -2;
  v3 = *(uint32_t *)(v1 + 52);
  if ( v3 != 0 )
    v2(a1[10], v3);
  ((void (/*cdecl*/ *)(uint32_t, uint32_t))a1[9])(a1[10], a1[7]);
  a1[7] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6547A0 sub_6547A0
// ------------------------------------------------------------
void */*cdecl*/ sub_6547A0(int a1, int a2, int a3)
{
  return malloc(a3 * a2);
}



// ------------------------------------------------------------
// 0x6547C0 sub_6547C0
// ------------------------------------------------------------
void /*cdecl*/ sub_6547C0(int a1, void *Block)
{
  free(Block);
}



// ------------------------------------------------------------
// 0x6548D8 sub_6548D8
// ------------------------------------------------------------
int */*usercall*/ sub_6548D8@<eax>(__m64 a1@<mm0>, __m64 a2@<mm1>, int *a3, int a4)
{
  unsigned int v4; // kr00_4
  uint32_t *v5; // edi
  int v6; // edx
  int v7; // ecx
  unsigned int v8; // eax
  unsigned int v9; // ecx
  char *v10; // edx
  unsigned int v11; // ebp
  unsigned int v12; // ebx
  uint8_t *v13; // esi
  unsigned int v14; // ecx
  unsigned int v15; // ecx
  int v16; // eax
  char *v17; // edi
  unsigned int v18; // kr04_4
  unsigned int v19; // kr08_4
  uint16_t v30; // ax
  char v31; // cl
  unsigned int i; // eax
  unsigned int v33; // edx
  uint8_t v34; // cl
  uint8_t v35; // ch
  uint16_t v36; // ax
  char v37; // cl
  int v38; // eax
  uint16_t v39; // ax
  char v40; // cl
  unsigned int j; // eax
  unsigned int v42; // edx
  uint8_t v43; // cl
  uint8_t v44; // ch
  uint16_t v45; // ax
  char v46; // cl
  int v47; // eax
  char *v48; // esi
  char v49; // al
  char v50; // dl
  char *v51; // edi
  char *v52; // edi
  char v53; // al
  unsigned int v54; // ecx
  char *v55; // esi
  unsigned int v56; // eax
  unsigned int v57; // ecx
  unsigned int v58; // ecx
  __m64 v59; // mm4
  __m64 v60; // mm3
  __m64 v61; // mm5
  __m64 v62; // mm2
  __m64 v63; // mm7
  __m64 v64; // mm7
  int v65; // eax
  unsigned int v66; // edx
  unsigned int v67; // eax
  __m64 v68; // mm7
  __m64 v69; // mm7
  int v70; // eax
  unsigned int k; // eax
  unsigned int v72; // eax
  unsigned int v73; // ecx
  char v74; // dl
  char *v75; // esi
  char *v76; // edi
  char *v77; // edi
  char v78; // al
  unsigned int v79; // ecx
  char *v80; // esi
  unsigned int v81; // ecx
  unsigned int v82; // ecx
  const char *v83; // ecx
  int v84; // edx
  int *result; // eax
  int v86; // edx
  int v87; // esi
  unsigned int v88; // ebx
  char *v89; // [esp+4h] [ebp-64h]
  unsigned int v90; // [esp+8h] [ebp-60h]
  unsigned int v91; // [esp+Ch] [ebp-5Ch]
  unsigned int v92; // [esp+10h] [ebp-58h]
  unsigned int v93; // [esp+14h] [ebp-54h]
  unsigned int v94; // [esp+18h] [ebp-50h]
  unsigned int v95; // [esp+1Ch] [ebp-4Ch]
  int v96; // [esp+20h] [ebp-48h]
  unsigned int v97; // [esp+24h] [ebp-44h]
  uint8_t *v98; // [esp+28h] [ebp-40h]
  unsigned int v99; // [esp+2Ch] [ebp-3Ch]
  uint8_t v100[12]; // [esp+30h] [ebp-38h] BYREF
  char *v101; // [esp+3Ch] [ebp-2Ch]
  uint8_t *v102; // [esp+40h] [ebp-28h]
  unsigned int v103; // [esp+44h] [ebp-24h]
  unsigned int v104; // [esp+48h] [ebp-20h]
  char *v105; // [esp+4Ch] [ebp-1Ch]
  char *v106; // [esp+50h] [ebp-18h]
  unsigned int v107; // [esp+54h] [ebp-14h]

  v4 = __readeflags();
  v107 = v4;
  v5 = (uint32_t *)a3[7];
  v6 = *a3 + a3[1] - 11;
  v102 = (uint8_t *)*a3;
  v98 = (uint8_t *)v6;
  v7 = a3[4];
  v106 = (char *)a3[3];
  v101 = &v106[v7 - a4];
  v97 = (unsigned int)&v106[v7 - 257];
  v95 = v5[19];
  v96 = v5[20];
  v93 = (1 << v5[21]) - 1;
  v94 = (1 << v5[22]) - 1;
  v8 = v5[10];
  v9 = v5[12];
  v10 = (char *)v5[13];
  v104 = v8;
  v103 = v9;
  v105 = v10;
  v11 = v5[14];
  v12 = v5[15];
  v13 = v102;
  v14 = (unsigned int)v98;
  if ( v98 > v102 )
  {
    while ( ((uint8_t)v13 & 3) != 0 )
    {
      v16 = *v13++;
      v14 = v12;
      v12 += 8;
      v8 = v16 << v14;
      v11 |= v8;
    }
  }
  else
  {
    v15 = v98 + 11 - v102;
    qmemcpy(v100, v102, v15);
    v8 = 0;
    memset(&v100[v15], 0, 12 - v15);
    v14 = 0;
    v13 = v100;
    v98 = v100;
  }
  v17 = v106;
  while ( dword_7960F0 != 2 )
  {
    if ( (unsigned int)dword_7960F0 > 2 )
    {
      while ( 1 )
      {
        if ( (uint8_t)v12 <= 0xFu )
        {
          v30 = *(uint16_t *)v13;
          v13 += 2;
          v31 = v12;
          LOBYTE(v12) = v12 + 16;
          v11 |= v30 << v31;
        }
        for ( i = *(uint32_t *)(v95 + 4 * (v11 & v93)); ; i = *(uint32_t *)(v95 + 4 * (v33 + (v11 & ((1 << i) - 1)))) )
        {
          LOBYTE(v12) = v12 - BYTE1(i);
          v11 >>= SBYTE1(i);
          if ( (uint8_t)i == 0 )
          {
            *v17++ = BYTE2(i);
            goto LABEL_22;
          }
          v33 = HIWORD(i);
          if ( (i & 0x10) != 0 )
            break;
          if ( (i & 0x40) != 0 )
            goto LABEL_97;
        }
        v34 = i & 0xF;
        if ( (i & 0xF) != 0 )
        {
          if ( (uint8_t)v12 < v34 )
          {
            v35 = i & 0xF;
            v36 = *(uint16_t *)v13;
            v13 += 2;
            v37 = v12;
            LOBYTE(v12) = v12 + 16;
            v11 |= v36 << v37;
            v34 = v35;
          }
          LOBYTE(v12) = v12 - v34;
          v38 = v11 & ((1 << v34) - 1);
          v11 >>= v34;
          v33 += v38;
        }
        v99 = v33;
        if ( (uint8_t)v12 <= 0xFu )
        {
          v39 = *(uint16_t *)v13;
          v13 += 2;
          v40 = v12;
          LOBYTE(v12) = v12 + 16;
          v11 |= v39 << v40;
        }
        for ( j = *(uint32_t *)(v96 + 4 * (v11 & v94)); ; j = *(uint32_t *)(v96 + 4 * (v42 + (v11 & ((1 << j) - 1)))) )
        {
          v42 = HIWORD(j);
          LOBYTE(v12) = v12 - BYTE1(j);
          v11 >>= SBYTE1(j);
          if ( (j & 0x10) != 0 )
            break;
          if ( (j & 0x40) != 0 )
            goto LABEL_96;
        }
        v43 = j & 0xF;
        if ( (j & 0xF) != 0 )
        {
          if ( (uint8_t)v12 < v43 )
          {
            v44 = j & 0xF;
            v45 = *(uint16_t *)v13;
            v13 += 2;
            v46 = v12;
            LOBYTE(v12) = v12 + 16;
            v11 |= v45 << v46;
            v43 = v44;
          }
          LOBYTE(v12) = v12 - v43;
          v47 = v11 & ((1 << v43) - 1);
          v11 >>= v43;
          v42 += v47;
        }
        else if ( v42 == 1 && v101 != v17 )
        {
          v52 = v17 - 1;
          v53 = *v52;
          v52[1] = *v52;
          v52[2] = v53;
          v52[3] = v53;
          v52 += 4;
          memset(v52, v53, v99 - 3);
          v17 = &v52[v99 - 3];
          goto LABEL_22;
        }
        v102 = v13;
        if ( v17 - v101 >= v42 )
        {
          v48 = &v17[-v42];
          *v17 = v17[-v42];
          v49 = v17[-v42 + 1];
          v50 = v17[-v42 + 2];
          v17[1] = v49;
          v17[2] = v50;
          v51 = v17 + 3;
          qmemcpy(v51, v48 + 3, v99 - 3);
          v17 = &v51[v99 - 3];
          v13 = v102;
          goto LABEL_22;
        }
        if ( v104 < v42 )
          goto LABEL_100;
        v54 = v42 + v101 - v17;
        if ( v103 != 0 )
        {
          if ( v54 > v103 )
          {
            v55 = &v105[v104 + v103 - v54];
            v57 = v54 - v103;
            v56 = v99;
            if ( v99 > v57 )
            {
              v56 = v99 - v57;
              qmemcpy(v17, v55, v57);
              v17 += v57;
              v55 = v105;
              v58 = v103;
              if ( v56 > v103 )
              {
                v56 -= v103;
                qmemcpy(v17, v105, v103);
                v17 += v58;
                v55 = &v17[-v42];
              }
            }
            goto LABEL_57;
          }
          v55 = &v105[v103 - v54];
          v56 = v99;
          if ( v99 > v54 )
          {
LABEL_56:
            v56 = v99 - v54;
            qmemcpy(v17, v55, v54);
            v17 += v54;
            v55 = &v17[-v42];
          }
        }
        else
        {
          v55 = &v105[v104 - v54];
          v56 = v99;
          if ( v99 > v54 )
            goto LABEL_56;
        }
LABEL_57:
        qmemcpy(v17, v55, v56);
        v17 += v56;
        v13 = v102;
LABEL_22:
        if ( v97 <= (unsigned int)v17 || v98 <= v13 )
          goto LABEL_104;
      }
    }
    v92 = v8;
    v91 = v12;
    v90 = v14;
    v89 = v10;
    v18 = __readeflags();
    __writeeflags(v18 ^ 0x200000);
    v19 = __readeflags();
    if ( v18 == v19 )
      goto LABEL_15;
    _EAX = 0;
    __asm { cpuid }
    if ( _EBX != 1970169159 )
      goto LABEL_15;
    if ( _ECX != 1818588270 )
      goto LABEL_15;
    if ( _EDX != 1231384169 )
      goto LABEL_15;
    _EAX = 1;
    __asm { cpuid }
    if ( ((_EAX >> 8) & 0xF) != 6 )
      goto LABEL_15;
    if ( ((unsigned int)&unk_800000 & _EDX) != 0 )
      dword_7960F0 = 2;
    else
LABEL_15:
      dword_7960F0 = 3;
    v10 = v89;
    v14 = v90;
    v12 = v91;
    v8 = v92;
  }
  _m_empty();
  a1 = _mm_cvtsi32_si64(v11);
  v11 = v12;
  v59 = _mm_cvtsi32_si64(v93);
  v60 = v59;
  v61 = _mm_cvtsi32_si64(v94);
  v62 = v61;
  a2.m64_u64 = 0;
  v12 = v95;
LABEL_59:
  a1 = _m_psrlq(a1, a2);
  if ( v11 <= 0x20 )
  {
    v63 = _mm_cvtsi32_si64(*(uint32_t *)v13);
    v13 += 4;
    v64 = _m_psllqi(v63, v11);
    v11 += 32;
    a1 = _m_por(a1, v64);
  }
  v65 = _mm_cvtsi64_si32(_m_pand(v59, a1));
  v59 = v60;
  for ( i = *(uint32_t *)(v12 + 4 * v65); ; i = *(uint32_t *)(v12
                                                        + 4 * (v66 + (dword_654854[i & 0xF] & _mm_cvtsi64_si32(a1)))) )
  {
    a2 = _mm_cvtsi32_si64(BYTE1(i));
    v11 -= BYTE1(i);
    if ( (uint8_t)i == 0 )
    {
      *v17++ = BYTE2(i);
LABEL_64:
      if ( v97 <= (unsigned int)v17 || v98 <= v13 )
        goto LABEL_104;
      goto LABEL_59;
    }
    v66 = HIWORD(i);
    if ( (i & 0x10) != 0 )
    {
      v67 = i & 0xF;
      if ( v67 != 0 )
      {
        a1 = _m_psrlq(a1, a2);
        a2 = _mm_cvtsi32_si64(v67);
        v11 -= v67;
        v66 += dword_654854[v67] & _mm_cvtsi64_si32(a1);
      }
      a1 = _m_psrlq(a1, a2);
      if ( v11 <= 0x20 )
      {
        v68 = _mm_cvtsi32_si64(*(uint32_t *)v13);
        v13 += 4;
        v69 = _m_psllqi(v68, v11);
        v11 += 32;
        a1 = _m_por(a1, v69);
      }
      v70 = _mm_cvtsi64_si32(_m_pand(v61, a1));
      v61 = v62;
      for ( k = *(uint32_t *)(v96 + 4 * v70);
            ;
            k = *(uint32_t *)(v96 + 4 * (v12 + (dword_654854[k & 0xF] & _mm_cvtsi64_si32(a1)))) )
      {
        v12 = HIWORD(k);
        v11 -= BYTE1(k);
        a2 = _mm_cvtsi32_si64(BYTE1(k));
        if ( (k & 0x10) != 0 )
          break;
        if ( (k & 0x40) != 0 )
        {
LABEL_96:
          v83 = "invalid distance code";
          v84 = 26;
          goto LABEL_101;
        }
        a1 = _m_psrlq(a1, a2);
      }
      v72 = k & 0xF;
      if ( v72 != 0 )
      {
        a1 = _m_psrlq(a1, a2);
        a2 = _mm_cvtsi32_si64(v72);
        v11 -= v72;
        v12 += dword_654854[v72] & _mm_cvtsi64_si32(a1);
      }
      else if ( v12 == 1 && v101 != v17 )
      {
        v77 = v17 - 1;
        v78 = *v77;
        v77[1] = *v77;
        v77[2] = v78;
        v77[3] = v78;
        v77 += 4;
        memset(v77, v78, v66 - 3);
        v17 = &v77[v66 - 3];
        v12 = v95;
        goto LABEL_64;
      }
      v102 = v13;
      if ( v17 - v101 >= v12 )
      {
        v73 = v66 - 3;
        *v17 = v17[-v12];
        v74 = v17[-v12 + 2];
        v75 = &v17[-v12 + 3];
        v17[1] = v17[-v12 + 1];
        v17[2] = v74;
        v76 = v17 + 3;
        qmemcpy(v76, v75, v73);
        v17 = &v76[v73];
        v13 = v102;
        v12 = v95;
        goto LABEL_64;
      }
      if ( v104 < v12 )
      {
LABEL_100:
        v13 = v102;
        v83 = "invalid distance too far back";
        v84 = 26;
        goto LABEL_101;
      }
      v79 = v12 + v101 - v17;
      if ( v103 != 0 )
      {
        if ( v79 > v103 )
        {
          v80 = &v105[v104 + v103 - v79];
          v81 = v79 - v103;
          if ( v66 > v81 )
          {
            v66 -= v81;
            qmemcpy(v17, v80, v81);
            v17 += v81;
            v80 = v105;
            v82 = v103;
            if ( v66 > v103 )
            {
              v66 -= v103;
              qmemcpy(v17, v105, v103);
              v17 += v82;
              v80 = &v17[-v12];
            }
          }
          goto LABEL_95;
        }
        v80 = &v105[v103 - v79];
        if ( v66 > v79 )
          goto LABEL_94;
      }
      else
      {
        v80 = &v105[v104 - v79];
        if ( v66 > v79 )
        {
LABEL_94:
          v66 -= v79;
          qmemcpy(v17, v80, v79);
          v17 += v79;
          v80 = &v17[-v12];
        }
      }
LABEL_95:
      qmemcpy(v17, v80, v66);
      v17 += v66;
      v13 = v102;
      v12 = v95;
      goto LABEL_64;
    }
    if ( (i & 0x40) != 0 )
      break;
    a1 = _m_psrlq(a1, a2);
  }
LABEL_97:
  if ( (i & 0x20) != 0 )
  {
    v83 = nullptr;
    v84 = 11;
  }
  else
  {
    v83 = "invalid literal/length code";
    v84 = 26;
  }
LABEL_101:
  if ( v83 != nullptr )
    a3[6] = (int)v83;
  *(uint32_t *)a3[7] = v84;
LABEL_104:
  if ( dword_7960F0 == 2 )
    v12 = v11;
  result = a3;
  v86 = a3[7];
  v87 = (int)&v13[-(v12 >> 3)];
  v88 = v12 - 8 * (v12 >> 3);
  a3[3] = (int)v17;
  *(uint32_t *)(v86 + 60) = v88;
  if ( v98 == v100 )
  {
    v87 = *a3 + v87 - (uint32_t)v100;
    v98 = (uint8_t *)(a3[1] - 11 + *a3);
  }
  *a3 = v87;
  if ( dword_7960F0 == 2 )
  {
    v11 = _mm_cvtsi64_si32(_m_psrlq(a1, a2));
    _m_empty();
  }
  *(uint32_t *)(v86 + 56) = ((1 << v88) - 1) & v11;
  a3[1] = (int)&v98[-v87 + 11];
  a3[4] = v97 - (uint32_t)v17 + 257;
  __writeeflags(v107);
  return result;
}


// ------------------------------------------------------------
// 0x654F70 sub_654F70
// ------------------------------------------------------------
int /*cdecl*/ sub_654F70(int a1, int a2, unsigned int a3, uint32_t **a4, unsigned int *a5, char *a6)
{
  unsigned int v6; // eax
  unsigned int v7; // ebx
  uint32_t *v8; // edx
  unsigned int v10; // esi
  int v11; // edx
  unsigned int i; // eax
  unsigned int j; // eax
  int16_t v14; // dx
  int16_t v15; // cx
  unsigned int k; // eax
  char *v17; // eax
  unsigned int v18; // ebp
  unsigned int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  uint32_t *v23; // ecx
  unsigned int v24; // edx
  unsigned int m; // eax
  uint16_t *v26; // esi
  int v27; // esi
  char v28; // cl
  unsigned int v29; // edx
  int v30; // eax
  uint16_t *v31; // esi
  int v32; // eax
  unsigned int v33; // edx
  uint32_t *v34; // esi
  unsigned int n; // eax
  int v36; // [esp+Ch] [ebp-7Ch]
  int v37; // [esp+Ch] [ebp-7Ch]
  unsigned int v38; // [esp+10h] [ebp-78h]
  unsigned int v39; // [esp+14h] [ebp-74h]
  unsigned int v40; // [esp+18h] [ebp-70h]
  uint32_t *v41; // [esp+1Ch] [ebp-6Ch]
  char *v42; // [esp+20h] [ebp-68h]
  int v43; // [esp+24h] [ebp-64h]
  int v44; // [esp+28h] [ebp-60h]
  uint8_t *v45; // [esp+2Ch] [ebp-5Ch]
  char *v46; // [esp+30h] [ebp-58h]
  int v47; // [esp+34h] [ebp-54h]
  int v48; // [esp+38h] [ebp-50h]
  int v49; // [esp+3Ch] [ebp-4Ch]
  int v50; // [esp+48h] [ebp-40h] BYREF
  int v51; // [esp+4Ch] [ebp-3Ch]
  uint16_t v52[13]; // [esp+50h] [ebp-38h] BYREF
  uint16_t v53[15]; // [esp+6Ah] [ebp-1Eh]

  v6 = 0;
  v50 = 0;
  v51 = 0;
  memset(v52, 0, 24);
  if ( a3 != 0 )
  {
    do
      ++*((uint16_t *)&v50 + *(uint16_t *)(a2 + 2 * v6++));
    while ( v6 < a3 );
  }
  v7 = 15;
  v38 = *a5;
  do
  {
    if ( *((uint16_t *)&v50 + v7) != 0 )
      break;
    --v7;
  }
  while ( v7 != 0 );
  v40 = v7;
  if ( *a5 > v7 )
    v38 = v7;
  if ( v7 == 0 )
  {
    **a4 = 320;
    v8 = *a4 + 1;
    *a4 = v8;
    *v8 = 320;
    ++*a4;
    *a5 = 1;
    return 0;
  }
  v10 = 1;
  while ( *((uint16_t *)&v50 + v10) == 0 )
  {
    if ( *((uint16_t *)&v50 + v10 + 1) != 0 )
    {
      ++v10;
      break;
    }
    if ( v52[v10 - 2] != 0 )
    {
      v10 += 2;
      break;
    }
    if ( v52[v10 - 1] != 0 )
    {
      v10 += 3;
      break;
    }
    if ( v52[v10] != 0 )
    {
      v10 += 4;
      break;
    }
    v10 += 5;
    if ( v10 > 0xF )
      break;
  }
  if ( v38 < v10 )
    v38 = v10;
  v11 = 1;
  for ( i = 1; i <= 0xF; ++i )
  {
    v11 = 2 * v11 - *((uint16_t *)&v50 + i);
    if ( v11 < 0 )
      return -1;
  }
  if ( v11 > 0 && (a1 == 0 || v7 != 1) )
    return -1;
  v53[0] = 0;
  for ( j = 1; j < 15; j += 2 )
  {
    v14 = *(uint16_t *)((char *)&v50 + j * 2) + v52[j + 12];
    v15 = v14 + *(uint16_t *)((char *)&v50 + j * 2 + 2);
    v53[j] = v14;
    v53[j + 1] = v15;
  }
  for ( k = 0; k < a3; ++k )
  {
    if ( *(uint16_t *)(a2 + 2 * k) != 0 )
      *(uint16_t *)&a6[2 * (uint16_t)v52[*(uint16_t *)(a2 + 2 * k) + 12]++] = k;
  }
  if ( a1 != 0 )
  {
    if ( a1 != 1 )
    {
      v46 = (char *)&unk_73FE40;
      v45 = &unk_73FE80;
      v44 = -1;
      goto LABEL_44;
    }
    v46 = (char *)&unk_73FDC0 - 514;
    v17 = (char *)&unk_73FE00 - 514;
    v44 = 256;
  }
  else
  {
    v17 = a6;
    v46 = a6;
    v44 = 19;
  }
  v45 = v17;
LABEL_44:
  v41 = *a4;
  v47 = -1;
  v18 = 0;
  v19 = 0;
  v39 = v10;
  v48 = 1 << v38;
  v43 = 1 << v38;
  v49 = (1 << v38) - 1;
  if ( a1 == 1 && (unsigned int)(1 << v38) >= 0x5B0 )
    return 1;
  v42 = a6;
  while ( 1 )
  {
    if ( *(uint16_t *)v42 >= v44 )
    {
      if ( *(uint16_t *)v42 <= v44 )
      {
        LOBYTE(v36) = 96;
        HIWORD(v36) = 0;
      }
      else
      {
        v20 = 2 * *(uint16_t *)v42;
        LOBYTE(v36) = v45[v20];
        HIWORD(v36) = *(uint16_t *)&v46[v20];
      }
    }
    else
    {
      LOBYTE(v36) = 0;
      HIWORD(v36) = *(uint16_t *)v42;
    }
    v21 = v48;
    v22 = 1 << (v39 - v19);
    v23 = &v41[v48 + (v18 >> v19)];
    do
    {
      v21 -= v22;
      v23 -= v22;
      BYTE1(v36) = v39 - v19;
      *v23 = v36;
    }
    while ( v21 != 0 );
    v24 = v39;
    for ( m = 1 << (v39 - 1); (m & v18) != 0; m >>= 1 )
      ;
    if ( m != 0 )
      v18 = m + (v18 & (m - 1));
    else
      v18 = 0;
    v26 = (uint16_t *)(v42 + 2);
    --*((uint16_t *)&v50 + v39);
    v42 += 2;
    if ( *((uint16_t *)&v50 + v39) == 0 )
    {
      if ( v39 == v40 )
        break;
      v24 = *(uint16_t *)(a2 + 2 * *v26);
      v39 = v24;
    }
    if ( v24 > v38 )
    {
      v27 = v18 & v49;
      if ( (v18 & v49) != v47 )
      {
        if ( v19 == 0 )
          v19 = v38;
        v28 = v39 - v19;
        v41 += v48;
        v29 = v39;
        v30 = 1 << (v39 - v19);
        if ( v39 < v40 )
        {
          v31 = (uint16_t *)&v50 + v39;
          do
          {
            v32 = v30 - *v31;
            if ( v32 <= 0 )
              break;
            ++v28;
            ++v29;
            ++v31;
            v30 = 2 * v32;
          }
          while ( v29 < v40 );
          v27 = v18 & v49;
        }
        v33 = (1 << v28) + v43;
        v48 = 1 << v28;
        v43 = v33;
        if ( a1 == 1 && v33 >= 0x5B0 )
          return 1;
        LOBYTE((*a4)[v27]) = v28;
        BYTE1((*a4)[v27]) = v38;
        v47 = v27;
        HIWORD((*a4)[v27]) = v41 - *a4;
      }
    }
  }
  LOBYTE(v37) = 64;
  BYTE1(v37) = v39 - v19;
  HIWORD(v37) = 0;
  if ( v18 != 0 )
  {
    v34 = v41;
    do
    {
      if ( v19 != 0 && (v18 & v49) != v47 )
      {
        v34 = *a4;
        v19 = 0;
        BYTE1(v37) = v38;
        LOBYTE(v24) = v38;
      }
      v34[v18 >> v19] = v37;
      for ( n = 1 << (v24 - 1); (n & v18) != 0; n >>= 1 )
        ;
      if ( n == 0 )
        break;
      v18 = n + (v18 & (n - 1));
    }
    while ( v18 != 0 );
  }
  *a4 += v43;
  *a5 = v38;
  return 0;
}


// ------------------------------------------------------------
// 0x655460 sub_655460
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_655460(unsigned int a1, uint8_t *a2, unsigned int a3)
{
  unsigned int v3; // ebx
  unsigned int v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // ecx
  unsigned int v7; // edi
  uint8_t *v9; // esi
  unsigned int v10; // ebp
  int i; // eax
  unsigned int v12; // ecx
  unsigned int v13; // edi
  unsigned int v14; // ecx
  unsigned int v15; // edi
  unsigned int v16; // ecx
  unsigned int v17; // edi
  unsigned int v18; // ecx
  unsigned int v19; // edi
  unsigned int v20; // ecx
  unsigned int v21; // edi
  unsigned int v22; // ecx
  unsigned int v23; // edi
  unsigned int v24; // ecx
  int v25; // edi
  unsigned int v26; // ecx
  int v27; // edi
  unsigned int v28; // ecx
  int v29; // edi
  int v30; // ecx
  int v31; // edi
  int v32; // ecx
  int v33; // edi
  int v34; // ecx
  int v35; // edi
  int v36; // ecx
  int v37; // edi
  int v38; // ecx
  int v39; // edi
  int v40; // ecx
  int v41; // edi
  unsigned int v42; // eax
  unsigned int v43; // ecx
  unsigned int v44; // edi
  unsigned int v45; // ecx
  unsigned int v46; // edi
  unsigned int v47; // ecx
  unsigned int v48; // edi
  unsigned int v49; // ecx
  unsigned int v50; // edi
  unsigned int v51; // ecx
  unsigned int v52; // edi
  unsigned int v53; // ecx
  unsigned int v54; // edi
  unsigned int v55; // ecx
  int v56; // edi
  unsigned int v57; // ecx
  int v58; // edi
  unsigned int v59; // ecx
  int v60; // edi
  int v61; // ecx
  int v62; // edi
  int v63; // ecx
  int v64; // edi
  int v65; // ecx
  int v66; // edi
  int v67; // ecx
  int v68; // edi
  int v69; // ecx
  int v70; // edi
  int v71; // ecx
  int v72; // edi

  v3 = a3;
  v4 = HIWORD(a1);
  v5 = (uint16_t)a1;
  if ( a3 == 1 )
  {
    v6 = *a2 + (uint16_t)a1;
    if ( v6 >= 0xFFF1 )
      v6 -= 65521;
    v7 = v6 + v4;
    if ( v7 >= 0xFFF1 )
      v7 -= 65521;
    return v6 | (v7 << 16);
  }
  else
  {
    v9 = a2;
    if ( a2 != nullptr )
    {
      if ( a3 >= 0x10 )
      {
        if ( a3 >= 0x15B0 )
        {
          v10 = a3 / 0x15B0;
          do
          {
            v3 -= 5552;
            for ( i = 347; i != 0; --i )
            {
              v12 = *v9 + v5;
              v13 = v12 + v4;
              v14 = v9[1] + v12;
              v15 = v14 + v13;
              v16 = v9[2] + v14;
              v17 = v16 + v15;
              v18 = v9[3] + v16;
              v19 = v18 + v17;
              v20 = v9[4] + v18;
              v21 = v20 + v19;
              v22 = v9[5] + v20;
              v23 = v22 + v21;
              v24 = v9[6] + v22;
              v25 = v24 + v23;
              v26 = v9[7] + v24;
              v27 = v26 + v25;
              v28 = v9[8] + v26;
              v29 = v28 + v27;
              v30 = v9[9] + v28;
              v31 = v30 + v29;
              v32 = v9[10] + v30;
              v33 = v32 + v31;
              v34 = v9[11] + v32;
              v35 = v34 + v33;
              v36 = v9[12] + v34;
              v37 = v36 + v35;
              v38 = v9[13] + v36;
              v39 = v38 + v37;
              v40 = v9[14] + v38;
              v41 = v40 + v39;
              v5 = v9[15] + v40;
              v4 = v5 + v41;
              v9 += 16;
            }
            v5 %= 0xFFF1u;
            --v10;
            v4 %= 0xFFF1u;
          }
          while ( v10 != 0 );
        }
        if ( v3 != 0 )
        {
          if ( v3 >= 0x10 )
          {
            v42 = v3 >> 4;
            do
            {
              v43 = *v9 + v5;
              v44 = v43 + v4;
              v45 = v9[1] + v43;
              v46 = v45 + v44;
              v47 = v9[2] + v45;
              v48 = v47 + v46;
              v49 = v9[3] + v47;
              v50 = v49 + v48;
              v51 = v9[4] + v49;
              v52 = v51 + v50;
              v53 = v9[5] + v51;
              v54 = v53 + v52;
              v55 = v9[6] + v53;
              v56 = v55 + v54;
              v57 = v9[7] + v55;
              v58 = v57 + v56;
              v59 = v9[8] + v57;
              v60 = v59 + v58;
              v61 = v9[9] + v59;
              v62 = v61 + v60;
              v63 = v9[10] + v61;
              v64 = v63 + v62;
              v65 = v9[11] + v63;
              v66 = v65 + v64;
              v67 = v9[12] + v65;
              v68 = v67 + v66;
              v69 = v9[13] + v67;
              v70 = v69 + v68;
              v71 = v9[14] + v69;
              v72 = v71 + v70;
              v5 = v9[15] + v71;
              v3 -= 16;
              v4 = v5 + v72;
              v9 += 16;
              --v42;
            }
            while ( v42 != 0 );
          }
          for ( ; v3 != 0; --v3 )
          {
            v5 += *v9++;
            v4 += v5;
          }
          v5 %= 0xFFF1u;
          v4 %= 0xFFF1u;
        }
        return v5 | (v4 << 16);
      }
      else
      {
        if ( a3 != 0 )
        {
          do
          {
            v5 += *v9++;
            v4 += v5;
            --v3;
          }
          while ( v3 != 0 );
        }
        if ( v5 >= 0xFFF1 )
          v5 -= 65521;
        return v5 | ((v4 % 0xFFF1) << 16);
      }
    }
    else
    {
      return 1;
    }
  }
}


// ------------------------------------------------------------
// 0x6556B0 sub_6556B0
// ------------------------------------------------------------
int /*usercall*/ sub_6556B0@<eax>(int a1@<eax>, unsigned int a2@<edx>, uint32_t *a3@<ecx>)
{
  unsigned int v3; // esi
  unsigned int i; // eax
  unsigned int v5; // edi
  unsigned int v6; // eax
  unsigned int v7; // edx
  uint32_t *v8; // ecx
  unsigned int v9; // eax
  unsigned int v10; // edx
  unsigned int v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // eax
  unsigned int v14; // edx
  unsigned int v16; // [esp+8h] [ebp-4h]
  unsigned int v17; // [esp+8h] [ebp-4h]

  v3 = a2;
  for ( i = ~a1; v3 != 0; --v3 )
  {
    if ( ((uint8_t)a3 & 3) == 0 )
      break;
    i = dword_73FEC0[(uint8_t)(i ^ *(uint8_t *)a3)] ^ (i >> 8);
    a3 = (uint32_t *)((char *)a3 + 1);
  }
  if ( v3 >= 0x20 )
  {
    v5 = v3 >> 5;
    do
    {
      v6 = *a3 ^ i;
      v7 = a3[1]
         ^ dword_740AC0[(uint8_t)v6]
         ^ dword_73FEC0[HIBYTE(v6)]
         ^ dword_7406C0[BYTE1(v6)]
         ^ dword_7402C0[BYTE2(v6)];
      v8 = a3 + 1;
      v9 = v8[1]
         ^ dword_740AC0[(uint8_t)v7]
         ^ dword_73FEC0[HIBYTE(v7)]
         ^ dword_7406C0[BYTE1(v7)]
         ^ dword_7402C0[BYTE2(v7)];
      ++v8;
      v10 = v8[1]
          ^ dword_740AC0[(uint8_t)v9]
          ^ dword_73FEC0[HIBYTE(v9)]
          ^ dword_7406C0[BYTE1(v9)]
          ^ dword_7402C0[BYTE2(v9)];
      ++v8;
      v11 = v8[1]
          ^ dword_740AC0[(uint8_t)v10]
          ^ dword_73FEC0[HIBYTE(v10)]
          ^ dword_7406C0[BYTE1(v10)]
          ^ dword_7402C0[BYTE2(v10)];
      v8 += 2;
      v12 = *v8
          ^ dword_740AC0[(uint8_t)v11]
          ^ dword_73FEC0[HIBYTE(v11)]
          ^ dword_7406C0[BYTE1(v11)]
          ^ dword_7402C0[BYTE2(v11)];
      v13 = v8[1]
          ^ dword_740AC0[(uint8_t)v12]
          ^ dword_73FEC0[HIBYTE(v12)]
          ^ dword_7406C0[BYTE1(v12)]
          ^ dword_7402C0[BYTE2(v12)];
      ++v8;
      v16 = v8[1]
          ^ dword_740AC0[(uint8_t)v13]
          ^ dword_73FEC0[HIBYTE(v13)]
          ^ dword_7406C0[BYTE1(v13)]
          ^ dword_7402C0[BYTE2(v13)];
      a3 = v8 + 2;
      i = dword_740AC0[(uint8_t)v16]
        ^ dword_73FEC0[HIBYTE(v16)]
        ^ dword_7406C0[BYTE1(v16)]
        ^ dword_7402C0[BYTE2(v16)];
      v3 -= 32;
      --v5;
    }
    while ( v5 != 0 );
  }
  if ( v3 >= 4 )
  {
    v14 = v3 >> 2;
    do
    {
      v17 = *a3++ ^ i;
      v3 -= 4;
      --v14;
      i = dword_740AC0[(uint8_t)v17]
        ^ dword_73FEC0[HIBYTE(v17)]
        ^ dword_7406C0[BYTE1(v17)]
        ^ dword_7402C0[BYTE2(v17)];
    }
    while ( v14 != 0 );
  }
  for ( ; v3 != 0; --v3 )
  {
    i = dword_73FEC0[(uint8_t)(i ^ *(uint8_t *)a3)] ^ (i >> 8);
    a3 = (uint32_t *)((char *)a3 + 1);
  }
  return ~i;
}



// ------------------------------------------------------------
// 0x655990 sub_655990
// ------------------------------------------------------------
int /*cdecl*/ sub_655990(int a1, uint32_t *a2, unsigned int a3)
{
  if ( a2 != nullptr )
    return sub_6556B0(a1, a3, a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x6559B0 sub_6559B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559B0(uint32_t **this, int a2, int a3)
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 4) + 4))(*(this + 4), a2);
}



// ------------------------------------------------------------
// 0x6559D0 sub_6559D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559D0(uint32_t **this, int a2, int a3)
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 4) + 12))(*(this + 4), a2);
}



// ------------------------------------------------------------
// 0x6559F0 sub_6559F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6559F0(int this, int a2, int a3)
{
  return (***(int (/*thiscall*/ ****)(uint32_t, uint32_t))(this + 16))(*(uint32_t *)(this + 16), *(uint32_t *)(this + 12));
}



// ------------------------------------------------------------
// 0x655A00 sub_655A00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_655A00(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = a1; result != a2; v4[4] = a3[4] )
  {
    v4 = result;
    *result = *a3;
    result[1] = a3[1];
    result[2] = a3[2];
    result[3] = a3[3];
    result += 5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x655A40 sub_655A40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_655A40(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ecx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
      {
        *result = *a3;
        result[1] = a3[1];
        result[2] = a3[2];
        result[3] = a3[3];
        result[4] = a3[4];
      }
      result += 5;
      v4 = (uint32_t *)((char *)v4 - 1);
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x655A90 sub_655A90
// ------------------------------------------------------------
void /*thiscall*/ sub_655A90(int this, float a2)
{
  double v3; // st7
  int v4; // eax
  int v5; // eax
  int v6; // edi
  unsigned int v7; // ebx
  int v8; // edi
  int v9; // eax
  float *v10; // eax
  double v11; // st7
  int v12; // ecx
  int v13; // ecx
  double v14; // st7
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  double v18; // st7
  int v19; // edx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  char v25; // [esp+18h] [ebp-14h]
  float v26; // [esp+28h] [ebp-4h]

  v3 = a2 + *(float *)(this + 28);
  v4 = *(uint32_t *)(this + 40);
  v26 = 0.0;
  *(float *)(this + 28) = v3;
  *(uint32_t *)(this + 32) = -1;
  if ( v4 < 2 )
    goto LABEL_2;
  if ( v3 > *(float *)(this + 24) )
  {
    v5 = *(uint32_t *)(this + 4) - 1;
    *(uint32_t *)(this + 28) = 0;
    if ( v5 != 0 )
    {
      if ( v5 == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 16) + 8))(
          *(uint32_t *)(this + 16),
          *(uint32_t *)(this + 12));
        if ( *(uint8_t *)(this + 21) != 0 )
        {
          v6 = *(uint32_t *)(this + 12) + 1;
          v25 = *(uint8_t *)(this + 12) + 1;
          *(uint8_t *)(this + 21) = 0;
          *(uint32_t *)(this + 12) = v6;
          sub_40BE20("-------------%d---------------\n", v25);
          *(uint32_t *)(this + 4) = 1;
        }
      }
    }
    else
    {
      (***(void (/*thiscall*/ ****)(uint32_t, uint32_t))(this + 16))(*(uint32_t *)(this + 16), *(uint32_t *)(this + 12));
    }
  }
  v7 = 0;
  v8 = 0;
  while ( 1 )
  {
    v9 = *(uint32_t *)(this + 48);
    if ( v9 == 0 || v7 >= (*(uint32_t *)(this + 52) - v9) / 20 )
      break;
    sub_40BE20("%d enduranceTime_=>%f waitTime_=>%f elapsedTime=>%f\n", v7);
    v10 = (float *)(v8 + *(uint32_t *)(this + 48));
    if ( *(uint32_t *)v10 == 3 )
      goto LABEL_32;
    if ( *(uint32_t *)(this + 4) == 1 )
    {
      v18 = a2;
      if ( *(uint32_t *)v10 == 1 )
      {
        v10[2] = 0.0;
        *(float *)(v8 + *(uint32_t *)(this + 48) + 12) = v18 + *(float *)(*(uint32_t *)(this + 48) + v8 + 12);
        v19 = *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 3.0 >= *(float *)(v8 + v19 + 12) )
          goto LABEL_32;
        *(float *)(v8 + v19 + 4) = *(float *)(this + 24) + *(float *)(v8 + v19 + 4);
        v20 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(v20 + 4) > 60.0 )
          *(uint32_t *)(v20 + 4) = 1114636288;
        ++v7;
        *(uint32_t *)(v8 + *(uint32_t *)(this + 48) + 12) = 0;
        v8 += 20;
      }
      else
      {
        v10[2] = v18 + v10[2];
        v21 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 3.0 < *(float *)(v21 + 8) )
        {
          *(float *)(v21 + 4) = *(float *)(v21 + 4) - a2;
          v22 = v8 + *(uint32_t *)(this + 48);
          if ( v26 < (double)*(float *)(v22 + 8) )
          {
            *(uint32_t *)(this + 32) = v7;
            v26 = *(float *)(v22 + 8);
          }
        }
LABEL_32:
        ++v7;
        v8 += 20;
      }
    }
    else
    {
      if ( *(uint32_t *)(this + 4) != 2 )
        goto LABEL_32;
      v11 = a2;
      if ( *(uint32_t *)v10 == 2 )
      {
        v10[2] = 0.0;
        *(float *)(v8 + *(uint32_t *)(this + 48) + 12) = v11 + *(float *)(*(uint32_t *)(this + 48) + v8 + 12);
        v12 = v8 + *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 6.0 >= *(float *)(v12 + 12) )
          goto LABEL_32;
        *(float *)(v12 + 4) = *(float *)(v12 + 4) + *(float *)(this + 24);
        v13 = *(uint32_t *)(this + 48);
        v14 = *(float *)(v13 + v8 + 4);
        v15 = v8 + v13;
        if ( v14 > 60.0 )
          *(uint32_t *)(v15 + 4) = 1114636288;
        ++v7;
        *(uint32_t *)(v8 + *(uint32_t *)(this + 48) + 12) = 0;
        v8 += 20;
      }
      else
      {
        v10[2] = v11 + v10[2];
        v16 = *(uint32_t *)(this + 48);
        if ( *(float *)(this + 24) * 6.0 >= *(float *)(v8 + v16 + 8) )
          goto LABEL_32;
        *(float *)(v8 + v16 + 4) = *(float *)(v8 + v16 + 4) - a2;
        v17 = v8 + *(uint32_t *)(this + 48);
        if ( v26 >= (double)*(float *)(v17 + 8) )
          goto LABEL_32;
        *(uint32_t *)(this + 32) = v7++;
        v26 = *(float *)(v17 + 8);
        v8 += 20;
      }
    }
  }
  v23 = *(uint32_t *)(this + 32);
  if ( v23 < 0 )
  {
LABEL_2:
    *(uint32_t *)(this + 8) = 3;
    return;
  }
  v24 = *(uint32_t *)(this + 48) + 20 * v23;
  if ( *(float *)(this + 24) * 3.0 >= *(float *)(v24 + 8) )
  {
    if ( *(float *)(this + 24) + *(float *)(this + 24) < *(float *)(v24 + 8) )
    {
      *(uint32_t *)(this + 8) = 1;
      return;
    }
    if ( *(float *)(v24 + 8) > (double)*(float *)(this + 24) )
    {
      *(uint32_t *)(this + 8) = 2;
      return;
    }
    goto LABEL_2;
  }
  *(uint32_t *)(this + 8) = 0;
  if ( *(uint8_t *)(v24 + 16) == 0 )
    *(uint8_t *)(v24 + 16) = 1;
}


// ------------------------------------------------------------
// 0x655DB0 sub_655DB0
// ------------------------------------------------------------
char /*thiscall*/ sub_655DB0(uint32_t *this)
{
  int v1; // edi
  unsigned int v2; // esi
  int v3; // ebx
  int v4; // edx

  v1 = *(this + 12);
  v2 = 0;
  v3 = 0;
  while ( v1 != 0 && v2 < (*(this + 13) - v1) / 20 )
  {
    v4 = *(uint32_t *)(*(this + 12) + v3);
    if ( v4 != 3 && v4 != 1 )
      return 0;
    ++v2;
    v3 += 20;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x655E10 sub_655E10
// ------------------------------------------------------------
char /*thiscall*/ sub_655E10(uint32_t *this)
{
  int v1; // edi
  unsigned int v2; // esi
  int v3; // ebx
  int v4; // edx

  v1 = *(this + 12);
  v2 = 0;
  v3 = 0;
  while ( v1 != 0 && v2 < (*(this + 13) - v1) / 20 )
  {
    v4 = *(uint32_t *)(*(this + 12) + v3);
    if ( v4 != 3 && v4 != 2 )
      return 0;
    ++v2;
    v3 += 20;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x655E70 sub_655E70
// ------------------------------------------------------------
double /*thiscall*/ sub_655E70(uint32_t *this, int a2)
{
  return *(float *)(*(this + 12) + 20 * a2 + 4);
}



// ------------------------------------------------------------
// 0x655E90 sub_655E90
// ------------------------------------------------------------
int /*thiscall*/ sub_655E90(uint32_t *this, int a2)
{
  int result; // eax

  result = *(this + 12) + 20 * a2;
  *(uint32_t *)(result + 4) = 1114636288;
  return result;
}



// ------------------------------------------------------------
// 0x655EB0 sub_655EB0
// ------------------------------------------------------------
void /*thiscall*/ sub_655EB0(uint32_t *this, int a2, float a3)
{
  int v3; // edx
  uint32_t *v4; // eax
  int v5; // esi

  v3 = 20 * a2;
  v4 = (uint32_t *)(20 * a2 + *(this + 12));
  if ( *v4 != 3 )
  {
    *v4 = 0;
    *(uint32_t *)(v3 + *(this + 12) + 8) = 0;
  }
  v5 = v3 + *(this + 12);
  if ( *(float *)(v5 + 8) < (double)a3 )
  {
    *(uint32_t *)(v5 + 4) = 1114636288;
    *(float *)(v3 + *(this + 12) + 8) = a3;
    *(uint32_t *)(v3 + *(this + 12) + 12) = 0;
    *(uint8_t *)(*(this + 12) + 20 * *(this + 8) + 16) = 1;
  }
}



// ------------------------------------------------------------
// 0x655F20 sub_655F20
// ------------------------------------------------------------
void /*thiscall*/ sub_655F20(uint32_t *this, int a2)
{
  uint32_t *v2; // eax
  int v3; // ecx
  unsigned int v4; // edi
  int i; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  uint32_t *v9; // eax

  if ( *(this + 1) == 2 )
  {
    v2 = (uint32_t *)(*(this + 12) + 20 * a2);
    if ( *v2 != 3 )
      *v2 = 2;
    if ( sub_655E10(this) != 0 )
    {
      v4 = 0;
      for ( i = 0; ; i += 20 )
      {
        v6 = *(uint32_t *)(v3 + 48);
        if ( v6 == 0 || v4 >= (*(uint32_t *)(v3 + 52) - v6) / 20 )
          break;
        v7 = *(uint32_t *)(v3 + 48);
        v8 = *(uint32_t *)(v7 + i);
        v9 = (uint32_t *)(i + v7);
        if ( v8 != 3 )
        {
          *v9 = 0;
          *(uint32_t *)(i + *(uint32_t *)(v3 + 48) + 8) = 0;
        }
        ++v4;
      }
      *(uint8_t *)(v3 + 21) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x655FA0 sub_655FA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_655FA0(int this)
{
  unsigned int v1; // edi
  int i; // esi
  unsigned int result; // eax
  int v4; // eax
  int v5; // edx
  uint32_t *v6; // eax

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(uint32_t *)(this + 48);
    if ( result == 0 )
      break;
    result = (int)(*(uint32_t *)(this + 52) - result) / 20;
    if ( v1 >= result )
      break;
    v4 = *(uint32_t *)(this + 48);
    v5 = *(uint32_t *)(v4 + i);
    v6 = (uint32_t *)(i + v4);
    if ( v5 != 3 )
    {
      *v6 = 0;
      *(uint32_t *)(i + *(uint32_t *)(this + 48) + 8) = 0;
    }
    *(uint32_t *)(i + *(uint32_t *)(this + 48) + 4) = 1114636288;
    *(uint32_t *)(i + *(uint32_t *)(this + 48) + 12) = 0;
    ++v1;
    *(uint8_t *)(i + *(uint32_t *)(this + 48) + 16) = 0;
  }
  *(uint32_t *)(this + 12) = 0;
  *(uint8_t *)(this + 20) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 8) = 3;
  *(uint32_t *)(this + 32) = -1;
  *(uint32_t *)(this + 36) = -1082130432;
  return result;
}



// ------------------------------------------------------------
// 0x656030 sub_656030
// ------------------------------------------------------------
void /*thiscall*/ sub_656030(uint32_t *this, int a2)
{
  uint32_t *v2; // edx
  int v3; // ecx

  if ( *(this + 1) == 1 )
  {
    v2 = (uint32_t *)(20 * a2 + *(this + 12));
    if ( *v2 != 3 )
    {
      *v2 = 1;
      *(uint32_t *)(20 * a2 + *(this + 12) + 8) = 0;
    }
    if ( sub_655DB0(this) != 0 )
      *(uint32_t *)(v3 + 4) = 2;
  }
}



// ------------------------------------------------------------
// 0x656080 sub_656080
// ------------------------------------------------------------
void /*thiscall*/ sub_656080(uint32_t *this, int a2)
{
  sub_655F20(this, a2);
}



// ------------------------------------------------------------
// 0x656090 sub_656090
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656090(void *this)
{
  unsigned int result; // eax
  int v2; // ecx

  result = sub_655FA0((int)this);
  *(uint32_t *)(v2 + 4) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x6560A0 sub_6560A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_6560A0(int this)
{
  unsigned int result; // eax

  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  result = sub_655FA0(this);
  *(uint32_t *)(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6560D0 sub_6560D0
// ------------------------------------------------------------
void /*noreturn*/ sub_6560D0()
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



// ------------------------------------------------------------
// 0x656140 sub_656140
// ------------------------------------------------------------
int /*thiscall*/ sub_656140(int *this, uint32_t *a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int result; // eax
  unsigned int v10; // ecx
  int v12; // eax
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  unsigned int v18; // edi
  void *v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-48h]
  int v23; // [esp-Ch] [ebp-3Ch]
  unsigned int v24; // [esp-8h] [ebp-38h]
  int v25; // [esp+0h] [ebp-30h] BYREF
  uint32_t v26[6]; // [esp+Ch] [ebp-24h] BYREF
  int v27; // [esp+2Ch] [ebp-4h]
  int v28; // [esp+38h] [ebp+8h]
  uint32_t *v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];
  v6 = *(this + 1);
  v26[0] = *Block;
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( v6 != 0 )
  {
    result = 1717986919 * (*(this + 3) - v6);
    v10 = (*(this + 3) - v6) / 20;
  }
  else
  {
    v10 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v12 = (*(this + 2) - v6) / 20;
    else
      v12 = 0;
    if ( 214748364 - v12 < a3 )
      sub_6560D0(this);
    if ( v6 != 0 )
      v13 = (*(this + 2) - v6) / 20;
    else
      v13 = 0;
    if ( v10 >= a3 + v13 )
    {
      v19 = (void *)*(this + 2);
      Blockb = v19;
      if ( ((uint8_t *)v19 - (uint8_t *)a2) / 20 >= a3 )
      {
        v28 = (int)v19 - 20 * a3;
        *(this + 2) = sub_4FBDE0(v28, v19, v19);
        sub_57A4A0(a2, v28, Blockb);
        return (int)sub_655A00(a2, &a2[5 * a3], v26);
      }
      else
      {
        sub_4FBDE0(a2, v19, &a2[5 * a3]);
        v24 = a3 - (*(this + 2) - (int)a2) / 20;
        v23 = *(this + 2);
        v27 = 2;
        sub_57A4C0(v23, v24, v26);
        v21 = 20 * a3 + *(this + 2);
        *(this + 2) = v21;
        return (int)sub_655A00(a2, (uint32_t *)(v21 - 20 * a3), v26);
      }
    }
    else
    {
      if ( 214748364 - (v10 >> 1) >= v10 )
        v14 = (v10 >> 1) + v10;
      else
        v14 = 0;
      if ( v6 != 0 )
        v15 = (*(this + 2) - v6) / 20;
      else
        v15 = 0;
      if ( v14 < a3 + v15 )
        v14 = a3 + sub_45E580(this);
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      v22 = *(this + 1);
      v27 = 0;
      v29 = (uint32_t *)sub_4FBDE0(v22, a2, Blocka);
      sub_655A40(v29, (uint32_t *)a3, v26);
      sub_4FBDE0(a2, *(this + 2), &v29[5 * a3]);
      v17 = *(this + 1);
      if ( v17 != 0 )
        v17 = (*(this + 2) - v17) / 20;
      v18 = v17 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v16];
      *(this + 2) = (int)&Blocka[20 * v18];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x656400 sub_656400
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656400(int *this, uint32_t *a2, uint32_t *a3, uint32_t *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 20 != 0 )
    v6 = ((int)a3 - v5) / 20;
  else
    v6 = 0;
  sub_656140(this, a3, 1u, Block);
  *a2 = *(this + 1) + 20 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x656470 sub_656470
// ------------------------------------------------------------
void */*thiscall*/ sub_656470(void *this, int a2)
{
  *(uint32_t *)this = &off_741F20;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 4) = a2;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 8) = -1;
  *((uint8_t *)this + 21) = 0;
  *((uint32_t *)this + 2) = 3;
  if ( *((uint32_t *)this + 12) != 0 )
    j__free(*((void **)this + 12));
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x6564D0 sub_6564D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6564D0(int *this, uint32_t *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  uint32_t *v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 20;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 20 )
    return sub_656400(this, &Block, (uint32_t *)*(this + 2), Block);
  v5 = (uint32_t *)*(this + 2);
  result = sub_655A40(v5, (uint32_t *)1, Block);
  *(this + 2) = (int)(v5 + 5);
  return result;
}



// ------------------------------------------------------------
// 0x656560 sub_656560
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656560(int *this, int a2)
{
  int v3; // eax
  int *v4; // esi
  uint32_t *v6; // eax
  unsigned int v7; // edi
  unsigned int result; // eax
  uint32_t Block[5]; // [esp+Ch] [ebp-14h] BYREF
  int v10; // [esp+28h] [ebp+8h]
  int i; // [esp+28h] [ebp+8h]

  v3 = *(this + 12);
  v4 = this + 11;
  if ( v3 != 0 )
    v3 = (*(this + 13) - v3) / 20;
  if ( v3 < a2 + 1 )
  {
    v10 = a2 + 1 - v3;
    do
    {
      sub_6564D0(v4, Block);
      --v10;
    }
    while ( v10 != 0 );
  }
  v6 = (uint32_t *)(*(this + 12) + 20 * a2);
  if ( *v6 != 3 )
    *v6 = 3;
  sub_655FA0((int)this);
  v7 = 0;
  *(this + 10) = 0;
  for ( i = 0; ; i += 20 )
  {
    result = v4[1];
    if ( result == 0 )
      break;
    result = (int)(v4[2] - result) / 20;
    if ( v7 >= result )
      break;
    if ( *(uint32_t *)(*(this + 12) + i) != 3 )
      ++*(this + 10);
    ++v7;
  }
  *(this + 9) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x656630 sub_656630
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_656630(int *this, int a2)
{
  int v3; // eax
  int *v4; // ebx
  unsigned int v6; // edi
  unsigned int result; // eax
  uint32_t Block[5]; // [esp+Ch] [ebp-14h] BYREF
  int v9; // [esp+28h] [ebp+8h]
  int i; // [esp+28h] [ebp+8h]

  v3 = *(this + 12);
  v4 = this + 11;
  if ( v3 != 0 )
    v3 = (*(this + 13) - v3) / 20;
  if ( v3 < a2 + 1 )
  {
    v9 = a2 + 1 - v3;
    do
    {
      sub_6564D0(v4, Block);
      --v9;
    }
    while ( v9 != 0 );
  }
  *(uint32_t *)(*(this + 12) + 20 * a2 + 4) = 1114636288;
  *(uint32_t *)(20 * a2 + *(this + 12) + 8) = 0;
  *(uint32_t *)(20 * a2 + *(this + 12) + 12) = 0;
  *(uint8_t *)(20 * a2 + *(this + 12) + 16) = 0;
  *(uint32_t *)(20 * a2 + *(this + 12)) = 0;
  *(uint32_t *)(20 * a2 + *(this + 12) + 8) = 0;
  *(this + 10) = 0;
  v6 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = v4[1];
    if ( result == 0 )
      break;
    result = (int)(v4[2] - result) / 20;
    if ( v6 >= result )
      break;
    if ( *(uint32_t *)(*(this + 12) + i) != 3 )
      ++*(this + 10);
    ++v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x656720 sub_656720
// ------------------------------------------------------------
char /*thiscall*/ sub_656720(uint32_t *this, const void *a2, int16_t a3)
{
  int v4; // ecx
  int v6; // ecx

  v4 = *(this + 512);
  if ( v4 + a3 > *(this + 515) )
    return 0;
  *(uint16_t *)((char *)this + v4) = a3;
  v6 = *(this + 512) + 2;
  *(this + 512) = v6;
  qmemcpy((char *)this + v6, a2, a3);
  *(this + 512) += a3;
  return 1;
}



// ------------------------------------------------------------
// 0x656790 sub_656790
// ------------------------------------------------------------
int /*thiscall*/ sub_656790(uint32_t *this, int a2)
{
  *(uint32_t *)(*(this + 8) + 1088) = a2;
  return 1;
}



// ------------------------------------------------------------
// 0x6567B0 sub_6567B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6567B0(int this, int a2)
{
  *(uint32_t *)(*(uint32_t *)(this + 32) + 1096) = a2;
  sub_658CB0(*(uint32_t *)(this + 32));
  sub_657970(*(LPVOID *)(this + 32));
  *(uint32_t *)(this + 44) = GetTickCount();
  return 1;
}



// ------------------------------------------------------------
// 0x6567F0 sub_6567F0
// ------------------------------------------------------------
int /*cdecl*/ sub_6567F0(int a1)
{
  dword_79693C = a1;
  return a1;
}



// ------------------------------------------------------------
// 0x656800 sub_656800
// ------------------------------------------------------------
int sub_656800()
{
  return dword_79693C;
}



// ------------------------------------------------------------
// 0x656810 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *a1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *a2,
        bool (/*cdecl*/ *a3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_658C80(a1, a2);
}



// ------------------------------------------------------------
// 0x656820 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z_0
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *a1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *a2,
        bool (/*cdecl*/ *a3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_6588B0(a1);
}



// ------------------------------------------------------------
// 0x656830 ?SweepUnstructured@ContextBase@details@Concurrency@@QAEXP6A_NPAV_UnrealizedChore@23@PAX@Z12@Z_1
// ------------------------------------------------------------
void /*userpurge*/ Concurrency::details::ContextBase::SweepUnstructured(
        bool (/*cdecl*/ *a1)(struct Concurrency::details::_UnrealizedChore *, void *),
        void *a2,
        bool (/*cdecl*/ *a3)(struct Concurrency::details::_UnrealizedChore *, void *))
{
  sub_6588C0(a1);
}



// ------------------------------------------------------------
// 0x656840 sub_656840
// ------------------------------------------------------------
int /*thiscall*/ sub_656840(uint32_t *this)
{
  return *(uint32_t *)(*(this + 8) + 1096);
}



// ------------------------------------------------------------
// 0x656850 sub_656850
// ------------------------------------------------------------
int /*thiscall*/ sub_656850(uint32_t *this, int a2)
{
  int64_t v2; // rax

  LODWORD(v2) = *(this + a2);
  if ( (uint32_t)v2 != -1 )
    return (uint64_t)sub_658770(v2, 1116471296);
  return v2;
}



// ------------------------------------------------------------
// 0x656880 sub_656880
// ------------------------------------------------------------
void /*thiscall*/ sub_656880(uint32_t *this, int a2, void *Src, int16_t a4, int a5, char a6)
{
  int v7; // eax
  int *v8; // ecx

  if ( *(uint32_t *)(*(this + 8) + 1096) != a2 )
  {
    v7 = sub_659510(Src, a4, a2, a5, a6);
    v8 = this + a2;
    *v8 = 0;
    *v8 = v7;
  }
}



// ------------------------------------------------------------
// 0x6568C0 sub_6568C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6568C0(char *this, int a2)
{
  char *v2; // esi
  int result; // eax

  v2 = this + 4 * a2;
  result = *(uint32_t *)v2;
  if ( *(uint32_t *)v2 != -1 )
  {
    result = sub_659600(*(uint32_t *)v2);
    *(uint32_t *)v2 = 0;
    *(uint32_t *)v2 = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6568F0 sub_6568F0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_6568F0(
        int a1,
        uint32_t *a2,
        uint32_t *a3,
        uint32_t *a4,
        int a5,
        int a6,
        int a7,
        uint32_t *a8,
        uint32_t *a9)
{
  *a4 = 0;
  *a3 = 0;
  *a2 = 0;
  sub_658C10(a1, a2, a3, a4, a5, a6, a7);
  *a8 = dword_796900;
  *a9 = dword_9B9D58[516 * a1];
  return a9;
}



// ------------------------------------------------------------
// 0x656950 sub_656950
// ------------------------------------------------------------
int /*stdcall*/ sub_656950(int a1, int a2)
{
  dword_9B9D5C[516 * a1] = a2;
  return 2064 * a1;
}



// ------------------------------------------------------------
// 0x656970 sub_656970
// ------------------------------------------------------------
int /*thiscall*/ sub_656970(uint32_t *this)
{
  int16_t *v2; // esi
  uint32_t *v3; // edi
  int result; // eax

  v2 = &word_9B9D50;
  v3 = this;
  do
  {
    if ( *(uint32_t *)v2 != 0 )
    {
      result = sub_657FD0(v2 - 1024, (void *)(uint16_t)*v2, *v3, *(uint8_t *)(*(this + 8) + 1096), 0);
      *((uint32_t *)v2 + 1) = 0;
      *(uint32_t *)v2 = 0;
    }
    v2 += 1032;
    ++v3;
  }
  while ( (int)v2 < (int)word_9BDDD0 );
  return result;
}



// ------------------------------------------------------------
// 0x6569D0 sub_6569D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6569D0(uint32_t *this)
{
  uint32_t **v2; // ecx
  uint32_t *result; // eax
  bool v4; // zf
  uint32_t *v5; // edi

  v2 = (uint32_t **)*(this + 1);
  result = *v2;
  *v2 = v2;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  v4 = result == (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  if ( !v4 )
  {
    do
    {
      v5 = (uint32_t *)*result;
      j__free(result);
      result = v5;
    }
    while ( v5 != (uint32_t *)*(this + 1) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x656A10 sub_656A10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656A10(uint32_t *this)
{
  uint32_t *v2; // edi
  int16_t *v3; // esi
  uint32_t **v4; // ecx
  uint32_t *result; // eax
  bool v6; // zf
  uint32_t *v7; // esi

  v2 = this;
  v3 = &word_9B9D50;
  do
  {
    if ( *v2 != -1 )
    {
      sub_659600(*v2);
      *v2 = 0;
      *v2 = -1;
    }
    *((uint32_t *)v3 + 1) = 0;
    *(uint32_t *)v3 = 0;
    v3 += 1032;
    ++v2;
  }
  while ( (int)v3 < (int)word_9BDDD0 );
  sub_658900(*(this + 8));
  v4 = (uint32_t **)*(this + 13);
  result = *v4;
  *v4 = v4;
  *(uint32_t *)(*(this + 13) + 4) = *(this + 13);
  v6 = result == (uint32_t *)*(this + 13);
  *(this + 14) = 0;
  if ( !v6 )
  {
    do
    {
      v7 = (uint32_t *)*result;
      j__free(result);
      result = v7;
    }
    while ( v7 != (uint32_t *)*(this + 13) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x656AA0 sub_656AA0
// ------------------------------------------------------------
char /*thiscall*/ sub_656AA0(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t **v5; // ecx
  uint32_t *v6; // eax
  bool v7; // zf
  uint32_t *v8; // esi
  uint16_t k; // ax
  uint16_t j; // ax
  int v11; // edx
  int v12; // eax
  int16_t v13; // cx
  int v14; // eax
  uint32_t *i; // [esp+Ch] [ebp-810h]
  uint8_t v17[6]; // [esp+10h] [ebp-80Ch] BYREF
  char v18; // [esp+16h] [ebp-806h] BYREF
  uint8_t v19; // [esp+17h] [ebp-805h] BYREF
  uint8_t v20[2048]; // [esp+18h] [ebp-804h] BYREF
  int v21; // [esp+818h] [ebp-4h]

  v21 = dword_796E50;
  v2 = *(uint32_t **)(this + 52);
  v3 = (uint32_t *)*v2;
  for ( i = v2; v3 != i; v3 = (uint32_t *)*v3 )
  {
    v4 = v3[2];
    v18 = *(uint8_t *)(v4 + 2069);
    v19 = *(uint8_t *)(v4 + 2068);
    (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, int, uint32_t))(this + 36))(
      *(uint32_t *)(this + 36),
      v19,
      v4 + 4,
      *(uint16_t *)(v4 + 2052));
    (**(void (/*thiscall*/ ***)(int, int))v4)(v4, 1);
  }
  v5 = *(uint32_t ***)(this + 52);
  v6 = *v5;
  *v5 = v5;
  *(uint32_t *)(*(uint32_t *)(this + 52) + 4) = *(uint32_t *)(this + 52);
  v7 = v6 == *(uint32_t **)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  if ( !v7 )
  {
    do
    {
      v8 = (uint32_t *)*v6;
      j__free(v6);
      v6 = v8;
    }
    while ( v8 != *(uint32_t **)(this + 52) );
  }
  LOBYTE(k) = *(uint8_t *)(*(uint32_t *)(this + 32) + 1120);
  if ( (uint8_t)k != 0 )
  {
    sub_6585C0();
    sub_658850(*(uint32_t *)(this + 32));
    if ( GetTickCount() - *(uint32_t *)(this + 44) > 0x3C )
    {
      sub_656970((uint32_t *)this);
      *(uint32_t *)(this + 44) = GetTickCount();
    }
    for ( j = sub_657A90(v20, 2048, v17, &v19, &v18); j != 0; j = sub_657A90(v20, 2048, v17, &v19, &v18) )
      (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, uint8_t *, uint32_t))(this + 36))(*(uint32_t *)(this + 36), v19, v20, j);
    for ( k = sub_657B80(v20, 2048, v17, &v19, &v18); k != 0; k = sub_657B80(v20, 2048, v17, &v19, &v18) )
    {
      v11 = k;
      if ( k <= dword_796904 )
      {
        qmemcpy(&word_7960F8, v20, k);
        v12 = 0;
        dword_7968FC = 0;
        dword_7968F8 = v11;
      }
      else
      {
        v12 = dword_7968FC;
        dword_796900 = 1;
      }
      while ( v12 < dword_7968F8 )
      {
        v13 = *(int16_t *)((char *)&word_7960F8 + v12);
        v14 = v12 + 2;
        dword_7968FC = v13 + v14;
        if ( v13 == 0 )
          break;
        (***(void (/*thiscall*/ ****)(uint32_t, uint32_t, char *, uint32_t))(this + 36))(
          *(uint32_t *)(this + 36),
          v19,
          (char *)&word_7960F8 + v14,
          v13);
        v12 = dword_7968FC;
      }
    }
  }
  return k;
}



// ------------------------------------------------------------
// 0x656D00 sub_656D00
// ------------------------------------------------------------
void /*thiscall*/ sub_656D00(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // esi

  sub_656A10(this);
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 8);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = this + 12;
  sub_6569D0(v3);
  j__free((void *)v3[1]);
  v3[1] = 0;
}



// ------------------------------------------------------------
// 0x656D70 sub_656D70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_656D70(uint32_t *this)
{
  uint32_t *v2; // edi
  void *v3; // eax
  int v4; // eax

  v2 = this + 12;
  *(this + 13) = sub_425940(this + 12);
  v2[2] = 0;
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = -1;
  *(this + 3) = -1;
  *(this + 4) = -1;
  *(this + 5) = -1;
  *(this + 6) = -1;
  *(this + 7) = -1;
  *(this + 10) = -1;
  v3 = operator new(0x464u);
  if ( v3 != nullptr )
    v4 = sub_6596B0(v3);
  else
    v4 = 0;
  *(this + 8) = v4;
  return this;
}



// ------------------------------------------------------------
// 0x656E20 sub_656E20
// ------------------------------------------------------------
int /*thiscall*/ sub_656E20(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x3FFFFFFF - v2 < a2 )
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



// ------------------------------------------------------------
// 0x656EB0 sub_656EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_656EB0(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  int result; // eax

  v3 = *(this + 1);
  v4 = sub_40C0F0(v3, *(uint32_t *)(v3 + 4), a2);
  result = sub_656E20(this, 1u);
  *(uint32_t *)(v3 + 4) = v4;
  **(uint32_t **)(v4 + 4) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x656EF0 sub_656EF0
// ------------------------------------------------------------
char /*thiscall*/ sub_656EF0(int *this, const void *a2, int a3, int Block, int a5)
{
  int v5; // ebx
  void *v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // ebx
  int v11; // eax
  uint32_t *v12; // esi

  v5 = Block;
  if ( Block == -1 )
    v5 = *(this + 10);
  if ( *(uint32_t *)(*(this + 8) + 1096) == v5 )
  {
    v7 = operator new(0x818u);
    Block = (int)v7;
    if ( v7 != nullptr )
      v8 = sub_659790(v7);
    else
      v8 = 0;
    Block = v8;
    sub_6597C0(0, 0, a3, a2, v5, 0);
    v9 = *(this + 13);
    v10 = sub_40C0F0(v9, *(uint32_t *)(v9 + 4), &Block);
    LOBYTE(v11) = sub_656E20(this + 12, 1u);
    *(uint32_t *)(v9 + 4) = v10;
    **(uint32_t **)(v10 + 4) = v10;
  }
  else
  {
    v11 = *(this + v5);
    if ( v11 != -1 )
    {
      if ( a5 != 0 )
      {
        Block = 2064 * v5;
        v12 = (uint32_t *)((char *)&unk_9B9550 + 2064 * v5);
        for ( LOBYTE(v11) = sub_656720(v12, a2, a3);
              (uint8_t)v11 == 0;
              LOBYTE(v11) = sub_656720((uint32_t *)&unk_9B9550 + 516 * v5, a2, a3) )
        {
          sub_657FD0(
            (char *)&unk_9B9550 + 2064 * v5,
            (void *)*(uint16_t *)((char *)&word_9B9D50 + Block),
            *(this + v5),
            *(uint8_t *)(*(this + 8) + 1096),
            0);
          v12[513] = 0;
          v12[512] = 0;
        }
      }
      else
      {
        LOBYTE(v11) = sub_658350(a2, a3, v11, *(uint8_t *)(*(this + 8) + 1096), 0);
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// 0x657070 sub_657070
// ------------------------------------------------------------
int /*thiscall*/ sub_657070(int this, const void *a2, int a3)
{
  int result; // eax
  int v4; // edx

  result = this;
  v4 = *(uint16_t *)(this + 14);
  if ( (uint16_t)a3 + v4 > *(uint32_t *)(this + 8) )
    _CxxThrowException((char *)&a3 + 3, (_ThrowInfo *)&_TI1_AVException_CMsgCell__);
  qmemcpy((void *)(v4 + *(uint32_t *)(this + 4)), a2, (uint16_t)a3);
  *(uint16_t *)(this + 14) += a3;
  return result;
}



// ------------------------------------------------------------
// 0x6570D0 sub_6570D0
// ------------------------------------------------------------
char /*thiscall*/ sub_6570D0(int this)
{
  DWORD Time; // eax

  *(uint32_t *)(this + 2228) = timeGetTime();
  LOBYTE(Time) = *(uint8_t *)(this + 2224);
  if ( (uint8_t)Time == 0 )
  {
    sub_667430(1u);
    LOBYTE(Time) = sub_666F00(*(uint32_t *)(this + 4));
    if ( (uint8_t)Time != 0 )
    {
      Time = timeGetTime();
      if ( Time - *(uint32_t *)(this + 2228) > 0x32 )
        *(uint32_t *)(this + 2228) = Time;
    }
  }
  return Time;
}



// ------------------------------------------------------------
// 0x657120 sub_657120
// ------------------------------------------------------------
bool /*thiscall*/ sub_657120(uint32_t *this)
{
  uint32_t *v2; // edi

  v2 = this + 558;
  sub_40BE20("\nstartup[%s] :%d  \n\n", (uint8_t)this - 72);
  if ( sub_667970(v2, *(this + 622)) == 0 )
    return false;
  sub_40BE20("\ninitialize(getIP(),getPort())\n\n", (char)v2);
  return sub_667670(this) == 1;
}



// ------------------------------------------------------------
// 0x6571C0 sub_6571C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6571C0(int this, int a2)
{
  int result; // eax
  char v4; // [esp+0h] [ebp-4h]

  sub_40BE20("\nDisconnected\n\n", v4);
  *(uint8_t *)(this + 2224) = 1;
  sub_6676C0(this);
  result = *(uint32_t *)(this + 2492);
  if ( result != -1 )
  {
    result = closesocket(*(uint32_t *)(this + 2492));
    *(uint32_t *)(this + 2492) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x657200 sub_657200
// ------------------------------------------------------------
int /*thiscall*/ sub_657200(int this, int a2)
{
  *(uint8_t *)(this + 2225) = 0;
  return (***(int (/*thiscall*/ ****)(uint32_t, uint32_t, uint32_t))(this + 2512))(
           *(uint32_t *)(this + 2512),
           *(uint32_t *)(a2 + 4),
           *(uint16_t *)(*(uint32_t *)(a2 + 4) + 2));
}



// ------------------------------------------------------------
// 0x657230 sub_657230
// ------------------------------------------------------------
int /*thiscall*/ sub_657230(int this)
{
  int result; // eax

  *(uint8_t *)(this + 2224) = 1;
  sub_6676C0(this);
  result = *(uint32_t *)(this + 2492);
  if ( result != -1 )
  {
    result = closesocket(*(uint32_t *)(this + 2492));
    *(uint32_t *)(this + 2492) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x657260 sub_657260
// ------------------------------------------------------------
char /*thiscall*/ sub_657260(int this, int a2)
{
  char result; // al

  result = 0;
  *(uint32_t *)(this + 2524) = a2;
  if ( a2 <= 0 )
  {
    *(uint8_t *)(this + 2556) = 0;
    *(uint8_t *)(this + 2541) = 0;
    *(uint8_t *)(this + 2542) = 0;
    *(uint8_t *)(this + 2540) = 0;
  }
  else
  {
    *(uint8_t *)(this + 2556) = 1;
    *(uint8_t *)(this + 2541) = 0;
    *(uint8_t *)(this + 2542) = 0;
    result = sub_698F90(this + 2528, *(uint32_t *)(this + 2524), 0);
    *(uint8_t *)(this + 2540) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6572C0 sub_6572C0
// ------------------------------------------------------------
char /*thiscall*/ sub_6572C0(int this)
{
  SOCKET v2; // eax
  char LastError; // al
  char v5; // [esp+0h] [ebp-4h]

  sub_667430(0);
  if ( (uint8_t)sub_666F00(*(uint32_t *)(this + 4)) == 0 )
    return 0;
  v2 = socket(2, 2, 17);
  *(uint32_t *)(this + 2492) = v2;
  if ( v2 == -1 )
  {
    LastError = GetLastError();
    sub_40BE20("\n\nCould not create a UDP socket : %d\n", LastError);
    return 0;
  }
  *(uint32_t *)(this + 2496) = 0;
  *(uint32_t *)(this + 2500) = 0;
  *(uint32_t *)(this + 2504) = 0;
  *(uint32_t *)(this + 2508) = 0;
  *(uint16_t *)(this + 2496) = 2;
  *(uint16_t *)(this + 2498) = htons(*(uint16_t *)(this + 2488));
  *(uint32_t *)(this + 2500) = inet_addr((const char *)(this + 2232));
  *(uint8_t *)(this + 2224) = 0;
  *(uint8_t *)(this + 2225) = 1;
  sub_40BE20("\nconnected to Relayserver\n\n", v5);
  return 1;
}


