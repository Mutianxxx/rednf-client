// ============================================================
// 【40JP逆向源代码工程】game/broadcast_debug.cpp
// 模块: 播报层/调试输出/Socket 封装
// 来源: work/dump_combat.txt  区块: 0x420000-0x440000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 644
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x420070 sub_420070
// ------------------------------------------------------------
int /*thiscall*/ sub_420070(uint8_t *this)
{
  void *v2; // esi

  if ( dword_79C0A0 != 0 )
  {
    *(uint32_t *)(dword_79C0A0 + 124) = 0;
    *(uint32_t *)(dword_79C0A0 + 128) = 0;
  }
  sub_41C240(this);
  dword_8F7A24 = 0;
  sub_438910();
  if ( dword_99FCC8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FCC8)(dword_99FCC8, 1);
  dword_99FCC8 = 0;
  if ( dword_8F7B08 != 0 )
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_8F7B08)(dword_8F7B08, 1);
    dword_8F7B08 = 0;
  }
  if ( dword_99FD5C != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD5C)(dword_99FD5C, 1);
  dword_99FD5C = 0;
  if ( dword_99FD60 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD60)(dword_99FD60, 1);
  dword_99FD60 = 0;
  if ( dword_99FD64 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD64)(dword_99FD64, 1);
  dword_99FD64 = 0;
  if ( dword_99FD6C != nullptr )
  {
    v2 = dword_99FD6C;
    sub_41FF40();
    j__free(v2);
  }
  dword_99FD6C = nullptr;
  if ( dword_99FD68 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD68)(dword_99FD68, 1);
  dword_99FD68 = 0;
  sub_41FD50();
  sub_403BE0();
  *(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x420160 sub_420160
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_420160(uint32_t *a1, int a2, int a3)
{
  sub_41FFE0(a1, a2, a3);
  return &a1[a2];
}



// ------------------------------------------------------------
// 0x420190 sub_420190
// ------------------------------------------------------------
int /*usercall*/ sub_420190@<eax>(int a1@<ebx>, int a2@<esi>)
{
  int v3; // esi
  const CHAR *v4; // eax
  int v5; // esi
  int v6; // esi
  int v7; // esi
  const CHAR *v8; // eax
  const CHAR *v9; // [esp-10h] [ebp-78h]
  const CHAR *v10; // [esp-10h] [ebp-78h]
  uint8_t v12[4]; // [esp+4h] [ebp-64h] BYREF
  void *Block; // [esp+8h] [ebp-60h]
  int v14; // [esp+18h] [ebp-50h]
  unsigned int v15; // [esp+1Ch] [ebp-4Ch]
  uint8_t v16[28]; // [esp+20h] [ebp-48h] BYREF
  uint8_t v17[28]; // [esp+3Ch] [ebp-2Ch] BYREF
  int v18; // [esp+58h] [ebp-10h]
  int v19; // [esp+64h] [ebp-4h]

  v18 = dword_796E50;
  if ( (uint8_t)sub_432F70() == 0 )
    return 0x80000000;
  v3 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 4))(dword_79C0A0, 3, &dword_79C0A4);
  _access("_ImagePacks", 0);
  if ( _access("!ImagePacks", 0) != 0 )
  {
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
    sub_4015C0("ImagePacks2/", 0xCu);
    v19 = 0;
    sub_407CB0(v12);
    v19 = -1;
    if ( v15 >= 0x10 )
      j__free(Block);
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
  }
  if ( v3 < 0 )
  {
    v9 = (const CHAR *)sub_422E70(589);
    v4 = (const CHAR *)sub_422E70(588);
LABEL_9:
    MessageBoxA(nullptr, v4, v9, 0);
    return v3;
  }
  sub_404330(640, 480);
  v3 = sub_407C40(640, 480, 16, *(uint8_t *)(dword_8F7A24 + 112));
  if ( v3 < 0 )
  {
    v9 = (const CHAR *)sub_422E70(591);
    v4 = (const CHAR *)sub_422E70(590);
    goto LABEL_9;
  }
  v5 = dword_79C0A4;
  sub_401710("ScreenShot");
  v19 = 1;
  sub_401710("ScreenShot");
  v6 = *(uint32_t *)(v5 + 8252);
  LOBYTE(v19) = 2;
  dword_9D3BE0 = sub_699760(v6, v16, v17, 1);
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A4 + 8))(dword_79C0A4, 7, &dword_79C0B0);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(593);
    v8 = (const CHAR *)sub_422E70(592);
LABEL_32:
    MessageBoxA(nullptr, v8, v10, 0);
    sub_501490(v17);
    sub_501490(v16);
    return v7;
  }
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 12))(dword_79C0A0, 2, &dword_79C0A8);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(595);
    v8 = (const CHAR *)sub_422E70(594);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0A8 + 8))(dword_79C0A8);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(597);
    v8 = (const CHAR *)sub_422E70(596);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, uint32_t, int *))(*(uint32_t *)dword_79C0A8 + 16))(dword_79C0A8, 0, &dword_79C0B4);
  if ( dword_79C0B4 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(599);
    v8 = (const CHAR *)sub_422E70(598);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B4 + 4))(dword_79C0B4, 0);
  if ( dword_79C0B4 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(601);
    v8 = (const CHAR *)sub_422E70(600);
    goto LABEL_32;
  }
  (*(void (/*thiscall*/ **)(int, int, int *, int, int))(*(uint32_t *)dword_79C0A8 + 16))(
    dword_79C0A8,
    1,
    &dword_79C0B8,
    a2,
    a1);
  if ( dword_79C0B8 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B8 + 4))(dword_79C0B8, 0);
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 16))(dword_79C0A0, 2, &dword_79C0AC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(603);
    v8 = (const CHAR *)sub_422E70(602);
    goto LABEL_32;
  }
  v7 = sub_407AE0(dword_79C0A4);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(605);
    v8 = (const CHAR *)sub_422E70(604);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0AC + 4))(dword_79C0AC, 3, &dword_99FCCC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(607);
    v8 = (const CHAR *)sub_422E70(606);
    goto LABEL_32;
  }
  v7 = sub_4163F0(dword_99FCCC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(609);
    v8 = (const CHAR *)sub_422E70(608);
    goto LABEL_32;
  }
  dword_9D3BD8 = dword_99FCCC;
  SetClassLongA(*(HWND *)(dword_79C0A0 + 16), -26, 3);
  sub_501490(v17);
  sub_501490(v16);
  return 1;
}


// ------------------------------------------------------------
// 0x420550 sub_420550
// ------------------------------------------------------------
void /*noreturn*/ sub_420550()
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
// 0x4205C0 sub_4205C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4205C0(void *this)
{
  int v2; // eax
  int v3; // eax
  HWND WindowA; // eax
  int i; // esi

  *(uint32_t *)this = &vftbl_nmodule__nMinimizeWindows;
  v2 = *((uint32_t *)this + 1);
  if ( v2 != 0 )
  {
    v3 = v2 - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        sub_41FCF0();
    }
    else
    {
      WindowA = FindWindowA("Shell_TrayWnd", nullptr);
      if ( WindowA != nullptr )
        SendMessageA(WindowA, 0x111u, 0x1A0u, 0);
    }
  }
  else
  {
    for ( i = *((uint32_t *)this + 3); i != *((uint32_t *)this + 4); i += 8 )
      ShowWindow(*(HWND *)i, *(uint32_t *)(i + 4));
    if ( *((uint32_t *)this + 3) != 0 )
      j__free(*((void **)this + 3));
    *((uint32_t *)this + 3) = 0;
    *((uint32_t *)this + 4) = 0;
    *((uint32_t *)this + 5) = 0;
  }
  if ( *((uint32_t *)this + 3) != 0 )
    j__free(*((void **)this + 3));
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4206A0 nmodule__nMinimizeWindows__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nmodule__nMinimizeWindows__vmt0(void *Block, char a2)
{
  sub_4205C0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4206D0 sub_4206D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4206D0(int this, unsigned int **a2, unsigned int a3, unsigned int **a4)
{
  int v5; // edx
  unsigned int v6; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v13; // edi
  void **v14; // ecx
  int v15; // eax
  unsigned int v16; // ebx
  char *v17; // eax
  int v18; // ecx
  int v19; // ebx
  unsigned int **v20; // ebx
  unsigned int **v21; // eax
  unsigned int **v22; // [esp-18h] [ebp-40h]
  unsigned int **v23; // [esp-18h] [ebp-40h]
  int v24; // [esp-Ch] [ebp-34h]
  unsigned int v25; // [esp-8h] [ebp-30h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  void *v29[2]; // [esp+14h] [ebp-14h] BYREF
  int v30; // [esp+24h] [ebp-4h]
  unsigned int **v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v29[1] = &v26;
  v28 = this;
  v29[0] = nullptr;
  sub_41B0D0((unsigned int **)v29, a4);
  v5 = *(uint32_t *)(this + 4);
  v30 = 0;
  if ( v5 != 0 )
    v6 = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_401830(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v17 = *(char **)(this + 8);
      v18 = 4 * a3;
      Block = v17;
      v33 = 4 * a3;
      if ( (v17 - (char *)a2) >> 2 >= a3 )
      {
        v20 = (unsigned int **)&v17[-v18];
        v21 = sub_41CB60((unsigned int **)&v17[-v18], (unsigned int **)v17, (unsigned int **)v17);
        v23 = (unsigned int **)Block;
        *(uint32_t *)(this + 8) = v21;
        sub_41FF20(a2, v20, v23);
        sub_41FE80(a2, &a2[v33 / 4u], (unsigned int **)v29);
      }
      else
      {
        sub_41CB60(a2, (unsigned int **)v17, &a2[v18 / 4u]);
        v25 = a3 - ((*(uint32_t *)(this + 8) - (int)a2) >> 2);
        v24 = *(uint32_t *)(this + 8);
        LOBYTE(v30) = 3;
        sub_420160(v24, v25, v29);
        v19 = v33 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v19;
        v30 = 0;
        sub_41FE80(a2, (unsigned int **)(v19 - v33), (unsigned int **)v29);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
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
      v32 = 4 * v10;
      v13 = (char *)operator new(4 * v10);
      v22 = *(unsigned int ***)(this + 4);
      Block = v13;
      LOBYTE(v30) = 1;
      v31 = sub_41CB60(v22, a2, (unsigned int **)v13);
      sub_41FFE0(v31, a3, (unsigned int **)v29);
      sub_41CB60(a2, *(unsigned int ***)(this + 8), &v31[a3]);
      v14 = *(void ***)(this + 4);
      v30 = 0;
      if ( v14 != nullptr )
        v15 = (*(uint32_t *)(this + 8) - (int)v14) >> 2;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != nullptr )
      {
        sub_4016E0(v14, *(void ***)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v13[v32];
      *(uint32_t *)(this + 8) = &v13[4 * v16];
      *(uint32_t *)(this + 4) = v13;
    }
  }
  v30 = -1;
  sub_41B010(v29);
}


// ------------------------------------------------------------
// 0x420960 sub_420960
// ------------------------------------------------------------
void /*thiscall*/ sub_420960(int this, int a2, unsigned int a3, int a4)
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
      sub_420550(this);
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
// 0x420BB0 sub_420BB0
// ------------------------------------------------------------
void /*thiscall*/ sub_420BB0(int *this, int a2)
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
    sub_41FFE0(v5, 1, a2);
    *(this + 2) = (int)(v5 + 1);
  }
  else
  {
    sub_4206D0((int)this, *(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x420C20 sub_420C20
// ------------------------------------------------------------
void /*thiscall*/ sub_420C20(int *this, int a2)
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
    sub_420960((int)this, *(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x420C90 sub_420C90
// ------------------------------------------------------------
char /*thiscall*/ sub_420C90(int *this, HWND hWnd)
{
  struct tagWINDOWINFO pwi; // [esp+8h] [ebp-148h] BYREF
  HWND v5; // [esp+44h] [ebp-10Ch] BYREF
  int v6; // [esp+48h] [ebp-108h]
  CHAR String[256]; // [esp+4Ch] [ebp-104h] BYREF
  int v8; // [esp+14Ch] [ebp-4h]

  v8 = dword_796E50;
  if ( GetWindowTextLengthA(hWnd) == 0 )
    return 0;
  if ( !IsWindowVisible(hWnd) )
    return 0;
  GetWindowInfo(hWnd, &pwi);
  if ( SLOBYTE(pwi.dwExStyle) < 0 )
    return 0;
  GetWindowTextA(hWnd, String, 255);
  OutputDebugStringA("*Minimize::");
  OutputDebugStringA(String);
  OutputDebugStringA("\n");
  v5 = hWnd;
  if ( IsZoomed(hWnd) )
    v6 = 3;
  else
    v6 = IsIconic(hWnd) ? 6 : 1;
  sub_420C20(this + 2, (int)&v5);
  ShowWindow(hWnd, 6);
  return 1;
}



// ------------------------------------------------------------
// 0x420D80 EnumFunc
// ------------------------------------------------------------
BOOL /*stdcall*/ EnumFunc(HWND hWnd, int *a2)
{
  sub_420C90(a2, hWnd);
  return true;
}



// ------------------------------------------------------------
// 0x420DA0 sub_420DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_420DA0(int this, int a2)
{
  int v4; // ecx
  const char *v5; // eax
  int v6; // eax
  int v7; // ecx
  const char *v8; // eax
  int v9; // eax
  HWND v10; // ebx
  const CHAR *v11; // eax
  HWND v12; // esi
  const CHAR *v13; // eax
  int v14; // eax
  uint8_t v15[4]; // [esp+4h] [ebp-18h] BYREF
  int v16; // [esp+8h] [ebp-14h]
  void *v17; // [esp+Ch] [ebp-10h] BYREF
  int v18; // [esp+18h] [ebp-4h]
  bool v19; // [esp+27h] [ebp+Bh]

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  sub_403920();
  nullsub_3(v4);
  sub_403990("DNF.trc", 2, 1, 0);
  byte_79C7B0 = _access("ConsoleDebug", 0) == 0;
  byte_79C7B8 = 0;
  dword_79C7B4 = 0;
  sub_48BB30((LPCVOID)0xA000);
  byte_77F280 = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 92) = 0;
  dword_8F7A24 = this;
  *(uint8_t *)(this + 112) = 1;
  if ( _access("ModeWindow", 0) == 0 )
    *(uint8_t *)(this + 112) = 0;
  dword_79C0A0 = a2;
  sub_4017E0(this + 268);
  sub_488690(this + 268, *(uint32_t *)(dword_79C0A0 + 100), "?", 0);
  v5 = (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 20);
  *(uint8_t *)(this + 112) = j__atol(v5) != 1;
  v6 = *(uint32_t *)(this + 272);
  if ( v6 == 0 || (unsigned int)((*(uint32_t *)(this + 276) - v6) >> 2) < 5 )
  {
    byte_77F280 = 1;
    while ( 1 )
    {
      v7 = *(uint32_t *)(this + 272);
      if ( v7 != 0 && (unsigned int)((*(uint32_t *)(this + 276) - v7) >> 2) >= 5 )
        break;
      v17 = nullptr;
      sub_41BFE0(&v17, szPassword);
      v18 = 0;
      sub_420BB0(&v17);
      v18 = -1;
      sub_41B010(&v17);
    }
  }
  v8 = (const char *)sub_41ACF0(*(uint32_t *)(this + 272));
  v19 = j__atol(v8) < 10;
  v9 = *(uint32_t *)(*(uint32_t *)(this + 272) + 16);
  if ( v9 == 0 || *(uint32_t *)(v9 + 4) == 0 )
    byte_77F280 = 1;
  if ( (uint8_t)sub_4422C0("Script/") == 0 )
  {
    ShowCursor(true);
    v10 = *(HWND *)(dword_79C0A0 + 16);
    v11 = (const CHAR *)sub_422E70(612);
    MessageBoxA(v10, v11, "Run Error", 0);
    PostQuitMessage(0);
  }
  if ( sub_420190(0, this) < 0 )
    return 0;
  dword_9D3BC8 = dword_79C0B0;
  byte_790700 = 0;
  byte_790701 = 0;
  byte_790702 = 0;
  byte_790703 = 0;
  dword_79070C = 0;
  dword_790710 = 6;
  dword_790714 = 12;
  dword_790718 = 0;
  dword_79071C = 1600;
  dword_790720 = 0;
  dword_790724 = 0;
  dword_790728 = 0;
  dword_79072C = 0;
  dword_790730 = dword_99FCCC;
  if ( byte_77F280 != 0 && _access("DebugConfig.txt", 0) != 0 )
  {
    ShowCursor(true);
    v12 = *(HWND *)(dword_79C0A0 + 16);
    v13 = (const CHAR *)sub_422E70(613);
    MessageBoxA(v12, v13, "Run Error", 0);
    PostQuitMessage(0);
    return 0x80000000;
  }
  else
  {
    sub_41F2C0(this);
    sub_419EE0(v15);
    v16 = sub_418DD0(91);
    sub_419EB0(v15);
    sub_41FC50();
    sub_439AB0();
    sub_41FAA0(this);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
      dword_8F8520,
      *(uint32_t *)(*(uint32_t *)(this + 20) + 44));
    *(uint32_t *)(dword_79C0A0 + 124) = this;
    v14 = *(uint32_t *)(this + 272);
    if ( v14 != 0 && (unsigned int)((*(uint32_t *)(this + 276) - v14) >> 2) >= 4 )
    {
      strcpy((char *)(this + 113), (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 12));
      strcpy((char *)(this + 177), (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 16));
      off_77F3FC((char *)&byte_6C36B8, this + 113);
      sub_48BA30(this + 113);
    }
    else
    {
      strcpy((char *)(this + 113), (const char *)sub_422E70(614));
      strcpy((char *)(this + 177), (const char *)sub_422E70(615));
    }
    if ( v19 )
    {
      if ( byte_77F280 != 0 )
        sub_41D300(0);
      else
        sub_41D300(5);
    }
    else
    {
      sub_41D300(0);
      if ( byte_77F280 == 0 )
        sub_41E4F0(this + 268);
    }
    sub_488670(dword_79C0B0);
    if ( byte_77F280 != 0 )
    {
      sub_489800((uint32_t *)this);
      dword_978998 = 0;
    }
    *(uint8_t *)(this + 4) = 1;
    return 1;
  }
}


// ------------------------------------------------------------
// 0x421220 sub_421220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_421220(uint32_t *lParam, int a2)
{
  HWND WindowA; // eax

  *lParam = &vftbl_nmodule__nMinimizeWindows;
  *(lParam + 1) = a2;
  *(lParam + 3) = 0;
  *(lParam + 4) = 0;
  *(lParam + 5) = 0;
  if ( *(lParam + 1) != 0 )
  {
    if ( *(lParam + 1) == 1 )
    {
      WindowA = FindWindowA("Shell_TrayWnd", nullptr);
      if ( WindowA != nullptr )
      {
        SendMessageA(WindowA, 0x111u, 0x19Fu, 0);
        return lParam;
      }
    }
    else if ( *(lParam + 1) == 2 )
    {
      sub_41FCF0();
      return lParam;
    }
  }
  else
  {
    EnumWindows((WNDENUMPROC)EnumFunc, (LPARAM)lParam);
  }
  return lParam;
}



// ------------------------------------------------------------
// 0x4212E0 sub_4212E0
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_4212E0(uint32_t *a1, uint32_t *a2)
{
  return *a1 < *a2;
}



// ------------------------------------------------------------
// 0x421300 sub_421300
// ------------------------------------------------------------
int /*cdecl*/ sub_421300(char *FileName)
{
  HMODULE AllocationBase; // ebx
  HRSRC ResourceA; // eax
  HRSRC v3; // esi
  HGLOBAL Resource; // edi
  size_t v6; // ebx
  FILE *v7; // esi
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+14h] [ebp-20h] BYREF
  LPCVOID lpAddress; // [esp+30h] [ebp-4h]

  lpAddress = &loc_421311;
  VirtualQuery(&loc_421311, &Buffer, 0x1Cu);
  AllocationBase = (HMODULE)Buffer.AllocationBase;
  ResourceA = FindResourceA((HMODULE)Buffer.AllocationBase, (LPCSTR)0x73, "File");
  v3 = ResourceA;
  if ( ResourceA == nullptr )
    return -1;
  Resource = LoadResource(AllocationBase, ResourceA);
  if ( Resource == nullptr )
    return -2;
  v6 = SizeofResource(AllocationBase, v3);
  v7 = fopen(FileName, "wb");
  sub_66BC25(Resource, v6, 1u, v7);
  fclose(v7);
  return 1;
}



// ------------------------------------------------------------
// 0x4213A0 sub_4213A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4213A0(uint32_t *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi

  v5 = a2;
  v6 = (a3 - a2) >> 5;
  if ( v6 <= 0 )
  {
    *a1 = a2;
    return a1;
  }
  else
  {
    while ( 1 )
    {
      v7 = v5 + 32 * (v6 / 2);
      if ( a5(v7, a4) != 0 )
      {
        a2 = v7 + 32;
        v6 += -1 - v6 / 2;
      }
      else
      {
        v6 /= 2;
      }
      if ( v6 <= 0 )
        break;
      v5 = a2;
    }
    *a1 = a2;
    return a1;
  }
}



// ------------------------------------------------------------
// 0x421410 sub_421410
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421410(uint32_t *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi

  v5 = a2;
  v6 = (a3 - a2) >> 5;
  if ( v6 <= 0 )
  {
    *a1 = a2;
    return a1;
  }
  else
  {
    while ( 1 )
    {
      v7 = v5 + 32 * (v6 / 2);
      if ( a5(a4, v7) != 0 )
      {
        v6 /= 2;
      }
      else
      {
        a2 = v7 + 32;
        v6 += -1 - v6 / 2;
      }
      if ( v6 <= 0 )
        break;
      v5 = a2;
    }
    *a1 = a2;
    return a1;
  }
}



// ------------------------------------------------------------
// 0x421480 sub_421480
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_421480(uint32_t *this, size_t Size, size_t a3, uint32_t *a4, unsigned int a5, size_t a6)
{
  uint32_t *v6; // esi
  unsigned int v7; // edi
  size_t v8; // ebx
  size_t v9; // edx
  size_t v10; // edx
  unsigned int v11; // ebx
  unsigned int v12; // eax
  uint8_t *v13; // eax
  int *v14; // ebx
  unsigned int v15; // eax
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // edx
  int v19; // eax
  unsigned int v20; // eax
  int v21; // ecx
  int v22; // eax
  unsigned int v23; // eax
  int v24; // ecx
  int v25; // eax
  unsigned int v26; // eax
  int v27; // ecx
  int v28; // eax
  unsigned int v29; // eax
  int v30; // ecx
  unsigned int v31; // eax
  int v32; // ecx
  int v33; // eax
  unsigned int v34; // ecx
  int v35; // eax
  unsigned int v36; // edx
  const void *v37; // eax
  int v38; // ecx
  uint32_t *v39; // eax
  unsigned int v40; // eax
  uint32_t *v41; // ecx
  uint32_t *v42; // eax
  unsigned int v43; // eax
  bool v44; // cf
  const void *v46; // [esp-8h] [ebp-1Ch]
  size_t v47; // [esp-4h] [ebp-18h]
  unsigned int v48; // [esp+Ch] [ebp-8h]
  size_t Sizea; // [esp+1Ch] [ebp+8h]
  size_t Sizeb; // [esp+1Ch] [ebp+8h]
  int v52; // [esp+24h] [ebp+10h]

  v6 = this;
  v7 = Size;
  if ( *(this + 5) < Size || a4[5] < a5 )
    std::_String_base::_Xran((std::_String_base *)this);
  v8 = a3;
  if ( *(this + 5) - Size < a3 )
  {
    v8 = *(this + 5) - Size;
    a3 = v8;
  }
  v9 = a6;
  if ( a4[5] - a5 < a6 )
  {
    v9 = a4[5] - a5;
    a6 = v9;
  }
  if ( -1 - v9 <= *(this + 5) - v8 )
    std::_String_base::_Xlen((std::_String_base *)this);
  v10 = a3;
  Sizea = *(this + 5) - Size - a3;
  v11 = a6 + *(this + 5) - a3;
  v48 = v11;
  if ( *(this + 5) < v11 )
  {
    if ( v11 == -1 )
      std::_String_base::_Xlen((std::_String_base *)this);
    v12 = *(this + 6);
    if ( v12 >= v11 )
    {
      if ( v11 == 0 )
      {
        *(this + 5) = 0;
        if ( v12 < 0x10 )
          v13 = this + 1;
        else
          v13 = (uint8_t *)*(this + 1);
        *v13 = 0;
      }
    }
    else
    {
      sub_4012B0(this, v11, *(this + 5));
      v10 = a3;
    }
  }
  v14 = v6 + 1;
  if ( v6 == a4 )
  {
    if ( a6 > v10 )
    {
      if ( a5 > v7 )
      {
        v31 = v6[6];
        if ( v7 + v10 > a5 )
        {
          if ( v31 < 0x10 )
            v38 = (int)(v6 + 1);
          else
            v38 = *v14;
          if ( v31 < 0x10 )
            v39 = v6 + 1;
          else
            v39 = (uint32_t *)*v14;
          memcpy_0((char *)v39 + v7, (const void *)(a5 + v38), a3);
          v40 = v6[6];
          if ( v40 < 0x10 )
            v41 = v6 + 1;
          else
            v41 = (uint32_t *)*v14;
          if ( v40 < 0x10 )
            v42 = v6 + 1;
          else
            v42 = (uint32_t *)*v14;
          memcpy_0((char *)v42 + v7 + a6, (char *)v41 + v7 + a3, Sizea);
          v43 = v6[6];
          if ( v43 < 0x10 )
            v52 = (int)(v6 + 1);
          else
            v52 = *v14;
          if ( v43 < 0x10 )
            Sizeb = (size_t)(v6 + 1);
          else
            Sizeb = *v14;
          v47 = a6 - a3;
          v36 = v7 + Sizeb;
          v7 = a3;
          v46 = (const void *)(a6 + a5 + v52);
        }
        else
        {
          if ( v31 < 0x10 )
            v32 = (int)(v6 + 1);
          else
            v32 = *v14;
          if ( v31 < 0x10 )
            v33 = (int)(v6 + 1);
          else
            v33 = *v14;
          memcpy_0((void *)(a6 + v7 + v33), (const void *)(a3 + v7 + v32), Sizea);
          v34 = v6[6];
          if ( v34 < 0x10 )
            v35 = (int)(v6 + 1);
          else
            v35 = *v14;
          if ( v34 < 0x10 )
          {
            v47 = a6;
            v37 = (const void *)(a6 + a5 + v35 - a3);
            v36 = (unsigned int)(v6 + 1);
          }
          else
          {
            v36 = *v14;
            v47 = a6;
            v37 = (const void *)(a6 + a5 + v35 - a3);
          }
          v46 = v37;
        }
        memcpy_0((void *)(v7 + v36), v46, v47);
      }
      else
      {
        v26 = v6[6];
        if ( v26 < 0x10 )
          v27 = (int)(v6 + 1);
        else
          v27 = *v14;
        if ( v26 < 0x10 )
          v28 = (int)(v6 + 1);
        else
          v28 = *v14;
        memcpy_0((void *)(a6 + v7 + v28), (const void *)(a3 + v7 + v27), Sizea);
        v29 = v6[6];
        if ( v29 < 0x10 )
          v30 = (int)(v6 + 1);
        else
          v30 = *v14;
        if ( v29 < 0x10 )
          memcpy_0((char *)v14 + v7, (const void *)(a5 + v30), a6);
        else
          memcpy_0((void *)(v7 + *v14), (const void *)(a5 + v30), a6);
      }
    }
    else
    {
      v20 = v6[6];
      if ( v20 < 0x10 )
        v21 = (int)(v6 + 1);
      else
        v21 = *v14;
      if ( v20 < 0x10 )
        v22 = (int)(v6 + 1);
      else
        v22 = *v14;
      memcpy_0((void *)(v7 + v22), (const void *)(a5 + v21), a6);
      v23 = v6[6];
      if ( v23 < 0x10 )
        v24 = (int)(v6 + 1);
      else
        v24 = *v14;
      if ( v23 < 0x10 )
        v25 = (int)(v6 + 1);
      else
        v25 = *v14;
      memcpy_0((void *)(a6 + v7 + v25), (const void *)(a3 + v7 + v24), Sizea);
    }
  }
  else
  {
    v15 = v6[6];
    if ( v15 < 0x10 )
      v16 = (int)(v6 + 1);
    else
      v16 = *v14;
    if ( v15 < 0x10 )
      v17 = (int)(v6 + 1);
    else
      v17 = *v14;
    memcpy_0((void *)(a6 + v7 + v17), (const void *)(a3 + v7 + v16), Sizea);
    if ( a4[6] < 0x10u )
      v18 = a4 + 1;
    else
      v18 = (uint32_t *)a4[1];
    if ( v6[6] < 0x10u )
      v19 = (int)(v6 + 1);
    else
      v19 = *v14;
    qmemcpy((void *)(v19 + v7), (char *)v18 + a5, a6);
    v6 = this;
  }
  v44 = v6[6] < 0x10u;
  v6[5] = v48;
  if ( !v44 )
    v14 = (int *)*v14;
  *((uint8_t *)v14 + v48) = 0;
  return v6;
}


// ------------------------------------------------------------
// 0x4217E0 sub_4217E0
// ------------------------------------------------------------
int */*cdecl*/ sub_4217E0(int *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // edi
  int v7; // esi
  int v9; // ebx
  int v10; // ecx

  v5 = a2;
  v6 = (a3 - a2) >> 5;
  if ( v6 <= 0 )
  {
LABEL_7:
    a1[1] = v5;
    *a1 = v5;
    return a1;
  }
  while ( 1 )
  {
    v7 = v5 + 32 * (v6 / 2);
    if ( a5(v7, a4) == 0 )
      break;
    a2 = v7 + 32;
    v6 += -1 - v6 / 2;
LABEL_6:
    v5 = a2;
    if ( v6 <= 0 )
      goto LABEL_7;
  }
  if ( a5(a4, v7) != 0 )
  {
    v6 /= 2;
    goto LABEL_6;
  }
  v9 = a2;
  sub_4213A0(&a2, a2, v7, a4, a5);
  sub_421410(&a3, v7 + 32, v9 + 32 * v6, a4, a5);
  v10 = a2;
  a1[1] = a3;
  *a1 = v10;
  return a1;
}



// ------------------------------------------------------------
// 0x4218A0 sub_4218A0
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_4218A0(unsigned int *this, size_t a2, size_t Size, uint8_t *a4, size_t a5)
{
  unsigned int v6; // esi
  unsigned int v7; // eax
  uint32_t *v8; // eax
  int v9; // ecx
  size_t v11; // edi
  size_t v12; // ecx
  size_t v13; // edx
  uint32_t *v14; // eax
  unsigned int v15; // esi
  unsigned int v16; // eax
  bool v17; // zf
  unsigned int v18; // ecx
  uint32_t *v19; // eax
  uint32_t *v20; // esi
  uint32_t *v21; // eax
  bool v22; // cf
  uint32_t *v23; // [esp+Ch] [ebp-4h]
  unsigned int v24; // [esp+Ch] [ebp-4h]
  size_t Sizea; // [esp+1Ch] [ebp+Ch]

  v6 = *(this + 6);
  if ( v6 < 0x10 )
    v7 = (unsigned int)(this + 1);
  else
    v7 = *(this + 1);
  if ( (unsigned int)a4 >= v7 )
  {
    v8 = this + 1;
    v9 = v6 < 0x10 ? (int)(this + 1) : *v8;
    if ( v9 + *(this + 5) > (unsigned int)a4 )
    {
      if ( v6 >= 0x10 )
        v8 = (uint32_t *)*v8;
      return (unsigned int *)sub_421480(a2, Size, (int)this, a4 - (uint8_t *)v8, a5);
    }
  }
  if ( *(this + 5) < a2 )
    std::_String_base::_Xran((std::_String_base *)this);
  v11 = Size;
  if ( *(this + 5) - a2 < Size )
    v11 = *(this + 5) - a2;
  v12 = a5;
  if ( -1 - a5 <= *(this + 5) - v11 )
    std::_String_base::_Xlen((std::_String_base *)this);
  v13 = *(this + 5) - a2 - v11;
  Sizea = v13;
  if ( a5 < v11 )
  {
    v14 = this + 1;
    if ( *(this + 6) < 0x10 )
      v23 = this + 1;
    else
      v23 = (uint32_t *)*v14;
    if ( *(this + 6) >= 0x10 )
      v14 = (uint32_t *)*v14;
    memcpy_0((char *)v14 + a2 + a5, (char *)v23 + a2 + v11, v13);
    v13 = Sizea;
    v12 = a5;
  }
  if ( v12 == 0 && v11 == 0 )
    return this;
  v15 = *(this + 5) + v12 - v11;
  v24 = v15;
  if ( v15 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  v16 = *(this + 6);
  if ( v16 < v15 )
  {
    sub_4012B0(this, v15, *(this + 5));
    v13 = Sizea;
    v17 = v15 == 0;
    goto LABEL_31;
  }
  v17 = v15 == 0;
  if ( v15 != 0 )
  {
LABEL_31:
    if ( !v17 )
    {
      if ( v11 < a5 )
      {
        v18 = *(this + 6);
        v19 = this + 1;
        if ( v18 < 0x10 )
          v20 = this + 1;
        else
          v20 = (uint32_t *)*v19;
        if ( v18 >= 0x10 )
          v19 = (uint32_t *)*v19;
        memcpy_0((char *)v19 + a2 + a5, (char *)v20 + a2 + v11, v13);
      }
      if ( *(this + 6) < 0x10 )
        v21 = this + 1;
      else
        v21 = (uint32_t *)*(this + 1);
      qmemcpy((char *)v21 + a2, a4, a5);
      v22 = *(this + 6) < 0x10;
      *(this + 5) = v24;
      if ( !v22 )
      {
        *(uint8_t *)(*(this + 1) + v24) = 0;
        return this;
      }
      *((uint8_t *)this + v24 + 4) = 0;
    }
    return this;
  }
  *(this + 5) = 0;
  if ( v16 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    *(uint8_t *)*(this + 1) = 0;
  return this;
}


// ------------------------------------------------------------
// 0x421A80 sub_421A80
// ------------------------------------------------------------
void /*noreturn*/ sub_421A80()
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
// 0x421AF0 sub_421AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_421AF0(uint32_t *this, uint32_t *a2)
{
  int v2; // eax
  int v3; // edx
  int result; // eax
  int v5; // [esp+Ch] [ebp-14h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+14h] [ebp-Ch]
  int v8; // [esp+18h] [ebp-8h]

  v5 = *(this + 1);
  v6 = *(this + 2);
  v7 = *(this + 3);
  v8 = *(this + 4);
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  a2[1] = v5;
  a2[2] = v6;
  a2[3] = v7;
  a2[4] = v8;
  v2 = *(this + 5);
  *(this + 5) = a2[5];
  v3 = a2[6];
  a2[5] = v2;
  result = *(this + 6);
  *(this + 6) = v3;
  a2[6] = result;
  return result;
}



// ------------------------------------------------------------
// 0x421B80 sub_421B80
// ------------------------------------------------------------
char /*thiscall*/ sub_421B80(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x7FFFFFF )
    sub_421A80(this);
  v4 = (char *)operator new(32 * a2);
  *(this + 3) = &v4[32 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x421BD0 sub_421BD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421BD0(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 32);
    v3 -= 32;
    v4 -= 8;
    *v4 = v5;
    sub_4014D0((std::_String_base *)(v4 + 1), v3 + 4, 0, -1);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x421C10 sub_421C10
// ------------------------------------------------------------
int /*cdecl*/ sub_421C10(uint32_t *a1, uint32_t *a2, int a3)
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
      *(uint32_t *)v3 = *a1;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a1 + 1, 0, -1);
    }
    v3 += 32;
    LOBYTE(v7) = 0;
    a1 += 8;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x421CE0 sub_421CE0
// ------------------------------------------------------------
void /*cdecl*/ sub_421CE0(
        int a1,
        int a2,
        int a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(uint32_t *, int *))
{
  int v12; // esi
  int i; // edi
  uint32_t *v14; // ebx
  uint32_t *v15; // eax
  uint32_t *v16; // esi

  v12 = a2;
  for ( i = (a2 - 1) / 2; a3 < v12; i = (i - 1) / 2 )
  {
    v14 = (uint32_t *)(32 * i + a1);
    if ( a12(v14, &a4) == 0 )
      break;
    v15 = (uint32_t *)(a1 + 32 * v12);
    *v15 = *v14;
    sub_4014D0((std::_String_base *)(v15 + 1), v14 + 1, 0, -1);
    v12 = i;
  }
  v16 = (uint32_t *)(a1 + 32 * v12);
  *v16 = a4;
  sub_4014D0((std::_String_base *)(v16 + 1), &a5, 0, -1);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x421DA0 sub_421DA0
// ------------------------------------------------------------
int /*cdecl*/ sub_421DA0(int a1, int a2, char *a3)
{
  int v3; // ecx
  int result; // eax
  int v5; // ebx
  int v6; // edx
  int v7; // ecx
  char *v8; // ebx
  int v9; // edx
  char *v10; // esi
  char *v11; // edi
  char **v12; // eax
  char *v13; // esi
  int v14; // eax
  char **v15; // eax
  bool v16; // zf
  char *v17; // [esp+Ch] [ebp-48h] BYREF
  int v18; // [esp+10h] [ebp-44h]
  int v19; // [esp+14h] [ebp-40h] BYREF
  char *v20; // [esp+18h] [ebp-3Ch] BYREF
  int v21; // [esp+1Ch] [ebp-38h]
  int v22; // [esp+20h] [ebp-34h]
  int v23; // [esp+24h] [ebp-30h]
  char v24[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *Block; // [esp+2Ch] [ebp-28h]
  int v26; // [esp+3Ch] [ebp-18h]
  unsigned int v27; // [esp+40h] [ebp-14h]
  int v28; // [esp+44h] [ebp-10h]
  int v29; // [esp+50h] [ebp-4h]

  v3 = (a2 - a1) >> 5;
  v28 = dword_796E50;
  v21 = v3;
  result = (int)&a3[-a1] >> 5;
  v5 = v3;
  if ( v3 != 0 )
  {
    do
    {
      v6 = result % v5;
      result = v5;
      v5 = v6;
    }
    while ( v6 != 0 );
  }
  if ( result < (int)&a3[-a1] >> 5 && result > 0 )
  {
    v7 = 32 * v3;
    v8 = (char *)(a1 + 32 * result);
    v9 = 4 - v7;
    a2 = v7;
    v18 = 4 - v7;
    v22 = result;
    while ( 1 )
    {
      v10 = &v8[v7];
      v11 = v8;
      v23 = *(uint32_t *)v8;
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      sub_4014D0((std::_String_base *)v24, &v8[v7 + v9], 0, -1);
      v29 = 0;
      if ( v10 == a3 )
      {
        v12 = (char **)&a1;
      }
      else
      {
        v17 = v10;
        v12 = &v17;
      }
      v13 = *v12;
      if ( *v12 != v8 )
      {
        do
        {
          *(uint32_t *)v11 = *(uint32_t *)v13;
          sub_4014D0((std::_String_base *)(v11 + 4), v13 + 4, 0, -1);
          v14 = (a3 - v13) >> 5;
          v11 = v13;
          if ( v21 >= v14 )
          {
            v19 = a1 + 32 * (v21 - v14);
            v15 = (char **)&v19;
          }
          else
          {
            v20 = &v13[a2];
            v15 = &v20;
          }
          v13 = *v15;
        }
        while ( *v15 != v8 );
      }
      *(uint32_t *)v11 = v23;
      sub_4014D0((std::_String_base *)(v11 + 4), v24, 0, -1);
      v29 = -1;
      if ( v27 >= 0x10 )
        j__free(Block);
      v8 -= 32;
      result = v22 - 1;
      v16 = v22 == 1;
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      --v22;
      if ( v16 )
        break;
      v7 = a2;
      v9 = v18;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x421F30 sub_421F30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421F30(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 8 )
  {
    *i = *a3;
    sub_4014D0((std::_String_base *)(i + 1), a3 + 1, 0, -1);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x421F70 sub_421F70
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421F70(int a1, int a2, uint32_t *a3)
{
  return sub_421BD0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x421F90 sub_421F90
// ------------------------------------------------------------
int /*cdecl*/ sub_421F90(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int result; // eax
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
      *(uint32_t *)v3 = *a3;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      result = sub_4014D0((std::_String_base *)(v3 + 4), a3 + 1, 0, -1);
    }
    v3 += 32;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x422060 sub_422060
// ------------------------------------------------------------
void /*cdecl*/ sub_422060(
        int a1,
        int a2,
        int a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(int, int))
{
  int v12; // edi
  int v13; // eax
  int v14; // esi
  bool v15; // zf
  int v16; // edx
  uint32_t *v17; // ecx
  int v18; // eax
  int v19; // ecx
  uint32_t *v20; // edi
  char v21; // [esp-20h] [ebp-38h] BYREF
  void *v22; // [esp-1Ch] [ebp-34h]
  int v23; // [esp-18h] [ebp-30h]
  int v24; // [esp-14h] [ebp-2Ch]
  int v25; // [esp-10h] [ebp-28h]
  int v26; // [esp-Ch] [ebp-24h]
  unsigned int v27; // [esp-8h] [ebp-20h]
  int v28; // [esp-4h] [ebp-1Ch]
  int v29; // [esp+14h] [ebp-4h]

  v12 = a2;
  v13 = a3;
  v14 = 2 * a2 + 2;
  v15 = v14 == a3;
  v29 = 0;
  if ( v14 < a3 )
  {
    do
    {
      if ( a12(a1 + 32 * v14, a1 + 32 * v14 - 32) != 0 )
        --v14;
      v16 = *(uint32_t *)(32 * v14 + a1);
      v28 = -1;
      v17 = (uint32_t *)(a1 + 32 * v12);
      v27 = 0;
      *v17 = v16;
      sub_4014D0((std::_String_base *)(v17 + 1), a1 + 32 * v14 + 4, v27, v28);
      v13 = a3;
      v12 = v14;
      v14 = 2 * v14 + 2;
    }
    while ( v14 < a3 );
    v15 = v14 == a3;
  }
  if ( v15 )
  {
    v18 = 32 * v13;
    v19 = *(uint32_t *)(v18 + a1 - 32);
    v28 = -1;
    v20 = (uint32_t *)(a1 + 32 * v12);
    v27 = 0;
    *v20 = v19;
    sub_4014D0((std::_String_base *)(v20 + 1), v18 + a1 - 32 + 4, v27, v28);
    v12 = a3 - 1;
  }
  v28 = (int)a12;
  v27 = 15;
  v26 = 0;
  LOBYTE(v22) = 0;
  sub_4014D0((std::_String_base *)&v21, &a5, 0, -1);
  sub_421CE0(a1, v12, a2, a4, v21, v22, v23, v24, v25, v26, v27, (uint8_t (/*cdecl*/ *)(uint32_t *, int *))v28);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x422170 sub_422170
// ------------------------------------------------------------
void /*cdecl*/ sub_422170(
        int *a1,
        int a2,
        uint32_t *a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(int, int))
{
  int v12; // ecx
  char v13; // [esp-20h] [ebp-30h] BYREF
  void *v14; // [esp-1Ch] [ebp-2Ch]
  int v15; // [esp-18h] [ebp-28h]
  int v16; // [esp-14h] [ebp-24h]
  int v17; // [esp-10h] [ebp-20h]
  int v18; // [esp-Ch] [ebp-1Ch]
  unsigned int v19; // [esp-8h] [ebp-18h]
  int v20; // [esp-4h] [ebp-14h]
  int v21; // [esp+Ch] [ebp-4h]

  v12 = *a1;
  v20 = -1;
  v19 = 0;
  *a3 = v12;
  v21 = 0;
  sub_4014D0((std::_String_base *)(a3 + 1), a1 + 1, v19, v20);
  v20 = (int)a12;
  v19 = 15;
  v18 = 0;
  LOBYTE(v14) = 0;
  sub_4014D0((std::_String_base *)&v13, &a5, 0, -1);
  sub_422060(
    (int)a1,
    0,
    (a2 - (int)a1) >> 5,
    a4,
    v13,
    v14,
    v15,
    v16,
    v17,
    v18,
    v19,
    (uint8_t (/*cdecl*/ *)(int, int))v20);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x422220 sub_422220
// ------------------------------------------------------------
int /*stdcall*/ sub_422220(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 32 )
    result = sub_442C50(i);
  return result;
}



// ------------------------------------------------------------
// 0x422250 sub_422250
// ------------------------------------------------------------
int /*stdcall*/ sub_422250(uint32_t *a1, uint32_t *a2, int a3)
{
  return sub_421C10(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x422270 sub_422270
// ------------------------------------------------------------
void /*cdecl*/ sub_422270(int a1, int a2, uint8_t (/*cdecl*/ *a3)(int, int))
{
  int v3; // esi
  int v4; // edi
  int v5; // ecx
  int v6; // [esp-24h] [ebp-30h]
  char v7; // [esp-20h] [ebp-2Ch] BYREF
  void *v8; // [esp-1Ch] [ebp-28h]
  int v9; // [esp-18h] [ebp-24h]
  int v10; // [esp-14h] [ebp-20h]
  int v11; // [esp-10h] [ebp-1Ch]
  int v12; // [esp-Ch] [ebp-18h]
  unsigned int v13; // [esp-8h] [ebp-14h]
  uint8_t (/*cdecl*/ *v14)(int, int); // [esp-4h] [ebp-10h]

  v3 = ((a2 - a1) >> 5) / 2;
  if ( v3 > 0 )
  {
    v4 = a1 + 32 * v3;
    do
    {
      v5 = *(uint32_t *)(v4 - 32);
      v14 = a3;
      v4 -= 32;
      v6 = v5;
      v13 = 15;
      v12 = 0;
      --v3;
      LOBYTE(v8) = 0;
      sub_4014D0((std::_String_base *)&v7, v4 + 4, 0, -1);
      sub_422060(a1, v3, (a2 - a1) >> 5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
    }
    while ( v3 > 0 );
  }
}



// ------------------------------------------------------------
// 0x4222F0 sub_4222F0
// ------------------------------------------------------------
void /*cdecl*/ sub_4222F0(int *a1, int a2, uint8_t (/*cdecl*/ *a3)(int, int))
{
  int v3; // ecx
  int v4; // [esp-28h] [ebp-2Ch]
  char v5; // [esp-24h] [ebp-28h] BYREF
  void *v6; // [esp-20h] [ebp-24h]
  int v7; // [esp-1Ch] [ebp-20h]
  int v8; // [esp-18h] [ebp-1Ch]
  int v9; // [esp-14h] [ebp-18h]
  int v10; // [esp-10h] [ebp-14h]
  unsigned int v11; // [esp-Ch] [ebp-10h]
  uint8_t (/*cdecl*/ *v12)(int, int); // [esp-8h] [ebp-Ch]
  int v13; // [esp-4h] [ebp-8h]

  v3 = *(uint32_t *)(a2 - 32);
  v13 = 0;
  v12 = a3;
  v4 = v3;
  v10 = 0;
  v11 = 15;
  LOBYTE(v6) = 0;
  sub_4014D0((std::_String_base *)&v5, a2 - 32 + 4, 0, -1);
  sub_422170(a1, a2 - 32, (uint32_t *)(a2 - 32), v4, v5, v6, v7, v8, v9, v10, v11, v12);
}



// ------------------------------------------------------------
// 0x422340 sub_422340
// ------------------------------------------------------------
int /*thiscall*/ sub_422340(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 32 )
      sub_442C50(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x422380 sub_422380
// ------------------------------------------------------------
int /*stdcall*/ sub_422380(int a1, int a2, uint32_t *a3)
{
  sub_421F90(a1, a2, a3);
  return a1 + 32 * a2;
}



// ------------------------------------------------------------
// 0x4223B0 sub_4223B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4223B0(int this, int a2, unsigned int a3, uint32_t *a4)
{
  int v5; // ecx
  unsigned int v6; // eax
  int v8; // edx
  int v9; // edx
  unsigned int v10; // eax
  int v11; // edx
  int v12; // eax
  char *v13; // ebx
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // edi
  char *v17; // eax
  int v18; // edi
  char *v19; // edi
  int v20; // eax
  int v21; // [esp-18h] [ebp-64h]
  void *v22; // [esp-18h] [ebp-64h]
  int v23; // [esp-10h] [ebp-5Ch]
  int v24; // [esp-Ch] [ebp-58h]
  unsigned int v25; // [esp-8h] [ebp-54h]
  uint32_t v26[4]; // [esp+0h] [ebp-4Ch] BYREF
  void *Block; // [esp+10h] [ebp-3Ch]
  char *v28; // [esp+14h] [ebp-38h]
  int v29; // [esp+18h] [ebp-34h] BYREF
  size_t v30; // [esp+1Ch] [ebp-30h] BYREF
  void *v31; // [esp+20h] [ebp-2Ch]
  int v32; // [esp+30h] [ebp-1Ch]
  unsigned int v33; // [esp+34h] [ebp-18h]
  int v34; // [esp+38h] [ebp-14h]
  uint32_t *v35; // [esp+3Ch] [ebp-10h]
  int v36; // [esp+48h] [ebp-4h]
  int v37; // [esp+58h] [ebp+Ch]

  v34 = dword_796E50;
  v35 = v26;
  v29 = *a4;
  v26[3] = this;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0(&v30, a4 + 1, 0, 0xFFFFFFFF);
  v5 = *(uint32_t *)(this + 4);
  v36 = 0;
  if ( v5 != 0 )
    v6 = (*(uint32_t *)(this + 12) - v5) >> 5;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 5;
    else
      v8 = 0;
    if ( 0x7FFFFFF - v8 < a3 )
      sub_421A80(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 5;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v17 = *(char **)(this + 8);
      Block = v17;
      if ( (int)&v17[-a2] >> 5 >= a3 )
      {
        v19 = &v17[-32 * a3];
        v20 = sub_421C10(v19, v17, v17);
        v22 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_421F70(a2, v19, v22);
        sub_421F30(a2, a2 + 32 * a3, &v29);
      }
      else
      {
        sub_421C10(a2, v17, a2 + 32 * a3);
        v25 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 5);
        v24 = *(uint32_t *)(this + 8);
        LOBYTE(v36) = 3;
        sub_422380(v24, v25, &v29);
        v18 = 32 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v18;
        v36 = 0;
        sub_421F30(a2, v18 - 32 * a3, &v29);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 5;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 5;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v37 = 32 * v10;
      v13 = (char *)operator new(32 * v10);
      v21 = *(uint32_t *)(this + 4);
      Block = v13;
      v28 = v13;
      LOBYTE(v36) = 1;
      v28 = (char *)sub_421C10(v21, a2, v13);
      sub_421F90(v28, a3, &v29);
      v23 = *(uint32_t *)(this + 8);
      v28 += 32 * a3;
      sub_421C10(a2, v23, v28);
      v14 = *(uint32_t *)(this + 4);
      if ( v14 != 0 )
        v15 = (*(uint32_t *)(this + 8) - v14) >> 5;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != 0 )
      {
        sub_422220(v14, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v13[v37];
      *(uint32_t *)(this + 8) = &v13[32 * v16];
      *(uint32_t *)(this + 4) = v13;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x422670 sub_422670
// ------------------------------------------------------------
int /*cdecl*/ sub_422670(int a1, int a2, uint8_t (/*cdecl*/ *a3)(int, int))
{
  int result; // eax
  int v4; // ebx
  int i; // esi
  int v6; // edi
  int v7; // ebx

  result = a2;
  v4 = a1;
  if ( a1 != a2 )
  {
    for ( i = a1 + 32; i != a2; i += 32 )
    {
      if ( a3(i, v4) != 0 )
      {
        if ( v4 != i && i != i + 32 )
          sub_421DA0(v4, i, (char *)(i + 32));
      }
      else
      {
        v6 = i - 32;
        if ( a3(i, i - 32) != 0 )
        {
          do
          {
            v7 = v6;
            v6 -= 32;
          }
          while ( a3(i, v6) != 0 );
          if ( v7 != i )
            sub_421DA0(v7, i, (char *)(i + 32));
          v4 = a1;
        }
      }
      result = a2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x422700 sub_422700
// ------------------------------------------------------------
int /*cdecl*/ sub_422700(int *a1, int *a2, int *a3, uint8_t (/*cdecl*/ *a4)(int *, int *))
{
  int v4; // eax
  int v5; // eax
  int result; // eax
  int v7; // eax

  if ( a4(a2, a1) != 0 )
  {
    v4 = *a2;
    *a2 = *a1;
    *a1 = v4;
    sub_421AF0(a2 + 1, a1 + 1);
  }
  if ( a4(a3, a2) != 0 )
  {
    v5 = *a3;
    *a3 = *a2;
    *a2 = v5;
    sub_421AF0(a3 + 1, a2 + 1);
  }
  result = ((int (/*cdecl*/ *)(int *, int *))a4)(a2, a1);
  if ( (uint8_t)result != 0 )
  {
    v7 = *a2;
    *a2 = *a1;
    *a1 = v7;
    return sub_421AF0(a2 + 1, a1 + 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x422780 sub_422780
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_422780(int *this)
{
  return sub_422340(this);
}



// ------------------------------------------------------------
// 0x422790 sub_422790
// ------------------------------------------------------------
int /*cdecl*/ sub_422790(int *a1, int a2, uint8_t (/*cdecl*/ *a3)(int, int))
{
  int v3; // esi
  int result; // eax

  v3 = a2;
  for ( result = (a2 - (int)a1) >> 5; result > 1; result = (v3 - (int)a1) >> 5 )
  {
    sub_4222F0(a1, v3, a3);
    v3 -= 32;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4227D0 sub_4227D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4227D0(int *a1, int *a2, int *a3, uint8_t (/*cdecl*/ *a4)(int *, int *))
{
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int *v9; // [esp-3Ch] [ebp-3Ch]
  int *v12; // [esp-14h] [ebp-14h]
  int *v13; // [esp+8h] [ebp+8h]
  int *v14; // [esp+10h] [ebp+10h]

  v4 = ((char *)a3 - (char *)a1) >> 5;
  if ( v4 <= 40 )
    return sub_422700(a1, a2, a3, a4);
  v5 = (v4 + 1) / 8;
  v6 = 8 * v5;
  v5 <<= 6;
  v7 = v6 * 4;
  v12 = (int *)((char *)a1 + v5);
  v13 = &a1[v6];
  sub_422700(a1, v13, v12, a4);
  sub_422700((int *)((char *)a2 - v7), a2, (int *)((char *)a2 + v7), a4);
  v9 = (int *)((char *)a3 - v5);
  v14 = (int *)((char *)a3 - v7);
  sub_422700(v9, v14, a3, a4);
  return sub_422700(v13, a2, v14, a4);
}



// ------------------------------------------------------------
// 0x422870 sub_422870
// ------------------------------------------------------------
void /*thiscall*/ sub_422870(int *this, int *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) >> 5;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 3) - v3) >> 5 )
  {
    v5 = *(this + 2);
    sub_421F90(v5, 1, a2);
    *(this + 2) = v5 + 32;
  }
  else
  {
    sub_4223B0(this, (char *)*(this + 2), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x4228E0 sub_4228E0
// ------------------------------------------------------------
int **/*cdecl*/ sub_4228E0(int **a1, unsigned int a2, int *a3, uint8_t (/*cdecl*/ *a4)(int *, int *))
{
  int *v4; // esi
  int *v5; // ebx
  int *v6; // eax
  int *v7; // edi
  int v8; // ecx
  bool v9; // zf
  int *v10; // ebx
  int v11; // eax
  bool v12; // cf
  int v13; // eax
  int *v14; // eax
  int *v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v20; // [esp+Ch] [ebp-Ch]
  int *v21; // [esp+10h] [ebp-8h]
  int *v22; // [esp+14h] [ebp-4h]
  int *i; // [esp+14h] [ebp-4h]

  v4 = (int *)(a2 + 32 * (((int)((int)a3 - a2) >> 5) / 2));
  sub_4227D0(a2, v4, a3 - 8, a4);
  v5 = v4 + 8;
  v21 = v4 + 8;
  if ( a2 < (unsigned int)v4 )
  {
    do
    {
      v22 = v4 - 8;
      if ( a4(v4 - 8, v4) != 0 )
        break;
      if ( a4(v4, v22) != 0 )
        break;
      v4 -= 8;
    }
    while ( a2 < (unsigned int)v22 );
  }
  if ( v5 < a3 )
  {
    do
    {
      if ( a4(v5, v4) != 0 )
        break;
      if ( a4(v4, v5) != 0 )
        break;
      v5 += 8;
    }
    while ( v5 < a3 );
    v21 = v5;
  }
  v6 = v4;
  v7 = v5;
  for ( i = v4; ; v6 = i )
  {
    while ( 1 )
    {
      if ( v7 < a3 )
      {
        do
        {
          if ( a4(v4, v7) == 0 )
          {
            if ( a4(v7, v4) != 0 )
              break;
            v8 = *v5;
            *v5 = *v7;
            *v7 = v8;
            v5 += 8;
            sub_421AF0(v7 + 1);
          }
          v7 += 8;
        }
        while ( v7 < a3 );
        v6 = i;
        v21 = v5;
      }
      v9 = v6 == (int *)a2;
      if ( (unsigned int)v6 > a2 )
      {
        v10 = v6 - 8;
        do
        {
          if ( a4(v10, v4) == 0 )
          {
            if ( a4(v4, v10) != 0 )
              break;
            v11 = *(v4 - 8);
            v4 -= 8;
            *v4 = *v10;
            *v10 = v11;
            sub_421AF0(v10 + 1);
          }
          v10 -= 8;
          v12 = a2 < (unsigned int)(i - 8);
          i -= 8;
        }
        while ( v12 );
        v6 = i;
        v5 = v21;
        v9 = i == (int *)a2;
      }
      if ( v9 )
        break;
      v14 = v6 - 8;
      i = v14;
      if ( v7 != a3 )
      {
        v15 = v7;
        v7 += 8;
        goto LABEL_29;
      }
      v4 -= 8;
      if ( v14 != v4 )
      {
        v16 = *v14;
        *v14 = *v4;
        *v4 = v16;
        sub_421AF0(v4 + 1);
      }
      v17 = *v4;
      v18 = *(v5 - 8);
      v5 -= 8;
      *v4 = v18;
      *v5 = v17;
      v21 = v5;
      sub_421AF0(v5 + 1);
      v6 = i;
    }
    if ( v7 == a3 )
      break;
    if ( v5 != v7 )
    {
      v13 = *v4;
      *v4 = *v5;
      *v5 = v13;
      sub_421AF0(v5 + 1);
    }
    v5 += 8;
    v14 = v7;
    v7 += 8;
    v15 = v4;
    v21 = v5;
    v4 += 8;
LABEL_29:
    v20 = *v15;
    *v15 = *v14;
    *v14 = v20;
    sub_421AF0(v14 + 1);
  }
  *a1 = v4;
  a1[1] = v5;
  return a1;
}


// ------------------------------------------------------------
// 0x422AE0 sub_422AE0
// ------------------------------------------------------------
int /*cdecl*/ sub_422AE0(int *a1, int *a2, int a3, uint8_t (/*cdecl*/ *a4)(int, int))
{
  int *v4; // ebx
  int *v5; // edi
  int result; // eax
  int *v8; // [esp+Ch] [ebp-8h] BYREF
  int *v9; // [esp+10h] [ebp-4h]

  v4 = a1;
  v5 = a2;
  result = ((char *)a2 - (char *)a1) >> 5;
  if ( result <= 32 )
  {
LABEL_7:
    if ( result > 1 )
      return sub_422670((int)v4, (int)v5, a4);
  }
  else
  {
    while ( a3 > 0 )
    {
      sub_4228E0(&v8, v4, v5, (uint8_t (/*cdecl*/ *)(int *, int *))a4);
      a3 = a3 / 2 / 2 + a3 / 2;
      if ( (int)(((char *)v8 - (char *)v4) & 0xFFFFFFE0) >= (int)(((char *)v5 - (char *)v9) & 0xFFFFFFE0) )
      {
        sub_422AE0(v9, v5, a3, a4);
        v5 = v8;
      }
      else
      {
        sub_422AE0(v4, v8, a3, a4);
        v4 = v9;
      }
      result = ((char *)v5 - (char *)v4) >> 5;
      if ( result <= 32 )
        goto LABEL_7;
    }
    if ( (int)(((char *)v5 - (char *)v4) & 0xFFFFFFE0) > 32 )
      sub_422270((int)v4, (int)v5, a4);
    return sub_422790(v4, (int)v5, a4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x422BD0 sub_422BD0
// ------------------------------------------------------------
int /*cdecl*/ sub_422BD0(char *FileName)
{
  FILE *v1; // eax
  FILE *v2; // edi
  unsigned int v4; // kr00_4
  signed int v5; // eax
  int i; // esi
  char v7; // cl
  int v8; // edi
  size_t j; // esi
  int v10; // [esp+8h] [ebp-85Ch] BYREF
  uint8_t v11[4]; // [esp+Ch] [ebp-858h] BYREF
  void *Block; // [esp+10h] [ebp-854h]
  int v13; // [esp+20h] [ebp-844h]
  unsigned int v14; // [esp+24h] [ebp-840h]
  FILE *v15; // [esp+28h] [ebp-83Ch]
  char Buffer; // [esp+2Ch] [ebp-838h] BYREF
  char Src[2047]; // [esp+2Dh] [ebp-837h] BYREF
  char String[12]; // [esp+82Ch] [ebp-38h] BYREF
  int v19; // [esp+838h] [ebp-2Ch] BYREF
  void *v20; // [esp+83Ch] [ebp-28h]
  int v21; // [esp+84Ch] [ebp-18h]
  unsigned int v22; // [esp+850h] [ebp-14h]
  int v23; // [esp+854h] [ebp-10h]
  int v24; // [esp+860h] [ebp-4h]

  v23 = dword_796E50;
  v1 = fopen(FileName, "r");
  v2 = v1;
  v15 = v1;
  if ( v1 == nullptr )
    return -1;
  if ( fgets(&Buffer, 2048, v1) != nullptr )
  {
    do
    {
      v4 = strlen(&Buffer);
      v5 = v4;
      if ( v4 != 0 )
      {
        if ( *((uint8_t *)&v15 + v4 + 3) == 10 )
        {
          *((uint8_t *)&v15 + v4 + 3) = 0;
          v5 = v4 - 1;
        }
        if ( v5 != 0 && (Buffer != 47 || Src[0] != 47) )
        {
          for ( i = 0; i < v5; String[i++] = v7 )
          {
            v7 = Src[i - 1];
            if ( v7 == 62 )
              break;
            if ( i >= 10 || v7 < 48 || v7 > 57 )
              goto LABEL_24;
          }
          if ( i != v5 )
          {
            String[i] = 0;
            v8 = j__atol(String);
            v22 = 15;
            v21 = 0;
            LOBYTE(v20) = 0;
            v24 = 0;
            sub_4015C0(&Src[i], strlen(&Src[i]));
            for ( j = sub_4027F0("\\n", 0, 2); j != -1; j = sub_4027F0("\\n", j, 2) )
              sub_4218A0((unsigned int *)&v19, j, 2u, "\n", 1u);
            v10 = v8;
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
            sub_4014D0((std::_String_base *)v11, &v19, 0, -1);
            LOBYTE(v24) = 1;
            sub_422870(&dword_8F7A74, &v10);
            if ( v14 >= 0x10 )
              j__free(Block);
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
            v24 = -1;
            if ( v22 >= 0x10 )
              j__free(v20);
            v2 = v15;
            v22 = 15;
            v21 = 0;
            LOBYTE(v20) = 0;
          }
        }
      }
LABEL_24:
      ;
    }
    while ( fgets(&Buffer, 2048, v2) != nullptr );
  }
  fclose(v2);
  sub_422AE0(
    (int *)dword_8F7A78,
    (int *)dword_8F7A7C,
    (dword_8F7A7C - dword_8F7A78) >> 5,
    (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  if ( dword_8F7A78 != 0 )
    return (dword_8F7A7C - dword_8F7A78) >> 5;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x422E70 sub_422E70
// ------------------------------------------------------------
char */*cdecl*/ sub_422E70(int a1)
{
  HWND DesktopWindow; // eax
  HWND v2; // eax
  uint32_t *v3; // esi
  int v5; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v6[4]; // [esp+10h] [ebp-4Ch] BYREF
  void *Block; // [esp+14h] [ebp-48h]
  int v8; // [esp+24h] [ebp-38h]
  unsigned int v9; // [esp+28h] [ebp-34h]
  uint8_t v10[4]; // [esp+2Ch] [ebp-30h] BYREF
  void *v11; // [esp+30h] [ebp-2Ch]
  int v12; // [esp+40h] [ebp-1Ch]
  unsigned int v13; // [esp+44h] [ebp-18h]
  uint32_t *v14; // [esp+48h] [ebp-14h] BYREF
  int v15; // [esp+58h] [ebp-4h]

  if ( byte_8F7A60 == 0 )
  {
    if ( sub_421300((char *)lpFileName) <= 0 )
    {
      DesktopWindow = GetDesktopWindow();
      MessageBoxA(DesktopWindow, "String Table extraction failed", "Fatal Error", 0);
      exit(1);
    }
    if ( sub_422BD0((char *)lpFileName) <= 0 )
    {
      v2 = GetDesktopWindow();
      MessageBoxA(v2, "String Table load failed", "Fatal Error", 0);
      DeleteFileA(lpFileName);
      exit(1);
    }
    DeleteFileA(lpFileName);
    byte_8F7A60 = 1;
  }
  v13 = 15;
  v12 = 0;
  LOBYTE(v11) = 0;
  sub_4015C0((void *)szPassword, 0);
  v15 = 0;
  v5 = a1;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v6, v10, 0, -1);
  LOBYTE(v15) = 1;
  sub_4217E0((int *)&v14, dword_8F7A78, dword_8F7A7C, (int)&v5, (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  v3 = v14;
  if ( v9 >= 0x10 )
    j__free(Block);
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  if ( v13 >= 0x10 )
    j__free(v11);
  if ( *v3 == a1 )
  {
    if ( v3[7] < 0x10u )
      return (char *)(v3 + 2);
    else
      return (char *)v3[2];
  }
  else
  {
    sprintf(byte_8F7A88, "CStringManager::getStr(%d) == NULL", a1);
    return byte_8F7A88;
  }
}



// ------------------------------------------------------------
// 0x423020 sub_423020
// ------------------------------------------------------------
int /*thiscall*/ sub_423020(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_mon + 1;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x423040 sub_423040
// ------------------------------------------------------------
int /*thiscall*/ sub_423040(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_mday;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x423060 sub_423060
// ------------------------------------------------------------
int /*thiscall*/ sub_423060(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_hour;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x423080 sub_423080
// ------------------------------------------------------------
int /*thiscall*/ sub_423080(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_min;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x4230A0 sub_4230A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4230A0(uint32_t *this)
{
  sub_6986D0();
  *this = &vftbl_CNGameSocket;
  *(this + 112) = 0;
  *(this + 113) = 0;
  *(this + 114) = 0;
  if ( sub_698870(*(void **)(dword_79C0A0 + 16), 0x100000u) >= 0 )
  {
    *(this + 115) = rand();
    *((uint16_t *)this + 232) = 0;
    *((uint8_t *)this + 466) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x423130 CNGameSocket__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNGameSocket__vmt0(void *Block, char a2)
{
  sub_423160();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x423160 sub_423160
// ------------------------------------------------------------
int /*thiscall*/ sub_423160(uint32_t *this)
{
  *this = &vftbl_CNGameSocket;
  sub_6987C0();
  return sub_698720(this);
}



// ------------------------------------------------------------
// 0x4231B0 sub_4231B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4231B0(int this, const char *ArgList, int a3)
{
  int result; // eax

  *(uint8_t *)(this + 466) = 0;
  *(uint32_t *)(this + 456) = 0;
  *(uint16_t *)(this + 464) = 0;
  off_77F3FC("[%s][%d]", ArgList, a3);
  result = sub_698DC0(this, (int)ArgList, a3);
  if ( result >= 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x423200 sub_423200
// ------------------------------------------------------------
int /*thiscall*/ sub_423200(int this, char a2)
{
  uint8_t v4[2]; // [esp+4h] [ebp-Ch] BYREF
  int v5; // [esp+6h] [ebp-Ah]

  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  if ( *(uint32_t *)(this + 452) != 0 || *(uint32_t *)(this + 448) != 0 )
  {
    off_77F3FC(asc_6C37C8);
    return 0x80000000;
  }
  else
  {
    v4[0] = 1;
    v4[1] = a2;
    v5 = 0;
    *(uint32_t *)(this + 452) = sub_698D70(this);
    sub_698C80(v4, 12);
    *(uint32_t *)(this + 448) = 0;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x423290 sub_423290
// ------------------------------------------------------------
int /*thiscall*/ sub_423290(int this, int a2, int a3)
{
  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  if ( a2 == 0 )
    return -2147483640;
  *(uint32_t *)(this + 448) += a3;
  return sub_698C80(a2, a3);
}



// ------------------------------------------------------------
// 0x4232E0 sub_4232E0
// ------------------------------------------------------------
__time64_t */*stdcall*/ sub_4232E0(__time64_t *a1)
{
  *a1 = _time64(nullptr);
  return a1;
}



// ------------------------------------------------------------
// 0x423300 sub_423300
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423300(unsigned int *a1, const char *a2)
{
  return sub_40BF00((std::_String_base *)a1, 0, a1[5], a2, strlen(a2)) == 0;
}



// ------------------------------------------------------------
// 0x423340 sub_423340
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423340(unsigned int *a1, const char *a2)
{
  return sub_40BF00((std::_String_base *)a1, 0, a1[5], a2, strlen(a2)) != 0;
}



// ------------------------------------------------------------
// 0x423380 sub_423380
// ------------------------------------------------------------
int /*thiscall*/ sub_423380(int this)
{
  int v3; // edi
  int v4; // eax
  int16_t v5; // dx
  int v6; // ecx
  int v7; // ebx
  int v8; // eax
  struct tm *v9; // eax
  struct tm *v10; // eax
  struct tm *v11; // eax
  struct tm *v12; // eax
  int tm_min; // ebx
  struct tm *v14; // eax
  int tm_sec; // eax
  int v16; // esi
  char *v17; // eax
  uint32_t *v18; // eax
  int tm_hour; // [esp+4h] [ebp-40h]
  int tm_mday; // [esp+8h] [ebp-3Ch]
  int v21; // [esp+Ch] [ebp-38h]
  __time64_t Time; // [esp+10h] [ebp-34h] BYREF
  uint8_t v23[4]; // [esp+18h] [ebp-2Ch] BYREF
  uint32_t v24[10]; // [esp+1Ch] [ebp-28h] BYREF

  v24[6] = dword_796E50;
  if ( *(uint8_t *)(this + 466) != 0 )
  {
    off_77F3FC(aSendlock);
    return 0x80000000;
  }
  else if ( *(uint8_t *)(this + 8) != 0 )
  {
    v3 = *(uint32_t *)(this + 452);
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 2) = *(uint32_t *)(this + 448) + 12;
      v4 = *(uint32_t *)(this + 452);
      v5 = *(uint16_t *)(this + 464);
      v6 = v4 + 10;
      v7 = v4 + 12;
      *(uint16_t *)(v3 + 10) = v5;
      v8 = *(uint32_t *)(this + 448);
      ++*(uint16_t *)(this + 464);
      *(uint32_t *)(v3 + 6) = sub_48BE40(v6, v8 + 2);
      sub_48BD40(v7, *(uint32_t *)(this + 448), this + 460);
      *(uint32_t *)(this + 452) = 0;
      *(uint32_t *)(this + 448) = 0;
      Time = _time64(nullptr);
      v9 = _localtime64(&Time);
      if ( v9 != nullptr )
        v21 = v9->tm_mon + 1;
      else
        v21 = 0;
      v10 = _localtime64(&Time);
      if ( v10 != nullptr )
        tm_mday = v10->tm_mday;
      else
        tm_mday = 0;
      v11 = _localtime64(&Time);
      if ( v11 != nullptr )
        tm_hour = v11->tm_hour;
      else
        tm_hour = -1;
      v12 = _localtime64(&Time);
      if ( v12 != nullptr )
        tm_min = v12->tm_min;
      else
        tm_min = -1;
      v14 = _localtime64(&Time);
      if ( v14 != nullptr )
        tm_sec = v14->tm_sec;
      else
        tm_sec = -1;
      off_77F3FC(
        "\n[-> COMMAND PACKET] Packet : %s, Size : %d, CheckSum : %d (%2d%2d-%2d:%2d:%2d)",
        *(const char **)&off_790928[4 * *(uint8_t *)(v3 + 1)],
        *(uint32_t *)(v3 + 2),
        *(uint32_t *)(v3 + 6),
        v21,
        tm_mday,
        tm_hour,
        tm_min,
        tm_sec);
      if ( *(uint8_t *)(v3 + 1) == 3 )
        *(uint8_t *)(this + 466) = 1;
      v16 = sub_698A50(this);
      if ( v16 != 1 && dword_8F8528 != nullptr )
      {
        v17 = (char *)sub_422E70(145);
        sub_401710(v17);
        v18 = (uint32_t *)v24[0];
        v24[9] = 0;
        if ( v24[5] < 0x10u )
          v18 = v24;
        sub_44E8D0(dword_8F8528, (void *)0x1B, v18, 1);
        sub_501490(v23);
      }
      return v16;
    }
    else
    {
      return 0x80000000;
    }
  }
  else
  {
    return -2147483564;
  }
}


// ------------------------------------------------------------
// 0x4235A0 CNGameSocket__vmt4
// ------------------------------------------------------------
int /*thiscall*/ sub_4235A0(int this, int a2, int a3, int a4, unsigned int a5)
{
  int v6; // eax
  int v7; // edi
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  void *p_Block; // eax
  int v12; // eax
  int v13; // esi
  char *v14; // eax
  char v15; // cl
  char *v16; // eax
  char v17; // cl
  char *v18; // eax
  char v19; // cl
  int v20; // esi
  int v21; // edi
  int v22; // eax
  size_t v24; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h] BYREF
  unsigned int v26; // [esp+20h] [ebp-18h]
  unsigned int v27; // [esp+24h] [ebp-14h]
  int v28; // [esp+28h] [ebp-10h]
  int v29; // [esp+34h] [ebp-4h]

  v28 = dword_796E50;
  switch ( (uint16_t)a5 )
  {
    case 1u:
      v13 = sub_698B50(this);
      off_77F3FC("nLen:ISocket : %d", v13);
      if ( v13 >= 0 )
      {
        while ( 1 )
        {
          if ( *(uint8_t *)(this + 8) != 0 )
          {
            if ( (uint8_t)sub_698D90(this) != 0 )
              v20 = *(uint32_t *)(sub_698D80(this) + 2);
            else
              v20 = sub_698B50(this);
          }
          else
          {
            v20 = 0;
          }
          off_77F3FC("nLen:GameSocket : %d", v20);
          if ( v20 == 0 )
            break;
          v21 = dword_8F7A24;
          if ( dword_8F7A24 != 0 )
          {
            v22 = sub_698D80(this);
            if ( sub_48BE70(v21, v22, v20) < 0 )
              break;
          }
        }
      }
      else
      {
        switch ( v13 )
        {
          case -2147483647:
            v18 = (char *)sub_422E70(146);
            off_77F3F8(v19, v18);
            break;
          case -2147483564:
            v16 = (char *)sub_422E70(147);
            off_77F3F8(v17, v16);
            break;
          case -2147483563:
            v14 = (char *)sub_422E70(148);
            off_77F3F8(v15, v14);
            break;
          default:
            break;
        }
      }
      break;
    case 0x10u:
      if ( HIWORD(a5) != 0 )
      {
        v12 = sub_422E70(149);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v12, 1);
      }
      break;
    case 0x20u:
      off_77F3FC("SOCKET CLOSE %d", *(uint32_t *)(this + 436));
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      sub_4015C0(&v24, szPassword, 0);
      v6 = *(uint32_t *)(this + 456);
      v29 = 0;
      v7 = 1;
      switch ( v6 )
      {
        case 0:
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 5 )
          {
            sub_406D60(&v24, (char *)szPassword);
            v7 = 0;
          }
          else if ( *(uint32_t *)(dword_8F7A24 + 108) == 0 )
          {
            v8 = (char *)sub_422E70(150);
            goto LABEL_19;
          }
          break;
        case 1:
          v8 = (char *)sub_422E70(151);
          goto LABEL_19;
        case 2:
          v8 = (char *)sub_422E70(152);
          goto LABEL_19;
        case 3:
          v9 = (char *)sub_422E70(153);
          goto LABEL_21;
        case 4:
          v9 = (char *)sub_422E70(154);
          goto LABEL_21;
        case 5:
          v9 = (char *)sub_422E70(155);
          goto LABEL_21;
        case 6:
          v9 = (char *)sub_422E70(156);
          goto LABEL_21;
        case 7:
          v8 = (char *)sub_422E70(157);
          goto LABEL_19;
        case 8:
          v9 = (char *)sub_422E70(158);
          goto LABEL_21;
        case 9:
          v9 = (char *)sub_422E70(159);
          goto LABEL_21;
        case 10:
          v8 = (char *)sub_422E70(160);
LABEL_19:
          sub_406D60(&v24, v8);
          v7 = 2;
          break;
        case 11:
          v9 = (char *)sub_422E70(161);
LABEL_21:
          sub_406D60(&v24, v9);
          break;
        default:
          v10 = (char *)sub_422E70(162);
          sub_4015C0(&v24, v10, strlen(v10));
          break;
      }
      if ( sub_40BF00((std::_String_base *)&v24, 0, v26, szPassword, 0) != 0 )
      {
        p_Block = Block;
        if ( v27 < 0x10 )
          p_Block = &Block;
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)p_Block, v7);
      }
      if ( *(uint32_t *)(this + 436) == 0 )
        sub_46E360(*(uint32_t *)(dword_8F7A24 + 36));
      v29 = -1;
      if ( v27 >= 0x10 )
        j__free(Block);
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      break;
    default:
      break;
  }
  return sub_698CA0(a2, a3, a4, a5);
}


// ------------------------------------------------------------
// 0x4238E0 sub_4238E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4238E0(int *this)
{
  int v2; // esi
  int v3; // esi

  v2 = *(this + 6);
  if ( v2 < sub_699000((int)this) )
    return 0;
  v3 = *(this + 6);
  return v3 - sub_699000((int)this);
}



// ------------------------------------------------------------
// 0x423910 sub_423910
// ------------------------------------------------------------
int /*thiscall*/ sub_423910(uint32_t *this)
{
  *(this + 298) = 0;
  dword_77F6DC = 1065353216;
  dword_8F7BD0 = 0;
  dword_8F7BD4 = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x423930 sub_423930
// ------------------------------------------------------------
int /*thiscall*/ sub_423930(void *this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  int result; // eax

  result = a4;
  if ( a4 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, void *, int, int, int, int, int, int))(*(uint32_t *)a4 + 156))(
             a4,
             a2,
             a3,
             this,
             a5,
             a6,
             a7,
             a8,
             a9,
             a10);
  return result;
}



// ------------------------------------------------------------
// 0x423970 sub_423970
// ------------------------------------------------------------
int /*cdecl*/ sub_423970(int a1, int a2)
{
  int v2; // eax
  int v4; // [esp-8h] [ebp-Ch]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
  return sub_48C0A0(v2, v4, a2);
}



// ------------------------------------------------------------
// 0x4239A0 sub_4239A0
// ------------------------------------------------------------
int /*stdcall*/ sub_4239A0(int a1)
{
  int v1; // eax
  int v3; // [esp-4h] [ebp-Ch]

  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 36))(a1) + 8);
  v1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
  return sub_45E490(v1, v3);
}



// ------------------------------------------------------------
// 0x4239D0 sub_4239D0
// ------------------------------------------------------------
int /*stdcall*/ sub_4239D0(int a1, float a2)
{
  int v3; // eax
  int v5; // [esp-Ch] [ebp-14h]
  int v6; // [esp-8h] [ebp-10h]

  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 36))(a1) + 8);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
  return sub_45E4D0(v3, v5, v6, a2);
}



// ------------------------------------------------------------
// 0x423A20 sub_423A20
// ------------------------------------------------------------
int /*thiscall*/ sub_423A20(int this)
{
  int v1; // edx
  uint32_t *v2; // eax
  int i; // esi

  v1 = 0;
  v2 = (uint32_t *)(this + 39);
  do
  {
    *(uint32_t *)(this + 4 * v1) = 0;
    *(uint8_t *)(this + v1 + 12) = 0;
    for ( i = 2; i != 0; --i )
    {
      *(v2 - 6) = 0;
      *v2++ = 0;
    }
    ++v1;
  }
  while ( v1 < 3 );
  *(uint32_t *)(this + 63) = 0;
  *(uint8_t *)(this + 67) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 84) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint8_t *)(this + 89) = 0;
  *(uint32_t *)(this + 90) = 100;
  *(uint32_t *)(this + 94) = 100;
  return 100;
}



// ------------------------------------------------------------
// 0x423A80 sub_423A80
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_423A80(int a1, int a2, int a3, int a4)
{
  double v4; // st7
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+4h] [ebp-Ch]

  v7 = (float)a2;
  v6 = (float)a1;
  v4 = sub_4049C0(v6, v7, a3, a4);
  return _ftol2(v4);
}



// ------------------------------------------------------------
// 0x423AB0 sub_423AB0
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_423AB0(int a1, int a2, int a3, int a4, char a5)
{
  double v5; // st7
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+4h] [ebp-10h]

  v8 = (float)a2;
  v5 = (double)a1;
  v7 = v5;
  sub_4049F0(v7, v8, a3, a4, a5);
  return _ftol2(v5);
}



// ------------------------------------------------------------
// 0x423AE0 sub_423AE0
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423AE0(int a1, int a2)
{
  return dword_99FB7C == a1 && dword_99FB80 == a2;
}



// ------------------------------------------------------------
// 0x423B10 sub_423B10
// ------------------------------------------------------------
int /*thiscall*/ sub_423B10(uint32_t *this)
{
  if ( sub_456480(this) == -1 )
    return 0;
  else
    return *(this + sub_456480(this) + 4);
}



// ------------------------------------------------------------
// 0x423B30 sub_423B30
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_423B30(uint8_t *this, int a2, int a3, int a4, int a5)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNNumberSet;
  sub_699E20(this);
  sub_699E40(a2, a3, a4, a5);
  return this;
}



// ------------------------------------------------------------
// 0x423B90 nengine__CNNumberSet__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNNumberSet__vmt0(void *Block, char a2)
{
  sub_423BC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x423BC0 sub_423BC0
// ------------------------------------------------------------
int /*thiscall*/ sub_423BC0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_nengine__CNNumberSet;
  result = sub_699EC0();
  *(uint32_t *)this = &vftbl_nengine__IObject;
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x423C10 sub_423C10
// ------------------------------------------------------------
void /*fastcall*/ sub_423C10(int a1, int a2)
{
  int v3; // edx
  int v4; // edx
  uint32_t *v5; // edi
  int v6; // eax
  uint8_t *v7; // ecx
  int v8; // ebx
  int v9; // ebx
  int v10; // edi
  int m; // ebx
  int i; // [esp+Ch] [ebp-Ch]
  int j; // [esp+Ch] [ebp-Ch]
  int k; // [esp+Ch] [ebp-Ch]
  uint32_t *v15; // [esp+10h] [ebp-8h]
  int v16; // [esp+14h] [ebp-4h]

  *(uint32_t *)(a1 + 36) = 0;
  *(uint32_t *)(a1 + 40) = 0;
  *(uint32_t *)(a1 + 44) = 0;
  *(uint8_t *)(a1 + 48) = 0;
  *(uint32_t *)(a1 + 52) = 0;
  *(uint32_t *)(a1 + 84) = -1;
  *(uint32_t *)(a1 + 88) = -1;
  *(uint32_t *)(a1 + 92) = -1;
  *(uint32_t *)(a1 + 96) = -1;
  *(uint32_t *)(a1 + 100) = 4;
  *(uint32_t *)(a1 + 1256) = 1;
  *(uint32_t *)(a1 + 104) = 0;
  *(uint32_t *)(a1 + 108) = 0;
  *(uint32_t *)(a1 + 112) = 0;
  *(uint32_t *)(a1 + 116) = 0;
  sub_41A590(a1 + 120, a2, 0);
  sub_41A590(a1 + 134, v3, 0);
  sub_41A590(a1 + 148, v4, 0);
  *(uint32_t *)(a1 + 192) = 0;
  *(uint32_t *)(a1 + 196) = 0;
  *(uint32_t *)(a1 + 200) = 0;
  *(uint32_t *)(a1 + 204) = 0;
  sub_699070(a1 + 208, 2u);
  *(uint32_t *)(a1 + 240) = 0;
  *(uint32_t *)(a1 + 236) = 0;
  *(uint32_t *)(a1 + 244) = 0;
  v15 = (uint32_t *)(a1 + 376);
  v5 = (uint32_t *)(a1 + 312);
  v16 = a1 + 256;
  for ( i = 2; i != 0; --i )
  {
    *(v5 - 16) = 0;
    sub_699070(v16, 1u);
    *v5 = 0;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    v15 += 3;
    v5[22] = 0;
    v5[38] = 0;
    ++v5;
    v16 += 28;
  }
  *(uint32_t *)(a1 + 556) = 0;
  *(uint32_t *)(a1 + 588) = 0;
  *(uint32_t *)(a1 + 1168) = 0;
  *(uint32_t *)(a1 + 1172) = 0;
  *(uint32_t *)(a1 + 1176) = 0;
  *(uint32_t *)(a1 + 1180) = -1;
  *(uint32_t *)(a1 + 1184) = -1;
  *(uint32_t *)(a1 + 1188) = -1;
  *(uint32_t *)(a1 + 1192) = 0;
  sub_699070(a1 + 1196, 2u);
  *(uint32_t *)(a1 + 1224) = 0;
  *(uint32_t *)(a1 + 1228) = 0;
  *(uint32_t *)(a1 + 1240) = 0;
  *(uint32_t *)(a1 + 1236) = 0;
  *(uint32_t *)(a1 + 1244) = 0;
  *(uint32_t *)(a1 + 1248) = 0;
  *(uint32_t *)(a1 + 840) = -1;
  *(uint32_t *)(a1 + 932) = 0;
  *(uint32_t *)(a1 + 728) = 0;
  *(uint32_t *)(a1 + 724) = 0;
  *(uint8_t *)(a1 + 721) = 0;
  *(uint8_t *)(a1 + 677) = 0;
  *(uint8_t *)(a1 + 678) = 0;
  *(uint32_t *)(a1 + 832) = 0;
  *(uint32_t *)(a1 + 828) = 0;
  *(uint8_t *)(a1 + 824) = 0;
  *(uint8_t *)(a1 + 809) = 0;
  *(uint8_t *)(a1 + 810) = 0;
  *(uint32_t *)(a1 + 836) = 0;
  v6 = 0;
  v7 = (uint8_t *)(a1 + 950);
  do
  {
    *(v7 - 1) = 0;
    *v7 = 0;
    *(uint8_t *)(a1 + v6++ + 1160) = 0;
    v7 += 28;
  }
  while ( v6 < 8 );
  *(uint32_t *)(a1 + 900) = 0;
  *(uint8_t *)(a1 + 720) = 0;
  *(uint32_t *)(a1 + 592) = 0;
  *(uint8_t *)(a1 + 609) = 0;
  *(uint8_t *)(a1 + 610) = 0;
  *(uint32_t *)(a1 + 624) = 0;
  *(uint32_t *)(a1 + 628) = 0;
  *(uint8_t *)(a1 + 645) = 0;
  *(uint8_t *)(a1 + 646) = 0;
  *(uint32_t *)(a1 + 660) = 0;
  *(uint32_t *)(a1 + 1252) = 8;
  *(uint32_t *)(a1 + 1316) = 0;
  *(uint32_t *)(a1 + 1320) = 0;
  *(uint32_t *)(a1 + 1324) = 0;
  *(uint32_t *)(a1 + 788) = 0;
  *(uint32_t *)(a1 + 792) = 0;
  *(uint8_t *)(a1 + 773) = 0;
  *(uint8_t *)(a1 + 774) = 0;
  *(uint32_t *)(a1 + 752) = 0;
  *(uint32_t *)(a1 + 1356) = 1065353216;
  *(uint32_t *)(a1 + 1360) = 1065353216;
  *(uint32_t *)(a1 + 1364) = 1065353216;
  sub_699070(a1 + 164, 3u);
  sub_699070(a1 + 56, 3u);
  v8 = a1 + 320;
  for ( j = 2; j != 0; --j )
  {
    sub_699070(v8, 3u);
    v8 += 28;
  }
  v9 = a1 + 408;
  for ( k = 2; k != 0; --k )
  {
    sub_699070(v9, 3u);
    v9 += 28;
  }
  sub_699070(a1 + 472, 3u);
  sub_699070(a1 + 500, 3u);
  sub_699070(a1 + 528, 3u);
  sub_699070(a1 + 560, 3u);
  sub_699070(a1 + 596, 3u);
  sub_699070(a1 + 632, 3u);
  sub_699070(a1 + 664, 3u);
  sub_699070(a1 + 692, 3u);
  sub_699070(a1 + 760, 3u);
  sub_699070(a1 + 796, 3u);
  sub_699070(a1 + 844, 3u);
  sub_699070(a1 + 872, 3u);
  sub_699070(a1 + 904, 3u);
  v10 = a1 + 936;
  for ( m = 8; m != 0; --m )
  {
    sub_699070(v10, 3u);
    v10 += 28;
  }
  sub_699070(a1 + 1260, 3u);
  sub_699070(a1 + 1288, 3u);
  sub_699070(a1 + 1328, 3u);
}


// ------------------------------------------------------------
// 0x423FD0 sub_423FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_423FD0(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  uint32_t *v11; // esi
  int j; // ebx
  int result; // eax
  int (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-8h]
  uint32_t *v16; // [esp+Ch] [ebp-4h]

  v2 = *(this + 11);
  if ( v2 != 0 )
    *(uint32_t *)(v2 + 392) = 0;
  v3 = *(this + 26);
  if ( v3 != 0 )
    *(uint32_t *)(v3 + 132) = 0;
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  *(this + 27) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 147);
  *(this + 10) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 156);
  *(this + 147) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 165);
  *(this + 156) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 197);
  *(this + 165) = 0;
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  v10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 198);
  *(this + 197) = 0;
  if ( v10 != nullptr )
    (**v10)(v10, 1);
  *(this + 198) = 0;
  v16 = this + 116;
  v11 = this + 94;
  for ( i = 2; i != 0; --i )
  {
    for ( j = 3; j != 0; --j )
    {
      if ( *v11 != 0 )
        (**(void (/*thiscall*/ ***)(uint32_t, int))*v11)(*v11, 1);
      *v11++ = 0;
    }
    if ( *v16 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v16)(*v16, 1);
    *v16 = 0;
    result = (int)++v16;
  }
  v14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 209);
  if ( v14 != nullptr )
    result = (**v14)(v14, 1);
  *(this + 209) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x424100 sub_424100
// ------------------------------------------------------------
int /*thiscall*/ sub_424100(uint32_t *this, int a2)
{
  int result; // eax

  result = a2;
  *(this + 26) = a2;
  if ( a2 != 0 )
    *(uint32_t *)(a2 + 132) = this;
  return result;
}



// ------------------------------------------------------------
// 0x424120 sub_424120
// ------------------------------------------------------------
int /*thiscall*/ sub_424120(uint32_t *this, int a2, int a3)
{
  uint32_t *v4; // ecx
  int result; // eax

  v4 = this + 52;
  *(this + 50) = a2;
  *(this + 51) = a3;
  *((uint8_t *)v4 + 13) = 0;
  *((uint8_t *)v4 + 14) = 0;
  result = sub_698F90(0, 0);
  if ( a2 == 0 )
  {
    *(this + 59) = 0;
    *(this + 60) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x424170 sub_424170
// ------------------------------------------------------------
int /*thiscall*/ sub_424170(uint32_t *this)
{
  int result; // eax
  int v3; // eax

  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 3 || result == 4 || result == 6 )
  {
    if ( dword_8F7C04 == 0 || (result = *((uint32_t *)dword_8F8528 + 1)) != 0 )
    {
      *(this + 61) = 0;
    }
    else
    {
      v3 = (*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 128))() / 5;
      if ( v3 > 35 )
        v3 = 35;
      result = v3 - 35;
      *(this + 61) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4241E0 sub_4241E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4241E0(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v2 = *(uint32_t *)(this + 200);
  if ( v2 != 0 && *(uint32_t *)(this + 1224) == 0 )
  {
    v3 = 2 * v2;
    v4 = v3 + 1;
    v5 = v3 / 2;
    *(uint32_t *)(this + 236) = rand() % (v3 + 1) - v3 / 2;
    *(uint32_t *)(this + 240) = rand() % v4 - v5;
    v2 = sub_699000(this + 208);
    if ( v2 >= *(uint32_t *)(this + 204) )
    {
      *(uint32_t *)(this + 200) = 0;
      *(uint32_t *)(this + 204) = 0;
      *(uint8_t *)(this + 221) = 0;
      *(uint8_t *)(this + 222) = 0;
      LOBYTE(v2) = sub_698F90(this + 208, 0, 0);
      *(uint32_t *)(this + 236) = 0;
      *(uint32_t *)(this + 240) = 0;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x424270 sub_424270
// ------------------------------------------------------------
int /*thiscall*/ sub_424270(int this, int a2, int a3)
{
  int v5; // eax
  int v7; // [esp-4h] [ebp-10h]

  v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 36))(a2) + 8);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  *(uint32_t *)(this + 732) = sub_45E490(v5, v7) - 50;
  *(uint32_t *)(this + 736) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) - 32;
  *(uint32_t *)(this + 740) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2);
  *(uint32_t *)(this + 752) = a3;
  *(uint8_t *)(this + 773) = 0;
  *(uint8_t *)(this + 774) = 0;
  sub_698F90(this + 760, 1500, 0);
  *(uint32_t *)(this + 744) = 0;
  *(uint32_t *)(this + 748) = 1065353216;
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
}



// ------------------------------------------------------------
// 0x424310 sub_424310
// ------------------------------------------------------------
int /*thiscall*/ sub_424310(uint32_t *this, uint8_t *a2)
{
  int v2; // ebx
  uint8_t *v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int i; // ebx
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v12; // eax
  int v13; // esi
  int v14; // ecx
  int v15; // edi
  int v16; // edi
  int v17; // eax
  int v18; // ecx
  int v19; // [esp+Ch] [ebp-8h]
  int v20; // [esp+10h] [ebp-4h]
  int v21; // [esp+1Ch] [ebp+8h]

  v2 = 0;
  if ( *(this + 26) == 0 )
    return 0;
  v3 = a2;
  if ( a2 == nullptr )
    return 0;
  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v4 == 3 )
  {
    if ( (uint8_t)sub_45E680(a2) == 0 )
    {
      v5 = sub_423B10(dword_8F850C);
      if ( v5 == 0 || (v3 = *(uint8_t **)(v5 + 196)) == nullptr || (uint8_t)sub_45E680(*(uint32_t *)(v5 + 196)) == 0 )
      {
        v21 = 0;
        v6 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v8 = *(uint32_t *)(i + dword_8F850C);
          if ( v8 != 0 )
          {
            v9 = *(uint32_t *)(v8 + 196);
            if ( v9 != 0 && (uint8_t)sub_45E680(*(uint32_t *)(v8 + 196)) != 0 )
            {
              v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 1032))(v9) + 48);
              if ( v6 == 0 || v10 > v21 )
              {
                v6 = v9;
                v21 = v10;
              }
            }
          }
        }
        return v6;
      }
    }
    return (int)v3;
  }
  if ( v4 != 4 && v4 != 6 )
  {
    if ( v4 == 1 )
      return dword_8F7C08;
    return 0;
  }
  if ( dword_8F7C04 == 0 )
    return 0;
  if ( v4 == 4 && dword_99FEC0 != 0 )
  {
    v20 = dword_99FEC0 + 4;
  }
  else
  {
    if ( v4 != 6 || dword_99FF08 == 0 )
      return 0;
    v20 = dword_99FF08 + 4;
  }
  if ( v20 == 0 )
    return 0;
  if ( *(uint8_t *)(dword_8F7C04 + 8052) != 0 || a2[8052] != 0 )
    return *(this + 13);
  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a2 + 1196))(a2) == 0 )
    return (int)v3;
  while ( 1 )
  {
    v12 = sub_48F660(v2);
    v13 = v12;
    if ( v12 != 0 )
    {
      v14 = *(uint32_t *)(v12 + 196);
      if ( v14 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 1196))(v14) == 0 )
      {
        v15 = *(uint32_t *)(v13 + 196);
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a2 + 376))(a2);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 376))(v15) == v19 )
          break;
      }
    }
    if ( ++v2 >= 8 )
    {
      v16 = 0;
      while ( 1 )
      {
        v17 = sub_48F660(v16);
        v13 = v17;
        if ( v17 != 0 )
        {
          v18 = *(uint32_t *)(v17 + 196);
          if ( v18 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 1196))(v18) == 0 )
            break;
        }
        if ( ++v16 >= 8 )
          return 0;
      }
      return *(uint32_t *)(v13 + 196);
    }
  }
  return *(uint32_t *)(v13 + 196);
}


// ------------------------------------------------------------
// 0x424530 sub_424530
// ------------------------------------------------------------
char /*thiscall*/ sub_424530(int this, float a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
  int v9; // eax
  double v10; // st7
  long double v11; // st7

  v9 = sub_48B740(2);
  if ( v9 != 0 )
  {
    if ( a8 != 0 && (v9 = *(uint32_t *)(this + 1192)) != 0 )
    {
      if ( v9 == 1 )
      {
        v9 = *(uint32_t *)(this + 1176);
        if ( v9 <= a4 )
          v9 = a4;
        *(uint32_t *)(this + 1176) = v9;
      }
      else if ( v9 == 2 )
      {
        v9 = sub_4238E0(this + 1196);
        if ( a4 > v9 )
        {
          *(uint32_t *)(this + 1176) = a4;
          *(uint8_t *)(this + 1209) = 0;
          *(uint8_t *)(this + 1210) = 0;
          LOBYTE(v9) = sub_698F90(this + 1196, *(uint32_t *)(this + 1176), 0);
        }
      }
    }
    else
    {
      v10 = *(float *)&dword_77F6DC;
      *(float *)(this + 1168) = a2;
      *(uint32_t *)(this + 1172) = a3;
      *(uint32_t *)(this + 1176) = a4;
      if ( a8 != 0 )
        v11 = fabs(v10 - 1.0);
      else
        v11 = fabs(a2 - v10);
      *(uint32_t *)(this + 1192) = 2 * (a8 == 0) + 1;
      *(uint8_t *)(this + 1209) = 0;
      *(uint8_t *)(this + 1210) = 0;
      sub_698F90(this + 1196, *(uint32_t *)(this + 1172), (uint64_t)((double)a3 * v11 / (a2 - 1.0)));
      *(uint32_t *)(this + 1180) = a5;
      *(uint32_t *)(this + 1184) = a6;
      *(uint32_t *)(this + 1188) = a7;
      LOBYTE(v9) = a5;
    }
  }
  else
  {
    *(uint32_t *)(this + 1192) = 0;
    dword_8F7BD0 = 0;
    dword_8F7BD4 = 0;
    dword_77F6DC = 1065353216;
  }
  return v9;
}



// ------------------------------------------------------------
// 0x424680 sub_424680
// ------------------------------------------------------------
int /*cdecl*/ sub_424680(int *a1, int *a2, float a3, float a4)
{
  uint64_t v4; // rax
  double v5; // st7
  double v6; // st6
  float v8; // [esp+14h] [ebp+10h]

  if ( a3 == 0.0 && a4 == 0.0 )
  {
    *a1 = dword_8F7BD0 + (uint64_t)((double)(*a1 - dword_8F7BD0) * *(float *)&dword_77F6DC);
    LODWORD(v4) = dword_8F7BD4 + (uint64_t)((double)(*a2 - dword_8F7BD4) * *(float *)&dword_77F6DC);
    *a2 = v4;
  }
  else
  {
    v5 = (double)*a1;
    v6 = a3 + v5;
    v8 = ((double)*a2 + a4 - (double)dword_8F7BD4) * *(float *)&dword_77F6DC + (double)dword_8F7BD4 - ((double)*a2 + a4);
    *a1 = (uint64_t)((v6 - (double)dword_8F7BD0) * *(float *)&dword_77F6DC + (double)dword_8F7BD0 - v6 + v5);
    v4 = (uint64_t)((double)*a2 + v8);
    *a2 = v4;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x424760 sub_424760
// ------------------------------------------------------------
void /*cdecl*/ sub_424760(int a1, int a2, int a3, int a4, float a5, int a6, float a7, int a8, float a9, float a10)
{
  bool v10; // bl
  double v11; // st7
  bool v12; // c0
  float v13; // esi
  float v14; // edi
  double v15; // st7
  bool v16; // c0
  float v17; // [esp+0h] [ebp-30h]
  float v18; // [esp+4h] [ebp-2Ch]
  float v19; // [esp+28h] [ebp-8h]
  float v20; // [esp+28h] [ebp-8h]
  float v21; // [esp+28h] [ebp-8h]
  float v22; // [esp+28h] [ebp-8h]
  float v23; // [esp+2Ch] [ebp-4h]
  float v24; // [esp+2Ch] [ebp-4h]

  v10 = *(uint32_t *)(dword_8F7A24 + 12) == 1 || a7 == 0.0;
  if ( *(float *)&dword_77F6DC == 1.0 )
  {
    if ( !v10 )
      goto LABEL_13;
    v19 = (double)*(int *)(a4 + 28) - a9;
    v23 = (float)a2;
    v11 = v19 * a5 + v23 + a9;
    v20 = ((double)*(unsigned int *)(a4 + 20) + v19) * a5 + v23 + a9;
    if ( a5 < 0.0 )
    {
      if ( v20 >= 640.0 )
        return;
      v12 = v11 < 0.0;
    }
    else
    {
      if ( v11 >= 640.0 )
        return;
      v12 = v20 < 0.0;
    }
    if ( !v12 )
    {
LABEL_13:
      if ( a4 != 0 )
        (*(void (/*stdcall*/ **)(int, int, int, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)a4 + 156))(
          a2,
          a3,
          a1,
          LODWORD(a5),
          a6,
          LODWORD(a7),
          a8,
          LODWORD(a9),
          LODWORD(a10));
    }
  }
  else
  {
    v13 = a10;
    v14 = a9;
    sub_424680((int)&a2, (int)&a3, a9, a10);
    if ( !v10 )
      goto LABEL_22;
    v21 = (double)*(int *)(a4 + 28) - a9;
    v24 = (float)a2;
    v15 = v21 * *(float *)&dword_77F6DC * a5 + v24 + a9;
    v22 = ((double)*(unsigned int *)(a4 + 20) + v21) * *(float *)&dword_77F6DC * a5 + v24 + a9;
    if ( a5 < 0.0 )
    {
      if ( v22 >= 640.0 )
        return;
      v16 = v15 < 0.0;
    }
    else
    {
      if ( v15 >= 640.0 )
        return;
      v16 = v22 < 0.0;
    }
    if ( !v16 )
    {
LABEL_22:
      if ( a4 != 0 )
      {
        v18 = *(float *)&dword_77F6DC * *(float *)&a6;
        v17 = *(float *)&dword_77F6DC * a5;
        (*(void (/*stdcall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int, float, float))(*(uint32_t *)a4 + 156))(
          a2,
          a3,
          a1,
          LODWORD(v17),
          LODWORD(v18),
          LODWORD(a7),
          a8,
          COERCE_FLOAT(LODWORD(v14)),
          COERCE_FLOAT(LODWORD(v13)));
      }
    }
  }
}



// ------------------------------------------------------------
// 0x424980 sub_424980
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_424980(uint32_t *a1, int a2, int a3, int a4, int a5)
{
  int v5; // eax
  int v6; // ecx
  bool v7; // bl
  int v8; // esi
  int v9; // edi
  int v10; // edx
  int v11; // ecx
  int v12; // esi
  int v13; // edi
  bool v15; // [esp+Bh] [ebp-1h]

  if ( *(float *)&dword_77F6DC == 1.0 )
  {
    v13 = a5;
    v12 = a4;
    v11 = a3;
    v10 = a2;
  }
  else
  {
    v5 = a4;
    v6 = a5;
    v7 = a2 == 0;
    v15 = a3 == 0;
    HIBYTE(a4) = a4 == 640;
    HIBYTE(a5) = a5 == 480;
    v8 = v5 - a2;
    v9 = v6 - a3;
    sub_424680(&a2, &a3, 0.0, 0.0);
    v10 = a2;
    v11 = a3;
    v12 = a2 + v8;
    v13 = a3 + v9;
    if ( v7 )
      v10 = 0;
    if ( v15 )
      v11 = 0;
    if ( HIBYTE(a4) != 0 )
      v12 = 640;
    if ( HIBYTE(a5) != 0 )
      v13 = 480;
  }
  a1[15] = v13;
  a1[14] = v12;
  a1[12] = v10;
  a1[13] = v11;
  return a1;
}



// ------------------------------------------------------------
// 0x424A40 sub_424A40
// ------------------------------------------------------------
int /*thiscall*/ sub_424A40(uint32_t *this, int a2)
{
  int result; // eax

  result = a2;
  *(this + 13) = a2;
  if ( *(this + 11) != 0 && a2 != 0 )
    return sub_48C500(a2);
  return result;
}



// ------------------------------------------------------------
// 0x424A60 sub_424A60
// ------------------------------------------------------------
void /*thiscall*/ sub_424A60(uint32_t *this)
{
  int v1; // eax

  if ( *(this + 314) == 2 )
  {
    v1 = sub_699000((int)(this + 315));
    sub_69A110(285, 220, 5 - v1 / 1000, -1);
  }
}



// ------------------------------------------------------------
// 0x424AB0 sub_424AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_424AB0(int this, int a2, int a3)
{
  uint64_t v4; // rax
  DWORD TickCount; // eax
  double v6; // st7

  LODWORD(v4) = *(uint32_t *)(this + 1236);
  if ( (uint32_t)v4 == 0 )
  {
    LODWORD(v4) = GetTickCount() - *(uint32_t *)(this + 1240);
    if ( (unsigned int)v4 >= 0x3E8 )
    {
      TickCount = GetTickCount();
      v6 = (double)a3;
      *(uint32_t *)(this + 1236) = TickCount;
      *(uint32_t *)(this + 1240) = TickCount;
      *(float *)(this + 1364) = 0.0099999998 * v6;
      *(uint32_t *)(this + 1244) = a2 + TickCount;
      *(float *)(this + 1360) = 0.0099999998 * v6;
      *(uint32_t *)(this + 1248) = a3;
      dword_79D0C4 = (uint64_t)(v6 * *(float *)(this + 1356));
      v4 = (uint64_t)(v6 * *(float *)(this + 1356));
      dword_79D0C8 = v4;
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x424B40 sub_424B40
// ------------------------------------------------------------
int /*thiscall*/ sub_424B40(int this)
{
  uint64_t v2; // rax
  double v3; // st7

  LODWORD(v2) = *(uint32_t *)(this + 1236);
  if ( (uint32_t)v2 != 0 )
  {
    LODWORD(v2) = GetTickCount() - *(uint32_t *)(this + 1236);
    if ( (unsigned int)v2 >= 0xFA )
    {
      v3 = *(float *)(this + 1356) * 100.0;
      *(uint32_t *)(this + 1236) = 0;
      *(uint32_t *)(this + 1364) = 1065353216;
      *(uint32_t *)(this + 1360) = 1065353216;
      dword_79D0C4 = (uint64_t)v3;
      v2 = (uint64_t)(*(float *)(this + 1356) * 100.0);
      dword_79D0C8 = v2;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x424BB0 sub_424BB0
// ------------------------------------------------------------
char /*thiscall*/ sub_424BB0(int this, int a2, int a3, char a4)
{
  DWORD TickCount; // eax
  double v6; // st7
  char result; // al

  TickCount = GetTickCount();
  v6 = *(float *)(this + 1356) * 5.0;
  *(uint32_t *)(this + 1224) = TickCount;
  *(uint32_t *)(this + 1228) = a2 + TickCount;
  *(uint32_t *)(this + 1232) = a3;
  *(uint32_t *)(this + 1364) = 1028443341;
  *(uint32_t *)(this + 1360) = 1028443341;
  dword_79D0C4 = (uint64_t)v6;
  dword_79D0C8 = (uint64_t)(*(float *)(this + 1356) * 5.0);
  result = a4;
  if ( a4 != 0 )
    return sub_424530(*(uint32_t *)(*(uint32_t *)(this + 104) + 132), 1.2, 100, 150, -1, -1, -1, 1);
  return result;
}



// ------------------------------------------------------------
// 0x424C50 sub_424C50
// ------------------------------------------------------------
int /*thiscall*/ sub_424C50(int this)
{
  uint64_t v2; // rax
  double v3; // st7
  double v4; // st7
  double v5; // st7

  LODWORD(v2) = *(uint32_t *)(this + 1224);
  if ( (uint32_t)v2 != 0 )
  {
    LODWORD(v2) = GetTickCount() - *(uint32_t *)(this + 1224);
    if ( (unsigned int)v2 >= 0xBB8 )
    {
      if ( (unsigned int)v2 >= 0x157C )
      {
        if ( (unsigned int)v2 >= 0x15E0 )
        {
          v5 = *(float *)(this + 1356) * 100.0;
          *(uint32_t *)(this + 1224) = 0;
          *(uint32_t *)(this + 1364) = 1065353216;
          *(uint32_t *)(this + 1360) = 1065353216;
          dword_79D0C4 = (uint64_t)v5;
          v2 = (uint64_t)(*(float *)(this + 1356) * 100.0);
        }
        else
        {
          v4 = (double)(int)sub_423A80(*(uint32_t *)(this + 1232), 100, v2, 5600);
          *(float *)(this + 1364) = 0.0099999998 * v4;
          *(float *)(this + 1360) = 0.0099999998 * v4;
          dword_79D0C4 = (uint64_t)(v4 * *(float *)(this + 1356));
          v2 = (uint64_t)(v4 * *(float *)(this + 1356));
        }
        dword_79D0C8 = v2;
      }
      else
      {
        v3 = (double)*(int *)(this + 1232);
        *(float *)(this + 1364) = 0.0099999998 * v3;
        *(float *)(this + 1360) = 0.0099999998 * v3;
        dword_79D0C4 = (uint64_t)(v3 * *(float *)(this + 1356));
        v2 = (uint64_t)((double)*(int *)(this + 1232) * *(float *)(this + 1356));
        dword_79D0C8 = v2;
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x424D80 sub_424D80
// ------------------------------------------------------------
char /*thiscall*/ sub_424D80(uint8_t *this, int a2)
{
  int v3; // ecx
  char result; // al

  v3 = (int)(this + 28 * a2 + 936);
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  result = sub_698F90(v3, 500, 0);
  *(this + a2 + 1160) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x424DC0 sub_424DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_424DC0(uint32_t *this)
{
  int v1; // eax
  int v3; // esi
  int v4; // eax
  int v5; // [esp-Ch] [ebp-Ch]

  v1 = *(this + 295);
  if ( v1 != -1 )
    return sub_45E490(v1, 1);
  v3 = *(this + 13);
  if ( v3 == 0 )
    return 320;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 36))(v3) + 8);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
  return sub_45E490(v4, v5);
}



// ------------------------------------------------------------
// 0x424E10 sub_424E10
// ------------------------------------------------------------
int /*thiscall*/ sub_424E10(int *this)
{
  int v1; // edx
  int v2; // eax
  int v4; // esi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // [esp-18h] [ebp-18h]
  int v9; // [esp-14h] [ebp-14h]

  v1 = *(this + 296);
  if ( v1 != -1 )
  {
    v2 = *(this + 297);
    if ( v2 != -1 )
      return sub_45E4D0(v1, v2, 1, 1.0);
  }
  v4 = *(this + 13);
  if ( v4 == 0 )
    return 240;
  v5 = *(this + 13);
  v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 36))(v4) + 8);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
  v7 = sub_45E4D0(v6, v8, v9, 1.0);
  return v7 - 2 * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 192))(v4) / 3;
}



// ------------------------------------------------------------
// 0x424EA0 sub_424EA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_424EA0(float *this, float a2)
{
  uint64_t result; // rax

  *(this + 339) = a2;
  dword_79D0CC = (uint64_t)(a2 * 100.0);
  dword_79D0C4 = (uint64_t)(*(this + 340) * *(this + 339) * 100.0);
  result = (uint64_t)(*(this + 341) * *(this + 339) * 100.0);
  dword_79D0C8 = result;
  return result;
}



// ------------------------------------------------------------
// 0x424F00 sub_424F00
// ------------------------------------------------------------
int /*thiscall*/ sub_424F00(int this)
{
  int v2; // ebx
  int v3; // edi
  int result; // eax
  long double v5; // st7
  int v6; // [esp+Ch] [ebp-10h]
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  float v9; // [esp+18h] [ebp-4h]

  v2 = *(uint32_t *)(this + 1184);
  v3 = *(uint32_t *)(this + 1188);
  v6 = *(uint32_t *)(this + 1180);
  v7 = *(uint32_t *)(this + 1176);
  v8 = *(uint32_t *)(this + 1172);
  v9 = *(float *)(this + 1168);
  result = sub_48B740(2);
  if ( result != 0 )
  {
    v5 = v9 - *(float *)&dword_77F6DC;
    *(float *)(this + 1168) = v9;
    *(uint32_t *)(this + 1172) = v8;
    *(uint32_t *)(this + 1176) = v7;
    *(uint32_t *)(this + 1192) = 3;
    *(uint8_t *)(this + 1209) = 0;
    *(uint8_t *)(this + 1210) = 0;
    sub_698F90(this + 1196, *(uint32_t *)(this + 1172), (uint64_t)(fabs(v5) * (double)v8 / (v9 - 1.0)));
    *(uint32_t *)(this + 1188) = v3;
    *(uint32_t *)(this + 1184) = v2;
    *(uint32_t *)(this + 1180) = v6;
    return v6;
  }
  else
  {
    *(uint32_t *)(this + 1192) = 0;
    dword_77F6DC = 1065353216;
    dword_8F7BD0 = 0;
    dword_8F7BD4 = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x424FF0 sub_424FF0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_424FF0(uint32_t *this)
{
  int v1; // edx
  int v3; // edx
  unsigned int v4; // eax
  int v5; // edx

  v1 = *(this + 91);
  if ( v1 == 0 || (*(this + 92) - v1) >> 5 == 0 )
    return 0;
  v3 = *(this + 95);
  if ( v3 != 0 )
    v4 = (*(this + 96) - v3) >> 5;
  else
    v4 = 0;
  v5 = *(this + 91);
  if ( v5 != 0 )
    return v4 / ((*(this + 92) - v5) >> 5);
  else
    return v4 / 0;
}



// ------------------------------------------------------------
// 0x425050 sub_425050
// ------------------------------------------------------------
int /*thiscall*/ sub_425050(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 91);
  if ( v1 != 0 )
    return 224 * ((*(this + 92) - v1) >> 5);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425080 sub_425080
// ------------------------------------------------------------
int /*thiscall*/ sub_425080(uint32_t *this)
{
  int v1; // edx
  int v2; // eax
  int v3; // edx

  v1 = *(this + 91);
  if ( v1 != 0 )
    v2 = (*(this + 92) - v1) >> 5;
  else
    v2 = 0;
  if ( 224 * v2 - 640 <= 0 )
    return 0;
  v3 = *(this + 91);
  if ( v3 != 0 )
    return 224 * ((*(this + 92) - v3) >> 5) - 640;
  else
    return -640;
}



// ------------------------------------------------------------
// 0x4250E0 sub_4250E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4250E0(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 2);
  if ( v1 != 0 )
    return (*(this + 3) - v1) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425100 sub_425100
// ------------------------------------------------------------
int /*thiscall*/ sub_425100(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 30);
  if ( v1 != 0 )
    return (*(this + 31) - v1) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425120 sub_425120
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_425120(uint32_t *this)
{
  *this = &vftbl_CNRDParticleCreater;
  sub_423A20((int)(this + 1));
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
  *(this + 44) = &vftbl_nengine__CNTimer;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 1;
  *((uint8_t *)this + 190) = 0;
  *((uint8_t *)this + 189) = 0;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *(this + 48) = 0;
  sub_4902C0(this);
  sub_490BD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x425210 CNRDParticleCreater__vmt14
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt14(uint32_t *this, int a2)
{
  return sub_490460(a2, (int)(this + 1), this + 26);
}



// ------------------------------------------------------------
// 0x425230 CNRDParticleCreater__vmt20
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt20(int this, const void *a2)
{
  qmemcpy((void *)(this + 104), a2, 0x48u);
}



// ------------------------------------------------------------
// 0x425260 CNRDParticleCreater__vmt28
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt28(uint32_t *this, int a2, int a3, int a4)
{
  *(this + 1) = a2;
  *(this + 2) = a3;
  *(this + 3) = a4;
  return a4;
}



// ------------------------------------------------------------
// 0x4252A0 CNRDParticleCreater__vmt40
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticleCreater__vmt40(uint8_t *this, char a2)
{
  *(this + 216) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4252B0 CNRDParticleCreater__vmt44
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticleCreater__vmt44(uint8_t *this)
{
  return *(this + 216);
}



// ------------------------------------------------------------
// 0x4252D0 CNRDParticleCreater__vmt54
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt54(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + 58);
  if ( v2 == -1 )
    return a2;
  else
    return a2 * *(this + v2 + 40) / 100;
}



// ------------------------------------------------------------
// 0x425310 CNRDParticleCreater__vmt50
// ------------------------------------------------------------
double /*thiscall*/ CNRDParticleCreater__vmt50(uint32_t *this, float a2)
{
  int v2; // eax

  v2 = *(this + 58);
  if ( v2 == -1 )
    return a2;
  else
    return (double)(int)*(this + v2 + 40) * a2 * 0.0099999998;
}



// ------------------------------------------------------------
// 0x425340 CNRDParticleCreater__vmt58
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt58(void *this, unsigned int a2)
{
  sub_699070((int)this + 176, a2);
}



// ------------------------------------------------------------
// 0x425350 sub_425350
// ------------------------------------------------------------
void /*thiscall*/ sub_425350(uint32_t *this)
{
  *this = &vftbl_CNRDParticleCreater;
  nullsub_3();
  *(this + 44) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 180) = 0;
}



// ------------------------------------------------------------
// 0x4253B0 CNRDParticleCreater__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDParticleCreater__vmt0(uint32_t *Block, char a2)
{
  sub_425350(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4253E0 sub_4253E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4253E0(int this)
{
  int v2; // ecx

  v2 = this + 208;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 0, 0);
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  dword_77F6DC = 1065353216;
  dword_8F7BD0 = 0;
  dword_8F7BD4 = 0;
  *(uint32_t *)(this + 84) = -1;
  *(uint32_t *)(this + 88) = -1;
  *(uint32_t *)(this + 92) = -1;
  *(uint32_t *)(this + 96) = -1;
  *(uint32_t *)(this + 100) = 4;
  *(uint32_t *)(this + 1256) = 1;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  return sub_698F90(this + 56, 0, 0);
}



// ------------------------------------------------------------
// 0x425460 sub_425460
// ------------------------------------------------------------
int /*fastcall*/ sub_425460(int a1, int a2)
{
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int result; // eax
  int v7; // ecx

  sub_41A590(a1 + 120, a2, 0);
  sub_41A590(a1 + 134, v3, 0);
  sub_41A590(a1 + 148, v4, 0);
  *(uint8_t *)(a1 + 177) = 0;
  *(uint8_t *)(a1 + 178) = 0;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(uint32_t *)(a1 + 108) != 0 )
    sub_472B30(1, 0);
  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  result = dword_8F7C04;
  if ( v5 != 4 && v5 != 6 || dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
  {
    v7 = *(uint32_t *)(a1 + 44);
    *(uint32_t *)(a1 + 52) = dword_8F7C04;
    if ( v7 != 0 && result != 0 )
      result = sub_48C500(result);
  }
  *(uint32_t *)(a1 + 1320) = 0;
  *(uint32_t *)(a1 + 1324) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x425500 sub_425500
// ------------------------------------------------------------
char /*thiscall*/ sub_425500(int this, int a2)
{
  int v3; // eax
  int v4; // eax

  sub_65DC70(lpCriticalSection);
  v3 = *(uint32_t *)(this + 44);
  if ( v3 != 0 )
    *(uint32_t *)(v3 + 392) = 0;
  *(uint32_t *)(this + 44) = a2;
  if ( a2 != 0 )
    *(uint32_t *)(a2 + 392) = this;
  *(uint8_t *)(this + 48) = 0;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == this )
  {
    v4 = *(uint32_t *)(this + 44);
    if ( v4 != 0 )
      dword_9A012C = *(uint32_t *)(v4 + 356);
  }
  return sub_4253E0(this);
}



// ------------------------------------------------------------
// 0x425570 sub_425570
// ------------------------------------------------------------
char /*thiscall*/ sub_425570(int this)
{
  int v2; // eax
  uint32_t *v3; // ecx
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  uint64_t v17; // rax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // edi
  int v25; // ebx
  float v27; // [esp+0h] [ebp-34h]
  float v28; // [esp+0h] [ebp-34h]
  float v29; // [esp+4h] [ebp-30h]
  float v30; // [esp+4h] [ebp-30h]
  int v31; // [esp+Ch] [ebp-28h]
  int v32; // [esp+Ch] [ebp-28h]
  int v33; // [esp+Ch] [ebp-28h]
  int v34; // [esp+Ch] [ebp-28h]
  int v35; // [esp+1Ch] [ebp-18h]
  int v36; // [esp+1Ch] [ebp-18h]
  int v37; // [esp+20h] [ebp-14h]
  int v38; // [esp+20h] [ebp-14h]
  int v39; // [esp+24h] [ebp-10h]
  float v40; // [esp+28h] [ebp-Ch]
  int v41; // [esp+2Ch] [ebp-8h]
  int v42; // [esp+2Ch] [ebp-8h]
  int v43; // [esp+2Ch] [ebp-8h]
  int v44; // [esp+30h] [ebp-4h]
  int v45; // [esp+30h] [ebp-4h]
  int v46; // [esp+30h] [ebp-4h]

  v2 = *(uint32_t *)(this + 1192);
  if ( v2 == 0 )
    return v2;
  v3 = *(uint32_t **)(this + 44);
  if ( v3 == nullptr )
    return v2;
  v40 = 1.0;
  v4 = 0;
  v5 = 0;
  v6 = sub_48C1C0(v3, 1);
  v7 = *(uint32_t *)(this + 1180);
  v39 = v6;
  if ( v7 == -1 )
  {
    v8 = *(uint32_t *)(this + 52);
    if ( v8 != 0 )
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 120))(v8) - 320;
    v41 = v6;
  }
  else
  {
    v41 = v7 - 320;
  }
  v9 = *(uint32_t *)(this + 1184);
  v37 = *(uint32_t *)(*(uint32_t *)(this + 44) + 468);
  if ( v9 == -1 || (v10 = *(uint32_t *)(this + 1188)) == -1 )
  {
    v11 = *(uint32_t *)(this + 52);
    if ( v11 != 0 )
    {
      v45 = *(uint32_t *)(this + 52);
      v35 = -120 - (*(int (**)(void))(*(uint32_t *)v11 + 128))();
      v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v45 + 124))(v45) + v35;
    }
    else
    {
      v44 = *(uint32_t *)(*(uint32_t *)(this + 44) + 468);
    }
  }
  else
  {
    v44 = v9 - v10 - 120;
  }
  v12 = *(uint32_t *)(this + 1192);
  switch ( v12 )
  {
    case 1:
      v31 = *(uint32_t *)(this + 1220);
      v13 = sub_699000(this + 1196);
      v40 = sub_4049C0(1.0, *(float *)(this + 1168), v13, v31);
      v14 = *(uint32_t *)(this + 1220);
      v15 = sub_699000(this + 1196);
      v29 = (float)v41;
      v27 = (float)v39;
      v4 = (uint64_t)sub_4049C0(v27, v29, v15, v14);
      v36 = *(uint32_t *)(this + 1220);
      v16 = sub_699000(this + 1196);
      v30 = (float)v44;
      v28 = (float)v37;
      v17 = (uint64_t)sub_4049C0(v28, v30, v16, v36);
LABEL_20:
      v5 = v17;
      break;
    case 2:
      v4 = v41;
      v5 = v44;
      v40 = *(float *)(this + 1168);
      break;
    case 3:
      v32 = *(uint32_t *)(this + 1220);
      v18 = sub_699000(this + 1196);
      v40 = sub_4049C0(*(float *)(this + 1168), 1.0, v18, v32);
      v33 = *(uint32_t *)(this + 1220);
      v19 = sub_699000(this + 1196);
      v4 = sub_423A80(v41, v39, v19, v33);
      v34 = *(uint32_t *)(this + 1220);
      v20 = sub_699000(this + 1196);
      LODWORD(v17) = sub_423A80(v44, v37, v20, v34);
      goto LABEL_20;
    default:
      break;
  }
  v42 = *(uint32_t *)(this + 44);
  v21 = sub_424FF0(v42);
  v22 = v5 <= 0 ? 0 : v5;
  if ( v22 >= 120 * v21 )
    v22 = 120 * sub_424FF0(v42);
  v38 = v22;
  if ( (v4 <= 0 ? 0 : v4) >= sub_425080(v42) )
    v23 = sub_425080(v42);
  else
    v23 = v4 <= 0 ? 0 : v4;
  *(uint32_t *)(v42 + 464) = v23;
  *(uint32_t *)(v42 + 468) = v38;
  v46 = sub_424DC0(this);
  v43 = sub_424E10(this);
  if ( v4 >= 0 )
  {
    if ( v4 > sub_425080(*(uint32_t *)(this + 44)) )
    {
      v46 += v4 - sub_425080(*(uint32_t *)(this + 44));
      if ( v46 >= 640 )
        v46 = 640;
    }
  }
  else
  {
    v46 = v46 + v4 <= 0 ? 0 : v46 + v4;
  }
  if ( v5 >= 0 )
  {
    v24 = *(uint32_t *)(this + 44);
    if ( v5 > 120 * sub_424FF0(v24) )
    {
      v43 += v5 - 120 * sub_424FF0(v24);
      if ( v43 >= 480 )
        v43 = 480;
    }
  }
  else
  {
    v43 = v43 + v5 <= 0 ? 0 : v43 + v5;
  }
  dword_77F6DC = LODWORD(v40);
  dword_8F7BD0 = v46;
  dword_8F7BD4 = v43;
  v2 = *(uint32_t *)(this + 1192);
  switch ( v2 )
  {
    case 1:
      v25 = *(uint32_t *)(this + 1220);
      v2 = sub_699000(this + 1196);
      if ( v2 >= v25 )
      {
        if ( *(uint32_t *)(this + 1176) != 0 )
        {
          *(uint8_t *)(this + 1209) = 0;
          *(uint8_t *)(this + 1210) = 0;
          LOBYTE(v2) = sub_698F90(this + 1196, *(uint32_t *)(this + 1176) == -1 ? 0 : *(uint32_t *)(this + 1176), 0);
          *(uint32_t *)(this + 1192) = 2;
          return v2;
        }
LABEL_43:
        LOBYTE(v2) = sub_424F00(this);
      }
      break;
    case 2:
      if ( *(uint32_t *)(this + 1176) != -1 )
      {
        LOBYTE(v2) = sub_41C6E0((int *)(this + 1196));
        if ( (uint8_t)v2 != 0 )
          goto LABEL_43;
      }
      break;
    case 3:
      LOBYTE(v2) = sub_41C6E0((int *)(this + 1196));
      if ( (uint8_t)v2 != 0 )
        LOBYTE(v2) = sub_423910(this);
      break;
    default:
      break;
  }
  return v2;
}


// ------------------------------------------------------------
// 0x425940 sub_425940
// ------------------------------------------------------------
uint32_t *sub_425940()
{
  uint32_t *result; // eax

  result = operator new(0xCu);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x425960 sub_425960
// ------------------------------------------------------------
char /*cdecl*/ sub_425960(char a1, int a2, int **a3)
{
  char result; // al
  int **v4; // edi
  int *k; // esi
  int i; // [esp+14h] [ebp+Ch]
  int j; // [esp+18h] [ebp+10h]

  if ( a3 != nullptr )
    result = sub_45ED10(a3, a1);
  if ( a2 != 0 )
  {
    v4 = (int **)(a2 + 28);
    for ( i = 6; i != 0; --i )
    {
      for ( j = 2; j != 0; --j )
      {
        for ( k = *(v4 - 1); k != *v4; k += 2 )
          sub_4939E0(*k, a1);
        v4 += 4;
        result = j - 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4259D0 sub_4259D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4259D0(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 2);
  if ( v2 != 0 && a2 < (*(this + 3) - v2) >> 2 )
    return *(uint32_t *)(*(this + 2) + 4 * a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425A00 sub_425A00
// ------------------------------------------------------------
int /*thiscall*/ sub_425A00(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 30);
  if ( v2 != 0 && a2 < (*(this + 31) - v2) >> 2 )
    return *(uint32_t *)(*(this + 30) + 4 * a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425A30 sub_425A30
// ------------------------------------------------------------
int /*thiscall*/ sub_425A30(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  char v5; // bl
  double v6; // st7
  uint8_t v8; // c0
  uint8_t v9; // c3
  int v10; // edx
  double v11; // st7
  unsigned int v12; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  double v16; // st7
  int v17; // eax
  unsigned int v18; // ebx
  int v19; // edi
  double v20; // st7
  int v21; // eax
  int v22; // [esp-1Ch] [ebp-6Ch]
  int v23; // [esp-1Ch] [ebp-6Ch]
  int v24; // [esp-14h] [ebp-64h]
  int v25; // [esp-14h] [ebp-64h]
  uint32_t v26[8]; // [esp+4h] [ebp-4Ch]
  int v27; // [esp+24h] [ebp-2Ch]
  int v28; // [esp+28h] [ebp-28h]
  int v29; // [esp+2Ch] [ebp-24h]
  unsigned int v30; // [esp+30h] [ebp-20h]
  int v31; // [esp+34h] [ebp-1Ch]
  int v32; // [esp+38h] [ebp-18h]
  char Buffer[16]; // [esp+3Ch] [ebp-14h] BYREF
  int v34; // [esp+4Ch] [ebp-4h]

  v34 = dword_796E50;
  result = *(this + 188);
  if ( result > 0 )
  {
    v3 = *(this + 196);
    result = sub_699000((int)(this + 190));
    if ( result < v3 )
    {
      v4 = sub_699000((int)(this + 190));
      sprintf(Buffer, "%d", *(this + 188));
      v5 = 0;
      v28 = 255;
      if ( v4 >= 200 )
      {
        if ( v4 >= 300 )
        {
          if ( v4 >= 700 )
          {
            v10 = *(this + 184) - 1;
            *(this + 187) = 1065353216;
            *(this + 184) = v10;
            if ( sub_4049C0(255.0, 0.0, v4, 1500) >= 1.0 )
              v11 = sub_4049C0(255.0, 0.0, v4, 1500);
            else
              v11 = 1.0;
            v28 = (uint64_t)(v11 * 0.5);
          }
          else
          {
            v6 = *((float *)this + 187) - 0.1;
            *((float *)this + 187) = v6;
            if ( (v8 | v9) != 0 )
              v6 = 1.0;
            *((float *)this + 187) = v6;
          }
        }
        else
        {
          v5 = 1;
          *(this + 187) = 1069547520;
        }
      }
      else
      {
        *((float *)this + 187) = sub_4049C0(0.5, 1.2, v4, 200);
      }
      v27 = v5 != 1 ? 0 : 5;
      v31 = (v5 != 1) - 1;
      sub_491530(2, 0);
      v32 = *(this + 183);
      v12 = 0;
      v30 = strlen(Buffer);
      if ( v30 != 0 )
      {
        v29 = ((uint8_t)v28 << 24) | 0xFFFFFF;
        do
        {
          v13 = Buffer[v12] + 64;
          v14 = *(uint32_t *)(sub_418DD0(v13) + 20);
          v26[v12] = v14;
          v15 = v14 - 30;
          v30 = v15;
          if ( v12 != 0 )
            v16 = (double)v15 * *((float *)this + 187);
          else
            v16 = (double)v15 * (1.0 - *((float *)this + 187));
          v24 = v29;
          v32 += (uint64_t)v16;
          v22 = *(this + 187);
          v17 = sub_418DD0(v13);
          sub_424760(dword_79C0B0, v32, *(this + 184), v17, *(float *)&v22, v22, 0.0, v24, 0.0, 0.0);
          ++v12;
        }
        while ( v12 < strlen(Buffer) );
      }
      sub_491630(2);
      sub_491530(v27, v31);
      v32 = *(this + 183);
      v18 = 0;
      v31 = strlen(Buffer);
      if ( v31 != 0 )
      {
        v29 = ((uint8_t)v28 << 24) | 0xFFFFFF;
        do
        {
          v19 = Buffer[v18] + 75;
          if ( v18 != 0 )
          {
            v31 = v26[v18] - 30;
            v20 = (double)v31 * *((float *)this + 187);
          }
          else
          {
            v31 = v26[0] - 30;
            v20 = (double)(v26[0] - 30) * (1.0 - *((float *)this + 187));
          }
          v32 += (uint64_t)v20;
          v25 = v29;
          v23 = *(this + 187);
          v21 = sub_418DD0(v19);
          sub_424760(dword_79C0B0, v32, *(this + 184), v21, *(float *)&v23, v23, 0.0, v25, 0.0, 0.0);
          ++v18;
        }
        while ( v18 < strlen(Buffer) );
      }
      return sub_491630(v27);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x425DA0 sub_425DA0
// ------------------------------------------------------------
int /*usercall*/ sub_425DA0@<eax>(int a1@<ecx>, double a2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int v10; // [esp-14h] [ebp-18h]

  result = *(uint32_t *)(a1 + 592);
  if ( result > 0 )
  {
    v4 = 518;
    v5 = sub_699000(a1 + 596);
    v6 = v5;
    if ( *(uint32_t *)(a1 + 592) == 2 )
    {
      if ( v5 < 250 )
      {
        sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
        v4 = (uint64_t)a2 + 513;
LABEL_13:
        v7 = sub_418DD0(99);
        if ( v7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4, 278, dword_79C0B0);
        v8 = 513 - sub_699FC0(*(uint32_t *)(a1 + 592));
        if ( v6 >= 250 )
        {
          if ( v6 >= 300 )
            goto LABEL_20;
          sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
        }
        else
        {
          sub_4049F0(110.0, 0.0, v6, 250, 1);
        }
        v8 = v8 + (uint64_t)a2 - 5;
LABEL_20:
        sub_69A110(v8, 277, *(uint32_t *)(a1 + 592), -1);
        v9 = *(uint32_t *)(a1 + 620);
        result = sub_699000(a1 + 596);
        if ( result >= v9 )
          *(uint32_t *)(a1 + 592) = 0;
        return result;
      }
      if ( v5 >= 300 )
        goto LABEL_13;
      v10 = v5 - 250;
    }
    else
    {
      if ( v5 < 50 )
      {
        sub_4049F0(5.0, 0.0, v5, 250, 1);
        goto LABEL_12;
      }
      if ( v5 >= 100 )
        goto LABEL_13;
      v10 = v5 - 50;
    }
    sub_4049F0(0.0, 5.0, v10, 50, 0);
    goto LABEL_12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x425F10 sub_425F10
// ------------------------------------------------------------
int /*usercall*/ sub_425F10@<eax>(int a1@<ecx>, double a2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int v10; // [esp-14h] [ebp-18h]

  result = *(uint32_t *)(a1 + 628);
  if ( result > 0 )
  {
    v4 = 518;
    v5 = sub_699000(a1 + 632);
    v6 = v5;
    if ( *(uint32_t *)(a1 + 628) == 2 )
    {
      if ( v5 < 250 )
      {
        sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
        v4 = (uint64_t)a2 + 513;
LABEL_13:
        v7 = sub_418DD0(43);
        if ( v7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4, 298, dword_79C0B0);
        v8 = 513 - sub_699FC0(*(uint32_t *)(a1 + 628));
        if ( v6 >= 250 )
        {
          if ( v6 >= 300 )
            goto LABEL_20;
          sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
        }
        else
        {
          sub_4049F0(110.0, 0.0, v6, 250, 1);
        }
        v8 = v8 + (uint64_t)a2 - 5;
LABEL_20:
        sub_69A110(v8, 299, *(uint32_t *)(a1 + 628), -1);
        v9 = *(uint32_t *)(a1 + 656);
        result = sub_699000(a1 + 632);
        if ( result >= v9 )
          *(uint32_t *)(a1 + 628) = 0;
        return result;
      }
      if ( v5 >= 300 )
        goto LABEL_13;
      v10 = v5 - 250;
    }
    else
    {
      if ( v5 < 50 )
      {
        sub_4049F0(5.0, 0.0, v5, 250, 1);
        goto LABEL_12;
      }
      if ( v5 >= 100 )
        goto LABEL_13;
      v10 = v5 - 50;
    }
    sub_4049F0(0.0, 5.0, v10, 50, 0);
    goto LABEL_12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x426080 sub_426080
// ------------------------------------------------------------
int /*usercall*/ sub_426080@<eax>(int a1@<ecx>, double a2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int v10; // eax
  int v11; // esi

  result = *(uint32_t *)(a1 + 556);
  if ( result <= 0 )
    return result;
  v4 = 483;
  v5 = sub_699000(a1 + 560);
  if ( *(uint32_t *)(a1 + 556) != 2 )
  {
    if ( v5 < 50 )
    {
      sub_4049F0(5.0, 0.0, v5, 250, 1);
      goto LABEL_12;
    }
    if ( v5 >= 100 )
      goto LABEL_13;
    v6 = v5 - 50;
LABEL_11:
    sub_4049F0(0.0, 5.0, v6, 50, 0);
    goto LABEL_12;
  }
  if ( v5 >= 250 )
  {
    if ( v5 >= 300 )
      goto LABEL_13;
    v6 = v5 - 250;
    goto LABEL_11;
  }
  sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
  v4 = (uint64_t)a2 + 478;
LABEL_13:
  v7 = sub_418DD0(98);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4, 248, dword_79C0B0);
  v8 = *(uint32_t *)(a1 + 584);
  if ( sub_699000(a1 + 560) >= v8 )
    *(uint32_t *)(a1 + 556) = 0;
  result = *(uint32_t *)(a1 + 556);
  if ( result > 0 )
  {
    v9 = 578;
    v10 = sub_699000(a1 + 560);
    if ( v10 >= 250 )
    {
      if ( v10 >= 300 )
        goto LABEL_23;
      sub_4049F0(0.0, 5.0, v10 - 250, 50, 0);
    }
    else
    {
      sub_4049F0(110.0, 0.0, v10, 250, 1);
    }
    v9 = (uint64_t)a2 + 573;
LABEL_23:
    sub_69A110(v9, 248, *(uint32_t *)(a1 + 556), -1);
    v11 = *(uint32_t *)(a1 + 584);
    result = sub_699000(a1 + 560);
    if ( result >= v11 )
      *(uint32_t *)(a1 + 556) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x426200 sub_426200
// ------------------------------------------------------------
void /*thiscall*/ sub_426200(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  double v8; // st7
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  double v18; // st7
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  int v27; // edi
  int v28; // esi
  int v29; // eax
  double v30; // st7
  int v31; // esi
  int v32; // eax
  int v33; // [esp-14h] [ebp-34h]
  int v34; // [esp-14h] [ebp-34h]
  int v35; // [esp-14h] [ebp-34h]
  int v36; // [esp-10h] [ebp-30h]
  int v37; // [esp-10h] [ebp-30h]
  int v38; // [esp-10h] [ebp-30h]
  int v39; // [esp-Ch] [ebp-2Ch]
  int v40; // [esp-Ch] [ebp-2Ch]
  int v41; // [esp-Ch] [ebp-2Ch]
  int v42; // [esp+4h] [ebp-1Ch]
  int v43; // [esp+4h] [ebp-1Ch]
  int v44; // [esp+4h] [ebp-1Ch]
  int v45; // [esp+4h] [ebp-1Ch]
  int v46; // [esp+4h] [ebp-1Ch]
  int v47; // [esp+4h] [ebp-1Ch]
  int v48; // [esp+4h] [ebp-1Ch]
  int v49; // [esp+8h] [ebp-18h]
  int v50; // [esp+8h] [ebp-18h]
  int v51; // [esp+8h] [ebp-18h]
  int v52; // [esp+8h] [ebp-18h]
  int v53; // [esp+8h] [ebp-18h]
  int v54; // [esp+8h] [ebp-18h]
  int v55; // [esp+8h] [ebp-18h]
  int v56; // [esp+Ch] [ebp-14h]
  int v57; // [esp+10h] [ebp-10h]
  int v58; // [esp+10h] [ebp-10h]
  int v59; // [esp+10h] [ebp-10h]
  int v60; // [esp+14h] [ebp-Ch]
  int v61; // [esp+14h] [ebp-Ch]
  int v62; // [esp+14h] [ebp-Ch]
  float v63; // [esp+18h] [ebp-8h]
  char v64; // [esp+1Fh] [ebp-1h]
  char v65; // [esp+1Fh] [ebp-1h]
  char v66; // [esp+1Fh] [ebp-1h]

  if ( dword_8F7C04 == 0 )
    return;
  v2 = dword_8F7C04;
  v39 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
  v60 = sub_45E490(v3, v39);
  v4 = dword_8F7C04;
  v36 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
  v57 = sub_45E4D0(v5, v33, v36, 1.0);
  v56 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 192))(dword_8F7C04);
  sub_418DD0(85);
  sub_418DD0(86);
  sub_418DD0(87);
  v6 = dword_8F7BE4;
  LOBYTE(v63) = 0;
  v64 = 0;
  v49 = *(uint32_t *)(this + 524);
  if ( sub_699000(this + 500) >= v49 && dword_8F7BE4 < 2 && sub_699000(this + 500) > dword_8F7B28[v6] )
  {
    v6 = ++dword_8F7BE4;
    *(uint8_t *)(this + 513) = 0;
    *(uint8_t *)(this + 514) = 0;
    sub_698F90(this + 500, dword_8F7B28[v6], 0);
    v64 = 1;
  }
  v50 = *(uint32_t *)(this + 524);
  if ( sub_699000(this + 500) < v50 )
  {
    v42 = *(uint32_t *)(this + 524);
    v51 = dword_8F7B88[v6];
    v7 = sub_699000(this + 500);
    v8 = (double)v51;
    v63 = v8;
    sub_4049F0(0.0, v63, v7, v42, 1);
    v52 = (uint64_t)v8;
    v9 = *(uint32_t *)(sub_418DD0(85) + 20) - v52 + v60;
    if ( v6 != 0 )
    {
      if ( v6 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v52 / v63 * 255.0);
      v9 -= dword_8F7B88[0];
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v52 / v63 * 255.0);
    }
    goto LABEL_15;
  }
  if ( v64 == 1 )
  {
    v9 = v60;
LABEL_15:
    v10 = sub_418DD0(85);
    sub_424760(dword_79C0B0, v9, v57 - v56 - 64, v10, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
  }
  v11 = dword_8F7C04;
  v40 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11);
  v61 = sub_45E490(v12, v40);
  v13 = dword_8F7C04;
  v37 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 128))(v13);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
  v15 = sub_45E4D0(v14, v34, v37, 1.0);
  v16 = dword_8F7BE0;
  v43 = *(uint32_t *)(this + 496);
  v58 = v15;
  v65 = 0;
  if ( sub_699000(this + 472) >= v43 && dword_8F7BE0 < 2 && sub_699000(this + 472) > dword_8F7B1C[v16] )
  {
    v16 = ++dword_8F7BE0;
    *(uint8_t *)(this + 485) = 0;
    *(uint8_t *)(this + 486) = 0;
    sub_698F90(this + 472, dword_8F7B1C[v16], 0);
    v65 = 1;
  }
  v44 = *(uint32_t *)(this + 496);
  if ( sub_699000(this + 472) >= v44 )
  {
    if ( v65 != 1 )
      goto LABEL_31;
    v19 = v61;
  }
  else
  {
    v45 = dword_8F7B7C[v16];
    v53 = *(uint32_t *)(this + 496);
    v17 = sub_699000(this + 472);
    v18 = (double)v45;
    v63 = v18;
    sub_4049F0(0.0, v63, v17, v53, 1);
    v54 = (uint64_t)v18;
    if ( v16 != 0 )
    {
      if ( v16 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v54 / v63 * 255.0);
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v54 / v63 * 255.0);
    }
    v19 = *(uint32_t *)(sub_418DD0(86) + 20) - (uint64_t)v18 + v61;
    if ( v16 != 0 )
      v19 -= dword_8F7B7C[0];
  }
  v20 = sub_418DD0(86);
  sub_424760(dword_79C0B0, v19, v58 - v56 - 64, v20, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
LABEL_31:
  v21 = dword_8F7C04;
  v41 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 120))(v21);
  v62 = sub_45E490(v22, v41);
  v23 = dword_8F7C04;
  v38 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 128))(v23);
  v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 124))(v23);
  v25 = sub_45E4D0(v24, v35, v38, 1.0);
  v26 = dword_8F7BDC;
  v27 = this + 528;
  v46 = *(uint32_t *)(this + 552);
  v59 = v25;
  v66 = 0;
  if ( sub_699000(this + 528) >= v46 && dword_8F7BDC < 2 && sub_699000(this + 528) > dword_8F7B10[v26] )
  {
    v26 = ++dword_8F7BDC;
    *(uint8_t *)(this + 541) = 0;
    *(uint8_t *)(this + 542) = 0;
    sub_698F90(this + 528, dword_8F7B10[v26], 0);
    v66 = 1;
  }
  v47 = *(uint32_t *)(this + 552);
  if ( sub_699000(this + 528) >= v47 )
  {
    if ( v66 != 1 )
      return;
    v31 = v62;
  }
  else
  {
    v28 = *(uint32_t *)(this + 552);
    v48 = dword_8F7B70[v26];
    v29 = sub_699000(v27);
    v30 = (double)v48;
    v63 = v30;
    sub_4049F0(0.0, v63, v29, v28, 1);
    v55 = (uint64_t)v30;
    if ( v26 != 0 )
    {
      if ( v26 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v55 / v63 * 255.0);
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v55 / v63 * 255.0);
    }
    v31 = *(uint32_t *)(sub_418DD0(87) + 20) - (uint64_t)v30 + v62;
    if ( v26 != 0 )
      v31 -= dword_8F7B70[0];
  }
  v32 = sub_418DD0(87);
  sub_424760(dword_79C0B0, v31, v59 - v56 - 64, v32, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
}


// ------------------------------------------------------------
// 0x426820 sub_426820
// ------------------------------------------------------------
int /*thiscall*/ sub_426820(int this, int a2, int a3)
{
  int result; // eax

  result = a2;
  if ( a2 != 0 )
  {
    switch ( a2 )
    {
      case 1:
        dword_8F7B84 = *(uint32_t *)(sub_418DD0(86) + 20);
        dword_8F7B7C = dword_8F7B84 + ((unsigned int)dword_8F7B84 >> 1);
        dword_8F7B1C = 200;
        dword_8F7B80 = 0;
        dword_8F7B20 = 500;
        dword_8F7B24 = 200;
        dword_8F7BE0 = 0;
        *(uint32_t *)(this + 1252) = 1;
        *(uint8_t *)(this + 485) = 0;
        *(uint8_t *)(this + 486) = 0;
        sub_698F90(dword_8F7B1C, 0);
        *(uint8_t *)(this + 977) = 0;
        *(uint8_t *)(this + 978) = 0;
        result = sub_698F90(500, 0);
        *(uint8_t *)(this + 1161) = 1;
        break;
      case 2:
        if ( dword_8F7C04 != 0 )
        {
          dword_8F7B90 = *(uint32_t *)(sub_418DD0(85) + 20);
          dword_8F7B88 = dword_8F7B90 + ((unsigned int)dword_8F7B90 >> 1);
          dword_8F7B28 = 200;
          dword_8F7B8C = 0;
          dword_8F7B2C = 500;
          dword_8F7B30 = 200;
          *(uint32_t *)(this + 1252) = 2;
          dword_8F7BE4 = 0;
          *(uint8_t *)(this + 513) = 0;
          *(uint8_t *)(this + 514) = 0;
          sub_698F90(dword_8F7B28, 0);
          return sub_424D80(2);
        }
        break;
      case 3:
        *(uint8_t *)(this + 573) = 0;
        *(uint8_t *)(this + 574) = 0;
        sub_698F90(1500, 0);
        *(uint32_t *)(this + 556) += a3;
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_ATTACKED",
                 -1,
                 0,
                 0);
      case 4:
        return sub_424D80(4);
      case 5:
        *(uint32_t *)(this + 900) = a3;
        *(uint8_t *)(this + 885) = 0;
        *(uint8_t *)(this + 886) = 0;
        sub_698F90(1500, 0);
        return sub_424D80(5);
      case 7:
        *(uint32_t *)(this + 592) = a3;
        *(uint8_t *)(this + 609) = 0;
        *(uint8_t *)(this + 610) = 0;
        sub_698F90(1500, 0);
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_TECHNIC",
                 -1,
                 0,
                 0);
      case 6:
        *(uint32_t *)(this + 628) = a3;
        *(uint8_t *)(this + 645) = 0;
        *(uint8_t *)(this + 646) = 0;
        sub_698F90(1500, 0);
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_STYLE",
                 -1,
                 0,
                 0);
      default:
        break;
    }
  }
  else
  {
    dword_8F7B78 = *(uint32_t *)(sub_418DD0(87) + 20);
    dword_8F7B70 = dword_8F7B78 + ((unsigned int)dword_8F7B78 >> 1);
    dword_8F7B10 = 200;
    dword_8F7B74 = 0;
    dword_8F7B14 = 500;
    dword_8F7B18 = 200;
    *(uint32_t *)(this + 1252) = 0;
    dword_8F7BDC = 0;
    *(uint8_t *)(this + 541) = 0;
    *(uint8_t *)(this + 542) = 0;
    sub_698F90(dword_8F7B10, 0);
    *(uint8_t *)(this + 949) = 0;
    *(uint8_t *)(this + 950) = 0;
    result = sub_698F90(500, 0);
    *(uint8_t *)(this + 1160) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x426B10 sub_426B10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_426B10(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // ecx
  uint32_t *result; // eax
  int v7; // ecx
  int v8; // ebx
  unsigned int i; // esi
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // ecx

  v4 = *(this + 331);
  *(this + 331) = a2;
  v5 = (int)(this + 332);
  *(this + 330) = v4;
  *(uint8_t *)(v5 + 13) = 0;
  *(uint8_t *)(v5 + 14) = 0;
  sub_698F90(v5, a3, 0);
  result = (uint32_t *)*(this + 26);
  if ( result != nullptr )
  {
    v7 = result[30];
    v8 = v7 != 0 ? (result[31] - v7) >> 2 : 0;
    for ( i = 0; (int)i < v8; ++i )
    {
      v10 = *(this + 26);
      v11 = *(uint32_t *)(v10 + 120);
      if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      result = (uint32_t *)__RTDynamicCast(
                           v12,
                           0,
                           &IRDCollisionObject `RTTI Type Descriptor',
                           &IRDActiveObject `RTTI Type Descriptor',
                           0);
      if ( result != nullptr )
      {
        v13 = result[1665];
        if ( v13 == 2 || v13 == 1 )
          result = (uint32_t *)sub_495890(v13, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x426BD0 sub_426BD0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_426BD0(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__IControl;
  *(this + 76) = 0;
  *((uint32_t *)this + 18) = &vftbl_nengine__CNString;
  sub_402A50();
  *((uint32_t *)this + 24) = sub_425940(this + 92);
  *((uint32_t *)this + 25) = 0;
  nengine__IControl__vmt10(this);
  nengine__IControl__vmt4(this);
  return this;
}



// ------------------------------------------------------------
// 0x426C60 nengine__IControl__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__IControl__vmt0(void *Block, char a2)
{
  sub_426C90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x426C90 sub_426C90
// ------------------------------------------------------------
int /*thiscall*/ sub_426C90(void **this)
{
  int result; // eax

  *this = &vftbl_nengine__IControl;
  nengine__IControl__vmt14();
  sub_6569D0(this + 23);
  j__free(*(this + 24));
  *(this + 24) = nullptr;
  *(this + 18) = &vftbl_nengine__CNString;
  result = sub_402A60(this + 18);
  *(this + 18) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 76) = 0;
  *this = &vftbl_nengine__IObject;
  *((uint8_t *)this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x426D20 sub_426D20
// ------------------------------------------------------------
void /*thiscall*/ sub_426D20(int this)
{
  int v2; // eax
  int v3; // esi
  int v4; // esi
  int v5; // kr08_4
  int v6; // esi
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  bool v16; // sf
  int v17; // eax
  int v18; // edi
  int v19; // esi
  void *v20; // ecx
  void *v21; // eax
  bool v22; // zf
  int v23; // [esp-14h] [ebp-40h]
  uint8_t v24[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v26; // [esp+14h] [ebp-18h]
  int v27; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h]
  int v29; // [esp+28h] [ebp-4h]

  v2 = *(uint32_t *)(this + 840);
  if ( v2 == -1 )
  {
    dword_77F7AC = 0;
    dword_8F7C00 = 0;
    return;
  }
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      dword_8F7C00 = 104;
    }
    else if ( v2 == 2 )
    {
      dword_8F7C00 = 106;
    }
  }
  else
  {
    dword_8F7C00 = 102;
  }
  v3 = *(uint32_t *)(sub_418DD0(dword_8F7C00 + 1) + 20);
  v27 = (int)abs32(v3 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 20)) / 2;
  v4 = *(uint32_t *)(sub_418DD0(dword_8F7C00 + 1) + 24);
  v28 = (int)abs32(v4 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 24)) / 2;
  v5 = *(uint32_t *)(sub_418DD0(dword_8F7C00) + 20);
  v6 = 320 - v5 / 2;
  v7 = 240 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 24) / 2;
  v8 = *(uint32_t *)(this + 932);
  switch ( v8 )
  {
    case 0:
      sub_491530(5, -1);
      v27 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      v9 = sub_418DD0(dword_8F7C00 + 1);
      if ( v9 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 156))(
          v9,
          320 - v5 / 2,
          v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v27,
          1115947008,
          1333788672);
      goto LABEL_22;
    case 1:
      sub_491530(5, -1);
      v26 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      v10 = sub_418DD0(dword_8F7C00);
      if ( v10 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 156))(
          v10,
          v27 + v6,
          v28 + v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v26,
          1115947008,
          1333788672);
      goto LABEL_22;
    case 2:
      v11 = sub_418DD0(dword_8F7C00);
      if ( v11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 156))(
          v11,
          v27 + v6,
          v28 + v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1115947008,
          1333788672);
      break;
    case 3:
      v12 = sub_418DD0(dword_8F7C00 + 1);
      sub_423930(320 - v5 / 2, v7, v12, 1065353216, 1065353216, 0, -1, 1115947008, 1333788672);
      break;
    case 4:
      sub_491530(5, -1);
      v23 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      v13 = sub_418DD0(dword_8F7C00 + 1);
      sub_423930(320 - v5 / 2, v7, v13, 1065353216, 1065353216, 0, v23, 1115947008, 1333788672);
LABEL_22:
      sub_491630(5);
      break;
    default:
      break;
  }
  dword_77F7AC -= 10;
  if ( dword_77F7AC <= 128 )
    dword_77F7AC = 128;
  v14 = *(uint32_t *)(this + 868);
  if ( sub_699000(this + 844) >= v14 )
  {
    v15 = *(uint32_t *)(this + 932) + 1;
    v16 = *(uint32_t *)(this + 932) - 4 < 0;
    *(uint32_t *)(this + 932) = v15;
    if ( v16 != __OFSUB__(v15, 5) )
    {
      *(uint8_t *)(this + 857) = 0;
      *(uint8_t *)(this + 858) = 0;
      sub_698F90(this + 844, dword_6C38CC[*(uint32_t *)(this + 932)], 0);
      dword_77F7AC = 255;
    }
    else
    {
      v17 = sub_48C1C0(0);
      v18 = *(uint32_t *)(*(uint32_t *)(this + 44) + 468) + 128;
      v19 = v17 + 320;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 836) + 12))(*(uint32_t *)(this + 836), 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 836) + 40))(
        *(uint32_t *)(this + 836),
        v19,
        v18,
        0);
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 836) + 28))(*(uint32_t *)(this + 836)) + 84) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 836) + 92))(*(uint32_t *)(this + 836), v24);
      v20 = *(void **)(this + 104);
      v29 = 0;
      sub_4600B0(v20, 2, 0, (int)v24);
      v21 = Block;
      v22 = Block == nullptr;
      *(uint32_t *)(this + 840) = -1;
      if ( !v22 )
        j__free(v21);
    }
  }
}


// ------------------------------------------------------------
// 0x4271B0 sub_4271B0
// ------------------------------------------------------------
void /*usercall*/ sub_4271B0(int a1@<ecx>, double a2@<st0>)
{
  int i; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // edi
  int v15; // eax
  char *v16; // edx
  int v17; // edi
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // [esp+8h] [ebp-38h]
  int v28; // [esp+Ch] [ebp-34h]
  int v29; // [esp+10h] [ebp-30h]
  void *Block[4]; // [esp+18h] [ebp-28h] BYREF
  int v31; // [esp+28h] [ebp-18h]
  unsigned int v32; // [esp+2Ch] [ebp-14h]
  int v33; // [esp+30h] [ebp-10h]
  int v34; // [esp+3Ch] [ebp-4h]

  v33 = dword_796E50;
  for ( i = 0; i < 2; ++i )
  {
    if ( *(int *)(a1 + 4 * i + 248) >= 1 )
    {
      v4 = 28 * i + a1;
      v29 = *(uint32_t *)(v4 + 280);
      if ( sub_699000(v4 + 256) >= v29 )
      {
        v5 = *(uint32_t *)(a1 + 4 * i + 248);
        v6 = dword_6C38A4[i];
        if ( v5 >= v6 )
        {
          *(uint32_t *)(a1 + 4 * i + 400) = 5 * (v5 - v6 + 1);
          *(uint8_t *)(v4 + 421) = 0;
          *(uint8_t *)(v4 + 422) = 0;
          sub_698F90(v4 + 408, 1500, 0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
            dword_8F7C04,
            "HK_STYLE",
            -1,
            0,
            0);
        }
        if ( *(uint32_t *)(a1 + 4 * i + 248) >= dword_6C38A4[i] )
        {
          if ( i != 0 )
            sub_422E70(497);
          else
            sub_422E70(496);
          v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
          sub_495A70(dword_99FD58, *(uint32_t *)(a1 + 4 * i + 248), i != 0 ? 2 : 0, v7);
        }
        *(uint32_t *)(a1 + 4 * i + 248) = 0;
      }
    }
    if ( *(int *)(a1 + 312) >= 2 && *(int *)(a1 + 316) >= 1 )
      *(uint32_t *)(a1 + 316) = 0;
    if ( *(uint32_t *)(a1 + 4 * i + 312) >= dword_6C38AC[i] )
    {
      v8 = 515;
      v28 = 28 * i + a1 + 320;
      v9 = sub_699000(v28);
      if ( *(uint32_t *)(a1 + 4 * i + 312) == 2 )
      {
        if ( v9 < 250 )
        {
          sub_4049F0(110.0, 0.0, v9, 250, 1);
LABEL_26:
          v8 = (uint64_t)a2 + 510;
          goto LABEL_27;
        }
        if ( v9 < 300 )
        {
          v10 = v9 - 250;
LABEL_25:
          sub_4049F0(0.0, 5.0, v10, 50, 0);
          goto LABEL_26;
        }
      }
      else
      {
        if ( v9 < 50 )
        {
          sub_4049F0(5.0, 0.0, v9, 250, 1);
          goto LABEL_26;
        }
        if ( v9 < 100 )
        {
          v10 = v9 - 50;
          goto LABEL_25;
        }
      }
LABEL_27:
      v11 = *(uint32_t *)(a1 + 4 * i + 312);
      if ( v11 > 10 )
        v29 = (v11 > 20) + 1;
      else
        v29 = 0;
      v12 = sub_418DD0(11 * v29 + 10);
      if ( v12 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v8, 131, dword_79C0B0);
      sub_69A110(v8, 123, *(uint32_t *)(a1 + 4 * i + 312), -1);
      v13 = *(uint32_t *)(v28 + 24);
      if ( sub_699000(v28) >= v13 )
        *(uint32_t *)(a1 + 4 * i + 312) = 0;
      continue;
    }
  }
  if ( *(uint8_t *)(a1 + 720) == 1 )
  {
    v14 = *(uint32_t *)(a1 + 716);
    if ( sub_699000(a1 + 692) >= v14 )
    {
      *(uint8_t *)(a1 + 720) = 0;
      *(uint8_t *)(a1 + 677) = 0;
      *(uint8_t *)(a1 + 678) = 0;
      sub_698F90(a1 + 664, 125, 0);
      *(uint8_t *)(a1 + 721) = 1;
      *(uint32_t *)(a1 + 728) = 108;
      *(uint32_t *)(a1 + 724) = 0;
      v15 = *(uint32_t *)(dword_8F7A24 + 12);
      if ( v15 == 4 || (v16 = "HK2_AIRIAL", v15 == 6) )
        v16 = "HK1_AIRIAL";
      v31 = 0;
      v32 = 15;
      LOBYTE(Block[0]) = 0;
      sub_4015C0(v16, strlen(v16));
      v34 = 0;
      (*(void (/*thiscall*/ **)(int, void **, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        Block,
        -1,
        0,
        0);
      v34 = -1;
      if ( v32 >= 0x10 )
        j__free(Block[0]);
    }
  }
  if ( *(uint8_t *)(a1 + 824) == 1 )
  {
    v17 = *(uint32_t *)(a1 + 820);
    if ( sub_699000(a1 + 796) >= v17 )
    {
      v18 = *(uint32_t *)(a1 + 828);
      if ( v18 != 0 )
      {
        switch ( v18 )
        {
          case 1:
            *(uint32_t *)(a1 + 828) = 2;
            *(uint32_t *)(a1 + 832) = 142;
            *(uint8_t *)(a1 + 809) = 0;
            *(uint8_t *)(a1 + 810) = 0;
            sub_698F90(a1 + 796, dword_6C38E0[*(uint32_t *)(a1 + 828)], 0);
            break;
          case 2:
            *(uint32_t *)(a1 + 828) = 3;
            *(uint8_t *)(a1 + 809) = 0;
            *(uint8_t *)(a1 + 810) = 0;
            sub_698F90(a1 + 796, dword_6C38E0[*(uint32_t *)(a1 + 828)], 0);
            break;
          case 3:
            *(uint32_t *)(a1 + 828) = 0;
            *(uint8_t *)(a1 + 824) = 0;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(a1 + 828) = 1;
        *(uint32_t *)(a1 + 832) = 141;
        *(uint8_t *)(a1 + 809) = 0;
        *(uint8_t *)(a1 + 810) = 0;
        sub_698F90(a1 + 796, dword_6C38E0[*(uint32_t *)(a1 + 828)], 0);
      }
    }
    Block[0] = (void *)134;
    Block[1] = (void *)135;
    Block[2] = (void *)136;
    Block[3] = (void *)137;
    v31 = 138;
    v32 = 139;
    sub_491530(2, 0);
    v19 = *(uint32_t *)(sub_418DD0(*(&v27 + 2 * *(uint32_t *)(a1 + 756))) + 20);
    v20 = sub_418DD0(*(&v27 + 2 * *(uint32_t *)(a1 + 756)));
    if ( v20 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, 640 - v19, 145, dword_79C0B0);
    sub_491630(2);
    v21 = sub_418DD0(*(&v28 + 2 * *(uint32_t *)(a1 + 756)));
    if ( v21 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v21 + 152))(v21, 640 - v19, 145, dword_79C0B0);
    if ( *(int *)(a1 + 828) <= 2 && *(uint8_t *)(a1 + 824) == 1 )
    {
      sub_491530(2, 0);
      v22 = sub_418DD0(*(uint32_t *)(a1 + 832));
      if ( v22 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v22 + 152))(v22, 200, 155, dword_79C0B0);
      sub_491630(2);
    }
  }
  if ( *(uint8_t *)(a1 + 721) == 1 )
  {
    v23 = *(uint32_t *)(a1 + 688);
    if ( sub_699000(a1 + 664) >= v23 )
    {
      v24 = *(uint32_t *)(a1 + 724);
      if ( v24 != 0 )
      {
        switch ( v24 )
        {
          case 1:
            *(uint32_t *)(a1 + 724) = 2;
            *(uint32_t *)(a1 + 728) = 110;
            *(uint8_t *)(a1 + 677) = 0;
            *(uint8_t *)(a1 + 678) = 0;
            sub_698F90(a1 + 664, dword_6C38E0[*(uint32_t *)(a1 + 724)], 0);
            break;
          case 2:
            *(uint32_t *)(a1 + 724) = 3;
            *(uint8_t *)(a1 + 677) = 0;
            *(uint8_t *)(a1 + 678) = 0;
            sub_698F90(a1 + 664, dword_6C38E0[*(uint32_t *)(a1 + 724)], 0);
            break;
          case 3:
            *(uint32_t *)(a1 + 724) = 0;
            *(uint8_t *)(a1 + 721) = 0;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(a1 + 724) = 1;
        *(uint32_t *)(a1 + 728) = 109;
        *(uint8_t *)(a1 + 677) = 0;
        *(uint8_t *)(a1 + 678) = 0;
        sub_698F90(a1 + 664, dword_6C38E0[*(uint32_t *)(a1 + 724)], 0);
      }
    }
    v25 = sub_418DD0(100);
    if ( v25 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, 555, 200, dword_79C0B0);
    if ( *(int *)(a1 + 724) <= 2 && *(uint8_t *)(a1 + 721) == 1 )
    {
      sub_491530(2, 0);
      v26 = sub_418DD0(*(uint32_t *)(a1 + 728));
      if ( v26 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, 415, 195, dword_79C0B0);
      sub_491630(2);
    }
  }
}


// ------------------------------------------------------------
// 0x4278D0 sub_4278D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4278D0(int this, int a2, int a3)
{
  int v4; // eax
  bool v5; // zf
  char *v6; // eax
  void *p_Block; // eax
  void *Block; // [esp+Ch] [ebp-28h] BYREF
  unsigned int v9; // [esp+20h] [ebp-14h]
  int v10; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  v10 = dword_796E50;
  if ( a2 != 0 )
  {
    if ( a2 == 1 )
    {
      *(uint32_t *)(this + 756) = a3;
      if ( *(uint8_t *)(this + 824) == 0 )
      {
        *(uint8_t *)(this + 809) = 0;
        *(uint8_t *)(this + 810) = 0;
        sub_698F90(this + 796, 125, 0);
        *(uint8_t *)(this + 824) = 1;
        *(uint32_t *)(this + 832) = 140;
        *(uint32_t *)(this + 828) = 0;
        v4 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v4 == 4 || (v5 = v4 == 6, v6 = "R_HK2_DOUBLE", v5) )
          v6 = "R_HK1_DOUBLE";
        sub_401710(v6);
        p_Block = Block;
        v11 = 0;
        if ( v9 < 0x10 )
          p_Block = &Block;
        (*(void (/*thiscall*/ **)(int, void *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
          dword_8F7C04,
          p_Block,
          -1,
          0,
          0);
        if ( v9 >= 0x10 )
          j__free(Block);
      }
    }
  }
  else if ( *(uint8_t *)(this + 721) == 0 )
  {
    *(uint8_t *)(this + 705) = 0;
    *(uint8_t *)(this + 706) = 0;
    sub_698F90(this + 692, 1000, 0);
    *(uint8_t *)(this + 720) = 1;
  }
}



// ------------------------------------------------------------
// 0x427A00 sub_427A00
// ------------------------------------------------------------
HGDIOBJ /*usercall*/ sub_427A00@<eax>(int a1@<ecx>, double a2@<st0>)
{
  int v2; // esi
  int v3; // edi
  HGDIOBJ result; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  void *v9; // esi
  int v10; // esi
  int v11; // eax
  int v12; // eax
  uint8_t v13[4]; // [esp+8h] [ebp-68h] BYREF
  int v14; // [esp+Ch] [ebp-64h]
  int v15; // [esp+14h] [ebp-5Ch]
  int v16; // [esp+18h] [ebp-58h]
  int v17; // [esp+1Ch] [ebp-54h]
  int v18; // [esp+20h] [ebp-50h]
  int v19; // [esp+24h] [ebp-4Ch]
  int v20; // [esp+28h] [ebp-48h]
  int v21; // [esp+2Ch] [ebp-44h]
  int v22; // [esp+30h] [ebp-40h]
  HGDIOBJ ho; // [esp+34h] [ebp-3Ch]
  int v24; // [esp+38h] [ebp-38h]
  int v25; // [esp+3Ch] [ebp-34h]
  int v26; // [esp+40h] [ebp-30h]
  void *Block; // [esp+48h] [ebp-28h]
  int v28; // [esp+58h] [ebp-18h]
  unsigned int v29; // [esp+5Ch] [ebp-14h]
  int v30; // [esp+60h] [ebp-10h]
  int v31; // [esp+6Ch] [ebp-4h]

  v2 = a1 + 872;
  v25 = a1;
  v3 = *(uint32_t *)(a1 + 896);
  v30 = dword_796E50;
  result = (HGDIOBJ)sub_699000(a1 + 872);
  if ( (int)result >= v3 )
    return result;
  v5 = 10;
  v6 = sub_699000(v2);
  if ( v6 < 250 )
  {
    sub_4049F0(-110.0, 0.0, v6, 250, 1);
LABEL_6:
    v5 = (uint64_t)a2 + 5;
    goto LABEL_7;
  }
  if ( v6 < 300 )
  {
    sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
    goto LABEL_6;
  }
LABEL_7:
  v7 = sub_418DD0(104);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5, 218, dword_79C0B0);
  v24 = dword_99FCCC;
  v13[0] = 0;
  v13[1] = 0;
  v13[3] = 0;
  v15 = 0;
  v16 = 6;
  v17 = 12;
  v18 = 0;
  v19 = 1600;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  ho = nullptr;
  v13[2] = 1;
  v14 = -16777216;
  v8 = *(uint32_t *)dword_79C0B0;
  v31 = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(v8 + 72))(dword_79C0B0, v13);
  v26 = 0;
  v9 = (void *)sub_422E70(498);
  v29 = 15;
  v28 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(v9, strlen((const char *)v9));
  LOBYTE(v31) = 1;
  if ( dword_99FEC0 != 0 )
  {
    v10 = sub_48F690(*(uint32_t *)(v25 + 900));
    if ( v10 != 0 && v10 != -16 )
    {
      if ( *(uint32_t *)(v10 + 40) < 0x10u )
        v11 = v10 + 20;
      else
        v11 = *(uint32_t *)(v10 + 20);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v5 + 33,
        204,
        -16776961,
        v11);
    }
  }
  else
  {
    v10 = v26;
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( v10 != 0 )
  {
    v12 = sub_42B340(v10);
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v12 + 384))(v12, v5 + 10, 191, 24, 24, 1065353216);
  }
  if ( v29 >= 0x10 )
    j__free(Block);
  result = ho;
  v28 = 0;
  LOBYTE(Block) = 0;
  v29 = 15;
  if ( ho != nullptr )
    return (HGDIOBJ)DeleteObject(ho);
  return result;
}


// ------------------------------------------------------------
// 0x427C20 sub_427C20
// ------------------------------------------------------------
void /*thiscall*/ sub_427C20(uint32_t *this)
{
  int i; // edi
  int v2; // esi
  char *v3; // edx
  void *p_Block; // eax
  int v6; // [esp+10h] [ebp-30h]
  void *Block; // [esp+18h] [ebp-28h] BYREF
  int v8; // [esp+28h] [ebp-18h]
  unsigned int v9; // [esp+2Ch] [ebp-14h]
  int v10; // [esp+30h] [ebp-10h]
  int v11; // [esp+3Ch] [ebp-4h]

  v10 = dword_796E50;
  v6 = *(uint32_t *)(dword_8F7A24 + 12);
  for ( i = 0; i < 8; ++i )
  {
    v2 = *(this + 7 * i + 240);
    if ( sub_699000((int)(this + 7 * i + 234)) >= v2 && *((uint8_t *)this + i + 1160) == 1 )
    {
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
      sub_4015C0((void *)szPassword, 0);
      v11 = 0;
      switch ( i )
      {
        case 0:
          if ( v6 == 4 || (v3 = "HK2_OVERKILL", v6 == 6) )
            v3 = "HK1_OVERKILL";
          goto LABEL_24;
        case 1:
          if ( v6 == 4 || (v3 = "HK2_BACK_ATK", v6 == 6) )
            v3 = "HK1_BACK_ATK";
          goto LABEL_24;
        case 2:
          if ( v6 == 4 || (v3 = "HK2_COUNTER", v6 == 6) )
            v3 = "HK1_COUNTER";
          goto LABEL_24;
        case 4:
          if ( v6 == 4 || (v3 = "HK2_FINISH_01", v6 == 6) )
            v3 = "HK1_FINISH_01";
          goto LABEL_24;
        case 5:
          if ( v6 == 4 || (v3 = "R_HK2_KILL", v6 == 6) )
            v3 = "R_HK1_KILL";
LABEL_24:
          sub_4015C0(v3, strlen(v3));
          break;
        default:
          break;
      }
      p_Block = Block;
      if ( v9 < 0x10 )
        p_Block = &Block;
      (*(void (/*thiscall*/ **)(int, void *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        p_Block,
        -1,
        0,
        0);
      *((uint8_t *)this + i + 1160) = 0;
      v11 = -1;
      if ( v9 >= 0x10 )
        j__free(Block);
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
    }
  }
}



// ------------------------------------------------------------
// 0x427E20 sub_427E20
// ------------------------------------------------------------
void /*noreturn*/ sub_427E20()
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
// 0x427E90 sub_427E90
// ------------------------------------------------------------
HGDIOBJ /*usercall*/ sub_427E90@<eax>(int *a1@<ecx>, double a2@<st0>)
{
  HGDIOBJ result; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7

  result = (HGDIOBJ)a1[11];
  if ( result != nullptr )
  {
    result = (HGDIOBJ)a1[26];
    if ( result != nullptr )
    {
      v4 = a1[13];
      v5 = 0;
      if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 40))(v4, 17) != 0 )
        v5 = a1[13];
      sub_48CA20(5, 0);
      sub_45E740(5);
      sub_48CA20(5, 1);
      sub_48CA20(4, 0);
      sub_45E740(4);
      sub_48CA20(4, 1);
      sub_48CA20(3, 0);
      sub_45E740(3);
      sub_48CA20(3, 1);
      sub_48CA20(2, 0);
      sub_45E740(2);
      sub_48CA20(2, 1);
      if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 776))(v5, 5) != 0 )
        sub_496DD0(1);
      sub_48CA20(1, 0);
      sub_45E740(1);
      sub_48CA20(1, 1);
      sub_48CA20(0, 0);
      sub_45E740(0);
      sub_48CA20(0, 1);
      if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 776))(v5, 5) != 0 )
      {
        sub_496DD0(0);
      }
      else
      {
        v6 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4);
        if ( v6 == 8 || v6 == 9 )
          sub_459190(0);
      }
      sub_4271B0((int)a1, a2);
      sub_426080((int)a1, v7);
      sub_426200((int)a1);
      sub_426D20((int)a1);
      sub_425DA0((int)a1, v8);
      sub_425F10((int)a1, v9);
      sub_425A30(a1);
      sub_424A60(a1);
      result = *(HGDIOBJ *)(dword_8F7A24 + 12);
      if ( result == (HGDIOBJ)4 || result == (HGDIOBJ)6 )
        return sub_427A00((int)a1, v10);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x428050 sub_428050
// ------------------------------------------------------------
char /*thiscall*/ sub_428050(int *this, int a2, char a3, float *a4)
{
  int v4; // ebx
  int *v6; // eax
  int v7; // eax
  int v8; // edx
  int v10; // [esp+Ch] [ebp-4h]
  int *v11; // [esp+18h] [ebp+8h]

  v4 = 0;
  v10 = a2 + 1;
  if ( a2 + 1 <= 0 )
  {
LABEL_8:
    v7 = *(this + 62);
    if ( v7 < 20 || *(this + 63) < 8 )
    {
      if ( v7 < 10 || *(this + 63) < 4 )
      {
        if ( v7 >= 2 && *(this + 63) >= 2 )
          LOBYTE(v7) = (uint8_t)sub_432EA0("R_HK2_3GOOD", -1, 0, 0);
      }
      else
      {
        LOBYTE(v7) = (uint8_t)sub_432EA0("R_HK2_2GOOD", -1, 0, 0);
      }
    }
    else
    {
      LOBYTE(v7) = (uint8_t)sub_432EA0("R_HK2_1GOOD", -1, 0, 0);
    }
  }
  else
  {
    while ( 1 )
    {
      v6 = this + 7 * v4;
      v11 = v6;
      *((uint8_t *)v6 + 269) = 0;
      *((uint8_t *)v6 + 270) = 0;
      sub_698F90((int)(v6 + 64), 1500, 0);
      LOBYTE(v7) = a3;
      if ( a3 != 0 )
        break;
      v8 = *(this + v4 + 62) + 1;
      *(this + v4 + 62) = v8;
      if ( v8 >= dword_6C38AC[v4] )
      {
        *(this + v4 + 78) = v8;
        *((uint8_t *)v11 + 333) = 0;
        *((uint8_t *)v11 + 334) = 0;
        sub_698F90((int)(v11 + 80), 3000, 0);
      }
      if ( v4 == 1 )
      {
        sub_424530(
          0x40000000,
          300,
          1000,
          (uint64_t)(a4[3] * 0.5 + *a4),
          (uint64_t)(a4[4] * 0.5 + a4[1]),
          (uint64_t)(a4[5] * 0.5 + a4[2]),
          1);
        sub_4278D0(0, 0);
      }
      if ( ++v4 >= v10 )
        goto LABEL_8;
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x4281D0 sub_4281D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4281D0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x7FFFFFF )
    sub_427E20(this);
  v4 = (char *)operator new(32 * a2);
  *(this + 3) = &v4[32 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x428220 sub_428220
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_428220(int this, int Src, unsigned int a3, int *a4)
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
      sub_427E20(this);
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
// 0x428400 CNRDStage__vmt0
// ------------------------------------------------------------
HGDIOBJ /*userpurge*/ CNRDStage__vmt0@<eax>(int *a1@<ecx>, double a2@<st0>, void *a3)
{
  HGDIOBJ result; // eax

  result = a3;
  if ( a3 == (void *)a1[9] )
    return sub_427E90(a1, a2);
  if ( a3 == (void *)a1[10] && a1[27] != 0 )
    return (HGDIOBJ)sub_472B80();
  return result;
}



// ------------------------------------------------------------
// 0x428430 sub_428430
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_428430(int *this, int *a2)
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
    return sub_428220((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x428480 sub_428480
// ------------------------------------------------------------
int /*thiscall*/ sub_428480(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 32 )
      sub_501490(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4284C0 sub_4284C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4284C0(uint32_t *this, int a2, int a3)
{
  int v3; // esi
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // esi
  int v12; // ebx
  int v13; // ecx
  unsigned int v14; // esi
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  int v21; // ecx
  unsigned int v22; // ebx
  int v23; // ecx
  int v24; // edx
  int result; // eax
  int v26; // edx
  int v27; // [esp+20h] [ebp-44h]
  int v28; // [esp+24h] [ebp-40h]
  int v29; // [esp+28h] [ebp-3Ch]
  int v30; // [esp+2Ch] [ebp-38h]
  int i; // [esp+34h] [ebp-30h]
  uint32_t v32[3]; // [esp+38h] [ebp-2Ch] BYREF
  int v33; // [esp+44h] [ebp-20h] BYREF
  int v34; // [esp+48h] [ebp-1Ch] BYREF
  int v35; // [esp+54h] [ebp-10h]
  int v36; // [esp+60h] [ebp-4h]
  int v37; // [esp+6Ch] [ebp+8h]

  v3 = a3;
  v5 = *(this + 28);
  v6 = *(this + 29);
  v7 = *(this + 11);
  v28 = v5;
  v35 = *(this + 26);
  v8 = *(this + 27);
  *(this + 28) = a2;
  *(this + 29) = v3;
  v27 = v6;
  v29 = v7;
  sub_425500(*(uint32_t *)(dword_99FBC4 + 4 * (a2 + v3 * *(uint32_t *)(*(uint32_t *)(v8 + 168) + 8 * dword_99FB78))));
  v9 = *(uint32_t *)(dword_99FBD4 + 4 * (a2 + v3 * *(uint32_t *)(*(uint32_t *)(*(this + 27) + 168) + 8 * dword_99FB78)));
  *(this + 26) = v9;
  if ( v9 != 0 )
    *(uint32_t *)(v9 + 132) = this;
  v10 = *(this + 11);
  if ( v10 != 0 )
    sub_48E870(v10, *(this + 26));
  *(this + 329) = 0;
  for ( i = 16; i < 32; i += 4 )
  {
    v11 = *(uint32_t *)(i + dword_8F850C);
    v30 = v11;
    if ( v11 != 0 )
    {
      v12 = *(uint32_t *)(v11 + 196);
      if ( v12 != 0 )
      {
        if ( v35 != 0 )
        {
          if ( (uint8_t)sub_45E680(v12) == 0 )
            continue;
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 1196))(v12) != 0 )
        {
          continue;
        }
        v36 = 0;
        if ( v35 != 0 )
        {
          if ( *(this + 26) != 0 )
          {
            v13 = *(uint32_t *)(v35 + 120);
            v37 = v13 != 0 ? (*(uint32_t *)(v35 + 124) - v13) >> 2 : 0;
            v14 = 0;
            if ( v37 > 0 )
            {
              v15 = v35;
              do
              {
                v16 = *(uint32_t *)(v15 + 120);
                if ( v16 != 0 && v14 < (*(uint32_t *)(v15 + 124) - v16) >> 2 )
                {
                  v32[0] = *(uint32_t *)(v16 + 4 * v14);
                  if ( v32[0] != 0 && *(uint32_t *)(v32[0] + 668) == v12 && *(uint32_t *)(v32[0] + 672) != 0 )
                  {
                    sub_428430(v32);
                    v15 = v35;
                  }
                }
                ++v14;
              }
              while ( (int)v14 < v37 );
            }
          }
          sub_45F1E0(v12);
          v11 = v30;
        }
        v17 = *(this + 26);
        if ( v17 != 0 )
          sub_45FE80(v17, (int)this, 273, *(uint16_t *)(v11 + 4), v12, 0, 0);
        v33 = 0;
        v34 = 0;
        if ( v29 != 0 )
        {
          v18 = *(this + 28);
          if ( v28 >= v18 )
          {
            if ( v28 <= v18 )
              *(this + 329) = (v27 >= *(this + 29)) + 2;
            else
              *(this + 329) = 1;
          }
          else
          {
            *(this + 329) = 0;
          }
          sub_48C2A0(
            (uint32_t *)*(this + 11),
            &v33,
            &v34,
            *(this + 329),
            v12,
            *(uint32_t *)*(this + 11) * *(uint16_t *)(v11 + 4));
        }
        else
        {
          sub_48C330((uint32_t *)*(this + 11), &v33, &v34, v12, *(uint32_t *)*(this + 11) * *(uint16_t *)(v11 + 4));
        }
        if ( v35 != 0 && *(this + 26) != 0 )
          v32[2] = 0;
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v12 + 112))(v12, v33, v34, 0);
        v19 = *(this + 329);
        if ( v19 != 0 )
        {
          if ( v19 == 1 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v12 + 148))(v12, 0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 148))(v12, 1);
        }
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v12 + 228))(v12, 2, -1, 0);
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 1120))(v12);
        if ( v20 != 0 )
        {
          if ( v35 != 0 )
            sub_45F1E0(v20);
          v21 = *(this + 26);
          if ( v21 != 0 )
            sub_45FE80(v21, (int)this, 65, *(uint16_t *)(v11 + 4), v20, 0, 0);
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v20 + 228))(v20, 2, -1, 0);
        }
        v36 = -1;
      }
    }
  }
  if ( v29 != 0 )
    *(uint8_t *)(v29 + 472) = 0;
  sub_44F080(dword_8F8528);
  v22 = 0;
  while ( 1 )
  {
    v23 = *(this + 26);
    v24 = *(uint32_t *)(v23 + 8);
    result = v24 != 0 ? (*(uint32_t *)(v23 + 12) - v24) >> 2 : 0;
    if ( (int)v22 >= result )
      break;
    v26 = *(uint32_t *)(v23 + 8);
    if ( v26 != 0 && v22 < (*(uint32_t *)(v23 + 12) - v26) >> 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v26 + 4 * v22) + 320))(*(uint32_t *)(v26 + 4 * v22));
      ++v22;
    }
    else
    {
      (*(void (**)(void))(MEMORY[0] + 320))();
      ++v22;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x428AD0 sub_428AD0
// ------------------------------------------------------------
void /*thiscall*/ sub_428AD0(uint32_t *this)
{
  int v1; // eax
  uint32_t *v2; // edi
  int v3; // eax
  int i; // esi
  int v5; // ebx
  int v6; // ecx
  int v7; // ebx
  int v8; // esi
  int v9; // eax
  char *v10; // edi
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // ecx
  char *v15; // edx
  char *v16; // esi
  void *v17; // ebx
  int v18; // eax
  int v19; // esi
  int v20; // ecx
  BOOL v21; // ecx
  unsigned int j; // ebx
  int v23; // ecx
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // ecx
  int v28; // ecx
  int v29; // edx
  int v30; // esi
  int v31; // eax
  char v32; // al
  int v33; // esi
  int v34; // esi
  int v35; // [esp-10h] [ebp-54h]
  int v36; // [esp-10h] [ebp-54h]
  int v37; // [esp-Ch] [ebp-50h]
  int v38; // [esp-Ch] [ebp-50h]
  void *v39[4]; // [esp+4h] [ebp-40h] BYREF
  void *Block; // [esp+18h] [ebp-2Ch]
  char *v41; // [esp+1Ch] [ebp-28h]
  int v42; // [esp+20h] [ebp-24h]
  int v43; // [esp+24h] [ebp-20h] BYREF
  int v44; // [esp+28h] [ebp-1Ch]
  int v45; // [esp+2Ch] [ebp-18h]
  int v46; // [esp+30h] [ebp-14h]
  uint32_t *v47; // [esp+34h] [ebp-10h]
  int v48; // [esp+40h] [ebp-4h]

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  v2 = this;
  v47 = this;
  if ( v1 == 3 )
  {
    v3 = *(this + 26);
    if ( v3 != 0 && *(this + 11) != 0 )
    {
      if ( *(uint8_t *)(v3 + 152) != 0 )
      {
        *(this + 314) = 1;
        return;
      }
      if ( (uint8_t)sub_423AE0(*(this + 28), *(this + 29)) == 0 )
      {
        Block = nullptr;
        v41 = nullptr;
        v42 = 0;
        v48 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v43 = *(uint32_t *)(i + dword_8F850C);
          v5 = v43;
          if ( v43 != 0 )
          {
            v6 = *(uint32_t *)(v43 + 196);
            if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 724))(v6) == 0 )
            {
              sub_428430(&v43);
              (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v5 + 196) + 1228))(*(uint32_t *)(v5 + 196), 4);
            }
          }
        }
        v7 = 0;
        memset(v39, 0, sizeof(v39));
        v8 = 400;
        v46 = 0;
        v45 = 4;
        v44 = 400;
        do
        {
          if ( sub_48C220((uint8_t *)v2[11], v7) )
          {
            v9 = v2[11];
            v10 = (char *)Block;
            v11 = v8 + v9;
            v43 = v11;
            if ( Block != v41 )
            {
              while ( 1 )
              {
                v12 = *(uint32_t *)(*(uint32_t *)v10 + 196);
                v37 = v11;
                v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
                v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 120))(v12);
                if ( (uint8_t)sub_48C0A0(v13, v35, v37) == 1 )
                {
                  v14 = v47[314];
                  v15 = (char *)v39[v7] + 1;
                  v39[v7] = v15;
                  v16 = v15;
                  if ( v14 != 1 )
                    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*(uint32_t *)v10 + 196) + 1228))(
                      *(uint32_t *)(*(uint32_t *)v10 + 196),
                      v7);
                  if ( (int)v16 > v46 )
                  {
                    ++v46;
                    v45 = v7;
                  }
                }
                v10 += 4;
                if ( v10 == v41 )
                  break;
                v11 = v43;
              }
              v8 = v44;
            }
            v2 = v47;
          }
          v8 += 16;
          ++v7;
          v44 = v8;
        }
        while ( v8 < 464 );
        v17 = Block;
        if ( Block != nullptr )
          v18 = (v41 - (uint8_t *)Block) >> 2;
        else
          v18 = 0;
        v19 = v46;
        v46 = v18 == v46;
        if ( Block != nullptr )
          v20 = (v41 - (uint8_t *)Block) >> 2;
        else
          v20 = 0;
        v21 = (int)(uint64_t)((double)(unsigned int)v20 * 0.5 + 1.0) <= v19;
        v43 = 0;
        v44 = v21;
        if ( v21 )
        {
          for ( j = 0; ; ++j )
          {
            v23 = v2[26];
            v24 = *(uint32_t *)(v23 + 8);
            v25 = v24 != 0 ? (*(uint32_t *)(v23 + 12) - v24) >> 2 : 0;
            if ( (int)j >= v25 )
              break;
            v26 = *(uint32_t *)(v23 + 8);
            if ( v26 != 0 && j < (*(uint32_t *)(v23 + 12) - v26) >> 2 )
              v27 = *(uint32_t *)(v26 + 4 * j);
            else
              v27 = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v27 + 40))(v27, 289) != 0 )
            {
              v28 = v2[26];
              v29 = *(uint32_t *)(v28 + 8);
              if ( v29 != 0 && j < (*(uint32_t *)(v28 + 12) - v29) >> 2 )
                v30 = *(uint32_t *)(v29 + 4 * j);
              else
                v30 = 0;
              v38 = v47[11] + 16 * (v45 + 25);
              v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 124))(v30);
              v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 120))(v30);
              v32 = sub_48C0A0(v31, v36, v38);
              v2 = v47;
              if ( v32 == 1 )
              {
                v43 = 1;
                break;
              }
            }
          }
          v17 = Block;
          v21 = v44;
        }
        switch ( v2[314] )
        {
          case 0:
            if ( v46 == 1 )
              goto LABEL_59;
            if ( v21 )
            {
              sub_698F90((int)(v2 + 315), 0, 0);
              v2[314] = 2;
            }
            goto LABEL_74;
          case 1:
            if ( !v21 )
              goto LABEL_61;
            goto LABEL_74;
          case 2:
            if ( v46 == 1 )
              goto LABEL_59;
            if ( v21 )
            {
              if ( v21 && sub_699000((int)(v2 + 315)) > 5000 )
              {
LABEL_59:
                sub_698F90((int)(v2 + 322), 0, 0);
                v2[314] = 3;
              }
            }
            else
            {
LABEL_61:
              *((uint8_t *)v2 + 1273) = 0;
              *((uint8_t *)v2 + 1274) = 0;
              *((uint8_t *)v2 + 1301) = 0;
              *((uint8_t *)v2 + 1302) = 0;
              v2[314] = 0;
            }
LABEL_74:
            if ( v17 != nullptr )
              j__free(v17);
            return;
          case 3:
            if ( v43 != 0 )
            {
              if ( sub_699000((int)(v2 + 322)) > 2000 )
                v2[314] = 4;
            }
            else
            {
              v2[314] = 4;
            }
            goto LABEL_74;
          case 4:
            v33 = dword_8F850C;
            if ( sub_456480(dword_8F850C) == -1 )
              v34 = 0;
            else
              v34 = *(uint32_t *)(v33 + 4 * sub_456480(v33) + 16);
            if ( v34 == sub_429830((uint16_t)word_77F804) )
              sub_48C680(v45);
            goto LABEL_74;
          default:
            goto LABEL_74;
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x428F30 sub_428F30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_428F30(uint32_t *this, int a2, int a3)
{
  sub_425120();
  *this = &vftbl_CNRDObjectParticleCreater;
  *(this + 63) = 0;
  *(this + 64) = 0;
  *(this + 65) = 0;
  *(this + 74) = 15;
  *(this + 73) = 0;
  *((uint8_t *)this + 276) = 0;
  sub_498190(this);
  sub_497E40(szPassword, a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x428FC0 CNRDObjectParticleCreater__vmt60
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt60(uint32_t *this, int a2)
{
  *(this + 59) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x428FD0 CNRDObjectParticleCreater__vmt68
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt68(uint32_t *this, int a2)
{
  *(this + 60) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x428FE0 ?GetIScheduler@SchedulerBase@details@Concurrency@@QAEPAUIScheduler@3@XZ
// ------------------------------------------------------------
struct Concurrency::IScheduler */*thiscall*/ Concurrency::details::SchedulerBase::GetIScheduler(
        Concurrency::details::SchedulerBase *this)
{
  return *((struct Concurrency::IScheduler **)this + 60);
}



// ------------------------------------------------------------
// 0x428FF0 CNRDObjectParticleCreater__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt70(uint32_t *this, int a2)
{
  *(this + 67) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x429000 CNRDObjectParticleCreater__vmt74
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt74(uint32_t *this)
{
  return *(this + 67);
}



// ------------------------------------------------------------
// 0x429010 CNRDObjectParticleCreater__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDObjectParticleCreater__vmt0(void *Block, char a2)
{
  sub_429040();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x429040 sub_429040
// ------------------------------------------------------------
void /*thiscall*/ sub_429040(int this)
{
  *(uint32_t *)this = &vftbl_CNRDObjectParticleCreater;
  nullsub_3();
  if ( *(uint32_t *)(this + 296) >= 0x10u )
    j__free(*(void **)(this + 276));
  *(uint32_t *)(this + 296) = 15;
  *(uint32_t *)(this + 292) = 0;
  *(uint8_t *)(this + 276) = 0;
  sub_428480(this + 248);
  sub_425350((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x4290D0 sub_4290D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4290D0(uint32_t *this)
{
  void *v2; // eax
  int v3; // eax
  void *v4; // eax
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  uint8_t *v8; // esi
  uint8_t *v9; // eax
  uint8_t *v10; // esi
  int v11; // ebx
  int v12; // ecx
  bool v13; // zf
  uint8_t *v14; // eax
  uint8_t *v15; // esi
  int v16; // edi
  uint8_t *v17; // eax
  uint32_t *v18; // eax
  uint32_t *v19; // eax
  uint8_t *v20; // eax
  uint8_t *v21; // edi
  int v22; // ebx
  uint8_t *v23; // eax
  uint8_t *v24; // edi
  int v25; // ebx
  uint8_t *v26; // eax
  uint8_t *v27; // edi
  int v28; // ebx
  uint8_t *v29; // eax
  uint8_t *v30; // edi
  int v31; // ebx
  int result; // eax
  void *Block; // [esp+14h] [ebp-20h]
  int v35; // [esp+18h] [ebp-1Ch]
  int *v36; // [esp+1Ch] [ebp-18h]
  int i; // [esp+20h] [ebp-14h]
  int v38; // [esp+24h] [ebp-10h]

  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = 0;
  *(this + 9) = v3;
  *(uint32_t *)(v3 + 28) = 640;
  *(uint32_t *)(v3 + 32) = 480;
  *(uint32_t *)(*(this + 9) + 68) = this;
  v4 = operator new(0x68u);
  if ( v4 != nullptr )
    v5 = sub_426BD0(v4);
  else
    v5 = 0;
  *(this + 10) = v5;
  *(uint32_t *)(v5 + 68) = this;
  v38 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 120);
  v36 = this + 116;
  v6 = this + 94;
  v35 = 2;
  do
  {
    v7 = -1;
    for ( i = 3; i != 0; --i )
    {
      v8 = operator new(0x2Cu);
      if ( v8 != nullptr )
      {
        Block = (void *)dword_79C0B0;
        v8[4] = 0;
        *(uint32_t *)v8 = &nengine::CNNumberSet::`vftable';
        sub_699E20(v8);
        sub_699E40(Block, v38, v7, 5);
      }
      else
      {
        v8 = nullptr;
      }
      *v6 = v8;
      *((uint32_t *)v8 + 9) = 2;
      *(uint32_t *)(*v6++ + 40) = -6;
      v7 += 11;
    }
    v9 = operator new(0x2Cu);
    v10 = v9;
    if ( v9 != nullptr )
    {
      v11 = dword_79C0B0;
      v9[4] = 0;
      *(uint32_t *)v9 = &nengine::CNNumberSet::`vftable';
      sub_699E20(v9);
      sub_699E40(v11, v38, 32, 10);
    }
    else
    {
      v10 = nullptr;
    }
    *v36 = (int)v10;
    *((uint32_t *)v10 + 9) = 2;
    v12 = *v36++;
    v13 = v35 == 1;
    *(uint32_t *)(v12 + 40) = -4;
    --v35;
  }
  while ( !v13 );
  v14 = operator new(0x2Cu);
  v15 = v14;
  if ( v14 != nullptr )
  {
    v16 = dword_79C0B0;
    v14[4] = 0;
    *(uint32_t *)v14 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v14);
    sub_699E40(v16, v38, 87, 10);
    v17 = v15;
  }
  else
  {
    v17 = nullptr;
  }
  *(this + 147) = v17;
  *((uint32_t *)v17 + 9) = 0;
  *(uint32_t *)(*(this + 147) + 40) = -4;
  v18 = operator new(0x12Cu);
  if ( v18 != nullptr )
    v19 = sub_428F30(v18, (int)"Common/Etc/Particle/finishfx00.ptl", 0);
  else
    v19 = nullptr;
  *(this + 209) = v19;
  v20 = operator new(0x2Cu);
  v21 = v20;
  if ( v20 != nullptr )
  {
    v22 = dword_79C0B0;
    v20[4] = 0;
    *(uint32_t *)v20 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v20);
    sub_699E40(v22, v38, 32, 10);
  }
  else
  {
    v21 = nullptr;
  }
  *(this + 156) = v21;
  *((uint32_t *)v21 + 9) = 0;
  *(uint32_t *)(*(this + 156) + 40) = -4;
  v23 = operator new(0x2Cu);
  v24 = v23;
  if ( v23 != nullptr )
  {
    v25 = dword_79C0B0;
    v23[4] = 0;
    *(uint32_t *)v23 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v23);
    sub_699E40(v25, v38, 32, 10);
  }
  else
  {
    v24 = nullptr;
  }
  *(this + 165) = v24;
  *((uint32_t *)v24 + 9) = 0;
  *(uint32_t *)(*(this + 165) + 40) = -4;
  v26 = operator new(0x2Cu);
  v27 = v26;
  if ( v26 != nullptr )
  {
    v28 = dword_79C0B0;
    v26[4] = 0;
    *(uint32_t *)v26 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v26);
    sub_699E40(v28, v38, 122, 10);
  }
  else
  {
    v27 = nullptr;
  }
  *(this + 197) = v27;
  *((uint32_t *)v27 + 9) = 0;
  *(uint32_t *)(*(this + 197) + 40) = -4;
  v29 = operator new(0x2Cu);
  v30 = v29;
  if ( v29 != nullptr )
  {
    v31 = dword_79C0B0;
    v29[4] = 0;
    *(uint32_t *)v29 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v29);
    result = sub_699E40(v31, v38, 121, 10);
    *(this + 198) = v30;
  }
  else
  {
    *(this + 198) = 0;
    return 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4294E0 sub_4294E0
// ------------------------------------------------------------
void /*usercall*/ sub_4294E0(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // ecx
  uint32_t *v5; // ecx
  unsigned int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // edi
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // ecx
  int v16; // edx
  int v17; // eax
  int v20; // [esp+4h] [ebp-4h]

  v4 = *(uint32_t *)(a1 + 52);
  if ( v4 != 0 )
  {
    flt_77FD6C = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 120))(v4);
    flt_77FD70 = (float)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 52) + 124))(*(uint32_t *)(a1 + 52));
    flt_77FD74 = (float)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 52) + 128))(*(uint32_t *)(a1 + 52));
  }
  sub_483CF0();
  v5 = *(uint32_t **)(a1 + 44);
  if ( v5 != nullptr && *(uint8_t *)(a1 + 48) == 0 && *(uint32_t *)(dword_8F7A24 + 12) != 2 && dword_8F7C04 != 0 )
  {
    sub_48C8E0(v5);
    *(uint8_t *)(a1 + 48) = 1;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    {
      v6 = 0;
      v20 = sub_4250E0(*(uint32_t **)(a1 + 104));
      if ( v20 > 0 )
      {
        do
        {
          v7 = *(uint32_t *)(a1 + 104);
          v8 = *(uint32_t *)(v7 + 8);
          if ( v8 != 0 && v6 < (*(uint32_t *)(v7 + 12) - v8) >> 2 )
            v9 = *(uint32_t *)(v8 + 4 * v6);
          else
            v9 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 34) != 0 )
          {
            v10 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v9 + 340))(v9, a2, a3);
            v11 = *(uint32_t *)(v10 + 124);
            v12 = v10 + 100;
            if ( v11 < 0x10 )
              v13 = v12 + 4;
            else
              v13 = *(uint32_t *)(v12 + 4);
            a3 = 10000;
            a2 = 0;
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v9 + 212))(v9, v13, -1);
          }
          ++v6;
        }
        while ( (int)v6 < v20 );
      }
    }
  }
  if ( *(uint32_t *)(a1 + 1324) != 0 && *(uint32_t *)(a1 + 1352) != 0 )
  {
    v14 = *(uint32_t *)(a1 + 1352);
    if ( sub_699000(a1 + 1328) >= v14 )
      sub_426B10((uint32_t *)a1, 0, 0);
  }
  if ( *(uint32_t *)(a1 + 104) != 0 )
    sub_45F6C0();
  sub_428AD0((int *)a1);
  sub_4241E0(a1);
  sub_424170((uint32_t *)a1);
  v15 = *(uint32_t *)(a1 + 244);
  v16 = *(uint32_t *)(a1 + 240);
  *(uint32_t *)(a1 + 192) = *(uint32_t *)(a1 + 236);
  v17 = *(uint32_t *)(a1 + 52);
  *(uint32_t *)(a1 + 196) = v16 + v15;
  if ( v17 != 0 && *(uint32_t *)(a1 + 44) != 0 )
    sub_48C500(v17);
  sub_425570(a1);
  sub_424C50(a1);
  if ( *(uint32_t *)(a1 + 1224) == 0 )
    sub_424B40(a1);
  sub_427C20((uint32_t *)a1);
}



// ------------------------------------------------------------
// 0x4296C0 sub_4296C0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4296C0(uint32_t *this, uint32_t *a2)
{
  return *this != *a2;
}



// ------------------------------------------------------------
// 0x4296E0 sub_4296E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4296E0(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 21) == 0 )
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
// 0x429740 sub_429740
// ------------------------------------------------------------
char /*stdcall*/ sub_429740(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_429740(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x429780 sub_429780
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429780(int *this, uint32_t *a2, int a3)
{
  int v3; // esi

  v3 = *this;
  sub_41C5E0(this);
  *a2 = v3;
  return a2;
}



// ------------------------------------------------------------
// 0x4297A0 sub_4297A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4297A0(uint32_t *this)
{
  uint32_t *v2; // ecx
  uint32_t *v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void *i; // ebx
  uint32_t *v6; // edi
  uint32_t *v7; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  v2 = (uint32_t *)*(this + 2);
  v3 = (uint32_t *)*v2;
  v9 = (uint32_t *)*v2;
  if ( v9 != v2 )
  {
    do
    {
      v4 = (void (/*thiscall*/ ***)(uint32_t, int))v3[4];
      if ( v4 != nullptr )
        (**v4)(v4, 1);
      sub_41C5E0(&v9);
      v3 = v9;
    }
    while ( v9 != (uint32_t *)*(this + 2) );
  }
  v6 = this + 1;
  v7 = *(uint32_t **)(*(this + 2) + 4);
  for ( i = v7; *((uint8_t *)v7 + 21) == 0; i = v7 )
  {
    sub_429740((void **)v7[2]);
    v7 = (uint32_t *)*v7;
    j__free(i);
  }
  *(uint32_t *)(v6[1] + 4) = v6[1];
  result = (uint32_t *)v6[1];
  v6[2] = 0;
  *result = result;
  *(uint32_t *)(v6[1] + 8) = v6[1];
  return result;
}



// ------------------------------------------------------------
// 0x429830 sub_429830
// ------------------------------------------------------------
int /*thiscall*/ sub_429830(uint32_t *this, int a2)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  a2 = (uint16_t)a2;
  sub_472E30(&v4, &a2);
  if ( v4 == *(this + 2) )
    return 0;
  else
    return *(uint32_t *)(v4 + 16);
}



// ------------------------------------------------------------
// 0x429870 sub_429870
// ------------------------------------------------------------
int /*thiscall*/ sub_429870(int **this, const char *a2)
{
  int *v2; // eax
  int *v3; // ebx
  bool v4; // zf
  int *v7; // [esp+10h] [ebp-4h] BYREF

  v2 = *(this + 2);
  v3 = (int *)*v2;
  v4 = *v2 == (uint32_t)v2;
  v7 = (int *)*v2;
  if ( v4 )
    return 0;
  while ( sub_40BF00((std::_String_base *)(v3[4] + 16), 0, *(uint32_t *)(v3[4] + 36), a2, strlen(a2)) != 0 )
  {
    sub_41C5E0(&v7);
    v3 = v7;
    if ( v7 == *(this + 2) )
      return 0;
  }
  return v3[4];
}



// ------------------------------------------------------------
// 0x4298F0 sub_4298F0
// ------------------------------------------------------------
// attributes: thunk
uint32_t */*thiscall*/ sub_4298F0(uint32_t *this)
{
  return sub_4297A0(this);
}



// ------------------------------------------------------------
// 0x429900 sub_429900
// ------------------------------------------------------------
int /*thiscall*/ sub_429900(uint32_t *this)
{
  int v2; // eax
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  v5 = (uint16_t)word_77F804;
  sub_472E30(&v4, &v5);
  if ( v4 != *(this + 2) && (v2 = *(uint32_t *)(v4 + 16)) != 0 )
    return *(uint32_t *)(v2 + 120);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x429950 sub_429950
// ------------------------------------------------------------
int ***/*thiscall*/ sub_429950(uint32_t *this, int ***a2, int **a3)
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
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v26; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  v26 = this;
  if ( *((uint8_t *)a3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C5E0((int *)&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    v7 = v26;
    v8 = v26[1];
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
        v7 = v26;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v24 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v24 + 8) = sub_542490(v4);
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
  v12 = v26[1];
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
    v15 = v26;
    if ( v4 != *(int **)(v26[1] + 4) )
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
            v15 = v26;
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
            v15 = v26;
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
  v17 = v26[2];
  if ( v17 != 0 )
    v26[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x429C10 sub_429C10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429C10(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
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
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int v21; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  v6 = sub_5648C0(*(this + 1), a4, *(this + 1), a5, 0);
  v7 = (uint32_t *)*(this + 1);
  v21 = v6;
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
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);
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
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x429DC0 sub_429DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_429DC0(int this)
{
  int v2; // edx

  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(this + 28) = 4;
  *(uint32_t *)(this + 32) = 0;
  *(uint8_t *)(this + 36) = 1;
  sub_41A590(this + 37, v2, 0);
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0xFFFF;
  *(uint32_t *)(this + 60) = 0xFFFF;
  *(uint32_t *)(this + 64) = 0xFFFF;
  *(uint32_t *)(this + 68) = 0xFFFF;
  *(uint32_t *)(this + 72) = 0xFFFF;
  *(uint32_t *)(this + 76) = 0xFFFF;
  *(uint32_t *)(this + 80) = 0xFFFF;
  *(uint32_t *)(this + 84) = 0xFFFF;
  *(uint32_t *)(this + 88) = 0xFFFF;
  *(uint32_t *)(this + 92) = 0xFFFF;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  return sub_4015C0((void *)szPassword, 0);
}



// ------------------------------------------------------------
// 0x429E30 sub_429E30
// ------------------------------------------------------------
int /*thiscall*/ sub_429E30(int this)
{
  uint32_t *v2; // edi

  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  v2 = (uint32_t *)(this + 37);
  sub_41A630(this + 37);
  *v2 = &vftbl_clong;
  *(uint32_t *)(this + 140) = 15;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 120) = 0;
  sub_429DC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x429EB0 sub_429EB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429EB0(uint32_t *this, int16_t a2)
{
  *this = &vftbl_CNUser;
  sub_429E30((int)(this + 4));
  *(this + 40) = 0;
  *(this + 41) = 0;
  *((uint16_t *)this + 84) = 0;
  *(this + 44) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 0;
  sub_42A230(this);
  sub_42A250(a2);
  return this;
}



// ------------------------------------------------------------
// 0x429F40 CNUser__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNUser__vmt0(void *Block, char a2)
{
  sub_429F70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x429F70 sub_429F70
// ------------------------------------------------------------
int /*thiscall*/ sub_429F70(uint32_t *this)
{
  *this = &vftbl_CNUser;
  sub_42A260();
  return sub_41CBF0(this + 4);
}



// ------------------------------------------------------------
// 0x429FC0 sub_429FC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429FC0(uint32_t *this, int a2)
{
  uint16_t v3; // di
  int v4; // edx
  int v5; // esi
  uint32_t *result; // eax
  int v7; // esi
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int v9; // [esp+Ch] [ebp-4h] BYREF

  v3 = a2;
  v4 = 0;
  v5 = dword_8F850C + 16;
  while ( *(uint32_t *)v5 == 0 || *(uint16_t *)(*(uint32_t *)v5 + 4) != (uint16_t)a2 )
  {
    ++v4;
    v5 += 4;
    if ( v4 >= 4 )
      goto LABEL_7;
  }
  sub_456300(v4, 0);
LABEL_7:
  a2 = v3;
  result = (uint32_t *)sub_472E30(&v9, &a2);
  v7 = v9;
  if ( v9 != *(this + 2) )
  {
    v8 = *(void (/*thiscall*/ ****)(uint32_t, int))(v9 + 16);
    if ( v8 != nullptr )
      (**v8)(v8, 1);
    return sub_429950(this + 1, &a2, v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A040 sub_42A040
// ------------------------------------------------------------
int /*thiscall*/ sub_42A040(uint32_t *this, int a2, uint32_t *a3)
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
      v10 = *sub_429C10(this, &a3, 1, v5, (int)v3);
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
    v12 = *sub_429C10(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x42A100 sub_42A100
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42A100(void **this, uint16_t a2)
{
  uint32_t *v3; // ebx
  uint32_t *result; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  int v7; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h] BYREF
  uint8_t v9[4]; // [esp+14h] [ebp-14h] BYREF
  int v10; // [esp+18h] [ebp-10h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  v3 = this + 1;
  v10 = a2;
  sub_472E30(&Block, &v10);
  if ( Block == *(this + 2) || (result = *((uint32_t **)Block + 4)) == nullptr )
  {
    v5 = operator new(0xC8u);
    Block = v5;
    v6 = nullptr;
    v11 = 0;
    if ( v5 != nullptr )
      v6 = sub_429EB0(v5, a2);
    v11 = -1;
    v7 = a2;
    Block = v6;
    sub_42A040(v3, (int)v9, &v7);
    return v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A1B0 sub_42A1B0
// ------------------------------------------------------------
int /*cdecl*/ sub_42A1B0(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x42A1D0 KMessenger__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ KMessenger__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_KMessenger;
  sub_4989B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x42A200 sub_42A200
// ------------------------------------------------------------
int /*thiscall*/ sub_42A200(uint32_t *this)
{
  *this = &vftbl_KMessenger;
  return sub_4989B0();
}



// ------------------------------------------------------------
// 0x42A210 sub_42A210
// ------------------------------------------------------------
char */*cdecl*/ sub_42A210(int a1)
{
  return sub_422E70(a1 + 1207);
}



// ------------------------------------------------------------
// 0x42A230 sub_42A230
// ------------------------------------------------------------
int /*thiscall*/ sub_42A230(int this)
{
  *(uint16_t *)(this + 4) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x42A250 sub_42A250
// ------------------------------------------------------------
int16_t /*thiscall*/ sub_42A250(uint16_t *this, int16_t a2)
{
  *(this + 2) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x42A260 sub_42A260
// ------------------------------------------------------------
int /*thiscall*/ sub_42A260(int *this)
{
  int v2; // ecx
  uint32_t *v3; // edi
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int result; // eax
  int v6; // ecx
  uint32_t *v7; // edi
  int v8; // eax
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int v10; // [esp-4h] [ebp-10h]
  int v11; // [esp-4h] [ebp-10h]

  if ( *(this + 48) == dword_8F7C08 )
    dword_8F7C08 = 0;
  v2 = *(this + 48);
  if ( v2 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 80))(v2) != 0 )
    {
      v3 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 48) + 80))(*(this + 48)) + 132);
      v10 = *(this + 48);
      (*(void (**)(void))(*(uint32_t *)v10 + 80))();
      sub_45F1E0(v10);
      if ( v3 != nullptr && v3[13] == *(this + 48) )
        sub_424A40(v3, dword_8F7C08);
    }
    v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 48);
    if ( v4 != nullptr )
      (**v4)(v4, 1);
    *(this + 48) = 0;
  }
  result = *(this + 49);
  if ( result == dword_8F7C04 )
    dword_8F7C04 = 0;
  v6 = *(this + 49);
  if ( v6 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6);
    if ( result != 0 )
    {
      v7 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 49) + 80))(*(this + 49)) + 132);
      v11 = *(this + 49);
      (*(void (**)(void))(*(uint32_t *)v11 + 80))();
      result = sub_45F1E0(v11);
      if ( v7 != nullptr )
      {
        result = v7[13];
        if ( result == *(this + 49) )
        {
          v8 = sub_424310(v7, (uint8_t *)dword_8F7C04);
          result = sub_424A40(v7, v8);
        }
      }
    }
    v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 49);
    if ( v9 != nullptr )
      result = (**v9)(v9, 1);
    *(this + 49) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A380 sub_42A380
// ------------------------------------------------------------
char */*thiscall*/ sub_42A380(unsigned int *this, char a2)
{
  unsigned int v2; // eax

  if ( a2 != 0 )
    v2 = *(this + 41);
  else
    v2 = *(this + 40);
  sprintf(byte_8F7C20, "%d.%d.%d.%d", (uint8_t)v2, BYTE1(v2), BYTE2(v2), HIBYTE(v2));
  return byte_8F7C20;
}



// ------------------------------------------------------------
// 0x42A3D0 sub_42A3D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42A3D0(int this, int a2)
{
  int v3; // edi

  *(uint32_t *)(this + 196) = a2;
  if ( a2 != 0 )
  {
    v3 = *(uint16_t *)(this + 4);
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 36))(a2) + 4) = v3;
  }
  if ( *(uint16_t *)(this + 4) == (uint16_t)word_77F804 )
    dword_8F7C04 = *(uint32_t *)(this + 196);
}



// ------------------------------------------------------------
// 0x42A410 sub_42A410
// ------------------------------------------------------------
int /*thiscall*/ sub_42A410(uint32_t *this)
{
  return sub_418DD0(*(this + 29));
}



// ------------------------------------------------------------
// 0x42A430 sub_42A430
// ------------------------------------------------------------
int /*thiscall*/ sub_42A430(uint32_t *this)
{
  return sub_418DD0(*(this + 29));
}



// ------------------------------------------------------------
// 0x42A450 sub_42A450
// ------------------------------------------------------------
int /*thiscall*/ sub_42A450(void **this)
{
  *this = &vftbl_CNRDObject;
  sub_49A850();
  sub_660080(this + 44);
  if ( *(this + 36) != nullptr )
    j__free(*(this + 36));
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  sub_6569D0(this + 31);
  j__free(*(this + 32));
  *(this + 32) = nullptr;
  *(this + 16) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 68) = 0;
  *(this + 9) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 40) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  *this = &vftbl_KMessenger;
  return sub_4989B0(this);
}



// ------------------------------------------------------------
// 0x42A510 CNRDObject__vmt20
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt20(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // ecx
  int result; // eax

  v2 = this + 25;
  *v2 = *a2;
  v2[1] = a2[1];
  result = a2[2];
  v2[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x42A5B0 CNRDObject__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt54(uint8_t *this, char a2)
{
  *(this + 156) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x42A5C0 CNRDObject__vmt58
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt58(uint8_t *this)
{
  return *(this + 156);
}



// ------------------------------------------------------------
// 0x42A5D0 CNRDObject__vmt5C
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt5C(uint32_t *this, int a2)
{
  int v2; // edx
  int result; // eax

  v2 = *(this + 30);
  result = a2;
  *(this + 34) = a2;
  if ( v2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, a2);
  return result;
}



// ------------------------------------------------------------
// 0x42A5F0 CNRDObject__vmt78
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt78(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 116))(this, 0);
}



// ------------------------------------------------------------
// 0x42A620 CNRDObject__vmt88
// ------------------------------------------------------------
char /*stdcall*/ CNRDObject__vmt88(int a1, int a2, uint32_t *a3)
{
  if ( a3 != nullptr )
    *a3 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x42A640 CNRDObject__vmt9C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDObject__vmt9C(void *this, int a2)
{
  int v3; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  return abs32((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) - v3);
}



// ------------------------------------------------------------
// 0x42A670 CNRDObject__vmtA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDObject__vmtA0(void *this, int a2)
{
  int v3; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
  return abs32((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) - v3);
}



// ------------------------------------------------------------
// 0x42A6A0 CNRDObject__vmt8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt8(void *this, int a2, int a3)
{
  int v4; // eax
  int v6; // [esp-10h] [ebp-18h]
  int v7; // [esp-Ch] [ebp-14h]
  int v8; // [esp-8h] [ebp-10h]

  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
  v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  return sub_499240(v4, v6, v7, v8, a3);
}



// ------------------------------------------------------------
// 0x42A6E0 CNRDObject__vmtB0
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmtB0(void *this, int a2)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1
      && a2 > (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)
      || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0
      && a2 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
}



// ------------------------------------------------------------
// 0x42A730 CNRDObject__vmtB4
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmtB4(void *this, int a2)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1
      && a2 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)
      || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0
      && a2 > (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
}



// ------------------------------------------------------------
// 0x42A790 CNRDObject__vmtC4
// ------------------------------------------------------------
uint8_t /*thiscall*/ CNRDObject__vmtC4(unsigned int *this, int a2)
{
  uint8_t result; // al

  *(this + 30) = a2;
  if ( a2 != 0 )
  {
    sub_699070(a2, *(this + 23));
    result = *(uint8_t *)(a2 + 168);
    if ( result != 0 )
      return (uint8_t)sub_4938F0(a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A7D0 CNRDObject__vmtDC
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmtDC(uint8_t *this, char a2)
{
  *(this + 172) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x42A7E0 CNRDObject__vmtE0
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmtE0(uint8_t *this)
{
  return *(this + 172);
}



// ------------------------------------------------------------
// 0x42A7F0 CNRDObject__vmtE8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtE8(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t, int, uint32_t))(*(uint32_t *)this + 228))(this, 0, -1, 0);
}



// ------------------------------------------------------------
// 0x42A810 CNRDObject__vmtF0
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF0(uint32_t *this)
{
  return sub_699000((int)(this + 2)) - *(this + 52);
}



// ------------------------------------------------------------
// 0x42A830 CNRDObject__vmtF4
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF4(uint32_t *this)
{
  return *(this + 51);
}



// ------------------------------------------------------------
// 0x42A840 CNRDObject__vmtF8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF8(void *this)
{
  int v2; // edi

  v2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 244))(this);
  return v2 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 240))(this);
}



// ------------------------------------------------------------
// 0x42A860 CNRDObject__vmt100
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt100(uint32_t *this, int a2)
{
  return *(this + a2 + 54);
}



// ------------------------------------------------------------
// 0x42A880 CNRDObject__vmt108
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt108(uint8_t *this)
{
  return *(this + 232);
}



// ------------------------------------------------------------
// 0x42A8A0 CNRDObject__vmt114
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmt114(float *this)
{
  return *(this + 61) != 0.0;
}



// ------------------------------------------------------------
// 0x42A8D0 CNRDObject__vmt11C
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt11C(int this, char a2, int a3, char a4, int a5)
{
  *(uint8_t *)(this + 248) = a2;
  *(uint32_t *)(this + 252) = a3;
  *(uint8_t *)(this + 256) = a4;
  *(uint32_t *)(this + 260) = a5;
  return a4;
}



// ------------------------------------------------------------
// 0x42A930 CNRDObject__vmt68
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt68(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 36);
  if ( v2 != 0 && a2 < (*(this + 37) - v2) >> 2 )
    return *(uint32_t *)(*(this + 36) + 4 * a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x42A970 CNRDObject__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDObject__vmt0(void *Block, char a2)
{
  sub_42A450();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x42A9A0 sub_42A9A0
// ------------------------------------------------------------
void /*noreturn*/ sub_42A9A0()
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
// 0x42AA10 sub_42AA10
// ------------------------------------------------------------
void /*thiscall*/ sub_42AA10(int this)
{
  if ( *(uint32_t *)(this + 76) != 0 )
    j__free(*(void **)(this + 76));
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  if ( *(uint32_t *)(this + 60) != 0 )
    j__free(*(void **)(this + 60));
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
}



// ------------------------------------------------------------
// 0x42AA50 sub_42AA50
// ------------------------------------------------------------
char /*thiscall*/ sub_42AA50(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_42A9A0(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x42AAB0 sub_42AAB0
// ------------------------------------------------------------
char */*thiscall*/ sub_42AAB0(char *this)
{
  *(uint32_t *)this = &vftbl_KMessenger;
  sub_498AB0();
  *(uint32_t *)this = &vftbl_CNRDObject;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 4) = 0;
  *(this + 20) = 1;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *(this + 40) = 0;
  *((uint32_t *)this + 9) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 11) = 0;
  *(this + 48) = 1;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 13) = 0;
  *(this + 68) = 0;
  *((uint32_t *)this + 16) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 18) = 0;
  *(this + 76) = 1;
  *(this + 78) = 0;
  *(this + 77) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 27) = 1;
  *((uint32_t *)this + 32) = sub_433A60(this + 124);
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 0;
  sub_498B70((int)this);
  sub_499B40(this);
  return this;
}



// ------------------------------------------------------------
// 0x42ABC0 CNRDObject__vmt64
// ------------------------------------------------------------
int /*stdcall*/ CNRDObject__vmt64(char a1)
{
  return sub_42ABE0(&a1);
}



// ------------------------------------------------------------
// 0x42ABE0 sub_42ABE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42ABE0(int this, uint32_t *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  uint32_t *v4; // eax
  uint32_t *result; // eax

  v2 = *(uint32_t *)(this + 4);
  if ( v2 != 0 )
    v3 = (*(uint32_t *)(this + 8) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= (*(uint32_t *)(this + 12) - v2) >> 2 )
    return (uint32_t *)sub_42AC40(&a2, *(void **)(this + 8), a2);
  v4 = *(uint32_t **)(this + 8);
  *v4 = *a2;
  result = v4 + 1;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x42AC40 sub_42AC40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42AC40(uint32_t *this, uint32_t *a2, void *Src, int a4)
{
  int v5; // ecx
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) >> 2 != 0 )
    v6 = ((int)Src - v5) >> 2;
  else
    v6 = 0;
  sub_42AC90(Src, 1, a4);
  *a2 = *(this + 1) + 4 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x42AC90 sub_42AC90
// ------------------------------------------------------------
int */*thiscall*/ sub_42AC90(int this, char *Src, unsigned int a3, int *a4)
{
  int v5; // ecx
  int *result; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // edx
  unsigned int v10; // edi
  int v11; // edx
  int v12; // edx
  char *v13; // ebx
  int v14; // eax
  unsigned int v15; // edx
  int *v16; // ecx
  void *v17; // ecx
  int v18; // eax
  uint8_t *v19; // ebx
  int *v20; // edi
  unsigned int v21; // eax
  int v22; // edx
  char *v23; // esi
  char *v24; // eax
  void *v25; // [esp-18h] [ebp-38h]
  int v26; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v28; // [esp+10h] [ebp-10h]
  int v29; // [esp+1Ch] [ebp-4h]
  void *Srca; // [esp+28h] [ebp+8h]
  int v31; // [esp+2Ch] [ebp+Ch]
  size_t v32; // [esp+2Ch] [ebp+Ch]
  int v33; // [esp+30h] [ebp+10h]

  v5 = *a4;
  result = *(int **)(this + 4);
  v28 = &v26;
  Block = (void *)this;
  v33 = v5;
  if ( result != nullptr )
    v7 = (*(uint32_t *)(this + 12) - (int)result) >> 2;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( result != nullptr )
      v8 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_42A9A0(this);
    if ( result != nullptr )
      v9 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v20 = (int *)Src;
      v21 = (v19 - Src) >> 2;
      if ( v21 >= a3 )
      {
        Srca = (void *)(4 * a3);
        v23 = &v19[-4 * a3];
        v32 = 4 * ((int)(4 * a3) >> 2);
        v24 = (char *)memcpy_0(v19, v23, v32);
        *((uint32_t *)Block + 2) = &v24[v32];
        memcpy_0(&v19[-4 * ((v23 - (char *)v20) >> 2)], v20, 4 * ((v23 - (char *)v20) >> 2));
        for ( result = (int *)((char *)v20 + (uint32_t)Srca); v20 != result; ++v20 )
          *v20 = v33;
      }
      else
      {
        memcpy_0(&Src[4 * a3], Src, 4 * v21);
        memset32(*(void **)(this + 8), v33, a3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
        result = nullptr;
        v22 = 4 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        if ( Src != (char *)(v22 - 4 * a3) )
        {
          do
          {
            result = (int *)v33;
            *v20++ = v33;
          }
          while ( v20 != (int *)(v22 - 4 * a3) );
        }
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( result != nullptr )
        v11 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( result != nullptr )
          v12 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
        else
          v12 = 0;
        v10 = v12 + a3;
      }
      v13 = (char *)operator new(4 * v10);
      v25 = *(void **)(this + 4);
      Block = v13;
      v29 = 0;
      v14 = sub_433A30(v25, (int)Src, v13);
      v15 = a3;
      v16 = (int *)v14;
      while ( v15 != 0 )
      {
        *v16 = v33;
        v13 = (char *)Block;
        --v15;
        ++v16;
      }
      sub_433A30(Src, *(uint32_t *)(this + 8), (void *)(v14 + 4 * a3));
      v17 = *(void **)(this + 4);
      if ( v17 != nullptr )
        v18 = (*(uint32_t *)(this + 8) - (int)v17) >> 2;
      else
        v18 = 0;
      v31 = v18 + a3;
      if ( v17 != nullptr )
        j__free(v17);
      result = (int *)&v13[4 * v31];
      *(uint32_t *)(this + 12) = &v13[4 * v10];
      *(uint32_t *)(this + 8) = result;
      *(uint32_t *)(this + 4) = v13;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x42AF10 sub_42AF10
// ------------------------------------------------------------
void /*stdcall*/ sub_42AF10(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 88 )
    sub_42AA10(i);
}



// ------------------------------------------------------------
// 0x42AF40 sub_42AF40
// ------------------------------------------------------------
int /*thiscall*/ sub_42AF40(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 88 )
      sub_42AA10(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42AF90 sub_42AF90
// ------------------------------------------------------------
int /*thiscall*/ sub_42AF90(void **this)
{
  int result; // eax

  sub_493C80();
  sub_6569D0(this + 50);
  j__free(*(this + 51));
  *(this + 51) = nullptr;
  if ( *(this + 34) != nullptr )
    j__free(*(this + 34));
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  if ( *(this + 30) != nullptr )
    j__free(*(this + 30));
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  result = sub_42AF40(this + 10);
  *((uint8_t *)this + 4) = 0;
  *this = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x42B040 sub_42B040
// ------------------------------------------------------------
int /*thiscall*/ sub_42B040(void ***this)
{
  int result; // eax
  void **v3; // edi
  int v4; // edi
  int v5; // edi

  if ( *this != nullptr )
  {
    result = sub_4942D0();
    v3 = *this;
    if ( *this != nullptr )
    {
      sub_42AF90(*this);
      result = sub_657740(v3, 228);
    }
    *this = nullptr;
  }
  if ( *(this + 1) != nullptr )
  {
    result = sub_4942D0();
    v4 = (int)*(this + 1);
    if ( v4 != 0 )
    {
      sub_42AF90(*(this + 1));
      result = sub_657740(v4, 228);
    }
    *(this + 1) = nullptr;
  }
  if ( *(this + 2) != nullptr )
  {
    result = sub_4942D0();
    v5 = (int)*(this + 2);
    if ( v5 != 0 )
    {
      sub_42AF90(*(this + 2));
      result = sub_657740(v5, 228);
    }
    *(this + 2) = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B0F0 sub_42B0F0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B0F0(int this)
{
  sub_42AAB0((char *)this);
  *(uint32_t *)this = &vftbl_CNRDVirtualCharacter;
  *(uint32_t *)(this + 284) = 4;
  *(uint32_t *)(this + 288) = -1;
  *(uint8_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  `eh vector constructor iterator'((void *)(this + 380), 0x10u, 10, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 544) = 0;
  *(uint32_t *)(this + 548) = 0;
  *(uint32_t *)(this + 552) = 0;
  *(uint32_t *)(this + 608) = 15;
  *(uint32_t *)(this + 604) = 0;
  *(uint8_t *)(this + 588) = 0;
  sub_42F250(this);
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x42B1C0 CNRDVirtualCharacter__vmt150
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt150(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // ecx
  int result; // eax

  v2 = this + 71;
  *v2 = *a2;
  v2[1] = a2[1];
  result = a2[2];
  v2[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x42B1E0 IRDCollisionObject__vmt154
// ------------------------------------------------------------
char */*thiscall*/ IRDCollisionObject__vmt154(char *this)
{
  return this + 284;
}



// ------------------------------------------------------------
// 0x42B220 CNRDVirtualCharacter__vmt164
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDVirtualCharacter__vmt164(uint32_t *this)
{
  if ( *(this + 152) < 0x10u )
    return this + 147;
  else
    return (uint32_t *)*(this + 147);
}



// ------------------------------------------------------------
// 0x42B240 CNRDVirtualCharacter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDVirtualCharacter__vmt0(void *Block, char a2)
{
  sub_42B270();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x42B270 sub_42B270
// ------------------------------------------------------------
int /*thiscall*/ sub_42B270(int this)
{
  *(uint32_t *)this = &vftbl_CNRDVirtualCharacter;
  sub_431AE0();
  if ( *(uint32_t *)(this + 608) >= 0x10u )
    j__free(*(void **)(this + 588));
  *(uint32_t *)(this + 608) = 15;
  *(uint32_t *)(this + 604) = 0;
  *(uint8_t *)(this + 588) = 0;
  if ( *(uint32_t *)(this + 544) != 0 )
    j__free(*(void **)(this + 544));
  *(uint32_t *)(this + 544) = 0;
  *(uint32_t *)(this + 548) = 0;
  *(uint32_t *)(this + 552) = 0;
  `eh vector destructor iterator'((void *)(this + 380), 0x10u, 10, (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_42B040((void ***)(this + 296));
  return sub_42A450((void **)this);
}



// ------------------------------------------------------------
// 0x42B340 sub_42B340
// ------------------------------------------------------------
int /*thiscall*/ sub_42B340(int this)
{
  void *v2; // eax
  int v3; // eax
  int16_t v4; // cx
  int v5; // edi

  if ( *(uint32_t *)(this + 192) == 0 )
  {
    v2 = operator new(0x294u);
    if ( v2 != nullptr )
      v3 = sub_42B0F0((int)v2);
    else
      v3 = 0;
    v4 = *(uint16_t *)(this + 4);
    *(uint32_t *)(this + 192) = v3;
    if ( v4 == (uint16_t)word_77F804 )
      dword_8F7C08 = v3;
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 192) + 348))(*(uint32_t *)(this + 192), this + 16);
    v5 = *(uint16_t *)(this + 4);
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 192) + 36))(*(uint32_t *)(this + 192)) + 4) = v5;
  }
  return *(uint32_t *)(this + 192);
}



// ------------------------------------------------------------
// 0x42B3F0 sub_42B3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B3F0(void *this, float a2)
{
  uint64_t v3; // rax
  int v4; // edi

  v3 = (uint64_t)((double)sub_41A5E0((unsigned int)this) * a2);
  v4 = v3;
  sub_41A590((unsigned int)this, SHIDWORD(v3), v3);
  return v4;
}



// ------------------------------------------------------------
// 0x42B420 sub_42B420
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_42B420(int a1, int a2, int a3, int a4)
{
  int v4; // edx
  double v5; // st7
  float v7; // [esp+0h] [ebp-10h]
  float v8; // [esp+0h] [ebp-10h]
  float v9; // [esp+4h] [ebp-Ch]
  float v10; // [esp+4h] [ebp-Ch]

  v4 = a3 % (2 * a4);
  if ( v4 >= a4 )
  {
    v10 = (float)a1;
    v8 = (float)a2;
    v5 = sub_4049C0(v8, v10, v4 - a4, a4);
  }
  else
  {
    v9 = (float)a2;
    v7 = (float)a1;
    v5 = sub_4049C0(v7, v9, a3 % (2 * a4), a4);
  }
  return _ftol2(v5);
}



// ------------------------------------------------------------
// 0x42B480 sub_42B480
// ------------------------------------------------------------
char /*thiscall*/ sub_42B480(uint8_t *this, int a2, int a3)
{
  int v3; // ecx

  *(this + 1196) = 1;
  v3 = (int)(this + 1184);
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  return sub_698F90(v3, a3, -a2);
}



// ------------------------------------------------------------
// 0x42B4B0 ?_Get_future_error_what@std@@YAPBDH@Z
// ------------------------------------------------------------
const char */*cdecl*/ std::_Get_future_error_what(int a1)
{
  return (const char *)dword_8F7D28[a1];
}



// ------------------------------------------------------------
// 0x42B4C0 sub_42B4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B4C0(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 24) = 0;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = -1;
    *(uint32_t *)(this + 84) = 0;
    *(uint32_t *)(this + 88) = 0;
    *(uint32_t *)(this + 92) = 0;
    *(uint32_t *)(this + 124) = 0;
    *(uint32_t *)(this + 152) = 2;
    *(uint32_t *)(this + 76) = -1;
    *(uint8_t *)(this + 184) = 0;
    *(uint32_t *)(this + 188) = 0;
    *(uint32_t *)(this + 132) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B510 sub_42B510
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B510(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 8);
  return v1 == 2 || v1 == 3 || v1 == 4;
}



// ------------------------------------------------------------
// 0x42B530 sub_42B530
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B530(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 8);
  return v1 != 2 && v1 != 3 && v1 != 4;
}



// ------------------------------------------------------------
// 0x42B560 sub_42B560
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B560(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 8);
  return v1 == 2 || v1 == 3;
}



// ------------------------------------------------------------
// 0x42B580 sub_42B580
// ------------------------------------------------------------
int /*stdcall*/ sub_42B580(int a1, int a2)
{
  if ( a2 != sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, a1);
    off_77F3FC("@@REMOVE PEER : WARROOM");
  }
  if ( a2 != 0 && *(uint32_t *)(a2 + 196) != 0 )
    sub_45F1E0(*(uint32_t *)(a2 + 196));
  return sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
}



// ------------------------------------------------------------
// 0x42B5F0 sub_42B5F0
// ------------------------------------------------------------
char /*thiscall*/ sub_42B5F0(uint8_t *this)
{
  int v1; // ecx

  *(this + 108) = 1;
  v1 = (int)(this + 96);
  *(uint8_t *)(v1 + 13) = 0;
  *(uint8_t *)(v1 + 14) = 0;
  return sub_698F90(v1, 0, 0);
}



// ------------------------------------------------------------
// 0x42B610 sub_42B610
// ------------------------------------------------------------
void */*thiscall*/ sub_42B610(uint32_t *this, int ArgList)
{
  void *result; // eax

  off_77F3FC((char *)&byte_6C3EB0, ArgList);
  sub_49BDB0(0);
  sub_432EA0("GRENSELOS_TRUCE", -1, 0, 0);
  result = (void *)*(this + 22);
  if ( result == (void *)1 )
  {
    sub_49AA90("first battle end");
    result = dword_8F8528;
    *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B690 sub_42B690
// ------------------------------------------------------------
int /*stdcall*/ sub_42B690(int a1)
{
  int i; // esi
  int result; // eax
  int v3; // ecx

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 )
    {
      v3 = *(uint32_t *)(result + 196);
      if ( v3 != 0 )
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1200))(v3, a1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B6D0 sub_42B6D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42B6D0(int *this)
{
  int i; // esi
  int v3; // eax
  int v4; // ecx

  for ( i = 0; i < 8; ++i )
  {
    v3 = sub_578E80(i);
    if ( v3 != 0 )
    {
      v4 = *(uint32_t *)(v3 + 196);
      if ( v4 != 0 )
        sub_45FE80(*(this + 7), (int)this, 273, *(uint16_t *)(v3 + 4), v4, 0, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x42B720 sub_42B720
// ------------------------------------------------------------
int /*stdcall*/ sub_42B720(int a1, int a2)
{
  int i; // edi
  int result; // eax

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 && *(uint32_t *)(result + 196) != 0 )
    {
      sub_49C620(1, 1, 0);
      result = sub_49C5F0(1, 0, 0, a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B780 sub_42B780
// ------------------------------------------------------------
int /*stdcall*/ sub_42B780(int a1)
{
  int i; // esi
  int result; // eax
  int v3; // ecx

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 )
    {
      v3 = *(uint32_t *)(result + 196);
      if ( v3 != 0 )
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 604))(v3, a1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B7C0 sub_42B7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B7C0(uint32_t *this, int a2, int a3)
{
  *(this + 31) = a2;
  *(this + 32) = a3;
  *(this + 33) = 0;
  return a2;
}



// ------------------------------------------------------------
// 0x42B7E0 sub_42B7E0
// ------------------------------------------------------------
char */*thiscall*/ sub_42B7E0(char *this)
{
  *(uint32_t *)this = &off_6C3EE0;
  *(this + 8) = 0;
  *((uint32_t *)this + 1) = &off_6C2B88;
  *((uint32_t *)this + 3) = 0;
  *(this + 16) = 1;
  *(this + 18) = 0;
  *(this + 17) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *(this + 60) = 0;
  *((uint32_t *)this + 14) = &off_6C2B88;
  *((uint32_t *)this + 16) = 0;
  *(this + 68) = 1;
  *(this + 70) = 0;
  *(this + 69) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 18) = 0;
  sub_41A630(this + 120);
  *((uint32_t *)this + 30) = &clong::`vftable';
  sub_41A630(this + 134);
  *(uint32_t *)(this + 134) = &clong::`vftable';
  sub_41A630(this + 148);
  *((uint32_t *)this + 37) = &clong::`vftable';
  *(this + 168) = 0;
  *((uint32_t *)this + 41) = &off_6C2B88;
  *((uint32_t *)this + 43) = 0;
  *(this + 176) = 1;
  *(this + 178) = 0;
  *(this + 177) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 45) = 0;
  *(this + 212) = 0;
  *((uint32_t *)this + 52) = &off_6C2B88;
  *((uint32_t *)this + 54) = 0;
  *(this + 220) = 1;
  *(this + 222) = 0;
  *(this + 221) = 0;
  *((uint32_t *)this + 58) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 56) = 0;
  `eh vector constructor iterator'(this + 256, 0x1Cu, 2, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 320, 0x1Cu, 2, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 408, 0x1Cu, 2, sub_401170, sub_401000);
  *(this + 476) = 0;
  *((uint32_t *)this + 118) = &off_6C2B88;
  *((uint32_t *)this + 120) = 0;
  *(this + 484) = 1;
  *(this + 486) = 0;
  *(this + 485) = 0;
  *((uint32_t *)this + 124) = 0;
  *((uint32_t *)this + 123) = 0;
  *((uint32_t *)this + 122) = 0;
  *(this + 504) = 0;
  *((uint32_t *)this + 125) = &off_6C2B88;
  *((uint32_t *)this + 127) = 0;
  *(this + 512) = 1;
  *(this + 514) = 0;
  *(this + 513) = 0;
  *((uint32_t *)this + 131) = 0;
  *((uint32_t *)this + 130) = 0;
  *((uint32_t *)this + 129) = 0;
  *(this + 532) = 0;
  *((uint32_t *)this + 132) = &off_6C2B88;
  *((uint32_t *)this + 134) = 0;
  *(this + 540) = 1;
  *(this + 542) = 0;
  *(this + 541) = 0;
  *((uint32_t *)this + 138) = 0;
  *((uint32_t *)this + 137) = 0;
  *((uint32_t *)this + 136) = 0;
  *(this + 564) = 0;
  *((uint32_t *)this + 140) = &off_6C2B88;
  *((uint32_t *)this + 142) = 0;
  *(this + 572) = 1;
  *(this + 574) = 0;
  *(this + 573) = 0;
  *((uint32_t *)this + 146) = 0;
  *((uint32_t *)this + 145) = 0;
  *((uint32_t *)this + 144) = 0;
  *(this + 600) = 0;
  *((uint32_t *)this + 149) = &off_6C2B88;
  *((uint32_t *)this + 151) = 0;
  *(this + 608) = 1;
  *(this + 610) = 0;
  *(this + 609) = 0;
  *((uint32_t *)this + 155) = 0;
  *((uint32_t *)this + 154) = 0;
  *((uint32_t *)this + 153) = 0;
  *(this + 636) = 0;
  *((uint32_t *)this + 158) = &off_6C2B88;
  *((uint32_t *)this + 160) = 0;
  *(this + 644) = 1;
  *(this + 646) = 0;
  *(this + 645) = 0;
  *((uint32_t *)this + 164) = 0;
  *((uint32_t *)this + 163) = 0;
  *((uint32_t *)this + 162) = 0;
  *(this + 668) = 0;
  *((uint32_t *)this + 166) = &off_6C2B88;
  *((uint32_t *)this + 168) = 0;
  *(this + 676) = 1;
  *(this + 678) = 0;
  *(this + 677) = 0;
  *((uint32_t *)this + 172) = 0;
  *((uint32_t *)this + 171) = 0;
  *((uint32_t *)this + 170) = 0;
  *(this + 696) = 0;
  *((uint32_t *)this + 173) = &off_6C2B88;
  *((uint32_t *)this + 175) = 0;
  *(this + 704) = 1;
  *(this + 706) = 0;
  *(this + 705) = 0;
  *((uint32_t *)this + 179) = 0;
  *((uint32_t *)this + 178) = 0;
  *((uint32_t *)this + 177) = 0;
  *(this + 764) = 0;
  *((uint32_t *)this + 190) = &off_6C2B88;
  *((uint32_t *)this + 192) = 0;
  *(this + 772) = 1;
  *(this + 774) = 0;
  *(this + 773) = 0;
  *((uint32_t *)this + 196) = 0;
  *((uint32_t *)this + 195) = 0;
  *((uint32_t *)this + 194) = 0;
  *(this + 800) = 0;
  *((uint32_t *)this + 199) = &off_6C2B88;
  *((uint32_t *)this + 201) = 0;
  *(this + 808) = 1;
  *(this + 810) = 0;
  *(this + 809) = 0;
  *((uint32_t *)this + 205) = 0;
  *((uint32_t *)this + 204) = 0;
  *((uint32_t *)this + 203) = 0;
  *(this + 848) = 0;
  *((uint32_t *)this + 211) = &off_6C2B88;
  *((uint32_t *)this + 213) = 0;
  *(this + 856) = 1;
  *(this + 858) = 0;
  *(this + 857) = 0;
  *((uint32_t *)this + 217) = 0;
  *((uint32_t *)this + 216) = 0;
  *((uint32_t *)this + 215) = 0;
  *(this + 876) = 0;
  *((uint32_t *)this + 218) = &off_6C2B88;
  *((uint32_t *)this + 220) = 0;
  *(this + 884) = 1;
  *(this + 886) = 0;
  *(this + 885) = 0;
  *((uint32_t *)this + 224) = 0;
  *((uint32_t *)this + 223) = 0;
  *((uint32_t *)this + 222) = 0;
  *(this + 908) = 0;
  *((uint32_t *)this + 226) = &off_6C2B88;
  *((uint32_t *)this + 228) = 0;
  *(this + 916) = 1;
  *(this + 918) = 0;
  *(this + 917) = 0;
  *((uint32_t *)this + 232) = 0;
  *((uint32_t *)this + 231) = 0;
  *((uint32_t *)this + 230) = 0;
  `eh vector constructor iterator'(this + 936, 0x1Cu, 8, sub_401170, sub_401000);
  *(this + 1200) = 0;
  *((uint32_t *)this + 299) = &off_6C2B88;
  *((uint32_t *)this + 301) = 0;
  *(this + 1208) = 1;
  *(this + 1210) = 0;
  *(this + 1209) = 0;
  *((uint32_t *)this + 305) = 0;
  *((uint32_t *)this + 304) = 0;
  *((uint32_t *)this + 303) = 0;
  *(this + 1264) = 0;
  *((uint32_t *)this + 315) = &off_6C2B88;
  *((uint32_t *)this + 317) = 0;
  *(this + 1272) = 1;
  *(this + 1274) = 0;
  *(this + 1273) = 0;
  *((uint32_t *)this + 321) = 0;
  *((uint32_t *)this + 320) = 0;
  *((uint32_t *)this + 319) = 0;
  *(this + 1292) = 0;
  *((uint32_t *)this + 322) = &off_6C2B88;
  *((uint32_t *)this + 324) = 0;
  *(this + 1300) = 1;
  *(this + 1302) = 0;
  *(this + 1301) = 0;
  *((uint32_t *)this + 328) = 0;
  *((uint32_t *)this + 327) = 0;
  *((uint32_t *)this + 326) = 0;
  *(this + 1332) = 0;
  *((uint32_t *)this + 332) = &off_6C2B88;
  *((uint32_t *)this + 334) = 0;
  *(this + 1340) = 1;
  *(this + 1342) = 0;
  *(this + 1341) = 0;
  *((uint32_t *)this + 338) = 0;
  *((uint32_t *)this + 337) = 0;
  *((uint32_t *)this + 336) = 0;
  sub_423C10(this);
  sub_4290D0(this);
  return this;
}


// ------------------------------------------------------------
// 0x42BD40 sub_42BD40
// ------------------------------------------------------------
int /*thiscall*/ sub_42BD40(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDStage;
  sub_423FD0((uint32_t *)this);
  *(uint8_t *)(this + 1332) = 0;
  *(uint32_t *)(this + 1328) = &vftbl_nengine__IObject;
  *(uint32_t *)(this + 1288) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1292) = 0;
  *(uint32_t *)(this + 1260) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1264) = 0;
  *(uint32_t *)(this + 1196) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1200) = 0;
  `eh vector destructor iterator'((void *)(this + 936), 0x1Cu, 8, sub_401000);
  *(uint32_t *)(this + 904) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 908) = 0;
  *(uint32_t *)(this + 872) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 876) = 0;
  *(uint32_t *)(this + 844) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 848) = 0;
  *(uint32_t *)(this + 796) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 800) = 0;
  *(uint32_t *)(this + 760) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 764) = 0;
  *(uint32_t *)(this + 692) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 696) = 0;
  *(uint32_t *)(this + 664) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 668) = 0;
  *(uint32_t *)(this + 632) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 636) = 0;
  *(uint32_t *)(this + 596) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 600) = 0;
  *(uint32_t *)(this + 560) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 564) = 0;
  *(uint32_t *)(this + 528) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 532) = 0;
  *(uint32_t *)(this + 500) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 504) = 0;
  *(uint32_t *)(this + 472) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 476) = 0;
  `eh vector destructor iterator'((void *)(this + 408), 0x1Cu, 2, sub_401000);
  `eh vector destructor iterator'((void *)(this + 320), 0x1Cu, 2, sub_401000);
  `eh vector destructor iterator'((void *)(this + 256), 0x1Cu, 2, sub_401000);
  *(uint32_t *)(this + 208) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 212) = 0;
  *(uint32_t *)(this + 164) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 168) = 0;
  sub_41A580(this + 148);
  sub_41A580(this + 134);
  result = sub_41A580(this + 120);
  *(uint32_t *)(this + 56) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 60) = 0;
  *(uint32_t *)(this + 4) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42BF10 sub_42BF10
// ------------------------------------------------------------
char /*thiscall*/ sub_42BF10(int this, int ArgList)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax

  off_77F3FC((char *)&byte_6C3EF4, ArgList);
  sub_49E050(0);
  v3 = sub_432F00(0);
  sub_487080(v3);
  sub_49CD70(1);
  sub_45FC60(*(uint32_t *)(this + 28));
  sub_4602C0(*(uint32_t *)(*(uint32_t *)(this + 24) + 476));
  sub_48E870(*(uint32_t *)(this + 28));
  sub_42B6D0((int *)this);
  sub_42B690(0);
  sub_42B780(0);
  sub_48FDE0(dword_99FF08);
  v4 = *(uint32_t *)(this + 16);
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = *(uint32_t *)(*(uint32_t *)(v4 + 108) + 280);
  sub_432EA0("GRENSELOS_READY", -1, 0, 0);
  v5 = *(uint32_t *)(this + 152);
  if ( v5 == 1 )
  {
    *(uint32_t *)(this + 152) = 0;
    *(uint8_t *)(this + 168) = 1;
    *(uint8_t *)(this + 169) = 0;
    *(uint8_t *)(this + 170) = 0;
    LOBYTE(v5) = sub_698F90(this + 156, 500, 0);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x42C000 sub_42C000
// ------------------------------------------------------------
int /*thiscall*/ sub_42C000(int *this, int ArgList)
{
  int v3; // edi
  int v4; // edx
  uint32_t *v6; // esi
  char *v7; // eax
  uint32_t *v8; // esi
  char *v9; // eax
  uint32_t *v10; // esi
  char *v11; // eax
  int v12; // edx

  off_77F3FC((char *)&byte_6C3F44, ArgList);
  if ( ArgList == 4 )
  {
    v3 = sub_48FCA0();
    if ( (int)sub_48FD70(v3) <= 0 )
    {
      sub_48FC30(v3, 255);
      *(this + 47) = 2;
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1024))(dword_8F7C04);
  }
  else if ( ArgList == 0 )
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);
    v7 = sub_422E70(1910);
    sub_43BEE0(v6, (int)v7, -13435036, 0, -1);
    v8 = *((uint32_t **)dword_8F8528 + 7);
    v9 = sub_422E70(1911);
    sub_43BEE0(v8, (int)v9, -13435036, 0, -1);
    v10 = *((uint32_t **)dword_8F8528 + 7);
    v11 = sub_422E70(1927);
    sub_43BEE0(v10, (int)v11, -13435036, 0, -1);
    return sub_425460(*(this + 4), v12);
  }
  off_77F3FC(aOldstateWait);
  sub_42BF10((int)this, ArgList);
  return sub_425460(*(this + 4), v4);
}



// ------------------------------------------------------------
// 0x42C110 sub_42C110
// ------------------------------------------------------------
char /*thiscall*/ sub_42C110(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  uint64_t v7; // rax
  int v8; // ebx
  int v9; // eax
  bool v10; // cc

  if ( *(uint8_t *)(this + 168) != 0 )
  {
    v2 = *(uint32_t *)(this + 152);
    if ( v2 == 1 )
    {
      v3 = *(uint32_t *)(this + 180);
      v4 = sub_699000(this + 156);
      *((uint32_t *)dword_8F8528 + 621) = (uint64_t)sub_4049C0(0.0, 255.0, v4, v3);
    }
    else if ( v2 == 0 )
    {
      v5 = *(uint32_t *)(this + 180);
      v6 = sub_699000(this + 156);
      v7 = (uint64_t)sub_4049C0(255.0, 0.0, v6, v5);
      *((uint32_t *)dword_8F8528 + 621) = v7;
      v8 = *(uint32_t *)(this + 180);
      if ( sub_699000(this + 156) >= v8 )
      {
        *(uint32_t *)(this + 152) = 2;
        *(uint8_t *)(this + 168) = 0;
      }
    }
  }
  if ( *(uint32_t *)(this + 32) == 3 )
  {
    v9 = sub_699000(this + 36);
    v10 = v9 < 9200;
  }
  else
  {
    v9 = *(uint32_t *)(this + 32) - 4;
    if ( *(uint32_t *)(this + 32) != 4 )
      return v9;
    v9 = sub_699000(this + 36);
    v10 = v9 < 16200;
  }
  if ( !v10 && *(uint32_t *)(this + 152) == 2 )
  {
    *(uint8_t *)(this + 168) = 1;
    *(uint32_t *)(this + 152) = 1;
    *(uint8_t *)(this + 170) = 0;
    *(uint8_t *)(this + 169) = 0;
    LOBYTE(v9) = sub_698F90(this + 156, 300, 0);
  }
  return v9;
}



// ------------------------------------------------------------
// 0x42C220 sub_42C220
// ------------------------------------------------------------
void /*thiscall*/ sub_42C220(int this)
{
  if ( *(uint32_t *)(this + 12) != 0 )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
}



// ------------------------------------------------------------
// 0x42C250 sub_42C250
// ------------------------------------------------------------
void **/*thiscall*/ sub_42C250(void **this)
{
  char *v2; // edi
  char *v3; // edi
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]

  *this = (void *)-1;
  v2 = (char *)(this + 2);
  for ( i = 4; i != 0; --i )
  {
    if ( *(uint32_t *)v2 != 0 )
      j__free(*(void **)v2);
    *(uint32_t *)v2 = 0;
    *((uint32_t *)v2 + 1) = 0;
    *((uint32_t *)v2 + 2) = 0;
    v2 += 16;
  }
  if ( *(this + 18) != nullptr )
    j__free(*(this + 18));
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  v3 = (char *)(this + 29);
  for ( j = 4; j != 0; --j )
  {
    if ( *(uint32_t *)v3 != 0 )
      j__free(*(void **)v3);
    *(uint32_t *)v3 = 0;
    *((uint32_t *)v3 + 1) = 0;
    *((uint32_t *)v3 + 2) = 0;
    v3 += 16;
  }
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  *(this + 54) = nullptr;
  *(this + 55) = nullptr;
  *(this + 56) = nullptr;
  *(this + 57) = nullptr;
  *(this + 59) = nullptr;
  *(this + 60) = nullptr;
  *(this + 61) = nullptr;
  *(this + 62) = nullptr;
  *(this + 58) = nullptr;
  *(this + 63) = nullptr;
  *(this + 64) = nullptr;
  *(this + 65) = nullptr;
  *(this + 66) = nullptr;
  return this + 59;
}



// ------------------------------------------------------------
// 0x42C370 sub_42C370
// ------------------------------------------------------------
void /*thiscall*/ sub_42C370(int this)
{
  `eh vector destructor iterator'((void *)(this + 112), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 72) != 0 )
    j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  `eh vector destructor iterator'((void *)(this + 4), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x42C400 sub_42C400
// ------------------------------------------------------------
double /*cdecl*/ sub_42C400(int a1, int a2)
{
  if ( a1 == -1 )
    return 1.0;
  else
    return *(float *)(*(uint32_t *)(dword_8F7C40 + 8) + 44 * a1 - 44 + 4 * a2);
}



// ------------------------------------------------------------
// 0x42C430 sub_42C430
// ------------------------------------------------------------
int /*thiscall*/ sub_42C430(uint32_t *this)
{
  unsigned int v2; // esi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx

  v2 = 0;
  while ( 1 )
  {
    v3 = *(this + 7);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      return sub_45F550(*(this + 7));
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v2);
    else
      v7 = 0;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7) == 289 )
    {
      v8 = *(this + 7);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 == 0 || v2 >= (*(uint32_t *)(v8 + 12) - v9) >> 2 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(MEMORY[0] + 84))(0);
        goto LABEL_15;
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v9 + 4 * v2) + 84))(*(uint32_t *)(v9 + 4 * v2), 0);
      ++v2;
    }
    else
    {
LABEL_15:
      ++v2;
    }
  }
}



// ------------------------------------------------------------
// 0x42C4C0 sub_42C4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42C4C0(uint32_t *this)
{
  unsigned int v2; // esi
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx

  v2 = 0;
  while ( 1 )
  {
    v3 = *(this + 7);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      return sub_45F550(*(this + 7));
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v2);
    else
      v7 = 0;
    if ( *(uint8_t *)(v7 + 277) == 1 )
    {
      v8 = *(uint32_t *)(v3 + 8);
      if ( v8 == 0 || v2 >= (*(uint32_t *)(v3 + 12) - v8) >> 2 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(MEMORY[0] + 84))(0);
        goto LABEL_15;
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v8 + 4 * v2) + 84))(*(uint32_t *)(v8 + 4 * v2), 0);
      ++v2;
    }
    else
    {
LABEL_15:
      ++v2;
    }
  }
}



// ------------------------------------------------------------
// 0x42C540 sub_42C540
// ------------------------------------------------------------
char */*stdcall*/ sub_42C540(int a1)
{
  char *v1; // eax

  v1 = (char *)dword_8F7C58 + 28 * a1;
  if ( *((uint32_t *)v1 + 6) < 0x10u )
    return v1 + 4;
  else
    return *((char **)v1 + 1);
}



// ------------------------------------------------------------
// 0x42C570 sub_42C570
// ------------------------------------------------------------
int /*stdcall*/ sub_42C570(int ArgList, int a2, int a3)
{
  int result; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // [esp-Ch] [ebp-210h]
  char Buffer[512]; // [esp+0h] [ebp-204h] BYREF
  int v8; // [esp+200h] [ebp-4h]

  v8 = dword_796E50;
  result = sub_48B740(6);
  if ( result != 1 )
  {
    v4 = sub_49EDC0(ArgList, -1);
    if ( v4 != 0 )
    {
      sub_422E70(10033);
      result = a2;
      if ( a2 == -1 )
      {
        if ( a3 != -1 )
        {
          v6 = sub_48FE30(v4);
          v5 = sub_422E70(1920);
LABEL_11:
          sprintf(Buffer, v5, v6);
          return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
        }
      }
      else
      {
        result = a3 + 1;
        switch ( a3 )
        {
          case -1:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1921);
            goto LABEL_11;
          case 0:
          case 1:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1922);
            goto LABEL_11;
          case 4:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1923);
            goto LABEL_11;
          default:
            return result;
        }
      }
    }
    else
    {
      return off_77F3FC((char *)&byte_6C3F6C, ArgList);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42C6A0 sub_42C6A0
// ------------------------------------------------------------
char */*stdcall*/ sub_42C6A0(int ArgList)
{
  char *result; // eax

  result = (char *)sub_48B740(6);
  if ( result != (char *)1 )
  {
    if ( sub_49EDC0(ArgList, -1) != 0 )
      return sub_422E70(10033);
    else
      return (char *)off_77F3FC((char *)&byte_6C3F9C, ArgList);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42C710 sub_42C710
// ------------------------------------------------------------
double /*thiscall*/ sub_42C710(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v6; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v6, &a2);
  if ( v6 == *(this + 17) )
    return 1.0;
  v4 = *(uint32_t *)(v6 + 16);
  if ( v4 == -1 )
    return 1.0;
  else
    return *(float *)(44 * v4 + *(uint32_t *)(dword_8F7C40 + 8) - 44 + 4 * a3);
}



// ------------------------------------------------------------
// 0x42C770 sub_42C770
// ------------------------------------------------------------
void /*thiscall*/ sub_42C770(int this)
{
  sub_45F080();
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  if ( *(uint32_t *)(this + 120) != 0 )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  `eh vector destructor iterator'((void *)(this + 20), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x42C820 sub_42C820
// ------------------------------------------------------------
int /*thiscall*/ sub_42C820(uint32_t *this, int ArgList)
{
  uint8_t *v3; // ecx
  _BOOL2 v4; // dx
  int v5; // eax

  off_77F3FC((char *)&byte_6C3FCC, ArgList);
  sub_49AA90("result");
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = -1;
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;
  if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )
  {
    word_8F7C10 += *(uint16_t *)(*(this + 5) + 460);
    v3 = *((uint8_t **)dword_8F8528 + 4);
    v4 = word_8F7C10 != word_8F7C14;
    v3[1196] = 1;
    v3 += 1184;
    v3[13] = 0;
    v3[14] = 0;
    sub_698F90((int)v3, v4 ? 1000 : 5000, -500);
  }
  sub_49BDB0(0);
  v5 = sub_432F00(0);
  sub_487080(v5);
  sub_42B690(0);
  return sub_42C430(this);
}



// ------------------------------------------------------------
// 0x42C920 sub_42C920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42C920(uint32_t *this, uint32_t *a2, int a3)
{
  sub_48C4B0(a3 + 24, *(this + 2), a3);
  *(this + 2) -= 24;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x42C960 sub_42C960
// ------------------------------------------------------------
void /*stdcall*/ sub_42C960(int a1)
{
  if ( *(uint32_t *)(a1 + 4) != 0 )
    j__free(*(void **)(a1 + 4));
  *(uint32_t *)(a1 + 4) = 0;
  *(uint32_t *)(a1 + 8) = 0;
  *(uint32_t *)(a1 + 12) = 0;
}



// ------------------------------------------------------------
// 0x42C9A0 sub_42C9A0
// ------------------------------------------------------------
void /*thiscall*/ sub_42C9A0(int this)
{
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
}



// ------------------------------------------------------------
// 0x42C9E0 sub_42C9E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42C9E0(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
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
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int v21; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  v6 = sub_5648C0(*(this + 1), a4, *(this + 1), a5, 0);
  v7 = (uint32_t *)*(this + 1);
  v21 = v6;
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
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);
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
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x42CB90 sub_42CB90
// ------------------------------------------------------------
void /*noreturn*/ sub_42CB90()
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
// 0x42CC00 sub_42CC00
// ------------------------------------------------------------
void /*cdecl*/ sub_42CC00(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 16 )
  {
    if ( *(uint32_t *)(i + 4) != 0 )
      j__free(*(void **)(i + 4));
    *(uint32_t *)(i + 4) = 0;
    *(uint32_t *)(i + 8) = 0;
    *(uint32_t *)(i + 12) = 0;
  }
}



// ------------------------------------------------------------
// 0x42CC40 sub_42CC40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42CC40(char *this)
{
  char *v2; // esi
  int v3; // esi
  uint32_t *result; // eax
  int m; // ecx
  int i; // [esp+Ch] [ebp-8h]
  int k; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 4;
  *((uint32_t *)this + 2) = 100;
  *((uint32_t *)this + 3) = 100;
  *((uint32_t *)this + 4) = 100;
  v2 = this + 24;
  for ( i = 6; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      if ( *(uint32_t *)v2 != 0 )
        j__free(*(void **)v2);
      *(uint32_t *)v2 = 0;
      *((uint32_t *)v2 + 1) = 0;
      *((uint32_t *)v2 + 2) = 0;
      v2 += 16;
    }
  }
  if ( *((uint32_t *)this + 54) != 0 )
    j__free(*((void **)this + 54));
  *((uint32_t *)this + 54) = 0;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  if ( *((uint32_t *)this + 58) != 0 )
    j__free(*((void **)this + 58));
  *((uint32_t *)this + 58) = 0;
  *((uint32_t *)this + 59) = 0;
  *((uint32_t *)this + 60) = 0;
  *((uint32_t *)this + 61) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 72) = 0;
  v3 = *((uint32_t *)this + 74);
  if ( v3 != 0 )
  {
    for ( k = *((uint32_t *)this + 75); v3 != k; v3 += 4 )
      sub_41B010(v3);
    j__free(*((void **)this + 74));
  }
  *((uint32_t *)this + 74) = 0;
  *((uint32_t *)this + 75) = 0;
  *((uint32_t *)this + 76) = 0;
  result = this + 316;
  for ( m = 3; m != 0; --m )
  {
    *(result - 2) = 0;
    *(result - 1) = 0;
    *result = 0;
    result[1] = 0;
    result += 4;
  }
  *((uint32_t *)this + 89) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42CDB0 sub_42CDB0
// ------------------------------------------------------------
int /*thiscall*/ sub_42CDB0(uint32_t *this, int a2, uint32_t *a3)
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
      v10 = *sub_42C9E0(this, &a3, 1, v5, (int)v3);
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
    v12 = *sub_42C9E0(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x42CE70 sub_42CE70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42CE70(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_42C9E0((uint32_t *)this, a2, 1, *(uint32_t **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_42C9E0((uint32_t *)this, a2, 1, a3, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_42C9E0((uint32_t *)this, a2, 0, v8, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_4A3B30(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C5E0(&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_42CDB0((uint32_t *)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 21) != 0 )
      sub_42C9E0((uint32_t *)this, a2, 0, a3, (int)v7);
    else
      sub_42C9E0((uint32_t *)this, a2, 1, a4, (int)v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 21) != 0 )
      sub_42C9E0((uint32_t *)this, a2, 0, a4, (int)v7);
    else
      sub_42C9E0((uint32_t *)this, a2, 1, a3, (int)v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x42CFD0 sub_42CFD0
// ------------------------------------------------------------
char /*thiscall*/ sub_42CFD0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_42CB90(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x42D030 sub_42D030
// ------------------------------------------------------------
char /*thiscall*/ sub_42D030(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x1FFFFFFF )
    sub_42CB90(this);
  v4 = (char *)operator new(8 * a2);
  *(this + 3) = &v4[8 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x42D090 sub_42D090
// ------------------------------------------------------------
char /*thiscall*/ sub_42D090(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xFFFFFFF )
    sub_42CB90(this);
  v4 = (char *)operator new(16 * a2);
  *(this + 3) = &v4[16 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x42D0E0 sub_42D0E0
// ------------------------------------------------------------
char /*thiscall*/ sub_42D0E0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xAAAAAAA )
    sub_42CB90(this);
  v4 = (char *)operator new(24 * a2);
  *(this + 3) = &v4[24 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x42D130 sub_42D130
// ------------------------------------------------------------
int /*thiscall*/ sub_42D130(int *this, int a2, unsigned int a3, uint32_t *Block)
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
      sub_41D5A0(this);
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
// 0x42D400 sub_42D400
// ------------------------------------------------------------
void /*thiscall*/ sub_42D400(void **this)
{
  if ( *(this + 2) != nullptr )
    j__free(*(this + 2));
  *(this + 2) = nullptr;
  *(this + 3) = nullptr;
  *(this + 4) = nullptr;
}



// ------------------------------------------------------------
// 0x42D430 sub_42D430
// ------------------------------------------------------------
int /*thiscall*/ sub_42D430(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  v2 = (uint32_t *)*(this + 1);
  v3 = (int *)v2[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *a2 )
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
  return *sub_42CE70((int)this, &a2, v2, v5) + 16;
}



// ------------------------------------------------------------
// 0x42D4B0 sub_42D4B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42D4B0(int *this, uint32_t *a2, int a3, uint32_t *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 24 != 0 )
    v6 = (a3 - v5) / 24;
  else
    v6 = 0;
  sub_42D130(this, a3, 1u, Block);
  *a2 = *(this + 1) + 24 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x42D520 sub_42D520
// ------------------------------------------------------------
void /*stdcall*/ sub_42D520(int a1, int a2)
{
  sub_42CC00(a1, a2);
}



// ------------------------------------------------------------
// 0x42D540 sub_42D540
// ------------------------------------------------------------
void /*thiscall*/ sub_42D540(int *this)
{
  int v2; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
  {
    sub_42CC00(v2, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x42D590 sub_42D590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42D590(uint32_t *this, int a2)
{
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  `eh vector constructor iterator'(this + 5, 0x10u, 6, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  sub_45F040(this);
  sub_45FA80(a2);
  return this;
}



// ------------------------------------------------------------
// 0x42D620 sub_42D620
// ------------------------------------------------------------
int /*thiscall*/ sub_42D620(int this)
{
  `eh vector constructor iterator'((void *)(this + 4), 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  `eh vector constructor iterator'((void *)(this + 112), 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_42C250((void **)this);
  return this;
}



// ------------------------------------------------------------
// 0x42D6A0 sub_42D6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_42D6A0(int this)
{
  `eh vector constructor iterator'((void *)(this + 20), 0x10u, 12, sub_4019A0, sub_5E5260);
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 348) = 0;
  *(uint32_t *)(this + 352) = 0;
  sub_42CC40((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x42D780 sub_42D780
// ------------------------------------------------------------
void /*userpurge*/ sub_42D780(uint32_t *a1@<ecx>, float a2@<esi>, int a3, int a4)
{
  int v4; // edi
  uint32_t *v5; // esi
  uint32_t *v6; // eax
  int v7; // ebx
  int v8; // esi
  double v9; // st7
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int *v13; // eax
  int *v14; // esi
  int *v15; // ebx
  int *v16; // esi
  float v17; // [esp+0h] [ebp-14h]

  v4 = a3;
  if ( *(float *)&a3 != 0.0 )
  {
    v5 = a1 + 16;
    v6 = (uint32_t *)sub_42D430(a1 + 16, &a3);
    v7 = a4;
    if ( *v6 != a4 )
    {
      *(uint32_t *)sub_42D430(v5, &a3) = v7;
      v8 = __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( v8 != 0 )
      {
        a3 = dword_77F884;
        v9 = sub_42C710(a1, v4, 2);
        v17 = v9 * *(float *)&a3;
        v10 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v8 + 672))(v8, 0, LODWORD(v17));
        sub_42B3F0((void *)(v10 + 4), a2);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 676))(v8, 0);
        v11 = *(uint32_t *)v8;
        v12 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v8 + 740))(v8, 0, 1);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 732))(v8, v12);
      }
      v13 = (int *)__RTDynamicCast(
                     v4,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &CNRDPassiveObject `RTTI Type Descriptor',
                     0);
      v14 = v13;
      if ( v13 != nullptr && v13[171] > 0 )
      {
        v15 = (int *)((*(int (/*thiscall*/ **)(int *))(*v13 + 672))(v13) + 4);
        *v15 = (uint64_t)(sub_42C710(a1, v4, 2) * (double)*v15 * *(float *)&dword_77F884);
        v16 = (int *)(*(int (/*thiscall*/ **)(int *))(*v14 + 672))(v14);
        *v16 = (uint64_t)(sub_42C710(a1, v4, 2) * (double)*v16 * *(float *)&dword_77F884);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x42D8B0 sub_42D8B0
// ------------------------------------------------------------
char /*fastcall*/ sub_42D8B0(uint32_t *a1)
{
  int v1; // eax
  unsigned int v2; // edi
  int *v3; // ebx
  int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  void *v12; // esi
  unsigned int v13; // edi
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  uint8_t *v18; // esi
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  uint32_t *v26; // ecx
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // ebx
  uint32_t *v37; // eax
  uint32_t *v38; // edi
  uint32_t *v39; // esi
  int v40; // ecx
  int v41; // edx
  int v43; // [esp-10h] [ebp-50h]
  int v44; // [esp-8h] [ebp-48h]
  int v45; // [esp-8h] [ebp-48h]
  char v46; // [esp-4h] [ebp-44h]
  void *v47[4]; // [esp+0h] [ebp-40h] BYREF
  int v48; // [esp+10h] [ebp-30h]
  int v49; // [esp+14h] [ebp-2Ch]
  int v50; // [esp+18h] [ebp-28h] BYREF
  int v51; // [esp+1Ch] [ebp-24h]
  int v52; // [esp+20h] [ebp-20h]
  int v53; // [esp+24h] [ebp-1Ch]
  int v54; // [esp+28h] [ebp-18h] BYREF
  int v55; // [esp+2Ch] [ebp-14h] BYREF
  uint32_t *v56; // [esp+30h] [ebp-10h]
  int v57; // [esp+3Ch] [ebp-4h]

  v1 = a1[8];
  v56 = a1;
  if ( v1 == 2 )
  {
    LOBYTE(v1) = *((uint8_t *)a1 + 108);
    if ( (uint8_t)v1 != 0 )
    {
      v1 = a1[35];
      v2 = 0;
      if ( v1 != 0 )
      {
        v1 = (a1[36] - v1) / 24;
        v48 = v1;
        if ( v1 != 0 )
        {
          v3 = (int *)a1[35];
          v4 = *(uint32_t *)(a1[4] + 104);
          v55 = 0;
          while ( 1 )
          {
            v5 = *(uint32_t *)(v4 + 120);
            v6 = v5 != 0 ? (*(uint32_t *)(v4 + 124) - v5) >> 2 : 0;
            if ( (int)v2 >= v6 )
              break;
            v7 = *(uint32_t *)(v4 + 120);
            if ( v7 != 0 && v2 < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
              v8 = *(uint32_t *)(v7 + 4 * v2);
            else
              v8 = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 529) != 0 )
            {
              v9 = *(uint32_t *)(v4 + 120);
              if ( v9 != 0 && v2 < (*(uint32_t *)(v4 + 124) - v9) >> 2 )
                v10 = *(uint32_t *)(v9 + 4 * v2);
              else
                v10 = 0;
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10) == 100 )
                ++v55;
            }
            a1 = v56;
            ++v2;
          }
          v11 = v3[1];
          v12 = (void *)v3[2];
          v13 = v3[4];
          v51 = *v3;
          v14 = v3[3];
          v53 = v11;
          v15 = v3[5];
          v16 = a1[30];
          v52 = v14;
          v48 = v15;
          v49 = (int)(a1 + 24);
          v1 = sub_699000((int)(a1 + 24));
          if ( v1 >= v16 )
          {
            LOBYTE(v1) = (uint8_t)v56;
            if ( v55 < v56[31] )
            {
              v50 = *(uint32_t *)(*(uint32_t *)(16 * v53 + v56[5] + 204) + 4 * v52);
              v17 = sub_4ABE10(v50, v12, 0);
              v18 = (uint8_t *)v17;
              if ( v17 != 0 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 372))(v17, 100);
                v19 = *(uint32_t *)(v56[6] + 476);
                v20 = *(uint32_t *)(v19 + 444);
                if ( v20 == 0 || v13 >= (*(uint32_t *)(v19 + 448) - v20) / 12 )
                {
                  v21 = sub_4DA030(v19 + 440);
                  off_77F3FC((char *)&byte_6C4088, v13, v21);
                  v13 = 0;
                }
                v22 = *(uint32_t *)(*(uint32_t *)(v56[6] + 476) + 444);
                v23 = *(uint32_t *)v18;
                v24 = *(uint32_t *)(12 * v13 + v22 + 4);
                v55 = *(uint32_t *)(12 * v13 + v22);
                v54 = v24;
                v25 = (*(int (/*thiscall*/ **)(uint8_t *))(v23 + 436))(v18);
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, int))(v23 + 112))(v18, v55, v54, v25);
                v26 = v56;
                v43 = v51;
                v18[7801] = 1;
                sub_45FE80(v26[7], v13, 529, v43, (int)v18, 0, 0);
                v27 = *(uint32_t *)v18;
                v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
                (*(void (/*thiscall*/ **)(uint8_t *, int))(v27 + 1044))(v18, v28);
                (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v18 + 320))(v18);
                if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v18 + 308))(v18) != 0 )
                {
                  v29 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v18 + 120))(v18);
                  v30 = *(uint32_t *)v18;
                  v55 = v29;
                  v31 = (*(int (/*thiscall*/ **)(uint8_t *))(v30 + 124))(v18);
                  v32 = *(uint32_t *)v18;
                  v54 = v31;
                  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(v32 + 136))(v18, v55, v31, 0) == 0 )
                  {
                    v33 = *(uint32_t *)v18;
                    v34 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)v18 + 124))(v18, 300, 1, 5);
                    v35 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v18 + 120))(v18, v34);
                    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int *, int *, int))(v33 + 140))(
                           v18,
                           &v55,
                           &v54,
                           v35) != 0 )
                    {
                      v36 = *(uint32_t *)v18;
                      v47[0] = (void *)(*(int (/*thiscall*/ **)(uint8_t *, void *))(*(uint32_t *)v18 + 128))(v18, v47[0]);
                      v46 = v54;
                      v44 = v55;
                      (*(void (/*thiscall*/ **)(uint8_t *))(v36 + 108))(v18);
                      v37 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)v18 + 60))(v18, 1, 1);
                      sub_49FFC0(v37, v13, (int)v18, v44, v46);
                      off_77F3FC((char *)&byte_6C4058, v13, v55, v54);
                    }
                    else
                    {
                      off_77F3FC((char *)&byte_6C402C, v13);
                    }
                  }
                }
                if ( v53 == 1 || v53 == 2 )
                {
                  memset(&v47[1], 0, 12);
                  v41 = *(uint32_t *)v18;
                  v57 = 0;
                  (*(void (/*thiscall*/ **)(uint8_t *, unsigned int, void **, int))(v41 + 1160))(
                    v18,
                    v52 + v13 + v50,
                    v47,
                    v53);
                  v57 = -1;
                  sub_5E5260(v47);
                }
                else if ( v53 == 3 )
                {
                  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v18 + 1120))(v18);
                }
                sub_495C00(1);
                v38 = v56;
                v39 = v56 + 34;
                sub_42C920(&v50, v56[35]);
                v1 = sub_4FEF30(v39);
                if ( v1 != 0 )
                {
                  v40 = v49;
                  v45 = v48;
                  *(uint8_t *)(v49 + 13) = 0;
                  *(uint8_t *)(v40 + 14) = 0;
                  LOBYTE(v1) = sub_698F90(v40, v45, 0);
                }
                else
                {
                  *((uint8_t *)v38 + 108) = 0;
                }
              }
              else
              {
                LOBYTE(v1) = off_77F3FC((char *)&byte_6C3FF4, v50);
              }
            }
          }
        }
      }
    }
  }
  return v1;
}


// ------------------------------------------------------------
// 0x42DCA0 sub_42DCA0
// ------------------------------------------------------------
void /*thiscall*/ sub_42DCA0(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // eax

  v2 = this + 16;
  sub_41CAA0(*(void **)(*(this + 17) + 4));
  *(uint32_t *)(v2[1] + 4) = v2[1];
  v3 = (uint32_t *)v2[1];
  v4 = 0;
  v2[2] = 0;
  *v3 = v3;
  *(uint32_t *)(v2[1] + 8) = v2[1];
  do
  {
    v5 = sub_578E80(v4);
    if ( v5 != 0 )
    {
      v6 = *(uint32_t *)(v5 + 196);
      if ( v6 != 0 )
      {
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v6 + 388))(*(uint32_t *)(v5 + 196));
        sub_42D780(this, *(float *)&v6, v6, v7);
      }
    }
    ++v4;
  }
  while ( v4 < 8 );
}



// ------------------------------------------------------------
// 0x42DD10 sub_42DD10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42DD10(int *this, uint32_t *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 24;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 24 )
    return sub_42D4B0(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_5044B0(v5, 1, Block);
  *(this + 2) = v5 + 24;
  return result;
}



// ------------------------------------------------------------
// 0x42DDA0 sub_42DDA0
// ------------------------------------------------------------
void /*stdcall*/ sub_42DDA0(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 44 )
    sub_42C220(i);
}



// ------------------------------------------------------------
// 0x42DDD0 sub_42DDD0
// ------------------------------------------------------------
void /*thiscall*/ sub_42DDD0(int *this)
{
  int v1; // eax
  uint32_t *v2; // esi

  v1 = *(this + 5);
  v2 = this + 4;
  if ( v1 != 0 )
  {
    sub_42CC00(v1, *(this + 6));
    j__free((void *)v2[1]);
  }
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
}



// ------------------------------------------------------------
// 0x42DE20 sub_42DE20
// ------------------------------------------------------------
void **/*thiscall*/ sub_42DE20(void *this)
{
  int v2; // edi
  int v3; // ecx
  void **result; // eax
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0xFFFF;
  *((uint32_t *)this + 25) = 0;
  *((uint8_t *)this + 104) = 0;
  *((uint32_t *)this + 27) = -1;
  *((uint32_t *)this + 28) = 1;
  *((uint32_t *)this + 29) = -1;
  *((uint32_t *)this + 30) = -1;
  *((uint32_t *)this + 31) = -1;
  *((uint32_t *)this + 32) = -1;
  *((uint32_t *)this + 33) = -1;
  *((uint32_t *)this + 34) = -1;
  *((uint32_t *)this + 35) = -1;
  *((uint32_t *)this + 36) = -1;
  *((uint32_t *)this + 37) = -1;
  *((uint32_t *)this + 38) = -1;
  *((uint32_t *)this + 39) = -1;
  *((uint32_t *)this + 40) = -1;
  if ( *((uint32_t *)this + 42) != 0 )
    j__free(*((void **)this + 42));
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  v2 = *((uint32_t *)this + 46);
  if ( v2 != 0 )
  {
    v3 = *((uint32_t *)this + 47);
    for ( i = v3; v2 != v3; v2 += 16 )
    {
      if ( *(uint32_t *)(v2 + 4) != 0 )
      {
        j__free(*(void **)(v2 + 4));
        v3 = i;
      }
      *(uint32_t *)(v2 + 4) = 0;
      *(uint32_t *)(v2 + 8) = 0;
      *(uint32_t *)(v2 + 12) = 0;
    }
    j__free(*((void **)this + 46));
  }
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  result = sub_42C250((void **)this + 49);
  *((uint8_t *)this + 464) = 0;
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42DF70 sub_42DF70
// ------------------------------------------------------------
int /*thiscall*/ sub_42DF70(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  *(uint32_t *)(this + 96) = 0xFFFF;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  sub_42D620(this + 196);
  sub_42DE20((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x42E010 CNWarRoomModule__vmt4
// ------------------------------------------------------------
char /*usercall*/ CNWarRoomModule__vmt4@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  uint8_t v7; // al
  uint8_t *v8; // eax
  int i; // ecx

  sub_4AEB30(&unk_9A02B0);
  sub_433690();
  sub_4294E0(*(uint32_t *)(a1 + 16), a2, a3);
  v4 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )
    v4 = sub_45E870(pt.x, pt.y, 1);
  v5 = *(uint32_t *)(a1 + 84);
  if ( v5 != v4 )
  {
    if ( v5 != 0 && (uint8_t)sub_45E680(*(uint32_t *)(a1 + 84)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(a1 + 84) + 284))(
        *(uint32_t *)(a1 + 84),
        0,
        0,
        1,
        2);
    *(uint32_t *)(a1 + 84) = v4;
  }
  if ( *(uint32_t *)(a1 + 84) != 0 )
  {
    v6 = sub_699000(a1 + 36);
    v7 = sub_42B420(100, 255, v6, 500);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(a1 + 84) + 284))(
      *(uint32_t *)(a1 + 84),
      1,
      (v7 << 24) | 0xFF9B,
      0,
      1);
  }
  sub_42D8B0((uint32_t *)a1);
  sub_42C110(a1);
  LOBYTE(v8) = *(uint8_t *)(a1 + 184);
  if ( (uint8_t)v8 == 0 )
  {
    *(uint8_t *)(a1 + 184) = 1;
    v8 = (uint8_t *)(dword_8F8520 + 1048692);
    for ( i = 8; i != 0; --i )
    {
      if ( *v8 == 0 )
      {
        *v8 = 1;
        v8[1] = 0;
        v8[2] = 0;
      }
      v8 += 28;
    }
  }
  return (char)v8;
}



// ------------------------------------------------------------
// 0x42E120 sub_42E120
// ------------------------------------------------------------
void /*thiscall*/ sub_42E120(int *this, int ArgList, int a3, char a4)
{
  int v4; // edi
  int v6; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // [esp+8h] [ebp-4h] BYREF

  v4 = a3;
  if ( a3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( v4 != v6 )
    {
      LOBYTE(v6) = a4 == 0;
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 100))(
        dword_8F8520,
        ArgList,
        v4,
        v6,
        0);
    }
    v7 = *(uint32_t *)(v4 + 196);
    if ( v7 != 0 )
    {
      sub_45FE80(*(this + 7), v4, 273, *(uint16_t *)(v4 + 4), v7, 0, 0);
      v8 = *(uint16_t *)(v4 + 4);
      v10 = 0;
      a3 = 0;
      sub_48C2A0(&v10, &a3, 0, v7, ArgList * v8);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v7 + 112))(v7, v10, a3, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 148))(v7, 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 1020))(v7);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 1212))(v7, ArgList);
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 388))(v7);
      sub_42D780(this, *(float *)&v7, v7, v9);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 1056))(v7, 1);
      sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
    }
    else
    {
      off_77F3FC(aCriticalErrorW_0, ArgList);
    }
  }
}



// ------------------------------------------------------------
// 0x42E230 sub_42E230
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42E230(int *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  uint32_t Block[6]; // [esp+0h] [ebp-18h] BYREF

  Block[0] = a2;
  Block[2] = a4;
  Block[1] = a3;
  Block[4] = a6;
  Block[3] = a5;
  Block[5] = a7;
  return sub_42DD10(this + 34, Block);
}



// ------------------------------------------------------------
// 0x42E270 sub_42E270
// ------------------------------------------------------------
int /*thiscall*/ sub_42E270(int this, int ArgList)
{
  uint8_t *v3; // ecx
  _BOOL2 v4; // dx
  int v5; // edi
  int v6; // eax
  const char *v7; // eax
  unsigned int v8; // edi
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  unsigned int v13; // edi
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int v19; // eax
  int v20; // edi
  int v21; // edi
  int v22; // edi
  uint32_t *v23; // eax
  int v24; // eax
  int v25; // edx
  int v27; // [esp+Ch] [ebp-210h]
  int v28; // [esp+10h] [ebp-20Ch] BYREF
  int v29; // [esp+14h] [ebp-208h] BYREF
  char Buffer[512]; // [esp+18h] [ebp-204h] BYREF
  int v31; // [esp+218h] [ebp-4h]
  int ArgLista; // [esp+224h] [ebp+8h]

  v31 = dword_796E50;
  off_77F3FC((char *)&byte_6C4154, ArgList);
  sub_49CD70(0);
  sub_44E850(dword_8F8528, 42);
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;
  if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )
  {
    word_8F7C10 += *(uint16_t *)(*(uint32_t *)(this + 20) + 456);
    v3 = *((uint8_t **)dword_8F8528 + 4);
    v4 = word_8F7C10 != word_8F7C14;
    v3[1196] = 1;
    v3 += 1184;
    v3[13] = 0;
    v3[14] = 0;
    sub_698F90((int)v3, v4 ? 1000 : 5000, -500);
  }
  if ( *(uint32_t *)(this + 152) == 1 )
  {
    *(uint32_t *)(this + 152) = 0;
    *(uint8_t *)(this + 168) = 1;
    *(uint8_t *)(this + 169) = 0;
    *(uint8_t *)(this + 170) = 0;
    sub_698F90(this + 156, 500, 0);
  }
  if ( ArgList == 1 )
  {
    v5 = dword_8F7D28[dword_77F888 + *(uint32_t *)(this + 76)];
    v6 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) - v5;
    if ( v6 < 0 )
      v6 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(**((uint32_t **)dword_8F852C + 3), v6);
    v7 = (const char *)sub_422E70(1940);
    sprintf(Buffer, v7, v5);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -13435036, 0, -1);
    sub_42B690(1);
    sub_42DCA0(this);
    v8 = 0;
    while ( 1 )
    {
      v9 = *(uint32_t *)(this + 28);
      v10 = *(uint32_t *)(v9 + 120);
      v11 = v10 != 0 ? (*(uint32_t *)(v9 + 124) - v10) >> 2 : 0;
      if ( (int)v8 >= v11 )
        break;
      v12 = *(uint32_t *)(v9 + 120);
      if ( v12 != 0 && v8 < (*(uint32_t *)(v9 + 124) - v12) >> 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v12 + 4 * v8) + 320))(*(uint32_t *)(v12 + 4 * v8));
        ++v8;
      }
      else
      {
        (*(void (**)(void))(MEMORY[0] + 320))();
        ++v8;
      }
    }
  }
  else if ( ArgList == 3 )
  {
    sub_42C4C0(this);
    sub_4602C0(*(uint32_t *)(*(uint32_t *)(this + 24) + 476));
    sub_48E870(*(uint32_t *)(this + 28));
    sub_42B720(1, 3000);
    v13 = 0;
    while ( 1 )
    {
      v14 = *(uint32_t *)(this + 28);
      v15 = *(uint32_t *)(v14 + 120);
      v16 = v15 != 0 ? (*(uint32_t *)(v14 + 124) - v15) >> 2 : 0;
      if ( (int)v13 >= v16 )
        break;
      v17 = *(uint32_t *)(v14 + 120);
      if ( v17 != 0 && v13 < (*(uint32_t *)(v14 + 124) - v17) >> 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v17 + 4 * v13) + 320))(*(uint32_t *)(v17 + 4 * v13));
        ++v13;
      }
      else
      {
        (*(void (**)(void))(MEMORY[0] + 320))();
        ++v13;
      }
    }
    if ( *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
    {
      v18 = *(uint32_t *)(dword_99FF08 + 4);
      v27 = dword_99FF08;
      v19 = sub_48FCA0();
      v20 = sub_48FD70(v19);
      ArgLista = v18 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      v21 = *(uint32_t *)(this + 124) * (*(uint32_t *)(this + 88) + sub_48FCA0()) * ArgLista + v20;
      v22 = sub_48FBB0(v27) + v21;
      sub_48C3A0(0, &v28, &v29, dword_8F7C04, v22);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 108))(dword_8F7C04, v28, v29, 0);
      v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 60))(dword_8F7C04);
      sub_49FFC0(v23, v22, this, 1, 1);
    }
  }
  sub_432EA0("R_GRENSELOS_BATTLE", -1, 0, 0);
  sub_42B780(1);
  v24 = sub_4B09A0(dword_8F7C04);
  sub_4B09B0(v24);
  v25 = *(uint32_t *)(this + 88) + 1;
  *(uint32_t *)(this + 88) = v25;
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = v25;
  if ( *(uint32_t *)(this + 88) == *(uint32_t *)(this + 92) )
    return sub_49AA90("last battle start");
  else
    return sub_49AA90("battle start");
}


// ------------------------------------------------------------
// 0x42E620 sub_42E620
// ------------------------------------------------------------
int /*thiscall*/ sub_42E620(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 44 )
      sub_42C220(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42E670 sub_42E670
// ------------------------------------------------------------
void /*stdcall*/ sub_42E670(void **a1, void **a2)
{
  void **i; // esi

  for ( i = a1; i != a2; i += 5 )
    sub_42D400(i);
}



// ------------------------------------------------------------
// 0x42E6A0 sub_42E6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_42E6A0(void ****this)
{
  void ****v1; // ebx
  void ***k; // esi
  void **v3; // edi
  int result; // eax
  int i; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]

  v1 = this + 7;
  for ( i = 6; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      for ( k = *(v1 - 1); k != *v1; k += 2 )
      {
        v3 = *k;
        if ( *k != nullptr )
        {
          sub_42AF90(*k);
          sub_657740(v3, 228);
        }
        *k = nullptr;
      }
      v1 += 4;
      result = j - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42E710 sub_42E710
// ------------------------------------------------------------
void /*thiscall*/ sub_42E710(int this)
{
  sub_42E6A0((void ****)this);
  sub_4017E0(this + 292);
  if ( *(uint32_t *)(this + 232) != 0 )
    j__free(*(void **)(this + 232));
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  if ( *(uint32_t *)(this + 216) != 0 )
    j__free(*(void **)(this + 216));
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  `eh vector destructor iterator'((void *)(this + 20), 0x10u, 12, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x42E7C0 sub_42E7C0
// ------------------------------------------------------------
void /*stdcall*/ sub_42E7C0(int *a1, int *a2)
{
  int *i; // esi

  for ( i = a1; i != a2; i += 8 )
    sub_42DDD0(i);
}



// ------------------------------------------------------------
// 0x42E7F0 sub_42E7F0
// ------------------------------------------------------------
void /*thiscall*/ sub_42E7F0(int this)
{
  void **v2; // edi
  int v3; // eax

  v2 = *(void ***)(this + 60);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_657740(v2, 228);
  }
  *(uint32_t *)(this + 60) = 0;
  sub_42C370(this + 196);
  v3 = *(uint32_t *)(this + 184);
  if ( v3 != 0 )
  {
    sub_42CC00(v3, *(uint32_t *)(this + 188));
    j__free(*(void **)(this + 184));
  }
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  if ( *(uint32_t *)(this + 56) >= 0x10u )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x42E8F0 sub_42E8F0
// ------------------------------------------------------------
void */*thiscall*/ sub_42E8F0(void *this, char ArgList)
{
  sub_42DF70((int)this);
  nullsub_3();
  sub_476AF0(ArgList);
  return this;
}



// ------------------------------------------------------------
// 0x42E940 sub_42E940
// ------------------------------------------------------------
void /*thiscall*/ sub_42E940(void *this)
{
  nullsub_3();
  sub_42E7F0((int)this);
}



// ------------------------------------------------------------
// 0x42E990 sub_42E990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42E990(uint32_t *this, void *Block)
{
  void *v3; // edi
  uint32_t *result; // eax
  void *v5; // eax
  int v6; // edx

  off_77F3FC((char *)&byte_6C4180, Block);
  *(this + 20) = Block;
  v3 = (void *)*(this + 5);
  if ( Block == (void *)-1 )
  {
    if ( v3 != nullptr )
    {
      nullsub_3();
      sub_42E7F0((int)v3);
      j__free(v3);
    }
    result = (uint32_t *)*(this + 4);
    *(this + 5) = 0;
    result[27] = 0;
  }
  else
  {
    if ( v3 != nullptr )
    {
      nullsub_3();
      sub_42E7F0((int)v3);
      j__free(v3);
    }
    *(this + 5) = 0;
    v5 = operator new(0x1F0u);
    if ( v5 != nullptr )
      result = sub_42E8F0(v5, *(this + 20));
    else
      result = nullptr;
    v6 = *(this + 4);
    *(this + 5) = result;
    *(uint32_t *)(v6 + 108) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42EA90 sub_42EA90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42EA90(uint32_t *this)
{
  uint32_t *result; // eax

  sub_487080(dword_8F852C);
  sub_49A9A0(*((uint32_t *)dword_8F8528 + 634));
  *(this + 19) = -1;
  result = sub_42E990(this, (void *)0xFFFFFFFF);
  *(this + 8) = -1;
  if ( dword_99FF08 != 0 )
  {
    result = (uint32_t *)sub_48FD80(dword_99FF08);
    if ( result == nullptr )
      *(this + 47) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42EAF0 sub_42EAF0
// ------------------------------------------------------------
char /*thiscall*/ sub_42EAF0(uint32_t *this, int a2)
{
  int v3; // esi
  int v4; // ebx
  unsigned int v5; // ebx
  int v8; // [esp+18h] [ebp+8h]

  v3 = 20 * a2;
  v4 = *((int16_t *)dword_8F7C48 + 10 * a2);
  v8 = *((int16_t *)dword_8F7C48 + 10 * a2 + 1);
  if ( *(uint32_t *)(*(int (/*stdcall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 672))(3) >= v4
    && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) <= v8 )
  {
    v5 = dword_8F7D28[a2];
    if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < v5 )
      return 0;
  }
  *(this + 19) = a2;
  dword_8F7C40 = (int)dword_8F7C48 + v3;
  sub_42E990(this, (void *)(a2 + 2000));
  return 1;
}



// ------------------------------------------------------------
// 0x42EB90 sub_42EB90
// ------------------------------------------------------------
int /*thiscall*/ sub_42EB90(int this)
{
  int *v2; // esi
  int result; // eax
  int *i; // edi

  v2 = *(int **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(int **)(this + 8); v2 != i; v2 += 8 )
      sub_42DDD0(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42EBD0 sub_42EBD0
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_42EBD0(int this)
{
  uint8_t result; // al
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
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
    *(uint32_t *)(this + 16) = v6;
    sub_69A840(*((uint32_t *)v6 + 9));
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 16) + 40));
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    *(uint32_t *)(this + 76) = -1;
    result = (uint8_t)sub_42E990((uint32_t *)this, (void *)0xFFFFFFFF);
    *(uint8_t *)(this + 108) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42ECF0 sub_42ECF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42ECF0(uint32_t *this, int a2, int a3)
{
  sub_42D6A0((int)this);
  *(this + 91) = 0;
  *(this + 92) = 0;
  *(this + 93) = 0;
  *(this + 95) = 0;
  *(this + 96) = 0;
  *(this + 97) = 0;
  *(this + 100) = 0;
  *(this + 101) = 0;
  *(this + 102) = 0;
  *(this + 103) = 0;
  *(this + 104) = 0;
  *(this + 105) = 0;
  *(this + 106) = 0;
  *(this + 107) = 0;
  *(this + 108) = 0;
  *(this + 109) = 0;
  *(this + 110) = 0;
  *(this + 111) = 0;
  *(this + 112) = 0;
  *(this + 113) = 0;
  *(this + 114) = 0;
  *(this + 115) = 0;
  *(this + 123) = 0;
  *(this + 124) = 0;
  *(this + 125) = 0;
  *(this + 127) = 0;
  *(this + 128) = 0;
  *(this + 129) = 0;
  sub_48D9D0(this);
  sub_48F470(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x42EDE0 sub_42EDE0
// ------------------------------------------------------------
void /*thiscall*/ sub_42EDE0(int this)
{
  sub_48EAA0();
  sub_42E620((int *)(this + 504));
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  sub_42EB90(this + 376);
  sub_42EB90(this + 360);
  sub_42E710(this);
}



// ------------------------------------------------------------
// 0x42EE80 sub_42EE80
// ------------------------------------------------------------
char /*thiscall*/ sub_42EE80(int this)
{
  char result; // al
  void *v3; // edi
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // ecx
  void *v7; // edi
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  uint32_t *v11; // eax
  int v12; // [esp+Ch] [ebp-10h]

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    if ( dword_99FF08 != 0 )
    {
      nullsub_3();
      v12 = dword_99FF08 + 4;
      sub_424100(*(uint32_t **)(this + 16), 0);
      v3 = *(void **)(this + 28);
      if ( v3 != nullptr )
      {
        sub_42C770(*(uint32_t *)(this + 28));
        j__free(v3);
      }
      *(uint32_t *)(this + 28) = 0;
      v4 = operator new(0xA0u);
      if ( v4 != nullptr )
        v5 = sub_42D590(v4, 0);
      else
        v5 = nullptr;
      v6 = *(uint32_t **)(this + 16);
      *(uint32_t *)(this + 28) = v5;
      sub_424100(v6, (int)v5);
      sub_425500(*(uint32_t *)(this + 16), 0);
      v7 = *(void **)(this + 24);
      if ( v7 != nullptr )
      {
        sub_42EDE0(*(uint32_t *)(this + 24));
        j__free(v7);
      }
      *(uint32_t *)(this + 24) = 0;
      v8 = operator new(0x208u);
      if ( v8 != nullptr )
        v9 = sub_42ECF0(v8, *(uint32_t *)(v12 + 72), 0);
      else
        v9 = nullptr;
      v10 = *(uint32_t *)(this + 16);
      *(uint32_t *)(this + 24) = v9;
      sub_425500(v10, (int)v9);
      *(uint32_t *)(this + 88) = 0;
      *(uint32_t *)(this + 92) = 0;
      *(uint32_t *)(this + 124) = 0;
      *(uint32_t *)(this + 132) = 0;
      *(uint32_t *)(this + 128) = 0;
      if ( *(uint32_t *)(this + 140) != 0 )
        j__free(*(void **)(this + 140));
      *(uint32_t *)(this + 140) = 0;
      *(uint32_t *)(this + 144) = 0;
      *(uint32_t *)(this + 148) = 0;
      *(uint8_t *)(this + 108) = 0;
      *(uint32_t *)(this + 152) = 2;
      *(uint8_t *)(this + 168) = 0;
      sub_41CAA0(*(void **)(*(uint32_t *)(this + 68) + 4));
      *(uint32_t *)(*(uint32_t *)(this + 68) + 4) = *(uint32_t *)(this + 68);
      v11 = *(uint32_t **)(this + 68);
      *(uint32_t *)(this + 72) = 0;
      *v11 = v11;
      *(uint32_t *)(*(uint32_t *)(this + 68) + 8) = *(uint32_t *)(this + 68);
      result = sub_49B930(*((uint32_t **)dword_8F8528 + 634), "dungeon/warroom/warroomBattleTalk.tlk");
      *(uint8_t *)(this + 184) = 0;
      *(uint32_t *)(this + 188) = 0;
    }
    else
    {
      return off_77F3FC(aCnwarroomGetmy);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F050 sub_42F050
// ------------------------------------------------------------
void /*thiscall*/ sub_42F050(int *this, int ArgList)
{
  void *v3; // edi
  void *v4; // edi
  void *v5; // edi

  off_77F3FC((char *)&byte_6C41F8, ArgList);
  v3 = (void *)*(this + 7);
  if ( v3 != nullptr )
  {
    sub_42C770(*(this + 7));
    j__free(v3);
  }
  v4 = (void *)*(this + 6);
  *(this + 7) = 0;
  if ( v4 != nullptr )
  {
    sub_42EDE0((int)v4);
    j__free(v4);
  }
  v5 = (void *)*(this + 5);
  *(this + 6) = 0;
  if ( v5 != nullptr )
  {
    sub_42E940(v5);
    j__free(v5);
  }
  *(this + 5) = 0;
}



// ------------------------------------------------------------
// 0x42F0D0 sub_42F0D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42F0D0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // edi
  void *v4; // edi
  void *v5; // edi
  void *v6; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *(uint8_t *)(this + 4) = 0;
    if ( v2 != nullptr )
      (**v2)(v2, 1);
    v3 = *(void **)(this + 16);
    *(uint32_t *)(this + 12) = 0;
    if ( v3 != nullptr )
    {
      sub_42BD40((int)v3);
      j__free(v3);
    }
    v4 = *(void **)(this + 20);
    *(uint32_t *)(this + 16) = 0;
    if ( v4 != nullptr )
    {
      sub_42E940(v4);
      j__free(v4);
    }
    v5 = *(void **)(this + 24);
    *(uint32_t *)(this + 20) = 0;
    if ( v5 != nullptr )
    {
      sub_42EDE0((int)v5);
      j__free(v5);
    }
    v6 = *(void **)(this + 28);
    *(uint32_t *)(this + 24) = 0;
    if ( v6 != nullptr )
    {
      sub_42C770((int)v6);
      j__free(v6);
    }
    *(uint32_t *)(this + 28) = 0;
  }
}



// ------------------------------------------------------------
// 0x42F160 sub_42F160
// ------------------------------------------------------------
void /*thiscall*/ sub_42F160(int this, unsigned int a2, int a3)
{
  int v4; // edi
  int v5; // ecx

  v4 = *(uint32_t *)(this + 32);
  v5 = this + 36;
  *(uint32_t *)(this + 32) = a2;
  *(uint8_t *)(v5 + 13) = 0;
  *(uint8_t *)(v5 + 14) = 0;
  sub_698F90(v5, 0, a3);
  if ( a2 <= 1 )
    sub_424A40(*(uint32_t **)(this + 16), dword_8F7C04);
  switch ( a2 )
  {
    case 0xFFFFFFFF:
      sub_42F050((int *)this, v4);
      break;
    case 0u:
      sub_42BF10(this, v4);
      break;
    case 1u:
      sub_42C000((int *)this, v4);
      break;
    case 2u:
      sub_42E270(this, v4);
      break;
    case 3u:
      sub_42B610((uint32_t *)this, v4);
      break;
    case 4u:
      sub_42C820((uint32_t *)this, v4);
      break;
    default:
      return;
  }
}



// ------------------------------------------------------------
// 0x42F220 sub_42F220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42F220(uint32_t *this)
{
  if ( *(this + 37) == -1 )
    sub_4938F0((int)this);
  return this + 15;
}



// ------------------------------------------------------------
// 0x42F240 sub_42F240
// ------------------------------------------------------------
int /*thiscall*/ sub_42F240(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 26);
  if ( v1 != 0 )
    return *(uint32_t *)v1;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x42F250 sub_42F250
// ------------------------------------------------------------
int /*thiscall*/ sub_42F250(int this)
{
  *(uint32_t *)(this + 96) = 18;
  *(uint32_t *)(this + 308) = 4;
  *(uint32_t *)(this + 312) = 4;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0xFFFF;
  *(uint32_t *)(this + 344) = 0xFFFF;
  *(uint32_t *)(this + 348) = 0xFFFF;
  *(uint32_t *)(this + 352) = 0xFFFF;
  *(uint32_t *)(this + 356) = 0xFFFF;
  *(uint32_t *)(this + 360) = 0xFFFF;
  *(uint32_t *)(this + 364) = 0xFFFF;
  *(uint32_t *)(this + 368) = 0xFFFF;
  *(uint32_t *)(this + 372) = 0xFFFF;
  *(uint32_t *)(this + 376) = 0xFFFF;
  *(uint32_t *)(this + 556) = 0;
  *(uint32_t *)(this + 560) = 0;
  *(uint32_t *)(this + 564) = 0;
  *(uint32_t *)(this + 568) = 0;
  *(uint8_t *)(this + 572) = 0;
  *(uint8_t *)(this + 573) = 0;
  *(uint32_t *)(this + 576) = 0;
  *(uint32_t *)(this + 580) = 0;
  *(uint32_t *)(this + 612) = 0;
  *(uint8_t *)(this + 616) = 0;
  *(uint32_t *)(this + 620) = 0;
  *(uint32_t *)(this + 624) = 0;
  *(uint32_t *)(this + 628) = 0;
  *(uint32_t *)(this + 632) = 0;
  *(uint32_t *)(this + 636) = -1;
  *(uint32_t *)(this + 640) = 0;
  *(uint32_t *)(this + 644) = 0;
  *(uint32_t *)(this + 656) = 0;
  *(uint32_t *)(this + 648) = 0;
  *(uint8_t *)(this + 652) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x42F350 CNRDVirtualCharacter__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmtC(int *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int result; // eax

  CNRDObject__vmtC(this);
  sub_49FD20(*(this + 28));
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);
  result = (*(int (/*thiscall*/ **)(int *, int))(v2 + 372))(this, v4);
  *((uint8_t *)this + 573) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42F390 CNRDVirtualCharacter__vmt19C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt19C(int *this)
{
  int v2; // eax
  int v3; // edi
  bool v4; // cc
  int v5; // edi
  bool v6; // cc
  int v7; // eax
  int v8; // ecx
  int result; // eax
  int v10; // [esp-8h] [ebp-18h]
  int v11; // [esp-8h] [ebp-18h]
  int v12; // [esp-4h] [ebp-14h]
  int v13; // [esp-4h] [ebp-14h]
  int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]

  v2 = *(this + 81);
  v3 = *(this + 79);
  v4 = v2 <= v3;
  if ( v2 < v3 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v3 && *(this + 77) == 1 )
      goto LABEL_4;
    v4 = *(this + 81) <= v3;
  }
  if ( !v4 && (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 79) && *(this + 77) == 0 )
  {
LABEL_4:
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    CNRDObject__vmt70(this, *(this + 79), v10, v12);
LABEL_5:
    *(this + 77) = 4;
    goto LABEL_6;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) >= *(this + 79) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 79) )
      goto LABEL_5;
    *(this + 77) = 0;
  }
  else
  {
    *(this + 77) = 1;
  }
LABEL_6:
  v5 = *(this + 80);
  v6 = *(this + 82) <= v5;
  if ( *(this + 82) < v5 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > v5 && *(this + 78) == 3 )
      goto LABEL_9;
    v6 = *(this + 82) <= v5;
  }
  if ( !v6 && (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 80) && *(this + 78) == 2 )
  {
LABEL_9:
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v11 = *(this + 80);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    CNRDObject__vmt70(this, v7, v11, v13);
LABEL_10:
    *(this + 78) = 4;
    goto LABEL_11;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= *(this + 80) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 80) )
      goto LABEL_10;
    *(this + 78) = 2;
  }
  else
  {
    *(this + 78) = 3;
  }
LABEL_11:
  v8 = *(this + 78);
  result = *(this + 77);
  v15 = v8 != 4 ? 186 : 223;
  v14 = result != 4 ? 122 : 149;
  if ( result == 4 )
  {
    v15 = 0;
  }
  else if ( result == 0 )
  {
    v15 = -(v8 != 4 ? 186 : 223);
  }
  if ( v8 == 4 )
  {
    v14 = 0;
  }
  else if ( v8 == 2 )
  {
    v14 = -(result != 4 ? 122 : 149);
  }
  *(float *)(*(this + 28) + 16) = (float)v15;
  *(float *)(*(this + 28) + 20) = (float)v14;
  return result;
}



// ------------------------------------------------------------
// 0x42F5D0 CNRDVirtualCharacter__vmt170
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt170(void *this, int a2, int a3, int a4, int a5)
{
  int v5; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edi

  v5 = a2;
  v7 = a5 != 4 ? 186 : 223;
  v8 = a4 != 4 ? 122 : 149;
  if ( a4 != 0 )
  {
    if ( a4 != 1 )
      goto LABEL_6;
    v9 = 500 * v7;
  }
  else
  {
    v9 = -500 * v7;
  }
  v5 = v9 / 1000 + a2;
LABEL_6:
  if ( a5 == 2 )
  {
    v10 = -500 * v8 / 1000 + a3;
  }
  else
  {
    v10 = a3;
    if ( a5 == 3 )
      v10 = 500 * v8 / 1000 + a3;
  }
  if ( a4 == 4 && a5 == 4 )
  {
    if ( (int)abs32(v5 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)) < 50 )
      v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
    if ( (int)abs32(v10 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this)) < 50 )
      v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  }
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 372))(this, v5, v10);
}



// ------------------------------------------------------------
// 0x42F6E0 CNRDVirtualCharacter__vmt16C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt16C(int *this, int a2, int a3, uint8_t a4)
{
  int result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax

  result = *(this + 162);
  if ( result == 0 || *(uint8_t *)(result + 284) == 0 )
  {
    v5 = (a4 - 1) / 3;
    v6 = (a4 - 1) % 3;
    if ( v6 != 0 )
      v6 = v6 != 1 ? 1 : 4;
    if ( v5 != 0 )
      v7 = 2 * (v5 == 1) + 2;
    else
      v7 = 3;
    return (*(int (/*thiscall*/ **)(int *, int, int, int, int))(*this + 368))(this, a2, a3, v6, v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F750 CNRDVirtualCharacter__vmt174
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt174(int *this, int a2, int a3)
{
  int result; // eax
  int v4; // eax

  result = *(this + 162);
  if ( result == 0 || *(uint8_t *)(result + 284) == 0 )
  {
    *(this + 79) = a2;
    v4 = *this;
    *(this + 80) = a3;
    return (*(int (**)(void))(v4 + 412))();
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F790 CNRDVirtualCharacter__vmt17C
// ------------------------------------------------------------
bool /*thiscall*/ CNRDVirtualCharacter__vmt17C(uint32_t *this, int a2, int a3)
{
  bool result; // al
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // [esp-10h] [ebp-18h]
  int v10; // [esp-Ch] [ebp-14h]
  int v11; // [esp-8h] [ebp-10h]

  result = *(this + 29) != 0
        && (v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8),
            v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this),
            v6 = sub_45E490(v5, v11),
            v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8),
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
            v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this),
            v8 = sub_45E4D0(v7, v9, v10, 1.0),
            a2 >= v6 - 30)
        && a2 < v6 + 30
        && a3 >= v8 - 100
        && a3 < v8 + 10;
  return result;
}



// ------------------------------------------------------------
// 0x42F820 CNRDVirtualCharacter__vmt178
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt178(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  char v4; // bl
  int v5; // eax
  int v6; // edi
  int v7; // edi
  int v8; // [esp+4h] [ebp-8h] BYREF
  uint8_t v9[4]; // [esp+8h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) != *(this + 83)
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this)) != *(this + 84) )
  {
    v3 = *(this + 78);
    v4 = 0;
    if ( v3 == 4 )
    {
      v4 = 3;
    }
    else if ( v3 == 2 )
    {
      v4 = 6;
    }
    v5 = *(this + 77);
    if ( v5 == 4 )
    {
      ++v4;
    }
    else if ( v5 == 1 )
    {
      v4 += 2;
    }
    sub_423200(dword_8F7B08, 37);
    v6 = dword_8F7B08;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_423290(v6, (int)&v8, 2);
    v7 = dword_8F7B08;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    sub_423290(v7, (int)&v8, 2);
    v9[0] = v4 + 1;
    sub_423290(dword_8F7B08, (int)v9, 1);
    sub_423380(dword_8F7B08);
    *(this + 83) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    *(this + 84) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F910 CNRDVirtualCharacter__vmt180
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt180(int *this, int a2, int a3, int a4, int a5, float a6)
{
  int v6; // ebx
  uint32_t *v7; // eax
  int v8; // [esp+8h] [ebp-10h]
  float v10; // [esp+10h] [ebp-8h]
  float v11; // [esp+14h] [ebp-4h]

  v6 = *(this + 76);
  v8 = dword_77F6DC;
  dword_77F6DC = 1065353216;
  if ( *(uint32_t *)(v6 + 148) == -1 )
    sub_4938F0(v6);
  v10 = *(float *)(v6 + 80);
  if ( *(uint32_t *)(v6 + 148) == -1 )
    sub_4938F0(v6);
  v11 = *(float *)(v6 + 84);
  if ( v10 != a6 || v11 != a6 )
    sub_4920E0((uint32_t *)v6, a6, a6);
  v7 = (uint32_t *)dword_79C0B0;
  *(uint32_t *)(dword_79C0B0 + 56) = a2 + a4;
  v7[12] = a2;
  v7[13] = a3;
  v7[15] = a3 + a5;
  sub_492550(
    dword_79C0B0,
    a2 + (uint64_t)((double)*(this + 144) * a6) + a4 / 2,
    a3 + (uint64_t)((double)*(this + 145) * a6) + a5 / 2,
    0.0,
    0);
  sub_488670(dword_79C0B0);
  if ( v10 == a6 && v11 == a6 )
  {
    dword_77F6DC = v8;
  }
  else
  {
    sub_4920E0((uint32_t *)v6, v10, v11);
    dword_77F6DC = v8;
  }
}



// ------------------------------------------------------------
// 0x42FA60 CNRDVirtualCharacter__vmt160
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt160(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // edx

  if ( a3 != 0xFFFF )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 404))(this, a3);
  v4 = sub_4B0210(*(this + 71), a2);
  v5 = *this;
  if ( v4 == 0xFFFF )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 408))(this, a2);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 404))(this, v4);
}



// ------------------------------------------------------------
// 0x42FAC0 CNRDVirtualCharacter__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt12C(uint32_t *this, int a2)
{
  int result; // eax

  result = CNRDObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x42FB00 sub_42FB00
// ------------------------------------------------------------
int /*thiscall*/ sub_42FB00(uint32_t *this, int a2)
{
  uint32_t *v2; // esi
  int i; // edi
  int result; // eax

  v2 = this + 160;
  for ( i = 2; i != 0; --i )
  {
    if ( *v2 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FB30 sub_42FB30
// ------------------------------------------------------------
bool /*thiscall*/ sub_42FB30(uint32_t *this, int a2)
{
  int v2; // eax
  bool result; // al

  result = false;
  if ( a2 != 0 )
  {
    v2 = *(this + 162);
    if ( v2 != 0 && a2 == v2 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FB60 CNRDVirtualCharacter__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt70(uint32_t *this, int a2, int a3, int a4)
{
  int result; // eax
  int v6; // ecx

  result = CNRDObject__vmt70(this, a2, a3, a4);
  v6 = *(this + 162);
  if ( v6 != 0 )
    result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 112))(v6, a2, a3, a4);
  *(this + 80) = a3;
  *(this + 82) = a3;
  *(this + 79) = a2;
  *(this + 81) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x42FBB0 sub_42FBB0
// ------------------------------------------------------------
int /*thiscall*/ sub_42FBB0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  if ( *(this + 162) != 0 )
    return sub_4BD440(a2, a3, a4, a5);
  else
    return off_77F3FC("Cannot prepare private store.");
}



// ------------------------------------------------------------
// 0x42FBE0 sub_42FBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_42FBE0(uint32_t *this)
{
  uint8_t *v1; // ecx
  char result; // al

  v1 = (uint8_t *)*(this + 162);
  if ( v1 != nullptr )
  {
    v1[284] = 0;
    v1[285] = 0;
    v1[340] = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FBF0 sub_42FBF0
// ------------------------------------------------------------
char /*thiscall*/ sub_42FBF0(uint32_t *this)
{
  int v1; // ecx
  char result; // al

  v1 = *(this + 162);
  if ( v1 != 0 )
  {
    result = *(uint8_t *)(v1 + 284);
    if ( result != 0 )
    {
      result = *(uint8_t *)(v1 + 285);
      if ( result != 0 )
        *(uint8_t *)(v1 + 285) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FC00 sub_42FC00
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC00(int *this, void *a2)
{
  int result; // eax

  result = *(this + 162);
  if ( result != 0 )
  {
    *(uint8_t *)(result + 285) = 0;
    return sub_4BD690(a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FC30 sub_42FC30
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC30(int this, int a2)
{
  int result; // eax

  result = a2;
  *(uint8_t *)(this + 652) = a2;
  if ( *(uint32_t *)(this + 648) != 0 )
    return sub_4BD500(a2);
  return result;
}



// ------------------------------------------------------------
// 0x42FC50 sub_42FC50
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC50(uint32_t *this)
{
  int result; // eax

  result = *(this + 164);
  if ( result != 0 )
    return sub_4BE180(result + 284);
  return result;
}



// ------------------------------------------------------------
// 0x42FC70 sub_42FC70
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC70(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 88;
  return result;
}



// ------------------------------------------------------------
// 0x42FC90 sub_42FC90
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC90(int *this)
{
  int result; // eax

  result = *(this + 11);
  if ( result != 0 )
    return (*(this + 12) - result) / 88;
  return result;
}



// ------------------------------------------------------------
// 0x42FCB0 sub_42FCB0
// ------------------------------------------------------------
int /*cdecl*/ sub_42FCB0(int a1)
{
  if ( dword_9A0128 == 0 )
  {
    if ( (dword_8F8150 & 1) == 0 )
    {
      dword_8F8150 |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BF450);
    }
    dword_9A0128 = (int)&unk_8F8130;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x42FD40 sub_42FD40
// ------------------------------------------------------------
bool /*thiscall*/ sub_42FD40(void *this, const char *a2)
{
  return strcmp((const char *)sub_41ACF0(this), a2) != 0;
}



// ------------------------------------------------------------
// 0x42FDA0 sub_42FDA0
// ------------------------------------------------------------
int /*usercall*/ sub_42FDA0@<eax>(int a1@<ebx>, int a2@<esi>, int a3, int a4, int a5, int a6, int a7)
{
  int result; // eax
  int v8; // edi
  int v9; // esi
  int v10; // ebx
  uint64_t v11; // rax
  int v12; // ebx
  int v13; // esi
  int v14; // eax
  const char *v15; // eax
  int v16; // eax
  unsigned int v17; // eax
  const char *v18; // esi
  int v19; // eax
  const char *v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  uint32_t *v27; // ebx
  int v28; // edi
  int v29; // eax
  int v31; // [esp-8h] [ebp-94h]
  int v33; // [esp+4h] [ebp-88h]
  int v34; // [esp+4h] [ebp-88h]
  char Buffer[64]; // [esp+8h] [ebp-84h] BYREF
  char v36[64]; // [esp+48h] [ebp-44h] BYREF
  int v37; // [esp+88h] [ebp-4h]

  result = dword_796E50;
  v8 = a6;
  v37 = dword_796E50;
  if ( a6 != 0 )
  {
    v9 = a5;
    if ( a5 != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a5 + 40))(a5, 17) == 0
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 940))(v9) == 0
        || (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 376))(v9),
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04),
            v10 == result) )
      {
        sub_424680((int)&a3, (int)&a4, 0.0, 0.0);
        v11 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v9 + 192))(v9, a1, a2)
                               * *(float *)&dword_77F6DC);
        v12 = a7;
        a6 = a4 - v11 - 34;
        if ( a7 != 0 )
        {
          v13 = a3 - (*(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36) >> 1);
          v33 = dword_77F6DC;
          dword_77F6DC = 1065353216;
          sub_4938F0(v12);
          sub_491D00(dword_79C0B0, v13, a6 - 26, 0.0);
          dword_77F6DC = v33;
        }
        v34 = -5000269;
        if ( *(uint32_t *)(v8 + 112) == 1 )
        {
          v34 = -6567706;
        }
        else if ( v8 != sub_429830((uint16_t)word_77F804) || *(uint32_t *)(v8 + 184) != 0 )
        {
          if ( *(uint8_t *)(v8 + 188) != 0 )
            v34 = -6400;
        }
        else
        {
          v34 = -1;
        }
        v14 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v14 == 4 || v14 == 6 )
        {
          v36[0] = 0;
          v17 = *(uint32_t *)(v8 + 40);
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
          {
            if ( v17 < 0x10 )
              v18 = (const char *)(v8 + 20);
            else
              v18 = *(const char **)(v8 + 20);
            v19 = sub_41A5E0(v8 + 53);
            sprintf(Buffer, "Lv.%d %s", v19, v18);
          }
          else
          {
            if ( v17 < 0x10 )
              v20 = (const char *)(v8 + 20);
            else
              v20 = *(const char **)(v8 + 20);
            sprintf(Buffer, "%s", v20);
          }
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && dword_99FEC0 != 0 && (uint8_t)sub_48F620() != 0
            || *(uint32_t *)(dword_8F7A24 + 12) == 6 && dword_99FF08 != 0 && (uint8_t)sub_48FD20() != 0 )
          {
            v21 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 196) + 376))(*(uint32_t *)(v8 + 196));
            if ( v21 != 0 )
            {
              if ( v21 == 1 )
                v34 = -20736;
            }
            else
            {
              v34 = -16771841;
            }
          }
        }
        else
        {
          if ( *(uint32_t *)(v8 + 40) < 0x10u )
            v15 = (const char *)(v8 + 20);
          else
            v15 = *(const char **)(v8 + 20);
          sprintf(Buffer, "%s", v15);
          v16 = sub_41A5E0(v8 + 53);
          sprintf(v36, "Lv.%d", v16);
        }
        v22 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Buffer);
        v23 = a3 - v22 / 2;
        if ( *(uint32_t *)(v8 + 112) == 1 )
        {
          v23 += 11;
          if ( dword_8F8124 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8124 + 152))(
              dword_8F8124,
              v23 - 18,
              a6 - 2,
              dword_79C0B0);
        }
        else if ( *(uint32_t *)(v8 + 120) != 0 )
        {
          v24 = sub_4BF0F0(*(void **)(v8 + 120));
          v25 = sub_4BE300(v24);
          if ( v25 != 0 )
            sub_40FC80(v23 - 26, a6 - 2, v25);
        }
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);
        if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )
        {
          v26 = a6;
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            a6 - 38,
            v34,
            Buffer);
        }
        else
        {
          v26 = a6;
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            a6 - 9,
            v34,
            Buffer);
        }
        if ( v36[0] != 0 )
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            v26 + 7,
            v34,
            v36);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        result = dword_8F7C04;
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
        {
          v27 = (uint32_t *)sub_42A410(v8);
          v28 = sub_42A430(v8);
          if ( v36[0] != 0 )
          {
            sub_491530(2, 0);
            v29 = v23 + (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v36, v31);
            if ( v28 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v28 + 152))(v28, v29, a6 + 4, dword_79C0B0);
            sub_491630(2);
            result = v23 + (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v36);
            if ( v27 != nullptr )
              return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v27 + 152))(v27, result, a6 + 4, dword_79C0B0);
          }
          else
          {
            sub_491530(2, 0);
            if ( v28 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v28 + 152))(
                v28,
                a3 - (v27[5] >> 1),
                a6 + 4,
                dword_79C0B0);
            result = sub_491630(2);
            if ( v27 != nullptr )
              return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v27 + 152))(
                       v27,
                       a3 - (v27[5] >> 1),
                       a6 + 4,
                       dword_79C0B0);
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x430230 sub_430230
// ------------------------------------------------------------
char /*thiscall*/ sub_430230(uint32_t **this)
{
  int v2; // eax
  int *v3; // eax
  int v5; // [esp+4h] [ebp-10h] BYREF
  int v6; // [esp+8h] [ebp-Ch] BYREF
  int v7; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h] BYREF

  if ( *(this + 162) != nullptr )
  {
    sub_4BD470(&v6, &v5, &v7, &v8);
    v2 = *(uint32_t *)(dword_8F7A24 + 20);
    if ( *(uint32_t *)(v2 + 100) == v6 )
    {
      v3 = *(int **)(v2 + 104);
      if ( v3 != nullptr )
        v2 = *v3;
      else
        v2 = -1;
      if ( v2 == v5 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(this + 162) + 112))(*(this + 162), v7, v8, 0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[93])(this, v7, v8);
        sub_4BD4B0(*(this + 162));
        LOBYTE(v2) = *((uint8_t *)this + 652);
        if ( (uint8_t)v2 != 0 )
          LOBYTE(v2) = sub_42FC30((int)this, 0);
      }
    }
  }
  else
  {
    LOBYTE(v2) = off_77F3FC("Cannot create private store.");
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4302E0 sub_4302E0
// ------------------------------------------------------------
int sub_4302E0()
{
  int result; // eax

  dword_77F92C = dword_99FCCC;
  byte_77F8FC = 0;
  byte_77F8FD = 0;
  byte_77F8FF = 0;
  dword_77F908 = 0;
  dword_77F90C = 6;
  dword_77F910 = 12;
  dword_77F914 = 0;
  dword_77F918 = 1600;
  dword_77F91C = 0;
  dword_77F920 = 0;
  dword_77F924 = 0;
  dword_77F928 = 0;
  byte_77F8FE = 1;
  dword_77F900 = -16777216;
  dword_8F811C = sub_418DD0(100);
  dword_8F8120 = sub_418DD0(99);
  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Temp/AdminIcon.img");
  result = sub_418DD0(0);
  dword_8F8124 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4303B0 CNRDVirtualCharacter__vmt88
// ------------------------------------------------------------
bool /*thiscall*/ CNRDVirtualCharacter__vmt88(uint32_t *this, int a2, int a3, uint32_t *a4)
{
  int v4; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // esi
  int v9; // ebx
  int v10; // edi
  int v11; // [esp+10h] [ebp+10h]

  if ( a4 != nullptr )
    *a4 = 0;
  v4 = *(this + 29);
  if ( v4 == 0 )
    return true;
  v6 = *(uint32_t *)(*(uint32_t *)(v4 + 132) + 44);
  v11 = v6;
  if ( v6 == 0 )
    return true;
  v7 = *(uint32_t *)(v6 + 232);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(v6 + 236) - v7) >> 4;
  else
    v8 = 0;
  v9 = 0;
  if ( v8 > 0 )
  {
    v10 = 0;
    while ( (uint8_t)sub_48C0A0(a2, a3, v10 + *(uint32_t *)(v6 + 232)) == 0 )
    {
      ++v9;
      v10 += 16;
      if ( v9 >= v8 )
        break;
      v6 = v11;
    }
  }
  return v9 != v8;
}



// ------------------------------------------------------------
// 0x430450 sub_430450
// ------------------------------------------------------------
// attributes: thunk
int sub_430450()
{
  return sub_406E40();
}



// ------------------------------------------------------------
// 0x430460 sub_430460
// ------------------------------------------------------------
int /*thiscall*/ sub_430460(uint32_t *this)
{
  int result; // eax
  void *v2; // edi
  uint32_t *v3; // esi
  uint8_t v4[4]; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+4h] [ebp-1Ch]
  int v6; // [esp+8h] [ebp-18h]
  int v7; // [esp+Ch] [ebp-14h]
  int i; // [esp+10h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-4h]

  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 44);
    v2 = *(void **)(result + 104);
    if ( v2 != nullptr )
    {
      v3 = this + 160;
      for ( i = 2; i != 0; --i )
      {
        if ( *v3 != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v3 + 12))(*v3, 0);
          (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*v3 + 92))(*v3, v4);
          v9 = 0;
          sub_4600B0(v2, 2, 0, (int)v4);
          v9 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v6 = 0;
          v7 = 0;
        }
        ++v3;
        result = i - 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x430510 CNRDVirtualCharacter__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ sub_430510(int *this)
{
  unsigned int v2; // ebx
  int v3; // edi
  int v4; // edi
  bool v5; // cc
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  void *v16; // ecx
  void *v17; // eax
  bool v18; // zf
  int *v19; // ecx
  int v20; // eax
  int v21; // edi
  int *v22; // edi
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // ebx
  uint32_t *v34; // edi
  void *v35; // ecx
  int v36; // ecx
  int v37; // ecx
  int v39; // [esp-8h] [ebp-48h]
  int v40; // [esp-4h] [ebp-44h]
  int v41; // [esp-4h] [ebp-44h]
  char v42[4]; // [esp+Ch] [ebp-34h] BYREF
  void *Block; // [esp+10h] [ebp-30h]
  char v44[4]; // [esp+1Ch] [ebp-24h] BYREF
  void *v45; // [esp+20h] [ebp-20h]
  int v46; // [esp+24h] [ebp-1Ch]
  int v47; // [esp+28h] [ebp-18h]
  int v48; // [esp+2Ch] [ebp-14h]
  int v49; // [esp+30h] [ebp-10h]
  int v50; // [esp+3Ch] [ebp-4h]

  nullsub_3(this);
  v2 = 4;
  if ( *(this + 77) != 4 )
  {
    v3 = *(this + 77);
    if ( v3 != (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )
      (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v3);
  }
  if ( *(this + 50) == 0 )
  {
    if ( *(this + 77) == 4 && *(this + 78) == 4 )
    {
      if ( *(this + 30) != *(this + 74) )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 74));
        sub_4926A0(*(this + 30));
        if ( *(this + 71) == 2 )
          *(this + 159) = -1;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);
      }
      if ( *(this + 71) == 2 )
      {
        v4 = *(uint32_t *)(*(this + 30) + 148);
        v5 = *(this + 159) < v4;
        if ( *(this + 159) > v4 )
        {
          while ( 1 )
          {
            v6 = *(this + 30);
            v7 = *(uint32_t *)(v6 + 44);
            v8 = v6 + 40;
            v9 = v7 != 0 ? (*(uint32_t *)(v8 + 8) - v7) / 88 : 0;
            v10 = *(this + 159);
            if ( v10 >= v9 )
              break;
            v40 = *(this + 93);
            *(this + 159) = v10 + 1;
            sub_4C23A0(this, v10 + 1, v40);
          }
          *(this + 159) = -1;
          v5 = *(this + 159) < v4;
        }
        if ( v5 )
        {
          do
          {
            v41 = *(this + 93);
            v39 = *(this + 159) + 1;
            *(this + 159) = v39;
            sub_4C23A0(this, v39, v41);
          }
          while ( *(this + 159) < v4 );
        }
      }
    }
    else if ( *(this + 30) != *(this + 75) )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 75));
      sub_4926A0(*(this + 30));
      (*(void (/*thiscall*/ **)(int *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
        this,
        "WALK_STONE_LOOP",
        0,
        0,
        0);
    }
  }
  v11 = *(this + 139);
  if ( v11 != 0 && *(this + 29) != 0 )
  {
    if ( *((uint8_t *)this + 572) == 0 || *(this + 30) == *(this + 74) )
    {
      if ( *((uint8_t *)this + 573) == 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 12))(v11, 0);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v12 = *(this + 140) + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      else
        v12 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - *(this + 140);
      v13 = *(uint32_t *)*(this + 139);
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, *(this + 142) + v14);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(v13 + 40))(*(this + 139), v12, *(this + 141) + v15);
      (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 139) + 92))(*(this + 139), v42);
      v16 = (void *)*(this + 29);
      v50 = 0;
      sub_4600B0(v16, 2, 0, (int)v42);
      v17 = Block;
      v18 = Block == nullptr;
      *((uint8_t *)this + 573) = 1;
      v50 = -1;
      if ( !v18 )
        j__free(v17);
      v2 = 4;
    }
    else
    {
      *((uint8_t *)this + 573) = 0;
    }
  }
  v19 = this;
  if ( (int *)dword_8F7C08 != this )
    goto LABEL_68;
  sub_430460(this);
  v20 = *(this + 162);
  if ( v20 == 0 || *(uint8_t *)(v20 + 284) == 0 )
  {
    v21 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 12) + 8);
    v49 = 4;
    if ( v21 != 0
      && (uint8_t)sub_45E680(v21) != 0
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 40))(v21, 34) == 0 )
    {
      v22 = *(int **)(*((uint32_t *)dword_8F8528 + 12) + 8);
      if ( (*(int (/*thiscall*/ **)(int *, int *, uint32_t))(*v22 + 8))(v22, this, 0) <= 80 )
      {
        v26 = v49;
        byte_8F8118 = 0;
        goto LABEL_46;
      }
      v23 = (*(int (/*thiscall*/ **)(int *))(*v22 + 120))(v22);
      v24 = *v22;
      v48 = v23;
      v25 = (*(int (/*thiscall*/ **)(int *))(v24 + 124))(v22);
      byte_8F8118 = 1;
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 372))(this, v48, v25);
      v26 = 4;
    }
    else
    {
      v27 = sub_4BF3D0(&unk_9A0310);
      v28 = sub_4BF3D0(&unk_9A0320);
      v2 = 0;
      if ( v27 != 2 )
      {
        LOBYTE(v2) = v27 != 3;
        v2 = ((v2 - 1) & 0xFFFFFFFD) + 4;
      }
      if ( v28 != 0 )
      {
        v49 = (v28 != 1) + 3;
        v26 = v49;
      }
      else
      {
        v26 = 2;
      }
      if ( v2 != 4 || v26 != 4 )
      {
        byte_8F8118 = 0;
        goto LABEL_46;
      }
    }
    if ( byte_8F8118 == 0 )
    {
LABEL_46:
      *(this + 77) = v2;
      *(this + 78) = v26;
      v49 = v26 != 4 ? 186 : 223;
      v48 = v2 != 4 ? 122 : 149;
      if ( v2 == 4 )
      {
        v49 = 0;
      }
      else if ( v2 == 0 )
      {
        v49 = -(v26 != 4 ? 186 : 223);
      }
      if ( v26 == 4 )
      {
        v48 = 0;
      }
      else if ( v26 == 2 )
      {
        v48 = -(v2 != 4 ? 122 : 149);
      }
      v29 = *(this + 162);
      if ( v29 != 0 && *(uint8_t *)(v29 + 284) != 0 )
      {
        v49 = 0;
        v48 = 0;
      }
      *(float *)(*(this + 28) + 16) = (float)v49;
      *(float *)(*(this + 28) + 20) = (float)v48;
LABEL_69:
      v30 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v31 = *this;
      *(this + 81) = v30;
      *(this + 82) = (*(int (/*thiscall*/ **)(int *))(v31 + 124))(this);
      LOBYTE(v32) = *((uint8_t *)this + 616);
      if ( (uint8_t)v32 != 0 )
      {
        v32 = *(this + 29);
        if ( v32 != 0 )
        {
          v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          v49 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
          v34 = this + 156;
          v48 = 3;
          do
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*v34 + 40))(*v34, v33, v49, 0);
            (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*v34 + 92))(*v34, v44);
            v35 = (void *)*(this + 29);
            v50 = 1;
            sub_4600B0(v35, 2, 0, (int)v44);
            v50 = -1;
            if ( v45 != nullptr )
              j__free(v45);
            ++v34;
            v18 = v48 == 1;
            v45 = nullptr;
            v46 = 0;
            v47 = 0;
            --v48;
          }
          while ( !v18 );
          v32 = sub_699000((int)(this + 2));
          if ( v32 >= *(this + 155) + 1300 )
          {
            if ( (int *)dword_8F7C08 == this )
              LOBYTE(v32) = sub_44E8D0((char *)dword_8F8528, (void *)0x29, 0, *(this + 72));
            *((uint8_t *)this + 616) = 0;
          }
        }
      }
      v36 = *(this + 162);
      if ( v36 != 0 )
      {
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v36 + 80))(v36);
        if ( v32 != *(this + 29) )
          LOBYTE(v32) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 162) + 28))(*(this + 162));
      }
      v37 = *(this + 164);
      if ( v37 != 0 )
      {
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v37 + 80))(v37);
        if ( v32 != *(this + 29) )
          LOBYTE(v32) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 164) + 28))(*(this + 164));
      }
      return v32;
    }
  }
  v19 = this;
LABEL_68:
  (*(void (/*thiscall*/ **)(int *))(*this + 412))(v19);
  goto LABEL_69;
}


// ------------------------------------------------------------
// 0x430A90 sub_430A90
// ------------------------------------------------------------
void /*noreturn*/ sub_430A90()
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
// 0x430B00 sub_430B00
// ------------------------------------------------------------
void /*noreturn*/ sub_430B00()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("deque<T> too long", 0x11u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x430B70 sub_430B70
// ------------------------------------------------------------
void /*thiscall*/ sub_430B70(void *this)
{
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = -1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 1065353216;
  *((uint32_t *)this + 6) = 1065353216;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = -1;
  *((uint8_t *)this + 36) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  if ( *((uint32_t *)this + 15) != 0 )
    j__free(*((void **)this + 15));
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  if ( *((uint32_t *)this + 19) != 0 )
    j__free(*((void **)this + 19));
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 13) = 0;
}



// ------------------------------------------------------------
// 0x430BE0 sub_430BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_430BE0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xAAAAAAA )
    sub_430A90(this);
  v4 = (char *)operator new(24 * a2);
  *(this + 3) = &v4[24 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x430C30 sub_430C30
// ------------------------------------------------------------
char /*thiscall*/ sub_430C30(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x2E8BA2E )
    sub_430A90(this);
  v4 = (char *)operator new(88 * a2);
  *(this + 3) = &v4[88 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x430C80 sub_430C80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_430C80(int this, int Src, unsigned int a3, int *a4)
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
      sub_42A9A0(this);
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
// 0x430E60 sub_430E60
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_430E60(int this, unsigned int a2)
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
    sub_430B00(this);
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
// 0x430FB0 sub_430FB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_430FB0(uint32_t *this, uint32_t *a2, void *Src, int *a4)
{
  int v5; // ecx
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) >> 2 != 0 )
    v6 = ((int)Src - v5) >> 2;
  else
    v6 = 0;
  sub_430C80((int)this, (int)Src, 1u, a4);
  *a2 = *(this + 1) + 4 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x431000 sub_431000
// ------------------------------------------------------------
int /*thiscall*/ sub_431000(int this, uint32_t *a2)
{
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // ebx
  uint32_t *v7; // edi
  int result; // eax

  v3 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)v3 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(v3 + 4) >> 2 )
    sub_430E60(this, 1u);
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
// 0x431080 sub_431080
// ------------------------------------------------------------
char */*thiscall*/ sub_431080(char *this, int a2)
{
  sub_42AAB0(this);
  *(uint32_t *)this = &vftbl_CNRDDonkey;
  sub_4BCCA0(this);
  sub_4BCD50(this);
  sub_4BD5E0(a2);
  return this;
}



// ------------------------------------------------------------
// 0x4310E0 CNRDDonkey__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDDonkey__vmt0(void *Block, char a2)
{
  sub_431110();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x431110 sub_431110
// ------------------------------------------------------------
int /*thiscall*/ sub_431110(void **this)
{
  *this = &vftbl_CNRDDonkey;
  sub_4BDC40();
  return sub_42A450(this);
}



// ------------------------------------------------------------
// 0x431160 sub_431160
// ------------------------------------------------------------
char /*thiscall*/ sub_431160(uint32_t *this, char Block)
{
  char *v2; // eax
  char *v4; // eax
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  LOBYTE(v2) = Block;
  if ( Block != 0 )
  {
    if ( *(this + 162) != 0 )
    {
      LOBYTE(v2) = off_77F3FC("Donkey exist already");
    }
    else
    {
      v4 = (char *)operator new(0x17Cu);
      if ( v4 != nullptr )
      {
        v2 = sub_431080(v4, (int)this);
        *(this + 162) = v2;
      }
      else
      {
        *(this + 162) = 0;
        LOBYTE(v2) = 0;
      }
    }
  }
  else
  {
    v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 162);
    if ( v5 != nullptr )
      LOBYTE(v2) = (**v5)(v5, 1);
    *(this + 162) = 0;
  }
  return (char)v2;
}



// ------------------------------------------------------------
// 0x431230 sub_431230
// ------------------------------------------------------------
int /*thiscall*/ sub_431230(int this, uint32_t *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  uint32_t *v4; // eax
  int result; // eax

  v2 = *(uint32_t *)(this + 4);
  if ( v2 != 0 )
    v3 = (*(uint32_t *)(this + 8) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= (*(uint32_t *)(this + 12) - v2) >> 2 )
    return sub_430C80(*(void **)(this + 8), 1, (int)a2);
  v4 = *(uint32_t **)(this + 8);
  *v4 = *a2;
  result = (int)(v4 + 1);
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x431280 CNRDVirtualCharacter__vmt15C
// ------------------------------------------------------------
char /*thiscall*/ CNRDVirtualCharacter__vmt15C(uint32_t *this, int a2)
{
  int v3; // edi
  uint32_t *v4; // ebx

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 392))(this, *(uint32_t *)(a2 + 28));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 396))(
    this,
    *(uint32_t *)(a2 + 32),
    *(uint8_t *)(a2 + 36));
  v3 = 0;
  v4 = (uint32_t *)(a2 + 56);
  do
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 352))(this, v3++, *v4++);
  while ( v3 < 10 );
  return sub_431160(this, *(uint8_t *)(a2 + 108));
}



// ------------------------------------------------------------
// 0x4312E0 CNRDVirtualCharacter__vmt184
// ------------------------------------------------------------
int /*thiscall*/ sub_4312E0(int *this, int a2, int a3, int a4, int a5, float a6, int a7)
{
  int v7; // edi
  int v8; // eax
  bool v9; // zf
  uint32_t *v10; // eax
  int v11; // eax
  uint32_t **v12; // eax
  uint32_t *v13; // esi
  int v14; // eax
  unsigned int v15; // eax
  int v16; // ebx
  unsigned int v17; // ebx
  unsigned int v18; // ecx
  uint32_t **v19; // eax
  unsigned int v20; // eax
  int v21; // ebx
  char v23[4]; // [esp+Ch] [ebp-30h] BYREF
  int v24; // [esp+10h] [ebp-2Ch]
  unsigned int v25; // [esp+14h] [ebp-28h]
  unsigned int v26; // [esp+18h] [ebp-24h]
  int v27; // [esp+1Ch] [ebp-20h]
  int v28; // [esp+20h] [ebp-1Ch]
  int *v29; // [esp+24h] [ebp-18h]
  float v30; // [esp+28h] [ebp-14h]
  float v31; // [esp+2Ch] [ebp-10h]
  int v32; // [esp+38h] [ebp-4h]
  uint32_t *v33; // [esp+58h] [ebp+1Ch]

  v7 = *(this + 76);
  v28 = dword_77F6DC;
  dword_77F6DC = 1065353216;
  v8 = *(uint32_t *)(v7 + 148);
  v29 = this;
  if ( v8 == -1 )
    sub_4938F0(v7);
  v9 = *(uint32_t *)(v7 + 148) == -1;
  v30 = *(float *)(v7 + 80);
  if ( v9 )
    sub_4938F0(v7);
  v31 = *(float *)(v7 + 84);
  if ( v30 != a6 || v31 != a6 )
    sub_4920E0((uint32_t *)v7, a6, a6);
  v10 = (uint32_t *)dword_79C0B0;
  *(uint32_t *)(dword_79C0B0 + 56) = a2 + a4;
  v10[13] = a3;
  v10[12] = a2;
  v10[15] = a5 + a3;
  v24 = 0;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v32 = 0;
  v11 = sub_4924C0(0);
  sub_431000(v11 + 32);
  *(uint32_t *)(sub_4924C0(0) + 32) = a7;
  v12 = *(uint32_t ***)(v7 + 204);
  v13 = *v12;
  if ( *v12 != v12 )
  {
    do
    {
      v14 = sub_4924C0(0);
      sub_431000(v14 + 32);
      *(uint32_t *)(sub_4924C0(0) + 32) = a7;
      v13 = (uint32_t *)*v13;
    }
    while ( v13 != *(uint32_t **)(v7 + 204) );
  }
  sub_492550(
    dword_79C0B0,
    a2 + (uint64_t)((double)v29[144] * a6) + a4 / 2,
    a3 + (uint64_t)((double)v29[145] * a6) + a5 / 2,
    0.0,
    0);
  v15 = v26 >> 2;
  if ( v25 <= v26 >> 2 )
    v15 -= v25;
  v16 = *(uint32_t *)(v24 + 4 * v15);
  *(uint32_t *)(sub_4924C0(0) + 32) = *(uint32_t *)(v16 + 4 * (v26 - 4 * (v26 >> 2)));
  v17 = v25;
  v18 = v26;
  if ( v27 != 0 )
  {
    v18 = v26 + 1;
    v26 = v18;
    if ( 4 * v25 <= v18 )
    {
      v18 = 0;
      v26 = 0;
    }
    if ( --v27 == 0 )
    {
      v18 = 0;
      v26 = 0;
    }
  }
  v19 = *(uint32_t ***)(v7 + 204);
  v33 = *v19;
  if ( *v19 != v19 )
  {
    do
    {
      v20 = v18 >> 2;
      if ( v17 <= v18 >> 2 )
        v20 -= v17;
      v21 = *(uint32_t *)(v24 + 4 * v20);
      *(uint32_t *)(sub_4924C0(0) + 32) = *(uint32_t *)(v21 + 4 * (v18 - 4 * (v18 >> 2)));
      v17 = v25;
      v18 = v26;
      if ( v27 != 0 )
      {
        v18 = v26 + 1;
        v26 = v18;
        if ( 4 * v25 <= v18 )
        {
          v18 = 0;
          v26 = 0;
        }
        if ( --v27 == 0 )
        {
          v18 = 0;
          v26 = 0;
        }
      }
      v33 = (uint32_t *)*v33;
    }
    while ( v33 != *(uint32_t **)(v7 + 204) );
  }
  sub_488670(dword_79C0B0);
  if ( v30 != a6 || v31 != a6 )
    sub_4920E0((uint32_t *)v7, v30, v31);
  dword_77F6DC = v28;
  return sub_406E40(v23);
}


// ------------------------------------------------------------
// 0x431590 CNRDVirtualCharacter__vmt190
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt190(char *this)
{
  uint32_t *v2; // ebx
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int i; // ebx

  *(this + 616) = 1;
  v2 = this + 624;
  *((uint32_t *)this + 155) = sub_699000((int)(this + 8));
  if ( *v2 == 0 )
  {
    v3 = 0;
    do
    {
      v4 = v3 + 1;
      sprintf(byte_8F8158, "Common/CommonEffect/Particle/ClassChange%02d.ptl", v3 + 1);
      v5 = operator new(0x12Cu);
      if ( v5 != nullptr )
        v6 = sub_428F30(v5, (int)byte_8F8158, (int)this);
      else
        v6 = nullptr;
      *v2 = v6;
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v6 + 112))(v6, this);
      v3 = v4;
      ++v2;
    }
    while ( v4 < 3 );
  }
  v7 = this + 624;
  for ( i = 3; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v7 + 12))(*v7, 0);
    ++v7;
  }
  return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "JOB_CONVERTER",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x431670 sub_431670
// ------------------------------------------------------------
int /*userpurge*/ sub_431670@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4@<esi>, int a5)
{
  int result; // eax
  int v6; // edx
  int v7; // esi
  uint32_t *v8; // edi
  int v9; // ebx
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int v16; // esi
  int v17; // ecx
  int v18; // eax
  int v23; // [esp+4h] [ebp-218h]
  int Block; // [esp+8h] [ebp-214h]
  char Buffer[512]; // [esp+Ch] [ebp-210h] BYREF
  int v26; // [esp+20Ch] [ebp-10h]
  int v27; // [esp+218h] [ebp-4h]
  int v28; // [esp+224h] [ebp+8h]

  v26 = dword_796E50;
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 20);
    v23 = *(uint32_t *)(*(uint32_t *)(result + 44) + 104);
    if ( v23 != 0 && a5 == 1 )
    {
      v6 = *(uint32_t *)(result + 104);
      if ( *(uint32_t *)(v6 + 32) == 0 || *(uint32_t *)(v6 + 32) == 4 )
      {
        v7 = 0;
        v8 = a1 + 160;
        do
        {
          if ( *v8 != 0 )
            (**(void (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
          v9 = v7 + 1;
          *v8 = 0;
          sprintf(Buffer, "PassiveObject/MapObject/ParticleFactory/Particle/snowflake%d.ptl", v7 + 1);
          v10 = operator new(0x12Cu);
          v27 = 0;
          if ( v10 != nullptr )
            v11 = sub_428F30(v10, (int)Buffer, (int)a1);
          else
            v11 = nullptr;
          *v8 = v11;
          v12 = *(uint32_t *)(*(uint32_t *)(v23 + 132) + 44);
          v13 = *(uint32_t *)(v12 + 364);
          v14 = v12 + 360;
          v27 = -1;
          if ( v13 != 0 )
            v15 = (*(uint32_t *)(v14 + 8) - v13) >> 5;
          else
            v15 = 0;
          v16 = 224 * v15;
          Block = 224 * v15;
          v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v11 + 36))(v11, a3, a2, a4);
          v28 = *(uint32_t *)(v17 + 12);
          if ( *(uint32_t *)v17 != -1082130432 )
            *(float *)v17 = (double)Block * *(float *)v17 / (double)v28;
          v18 = v16 * *(uint32_t *)(v17 + 4) / v28;
          *(uint32_t *)(v17 + 12) = v16;
          a4 = 380;
          a2 = 280;
          *(uint32_t *)(v17 + 4) = v18;
          a3 = v16 / 2;
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 40))(*v8);
          v7 = v9;
          ++v8;
        }
        while ( v9 < 2 );
      }
      else
      {
        return sub_42FB00(a1, 1);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x431820 sub_431820
// ------------------------------------------------------------
int /*userpurge*/ sub_431820@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4@<esi>, char a5)
{
  int result; // eax

  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 292) - 1;
    if ( *(uint32_t *)(dword_8F7A24 + 292) == 1 )
    {
      if ( a5 != 0 )
        return sub_431670(a1, a2, a3, a4, 1);
      else
        return sub_42FB00(a1, 1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x431860 sub_431860
// ------------------------------------------------------------
int /*thiscall*/ sub_431860(int this, const char *ArgList, char a3)
{
  uint32_t *v4; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
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
  v4 = (uint32_t *)(this + 60);
  v4[15] = 0;
  v4[16] = 0;
  v4[17] = 0;
  v4[19] = 0;
  v4[20] = 0;
  v4[21] = 0;
  sub_430B70(v4);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, szPassword, ArgList, a3, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x431920 sub_431920
// ------------------------------------------------------------
int /*thiscall*/ sub_431920(int this, const char *a2, const char *ArgList, char a4)
{
  uint32_t *v5; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
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
  v5 = (uint32_t *)(this + 60);
  v5[15] = 0;
  v5[16] = 0;
  v5[17] = 0;
  v5[19] = 0;
  v5[20] = 0;
  v5[21] = 0;
  sub_430B70(v5);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, a2, ArgList, a4, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4319E0 sub_4319E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4319E0(int this, int a2, int a3, const char *a4, const char *ArgList, char a6)
{
  uint32_t *v7; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
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
  v7 = (uint32_t *)(this + 60);
  v7[15] = 0;
  v7[16] = 0;
  v7[17] = 0;
  v7[19] = 0;
  v7[20] = 0;
  v7[21] = 0;
  sub_430B70(v7);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, a4, ArgList, a6, 1, 0, a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x431AA0 sub_431AA0
// ------------------------------------------------------------
int sub_431AA0()
{
  void ***v0; // esi
  void **v1; // edi
  int result; // eax

  v0 = (void ***)&dword_8F8128;
  do
  {
    v1 = *v0;
    if ( *v0 != nullptr )
    {
      sub_42AF90(*v0);
      result = sub_657740(v1, 228);
    }
    *v0++ = nullptr;
  }
  while ( (int)v0 < (int)&unk_8F8130 );
  return result;
}



// ------------------------------------------------------------
// 0x431AE0 sub_431AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_431AE0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void **v3; // esi
  uint32_t *v4; // esi
  int i; // ebx
  uint32_t *v6; // esi
  int j; // ebx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 139);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void **)*(this + 153);
  *(this + 139) = 0;
  if ( v3 != nullptr )
  {
    sub_42AF90(v3);
    sub_657740(v3, 228);
  }
  *(this + 153) = 0;
  v4 = this + 156;
  for ( i = 3; i != 0; --i )
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = this + 160;
  for ( j = 2; j != 0; --j )
  {
    if ( *v6 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v6)(*v6, 1);
    *v6++ = 0;
  }
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 162);
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 164);
  result = 0;
  *(this + 162) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 164) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x431BB0 CNRDVirtualCharacter__vmt18C
// ------------------------------------------------------------
char /*thiscall*/ sub_431BB0(void *this, int a2, char a3)
{
  int v4; // eax
  int v5; // esi
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  uint32_t *v7; // esi
  bool v8; // zf
  int v9; // eax
  int v10; // edx
  uint32_t *v11; // ecx
  int v12; // esi
  char v13; // di
  char v14; // al
  char v15; // al
  int v16; // esi
  char v17; // di
  char v18; // al
  int v19; // esi
  uint32_t *v20; // edi
  int v21; // esi
  unsigned int v22; // edx
  uint32_t *v23; // eax
  char v25; // [esp+Ch] [ebp-14h]
  uint32_t *v26; // [esp+10h] [ebp-10h]
  uint32_t *v27; // [esp+28h] [ebp+8h]
  uint32_t *v28; // [esp+2Ch] [ebp+Ch]

  v4 = *((uint32_t *)this + 72);
  v5 = a2;
  if ( v4 != a2 || *((uint8_t *)this + 292) != a3 )
  {
    if ( v4 != -1
      && v4 != a2
      && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104) != 0
      && (uint8_t)sub_45E680(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 400))(this);
    }
    if ( *((uint8_t *)this + 292) != 0 )
    {
      v6 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 139);
      if ( v6 != nullptr )
        (**v6)(v6, 1);
      v7 = *((uint32_t **)this + 136);
      v8 = v7 == *((uint32_t **)this + 137);
      *((uint32_t *)this + 139) = 0;
      if ( !v8 )
      {
        do
        {
          sub_494500(*v7);
          sub_494500(*v7);
          sub_494500(*v7++);
        }
        while ( v7 != *((uint32_t **)this + 137) );
      }
      if ( *((uint32_t *)this + 136) != 0 )
        j__free(*((void **)this + 136));
      v5 = a2;
      *((uint32_t *)this + 136) = 0;
      *((uint32_t *)this + 137) = 0;
      *((uint32_t *)this + 138) = 0;
    }
    LOBYTE(v4) = a3;
    *((uint32_t *)this + 72) = v5;
    *((uint8_t *)this + 292) = a3;
    if ( a3 != 0 )
    {
      v9 = sub_4B50F0(
             (int)this + 560,
             (int)this + 564,
             (int)this + 568,
             (int)this + 572,
             *((void **)this + 71),
             v5,
             (int)this);
      v10 = *((uint32_t *)this + 72);
      *((uint32_t *)this + 139) = v9;
      v4 = sub_4B0080(*((uint32_t *)this + 71), v10);
      if ( v4 != 0 )
      {
        v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84D0 + 4))(dword_8F84D0, v4);
        v26 = (uint32_t *)v4;
        if ( v4 != 0 )
        {
          v11 = *(uint32_t **)(v4 + 1056);
          v27 = v11;
          if ( v11 != *(uint32_t **)(v4 + 1060) )
          {
            v28 = v11 + 2;
            do
            {
              if ( strcmp((const char *)sub_41ACF0(v28 + 8), szPassword) != 0 )
              {
                v12 = 0;
                if ( sub_42FCB0(228) != 0 )
                {
                  v13 = sub_41ACF0(v26 + 272);
                  v14 = sub_41ACF0(v28 + 8);
                  v12 = sub_4319E0(v26[273], v26[274], v13, v14, 1);
                }
                sub_4B0DF0(*((uint32_t *)this + 74), v12);
                sub_494240(*v27, v12);
              }
              if ( strcmp((const char *)sub_41ACF0(v28), szPassword) != 0 )
              {
                if ( sub_42FCB0(228) != 0 )
                {
                  v25 = sub_41ACF0(v26 + 272);
                  v15 = sub_41ACF0(v28);
                  v16 = sub_4319E0(v26[273], v26[274], v25, v15, 1);
                }
                else
                {
                  v16 = 0;
                }
                sub_4B0DF0(*((uint32_t *)this + 75), v16);
                sub_494240(*v27, v16);
              }
              if ( strcmp((const char *)sub_41ACF0(v28 - 1), szPassword) == 0 )
              {
                v20 = v27;
              }
              else
              {
                if ( sub_42FCB0(228) != 0 )
                {
                  v17 = sub_41ACF0(v26 + 272);
                  v18 = sub_41ACF0(v28 - 1);
                  v19 = sub_4319E0(v26[273], v26[274], v17, v18, 1);
                }
                else
                {
                  v19 = 0;
                }
                sub_4B0DF0(*((uint32_t *)this + 76), v19);
                v20 = v27;
                sub_494240(*v27, v19);
              }
              v21 = *((uint32_t *)this + 136);
              if ( v21 != 0 )
                v22 = (*((uint32_t *)this + 137) - v21) >> 2;
              else
                v22 = 0;
              if ( v21 != 0 && v22 < (*((uint32_t *)this + 138) - v21) >> 2 )
              {
                v23 = *((uint32_t **)this + 137);
                *v23 = *v20;
                *((uint32_t *)this + 137) = v23 + 1;
              }
              else
              {
                sub_430C80(*((void **)this + 137), 1, (int)v20);
              }
              LOBYTE(v4) = (uint8_t)v26;
              v27 = v20 + 31;
              v28 += 31;
            }
            while ( v20 + 31 != (uint32_t *)v26[265] );
          }
        }
      }
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x431FB0 CNRDVirtualCharacter__vmt194
// ------------------------------------------------------------
void /*thiscall*/ sub_431FB0(uint32_t *this, int a2)
{
  uint32_t *v2; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  int v5; // eax
  int v6; // ecx
  char v7; // al
  int v8; // eax
  uint32_t *v9; // ebx
  char v10; // al
  int v11; // eax
  char v12; // al
  int v13; // eax
  char v14; // bl
  char v15; // al
  int v16; // eax
  int v17; // [esp-8h] [ebp-50h]
  int v18; // [esp-8h] [ebp-50h]
  int v19; // [esp-8h] [ebp-50h]
  int v20; // [esp+Ch] [ebp-3Ch]
  int v21; // [esp+Ch] [ebp-3Ch]
  int v22; // [esp+Ch] [ebp-3Ch]
  char v23; // [esp+10h] [ebp-38h]
  uint32_t *v24; // [esp+10h] [ebp-38h]
  int v25; // [esp+14h] [ebp-34h]
  char v26; // [esp+14h] [ebp-34h]
  char v27; // [esp+14h] [ebp-34h]
  uint8_t v29[20]; // [esp+1Ch] [ebp-2Ch] BYREF
  int v30; // [esp+30h] [ebp-18h]
  int v31; // [esp+34h] [ebp-14h]
  int v32; // [esp+38h] [ebp-10h]
  int v33; // [esp+44h] [ebp-4h]
  int v34; // [esp+50h] [ebp+8h]
  uint32_t *v35; // [esp+50h] [ebp+8h]

  v2 = this;
  v32 = dword_796E50;
  v3 = (uint32_t *)sub_4CE8A0(a2);
  v4 = v3;
  if ( v3 != nullptr )
  {
    v5 = v3[23];
    if ( v5 <= 9 )
    {
      if ( v2[v5 + 85] != a2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v2 + 408))(v2, v4[23]);
        v2[v4[23] + 85] = a2;
        if ( v4[23] == 9 )
        {
          v31 = 15;
          v30 = 0;
          v29[4] = 0;
          v33 = 0;
          sub_4014D0((std::_String_base *)(v2 + 146), v29, 0, -1);
          v6 = v4[20];
          if ( v6 != 0 && (v4[21] - v6) >> 2 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )
          {
            v25 = sub_42FCB0(228);
            LOBYTE(v33) = 1;
            if ( v25 != 0 )
            {
              v34 = v4[20];
              v23 = sub_41ACF0(v4 + 272);
              v7 = sub_41ACF0(v34);
              v8 = sub_431920(v23, v7, 1);
            }
            else
            {
              v8 = 0;
            }
            LOBYTE(v33) = 0;
            v2[153] = v8;
            sub_699070(2);
          }
          v33 = -1;
          sub_501490(v29);
        }
        v9 = (uint32_t *)v4[264];
        v24 = v9;
        if ( v9 != (uint32_t *)v4[265] )
        {
          v35 = v9 + 2;
          do
          {
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v20 = sub_42FCB0(228);
              v33 = 2;
              if ( v20 != 0 )
              {
                v26 = sub_41ACF0(v4 + 272);
                v10 = sub_41ACF0(v35 + 8);
                v11 = sub_4319E0(v4[273], v4[274], v26, v10, 1);
              }
              else
              {
                v11 = 0;
              }
              v17 = *v9;
              v33 = -1;
              sub_494240(v17, v11);
              v2 = this;
            }
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v21 = sub_42FCB0(228);
              v33 = 3;
              if ( v21 != 0 )
              {
                v27 = sub_41ACF0(v4 + 272);
                v12 = sub_41ACF0(v35);
                v13 = sub_4319E0(v4[273], v4[274], v27, v12, 1);
              }
              else
              {
                v13 = 0;
              }
              v18 = *v9;
              v33 = -1;
              sub_494240(v18, v13);
              v2 = this;
            }
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v22 = sub_42FCB0(228);
              v33 = 4;
              if ( v22 != 0 )
              {
                v14 = sub_41ACF0(v4 + 272);
                v15 = sub_41ACF0(v35 - 1);
                v16 = sub_4319E0(v4[273], v4[274], v14, v15, 1);
                v9 = v24;
              }
              else
              {
                v16 = 0;
              }
              v19 = *v9;
              v33 = -1;
              sub_494240(v19, v16);
              v2 = this;
            }
            sub_431230((int)&v2[4 * v4[23] + 95], v9);
            v9 += 31;
            v24 = v9;
            v35 += 31;
          }
          while ( v9 != (uint32_t *)v4[265] );
        }
      }
    }
    else
    {
      off_77F3FC(aCriticalErrorD, v4[23]);
    }
  }
}


// ------------------------------------------------------------
// 0x4322F0 CNRDVirtualCharacter__vmt198
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt198(void ***this, int a2)
{
  int v3; // edi
  void **v4; // edi
  void ***i; // ebx

  if ( *(this + a2 + 85) != (void **)0xFFFF )
  {
    *(this + a2 + 85) = (void **)0xFFFF;
    if ( a2 == 9 )
    {
      sub_4015C0((void *)szPassword, 0);
      v3 = (int)*(this + 153);
      if ( v3 != 0 )
      {
        sub_42AF90(*(this + 153));
        sub_657740(v3, 228);
      }
      *(this + 153) = nullptr;
    }
    v4 = *(this + 4 * a2 + 96);
    for ( i = this + 4 * a2; v4 != i[97]; ++v4 )
    {
      sub_494500(*v4);
      sub_494500(*v4);
      sub_494500(*v4);
    }
    if ( i[96] != nullptr )
      j__free(i[96]);
    i[96] = nullptr;
    i[97] = nullptr;
    i[98] = nullptr;
  }
}



// ------------------------------------------------------------
// 0x4323E0 sub_4323E0
// ------------------------------------------------------------
void /*cdecl*/ sub_4323E0(char a1, int a2, int a3, int a4, float a5, char a6, int a7)
{
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  BOOL v13; // edi
  int v14; // eax
  int v15; // [esp+4h] [ebp-10h]
  int v16; // [esp+2Ch] [ebp+18h]

  if ( LODWORD(a5) != 0xFFFF
    && a7 != 0
    && (a6 == 0
     || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4) == 0
     || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4) + 161) != 0)
    && LODWORD(a5) == 26029
    && a1 == 0 )
  {
    if ( dword_8F8128[0] == 0 )
    {
      v7 = sub_42FCB0(228);
      if ( v7 != 0 )
        v8 = sub_431860(v7, "equipment/character/common/title/etcanimation/RainbowHopeBalloonStay.ani", 1);
      else
        v8 = 0;
      dword_8F8128[0] = v8;
      v9 = sub_42FCB0(228);
      if ( v9 != 0 )
        v10 = sub_431860(v9, "equipment/character/common/title/etcanimation/RainbowHopeBalloonMove.ani", 1);
      else
        v10 = 0;
      dword_8F812C = v10;
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 152))(a4) != 0 )
      v15 = a2 - 45;
    else
      v15 = a2 + 45;
    timeGetTime();
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 192))(a4);
    v11 = (uint64_t)((double)v16 * 0.34999999);
    LOBYTE(v16) = 0;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 184))(a4);
    v13 = v12 != 4;
    if ( v12 == 0 || v12 == 4 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 152))(a4) == 0 )
      LOBYTE(v16) = 1;
    sub_4938F0(dword_8F8128[v13]);
    sub_491F80(-1, -1, -1, a7, 1);
    if ( a6 != 0 )
    {
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 128))(a4);
      sub_491EA0(dword_79C0B0, v15, a3, *(float *)&v16, v11 + v14, 0.40000001, 0.30000001, 100);
    }
    else
    {
      sub_491D00(dword_79C0B0, v15, a3 - v11, *(float *)&v16);
    }
  }
}



// ------------------------------------------------------------
// 0x432600 sub_432600
// ------------------------------------------------------------
void /*cdecl*/ sub_432600(char a1, int a2, int a3, int a4, int a5, char a6, int a7)
{
  int v7; // eax

  if ( a5 != 0 )
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a5 + 16))(a5) + 4);
  else
    v7 = 0xFFFF;
  sub_4323E0(a1, a2, a3, a4, *(float *)&v7, a6, a7);
}



// ------------------------------------------------------------
// 0x432640 CNRDVirtualCharacter__vmt188
// ------------------------------------------------------------
int /*thiscall*/ sub_432640(int this, int ArgList)
{
  int result; // eax
  uint32_t *v4; // edi
  int v5; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // eax
  int i; // [esp+4h] [ebp-10h]

  result = ArgList;
  if ( ArgList != *(uint32_t *)(this + 284) )
  {
    sub_42B040(this + 296);
    v4 = (uint32_t *)(this + 340);
    v5 = this + 384;
    for ( i = 10; i != 0; --i )
    {
      *v4 = 0xFFFF;
      if ( *(uint32_t *)v5 != 0 )
        j__free(*(void **)v5);
      *(uint32_t *)v5 = 0;
      *(uint32_t *)(v5 + 4) = 0;
      *(uint32_t *)(v5 + 8) = 0;
      ++v4;
      v5 += 16;
    }
    if ( *(uint32_t *)(this + 544) != 0 )
      j__free(*(void **)(this + 544));
    *(uint32_t *)(this + 544) = 0;
    *(uint32_t *)(this + 548) = 0;
    *(uint32_t *)(this + 552) = 0;
    *(uint32_t *)(this + 284) = ArgList;
    *(uint32_t *)(this + 288) = -1;
    v6 = (uint32_t *)sub_4CE8A0(ArgList);
    v7 = v6;
    if ( v6 != nullptr )
    {
      if ( sub_40BF00((std::_String_base *)(v6 + 269), 0, v6[274], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[275] < 0x10u )
            LOBYTE(v8) = (uint8_t)v7 + 56;
          else
            v8 = v7[270];
          if ( v7[416] < 0x10u )
            v9 = sub_431920((uint8_t)v7 + 108, v8, 1);
          else
            v9 = sub_431920(v7[411], v8, 1);
        }
        else
        {
          v9 = 0;
        }
        *(uint32_t *)(this + 296) = v9;
      }
      if ( sub_40BF00((std::_String_base *)(v7 + 213), 0, v7[218], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[219] < 0x10u )
            LOBYTE(v10) = (uint8_t)v7 + 88;
          else
            v10 = v7[214];
          if ( v7[416] < 0x10u )
            v11 = sub_431920((uint8_t)v7 + 108, v10, 1);
          else
            v11 = sub_431920(v7[411], v10, 1);
        }
        else
        {
          v11 = 0;
        }
        *(uint32_t *)(this + 300) = v11;
        sub_493D00(v11, 120.0);
      }
      if ( sub_40BF00((std::_String_base *)(v7 + 206), 0, v7[211], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[212] < 0x10u )
            LOBYTE(v12) = (uint8_t)v7 + 60;
          else
            v12 = v7[207];
          if ( v7[416] < 0x10u )
            v13 = sub_431920((uint8_t)v7 + 108, v12, 1);
          else
            v13 = sub_431920(v7[411], v12, 1);
        }
        else
        {
          v13 = 0;
        }
        *(uint32_t *)(this + 304) = v13;
      }
      v14 = sub_4924C0(0);
      *(uint32_t *)(this + 160) = sub_4918E0(v14, 2);
      result = ArgList;
      if ( ArgList != 0 )
      {
        switch ( ArgList )
        {
          case 1:
            *(uint32_t *)(this + 576) = 2;
            *(uint32_t *)(this + 580) = 91;
            break;
          case 2:
            *(uint32_t *)(this + 576) = -3;
            *(uint32_t *)(this + 580) = 120;
            break;
          case 3:
            *(uint32_t *)(this + 576) = 0;
            *(uint32_t *)(this + 580) = 76;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(this + 576) = -10;
        *(uint32_t *)(this + 580) = 92;
      }
    }
    else
    {
      return off_77F3FC("VIRTUAL CHARACTER ANIMATION SETTING FAIL! JOB : %d", ArgList);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4329C0 CNRDVirtualCharacter__vmt144
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt144(void *this, int a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // [esp-4h] [ebp-10h]

  if ( (uint8_t)a2 != 0 )
  {
    nullsub_2(a2, a3, a4, a5);
    if ( *((uint32_t *)this + 71) == 2 && *((uint32_t *)this + 72) == 3 )
      sub_4C4EF0(this, a3, a4, 0, 255);
    v6 = *((uint32_t *)dword_8F8528 + 12);
    if ( *(void **)(v6 + 8) == this )
    {
      if ( *(uint32_t *)(v6 + 12) != 0 )
      {
        v8 = sub_418DD0(73);
        if ( v8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(
            v8,
            a3 + 10,
            a4 - *((uint32_t *)this + 40) - 10,
            dword_79C0B0);
      }
      else
      {
        v7 = sub_418DD0(74);
        if ( v7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(
            v7,
            a3 - 33,
            a4 - *((uint32_t *)this + 40) - 10,
            dword_79C0B0);
      }
    }
    v9 = *((uint32_t *)this + 162);
    if ( v9 == 0 || *(uint8_t *)(v9 + 284) == 0 )
    {
      v12 = *((uint32_t *)this + 153);
      v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
      v11 = sub_429830((uint32_t *)dword_8F8500, v10);
      sub_42FDA0(a3, (int)this, a3, a4, (int)this, v11, v12);
    }
    sub_4323E0(1, a3, a4, (int)this, *((float *)this + 94), 0, 255);
  }
  else
  {
    sub_4323E0(0, a3, a4, (int)this, *((float *)this + 94), 0, 255);
    nullsub_2(0, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x432B20 CNRDVirtualCharacter__vmt148
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt148(float *this, char a2, int a3, int a4, int a5)
{
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+1Ch] [ebp+Ch]
  int v13; // [esp+20h] [ebp+10h]

  if ( a2 == 0 )
  {
    sub_4323E0(0, a3, a4, (int)this, *(this + 94), 1, 255);
    v8 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 52))(this);
    v9 = sub_429830((uint32_t *)dword_8F8500, v8);
    v11 = v9;
    if ( v9 != 0 && *(uint8_t *)(v9 + 188) != 0 && ((float *)dword_8F7C08 != this || *(uint32_t *)(v9 + 184) != 0) )
    {
      v12 = 0;
      v13 = dword_8F850C;
      if ( sub_456480(dword_8F850C) == -1 )
        v10 = 0;
      else
        v10 = *(uint32_t *)(v13 + 4 * sub_456480(v13) + 16);
      if ( v10 == v11 )
        v12 = 1;
      sub_491530(2, 0);
      sub_424760(dword_79C0B0, a3 - 63, a4 - 21, *(&dword_8F811C + v12), 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
      sub_491630(2);
    }
  }
  CNRDObject__vmt148(this, a2, a3, a4, a5);
  if ( a2 != 0 )
  {
    if ( *((uint32_t *)this + 71) == 2 && *((uint32_t *)this + 72) == 3 )
      sub_4C4EF0(this, a3, a4, 1, 255);
    sub_4323E0(1, a3, a4, (int)this, *(this + 94), 1, 255);
  }
}



// ------------------------------------------------------------
// 0x432C70 CNWarRoomManager__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNWarRoomManager__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_CNWarRoomManager;
  sub_49F9F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432CA0 CNCommandChecker__vmt14
// ------------------------------------------------------------
int /*thiscall*/ CNCommandChecker__vmt14(void *this, int a2, int a3, int a4)
{
  uint32_t v5[2]; // [esp+0h] [ebp-8h] BYREF

  v5[1] = a4;
  v5[0] = a3;
  return (*(int (/*thiscall*/ **)(void *, int, uint32_t *))(*(uint32_t *)this + 16))(this, a2, v5);
}



// ------------------------------------------------------------
// 0x432CD0 sub_432CD0
// ------------------------------------------------------------
void /*thiscall*/ sub_432CD0(uint32_t *this)
{
  sub_41A630((unsigned int)this);
  *this = &vftbl_cfloat;
}



// ------------------------------------------------------------
// 0x432CF0 sub_432CF0
// ------------------------------------------------------------
double /*stdcall*/ sub_432CF0(float a1)
{
  sub_41A590(LODWORD(a1));
  return a1;
}



// ------------------------------------------------------------
// 0x432D10 sub_432D10
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ sub_432D10(void *this)
{
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x432D20 sub_432D20
// ------------------------------------------------------------
void /*thiscall*/ sub_432D20(void **this)
{
  *this = nullptr;
  sub_41BFE0(this, szPassword);
}



// ------------------------------------------------------------
// 0x432D40 sub_432D40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_432D40(uint32_t *this)
{
  *this = 1065353216;
  *(this + 1) = 1065353216;
  *(this + 2) = 1065353216;
  *(this + 3) = 1065353216;
  *(this + 4) = 1065353216;
  *(this + 5) = 1065353216;
  *(this + 6) = 1065353216;
  *(this + 7) = 1065353216;
  *(this + 8) = 1065353216;
  *(this + 9) = 1065353216;
  *(this + 10) = 1065353216;
  return this;
}



// ------------------------------------------------------------
// 0x432D70 CNRDConfigFile__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDConfigFile__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_CNRDConfigFile;
  sub_48B720();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432DC0 sub_432DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_432DC0(char *this)
{
  sub_41A580(this + 18);
  return sub_41A580(this + 4);
}



// ------------------------------------------------------------
// 0x432E10 CNRDAStar__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDAStar__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_CNRDAStar;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432E40 CNWebTextFilter__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNWebTextFilter__vmt4(uint8_t *this)
{
  *(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x432E50 sub_432E50
// ------------------------------------------------------------
int /*cdecl*/ sub_432E50(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 0:
      result = 1;
      break;
    case 1:
      result = 0;
      break;
    case 2:
      result = 3;
      break;
    case 3:
      result = 2;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x432EA0 sub_432EA0
// ------------------------------------------------------------
void */*cdecl*/ sub_432EA0(void *Src, int a2, int a3, int a4)
{
  void *result; // eax

  result = Src;
  if ( strcmp((const char *)Src, szPassword) != 0 )
    return (void *)sub_65FE10(Src, 0, a3, a4, 0, 0xFFFF, a2);
  return result;
}



// ------------------------------------------------------------
// 0x432EE0 sub_432EE0
// ------------------------------------------------------------
int /*cdecl*/ sub_432EE0(int a1)
{
  return sub_65DE30(0xFFFF, a1);
}



// ------------------------------------------------------------
// 0x432F00 sub_432F00
// ------------------------------------------------------------
void */*cdecl*/ sub_432F00(int a1)
{
  switch ( a1 )
  {
    case 0:
      return dword_8F852C;
    case 1:
      return dword_8F8534;
    case 2:
      return dword_8F8530;
    case 4:
      return *(void **)(dword_8F8538 + 16);
    default:
      break;
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x432F40 sub_432F40
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_432F40(float a1)
{
  double v2; // st7
  char v3; // c0

  v2 = a1;
  if ( v3 != 0 )
    return (uint64_t)(v2 - 0.5);
  else
    return (uint64_t)(v2 + 0.5);
}



// ------------------------------------------------------------
// 0x432F70 sub_432F70
// ------------------------------------------------------------
bool sub_432F70()
{
  dword_8F84B4 = operator new(1u);
  return dword_8F84B4 != nullptr;
}



// ------------------------------------------------------------
// 0x432FA0 sub_432FA0
// ------------------------------------------------------------
void sub_432FA0()
{
  int v0; // esi
  DWORD Time; // eax

  v0 = sub_4D33A0(&unk_77F9D8);
  Time = timeGetTime();
  srand(1000 * Time + v0);
}



// ------------------------------------------------------------
// 0x432FD0 sub_432FD0
// ------------------------------------------------------------
double /*cdecl*/ sub_432FD0(int a1, int a2)
{
  double result; // st7

  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    sub_4527C0(a1, a2);
  }
  else if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
  {
    return sub_42C400(a1, a2);
  }
  else
  {
    return 1.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x433000 sub_433000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433000(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 137) == 0 )
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
// 0x433060 sub_433060
// ------------------------------------------------------------
int /*cdecl*/ sub_433060(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 137) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x433090 sub_433090
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_433090(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 137) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 137) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4330C0 sub_4330C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4330C0(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 137) == 0 )
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
// 0x433130 sub_433130
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433130(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 21) == 0 )
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
// 0x433190 sub_433190
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_433190(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 25) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 25) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4331B0 sub_4331B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4331B0(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 33) == 0 )
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
// 0x433210 sub_433210
// ------------------------------------------------------------
int /*cdecl*/ sub_433210(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 33) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x433230 sub_433230
// ------------------------------------------------------------
int /*thiscall*/ sub_433230(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 33) == 0 )
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
// 0x433290 sub_433290
// ------------------------------------------------------------
int /*thiscall*/ sub_433290(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 45) == 0 )
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
// 0x4332F0 sub_4332F0
// ------------------------------------------------------------
int */*thiscall*/ sub_4332F0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 137) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 137) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 137) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 137) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 137) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x433360 sub_433360
// ------------------------------------------------------------
int /*thiscall*/ sub_433360(int this)
{
  *(uint8_t *)(this + 372) = 0;
  *(uint32_t *)(this + 368) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 376) = 0;
  *(uint8_t *)(this + 380) = 1;
  *(uint8_t *)(this + 382) = 0;
  *(uint8_t *)(this + 381) = 0;
  *(uint32_t *)(this + 392) = 0;
  *(uint32_t *)(this + 388) = 0;
  *(uint32_t *)(this + 384) = 0;
  *(uint8_t *)(this + 412) = 0;
  *(uint32_t *)(this + 408) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 416) = 0;
  *(uint8_t *)(this + 420) = 1;
  *(uint8_t *)(this + 422) = 0;
  *(uint8_t *)(this + 421) = 0;
  *(uint32_t *)(this + 432) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 424) = 0;
  sub_45D410(this);
  sub_45D4C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x433420 sub_433420
// ------------------------------------------------------------
char /*thiscall*/ sub_433420(int this)
{
  nullsub_3();
  *(uint32_t *)(this + 408) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 412) = 0;
  *(uint32_t *)(this + 368) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 372) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x433480 sub_433480
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_433480(uint8_t *this)
{
  *(uint32_t *)this = &vftbl_CNRDItemTradeModule;
  *(this + 28) = 0;
  *((uint32_t *)this + 6) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 8) = 0;
  *(this + 36) = 1;
  *(this + 38) = 0;
  *(this + 37) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 10) = 0;
  *(this + 56) = 0;
  *((uint32_t *)this + 13) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 15) = 0;
  *(this + 64) = 1;
  *(this + 66) = 0;
  *(this + 65) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 17) = 0;
  sub_484490(this);
  sub_4847F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x433510 CNRDItemTradeModule__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemTradeModule__vmt0(void *Block, char a2)
{
  sub_433540();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433540 sub_433540
// ------------------------------------------------------------
char /*thiscall*/ sub_433540(uint32_t *this)
{
  *this = &vftbl_CNRDItemTradeModule;
  sub_4847B0();
  *(this + 13) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 56) = 0;
  *(this + 6) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 28) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4335A0 cfloat__vmt0
// ------------------------------------------------------------
void */*thiscall*/ cfloat__vmt0(void *Block, char a2)
{
  sub_432D10(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4335D0 Camera__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ Camera__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_Camera;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433600 sub_433600
// ------------------------------------------------------------
void /*thiscall*/ sub_433600(uint32_t *this)
{
  *this = &vftbl_ITextFilter;
}



// ------------------------------------------------------------
// 0x433610 ITextFilter__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ ITextFilter__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_ITextFilter;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433640 IRDCollisionObject__vmt28C
// ------------------------------------------------------------
int /*stdcall*/ IRDCollisionObject__vmt28C(int a1)
{
  return 0;
}



// ------------------------------------------------------------
// 0x433650 CNWebTextFilter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNWebTextFilter__vmt0(void *Block, char a2)
{
  sub_433680();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433680 sub_433680
// ------------------------------------------------------------
void /*thiscall*/ sub_433680(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_ITextFilter;
}



// ------------------------------------------------------------
// 0x433690 sub_433690
// ------------------------------------------------------------
char sub_433690()
{
  int v0; // eax
  int v1; // eax
  int v2; // ebx
  char result; // al

  LeaveCriticalSection(&stru_8F8258);
  EnterCriticalSection(&stru_8F8258);
  if ( (dword_8F8764 & 1) == 0 )
  {
    dword_8F8764 |= 1u;
    dword_8F8760 = timeGetTime();
  }
  v0 = timeGetTime() - dword_8F8760;
  if ( byte_8F8554 != 0 )
  {
    sub_65FAF0(lpCriticalSection, v0);
    dword_8F8760 = timeGetTime();
  }
  v1 = sub_656710();
  sub_656AA0(v1);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 116))(dword_8F8520);
  sub_45E1A0(dword_8F8524);
  CNCommandChecker__vmt4(&dword_8F8558);
  sub_451D50(dword_8F8528);
  if ( *(uint32_t *)(dword_79C0A0 + 32) != 0 && sub_415660(44, byte_8F875C) != 0 )
  {
    v2 = sub_6997C0(dword_9D3BE0);
    if ( strcmp("SHUTTER_ON", szPassword) != 0 )
      sub_65FE10(lpCriticalSection, "SHUTTER_ON", 0, 0, 0, 0, 0xFFFF, -1);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), v2, -5000269, 0, -1);
  }
  result = byte_77F280;
  if ( byte_77F280 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 84);
      if ( result != 0 )
        sub_41C1E0(dword_8F7A24);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4337E0 sub_4337E0
// ------------------------------------------------------------
int /*cdecl*/ sub_4337E0(int a1, int a2, uint32_t *a3, int a4)
{
  int v4; // edi
  char *v5; // eax
  uint32_t *v6; // eax
  char *v7; // eax
  int result; // eax
  int v9; // ecx
  int v10; // edi
  char *v11; // eax
  uint32_t *v12; // eax
  char *v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // [esp-10h] [ebp-9Ch]
  uint32_t *v19; // [esp-8h] [ebp-94h]
  char Buffer[128]; // [esp+8h] [ebp-84h] BYREF
  int v21; // [esp+88h] [ebp-4h]

  v21 = dword_796E50;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 16))(a1) + 4) != 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 108))(a1);
    if ( a3 == (uint32_t *)sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    {
      v11 = sub_422E70(1179);
      sprintf(Buffer, v11, v10, a2);
    }
    else
    {
      if ( a3[10] < 0x10u )
        v12 = a3 + 5;
      else
        v12 = (uint32_t *)a3[5];
      v18 = v12;
      v13 = sub_422E70(1180);
      sprintf(Buffer, v13, v18, v10, a2);
    }
    v14 = __RTDynamicCast(a1, 0, &IRDItem `RTTI Type Descriptor', &CNRDStackable `RTTI Type Descriptor', 0);
    if ( v14 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 132))(v14) == 6 )
      v15 = -16715009;
    else
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 24))(a1);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, v15, 0, -1);
    result = a4;
    if ( a4 != -1 )
    {
      v16 = a3[49];
      if ( v16 != 0 )
        result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v16 + 1268))(v16, a1, a4);
    }
    if ( v14 != 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14) + 4) == 1086
       || *(uint32_t *)((result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14)) + 4) == 7039) )
    {
      v17 = sub_44E8D0((char *)dword_8F8528, (void *)0x44, 0, 0);
      result = __RTDynamicCast(
                 v17,
                 0,
                 &IRDPopupWindow `RTTI Type Descriptor',
                 &CNRDSeriasPresentListWindow `RTTI Type Descriptor',
                 0);
      if ( result != 0 )
        return sub_4D4530(v14);
    }
  }
  else
  {
    if ( a3 == (uint32_t *)sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    {
      v4 = a2;
      v5 = sub_422E70(1177);
      sprintf(Buffer, v5, a2);
    }
    else
    {
      if ( a3[10] < 0x10u )
        v6 = a3 + 5;
      else
        v6 = (uint32_t *)a3[5];
      v4 = a2;
      v19 = v6;
      v7 = sub_422E70(1178);
      sprintf(Buffer, v7, v19, a2);
    }
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
    result = a4;
    if ( a4 != -1 )
    {
      v9 = a3[49];
      if ( v9 != 0 )
        return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v9 + 1260))(
                 v9,
                 1,
                 v4,
                 0,
                 a4,
                 0,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x433A30 sub_433A30
// ------------------------------------------------------------
int /*cdecl*/ sub_433A30(void *Src, int a2, void *a3)
{
  return (int)memcpy_0(a3, Src, 4 * ((a2 - (int)Src) >> 2)) + 4 * ((a2 - (int)Src) >> 2);
}



// ------------------------------------------------------------
// 0x433A60 sub_433A60
// ------------------------------------------------------------
uint32_t *sub_433A60()
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x433A80 sub_433A80
// ------------------------------------------------------------
uint32_t *sub_433A80()
{
  uint32_t *result; // eax

  result = operator new(0x8Cu);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 136) = 1;
  *((uint8_t *)result + 137) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433AC0 sub_433AC0
// ------------------------------------------------------------
uint32_t *sub_433AC0()
{
  uint32_t *result; // eax

  result = operator new(0x18u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 20) = 1;
  *((uint8_t *)result + 21) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B00 sub_433B00
// ------------------------------------------------------------
uint32_t *sub_433B00()
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 24) = 1;
  *((uint8_t *)result + 25) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B40 sub_433B40
// ------------------------------------------------------------
uint32_t *sub_433B40()
{
  uint32_t *result; // eax

  result = operator new(0x24u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 32) = 1;
  *((uint8_t *)result + 33) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B80 sub_433B80
// ------------------------------------------------------------
uint32_t *sub_433B80()
{
  uint32_t *result; // eax

  result = operator new(0x30u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 44) = 1;
  *((uint8_t *)result + 45) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433BC0 sub_433BC0
// ------------------------------------------------------------
char /*stdcall*/ sub_433BC0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_433BC0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x433C00 sub_433C00
// ------------------------------------------------------------
char /*stdcall*/ sub_433C00(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 25);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_433C00(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 25);
  }
  return result;
}



// ------------------------------------------------------------
// 0x433C40 sub_433C40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433C40(uint32_t *this)
{
  *this = &vftbl_CNRDTutorialTip;
  `eh vector constructor iterator'(this + 2, 0x1Cu, 256, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 1794, 0x1Cu, 256, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 3586, 0x1Cu, 64, sub_40C120, sub_501490);
  sub_488870(this);
  sub_488940(this);
  return this;
}



// ------------------------------------------------------------
// 0x433CF0 sub_433CF0
// ------------------------------------------------------------
int /*stdcall*/ sub_433CF0(int a1, int a2, int a3)
{
  return sub_508EA0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x433D10 sub_433D10
// ------------------------------------------------------------
int /*thiscall*/ sub_433D10(int this)
{
  if ( *(uint32_t *)(this + 76) >= 0x10u )
    j__free(*(void **)(this + 56));
  *(uint32_t *)(this + 76) = 15;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 56) = 0;
  sub_41A580(this + 38);
  sub_41A580(this + 24);
  return sub_41A580(this + 5);
}



// ------------------------------------------------------------
// 0x433DA0 sub_433DA0
// ------------------------------------------------------------
void /*thiscall*/ sub_433DA0(int this)
{
  `eh vector destructor iterator'((void *)(this + 16), 0x10u, 8, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x433FB0 sub_433FB0
// ------------------------------------------------------------
void /*thiscall*/ sub_433FB0(void **this)
{
  *this = &vftbl_CNPvpRoom;
  nullsub_3();
  if ( (unsigned int)*(this + 26) >= 0x10 )
    j__free(*(this + 21));
  *(this + 26) = (void *)15;
  *(this + 25) = nullptr;
  *((uint8_t *)this + 84) = 0;
}



// ------------------------------------------------------------
// 0x434020 CNPvpRoom__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ CNPvpRoom__vmt0(void **Block, char a2)
{
  sub_433FB0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x434050 sub_434050
// ------------------------------------------------------------
void /*thiscall*/ sub_434050(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDInterfaceManager;
  sub_451750();
  *((uint32_t *)this + 614) = &vftbl_nengine__IObject;
  *(this + 2460) = 0;
  if ( *((uint32_t *)this + 602) != 0 )
    j__free(*((void **)this + 602));
  *((uint32_t *)this + 602) = 0;
  *((uint32_t *)this + 603) = 0;
  *((uint32_t *)this + 604) = 0;
  `eh vector destructor iterator'(this + 1268, 0x10u, 71, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector destructor iterator'(this + 132, 0x10u, 71, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x434100 sub_434100
// ------------------------------------------------------------
int /*stdcall*/ sub_434100(char *a1, char *a2)
{
  char *i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 32 )
    result = sub_432DC0(i);
  return result;
}



// ------------------------------------------------------------
// 0x434130 sub_434130
// ------------------------------------------------------------
void /*thiscall*/ sub_434130(void **this)
{
  sub_433FB0(this + 1);
}



// ------------------------------------------------------------
// 0x434140 sub_434140
// ------------------------------------------------------------
int /*thiscall*/ sub_434140(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 32 )
      sub_432DC0(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x434180 sub_434180
// ------------------------------------------------------------
int /*stdcall*/ sub_434180(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 20 )
    result = sub_433350(i);
  return result;
}



// ------------------------------------------------------------
// 0x4341B0 sub_4341B0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4341B0(uint32_t *this, int ***a2, int **a3)
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
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v26; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  v26 = this;
  if ( *((uint8_t *)a3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C5E0((int *)&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    v7 = v26;
    v8 = v26[1];
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
        v7 = v26;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v24 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v24 + 8) = sub_542490(v4);
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
  v12 = v26[1];
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
    v15 = v26;
    if ( v4 != *(int **)(v26[1] + 4) )
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
            v15 = v26;
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
            v15 = v26;
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
  v17 = v26[2];
  if ( v17 != 0 )
    v26[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x434470 sub_434470
// ------------------------------------------------------------
int ***/*thiscall*/ sub_434470(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 25) != 0 )
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
  sub_4B0C60(&a3);
  if ( *((uint8_t *)*v3 + 25) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 25) == 0 )
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
      if ( *((uint8_t *)v4 + 25) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_433190(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 25) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_4B0BE0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 25) != 0 )
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
    if ( *((uint8_t *)v4 + 25) == 0 )
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
  v14 = *((uint8_t *)v5 + 24);
  *((uint8_t *)v5 + 24) = *((uint8_t *)v3 + 24);
  *((uint8_t *)v3 + 24) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 24) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 24) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0FD0(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 24) != 1 || *(uint8_t *)(v16[2] + 24) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 24) == 1 )
            {
              *(uint8_t *)(*v16 + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0C00(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(v16[2] + 24) = 1;
            sub_4B0FD0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0C00(v6);
            v16 = (uint32_t *)*v6;
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 24) != 1 || *(uint8_t *)(*v16 + 24) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 24) == 1 )
            {
              *(uint8_t *)(v16[2] + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0FD0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(*v16 + 24) = 1;
            sub_4B0C00(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 24) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 24) = 1;
  }
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x434730 sub_434730
// ------------------------------------------------------------
void /*noreturn*/ sub_434730()
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
// 0x4347A0 sub_4347A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4347A0(void **this)
{
  sub_433FB0(this + 4);
}



// ------------------------------------------------------------
// 0x4347B0 sub_4347B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4347B0(void **this)
{
  sub_4017E0(this + 27);
  sub_4017E0(this + 23);
  sub_41B010(this + 22);
  sub_41B010(this + 21);
  sub_41B010(this + 20);
  sub_41B010(this + 19);
  `eh vector destructor iterator'(this + 15, 4u, 4, sub_401060);
  `eh vector destructor iterator'(this + 11, 4u, 4, sub_401060);
  sub_41B010(this + 10);
  sub_41B010(this + 9);
  sub_41B010(this + 8);
  sub_41B010(this + 7);
  sub_41B010(this + 6);
  `eh vector destructor iterator'(this + 4, 4u, 2, sub_401060);
  sub_41B010(this + 3);
  sub_41B010(this + 2);
  sub_41B010(this + 1);
}



// ------------------------------------------------------------
// 0x434950 sub_434950
// ------------------------------------------------------------
char /*thiscall*/ sub_434950(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xAAAAAAA )
    sub_434730(this);
  v4 = (char *)operator new(24 * a2);
  *(this + 3) = &v4[24 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x4349A0 sub_4349A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4349A0(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 20 )
      sub_433350(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4349E0 sub_4349E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4349E0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_434730(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x434A40 sub_434A40
// ------------------------------------------------------------
char /*thiscall*/ sub_434A40(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x7FFFFFF )
    sub_434730(this);
  v4 = (char *)operator new(32 * a2);
  *(this + 3) = &v4[32 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x434A90 sub_434A90
// ------------------------------------------------------------
char /*thiscall*/ sub_434A90(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3333333 )
    sub_434730(this);
  v4 = (char *)operator new(80 * a2);
  *(this + 3) = &v4[80 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x434AE0 sub_434AE0
// ------------------------------------------------------------
char /*thiscall*/ sub_434AE0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x6666666 )
    sub_434730(this);
  v4 = (char *)operator new(40 * a2);
  *(this + 3) = &v4[40 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x434B30 sub_434B30
// ------------------------------------------------------------
int */*thiscall*/ sub_434B30(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v10; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(uint32_t *)v7 && a4 == v7 )
  {
    sub_429740(*(void ***)(v7 + 4));
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
        v10 = v5;
        if ( *(uint8_t *)(v5 + 21) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 21) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v5 != *(uint32_t *)(i + 8) )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = *(uint32_t *)(v5 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_429950(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x434BF0 sub_434BF0
// ------------------------------------------------------------
int */*thiscall*/ sub_434BF0(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v10; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(uint32_t *)v7 && a4 == v7 )
  {
    sub_433BC0(*(void ***)(v7 + 4));
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
        v10 = v5;
        if ( *(uint8_t *)(v5 + 21) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 21) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v5 != *(uint32_t *)(i + 8) )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = *(uint32_t *)(v5 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_4341B0(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x434CB0 sub_434CB0
// ------------------------------------------------------------
int **/*thiscall*/ sub_434CB0(int ***this, int **a2, int *a3, int *a4)
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
    sub_433C00(*(void ***)(v7 + 4));
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
        if ( *((uint8_t *)v5 + 25) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 25) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 25) == 0; i = (int *)i[1] )
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
            for ( j = *v11; *((uint8_t *)j + 25) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_434470(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x434D70 sub_434D70
// ------------------------------------------------------------
void /*thiscall*/ sub_434D70(int *this, int a2, unsigned int a3, void *Block)
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
  int v17; // esi
  int v18; // [esp-18h] [ebp-60h]
  int v19; // [esp-Ch] [ebp-54h]
  unsigned int v20; // [esp-8h] [ebp-50h]
  int v21; // [esp+0h] [ebp-48h] BYREF
  uint32_t v22[12]; // [esp+Ch] [ebp-3Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]
  int v24; // [esp+50h] [ebp+8h]
  int v25; // [esp+54h] [ebp+Ch]
  char *Blocka; // [esp+58h] [ebp+10h]
  void *Blockb; // [esp+58h] [ebp+10h]

  qmemcpy(v22, Block, 0x2Cu);
  v5 = *(this + 1);
  v22[11] = &v21;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 44;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 44;
    else
      v8 = 0;
    if ( 97612893 - v8 < a3 )
      sub_434730(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 44;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v15 = (void *)*(this + 2);
      Blockb = v15;
      if ( ((int)v15 - a2) / 44 >= a3 )
      {
        v24 = (int)v15 - 44 * a3;
        *(this + 2) = sub_508EA0(v24, v15, v15);
        sub_4F8D90(a2, v24, Blockb);
        sub_508E70(a2, a2 + 44 * a3, v22);
      }
      else
      {
        sub_508EA0(a2, v15, a2 + 44 * a3);
        v20 = a3 - (*(this + 2) - a2) / 44;
        v19 = *(this + 2);
        v23 = 2;
        sub_508EE0(v19, v20, v22);
        v17 = 44 * a3 + *(this + 2);
        *(this + 2) = v17;
        sub_508E70(a2, v17 - 44 * a3, v22);
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
      v12 = 44 * v10;
      Blocka = (char *)operator new(44 * v10);
      v18 = *(this + 1);
      v23 = 0;
      v25 = sub_508EA0(v18, a2, Blocka);
      sub_4F8DF0(v25, a3, v22);
      sub_508EA0(a2, *(this + 2), 44 * a3 + v25);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 44;
      v14 = v13 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v12];
      *(this + 2) = (int)&Blocka[44 * v14];
      *(this + 1) = (int)Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x435020 sub_435020
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435020(uint32_t *this, uint32_t *a2)
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

  v3 = a2[1];
  v11 = &v9;
  v10 = this;
  if ( v3 != 0 )
    v4 = (a2[2] - v3) >> 2;
  else
    v4 = 0;
  if ( sub_42AA50(this, v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = a2[2];
    v6 = a2[1];
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4350C0 sub_4350C0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_4350C0(int *this)
{
  return sub_4349A0(this);
}



// ------------------------------------------------------------
// 0x4350D0 sub_4350D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4350D0(int *this, uint32_t *a2, int a3, void *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 44 != 0 )
    v6 = (a3 - v5) / 44;
  else
    v6 = 0;
  sub_434D70(this, a3, 1u, Block);
  *a2 = *(this + 1) + 44 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x435140 sub_435140
// ------------------------------------------------------------
int ***/*thiscall*/ sub_435140(uint32_t *this, int ***a2, int **a3)
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
  void **v15; // eax
  uint32_t *v16; // ecx
  int v17; // eax
  uint32_t *v18; // eax
  int v19; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v27; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  v27 = this;
  if ( *((uint8_t *)a3 + 45) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v28 = 0;
    sub_401740(v22);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_40BEA0(&a3);
  if ( *((uint8_t *)*v3 + 45) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    v7 = v27;
    v8 = v27[1];
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
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = sub_6600D0(v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_4429F0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 45) != 0 )
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
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v27[1];
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
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)v3 + 44);
  *((uint8_t *)v3 + 44) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    v16 = v27;
    if ( v4 != *(int **)(v27[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;
        v17 = *v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = v6[2];
          if ( *(uint8_t *)(v17 + 44) == 0 )
          {
            *(uint8_t *)(v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            v17 = v6[2];
            v16 = v27;
          }
          if ( *(uint8_t *)(v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v17 + 44) != 1 || *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v17 + 44) = 1;
              *(uint8_t *)(v17 + 44) = 0;
              sub_433290(v17);
              v17 = v6[2];
            }
            *(uint8_t *)(v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *(uint8_t *)(v17 + 44) == 0 )
          {
            *(uint8_t *)(v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            v17 = *v6;
            v16 = v27;
          }
          if ( *(uint8_t *)(v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) != 1 || *(uint8_t *)(*(uint32_t *)v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v17 + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) = 1;
              *(uint8_t *)(v17 + 44) = 0;
              sub_442AC0(v17);
              v17 = *v6;
            }
            *(uint8_t *)(v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)v17 + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *(uint8_t *)(v17 + 44) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v16[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  v18 = Block;
  *((uint32_t *)Block + 9) = 15;
  v18[8] = 0;
  *((uint8_t *)v18 + 16) = 0;
  j__free(v18);
  v19 = v27[2];
  if ( v19 != 0 )
    v27[2] = v19 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x435420 sub_435420
// ------------------------------------------------------------
char /*stdcall*/ sub_435420(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_435420(i[2]);
    i = (void **)*i;
    sub_5014C0(v1);
    j__free(v1);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x435470 sub_435470
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435470(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  `eh vector constructor iterator'(this + 4, 0x10u, 8, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  return this;
}



// ------------------------------------------------------------
// 0x4354D0 sub_4354D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4354D0(uint32_t *this, void *Block, int a3)
{
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  sub_484CA0();
  sub_485E80(Block, a3);
  return this;
}



// ------------------------------------------------------------
// 0x435530 sub_435530
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435530(uint32_t *this)
{
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 56) = 0;
  sub_433EF0();
  return this;
}



// ------------------------------------------------------------
// 0x4355A0 sub_4355A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4355A0(uint32_t *Block)
{
  *Block = &vftbl_CNRDInterfaceManager;
  `eh vector constructor iterator'(Block + 33, 0x10u, 71, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(Block + 317, 0x10u, 71, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(Block + 602) = 0;
  *(Block + 603) = 0;
  *(Block + 604) = 0;
  *((uint8_t *)Block + 2460) = 0;
  *(Block + 614) = &vftbl_nengine__CNTimer;
  *(Block + 616) = 0;
  *((uint8_t *)Block + 2468) = 1;
  *((uint8_t *)Block + 2470) = 0;
  *((uint8_t *)Block + 2469) = 0;
  *(Block + 620) = 0;
  *(Block + 619) = 0;
  *(Block + 618) = 0;
  *(Block + 627) = 12;
  *(Block + 628) = 0;
  *(Block + 629) = 0;
  *(Block + 630) = 0;
  sub_44AA50(Block);
  sub_450C80(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x435690 sub_435690
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_435690(uint8_t *this, int a2)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_CNSlangTextFilter;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  sub_4D3710();
  *(this + 4) = 1;
  sub_4D4040(a2);
  return this;
}



// ------------------------------------------------------------
// 0x435700 CNSlangTextFilter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNSlangTextFilter__vmt0(void *Block, char a2)
{
  sub_435730();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x435730 sub_435730
// ------------------------------------------------------------
int /*thiscall*/ sub_435730(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNSlangTextFilter;
  CNSlangTextFilter__vmt8();
  result = sub_4017E0(this + 2);
  *this = &vftbl_ITextFilter;
  return result;
}



// ------------------------------------------------------------
// 0x435790 sub_435790
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435790(int *this, void *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 44;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 44 )
    return sub_4350D0(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_4F8DF0(v5, 1, Block);
  *(this + 2) = v5 + 44;
  return result;
}



// ------------------------------------------------------------
// 0x435820 sub_435820
// ------------------------------------------------------------
void /*stdcall*/ sub_435820(void **a1, void **a2)
{
  void **i; // esi

  for ( i = a1; i != a2; i += 6 )
    sub_5E5260(i);
}



// ------------------------------------------------------------
// 0x435850 sub_435850
// ------------------------------------------------------------
int /*thiscall*/ sub_435850(int this)
{
  void **v2; // esi
  int result; // eax
  void **i; // edi

  v2 = *(void ***)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(void ***)(this + 8); v2 != i; v2 += 6 )
      sub_5E5260(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x435890 sub_435890
// ------------------------------------------------------------
int /*stdcall*/ sub_435890(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 80 )
    result = sub_433D10(i);
  return result;
}



// ------------------------------------------------------------
// 0x4358C0 sub_4358C0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4358C0(uint32_t *this, int ***a2, int **a3)
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
  int v16; // eax
  uint32_t *v17; // eax
  int v18; // eax
  void *v20; // [esp-4h] [ebp-64h]
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-5Ch] BYREF
  size_t v22; // [esp+2Ch] [ebp-34h] BYREF
  char v23; // [esp+30h] [ebp-30h]
  int v24; // [esp+40h] [ebp-20h]
  int v25; // [esp+44h] [ebp-1Ch]
  int v26; // [esp+48h] [ebp-18h]
  void *Block; // [esp+4Ch] [ebp-14h]
  uint32_t *v28; // [esp+50h] [ebp-10h]
  int v29; // [esp+5Ch] [ebp-4h]

  v28 = this;
  if ( *((uint8_t *)a3 + 33) != 0 )
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);
    v29 = 0;
    sub_401740(pExceptionObject, &v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C640((int *)&a3);
  if ( *((uint8_t *)*v3 + 33) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    v7 = v28;
    v8 = v28[1];
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
      if ( *((uint8_t *)v4 + 33) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = sub_41C5C0(v4);
        v7 = v28;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 33) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v26 + 8) = sub_433210(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 33) != 0 )
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
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v28[1];
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
  v14 = *((uint8_t *)v5 + 32);
  *((uint8_t *)v5 + 32) = *((uint8_t *)v3 + 32);
  *((uint8_t *)v3 + 32) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 32) == 1 )
  {
    v15 = v28;
    if ( v4 != *(int **)(v28[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 32) != 1 )
          break;
        v16 = *v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = v6[2];
          if ( *(uint8_t *)(v16 + 32) == 0 )
          {
            *(uint8_t *)(v16 + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_4331B0(v6);
            v16 = v6[2];
            v15 = v28;
          }
          if ( *(uint8_t *)(v16 + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v16 + 32) != 1 || *(uint8_t *)(*(uint32_t *)(v16 + 8) + 32) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)(v16 + 8) + 32) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v16 + 32) = 1;
              *(uint8_t *)(v16 + 32) = 0;
              sub_433230(v16);
              v16 = v6[2];
            }
            *(uint8_t *)(v16 + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(*(uint32_t *)(v16 + 8) + 32) = 1;
            sub_4331B0(v6);
            break;
          }
        }
        else
        {
          if ( *(uint8_t *)(v16 + 32) == 0 )
          {
            *(uint8_t *)(v16 + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_433230(v6);
            v16 = *v6;
            v15 = v28;
          }
          if ( *(uint8_t *)(v16 + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)(v16 + 8) + 32) != 1 || *(uint8_t *)(*(uint32_t *)v16 + 32) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v16 + 32) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)(v16 + 8) + 32) = 1;
              *(uint8_t *)(v16 + 32) = 0;
              sub_4331B0(v16);
              v16 = *v6;
            }
            *(uint8_t *)(v16 + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(*(uint32_t *)v16 + 32) = 1;
            sub_433230(v6);
            break;
          }
        }
        *(uint8_t *)(v16 + 32) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 32) = 1;
  }
  if ( *((uint32_t *)Block + 5) != 0 )
    j__free(*((void **)Block + 5));
  v17 = Block;
  v20 = Block;
  *((uint32_t *)Block + 5) = 0;
  v17[6] = 0;
  v17[7] = 0;
  j__free(v20);
  v18 = v28[2];
  if ( v18 != 0 )
    v28[2] = v18 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x435BA0 sub_435BA0
// ------------------------------------------------------------
char /*stdcall*/ sub_435BA0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 33);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_435BA0(i[2]);
    i = (void **)*i;
    sub_4CEB50(v1);
    j__free(v1);
    result = *((uint8_t *)i + 33);
  }
  return result;
}



// ------------------------------------------------------------
// 0x435BF0 sub_435BF0
// ------------------------------------------------------------
int /*cdecl*/ sub_435BF0(int a1, int a2, int a3)
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
    *(uint32_t *)(v4 + 16) = *(uint32_t *)(v3 + 16);
    *(uint32_t *)(v4 + 20) = *(uint32_t *)(v3 + 20);
    v3 += 24;
    v4 += 24;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x435C30 sub_435C30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435C30(uint32_t *this)
{
  char *v2; // edi

  *this = &vftbl_CNRDUdpModule;
  *(this + 1) = &CNRDUdpModule::`vftable';
  *(this + 2) = &CNRDUdpModule::`vftable';
  *((uint8_t *)this + 1048608) = 0;
  *(this + 262151) = &vftbl_nengine__CNTimer;
  *(this + 262153) = 0;
  *((uint8_t *)this + 1048616) = 1;
  *((uint8_t *)this + 1048618) = 0;
  *((uint8_t *)this + 1048617) = 0;
  *(this + 262157) = 0;
  *(this + 262156) = 0;
  *(this + 262155) = 0;
  v2 = (char *)(this + 262158);
  *(this + 262159) = sub_433A60();
  *((uint32_t *)v2 + 2) = 0;
  `eh vector constructor iterator'(this + 262170, 0x1Cu, 8, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 262237, 0x1Cu, 8, sub_401170, sub_401000);
  *((uint8_t *)this + 1049208) = 0;
  *(this + 262301) = &vftbl_nengine__CNTimer;
  *(this + 262303) = 0;
  *((uint8_t *)this + 1049216) = 1;
  *((uint8_t *)this + 1049218) = 0;
  *((uint8_t *)this + 1049217) = 0;
  *(this + 262307) = 0;
  *(this + 262306) = 0;
  *(this + 262305) = 0;
  *((uint8_t *)this + 1049960) = 0;
  *(this + 262489) = &vftbl_nengine__CNTimer;
  *(this + 262491) = 0;
  *((uint8_t *)this + 1049968) = 1;
  *((uint8_t *)this + 1049970) = 0;
  *((uint8_t *)this + 1049969) = 0;
  *(this + 262495) = 0;
  *(this + 262494) = 0;
  *(this + 262493) = 0;
  *((uint8_t *)this + 1050000) = 0;
  *(this + 262499) = &vftbl_nengine__CNTimer;
  *(this + 262501) = 0;
  *((uint8_t *)this + 1050008) = 1;
  *((uint8_t *)this + 1050010) = 0;
  *((uint8_t *)this + 1050009) = 0;
  *(this + 262505) = 0;
  *(this + 262504) = 0;
  *(this + 262503) = 0;
  sub_435470(this + 262522);
  CNRDUdpModule__vmtA8(this);
  CNRDUdpModule__vmtAC(this);
  return this;
}



// ------------------------------------------------------------
// 0x435DE0 CNRDUdpModule__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtC(uint32_t *this, int a2)
{
  *(this + 262147) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x435DF0 CNRDUdpModule__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt10(uint32_t *this)
{
  return *(this + 262147) - (uint32_t)this - 12;
}



// ------------------------------------------------------------
// 0x435E30 CNRDUdpModule__vmt20
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUdpModule__vmt20(uint32_t *this, char a2)
{
  uint8_t *result; // eax

  result = (uint8_t *)*(this + 262147);
  *result = a2;
  ++*(this + 262147);
  return result;
}



// ------------------------------------------------------------
// 0x435E50 CNRDUdpModule__vmt24
// ------------------------------------------------------------
uint16_t */*thiscall*/ CNRDUdpModule__vmt24(uint32_t *this, int16_t a2)
{
  uint16_t *result; // eax

  result = (uint16_t *)*(this + 262147);
  *result = a2;
  *(this + 262147) += 2;
  return result;
}



// ------------------------------------------------------------
// 0x435E70 CNRDUdpModule__vmt28
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt28(uint32_t *this, int a2)
{
  uint32_t *result; // eax

  result = (uint32_t *)*(this + 262147);
  *result = a2;
  *(this + 262147) += 4;
  return result;
}



// ------------------------------------------------------------
// 0x435E90 CNRDUdpModule__vmt2C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt2C(uint32_t *this, int a2, int a3)
{
  uint32_t *result; // eax

  result = (uint32_t *)*(this + 262147);
  *result = a2;
  result[1] = a3;
  *(this + 262147) += 8;
  return result;
}



// ------------------------------------------------------------
// 0x435EB0 CNRDUdpModule__vmt30
// ------------------------------------------------------------
void **/*thiscall*/ CNRDUdpModule__vmt30(void **this, const void *a2, unsigned int a3)
{
  void **result; // eax

  result = this;
  if ( a2 != nullptr )
  {
    qmemcpy(*(this + 262147), a2, a3);
    *(this + 262147) = (char *)*(this + 262147) + a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x435EF0 CNRDUdpModule__vmt34
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt34(void *this, int a2, int a3)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, a3);
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 48))(this, a2, a3);
}



// ------------------------------------------------------------
// 0x435F20 CNRDUdpModule__vmt38
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt38(void *this, const char *a2)
{
  return (*(int (/*thiscall*/ **)(void *, const char *, unsigned int))(*(uint32_t *)this + 52))(this, a2, strlen(a2));
}



// ------------------------------------------------------------
// 0x435F50 CNRDUdpModule__vmt40
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt40(uint32_t *this, int a2)
{
  *(this + 262148) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x435F60 CNRDUdpModule__vmt44
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt44(uint32_t *this)
{
  return *(this + 262148);
}



// ------------------------------------------------------------
// 0x435F70 CNRDUdpModule__vmt48
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUdpModule__vmt48(uint32_t *this, uint8_t *a2)
{
  *a2 = *(uint8_t *)(*(this + 262148))++;
  return a2;
}



// ------------------------------------------------------------
// 0x435F90 CNRDUdpModule__vmt4C
// ------------------------------------------------------------
uint16_t */*thiscall*/ CNRDUdpModule__vmt4C(uint16_t **this, uint16_t *a2)
{
  *a2 = *(*(this + 262148))++;
  return a2;
}



// ------------------------------------------------------------
// 0x435FB0 CNRDUdpModule__vmt50
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt50(uint32_t **this, uint32_t *a2)
{
  *a2 = *(*(this + 262148))++;
  return a2;
}



// ------------------------------------------------------------
// 0x435FD0 CNRDUdpModule__vmt54
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt54(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edx

  v2 = (uint32_t *)*(this + 262148);
  *a2 = *v2;
  a2[1] = v2[1];
  *(this + 262148) += 8;
  return a2;
}



// ------------------------------------------------------------
// 0x436000 CNRDUdpModule__vmt58
// ------------------------------------------------------------
const void **/*thiscall*/ CNRDUdpModule__vmt58(const void **this, void *a2, unsigned int a3)
{
  qmemcpy(a2, *(this + 262148), a3);
  *(this + 262148) = (char *)*(this + 262148) + a3;
  return this;
}



// ------------------------------------------------------------
// 0x436040 CNRDUdpModule__vmt6C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt6C(uint32_t *this, int a2)
{
  return *(this + a2 + 262293);
}



// ------------------------------------------------------------
// 0x436060 CNRDUdpModule__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt70(uint32_t *this)
{
  *(this + 262293) = 0;
  *(this + 262294) = 0;
  *(this + 262295) = 0;
  *(this + 262296) = 0;
  *(this + 262297) = 0;
  *(this + 262298) = 0;
  *(this + 262299) = 0;
  *(this + 262300) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4360A0 CNRDUdpModule__vmt78
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt78(uint32_t *this)
{
  return *(this + 262149);
}



// ------------------------------------------------------------
// 0x4360B0 CNRDUdpModule__vmt80
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt80(uint32_t *this, int a2)
{
  *(this + 262150) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4360C0 CNRDUdpModule__vmt84
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt84(uint32_t *this)
{
  return *(this + 262150);
}



// ------------------------------------------------------------
// 0x4360D0 CNRDUdpModule__vmt94
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmt94(char *this, int a2)
{
  char result; // al

  result = *(this + 1048644);
  if ( result == 0 )
  {
    sub_656710();
    sub_6567B0(a2);
    *(this + 1048644) = 1;
    *(this + 1049217) = 0;
    *(this + 1049218) = 0;
    return sub_698F90((int)(this + 1049204), 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x436120 CNRDUdpModule__vmt9C
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmt9C(uint8_t *this)
{
  return *(this + 1048644);
}



// ------------------------------------------------------------
// 0x436130 CNRDUdpModule__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDUdpModule__vmt4(void *Block, char a2)
{
  sub_436160();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x436160 sub_436160
// ------------------------------------------------------------
void /*thiscall*/ sub_436160(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDUdpModule;
  *((uint32_t *)this + 1) = &CNRDUdpModule::`vftable';
  *((uint32_t *)this + 2) = &CNRDUdpModule::`vftable';
  CNRDUdpModule__vmtB0();
  sub_433DA0((int)(this + 1050088));
  *((uint32_t *)this + 262499) = &vftbl_nengine__IObject;
  *(this + 1050000) = 0;
  *((uint32_t *)this + 262489) = &vftbl_nengine__IObject;
  *(this + 1049960) = 0;
  *((uint32_t *)this + 262301) = &vftbl_nengine__IObject;
  *(this + 1049208) = 0;
  `eh vector destructor iterator'(this + 1048948, 0x1Cu, 8, sub_401000);
  `eh vector destructor iterator'(this + 1048680, 0x1Cu, 8, sub_401000);
  sub_6569D0(this + 1048632);
  j__free(*((void **)this + 262159));
  *((uint32_t *)this + 262159) = 0;
  *(this + 1048608) = 0;
  *((uint32_t *)this + 262151) = &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x436250 sub_436250
// ------------------------------------------------------------
int /*thiscall*/ sub_436250(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_434B30((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x436290 sub_436290
// ------------------------------------------------------------
int /*thiscall*/ sub_436290(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_434BF0((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4362D0 sub_4362D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4362D0(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_434CB0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x436310 sub_436310
// ------------------------------------------------------------
char sub_436310()
{
  int v1; // esi
  int v2; // esi
  float *v3; // esi
  int j; // esi
  double v5; // st7
  char *v6; // esi
  int v7; // edi
  char *v8; // esi
  int v9; // edi
  float v10[11]; // [esp+0h] [ebp-64h] BYREF
  float i; // [esp+2Ch] [ebp-38h]
  int v12; // [esp+30h] [ebp-34h] BYREF
  char v13; // [esp+37h] [ebp-2Dh] BYREF
  char v14[4]; // [esp+38h] [ebp-2Ch] BYREF
  void *Block; // [esp+3Ch] [ebp-28h]
  int v16; // [esp+4Ch] [ebp-18h]
  unsigned int v17; // [esp+50h] [ebp-14h]
  int v18; // [esp+54h] [ebp-10h]
  int v19; // [esp+60h] [ebp-4h]

  v18 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/EtcParameter.etc") == 0 )
  {
    off_77F3FC(aCriticalError);
    return 0;
  }
  v17 = 15;
  v16 = 0;
  LOBYTE(Block) = 0;
  v19 = 1;
  v12 = 0;
  sub_41BFE0(szPassword);
  v13 = 0;
  while ( (uint8_t)sub_443430(v14) != 0 )
  {
    sub_442B20(v14);
    if ( sub_40BF00(0, v16, "[nation code]", 13) == 0 )
    {
      v1 = sub_4423D0(0);
      sub_41C570(v1);
      dword_9B0AB0 = (int)&dword_9B0C08;
      if ( v1 != 1 )
        dword_9B0AB0 = (int)&dword_9B0BC8;
    }
    if ( sub_40BF00(0, v16, "[script version]", 16) != 0 )
    {
      if ( sub_40BF00(0, v16, "[durability decrease rate]", 26) != 0 )
      {
        if ( sub_40BF00(0, v16, "[equipment weight constant]", 27) != 0 )
        {
          if ( sub_40BF00(0, v16, "[damage fomula constant]", 24) != 0 )
          {
            if ( (uint8_t)sub_423300(v14, "[summoned monster status up rate]") != 0 )
            {
              v3 = (float *)&unk_9A05E0;
              do
                *v3++ = sub_442480(0);
              while ( (int)v3 < (int)&byte_9A05F0 );
            }
            else if ( (uint8_t)sub_423300(v14, "[divine armor defense constant]") != 0 )
            {
              dword_9A05C8 = sub_4423D0(0);
            }
            else if ( (uint8_t)sub_423300(v14, "[PVP equalization]") != 0 )
            {
              sub_5E5260(&unk_98B71C);
              sub_432D40(v10);
              for ( i = sub_442480(&v13); v13 != 0; i = sub_442480(&v13) )
              {
                for ( j = 0; j < 11; ++j )
                {
                  if ( j != 0 )
                    v5 = sub_442480(0);
                  else
                    v5 = i;
                  v10[j] = v5;
                }
                sub_435790(v10);
              }
            }
            else if ( (uint8_t)sub_423300(v14, "[PVP slave hp equalization]") != 0 )
            {
              flt_7904FC = sub_442480(0);
            }
            else if ( (uint8_t)sub_423300(v14, "[tutorial message]") != 0 )
            {
              v6 = (char *)dword_98B730;
              if ( dword_98B730 != nullptr )
              {
                v7 = dword_98B734;
                if ( dword_98B730 != (void *)dword_98B734 )
                {
                  do
                  {
                    sub_41B010(v6);
                    v6 += 4;
                  }
                  while ( v6 != (char *)v7 );
                  v6 = (char *)dword_98B730;
                }
                j__free(v6);
              }
              dword_98B730 = nullptr;
              dword_98B734 = 0;
              dword_98B738 = 0;
              while ( (uint8_t)sub_442E10(&v12) != 0 )
                sub_420BB0(&v12);
            }
            else if ( (uint8_t)sub_423300(v14, "[prohibited name]") != 0 )
            {
              v8 = (char *)dword_98BA0C;
              if ( dword_98BA0C != nullptr )
              {
                v9 = dword_98BA10;
                if ( dword_98BA0C != (void *)dword_98BA10 )
                {
                  do
                  {
                    sub_41B010(v8);
                    v8 += 4;
                  }
                  while ( v8 != (char *)v9 );
                  v8 = (char *)dword_98BA0C;
                }
                j__free(v8);
              }
              dword_98BA0C = nullptr;
              dword_98BA10 = 0;
              dword_98BA14 = 0;
              while ( (uint8_t)sub_442E10(&v12) != 0 )
                sub_420BB0(&v12);
            }
          }
          else
          {
            flt_9A05F4 = sub_442480(0);
            flt_9A05F8 = sub_442480(0);
            flt_9A05FC = sub_442480(0);
            flt_9A0600 = sub_442480(0);
            flt_9A0604 = sub_442480(0);
            flt_9A0608 = sub_442480(0);
            flt_9A060C = sub_442480(0);
            flt_9A0610 = sub_442480(0);
            flt_9A0614 = sub_442480(0);
            flt_9A0618 = sub_442480(0);
            flt_9A061C = sub_442480(0);
            flt_9A0620 = sub_442480(0);
            flt_9A0624 = sub_442480(0);
            flt_9A0628 = sub_442480(0);
          }
        }
        else
        {
          flt_791E20 = sub_442480(0);
          flt_9B06D0 = sub_442480(0);
        }
      }
      else
      {
        dword_9A0308 = sub_4423D0(0);
        dword_9A030C = sub_4423D0(0);
        dword_9A0594 = sub_4423D0(0);
      }
    }
    else
    {
      v2 = sub_4423D0(0);
      off_77F3FC("script version : %d", v2);
      if ( v2 != 30060504 )
      {
        off_77F3FC("g_scriptVersion != curVersion");
        LOBYTE(v19) = 0;
        sub_41B010(&v12);
        if ( v17 >= 0x10 )
          j__free(Block);
        return 0;
      }
    }
  }
  LOBYTE(v19) = 0;
  sub_41B010(&v12);
  if ( v17 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x436840 sub_436840
// ------------------------------------------------------------
int /*thiscall*/ sub_436840(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 80 )
      sub_433D10(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x436880 sub_436880
// ------------------------------------------------------------
int */*thiscall*/ sub_436880(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v10; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(uint32_t *)v7 && a4 == v7 )
  {
    sub_435420(*(void ***)(v7 + 4));
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
        v10 = v5;
        if ( *(uint8_t *)(v5 + 45) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 45) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 45) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v5 != *(uint32_t *)(i + 8) )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = *(uint32_t *)(v5 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 45) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_435140(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x436940 sub_436940
// ------------------------------------------------------------
int ***/*thiscall*/ sub_436940(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 137) != 0 )
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
  sub_4332F0(&a3);
  if ( *((uint8_t *)*v3 + 137) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 137) == 0 )
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
      if ( *((uint8_t *)v4 + 137) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_433090(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 137) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_433060(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 137) != 0 )
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
    if ( *((uint8_t *)v4 + 137) == 0 )
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
  v14 = *((uint8_t *)v5 + 136);
  *((uint8_t *)v5 + 136) = *((uint8_t *)v3 + 136);
  *((uint8_t *)v3 + 136) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 136) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 136) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 136) == 0 )
          {
            *((uint8_t *)v16 + 136) = 1;
            *((uint8_t *)v6 + 136) = 0;
            sub_433000(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 137) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 136) != 1 || *(uint8_t *)(v16[2] + 136) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 136) == 1 )
            {
              *(uint8_t *)(*v16 + 136) = 1;
              *((uint8_t *)v16 + 136) = 0;
              sub_4330C0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 136) = *((uint8_t *)v6 + 136);
            *((uint8_t *)v6 + 136) = 1;
            *(uint8_t *)(v16[2] + 136) = 1;
            sub_433000(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 136) == 0 )
          {
            *((uint8_t *)v16 + 136) = 1;
            *((uint8_t *)v6 + 136) = 0;
            sub_4330C0(v6);
            v16 = (uint32_t *)*v6;
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 137) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 136) != 1 || *(uint8_t *)(*v16 + 136) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 136) == 1 )
            {
              *(uint8_t *)(v16[2] + 136) = 1;
              *((uint8_t *)v16 + 136) = 0;
              sub_433000(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 136) = *((uint8_t *)v6 + 136);
            *((uint8_t *)v6 + 136) = 1;
            *(uint8_t *)(*v16 + 136) = 1;
            sub_4330C0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 136) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 136) = 1;
  }
  sub_433FB0((char *)Block + 16);
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x436CA0 sub_436CA0
// ------------------------------------------------------------
char /*stdcall*/ sub_436CA0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 137);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_436CA0(i[2]);
    i = (void **)*i;
    sub_4347A0(v1);
    j__free(v1);
    result = *((uint8_t *)i + 137);
  }
  return result;
}



// ------------------------------------------------------------
// 0x436CF0 sub_436CF0
// ------------------------------------------------------------
int /*cdecl*/ sub_436CF0(int a1, int a2, int a3)
{
  return sub_435BF0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x436D10 sub_436D10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_436D10(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax

  v2 = this + 1;
  *this = &vftbl_CNUserManager;
  v3 = sub_433AC0();
  v2[1] = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(v2[1] + 4) = v2[1];
  *(uint32_t *)v2[1] = v2[1];
  *(uint32_t *)(v2[1] + 8) = v2[1];
  v2[2] = 0;
  sub_4296B0(this);
  sub_4298F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x436D80 CNUserManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNUserManager__vmt0(void *Block, char a2)
{
  sub_436DB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x436DB0 sub_436DB0
// ------------------------------------------------------------
void /*thiscall*/ sub_436DB0(int **this)
{
  int **v1; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **v4; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  v1 = this;
  v4 = this;
  *this = (int *)&vftbl_CNUserManager;
  v5 = 0;
  sub_4297A0(this);
  v2 = v1[2];
  ++v1;
  v3 = *v2;
  v5 = -1;
  sub_434B30(v1, (int *)&v4, v3, (int)v2);
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
}



// ------------------------------------------------------------
// 0x436E30 sub_436E30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_436E30(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax

  v2 = this + 1;
  *this = &vftbl_CNRDPartyManager;
  v3 = sub_433AC0();
  v2[1] = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(v2[1] + 4) = v2[1];
  *(uint32_t *)v2[1] = v2[1];
  *(uint32_t *)(v2[1] + 8) = v2[1];
  v2[2] = 0;
  sub_4562E0(this);
  sub_456A30(this);
  return this;
}



// ------------------------------------------------------------
// 0x436EA0 CNRDPartyManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyManager__vmt0(void *Block, char a2)
{
  sub_436ED0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x436ED0 sub_436ED0
// ------------------------------------------------------------
void /*thiscall*/ sub_436ED0(int **this)
{
  int **v1; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **v4; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  v1 = this;
  v4 = this;
  *this = (int *)&vftbl_CNRDPartyManager;
  v5 = 0;
  sub_4568C0();
  v2 = v1[2];
  ++v1;
  v3 = *v2;
  v5 = -1;
  sub_434BF0(v1, (int *)&v4, v3, (int)v2);
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
}



// ------------------------------------------------------------
// 0x436F50 sub_436F50
// ------------------------------------------------------------
int /*thiscall*/ sub_436F50(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  sub_435850(this);
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 32) = 1;
  *(uint8_t *)(this + 40) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x436FC0 sub_436FC0
// ------------------------------------------------------------
char */*thiscall*/ sub_436FC0(char *this)
{
  char *v2; // edi
  uint32_t *v3; // eax

  *(uint32_t *)this = &vftbl_CNCommandChecker;
  *(this + 8) = 0;
  *((uint32_t *)this + 1) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 3) = 0;
  *(this + 16) = 1;
  *(this + 18) = 0;
  *(this + 17) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  v2 = this + 32;
  v3 = sub_433B00();
  *((uint32_t *)v2 + 1) = v3;
  *((uint8_t *)v3 + 25) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 18) = sub_425940();
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 21) = sub_425940();
  *((uint32_t *)this + 22) = 0;
  CNCommandChecker__vmt64(this);
  CNCommandChecker__vmt68(this);
  return this;
}



// ------------------------------------------------------------
// 0x4370B0 ?set_bound@?$source_link_manager@V?$multi_link_registry@V?$ISource@W4agent_status@Concurrency@@@Concurrency@@@Concurrency@@@Concurrency@@QAEXI@Z
// ------------------------------------------------------------
int /*thiscall*/ Concurrency::source_link_manager<Concurrency::multi_link_registry<Concurrency::ISource<enum Concurrency::agent_status>>>::set_bound(
        uint32_t *this,
        int a2)
{
  *(this + 15) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4370D0 CNCommandChecker__vmt44
// ------------------------------------------------------------
char /*thiscall*/ CNCommandChecker__vmt44(uint8_t *this, int a2)
{
  return *(this + a2 + 64);
}



// ------------------------------------------------------------
// 0x437100 CNCommandChecker__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNCommandChecker__vmtC(uint32_t *this, char a2)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_437140(&v4, &a2);
  if ( v4 == *(this + 9) )
    return 0;
  else
    return v4 + 16;
}



// ------------------------------------------------------------
// 0x437140 sub_437140
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437140(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  int v5; // eax
  int v6; // esi
  int v8; // [esp+18h] [ebp+Ch]

  v5 = sub_437190(a3);
  v6 = *(this + 1);
  v8 = v5;
  if ( v5 == v6 || *a3 < *(uint32_t *)(v5 + 12) )
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
// 0x437190 sub_437190
// ------------------------------------------------------------
int */*thiscall*/ sub_437190(uint32_t *this, uint32_t *a2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 25) == 0 )
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
// 0x4371C0 CNCommandChecker__vmt54
// ------------------------------------------------------------
int /*stdcall*/ CNCommandChecker__vmt54(char a1)
{
  return sub_437240(&a1);
}



// ------------------------------------------------------------
// 0x4371E0 sub_4371E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4371E0(int this, uint32_t *a2, uint32_t **Block)
{
  uint32_t *v4; // edi

  v4 = *Block;
  if ( Block != *(uint32_t ***)(this + 4) )
  {
    *Block[1] = *Block;
    (*Block)[1] = Block[1];
    j__free(Block);
    --*(uint32_t *)(this + 8);
  }
  *a2 = v4;
  return a2;
}



// ------------------------------------------------------------
// 0x437220 CNCommandChecker__vmt60
// ------------------------------------------------------------
int /*stdcall*/ CNCommandChecker__vmt60(char a1)
{
  return sub_437240(&a1);
}



// ------------------------------------------------------------
// 0x437240 sub_437240
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437240(uint32_t *this, int a2)
{
  uint32_t **v3; // edi
  uint32_t *result; // eax
  uint32_t *v5; // ebx

  v3 = (uint32_t **)*(this + 1);
  result = *v3;
  if ( *v3 != v3 )
  {
    v5 = (uint32_t *)a2;
    do
    {
      if ( result[2] == *v5 )
        result = sub_4371E0((int)this, &a2, (uint32_t **)result);
      result = (uint32_t *)*result;
    }
    while ( result != v3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x437280 CNCommandChecker__vmt1C
// ------------------------------------------------------------
void /*thiscall*/ CNCommandChecker__vmt1C(void **this)
{
  sub_6569D0(this + 17);
  sub_5E5260(this + 11);
}



// ------------------------------------------------------------
// 0x4372A0 CNCommandChecker__vmt5C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNCommandChecker__vmt5C(uint32_t *this, int a2)
{
  uint32_t *v2; // edx
  uint32_t *result; // eax

  v2 = (uint32_t *)*(this + 18);
  result = (uint32_t *)*v2;
  if ( (uint32_t *)*v2 == v2 )
    return (uint32_t *)sub_4372E0(*(this + 18), &a2);
  do
  {
    if ( result[2] == a2 )
      break;
    result = (uint32_t *)*result;
  }
  while ( result != v2 );
  if ( result == v2 )
    return (uint32_t *)sub_4372E0(*(this + 18), &a2);
  return result;
}



// ------------------------------------------------------------
// 0x4372E0 sub_4372E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4372E0(int a1, int a2)
{
  int v2; // esi
  int result; // eax

  v2 = sub_40C0F0(a1, *(uint32_t *)(a1 + 4), a2);
  result = sub_437320(1);
  *(uint32_t *)(a1 + 4) = v2;
  **(uint32_t **)(v2 + 4) = v2;
  return result;
}



// ------------------------------------------------------------
// 0x437320 sub_437320
// ------------------------------------------------------------
int /*thiscall*/ sub_437320(uint32_t *this, unsigned int a2)
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
// 0x4373B0 CNCommandChecker__vmt10
// ------------------------------------------------------------
uint32_t */*stdcall*/ CNCommandChecker__vmt10(char a1, uint32_t *a2)
{
  uint32_t *result; // eax
  int v3; // ecx

  result = (uint32_t *)sub_4373D0(&a1);
  v3 = a2[1];
  *result = *a2;
  result[1] = v3;
  return result;
}



// ------------------------------------------------------------
// 0x4373D0 sub_4373D0
// ------------------------------------------------------------
int */*thiscall*/ sub_4373D0(uint32_t *this, int *a2)
{
  int *v2; // edi
  int *v4; // eax
  int v5; // edi
  uint32_t v7[3]; // [esp+8h] [ebp-Ch] BYREF

  v2 = a2;
  v4 = sub_437190(this, a2);
  if ( v4 == (int *)*(this + 1) || *v2 < v4[3] )
  {
    v5 = *v2;
    v7[2] = 0;
    v7[1] = 2;
    v7[0] = v5;
    v4 = *(int **)sub_437420(&a2, v4, v7);
  }
  return v4 + 4;
}



// ------------------------------------------------------------
// 0x437420 sub_437420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437420(uint32_t *this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  int v5; // eax
  uint32_t *v7; // eax
  int v8; // eax
  int v9; // ecx
  char v10[8]; // [esp+8h] [ebp-Ch] BYREF
  uint32_t *v11; // [esp+10h] [ebp-4h] BYREF

  v5 = *(this + 2);
  v11 = nullptr;
  if ( v5 == 0 )
  {
    sub_437590(a2, 1, *(this + 1), a4);
    return a2;
  }
  v7 = (uint32_t *)*(this + 1);
  if ( a3 == (uint32_t *)*v7 )
  {
    if ( *a4 < a3[3] )
    {
      sub_437590(a2, 1, a3, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v7 )
  {
    v8 = v7[2];
    if ( *(uint32_t *)(v8 + 12) < *a4 )
    {
      sub_437590(a2, 0, v8, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (v11 = a3, sub_4B0CC0(&v11), v11[3] >= *a4) )
  {
    if ( a3[3] >= *a4 || (v11 = a3, sub_4B0C60(&v11), v11 != (uint32_t *)*(this + 1)) && *a4 >= v11[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_437790(v10, a4);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 25) != 0 )
      sub_437590(a2, 0, a3, a4);
    else
      sub_437590(a2, 1, v11, a4);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(v11[2] + 25) != 0 )
      sub_437590(a2, 0, v11, a4);
    else
      sub_437590(a2, 1, a3, a4);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x437590 sub_437590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437590(uint32_t *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
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
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int v21; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x15555554u )
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);
    v20 = 0;
    sub_401740(v17);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  v6 = sub_437740(*(this + 1), a4, *(this + 1), a5, 0);
  v7 = (uint32_t *)*(this + 1);
  v21 = v6;
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
  if ( *(uint8_t *)(*(uint32_t *)(v6 + 4) + 24) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 24) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_4B0FD0(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 24) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 24) = 0;
          sub_4B0C00(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 24) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4B0C00(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 24) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 24) = 0;
        sub_4B0FD0(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 24) = 1;
      *(uint8_t *)(v14 + 24) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 24) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 24) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 24) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x437740 sub_437740
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_437740(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
  {
    *result = a1;
    result[1] = a2;
    result[2] = a3;
    result[3] = *a4;
    result[4] = a4[1];
    result[5] = a4[2];
    *((uint8_t *)result + 24) = a5;
    *((uint8_t *)result + 25) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x437790 sub_437790
// ------------------------------------------------------------
int /*thiscall*/ sub_437790(uint32_t *this, int a2, uint32_t *a3)
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
  if ( *((uint8_t *)v6 + 25) == 0 )
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
    while ( *((uint8_t *)v6 + 25) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_437590(this, &a3, 1, v5, (int)v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_4B0CC0(&a3);
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
    v12 = *sub_437590(this, &a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x437850 sub_437850
// ------------------------------------------------------------
void /*thiscall*/ sub_437850(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-4h] [ebp-24h]
  int *v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = (int *)this;
  *(uint32_t *)this = &vftbl_CNCommandChecker;
  v5 = 4;
  nullsub_3();
  sub_6569D0(this + 80);
  j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 84) = 0;
  sub_6569D0(this + 68);
  j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  v3 = *(int **)(this + 36);
  v2 = (int *)*v3;
  LOBYTE(v5) = 0;
  sub_434CB0((int ***)(this + 32), v4, v2, v3);
  j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 4) = &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x437920 CNCommandChecker__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNCommandChecker__vmt0(void *Block, char a2)
{
  sub_437850((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x437950 sub_437950
// ------------------------------------------------------------
int /*thiscall*/ sub_437950(int this)
{
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  return sub_435850(this);
}



// ------------------------------------------------------------
// 0x437980 sub_437980
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_437980(int *this)
{
  return sub_436840(this);
}



// ------------------------------------------------------------
// 0x437990 sub_437990
// ------------------------------------------------------------
int */*thiscall*/ sub_437990(int **this, int *a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v10; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(uint32_t *)v7 && a4 == v7 )
  {
    sub_435BA0(*(void ***)(v7 + 4));
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
        v10 = v5;
        if ( *(uint8_t *)(v5 + 33) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 33) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 33) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v5 != *(uint32_t *)(i + 8) )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = *(uint32_t *)(v5 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 33) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_4358C0(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x437A50 sub_437A50
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_437A50(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
      sub_435020(v3, a1);
      v3[4] = a1[4];
      v3[5] = a1[5];
    }
    v3 += 6;
    LOBYTE(v7) = 0;
    a1 += 6;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x437B00 sub_437B00
// ------------------------------------------------------------
int /*fastcall*/ sub_437B00(unsigned int a1, int a2)
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
  int v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  unsigned int v24; // ebx
  int i; // edi
  int v26; // edx
  unsigned int v27; // ebx
  int j; // edi
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
  unsigned int v44; // ebx
  int k; // edi
  unsigned int v46; // ebx
  char *v47; // edi
  int v48; // ebx
  int n; // edi
  char *v51; // [esp+Ch] [ebp-8h]
  int m; // [esp+10h] [ebp-4h]

  sub_41A590(a1, a2, 2);
  sub_41A590(a1 + 14, v3, 0);
  sub_41A590(a1 + 28, v4, 0);
  sub_41A590(a1 + 42, v5, 0);
  sub_41A590(a1 + 56, v6, 0);
  sub_41A590(a1 + 70, v7, 0);
  sub_41A590(a1 + 98, v8, 0);
  sub_41A590(a1 + 112, v9, 0);
  sub_41A590(a1 + 126, v10, 0);
  sub_41A590(a1 + 140, v11, 0);
  sub_41A590(a1 + 154, v12, 0);
  sub_41A590(a1 + 168, v13, 0);
  sub_41A590(a1 + 182, v14, 0);
  sub_41A590(a1 + 196, v15, 0);
  sub_41A590(a1 + 210, v16, 0);
  sub_41A590(a1 + 224, v17, 0);
  sub_41A590(a1 + 238, v18, 0);
  sub_41A590(a1 + 252, v19, 0);
  sub_41A590(a1 + 266, v20, 0);
  sub_41A590(a1 + 280, v21, 0);
  sub_41A590(a1 + 294, v22, 0);
  v24 = a1 + 308;
  for ( i = 4; i != 0; --i )
  {
    sub_41A590(v24, v23, 0);
    v24 += 14;
  }
  sub_41A590(a1 + 364, v23, 0);
  v27 = a1 + 378;
  for ( j = 16; j != 0; --j )
  {
    sub_41A590(v27, v26, 0);
    v27 += 14;
  }
  sub_41A590(a1 + 602, v26, 0);
  sub_41A590(a1 + 616, v29, 0);
  sub_41A590(a1 + 630, v30, 0);
  sub_41A590(a1 + 644, v31, 0);
  sub_41A590(a1 + 658, 0, 0);
  sub_41A590(a1 + 672, v32, 0);
  sub_41A590(a1 + 686, v33, 0);
  sub_41A590(a1 + 700, v34, 0);
  sub_41A590(a1 + 714, v35, 0);
  sub_41A590(a1 + 728, v36, 0);
  sub_41A590(a1 + 742, v37, 0);
  sub_41A590(a1 + 756, v38, 0);
  *(uint32_t *)(a1 + 772) = 4;
  *(uint32_t *)(a1 + 776) = 17;
  sub_41A590(a1 + 780, 0, 0);
  sub_41A590(a1 + 794, v39, 0);
  sub_41A590(a1 + 808, v40, 0);
  sub_41A590(a1 + 822, v41, 0);
  sub_41A590(a1 + 836, v42, 0);
  *(uint8_t *)(a1 + 850) = 0;
  v44 = a1 + 851;
  for ( k = 2; k != 0; --k )
  {
    sub_41A590(v44, v43, 0);
    v44 += 14;
  }
  *(uint8_t *)(a1 + 879) = 0;
  *(uint8_t *)(a1 + 880) = 0;
  v46 = a1 + 888;
  for ( m = 2; m != 0; --m )
  {
    if ( *(uint32_t *)v46 != 0 )
    {
      v47 = *(char **)v46;
      v51 = *(char **)(v46 + 4);
      if ( *(char **)v46 != v51 )
      {
        do
        {
          sub_432DC0(v47);
          v47 += 32;
        }
        while ( v47 != v51 );
      }
      j__free(*(void **)v46);
    }
    *(uint32_t *)v46 = 0;
    *(uint32_t *)(v46 + 4) = 0;
    *(uint32_t *)(v46 + 8) = 0;
    v46 += 16;
  }
  v48 = *(uint32_t *)(a1 + 920);
  if ( v48 != 0 )
  {
    for ( n = *(uint32_t *)(a1 + 924); v48 != n; v48 += 80 )
      sub_433D10(v48);
    j__free(*(void **)(a1 + 920));
  }
  *(uint32_t *)(a1 + 920) = 0;
  *(uint32_t *)(a1 + 924) = 0;
  *(uint32_t *)(a1 + 928) = 0;
  return sub_41A590(a1 + 932, v43, -1);
}


// ------------------------------------------------------------
// 0x437E70 sub_437E70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437E70(uint32_t *this)
{
  int v2; // edx

  sub_41A630((unsigned int)this);
  *this = &vftbl_clong;
  sub_41A630((unsigned int)this + 14);
  *(uint32_t *)((char *)this + 14) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 7));
  *(this + 7) = &vftbl_clong;
  sub_41A630((unsigned int)this + 42);
  *(uint32_t *)((char *)this + 42) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 14));
  *(this + 14) = &vftbl_clong;
  sub_41A630((unsigned int)this + 70);
  *(uint32_t *)((char *)this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 21));
  *(this + 21) = &vftbl_clong;
  sub_41A630((unsigned int)this + 98);
  *(uint32_t *)((char *)this + 98) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 28));
  *(this + 28) = &vftbl_clong;
  sub_41A630((unsigned int)this + 126);
  *(uint32_t *)((char *)this + 126) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 35));
  *(this + 35) = &vftbl_clong;
  sub_41A630((unsigned int)this + 154);
  *(uint32_t *)((char *)this + 154) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 42));
  *(this + 42) = &vftbl_clong;
  sub_41A630((unsigned int)this + 182);
  *(uint32_t *)((char *)this + 182) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 49));
  *(this + 49) = &vftbl_clong;
  sub_41A630((unsigned int)this + 210);
  *(uint32_t *)((char *)this + 210) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 56));
  *(this + 56) = &vftbl_clong;
  sub_41A630((unsigned int)this + 238);
  *(uint32_t *)((char *)this + 238) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 63));
  *(this + 63) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 266);
  *(uint32_t *)((char *)this + 266) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 70));
  *(this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)this + 294);
  *(uint32_t *)((char *)this + 294) = &vftbl_cfloat;
  `eh vector constructor iterator'(this + 77, 0xEu, 4, sub_401040, sub_432D10);
  sub_41A630((unsigned int)(this + 91));
  *(this + 91) = &vftbl_clong;
  `eh vector constructor iterator'((char *)this + 378, 0xEu, 16, sub_401040, sub_432D10);
  sub_41A630((unsigned int)this + 602);
  *(uint32_t *)((char *)this + 602) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 154));
  *(this + 154) = &vftbl_clong;
  sub_41A630((unsigned int)this + 630);
  *(uint32_t *)((char *)this + 630) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 161));
  *(this + 161) = &vftbl_clong;
  sub_41A630((unsigned int)this + 658);
  *(uint32_t *)((char *)this + 658) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 168));
  *(this + 168) = &vftbl_clong;
  sub_41A630((unsigned int)this + 686);
  *(uint32_t *)((char *)this + 686) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 175));
  *(this + 175) = &vftbl_clong;
  sub_41A630((unsigned int)this + 714);
  *(uint32_t *)((char *)this + 714) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 182));
  *(this + 182) = &vftbl_clong;
  sub_41A630((unsigned int)this + 742);
  *(uint32_t *)((char *)this + 742) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 189));
  *(this + 189) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 195));
  *(this + 195) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 794);
  *(uint32_t *)((char *)this + 794) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 202));
  *(this + 202) = &vftbl_clong;
  sub_41A630((unsigned int)this + 822);
  *(uint32_t *)((char *)this + 822) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 209));
  *(this + 209) = &vftbl_cfloat;
  `eh vector constructor iterator'((char *)this + 851, 0xEu, 2, (void (/*thiscall*/ *)(void *))sub_432CD0, sub_432D10);
  `eh vector constructor iterator'(this + 221, 0x10u, 2, sub_4019A0, sub_434940);
  *(this + 230) = 0;
  *(this + 231) = 0;
  *(this + 232) = 0;
  sub_41A630((unsigned int)(this + 233));
  *(this + 233) = &vftbl_clong;
  sub_437B00((unsigned int)this, v2);
  return this;
}



// ------------------------------------------------------------
// 0x4382D0 sub_4382D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4382D0(int *this)
{
  sub_41A580(this + 233);
  sub_436840(this + 229);
  `eh vector destructor iterator'(this + 221, 0x10u, 2, sub_434940);
  `eh vector destructor iterator'((char *)this + 851, 0xEu, 2, sub_432D10);
  sub_41A580(this + 209);
  sub_41A580((char *)this + 822);
  sub_41A580(this + 202);
  sub_41A580((char *)this + 794);
  sub_41A580(this + 195);
  sub_41A580(this + 189);
  sub_41A580((char *)this + 742);
  sub_41A580(this + 182);
  sub_41A580((char *)this + 714);
  sub_41A580(this + 175);
  sub_41A580((char *)this + 686);
  sub_41A580(this + 168);
  sub_41A580((char *)this + 658);
  sub_41A580(this + 161);
  sub_41A580((char *)this + 630);
  sub_41A580(this + 154);
  sub_41A580((char *)this + 602);
  `eh vector destructor iterator'((char *)this + 378, 0xEu, 16, sub_432D10);
  sub_41A580(this + 91);
  `eh vector destructor iterator'(this + 77, 0xEu, 4, sub_432D10);
  sub_41A580((char *)this + 294);
  sub_41A580(this + 70);
  sub_41A580((char *)this + 266);
  sub_41A580(this + 63);
  sub_41A580((char *)this + 238);
  sub_41A580(this + 56);
  sub_41A580((char *)this + 210);
  sub_41A580(this + 49);
  sub_41A580((char *)this + 182);
  sub_41A580(this + 42);
  sub_41A580((char *)this + 154);
  sub_41A580(this + 35);
  sub_41A580((char *)this + 126);
  sub_41A580(this + 28);
  sub_41A580((char *)this + 98);
  sub_41A580(this + 21);
  sub_41A580((char *)this + 70);
  sub_41A580(this + 14);
  sub_41A580((char *)this + 42);
  sub_41A580(this + 7);
  sub_41A580((char *)this + 14);
  return sub_41A580(this);
}



// ------------------------------------------------------------
// 0x4385C0 sub_4385C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4385C0(uint32_t *this)
{
  char *v2; // edx
  int i; // ebx
  void *v4; // edi

  v2 = (char *)this;
  for ( i = 8; i != 0; --i )
  {
    memset(v2, 0, 0x30u);
    v4 = v2 + 48;
    v2 += 96;
    memset(v4, 0, 0x30u);
  }
  memset(this + 192, 0, 0x30u);
  memset(this + 204, 0, 0x30u);
  sub_41A630((unsigned int)(this + 216));
  *(this + 216) = &vftbl_clong;
  sub_41A630((unsigned int)this + 878);
  *(uint32_t *)((char *)this + 878) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 223));
  *(this + 223) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 906);
  *(uint32_t *)((char *)this + 906) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 230));
  *(this + 230) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 934);
  *(uint32_t *)((char *)this + 934) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 237));
  *(this + 237) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 244));
  *(this + 244) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 990);
  *(uint32_t *)((char *)this + 990) = &vftbl_cfloat;
  *(this + 253) = 0;
  *(this + 254) = 0;
  *(this + 255) = 0;
  *(this + 257) = 0;
  *(this + 258) = 0;
  *(this + 259) = 0;
  sub_4968E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x438740 sub_438740
// ------------------------------------------------------------
int /*thiscall*/ sub_438740(char *this)
{
  sub_55A050(this + 1024);
  sub_55A050(this + 1008);
  sub_41A580(this + 990);
  sub_41A580(this + 976);
  sub_41A580(this + 948);
  sub_41A580(this + 934);
  sub_41A580(this + 920);
  sub_41A580(this + 906);
  sub_41A580(this + 892);
  sub_41A580(this + 878);
  return sub_41A580(this + 864);
}



// ------------------------------------------------------------
// 0x438820 sub_438820
// ------------------------------------------------------------
int */*thiscall*/ sub_438820(int **this, int *a2, int a3, int a4)
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
    sub_436CA0(*(void ***)(v6 + 4));
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
        sub_4332F0(&a3);
        sub_436940(this, &a4, v10);
        v7 = a3;
      }
      while ( a3 != v4 );
    }
    *a2 = v7;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4388A0 sub_4388A0
// ------------------------------------------------------------
void /*stdcall*/ sub_4388A0(void **a1, void **a2)
{
  void **i; // esi

  for ( i = a1; i != a2; i += 31 )
    sub_4347B0(i);
}



// ------------------------------------------------------------
// 0x4388D0 sub_4388D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4388D0(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_436880((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x438910 sub_438910
// ------------------------------------------------------------
void sub_438910()
{
  void *v0; // esi
  void *v1; // esi
  void *v2; // esi
  void *v3; // esi
  void *v4; // esi
  void *v5; // esi
  void *v6; // esi
  void *v7; // esi
  int *v8; // esi
  LPCRITICAL_SECTION v9; // esi

  if ( dword_8F84B4 != nullptr )
    j__free(dword_8F84B4);
  dword_8F84B4 = nullptr;
  if ( dword_8F84B8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84B8)(dword_8F84B8, 1);
  dword_8F84B8 = 0;
  if ( dword_8F84BC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84BC)(dword_8F84BC, 1);
  dword_8F84BC = 0;
  if ( dword_8F84C0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C0)(dword_8F84C0, 1);
  dword_8F84C0 = 0;
  if ( dword_8F84C4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C4)(dword_8F84C4, 1);
  dword_8F84C4 = 0;
  if ( dword_8F84C8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C8)(dword_8F84C8, 1);
  dword_8F84C8 = 0;
  if ( dword_8F84CC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84CC)(dword_8F84CC, 1);
  dword_8F84CC = 0;
  if ( dword_8F84D0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D0)(dword_8F84D0, 1);
  dword_8F84D0 = 0;
  if ( dword_8F84D4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D4)(dword_8F84D4, 1);
  dword_8F84D4 = 0;
  if ( dword_8F84D8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D8)(dword_8F84D8, 1);
  dword_8F84D8 = 0;
  if ( dword_8F84DC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84DC)(dword_8F84DC, 1);
  dword_8F84DC = 0;
  if ( dword_8F84E0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E0)(dword_8F84E0, 1);
  dword_8F84E0 = 0;
  if ( dword_8F84E4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E4)(dword_8F84E4, 1);
  dword_8F84E4 = 0;
  if ( dword_8F84E8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E8)(dword_8F84E8, 1);
  dword_8F84E8 = 0;
  if ( dword_8F84EC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84EC)(dword_8F84EC, 1);
  dword_8F84EC = 0;
  if ( dword_8F84F0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F0)(dword_8F84F0, 1);
  dword_8F84F0 = 0;
  if ( dword_8F84F4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F4)(dword_8F84F4, 1);
  dword_8F84F4 = 0;
  if ( dword_8F84F8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F8)(dword_8F84F8, 1);
  dword_8F84F8 = 0;
  if ( dword_8F84FC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84FC)(dword_8F84FC, 1);
  dword_8F84FC = 0;
  if ( dword_99FD58 != nullptr )
  {
    v0 = dword_99FD58;
    sub_438740((char *)dword_99FD58);
    j__free(v0);
  }
  dword_99FD58 = nullptr;
  if ( dword_8F8500 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8500)(dword_8F8500, 1);
  dword_8F8500 = 0;
  if ( dword_8F8504 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8504)(dword_8F8504, 1);
  dword_8F8504 = 0;
  if ( dword_8F8508 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8508)(dword_8F8508, 1);
  dword_8F8508 = 0;
  if ( dword_8F850C != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F850C)(dword_8F850C, 1);
  dword_8F850C = 0;
  if ( dword_8F8510 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8510)(dword_8F8510, 1);
  dword_8F8510 = 0;
  if ( dword_8F8514 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8514)(dword_8F8514, 1);
  dword_8F8514 = 0;
  if ( dword_8F851C != nullptr )
  {
    v1 = dword_8F851C;
    sub_4BF080(dword_8F851C);
    j__free(v1);
  }
  dword_8F851C = nullptr;
  if ( dword_8F8518 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8518)(dword_8F8518, 1);
  dword_8F8518 = 0;
  sub_475EF0();
  sub_47EC40();
  if ( dword_8F8520 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 4))(dword_8F8520, 1);
  dword_8F8520 = 0;
  if ( dword_8F8524 != nullptr )
  {
    v2 = dword_8F8524;
    sub_433420();
    j__free(v2);
  }
  dword_8F8524 = nullptr;
  if ( dword_8F8528 != nullptr )
  {
    v3 = dword_8F8528;
    sub_434050((char *)dword_8F8528);
    j__free(v3);
  }
  dword_8F8528 = nullptr;
  if ( dword_8F852C != nullptr )
  {
    v4 = dword_8F852C;
    sub_433E30((int)dword_8F852C);
    j__free(v4);
  }
  dword_8F852C = nullptr;
  if ( dword_8F8530 != nullptr )
  {
    v5 = dword_8F8530;
    sub_433E30((int)dword_8F8530);
    j__free(v5);
  }
  dword_8F8530 = nullptr;
  if ( dword_8F8534 != nullptr )
  {
    v6 = dword_8F8534;
    sub_433E30((int)dword_8F8534);
    j__free(v6);
  }
  dword_8F8534 = nullptr;
  if ( dword_8F8538 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8538)(dword_8F8538, 1);
  dword_8F8538 = 0;
  if ( dword_8F853C != nullptr )
  {
    v7 = dword_8F853C;
    sub_483CD0();
    j__free(v7);
  }
  dword_8F853C = nullptr;
  if ( dword_8F8540 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8540)(dword_8F8540, 1);
  dword_8F8540 = 0;
  if ( dword_8F8544 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8544)(dword_8F8544, 1);
  dword_8F8544 = 0;
  v8 = dword_8F8270;
  do
  {
    if ( *v8 != 0 )
      (**(void (/*thiscall*/ ***)(int, int))*v8)(*v8, 1);
    *v8++ = 0;
  }
  while ( (int)v8 < (int)&dword_8F831C );
  sub_4AEDB0();
  sub_431AA0();
  sub_4F2BC0();
  v9 = lpCriticalSection;
  if ( lpCriticalSection != nullptr )
  {
    sub_65FC70(lpCriticalSection);
    j__free(v9);
  }
  DeleteCriticalSection(&stru_8F8258);
}


// ------------------------------------------------------------
// 0x438D10 sub_438D10
// ------------------------------------------------------------
int /*thiscall*/ sub_438D10(int this)
{
  void **v2; // esi
  int result; // eax
  void **i; // edi

  v2 = *(void ***)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(void ***)(this + 8); v2 != i; v2 += 31 )
      sub_4347B0(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x438D50 sub_438D50
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_438D50(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_437A50(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x438D70 sub_438D70
// ------------------------------------------------------------
int /*thiscall*/ sub_438D70(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_437990((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x438DB0 sub_438DB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_438DB0(uint32_t *this, int a2, int a3, int a4)
{
  uint32_t *v5; // esi
  uint32_t *v6; // eax

  v5 = this + 67;
  *this = &vftbl_IFileResourceManager;
  v6 = sub_433B80();
  v5[1] = v6;
  *((uint8_t *)v6 + 45) = 1;
  *(uint32_t *)(v5[1] + 4) = v5[1];
  *(uint32_t *)v5[1] = v5[1];
  *(uint32_t *)(v5[1] + 8) = v5[1];
  v5[2] = 0;
  IFileResourceManager__vmt20(this);
  IFileResourceManager__vmt24(a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x438E40 IFileResourceManager__vmt4
// ------------------------------------------------------------
int /*thiscall*/ IFileResourceManager__vmt4(void *this, int a2)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t, int))(*(uint32_t *)this + 8))(this, 0, a2);
}



// ------------------------------------------------------------
// 0x438E60 IFileResourceManager__vmt1C
// ------------------------------------------------------------
char /*thiscall*/ IFileResourceManager__vmt1C(uint8_t *this, char a2)
{
  *(this + 280) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x438E70 IFileResourceManager__vmt14
// ------------------------------------------------------------
int /*thiscall*/ IFileResourceManager__vmt14(uint32_t *this)
{
  int result; // eax

  for ( result = *(this + 69); result != 0; result = *(this + 69) )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 44))(this, *(uint32_t *)*(this + 68));
  return result;
}



// ------------------------------------------------------------
// 0x438EA0 sub_438EA0
// ------------------------------------------------------------
void /*thiscall*/ sub_438EA0(int **this)
{
  int **v1; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **v4; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  v1 = this;
  v4 = this;
  *this = (int *)&vftbl_IFileResourceManager;
  v5 = 0;
  IFileResourceManager__vmt28();
  v2 = v1[68];
  v1 += 67;
  v3 = *v2;
  v5 = -1;
  sub_436880(v1, (int *)&v4, v3, (int)v2);
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
}



// ------------------------------------------------------------
// 0x438F20 IFileResourceManager__vmt0
// ------------------------------------------------------------
int **/*thiscall*/ IFileResourceManager__vmt0(int **Block, char a2)
{
  sub_438EA0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x438F50 CNScriptLoader__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNScriptLoader__vmt0(void *Block, char a2)
{
  sub_438F80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x438F80 sub_438F80
// ------------------------------------------------------------
void /*thiscall*/ sub_438F80(int **this)
{
  *this = (int *)&vftbl_CNScriptLoader;
  IFileResourceManager__vmt28();
  sub_438EA0(this);
}



// ------------------------------------------------------------
// 0x438FD0 CNAnimationLoader__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNAnimationLoader__vmt0(void *Block, char a2)
{
  sub_439000();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439000 sub_439000
// ------------------------------------------------------------
void /*thiscall*/ sub_439000(int **this)
{
  *this = (int *)&vftbl_CNAnimationLoader;
  IFileResourceManager__vmt28();
  sub_438EA0(this);
}



// ------------------------------------------------------------
// 0x439050 sub_439050
// ------------------------------------------------------------
int /*thiscall*/ sub_439050(int this, uint32_t *a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  void **v7; // edi
  unsigned int v8; // eax
  void **v9; // eax
  int v10; // eax
  int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( (uint32_t *)this == a2 )
    return this;
  v4 = a2[1];
  if ( v4 == 0 || (v5 = (a2[2] - v4) / 24) == 0 )
  {
    sub_435850(this);
    return this;
  }
  v7 = *(void ***)(this + 4);
  if ( v7 != nullptr )
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 24;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
      v12 = (*(uint32_t *)(this + 12) - (int)v7) / 24;
    else
      v12 = 0;
    if ( v5 <= v12 )
    {
      v14 = (uint32_t *)(a2[1] + 24 * sub_4FEF30(this));
      sub_436CF0(a2[1], (int)v14, (int)v7);
      *(uint32_t *)(this + 8) = sub_437A50(v14, (uint32_t *)a2[2], *(uint32_t **)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
    {
      sub_435820(v7, *(void ***)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_4FEF30(a2);
    if ( sub_434950((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_438D50((uint32_t *)a2[1], (uint32_t *)a2[2], *(uint32_t **)(this + 4));
    return this;
  }
  v9 = (void **)sub_435BF0(a2[1], a2[2], (int)v7);
  sub_435820(v9, *(void ***)(this + 8));
  v10 = a2[1];
  if ( v10 != 0 )
    v11 = *(uint32_t *)(this + 4) + 24 * ((a2[2] - v10) / 24);
  else
    v11 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = v11;
  return this;
}



// ------------------------------------------------------------
// 0x4391E0 sub_4391E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4391E0(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_438820((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x439220 sub_439220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_439220(uint32_t *this)
{
  uint32_t *v2; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  *this = &vftbl_CNRDQuestModule;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  v2 = this + 9;
  v3 = sub_433B40();
  v2[1] = v3;
  *((uint8_t *)v3 + 33) = 1;
  *(uint32_t *)(v2[1] + 4) = v2[1];
  *(uint32_t *)v2[1] = v2[1];
  *(uint32_t *)(v2[1] + 8) = v2[1];
  v2[2] = 0;
  v4 = sub_433AC0();
  *(this + 13) = v4;
  *((uint8_t *)v4 + 21) = 1;
  *(uint32_t *)(*(this + 13) + 4) = *(this + 13);
  *(uint32_t *)*(this + 13) = *(this + 13);
  *(uint32_t *)(*(this + 13) + 8) = *(this + 13);
  *(this + 14) = 0;
  nullsub_3();
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x4392E0 CNRDQuestModule__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestModule__vmt0(void *Block, char a2)
{
  sub_439310();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439310 sub_439310
// ------------------------------------------------------------
int /*thiscall*/ sub_439310(int this)
{
  int v3; // [esp-8h] [ebp-28h]
  int v4; // [esp-8h] [ebp-28h]
  int *v5; // [esp-4h] [ebp-24h]
  int *v6; // [esp-4h] [ebp-24h]
  int v7[2]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v7[1] = this;
  *(uint32_t *)this = &vftbl_CNRDQuestModule;
  v8 = 3;
  nullsub_3();
  v5 = *(int **)(this + 52);
  v3 = *v5;
  LOBYTE(v8) = 2;
  sub_41D980(v7, v3, v5);
  j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  v6 = *(int **)(this + 40);
  v4 = *v6;
  LOBYTE(v8) = 1;
  sub_437990((int **)(this + 36), v7, v4, (int)v6);
  j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  v8 = -1;
  return sub_4349A0((int *)(this + 4));
}



// ------------------------------------------------------------
// 0x4393E0 sub_4393E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4393E0(char *this)
{
  void **v2; // eax
  void **v3; // edi
  int v4; // eax
  int v5; // edi
  void **v6; // eax
  void **v7; // edi
  void **v8; // eax
  void **v9; // edi
  void **v10; // [esp+Ch] [ebp-4h]
  int v11; // [esp+Ch] [ebp-4h]
  void **v12; // [esp+Ch] [ebp-4h]
  void **v13; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_41BFE0((void **)this + 530, szPassword);
  sub_41BFE0((void **)this + 531, szPassword);
  sub_41BFE0((void **)this + 532, szPassword);
  sub_41BFE0((void **)this + 533, szPassword);
  sub_41BFE0((void **)this + 534, szPassword);
  sub_41BFE0((void **)this + 276, szPassword);
  *((uint32_t *)this + 1) = 1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 9) = -1;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = -1;
  *((uint32_t *)this + 14) = 0;
  sub_41BFE0((void **)this + 15, szPassword);
  *((uint32_t *)this + 16) = 0;
  sub_41BFE0((void **)this + 17, szPassword);
  *((uint32_t *)this + 18) = 0;
  v2 = *((void ***)this + 20);
  if ( v2 != nullptr )
  {
    v3 = *((void ***)this + 20);
    v10 = *((void ***)this + 21);
    if ( v2 != v10 )
    {
      do
        sub_41B010(v3++);
      while ( v3 != v10 );
    }
    j__free(*((void **)this + 20));
  }
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 18;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  sub_437B00(this + 104);
  v4 = *((uint32_t *)this + 264);
  if ( v4 != 0 )
  {
    v5 = *((uint32_t *)this + 264);
    v11 = *((uint32_t *)this + 265);
    if ( v4 != v11 )
    {
      do
      {
        sub_4347B0(v5);
        v5 += 124;
      }
      while ( v5 != v11 );
    }
    j__free(*((void **)this + 264));
  }
  *((uint32_t *)this + 264) = 0;
  *((uint32_t *)this + 265) = 0;
  *((uint32_t *)this + 266) = 0;
  sub_41BFE0((void **)this + 267, szPassword);
  v6 = *((void ***)this + 269);
  if ( v6 != nullptr )
  {
    v7 = *((void ***)this + 269);
    v12 = *((void ***)this + 270);
    if ( v6 != v12 )
    {
      do
        sub_41B010(v7++);
      while ( v7 != v12 );
    }
    j__free(*((void **)this + 269));
  }
  *((uint32_t *)this + 269) = 0;
  *((uint32_t *)this + 270) = 0;
  *((uint32_t *)this + 271) = 0;
  sub_41BFE0((void **)this + 272, szPassword);
  *((uint32_t *)this + 273) = -1;
  *((uint32_t *)this + 274) = -1;
  *(this + 1100) = 0;
  if ( *((uint32_t *)this + 278) != 0 )
    j__free(*((void **)this + 278));
  *((uint32_t *)this + 278) = 0;
  *((uint32_t *)this + 279) = 0;
  *((uint32_t *)this + 280) = 0;
  sub_437B00(this + 1124);
  *((uint32_t *)this + 518) = -1;
  if ( *((uint32_t *)this + 520) != 0 )
    j__free(*((void **)this + 520));
  *((uint32_t *)this + 520) = 0;
  *((uint32_t *)this + 521) = 0;
  *((uint32_t *)this + 522) = 0;
  v8 = *((void ***)this + 524);
  if ( v8 != nullptr )
  {
    v9 = *((void ***)this + 524);
    v13 = *((void ***)this + 525);
    if ( v8 != v13 )
    {
      do
        sub_41B010(v9++);
      while ( v9 != v13 );
    }
    j__free(*((void **)this + 524));
  }
  *((uint32_t *)this + 524) = 0;
  *((uint32_t *)this + 525) = 0;
  *((uint32_t *)this + 526) = 0;
  *((uint32_t *)this + 529) = -1;
  *(this + 2108) = 0;
  *((uint32_t *)this + 528) = 0;
}


// ------------------------------------------------------------
// 0x439680 sub_439680
// ------------------------------------------------------------
int /*thiscall*/ sub_439680(int this)
{
  void **v2; // ecx

  v2 = (void **)(this + 60);
  *v2 = nullptr;
  sub_41BFE0(v2, szPassword);
  *(uint32_t *)(this + 68) = 0;
  sub_41BFE0((void **)(this + 68), szPassword);
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  sub_437E70((uint32_t *)(this + 104));
  *(uint32_t *)(this + 1056) = 0;
  *(uint32_t *)(this + 1060) = 0;
  *(uint32_t *)(this + 1064) = 0;
  *(uint32_t *)(this + 1068) = 0;
  sub_41BFE0((void **)(this + 1068), szPassword);
  *(uint32_t *)(this + 1076) = 0;
  *(uint32_t *)(this + 1080) = 0;
  *(uint32_t *)(this + 1084) = 0;
  *(uint32_t *)(this + 1088) = 0;
  sub_41BFE0((void **)(this + 1088), szPassword);
  *(uint32_t *)(this + 1104) = 0;
  sub_41BFE0((void **)(this + 1104), szPassword);
  *(uint32_t *)(this + 1112) = 0;
  *(uint32_t *)(this + 1116) = 0;
  *(uint32_t *)(this + 1120) = 0;
  sub_437E70((uint32_t *)(this + 1124));
  *(uint32_t *)(this + 2080) = 0;
  *(uint32_t *)(this + 2084) = 0;
  *(uint32_t *)(this + 2088) = 0;
  *(uint32_t *)(this + 2096) = 0;
  *(uint32_t *)(this + 2100) = 0;
  *(uint32_t *)(this + 2104) = 0;
  *(uint32_t *)(this + 2120) = 0;
  sub_41BFE0((void **)(this + 2120), szPassword);
  *(uint32_t *)(this + 2124) = 0;
  sub_41BFE0((void **)(this + 2124), szPassword);
  *(uint32_t *)(this + 2128) = 0;
  sub_41BFE0((void **)(this + 2128), szPassword);
  *(uint32_t *)(this + 2132) = 0;
  sub_41BFE0((void **)(this + 2132), szPassword);
  *(uint32_t *)(this + 2136) = 0;
  sub_41BFE0((void **)(this + 2136), szPassword);
  sub_4393E0((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x439810 sub_439810
// ------------------------------------------------------------
void /*thiscall*/ sub_439810(int this)
{
  sub_41B010((void **)(this + 2136));
  sub_41B010((void **)(this + 2132));
  sub_41B010((void **)(this + 2128));
  sub_41B010((void **)(this + 2124));
  sub_41B010((void **)(this + 2120));
  sub_4017E0(this + 2092);
  if ( *(uint32_t *)(this + 2080) != 0 )
    j__free(*(void **)(this + 2080));
  *(uint32_t *)(this + 2080) = 0;
  *(uint32_t *)(this + 2084) = 0;
  *(uint32_t *)(this + 2088) = 0;
  sub_4382D0((int *)(this + 1124));
  if ( *(uint32_t *)(this + 1112) != 0 )
    j__free(*(void **)(this + 1112));
  *(uint32_t *)(this + 1112) = 0;
  *(uint32_t *)(this + 1116) = 0;
  *(uint32_t *)(this + 1120) = 0;
  sub_41B010((void **)(this + 1104));
  sub_41B010((void **)(this + 1088));
  sub_4017E0(this + 1072);
  sub_41B010((void **)(this + 1068));
  sub_438D10(this + 1052);
  sub_4382D0((int *)(this + 104));
  sub_4017E0(this + 76);
  sub_41B010((void **)(this + 68));
  sub_41B010((void **)(this + 60));
}



// ------------------------------------------------------------
// 0x439980 sub_439980
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_439980(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *v3; // eax

  v2 = this + 1;
  *this = &vftbl_CNPvpRoomManager;
  v3 = sub_433A80();
  v2[1] = v3;
  *((uint8_t *)v3 + 137) = 1;
  *(uint32_t *)(v2[1] + 4) = v2[1];
  *(uint32_t *)v2[1] = v2[1];
  *(uint32_t *)(v2[1] + 8) = v2[1];
  v2[2] = 0;
  nullsub_3();
  sub_4878B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x439A00 CNPvpRoomManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNPvpRoomManager__vmt0(void *Block, char a2)
{
  sub_439A30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439A30 sub_439A30
// ------------------------------------------------------------
void /*thiscall*/ sub_439A30(int **this)
{
  int **v1; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **v4; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  v1 = this;
  v4 = this;
  *this = (int *)&vftbl_CNPvpRoomManager;
  v5 = 0;
  nullsub_3();
  v2 = v1[2];
  ++v1;
  v3 = *v2;
  v5 = -1;
  sub_438820(v1, (int *)&v4, v3, (int)v2);
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
}



// ------------------------------------------------------------
// 0x439AB0 sub_439AB0
// ------------------------------------------------------------
void sub_439AB0()
{
  struct _RTL_CRITICAL_SECTION *v0; // eax
  void *v1; // eax
  uint32_t *v2; // eax
  void *v3; // eax
  int v4; // edx
  char *v5; // eax
  bool v6; // zf
  HWND v7; // edi
  const CHAR *v8; // eax
  HWND v9; // edi
  const CHAR *v10; // eax
  HWND v11; // edi
  const CHAR *v12; // eax
  HWND v13; // edi
  const CHAR *v14; // eax
  int v15; // eax
  uint8_t *v16; // eax
  void *v17; // eax
  char *v18; // eax
  void *v19; // eax
  char *v20; // eax
  uint32_t *v21; // esi
  uint32_t *v22; // esi
  uint32_t *v23; // esi
  uint32_t *v24; // esi
  uint32_t *v25; // esi
  uint32_t *v26; // esi
  uint32_t *v27; // esi
  uint32_t *v28; // esi
  uint32_t *v29; // esi
  uint32_t *v30; // esi
  uint32_t *v31; // esi
  uint32_t *v32; // esi
  uint32_t *v33; // esi
  uint32_t *v34; // esi
  uint32_t *v35; // esi
  uint32_t *v36; // esi
  void *v37; // eax
  void *v38; // eax
  void *v39; // eax
  int v40; // eax
  void *v41; // eax
  int v42; // eax
  uint32_t *v43; // eax
  uint32_t *v44; // esi
  int v45; // eax
  void *v46; // eax
  int v47; // eax
  void *v48; // eax
  int v49; // eax
  void *v50; // eax
  int v51; // eax
  void *v52; // eax
  int v53; // eax
  uint8_t *v54; // eax
  uint8_t *v55; // eax
  void *v56; // eax
  uint32_t *v57; // eax
  uint32_t *v58; // eax
  void *v59; // eax
  int v60; // esi
  int v61; // eax
  bool (/*cdecl*/ *v62)(struct Concurrency::details::_UnrealizedChore *, void *); // eax
  void *v63; // eax
  void *v64; // eax
  void *v65; // eax
  void *v66; // eax
  void *v67; // eax
  void *v68; // eax
  void *v69; // eax
  void *v70; // eax
  int v71; // eax
  uint32_t *v72; // eax
  uint32_t *v73; // esi
  void *v74; // eax
  int v75; // eax
  uint32_t *v76; // eax
  uint32_t *v77; // esi
  uint32_t *v78; // eax
  uint32_t *v79; // eax
  uint32_t *v80; // eax
  uint32_t *v81; // eax
  uint32_t *v82; // eax
  uint32_t *v83; // eax
  uint32_t *v84; // eax
  uint32_t *v85; // eax
  uint32_t *v86; // eax
  uint32_t *v87; // eax
  uint32_t *v88; // eax
  uint32_t *v89; // eax
  uint32_t *v90; // eax
  uint32_t *v91; // eax
  uint32_t *v92; // eax
  uint32_t *v93; // eax
  uint32_t *v94; // eax
  uint32_t *v95; // eax
  uint32_t *v96; // eax
  uint32_t *v97; // eax
  uint32_t *v98; // eax
  uint32_t *v99; // eax
  uint32_t *v100; // eax
  uint32_t *v101; // eax
  uint32_t *v102; // eax
  uint32_t *v103; // eax
  uint32_t *v104; // eax
  uint32_t *v105; // eax
  uint32_t *v106; // eax
  uint32_t *v107; // eax
  uint32_t *v108; // eax
  uint32_t *v109; // eax
  uint32_t *v110; // eax
  uint32_t *v111; // eax
  uint32_t *v112; // eax
  uint32_t *v113; // eax
  uint32_t *v114; // eax
  uint32_t *v115; // eax
  uint32_t *v116; // eax
  uint32_t *v117; // eax
  uint32_t *v118; // eax
  uint32_t *v119; // eax
  uint32_t *v120; // eax
  uint32_t *v121; // eax
  uint32_t *v122; // eax
  uint32_t *v123; // eax
  uint32_t *v124; // eax
  uint32_t *v125; // eax
  uint32_t *v126; // eax
  uint32_t *v127; // eax
  uint32_t *v128; // eax
  uint32_t *v129; // eax
  uint32_t *v130; // eax
  uint32_t *v131; // eax
  uint32_t *v132; // eax
  uint32_t *v133; // eax
  uint32_t *v134; // eax
  uint32_t *v135; // eax
  uint32_t *v136; // eax
  uint32_t *v137; // eax
  uint32_t *v138; // eax
  uint32_t *v139; // eax
  uint32_t *v140; // eax
  uint32_t *v141; // eax
  uint32_t *v142; // eax
  uint32_t *v143; // eax
  uint32_t *v144; // eax
  uint32_t *v145; // eax
  uint32_t *v146; // eax
  uint32_t *v147; // eax
  uint32_t *v148; // eax
  uint32_t *v149; // eax
  uint32_t *v150; // eax
  uint32_t *v151; // eax
  uint32_t *v152; // eax
  uint32_t *v153; // eax
  uint32_t *v154; // eax
  uint32_t *v155; // eax
  uint32_t *v156; // eax
  uint32_t *v157; // eax
  uint32_t *v158; // eax
  uint32_t *v159; // eax
  uint32_t *v160; // eax
  uint32_t *v161; // eax
  uint32_t *v162; // eax
  uint32_t *v163; // eax
  int i; // eax
  uint32_t *v165; // eax
  char *v166; // eax
  int j; // eax
  void **v168; // esi
  void **v169; // edi
  int v170; // [esp-4h] [ebp-89Ch]
  int v171; // [esp-4h] [ebp-89Ch]
  bool (/*cdecl*/ *v172)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp-4h] [ebp-89Ch]
  void *v173; // [esp+0h] [ebp-898h]
  bool (/*cdecl*/ *v174)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+4h] [ebp-894h]
  char v175[4]; // [esp+Ch] [ebp-88Ch] BYREF
  void *Block; // [esp+10h] [ebp-888h]
  void **v177; // [esp+14h] [ebp-884h]
  int v178; // [esp+18h] [ebp-880h]
  uint16_t v179[2]; // [esp+1Ch] [ebp-87Ch] BYREF
  int v180; // [esp+20h] [ebp-878h]
  int v181; // [esp+24h] [ebp-874h] BYREF
  void *v182; // [esp+28h] [ebp-870h]
  int v183[536]; // [esp+2Ch] [ebp-86Ch] BYREF
  int v184; // [esp+894h] [ebp-4h]

  v183[535] = dword_796E50;
  v0 = (struct _RTL_CRITICAL_SECTION *)operator new(0xA14u);
  v182 = v0;
  v184 = 0;
  if ( v0 != nullptr )
    sub_65FED0(v0);
  v170 = *(uint32_t *)(dword_79C0A0 + 16);
  v184 = -1;
  if ( sub_65D680(lpCriticalSection, v170) != 0 && (uint8_t)sub_65EDD0("audio.xml") != 0 )
    byte_8F8554 = 1;
  else
    off_77F3FC("Audio Manager Create Failed!");
  sub_65DAF0(0);
  sub_65D8A0(&off_77FD68);
  _access("_SoundPacks", 0);
  if ( _access("!SoundPacks", 0) != 0 )
  {
    sub_40F2B0("SoundPacks/", 1);
    lpCriticalSection[107].LockCount = (LONG)&unk_8A76C8;
  }
  Block = nullptr;
  v177 = nullptr;
  v178 = 0;
  v184 = 2;
  sub_444A40("String.lst");
  v1 = operator new(0x4318u);
  v182 = v1;
  if ( v1 != nullptr )
    v2 = (uint32_t *)sub_433C40(v1);
  else
    v2 = nullptr;
  dword_99FD6C = v2;
  sub_488AB0(v2);
  v3 = operator new(0x68u);
  v182 = v3;
  LOBYTE(v184) = 3;
  if ( v3 != nullptr )
  {
    v4 = 28 * *((uint32_t *)dword_99FD6C + 1);
    if ( *(uint32_t *)((char *)dword_99FD6C + v4 + 14368) < 0x10u )
      v5 = sub_4198A0((char *)v3, dword_79C0A4, (char *)dword_99FD6C + v4 + 14348);
    else
      v5 = sub_4198A0((char *)v3, dword_79C0A4, *(char **)((char *)dword_99FD6C + v4 + 14348));
  }
  else
  {
    v5 = nullptr;
  }
  dword_99FD68 = (int)v5;
  v6 = v5[4] == 0;
  LOBYTE(v184) = 1;
  if ( v6 )
    off_77F3FC("IMAGE LOAD ERROR");
  dword_978998 = (int)sub_488440;
  if ( sub_436310() == 0 )
  {
    v7 = *(HWND *)(dword_79C0A0 + 16);
    v8 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v7, v8, "Run Error", 0);
  }
  if ( (uint8_t)sub_4F8E20(&unk_8F8320) == 0 )
  {
    v9 = *(HWND *)(dword_79C0A0 + 16);
    v10 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v9, v10, "Run Error", 0);
  }
  if ( (uint8_t)sub_4FA630("Etc/EmoticonTypeTags.etc") == 0 )
  {
    v11 = *(HWND *)(dword_79C0A0 + 16);
    v12 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v11, v12, "Run Error", 0);
  }
  if ( (uint8_t)sub_4FA820("Etc/SlangList.etc", v175) == 0 )
  {
    ShowCursor(true);
    v13 = *(HWND *)(dword_79C0A0 + 16);
    v14 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v13, v14, "Run Error", 0);
    PostQuitMessage(0);
  }
  sub_508C30("Character/", "Character.lst", "ExpTable.tbl", "PVPPriceTable.tbl");
  sub_50D260("Monster/", "Monster.lst");
  sub_508D50("PassiveObject/", "PassiveObject.lst");
  sub_508DE0("Pet/", "Pet.lst");
  sub_4F4BE0("Equipment/", "Equipment.lst", "PriceTable.tbl");
  sub_4F4D50("Stackable/", "Stackable.lst", "PriceTable.tbl");
  sub_4AB6A0();
  sub_504300("Map/", "Map.lst");
  sub_4F0600("Dungeon/", "Dungeon.lst");
  sub_4AB6A0();
  sub_502B30("Skill/", "SkillList.lst");
  sub_4AB6A0();
  sub_5002A0("ItemShop/", "ItemShop.lst");
  sub_4FEEA0("Quest/", "Quest.lst");
  sub_4FD770("Npc/", "Npc.lst");
  sub_4FD430("WorldMap/", "WorldMap.lst");
  sub_4FC840("Town/", "Town.lst");
  sub_4FC1E0((int)byte_8F85E0, (char)"Etc/ServerParameter.etc");
  sub_4FBA70();
  sub_4F9240(&unk_8F7C68);
  sub_439680(v183);
  LOBYTE(v184) = 4;
  sub_4F7C60((int)v183, (char)"character/gunner/weapon/revolver/n_rev_coltpats.equ");
  v182 = operator new(0x24u);
  LOBYTE(v184) = 5;
  if ( v182 != nullptr )
    v15 = sub_435690(v175);
  else
    v15 = 0;
  LOBYTE(v184) = 4;
  dword_99FD60 = v15;
  v16 = operator new(8u);
  if ( v16 != nullptr )
  {
    *(uint32_t *)v16 = &CNWebTextFilter::`vftable';
    v16[4] = 1;
  }
  else
  {
    v16 = nullptr;
  }
  dword_99FD5C = (int)v16;
  v17 = operator new(0x164u);
  v182 = v17;
  LOBYTE(v184) = 6;
  if ( v17 != nullptr )
    v18 = sub_4BC900((char *)v17, (int)"Sprite/", 0, 0);
  else
    v18 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F84B8 = (int)v18;
  v19 = operator new(0x164u);
  v182 = v19;
  LOBYTE(v184) = 7;
  if ( v19 != nullptr )
    v20 = sub_4BC900((char *)v19, (int)"Sprite/", 1, 0);
  else
    v20 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F84BC = (int)v20;
  v21 = operator new(0x124u);
  v182 = v21;
  LOBYTE(v184) = 8;
  if ( v21 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v21 = &CNScriptLoader::`vftable';
    v21[72] = 0;
  }
  else
  {
    v21 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C0 = (int)v21;
  v22 = operator new(0x124u);
  v182 = v22;
  LOBYTE(v184) = 9;
  if ( v22 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v22 = &CNScriptLoader::`vftable';
    v22[72] = 1;
  }
  else
  {
    v22 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C4 = (int)v22;
  v23 = operator new(0x124u);
  v182 = v23;
  LOBYTE(v184) = 10;
  if ( v23 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v23 = &CNScriptLoader::`vftable';
    v23[72] = 2;
  }
  else
  {
    v23 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C8 = (int)v23;
  v24 = operator new(0x124u);
  v182 = v24;
  LOBYTE(v184) = 11;
  if ( v24 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v24 = &CNScriptLoader::`vftable';
    v24[72] = 3;
  }
  else
  {
    v24 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84CC = (int)v24;
  v25 = operator new(0x124u);
  v182 = v25;
  LOBYTE(v184) = 12;
  if ( v25 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v25 = &CNScriptLoader::`vftable';
    v25[72] = 4;
  }
  else
  {
    v25 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D0 = (int)v25;
  v26 = operator new(0x124u);
  v182 = v26;
  LOBYTE(v184) = 13;
  if ( v26 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v26 = &CNScriptLoader::`vftable';
    v26[72] = 5;
  }
  else
  {
    v26 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D4 = (int)v26;
  v27 = operator new(0x124u);
  v182 = v27;
  LOBYTE(v184) = 14;
  if ( v27 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v27 = &CNScriptLoader::`vftable';
    v27[72] = 6;
  }
  else
  {
    v27 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D8 = (int)v27;
  v28 = operator new(0x124u);
  v182 = v28;
  LOBYTE(v184) = 15;
  if ( v28 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v28 = &CNScriptLoader::`vftable';
    v28[72] = 7;
  }
  else
  {
    v28 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84DC = (int)v28;
  v29 = operator new(0x124u);
  v182 = v29;
  LOBYTE(v184) = 16;
  if ( v29 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v29 = &CNScriptLoader::`vftable';
    v29[72] = 8;
  }
  else
  {
    v29 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E0 = (int)v29;
  v30 = operator new(0x124u);
  v182 = v30;
  LOBYTE(v184) = 17;
  if ( v30 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v30 = &CNScriptLoader::`vftable';
    v30[72] = 9;
  }
  else
  {
    v30 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E4 = (int)v30;
  v31 = operator new(0x124u);
  v182 = v31;
  LOBYTE(v184) = 18;
  if ( v31 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v31 = &CNScriptLoader::`vftable';
    v31[72] = 10;
  }
  else
  {
    v31 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E8 = (int)v31;
  v32 = operator new(0x124u);
  v182 = v32;
  LOBYTE(v184) = 19;
  if ( v32 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v32 = &CNScriptLoader::`vftable';
    v32[72] = 11;
  }
  else
  {
    v32 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84EC = (int)v32;
  v33 = operator new(0x124u);
  v182 = v33;
  LOBYTE(v184) = 20;
  if ( v33 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v33 = &CNScriptLoader::`vftable';
    v33[72] = 12;
  }
  else
  {
    v33 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F0 = (int)v33;
  v34 = operator new(0x124u);
  v182 = v34;
  LOBYTE(v184) = 21;
  if ( v34 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v34 = &CNScriptLoader::`vftable';
    v34[72] = 13;
  }
  else
  {
    v34 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F4 = (int)v34;
  v35 = operator new(0x124u);
  v182 = v35;
  LOBYTE(v184) = 22;
  if ( v35 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v35 = &CNScriptLoader::`vftable';
    v35[72] = 14;
  }
  else
  {
    v35 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F8 = (int)v35;
  v36 = operator new(0x120u);
  v182 = v36;
  LOBYTE(v184) = 23;
  if ( v36 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v36 = &CNAnimationLoader::`vftable';
  }
  else
  {
    v36 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84FC = (int)v36;
  v37 = operator new(0x410u);
  v182 = v37;
  LOBYTE(v184) = 24;
  if ( v37 != nullptr )
    v38 = (void *)sub_4385C0(v37);
  else
    v38 = nullptr;
  LOBYTE(v184) = 4;
  dword_99FD58 = v38;
  v39 = operator new(0x14u);
  v182 = v39;
  LOBYTE(v184) = 25;
  if ( v39 != nullptr )
    v40 = sub_436D10(v39);
  else
    v40 = 0;
  LOBYTE(v184) = 4;
  dword_8F8500 = v40;
  v41 = operator new(0x10u);
  v182 = v41;
  LOBYTE(v184) = 26;
  if ( v41 != nullptr )
    v42 = sub_439980(v41);
  else
    v42 = 0;
  LOBYTE(v184) = 4;
  dword_8F8504 = v42;
  v43 = operator new(0xCu);
  v44 = v43;
  v182 = v43;
  LOBYTE(v184) = 27;
  if ( v43 != nullptr )
  {
    *v43 = &off_6C45C8;
    sub_49EA10(v43);
    sub_49F320(v44);
  }
  else
  {
    v44 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8508 = (int)v44;
  if ( dword_8F7C48 != nullptr )
    v45 = (dword_8F7C4C - (int)dword_8F7C48) / 20;
  else
    v45 = 0;
  sub_49F970(v44, v45);
  v46 = operator new(0x24u);
  v182 = v46;
  LOBYTE(v184) = 28;
  if ( v46 != nullptr )
    v47 = sub_436E30(v46);
  else
    v47 = 0;
  LOBYTE(v184) = 4;
  dword_8F850C = v47;
  v48 = operator new(0x14u);
  v182 = v48;
  LOBYTE(v184) = 29;
  if ( v48 != nullptr )
    v49 = sub_47A9B0(v48);
  else
    v49 = 0;
  LOBYTE(v184) = 4;
  dword_8F8510 = v49;
  v50 = operator new(0x78u);
  v182 = v50;
  LOBYTE(v184) = 30;
  if ( v50 != nullptr )
    v51 = sub_47A9E0(v50);
  else
    v51 = 0;
  LOBYTE(v184) = 4;
  dword_8F8514 = v51;
  v52 = operator new(0x8Cu);
  v182 = v52;
  LOBYTE(v184) = 31;
  if ( v52 != nullptr )
    v53 = sub_47AB30(v52);
  else
    v53 = 0;
  LOBYTE(v184) = 4;
  dword_8F8518 = v53;
  v54 = operator new(0x10u);
  v182 = v54;
  LOBYTE(v184) = 32;
  if ( v54 != nullptr )
    v55 = sub_4BF200(v54);
  else
    v55 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F851C = v55;
  sub_472AF0();
  sub_483870();
  v56 = operator new(0x1C0u);
  v182 = v56;
  LOBYTE(v184) = 33;
  if ( v56 != nullptr )
    v57 = (uint32_t *)sub_433360(v56);
  else
    v57 = nullptr;
  dword_8F8524 = v57;
  v171 = v57[4];
  LOBYTE(v184) = 4;
  v58 = (uint32_t *)sub_656710();
  sub_656790(v58, v171);
  v59 = operator new(0x100678u);
  v182 = v59;
  LOBYTE(v184) = 34;
  if ( v59 != nullptr )
    v60 = sub_435C30(v59);
  else
    v60 = 0;
  LOBYTE(v184) = 4;
  dword_8F8520 = v60;
  *(uint32_t *)(sub_656710() + 36) = v60;
  v61 = *(uint32_t *)(dword_8F8520 + 1049988);
  if ( v61 != 0 )
    v62 = (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))(v61 + 2220);
  else
    v62 = nullptr;
  v172 = v62;
  sub_656710();
  Concurrency::details::ContextBase::SweepUnstructured(v172, v173, v174);
  v63 = operator new(0x3Cu);
  v182 = v63;
  LOBYTE(v184) = 35;
  if ( v63 != nullptr )
  {
    if ( dword_8F8520 != 0 )
      v64 = sub_656470(v63, dword_8F8520 + 8);
    else
      v64 = sub_656470(v63, 0);
  }
  else
  {
    v64 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8548 = (int)v64;
  v65 = operator new(0x9ECu);
  v182 = v65;
  LOBYTE(v184) = 36;
  if ( v65 != nullptr )
    v66 = (void *)sub_4355A0(v65);
  else
    v66 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8528 = v66;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 37;
  if ( v182 != nullptr )
    v67 = (void *)sub_4354D0(nullptr, 137);
  else
    v67 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F852C = v67;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 38;
  if ( v182 != nullptr )
    v68 = (void *)sub_4354D0((void *)2, 64);
  else
    v68 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8530 = v68;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 39;
  if ( v182 != nullptr )
    v69 = (void *)sub_4354D0((void *)1, 105);
  else
    v69 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8534 = v69;
  v70 = operator new(0x50u);
  v182 = v70;
  LOBYTE(v184) = 40;
  if ( v70 != nullptr )
    v71 = sub_433480(v70);
  else
    v71 = 0;
  LOBYTE(v184) = 4;
  dword_8F8538 = v71;
  v72 = operator new(0xCu);
  v73 = v72;
  v182 = v72;
  LOBYTE(v184) = 41;
  if ( v72 != nullptr )
  {
    unknown_libname_4(v72);
    sub_483C60(v73, 216);
  }
  else
  {
    v73 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F853C = v73;
  v74 = operator new(0x3Cu);
  v182 = v74;
  LOBYTE(v184) = 42;
  if ( v74 != nullptr )
    v75 = sub_439220(v74);
  else
    v75 = 0;
  LOBYTE(v184) = 4;
  dword_8F8540 = v75;
  v76 = operator new(0xB0u);
  v77 = v76;
  v182 = v76;
  LOBYTE(v184) = 43;
  if ( v76 != nullptr )
  {
    *v76 = &CNRDConfigFile::`vftable';
    sub_48B700((int)v76);
    sub_48B9C0(v77, "./ARAD.cfg");
  }
  else
  {
    v77 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8544 = (int)v77;
  v78 = operator new(0x12Cu);
  v182 = v78;
  LOBYTE(v184) = 44;
  if ( v78 != nullptr )
    v79 = sub_428F30(v78, (int)"Common/HitEffect/Particle/LargeHitParticle.ptl", 0);
  else
    v79 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8270[0] = (int)v79;
  v80 = operator new(0x12Cu);
  v182 = v80;
  LOBYTE(v184) = 45;
  if ( v80 != nullptr )
    v81 = sub_428F30(v80, (int)"Common/HitEffect/Particle/SmallHitParticle.ptl", 0);
  else
    v81 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8274 = (int)v81;
  v82 = operator new(0x12Cu);
  v182 = v82;
  LOBYTE(v184) = 46;
  if ( v82 != nullptr )
    v83 = sub_428F30(v82, (int)"Common/HitEffect/Particle/FireHitParticle.ptl", 0);
  else
    v83 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8278 = (int)v83;
  v84 = operator new(0x12Cu);
  v182 = v84;
  LOBYTE(v184) = 47;
  if ( v84 != nullptr )
    v85 = sub_428F30(v84, (int)"Common/HitEffect/Particle/FireHitParticleLight.ptl", 0);
  else
    v85 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F827C = (int)v85;
  v86 = operator new(0x12Cu);
  v182 = v86;
  LOBYTE(v184) = 48;
  if ( v86 != nullptr )
    v87 = sub_428F30(v86, (int)"Common/HitEffect/Particle/WaterHitParticle.ptl", 0);
  else
    v87 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8280 = (int)v87;
  v88 = operator new(0x12Cu);
  v182 = v88;
  LOBYTE(v184) = 49;
  if ( v88 != nullptr )
    v89 = sub_428F30(v88, (int)"Common/HitEffect/Particle/WaterHitParticleLight.ptl", 0);
  else
    v89 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8284 = (int)v89;
  v90 = operator new(0x12Cu);
  v182 = v90;
  LOBYTE(v184) = 50;
  if ( v90 != nullptr )
    v91 = sub_428F30(v90, (int)"Common/HitEffect/Particle/DarkHitParticleLight.ptl", 0);
  else
    v91 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8288 = (int)v91;
  v92 = operator new(0x12Cu);
  v182 = v92;
  LOBYTE(v184) = 51;
  if ( v92 != nullptr )
    v93 = sub_428F30(v92, (int)"Common/HitEffect/Particle/LightHitParticleLight.ptl", 0);
  else
    v93 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F828C = (int)v93;
  v94 = operator new(0x12Cu);
  v182 = v94;
  LOBYTE(v184) = 52;
  if ( v94 != nullptr )
    v95 = sub_428F30(v94, (int)"Common/HitEffect/Particle/MagicHitParticle1.ptl", 0);
  else
    v95 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8290 = (int)v95;
  v96 = operator new(0x12Cu);
  v182 = v96;
  LOBYTE(v184) = 53;
  if ( v96 != nullptr )
    v97 = sub_428F30(v96, (int)"Common/HitEffect/Particle/MagicHitParticle2.ptl", 0);
  else
    v97 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8294 = (int)v97;
  v98 = operator new(0x12Cu);
  v182 = v98;
  LOBYTE(v184) = 54;
  if ( v98 != nullptr )
    v99 = sub_428F30(v98, (int)"Common/CommonEffect/Particle/DustDownLarge.ptl", 0);
  else
    v99 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8298 = (int)v99;
  v100 = operator new(0x12Cu);
  v182 = v100;
  LOBYTE(v184) = 55;
  if ( v100 != nullptr )
    v101 = sub_428F30(v100, (int)"Common/CommonEffect/Particle/DustDownSmall.ptl", 0);
  else
    v101 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F829C = (int)v101;
  v102 = operator new(0x12Cu);
  v182 = v102;
  LOBYTE(v184) = 56;
  if ( v102 != nullptr )
    v103 = sub_428F30(v102, (int)"Common/CommonEffect/Particle/DustMove.ptl", 0);
  else
    v103 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A0 = (int)v103;
  v104 = operator new(0x12Cu);
  v182 = v104;
  LOBYTE(v184) = 57;
  if ( v104 != nullptr )
    v105 = sub_428F30(v104, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticleSmoke.ptl", 0);
  else
    v105 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A4 = (int)v105;
  v106 = operator new(0x12Cu);
  v182 = v106;
  LOBYTE(v184) = 58;
  if ( v106 != nullptr )
    v107 = sub_428F30(v106, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticle.ptl", 0);
  else
    v107 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A8 = (int)v107;
  v108 = operator new(0x12Cu);
  v182 = v108;
  LOBYTE(v184) = 59;
  if ( v108 != nullptr )
    v109 = sub_428F30(v108, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticleStar.ptl", 0);
  else
    v109 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82AC = (int)v109;
  v110 = operator new(0x12Cu);
  v182 = v110;
  LOBYTE(v184) = 60;
  if ( v110 != nullptr )
    v111 = sub_428F30(v110, (int)"PassiveObject/Common/Particle/ThunderBoltParticle.ptl", 0);
  else
    v111 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B0 = (int)v111;
  v112 = operator new(0x12Cu);
  v182 = v112;
  LOBYTE(v184) = 61;
  if ( v112 != nullptr )
    v113 = sub_428F30(v112, (int)"Common/CommonEffect/Particle/HealParticle.ptl", 0);
  else
    v113 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B4 = (int)v113;
  v114 = operator new(0x12Cu);
  v182 = v114;
  LOBYTE(v184) = 62;
  if ( v114 != nullptr )
    v115 = sub_428F30(v114, (int)"Common/CommonEffect/Particle/FieldItemParticle.ptl", 0);
  else
    v115 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B8 = (int)v115;
  v116 = operator new(0x12Cu);
  v182 = v116;
  LOBYTE(v184) = 63;
  if ( v116 != nullptr )
    v117 = sub_428F30(v116, (int)"Common/ActiveStatus/Particle/FreezeParticle.ptl", 0);
  else
    v117 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82BC = (int)v117;
  v118 = operator new(0x12Cu);
  v182 = v118;
  LOBYTE(v184) = 64;
  if ( v118 != nullptr )
    v119 = sub_428F30(v118, (int)"PassiveObject/Character/Fighter/Particle/ThrowSandParticle1.ptl", 0);
  else
    v119 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C0 = (int)v119;
  v120 = operator new(0x12Cu);
  v182 = v120;
  LOBYTE(v184) = 65;
  if ( v120 != nullptr )
    v121 = sub_428F30(v120, (int)"PassiveObject/Character/Fighter/Particle/ThrowSandParticle2.ptl", 0);
  else
    v121 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C4 = (int)v121;
  v122 = operator new(0x12Cu);
  v182 = v122;
  LOBYTE(v184) = 66;
  if ( v122 != nullptr )
    v123 = sub_428F30(v122, (int)"PassiveObject/Common/Particle/ShootingStarPath.ptl", 0);
  else
    v123 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C8 = (int)v123;
  v124 = operator new(0x12Cu);
  v182 = v124;
  LOBYTE(v184) = 67;
  if ( v124 != nullptr )
    v125 = sub_428F30(v124, (int)"Monster/Common/Particle/MonsterDieBlood.ptl", 0);
  else
    v125 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82CC = (int)v125;
  v126 = operator new(0x12Cu);
  v182 = v126;
  LOBYTE(v184) = 68;
  if ( v126 != nullptr )
    v127 = sub_428F30(v126, (int)"Monster/Common/Particle/MonsterDieBloodYoung.ptl", 0);
  else
    v127 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D0 = (int)v127;
  v128 = operator new(0x12Cu);
  v182 = v128;
  LOBYTE(v184) = 69;
  if ( v128 != nullptr )
    v129 = sub_428F30(v128, (int)"Monster/Common/Particle/MonsterDiePiece.ptl", 0);
  else
    v129 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D4 = (int)v129;
  v130 = operator new(0x12Cu);
  v182 = v130;
  LOBYTE(v184) = 70;
  if ( v130 != nullptr )
    v131 = sub_428F30(v130, (int)"Monster/Common/Particle/MonsterDiePieceYoung.ptl", 0);
  else
    v131 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D8 = (int)v131;
  v132 = operator new(0x12Cu);
  v182 = v132;
  LOBYTE(v184) = 71;
  if ( v132 != nullptr )
    v133 = sub_428F30(v132, (int)"Monster/Common/Particle/MonsterDiePieceVeryYoung.ptl", 0);
  else
    v133 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82DC = (int)v133;
  v134 = operator new(0x12Cu);
  v182 = v134;
  LOBYTE(v184) = 72;
  if ( v134 != nullptr )
    v135 = sub_428F30(v134, (int)"Monster/Common/Particle/MonsterDieFlashYoung.ptl", 0);
  else
    v135 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E0 = (int)v135;
  v136 = operator new(0x12Cu);
  v182 = v136;
  LOBYTE(v184) = 73;
  if ( v136 != nullptr )
    v137 = sub_428F30(v136, (int)"Common/CommonEffect/Particle/BuffStartParticle.ptl", 0);
  else
    v137 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E4 = (int)v137;
  v138 = operator new(0x12Cu);
  v182 = v138;
  LOBYTE(v184) = 74;
  if ( v138 != nullptr )
    v139 = sub_428F30(v138, (int)"Common/CommonEffect/Particle/SwampSpoutDownLarge.ptl", 0);
  else
    v139 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E8 = (int)v139;
  v140 = operator new(0x12Cu);
  v182 = v140;
  LOBYTE(v184) = 75;
  if ( v140 != nullptr )
    v141 = sub_428F30(v140, (int)"Common/CommonEffect/Particle/SwampSpoutDownSmall.ptl", 0);
  else
    v141 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82EC = (int)v141;
  v142 = operator new(0x12Cu);
  v182 = v142;
  LOBYTE(v184) = 76;
  if ( v142 != nullptr )
    v143 = sub_428F30(v142, (int)"Common/CommonEffect/Particle/SwampSpoutMove.ptl", 0);
  else
    v143 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F0 = (int)v143;
  v144 = operator new(0x12Cu);
  v182 = v144;
  LOBYTE(v184) = 77;
  if ( v144 != nullptr )
    v145 = sub_428F30(v144, (int)"Common/CommonEffect/Particle/PoisonSpoutDownLarge.ptl", 0);
  else
    v145 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F4 = (int)v145;
  v146 = operator new(0x12Cu);
  v182 = v146;
  LOBYTE(v184) = 78;
  if ( v146 != nullptr )
    v147 = sub_428F30(v146, (int)"Common/CommonEffect/Particle/PoisonSpoutDownSmall.ptl", 0);
  else
    v147 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F8 = (int)v147;
  v148 = operator new(0x12Cu);
  v182 = v148;
  LOBYTE(v184) = 79;
  if ( v148 != nullptr )
    v149 = sub_428F30(v148, (int)"Common/CommonEffect/Particle/PoisonSpoutMove.ptl", 0);
  else
    v149 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82FC = (int)v149;
  v150 = operator new(0x12Cu);
  v182 = v150;
  LOBYTE(v184) = 80;
  if ( v150 != nullptr )
    v151 = sub_428F30(v150, (int)"Common/CommonEffect/Particle/WaterBubbleLarge.ptl", 0);
  else
    v151 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8300 = (int)v151;
  v152 = operator new(0x12Cu);
  v182 = v152;
  LOBYTE(v184) = 81;
  if ( v152 != nullptr )
    v153 = sub_428F30(v152, (int)"Common/CommonEffect/Particle/WaterBubbleSmall.ptl", 0);
  else
    v153 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8304 = (int)v153;
  v154 = operator new(0x12Cu);
  v182 = v154;
  LOBYTE(v184) = 82;
  if ( v154 != nullptr )
    v155 = sub_428F30(v154, (int)"Common/CommonEffect/Particle/WaterBubbleMove.ptl", 0);
  else
    v155 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8308 = (int)v155;
  v156 = operator new(0x12Cu);
  v182 = v156;
  LOBYTE(v184) = 83;
  if ( v156 != nullptr )
    v157 = sub_428F30(v156, (int)"Character/Gunner/Effect/Particle/AutomaticShell.ptl", 0);
  else
    v157 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F830C = (int)v157;
  v158 = operator new(0x12Cu);
  v182 = v158;
  LOBYTE(v184) = 84;
  if ( v158 != nullptr )
    v159 = sub_428F30(v158, (int)"Common/CommonEffect/Particle/MAGMASpoutDownLarge.ptl", 0);
  else
    v159 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8310 = (int)v159;
  v160 = operator new(0x12Cu);
  v182 = v160;
  LOBYTE(v184) = 85;
  if ( v160 != nullptr )
    v161 = sub_428F30(v160, (int)"Common/CommonEffect/Particle/MAGMASpoutDownSmall.ptl", 0);
  else
    v161 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8314 = (int)v161;
  v162 = operator new(0x12Cu);
  v182 = v162;
  LOBYTE(v184) = 86;
  if ( v162 != nullptr )
    v163 = sub_428F30(v162, (int)"Common/CommonEffect/Particle/MAGMASpoutMove.ptl", 0);
  else
    v163 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8318 = (int)v163;
  sub_4F3960();
  sub_4302E0();
  sub_4B5B80();
  v181 = 0;
  v182 = (void *)2;
  (*(void (/*thiscall*/ **)(int *, uint32_t, int *))(dword_8F8558 + 16))(&dword_8F8558, 0, &v181);
  v181 = 0;
  v182 = (void *)3;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 1, &v181);
  v181 = 0;
  v182 = nullptr;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 2, &v181);
  v181 = 0;
  v182 = (void *)1;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 3, &v181);
  v181 = 0;
  v182 = (void *)80;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 4, &v181);
  v181 = 0;
  v182 = (void *)78;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 5, &v181);
  v181 = 0;
  v182 = (void *)57;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 6, &v181);
  v181 = 0;
  v182 = (void *)76;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 7, &v181);
  v181 = 0;
  v182 = (void *)13;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 8, &v181);
  if ( dword_79C0B8 != 0 )
  {
    *(uint32_t *)(dword_79C0B8 + 2064) = 80;
    *(uint32_t *)(dword_79C0B8 + 2068) = 78;
    *(uint32_t *)(dword_79C0B8 + 2072) = 57;
    *(uint32_t *)(dword_79C0B8 + 2076) = 55;
    *(uint32_t *)(dword_79C0B8 + 2080) = 73;
    *(uint32_t *)(dword_79C0B8 + 2084) = 58;
    *(uint32_t *)(dword_79C0B8 + 2088) = 60;
    *(uint32_t *)(dword_79C0B8 + 2092) = 61;
  }
  for ( i = 0; i < 6; ++i )
  {
    dword_77FCA8[2 * i] = 0;
    dword_77FCAC[2 * i] = i + 46;
  }
  v165 = &unk_77FCD8;
  do
  {
    *v165 = 0;
    v165 += 2;
  }
  while ( (int)v165 < (int)byte_77FD08 );
  dword_77FCDC = 55;
  dword_77FCE4 = 73;
  dword_77FCEC = 58;
  dword_77FCF4 = 60;
  dword_77FCFC = 61;
  dword_77FD04 = 62;
  v166 = byte_77FD08;
  do
  {
    *(uint32_t *)v166 = 0;
    v166 += 8;
  }
  while ( (int)v166 < (int)dword_77FD48 );
  dword_77FD0C = 67;
  dword_77FD14 = 65;
  dword_77FD1C = 74;
  dword_77FD24 = 63;
  dword_77FD2C = 69;
  dword_77FD34 = 71;
  dword_77FD3C = 75;
  dword_77FD44 = 68;
  for ( j = 0; j < 4; ++j )
  {
    dword_77FD48[2 * j] = 0;
    dword_77FD4C[2 * j] = j + 81;
  }
  sub_439050(&unk_9A0330);
  sub_4ED3F0((int)&unk_8F85C4, (int)&unk_9A0340);
  dword_8F85D4 = dword_9A0350;
  dword_8F85D8 = dword_9A0354;
  byte_8F85DC = byte_9A0358;
  v179[0] = 100;
  v179[1] = 2;
  v180 = 0;
  sub_4F49C0(&unk_8F86D0, v179);
  InitializeCriticalSection(&stru_8F8258);
  EnterCriticalSection(&stru_8F8258);
  LOBYTE(v184) = 1;
  sub_439810(v183);
  v168 = (void **)Block;
  v184 = -1;
  if ( Block != nullptr )
  {
    v169 = v177;
    if ( Block != v177 )
    {
      do
        sub_41B010(v168++);
      while ( v168 != v169 );
      v168 = (void **)Block;
    }
    j__free(v168);
  }
}


// ------------------------------------------------------------
// 0x43B4C0 sub_43B4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B4C0(void *this, char a2)
{
  return sub_423290((int)this, (int)&a2, 4);
}



// ------------------------------------------------------------
// 0x43B4E0 sub_43B4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B4E0(void *this, char a2, int a3)
{
  return sub_423290((int)this, (int)&a2, 8);
}



// ------------------------------------------------------------
// 0x43B500 sub_43B500
// ------------------------------------------------------------
bool /*thiscall*/ sub_43B500(int this)
{
  return *(uint8_t *)(this + 17) != 0 && dword_79BE34 == *(uint32_t *)(this + 12);
}



// ------------------------------------------------------------
// 0x43B520 sub_43B520
// ------------------------------------------------------------
bool /*thiscall*/ sub_43B520(int this)
{
  return *(uint8_t *)(this + 17) != 0 && dword_79BE38 == *(uint32_t *)(this + 12);
}



// ------------------------------------------------------------
// 0x43B540 sub_43B540
// ------------------------------------------------------------
char /*thiscall*/ sub_43B540(uint32_t *this)
{
  int v1; // eax
  uint32_t *i; // ecx

  v1 = 0;
  for ( i = this + 4; *i != 0; ++i )
  {
    if ( ++v1 >= 4 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x43B560 sub_43B560
// ------------------------------------------------------------
int /*thiscall*/ sub_43B560(void *this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  int result; // eax

  result = a4;
  if ( a4 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, void *, int, int, int, int, int, int))(*(uint32_t *)a4 + 128))(
             a4,
             a2,
             a3,
             this,
             a5,
             a6,
             a7,
             a8,
             a9,
             a10);
  return result;
}



// ------------------------------------------------------------
// 0x43B5A0 sub_43B5A0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5A0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this));
}



// ------------------------------------------------------------
// 0x43B5C0 sub_43B5C0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5C0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 892));
}



// ------------------------------------------------------------
// 0x43B5E0 sub_43B5E0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5E0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 920));
}



// ------------------------------------------------------------
// 0x43B600 sub_43B600
// ------------------------------------------------------------
bool /*cdecl*/ sub_43B600(const char *a1, unsigned int a2, char *SubStr, char a4)
{
  if ( strlen(a1) < a2 )
    return false;
  if ( a4 != 0 )
    return strcmp(&a1[a2], SubStr) == 0;
  return &a1[a2] == strstr(&a1[a2], SubStr);
}



// ------------------------------------------------------------
// 0x43B6A0 sub_43B6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B6A0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  uint32_t *v6; // edi
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  bool v9; // zf
  void (/*thiscall*/ ****v10)(uint32_t, int); // edi
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v18)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v19)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v20)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v21)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v23)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v24)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v25)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v26)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v27)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v28)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v29)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-4h]
  int v31; // [esp+8h] [ebp-4h]

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 3) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(this + 6) = 0;
  v6 = this + 7;
  for ( i = 4; i != 0; --i )
  {
    v7 = (void (/*thiscall*/ ***)(uint32_t, int))v6[12];
    if ( v7 != nullptr )
      (**v7)(v7, 1);
    v8 = (void (/*thiscall*/ ***)(uint32_t, int))*v6;
    v9 = *v6 == 0;
    v6[12] = 0;
    if ( !v9 )
      (**v8)(v8, 1);
    *v6++ = 0;
  }
  v10 = (void (/*thiscall*/ ****)(uint32_t, int))(this + 15);
  v31 = 2;
  do
  {
    v11 = *(v10 - 4);
    if ( v11 != nullptr )
      (**v11)(v11, 1);
    v12 = *v10;
    v9 = *v10 == nullptr;
    *(v10 - 4) = nullptr;
    if ( !v9 )
      (**v12)(v12, 1);
    *v10++ = nullptr;
    result = v31 - 1;
    v31 = result;
  }
  while ( result != 0 );
  v14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v14 != nullptr )
    result = (**v14)(v14, 1);
  v15 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v15 != nullptr )
    result = (**v15)(v15, 1);
  v16 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  *(this + 14) = 0;
  if ( v16 != nullptr )
    result = (**v16)(v16, 1);
  v17 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  *(this + 17) = 0;
  if ( v17 != nullptr )
    result = (**v17)(v17, 1);
  v18 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);
  *(this + 18) = 0;
  if ( v18 != nullptr )
    result = (**v18)(v18, 1);
  v19 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 24);
  *(this + 23) = 0;
  if ( v19 != nullptr )
    result = (**v19)(v19, 1);
  v20 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 30);
  *(this + 24) = 0;
  if ( v20 != nullptr )
    result = (**v20)(v20, 1);
  v21 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;
  if ( v21 != nullptr )
    result = (**v21)(v21, 1);
  v22 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  *(this + 31) = 0;
  if ( v22 != nullptr )
    result = (**v22)(v22, 1);
  v23 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 33);
  *(this + 32) = 0;
  if ( v23 != nullptr )
    result = (**v23)(v23, 1);
  v24 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  *(this + 33) = 0;
  if ( v24 != nullptr )
    result = (**v24)(v24, 1);
  v25 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  *(this + 34) = 0;
  if ( v25 != nullptr )
    result = (**v25)(v25, 1);
  v26 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 29);
  *(this + 28) = 0;
  if ( v26 != nullptr )
    result = (**v26)(v26, 1);
  v27 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  *(this + 29) = 0;
  if ( v27 != nullptr )
    result = (**v27)(v27, 1);
  v28 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;
  if ( v28 != nullptr )
    result = (**v28)(v28, 1);
  v29 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  *(this + 26) = 0;
  if ( v29 != nullptr )
    result = (**v29)(v29, 1);
  *(this + 27) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x43B880 sub_43B880
// ------------------------------------------------------------
void /*thiscall*/ sub_43B880(uint32_t *this, int a2)
{
  if ( a2 == 1 )
  {
    if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0
      || *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0 )
    {
      return;
    }
LABEL_8:
    *(this + 72) = a2;
    return;
  }
  if ( a2 != 2
    || sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
    && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 120) != 0 )
  {
    goto LABEL_8;
  }
}



// ------------------------------------------------------------
// 0x43B920 sub_43B920
// ------------------------------------------------------------
char /*thiscall*/ sub_43B920(int this, char a2)
{
  char result; // al

  if ( *(uint8_t *)(this + 256) != a2 )
  {
    if ( a2 != 0 )
    {
      result = *(uint8_t *)(*(uint32_t *)(this + 136) + 17);
      if ( result == 0 )
        return result;
      sub_69BCC0();
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 136) + 12);
      dword_79BE54 = dword_79BE4C;
      *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475;
      *(uint8_t *)(this + 1794) = 1;
    }
    else
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = a2;
    *(uint8_t *)(this + 273) = 0;
    *(uint8_t *)(this + 274) = 0;
    result = sub_698F90(this + 260, 100, 0);
    *(uint8_t *)(this + 256) = a2;
    if ( a2 == 0 )
      return CNCommandChecker__vmt40(0, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x43B9D0 sub_43B9D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_43B9D0(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v4; // edx
  uint32_t *v5; // ecx

  result = (uint32_t *)sub_69C340(a2);
  v4 = 20 - a2;
  if ( 20 - a2 > 0 )
  {
    v5 = this + 44;
    result = this + a2 + 44;
    do
    {
      *v5++ = *result++;
      --v4;
    }
    while ( v4 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BA20 sub_43BA20
// ------------------------------------------------------------
int /*thiscall*/ sub_43BA20(int this, int a2)
{
  int v3; // ebx
  int v4; // eax
  BOOL v5; // ebx
  int v6; // eax

  *(uint32_t *)(this + 144) = a2;
  *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = a2 == 0;
  *(uint8_t *)(*(uint32_t *)(this + 28) + 16) = a2 != 0;
  *(uint8_t *)(*(uint32_t *)(this + 80) + 16) = a2 == 1;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = a2 != 1;
  *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = a2 == 2;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = a2 != 2;
  *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = a2 == 3;
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = a2 != 3;
  v3 = sub_69C3A0(*(uint32_t *)(this + 4 * a2 + 76));
  v4 = sub_69C500(*(uint32_t *)(this + 4 * a2 + 76)) - v3;
  v5 = v4 <= 0;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), v5 ? 0 : v4);
    v6 = sub_69C6A0(*(uint32_t *)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v5 ? 0 : v4);
    v6 = sub_69C6A0(*(uint32_t *)(this + 56));
  }
  return sub_69C680(v6);
}



// ------------------------------------------------------------
// 0x43BB10 sub_43BB10
// ------------------------------------------------------------
int /*thiscall*/ sub_43BB10(uint32_t *this, int a2, char a3)
{
  *(uint8_t *)(*(this + a2 + 7) + 17) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x43BB30 sub_43BB30
// ------------------------------------------------------------
int /*thiscall*/ sub_43BB30(int this)
{
  int v2; // esi
  int i; // ebx

  v2 = this + 76;
  for ( i = 4; i != 0; --i )
  {
    sub_69C340(-1);
    v2 += 4;
  }
  if ( *(uint8_t *)(this + 1474) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), 0);
  else
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), 0);
  sub_69C340(-1);
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  return this + 176;
}



// ------------------------------------------------------------
// 0x43BBC0 sub_43BBC0
// ------------------------------------------------------------
int /*thiscall*/ sub_43BBC0(uint8_t *this)
{
  char v1; // bl
  int result; // eax
  int v3; // ecx
  LONG v4; // edx

  v1 = *(this + 1474);
  result = 0;
  v3 = 202;
  while ( 1 )
  {
    v4 = v3 + 192;
    if ( v1 == 0 )
      v4 = v3;
    if ( pt.x >= 9 && pt.x < 42 && pt.y >= v4 && pt.y < v4 + 16 )
      break;
    v3 += 16;
    ++result;
    if ( v3 >= 282 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BC20 sub_43BC20
// ------------------------------------------------------------
int sub_43BC20()
{
  int result; // eax
  LONG v1; // ecx

  result = 0;
  v1 = 322;
  while ( pt.x < 61 || pt.x >= 94 || pt.y < v1 || pt.y >= v1 + 16 )
  {
    v1 += 17;
    ++result;
    if ( v1 >= 390 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BC60 sub_43BC60
// ------------------------------------------------------------
int /*thiscall*/ sub_43BC60(int this, char a2)
{
  int result; // eax
  int v3; // ecx
  bool v4; // zf
  int v5; // ecx

  result = 0;
  if ( a2 != 0 || *(uint8_t *)(*(uint32_t *)(this + 16) + 16) != 0 )
  {
    v3 = *(uint32_t *)(this + 12);
    *(uint32_t *)(v3 + 28) = 0;
    *(uint32_t *)(v3 + 32) = 0;
  }
  else
  {
    v4 = *(uint8_t *)(this + 1474) == 0;
    v5 = *(uint32_t *)(this + 12);
    *(uint32_t *)(v5 + 28) = 317;
    if ( v4 )
      *(uint32_t *)(v5 + 32) = 162;
    else
      *(uint32_t *)(v5 + 32) = 354;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BCB0 sub_43BCB0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_43BCB0(int this)
{
  int v1; // esi
  BOOL result; // eax

  result = false;
  if ( *(uint8_t *)(this + 17) != 0 )
  {
    v1 = *(uint32_t *)(this + 12);
    if ( dword_79BE3C == v1 || dword_79BE34 == v1 || dword_79BE38 == v1 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BCF0 sub_43BCF0
// ------------------------------------------------------------
bool /*thiscall*/ sub_43BCF0(void *this, const char *a2)
{
  return strcmp((const char *)sub_41ACF0(this), a2) == 0;
}



// ------------------------------------------------------------
// 0x43BD50 sub_43BD50
// ------------------------------------------------------------
char /*thiscall*/ sub_43BD50(int this, int a2, int a3, int a4, int a5, int a6)
{
  int v8; // ebx
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  bool v14; // zf
  int v15; // eax
  int v16; // ecx
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // ecx
  int v21; // eax
  bool v23; // [esp+17h] [ebp+Bh]
  int v24; // [esp+1Ch] [ebp+10h]

  if ( a2 == 4 )
  {
    v8 = sub_69C500(*(uint32_t *)(this + 96));
    sub_69C440(a4);
    sub_69C4A0(a5);
    sub_69C360(a3, a6);
    v9 = sub_69C500(*(uint32_t *)(this + 96));
    v10 = v9;
    if ( v9 > 8 )
      sub_43B9D0((uint32_t *)this, v9 - 8);
    v11 = v10 - v8;
    if ( v10 - v8 > 0 )
    {
      v12 = 43;
      v24 = v11;
      do
      {
        v13 = sub_699000(this + 148);
        *(uint32_t *)(this + 4 * (v12 + sub_69C500(*(uint32_t *)(this + 96)))) = v13;
        --v12;
        LOBYTE(v11) = --v24;
      }
      while ( v24 != 0 );
    }
  }
  else
  {
    v14 = *(uint32_t *)(this + 144) == a2;
    v23 = false;
    if ( v14 )
    {
      if ( *(uint8_t *)(this + 1474) != 0 )
      {
        v15 = sub_69C6A0(*(uint32_t *)(this + 72));
        v16 = *(uint32_t *)(this + 72);
      }
      else
      {
        v15 = sub_69C6A0(*(uint32_t *)(this + 56));
        v16 = *(uint32_t *)(this + 56);
      }
      v23 = sub_69C690(v16) == v15;
    }
    sub_69C440(a4);
    sub_69C4A0(a5);
    LOBYTE(v11) = sub_69C360(a3, a6);
    if ( *(uint32_t *)(this + 144) == a2 )
    {
      v17 = *(uint8_t *)(this + 1474) != 0 ? 20 : 8;
      v18 = sub_69C500(*(uint32_t *)(this + 4 * a2 + 76)) - v17;
      v19 = 0;
      v20 = *(uint8_t *)(this + 1474) != 0 ? *(uint32_t *)(this + 72) : *(uint32_t *)(this + 56);
      LOBYTE(v19) = v18 <= 0;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 32))(v20, v18 & (v19 - 1));
      LOBYTE(v11) = v23;
      if ( v23 )
      {
        if ( *(uint8_t *)(this + 1474) != 0 )
          v21 = sub_69C6A0(*(uint32_t *)(this + 72));
        else
          v21 = sub_69C6A0(*(uint32_t *)(this + 56));
        LOBYTE(v11) = sub_69C680(v21);
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// 0x43BEE0 sub_43BEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_43BEE0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v5; // eax

  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v5 == 3 || v5 == 4 || v5 == 6 )
    return sub_43BD50(4, a2, a3, a4, a5);
  else
    return sub_43BD50(*(this + 36), a2, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x43BF40 sub_43BF40
// ------------------------------------------------------------
int /*thiscall*/ sub_43BF40(int *this, const char *a2)
{
  int v3; // esi
  char *v4; // eax
  int v5; // eax
  char Buffer[256]; // [esp+Ch] [ebp-104h] BYREF
  int v8; // [esp+10Ch] [ebp-4h]

  v8 = dword_796E50;
  v3 = sub_429870((int **)dword_8F8500, a2);
  if ( v3 == 0 )
  {
    v4 = sub_422E70(328);
    sprintf(Buffer, v4, a2);
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 3 || v5 == 4 || v5 == 6 )
      sub_43BD50((int)this, 4, (int)Buffer, -6567706, 0, -1);
    else
      sub_43BD50((int)this, *(this + 36), (int)Buffer, -6567706, 0, -1);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x43BFF0 sub_43BFF0
// ------------------------------------------------------------
char /*stdcall*/ sub_43BFF0(int a1)
{
  int v1; // ecx
  int v3; // ebx
  int v4; // edi

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v1 == 4 )
    return 1;
  if ( v1 == 6 )
  {
    v3 = *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76) + 1);
    v4 = *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));
    if ( sub_41A5E0(a1 + 53) >= v4 && sub_41A5E0(a1 + 53) <= v3 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x43C060 sub_43C060
// ------------------------------------------------------------
int /*thiscall*/ sub_43C060(int this, int a2, int a3)
{
  sub_426BD0((uint8_t *)this);
  *(uint32_t *)this = &vftbl_nengine__CNEdit;
  *(uint8_t *)(this + 136) = 0;
  *(uint32_t *)(this + 132) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 140) = 0;
  *(uint8_t *)(this + 144) = 1;
  *(uint8_t *)(this + 146) = 0;
  *(uint8_t *)(this + 145) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 164) = 0;
  *(uint32_t *)(this + 160) = &vftbl_nengine__CNString;
  sub_402A50();
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 180) = &vftbl_nengine__CNString;
  sub_402A50();
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 200) = &vftbl_nengine__CNString;
  sub_402A50();
  sub_69AB50(this);
  nengine__CNEdit__vmt20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x43C150 nengine__CNEdit__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNEdit__vmt0(void *Block, char a2)
{
  sub_43C180();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C180 sub_43C180
// ------------------------------------------------------------
int /*thiscall*/ sub_43C180(int this)
{
  *(uint32_t *)this = &vftbl_nengine__CNEdit;
  nengine__CNEdit__vmt8();
  *(uint32_t *)(this + 200) = &vftbl_nengine__CNString;
  sub_402A60(this + 200);
  *(uint32_t *)(this + 200) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 180) = &vftbl_nengine__CNString;
  sub_402A60(this + 180);
  *(uint32_t *)(this + 180) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 160) = &vftbl_nengine__CNString;
  sub_402A60(this + 160);
  *(uint32_t *)(this + 160) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 164) = 0;
  *(uint32_t *)(this + 132) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 136) = 0;
  return sub_426C90((void **)this);
}



// ------------------------------------------------------------
// 0x43C250 sub_43C250
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C250(uint8_t *this, int a2, int a3)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNFrame;
  sub_69C6B0(this);
  nengine__CNFrame__vmt20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x43C2B0 nengine__CNFrame__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNFrame__vmt0(void *Block, char a2)
{
  sub_43C2E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C2E0 sub_43C2E0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C2E0(void **this)
{
  *this = &vftbl_nengine__CNFrame;
  nengine__CNFrame__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C330 sub_43C330
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C330(uint8_t *this, int a2, int a3)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNTextBox;
  sub_69C2D0(this);
  nengine__CNTextBox__vmt20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x43C390 nengine__CNTextBox__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNTextBox__vmt0(void *Block, char a2)
{
  sub_43C3C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C3C0 sub_43C3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C3C0(void **this)
{
  *this = &vftbl_nengine__CNTextBox;
  nengine__CNTextBox__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C410 sub_43C410
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_43C410(uint32_t *this, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
  sub_426BD0(this);
  *this = &vftbl_nengine__CNButton;
  sub_69C780(this);
  nengine__CNButton__vmt20(a2, a3, a4, a5, a6, a7, a8);
  return this;
}



// ------------------------------------------------------------
// 0x43C480 sub_43C480
// ------------------------------------------------------------
void /*thiscall*/ sub_43C480(void **this)
{
  *this = &vftbl_nengine__CNButton;
  nengine__CNButton__vmt8();
  sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C4D0 sub_43C4D0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C4D0(uint8_t *this, int a2, int a3, int a4)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNSlider;
  sub_69CA20(this);
  nengine__CNSlider__vmt20(a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x43C530 sub_43C530
// ------------------------------------------------------------
int /*thiscall*/ sub_43C530(void **this)
{
  *this = &vftbl_nengine__CNSlider;
  nengine__CNSlider__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C580 nengine__CNSlider__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNSlider__vmt0(void **Block, char a2)
{
  sub_43C530(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C5B0 sub_43C5B0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C5B0(void **this)
{
  *this = &vftbl_nengine__CNScroll;
  nengine__CNScroll__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C600 nengine__CNScroll__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNScroll__vmt0(void **Block, char a2)
{
  sub_43C5B0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C630 sub_43C630
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C630(uint8_t *this, int a2, int a3, int a4)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNScroll;
  sub_69C5D0(this);
  *(uint32_t *)this = &vftbl_nengine__CNVScroll;
  sub_69C5D0(this);
  nengine__CNVScroll__vmt24(a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x43C6B0 nengine__CNVSlider__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNVSlider__vmt0(void **Block, char a2)
{
  sub_43C6E0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C6E0 sub_43C6E0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_43C6E0(void **this)
{
  return sub_43C530(this);
}



// ------------------------------------------------------------
// 0x43C6F0 nengine__CNVScroll__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNVScroll__vmt0(void **Block, char a2)
{
  sub_43C720(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C720 sub_43C720
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_43C720(void **this)
{
  return sub_43C5B0(this);
}



// ------------------------------------------------------------
// 0x43C730 sub_43C730
// ------------------------------------------------------------
int /*thiscall*/ sub_43C730(int this)
{
  int v2; // edi
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint8_t *)(this + 256) = 1;
  *(uint32_t *)(this + 288) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(uint8_t *)(this + 1532) = 0;
  *(uint32_t *)(this + 1788) = 3;
  *(uint16_t *)(this + 1792) = -1;
  *(uint8_t *)(this + 1794) = 0;
  *(uint8_t *)(this + 320) = 0;
  v2 = this + 884;
  for ( i = 20; i != 0; --i )
  {
    sub_4015C0((void *)szPassword, 0);
    sub_4015C0((void *)szPassword, 0);
    v2 += 28;
    result = i - 1;
  }
  *(uint8_t *)(this + 1454) = 0;
  *(uint8_t *)(this + 1462) = 0;
  *(uint8_t *)(this + 1466) = 0;
  *(uint8_t *)(this + 1455) = 0;
  *(uint8_t *)(this + 1459) = 0;
  *(uint8_t *)(this + 1467) = 0;
  *(uint8_t *)(this + 1460) = 0;
  *(uint8_t *)(this + 1456) = 0;
  *(uint8_t *)(this + 1464) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 1473) = 0;
  *(uint8_t *)(this + 1475) = 0;
  *(uint8_t *)(this + 1474) = 0;
  *(uint32_t *)(this + 1444) = 0;
  *(uint32_t *)(this + 1448) = 0;
  *(uint8_t *)(this + 1452) = 0;
  *(uint8_t *)(this + 1453) = 1;
  *(uint8_t *)(this + 1457) = 1;
  *(uint8_t *)(this + 1461) = 1;
  *(uint8_t *)(this + 1465) = 1;
  *(uint8_t *)(this + 1469) = 1;
  *(uint8_t *)(this + 1458) = 1;
  *(uint8_t *)(this + 1470) = 1;
  *(uint8_t *)(this + 1463) = 1;
  *(uint8_t *)(this + 1471) = 1;
  *(uint8_t *)(this + 1468) = 1;
  *(uint8_t *)(this + 1472) = 1;
  *(uint32_t *)(this + 4) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x43C960 sub_43C960
// ------------------------------------------------------------
const char */*thiscall*/ sub_43C960(int this, const char *a2, int a3, int a4, char *Src)
{
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  const char *result; // eax
  unsigned int v12; // ebx
  int v13; // eax
  int i; // esi
  int v15; // [esp+1Ch] [ebp+10h]

  if ( (uint16_t)a4 == (uint16_t)word_77F804 )
  {
    if ( *(uint8_t *)(this + 1474) != 0 )
      v6 = sub_69C6A0(*(uint32_t **)(this + 72));
    else
      v6 = sub_69C6A0(*(uint32_t **)(this + 56));
    sub_69C680(v6);
  }
  v7 = a3;
  if ( a3 == 0 )
  {
    v8 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v8 == 3 || v8 == 4 || v8 == 6 )
    {
      sub_43BD50(4, a2, -6567706, 0, -1);
    }
    else
    {
      do
        sub_43BD50(v7++, a2, -6567706, 0, -1);
      while ( v7 <= 4 );
    }
    return (const char *)sub_432EA0("CHAT_MESSAGE", -1, 0, 0);
  }
  v9 = sub_429830(a4);
  v10 = v9;
  if ( v9 != 0 )
  {
    if ( *(uint32_t *)(v9 + 40) < 0x10u )
      result = (const char *)(v9 + 20);
    else
      result = *(const char **)(v9 + 20);
  }
  else
  {
    result = "Someone";
  }
  if ( a3 == 4 )
    result = (const char *)sub_422E70(1850);
  if ( v10 != 0 || a3 == 6 || a3 == 8 || a3 == 4 )
  {
    switch ( a3 )
    {
      case 2:
        v15 = -1190552;
        break;
      case 6:
        v15 = -701185;
        goto LABEL_33;
      case 8:
        result = Src;
        v15 = -16739585;
        break;
      default:
        v15 = -8934503;
        if ( a3 != 1 )
          v15 = -1;
        break;
    }
    Src = (char *)result;
LABEL_33:
    sprintf(byte_8F8768, "%s : %s", Src, a2);
    v12 = strlen(Src) + 3;
    v13 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v13 == 3 || v13 == 4 || v13 == 6 )
    {
      sub_43BD50(4, byte_8F8768, v15, v12, a3);
    }
    else
    {
      for ( i = 0; i < 4; ++i )
      {
        switch ( a3 )
        {
          case 2:
            if ( *(uint8_t *)(i + this + 1457) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, 2);
            break;
          case 6:
            if ( *(uint8_t *)(i + this + 1461) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, 6);
            break;
          case 8:
            if ( *(uint8_t *)(i + this + 1465) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, 8);
            break;
          case 1:
            if ( *(uint8_t *)(i + this + 1469) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, 1);
            break;
          case 3:
            if ( *(uint8_t *)(i + this + 1453) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, 3);
            break;
          case 4:
            off_77F3FC((char *)&byte_6C5718, byte_8F8768);
            sub_43BD50(i, byte_8F8768, v15, v12, 4);
            break;
          default:
            if ( *(uint8_t *)(i + this + 1453) != 0 )
              sub_43BD50(i, byte_8F8768, v15, v12, a3);
            break;
        }
      }
      v7 = a3;
    }
    if ( v7 == 1 )
      sub_4015C0(Src, strlen(Src));
    return (const char *)sub_432EA0("CHAT_MESSAGE", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x43CC10 CNRDChatting__vmt0
// ------------------------------------------------------------
char /*userpurge*/ sub_43CC10@<al>(int a1@<ecx>, char a2@<dil>, int a3)
{
  int v4; // ecx
  LONG y; // eax
  int v6; // edx
  int v7; // ecx
  bool v8; // cc
  int v9; // edx
  int v10; // edx
  bool v11; // cc
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  uint64_t v15; // rax
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  unsigned int v27; // ecx
  int v28; // eax
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  char *v32; // eax
  uint32_t *v33; // eax
  int v34; // eax
  int v35; // eax
  unsigned int v36; // ecx
  int v37; // eax
  char *v38; // eax
  int v39; // eax
  int v40; // edi
  int v41; // eax
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // eax
  signed int i; // edi
  int v47; // eax
  int v48; // eax
  LONG x; // ebx
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // edi
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  LONG v64; // edi
  int v66; // [esp-8h] [ebp-44h]
  int v68; // [esp+8h] [ebp-34h]
  int v69; // [esp+Ch] [ebp-30h]
  int v70; // [esp+Ch] [ebp-30h]
  int v71; // [esp+Ch] [ebp-30h]
  char v72[4]; // [esp+10h] [ebp-2Ch] BYREF
  uint32_t v73[7]; // [esp+14h] [ebp-28h] BYREF
  int v74; // [esp+38h] [ebp-4h]
  int v75; // [esp+44h] [ebp+8h]
  unsigned int v76; // [esp+44h] [ebp+8h]
  int v77; // [esp+44h] [ebp+8h]
  int v78; // [esp+44h] [ebp+8h]
  int v79; // [esp+44h] [ebp+8h]
  LONG v80; // [esp+44h] [ebp+8h]

  v73[6] = dword_796E50;
  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  LOBYTE(y) = a3;
  if ( a3 == *(uint32_t *)(a1 + 12) && v4 != 2 && v4 != 5 )
  {
    if ( *(uint8_t *)(a1 + 1474) == 0 )
    {
      v6 = *(uint32_t *)(a1 + 16);
      LOBYTE(y) = pt.x;
      if ( *(uint8_t *)(v6 + 16) != 0 )
      {
        if ( *(uint8_t *)(a1 + 1473) != 0 )
        {
          if ( pt.x < 2 || (pt.x > 319 || pt.y < 35 || pt.y > 195) && (pt.x > 54 || pt.y < 196 || pt.y > 287) )
          {
            *(uint8_t *)(v6 + 16) = 0;
            LOBYTE(y) = sub_43BC60(0);
            v7 = *(uint32_t *)(a1 + 20);
            *(uint8_t *)(a1 + 1473) = 0;
            *(uint8_t *)(v7 + 16) = 0;
            return y;
          }
        }
        else if ( pt.x < 2 || pt.x > 319 || pt.y < 35 || pt.y > 195 )
        {
          *(uint8_t *)(v6 + 16) = 0;
          LOBYTE(y) = sub_43BC60(0);
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 16) = 0;
          return y;
        }
LABEL_34:
        *(uint8_t *)(*(uint32_t *)(a1 + 20) + 16) = 0;
        return y;
      }
      if ( *(uint8_t *)(a1 + 1473) != 0 )
      {
        if ( pt.x < 2 )
          goto LABEL_34;
        if ( pt.x <= 319 && pt.y >= 35 && pt.y <= 195 )
        {
LABEL_33:
          *(uint8_t *)(v6 + 16) = 1;
          y = *(uint32_t *)(a1 + 12);
          *(uint32_t *)(y + 28) = 0;
          *(uint32_t *)(y + 32) = 0;
          goto LABEL_34;
        }
        if ( pt.x > 54 || pt.y < 196 )
          goto LABEL_34;
        v8 = pt.y <= 287;
      }
      else
      {
        if ( pt.x < 2 || pt.x > 319 || pt.y < 35 )
          goto LABEL_34;
        v8 = pt.y <= 195;
      }
      if ( !v8 )
        goto LABEL_34;
      goto LABEL_33;
    }
    v9 = *(uint32_t *)(a1 + 20);
    LOBYTE(y) = pt.x;
    if ( *(uint8_t *)(v9 + 16) != 0 )
    {
      if ( *(uint8_t *)(a1 + 1473) != 0 )
      {
        if ( pt.x < 2 || (pt.x > 319 || pt.y < 35 || pt.y > 387) && (pt.x > 54 || pt.y < 388 || pt.y > 479) )
        {
          *(uint8_t *)(v9 + 16) = 0;
          LOBYTE(y) = sub_43BC60(0);
          v10 = *(uint32_t *)(a1 + 16);
          *(uint8_t *)(a1 + 1473) = 0;
          *(uint8_t *)(v10 + 16) = 0;
          return y;
        }
      }
      else if ( pt.x < 2 || pt.x > 319 || pt.y < 35 || pt.y > 387 )
      {
        *(uint8_t *)(v9 + 16) = 0;
        LOBYTE(y) = sub_43BC60(0);
        *(uint8_t *)(*(uint32_t *)(a1 + 16) + 16) = 0;
        return y;
      }
LABEL_64:
      *(uint8_t *)(*(uint32_t *)(a1 + 16) + 16) = 0;
      return y;
    }
    if ( *(uint8_t *)(a1 + 1473) != 0 )
    {
      if ( pt.x < 2 )
        goto LABEL_64;
      if ( pt.x <= 319 && pt.y >= 35 && pt.y <= 387 )
      {
LABEL_63:
        *(uint8_t *)(v9 + 16) = 1;
        y = *(uint32_t *)(a1 + 12);
        *(uint32_t *)(y + 28) = 0;
        *(uint32_t *)(y + 32) = 0;
        goto LABEL_64;
      }
      if ( pt.x > 54 || pt.y < 388 )
        goto LABEL_64;
      v11 = pt.y <= 479;
    }
    else
    {
      if ( pt.x < 2 || pt.x > 319 || pt.y < 35 )
        goto LABEL_64;
      v11 = pt.y <= 387;
    }
    if ( !v11 )
      goto LABEL_64;
    goto LABEL_63;
  }
  v12 = *(uint32_t *)(a1 + 16);
  if ( a3 != v12 && a3 != *(uint32_t *)(a1 + 20) )
  {
    if ( a3 != *(uint32_t *)(a1 + 120) )
      return y;
    v13 = *(uint32_t *)(a1 + 284);
    v14 = sub_699000(a1 + 260);
    v15 = (uint64_t)sub_4049C0(0.0, 255.0, v14, v13);
    if ( *(uint8_t *)(a1 + 256) == 0 )
      LODWORD(v15) = 255 - v15;
    if ( (uint32_t)v15 == 0 )
      goto LABEL_100;
    switch ( *(uint32_t *)(a1 + 288) )
    {
      case 0:
        *(uint32_t *)(*(uint32_t *)(a1 + 136) + 128) = -1;
        break;
      case 1:
        *(uint32_t *)(*(uint32_t *)(a1 + 136) + 128) = -1190552;
        break;
      case 2:
        *(uint32_t *)(*(uint32_t *)(a1 + 136) + 128) = -701185;
        break;
      case 3:
        *(uint32_t *)(*(uint32_t *)(a1 + 136) + 128) = -16739585;
        break;
      default:
        break;
    }
    v16 = *(uint32_t *)(a1 + 128);
    v17 = (uint8_t)v15 << 24;
    v69 = *(uint32_t *)(v16 + 20);
    v75 = *(uint32_t *)(v16 + 24);
    v18 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x23u);
    sub_43B560(v69, v75, v18, 1065353216, 1065353216, 0, v17 | 0xFFFFFF, 1333788672, 1333788672);
    v76 = 2 * *(uint32_t *)(a1 + 288) + 36;
    if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 132)) != 0 )
      ++v76;
    v19 = *(uint32_t *)(a1 + 132);
    v70 = *(uint32_t *)(v19 + 24);
    v68 = *(uint32_t *)(v19 + 20);
    v20 = sub_418DD0(*(uint32_t **)(a1 + 140), v76);
    sub_43B560(v68, v70, v20, 1065353216, 1065353216, 0, v17 | 0xFFFFFF, 1333788672, 1333788672);
    if ( (uint8_t)sub_69AC60(*(uint32_t *)(a1 + 136)) != 0 )
    {
      v21 = *(uint32_t *)(a1 + 132);
      v22 = *(uint32_t *)(v21 + 24);
      v77 = *(uint32_t *)(v21 + 20);
      v23 = sub_69AC70(*(uint32_t *)(a1 + 136));
      sub_464740(v77 + 15, v22 - 150, v23 + 10, 11, 0, 0);
    }
    if ( (uint8_t)sub_423340(a1 + 292, szPassword) != 0 )
    {
      if ( *(uint8_t *)(a1 + 320) != 0 )
        goto LABEL_87;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
      if ( *(uint32_t *)(a1 + 316) < 0x10u )
        v24 = a1 + 296;
      else
        v24 = *(uint32_t *)(a1 + 296);
      v78 = *(uint32_t *)dword_79C0B0;
      v25 = sub_422E70(276);
      (*(void (/*cdecl*/ **)(int, int, int, unsigned int, int, int))(v78 + 80))(
        dword_79C0B0,
        93,
        402,
        (unsigned int)&unk_9BC8E6 | v17,
        v25,
        v24);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      *(uint32_t *)(*(uint32_t *)(a1 + 136) + 128) = -6567706;
    }
    if ( *(uint8_t *)(a1 + 320) == 0 )
    {
LABEL_97:
      if ( *(uint8_t *)(a1 + 1475) != 0 )
      {
        v39 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x11u);
        sub_43B560(59, 319, v39, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);
        v40 = sub_43BC20(a1);
        if ( v40 != -1 )
        {
          v41 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x12u);
          sub_43B560(61, 17 * v40 + 322, v41, 1065353216, 1065353216, 0, -2130706433, 1333788672, 1333788672);
        }
      }
LABEL_100:
      LOBYTE(y) = sub_43BCB0(*(uint32_t *)(a1 + 128));
      if ( (uint8_t)y != 0 )
      {
        LOBYTE(y) = sub_69AC60(*(uint32_t *)(a1 + 136));
        if ( (uint8_t)y == 0 )
        {
          v42 = sub_422E70(279);
          LOBYTE(y) = sub_4649B0(59, 396, -1, -16777216, 1, v42, 0, 0, 1600, 0);
        }
      }
      return y;
    }
LABEL_87:
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    v26 = 28 * *(uint32_t *)(a1 + 1444);
    v27 = *(uint32_t *)(v26 + a1 + 348);
    v28 = v26 + a1 + 324;
    if ( v27 < 0x10 )
      v29 = v28 + 4;
    else
      v29 = *(uint32_t *)(v28 + 4);
    v30 = *(uint32_t *)dword_79C0B0;
    v66 = v29;
    v31 = sub_422E70(277);
    (*(void (/*cdecl*/ **)(int, int, int, unsigned int, int, int))(v30 + 80))(
      dword_79C0B0,
      93,
      402,
      (unsigned int)&unk_9BC8E6 | v17,
      v31,
      v66);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    if ( *(uint8_t *)(a1 + 1452) == 0 )
    {
      sub_401690((int)v72, (size_t *)(28 * *(uint32_t *)(a1 + 1444) + a1 + 324));
      v74 = 0;
      v32 = (char *)sub_422E70(278);
      sub_402410((std::_String_base *)v72, v32);
      v33 = (uint32_t *)v73[0];
      if ( v73[5] < 0x10u )
        v33 = v73;
      v34 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v33);
      sub_69A5F0(*(uint32_t **)(a1 + 136), v34 + 93, 402);
      v35 = 28 * *(uint32_t *)(a1 + 1444);
      v36 = *(uint32_t *)(v35 + a1 + 908);
      v37 = v35 + a1 + 884;
      if ( v36 < 0x10 )
        v38 = (char *)(v37 + 4);
      else
        v38 = *(char **)(v37 + 4);
      sub_69BD90(*(uint32_t *)(a1 + 136), v38, a2);
      *(uint8_t *)(a1 + 1452) = 1;
      v74 = -1;
      sub_501490(v72);
    }
    goto LABEL_97;
  }
  v43 = *(uint32_t *)(a3 + 20) + 36;
  v44 = *(uint32_t *)(a3 + 24);
  if ( a3 == v12 )
    v45 = v44 + 144;
  else
    v45 = v44 + 336;
  v79 = v45;
  v71 = 0;
  for ( i = 19; i < 39; i += 4 )
  {
    if ( *(uint32_t *)(a1 + 144) == v71 )
    {
      v47 = sub_418DD0(*(uint32_t **)(a1 + 140), i);
      if ( v47 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v47 + 152))(v47, v43, v79, dword_79C0B0);
    }
    v48 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x2Cu);
    if ( v48 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v48 + 152))(v48, v43, v79, dword_79C0B0);
    v43 += 45;
    ++v71;
  }
  LOBYTE(y) = *(uint8_t *)(a1 + 1473);
  if ( (uint8_t)y != 0 )
  {
    y = pt.y;
    x = pt.x;
    v80 = pt.y;
    if ( *(uint8_t *)(a1 + 1474) != 0 )
      goto LABEL_147;
    if ( pt.x >= 2 && (pt.x <= 319 && pt.y >= 35 && pt.y <= 195 || pt.x <= 54 && pt.y >= 198 && pt.y <= 287) )
    {
      sub_69A5F0(*(uint32_t **)(a1 + 112), 2, 198);
      v50 = sub_418DD0(*(uint32_t **)(a1 + 140), 0xFu);
      if ( v50 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v50 + 128))(
          v50,
          2,
          198,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1333788672,
          1333788672);
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1453) != 0 )
      {
        v51 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v51 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v51 + 128))(
            v51,
            11,
            208,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1457) != 0 )
      {
        v52 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v52 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v52 + 128))(
            v52,
            11,
            224,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1461) != 0 )
      {
        v53 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v53 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v53 + 128))(
            v53,
            11,
            240,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1465) != 0 )
      {
        v54 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v54 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v54 + 128))(
            v54,
            11,
            256,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1469) != 0 )
      {
        v55 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v55 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v55 + 128))(
            v55,
            11,
            272,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      v56 = sub_43BBC0(a1);
      if ( v56 != -1 )
      {
        v57 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x12u);
        if ( v57 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v57 + 128))(
            v57,
            1,
            16 * v56 + 202,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -2130706433,
            1333788672,
            1333788672);
      }
      y = v80;
    }
    if ( *(uint8_t *)(a1 + 1474) != 0 )
    {
LABEL_147:
      if ( x < 2 )
        return y;
      if ( x <= 319 && y >= 35 && y <= 387 )
        goto LABEL_152;
    }
    if ( x >= 2 && x <= 54 && y >= 390 && y <= 479 )
    {
LABEL_152:
      sub_69A5F0(*(uint32_t **)(a1 + 112), 2, 390);
      v58 = sub_418DD0(*(uint32_t **)(a1 + 140), 0xFu);
      if ( v58 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v58 + 128))(
          v58,
          2,
          390,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1333788672,
          1333788672);
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1453) != 0 )
      {
        v59 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v59 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v59 + 128))(
            v59,
            11,
            400,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1457) != 0 )
      {
        v60 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v60 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v60 + 128))(
            v60,
            11,
            416,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1461) != 0 )
      {
        v61 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v61 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v61 + 128))(
            v61,
            11,
            432,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1465) != 0 )
      {
        v62 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v62 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v62 + 128))(
            v62,
            11,
            448,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 144) + a1 + 1469) != 0 )
      {
        v63 = sub_418DD0(*(uint32_t **)(a1 + 140), 0x10u);
        if ( v63 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v63 + 128))(
            v63,
            11,
            464,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      y = sub_43BBC0(a1);
      v64 = y;
      if ( y != -1 )
      {
        y = sub_418DD0(*(uint32_t **)(a1 + 140), 0x12u);
        if ( y != 0 )
          LOBYTE(y) = (*(int (/*thiscall*/ **)(LONG, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)y + 128))(
                        y,
                        1,
                        16 * v64 + 394,
                        dword_79C0B0,
                        1065353216,
                        1065353216,
                        0,
                        -2130706433,
                        1333788672,
                        1333788672);
      }
    }
  }
  return y;
}


// ------------------------------------------------------------
// 0x43D900 sub_43D900
// ------------------------------------------------------------
char */*thiscall*/ sub_43D900(uint32_t *this, char *Str, int a3, int a4, char *Src)
{
  int v5; // eax
  int v6; // ecx
  int v7; // esi
  int v8; // eax
  int16_t v9; // ax
  int v10; // eax
  char *result; // eax
  int v12; // eax
  int v13; // eax
  const char *v14; // eax
  int v15; // eax

  if ( a3 != 1 || (uint16_t)a4 != (uint16_t)word_77F804 )
  {
    sub_43C960((int)this, Str, a3, a4, Src);
    if ( a3 == 0 )
      goto LABEL_20;
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, a4);
  if ( v5 != 0 )
  {
    v6 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v6 == 1 || v6 == 2 )
    {
      v7 = *(uint32_t *)(v5 + 192);
LABEL_12:
      if ( v7 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 64))(v7);
        sub_50EF20(v8, Str, 0, -1);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 68))(v7);
        sub_50EAA0(Str);
      }
      goto LABEL_14;
    }
    if ( v6 == 3 || v6 == 4 || v6 == 6 )
    {
      v7 = *(uint32_t *)(v5 + 196);
      goto LABEL_12;
    }
  }
LABEL_14:
  v9 = *(uint16_t *)(dword_8F8538 + 4);
  if ( v9 == -1 )
    goto LABEL_20;
  if ( (uint16_t)a4 == (uint16_t)word_77F804 )
  {
    v10 = 0;
  }
  else
  {
    if ( (uint16_t)a4 != v9 )
      goto LABEL_20;
    v10 = 1;
  }
  sub_50EF20(*(uint32_t *)(*(uint32_t *)(*(this + 2) + 64) + 4 * v10 + 220), Str, 0, -1);
LABEL_20:
  result = (char *)sub_4BE170();
  if ( result != nullptr )
  {
    v12 = sub_4BE170();
    result = (char *)sub_4BE190(v12);
    if ( result != nullptr )
    {
      if ( (result = (char *)dword_8F7A24, *(uint32_t *)(dword_8F7A24 + 12) == 3) && a3 == 2 || a3 == 3 )
      {
        v13 = sub_4BE170();
        v14 = (const char *)sub_4BE190(v13);
        result = strstr(Str, v14);
        if ( result != nullptr )
        {
          v15 = sub_4BE170();
          return (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 4))(v15);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x43DA50 sub_43DA50
// ------------------------------------------------------------
int /*thiscall*/ sub_43DA50(int this, CHAR *a2, char *Format)
{
  char *v4; // eax
  void *p_Block; // eax
  int v6; // esi
  int result; // eax
  char v8; // [esp+0h] [ebp-38h]
  uint8_t v9[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h] BYREF
  int v11; // [esp+20h] [ebp-18h]
  unsigned int v12; // [esp+24h] [ebp-14h]
  int v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+34h] [ebp-4h]

  v13 = dword_796E50;
  if ( a2 != nullptr && a2 != szPassword && sub_43BF40((int *)this, a2) != 0 )
    sub_4015C0(a2, strlen(a2));
  else
    sub_4015C0((void *)szPassword, 0);
  if ( sub_40BF00((std::_String_base *)(this + 292), 0, *(uint32_t *)(this + 312), szPassword, 0) != 0 )
  {
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)v9, this + 292, 0, -1);
    v14 = 0;
    v4 = sub_422E70(294);
    sub_4022F0((std::_String_base *)v9, v4, strlen(v4));
    p_Block = Block;
    if ( v12 < 0x10 )
      p_Block = &Block;
    v6 = (*(int (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, p_Block);
    sub_69A5F0(*(uint32_t **)(this + 136), v6 + 93, 402);
    *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475 - v6;
    v14 = -1;
    if ( v12 >= 0x10 )
      j__free(Block);
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
  }
  else
  {
    sub_69A5F0(*(uint32_t **)(this + 136), 93, 402);
    *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475;
  }
  result = (int)Format;
  if ( Format != nullptr )
    return sub_69BD90(*(uint32_t *)(this + 136), Format, v8);
  return result;
}



// ------------------------------------------------------------
// 0x43DBE0 sub_43DBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_43DBE0(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // edi
  int v7; // edi
  char *v8; // eax
  char *v9; // eax
  uint32_t *v10; // edi
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *Source; // [esp+8h] [ebp-8Ch]
  int v21; // [esp+Ch] [ebp-88h]
  int v22; // [esp+Ch] [ebp-88h]
  char Destination[128]; // [esp+10h] [ebp-84h] BYREF
  int v24; // [esp+90h] [ebp-4h]

  v2 = *(this + 34);
  v24 = dword_796E50;
  LOBYTE(v3) = *(uint8_t *)(v2 + 220);
  if ( (uint8_t)v3 == 0 )
    return v3;
  v4 = sub_69B740(v2);
  if ( strstr((const char *)v4, "/w ") == (char *)v4 || strstr((const char *)v4, "/W ") == (char *)v4 )
  {
    v21 = 3;
    v6 = 3;
  }
  else
  {
    v5 = sub_422E70(321);
    if ( (uint8_t)sub_43B600(v4, 0, v5, 0) == 0 )
      goto LABEL_11;
    v6 = 4;
    v21 = 4;
  }
  Source = (char *)(v6 + v4);
  if ( *(uint8_t *)(v6 + v4) == 32 || (v7 = v6 + 1) >= strlen((const char *)v4) )
  {
LABEL_11:
    if ( strstr((const char *)v4, "/r ") == (char *)v4 || strstr((const char *)v4, "/R ") == (char *)v4 )
    {
      v22 = 3;
    }
    else
    {
      v8 = sub_422E70(322);
      if ( strstr((const char *)v4, v8) != (char *)v4 )
        goto LABEL_23;
      v22 = 4;
    }
    if ( sub_40BF00((std::_String_base *)(this + 449), 0, *(this + 454), szPassword, 0) != 0 )
    {
      if ( *(this + 455) < 0x10u )
        v10 = this + 450;
      else
        v10 = (uint32_t *)*(this + 450);
      sub_43DA50(this, v10, v4 + v22);
    }
    else
    {
      v9 = sub_422E70(323);
      sub_43BEE0(this, (int)v9, -6567706, 0, -1);
      sub_69BD90(*(this + 34), (char *)szPassword);
    }
LABEL_23:
    if ( (*(this + 72) != 1 || sub_40BF00((std::_String_base *)(this + 73), 0, *(this + 78), szPassword, 0) != 0)
      && (strstr((const char *)v4, "/p ") == (char *)v4
       || strstr((const char *)v4, "/P ") == (char *)v4
       || (v11 = sub_422E70(324), strstr((const char *)v4, v11) == (char *)v4)) )
    {
      if ( sub_40BF00((std::_String_base *)(this + 73), 0, *(this + 78), szPassword, 0) != 0 )
        sub_43DA50(this, 0, 0);
      if ( *(this + 72) != 1
        && sub_429830((uint16_t)word_77F804) != 0
        && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
      {
        *(this + 72) = 1;
      }
      v18 = sub_422E70(325);
      if ( strstr((const char *)v4, v18) == (char *)v4 )
        goto LABEL_48;
    }
    else
    {
      if ( *(this + 72) == 2
        || strstr((const char *)v4, "/g ") != (char *)v4
        && (uint8_t)sub_43B600(v4, 0, "/G ", 0) == 0
        && (v12 = sub_422E70(326), (uint8_t)sub_43B600(v4, 0, v12, 0) == 0) )
      {
        if ( *(this + 72) != 3
          && ((uint8_t)sub_43B600(v4, 0, "/m ", 0) != 0
           || (uint8_t)sub_43B600(v4, 0, "/M ", 0) != 0
           || (v14 = sub_422E70(1521), (uint8_t)sub_43B600(v4, 0, v14, 0) != 0)) )
        {
          *(this + 72) = 3;
          v15 = sub_422E70(1521);
          if ( (uint8_t)sub_43B600(v4, 0, v15, 0) == 0 )
            goto LABEL_57;
        }
        else
        {
          v3 = *(this + 72);
          if ( v3 == 0 )
            return v3;
          if ( (uint8_t)sub_43B600(v4, 0, "/a ", 0) == 0 && (uint8_t)sub_43B600(v4, 0, "/A ", 0) == 0 )
          {
            v16 = sub_422E70(3003);
            LOBYTE(v3) = sub_43B600(v4, 0, v16, 0);
            if ( (uint8_t)v3 == 0 )
              return v3;
          }
          *(this + 72) = 0;
          v17 = sub_422E70(3003);
          if ( (uint8_t)sub_43B600(v4, 0, v17, 0) == 0 )
            goto LABEL_57;
        }
LABEL_48:
        LOBYTE(v3) = sub_69BD90(*(this + 34), (char *)(v4 + 4));
        return v3;
      }
      if ( sub_429830((uint16_t)word_77F804) != 0
        && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) != 0 )
      {
        *(this + 72) = 2;
      }
      v13 = sub_422E70(327);
      if ( strstr((const char *)v4, v13) == (char *)v4 )
        goto LABEL_48;
    }
LABEL_57:
    LOBYTE(v3) = sub_69BD90(*(this + 34), (char *)(v4 + 3));
    return v3;
  }
  while ( *(uint8_t *)(v7 + v4) != 32 )
  {
    if ( ++v7 >= strlen((const char *)v4) )
      goto LABEL_11;
  }
  strncpy(Destination, Source, v7 - v21);
  Destination[v7 - v21] = 0;
  sub_40BE20("\n.......6 <%s><%s>", (char)Destination);
  LOBYTE(v3) = sub_43DA50(this, Destination, v7 + v4 + 1);
  return v3;
}


// ------------------------------------------------------------
// 0x43E150 sub_43E150
// ------------------------------------------------------------
int /*thiscall*/ sub_43E150(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  int v5; // eax
  int v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint32_t *v9; // ebx
  uint8_t *v10; // eax
  uint32_t *v11; // edi
  char *v12; // eax
  int v13; // edi
  uint8_t *v14; // ebx
  uint8_t *v15; // ebx
  uint8_t *v16; // eax
  uint32_t *v17; // edi
  int v18; // ebx
  uint8_t *v19; // edi
  int v20; // ebx
  uint8_t *v21; // eax
  uint32_t *v22; // edi
  int v23; // ebx
  uint8_t *v24; // eax
  uint32_t *v25; // edi
  int v26; // ebx
  uint32_t *v27; // edi
  uint8_t *v28; // eax
  uint32_t *v29; // ebx
  uint32_t *v30; // ecx
  uint8_t *v31; // eax
  uint8_t *v32; // eax
  uint8_t *v33; // eax
  uint32_t *v34; // edi
  uint32_t *v35; // ecx
  uint8_t *v36; // eax
  uint8_t *v37; // eax
  uint8_t *v38; // eax
  uint8_t *v39; // eax
  uint8_t *v40; // eax
  uint32_t *v41; // edi
  int v42; // ebx
  uint8_t *v43; // eax
  uint32_t *v44; // edi
  int v45; // ebx
  uint8_t *v46; // eax
  uint32_t *v47; // edi
  int v48; // ebx
  uint8_t *v49; // eax
  uint8_t *v50; // eax
  uint32_t *v51; // eax
  uint8_t *v52; // eax
  uint8_t *v53; // eax
  uint8_t *v54; // eax
  uint8_t *v55; // eax
  int v56; // eax
  int v57; // eax
  int *v58; // ecx
  int v59; // edi
  bool v60; // dl
  int v61; // edi
  int v62; // eax
  BOOL v63; // ebx
  int v64; // eax
  int v66; // [esp+10h] [ebp-20h]
  int v67; // [esp+10h] [ebp-20h]
  int v68; // [esp+10h] [ebp-20h]
  int v69; // [esp+10h] [ebp-20h]
  int v70; // [esp+10h] [ebp-20h]
  char *Blocka; // [esp+38h] [ebp+8h]
  uint32_t *Blockb; // [esp+38h] [ebp+8h]
  void *Blockd; // [esp+38h] [ebp+8h]
  void *Blocke; // [esp+38h] [ebp+8h]
  int Blockc; // [esp+38h] [ebp+8h]

  *(uint32_t *)(this + 8) = Block;
  *(uint32_t *)(this + 140) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 92);
  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 12) = v4;
  sub_69A5F0(v4, 2, 35);
  *(uint32_t *)(*(uint32_t *)(this + 12) + 68) = this;
  if ( operator new(0x6Cu) != nullptr )
    v5 = sub_43C250(*(uint32_t *)(this + 140), 0);
  else
    v5 = 0;
  *(uint32_t *)(this + 16) = v5;
  *(uint32_t *)(v5 + 28) = 317;
  *(uint32_t *)(v5 + 32) = 180;
  *(uint32_t *)(*(uint32_t *)(this + 16) + 68) = this;
  if ( operator new(0x6Cu) != nullptr )
    v6 = sub_43C250(*(uint32_t *)(this + 140), 1);
  else
    v6 = 0;
  *(uint32_t *)(this + 20) = v6;
  *(uint32_t *)(v6 + 28) = 317;
  *(uint32_t *)(v6 + 32) = 352;
  *(uint32_t *)(*(uint32_t *)(this + 20) + 68) = this;
  *(uint8_t *)(*(uint32_t *)(this + 20) + 16) = 0;
  v7 = operator new(0x68u);
  if ( v7 != nullptr )
    v8 = sub_426BD0(v7);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 24) = v8;
  *((uint32_t *)v8 + 7) = 180;
  *((uint32_t *)v8 + 8) = 18;
  sub_69A840(*(uint32_t *)(this + 24));
  sub_69A840(*(uint32_t *)(this + 24));
  Blocka = nullptr;
  v9 = (uint32_t *)(this + 28);
  do
  {
    v10 = operator new(0x84u);
    v11 = v10;
    if ( v10 != nullptr )
    {
      v66 = *(uint32_t *)(this + 140);
      sub_426BD0(v10);
      *v11 = &nengine::CNButton::`vftable';
      sub_69C780(v11);
      sub_69C7B0(v66, (char *)v9 - 8 - this, (char *)v9 - 9 - this, (char *)v9 - 7 - this, (char *)v9 - 6 - this, 0, 0);
    }
    else
    {
      v11 = nullptr;
    }
    *v9 = v11;
    sub_69A840(v11);
    sub_69A840(*v9);
    v12 = Blocka;
    if ( Blocka == (char *)2 || Blocka == (char *)3 )
      *(uint8_t *)(*v9 + 17) = 0;
    ++v9;
    ++Blocka;
  }
  while ( (int)(v12 + 1) < 4 );
  v13 = 4;
  Blockb = (uint32_t *)(this + 60);
  do
  {
    v14 = operator new(0x84u);
    if ( v14 != nullptr )
    {
      v67 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v14);
      *(uint32_t *)v14 = &nengine::CNButton::`vftable';
      sub_69C780(v14);
      sub_69C7B0(v67, v13, v13, v13 + 1, v13, 0, 0);
    }
    else
    {
      v14 = nullptr;
    }
    *(Blockb - 4) = v14;
    v15 = operator new(0x84u);
    if ( v15 != nullptr )
    {
      v68 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v15);
      *(uint32_t *)v15 = &nengine::CNButton::`vftable';
      sub_69C780(v15);
      sub_69C7B0(v68, v13, v13, v13 + 1, v13, 0, 0);
    }
    else
    {
      v15 = nullptr;
    }
    *Blockb = v15;
    v13 += 2;
    ++Blockb;
  }
  while ( v13 < 8 );
  v16 = operator new(0x88u);
  v17 = v16;
  if ( v16 != nullptr )
  {
    v18 = *(uint32_t *)(this + 140);
    sub_426BD0(v16);
    *v17 = &nengine::CNSlider::`vftable';
    sub_69CA20(v17);
    sub_69CA50(v18, 6, 8);
    *v17 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v17 = nullptr;
  }
  *(uint32_t *)(this + 52) = v17;
  v19 = operator new(0x74u);
  if ( v19 != nullptr )
  {
    v20 = *(uint32_t *)(this + 52);
    Blockd = *(void **)(this + 48);
    v69 = *(uint32_t *)(this + 44);
    sub_426BD0(v19);
    *(uint32_t *)v19 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v19);
    *(uint32_t *)v19 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v19);
    sub_69CD70(v69, Blockd, v20);
  }
  else
  {
    v19 = nullptr;
  }
  *(uint32_t *)(this + 56) = v19;
  sub_69A5F0(v19, 302, 10);
  sub_69A840(*(uint32_t *)(this + 56));
  v21 = operator new(0x88u);
  v22 = v21;
  if ( v21 != nullptr )
  {
    v23 = *(uint32_t *)(this + 140);
    sub_426BD0(v21);
    *v22 = &nengine::CNSlider::`vftable';
    sub_69CA20(v22);
    sub_69CA50(v23, 7, 8);
    *v22 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v22 = nullptr;
  }
  *(uint32_t *)(this + 68) = v22;
  v24 = operator new(0x74u);
  v25 = v24;
  if ( v24 != nullptr )
  {
    v26 = *(uint32_t *)(this + 68);
    Blocke = *(void **)(this + 64);
    v70 = *(uint32_t *)(this + 60);
    sub_426BD0(v24);
    *v25 = &nengine::CNScroll::`vftable';
    sub_69C5D0(v25);
    *v25 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v25);
    sub_69CD70(v70, Blocke, v26);
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 72) = v25;
  sub_69A5F0(v25, 302, 10);
  sub_69A840(*(uint32_t *)(this + 72));
  sub_69A5F0(*(uint32_t **)(this + 16), 2, 35);
  sub_69A5F0(*(uint32_t **)(this + 20), 2, 35);
  sub_69A840(*(uint32_t *)(this + 16));
  sub_69A840(*(uint32_t *)(this + 20));
  v27 = (uint32_t *)(this + 76);
  for ( Blockc = 4; Blockc != 0; --Blockc )
  {
    v28 = operator new(0x6Cu);
    v29 = v28;
    if ( v28 != nullptr )
    {
      sub_426BD0(v28);
      *v29 = &nengine::CNTextBox::`vftable';
      sub_69C2D0(v29);
      sub_69C520(290, 2048);
      v30 = v29;
    }
    else
    {
      v30 = nullptr;
    }
    *v27 = v30;
    sub_69A5F0(v30, 8, 46);
    sub_69C420(4);
    sub_69C460(1);
    sub_69C480(-16777216);
    sub_69C4C0(dword_99FCCC);
    *(uint32_t *)(*v27 + 68) = this;
    sub_69A840(*v27++);
  }
  v31 = operator new(0x68u);
  if ( v31 != nullptr )
    v32 = sub_426BD0(v31);
  else
    v32 = nullptr;
  *(uint32_t *)(this + 92) = v32;
  v33 = operator new(0x6Cu);
  v34 = v33;
  if ( v33 != nullptr )
  {
    sub_426BD0(v33);
    *v34 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v34);
    sub_69C520(330, 2048);
    v35 = v34;
  }
  else
  {
    v35 = nullptr;
  }
  *(uint32_t *)(this + 96) = v35;
  sub_69A5F0(v35, 9, 74);
  sub_69C3E0(20);
  sub_69C420(2);
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C4C0(dword_99FCCC);
  sub_69A840(*(uint32_t *)(this + 96));
  v36 = operator new(0x68u);
  if ( v36 != nullptr )
    v37 = sub_426BD0(v36);
  else
    v37 = nullptr;
  *(uint32_t *)(this + 112) = v37;
  *((uint32_t *)v37 + 7) = 52;
  *((uint32_t *)v37 + 8) = 89;
  sub_69A840(*(uint32_t *)(this + 112));
  sub_69A840(*(uint32_t *)(this + 112));
  v38 = operator new(0x68u);
  if ( v38 != nullptr )
    v39 = sub_426BD0(v38);
  else
    v39 = nullptr;
  *(uint32_t *)(this + 116) = v39;
  *((uint32_t *)v39 + 7) = 61;
  *((uint32_t *)v39 + 8) = 70;
  v40 = operator new(0x84u);
  v41 = v40;
  if ( v40 != nullptr )
  {
    v42 = *(uint32_t *)(this + 140);
    sub_426BD0(v40);
    *v41 = &nengine::CNButton::`vftable';
    sub_69C780(v41);
    sub_69C7B0(v42, 9, 10, 10, 9, 0, 0);
  }
  else
  {
    v41 = nullptr;
  }
  *(uint32_t *)(this + 100) = v41;
  sub_69A840(v41);
  sub_69A840(*(uint32_t *)(this + 100));
  v43 = operator new(0x84u);
  v44 = v43;
  if ( v43 != nullptr )
  {
    v45 = *(uint32_t *)(this + 140);
    sub_426BD0(v43);
    *v44 = &nengine::CNButton::`vftable';
    sub_69C780(v44);
    sub_69C7B0(v45, 11, 12, 12, 11, 0, 0);
  }
  else
  {
    v44 = nullptr;
  }
  *(uint32_t *)(this + 104) = v44;
  sub_69A840(v44);
  sub_69A840(*(uint32_t *)(this + 104));
  v46 = operator new(0x84u);
  v47 = v46;
  if ( v46 != nullptr )
  {
    v48 = *(uint32_t *)(this + 140);
    sub_426BD0(v46);
    *v47 = &nengine::CNButton::`vftable';
    sub_69C780(v47);
    sub_69C7B0(v48, 13, 14, 14, 13, 0, 0);
  }
  else
  {
    v47 = nullptr;
  }
  *(uint32_t *)(this + 108) = v47;
  sub_69A840(v47);
  sub_69A840(*(uint32_t *)(this + 108));
  v49 = operator new(0x68u);
  if ( v49 != nullptr )
    v50 = sub_426BD0(v49);
  else
    v50 = nullptr;
  *(uint32_t *)(this + 120) = v50;
  *((uint32_t *)v50 + 17) = this;
  if ( operator new(0xE4u) != nullptr )
    v51 = (uint32_t *)sub_43C060(1, -1);
  else
    v51 = nullptr;
  *(uint32_t *)(this + 124) = v51;
  sub_69A5F0(v51, 640, 480);
  sub_69A840(*(uint32_t *)(this + 124));
  *(uint8_t *)(*(uint32_t *)(this + 124) + 221) = 1;
  v52 = operator new(0x68u);
  if ( v52 != nullptr )
    v53 = sub_426BD0(v52);
  else
    v53 = nullptr;
  *(uint32_t *)(this + 128) = v53;
  *((uint32_t *)v53 + 7) = 520;
  *((uint32_t *)v53 + 8) = 22;
  sub_69A5F0(*(uint32_t **)(this + 128), 59, 396);
  sub_69A840(*(uint32_t *)(this + 128));
  v54 = operator new(0x68u);
  if ( v54 != nullptr )
    v55 = sub_426BD0(v54);
  else
    v55 = nullptr;
  *(uint32_t *)(this + 132) = v55;
  *((uint32_t *)v55 + 7) = 28;
  *((uint32_t *)v55 + 8) = 16;
  sub_69A5F0(*(uint32_t **)(this + 132), 62, 399);
  sub_69A840(*(uint32_t *)(this + 132));
  if ( operator new(0xE4u) != nullptr )
    v56 = sub_43C060(95, 480);
  else
    v56 = 0;
  *(uint32_t *)(this + 136) = v56;
  *(uint32_t *)(v56 + 128) = -1;
  sub_69A840(*(uint32_t *)(this + 136));
  sub_69A840(*(uint32_t *)(this + 116));
  if ( *(uint8_t *)(this + 256) != 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 124) + 12);
    dword_79BE54 = dword_79BE4C;
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
    *(uint8_t *)(this + 273) = 0;
    *(uint8_t *)(this + 274) = 0;
    sub_698F90(this + 260, 100, 0);
    *(uint8_t *)(this + 256) = 0;
    sub_4BF300(0, 1);
  }
  *(uint8_t *)(this + 161) = 0;
  *(uint8_t *)(this + 162) = 0;
  sub_698F90(this + 148, 0, 0);
  *(uint8_t *)(this + 273) = 0;
  *(uint8_t *)(this + 274) = 0;
  sub_698F90(this + 260, 0, 0);
  *(uint8_t *)(this + 1489) = 0;
  *(uint8_t *)(this + 1490) = 0;
  sub_698F90(this + 1476, 0, 0);
  *(uint8_t *)(this + 1517) = 0;
  *(uint8_t *)(this + 1518) = 0;
  sub_698F90(this + 1504, 0, 0);
  *(uint32_t *)(this + 144) = 0;
  v57 = 0;
  v58 = (int *)(this + 28);
  do
  {
    *(uint8_t *)(v58[12] + 16) = v57 == 0;
    v59 = *v58;
    v60 = v57++ != 0;
    ++v58;
    *(uint8_t *)(v59 + 16) = v60;
  }
  while ( v57 < 4 );
  v61 = sub_69C3A0(*(uint32_t *)(this + 76));
  v62 = sub_69C500(*(uint32_t *)(this + 76)) - v61;
  v63 = v62 <= 0;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), v63 ? 0 : v62);
    v64 = sub_69C6A0(*(uint32_t **)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v63 ? 0 : v62);
    v64 = sub_69C6A0(*(uint32_t **)(this + 56));
  }
  sub_69C680(v64);
  return sub_43DA50(this, 0, 0);
}


// ------------------------------------------------------------
// 0x43ECC0 sub_43ECC0
// ------------------------------------------------------------
int /*thiscall*/ sub_43ECC0(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax

  *(uint8_t *)(this + 1532) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 28) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 80) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = 1;
  v2 = sub_69C3A0(*(uint32_t *)(this + 76));
  v3 = sub_69C500(*(uint32_t *)(this + 76)) - v2;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), v3 <= 0 ? 0 : v3);
    v4 = sub_69C6A0(*(uint32_t *)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v3 <= 0 ? 0 : v3);
    v4 = sub_69C6A0(*(uint32_t *)(this + 56));
  }
  sub_69C680(v4);
  return sub_43DA50(this, nullptr, nullptr);
}



// ------------------------------------------------------------
// 0x43ED90 sub_43ED90
// ------------------------------------------------------------
char /*thiscall*/ sub_43ED90(int this, int a2, int a3, int a4)
{
  const char *v4; // edi
  unsigned int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // ecx
  int i; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  size_t *v18; // ebx
  int j; // edi
  size_t *v20; // eax
  const char *v21; // eax
  int v22; // eax
  size_t *v23; // edi
  bool v24; // zf
  char *v25; // eax
  char v26; // cl
  size_t *v28; // [esp-Ch] [ebp-21Ch]
  char Buffer[256]; // [esp+Ch] [ebp-204h] BYREF
  char Src[256]; // [esp+10Ch] [ebp-104h] BYREF
  int v31; // [esp+20Ch] [ebp-4h]

  v4 = (const char *)a2;
  v31 = dword_796E50;
  v6 = strlen((const char *)a2);
  a2 = v6;
  if ( v6 < 0xFF )
  {
    strcpy(Src, v4);
    v7 = *(uint32_t *)(this + 1500);
    v8 = sub_699000(this + 1476);
    v9 = this + 1476;
    *(uint8_t *)(this + 1490) = 0;
    *(uint8_t *)(this + 1489) = 0;
    if ( v8 < v7 )
    {
      LOBYTE(v6) = sub_698F90(v9, 100, 0);
      return v6;
    }
    sub_698F90(v9, 100, 0);
    v10 = *(uint32_t *)(this + 1528);
    if ( sub_699000(this + 1504) >= v10 || (v6 = strcmp((const char *)(this + 1532), Src)) != 0 )
    {
      v11 = a2;
      for ( i = 0; i < v11; ++i )
      {
        if ( Src[i] == 37 )
          Src[i] = 32;
      }
      if ( (*(int (/*thiscall*/ **)(int, uint32_t, char *))(*(uint32_t *)dword_99FD60 + 20))(dword_99FD60, 0, Src) != 0 )
      {
        v13 = sub_422E70(281);
LABEL_12:
        LOBYTE(v6) = sub_43BEE0((uint32_t *)this, v13, -6567706, 0, -1);
        return v6;
      }
      v14 = a3;
      if ( a3 == 2 )
      {
        v15 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( (v15 == 1 || v15 == 4 || v15 == 6) && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) == 0 )
        {
          v13 = sub_422E70(282);
          goto LABEL_12;
        }
      }
      else if ( a3 == 6 )
      {
        v16 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( (v16 == 1 || v16 == 4 || v16 == a3) && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) == 0 )
        {
          v13 = sub_422E70(283);
          goto LABEL_12;
        }
      }
      sub_423200(dword_8F7B08, 17);
      HIBYTE(a2) = v14;
      sub_423290((char *)&a2 + 3, 1);
      v17 = a4;
      a2 = a4;
      sub_423290(&a2, 2);
      a2 = 0;
      sub_423290(&a2, 4);
      sub_41C100(Src);
      sub_423380(dword_8F7B08);
      if ( v14 == 1 )
      {
        v18 = (size_t *)sub_429830(v17);
        if ( v18 != nullptr )
        {
          for ( j = 0; j < 4; ++j )
          {
            if ( *(uint8_t *)(this + j + 1469) != 0 )
            {
              if ( v18[10] < 0x10 )
                v20 = v18 + 5;
              else
                v20 = (size_t *)v18[5];
              v28 = v20;
              v21 = (const char *)sub_422E70(284);
              sprintf(Buffer, v21, v28, Src);
              sub_43BD50(j, Buffer, -8934503, 1, -1);
            }
          }
          v22 = *(uint32_t *)(this + 1448);
          if ( v22 >= 20 )
          {
            v23 = (size_t *)(this + 324);
            a2 = 19;
            do
            {
              sub_4014D0(v23, v23 + 7, 0, 0xFFFFFFFF);
              sub_4014D0(v23 + 140, v23 + 147, 0, 0xFFFFFFFF);
              v24 = a2 == 1;
              v23 += 7;
              --a2;
            }
            while ( !v24 );
            sub_4014D0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 296), v18 + 4, 0, 0xFFFFFFFF);
            sub_4015C0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 856), Src, strlen(Src));
          }
          else
          {
            sub_4014D0((size_t *)(28 * v22 + this + 324), v18 + 4, 0, 0xFFFFFFFF);
            sub_4015C0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 884), Src, strlen(Src));
            ++*(uint32_t *)(this + 1448);
          }
          *(uint32_t *)(this + 1444) = *(uint32_t *)(this + 1448) - 1;
        }
        sub_43D900(Src, 1, (uint16_t)word_77F804, nullptr);
        v14 = a3;
        LOWORD(v17) = a4;
      }
      v25 = Src;
      do
      {
        v26 = *v25;
        v25[this - (uint32_t)Src + 1532] = *v25;
        ++v25;
      }
      while ( v26 != 0 );
      *(uint32_t *)(this + 1788) = v14;
      *(uint16_t *)(this + 1792) = v17;
      *(uint8_t *)(this + 1517) = 0;
      *(uint8_t *)(this + 1518) = 0;
      sub_698F90(this + 1504, 1000, 0);
      LOBYTE(v6) = byte_77F280;
      if ( byte_77F280 != 0 && v14 != 1 )
        LOBYTE(v6) = sub_43D900(Src, v14, (uint16_t)word_77F804, nullptr);
    }
  }
  return v6;
}


// ------------------------------------------------------------
// 0x43F210 sub_43F210
// ------------------------------------------------------------
int /*cdecl*/ sub_43F210(uint32_t *a1, int a2, int a3, int a4)
{
  void **v4; // ecx
  int v5; // esi
  void *v6; // edi
  char *v7; // eax
  void **v8; // esi
  bool v9; // zf
  void **v10; // edi
  void *v11; // edi
  char *v12; // eax
  void *v13; // edi
  char *v14; // eax
  void *v15; // edi
  char *v16; // eax
  char *v17; // ecx
  void *v18; // eax
  void **v19; // edi
  void *v20; // edi
  char *v21; // eax
  void **v22; // edi
  void *v23; // edi
  char *v24; // eax
  void *v25; // edi
  char *v26; // eax
  void *v27; // edi
  char *v28; // eax
  char *v29; // ecx
  void *v30; // eax
  void **v31; // edi
  void *v32; // edi
  char *v33; // eax
  char *v34; // ecx
  void *v35; // eax
  void **v36; // edi
  void *v37; // edi
  char *v38; // eax
  void **v39; // esi
  void **v40; // edi
  void *v42; // esi
  char *v43; // eax
  char *v44; // ecx
  void *v45; // eax
  void **v46; // edi
  void **v47; // edi
  void **v48; // edi
  void **v49; // esi
  char v50[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  void **v52; // [esp+14h] [ebp-14h]
  int v53; // [esp+18h] [ebp-10h]
  int v54; // [esp+24h] [ebp-4h]

  Block = nullptr;
  v52 = nullptr;
  v53 = 0;
  v54 = 0;
  sub_488690(v50, a4, " ", 2);
  v4 = (void **)Block;
  if ( Block == nullptr || (v5 = ((char *)v52 - (uint8_t *)Block) >> 2) == 0 )
  {
LABEL_66:
    *a1 = 0;
    v54 = -1;
    if ( v4 != nullptr )
    {
      v48 = v52;
      v49 = v4;
      if ( v4 != v52 )
      {
        do
          sub_41B010(v49++);
        while ( v49 != v48 );
        v4 = (void **)Block;
      }
      j__free(v4);
    }
    return a4;
  }
  if ( *(uint8_t *)sub_41ACF0(Block) != 47 )
  {
    v4 = (void **)Block;
    goto LABEL_66;
  }
  if ( v5 == 1 )
  {
    if ( sub_43BCF0(Block, (const char *)&off_6C57B0)
      || sub_43BCF0(Block, (const char *)&off_6C57AC)
      || (v6 = Block, v7 = sub_422E70(285), sub_43BCF0(v6, v7)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *a1 = 2;
      v54 = -1;
      if ( !v9 )
      {
        v10 = v52;
        if ( v8 != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v10 );
LABEL_59:
          j__free(Block);
          return a4;
        }
        goto LABEL_64;
      }
      return a4;
    }
    if ( sub_43BCF0(Block, "/OUT")
      || sub_43BCF0(Block, "/out")
      || (v20 = Block, v21 = sub_422E70(289), sub_43BCF0(v20, v21)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *a1 = 4;
      v54 = -1;
      if ( !v9 )
      {
        v22 = v52;
        if ( v8 != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v22 );
          goto LABEL_59;
        }
LABEL_64:
        j__free(v8);
      }
      return a4;
    }
  }
  else if ( v5 == 2 )
  {
    if ( sub_43BCF0(Block, "/j")
      || sub_43BCF0(Block, "/J")
      || (v11 = Block, v12 = sub_422E70(286), sub_43BCF0(v11, v12))
      || (v13 = Block, v14 = sub_422E70(287), sub_43BCF0(v13, v14))
      || (v15 = Block, v16 = sub_422E70(288), sub_43BCF0(v15, v16)) )
    {
      v17 = (char *)Block + 4;
      *a1 = 3;
      v18 = (void *)sub_41ACF0(v17);
      sub_406D60(v18);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v19 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v19 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return a4;
    }
    if ( sub_43BCF0(Block, "/v")
      || sub_43BCF0(Block, "/V")
      || (v23 = Block, v24 = sub_422E70(290), sub_43BCF0(v23, v24))
      || (v25 = Block, v26 = sub_422E70(2030), sub_43BCF0(v25, v26))
      || (v27 = Block, v28 = sub_422E70(2031), sub_43BCF0(v27, v28)) )
    {
      v29 = (char *)Block + 4;
      *a1 = 5;
      v30 = (void *)sub_41ACF0(v29);
      sub_406D60(v30);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v31 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v31 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return a4;
    }
    if ( sub_43BCF0(Block, (const char *)&off_6C5788)
      || sub_43BCF0(Block, (const char *)&off_6C5784)
      || (v32 = Block, v33 = sub_422E70(291), sub_43BCF0(v32, v33)) )
    {
      v34 = (char *)Block + 4;
      *a1 = 6;
      v35 = (void *)sub_41ACF0(v34);
      sub_406D60(v35);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v36 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v36 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return a4;
    }
  }
  if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 112) != 1
    || (v37 = Block, v38 = sub_422E70(292), !sub_43BCF0(v37, v38)) )
  {
    if ( v5 != 2 || !sub_43BCF0(Block, "/target") && (v42 = Block, v43 = sub_422E70(293), !sub_43BCF0(v42, v43)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *a1 = 8;
      v54 = -1;
      if ( v9 )
        return a4;
      v47 = v52;
      if ( v8 != v52 )
      {
        do
          sub_41B010(v8++);
        while ( v8 != v47 );
        v8 = (void **)Block;
      }
      goto LABEL_64;
    }
    v44 = (char *)Block + 4;
    *a1 = 9;
    v45 = (void *)sub_41ACF0(v44);
    sub_406D60(v45);
    v8 = (void **)Block;
    v54 = -1;
    if ( Block != nullptr )
    {
      v46 = v52;
      if ( Block != v52 )
      {
        do
          sub_41B010(v8++);
        while ( v8 != v46 );
        goto LABEL_59;
      }
      goto LABEL_64;
    }
    return a4;
  }
  v39 = (void **)Block;
  v9 = Block == nullptr;
  *a1 = 7;
  v54 = -1;
  if ( !v9 )
  {
    v40 = v52;
    if ( v39 != v52 )
    {
      do
        sub_41B010(v39++);
      while ( v39 != v40 );
      v39 = (void **)Block;
    }
    j__free(v39);
  }
  return a4 + 5;
}


// ------------------------------------------------------------
// 0x43F740 sub_43F740
// ------------------------------------------------------------
char /*thiscall*/ sub_43F740(uint32_t *this, char *Str)
{
  char *v2; // esi
  int v4; // edi
  uint8_t *v5; // ecx
  uint8_t *v6; // eax
  uint8_t *v7; // esi
  bool v8; // zf
  const char *v9; // eax
  const char *v10; // eax
  int v11; // eax
  const char *v12; // eax
  int v13; // eax
  void **v14; // esi
  void **v15; // edi
  bool v16; // al
  char v17; // bl
  int v18; // esi
  char *v19; // ecx
  int v20; // edi
  const char *v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  uint32_t *v27; // eax
  void **v28; // edi
  void **v29; // edi
  void **v30; // edi
  const char *v31; // eax
  int v32; // ebx
  const char *v33; // eax
  int v34; // ebx
  void **v35; // edi
  const char *v36; // eax
  int v37; // ebx
  void **v38; // edi
  void **v39; // edi
  const char *v40; // eax
  int v41; // ebx
  const char *v42; // eax
  void **v43; // edi
  const char *v44; // eax
  char *v45; // esi
  void **v46; // edi
  void **v47; // edi
  int v48; // eax
  void **v49; // edi
  int v50; // eax
  int v51; // eax
  int v52; // edi
  int v53; // ebx
  uint8_t *v54; // esi
  int v55; // eax
  const char *v56; // eax
  char *v57; // esi
  int v58; // eax
  void **v59; // edi
  const char *v60; // eax
  double v61; // st7
  void **v62; // edi
  const char *v63; // eax
  double v64; // st7
  const char *v65; // eax
  const char *v66; // eax
  const char *v67; // eax
  char v68; // al
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int v73; // esi
  const char *v74; // eax
  char v75; // al
  const char *v76; // eax
  int v77; // eax
  int v78; // esi
  char *v79; // edi
  char *v80; // ebx
  void *v81; // eax
  int v82; // eax
  const char *v83; // eax
  const char *v84; // eax
  const char *v85; // eax
  int v86; // eax
  int v88; // [esp+Ch] [ebp-248h]
  int i; // [esp+Ch] [ebp-248h]
  int v91; // [esp+10h] [ebp-244h]
  bool v92; // [esp+17h] [ebp-23Dh]
  char v93[4]; // [esp+18h] [ebp-23Ch] BYREF
  void *Block; // [esp+1Ch] [ebp-238h]
  uint8_t *v95; // [esp+20h] [ebp-234h]
  int v96; // [esp+24h] [ebp-230h]
  char Buffer[512]; // [esp+28h] [ebp-22Ch] BYREF
  char v98[4]; // [esp+228h] [ebp-2Ch] BYREF
  uint32_t *v99; // [esp+22Ch] [ebp-28h] BYREF
  int v100; // [esp+23Ch] [ebp-18h]
  unsigned int v101; // [esp+240h] [ebp-14h]
  int v102; // [esp+244h] [ebp-10h]
  int v103; // [esp+250h] [ebp-4h]

  v2 = Str;
  v102 = dword_796E50;
  v4 = 0;
  if ( strstr(Str, "//") != v2 )
    return 0;
  Block = nullptr;
  v95 = nullptr;
  v96 = 0;
  v103 = 0;
  sub_488690(v93, v2, " ", 0);
  v5 = Block;
  v6 = v95;
  if ( Block != nullptr )
  {
    v4 = (v95 - (uint8_t *)Block) >> 2;
    v88 = v4;
  }
  else
  {
    v88 = 0;
  }
  while ( v5 == nullptr || (unsigned int)((v6 - v5) >> 2) < 0xA )
  {
    *(float *)&Str = 0.0;
    sub_41BFE0((void **)&Str, szPassword);
    LOBYTE(v103) = 1;
    if ( Block != nullptr && (v95 - (uint8_t *)Block) >> 2 < (unsigned int)((v96 - (int)Block) >> 2) )
    {
      v7 = v95;
      sub_41FFE0(v95, 1, &Str);
      v95 = v7 + 4;
    }
    else
    {
      sub_4206D0(v95, 1, &Str);
    }
    LOBYTE(v103) = 0;
    sub_41B010((void **)&Str);
    v6 = v95;
    v5 = Block;
  }
  if ( sub_43BCF0(v5, "//monitor") )
  {
    *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 508) = *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 508) == 0;
    off_77F3FC((char *)&byte_6C5CE8);
LABEL_241:
    v103 = -1;
    sub_4017E0(v93);
    return 1;
  }
  if ( sub_43BCF0(Block, "//rrs") )
    goto LABEL_241;
  if ( sub_43BCF0(Block, "//rp2p") )
  {
    v8 = byte_97B6D0 != 0;
    byte_97B6D0 = byte_97B6D0 == 0;
    if ( v8 )
      sub_43BEE0(this, (int)"RelayP2p: false", -6567706, 0, -1);
    else
      sub_43BEE0(this, (int)"RelayP2p: true", -6567706, 0, -1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//rmark") )
  {
    v8 = byte_98B74E != 0;
    byte_98B74E = byte_98B74E == 0;
    if ( v8 )
      sub_43BEE0(this, (int)"ShowRelayMark: false", -6567706, 0, -1);
    else
      sub_43BEE0(this, (int)"ShowRelayMark: true", -6567706, 0, -1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//drop") )
  {
    v9 = (const char *)sub_41ACF0((char *)Block + 4);
    dword_796938 = j__atol(v9);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//lth") )
  {
    sub_657920(2);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//ltm") )
  {
    sub_657920(1);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//ltl") )
  {
    sub_657920(0);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//lt") )
  {
    v10 = (const char *)sub_41ACF0((char *)Block + 4);
    v11 = j__atol(v10);
    sub_657900(v11);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//st") )
  {
    if ( sub_43BCF0((char *)Block + 4, (const char *)&off_6C5C4C) )
    {
      *(uint8_t *)(*(uint32_t *)(dword_8F8520 + 1049988) + 2520) = 0;
    }
    else if ( sub_43BCF0((char *)Block + 4, (const char *)&off_6C5C48) )
    {
      *(uint8_t *)(*(uint32_t *)(dword_8F8520 + 1049988) + 2520) = 1;
    }
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//bt") )
  {
    v12 = (const char *)sub_41ACF0((char *)Block + 4);
    v13 = j__atol(v12);
    sub_657260(*(uint32_t *)(dword_8F8520 + 1049988), v13);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//full") )
  {
    sub_41C1C0(1);
    sub_408FA0(1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//normal") )
  {
    sub_41C1C0(0);
    sub_408FA0(0);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//repel") && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 112) == 1 )
  {
    if ( v4 <= 2 )
    {
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v15 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v15 );
          v14 = (void **)Block;
        }
LABEL_191:
        j__free(v14);
        return 0;
      }
      return 0;
    }
    v16 = sub_43BCF0((char *)Block + 4, "m_id");
    v17 = 0;
    v18 = 0xFFFF;
    v19 = (char *)Block + 8;
    v92 = v16;
    v20 = 0xFFFF;
    if ( v16 )
    {
      v21 = (const char *)sub_41ACF0(v19);
      v20 = j__atol(v21);
    }
    else
    {
      v22 = sub_41ACF0(v19);
      v23 = sub_429870(v22);
      if ( v23 == 0 )
      {
LABEL_57:
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 12;
        sub_423290((char *)&Str + 3, 1);
        if ( v92 )
        {
          HIBYTE(Str) = 1;
          sub_423290((char *)&Str + 3, 1);
          Str = (char *)v20;
        }
        else
        {
          HIBYTE(Str) = 0;
          sub_423290((char *)&Str + 3, 1);
          Str = (char *)v18;
        }
        sub_423290(&Str, 4);
        sub_423380(dword_8F7B08);
        v101 = 15;
        v100 = 0;
        LOBYTE(v99) = 0;
        LOBYTE(v103) = 2;
        v24 = sub_41ACF0(Block);
        sub_402410(v24);
        sub_402410(" ");
        v25 = sub_41ACF0((char *)Block + 4);
        sub_402410(v25);
        sub_402410(" ");
        v26 = sub_41ACF0((char *)Block + 8);
        sub_402410(v26);
        if ( v17 != 0 )
          sub_402410(" Success");
        else
          sub_402410(" Fail");
        v27 = v99;
        if ( v101 < 0x10 )
          v27 = &v99;
        sub_43BEE0(this, (int)v27, -6567706, 0, -1);
LABEL_240:
        sub_501490(v98);
        goto LABEL_241;
      }
      v18 = *(uint16_t *)(v23 + 4);
    }
    v17 = 1;
    goto LABEL_57;
  }
  if ( sub_43BCF0(Block, "//godqhrdmlans") )
  {
    sub_423200(dword_8F7B08, 65);
    HIBYTE(Str) = 0;
    sub_423290((char *)&Str + 3, 1);
    sub_423380(dword_8F7B08);
    off_77F3FC((char *)&byte_6C5BD8);
    goto LABEL_241;
  }
  if ( !sub_43BCF0(Block, "//level") || !sub_43BCF0((char *)Block + 4, "up") )
  {
    if ( sub_43BCF0(Block, "//level") && sub_43BCF0((char *)Block + 4, "down") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 2;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B90);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v29 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v29 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//levelto") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v31 = (const char *)sub_41ACF0((char *)Block + 4);
        v32 = j__atol(v31);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 7;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v32;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B68, v32);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v30 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v30 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//pvprank") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v33 = (const char *)sub_41ACF0((char *)Block + 4);
        v34 = j__atol(v33);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 8;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v34;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B40, v34);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v35 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v35 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//grow") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v36 = (const char *)sub_41ACF0((char *)Block + 4);
        v37 = j__atol(v36);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 3;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v37;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B20, v37);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v38 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v38 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//clear")
      && sub_43BCF0((char *)Block + 4, "[all]")
      && sub_43BCF0((char *)Block + 8, "skill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 4;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5AE8);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v39 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v39 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//add") && sub_43BCF0((char *)Block + 4, "skill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 3 )
      {
        v40 = (const char *)sub_41ACF0((char *)Block + 8);
        v41 = j__atol(v40);
        v42 = (const char *)sub_41ACF0((char *)Block + 12);
        v91 = j__atol(v42);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 5;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v41;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v91;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5AB8, v41, v91);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v43 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v43 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//add") && sub_43BCF0((char *)Block + 4, "item") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 2 )
      {
        v44 = (const char *)sub_41ACF0((char *)Block + 8);
        v45 = (char *)j__atol(v44);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 6;
        sub_423290((char *)&Str + 3, 1);
        Str = v45;
        sub_423290(&Str, 2);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5A90, v45);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v46 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v46 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//no") && sub_43BCF0((char *)Block + 4, "random") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v8 = byte_9A05F0 != 0;
        byte_9A05F0 = byte_9A05F0 == 0;
        if ( v8 )
          v48 = sub_422E70(330);
        else
          v48 = sub_422E70(329);
        sub_43BEE0(this, v48, -6567706, 0, -1);
        off_77F3FC((char *)&byte_6C5A5C);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v47 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v47 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//kill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v50 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v50 == 3 || v50 == 6 )
        {
          v51 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          v52 = sub_425100(*(uint32_t *)(v51 + 104));
          v53 = 0;
          for ( i = v52; v53 < v52; ++v53 )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
            v54 = (uint8_t *)sub_425A00(v53);
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v54 + 40))(v54, 529) != 0 )
            {
              if ( byte_77F280 != 0 )
              {
                (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int))(*(uint32_t *)v54 + 732))(v54, 0, 0, 1);
              }
              else if ( v54[7801] != 0 )
              {
                sub_423200(dword_8F7B08, 42);
                *(float *)&Str = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v54 + 52))(v54));
                sub_423290(&Str, 2);
                *(float *)&Str = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04));
                sub_423290(&Str, 2);
                sub_423380(dword_8F7B08);
                v52 = i;
              }
              else
              {
                (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v54 + 312))(v54, 1);
              }
            }
          }
          off_77F3FC((char *)&byte_6C5A38);
          v55 = sub_422E70(331);
          sub_43BEE0(this, v55, -6567706, 0, -1);
        }
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v49 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v49 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//quest") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 && v4 > 1 )
      {
        v56 = (const char *)sub_41ACF0((char *)Block + 4);
        v57 = (char *)j__atol(v56);
        sub_423200(dword_8F7B08, 33);
        Str = v57;
        sub_423290(&Str, 2);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5A14);
        v58 = sub_422E70(332);
        sub_43BEE0(this, v58, -6567706, 0, -1);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v59 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v59 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//style") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v60 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = (double)j__atol(v60) * 0.0099999998;
        v61 = sub_43B5C0(dword_99FD58);
        *((float *)dword_99FD58 + 241) = v61 * *(float *)&Str;
        off_77F3FC((char *)&byte_6C59E8);
        sub_43BEE0(this, (int)"//style : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v62 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v62 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//technic") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v63 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = (double)j__atol(v63) * 0.0099999998;
        v64 = sub_43B5E0(dword_99FD58);
        *((float *)dword_99FD58 + 242) = v64 * *(float *)&Str;
        off_77F3FC((char *)&byte_6C599C);
        sub_43BEE0(this, (int)"//technic : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//attacked") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v65 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = COERCE_FLOAT(j__atol(v65));
        *((float *)dword_99FD58 + 243) = (float)(int)Str;
        off_77F3FC((char *)&byte_6C5950);
        sub_43BEE0(this, (int)"//attacked : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//upgrade") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        if ( sub_43BCF0((char *)Block + 4, "success") )
        {
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(9);
          off_77F3FC(byte_6C58F4);
        }
        else if ( sub_43BCF0((char *)Block + 4, "fail") )
        {
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(10);
          off_77F3FC(byte_6C58C4);
        }
        else
        {
          if ( !sub_43BCF0((char *)Block + 4, "random") )
            goto LABEL_241;
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(11);
          off_77F3FC((char *)&byte_6C589C);
        }
        sub_423380(dword_8F7B08);
        v66 = (const char *)sub_41ACF0((char *)Block + 4);
        sprintf(Buffer, "//upgrade %s - ok", v66);
        sub_43BEE0(this, (int)Buffer, -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//warroomtime") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 && v4 > 1 )
      {
        sub_423200(dword_8F7B08, 65);
        sub_41C0C0(13);
        v67 = (const char *)sub_41ACF0((char *)Block + 4);
        v68 = j__atol(v67);
        sub_43B4C0(v68);
        sub_423380(dword_8F7B08);
        v69 = sub_41ACF0((char *)Block + 4);
        off_77F3FC((char *)&byte_6C5854, v69);
        sub_43BEE0(this, (int)"//warroomtime", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else
    {
      if ( sub_43BCF0(Block, "//mail") )
      {
        v70 = sub_524330();
        sub_523800(v70);
        sub_524AF0(1, 432000, &unk_6C5840, (void *)0x2710, 0);
        v71 = sub_522300((void *)0x699E, 1, 0, 0, -1, 1);
        sub_524AF0(2, 3630, &unk_6C5840, nullptr, v71);
        v72 = sub_522300((void *)0x699E, 1, 0, 0, -1, 1);
        sub_524AF0(3, 180, &unk_6C5840, nullptr, v72);
        sub_44E8D0((char *)dword_8F8528, (void *)0xD, 0, 0);
        goto LABEL_241;
      }
      if ( sub_43BCF0(Block, "//packet") && (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v101 = 15;
        v100 = 0;
        LOBYTE(v99) = 0;
        v73 = dword_8F7B08;
        LOBYTE(v103) = 3;
        v74 = (const char *)sub_41ACF0((char *)Block + 4);
        v75 = j__atol(v74);
        sub_423200(v73, v75);
        v76 = (const char *)sub_41ACF0((char *)Block + 4);
        v77 = j__atol(v76);
        off_77F3FC("commands : %d", v77);
        v78 = 2;
        if ( v4 > 2 )
        {
          v79 = Str;
          v80 = Str;
          do
          {
            if ( v78 % 2 == 1 )
            {
              if ( v79 == (char *)-1 )
              {
                v81 = (void *)sub_41ACF0((char *)Block + 4 * v78);
                sub_406D60(v81);
                v82 = unknown_libname_2(v98);
                sub_41C100(v82);
              }
              else
              {
                if ( (int)v79 > 0 )
                {
                  v84 = (const char *)sub_41ACF0((char *)Block + 4 * v78);
                  v80 = (char *)j__atol(v84);
                }
                if ( v79 == (char *)1 )
                {
                  sub_41C0C0((char)v80);
                  off_77F3FC("WriteByte : %d", 1);
                }
                else if ( v79 == (char *)2 )
                {
                  sub_41C0E0((char)v80);
                }
                else if ( v79 == (char *)4 )
                {
                  sub_43B4C0((char)v80);
                }
                else if ( v79 == (char *)8 )
                {
                  sub_43B4E0((char)v80, (int)v80 >> 31);
                }
              }
              v83 = (const char *)unknown_libname_2(v98);
              off_77F3FC("k : %d\tpacketFieldByteSize : %d\tnumPacket : %d\tstring : %s", v78, v79, v80, v83);
            }
            else
            {
              v85 = (const char *)sub_41ACF0((char *)Block + 4 * v78);
              v79 = (char *)j__atol(v85);
            }
            ++v78;
          }
          while ( v78 < v88 );
        }
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C57B4);
        v86 = sub_422E70(332);
        sub_43BEE0(this, v86, -6567706, 0, -1);
        goto LABEL_240;
      }
    }
    v103 = -1;
    sub_4017E0(v93);
    return 0;
  }
  if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
  {
    sub_423200(dword_8F7B08, 65);
    HIBYTE(Str) = 1;
    sub_423290((char *)&Str + 3, 1);
    sub_423380(dword_8F7B08);
    off_77F3FC((char *)&byte_6C5BB4);
    goto LABEL_241;
  }
  v14 = (void **)Block;
  v103 = -1;
  if ( Block != nullptr )
  {
    v28 = (void **)v95;
    if ( Block != v95 )
    {
      do
        sub_41B010(v14++);
      while ( v14 != v28 );
      v14 = (void **)Block;
    }
    goto LABEL_191;
  }
  return 0;
}

