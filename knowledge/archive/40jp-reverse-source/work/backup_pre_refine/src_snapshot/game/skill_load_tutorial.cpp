// ============================================================
// 【40JP逆向源代码工程】game/skill_load_tutorial.cpp
// 模块: 技能加载/教程
// 来源: work/dump_misca.txt  区块: 0x480000-0x490000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 305
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x480020 sub_480020
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480020(uint32_t *this, int a2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int v7; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(a2 + 4);
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(a2 + 8) - v2) / 14;
  if ( (uint8_t)sub_47FC20(v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(uint32_t *)(a2 + 8);
    v5 = *(uint32_t *)(a2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_47E200(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4800C0 sub_4800C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4800C0(int this, int a2)
{
  int v3; // ebx
  unsigned int v4; // ecx
  int v6; // eax
  unsigned int v7; // edx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // edx
  int v11; // edx
  int v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 3) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(uint32_t *)(this + 4);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 8) - v6) >> 3;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    sub_47E1D0(v3, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 8 * ((*(uint32_t *)(a2 + 8) - v8) >> 3);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != 0 )
    v10 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != 0 )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 3;
    else
      v14 = 0;
    if ( (uint8_t)sub_42D030(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_472EA0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  if ( v6 != 0 )
    v11 = (*(uint32_t *)(this + 8) - v6) >> 3;
  else
    v11 = 0;
  v12 = *(uint32_t *)(a2 + 4) + 8 * v11;
  sub_47E1D0(*(uint32_t *)(a2 + 4), v12, *(uint32_t *)(this + 4));
  *(uint32_t *)(this + 8) = sub_44BD30(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x480210 sub_480210
// ------------------------------------------------------------
int /*thiscall*/ sub_480210(int this, int a2)
{
  int v3; // ecx
  unsigned int v4; // edx
  void *v6; // ecx
  unsigned int v7; // ebx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 2) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(void **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    memcpy_0(v6, *(const void **)(a2 + 4), 4 * ((*(uint32_t *)(a2 + 8) - *(uint32_t *)(a2 + 4)) >> 2));
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(a2 + 8) - v8) >> 2);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != nullptr )
    v10 = (*(uint32_t *)(this + 12) - (int)v6) >> 2;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 2;
    else
      v14 = 0;
    if ( (uint8_t)sub_47FB20(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(a2 + 4), *(uint32_t *)(a2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v11 = 0;
  v12 = (void *)(*(uint32_t *)(a2 + 4) + 4 * v11);
  sub_433A30(*(void **)(a2 + 4), (int)v12, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(a2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x480360 sub_480360
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480360(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
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
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( (uint8_t)sub_42D030(v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = *(uint32_t *)(a2 + 8);
    v6 = *(uint32_t *)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x480400 sub_480400
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480400(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
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
  if ( (uint8_t)sub_47FB20(v4) != 0 )
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
// 0x4804A0 sub_4804A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4804A0(int this, int a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  int v7; // edi
  unsigned int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 12) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v7 = *(uint32_t *)(this + 4);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(this + 8) - v7) / 12;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(this + 12) - v7) / 12;
    else
      v10 = 0;
    if ( v5 <= v10 )
    {
      v12 = *(uint32_t *)(a2 + 4) + 12 * sub_4DA030(this);
      sub_47E170(*(uint32_t *)(a2 + 4), v12, v7);
      *(uint32_t *)(this + 8) = sub_59EE30(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != 0 )
      j__free(*(void **)(this + 4));
    v11 = sub_4DA030(a2);
    if ( (uint8_t)sub_47FB80(v11) != 0 )
      *(uint32_t *)(this + 8) = sub_47F790(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  sub_47DDD0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), v7);
  v9 = *(uint32_t *)(a2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 12 * ((*(uint32_t *)(a2 + 8) - v9) / 12);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x480620 sub_480620
// ------------------------------------------------------------
int /*thiscall*/ sub_480620(int this, int a2)
{
  int v2; // edi
  int v4; // eax
  unsigned int v5; // ecx
  int v7; // ebx
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax

  v2 = a2;
  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 14) == 0 )
  {
    sub_47F6E0(this);
    return this;
  }
  v7 = *(uint32_t *)(this + 4);
  if ( v7 != 0 )
  {
    v2 = a2;
    v8 = (*(uint32_t *)(this + 8) - v7) / 14;
  }
  else
  {
    v8 = 0;
  }
  if ( v5 > v8 )
  {
    if ( v7 != 0 )
    {
      v2 = a2;
      v11 = (*(uint32_t *)(this + 12) - v7) / 14;
    }
    else
    {
      v11 = 0;
    }
    if ( v5 <= v11 )
    {
      v12 = *(uint32_t *)(a2 + 4) + 14 * sub_47DD70(this);
      sub_47E190(*(uint32_t *)(a2 + 4), v12, v7);
      *(uint32_t *)(this + 8) = sub_47E200(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != 0 )
    {
      sub_47F6B0(v7, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_47DD70(v2);
    if ( (uint8_t)sub_47FC20(v13) != 0 )
      *(uint32_t *)(this + 8) = sub_47F7B0(*(uint32_t *)(v2 + 4), *(uint32_t *)(v2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  v9 = sub_47DE10(*(uint32_t *)(v2 + 4), *(uint32_t *)(v2 + 8), v7);
  sub_47F6B0(v9, *(uint32_t *)(this + 8));
  v10 = *(uint32_t *)(v2 + 4);
  if ( v10 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 14 * ((*(uint32_t *)(v2 + 8) - v10) / 14);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x4807B0 sub_4807B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4807B0(int *this, unsigned int a2, int a3, int a4, int a5, int a6)
{
  int v6; // ebx
  unsigned int v7; // eax
  int v8; // eax

  v6 = *(this + 1);
  v7 = 0;
  if ( v6 != 0 )
    v7 = (*(this + 2) - v6) / 14;
  if ( v7 >= a2 )
  {
    if ( v6 != 0 && a2 < (*(this + 2) - v6) / 14 )
      sub_47F720(&a2, v6 + 14 * a2, *(this + 2));
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) / 14;
    else
      v8 = 0;
    sub_47FD00(this, *(this + 2), a2 - v8, (int)&a3);
  }
  sub_41A580(&a3);
}



// ------------------------------------------------------------
// 0x480880 sub_480880
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480880(int *this, uint32_t *a2, int a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 14 != 0 )
    v6 = (a3 - v5) / 14;
  else
    v6 = 0;
  sub_47FD00(this, a3, 1u, a4);
  *a2 = *(this + 1) + 14 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4808F0 sub_4808F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4808F0(int a1, int a2, int a3)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 16 )
    result = sub_480620(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x480920 sub_480920
// ------------------------------------------------------------
int /*cdecl*/ sub_480920(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_480620(v4, v3);
    v3 += 16;
    v4 += 16;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x480960 sub_480960
// ------------------------------------------------------------
int /*cdecl*/ sub_480960(int a1, int a2)
{
  int result; // eax
  int i; // edi
  char *v4; // esi
  char *j; // ebx

  result = a2;
  for ( i = a1; i != a2; i += 16 )
  {
    v4 = *(char **)(i + 4);
    if ( v4 != nullptr )
    {
      for ( j = *(char **)(i + 8); v4 != j; v4 += 14 )
        (**(void (/*thiscall*/ ***)(char *, uint32_t))v4)(v4, 0);
      j__free(*(void **)(i + 4));
    }
    *(uint32_t *)(i + 4) = 0;
    *(uint32_t *)(i + 8) = 0;
    *(uint32_t *)(i + 12) = 0;
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4809C0 sub_4809C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4809C0(int a1, int a2, int a3)
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
    sub_480620(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x480A00 sub_480A00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480A00(int a1, int a2, uint32_t *a3)
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
      sub_480020(v3, a1);
    v3 += 4;
    LOBYTE(v7) = 0;
    a1 += 16;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x480A90 sub_480A90
// ------------------------------------------------------------
unsigned int **/*thiscall*/ sub_480A90(unsigned int **this, int a2)
{
  unsigned int **v3; // ecx

  *this = *(unsigned int **)a2;
  *(this + 1) = *(unsigned int **)(a2 + 4);
  v3 = this + 2;
  *v3 = nullptr;
  sub_41B0D0(v3, (unsigned int **)(a2 + 8));
  sub_480360(this + 3, a2 + 12);
  sub_480400(this + 7, a2 + 28);
  return this;
}



// ------------------------------------------------------------
// 0x480B10 sub_480B10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_480B10(int *this, int a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 14;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 14 )
    return sub_480880(this, &a2, *(this + 2), a2);
  v5 = *(this + 2);
  result = (uint32_t *)sub_47E920(v5, 1, a2);
  *(this + 2) = v5 + 14;
  return result;
}



// ------------------------------------------------------------
// 0x480BA0 sub_480BA0
// ------------------------------------------------------------
int /*cdecl*/ sub_480BA0(int a1, int a2, int a3)
{
  return sub_4809C0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x480BC0 sub_480BC0
// ------------------------------------------------------------
int /*cdecl*/ sub_480BC0(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *(uint32_t *)v4 = *(uint32_t *)v3;
    *(uint32_t *)(v4 + 4) = *(uint32_t *)(v3 + 4);
    sub_41B0D0((unsigned int **)(v4 + 8), (unsigned int **)(v3 + 8));
    sub_4800C0(v4 + 12, v3 + 12);
    sub_480210(v4 + 28, v3 + 28);
    v3 += 44;
    v4 += 44;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x480C20 sub_480C20
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480C20(uint32_t *a1, int a2, int a3)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax
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
      result = sub_480020(v3, a3);
    --a2;
    v3 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x480CB0 sub_480CB0
// ------------------------------------------------------------
int /*stdcall*/ sub_480CB0(int a1, int a2)
{
  return sub_480960(a1, a2);
}



// ------------------------------------------------------------
// 0x480CD0 sub_480CD0
// ------------------------------------------------------------
int */*thiscall*/ sub_480CD0(int *this, int *a2, int a3, int a4)
{
  int v5; // edi

  if ( a3 != a4 )
  {
    v5 = sub_480920(a4, *(this + 2), a3);
    sub_480960(v5, *(this + 2));
    *(this + 2) = v5;
  }
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x480D20 sub_480D20
// ------------------------------------------------------------
int /*cdecl*/ sub_480D20(int a1, int a2, int a3)
{
  return sub_480BC0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x480D40 sub_480D40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_480D40(char *a1, char *a2, uint32_t *a3)
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
    {
      sub_435020(a1);
      v3[4] = *((uint32_t *)a1 + 4);
      v3[5] = *((uint32_t *)a1 + 5);
    }
    v3 += 6;
    LOBYTE(v7) = 0;
    a1 += 24;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x480DF0 sub_480DF0
// ------------------------------------------------------------
void /*thiscall*/ sub_480DF0(int *this)
{
  int v2; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
  {
    sub_480960(v2, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x480E40 sub_480E40
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_480E40(uint32_t *a1, int a2, int a3)
{
  sub_480C20(a1, a2, a3);
  return &a1[4 * a2];
}



// ------------------------------------------------------------
// 0x480E70 sub_480E70
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_480E70(int a1, int a2, unsigned int **a3)
{
  unsigned int **v3; // esi
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
      sub_480A90(v3, a1);
    v3 += 11;
    LOBYTE(v7) = 0;
    a1 += 44;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x480F40 sub_480F40
// ------------------------------------------------------------
int /*stdcall*/ sub_480F40(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 44 )
    result = sub_47FA00(i);
  return result;
}



// ------------------------------------------------------------
// 0x480F70 sub_480F70
// ------------------------------------------------------------
int /*thiscall*/ sub_480F70(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 44 )
      sub_47FA00(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x480FB0 sub_480FB0
// ------------------------------------------------------------
int /*thiscall*/ sub_480FB0(int *this, int a2, unsigned int a3, int a4)
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
  uint32_t *v17; // eax
  int v18; // edi
  int v19; // edi
  uint32_t *v20; // eax
  int v22; // [esp-18h] [ebp-4Ch]
  void *v23; // [esp-18h] [ebp-4Ch]
  int v24; // [esp-Ch] [ebp-40h]
  unsigned int v25; // [esp-8h] [ebp-3Ch]
  int v26; // [esp+0h] [ebp-34h] BYREF
  uint32_t v27[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int *v29; // [esp+20h] [ebp-14h]
  int *v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+30h] [ebp-4h]
  uint32_t *v32; // [esp+40h] [ebp+Ch]
  int v33; // [esp+44h] [ebp+10h]

  v30 = &v26;
  v29 = this;
  sub_480020(v27, a4);
  v5 = *(this + 1);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v7 = (*(this + 3) - v5) >> 4;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v6 = (*(this + 2) - v5) >> 4;
    if ( 0xFFFFFFF - v6 < a3 )
      sub_47F990(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) >> 4;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v17 = (uint32_t *)*(this + 2);
      Block = v17;
      if ( ((int)v17 - a2) >> 4 >= a3 )
      {
        v19 = (int)&v17[-4 * a3];
        v20 = sub_480A00(v19, (int)v17, v17);
        v23 = Block;
        *(this + 2) = (int)v20;
        sub_480BA0(a2, v19, v23);
        sub_4808F0(a2, a2 + 16 * a3, v27);
      }
      else
      {
        sub_480A00(a2, (int)v17, (uint32_t *)(a2 + 16 * a3));
        v25 = a3 - ((*(this + 2) - a2) >> 4);
        v24 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_480E40(v24, v25, v27);
        v18 = 16 * a3 + *(this + 2);
        *(this + 2) = v18;
        v31 = 0;
        sub_4808F0(a2, v18 - 16 * a3, v27);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) >> 4;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(this + 2) - v5) >> 4;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v33 = 16 * v10;
      v13 = (char *)operator new(16 * v10);
      v22 = *(this + 1);
      Block = v13;
      LOBYTE(v31) = 1;
      v32 = sub_480A00(v22, a2, v13);
      sub_480C20(v32, a3, (int)v27);
      sub_480A00(a2, *(this + 2), &v32[4 * a3]);
      v14 = *(this + 1);
      v31 = 0;
      if ( v14 != 0 )
        v15 = (*(this + 2) - v14) >> 4;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != 0 )
      {
        sub_480960(v14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v13[v33];
      *(this + 2) = (int)&v13[16 * v16];
      *(this + 1) = (int)v13;
    }
  }
  v31 = -1;
  return sub_47F6E0(v27);
}


// ------------------------------------------------------------
// 0x481260 sub_481260
// ------------------------------------------------------------
int /*thiscall*/ sub_481260(int *this, unsigned int a2, char a3, int a4, int a5, int a6)
{
  int v6; // esi
  unsigned int v7; // edx
  int v8; // edx

  v6 = *(this + 1);
  if ( v6 != 0 )
    v7 = (*(this + 2) - v6) >> 4;
  else
    v7 = 0;
  if ( v7 >= a2 )
  {
    if ( v6 != 0 && a2 < (*(this + 2) - v6) >> 4 )
      sub_480CD0(this, (int *)&a2, v6 + 16 * a2, *(this + 2));
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) >> 4;
    else
      v8 = 0;
    sub_480FB0(this, *(this + 2), a2 - v8, (int)&a3);
  }
  return sub_47F6E0(&a3);
}



// ------------------------------------------------------------
// 0x481300 sub_481300
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_481300(uint32_t *this, int a2)
{
  int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  uint32_t *v7; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(a2 + 4);
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(a2 + 8) - v2) / 24;
  if ( (uint8_t)sub_434950(v2) != 0 )
  {
    v7 = (uint32_t *)*(this + 1);
    v6 = *(char **)(a2 + 8);
    v5 = *(char **)(a2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_480D40(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4813A0 sub_4813A0
// ------------------------------------------------------------
unsigned int **/*stdcall*/ sub_4813A0(int a1, int a2, unsigned int **a3)
{
  return sub_480E70(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4813C0 sub_4813C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4813C0(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 44;
    v4 -= 44;
    sub_439050((void *)v3);
    sub_4ED3F0(v4 + 16, v3 + 16);
    *(uint32_t *)(v4 + 32) = *(uint32_t *)(v3 + 32);
    *(uint32_t *)(v4 + 36) = *(uint32_t *)(v3 + 36);
    *(uint8_t *)(v4 + 40) = *(uint8_t *)(v3 + 40);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x481420 sub_481420
// ------------------------------------------------------------
void /*thiscall*/ sub_481420(char *this)
{
  uint32_t *v2; // eax
  int i; // ecx
  uint32_t *v4; // eax
  int j; // ecx
  uint32_t *v6; // edi
  char *v7; // edi
  int v8; // edi
  int v9; // ecx
  int v10; // edi
  int k; // [esp+8h] [ebp-4h]
  char *m; // [esp+8h] [ebp-4h]
  int n; // [esp+8h] [ebp-4h]
  int ii; // [esp+8h] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_41BFE0(szPassword);
  sub_41BFE0(szPassword);
  *((uint32_t *)this + 4) = 0;
  sub_41BFE0(szPassword);
  if ( *((uint32_t *)this + 6) != 0 )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 1;
  *((uint32_t *)this + 10) = 1;
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
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  v2 = this + 104;
  for ( i = 5; i != 0; --i )
  {
    *(v2 - 5) = 0;
    *v2++ = 0;
  }
  v4 = this + 132;
  for ( j = 2; j != 0; --j )
  {
    *(v4 - 2) = 0;
    *v4 = 0;
    v4[6] = 0;
    ++v4;
  }
  if ( *((uint32_t *)this + 36) != 0 )
    j__free(*((void **)this + 36));
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  if ( *((uint32_t *)this + 42) != 0 )
    j__free(*((void **)this + 42));
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  *(this + 180) = 1;
  v6 = this + 192;
  for ( k = 2; k != 0; --k )
  {
    sub_41BFE0(szPassword);
    *v6++ = 0;
  }
  v7 = *((char **)this + 51);
  if ( v7 != nullptr )
  {
    for ( m = *((char **)this + 52); v7 != m; v7 += 24 )
      sub_5E5260(v7);
    j__free(*((void **)this + 51));
  }
  *((uint32_t *)this + 51) = 0;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 53) = 0;
  if ( *((uint32_t *)this + 55) != 0 )
    j__free(*((void **)this + 55));
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 58) = 1;
  *((uint32_t *)this + 59) = 0;
  *(this + 240) = 1;
  sub_41BFE0(szPassword);
  if ( *((uint32_t *)this + 63) != 0 )
    j__free(*((void **)this + 63));
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  v8 = *((uint32_t *)this + 67);
  if ( v8 != 0 )
  {
    v9 = *((uint32_t *)this + 68);
    for ( n = v9; v8 != v9; v8 += 16 )
    {
      if ( *(uint32_t *)(v8 + 4) != 0 )
      {
        j__free(*(void **)(v8 + 4));
        v9 = n;
      }
      *(uint32_t *)(v8 + 4) = 0;
      *(uint32_t *)(v8 + 8) = 0;
      *(uint32_t *)(v8 + 12) = 0;
    }
    j__free(*((void **)this + 67));
  }
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  v10 = *((uint32_t *)this + 71);
  if ( v10 != 0 )
  {
    for ( ii = *((uint32_t *)this + 72); v10 != ii; v10 += 44 )
      sub_47FA00(v10);
    j__free(*((void **)this + 71));
  }
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 72) = 0;
  *((uint32_t *)this + 73) = 0;
  *((uint32_t *)this + 74) = 0;
  *((uint32_t *)this + 75) = 0;
  *(this + 320) = 0;
  *((uint32_t *)this + 81) = 0;
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  if ( *((uint32_t *)this + 77) != 0 )
    j__free(*((void **)this + 77));
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  *((uint32_t *)this + 79) = 0;
}


// ------------------------------------------------------------
// 0x481720 sub_481720
// ------------------------------------------------------------
int /*thiscall*/ sub_481720(int this)
{
  *(uint32_t *)(this + 4) = 0;
  sub_41BFE0(szPassword);
  *(uint32_t *)(this + 8) = 0;
  sub_41BFE0(szPassword);
  *(uint32_t *)(this + 12) = 0;
  sub_41BFE0(szPassword);
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  `eh vector constructor iterator'((void *)(this + 184), 4u, 2, sub_432D20, sub_401060);
  sub_436F50(this + 200);
  *(uint32_t *)(this + 244) = 0;
  sub_41BFE0(szPassword);
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 292) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  sub_481420((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x481860 sub_481860
// ------------------------------------------------------------
void /*thiscall*/ sub_481860(int this)
{
  void *v2; // eax
  int v3; // eax

  v2 = *(void **)(this + 308);
  if ( v2 != nullptr )
    j__free(v2);
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  sub_480F70((int *)(this + 280));
  v3 = *(uint32_t *)(this + 268);
  if ( v3 != 0 )
  {
    sub_42CC00(v3, *(uint32_t *)(this + 272));
    j__free(*(void **)(this + 268));
  }
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  if ( *(uint32_t *)(this + 252) != 0 )
    j__free(*(void **)(this + 252));
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  sub_41B010((void **)(this + 244));
  if ( *(uint32_t *)(this + 220) != 0 )
    j__free(*(void **)(this + 220));
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  sub_435850(this + 200);
  `eh vector destructor iterator'((void *)(this + 184), 4u, 2, (void (/*thiscall*/ *)(void *))sub_401060);
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  if ( *(uint32_t *)(this + 144) != 0 )
    j__free(*(void **)(this + 144));
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
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
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  sub_41B010((void **)(this + 12));
  sub_41B010((void **)(this + 8));
  sub_41B010((void **)(this + 4));
}



// ------------------------------------------------------------
// 0x481A30 sub_481A30
// ------------------------------------------------------------
int /*thiscall*/ sub_481A30(int this, int a2)
{
  int v3; // eax
  unsigned int v4; // ecx
  int v6; // ebx
  unsigned int v7; // eax
  int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  int v11; // edi
  int v12; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) / 44) == 0 )
  {
    sub_480F70((int *)this);
    return this;
  }
  v6 = *(uint32_t *)(this + 4);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 8) - v6) / 44;
  else
    v7 = 0;
  if ( v4 > v7 )
  {
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 12) - v6) / 44;
    else
      v10 = 0;
    if ( v4 <= v10 )
    {
      v11 = *(uint32_t *)(a2 + 4) + 44 * sub_527B90(this);
      sub_480D20(*(uint32_t *)(a2 + 4), v11, v6);
      *(uint32_t *)(this + 8) = sub_480E70(v11, *(uint32_t *)(a2 + 8), *(unsigned int ***)(this + 8));
      return this;
    }
    if ( v6 != 0 )
    {
      sub_480F40(v6, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v12 = sub_527B90(a2);
    if ( (uint8_t)sub_47FBD0(v12) != 0 )
      *(uint32_t *)(this + 8) = sub_4813A0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(unsigned int ***)(this + 4));
    return this;
  }
  v8 = sub_480BC0(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), v6);
  sub_480F40(v8, *(uint32_t *)(this + 8));
  v9 = *(uint32_t *)(a2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 44 * ((*(uint32_t *)(a2 + 8) - v9) / 44);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x481BB0 sub_481BB0
// ------------------------------------------------------------
int /*thiscall*/ sub_481BB0(int this, int a2)
{
  sub_481300((uint32_t *)this, a2);
  sub_435020((void *)(a2 + 16));
  *(uint32_t *)(this + 32) = *(uint32_t *)(a2 + 32);
  *(uint32_t *)(this + 36) = *(uint32_t *)(a2 + 36);
  *(uint8_t *)(this + 40) = *(uint8_t *)(a2 + 40);
  return this;
}



// ------------------------------------------------------------
// 0x481C20 sub_481C20
// ------------------------------------------------------------
int /*cdecl*/ sub_481C20(int a1, int a2, void *a3)
{
  int result; // eax
  int i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 44 )
  {
    sub_439050(a3);
    sub_4ED3F0(i + 16, (int)a3 + 16);
    *(uint32_t *)(i + 32) = *((uint32_t *)a3 + 8);
    result = a2;
    *(uint32_t *)(i + 36) = *((uint32_t *)a3 + 9);
    *(uint8_t *)(i + 40) = *((uint8_t *)a3 + 40);
  }
  return result;
}



// ------------------------------------------------------------
// 0x481C70 sub_481C70
// ------------------------------------------------------------
int /*cdecl*/ sub_481C70(int a1, int a2, int a3)
{
  return sub_4813C0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x481C90 sub_481C90
// ------------------------------------------------------------
int /*cdecl*/ sub_481C90(int a1, int a2, int a3)
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
      sub_481BB0(v3, a1);
    v3 += 44;
    LOBYTE(v7) = 0;
    a1 += 44;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x481D40 sub_481D40
// ------------------------------------------------------------
void /*cdecl*/ sub_481D40(int a1, int a2, int a3)
{
  int v3; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v5[4] = v5;
  v5[3] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( v3 != 0 )
      sub_481BB0(v3, a3);
    --a2;
    v3 += 44;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x481DF0 sub_481DF0
// ------------------------------------------------------------
int /*stdcall*/ sub_481DF0(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 44 )
    result = sub_437950(i);
  return result;
}



// ------------------------------------------------------------
// 0x481E20 sub_481E20
// ------------------------------------------------------------
int /*thiscall*/ sub_481E20(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 44 )
      sub_437950(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x481E70 sub_481E70
// ------------------------------------------------------------
int /*stdcall*/ sub_481E70(int a1, int a2, int a3)
{
  sub_481D40(a1, a2, a3);
  return a1 + 44 * a2;
}



// ------------------------------------------------------------
// 0x481EA0 sub_481EA0
// ------------------------------------------------------------
void /*thiscall*/ sub_481EA0(int this)
{
  int v2; // edi
  char *v3; // edi
  char *v4; // edi
  char *v5; // edi
  char *v6; // edi
  int v7; // edi
  char *v8; // edi
  int v9; // eax
  int v10; // edi
  int i; // [esp+Ch] [ebp-4h]
  char *j; // [esp+Ch] [ebp-4h]
  char *k; // [esp+Ch] [ebp-4h]
  char *m; // [esp+Ch] [ebp-4h]
  char *n; // [esp+Ch] [ebp-4h]
  int ii; // [esp+Ch] [ebp-4h]
  char *jj; // [esp+Ch] [ebp-4h]
  int kk; // [esp+Ch] [ebp-4h]

  sub_41A590(0);
  sub_41BFE0((void **)(this + 16), szPassword);
  sub_41BFE0((void **)(this + 20), szPassword);
  sub_41BFE0((void **)(this + 24), szPassword);
  sub_41A590(0);
  sub_47F6E0(this + 44);
  sub_41A590(1);
  sub_41A590(1);
  sub_47F6E0(this + 88);
  sub_47F6E0(this + 104);
  *(uint32_t *)(this + 120) = 0;
  sub_41A590(0);
  v2 = this + 208;
  for ( i = 5; i != 0; --i )
  {
    sub_41A590(0);
    sub_41A590(0);
    v2 += 14;
  }
  sub_41A590(0);
  v3 = *(char **)(this + 296);
  if ( v3 != nullptr )
  {
    for ( j = *(char **)(this + 300); v3 != j; v3 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v3)(v3, 0);
    j__free(*(void **)(this + 296));
  }
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  v4 = *(char **)(this + 312);
  if ( v4 != nullptr )
  {
    for ( k = *(char **)(this + 316); v4 != k; v4 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v4)(v4, 0);
    j__free(*(void **)(this + 312));
  }
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  if ( *(uint32_t *)(this + 328) != 0 )
    j__free(*(void **)(this + 328));
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  v5 = *(char **)(this + 344);
  if ( v5 != nullptr )
  {
    for ( m = *(char **)(this + 348); v5 != m; v5 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v5)(v5, 0);
    j__free(*(void **)(this + 344));
  }
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 348) = 0;
  *(uint32_t *)(this + 352) = 0;
  v6 = *(char **)(this + 360);
  if ( v6 != nullptr )
  {
    for ( n = *(char **)(this + 364); v6 != n; v6 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v6)(v6, 0);
    j__free(*(void **)(this + 360));
  }
  *(uint32_t *)(this + 360) = 0;
  *(uint32_t *)(this + 364) = 0;
  *(uint32_t *)(this + 368) = 0;
  *(uint8_t *)(this + 372) = 1;
  *(uint32_t *)(this + 376) = 0;
  *(uint32_t *)(this + 380) = 0;
  v7 = *(uint32_t *)(this + 388);
  if ( v7 != 0 )
  {
    for ( ii = *(uint32_t *)(this + 392); v7 != ii; v7 += 44 )
      sub_437950(v7);
    j__free(*(void **)(this + 388));
  }
  *(uint32_t *)(this + 388) = 0;
  *(uint32_t *)(this + 392) = 0;
  *(uint32_t *)(this + 396) = 0;
  sub_41BFE0((void **)(this + 400), szPassword);
  v8 = *(char **)(this + 408);
  if ( v8 != nullptr )
  {
    for ( jj = *(char **)(this + 412); v8 != jj; v8 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v8)(v8, 0);
    j__free(*(void **)(this + 408));
  }
  *(uint32_t *)(this + 408) = 0;
  *(uint32_t *)(this + 412) = 0;
  *(uint32_t *)(this + 416) = 0;
  v9 = *(uint32_t *)(this + 424);
  if ( v9 != 0 )
  {
    sub_480960(v9, *(uint32_t *)(this + 428));
    j__free(*(void **)(this + 424));
  }
  *(uint32_t *)(this + 424) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;
  v10 = *(uint32_t *)(this + 440);
  if ( v10 != 0 )
  {
    for ( kk = *(uint32_t *)(this + 444); v10 != kk; v10 += 44 )
      sub_47FA00(v10);
    j__free(*(void **)(this + 440));
  }
  *(uint32_t *)(this + 440) = 0;
  *(uint32_t *)(this + 444) = 0;
  *(uint32_t *)(this + 448) = 0;
  *(uint32_t *)(this + 452) = 0;
  *(uint32_t *)(this + 456) = 0;
  *(uint8_t *)(this + 476) = 0;
  *(uint32_t *)(this + 480) = 0;
  *(uint32_t *)(this + 484) = 0;
  *(uint32_t *)(this + 488) = 0;
  if ( *(uint32_t *)(this + 464) != 0 )
    j__free(*(void **)(this + 464));
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 472) = 0;
}


// ------------------------------------------------------------
// 0x482240 sub_482240
// ------------------------------------------------------------
char */*thiscall*/ sub_482240(char *this)
{
  sub_41A630((unsigned int)this);
  *(uint32_t *)this = &clong::`vftable';
  *((uint32_t *)this + 4) = 0;
  sub_41BFE0((void **)this + 4, szPassword);
  *((uint32_t *)this + 5) = 0;
  sub_41BFE0((void **)this + 5, szPassword);
  *((uint32_t *)this + 6) = 0;
  sub_41BFE0((void **)this + 6, szPassword);
  sub_41A630((unsigned int)(this + 28));
  *((uint32_t *)this + 7) = &clong::`vftable';
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  sub_41A630((unsigned int)(this + 60));
  *((uint32_t *)this + 15) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 74));
  *(uint32_t *)(this + 74) = &clong::`vftable';
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  sub_41A630((unsigned int)(this + 124));
  *((uint32_t *)this + 31) = &clong::`vftable';
  `eh vector constructor iterator'(this + 138, 0xEu, 5, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);
  `eh vector constructor iterator'(this + 208, 0xEu, 5, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);
  sub_41A630((unsigned int)(this + 278));
  *(uint32_t *)(this + 278) = &clong::`vftable';
  *((uint32_t *)this + 74) = 0;
  *((uint32_t *)this + 75) = 0;
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 78) = 0;
  *((uint32_t *)this + 79) = 0;
  *((uint32_t *)this + 80) = 0;
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 87) = 0;
  *((uint32_t *)this + 88) = 0;
  *((uint32_t *)this + 90) = 0;
  *((uint32_t *)this + 91) = 0;
  *((uint32_t *)this + 92) = 0;
  *((uint32_t *)this + 97) = 0;
  *((uint32_t *)this + 98) = 0;
  *((uint32_t *)this + 99) = 0;
  *((uint32_t *)this + 100) = 0;
  sub_41BFE0((void **)this + 100, szPassword);
  *((uint32_t *)this + 102) = 0;
  *((uint32_t *)this + 103) = 0;
  *((uint32_t *)this + 104) = 0;
  *((uint32_t *)this + 106) = 0;
  *((uint32_t *)this + 107) = 0;
  *((uint32_t *)this + 108) = 0;
  *((uint32_t *)this + 110) = 0;
  *((uint32_t *)this + 111) = 0;
  *((uint32_t *)this + 112) = 0;
  *((uint32_t *)this + 116) = 0;
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 0;
  sub_481EA0((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x482450 sub_482450
// ------------------------------------------------------------
void /*thiscall*/ sub_482450(int this)
{
  void *v2; // eax
  int v3; // eax

  v2 = *(void **)(this + 464);
  if ( v2 != nullptr )
    j__free(v2);
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 472) = 0;
  sub_480F70((int *)(this + 436));
  v3 = *(uint32_t *)(this + 424);
  if ( v3 != 0 )
  {
    sub_480960(v3, *(uint32_t *)(this + 428));
    j__free(*(void **)(this + 424));
  }
  *(uint32_t *)(this + 424) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;
  sub_47F6E0(this + 404);
  sub_41B010((void **)(this + 400));
  sub_481E20((int *)(this + 384));
  sub_47F6E0(this + 356);
  sub_47F6E0(this + 340);
  if ( *(uint32_t *)(this + 328) != 0 )
    j__free(*(void **)(this + 328));
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  sub_47F6E0(this + 308);
  sub_47F6E0(this + 292);
  sub_41A580((uint32_t *)(this + 278));
  `eh vector destructor iterator'((void *)(this + 208), 0xEu, 5, sub_432D10);
  `eh vector destructor iterator'((void *)(this + 138), 0xEu, 5, sub_432D10);
  sub_41A580((uint32_t *)(this + 124));
  sub_47F6E0(this + 104);
  sub_47F6E0(this + 88);
  sub_41A580((uint32_t *)(this + 74));
  sub_41A580((uint32_t *)(this + 60));
  sub_47F6E0(this + 44);
  sub_41A580((uint32_t *)(this + 28));
  sub_41B010((void **)(this + 24));
  sub_41B010((void **)(this + 20));
  sub_41B010((void **)(this + 16));
  sub_41A580((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x482650 sub_482650
// ------------------------------------------------------------
void /*thiscall*/ sub_482650(int *this, int a2, unsigned int a3, int a4)
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
  void *v19; // esi
  char *v20; // edi
  char *v21; // esi
  int v22; // [esp-18h] [ebp-68h]
  int v23; // [esp-Ch] [ebp-5Ch]
  unsigned int v24; // [esp-8h] [ebp-58h]
  int v25; // [esp+0h] [ebp-50h] BYREF
  char v26[4]; // [esp+Ch] [ebp-44h] BYREF
  void *v27; // [esp+10h] [ebp-40h]
  char *v28; // [esp+14h] [ebp-3Ch]
  void *v29; // [esp+20h] [ebp-30h]
  int v30; // [esp+24h] [ebp-2Ch]
  int v31; // [esp+28h] [ebp-28h]
  void *Block; // [esp+38h] [ebp-18h]
  int *v33; // [esp+3Ch] [ebp-14h]
  int *v34; // [esp+40h] [ebp-10h]
  int v35; // [esp+4Ch] [ebp-4h]
  int v36; // [esp+58h] [ebp+8h]
  int v37; // [esp+5Ch] [ebp+Ch]
  int v38; // [esp+60h] [ebp+10h]
  int v39; // [esp+60h] [ebp+10h]

  v34 = &v25;
  v33 = this;
  sub_481BB0((int)v26, a4);
  v5 = *(this + 1);
  v6 = 0;
  v35 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 44;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 44;
    else
      v8 = 0;
    if ( 97612893 - v8 < a3 )
      sub_47F990(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 44;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v39 = v16;
      if ( (v16 - a2) / 44 >= a3 )
      {
        v36 = v16 - 44 * a3;
        *(this + 2) = sub_481C90(v36, v16, v16);
        sub_481C70(a2, v36, v39);
        sub_481C20(a2, a2 + 44 * a3, v26);
      }
      else
      {
        sub_481C90(a2, v16, a2 + 44 * a3);
        v24 = a3 - (*(this + 2) - a2) / 44;
        v23 = *(this + 2);
        LOBYTE(v35) = 3;
        sub_481E70(v23, v24, v26);
        v18 = 44 * a3 + *(this + 2);
        *(this + 2) = v18;
        v35 = 0;
        sub_481C20(a2, v18 - 44 * a3, v26);
      }
    }
    else
    {
      if ( 97612893 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 44;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_527B90(this);
      v38 = 44 * v10;
      v12 = (char *)operator new(44 * v10);
      v22 = *(this + 1);
      Block = v12;
      LOBYTE(v35) = 1;
      v37 = sub_481C90(v22, a2, (int)v12);
      sub_481D40(v37, a3, (int)v26);
      sub_481C90(a2, *(this + 2), 44 * a3 + v37);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 44;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_481DF0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v38];
      *(this + 2) = (int)&v12[44 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v29 != nullptr )
    j__free(v29);
  v19 = v27;
  v29 = nullptr;
  v30 = 0;
  v31 = 0;
  if ( v27 != nullptr )
  {
    v20 = v28;
    if ( v27 != v28 )
    {
      v21 = (char *)v27 + 4;
      do
      {
        if ( *(uint32_t *)v21 != 0 )
          j__free(*(void **)v21);
        *(uint32_t *)v21 = 0;
        *((uint32_t *)v21 + 1) = 0;
        *((uint32_t *)v21 + 2) = 0;
        v21 += 24;
      }
      while ( v21 - 4 != v20 );
      v19 = v27;
    }
    j__free(v19);
  }
}


// ------------------------------------------------------------
// 0x482990 sub_482990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_482990(int *this, uint32_t *a2, int a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 44 != 0 )
    v6 = (a3 - v5) / 44;
  else
    v6 = 0;
  sub_482650(this, a3, 1u, a4);
  *a2 = *(this + 1) + 44 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x482A00 sub_482A00
// ------------------------------------------------------------
void /*thiscall*/ sub_482A00(int *this, int a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 44;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) / 44 )
  {
    v5 = *(this + 2);
    sub_481D40(v5, 1, a2);
    *(this + 2) = v5 + 44;
  }
  else
  {
    sub_482990(this, &a2, *(this + 2), a2);
  }
}



// ------------------------------------------------------------
// 0x482A90 sub_482A90
// ------------------------------------------------------------
int /*thiscall*/ sub_482A90(uint32_t *this, const char *ArgList, int a3)
{
  uint32_t *v3; // ebx
  unsigned int v4; // edi
  int v5; // edx
  unsigned int v6; // esi
  int v7; // edx
  unsigned int v8; // esi
  int v9; // ebx
  unsigned int v10; // esi
  int v11; // ebx
  char *v12; // esi
  int v13; // edx
  unsigned int v14; // ecx
  int v15; // edx
  int v16; // ebx
  unsigned int v17; // esi
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int i; // esi
  int v22; // eax
  int v23; // ebx
  int v24; // edx
  int j; // esi
  int v26; // eax
  int v27; // ebx
  int v28; // edx
  int k; // esi
  int v30; // eax
  int v31; // ebx
  int v32; // edx
  int v33; // edi
  char *v34; // ebx
  unsigned int v35; // esi
  int v36; // edi
  char *v37; // edi
  int v38; // esi
  uint32_t *v39; // edi
  int v40; // eax
  char *v41; // edi
  int v42; // eax
  int v43; // esi
  char v44; // bl
  uint32_t *v45; // eax
  uint32_t *v46; // edx
  uint32_t *v47; // ecx
  bool v48; // zf
  uint32_t *v49; // ecx
  bool v50; // dl
  bool v51; // zf
  int v52; // esi
  uint32_t *v53; // eax
  uint32_t *v54; // edx
  uint32_t *v55; // ecx
  bool v56; // zf
  uint32_t *v57; // ecx
  bool v58; // dl
  bool v59; // zf
  unsigned int v60; // edx
  int v61; // eax
  unsigned int v62; // edx
  int v63; // eax
  int v64; // edi
  unsigned int v65; // esi
  int v66; // edi
  char *v67; // ecx
  int v68; // edx
  char *v69; // esi
  int v70; // edx
  unsigned int v71; // eax
  unsigned int v72; // ecx
  int v73; // esi
  int v74; // eax
  int v75; // ebx
  int v76; // edx
  char *v77; // ecx
  unsigned int v78; // ebx
  unsigned int v79; // esi
  int v80; // edi
  int v81; // ecx
  int v82; // edx
  int v83; // edi
  int v84; // esi
  int v85; // edx
  char v86; // al
  int v87; // edx
  int v88; // eax
  float v90; // [esp+0h] [ebp-194h] BYREF
  float v91; // [esp+4h] [ebp-190h]
  int v92; // [esp+8h] [ebp-18Ch]
  int v93; // [esp+Ch] [ebp-188h]
  int v94; // [esp+1Ch] [ebp-178h] BYREF
  char v95[4]; // [esp+20h] [ebp-174h] BYREF
  char v96[4]; // [esp+24h] [ebp-170h] BYREF
  char v97[4]; // [esp+28h] [ebp-16Ch] BYREF
  int v98; // [esp+2Ch] [ebp-168h]
  int v99; // [esp+34h] [ebp-160h]
  int v100; // [esp+38h] [ebp-15Ch]
  int v101; // [esp+40h] [ebp-154h]
  int v102; // [esp+44h] [ebp-150h]
  int v103; // [esp+4Ch] [ebp-148h]
  int v104; // [esp+50h] [ebp-144h]
  int v105; // [esp+5Ch] [ebp-138h]
  int v106; // [esp+60h] [ebp-134h]
  int v107; // [esp+68h] [ebp-12Ch]
  int v108; // [esp+6Ch] [ebp-128h]
  float v109[14]; // [esp+70h] [ebp-124h]
  char v110[16]; // [esp+A8h] [ebp-ECh] BYREF
  int v111; // [esp+B8h] [ebp-DCh]
  int v112; // [esp+BCh] [ebp-D8h]
  int v113; // [esp+C4h] [ebp-D0h]
  int v114; // [esp+C8h] [ebp-CCh]
  char v115; // [esp+D0h] [ebp-C4h]
  uint32_t v116[4]; // [esp+D4h] [ebp-C0h] BYREF
  char v117[4]; // [esp+E4h] [ebp-B0h] BYREF
  int v118; // [esp+E8h] [ebp-ACh]
  int v119; // [esp+ECh] [ebp-A8h]
  char v120[8]; // [esp+110h] [ebp-84h] BYREF
  int v121; // [esp+118h] [ebp-7Ch]
  int v122; // [esp+11Ch] [ebp-78h]
  char v123[4]; // [esp+124h] [ebp-70h] BYREF
  int v124; // [esp+128h] [ebp-6Ch]
  int v125; // [esp+12Ch] [ebp-68h]
  char v126[16]; // [esp+134h] [ebp-60h] BYREF
  int v127; // [esp+144h] [ebp-50h]
  int v128; // [esp+148h] [ebp-4Ch]
  uint8_t v129[20]; // [esp+14Ch] [ebp-48h] BYREF
  int v130; // [esp+160h] [ebp-34h]
  int v131; // [esp+164h] [ebp-30h]
  int v132; // [esp+168h] [ebp-2Ch]
  int n; // [esp+16Ch] [ebp-28h]
  float *v134; // [esp+170h] [ebp-24h]
  uint32_t v135[3]; // [esp+176h] [ebp-1Eh] BYREF
  char *v136; // [esp+184h] [ebp-10h]
  int v137; // [esp+190h] [ebp-4h]
  int ArgLista; // [esp+19Ch] [ebp+8h]
  const char *ArgListb; // [esp+19Ch] [ebp+8h]
  char *ArgListc; // [esp+19Ch] [ebp+8h]
  char *ArgListd; // [esp+19Ch] [ebp+8h]
  unsigned int ArgListe; // [esp+19Ch] [ebp+8h]
  int v143; // [esp+1A0h] [ebp+Ch]
  int v144; // [esp+1A0h] [ebp+Ch]
  int v145; // [esp+1A0h] [ebp+Ch]
  int v146; // [esp+1A0h] [ebp+Ch]
  int v147; // [esp+1A0h] [ebp+Ch]
  int v148; // [esp+1A0h] [ebp+Ch]
  int v149; // [esp+1A0h] [ebp+Ch]
  int m; // [esp+1A0h] [ebp+Ch]

  v3 = this;
  v136 = (char *)this;
  sub_481720((int)&v94);
  v137 = 0;
  if ( sub_502F00((int)&v94, ArgList, a3) == 0 )
  {
    off_77F3FC("SKILL CREATE FAIL! FILENAME[%s]", ArgList);
    goto LABEL_139;
  }
  sub_41A590((unsigned int)(v3 + 1), v94, v94);
  sub_41B0D0(v95);
  sub_41B0D0(v96);
  sub_41B0D0(v97);
  v4 = (unsigned int)(v3 + 8);
  sub_41A590((unsigned int)(v3 + 8), v5, v98);
  if ( v99 != 0 )
  {
    ArgLista = (v100 - v99) >> 2;
    if ( ArgLista != 0 )
    {
      sub_41A630((unsigned int)&v90);
      sub_4807B0(ArgLista, (char)&clong::`vftable', LODWORD(v91), v92, v93);
      v6 = 0;
      ArgListb = nullptr;
      while ( v99 != 0 && (v100 - v99) >> 2 > v6 )
      {
        if ( v3[13] == 0 || (v3[14] - v3[13]) / 14 <= v6 )
          sub_47F920(v3 + 12);
        sub_41A590((unsigned int)&ArgListb[v3[13]], *(uint32_t *)(v99 + 4 * v6), *(uint32_t *)(v99 + 4 * v6));
        ++v6;
        ArgListb += 14;
      }
    }
  }
  sub_41A590((unsigned int)(v3 + 16), v101, v101);
  sub_41A590((unsigned int)v3 + 78, v7, v102);
  if ( v103 != 0 )
  {
    v143 = (v104 - v103) >> 2;
    if ( v143 != 0 )
    {
      sub_41A630((unsigned int)&v90);
      ArgListc = (char *)(v3 + 23);
      sub_4807B0(v143, (char)&clong::`vftable', LODWORD(v91), v92, v93);
      v8 = 0;
      v144 = 0;
      while ( v103 != 0 && (v104 - v103) >> 2 > v8 )
      {
        v9 = *((uint32_t *)ArgListc + 1);
        if ( v9 == 0 || (*((uint32_t *)ArgListc + 2) - v9) / 14 <= v8 )
          sub_47F920(ArgListc);
        sub_41A590(v9 + v144, v103, *(uint32_t *)(v103 + 4 * v8));
        v3 = v136;
        ++v8;
        v144 += 14;
      }
    }
  }
  if ( v105 != 0 )
  {
    v145 = (v106 - v105) >> 2;
    if ( v145 != 0 )
    {
      sub_41A630((unsigned int)&v90);
      ArgListd = (char *)(v3 + 27);
      sub_4807B0(v145, (char)&clong::`vftable', LODWORD(v91), v92, v93);
      v10 = 0;
      v146 = 0;
      while ( v105 != 0 && (v106 - v105) >> 2 > v10 )
      {
        v11 = *((uint32_t *)ArgListd + 1);
        if ( v11 == 0 || (*((uint32_t *)ArgListd + 2) - v11) / 14 <= v10 )
          sub_47F920(ArgListd);
        sub_41A590(v11 + v146, v105, *(uint32_t *)(v105 + 4 * v10++));
        v146 += 14;
      }
    }
  }
  v12 = v136;
  v13 = v107;
  v93 = v108;
  v14 = (unsigned int)(v136 + 128);
  *((uint32_t *)v136 + 31) = v107;
  sub_41A590(v14, v13, v93);
  v16 = 0;
  v17 = (unsigned int)(v12 + 212);
  do
  {
    sub_41A590(v17 - 70, v15, LODWORD(v109[v16]));
    sub_41A590(v17, v18, LODWORD(v109[v16 + 5]));
    v147 = sub_41A5E0(v17);
    if ( v147 > sub_41A5E0((unsigned int)(v136 + 282)) )
    {
      v19 = sub_41A5E0(v17);
      sub_41A590((unsigned int)(v136 + 282), v20, v19);
    }
    ++v16;
    v17 += 14;
  }
  while ( v16 < 5 );
  for ( i = 1; i <= sub_41A5E0(v4); ++i )
  {
    v22 = sub_41A5E0(v4);
    v23 = (uint64_t)sub_4049C0(v109[10], v109[11], i - 1, v22 - 1);
    sub_41A630((unsigned int)v135);
    LOBYTE(v137) = 1;
    v135[0] = &clong::`vftable';
    sub_41A590((unsigned int)v135, v24, v23);
    LOBYTE(v137) = 2;
    sub_480B10(v135);
    LOBYTE(v137) = 0;
    sub_41A580(v135);
  }
  for ( j = 1; j <= sub_41A5E0(v4); ++j )
  {
    v26 = sub_41A5E0(v4);
    v91 = (float)SLODWORD(v109[13]);
    v90 = (float)SLODWORD(v109[12]);
    v27 = (uint64_t)sub_4049C0(v90, v91, j - 1, v26 - 1);
    sub_41A630((unsigned int)v135);
    LOBYTE(v137) = 3;
    v135[0] = &clong::`vftable';
    sub_41A590((unsigned int)v135, v28, v27);
    LOBYTE(v137) = 4;
    sub_480B10(v135);
    LOBYTE(v137) = 0;
    sub_41A580(v135);
  }
  sub_4804A0(v110);
  for ( k = 1; k <= sub_41A5E0(v4); ++k )
  {
    v30 = sub_41A5E0(v4);
    v91 = (float)v112;
    v90 = (float)v111;
    v31 = (uint64_t)sub_4049C0(v90, v91, k - 1, v30 - 1);
    sub_41A630((unsigned int)v135);
    LOBYTE(v137) = 5;
    v135[0] = &clong::`vftable';
    sub_41A590((unsigned int)v135, v32, v31);
    LOBYTE(v137) = 6;
    sub_480B10(v135);
    LOBYTE(v137) = 0;
    sub_41A580(v135);
  }
  if ( v113 != 0 )
  {
    v33 = (v114 - v113) >> 2;
    if ( v33 != 0 )
    {
      sub_41A630((unsigned int)&v90);
      v34 = v136 + 360;
      sub_4807B0(v33, (char)&clong::`vftable', LODWORD(v91), v92, v93);
      v35 = 0;
      v148 = 0;
      while ( v113 != 0 && (v114 - v113) >> 2 > v35 )
      {
        v36 = *((uint32_t *)v34 + 1);
        if ( v36 == 0 || (*((uint32_t *)v34 + 2) - v36) / 14 <= v35 )
        {
LABEL_105:
          v67 = v34;
LABEL_106:
          sub_47F920(v67);
        }
        sub_41A590(v36 + v148, v113, *(uint32_t *)(v113 + 4 * v35++));
        v148 += 14;
      }
    }
  }
  v37 = v136;
  v136[376] = v115;
  v38 = 0;
  v39 = v37 + 380;
  do
  {
    v40 = sub_41ACF0(&v116[v38]);
    v93 = v116[v38 + 2];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v40);
    *v39 = sub_418DD0(v93);
    ++v38;
    ++v39;
  }
  while ( v38 < 2 );
  if ( v118 != 0 && (v119 - v118) / 24 != 0 )
  {
    v41 = v136;
    sub_482A00(v117);
    v42 = *((uint32_t *)v41 + 98);
    v43 = *(uint32_t *)(v42 + 4);
    v44 = 0;
    if ( v43 != *(uint32_t *)(v42 + 8) )
    {
      do
      {
        if ( v44 != 0 )
          goto LABEL_79;
        v45 = *(uint32_t **)(v43 + 4);
        v46 = *(uint32_t **)(v43 + 8);
        v47 = v45;
        v48 = v45 == v46;
        if ( v45 != v46 )
        {
          do
          {
            if ( *v47 == 2 )
              break;
            ++v47;
          }
          while ( v47 != v46 );
          v48 = v47 == v46;
        }
        v49 = *(uint32_t **)(v43 + 8);
        v50 = !v48;
        v51 = v45 == v49;
        if ( v45 != v49 )
        {
          do
          {
            if ( *v45 == 3 )
              break;
            ++v45;
          }
          while ( v45 != v49 );
          v51 = v45 == v49;
        }
        if ( v50 )
        {
          if ( v51 )
          {
LABEL_78:
            v44 = 1;
LABEL_79:
            v60 = 0;
            while ( 1 )
            {
              v61 = *(uint32_t *)(v43 + 4);
              if ( v61 == 0 || v60 >= (*(uint32_t *)(v43 + 8) - v61) >> 2 )
                break;
              if ( *(uint32_t *)(v61 + 4 * v60) == 2 )
              {
                *(uint32_t *)(v61 + 4 * v60++) = 3;
              }
              else
              {
                if ( *(uint32_t *)(v61 + 4 * v60) == 3 )
                  *(uint32_t *)(v61 + 4 * v60) = 2;
                ++v60;
              }
            }
          }
        }
        else if ( !v51 )
        {
          goto LABEL_78;
        }
        v43 += 24;
      }
      while ( v43 != *(uint32_t *)(*((uint32_t *)v41 + 98) + 8) );
    }
    v52 = *((uint32_t *)v41 + 98);
    if ( v44 != 0 )
      goto LABEL_88;
    v53 = *(uint32_t **)(v52 + 20);
    v54 = *(uint32_t **)(v52 + 24);
    v55 = v53;
    v56 = v53 == v54;
    if ( v53 != v54 )
    {
      do
      {
        if ( *v55 == 2 )
          break;
        ++v55;
      }
      while ( v55 != v54 );
      v56 = v55 == v54;
    }
    v57 = *(uint32_t **)(v52 + 24);
    v58 = !v56;
    v59 = v53 == v57;
    if ( v53 != v57 )
    {
      do
      {
        if ( *v53 == 3 )
          break;
        ++v53;
      }
      while ( v53 != v57 );
      v59 = v53 == v57;
    }
    if ( v58 )
    {
      if ( v59 )
        goto LABEL_88;
    }
    else if ( !v59 )
    {
LABEL_88:
      v62 = 0;
      while ( 1 )
      {
        v63 = *(uint32_t *)(v52 + 20);
        if ( v63 == 0 || v62 >= (*(uint32_t *)(v52 + 24) - v63) >> 2 )
          break;
        if ( *(uint32_t *)(v63 + 4 * v62) == 2 )
        {
          *(uint32_t *)(v63 + 4 * v62++) = 3;
        }
        else
        {
          if ( *(uint32_t *)(v63 + 4 * v62) == 3 )
            *(uint32_t *)(v63 + 4 * v62) = 2;
          ++v62;
        }
      }
      sub_482650(*((uint32_t *)v41 + 98), 1, v117);
    }
  }
  sub_41B0D0(v120);
  if ( v121 != 0 )
  {
    v64 = (v122 - v121) >> 2;
    if ( v64 != 0 )
    {
      sub_41A630((unsigned int)&v90);
      v34 = v136 + 408;
      sub_4807B0(v64, (char)&clong::`vftable', LODWORD(v91), v92, v93);
      v65 = 0;
      v149 = 0;
      while ( v121 != 0 && (v122 - v121) >> 2 > v65 )
      {
        v66 = *((uint32_t *)v34 + 1);
        if ( v66 == 0 || (*((uint32_t *)v34 + 2) - v66) / 14 <= v65 )
          goto LABEL_105;
        sub_41A590(v66 + v149, v149, *(uint32_t *)(v121 + 4 * v65++));
        v149 += 14;
      }
    }
  }
  if ( v124 != 0 && (v68 = (v125 - v124) >> 4) != 0 )
  {
    v69 = v136;
    sub_481260(v68, SLOBYTE(v90), 0, 0, 0);
    v70 = v124;
    v71 = 0;
    ArgListe = 0;
    for ( m = 0; v70 != 0; m += 16 )
    {
      v72 = (v125 - v70) >> 4;
      if ( v72 <= v71 )
        break;
      v73 = *(uint32_t *)(v70 + m + 4);
      if ( v73 != 0 && (*(uint32_t *)(v70 + m + 8) - v73) >> 2 != 0 )
      {
        if ( v72 > ArgListe )
        {
          v74 = *(uint32_t *)(v70 + m + 4);
          if ( v74 != 0 )
            v75 = (*(uint32_t *)(v70 + m + 8) - v74) >> 2;
          else
            v75 = 0;
          v76 = *((uint32_t *)v136 + 107);
          v77 = v136 + 424;
          if ( v76 == 0 || (*((uint32_t *)v136 + 108) - v76) >> 4 <= ArgListe )
LABEL_136:
            sub_47F920(v77);
          v134 = &v90;
          sub_41A630((unsigned int)&v90);
          sub_4807B0(v75, (char)&clong::`vftable', LODWORD(v91), v92, v93);
          v78 = 0;
          for ( n = 0; ; n = v84 + 14 )
          {
            v70 = v124;
            if ( v124 == 0 )
              break;
            v79 = (v125 - v124) >> 4;
            if ( v79 <= ArgListe )
              break;
            v80 = *(uint32_t *)(m + v124 + 4);
            v81 = v124 + m;
            if ( v80 == 0 || v78 >= (*(uint32_t *)(v81 + 8) - v80) >> 2 )
              goto LABEL_133;
            if ( v79 <= ArgListe )
              break;
            v134 = *(float **)(v81 + 4);
            if ( v134 == nullptr || (*(uint32_t *)(v81 + 8) - (int)v134) >> 2 <= v78 )
              sub_454B50();
            v82 = *((uint32_t *)v136 + 107);
            v77 = v136 + 424;
            if ( v82 == 0 || (*((uint32_t *)v136 + 108) - v82) >> 4 <= ArgListe )
              goto LABEL_136;
            v83 = *(uint32_t *)(v82 + m + 4);
            v67 = (char *)(v82 + m);
            if ( v83 == 0 || (*((uint32_t *)v67 + 2) - v83) / 14 <= v78 )
              goto LABEL_106;
            v84 = n;
            sub_41A590(v83 + n, LODWORD(v134[v78]), LODWORD(v134[v78]));
            ++v78;
          }
        }
        sub_47F920(v123);
      }
LABEL_133:
      v69 = v136;
      v71 = ++ArgListe;
    }
  }
  else
  {
    v69 = v136;
  }
  sub_481A30(v126);
  v85 = v128;
  v86 = v129[16];
  *((uint32_t *)v69 + 114) = v127;
  *((uint32_t *)v69 + 121) = v130;
  *((uint32_t *)v69 + 115) = v85;
  v87 = v131;
  v69[480] = v86;
  v88 = v132;
  v93 = (int)v129;
  *((uint32_t *)v69 + 122) = v87;
  *((uint32_t *)v69 + 123) = v88;
  sub_4ED3F0((int)(v69 + 464), v93);
  v93 = 1500;
  v92 = 0;
  v69[601] = 0;
  v69[602] = 0;
  sub_698F90((int)(v69 + 588), v92, v93);
LABEL_139:
  v137 = -1;
  return sub_481860(&v94);
}


// ------------------------------------------------------------
// 0x4835D0 sub_4835D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4835D0(int this, const char *ArgList, int a3)
{
  *(uint32_t *)this = &CNRDSkill::`vftable';
  sub_482240((char *)(this + 4));
  `eh vector constructor iterator'((void *)(this + 496), 0xEu, 2, (void (/*thiscall*/ *)(void *))sub_401040, sub_432D10);
  sub_41A630(this + 524);
  *(uint32_t *)(this + 524) = &cfloat::`vftable';
  sub_41A630(this + 544);
  *(uint32_t *)(this + 544) = &clong::`vftable';
  sub_41A630(this + 558);
  *(uint32_t *)(this + 558) = &clong::`vftable';
  sub_41A630(this + 572);
  *(uint32_t *)(this + 572) = &clong::`vftable';
  *(uint8_t *)(this + 592) = 0;
  *(uint32_t *)(this + 588) = &off_6C2B88;
  *(uint32_t *)(this + 596) = 0;
  *(uint8_t *)(this + 600) = 1;
  *(uint8_t *)(this + 602) = 0;
  *(uint8_t *)(this + 601) = 0;
  *(uint32_t *)(this + 612) = 0;
  *(uint32_t *)(this + 608) = 0;
  *(uint32_t *)(this + 604) = 0;
  sub_41A630(this + 616);
  *(uint32_t *)(this + 616) = &clong::`vftable';
  sub_41A630(this + 630);
  *(uint32_t *)(this + 630) = &clong::`vftable';
  sub_47DC00((uint32_t *)this);
  sub_482A90((char *)this, ArgList, a3);
  return this;
}



// ------------------------------------------------------------
// 0x483720 sub_483720
// ------------------------------------------------------------
int /*fastcall*/ sub_483720(int a1, int a2)
{
  int v3; // edx

  sub_41A590(a1 + 616, a2, 0);
  return sub_41A590(a1 + 630, v3, 0);
}



// ------------------------------------------------------------
// 0x483740 sub_483740
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_483740(void *this)
{
  int v1; // esi

  v1 = sub_41A5E0((unsigned int)this + 630);
  return v1 - sub_699000((int)&unk_99FC80) > 0;
}



// ------------------------------------------------------------
// 0x483770 sub_483770
// ------------------------------------------------------------
void */*thiscall*/ sub_483770(void *Block, char a2)
{
  sub_4837A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4837A0 sub_4837A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4837A0(uint32_t *this)
{
  *this = &CNRDSkill::`vftable';
  sub_41A580((uint32_t *)((char *)this + 630));
  sub_41A580(this + 154);
  *(this + 147) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 592) = 0;
  sub_41A580(this + 143);
  sub_41A580((uint32_t *)((char *)this + 558));
  sub_41A580(this + 136);
  sub_41A580(this + 131);
  `eh vector destructor iterator'(this + 124, 0xEu, 2, sub_432D10);
  sub_482450((int)(this + 1));
}



// ------------------------------------------------------------
// 0x483870 sub_483870
// ------------------------------------------------------------
char sub_483870()
{
  unsigned int v0; // edi
  uint32_t *v1; // esi
  const char *i; // ebx
  void *v3; // eax
  int v4; // edx
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int **v10; // ecx
  int *k; // eax
  int *j; // eax
  uint32_t *v13; // esi
  uint8_t *v14; // eax
  int v15; // edi
  int v16; // ebx
  uint8_t *v17; // eax
  int v18; // edi
  uint8_t *v19; // eax
  int v20; // edi
  int v21; // ebx
  uint8_t *v22; // eax
  int v23; // edi
  int v24; // ebx
  void *Block; // [esp+Ch] [ebp-1Ch]
  void *Blocka; // [esp+Ch] [ebp-1Ch]
  void *v28; // [esp+10h] [ebp-18h]
  const char ***v29; // [esp+14h] [ebp-14h]
  int ArgList; // [esp+18h] [ebp-10h]

  v0 = 0;
  ArgList = 0;
  v29 = (const char ***)&unk_9B72D8;
  v1 = &unk_99FC30;
  do
  {
    sub_47FA50(50);
    for ( i = **v29; i != (const char *)*v29; v0 = 0 )
    {
      v3 = operator new(0x284u);
      if ( v3 != nullptr )
      {
        if ( *((uint32_t *)i + 10) < 0x10u )
          v28 = (void *)sub_4835D0((int)v3, i + 20, ArgList);
        else
          v28 = (void *)sub_4835D0((int)v3, *((const char **)i + 5), ArgList);
      }
      else
      {
        v28 = nullptr;
      }
      v4 = v1[1];
      v5 = *((uint32_t *)i + 3);
      Block = (void *)v5;
      if ( v4 == 0 || v5 >= (v1[2] - v4) >> 2 )
      {
        v6 = v1[1];
        if ( v6 != 0 )
          v0 = (v1[2] - v6) >> 2;
        sub_47FC70(v5 + 1, 0);
        while ( 1 )
        {
          v7 = v1[1];
          if ( v7 == 0 || v0 >= (v1[2] - v7) >> 2 )
            break;
          *(uint32_t *)(v7 + 4 * v0++) = 0;
        }
        v5 = (unsigned int)Block;
      }
      v8 = 4 * v5;
      if ( *(uint32_t *)(4 * v5 + v1[1]) != 0 )
      {
        off_77F3FC("SKILL LIST ERROR! JOB : %d, INDEX : %d", ArgList, v5);
        v9 = *(void (/*thiscall*/ ****)(uint32_t, int))(v8 + v1[1]);
        if ( v9 != nullptr )
          (**v9)(v9, 1);
      }
      *(uint32_t *)(v8 + v1[1]) = v28;
      if ( i[45] == 0 )
      {
        v10 = *((int ***)i + 2);
        if ( *((uint8_t *)v10 + 45) != 0 )
        {
          for ( j = *((int **)i + 1); *((uint8_t *)j + 45) == 0; j = (int *)j[1] )
          {
            if ( i != (const char *)j[2] )
              break;
            i = (const char *)j;
          }
          i = (const char *)j;
        }
        else
        {
          for ( k = *v10; *((uint8_t *)k + 45) == 0; k = (int *)*k )
            v10 = (int **)k;
          i = (const char *)v10;
        }
      }
    }
    v1 += 4;
    ++ArgList;
    v29 += 3;
  }
  while ( (int)v1 < (int)&dword_99FC70 );
  v13 = *(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  dword_99FC08 = sub_418DD0(v13, 0x53u);
  dword_99FC0C = sub_418DD0(v13, 0x3Cu);
  dword_99FC10 = sub_418DD0(v13, 0x47u);
  dword_99FC14 = sub_418DD0(v13, 0x6Bu);
  v14 = operator new(0x2Cu);
  v15 = (int)v14;
  if ( v14 != nullptr )
  {
    v16 = dword_79C0B0;
    v14[4] = 0;
    *(uint32_t *)v14 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v14);
    sub_699E40(v16, v13, 83, 3);
  }
  else
  {
    v15 = 0;
  }
  dword_99FC18 = v15;
  v17 = operator new(0x2Cu);
  v18 = (int)v17;
  if ( v17 != nullptr )
  {
    Blocka = (void *)dword_79C0B0;
    v17[4] = 0;
    *(uint32_t *)v17 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v17);
    sub_699E40(Blocka, v13, 60, 3);
  }
  else
  {
    v18 = 0;
  }
  dword_99FC1C = v18;
  v19 = operator new(0x2Cu);
  v20 = (int)v19;
  if ( v19 != nullptr )
  {
    v21 = dword_79C0B0;
    v19[4] = 0;
    *(uint32_t *)v19 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v19);
    sub_699E40(v21, v13, 71, 3);
  }
  else
  {
    v20 = 0;
  }
  dword_99FC20 = v20;
  v22 = operator new(0x2Cu);
  v23 = (int)v22;
  if ( v22 != nullptr )
  {
    v24 = dword_79C0B0;
    v22[4] = 0;
    *(uint32_t *)v22 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v22);
    sub_699E40(v24, v13, 107, 3);
  }
  else
  {
    v23 = 0;
  }
  dword_99FC24 = v23;
  dword_99FC28 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 12), 0x9Cu);
  *(uint32_t *)(dword_99FC18 + 36) = 2;
  *(uint32_t *)(dword_99FC18 + 40) = -1;
  *(uint32_t *)(dword_99FC1C + 36) = 2;
  *(uint32_t *)(dword_99FC1C + 40) = -1;
  *(uint32_t *)(dword_99FC20 + 36) = 2;
  *(uint32_t *)(dword_99FC20 + 40) = -1;
  *(uint32_t *)(dword_99FC24 + 36) = 2;
  *(uint32_t *)(dword_99FC24 + 40) = -1;
  byte_99FC8D = 0;
  byte_99FC8E = 0;
  sub_699070(1);
  return sub_698F90((int)&unk_99FC80, 0, 0);
}


// ------------------------------------------------------------
// 0x483C60 sub_483C60
// ------------------------------------------------------------
char /*thiscall*/ sub_483C60(uint32_t *this, int a2)
{
  int i; // eax
  char result; // al

  *this = a2;
  *(this + 1) = operator new(4 * a2);
  for ( i = 0; i < a2; ++i )
    *(uint32_t *)(*(this + 1) + 4 * i) = 0;
  result = byte_99FCAA;
  if ( byte_99FCAA == 0 )
  {
    dword_99FC9C = 0;
    dword_99FCA4 = 0;
    word_99FCA0 = 0;
    word_99FCA8 = 0;
    byte_99FCAA = 1;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483CD0 sub_483CD0
// ------------------------------------------------------------
void /*thiscall*/ sub_483CD0(void **this)
{
  if ( *(this + 1) != nullptr )
    j_j__free(*(this + 1));
  *(this + 1) = nullptr;
}



// ------------------------------------------------------------
// 0x483CF0 sub_483CF0
// ------------------------------------------------------------
int sub_483CF0()
{
  char v0; // bl
  int v1; // esi
  char *v2; // edi
  int result; // eax

  v0 = 0;
  v1 = 0;
  v2 = (char *)&unk_77FCD8;
  do
  {
    result = sub_4BF250(v2);
    if ( *((uint8_t *)&dword_99FCA4 + v1) != 0 || (uint8_t)result == 0 || v0 != 0 )
    {
      *((uint8_t *)&dword_99FC9C + v1) = 0;
    }
    else
    {
      *((uint8_t *)&dword_99FC9C + v1) = 1;
      v0 = 1;
    }
    *((uint8_t *)&dword_99FCA4 + v1) = result;
    v2 += 8;
    ++v1;
  }
  while ( (int)v2 < (int)byte_77FD08 );
  return result;
}



// ------------------------------------------------------------
// 0x483D50 sub_483D50
// ------------------------------------------------------------
char /*thiscall*/ sub_483D50(uint32_t *this, int a2, int a3)
{
  int v5; // ecx

  if ( a2 >= *this )
    return 0;
  v5 = *(uint32_t *)(*(this + 1) + 4 * a2);
  if ( v5 != a3 )
  {
    if ( v5 != 0 )
      sub_47ECE0();
    if ( a3 != 0 )
      sub_47E3E0(a3);
  }
  *(uint32_t *)(*(this + 1) + 4 * a2) = a3;
  return 1;
}



// ------------------------------------------------------------
// 0x483DA0 sub_483DA0
// ------------------------------------------------------------
char /*thiscall*/ sub_483DA0(int *this, int a2, int a3)
{
  int v3; // eax
  int v5; // eax
  int v6; // edi

  v3 = *(this + 2);
  if ( v3 <= 0 )
    return 0;
  *(this + 2) = v3 - 1;
  if ( a2 >= *this || a3 >= *this )
    return 0;
  v5 = *(this + 1);
  v6 = *(uint32_t *)(v5 + 4 * a2);
  *(uint32_t *)(v5 + 4 * a2) = *(uint32_t *)(v5 + 4 * a3);
  *(uint32_t *)(*(this + 1) + 4 * a3) = v6;
  return 1;
}



// ------------------------------------------------------------
// 0x483DF0 sub_483DF0
// ------------------------------------------------------------
int /*thiscall*/ sub_483DF0(int *this, char a2)
{
  int result; // eax
  int i; // esi

  result = *this;
  for ( i = 0; i < *this; ++i )
  {
    if ( *(uint32_t *)(*(this + 1) + 4 * i) != 0 )
      sub_47E440(a2);
    result = *this;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483E30 sub_483E30
// ------------------------------------------------------------
int /*thiscall*/ sub_483E30(int *this)
{
  int result; // eax
  int i; // esi

  result = *this;
  for ( i = 0; i < *this; ++i )
  {
    if ( *(uint32_t *)(*(this + 1) + 4 * i) != 0 )
      sub_47ECE0();
    *(uint32_t *)(*(this + 1) + 4 * i) = 0;
    result = *this;
  }
  return result;
}



// ------------------------------------------------------------
// 0x483E70 sub_483E70
// ------------------------------------------------------------
char /*thiscall*/ sub_483E70(int *this, int a2, int a3, int a4)
{
  int v6; // eax
  int v7; // eax

  if ( *(this + 2) >= a4 )
    return 0;
  if ( a2 >= *this )
    return 0;
  if ( a3 >= *this )
    return 0;
  if ( a2 < 6 )
  {
    v6 = *(uint32_t *)(*(this + 1) + 4 * a3);
    if ( v6 != 0 && *(uint32_t *)(v6 + 124) != 0 )
      return 0;
  }
  if ( a3 < 6 )
  {
    v7 = *(uint32_t *)(*(this + 1) + 4 * a2);
    if ( v7 != 0 && *(uint32_t *)(v7 + 124) != 0 )
      return 0;
  }
  sub_423200(dword_8F7B08, 30);
  HIBYTE(a4) = a2;
  sub_423290((char *)&a4 + 3, 1);
  HIBYTE(a4) = a3;
  sub_423290((char *)&a4 + 3, 1);
  sub_423380(dword_8F7B08);
  ++*(this + 2);
  if ( byte_77F280 != 0 )
    sub_483DA0(this, a2, a3);
  return 1;
}



// ------------------------------------------------------------
// 0x483F40 sub_483F40
// ------------------------------------------------------------
char /*thiscall*/ sub_483F40(int *this, int a2, int a3, int a4)
{
  char result; // al

  result = sub_483E70(this, a2, a3, 1);
  if ( result != 0 )
    return sub_483E70(this, a3, a4, 2) != 0;
  return result;
}



// ------------------------------------------------------------
// 0x483F80 sub_483F80
// ------------------------------------------------------------
void /*noreturn*/ sub_483F80()
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
// 0x483FF0 sub_483FF0
// ------------------------------------------------------------
void /*thiscall*/ sub_483FF0(int this, int a2, unsigned int a3, int a4)
{
  void *v4; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // edx
  int v10; // edx
  unsigned int v11; // eax
  int v12; // edx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-40h]
  int v25; // [esp-Ch] [ebp-34h]
  unsigned int v26; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v4 = *(void **)(a4 + 4);
  v28[0] = *(void **)a4;
  v6 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v9 = 0;
    if ( 0x1FFFFFFF - v9 < a3 )
      sub_483F80(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, a2 + v21);
        v26 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, v22 - v30, v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, a2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 3;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 3;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v31 = 8 * v11;
      v14 = (char *)operator new(8 * v11);
      v24 = *(uint32_t *)(this + 4);
      v28[2] = v14;
      v29 = 0;
      v32 = sub_44BD30(v24, a2, v14);
      sub_63A7C0(v32, a3, v28);
      sub_44BD30(a2, *(uint32_t *)(this + 8), v32 + 8 * a3);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 3;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v31];
      *(uint32_t *)(this + 8) = &v14[8 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x484240 sub_484240
// ------------------------------------------------------------
void /*thiscall*/ sub_484240(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) >> 3 )
  {
    v5 = *(this + 2);
    sub_63A7C0(v5, 1, a2);
    *(this + 2) = v5 + 8;
  }
  else
  {
    sub_483FF0((int)this, (uint32_t *)*(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x4842B0 sub_4842B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4842B0(int *this, int a2, void **a3)
{
  int v4; // edi
  int v5; // eax
  int v7; // esi
  void **v8; // ebx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  int v12; // edx
  void ***v13; // esi
  void ***v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  void **v20; // esi
  int v21; // [esp+Ch] [ebp-4h] BYREF
  int v22; // [esp+18h] [ebp+8h]

  v4 = 0;
  if ( *this <= 0 )
    return -1;
  while ( 1 )
  {
    v5 = *(uint32_t *)(*(this + 1) + 4 * v4);
    if ( v5 != 0 && sub_41A5E0(v5 + 4) == a2 )
      break;
    if ( ++v4 >= *this )
      return -1;
  }
  v7 = *(uint32_t *)(*(this + 1) + 4 * v4);
  if ( v7 == 0 || sub_41A5E0(v7 + 544) == 0 )
    return -1;
  v22 = sub_47E340(v7);
  if ( v22 != -1 )
  {
    v8 = a3;
    if ( a3 != nullptr )
    {
      if ( a3[1] != nullptr )
        j__free(a3[1]);
      v8[1] = nullptr;
      v8[2] = nullptr;
      v8[3] = nullptr;
      v9 = *(uint32_t *)(v7 + 392);
      if ( v22 == 0 )
        v9 += 44;
      v10 = *(uint32_t *)(v9 + 4);
      if ( v10 != 0 )
        v11 = (*(uint32_t *)(v9 + 8) - v10) / 24;
      else
        v11 = 0;
      v12 = 3 * v11;
      v13 = *(void ****)(v10 + 24 * v11 - 20);
      v14 = *(void ****)(v10 + 24 * v11 - 16);
      v15 = v10 + 8 * v12 - 24;
      if ( v13 != v14 )
      {
        do
        {
          a3 = *v13;
          sub_437140(&v21, &a3);
          if ( v21 == dword_8F857C )
            v16 = 0;
          else
            v16 = v21 + 16;
          sub_484240(v8, v16);
          ++v13;
        }
        while ( v13 != *(void ****)(v15 + 8) );
      }
    }
    return v22;
  }
  if ( v4 >= 6 || *((uint8_t *)&dword_99FC9C + v4) == 0 )
    return -1;
  v17 = *(uint32_t *)(v7 + 392);
  if ( v17 != 0 && (*(uint32_t *)(v7 + 396) - v17) / 44 == 2 && dword_8F7C04 != 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1132))(dword_8F7C04, 0);
    if ( v18 == 4 )
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04);
    else
      v19 = v18;
  }
  else
  {
    v19 = 4;
  }
  v20 = a3;
  if ( a3 != nullptr )
  {
    sub_5E5260(a3);
    if ( *((uint8_t *)&dword_99FC9C + v4) != 0 )
      sub_484240(v20, 8 * v4 + 7863512);
  }
  return v19;
}



// ------------------------------------------------------------
// 0x484470 sub_484470
// ------------------------------------------------------------
char /*thiscall*/ sub_484470(uint8_t *this)
{
  int v1; // ecx

  *(this + 64) = 1;
  v1 = (int)(this + 52);
  *(uint8_t *)(v1 + 13) = 0;
  *(uint8_t *)(v1 + 14) = 0;
  return sub_698F90(v1, 0, 0);
}



// ------------------------------------------------------------
// 0x484490 sub_484490
// ------------------------------------------------------------
int /*thiscall*/ sub_484490(int this)
{
  *(uint16_t *)(this + 4) = -1;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 20) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4844B0 sub_4844B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4844B0(int *this)
{
  int *v1; // esi
  int i; // edi
  int v3; // ecx
  int result; // eax

  *((uint16_t *)this + 2) = -1;
  v1 = this + 4;
  for ( i = 2; i != 0; --i )
  {
    v3 = *v1;
    *(v1 - 2) = 0;
    result = sub_485020(v3);
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4844E0 sub_4844E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4844E0(uint16_t *this, char a2)
{
  char result; // al
  uint32_t *v3; // esi
  const char *v4; // eax
  int v5; // [esp+10h] [ebp-4Ch]
  bool v6[4]; // [esp+14h] [ebp-48h] BYREF
  char Buffer[64]; // [esp+18h] [ebp-44h] BYREF
  int v8; // [esp+58h] [ebp-4h]

  result = dword_796E50;
  v3 = this;
  LOWORD(this) = *(this + 2);
  v8 = dword_796E50;
  if ( (uint16_t)this != 0xFFFF )
  {
    result = a2;
    if ( (a2 != 0) != v3[2] )
    {
      if ( a2 != 0
        && *(int *)(v3[4] + 4) > 0
        && (v5 = *(uint32_t *)(sub_429830(this) + 176) + *(uint32_t *)(v3[5] + 4) - *(uint32_t *)(v3[4] + 4)) < 0 )
      {
        v4 = (const char *)sub_422E70(419);
        sprintf(Buffer, v4, -((double)v5 * 0.001));
        return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
      }
      else
      {
        sub_423200(dword_8F7B08, 26);
        v6[0] = a2 != 0;
        sub_423290(v6, 1);
        sub_423380(dword_8F7B08);
        result = a2;
        if ( a2 != 0 )
        {
          sub_540960(*((uint32_t *)dword_8F8528 + 29));
          return sub_44AC80(dword_8F8528);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x484600 sub_484600
// ------------------------------------------------------------
int /*thiscall*/ sub_484600(uint16_t *this)
{
  int result; // eax
  uint16_t *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = this;
  if ( *(this + 2) != 0xFFFF )
  {
    sub_423200(dword_8F7B08, 26);
    LOBYTE(v2) = 2;
    sub_423290(&v2, 1);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x484640 sub_484640
// ------------------------------------------------------------
int /*thiscall*/ sub_484640(uint16_t *this, int a2)
{
  uint32_t *v2; // esi
  int v3; // eax
  int v5; // esi
  uint32_t *v6; // esi
  int v7; // eax

  if ( *(this + 2) == 0xFFFF )
  {
    sub_423200(dword_8F7B08, 10);
    sub_423290(&a2, 2);
    HIBYTE(a2) = 1;
    sub_423290((char *)&a2 + 3, 1);
    v5 = *((uint32_t *)dword_8F852C + 1);
    a2 = sub_484FA0() - v5;
    sub_423290(&a2, 4);
    sub_423380(dword_8F7B08);
    v6 = *((uint32_t **)dword_8F8528 + 7);
    v7 = sub_422E70(421);
    return sub_43BEE0(v6, v7, -6567706, 0, -1);
  }
  else
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);
    v3 = sub_422E70(420);
    return sub_43BEE0(v2, v3, -6567706, 0, -1);
  }
}



// ------------------------------------------------------------
// 0x484710 sub_484710
// ------------------------------------------------------------
char /*thiscall*/ sub_484710(uint32_t *this, int a2, int a3)
{
  *(this + a2 + 2) = a3;
  if ( a2 == 0 && a3 == 1 )
  {
    sub_540960(*((uint32_t *)dword_8F8528 + 29));
    sub_44AC80(dword_8F8528);
  }
  if ( *(this + 2) == 1 && *(this + 3) == 1 )
    return sub_44E8D0((char *)dword_8F8528, (void *)0x42, 0, 0);
  sub_44E850(dword_8F8528, 66);
  return sub_44E850(dword_8F8528, 27);
}



// ------------------------------------------------------------
// 0x484790 sub_484790
// ------------------------------------------------------------
int /*thiscall*/ sub_484790(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 5);
  if ( v1 != 0 )
    return (*(this + 6) - v1) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4847B0 sub_4847B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4847B0(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // ebx
  void *v3; // edi

  v1 = this + 4;
  for ( i = 2; i != 0; --i )
  {
    v3 = (void *)*v1;
    if ( *v1 != 0 )
    {
      sub_433E30(*v1);
      j__free(v3);
    }
    *v1++ = 0;
  }
}



// ------------------------------------------------------------
// 0x4847F0 sub_4847F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4847F0(uint32_t *this)
{
  uint32_t *v1; // ebx
  uint32_t *v2; // eax
  uint32_t *v3; // esi
  int result; // eax
  int v5; // [esp+10h] [ebp-10h]

  v1 = this + 4;
  v5 = 2;
  do
  {
    v2 = operator new(0x20u);
    v3 = v2;
    if ( v2 != nullptr )
    {
      v2[5] = 0;
      v2[6] = 0;
      v2[7] = 0;
      sub_484CA0(v2);
      sub_485E80((void *)4, 27);
    }
    else
    {
      v3 = nullptr;
    }
    *v1++ = v3;
    result = v5 - 1;
    v5 = result;
  }
  while ( result != 0 );
  return result;
}



// ------------------------------------------------------------
// 0x484880 sub_484880
// ------------------------------------------------------------
int /*thiscall*/ sub_484880(uint32_t *this, int a2)
{
  int v2; // edx
  uint32_t *v3; // ecx
  unsigned int v4; // esi
  int *v5; // eax
  int result; // eax

  v2 = *(this + 5);
  v3 = this + 4;
  if ( v2 != 0 )
    v4 = (v3[2] - v2) >> 2;
  else
    v4 = 0;
  if ( v2 == 0 || v4 >= (v3[3] - v2) >> 2 )
    return sub_430C80((void *)v3[2], 1, (int)&a2);
  v5 = (int *)v3[2];
  *v5 = a2;
  result = (int)(v5 + 1);
  v3[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4848E0 sub_4848E0
// ------------------------------------------------------------
char /*userpurge*/ sub_4848E0@<al>(int a1@<ecx>, int a2@<ebx>, unsigned int a3, int a4, unsigned int a5)
{
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v9; // edx
  int v10; // edi
  int v11; // esi
  unsigned int v12; // eax
  unsigned int v13; // ebx
  int i; // esi
  int v15; // eax
  unsigned int v16; // esi
  uint32_t *v17; // eax
  int v18; // [esp-Ch] [ebp-10h]

  if ( *(uint16_t *)(a1 + 4) == 0xFFFF )
    return 0;
  if ( *(uint32_t *)(a1 + 8) == 1 )
    return 0;
  v5 = *(uint32_t *)(a1 + 16);
  v6 = *(uint32_t *)(v5 + 20);
  v7 = v5 + 16;
  if ( v6 != 0 && (*(uint32_t *)(v7 + 8) - v6) >> 2 >= 1 )
    return 0;
  if ( a3 != 0 )
  {
    if ( a3 == 3 )
    {
      if ( a4 >= 18 || dword_8F7C04 == 0 )
        return 0;
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, a4);
      if ( v11 == 0 )
        return 0;
    }
    else
    {
      if ( a3 != 1 )
        return 0;
      v18 = a4;
      sub_432F00(1);
      v11 = sub_44A980(v18);
      if ( v11 == 0 )
        return 0;
    }
    v10 = a4;
    goto LABEL_21;
  }
  v9 = *((uint32_t *)dword_8F852C + 5);
  if ( v9 != 0 && (*((uint32_t *)dword_8F852C + 6) - v9) >> 2 >= 1 )
    return 0;
  v10 = a4;
  if ( a4 >= *((uint32_t *)dword_8F852C + 2) )
    return 0;
  v11 = sub_44A980(a4);
  if ( v11 == 0 )
    return 0;
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
  if ( v12 < a5 )
    return 0;
LABEL_21:
  v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 16))(v11, a2) + 4);
  if ( v13 > 2 )
  {
    for ( i = 3; i < 27; ++i )
    {
      if ( sub_44A980(i) == 0 )
        break;
      v15 = sub_44A980(i);
      if ( (*(uint8_t (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v15 + 60))(v15, v13) != 0 )
        break;
    }
    if ( i == 27 )
      return 0;
    v10 = a4;
  }
  sub_423200(dword_8F7B08, 19);
  HIBYTE(a4) = a3;
  sub_423290((char *)&a4 + 3, 1);
  a4 = v10;
  sub_423290(&a4, 2);
  v16 = a5;
  a4 = a5;
  sub_423290(&a4, 4);
  HIBYTE(a4) = 4;
  sub_423290((char *)&a4 + 3, 1);
  a4 = 0;
  sub_423290(&a4, 2);
  sub_423380(dword_8F7B08);
  if ( a3 <= 1 )
  {
    v17 = (uint32_t *)sub_432F00(a3);
    sub_484880(v17, 5);
  }
  sub_484880(*(uint32_t **)(a1 + 16), 5);
  if ( a3 == 0 && v10 == 0 && v16 != 0 )
    sub_484470((uint8_t *)a1);
  return 1;
}



// ------------------------------------------------------------
// 0x484AF0 sub_484AF0
// ------------------------------------------------------------
char /*thiscall*/ sub_484AF0(int this, signed int a2, unsigned int a3, unsigned int a4, int a5)
{
  uint32_t *v5; // ecx
  int v6; // edx
  int v8; // ecx
  int v9; // esi
  unsigned int v10; // eax
  unsigned int v11; // ebx
  signed int v12; // edi
  uint32_t *v13; // esi
  signed int v14; // esi
  uint32_t *v15; // eax

  if ( *(uint16_t *)(this + 4) == 0xFFFF )
    return 0;
  if ( *(uint32_t *)(this + 8) == 1 )
    return 0;
  v5 = *(uint32_t **)(this + 16);
  v6 = v5[5];
  if ( v6 != 0 && (v5[6] - v6) >> 2 >= 1 )
    return 0;
  if ( a2 >= v5[2] )
    return 0;
  v8 = v5[3];
  v9 = *(uint32_t *)(v8 + 4 * a2);
  if ( v9 == 0 )
    return 0;
  v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v9 + 44))(*(uint32_t *)(v8 + 4 * a2));
  if ( v10 < a3 )
    return 0;
  v11 = a4;
  v12 = a5;
  if ( a4 != 0 )
  {
    if ( a4 == 3 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 20))(v9, 2) == 0 )
        return 0;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 172))(v9) != v12 )
        return 0;
    }
    else if ( a4 != 1 || sub_484790(dword_8F8534) > 0 )
    {
      return 0;
    }
  }
  else
  {
    v13 = dword_8F852C;
    if ( sub_484790(dword_8F852C) >= 1 || v12 >= v13[2] )
      return 0;
  }
  sub_423200(dword_8F7B08, 19);
  HIBYTE(a4) = 4;
  sub_423290((char *)&a4 + 3, 1);
  v14 = a2;
  sub_423290(&a2, 2);
  a2 = a3;
  sub_423290(&a2, 4);
  HIBYTE(a2) = v11;
  sub_423290((char *)&a2 + 3, 1);
  a2 = v12;
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  if ( v11 <= 1 )
  {
    v15 = (uint32_t *)sub_432F00(v11);
    sub_484880(v15, 5);
  }
  sub_484880(*(uint32_t **)(this + 16), 5);
  if ( v11 == 0 && v14 == 0 && a3 != 0 )
    sub_484470((uint8_t *)this);
  return 1;
}



// ------------------------------------------------------------
// 0x484CA0 sub_484CA0
// ------------------------------------------------------------
int /*thiscall*/ sub_484CA0(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x484CB0 sub_484CB0
// ------------------------------------------------------------
void /*thiscall*/ sub_484CB0(int this)
{
  int i; // edi
  int v3; // ecx

  for ( i = 0; i < *(uint32_t *)(this + 8); ++i )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(this + 12) + 4 * i);
    if ( v3 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 4))(v3, 1);
      *(uint32_t *)(*(uint32_t *)(this + 12) + 4 * i) = 0;
    }
  }
  if ( *(uint32_t *)(this + 12) != 0 )
    j_j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x484D00 sub_484D00
// ------------------------------------------------------------
int /*thiscall*/ sub_484D00(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // ecx

  result = *(this + 2);
  v3 = 0;
  for ( *(this + 1) = 0; v3 < result; ++v3 )
  {
    v4 = *(uint32_t *)(*(this + 3) + 4 * v3);
    if ( v4 != 0 )
      *(this + 1) += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 36))(v4);
    result = *(this + 2);
  }
  if ( *this == 0 && dword_8F7C04 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 796))(dword_8F7C04);
    *(this + 1) += result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x484D50 sub_484D50
// ------------------------------------------------------------
int /*thiscall*/ sub_484D50(int *this, int a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  result = *(this + 2);
  if ( a2 < result )
  {
    if ( *this != 0 && *this != 4 || a2 >= 3 )
    {
      v5 = *(uint32_t *)(*(this + 3) + 4 * a2);
      if ( v5 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
      *(uint32_t *)(*(this + 3) + 4 * a2) = 0;
      return sub_484D00(this);
    }
    else
    {
      v4 = *(uint32_t *)(*(this + 3) + 4 * a2);
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 40))(v4, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x484DB0 sub_484DB0
// ------------------------------------------------------------
char /*thiscall*/ sub_484DB0(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  char v6; // bl
  uint32_t *v7; // esi

  v3 = *(this + 2);
  v4 = a3;
  if ( a3 >= v3 )
    v4 = v3 - 1;
  v5 = a2;
  v6 = 0;
  if ( a2 <= v4 )
  {
    v7 = (uint32_t *)(*(this + 3) + 4 * a2);
    do
    {
      if ( *v7 != 0 )
      {
        if ( v6 != 0 )
          return 0;
      }
      else
      {
        v6 = 1;
      }
      ++v5;
      ++v7;
    }
    while ( v5 <= v4 );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x484E00 sub_484E00
// ------------------------------------------------------------
int /*thiscall*/ sub_484E00(int *this, int a2)
{
  int v3; // esi
  int v4; // eax
  int v5; // ecx
  int v7; // ecx
  int v8; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v8 = 0;
  if ( *(this + 2) <= 0 )
    return v8;
  while ( 1 )
  {
    v4 = *(this + 3);
    if ( *(uint32_t *)(v4 + 4 * v3) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + 4 * v3) + 16))(*(uint32_t *)(v4 + 4 * v3)) + 4) == a2 )
    {
      v5 = *(uint32_t *)(*(this + 3) + 4 * v3);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 20))(v5, 1) != 0 )
        break;
      ++v8;
    }
    if ( ++v3 >= *(this + 2) )
      return v8;
  }
  v7 = *(uint32_t *)(*(this + 3) + 4 * v3);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7);
}



// ------------------------------------------------------------
// 0x484E80 sub_484E80
// ------------------------------------------------------------
int /*thiscall*/ sub_484E80(int *this, int a2)
{
  int v3; // esi
  int v4; // eax

  v3 = 0;
  if ( *(this + 2) <= 0 )
    return -1;
  while ( 1 )
  {
    v4 = *(this + 3);
    if ( *(uint32_t *)(v4 + 4 * v3) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + 4 * v3) + 16))(*(uint32_t *)(v4 + 4 * v3)) + 4) == a2 )
    {
      break;
    }
    if ( ++v3 >= *(this + 2) )
      return -1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x484ED0 sub_484ED0
// ------------------------------------------------------------
int /*thiscall*/ sub_484ED0(int *this, int a2)
{
  int result; // eax
  int v3; // edx
  uint32_t *i; // ecx

  if ( a2 == 0 )
    return -1;
  v3 = *(this + 2);
  result = 0;
  if ( v3 <= 0 )
    return -1;
  for ( i = (uint32_t *)*(this + 3); *i != a2; ++i )
  {
    if ( ++result >= v3 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x484F10 sub_484F10
// ------------------------------------------------------------
bool /*thiscall*/ sub_484F10(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 1);
  return v1 == 0 || (*(this + 2) - v1) >> 2 == 0;
}



// ------------------------------------------------------------
// 0x484F40 sub_484F40
// ------------------------------------------------------------
char /*thiscall*/ sub_484F40(int *this, int a2, int a3, char a4)
{
  if ( a2 >= *(this + 2) )
    return 0;
  *(uint32_t *)(*(this + 3) + 4 * a2) = a3;
  if ( a3 != 0 )
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)a3 + 28))(a3, this);
  sub_484D00(this);
  if ( a4 == 1 && *this == 0 && a3 != 0 )
    sub_5473D0(a3);
  return 1;
}



// ------------------------------------------------------------
// 0x484FA0 sub_484FA0
// ------------------------------------------------------------
int sub_484FA0()
{
  int v0; // esi
  int64_t v1; // rax
  int v3; // [esp+4h] [ebp-4h]

  if ( dword_8F7C04 != 0 )
  {
    v0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);
    v3 = sub_41A5E0(v0 + 732);
    return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v0 + 746)));
  }
  else
  {
    LODWORD(v1) = -1;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x484FF0 sub_484FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_484FF0(uint32_t *this)
{
  int v1; // edx
  int result; // eax

  v1 = *(this + 5);
  if ( v1 != 0 )
  {
    result = (*(this + 6) - v1) >> 2;
    if ( result != 0 )
    {
      result = (*(this + 6) - v1) >> 2;
      if ( result != 0 )
        *(this + 6) -= 4;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x485020 sub_485020
// ------------------------------------------------------------
void /*thiscall*/ sub_485020(int *this)
{
  int v2; // edi
  int v3; // ecx
  int v4; // eax
  bool v5; // zf

  v2 = 0;
  if ( *this == 0 || *this == 4 )
    v2 = 3;
  for ( ; v2 < *(this + 2); ++v2 )
  {
    v3 = *(uint32_t *)(*(this + 3) + 4 * v2);
    if ( v3 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 4))(v3, 1);
      *(uint32_t *)(*(this + 3) + 4 * v2) = 0;
    }
  }
  v4 = *this;
  v5 = *this == 0;
  *(this + 1) = 0;
  if ( v5 || v4 == 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)*(this + 3) + 40))(*(uint32_t *)*(this + 3), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 3) + 4) + 40))(*(uint32_t *)(*(this + 3) + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 3) + 8) + 40))(*(uint32_t *)(*(this + 3) + 8), 0);
  }
  if ( *(this + 5) != 0 )
    j__free((void *)*(this + 5));
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
}



// ------------------------------------------------------------
// 0x4850B0 sub_4850B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4850B0(int *this, int a2, unsigned int a3)
{
  int v4; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx

  v4 = *(this + 5);
  if ( v4 == 0 || (*(this + 6) - v4) >> 2 <= 0 )
    return 0;
  v6 = *(this + 5);
  if ( v6 != 0 && (*(this + 6) - v6) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )
    *(this + 6) -= 4;
  if ( a2 >= *(this + 2) )
    return 0;
  v7 = *(this + 3);
  if ( *(uint32_t *)(v7 + 4 * a2) == 0 )
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v7 + 4 * a2) + 44))(*(uint32_t *)(v7 + 4 * a2)) <= a3 )
  {
    sub_484D50(this, a2);
  }
  else
  {
    v8 = *(uint32_t *)(*(this + 3) + 4 * a2);
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v8 + 52))(v8, a3);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x485150 sub_485150
// ------------------------------------------------------------
char /*thiscall*/ sub_485150(int *this, int a2)
{
  int v3; // ecx
  int v5; // ecx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // ecx
  int v9; // edi
  unsigned int v10; // ebx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  uint32_t *v15; // [esp+4h] [ebp-4h]

  v3 = *(this + 5);
  if ( v3 == 0 || (*(this + 6) - v3) >> 2 <= 0 )
    return 0;
  v5 = *(this + 5);
  if ( v5 != 0 && (*(this + 6) - v5) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )
    *(this + 6) -= 4;
  v6 = *(uint32_t **)(a2 + 4);
  v7 = *(uint32_t **)(a2 + 8);
  v8 = v6;
  if ( v6 == v7 )
  {
LABEL_12:
    v15 = *(uint32_t **)(a2 + 4);
    if ( v6 != v7 )
    {
      while ( 1 )
      {
        v9 = *v6;
        v10 = v6[1];
        v11 = *(uint32_t *)(*(this + 3) + 4 * *v6);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11) <= v10 )
        {
          if ( v9 < *(this + 2) )
          {
            if ( *this != 0 && *this != 4 || v9 >= 3 )
            {
              v14 = *(uint32_t *)(*(this + 3) + 4 * v9);
              if ( v14 != 0 )
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, 1);
              *(uint32_t *)(*(this + 3) + 4 * v9) = 0;
              sub_484D00(this);
            }
            else
            {
              v13 = *(uint32_t *)(*(this + 3) + 4 * v9);
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 40))(v13, 0);
            }
          }
        }
        else
        {
          v12 = *(uint32_t *)(*(this + 3) + 4 * v9);
          (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v12 + 52))(v12, v10);
        }
        v15 += 2;
        if ( v15 == *(uint32_t **)(a2 + 8) )
          break;
        v6 = v15;
      }
    }
    return 1;
  }
  else
  {
    while ( *v8 < *(this + 2) && *(uint32_t *)(*(this + 3) + 4 * *v8) != 0 )
    {
      v8 += 2;
      if ( v8 == v7 )
        goto LABEL_12;
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x485270 sub_485270
// ------------------------------------------------------------
char /*thiscall*/ sub_485270(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  void *v10; // eax
  int v11; // eax
  int v12; // ecx

  v4 = *(this + 5);
  if ( v4 == 0 || (*(this + 6) - v4) >> 2 <= 0 )
    return 0;
  v6 = *(this + 5);
  if ( v6 != 0 && (*(this + 6) - v6) >> 2 != 0 && (*(this + 6) - *(this + 5)) >> 2 != 0 )
    *(this + 6) -= 4;
  v7 = *(this + 2);
  if ( a2 < v7 && a3 < v7 )
  {
    v8 = *(this + 3);
    if ( *(uint32_t *)(v8 + 4 * a3) != 0 )
    {
      v9 = *(uint32_t *)(v8 + 4 * a3);
    }
    else
    {
      if ( *(uint32_t *)(v8 + 4 * a2) == 0 )
      {
LABEL_15:
        v11 = *(this + 3);
        v12 = *(uint32_t *)(v11 + 4 * a2);
        *(uint32_t *)(v11 + 4 * a2) = *(uint32_t *)(v11 + 4 * a3);
        *(uint32_t *)(*(this + 3) + 4 * a3) = v12;
        return 1;
      }
      v9 = *(uint32_t *)(*(this + 3) + 4 * a2);
    }
    v10 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 56))(v9);
    sub_432EA0(v10, -1, 0, 0);
    goto LABEL_15;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x485330 sub_485330
// ------------------------------------------------------------
char /*thiscall*/ sub_485330(int *this, int a2, unsigned int a3, int *a4, int a5)
{
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // edi
  int v12; // eax
  void *v13; // eax
  int v14; // ebx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  int v20; // [esp+4h] [ebp-4h]

  v6 = *(this + 5);
  if ( v6 == 0 )
    return 0;
  if ( (*(this + 6) - v6) >> 2 <= 0 )
    return 0;
  v7 = a4[5];
  if ( v7 == 0 || (a4[6] - v7) >> 2 <= 0 )
    return 0;
  v8 = *(this + 5);
  if ( v8 != 0 && (*(this + 6) - v8) >> 2 != 0 )
    *(this + 6) -= 4;
  v9 = a4[5];
  if ( v9 != 0 && (a4[6] - v9) >> 2 != 0 && (a4[6] - a4[5]) >> 2 != 0 )
    a4[6] -= 4;
  if ( a2 >= *(this + 2) )
    return 0;
  if ( a5 >= a4[2] )
    return 0;
  v10 = *(this + 3);
  if ( *(uint32_t *)(v10 + 4 * a2) == 0
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v10 + 4 * a2) + 44))(*(uint32_t *)(v10 + 4 * a2)) < a3 )
  {
    return 0;
  }
  v11 = *(uint32_t *)(*(this + 3) + 4 * a2);
  v12 = sub_44A980(a5);
  v20 = v12;
  if ( v11 != 0 )
  {
    v13 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 56))(v11);
    sub_432EA0(v13, -1, 0, 0);
    v12 = v20;
  }
  if ( v12 != 0 )
  {
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 16))(v12);
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 4) != *(uint32_t *)(v14 + 4) )
      return 0;
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v20 + 48))(v20, a3);
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v11 + 52))(v11, a3);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11) == 0 )
      sub_484D50(this, a2);
  }
  else
  {
    v16 = *(uint32_t *)(*(this + 3) + 4 * a2);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 44))(v16) == a3 )
    {
      sub_484F40(a4, a5, *(uint32_t *)(*(this + 3) + 4 * a2), 1);
      *(uint32_t *)(*(this + 3) + 4 * a2) = 0;
    }
    else
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11);
      v18 = sub_522300(*(void **)(v17 + 4), a3, 0, 0, -1, 1);
      sub_484F40(a4, a5, v18, 1);
      v19 = *(uint32_t *)(*(this + 3) + 4 * a2);
      (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v19 + 52))(v19, a3);
    }
  }
  sub_484D00(this);
  sub_484D00(a4);
  return 1;
}



// ------------------------------------------------------------
// 0x485510 sub_485510
// ------------------------------------------------------------
char /*userpurge*/ sub_485510@<al>(int *a1@<ecx>, int a2@<esi>, int a3, int a4)
{
  int v5; // ecx
  int v7; // ecx
  int v8; // ebx
  int v9; // esi
  int v10; // ebx
  void *v11; // eax
  void *v12; // eax
  int v13; // edi
  int v14; // eax
  int v16; // [esp+4h] [ebp-4h]

  v5 = a1[5];
  if ( v5 == 0 || (a1[6] - v5) >> 2 <= 0 )
    return 0;
  v7 = a1[5];
  if ( v7 != 0 && (a1[6] - v7) >> 2 != 0 && (a1[6] - a1[5]) >> 2 != 0 )
    a1[6] -= 4;
  v8 = dword_8F7C04;
  if ( dword_8F7C04 == 0 || a3 >= a1[2] )
    return 0;
  v9 = __RTDynamicCast(
         *(uint32_t *)(a1[3] + 4 * a3),
         0,
         &IRDItem `RTTI Type Descriptor',
         &CNRDEquipment `RTTI Type Descriptor',
         0);
  if ( v9 == 0 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 792))(v8, a4) == 0 )
    return 0;
  v16 = 0;
  if ( v9 != 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 784))(v8, v9);
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 100))(v9);
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v8 + 792))(v8, a4, a2) != 0 )
      v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 788))(v8, a4);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 1080))(v8, a4);
    v10 = v16;
  }
  if ( v9 == v10 )
    return 0;
  if ( v9 != 0 )
  {
    v11 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 56))(v9);
    sub_432EA0(v11, -1, 0, 0);
  }
  else if ( v10 != 0 )
  {
    v12 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 56))(v10);
    sub_432EA0(v12, -1, 0, 0);
  }
  *(uint32_t *)(a1[3] + 4 * a3) = v10;
  sub_484D00(a1);
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && a4 <= 9 )
  {
    v13 = sub_429830((uint16_t)word_77F804) + 16;
    if ( v9 != 0 )
      v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9) + 4);
    else
      v14 = 0xFFFF;
    *(uint32_t *)(v13 + 4 * a4 + 56) = v14;
    if ( dword_8F7C08 != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C08 + 348))(dword_8F7C08, v13);
    if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 611) + 12) == 1 )
      sub_5603E0(v13);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4856E0 sub_4856E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4856E0(int *this, int a2)
{
  int v3; // ecx
  int v5; // eax
  int v6; // ecx

  v3 = *(this + 5);
  if ( v3 == 0 )
    return 0;
  if ( (*(this + 6) - v3) >> 2 <= 0 )
    return 0;
  *(this + 6) -= 4;
  if ( dword_8F7C04 == 0 )
    return 0;
  if ( a2 >= *(this + 2) )
    return 0;
  v5 = *(this + 3);
  if ( *(uint32_t *)(v5 + 4 * a2) == 0 )
    return 0;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + 4 * a2) + 44))(*(uint32_t *)(v5 + 4 * a2)) <= 1 )
  {
    sub_484D50(this, a2);
  }
  else
  {
    v6 = *(uint32_t *)(*(this + 3) + 4 * a2);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 52))(v6, 1);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x485790 sub_485790
// ------------------------------------------------------------
void /*thiscall*/ sub_485790(void *this)
{
  void **v2; // edi
  void **i; // [esp+Ch] [ebp-4h]

  *((uint32_t *)this + 1) = 0;
  sub_41BFE0((void **)this + 2, szPassword);
  sub_41BFE0((void **)this + 3, szPassword);
  sub_41BFE0((void **)this + 4, szPassword);
  sub_41BFE0((void **)this + 5, szPassword);
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint8_t *)this + 32) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  sub_41BFE0((void **)this + 19, szPassword);
  sub_41BFE0((void **)this + 20, szPassword);
  *((uint32_t *)this + 21) = 0;
  if ( *((uint32_t *)this + 23) != 0 )
    j__free(*((void **)this + 23));
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  v2 = *((void ***)this + 27);
  if ( v2 != nullptr )
  {
    for ( i = *((void ***)this + 28); v2 != i; ++v2 )
      sub_41B010(v2);
    j__free(*((void **)this + 27));
  }
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
}



// ------------------------------------------------------------
// 0x485870 sub_485870
// ------------------------------------------------------------
void /*thiscall*/ sub_485870(int this)
{
  sub_4017E0(this + 104);
  if ( *(uint32_t *)(this + 92) != 0 )
    j__free(*(void **)(this + 92));
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  sub_41B010((void **)(this + 80));
  sub_41B010((void **)(this + 76));
  sub_41B010((void **)(this + 20));
  sub_41B010((void **)(this + 16));
  sub_41B010((void **)(this + 12));
  sub_41B010((void **)(this + 8));
}



// ------------------------------------------------------------
// 0x485920 sub_485920
// ------------------------------------------------------------
void /*thiscall*/ sub_485920(uint32_t *this)
{
  *this = &IRDItem::`vftable';
  nullsub_3(this);
  sub_41A580(this + 33);
  sub_485870((int)(this + 2));
}



// ------------------------------------------------------------
// 0x485990 sub_485990
// ------------------------------------------------------------
int /*thiscall*/ sub_485990(uint32_t *this, int a2)
{
  *(this + 32) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4859B0 sub_4859B0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4859B0(uint32_t *this, int a2)
{
  return (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 20))(this, 1) != 0 && *(this + 3) == a2;
}



// ------------------------------------------------------------
// 0x4859F0 sub_4859F0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4859F0(int this)
{
  int v1; // eax

  v1 = *(uint32_t *)(this + 36);
  return v1 == 0 || v1 == 3 && *(uint8_t *)(this + 40) != 0;
}



// ------------------------------------------------------------
// 0x485A20 sub_485A20
// ------------------------------------------------------------
char /*thiscall*/ sub_485A20(uint8_t *this, char a2)
{
  *(this + 146) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x485A40 sub_485A40
// ------------------------------------------------------------
bool /*thiscall*/ sub_485A40(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) > 0;
}



// ------------------------------------------------------------
// 0x485A50 sub_485A50
// ------------------------------------------------------------
int /*thiscall*/ sub_485A50(void *this)
{
  int v1; // esi

  v1 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 116))(this);
  return v1 - sub_699000((int)&unk_9B0C70);
}



// ------------------------------------------------------------
// 0x485A70 sub_485A70
// ------------------------------------------------------------
int /*thiscall*/ sub_485A70(uint32_t *this)
{
  return sub_41A5E0((unsigned int)(this + 33)) * *(this + 16);
}



// ------------------------------------------------------------
// 0x485AA0 sub_485AA0
// ------------------------------------------------------------
int /*thiscall*/ sub_485AA0(void *this, int a2)
{
  int v3; // eax

  v3 = sub_41A5E0((unsigned int)this + 132);
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, a2 + v3);
}



// ------------------------------------------------------------
// 0x485AD0 sub_485AD0
// ------------------------------------------------------------
int /*thiscall*/ sub_485AD0(void *this, int a2)
{
  int v3; // eax

  v3 = sub_41A5E0((unsigned int)this + 132);
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, v3 - a2);
}



// ------------------------------------------------------------
// 0x485B00 sub_485B00
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_485B00(unsigned int **this)
{
  return sub_41ACF0(this + 21);
}



// ------------------------------------------------------------
// 0x485B10 sub_485B10
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_485B10(unsigned int **this)
{
  return sub_41ACF0(this + 4);
}



// ------------------------------------------------------------
// 0x485B20 sub_485B20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485B20(uint32_t *Block, char a2)
{
  sub_485920(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x485B50 sub_485B50
// ------------------------------------------------------------
void /*thiscall*/ sub_485B50(uint32_t *this)
{
  *this = &CNRDStackable::`vftable';
  nullsub_3(this);
  sub_485920(this);
}



// ------------------------------------------------------------
// 0x485BA0 sub_485BA0
// ------------------------------------------------------------
int /*thiscall*/ sub_485BA0(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // ecx
  int result; // eax

  v2 = this + 37;
  *v2 = *a2;
  v2[1] = a2[1];
  v2[2] = a2[2];
  result = a2[3];
  v2[3] = result;
  return result;
}



// ------------------------------------------------------------
// 0x485BD0 sub_485BD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485BD0(uint32_t *Block, char a2)
{
  sub_485B50(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x485C00 sub_485C00
// ------------------------------------------------------------
int /*thiscall*/ sub_485C00(int this)
{
  void **v2; // ecx

  v2 = (void **)(this + 8);
  *v2 = nullptr;
  sub_41BFE0(v2, szPassword);
  *(uint32_t *)(this + 12) = 0;
  sub_41BFE0((void **)(this + 12), szPassword);
  *(uint32_t *)(this + 16) = 0;
  sub_41BFE0((void **)(this + 16), szPassword);
  *(uint32_t *)(this + 20) = 0;
  sub_41BFE0((void **)(this + 20), szPassword);
  *(uint32_t *)(this + 76) = 0;
  sub_41BFE0((void **)(this + 76), szPassword);
  *(uint32_t *)(this + 80) = 0;
  sub_41BFE0((void **)(this + 80), szPassword);
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  sub_485790((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x485CC0 sub_485CC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485CC0(uint32_t *this)
{
  *this = &IRDItem::`vftable';
  sub_485C00((int)(this + 2));
  sub_41A630((unsigned int)(this + 33));
  *(this + 33) = &clong::`vftable';
  sub_4F2BE0(this);
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x485D30 sub_485D30
// ------------------------------------------------------------
int /*thiscall*/ sub_485D30(int this)
{
  sub_485CC0((uint32_t *)this);
  *(uint32_t *)this = &CNRDStackable::`vftable';
  *(uint32_t *)(this + 148) = 8;
  *(uint32_t *)(this + 152) = -1;
  *(uint32_t *)(this + 156) = 0;
  *(uint8_t *)(this + 160) = 0;
  sub_577FF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x485DA0 sub_485DA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_485DA0(uint32_t *this, int a2)
{
  sub_485D30((int)this);
  *this = &CNRDMoney::`vftable';
  nullsub_3(this);
  sub_578680(a2);
  return this;
}



// ------------------------------------------------------------
// 0x485E00 sub_485E00
// ------------------------------------------------------------
void */*thiscall*/ sub_485E00(void *Block, char a2)
{
  sub_485E30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x485E30 sub_485E30
// ------------------------------------------------------------
void /*thiscall*/ sub_485E30(uint32_t *this)
{
  *this = &CNRDMoney::`vftable';
  nullsub_3(this);
  sub_485B50(this);
}



// ------------------------------------------------------------
// 0x485E80 sub_485E80
// ------------------------------------------------------------
int /*thiscall*/ sub_485E80(uint32_t *this, void *Block, int a3)
{
  int result; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // edi

  *this = Block;
  *(this + 2) = a3;
  *(this + 3) = operator new(4 * a3);
  for ( result = 0; result < a3; ++result )
    *(uint32_t *)(*(this + 3) + 4 * result) = 0;
  if ( Block == nullptr || Block == (void *)4 )
  {
    v5 = operator new(0xA4u);
    v6 = v5;
    if ( v5 != nullptr )
    {
      sub_485D30((int)v5);
      *v6 = &CNRDMoney::`vftable';
      nullsub_3(v6);
      sub_578680(0);
    }
    else
    {
      v6 = nullptr;
    }
    *(uint32_t *)*(this + 3) = v6;
    *(uint32_t *)(*(this + 3) + 4) = sub_522300((void *)1, 0, 0, 0, -1, 1);
    result = sub_522300((void *)2, 0, 0, 0, -1, 1);
    *(uint32_t *)(*(this + 3) + 8) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x485F70 sub_485F70
// ------------------------------------------------------------
int /*thiscall*/ sub_485F70(int this, int a2)
{
  int v2; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = this + 8;
  *(uint32_t *)(this + 8) = *(uint32_t *)a2;
  *(uint32_t *)(this + 12) = *(uint32_t *)(a2 + 4);
  sub_41B0D0((unsigned int **)(this + 16), (unsigned int **)(a2 + 8));
  sub_41B0D0((unsigned int **)(v2 + 12), (unsigned int **)(a2 + 12));
  sub_41B0D0((unsigned int **)(v2 + 16), (unsigned int **)(a2 + 16));
  sub_41B0D0((unsigned int **)(v2 + 20), (unsigned int **)(a2 + 20));
  *(uint32_t *)(v2 + 24) = *(uint32_t *)(a2 + 24);
  *(uint32_t *)(v2 + 28) = *(uint32_t *)(a2 + 28);
  *(uint8_t *)(v2 + 32) = *(uint8_t *)(a2 + 32);
  *(uint32_t *)(v2 + 36) = *(uint32_t *)(a2 + 36);
  *(uint32_t *)(v2 + 40) = *(uint32_t *)(a2 + 40);
  *(uint32_t *)(v2 + 44) = *(uint32_t *)(a2 + 44);
  *(uint32_t *)(v2 + 48) = *(uint32_t *)(a2 + 48);
  *(uint32_t *)(v2 + 52) = *(uint32_t *)(a2 + 52);
  *(uint32_t *)(v2 + 56) = *(uint32_t *)(a2 + 56);
  *(uint8_t *)(v2 + 60) = *(uint8_t *)(a2 + 60);
  *(uint8_t *)(v2 + 61) = *(uint8_t *)(a2 + 61);
  *(uint8_t *)(v2 + 62) = *(uint8_t *)(a2 + 62);
  *(uint8_t *)(v2 + 63) = *(uint8_t *)(a2 + 63);
  *(uint32_t *)(v2 + 64) = *(uint32_t *)(a2 + 64);
  *(uint32_t *)(v2 + 68) = *(uint32_t *)(a2 + 68);
  *(uint32_t *)(v2 + 72) = *(uint32_t *)(a2 + 72);
  sub_41B0D0((unsigned int **)(v2 + 76), (unsigned int **)(a2 + 76));
  sub_41B0D0((unsigned int **)(v2 + 80), (unsigned int **)(a2 + 80));
  *(uint32_t *)(v2 + 84) = *(uint32_t *)(a2 + 84);
  sub_4ED3F0(v2 + 88, a2 + 88);
  sub_41DC80(v2 + 104, a2 + 104);
  return v2;
}



// ------------------------------------------------------------
// 0x486070 sub_486070
// ------------------------------------------------------------
char /*thiscall*/ sub_486070(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ecx
  int v7; // edi
  int v8; // eax
  unsigned int v9; // eax
  unsigned int v10; // ebx

  v5 = *(this + 5);
  if ( v5 != 0 && (*(this + 6) - v5) >> 2 >= 1 )
    return 0;
  v7 = a2;
  if ( a2 >= *(this + 2) )
    return 0;
  v8 = *(this + 3);
  if ( *(uint32_t *)(v8 + 4 * a2) == 0 )
    return 0;
  v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 4 * a2) + 44))(*(uint32_t *)(v8 + 4 * a2));
  v10 = a3;
  if ( v9 < a3 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  sub_423200(dword_8F7B08, 18);
  HIBYTE(a2) = *(uint8_t *)this;
  sub_423290((char *)&a2 + 3, 1);
  HIBYTE(a2) = 1;
  sub_423290((char *)&a2 + 3, 1);
  a2 = a4;
  sub_423290(&a2, 2);
  a2 = v7;
  sub_423290(&a2, 2);
  a2 = v10;
  sub_423290(&a2, 4);
  sub_423380(dword_8F7B08);
  sub_484880(this, 0);
  if ( byte_77F280 != 0 )
    sub_4850B0(this, v7, v10);
  return 1;
}



// ------------------------------------------------------------
// 0x486190 sub_486190
// ------------------------------------------------------------
char /*thiscall*/ sub_486190(int *this, int a2, int a3)
{
  int *v3; // ebx
  int v4; // ecx
  int v6; // edi
  int *v7; // esi
  int v8; // eax
  unsigned int v9; // ebx
  int v10; // edx
  int v11; // eax
  uint16_t *v12; // esi
  int v13; // ebx
  int v14; // edx
  unsigned int v15; // ecx
  uint32_t *v16; // eax
  int *v17; // [esp+4h] [ebp-4h]

  v3 = this;
  v4 = *(this + 5);
  v17 = v3;
  if ( v4 != 0 && (v3[6] - v4) >> 2 >= 1 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v6 = a2;
  v7 = *(int **)(a2 + 4);
  if ( v7 == *(int **)(a2 + 8) )
  {
LABEL_11:
    sub_423200(dword_8F7B08, 18);
    HIBYTE(a2) = *(uint8_t *)v3;
    sub_423290((char *)&a2 + 3, 1);
    v11 = *(uint32_t *)(v6 + 4);
    if ( v11 != 0 )
      HIBYTE(a2) = (*(uint32_t *)(v6 + 8) - v11) >> 3;
    else
      HIBYTE(a2) = 0;
    sub_423290((char *)&a2 + 3, 1);
    v12 = *(uint16_t **)(v6 + 4);
    if ( v12 != *(uint16_t **)(v6 + 8) )
    {
      v13 = a3;
      do
      {
        a2 = v13;
        sub_423290(&a2, 2);
        a2 = *v12;
        sub_423290(&a2, 2);
        a2 = *((uint32_t *)v12 + 1);
        sub_423290(&a2, 4);
        v12 += 4;
      }
      while ( v12 != *(uint16_t **)(v6 + 8) );
      v3 = v17;
    }
    sub_423380(dword_8F7B08);
    v14 = v3[5];
    a2 = 0;
    if ( v14 != 0 )
      v15 = (v3[6] - v14) >> 2;
    else
      v15 = 0;
    if ( v14 != 0 && v15 < (v3[7] - v14) >> 2 )
    {
      v16 = (uint32_t *)v3[6];
      *v16 = 0;
      v3[6] = (int)(v16 + 1);
    }
    else
    {
      sub_430C80((void *)v3[6], 1, (int)&a2);
    }
    if ( byte_77F280 != 0 )
      sub_485150(v3, v6);
    return 1;
  }
  else
  {
    while ( 1 )
    {
      v8 = *v7;
      if ( *v7 >= v17[2] )
        return 0;
      v10 = v17[3];
      if ( *(uint32_t *)(v10 + 4 * v8) == 0 )
        return 0;
      v9 = v7[1];
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v10 + 4 * v8) + 44))(*(uint32_t *)(v10 + 4 * v8)) < v9 )
        return 0;
      v7 += 2;
      if ( v7 == *(int **)(v6 + 8) )
      {
        v3 = v17;
        goto LABEL_11;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x486330 sub_486330
// ------------------------------------------------------------
char /*thiscall*/ sub_486330(uint32_t *this, signed int a2, unsigned int a3)
{
  int v4; // ecx
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // edi
  int v9; // [esp+4h] [ebp-8h] BYREF
  char v10[4]; // [esp+8h] [ebp-4h] BYREF

  v4 = *(this + 5);
  if ( v4 != 0 && (*(this + 6) - v4) >> 2 >= 1 )
    return 0;
  if ( a2 >= *(this + 2) )
    return 0;
  v5 = *(this + 3);
  if ( *(uint32_t *)(v5 + 4 * a2) == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + 4 * a2) + 44))(*(uint32_t *)(v5 + 4 * a2));
  if ( v6 < a3 )
    return 0;
  v7 = dword_8F7C04;
  if ( dword_8F7C04 == 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 80))(dword_8F7C04) == 0
    || *this != 0
    || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
  {
    return 0;
  }
  sub_423200(dword_8F7B08, 50);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
  sub_423290(&v9, 2);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
  sub_423290(&v9, 2);
  v10[0] = *(uint8_t *)this;
  sub_423290(v10, 1);
  sub_423290(&a2, 2);
  a2 = a3;
  sub_423290(&a2, 4);
  sub_423380(dword_8F7B08);
  sub_484880(this, 1);
  return 1;
}



// ------------------------------------------------------------
// 0x486470 sub_486470
// ------------------------------------------------------------
char /*thiscall*/ sub_486470(uint32_t *this, int a2)
{
  int v3; // ecx
  uint8_t *v5; // esi
  int v6; // eax

  v3 = *(this + 5);
  if ( v3 != 0 && (*(this + 6) - v3) >> 2 >= 1 )
    return 0;
  v5 = (uint8_t *)a2;
  if ( a2 == 0 )
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v6 = sub_429830((uint16_t)word_77F804);
  if ( (uint8_t)sub_5788B0(*(uint16_t *)(v6 + 4)) == 0 )
    return 0;
  sub_423200(dword_8F7B08, 46);
  a2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v5 + 52))(v5);
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  v5[977] = 1;
  sub_484880(this, 2);
  return 1;
}



// ------------------------------------------------------------
// 0x486530 sub_486530
// ------------------------------------------------------------
char /*thiscall*/ sub_486530(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v5 = *(this + 5);
  if ( v5 != 0 )
    v6 = (*(this + 6) - v5) >> 2;
  else
    v6 = 0;
  if ( v6 >= a4 )
    return 0;
  v7 = *(this + 5);
  if ( v7 != 0 && (*(this + 6) - v7) >> 2 >= 1 && ((*(this + 6) - v7) >> 2 == 0 || *(uint32_t *)(*(this + 6) - 4) != 3) )
    return 0;
  v9 = *(this + 2);
  if ( a2 >= v9 )
    return 0;
  if ( a3 >= v9 )
    return 0;
  v10 = *(this + 3);
  if ( *(uint32_t *)(v10 + 4 * a2) == 0 && *(uint32_t *)(v10 + 4 * a3) == 0 )
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v11 = *(uint32_t *)(dword_8F7C08 + 648);
  if ( v11 != 0 && *(uint8_t *)(v11 + 284) != 0 && *(uint8_t *)(v11 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 19);
  HIBYTE(a4) = *(uint8_t *)this;
  sub_423290((char *)&a4 + 3, 1);
  a4 = a2;
  sub_423290(&a4, 2);
  a4 = 0;
  sub_423290(&a4, 4);
  HIBYTE(a4) = *(uint8_t *)this;
  sub_423290((char *)&a4 + 3, 1);
  a4 = a3;
  sub_423290(&a4, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 3);
  return 1;
}



// ------------------------------------------------------------
// 0x486690 sub_486690
// ------------------------------------------------------------
char /*thiscall*/ sub_486690(uint32_t *this, int a2, int a3, int a4)
{
  char result; // al

  result = sub_486530(this, a2, a3, 1);
  if ( result != 0 )
    return sub_486530(this, a3, a4, 2) != 0;
  return result;
}



// ------------------------------------------------------------
// 0x4866D0 sub_4866D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4866D0(uint32_t *this, int a2, unsigned int a3, uint32_t *a4, signed int a5)
{
  int v6; // ecx
  uint32_t *v7; // edi
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v12; // eax

  v6 = *(this + 5);
  if ( v6 != 0 && (*(this + 6) - v6) >> 2 >= 1 )
    return 0;
  v7 = a4;
  v8 = a4[5];
  if ( v8 != 0 && (a4[6] - v8) >> 2 >= 1 )
    return 0;
  if ( a2 >= *(this + 2) )
    return 0;
  if ( a5 >= a4[2] )
    return 0;
  v9 = *(this + 3);
  if ( *(uint32_t *)(v9 + 4 * a2) != 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v9 + 4 * a2) + 44))(*(uint32_t *)(v9 + 4 * a2));
    if ( v10 < a3 )
      return 0;
  }
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v12 = *(uint32_t *)(dword_8F7C08 + 648);
  if ( v12 != 0 && *(uint8_t *)(v12 + 284) != 0 && *(uint8_t *)(v12 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 19);
  HIBYTE(a4) = *(uint8_t *)this;
  sub_423290((char *)&a4 + 3, 1);
  a4 = (uint32_t *)a2;
  sub_423290(&a4, 2);
  sub_423290(&a3, 4);
  HIBYTE(a3) = *(uint8_t *)v7;
  sub_423290((char *)&a3 + 3, 1);
  a3 = a5;
  sub_423290(&a3, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 4);
  sub_484880(v7, 4);
  return 1;
}



// ------------------------------------------------------------
// 0x486820 sub_486820
// ------------------------------------------------------------
char /*thiscall*/ sub_486820(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  uint8_t *v10; // eax
  int v11; // ebx
  uint32_t *v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edx
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  uint8_t *v22; // [esp+4h] [ebp-4h]

  v5 = *(this + 5);
  if ( v5 != 0 )
    v6 = (*(this + 6) - v5) >> 2;
  else
    v6 = 0;
  if ( v6 >= a4 )
    return 0;
  v7 = *(this + 5);
  if ( v7 != 0 && (*(this + 6) - v7) >> 2 >= 1 && ((*(this + 6) - v7) >> 2 == 0 || *(uint32_t *)(*(this + 6) - 4) != 7) )
    return 0;
  a4 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
    return 0;
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v8 = *(uint32_t *)(dword_8F7C08 + 648);
  if ( v8 != 0 && *(uint8_t *)(v8 + 284) != 0 && *(uint8_t *)(v8 + 285) != 0 )
    return 0;
  if ( a2 >= *(this + 2) )
    return 0;
  v10 = __RTDynamicCast(
          *(uint32_t **)(*(this + 3) + 4 * a2),
          0,
          &IRDItem `RTTI Type Descriptor',
          &CNRDEquipment `RTTI Type Descriptor',
          0);
  v11 = (int)v10;
  if ( v10 != nullptr )
  {
    v22 = v10;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v10 + 172))(v10);
    v13 = a3;
    if ( *v12 != a3 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 804))(a4, v11) == 0 )
      return 0;
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 32) != 0 )
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0x19, v11, 0);
      return 1;
    }
    v14 = (int)v22;
  }
  else
  {
    if ( *(uint32_t *)(*(this + 3) + 4 * a2) != 0 )
      return 0;
    v13 = a3;
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 792))(a4, a3) == 0 )
      return 0;
    v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 792))(a4, v13);
  }
  if ( v14 == 0 )
    return 0;
  v15 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v15 != 3 && v15 != 4 && v15 != 6 )
    goto LABEL_35;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 104))(v14) != 0 )
  {
    v16 = *((uint32_t **)dword_8F8528 + 7);
    v17 = sub_422E70(414);
    sub_43BEE0(v16, v17, -6567706, 0, -1);
    sub_432EA0("ALERT_1", -1, 0, 0);
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 1100))(a4, v13) == 0 )
  {
    v18 = *((uint32_t **)dword_8F8528 + 7);
    v19 = sub_422E70(415);
    sub_43BEE0(v18, v19, -6567706, 0, -1);
    return 0;
  }
  else
  {
LABEL_35:
    sub_423200(dword_8F7B08, 19);
    HIBYTE(a3) = *(uint8_t *)this;
    sub_423290((char *)&a3 + 3, 1);
    a3 = a2;
    sub_423290(&a3, 2);
    a3 = 1;
    sub_423290(&a3, 4);
    HIBYTE(a3) = 3;
    sub_423290((char *)&a3 + 3, 1);
    a3 = v13;
    sub_423290(&a3, 2);
    sub_423380(dword_8F7B08);
    sub_484880(7);
    if ( byte_77F280 != 0 )
    {
      sub_485510(a2, v13);
      if ( v13 <= 9 )
      {
        if ( v11 != 0 )
          v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 4);
        else
          v20 = 0xFFFF;
        *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 4 * v13 + 72) = v20;
        if ( dword_8F7C08 != 0 )
        {
          v21 = sub_429830((uint16_t)word_77F804);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C08 + 348))(dword_8F7C08, v21 + 16);
        }
      }
    }
    return 1;
  }
}


// ------------------------------------------------------------
// 0x486B40 sub_486B40
// ------------------------------------------------------------
char /*thiscall*/ sub_486B40(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v5; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // ecx
  int v12; // eax

  if ( byte_77F280 != 0 )
  {
    v4 = *(uint32_t *)(*(this + 3) + 4 * a2);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 864))(dword_8F7C04, *(uint32_t *)(v5 + 4));
    return 1;
  }
  else
  {
    v7 = *(this + 5);
    if ( v7 != 0 )
      v8 = (*(this + 6) - v7) >> 2;
    else
      v8 = 0;
    if ( v8 < a3
      && ((v9 = *(this + 5)) == 0
       || (*(this + 6) - v9) >> 2 < 1
       || (*(this + 6) - v9) >> 2 != 0 && *(uint32_t *)(*(this + 6) - 4) == 8)
      && dword_8F7C04 != 0
      && *(uint16_t *)(dword_8F8538 + 4) == 0xFFFF )
    {
      sub_423200(dword_8F7B08, 47);
      v10 = a2;
      sub_423290(&a2, 2);
      sub_423380(dword_8F7B08);
      sub_484880(this, 8);
      v11 = *(uint32_t *)(*(this + 3) + 4 * v10);
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 864))(dword_8F7C04, *(uint32_t *)(v12 + 4));
      return 1;
    }
    else
    {
      return 0;
    }
  }
}



// ------------------------------------------------------------
// 0x486C40 sub_486C40
// ------------------------------------------------------------
char /*thiscall*/ sub_486C40(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int i; // esi
  int v6; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  v2 = *(this + 5);
  if ( v2 != 0 && (*(this + 6) - v2) >> 2 >= 1 || *(uint32_t *)(*((uint32_t *)dword_8F8528 + 20) + 108) != 0 )
    return 0;
  if ( *this != 0 )
  {
    if ( *this != 2 && sub_484DB0(this, 0, *(this + 2) - 1) != 0 )
      return 0;
  }
  else
  {
    v3 = 0;
    for ( i = 9; i < 137; i += 32 )
    {
      if ( sub_484DB0(this, i, i + 31) == 0 )
        break;
      ++v3;
    }
    if ( v3 == 4 )
      return 0;
  }
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  v6 = *(uint32_t *)(dword_8F7C08 + 648);
  if ( v6 != 0 && *(uint8_t *)(v6 + 284) != 0 && *(uint8_t *)(v6 + 285) != 0 )
    return 0;
  sub_423200(dword_8F7B08, 20);
  v7[0] = *(uint8_t *)this;
  sub_423290(v7, 1);
  sub_423380(dword_8F7B08);
  sub_484880(this, 9);
  return 1;
}



// ------------------------------------------------------------
// 0x486D40 sub_486D40
// ------------------------------------------------------------
char /*thiscall*/ sub_486D40(uint32_t *this, int a2)
{
  int v3; // ecx
  uint32_t *v4; // esi
  int v5; // eax

  v3 = *(this + 5);
  if ( v3 != 0 && (*(this + 6) - v3) >> 2 >= 1
    || *this != 0
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 3) + 4) + 44))(*(uint32_t *)(*(this + 3) + 4)) == 0
    || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
  {
    return 0;
  }
  if ( (uint8_t)sub_49BE70(*((uint32_t *)dword_8F8528 + 605)) != 0 )
  {
    v4 = *((uint32_t **)dword_8F8528 + 7);
    v5 = sub_422E70(3015);
    sub_43BEE0(v4, v5, -6567706, 0, -1);
    return 0;
  }
  sub_423200(dword_8F7B08, 44);
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 10);
  return 1;
}



// ------------------------------------------------------------
// 0x486E00 sub_486E00
// ------------------------------------------------------------
char /*thiscall*/ sub_486E00(uint32_t *this, int a2)
{
  int v3; // ecx

  v3 = *(this + 5);
  if ( v3 != 0 && (*(this + 6) - v3) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  sub_423200(dword_8F7B08, 28);
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 11);
  return 1;
}



// ------------------------------------------------------------
// 0x486E80 sub_486E80
// ------------------------------------------------------------
char /*thiscall*/ sub_486E80(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v6; // edi
  int v7; // ecx

  v4 = *(this + 5);
  if ( v4 != 0 && (*(this + 6) - v4) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  sub_423200(dword_8F7B08, 83);
  v6 = a2;
  sub_423290(&a2, 2);
  if ( v6 >= *(this + 2) )
    v7 = 0;
  else
    v7 = *(uint32_t *)(*(this + 3) + 4 * v6);
  a2 = *(uint16_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4);
  sub_423290(&a2, 2);
  a2 = a3;
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 12);
  return 1;
}



// ------------------------------------------------------------
// 0x486F40 sub_486F40
// ------------------------------------------------------------
char /*thiscall*/ sub_486F40(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v6; // edi
  int v7; // ecx

  v4 = *(this + 5);
  if ( v4 != 0 && (*(this + 6) - v4) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  sub_423200(dword_8F7B08, 84);
  v6 = a2;
  sub_423290(&a2, 2);
  if ( v6 >= *(this + 2) )
    v7 = 0;
  else
    v7 = *(uint32_t *)(*(this + 3) + 4 * v6);
  a2 = *(uint16_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4);
  sub_423290(&a2, 2);
  a2 = a3;
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 13);
  return 1;
}



// ------------------------------------------------------------
// 0x487000 sub_487000
// ------------------------------------------------------------
char /*thiscall*/ sub_487000(uint32_t *this, int a2)
{
  int v3; // ecx

  v3 = *(this + 5);
  if ( v3 != 0 && (*(this + 6) - v3) >> 2 >= 1 || *this != 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    return 0;
  sub_423200(dword_8F7B08, 32);
  sub_423290(&a2, 2);
  sub_423380(dword_8F7B08);
  sub_484880(this, 14);
  return 1;
}



// ------------------------------------------------------------
// 0x487080 sub_487080
// ------------------------------------------------------------
void /*thiscall*/ sub_487080(int *this)
{
  int v1; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6[4]; // [esp+1Ch] [ebp-10h] BYREF

  v1 = 0;
  v3 = *(this + 2);
  v6[3] = 0;
  v6[0] = 0;
  if ( v3 > 0 )
  {
    do
    {
      v4 = *(uint32_t *)(*(this + 3) + 4 * v1);
      if ( v4 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4) + 52) != 0 )
        sub_430C80(nullptr, 1, (int)v6);
      v5 = *(this + 2);
      v6[0] = ++v1;
    }
    while ( v1 < v5 );
  }
}



// ------------------------------------------------------------
// 0x4871A0 sub_4871A0
// ------------------------------------------------------------
char /*thiscall*/ sub_4871A0(uint32_t *this, int a2)
{
  int v2; // ebx
  int v5; // esi
  uint32_t *v6; // esi
  int v7; // eax
  int v8; // eax

  v2 = dword_8F7C04;
  if ( dword_8F7C04 == 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF || a2 >= *(this + 2) )
    return 0;
  v5 = *(uint32_t *)(*(this + 3) + 4 * a2);
  if ( v5 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 20))(v5, 1) == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 804))(v2, v5) == 0 )
  {
    return 0;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 104))(v5) != 0 )
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);
    v7 = sub_422E70(416);
    sub_43BEE0(v6, v7, -6567706, 0, -1);
    sub_432EA0("ALERT_1", -1, 0, 0);
    return 0;
  }
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 140))(v5);
  if ( v8 == 1 )
    return sub_486B40(this, a2, 1);
  if ( v8 != 2 )
    return v8 != 0;
  if ( dword_8F7C04 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 136))(v5, dword_8F7C04, 2, -1);
  return 1;
}



// ------------------------------------------------------------
// 0x4872A0 sub_4872A0
// ------------------------------------------------------------
char /*thiscall*/ sub_4872A0(int *this, int a2)
{
  int v3; // esi
  int *v4; // eax

  v3 = *(uint32_t *)(*(this + 3) + 4 * a2);
  if ( v3 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 20))(v3, 2) != 0 )
  {
    v4 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3);
    return sub_486820(this, a2, *v4, 1);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 20))(v3, 1) != 0 )
    return sub_4871A0(this, a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x487310 sub_487310
// ------------------------------------------------------------
int /*thiscall*/ sub_487310(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 137) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 137) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 137) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 137) == 0 );
        if ( *(uint8_t *)(result + 137) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 137) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x487390 sub_487390
// ------------------------------------------------------------
int */*thiscall*/ sub_487390(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 137) == 0 )
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
// 0x4873D0 sub_4873D0
// ------------------------------------------------------------
int **/*thiscall*/ sub_4873D0(int **this, int **a2, uint32_t *a3)
{
  int *v5; // eax
  int *v6; // esi
  int *v8; // [esp+18h] [ebp+Ch]

  v5 = sub_487390(this, a3);
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
// 0x487420 sub_487420
// ------------------------------------------------------------
int /*thiscall*/ sub_487420(uint32_t *this, int a2)
{
  uint32_t *v3; // esi
  int *v4; // eax
  int *v5; // esi
  int *v6; // eax
  int v7; // eax
  int *v9; // [esp+8h] [ebp-4h] BYREF

  v3 = this + 1;
  v4 = sub_487390(this + 1, &a2);
  v5 = (int *)v3[1];
  v9 = v4;
  if ( v4 == v5 || a2 < v4[3] )
  {
    a2 = (int)v5;
    v6 = &a2;
  }
  else
  {
    v6 = (int *)&v9;
  }
  v7 = *v6;
  if ( v7 == *(this + 2) )
    return 0;
  else
    return v7 + 16;
}



// ------------------------------------------------------------
// 0x487470 sub_487470
// ------------------------------------------------------------
int /*thiscall*/ sub_487470(int this, size_t *a2)
{
  qmemcpy((void *)this, a2, 0x4Cu);
  *(uint32_t *)(this + 100) = 15;
  *(uint32_t *)(this + 96) = 0;
  *(uint8_t *)(this + 80) = 0;
  sub_4014D0((size_t *)(this + 76), a2 + 19, 0, 0xFFFFFFFF);
  *(uint32_t *)(this + 104) = a2[26];
  *(uint32_t *)(this + 108) = a2[27];
  *(uint32_t *)(this + 112) = a2[28];
  return this;
}



// ------------------------------------------------------------
// 0x4874D0 sub_4874D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4874D0(uint32_t *this)
{
  uint32_t *v2; // eax
  int i; // ecx

  *this = 0;
  v2 = this + 9;
  for ( i = 8; i != 0; --i )
  {
    *(v2 - 8) = 255;
    *v2++ = 0xFFFF;
  }
  *(this + 25) = 15;
  *(this + 24) = 0;
  *((uint8_t *)this + 80) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  sub_4015C0(this + 19, szPassword, 0);
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 26) = -1;
  return this;
}



// ------------------------------------------------------------
// 0x487560 sub_487560
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_487560(uint32_t *this, int a2)
{
  *this = &CNPvpRoom::`vftable';
  sub_4874D0(this + 1);
  nullsub_3(this);
  unknown_libname_7(a2);
  return this;
}



// ------------------------------------------------------------
// 0x4875C0 sub_4875C0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4875C0(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x8Cu);
  v6 = v5;
  v8[4] = v5;
  v8[8] = (void *)1;
  v8[3] = v5;
  if ( v5 != nullptr )
  {
    *v5 = a1;
    v5[1] = a2;
    v5[2] = a3;
    v5[3] = *a4;
    v5[4] = &CNPvpRoom::`vftable';
    sub_487470((int)(v5 + 5), a4 + 2);
    *((uint8_t *)v6 + 136) = a5;
    *((uint8_t *)v6 + 137) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x487670 sub_487670
// ------------------------------------------------------------
int /*thiscall*/ sub_487670(uint32_t *this, int ArgList)
{
  uint32_t *v3; // esi
  int *v4; // eax
  int *v5; // ecx
  int v6; // edx
  int *p_ArgList; // eax
  int v8; // eax
  int *v10; // [esp+8h] [ebp-4h] BYREF

  v3 = this + 1;
  v4 = sub_487390(this + 1, &ArgList);
  v5 = (int *)v3[1];
  v6 = ArgList;
  v10 = v4;
  if ( v4 == v5 || ArgList < v4[3] )
  {
    ArgList = (int)v5;
    p_ArgList = &ArgList;
  }
  else
  {
    p_ArgList = (int *)&v10;
  }
  v8 = *p_ArgList;
  if ( v8 == *(this + 2) )
    return off_77F3FC(aCriticalError_9, v6);
  else
    return sub_436940(&ArgList, v8);
}



// ------------------------------------------------------------
// 0x4876E0 sub_4876E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4876E0(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
{
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // esi
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

  if ( (unsigned int)*(this + 2) >= 0x2108420 )
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
  v6 = sub_4875C0(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  v11 = v6;
  if ( *(uint8_t *)(v6[1] + 136) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 136) != 0 )
        {
          if ( v11 == (uint32_t *)v12[2] )
          {
            v11 = (uint32_t *)*v10;
            sub_433000(*v10);
          }
          *(uint8_t *)(v11[1] + 136) = 1;
          *(uint8_t *)(*(uint32_t *)(v11[1] + 4) + 136) = 0;
          sub_4330C0(*(uint32_t *)(v11[1] + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 136) != 0 )
      {
        if ( v11 == (uint32_t *)*v12 )
        {
          v11 = (uint32_t *)*v10;
          sub_4330C0(*v10);
        }
        *(uint8_t *)(v11[1] + 136) = 1;
        *(uint8_t *)(*(uint32_t *)(v11[1] + 4) + 136) = 0;
        sub_433000(*(uint32_t *)(v11[1] + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 136) = 1;
      *(uint8_t *)(v14 + 136) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 136) = 0;
      v11 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = v11 + 1;
      if ( *(uint8_t *)(v11[1] + 136) != 0 )
      {
        v6 = v22;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 136) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4878B0 sub_4878B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4878B0(uint32_t *this)
{
  uint32_t *v1; // esi
  uint32_t *v2; // eax

  v1 = this + 1;
  sub_436CA0(*(void **)(*(this + 2) + 4));
  *(uint32_t *)(v1[1] + 4) = v1[1];
  v2 = (uint32_t *)v1[1];
  v1[2] = 0;
  *v2 = v2;
  *(uint32_t *)(v1[1] + 8) = v1[1];
  return sub_48F890(0);
}



// ------------------------------------------------------------
// 0x4878F0 sub_4878F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4878F0(int *this, int a2, uint32_t *a3)
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
  if ( *((uint8_t *)v6 + 137) == 0 )
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
    while ( *((uint8_t *)v6 + 137) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4876E0(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_487310(&a3);
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
    v12 = *sub_4876E0(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4879B0 sub_4879B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4879B0(int *this, int a2)
{
  int v2; // ebx
  int result; // eax
  uint32_t *v5; // esi
  uint32_t *v6; // eax
  int *v7; // edi
  int *v8; // eax
  int *v9; // edi
  void **p_Block; // eax
  int v11; // [esp+Ch] [ebp-90h] BYREF
  void **v12; // [esp+10h] [ebp-8Ch] BYREF
  uint8_t v13[116]; // [esp+14h] [ebp-88h] BYREF
  uint8_t v14[4]; // [esp+88h] [ebp-14h] BYREF
  void *Block; // [esp+8Ch] [ebp-10h] BYREF
  int v16; // [esp+98h] [ebp-4h]

  v2 = a2;
  result = sub_487420(this, a2);
  v5 = nullptr;
  if ( result == 0 )
  {
    v6 = operator new(0x78u);
    Block = v6;
    v16 = 0;
    if ( v6 != nullptr )
      v5 = sub_487560(v6, v2);
    v16 = -1;
    v11 = v2;
    v12 = &CNPvpRoom::`vftable';
    sub_487470((int)v13, v5 + 1);
    v7 = this + 1;
    v16 = 1;
    sub_4878F0(v7, (int)v14, &v11);
    v16 = -1;
    sub_433FB0(&v12);
    if ( v5 != nullptr )
      (*(void (/*thiscall*/ **)(uint32_t *, int))*v5)(v5, 1);
    v8 = sub_487390(v7, &a2);
    v9 = (int *)v7[1];
    a2 = (int)v8;
    if ( v8 == v9 || v2 < v8[3] )
    {
      Block = v9;
      p_Block = &Block;
    }
    else
    {
      p_Block = (void **)&a2;
    }
    return (int)*p_Block + 16;
  }
  return result;
}



// ------------------------------------------------------------
// 0x487AB0 sub_487AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_487AB0(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    *(uint32_t *)(this + 36) = 0;
    *(uint32_t *)(this + 40) = 0;
    *(uint32_t *)(this + 44) = -1;
    *(uint32_t *)(this + 92) = 0;
    *(uint32_t *)(this + 96) = 2;
    *(uint8_t *)(this + 128) = 0;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 24) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x487AF0 sub_487AF0
// ------------------------------------------------------------
void /*thiscall*/ sub_487AF0(int this)
{
  *(uint32_t *)(this + 8) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x487B00 sub_487B00
// ------------------------------------------------------------
char /*thiscall*/ sub_487B00(int this)
{
  uint64_t v2; // rax
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  uint64_t v7; // rax
  int v8; // ebx

  LOBYTE(v2) = *(uint8_t *)(this + 112);
  if ( (uint8_t)v2 != 0 )
  {
    LODWORD(v2) = *(uint32_t *)(this + 96);
    if ( (uint32_t)v2 == 1 )
    {
      v3 = *(uint32_t *)(this + 124);
      v4 = sub_699000(this + 100);
      v2 = (uint64_t)sub_4049C0(0.0, 255.0, v4, v3);
      *((uint32_t *)dword_8F8528 + 621) = v2;
    }
    else if ( (uint32_t)v2 == 0 )
    {
      v5 = *(uint32_t *)(this + 124);
      v6 = sub_699000(this + 100);
      v7 = (uint64_t)sub_4049C0(255.0, 0.0, v6, v5);
      *((uint32_t *)dword_8F8528 + 621) = v7;
      v8 = *(uint32_t *)(this + 124);
      LODWORD(v2) = sub_699000(this + 100);
      if ( (int)v2 >= v8 )
      {
        *(uint32_t *)(this + 96) = 2;
        *(uint8_t *)(this + 112) = 0;
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x487BA0 sub_487BA0
// ------------------------------------------------------------
char /*thiscall*/ sub_487BA0(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  uint8_t v5; // al
  uint8_t *v6; // eax
  int i; // ecx

  sub_4AEB30(&unk_9A02B0);
  sub_433690();
  sub_4294E0(*(uint32_t *)(this + 28));
  v2 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )
    v2 = sub_45E870(pt.x, pt.y, 1);
  v3 = *(uint32_t *)(this + 92);
  if ( v3 != v2 )
  {
    if ( v3 != 0 && (uint8_t)sub_45E680(*(uint32_t *)(this + 92)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 92) + 284))(
        *(uint32_t *)(this + 92),
        0,
        0,
        1,
        2);
    *(uint32_t *)(this + 92) = v2;
  }
  if ( *(uint32_t *)(this + 92) != 0 )
  {
    v4 = sub_699000(this + 48);
    v5 = sub_42B420(100, 255, v4, 500);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(this + 92) + 284))(
      *(uint32_t *)(this + 92),
      1,
      (v5 << 24) | 0xFF9B,
      0,
      1);
  }
  sub_487B00(this);
  LOBYTE(v6) = *(uint8_t *)(this + 128);
  if ( (uint8_t)v6 == 0 )
  {
    *(uint8_t *)(this + 128) = 1;
    v6 = (uint8_t *)(dword_8F8520 + 1048692);
    for ( i = 8; i != 0; --i )
    {
      if ( *v6 == 0 )
      {
        *v6 = 1;
        v6[1] = 0;
        v6[2] = 0;
      }
      v6 += 28;
    }
  }
  return (char)v6;
}



// ------------------------------------------------------------
// 0x487CA0 sub_487CA0
// ------------------------------------------------------------
void /*thiscall*/ sub_487CA0(int this)
{
  sub_41A580((uint32_t *)(this + 54));
  sub_41A580((uint32_t *)(this + 40));
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x487D10 sub_487D10
// ------------------------------------------------------------
void /*noreturn*/ sub_487D10()
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
// 0x487D80 sub_487D80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_487D80(int this, int Src, unsigned int a3, int *a4)
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
      sub_487D10(this);
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
// 0x487F60 sub_487F60
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_487F60(int *this, int *a2)
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
    return sub_487D80((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x487FB0 sub_487FB0
// ------------------------------------------------------------
int /*thiscall*/ sub_487FB0(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 68 )
      sub_487CA0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x487FF0 sub_487FF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_487FF0(uint32_t *this, int a2)
{
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *((uint8_t *)this + 32) = 0;
  *(this + 9) = 0;
  *((uint8_t *)this + 42) = 0;
  *((uint8_t *)this + 41) = 0;
  *(this + 13) = 0;
  *(this + 12) = 0;
  *(this + 11) = 0;
  *(this + 7) = &off_6C2B88;
  *((uint8_t *)this + 40) = 1;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *this = a2;
  *(this + 1) = *(uint32_t *)(a2 + 40);
  return this;
}



// ------------------------------------------------------------
// 0x488040 sub_488040
// ------------------------------------------------------------
int /*thiscall*/ sub_488040(int this)
{
  *(uint32_t *)(this + 28) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 32) = 0;
  return sub_487FB0((int *)(this + 12));
}



// ------------------------------------------------------------
// 0x488060 sub_488060
// ------------------------------------------------------------
int /*thiscall*/ sub_488060(uint32_t *this, void *Block)
{
  void *v3; // edi
  int result; // eax
  int v5; // edx

  off_77F3FC((char *)&byte_6C8BF4, Block);
  *(this + 22) = Block;
  v3 = (void *)*(this + 8);
  if ( Block == (void *)-1 )
  {
    if ( v3 != nullptr )
    {
      nullsub_3(v3);
      sub_42E7F0(v3);
      j__free(v3);
    }
    result = *(this + 7);
    *(this + 8) = 0;
    *(uint32_t *)(result + 108) = 0;
  }
  else
  {
    if ( v3 != nullptr )
    {
      nullsub_3(v3);
      sub_42E7F0(v3);
      j__free(v3);
    }
    *(this + 8) = 0;
    if ( operator new(0x1F0u) != nullptr )
      result = sub_42E8F0(*(this + 22));
    else
      result = 0;
    v5 = *(this + 7);
    *(this + 8) = result;
    *(uint32_t *)(v5 + 108) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x488160 sub_488160
// ------------------------------------------------------------
char /*thiscall*/ sub_488160(int this)
{
  int *v2; // eax
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax
  uint8_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax

  LOBYTE(v2) = *(uint8_t *)(this + 4);
  if ( (uint8_t)v2 == 0 )
  {
    *(uint8_t *)(this + 4) = 1;
    v3 = operator new(0x68u);
    if ( v3 != nullptr )
      v4 = sub_426BD0(v3);
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;
    *((uint32_t *)v4 + 17) = this + 8;
    v5 = (char *)operator new(0x558u);
    if ( v5 != nullptr )
      v6 = sub_42B7E0(v5);
    else
      v6 = nullptr;
    *(uint32_t *)(this + 28) = v6;
    sub_69A840(*((uint32_t *)v6 + 9));
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 40));
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    sub_488060((uint32_t *)this, (void *)0xFFFFFFFF);
    v7 = operator new(0x24u);
    if ( v7 != nullptr )
    {
      v7[12] = 0;
      *((uint32_t *)v7 + 2) = &off_6C2B88;
      *((uint32_t *)v7 + 4) = 0;
      v7[20] = 1;
      v7[22] = 0;
      v7[21] = 0;
      *((uint32_t *)v7 + 8) = 0;
      *((uint32_t *)v7 + 7) = 0;
      *((uint32_t *)v7 + 6) = 0;
      *((uint32_t *)v7 + 1) = 0;
      *(uint32_t *)v7 = this;
      *((uint32_t *)v7 + 1) = *(uint32_t *)(this + 40);
    }
    else
    {
      v7 = nullptr;
    }
    *(uint32_t *)(this + 16) = v7;
    v8 = operator new(0x38u);
    if ( v8 != nullptr )
      v9 = sub_487FF0(v8, this);
    else
      v9 = nullptr;
    *(uint32_t *)(this + 20) = v9;
    v2 = (int *)operator new(8u);
    if ( v2 != nullptr )
    {
      v2[1] = 0;
      *v2 = this;
      v2[1] = *(uint32_t *)(this + 40);
      *(uint32_t *)(this + 24) = v2;
    }
    else
    {
      *(uint32_t *)(this + 24) = 0;
      LOBYTE(v2) = 0;
    }
  }
  return (char)v2;
}



// ------------------------------------------------------------
// 0x488300 sub_488300
// ------------------------------------------------------------
void /*thiscall*/ sub_488300(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // edi
  void *v4; // edi
  void *v5; // edi
  void *v6; // edi
  void *v7; // edi
  void *v8; // edi
  void *v9; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *(uint8_t *)(this + 4) = 0;
    if ( v2 != nullptr )
      (**v2)(v2, 1);
    v3 = *(void **)(this + 28);
    *(uint32_t *)(this + 12) = 0;
    if ( v3 != nullptr )
    {
      sub_42BD40(v3);
      j__free(v3);
    }
    v4 = *(void **)(this + 32);
    *(uint32_t *)(this + 28) = 0;
    if ( v4 != nullptr )
    {
      sub_42E940(v4);
      j__free(v4);
    }
    v5 = *(void **)(this + 36);
    *(uint32_t *)(this + 32) = 0;
    if ( v5 != nullptr )
    {
      sub_42EDE0(v5);
      j__free(v5);
    }
    v6 = *(void **)(this + 40);
    *(uint32_t *)(this + 36) = 0;
    if ( v6 != nullptr )
    {
      sub_42C770(v6);
      j__free(v6);
    }
    v7 = *(void **)(this + 16);
    *(uint32_t *)(this + 40) = 0;
    if ( v7 != nullptr )
    {
      sub_487AF0((int)v7);
      j__free(v7);
    }
    v8 = *(void **)(this + 20);
    *(uint32_t *)(this + 16) = 0;
    if ( v8 != nullptr )
    {
      sub_488040((int)v8);
      j__free(v8);
    }
    v9 = *(void **)(this + 24);
    *(uint32_t *)(this + 20) = 0;
    if ( v9 != nullptr )
      j__free(v9);
    *(uint32_t *)(this + 24) = 0;
  }
}



// ------------------------------------------------------------
// 0x4883E0 sub_4883E0
// ------------------------------------------------------------
int /*cdecl*/ sub_4883E0(int a1, int a2)
{
  return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 48) + 16))(*(uint32_t *)(a1 + 48), a2);
}



// ------------------------------------------------------------
// 0x488400 sub_488400
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_488400(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C8C08;
  return this;
}



// ------------------------------------------------------------
// 0x488410 sub_488410
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_488410(uint8_t *Block, char a2)
{
  sub_401000(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x488440 sub_488440
// ------------------------------------------------------------
DWORD /*usercall*/ sub_488440@<eax>(int a1@<esi>)
{
  char *v1; // eax
  char *v2; // eax
  char v3; // cl
  DWORD result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char *Block; // [esp+0h] [ebp-54h]
  void *Blocka; // [esp+0h] [ebp-54h]
  char Buffer[64]; // [esp+4h] [ebp-50h] BYREF
  int v13; // [esp+44h] [ebp-10h]
  int v14; // [esp+50h] [ebp-4h]

  v13 = dword_796E50;
  SetCursor(nullptr);
  if ( dword_99FD64 == 0 )
  {
    sprintf(Buffer, "sprite/nowloading.img");
    v1 = (char *)operator new(0x68u);
    Block = v1;
    v14 = 0;
    v2 = v1 != nullptr ? sub_4198A0(v1, dword_79C0A4, Buffer) : nullptr;
    dword_99FD64 = (int)v2;
    v3 = v2[4];
    v14 = -1;
    if ( v3 == 0 )
      off_77F3FC("IMAGE LOAD ERROR [%s]", Buffer);
  }
  result = timeGetTime() - dword_99FD7C;
  if ( result > 0x64 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0, a1);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0, Block);
    v5 = sub_418DD0((uint32_t *)dword_99FD64, 0);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v5 + 152))(v5, 0, 0, dword_79C0B0);
    Blocka = (void *)dword_99FD78;
    v6 = sub_418DD0((uint32_t *)dword_99FD64, 2u);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, void *, int, int, int))(*(uint32_t *)v6 + 128))(
        v6,
        278,
        53,
        dword_79C0B0,
        1065353216,
        1065353216,
        Blocka,
        -1,
        1333788672,
        1333788672);
    dword_99FD7C = timeGetTime();
    *(float *)&dword_99FD78 = *(float *)&dword_99FD78 + 0.0099999998;
    v7 = sub_418DD0((uint32_t *)dword_99FD64, 1u);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, 194, 60, dword_79C0B0);
    v8 = sub_418DD0((uint32_t *)dword_99FD64, 3u);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
        v8,
        79,
        292,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1929379841,
        1333788672,
        1333788672);
    v9 = sub_418DD0((uint32_t *)dword_99FD68, 0);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, 79, 292, dword_79C0B0);
    if ( dword_99FCCC != 0 )
      sub_488970(dword_99FD6C);
    (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0, Blocka);
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x488670 sub_488670
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_488670(uint32_t *a1)
{
  a1[12] = 0;
  a1[13] = 0;
  a1[14] = 640;
  a1[15] = 480;
  return a1;
}



// ------------------------------------------------------------
// 0x488690 sub_488690
// ------------------------------------------------------------
void /*cdecl*/ sub_488690(uint32_t *a1, const char *a2, char *SubStr, int a4)
{
  int v4; // ecx
  unsigned int v5; // eax
  const char *v6; // ebx
  const char *v7; // edi
  char *v8; // eax
  size_t v9; // eax
  size_t v10; // ebx
  int v11; // ecx
  unsigned int v12; // edx
  unsigned int **v13; // edi
  void *v14; // [esp+4h] [ebp-118h] BYREF
  int i; // [esp+8h] [ebp-114h]
  char Destination[256]; // [esp+Ch] [ebp-110h] BYREF
  int v17; // [esp+10Ch] [ebp-10h]
  int v18; // [esp+118h] [ebp-4h]

  v17 = dword_796E50;
  sub_4017E0((int)a1);
  for ( i = 0; ; i += v10 + strlen(SubStr) )
  {
    if ( a4 != 0 )
    {
      v4 = a1[1];
      v5 = v4 != 0 ? (a1[2] - v4) >> 2 : 0;
      if ( v5 >= a4 - 1 )
        break;
    }
    v6 = a2;
    v7 = &a2[i];
    v8 = strstr(&a2[i], SubStr);
    if ( v8 == nullptr )
      goto LABEL_19;
    v9 = &v8[-i] - v6;
    v10 = v9;
    if ( v9 != 0 )
    {
      strncpy(Destination, v7, v9);
      Destination[v10] = 0;
      v14 = nullptr;
      sub_41BFE0(&v14, Destination);
      v11 = a1[1];
      v18 = 0;
      if ( v11 != 0 )
        v12 = (a1[2] - v11) >> 2;
      else
        v12 = 0;
      if ( v11 != 0 && v12 < (a1[3] - v11) >> 2 )
      {
        v13 = (unsigned int **)a1[2];
        sub_41FFE0(v13, 1, (unsigned int **)&v14);
        a1[2] = v13 + 1;
      }
      else
      {
        sub_4206D0(a1[2], 1, &v14);
      }
      v18 = -1;
      sub_41B010(&v14);
      off_77F3FC(Destination);
    }
  }
  v6 = a2;
LABEL_19:
  if ( strlen(&v6[i]) != 0 )
  {
    a2 = nullptr;
    sub_41BFE0((void **)&a2, &v6[i]);
    v18 = 1;
    sub_420BB0(&a2);
    v18 = -1;
    sub_41B010((void **)&a2);
  }
}



// ------------------------------------------------------------
// 0x488870 sub_488870
// ------------------------------------------------------------
int /*thiscall*/ sub_488870(uint32_t *this)
{
  *(this + 4293) = 0;
  *(this + 4034) = 0;
  *(this + 4035) = 0;
  *(this + 1) = 0;
  *(this + 4292) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x488890 sub_488890
// ------------------------------------------------------------
int /*thiscall*/ sub_488890(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  int v4; // esi
  uint32_t *v5; // ecx
  int v6; // edx
  int v7; // edi
  int result; // eax
  int v9; // edx
  int *i; // esi
  uint32_t v11[18]; // [esp+Ch] [ebp-48h] BYREF

  v2 = *(this + 4292);
  v11[17] = dword_796E50;
  v3 = 1;
  v4 = 0;
  if ( v2 >= 1 )
  {
    v5 = this + 4229;
    do
    {
      if ( (int)*(v5 - 192) > 10 )
      {
        *((uint8_t *)&v11[1] + v3) = 0;
      }
      else
      {
        v4 += *v5;
        *((uint8_t *)&v11[1] + v3) = 1;
      }
      ++v3;
      ++v5;
    }
    while ( v3 <= v2 );
  }
  v11[0] = rand();
  v6 = sub_4D33A0(v11) % v4;
  v7 = *(this + 4292);
  result = 1;
  v9 = v6 + 1;
  if ( v7 < 1 )
    return 0;
  for ( i = this + 4229; v9 > *i; ++i )
  {
    v9 -= *i;
    if ( ++result > v7 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x488940 sub_488940
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488940(uint32_t *this)
{
  uint32_t *result; // eax
  int i; // ecx

  *(this + 1) = 0;
  result = this + 4100;
  for ( i = 64; i != 0; --i )
  {
    *(result - 64) = 0;
    *result = 0;
    result[64] = 0;
    result[128] = 0;
    ++result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x488970 sub_488970
// ------------------------------------------------------------
HGDIOBJ /*thiscall*/ sub_488970(uint32_t *this)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ecx
  int v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // eax
  HGDIOBJ result; // eax
  uint8_t v10[4]; // [esp+8h] [ebp-40h] BYREF
  int v11; // [esp+Ch] [ebp-3Ch]
  int v12; // [esp+14h] [ebp-34h]
  int v13; // [esp+18h] [ebp-30h]
  int v14; // [esp+1Ch] [ebp-2Ch]
  int v15; // [esp+20h] [ebp-28h]
  int v16; // [esp+24h] [ebp-24h]
  int v17; // [esp+28h] [ebp-20h]
  int v18; // [esp+2Ch] [ebp-1Ch]
  int v19; // [esp+30h] [ebp-18h]
  HGDIOBJ ho; // [esp+34h] [ebp-14h]
  int v21; // [esp+38h] [ebp-10h]
  int v22; // [esp+44h] [ebp-4h]

  v21 = dword_99FCCC;
  v10[0] = 0;
  v10[1] = 0;
  v10[2] = 0;
  v10[3] = 0;
  v12 = 0;
  v13 = 6;
  v14 = 12;
  v15 = 0;
  v16 = 1600;
  v17 = 0;
  v18 = 0;
  v19 = 0;
  ho = nullptr;
  v11 = -16777216;
  v2 = *(uint32_t *)dword_79C0B0;
  v22 = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(v2 + 72))(dword_79C0B0, v10);
  v3 = 28 * *(this + 1);
  if ( *(uint32_t *)((char *)this + v3 + 32) < 0x10u )
    v4 = (int)this + v3 + 12;
  else
    v4 = *(uint32_t *)((char *)this + v3 + 12);
  (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    245,
    309,
    -13523457,
    "%s",
    v4);
  v5 = 28 * *(this + 1);
  v6 = *(uint32_t *)((char *)this + v5 + 7200);
  v7 = (int)this + v5 + 7176;
  if ( v6 < 0x10 )
    v8 = v7 + 4;
  else
    v8 = *(uint32_t *)(v7 + 4);
  (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    245,
    332,
    -2428169,
    "%s",
    v8);
  (*(void (/*cdecl*/ **)(int, int, int, int, const char *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    525,
    421,
    -328966,
    "Ver. 200606130k0515");
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  result = ho;
  if ( ho != nullptr )
    return (HGDIOBJ)DeleteObject(ho);
  return result;
}



// ------------------------------------------------------------
// 0x488AB0 sub_488AB0
// ------------------------------------------------------------
char /*thiscall*/ sub_488AB0(uint32_t *this)
{
  uint32_t *v1; // edi
  char result; // al
  int v3; // esi
  int v4; // ecx
  const char *v5; // esi
  int v6; // eax
  int v8; // [esp+8h] [ebp-4Ch]
  uint8_t v9[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  unsigned int v11; // [esp+20h] [ebp-34h]
  unsigned int v12; // [esp+24h] [ebp-30h]
  uint8_t v13[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v14; // [esp+2Ch] [ebp-28h] BYREF
  unsigned int v15; // [esp+3Ch] [ebp-18h]
  unsigned int v16; // [esp+40h] [ebp-14h]
  int v17; // [esp+44h] [ebp-10h]
  int v18; // [esp+50h] [ebp-4h]

  v1 = this;
  v17 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)"Etc/TutorialTip.etc");
  if ( result != 0 )
  {
    v16 = 15;
    v15 = 0;
    LOBYTE(v14) = 0;
    v18 = 1;
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
    v3 = v8;
    if ( (uint8_t)sub_443430(v13) != 0 )
    {
      while ( 1 )
      {
        if ( v15 == 0 )
          goto LABEL_12;
        v4 = v15;
        if ( v15 >= 4 )
          v4 = 4;
        v5 = (const char *)v14;
        if ( v16 < 0x10 )
          v5 = (const char *)&v14;
        if ( memcmp(v5, "[no]", v4) != 0 || v15 != 4 )
          break;
        v1 = this;
        v3 = sub_4423D0(nullptr);
        v8 = v3;
LABEL_27:
        if ( (uint8_t)sub_443430(v13) == 0 )
          goto LABEL_28;
      }
      v3 = v8;
      v1 = this;
LABEL_12:
      if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[priority]", 0xAu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[level]", 7u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v13, 0, v15, "[title]", 7u) != 0
            && sub_40BF00((std::_String_base *)v13, 0, v15, "[content]", 9u) != 0
            && sub_40BF00((std::_String_base *)v13, 0, v15, "[image]", 7u) != 0 )
          {
            if ( (uint8_t)sub_423300(v13, "[end]") != 0 )
              goto LABEL_28;
          }
          else
          {
            sub_443370();
          }
        }
        else
        {
          v1[v3 + 4036] = sub_4423D0(nullptr);
        }
      }
      else
      {
        sub_443370();
        if ( sub_40BF00((std::_String_base *)v9, 0, v11, "A", 1u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v9, 0, v11, "B", 1u) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v9, 0, v11, "C", 1u) == 0 )
              v1[v3 + 4228] = 1;
          }
          else
          {
            v1[v3 + 4228] = 2;
          }
        }
        else
        {
          v1[v3 + 4228] = 3;
        }
      }
      goto LABEL_27;
    }
LABEL_28:
    v1[4292] = v3;
    v6 = sub_488890(v1);
    v1[1] = v6;
    if ( v6 == 1 || v6 == 26 )
      v1[1] = 25;
    if ( v12 >= 0x10 )
      j__free(Block);
    v11 = 0;
    LOBYTE(Block) = 0;
    v12 = 15;
    if ( v16 >= 0x10 )
      j__free(v14);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x488D90 sub_488D90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488D90(uint32_t *this, int a2, int a3, int a4, int a5, int a6, char a7, int a8)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  *(this + 4) = a6;
  *((uint8_t *)this + 20) = a7;
  *(this + 6) = a8;
  return this;
}



// ------------------------------------------------------------
// 0x488DD0 sub_488DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_488DD0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 56;
  return result;
}



// ------------------------------------------------------------
// 0x488E00 sub_488E00
// ------------------------------------------------------------
int /*stdcall*/ sub_488E00(int a1, int a2, int a3)
{
  sub_4FF0A0(a1, a2, a3);
  return a1 + 28 * a2;
}



// ------------------------------------------------------------
// 0x488E30 sub_488E30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_488E30(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
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
// 0x488FE0 sub_488FE0
// ------------------------------------------------------------
void /*thiscall*/ sub_488FE0(int *this, int a2, unsigned int a3, void *Block)
{
  int v5; // edi
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // edi
  int v13; // eax
  unsigned int v14; // esi
  void *v15; // ecx
  int v17; // edx
  int v18; // [esp-18h] [ebp-50h]
  int v19; // [esp-Ch] [ebp-44h]
  int v20; // [esp-8h] [ebp-40h]
  int v21; // [esp+0h] [ebp-38h] BYREF
  uint32_t v22[8]; // [esp+Ch] [ebp-2Ch] BYREF
  int v23; // [esp+34h] [ebp-4h]
  int v24; // [esp+40h] [ebp+8h]
  int v25; // [esp+44h] [ebp+Ch]
  char *Blocka; // [esp+48h] [ebp+10h]
  void *Blockb; // [esp+48h] [ebp+10h]

  qmemcpy(v22, Block, 0x1Cu);
  v5 = *(this + 1);
  v22[7] = &v21;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 28;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 28;
    else
      v8 = 0;
    if ( 153391689 - v8 < a3 )
      sub_4735F0(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 28;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v15 = (void *)*(this + 2);
      Blockb = v15;
      if ( ((int)v15 - a2) / 28 >= a3 )
      {
        v24 = (int)v15 - 28 * a3;
        *(this + 2) = sub_472DB0(v24, v15, v15);
        sub_4FF020(a2, v24, Blockb);
        sub_4FEFA0(a2, a2 + 28 * a3, v22);
      }
      else
      {
        sub_472DB0(a2, v15, a2 + 28 * a3);
        v20 = a3 - (*(this + 2) - a2) / 28;
        v19 = *(this + 2);
        v23 = 2;
        sub_488E00(v19, v20, (int)v22);
        v17 = 28 * a3 + *(this + 2);
        *(this + 2) = v17;
        sub_4FEFA0(a2, v17 - 28 * a3, v22);
      }
    }
    else
    {
      if ( 153391689 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 28;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_52AEF0(this);
      v12 = 28 * v10;
      Blocka = (char *)operator new(28 * v10);
      v18 = *(this + 1);
      v23 = 0;
      v25 = sub_472DB0(v18, a2, Blocka);
      sub_4FF0A0(v25, a3, v22);
      sub_472DB0(a2, *(this + 2), 28 * a3 + v25);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 28;
      v14 = v13 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v12];
      *(this + 2) = (int)&Blocka[28 * v14];
      *(this + 1) = (int)Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x4892B0 sub_4892B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4892B0(uint32_t *this, int a2, uint32_t *a3)
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
      v10 = *sub_488E30(this, &a3, 1, v5, (int)v3);
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
    v12 = *sub_488E30(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x489370 sub_489370
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_489370(int *this, uint32_t *a2, int a3, void *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 28 != 0 )
    v6 = (a3 - v5) / 28;
  else
    v6 = 0;
  sub_488FE0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 28 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4893E0 sub_4893E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4893E0(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_488E30((uint32_t *)this, a2, 1, *(uint32_t **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_488E30((uint32_t *)this, a2, 1, a3, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_488E30((uint32_t *)this, a2, 0, v8, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_4A3B30(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C5E0((int *)&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4892B0((uint32_t *)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 21) != 0 )
      sub_488E30((uint32_t *)this, a2, 0, a3, (int)v7);
    else
      sub_488E30((uint32_t *)this, a2, 1, a4, (int)v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 21) != 0 )
      sub_488E30((uint32_t *)this, a2, 0, a4, (int)v7);
    else
      sub_488E30((uint32_t *)this, a2, 1, a3, (int)v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x489540 sub_489540
// ------------------------------------------------------------
int /*cdecl*/ sub_489540(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_4ED3F0(v4, v3);
    v3 += 16;
    v4 += 16;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x489580 sub_489580
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_489580(int *this, void *Block)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 28;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 28 )
    return sub_489370(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_4FF0A0(v5, 1, Block);
  *(this + 2) = v5 + 28;
  return result;
}



// ------------------------------------------------------------
// 0x489610 sub_489610
// ------------------------------------------------------------
int /*thiscall*/ sub_489610(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  v2 = (uint32_t *)*(this + 1);
  v3 = (int *)v2[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( v3[3] >= *a2 )
    {
      v2 = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( v2 != (uint32_t *)*(this + 1) && *a2 >= v2[3] )
    return (int)(v2 + 4);
  v5[0] = *a2;
  v5[1] = 0;
  return *sub_4893E0((int)this, &a2, v2, v5) + 16;
}



// ------------------------------------------------------------
// 0x489690 sub_489690
// ------------------------------------------------------------
int /*cdecl*/ sub_489690(int a1, int a2, int a3)
{
  return sub_489540(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4896B0 sub_4896B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4896B0(int a1, int a2)
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_489610(&dword_99FBA4, &a1);
  *result = a2;
  return result;
}



// ------------------------------------------------------------
// 0x4896D0 sub_4896D0
// ------------------------------------------------------------
int */*thiscall*/ sub_4896D0(int *this, int *a2, int a3, int a4)
{
  int v5; // edi

  if ( a3 != a4 )
  {
    v5 = sub_489540(a4, *(this + 2), a3);
    sub_42CC00(v5, *(this + 2));
    *(this + 2) = v5;
  }
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x489720 sub_489720
// ------------------------------------------------------------
void /*thiscall*/ sub_489720(int *this, unsigned int a2, char a3, void *Block, int a5, int a6)
{
  int v6; // esi
  unsigned int v7; // edx
  int v8; // edx

  v6 = *(this + 1);
  if ( v6 != 0 )
    v7 = (*(this + 2) - v6) >> 4;
  else
    v7 = 0;
  if ( v7 >= a2 )
  {
    if ( v6 != 0 && a2 < (*(this + 2) - v6) >> 4 )
      sub_4896D0(this, (int *)&a2, v6 + 16 * a2, *(this + 2));
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) >> 4;
    else
      v8 = 0;
    sub_474DE0((int)this, (void *)*(this + 2), a2 - v8, &a3);
  }
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x4897D0 sub_4897D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4897D0(int *this, unsigned int a2)
{
  char v2; // [esp+0h] [ebp-14h] BYREF
  char *v3; // [esp+10h] [ebp-4h]

  v3 = &v2;
  sub_489720(this, a2, v2, nullptr, 0, 0);
}



// ------------------------------------------------------------
// 0x489800 sub_489800
// ------------------------------------------------------------
void /*thiscall*/ sub_489800(uint32_t *this)
{
  unsigned int v1; // edx
  int v2; // ecx
  const char *p_Block; // esi
  int j; // esi
  int k; // esi
  int v6; // eax
  int m; // esi
  void *v8; // eax
  int *v9; // eax
  int v10; // edx
  void *v11; // eax
  bool v12; // zf
  void **v13; // edi
  unsigned int n; // esi
  int v15; // eax
  void *v16; // edi
  int v17; // ebx
  int v18; // esi
  int v19; // ecx
  int v20; // esi
  struct TypeDescriptor *v21; // esi
  int v22; // edi
  uint32_t *v23; // eax
  const struct TypeDescriptor_vtbl *v24; // edx
  int v25; // eax
  int v26; // edi
  int ii; // edx
  int v28; // ebx
  int v29; // eax
  uint32_t *jj; // edx
  char *v31; // esi
  int v32; // edi
  int v33; // eax
  uint32_t *v34; // ecx
  uint32_t *v35; // edx
  uint32_t *v36; // edi
  int v37; // eax
  int v38; // edi
  int v39; // esi
  int v40; // edx
  int v41; // eax
  int kk; // eax
  int v43; // eax
  uint32_t *v44; // esi
  uint32_t *v45; // eax
  uint32_t *v46; // eax
  uint32_t *v47; // eax
  uint32_t *v48; // edi
  int v49; // eax
  unsigned int v50; // esi
  int v51; // edx
  int v52; // eax
  int v53; // esi
  int v54; // ecx
  int v55; // esi
  unsigned int v56; // edx
  uint32_t *v57; // eax
  int v58; // ecx
  int v59; // eax
  int v60; // eax
  int v61; // edx
  int v62; // ecx
  unsigned int v63; // esi
  int v64; // edx
  int v65; // ecx
  int v66; // ebx
  uint8_t *v67; // esi
  uint32_t *v68; // eax
  uint8_t *v69; // ecx
  unsigned int v70; // esi
  int *v71; // ebx
  int v72; // edi
  unsigned int v73; // esi
  int v74; // eax
  int v75; // eax
  char v76; // cl
  int *v77; // eax
  int v78; // edx
  int v79; // ecx
  int v80; // eax
  int v81; // eax
  void *v82; // edx
  int v83; // edi
  int v84; // ebx
  int v85; // esi
  void *v86; // eax
  unsigned int i1; // edi
  int v88; // ecx
  int v89; // eax
  unsigned int v90; // edi
  int v91; // eax
  int *v92; // eax
  int v93; // edx
  int v94; // ebx
  unsigned int i2; // esi
  int v96; // edx
  int v97; // edx
  int v98; // edi
  int v99; // eax
  int v100; // eax
  int v101; // eax
  int i3; // edi
  int v103; // esi
  int v104; // eax
  int v105; // eax
  int v106; // edx
  char *v107; // edi
  int v108; // esi
  int v109; // ecx
  int v110; // edx
  int v111; // ecx
  int v112; // esi
  int v113; // edi
  int v114; // eax
  int v115; // edi
  int v116; // eax
  int *v117; // esi
  int v118; // edx
  void *v119; // edi
  int v120; // eax
  int v121; // eax
  int v122; // edx
  int v123; // eax
  uint32_t *v124; // ecx
  int i4; // edi
  int v126; // esi
  int v127; // eax
  int v128; // eax
  int v129; // ebx
  int i5; // edi
  int v131; // esi
  struct TypeDescriptor *v132; // eax
  uint16_t v133; // dx
  int v134; // ebx
  int i6; // edi
  int v136; // esi
  struct TypeDescriptor *v137; // eax
  int v138; // ecx
  int v139; // eax
  uint32_t *v140; // ecx
  int v141; // eax
  int v142; // ebx
  int v143; // esi
  int i7; // edi
  struct TypeDescriptor *v145; // edi
  int i8; // esi
  int v147; // eax
  int v148; // eax
  int v149; // esi
  int v150; // esi
  int v151; // esi
  int v152; // eax
  int v153; // eax
  int v154; // eax
  int v155; // eax
  int v156; // eax
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int v160; // eax
  int v161; // eax
  int v162; // eax
  int v163; // eax
  int v164; // [esp-10h] [ebp-254h] BYREF
  int v165; // [esp-Ch] [ebp-250h]
  int v166; // [esp-8h] [ebp-24Ch]
  int v167; // [esp-4h] [ebp-248h]
  uint8_t v168[64]; // [esp+Ch] [ebp-238h] BYREF
  int v169; // [esp+4Ch] [ebp-1F8h] BYREF
  char v170[14]; // [esp+50h] [ebp-1F4h] BYREF
  char v171[14]; // [esp+5Eh] [ebp-1E6h] BYREF
  char v172[14]; // [esp+6Ch] [ebp-1D8h] BYREF
  char v173[14]; // [esp+7Ah] [ebp-1CAh] BYREF
  int v174; // [esp+8Ch] [ebp-1B8h]
  int v175; // [esp+90h] [ebp-1B4h]
  int v176; // [esp+94h] [ebp-1B0h]
  uint8_t v177[64]; // [esp+98h] [ebp-1ACh] BYREF
  void *v178; // [esp+DCh] [ebp-168h]
  int v179; // [esp+E0h] [ebp-164h]
  int v180; // [esp+E4h] [ebp-160h]
  void *v181; // [esp+ECh] [ebp-158h]
  int v182; // [esp+F0h] [ebp-154h]
  int v183; // [esp+F4h] [ebp-150h]
  void *v184; // [esp+FCh] [ebp-148h]
  uint32_t *v185; // [esp+100h] [ebp-144h]
  int v186; // [esp+104h] [ebp-140h]
  void *v187; // [esp+10Ch] [ebp-138h]
  char *v188; // [esp+110h] [ebp-134h]
  int v189; // [esp+114h] [ebp-130h]
  int v190; // [esp+118h] [ebp-12Ch] BYREF
  int v191; // [esp+11Ch] [ebp-128h]
  int v192; // [esp+120h] [ebp-124h]
  int v193; // [esp+124h] [ebp-120h]
  int v194; // [esp+128h] [ebp-11Ch]
  uint32_t v195[4]; // [esp+12Ch] [ebp-118h] BYREF
  uint8_t *v196; // [esp+13Ch] [ebp-108h]
  uint32_t *v197; // [esp+140h] [ebp-104h] BYREF
  void *v198; // [esp+144h] [ebp-100h]
  int v199; // [esp+148h] [ebp-FCh]
  int v200; // [esp+14Ch] [ebp-F8h] BYREF
  int v201; // [esp+150h] [ebp-F4h]
  int v202; // [esp+154h] [ebp-F0h] BYREF
  int v203; // [esp+158h] [ebp-ECh] BYREF
  void *v204; // [esp+15Ch] [ebp-E8h]
  int v205; // [esp+160h] [ebp-E4h] BYREF
  uint32_t *v206; // [esp+164h] [ebp-E0h]
  int v207; // [esp+168h] [ebp-DCh] BYREF
  int mm; // [esp+16Ch] [ebp-D8h] BYREF
  uint32_t *v209; // [esp+170h] [ebp-D4h]
  void *nn; // [esp+174h] [ebp-D0h]
  char ArgList[4]; // [esp+178h] [ebp-CCh]
  uint32_t *i; // [esp+17Ch] [ebp-C8h] BYREF
  int v213; // [esp+180h] [ebp-C4h] BYREF
  char v214; // [esp+187h] [ebp-BDh] BYREF
  uint8_t v215[28]; // [esp+188h] [ebp-BCh] BYREF
  void *v216; // [esp+1A4h] [ebp-A0h]
  uint16_t v217[39]; // [esp+1C8h] [ebp-7Ch] BYREF
  char v218; // [esp+216h] [ebp-2Eh]
  char v219; // [esp+217h] [ebp-2Dh] BYREF
  char v220[4]; // [esp+218h] [ebp-2Ch] BYREF
  void *Block; // [esp+21Ch] [ebp-28h] BYREF
  unsigned int v222; // [esp+22Ch] [ebp-18h]
  unsigned int v223; // [esp+230h] [ebp-14h]
  int v224; // [esp+234h] [ebp-10h]
  int v225; // [esp+240h] [ebp-4h]

  v224 = dword_796E50;
  v206 = this;
  dword_8F84B0 = 0;
  v199 = 0;
  v213 = 1;
  *(uint32_t *)ArgList = 0;
  nn = nullptr;
  v204 = nullptr;
  v192 = 0;
  v194 = 0;
  v181 = nullptr;
  v182 = 0;
  v183 = 0;
  v225 = 3;
  v184 = nullptr;
  v185 = nullptr;
  v186 = 0;
  v187 = nullptr;
  v188 = nullptr;
  v189 = 0;
  v174 = 0;
  v175 = 0;
  v176 = 0;
  `eh vector constructor iterator'(v177, 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  LOBYTE(v225) = 4;
  `eh vector constructor iterator'(v168, 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  v207 = 0;
  v205 = 0;
  v193 = 1;
  v200 = 0;
  v178 = nullptr;
  v179 = 0;
  v180 = 0;
  LOBYTE(v225) = 6;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"../DebugConfig.txt") == 0 )
  {
    LOBYTE(v225) = 4;
    `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
    LOBYTE(v225) = 3;
    `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
    return;
  }
  v223 = 15;
  v222 = 0;
  LOBYTE(Block) = 0;
  LOBYTE(v225) = 7;
  v214 = 0;
  if ( (uint8_t)sub_443430(v220) == 0 )
    goto LABEL_70;
  do
  {
    v1 = v222;
    if ( v222 != 0 )
    {
      v2 = v222;
      if ( v222 >= 0xF )
        v2 = 15;
      p_Block = (const char *)Block;
      if ( v223 < 0x10 )
        p_Block = (const char *)&Block;
      if ( memcmp(p_Block, "[dungeon index]", v2) == 0 && v222 == 15 )
      {
        v199 = sub_4423D0(nullptr);
        continue;
      }
      v1 = v222;
    }
    if ( sub_40BF00((std::_String_base *)v220, 0, v1, "[map index]", 0xBu) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[path info]", 0xBu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[job]", 5u) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[grow type]", 0xBu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)v220, 0, v222, "[level]", 7u) != 0 )
            {
              if ( (uint8_t)sub_423300(v220, "[avatar]") != 0 )
              {
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(v220, "[item]") != 0 )
              {
                for ( j = sub_4423D0(&v214); v214 != 0; j = sub_4423D0(&v214) )
                {
                  v198 = (void *)sub_4423D0(nullptr);
                  v197 = (uint32_t *)j;
                  sub_474950(&v197);
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[storage]") != 0 )
              {
                for ( k = sub_4423D0(&v214); v214 != 0; k = sub_4423D0(&v214) )
                {
                  v6 = sub_4423D0(nullptr);
                  v190 = k;
                  v191 = v6;
                  sub_474950(&v190);
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[mounted equipment]") != 0 )
              {
                sub_4423D0(nullptr);
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )
                  sub_431230(&i);
              }
              else if ( (uint8_t)sub_423300(v220, "[skill]") != 0 )
              {
                sub_4423D0(nullptr);
                for ( m = sub_4423D0(&v214); v214 != 0; m = sub_4423D0(&v214) )
                {
                  v203 = sub_4423D0(nullptr);
                  v202 = m;
                  sub_474950(&v202);
                }
              }
              else if ( (uint8_t)sub_423300(v220, "[cash]") != 0 )
              {
                v207 = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(v220, "[SP]") != 0 )
              {
                v205 = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(v220, "[test user number]") != 0 )
              {
                v193 = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(v220, "[user index]") != 0 )
              {
                v200 = sub_4423D0(nullptr);
              }
              else if ( (uint8_t)sub_423300(v220, "[IP]") != 0 )
              {
                for ( i = (uint32_t *)sub_4423D0(&v214); v214 != 0; i = (uint32_t *)sub_4423D0(&v214) )
                  sub_431230(&i);
              }
            }
            else
            {
              v194 = sub_4423D0(nullptr);
            }
          }
          else
          {
            v192 = sub_4423D0(nullptr);
          }
        }
        else
        {
          v204 = (void *)sub_4423D0(nullptr);
        }
      }
      else
      {
        *(uint32_t *)ArgList = sub_4423D0(nullptr);
        nn = (void *)sub_4423D0(nullptr);
      }
    }
    else
    {
      v213 = sub_4423D0(nullptr);
    }
  }
  while ( (uint8_t)sub_443430(v220) != 0 );
  if ( v199 == -1 )
  {
    sub_429E30(v215);
    LOBYTE(v225) = 8;
    v216 = v204;
    v8 = operator new(0x294u);
    v198 = v8;
    LOBYTE(v225) = 9;
    if ( v8 != nullptr )
      v9 = (int *)sub_42B0F0(v8);
    else
      v9 = nullptr;
    v10 = *v9;
    LOBYTE(v225) = 8;
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(v10 + 348))(v9, v215);
    sub_46B150(v206[4]);
    LOBYTE(v225) = 7;
    sub_41CBF0(v215);
    if ( v223 >= 0x10 )
      j__free(Block);
    v223 = 15;
    v222 = 0;
    LOBYTE(Block) = 0;
    if ( v178 != nullptr )
      j__free(v178);
    LOBYTE(v225) = 4;
    `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
    LOBYTE(v225) = 3;
    `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
    if ( v187 != nullptr )
      j__free(v187);
    if ( v184 != nullptr )
      j__free(v184);
    v11 = v181;
    v12 = v181 == nullptr;
    goto LABEL_255;
  }
  if ( v199 != -2 )
  {
    if ( v199 != 0 )
      v167 = 3;
    else
LABEL_70:
      v167 = 1;
    sub_41D300(v167);
  }
  v13 = (void **)v181;
  for ( n = 0; v13 != nullptr && n < (v182 - (int)v13) >> 2; ++n )
  {
    v15 = sub_522300(v13[n], 12300, 0, 0, -1, 1);
    sub_484F40(n, v15, 1);
  }
  mm = 1;
  v209 = v184;
  if ( v184 != v185 )
  {
    do
    {
      v16 = (void *)*v209;
      v17 = v209[1];
      v18 = sub_484E80(*v209);
      if ( v18 == -1
        || (v18 >= *((uint32_t *)dword_8F852C + 2)
          ? (v19 = 0)
          : (v19 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v18)),
            (*(uint8_t (/*thiscall*/ **)(int, void *))(*(uint32_t *)v19 + 60))(v19, v16) == 0) )
      {
        v21 = (struct TypeDescriptor *)sub_522300(v16, v17, 0, 0, -1, 1);
        if ( (*((uint8_t (/*thiscall*/ **)(struct TypeDescriptor *, int))v21->__vftable + 5))(v21, 2) != 0 )
        {
          v22 = mm;
          v23 = sub_4E9B10(&v169, 0, mm, 0, -1);
          v24 = v21->__vftable;
          LOBYTE(v225) = 10;
          (*((void (/*thiscall*/ **)(struct TypeDescriptor *, uint32_t *))v24 + 46))(v21, v23);
          mm = v22 + 1;
          LOBYTE(v225) = 7;
          sub_445150(&v169);
        }
        v25 = sub_547350(v21);
        v26 = *((uint32_t *)dword_8F852C + 2);
        for ( ii = 3; ii < 9; ++ii )
        {
          if ( ii < v26 )
          {
            v28 = *((uint32_t *)dword_8F852C + 3);
            if ( *(uint32_t *)(v28 + 4 * ii) != 0 )
              continue;
          }
          v167 = 1;
          v166 = (int)v21;
          v165 = ii;
          goto LABEL_98;
        }
        v29 = 32 * v25 + 9;
        for ( jj = (uint32_t *)(v28 + 4 * v29); v29 < v26 && *jj != 0; ++jj )
          ++v29;
        v167 = 1;
        v166 = (int)v21;
        v165 = v29;
LABEL_98:
        sub_484F40(v165, v166, v167);
      }
      else if ( v18 >= *((uint32_t *)dword_8F852C + 2) )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int))(MEMORY[0] + 48))(0, v17);
      }
      else
      {
        v20 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v18);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 48))(v20, v17);
      }
      v209 += 2;
    }
    while ( v209 != v185 );
  }
  v31 = (char *)v187;
  v32 = 0;
  if ( v187 != v188 )
  {
    do
    {
      v33 = sub_522300(*(void **)v31, *((uint32_t *)v31 + 1), 0, 0, -1, 1);
      sub_484F40(v32, v33, 1);
      v31 += 8;
      ++v32;
    }
    while ( v31 != v188 );
  }
  v34 = *(uint32_t **)&v168[16 * (uint32_t)v204 + 4];
  v35 = *(uint32_t **)&v168[16 * (uint32_t)v204 + 8];
  v201 = 16 * (uint32_t)v204;
  v209 = v34;
  v203 = (int)&v168[16 * (uint32_t)v204 + 8];
  if ( v34 != v35 )
  {
    do
    {
      v36 = v209;
      v37 = sub_47E720(v204, *v209);
      v38 = v36[1];
      v39 = v37;
      if ( sub_47DCC0(v37) >= v38 )
        v41 = v38;
      else
        v41 = sub_47DCC0(v39);
      sub_41A590(v39 + 496, v40, v41);
      if ( *(uint32_t *)(v39 + 124) != 0 )
      {
LABEL_111:
        for ( kk = 42 * sub_41A5E0(v39 + 128) + 6;
              kk < *(uint32_t *)dword_8F853C && *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * kk) != 0;
              ++kk )
        {
          ;
        }
      }
      else
      {
        kk = 0;
        while ( kk < *(uint32_t *)dword_8F853C && *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * kk) != 0 )
        {
          if ( ++kk >= 6 )
            goto LABEL_111;
        }
      }
      sub_483D50(kk, v39);
      v12 = v209 + 2 == *(uint32_t **)v203;
      v209 += 2;
    }
    while ( !v12 );
  }
  Value = v205;
  dword_8F7C0C = v207;
  word_8F7C14 = 100;
  LOWORD(word_77F804) = v200;
  v43 = v206[3];
  v44 = nullptr;
  i = nullptr;
  v203 = 0;
  if ( v43 != 1 )
  {
    if ( v43 != 3 )
    {
      if ( v199 == -2 )
      {
        v44 = *(uint32_t **)(v206[8] + 16);
        i = v44;
      }
      goto LABEL_178;
    }
    dword_9B0AB0 = (int)&dword_9B0C08;
    i = *(uint32_t **)(v206[7] + 16);
    v48 = (uint32_t *)sub_476B60(v199);
    dword_99FB8C = 2;
    v197 = nullptr;
    v49 = v48[42];
    v207 = (int)v48;
    v198 = nullptr;
    if ( v49 != 0 )
    {
      v50 = (v48[43] - v49) >> 3;
      if ( v50 != 0 )
      {
        if ( v50 > 1 )
        {
          v52 = v49 + 8;
          if ( v52 != v48[43] )
            v48[43] = v52;
        }
        goto LABEL_127;
      }
      v51 = (v48[43] - v49) >> 3;
    }
    else
    {
      v51 = 0;
    }
    sub_473A80(v48[43], 1 - v51, &v197);
LABEL_127:
    *(uint32_t *)v48[42] = 3;
    *(uint32_t *)(v48[42] + 4) = 3;
    v198 = &v164;
    sub_489720(1, v164, nullptr, 0, 0);
    v53 = v48[46];
    if ( *(uint32_t *)(v53 + 4) != 0 )
      j__free(*(void **)(v53 + 4));
    *(uint32_t *)(v53 + 4) = 0;
    *(uint32_t *)(v53 + 8) = 0;
    *(uint32_t *)(v53 + 12) = 0;
    v205 = 15;
    for ( mm = 9; mm != 0; --mm )
    {
      v54 = v48[46];
      v55 = *(uint32_t *)(v54 + 4);
      if ( v55 != 0 )
        v56 = (*(uint32_t *)(v54 + 8) - v55) >> 2;
      else
        v56 = 0;
      if ( v55 != 0 && v56 < (*(uint32_t *)(v54 + 12) - v55) >> 2 )
      {
        v57 = *(uint32_t **)(v54 + 8);
        *v57 = 15;
        *(uint32_t *)(v54 + 8) = v57 + 1;
      }
      else
      {
        sub_430C80(*(void **)(v54 + 8), 1, (int)&v205);
      }
    }
    sub_4755F0(nullptr);
    if ( nn == (void *)100 )
    {
      dword_99FB7C = 1;
      dword_99FB80 = 0;
    }
    else
    {
      dword_99FB7C = 2;
      dword_99FB80 = 2;
    }
    v58 = v213;
    i[27] = v48;
    v59 = dword_99FBB4 + 36;
    *(uint32_t *)(dword_99FBB4 + 36) = v58;
    mm = v59;
    v60 = sub_4CE8A0(v58);
    v61 = *(uint32_t *)(v60 + 24);
    v213 = v60;
    if ( v61 != 0 && (*(uint32_t *)(v60 + 28) - v61) >> 3 != 0 )
    {
      v62 = *(uint32_t *)(v60 + 24);
      if ( v62 != 0 )
        v63 = (*(uint32_t *)(v60 + 28) - v62) >> 3;
      else
        v63 = 0;
      v64 = *(uint32_t *)ArgList % v63;
      v65 = *(uint32_t *)(v213 + 24);
      v66 = *(uint32_t *)(v65 + 8 * (*(uint32_t *)ArgList % v63) + 4);
      v67 = nullptr;
      v198 = nullptr;
      *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v207 + 184) + 4) + 4) = *(uint32_t *)(v65 + 8 * v64);
      v68 = nullptr;
      v69 = nullptr;
      v196 = nullptr;
      v197 = nullptr;
      LOBYTE(v225) = 11;
      if ( (v66 & 4) != 0 )
      {
        v203 = 0;
        sub_430C80(nullptr, 1, (int)&v203);
        v67 = v198;
        v68 = v197;
        v69 = v196;
      }
      if ( (v66 & 1) != 0 )
      {
        v203 = 1;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((v67 - v69) >> 2) )
        {
          *v68++ = 1;
          v197 = v68;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);
          v67 = v198;
          v68 = v197;
          v69 = v196;
        }
      }
      if ( (v66 & 2) != 0 )
      {
        v203 = 2;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((v67 - v69) >> 2) )
        {
          *v68++ = 2;
          v197 = v68;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);
          v67 = v198;
          v68 = v197;
          v69 = v196;
        }
      }
      if ( (v66 & 8) != 0 )
      {
        v203 = 3;
        if ( v69 != nullptr && ((char *)v68 - v69) >> 2 < (unsigned int)((v67 - v69) >> 2) )
        {
          *v68++ = 3;
        }
        else
        {
          sub_430C80(v68, 1, (int)&v203);
          v68 = v197;
          v69 = v196;
        }
      }
      if ( v69 != nullptr )
        v70 = ((char *)v68 - v69) >> 2;
      else
        v70 = 0;
      LOBYTE(v225) = 7;
      v203 = *(uint32_t *)&v69[4 * ((unsigned int)nn % v70)];
      if ( v69 != nullptr )
        j__free(v69);
    }
    else
    {
      *(uint32_t *)(*(uint32_t *)(v48[46] + 4) + 4) = 15;
    }
    v71 = (int *)v207;
    v72 = v213;
    v73 = 0;
    for ( *(uint32_t *)ArgList = 0; ; *(uint32_t *)ArgList += 56 )
    {
      v74 = *(uint32_t *)(v72 + 64);
      if ( v74 == 0 || v73 >= (*(uint32_t *)(v72 + 68) - v74) / 56 )
        break;
      v75 = *(uint32_t *)(v72 + 64);
      v76 = *(uint8_t *)(v75 + *(uint32_t *)ArgList + 4);
      v77 = (int *)(*(uint32_t *)ArgList + v75);
      v78 = *v77;
      v12 = v76 == 0;
      v79 = v77[2];
      if ( !v12 )
        v79 += v71[28];
      v195[3] = v79;
      v196 = (uint8_t *)v77[9];
      v195[2] = v78;
      v195[0] = v73;
      v195[1] = v73;
      LOBYTE(v197) = 0;
      v198 = nullptr;
      sub_489580(v195);
      ++v73;
    }
    sub_475810(v71, v73, 1, 0);
    v44 = i;
    sub_4284C0(1, 0);
    sub_425960(0, v44[11], v44[26]);
    goto LABEL_178;
  }
  sub_45D190(ArgList[0], nn);
  v44 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  i = v44;
  v213 = 1;
  v45 = (uint32_t *)sub_489610(&v213);
  v167 = (int)&v213;
  *v45 = 2;
  v213 = 2;
  *(uint32_t *)sub_489610(v167) = 2;
  v213 = 3;
  v46 = (uint32_t *)sub_489610(&v213);
  v167 = (int)&v213;
  *v46 = 3;
  v213 = 4;
  v47 = (uint32_t *)sub_489610(v167);
  v167 = (int)&v213;
  *v47 = 3;
  v213 = 5;
  *(uint32_t *)sub_489610(v167) = 2;
  v213 = 6;
  *(uint32_t *)sub_489610(&v213) = 1;
  sub_47D1E0(1015);
  sub_47D1E0(1011);
  sub_47D1E0(1003);
  sub_47D1E0(1002);
  sub_47D1E0(1001);
  sub_47D1E0(19);
LABEL_178:
  v80 = *(uint32_t *)dword_8F8520;
  v209 = (uint32_t *)v44[26];
  (*(void (/*thiscall*/ **)(int, uint32_t *))(v80 + 124))(dword_8F8520, v44);
  for ( nn = nullptr; (int)nn < v193; nn = (char *)nn + 1 )
  {
    v81 = sub_42A100(nn);
    v82 = v204;
    v83 = v192;
    v84 = v81;
    v85 = v81 + 16;
    v167 = v194;
    v213 = v81;
    *(uint32_t *)(v81 + 44) = v204;
    *(uint32_t *)(v81 + 48) = v83;
    sub_41A590(v81 + 53, (int)v82, v167);
    v86 = (void *)sub_4B0EC0(v204, v83);
    sub_4015C0(v86, strlen((const char *)v86));
    *(uint32_t *)(v84 + 116) = 20;
    for ( i1 = 0; ; ++i1 )
    {
      v88 = *(uint32_t *)&v177[v201 + 4];
      if ( v88 == 0 || i1 >= (*(uint32_t *)&v177[v201 + 8] - v88) >> 2 )
        break;
      v89 = *(uint32_t *)(sub_4CE8A0(*(uint32_t *)(4 * i1 + *(uint32_t *)&v177[v201 + 4])) + 92);
      if ( v89 <= 9 )
        *(uint32_t *)(v85 + 4 * v89 + 56) = *(uint32_t *)(*(uint32_t *)&v177[v201 + 4] + 4 * i1);
      v84 = v213;
    }
    v90 = (unsigned int)nn;
    sub_456300(nn, v84);
    if ( v178 != nullptr && (v179 - (int)v178) >> 2 > v90 )
    {
      v91 = (*((uint32_t *)v178 + v90) << 24) + 43200;
      *(uint32_t *)(v84 + 160) = v91;
      *(uint32_t *)(v84 + 164) = v91;
      *(uint16_t *)(v84 + 168) = 5063;
    }
    v92 = (int *)sub_42B340(v213);
    v93 = *v92;
    v198 = v92;
    (*(void (/*thiscall*/ **)(int *, int))(v93 + 348))(v92, v85);
    v94 = sub_579F90(v204);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v94 + 1044))(v94, v85);
    (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)v94 + 1212))(v94, nn);
    sub_42A3D0(v94);
    for ( i2 = 0; ; ++i2 )
    {
      v96 = *(uint32_t *)&v177[v201 + 4];
      if ( v96 == 0 || i2 >= (*(uint32_t *)&v177[v201 + 8] - v96) >> 2 )
        break;
      v97 = *(uint32_t *)&v177[v201 + 4];
      v98 = *(uint32_t *)v94;
      v167 = 0;
      v166 = (int)&CNRDEquipment `RTTI Type Descriptor';
      v165 = (int)&IRDItem `RTTI Type Descriptor';
      v164 = 0;
      v213 = v97 + 4 * i2;
      v99 = rand();
      v100 = sub_522300(*(void **)v213, v99, 0, 0, -1, 1);
      v101 = __RTDynamicCast(v100, v164, (struct TypeDescriptor *)v165, (struct TypeDescriptor *)v166, v167);
      (*(void (/*thiscall*/ **)(int, int))(v98 + 784))(v94, v101);
    }
    for ( i3 = 0; i3 < 18; ++i3 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v94 + 1080))(v94, i3);
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v94 + 792))(v94, i3) != 0 )
      {
        v103 = sub_4E9C00(10, 0, 0, 10, 0);
        v104 = *(uint32_t *)v94;
        LOBYTE(v225) = 12;
        v105 = (*(int (/*thiscall*/ **)(int, int))(v104 + 792))(v94, i3);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v105 + 184))(v105, v103);
        LOBYTE(v225) = 15;
        sub_41A580(v173);
        LOBYTE(v225) = 14;
        sub_41A580(v172);
        LOBYTE(v225) = 13;
        sub_41A580(v171);
        LOBYTE(v225) = 7;
        sub_41A580(v170);
      }
    }
    v106 = sub_4CE8A0(v204);
    qmemcpy(v217, (const void *)(v106 + 152), sizeof(v217));
    v107 = &v219;
    v108 = 0;
    v191 = v106;
    v218 = 100;
    v213 = 0;
    while ( 1 )
    {
      v109 = v194;
      if ( v108 != 0 )
      {
        if ( v194 <= 18 )
          break;
        v110 = 79 * v192 + v106 + 231;
        v111 = v194 - 18;
      }
      else
      {
        v110 = v106 + 231;
        if ( v194 > 18 )
          v109 = 18;
        v111 = v109 - 1;
      }
      *(uint32_t *)v217 += v111 * *(uint32_t *)v110;
      *(uint32_t *)&v217[2] += v111 * *(uint32_t *)(v110 + 4);
      v217[4] += v111 * *(uint16_t *)(v110 + 8);
      v217[5] += v111 * *(uint16_t *)(v110 + 10);
      v217[6] += v111 * *(uint16_t *)(v110 + 12);
      v217[7] += v111 * *(uint16_t *)(v110 + 14);
      v112 = 0;
      *(uint32_t *)ArgList = v110 + 16;
      do
      {
        v113 = *(uint32_t *)ArgList;
        v217[v112++ + 8] += v111 * **(uint16_t **)ArgList;
        *(uint32_t *)ArgList = v113 + 2;
      }
      while ( v112 < 4 );
      v114 = 0;
      *(uint32_t *)ArgList = v110 + 24;
      do
      {
        v115 = *(uint32_t *)ArgList;
        v217[v114++ + 12] += v111 * **(uint16_t **)ArgList;
        v107 = (char *)(v115 + 2);
        *(uint32_t *)ArgList = v107;
      }
      while ( v114 < 16 );
      *(uint32_t *)&v217[28] += v111 * *(uint32_t *)(v110 + 56);
      v217[30] += v111 * *(uint16_t *)(v110 + 60);
      v217[31] += v111 * *(uint16_t *)(v110 + 62);
      v217[32] += v111 * *(uint16_t *)(v110 + 64);
      v217[33] += v111 * *(uint16_t *)(v110 + 66);
      v217[34] += v111 * *(uint16_t *)(v110 + 68);
      v217[35] += v111 * *(uint16_t *)(v110 + 70);
      v217[36] += v111 * *(uint16_t *)(v110 + 72);
      *(uint32_t *)&v217[37] += v111 * *(uint32_t *)(v110 + 74);
      v108 = ++v213;
      if ( v213 >= 2 )
        break;
      v106 = v191;
    }
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)v94 + 1048))(v94, v217);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v94 + 1056))(v94, 1);
    v116 = v206[3];
    if ( v116 == 1 )
    {
      v117 = (int *)v198;
      sub_45FE80((int)v209, (int)v107, 18, (int)nn, (int)v198, 0, 0);
      v118 = *v117;
      v205 = 100;
      v200 = 200;
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(v118 + 112))(v117, 100, 200, 0);
      (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(*v117 + 140))(
        v117,
        &v205,
        &v200,
        v205,
        v200,
        200,
        1,
        1);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*v117 + 112))(v117, v205, v200, 0);
    }
    else if ( v116 == 3 )
    {
      v119 = nn;
      sub_45FE80((int)v209, (int)nn, 273, (int)nn, v94, 0, 0);
      mm = 0;
      v207 = 0;
      if ( *(uint32_t *)(i[11] + 284) != 0 )
      {
        v121 = rand();
        sub_48C330(&mm, &v207, v94, v121);
      }
      else
      {
        v120 = rand();
        sub_48C2A0(&mm, &v207, v203, v94, v120);
      }
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v94 + 112))(v94, mm, v207, 0);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v94 + 1120))(v94) != 0 )
      {
        v122 = *(uint32_t *)v94;
        v167 = 0;
        v166 = 0;
        v123 = (*(int (/*thiscall*/ **)(int))(v122 + 1120))(v94);
        sub_45FE80((int)v209, (int)v119, 65, (int)v119, v123, v166, v167);
      }
      v124 = dword_8F853C;
      for ( i4 = 0; i4 < *v124; ++i4 )
      {
        v126 = *(uint32_t *)(v124[1] + 4 * i4);
        if ( v126 != 0 )
        {
          v198 = (void *)sub_41A5E0(v126 + 496);
          v127 = sub_41A5E0(v126 + 4);
          (*(void (/*thiscall*/ **)(int, int, void *))(*(uint32_t *)v94 + 1136))(v94, v127, v198);
          v124 = dword_8F853C;
        }
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v94 + 1152))(v94);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v94 + 1156))(v94);
    }
  }
  v128 = v206[3];
  if ( v128 == 1 )
  {
    sub_45B140(v206[5]);
    sub_424A40(i, dword_8F7C08);
    sub_47D1E0(1);
    sub_47D9D0(dword_8F8540);
    v167 = (uint16_t)word_77F804;
    sub_656710();
    sub_6567B0(v167);
    v129 = 0;
    for ( i5 = 16; i5 < 32; i5 += 4 )
    {
      v131 = *(uint32_t *)(i5 + dword_8F850C);
      if ( v131 != 0 && v131 != sub_429830((uint16_t)word_77F804) )
      {
        v132 = *(struct TypeDescriptor **)(v131 + 8);
        v133 = *(uint16_t *)(v131 + 168);
        v167 = 0;
        v166 = (int)v132;
        v165 = v133;
        v164 = sub_42A380(1);
        sub_656710();
        sub_656880(v129, (void *)v164, v165, v166, v167);
      }
      ++v129;
    }
    *(uint32_t *)(sub_656710() + 40) = 0;
  }
  else if ( v128 == 3 )
  {
    sub_47E4F0();
    *((uint8_t *)v209 + 152) = 1;
    v167 = (uint16_t)word_77F804;
    sub_656710();
    sub_6567B0(v167);
    v134 = 0;
    for ( i6 = 16; i6 < 32; i6 += 4 )
    {
      v136 = *(uint32_t *)(i6 + dword_8F850C);
      if ( v136 != 0 && v136 != sub_429830((uint16_t)word_77F804) )
      {
        v137 = *(struct TypeDescriptor **)(v136 + 8);
        v138 = *(uint16_t *)(v136 + 168);
        v167 = 0;
        v166 = (int)v137;
        v165 = v138;
        v164 = sub_42A380(1);
        sub_656710();
        sub_656880(v134, (void *)v164, v165, v166, v167);
      }
      ++v134;
    }
    v139 = sub_656710();
    v140 = i;
    *(uint32_t *)(v139 + 40) = 0;
    sub_424A40(v140, dword_8F7C04);
  }
  else if ( v199 == -2 )
  {
    v141 = sub_4879B0(1);
    v142 = v193;
    v143 = 0;
    for ( i7 = v141; v143 < v142; ++v143 )
      sub_48F700(v143, v143, v143 % 2 + 1);
    sub_48FA30(0);
    v167 = i7;
    *(uint32_t *)(i7 + 116) = 1;
    sub_48F890(v167);
    sub_453050(2, 0);
  }
  *(uint32_t *)dword_99FB70 = 1;
  sub_47D060(1063, 0);
  sub_47D060(1062, 0);
  *(uint32_t *)dword_99FCD8 = -1010512201;
  dword_99FCE0 = -1045510470;
  dword_99FCDC = -1109932768;
  word_99FCE4 = 223;
  sub_456EB0((void *)1);
  *(uint32_t *)(sub_4569F0(1) + 8) = 1;
  v145 = nullptr;
  for ( i8 = 16; i8 < 32; i8 += 4 )
  {
    v147 = *(uint32_t *)(i8 + dword_8F850C);
    if ( v147 != 0 )
      v148 = *(uint16_t *)(v147 + 4);
    else
      v148 = 0xFFFF;
    v167 = v148;
    v166 = (int)v145;
    sub_4569F0(1);
    sub_56A6B0(v166, v167);
    v145 = (struct TypeDescriptor *)((char *)v145 + 1);
  }
  sub_41C270(1);
  sub_47B150(&unk_6C8D60, 13, 0, 0, 0);
  sub_47B150("[fighter]", 14, 1, 0, 0);
  sub_47B150("[gunner]", 13, 2, 0, 0);
  sub_47B150(&unk_6C8D58, 13, 0, 1, 0);
  sub_47B150(&unk_6C8D50, 14, 1, 1, 0);
  sub_47B150(&unk_6C8D48, 13, 2, 1, 0);
  sub_47B150(&unk_6C8D40, 13, 0, 2, 0);
  sub_47B150(&unk_6C8D38, 14, 1, 2, 0);
  sub_47B150(&unk_6C8D30, 13, 2, 2, 0);
  sub_47B150(&unk_6C8D28, 13, 0, 3, 0);
  sub_47B150(&unk_6C8D20, 14, 1, 3, 0);
  sub_47B150(&unk_6C8D18, 13, 2, 3, 0);
  v149 = sub_47B150(&unk_6C8D60, 13, 0, 0, 0);
  sprintf((char *const)(v149 + 52), &byte_6C8D10);
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 14;
  *(uint32_t *)(v149 + 40) = 12;
  v150 = sub_47B150("[fighter]", v164, v165, v166, v167);
  sprintf((char *const)(v150 + 52), &byte_6C8D08);
  v167 = 0;
  v166 = 0;
  v165 = 2;
  v164 = 13;
  *(uint32_t *)(v150 + 40) = 10;
  v151 = sub_47B150("[gunner]", v164, v165, v166, v167);
  sprintf((char *const)(v151 + 52), &byte_6C8D08);
  v167 = 0;
  v166 = 1;
  v165 = 0;
  v164 = 13;
  *(uint32_t *)(v151 + 40) = 5;
  v152 = sub_47B150(&unk_6C8D58, v164, v165, v166, v167);
  sprintf((char *const)(v152 + 52), &byte_6C8CFC);
  v153 = sub_47B150(&unk_6C8D50, 14, 1, 1, 0);
  sprintf((char *const)(v153 + 52), &byte_6C8CFC);
  v154 = sub_47B150(&unk_6C8D48, 13, 2, 1, 0);
  sprintf((char *const)(v154 + 52), &byte_6C8CF0);
  v155 = sub_47B150(&unk_6C8D40, 13, 0, 2, 0);
  sprintf((char *const)(v155 + 52), &byte_6C8CF0);
  v156 = sub_47B150(&unk_6C8D38, 14, 1, 2, 0);
  sprintf((char *const)(v156 + 52), &byte_6C8CF0);
  v157 = sub_47B150(&unk_6C8D30, 13, 2, 2, 0);
  sprintf((char *const)(v157 + 52), &byte_6C8CF0);
  v158 = sub_47B150(&unk_6C8D28, 13, 0, 3, 0);
  sprintf((char *const)(v158 + 52), &byte_6C8CF0);
  v159 = sub_47B150(&unk_6C8D20, 14, 1, 3, 0);
  sprintf((char *const)(v159 + 52), &byte_6C8CF0);
  v160 = sub_47B150(&unk_6C8D18, 13, 2, 3, 0);
  sprintf((char *const)(v160 + 52), &byte_6C8CF0);
  sub_4015C0("Allons y", 8u);
  v161 = sub_47B150(&unk_6C8CDC, 38, 1, 0, 0);
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 27;
  *(uint32_t *)(v161 + 40) = 5;
  sub_47B150(&unk_6C8CD4, v164, v165, v166, v167);
  v162 = sub_47B150(&unk_6C8CCC, 20, 1, 0, 0);
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 10;
  *(uint32_t *)(v162 + 40) = 12;
  sub_47B150(&unk_6C8D48, v164, v165, v166, v167);
  v163 = sub_47B150("CruelRogue", 5, 1, 0, 0);
  v167 = 0;
  v166 = 0;
  v165 = 1;
  v164 = 2;
  *(uint32_t *)(v163 + 40) = 23;
  sub_47B150("WindShadow", v164, v165, v166, v167);
  (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(
    **((uint32_t **)dword_8F852C + 3),
    100000);
  sub_50D920(0);
  if ( v223 >= 0x10 )
    j__free(Block);
  v223 = 15;
  v222 = 0;
  LOBYTE(Block) = 0;
  if ( v178 != nullptr )
    j__free(v178);
  LOBYTE(v225) = 4;
  `eh vector destructor iterator'(v168, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
  LOBYTE(v225) = 3;
  `eh vector destructor iterator'(v177, 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( v187 != nullptr )
    j__free(v187);
  if ( v184 != nullptr )
    j__free(v184);
  v11 = v181;
  v12 = v181 == nullptr;
LABEL_255:
  if ( !v12 )
    j__free(v11);
}


// ------------------------------------------------------------
// 0x48B700 sub_48B700
// ------------------------------------------------------------
int /*thiscall*/ sub_48B700(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint8_t *)(this + 40) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x48B720 sub_48B720
// ------------------------------------------------------------
int /*thiscall*/ sub_48B720(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 1) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x48B740 sub_48B740
// ------------------------------------------------------------
int /*thiscall*/ sub_48B740(const CHAR *this, int a2)
{
  int result; // eax
  const CHAR *v3; // eax
  int v4; // ecx
  int v5; // edx

  if ( dword_6C8E30[a2] != 0 )
    return 0;
  if ( a2 > 0 )
  {
    v3 = this + 40;
    if ( a2 > 17 )
      v3 = this + 104;
  }
  else
  {
    v3 = lpAppName;
  }
  result = sub_57A100(v3, (&lpKeyName)[a2], nDefault[a2]);
  v4 = dword_6C8ED4[2 * a2];
  v5 = v4;
  if ( v4 >= result )
    v5 = result;
  if ( dword_6C8ED0[2 * a2] > v5 )
    return dword_6C8ED0[2 * a2];
  if ( v4 < result )
    return dword_6C8ED4[2 * a2];
  return result;
}



// ------------------------------------------------------------
// 0x48B7C0 sub_48B7C0
// ------------------------------------------------------------
bool /*thiscall*/ sub_48B7C0(const CHAR *this, int a2, int a3)
{
  const CHAR *v4; // eax
  bool v5; // bl

  if ( dword_6C8E30[a2] != 0 )
    return false;
  if ( a2 > 0 )
  {
    v4 = this + 40;
    if ( a2 > 17 )
      v4 = this + 104;
  }
  else
  {
    v4 = lpAppName;
  }
  v5 = sub_57A180(v4, (&lpKeyName)[a2], a3) == 1;
  sub_48B830(a2);
  return v5;
}



// ------------------------------------------------------------
// 0x48B830 sub_48B830
// ------------------------------------------------------------
char /*thiscall*/ sub_48B830(int this, int a2)
{
  int v2; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  LOBYTE(v2) = a2;
  if ( a2 != 0 )
  {
    switch ( a2 )
    {
      case 1:
        v2 = sub_48B740((const CHAR *)this, 1);
        byte_790AD0 = v2 != 0;
        break;
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
LABEL_23:
        break;
      case 7:
        v2 = sub_48B740((const CHAR *)this, 7);
        dword_9A0114 = v2;
        if ( dword_9B8880 != 0 )
          LOBYTE(v2) = sub_69CE50(v2);
        break;
      case 9:
        v4 = sub_48B740((const CHAR *)this, 9);
        LOBYTE(v2) = sub_5621D0(v4);
        break;
      case 10:
        v5 = sub_48B740((const CHAR *)this, 10);
        LOBYTE(v2) = sub_5621F0(v5);
        break;
      case 8:
        v6 = sub_48B740((const CHAR *)this, 8);
        LOBYTE(v2) = sub_657920(v6);
        *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
        break;
      default:
        goto LABEL_23;
    }
  }
  else
  {
    v2 = sub_48B740((const CHAR *)this, 0);
    if ( v2 != 1 )
    {
      DeleteFileA((LPCSTR)(*(uint32_t *)(this + 4) + 4));
      LOBYTE(v2) = sub_48B7C0((const CHAR *)this, 0, 1);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x48B970 sub_48B970
// ------------------------------------------------------------
int /*thiscall*/ sub_48B970(const CHAR *this)
{
  int i; // esi
  int result; // eax

  sub_57A120(this + 104, lpszKey, byte_99FDD0, 0xD8u);
  for ( i = 0; i < 216; ++i )
  {
    result = sub_47DC90(i);
    if ( result != 0 )
      result = sub_47E7A0(byte_99FDD0[i], 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x48B9C0 sub_48B9C0
// ------------------------------------------------------------
char /*thiscall*/ sub_48B9C0(uint32_t *this, LPCSTR lpString2)
{
  int v3; // eax

  if ( operator new(0x108u) != nullptr )
    v3 = sub_57A0A0(lpString2);
  else
    v3 = 0;
  *(this + 1) = v3;
  return sub_48B830((int)this, 0);
}



// ------------------------------------------------------------
// 0x48BA30 sub_48BA30
// ------------------------------------------------------------
char /*thiscall*/ sub_48BA30(char *this, char *a2)
{
  char *v2; // eax
  const char *v4; // esi
  int v5; // edx
  char v6; // cl
  int i; // esi
  char result; // al

  v2 = a2;
  v4 = this + 8;
  v5 = this + 8 - a2;
  do
  {
    v6 = *v2;
    v2[v5] = *v2;
    ++v2;
  }
  while ( v6 != 0 );
  sprintf(this + 40, "ID %s", v4);
  for ( i = 1; i <= 17; ++i )
    result = sub_48B830((int)this, i);
  return result;
}



// ------------------------------------------------------------
// 0x48BA80 sub_48BA80
// ------------------------------------------------------------
char /*thiscall*/ sub_48BA80(int this, const char *a2, int a3)
{
  int v4; // eax

  v4 = sub_48BE40(a2, strlen(a2));
  sprintf((char *const)(this + 104), "CH %s %s %d %d", (const char *)(this + 8), a2, v4, a3);
  return sub_48B830(this, 18);
}



// ------------------------------------------------------------
// 0x48BAD0 sub_48BAD0
// ------------------------------------------------------------
int /*thiscall*/ sub_48BAD0(const CHAR *this)
{
  int i; // esi
  int v3; // eax
  bool v4; // al

  for ( i = 0; i < 216; ++i )
  {
    v3 = sub_47DC90(i);
    v4 = v3 != 0 && sub_41A5E0(v3 + 558) != 0;
    byte_99FDD0[i] = v4;
  }
  return sub_57A0D0(this + 104, lpszKey, byte_99FDD0, 0xD8u);
}



// ------------------------------------------------------------
// 0x48BB30 sub_48BB30
// ------------------------------------------------------------
int /*thiscall*/ sub_48BB30(uint32_t *this, LPCVOID lpAddress)
{
  HMODULE LibraryA; // eax
  SIZE_T RegionSize; // ecx
  bool v6; // cf
  __time32_t v7; // eax
  int v8; // eax
  unsigned int i; // edi
  size_t v10; // [esp-1Ch] [ebp-48h]
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+10h] [ebp-1Ch] BYREF

  if ( lpAddress == nullptr )
    return -1;
  if ( *this != 0 )
    return -2;
  if ( IsDebuggerPresent == nullptr )
  {
    LibraryA = LoadLibraryA("Kernel32.dll");
    if ( LibraryA != nullptr )
      IsDebuggerPresent = GetProcAddress(LibraryA, "IsDebuggerPresent");
  }
  VirtualQuery(&loc_48BB8F, &Buffer, 0x1Cu);
  RegionSize = Buffer.RegionSize;
  v6 = Buffer.RegionSize < (unsigned int)lpAddress;
  *(this + 6) = Buffer.AllocationBase;
  if ( v6 )
    *(this + 2) = RegionSize;
  else
    *(this + 2) = lpAddress;
  *(this + 3) = RegionSize / *(this + 2);
  off_77F3FC("EyeOfBeholder::open_eye - code region size = %d", RegionSize);
  off_77F3FC("EyeOfBeholder::open_eye - CRC block size = %d", lpAddress);
  off_77F3FC("EyeOfBeholder::open_eye - number of CRC blocks = %d", *(this + 3));
  v7 = time(nullptr);
  srand(v7);
  v8 = rand();
  v10 = 4 * *(this + 3);
  *(this + 1) = v8;
  *(this + 4) = malloc(v10);
  for ( i = 0; i < *(this + 3); ++i )
    *(uint32_t *)(*(this + 4) + 4 * i) = sub_57A220(*(this + 1), *(this + 6) + i * *(this + 2), *(this + 2));
  *this = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x48BC60 sub_48BC60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48BC60(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 4) = 0;
  *(this + 3) = 0;
  *(this + 2) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x48BC90 sub_48BC90
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_48BC90(void *a1)
{
  unsigned int v2; // [esp+0h] [ebp-4h] BYREF

  v2 = 0;
  sub_404AD0(&v2);
  sub_404AF0(a1, v2);
  return v2;
}



// ------------------------------------------------------------
// 0x48BCC0 sub_48BCC0
// ------------------------------------------------------------
char */*cdecl*/ sub_48BCC0(char *Destination, unsigned int a2, char *Source)
{
  char *result; // eax
  unsigned int v4; // [esp+4h] [ebp-4h] BYREF

  v4 = 0;
  if ( a2 != 0 )
  {
    sub_404AD0(&v4);
    if ( v4 < a2 && v4 != 0 )
    {
      sub_404AF0(Destination, v4);
      Destination[v4] = 0;
      return (char *)v4;
    }
    result = Source;
    if ( Source == nullptr )
    {
      *Destination = 0;
      return result;
    }
    strncpy(Destination, Source, a2 - 1);
    Destination[a2 - 1] = 0;
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x48BD40 sub_48BD40
// ------------------------------------------------------------
int /*cdecl*/ sub_48BD40(int a1, int a2, int a3)
{
  int16_t v3; // ax
  int v4; // ebx
  int result; // eax
  int v6; // esi
  char v7; // al

  v3 = 16053;
  if ( a3 != 0 )
    v3 = sub_4D33A0(a3);
  v4 = HIBYTE(v3) & 7;
  byte_99FEAC = v3;
  result = a2;
  v6 = 0;
  dword_99FEB0 = v4;
  if ( a2 > 0 )
  {
    while ( 1 )
    {
      v7 = __ROL1__(*(uint8_t *)(v6 + a1), v4);
      *(uint8_t *)(v6 + a1) = v7;
      *(uint8_t *)(v6 + a1) = byte_99FEAC ^ v7;
      result = a2;
      if ( ++v6 >= a2 )
        break;
      LOBYTE(v4) = dword_99FEB0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48BDC0 sub_48BDC0
// ------------------------------------------------------------
int /*cdecl*/ sub_48BDC0(int a1, int a2, int a3)
{
  int16_t v3; // ax
  int result; // eax
  int i; // esi
  char v6; // al
  char v7; // bl

  v3 = 16053;
  if ( a3 != 0 )
    v3 = sub_4D33A0(a3);
  byte_99FEAC = v3;
  dword_99FEB0 = HIBYTE(v3) & 7;
  result = a2;
  for ( i = 0; i < a2; ++i )
  {
    v6 = byte_99FEAC ^ *(uint8_t *)(i + a1);
    *(uint8_t *)(i + a1) = v6;
    v7 = __ROR1__(v6, dword_99FEB0);
    result = a2;
    *(uint8_t *)(i + a1) = v7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48BE40 sub_48BE40
// ------------------------------------------------------------
int /*cdecl*/ sub_48BE40(int a1, int a2)
{
  int v3; // eax

  if ( a2 < 0 )
    return 0;
  v3 = sub_57A220(0, 0, 0);
  return sub_57A220(v3, a1, a2);
}



// ------------------------------------------------------------
// 0x48BE70 sub_48BE70
// ------------------------------------------------------------
int /*thiscall*/ sub_48BE70(int this, int a2, int a3)
{
  char v3; // al
  uint8_t *v5; // eax
  char v6; // cl
  uint8_t *v7; // esi
  struct tm *v8; // eax
  struct tm *v9; // eax
  struct tm *v10; // eax
  struct tm *v11; // eax
  struct tm *v12; // eax
  int tm_sec; // ebx
  unsigned int v14; // edi
  const char *v15; // eax
  uint32_t *v16; // ebx
  int v17; // edx
  int v18; // eax
  __time64_t Time; // [esp+0h] [ebp-1Ch] BYREF
  int v20; // [esp+8h] [ebp-14h]
  int tm_mday; // [esp+Ch] [ebp-10h]
  int tm_hour; // [esp+10h] [ebp-Ch]
  int tm_min; // [esp+14h] [ebp-8h]
  uint32_t *v24; // [esp+18h] [ebp-4h]

  v3 = *(uint8_t *)(this + 4);
  v24 = (uint32_t *)this;
  if ( v3 == 0 )
    return -2147483647;
  v5 = (uint8_t *)sub_698C50(*(uint32_t *)(a2 + 2));
  v7 = v5;
  if ( v5 == nullptr )
  {
    off_77F3F8(v6, "Socket Error");
    return 0x80000000;
  }
  sub_48BDC0(v5 + 6, *(uint32_t *)(v5 + 2) - 6, 0);
  sub_404A80(v7 + 6);
  Time = _time64(nullptr);
  v8 = _localtime64(&Time);
  if ( v8 != nullptr )
    v20 = v8->tm_mon + 1;
  else
    v20 = 0;
  v9 = _localtime64(&Time);
  if ( v9 != nullptr )
    tm_mday = v9->tm_mday;
  else
    tm_mday = 0;
  v10 = _localtime64(&Time);
  if ( v10 != nullptr )
    tm_hour = v10->tm_hour;
  else
    tm_hour = -1;
  v11 = _localtime64(&Time);
  if ( v11 != nullptr )
    tm_min = v11->tm_min;
  else
    tm_min = -1;
  v12 = _localtime64(&Time);
  if ( v12 != nullptr )
    tm_sec = v12->tm_sec;
  else
    tm_sec = -1;
  LOBYTE(a2) = 0;
  v14 = 1;
  if ( *v7 != 0 )
  {
    if ( *v7 == 1 )
    {
      sub_404A90(&a2);
      v15 = "Ok";
      if ( (uint8_t)a2 == 0 )
        v15 = "Error";
      off_77F3FC(
        "\n[<- COMMAND PACKET] Packet : %s, Size : %d, Return : %s (%2d%2d-%2d:%2d:%2d)",
        *(const char **)&off_790928[4 * v7[1]],
        *(uint32_t *)(v7 + 2) - 6,
        v15,
        v20,
        tm_mday,
        tm_hour,
        tm_min,
        tm_sec);
      v16 = v24;
      v14 = sub_583B90(v24, v7, a2);
      goto LABEL_28;
    }
    off_77F3FC("Type Error! Type is %d", *v7);
  }
  else
  {
    off_77F3FC(
      "\n[<- NOTIFY PACKET] Packet : %s, Size : %d (%2d%2d-%2d:%2d:%2d)",
      *(const char **)&off_790790[4 * v7[1]],
      *(uint32_t *)(v7 + 2) - 6,
      v20,
      tm_mday,
      tm_hour,
      tm_min,
      tm_sec);
    v14 = sub_57A980(v24, v17, (int)v7);
  }
  v16 = v24;
LABEL_28:
  v18 = v16[3];
  if ( v18 != 8 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint8_t *, uint32_t))(*(uint32_t *)v16[v18 + 4] + 12))(
      v16[v18 + 4],
      v7[1],
      v7,
      *(uint32_t *)(v7 + 2));
  return v14;
}


// ------------------------------------------------------------
// 0x48C070 sub_48C070
// ------------------------------------------------------------
int /*stdcall*/ sub_48C070(int *a1, int *a2, int a3, int a4)
{
  *a1 = a3 / 16;
  *a2 = a4 / 12;
  return a4 / 12;
}



// ------------------------------------------------------------
// 0x48C0A0 sub_48C0A0
// ------------------------------------------------------------
bool /*cdecl*/ sub_48C0A0(int a1, int a2, int *a3)
{
  bool result; // al
  int v4; // ecx

  result = a1 >= *a3 && a1 < *a3 + a3[2] && (v4 = a3[1], a2 >= v4) && a2 < v4 + a3[3];
  return result;
}



// ------------------------------------------------------------
// 0x48C0E0 sub_48C0E0
// ------------------------------------------------------------
int /*cdecl*/ sub_48C0E0(uint32_t *a1, int *a2, uint32_t *a3, int a4, int a5)
{
  int v6; // ebx
  int v7; // ebx
  int v8; // ebx
  int result; // eax
  int v10; // edx
  int v11; // [esp+20h] [ebp+14h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a4 + 40))(a4, 1) != 0 )
  {
    v6 = a3[2] - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 428))(a4) + 1;
    v11 = sub_4D33A0(a5) % v6;
    v7 = a3[3] - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 432))(a4) + 1;
    v8 = sub_4D33A0(a5) % v7;
    *a1 = v11 + *a3 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 428))(a4) / 2;
    result = v8 + a3[1] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 432))(a4) / 2;
    *a2 = result;
  }
  else
  {
    *a1 = *a3 + sub_4D33A0(a5) % a3[2];
    v10 = sub_4D33A0(a5) % a3[3];
    result = a3[1];
    *a2 = result + v10;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C1C0 sub_48C1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_48C1C0(uint32_t *this, int a2)
{
  int v2; // edx

  switch ( a2 )
  {
    case 5:
      v2 = *(this + 2) * *(this + 116);
      return v2 / 100;
    case 4:
      v2 = *(this + 3) * *(this + 116);
      return v2 / 100;
    case 0:
      v2 = *(this + 4) * *(this + 116);
      return v2 / 100;
    default:
      break;
  }
  return *(this + 116);
}



// ------------------------------------------------------------
// 0x48C220 sub_48C220
// ------------------------------------------------------------
bool /*thiscall*/ sub_48C220(uint8_t *this, int a2)
{
  bool result; // al

  switch ( a2 )
  {
    case 0:
      result = (*(this + 396) & 4) == 4;
      break;
    case 1:
      result = (*(this + 396) & 1) == 1;
      break;
    case 2:
      result = (*(this + 396) & 2) == 2;
      break;
    case 3:
      result = (*(this + 396) & 8) == 8;
      break;
    default:
      result = false;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C2A0 sub_48C2A0
// ------------------------------------------------------------
int /*thiscall*/ sub_48C2A0(uint32_t *this, uint32_t *a2, int *a3, unsigned int a4, int a5, int a6)
{
  int v6; // eax
  int result; // eax

  sub_48C0E0(a2, a3, this + 4 * a4 + 100, a5, (int)&a6);
  v6 = a4;
  if ( a4 < 2 )
    v6 = 1;
  else
    LOBYTE(v6) = 0;
  result = (*(int (/*thiscall*/ **)(int, uint32_t *, int *, uint32_t, int, int, int, int))(*(uint32_t *)a5 + 140))(
             a5,
             a2,
             a3,
             *a2,
             *a3,
             200,
             v6,
             1);
  if ( (uint8_t)result == 0 )
    return off_77F3FC("FIND POS FAIL! %d %d %d", *this, a4, a6);
  return result;
}



// ------------------------------------------------------------
// 0x48C330 sub_48C330
// ------------------------------------------------------------
int /*thiscall*/ sub_48C330(uint32_t *this, uint32_t *a2, int *a3, int a4, int a5)
{
  int result; // eax

  sub_48C0E0(a2, a3, this + 69, a4, (int)&a5);
  result = (*(int (/*thiscall*/ **)(int, uint32_t *, int *, uint32_t, int, int, int, int))(*(uint32_t *)a4 + 140))(
             a4,
             a2,
             a3,
             *a2,
             *a3,
             200,
             1,
             1);
  if ( (uint8_t)result == 0 )
    return off_77F3FC("FIND POS FAIL! %d %d", *this, a5);
  return result;
}



// ------------------------------------------------------------
// 0x48C3A0 sub_48C3A0
// ------------------------------------------------------------
int /*thiscall*/ sub_48C3A0(uint32_t *this, int a2, uint32_t *a3, int *a4, int a5, char a6)
{
  uint32_t *v7; // [esp+Ch] [ebp-10h]
  uint32_t *v9; // [esp+14h] [ebp-8h]
  int v10; // [esp+18h] [ebp-4h]

  v7 = this + 4 * a2;
  v10 = 1000;
  v9 = v7 + 77;
  do
  {
    sub_48C0E0(a3, a4, v9, a5, (int)&a6);
    if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)a5 + 136))(a5, *a3, *a4, 0) == 1 )
      break;
    --v10;
  }
  while ( v10 != 0 );
  return off_77F3FC(aPvp_1, *v9, v7[78], v7[79], *(this + 4 * a2 + 80));
}



// ------------------------------------------------------------
// 0x48C440 sub_48C440
// ------------------------------------------------------------
bool /*thiscall*/ sub_48C440(int this, int a2, int a3)
{
  int v3; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax

  v3 = *(uint32_t *)(this + 392);
  if ( v3 == 0 )
    return false;
  v5 = *(uint32_t *)(v3 + 112);
  v6 = *(uint32_t *)(v3 + 116);
  if ( a3 == v6 )
  {
    if ( a2 == v5 - 1 )
    {
      v7 = 0;
    }
    else
    {
      if ( a2 != v5 + 1 )
        return false;
      v7 = 1;
    }
  }
  else
  {
    if ( a2 != v5 )
      return false;
    if ( a3 == v6 - 1 )
    {
      v7 = 2;
    }
    else
    {
      if ( a3 != v6 + 1 )
        return false;
      v7 = 3;
    }
  }
  return sub_48C220((uint8_t *)this, v7);
}



// ------------------------------------------------------------
// 0x48C4B0 sub_48C4B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48C4B0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  v3 = a1;
  for ( result = a3; v3 != a2; v5[5] = v6 )
  {
    v5 = result;
    *result = *v3;
    result[1] = v3[1];
    result[2] = v3[2];
    result[3] = v3[3];
    result[4] = v3[4];
    v6 = v3[5];
    v3 += 6;
    result += 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C500 sub_48C500
// ------------------------------------------------------------
void /*thiscall*/ sub_48C500(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // edx
  int v11; // edi
  int v12; // eax
  int v13; // edx

  if ( a2 != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2) - *(this + 116);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) - *(this + 117);
    if ( v3 >= 270 )
    {
      if ( v3 < 370 )
        goto LABEL_15;
      v9 = v3 - 370 + *(this + 116);
      *(this + 116) = v9;
      v6 = v9;
      if ( sub_425080(this) >= v9 )
        v7 = v6;
      else
        v7 = sub_425080(this);
    }
    else
    {
      v5 = v3 - 270 + *(this + 116);
      *(this + 116) = v5;
      v6 = v5;
      if ( sub_425080(this) >= v5 )
        v7 = v6;
      else
        v7 = sub_425080(this);
    }
    if ( v7 >= 0 )
    {
      if ( sub_425080(this) >= v6 )
        v8 = v6;
      else
        v8 = sub_425080(this);
    }
    else
    {
      v8 = 0;
    }
    *(this + 116) = v8;
LABEL_15:
    if ( v4 >= 160 )
    {
      if ( v4 < 240 )
        return;
      v13 = v4 - 240 + *(this + 117);
      *(this + 117) = v13;
      v11 = v13;
      if ( 120 * sub_424FF0(this) < v13 )
        goto LABEL_17;
    }
    else
    {
      v10 = v4 - 160 + *(this + 117);
      *(this + 117) = v10;
      v11 = v10;
      if ( 120 * sub_424FF0(this) < v10 )
      {
LABEL_17:
        v12 = 120 * sub_424FF0(this);
        goto LABEL_19;
      }
    }
    v12 = v11;
LABEL_19:
    if ( v12 >= 0 )
    {
      if ( 120 * sub_424FF0(this) >= v11 )
        *(this + 117) = v11;
      else
        *(this + 117) = 120 * sub_424FF0(this);
    }
    else
    {
      *(this + 117) = 0;
    }
  }
}



// ------------------------------------------------------------
// 0x48C680 sub_48C680
// ------------------------------------------------------------
char /*thiscall*/ sub_48C680(int this, int a2)
{
  char result; // al
  int v4; // edx
  int v5; // eax
  int v6; // ebx

  result = *(uint8_t *)(this + 472);
  if ( result == 0 )
  {
    result = sub_48C220((uint8_t *)this, a2);
    if ( result != 0 )
    {
      v5 = *(uint32_t *)(this + 392);
      v6 = *(uint32_t *)(v5 + 116);
      a2 = *(uint32_t *)(v5 + 112);
      switch ( v4 )
      {
        case 0:
          --a2;
          break;
        case 1:
          ++a2;
          break;
        case 2:
          LOBYTE(v6) = v6 - 1;
          break;
        case 3:
          LOBYTE(v6) = v6 + 1;
          break;
        default:
          break;
      }
      sub_423200(dword_8F7B08, 48);
      HIBYTE(a2) = a2;
      sub_423290((char *)&a2 + 3, 1);
      HIBYTE(a2) = v6;
      sub_423290((char *)&a2 + 3, 1);
      result = sub_423380(dword_8F7B08);
      *(uint8_t *)(this + 472) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C730 sub_48C730
// ------------------------------------------------------------
int */*thiscall*/ sub_48C730(uint32_t *this, int a2, char a3)
{
  int v4; // eax
  int *v5; // edi
  int *result; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // ebx
  int v10; // esi
  int v11; // edi
  int v12; // ebx
  int i; // esi
  int *v14; // [esp+8h] [ebp-Ch]
  int v15; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]
  int *v18; // [esp+20h] [ebp+Ch]

  v4 = 16 * ((a3 != 0) + 2 * a2);
  v5 = *(int **)((char *)this + v4 + 24);
  result = (uint32_t *)((char *)this + v4 + 20);
  v14 = result;
  if ( v5 != nullptr )
  {
    v17 = result[2];
    result = (int *)((v17 - (int)v5) >> 3);
    if ( result != nullptr )
    {
      v7 = *(this + 98);
      v9 = sub_48C1C0(this, a2) - *(uint32_t *)(v7 + 192);
      result = v5;
      v16 = v9;
      v15 = *(uint32_t *)(v7 + 196) - *(uint32_t *)(v8 + 468);
      v18 = v5;
      if ( v5 != (int *)v17 )
      {
        while ( 1 )
        {
          v10 = *result;
          v11 = result[1];
          sub_4938F0(*result);
          v12 = -((v11 + v9) % v11);
          if ( *(uint32_t *)(v10 + 148) == -1 )
          {
            sub_4938F0(v10);
            if ( *(uint32_t *)(v10 + 148) == -1 )
              sub_4938F0(v10);
          }
          for ( i = v12 + (uint64_t)((double)*(int *)(v10 + 72) * *(float *)(v10 + 80)); i > 0; v12 -= v11 )
            i -= v11;
          for ( ; i < 640; v12 += v11 )
          {
            sub_491D00(dword_79C0B0, v12, v15, 0.0);
            i += v11;
          }
          result = v18 + 2;
          v18 += 2;
          if ( v18 == (int *)v14[2] )
            break;
          v9 = v16;
          result = v18;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48C860 sub_48C860
// ------------------------------------------------------------
int */*thiscall*/ sub_48C860(int **this, int a2)
{
  int *v2; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax

  v2 = *(this + 54);
  if ( v2 == *(this + 55) )
    return nullptr;
  while ( 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
    if ( v4 >= *v2 && v4 < *v2 + v2[2] )
    {
      v5 = v2[1];
      if ( v3 >= v5 && v3 < v5 + v2[3] )
        break;
    }
    v2 += 6;
    if ( v2 == *(this + 55) )
      return nullptr;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x48C8E0 sub_48C8E0
// ------------------------------------------------------------
void /*thiscall*/ sub_48C8E0(uint32_t *this)
{
  unsigned int i; // esi
  int v3; // ecx
  void *v4; // eax

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 74);
    if ( v3 == 0 || i >= (*(this + 75) - v3) >> 2 )
      break;
    v4 = (void *)sub_41ACF0(v3 + 4 * i);
    sub_432EA0(v4, -1, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x48C920 sub_48C920
// ------------------------------------------------------------
int /*thiscall*/ sub_48C920(uint32_t *this, uint32_t *a2, uint32_t *a3, int a4, int ArgList, int a6)
{
  uint32_t *v6; // esi
  uint32_t *v7; // ecx
  int result; // eax

  v6 = (uint32_t *)*(this + 54);
  v7 = (uint32_t *)*(this + 55);
  if ( v6 == v7 )
    return off_77F3FC(aCriticalError_10, ArgList, a6);
  while ( v6[4] != ArgList || v6[5] != a6 )
  {
    v6 += 6;
    if ( v6 == v7 )
      return off_77F3FC(aCriticalError_10, ArgList, a6);
  }
  *a2 = *v6 + v6[2] / 2;
  result = v6[1] + v6[3] / 2;
  *a3 = result;
  return result;
}



// ------------------------------------------------------------
// 0x48C990 sub_48C990
// ------------------------------------------------------------
char /*thiscall*/ sub_48C990(uint32_t *this, int a2, int a3)
{
  uint32_t *v3; // eax
  uint32_t *v4; // ecx

  v3 = (uint32_t *)*(this + 123);
  v4 = (uint32_t *)*(this + 124);
  if ( v3 == v4 )
    return 0;
  while ( *v3 != a2 || v3[1] != a3 )
  {
    v3 += 2;
    if ( v3 == v4 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x48C9D0 sub_48C9D0
// ------------------------------------------------------------
int /*thiscall*/ sub_48C9D0(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v5; // eax

  if ( a2 >= sub_424FF0(this) )
    return 0;
  v4 = *(this + 91);
  if ( v4 != 0 )
    v5 = (*(this + 92) - v4) >> 5;
  else
    v5 = 0;
  return *(this + 95) + 32 * (a3 + a2 * v5);
}



// ------------------------------------------------------------
// 0x48CA20 sub_48CA20
// ------------------------------------------------------------
int */*thiscall*/ sub_48CA20(uint32_t *this, int a2, char a3)
{
  int *result; // eax
  unsigned int v5; // ebx
  int v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // edx
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  int v14; // ebx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // eax
  int v19; // edx
  unsigned int v20; // ecx
  int v21; // ecx
  int v22; // eax
  uint32_t *v23; // edi
  uint32_t *v24; // eax
  unsigned int v25; // [esp-4h] [ebp-1Ch]
  unsigned int v26; // [esp-4h] [ebp-1Ch]
  int v27; // [esp+Ch] [ebp-Ch]
  int v28; // [esp+10h] [ebp-8h]
  uint32_t *v29; // [esp+14h] [ebp-4h]
  int v30; // [esp+14h] [ebp-4h]
  int i; // [esp+20h] [ebp+8h]
  unsigned int v32; // [esp+24h] [ebp+Ch]

  result = sub_48C730(this, a2, a3);
  if ( a2 == 3 && a3 == 0 )
  {
    v5 = (*(this + 116) - *(uint32_t *)(*(this + 98) + 192)) / 224;
    v6 = -((*(this + 116) - *(uint32_t *)(*(this + 98) + 192)) % 224);
    v32 = v5;
    v28 = v6;
    result = (int *)sub_424FF0(this);
    v27 = (int)result;
    if ( v6 < 640 )
    {
      v7 = 32 * v5;
      for ( i = 32 * v5; ; v7 = i )
      {
        v8 = *(this + 91);
        if ( v8 == 0 )
          break;
        result = (int *)((*(this + 92) - v8) >> 5);
        if ( v5 >= (unsigned int)result )
          break;
        v9 = *(uint32_t *)(*(this + 98) + 196) - *(this + 117);
        v10 = *(this + 91);
        v11 = *(uint32_t *)(v10 + v7);
        v12 = (uint32_t *)(v7 + v10);
        v29 = v12;
        if ( v11 != -1 )
        {
          v25 = v12[1];
          v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, *v12);
          v29[2] = sub_418DD0(v13, v25);
          v7 = i;
        }
        sub_424760(dword_79C0B0, v6, v9, *(uint32_t *)(*(this + 91) + v7 + 8), 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        result = (int *)v27;
        v14 = v9 + 480;
        v30 = 0;
        if ( v27 > 0 )
        {
          do
          {
            v15 = *(this + 91);
            if ( v15 != 0 && (*(this + 92) - v15) >> 5 != 0 )
            {
              v17 = *(this + 95);
              if ( v17 != 0 )
                v18 = (*(this + 96) - v17) >> 5;
              else
                v18 = 0;
              v19 = *(this + 91);
              if ( v19 != 0 )
                v20 = (*(this + 92) - v19) >> 5;
              else
                v20 = 0;
              v16 = v18 / v20;
            }
            else
            {
              v16 = 0;
            }
            if ( v30 >= v16 )
            {
              v23 = nullptr;
            }
            else
            {
              v21 = *(this + 91);
              if ( v21 != 0 )
                v22 = (*(this + 92) - v21) >> 5;
              else
                v22 = 0;
              v23 = (uint32_t *)(*(this + 95) + 32 * (v32 + v30 * v22));
            }
            if ( *v23 != -1 )
            {
              v26 = v23[1];
              v24 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, *v23);
              v23[2] = sub_418DD0(v24, v26);
            }
            sub_424760(dword_79C0B0, v28, v14, v23[2], 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
            v14 += 120;
            result = (int *)++v30;
          }
          while ( v30 < v27 );
          v6 = v28;
        }
        v6 += 224;
        ++v32;
        i += 32;
        v28 = v6;
        if ( v6 >= 640 )
          break;
        v5 = v32;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x48CC70 sub_48CC70
// ------------------------------------------------------------
int /*thiscall*/ sub_48CC70(uint32_t *this, int a2, int a3)
{
  int v3; // esi
  unsigned int v4; // edi
  int v5; // edx
  int v6; // eax

  v3 = a3;
  v4 = a2 / 14;
  if ( a3 >= 30 )
  {
    v3 = (a3 - 30) % 10;
    v6 = sub_48C9D0(this, (a3 - 30) / 10, a2 / 14);
  }
  else
  {
    v5 = *(this + 91);
    if ( v5 == 0 || v4 >= (*(this + 92) - v5) >> 5 )
      return 2;
    v6 = v5 + 32 * v4;
  }
  if ( v6 == 0 )
    return 2;
  return *(uint32_t *)(*(uint32_t *)(16 * v3 + *(uint32_t *)(v6 + 20) + 4) + 4 * (a2 % 14));
}



// ------------------------------------------------------------
// 0x48CCF0 sub_48CCF0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_48CCF0(uint32_t *this, int a2, int a3, int a4)
{
  unsigned int result; // eax
  int v5; // esi
  unsigned int v6; // edi
  int v7; // edx

  result = a2 / 14;
  v5 = a3;
  v6 = a2 / 14;
  if ( a3 >= 30 )
  {
    v5 = (a3 - 30) % 10;
    result = sub_48C9D0(this, (a3 - 30) / 10, a2 / 14);
LABEL_6:
    if ( result != 0 )
    {
      result = *(uint32_t *)(16 * v5 + *(uint32_t *)(result + 20) + 4) + 4 * (a2 % 14);
      *(uint32_t *)result = a4;
    }
    return result;
  }
  v7 = *(this + 91);
  if ( v7 != 0 )
  {
    result = (*(this + 92) - v7) >> 5;
    if ( v6 < result )
    {
      result = v7 + 32 * v6;
      goto LABEL_6;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48CD70 sub_48CD70
// ------------------------------------------------------------
char /*thiscall*/ sub_48CD70(uint32_t *this, int a2)
{
  int v4; // eax
  int v5; // edi
  int v6; // edi
  int v7; // edi
  int v8; // ebx
  int v9; // ecx
  int v10; // edx
  uint32_t *v11; // ebx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // eax
  int j; // edi
  int v17; // eax
  int v19; // [esp+Ch] [ebp-10h]
  int v20; // [esp+10h] [ebp-Ch]
  int v21; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int v24; // [esp+24h] [ebp+8h]
  int v25; // [esp+24h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 33) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 672))(a2) + 21) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2) < 0 )
      return 0;
    v4 = *(this + 91);
    v5 = v4 != 0 ? (*(this + 92) - v4) >> 5 : 0;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2) >= 224 * v5 )
      return 0;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) < 0 )
      return 0;
    v6 = 120 * (sub_424FF0(this) + 3);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) >= v6 )
      return 0;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 428))(a2) != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 432))(a2) != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 448))(a2);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 440))(a2) / 16;
    v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 452))(a2);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 444))(a2) / 16;
    v25 = v24 / 12;
    v21 = v9;
    v10 = v8 < 0 ? 0 : v8;
    v11 = this;
    v19 = v10;
    v20 = v7 / 12 < 0 ? 0 : v7 / 12;
    v12 = *(this + 91);
    if ( v12 != 0 )
      v13 = (*(this + 92) - v12) >> 5;
    else
      v13 = 0;
    if ( 14 * v13 - 1 < v9 )
    {
      v14 = *(this + 91);
      if ( v14 != 0 )
        v15 = (*(this + 92) - v14) >> 5;
      else
        v15 = 0;
      v21 = 14 * v15 - 1;
    }
    if ( 10 * sub_424FF0(this) + 29 < v25 )
      v25 = 10 * sub_424FF0(this) + 29;
    for ( i = v19; i <= v21; ++i )
    {
      for ( j = v20; j <= v25; ++j )
      {
        v17 = sub_48CC70(v11, i, j) - 1;
        if ( v17 != 0 )
        {
          if ( v17 == 1 )
            return 0;
        }
        else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 436))(a2) <= 0 )
        {
          return 0;
        }
      }
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x48CF90 sub_48CF90
// ------------------------------------------------------------
void /*thiscall*/ sub_48CF90(int this, int a2, unsigned int a3, int a4)
{
  void *v4; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // edx
  int v10; // edx
  unsigned int v11; // eax
  int v12; // edx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-40h]
  int v25; // [esp-Ch] [ebp-34h]
  unsigned int v26; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v4 = *(void **)(a4 + 4);
  v28[0] = *(void **)a4;
  v6 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v9 = 0;
    if ( 0x1FFFFFFF - v9 < a3 )
      sub_42CB90(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, a2 + v21);
        v26 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, v22 - v30, v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, a2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 3;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 3;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v31 = 8 * v11;
      v14 = (char *)operator new(8 * v11);
      v24 = *(uint32_t *)(this + 4);
      v28[2] = v14;
      v29 = 0;
      v32 = sub_44BD30(v24, a2, v14);
      sub_63A7C0(v32, a3, v28);
      sub_44BD30(a2, *(uint32_t *)(this + 8), v32 + 8 * a3);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 3;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v31];
      *(uint32_t *)(this + 8) = &v14[8 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x48D1E0 sub_48D1E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48D1E0(uint32_t *this, int a2)
{
  int v2; // eax
  size_t v4; // edi
  char *v5; // eax
  int v7; // [esp-18h] [ebp-38h]
  int v8; // [esp-14h] [ebp-34h]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *v10; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(a2 + 4);
  v11 = &v9;
  v10 = this;
  if ( v2 != 0 )
    v4 = *(uint32_t *)(a2 + 8) - v2;
  else
    v4 = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( v4 != 0 )
  {
    v5 = (char *)operator new(v4);
    *(this + 1) = v5;
    *(this + 2) = v5;
    *(this + 3) = &v5[v4];
    v8 = *(uint32_t *)(a2 + 8);
    v7 = *(uint32_t *)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_4460D0(v7, v8, v5);
  }
  return this;
}



// ------------------------------------------------------------
// 0x48D290 sub_48D290
// ------------------------------------------------------------
int /*thiscall*/ sub_48D290(int this, int a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *v7; // edi
  unsigned int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

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
      v12 = *(uint32_t *)(a2 + 4) + 24 * sub_4FEF30(this);
      sub_4919B0(*(uint32_t *)(a2 + 4), v12, v7);
      *(uint32_t *)(this + 8) = sub_4FF050(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
      j__free(*(void **)(this + 4));
    v11 = sub_4FEF30(a2);
    if ( (uint8_t)sub_42D0E0(v11) != 0 )
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
// 0x48D410 sub_48D410
// ------------------------------------------------------------
int /*thiscall*/ sub_48D410(int this, int a2)
{
  int v3; // ebx
  unsigned int v4; // eax
  int v6; // ecx
  unsigned int v7; // edx
  int v8; // eax
  int v9; // edi
  unsigned int v10; // edx
  int v11; // eax
  int v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 4) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(uint32_t *)(this + 4);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 8) - v6) >> 4;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    sub_54E1B0(v3, *(uint32_t *)(a2 + 8), v6);
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(a2 + 8) - v8) >> 4);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != 0 )
    v10 = (*(uint32_t *)(this + 12) - v6) >> 4;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != 0 )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 4;
    else
      v14 = 0;
    if ( (uint8_t)sub_42D090(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_54E680(*(uint32_t *)(a2 + 4), *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  if ( v6 != 0 )
    v11 = (*(uint32_t *)(this + 8) - v6) >> 4;
  else
    v11 = 0;
  v12 = *(uint32_t *)(a2 + 4) + 16 * v11;
  sub_54E660(*(uint32_t *)(a2 + 4), v12, *(uint32_t *)(this + 4));
  *(uint32_t *)(this + 8) = sub_602460(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x48D570 sub_48D570
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D570(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *v4 = *v3;
    v4[1] = v3[1];
    sub_446AB0(v3 + 2);
    v4[6] = v3[6];
    v4[7] = v3[7];
    v4[8] = v3[8];
    v4[9] = v3[9];
    v4[10] = v3[10];
    v3 += 11;
    v4 += 11;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x48D5D0 sub_48D5D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D5D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(v3 - 11);
    v3 -= 11;
    v4 -= 11;
    *v4 = v5;
    v4[1] = v3[1];
    sub_446AB0(v3 + 2);
    v4[6] = v3[6];
    v4[7] = v3[7];
    v4[8] = v3[8];
    v4[9] = v3[9];
    v4[10] = v3[10];
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x48D630 sub_48D630
// ------------------------------------------------------------
void /*thiscall*/ sub_48D630(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) >> 3 )
  {
    v5 = *(this + 2);
    sub_63A7C0(v5, 1, a2);
    *(this + 2) = v5 + 8;
  }
  else
  {
    sub_48CF90((int)this, (uint32_t *)*(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x48D6A0 sub_48D6A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D6A0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 11 )
  {
    *i = *a3;
    i[1] = a3[1];
    sub_446AB0(a3 + 2);
    i[6] = a3[6];
    i[7] = a3[7];
    i[8] = a3[8];
    i[9] = a3[9];
    i[10] = a3[10];
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48D700 sub_48D700
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D700(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_48D5D0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x48D720 sub_48D720
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_48D720(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
    {
      *v3 = *a1;
      v3[1] = a1[1];
      sub_48D1E0(v3 + 2, (int)(a1 + 2));
      v3[6] = a1[6];
      v3[7] = a1[7];
      v3[8] = a1[8];
      v3[9] = a1[9];
      v3[10] = a1[10];
    }
    v3 += 11;
    LOBYTE(v7) = 0;
    a1 += 11;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x48D800 sub_48D800
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48D800(uint32_t **this, uint32_t *a2, uint32_t *a3)
{
  int v4; // edi
  int v5; // esi

  sub_48D570(a3 + 11, *(this + 2), a3);
  v4 = (int)*(this + 2);
  v5 = v4 - 44;
  do
  {
    sub_42C220(v5);
    v5 += 44;
  }
  while ( v5 != v4 );
  *(this + 2) -= 11;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x48D860 sub_48D860
// ------------------------------------------------------------
void /*cdecl*/ sub_48D860(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v3 = a1;
  v4[5] = v4;
  v4[4] = a1;
  v5 = 0;
  while ( a2 != 0 )
  {
    v4[3] = v3;
    LOBYTE(v5) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a3;
      v3[1] = a3[1];
      sub_48D1E0(v3 + 2, (int)(a3 + 2));
      v3[6] = a3[6];
      v3[7] = a3[7];
      v3[8] = a3[8];
      v3[9] = a3[9];
      v3[10] = a3[10];
    }
    v3 += 11;
    LOBYTE(v5) = 0;
    --a2;
  }
}



// ------------------------------------------------------------
// 0x48D940 sub_48D940
// ------------------------------------------------------------
char */*cdecl*/ sub_48D940(char *a1, char *a2, char *a3)
{
  char *v3; // esi
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
      sub_435020(a1);
    v3 += 16;
    LOBYTE(v7) = 0;
    a1 += 16;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x48D9D0 sub_48D9D0
// ------------------------------------------------------------
int /*thiscall*/ sub_48D9D0(int this)
{
  *(uint32_t *)(this + 392) = 0;
  *(uint8_t *)(this + 396) = 0;
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
  *(uint8_t *)(this + 472) = 0;
  *(uint32_t *)(this + 476) = 0;
  *(uint32_t *)(this + 480) = 0;
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  return sub_42E620(this + 504);
}



// ------------------------------------------------------------
// 0x48DA40 sub_48DA40
// ------------------------------------------------------------
char /*thiscall*/ sub_48DA40(int *this, int a2, int a3, char a4)
{
  int *v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // ecx
  uint32_t *v10; // edi
  uint32_t *v11; // eax
  uint8_t *v12; // eax
  uint8_t *v13; // esi
  int v14; // edx
  bool v15; // cc
  int v16; // esi
  int v17; // ecx
  int i; // eax
  int v19; // eax
  int v22; // [esp+8h] [ebp-10h]
  int v23; // [esp+10h] [ebp-8h] BYREF
  int v24; // [esp+14h] [ebp-4h]

  v4 = this;
  v5 = *(this + 120);
  if ( v5 != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( v5 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      if ( *(uint32_t *)(v5 + 104) != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
        v6 = v4[91];
        if ( v6 != 0 )
          v7 = (v4[92] - v6) >> 5;
        else
          v7 = 0;
        v8 = 14 * v7;
        v24 = 14 * v7;
        v5 = 10 * (sub_424FF0(v4) + 3);
        qmemcpy((void *)v4[120], (const void *)v4[121], v8 * v5);
        v22 = v5;
        LOBYTE(v5) = a4;
        if ( a4 != 0 )
        {
          v5 = v4[127];
          v9 = v4[128];
          if ( v5 != v9 )
          {
            while ( *(uint32_t *)v5 != a2 || *(uint32_t *)(v5 + 4) != a3 )
            {
              v5 += 44;
              if ( v5 == v9 )
                goto LABEL_14;
            }
            LOBYTE(v5) = sub_48D800(&v23, v5);
          }
        }
LABEL_14:
        v10 = (uint32_t *)v4[127];
        if ( v10 != (uint32_t *)v4[128] )
        {
          do
          {
            if ( *v10 == a2 && v10[1] == a3 && a4 == 0 )
            {
              v11 = (uint32_t *)sub_45EBE0(a2, a3);
              v12 = __RTDynamicCast(
                      v11,
                      0,
                      &CNRDObject `RTTI Type Descriptor',
                      &CNRDPassiveObject `RTTI Type Descriptor',
                      0);
              v13 = v12;
              if ( v12 != nullptr )
              {
                v10[6] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v12 + 440))(v12) / 16 - 1;
                v10[7] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v13 + 448))(v13) / 12 - 1;
                v10[8] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v13 + 444))(v13) / 16 + 1;
                v10[9] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v13 + 452))(v13) / 12;
                v10[10] = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v13 + 672))(v13) + 8);
              }
            }
            v14 = v10[7];
            v15 = v14 <= v10[9];
            v23 = v14;
            if ( v15 )
            {
              v16 = v24;
              v17 = v24 * v14;
              do
              {
                if ( v14 >= 0 && v14 < v22 )
                {
                  for ( i = v10[6]; i <= v10[8]; ++i )
                  {
                    if ( i >= 0 && i < v16 )
                    {
                      *(uint8_t *)(v17 + i + v4[120]) = *((uint8_t *)v10 + 40);
                      v4 = this;
                      v14 = v23;
                      v16 = v24;
                    }
                  }
                }
                v19 = v10[9];
                ++v14;
                v17 += v16;
                v23 = v14;
              }
              while ( v14 <= v19 );
            }
            v5 = v4[128];
            v10 += 11;
          }
          while ( v10 != (uint32_t *)v5 );
        }
      }
    }
  }
  return v5;
}


// ------------------------------------------------------------
// 0x48DC80 sub_48DC80
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_48DC80(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_48D860(a1, a2, a3);
  return &a1[11 * a2];
}



// ------------------------------------------------------------
// 0x48DCB0 sub_48DCB0
// ------------------------------------------------------------
void /*thiscall*/ sub_48DCB0(int *this, char *a2, unsigned int a3, int *a4)
{
  int v4; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // ebx
  unsigned int v12; // ecx
  int v14; // eax
  int v15; // eax
  unsigned int v16; // ecx
  int v17; // eax
  char *v18; // ebx
  int v19; // eax
  unsigned int v20; // edi
  int v21; // eax
  uint32_t *v22; // ecx
  int v24; // edi
  uint32_t *v25; // [esp-18h] [ebp-68h]
  uint32_t *v26; // [esp-Ch] [ebp-5Ch]
  int v27; // [esp-8h] [ebp-58h]
  int v28; // [esp+0h] [ebp-50h] BYREF
  uint32_t v29[2]; // [esp+Ch] [ebp-44h] BYREF
  int v30; // [esp+14h] [ebp-3Ch] BYREF
  void *v31; // [esp+18h] [ebp-38h]
  int v32; // [esp+24h] [ebp-2Ch]
  int v33; // [esp+28h] [ebp-28h]
  int v34; // [esp+2Ch] [ebp-24h]
  int v35; // [esp+30h] [ebp-20h]
  int v36; // [esp+34h] [ebp-1Ch]
  void *Block; // [esp+38h] [ebp-18h]
  int *v38; // [esp+3Ch] [ebp-14h]
  int *v39; // [esp+40h] [ebp-10h]
  int v40; // [esp+4Ch] [ebp-4h]
  uint32_t *v41; // [esp+58h] [ebp+8h]
  uint32_t *v42; // [esp+5Ch] [ebp+Ch]
  int v43; // [esp+60h] [ebp+10h]
  uint32_t *v44; // [esp+60h] [ebp+10h]

  v4 = *a4;
  v6 = a4[1];
  v39 = &v28;
  v29[1] = v6;
  v38 = this;
  v29[0] = v4;
  sub_48D1E0(&v30, (int)(a4 + 2));
  v7 = a4[7];
  v8 = a4[8];
  v32 = a4[6];
  v9 = a4[9];
  v33 = v7;
  v10 = a4[10];
  v34 = v8;
  v35 = v9;
  v36 = v10;
  v11 = *(this + 1);
  v12 = 0;
  v40 = 0;
  if ( v11 != 0 )
    v12 = (*(this + 3) - v11) / 44;
  if ( a3 != 0 )
  {
    if ( v11 != 0 )
      v14 = (*(this + 2) - v11) / 44;
    else
      v14 = 0;
    if ( 97612893 - v14 < a3 )
      sub_42CB90(this);
    if ( v11 != 0 )
      v15 = (*(this + 2) - v11) / 44;
    else
      v15 = 0;
    if ( v12 >= a3 + v15 )
    {
      v22 = (uint32_t *)*(this + 2);
      v44 = v22;
      if ( ((char *)v22 - a2) / 44 >= a3 )
      {
        v41 = &v22[-11 * a3];
        *(this + 2) = (int)sub_48D720(v41, v22, v22);
        sub_48D700(a2, v41, v44);
        sub_48D6A0(a2, &a2[44 * a3], v29);
      }
      else
      {
        sub_48D720(a2, v22, &a2[44 * a3]);
        v27 = a3 - (*(this + 2) - (int)a2) / 44;
        v26 = (uint32_t *)*(this + 2);
        LOBYTE(v40) = 3;
        sub_48DC80(v26, v27, v29);
        v24 = 44 * a3 + *(this + 2);
        *(this + 2) = v24;
        v40 = 0;
        sub_48D6A0(a2, (uint32_t *)(v24 - 44 * a3), v29);
      }
    }
    else
    {
      if ( 97612893 - (v12 >> 1) >= v12 )
        v16 = (v12 >> 1) + v12;
      else
        v16 = 0;
      if ( v11 != 0 )
        v17 = (*(this + 2) - v11) / 44;
      else
        v17 = 0;
      if ( v16 < a3 + v17 )
        v16 = a3 + sub_527B90(this);
      v43 = 44 * v16;
      v18 = (char *)operator new(44 * v16);
      v25 = (uint32_t *)*(this + 1);
      Block = v18;
      LOBYTE(v40) = 1;
      v42 = sub_48D720(v25, a2, v18);
      sub_48D860(v42, a3, v29);
      sub_48D720(a2, (uint32_t *)*(this + 2), &v42[11 * a3]);
      v19 = *(this + 1);
      if ( v19 != 0 )
        v19 = (*(this + 2) - v19) / 44;
      v20 = v19 + a3;
      v21 = *(this + 1);
      if ( v21 != 0 )
      {
        sub_42DDA0(v21, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v18[v43];
      *(this + 2) = (int)&v18[44 * v20];
      *(this + 1) = (int)v18;
    }
  }
  if ( v31 != nullptr )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x48DFD0 sub_48DFD0
// ------------------------------------------------------------
int /*thiscall*/ sub_48DFD0(int this, int a2)
{
  int v3; // ebx
  unsigned int v4; // eax
  int v6; // ecx
  unsigned int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // edi
  unsigned int v11; // edx
  int v12; // eax
  void *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(a2 + 8) - v3) >> 4) == 0 )
  {
    sub_42D540(this);
    return this;
  }
  v6 = *(uint32_t *)(this + 4);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 8) - v6) >> 4;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    v8 = sub_489540(v3, *(uint32_t *)(a2 + 8), v6);
    sub_42CC00(v8, *(uint32_t *)(this + 8));
    v9 = *(uint32_t *)(a2 + 4);
    if ( v9 != 0 )
      v10 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(a2 + 8) - v9) >> 4);
    else
      v10 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v10;
    return this;
  }
  if ( v6 != 0 )
    v11 = (*(uint32_t *)(this + 12) - v6) >> 4;
  else
    v11 = 0;
  if ( v4 > v11 )
  {
    if ( v6 != 0 )
    {
      sub_42D520(v6, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v14 = *(uint32_t *)(a2 + 4);
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(a2 + 8) - v14) >> 4;
    else
      v15 = 0;
    if ( (uint8_t)sub_42D090(v15) != 0 )
      *(uint32_t *)(this + 8) = sub_474CA0(this, *(void **)(a2 + 4), *(uint32_t *)(a2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( v6 != 0 )
    v12 = (*(uint32_t *)(this + 8) - v6) >> 4;
  else
    v12 = 0;
  v13 = (void *)(*(uint32_t *)(a2 + 4) + 16 * v12);
  sub_489690(*(uint32_t *)(a2 + 4), (int)v13, *(uint32_t *)(this + 4));
  *(uint32_t *)(this + 8) = sub_474680(v13, *(uint32_t *)(a2 + 8), *(void **)(this + 8), this);
  return this;
}



// ------------------------------------------------------------
// 0x48E130 sub_48E130
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_48E130(int *this, uint32_t *a2, char *a3, int *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 44 != 0 )
    v6 = (int)&a3[-v5] / 44;
  else
    v6 = 0;
  sub_48DCB0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 44 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x48E1A0 sub_48E1A0
// ------------------------------------------------------------
char **/*thiscall*/ sub_48E1A0(char **this, int a2)
{
  int v3; // ecx
  int v4; // eax
  char *v6; // [esp-14h] [ebp-34h]
  char *v7; // [esp-10h] [ebp-30h]
  char *v8; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(a2 + 4);
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 4;
  else
    v4 = 0;
  if ( (uint8_t)sub_42D090(v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = *(char **)(a2 + 8);
    v6 = *(char **)(a2 + 4);
    v9[7] = 0;
    *(this + 2) = sub_48D940(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x48E240 sub_48E240
// ------------------------------------------------------------
int /*cdecl*/ sub_48E240(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *(uint32_t *)v4 = *(uint32_t *)v3;
    *(uint32_t *)(v4 + 4) = *(uint32_t *)(v3 + 4);
    *(uint32_t *)(v4 + 8) = *(uint32_t *)(v3 + 8);
    *(uint8_t *)(v4 + 12) = *(uint8_t *)(v3 + 12);
    sub_48DFD0(v4 + 16, v3 + 16);
    v3 += 32;
    v4 += 32;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x48E290 sub_48E290
// ------------------------------------------------------------
int /*cdecl*/ sub_48E290(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 32);
    v3 -= 32;
    v4 -= 32;
    *(uint32_t *)v4 = v5;
    *(uint32_t *)(v4 + 4) = *(uint32_t *)(v3 + 4);
    *(uint32_t *)(v4 + 8) = *(uint32_t *)(v3 + 8);
    *(uint8_t *)(v4 + 12) = *(uint8_t *)(v3 + 12);
    sub_48DFD0(v4 + 16, v3 + 16);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x48E2E0 sub_48E2E0
// ------------------------------------------------------------
int /*stdcall*/ sub_48E2E0(int a1, int a2, const char *ArgList)
{
  unsigned int *v3; // eax
  int v4; // esi
  int v6; // eax
  uint32_t *v7; // eax
  unsigned int v8; // [esp-4h] [ebp-Ch]

  v3 = (unsigned int *)(*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84D8 + 12))(
                         dword_8F84D8,
                         "%s%s",
                         a2,
                         ArgList);
  v4 = (int)v3;
  if ( v3 == nullptr )
    return off_77F3FC("TILE CREATE FAIL! FILENAME[%s]", ArgList);
  if ( sub_40BF00((std::_String_base *)v3, 0, v3[5], szPassword, 0) != 0 )
  {
    v6 = sub_4BC700((uint32_t *)dword_8F84BC, v4);
    *(uint32_t *)a1 = v6;
    *(uint32_t *)(a1 + 4) = *(uint32_t *)(v4 + 28);
    v8 = *(uint32_t *)(v4 + 28);
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v6);
    *(uint32_t *)(a1 + 8) = sub_418DD0(v7, v8);
  }
  *(uint8_t *)(a1 + 12) = *(uint8_t *)(v4 + 32);
  return sub_48DFD0(a1 + 16, v4 + 36);
}



// ------------------------------------------------------------
// 0x48E380 sub_48E380
// ------------------------------------------------------------
void /*thiscall*/ sub_48E380(int this, int *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 44;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) / 44 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_48D860(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 11;
  }
  else
  {
    sub_48E130((int *)this, &a2, *(char **)(this + 8), a2);
  }
}



// ------------------------------------------------------------
// 0x48E410 sub_48E410
// ------------------------------------------------------------
int /*cdecl*/ sub_48E410(int a1, int a2, int a3)
{
  int result; // eax
  int i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 32 )
  {
    *(uint32_t *)i = *(uint32_t *)a3;
    *(uint32_t *)(i + 4) = *(uint32_t *)(a3 + 4);
    *(uint32_t *)(i + 8) = *(uint32_t *)(a3 + 8);
    *(uint8_t *)(i + 12) = *(uint8_t *)(a3 + 12);
    sub_48DFD0(i + 16, a3 + 16);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48E460 sub_48E460
// ------------------------------------------------------------
int /*cdecl*/ sub_48E460(int a1, int a2, int a3)
{
  return sub_48E290(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x48E480 sub_48E480
// ------------------------------------------------------------
int /*thiscall*/ sub_48E480(int this, int a2)
{
  int result; // eax
  int v4; // esi
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  unsigned int v8; // ebx
  int v9; // ecx
  int *v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // edi
  int v15; // edx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int i; // edi
  int v23; // eax
  uint32_t v24[3]; // [esp+8h] [ebp-64h] BYREF
  int v25; // [esp+14h] [ebp-58h]
  int v26; // [esp+18h] [ebp-54h]
  int v27; // [esp+1Ch] [ebp-50h]
  int v28; // [esp+20h] [ebp-4Ch]
  int v29; // [esp+24h] [ebp-48h]
  int v30; // [esp+28h] [ebp-44h]
  int v31; // [esp+2Ch] [ebp-40h]
  int v32; // [esp+30h] [ebp-3Ch]
  uint32_t v33[2]; // [esp+34h] [ebp-38h] BYREF
  int v34; // [esp+3Ch] [ebp-30h]
  unsigned int v35; // [esp+40h] [ebp-2Ch]
  int v36; // [esp+44h] [ebp-28h]
  int v37; // [esp+48h] [ebp-24h]
  int v38; // [esp+4Ch] [ebp-20h]
  int v39; // [esp+50h] [ebp-1Ch]
  int v40; // [esp+54h] [ebp-18h]
  int v41; // [esp+58h] [ebp-14h]
  int v42; // [esp+5Ch] [ebp-10h]
  int v43; // [esp+68h] [ebp-4h]

  result = *(uint32_t *)(this + 480);
  v39 = this;
  if ( result != 0 )
  {
    if ( *(uint32_t *)(this + 492) != 0 )
      j__free(*(void **)(this + 492));
    v4 = a2;
    *(uint32_t *)(this + 492) = 0;
    *(uint32_t *)(this + 496) = 0;
    *(uint32_t *)(this + 500) = 0;
    v5 = *(uint32_t *)(a2 + 120);
    if ( v5 != 0 )
      v38 = (*(uint32_t *)(a2 + 124) - v5) >> 2;
    else
      v38 = 0;
    v6 = *(uint32_t *)(this + 364);
    if ( v6 != 0 )
      v7 = (*(uint32_t *)(this + 368) - v6) >> 5;
    else
      v7 = 0;
    v37 = 14 * v7;
    v34 = 10 * (sub_424FF0(this) + 3);
    result = v38;
    v8 = 0;
    v35 = 0;
    if ( v38 > 0 )
    {
      while ( 1 )
      {
        v9 = *(uint32_t *)(v4 + 120);
        if ( v9 != 0 && v8 < (*(uint32_t *)(v4 + 124) - v9) >> 2 )
          v10 = *(int **)(v9 + 4 * v8);
        else
          v10 = nullptr;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v10 + 40))(v10, 33) != 0
          && (*(int (/*thiscall*/ **)(int *))(*v10 + 428))(v10) != 0
          && (*(int (/*thiscall*/ **)(int *))(*v10 + 432))(v10) != 0
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v10 + 672))(v10) + 8) != 0 )
        {
          v25 = 0;
          v26 = 0;
          v27 = 0;
          v11 = *v10;
          v43 = 0;
          v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 440))(v10);
          v13 = *v10;
          v42 = v12 / 16 - 1;
          v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 448))(v10) / 12 - 1;
          v41 = (*(int (/*thiscall*/ **)(int *))(*v10 + 444))(v10) / 16 + 1;
          v15 = (uint64_t)(715827883LL * (*(int (/*thiscall*/ **)(int *))(*v10 + 452))(v10)) >> 32;
          v16 = *v10;
          v17 = (v15 >> 1) + ((unsigned int)v15 >> 31);
          v28 = v42;
          v29 = v14;
          v30 = v41;
          v31 = v17;
          v18 = (*(int (/*thiscall*/ **)(int *))(v16 + 672))(v10);
          v19 = *v10;
          v32 = *(uint32_t *)(v18 + 8);
          v24[0] = (*(int (/*thiscall*/ **)(int *))(v19 + 48))(v10);
          v24[1] = (*(int (/*thiscall*/ **)(int *))(*v10 + 52))(v10);
          v20 = v14;
          v36 = v14;
          if ( v14 <= v17 )
          {
            v21 = v37;
            v40 = v37 * v14;
            do
            {
              if ( v20 >= 0 && v20 < v34 )
              {
                for ( i = v42; i <= v41; ++i )
                {
                  if ( i >= 0 && i < v21 )
                  {
                    v23 = (*(int (/*thiscall*/ **)(int *))(*v10 + 672))(v10);
                    *(uint8_t *)(i + v40 + *(uint32_t *)(v39 + 480)) = *(uint8_t *)(v23 + 8);
                    v20 = v36;
                    v21 = v37;
                  }
                }
              }
              v36 = ++v20;
              v40 += v21;
            }
            while ( v20 <= v17 );
          }
          v33[0] = (*(int (/*thiscall*/ **)(int *))(*v10 + 48))(v10);
          v33[1] = (*(int (/*thiscall*/ **)(int *))(*v10 + 52))(v10);
          sub_474950(v33);
          sub_48E380(v24);
          v8 = v35;
          v43 = -1;
          v25 = 0;
          v26 = 0;
          v27 = 0;
        }
        result = v38;
        v35 = ++v8;
        if ( (int)v8 >= v38 )
          break;
        v4 = a2;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x48E730 sub_48E730
// ------------------------------------------------------------
int */*thiscall*/ sub_48E730(int *this, int *a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // edi
  int i; // esi
  int *v11; // [esp+4h] [ebp-4h]

  v5 = a3;
  v11 = this;
  if ( a3 != a4 )
  {
    v6 = sub_48E240(a4, *(this + 2), a3);
    v7 = *(this + 2);
    v8 = v6;
    for ( i = v6; i != v7; i += 32 )
      sub_42DDD0(i);
    v5 = a3;
    v11[2] = v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x48E790 sub_48E790
// ------------------------------------------------------------
int /*cdecl*/ sub_48E790(int a1, int a2, int a3)
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
      *(uint32_t *)v3 = *(uint32_t *)a1;
      *(uint32_t *)(v3 + 4) = *(uint32_t *)(a1 + 4);
      *(uint32_t *)(v3 + 8) = *(uint32_t *)(a1 + 8);
      *(uint8_t *)(v3 + 12) = *(uint8_t *)(a1 + 12);
      sub_48E1A0((char **)(v3 + 16), a1 + 16);
    }
    v3 += 32;
    LOBYTE(v7) = 0;
    a1 += 32;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x48E870 sub_48E870
// ------------------------------------------------------------
int /*thiscall*/ sub_48E870(int this, int a2)
{
  void *v3; // eax
  uint32_t *v4; // esi
  void *v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // eax
  size_t v10; // esi
  int v11; // edi
  int v12; // esi
  int v14; // [esp+Ch] [ebp-14h]
  int v15; // [esp+10h] [ebp-10h]
  int v16; // [esp+14h] [ebp-Ch]
  const void **v17; // [esp+18h] [ebp-8h]
  int v18; // [esp+1Ch] [ebp-4h]

  v3 = *(void **)(this + 480);
  v4 = (uint32_t *)(this + 480);
  v17 = (const void **)(this + 480);
  if ( v3 != nullptr )
    j_j__free(v3);
  v5 = *(void **)(this + 484);
  *v4 = 0;
  if ( v5 != nullptr )
    j_j__free(v5);
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  v6 = *(uint32_t *)(this + 364);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 368) - v6) >> 5;
  else
    v7 = 0;
  v8 = 14 * v7;
  v18 = 14 * v7;
  v9 = 10 * (sub_424FF0(this) + 3);
  v10 = v8 * v9;
  v15 = v9;
  v14 = v8 * v9;
  *v17 = operator new(v8 * v9);
  *(uint32_t *)(this + 484) = operator new(v10);
  v11 = 0;
  if ( v18 > 0 )
  {
    do
    {
      v12 = 0;
      if ( v15 > 0 )
      {
        v16 = 0;
        do
        {
          *((uint8_t *)*v17 + v11 + v16) = sub_48CC70((uint32_t *)this, v11, v12++);
          v16 += v18;
        }
        while ( v12 < v15 );
      }
      ++v11;
    }
    while ( v11 < v18 );
    v10 = v14;
  }
  qmemcpy(*(void **)(this + 484), *v17, v10);
  sub_48E480(this, a2);
  return sub_58A9D0(v17, v18, v15);
}



// ------------------------------------------------------------
// 0x48E9C0 sub_48E9C0
// ------------------------------------------------------------
void /*cdecl*/ sub_48E9C0(int a1, int a2, int a3)
{
  int v3; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v3 = a1;
  v4[5] = v4;
  v4[4] = a1;
  v5 = 0;
  while ( a2 != 0 )
  {
    v4[3] = v3;
    LOBYTE(v5) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *(uint32_t *)a3;
      *(uint32_t *)(v3 + 4) = *(uint32_t *)(a3 + 4);
      *(uint32_t *)(v3 + 8) = *(uint32_t *)(a3 + 8);
      *(uint8_t *)(v3 + 12) = *(uint8_t *)(a3 + 12);
      sub_48E1A0((char **)(v3 + 16), a3 + 16);
    }
    v3 += 32;
    LOBYTE(v5) = 0;
    --a2;
  }
}



// ------------------------------------------------------------
// 0x48EAA0 sub_48EAA0
// ------------------------------------------------------------
int /*thiscall*/ sub_48EAA0(int this)
{
  void *v2; // eax

  sub_42EB90(this + 360);
  sub_42EB90(this + 376);
  if ( *(uint32_t *)(this + 480) != 0 )
    j_j__free(*(void **)(this + 480));
  v2 = *(void **)(this + 484);
  *(uint32_t *)(this + 480) = 0;
  if ( v2 != nullptr )
    j_j__free(v2);
  *(uint32_t *)(this + 484) = 0;
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  return sub_42E620(this + 504);
}



// ------------------------------------------------------------
// 0x48EB20 sub_48EB20
// ------------------------------------------------------------
int /*stdcall*/ sub_48EB20(int a1, int a2, int a3)
{
  sub_48E9C0(a1, a2, a3);
  return a1 + 32 * a2;
}



// ------------------------------------------------------------
// 0x48EB50 sub_48EB50
// ------------------------------------------------------------
void /*thiscall*/ sub_48EB50(int this, int a2, unsigned int a3, int a4)
{
  int v4; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  unsigned int v9; // eax
  int v11; // edx
  unsigned int v12; // eax
  int v13; // edx
  int v14; // eax
  char *v15; // ebx
  int v16; // ecx
  int v17; // eax
  unsigned int v18; // edi
  char *v19; // eax
  int v20; // edi
  char *v21; // edi
  int v22; // eax
  void *v23; // esi
  int v24; // [esp-18h] [ebp-5Ch]
  void *v25; // [esp-18h] [ebp-5Ch]
  int v26; // [esp-Ch] [ebp-50h]
  unsigned int v27; // [esp-8h] [ebp-4Ch]
  int v28; // [esp+0h] [ebp-44h] BYREF
  uint32_t v29[3]; // [esp+Ch] [ebp-38h] BYREF
  char v30; // [esp+18h] [ebp-2Ch]
  int v31; // [esp+1Ch] [ebp-28h] BYREF
  void *v32; // [esp+20h] [ebp-24h]
  int v33; // [esp+24h] [ebp-20h]
  void *Block; // [esp+2Ch] [ebp-18h]
  int v35; // [esp+30h] [ebp-14h]
  int *v36; // [esp+34h] [ebp-10h]
  int v37; // [esp+40h] [ebp-4h]
  int v38; // [esp+50h] [ebp+Ch]
  int v39; // [esp+54h] [ebp+10h]

  v4 = *(uint32_t *)(a4 + 4);
  v29[0] = *(uint32_t *)a4;
  v6 = *(uint32_t *)(a4 + 8);
  v29[1] = v4;
  LOBYTE(v4) = *(uint8_t *)(a4 + 12);
  v36 = &v28;
  v29[2] = v6;
  v35 = this;
  v30 = v4;
  sub_48E1A0((int)&v31, a4 + 16);
  v7 = *(uint32_t *)(this + 4);
  v8 = 0;
  v37 = 0;
  if ( v7 != 0 )
    v9 = (*(uint32_t *)(this + 12) - v7) >> 5;
  else
    v9 = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v7) >> 5;
    if ( 0x7FFFFFF - v8 < a3 )
      sub_42CB90(this);
    if ( v7 != 0 )
      v11 = (*(uint32_t *)(this + 8) - v7) >> 5;
    else
      v11 = 0;
    if ( v9 >= a3 + v11 )
    {
      v19 = *(char **)(this + 8);
      Block = v19;
      if ( (int)&v19[-a2] >> 5 >= a3 )
      {
        v21 = &v19[-32 * a3];
        v22 = sub_48E790(v21, v19, v19);
        v25 = Block;
        *(uint32_t *)(this + 8) = v22;
        sub_48E460(a2, v21, v25);
        sub_48E410(a2, a2 + 32 * a3, v29);
      }
      else
      {
        sub_48E790(a2, v19, a2 + 32 * a3);
        v27 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 5);
        v26 = *(uint32_t *)(this + 8);
        LOBYTE(v37) = 3;
        sub_48EB20(v26, v27, v29);
        v20 = 32 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v20;
        v37 = 0;
        sub_48E410(a2, v20 - 32 * a3, v29);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (v9 >> 1) >= v9 )
        v12 = (v9 >> 1) + v9;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v7) >> 5;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
      {
        if ( v7 != 0 )
          v14 = (*(uint32_t *)(this + 8) - v7) >> 5;
        else
          v14 = 0;
        v12 = a3 + v14;
      }
      v39 = 32 * v12;
      v15 = (char *)operator new(32 * v12);
      v24 = *(uint32_t *)(this + 4);
      Block = v15;
      LOBYTE(v37) = 1;
      v38 = sub_48E790(v24, a2, v15);
      sub_48E9C0(v38, a3, v29);
      sub_48E790(a2, *(uint32_t *)(this + 8), 32 * a3 + v38);
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 5;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
      {
        sub_42E7C0(v16, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v15[v39];
      *(uint32_t *)(this + 8) = &v15[32 * v18];
      *(uint32_t *)(this + 4) = v15;
    }
  }
  v23 = v32;
  if ( v32 != nullptr )
  {
    sub_42CC00(v32, v33);
    j__free(v23);
  }
}


// ------------------------------------------------------------
// 0x48EE10 sub_48EE10
// ------------------------------------------------------------
void /*thiscall*/ sub_48EE10(
        int *this,
        unsigned int a2,
        char a3,
        int a4,
        int a5,
        int a6,
        char a7,
        void *Block,
        int a9,
        int a10)
{
  int v10; // esi
  unsigned int v11; // edx
  int v12; // edx
  void *v13; // esi

  v10 = *(this + 1);
  if ( v10 != 0 )
    v11 = (*(this + 2) - v10) >> 5;
  else
    v11 = 0;
  if ( v11 >= a2 )
  {
    if ( v10 != 0 && a2 < (*(this + 2) - v10) >> 5 )
      sub_48E730(this, (int *)&a2, v10 + 32 * a2, *(this + 2));
  }
  else
  {
    if ( v10 != 0 )
      v12 = (*(this + 2) - v10) >> 5;
    else
      v12 = 0;
    sub_48EB50(this, *(this + 2), a2 - v12, (int)&a3);
  }
  v13 = Block;
  if ( Block != nullptr )
  {
    sub_42CC00(Block, a9);
    j__free(v13);
  }
}



// ------------------------------------------------------------
// 0x48EED0 sub_48EED0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_48EED0(uint32_t *this, const char *ArgList, char a3)
{
  uint32_t *v4; // eax
  uint32_t *v5; // ebx
  unsigned int result; // eax
  uint32_t *v7; // ecx
  uint32_t *v8; // eax
  int i; // edx
  const char *v10; // edi
  int v11; // edi
  float *v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // edi
  unsigned int v16; // edx
  uint32_t *v17; // eax
  uint32_t *v18; // ecx
  int j; // edx
  uint32_t *v20; // eax
  bool v21; // zf
  int v22; // ecx
  unsigned int **v23; // ecx
  int v24; // edi
  const char *v25; // eax
  int v26; // edx
  unsigned int **v27; // ecx
  int v28; // edi
  const char *v29; // eax
  uint32_t *v30; // ecx
  int v31; // edx
  int v32; // edx
  int v33; // [esp-14h] [ebp-38h]
  int v34; // [esp-14h] [ebp-38h]
  char v35; // [esp-10h] [ebp-34h]
  char v36; // [esp-10h] [ebp-34h]
  int v37; // [esp+Ch] [ebp-18h] BYREF
  int v38; // [esp+10h] [ebp-14h]
  int v39; // [esp+14h] [ebp-10h]
  int v40; // [esp+20h] [ebp-4h]
  const char *ArgLista; // [esp+2Ch] [ebp+8h]
  int ArgListb; // [esp+2Ch] [ebp+8h]
  char *ArgListc; // [esp+2Ch] [ebp+8h]
  unsigned int ArgListd; // [esp+2Ch] [ebp+8h]
  const char *ArgListe; // [esp+2Ch] [ebp+8h]
  unsigned int ArgListf; // [esp+2Ch] [ebp+8h]
  const char *ArgListg; // [esp+2Ch] [ebp+8h]
  int v48; // [esp+30h] [ebp+Ch]
  int v49; // [esp+30h] [ebp+Ch]

  v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84DC + 4))(dword_8F84DC, ArgList);
  v5 = v4;
  if ( v4 == nullptr )
    return off_77F3FC("MAP CREATE FAIL! FILENAME[%s]", ArgList);
  *this = *v4;
  *(this + 1) = v4[30];
  v7 = this + 2;
  v8 = v4 + 39;
  for ( i = 3; i != 0; --i )
    *v7++ = *v8++;
  v10 = (const char *)v5[43];
  ArgLista = v10;
  if ( v10 != (const char *)v5[44] )
  {
    while ( 1 )
    {
      v39 = sub_42FCB0(228);
      v40 = 0;
      if ( v39 != 0 )
      {
        if ( *((uint32_t *)v10 + 6) < 0x10u )
          LOBYTE(v10) = (uint8_t)v10 + 4;
        else
          v10 = *((const char **)v10 + 1);
        if ( v5[76] < 0x10u )
          v11 = sub_431920((uint8_t)v5 + 28, (char)v10, 1);
        else
          v11 = sub_431920(v5[71], (char)v10, 1);
      }
      else
      {
        v11 = 0;
      }
      v40 = -1;
      v37 = v11;
      sub_699070(2);
      v12 = (float *)sub_4924C0(0);
      v38 = (uint64_t)((double)*(unsigned int *)(*(uint32_t *)v12 + 36) * v12[5]);
      if ( v38 > 0 )
      {
        v13 = 16 * ((ArgLista[32] != 0) + 2 * *((uint32_t *)ArgLista + 7));
        v14 = *(uint32_t *)((char *)this + v13 + 24);
        v15 = (int)this + v13 + 20;
        if ( v14 != 0 )
          v16 = (*(uint32_t *)((char *)this + v13 + 28) - v14) >> 3;
        else
          v16 = 0;
        if ( v14 != 0 && v16 < (*(uint32_t *)((char *)this + v13 + 32) - v14) >> 3 )
        {
          v39 = *(uint32_t *)((char *)this + v13 + 28);
          sub_63A7C0(v39, 1, &v37);
          *(uint32_t *)(v15 + 8) = v39 + 8;
        }
        else
        {
          sub_48CF90((int)this + v13 + 20, *(uint32_t **)((char *)this + v13 + 28), 1u, (int)&v37);
        }
      }
      ArgLista += 36;
      if ( ArgLista == (const char *)v5[44] )
        break;
      v10 = ArgLista;
    }
  }
  sub_48D290((int)(this + 53), (int)(v5 + 46));
  sub_48D410((int)(this + 57), (int)(v5 + 50));
  v17 = v5 + 54;
  v18 = this + 61;
  for ( ArgListb = 4; ArgListb != 0; --ArgListb )
  {
    for ( j = 2; j != 0; --j )
      *v18++ = *v17++;
  }
  *(this + 69) = v5[62];
  *(this + 70) = v5[63];
  *(this + 71) = v5[64];
  *(this + 72) = v5[65];
  sub_41DC80((int)(this + 73), (int)(v5 + 66));
  ArgListc = (char *)(this + 77);
  v20 = v5 + 86;
  v39 = 3;
  do
  {
    *(uint32_t *)ArgListc = *v20;
    *((uint32_t *)ArgListc + 1) = v20[1];
    *((uint32_t *)ArgListc + 2) = v20[2];
    *((uint32_t *)ArgListc + 3) = v20[3];
    v20 += 4;
    v21 = v39 == 1;
    ArgListc += 16;
    --v39;
  }
  while ( !v21 );
  *(this + 89) = v5[98];
  *((uint8_t *)this + 396) = a3;
  v22 = v5[32];
  if ( v22 != 0 )
    ArgListd = (v5[33] - v22) >> 2;
  else
    ArgListd = 0;
  LOBYTE(v33) = 0;
  sub_48EE10(this + 90, ArgListd, -1, 0, 0, v33, v35, nullptr, 0, 0);
  v23 = (unsigned int **)v5[32];
  v48 = (int)v23;
  if ( v23 != (unsigned int **)v5[33] )
  {
    ArgListe = nullptr;
    while ( 1 )
    {
      v39 = v5[76] < 0x10u ? (int)(v5 + 71) : v5[71];
      v24 = (int)&ArgListe[*(this + 91)];
      v25 = sub_41ACF0(v23);
      sub_48E2E0(v24, v39, v25);
      v21 = v48 + 4 == v5[33];
      v48 += 4;
      ArgListe += 32;
      if ( v21 )
        break;
      v23 = (unsigned int **)v48;
    }
  }
  v26 = v5[36];
  if ( v26 != 0 )
    ArgListf = (v5[37] - v26) >> 2;
  else
    ArgListf = 0;
  LOBYTE(v34) = 0;
  sub_48EE10(this + 94, ArgListf, -1, 0, 0, v34, v36, nullptr, 0, 0);
  v27 = (unsigned int **)v5[36];
  v49 = (int)v27;
  if ( v27 != (unsigned int **)v5[37] )
  {
    ArgListg = nullptr;
    while ( 1 )
    {
      v39 = v5[76] < 0x10u ? (int)(v5 + 71) : v5[71];
      v28 = (int)&ArgListg[*(this + 95)];
      v29 = sub_41ACF0(v27);
      sub_48E2E0(v28, v39, v29);
      v21 = v49 + 4 == v5[37];
      v49 += 4;
      ArgListg += 32;
      if ( v21 )
        break;
      v27 = (unsigned int **)v49;
    }
  }
  result = 0;
  *(this + 116) = 0;
  *(this + 117) = 0;
  do
  {
    if ( result < 2 )
    {
      v30 = this + 4 * result;
      v30[102] = 120;
      v30[103] = 106;
      if ( result != 0 )
        *(this + 4 * result + 100) = *(this + 2 * result + 61) - 120;
      else
        *(this + 100) = *(this + 61);
      v32 = *(this + 2 * result + 62) - 53;
    }
    else
    {
      v30 = this + 4 * result;
      *(this + 4 * result + 100) = *(this + 2 * result + 61) - 70;
      v31 = *(this + 2 * result + 62);
      v30[102] = 140;
      v30[103] = 40;
      v32 = v31 - 20;
    }
    ++result;
    v30[101] = v32;
  }
  while ( (int)result < 4 );
  *(this + 119) = v5;
  return result;
}


// ------------------------------------------------------------
// 0x48F470 sub_48F470
// ------------------------------------------------------------
const char */*thiscall*/ sub_48F470(uint32_t *this, int a2, char a3)
{
  const char *result; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_442D00(&v5, &a2);
  result = (const char *)v5;
  if ( v5 != dword_9B740C )
  {
    if ( *(uint32_t *)(v5 + 40) < 0x10u )
      result = (const char *)(v5 + 20);
    else
      result = *(const char **)(v5 + 20);
    if ( result != nullptr )
      return (const char *)sub_48EED0(this, result, a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F4C0 sub_48F4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_48F4C0(uint32_t *this)
{
  int result; // eax

  result = *(this + 2) != 254;
  if ( *(this + 3) != 254 )
    ++result;
  if ( *(this + 4) != 254 )
    ++result;
  if ( *(this + 5) != 254 )
    ++result;
  if ( *(this + 6) != 254 )
    ++result;
  if ( *(this + 7) != 254 )
    ++result;
  if ( *(this + 8) != 254 )
    ++result;
  if ( *(this + 9) != 254 )
    ++result;
  return result;
}



// ------------------------------------------------------------
// 0x48F500 sub_48F500
// ------------------------------------------------------------
int /*cdecl*/ sub_48F500(int a1, int a2)
{
  int v2; // ecx
  int result; // eax
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = v2;
  result = dword_99FEC0;
  if ( dword_99FEC0 != 0
    && *(uint32_t *)(dword_99FEC0 + 4 * a1 + 8) != a2
    && (*(uint32_t *)(dword_99FEC0 + 4 * a1 + 40) == (uint16_t)word_77F804
     || *(uint32_t *)(dword_99FEC0 + 4 * *(uint32_t *)(dword_99FEC0 + 108) + 40) == (uint16_t)word_77F804) )
  {
    sub_423200(dword_8F7B08, 55);
    LOBYTE(v4) = a1;
    sub_423290(&v4, 1);
    LOBYTE(v4) = a2;
    sub_423290(&v4, 1);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F580 sub_48F580
// ------------------------------------------------------------
int /*cdecl*/ sub_48F580(int a1, char a2)
{
  uint32_t *v2; // edx

  v2 = dword_8F8528;
  *((uint8_t *)&dword_99FEB8 + a1) = a2;
  return sub_52AF20(v2[8]);
}



// ------------------------------------------------------------
// 0x48F5A0 sub_48F5A0
// ------------------------------------------------------------
int sub_48F5A0()
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != (uint16_t)word_77F804; ++i )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F5E0 sub_48F5E0
// ------------------------------------------------------------
int /*cdecl*/ sub_48F5E0(int a1)
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FEC0 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FEC0 + 40); *i != a1; ++i )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F620 sub_48F620
// ------------------------------------------------------------
bool /*thiscall*/ sub_48F620(uint32_t *this)
{
  int v1; // eax
  uint32_t *i; // esi
  int v4; // eax

  v1 = 0;
  for ( i = this + 2; *i == 255 || *i == 254; ++i )
  {
    if ( ++v1 >= 8 )
      return false;
  }
  v4 = *(this + v1 + 2);
  return v4 != 0 && v4 != 4;
}



// ------------------------------------------------------------
// 0x48F660 sub_48F660
// ------------------------------------------------------------
int /*thiscall*/ sub_48F660(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + a2 + 9);
  if ( v2 == 0xFFFF )
    return 0;
  else
    return sub_429830(v2);
}



// ------------------------------------------------------------
// 0x48F690 sub_48F690
// ------------------------------------------------------------
int /*thiscall*/ sub_48F690(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + a2 + 10);
  if ( v2 == 0xFFFF )
    return 0;
  else
    return sub_429830(v2);
}



// ------------------------------------------------------------
// 0x48F6C0 sub_48F6C0
// ------------------------------------------------------------
int /*thiscall*/ sub_48F6C0(uint32_t *this)
{
  int v1; // ebx
  uint32_t *v2; // esi
  int i; // edi

  v1 = 0;
  v2 = this + 10;
  for ( i = 8; i != 0; --i )
  {
    if ( *(v2 - 8) != 254 && (*v2 == 0xFFFF || sub_429830(*v2) == 0) )
      ++v1;
    ++v2;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x48F700 sub_48F700
// ------------------------------------------------------------
int /*thiscall*/ sub_48F700(uint32_t *this, int ArgList, int a3, int a4)
{
  int result; // eax
  int v5; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // esi
  int v15; // eax
  int v16; // ecx
  int ArgLista; // [esp+14h] [ebp+8h]
  char v18; // [esp+1Ch] [ebp+10h]

  result = a3;
  v5 = a4;
  v8 = *(this + ArgList + 10);
  if ( v8 != a3 || *(this + ArgList + 2) != a4 )
  {
    v9 = *(this + ArgList + 2);
    *(this + ArgList + 10) = a3;
    ArgLista = v9;
    *(this + ArgList + 2) = a4;
    if ( (uint32_t *)dword_99FEC0 == this )
    {
      if ( v8 != a3 )
      {
        if ( a3 == 0xFFFF )
        {
          v10 = sub_429830(v8);
          v11 = v10;
          if ( v10 != 0 && *(uint32_t *)(v10 + 196) != 0 )
            sub_4B05C0(0);
          sub_452630(*(uint32_t *)(dword_8F7A24 + 32), ArgList, v11);
        }
        else
        {
          v12 = sub_429830(a3);
          sub_4529B0(ArgList, v12, 1);
          v13 = *(uint32_t *)(v12 + 196);
          if ( v13 != 0 )
            sub_4B05B0(v13);
          sub_432EA0("LADDER_DOWN", -1, 0, 0);
        }
        v5 = a4;
      }
      if ( ArgLista != v5 )
      {
        sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
        sub_52A950(*((uint32_t *)dword_8F8528 + 8));
      }
      v14 = *(this + ArgList + 10);
      if ( v14 != 0xFFFF )
      {
        v15 = sub_429830(v14);
        if ( v15 != 0 )
        {
          v16 = *(uint32_t *)(v15 + 196);
          if ( v16 != 0 )
          {
            v18 = 0;
            switch ( v5 )
            {
              case 0:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 372))(v16, ArgList + 3);
                break;
              case 1:
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v16 + 372))(v16, 0);
                break;
              case 2:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 372))(v16, 1);
                break;
              case 3:
              case 4:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 372))(v16, 2);
                v18 = 1;
                break;
              default:
                break;
            }
            sub_4B12B0(v18);
          }
        }
      }
      return sub_52ADA0(*((uint32_t *)dword_8F8528 + 8));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48F890 sub_48F890
// ------------------------------------------------------------
int /*cdecl*/ sub_48F890(int a1)
{
  int result; // eax
  int v2; // esi
  uint32_t *v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // esi
  int v12; // ecx
  char v13; // [esp+Ch] [ebp+8h]

  result = dword_99FEC0;
  if ( dword_99FEC0 != a1 )
  {
    dword_99FEC0 = a1;
    if ( a1 != 0 )
    {
      v2 = *(uint32_t *)(a1 + 108);
      if ( v2 != -1 )
      {
        v3 = dword_8F8528;
        *((uint8_t *)&dword_99FEB8 + v2) = 0;
        sub_52AF20(v3[8]);
        *(uint32_t *)(sub_656710() + 40) = v2;
        off_77F3FC("@@SET HOST %d", v2);
      }
      sub_41D300((int *)dword_8F7A24, 4);
      v4 = sub_48F5A0();
      off_77F3FC("@@UDP START - CNPvpRoom::setMyRoom() seatIndex %d /// 1", v4);
      v5 = dword_8F8520;
      v6 = *(uint32_t *)dword_8F8520;
      v7 = sub_48F5A0();
      (*(void (/*thiscall*/ **)(int, int))(v6 + 148))(v5, v7);
      v8 = 0;
      v9 = (uint32_t *)(a1 + 8);
      do
      {
        if ( v9[8] != 0xFFFF )
        {
          v10 = sub_429830(v9[8]);
          v11 = v10;
          if ( v10 != 0 && *(uint32_t *)(v10 + 196) != 0 )
          {
            sub_4529B0(v8, v10, 0);
            sub_4B05B0(*(uint32_t *)(v11 + 196));
            v12 = *(uint32_t *)(v11 + 196);
            if ( v12 != 0 )
            {
              v13 = 0;
              switch ( *v9 )
              {
                case 0:
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 372))(v12, v8 + 3);
                  break;
                case 1:
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v12 + 372))(v12, 0);
                  break;
                case 2:
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 372))(v12, 1);
                  break;
                case 3:
                case 4:
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 372))(v12, 2);
                  v13 = 1;
                  break;
                default:
                  break;
              }
              sub_4B12B0(v13);
            }
          }
        }
        ++v8;
        ++v9;
      }
      while ( v8 < 8 );
      return sub_52ADA0(*((uint32_t *)dword_8F8528 + 8));
    }
    else
    {
      dword_99FEB8 = 0;
      dword_99FEBC = 0;
      off_77F3FC("@@UDP STOP - CNPvpRoom::setMyRoom 1");
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FA30 sub_48FA30
// ------------------------------------------------------------
char /*thiscall*/ sub_48FA30(uint32_t *this, int ArgList)
{
  int v2; // eax
  int v4; // edx
  char result; // al
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  const char *v13; // eax
  uint32_t *v14; // eax
  int v15; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int v17; // [esp+208h] [ebp-4h]

  v2 = dword_796E50;
  v4 = *(this + 27);
  *(this + 27) = ArgList;
  v17 = v2;
  result = v4 != ArgList;
  if ( (uint32_t *)dword_99FEC0 == this )
  {
    if ( v4 != ArgList )
    {
      v6 = 0xFFFF;
      if ( ArgList != -1 )
        v6 = *(this + ArgList + 10);
      if ( *(uint32_t *)(sub_429830(v6) + 196) != 0 )
      {
        v7 = *(this + 27);
        if ( v7 == -1 )
          v8 = 0xFFFF;
        else
          v8 = *(this + v7 + 10);
        v9 = *(uint32_t *)(sub_429830(v8) + 196);
        v10 = *(uint32_t *)(v9 + 312);
        v11 = v9 + 288;
        if ( v10 < 0x10 )
          v12 = v11 + 4;
        else
          v12 = *(uint32_t *)(v11 + 4);
        v15 = v12;
        v13 = (const char *)sub_422E70(1607);
        sprintf(Buffer, v13, v15);
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
      }
    }
    v14 = dword_8F8528;
    *((uint8_t *)&dword_99FEB8 + ArgList) = 0;
    sub_52AF20(v14[8]);
    sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
    sub_52A950(*((uint32_t *)dword_8F8528 + 8));
    *(uint32_t *)(sub_656710() + 40) = ArgList;
    return off_77F3FC("@@SET HOST %d", ArgList);
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FB60 sub_48FB60
// ------------------------------------------------------------
int /*thiscall*/ sub_48FB60(uint32_t *this, int a2, int *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int result; // eax

  v3 = 0;
  v4 = this + 1;
  while ( 1 )
  {
    result = sub_48F660(v4, v3);
    if ( result != 0 && *(uint16_t *)(result + 4) == a2 )
      break;
    if ( ++v3 >= 8 )
      return 0;
  }
  if ( a3 != nullptr )
    *a3 = v3;
  return result;
}



// ------------------------------------------------------------
// 0x48FBB0 sub_48FBB0
// ------------------------------------------------------------
int /*thiscall*/ sub_48FBB0(uint32_t *this)
{
  int result; // eax

  result = *(this + 10) != 0xFFFF;
  if ( *(this + 11) != 0xFFFF )
    ++result;
  if ( *(this + 12) != 0xFFFF )
    ++result;
  if ( *(this + 13) != 0xFFFF )
    ++result;
  if ( *(this + 14) != 0xFFFF )
    ++result;
  if ( *(this + 15) != 0xFFFF )
    ++result;
  if ( *(this + 16) != 0xFFFF )
    ++result;
  if ( *(this + 17) != 0xFFFF )
    ++result;
  return result;
}



// ------------------------------------------------------------
// 0x48FBF0 sub_48FBF0
// ------------------------------------------------------------
int /*thiscall*/ sub_48FBF0(uint32_t *this)
{
  int result; // eax

  result = *(this + 2) == 255;
  if ( *(this + 3) == 255 )
    ++result;
  if ( *(this + 4) == 255 )
    ++result;
  if ( *(this + 5) == 255 )
    ++result;
  if ( *(this + 6) == 255 )
    ++result;
  if ( *(this + 7) == 255 )
    ++result;
  if ( *(this + 8) == 255 )
    ++result;
  if ( *(this + 9) == 255 )
    ++result;
  return result;
}



// ------------------------------------------------------------
// 0x48FC30 sub_48FC30
// ------------------------------------------------------------
int /*cdecl*/ sub_48FC30(int a1, int a2)
{
  int v2; // ecx
  int result; // eax
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = v2;
  result = dword_99FF08;
  if ( dword_99FF08 != 0 && *(uint32_t *)(dword_99FF08 + 4 * a1 + 8) != a2 )
  {
    sub_423200(dword_8F7B08, 94);
    LOBYTE(v4) = a1;
    sub_423290(&v4, 1);
    LOBYTE(v4) = a2;
    sub_423290(&v4, 1);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FCA0 sub_48FCA0
// ------------------------------------------------------------
int sub_48FCA0()
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FF08 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FF08 + 40); *i != (uint16_t)word_77F804; ++i )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FCE0 sub_48FCE0
// ------------------------------------------------------------
int /*cdecl*/ sub_48FCE0(int a1)
{
  int result; // eax
  uint32_t *i; // ecx

  if ( dword_99FF08 == 0 )
    return -1;
  result = 0;
  for ( i = (uint32_t *)(dword_99FF08 + 40); *i != a1; ++i )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x48FD20 sub_48FD20
// ------------------------------------------------------------
bool /*thiscall*/ sub_48FD20(uint32_t *this)
{
  int v1; // eax
  uint32_t *i; // edx

  v1 = 0;
  for ( i = this + 2; *i == 255; ++i )
  {
    if ( ++v1 >= 8 )
      return false;
  }
  return *(this + v1 + 2) != 0;
}



// ------------------------------------------------------------
// 0x48FD50 sub_48FD50
// ------------------------------------------------------------
bool /*thiscall*/ sub_48FD50(uint32_t *this)
{
  return *(this + 18) != -1;
}



// ------------------------------------------------------------
// 0x48FD60 sub_48FD60
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD60(uint32_t *this, int a2)
{
  return *(this + a2 + 20);
}



// ------------------------------------------------------------
// 0x48FD70 sub_48FD70
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD70(uint32_t *this, int a2)
{
  return *(this + a2 + 28);
}



// ------------------------------------------------------------
// 0x48FD80 sub_48FD80
// ------------------------------------------------------------
int /*thiscall*/ sub_48FD80(uint8_t *this)
{
  int result; // eax

  result = *(this + 144) == 0;
  if ( *(this + 145) == 0 )
    ++result;
  if ( *(this + 146) == 0 )
    ++result;
  if ( *(this + 147) == 0 )
    ++result;
  if ( *(this + 148) == 0 )
    ++result;
  if ( *(this + 149) == 0 )
    ++result;
  if ( *(this + 150) == 0 )
    ++result;
  if ( *(this + 151) == 0 )
    ++result;
  return result;
}



// ------------------------------------------------------------
// 0x48FDE0 sub_48FDE0
// ------------------------------------------------------------
int /*thiscall*/ sub_48FDE0(uint32_t *this)
{
  uint32_t *v1; // ecx

  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
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
  v1 = this + 36;
  *v1 = 0;
  v1[1] = 0;
  return sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
}



// ------------------------------------------------------------
// 0x48FE30 sub_48FE30
// ------------------------------------------------------------
char */*thiscall*/ sub_48FE30(int this)
{
  const char *v2; // edi
  const char *v3; // eax

  v2 = (const char *)sub_422E70(1900);
  v3 = (const char *)sub_42C540(*(char *)(this + 152));
  sprintf(byte_99FF10, "%s %s #%d", v2, v3, *(uint32_t *)(this + 4));
  return byte_99FF10;
}



// ------------------------------------------------------------
// 0x48FE80 sub_48FE80
// ------------------------------------------------------------
int /*usercall*/ sub_48FE80@<eax>(int a1@<edi>, int a2)
{
  int result; // eax
  int v3; // esi
  uint32_t *v4; // eax
  int v5; // eax
  uint32_t *v6; // ecx
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // edi
  uint32_t *v10; // ebx
  int v11; // eax
  int v12; // esi
  int v13; // ecx
  char v14; // [esp+10h] [ebp+8h]

  result = dword_99FF08;
  if ( dword_99FF08 != a2 )
  {
    dword_99FF08 = a2;
    if ( a2 != 0 )
    {
      v3 = 0;
      v4 = (uint32_t *)(a2 + 40);
      while ( *v4 == 0xFFFF )
      {
        ++v3;
        ++v4;
        if ( v3 >= 8 )
        {
          MessageBoxA(*(HWND *)(dword_79C0A0 + 16), &byte_6CAE90, szPassword, 0);
          goto LABEL_8;
        }
      }
      *(uint32_t *)(sub_656710(a1) + 40) = v3;
      off_77F3FC("@@SET HOST %d", v3);
LABEL_8:
      off_77F3FC((char *)&byte_6CAE5C, *(uint32_t *)(a2 + 72), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32));
      sub_41D300(6);
      sub_42F160(*(uint32_t *)(a2 + 72), 0);
      off_77F3FC((char *)&byte_6CAE28, *(uint32_t *)(a2 + 72), *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32));
      if ( dword_99FF08 != 0 )
      {
        v5 = 0;
        v6 = (uint32_t *)(dword_99FF08 + 40);
        while ( *v6 != (uint16_t)word_77F804 )
        {
          ++v5;
          ++v6;
          if ( v5 >= 8 )
            goto LABEL_12;
        }
      }
      else
      {
LABEL_12:
        v5 = -1;
      }
      off_77F3FC("@@UDP START - CNWarRoom::setMyRoom() seatIndex %d /// 1", v5);
      if ( dword_99FF08 != 0 )
      {
        v7 = 0;
        v8 = (uint32_t *)(dword_99FF08 + 40);
        while ( *v8 != (uint16_t)word_77F804 )
        {
          ++v7;
          ++v8;
          if ( v7 >= 8 )
            goto LABEL_17;
        }
      }
      else
      {
LABEL_17:
        v7 = -1;
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 148))(dword_8F8520, v7);
      v9 = 0;
      v10 = (uint32_t *)(a2 + 8);
      do
      {
        v11 = sub_48F660(v9);
        v12 = v11;
        if ( v11 != 0 && *(uint32_t *)(v11 + 196) != 0 )
        {
          sub_42E120(v9, v11, 0);
          sub_4B05B0(*(uint32_t *)(v12 + 196));
          v13 = *(uint32_t *)(v12 + 196);
          if ( v13 != 0 )
          {
            v14 = 0;
            switch ( *v10 )
            {
              case 0:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 372))(v13, v9 + 3);
                break;
              case 1:
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 372))(v13, 0);
                break;
              case 2:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 372))(v13, 1);
                break;
              case 3:
              case 4:
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 372))(v13, 2);
                v14 = 1;
                break;
              default:
                break;
            }
            sub_4B12B0(v14);
          }
        }
        ++v9;
        ++v10;
      }
      while ( v9 < 8 );
      return sub_49CA80(*((uint32_t *)dword_8F8528 + 9));
    }
    else
    {
      off_77F3FC("@@UDP STOP - CNWarRoom::setMyRoom 1");
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
      return sub_42EA90(*(uint32_t *)(dword_8F7A24 + 40));
    }
  }
  return result;
}

