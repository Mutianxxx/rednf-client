// ============================================================
// 【40JP逆向源代码工程】combat/passive_object.cpp
// 模块: PassiveObject 生成/召唤/精炼
// 来源: work/dump_skills.txt  区块: 0x600000-0x620000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 621
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x6000B0 CNRDPassiveObject__vmtC
// ------------------------------------------------------------
float */*thiscall*/ CNRDPassiveObject__vmtC(int *this)
{
  float *result; // eax
  int v2; // eax
  int v4; // [esp-4h] [ebp-8h]

  IRDCollisionObject__vmtC(this);
  (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
  result = (float *)(*(int (/*thiscall*/ **)(int *, int))(*this + 684))(this, v4);
  if ( result != nullptr )
  {
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    result = (float *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 529);
    if ( (uint8_t)result != 0 )
    {
      result = *(float **)((*(int (/*thiscall*/ **)(int *))(*this + 684))(this) + 7772);
      if ( result == (float *)1 || result == (float *)2 )
      {
        if ( (uint8_t)sub_4DB0E0(261641) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 0;
        if ( (uint8_t)sub_4DB0E0(261642) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 1;
        if ( (uint8_t)sub_4DB0E0(261643) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 3;
        if ( (uint8_t)sub_4DB0E0(261644) != 0 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 348))(this) + 20) = 2;
        result = (float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
        *result = *result * 1.05;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6000E0 CNRDPassiveObject__vmt1D8
// ------------------------------------------------------------
int /*userpurge*/ CNRDPassiveObject__vmt1D8@<eax>(
        uint32_t *a1@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        int a4,
        int a5,
        int a6,
        int a7)
{
  int result; // eax
  int *v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  uint32_t *v13; // eax
  int v14; // eax
  int v15; // [esp-Ch] [ebp-20h]
  char v18; // [esp-4h] [ebp-18h]
  int v19; // [esp+8h] [ebp-Ch]
  int v20; // [esp+Ch] [ebp-8h]
  int v21; // [esp+10h] [ebp-4h]
  int v22; // [esp+1Ch] [ebp+8h]
  int v23; // [esp+20h] [ebp+Ch]

  result = a4 - 1;
  if ( a4 != 1 )
  {
    a1[240] = a4;
    return result;
  }
  v9 = *(int **)(a5 + 4);
  v10 = *v9;
  v23 = v9[2];
  v11 = v9[1];
  v22 = v9[4];
  v19 = v9[5];
  v20 = v9[6];
  v21 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 672))(a1, a3, a2);
  *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 672))(a1) = v11;
  if ( v21 > v11 )
  {
    v18 = dword_8F7C04 == a1[143];
    v15 = 0;
LABEL_7:
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 124))(a1);
    sub_4D7960(v10, v11, (int)a1, v23, v12 + 1, v22, v10, v15, 0, v18);
    goto LABEL_8;
  }
  if ( v21 < v11 )
  {
    v18 = 0;
    v15 = 2;
    goto LABEL_7;
  }
LABEL_8:
  v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 80))(a1);
  v14 = sub_45EBE0(v13, v19, v20);
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*a1 + 692))(a1, v14, v10, v23);
}



// ------------------------------------------------------------
// 0x6001C0 CNRDPassiveObject__vmt214
// ------------------------------------------------------------
char /*thiscall*/ sub_6001C0(uint32_t *this, int a2, int a3, int a4)
{
  char result; // al
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // eax
  int v14; // eax
  float *v15; // esi
  double v16; // st7
  int v17; // eax
  float *v18; // esi
  double v19; // st7
  int v20; // eax
  int v21; // edx
  int v22; // esi
  int v23; // eax
  float v24; // edx
  int v25; // eax
  int v26; // eax
  double v27; // st7
  float v28; // [esp+4h] [ebp-2Ch] BYREF
  float v29; // [esp+8h] [ebp-28h]
  float v30; // [esp+Ch] [ebp-24h]
  float v31; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  float v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int i; // [esp+20h] [ebp-10h]
  int v36; // [esp+24h] [ebp-Ch]
  int v37; // [esp+28h] [ebp-8h]
  int v38; // [esp+2Ch] [ebp-4h]
  int v39; // [esp+40h] [ebp+10h]
  int v40; // [esp+40h] [ebp+10h]
  int v41; // [esp+40h] [ebp+10h]

  result = *((uint8_t *)this + 700);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( result != 0 )
    {
      if ( *(this + 30) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 600))(this) != 0
        && a4 != 0
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 608))(a4) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 360))(this, a4) == 0 )
      {
        sub_4938F0(*(this + 30));
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4);
        sub_4938F0(v7);
        v8 = sub_42F220(*(this + 30));
        if ( (uint8_t)sub_600070(v8 + 56) == 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4);
          v10 = sub_42F220(v9);
          if ( (uint8_t)sub_600070(v10 + 72) == 0 )
          {
            v11 = *(this + 30);
            v38 = 0;
            v39 = 0xFFFF;
            v37 = 0;
            v36 = 0xFFFF;
            v12 = sub_42F220(v11) + 56;
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 200))(a4);
            v34 = sub_42F220(v13) + 72;
            v14 = sub_4FEF30(v12);
            if ( v14 != 0 )
            {
              v15 = (float *)(*(uint32_t *)(v12 + 4) + 8);
              for ( i = v14; i != 0; --i )
              {
                if ( (double)v39 > *v15 )
                  v39 = (uint64_t)*v15;
                v16 = v15[3] + *v15;
                if ( v16 > (double)v38 )
                  v38 = (uint64_t)v16;
                v15 += 6;
              }
            }
            v17 = sub_4FEF30(v34);
            if ( v17 != 0 )
            {
              v18 = (float *)(*(uint32_t *)(v34 + 4) + 8);
              for ( i = v17; i != 0; --i )
              {
                if ( (double)v36 > *v18 )
                  v36 = (uint64_t)*v18;
                v19 = v18[3] + *v18;
                if ( v19 > (double)v37 )
                  v37 = (uint64_t)v19;
                v18 += 6;
              }
            }
            v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
            v21 = *this;
            v38 += v20;
            v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v21 + 128))(this) + v39;
            v37 += (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 128))(a4);
            v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 128))(a4) + v36;
            if ( v38 >= v22 && v37 >= v40 )
            {
              v23 = *(uint32_t *)(sub_42F220(*(this + 30)) + 60);
              v28 = *(float *)v23;
              v29 = *(float *)(v23 + 4);
              v30 = *(float *)(v23 + 8);
              v31 = *(float *)(v23 + 12);
              v32 = *(uint32_t *)(v23 + 16);
              v24 = *(float *)(v23 + 20);
              v25 = *this;
              v33 = v24;
              if ( (*(int (/*thiscall*/ **)(uint32_t *))(v25 + 152))(this) == 0 )
                v28 = -v28 - v31;
              v34 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
              v26 = *this;
              v28 = (double)v34 + v28;
              v34 = (*(int (/*thiscall*/ **)(uint32_t *))(v26 + 124))(this);
              v29 = (double)v34 + v29;
              if ( v40 <= v22 )
                v40 = v22;
              v27 = (double)v40 + v30;
              v41 = v38;
              v30 = v27;
              if ( v38 >= v37 )
                v41 = v37;
              v33 = (double)v41 - v30;
              sub_4E5F70(a4, (int)this, a4, &v28, 1, 1);
            }
          }
        }
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6004B0 sub_6004B0
// ------------------------------------------------------------
char /*thiscall*/ sub_6004B0(uint8_t *this)
{
  int v2; // eax
  void **v3; // edx
  unsigned int v4; // ebx
  uint8_t *v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // esi
  bool v16; // zf
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int v20; // eax
  DWORD v21; // eax
  uint64_t v22; // rax
  DWORD TickCount; // eax
  uint64_t v24; // rax
  int v25; // eax
  float v27; // [esp+0h] [ebp-20h]
  float v28; // [esp+4h] [ebp-1Ch]
  int v29; // [esp+8h] [ebp-18h]
  int v30; // [esp+1Ch] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
  v3 = *(void ***)(v2 + 120);
  v4 = 0;
  if ( v3 != nullptr && (*(uint32_t *)(v2 + 124) - (int)v3) >> 2 != 0 )
    v5 = *v3;
  else
    v5 = nullptr;
  if ( this == v5 )
  {
    dword_9B9358 = 0;
    while ( 1 )
    {
      while ( 1 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
        v7 = *(uint32_t *)(v6 + 120);
        v8 = v6 + 116;
        if ( v7 != 0 )
          v9 = (*(uint32_t *)(v8 + 8) - v7) >> 2;
        else
          v9 = 0;
        if ( (int)v4 >= v9 )
          goto LABEL_29;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
        v11 = *(uint32_t *)(v10 + 120);
        if ( v11 != 0 && v4 < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * v4);
        else
          v12 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 40))(v12, 33) != 0 )
        {
          v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
          v14 = *(uint32_t *)(v13 + 120);
          if ( v14 != 0 && v4 < (*(uint32_t *)(v13 + 124) - v14) >> 2 )
            v15 = *(uint32_t *)(v14 + 4 * v4);
          else
            v15 = 0;
          if ( *(uint8_t *)(v15 + 945) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 200))(v15) != 0 )
            break;
        }
LABEL_28:
        ++v4;
      }
      v16 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 492))(v15, dword_8F7C04) == 1;
      v17 = *(uint32_t *)(v15 + 948);
      if ( !v16 )
      {
        if ( v17 == 2 )
        {
          *(uint32_t *)(v15 + 952) = GetTickCount();
          *(uint32_t *)(v15 + 948) = 1;
        }
        goto LABEL_28;
      }
      if ( v17 == 3 )
      {
        *(uint32_t *)(v15 + 952) = GetTickCount();
        *(uint32_t *)(v15 + 948) = 0;
      }
      ++dword_9B9358;
      ++v4;
    }
  }
LABEL_29:
  LOBYTE(v18) = *(this + 945);
  if ( (uint8_t)v18 != 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    if ( v18 != 0 )
    {
      v19 = 100 - 15 * dword_9B9358;
      v30 = v19;
      if ( v19 < 5 )
      {
        v19 = 5;
        v30 = 5;
      }
      v20 = *((uint32_t *)this + 237);
      if ( v20 != 0 )
      {
        if ( v20 == 1 )
        {
          TickCount = GetTickCount();
          v27 = (float)v30;
          v24 = (uint64_t)sub_4049C0(v27, 255.0, TickCount - *((uint32_t *)this + 238), 200);
          *((uint32_t *)this + 239) = v24;
          if ( (uint32_t)v24 == 255 )
            *((uint32_t *)this + 237) = 3;
        }
      }
      else
      {
        v21 = GetTickCount();
        v28 = (float)v30;
        v22 = (uint64_t)sub_4049C0(255.0, v28, v21 - *((uint32_t *)this + 238), 200);
        *((uint32_t *)this + 239) = v22;
        if ( (uint32_t)v22 == v19 )
          *((uint32_t *)this + 237) = 2;
      }
      v25 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
      sub_4938F0(v25);
      v29 = *((uint32_t *)this + 239);
      (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
      LOBYTE(v18) = sub_491F80(-1, -1, -1, v29, 1);
    }
  }
  return v18;
}


// ------------------------------------------------------------
// 0x600700 sub_600700
// ------------------------------------------------------------
int */*thiscall*/ sub_600700(void *this)
{
  int *result; // eax
  int v2; // esi
  bool v3; // zf
  int v5; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = *(int **)(dword_8F8500 + 8);
  v2 = *result;
  v3 = *result == (uint32_t)result;
  v6 = *result;
  if ( !v3 )
  {
    do
    {
      v5 = *(uint32_t *)(v2 + 16);
      if ( v5 != 0
        && (*(uint8_t (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 696))(this, *(uint32_t *)(v5 + 196)) == 1
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v2 + 16) + 196) + 200))(*(uint32_t *)(*(uint32_t *)(v2 + 16) + 196)) != 0 )
      {
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v2 + 16) + 196) + 200))(*(uint32_t *)(*(uint32_t *)(v2 + 16) + 196))
                 + 161) = 0;
      }
      sub_41C5E0(&v6);
      result = (int *)dword_8F8500;
      v2 = v6;
    }
    while ( v6 != *(uint32_t *)(dword_8F8500 + 8) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x600790 CNRDPassiveObject__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNRDPassiveObject__vmt12C(uint32_t *this, int a2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint8_t v11[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v13; // [esp+20h] [ebp-4h]

  IRDCollisionObject__vmt12C(this, a2);
  if ( a2 == *(this + 173) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 33) != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 672))(a2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 680))(this, *(uint32_t *)(v4 + 12));
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 680))(this, 0);
    }
  }
  if ( (uint32_t *)a2 == this )
  {
    v5 = *(this + 219);
    if ( v5 != 0 )
    {
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v5 + 12))(0);
      v6 = *(uint32_t *)*(this + 219);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*(this + 219), v9);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v11);
      v10 = (void *)*(this + 29);
      v13 = 0;
      sub_4600B0(v10, 2, 0, (int)v11);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x600880 CNRDPassiveObject__vmt10
// ------------------------------------------------------------
// attributes: thunk
char /*thiscall*/ CNRDPassiveObject__vmt10(uint8_t *this)
{
  return sub_6004B0(this);
}



// ------------------------------------------------------------
// 0x600890 CNRDPassiveObject__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNRDPassiveObject__vmt14C(int this)
{
  int v2; // eax
  int *result; // eax
  int v4; // ecx

  IRDCollisionObject__vmt14C((int *)this);
  if ( *(uint8_t *)(this + 944) == 0 )
  {
    if ( *(uint32_t *)(this + 940) < 0x10u )
      v2 = this + 920;
    else
      v2 = *(uint32_t *)(this + 920);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, v2, -1, 0, 0);
    *(uint8_t *)(this + 944) = 1;
  }
  result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v4 = *(uint32_t *)(*(uint32_t *)(this + 112) + 104);
    if ( v4 != 0 )
    {
      result = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 52))(v4);
      if ( (uint8_t)result == 0 )
        result = (int *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
  }
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    result = (int *)dword_9A012C;
    if ( dword_9A012C != 0 )
      return sub_600700((void *)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x600920 sub_600920
// ------------------------------------------------------------
int /*stdcall*/ sub_600920(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v7; // ecx
  unsigned int v8; // edx
  int *v9; // eax
  int v10; // edx
  unsigned int v11; // ecx
  int *v12; // eax
  int v13; // edx
  unsigned int v14; // ecx
  int *v15; // eax
  int v16; // edx
  unsigned int v17; // ecx
  int *v18; // eax
  int v19; // edi

  if ( *(uint32_t *)(a1 + 4) != 0 )
    j__free(*(void **)(a1 + 4));
  *(uint32_t *)(a1 + 4) = 0;
  *(uint32_t *)(a1 + 8) = 0;
  *(uint32_t *)(a1 + 12) = 0;
  sub_430C80(a1, 0, 1u, &a3);
  v7 = *(uint32_t *)(a1 + 4);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(a1 + 8) - v7) >> 2;
  else
    v8 = 0;
  if ( v7 != 0 && v8 < (*(uint32_t *)(a1 + 12) - v7) >> 2 )
  {
    v9 = *(int **)(a1 + 8);
    *v9 = a4;
    *(uint32_t *)(a1 + 8) = v9 + 1;
  }
  else
  {
    sub_430C80(a1, *(uint32_t *)(a1 + 8), 1u, &a4);
  }
  v10 = *(uint32_t *)(a1 + 4);
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(a1 + 8) - v10) >> 2;
  else
    v11 = 0;
  if ( v10 != 0 && v11 < (*(uint32_t *)(a1 + 12) - v10) >> 2 )
  {
    v12 = *(int **)(a1 + 8);
    *v12 = a5;
    *(uint32_t *)(a1 + 8) = v12 + 1;
  }
  else
  {
    sub_430C80(a1, *(uint32_t *)(a1 + 8), 1u, &a5);
  }
  v13 = *(uint32_t *)(a1 + 4);
  if ( v13 != 0 )
    v14 = (*(uint32_t *)(a1 + 8) - v13) >> 2;
  else
    v14 = 0;
  if ( v13 != 0 && v14 < (*(uint32_t *)(a1 + 12) - v13) >> 2 )
  {
    v15 = *(int **)(a1 + 8);
    *v15 = a6;
    *(uint32_t *)(a1 + 8) = v15 + 1;
  }
  else
  {
    sub_430C80(a1, *(uint32_t *)(a1 + 8), 1u, &a6);
  }
  v16 = *(uint32_t *)(a1 + 4);
  if ( v16 != 0 )
    v17 = (*(uint32_t *)(a1 + 8) - v16) >> 2;
  else
    v17 = 0;
  if ( v16 != 0 && v17 < (*(uint32_t *)(a1 + 12) - v16) >> 2 )
  {
    v18 = *(int **)(a1 + 8);
    *v18 = a7;
    *(uint32_t *)(a1 + 8) = v18 + 1;
  }
  else
  {
    sub_430C80(a1, *(uint32_t *)(a1 + 8), 1u, &a7);
  }
  v19 = a2;
  if ( a2 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2) != 0 )
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    a4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 48))(v19);
    sub_431230(a1, &a4);
    a4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 52))(v19);
    return sub_431230(a1, &a4);
  }
  else
  {
    a4 = 0xFFFF;
    sub_431230(a1, &a4);
    a4 = 0xFFFF;
    return sub_431230(a1, &a4);
  }
}



// ------------------------------------------------------------
// 0x600AF0 CNRDPassiveObject__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNRDPassiveObject__vmt200(int *this, int a2, float *a3, char a4)
{
  int v4; // ebx
  float *v6; // edi
  int v7; // edx
  int v8; // eax
  double v9; // st7
  uint8_t v11[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]
  int v14; // [esp+18h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-18h]
  int v16; // [esp+20h] [ebp-14h]
  int v17; // [esp+24h] [ebp-10h] BYREF
  int v18; // [esp+30h] [ebp-4h]

  v4 = a2;
  v6 = a3;
  if ( *(this + 171) > 0 && a4 == 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v7 = *this;
    HIBYTE(a3) = 0;
    a2 = 100;
    v17 = 0;
    (*(void (/*thiscall*/ **)(int *, int *, int))(v7 + 648))(this, &a2, v4);
    v8 = (*(int (/*thiscall*/ **)(int *, char *, int *, int, int, float *, uint32_t))(*this + 628))(
           this,
           (char *)&a3 + 3,
           &v17,
           a2,
           v4,
           v6,
           0);
    v16 = *(this + 170) - v8;
    v15 = v8;
    Block = nullptr;
    v13 = 0;
    v14 = 0;
    v9 = v6[2];
    v18 = 0;
    sub_600920((int)v11, v4, v8, v16, (uint64_t)*v6, (uint64_t)v6[1], (uint64_t)v9);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 1, v11, 0, 0);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = 0;
    v14 = 0;
  }
  return IRDCollisionObject__vmt200(this, v4, (int)v6, a4);
}



// ------------------------------------------------------------
// 0x600C20 sub_600C20
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_600C20(size_t *this, const char *a2, size_t a3)
{
  size_t *v3; // esi
  int v4; // eax
  size_t *v5; // ebx
  unsigned int result; // eax
  size_t v7; // edi
  int v8; // eax
  size_t v9; // edx
  unsigned int **v10; // ecx
  size_t v11; // edi
  char v12; // al
  int v13; // eax
  size_t v14; // esi
  uint32_t *v15; // ecx
  unsigned int v16; // edi
  int *v17; // edx
  size_t v18; // esi
  unsigned int v19; // edx
  uint32_t *v20; // eax
  int *v21; // ecx
  int *v22; // eax
  uint32_t *v23; // edi
  uint32_t *v24; // ecx
  int v25; // eax
  unsigned int **v26; // ecx
  int v27; // esi
  int v28; // edi
  const CHAR *v29; // eax
  int v30; // eax
  void *v31; // eax
  int v32; // ebx
  int v33; // eax
  unsigned int i; // edi
  size_t v35; // ecx
  uint32_t v36[23]; // [esp+Ch] [ebp-A8h] BYREF
  void *Block; // [esp+6Ch] [ebp-48h]
  int v38; // [esp+7Ch] [ebp-38h]
  unsigned int v39; // [esp+80h] [ebp-34h]
  size_t *v40; // [esp+A4h] [ebp-10h]
  int v41; // [esp+B0h] [ebp-4h]
  unsigned int **v42; // [esp+BCh] [ebp+8h]
  unsigned int **v43; // [esp+BCh] [ebp+8h]

  v3 = this;
  v4 = *(uint32_t *)dword_8F84C8;
  v40 = this;
  v5 = (size_t *)(*(int (/*thiscall*/ **)(int, const char *))(v4 + 4))(dword_8F84C8, a2);
  if ( v5 == nullptr )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! FILENAME[%s]", a2);
  sub_4014D0(v3 + 90, v5 + 55, 0, 0xFFFFFFFF);
  v3[176] = a3;
  v3[71] = *v5;
  sub_4014D0(v3 + 72, v5 + 1, 0, 0xFFFFFFFF);
  v3[79] = v5[8];
  v3[80] = v5[9];
  v3[81] = v5[10];
  v3[27] = v5[11];
  v3[172] = v5[12];
  v3[174] = v5[13];
  sub_4ED3F0((int)(v3 + 82), (int)(v5 + 14));
  if ( sub_40BF00((std::_String_base *)(v5 + 18), 0, v5[23], szPassword, 0) != 0 )
  {
    v41 = 0;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( v5[24] < 0x10 )
        LOBYTE(v7) = (uint8_t)v5 + 76;
      else
        v7 = v5[19];
      if ( v5[61] < 0x10 )
        v8 = sub_431920((uint8_t)v5 - 32, v7, 1);
      else
        v8 = sub_431920(v5[56], v7, 1);
    }
    else
    {
      v8 = 0;
    }
    v9 = *v3;
    v41 = -1;
    (*(void (/*thiscall*/ **)(size_t *, int))(v9 + 92))(v3, v8);
  }
  v10 = (unsigned int **)v5[26];
  v42 = v10;
  if ( v10 != (unsigned int **)v5[27] )
  {
    while ( 1 )
    {
      if ( strcmp(sub_41ACF0(v10), szPassword) == 0 )
      {
        v18 = v40[36];
        v15 = v40 + 35;
        a3 = 0;
        if ( v18 != 0 )
          v19 = (int)(v40[37] - v18) >> 2;
        else
          v19 = 0;
        if ( v18 != 0 && v19 < (int)(v40[38] - v18) >> 2 )
        {
          v20 = (uint32_t *)v40[37];
          *v20 = 0;
          v15[2] = v20 + 1;
          goto LABEL_37;
        }
      }
      else
      {
        a3 = sub_42FCB0(228);
        v41 = 1;
        if ( a3 != 0 )
        {
          if ( v5[61] < 0x10 )
            LOBYTE(v11) = (uint8_t)v5 - 32;
          else
            v11 = v5[56];
          v12 = (uint8_t)sub_41ACF0(v42);
          v13 = sub_431920(v11, v12, 1);
        }
        else
        {
          v13 = 0;
        }
        v14 = v40[36];
        v15 = v40 + 35;
        v41 = -1;
        a3 = v13;
        if ( v14 != 0 )
          v16 = (int)(v40[37] - v14) >> 2;
        else
          v16 = 0;
        if ( v14 != 0 && v16 < (int)(v40[38] - v14) >> 2 )
        {
          v17 = (int *)v40[37];
          *v17 = v13;
          v15[2] = v17 + 1;
          goto LABEL_37;
        }
      }
      sub_42AC90((void *)v15[2], 1, (int)&a3);
LABEL_37:
      if ( ++v42 == (unsigned int **)v5[27] )
      {
        v3 = v40;
        break;
      }
      v10 = v42;
    }
  }
  v21 = (int *)v3[34];
  if ( v21 != nullptr )
  {
    v22 = (int *)sub_4924C0(v21, 0);
    v3[40] = sub_4918E0(v22, 2);
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 36), 0, v5[41], szPassword, 0) != 0 )
  {
    if ( v5[42] < 0x10 )
      v23 = v5 + 37;
    else
      v23 = (uint32_t *)v5[37];
    if ( v5[61] < 0x10 )
      v24 = v5 + 56;
    else
      v24 = (uint32_t *)v5[56];
    v25 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v24, v23);
    sub_4B2970(v3 + 181, v25);
  }
  v26 = (unsigned int **)v5[44];
  v43 = v26;
  if ( v26 != (unsigned int **)v5[45] )
  {
    while ( 1 )
    {
      if ( strcmp(sub_41ACF0(v26), szPassword) == 0 )
      {
        v39 = 15;
        v38 = 0;
        LOBYTE(Block) = 0;
        v41 = 2;
        sub_4A3450(v36);
        v41 = 3;
        sub_4B52F0((int)(v40 + 138), (int)v36);
        v41 = -1;
        if ( v39 >= 0x10 )
          j__free(Block);
        v39 = 15;
        v38 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        v27 = v5[61] < 0x10 ? (int)(v5 + 56) : v5[56];
        v28 = *(uint32_t *)dword_8F84E0;
        v29 = sub_41ACF0(v43);
        v30 = (*(int (**)(int, const char *, ...))(v28 + 12))(dword_8F84E0, "%s%s", v27, v29);
        sub_4B52F0((int)(v40 + 138), v30);
      }
      if ( ++v43 == (unsigned int **)v5[45] )
        break;
      v26 = v43;
    }
    v3 = v40;
  }
  sub_4ED3F0((int)(v3 + 86), (int)(v5 + 47));
  sub_41DC80((int)(v3 + 177), (int)(v5 + 51));
  if ( v5[34] != 0 )
  {
    v3 = v40;
    v31 = operator new(0x12Cu);
    v41 = 4;
    if ( v31 != nullptr )
    {
      if ( v5[35] < 0x10 )
        v32 = (int)(v5 + 30);
      else
        v32 = v5[30];
      if ( v3[96] < 0x10 )
        v33 = sub_4C3640((int)v31, (int)(v3 + 91), v32, (int)v3);
      else
        v33 = sub_4C3640((int)v31, v3[91], v32, (int)v3);
    }
    else
    {
      v33 = 0;
    }
    v41 = -1;
    v3[219] = v33;
  }
  (*(void (/*thiscall*/ **)(size_t *, uint32_t, uint32_t, int, int))(*v3 + 472))(v3, 0, 0, 1, 1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    v3[220] = *(uint32_t *)(*(uint32_t *)(result + 108) + 112);
  }
  else
  {
    result = off_77F3FC((char *)&byte_73ABD4);
  }
  for ( i = 0; ; ++i )
  {
    v35 = v3[83];
    if ( v35 == 0 )
      break;
    result = (int)(v3[84] - v35) >> 2;
    if ( i >= result )
      break;
    result = (*(int (/*thiscall*/ **)(size_t *, uint32_t))(*v3 + 464))(v3, *(uint32_t *)(v35 + 4 * i));
  }
  return result;
}


// ------------------------------------------------------------
// 0x6011B0 sub_6011B0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_6011B0(uint32_t *this, int ArgList, int a3)
{
  int v3; // edi
  const char *v5; // eax
  int *v7; // [esp+8h] [ebp-4h] BYREF

  v3 = ArgList;
  sub_442D00(&dword_9B7C48, &v7, &ArgList);
  if ( v7 == (int *)dword_9B7C4C )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! INDEX %d", v3);
  v5 = (unsigned int)v7[10] < 0x10 ? (const char *)(v7 + 5) : (const char *)v7[5];
  if ( v5 == nullptr )
    return off_77F3FC("PASSIVEOBJECT CREATE FAIL! INDEX %d", v3);
  else
    return sub_600C20(this, v5, a3);
}



// ------------------------------------------------------------
// 0x601220 sub_601220
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_601220(int this, int a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  unsigned int result; // eax
  int v10; // ecx
  int v11; // ecx
  unsigned int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // ecx
  int v17; // eax
  unsigned int v18; // edi
  char *v19; // eax
  int v20; // edi
  char *v21; // edi
  int v22; // [esp-18h] [ebp-44h]
  int v23; // [esp-Ch] [ebp-38h]
  unsigned int v24; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  v7 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( v7 != 0 )
    result = (*(uint32_t *)(this + 12) - v7) >> 4;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v10 = 0;
    if ( 0xFFFFFFF - v10 < a3 )
      sub_4F34F0(this);
    if ( v7 != 0 )
      v11 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v11 = 0;
    if ( result >= a3 + v11 )
    {
      v19 = *(char **)(this + 8);
      Blockb = v19;
      if ( (int)&v19[-a2] >> 4 >= a3 )
      {
        v21 = &v19[-16 * a3];
        *(uint32_t *)(this + 8) = sub_602460(v21, v19, v19);
        sub_4BF320(a2, v21, Blockb);
        return sub_453C20(a2, a2 + 16 * a3, v26);
      }
      else
      {
        sub_602460(a2, v19, a2 + 16 * a3);
        v24 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 4);
        v23 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(v23, v24, v26);
        v20 = 16 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v20;
        return sub_453C20(a2, v20 - 16 * a3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v7) >> 4;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
      {
        if ( v7 != 0 )
          v14 = (*(uint32_t *)(this + 8) - v7) >> 4;
        else
          v14 = 0;
        v12 = a3 + v14;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      v22 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = sub_602460(v22, a2, Blocka);
      sub_4BF340(v15, a3, v26);
      sub_602460(a2, *(uint32_t *)(this + 8), 16 * a3 + v15);
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 4;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x601480 sub_601480
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_601480(int this, uint32_t *Block)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi
  unsigned int result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 4;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) >> 4 )
    return sub_601220(this, *(char **)(this + 8), 1u, Block);
  v5 = *(uint32_t *)(this + 8);
  result = sub_4BF340(v5, 1, Block);
  *(uint32_t *)(this + 8) = v5 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x6014F0 sub_6014F0
// ------------------------------------------------------------
char /*cdecl*/ sub_6014F0(int a1, const char *ArgList)
{
  char result; // al
  int v3; // ebx
  void **v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // ebx
  unsigned int v8; // edx
  int *v9; // ecx
  int v10; // edi
  int v11; // eax
  char *v12; // esi
  void **v13; // eax
  int v14; // eax
  void **v15; // eax
  float *v16; // esi
  int i; // ebx
  int v18; // esi
  int j; // edi
  int *v20; // esi
  float *v21; // ebx
  int k; // edi
  double v23; // st7
  int v24; // eax
  const char *v25; // eax
  void *v26[3]; // [esp-1Ch] [ebp-9Ch] BYREF
  char *v27; // [esp-10h] [ebp-90h]
  int v28; // [esp-Ch] [ebp-8Ch]
  char *v29; // [esp-8h] [ebp-88h]
  char *v30; // [esp-4h] [ebp-84h]
  int v31; // [esp+Ch] [ebp-74h] BYREF
  int v32; // [esp+10h] [ebp-70h]
  int v33; // [esp+14h] [ebp-6Ch]
  int v34; // [esp+18h] [ebp-68h]
  void **v35; // [esp+1Ch] [ebp-64h] BYREF
  uint8_t v36[4]; // [esp+20h] [ebp-60h] BYREF
  void *Block; // [esp+24h] [ebp-5Ch]
  void *Src; // [esp+28h] [ebp-58h]
  int v39; // [esp+2Ch] [ebp-54h]
  int v40; // [esp+30h] [ebp-50h] BYREF
  char v41; // [esp+37h] [ebp-49h] BYREF
  char v42; // [esp+38h] [ebp-48h] BYREF
  void *v43[4]; // [esp+3Ch] [ebp-44h] BYREF
  int v44; // [esp+4Ch] [ebp-34h]
  unsigned int v45; // [esp+50h] [ebp-30h]
  int v46; // [esp+54h] [ebp-2Ch] BYREF
  void *v47; // [esp+58h] [ebp-28h] BYREF
  int v48; // [esp+68h] [ebp-18h]
  unsigned int v49; // [esp+6Ch] [ebp-14h]
  int v50; // [esp+70h] [ebp-10h]
  int v51; // [esp+7Ch] [ebp-4h]

  v50 = dword_796E50;
  result = sub_442A10((char)szPassword, (int)ArgList);
  if ( result != 0 )
  {
    v3 = a1;
    sub_4F3560(a1);
    v49 = 15;
    v48 = 0;
    LOBYTE(v47) = 0;
    v51 = 1;
    v45 = 15;
    v44 = 0;
    LOBYTE(v43[0]) = 0;
    v41 = 0;
    while ( (uint8_t)sub_443430(&v46) != 0 )
    {
      sub_442B20(&v46);
      if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[cube index]", 0xCu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[legacy info]", 0xDu) != 0 )
        {
          if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[skill info]", 0xCu) != 0 )
          {
            if ( sub_40BF00((std::_String_base *)&v46, 0, v48, "[skill prob]", 0xCu) != 0 )
            {
              if ( (uint8_t)sub_423300(&v46, "[cube creation const]") != 0 )
              {
                *(uint32_t *)(v3 + 188) = sub_4423D0(nullptr);
                v16 = (float *)(v3 + 192);
                for ( i = 4; i != 0; --i )
                  *v16++ = sub_442480(nullptr);
                v3 = a1;
              }
              else if ( (uint8_t)sub_423300(&v46, "[additional result]") != 0 )
              {
                v40 = 0;
                v18 = v3 + 272;
                do
                {
                  *(uint32_t *)v18 = sub_4423D0(&v41);
                  if ( v41 == 0 )
                    break;
                  sub_5E5260((void **)(v18 + 4));
                  for ( j = 0; j < *(uint32_t *)v18; ++j )
                  {
                    v35 = (void **)sub_4423D0(nullptr);
                    sub_431230(v18 + 4, &v35);
                  }
                  v3 = a1;
                  v18 += 20;
                  ++v40;
                }
                while ( v40 < 4 );
              }
              else if ( (uint8_t)sub_423300(&v46, "[additional result const]") != 0 )
              {
                v20 = (int *)(v3 + 232);
                v21 = (float *)(v3 + 208);
                for ( k = 4; k != 0; --k )
                {
                  v23 = sub_442480(nullptr);
                  *v21 = v23;
                  if ( v23 == 0.0 )
                  {
                    *(v20 - 1) = 0;
                    *v20 = 0;
                  }
                  else
                  {
                    v24 = sub_4423D0(nullptr);
                    v29 = nullptr;
                    *(v20 - 1) = v24;
                    *v20 = sub_4423D0(v29);
                  }
                  ++v21;
                  v20 += 3;
                }
                v3 = a1;
              }
              else
              {
                v35 = v26;
                sub_401690(&v46);
                if ( (uint8_t)sub_442C80((char)v26[0], v26[1], (int)v26[2], (int)v27, v28, (int)v29, (int)v30) == 0 )
                {
                  v25 = (const char *)v47;
                  if ( v49 < 0x10 )
                    v25 = (const char *)&v47;
                  off_77F3FC("SCRIPT TAG ERROR! [%s] %s", ArgList, v25);
                }
              }
            }
            else
            {
              *(float *)(v3 + 180) = sub_442480(nullptr);
              *(float *)(v3 + 184) = sub_442480(nullptr);
            }
          }
          else
          {
            if ( *(uint32_t *)(v3 + 168) != 0 )
              j__free(*(void **)(v3 + 168));
            v30 = nullptr;
            *(uint32_t *)(v3 + 168) = 0;
            *(uint32_t *)(v3 + 172) = 0;
            *(uint32_t *)(v3 + 176) = 0;
            *(uint32_t *)(v3 + 160) = sub_4423D0(v30);
            v31 = 4;
            v34 = 4;
            v29 = &v42;
            v32 = 0;
            v33 = 0;
            if ( sub_443370() != 0 )
            {
              do
              {
                v13 = (void **)v43[0];
                if ( v45 < 0x10 )
                  v13 = v43;
                v31 = sub_4426A0(v13);
                v32 = sub_4423D0(nullptr);
                v14 = sub_4423D0(nullptr);
                v27 = &v42;
                v33 = v14;
                sub_443370();
                v15 = (void **)v43[0];
                if ( v45 < 0x10 )
                  v15 = v43;
                v34 = sub_442710(v15);
                sub_601480(&v31);
                v30 = &v42;
              }
              while ( sub_443370() != 0 );
              v3 = a1;
            }
          }
        }
        else
        {
          v10 = sub_4423D0(nullptr);
          Block = nullptr;
          Src = nullptr;
          v39 = 0;
          LOBYTE(v51) = 2;
          v11 = sub_4423D0(&v41);
          v40 = v11;
          if ( v41 != 0 )
          {
            do
            {
              v12 = (char *)Src;
              if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v39 - (int)Block) >> 2) )
              {
                *(uint32_t *)Src = v11;
                Src = v12 + 4;
              }
              else
              {
                sub_430C80(Src, 1, (int)&v40);
              }
              v11 = sub_4423D0(&v41);
              v40 = v11;
            }
            while ( v41 != 0 );
            v3 = a1;
          }
          if ( v10 - 1 < 4 )
            sub_4F6540(v3 + 4 * (5 * v10 + 15), v36);
          LOBYTE(v51) = 1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          Src = nullptr;
          v39 = 0;
        }
      }
      else
      {
        v30 = &v42;
        sub_443370();
        v4 = (void **)v43[0];
        if ( v45 < 0x10 )
          v4 = v43;
        v5 = 16 * sub_442710(v4) + v3;
        if ( *(uint32_t *)(v5 + 4) != 0 )
          j__free(*(void **)(v5 + 4));
        v30 = &v41;
        *(uint32_t *)(v5 + 4) = 0;
        *(uint32_t *)(v5 + 8) = 0;
        *(uint32_t *)(v5 + 12) = 0;
        v6 = sub_4423D0(v30);
        v40 = v6;
        if ( v41 != 0 )
        {
          do
          {
            v7 = *(uint32_t *)(v5 + 4);
            if ( v7 != 0 )
              v8 = (*(uint32_t *)(v5 + 8) - v7) >> 2;
            else
              v8 = 0;
            if ( v7 != 0 && v8 < (*(uint32_t *)(v5 + 12) - v7) >> 2 )
            {
              v9 = *(int **)(v5 + 8);
              *v9 = v6;
              *(uint32_t *)(v5 + 8) = v9 + 1;
            }
            else
            {
              sub_430C80(*(void **)(v5 + 8), 1, (int)&v40);
            }
            v6 = sub_4423D0(&v41);
            v40 = v6;
          }
          while ( v41 != 0 );
          v3 = a1;
        }
      }
    }
    if ( v45 >= 0x10 )
      j__free(v43[0]);
    v45 = 15;
    v44 = 0;
    LOBYTE(v43[0]) = 0;
    if ( v49 >= 0x10 )
      j__free(v47);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x601A50 sub_601A50
// ------------------------------------------------------------
void /*thiscall*/ sub_601A50(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0xFFFF;
}



// ------------------------------------------------------------
// 0x601A70 CNStorageBird__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNStorageBird__vmtC(int this)
{
  int v2; // edi
  int v3; // eax
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  v2 = *(uint32_t *)(this + 112);
  v3 = *(uint32_t *)this;
  *(uint32_t *)(this + 972) = 1;
  result = -(*(int (/*thiscall*/ **)(int, uint32_t))(v3 + 384))(this, 0);
  *(uint32_t *)(v2 + 36) = result;
  *(uint32_t *)(*(uint32_t *)(this + 112) + 112) = 2;
  *(uint8_t *)(this + 700) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x601AB0 sub_601AB0
// ------------------------------------------------------------
char /*thiscall*/ sub_601AB0(uint8_t *this)
{
  int v2; // eax

  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  if ( v2 >= 900 )
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
// 0x601AF0 CNFallingStorage__vmt138
// ------------------------------------------------------------
char /*thiscall*/ CNFallingStorage__vmt138(char *this, int a2)
{
  return CNRDObject__vmt138(this, 1);
}



// ------------------------------------------------------------
// 0x601B00 sub_601B00
// ------------------------------------------------------------
char /*thiscall*/ sub_601B00(uint8_t *this)
{
  int v2; // eax

  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this);
    if ( v2 == dword_8F7C04 )
    {
      LOBYTE(v2) = *(this + 264);
      if ( (uint8_t)v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 312))(this, 1);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x601B40 CNFallingStorage__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNFallingStorage__vmt12C(uint32_t *this, int a2)
{
  if ( (uint32_t *)a2 == this )
    dword_9B7C88 = 0;
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x601B60 sub_601B60
// ------------------------------------------------------------
int /*thiscall*/ sub_601B60(uint32_t *this, int a2)
{
  *(this + 245) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x601B70 sub_601B70
// ------------------------------------------------------------
char /*thiscall*/ sub_601B70(void *this, int a2)
{
  int *v3; // ecx

  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -100,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -200,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  v3 = *((int **)this + 36);
  *((uint32_t *)this + 245) = a2;
  sub_493400(*v3, a2);
  return sub_4939E0(**((uint32_t **)this + 36), 1);
}



// ------------------------------------------------------------
// 0x601BE0 sub_601BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_601BE0(uint32_t **this, uint32_t *a2)
{
  uint32_t *v3; // edx
  int v4; // eax
  int v5; // eax

  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(this, 100, **(this + 36), 0, 0, 0);
  v3 = *this;
  *(this + 244) = a2;
  v4 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t *))v3[50])(this, a2);
  sub_493400(v4, 0);
  v5 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[50])(this);
  return sub_4939E0(v5, 1);
}



// ------------------------------------------------------------
// 0x601C40 sub_601C40
// ------------------------------------------------------------
int /*thiscall*/ sub_601C40(uint32_t *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // [esp-24h] [ebp-28h]
  int v9; // [esp-1Ch] [ebp-20h]
  int v10; // [esp-18h] [ebp-1Ch]
  int v11; // [esp-14h] [ebp-18h]
  int v12; // [esp-Ch] [ebp-10h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( result <= 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 4),
      0,
      0,
      0,
      0);
    v6 = *(this + 28);
    *(this + 243) = 2;
    *(uint32_t *)(v6 + 36) = 0;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == dword_8F7C04 )
    {
      dword_9B7C88 = (int)this;
      sub_44E8D0((char *)dword_8F8528, (void *)0xF, 0, 0);
    }
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 152))(this, 0);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      v9 = *(this + 244);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      return sub_4E4A50(v7, v8, 2, v9, v10, v11, 0, v12, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601D40 sub_601D40
// ------------------------------------------------------------
int /*thiscall*/ sub_601D40(int *this)
{
  int result; // eax
  int v3; // ecx

  result = *(this + 36);
  *(this + 243) = 3;
  v3 = *(uint32_t *)(result + 8);
  if ( v3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, v3);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             100,
             *(uint32_t *)(*(this + 36) + 12),
             0,
             0,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x601DA0 CNStorageSub__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNStorageSub__vmtC(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmtC(this);
  switch ( *(this + 245) )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
      break;
    case 1:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);
      break;
    case 2:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 304);
      break;
    case 3:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 456);
      break;
    default:
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, 0);
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x601E40 sub_601E40
// ------------------------------------------------------------
int /*thiscall*/ sub_601E40(uint32_t *this)
{
  int v2; // edi
  int result; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // [esp-20h] [ebp-28h]
  int v12; // [esp-1Ch] [ebp-24h]
  int v13; // [esp-18h] [ebp-20h]
  int v14; // [esp-14h] [ebp-1Ch]
  int v15; // [esp-Ch] [ebp-14h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( result < v2 )
  {
    v4 = *this;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 112))(this, v7);
    v8 = *(this + 28);
    v9 = *this;
    *(this + 243) = 2;
    *(uint32_t *)(v8 + 36) = 10 * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v9 + 384))(this, 0);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == dword_8F7C04 )
    {
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 152))(this, 0);
      v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this) - 79;
      v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      v11 = *(this + 245);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      result = sub_4E4A50(v10, 51201, v11, v12, v13, v14, 1, v15, 0, 0);
      *(this + 244) = result;
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601F40 CNStorageBird__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNStorageBird__vmt128(uint32_t *this, int a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 33);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
    if ( result == *(this + 244) )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x601FA0 CNFallingStorage__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNFallingStorage__vmt10(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt10(this);
  result = *(this + 243);
  if ( result != 0 )
  {
    v3 = result - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 2 )
        sub_601B00(this);
    }
    else
    {
      sub_601C40(this);
    }
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result <= 0 )
    {
      v4 = *this;
      v5 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
      return (*(int (/*thiscall*/ **)(int *, int))(v4 + 112))(this, v6);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602000 CNStorageBird__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNStorageBird__vmt10(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax

  CNRDPassiveObject__vmt10(this);
  result = *(this + 243);
  if ( result != 0 )
  {
    v3 = result - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        sub_601AB0(this);
    }
    else
    {
      sub_601E40(this);
    }
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result < v4 )
    {
      v5 = *this;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v7);
      return (*(int (/*thiscall*/ **)(int *, int))(v5 + 112))(this, v8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602070 sub_602070
// ------------------------------------------------------------
int /*thiscall*/ sub_602070(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 96) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x602090 CNChangeMp__vmt1C
// ------------------------------------------------------------
int /*thiscall*/ CNChangeMp__vmt1C(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // [esp+4h] [ebp-8h]
  int v13; // [esp+8h] [ebp-4h]

  v2 = *(this + 1);
  *(this + 22) = 0;
  if ( v2 != 0 && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || v2 == dword_8F7C04) )
  {
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 124))(*(this + 1));
    v4 = *(this + 1);
    v13 = v3;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 192))(v4);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4);
    sub_4D7960(v6 + v5, v4, (int)this, v12, v13, v6 + v5, *(this + 20), 3, 0, 0);
  }
  *((uint8_t *)this + 96) = 0;
  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 4 || result == 6 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);
    v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 32) + 576))(*(uint32_t *)(v8 + 32));
    result = __RTDynamicCast(v9, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    if ( result == dword_8F7C04 )
    {
      v10 = *(this + 1);
      if ( v10 != dword_8F7C04 )
      {
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 273);
        if ( (uint8_t)result != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
          return sub_496010((int)dword_99FD58, v11, 11, 1);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602190 CNChangeMp__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNChangeMp__vmt54(int this, char a2)
{
  char result; // al
  int v4; // ecx

  result = IRDAppendage__vmt54((uint8_t *)this, a2);
  v4 = *(uint32_t *)(this + 92);
  if ( v4 != 0 )
    return sub_4939E0(v4, a2);
  return result;
}



// ------------------------------------------------------------
// 0x6021C0 CNChangeMp__vmt14
// ------------------------------------------------------------
char /*thiscall*/ CNChangeMp__vmt14(int *this, char a2, int a3, int a4, int a5)
{
  char result; // al
  int v6; // ecx

  result = a2;
  if ( a2 != 0 )
  {
    v6 = *(this + 23);
    if ( v6 != 0 )
    {
      sub_4938F0(v6);
      return sub_491D00(dword_79C0B0, a3, a4 - 60, 0.0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602200 CNChangeMp__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNChangeMp__vmt4(int this)
{
  int v2; // edi
  int v3; // eax
  uint64_t v4; // rax
  int v5; // ecx
  int v6; // edi
  int *v7; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // edx
  int v13; // ebx
  int v14; // eax
  int *v15; // ecx
  int v16; // eax
  void *v17; // eax
  int v18; // ecx
  int result; // eax
  float v20; // [esp+0h] [ebp-38h]
  int v21; // [esp+0h] [ebp-38h]
  int v22; // [esp+4h] [ebp-34h]
  void *v23[4]; // [esp+18h] [ebp-20h] BYREF
  int v24; // [esp+28h] [ebp-10h]
  int v25; // [esp+34h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  v2 = *(uint32_t *)(this + 84);
  v3 = sub_699000(this + 8);
  v24 = *(uint32_t *)(this + 80);
  v20 = (float)v24;
  v4 = (uint64_t)sub_4049C0(0.0, v20, v3, v2);
  v5 = *(uint32_t *)(this + 88);
  if ( (uint32_t)v4 != v5 )
  {
    v6 = v4 - v5;
    v7 = *(int **)(this + 4);
    *(uint32_t *)(this + 88) = v4;
    v8 = *v7;
    v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v7 + 752))(v7, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 744))(*(uint32_t *)(this + 4), v6 + v9);
  }
  v10 = *(uint32_t *)(this + 92);
  if ( v10 != 0 && *(int *)(v10 + 148) >= 4 && *(uint8_t *)(this + 96) == 0 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04 )
    {
      v11 = dword_8F82B4;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82B4 + 12))(dword_8F82B4);
      v12 = **(uint32_t **)(this + 4);
      v13 = *(uint32_t *)v11;
      v24 = *(uint32_t *)(this + 4);
      v22 = (*(int (**)(void))(v12 + 128))() + 60;
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 124))(v24);
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 120))(v24);
      (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(v11, v14);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v11 + 92))(v11, v23);
      v15 = *(int **)(this + 4);
      v16 = *v15;
      v25 = 0;
      v17 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v16 + 80))(v15, 2, 0, v23);
      sub_4600B0(v17, v21, v22, 0);
      v25 = -1;
      sub_5E5260(v23);
    }
    v18 = *(uint32_t *)(this + 4);
    *(uint8_t *)(this + 96) = 1;
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v18 + 212))(
      v18,
      "MP_RECOVERED",
      -1,
      0,
      0);
  }
  result = *(uint32_t *)(this + 88);
  if ( result == *(uint32_t *)(this + 80) )
  {
    result = *(uint32_t *)(this + 92);
    if ( result == 0 || *(uint8_t *)(result + 170) != 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x602380 sub_602380
// ------------------------------------------------------------
int /*thiscall*/ sub_602380(uint32_t *this, int a2, int a3)
{
  int result; // eax
  int v5; // eax

  result = a2;
  *(this + 20) = a2;
  *(this + 21) = a3;
  if ( a2 > 0 )
  {
    v5 = sub_42FCB0(228);
    if ( v5 != 0 )
    {
      result = sub_431860(v5, "Common/CommonEffect/Animation/MpUp.ani", 1);
      *(this + 23) = result;
    }
    else
    {
      *(this + 23) = 0;
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602400 sub_602400
// ------------------------------------------------------------
int /*thiscall*/ sub_602400(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 23);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 23));
    result = sub_657740(v2, 228);
  }
  *(this + 23) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x602430 sub_602430
// ------------------------------------------------------------
int /*thiscall*/ sub_602430(int this)
{
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 184) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x602440 sub_602440
// ------------------------------------------------------------
int /*thiscall*/ sub_602440(int this, int a2, char a3)
{
  *(uint32_t *)(this + 180) = a2;
  *(uint8_t *)(this + 184) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x602460 sub_602460
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_602460(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 4 )
  {
    if ( result != nullptr )
    {
      *result = *v3;
      result[1] = v3[1];
      result[2] = v3[2];
      result[3] = v3[3];
    }
    v3 += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6024A0 sub_6024A0
// ------------------------------------------------------------
void /*noreturn*/ sub_6024A0()
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
// 0x602510 sub_602510
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602510(int this, int a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  unsigned int result; // eax
  int v10; // ecx
  int v11; // ecx
  unsigned int v12; // eax
  int v13; // ecx
  int v14; // eax
  uint32_t *v15; // ebx
  int v16; // ecx
  int v17; // eax
  unsigned int v18; // edi
  void *v19; // eax
  int v20; // edi
  int v21; // edi
  int v22; // [esp-18h] [ebp-44h]
  int v23; // [esp-Ch] [ebp-38h]
  unsigned int v24; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  v7 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( v7 != 0 )
    result = (*(uint32_t *)(this + 12) - v7) >> 4;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v10 = 0;
    if ( 0xFFFFFFF - v10 < a3 )
      sub_50F360(this);
    if ( v7 != 0 )
      v11 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v11 = 0;
    if ( result >= a3 + v11 )
    {
      v19 = *(void **)(this + 8);
      Blockb = v19;
      if ( ((int)v19 - a2) >> 4 >= a3 )
      {
        v21 = (int)v19 - 16 * a3;
        *(uint32_t *)(this + 8) = sub_602460(v21, v19, v19);
        sub_4BF320(a2, v21, (int)Blockb);
        return sub_453C20(a2, a2 + 16 * a3, v26);
      }
      else
      {
        sub_602460(a2, v19, a2 + 16 * a3);
        v24 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 4);
        v23 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(v23, v24, v26);
        v20 = 16 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v20;
        return sub_453C20(a2, v20 - 16 * a3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v7) >> 4;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
      {
        if ( v7 != 0 )
          v14 = (*(uint32_t *)(this + 8) - v7) >> 4;
        else
          v14 = 0;
        v12 = a3 + v14;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      v22 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = (uint32_t *)sub_602460(v22, a2, Blocka);
      sub_4BF340(v15, (uint32_t *)a3, v26);
      sub_602460(a2, *(uint32_t *)(this + 8), &v15[4 * a3]);
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 4;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x602770 sub_602770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_602770(uint32_t *this, char a2, void *Block)
{
  sub_4B1030(this);
  *this = &vftbl_CNRemoveActiveStatus;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  sub_651AE0(this);
  sub_651F70(a2, Block);
  return this;
}



// ------------------------------------------------------------
// 0x6027E0 CNRemoveActiveStatus__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRemoveActiveStatus__vmt0(void *Block, char a2)
{
  sub_602810();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x602810 sub_602810
// ------------------------------------------------------------
int /*thiscall*/ sub_602810(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRemoveActiveStatus;
  sub_651AF0();
  if ( *(uint32_t *)(this + 88) != 0 )
    j__free(*(void **)(this + 88));
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint8_t *)(this + 12) = 0;
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x602890 sub_602890
// ------------------------------------------------------------
int /*thiscall*/ sub_602890(uint32_t *this, void *Block)
{
  int result; // eax
  int i; // esi
  int v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 308))(Block);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 43);
    for ( i = *(this + 42); i != result; i += 16 )
    {
      v5 = *(uint32_t *)(i + 8);
      if ( v5 == -1 )
      {
        v6 = operator new(0x68u);
        if ( v6 != nullptr )
          v7 = sub_602770(v6, *(uint32_t *)i, (void *)*(uint8_t *)(i + 12));
        else
          v7 = nullptr;
        (*(void (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, uint32_t, int))(*v7 + 56))(
          v7,
          Block,
          Block,
          0,
          0,
          0,
          -1);
      }
      else
      {
        (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, void *, uint32_t))(*(uint32_t *)Block + 760))(
          Block,
          *(uint32_t *)i,
          *(uint32_t *)(i + 4),
          v5,
          Block,
          0);
      }
      result = *(this + 43);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x602960 sub_602960
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602960(int this, uint32_t *Block)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi
  unsigned int result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 4;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) >> 4 )
    return sub_602510(this, *(char **)(this + 8), 1u, Block);
  v5 = *(uint32_t *)(this + 8);
  result = sub_4BF340(v5, 1, Block);
  *(uint32_t *)(this + 8) = v5 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x6029D0 CNActiveStatusStackable__vmt88
// ------------------------------------------------------------
int /*thiscall*/ sub_6029D0(int this, int *Block, int a3, int a4)
{
  int *v6; // esi
  int result; // eax
  int v8; // edx
  int v9; // edi
  int v10; // eax
  unsigned int v11; // edx
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // edi
  uint64_t v16; // rax
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // eax
  int v24; // [esp-8h] [ebp-2Ch]
  int v25; // [esp+Ch] [ebp-18h] BYREF
  int v26; // [esp+10h] [ebp-14h]
  int v27; // [esp+14h] [ebp-10h]
  int v28; // [esp+18h] [ebp-Ch]
  int v29; // [esp+1Ch] [ebp-8h]
  int v30; // [esp+20h] [ebp-4h]
  int Blocka; // [esp+2Ch] [ebp+8h]
  int v32; // [esp+30h] [ebp+Ch]
  int v33; // [esp+34h] [ebp+10h]

  v30 = this;
  sub_578100(Block, a3, a4);
  v6 = nullptr;
  if ( *(uint32_t *)(this + 180) == 0 )
  {
    result = *(uint8_t *)(this + 184);
    if ( (uint8_t)result == 0 )
      return sub_602890(Block);
    return result;
  }
  v8 = *Block;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v28 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 80))(Block);
  v10 = *(uint32_t *)(v9 + 120);
  v33 = v9;
  if ( v10 != 0 )
    Blocka = (*(uint32_t *)(v9 + 124) - v10) >> 2;
  else
    Blocka = 0;
  result = Blocka;
  v11 = 0;
  v32 = 0;
  if ( Blocka > 0 )
  {
    while ( 1 )
    {
      v12 = *(uint32_t *)(v9 + 120);
      if ( v12 != 0 && v11 < (*(uint32_t *)(v9 + 124) - v12) >> 2 )
        v6 = *(int **)(v12 + 4 * v11);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(int *))(*Block + 376))(Block);
        if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6) == v13 )
        {
          v14 = v30;
          if ( *(uint8_t *)(v30 + 184) == 0 || v6 != Block )
          {
            v15 = 0;
            while ( 1 )
            {
              if ( v15 != 0 )
              {
                if ( v15 == 1 )
                {
                  v29 = 2 * *(uint32_t *)(v14 + 180);
                  v18 = (double)v29;
                  v16 = (uint64_t)(0.88 * v18);
                  v17 = v18 * 0.2552;
                }
                else
                {
                  if ( v15 != 2 )
                    goto LABEL_26;
                  v29 = 2 * *(uint32_t *)(v14 + 180);
                  v19 = (double)v29;
                  v16 = (uint64_t)(0.60000002 * v19);
                  v17 = v19 * 0.28999999;
                }
              }
              else
              {
                LODWORD(v16) = 2 * *(uint32_t *)(v14 + 180);
                v29 = v16;
                v17 = (double)(int)v16 * 0.17399999;
              }
              v27 = v16;
              v28 = (uint64_t)v17;
LABEL_26:
              v20 = (*(int (/*thiscall*/ **)(int *))(*Block + 120))(Block);
              v21 = *Block;
              v25 = v20 - v27 / 2;
              v22 = (*(int (/*thiscall*/ **)(int *))(v21 + 124))(Block);
              v26 = v22 - v28 / 2;
              v24 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
              v23 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
              if ( (uint8_t)sub_48C0A0(v23, v24, &v25) != 0 )
              {
                sub_602890(v6);
                break;
              }
              if ( ++v15 >= 3 )
                break;
              v14 = v30;
            }
          }
        }
        v9 = v33;
      }
      result = ++v32;
      if ( v32 >= Blocka )
        return result;
      v11 = v32;
      v6 = nullptr;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x602BC0 sub_602BC0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602BC0(void *this, int a2, int a3, int a4, char a5)
{
  uint32_t Block[3]; // [esp+0h] [ebp-10h] BYREF
  char v7; // [esp+Ch] [ebp-4h]

  Block[0] = a2;
  Block[2] = a4;
  Block[1] = a3;
  v7 = a5;
  return sub_602960((int)this + 164, Block);
}



// ------------------------------------------------------------
// 0x602C00 sub_602C00
// ------------------------------------------------------------
int /*thiscall*/ sub_602C00(uint32_t *this, int a2)
{
  CNRDStackable__vmt88(*(this + 41), *(this + 42), *(this + 43));
  return sub_487000(a2);
}



// ------------------------------------------------------------
// 0x602C40 CNIncreaseStatusStackable__vmt88
// ------------------------------------------------------------
void */*thiscall*/ CNIncreaseStatusStackable__vmt88(int *this, int a2, int a3, int a4)
{
  int v5; // edi
  void *result; // eax
  uint32_t *v7; // esi
  char *v8; // eax
  int v9; // eax
  int v10; // edx
  uint32_t v11[3]; // [esp+8h] [ebp-Ch] BYREF

  *(this + 41) = a2;
  *(this + 42) = a3;
  *(this + 43) = a4;
  v5 = -1;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 308))(a2) == 0
    || *(this + 32) == 0
    || (result = (void *)sub_484E80(*(this + 3)), v5 = (int)result, result != (void *)-1) )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
    {
      v7 = *((uint32_t **)dword_8F8528 + 7);
      v8 = sub_422E70(1201);
      sub_43BEE0(v7, (int)v8, -6567706, 0, -1);
      return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    }
    v9 = *(this + 3);
    if ( v9 > 4082 )
    {
      if ( v9 < 4087 || v9 > 4102 )
        return (void *)sub_602C00(this, v5);
    }
    else if ( v9 < 4079 && v9 != 3 && (v9 <= 4040 || v9 > 4052) )
    {
      return (void *)sub_602C00(this, v5);
    }
    v10 = *this;
    v11[0] = this;
    v11[2] = v5;
    v11[1] = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 16))(this) + 4);
    return (void *)sub_44E8D0((char *)dword_8F8528, (void *)0x31, (int)v11, v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x602D50 CNItemScreamOfHysma__vmt88
// ------------------------------------------------------------
int /*stdcall*/ CNItemScreamOfHysma__vmt88(int a1, int a2, int a3)
{
  int result; // eax

  CNRDStackable__vmt88(a1, a2, a3);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 580))(
             a1,
             48001,
             2,
             0,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x602DA0 sub_602DA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_602DA0(int this, int a2, float a3, int a4)
{
  uint64_t result; // rax

  *(uint32_t *)(this + 180) = a2;
  result = (uint64_t)(a3 * 100.0);
  *(uint32_t *)(this + 188) = a4;
  *(float *)(this + 184) = (float)(int)result;
  return result;
}



// ------------------------------------------------------------
// 0x602DE0 sub_602DE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_602DE0(uint32_t *this)
{
  unsigned int i; // ebx
  int v3; // ecx
  unsigned int result; // eax
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 42);
    if ( v3 == 0 )
      break;
    result = (*(this + 43) - v3) >> 3;
    if ( i >= result )
      break;
    v5 = *(void (/*thiscall*/ ****)(uint32_t, int))(v3 + 8 * i);
    if ( v5 != nullptr )
      (**v5)(v5, 1);
    result = 8 * i + *(this + 42);
    *(uint32_t *)result = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x602E40 sub_602E40
// ------------------------------------------------------------
void /*thiscall*/ sub_602E40(int this)
{
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
}



// ------------------------------------------------------------
// 0x602E80 sub_602E80
// ------------------------------------------------------------
void /*thiscall*/ sub_602E80(int this, int a2, unsigned int a3, int a4)
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
      sub_50F360(this);
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
// 0x6030D0 CNAppendageStackable__vmt88
// ------------------------------------------------------------
void /*thiscall*/ CNAppendageStackable__vmt88(int this, int a2, int a3, unsigned int Seed)
{
  int v5; // ecx
  unsigned int i; // ebx
  int v7; // ecx
  int v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax

  CNRDStackable__vmt88(a2, a3, Seed);
  v5 = *(uint32_t *)(this + 168);
  if ( v5 != 0 && (*(uint32_t *)(this + 172) - v5) >> 3 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v7 = *(uint32_t *)(this + 168);
      if ( v7 == 0 || i >= (*(uint32_t *)(this + 172) - v7) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(v7 + 8 * i) + 56))(
        *(uint32_t *)(v7 + 8 * i),
        a2,
        a2,
        0,
        0,
        *(uint32_t *)(*(uint32_t *)(this + 168) + 8 * i + 4),
        -1);
    }
    if ( *(uint32_t *)(this + 168) != 0 )
      j__free(*(void **)(this + 168));
    *(uint32_t *)(this + 168) = 0;
    *(uint32_t *)(this + 172) = 0;
    *(uint32_t *)(this + 176) = 0;
  }
  srand(Seed);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 308))(a2) != 0
    && *(uint32_t *)(this + 180) != 17
    && (double)(rand() % 10000) < *(float *)(this + 184) )
  {
    v8 = *(uint32_t *)(this + 188);
    if ( v8 == -1 )
    {
      v9 = operator new(0x68u);
      if ( v9 != nullptr )
        v10 = sub_602770(v9, *(uint32_t *)(this + 180), (void *)1);
      else
        v10 = nullptr;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*v10 + 56))(v10, a2, a2, 0, 0, 0, -1);
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)a2 + 760))(
        a2,
        *(uint32_t *)(this + 180),
        1120403456,
        v8,
        a2,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x603260 sub_603260
// ------------------------------------------------------------
void /*thiscall*/ sub_603260(int this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_63A7C0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_602E80(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x6032D0 sub_6032D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6032D0(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_603260((int)this + 164, (int)v3);
}



// ------------------------------------------------------------
// 0x603300 sub_603300
// ------------------------------------------------------------
int /*thiscall*/ sub_603300(void *this, int a2, uint32_t *a3, int a4)
{
  int v4; // edi
  int v5; // esi
  uint32_t *v6; // ebx
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // edx
  int v10; // edi
  int result; // eax
  uint32_t v12[2]; // [esp+0h] [ebp-8h] BYREF
  int v13; // [esp+14h] [ebp+Ch]

  if ( a4 > 0 )
  {
    v4 = a2 - (uint32_t)a3;
    v5 = (int)this + 164;
    v6 = a3;
    v13 = a2 - (uint32_t)a3;
    do
    {
      v7 = *(uint32_t *)((char *)v6 + v4);
      v12[1] = *v6;
      v8 = *(uint32_t *)(v5 + 4);
      v12[0] = v7;
      if ( v8 != 0 )
        v9 = (*(uint32_t *)(v5 + 8) - v8) >> 3;
      else
        v9 = 0;
      if ( v8 != 0 && v9 < (*(uint32_t *)(v5 + 12) - v8) >> 3 )
      {
        v10 = *(uint32_t *)(v5 + 8);
        sub_63A7C0(v10, 1, v12);
        *(uint32_t *)(v5 + 8) = v10 + 8;
        v4 = v13;
      }
      else
      {
        sub_602E80(v5, *(char **)(v5 + 8), 1u, (int)v12);
      }
      ++v6;
      result = --a4;
    }
    while ( a4 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x6033B0 sub_6033B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6033B0(int *this, int a2, int a3)
{
  int i; // esi
  int v5; // eax
  int v6; // edi
  int result; // eax
  unsigned int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v16; // [esp+18h] [ebp+8h]
  int v17; // [esp+1Ch] [ebp+Ch]

  for ( i = 0; i < 17; ++i )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 776))(a2, i) != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 772))(a2, i);
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v5 + 4))(v5, 0, a3);
    }
  }
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
  result = *(uint32_t *)(v6 + 4);
  v8 = 0;
  if ( result != 0 )
    v16 = (*(uint32_t *)(v6 + 8) - result) >> 2;
  else
    v16 = 0;
  v17 = 0;
  if ( v16 > 0 )
  {
    do
    {
      v9 = *(uint32_t *)(v6 + 4);
      if ( v9 != 0 && v8 < (*(uint32_t *)(v6 + 8) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v8);
      else
        v10 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 92))(v10) != 0 )
      {
        v11 = *(uint32_t *)(v6 + 4);
        if ( v11 != 0 && v8 < (*(uint32_t *)(v6 + 8) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * v8);
        else
          v12 = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v12 + 76))(v12, 0);
        v13 = *(this + 41);
        v14 = ++v17;
        if ( v13 > 0 && v14 >= v13 )
          break;
      }
      ++v8;
    }
    while ( (int)v8 < v16 );
    result = v17;
    if ( v17 > 0 )
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 956))(a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6034A0 CNOmozzaOfWorld__vmt88
// ------------------------------------------------------------
char /*thiscall*/ sub_6034A0(int this, int *a2, int a3, int a4)
{
  int *v6; // esi
  char result; // al
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ecx
  unsigned int v12; // edx
  int v13; // ecx
  int v14; // edi
  int v15; // eax
  int v16; // edi
  uint64_t v17; // rax
  double v18; // st7
  double v19; // st7
  double v20; // st7
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // [esp-8h] [ebp-2Ch]
  int v26; // [esp+Ch] [ebp-18h] BYREF
  int v27; // [esp+10h] [ebp-14h]
  int v28; // [esp+14h] [ebp-10h]
  int v29; // [esp+18h] [ebp-Ch]
  int v30; // [esp+1Ch] [ebp-8h]
  int v31; // [esp+20h] [ebp-4h]
  int v32; // [esp+2Ch] [ebp+8h]
  signed int v33; // [esp+30h] [ebp+Ch]
  int v34; // [esp+34h] [ebp+10h]

  v31 = this;
  sub_578100(a2, a3, a4);
  v6 = nullptr;
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*a2 + 212))(a2, "USE_DEBUFF", -1, 0, 0);
  if ( *(uint32_t *)(this + 168) == 0 )
  {
    result = *(uint8_t *)(this + 172);
    if ( result == 0 )
      return sub_6033B0(a2, a2);
    return result;
  }
  v8 = *a2;
  v26 = 0;
  v27 = 0;
  v28 = 0;
  v29 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 80))(a2);
  v10 = v9;
  v11 = *(uint32_t *)(v9 + 120);
  v34 = v9;
  if ( v11 != 0 )
    v32 = (*(uint32_t *)(v9 + 124) - v11) >> 2;
  else
    v32 = 0;
  result = v32;
  v12 = 0;
  v33 = 0;
  if ( v32 > 0 )
  {
    while ( 1 )
    {
      v13 = *(uint32_t *)(v10 + 120);
      if ( v13 != 0 && v12 < (*(uint32_t *)(v10 + 124) - v13) >> 2 )
        v6 = *(int **)(v13 + 4 * v12);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) != 0 )
      {
        v14 = (*(int (/*thiscall*/ **)(int *))(*a2 + 376))(a2);
        if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6) == v14 )
        {
          v15 = v31;
          if ( *(uint8_t *)(v31 + 172) == 0 || v6 != a2 )
          {
            v16 = 0;
            while ( 1 )
            {
              if ( v16 != 0 )
              {
                if ( v16 == 1 )
                {
                  v30 = 2 * *(uint32_t *)(v15 + 168);
                  v19 = (double)v30;
                  v17 = (uint64_t)(0.88 * v19);
                  v18 = v19 * 0.2552;
                }
                else
                {
                  if ( v16 != 2 )
                    goto LABEL_26;
                  v30 = 2 * *(uint32_t *)(v15 + 168);
                  v20 = (double)v30;
                  v17 = (uint64_t)(0.60000002 * v20);
                  v18 = v20 * 0.28999999;
                }
              }
              else
              {
                LODWORD(v17) = 2 * *(uint32_t *)(v15 + 168);
                v30 = v17;
                v18 = (double)(int)v17 * 0.17399999;
              }
              v28 = v17;
              v29 = (uint64_t)v18;
LABEL_26:
              v21 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2);
              v22 = *a2;
              v26 = v21 - v28 / 2;
              v23 = (*(int (/*thiscall*/ **)(int *))(v22 + 124))(a2);
              v27 = v23 - v29 / 2;
              v25 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
              v24 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
              if ( sub_48C0A0(v24, v25, &v26) )
              {
                sub_6033B0(v6, a2);
                break;
              }
              if ( ++v16 >= 3 )
                break;
              v15 = v31;
            }
          }
        }
        v10 = v34;
      }
      result = ++v33;
      if ( v33 >= v32 )
        return result;
      v12 = v33;
      v6 = nullptr;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6036B0 CNUsableStackable__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNUsableStackable__vmt88(int *this, int a2, int a3, int a4)
{
  int v4; // eax
  uint32_t *v5; // esi
  char *v6; // eax
  int result; // eax
  uint32_t *v8; // esi
  char *v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edx

  v4 = *(this + 3);
  if ( v4 < 14 || v4 > 15 )
    goto LABEL_7;
  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
  {
    v5 = *((uint32_t **)dword_8F8528 + 7);
    v6 = sub_422E70(1201);
    sub_43BEE0(v5, (int)v6, -6567706, 0, -1);
    return (int)sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
  }
  if ( *((uint32_t *)dword_8F8528 + 26) == 9 )
  {
    v8 = *((uint32_t **)dword_8F8528 + 7);
    v9 = sub_422E70(2000);
    sub_43BEE0(v8, (int)v9, -6567706, 0, -1);
    return (int)sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
  }
  else
  {
LABEL_7:
    v10 = v4 - 14;
    if ( v10 != 0 )
    {
      result = v10 - 1;
      if ( result == 0 )
      {
        v11 = *((uint32_t *)dword_8F8528 + 90);
        if ( v11 == 0 )
          return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 0);
        result = (*((uint32_t *)dword_8F8528 + 91) - v11) >> 2;
        if ( result == 0 )
          return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 0);
      }
    }
    else
    {
      v12 = *((uint32_t *)dword_8F8528 + 90);
      if ( v12 == 0 )
        return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 1);
      result = (*((uint32_t *)dword_8F8528 + 91) - v12) >> 2;
      if ( result == 0 )
        return sub_44E8D0((char *)dword_8F8528, (void *)0xE, 0, 1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6037B0 sub_6037B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6037B0(uint32_t *this, int a2)
{
  *(this + 11) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x6037C0 CNChangeActiveProperty__vmtC
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNChangeActiveProperty__vmtC(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v4; // ebx
  unsigned int v5; // edi
  int v6; // eax
  int v7; // edx

  result = (uint32_t *)*(this + 22);
  for ( i = (uint32_t *)*(this + 21); i != result; i += 2 )
  {
    v4 = i[1];
    v5 = 14 * *i + a2 + 284;
    v6 = sub_41A5E0(v5);
    sub_41A590(v5, v7, v4 + v6);
    result = (uint32_t *)*(this + 22);
  }
  return result;
}



// ------------------------------------------------------------
// 0x603810 CNChangeActiveProperty__vmt1C
// ------------------------------------------------------------
int /*thiscall*/ CNChangeActiveProperty__vmt1C(int this)
{
  int result; // eax
  uint32_t *v3; // esi
  int v4; // edi
  int v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);
    v3 = *(uint32_t **)(this + 84);
    v7 = result;
    if ( v3 != *(uint32_t **)(this + 88) )
    {
      do
      {
        v5 = sub_497040(*v3);
        if ( v5 != 17 )
        {
          v4 = 14 * *v3 + v7;
          v6 = sub_41A5E0(v4 + 284);
          if ( (int)(v3[1] + (uint64_t)((double)v6 * COERCE_FLOAT(sub_41A5E0(v4 + 508)))) >= 100
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(
                 *(uint32_t *)(this + 4),
                 v5) != 0 )
          {
            (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 764))(
              v5,
              0,
              *(uint32_t *)(this + 4),
              0);
          }
        }
        result = *(uint32_t *)(this + 88);
        v3 += 2;
      }
      while ( v3 != (uint32_t *)result );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6038D0 sub_6038D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6038D0(uint32_t *this, int a2, int a3, int a4)
{
  uint32_t v6[2]; // [esp+4h] [ebp-8h] BYREF

  v6[1] = a3;
  v6[0] = a2;
  sub_5E5E60((int)(this + 20), (int)v6);
  *(this + 11) = a4;
  return a4;
}



// ------------------------------------------------------------
// 0x603910 sub_603910
// ------------------------------------------------------------
int /*thiscall*/ sub_603910(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 20) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x603930 CNChangeElementTolerance__vmtC
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNChangeElementTolerance__vmtC(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int *v3; // edi
  int v4; // eax
  unsigned int v5; // esi
  int i; // ebx
  int v7; // edx
  unsigned int v8; // esi
  unsigned int v9; // esi
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  int v13; // ebx
  unsigned int v14; // esi
  int v15; // edx
  int v16; // [esp-10h] [ebp-20h]
  float v18; // [esp+4h] [ebp-Ch]
  int v19; // [esp+4h] [ebp-Ch]
  int v20; // [esp+4h] [ebp-Ch]
  float v21; // [esp+8h] [ebp-8h]
  int j; // [esp+8h] [ebp-8h]
  uint32_t *v23; // [esp+Ch] [ebp-4h]

  result = (uint32_t *)*(this + 22);
  v23 = result;
  if ( result != (uint32_t *)*(this + 23) )
  {
    v3 = result + 2;
    while ( 1 )
    {
      v4 = *result;
      if ( *((uint8_t *)v3 - 4) != 0 )
      {
        if ( v4 == 4 )
        {
          v5 = a2 + 228;
          for ( i = 4; i != 0; --i )
          {
            v18 = (double)*v3 * 0.0099999998;
            *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(v5)) + v18;
            sub_41A590(v5, v7, v19);
            v5 += 14;
          }
        }
        else
        {
          v21 = (double)*v3 * 0.0099999998;
          v8 = 14 * v4 + a2 + 228;
          *(float *)&v20 = COERCE_FLOAT(sub_41A5E0(v8)) + v21;
          sub_41A590(v8, v20, v20);
        }
      }
      else if ( v4 == 4 )
      {
        v9 = a2 + 172;
        for ( j = 4; j != 0; --j )
        {
          v10 = *v3;
          v11 = sub_41A5E0(v9);
          sub_41A590(v9, v12, v10 + v11);
          v9 += 14;
        }
      }
      else
      {
        v13 = *v3;
        v14 = 14 * v4 + a2 + 172;
        v16 = v13 + sub_41A5E0(v14);
        sub_41A590(v14, v15, v16);
      }
      result = v23 + 3;
      v3 += 3;
      v23 += 3;
      if ( v23 == (uint32_t *)*(this + 23) )
        break;
      result = v23;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x603A50 sub_603A50
// ------------------------------------------------------------
int /*thiscall*/ sub_603A50(int this, int a2, char a3, void *Src)
{
  int result; // eax

  result = a2;
  *(uint32_t *)(this + 44) = a2;
  *(uint8_t *)(this + 100) = a3;
  if ( Src != nullptr )
    return sub_4015C0(Src, strlen((const char *)Src));
  return result;
}



// ------------------------------------------------------------
// 0x603A90 sub_603A90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_603A90(int this, int a2, char a3, int a4, int a5, char a6, void *Src)
{
  int Block; // [esp+4h] [ebp-Ch] BYREF
  char v10; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 44) = a5;
  *(uint8_t *)(this + 100) = a6;
  if ( Src != nullptr )
    sub_4015C0(Src, strlen((const char *)Src));
  Block = a2;
  v11 = a4;
  v10 = a3;
  return sub_5E5DE0((int *)(this + 84), &Block);
}



// ------------------------------------------------------------
// 0x603AF0 CNChangeElementTolerance__vmt4
// ------------------------------------------------------------
char /*thiscall*/ CNChangeElementTolerance__vmt4(int this)
{
  int v2; // eax
  uint32_t *v3; // eax
  int *v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  int *v8; // edi
  int v9; // edx
  void *v10; // eax
  char result; // al
  int v12; // eax
  int v13; // [esp-14h] [ebp-38h]
  int v14; // [esp-10h] [ebp-34h]
  int v15; // [esp-Ch] [ebp-30h]
  void *v16[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  v2 = *(uint32_t *)(this + 88);
  if ( v2 != 0 )
  {
    Block = (void *)((*(uint32_t *)(this + 92) - v2) / 12);
    if ( Block != nullptr
      && *(int *)(*(uint32_t *)(this + 88) + 8) > 0
      && *(uint8_t *)(this + 100) != 0
      && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04) )
    {
      if ( *(uint32_t *)(this + 80) == 0 )
      {
        v3 = operator new(0x12Cu);
        Block = v3;
        v18 = 0;
        if ( v3 != nullptr )
          v4 = sub_428F30(v3, (int)"Common/CommonEffect/Particle/RemoveActiveStatus.ptl", *(uint32_t *)(this + 4));
        else
          v4 = nullptr;
        v5 = *(uint32_t *)(this + 4);
        *(uint32_t *)(this + 80) = v4;
        v6 = *v4;
        v18 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 112))(v4, v5);
      }
      v7 = **(uint32_t **)(this + 80);
      v8 = *(int **)(this + 4);
      v15 = (*(int (/*thiscall*/ **)(int *))(*v8 + 128))(v8) + 90;
      v14 = (*(int (/*thiscall*/ **)(int *))(*v8 + 124))(v8) + 30;
      v13 = (*(int (/*thiscall*/ **)(int *))(*v8 + 120))(v8);
      (*(void (/*thiscall*/ **)(uint32_t))(v7 + 40))(*(uint32_t *)(this + 80));
      (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(this + 80) + 92))(*(uint32_t *)(this + 80), v16);
      v9 = *v8;
      v18 = 1;
      v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v9 + 80))(v8, 2, 0, v16);
      sub_4600B0(v10, v13, v14, v15);
      v18 = -1;
      sub_5E5260(v16);
    }
  }
  result = *(uint8_t *)(this + 101);
  if ( result == 0 )
  {
    if ( *(uint32_t *)(this + 128) < 0x10u )
      v12 = this + 108;
    else
      v12 = *(uint32_t *)(this + 108);
    result = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
               *(uint32_t *)(this + 4),
               v12,
               -1,
               0,
               0);
    *(uint8_t *)(this + 101) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x603C70 CNThrowStackable__vmt88
// ------------------------------------------------------------
void /*thiscall*/ CNThrowStackable__vmt88(uint32_t *this, int a2, int a3, int a4)
{
  int v4; // ebx
  uint32_t *v6; // esi
  char *v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  unsigned int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  void *v16[7]; // [esp+Ch] [ebp-1Ch] BYREF

  v4 = a3;
  CNRDStackable__vmt88(a2, a3, a4);
  if ( v4 == 2
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 308))(a2) != 0
    && __RTDynamicCast(a2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 104))(this) != 0 )
    {
      v6 = *((uint32_t **)dword_8F8528 + 7);
      v7 = sub_422E70(1204);
      sub_43BEE0(v6, (int)v7, -6567706, 0, -1);
      sub_432EA0("ALERT_1", -1, 0, 0);
    }
    else
    {
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 900))(a2, 3);
      v9 = *(this + 25);
      a4 = v8;
      if ( v9 != 0 && (unsigned int)((*(this + 26) - v9) >> 2) > 4 && *(uint32_t *)(v9 + 16) == 1 )
      {
        v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 672))(a2, 3);
        v8 = sub_495540(v10);
        a4 = v8;
      }
      v11 = *(this + 25);
      if ( v11 != 0 && (unsigned int)((*(this + 26) - v11) >> 2) > 5 )
      {
        v12 = (int)((uint64_t)(1374389535LL * v8 * *(uint32_t *)(v11 + 20)) >> 32) >> 5;
        a4 = v12 + (v12 >> 31);
      }
      memset(&v16[1], 0, 12);
      v16[6] = nullptr;
      a3 = 0;
      sub_431230((int)v16, &a3);
      v13 = *(this + 37);
      if ( v13 == 3 )
      {
        a3 = 1;
        sub_431230((int)v16, &a3);
      }
      else if ( v13 == 4 )
      {
        a3 = 2;
        sub_431230((int)v16, &a3);
      }
      sub_431230((int)v16, this + 3);
      v14 = *(this + 25);
      if ( v14 != 0 && (unsigned int)((*(this + 26) - v14) >> 2) > 2 )
        a3 = *(uint32_t *)(v14 + 8);
      else
        a3 = 0;
      sub_431230((int)v16, &a3);
      v15 = *(this + 25);
      if ( v15 != 0 && (unsigned int)((*(this + 26) - v15) >> 2) > 3 )
        a3 = *(uint32_t *)(v15 + 12);
      else
        a3 = 500;
      sub_431230((int)v16, &a3);
      a3 = 0;
      sub_431230((int)v16, &a3);
      a3 = 0;
      sub_431230((int)v16, &a3);
      a3 = 0;
      sub_431230((int)v16, &a3);
      sub_431230((int)v16, &a4);
      sub_431230((int)v16, &a4);
      (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)a2 + 560))(a2, 10, v16, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 564))(a2);
      sub_5E5260(v16);
    }
  }
}



// ------------------------------------------------------------
// 0x603EE0 sub_603EE0
// ------------------------------------------------------------
void /*thiscall*/ sub_603EE0(uint32_t *this)
{
  *(this + 41) = 4;
}



// ------------------------------------------------------------
// 0x603EF0 CNRecipeStackable__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNRecipeStackable__vmt88(void *this, int a2, int a3, int a4)
{
  int result; // eax

  result = CNRDStackable__vmt88(a2, a3, a4);
  if ( a3 == 2 )
    return sub_44E8D0((char *)dword_8F8528, (void *)0x21, (int)this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x603F30 sub_603F30
// ------------------------------------------------------------
bool /*thiscall*/ sub_603F30(int this)
{
  bool result; // al

  result = sub_43BCF0(*(void **)(this + 116), "[craftmanship]");
  if ( result )
  {
    *(uint32_t *)(this + 164) = 0;
  }
  else
  {
    result = sub_43BCF0(*(void **)(this + 116), "[weaving]");
    if ( result )
    {
      *(uint32_t *)(this + 164) = 1;
    }
    else
    {
      result = sub_43BCF0(*(void **)(this + 116), "[machinary]");
      if ( result )
      {
        *(uint32_t *)(this + 164) = 2;
      }
      else
      {
        result = sub_43BCF0(*(void **)(this + 116), "[chemistry]");
        if ( result )
          *(uint32_t *)(this + 164) = 3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x603FB0 CNLotteryStackable__vmt88
// ------------------------------------------------------------
void */*thiscall*/ CNLotteryStackable__vmt88(void *this, int a2, int a3, int a4)
{
  void *result; // eax
  uint32_t *v6; // esi
  char *v7; // eax
  int v8; // esi
  uint32_t *v9; // esi
  char *v10; // eax

  result = (void *)CNRDStackable__vmt88(a2, a3, a4);
  if ( a3 == 2 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    {
      v8 = *((uint32_t *)dword_8F852C + 1);
      if ( v8 < sub_484FA0() )
      {
        return (void *)sub_44E8D0((char *)dword_8F8528, (void *)0x23, (int)this, 0);
      }
      else
      {
        v9 = *((uint32_t **)dword_8F8528 + 7);
        v10 = sub_422E70(1203);
        sub_43BEE0(v9, (int)v10, -6567706, 0, -1);
        return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
      }
    }
    else
    {
      v6 = *((uint32_t **)dword_8F8528 + 7);
      v7 = sub_422E70(1202);
      sub_43BEE0(v6, (int)v7, -6567706, 0, -1);
      return sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604080 CNAntiFreezePotion__vmt88
// ------------------------------------------------------------
int /*thiscall*/ sub_604080(int this, int *a2, int a3, void *Block)
{
  int *v6; // esi
  int result; // eax
  int *v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  unsigned int v13; // edx
  int v14; // ecx
  int v15; // edi
  int v16; // eax
  int v17; // edi
  uint64_t v18; // rax
  double v19; // st7
  double v20; // st7
  double v21; // st7
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // eax
  int *v26; // eax
  int v27; // edx
  int v28; // [esp-8h] [ebp-38h]
  int v29; // [esp+Ch] [ebp-24h] BYREF
  int v30; // [esp+10h] [ebp-20h]
  int v31; // [esp+14h] [ebp-1Ch]
  int v32; // [esp+18h] [ebp-18h]
  void *v33; // [esp+1Ch] [ebp-14h]
  int v34; // [esp+20h] [ebp-10h]
  int v35; // [esp+2Ch] [ebp-4h]
  int v36; // [esp+38h] [ebp+8h]
  int v37; // [esp+3Ch] [ebp+Ch]
  void *Blocka; // [esp+40h] [ebp+10h]

  v34 = this;
  sub_6029D0(this, a2, a3, (int)Block);
  v6 = nullptr;
  if ( *(uint32_t *)(this + 180) == 0 )
  {
    result = *(uint8_t *)(this + 184);
    if ( (uint8_t)result == 0 )
    {
      v35 = 0;
      if ( operator new(0x60u) != nullptr )
        v8 = (int *)sub_510230(1, 1000, 3000);
      else
        v8 = nullptr;
      v9 = *v8;
      v35 = -1;
      return (*(int (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v9 + 56))(
               v8,
               a2,
               a2,
               0,
               0,
               0,
               -1);
    }
    return result;
  }
  v10 = *a2;
  v29 = 0;
  v30 = 0;
  v31 = 0;
  v32 = 0;
  v11 = (*(int (/*thiscall*/ **)(int *))(v10 + 80))(a2);
  v12 = *(uint32_t *)(v11 + 120);
  Blocka = (void *)v11;
  if ( v12 != 0 )
    v36 = (*(uint32_t *)(v11 + 124) - v12) >> 2;
  else
    v36 = 0;
  result = v36;
  v13 = 0;
  v37 = 0;
  if ( v36 <= 0 )
    return result;
  while ( 2 )
  {
    v14 = *(uint32_t *)(v11 + 120);
    if ( v14 != 0 && v13 < (*(uint32_t *)(v11 + 124) - v14) >> 2 )
      v6 = *(int **)(v14 + 4 * v13);
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v6 + 40))(v6, 17) == 0 )
      goto LABEL_37;
    v15 = (*(int (/*thiscall*/ **)(int *))(*v6 + 376))(v6);
    if ( v15 != (*(int (/*thiscall*/ **)(int *))(*a2 + 376))(a2) )
      goto LABEL_36;
    v16 = v34;
    if ( *(uint8_t *)(v34 + 184) != 0 && v6 == a2 )
      goto LABEL_36;
    v17 = 0;
    while ( 1 )
    {
      if ( v17 != 0 )
      {
        if ( v17 == 1 )
        {
          v33 = (void *)(2 * *(uint32_t *)(v16 + 180));
          v20 = (double)(int)v33;
          v18 = (uint64_t)(0.88 * v20);
          v19 = v20 * 0.2552;
        }
        else
        {
          if ( v17 != 2 )
            goto LABEL_29;
          v33 = (void *)(2 * *(uint32_t *)(v16 + 180));
          v21 = (double)(int)v33;
          v18 = (uint64_t)(0.60000002 * v21);
          v19 = v21 * 0.28999999;
        }
      }
      else
      {
        LODWORD(v18) = 2 * *(uint32_t *)(v16 + 180);
        v33 = (void *)v18;
        v19 = (double)(int)v18 * 0.17399999;
      }
      v31 = v18;
      v32 = (uint64_t)v19;
LABEL_29:
      v22 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2);
      v23 = *a2;
      v29 = v22 - v31 / 2;
      v24 = (*(int (/*thiscall*/ **)(int *))(v23 + 124))(a2);
      v30 = v24 - v32 / 2;
      v28 = (*(int (/*thiscall*/ **)(int *))(*v6 + 124))(v6);
      v25 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
      if ( (uint8_t)sub_48C0A0(v25, v28, &v29) != 0 )
        break;
      if ( ++v17 >= 3 )
        goto LABEL_36;
      v16 = v34;
    }
    v33 = operator new(0x60u);
    v35 = 1;
    if ( v33 != nullptr )
      v26 = (int *)sub_510230(1, 1000, 3000);
    else
      v26 = nullptr;
    v27 = *v26;
    v35 = -1;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v27 + 56))(v26, v6, a2, 0, 0, 0, -1);
LABEL_36:
    v11 = (int)Blocka;
LABEL_37:
    result = ++v37;
    if ( v37 < v36 )
    {
      v13 = v37;
      v6 = nullptr;
      continue;
    }
    return result;
  }
}


// ------------------------------------------------------------
// 0x604310 sub_604310
// ------------------------------------------------------------
char /*thiscall*/ sub_604310(uint8_t *this)
{
  *(this + 3276) = 0;
  *(this + 3277) = 0;
  *(this + 3278) = 0;
  *(this + 3279) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x604330 sub_604330
// ------------------------------------------------------------
char /*thiscall*/ sub_604330(uint8_t *this, char a2, char a3)
{
  *(this + 3276) = a2;
  *(this + 3277) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x604350 CNSpecificEnemyEquipment__vmt88
// ------------------------------------------------------------
char /*thiscall*/ CNSpecificEnemyEquipment__vmt88(char *this, int a2, int a3, int a4, char a5, int a6)
{
  char result; // al

  result = *(this + 3276);
  if ( result != 0 )
  {
    if ( *(this + 3278) != 0 )
    {
      sub_4EA7C0(this + 212, this + 1380);
      if ( a6 != 0 )
      {
        *(uint32_t *)(a6 + 68) -= sub_41A5E0((unsigned int)(this + 2202));
        *(uint32_t *)(a6 + 64) -= sub_41A5E0((unsigned int)(this + 2188));
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
      *(this + 3278) = 0;
    }
    result = a5;
    if ( a5 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 304))(this, a2);
      if ( result != 0 )
      {
        sub_4EA220(this + 212, this + 1380);
        if ( a6 != 0 )
        {
          *(uint32_t *)(a6 + 68) += sub_41A5E0((unsigned int)(this + 2202));
          *(uint32_t *)(a6 + 64) += sub_41A5E0((unsigned int)(this + 2188));
        }
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
        *(this + 3278) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604440 CNSpecificEnemyEquipment__vmt8C
// ------------------------------------------------------------
char /*thiscall*/ CNSpecificEnemyEquipment__vmt8C(char *this, int a2, int a3, int a4, char a5)
{
  char result; // al

  result = *(this + 3277);
  if ( result != 0 )
  {
    if ( *(this + 3279) != 0 )
    {
      sub_4EA7C0(this + 212, this + 2328);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
      *(this + 3279) = 0;
    }
    result = a5;
    if ( a5 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 304))(this, a2);
      if ( result != 0 )
      {
        sub_4EA220(this + 212, this + 2328);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 321) + 676))(*((uint32_t *)this + 321), 0);
        *(this + 3279) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6044E0 sub_6044E0
// ------------------------------------------------------------
bool /*cdecl*/ sub_6044E0(int a1, int a2, int a3)
{
  bool result; // al
  int v4; // eax
  int v5; // eax

  switch ( a1 )
  {
    case 0:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 40))(a3, a2) == 0 )
        goto LABEL_14;
      return true;
    case 1:
      if ( (uint8_t)sub_4DAB60(a2) == 0 )
        goto LABEL_14;
      return true;
    case 2:
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 368))(a3) != 0 )
        return a2 == 1;
      else
        return a2 == 0;
    case 3:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 40))(a3, 17) == 0 )
        goto LABEL_14;
      v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 672))(a3, 3);
      if ( sub_4B0D20(v4) < a2 )
        goto LABEL_14;
      goto LABEL_11;
    case 4:
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 40))(a3, 17) == 0 )
        goto LABEL_14;
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 672))(a3, 3);
      if ( sub_4B0D20(v5) > a2 )
        goto LABEL_14;
LABEL_11:
      result = true;
      break;
    default:
LABEL_14:
      result = false;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6045C0 CNSpecificEnemyEquipment__vmt130
// ------------------------------------------------------------
char /*thiscall*/ CNSpecificEnemyEquipment__vmt130(int **this, int a2)
{
  int *v3; // edi
  int *v4; // ecx
  int *v5; // edi

  v3 = *(this + 338);
  if ( v3 != *(this + 339) )
  {
    while ( sub_6044E0(*v3, v3[1], a2) )
    {
      v3 += 2;
      if ( v3 == *(this + 339) )
        goto LABEL_4;
    }
    return 0;
  }
LABEL_4:
  v4 = *(this + 342);
  if ( v4 != nullptr && ((char *)*(this + 343) - (char *)v4) >> 3 != 0 )
  {
    v5 = *(this + 342);
    if ( v4 == *(this + 343) )
      return 0;
    while ( !sub_6044E0(*v5, v5[1], a2) )
    {
      v5 += 2;
      if ( v5 == *(this + 343) )
        return 0;
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x604670 CNSpecificStateEquipment__vmt9C
// ------------------------------------------------------------
char /*thiscall*/ CNSpecificStateEquipment__vmt9C(uint32_t *this, int a2)
{
  int v3; // ecx
  char result; // al
  uint32_t *v5; // edi
  char v6; // bl

  v3 = *(this + 314);
  if ( v3 == 0
    || (*(this + 315) - v3) >> 2 == 0
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this)) != 0 )
  {
    v5 = (uint32_t *)*(this + 338);
    v6 = 0;
    if ( v5 == (uint32_t *)*(this + 339) )
    {
LABEL_15:
      result = *((uint8_t *)this + 2312);
      if ( result != 0 )
      {
        sub_4EA7C0(this + 53, this + 341);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);
        *((uint8_t *)this + 2312) = 0;
      }
    }
    else
    {
      while ( v6 == 0 )
      {
        if ( *v5 == a2
          && (a2 != 8
           || v5[1] == -1
           || v5[1] == (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 321) + 908))(*(this + 321))) )
        {
          v6 = 1;
        }
        v5 += 2;
        if ( v5 == (uint32_t *)*(this + 339) )
        {
          if ( v6 == 0 )
            goto LABEL_15;
          break;
        }
      }
      result = *((uint8_t *)this + 2312);
      if ( result == 0 )
      {
        sub_4EA220(this + 53, this + 341);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);
        *((uint8_t *)this + 2312) = 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604770 sub_604770
// ------------------------------------------------------------
void /*thiscall*/ sub_604770(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_474950((int)this + 1348, (int)v3);
}



// ------------------------------------------------------------
// 0x6047A0 sub_6047A0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_6047A0(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  float v9; // [esp+Ch] [ebp-1Ch]
  float v10; // [esp+10h] [ebp-18h]
  float v11; // [esp+14h] [ebp-14h]

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v9 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v10 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 192))(v5) / 2;
  v11 = (float)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4) + v6);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  return (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 52))(v7) * (v11 + v10 + v9)
                          + (double)*(this + 338));
}



// ------------------------------------------------------------
// 0x604850 CNEventEquipment__vmtA0
// ------------------------------------------------------------
int /*thiscall*/ CNEventEquipment__vmtA0(int *this)
{
  unsigned int v2; // eax
  int result; // eax
  int *v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax

  nullsub_3();
  v2 = sub_6047A0(this);
  srand(v2);
  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 2 )
    goto LABEL_2;
  if ( result == 4 || result == 6 || result == 3 )
  {
    if ( *(this + 359) != 4 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      v4 = this;
      if ( *(this + 359) != *(uint32_t *)(*(uint32_t *)(v7 + 44) + 4) )
        return (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      goto LABEL_3;
    }
LABEL_2:
    v4 = this;
LABEL_3:
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 212))(v4, 0, 0, 0, 0);
    return (*(int (/*thiscall*/ **)(int *, int, int))(v5 + 304))(this, 2, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6048E0 sub_6048E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6048E0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  char *v5; // edx
  int result; // eax

  v5 = (char *)(this + 3 * a2);
  *((uint32_t *)v5 + 343) = a3;
  *((uint32_t *)v5 + 344) = a4;
  result = 3 * a2 + 345;
  *(this + result) = a5;
  return result;
}



// ------------------------------------------------------------
// 0x604920 CNEventEquipment__vmt138
// ------------------------------------------------------------
int /*thiscall*/ CNEventEquipment__vmt138(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int result; // eax
  float *v7; // esi
  int *v8; // ebx
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // [esp-2Ch] [ebp-50h]
  int v13; // [esp-24h] [ebp-48h]
  int v14; // [esp-20h] [ebp-44h]
  int v15; // [esp-1Ch] [ebp-40h]
  int v16; // [esp-10h] [ebp-34h]
  int v17; // [esp-Ch] [ebp-30h]
  uint32_t v18[5]; // [esp+4h] [ebp-20h]
  uint32_t *v19; // [esp+18h] [ebp-Ch]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+20h] [ebp-4h]

  v4 = *this;
  v19 = this;
  v5 = (*(int (/*fastcall*/ **)(uint32_t *))(v4 + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 308))(v5);
  if ( (uint8_t)result != 0 )
  {
    v7 = (float *)a3;
    v18[0] = 42004;
    v18[1] = 42003;
    v18[2] = 42005;
    v18[3] = 42006;
    v18[4] = 48011;
    v21 = 0;
    v8 = this + 344;
    do
    {
      v9 = v8[1];
      v10 = *(v8 - 1);
      v20 = *v8;
      a3 = v9;
      sub_432FA0();
      if ( v10 != -1 && rand() % a3 < v20 )
      {
        a3 = 0;
        v17 = sub_605840(&a3, a2, v7, 1);
        v16 = a3;
        v15 = (uint64_t)v7[2];
        v14 = (uint64_t)v7[1];
        v13 = (uint64_t)*v7;
        v12 = v18[v21];
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 212))(v19);
        sub_4E4A50(v11, v12, v10, v13, v14, v15, 1, 0, v16, v17);
      }
      result = v21 + 1;
      v8 += 3;
      ++v21;
    }
    while ( v21 < 5 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x604A20 sub_604A20
// ------------------------------------------------------------
char */*cdecl*/ sub_604A20(char *a1, char *a2, const void *a3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = a1; result != a2; result += 40 )
  {
    v4 = result;
    qmemcpy(v4, a3, 0x28u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x604A50 CNEventEquipment__vmt94
// ------------------------------------------------------------
char /*thiscall*/ CNEventEquipment__vmt94(int this)
{
  int v2; // ecx
  int v3; // eax
  unsigned int v4; // eax
  int v5; // edi
  int v6; // eax

  v2 = *(uint32_t *)(this + 1256);
  if ( v2 == 0
    || (*(uint32_t *)(this + 1260) - v2) >> 2 == 0
    || (LOBYTE(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 224))(this), (uint8_t)v3 != 0) )
  {
    v3 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v3 == 4 || v3 == 6 || v3 == 3 )
    {
      LOBYTE(v3) = *(uint8_t *)(this + 1432);
      if ( (uint8_t)v3 == 0 )
      {
        v4 = sub_6047A0((int *)this);
        srand(v4);
        if ( *(uint32_t *)(this + 1436) == 4
          || (v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 44),
              *(uint32_t *)(this + 1436) == *(uint32_t *)(v3 + 4)) )
        {
          v5 = *(uint32_t *)this;
          v6 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, 0, 0, 0, 0);
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int))(v5 + 304))(this, 2, v6);
          *(uint8_t *)(this + 1432) = 1;
          *(uint8_t *)(this + 1433) = 0;
        }
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x604B10 CNEventEquipment__vmt88
// ------------------------------------------------------------
int /*thiscall*/ CNEventEquipment__vmt88(uint32_t *this, int a2, float *a3, int a4, int a5, int a6)
{
  int v7; // ecx
  int result; // eax
  double v9; // st7

  v7 = *(this + 314);
  if ( v7 == 0
    || (*(this + 315) - v7) >> 2 == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this)) != 0 )
  {
    v9 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2) * (a3[2] + a3[1] + *a3)
       + (double)(int)*(this + 337);
    srand((uint64_t)v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, float *, int, int, int))(*this + 304))(this, 0, a2, a3, a4, a5, a6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, float *))(*this + 312))(this, a2, a3);
    result = *(this + 337) + 1;
    *(this + 337) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x604BB0 CNEventEquipment__vmt8C
// ------------------------------------------------------------
void /*thiscall*/ CNEventEquipment__vmt8C(uint32_t *this, int a2, float *a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // eax
  double v8; // st7

  v6 = *(this + 314);
  if ( v6 == 0
    || (*(this + 315) - v6) >> 2 == 0
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 224))(this) != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
    if ( *(uint8_t *)(v7 + 16) != 0 || *(float *)v7 > 0.0 )
    {
      v8 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2) * (a3[2] + a3[1] + *a3)
         + (double)(int)*(this + 338);
      srand((uint64_t)v8);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, float *, int, int, uint32_t))(*this + 304))(this, 1, a2, a3, a4, a5, 0);
      ++*(this + 338);
    }
  }
}



// ------------------------------------------------------------
// 0x604C60 sub_604C60
// ------------------------------------------------------------
char */*cdecl*/ sub_604C60(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a2;
  result = a3;
  while ( v3 != a1 )
  {
    v3 -= 40;
    result -= 40;
    qmemcpy(result, v3, 0x28u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x604C90 sub_604C90
// ------------------------------------------------------------
char */*cdecl*/ sub_604C90(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 40 )
  {
    if ( result != nullptr )
      qmemcpy(result, v3, 0x28u);
    v3 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x604CD0 sub_604CD0
// ------------------------------------------------------------
char */*cdecl*/ sub_604CD0(char *a1, char *a2, const void *a3)
{
  char *result; // eax
  char *v4; // edx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, a3, 0x28u);
      result += 40;
      --v4;
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x604D00 sub_604D00
// ------------------------------------------------------------
char /*thiscall*/ sub_604D00(uint32_t *this, int a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // ecx

  v2 = (uint32_t *)*(this + 361);
  v3 = (uint32_t *)*(this + 362);
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
// 0x604D30 CNEventEquipment__vmt90
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNEventEquipment__vmt90(int *this, uint32_t *a2, int a3)
{
  uint32_t *result; // eax
  uint32_t *v5; // ecx
  int v6; // edx
  int v7; // eax
  double v8; // st7
  int v9; // eax
  int v10; // eax
  double v11; // st7
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  double v19; // st7
  int v20; // edi
  int v21; // eax
  float v22; // [esp+4h] [ebp-18h] BYREF
  float v23; // [esp+8h] [ebp-14h]
  float v24; // [esp+Ch] [ebp-10h]
  int v25; // [esp+10h] [ebp-Ch]
  int v26; // [esp+14h] [ebp-8h]
  int v27; // [esp+18h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( result != nullptr )
  {
    result = (uint32_t *)*(this + 361);
    v5 = (uint32_t *)*(this + 362);
    if ( result != v5 )
    {
      while ( *result != *a2 )
      {
        if ( ++result == v5 )
          return result;
      }
      v6 = *this;
      v22 = 0.0;
      v23 = 0.0;
      v24 = 0.0;
      v25 = 0;
      v26 = 0;
      v27 = 0;
      v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 212))(this);
      v8 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
      v9 = *this;
      v22 = v8;
      v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 212))(this);
      v11 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 124))(v10);
      v12 = *this;
      v23 = v11;
      v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 212))(this);
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 192))(v14) / 2;
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 128))(v13);
      v17 = *this;
      v24 = (float)(v16 + v15);
      v18 = (*(int (/*thiscall*/ **)(int *))(v17 + 212))(this);
      v19 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 52))(v18) * (v24 + v23 + v22) + (double)*(this + 338);
      srand((uint64_t)v19);
      v20 = *this;
      v21 = (*(int (/*thiscall*/ **)(int *, float *, uint32_t, uint32_t, uint32_t))(*this + 212))(this, &v22, 0, 0, 0);
      return (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(v20 + 304))(this, 4, v21);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x604E70 CNEventEquipment__vmt130
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_604E70(unsigned int *this, int a2, int a3, float *a4, int a5, char a6, int a7)
{
  int v7; // ebx
  unsigned int result; // eax
  int v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // edx
  int v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // ecx
  int *v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // edi
  int v29; // eax
  int v30; // [esp-24h] [ebp-48h]
  int v31; // [esp-20h] [ebp-44h]
  int v32; // [esp-1Ch] [ebp-40h]
  int v33; // [esp-18h] [ebp-3Ch]
  int v34; // [esp-14h] [ebp-38h]
  int v35; // [esp-10h] [ebp-34h]
  int v36; // [esp+Ch] [ebp-18h] BYREF
  int v37; // [esp+10h] [ebp-14h]
  int v38; // [esp+14h] [ebp-10h]
  unsigned int v39; // [esp+18h] [ebp-Ch]
  int v40; // [esp+1Ch] [ebp-8h]
  int v41; // [esp+20h] [ebp-4h]

  v7 = 0;
  v41 = 0;
  v39 = 0;
  while ( 1 )
  {
    result = *(this + 340);
    v38 = v7;
    if ( result == 0 )
      return result;
    result = (int)(*(this + 341) - result) / 40;
    if ( v39 >= result )
      return result;
    v10 = *(this + 340) + v7;
    if ( a6 == *(uint8_t *)(v10 + 24) && *(uint32_t *)v10 == a2 )
    {
      LOBYTE(v40) = 0;
      if ( a2 != 2 && a2 != 3 && rand() % *(uint32_t *)(v10 + 16) >= *(uint32_t *)(v10 + 12) )
        goto LABEL_30;
      v11 = *(uint32_t *)(v7 + *(this + 340) + 8);
      if ( v11 != 0 )
      {
        if ( v11 > 0 && v11 <= 2 )
          v41 = a3;
      }
      else
      {
        v41 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
      }
      v12 = *(this + 340);
      v13 = *(uint32_t *)(v12 + v7 + 4);
      v14 = v7 + v12;
      if ( v13 != 0 )
      {
        v15 = v13 - 1;
        if ( v15 != 0 )
        {
          if ( v15 == 1 )
          {
            v37 = *(uint32_t *)(v14 + 32);
            v16 = v37;
            if ( v37 == -1 )
            {
              v16 = rand() % 17;
              v37 = v16;
            }
            v17 = rand();
            v18 = *(uint32_t *)v41;
            v36 = v17;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v18 + 40))(v41, 17) != 0
              && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v41 + 776))(v41, v16) == 0
              && (uint8_t)sub_4D6750(v16, 100.0, (int)&v36) != 0 )
            {
              v19 = v7 + *(this + 340);
              v20 = *(uint32_t *)v41;
              v21 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v20 + 768))(v41, v37, *(uint32_t *)(v19 + 20), v21);
              v7 = v38;
              goto LABEL_29;
            }
LABEL_26:
            LOBYTE(v40) = 0;
          }
LABEL_30:
          (*(void (/*thiscall*/ **)(unsigned int *, unsigned int, int))(*this + 308))(this, v39, v40);
          goto LABEL_31;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v41 + 40))(v41, 17) == 0 )
          goto LABEL_26;
        v22 = *(uint32_t *)(v7 + *(this + 340) + 28);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v22 + 80))(v22) != 0 )
          goto LABEL_26;
        v23 = *(int **)(*(this + 340) + v7 + 28);
        v24 = *v23;
        v25 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
        (*(void (/*thiscall*/ **)(int *, int, int))(v24 + 56))(v23, v41, v25);
        v7 = v38;
      }
      else
      {
        v26 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v26 + 308))(v26) != 0 )
        {
          v27 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
          v28 = *(this + 340) + v7;
          v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 152))(v27);
          v34 = (uint64_t)a4[2];
          v33 = (uint64_t)a4[1];
          v32 = (uint64_t)*a4;
          v31 = *(uint32_t *)(v28 + 20);
          v30 = *(uint32_t *)(v28 + 36);
          v29 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);
          sub_4E4A50(v29, v30, v31, v32, v33, v34, v35, 0, 0, 0);
        }
      }
LABEL_29:
      LOBYTE(v40) = 1;
      goto LABEL_30;
    }
LABEL_31:
    ++v39;
    v7 += 40;
  }
}


// ------------------------------------------------------------
// 0x6050F0 sub_6050F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_6050F0(unsigned int *this)
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax

  v1 = 0;
  for ( i = 0; ; i += 40 )
  {
    result = *(this + 340);
    if ( result == 0 )
      break;
    result = (int)(*(this + 341) - result) / 40;
    if ( v1 >= result )
      break;
    v5 = *(this + 340);
    v6 = *(uint32_t *)(v5 + i + 4);
    v7 = i + v5;
    if ( v6 == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v7 + 28) + 76))(*(uint32_t *)(v7 + 28), 0);
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605150 sub_605150
// ------------------------------------------------------------
char */*stdcall*/ sub_605150(char *a1, char *a2, const void *a3)
{
  sub_604CD0(a1, a2, a3);
  return &a1[40 * (uint32_t)a2];
}



// ------------------------------------------------------------
// 0x605180 CNEventEquipment__vmt98
// ------------------------------------------------------------
char /*thiscall*/ CNEventEquipment__vmt98(int this)
{
  int v1; // eax
  unsigned int v3; // eax
  int v4; // edi
  int v5; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v1 == 4 || v1 == 6 || v1 == 3 )
  {
    LOBYTE(v1) = *(uint8_t *)(this + 1433);
    if ( (uint8_t)v1 == 0 )
    {
      v3 = sub_6047A0((int *)this);
      srand(v3);
      v4 = *(uint32_t *)this;
      v5 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(v4 + 304))(this, 3, v5);
      LOBYTE(v1) = sub_6050F0((unsigned int *)this);
      *(uint8_t *)(this + 1432) = 0;
      *(uint8_t *)(this + 1433) = 1;
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x6051F0 sub_6051F0
// ------------------------------------------------------------
void /*thiscall*/ sub_6051F0(int this, char *a2, unsigned int a3, void *Block)
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
  char *v15; // ecx
  int v17; // esi
  char *v18; // [esp-18h] [ebp-5Ch]
  char *v19; // [esp-Ch] [ebp-50h]
  char *v20; // [esp-8h] [ebp-4Ch]
  int v21; // [esp+0h] [ebp-44h] BYREF
  uint32_t v22[11]; // [esp+Ch] [ebp-38h] BYREF
  int v23; // [esp+40h] [ebp-4h]
  char *v24; // [esp+4Ch] [ebp+8h]
  char *v25; // [esp+50h] [ebp+Ch]
  char *Blocka; // [esp+54h] [ebp+10h]
  char *Blockb; // [esp+54h] [ebp+10h]

  qmemcpy(v22, Block, 0x28u);
  v5 = *(uint32_t *)(this + 4);
  v22[10] = &v21;
  if ( v5 != 0 )
    v6 = (*(uint32_t *)(this + 12) - v5) / 40;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) / 40;
    else
      v8 = 0;
    if ( 107374182 - v8 < a3 )
      sub_50F360(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) / 40;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v15 = *(char **)(this + 8);
      Blockb = v15;
      if ( (v15 - a2) / 40 >= a3 )
      {
        v24 = &v15[-40 * a3];
        *(uint32_t *)(this + 8) = sub_604C90(v24, v15, v15);
        sub_604C60(a2, v24, Blockb);
        sub_604A20(a2, &a2[40 * a3], v22);
      }
      else
      {
        sub_604C90(a2, v15, &a2[40 * a3]);
        v20 = (char *)(a3 - (*(uint32_t *)(this + 8) - (int)a2) / 40);
        v19 = *(char **)(this + 8);
        v23 = 2;
        sub_605150(v19, v20, v22);
        v17 = 40 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v17;
        sub_604A20(a2, (char *)(v17 - 40 * a3), v22);
      }
    }
    else
    {
      if ( 107374182 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) / 40;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_5721D0(this);
      v12 = 40 * v10;
      Blocka = (char *)operator new(40 * v10);
      v18 = *(char **)(this + 4);
      v23 = 0;
      v25 = sub_604C90(v18, a2, Blocka);
      sub_604CD0(v25, (char *)a3, v22);
      sub_604C90(a2, *(char **)(this + 8), &v25[40 * a3]);
      v13 = *(uint32_t *)(this + 4);
      if ( v13 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v13) / 40;
      v14 = v13 + a3;
      if ( *(uint32_t *)(this + 4) != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v12];
      *(uint32_t *)(this + 8) = &Blocka[40 * v14];
      *(uint32_t *)(this + 4) = Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x6054A0 sub_6054A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6054A0(uint32_t *this, uint32_t *a2, char *a3, void *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 40 != 0 )
    v6 = (int)&a3[-v5] / 40;
  else
    v6 = 0;
  sub_6051F0((int)this, a3, 1u, Block);
  *a2 = *(this + 1) + 40 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x605510 sub_605510
// ------------------------------------------------------------
char */*thiscall*/ sub_605510(int this, void *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  char *v5; // edi
  char *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 40;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 40 )
    return (char *)sub_6054A0((uint32_t *)this, &Block, *(char **)(this + 8), Block);
  v5 = *(char **)(this + 8);
  result = sub_604CD0(v5, (char *)1, Block);
  *(uint32_t *)(this + 8) = v5 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x6055A0 sub_6055A0
// ------------------------------------------------------------
char */*thiscall*/ sub_6055A0(void *this, int a2, int a3, int a4, int a5, char a6, int a7)
{
  uint32_t Block[6]; // [esp+0h] [ebp-28h] BYREF
  char v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+24h] [ebp-4h]

  Block[0] = a2;
  Block[4] = a4;
  Block[3] = a3;
  v9 = a6;
  Block[5] = a5;
  Block[1] = 0;
  v10 = a7;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x6055F0 sub_6055F0
// ------------------------------------------------------------
char */*thiscall*/ sub_6055F0(void *this, int a2, int a3, int a4, char a5, uint32_t *a6, int a7)
{
  int v8; // edx
  uint32_t Block[6]; // [esp+4h] [ebp-28h] BYREF
  char v11; // [esp+1Ch] [ebp-10h]
  uint32_t *v12; // [esp+20h] [ebp-Ch]

  Block[2] = a7;
  v11 = a5;
  Block[0] = a2;
  Block[3] = a3;
  v8 = *a6;
  Block[1] = 1;
  Block[4] = a4;
  v12 = a6;
  *(uint8_t *)((*(int (**)(void))(v8 + 64))() + 36) = 0;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x605650 sub_605650
// ------------------------------------------------------------
char */*thiscall*/ sub_605650(void *this, int a2, int a3, int a4, int a5, char a6, int a7, int a8)
{
  uint32_t Block[6]; // [esp+0h] [ebp-28h] BYREF
  char v10; // [esp+18h] [ebp-10h]
  int v11; // [esp+20h] [ebp-8h]

  Block[2] = a8;
  Block[0] = a2;
  Block[4] = a4;
  Block[3] = a3;
  v10 = a6;
  Block[5] = a5;
  Block[1] = 2;
  v11 = a7;
  return sub_605510((int)this + 1356, Block);
}



// ------------------------------------------------------------
// 0x6056A0 sub_6056A0
// ------------------------------------------------------------
void /*thiscall*/ sub_6056A0(float *this, int a2)
{
  *(this + 181) = (float)a2;
}



// ------------------------------------------------------------
// 0x6056B0 CNTemporaryHit__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNTemporaryHit__vmt2BC(uint32_t *this, const void *a2, int Size)
{
  int v4; // eax
  int v5; // eax
  char v6; // cl
  int16_t v7; // cx
  float v9[8]; // [esp+Ch] [ebp-20h] BYREF

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  dword_78FE30 = (int)a2;
  dword_78FE34 = 0;
  if ( Size > 0 )
  {
    qmemcpy(v9, a2, 0x1Eu);
    dword_78FE34 = 30;
    if ( LOBYTE(v9[7]) == 0 )
      *(this + 196) = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v4 = sub_45EBE0((uint32_t *)*(this + 29), LOWORD(v9[0]), HIWORD(v9[0]));
      v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
      if ( v5 != 0 )
        sub_4E5F70((int)this, (int)this, v5, &v9[1], 1, 1);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
    if ( dword_78FE34 < Size )
    {
      v6 = *(uint8_t *)(dword_78FE34 + dword_78FE30);
      ++dword_78FE34;
      *((uint8_t *)this + 740) = v6 == 1;
      if ( dword_78FE34 < Size )
      {
        v7 = *(uint16_t *)(dword_78FE34 + dword_78FE30);
        dword_78FE34 += 2;
        *(this + 183) = v7;
        if ( dword_78FE34 < Size )
        {
          *(this + 218) = *(uint32_t *)(dword_78FE34 + dword_78FE30);
          dword_78FE34 += 4;
        }
      }
    }
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x605800 CNTemporaryHit__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNTemporaryHit__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x605840 sub_605840
// ------------------------------------------------------------
int16_t */*cdecl*/ sub_605840(uint32_t *a1, int a2, int *a3, char a4)
{
  int v4; // edx

  if ( (dword_9B937C & 1) == 0 )
  {
    dword_9B937C |= 1u;
    dword_9B9360 = 0;
    dword_9B9364 = 0;
    dword_9B9368 = 0;
    dword_9B936C = 0;
    dword_9B9370 = 0;
    dword_9B9374 = 0;
  }
  word_9B935C = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 48))(a2);
  word_9B935E = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
  dword_9B9360 = *a3;
  dword_9B9364 = a3[1];
  dword_9B9368 = a3[2];
  dword_9B936C = a3[3];
  dword_9B9370 = a3[4];
  v4 = a3[5];
  byte_9B9378 = a4;
  dword_9B9374 = v4;
  *a1 = 30;
  return &word_9B935C;
}



// ------------------------------------------------------------
// 0x605910 sub_605910
// ------------------------------------------------------------
void /*thiscall*/ sub_605910(uint32_t *this)
{
  *(this + 20) = 0;
}



// ------------------------------------------------------------
// 0x605920 CNSuperArmor__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNSuperArmor__vmt4(int *this)
{
  int v2; // esi
  int result; // eax

  IRDAppendage__vmt4(this);
  v2 = *(this + 1);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 616))(v2) == 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 620))(v2) != 1 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v2 + 612))(v2, 1, 1);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 724))(v2);
  if ( (uint8_t)result == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 288))(v2) == 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v2 + 284))(v2, 1, -16776961, 1, 2);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 292))(v2);
    if ( result != -16776961 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v2 + 284))(v2, 1, -16776961, 1, 2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6059A0 CNSuperArmor__vmt20
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt20(uint32_t **this, char a2)
{
  char result; // al

  result = a2;
  if ( a2 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(this + 1) + 612))(*(this + 1), 0, 0);
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(this + 1) + 284))(*(this + 1), 0, 0, 1, 2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6059E0 CNSuperArmor__vmt14
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt14(int *this, char a2, int a3, int a4, float a5)
{
  char result; // al
  int *i; // esi

  result = a2;
  if ( a2 != 0 )
  {
    for ( i = (int *)*(this + 22); i != (int *)*(this + 23); ++i )
    {
      sub_4938F0(*i);
      if ( *(uint8_t *)(*i + 170) == 0 )
        sub_491D00(dword_79C0B0, a3, a4, a5);
    }
    sub_4938F0(*(this + 20));
    result = *(uint8_t *)(*(this + 20) + 170);
    if ( result == 0 )
      return sub_491D00(dword_79C0B0, a3, a4, a5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x605A70 CNSuperArmor__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNSuperArmor__vmt54(int this, char a2)
{
  int *i; // esi

  IRDAppendage__vmt54((uint8_t *)this, a2);
  for ( i = *(int **)(this + 88); i != *(int **)(this + 92); ++i )
    sub_4939E0(*i, a2);
  return sub_4939E0(*(uint32_t *)(this + 80), a2);
}



// ------------------------------------------------------------
// 0x605AC0 sub_605AC0
// ------------------------------------------------------------
int /*thiscall*/ sub_605AC0(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
  {
    result = sub_431860(v2, "Common/CommonEffect/Animation/SuperArmorEffect.ani", 1);
    *(this + 20) = result;
  }
  else
  {
    *(this + 20) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605B30 sub_605B30
// ------------------------------------------------------------
void /*thiscall*/ sub_605B30(int this)
{
  int v2; // esi
  void ***v3; // esi
  bool v4; // zf
  void **v5; // ebx

  v2 = *(uint32_t *)(this + 80);
  if ( v2 != 0 )
  {
    sub_42AF90(*(void ***)(this + 80));
    sub_657740(v2, 228);
  }
  v3 = *(void ****)(this + 88);
  v4 = v3 == *(void ****)(this + 92);
  *(uint32_t *)(this + 80) = 0;
  if ( !v4 )
  {
    do
    {
      v5 = *v3;
      if ( *v3 != nullptr )
      {
        sub_42AF90(*v3);
        sub_657740(v5, 228);
      }
      *v3++ = nullptr;
    }
    while ( v3 != *(void ****)(this + 92) );
  }
  if ( *(uint32_t *)(this + 88) != 0 )
    j__free(*(void **)(this + 88));
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
}



// ------------------------------------------------------------
// 0x605BB0 CNSuperArmor__vmt1C
// ------------------------------------------------------------
int /*thiscall*/ CNSuperArmor__vmt1C(void *this)
{
  void ***i; // edi
  void **v3; // ebx
  int v4; // eax
  int v5; // ebx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // ecx
  int v9; // ecx
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+Ch] [ebp-4h]
  float v13; // [esp+Ch] [ebp-4h]

  for ( i = *((void ****)this + 22); i != *((void ****)this + 23); ++i )
  {
    v3 = *i;
    if ( *i != nullptr )
    {
      sub_42AF90(*i);
      sub_657740(v3, 228);
    }
    *i = nullptr;
  }
  if ( *((uint32_t *)this + 22) != 0 )
    j__free(*((void **)this + 22));
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  v4 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 200))(*((uint32_t *)this + 1));
  v5 = v4;
  if ( v4 != 0 )
  {
    v6 = *(uint32_t **)(v4 + 204);
    v7 = (uint32_t *)*v6;
    if ( (uint32_t *)*v6 != v6 )
    {
      do
      {
        if ( (int)v7[2] >= 0 )
          break;
        v8 = v7[3];
        v11 = v8;
        if ( *(uint32_t *)(v8 + 148) == -1 )
        {
          sub_4938F0(v8);
          v8 = v11;
        }
        (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v8 + 60);
        v7 = (uint32_t *)*v7;
      }
      while ( v7 != *(uint32_t **)(v5 + 204) );
    }
    if ( *(uint32_t *)(v5 + 148) == -1 )
      sub_4938F0(v5);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v5 + 60);
    for ( ; v7 != *(uint32_t **)(v5 + 204); v7 = (uint32_t *)*v7 )
    {
      v9 = v7[3];
      v12 = v9;
      if ( *(uint32_t *)(v9 + 148) == -1 )
      {
        sub_4938F0(v9);
        v9 = v12;
      }
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v9 + 60);
    }
  }
  v13 = (double)(*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 192))(*((uint32_t *)this + 1)) * 0.0071428572;
  sub_4920E0(*((uint32_t **)this + 20), v13, v13);
  sub_4926A0(*((uint32_t *)this + 20));
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
           *((uint32_t *)this + 1),
           "SUPERARMOR",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x605D10 CNSuperArmor__vmt78
// ------------------------------------------------------------
void /*thiscall*/ CNSuperArmor__vmt78(uint32_t **this, int a2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // esi
  bool v8; // cc
  uint32_t *v9; // edi
  char *v10; // eax
  unsigned int v11; // esi
  int *v12; // edx
  int v13; // [esp+8h] [ebp-1Ch] BYREF
  int v14; // [esp+Ch] [ebp-18h]
  uint32_t **v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+20h] [ebp-4h]
  int v18; // [esp+2Ch] [ebp+8h]

  v3 = 0;
  v15 = this;
  if ( a2 != 0 )
  {
    v4 = sub_42FCB0(228);
    v17 = 0;
    if ( v4 != 0 )
    {
      v5 = sub_431860(v4, "Common/CommonEffect/Animation/SuperArmorBody.ani", 1);
      v18 = v5;
    }
    else
    {
      v18 = 0;
      v5 = 0;
    }
    v6 = *(uint32_t *)(v5 + 44);
    v17 = -1;
    v13 = v5;
    if ( v6 != 0 )
      v16 = (*(uint32_t *)(v5 + 48) - v6) / 88;
    else
      v16 = 0;
    if ( v16 > 0 )
    {
      do
      {
        v7 = sub_4924C0(v3);
        *(uint32_t *)v7 = *(uint32_t *)a2;
        *(uint32_t *)(v7 + 12) = *(uint32_t *)(a2 + 12);
        *(uint32_t *)(v7 + 16) = *(uint32_t *)(a2 + 16);
        if ( v3 < 2 )
        {
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v15[1] + 192))(v15[1]);
          *(uint32_t *)(v7 + 16) += (uint64_t)((double)v14
                                                   * ((*(float *)(v7 + 24) - 1.0)
                                                    / *(float *)(a2 + 24))
                                                   * 0.40000001);
        }
        v5 = v18;
        v8 = ++v3 < v16;
        *(float *)(v7 + 20) = *(float *)(v7 + 20) * *(float *)(a2 + 20);
        *(float *)(v7 + 24) = *(float *)(v7 + 24) * *(float *)(a2 + 24);
      }
      while ( v8 );
    }
    v9 = v15[22];
    v10 = (char *)(v15 + 21);
    if ( v9 != nullptr )
      v11 = v15[23] - v9;
    else
      v11 = 0;
    if ( v9 != nullptr && v11 < v15[24] - v9 )
    {
      v12 = v15[23];
      *v12 = v5;
      *((uint32_t *)v10 + 2) = v12 + 1;
    }
    else
    {
      sub_42AC90((int)(v15 + 21), (char *)v15[23], 1u, &v13);
    }
  }
}



// ------------------------------------------------------------
// 0x605E80 sub_605E80
// ------------------------------------------------------------
int /*thiscall*/ sub_605E80(int this)
{
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint8_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x605EB0 sub_605EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_605EB0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // edi
  int i; // ebx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  *(this + 11) = 0;
  v5 = this + 12;
  for ( i = 2; i != 0; --i )
  {
    if ( *v5 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  result = 0;
  *(this + 14) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  *(this + 15) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x605F40 sub_605F40
// ------------------------------------------------------------
int /*thiscall*/ sub_605F40(uint32_t *this)
{
  int v1; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 24) + 31;
  v3 = *(uint32_t *)(v1 + 20) + 7;
  result = 0;
  for ( i = v2 + 18; pt.x < v3 || pt.x >= v3 + 177 || pt.y < v2 || pt.y >= i; i += 19 )
  {
    ++result;
    v2 += 19;
    if ( result >= 10 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x605FA0 sub_605FA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_605FA0(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 1);
  return v1 == 0 || (*(this + 2) - v1) >> 3 == 0;
}



// ------------------------------------------------------------
// 0x605FD0 CNRDDialogueWindow__vmt0
// ------------------------------------------------------------
char /*thiscall*/ CNRDDialogueWindow__vmt0(int this, int a2)
{
  unsigned int v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // ecx
  unsigned int v8; // edi
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  bool v17; // cc
  unsigned int v19; // [esp+8h] [ebp-10h]
  int v20; // [esp+Ch] [ebp-Ch]
  int v21; // [esp+10h] [ebp-8h]
  unsigned int v22; // [esp+14h] [ebp-4h]
  int v23; // [esp+20h] [ebp+8h]

  LOBYTE(v3) = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(uint32_t *)(this + 8) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(109);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 5, v5 + 5, dword_79C0B0);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 68);
    if ( *(uint32_t *)(this + 152) < 0x10u )
      v7 = this + 132;
    else
      v7 = *(uint32_t *)(this + 132);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v4 + 34,
      v5 + 11,
      -6632219,
      v7);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    LOBYTE(v3) = *(uint8_t *)(this + 188);
    if ( (uint8_t)v3 == 0 )
    {
      v20 = v4 + 7;
      v21 = v5 + 31;
      v8 = sub_69C690(*(uint32_t *)(this + 60));
      v22 = v8;
      v3 = sub_605F40((uint32_t *)this);
      v19 = v3;
      v23 = 0;
      while ( 1 )
      {
        v9 = *(uint32_t *)(this + 176);
        if ( v9 == 0 )
          break;
        v3 = (*(uint32_t *)(this + 180) - v9) >> 3;
        if ( v8 >= v3 )
          break;
        v10 = 8 * v8;
        v11 = sub_418DD0(120 - (*(uint32_t *)(v10 + *(uint32_t *)(this + 176) + 4) != 0));
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v20 + 3, v21 + 3, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
        v12 = *(uint32_t *)(v10 + *(uint32_t *)(this + 176));
        v13 = *(uint32_t *)(v12 + 36);
        v14 = v12 + 12;
        if ( v13 < 0x10 )
          v15 = v14 + 4;
        else
          v15 = *(uint32_t *)(v14 + 4);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v20 + 19,
          v21 + 4,
          -1,
          v15);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( v23 == v19 )
        {
          sub_491530(2, 0);
          v16 = sub_418DD0(121);
          if ( v16 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 152))(v16, v20, v21, dword_79C0B0);
          sub_491630(2);
        }
        LOBYTE(v3) = v23 + 1;
        v17 = ++v23 < 10;
        ++v22;
        v21 += 19;
        if ( !v17 )
          break;
        v8 = v22;
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6061D0 sub_6061D0
// ------------------------------------------------------------
int **/*thiscall*/ sub_6061D0(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 101) == 0 )
  {
    if ( v4[3] >= *a3 )
    {
      v3 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( v3 == *(this + 1) || *a3 < v3[3] )
  {
    *a2 = *(this + 1);
    return a2;
  }
  else
  {
    *a2 = v3;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x606240 CNRDDialogueWindow__vmt14
// ------------------------------------------------------------
char /*usercall*/ CNRDDialogueWindow__vmt14@<al>(uint32_t *a1@<ecx>, int a2@<esi>)
{
  int v2; // edi
  unsigned int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v16; // [esp+Ch] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = *(uint32_t *)(v2 + 8);
    v16 = v4 != 0 ? (*(uint32_t *)(v2 + 12) - v4) >> 2 : 0;
    if ( v16 > 0 )
    {
      while ( 1 )
      {
        v5 = *(uint32_t *)(v2 + 8);
        if ( v5 != 0 && v3 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
          v6 = *(uint32_t *)(v5 + 4 * v3);
        else
          v6 = 0;
        v7 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
        v8 = v7;
        if ( v7 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) == a1[48] )
          break;
        if ( (int)++v3 >= v16 )
          goto LABEL_18;
      }
      v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 340))(v8, a2);
      v10 = *(uint32_t *)(v9 + 180);
      v11 = v9 + 156;
      if ( v10 < 0x10 )
        v12 = v11 + 4;
      else
        v12 = *(uint32_t *)(v11 + 4);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v8 + 212))(v8, v12, -1, 0);
    }
  }
LABEL_18:
  (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 32))(a1);
  return 1;
}



// ------------------------------------------------------------
// 0x606340 sub_606340
// ------------------------------------------------------------
int /*thiscall*/ sub_606340(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // ebx
  uint8_t *v10; // edi
  uint8_t *v11; // eax
  uint32_t *v12; // edi
  int v13; // ebx
  uint32_t *v14; // eax
  int result; // eax
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v17; // [esp+14h] [ebp-10h]

  v2 = *this;
  *(this + 16) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 24))(16, 18);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 44))(this, 168, 4096);
  sub_69A5F0((uint32_t *)*(this + 3), 8, 37);
  sub_69C3E0(10);
  sub_69C440(-1);
  sub_69C420(6);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 16), 110, 111, 112, 110, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  sub_69A5F0(v4, 179, 8);
  sub_69A840(*(this + 9));
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(this + 16), 113, 114, 115, 113, 0, 0);
  else
    v6 = nullptr;
  *(this + 10) = v6;
  sub_69A5F0(v6, 9, 226);
  sub_69A840(*(this + 10));
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_43C410(v7, *(this + 16), 116, 117, 118, 116, 0, 0);
  else
    v8 = nullptr;
  *(this + 11) = v8;
  sub_69A5F0(v8, 25, 226);
  sub_69A840(*(this + 11));
  v9 = 4;
  v17 = this + 12;
  do
  {
    v10 = operator new(0x84u);
    if ( v10 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v10);
      *(uint32_t *)v10 = &nengine::CNButton::`vftable';
      sub_69C780(v10);
      sub_69C7B0(Block, v9, v9, v9 + 1, v9, 0, 0);
    }
    else
    {
      v10 = nullptr;
    }
    *v17 = v10;
    v9 += 2;
    ++v17;
  }
  while ( v9 < 8 );
  v11 = operator new(0x88u);
  v12 = v11;
  if ( v11 != nullptr )
  {
    v13 = *(this + 16);
    sub_426BD0(v11);
    *v12 = &nengine::CNSlider::`vftable';
    sub_69CA20(v12);
    sub_69CA50(v13, 122, 88);
    *v12 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v12 = nullptr;
  }
  *(this + 14) = v12;
  if ( operator new(0x74u) != nullptr )
    v14 = (uint32_t *)sub_43C630(*(this + 12), *(this + 13), *(this + 14));
  else
    v14 = nullptr;
  *(this + 15) = v14;
  sub_69A5F0(v14, 186, 31);
  sub_69A840(*(this + 15));
  *(this + 20) = 0;
  *(this + 23) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *((uint8_t *)this + 68) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;
  *(this + 21) = 6;
  *(this + 22) = 12;
  *(this + 24) = 1600;
  result = dword_99FCCC;
  *(this + 29) = dword_99FCCC;
  *(this + 18) = -14405058;
  return result;
}


// ------------------------------------------------------------
// 0x606650 sub_606650
// ------------------------------------------------------------
void /*thiscall*/ sub_606650(int this, int a2, unsigned int a3, int a4)
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
      sub_558090(this);
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
// 0x6068A0 sub_6068A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6068A0(uint32_t *this, int a2)
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
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( (uint8_t)sub_558520(v4) != 0 )
  {
    v8 = (uint32_t *)*(this + 1);
    v7 = *(uint32_t **)(a2 + 8);
    v6 = *(uint32_t **)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_44BD30(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x606940 sub_606940
// ------------------------------------------------------------
int /*thiscall*/ sub_606940(int this, int a2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // ecx
  int v6; // eax
  unsigned int v7; // edx
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // edx
  int v11; // edx
  uint32_t *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t **)(a2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(a2 + 8) - (int)v3) >> 3) == 0 )
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
    sub_47E1D0(v3, *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 4));
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
    if ( (uint8_t)sub_558520(v14) != 0 )
      *(uint32_t *)(this + 8) = sub_472EA0(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  if ( v6 != 0 )
    v11 = (*(uint32_t *)(this + 8) - v6) >> 3;
  else
    v11 = 0;
  v12 = (uint32_t *)(*(uint32_t *)(a2 + 4) + 8 * v11);
  sub_47E1D0(*(uint32_t **)(a2 + 4), v12, *(uint32_t **)(this + 4));
  *(uint32_t *)(this + 8) = sub_44BD30(v12, *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x606A90 sub_606A90
// ------------------------------------------------------------
void /*thiscall*/ sub_606A90(int this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_63A7C0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_606650(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x606B00 sub_606B00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_606B00(uint32_t *a1, int **a2, int a3)
{
  void *v3; // ebx
  int v4; // esi
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int *v11; // esi
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  char v16[4]; // [esp+8h] [ebp-48h] BYREF
  void *Block; // [esp+Ch] [ebp-44h]
  int v18; // [esp+10h] [ebp-40h]
  int v19; // [esp+14h] [ebp-3Ch]
  char v20[4]; // [esp+18h] [ebp-38h] BYREF
  void *v21; // [esp+1Ch] [ebp-34h]
  int v22; // [esp+20h] [ebp-30h]
  int v23; // [esp+24h] [ebp-2Ch]
  uint32_t v24[2]; // [esp+28h] [ebp-28h] BYREF
  int *v25; // [esp+30h] [ebp-20h] BYREF
  int v26; // [esp+34h] [ebp-1Ch] BYREF
  int v27; // [esp+38h] [ebp-18h]
  int v28; // [esp+3Ch] [ebp-14h]
  int v29; // [esp+40h] [ebp-10h]
  int v30; // [esp+4Ch] [ebp-4h]

  v3 = nullptr;
  v25 = nullptr;
  v21 = nullptr;
  v22 = 0;
  v23 = 0;
  v4 = a3;
  v30 = 0;
  if ( a3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v7 = sub_41A5E0(v6 + 53);
    v8 = *(uint32_t *)(a3 + 72);
    v27 = v7;
    if ( v8 != 0 )
      v29 = (*(uint32_t *)(a3 + 76) - v8) >> 2;
    else
      v29 = 0;
    v9 = 0;
    v28 = 0;
    if ( v29 > 0 )
    {
      while ( 1 )
      {
        v10 = *(uint32_t *)(*(uint32_t *)(v4 + 72) + 4 * v9);
        v26 = v10;
        sub_6061D0(a2, &v25, &v26);
        if ( v25 == a2[1] )
        {
          off_77F3FC(aCriticalErrorN, v10);
        }
        else
        {
          v11 = v25 + 4;
          if ( v25 != (int *)-16 && v7 >= v25[5] && v7 <= v25[6] )
          {
            v12 = sub_606B00(v16, a2, v25 + 4);
            v13 = *(uint32_t *)(v12 + 4);
            if ( v13 != 0 )
              v14 = (*(uint32_t *)(v12 + 8) - v13) >> 3;
            else
              v14 = 0;
            if ( Block != nullptr )
              j__free(Block);
            v15 = v11[18];
            Block = nullptr;
            v18 = 0;
            v19 = 0;
            if ( v15 == 0 || (v11[19] - v15) >> 2 == 0 || v14 != 0 )
            {
              v24[0] = v11;
              v24[1] = v14;
              sub_606A90((int)v20, (int)v24);
            }
          }
        }
        v9 = ++v28;
        if ( v28 >= v29 )
          break;
        v4 = a3;
        v7 = v27;
      }
      v3 = v21;
    }
    sub_6068A0(a1, (int)v20);
    if ( v3 != nullptr )
      j__free(v3);
    return a1;
  }
  else
  {
    sub_6068A0(a1, (int)v20);
    return a1;
  }
}



// ------------------------------------------------------------
// 0x606CA0 sub_606CA0
// ------------------------------------------------------------
char /*cdecl*/ sub_606CA0(int **a1)
{
  char v1; // bl
  int **v2; // edi
  int **v3; // esi
  int v5; // esi
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // eax
  bool v9; // al
  void *v10[4]; // [esp+Ch] [ebp-14h] BYREF
  int v11; // [esp+1Ch] [ebp-4h] BYREF

  v1 = 0;
  v2 = a1;
  v11 = 1;
  sub_6061D0(a1, (int **)&a1, &v11);
  v3 = a1;
  if ( a1 == (int **)v2[1] )
  {
    off_77F3FC(aNpc1);
    return 0;
  }
  else if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 )
  {
    v5 = (int)(v3 + 4);
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v7 = sub_41A5E0(v6 + 53);
    if ( v7 < *(uint32_t *)(v5 + 4) || v7 > *(uint32_t *)(v5 + 8) )
    {
      off_77F3FC((char *)&byte_73B05C);
      return 0;
    }
    else
    {
      if ( (uint8_t)sub_484F10(v5 + 68) != 0
        || (v8 = sub_606B00(v10, v2, v5), v1 = 1, v9 = sub_605FA0(v8), HIBYTE(a1) = 1, !v9) )
      {
        HIBYTE(a1) = 0;
      }
      if ( (v1 & 1) != 0 )
        sub_5E5260(v10);
      if ( HIBYTE(a1) != 0 )
      {
        off_77F3FC(asc_73B06C);
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
  else
  {
    off_77F3FC("if (g_userManager->getMyUser() == NULL)");
    return 0;
  }
}



// ------------------------------------------------------------
// 0x606DC0 sub_606DC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_606DC0(int ***this, uint32_t *a2, int a3)
{
  sub_606B00(a2, *(this + 30), a3);
  return a2;
}



// ------------------------------------------------------------
// 0x606DF0 sub_606DF0
// ------------------------------------------------------------
char /*thiscall*/ sub_606DF0(int this, int ArgList, char a3)
{
  int v3; // ebx
  int v5; // edi
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  char v20; // dl
  bool v21; // zf
  int v22; // ecx
  bool v23; // al
  uint8_t v24[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v26; // [esp+14h] [ebp-18h]
  int v27; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h] BYREF
  int v29; // [esp+28h] [ebp-4h]

  v3 = ArgList;
  v5 = *(uint32_t *)(this + 120);
  sub_6061D0(&v28, &ArgList);
  if ( v28 == *(uint32_t *)(v5 + 4) )
  {
    off_77F3FC(aCriticalErrorN, v3);
    return 0;
  }
  else
  {
    v7 = v28 + 16;
    ArgList = v28 + 16;
    if ( v28 == -16 )
    {
      return 0;
    }
    else
    {
      if ( a3 != 0 && sub_40BF00((std::_String_base *)(v28 + 56), 0, *(uint32_t *)(v28 + 76), szPassword, 0) == 0 )
        a3 = 0;
      v8 = sub_606DC0(v24, v7);
      v29 = 0;
      sub_606940(v8);
      v29 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v26 = 0;
      v27 = 0;
      if ( a3 != 0 )
      {
        sub_69C340(-1);
        if ( *(uint32_t *)(v7 + 64) < 0x10u )
          v9 = v7 + 44;
        else
          v9 = *(uint32_t *)(v7 + 44);
        sub_69C360(v9, 0);
        sub_69C400(0);
        v10 = sub_69C500(*(uint32_t *)(this + 12));
        if ( v10 - sub_69C3A0(*(uint32_t *)(this + 12)) >= 0 )
        {
          v11 = sub_69C500(*(uint32_t *)(this + 12));
          v12 = sub_69C3A0(*(uint32_t *)(this + 12));
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), v11 - v12);
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), 0);
        }
        v7 = ArgList;
      }
      else
      {
        v13 = *(uint32_t *)(this + 176);
        if ( v13 != 0 )
          v14 = (*(uint32_t *)(this + 180) - v13) >> 3;
        else
          v14 = 0;
        if ( v14 - 10 >= 0 )
        {
          v16 = *(uint32_t *)(this + 176);
          if ( v16 != 0 )
            v17 = (*(uint32_t *)(this + 180) - v16) >> 3;
          else
            v17 = 0;
          v15 = v17 - 10;
        }
        else
        {
          v15 = 0;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 60) + 32))(*(uint32_t *)(this + 60), v15);
      }
      v18 = *(uint32_t *)(this + 160);
      if ( v18 != 0 )
        v19 = (*(uint32_t *)(this + 164) - v18) >> 2;
      else
        v19 = 0;
      v20 = a3;
      v21 = a3 == 0;
      *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = v19 != 0;
      v23 = false;
      if ( !v21 )
      {
        v22 = *(uint32_t *)(this + 176);
        if ( v22 != 0 && (*(uint32_t *)(this + 180) - v22) >> 3 != 0 )
          v23 = true;
      }
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = v23;
      *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = v20;
      sub_69C680(0);
      *(uint32_t *)(this + 124) = v7;
      sub_4014D0((std::_String_base *)(this + 128), v7 + 12, 0, -1);
      *(uint8_t *)(this + 188) = a3;
      return 1;
    }
  }
}


// ------------------------------------------------------------
// 0x607020 CNRDDialogueWindow__vmt8
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDDialogueWindow__vmt8(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  unsigned int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int *v10; // edi
  int v11; // eax
  int v12; // eax
  uint8_t *result; // eax

  sub_69A650(*(uint32_t *)(this + 8));
  if ( *(uint8_t *)(this + 188) != 0 )
  {
    v2 = sub_69C690(*(uint32_t *)(this + 60));
    sub_69C400(v2);
  }
  else
  {
    v3 = *(uint32_t *)(this + 8);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    {
      v4 = sub_605F40((uint32_t *)this);
      if ( v4 != -1 )
      {
        v5 = *(uint32_t *)(this + 176);
        v6 = v5 != 0 ? (*(uint32_t *)(this + 180) - v5) >> 3 : 0;
        if ( v4 + sub_69C690(*(uint32_t *)(this + 60)) < v6 )
        {
          sub_431230(this + 156, *(uint32_t **)(this + 124));
          v7 = sub_69C690(*(uint32_t *)(this + 60));
          sub_606DF0(this, **(int ***)(*(uint32_t *)(this + 176) + 8 * (v4 + v7)), 1);
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
      }
    }
  }
  v8 = *(uint32_t *)(this + 40);
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
  {
    v9 = *(uint32_t *)(this + 160);
    v10 = *(int **)(*(uint32_t *)(this + 164) - 4);
    if ( v9 != 0 )
      v11 = (*(uint32_t *)(this + 164) - v9) >> 2;
    else
      v11 = 0;
    sub_505FF0(v11 - 1, 0);
    sub_606DF0(this, v10, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v12 = *(uint32_t *)(this + 44);
  if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
  {
    sub_606DF0(this, **(int ***)(this + 124), 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(uint8_t **)(this + 36);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 20))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6071B0 CNRDDialogueWindow__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CNRDDialogueWindow__vmtC(int this, uint32_t *a2, int a3)
{
  *(uint32_t *)(this + 120) = a2 + 74;
  if ( a2 == (uint32_t *)-296 )
    return 0;
  *(uint32_t *)(this + 192) = *a2;
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  sub_606DF0(this, (int *)1, 1);
  sub_69A5F0(
    *(uint32_t **)(this + 8),
    (640 - *(uint32_t *)(*(uint32_t *)(this + 8) + 28)) / 2,
    (480 - *(uint32_t *)(*(uint32_t *)(this + 8) + 32)) / 2);
  return 1;
}



// ------------------------------------------------------------
// 0x607240 sub_607240
// ------------------------------------------------------------
int /*thiscall*/ sub_607240(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *((uint8_t *)this + 8) = 1;
  *((uint8_t *)this + 9) = 1;
  *((uint8_t *)this + 10) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x607260 sub_607260
// ------------------------------------------------------------
char /*thiscall*/ sub_607260(uint32_t *this, int a2, int a3, char a4, char a5)
{
  *this = a2;
  *(this + 1) = a3;
  *((uint8_t *)this + 8) = a4;
  *((uint8_t *)this + 9) = a5;
  return a4;
}



// ------------------------------------------------------------
// 0x607290 sub_607290
// ------------------------------------------------------------
char /*thiscall*/ sub_607290(uint8_t *this, int a2)
{
  int v2; // eax

  LOBYTE(v2) = *(this + 9);
  *(this + 10) = 1;
  *((uint32_t *)this + 4) = 0;
  if ( (uint8_t)v2 != 0 )
  {
    v2 = a2 - *(uint32_t *)this;
    *((uint32_t *)this + 3) = v2;
  }
  else
  {
    *((uint32_t *)this + 3) = a2;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x6072C0 sub_6072C0
// ------------------------------------------------------------
char /*thiscall*/ sub_6072C0(uint8_t *this, int a2)
{
  char v2; // al
  int v3; // eax
  int v4; // eax

  if ( *(this + 10) == 0 )
  {
    v2 = *(this + 9);
    *(this + 10) = 1;
    *((uint32_t *)this + 4) = 0;
    if ( v2 != 0 )
      *((uint32_t *)this + 3) = a2 - *(uint32_t *)this;
    else
      *((uint32_t *)this + 3) = a2;
  }
  v3 = *((uint32_t *)this + 1);
  if ( v3 != -1 && *((uint32_t *)this + 4) >= v3 )
    return 0;
  v4 = *(uint32_t *)this + *((uint32_t *)this + 3);
  if ( a2 < v4 )
    return 0;
  if ( *(this + 8) != 0 )
  {
    ++*((uint32_t *)this + 4);
    *((uint32_t *)this + 3) = a2;
  }
  else
  {
    *((uint32_t *)this + 3) = v4;
    ++*((uint32_t *)this + 4);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x607330 sub_607330
// ------------------------------------------------------------
int /*thiscall*/ sub_607330(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = -1;
  *(uint32_t *)(this + 984) = -1;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = -1;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = -1;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint8_t *)(this + 1036) = 0;
  *(uint8_t *)(this + 1037) = 0;
  *(uint8_t *)(this + 1038) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6073C0 sub_6073C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6073C0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 253);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 253) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6073E0 sub_6073E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6073E0(uint32_t *this, int a2, int a3)
{
  int result; // eax

  result = sub_41A5E0(a2 + 4);
  *(this + 246) = result;
  *(this + 247) = a3;
  if ( result == 6 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
    *(this + 174) = 1000;
  }
  return result;
}



// ------------------------------------------------------------
// 0x607420 CNGunnerBullet__vmt158
// ------------------------------------------------------------
int /*thiscall*/ sub_607420(int this, int a2)
{
  int v3; // eax
  int v4; // edi
  char *v5; // ebx
  uint32_t *v6; // eax
  double v7; // st7
  char *v8; // eax
  int v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // edi
  int v14; // eax
  int v15; // ecx
  char *v16; // eax
  char *v17; // eax
  double v18; // st7
  int v19; // eax
  int result; // eax
  uint32_t *v21; // edi
  int v22; // eax
  int i; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // [esp-10h] [ebp-1Ch]
  int v27; // [esp-10h] [ebp-1Ch]

  sub_4E7440((char *)this, a2);
  v3 = *(uint32_t *)(this + 992);
  v4 = 0;
  *(uint32_t *)(this + 508) = (*(uint32_t *)(this + 972) != 0) + 1;
  switch ( v3 )
  {
    case 1:
      *(uint32_t *)(this + 408) = 0;
      goto LABEL_13;
    case 2:
      v5 = (char *)sub_47E720(2, 2);
      *(uint32_t *)(this + 408) = 1;
      v6 = (uint32_t *)(this + 412);
      while ( *v6 != 17 )
      {
        ++v4;
        ++v6;
        if ( v4 >= 3 )
          goto LABEL_9;
      }
      *(uint32_t *)(this + 4 * v4 + 412) = 1;
      *(uint32_t *)(this + 4 * v4 + 436) = sub_47EF20(1, *(uint32_t *)(this + 996), -1, -1, 11);
      *(float *)(this + 4 * v4 + 424) = (double)(int)sub_47EF20(2, *(uint32_t *)(this + 996), -1, -1, 11) * 0.1;
LABEL_9:
      v7 = (double)sub_47EFD0(
                     v5,
                     COERCE_FLOAT(3),
                     *(uint32_t *)(this + 996),
                     *(uint32_t *)(this + 980),
                     *(uint32_t *)(this + 980),
                     0);
      break;
    case 30:
      *(uint32_t *)(this + 408) = 3;
      v8 = (char *)sub_47E720(2, 30);
      v7 = (double)sub_47EFD0(
                     v8,
                     COERCE_FLOAT(1),
                     *(uint32_t *)(this + 996),
                     *(uint32_t *)(this + 980),
                     *(uint32_t *)(this + 980),
                     0);
      break;
    default:
      goto LABEL_13;
  }
  *(float *)(this + 388) = v7 + *(float *)(this + 388);
LABEL_13:
  v9 = *(uint32_t *)(this + 984);
  switch ( v9 )
  {
    case 5:
      *(uint32_t *)(this + 464) = -998637568;
      v10 = (char *)sub_47E720(2, 5);
      v11 = sub_47EFD0(v10, 0.0, *(uint32_t *)(this + 988), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      v26 = *(uint32_t *)(this + 988);
      *(float *)(this + 388) = (double)v11 + *(float *)(this + 388);
      *(float *)(this + 460) = (double)(int)sub_47EF20(2, v26, -1, -1, 11) * 0.1 + *(float *)(this + 460);
      break;
    case 6:
    case 9:
    case 15:
      v17 = (char *)sub_47E720(2, *(uint32_t *)(this + 984));
      v18 = (double)sub_47EFD0(v17, 0.0, *(uint32_t *)(this + 988), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      v19 = *(uint32_t *)(this + 984);
      *(float *)(this + 388) = v18 + *(float *)(this + 388);
      if ( v19 == 15 )
      {
        *(float *)(this + 464) = (double)(int)sub_47EF20(4, *(uint32_t *)(this + 988), -1, -1, 11)
                               + *(float *)(this + 464);
        *(float *)(this + 524) = *(float *)(this + 524) * 0.5;
      }
      break;
    case 48:
      v12 = (char *)sub_47E720(2, 48);
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v12,
                                         0.0,
                                         *(uint32_t *)(this + 988),
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    case 47:
      v13 = (char *)sub_47E720(2, 47);
      v27 = *(uint32_t *)(this + 988);
      *(uint32_t *)(this + 448) = 2;
      *(uint32_t *)(this + 456) = sub_47EF20(0, v27, -1, -1, 11);
      v14 = sub_47EF20(1, *(uint32_t *)(this + 988), -1, -1, 11);
      v15 = *(uint32_t *)(this + 988);
      *(uint32_t *)(this + 452) = v14;
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v13,
                                         COERCE_FLOAT(2),
                                         v15,
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    case 26:
      v16 = (char *)sub_47E720(2, 26);
      *(float *)(this + 388) = (double)sub_47EFD0(
                                         v16,
                                         COERCE_FLOAT(2),
                                         *(uint32_t *)(this + 988),
                                         *(uint32_t *)(this + 980),
                                         *(uint32_t *)(this + 980),
                                         0)
                             + *(float *)(this + 388);
      break;
    default:
      break;
  }
  result = __RTDynamicCast(
             *(uint32_t *)(this + 692),
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  v21 = (uint32_t *)result;
  if ( result != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 840))(result) == 8
      && (*(int (/*thiscall*/ **)(uint32_t *))(*v21 + 908))(v21) == 1 )
    {
      v22 = *(uint32_t *)(this + 984);
      if ( v22 != 47 && v22 != 5 )
      {
        *(uint32_t *)(this + 396) += 200;
        *(uint32_t *)(this + 448) = 2;
      }
    }
    for ( i = 0; i < 18; ++i )
    {
      v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 792))(v21, i);
      if ( v24 == 0 )
      {
        v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1084))(v21, i);
        if ( v24 == 0 )
          continue;
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v24 + 128))(v24, this + 388);
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*v21 + 700))(v21);
    sub_53F7A0(this + 388);
    if ( *(uint32_t *)(this + 972) == 2 )
      *(float *)(this + 388) = (double)sub_4C0FD0(v21) + *(float *)(this + 388);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1140))(v21, 38);
    if ( result > 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1160))(v21, 38);
      v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v21 + 1140))(v21, 38);
      result = sub_47EF20(0, v25, -1, -1, 11);
      *(float *)(this + 524) = ((double)result * 0.0099999998 + 1.0) * *(float *)(this + 524);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6078B0 sub_6078B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6078B0(uint32_t *this)
{
  int v2; // eax
  int result; // eax
  int v4; // esi
  int v5; // ebx
  uint32_t *v6; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
  result = __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
  v4 = result;
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1140))(result, 31);
    v5 = result;
    if ( result > 0 )
    {
      v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1160))(v4, 31);
      result = sub_47EF20(v6, 0, v5, -1, -1, 11);
      *(this + 174) += result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x607920 CNGunnerBullet__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNGunnerBullet__vmt214(int *this, int a2, int a3, int a4)
{
  int v5; // eax
  int *v6; // ebx
  int i; // edi

  LOBYTE(v5) = CNRDPassiveObject__vmt214(this, a2, a3, a4);
  if ( *(this + 254) == -1 )
  {
    v6 = this + 256;
    *(this + 254) = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > 0 ? 0 : 2;
    for ( i = 0; i < 3; ++i )
    {
      v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, i);
      *v6++ = v5;
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x607990 sub_607990
// ------------------------------------------------------------
int /*thiscall*/ sub_607990(uint32_t *this)
{
  int v1; // esi
  int v2; // edi

  v1 = *(uint32_t *)(*(this + 28) + 104);
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v1 + 16))(v1);
  return *(uint32_t *)(v2 + 15) * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v1 + 44))(v1) / 1000;
}



// ------------------------------------------------------------
// 0x6079D0 CNGunnerBullet__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerBullet__vmt1F0(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this) == 0 )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, 273) == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 1032))(v6) == 2 )
  {
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 792))(v6, 8);
    if ( v7 != 0 )
    {
      v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4);
      if ( (v8 == 31941 || v8 == 31967) && (uint8_t)sub_4DAB60(6) != 0 )
        *(this + 99) += 20;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x607A70 sub_607A70
// ------------------------------------------------------------
char /*thiscall*/ sub_607A70(int this, int a2, char a3)
{
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  char *v6; // eax
  double v7; // st7
  int v9; // [esp+Ch] [ebp+8h]

  v4 = *(uint32_t **)(a2 + 336);
  v5 = *(uint32_t **)(a2 + 332);
  if ( v5 != v4 )
  {
    do
    {
      if ( *v5 == 6 )
        break;
      ++v5;
    }
    while ( v5 != v4 );
    if ( v5 != v4 )
    {
      v6 = (char *)sub_47E720(2, 0x1Eu);
      v9 = sub_47EFD0(v6, COERCE_FLOAT(2), *(uint32_t *)(this + 996), *(uint32_t *)(this + 980), *(uint32_t *)(this + 980), 0);
      LOBYTE(v5) = a3;
      v7 = (double)v9;
      if ( a3 == 1 )
        *(float *)(this + 388) = v7 + *(float *)(this + 388);
      else
        *(float *)(this + 388) = *(float *)(this + 388) - v7;
    }
  }
  return (char)v5;
}



// ------------------------------------------------------------
// 0x607B00 CNGunnerBullet__vmt10
// ------------------------------------------------------------
char /*usercall*/ CNGunnerBullet__vmt10@<al>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  bool v5; // zf
  int v6; // eax
  int v7; // et2
  int v8; // ecx
  int v9; // edi
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  uint32_t *v13; // edi
  int v15; // [esp+4h] [ebp-4h]
  float v16; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10(a1);
  v4 = a1[246];
  if ( v4 == 6 )
  {
    LOBYTE(v4) = *((uint8_t *)a1 + 1037);
    if ( (uint8_t)v4 == 0 )
    {
      a1[252] = -1081794888;
      *((uint8_t *)a1 + 1037) = 1;
    }
  }
  else
  {
    v5 = v4 == 9;
    LOBYTE(v4) = *((uint8_t *)a1 + 1037);
    if ( v5 )
    {
      if ( (uint8_t)v4 == 0 )
      {
        v6 = rand();
        v7 = v6 % 628;
        v4 = v6 / 628;
        *((uint8_t *)a1 + 1037) = 1;
        *((float *)a1 + 252) = (double)v7 * 0.0099999998;
      }
    }
    else
    {
      if ( (uint8_t)v4 == 0 )
      {
        v8 = *(uint32_t *)(a1[28] + 104);
        if ( v8 != 0 && a1[30] != 0 )
        {
          v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v8 + 16))(v8, a3, a2) + 76);
          v10 = dword_7930D4[0]
              * *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1[28] + 104) + 16))(*(uint32_t *)(a1[28] + 104))
                          + 72)
              / 100;
          if ( (int)abs32(v9) <= (int)abs32(v10) )
            v15 = -v10;
          else
            v15 = v9;
          v11 = *a1;
          v16 = (double)v15 * 0.0174532925199433;
          *((float *)a1 + 252) = v16;
          (*(void (/*thiscall*/ **)(int *, int, uint32_t))(v11 + 272))(a1, 1, LODWORD(v16));
        }
        *((uint8_t *)a1 + 1037) = 1;
      }
      v12 = a1[248];
      if ( v12 == 1 || v12 == 2 || v12 == 30 )
      {
        v4 = a1[32];
        v13 = *(uint32_t **)v4;
        if ( *(uint32_t *)v4 != v4 )
        {
          do
          {
            sub_4938F0(v13[3]);
            if ( *((float *)a1 + 252) != 0.0 )
              sub_492080(*((float *)a1 + 252));
            if ( sub_699000((int)(a1 + 9)) <= 70 )
              LOBYTE(v4) = sub_491F80(-1, -1, -1, 0, 1);
            else
              LOBYTE(v4) = sub_491F80(-1, -1, -1, 255, 1);
            v13 = (uint32_t *)*v13;
          }
          while ( v13 != (uint32_t *)a1[32] );
        }
      }
      else if ( sub_699000((int)(a1 + 9)) <= 70 )
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*a1 + 252))(a1, 3, 0);
      }
      else
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 252))(a1, 3, 255);
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x607CD0 CNGunnerBullet__vmt1F8
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerBullet__vmt1F8(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // esi
  int i; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax

  if ( *(this + 248) == 30 )
    sub_607A70((int)this, a2, 0);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this) == 0 )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, 273) == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 1032))(v6) == 2 )
  {
    for ( i = 0; i < 18; ++i )
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 792))(v6, i) != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 792))(v6, i);
        (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t, uint32_t *))(*(uint32_t *)v8 + 136))(
          v8,
          a2,
          a3,
          a4,
          0,
          this + 97);
      }
    }
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 792))(v6, 8);
    if ( v9 != 0 )
    {
      v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9) + 4);
      if ( (v10 == 31941 || v10 == 31967) && (uint8_t)sub_4DAB60(6) != 0 )
        *(this + 99) -= 20;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x607DD0 CNGunnerBullet__vmt28C
// ------------------------------------------------------------
void **/*thiscall*/ CNGunnerBullet__vmt28C(uint32_t *this, int a2)
{
  void **result; // eax

  if ( (dword_9B93A0 & 1) == 0 )
  {
    dword_9B93A0 |= 1u;
    dword_9B939C = 15;
    dword_9B9398 = 0;
    LOBYTE(dword_9B9388) = 0;
    atexit(sub_6BFF00);
  }
  if ( *(this + 244) > 2u )
    return nullptr;
  if ( *(this + 243) != 0 )
    sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/DownDefault.ani", 0x3Bu);
  else
    sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/UpDefault.ani", 0x39u);
  result = (void **)dword_9B9388;
  if ( (unsigned int)dword_9B939C < 0x10 )
    return &dword_9B9388;
  return result;
}



// ------------------------------------------------------------
// 0x607E70 CNGunnerBullet__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ sub_607E70(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // edx
  int v5; // eax
  double v6; // st7
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int *v17; // ecx
  int v18; // edx
  int *v19; // edi
  int *v20; // edi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int *v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // eax
  int v28; // eax
  void *v29; // ecx
  int v30; // eax
  int v31; // [esp-10h] [ebp-54h]
  float v32; // [esp+Ch] [ebp-38h] BYREF
  float v33; // [esp+10h] [ebp-34h]
  float v34; // [esp+14h] [ebp-30h]
  int v35; // [esp+18h] [ebp-2Ch]
  int v36; // [esp+1Ch] [ebp-28h]
  int v37; // [esp+20h] [ebp-24h]
  uint8_t v38[4]; // [esp+24h] [ebp-20h] BYREF
  void *Block; // [esp+28h] [ebp-1Ch]
  int v40; // [esp+2Ch] [ebp-18h]
  int v41; // [esp+30h] [ebp-14h]
  int v42; // [esp+34h] [ebp-10h]
  int v43; // [esp+40h] [ebp-4h]

  sub_600890();
  if ( *((uint8_t *)this + 1036) == 0 )
  {
    if ( *(this + 246) == 6 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      v2 = (uint32_t *)__RTDynamicCast(
                       *(this + 173),
                       0,
                       &IRDCollisionObject `RTTI Type Descriptor',
                       &CNGunner `RTTI Type Descriptor',
                       0);
      v3 = v2;
      if ( v2 != nullptr && v2[2175] != 0 )
      {
        v4 = *v2;
        v32 = 0.0;
        v33 = 0.0;
        v34 = 0.0;
        v35 = 0;
        v36 = 0;
        v37 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(v2) != 0 )
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 120))(v3) + 94;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 120))(v3) - 94;
        v42 = v5;
        v6 = (double)v5;
        v7 = *v3;
        v32 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(v3);
        v9 = *v3;
        v42 = v8;
        v33 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(v3);
        v11 = v3[2175];
        v42 = v10 + 16;
        v34 = (float)(v10 + 16);
        sub_4E5F70(0, (int)this, v11, &v32, 1, 1);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
    else
    {
      v12 = *(this + 246);
      if ( v12 == 9 )
      {
        sub_4A0B60(0);
        v13 = sub_42FCB0(228);
        v42 = v13;
        v43 = 0;
        if ( v13 != 0 )
          v14 = sub_431860(v13, "Character/Gunner/Effect/Animation/Bullet/RandomShoot.ani", 1);
        else
          v14 = 0;
        v15 = *this;
        v43 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 196))(this, v14);
        (*(void (/*thiscall*/ **)(int *, int))(*this + 100))(this, v14);
      }
      else if ( v12 == 48 && *(this + 244) != 3 )
      {
        v31 = *(this + 247);
        sub_47E720(2, 48);
        v16 = sub_47EF20(1, v31, -1, -1, 11);
        v17 = *(int **)(*(this + 28) + 104);
        v18 = *v17;
        *(float *)&v42 = (double)v16 * 0.0099999998;
        v19 = (int *)((*(int (/*thiscall*/ **)(int *))(v18 + 16))(v17) + 85);
        *v19 = (uint64_t)((double)*v19 * *(float *)&v42);
        v20 = *(int **)(*(this + 28) + 104);
        v21 = *v20;
        v22 = (*(int (/*thiscall*/ **)(int *))(*v20 + 44))(v20);
        (*(void (/*thiscall*/ **)(int *, int))(v21 + 4))(v20, v22);
      }
    }
    *((uint8_t *)this + 1036) = 1;
  }
  v23 = *(this + 248);
  if ( v23 == 1 || v23 == 2 || v23 == 30 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 252))(this, 3, 0);
    if ( *(this + 248) == 30 )
    {
      v24 = (int *)*(this + 253);
      if ( v24 != nullptr )
      {
        v25 = *v24;
        v26 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v26);
        v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v27);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v25 + 40))(*(this + 253), v28);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 253) + 92))(*(this + 253), v38);
        v29 = (void *)*(this + 29);
        v43 = 1;
        sub_4600B0(v29, 2, 0, (int)v38);
        v43 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        v40 = 0;
        v41 = 0;
      }
    }
  }
  if ( *(this + 246) == 9
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && sub_699000((int)(this + 9)) >= 200 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  if ( *(this + 244) != 3 )
  {
    v30 = *(this + 246);
    if ( v30 != 6 && v30 != 9 && v30 != 5 )
    {
      *((float *)this + 116) = *((float *)this + 116) - *((float *)this + 251);
      v42 = sub_607990(this) - 200;
      if ( v42 > 0 )
        *((float *)this + 251) = (double)v42 * 0.0175;
      else
        *(this + 251) = 0;
      *((float *)this + 116) = *((float *)this + 116) + *((float *)this + 251);
    }
  }
}


// ------------------------------------------------------------
// 0x6081B0 sub_6081B0
// ------------------------------------------------------------
int /*cdecl*/ sub_6081B0(int a1, int a2)
{
  int v2; // eax
  void **v3; // ecx
  int v4; // esi
  uint8_t v6[4]; // [esp+4h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+8h] [ebp-28h] BYREF
  unsigned int v8; // [esp+1Ch] [ebp-14h]
  int v9; // [esp+20h] [ebp-10h]
  int v10; // [esp+2Ch] [ebp-4h]

  v9 = dword_796E50;
  v8 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/Bullet/", 0x29u);
  v10 = 0;
  switch ( a1 )
  {
    case 1:
      sub_4022F0((std::_String_base *)v6, "Flame", 5);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v6, "Freeze", 6);
      break;
    case 30:
      sub_4022F0((std::_String_base *)v6, "Silver", 6);
      break;
    default:
      return 0;
  }
  switch ( a2 )
  {
    case 0:
    case 1:
      sub_4022F0((std::_String_base *)v6, "Pistol.ani", 10);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v6, "Musket.ani", 10);
      break;
    case 4:
      sub_4022F0((std::_String_base *)v6, "BowGun.ani", 10);
      break;
    default:
      if ( v8 >= 0x10 )
        j__free(Block[0]);
      return 0;
  }
  v2 = sub_42FCB0(228);
  LOBYTE(v10) = 1;
  if ( v2 != 0 )
  {
    v3 = (void **)Block[0];
    if ( v8 < 0x10 )
      v3 = Block;
    v4 = sub_431860(v2, (const char *)v3, 1);
  }
  else
  {
    v4 = 0;
  }
  if ( v8 >= 0x10 )
    j__free(Block[0]);
  return v4;
}



// ------------------------------------------------------------
// 0x608300 sub_608300
// ------------------------------------------------------------
int /*cdecl*/ sub_608300(int a1, int a2, int a3)
{
  int v3; // eax
  void **v4; // ecx
  int v5; // esi
  int i; // edi
  int v7; // eax
  int v8; // eax
  uint8_t v10[4]; // [esp+10h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+14h] [ebp-28h] BYREF
  unsigned int v12; // [esp+28h] [ebp-14h]
  int v13; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  v13 = dword_796E50;
  v12 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0("Character/Gunner/Effect/Animation/HitEffect/", 0x2Cu);
  v14 = 0;
  switch ( a1 )
  {
    case 1:
      sub_4022F0((std::_String_base *)v10, "Flame", 5);
      break;
    case 2:
      sub_4022F0((std::_String_base *)v10, "Freeze", 6);
      break;
    case 30:
      sub_4022F0((std::_String_base *)v10, "Silver", 6);
      break;
    default:
      sub_4022F0((std::_String_base *)v10, "Normal", 6);
      break;
  }
  sub_4022F0((std::_String_base *)v10, "BowGun.ani", 10);
  v3 = sub_42FCB0(228);
  LOBYTE(v14) = 1;
  if ( v3 != 0 )
  {
    v4 = (void **)Block[0];
    if ( v12 < 0x10 )
      v4 = Block;
    v5 = sub_431860(v3, (const char *)v4, 1);
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v14) = 0;
  for ( i = 0; ; ++i )
  {
    v7 = *(uint32_t *)(v5 + 44);
    v8 = v7 != 0 ? (*(uint32_t *)(v5 + 48) - v7) / 88 : 0;
    if ( i >= v8 )
      break;
    *(uint32_t *)(sub_4924C0(i) + 28) = a3;
  }
  if ( v12 >= 0x10 )
    j__free(Block[0]);
  return v5;
}



// ------------------------------------------------------------
// 0x608430 CNGunnerBullet__vmt12C
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_608430(uint32_t *this, uint32_t *a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  unsigned int v6; // eax
  int v7; // edi
  int v8; // edi
  int v9; // edi
  int v10; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  bool v14; // zf
  char *v15; // eax
  uint32_t *v16; // ecx
  int v17; // edi
  int v18; // ecx
  int v19; // ebx
  int v20; // eax
  int v21; // edi
  int v22; // ebx
  int v23; // eax
  uint32_t *result; // eax
  int v25; // [esp-8h] [ebp-40h]
  int v26; // [esp+8h] [ebp-30h]
  char v27[4]; // [esp+Ch] [ebp-2Ch] BYREF
  uint32_t v28[7]; // [esp+10h] [ebp-28h] BYREF
  int v29; // [esp+34h] [ebp-4h]

  v28[6] = dword_796E50;
  sub_600790(a2);
  if ( a2 == this )
  {
    v3 = *(this + 246);
    if ( v3 != 9 && v3 != 6 )
    {
      v4 = *(uint32_t *)(*(this + 28) + 104);
      if ( v4 == 0
        || (v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4),
            (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 44))(v4) < *(uint32_t *)(v5 + 85)) )
      {
        v6 = *(this + 244);
        v7 = 0;
        if ( v6 <= 2 )
        {
          v13 = *(this + 254);
          if ( v13 != -1 )
          {
            v14 = v13 == 2;
            v15 = "Character/Gunner/Effect/Animation/HitEffect/CollisionFloor.ani";
            if ( !v14 )
              v15 = "Character/Gunner/Effect/Animation/HitEffect/CollisionWall.ani";
            sub_401710(v15);
            v29 = 1;
            if ( sub_42FCB0(228) != 0 )
            {
              LOBYTE(v16) = v28[0];
              if ( v28[5] < 0x10u )
                v16 = v28;
              v7 = sub_431860((char)v16, 1);
            }
            LOBYTE(v29) = 0;
            v26 = sub_44B6C0(284);
            LOBYTE(v29) = 2;
            if ( v26 != 0 )
              v17 = sub_44E1F0(v7, 1);
            else
              v17 = 0;
            v18 = *(this + 29);
            LOBYTE(v29) = 0;
            sub_45FE80(v18, v17, 2, 0, v17, 0, 0);
            v19 = *(uint32_t *)v17;
            v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v19 + 148))(v17, v20);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v17 + 112))(
              v17,
              *(this + 256),
              *(this + 257),
              *(this + 258));
            v29 = -1;
            sub_501490(v27);
          }
        }
        else if ( v6 == 4 )
        {
          v8 = sub_608300(*(this + 248), *(this + 243), *(this + 252));
          v29 = 3;
          v9 = sub_44B6C0(284) != 0 ? sub_44E1F0(v8, 1) : 0;
          v10 = *(this + 29);
          v29 = -1;
          sub_45FE80(v10, v9, 2, 0, v9, 0, 0);
          v11 = *(uint32_t *)v9;
          v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(int, int))(v11 + 148))(v9, v12);
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v9 + 112))(
            v9,
            *(this + 256),
            *(this + 257),
            *(this + 258));
          if ( *(this + 254) == -1 && *(this + 255) != 0 )
          {
            v25 = *(this + 255);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 60))(v9);
            sub_4A06D0(v25);
          }
        }
        if ( *(this + 248) == 1
          && *(this + 254) != -1
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        {
          sub_47E720(2, *(this + 248));
          v21 = sub_47EF20(1, *(this + 249), -1, -1, 11);
          v22 = *(this + 258) <= 0 ? 0 : *(this + 258);
          v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
          sub_4E4A50(*(this + 173), 40002, v21, *(this + 256), *(this + 257), v22, v23, 0, 0, 0);
        }
      }
    }
  }
  result = a2;
  if ( a2 == (uint32_t *)*(this + 255) )
    *(this + 255) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x608730 sub_608730
// ------------------------------------------------------------
int /*thiscall*/ sub_608730(int *this, void *Block, int a3)
{
  int result; // eax
  int v5; // ecx
  int v6; // edi
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // edi

  result = sub_41A5E0((unsigned int)Block + 4);
  *(this + 248) = result;
  *(this + 249) = a3;
  if ( result == 1 || result == 2 || result == 30 )
  {
    v5 = *(this + 246);
    if ( v5 != 6 && v5 != 9 )
    {
      result = sub_6081B0(result, *(this + 244));
      v6 = result;
      if ( result != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          1,
          result,
          0,
          0,
          0,
          0);
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 100))(this, v6);
      }
      if ( *(this + 248) == 30 )
      {
        result = *(this + 253);
        if ( result == 0 && *(this + 244) != 3 )
        {
          v7 = operator new(0x12Cu);
          if ( v7 != nullptr )
            v8 = sub_428F30(v7, (int)"Character/Gunner/Effect/Particle/SilverBulletParticle.ptl", (int)this);
          else
            v8 = nullptr;
          *(this + 253) = (int)v8;
          (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v8 + 112))(v8, this);
          result = *(this + 243);
          if ( result == 1 )
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 28))(*(this + 253));
            v10 = -30;
          }
          else
          {
            if ( result != 2 )
              return result;
            v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 28))(*(this + 253));
            v10 = -45;
          }
          *(uint32_t *)(v9 + 76) = v10;
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 253) + 36))(*(this + 253));
          *(uint32_t *)(result + 28) = v10;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x608890 CNGunnerBullet__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ sub_608890(int *this, int a2, float *a3, int a4)
{
  int v4; // ebx
  int v5; // eax
  int v7; // eax
  int v8; // eax
  void *v9; // eax
  int v10; // eax
  float *v11; // edi
  char *v12; // eax
  int v13; // eax
  int v14; // eax
  char *v15; // edi
  int v16; // ecx
  int v17; // edi
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  bool v24; // cc
  int v25; // eax
  int v26; // eax
  int v28; // [esp-8h] [ebp-38h]
  BOOL v29; // [esp-4h] [ebp-34h]
  int v30; // [esp+Ch] [ebp-24h]
  int v31; // [esp+10h] [ebp-20h]
  int v32; // [esp+10h] [ebp-20h]
  int v33; // [esp+10h] [ebp-20h]
  int v34; // [esp+14h] [ebp-1Ch]
  int v35; // [esp+14h] [ebp-1Ch]
  int v36; // [esp+18h] [ebp-18h]
  int v37; // [esp+18h] [ebp-18h]
  int v38; // [esp+1Ch] [ebp-14h]
  char *v39; // [esp+1Ch] [ebp-14h]
  int v40; // [esp+20h] [ebp-10h] BYREF
  int v41; // [esp+2Ch] [ebp-4h]
  int v42; // [esp+38h] [ebp+8h]
  int i; // [esp+38h] [ebp+8h]
  uint32_t *v44; // [esp+3Ch] [ebp+Ch]
  int v45; // [esp+3Ch] [ebp+Ch]

  v4 = a2;
  v5 = *(uint32_t *)a2;
  v40 = 100;
  (*(void (/*thiscall*/ **)(int, int *, int *))(v5 + 648))(a2, &v40, this);
  if ( (uint8_t)a4 == 0 )
  {
    v7 = __RTDynamicCast(
           *(this + 173),
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNGunner `RTTI Type Descriptor',
           0);
    if ( v7 != 0 )
    {
      v8 = 28 * (*(this + 246) == 5) + v7 + 8404;
      if ( *(uint32_t *)(v8 + 24) < 0x10u )
        v9 = (void *)(v8 + 4);
      else
        v9 = *(void **)(v8 + 4);
      sub_432EA0(v9, -1, 0, 0);
    }
  }
  v10 = *(this + 248);
  v11 = a3;
  if ( v10 == 1 )
  {
    if ( (uint8_t)a4 == 0 && v40 > 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 308))(a2) != 0 )
    {
      v12 = (char *)sub_47E720(2, *(this + 248));
      v31 = sub_47EFD0(v12, COERCE_FLOAT(1), *(this + 249), *(this + 245), *(this + 245), 0);
      v34 = (uint64_t)(a3[3] * 0.5 + *a3);
      v36 = (uint64_t)(a3[4] * 0.5 + a3[1]);
      v38 = (uint64_t)(a3[5] * 0.5 + a3[2]);
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      sub_4E4A50((int)a3, *(this + 173), 40002, v31, v34, v36, v38, v13, 0, 0, 0);
    }
  }
  else if ( v10 == 30 )
  {
    sub_607A70(a2, 1);
  }
  if ( *(this + 244) == 4 )
  {
    v14 = *(this + 246);
    if ( v14 == 9 || v14 == 6 )
    {
      v30 = (uint64_t)(a3[3] * 0.5 + *a3);
      v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
      v35 = (uint64_t)(a3[5] * 0.5 + a3[2]);
      v32 = sub_608300(*(this + 248), *(this + 243), *(this + 252));
      v15 = (char *)sub_44B6C0(284);
      v41 = 0;
      if ( v15 != nullptr )
      {
        sub_44E0D0(v15, v32, 1);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = nullptr;
      }
      v16 = *(this + 29);
      v39 = v15;
      v41 = -1;
      sub_45FE80(v16, (int)v15, 2, 0, (int)v15, a2, 0);
      v33 = *(uint32_t *)v15;
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
      v29 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v17;
      (*(void (/*thiscall*/ **)(char *))(v33 + 148))(v39);
      v18 = *(uint32_t *)v39;
      v28 = rand() % 6 + v35 - 3;
      v19 = rand();
      (*(void (/*thiscall*/ **)(char *, int, int, int))(v18 + 112))(v39, v19 % 6 + v30 - 3, v37, v28);
      v4 = a2;
      v20 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)v39 + 60))(v39, a2);
      sub_4A06D0(v20, v29);
      v11 = a3;
    }
  }
  if ( *(this + 244) != 3 )
  {
    v21 = *(this + 246);
    if ( v21 != 6 && v21 != 9 )
    {
      v22 = *(this + 250);
      if ( v22 != 0 )
        *(this + 99) -= v22;
      v23 = sub_607990(this) - 200;
      if ( v23 > 0 )
        *(this + 250) = -60 * v23 * (*(this + 99) + 100) / 400 / 100;
      else
        *(this + 250) = 0;
      *(this + 99) += *(this + 250);
    }
  }
  *(this + 255) = v4;
  v42 = 0;
  v44 = this + 256;
  do
  {
    *v44 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, v42);
    v24 = ++v42 < 3;
    ++v44;
  }
  while ( v24 );
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) != 0 )
  {
    v25 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v25 + 40))(v25, 273) != 0 )
    {
      v45 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v45 + 1032))(v45) == 2 )
      {
        for ( i = 0; i < 18; ++i )
        {
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v45 + 792))(v45, i) != 0 )
          {
            v26 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v45 + 792))(v45, i);
            (*(void (/*thiscall*/ **)(int, int, float *, int, int, int *))(*(uint32_t *)v26 + 136))(
              v26,
              v4,
              v11,
              a4,
              1,
              this + 97);
          }
        }
      }
    }
  }
  return sub_5FF9C0(v4, v11, a4);
}


// ------------------------------------------------------------
// 0x608CD0 CNGunnerBullet__vmt2A8
// ------------------------------------------------------------
void /*thiscall*/ CNGunnerBullet__vmt2A8(int this, int a2)
{
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  void *v9; // eax
  int v10; // [esp-4h] [ebp-10h]
  int v11; // [esp+14h] [ebp+8h]

  v3 = *(uint32_t *)(this + 692);
  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  if ( v3 != a2 && *(uint8_t *)(this + 1038) == 0 )
  {
    v4 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    if ( v4 != 0 )
    {
      *(uint32_t *)(this + 980) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 8 )
      {
        *(uint32_t *)(this + 972) = *(uint8_t *)(v4 + 8596) != 0;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 7 )
      {
        *(uint32_t *)(this + 972) = 2;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 18 )
      {
        *(uint32_t *)(this + 972) = 3;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 20 )
      {
        *(uint32_t *)(this + 972) = rand() % 4;
      }
      else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 27 )
      {
        *(uint32_t *)(this + 972) = 0;
      }
      *(uint32_t *)(this + 976) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1096))(v4);
      *(uint32_t *)(this + 696) = sub_41A5E0(v4 + 8502);
      sub_6078B0((uint32_t *)this);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1332))(v4);
      v6 = v5;
      if ( v5 != -1 )
      {
        v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1160))(v4, v5);
        if ( v11 != 0 )
        {
          v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1140))(v4, v6);
          sub_6073E0((uint32_t *)this, v11, v7);
        }
        else
        {
          off_77F3FC(aCriticalError_43, v6);
        }
      }
      v8 = *(uint32_t *)(v4 + 8656);
      if ( v8 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v8 + 136))(*(uint32_t *)(v4 + 8656)) != 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 132))(v8);
        v9 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 128))(v8);
        sub_608730((int *)this, v9, v10);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 308))(v4) != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1104))(v4, 8);
      *(uint8_t *)(this + 1038) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x608EA0 sub_608EA0
// ------------------------------------------------------------
int /*thiscall*/ sub_608EA0(int this)
{
  int v1; // eax
  int result; // eax

  if ( *(uint32_t *)(this + 6556) != 22 )
    return 0;
  v1 = *(uint32_t *)(this + 8516);
  if ( v1 != 13 && v1 != 36 )
    return 0;
  result = 1;
  if ( *(uint32_t *)(this + 8968) != 1 || *(uint8_t *)(this + 9301) != 0 )
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x608EE0 sub_608EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_608EE0(int this)
{
  *(uint32_t *)(this + 972) = -1;
  *(uint32_t *)(this + 976) = -1;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint8_t *)(this + 985) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x608F10 sub_608F10
// ------------------------------------------------------------
char /*thiscall*/ sub_608F10(uint32_t *this, uint32_t *a2, int a3)
{
  int v4; // eax
  int v5; // eax

  v4 = sub_41A5E0((unsigned int)(a2 + 1));
  *(this + 244) = v4;
  *(this + 245) = a3;
  if ( v4 == 13 || v4 == 36 )
  {
    v5 = sub_47EF20(a2, 2u, a3, -1, -1, 11);
    LOBYTE(v4) = sub_607260(this + 248, v5, -1, 0, 0);
  }
  return v4;
}



// ------------------------------------------------------------
// 0x608F70 CNGunnerSubWeaponBullet__vmt158
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt158(int this, int a2)
{
  int result; // eax
  char *v4; // eax

  IRDCollisionObject__vmt158((char *)this, a2);
  result = *(uint32_t *)(this + 976);
  if ( result == 12 || result == 13 || result == 36 || result == 14 || result == 40 )
  {
    v4 = (char *)sub_47E720(2, *(uint32_t *)(this + 976));
    result = sub_47EFD0(v4, 0.0, *(uint32_t *)(this + 980), *(uint32_t *)(this + 972), *(uint32_t *)(this + 972), 0);
    *(float *)(this + 388) = (float)result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x608FE0 CNGunnerSubWeaponBullet__vmt14C
// ------------------------------------------------------------
char /*usercall*/ CNGunnerSubWeaponBullet__vmt14C@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // edi
  int v6; // ecx
  char v7; // bl
  int v8; // edx
  int v9; // eax
  double v10; // st7
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  float v21; // [esp+4h] [ebp-1Ch] BYREF
  float v22; // [esp+8h] [ebp-18h]
  float v23; // [esp+Ch] [ebp-14h]
  int v24; // [esp+10h] [ebp-10h]
  int v25; // [esp+14h] [ebp-Ch]
  int v26; // [esp+18h] [ebp-8h]
  int v27; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C(a1);
  v4 = *(uint32_t *)(a1 + 976);
  if ( v4 == 14 )
  {
    v5 = __RTDynamicCast(
           *(uint32_t *)(a1 + 692),
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNGunner `RTTI Type Descriptor',
           0);
    LOBYTE(v4) = *(uint8_t *)(a1 + 985);
    if ( (uint8_t)v4 == 0 && v5 != 0 )
    {
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 308))(v5);
      if ( (uint8_t)v4 != 0 )
      {
        v6 = *(uint32_t *)(v5 + 9344);
        if ( v6 != 0 )
        {
          LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 724))(v6);
          if ( (uint8_t)v4 == 0 )
          {
            v7 = *(uint8_t *)(v5 + 9368);
            v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(a1 + 112) + 104) + 44))(*(uint32_t *)(*(uint32_t *)(a1 + 112) + 104));
            if ( v4 >= (uint8_t)(v7 != 0 ? 0 : 0x5A) )
            {
              v8 = *(uint32_t *)a1;
              v21 = 0.0;
              v22 = 0.0;
              v23 = 0.0;
              v24 = 0;
              v25 = 0;
              v26 = 0;
              if ( (*(int (/*thiscall*/ **)(int, int))(v8 + 152))(a1, a3) != 0 )
                v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 3;
              else
                v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 3;
              v27 = v9;
              v10 = (double)v9;
              v11 = *(uint32_t *)a1;
              v21 = v10;
              v12 = (*(int (/*thiscall*/ **)(int))(v11 + 124))(a1);
              v13 = *(uint32_t *)a1;
              v27 = v12;
              v22 = (float)v12;
              v14 = (*(int (/*thiscall*/ **)(int))(v13 + 128))(a1);
              v15 = *(uint32_t *)(v5 + 9344);
              v27 = v14 + 3;
              v23 = (float)(v14 + 3);
              sub_4E5F70(a2, a1, v15, &v21, 1, 1);
              LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 312))(a1, 1);
              *(uint8_t *)(a1 + 985) = 1;
            }
          }
        }
      }
    }
  }
  else if ( v4 == 13 || v4 == 36 )
  {
    v16 = sub_699000(a1 + 64);
    if ( sub_6072C0((uint8_t *)(a1 + 992), v16) != 0 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 352))(a1);
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
    if ( (uint8_t)v4 != 0 )
    {
      v17 = __RTDynamicCast(
              *(uint32_t *)(a1 + 692),
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &CNGunner `RTTI Type Descriptor',
              0);
      if ( v17 == 0 || (LOBYTE(v4) = sub_608EA0(v17), (uint8_t)v4 == 0) )
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x6091B0 CNGunnerSubWeaponBullet__vmt12C
// ------------------------------------------------------------
void /*userpurge*/ CNGunnerSubWeaponBullet__vmt12C(uint32_t *a1@<ecx>, int a2@<edi>, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // edi
  char *v7; // eax
  int v8; // eax
  int v9; // ecx
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edx
  int v16; // [esp-20h] [ebp-30h]
  int v17; // [esp-1Ch] [ebp-2Ch]
  int v18; // [esp-18h] [ebp-28h]
  int v19; // [esp-14h] [ebp-24h]
  int v21; // [esp+8h] [ebp-8h]
  int v22; // [esp+Ch] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 684))(a1) != 0
    && (v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 684))(a1),
        (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 40))(v4, 273) != 0)
    && (v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 684))(a1),
        *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 1032))(v5) == 2) )
  {
    v6 = a3;
    if ( a1[244] == 40 && ((uint32_t *)a3 == a1 || a1[247] == a3) )
    {
      if ( a1[247] != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 308))(a1, a2) != 0 )
        {
          v7 = (char *)sub_47E720(2, a1[244]);
          v21 = sub_47EFD0(v7, COERCE_FLOAT(1), a1[245], a1[243], a1[243], 0);
          v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[247] + 200))(a1[247]);
          v9 = a1[247];
          if ( v8 != 0 )
          {
            v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 200))(v9);
            v11 = sub_42F220(v10);
            v12 = sub_4918E0(v11, 2);
          }
          else
          {
            v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 192))(v9);
          }
          v22 = v12;
          v13 = a1[247];
          v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 128))(v13) - (uint64_t)((double)v22 * -0.69999999);
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13) + 1;
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13);
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 684))(a1);
          sub_4E4A50(v14, 40002, v21, v16, v17, v18, v19, 0, 0, 0);
          v6 = a3;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*a1 + 212))(a1, "DIFFUSION_GUN_EX", -1, 0);
      }
      if ( a1[247] == v6 )
      {
        v15 = *a1;
        a1[247] = 0;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v15 + 312))(a1, 0);
      }
    }
    CNRDPassiveObject__vmt12C(a1, v6);
  }
  else
  {
    CNRDPassiveObject__vmt12C(a1, a3);
  }
}



// ------------------------------------------------------------
// 0x609380 CNGunnerSubWeaponBullet__vmt28C
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt28C(uint32_t *this, bool *a2)
{
  uint32_t *v2; // edx
  int v3; // edx

  v2 = (uint32_t *)*(this + 87);
  *a2 = v2 != nullptr && (*(this + 88) - (int)v2) >> 2 != 0 && *v2 == 1;
  v3 = *(this + 178);
  if ( v3 != 0 && (*(this + 179) - v3) >> 2 != 0 )
    return sub_41ACF0(*(this + 178));
  else
    return 0;
}



// ------------------------------------------------------------
// 0x6093E0 CNGunnerSubWeaponBullet__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNGunnerSubWeaponBullet__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax
  float *v6; // ebx
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  int v9; // edx
  int v10; // eax
  uint32_t *v11; // eax
  int v12; // eax
  int v13; // edi
  double v14; // st7
  int v15; // ebx
  int v16; // eax
  int v18; // [esp-4h] [ebp-18h]
  int v19; // [esp+0h] [ebp-14h]
  int v20; // [esp+Ch] [ebp-8h]

  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  v6 = a3;
  v7 = a2;
  if ( __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0) != 0
    && *(this + 244) == 40
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0
    && *(this + 247) == 0 )
  {
    v8 = (uint32_t *)*(this + 36);
    v9 = *this;
    *(this + 247) = (int)a2;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v9 + 196))(this, *v8);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    v11 = (uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v10 + 104) + 16))(*(uint32_t *)(v10 + 104)) + 15);
    *v11 = 0;
    v11[1] = 0;
    v11[2] = 0;
    v11[3] = 0;
    v11[4] = 0;
    v11[5] = 0;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v12 + 104) + 4))(*(uint32_t *)(v12 + 104), 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
    v20 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 247) + 120))(*(this + 247));
    v13 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 247) + 124))(*(this + 247)) + 1;
    v14 = a3[5] * 0.5 + a3[2];
    v15 = *this;
    v18 = rand() % 6 + (uint64_t)v14 - 3;
    v16 = rand();
    (*(void (/*thiscall*/ **)(int *, int, int, int))(v15 + 112))(this, v16 % 6 + v20 - 3, v13, v18);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 60))(this, *(this + 247));
    sub_4A06D0(v19);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*this + 212))(this, "DIFFUSION_GUN_CHARGE", -1, 0);
    v7 = a2;
    v6 = a3;
  }
  return CNRDPassiveObject__vmt1F4(this, v7, v6, a4);
}



// ------------------------------------------------------------
// 0x609550 CNGunnerSubWeaponBullet__vmt2A8
// ------------------------------------------------------------
void /*thiscall*/ CNGunnerSubWeaponBullet__vmt2A8(int this, int a2)
{
  int v3; // ebx
  int v4; // esi
  int v5; // ebx
  int v6; // eax
  uint32_t *v7; // eax

  v3 = *(uint32_t *)(this + 692);
  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  if ( v3 != a2 && *(uint8_t *)(this + 984) == 0 )
  {
    v4 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    if ( v4 != 0 )
    {
      *(uint32_t *)(this + 972) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1332))(v4);
      if ( v5 != -1 )
      {
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1140))(v4);
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v4 + 1160))(v4, v5, v6);
        sub_608F10((uint32_t *)this, v7, v5);
      }
      if ( *(uint32_t *)(this + 976) == 40 )
        sub_406D60("R_DIFFUSION_GUNA");
    }
    *(uint8_t *)(this + 984) = 1;
  }
}



// ------------------------------------------------------------
// 0x609600 sub_609600
// ------------------------------------------------------------
int /*thiscall*/ sub_609600(uint32_t *this, int a2)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 249) = 0;
  *(this + 248) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
}



// ------------------------------------------------------------
// 0x609630 sub_609630
// ------------------------------------------------------------
int /*thiscall*/ sub_609630(float *this, int a2, int a3, int a4)
{
  int v5; // ebx
  int v6; // ecx
  int v7; // eax
  int v8; // edi
  double v9; // st7
  int result; // eax
  int v11; // ecx
  uint32_t v12[3]; // [esp+Ch] [ebp-18h] BYREF
  int v13; // [esp+18h] [ebp-Ch]
  int v14; // [esp+1Ch] [ebp-8h]
  int v15; // [esp+20h] [ebp-4h]

  v12[0] = a2;
  v12[1] = a3;
  v5 = 0;
  v12[2] = a4;
  v13 = 16 - (uint32_t)v12;
  while ( 1 )
  {
    v6 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 116))(this, v5);
    v15 = v12[v5];
    v7 = *(uint32_t *)this;
    v14 = v6;
    v8 = abs32(v15 - v6);
    if ( v8 > 3 * (*(int (/*thiscall*/ **)(float *))(v7 + 708))(this) )
      break;
    v9 = sub_4049C0(0.0, *(this + 250), v8, *((uint32_t *)this + 251));
    if ( v15 >= v14 )
    {
      if ( v15 == v14 )
        v9 = 0.0;
    }
    else
    {
      v9 = v9 * -1.0;
    }
    result = 4 * v5;
    v11 = 4 * v5++ + v13 + *((uint32_t *)this + 28);
    *(float *)((char *)v12 + v11) = v9;
    if ( v5 >= 3 )
      return result;
  }
  (*(void (/*thiscall*/ **)(float *, int, int, int))(*(uint32_t *)this + 112))(this, a2, a3, a4);
  *(uint32_t *)(*((uint32_t *)this + 28) + 16) = 0;
  *(uint32_t *)(*((uint32_t *)this + 28) + 20) = 0;
  *(uint32_t *)(*((uint32_t *)this + 28) + 24) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x609720 CNRDJoint__vmt2C8
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt2C8(uint32_t *this, int a2)
{
  int result; // eax

  if ( *(this + 243) == 2 )
    return off_77F3FC(aCriticalError_44);
  *(this + 243) = a2;
  *(this + 248) = sub_699000((int)(this + 2));
  result = *(this + 243) - 2;
  if ( *(this + 243) == 2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609790 CNRDJoint__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt12C(uint32_t *this, int a2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
  if ( a2 == result )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 680))(this, this);
  if ( a2 == *(this + 244) )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 728))(this);
  return result;
}



// ------------------------------------------------------------
// 0x6097E0 CNRDJoint__vmt2D8
// ------------------------------------------------------------
void /*thiscall*/ CNRDJoint__vmt2D8(uint32_t *this)
{
  *(this + 244) = 0;
}



// ------------------------------------------------------------
// 0x6097F0 CNRDJoint__vmt2CC
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt2CC(uint8_t *this)
{
  int result; // eax

  if ( *(this + 264) != 1 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 196))(this, 0);
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609820 sub_609820
// ------------------------------------------------------------
int /*thiscall*/ sub_609820(int this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  float v7; // edi
  int v8; // eax
  int v9; // edi
  int v11; // [esp+8h] [ebp-8h] BYREF
  int v12; // [esp+Ch] [ebp-4h] BYREF

  v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 976) + 120))(*(uint32_t *)(this + 976));
  v3 = *(uint32_t *)(this + 976);
  *(uint32_t *)(this + 980) = v2;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
  v5 = *(uint32_t *)(this + 976);
  *(uint32_t *)(this + 984) = v4;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 128))(v5);
  v7 = *(float *)this;
  *(uint32_t *)(this + 988) = v6;
  v8 = (*(int (/*thiscall*/ **)(int))(LODWORD(v7) + 708))(this);
  (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, int))(LODWORD(v7) + 172))(
    this,
    &v11,
    &v12,
    *(uint32_t *)(this + 976),
    v8);
  sub_609630((float *)this, v11, v12, *(uint32_t *)(this + 988));
  v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 976) + 120))(*(uint32_t *)(this + 976));
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < v9 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 148))(this, 1);
  else
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 148))(this, 0);
}



// ------------------------------------------------------------
// 0x6098E0 CNRDJoint__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNRDJoint__vmt14C(uint32_t *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 244) != 0 )
    sub_609820((int)this);
  if ( *(this + 243) == 1 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 720))(this);
  result = *(this + 243) - 2;
  if ( *(this + 243) == 2 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 716))(this);
  return result;
}



// ------------------------------------------------------------
// 0x609920 sub_609920
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_609920(uint32_t *this, int a2)
{
  uint32_t *v2; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *v5; // eax
  unsigned int result; // eax

  v2 = this + 1768;
  v3 = v2[1];
  if ( v3 != 0 )
    v4 = (v2[2] - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (v2[3] - v3) >> 2 )
    return sub_4E75F0((int)v2, v2[2], 1u, &a2);
  v5 = (int *)v2[2];
  *v5 = a2;
  result = (unsigned int)(v5 + 1);
  v2[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x609980 CNRDJoint__vmt2BC
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDJoint__vmt2BC(float *this, const void *a2, size_t Size)
{
  int v4; // esi
  int v5; // eax
  unsigned int result; // eax
  int v7; // edi
  size_t v8; // eax
  float v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  uint16_t v14[4]; // [esp+Ch] [ebp-10h] BYREF
  int v15; // [esp+14h] [ebp-8h]
  uint32_t *v16; // [esp+24h] [ebp+8h]
  size_t Sizea; // [esp+28h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  qmemcpy(v14, a2, Size);
  v4 = sub_45EBE0(*((uint32_t **)this + 29), v14[2], v14[3]);
  v5 = sub_45EBE0(*((uint32_t **)this + 29), v14[0], v14[1]);
  result = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  v16 = (uint32_t *)result;
  if ( v4 != 0 && result != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 708))(this);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 152))(v4) != 0 )
      v7 = -v7;
    v8 = v7 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 120))(v4);
    v9 = *this;
    Sizea = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4);
    v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 124))(v4, v10);
    (*(void (/*thiscall*/ **)(float *, size_t, int))(LODWORD(v9) + 112))(this, Sizea, v11);
    v12 = *(uint32_t *)this;
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 152))(v4);
    (*(void (/*thiscall*/ **)(float *, int))(v12 + 148))(this, v13);
    (*(void (/*thiscall*/ **)(float *, uint32_t *))(*(uint32_t *)this + 680))(this, v16);
    *(this + 250) = (float)v15;
    *((uint32_t *)this + 244) = v4;
    return sub_609920(v16, (int)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609A90 sub_609A90
// ------------------------------------------------------------
int /*thiscall*/ sub_609A90(int this)
{
  *(uint32_t *)(this + 96) = 1057;
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 4;
  *(uint8_t *)(this + 1000) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x609AD0 CNCutableGrass__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CNCutableGrass__vmtC(int this)
{
  char result; // al

  CNRDPassiveObject__vmtC((int *)this);
  result = *(uint8_t *)(this + 972);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x609AF0 sub_609AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_609AF0(uint32_t *this, uint32_t *a2)
{
  if ( a2 == this
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 488))(this, a2) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 128))(a2) > *(this + 40) )
  {
    return 4;
  }
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 60))(a2) + 16) > 0.0 )
    return 1;
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 60))(a2) + 16) < 0.0 )
    return 0;
  if ( *(float *)((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 60))(a2) + 20) == 0.0 )
    return 4;
  else
    return (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 152))(a2);
}



// ------------------------------------------------------------
// 0x609BA0 sub_609BA0
// ------------------------------------------------------------
int /*thiscall*/ sub_609BA0(int *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int v4; // esi
  bool v5; // zf
  int v6; // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = *(this + 252);
  v5 = v4 == *(this + 253);
  *(this + 246) = 0;
  if ( !v5 )
  {
    do
    {
      v6 = *(uint32_t *)(v4 + 4);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 4))(v6, 1);
      *(uint32_t *)(v4 + 4) = 0;
      result = *(this + 253);
      v4 += 8;
    }
    while ( v4 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x609C00 CNCutableGrass__vmt2D0
// ------------------------------------------------------------
int /*thiscall*/ CNCutableGrass__vmt2D0(uint32_t **this)
{
  return ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));
}



// ------------------------------------------------------------
// 0x609C20 sub_609C20
// ------------------------------------------------------------
char /*thiscall*/ sub_609C20(int *this, int a2)
{
  int v3; // eax
  int v4; // eax
  uint32_t *v5; // eax

  v3 = *(this + 249);
  if ( a2 != v3 )
  {
    LOBYTE(v3) = *((uint8_t *)this + 988);
    if ( (uint8_t)v3 != 0 )
    {
      if ( a2 == 4 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 34));
        LOBYTE(v3) = sub_4926A0(*(this + 30));
        *(this + 249) = 4;
      }
      else
      {
        v4 = *(this + 36);
        if ( a2 != 0 )
          v5 = (uint32_t *)(v4 + 8);
        else
          v5 = (uint32_t *)(v4 + 4);
        (*(void (/*stdcall*/ **)(uint32_t))(*this + 196))(*v5);
        LOBYTE(v3) = sub_4926A0(*(this + 30));
        *(this + 249) = a2;
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x609CA0 sub_609CA0
// ------------------------------------------------------------
void /*thiscall*/ sub_609CA0(int *this)
{
  int i; // edi
  int v3; // ecx
  int v4; // ebx
  int v5; // eax

  for ( i = 1; i < 3; ++i )
  {
    v3 = *(this + 178);
    if ( v3 != 0 && (*(this + 179) - v3) >> 2 > (unsigned int)i )
    {
      v4 = *this;
      v5 = sub_41ACF0(v3 + 4 * i);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v4 + 212))(this, v5, -1, 0, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x609CF0 CNCutableGrass__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNCutableGrass__vmt200(int this, int a2, float *a3, char a4)
{
  int *v5; // edx
  int *v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  void *v11; // ecx
  uint8_t v13[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+20h] [ebp-4h]
  int v18; // [esp+34h] [ebp+10h]

  v18 = CNRDPassiveObject__vmt200((int *)this, a2, a3, a4);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 716))(this);
  if ( *(uint32_t *)(this + 976) >= *(uint32_t *)(this + 980) )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, *(uint8_t *)(this + 972));
  else
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 720))(this);
  v5 = *(int **)(this + 984);
  if ( v5 != nullptr )
  {
    v6 = *(int **)(this + 348);
    if ( v6 != nullptr && (*(uint32_t *)(this + 352) - (int)v6) >> 2 != 0 )
      v7 = *v6;
    else
      v7 = 0;
    v8 = *v5;
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v7);
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v9);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 40))(*(uint32_t *)(this + 984), v10);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 984) + 12))(*(uint32_t *)(this + 984), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 984) + 92))(*(uint32_t *)(this + 984), v13);
    v11 = *(void **)(this + 116);
    v17 = 0;
    sub_4600B0(v11, 2, 0, (int)v13);
    v17 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v15 = 0;
    v16 = 0;
  }
  sub_609CA0((int *)this);
  *(uint8_t *)(this + 988) = 0;
  return v18;
}



// ------------------------------------------------------------
// 0x609E20 CNCutableGrass__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNCutableGrass__vmt14C(int this)
{
  unsigned int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  uint32_t *v9; // edi
  int v10; // eax
  char result; // al
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // ebx
  int v16; // ecx
  int v17; // edx
  int v18; // edi
  uint32_t v19[6]; // [esp+Ch] [ebp-1Ch] BYREF
  int v20; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 988) != 0 )
  {
    v2 = 0;
    if ( *(uint32_t *)(this + 992) != 0 )
    {
      v3 = sub_609AF0((uint32_t *)this, *(uint32_t **)(this + 992));
      if ( v3 == 4 )
        *(uint32_t *)(this + 992) = 0;
      sub_609C20((int *)this, v3);
    }
    if ( *(uint32_t *)(this + 992) == 0 )
    {
      v4 = *(uint32_t *)(this + 116);
      v5 = *(uint32_t *)(v4 + 120);
      v6 = v4 + 116;
      v20 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
      if ( v20 > 0 )
      {
        while ( 1 )
        {
          v7 = *(uint32_t *)(this + 116);
          v8 = *(uint32_t *)(v7 + 120);
          if ( v8 != 0 && v2 < (*(uint32_t *)(v7 + 124) - v8) >> 2 )
            v9 = *(uint32_t **)(v8 + 4 * v2);
          else
            v9 = nullptr;
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v9 + 40))(v9, 17) != 0 )
          {
            v10 = sub_609AF0((uint32_t *)this, v9);
            if ( v10 != 4 )
              break;
          }
          if ( (int)++v2 >= v20 )
            goto LABEL_20;
        }
        *(uint32_t *)(this + 992) = v9;
        sub_609C20((int *)this, v10);
      }
    }
  }
LABEL_20:
  result = *(uint8_t *)(this + 972);
  if ( result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);
    v12 = *(uint32_t *)(this + 116);
    v13 = *(uint32_t *)(v12 + 120);
    v14 = v12 + 116;
    v15 = 0;
    if ( v13 != 0 )
      v20 = (*(uint32_t *)(v14 + 8) - v13) >> 2;
    else
      v20 = 0;
    if ( v20 > 0 )
    {
      do
      {
        v16 = *(uint32_t *)(this + 116);
        v17 = *(uint32_t *)(v16 + 120);
        if ( v17 != 0 && v15 < (*(uint32_t *)(v16 + 124) - v17) >> 2 )
          v18 = *(uint32_t *)(v17 + 4 * v15);
        else
          v18 = 0;
        if ( (*(uint8_t *)(this + 1000) == 0
           || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 348))(v18) + 128) != 0)
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 360))(v18, this) == 0 )
        {
          memset(v19, 0, sizeof(v19));
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, uint32_t *))(*(uint32_t *)v18 + 480))(v18, this, v19) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 356))(v18, this);
            (*(void (/*thiscall*/ **)(int, int, uint32_t *, uint32_t))(*(uint32_t *)this + 512))(this, v18, v19, 0);
          }
        }
        ++v15;
      }
      while ( (int)v15 < v20 );
    }
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x609FF0 sub_609FF0
// ------------------------------------------------------------
void /*thiscall*/ sub_609FF0(int this, int a2, unsigned int a3, int a4)
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
      sub_52E630(this);
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
// 0x60A240 sub_60A240
// ------------------------------------------------------------
void /*thiscall*/ sub_60A240(int this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_63A7C0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_609FF0(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x60A2B0 CNCutableGrass__vmt2C4
// ------------------------------------------------------------
void /*thiscall*/ CNCutableGrass__vmt2C4(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_60A240((int)this + 1004, (int)v3);
}



// ------------------------------------------------------------
// 0x60A2E0 CNCutableGrass__vmt2C8
// ------------------------------------------------------------
void /*thiscall*/ CNCutableGrass__vmt2C8(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_474950((int)this + 1020, (int)v3);
}



// ------------------------------------------------------------
// 0x60A310 sub_60A310
// ------------------------------------------------------------
int /*thiscall*/ sub_60A310(uint32_t *this)
{
  void *v2; // ecx
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  uint32_t *v11; // ecx
  int result; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // eax

  v2 = (void *)*(this + 178);
  if ( v2 != nullptr && (*(this + 179) - (int)v2) >> 2 != 0 && sub_42FD40(v2, szPassword) )
  {
    if ( operator new(0x12Cu) != nullptr )
    {
      v3 = *(this + 178);
      if ( *(this + 96) < 0x10u )
      {
        v7 = sub_41ACF0(v3);
        v6 = sub_4C3640(this + 91, v7, this);
      }
      else
      {
        v4 = *(this + 91);
        v5 = sub_41ACF0(v3);
        v6 = sub_4C3640(v4, v5, this);
      }
    }
    else
    {
      v6 = 0;
    }
    *(this + 246) = v6;
  }
  v8 = *(this + 36);
  if ( v8 != 0
    && (unsigned int)((*(this + 37) - v8) >> 2) > 2
    && *(uint32_t *)(v8 + 4) != 0
    && *(uint32_t *)(*(this + 36) + 8) != 0 )
  {
    *((uint8_t *)this + 988) = 1;
  }
  v9 = rand();
  sub_493A60(*(this + 34), v9 % 1000);
  if ( *(this + 172) == 0 )
    *((uint8_t *)this + 972) = 1;
  v10 = *(this + 87);
  if ( v10 != 0 && (unsigned int)((*(this + 88) - v10) >> 2) > 1 && *(uint32_t *)(v10 + 4) == 1 )
    *((uint8_t *)this + 1000) = 1;
  v11 = (uint32_t *)*(this + 36);
  if ( v11 != nullptr && (*(this + 37) - (int)v11) >> 2 != 0 && *v11 != 0 )
    *(this + 245) = 2;
  else
    *(this + 245) = 1;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
  if ( result > 0 )
  {
    v13 = *this;
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
    v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v14);
    v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v15);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 112))(this, v16);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A4C0 sub_60A4C0
// ------------------------------------------------------------
void /*thiscall*/ sub_60A4C0(int *this)
{
  int v2; // ecx
  int *v3; // edi
  bool v4; // zf
  int *v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int *v10; // edi
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // ecx
  unsigned int j; // edi
  int v15; // ecx
  int v16; // [esp-Ch] [ebp-34h]
  void *Block; // [esp+Ch] [ebp-1Ch]
  unsigned int v18; // [esp+10h] [ebp-18h] BYREF
  int *v19; // [esp+14h] [ebp-14h]
  unsigned int i; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  v2 = *(this + 252);
  if ( v2 != 0 && (*(this + 253) - v2) >> 3 != 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    v3 = (int *)*(this + 252);
    v4 = v3 == (int *)*(this + 253);
    v19 = v3;
    for ( i = v18 % 0x168; !v4; i += 0x168 / v12 )
    {
      Block = operator new(0x424u);
      v21 = 0;
      if ( Block != nullptr )
        v5 = (int *)sub_4E2130(v3[1], &v18, i);
      else
        v5 = nullptr;
      v6 = *this;
      v7 = *v5;
      v21 = -1;
      v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 124))(this, 60);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int *, int))(v7 + 112))(v5, v9);
      v16 = (int)v5;
      v10 = v19;
      sub_45FE80(*(this + 29), (int)v19, 289, *v19, v16, 0, 0);
      v11 = *(this + 252);
      if ( v11 != 0 )
        v12 = (*(this + 253) - v11) >> 3;
      else
        v12 = 0;
      v3 = v10 + 2;
      v19 = v3;
      v4 = v3 == (int *)*(this + 253);
    }
    if ( *(this + 252) != 0 )
      j__free((void *)*(this + 252));
    *(this + 252) = 0;
    *(this + 253) = 0;
    *(this + 254) = 0;
  }
  v13 = *(this + 256);
  if ( v13 != 0
    && (*(this + 257) - v13) >> 3 != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    for ( j = 0; ; ++j )
    {
      v15 = *(this + 256);
      if ( v15 == 0 || j >= (*(this + 257) - v15) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(v15 + 8 * j),
        *(uint32_t *)(v15 + 8 * j + 4),
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x60A670 CNCutableGrass__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNCutableGrass__vmt12C(int *this, int a2)
{
  int v2; // ebx
  int *v4; // edx
  int *v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  v2 = a2;
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (int *)a2 == this )
  {
    if ( *(this + 244) < *(this + 245) )
    {
      v4 = (int *)*(this + 246);
      if ( v4 != nullptr )
      {
        v5 = (int *)*(this + 87);
        if ( v5 != nullptr && (*(this + 88) - (int)v5) >> 2 != 0 )
          v6 = *v5;
        else
          v6 = 0;
        v7 = *v4;
        v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v7 + 40))(*(this + 246), v9);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 246) + 92))(*(this + 246), v11);
        v10 = (void *)*(this + 29);
        v15 = 0;
        sub_4600B0(v10, 2, 0, (int)v11);
        v15 = -1;
        if ( Block != nullptr )
          j__free(Block);
        v2 = a2;
        Block = nullptr;
        v13 = 0;
        v14 = 0;
      }
      sub_609CA0(this);
      *(this + 244) = *(this + 245);
    }
    sub_60A4C0(this);
  }
  if ( *(this + 248) == v2 )
    *(this + 248) = 0;
}



// ------------------------------------------------------------
// 0x60A790 CNMapObject__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNMapObject__vmtC(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmtC(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
  if ( result > 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    return (*(int (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A7D0 sub_60A7D0
// ------------------------------------------------------------
bool /*thiscall*/ sub_60A7D0(void *this, void *a2)
{
  return a2 != this && (*(uint8_t (/*thiscall*/ **)(void *, void *))(*(uint32_t *)this + 488))(this, a2) != 0;
}



// ------------------------------------------------------------
// 0x60A800 sub_60A800
// ------------------------------------------------------------
void /*thiscall*/ sub_60A800(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  bool v6; // zf
  signed int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // [esp-2Ch] [ebp-40h]
  int v12; // [esp-28h] [ebp-3Ch]
  int v13; // [esp-24h] [ebp-38h]
  int v14; // [esp-20h] [ebp-34h]
  uint8_t *v15; // [esp-1Ch] [ebp-30h]
  int v16; // [esp-18h] [ebp-2Ch]
  int v17; // [esp-14h] [ebp-28h]
  uint16_t v18[2]; // [esp+Ch] [ebp-8h] BYREF
  char ArgList[4]; // [esp+10h] [ebp-4h]

  if ( *(this + 78) < 0x10u )
    *(uint32_t *)ArgList = this + 73;
  else
    *(uint32_t *)ArgList = *(this + 73);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 52))(this, a2, a3, a4);
  off_77F3FC((char *)&byte_73B39C, *(uint32_t *)ArgList, v5);
  sub_432FA0();
  v7 = rand() & 0x80000001;
  v6 = v7 == 0;
  if ( v7 < 0 )
    v6 = (((uint8_t)v7 - 1) | 0xFFFFFFFE) == -1;
  if ( v6 )
  {
    v17 = a4;
    v16 = 0;
    v15 = nullptr;
    v14 = 0;
    v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v12 = 0;
  }
  else
  {
    v18[0] = rand() % 100 + 50;
    v18[1] = rand() % 50 + 25;
    ArgList[2] = rand() % 2 == 0;
    ArgList[3] = 3 - (rand() % 2 != 0);
    v8 = rand() % 60;
    v9 = *this;
    v17 = a4;
    v16 = 8;
    *(uint16_t *)ArgList = v8 + 40;
    v15 = v18;
    v14 = 1;
    v13 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 152))(this);
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 10;
  }
  v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  IRDCollisionObject__vmt250(this, a3, (int)this, a2, 100, a3, v10, v11, v12, v13, v14, v15, v16, v17, 1, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x60A950 sub_60A950
// ------------------------------------------------------------
int /*thiscall*/ sub_60A950(uint32_t *this)
{
  uint32_t *v2; // esi
  int i; // edi
  int result; // eax
  int v5; // esi
  int v6; // ecx

  v2 = this + 255;
  for ( i = 3; i != 0; --i )
  {
    if ( *v2 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  v5 = *(this + 262);
  if ( v5 != *(this + 263) )
  {
    do
    {
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 4))(v6, 1);
      *(uint32_t *)(v5 + 4) = 0;
      result = *(this + 263);
      v5 += 8;
    }
    while ( v5 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x60A9B0 sub_60A9B0
// ------------------------------------------------------------
char /*thiscall*/ sub_60A9B0(uint32_t *this, int a2)
{
  int v2; // esi
  unsigned int i; // edx

  v2 = *(this + 251);
  for ( i = 0; v2 != 0 && i < (*(this + 252) - v2) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 251) + 4 * i) == a2 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x60AA00 sub_60AA00
// ------------------------------------------------------------
void /*thiscall*/ sub_60AA00(int this)
{
  void **v2; // edi
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 96) = 1057;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  v2 = (void **)(this + 1032);
  for ( i = 3; i != 0; --i )
    sub_41BFE0(v2++, nullptr);
  if ( *(uint32_t *)(this + 1004) != 0 )
    j__free(*(void **)(this + 1004));
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 1092) = 0;
  *(uint8_t *)(this + 1096) = 0;
  *(uint32_t *)(this + 1016) = 4;
}



// ------------------------------------------------------------
// 0x60AAB0 sub_60AAB0
// ------------------------------------------------------------
char /*thiscall*/ sub_60AAB0(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int i; // ecx

  v3 = *(this + 251);
  for ( i = 0; v3 != 0 && i < (*(this + 252) - v3) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 251) + 4 * i) == a2 )
    {
      memcpy_0(
        (void *)(*(this + 251) + 4 * i),
        (const void *)(*(this + 251) + 4 * i + 4),
        4 * ((int)(*(this + 252) - (*(this + 251) + 4 * i + 4)) >> 2));
      *(this + 252) -= 4;
      return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x60AB30 CNMapObject__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNMapObject__vmt12C(uint32_t *this, int a2)
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, a2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 1);
  if ( result != 0 )
    return sub_60AAB0(this, a2);
  return result;
}



// ------------------------------------------------------------
// 0x60AB60 sub_60AB60
// ------------------------------------------------------------
void /*thiscall*/ sub_60AB60(uint32_t *this)
{
  int v2; // ecx
  unsigned int i; // edi
  int v4; // ecx

  v2 = *(this + 266);
  if ( v2 != 0
    && (*(this + 267) - v2) >> 3 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *(this + 266);
      if ( v4 == 0 || i >= (*(this + 267) - v4) >> 3 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(v4 + 8 * i),
        *(uint32_t *)(v4 + 8 * i + 4),
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
  }
}



// ------------------------------------------------------------
// 0x60ABE0 sub_60ABE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_60ABE0(unsigned int *this)
{
  unsigned int result; // eax
  unsigned int v3; // edi
  int i; // ebx

  result = *(this + 270);
  if ( result != 0 )
  {
    result = (int)(*(this + 271) - result) / 12;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
      {
        v3 = 0;
        for ( i = 0; ; i += 12 )
        {
          result = *(this + 270);
          if ( result == 0 )
            break;
          result = (int)(*(this + 271) - result) / 12;
          if ( v3 >= result )
            break;
          sub_60A800(
            this,
            *(uint32_t *)(i + *(this + 270)),
            *(uint32_t *)(*(this + 270) + i + 4),
            *(uint32_t *)(*(this + 270) + i + 8));
          ++v3;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60AC80 CNMapObject__vmt2DC
// ------------------------------------------------------------
int /*thiscall*/ CNMapObject__vmt2DC(int **this)
{
  int *v2; // edx
  int *v3; // ecx
  int v4; // ecx
  int *v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  int result; // eax
  int v12; // eax
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v15; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int *v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  v2 = *this;
  if ( *(this + 246) != *(this + 247) )
    return ((int (/*thiscall*/ *)(int **))v2[187])(this);
  ((void (/*thiscall*/ *)(int **))v2[186])(this);
  v3 = *(this + 36);
  if ( v3 != nullptr && *(this + 37) - v3 != 0 )
  {
    v4 = *v3;
    if ( v4 != 0 )
      ((void (/*thiscall*/ *)(int **, int))(*this)[49])(this, v4);
  }
  v5 = *(this + 256);
  if ( v5 != nullptr )
  {
    v6 = *v5;
    v7 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
    v8 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, (int)*(this + 245) + v7);
    v9 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, (int)*(this + 244) + v8);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*(this + 256), (int)*(this + 243) + v9);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 256) + 12))(*(this + 256), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 256) + 92))(*(this + 256), v13);
    v10 = *(this + 29);
    v18 = 0;
    sub_4600B0(v10, 2, 0, (int)v13);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v15 = 0;
    v16 = 0;
  }
  result = sub_41ACF0(this + 259);
  if ( result != 0 )
  {
    v17 = *this;
    v12 = sub_41ACF0(this + 259);
    return ((int (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v17[53])(this, v12, -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60ADE0 CNMapObject__vmt2B4
// ------------------------------------------------------------
int /*thiscall*/ CNMapObject__vmt2B4(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int v8; // ecx

  result = *(this + 170);
  if ( result > 0 )
  {
    v8 = *(this + 36);
    if ( v8 != 0 )
    {
      result = (*(this + 37) - v8) >> 2;
      if ( (unsigned int)result > 1 )
      {
        result = *(this + 36);
        if ( *(uint32_t *)(v8 + 4) != 0 )
        {
          *(this + 273) = 1;
          sub_4926A0(*(uint32_t *)(result + 4));
          result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
        }
      }
    }
  }
  else
  {
    ++*(this + 246);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 732))(this);
    *(this + 170) = *(this + 171);
  }
  if ( *(this + 246) >= *(this + 248) && *((uint8_t *)this + 996) == 1 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 736))(this, a2);
  return result;
}



// ------------------------------------------------------------
// 0x60AE90 CNMapObject__vmt2E0
// ------------------------------------------------------------
int /*thiscall*/ CNMapObject__vmt2E0(int **this, int a2)
{
  int *v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  int v9; // eax
  int result; // eax
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h]
  int v14; // [esp+18h] [ebp-14h]
  int *v15; // [esp+1Ch] [ebp-10h]
  int v16; // [esp+28h] [ebp-4h]

  v3 = *(this + 257);
  if ( v3 != nullptr )
  {
    v4 = *v3;
    v5 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
    v6 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, (int)*(this + 245) + v5);
    v7 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, (int)*(this + 244) + v6);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(this + 257), (int)*(this + 243) + v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 257) + 12))(*(this + 257), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 257) + 92))(*(this + 257), v11);
    v8 = *(this + 29);
    v16 = 0;
    sub_4600B0(v8, 2, 0, (int)v11);
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = 0;
    v14 = 0;
  }
  if ( sub_41ACF0(this + 260) != 0 )
  {
    v15 = *this;
    v9 = sub_41ACF0(this + 260);
    ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v15[53])(this, v9, -1, 0, 0);
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
  if ( (uint8_t)result != 0 )
    return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60AFA0 sub_60AFA0
// ------------------------------------------------------------
int /*thiscall*/ sub_60AFA0(int *this, char *a2, unsigned int a3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  int result; // eax
  unsigned int v9; // ecx
  int v11; // eax
  int v12; // eax
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  unsigned int v17; // edi
  uint32_t *v18; // ecx
  int v20; // edi
  uint32_t *v21; // [esp-18h] [ebp-40h]
  int v22; // [esp-Ch] [ebp-34h]
  unsigned int v23; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  uint32_t *v27; // [esp+30h] [ebp+8h]
  uint32_t *v28; // [esp+34h] [ebp+Ch]
  uint32_t *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  v7 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( v7 != 0 )
  {
    result = 715827883 * (*(this + 3) - v7);
    v9 = (*(this + 3) - v7) / 12;
  }
  else
  {
    v9 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 12;
    else
      v11 = 0;
    if ( 357913941 - v11 < a3 )
      sub_52E630(this);
    if ( v7 != 0 )
      v12 = (*(this + 2) - v7) / 12;
    else
      v12 = 0;
    if ( v9 >= a3 + v12 )
    {
      v18 = (uint32_t *)*(this + 2);
      Blockb = v18;
      if ( ((char *)v18 - a2) / 12 >= a3 )
      {
        v27 = &v18[-3 * a3];
        *(this + 2) = (int)sub_59EE30(v27, v18, v18);
        sub_504450(a2, v27, Blockb);
        return sub_5043B0(a2, &a2[12 * a3], v25);
      }
      else
      {
        sub_59EE30(a2, v18, &a2[12 * a3]);
        v23 = a3 - (*(this + 2) - (int)a2) / 12;
        v22 = *(this + 2);
        v26 = 2;
        sub_5E51C0(v22, v23, v25);
        v20 = 12 * a3 + *(this + 2);
        *(this + 2) = v20;
        return sub_5043B0(a2, v20 - 12 * a3, v25);
      }
    }
    else
    {
      if ( 357913941 - (v9 >> 1) >= v9 )
        v13 = (v9 >> 1) + v9;
      else
        v13 = 0;
      if ( v7 != 0 )
        v14 = (*(this + 2) - v7) / 12;
      else
        v14 = 0;
      if ( v13 < a3 + v14 )
        v13 = a3 + sub_4DA030(this);
      v15 = 3 * v13;
      Blocka = operator new(12 * v13);
      v21 = (uint32_t *)*(this + 1);
      v26 = 0;
      v28 = sub_59EE30(v21, a2, Blocka);
      sub_623C10(v28, a3, v25);
      sub_59EE30(a2, (uint32_t *)*(this + 2), &v28[3 * a3]);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 12;
      v17 = v16 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[3 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x60B250 sub_60B250
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60B250(int *this, uint32_t *a2, int a3, int *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 12 != 0 )
    v6 = (a3 - v5) / 12;
  else
    v6 = 0;
  sub_60AFA0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 12 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x60B2C0 sub_60B2C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60B2C0(int *this, int *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 12;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 12 )
    return sub_60B250(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_623C10(v5, 1, Block);
  *(this + 2) = v5 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x60B340 CNMapObject__vmt2D0
// ------------------------------------------------------------
void /*thiscall*/ CNMapObject__vmt2D0(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_60A240((int)this + 1044, (int)v3);
}



// ------------------------------------------------------------
// 0x60B370 CNMapObject__vmt2D4
// ------------------------------------------------------------
void /*thiscall*/ CNMapObject__vmt2D4(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_474950((int)this + 1060, (int)v3);
}



// ------------------------------------------------------------
// 0x60B3A0 CNMapObject__vmt2D8
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNMapObject__vmt2D8(int *this, int a2, int a3, int a4)
{
  int Block[3]; // [esp+0h] [ebp-Ch] BYREF

  Block[1] = a3;
  Block[0] = a2;
  Block[2] = a4;
  return sub_60B2C0(this + 269, Block);
}



// ------------------------------------------------------------
// 0x60B3D0 CNMapObject__vmt2E4
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNMapObject__vmt2E4(int this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // edx
  int v10; // eax
  uint32_t *result; // eax
  uint32_t *v12; // [esp+10h] [ebp-10h]

  v2 = 0;
  v12 = (uint32_t *)(this + 1020);
  do
  {
    v3 = *(uint32_t *)(v2 + *(uint32_t *)(this + 712));
    if ( v3 != 0 && *(uint32_t *)(v3 + 4) != 0 )
    {
      if ( operator new(0x12Cu) != nullptr )
      {
        if ( *(uint32_t *)(this + 384) < 0x10u )
          v4 = this + 364;
        else
          v4 = *(uint32_t *)(this + 364);
        v5 = sub_41ACF0(v2 + *(uint32_t *)(this + 712));
        v6 = sub_4C3640(v4, v5, this);
      }
      else
      {
        v6 = 0;
      }
      *v12 = v6;
    }
    v2 += 4;
    ++v12;
  }
  while ( v2 < 12 );
  v7 = 12;
  v8 = this + 1032;
  do
  {
    v9 = *(uint32_t *)(this + 712);
    v10 = *(uint32_t *)(v7 + v9);
    if ( v10 != 0 && *(uint32_t *)(v10 + 4) != 0 )
      sub_41B0D0(v7 + v9);
    v7 += 4;
    v8 += 4;
  }
  while ( v7 < 24 );
  result = *(uint32_t **)(this + 348);
  *(uint32_t *)(this + 988) = *result;
  *(uint32_t *)(this + 992) = result[1];
  *(uint8_t *)(this + 996) = result[2] != 0;
  *(uint32_t *)(this + 972) = result[3];
  *(uint32_t *)(this + 976) = result[4];
  *(uint32_t *)(this + 980) = result[5];
  *(uint32_t *)(this + 680) = result[6];
  *(uint32_t *)(this + 684) = result[6];
  return result;
}



// ------------------------------------------------------------
// 0x60B520 sub_60B520
// ------------------------------------------------------------
int /*thiscall*/ sub_60B520(int *this)
{
  int v2; // ecx
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int result; // eax
  unsigned int v9; // edi
  int v10; // ecx
  int v11; // edx
  int v12; // edi
  int v13; // edx
  unsigned int v14; // ecx
  int *v15; // eax
  int v16; // [esp+Ch] [ebp-Ch] BYREF
  int v17; // [esp+10h] [ebp-8h]
  signed int v18; // [esp+14h] [ebp-4h]

  v2 = *(this + 251);
  if ( v2 != 0 && (*(this + 252) - v2) >> 2 != 0 )
  {
    v3 = 0;
    while ( 1 )
    {
      v4 = *(this + 251);
      if ( v4 == 0 || v3 >= (*(this + 252) - v4) >> 2 )
        break;
      if ( *(int **)(*(this + 251) + 4 * v3) != this
        && (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(*this + 488))(this, *(uint32_t *)(*(this + 251) + 4 * v3)) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 712))(this, *(uint32_t *)(*(this + 251) + 4 * v3++));
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 716))(this, *(uint32_t *)(*(this + 251) + 4 * v3));
        sub_60AAB0(this, *(uint32_t *)(*(this + 251) + 4 * v3++));
      }
    }
  }
  v5 = *(this + 29);
  v6 = *(uint32_t *)(v5 + 120);
  v7 = v5 + 116;
  if ( v6 != 0 )
    v17 = (*(uint32_t *)(v7 + 8) - v6) >> 2;
  else
    v17 = 0;
  result = v17;
  v9 = 0;
  v18 = 0;
  if ( v17 > 0 )
  {
    while ( 1 )
    {
      v10 = *(this + 29);
      v11 = *(uint32_t *)(v10 + 120);
      if ( v11 != 0 && v9 < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * v9);
      else
        v12 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 752))(this, v12) != 0
        && (int *)v12 != this
        && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 488))(this, v12) != 0 )
      {
        v16 = v12;
        if ( sub_60A9B0(this, v12) == 0 )
        {
          v13 = *(this + 251);
          if ( v13 != 0 )
            v14 = (*(this + 252) - v13) >> 2;
          else
            v14 = 0;
          if ( v13 != 0 && v14 < (*(this + 253) - v13) >> 2 )
          {
            v15 = (int *)*(this + 252);
            *v15 = v12;
            *(this + 252) = (int)(v15 + 1);
          }
          else
          {
            sub_428220((int)(this + 250), *(this + 252), 1u, &v16);
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 708))(this, v12);
        }
      }
      result = ++v18;
      if ( v18 >= v17 )
        break;
      v9 = v18;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60B6B0 CNMapObject__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNMapObject__vmt14C(int *this)
{
  int v2; // ecx
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 273) != 0 && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1 )
  {
    v2 = *(this + 34);
    *(this + 273) = 0;
    sub_4926A0(v2);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 34));
  }
  result = *((uint8_t *)this + 1096);
  if ( result != 0 )
    return sub_60B520(this);
  return result;
}



// ------------------------------------------------------------
// 0x60B710 sub_60B710
// ------------------------------------------------------------
void /*thiscall*/ sub_60B710(int *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // edi
  int *v5; // ebx
  bool v6; // zf
  int *v7; // edi
  int v8; // eax
  int v9; // ebx
  uint64_t v10; // rax
  int v11; // eax
  int v12; // eax
  int *v13; // ebx
  int v14; // eax
  unsigned int v15; // ecx
  int *v16; // eax
  void *Block; // [esp+4h] [ebp-1Ch]
  unsigned int v18; // [esp+8h] [ebp-18h] BYREF
  int *v19; // [esp+Ch] [ebp-14h]
  unsigned int v20; // [esp+10h] [ebp-10h]
  int v21; // [esp+1Ch] [ebp-4h]

  v2 = *(this + 262);
  if ( v2 != 0 && (*(this + 263) - v2) >> 3 != 0 )
  {
    v3 = (*(this + 263) - v2) >> 3;
    v4 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 492);
    v18 = v4 + v3 + (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    v5 = (int *)*(this + 262);
    v6 = v5 == (int *)*(this + 263);
    v19 = v5;
    v20 = v18 % 0x168;
    if ( !v6 )
    {
      do
      {
        Block = operator new(0x424u);
        v7 = nullptr;
        v21 = 0;
        if ( Block != nullptr )
          v7 = (int *)sub_4E2130(v5[1], &v18, v20);
        v8 = *this;
        v9 = *v7;
        v21 = -1;
        v10 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(v8 + 192))(this) * 0.69999999);
        v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, v10);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
        (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(v7, v12);
        v13 = v19;
        sub_45FE80(*(this + 29), (int)v7, 289, *v19, (int)v7, 0, 0);
        v14 = *(this + 262);
        if ( v14 != 0 )
          v15 = (*(this + 263) - v14) >> 3;
        else
          v15 = 0;
        v20 += 0x168 / v15;
        sub_4E7E40(v7);
        v16 = (int *)*(this + 263);
        v5 = v13 + 2;
        v19 = v5;
      }
      while ( v5 != v16 );
    }
    if ( *(this + 262) != 0 )
      j__free((void *)*(this + 262));
    *(this + 262) = 0;
    *(this + 263) = 0;
    *(this + 264) = 0;
  }
}



// ------------------------------------------------------------
// 0x60B8B0 CNMapObject__vmt2E8
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNMapObject__vmt2E8(int *this)
{
  sub_60B710(this);
  sub_60AB60(this);
  return sub_60ABE0((unsigned int *)this);
}



// ------------------------------------------------------------
// 0x60B8D0 sub_60B8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60B8D0(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 245) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60B8F0 sub_60B8F0
// ------------------------------------------------------------
int /*thiscall*/ sub_60B8F0(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 243;
  for ( i = 2; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60B920 CNFireMissile__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ sub_60B920(uint32_t *this)
{
  int **v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  bool v8; // zf
  char result; // al
  int v10; // eax
  int v11; // edx
  int v12; // [esp-28h] [ebp-4Ch]
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v15; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  sub_600890();
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        v10 = *(this + 71);
        if ( v10 == 30047 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            30048,
            *(this + 245),
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
        }
        else
        {
          v11 = *this;
          v12 = *(this + 245);
          if ( v10 == 30049 )
            (*(void (/*stdcall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
              30050,
              v12,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
          else
            (*(void (/*stdcall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
              40003,
              v12,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
        }
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  else
  {
    v2 = (int **)(this + 243);
    v17 = 2;
    do
    {
      v3 = **v2;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v4);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
      (*(void (/*thiscall*/ **)(int *, int))(v3 + 40))(*v2, v6);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v2 + 92))(*v2, v13);
      v7 = (void *)*(this + 29);
      v18 = 0;
      sub_4600B0(v7, 2, 0, (int)v13);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++v2;
      result = v17 - 1;
      v8 = v17 == 1;
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      --v17;
    }
    while ( !v8 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x60BA80 sub_60BA80
// ------------------------------------------------------------
int /*thiscall*/ sub_60BA80(float *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // edi
  float v9; // [esp+Ch] [ebp-2Ch]
  float v10; // [esp+10h] [ebp-28h]
  void *Block; // [esp+24h] [ebp-14h]

  v3 = operator new(0x12Cu);
  if ( v3 != nullptr )
    v4 = sub_428F30(v3, (int)"PassiveObject/Common/Particle/FireMissileParticle.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 243) = v4;
  v5 = operator new(0x12Cu);
  if ( v5 != nullptr )
    v6 = sub_428F30(v5, (int)"PassiveObject/Common/Particle/FireMissileParticleLight.ptl", (int)this);
  else
    v6 = nullptr;
  *((uint32_t *)this + 244) = v6;
  v7 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v10 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v9 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v9, v10, a2 - 1, v7 - 1);
  *((uint32_t *)this + 245) = a2;
  return sub_4015C0("SIZZLE_CREATE", 0xDu);
}



// ------------------------------------------------------------
// 0x60BB90 sub_60BB90
// ------------------------------------------------------------
void /*thiscall*/ sub_60BB90(uint32_t *this)
{
  *(this + 247) = 0;
  *(this + 248) = 100;
}



// ------------------------------------------------------------
// 0x60BBB0 CNFireExplosion__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNFireExplosion__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( *(this + 247) == a2 )
    *(this + 247) = 0;
}



// ------------------------------------------------------------
// 0x60BBE0 CNFireExplosion__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNFireExplosion__vmt1F0(uint32_t *this, int a2, int a3, int a4)
{
  if ( a2 == *(this + 247) )
    *(this + 112) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60BC00 CNFireExplosion__vmt1F8
// ------------------------------------------------------------
int /*thiscall*/ CNFireExplosion__vmt1F8(uint32_t *this, int a2, int a3, int a4)
{
  if ( a2 == *(this + 247) )
    *(this + 112) = 2;
  return 0;
}



// ------------------------------------------------------------
// 0x60BC20 sub_60BC20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60BC20(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *result; // eax

  v2 = (uint32_t *)*(this + 244);
  if ( v2 != (uint32_t *)*(this + 245) )
  {
    do
    {
      if ( *v2 != 0 )
        (**(void (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
      result = (uint32_t *)*(this + 245);
      ++v2;
    }
    while ( v2 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x60BC50 CNFireExplosion__vmt2BC
// ------------------------------------------------------------
void /*thiscall*/ CNFireExplosion__vmt2BC(void *this, float *a2, int Size)
{
  int v3; // esi
  int v5; // eax
  int v6; // eax
  uint16_t v7; // di
  uint32_t *v8; // eax
  int v9; // ecx
  uint32_t *v10; // edi
  int v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edx
  uint32_t *v17; // eax
  int v18; // eax
  uint8_t v19; // cl
  int v20; // edx
  uint64_t v21; // rax
  float v22; // [esp+0h] [ebp-10h]
  int i; // [esp+18h] [ebp+8h]
  int v24; // [esp+18h] [ebp+8h]

  v3 = Size;
  CNRDPassiveObject__vmt2BC((int)a2, Size);
  if ( Size == 30 )
  {
    v5 = sub_45EBE0(*((uint32_t **)this + 29), *(uint16_t *)a2, *((uint16_t *)a2 + 1));
    v6 = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    *((uint32_t *)this + 247) = v6;
    if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
      sub_4E5F70((int)this, (int)this, *((uint32_t *)this + 247), a2 + 1, 1, 0);
  }
  else
  {
    dword_78FE30 = (int)a2;
    dword_78FE34 = 0;
    if ( Size > 0 )
    {
      v7 = *(uint16_t *)a2;
      dword_78FE34 = 2;
      v8 = *((uint32_t **)this + 245);
      v9 = v7;
      v10 = *((uint32_t **)this + 244);
      *((uint32_t *)this + 248) = v9;
      if ( v10 != v8 )
      {
        do
        {
          v11 = 0;
          do
          {
            for ( i = 2; i != 0; --i )
            {
              v12 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v10 + 28))(*v10);
              *(uint32_t *)(v12 + v11 + 15) *= *((uint32_t *)this + 248);
              v13 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v10 + 28))(*v10);
              *(int *)(v13 + v11 + 15) /= 100;
              v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v10 + 28))(*v10);
              *(uint32_t *)(v14 + v11 + 39) *= *((uint32_t *)this + 248);
              v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v10 + 28))(*v10);
              *(int *)(v15 + v11 + 39) /= 100;
              v11 += 4;
            }
          }
          while ( v11 < 24 );
          ++v10;
        }
        while ( v10 != *((uint32_t **)this + 245) );
        v3 = Size;
      }
      v22 = (double)*((int *)this + 248) * 0.0099999998;
      sub_4922F0(v22);
      if ( dword_78FE34 < v3 )
      {
        v16 = *(int16_t *)(dword_78FE34 + dword_78FE30);
        dword_78FE34 += 2;
        v17 = *(uint32_t **)this;
        *((uint32_t *)this + 183) = v16;
        ((void (/*thiscall*/ *)(void *, int))v17[86])(this, (int)this + 724);
        v18 = dword_78FE34;
        if ( dword_78FE34 < v3 )
        {
          v19 = *(uint8_t *)(dword_78FE34 + dword_78FE30);
          ++dword_78FE34;
          v20 = *(uint32_t *)(v18 + 1 + dword_78FE30);
          dword_78FE34 = v18 + 5;
          v24 = *(int *)(v18 + 5 + dword_78FE30);
          dword_78FE34 = v18 + 9;
          if ( v19 != 17 )
          {
            *((uint32_t *)this + 187) = v19;
            *((uint32_t *)this + 190) = v20;
            v21 = (uint64_t)*(float *)&v24;
            HIDWORD(v21) = *(uint32_t *)this;
            *((uint32_t *)this + 193) = v21;
            (*(void (/*thiscall*/ **)(void *, int))(HIDWORD(v21) + 344))(this, (int)this + 724);
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x60BE80 CNFireExplosion__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNFireExplosion__vmt14C(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // eax
  uint32_t *v8; // ebx
  float v9; // [esp+10h] [ebp-48h]
  uint8_t v10[4]; // [esp+20h] [ebp-38h] BYREF
  void *Block; // [esp+24h] [ebp-34h]
  int v12; // [esp+28h] [ebp-30h]
  int v13; // [esp+2Ch] [ebp-2Ch]
  uint8_t v14[4]; // [esp+30h] [ebp-28h] BYREF
  void *v15; // [esp+34h] [ebp-24h]
  uint32_t *v16; // [esp+38h] [ebp-20h]
  int v17; // [esp+3Ch] [ebp-1Ch]
  int v18; // [esp+40h] [ebp-18h]
  int v19; // [esp+44h] [ebp-14h]
  int i; // [esp+48h] [ebp-10h]
  int v21; // [esp+54h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v15 = nullptr;
  v16 = nullptr;
  v17 = 0;
  v2 = *this;
  v21 = 0;
  v3 = (*(int (/*thiscall*/ **)(int *))(v2 + 120))(this);
  v4 = *this;
  v18 = v3;
  v19 = (*(int (/*thiscall*/ **)(int *))(v4 + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v6 = (uint32_t *)*(this + 244);
  for ( i = v5; v6 != (uint32_t *)*(this + 245); ++v6 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*v6 + 40))(*v6, v18, v19, i);
    v7 = (*(int (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*v6 + 92))(*v6, v10);
    LOBYTE(v21) = 1;
    sub_4E77D0((int)v14, v7);
    LOBYTE(v21) = 0;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v8 = v15;
    if ( v15 != v16 )
    {
      do
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 200))(*v8) != 0 )
        {
          v9 = (double)*(this + 248) * 0.0099999998;
          (*(void (**)(void))(*(uint32_t *)*v8 + 200))();
          sub_4922F0(v9);
        }
        ++v8;
      }
      while ( v8 != v16 );
    }
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v14);
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( *(this + 50) == 1 )
    (*(void (/*thiscall*/ **)(int *))(*this + 232))(this);
  if ( v15 != nullptr )
    j__free(v15);
}



// ------------------------------------------------------------
// 0x60BFF0 sub_60BFF0
// ------------------------------------------------------------
int /*thiscall*/ sub_60BFF0(int this, int a2)
{
  uint32_t *v2; // esi
  int v3; // eax
  int result; // eax
  uint32_t *v5; // edi
  void *v6; // eax
  uint32_t *v7; // esi
  int v8; // eax
  int v9; // edx
  unsigned int v10; // esi
  uint32_t *v11; // ecx
  uint32_t *v12; // [esp-10h] [ebp-24h]
  void *Block; // [esp+0h] [ebp-14h] BYREF
  uint32_t *v14; // [esp+4h] [ebp-10h]
  int v15; // [esp+10h] [ebp-4h]
  int v16; // [esp+1Ch] [ebp+8h]

  v2 = (uint32_t *)this;
  v3 = *(uint32_t *)(this + 284);
  *(float *)(this + 724) = (float)a2;
  v14 = (uint32_t *)this;
  if ( v3 == 22210 )
    sub_4015C0("NAPALM_EXPLOSION", 0x10u);
  else
    sub_4015C0("FIRE_EXPLOSION_CREATE", 0x15u);
  result = v2[178];
  v16 = result;
  if ( result != v2[179] )
  {
    v5 = v2 + 243;
    while ( 1 )
    {
      Block = operator new(0x12Cu);
      v6 = nullptr;
      v15 = 0;
      if ( Block != nullptr )
      {
        if ( v2[96] < 0x10u )
          v7 = v2 + 91;
        else
          v7 = (uint32_t *)v2[91];
        v12 = v14;
        v8 = sub_41ACF0(v16);
        v6 = (void *)sub_4C3640(v7, v8, v12);
      }
      v9 = v5[1];
      v15 = -1;
      Block = v6;
      v10 = v9 != 0 ? (v5[2] - v9) >> 2 : 0;
      if ( v9 != 0 && v10 < (v5[3] - v9) >> 2 )
      {
        v11 = (uint32_t *)v5[2];
        *v11 = v6;
        v5[2] = v11 + 1;
      }
      else
      {
        sub_5CC5A0((void *)v5[2], 1, (int)&Block);
      }
      result = v16 + 4;
      v16 += 4;
      if ( v16 == v14[179] )
        break;
      v2 = v14;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60C130 sub_60C130
// ------------------------------------------------------------
int /*thiscall*/ sub_60C130(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C140 CNIceMissile__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNIceMissile__vmt14C(int **this)
{
  int **v2; // ebx
  int v3; // edi
  int *v4; // edx
  int v5; // eax
  int v6; // eax
  int **v7; // ebx
  void *v8; // ecx
  bool v9; // zf
  int result; // eax
  uint8_t v11[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]
  int v14; // [esp+18h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-18h]
  int v16; // [esp+20h] [ebp-14h]
  int **v17; // [esp+24h] [ebp-10h]
  int v18; // [esp+30h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v2 = this + 243;
  v17 = this + 243;
  v16 = 2;
  do
  {
    if ( ((int (/*thiscall*/ *)(int **))(*this)[38])(this) != 0 )
      v3 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this) - 15;
    else
      v3 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this) + 15;
    v4 = *this;
    v15 = **v2;
    v5 = ((int (/*thiscall*/ *)(int **))v4[32])(this);
    v6 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v5);
    v7 = v17;
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 40))(*v17, v3, v6);
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v7 + 92))(*v7, v11);
    v8 = *(this + 29);
    v18 = 0;
    sub_4600B0(v8, 2, 0, (int)v11);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    v2 = v7 + 1;
    result = v16 - 1;
    v9 = v16 == 1;
    Block = nullptr;
    v13 = 0;
    v14 = 0;
    v17 = v2;
    --v16;
  }
  while ( !v9 );
  return result;
}



// ------------------------------------------------------------
// 0x60C230 sub_60C230
// ------------------------------------------------------------
int /*thiscall*/ sub_60C230(float *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // edx
  int v8; // edi
  double v9; // st7
  uint32_t *v10; // eax
  double v11; // st7
  uint32_t *v12; // eax
  float v14; // [esp+34h] [ebp-30h]
  float v15; // [esp+34h] [ebp-30h]
  float v16; // [esp+34h] [ebp-30h]
  float v17; // [esp+38h] [ebp-2Ch]
  float v18; // [esp+38h] [ebp-2Ch]
  float v19; // [esp+38h] [ebp-2Ch]
  void *Block; // [esp+50h] [ebp-14h]
  void *Blocka; // [esp+50h] [ebp-14h]
  void *Blockb; // [esp+50h] [ebp-14h]

  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  v3 = operator new(0x12Cu);
  if ( v3 != nullptr )
    v4 = sub_428F30(v3, (int)"PassiveObject/Common/Particle/IceMissileParticleLight.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 243) = v4;
  v5 = operator new(0x12Cu);
  if ( v5 != nullptr )
    v6 = sub_428F30(v5, (int)"PassiveObject/Common/Particle/IceMissileParticleTail.ptl", (int)this);
  else
    v6 = nullptr;
  v7 = *(uint32_t **)this;
  *((uint32_t *)this + 244) = v6;
  v8 = ((int (/*thiscall*/ *)(float *, uint32_t))v7[96])(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  --v8;
  v17 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v14 = (float)(int)Block;
  v9 = sub_4049C0(v14, v17, a2 - 1, v8);
  v10 = *(uint32_t **)this;
  *(this + 181) = v9;
  Blocka = (void *)((int (/*thiscall*/ *)(float *, int))v10[96])(this, 3);
  v18 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
  v15 = (float)(int)Blocka;
  v11 = sub_4049C0(v15, v18, a2 - 1, v8);
  v12 = *(uint32_t **)this;
  *(this + 190) = v11;
  Blockb = (void *)((int (/*thiscall*/ *)(float *, int))v12[96])(this, 5);
  v19 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 6);
  v16 = (float)(int)Blockb;
  *((uint32_t *)this + 193) = (uint64_t)sub_4049C0(v16, v19, a2 - 1, v8);
  return sub_4015C0("ICICLE_CREATE", 0xDu);
}



// ------------------------------------------------------------
// 0x60C3D0 sub_60C3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60C3D0(int this)
{
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 977) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C3F0 CNThunderBolt__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNThunderBolt__vmt2A8(int *this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  int v11; // ebx
  char *v12; // edi
  int v13; // eax

  CNRDPassiveObject__vmt2A8(this, a2);
  LOBYTE(v3) = *((uint8_t *)this + 977);
  if ( (uint8_t)v3 == 0 )
  {
    v3 = *(this + 243);
    if ( v3 == 1 )
    {
      v4 = (char *)sub_47E720(1, 0xBu);
      v5 = *(this + 176);
      v6 = v4;
      *((float *)this + 190) = (double)sub_47EF20(v4, 1u, v5, -1, -1, 11) * 0.1;
      v7 = sub_47EF20(v6, 2u, v5, -1, -1, 11);
      v8 = *this;
      *(this + 193) = v7;
      v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
      v3 = sub_47EFD0(v6, 0.0, v5, v9, v9, 0);
      *((uint8_t *)this + 977) = 1;
      *((float *)this + 181) = (float)v3;
    }
    else
    {
      if ( v3 == 3 )
      {
        v10 = (char *)sub_47E720(3, 0x36u);
        v11 = *(this + 176);
        v12 = v10;
        *((float *)this + 190) = (double)sub_47EF20(v10, 2u, v11, -1, -1, 11) * 0.1;
        *(this + 193) = sub_47EF20(v12, 3u, v11, -1, -1, 11);
        v13 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        v3 = sub_47EFD0(v12, COERCE_FLOAT(1), v11, v13, v13, 0);
        *((float *)this + 181) = (float)v3;
      }
      *((uint8_t *)this + 977) = 1;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x60C520 CNThunderBolt__vmt2BC
// ------------------------------------------------------------
void /*userpurge*/ CNThunderBolt__vmt2BC(uint32_t **a1@<ecx>, int a2@<ebx>, float *a3, size_t Size)
{
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt2BC((int)a3, Size);
  if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*a1)[77])(a1) != 0 )
  {
    v5 = sub_45EBE0(a1[29], *(uint16_t *)a3, *((uint16_t *)a3 + 1));
    v6 = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
    if ( v6 != 0 )
      sub_4E5F70(a2, (int)a1, v6, a3 + 1, 1, 1);
  }
}



// ------------------------------------------------------------
// 0x60C590 sub_60C590
// ------------------------------------------------------------
int /*thiscall*/ sub_60C590(float *this, int a2, int a3)
{
  int v4; // edi
  int v5; // ebx
  double v6; // st7
  int v7; // edx
  double v8; // st7
  float v9; // edx
  float v11; // [esp+1Ch] [ebp-20h]
  float v12; // [esp+1Ch] [ebp-20h]
  float v13; // [esp+1Ch] [ebp-20h]
  float v14; // [esp+20h] [ebp-1Ch]
  float v15; // [esp+20h] [ebp-1Ch]
  float v16; // [esp+20h] [ebp-1Ch]
  int v17; // [esp+38h] [ebp-4h]
  int v18; // [esp+38h] [ebp-4h]
  int v19; // [esp+44h] [ebp+8h]

  *((uint32_t *)this + 243) = a3;
  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
    v17 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
    --v4;
    v5 = a2 - 1;
    v14 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
    v11 = (float)v17;
    v6 = sub_4049C0(v11, v14, a2 - 1, v4);
    v7 = *(uint32_t *)this;
    *(this + 181) = v6;
    v19 = (*(int (/*thiscall*/ **)(float *, int))(v7 + 384))(this, 3);
    v15 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
    v12 = (float)v19;
    v8 = sub_4049C0(v12, v15, v5, v4);
    v9 = *this;
    *(this + 190) = v8;
    v18 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 5);
    v16 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 6);
    v13 = (float)v18;
    *((uint32_t *)this + 193) = (uint64_t)sub_4049C0(v13, v16, v5, v4);
  }
  *((uint8_t *)this + 976) = 0;
  return sub_4015C0("THUNDER_STRIKE", 0xEu);
}



// ------------------------------------------------------------
// 0x60C6A0 CNThunderBolt__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNThunderBolt__vmt14C(int *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  char *v8; // edi
  int v9; // eax
  int v10; // eax
  char *v11; // edi
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  void *v17; // eax
  bool v18; // zf
  int result; // eax
  char v20[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v22; // [esp+10h] [ebp-1Ch]
  int v23; // [esp+14h] [ebp-18h]
  int v24; // [esp+18h] [ebp-14h]
  char *v25; // [esp+1Ch] [ebp-10h]
  int v26; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)(*(this + 30) + 148) >= 1 && *((uint8_t *)this + 976) == 0 )
  {
    v2 = dword_8F82B0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B0 + 12))(dword_8F82B0, 0);
    v3 = *(uint32_t *)v2;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(int, int))(v3 + 40))(v2, v6);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v2 + 92))(v2, v20);
    v7 = (void *)*(this + 29);
    v26 = 0;
    sub_4600B0(v7, 2, 0, (int)v20);
    sub_424120(*(uint32_t **)(*(this + 29) + 132), 2, 150);
    if ( *(this + 243) == 2 )
    {
      v8 = (char *)sub_44B6C0(284);
      v25 = v8;
      LOBYTE(v26) = 1;
      if ( v8 != nullptr )
      {
        v9 = sub_42FCB0(228);
        v24 = v9;
        LOBYTE(v26) = 2;
        if ( v9 != 0 )
          v10 = sub_431860(v9, "PassiveObject/Common/Animation/EarthQuake.ani", 1);
        else
          v10 = 0;
        LOBYTE(v26) = 1;
        v11 = sub_44E1F0(v8, v10, 1);
      }
      else
      {
        v11 = nullptr;
      }
      v12 = *(uint32_t *)v11;
      LOBYTE(v26) = 0;
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 72))(v11, 2);
      sub_45FE80(*(this + 29), (int)v11, 2, 0, (int)v11, (int)this, 0);
      v13 = *(uint32_t *)v11;
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v14);
      v16 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v15 - 1);
      (*(void (/*thiscall*/ **)(char *, int))(v13 + 112))(v11, v16);
    }
    v17 = Block;
    v18 = Block == nullptr;
    *((uint8_t *)this + 976) = 1;
    v26 = -1;
    if ( !v18 )
      j__free(v17);
    Block = nullptr;
    v22 = 0;
    v23 = 0;
  }
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 && *((uint8_t *)this + 264) == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60C850 sub_60C850
// ------------------------------------------------------------
int /*thiscall*/ sub_60C850(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 1;
  *(uint8_t *)(this + 981) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60C870 sub_60C870
// ------------------------------------------------------------
int /*thiscall*/ sub_60C870(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 243);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 243) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60C890 CNParticleFactory__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNParticleFactory__vmtC(int this)
{
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 972) + 12))(
             *(uint32_t *)(this + 972),
             *(uint32_t *)(this + 976));
  *(uint8_t *)(this + 981) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60C8C0 CNParticleFactory__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNParticleFactory__vmt14C(int **this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  int *v5; // ecx
  int v6; // edi
  int v7; // eax
  float *v8; // eax
  float *v9; // ecx
  bool v10; // zf
  int v11; // ebx
  int v12; // eax
  int v13; // edx
  int *v14; // ebx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // edi
  int v22; // eax
  void *v23; // ecx
  uint8_t v24[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v26; // [esp+1Ch] [ebp-14h]
  int v27; // [esp+20h] [ebp-10h]
  int v28; // [esp+2Ch] [ebp-4h]

  if ( *((uint8_t *)this + 981) == 0 )
  {
    v2 = (int)*(this + 87);
    if ( v2 != 0 && (unsigned int)(((int)*(this + 88) - v2) >> 2) > 2 && *(uint32_t *)(v2 + 8) == 1 )
    {
      v3 = (int)*(this + 29);
      if ( v3 != 0 )
      {
        v4 = sub_425050(*(uint32_t **)(*(uint32_t *)(v3 + 132) + 44));
        v5 = *(this + 243);
        v6 = v4;
        v7 = *v5;
        v27 = v6;
        v8 = (float *)(*(int (/*thiscall*/ **)(int *))(v7 + 36))(v5);
        v9 = v8;
        v10 = *(uint32_t *)v8 == -1082130432;
        v11 = *((uint32_t *)v8 + 3);
        v26 = v11;
        if ( !v10 )
          *v8 = (double)v27 * *v8 / (double)v26;
        v12 = v6 * *((uint32_t *)v8 + 1) / v11;
        v13 = v6 * *((uint32_t *)v9 + 1) % v11;
        *((uint32_t *)v9 + 3) = v6;
        *((uint32_t *)v9 + 1) = v12;
        v14 = *this;
        v15 = ((int (/*fastcall*/ *)(int **, int))(*this)[32])(this, v13);
        v16 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v15);
        ((void (/*thiscall*/ *)(int **, int, int))v14[28])(this, v6 / 2, v16);
      }
    }
    *((uint8_t *)this + 981) = 1;
  }
  CNRDPassiveObject__vmt14C((int)this);
  v17 = **(this + 243);
  v18 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
  v19 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v18);
  v20 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v19);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v17 + 40))(*(this + 243), v20);
  v21 = (int)*(this + 243);
  v22 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 28))(v21) + 84) = v22 == 0;
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 243) + 92))(*(this + 243), v24);
  v23 = *(this + 29);
  v28 = 0;
  sub_4600B0(v23, 2, 0, (int)v24);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(this + 243) + 68))(*(this + 243)) != 0
    && *((uint8_t *)this + 980) != 0 )
  {
    ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[21])(this, 0);
  }
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x60CA50 sub_60CA50
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_60CA50(int this, int a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // ecx
  unsigned int result; // eax
  int v8; // ecx
  void *Block; // [esp+8h] [ebp-10h]

  Block = operator new(0x12Cu);
  v3 = 0;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v4 = this + 364;
    else
      v4 = *(uint32_t *)(this + 364);
    v5 = sub_41ACF0(*(uint32_t *)(this + 712));
    v3 = sub_4C3640(v4, v5, this);
  }
  *(uint32_t *)(this + 972) = v3;
  v6 = *(uint32_t **)(this + 348);
  if ( v6 != nullptr && (*(uint32_t *)(this + 352) - (int)v6) >> 2 != 0 )
    *(uint32_t *)(this + 976) = *v6;
  result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v3 + 12))(v3, *(uint32_t *)(this + 976));
  v8 = *(uint32_t *)(this + 348);
  if ( v8 != 0 )
  {
    result = (*(uint32_t *)(this + 352) - v8) >> 2;
    if ( result > 1 )
    {
      result = *(uint32_t *)(this + 348) + 4;
      if ( *(uint32_t *)(v8 + 4) == 0 )
        *(uint8_t *)(this + 980) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60CB40 sub_60CB40
// ------------------------------------------------------------
int /*thiscall*/ sub_60CB40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60CB70 sub_60CB70
// ------------------------------------------------------------
int /*thiscall*/ sub_60CB70(uint32_t *this, int a2)
{
  *(this + 247) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x60CB80 CNBlast__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNBlast__vmt10(int this)
{
  int result; // eax
  int v3; // edi
  int v4; // ebx
  uint32_t *v5; // esi
  int i; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint32_t *)(this + 692);
  if ( result != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
    v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 692) + 124))(*(uint32_t *)(this + 692));
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 112))(this, v3, v4, 0);
    v5 = (uint32_t *)(this + 972);
    for ( i = 3; i != 0; --i )
    {
      if ( *v5 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*v5 + 112))(*v5, v3, v4, 0);
      ++v5;
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60CBF0 CNBlast__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNBlast__vmt12C(uint32_t *this, int a2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  result = 0;
  if ( a2 == *(this + 243) )
    *(this + 243) = 0;
  if ( a2 == *(this + 244) )
    *(this + 244) = 0;
  if ( a2 == *(this + 245) )
    *(this + 245) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60CC40 CNBlast__vmt14C
// ------------------------------------------------------------
int /*usercall*/ sub_60CC40@<eax>(int a1@<ecx>, int a2@<ebx>)
{
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  char *v9; // ebx
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // ebx
  int v13; // eax
  char *v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp-8h] [ebp-30h]
  char *v24; // [esp+8h] [ebp-20h]
  int v25; // [esp+Ch] [ebp-1Ch]
  int v26; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  int v29; // [esp+14h] [ebp-14h]
  int v30; // [esp+18h] [ebp-10h]

  sub_600890();
  v3 = *(uint32_t *)(a1 + 692);
  if ( *(uint8_t *)(a1 + 984) == 0 )
  {
    v4 = 0;
    if ( v3 != 0 )
    {
      v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, a2);
      v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3);
      if ( *(uint32_t *)(a1 + 988) == 0 )
      {
        v5 = sub_42FCB0(228);
        if ( v5 != 0 )
          v4 = sub_431860(v5, "Common/CommonEffect/Animation/LevelUp.ani", 1);
        if ( sub_44B6C0(284) != 0 )
          v6 = sub_44E1F0(v4, 1);
        else
          v6 = 0;
        v7 = *(uint32_t *)(a1 + 116);
        *(uint32_t *)(a1 + 980) = v6;
        sub_45FE80(v7, v3, 2, 0, v6, v3, 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(a1 + 980) + 112))(
          *(uint32_t *)(a1 + 980),
          v28,
          v29,
          v30);
      }
      v8 = sub_42FCB0(228);
      if ( v8 != 0 )
        v25 = sub_431860(v8, "Common/CommonEffect/Animation/Blast1.ani", 1);
      else
        v25 = 0;
      v9 = (char *)sub_44B6C0(284);
      if ( v9 != nullptr )
      {
        sub_44E0D0(v9, v25, 1);
        *(uint32_t *)v9 = &CNRDPooledObject::`vftable';
        v10 = (int)v9;
      }
      else
      {
        v10 = 0;
      }
      v11 = *(uint32_t *)(a1 + 116);
      v12 = (uint32_t *)(a1 + 972);
      *(uint32_t *)(a1 + 972) = v10;
      sub_45FE80(v11, v3, 2, 0, v10, v3, 1);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*v12 + 112))(*v12, v28, v29, v30);
      v13 = sub_42FCB0(228);
      if ( v13 != 0 )
        v26 = sub_431860(v13, "Common/CommonEffect/Animation/Blast2.ani", 1);
      else
        v26 = 0;
      v14 = (char *)sub_44B6C0(284);
      v24 = v14;
      if ( v14 != nullptr )
      {
        sub_44E0D0(v14, v26, 1);
        v15 = (int)v24;
        *(uint32_t *)v24 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = 0;
      }
      v16 = *(uint32_t *)(a1 + 116);
      *(uint32_t *)(a1 + 976) = v15;
      sub_45FE80(v16, v3, 2, 0, v15, v3, 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 976) + 112))(*(uint32_t *)(a1 + 976), v28, v29);
      for ( i = 2; i != 0; --i )
      {
        v17 = *(uint32_t *)(a1 + 120);
        v18 = *(uint32_t *)(v17 + 212);
        if ( v18 != 0 )
          v19 = sub_4910A0(v18);
        else
          v19 = *(uint32_t *)(v17 + 32);
        v22 = v19;
        v20 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v12 + 200))(*v12);
        sub_493A60(v20, v22);
        ++v12;
      }
      sub_49C620(0, 1, 0);
      sub_49C5F0(0, 0, 0, 2000);
      switch ( *(uint32_t *)(a1 + 988) )
      {
        case 0:
        case 1:
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "LEVEL_UP",
            -1,
            0,
            0);
          break;
        case 2:
          goto LABEL_31;
        case 3:
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 596))(a1, 0);
LABEL_31:
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "SHOUTING",
            -1,
            0,
            0);
          break;
        default:
          break;
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
    }
    *(uint8_t *)(a1 + 984) = 1;
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = *(uint32_t *)(a1 + 972);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x60CF90 CNEarthQuake__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNEarthQuake__vmt14C(uint32_t *this)
{
  int v2; // edx
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)(*(this + 30) + 148) >= 1 && *((uint8_t *)this + 972) == 0 )
  {
    sub_424120(
      *(uint32_t **)(*(this + 29) + 132),
      (uint64_t)((double)(int)*(this + 247) * 7.5),
      750 * *(this + 247));
    v2 = *this;
    *((uint8_t *)this + 972) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v2 + 212))(this, "TAU_EQUAKE", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TAU_STONEDROP", -1, 0, 0);
  }
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D040 sub_60D040
// ------------------------------------------------------------
int /*thiscall*/ sub_60D040(uint8_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx

  *(this + 972) = 0;
  v3 = sub_42FCB0(228);
  if ( v3 != 0 )
    v4 = sub_431860(v3, "PassiveObject/Common/Animation/EarthQuakeRing.ani", 1);
  else
    v4 = 0;
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 244) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 204))(this, -1, v4, 0, 0, 0, 0);
  sub_4015C0("TAU_CRASH", 9u);
  *((uint32_t *)this + 247) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x60D0E0 sub_60D0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D0E0(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 244);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 244));
    result = sub_657740(v2, 228);
  }
  *(this + 244) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x60D120 sub_60D120
// ------------------------------------------------------------
int /*thiscall*/ sub_60D120(int this)
{
  *(uint8_t *)(this + 976) = 0;
  *(uint8_t *)(this + 264) = 0;
  *(uint32_t *)(this + 984) = 1;
  *(uint32_t *)(this + 972) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60D140 CNDangerousGas__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNDangerousGas__vmt12C(uint32_t *this, int a2)
{
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x60D170 CNDangerousGas__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDangerousGas__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  uint32_t *v5; // eax

  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
  if ( v5[6] != 17 )
    v5[12] = *(this + 246);
  if ( v5[7] != 17 )
    v5[13] = *(this + 246);
  if ( v5[8] != 17 )
    v5[14] = *(this + 246);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x60D1D0 sub_60D1D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D1D0(float *this, int a2, int a3)
{
  int v4; // eax
  int v5; // edi
  float v7; // [esp+Ch] [ebp-20h]
  float v8; // [esp+10h] [ebp-1Ch]
  int v9; // [esp+24h] [ebp-8h]

  v4 = *(uint32_t *)this;
  *((uint8_t *)this + 976) = 0;
  v5 = (*(int (/*stdcall*/ **)(uint32_t))(v4 + 384))(0);
  v9 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v8 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)v9;
  *(this + 181) = sub_4049C0(v7, v8, a2 - 1, v5 - 1);
  *((uint32_t *)this + 246) = a2;
  *((uint32_t *)this + 245) = a3;
  return sub_4015C0("THUNDERBOLT_CREATE", 0x12u);
}



// ------------------------------------------------------------
// 0x60D260 CNDangerousGas__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNDangerousGas__vmt14C(uint32_t *this)
{
  int v2; // eax
  const char *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  double v10; // st7
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  void *v15; // ecx
  uint8_t v16[4]; // [esp+4h] [ebp-228h] BYREF
  void *Block; // [esp+8h] [ebp-224h]
  int v18; // [esp+14h] [ebp-218h]
  void *v19; // [esp+18h] [ebp-214h]
  char Buffer[512]; // [esp+1Ch] [ebp-210h] BYREF
  int v21; // [esp+21Ch] [ebp-10h]
  int v22; // [esp+228h] [ebp-4h]

  v21 = dword_796E50;
  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 976) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);
    v3 = (const char *)sub_41ACF0(*(uint32_t *)(v2 + 32));
    sprintf(Buffer, "PassiveObject/Common/%s", v3);
    v4 = operator new(0x12Cu);
    v19 = v4;
    v22 = 0;
    if ( v4 != nullptr )
      v5 = sub_428F30(v4, (int)Buffer, 0);
    else
      v5 = nullptr;
    v22 = -1;
    *(this + 243) = v5;
    if ( v5 != nullptr )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v7 = *this;
      if ( v6 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 684))(this);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 192))(v8);
        v9 = *this;
        *(float *)&v19 = (double)v18 * 0.5;
        v18 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(this);
        v10 = (double)v18 + *(float *)&v19;
      }
      else
      {
        *(float *)&v19 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this));
        v10 = (double)(int)v19;
      }
      v11 = *(uint32_t *)*(this + 243);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)v10);
      v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v12);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v11 + 40))(*(this + 243), v13);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);
    }
    v14 = *this;
    *((uint8_t *)this + 976) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 216))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
      this,
      "CLOUD_KILL_LOOP",
      0,
      0,
      0);
  }
  if ( *(uint8_t *)(*(this + 30) + 170) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 68))(*(this + 243)) == 0
    || *((uint8_t *)this + 264) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v16);
    v15 = (void *)*(this + 29);
    v22 = 1;
    sub_4600B0(v15, 2, 0, (int)v16);
    if ( Block != nullptr )
      j__free(Block);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x60D480 CNIceNiddleGroup__vmt288
// ------------------------------------------------------------
int /*stdcall*/ CNIceNiddleGroup__vmt288(uint32_t *a1, int a2)
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 20) == 1 )
  {
    *a1 = 0;
    return 2;
  }
  else
  {
    *a1 = 100;
    return 0;
  }
}



// ------------------------------------------------------------
// 0x60D4C0 CNIceNiddleGroup__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNIceNiddleGroup__vmt14C(uint32_t *this)
{
  int i; // edi
  int v3; // eax
  unsigned int result; // eax
  int v5; // [esp-18h] [ebp-20h]
  int v6; // [esp-14h] [ebp-1Ch]
  int v7; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    for ( i = 0; i < 4; ++i )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      sub_4E4A50(*(this + 173), *(this + 71) + i + 1, *(this + 249), v3, v5, v6, v7, 0, 0, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  if ( *(uint8_t *)(*(this + 30) + 170) == 0 || *((uint8_t *)this + 264) != 0 )
  {
    result = sub_699000((int)(this + 9));
    if ( *(this + 247) + 2000 < result )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      result = sub_699000((int)(this + 9));
      *(this + 247) = result;
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D5A0 CNIceNiddleGroup__vmt2B4
// ------------------------------------------------------------
void /*thiscall*/ CNIceNiddleGroup__vmt2B4(int *this, int a2, void *a3, int a4, int a5, int a6)
{
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  void *v9; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-4h]

  if ( *(this + 170) <= 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( (int)a3 > 0 )
  {
    if ( *(this + 248) == 0 )
    {
      v7 = operator new(0x12Cu);
      v12 = 0;
      if ( v7 != nullptr )
        v8 = sub_428F30(v7, (int)"Common/HitEffect/Particle/WaterHitParticleLIght.ptl", (int)this);
      else
        v8 = nullptr;
      v12 = -1;
      *(this + 248) = (int)v8;
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 248) + 12))(*(this + 248), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 248) + 40))(*(this + 248), a4, a5, a6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 248) + 92))(*(this + 248), v10);
    v9 = (void *)*(this + 29);
    v12 = 1;
    sub_4600B0(v9, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x60D6A0 sub_60D6A0
// ------------------------------------------------------------
void /*thiscall*/ sub_60D6A0(uint8_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edi
  float v8; // [esp+24h] [ebp-2Ch]
  float v9; // [esp+28h] [ebp-28h]
  int v10; // [esp+3Ch] [ebp-14h]

  *(this + 972) = 0;
  *((uint32_t *)this + 248) = 0;
  v3 = sub_42FCB0(228);
  if ( v3 != 0 )
    v4 = sub_431860(v3, "PassiveObject/Common/Animation/IceNiddleGlow.ani", 1);
  else
    v4 = 0;
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 244) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 204))(this, 1, v4, 0, 0, 0, 0);
  sub_4015C0("ICE_NIDDLE_HIT", 0xEu);
  v6 = **((uint32_t **)this + 87);
  *((uint32_t *)this + 170) = v6;
  *((uint32_t *)this + 171) = v6;
  *((uint32_t *)this + 247) = sub_699000((int)(this + 36));
  v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
  v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);
  v9 = (float)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 3);
  v8 = (float)v10;
  *((float *)this + 181) = sub_4049C0(v8, v9, a2 - 1, v7 - 1);
  *((uint32_t *)this + 249) = a2;
}



// ------------------------------------------------------------
// 0x60D7C0 sub_60D7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_60D7C0(int this)
{
  int v2; // edi
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = *(uint32_t *)(this + 976);
  if ( v2 != 0 )
  {
    sub_42AF90(*(void ***)(this + 976));
    result = sub_657740(v2, 228);
  }
  *(uint32_t *)(this + 976) = 0;
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 992);
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 992) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60D810 sub_60D810
// ------------------------------------------------------------
int /*thiscall*/ sub_60D810(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x60D840 sub_60D840
// ------------------------------------------------------------
int /*thiscall*/ sub_60D840(float *this, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  int v7; // edi
  float v9; // [esp+14h] [ebp-24h]
  float v10; // [esp+14h] [ebp-24h]
  float v11; // [esp+18h] [ebp-20h]
  float v12; // [esp+18h] [ebp-20h]
  int v13; // [esp+30h] [ebp-8h]
  int v14; // [esp+48h] [ebp+10h]
  float v15; // [esp+48h] [ebp+10h]

  v6 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v13 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v7 = v6 - 1;
  v11 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v9 = (float)v13;
  *(this + 181) = sub_4049C0(v9, v11, a2 - 1, v7);
  if ( a4 == 1 )
  {
    v14 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
    v12 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 4);
    v10 = (float)v14;
    v15 = sub_4049C0(v10, v12, a2 - 1, v7);
    *((uint32_t *)this + 249) = (uint64_t)((double)(rand() % 2000) + v15 - 1000.0);
  }
  else
  {
    *(this + 249) = 8.670878e-37;
  }
  *((uint8_t *)this + 984) = 0;
  *((uint32_t *)this + 250) = a5;
  *((uint32_t *)this + 251) = a3;
  return a3;
}



// ------------------------------------------------------------
// 0x60D940 sub_60D940
// ------------------------------------------------------------
int /*thiscall*/ sub_60D940(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 243;
  for ( i = 3; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60D970 CNEarthFire__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNEarthFire__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
}



// ------------------------------------------------------------
// 0x60D9A0 CNEarthFire__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNEarthFire__vmt14C(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // edx
  void *v11; // ecx
  uint8_t v12[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  void *v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 984) == 0 )
  {
    v2 = *(this + 250);
    if ( v2 != 0 )
    {
      if ( v2 != 1 )
      {
LABEL_10:
        v5 = *(uint32_t *)*(this + 243);
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v7);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v5 + 40))(*(this + 243), v8);
        v9 = sub_699000((int)(this + 16));
        v10 = *this;
        *(this + 247) = v9;
        *(this + 248) = *(this + 251);
        *((uint8_t *)this + 984) = 1;
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(v10 + 212))(
          this,
          "EARTHFIRE_LOOP",
          0,
          0,
          0);
        goto LABEL_11;
      }
      v3 = operator new(0x12Cu);
      v14 = v3;
      v15 = 1;
    }
    else
    {
      v3 = operator new(0x12Cu);
      v14 = v3;
      v15 = 0;
    }
    if ( v3 != nullptr )
      v4 = sub_428F30(v3, (int)"PassiveObject/Common/Particle/FireMissileParticleFloor.ptl", (int)this);
    else
      v4 = nullptr;
    v15 = -1;
    *(this + 243) = v4;
    goto LABEL_10;
  }
LABEL_11:
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v12);
  v11 = (void *)*(this + 29);
  v15 = 2;
  sub_4600B0(v11, 2, 0, (int)v12);
  if ( sub_699000((int)(this + 9)) > *(this + 249) + 100 && *((uint8_t *)this + 264) == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x60DB10 sub_60DB10
// ------------------------------------------------------------
void /*thiscall*/ sub_60DB10(uint32_t *this)
{
  *(this + 245) = 0;
}



// ------------------------------------------------------------
// 0x60DB20 CNShootingStar__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNShootingStar__vmt14C(int *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *v6; // ecx
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  char v10[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v12; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 30 )
  {
    if ( *((uint8_t *)this + 264) == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      {
        v7 = *(this + 244);
        if ( v7 < 0 )
          v7 = *(this + 243);
        v8 = *this;
        v9 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(v8 + 580))(
          this,
          *(this + 71) + 1,
          v7,
          0,
          0,
          0,
          0,
          -v9);
      }
      sub_424120(*(uint32_t **)(*(this + 29) + 132), 8, 500);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
  }
  else
  {
    v2 = *(uint32_t *)*(this + 245);
    v3 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v3);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(this + 245), v5);
    (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v10);
    v6 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(v6, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x60DC60 sub_60DC60
// ------------------------------------------------------------
int /*thiscall*/ sub_60DC60(float *this, uint32_t *a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // edi
  float v7; // [esp+30h] [ebp-2Ch]
  float v8; // [esp+34h] [ebp-28h]
  void *Block; // [esp+48h] [ebp-14h]

  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  v3 = operator new(0x12Cu);
  if ( v3 != nullptr )
    v4 = sub_428F30(v3, (int)"PassiveObject/Common/Particle/ShootingStarFire.ptl", (int)this);
  else
    v4 = nullptr;
  *((uint32_t *)this + 245) = v4;
  (*(void (/*thiscall*/ **)(uint32_t *, float *))(*v4 + 112))(v4, this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 245) + 12))(*((uint32_t *)this + 245), 500);
  v5 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v8 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  *((uint32_t *)this + 244) = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v7 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v7, v8, (int)a2 - 1, v5 - 1);
  *((uint32_t *)this + 243) = a2;
  return sub_4015C0("SSTAR_DROP", 0xAu);
}



// ------------------------------------------------------------
// 0x60DD80 sub_60DD80
// ------------------------------------------------------------
int /*thiscall*/ sub_60DD80(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60DD90 sub_60DD90
// ------------------------------------------------------------
int /*thiscall*/ sub_60DD90(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 247;
  for ( i = 3; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60DDC0 CNShootingStarExp__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNShootingStarExp__vmt14C(char *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int **v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  void *v12; // ecx
  bool v13; // zf
  int result; // eax
  int v15; // [esp-8h] [ebp-34h]
  int v16; // [esp-4h] [ebp-30h]
  char v17[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v19; // [esp+14h] [ebp-18h]
  int v20; // [esp+18h] [ebp-14h]
  int i; // [esp+1Ch] [ebp-10h]
  int v22; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 972) == 0 )
  {
    v2 = *(uint32_t *)this;
    *(this + 972) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(char *))(v2 + 308))(this) != 0 && *((uint32_t *)this + 246) != 1 )
    {
      sub_432FA0();
      for ( i = 0; i < rand() % 4 + 2; ++i )
      {
        v3 = 40003;
        if ( *((uint32_t *)this + 71) == 30067 )
          v3 = 30091;
        if ( *((int *)this + 245) > 0 )
        {
          v4 = *(uint32_t *)this;
          v5 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 4, 0, 0, 0);
          v16 = -(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 128))(this, v5);
          v15 = rand() % 100 - 50;
          v6 = rand();
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, int, int))(v4 + 580))(
            this,
            v3,
            *((uint32_t *)this + 244),
            0,
            v6 % 200 - 100,
            v15,
            v16);
        }
      }
    }
  }
  v7 = (int **)(this + 988);
  i = 3;
  do
  {
    v8 = **v7;
    v9 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
    v10 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, v9);
    v11 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, v10);
    (*(void (/*thiscall*/ **)(int *, int))(v8 + 40))(*v7, v11);
    (*(void (/*thiscall*/ **)(int *, char *))(**v7 + 92))(*v7, v17);
    v12 = *((void **)this + 29);
    v22 = 0;
    sub_4600B0(v12, 2, 0, (int)v17);
    v22 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v7;
    result = i - 1;
    v13 = i == 1;
    Block = nullptr;
    v19 = 0;
    v20 = 0;
    --i;
  }
  while ( !v13 );
  if ( *(uint8_t *)(*((uint32_t *)this + 30) + 170) != 0 && *(this + 264) == 0 )
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x60DFA0 sub_60DFA0
// ------------------------------------------------------------
int /*thiscall*/ sub_60DFA0(float *this, int a2, int a3)
{
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // edi
  float v12; // [esp+10h] [ebp-2Ch]
  float v13; // [esp+14h] [ebp-28h]
  void *Block; // [esp+28h] [ebp-14h]
  int v15; // [esp+2Ch] [ebp-10h]

  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    v5 = sub_428F30(v4, (int)"PassiveObject/Common/Particle/ShootingStarExpSmoke.ptl", (int)this);
  else
    v5 = nullptr;
  *((uint32_t *)this + 247) = v5;
  v6 = operator new(0x12Cu);
  if ( v6 != nullptr )
    v7 = sub_428F30(v6, (int)"PassiveObject/Common/Particle/ShootingStarExp.ptl", (int)this);
  else
    v7 = nullptr;
  *((uint32_t *)this + 248) = v7;
  v8 = operator new(0x12Cu);
  if ( v8 != nullptr )
    v9 = sub_428F30(v8, (int)"PassiveObject/Common/Particle/ShootingStarExpEtc.ptl", (int)this);
  else
    v9 = nullptr;
  *((uint32_t *)this + 249) = v9;
  v10 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v15 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  *((uint32_t *)this + 245) = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v13 = (float)v15;
  v12 = (float)(int)Block;
  *(this + 181) = sub_4049C0(v12, v13, a2 - 1, v10 - 1);
  *((uint32_t *)this + 246) = a3;
  *((uint8_t *)this + 972) = 0;
  *((uint32_t *)this + 244) = a2;
  return sub_4015C0("SSTAR_HIT", 9u);
}



// ------------------------------------------------------------
// 0x60E100 sub_60E100
// ------------------------------------------------------------
int /*thiscall*/ sub_60E100(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = -1;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60E120 CNBoomerang__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBoomerang__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  char result; // al
  int v8; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 30);
  v3 = *(uint32_t *)(v2 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(v2 + 32);
  if ( v4 >= *(this + 244) + *(this + 243) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
    *(this + 243) += *(this + 244);
  }
  v5 = *(this + 173);
  if ( v5 != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
    v6 = *(this + 28);
    *(uint8_t *)(v6 + 124) = 1;
    *(float *)(v6 + 8) = (float)v8;
  }
  if ( *((uint8_t *)this + 980) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
      this,
      "BOOMERANG_SHOOT_LOOP",
      0,
      0,
      0);
    *((uint8_t *)this + 980) = 1;
  }
  result = *((uint8_t *)this + 981);
  if ( result == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
    result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "BOOMERANG_BACK_LOOP",
               1,
               0,
               0);
    *((uint8_t *)this + 981) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E1F0 CNBoomerang__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBoomerang__vmt12C(int this, int a2)
{
  CNRDPassiveObject__vmt12C((uint32_t *)this, a2);
  if ( a2 == this )
  {
    if ( *(uint8_t *)(this + 981) != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 1);
    else
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 216))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x60E230 sub_60E230
// ------------------------------------------------------------
int /*thiscall*/ sub_60E230(int **this)
{
  int *v1; // edx
  int result; // eax

  v1 = *(this + 87);
  if ( v1 != nullptr )
  {
    result = *(this + 88) - v1;
    if ( result != 0 )
    {
      result = *v1;
      *(this + 244) = (int *)*v1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E260 sub_60E260
// ------------------------------------------------------------
int /*thiscall*/ sub_60E260(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x60E280 CNBouncer__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBouncer__vmt14C(void *this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(v2) = *((uint8_t *)this + 980);
  if ( (uint8_t)v2 != 0 )
  {
    v2 = *((uint32_t *)this + 30);
    if ( *(uint8_t *)(v2 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 34));
      LOBYTE(v2) = sub_4926A0(*((uint32_t *)this + 30));
      *((uint8_t *)this + 980) = 0;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x60E2D0 sub_60E2D0
// ------------------------------------------------------------
int /*usercall*/ sub_60E2D0@<eax>(uint32_t *a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int result; // eax
  int v5; // eax
  const void *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // esi
  int v15; // esi
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int v19; // [esp+4h] [ebp-70h] BYREF
  int v20; // [esp+8h] [ebp-6Ch] BYREF
  uint32_t v21[26]; // [esp+Ch] [ebp-68h] BYREF

  v21[25] = dword_796E50;
  (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 352))(a1);
  if ( *((uint8_t *)a1 + 981) == 1 && *((uint8_t *)a1 + 980) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)a1[36]);
    *((uint8_t *)a1 + 980) = 1;
  }
  sub_4926A0(a1[30]);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 88))(a1);
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();
      sub_423A20((int)v21);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 60))(a1, a2);
      v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + 104) + 16))(*(uint32_t *)(v5 + 104));
      v7 = *a1;
      qmemcpy(v21, v6, 0x62u);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 60))(a1);
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 104) + 44))(*(uint32_t *)(v8 + 104));
      *(uint32_t *)((char *)&v21[21] + 1) += -50 - v9;
      if ( *(uint32_t *)((char *)&v21[21] + 1) > 0 )
      {
        v10 = (rand() % 181 + v21[18] + 90) % 360;
        v11 = a1[243];
        v21[18] = v10;
        if ( v11 + *(uint32_t *)((char *)&v21[3] + 3) <= a1[244] )
        {
          *(uint32_t *)((char *)&v21[3] + 3) += v11;
          *(uint32_t *)((char *)&v21[4] + 3) += v11;
        }
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, a3);
        v13 = *a1;
        v19 = v12;
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(v13 + 124))(a1);
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*a1 + 136))(a1, v19, v20, 0) != 0
          || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int, int, int))(*a1 + 140))(
                                a1,
                                &v19,
                                &v20,
                                v19,
                                v20,
                                100,
                                1,
                                1)) != 0 )
        {
          v21[0] = v19;
          v21[1] = v20;
          v21[2] = v14;
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
          v15 = *(uint32_t *)dword_8F8520;
          v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 48))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);
          v17 = *(uint32_t *)dword_8F8520;
          v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 52))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v17 + 36))(dword_8F8520, v18);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v21, 98);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E4E0 CNBouncerLooseSerimalion__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBouncerLooseSerimalion__vmt14C(void *this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(v2) = *((uint8_t *)this + 980);
  if ( (uint8_t)v2 != 0 )
  {
    v2 = *((uint32_t *)this + 30);
    if ( *(uint8_t *)(v2 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 34));
      LOBYTE(v2) = sub_4926A0(*((uint32_t *)this + 30));
      *((uint8_t *)this + 980) = 0;
    }
  }
  if ( *((uint8_t *)this + 984) == 1 )
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                   this,
                   100,
                   *(uint32_t *)(*((uint32_t *)this + 36) + 4),
                   0,
                   0,
                   0,
                   0);
    *((uint8_t *)this + 984) = 0;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x60E560 CNBouncer__vmt1F4
// ------------------------------------------------------------
int /*userpurge*/ CNBouncer__vmt1F4@<eax>(int *a1@<ecx>, int a2@<edi>, uint32_t *a3, float *a4, char a5)
{
  sub_60E2D0(a1, a2, (int)a1);
  return CNRDPassiveObject__vmt1F4(a1, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x60E590 CNBouncer__vmt214
// ------------------------------------------------------------
char /*userpurge*/ CNBouncer__vmt214@<al>(uint32_t *a1@<ecx>, int a2@<edi>, int a3, int a4, int a5)
{
  sub_60E2D0(a1, a2, (int)a1);
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "HEDGEHOG_BUMP", -1, 0, 0);
  return CNRDPassiveObject__vmt214(a1, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x60E5D0 sub_60E5D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60E5D0(int this)
{
  uint32_t *v1; // edx
  int v2; // edx

  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 1;
  v1 = *(uint32_t **)(this + 348);
  if ( v1 != nullptr && (*(uint32_t *)(this + 352) - (int)v1) >> 2 != 0 )
    *(uint32_t *)(this + 972) = *v1;
  v2 = *(uint32_t *)(this + 348);
  if ( v2 != 0 && (unsigned int)((*(uint32_t *)(this + 352) - v2) >> 2) > 1 )
    *(uint32_t *)(this + 976) = *(uint32_t *)(v2 + 4);
  return sub_4015C0("HEDGEHOG_SHOOT", 0xEu);
}



// ------------------------------------------------------------
// 0x60E640 CNBouncerLooseSerimalion__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBouncerLooseSerimalion__vmt12C(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  uint8_t v17[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  uint8_t v19[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *v20; // [esp+1Ch] [ebp-18h]
  int v21; // [esp+30h] [ebp-4h]

  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
  {
    v3 = dword_8F82A8;
    v4 = *(uint32_t *)dword_8F82A8;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 40))(v3, v7);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v3 + 12))(v3, 0);
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v3 + 92))(v3, v19);
    v8 = *(uint32_t *)dword_8F8520;
    v21 = 0;
    v9 = (*(int (/*thiscall*/ **)(int))(v8 + 120))(dword_8F8520);
    sub_4600B0(*(void **)(v9 + 104), 2, 0, (int)v19);
    v10 = dword_8F82AC;
    v11 = *(uint32_t *)dword_8F82AC;
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v12);
    v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v13);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 40))(v10, v14);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v10 + 12))(v10, 0);
    v15 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v10 + 92))(v10, v17);
    LOBYTE(v21) = 1;
    sub_4E77D0((int)v19, v15);
    LOBYTE(v21) = 0;
    if ( Block != nullptr )
      j__free(Block);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    sub_4600B0(*(void **)(v16 + 104), 2, 0, (int)v19);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
    if ( v20 != nullptr )
      j__free(v20);
  }
}



// ------------------------------------------------------------
// 0x60E790 CNBouncerLooseSerimalion__vmt214
// ------------------------------------------------------------
void /*userpurge*/ CNBouncerLooseSerimalion__vmt214(int a1@<ecx>, int a2@<edi>, int a3, int a4, int a5)
{
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  void *v11; // ecx
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  uint8_t v18[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  uint8_t v20[4]; // [esp+1Ch] [ebp-1Ch] BYREF
  void *v21; // [esp+20h] [ebp-18h]
  int v22; // [esp+34h] [ebp-4h]

  sub_60E2D0((uint32_t *)a1, a2, a1);
  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(a1, "HEDGEHOG_BUMP", -1, 0, 0);
  CNRDPassiveObject__vmt214((uint32_t *)a1, a3, a4, a5);
  v6 = dword_8F8280;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8280 + 12))(dword_8F8280, 0);
  v7 = *(uint32_t *)v6;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
  v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v8);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v9);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 40))(v6, v10);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 28))(v6) + 84) = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v6 + 92))(v6, v20);
  v11 = *(void **)(a1 + 116);
  v22 = 0;
  sub_4600B0(v11, 2, 0, (int)v20);
  v12 = dword_8F8284;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8284 + 12))(dword_8F8284, 0);
  v13 = *(uint32_t *)v12;
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
  v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v14);
  v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v15);
  (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(v12, v16);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 28))(v12) + 84) = 0;
  v17 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v12 + 92))(v12, v18);
  LOBYTE(v22) = 1;
  sub_4E77D0((int)v20, v17);
  LOBYTE(v22) = 0;
  if ( Block != nullptr )
    j__free(Block);
  sub_4600B0(*(void **)(a1 + 116), 2, 0, (int)v20);
  if ( v21 != nullptr )
    j__free(v21);
}



// ------------------------------------------------------------
// 0x60E8D0 sub_60E8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_60E8D0(void **this)
{
  *this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x60E8E0 sub_60E8E0
// ------------------------------------------------------------
void /*thiscall*/ sub_60E8E0(uint32_t *this)
{
  *(this + 243) = 0xFFFF;
  *(this + 244) = 0;
}



// ------------------------------------------------------------
// 0x60E900 CNCreateOnDestroyObject__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNCreateOnDestroyObject__vmt12C(uint32_t *this, int a2)
{
  int v3; // ebx
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // [esp-1Ch] [ebp-24h]
  int v7; // [esp-14h] [ebp-1Ch]

  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this
    && *(this + 243) != 0xFFFF
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
      v3 = 0;
    else
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v4 = (uint32_t *)*(this + 173);
    if ( v4 == nullptr )
      v4 = this;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_4E4A50(v4, *(this + 243), *(this + 244), v5, v6, v3, v7, 0, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x60E9A0 sub_60E9A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_60E9A0(unsigned int **this)
{
  unsigned int *v1; // edx
  unsigned int result; // eax
  int v3; // edx

  v1 = *(this + 87);
  if ( v1 != nullptr )
  {
    result = *(this + 88) - v1;
    if ( result != 0 )
    {
      result = *v1;
      *(this + 243) = (unsigned int *)*v1;
    }
  }
  v3 = (int)*(this + 87);
  if ( v3 != 0 )
  {
    result = ((int)*(this + 88) - v3) >> 2;
    if ( result > 1 )
    {
      result = (unsigned int)(*(this + 87) + 1);
      *(this + 244) = *(unsigned int **)(v3 + 4);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60E9F0 CNSunkenRock__vmt144
// ------------------------------------------------------------
char /*thiscall*/ CNSunkenRock__vmt144(void *this, char a2, int a3, int a4, float a5)
{
  int v5; // eax
  int v7; // eax
  int v9; // [esp-20h] [ebp-24h]

  LOBYTE(v5) = a2;
  if ( a2 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
    v5 = __RTDynamicCast(v7, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMasterDogri `RTTI Type Descriptor', 0);
    if ( v5 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 200))(this);
      if ( v5 != 0 )
      {
        v9 = dword_79C0B0;
        (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 200))(this);
        LOBYTE(v5) = sub_491DE0(v9, a3, a4, a5, 2, 1, 255, 1358954495);
      }
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x60EA70 CNSunkenRock__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNSunkenRock__vmt14C(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int i; // edi
  int v11; // eax
  int v13; // [esp-20h] [ebp-24h]
  int v14; // [esp-1Ch] [ebp-20h]
  int v15; // [esp-18h] [ebp-1Ch]
  int v16; // [esp-14h] [ebp-18h]

  if ( *((uint8_t *)this + 973) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSteelMaster `RTTI Type Descriptor', 0) != 0 )
    {
      v3 = *(this + 139);
    }
    else
    {
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNClayMaster `RTTI Type Descriptor', 0) != 0 )
      {
        v3 = *(this + 139) + 152;
      }
      else
      {
        v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        if ( __RTDynamicCast(
               v5,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNMasterDogri `RTTI Type Descriptor',
               0) == 0 )
        {
LABEL_9:
          *((uint8_t *)this + 973) = 1;
          goto LABEL_10;
        }
        v3 = *(this + 139) + 304;
      }
    }
    (*(void (/*stdcall*/ **)(int))(*this + 344))(v3);
    goto LABEL_9;
  }
LABEL_10:
  CNRDPassiveObject__vmt14C((int)this);
  if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) >= 7 && *((uint8_t *)this + 972) == 0 )
  {
    v6 = *this;
    *((uint8_t *)this + 972) = 1;
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v6 + 212))(this, "DOLL_STONE", -1, 0, 0);
  }
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  if ( *(uint8_t *)(v7 + 170) != 0 )
  {
    LOBYTE(v7) = *((uint8_t *)this + 264);
    if ( (uint8_t)v7 == 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 684))(this) != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        v9 = __RTDynamicCast(
               v8,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNMasterDogri `RTTI Type Descriptor',
               0);
        if ( v9 != 0
          && *(uint32_t *)(v9 + 7772) == 3
          && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        {
          for ( i = 30; i < 150; i += 30 )
          {
            v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            v15 = i + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
            v11 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
            sub_4E4A50(v11, 30056, 0, v13, v14, v15, v16, 0, 0, 0);
          }
        }
      }
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_STONE_BREAK",
        -1,
        0,
        0);
      LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)v7 != 0 )
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x60EC70 sub_60EC70
// ------------------------------------------------------------
int /*thiscall*/ sub_60EC70(uint8_t *this, int a2)
{
  int v3; // edi
  double v4; // st7
  uint32_t *v5; // eax
  int result; // eax
  float v7; // [esp+Ch] [ebp-20h]
  float v8; // [esp+10h] [ebp-1Ch]
  int v9; // [esp+24h] [ebp-8h]

  v3 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
  v8 = (float)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)v9;
  v4 = sub_4049C0(v7, v8, a2 - 1, v3 - 1);
  v5 = *((uint32_t **)this + 36);
  *((float *)this + 181) = v4;
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -101,
    *v5,
    0,
    0,
    0,
    0);
  result = sub_4015C0("DOLL_STONE_READY", 0x10u);
  *(this + 972) = 0;
  *(this + 973) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60ED10 CNRedRock__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNRedRock__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 37111);
}



// ------------------------------------------------------------
// 0x60ED40 CNRedRock__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNRedRock__vmt14C(uint8_t *this)
{
  int v2; // eax
  int v3; // eax
  uint32_t *v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax

  CNRDPassiveObject__vmt14C((int)this);
  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  if ( v2 <= 0 )
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)v2 != 0 )
    {
      LOBYTE(v2) = *(this + 972);
      if ( (uint8_t)v2 == 0 )
      {
        v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 60))(this);
        v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 104) + 16))(*(uint32_t *)(v3 + 104));
        *v4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this);
        v4[1] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
        v4[2] = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
        v4[18] = 0;
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v5 = *(uint32_t *)dword_8F8520;
        v6 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v4, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        v9 = *(uint32_t *)this;
        *(this + 972) = 1;
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(
                       this,
                       "FIRELOCK_ROLLING_LOOP",
                       37111,
                       0,
                       0);
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x60EE50 CNRedRock__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNRedRock__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  void *v11; // eax
  bool v12; // zf
  uint8_t v14[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v16; // [esp+10h] [ebp-14h]
  int v17; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  v5 = *(this + 244);
  if ( v5 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
    v6 = *(uint32_t *)*(this + 244);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
    v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*(this + 244), v9);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v14);
    v10 = (void *)*(this + 29);
    v18 = 0;
    sub_4600B0(v10, 2, 0, (int)v14);
    v11 = Block;
    v12 = Block == nullptr;
    *(this + 244) = 0;
    v18 = -1;
    if ( !v12 )
      j__free(v11);
    Block = nullptr;
    v16 = 0;
    v17 = 0;
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x60EF20 sub_60EF20
// ------------------------------------------------------------
int /*thiscall*/ sub_60EF20(float *this, int a2)
{
  int v3; // edi
  double v4; // st7
  uint32_t *v5; // eax
  float v7; // [esp+Ch] [ebp-20h]
  float v8; // [esp+10h] [ebp-1Ch]
  int v9; // [esp+24h] [ebp-8h]

  v3 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v9 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v8 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v7 = (float)v9;
  v4 = sub_4049C0(v7, v8, a2 - 1, v3 - 1);
  v5 = *((uint32_t **)this + 36);
  *(this + 181) = v4;
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    *v5,
    0,
    0,
    0,
    0);
  *(this + 244) = *(this + 219);
  *((uint8_t *)this + 972) = 0;
  *(this + 219) = 0.0;
  return sub_4015C0("THROW_FIRELOCK", 0xEu);
}



// ------------------------------------------------------------
// 0x60EFD0 sub_60EFD0
// ------------------------------------------------------------
int /*stdcall*/ sub_60EFD0(int a1)
{
  return sub_4015C0("CLAY_SHOOT", 0xAu);
}



// ------------------------------------------------------------
// 0x60EFF0 CNDollMasterBubble__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDollMasterBubble__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // edi
  int v6; // ebx
  const char *v7; // eax
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax

  v5 = sub_42FCB0(228);
  v6 = 0;
  if ( v5 != 0 )
  {
    v7 = (const char *)sub_41ACF0(*(this + 178));
    v6 = sub_431860(v5, v7, 1);
  }
  v8 = (char *)sub_44B6C0(284);
  v9 = v8;
  if ( v8 != nullptr )
  {
    sub_44E0D0(v8, v6, 1);
    *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v9 = nullptr;
  }
  sub_45FE80(*(this + 29), (int)v9, 2, 0, (int)v9, (int)this, 0);
  v10 = *(uint32_t *)v9;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 148))(v9, v11);
  v12 = *(uint32_t *)v9;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v13);
  v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14);
  (*(void (/*thiscall*/ **)(char *, int))(v12 + 112))(v9, v15);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CLAY_HIT", -1, 0, 0);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x60F110 CNMagicTargetWarning__vmt2BC
// ------------------------------------------------------------
void /*thiscall*/ CNMagicTargetWarning__vmt2BC(uint32_t *this, int a2, size_t Size)
{
  int v3; // esi
  void *v5; // edx
  int v6; // eax
  signed int v7; // ecx
  int v8; // eax
  float v9; // [esp+0h] [ebp-10h]

  v3 = a2;
  CNRDPassiveObject__vmt2BC(a2, Size);
  v5 = (void *)*(this + 242);
  if ( v5 != nullptr )
  {
    *(this + 243) = *(uint32_t *)a2;
    *(this + 244) = *(uint32_t *)(a2 + 4);
    *(this + 245) = *(uint32_t *)(a2 + 8);
    *(this + 246) = *(uint32_t *)(a2 + 12);
    *((uint16_t *)this + 494) = *(uint16_t *)(a2 + 16);
    v6 = 18;
    if ( *((uint8_t *)this + 982) != 0 )
    {
      qmemcpy((char *)this + 990, (const void *)(a2 + 18), 0x62u);
      v3 = a2;
      v6 = 116;
    }
    v7 = *(uint32_t *)((char *)this + 986);
    *(this + 241) = v7;
    if ( v7 > 0 )
      qmemcpy(v5, (const void *)(v6 + v3), v7);
    v9 = (float)*((int16_t *)this + 492);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    sub_493D00(v8, v9);
  }
  else
  {
    off_77F3FC(aErrorCnmagicta);
  }
}



// ------------------------------------------------------------
// 0x60F1E0 CNMagicTargetWarning__vmt10
// ------------------------------------------------------------
int */*thiscall*/ CNMagicTargetWarning__vmt10(int this)
{
  int *result; // eax
  int v3; // edi

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(int **)(this + 1088);
  if ( result == (int *)3 || result == (int *)4 )
  {
    result = *(int **)(this + 116);
    if ( result != nullptr )
    {
      result = (int *)result[33];
      if ( result != nullptr )
      {
        result = (int *)__RTDynamicCast(
                          result[13],
                          0,
                          &CNRDObject `RTTI Type Descriptor',
                          &IRDCollisionObject `RTTI Type Descriptor',
                          0);
        if ( result != nullptr )
        {
          v3 = (*(int (/*thiscall*/ **)(int *))(*result + 376))(result);
          if ( v3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )
            return (int *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 3, -1);
          else
            return (int *)(*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 252))(this, 3, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60F270 CNMagicTargetWarning__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNMagicTargetWarning__vmt14C(uint8_t *this)
{
  int v2; // eax
  uint8_t *v3; // edi
  int v4; // eax
  int v5; // edx
  int v7; // [esp-8h] [ebp-Ch]

  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)v2 != 0 )
    {
      LOBYTE(v2) = *(this + 264);
      if ( (uint8_t)v2 == 0 )
      {
        v3 = *((uint8_t **)this + 173);
        if ( v3 == nullptr )
          v3 = this;
        v4 = *(this + 983);
        if ( v4 == 4 )
          v4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
        if ( *(this + 982) != 0 )
        {
          *(uint32_t *)(this + 990) = *((int16_t *)this + 488);
          *(uint32_t *)(this + 994) = *((int16_t *)this + 489);
          *(uint32_t *)(this + 998) = *((int16_t *)this + 490);
          v7 = *((uint32_t *)this + 242);
          v5 = *((uint16_t *)this + 486);
          *(this + 1074) = v4 == 0;
          sub_4E4C10(v3, v5, *((uint16_t *)this + 487), this + 990, 0, 0, *((uint32_t *)this + 241), v7);
        }
        else
        {
          sub_4E4A50(
            v3,
            *((uint16_t *)this + 486),
            *((uint16_t *)this + 487),
            *((int16_t *)this + 488),
            *((int16_t *)this + 489),
            *((int16_t *)this + 490),
            v4,
            0,
            *((uint32_t *)this + 241),
            *((uint32_t *)this + 242));
        }
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x60F3A0 sub_60F3A0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F3A0(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = a2;
  *(this + 272) = a2;
  if ( a2 == 3 )
  {
    v2 = 1;
  }
  else if ( a2 == 4 )
  {
    v2 = 2;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * v2));
}



// ------------------------------------------------------------
// 0x60F3E0 sub_60F3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F3E0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60F410 CNForceField__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNForceField__vmt10(int this)
{
  int result; // eax
  int v3; // edi
  int v4; // ebx
  uint32_t *v5; // esi
  int i; // [esp+4h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint32_t *)(this + 692);
  if ( result != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
    v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 692) + 124))(*(uint32_t *)(this + 692));
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 112))(this, v3, v4, 0);
    v5 = (uint32_t *)(this + 972);
    for ( i = 4; i != 0; --i )
    {
      if ( *v5 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*v5 + 112))(*v5, v3, v4, 0);
      ++v5;
      result = i - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60F480 CNForceField__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNForceField__vmt12C(uint32_t *this, int a2)
{
  int result; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  result = 0;
  if ( a2 == *(this + 243) )
    *(this + 243) = 0;
  if ( a2 == *(this + 244) )
    *(this + 244) = 0;
  if ( a2 == *(this + 245) )
    *(this + 245) = 0;
  if ( a2 == *(this + 246) )
    *(this + 246) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60F4E0 sub_60F4E0
// ------------------------------------------------------------
int sub_60F4E0()
{
  sub_4015C0("FORCE_FIELD_CIRCLE", 0x12u);
  return sub_4015C0("FORCE_FIELD_FIRE", 0x10u);
}



// ------------------------------------------------------------
// 0x60F510 CNForceField__vmt14C
// ------------------------------------------------------------
int /*usercall*/ sub_60F510@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // edi
  char *v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // ebx
  char *v8; // eax
  int v9; // eax
  int v10; // ecx
  char *v11; // eax
  int v12; // eax
  int v13; // ecx
  char *v14; // eax
  int v15; // eax
  int v16; // ecx
  uint32_t *v17; // eax
  int result; // eax
  int v19; // [esp+Ch] [ebp-1Ch]
  char *v20; // [esp+Ch] [ebp-1Ch]
  char *v21; // [esp+Ch] [ebp-1Ch]
  char *v22; // [esp+Ch] [ebp-1Ch]
  int v23; // [esp+10h] [ebp-18h]
  int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+10h] [ebp-18h]
  int v26; // [esp+10h] [ebp-18h]
  int v27; // [esp+14h] [ebp-14h]
  int v28; // [esp+18h] [ebp-10h]

  sub_600890();
  v3 = a1[173];
  if ( *((uint8_t *)a1 + 988) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 148) == 1 && a1[253] != 0 )
    {
      if ( a1[254] < 0x10u )
        v17 = a1 + 249;
      else
        v17 = (uint32_t *)a1[249];
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*a1 + 212))(a1, v17, -1, 0, 0);
      sub_4015C0((void *)szPassword, 0);
    }
  }
  else if ( v3 != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, a2);
    v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
    v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3);
    if ( sub_42FCB0(228) != 0 )
      v23 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/dirt.ani", 1);
    else
      v23 = 0;
    v4 = (char *)sub_44B6C0(284);
    if ( v4 != nullptr )
    {
      sub_44E0D0(v4, v23, 1);
      *(uint32_t *)v4 = &CNRDPooledObject::`vftable';
      v5 = (int)v4;
    }
    else
    {
      v5 = 0;
    }
    v6 = a1[29];
    a1[243] = v5;
    sub_45FE80(v6, v3, 2, 0, v5, v3, 1);
    v7 = v19;
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[243] + 112))(a1[243], v19, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v24 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/blast.ani", 1);
    else
      v24 = 0;
    v8 = (char *)sub_44B6C0(284);
    v20 = v8;
    if ( v8 != nullptr )
    {
      sub_44E0D0(v8, v24, 1);
      v9 = (int)v20;
      *(uint32_t *)v20 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v9 = 0;
    }
    v10 = a1[29];
    a1[244] = v9;
    sub_45FE80(v10, v3, 2, 0, v9, v3, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[244] + 112))(a1[244], v7, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v25 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/chargecircle.ani", 1);
    else
      v25 = 0;
    v11 = (char *)sub_44B6C0(284);
    v21 = v11;
    if ( v11 != nullptr )
    {
      sub_44E0D0(v11, v25, 1);
      v12 = (int)v21;
      *(uint32_t *)v21 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v12 = 0;
    }
    v13 = a1[29];
    a1[245] = v12;
    sub_45FE80(v13, v3, 2, 0, v12, v3, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[245] + 112))(a1[245], v7, v27, v28);
    if ( sub_42FCB0(228) != 0 )
      v26 = sub_431860((char)"PassiveObject/Common/Animation/ForceField/Field.ani", 1);
    else
      v26 = 0;
    v14 = (char *)sub_44B6C0(284);
    v22 = v14;
    if ( v14 != nullptr )
    {
      sub_44E0D0(v14, v26, 1);
      v15 = (int)v22;
      *(uint32_t *)v22 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v15 = 0;
    }
    v16 = a1[29];
    a1[246] = v15;
    sub_45FE80(v16, v3, 2, 0, v15, v3, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)a1[246] + 112))(a1[246], v7, v27);
    *((uint8_t *)a1 + 988) = 1;
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
    *((uint8_t *)a1 + 988) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = a1[243];
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x60F8A0 sub_60F8A0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F8A0(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x60F8C0 sub_60F8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_60F8C0(int this, int a2, int a3)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 980) = a2;
  *(uint32_t *)(this + 976) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x60F8E0 CNCircleAppendageMaker__vmt2C8
// ------------------------------------------------------------
int /*thiscall*/ CNCircleAppendageMaker__vmt2C8(uint32_t *this, int *a2, uint32_t *a3)
{
  int result; // eax
  int v5; // esi
  int *v6; // eax
  int v7; // ebx
  uint32_t *v8; // edi
  int v9; // ecx

  result = *(this + 244);
  if ( result == 0 )
  {
    result = __RTDynamicCast(
               *(this + 173),
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDCharacter `RTTI Type Descriptor',
               0);
    v5 = result;
    if ( result != 0 )
    {
      v6 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 1032))(result);
      v7 = *v6;
      v8 = (uint32_t *)sub_47E720(*v6, *(this + 245));
      result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 1140))(v5, *(this + 245));
      if ( v7 != 0 )
      {
        if ( v7 == 1 )
        {
          v9 = *(this + 245);
          switch ( v9 )
          {
            case 30:
              result = sub_47EF20(v8, 1u, result, -1, -1, 11);
LABEL_7:
              *a2 = result;
              *a3 = 0;
              return result;
            case 31:
              result = sub_47EF20(v8, 2u, result, -1, -1, 11);
              goto LABEL_7;
            case 39:
              result = sub_47EF20(v8, 2u, result, -1, -1, 11);
LABEL_12:
              *a2 = result;
              *a3 = 1;
              return result;
            case 44:
              result = sub_47EF20(v8, 1u, result, -1, -1, 11);
              goto LABEL_12;
            default:
              break;
          }
        }
        else if ( v7 == 2 )
        {
          if ( *(this + 245) == 50 )
          {
            *a2 = sub_47EF20(v8, 0, result, -1, -1, 11);
            *a3 = 0;
            return (int)a3;
          }
        }
        else if ( v7 == 3 && *(this + 245) == 28 )
        {
          *a2 = sub_47EF20(v8, 0, result, -1, -1, 11);
          *a3 = 1;
          return (int)a3;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FA60 sub_60FA60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60FA60(uint32_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *this = &vftbl_CNProvocationed;
  sub_652010(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x60FAC0 CNProvocationed__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNProvocationed__vmt0(void *Block, char a2)
{
  sub_60FAF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x60FAF0 sub_60FAF0
// ------------------------------------------------------------
int /*thiscall*/ sub_60FAF0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60FB40 sub_60FB40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_60FB40(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNAimVitalPoint;
  sub_652220(this);
  sub_652230(a2);
  return this;
}



// ------------------------------------------------------------
// 0x60FBA0 CNAimVitalPoint__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNAimVitalPoint__vmt0(void *Block, char a2)
{
  sub_60FBD0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x60FBD0 sub_60FBD0
// ------------------------------------------------------------
int /*thiscall*/ sub_60FBD0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNAimVitalPoint;
  sub_652350();
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x60FC30 sub_60FC30
// ------------------------------------------------------------
int /*thiscall*/ sub_60FC30(int *this, int a2, int a3)
{
  int result; // eax
  int i; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // esi
  int v10; // eax
  int v11; // ebx
  bool v12; // zf
  float v13[6]; // [esp+4h] [ebp-1Ch] BYREF
  int v14; // [esp+1Ch] [ebp-4h]

  result = a2;
  if ( a2 != 0 )
  {
    result = *(this + 29);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( result != 0 )
      {
        for ( i = 0; ; ++i )
        {
          v6 = *(this + 29);
          v7 = *(uint32_t *)(v6 + 120);
          v14 = i;
          if ( v7 != 0 )
            result = (*(uint32_t *)(v6 + 124) - v7) >> 2;
          else
            result = 0;
          if ( i >= result )
            return result;
          v8 = *(uint32_t *)(v6 + 120);
          if ( v8 != 0 && i < (unsigned int)((*(uint32_t *)(v6 + 124) - v8) >> 2) )
            v9 = *(uint32_t *)(v8 + 4 * i);
          else
            v9 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 17) != 0 )
          {
            if ( a3 == 0 )
            {
              v10 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
              v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10);
              v12 = v11 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 376))(v9);
              i = v14;
              if ( !v12 )
                continue;
LABEL_19:
              if ( (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, v9, 0) <= a2 / 2 )
              {
                memset(v13, 0, sizeof(v13));
                sub_4E5F70(i, (int)this, v9, v13, 0, 0);
              }
              continue;
            }
            if ( a3 != 1 )
              goto LABEL_19;
            (*(void (/*thiscall*/ **)(int *))(*this + 684))(this);
            if ( (uint8_t)sub_4E4630(v9) != 0 )
              goto LABEL_19;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FD70 CNCircleAppendageMaker__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNCircleAppendageMaker__vmt14C(int *this)
{
  char result; // al
  int v3; // edx
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  CNRDPassiveObject__vmt14C((int)this);
  result = *((uint8_t *)this + 972);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( result != 0 )
    {
      v3 = *this;
      v4 = 0;
      v5 = 0;
      (*(void (/*thiscall*/ **)(int *, int *, int *))(v3 + 712))(this, &v4, &v5);
      sub_60FC30(this, v4, v5);
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x60FDE0 CNCircleAppendageMaker__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ sub_60FDE0(int *this, int a2, int a3, int a4)
{
  int v5; // ebx
  int v6; // ecx
  int v7; // eax
  int v8; // esi
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // esi
  int v12; // eax
  void *v13; // edi
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // eax
  int v17; // esi
  void *v18; // eax
  int v19; // esi
  uint32_t *v20; // eax
  int v21; // eax
  int v22; // eax
  uint32_t *v23; // eax
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  uint32_t *v27; // eax
  uint32_t *v28; // esi
  int *v29; // eax
  uint32_t *v30; // edi
  int v31; // esi
  int v32; // eax
  int v33; // eax
  uint32_t *v34; // edi
  int v35; // ebx
  unsigned int i; // esi
  int v37; // ecx
  int v38; // ecx
  int v39; // eax
  float v41; // [esp+10h] [ebp-2Ch]
  unsigned int v42; // [esp+14h] [ebp-28h]
  void *Block; // [esp+20h] [ebp-1Ch]
  int v44; // [esp+24h] [ebp-18h]
  int v45; // [esp+28h] [ebp-14h]
  int v46; // [esp+28h] [ebp-14h]
  float v47; // [esp+28h] [ebp-14h]
  float v48; // [esp+28h] [ebp-14h]
  int v50; // [esp+44h] [ebp+8h]

  v5 = sub_5FF9C0(a2, a3, a4);
  v44 = v5;
  v6 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  v50 = v6;
  if ( v6 != 0 )
  {
    v7 = *(this + 244);
    a4 = 0;
    v45 = 0;
    a3 = 0;
    if ( v7 != 0 )
    {
      if ( v7 == 1 )
      {
        (*(void (/*thiscall*/ **)(int *, int *, int *))(*this + 708))(this, &a4, &a3);
      }
      else
      {
        if ( v7 != 2 || *(this + 245) != 0 )
          return v5;
        v34 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 700))(v6);
        v35 = sub_41C5A0(v34);
        for ( i = 0; (int)i < v35; ++i )
        {
          v37 = v34[1];
          if ( v37 != 0 && i < (v34[2] - v37) >> 2 )
            v38 = *(uint32_t *)(v37 + 4 * i);
          else
            v38 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v38 + 92))(v38) != 0 )
          {
            v39 = sub_517740(i);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v39 + 76))(v39, 0);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v50 + 956))(v50);
          }
        }
      }
    }
    else
    {
      v8 = __RTDynamicCast(
             *(this + 173),
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDCharacter `RTTI Type Descriptor',
             0);
      if ( v8 == 0 )
        return v5;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 1032))(v8);
      v10 = *v9;
      sub_47E720(*v9, *(this + 245));
      v11 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 1140))(v8, *(this + 245));
      if ( v10 != 0 )
      {
        if ( v10 == 1 )
        {
          v12 = *(this + 245);
          switch ( v12 )
          {
            case 30:
              v13 = operator new(0x84u);
              v14 = 0;
              if ( v13 != nullptr )
              {
                v15 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
                v14 = sub_4DF1B0((int)v13, v11, 3, 1, v15);
              }
              a4 = v14;
              v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img");
              v45 = sub_418DD0(v16, 2u);
              a3 = 1;
              break;
            case 31:
              v46 = sub_47EF20(0, v11, -1, -1, 11);
              v17 = sub_47EF20(1, v11, -1, -1, 11);
              v18 = operator new(0x7Cu);
              if ( v18 != nullptr )
                v19 = sub_4B3C90((int)v18, v17, 1);
              else
                v19 = 0;
              v47 = (float)v46;
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v19 + 120))(v19, 7, 0, LODWORD(v47));
              v41 = v47 * 0.001;
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v19 + 120))(v19, 24, 0, LODWORD(v41));
              a4 = v19;
              v20 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img",
                                3);
              v21 = sub_418DD0(v20, v42);
              a3 = 2;
              v45 = v21;
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)v50 + 212))(
                v50,
                "BUFF_FASTFIST",
                -1,
                0);
              break;
            case 39:
              if ( operator new(0x5Cu) != nullptr )
                v22 = sub_60FB40(v11);
              else
                v22 = 0;
              a4 = v22;
              v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img",
                                10);
              v24 = sub_418DD0(v23, v42);
              a3 = 7;
              v45 = v24;
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)v50 + 212))(
                v50,
                "BUFF_FATAL_POINT",
                -1,
                0);
              break;
            case 44:
              v25 = sub_47EF20(0, v11, -1, -1, 11);
              v48 = (double)(int)sub_47EF20(2, v11, -1, -1, 11) * 0.1;
              if ( operator new(0x54u) != nullptr )
                v26 = sub_60FA60(v25, LODWORD(v48));
              else
                v26 = 0;
              a4 = v26;
              v27 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img");
              v45 = sub_418DD0(v27, 0x17u);
              a3 = 8;
              break;
            default:
              break;
          }
        }
        else if ( v10 == 2 )
        {
          if ( *(this + 245) == 50 )
          {
            v28 = (uint32_t *)__RTDynamicCast(
                              v50,
                              0,
                              &IRDActiveObject `RTTI Type Descriptor',
                              &IRDMonster `RTTI Type Descriptor',
                              0);
            if ( v28 != nullptr && v28[2088] == *(this + 173) )
            {
              v29 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28);
              if ( sub_4C0400(*v29) != 0 )
              {
                if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60002 )
                {
                  sub_5C24B0(v28);
                }
                else if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60003 )
                {
                  sub_5C2D60(v28);
                }
                else if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 340))(v28) == 60004 )
                {
                  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*v28 + 732))(v28, 0, 0, 1);
                }
              }
            }
          }
        }
        else if ( v10 == 3 && *(this + 245) == 28 )
        {
          v30 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v50 + 700))(v50);
          v31 = 0;
          Block = (void *)sub_41C5A0(v30);
          if ( (int)Block > 0 )
          {
            do
            {
              v32 = sub_517740(v31);
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v32 + 92))(v32) != 0 )
              {
                v33 = sub_517740(v31);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v33 + 76))(v33, 0);
              }
              ++v31;
            }
            while ( v31 < (int)Block );
          }
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v50 + 956))(v50);
        }
      }
    }
    if ( a4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, int))(*(uint32_t *)a4 + 56))(
        a4,
        v50,
        *(this + 173),
        1,
        v45,
        a3,
        -1);
    return v44;
  }
  return v5;
}


// ------------------------------------------------------------
// 0x610320 CNToothSFish__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNToothSFish__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  uint32_t *v4; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // ecx
  unsigned int v9; // esi
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int i; // edi
  int *v15; // esi
  int v16; // ebx
  int v17; // eax
  int v19; // [esp+8h] [ebp-8h]
  int v21; // [esp+1Ch] [ebp+Ch]
  char v22; // [esp+23h] [ebp+13h]

  v4 = a2;
  v5 = CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
  v19 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 17) == 0 )
    return v5;
  v22 = 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 700))(a2);
  v7 = v6;
  v8 = *(uint32_t *)(v6 + 4);
  v9 = 0;
  if ( v8 != 0 )
    v21 = (*(uint32_t *)(v6 + 8) - v8) >> 2;
  else
    v21 = 0;
  if ( v21 > 0 )
  {
    do
    {
      v10 = *(uint32_t *)(v7 + 4);
      if ( v10 != 0 && v9 < (*(uint32_t *)(v7 + 8) - v10) >> 2 )
        v11 = *(uint32_t *)(v10 + 4 * v9);
      else
        v11 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 92))(v11) != 0 )
      {
        v12 = *(uint32_t *)(v7 + 4);
        if ( v12 != 0 && v9 < (*(uint32_t *)(v7 + 8) - v12) >> 2 )
          v13 = *(uint32_t *)(v12 + 4 * v9);
        else
          v13 = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 76))(v13, 0);
        v22 = 1;
      }
      ++v9;
    }
    while ( (int)v9 < v21 );
    if ( v22 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*a2 + 956))(a2);
  }
  for ( i = 0; i < 17; ++i )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 776))(v4, i) != 0 )
    {
      v15 = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v4 + 772))(v4, i);
      v16 = *v15;
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 576))(this);
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v16 + 4))(v15, 0, v17);
      v4 = a2;
    }
  }
  return v19;
}



// ------------------------------------------------------------
// 0x610440 CNToothKurokuta__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNToothKurokuta__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // ebx
  int v6; // ebx
  int v7; // eax
  int v9; // [esp+18h] [ebp+Ch]
  int v10; // [esp+1Ch] [ebp+10h]

  v5 = CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
  v9 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) == 0 )
    return v5;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v6 = sub_445870((uint32_t *)dword_8F8520, 37992, 17);
  v10 = *a2;
  v7 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 576))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v10 + 760))(a2, v6, 1120403456, 3, v7);
  return v9;
}



// ------------------------------------------------------------
// 0x6106B0 CNCurseBomb__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNCurseBomb__vmt14C(uint32_t *this)
{
  uint32_t *v1; // edi
  int v2; // eax
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // edx
  int v9; // [esp-1Ch] [ebp-20h]
  int v10; // [esp-18h] [ebp-1Ch]
  int v11; // [esp-14h] [ebp-18h]
  uint32_t *v12; // [esp-4h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( v4 <= 0 )
  {
    v5 = (uint32_t *)*(this + 36);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    v7 = *this;
    if ( v6 == *v5 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 200))(this);
      if ( *(uint8_t *)(v4 + 170) != 0 )
      {
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)v4 != 0 )
        {
          LOBYTE(v4) = *((uint8_t *)this + 264);
          if ( (uint8_t)v4 == 0 )
          {
            v12 = v5;
            v1 = (uint32_t *)*(this + 173);
            if ( v1 == nullptr )
              v1 = this;
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
            v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
            v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
            sub_4E4A50(v1, *(this + 243), 0, v2, v9, v10, v11, 0, 0, 0);
            LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(*this + 312))(this, 0, v12);
          }
        }
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 196))(this, *(uint32_t *)*(this + 36));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) + 60) = 0;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
      *(uint32_t *)v4 = 0;
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x610740 sub_610740
// ------------------------------------------------------------
int /*thiscall*/ sub_610740(uint32_t **this)
{
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      0,
      **(this + 36),
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      1,
      (*(this + 36))[1],
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      2,
      (*(this + 36))[2],
      0,
      0,
      0,
      0);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      3,
      (*(this + 36))[3],
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("BOMB_EXPLOSION", 0xEu);
}



// ------------------------------------------------------------
// 0x6107E0 CNCurseBombSub__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNCurseBombSub__vmt14C(int **this)
{
  uint32_t *v2; // edi
  int *v3; // eax
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int *v7; // eax
  int **v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *v13; // ecx
  bool v14; // zf
  char result; // al
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *v20; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    v2 = operator new(0x12Cu);
    v20 = v2;
    v3 = nullptr;
    v21 = 0;
    if ( v2 != nullptr )
    {
      v4 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(v2, v4, (int)this);
    }
    *(this + 243) = v3;
    v5 = operator new(0x12Cu);
    v20 = v5;
    v21 = 1;
    if ( v5 != nullptr )
    {
      v6 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(v5, v6, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    v8 = this + 243;
    v20 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**v8 + 12))(*v8, 0);
      v9 = **v8;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*v8, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v8 + 92))(*v8, v16);
      v13 = *(this + 29);
      v21 = 2;
      sub_4600B0(v13, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++v8;
      v14 = v20 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      v20 = (char *)v20 - 1;
    }
    while ( !v14 );
  }
  result = *((uint8_t *)*(this + 30) + 170);
  if ( result != 0 )
    return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x610960 sub_610960
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_610960(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNCurseBomb;
  *(this + 243) = a3;
  sub_5FF8E0((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x6109C0 CNCurseBomb__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNCurseBomb__vmt0(void *Block, char a2)
{
  sub_6109F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x6109F0 sub_6109F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6109F0(void **this)
{
  *this = &vftbl_CNCurseBomb;
  sub_5FF980(this);
  *this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x610A50 sub_610A50
// ------------------------------------------------------------
int /*thiscall*/ sub_610A50(int this)
{
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = -1;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint8_t *)(this + 1004) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x610A80 sub_610A80
// ------------------------------------------------------------
void /*thiscall*/ sub_610A80(void **this)
{
  if ( *(this + 246) != nullptr )
    j__free(*(this + 246));
  *(this + 246) = nullptr;
}



// ------------------------------------------------------------
// 0x610AB0 CNSummonMonsterWithEffect__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNSummonMonsterWithEffect__vmt14C(uint32_t *this)
{
  int v2; // eax
  int *v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 && *((uint8_t *)this + 1004) == 0 )
  {
    v2 = *(this + 247);
    if ( v2 == -1 )
    {
      if ( *(uint8_t *)(*(this + 30) + 170) == 0 )
        goto LABEL_12;
    }
    else if ( *(uint32_t *)(*(this + 30) + 148) < v2 )
    {
      goto LABEL_12;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )
        *(this + 248) = -*(this + 248);
      v3 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v4 = *v3;
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 152))(
             this,
             0,
             0,
             0,
             *((uint16_t *)this + 489),
             *((uint8_t *)this + 980),
             *((uint8_t *)this + 981),
             *(this + 246),
             0);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, v5);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, *(this + 250) + v6);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, *(this + 249) + v7);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, int))(v4 + 592))(
        v3,
        *(uint16_t *)((char *)this + 973),
        *(uint16_t *)((char *)this + 975),
        *((uint8_t *)this + 977),
        *(this + 248) + v8);
    }
    *((uint8_t *)this + 1004) = 1;
  }
LABEL_12:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x610C00 CNSummonMonsterWithEffect__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ sub_610C00(uint32_t *this, uint32_t *a2, size_t Size)
{
  size_t v3; // edi
  char *v5; // eax
  int v6; // edx
  int result; // eax
  size_t v8; // eax
  int v9; // eax
  size_t v10; // eax
  int v11; // eax
  size_t v12; // eax
  int v13; // eax
  size_t v14; // eax
  int v15; // eax
  size_t v16; // eax
  int v17; // eax
  size_t v18; // eax
  size_t v19; // eax

  v3 = Size;
  sub_5FFF80((int)this, a2, Size);
  *(this + 243) = *a2;
  *(this + 244) = a2[1];
  *((uint16_t *)this + 490) = *((uint16_t *)a2 + 4);
  if ( v3 > 0xA )
  {
    if ( *(this + 246) == 0 )
    {
      v5 = (char *)operator new(7u);
      if ( v5 != nullptr )
      {
        *v5 = 0;
        v5[1] = 0;
        v5[2] = 0;
        *(uint32_t *)(v5 + 3) = 0;
      }
      else
      {
        v5 = nullptr;
      }
      *(this + 246) = v5;
    }
    v6 = *(this + 246);
    *(uint32_t *)v6 = *(uint32_t *)((char *)a2 + 10);
    *(uint16_t *)(v6 + 4) = *((uint16_t *)a2 + 7);
    *(uint8_t *)(v6 + 6) = *((uint8_t *)a2 + 16);
  }
  result = *((uint8_t *)this + 972);
  switch ( *((uint8_t *)this + 972) )
  {
    case 0:
      v8 = sub_42FCB0(228);
      Size = v8;
      if ( v8 != 0 )
        v9 = sub_431860(v8, "Common/CommonEffect/Animation/SummonCircleBack.ani", 1);
      else
        v9 = 0;
      Size = v9;
      sub_42ABE0(&Size);
      v10 = sub_42FCB0(228);
      Size = v10;
      if ( v10 != 0 )
        v11 = sub_431860(v10, "Common/CommonEffect/Animation/SummonCircle.ani", 1);
      else
        v11 = 0;
      Size = v11;
      sub_42ABE0(&Size);
      v12 = sub_42FCB0(228);
      Size = v12;
      if ( v12 != 0 )
        v13 = sub_431860(v12, "Common/CommonEffect/Animation/SummonCircleFront.ani", 1);
      else
        v13 = 0;
      Size = v13;
      sub_42ABE0(&Size);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)*(this + 36),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                 this,
                 100,
                 *(uint32_t *)(*(this + 36) + 8),
                 0,
                 0,
                 0,
                 0);
      *(this + 247) = 9;
      return result;
    case 1:
      v14 = sub_42FCB0(228);
      Size = v14;
      if ( v14 == 0 )
        goto LABEL_25;
      v15 = sub_431860(v14, "Monster/Spirit/FireAnimation/Summon.ani", 1);
      goto LABEL_26;
    case 2:
      v16 = sub_42FCB0(228);
      Size = v16;
      if ( v16 == 0 )
        goto LABEL_29;
      v17 = sub_431860(v16, "Monster/Spirit/WaterAnimation/Summon.ani", 1);
      goto LABEL_30;
    case 3:
      v18 = sub_42FCB0(228);
      Size = v18;
      if ( v18 != 0 )
        v15 = sub_431860(v18, "Monster/Spirit/DarkAnimation/Summon.ani", 1);
      else
LABEL_25:
        v15 = 0;
LABEL_26:
      Size = v15;
      sub_42ABE0(&Size);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
    case 4:
      v19 = sub_42FCB0(228);
      Size = v19;
      if ( v19 != 0 )
        v17 = sub_431860(v19, "Monster/Spirit/LightAnimation/Summon.ani", 1);
      else
LABEL_29:
        v17 = 0;
LABEL_30:
      Size = v17;
      sub_42ABE0(&Size);
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      *(this + 250) = 40;
      break;
    default:
      return result;
  }
  return result;
}


// ------------------------------------------------------------
// 0x610F40 sub_610F40
// ------------------------------------------------------------
int /*thiscall*/ sub_610F40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = -1;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint8_t *)(this + 997) = 0;
  *(uint32_t *)(this + 1000) = -1;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1008) = 4;
  return 0;
}



// ------------------------------------------------------------
// 0x610F90 sub_610F90
// ------------------------------------------------------------
int /*thiscall*/ sub_610F90(int this, int a2)
{
  int v3; // eax
  int v4; // eax
  int result; // eax

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v4 = sub_45EBE0(*(uint32_t **)(v3 + 104), HIWORD(a2), (uint16_t)a2);
  result = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  *(uint32_t *)(this + 972) = result;
  *(uint8_t *)(this + 701) = 0;
  *(uint8_t *)(this + 700) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x610FF0 CNBodyHit__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNBodyHit__vmt2BC(float *this, int *a2, int Size)
{
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // ebx
  int v10; // edi
  int v12; // [esp+10h] [ebp-4h]
  int16_t v13; // [esp+1Ch] [ebp+8h]
  int16_t Sizea; // [esp+20h] [ebp+Ch]
  signed int Sizeb; // [esp+20h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v6 = 0;
  if ( Size >= 4 )
  {
    v6 = 4;
    *(this + 181) = (float)*a2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 244) = *(int16_t *)((char *)a2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 245) = *(int16_t *)((char *)a2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 2 )
  {
    *((uint32_t *)this + 246) = *(int16_t *)((char *)a2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 4 )
  {
    *((uint32_t *)this + 247) = *(int *)((char *)a2 + v6);
    v6 += 4;
  }
  if ( Size - v6 >= 4 )
  {
    *((uint32_t *)this + 248) = *(int *)((char *)a2 + v6);
    v6 += 4;
  }
  Sizea = -31072;
  v13 = 5;
  if ( Size - v6 >= 2 )
  {
    Sizea = *(uint16_t *)((char *)a2 + v6);
    v6 += 2;
  }
  if ( Size - v6 >= 1 )
    v13 = *((uint8_t *)a2 + v6);
  v7 = *((uint32_t *)this + 243);
  if ( v7 != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 672))(v7, 3);
    v12 = sub_41A5E0(v8 + 984);
    v9 = Sizea;
    if ( (int)(uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v8 + 998))) > Sizea )
    {
      v10 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)this + 243) + 672))(*((uint32_t *)this + 243), 3);
      Sizeb = sub_41A5E0(v10 + 984);
      *(this + 181) = ((double)(int)((uint64_t)((double)Sizeb * COERCE_FLOAT(sub_41A5E0(v10 + 998))) - v9)
                     * (double)v13
                     * 0.000001
                     + 1.0)
                    * *(this + 181);
    }
  }
  return (*(int (/*thiscall*/ **)(float *, float *))(*(uint32_t *)this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x611180 CNBodyHit__vmt160
// ------------------------------------------------------------
int /*thiscall*/ CNBodyHit__vmt160(int *this)
{
  int result; // eax

  IRDCollisionObject__vmt160(this);
  result = *(this + 243);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 356))(this, *(this + 243));
  return result;
}



// ------------------------------------------------------------
// 0x6111A0 sub_6111A0
// ------------------------------------------------------------
void /*thiscall*/ sub_6111A0(int *this, int a2)
{
  int v2; // esi

  *(this + 251) = a2;
  if ( a2 == 1 )
  {
    v2 = *(this + 30);
    if ( *(uint32_t *)(v2 + 148) == -1 )
      sub_4938F0(*(this + 30));
    if ( *(uint32_t *)(v2 + 120) != 0 )
      j__free(*(void **)(v2 + 120));
    *(uint32_t *)(v2 + 120) = 0;
    *(uint32_t *)(v2 + 124) = 0;
    *(uint32_t *)(v2 + 128) = 0;
  }
}



// ------------------------------------------------------------
// 0x611200 sub_611200
// ------------------------------------------------------------
int /*userpurge*/ sub_611200@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3@<esi>, char a4)
{
  int *v4; // edi
  int result; // eax
  const char *v6; // eax
  int v7; // eax
  int v8; // ebx
  char *v9; // eax
  int v10; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  float v16; // [esp+4h] [ebp-A0h]
  int v18; // [esp+Ch] [ebp-98h]
  int v19; // [esp+10h] [ebp-94h]
  char Buffer[128]; // [esp+14h] [ebp-90h] BYREF
  int v21; // [esp+94h] [ebp-10h]
  int v22; // [esp+A0h] [ebp-4h]

  v4 = a1;
  v21 = dword_796E50;
  result = a1[243];
  if ( result != 0 )
  {
    v19 = 0;
    v16 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 192))(result) * 0.0062500001;
    do
    {
      v6 = "Wall";
      if ( a4 == 0 )
        v6 = "Floor";
      sprintf(Buffer, "Character/Fighter/Effect/Animation/ThrowEnemy%s%d.ani", v6, v19);
      v7 = sub_42FCB0(228);
      v8 = 0;
      v22 = 0;
      if ( v7 != 0 )
        v8 = sub_431860(v7, Buffer, 1);
      v22 = -1;
      sub_4922F0(v16);
      v9 = (char *)sub_44B6C0(284);
      v10 = (int)v9;
      v22 = 1;
      if ( v9 != nullptr )
      {
        sub_44E0D0(v9, v8, 1);
        *(uint32_t *)v10 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v10 = 0;
      }
      v22 = -1;
      if ( a4 != 0 || v19 == 0 )
      {
        sub_45FE80(v4[29], (int)v4, 2, 0, v10, v4[243], 1);
      }
      else
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 36))(v10) + 8) = 2;
        sub_45FE80(v4[29], (int)v4, 2, 0, v10, 0, 0);
      }
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 148))(v10, v4[252], a3, a2);
      v11 = *(uint32_t *)v10;
      if ( a4 != 0 )
      {
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4[243] + 192))(v4[243]) / 2;
        v12 = (*(int (/*thiscall*/ **)(int *))(*v4 + 128))(v4);
        v4 = a1;
        a2 = v12 + v18;
        v13 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
      }
      else
      {
        a2 = (*(int (/*thiscall*/ **)(int *))(*v4 + 128))(v4);
        v13 = (*(int (/*thiscall*/ **)(int *))(*v4 + 124))(v4);
      }
      a3 = (*(int (/*thiscall*/ **)(int *, int))(*v4 + 120))(v4, v13);
      (*(void (/*thiscall*/ **)(int))(v11 + 112))(v10);
      result = ++v19;
    }
    while ( v19 < 3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x611400 CNBodyHit__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ sub_611400(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  char v12; // bl
  double v13; // st7
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // edi
  int v19; // ebx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  double v24; // st7
  int v25; // ecx
  int v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  int v31; // edx
  int v32; // [esp-Ch] [ebp-50h]
  float v33; // [esp+4h] [ebp-40h] BYREF
  float v34; // [esp+8h] [ebp-3Ch]
  float v35; // [esp+Ch] [ebp-38h]
  int v36; // [esp+10h] [ebp-34h]
  int v37; // [esp+14h] [ebp-30h]
  int v38; // [esp+18h] [ebp-2Ch]
  float v39; // [esp+1Ch] [ebp-28h] BYREF
  float v40; // [esp+20h] [ebp-24h]
  float v41; // [esp+24h] [ebp-20h] BYREF
  int v42; // [esp+28h] [ebp-1Ch]
  int v43; // [esp+2Ch] [ebp-18h]
  int v44; // [esp+30h] [ebp-14h]
  int v45; // [esp+34h] [ebp-10h] BYREF
  int v46; // [esp+40h] [ebp-4h]

  sub_600890();
  v2 = *(this + 243);
  if ( v2 == 0 )
    goto LABEL_46;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 840))(v2) != 4
    || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 952))(*(this + 243)) == 2 )
  {
    if ( *((uint8_t *)this + 996) == 0 )
      return;
LABEL_46:
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    return;
  }
  if ( *(this + 251) != 0 )
    return;
  v3 = *this;
  v4 = *(this + 243);
  v5 = *(uint32_t *)v4;
  v45 = v4;
  v6 = (*(int (**)(void))(v5 + 128))();
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 124))(v4, v6);
  v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 120))(v4, v7);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v8);
  v9 = *this;
  v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 152))(*(this + 243));
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 148))(this, v10);
  if ( *((uint8_t *)this + 996) == 0 )
  {
    *(this + 252) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    if ( *(this + 246) == -1 )
      *(this + 246) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243));
    *((uint8_t *)this + 996) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) > 0 )
    *((uint8_t *)this + 997) = 1;
  if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 200))(*(this + 243)) != 0 )
  {
    v11 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 200))(*(this + 243));
    if ( *(uint32_t *)(v11 + 148) != *(this + 250) )
    {
      sub_4938F0(*(this + 30));
      v32 = sub_42F220(v11) + 72;
      sub_42F220(*(this + 30));
      sub_492E80(v32);
      *(this + 250) = *(uint32_t *)(v11 + 148);
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 308))(*(this + 243)) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 184) == 4
      && (*(this + 244) != 0 || *(this + 247) != 0) )
    {
      sub_6111A0(1);
      v12 = 0;
      if ( *(this + 247) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
        v13 = (double)(int)*(this + 247);
        v14 = *(this + 243);
        v39 = 0.0;
        *((float *)this + 97) = v13;
        v40 = 0.0;
        v41 = 0.0;
        v42 = 0;
        v43 = 0;
        v44 = 0;
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 120))(v14);
        v16 = *(this + 243);
        v45 = v15;
        v39 = (float)v15;
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 124))(v16);
        v18 = *(this + 243);
        v45 = v17;
        v40 = (float)v17;
        v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 192))(v18) / 2;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 128))(v18);
        v21 = *(this + 243);
        v45 = v20 + v19;
        v41 = (float)(v20 + v19);
        sub_4E5F70(v20 + v19, (int)this, v21, &v39, 1, 0);
        v12 = 1;
      }
      if ( *(this + 244) != 0
        && ((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) >= *(this + 246)
         || *(float *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 24) >= 0.0) )
      {
        v42 = 0;
        v43 = 0;
        v44 = 0;
        v22 = *this;
        v46 = 0;
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(v22 + 152))(this);
        v45 = sub_432E50(v23);
        sub_431230((int)&v41, &v45);
        v45 = 0;
        sub_431230((int)&v41, &v45);
        v45 = 1;
        sub_431230((int)&v41, &v45);
        sub_431230((int)&v41, this + 245);
        sub_431230((int)&v41, this + 244);
        (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 243) + 560))(
          *(this + 243),
          4,
          &v41,
          2,
          0);
        v46 = -1;
        sub_5E5260((void **)&v41);
LABEL_24:
        sub_611200(1);
        return;
      }
      if ( v12 != 0 )
        goto LABEL_24;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) == 0
           && *(this + 248) != 0
           && *((uint8_t *)this + 997) != 0 )
    {
      sub_6111A0(1);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
      v24 = (double)(int)*(this + 248);
      v25 = *(this + 243);
      v33 = 0.0;
      *((float *)this + 97) = v24;
      v34 = 0.0;
      v35 = 0.0;
      v36 = 0;
      v37 = 0;
      v38 = 0;
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 120))(v25);
      v27 = *(this + 243);
      v45 = v26;
      v33 = (float)v26;
      v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 124))(v27);
      v29 = *(this + 243);
      v45 = v28;
      v34 = (float)v28;
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 128))(v29);
      v31 = *(this + 243);
      v45 = v30;
      v35 = (float)v30;
      sub_4E5F70(v3, (int)this, v31, &v33, 1, 0);
      sub_611200(0);
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != *(this + 252)
         && (*(this + 244) != 0 || *(this + 247) != 0) )
  {
    sub_6111A0(1);
    if ( *(this + 247) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
      *((float *)this + 97) = (float)(int)*(this + 247);
    }
    if ( *(this + 244) != 0
      && ((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) >= *(this + 246)
       || *(float *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 60))(*(this + 243)) + 24) >= 0.0) )
    {
      goto LABEL_24;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 243) + 128))(*(this + 243)) == 0
         && *(this + 248) != 0
         && *((uint8_t *)this + 997) != 0 )
  {
    sub_6111A0(1);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152);
    *((float *)this + 97) = (float)(int)*(this + 248);
    sub_611200(0);
  }
}


// ------------------------------------------------------------
// 0x611980 sub_611980
// ------------------------------------------------------------
int /*thiscall*/ sub_611980(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint8_t *)(this + 994) = 0;
  *(uint8_t *)(this + 1021) = 0;
  *(uint8_t *)(this + 1022) = 0;
  *(uint8_t *)(this + 1049) = 0;
  *(uint8_t *)(this + 1050) = 0;
  *(uint8_t *)(this + 1077) = 0;
  *(uint8_t *)(this + 1078) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6119C0 sub_6119C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6119C0(void **this)
{
  if ( *(this + 244) != nullptr )
    j__free(*(this + 244));
  *(this + 244) = nullptr;
}



// ------------------------------------------------------------
// 0x6119F0 sub_6119F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6119F0(uint8_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  const void *v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // esi
  int v12; // esi
  int v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // [esp+4h] [ebp-74h]
  int v19; // [esp+8h] [ebp-70h] BYREF
  int v20; // [esp+Ch] [ebp-6Ch] BYREF
  uint32_t v21[26]; // [esp+10h] [ebp-68h] BYREF

  v21[25] = dword_796E50;
  sub_423A20((int)v21);
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 88))(this);
    if ( (uint8_t)result != 0 && *(this + 264) != 1 )
    {
      v3 = sub_45EBE0(*((uint32_t **)this + 29), *((uint32_t *)this + 273), *((uint32_t *)this + 274));
      v4 = __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
      v5 = *(uint32_t *)this;
      v18 = v4;
      if ( v4 != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 60))(this);
        v7 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104));
        v8 = *(uint32_t *)this;
        qmemcpy(v21, v7, 0x62u);
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(v8 + 120))(this);
        v9 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
        v10 = *(uint32_t *)this;
        v20 = v9;
        v11 = (*(int (/*thiscall*/ **)(uint8_t *))(v10 + 128))(this);
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v19, v20, 0) != 0
          || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint8_t *, int *, int *, int, int, int, int, int))(*(uint32_t *)this + 140))(
                                this,
                                &v19,
                                &v20,
                                v19,
                                v20,
                                100,
                                1,
                                1)) != 0 )
        {
          v21[18] = (uint64_t)((double (/*thiscall*/ *)(uint8_t *, int, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(
                                        this,
                                        v18,
                                        0);
          *(uint32_t *)((char *)&v21[3] + 3) = *((uint32_t *)this + 276);
          *(uint32_t *)((char *)&v21[4] + 3) = *(uint32_t *)((char *)&v21[3] + 3);
          v21[0] = v19;
          v21[1] = v20;
          v21[2] = v11;
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
          v12 = *(uint32_t *)dword_8F8520;
          v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);
          (*(void (/*thiscall*/ **)(int, int))(v12 + 36))(dword_8F8520, v13);
          v14 = *(uint32_t *)dword_8F8520;
          v15 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
          (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v21, 98);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      else
      {
        v16 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 60))(this);
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v16 + 104) + 16))(*(uint32_t *)(v16 + 104)) + 15) = 0;
        v17 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 60))(this);
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v17 + 104) + 16))(*(uint32_t *)(v17 + 104)) + 19) = 0;
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)result == 1 )
          return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x611BF0 CNTrackingIceWave__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNTrackingIceWave__vmt2BC(int *this, const void *a2, size_t Size)
{
  CNRDPassiveObject__vmt2BC((int)a2, Size);
  qmemcpy(this + 273, a2, 0x1Cu);
  sub_698F90((int)(this + 245), *(this + 275), 0);
  return (*(int (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x611C40 CNTrackingIceWave__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNTrackingIceWave__vmt214(uint8_t *this, int a2, int a3, int a4)
{
  sub_6119F0(this);
  return CNRDPassiveObject__vmt214(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x611C70 CNTrackingIceWave__vmt14C
// ------------------------------------------------------------
void /*usercall*/ sub_611C70(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  unsigned int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  unsigned int i; // edi
  int v19; // ecx
  int v20; // edi
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  void *v27; // ecx
  uint32_t *v28; // edi
  int v29; // ebx
  uint32_t *v30; // eax
  int v31; // edi
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  void *v36; // ecx
  int v37; // eax
  int v38; // eax
  void *v41; // [esp+4h] [ebp-44h] BYREF
  void *v42; // [esp+8h] [ebp-40h]
  int v43; // [esp+Ch] [ebp-3Ch]
  int v44; // [esp+10h] [ebp-38h]
  uint8_t v45[4]; // [esp+14h] [ebp-34h] BYREF
  void *v46; // [esp+18h] [ebp-30h]
  int v47; // [esp+1Ch] [ebp-2Ch]
  int v48; // [esp+20h] [ebp-28h]
  uint8_t v49[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  uint32_t *v51; // [esp+2Ch] [ebp-1Ch]
  int v52; // [esp+30h] [ebp-18h]
  int v53; // [esp+34h] [ebp-14h]
  float v54; // [esp+38h] [ebp-10h]
  int v55; // [esp+44h] [ebp-4h]

  if ( *((uint8_t *)a1 + 264) != 1 )
  {
    sub_600890();
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) == 1
      && (v4 = a1[251], sub_699000((int)(a1 + 245)) >= v4) )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
    }
    else
    {
      v5 = sub_699000((int)(a1 + 245));
      if ( v5 >= 0x1F4 )
      {
        v6 = a1[275];
        if ( v5 <= v6 - 3000 )
        {
          v54 = 0.5;
        }
        else
        {
          v53 = v6 - v5;
          v54 = (double)(v6 - v5) * 0.00016666666;
        }
      }
      else
      {
        v53 = v5;
        v54 = (double)v5 * 0.001;
      }
      v7 = a1[258];
      if ( sub_699000((int)(a1 + 252)) >= v7 )
      {
        Block = nullptr;
        v51 = nullptr;
        v52 = 0;
        v8 = a1[36];
        v55 = 0;
        if ( v8 != 0 )
          v9 = (a1[37] - v8) >> 2;
        else
          v9 = 0;
        if ( a1[243] == v9 )
        {
          v10 = *a1;
          a1[243] = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v10 + 212))(
            a1,
            "ICEWAVE_CREATE",
            -1,
            0,
            0);
        }
        v11 = a1[243];
        if ( *(uint32_t *)(a1[244] + 4 * v11) == 0 )
        {
          sub_4926A0(*(uint32_t *)(a1[36] + 4 * v11));
          sub_4923C0(*(uint32_t **)(a1[36] + 4 * a1[243]), SLODWORD(v54));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*a1 + 204))(
            a1,
            0,
            *(uint32_t *)(a1[36] + 4 * a1[243]),
            0,
            0,
            0,
            1);
          *(uint32_t *)(a1[244] + 4 * a1[243]) = 1;
          v12 = dword_8F82A4;
          v13 = *(uint32_t *)dword_8F82A4;
          v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
          v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v14);
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v15);
          (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(v12, v16);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v12 + 12))(v12, 0);
          v17 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)v12 + 92))(v12, &v41);
          LOBYTE(v55) = 1;
          sub_4E77D0((int)v49, v17);
          LOBYTE(v55) = 0;
          sub_5E5260(&v41);
          sub_4600B0((void *)a1[29], 2, 0, (int)v49);
          ++a1[243];
          *((uint8_t *)a1 + 1021) = 0;
          *((uint8_t *)a1 + 1022) = 0;
          sub_698F90((int)(a1 + 252), a1[277], 0);
        }
        v55 = -1;
        if ( Block != nullptr )
          j__free(Block);
      }
      for ( i = 0; ; ++i )
      {
        v19 = a1[36];
        v53 = i;
        if ( v19 == 0 || i >= (a1[37] - v19) >> 2 )
          break;
        if ( *(uint32_t *)(a1[244] + 4 * i) == 1 && *(uint8_t *)(*(uint32_t *)(a1[36] + 4 * i) + 170) == 1 )
        {
          Block = nullptr;
          v51 = nullptr;
          v52 = 0;
          v20 = dword_8F82A8;
          v21 = *a1;
          v22 = *(uint32_t *)dword_8F82A8;
          v55 = 2;
          v23 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v21 + 128))(a1, a2, a3);
          v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v23 + 20);
          v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v24);
          (*(void (/*thiscall*/ **)(int, int))(v22 + 40))(v20, v25);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
          v26 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v20 + 92))(v20, v45);
          LOBYTE(v55) = 3;
          sub_4E77D0((int)v49, v26);
          LOBYTE(v55) = 2;
          if ( v46 != nullptr )
            j__free(v46);
          v27 = (void *)a1[29];
          v46 = nullptr;
          v47 = 0;
          v48 = 0;
          sub_4600B0(v27, 2, 0, (int)v49);
          v28 = Block;
          if ( Block != v51 )
          {
            v29 = LODWORD(v54);
            do
            {
              v30 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v28 + 200))(*v28);
              sub_4923C0(v30, v29);
              ++v28;
            }
            while ( v28 != v51 );
          }
          v31 = dword_8F82AC;
          v32 = *(uint32_t *)dword_8F82AC;
          a3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1) + 20;
          v33 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 124))(a1);
          v34 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v33);
          (*(void (/*thiscall*/ **)(int, int))(v32 + 40))(v31, v34);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v31 + 12))(v31, 0);
          v35 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)v31 + 92))(v31, &v41);
          LOBYTE(v55) = 4;
          sub_4E77D0((int)v49, v35);
          LOBYTE(v55) = 2;
          if ( v42 != nullptr )
            j__free(v42);
          v36 = (void *)a1[29];
          v42 = nullptr;
          v43 = 0;
          v44 = 0;
          sub_4600B0(v36, 2, 0, (int)v49);
          i = v53;
          a2 = *(uint32_t *)(a1[36] + 4 * v53);
          (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 208))(a1);
          *(uint32_t *)(a1[244] + 4 * i) = 0;
          v55 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v51 = nullptr;
          v52 = 0;
        }
      }
      v53 = a1[272];
      v37 = sub_699000((int)(a1 + 266));
      if ( v37 >= v53 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 352))(a1);
        *((uint8_t *)a1 + 1077) = 0;
        *((uint8_t *)a1 + 1078) = 0;
        sub_698F90((int)(a1 + 266), a1[278], 0);
      }
      v53 = a1[265];
      v38 = sub_699000((int)(a1 + 259));
      if ( v38 >= v53 )
      {
        sub_6119F0(a1);
        *((uint8_t *)a1 + 1049) = 0;
        *((uint8_t *)a1 + 1050) = 0;
        sub_698F90((int)(a1 + 259), a1[279], 0);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x6120F0 sub_6120F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6120F0(int this, int a2)
{
  int v3; // ecx
  char *v4; // ebx
  int v5; // eax
  unsigned int v6; // edi
  void *v7; // eax
  uint32_t *v8; // eax
  int (/*thiscall*/ ***v9)(void *, int); // esi
  char *v10; // eax
  const void *v11; // esi
  int v12; // esi
  uint32_t *v13; // edi
  int v14; // edi
  int v15; // edi
  int v17; // [esp+0h] [ebp-24h]
  int v18; // [esp+10h] [ebp-14h]
  int (/*thiscall*/ ***Block)(void *, int); // [esp+14h] [ebp-10h]

  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 1;
  v3 = *(uint32_t *)(this + 144);
  v4 = nullptr;
  v18 = this;
  if ( v3 != 0 )
    v5 = (*(uint32_t *)(this + 148) - v3) >> 2;
  else
    v5 = 0;
  v6 = 4 * v5;
  v7 = operator new(4 * v5);
  *(uint32_t *)(this + 976) = v7;
  memset(v7, 0, v6);
  v8 = operator new(0x12Cu);
  if ( v8 != nullptr )
  {
    v9 = (int (/*thiscall*/ ***)(void *, int))sub_428F30(
                                              v8,
                                              (int)"PassiveObject/Monster/Soldier/Particle/IceWaveMovePath.ptl",
                                              0);
    Block = v9;
  }
  else
  {
    Block = nullptr;
    v9 = nullptr;
  }
  v10 = (char *)sub_445D00(156);
  if ( v10 != nullptr )
    v4 = sub_445B90(v10);
  v11 = (const void *)((int (/*thiscall*/ *)(int (/*thiscall*/ ***)(void *, int)))(*v9)[7])(v9);
  qmemcpy((void *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v4 + 16))(v4), v11, 0x62u);
  v12 = v18;
  v13 = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v4 + 16))(v4);
  *v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 120))(v18);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v4 + 16))(v4) + 4) = v14;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 128))(v12);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v4 + 16))(v4) + 8) = v15;
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v12 + 60))(v12, v4);
  sub_4A0B60(v17);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v4 + 4))(v4, 0);
  return (**Block)(Block, 1);
}



// ------------------------------------------------------------
// 0x612250 sub_612250
// ------------------------------------------------------------
int /*thiscall*/ sub_612250(uint32_t *this)
{
  *(this + 253) = 1065353216;
  *(this + 254) = 1065353216;
  return 1065353216;
}



// ------------------------------------------------------------
// 0x612270 sub_612270
// ------------------------------------------------------------
char /*thiscall*/ sub_612270(int this, int a2)
{
  *(float *)(this + 724) = (float)a2;
  return sub_607260((uint32_t *)(this + 992), 300, -1, 1, 1);
}



// ------------------------------------------------------------
// 0x6122A0 CNSingleIceWave__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNSingleIceWave__vmt2BC(float *this, uint16_t *a2, int Size)
{
  int result; // eax
  uint16_t v6; // di
  unsigned int i; // edi
  int v8; // ecx
  int v9; // edx
  double v10; // st7
  float Sizea; // [esp+18h] [ebp+Ch]

  result = CNRDPassiveObject__vmt2BC((int)a2, Size);
  dword_78FE30 = (int)a2;
  dword_78FE34 = 0;
  if ( Size > 0 )
  {
    v6 = *a2;
    dword_78FE34 = 2;
    Sizea = (double)v6 * 0.0099999998;
    *(this + 253) = Sizea;
    sub_4922F0(Sizea);
    for ( i = 0; ; ++i )
    {
      v8 = *((uint32_t *)this + 36);
      if ( v8 == 0 || i >= (*((uint32_t *)this + 37) - v8) >> 2 )
        break;
      sub_4922F0(*(this + 253));
    }
    result = dword_78FE34;
    if ( dword_78FE34 < Size )
    {
      v9 = *(uint32_t *)(dword_78FE34 + dword_78FE30);
      dword_78FE34 += 4;
      v10 = *(float *)(result + 4 + dword_78FE30);
      dword_78FE34 = result + 8;
      *((uint32_t *)this + 190) = v9;
      *((uint32_t *)this + 193) = (uint64_t)v10;
      return (*(int (/*fastcall*/ **)(float *, uint32_t, float *))(*(uint32_t *)this + 344))(
               this,
               (uint64_t)v10 >> 32,
               this + 181);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x612390 CNSingleIceWave__vmt14C
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_612390(int *this)
{
  int v2; // ecx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  unsigned int v7; // ecx
  int v8; // edi
  int v9; // edi
  float v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  uint32_t *v22; // edi
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  void *v29; // ecx
  int v30; // eax
  uint32_t *v31; // ecx
  uint32_t *result; // eax
  float v33; // [esp+0h] [ebp-40h]
  float v34; // [esp+0h] [ebp-40h]
  uint8_t v35[4]; // [esp+10h] [ebp-30h] BYREF
  void *Block; // [esp+14h] [ebp-2Ch]
  int v37; // [esp+18h] [ebp-28h]
  int v38; // [esp+1Ch] [ebp-24h]
  uint8_t v39[4]; // [esp+20h] [ebp-20h] BYREF
  void *v40; // [esp+24h] [ebp-1Ch]
  uint32_t *v41; // [esp+28h] [ebp-18h]
  int v42; // [esp+2Ch] [ebp-14h]
  int v43; // [esp+30h] [ebp-10h]
  int v44; // [esp+3Ch] [ebp-4h]

  sub_600890();
  if ( *(this + 247) == 0 )
  {
    v2 = *(uint32_t *)(*(this + 28) + 104);
    v3 = 100;
    if ( v2 != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 16))(v2);
      v3 = (uint64_t)sub_4049C0(200.0, 50.0, *(uint32_t *)(v4 + 15) - 100, 900);
      v43 = 200 / v3;
      *((float *)this + 254) = (float)(200 / v3);
    }
    sub_607260(v3, -1, 1, 1);
  }
  v5 = sub_699000((int)(this + 9));
  if ( (uint8_t)sub_6072C0(v5) != 0 )
  {
    v6 = *(this + 36);
    if ( v6 != 0 )
      v7 = (*(this + 37) - v6) >> 2;
    else
      v7 = 0;
    v33 = *((float *)this + 254) * 100.0;
    v8 = *(uint32_t *)(*(this + 36) + 4 * (*(this + 247) % v7));
    sub_493D00(v8, v33);
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 1, v8, 0, 0, 0, 0);
    v40 = nullptr;
    v41 = nullptr;
    v42 = 0;
    v9 = dword_8F82A4;
    v10 = *(float *)this;
    v44 = 0;
    v11 = *(uint32_t *)dword_8F82A4;
    v12 = (*(int (/*thiscall*/ **)(int *))(LODWORD(v10) + 128))(this);
    v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v12);
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 40))(v9, v14);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v9 + 12))(v9, 0);
    v15 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v9 + 92))(v9, v35);
    LOBYTE(v44) = 1;
    sub_4E77D0((int)v39, v15);
    LOBYTE(v44) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v39);
    if ( *(this + 247) != 0 )
    {
      v16 = dword_8F82A8;
      v17 = *(uint32_t *)dword_8F82A8;
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v18 + 20);
      v20 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v19);
      (*(void (/*thiscall*/ **)(int, int))(v17 + 40))(v16, v20);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v16 + 12))(v16, 0);
      v21 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v16 + 92))(v16, v35);
      LOBYTE(v44) = 2;
      sub_4E77D0((int)v39, v21);
      LOBYTE(v44) = 0;
      if ( Block != nullptr )
        j__free(Block);
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v39);
      v22 = v40;
      if ( v40 != v41 )
      {
        do
        {
          v34 = *((float *)this + 253);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v22 + 200))(*v22);
          sub_4922F0(v34);
          ++v22;
        }
        while ( v22 != v41 );
      }
      v23 = dword_8F82AC;
      v24 = *(uint32_t *)dword_8F82AC;
      v25 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v26 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v25 + 20);
      v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v26);
      (*(void (/*thiscall*/ **)(int, int))(v24 + 40))(v23, v27);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v23 + 12))(v23, 0);
      v28 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v23 + 92))(v23, v35);
      LOBYTE(v44) = 3;
      sub_4E77D0((int)v39, v28);
      LOBYTE(v44) = 0;
      if ( Block != nullptr )
        j__free(Block);
      v29 = (void *)*(this + 29);
      Block = nullptr;
      v37 = 0;
      v38 = 0;
      sub_4600B0(v29, 2, 0, (int)v39);
    }
    v44 = -1;
    if ( v40 != nullptr )
      j__free(v40);
    v40 = nullptr;
    v41 = nullptr;
    v42 = 0;
  }
  v30 = sub_699000((int)(this + 9));
  if ( (uint8_t)sub_6072C0(v30) != 0 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ICEWAVE_CREATE", -1, 0, 0);
  v31 = (uint32_t *)*(this + 32);
  result = (uint32_t *)*v31;
  if ( (uint32_t *)*v31 != v31 )
  {
    while ( *(uint8_t *)(result[3] + 170) == 0 )
    {
      result = (uint32_t *)*result;
      if ( result == (uint32_t *)*(this + 32) )
        return result;
    }
    return (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, result[3]);
  }
  return result;
}


// ------------------------------------------------------------
// 0x6126D0 sub_6126D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6126D0(int this)
{
  *(uint32_t *)(this + 1100) = 0;
  *(uint32_t *)(this + 1104) = 0;
  *(uint32_t *)(this + 1108) = 0;
  *(uint8_t *)(this + 1125) = 0;
  *(uint8_t *)(this + 1126) = 0;
  *(uint8_t *)(this + 1140) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x612700 sub_612700
// ------------------------------------------------------------
int /*thiscall*/ sub_612700(int *this, int a2)
{
  int v3; // eax
  int result; // eax

  if ( a2 == 833 )
  {
    v3 = *this;
    *(this + 275) = 1;
    result = (*(int (/*stdcall*/ **)(int))(v3 + 384))(8);
    *(this + 277) = result;
  }
  else
  {
    *(this + 275) = 0;
    *(this + 277) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x612750 CNEventBarrier__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNEventBarrier__vmt200(int *this, int a2, float *a3, char a4)
{
  return CNRDPassiveObject__vmt200(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x612770 CNEventBarrier__vmt14C
// ------------------------------------------------------------
char /*usercall*/ sub_612770@<al>(uint8_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  unsigned int i; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  uint32_t *v15; // eax
  uint8_t *v16; // eax
  int v17; // edi
  int v18; // eax
  int v20; // [esp-20h] [ebp-24h]
  int v21; // [esp-1Ch] [ebp-20h]
  int v22; // [esp-18h] [ebp-1Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 316))(a1) == 1 )
  {
    LOBYTE(v3) = sub_60B6B0(a1);
    return v3;
  }
  if ( a1[1140] == 1 )
  {
    if ( *((uint32_t *)a1 + 275) == 1 )
      v4 = 500;
    else
      v4 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 384))(a1, 8);
    sub_698F90((int)(a1 + 1112), v4, 0);
    a1[1140] = 0;
  }
  v3 = *((uint32_t *)a1 + 276);
  if ( v3 != 0 )
  {
    if ( v3 == 1 )
    {
      v17 = *((uint32_t *)a1 + 284);
      v3 = sub_699000((int)(a1 + 1112));
      if ( v3 >= v17 )
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1);
        if ( (uint8_t)v3 == 1 )
        {
          v22 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1) - 10;
          v21 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 124))(a1);
          v20 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 120))(a1);
          v18 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 384))(a1);
          sub_4E4A50(a1, 40008, v18, 9, v20, v21, v22, 4, 0, 0);
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0, 0);
          *((uint32_t *)a1 + 276) = 2;
        }
      }
    }
  }
  else
  {
    v3 = *((uint32_t *)a1 + 275);
    if ( v3 == 0 )
    {
      v5 = *((uint32_t *)a1 + 284);
      v3 = sub_699000((int)(a1 + 1112));
      if ( v3 < v5 )
        return v3;
LABEL_11:
      *((uint32_t *)a1 + 276) = 1;
      a1[1125] = 0;
      a1[1126] = 0;
      v6 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t))(*(uint32_t *)a1 + 384))(a1, 7, 0);
      sub_698F90((int)(a1 + 1112), v6, a2);
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)a1 + 196))(a1, **((uint32_t **)a1 + 36));
      return v3;
    }
    if ( v3 == 1 )
    {
      v7 = *((uint32_t *)a1 + 284);
      v3 = sub_699000((int)(a1 + 1112));
      if ( v3 >= v7 )
      {
        for ( i = 0; ; ++i )
        {
          v9 = *((uint32_t *)a1 + 29);
          v10 = *(uint32_t *)(v9 + 8);
          v11 = v9 + 4;
          v12 = v10 != 0 ? (*(uint32_t *)(v11 + 8) - v10) >> 2 : 0;
          if ( (int)i >= v12 )
            break;
          v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 80))(a1);
          v14 = *(uint32_t *)(v13 + 8);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 12) - v14) >> 2 )
            v15 = *(uint32_t **)(v14 + 4 * i);
          else
            v15 = nullptr;
          v16 = __RTDynamicCast(
                  v15,
                  0,
                  &CNRDObject `RTTI Type Descriptor',
                  &CNRDPassiveObject `RTTI Type Descriptor',
                  0);
          if ( v16 != a1
            && v16 != nullptr
            && *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v16 + 340))(v16) == *((uint32_t *)a1 + 277) )
          {
            a1[1125] = 0;
            a1[1126] = 0;
            LOBYTE(v3) = sub_698F90((int)(a1 + 1112), 500, 0);
            return v3;
          }
        }
        goto LABEL_11;
      }
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x6129A0 sub_6129A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6129A0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint8_t *)(this + 980) = 0;
  *(uint8_t *)(this + 981) = 0;
  *(uint8_t *)(this + 982) = 0;
  *(uint32_t *)(this + 984) = 1065353216;
  *(uint8_t *)(this + 988) = 0;
  *(uint8_t *)(this + 989) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6129E0 CNIceWave__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNIceWave__vmt2A8(int this, int a2)
{
  int v3; // eax
  char *v4; // edi
  int v5; // ebx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v10; // [esp-18h] [ebp-1Ch]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  LOBYTE(v3) = *(uint8_t *)(this + 989);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x15u);
    v5 = sub_47EF20(v4, 0, *(uint32_t *)(this + 976), -1, -1, 11);
    v6 = v5 - *(uint32_t *)(sub_4924C0(0) + 48);
    *(uint32_t *)(sub_4924C0(1) + 48) = v6;
    if ( *(uint32_t *)(this + 972) >= sub_47EF20(v4, 1u, *(uint32_t *)(this + 976), -1, -1, 11) - 1 )
      *(uint8_t *)(this + 980) = 1;
    v7 = sub_47EF20(v4, 4u, *(uint32_t *)(this + 976), -1, -1, 11);
    v10 = *(uint32_t *)(this + 976);
    *(float *)(this + 760) = (double)v7 * 0.1;
    *(uint32_t *)(this + 772) = (uint64_t)(double)sub_47EF20(v4, 5u, v10, -1, -1, 11);
    if ( dword_795BE0 == -1 )
      dword_795BE0 = sub_47E9D0(v4, 0);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    v3 = sub_47EFD0(v4, COERCE_FLOAT(3), *(uint32_t *)(this + 976), v8, v8, 0);
    *(uint8_t *)(this + 989) = 1;
    *(float *)(this + 724) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x612B10 sub_612B10
// ------------------------------------------------------------
int /*thiscall*/ sub_612B10(int this, int a2)
{
  uint16_t v3; // cx
  int v5; // [esp+Ch] [ebp+8h]
  float v6; // [esp+Ch] [ebp+8h]

  v3 = a2;
  v5 = a2 >> 16;
  *(uint32_t *)(this + 972) = v5;
  *(uint32_t *)(this + 976) = v3;
  v6 = (double)v5 * 0.050000001 + 1.0;
  *(float *)(this + 984) = v6;
  sub_4922F0(v6);
  return sub_4015C0("G_ICEWAVE_MOVING", 0x10u);
}



// ------------------------------------------------------------
// 0x612B70 CNIceWave__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ sub_612B70(int *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint32_t *v11; // edi
  uint32_t *v12; // eax
  double v13; // st7
  int v14; // ebx
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  float v19; // edx
  int v20; // ebx
  int v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // edi
  void *v25; // ecx
  uint32_t *v26; // edi
  uint32_t *v27; // eax
  int v28; // ebx
  int v29; // edi
  int v30; // eax
  int v31; // eax
  int v32; // edi
  int v33; // eax
  void *v34; // ecx
  void *v35; // eax
  bool v36; // zf
  int result; // eax
  float v38; // [esp-4h] [ebp-58h]
  float v39; // [esp-4h] [ebp-58h]
  uint8_t v40[4]; // [esp+Ch] [ebp-48h] BYREF
  void *v41; // [esp+10h] [ebp-44h]
  int v42; // [esp+14h] [ebp-40h]
  int v43; // [esp+18h] [ebp-3Ch]
  uint8_t v44[4]; // [esp+1Ch] [ebp-38h] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  uint32_t *v46; // [esp+24h] [ebp-30h]
  uint8_t v47[4]; // [esp+2Ch] [ebp-28h] BYREF
  void *v48; // [esp+30h] [ebp-24h]
  uint32_t *v49; // [esp+34h] [ebp-20h]
  int v50; // [esp+38h] [ebp-1Ch]
  int v51; // [esp+3Ch] [ebp-18h]
  int v52; // [esp+40h] [ebp-14h]
  int v53; // [esp+44h] [ebp-10h]
  int v54; // [esp+50h] [ebp-4h]

  sub_600890();
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v2 + 136))(this, v4) != 0 )
  {
    if ( *((uint8_t *)this + 981) == 0 )
    {
      v5 = dword_8F82A4;
      v6 = *(uint32_t *)dword_8F82A4;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(v5, v9);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v5 + 92))(v5, v44);
      v10 = (void *)*(this + 29);
      v54 = 0;
      sub_4600B0(v10, 2, 0, (int)v44);
      v11 = Block;
      if ( Block != v46 )
      {
        do
        {
          v38 = *((float *)this + 246);
          v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v11 + 200))(*v11);
          sub_4922F0(v12, v38);
          ++v11;
        }
        while ( v11 != v46 );
        v11 = Block;
      }
      *((uint8_t *)this + 981) = 1;
      v54 = -1;
      if ( v11 != nullptr )
        j__free(v11);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    *((uint8_t *)this + 988) = 1;
  }
  if ( *((uint8_t *)this + 988) == 0 )
  {
    if ( *(this + 243) == 0 )
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ICEWAVE_CREATE", -1, 0, 0);
    *((uint8_t *)this + 988) = 1;
  }
  if ( *((uint8_t *)this + 980) == 0 && sub_699000((int)(this + 16)) >= dword_795BE0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      v53 = *(this + 71) + 1;
      if ( v53 == 20008 )
        v53 = 20002;
      v13 = (double)*(this + 243) * -0.80000001;
      v51 = *(this + 244) | ((uint16_t)(*((uint16_t *)this + 486) + 1) << 16);
      v14 = 14 - (uint64_t)v13;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v15 = v14 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      else
        v15 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v14;
      if ( *(this + 243) % 2 != 0 )
        v16 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - 8;
      else
        v16 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + 8;
      v52 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      sub_4E4A50(v15, *(this + 173), v53, v51, v15, v16, v52, v17, 0, 0, 0);
    }
    *((uint8_t *)this + 980) = 1;
  }
  if ( *((uint8_t *)this + 982) == 0 )
  {
    v18 = *(this + 30);
    if ( v18 != 0 && *(int *)(v18 + 148) >= 3 )
    {
      v19 = *(float *)this;
      v20 = *(uint32_t *)dword_8F82A8;
      v53 = dword_8F82A8;
      v21 = (*(int (/*thiscall*/ **)(int *))(LODWORD(v19) + 128))(this);
      v22 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(
              this,
              20 - (uint64_t)((double)*(this + 243) * -1.5) + v21);
      v23 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v22);
      v24 = v53;
      (*(void (/*thiscall*/ **)(int, int))(v20 + 40))(v53, v23);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v24 + 12))(v24, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v24 + 92))(v24, v47);
      v25 = (void *)*(this + 29);
      v54 = 1;
      sub_4600B0(v25, 2, 0, (int)v47);
      v26 = v48;
      if ( v48 != v49 )
      {
        do
        {
          v39 = *((float *)this + 246);
          v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v26 + 200))(*v26);
          sub_4922F0(v27, v39);
          ++v26;
        }
        while ( v26 != v49 );
      }
      v28 = *(uint32_t *)dword_8F82AC;
      v53 = dword_8F82AC;
      v29 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v30 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(
              this,
              20 - (uint64_t)((double)*(this + 243) * -1.5) + v29);
      v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v30);
      v32 = v53;
      (*(void (/*thiscall*/ **)(int, int))(v28 + 40))(v53, v31);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v32 + 12))(v32, 0);
      v33 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v32 + 92))(v32, v40);
      LOBYTE(v54) = 2;
      sub_4E77D0((int)v47, v33);
      LOBYTE(v54) = 1;
      if ( v41 != nullptr )
        j__free(v41);
      v34 = (void *)*(this + 29);
      v41 = nullptr;
      v42 = 0;
      v43 = 0;
      sub_4600B0(v34, 2, 0, (int)v47);
      v35 = v48;
      v36 = v48 == nullptr;
      *((uint8_t *)this + 982) = 1;
      v54 = -1;
      if ( !v36 )
        j__free(v35);
      v48 = nullptr;
      v49 = nullptr;
      v50 = 0;
    }
  }
  result = *(this + 30);
  if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x612F70 sub_612F70
// ------------------------------------------------------------
int /*thiscall*/ sub_612F70(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 1065353216;
  *(uint8_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x612F90 CNBodyHit__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBodyHit__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( a2 == *(this + 243) )
    *(this + 243) = 0;
}



// ------------------------------------------------------------
// 0x612FC0 CNSuplexSub__vmt2BC
// ------------------------------------------------------------
char /*thiscall*/ CNSuplexSub__vmt2BC(uint8_t *this, uint8_t *a2, size_t Size)
{
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // edx
  char *v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v15; // [esp+10h] [ebp+8h]
  float Sizea; // [esp+14h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v4 = *(uint32_t *)this;
  *(this + 976) = *a2;
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 684))(this);
  v6 = __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
  v7 = v6;
  if ( v6 != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 1332))(v6);
    v9 = *(uint32_t *)this;
    *((uint32_t *)this + 243) = v8;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v9 + 356))(this, v8);
    LOBYTE(v6) = *(this + 976);
    if ( (uint8_t)v6 != 0 )
    {
      v10 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 1160))(v7, 22);
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 1140))(v7, 22);
      Sizea = (double)sub_47EF20(v10, 0, v15, -1, -1, 11) * 0.0099999998;
      *((float *)this + 245) = Sizea;
      sub_4922F0(Sizea);
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 388))(v7);
      v12 = sub_47EFD0(v10, COERCE_FLOAT(1), v15, v11, v11, 0);
      v13 = *(uint32_t *)this;
      *((float *)this + 181) = (double)v12 + *((float *)this + 181);
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *))(v13 + 344))(this, this + 724);
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x6130C0 CNSuplexSub__vmt14C
// ------------------------------------------------------------
int /*usercall*/ sub_6130C0@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  char *v17; // eax
  char *v18; // edi
  int v19; // ebx
  int v20; // eax
  uint64_t v21; // rax
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // ebx
  char *v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // ebx
  int v34; // ecx
  int v35; // ebx
  char *v36; // eax
  int v37; // edi
  int v38; // ebx
  int v39; // eax
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int result; // eax
  int v47; // [esp+18h] [ebp-10h]
  float v48; // [esp+18h] [ebp-10h]

  sub_600890();
  if ( *(uint8_t *)(a1 + 984) == 0 )
  {
    if ( *(uint32_t *)(a1 + 284) == 21001 )
    {
      v4 = sub_42FCB0(228);
      v5 = 0;
      if ( v4 != 0 )
        v5 = sub_431860(v4, "Character/Fighter/Effect/Animation/SuplexDust.ani", 1);
      sub_4922F0(*(float *)(a1 + 980));
      off_77F3FC("SIZE RATE %f", *(float *)(a1 + 980));
      v6 = (char *)sub_44B6C0(284);
      v7 = v6;
      if ( v6 != nullptr )
      {
        sub_44E0D0(v6, v5, 1);
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = nullptr;
      }
      v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 684))(a1, 0);
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v7, 2, 0, (int)v7, v8, a3);
      v9 = *(uint32_t *)v7;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(char *, int))(v9 + 148))(v7, v10);
      v11 = *(uint32_t *)v7;
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v12);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v13);
    }
    else
    {
      v15 = sub_42FCB0(228);
      if ( v15 != 0 )
        v16 = sub_431860(v15, "Character/Fighter/Effect/Animation/JumpSuplexCrashUnder.ani", 1);
      else
        v16 = 0;
      sub_4922F0(*(float *)(a1 + 980));
      v17 = (char *)sub_44B6C0(284);
      v18 = v17;
      if ( v17 != nullptr )
      {
        sub_44E0D0(v17, v16, 1);
        *(uint32_t *)v18 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v18 = nullptr;
      }
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v18, 2, 0, (int)v18, 0, 0);
      v19 = *(uint32_t *)v18;
      v20 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 152))(a1, a3, a2);
      (*(void (/*thiscall*/ **)(char *, int))(v19 + 148))(v18, v20);
      v21 = (uint64_t)(*(float *)(sub_4924C0(0) + 24) * 10.0);
      v22 = *(uint32_t *)v18;
      v47 = v21;
      v23 = (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 128))(a1, HIDWORD(v21));
      v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v23);
      v25 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v24 - v47);
      (*(void (/*thiscall*/ **)(char *, int))(v22 + 112))(v18, v25);
      v26 = sub_42FCB0(228);
      if ( v26 != 0 )
        v27 = sub_431860(v26, "Character/Fighter/Effect/Animation/JumpSuplexCrashOver.ani", 1);
      else
        v27 = 0;
      sub_4922F0(*(float *)(a1 + 980));
      v28 = (char *)sub_44B6C0(284);
      v7 = v28;
      if ( v28 != nullptr )
      {
        sub_44E0D0(v28, v27, 1);
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = nullptr;
      }
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v7, 2, 0, (int)v7, 0, 0);
      v29 = *(uint32_t *)v7;
      v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(char *, int))(v29 + 148))(v7, v30);
      v11 = *(uint32_t *)v7;
      v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v32 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v31);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v47 + v32);
    }
    (*(void (/*thiscall*/ **)(char *, int))(v11 + 112))(v7, v14);
    if ( *(uint8_t *)(a1 + 976) != 0 )
    {
      v33 = *(uint32_t *)(a1 + 120);
      if ( *(uint32_t *)(v33 + 148) == -1 )
        sub_4938F0(*(uint32_t *)(a1 + 120));
      v48 = *(float *)(*(uint32_t *)(v33 + 120) + 12) * 0.0024999999;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( *(uint32_t *)(a1 + 384) < 0x10u )
          LOBYTE(v34) = a1 + 108;
        else
          v34 = *(uint32_t *)(a1 + 364);
        v35 = sub_431920(v34, (char)"Animation/PoweredSuplexSub.ani", 1);
      }
      else
      {
        v35 = 0;
      }
      sub_4922F0(v48);
      v36 = (char *)sub_44B6C0(284);
      v37 = (int)v36;
      if ( v36 != nullptr )
      {
        sub_44E0D0(v36, v35, 1);
        *(uint32_t *)v37 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v37 = 0;
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v37 + 36))(v37) + 8) = 2;
      sub_45FE80(*(uint32_t *)(a1 + 116), v37, 2, 0, v37, 0, 0);
      v38 = *(uint32_t *)v37;
      v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(int, int))(v38 + 148))(v37, v39);
      v40 = *(uint32_t *)v37;
      v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v41);
      v43 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v42);
      (*(void (/*thiscall*/ **)(int, int))(v40 + 112))(v37, v43);
    }
    *(uint8_t *)(a1 + 984) = 1;
  }
  result = *(uint32_t *)(a1 + 120);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
  return result;
}


// ------------------------------------------------------------
// 0x6134D0 CNEnergyBall__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNEnergyBall__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v4; // eax
  int *v6; // edi
  int v7; // eax
  int v9; // [esp-1Ch] [ebp-28h]
  int v10; // [esp-18h] [ebp-24h]
  int v11; // [esp-14h] [ebp-20h]
  int v12; // [esp+8h] [ebp-4h] BYREF

  v4 = *a2;
  v12 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(a2, &v12, this);
  if ( a4 == 0 && v12 > 0 && *((uint8_t *)this + 972) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
    {
      v6 = this;
      if ( *(this + 173) != 0 )
        v6 = (int *)*(this + 173);
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      sub_4E4A50(v6, 21003, *(this + 176), v7, v9, v10, v11, 0, 0, 0);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x613590 sub_613590
// ------------------------------------------------------------
int /*stdcall*/ sub_613590(int a1)
{
  uint32_t *v1; // eax
  float v3; // [esp+Ch] [ebp+8h]

  v1 = (uint32_t *)sub_47E720(1, 0xCu);
  v3 = (double)sub_47EF20(v1, 4u, a1, -1, -1, 11) * 0.0099999998;
  sub_4922F0(v3);
  return sub_4015C0("NEN_BEGIN", 9u);
}



// ------------------------------------------------------------
// 0x6135F0 CNThrowSand__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNThrowSand__vmt2A8(int *this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax

  CNRDPassiveObject__vmt2A8(this, a2);
  LOBYTE(v3) = *((uint8_t *)this + 973);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(1, 0xDu);
    v5 = *(this + 176);
    v6 = v4;
    *((float *)this + 190) = (double)sub_47EF20(v4, 0, v5, -1, -1, 11) * 0.1;
    v7 = sub_47EF20(v6, 1u, v5, -1, -1, 11);
    v8 = *this;
    *(this + 193) = v7;
    v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(2), v5, v9, v9, 0);
    *((uint8_t *)this + 973) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x613690 CNThrowSand__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNThrowSand__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SAND_DROP", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x6136C0 CNThrowSand__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNThrowSand__vmt14C(uint8_t *this)
{
  char result; // al
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  bool v9; // cc
  uint8_t v10[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v12; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  result = *(this + 972);
  if ( result == 0 )
  {
    v14 = 0;
    do
    {
      v3 = dword_8F82C0[v14 != 0];
      v4 = *(uint32_t *)v3;
      v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
      v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v5);
      v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v6);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 40))(v3, v7);
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) == 0;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 28))(v3) + 84) = v4;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v3 + 12))(v3, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v3 + 92))(v3, v10);
      v8 = *((void **)this + 29);
      v15 = 0;
      sub_4600B0(v8, 2, 0, (int)v10);
      v15 = -1;
      if ( Block != nullptr )
        j__free(Block);
      result = v14 + 1;
      v9 = v14 + 1 < 2;
      Block = nullptr;
      v12 = 0;
      v13 = 0;
      ++v14;
    }
    while ( v9 );
    *(this + 972) = 1;
  }
  if ( *(uint8_t *)(*((uint32_t *)this + 30) + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x6137D0 sub_6137D0
// ------------------------------------------------------------
int sub_6137D0()
{
  return sub_4015C0("SAND_SPREAD", 0xBu);
}



// ------------------------------------------------------------
// 0x6137F0 sub_6137F0
// ------------------------------------------------------------
void /*thiscall*/ sub_6137F0(uint8_t *this)
{
  *(this + 992) = 0;
}



// ------------------------------------------------------------
// 0x613800 CNEnergyField__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNEnergyField__vmt2A8(int this, int a2)
{
  char result; // al
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // [esp+4h] [ebp-4h]
  int v10; // [esp+10h] [ebp+8h]
  float v11; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  result = *(uint8_t *)(this + 992);
  if ( result == 0 )
  {
    v4 = sub_47E720(1, 0x10u);
    v5 = *(uint32_t *)(this + 704);
    v6 = (char *)v4;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    *(float *)(this + 724) = (float)sub_47EFD0(v6, 0.0, v5, v7, v7, 0);
    *(float *)(this + 760) = (double)sub_47EF20(v6, 1u, v5, -1, -1, 11) * 0.1;
    *(uint32_t *)(this + 772) = sub_47EF20(v6, 2u, v5, -1, -1, 11);
    v9 = sub_47EF20(v6, 3u, v5, -1, -1, 11);
    if ( v9 <= 1 )
    {
      sub_607260((uint32_t *)(this + 972), 0, 0, 1, 1);
    }
    else
    {
      v10 = sub_491C70(*(uint32_t *)(this + 136), 2);
      v8 = sub_491C70(*(uint32_t *)(this + 136), 13);
      sub_607260((uint32_t *)(this + 972), (v8 - v10) / v9, v9 - 1, 0, 0);
      sub_607290((uint8_t *)(this + 972), v10);
    }
    v11 = (double)sub_47EF20(v6, 4u, v5, -1, -1, 11) * 0.0099999998;
    sub_4920E0(*(uint32_t **)(this + 136), v11, v11);
    result = sub_4921E0(v11);
    *(uint8_t *)(this + 992) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x613960 CNEnergyField__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNEnergyField__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 30);
  v3 = *(uint32_t *)(v2 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(v2 + 32);
  if ( sub_6072C0((uint8_t *)this + 972, v4) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  v5 = __RTDynamicCast(
         *(this + 173),
         0,
         &IRDCollisionObject `RTTI Type Descriptor',
         &CNFighter `RTTI Type Descriptor',
         0);
  if ( v5 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 840))(v5) != 10 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x6139F0 sub_6139F0
// ------------------------------------------------------------
int sub_6139F0()
{
  return sub_4015C0("ENERGY_EXPLOTION", 0x10u);
}



// ------------------------------------------------------------
// 0x613A10 sub_613A10
// ------------------------------------------------------------
int /*thiscall*/ sub_613A10(int this)
{
  *(uint8_t *)(this + 992) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint32_t *)(this + 996) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x613A30 CNBlastBlood__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBlastBlood__vmt12C(int *this, int a2)
{
  int v3; // ecx
  int v4; // [esp-4h] [ebp-Ch]

  v3 = *(this + 249);
  if ( a2 == v3 )
  {
    v4 = v3;
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 1160))(24);
    sub_47DD30(v4);
    *(this + 249) = 0;
  }
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x613A70 CNBlastBlood__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNBlastBlood__vmt14C(uint8_t *this)
{
  int v2; // eax
  int v3; // eax
  int *v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int result; // eax
  int v9; // ecx
  int v10; // [esp-8h] [ebp-Ch]
  int v11; // [esp-4h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 993) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 684))(this);
    v3 = __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    *((uint32_t *)this + 249) = v3;
    if ( v3 != 0 )
    {
      v10 = v3;
      v4 = (int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1160))(v3, 24);
      sub_47DCD0(v4, v10, 20000);
    }
    *(this + 993) = 1;
  }
  v5 = *((uint32_t *)this + 30);
  v6 = *(uint32_t *)(v5 + 212);
  if ( v6 != 0 )
    v7 = sub_4910A0(v6);
  else
    v7 = *(uint32_t *)(v5 + 32);
  if ( sub_6072C0(this + 972, v7) != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 352))(this);
  if ( *(int *)(**((uint32_t **)this + 36) + 148) >= 8 && *(this + 992) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "FIRE_PILLAR_UP",
      -1,
      0,
      0);
    *(this + 992) = 1;
  }
  result = *((uint32_t *)this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    v9 = *((uint32_t *)this + 249);
    if ( v9 != 0 )
    {
      v11 = *((uint32_t *)this + 249);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v9 + 1160))(24);
      return sub_47DD30(v11);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x613B70 sub_613B70
// ------------------------------------------------------------
int /*thiscall*/ sub_613B70(void *this, int a2)
{
  uint32_t *v3; // ebx
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  float v8; // edx
  int result; // eax
  uint32_t *v10; // [esp+8h] [ebp+8h]

  *((float *)this + 181) = (float)a2;
  v3 = (uint32_t *)sub_47E720(0, 0x18u);
  v10 = v3;
  v4 = sub_47E9D0(v3, 0);
  if ( v4 > 1 )
  {
    v5 = sub_491C70(*((uint32_t *)this + 34), 1);
    v6 = sub_491C70(*((uint32_t *)this + 34), 4);
    sub_607260((uint32_t *)this + 243, (v6 - v5) / v4, v4 - 1, 0, 0);
    sub_607290((uint8_t *)this + 972, v5);
    v3 = v10;
  }
  v7 = sub_47E9D0(v3, 1u);
  v8 = *(float *)this;
  *((uint32_t *)this + 198) = v7;
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v8) + 204))(
    this,
    1,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    2,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    -1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 8),
    0,
    0,
    0,
    0);
  result = sub_4015C0("BLOOD_CIRCLE_CREATE", 0x13u);
  *((uint8_t *)this + 992) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x613C80 CNBlastBloodSub__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNBlastBloodSub__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 30);
  v3 = *(uint32_t *)(v2 + 212);
  if ( v3 != 0 )
    v4 = sub_4910A0(v3);
  else
    v4 = *(uint32_t *)(v2 + 32);
  if ( sub_6072C0((uint8_t *)this + 972, v4) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x613CE0 sub_613CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_613CE0(int this, int a2)
{
  uint32_t *v3; // ebx
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int result; // eax
  uint32_t *v8; // [esp+8h] [ebp+8h]

  *(float *)(this + 724) = (float)a2;
  v3 = (uint32_t *)sub_47E720(0, 0x18u);
  v8 = v3;
  v4 = sub_47E9D0(v3, 0);
  if ( v4 > 1 )
  {
    v5 = sub_491C70(*(uint32_t *)(this + 136), 1);
    v6 = sub_491C70(*(uint32_t *)(this + 136), 4);
    sub_607260((uint32_t *)(this + 972), (v6 - v5) / v4, v4 - 1, 0, 0);
    sub_607290((uint8_t *)(this + 972), v5);
    v3 = v8;
  }
  result = sub_47E9D0(v3, 2u);
  *(uint32_t *)(this + 792) = result;
  return result;
}



// ------------------------------------------------------------
// 0x613D70 CNBlastBloodSub__vmt1F4
// ------------------------------------------------------------
int /*userpurge*/ CNBlastBloodSub__vmt1F4@<eax>(int *a1@<ecx>, int a2@<ebx>, uint32_t *a3, float *a4, char a5)
{
  uint32_t *v5; // esi
  int v7; // eax
  int v8; // ebx
  const char *v9; // ecx
  char *v10; // eax
  int v11; // esi
  int v12; // eax
  const char *v13; // ecx
  int v14; // ebx
  char *v15; // eax
  int v16; // esi
  int v18; // [esp+Ch] [ebp-14h]
  int v19; // [esp+10h] [ebp-10h]

  v5 = a3;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 128))(a3) == 0 && a5 == 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 120))(a3, a2);
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 124))(a3);
    v7 = sub_42FCB0(228);
    v8 = 0;
    if ( v7 != 0 )
    {
      if ( (unsigned int)a1[96] < 0x10 )
        v9 = (const char *)(a1 + 91);
      else
        v9 = (const char *)a1[91];
      v8 = sub_431920(v7, v9, "Animation/BlastBloodHit1.ani", 1);
    }
    v10 = (char *)sub_44B6C0(284);
    v11 = (int)v10;
    if ( v10 != nullptr )
    {
      sub_44E0D0(v10, v8, 1);
      *(uint32_t *)v11 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v11 = 0;
    }
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 36))(v11) + 8) = 2;
    sub_45FE80(a1[29], (int)a1, 2, 0, v11, 0, 0);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v11 + 112))(v11, v18, v19, 0);
    v12 = sub_42FCB0(228);
    if ( v12 != 0 )
    {
      if ( (unsigned int)a1[96] < 0x10 )
        v13 = (const char *)(a1 + 91);
      else
        v13 = (const char *)a1[91];
      v14 = sub_431920(v12, v13, "Animation/BlastBloodHit2.ani", 1);
    }
    else
    {
      v14 = 0;
    }
    v15 = (char *)sub_44B6C0(284);
    v16 = (int)v15;
    if ( v15 != nullptr )
    {
      sub_44E0D0(v15, v14, 1);
      *(uint32_t *)v16 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v16 = 0;
    }
    sub_45FE80(a1[29], (int)a1, 2, 0, v16, (int)a1, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v16 + 112))(v16, v18, v19);
    v5 = a3;
  }
  return CNRDPassiveObject__vmt1F4(a1, v5, a4, a5);
}



// ------------------------------------------------------------
// 0x613F40 sub_613F40
// ------------------------------------------------------------
int /*thiscall*/ sub_613F40(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1048) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x613F90 CNGhost__vmtC
// ------------------------------------------------------------
float */*thiscall*/ CNGhost__vmtC(int *this)
{
  float *result; // eax

  result = CNRDPassiveObject__vmtC(this);
  if ( *(this + 243) == 36 )
    return (float *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x613FB0 sub_613FB0
// ------------------------------------------------------------
char /*thiscall*/ sub_613FB0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // ebx
  char result; // al

  v3 = *(this + 243);
  if ( v3 == 25 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    if ( v4 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      return 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, a2, 0) < *(this + 248);
  }
  if ( v3 != 41 )
  {
    if ( v3 == 36
      && ((uint8_t)sub_4E4630(a2) == 0
       || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 624))(a2) == 0
       || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2) > *(this + 262)) )
    {
      return 0;
    }
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, a2, 0) < *(this + 248);
  }
  result = sub_4E4630(a2);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, a2, 0) < *(this + 248);
  return result;
}



// ------------------------------------------------------------
// 0x614050 sub_614050
// ------------------------------------------------------------
bool /*thiscall*/ sub_614050(uint32_t *this, int a2)
{
  int v2; // edx
  int v3; // eax

  v2 = *(uint32_t *)(a2 + 64);
  v3 = *(this + 243);
  if ( v3 == 25 )
    return v2 == 13;
  else
    return v2 == (v3 != 41 ? 56 : 14);
}



// ------------------------------------------------------------
// 0x614090 sub_614090
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614090(uint32_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *this = &vftbl_CNBremenAppendage;
  sub_652220(this);
  sub_652400(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x6140F0 CNBremenAppendage__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNBremenAppendage__vmt0(void *Block, char a2)
{
  sub_614120();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x614120 sub_614120
// ------------------------------------------------------------
int /*thiscall*/ sub_614120(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNBremenAppendage;
  sub_603910((uint32_t *)this);
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x614180 sub_614180
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614180(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax
  int *v5; // ecx
  int *v6; // eax

  v3 = (int *)*(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
  {
    if ( *a3 >= (unsigned int)v4[3] )
    {
      v4 = (int *)v4[2];
    }
    else
    {
      v3 = v4;
      v4 = (int *)*v4;
    }
  }
  v5 = (int *)*(this + 1);
  v6 = (int *)v5[1];
  while ( *((uint8_t *)v6 + 21) == 0 )
  {
    if ( (unsigned int)v6[3] >= *a3 )
    {
      v5 = v6;
      v6 = (int *)*v6;
    }
    else
    {
      v6 = (int *)v6[2];
    }
  }
  *a2 = v5;
  a2[1] = v3;
  return a2;
}



// ------------------------------------------------------------
// 0x6141F0 CNGhost__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNGhost__vmt10(int this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  double v5; // st7
  int v6; // edi
  int i; // edi
  int result; // eax
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-8h] [ebp-14h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  v2 = *(uint32_t *)(this + 988);
  v3 = 180;
  if ( v2 == 0 )
  {
    v4 = *(uint32_t *)(this + 976);
    v9 = sub_699000(this + 36);
    v5 = sub_4049C0(0.0, 180.0, v9, v4);
LABEL_5:
    v3 = (uint64_t)v5;
    goto LABEL_6;
  }
  if ( v2 == 2 )
  {
    v6 = *(uint32_t *)(this + 984) - *(uint32_t *)(this + 980);
    v10 = sub_699000(this + 36) - *(uint32_t *)(this + 980);
    v5 = sub_4049C0(180.0, 0.0, v10, v6);
    goto LABEL_5;
  }
LABEL_6:
  for ( i = 0; i < 8; i += 4 )
  {
    sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 144) + i));
    result = sub_491F80(-1, -1, -1, v3, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6142A0 sub_6142A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6142A0(int *this, int a2)
{
  int result; // eax
  int v3; // ebx
  unsigned int i; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  result = *(this + 243);
  if ( result == 25 || result == 41 )
  {
    v3 = result == 25 ? 13 : result != 41 ? 56 : 14;
    if ( a2 != 0 )
    {
      for ( i = 0; ; ++i )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v6 = *(uint32_t *)(v5 + 4);
        result = v6 != 0 ? (*(uint32_t *)(v5 + 8) - v6) >> 2 : 0;
        if ( (int)i >= result )
          break;
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v8 = *(uint32_t *)(v7 + 4);
        if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
          v9 = *(uint32_t *)(v8 + 4 * i);
        else
          v9 = 0;
        if ( *(uint32_t *)(v9 + 4) == a2 )
        {
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v11 = *(uint32_t *)(v10 + 4);
          if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
            v12 = *(uint32_t *)(v11 + 4 * i);
          else
            v12 = 0;
          if ( *(int **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 64))(v12) + 32) == this )
          {
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
            v14 = *(uint32_t *)(v13 + 4);
            if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
            {
              v15 = *(uint32_t **)(v14 + 4 * i);
              if ( v15 != nullptr && v15[16] == v3 )
                return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6143B0 sub_6143B0
// ------------------------------------------------------------
char /*thiscall*/ sub_6143B0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // esi
  int v9; // eax

  v3 = *(this + 243);
  if ( v3 == 25 )
  {
    v4 = __RTDynamicCast(a2, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);
    v5 = v4;
    if ( v4 == 0 )
      return 0;
    v6 = *(uint32_t *)(v4 + 84);
    if ( v6 != 0 && (*(uint32_t *)(v5 + 88) - v6) / 12 != 0 )
      v7 = *(uint32_t *)(v5 + 84);
    else
      v7 = 0;
    if ( (double)(int)*(this + 255) > *(float *)(v7 + 8) )
      return 0;
  }
  else if ( v3 == 41 )
  {
    v9 = __RTDynamicCast(a2, 0, &IRDAppendage `RTTI Type Descriptor', &CNBremenAppendage `RTTI Type Descriptor', 0);
    if ( v9 == 0 || *(uint32_t *)(v9 + 84) < *(this + 257) )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x614460 sub_614460
// ------------------------------------------------------------
int /*thiscall*/ sub_614460(float *this, unsigned int a2, int a3)
{
  uint32_t *v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  float v7; // edx
  int v8; // ecx
  uint32_t *v9; // eax
  int v11; // [esp+Ch] [ebp-4h]

  *((uint32_t *)this + 243) = a2;
  v4 = (uint32_t *)sub_47E720(0, a2);
  v5 = v4;
  if ( a2 == 25 )
  {
    *((uint32_t *)this + 255) = sub_47EF20(v4, 0, a3, -1, -1, 11);
    *((uint32_t *)this + 256) = sub_47EF20(v5, 2u, a3, -1, -1, 11);
    sub_607260((uint32_t *)this + 250, 100, -1, 1, 1);
  }
  else if ( a2 == 36 )
  {
    *(this + 190) = (double)sub_47EF20(v4, 2u, a3, -1, -1, 11) * 0.1;
    *((uint32_t *)this + 193) = sub_47EF20(v5, 3u, a3, -1, -1, 11);
    v11 = sub_47E9D0(v5, 3u);
    *((uint32_t *)this + 262) = sub_47E9D0(v5, 2u);
    sub_607260((uint32_t *)this + 250, v11, -1, 1, 1);
  }
  else
  {
    if ( a2 == 41 )
    {
      *((uint32_t *)this + 257) = sub_47EF20(v4, 0, a3, -1, -1, 11);
      *((uint32_t *)this + 258) = sub_47EF20(v5, 2u, a3, -1, -1, 11);
    }
    sub_607260((uint32_t *)this + 250, 250, -1, 1, 1);
  }
  *((uint32_t *)this + 248) = sub_47E9D0(v5, 1u);
  *((uint32_t *)this + 246) = sub_47EF20(v5, 1u, a3, -1, -1, 11);
  *((uint32_t *)this + 244) = sub_491C10(*(uint32_t *)(*((uint32_t *)this + 36) + 12));
  v6 = sub_491C10(*(uint32_t *)(*((uint32_t *)this + 36) + 20));
  v7 = *this;
  v8 = *((uint32_t *)this + 246) - v6;
  v9 = *((uint32_t **)this + 36);
  *((uint32_t *)this + 245) = v8;
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v7) + 204))(
    this,
    2,
    *v9,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 8),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    2,
    *(uint32_t *)(*((uint32_t *)this + 36) + 12),
    0,
    0,
    0,
    1);
  return sub_4015C0("G_GHOST_CIRCLE", 0xEu);
}



// ------------------------------------------------------------
// 0x614660 sub_614660
// ------------------------------------------------------------
int */*thiscall*/ sub_614660(int **this, int *a2, char a3, int *a4, int a5)
{
  int v6; // ecx
  int *v7; // eax
  int *v8; // eax
  int v9; // eax
  int *v10; // eax
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )
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
  v7 = *(this + 1);
  v21 = v6;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);
  if ( a4 == v7 )
  {
    v7[1] = v6;
    **(this + 1) = v6;
    (*(this + 1))[2] = v6;
  }
  else if ( a3 != 0 )
  {
    *a4 = v6;
    v8 = *(this + 1);
    if ( a4 == (int *)*v8 )
      *v8 = v6;
  }
  else
  {
    a4[2] = v6;
    v9 = (int)*(this + 1);
    if ( a4 == *(int **)(v9 + 8) )
      *(uint32_t *)(v9 + 8) = v6;
  }
  v10 = (int *)(v6 + 4);
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
            sub_433130(this, *v10);
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
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 20) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x614810 sub_614810
// ------------------------------------------------------------
int /*thiscall*/ sub_614810(int **this, int a2, int *a3)
{
  int *v3; // ebx
  int *v5; // esi
  int v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  int *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = *(this + 1);
  v6 = v5[1];
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *a3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      v5 = (int *)v6;
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == (int *)**(this + 1) )
    {
      v10 = *sub_614660(this, (int *)&a3, 1, v5, (int)v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_4A3B30(&a3);
    v9 = a3;
  }
  if ( v9[3] >= (unsigned int)*v3 )
  {
    *(uint8_t *)(a2 + 4) = 0;
    *(uint32_t *)a2 = v9;
    return a2;
  }
  else
  {
    v12 = *sub_614660(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x6148D0 sub_6148D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6148D0(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t *v6; // [esp+Ch] [ebp-8h] BYREF
  uint32_t *v7; // [esp+10h] [ebp-4h]

  sub_614180(this, &v6, a2);
  v2 = v6;
  v3 = v7;
  v4 = 0;
  a2 = v6;
  if ( v6 != v7 )
  {
    do
    {
      ++v4;
      sub_41C5E0(&a2);
    }
    while ( a2 != v3 );
    v2 = v6;
  }
  sub_52E960(&a2, v2, v3);
  return v4;
}



// ------------------------------------------------------------
// 0x614930 sub_614930
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614930(int *this, int a2)
{
  uint32_t *result; // eax
  uint8_t v4[4]; // [esp+4h] [ebp-4h] BYREF

  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 || result == (uint32_t *)41 )
  {
    result = (uint32_t *)sub_4BE520(v4, &a2);
    if ( *result != *(this + 260) )
    {
      sub_6142A0(this, a2);
      return (uint32_t *)sub_6148D0(this + 259, &a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x614990 sub_614990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_614990(int *this, int a2)
{
  uint32_t *result; // eax
  uint32_t *v4; // esi
  uint32_t *v5; // ecx
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // eax
  float v9; // [esp+Ch] [ebp-1Ch]
  float v10; // [esp+Ch] [ebp-1Ch]

  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 )
  {
    if ( operator new(0x7Cu) != nullptr )
      v4 = (uint32_t *)sub_4B3C90(0, 1);
    else
      v4 = nullptr;
    v9 = (float)*(this + 255);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*v4 + 120))(v4, 0, 0, LODWORD(v9));
    v10 = (float)*(this + 256);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*v4 + 120))(v4, 1, 0, LODWORD(v10));
    v5 = v4;
  }
  else
  {
    if ( result != (uint32_t *)41 )
      return result;
    v6 = operator new(0x5Cu);
    if ( v6 != nullptr )
      result = sub_614090(v6, *(this + 257), *(this + 258));
    else
      result = nullptr;
    v5 = result;
  }
  if ( v5 != nullptr )
  {
    v7 = *(this + 243);
    if ( v7 == 25 )
      v8 = 13;
    else
      v8 = v7 != 41 ? 56 : 14;
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int *, uint32_t, uint32_t, int, int))(*v5 + 56))(
                       v5,
                       a2,
                       this,
                       0,
                       0,
                       v8,
                       -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x614AB0 CNGhost__vmt12C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNGhost__vmt12C(int *this, int a2)
{
  int v2; // edi
  uint32_t *result; // eax
  int *v5; // ecx

  v2 = a2;
  CNRDPassiveObject__vmt12C(this, a2);
  result = (uint32_t *)*(this + 243);
  if ( result == (uint32_t *)25 || result == (uint32_t *)41 )
  {
    if ( (int *)v2 == this )
    {
      v5 = (int *)*(this + 260);
      result = (uint32_t *)*v5;
      a2 = *v5;
      if ( (int *)a2 != v5 )
      {
        do
        {
          sub_6142A0(this, result[3]);
          sub_41C5E0(&a2);
          result = (uint32_t *)a2;
        }
        while ( a2 != *(this + 260) );
      }
    }
    else
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 17);
      if ( (uint8_t)result != 0 )
        return sub_614930(this, v2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x614B30 sub_614B30
// ------------------------------------------------------------
char /*thiscall*/ sub_614B30(int **this, int a2)
{
  int **v2; // ebx
  int v3; // eax
  int **v4; // eax
  int v5; // edi
  unsigned int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // esi
  int v16; // eax
  char v18[8]; // [esp+4h] [ebp-18h] BYREF
  int v19; // [esp+Ch] [ebp-10h] BYREF
  int v20; // [esp+10h] [ebp-Ch] BYREF
  int **v21; // [esp+14h] [ebp-8h]
  char v22; // [esp+1Bh] [ebp-1h]

  v2 = this;
  v3 = (int)*(this + 243);
  v21 = this;
  if ( v3 != 25 && v3 != 41 )
    return v3;
  v4 = (int **)sub_4BE520(&v20, &a2);
  v5 = a2;
  if ( *v4 == v2[260] )
  {
    v19 = a2;
    v20 = a2;
    sub_614810(v2 + 259, (int)v18, &v19);
  }
  HIBYTE(a2) = 0;
  v22 = 0;
  if ( v5 == 0 )
  {
LABEL_30:
    LOBYTE(v3) = (uint8_t)sub_614990((int *)v2, v5);
    return v3;
  }
  v6 = 0;
  while ( 1 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 700))(v5);
    v8 = *(uint32_t *)(v7 + 4);
    v9 = v8 != 0 ? (*(uint32_t *)(v7 + 8) - v8) >> 2 : 0;
    if ( (int)v6 >= v9 )
      break;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 700))(v5);
    v11 = *(uint32_t *)(v10 + 4);
    if ( v11 != 0 && v6 < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
      v12 = *(uint32_t *)(v11 + 4 * v6);
    else
      v12 = 0;
    if ( *(uint32_t *)(v12 + 4) == v5
      && (v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 700))(v5), (v14 = *(uint32_t *)(v13 + 4)) != 0)
      && v6 < (*(uint32_t *)(v13 + 8) - v14) >> 2
      && (v15 = *(uint32_t *)(v14 + 4 * v6)) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v15 + 80))(*(uint32_t *)(v14 + 4 * v6)) != 0
      && sub_614050(v21, v15) )
    {
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 64))(v15);
      if ( *(int ***)(v16 + 32) == v21 )
      {
        HIBYTE(a2) = 1;
        ++v6;
      }
      else
      {
        if ( sub_6143B0(v21, v15) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v15 + 76))(v15, 0);
          goto LABEL_26;
        }
        v22 = 1;
        ++v6;
      }
    }
    else
    {
LABEL_26:
      ++v6;
    }
  }
  LOBYTE(v3) = HIBYTE(a2);
  if ( HIBYTE(a2) == 0 )
  {
    LOBYTE(v3) = v22;
    if ( v22 == 0 )
    {
      v2 = v21;
      goto LABEL_30;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x614C90 CNGhost__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ sub_614C90(int *this)
{
  int v2; // eax
  char *v3; // edi
  int v4; // eax
  int v5; // eax
  unsigned int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // edi
  char v14; // bl
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int result; // eax
  float v21; // [esp+8h] [ebp-24h] BYREF
  float v22; // [esp+Ch] [ebp-20h]
  float v23; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int v27; // [esp+20h] [ebp-Ch]
  int v28; // [esp+24h] [ebp-8h]
  unsigned int v29; // [esp+28h] [ebp-4h]

  sub_600890();
  if ( *((uint8_t *)this + 996) == 0 )
  {
    v2 = *(this + 243);
    switch ( v2 )
    {
      case 25:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_KAJAN", -1, 0, 0);
        break;
      case 36:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_SAYA", -1, 0, 0);
        break;
      case 41:
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GHOST_BREMEN", -1, 0, 0);
        break;
      default:
        break;
    }
    if ( *(this + 243) == 36 )
    {
      v3 = (char *)sub_47E720(0, 36);
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
      v28 = sub_47EFD0(v3, 0.0, *(this + 176), v4, v4, 0);
      *((float *)this + 97) = (float)v28;
    }
    *((uint8_t *)this + 996) = 1;
  }
  v5 = *(this + 247);
  v6 = 0;
  if ( v5 != 0 )
  {
    if ( v5 == 1 && sub_699000((int)(this + 9)) >= *(this + 245) )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        2,
        *(uint32_t *)(*(this + 36) + 20),
        0,
        0,
        0,
        1);
      *(this + 247) = 2;
    }
  }
  else if ( sub_699000((int)(this + 9)) >= *(this + 244) )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
      this,
      2,
      *(uint32_t *)(*(this + 36) + 16),
      0,
      0,
      0,
      1);
    *(this + 247) = 1;
  }
  v7 = sub_699000((int)(this + 16));
  if ( (uint8_t)sub_6072C0(v7) != 0 )
  {
    v8 = *(this + 29);
    v9 = *(uint32_t *)(v8 + 120);
    v10 = v8 + 116;
    v28 = v9 != 0 ? (*(uint32_t *)(v10 + 8) - v9) >> 2 : 0;
    v29 = 0;
    if ( v28 > 0 )
    {
      while ( 1 )
      {
        v11 = *(this + 29);
        v12 = *(uint32_t *)(v11 + 120);
        if ( v12 != 0 && v6 < (*(uint32_t *)(v11 + 124) - v12) >> 2 )
          v13 = *(uint32_t *)(v12 + 4 * v6);
        else
          v13 = 0;
        v14 = sub_613FB0(v13);
        v15 = *(this + 243);
        if ( v15 == 25 || v15 == 41 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 40))(v13, 17) != 0 )
          {
            if ( v14 != 0 )
              sub_614B30(v13);
            else
              sub_614930(v13);
          }
        }
        else if ( v15 == 36 && v14 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 308))(v13) != 0 )
        {
          v16 = *(uint32_t *)v13;
          v21 = 0.0;
          v22 = 0.0;
          v23 = 0.0;
          v24 = 0;
          v25 = 0;
          v26 = 0;
          v17 = (*(int (/*thiscall*/ **)(int))(v16 + 120))(v13);
          v18 = *(uint32_t *)v13;
          v27 = v17;
          v21 = (float)v17;
          v27 = (*(int (/*thiscall*/ **)(int))(v18 + 124))(v13);
          v19 = *(uint32_t *)v13;
          v22 = (float)v27;
          v27 = (*(this + 262) - (*(int (/*thiscall*/ **)(int))(v19 + 128))(v13)) / 2;
          v23 = (float)v27;
          sub_4E5F70(v14, (int)this, v13, &v21, 1, 1);
        }
        if ( (int)++v29 >= v28 )
          break;
        v6 = v29;
      }
    }
  }
  result = sub_699000((int)(this + 9));
  if ( result >= *(this + 246) )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x614F90 sub_614F90
// ------------------------------------------------------------
int /*thiscall*/ sub_614F90(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 1065353216;
  *(uint8_t *)(this + 996) = 0;
  *(uint8_t *)(this + 997) = 0;
  *(uint8_t *)(this + 998) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x614FD0 sub_614FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_614FD0(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 244;
  for ( i = 4; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x615000 CNFireWave__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNFireWave__vmt2A8(int this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  float v9; // [esp+Ch] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  LOBYTE(v3) = *(uint8_t *)(this + 996);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x16u);
    v5 = *(uint32_t *)(this + 704);
    v6 = v4;
    v9 = (double)sub_47EF20(v4, 2u, v5, -1, -1, 11) * 0.0099999998;
    *(float *)(this + 992) = v9;
    sub_4921E0(v9);
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, v7, v7, 0);
    *(uint32_t *)(this + 972) = v3;
    *(uint8_t *)(this + 996) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x615090 CNFireWave__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNFireWave__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v4; // eax
  int v6; // edi
  int v7; // eax
  int v9; // [esp-18h] [ebp-24h]
  int v10; // [esp-14h] [ebp-20h]
  int v11; // [esp+8h] [ebp-4h] BYREF

  v4 = *a2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(a2, &v11, this);
  if ( a4 == 0
    && v11 > 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0
    && *((uint8_t *)this + 998) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 55;
      else
        v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 55;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 50;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      sub_4E4A50(*(this + 173), 40002, *(this + 243), v6, v7, v9, v10, 0, 0, 0);
    }
    *((uint8_t *)this + 998) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x615180 CNFireWave__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNFireWave__vmt14C(uint8_t *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // edx
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  float v8; // [esp-4h] [ebp-34h]
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 996) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "FIREWAVE_MOVING",
      0,
      0,
      0);
    *(this + 996) = 1;
  }
  v2 = 0;
  do
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 0 )
      v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) + 35;
    else
      v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) - 35;
    v4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
    v5 = *(uint32_t *)this;
    v13 = v4;
    v14 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 128))(this);
    if ( v2 == 2 )
    {
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 0 )
        v3 -= 40;
      else
        v3 += 40;
      v14 += 40;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**((uint32_t **)this + v2 + 244) + 40))(
      *((uint32_t *)this + v2 + 244),
      v3,
      v13,
      v14);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + v2 + 244) + 92))(*((uint32_t *)this + v2 + 244), v9);
    v6 = Block;
    v15 = 0;
    if ( Block != v11 )
    {
      do
      {
        v8 = *((float *)this + 248);
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 200))(*v6);
        sub_4920E0(v7, v8, v8);
        ++v6;
      }
      while ( v6 != v11 );
    }
    sub_4600B0(*((void **)this + 29), 2, 0, (int)v9);
    v15 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v2;
    Block = nullptr;
    v11 = nullptr;
    v12 = 0;
  }
  while ( v2 < 4 );
}



// ------------------------------------------------------------
// 0x6152E0 sub_6152E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6152E0(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v2 = sub_4C3640(this + 91, "Particle/FireWaveParticle.ptl", this);
    else
      v2 = sub_4C3640(*(this + 91), "Particle/FireWaveParticle.ptl", this);
  }
  else
  {
    v2 = 0;
  }
  *(this + 244) = v2;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v3 = sub_4C3640(this + 91, "Particle/FireWaveParticleTail.ptl", this);
    else
      v3 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleTail.ptl", this);
  }
  else
  {
    v3 = 0;
  }
  *(this + 245) = v3;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v4 = sub_4C3640(this + 91, "Particle/FireWaveParticleLight.ptl", this);
    else
      v4 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleLight.ptl", this);
  }
  else
  {
    v4 = 0;
  }
  *(this + 246) = v4;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v5 = sub_4C3640(this + 91, "Particle/FireWaveParticleFloor.ptl", this);
    else
      v5 = sub_4C3640(*(this + 91), "Particle/FireWaveParticleFloor.ptl", this);
  }
  else
  {
    v5 = 0;
  }
  *(this + 247) = v5;
  return sub_4015C0("FIREWAVE_CREATE", 0xFu);
}



// ------------------------------------------------------------
// 0x6154A0 sub_6154A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6154A0(int this)
{
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6154C0 sub_6154C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6154C0(uint32_t *this)
{
  *(this + 168) = 3;
}



// ------------------------------------------------------------
// 0x6154D0 CNSpiralNen__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNSpiralNen__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  v2 = sub_699000((int)(this + 16));
  if ( sub_6072C0((uint8_t *)this + 972, v2) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
  if ( (int)*(this + 170) <= 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  v3 = __RTDynamicCast(
         *(this + 173),
         0,
         &IRDCollisionObject `RTTI Type Descriptor',
         &CNFighter `RTTI Type Descriptor',
         0);
  v4 = v3;
  if ( v3 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 840))(v3);
  if ( result == 5 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( *(this + 167) != v4 )
    *(this + 167) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x615570 CNSpiralNen__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpiralNen__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // ecx
  int v6; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0 )
  {
    v5 = *(this + 249);
    v6 = *(this + 248) + 1;
    *(this + 248) = v6;
    if ( v5 == v6 )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x6155D0 CNSpiralNen__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNSpiralNen__vmt2A8(int this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  LOBYTE(v3) = *(uint8_t *)(this + 1000);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = sub_47E720(1, 0x28u);
    v5 = *(uint32_t *)(this + 704);
    v6 = (char *)v4;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
    *(float *)(this + 724) = (float)sub_47EFD0(v6, 0.0, v5, v7, v7, 0);
    *(float *)(this + 760) = (double)sub_47EF20(v6, 4u, v5, -1, -1, 11) * 0.1;
    *(uint32_t *)(this + 772) = sub_47EF20(v6, 5u, v5, -1, -1, 11);
    *(uint32_t *)(this + 996) = sub_47EF20(v6, 2u, v5, -1, -1, 11);
    v8 = sub_47E9D0(v6, 0);
    sub_607260((uint32_t *)(this + 972), v8, -1, 0, 0);
    *(uint32_t *)(this + 992) = 0;
    v3 = sub_47EF20(v6, 3u, v5, -1, -1, 11);
    *(uint32_t *)(this + 684) = v3;
    *(uint32_t *)(this + 680) = v3;
    *(uint8_t *)(this + 1000) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6156D0 sub_6156D0
// ------------------------------------------------------------
void /*thiscall*/ sub_6156D0(int this)
{
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
}



// ------------------------------------------------------------
// 0x615710 CNClosePunchSub__vmt160
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNClosePunchSub__vmt160(uint32_t *this)
{
  unsigned int result; // eax
  unsigned int i; // edi
  int v4; // ecx

  result = (unsigned int)IRDCollisionObject__vmt160(this);
  for ( i = 0; ; ++i )
  {
    v4 = *(this + 244);
    if ( v4 == 0 )
      break;
    result = (*(this + 245) - v4) >> 2;
    if ( i >= result )
      break;
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 356))(this, *(uint32_t *)(v4 + 4 * i));
  }
  return result;
}



// ------------------------------------------------------------
// 0x615760 CNClosePunchSub__vmt12C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNClosePunchSub__vmt12C(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  v3 = (uint32_t *)*(this + 245);
  result = (uint32_t *)*(this + 244);
  if ( result != v3 )
  {
    do
    {
      if ( *result == a2 )
        break;
      ++result;
    }
    while ( result != v3 );
    if ( result != v3 )
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 245) - (int)(result + 1)) >> 2));
      result = (uint32_t *)(*(this + 245) - 4);
      *(this + 245) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6157C0 CNClosePunchSub__vmt2A8
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNClosePunchSub__vmt2A8(uint32_t *this, int a2)
{
  unsigned int v3; // ebx
  unsigned int result; // eax
  unsigned int v5; // edi
  void *v6; // eax
  uint32_t *v7; // esi
  int v8; // ecx
  int *v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  int *v12; // eax
  int v13; // [esp+14h] [ebp+8h]

  CNRDPassiveObject__vmt2A8(this, a2);
  v3 = 0;
  result = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
  v5 = result;
  if ( result != 0 )
  {
    v6 = (void *)*(this + 244);
    v7 = this + 243;
    if ( v6 != nullptr )
      j__free(v6);
    v7[1] = 0;
    v7[2] = 0;
    v7[3] = 0;
    result = (*(int (/*thiscall*/ **)(unsigned int))(*(uint32_t *)v5 + 1336))(v5);
    v13 = result;
    while ( 1 )
    {
      v8 = *(uint32_t *)(result + 4);
      if ( v8 == 0 )
        break;
      result = (*(uint32_t *)(result + 8) - v8) >> 3;
      if ( v3 >= result )
        break;
      v9 = (int *)(v8 + 8 * v3);
      v10 = v7[1];
      if ( v10 != 0 )
        v11 = (v7[2] - v10) >> 2;
      else
        v11 = 0;
      if ( v10 != 0 && v11 < (v7[3] - v10) >> 2 )
      {
        v12 = (int *)v7[2];
        *v12 = *v9;
        v7[2] = v12 + 1;
        result = v13;
        ++v3;
      }
      else
      {
        sub_428220((int)v7, v7[2], 1u, v9);
        result = v13;
        ++v3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x615890 sub_615890
// ------------------------------------------------------------
int /*thiscall*/ sub_615890(int this, int a2)
{
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = a2;
  *(uint8_t *)(this + 988) = 0;
  *(uint8_t *)(this + 701) = 0;
  *(uint8_t *)(this + 700) = 0;
  *(uint32_t *)(this + 972) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6158C0 CNGunnerLaser__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGunnerLaser__vmt12C(int *this, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // [esp-4h] [ebp-Ch]

  v3 = *(this + 243);
  if ( a2 == v3 )
  {
    v5 = v3;
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 1160))(39);
    sub_47DD30(v5);
    *(this + 243) = 0;
  }
  if ( (int *)a2 == this )
  {
    v4 = *(this + 243);
    if ( v4 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 22 )
      sub_4C34F0(*(this + 245));
  }
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x615930 CNGunnerLaser__vmt14C
// ------------------------------------------------------------
int /*usercall*/ sub_615930@<eax>(float *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // eax
  int v6; // edi
  unsigned int v7; // eax
  int64_t v8; // rax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edi
  unsigned int v13; // edx
  int v14; // edi
  unsigned int v15; // ebx
  int v16; // edi
  char *v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int v21; // edi
  char *v22; // ebx
  int v23; // eax
  unsigned int v24; // eax
  int v25; // eax
  unsigned int v26; // eax
  int v27; // ecx
  int result; // eax
  int v29; // [esp-Ch] [ebp-14h]
  int v30; // [esp-4h] [ebp-Ch]

  sub_600890();
  if ( *((uint8_t *)a1 + 988) == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 684))(a1);
    v5 = __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
    *((uint32_t *)a1 + 243) = v5;
    if ( v5 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 1140))(v5, 41, a3, a2) > 0 )
      {
        v6 = *((uint32_t *)a1 + 243);
        v29 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v6 + 1140))(v6, 41, -1);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 1160))(v6);
        *((uint32_t *)a1 + 244) = sub_47EF20(41, 0, v29, -1, 11);
      }
      v7 = *((uint32_t *)a1 + 244);
      if ( v7 != 0 && *((uint32_t *)a1 + 245) >= v7 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 196))(a1, *(uint32_t *)(*((uint32_t *)a1 + 36) + 8));
        a1[246] = *(float *)(*((uint32_t *)a1 + 36) + 12);
        v30 = *((uint32_t *)a1 + 243);
        (*(void (**)(void))(*(uint32_t *)v30 + 1160))();
        sub_47DCD0(39, v30);
      }
      else
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 196))(a1, **((uint32_t **)a1 + 36));
        a1[246] = *(float *)(*((uint32_t *)a1 + 36) + 4);
      }
      if ( (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 152))(a1) != 0 )
      {
        v9 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)a1 + 29) + 132) + 44);
        v10 = *(uint32_t *)(v9 + 364);
        v11 = v9 + 360;
        if ( v10 != 0 )
          v12 = (*(uint32_t *)(v11 + 8) - v10) >> 5;
        else
          v12 = 0;
        v8 = 1374389535LL * (224 * v12 - (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 120))(a1));
      }
      else
      {
        v8 = 1374389535LL * (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 120))(a1);
      }
      v13 = SHIDWORD(v8) >> 4;
      if ( (int)(v13 + (v13 >> 31)) > 0 )
      {
        v14 = 0;
        v15 = v13 + (v13 >> 31);
        do
        {
          (*(void (/*thiscall*/ **)(float *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
            a1,
            0,
            *((uint32_t *)a1 + 246),
            v14,
            0,
            0,
            0);
          v14 += 50;
          --v15;
        }
        while ( v15 != 0 );
      }
      sub_4926A0(*((uint32_t *)a1 + 30));
      sub_4938F0(*((uint32_t *)a1 + 246));
      sub_4938F0(*((uint32_t *)a1 + 30));
      v16 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)a1 + 243) + 1140))(*((uint32_t *)a1 + 243), 39);
      v17 = (char *)sub_47E720(2, 39);
      v18 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)a1 + 243) + 388))(*((uint32_t *)a1 + 243));
      v19 = sub_47EFD0(v17, 0.0, v16, v18, v18, 0);
      v20 = *((uint32_t *)a1 + 243);
      a1[97] = (float)v19;
      v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 1140))(v20, 41);
      if ( v21 > 0 )
      {
        v22 = (char *)sub_47E720(2, 41);
        v23 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)a1 + 388))(a1);
        a1[97] = (double)((unsigned int)(sub_47EFD0(v22, COERCE_FLOAT(1), v21, v23, v23, 0) * *((uint32_t *)a1 + 245))
                        / *((uint32_t *)a1 + 244))
               + a1[97];
      }
      v24 = *((uint32_t *)a1 + 244);
      if ( v24 != 0
        && *((uint32_t *)a1 + 245) >= v24
        && (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)a1 + 243) + 792))(*((uint32_t *)a1 + 243), 8) != 0 )
      {
        v25 = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)a1 + 243) + 792))(*((uint32_t *)a1 + 243), 8);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 16))(v25) + 4) == 32239 )
          a1[97] = a1[97] * 1.2;
      }
      v26 = *((uint32_t *)a1 + 244);
      if ( v26 != 0 && *((uint32_t *)a1 + 245) >= v26 )
        (*(void (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "G_LASERGUNB",
          -1,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "G_LASERGUNA",
          -1,
          0,
          0);
    }
    *((uint8_t *)a1 + 988) = 1;
  }
  v27 = *((uint32_t *)a1 + 243);
  if ( v27 == 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
  if ( *(uint8_t *)(*((uint32_t *)a1 + 30) + 170) != 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 840))(v27);
  if ( result != 22 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
  return result;
}


// ------------------------------------------------------------
// 0x615C90 sub_615C90
// ------------------------------------------------------------
int /*thiscall*/ sub_615C90(uint32_t *this)
{
  *(this + 250) = 0;
  *(this + 251) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x615CA0 sub_615CA0
// ------------------------------------------------------------
bool /*thiscall*/ sub_615CA0(uint32_t *this, int a2)
{
  int v3; // ebx

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
  return v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2) <= 3 * *(this + 251) / 2
      && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, a2, 0) <= *(this + 251);
}



// ------------------------------------------------------------
// 0x615D10 sub_615D10
// ------------------------------------------------------------
int /*thiscall*/ sub_615D10(uint8_t *this, int a2)
{
  uint32_t *v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // ebx
  float v9; // [esp+14h] [ebp+8h]

  v3 = (uint32_t *)sub_47E720(1, 0x2Au);
  v4 = sub_47EF20(v3, 0, a2, -1, -1, 11);
  *(this + 985) = 0;
  *(this + 986) = 0;
  sub_698F90((int)(this + 972), v4 + 400, 0);
  v5 = sub_47EF20(v3, 2u, a2, -1, -1, 11);
  v6 = *(uint32_t *)this;
  *((uint32_t *)this + 171) = v5;
  *((uint32_t *)this + 170) = v5;
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(v6 + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    1);
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    0);
  v7 = sub_47EF20(v3, 1u, a2, -1, -1, 11);
  v9 = (double)v7 * 0.0041666669;
  sub_4922F0(v9);
  sub_4922F0(v9);
  sub_4922F0(v9);
  *((uint32_t *)this + 251) = v7 / 2;
  return v7 / 2;
}



// ------------------------------------------------------------
// 0x615E20 CNNenGuard__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNNenGuard__vmt12C(int **this, int a2)
{
  int **v2; // edi
  int *v4; // ecx
  int result; // eax
  int v6; // ebx
  int v7; // [esp+8h] [ebp-4h] BYREF

  v2 = (int **)a2;
  CNRDPassiveObject__vmt12C(this, a2);
  if ( v2 == this )
  {
    v4 = *(this + 253);
    result = *v4;
    a2 = *v4;
    if ( (int *)a2 != v4 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(result + 16) + 612))(
          *(uint32_t *)(result + 16),
          0,
          0);
        sub_41C5E0(&a2);
        result = a2;
      }
      while ( (int *)a2 != *(this + 253) );
    }
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **, int))(*v2)[10])(v2, 17);
    if ( (uint8_t)result != 0 )
    {
      a2 = (int)v2;
      result = sub_4BE520(&v7, &a2);
      v6 = v7;
      if ( (int *)v7 != *(this + 253) )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v7 + 16) + 612))(*(uint32_t *)(v7 + 16), 0, 0);
        return sub_52E6A0(&a2, v6);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x615ED0 CNNenGuard__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ sub_615ED0(void *this)
{
  int v2; // ebx
  unsigned int v3; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int **v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // ecx
  int v14; // eax
  int v15; // edi
  int v16; // edi
  int v17; // eax
  int v18; // edi
  int v19; // eax
  uint32_t *v20; // ecx
  uint32_t *v21; // eax
  int v22; // edi
  int result; // eax
  uint32_t v24[2]; // [esp+Ch] [ebp-1Ch] BYREF
  char v25[4]; // [esp+14h] [ebp-14h] BYREF
  int **v26; // [esp+18h] [ebp-10h] BYREF
  uint32_t *i; // [esp+1Ch] [ebp-Ch] BYREF
  int v28; // [esp+20h] [ebp-8h]
  int **v29; // [esp+24h] [ebp-4h] BYREF

  sub_600890();
  if ( *((int *)this + 170) <= 0 )
  {
    v2 = *((uint32_t *)this + 249);
    if ( sub_699000((int)this + 972) < v2 - 400 )
    {
      *((uint8_t *)this + 985) = 0;
      *((uint8_t *)this + 986) = 0;
      sub_698F90((int)this + 972, 400, 0);
    }
  }
  v3 = 0;
  if ( *((uint32_t *)this + 250) <= 1u )
  {
    v4 = *((uint32_t *)this + 29);
    v5 = *(uint32_t *)(v4 + 120);
    v6 = v4 + 116;
    v28 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
    for ( i = nullptr; (int)i < v28; i = (uint32_t *)((char *)i + 1) )
    {
      v7 = *((uint32_t *)this + 29);
      v8 = *(uint32_t *)(v7 + 120);
      if ( v8 != 0 && v3 < (*(uint32_t *)(v7 + 124) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * v3);
      else
        v9 = 0;
      v10 = (int **)__RTDynamicCast(
                      v9,
                      0,
                      &IRDCollisionObject `RTTI Type Descriptor',
                      &IRDActiveObject `RTTI Type Descriptor',
                      0);
      v26 = v10;
      if ( v10 != nullptr )
      {
        sub_4BE520(&v29, &v26);
        if ( (uint8_t)sub_615CA0(v10) != 0 )
        {
          if ( v29 == *((int ***)this + 253) )
          {
            v24[0] = v10;
            v24[1] = v10;
            sub_614810(v25, v24);
          }
          ((void (/*thiscall*/ *)(int **, int, int))(*v10)[153])(v10, 1, 2);
        }
        else if ( v29 != *((int ***)this + 253) )
        {
          ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t))(*v10)[153])(v10, 0, 0);
          sub_52E6A0((uint32_t *)this + 252, &v26, v29);
        }
      }
      v3 = (unsigned int)i + 1;
    }
  }
  v11 = *((uint32_t *)this + 250);
  v12 = *((uint32_t *)this + 30);
  v13 = *(uint32_t *)(v12 + 148);
  if ( v11 != 0 )
  {
    if ( v11 == 1 )
    {
      if ( v13 < 9 )
      {
        v15 = *((uint32_t *)this + 249);
        if ( sub_699000((int)this + 972) > v15 - 400 )
        {
          v16 = *((uint32_t *)this + 30);
          *((uint32_t *)this + 250) = 2;
          v17 = sub_491C70(v16, 10);
          sub_493A60(v16, v17);
          v18 = **((uint32_t **)this + 36);
          v19 = sub_491C70(v18, 5);
          sub_493A60(v18, v19);
          v20 = *((uint32_t **)this + 253);
          v21 = (uint32_t *)*v20;
          i = (uint32_t *)*v20;
          if ( i != v20 )
          {
            do
            {
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)v21[4] + 612))(v21[4], 0, 0);
              sub_41C5E0(&i);
              v21 = i;
            }
            while ( i != *((uint32_t **)this + 253) );
          }
        }
      }
      else
      {
        v14 = sub_491C70(v12, 4);
        sub_493A60(v12, v14);
      }
    }
  }
  else if ( v13 >= 4 )
  {
    *((uint32_t *)this + 250) = 1;
  }
  v22 = *((uint32_t *)this + 249);
  result = sub_699000((int)this + 972);
  if ( result >= v22 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x616130 sub_616130
// ------------------------------------------------------------
int /*thiscall*/ sub_616130(uint32_t *this)
{
  *(this + 243) = 0;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  *(this + 247) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616160 sub_616160
// ------------------------------------------------------------
int /*thiscall*/ sub_616160(uint32_t *this, int a2)
{
  uint32_t *v3; // edi
  uint64_t v4; // rax
  int result; // eax

  v3 = (uint32_t *)sub_47E720(0, 0x2Cu);
  *(this + 247) = a2;
  *(this + 243) = sub_47EF20(v3, 0, a2, -1, -1, 11);
  *(this + 244) = sub_47EF20(v3, 1u, a2, -1, -1, 11);
  v4 = (uint64_t)(1000.0 / (double)sub_47EF20(v3, 2u, a2, -1, -1, 11));
  *(this + 245) = v4;
  result = -(int)v4;
  *(this + 246) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6161F0 sub_6161F0
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_6161F0(uint32_t *a1, uint32_t *a2, float a3)
{
  int v3; // ecx
  float v4; // ebx
  float *i; // eax
  unsigned int v6; // ecx
  float v7; // edi
  uint32_t *v8; // esi
  int v9; // eax
  int v10; // ecx
  void *v11; // esi
  int v12; // eax
  int v13; // esi
  double v14; // st7
  uint64_t result; // rax
  uint32_t v16[4]; // [esp+0h] [ebp-10h] BYREF

  v16[0] = v3;
  if ( (dword_9B93B8 & 1) == 0 )
  {
    dword_9B93B8 |= 1u;
    dword_9B93AC = nullptr;
    dword_9B93B0 = nullptr;
    dword_9B93B4 = 0;
    atexit(sub_6BFF30);
    v16[3] = -1;
  }
  v4 = a3;
LABEL_4:
  for ( i = (float *)dword_9B93B0; ; dword_9B93B0 = i )
  {
    while ( dword_9B93AC == nullptr )
    {
LABEL_8:
      a3 = 0.0;
      if ( dword_9B93AC == nullptr
        || ((char *)i - (uint8_t *)dword_9B93AC) >> 2 >= (unsigned int)((dword_9B93B4 - (int)dword_9B93AC) >> 2) )
      {
LABEL_14:
        sub_430C80((int)&unk_9B93A8, (int)i, 1u, (int *)&a3);
        goto LABEL_4;
      }
      *i++ = 0.0;
      dword_9B93B0 = i;
    }
    v6 = ((char *)i - (uint8_t *)dword_9B93AC) >> 2;
    if ( v6 > LODWORD(v4) )
      break;
    if ( v6 == 0 )
      goto LABEL_8;
    LODWORD(v7) = v6 + *((uint32_t *)i - 1);
    a3 = v7;
    if ( v6 >= (dword_9B93B4 - (int)dword_9B93AC) >> 2 )
      goto LABEL_14;
    *i++ = v7;
  }
  v8 = (char *)dword_9B93AC + 4 * LODWORD(v4);
  v9 = rand();
  v10 = *v8 + 1;
  v11 = dword_9B93AC;
  LODWORD(a3) = v9 % v10;
  sub_490410(v16, dword_9B93AC, (char *)dword_9B93AC + 4 * LODWORD(v4), &a3);
  LODWORD(a3) = (v16[0] - (int)v11) >> 2;
  v12 = rand();
  a3 = (float)SLODWORD(a3);
  v13 = v12 % 360;
  *a1 = (uint64_t)(sub_405400(v12 % 360) * (double)dword_7930D0[0] * a3 * 0.0099999998);
  v14 = sub_4053E0(v13);
  result = (uint64_t)(v14 * (double)dword_7930D4[0] * a3 * 0.0099999998);
  *a2 = result;
  return result;
}



// ------------------------------------------------------------
// 0x616390 CNTombStoneRain__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNTombStoneRain__vmt14C(int *this)
{
  int v2; // edx
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ecx
  int result; // eax
  int v11; // eax
  int v12; // edi
  float v13; // [esp-8h] [ebp-18h]
  int v14; // [esp+8h] [ebp-8h] BYREF
  int v15; // [esp+Ch] [ebp-4h] BYREF

  CNRDPassiveObject__vmt14C((int)this);
  if ( sub_699000((int)(this + 9)) >= *(this + 246) + *(this + 245) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      sub_432FA0();
      v13 = *((float *)this + 243);
      v15 = 0;
      v14 = 0;
      v2 = sub_6161F0(&v15, &v14, v13) >> 32;
      v3 = *this;
      v4 = (*(int (/*fastcall*/ **)(int *, int, uint32_t))(*this + 124))(this, v2, 0);
      v5 = v14;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14 + v4);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v3 + 136))(this, v15 + v6) != 0 )
      {
        v7 = *this;
        v8 = rand() % 2;
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, bool, uint32_t, uint32_t, uint32_t))(v7 + 580))(
          this,
          20015,
          *(this + 247),
          0,
          0,
          v15,
          v5,
          0,
          v8 != 0,
          0,
          0,
          0);
      }
    }
    *(this + 246) += *(this + 245);
  }
  if ( sub_699000((int)(this + 9)) >= *(this + 244) )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  v9 = *(this + 173);
  if ( v9 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 529);
  if ( (uint8_t)result == 0 )
  {
    v11 = __RTDynamicCast(
            *(this + 173),
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &CNSwordman `RTTI Type Descriptor',
            0);
    v12 = v11;
    if ( v11 == 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 840))(v11) != 10 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 1280))(v12) != 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 1284))(v12);
    if ( result != 44 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x616500 sub_616500
// ------------------------------------------------------------
char /*thiscall*/ sub_616500(uint8_t *this)
{
  *(this + 972) = 0;
  *(this + 973) = 0;
  *(this + 974) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616520 CNTombStone__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNTombStone__vmt2A8(int *this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax

  CNRDPassiveObject__vmt2A8(this, a2);
  LOBYTE(v3) = *((uint8_t *)this + 972);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = (char *)sub_47E720(0, 0x2Cu);
    v5 = *(this + 176);
    v6 = v4;
    *(this + 193) = sub_47EF20(v4, 4u, v5, -1, -1, 11);
    v7 = sub_47EF20(v6, 5u, v5, -1, -1, 11);
    v8 = *this;
    *((float *)this + 190) = (double)v7 * 0.1;
    v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 388))(this);
    v3 = sub_47EFD0(v6, COERCE_FLOAT(3), v5, v9, v9, 0);
    *((uint8_t *)this + 972) = 1;
    *((float *)this + 181) = (float)v3;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x6165C0 CNTombStone__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNTombStone__vmt14C(void *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 973) == 0 && *(int *)(*((uint32_t *)this + 30) + 148) >= 2 )
  {
    sub_424120(
      *(uint32_t **)(*((uint32_t *)this + 29) + 132),
      **((uint32_t **)this + 87),
      *(uint32_t *)(*((uint32_t *)this + 87) + 4));
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TOMBTONE_STUCK",
      -1,
      0,
      0);
    *((uint8_t *)this + 973) = 1;
  }
  if ( *((uint8_t *)this + 974) == 0 && *(int *)(*((uint32_t *)this + 30) + 148) >= 4 )
  {
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TOMBSTONE_DIG",
      -1,
      0,
      0);
    *((uint8_t *)this + 974) = 1;
  }
  result = *((uint32_t *)this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616670 sub_616670
// ------------------------------------------------------------
int /*thiscall*/ sub_616670(uint32_t *this)
{
  unsigned int i; // ecx
  int v3; // edx
  unsigned int v4; // edi

  for ( i = 0; ; i = v4 )
  {
    v3 = *(this + 36);
    if ( v3 == 0 || i >= (*(this + 37) - v3) >> 2 )
      break;
    v4 = i + 1;
    (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      i + 1,
      *(uint32_t *)(v3 + 4 * i),
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("TOMBSTONE_DROP", 0xEu);
}



// ------------------------------------------------------------
// 0x6166D0 sub_6166D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6166D0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6166E0 CNDropBomb__vmt12C
// ------------------------------------------------------------
void /*userpurge*/ CNDropBomb__vmt12C(int a1@<ecx>, int a2@<ebx>, int a3)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  void *v19; // ecx
  int v20; // [esp-10h] [ebp-44h]
  int v21; // [esp-Ch] [ebp-40h]
  int v22; // [esp-8h] [ebp-3Ch]
  float v23; // [esp+4h] [ebp-30h]
  float v24; // [esp+4h] [ebp-30h]
  char v25[4]; // [esp+10h] [ebp-24h] BYREF
  void *Block; // [esp+14h] [ebp-20h]
  int v27; // [esp+20h] [ebp-14h]
  int v28; // [esp+24h] [ebp-10h]
  int v29; // [esp+30h] [ebp-4h]
  int v30; // [esp+3Ch] [ebp+8h]

  CNRDPassiveObject__vmt12C((uint32_t *)a1, a3);
  if ( a3 == a1 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 308))(a1, a2) != 0
      && *(uint32_t *)(a1 + 284) == 22206 )
    {
      v4 = sub_47E720(2, 0x2Du);
      v5 = *(uint32_t *)(a1 + 704);
      v6 = (char *)v4;
      dword_78FE2C = 0;
      sub_5C6A90(100);
      sub_5C6A90(0);
      sub_5C6A50(6);
      v23 = (double)sub_47EF20(v6, 1u, v5, -1, -1, 11) * 0.1;
      sub_5DAE20(LODWORD(v23));
      v24 = (float)sub_47EF20(v6, 2u, v5, -1, -1, 11);
      sub_5DAE20(LODWORD(v24));
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 684))(a1) != 0 )
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 684))(a1);
      else
        v30 = a1;
      v7 = *(uint32_t *)a1;
      v28 = dword_78FE28;
      v27 = dword_78FE2C;
      v8 = (*(int (/*thiscall*/ **)(int))(v7 + 388))(a1);
      v9 = sub_47EFD0(v6, 0.0, v5, v8, v8, 0);
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) + 20;
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
      sub_4E4A50(v30, 22208, v9, v10, v20, v21, v22, 0, v27, v28);
    }
    if ( *(uint32_t *)(a1 + 384) < 0x10u )
      v11 = a1 + 364;
    else
      v11 = *(uint32_t *)(a1 + 364);
    v12 = *(uint32_t *)dword_8F84E4;
    v13 = sub_41ACF0(*(uint32_t *)(a1 + 712));
    v14 = (*(int (**)(int, const char *, ...))(v12 + 12))(dword_8F84E4, "%s/%s", v11, v13);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 972) + 112))(*(uint32_t *)(a1 + 972), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 972) + 8))(*(uint32_t *)(a1 + 972), v14);
    v15 = **(uint32_t **)(a1 + 972);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
    v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v16 + 40);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v17);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v15 + 40))(*(uint32_t *)(a1 + 972), v18);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 972) + 12))(*(uint32_t *)(a1 + 972), 0);
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(a1 + 972) + 92))(*(uint32_t *)(a1 + 972), v25);
    v19 = *(void **)(a1 + 116);
    v29 = 0;
    sub_4600B0(v19, 2, 0, (int)v25);
    sub_424120(
      *(uint32_t **)(*(uint32_t *)(a1 + 116) + 132),
      *(uint32_t *)(*(uint32_t *)(a1 + 348) + 8),
      *(uint32_t *)(*(uint32_t *)(a1 + 348) + 12));
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x616950 CNDropBomb__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNDropBomb__vmt14C(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *v6; // ecx
  uint8_t v7[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v9; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 976) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BOMB_DROP", -1, 0, 0);
    *((uint8_t *)this + 976) = 1;
  }
  v2 = *(uint32_t *)*(this + 243);
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v3 + 70);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(this + 243), v5);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v7);
  v6 = (void *)*(this + 29);
  v9 = 0;
  sub_4600B0(v6, 2, 0, (int)v7);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x616A10 sub_616A10
// ------------------------------------------------------------
int /*thiscall*/ sub_616A10(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v2 = sub_4C3640(this + 364, "Particle/DropBombTail.ptl", this);
    else
      v2 = sub_4C3640(*(uint32_t *)(this + 364), "Particle/DropBombTail.ptl", this);
  }
  else
  {
    v2 = 0;
  }
  *(uint32_t *)(this + 972) = v2;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 112))(v2, this);
  *(float *)(*(uint32_t *)(this + 112) + 24) = (float)**(int **)(this + 348);
  v3 = *(uint32_t *)(this + 348);
  v4 = *(uint32_t *)(v3 + 4);
  *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = v4;
  return v3 + 4;
}



// ------------------------------------------------------------
// 0x616AD0 sub_616AD0
// ------------------------------------------------------------
char /*thiscall*/ sub_616AD0(void *this, int a2)
{
  int v2; // ecx

  v2 = (int)this + 976;
  *(float *)(v2 - 252) = (float)a2;
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  return sub_698F90(v2, 300, 0);
}



// ------------------------------------------------------------
// 0x616B00 CNTreadShootSub__vmt2A8
// ------------------------------------------------------------
int /*thiscall*/ CNTreadShootSub__vmt2A8(uint32_t *this, int a2)
{
  int result; // eax

  CNRDPassiveObject__vmt2A8(this, a2);
  result = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
  if ( result != 0 )
  {
    result = *(uint32_t *)(result + 8700);
    *(this + 243) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x616B40 CNTreadShootSub__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNTreadShootSub__vmt14C(void *this)
{
  int v2; // ecx
  int v3; // edi
  int result; // eax

  v2 = (int)this + 976;
  v3 = *(uint32_t *)(v2 + 24);
  result = sub_699000(v2);
  if ( result >= v3 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616B70 CNIceNiddle__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNIceNiddle__vmt14C(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = *(this + 30);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x616BA0 CNAshenForkSub__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNAshenForkSub__vmt2A8(int this, int a2)
{
  int v3; // eax
  int v4; // esi
  char *v5; // ebx
  int v6; // eax
  int v8; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  LOBYTE(v3) = *(uint8_t *)(this + 976);
  if ( (uint8_t)v3 == 0 )
  {
    v3 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    v4 = v3;
    if ( v3 != 0 )
    {
      v5 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1160))(v3, 16);
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1140))(v4, 16);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4);
      *(float *)(this + 724) = (float)sub_47EFD0(v5, COERCE_FLOAT(1), v8, v6, v6, 0);
      v3 = sub_47E9D0(v5, 3u);
      *(float *)(this + 724) = ((double)v3 * (double)*(int *)(this + 972) * 0.000099999997 + 1.0)
                             * *(float *)(this + 724);
    }
    *(uint8_t *)(this + 976) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x616C60 sub_616C60
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_616C60(float *this, float a2)
{
  uint32_t *v3; // eax
  float v4; // edx
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  unsigned int result; // eax
  unsigned int i; // edi
  int v10; // ecx
  float v11; // [esp+14h] [ebp+8h]

  v3 = *((uint32_t **)this + 36);
  v4 = *this;
  *(this + 243) = a2;
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v4) + 204))(2, *v3, 0, 0, 0, 1);
  (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 204))(
    this,
    1,
    *(uint32_t *)(*((uint32_t *)this + 36) + 4),
    0,
    0,
    0,
    1);
  v5 = *((uint32_t *)this + 36);
  if ( v5 != 0 && (unsigned int)((*((uint32_t *)this + 37) - v5) >> 2) > 2 )
    (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
      this,
      1,
      *(uint32_t *)(v5 + 8),
      0,
      0,
      0,
      0);
  sub_4015C0("SAJAHU_SPREAD", 0xDu);
  v6 = (uint32_t *)sub_47E720(0, 0x10u);
  v7 = LODWORD(a2) * sub_47E9D0(v6, 5u) / 100;
  v11 = (double)(sub_47E9D0(v6, 4u) + v7) * 0.0099999998;
  result = sub_4922F0(v11);
  for ( i = 0; ; ++i )
  {
    v10 = *((uint32_t *)this + 36);
    if ( v10 == 0 )
      break;
    result = (*((uint32_t *)this + 37) - v10) >> 2;
    if ( i >= result )
      break;
    result = sub_4922F0(v11);
  }
  return result;
}



// ------------------------------------------------------------
// 0x616D90 CNGrabBlastBlood__vmt2BC
// ------------------------------------------------------------
void /*userpurge*/ CNGrabBlastBlood__vmt2BC(int a1@<ecx>, int a2@<ebx>, float *a3, size_t Size)
{
  int v5; // eax
  int v6; // eax

  CNRDPassiveObject__vmt2BC((int)a3, Size);
  v5 = sub_45EBE0(*(uint32_t **)(a1 + 116), *(uint16_t *)a3, *((uint16_t *)a3 + 1));
  v6 = __RTDynamicCast(v5, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  *(uint32_t *)(a1 + 972) = v6;
  if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
    sub_4E5F70(a2, a1, *(uint32_t *)(a1 + 972), a3 + 1, 1, 0);
}



// ------------------------------------------------------------
// 0x616E10 CNGrabBlastBlood__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGrabBlastBlood__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( *(this + 243) == a2 )
    *(this + 243) = 0;
}



// ------------------------------------------------------------
// 0x616E40 CNGrabBlastBlood__vmt1F0
// ------------------------------------------------------------
int /*thiscall*/ CNGrabBlastBlood__vmt1F0(uint32_t *this, int a2, int a3, int a4)
{
  if ( a2 == *(this + 243) )
    *(this + 112) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616E60 CNGrabBlastBlood__vmt1F8
// ------------------------------------------------------------
int /*thiscall*/ CNGrabBlastBlood__vmt1F8(uint32_t *this, int a2, int a3, int a4)
{
  if ( a2 == *(this + 243) )
    *(this + 112) = 2;
  return 0;
}



// ------------------------------------------------------------
// 0x616E80 sub_616E80
// ------------------------------------------------------------
int /*thiscall*/ sub_616E80(float *this, int a2)
{
  uint32_t *v2; // eax
  float v3; // edx

  v2 = *((uint32_t **)this + 36);
  v3 = *this;
  *(this + 181) = (float)a2;
  return (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v3) + 204))(1, *v2, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x616EB0 sub_616EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_616EB0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x616ED0 CNGrandWave__vmt2A8
// ------------------------------------------------------------
void /*thiscall*/ CNGrandWave__vmt2A8(int this, int a2)
{
  int v3; // eax
  int v4; // esi
  char *v5; // ebx
  int v6; // eax
  double v7; // st7
  int v8; // eax
  char *v9; // ebx
  int v10; // eax
  float v11; // [esp+10h] [ebp-18h]
  int v12; // [esp+30h] [ebp+8h]
  int v13; // [esp+30h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  if ( *(uint8_t *)(this + 976) == 0 )
  {
    v3 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    v4 = v3;
    if ( v3 != 0 )
    {
      v5 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1160))(v3, 50);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1140))(v4, 50);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4);
      v7 = (double)sub_47EFD0(v5, COERCE_FLOAT(1), v12, v6, v6, 0);
      v8 = *(uint32_t *)(this + 972);
      *(float *)(this + 724) = v7;
      if ( v8 > 0 )
      {
        v9 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1160))(v4, 51);
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1140))(v4, 51);
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4);
        v11 = (float)sub_47EFD0(v9, 0.0, v13, v10, v10, 0);
        *(float *)(this + 724) = sub_4049C0(0.0, v11, *(uint32_t *)(this + 972), dword_795A0C) + *(float *)(this + 724);
      }
    }
    *(uint8_t *)(this + 976) = 1;
  }
}



// ------------------------------------------------------------
// 0x616FE0 CNGrandWave__vmt14C
// ------------------------------------------------------------
void /*usercall*/ CNGrandWave__vmt14C(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  bool v5; // bl
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  uint8_t v12[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)a1);
  if ( sub_699000((int)(a1 + 9)) >= a1[245] + 100 )
  {
    v4 = dword_8F82A0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 152))(a1, a3, a2) == 0;
    *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 28))(v4) + 84) = v5;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1) != 0 )
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1) - 40;
    else
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1) + 40;
    v7 = *(uint32_t *)v4;
    v14 = v6;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v8);
    (*(void (/*thiscall*/ **)(int, int, int))(v7 + 40))(v4, v14, v9);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 12))(v4, 0);
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v4 + 92))(v4, v12);
    v10 = (void *)a1[29];
    v15 = 0;
    sub_4600B0(v10, 2, 0, (int)v12);
    a1[245] = sub_699000((int)(a1 + 9));
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x6170E0 sub_6170E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6170E0(void *this, float a2)
{
  float v3; // edx
  uint32_t *v4; // eax
  float v6; // [esp+18h] [ebp-14h]
  int v7; // [esp+1Ch] [ebp-10h]
  int v8; // [esp+20h] [ebp-Ch]
  float v9; // [esp+34h] [ebp+8h]

  v3 = *(float *)this;
  *((float *)this + 243) = a2;
  (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(LODWORD(v3) + 204))(
    this,
    2,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  if ( *((int *)this + 243) > 0 )
  {
    v4 = (uint32_t *)sub_47E720(0, 0x33u);
    v8 = dword_795A0C;
    v7 = *((uint32_t *)this + 243);
    v6 = (double)sub_47E9D0(v4, 1u) * 0.0099999998;
    v9 = sub_4049C0(1.0, v6, v7, v8);
    sub_4922F0(v9);
    sub_4922F0(v9);
    if ( *((uint32_t *)this + 243) >= dword_795A0C )
    {
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        1,
        *((uint32_t *)this + 34),
        -20,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        3,
        **((uint32_t **)this + 36),
        -20,
        0,
        0,
        0);
      *((uint32_t *)this + 196) = 2;
    }
  }
  return sub_4015C0("AIR_SWORD", 9u);
}



// ------------------------------------------------------------
// 0x6171F0 sub_6171F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6171F0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1;
  *(uint8_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x617210 CNDecoy__vmt10
// ------------------------------------------------------------
char /*thiscall*/ CNDecoy__vmt10(int this)
{
  char result; // al
  int v3; // edi
  int v4; // eax

  CNRDPassiveObject__vmt10((uint8_t *)this);
  result = *(uint8_t *)(this + 980);
  if ( result == 0 )
  {
    v3 = *(uint32_t *)(this + 120);
    v4 = sub_491C70(v3, *(uint32_t *)(this + 972));
    sub_493A60(v3, v4);
    result = sub_4939E0(*(uint32_t *)(this + 120), 1);
    *(uint8_t *)(this + 980) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x617250 CNDecoy__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDecoy__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // edi
  uint32_t *v6; // eax
  int v7; // edi
  int v8; // eax
  int v10; // [esp+Ch] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 376))(a2);
  if ( v5 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 273) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
  {
    v6 = (uint32_t *)sub_47E720(3, 3u);
    v7 = sub_47EF20(v6, 6u, *(this + 244), -1, -1, 11);
    if ( v7 > 0 )
    {
      v10 = *a2;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 684))(this, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(v10 + 760))(a2, 12, 1120403456, v7, v8);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 312))(this, 1);
    }
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x617310 sub_617310
// ------------------------------------------------------------
int /*thiscall*/ sub_617310(int this, int a2)
{
  int v3; // edx
  int v4; // eax

  v3 = rand() % 3;
  v4 = *(uint32_t *)(this + 112);
  *(uint32_t *)(this + 972) = v3;
  *(uint32_t *)(this + 976) = a2;
  *(uint32_t *)(v4 + 24) = 1128792064;
  *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = -800;
  *(uint8_t *)(this + 700) = 0;
  return sub_4015C0("PHASE_SHIFT", 0xBu);
}



// ------------------------------------------------------------
// 0x617370 sub_617370
// ------------------------------------------------------------
int /*thiscall*/ sub_617370(int *this, int a2)
{
  int result; // eax
  uint32_t *v4; // ebx
  int v5; // eax
  int v6; // esi
  void *v7; // ebx
  void *v8; // ebx
  void *v9; // ebx
  float v10; // [esp+24h] [ebp-28h]
  float v11; // [esp+24h] [ebp-28h]
  float v12; // [esp+24h] [ebp-28h]
  float v13; // [esp+24h] [ebp-28h]
  void *Block; // [esp+34h] [ebp-18h]
  uint32_t *v15; // [esp+3Ch] [ebp-10h]

  result = a2;
  if ( a2 != 0 )
  {
    v4 = (uint32_t *)sub_47E720(3, 3u);
    v15 = v4;
    if ( operator new(0x7Cu) != nullptr )
    {
      v5 = sub_47EF20(v4, 1u, *(this + 244), -1, -1, 11);
      v6 = sub_4B3C90(v5, 1);
    }
    else
    {
      v6 = 0;
    }
    Block = *(void **)v6;
    v10 = (float)sub_47EF20(v4, 2u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))Block + 30))(v6, 8, 0, LODWORD(v10));
    v7 = *(void **)v6;
    v11 = (float)sub_47EF20(v15, 3u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))v7 + 30))(v6, 7, 0, LODWORD(v11));
    v8 = *(void **)v6;
    v12 = (float)sub_47EF20(v15, 4u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))v8 + 30))(v6, 0, 0, LODWORD(v12));
    v9 = *(void **)v6;
    v13 = (float)sub_47EF20(v15, 5u, *(this + 244), -1, -1, 11);
    (*((void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))v9 + 30))(v6, 1, 0, LODWORD(v13));
    return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, int, int))(*(uint32_t *)v6 + 56))(
             v6,
             a2,
             *(this + 173),
             1,
             0,
             10,
             -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6174E0 sub_6174E0
// ------------------------------------------------------------
int /*thiscall*/ sub_6174E0(uint32_t *this)
{
  if ( sub_699000((int)(this + 9)) < *(this + 244) )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 5, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x617520 sub_617520
// ------------------------------------------------------------
int /*thiscall*/ sub_617520(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 4;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint8_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1012) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1028) = 0;
  *(uint32_t *)(this + 1032) = 0;
  *(uint32_t *)(this + 1036) = 0;
  *(uint8_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1044) = -1;
  *(uint32_t *)(this + 960) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x6175B0 CNChaser__vmt2A8
// ------------------------------------------------------------
char /*userpurge*/ CNChaser__vmt2A8@<al>(int a1@<ecx>, int a2@<ebx>, int a3)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  double v9; // st7
  char v10; // al
  int v11; // eax
  int v14; // [esp+10h] [ebp+8h]

  CNRDPassiveObject__vmt2A8((uint32_t *)a1, a3);
  LOBYTE(v4) = *(uint8_t *)(a1 + 972);
  if ( (uint8_t)v4 == 0 )
  {
    v4 = __RTDynamicCast(a3, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    v5 = v4;
    v14 = v4;
    if ( v4 == 0 )
    {
LABEL_12:
      *(uint8_t *)(a1 + 972) = 1;
      return v4;
    }
    v6 = (char *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v4 + 1160))(
                   v4,
                   dword_73C3CC[*(uint32_t *)(a1 + 980)],
                   a2);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 1140))(v5, dword_73C3CC[*(uint32_t *)(a1 + 980)]);
    *(uint32_t *)(a1 + 976) = sub_47EF20(v6, 0, v7, -1, -1, 11);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 388))(v14);
    v9 = (double)sub_47EFD0(v6, COERCE_FLOAT(1), v7, v8, v8, 0);
    v10 = *(uint8_t *)(a1 + 1008);
    *(float *)(a1 + 724) = v9;
    if ( v10 != 0 )
      *(float *)(a1 + 724) = v9 + v9;
    v11 = *(uint32_t *)(a1 + 980);
    if ( v11 != 0 )
    {
      if ( v11 == 1 )
      {
        *(float *)(a1 + 760) = (double)sub_47EF20(v6, 2u, v7, -1, -1, 11) * 0.1;
        *(uint32_t *)(a1 + 772) = sub_47EF20(v6, 3u, v7, -1, -1, 11);
LABEL_11:
        LOBYTE(v4) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 344))(a1, a1 + 724);
        goto LABEL_12;
      }
      if ( v11 != 2 && v11 != 3 )
        goto LABEL_11;
    }
    *(uint32_t *)(a1 + 788) = sub_47EF20(v6, 2u, v7, -1, -1, 11);
    *(uint32_t *)(a1 + 792) = sub_47EF20(v6, 3u, v7, -1, -1, 11);
    goto LABEL_11;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x617720 sub_617720
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_617720(uint32_t *a1, uint32_t *a2, uint32_t *a3, int a4)
{
  int v4; // edx

  *a1 = -30 - 8 * a4;
  *a2 = (uint64_t)(sub_405400(110 * a4 % 360) * (double)dword_7930D4[0] * 0.2);
  v4 = 60 - (uint64_t)(sub_4053E0(110 * a4 % 360) * -20.0);
  *a3 = v4;
  return a3;
}



// ------------------------------------------------------------
// 0x617790 CNChaser__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNChaser__vmt12C(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  if ( a2 == *(this + 254) )
    *(this + 254) = 0;
  if ( (uint32_t *)a2 == this )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v4 = __RTDynamicCast(v3, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    if ( v4 != 0 )
      sub_5DC290(v4);
  }
}



// ------------------------------------------------------------
// 0x6177F0 sub_6177F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6177F0(uint32_t *this, int a2, int a3, char a4)
{
  int v4; // esi
  uint32_t *v5; // eax
  int v6; // esi
  int v7; // eax
  int v9; // [esp-8h] [ebp-18h]
  int v10; // [esp-8h] [ebp-18h]

  v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 116))(a2, a3);
  if ( a3 != 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 152))(a2) != 0 )
  {
    v5 = this;
    v6 = *(this + a3 + 246) + v4;
  }
  else
  {
    v5 = this;
    v6 = v4 - *(this + 246);
  }
  if ( a4 != 0 )
  {
    if ( a3 == 0 )
    {
      v9 = sub_699000((int)(v5 + 9));
      v7 = sub_42B420(-3, 3, v9, 400);
LABEL_10:
      v6 += v7;
      return v6;
    }
    if ( a3 == 2 )
    {
      v10 = sub_699000((int)(v5 + 9));
      v7 = sub_42B420(-5, 5, v10, 70);
      goto LABEL_10;
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x617880 sub_617880
// ------------------------------------------------------------
int /*thiscall*/ sub_617880(int *this, int a2)
{
  int result; // eax

  if ( *(this + 249) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 249));
  result = a2;
  *(this + 249) = a2;
  if ( a2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 1, a2, 0, 0, 0, 0);
    return sub_4926A0(*(this + 249));
  }
  return result;
}



// ------------------------------------------------------------
// 0x6178D0 CNChaser__vmt10
// ------------------------------------------------------------
char /*usercall*/ CNChaser__vmt10@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<esi>)
{
  char result; // al
  int v5; // esi
  int v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  CNRDPassiveObject__vmt10((uint8_t *)a1);
  result = *(uint8_t *)(a1 + 1000);
  if ( result == 0 )
  {
    v5 = *(uint32_t *)(a1 + 692);
    if ( v5 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 116))(v5, 2, a2, a3);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 116))(v5, 1);
      v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 116))(v5, 0);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 152))(v5) != 0 )
        v6 = *(uint32_t *)(a1 + 984) + v8;
      else
        v6 = v8 - *(uint32_t *)(a1 + 984);
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 112))(a1, v6);
    }
    *(uint8_t *)(a1 + 1000) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x617970 sub_617970
// ------------------------------------------------------------
int /*thiscall*/ sub_617970(int *this)
{
  int result; // eax
  int i; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  uint8_t *v7; // ebx
  int v8; // edi
  int v9; // ebx
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  double v13; // st7
  float v14; // [esp+14h] [ebp-34h]
  float v15; // [esp+18h] [ebp-30h]
  int v16; // [esp+34h] [ebp-14h]
  int v17; // [esp+38h] [ebp-10h]
  int v18; // [esp+3Ch] [ebp-Ch]
  int v19; // [esp+40h] [ebp-8h]
  float v20; // [esp+44h] [ebp-4h]

  result = *(this + 240);
  if ( result == 2 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = sub_699000((int)(this + 9));
      if ( result >= *(this + 253) + 100 )
      {
        result = *(this + 173);
        if ( result != 0 )
        {
          for ( i = 0; i < 3; ++i )
          {
            v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 116))(this, i);
            v5 = sub_6177F0(*(this + 173), i, 1);
            v6 = dword_73C3AC[i];
            v19 = v5;
            v20 = sub_4049C0(0.0, flt_73C3B8[i], abs32(v5 - v4), v6);
            if ( v19 >= v4 )
            {
              if ( v19 == v4 )
                v20 = 0.0;
            }
            else
            {
              v20 = v20 * -1.0;
            }
            v7 = (uint8_t *)*(this + 28);
            if ( *(uint32_t *)v7 != 0
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v7 + 308))(*(uint32_t *)v7) != 0
              && *(float *)&v7[4 * i + 16] != v20 )
            {
              *(float *)&v7[4 * i + 16] = v20;
              v7[196] = 1;
            }
          }
          result = sub_699000((int)(this + 9));
          *(this + 253) = result;
        }
      }
    }
  }
  else if ( result == 3 )
  {
    result = *(this + 254);
    v8 = 0;
    if ( result != 0 )
    {
      result = sub_699000((int)(this + 9));
      if ( result > *(this + 255) )
      {
        if ( *((uint8_t *)this + 1040) == 0 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "CHASER_LAUNCH",
            -1,
            0,
            0);
          *((uint8_t *)this + 1040) = 1;
        }
        v16 = 0;
        v17 = 0;
        v18 = 0;
        do
        {
          v9 = *(this + 254);
          v20 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 116))(v9, v8));
          if ( v8 != 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 152))(v9) != 0 )
            LODWORD(v20) += *(this + v8 + 246);
          else
            LODWORD(v20) -= *(this + 246);
          v10 = *(this + 256);
          v11 = sub_699000((int)(this + 9));
          v12 = *(this + 255);
          v15 = (float)SLODWORD(v20);
          v19 = *(this + v8 + 257);
          v13 = (double)v19;
          v14 = v13;
          sub_4049F0(v14, v15, v11 - v12, v10, 0);
          *(&v16 + v8++) = (uint64_t)v13;
        }
        while ( v8 < 3 );
        return (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 112))(this, v16, v17, v18);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x617B80 sub_617B80
// ------------------------------------------------------------
unsigned int sub_617B80()
{
  int i; // esi
  unsigned int j; // ebx
  int v2; // ecx
  unsigned int result; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  for ( i = 0; i < 20; i += 4 )
  {
    for ( j = 0; ; ++j )
    {
      v2 = dword_9B93C4[i];
      if ( v2 == 0 )
        break;
      result = (dword_9B93C8[i] - v2) >> 2;
      if ( j >= result )
        break;
      v4 = *(void (/*thiscall*/ ****)(uint32_t, int))(dword_9B93C4[i] + 4 * j);
      if ( v4 != nullptr )
        (**v4)(v4, 1);
      result = 4 * j + dword_9B93C4[i];
      *(uint32_t *)result = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x617BF0 CNChaser__vmtC
// ------------------------------------------------------------
float */*thiscall*/ CNChaser__vmtC(int *this)
{
  float *result; // eax

  result = CNRDPassiveObject__vmtC(this);
  if ( *(this + 245) == 2 )
    return (float *)sub_617880(this, *(uint32_t *)(*(this + 36) + 16));
  return result;
}



// ------------------------------------------------------------
// 0x617C20 sub_617C20
// ------------------------------------------------------------
char /*thiscall*/ sub_617C20(uint8_t *this, int a2, int a3)
{
  int v3; // eax
  int v5; // edx
  int v6; // eax
  unsigned int v7; // eax
  unsigned int i; // edi
  int v9; // ecx

  v3 = a2;
  if ( a2 >= 10000 )
  {
    *(this + 1008) = 1;
    v3 = a2 - 10000;
  }
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 251) = v3;
  *((uint32_t *)this + 245) = a3;
  *(this + 701) = 0;
  *(this + 700) = 0;
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int))(v5 + 472))(this, 2, 0, 1, 1);
  v6 = *((uint32_t *)this + 245);
  *((uint32_t *)this + 168) = 3;
  sub_4015C0(*(&off_795C18 + v6), strlen((const char *)*(&off_795C18 + v6)));
  LOBYTE(v7) = *(this + 1008);
  if ( (uint8_t)v7 != 0 )
  {
    if ( *((uint32_t *)this + 34) != 0 )
      LOBYTE(v7) = sub_4922F0(1.7);
    for ( i = 0; ; ++i )
    {
      v9 = *((uint32_t *)this + 36);
      if ( v9 == 0 )
        break;
      v7 = (*((uint32_t *)this + 37) - v9) >> 2;
      if ( i >= v7 )
        break;
      LOBYTE(v7) = sub_4922F0(1.7);
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x617D00 sub_617D00
// ------------------------------------------------------------
char */*thiscall*/ sub_617D00(int this, int a2, int a3, int a4)
{
  int v5; // edx
  char *v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  char *v12; // ecx
  int v13; // edx
  unsigned int v14; // edi
  uint32_t *v15; // edx
  unsigned int i; // edi
  int v17; // eax
  int v18; // edx
  char *result; // eax
  int v20; // esi
  char v21; // al
  uint32_t *v22; // esi
  uint32_t *v23; // eax
  int v24; // [esp+Ch] [ebp-128h]
  char v25[4]; // [esp+10h] [ebp-124h] BYREF
  void *Block; // [esp+14h] [ebp-120h]
  uint32_t *v27; // [esp+18h] [ebp-11Ch]
  int v28; // [esp+1Ch] [ebp-118h]
  void *v29; // [esp+20h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+24h] [ebp-110h] BYREF
  int v31; // [esp+124h] [ebp-10h]
  int v32; // [esp+130h] [ebp-4h]

  v5 = *(uint32_t *)(this + 980);
  v31 = dword_796E50;
  v6 = (char *)&unk_9B93C0 + 16 * v5;
  v7 = *((uint32_t *)v6 + 1);
  if ( v7 == 0 || (*((uint32_t *)v6 + 2) - v7) >> 2 == 0 )
  {
    v8 = v5;
    v9 = 0;
    if ( dword_73C3E0[v5] > 0 )
    {
      do
      {
        v24 = v9 + 1;
        sprintf(Buffer, "Character/Mage/Effect/Particle/Chaser%s%d.ptl", off_795C04[v8], v9 + 1);
        v10 = operator new(0x12Cu);
        v29 = v10;
        v32 = 0;
        if ( v10 != nullptr )
          v11 = sub_428F30(v10, (int)Buffer, 0);
        else
          v11 = nullptr;
        v12 = (char *)&unk_9B93C0 + 16 * *(uint32_t *)(this + 980);
        v13 = *((uint32_t *)v12 + 1);
        v32 = -1;
        v29 = v11;
        if ( v13 != 0 )
          v14 = (*((uint32_t *)v12 + 2) - v13) >> 2;
        else
          v14 = 0;
        if ( v13 != 0 && v14 < (*((uint32_t *)v12 + 3) - v13) >> 2 )
        {
          v15 = *((uint32_t **)v12 + 2);
          *v15 = v11;
          *((uint32_t *)v12 + 2) = v15 + 1;
        }
        else
        {
          sub_5CC5A0(*((void **)v12 + 2), 1, (int)&v29);
        }
        v9 = v24;
        v8 = *(uint32_t *)(this + 980);
      }
      while ( v24 < dword_73C3E0[v8] );
    }
  }
  for ( i = 0; ; ++i )
  {
    v17 = 4 * *(uint32_t *)(this + 980);
    v18 = dword_9B93C4[v17];
    result = (char *)&unk_9B93C0 + v17 * 4;
    if ( v18 == 0 || i >= (*((uint32_t *)result + 2) - v18) >> 2 )
      break;
    v20 = *(uint32_t *)(v18 + 4 * i);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 40))(v20, a2, a3, a4);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v20 + 92))(v20, v25);
    v21 = *(uint8_t *)(this + 1008);
    v32 = 1;
    if ( v21 != 0 )
    {
      v22 = Block;
      if ( Block != v27 )
      {
        do
        {
          v23 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v22 + 96))(*v22);
          sub_4922F0(v23, 1.7);
          ++v22;
        }
        while ( v22 != v27 );
      }
    }
    sub_4600B0(*(void **)(this + 116), 2, 0, (int)v25);
    v32 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v27 = nullptr;
    v28 = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x617F50 CNChaser__vmt14C
// ------------------------------------------------------------
char /*usercall*/ sub_617F50@<al>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  bool v19; // zf
  int v21; // [esp-Ch] [ebp-30h]
  int v22; // [esp-8h] [ebp-2Ch]
  float v23; // [esp+8h] [ebp-1Ch] BYREF
  float v24; // [esp+Ch] [ebp-18h]
  float v25; // [esp+10h] [ebp-14h]
  int v26; // [esp+14h] [ebp-10h]
  int v27; // [esp+18h] [ebp-Ch]
  int v28; // [esp+1Ch] [ebp-8h]
  int v29; // [esp+20h] [ebp-4h]

  sub_600890();
  v3 = a1[240];
  if ( v3 == 2 )
  {
    v4 = a1[30];
    if ( v4 == a1[34] && *(uint8_t *)(v4 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)a1[36]);
      if ( a1[245] == 2 )
        sub_617880(*(uint32_t *)(a1[36] + 20));
    }
    v5 = __RTDynamicCast(a1[173], 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
    if ( v5 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 840))(v5) == 5 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
    }
    else if ( a1[167] != v5 )
    {
      a1[167] = v5;
    }
    v3 = sub_699000((int)(a1 + 9));
    if ( v3 >= a1[244] )
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 5, 0, 0, 0);
    goto LABEL_40;
  }
  if ( v3 == 3 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
    if ( (uint8_t)v3 == 0 )
      goto LABEL_40;
    v6 = a1[254];
    v7 = a1;
    if ( v6 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, v6, 0) <= 480 )
      {
        v3 = sub_699000((int)(a1 + 9));
        if ( v3 < a1[255] + a1[256] )
          goto LABEL_40;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[254] + 608))(a1[254]) != 0
          && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[254] + 200))(a1[254]) != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[254] + 200))(a1[254]);
          v9 = sub_42F220(v8);
          if ( (uint8_t)sub_600070(v9 + 72) == 0 )
          {
            v10 = a1[254];
            v23 = 0.0;
            v24 = 0.0;
            v25 = 0.0;
            v26 = 0;
            v27 = 0;
            v28 = 0;
            v11 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v10 + 116))(v10, 0, a2);
            v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 152))(v10) == 0;
            v12 = a1[246];
            if ( v19 )
              v13 = v11 - v12;
            else
              v13 = v12 + v11;
            v14 = a1[254];
            v29 = v13;
            v23 = (float)v13;
            v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 116))(v14, 1) + a1[247];
            v15 = a1[254];
            v24 = (float)v29;
            v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 116))(v15, 2) + a1[248];
            v17 = a1[254];
            v29 = v16;
            v25 = (float)v16;
            sub_4E5F70(v13, (int)a1, v17, &v23, 1, 1);
LABEL_39:
            LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
            goto LABEL_40;
          }
        }
      }
      v7 = a1;
    }
    LOBYTE(v3) = sub_6174E0(v7);
    goto LABEL_40;
  }
  if ( v3 != 4 )
  {
    if ( v3 != 5 )
      goto LABEL_40;
    v3 = a1[30];
    v19 = *(uint8_t *)(v3 + 170) == 0;
LABEL_38:
    if ( v19 )
      goto LABEL_40;
    goto LABEL_39;
  }
  if ( a1[261] == -1 )
  {
    LOBYTE(v3) = *(uint8_t *)(a1[30] + 170);
    v19 = (uint8_t)v3 == 0;
    goto LABEL_38;
  }
  v3 = sub_699000((int)(a1 + 9));
  if ( v3 >= a1[261] )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[36] + 12));
    if ( a1[245] == 2 )
    {
      if ( a1[249] != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 208))(a1, a1[249]);
      a1[249] = 0;
    }
    v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
    v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 124))(a1);
    v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1);
    LOBYTE(v3) = sub_617D00(v18, v21, v22);
    a1[261] = -1;
  }
LABEL_40:
  if ( a1[154] == -1 )
    LOBYTE(v3) = sub_617970(a1);
  return v3;
}


// ------------------------------------------------------------
// 0x618260 CNChaser__vmt1F4
// ------------------------------------------------------------
int /*userpurge*/ CNChaser__vmt1F4@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3, float *a4, char a5)
{
  uint32_t *v6; // edi
  int v8; // [esp-8h] [ebp-2Ch]
  void *v9[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  v6 = (uint32_t *)a3;
  if ( a1[240] == 3 )
  {
    if ( a5 == 0 )
    {
      if ( a1[245] != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a3 + 124))(a3, (uint64_t)a4[2]) + 1;
        sub_617D00((int)a1, (uint64_t)*a4, v8, a2);
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*a1 + 308))(a1, a2) != 0 )
      {
        memset(&v9[1], 0, 12);
        v10 = 0;
        a3 = 0;
        sub_431230((int)v9, &a3);
        a3 = (*(int (/*thiscall*/ **)(uint32_t *))(*v6 + 48))(v6);
        sub_431230((int)v9, &a3);
        a3 = (*(int (/*thiscall*/ **)(uint32_t *))(*v6 + 52))(v6);
        sub_431230((int)v9, &a3);
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*a1 + 560))(a1, 4, v9, 0, 0);
        v10 = -1;
        sub_5E5260(v9);
      }
      (*(void (/*thiscall*/ **)(int *, char *, int, uint32_t))(*a1 + 212))(a1, off_795C2C[a1[245]], -1, 0);
    }
    if ( v6 == (uint32_t *)a1[254] )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 312))(a1, 0);
  }
  return CNRDPassiveObject__vmt1F4(a1, v6, a4, a5);
}



// ------------------------------------------------------------
// 0x6183A0 CNChaser__vmt1D8
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6183A0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  uint32_t *v6; // eax
  uint8_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // ecx
  int v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  char *v21; // eax
  char *v22; // edi
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  int v26; // eax
  uint32_t *v27; // eax
  uint8_t *v28; // eax
  uint32_t *v29; // ebx
  int i; // eax
  int v31; // eax
  uint32_t *v32; // eax
  uint8_t *v33; // eax
  int j; // ebx
  uint8_t *v35; // edi
  uint32_t *result; // eax
  uint32_t *v37; // edi
  int v38; // [esp+Ch] [ebp-10h]
  uint32_t *v39; // [esp+24h] [ebp+8h]
  int v40; // [esp+24h] [ebp+8h]
  int v41; // [esp+2Ch] [ebp+10h]
  int v42; // [esp+30h] [ebp+14h]

  v38 = *(this + 240);
  if ( v38 == 2 )
  {
    if ( a2 != 2 )
      *(this + 167) = 0;
  }
  else if ( v38 == 3 )
  {
    *(this + 254) = 0;
  }
  sub_6000E0(a2, a3, a4, a5);
  switch ( a2 )
  {
    case 2:
      sub_617720(this + 246, this + 247, this + 248, *(this + 251));
      if ( v38 == 3 )
      {
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
        v7 = __RTDynamicCast(v6, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
        if ( v7 != nullptr )
        {
          *(this + 251) = -1;
          sub_5DC290(v7);
        }
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
        if ( *(this + 245) == 2 )
        {
          v8 = (uint32_t *)(*(this + 36) + 20);
          goto LABEL_51;
        }
      }
      break;
    case 3:
      v9 = (uint32_t *)sub_45EBE0(**(uint32_t **)(a3 + 4), *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4));
      *(this + 254) = __RTDynamicCast(
                        v9,
                        0,
                        &CNRDObject `RTTI Type Descriptor',
                        &IRDActiveObject `RTTI Type Descriptor',
                        0);
      *(this + 255) = sub_699000((int)(this + 9)) + 100;
      *(this + 256) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8) - 100;
      *((uint8_t *)this + 1040) = 0;
      v10 = 0;
      v11 = 16;
      v39 = this + 257;
      do
      {
        *(uint32_t *)(v11 + *(this + 28)) = 0;
        *v39 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, v10);
        v11 += 4;
        ++v10;
        ++v39;
      }
      while ( v11 < 28 );
      v12 = *(this + 254);
      v13 = 0;
      if ( v12 != 0 )
      {
        *(this + 246) = 0;
        *(this + 247) = 0;
        *(this + 248) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 192))(v12) / 2;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 8));
      if ( *(this + 245) == 2 )
        sub_617880(*(uint32_t *)(*(this + 36) + 28));
      if ( sub_42FCB0(228) != 0 )
        v13 = sub_431860((char)"Character/Mage/Effect/Animation/Chaser/StartAttack.ani", 1);
      v14 = (char *)sub_44B6C0(284);
      v15 = v14;
      if ( v14 != nullptr )
      {
        sub_44E0D0(v14, v13, 1);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v15, 2, 0, (int)v15, (int)this, 0);
      v16 = *(uint32_t *)v15;
      v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v17);
      v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v18);
      (*(void (/*thiscall*/ **)(char *, int))(v16 + 112))(v15, v19);
      if ( *(this + 254) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
          v20 = sub_431860((char)"Character/Mage/Effect/Animation/Chaser/Target.ani", 1);
        else
          v20 = 0;
        v21 = (char *)sub_44B6C0(284);
        v22 = v21;
        if ( v21 != nullptr )
        {
          sub_44E0D0(v21, v20, 1);
          *(uint32_t *)v22 = &CNRDPooledObject::`vftable';
          v42 = (int)v22;
        }
        else
        {
          v42 = 0;
        }
        sub_45FE80(*(this + 29), (int)v22, 2, 0, v42, *(this + 254), 0);
        v23 = *(this + 248) + (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 254) + 116))(*(this + 254), 2);
        v24 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 254) + 116))(*(this + 254), 1);
        v25 = *(this + 254);
        v41 = *(this + 247) + v24;
        v40 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v25 + 116))(v25, 0);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 152))(v25) != 0 )
          v26 = *(this + 246) + v40;
        else
          v26 = v40 - *(this + 246);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v42 + 112))(v42, v26, v41 + 1);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v42 + 60))(v42, *(this + 254));
        sub_4A06D0(v23);
      }
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 356))(this, *(this + 254));
      v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      v28 = __RTDynamicCast(v27, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
      if ( v28 != nullptr )
        sub_5DC290(v28);
      (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        off_795C40[*(this + 245)],
        -1,
        0,
        0);
      break;
    case 4:
      v29 = *(uint32_t **)(a3 + 4);
      *(this + 261) = *v29 + sub_699000((int)(this + 9));
      for ( i = 16; i < 28; i += 4 )
        *(uint32_t *)(i + *(this + 28)) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      *(this + 174) = 1000;
      v31 = *(uint32_t *)(a3 + 4);
      if ( v31 != 0 && (unsigned int)((*(uint32_t *)(a3 + 8) - v31) >> 2) >= 3 )
      {
        v32 = (uint32_t *)sub_45EBE0(*(uint32_t *)(v31 + 4), *(uint32_t *)(v31 + 8));
        v33 = __RTDynamicCast(v32, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
        if ( v33 != nullptr )
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *))(*this + 356))(this, v33);
      }
      break;
    case 5:
      for ( j = 16; j < 28; j += 4 )
      {
        v35 = (uint8_t *)*(this + 28);
        if ( *(uint32_t *)v35 != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v35 + 308))(*(uint32_t *)v35) != 0
          && *(float *)&v35[j] != 0.0 )
        {
          *(uint32_t *)&v35[j] = 0;
          v35[196] = 1;
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      if ( *(this + 245) == 2 )
      {
        v8 = (uint32_t *)(*(this + 36) + 24);
LABEL_51:
        sub_617880(*v8);
      }
      break;
    default:
      break;
  }
  sub_4926A0(*(this + 30));
  result = (uint32_t *)*(this + 32);
  v37 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4926A0(v37[3]);
      v37 = (uint32_t *)*v37;
    }
    while ( v37 != (uint32_t *)*(this + 32) );
  }
  return result;
}


// ------------------------------------------------------------
// 0x618920 sub_618920
// ------------------------------------------------------------
int /*thiscall*/ sub_618920(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x618930 sub_618930
// ------------------------------------------------------------
int /*thiscall*/ sub_618930(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 244) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x618950 CNMagicMissile__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNMagicMissile__vmt2BC(int *this, uint16_t *a2, size_t Size)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+4h] [ebp-20h]
  float v14; // [esp+4h] [ebp-20h]
  int v15; // [esp+1Ch] [ebp-8h]
  int v16; // [esp+20h] [ebp-4h]
  int v17; // [esp+20h] [ebp-4h]
  uint16_t v18; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v18 = *a2;
  v4 = sub_47E720(3, 0xBu);
  v5 = *(this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v16 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v13 = (float)sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  v11 = (float)v16;
  v15 = (uint64_t)sub_4049C0(v11, v13, v18, 1000) - 100;
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v17 = sub_47EFD0(v6, COERCE_FLOAT(4), v5, v8, v8, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(5), v5, Sizeb, Sizeb, 0);
  v12 = (float)v17;
  v9 = (uint64_t)sub_4049C0(v12, v14, v18, 1000);
  *(this + 183) += v15;
  HIDWORD(v9) = *this;
  *((float *)this + 181) = (double)(100 * (int)v9 / (v15 + 100)) + *((float *)this + 181);
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x618A90 CNMagicMissile__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNMagicMissile__vmt14C(uint32_t *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  uint8_t v9[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v11; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v2 = *(this + 244);
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104));
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 28))(v2) + 72) = *(uint32_t *)(v3 + 72);
    *((uint8_t *)this + 972) = 1;
  }
  v4 = *(uint32_t *)*(this + 244);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(this + 244), v7);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v9);
  v8 = (void *)*(this + 29);
  v11 = 0;
  sub_4600B0(v8, 2, 0, (int)v9);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x618B60 sub_618B60
// ------------------------------------------------------------
int /*thiscall*/ sub_618B60(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"PassiveObject/Character/Mage/Particle/MagicMissileParticle.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 244) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v3 + 112))(v3, this);
  return sub_4015C0("MAGIC_MISSILE", 0xDu);
}



// ------------------------------------------------------------
// 0x618BE0 sub_618BE0
// ------------------------------------------------------------
int /*thiscall*/ sub_618BE0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 1000;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint8_t *)(this + 996) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x618C20 sub_618C20
// ------------------------------------------------------------
char /*thiscall*/ sub_618C20(int *this)
{
  char result; // al
  int *v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // [esp-20h] [ebp-24h]
  int v7; // [esp-1Ch] [ebp-20h]
  int v8; // [esp-18h] [ebp-1Ch]
  int v9; // [esp-10h] [ebp-14h]
  int v10; // [esp-Ch] [ebp-10h]

  result = *((uint8_t *)this + 996);
  if ( result == 0 )
  {
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = (uint64_t)((double)*(this + 246) * 0.060000002);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = *((uint16_t *)this + 490);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    v3 = this;
    v4 = 100 * *(this + 244) / (*(this + 245) + 100);
    if ( *(this + 173) != 0 )
      v3 = (int *)*(this + 173);
    v10 = dword_78FE28;
    v9 = dword_78FE2C;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    result = sub_4E4A50(v3, 23016, v4, v5, v6, v7, v8, 0, v9, v10);
    *((uint8_t *)this + 996) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x618D30 CNLaunchJOL__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchJOL__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v4; // eax
  int v7; // [esp+Ch] [ebp-4h] BYREF

  v4 = *a2;
  v7 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(a2, &v7, this);
  if ( a4 == 0 && v7 > 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
    sub_618C20(this);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x618D90 CNLaunchJOL__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNLaunchJOL__vmt214(int *this, int a2, int a3, int a4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    sub_618C20(this);
  return CNRDPassiveObject__vmt214(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x618DD0 CNLaunchJOL__vmt10
// ------------------------------------------------------------
void /*thiscall*/ CNLaunchJOL__vmt10(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // esi

  CNRDPassiveObject__vmt10((uint8_t *)this);
  if ( *(float *)(this + 992) != 0.0 )
  {
    sub_4938F0(*(uint32_t *)(this + 120));
    sub_492080(*(float *)(this + 992));
    v2 = *(uint32_t **)(this + 128);
    v3 = (uint32_t *)*v2;
    if ( (uint32_t *)*v2 != v2 )
    {
      do
      {
        sub_4938F0(v3[3]);
        sub_492080(*(float *)(this + 992));
        v3 = (uint32_t *)*v3;
      }
      while ( v3 != *(uint32_t **)(this + 128) );
    }
  }
}



// ------------------------------------------------------------
// 0x618E40 CNLaunchJOL__vmt14C
// ------------------------------------------------------------
signed int /*thiscall*/ sub_618E40(int *this)
{
  int v2; // edi
  int i; // ebx
  int v4; // edx
  int v5; // eax
  float *v6; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  signed int result; // eax
  int v15; // edi
  int v16; // ecx
  int v17; // [esp-30h] [ebp-44h]
  int v18; // [esp-2Ch] [ebp-40h]
  int v19; // [esp-28h] [ebp-3Ch]
  int v20; // [esp-24h] [ebp-38h]
  int v21; // [esp-20h] [ebp-34h]
  int v22; // [esp-18h] [ebp-2Ch]
  int v23; // [esp-10h] [ebp-24h]
  int v24; // [esp-Ch] [ebp-20h]
  int v25; // [esp-8h] [ebp-1Ch]
  int v26; // [esp-4h] [ebp-18h]
  int v27; // [esp+Ch] [ebp-8h] BYREF
  int v28; // [esp+10h] [ebp-4h] BYREF

  sub_600890();
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(uint32_t *)(*(this + 28) + 104) == 0
    && *(uint8_t *)(*(this + 30) + 170) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
           dword_8F84E4,
           "Character/Mage/Particle/LaunchJOL.ptl");
    *(uint8_t *)(v2 + 84) = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
    for ( i = 0; i < 3; ++i )
      *(uint32_t *)(v2 + 4 * i) = sub_4A0650(*(this + 28), i);
    *(uint32_t *)(v2 + 85) = *(this + 243);
    *(uint32_t *)(v2 + 76) = *(this + 247);
    v4 = *this;
    v28 = 0;
    v27 = 0;
    if ( (*(int (/*thiscall*/ **)(int *))(v4 + 684))(this) != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, 17) != 0 )
      {
        v6 = *(float **)(sub_4924C0(*(int **)*(this + 36), 0) + 60);
        v26 = (uint64_t)(v6[5] * 1.5);
        v25 = (uint64_t)(v6[4] * 1.5);
        v24 = (uint64_t)(v6[3] * 1.5);
        v23 = *(uint32_t *)(v2 + 85) * *(uint32_t *)(v2 + 15) / 1000;
        v22 = *(this + 247) != 0 ? 0xF : 0;
        v21 = *(uint32_t *)(v2 + 76);
        v20 = *(uint32_t *)(v2 + 72);
        v19 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v18 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
        v17 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        v7 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
        sub_4B2580(&v28, &v27, v7, v17, v18, v19, v20, v21, 15, v22, -1, v23, v24, v25, v26);
      }
    }
    v8 = *(uint32_t *)(v2 + 76);
    *(uint32_t *)(v2 + 72) += v28;
    *(uint32_t *)(v2 + 76) = v27 + v8;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
    v9 = *(uint32_t *)dword_8F8520;
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v2, 98);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    v13 = *(uint32_t *)(v2 + 76);
    *(uint32_t *)(v2 + 72) -= v28;
    *(uint32_t *)(v2 + 76) = v13 - v27;
  }
  result = *(uint32_t *)(*(this + 28) + 104);
  if ( result != 0 )
  {
    result = *(this + 30);
    if ( result == *(this + 34) )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -1,
        *(uint32_t *)(*(this + 36) + 8),
        0,
        0,
        0,
        0);
      v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                      + 76);
      v16 = dword_7930D4[0]
          * *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                      + 72)
          / 100;
      result = abs32(v15);
      if ( result <= (int)abs32(v16) )
        v27 = -v16;
      else
        v27 = v15;
      *((float *)this + 248) = (double)v27 * 0.0174532925199433;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x619110 CNLaunchJOL__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchJOL__vmt2BC(int *this, uint16_t *a2, int Size)
{
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint64_t v10; // rax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int result; // eax
  int v16; // ecx
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+0h] [ebp-24h]
  float v20; // [esp+0h] [ebp-24h]
  float v21; // [esp+0h] [ebp-24h]
  float v22; // [esp+4h] [ebp-20h]
  float v23; // [esp+4h] [ebp-20h]
  float v24; // [esp+4h] [ebp-20h]
  float v25; // [esp+4h] [ebp-20h]
  float v26; // [esp+4h] [ebp-20h]
  int v27; // [esp+1Ch] [ebp-8h]
  int v28; // [esp+20h] [ebp-4h]
  uint16_t v29; // [esp+2Ch] [ebp+8h]
  float v30; // [esp+2Ch] [ebp+8h]
  int v31; // [esp+2Ch] [ebp+8h]
  int v32; // [esp+2Ch] [ebp+8h]
  int v33; // [esp+2Ch] [ebp+8h]
  int v34; // [esp+2Ch] [ebp+8h]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  dword_78FE34 = 0;
  dword_78FE30 = (int)a2;
  v29 = *a2;
  dword_78FE34 = 2;
  v4 = (char *)sub_47E720(3, 0xFu);
  v5 = *(this + 176);
  v6 = v4;
  v28 = v29;
  v22 = (float)sub_47EF20(v4, 5u, v5, -1, -1, 11);
  v17 = (float)sub_47EF20(v6, 4u, v5, -1, -1, 11);
  v30 = sub_4049C0(v17, v22, v29, 1000) * 0.001;
  sub_4922F0(v30);
  sub_4922F0(v30);
  sub_4922F0(v30);
  sub_4922F0(v30);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v31 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, v7, v7, 11);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v9 = sub_47EFD0(v6, 0.0, v5, v8, v8, 11);
  v23 = (float)v31;
  v18 = (float)v9;
  v10 = (uint64_t)sub_4049C0(v18, v23, v28, 1000);
  HIDWORD(v10) = *this;
  *(this + 245) = v10 - 100;
  v11 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v10) + 388))(this);
  v32 = sub_47EFD0(v6, COERCE_FLOAT(9), v5, v11, v11, 0);
  v12 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v13 = sub_47EFD0(v6, COERCE_FLOAT(8), v5, v12, v12, 0);
  v24 = (float)v32;
  v19 = (float)v13;
  *(this + 244) = (uint64_t)sub_4049C0(v19, v24, v28, 1000);
  v33 = sub_47EF20(v6, 3u, v5, -1, -1, 11);
  v14 = sub_47EF20(v6, 2u, v5, -1, -1, 11);
  v25 = (float)v33;
  v20 = (float)v14;
  *(this + 243) = (uint64_t)sub_4049C0(v20, v25, v28, 1000);
  v34 = sub_47EF20(v6, 7u, v5, -1, -1, 11);
  v27 = sub_47EF20(v6, 6u, v5, -1, -1, 11);
  v26 = (float)v34;
  v21 = (float)v27;
  *(this + 246) = (uint64_t)sub_4049C0(v21, v26, v28, 1000);
  result = dword_78FE34;
  if ( dword_78FE34 >= Size )
  {
    *(this + 247) = 0;
  }
  else
  {
    v16 = *(uint32_t *)(dword_78FE34 + dword_78FE30);
    result = dword_78FE34 + 4;
    dword_78FE34 += 4;
    *(this + 247) = v16;
  }
  *((float *)this + 248) = (double)*(this + 247) * 0.017444445;
  return result;
}



// ------------------------------------------------------------
// 0x6193B0 sub_6193B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6193B0(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -2,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  return sub_4015C0("LANTURN_FIRE", 0xCu);
}



// ------------------------------------------------------------
// 0x6193F0 sub_6193F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6193F0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1065353216;
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x619410 sub_619410
// ------------------------------------------------------------
int /*stdcall*/ sub_619410(int a1, int a2)
{
  int64_t v2; // rax
  int v3; // edx

  v2 = (a1 % 360 + 360) % 360 - (a2 % 360 + 360) % 360;
  v3 = (int)((HIDWORD(v2) ^ v2) - HIDWORD(v2)) % 360;
  if ( v3 <= 180 )
    return v3;
  else
    return 360 - v3;
}



// ------------------------------------------------------------
// 0x619460 sub_619460
// ------------------------------------------------------------
int /*usercall*/ sub_619460@<eax>(uint32_t *a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int result; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  unsigned int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // esi
  int v14; // ecx
  int v15; // edx
  int v16; // esi
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // esi
  int v23; // eax
  int v25; // [esp+4h] [ebp-80h]
  int v26; // [esp+8h] [ebp-7Ch]
  unsigned int v27; // [esp+Ch] [ebp-78h]
  int v28; // [esp+10h] [ebp-74h]
  int v29; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  uint32_t v31[26]; // [esp+1Ch] [ebp-68h] BYREF

  v31[25] = dword_796E50;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    result = a1[29];
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 60))(a1);
      v5 = *(uint32_t *)(result + 104);
      if ( v5 != 0 )
      {
        sub_423A20(v31);
        qmemcpy(v31, (const void *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v5 + 16))(v5, a2, a3), 0x62u);
        v31[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 24))(v5);
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 28))(v5);
        *(uint32_t *)((char *)&v31[7] + 3) = a1[246];
        v31[1] = v6;
        v31[2] = 1;
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 44))(v5);
        if ( *(uint32_t *)((char *)&v31[21] + 1) - v7 >= 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 44))(v5);
          *(uint32_t *)((char *)&v31[21] + 1) -= v9;
          v8 = 0;
        }
        else
        {
          v8 = 0;
          *(uint32_t *)((char *)&v31[21] + 1) = 0;
        }
        v10 = a1[29];
        v11 = *(uint32_t *)(v10 + 120);
        v12 = v10 + 116;
        if ( v11 != 0 )
          v28 = (*(uint32_t *)(v12 + 8) - v11) >> 2;
        else
          v28 = 0;
        v13 = v31[18];
        v30 = -1;
        v29 = 0;
        v26 = v31[18];
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1) == 0 )
          v26 = 180 - v13;
        v25 = 9 * *(uint32_t *)((char *)&v31[21] + 1) * *(uint32_t *)((char *)&v31[3] + 3) / 10;
        v27 = 0;
        if ( v28 > 0 )
        {
          do
          {
            v14 = a1[29];
            v15 = *(uint32_t *)(v14 + 120);
            if ( v15 != 0 && v8 < (*(uint32_t *)(v14 + 124) - v15) >> 2 )
            {
              v16 = *(uint32_t *)(v15 + 4 * v8);
              if ( v16 != 0
                && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 40))(v16, 17) != 0
                && (uint8_t)sub_4E4630(v16) != 0 )
              {
                v17 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*a1 + 164))(
                                          a1,
                                          v16,
                                          0);
                if ( sub_619410(v17, v26) <= a1[243] / 2 )
                {
                  v18 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, v16, 0);
                  if ( (v30 == -1 || v18 < v29) && v18 < v25 )
                  {
                    v30 = v17;
                    v29 = v18;
                  }
                }
                v8 = v27;
              }
            }
            v27 = ++v8;
          }
          while ( (int)v8 < v28 );
          v19 = v30;
          if ( v30 != -1 )
          {
            if ( v30 <= 90 || v30 >= 270 )
            {
              LOBYTE(v31[21]) = 0;
            }
            else
            {
              LOBYTE(v31[21]) = 1;
              v19 = 180 - v30;
            }
            v31[18] = v19;
          }
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v20 = *(uint32_t *)dword_8F8520;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 48))(a1);
        (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);
        v22 = *(uint32_t *)dword_8F8520;
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 52))(a1);
        (*(void (/*thiscall*/ **)(int, int))(v22 + 36))(dword_8F8520, v23);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v31, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6196E0 CNLaunchFrostHead__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchFrostHead__vmt2BC(char *this, uint16_t *a2, size_t Size)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  uint64_t v8; // rax
  int v9; // eax
  int v10; // ecx
  uint32_t *v11; // eax
  int v12; // eax
  uint32_t *v13; // ecx
  int v14; // eax
  int v15; // edx
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+0h] [ebp-24h]
  float v20; // [esp+4h] [ebp-20h]
  float v21; // [esp+4h] [ebp-20h]
  float v22; // [esp+4h] [ebp-20h]
  int v23; // [esp+1Ch] [ebp-8h]
  int v24; // [esp+1Ch] [ebp-8h]
  int v25; // [esp+20h] [ebp-4h]
  uint16_t v26; // [esp+2Ch] [ebp+8h]
  int v27; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  float Sizec; // [esp+30h] [ebp+Ch]
  size_t Sized; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v26 = *a2;
  v4 = sub_47E720(3, 0x10u);
  v5 = *((uint32_t *)this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  v23 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v25 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  Sizeb = v26;
  v20 = (float)v25;
  v17 = (float)v23;
  v8 = (uint64_t)sub_4049C0(v17, v20, v26, 1000);
  HIDWORD(v8) = *(uint32_t *)this;
  *((uint32_t *)this + 183) = v8 - 100;
  v27 = (*(int (/*thiscall*/ **)(char *))(HIDWORD(v8) + 388))(this);
  v9 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
  v24 = sub_47EFD0(v6, COERCE_FLOAT(10), v5, v9, v9, 0);
  v21 = (float)sub_47EFD0(v6, COERCE_FLOAT(11), v5, v27, v27, 0);
  v18 = (float)v24;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v18, v21, Sizeb, 1000))
                                  / (*((uint32_t *)this + 183) + 100))
                         + *((float *)this + 181);
  *((uint32_t *)this + 243) = sub_47EF20(v6, 4u, v5, -1, -1, 11);
  v22 = (float)sub_47EF20(v6, 6u, v5, -1, -1, 11);
  v19 = (float)sub_47EF20(v6, 5u, v5, -1, -1, 11);
  Sizec = sub_4049C0(v19, v22, Sizeb, 1000) * 0.001;
  *((float *)this + 244) = Sizec;
  sub_4922F0(Sizec);
  sub_4922F0(*((float *)this + 244));
  v10 = 0;
  v11 = this + 748;
  while ( *v11 != 17 )
  {
    ++v10;
    ++v11;
    if ( v10 >= 3 )
      goto LABEL_6;
  }
  *((uint32_t *)this + v10 + 187) = 0;
  *((uint32_t *)this + v10 + 190) = 1120403456;
  *((uint32_t *)this + v10 + 193) = sub_47EF20(v6, 7u, v5, -1, -1, 11);
LABEL_6:
  v12 = 0;
  v13 = this + 748;
  while ( *v13 != 17 )
  {
    ++v12;
    ++v13;
    if ( v12 >= 3 )
      goto LABEL_11;
  }
  Sized = v12;
  *((uint32_t *)this + v12 + 187) = 1;
  *((float *)this + v12 + 190) = (double)sub_47EF20(v6, 8u, v5, -1, -1, 11) * 0.1;
  *((uint32_t *)this + Sized + 193) = sub_47EF20(v6, 9u, v5, -1, -1, 11);
LABEL_11:
  v14 = sub_47E9D0(v6, 4u);
  v15 = *(uint32_t *)this;
  *((uint32_t *)this + 246) = v14;
  return (*(int (/*thiscall*/ **)(char *, char *))(v15 + 344))(this, this + 724);
}



// ------------------------------------------------------------
// 0x619980 CNLaunchFrostHead__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchFrostHead__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax
  int v6; // ebx
  const char *v7; // ecx
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax

  v5 = sub_42FCB0(228);
  v6 = 0;
  if ( v5 != 0 )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      v7 = (const char *)(this + 91);
    else
      v7 = (const char *)*(this + 91);
    v6 = sub_431920(v5, v7, "Animation/LaunchFrostHeadHit.ani", 1);
  }
  sub_4922F0(*((float *)this + 244));
  v8 = (char *)sub_44B6C0(284);
  v9 = v8;
  if ( v8 != nullptr )
  {
    sub_44E0D0(v8, v6, 1);
    *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v9 = nullptr;
  }
  sub_45FE80(*(this + 29), (int)v9, 2, 0, (int)v9, 0, 0);
  v10 = *(uint32_t *)v9;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a2 + 124))(a2, v11);
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v12 + 1);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v9, v13);
  v14 = *(uint32_t *)v9;
  v15 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v14 + 148))(v9, v15);
  *((uint8_t *)this + 980) = 1;
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x619AB0 CNLaunchFrostHead__vmt14C
// ------------------------------------------------------------
int /*usercall*/ CNLaunchFrostHead__vmt14C@<eax>(char *a1@<ecx>, int a2@<edi>)
{
  int v3; // ecx
  int v4; // ebx
  int result; // eax
  int v6; // eax
  const char *v7; // ecx
  char *v8; // eax
  char *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // eax

  CNRDPassiveObject__vmt14C((int)a1);
  v3 = *(uint32_t *)(*((uint32_t *)a1 + 28) + 104);
  v4 = 0;
  if ( v3 != 0 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3) + 84) != 0 )
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)a1 + 148))(a1, 0);
    else
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)a1 + 148))(a1, 1);
  }
  if ( (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)a1 + 128))(a1) <= 0 )
  {
    result = *((uint32_t *)a1 + 30);
    if ( result == *((uint32_t *)a1 + 34) )
    {
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)a1 + 196))(a1, **((uint32_t **)a1 + 36));
      sub_4926A0(*((uint32_t *)a1 + 30));
      v6 = sub_42FCB0(228);
      if ( v6 != 0 )
      {
        if ( *((uint32_t *)a1 + 96) < 0x10u )
          v7 = a1 + 364;
        else
          v7 = *((const char **)a1 + 91);
        v4 = sub_431920(v6, v7, "Animation/LaunchFrostHeadJumpEffect.ani", 1);
      }
      v8 = (char *)sub_44B6C0(284);
      v9 = v8;
      if ( v8 != nullptr )
      {
        sub_44E0D0(v8, v4, 1);
        *(uint32_t *)v9 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v9 = nullptr;
      }
      sub_45FE80(*((uint32_t *)a1 + 29), (int)v9, 2, 0, (int)v9, (int)a1, 0);
      v10 = *(uint32_t *)v9;
      v11 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)a1 + 128))(a1);
      v12 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)a1 + 124))(a1, v11);
      v13 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)a1 + 120))(a1, v12);
      (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v9, v13);
      v14 = *(uint32_t *)v9;
      v15 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)a1 + 152))(a1);
      return (*(int (/*thiscall*/ **)(char *, int))(v14 + 148))(v9, v15);
    }
    else if ( *(uint8_t *)(result + 170) != 0 )
    {
      return sub_619460(a1, a2, (int)a1);
    }
  }
  else
  {
    result = *((uint32_t *)a1 + 34);
    if ( *((uint32_t *)a1 + 30) != result )
    {
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)a1 + 196))(a1, *((uint32_t *)a1 + 34));
      sub_4926A0(*((uint32_t *)a1 + 30));
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
               a1,
               "FROSTHEAD",
               -1,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x619C80 CNLaunchFrostHead__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNLaunchFrostHead__vmt12C(uint8_t *this, int a2)
{
  int v3; // eax
  int v4; // ebx
  const char *v5; // edx
  char *v6; // eax
  char *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax

  if ( (uint8_t *)a2 == this && *(this + 980) == 0 )
  {
    v3 = sub_42FCB0(228);
    v4 = 0;
    if ( v3 != 0 )
    {
      if ( *((uint32_t *)this + 96) < 0x10u )
        v5 = this + 364;
      else
        v5 = *((const char **)this + 91);
      v4 = sub_431920(v3, v5, "Animation/LaunchFrostHeadDisappear.ani", 1);
    }
    sub_4922F0(*((float *)this + 244));
    v6 = (char *)sub_44B6C0(284);
    v7 = v6;
    if ( v6 != nullptr )
    {
      sub_44E0D0(v6, v4, 1);
      *(uint32_t *)v7 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v7 = nullptr;
    }
    sub_45FE80(*((uint32_t *)this + 29), (int)v7, 2, 0, (int)v7, 0, 0);
    v8 = *(uint32_t *)v7;
    v9 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
    v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v9);
    v11 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v10);
    (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v7, v11);
    v12 = *(uint32_t *)v7;
    v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
    (*(void (/*thiscall*/ **)(char *, int))(v12 + 148))(v7, v13);
  }
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x619DB0 sub_619DB0
// ------------------------------------------------------------
int /*thiscall*/ sub_619DB0(int this)
{
  *(uint32_t *)(this + 972) = 5;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 1065353216;
  *(uint8_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint8_t *)(this + 1008) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x619E00 sub_619E00
// ------------------------------------------------------------
int /*thiscall*/ sub_619E00(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // edi
  bool v7; // zf
  int v8; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  }
  v6 = v5;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;
  v8 = *(this + 249);
  if ( v7 )
    v9 = v8 - a2;
  else
    v9 = a2 + v8;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 112))(this, v9, v6, a3 + *(this + 251));
}



// ------------------------------------------------------------
// 0x619E70 CNLaunchBlackCat__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNLaunchBlackCat__vmt2BC(int *this, uint16_t *a2, size_t Size)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  uint64_t v9; // rax
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+0h] [ebp-24h]
  float v14; // [esp+0h] [ebp-24h]
  float v15; // [esp+4h] [ebp-20h]
  float v16; // [esp+4h] [ebp-20h]
  float v17; // [esp+4h] [ebp-20h]
  float v18; // [esp+4h] [ebp-20h]
  int v19; // [esp+1Ch] [ebp-8h]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  uint16_t v23; // [esp+2Ch] [ebp+8h]
  int v24; // [esp+2Ch] [ebp+8h]
  int v25; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v23 = *a2;
  v4 = sub_47E720(3, 0x12u);
  v5 = *(this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v19 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v22 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  Sizeb = v23;
  v15 = (float)v22;
  v11 = (float)v19;
  *(this + 183) += (uint64_t)sub_4049C0(v11, v15, v23, 1000) - 100;
  v24 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v20 = sub_47EFD0(v6, COERCE_FLOAT(6), v5, v8, v8, 0);
  v16 = (float)sub_47EFD0(v6, COERCE_FLOAT(7), v5, v24, v24, 0);
  v12 = (float)v20;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v12, v16, Sizeb, 1000))
                                  / (*(this + 183) + 100))
                         + *((float *)this + 181);
  v17 = (float)sub_47EF20(v6, 3u, v5, -1, -1, 11);
  v13 = (float)sub_47EF20(v6, 2u, v5, -1, -1, 11);
  *((float *)this + 247) = sub_4049C0(v13, v17, Sizeb, 1000) * 0.001 + 1.0;
  v25 = sub_47EF20(v6, 5u, v5, -1, -1, 11);
  v21 = sub_47EF20(v6, 4u, v5, -1, -1, 11);
  v18 = (float)v25;
  v14 = (float)v21;
  v9 = (uint64_t)sub_4049C0(v14, v18, Sizeb, 1000);
  HIDWORD(v9) = *this;
  *(this + 246) = v9 - 140;
  return (*(int (/*thiscall*/ **)(int *, int *))(HIDWORD(v9) + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x61A070 sub_61A070
// ------------------------------------------------------------
int /*thiscall*/ sub_61A070(int *this, int a2)
{
  int result; // eax
  float v4; // [esp+20h] [ebp-10h]
  float v5; // [esp+20h] [ebp-10h]
  int v6; // [esp+20h] [ebp-10h]
  int v7; // [esp+20h] [ebp-10h]
  int v8; // [esp+24h] [ebp-Ch]

  result = *(this + 243);
  *(this + 243) = a2;
  if ( result != 5 )
  {
    result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8 * result + 4));
    *(this + 244) = *(this + 245);
  }
  if ( a2 != 5 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(8 * a2 + *(this + 36)));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(8 * a2 + *(this + 36) + 4),
      0,
      0,
      0,
      0);
    v4 = *((float *)this + 247) * 100.0;
    sub_493D00(*(uint32_t *)(8 * a2 + *(this + 36)), v4);
    v5 = *((float *)this + 247) * 100.0;
    sub_493D00(*(uint32_t *)(8 * a2 + *(this + 36) + 4), v5);
    result = dword_73C5A4[a2];
    if ( a2 == 1 || a2 == 3 )
      result = 2 * *(this + 246);
    *(this + 245) += result;
  }
  switch ( a2 )
  {
    case 1:
      result = sub_619E00(40, 0);
      break;
    case 2:
      v8 = -*(this + 251);
      v6 = *(this + 246) + 135;
      *(this + 81) = 0;
      result = sub_619E00(v6, v8);
      break;
    case 3:
      v7 = *(this + 246) + 40;
      *(this + 81) = 1;
      result = sub_619E00(v7, -10);
      break;
    case 4:
      result = sub_619E00(0, 0);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61A1F0 CNLaunchBlackCat__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNLaunchBlackCat__vmt14C(int this)
{
  int v2; // edi
  int *v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // ebx
  int v7; // edi
  int v8; // ebx
  uint64_t v9; // rax
  int v10; // ebx
  int v11; // edi
  int v12; // ebx
  double v13; // st7
  int v14; // eax
  int v15; // ebx
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  bool v21; // cc
  float v23; // [esp+0h] [ebp-24h]
  float v24; // [esp+4h] [ebp-20h]
  int v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+1Ch] [ebp-8h]

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 992) == 0 )
  {
    *(uint8_t *)(this + 992) = 1;
    v2 = 0;
    v3 = (int *)(this + 996);
    do
      *v3++ = sub_4A0650(*(uint32_t *)(this + 112), v2++);
    while ( v2 < 3 );
  }
  if ( (int)(uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) >= *(uint32_t *)(this + 980) )
  {
    v4 = *(uint32_t *)(this + 972);
    if ( v4 == 4 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    else
      sub_61A070((int *)this, v4 + 1);
  }
  v5 = *(uint32_t *)(this + 972);
  if ( v5 == 1 )
  {
    v6 = *(uint32_t *)(this + 976);
    v7 = (uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) - v6;
    v8 = *(uint32_t *)(this + 980) - v6;
    v24 = (float)*(int *)(this + 984);
    v25 = (uint64_t)sub_4049C0(0.0, v24, v7, v8);
    v9 = (uint64_t)sub_4049C0(0.0, -10.0, v7, v8);
    sub_619E00((uint32_t *)this, v25 + 40, v9);
  }
  else if ( v5 == 3 )
  {
    v10 = *(uint32_t *)(this + 976);
    v11 = (uint64_t)((double)sub_699000(this + 36) * *(float *)(this + 988)) - v10;
    v12 = *(uint32_t *)(this + 980) - v10;
    v23 = (float)*(int *)(this + 984);
    v26 = (uint64_t)sub_4049C0(v23, 0.0, v11, v12);
    v13 = sub_4049C0(-10.0, 0.0, v11, v12);
    sub_619E00((uint32_t *)this, v26 + 40, (uint64_t)v13);
  }
  else if ( v5 != 2 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this) != 0 )
  {
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this);
    v15 = *(uint32_t *)this;
    v16 = v14;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 124))(v16, v17);
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v18);
    (*(void (/*thiscall*/ **)(int, int))(v15 + 112))(this, v19);
  }
  LOBYTE(v20) = *(uint8_t *)(this + 1008);
  if ( (uint8_t)v20 == 0 )
  {
    v20 = *(uint32_t *)(this + 972);
    v21 = v20 <= 2;
    if ( v20 == 2 )
    {
      if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 )
      {
LABEL_20:
        LOBYTE(v20) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
        *(uint8_t *)(this + 1008) = 1;
        return v20;
      }
      v21 = true;
    }
    if ( !v21 )
      goto LABEL_20;
  }
  return v20;
}



// ------------------------------------------------------------
// 0x61A400 sub_61A400
// ------------------------------------------------------------
int /*thiscall*/ sub_61A400(uint32_t *this)
{
  int v2; // eax
  float v4; // [esp+20h] [ebp-8h]
  float v5; // [esp+20h] [ebp-8h]

  v2 = *(this + 243);
  *(this + 243) = 0;
  if ( v2 != 5 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8 * v2 + 4));
    *(this + 244) = *(this + 245);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    1,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  v4 = *((float *)this + 247) * 100.0;
  sub_493D00(*(uint32_t *)*(this + 36), v4);
  v5 = *((float *)this + 247) * 100.0;
  sub_493D00(*(uint32_t *)(*(this + 36) + 4), v5);
  *(this + 245) += 80;
  *((uint8_t *)this + 701) = 0;
  *((uint8_t *)this + 700) = 0;
  return sub_4015C0("LAUNCH_PLUTO", 0xCu);
}



// ------------------------------------------------------------
// 0x61A4E0 sub_61A4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_61A4E0(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 1065353216;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61A500 sub_61A500
// ------------------------------------------------------------
int /*thiscall*/ sub_61A500(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 245) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61A520 sub_61A520
// ------------------------------------------------------------
int /*thiscall*/ sub_61A520(uint32_t *this)
{
  *(this + 243) = 1065353216;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61A540 sub_61A540
// ------------------------------------------------------------
int /*thiscall*/ sub_61A540(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 244;
  for ( i = 3; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61A570 CNHalloweenBusterSub__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNHalloweenBusterSub__vmt2BC(int *this, uint16_t *a2, size_t Size)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  uint64_t v8; // rax
  int v9; // eax
  uint64_t v10; // rax
  double v11; // st7
  int i; // edi
  int *v13; // ebx
  bool v14; // zf
  float v16; // [esp+0h] [ebp-24h]
  float v17; // [esp+0h] [ebp-24h]
  float v18; // [esp+0h] [ebp-24h]
  float v19; // [esp+4h] [ebp-20h]
  float v20; // [esp+4h] [ebp-20h]
  float v21; // [esp+4h] [ebp-20h]
  int v22; // [esp+1Ch] [ebp-8h]
  int v23; // [esp+1Ch] [ebp-8h]
  int v24; // [esp+1Ch] [ebp-8h]
  int v25; // [esp+20h] [ebp-4h]
  uint16_t v26; // [esp+2Ch] [ebp+8h]
  int v27; // [esp+2Ch] [ebp+8h]
  int v28; // [esp+2Ch] [ebp+8h]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  size_t Sizec; // [esp+30h] [ebp+Ch]
  uint32_t *Sizea; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v26 = *a2;
  v4 = sub_47E720(3, 0x1Bu);
  v5 = *(this + 176);
  v6 = (char *)v4;
  Sizeb = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v22 = sub_47EFD0(v6, COERCE_FLOAT(2), v5, v7, v7, 11);
  v25 = sub_47EFD0(v6, COERCE_FLOAT(3), v5, Sizeb, Sizeb, 11);
  Sizec = v26;
  v19 = (float)v25;
  v16 = (float)v22;
  v8 = (uint64_t)sub_4049C0(v16, v19, v26, 1000);
  HIDWORD(v8) = *this;
  *(this + 183) = v8 - 100;
  v27 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v8) + 388))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
  v23 = sub_47EFD0(v6, COERCE_FLOAT(10), v5, v9, v9, 0);
  v20 = (float)sub_47EFD0(v6, COERCE_FLOAT(11), v5, v27, v27, 0);
  v17 = (float)v23;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v17, v20, Sizec, 1000))
                                  / (*(this + 183) + 100))
                         + *((float *)this + 181);
  v24 = (uint64_t)(double)sub_47EF20(v6, 7u, v5, -1, -1, 11);
  v10 = (uint64_t)(double)sub_47EF20(v6, 6u, v5, -1, -1, 11);
  v21 = (float)v24;
  v18 = (float)(int)v10;
  v11 = (double)(int)(uint64_t)sub_4049C0(v18, v21, Sizec, 1000);
  Sizea = this + 244;
  v28 = 3;
  *((float *)this + 243) = v11 * 0.001;
  do
  {
    for ( i = 12; i < 20; i += 4 )
    {
      v13 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Sizea + 36))(*Sizea) + i);
      *v13 = (uint64_t)((double)*v13 * *((float *)this + 243));
    }
    v14 = v28 == 1;
    ++Sizea;
    --v28;
  }
  while ( !v14 );
  return (*(int (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 181);
}



// ------------------------------------------------------------
// 0x61A780 CNHalloweenBuster__vmt2BC
// ------------------------------------------------------------
int /*thiscall*/ CNHalloweenBuster__vmt2BC(void *this, uint16_t *a2, size_t Size)
{
  int v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  int v8; // eax
  float v10; // [esp+0h] [ebp-24h]
  float v11; // [esp+0h] [ebp-24h]
  float v12; // [esp+0h] [ebp-24h]
  float v13; // [esp+4h] [ebp-20h]
  float v14; // [esp+4h] [ebp-20h]
  float v15; // [esp+4h] [ebp-20h]
  int v16; // [esp+1Ch] [ebp-8h]
  int v17; // [esp+1Ch] [ebp-8h]
  int v18; // [esp+20h] [ebp-4h]
  uint16_t v19; // [esp+2Ch] [ebp+8h]
  int v20; // [esp+2Ch] [ebp+8h]
  size_t Sizea; // [esp+30h] [ebp+Ch]
  size_t Sizeb; // [esp+30h] [ebp+Ch]
  float Sizec; // [esp+30h] [ebp+Ch]

  CNRDPassiveObject__vmt2BC((int)a2, Size);
  v19 = *a2;
  v4 = sub_47E720(3, 0x1Bu);
  v5 = *((uint32_t *)this + 176);
  v6 = (char *)v4;
  Sizea = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v16 = sub_47EFD0(v6, 0.0, v5, v7, v7, 11);
  v18 = sub_47EFD0(v6, COERCE_FLOAT(1), v5, Sizea, Sizea, 11);
  Sizeb = v19;
  v13 = (float)v18;
  v10 = (float)v16;
  *((uint32_t *)this + 183) += (uint64_t)sub_4049C0(v10, v13, v19, 1000) - 100;
  v20 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);
  v17 = sub_47EFD0(v6, COERCE_FLOAT(8), v5, v8, v8, 0);
  v14 = (float)sub_47EFD0(v6, COERCE_FLOAT(9), v5, v20, v20, 0);
  v11 = (float)v17;
  *((float *)this + 181) = (double)((int)(100 * (uint64_t)sub_4049C0(v11, v14, Sizeb, 1000))
                                  / (*((uint32_t *)this + 183) + 100))
                         + *((float *)this + 181);
  v15 = (float)sub_47EF20(v6, 5u, v5, -1, -1, 11);
  v12 = (float)sub_47EF20(v6, 4u, v5, -1, -1, 11);
  Sizec = sub_4049C0(v12, v15, Sizeb, 1000) * 0.001;
  *((float *)this + 244) = Sizec;
  sub_4922F0(Sizec);
  sub_4922F0(*((float *)this + 244));
  sub_4922F0(*((float *)this + 244));
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 344))(this, (int)this + 724);
}



// ------------------------------------------------------------
// 0x61A960 CNHalloweenBuster__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNHalloweenBuster__vmt14C(uint32_t **this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  uint32_t *v6; // edi
  int result; // eax
  float v8; // edi
  int v9; // eax
  float v10; // [esp-4h] [ebp-2Ch]
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) > 30 )
  {
    v2 = **(this + 245);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3);
    v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(this + 245), v5);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 245) + 92))(*(this + 245), v11);
    v6 = Block;
    v15 = 0;
    if ( Block != v13 )
    {
      do
      {
        v10 = *((float *)this + 244);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 200))(*v6);
        sub_4922F0(v10);
        ++v6;
      }
      while ( v6 != v13 );
    }
    sub_4600B0(*(this + 29), 2, 0, (int)v11);
    v15 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
  }
  result = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  if ( result <= 0 && *((uint8_t *)this + 972) == 0 )
  {
    sub_424120((uint32_t *)(*(this + 29))[33], 4, 400);
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      v8 = *(float *)this;
      v9 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[32])(
             this,
             4,
             0,
             *(this + 241),
             *(this + 242));
      (*(void (/*thiscall*/ **)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(LODWORD(v8) + 580))(
        this,
        23014,
        *(this + 176),
        0,
        0,
        0,
        0,
        -v9);
    }
    result = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    *((uint8_t *)this + 972) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61AAD0 CNHalloweenBusterSub__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNHalloweenBusterSub__vmt14C(float *this)
{
  int **v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  bool v8; // zf
  char result; // al
  float v10; // [esp-4h] [ebp-30h]
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  uint32_t *v13; // [esp+14h] [ebp-18h]
  int v14; // [esp+18h] [ebp-14h]
  int v15; // [esp+1Ch] [ebp-10h]
  int v16; // [esp+28h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v2 = (int **)(this + 244);
  v15 = 3;
  do
  {
    v3 = **v2;
    v4 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 40))(*v2, v6);
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v2 + 92))(*v2, v11);
    v7 = Block;
    v16 = 0;
    if ( Block != v13 )
    {
      do
      {
        v10 = *(this + 243);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 200))(*v7);
        sub_4922F0(v10);
        ++v7;
      }
      while ( v7 != v13 );
    }
    sub_4600B0(*((void **)this + 29), 2, 0, (int)v11);
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v2;
    v8 = v15 == 1;
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
    --v15;
  }
  while ( !v8 );
  result = *(uint8_t *)(*((uint32_t *)this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x61ABD0 sub_61ABD0
// ------------------------------------------------------------
int /*thiscall*/ sub_61ABD0(uint32_t **this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -1,
    **(this + 36),
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    1,
    (*(this + 36))[1],
    0,
    0,
    0,
    0);
  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"PassiveObject/Common/Particle/ShootingStarFire.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 245) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t **))(*v3 + 112))(v3, this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(this + 245) + 12))(*(this + 245), 500);
  return sub_4015C0("SSTAR_DROP", 0xAu);
}



// ------------------------------------------------------------
// 0x61ACA0 sub_61ACA0
// ------------------------------------------------------------
int /*thiscall*/ sub_61ACA0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"PassiveObject/Common/Particle/ShootingStarExpSmoke.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 244) = v3;
  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    v5 = sub_428F30(v4, (int)"PassiveObject/Common/Particle/ShootingStarExp.ptl", (int)this);
  else
    v5 = nullptr;
  *(this + 245) = v5;
  v6 = operator new(0x12Cu);
  if ( v6 != nullptr )
    v7 = sub_428F30(v6, (int)"PassiveObject/Common/Particle/ShootingStarExpEtc.ptl", (int)this);
  else
    v7 = nullptr;
  *(this + 246) = v7;
  return sub_4015C0("SSTAR_HIT", 9u);
}



// ------------------------------------------------------------
// 0x61AD90 sub_61AD90
// ------------------------------------------------------------
int /*thiscall*/ sub_61AD90(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint8_t *)(this + 973) = 0;
  *(uint32_t *)(this + 976) = -1;
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1040) = 0;
  *(uint32_t *)(this + 1044) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61ADE0 sub_61ADE0
// ------------------------------------------------------------
int /*thiscall*/ sub_61ADE0(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 260;
  for ( i = 2; i != 0; --i )
  {
    if ( *v1 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61AE10 sub_61AE10
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_61AE10(uint8_t *this, const char *ArgList, const char *a3)
{
  *(uint32_t *)this = &vftbl_CNRDParticle;
  sub_423A20((int)(this + 4));
  *(this + 108) = 0;
  *((uint32_t *)this + 26) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 1;
  *(this + 118) = 0;
  *(this + 117) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 30) = 0;
  sub_529CE0((int)this);
  sub_529D20(this, ArgList, a3);
  return this;
}



// ------------------------------------------------------------
// 0x61AE90 CNNapalmBomb__vmt2A8
// ------------------------------------------------------------
char /*thiscall*/ CNNapalmBomb__vmt2A8(int this, int a2)
{
  int v3; // eax
  char *v4; // eax
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  float v9; // [esp+8h] [ebp-4h]

  CNRDPassiveObject__vmt2A8((uint32_t *)this, a2);
  LOBYTE(v3) = *(uint8_t *)(this + 973);
  if ( (uint8_t)v3 == 0 )
  {
    if ( a2 != 0 )
      *(uint32_t *)(this + 976) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 388))(a2);
    v4 = (char *)sub_47E720(2, 0x35u);
    v5 = *(uint32_t *)(this + 704);
    v6 = v4;
    v9 = (float)sub_47EF20(v4, 1u, v5, -1, -1, 11);
    *(float *)(this + 988) = v9 / (double)sub_47EF20(v6, 1u, 1, -1, -1, 11);
    *(uint32_t *)(this + 992) = sub_47EF20(v6, 2u, v5, -1, -1, 11) / 2;
    *(float *)(this + 724) = (float)sub_47EFD0(
                                      v6,
                                      COERCE_FLOAT(5),
                                      v5,
                                      *(uint32_t *)(this + 976),
                                      *(uint32_t *)(this + 976),
                                      0);
    v7 = sub_47E9D0(v6, 0);
    sub_607260((uint32_t *)(this + 996), v7, -1, 1, 0);
    *(float *)(this + 1020) = (double)sub_47EF20(v6, 3u, v5, -1, -1, 11) * 0.1;
    v3 = sub_47EF20(v6, 4u, v5, -1, -1, 11);
    *(float *)(this + 1024) = (double)v3 * 0.1;
    *(uint8_t *)(this + 973) = 1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61AFC0 CNNapalmBomb__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNNapalmBomb__vmt10(int this)
{
  bool v2; // cc
  int v3; // ecx
  double v4; // st7
  int v5; // ecx
  uint64_t v6; // rax
  int v7; // eax
  int i; // esi
  int result; // eax
  int v10; // [esp-8h] [ebp-18h]
  int v11; // [esp-8h] [ebp-18h]
  uint32_t v12[2]; // [esp+8h] [ebp-8h]

  CNRDPassiveObject__vmt10((uint8_t *)this);
  v12[0] = 255;
  v2 = sub_699000(this + 36) < *(uint32_t *)(this + 1016) - 1000;
  v3 = this + 36;
  if ( v2 )
  {
    v2 = sub_699000(v3) <= *(uint32_t *)(this + 984) + 1000;
    v5 = this + 36;
    if ( !v2 )
    {
      v7 = sub_699000(v5);
      LODWORD(v6) = sub_42B420(255, 128, -1000 - *(uint32_t *)(this + 984) + v7, 500);
      goto LABEL_7;
    }
    v11 = sub_699000(v5) - *(uint32_t *)(this + 984);
    v4 = sub_4049C0(0.0, 255.0, v11, 1000);
  }
  else
  {
    v10 = 1000 - *(uint32_t *)(this + 1016) + sub_699000(v3);
    v4 = sub_4049C0(255.0, 0.0, v10, 1000);
  }
  v6 = (uint64_t)v4;
  v12[0] = (uint64_t)v4;
LABEL_7:
  v12[1] = v6;
  for ( i = 0; i < 2; ++i )
  {
    sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 144) + i * 4));
    result = sub_491F80(-1, -1, -1, v12[i], 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61B0D0 sub_61B0D0
// ------------------------------------------------------------
char /*usercall*/ sub_61B0D0@<al>(int a1@<ecx>, int a2@<ebx>)
{
  uint32_t *v3; // eax
  int v4; // eax
  uint32_t *v5; // ecx
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  float v11; // [esp+4h] [ebp-20h] BYREF
  float v12; // [esp+8h] [ebp-1Ch]
  int v13; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+18h] [ebp-Ch]
  int v17; // [esp+1Ch] [ebp-8h]
  uint32_t *v18; // [esp+20h] [ebp-4h] BYREF

  LOBYTE(v3) = *(uint8_t *)(a1 + 980);
  if ( (uint8_t)v3 != 0 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
    if ( (uint8_t)v3 != 0 )
    {
      v4 = sub_699000(a1 + 36);
      LOBYTE(v3) = sub_6072C0((uint8_t *)(a1 + 996), v4);
      if ( (uint8_t)v3 != 0 )
      {
        v5 = *(uint32_t **)(a1 + 1032);
        v3 = (uint32_t *)*v5;
        v18 = (uint32_t *)*v5;
        if ( v18 != v5 )
        {
          do
          {
            v6 = v3[3];
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 624))(v6) != 0 )
            {
              v7 = *(uint32_t *)v6;
              v11 = 0.0;
              v12 = 0.0;
              v13 = 0;
              v14 = 0;
              v15 = 0;
              v16 = 0;
              v8 = (*(int (/*thiscall*/ **)(int))(v7 + 120))(v6);
              v9 = *(uint32_t *)v6;
              v17 = v8;
              v11 = (float)v8;
              v17 = (*(int (/*thiscall*/ **)(int))(v9 + 124))(v6);
              v12 = (float)v17;
              v13 = 0;
              sub_4E5F70(a2, a1, v6, &v11, 1, 1);
            }
            sub_41C5E0(&v18);
            v3 = v18;
          }
          while ( v18 != *(uint32_t **)(a1 + 1032) );
        }
      }
    }
  }
  return (char)v3;
}



// ------------------------------------------------------------
// 0x61B1C0 CNNapalmBomb__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNNapalmBomb__vmt12C(int **this, int a2)
{
  int **v2; // edi
  int *v4; // ecx
  int v5; // eax
  int result; // eax
  int v7; // ebx
  int v8; // [esp+8h] [ebp-4h] BYREF

  v2 = (int **)a2;
  CNRDPassiveObject__vmt12C(this, a2);
  if ( v2 == this )
  {
    v4 = *(this + 258);
    v5 = *v4;
    a2 = *v4;
    if ( (int *)a2 != v4 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v5 + 16) + 76))(*(uint32_t *)(v5 + 16), 0);
        sub_41C5E0(&a2);
        v5 = a2;
      }
      while ( (int *)a2 != *(this + 258) );
    }
    return ((int (/*thiscall*/ *)(int **, int))(*this)[54])(this, 10000);
  }
  else
  {
    result = sub_4BE520(&v8, &a2);
    v7 = v8;
    if ( (int *)v8 != *(this + 258) )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v8 + 16) + 76))(*(uint32_t *)(v8 + 16), 0);
      return sub_4C20A0(&a2, v7);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61B260 sub_61B260
// ------------------------------------------------------------
char /*thiscall*/ sub_61B260(uint8_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  unsigned int v5; // esi
  int v6; // ecx
  int v7; // edx
  uint32_t *v8; // eax
  int **v9; // esi
  uint32_t *v10; // eax
  void **v11; // esi
  void (/*thiscall*/ **v12)(void **, int, int, uint32_t); // edx
  int v13; // edx
  int v14; // eax
  int **v15; // ebx
  int **v16; // esi
  int v18; // [esp+8h] [ebp-44h]
  float v19; // [esp+10h] [ebp-3Ch]
  uint32_t v20[2]; // [esp+20h] [ebp-2Ch] BYREF
  char v21[4]; // [esp+28h] [ebp-24h] BYREF
  int **v22; // [esp+2Ch] [ebp-20h] BYREF
  void *Block; // [esp+30h] [ebp-1Ch] BYREF
  int i; // [esp+34h] [ebp-18h]
  int **v25; // [esp+38h] [ebp-14h] BYREF
  int v26; // [esp+3Ch] [ebp-10h]
  int v27; // [esp+48h] [ebp-4h]

  LOBYTE(v2) = *(this + 980);
  if ( (uint8_t)v2 != 0 )
  {
    v3 = *((uint32_t *)this + 29);
    v4 = *(uint32_t *)(v3 + 120);
    v2 = v3 + 116;
    v5 = 0;
    if ( v4 != 0 )
    {
      v2 = (*(uint32_t *)(v2 + 8) - v4) >> 2;
      v26 = v2;
    }
    else
    {
      v26 = 0;
    }
    for ( i = 0; i < v26; ++i )
    {
      v6 = *((uint32_t *)this + 29);
      v7 = *(uint32_t *)(v6 + 120);
      if ( v7 != 0 && v5 < (*(uint32_t *)(v6 + 124) - v7) >> 2 )
        v8 = *(uint32_t **)(v7 + 4 * v5);
      else
        v8 = nullptr;
      v9 = (int **)__RTDynamicCast(
                     v8,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDActiveObject `RTTI Type Descriptor',
                     0);
      v22 = v9;
      if ( v9 != nullptr )
      {
        Block = v9;
        sub_4BE520(&v25, &Block);
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int **, uint32_t))(*(uint32_t *)this + 8))(this, v9, 0) <= *((uint32_t *)this + 248)
          && (uint8_t)sub_4E4630(v9) != 0
          && ((int (/*thiscall*/ *)(int **))(*v9)[32])(v9) <= 0 )
        {
          if ( v25 == *((int ***)this + 258) )
          {
            v10 = operator new(0x7Cu);
            Block = v10;
            v27 = 0;
            if ( v10 != nullptr )
            {
              *(float *)&v18 = -*((float *)this + 255);
              v11 = (void **)sub_4B3DF0(v10, 8, 1, v18, 0, 0);
            }
            else
            {
              v11 = nullptr;
            }
            v12 = (void (/*thiscall*/ **)(void **, int, int, uint32_t))*v11;
            v19 = -*((float *)this + 256);
            v27 = -1;
            v12[30](v11, 6, 1, LODWORD(v19));
            v13 = *(uint32_t *)this;
            Block = *v11;
            v14 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int))(v13 + 576))(this, 0, 0, 0, -1);
            v15 = v22;
            (*((void (/*thiscall*/ **)(void **, int **, int))Block + 14))(v11, v22, v14);
            v20[0] = v15;
            v20[1] = v11;
            sub_5FA510(v21, v20);
          }
        }
        else
        {
          v16 = v25;
          if ( v25 != *((int ***)this + 258) )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v25[4] + 76))(v25[4], 0);
            sub_4C20A0((uint32_t *)this + 257, &v22, v16);
          }
        }
      }
      LOBYTE(v2) = v26;
      v5 = i + 1;
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x61B440 sub_61B440
// ------------------------------------------------------------
int /*thiscall*/ sub_61B440(int this)
{
  int v2; // eax
  int v3; // eax
  int i; // esi
  int *v5; // edi
  bool v6; // zf
  int result; // eax
  int Block; // [esp+Ch] [ebp-14h]
  uint32_t *v9; // [esp+10h] [ebp-10h]

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v2 = sub_4C3640(this + 364, "Particle/NapalmBombFire.ptl", this);
    else
      v2 = sub_4C3640(*(uint32_t *)(this + 364), "Particle/NapalmBombFire.ptl", this);
  }
  else
  {
    v2 = 0;
  }
  *(uint32_t *)(this + 1040) = v2;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v3 = sub_4C3640(this + 364, "Particle/NapalmBombFireLight.ptl", this);
    else
      v3 = sub_4C3640(*(uint32_t *)(this + 364), "Particle/NapalmBombFireLight.ptl", this);
  }
  else
  {
    v3 = 0;
  }
  *(uint32_t *)(this + 1044) = v3;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 12))(v3, 500);
  v9 = (uint32_t *)(this + 1040);
  Block = 2;
  do
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*v9 + 112))(*v9, this);
    for ( i = 12; i < 24; i += 4 )
    {
      v5 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v9 + 36))(*v9) + i);
      *v5 = (uint64_t)((double)*v5 * *(float *)(this + 988));
    }
    result = Block - 1;
    v6 = Block == 1;
    ++v9;
    --Block;
  }
  while ( !v6 );
  return result;
}



// ------------------------------------------------------------
// 0x61B590 sub_61B590
// ------------------------------------------------------------
void /*thiscall*/ sub_61B590(int *this, int a2, float a3, int a4, int a5)
{
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  char *v10; // eax
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // ecx
  int *v20; // edi
  int v21; // edi
  int v22; // eax
  uint32_t *v23; // eax
  int v24; // ecx
  int *v25; // edi
  int v26; // edi
  int v27; // edx
  uint32_t *v28; // eax
  int v29; // [esp-10h] [ebp-130h]
  int v30; // [esp-10h] [ebp-130h]
  float v31; // [esp+0h] [ebp-120h]
  float v32; // [esp+4h] [ebp-11Ch]
  int v33; // [esp+Ch] [ebp-114h]
  int v34; // [esp+Ch] [ebp-114h]
  char Buffer[256]; // [esp+10h] [ebp-110h] BYREF
  int v36; // [esp+110h] [ebp-10h]
  int v37; // [esp+11Ch] [ebp-4h]
  int v38; // [esp+130h] [ebp+10h]
  int v39; // [esp+134h] [ebp+14h]

  v36 = dword_796E50;
  v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
  if ( (int)sub_499240(v6, v29, a2, SLODWORD(a3), 0) <= a5 )
  {
    if ( a4 != 0 )
    {
      if ( a4 == 1 )
      {
        v15 = rand();
        *(float *)&v38 = sub_4049C0(0.69999999, 1.0, v15 % 100, 99);
        v16 = rand();
        *(float *)&v39 = sub_4049C0(0.69999999, 1.0, v16 % 100, 99);
        v30 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
        v17 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        v18 = 2 * sub_499240(v17, v30, a2, SLODWORD(a3), 0);
        v37 = 3;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            LOBYTE(v19) = (uint8_t)this + 108;
          else
            v19 = *(this + 91);
          v20 = (int *)sub_431920(v19, (char)"Animation/NapalmBombAreaFire1.ani", 1);
        }
        else
        {
          v20 = nullptr;
        }
        *(uint32_t *)(sub_4924C0(v20, 0) + 48) = v18;
        v37 = 4;
        if ( sub_44B6C0(284) != 0 )
          v21 = sub_44E1F0(v20, 1);
        else
          v21 = 0;
        v22 = *(uint32_t *)v21;
        v37 = -1;
        v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(v22 + 200))(v21, v38, v39);
        sub_4920E0(v23, v31, v32);
        sub_45FE80(*(this + 29), v21, 2, 0, v21, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 112))(v21, a2);
        v37 = 5;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            LOBYTE(v24) = (uint8_t)this + 108;
          else
            v24 = *(this + 91);
          v25 = (int *)sub_431920(v24, (char)"Animation/NapalmBombAreaFire2.ani", 1);
        }
        else
        {
          v25 = nullptr;
        }
        *(uint32_t *)(sub_4924C0(v25, 0) + 48) = v18;
        v37 = 6;
        if ( sub_44B6C0(284) != 0 )
          v26 = sub_44E1F0(v25, 1);
        else
          v26 = 0;
        v27 = *(uint32_t *)v26;
        v37 = -1;
        v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(v27 + 200))(v26, v38, v39);
        sub_4920E0(v28, a3, 0.0);
        sub_45FE80(*(this + 29), v26, 2, 0, v26, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 112))(v26, a2);
      }
    }
    else
    {
      v7 = rand() % 2;
      sprintf(Buffer, "%s%d.ani", "Animation/NapalmBombFireLight", v7 + 1);
      v33 = sub_42FCB0(228);
      v8 = 0;
      v37 = 0;
      if ( v33 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v9) = (uint8_t)this + 108;
        else
          v9 = *(this + 91);
        v8 = sub_431920(v9, (char)Buffer, 1);
      }
      v37 = -1;
      v10 = (char *)sub_44B6C0(284);
      v11 = (int)v10;
      v37 = 1;
      if ( v10 != nullptr )
      {
        sub_44E0D0(v10, v8, 0);
        *(uint32_t *)v11 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v11 = 0;
      }
      v37 = -1;
      v34 = sub_445D00(156);
      v37 = 2;
      if ( v34 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          v12 = sub_61AE10((uint8_t)this + 108, (int)"Particle/NapalmBombAreaFireLight.ptl");
        else
          v12 = sub_61AE10(*(this + 91), (int)"Particle/NapalmBombAreaFireLight.ptl");
      }
      else
      {
        v12 = 0;
      }
      v13 = *(uint32_t *)v12;
      v37 = -1;
      *(uint32_t *)(*(int (/*thiscall*/ **)(int))(v13 + 16))(v12) = a2;
      *(float *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 16))(v12) + 4) = a3;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 16))(v12) + 8) = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 60))(v11);
      sub_4A0B60(v14, v12);
      sub_45FE80(*(this + 29), v12, 2, 0, v11, 0, 0);
    }
  }
}


// ------------------------------------------------------------
// 0x61B980 CNNapalmBomb__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ sub_61B980(uint32_t *this)
{
  uint32_t *v2; // edi
  int i; // ebx
  int v4; // eax
  int **v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // edi
  bool v11; // zf
  char *v12; // eax
  int v13; // ebx
  char *v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // edx
  int v23; // ebx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int v28; // ebx
  int v29; // edi
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edi
  int v34; // eax
  int v35; // eax
  float v37; // [esp-Ch] [ebp-40h]
  float v38; // [esp-Ch] [ebp-40h]
  float v39; // [esp-4h] [ebp-38h]
  char v40[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  uint32_t *v42; // [esp+14h] [ebp-20h]
  int v43; // [esp+18h] [ebp-1Ch]
  int v44; // [esp+1Ch] [ebp-18h]
  int v45; // [esp+20h] [ebp-14h] BYREF
  int v46; // [esp+24h] [ebp-10h]
  int v47; // [esp+30h] [ebp-4h]

  sub_600890();
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v46 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(this + 28) + 104) + 16))(*(uint32_t *)(*(this + 28) + 104))
                    + 76);
    v2 = this + 260;
    for ( i = 2; i != 0; --i )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v2 + 28))(*v2);
      ++v2;
      *(uint32_t *)(v4 + 76) = v46;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
    *((uint8_t *)this + 972) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0 )
  {
    if ( *((uint8_t *)this + 980) == 0 )
    {
      v12 = (char *)sub_47E720(2, 53);
      v13 = *(this + 176);
      v14 = v12;
      sub_424120(*(uint32_t **)(*(this + 29) + 132), 4, 400);
      sub_4A0B60(0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        v46 = sub_47EFD0(v14, 0.0, v13, *(this + 244), *(this + 244), 0);
        v45 = sub_47EF20(1, v13, -1, -1, 11);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*this + 580))(
          this,
          22210,
          v46,
          0,
          0,
          0,
          0,
          0,
          4,
          0,
          2,
          &v45);
      }
      sub_607280(this + 249);
      v15 = sub_47EF20(6, v13, -1, -1, 11);
      v16 = sub_699000((int)(this + 9));
      v17 = *(this + 248) * *(this + 248);
      *(this + 254) = v16 + v15;
      sub_607260((int)sub_4C4B40 / (4 * dword_7930D4[0] * v17 / 100), -1, 0, 1);
      sub_607280(this + 262);
      v18 = dword_73C5C8[dword_9A0114];
      v46 = 0;
      if ( v18 > 0 )
      {
        do
        {
          v19 = *(this + 248) - 20;
          v20 = v19 * dword_7930D4[0] / 100;
          v21 = rand();
          v22 = *this;
          v44 = v21 % (2 * v20 + 1) - v20;
          LODWORD(v37) = (*(int (/*thiscall*/ **)(uint32_t *))(v22 + 124))(this) + v44;
          v23 = rand() % (2 * v19 + 1) - v19;
          v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          sub_61B590(v24 + v23, v37, 1, v19);
          v25 = dword_73C5C8[dword_9A0114];
          ++v46;
        }
        while ( v46 < v25 );
      }
      *(float *)&v44 = (double)(int)*(this + 248) * 0.0044444446;
      sub_4922F0(*(float *)&v44);
      sub_4922F0(*(float *)&v44);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        0,
        *(uint32_t *)*(this + 36),
        0,
        0,
        0,
        1);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
        this,
        1,
        *(uint32_t *)(*(this + 36) + 4),
        0,
        0,
        0,
        1);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "SIZZLE_LOOP",
        10000,
        0,
        0);
      *((uint8_t *)this + 980) = 1;
      *(this + 246) = sub_699000((int)(this + 9));
    }
  }
  else
  {
    v5 = (int **)(this + 260);
    v46 = 2;
    do
    {
      v6 = **v5;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int *, int))(v6 + 40))(*v5, v9);
      (*(void (/*thiscall*/ **)(int *, char *))(**v5 + 92))(*v5, v40);
      v10 = Block;
      v47 = 0;
      if ( Block != v42 )
      {
        do
        {
          v39 = *((float *)this + 247);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v10 + 200))(*v10);
          sub_4922F0(v39);
          ++v10;
        }
        while ( v10 != v42 );
      }
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v40);
      v47 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++v5;
      v11 = v46 == 1;
      Block = nullptr;
      v42 = nullptr;
      v43 = 0;
      --v46;
    }
    while ( !v11 );
  }
  sub_61B260(this);
  sub_61B0D0(this);
  LOBYTE(v26) = *((uint8_t *)this + 980);
  if ( (uint8_t)v26 != 0 )
  {
    if ( sub_699000((int)(this + 9)) < *(this + 254) - 1500 )
    {
      v27 = sub_699000((int)(this + 9));
      if ( (uint8_t)sub_6072C0(v27) != 0 )
      {
        do
        {
          v28 = *(this + 248);
          v29 = v28 * dword_7930D4[0] / 100;
          v30 = rand();
          v31 = *this;
          v44 = v30 % (2 * v29 + 1) - v29;
          v32 = (*(int (/*thiscall*/ **)(uint32_t *))(v31 + 124))(this);
          LODWORD(v38) = v32 + v44;
          v33 = rand() % (2 * v28 + 1) - v28;
          v34 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          sub_61B590(v34 + v33, v38, 0, v28);
          v35 = sub_699000((int)(this + 9));
        }
        while ( (uint8_t)sub_6072C0(v35) != 0 );
      }
    }
    LOBYTE(v26) = *((uint8_t *)this + 980);
    if ( (uint8_t)v26 != 0 )
    {
      v26 = sub_699000((int)(this + 9));
      if ( v26 >= *(this + 254) )
        LOBYTE(v26) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return v26;
}


// ------------------------------------------------------------
// 0x61BE30 sub_61BE30
// ------------------------------------------------------------
void /*thiscall*/ sub_61BE30(uint8_t *this)
{
  *(this + 972) = 0;
}



// ------------------------------------------------------------
// 0x61BE50 CNTargetItBall__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNTargetItBall__vmt1F4(int *this, uint32_t *Block, float *a3, char a4)
{
  int v6; // eax
  int v7; // eax
  bool v8; // bl
  double v9; // st7
  int v10; // eax
  void *v11; // ecx
  void *v13[4]; // [esp+8h] [ebp-20h] BYREF
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]
  void *Blocka; // [esp+30h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*Block + 40))(Block, 17) != 0
    && *((uint8_t *)this + 972) == 0
    && a4 == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
    if ( __RTDynamicCast(v6, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0) != 0 )
    {
      sub_5DDBA0(Block);
      if ( dword_9B9410 == 0 )
      {
        v15 = 0;
        if ( operator new(0x12Cu) != nullptr )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            v7 = sub_4C3640(this + 91, "Particle/TargetItBallPaint.ptl", 0);
          else
            v7 = sub_4C3640(*(this + 91), "Particle/TargetItBallPaint.ptl", 0);
        }
        else
        {
          v7 = 0;
        }
        v15 = -1;
        dword_9B9410 = v7;
      }
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t *))(*this + 660))(this, Block) == 1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_9B9410 + 28))(dword_9B9410) + 84) = v8;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_9B9410 + 12))(dword_9B9410, 0);
      Blocka = (void *)(uint64_t)(a3[3] * 0.5 + *a3);
      v9 = a3[5] * 0.5 + a3[2];
      v14 = *(uint32_t *)dword_9B9410;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*Block + 124))(Block, (uint64_t)v9);
      (*(void (/*thiscall*/ **)(int, void *, int))(v14 + 40))(dword_9B9410, Blocka, v10 + 1);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_9B9410 + 92))(dword_9B9410, v13);
      v11 = (void *)*(this + 29);
      v15 = 1;
      sub_4600B0(v11, 2, 0, (int)v13);
      v15 = -1;
      sub_5E5260(v13);
    }
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, Block, a3, a4);
}



// ------------------------------------------------------------
// 0x61C020 CNHunterSpittle__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNHunterSpittle__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNHunterMaster `RTTI Type Descriptor', 0) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
    *((uint8_t *)this + 972) = 1;
  }
  if ( *(this + 30) == *(uint32_t *)*(this + 36) )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)v3 != 0 )
    {
      LOBYTE(v3) = *(uint8_t *)(*(this + 30) + 170);
      if ( (uint8_t)v3 != 0 )
      {
        LOBYTE(v3) = *((uint8_t *)this + 264);
        if ( (uint8_t)v3 == 0 )
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  else
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    if ( v3 <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);
      *(uint32_t *)(v3 + 16) = 1000;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61C0F0 CNHunterSpittle__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNHunterSpittle__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax
  int v6; // ebx
  char *v7; // eax
  char *v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax

  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 340))(this) == 30017 )
  {
    v5 = sub_42FCB0(228);
    v6 = v5 != 0 ? sub_431860(v5, "PassiveObject/Monster/Spider/Ani/PoisonWebLand.ani", 1) : 0;
    if ( v6 != 0 )
    {
      v7 = (char *)sub_44B6C0(284);
      v8 = v7;
      if ( v7 != nullptr )
      {
        sub_44E0D0(v7, v6, 1);
        *(uint32_t *)v8 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v8 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v8, 2, 0, (int)v8, (int)this, 0);
      v9 = *(uint32_t *)v8;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
      (*(void (/*thiscall*/ **)(char *, int))(v9 + 112))(v8, v12);
      v13 = *(uint32_t *)v8;
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v13 + 144))(v8, v14);
    }
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61C210 CNZombieEye__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNZombieEye__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 43739);
}



// ------------------------------------------------------------
// 0x61C240 CNZombieEye__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNZombieEye__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v4; // eax
  int v6; // eax
  int v8; // [esp-18h] [ebp-28h]
  int v9; // [esp-14h] [ebp-24h]
  int v10; // [esp-10h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-4h] BYREF

  v4 = *a2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v4 + 648))(a2, &v11, this);
  if ( ((*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 44))(a2) == 273
     || (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 44))(a2) == 529)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0
    && a4 == 0
    && v11 > 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    sub_4E4A50(*(this + 173), 30005, 0, v6, v8, v9, v10, 0, 0, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61C300 CNZombieEyeExplode__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNZombieEyeExplode__vmt14C(uint8_t *this)
{
  int result; // eax

  if ( *(this + 972) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "ZOMBIE_EYEEXPLOTION",
      -1,
      0,
      0);
    *(this + 972) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C360 sub_61C360
// ------------------------------------------------------------
int /*thiscall*/ sub_61C360(float *this, int a2)
{
  uint32_t *v3; // eax
  int result; // eax

  v3 = *((uint32_t **)this + 36);
  *(this + 181) = (float)a2;
  result = (*(int (/*thiscall*/ **)(float *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
             this,
             1,
             *v3,
             0,
             0,
             0,
             0);
  *((uint8_t *)this + 972) = 0;
  *((uint8_t *)this + 973) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61C3A0 CNZombieEye__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNZombieEye__vmt14C(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) != 0 )
    goto LABEL_10;
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNZombieHollowEye `RTTI Type Descriptor', 0) != 0 )
  {
    v3 = *(this + 139);
LABEL_8:
    (*(void (/*stdcall*/ **)(int))(*this + 344))(v3);
    goto LABEL_9;
  }
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v4, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNZombieGhoulgwish `RTTI Type Descriptor', 0) != 0 )
  {
    v3 = *(this + 139) + 152;
    goto LABEL_8;
  }
  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
  if ( __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNKalkazak `RTTI Type Descriptor', 0) != 0 )
  {
    v3 = *(this + 139) + 304;
    goto LABEL_8;
  }
LABEL_9:
  *((uint8_t *)this + 972) = 1;
LABEL_10:
  result = *((uint8_t *)this + 973);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "ZOMBIE_EYEROLLING_LOOP",
               43739,
               0,
               0);
    *((uint8_t *)this + 973) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C490 sub_61C490
// ------------------------------------------------------------
int /*thiscall*/ sub_61C490(uint32_t *this)
{
  uint32_t *v2; // eax
  int v3; // edx
  int result; // eax

  v2 = (uint32_t *)*(this + 36);
  v3 = *this;
  *(this + 181) = 0;
  result = (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v3 + 204))(1, *v2, 0, 0, 0, 0);
  *((uint8_t *)this + 972) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61C4D0 CNKagelBomb__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNKagelBomb__vmt200(int *this, int a2, float *a3, int a4)
{
  int v6; // edi
  int v7; // eax
  uint16_t *v8; // eax
  uint16_t *v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // esi
  int v17; // esi
  int v18; // eax
  int v19; // esi
  int v20; // eax
  int *v22; // [esp+Ch] [ebp-6Ch]
  uint32_t v23[26]; // [esp+10h] [ebp-68h] BYREF
  int v24; // [esp+80h] [ebp+8h]

  v23[25] = dword_796E50;
  v24 = CNRDPassiveObject__vmt200(this, a2, a3, a4);
  if ( a2 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v22 = (int *)v6;
  }
  else
  {
    v22 = nullptr;
    v6 = 0;
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( v6 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 273) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) == 1
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
  {
    sub_423A20((int)v23);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
    v8 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v7 + 104) + 16))(*(uint32_t *)(v7 + 104));
    qmemcpy(v23, v8, 0x60u);
    v9 = v8 + 48;
    v10 = *v22;
    LOWORD(v23[24]) = *v9;
    v11 = (*(int (/*thiscall*/ **)(int *))(v10 + 120))(v22);
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v11 )
      v12 = 135 - rand() % 20;
    else
      v12 = rand() % 20 + 45;
    v13 = *this;
    *(uint32_t *)((char *)&v23[3] + 3) = 300;
    *(uint32_t *)((char *)&v23[4] + 3) = 300;
    *(uint32_t *)((char *)&v23[7] + 3) = 0;
    *(uint32_t *)((char *)&v23[8] + 3) = 0;
    v23[18] = 0;
    v23[19] = v12;
    a4 = (*(int (/*thiscall*/ **)(int *))(v13 + 120))(this);
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v15 = *this;
    a3 = (float *)v14;
    v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 128))(this) + 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, float *, uint32_t))(*this + 136))(this, a4, a3, 0) != 0
      || (*(uint8_t (/*thiscall*/ **)(int *, int *, float **, int, float *, int, int, int))(*this + 140))(
           this,
           &a4,
           &a3,
           a4,
           a3,
           100,
           1,
           1) != 0 )
    {
      v23[1] = a3;
      v23[0] = a4;
      v23[2] = v16;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v17 = *(uint32_t *)dword_8F8520;
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v17 + 36))(dword_8F8520, v18);
      v19 = *(uint32_t *)dword_8F8520;
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v23, 98);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return v24;
}



// ------------------------------------------------------------
// 0x61C7A0 CNKagelBomb__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNKagelBomb__vmt14C(uint32_t *this)
{
  uint32_t *v1; // edi
  int v2; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // edx
  int result; // eax
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp-14h] [ebp-1Ch]
  int v10; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt14C((int)this);
  v4 = (uint32_t *)*(this + 36);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  v6 = *this;
  if ( v5 == *v4 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 && *((uint8_t *)this + 264) != 1 )
      {
        v1 = (uint32_t *)*(this + 173);
        if ( v1 == nullptr )
          v1 = this;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
        v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        sub_4E4A50(v1, *(this + 243), 0, v2, v8, v9, v10, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 128))(this);
    if ( result <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) + 60) = 0;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
      *(uint32_t *)result = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61C830 sub_61C830
// ------------------------------------------------------------
int /*thiscall*/ sub_61C830(uint32_t *this, int a2)
{
  sub_4015C0("THROW_BOMB", 0xAu);
  *(this + 243) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x61C860 sub_61C860
// ------------------------------------------------------------
int /*thiscall*/ sub_61C860(uint32_t **this)
{
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
      this,
      2,
      **(this + 36),
      0,
      0,
      0,
      1);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
      this,
      1,
      (*(this + 36))[1],
      0,
      0,
      0,
      1);
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      1,
      (*(this + 36))[2],
      0,
      0,
      0,
      0);
  }
  return sub_4015C0("BOMB_EXPLOSION", 0xEu);
}



// ------------------------------------------------------------
// 0x61C8E0 CNKagelBombSub__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNKagelBombSub__vmt14C(int **this)
{
  uint32_t *v2; // edi
  int *v3; // eax
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int *v7; // eax
  int **v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *v13; // ecx
  bool v14; // zf
  int result; // eax
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *v20; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    v2 = operator new(0x12Cu);
    v20 = v2;
    v3 = nullptr;
    v21 = 0;
    if ( v2 != nullptr )
    {
      v4 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(v2, v4, (int)this);
    }
    *(this + 243) = v3;
    v5 = operator new(0x12Cu);
    v20 = v5;
    v21 = 1;
    if ( v5 != nullptr )
    {
      v6 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(v5, v6, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    v8 = this + 243;
    v20 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**v8 + 12))(*v8, 0);
      v9 = **v8;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*v8, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v8 + 92))(*v8, v16);
      v13 = *(this + 29);
      v21 = 2;
      sub_4600B0(v13, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++v8;
      v14 = v20 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      v20 = (char *)v20 - 1;
    }
    while ( !v14 );
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[50])(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
    if ( (uint8_t)result == 1 )
      return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61CA80 CNSpaceFishBug__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishBug__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax
  int i; // ebx
  int v8; // ebx
  int v9; // eax
  int v11; // [esp+8h] [ebp-4h] BYREF
  int v12; // [esp+14h] [ebp+8h]

  v5 = *a2;
  v11 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v5 + 648))(a2, &v11, this);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0
    && rand() % 100 < 40
    && a4 == 0
    && v11 > 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
  {
    sub_432FA0();
    for ( i = 170; i > 0; --i )
    {
      v12 = rand() % 17;
      if ( sub_496F80(v12) != 16 )
        break;
    }
    v8 = *a2;
    v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 684))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int))(v8 + 760))(a2, v12, 1120403456, *(this + 243), v9);
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61CB60 sub_61CB60
// ------------------------------------------------------------
int /*thiscall*/ sub_61CB60(int **this, int *a2)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // eax
  uint64_t v6; // rax
  int result; // eax
  float v8; // [esp+0h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-18h]

  v3 = 0;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )
  {
    case 3:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
      break;
    case 4:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
      break;
    case 6:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
      break;
    default:
      break;
  }
  v4 = *(uint32_t *)(v3 + 112);
  v5 = *(this + 87);
  v9 = (float)v5[1];
  v8 = (float)*v5;
  v6 = (uint64_t)sub_4049C0(v8, v9, v4 - 1, 98);
  *(this + 170) = (int *)v6;
  *(this + 171) = (int *)v6;
  result = sub_4015C0("SFISH_CAST", 0xAu);
  *(this + 243) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x61CC10 CNLOLLaser__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNLOLLaser__vmt14C(uint32_t *this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 980) != 0 && *(this + 243) + *(this + 244) < (unsigned int)sub_699000((int)(this + 9)) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
    *(this + 243) = sub_699000((int)(this + 9));
  }
  v2 = *(this + 30);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    LOBYTE(v2) = *((uint8_t *)this + 264);
    if ( (uint8_t)v2 == 0 )
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)v2 != 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x61CC90 CNLOLLaser__vmtC
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNLOLLaser__vmtC(int *this)
{
  uint32_t *result; // eax
  uint32_t *v3; // esi

  CNRDPassiveObject__vmtC(this);
  sub_4926A0(*(this + 30));
  sub_4938F0(*(this + 30));
  result = (uint32_t *)*(this + 32);
  v3 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      sub_4926A0(v3[3]);
      result = sub_4938F0(v3[3]);
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 32) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x61CCE0 CNLOLLaser__vmt2C4
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNLOLLaser__vmt2C4(uint32_t **this, int a2)
{
  int v2; // ebx
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // edx
  uint32_t *result; // eax

  v2 = a2;
  if ( a2 > 0 )
  {
    v4 = 0;
    do
    {
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        0,
        **(this + 36),
        v4,
        0,
        0,
        0);
      v4 += 100;
      --v2;
    }
    while ( v2 != 0 );
  }
  v5 = sub_699000((int)(this + 9));
  v6 = *this;
  *(this + 243) = (uint32_t *)v5;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t ***)(((int (/*thiscall*/ *)(uint32_t **))v6[85])(this) + 64);
  *(this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61CD50 sub_61CD50
// ------------------------------------------------------------
int /*thiscall*/ sub_61CD50(uint32_t *this, int a2)
{
  *(this + 243) = 0;
  *(this + 244) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x61CD70 CNBronzeGolemBullets__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNBronzeGolemBullets__vmt12C(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // [esp-20h] [ebp-28h]
  int v6; // [esp-1Ch] [ebp-24h]
  int v7; // [esp-18h] [ebp-20h]
  int v8; // [esp-14h] [ebp-1Ch]
  int v9; // [esp-10h] [ebp-18h]

  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this
    && *(this + 243) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v5 = *(this + 244);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    sub_4E4A50(v3, 30045, v5, v6, v7, v8, v9, 0, 0, 0);
  }
  if ( *(this + 243) == a2 )
  {
    v4 = *this;
    *(this + 243) = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 84))(this, 0);
  }
}



// ------------------------------------------------------------
// 0x61CE10 CNBronzeGolemBullets__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNBronzeGolemBullets__vmt1F4(int this, uint32_t *a2, float *a3, char a4)
{
  int v5; // edx
  int v6; // eax
  uint32_t *v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v13; // [esp-4h] [ebp-10h]
  int v14; // [esp+0h] [ebp-Ch]
  int v15; // [esp+18h] [ebp+Ch]
  int v16; // [esp+1Ch] [ebp+10h]

  if ( a4 != 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) == 0 )
    return CNRDPassiveObject__vmt1F4((int *)this, a2, a3, a4);
  v5 = *(uint32_t *)this;
  *(uint32_t *)(this + 972) = a2;
  v6 = (*(int (/*thiscall*/ **)(int))(v5 + 60))(this);
  v7 = (uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104)) + 15);
  *v7 = 0;
  v7[1] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = 0;
  v7[5] = 0;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 60))(this);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v8 + 104) + 4))(*(uint32_t *)(v8 + 104), 0);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
  v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 972) + 120))(*(uint32_t *)(this + 972));
  v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 972) + 124))(*(uint32_t *)(this + 972));
  v10 = *(uint32_t *)this;
  v15 = (uint64_t)(a3[5] * 0.5 + a3[2]);
  v13 = rand() % 6 + v15 - 3;
  v11 = rand();
  (*(void (/*thiscall*/ **)(int, int, int, int))(v10 + 112))(this, v11 % 6 + v9 - 3, v16, v13);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 60))(this, *(uint32_t *)(this + 972));
  sub_4A06D0(v14);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  return 0;
}



// ------------------------------------------------------------
// 0x61CF30 sub_61CF30
// ------------------------------------------------------------
int /*thiscall*/ sub_61CF30(uint8_t *this)
{
  *(this + 974) = 0;
  return sub_4015C0("G_ICEWAVE_MOVING", 0x10u);
}



// ------------------------------------------------------------
// 0x61CF50 CNIceWaveUp__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ sub_61CF50(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  int v11; // edx
  uint32_t *v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  void *v19; // ecx
  int v20; // edi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  void *v26; // ecx
  void *v27; // eax
  bool v28; // zf
  int result; // eax
  uint8_t v30[4]; // [esp+Ch] [ebp-3Ch] BYREF
  void *Block; // [esp+10h] [ebp-38h]
  uint8_t v32[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *v33; // [esp+20h] [ebp-28h]
  int v34; // [esp+24h] [ebp-24h]
  int v35; // [esp+28h] [ebp-20h]
  uint8_t v36[4]; // [esp+2Ch] [ebp-1Ch] BYREF
  void *v37; // [esp+30h] [ebp-18h]
  int v38; // [esp+34h] [ebp-14h]
  int v39; // [esp+38h] [ebp-10h]
  int v40; // [esp+44h] [ebp-4h]

  sub_600890();
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) != 0 )
  {
    if ( *((uint8_t *)this + 973) == 0 )
    {
      v5 = dword_8F82A4;
      v6 = *(uint32_t *)dword_8F82A4;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(v5, v9);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v5 + 92))(v5, v30);
      v10 = (void *)*(this + 29);
      v40 = 0;
      sub_4600B0(v10, 2, 0, (int)v30);
      v11 = *this;
      *((uint8_t *)this + 973) = 1;
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(v11 + 576))(this);
      if ( __RTDynamicCast(
             v12,
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNIceDoll_Sharedo `RTTI Type Descriptor',
             0) != nullptr )
        sub_4DB200(24, 0);
      v40 = -1;
      if ( Block != nullptr )
        j__free(Block);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    *((uint8_t *)this + 974) = 1;
  }
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v13 = *(this + 30);
    if ( v13 != 0 && *(int *)(v13 + 148) >= 6 )
    {
      v14 = dword_8F82A8;
      v15 = *(uint32_t *)dword_8F82A8;
      v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v16 + 20);
      v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v17);
      (*(void (/*thiscall*/ **)(int, int))(v15 + 40))(v14, v18);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v14 + 12))(v14, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v14 + 92))(v14, v36);
      v19 = (void *)*(this + 29);
      v40 = 1;
      sub_4600B0(v19, 2, 0, (int)v36);
      v20 = dword_8F82AC;
      v21 = *(uint32_t *)dword_8F82AC;
      v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v23 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v22 + 20);
      v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v23);
      (*(void (/*thiscall*/ **)(int, int))(v21 + 40))(v20, v24);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
      v25 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v20 + 92))(v20, v32);
      LOBYTE(v40) = 2;
      sub_4E77D0((int)v36, v25);
      LOBYTE(v40) = 1;
      if ( v33 != nullptr )
        j__free(v33);
      v26 = (void *)*(this + 29);
      v33 = nullptr;
      v34 = 0;
      v35 = 0;
      sub_4600B0(v26, 2, 0, (int)v36);
      v27 = v37;
      v28 = v37 == nullptr;
      *((uint8_t *)this + 972) = 1;
      v40 = -1;
      if ( !v28 )
        j__free(v27);
      v37 = nullptr;
      v38 = 0;
      v39 = 0;
    }
  }
  result = *(this + 30);
  if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( *((uint8_t *)this + 974) == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "ICEWAVE_CREATE",
               -1,
               0,
               0);
    *((uint8_t *)this + 974) = 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x61D1D0 sub_61D1D0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D1D0(uint8_t *this, int a2)
{
  int result; // eax

  result = a2;
  *(this + 972) = 0;
  *((uint32_t *)this + 244) = a2;
  if ( a2 != 0xFFFF )
  {
    result = dword_9B9418;
    if ( dword_9B9418 <= dword_795C54 )
    {
      ++dword_9B9418;
      *(this + 972) = 1;
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 84))(this, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D220 CNLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNLegOfLotus__vmt12C(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax

  if ( (uint32_t *)a2 == this && *(this + 244) != 0xFFFF && dword_9B9418 == 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);
    v4 = __RTDynamicCast(v3, 0, &IRDActiveObject `RTTI Type Descriptor', &CNLotus `RTTI Type Descriptor', 0);
    sub_5C9A00(v4);
  }
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x61D280 sub_61D280
// ------------------------------------------------------------
int /*thiscall*/ sub_61D280(uint8_t *this)
{
  int v1; // eax
  int result; // eax

  v1 = *(uint32_t *)this;
  *(this + 984) = 0;
  result = (*(int (**)(void))(v1 + 672))();
  *(uint8_t *)(result + 20) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61D2A0 CNPierceHeadLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNPierceHeadLegOfLotus__vmt12C(uint32_t *this, int a2)
{
  CNLegOfLotus__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x61D2B0 CNPierceHeadLegOfLotus__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNPierceHeadLegOfLotus__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 984) == 0 )
  {
    *(uint32_t *)(*(this + 28) + 36) = -3000;
    *(this + 245) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v2 = *this;
    *((uint8_t *)this + 984) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v2 + 212))(this, "LOTUS_THRUST", -1, 0, 0);
  }
  if ( *(int *)(*(this + 28) + 36) < 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 50 )
    *(uint32_t *)(*(this + 28) + 36) = (uint64_t)((double)1500 * 3.0);
  v3 = *(uint32_t *)(*(this + 28) + 36);
  if ( v3 >= 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    if ( v3 > *(this + 245) )
    {
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)v3 != 0 )
      {
        LOBYTE(v3) = *((uint8_t *)this + 264);
        if ( (uint8_t)v3 == 0 )
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61D380 sub_61D380
// ------------------------------------------------------------
int /*thiscall*/ sub_61D380(uint32_t **this)
{
  int v2; // edi
  int v3; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 252) + 192))(*(this + 252)) / 2;
  v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  return v3 - v2 <= 0 ? 0 : v3 - v2;
}



// ------------------------------------------------------------
// 0x61D3C0 CNGrabbingLegOfLotus__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt10(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  if ( result < 40 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    return (*(int (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D3F0 sub_61D3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D3F0(uint32_t *this)
{
  uint32_t *v1; // esi
  uint32_t *v2; // eax
  int v3; // edx

  v1 = this;
  v2 = (uint32_t *)*(this + 87);
  v3 = *this;
  *((uint8_t *)this + 984) = 0;
  *((uint8_t *)this + 985) = 0;
  *(this + 252) = 0;
  *(this + 247) = *v2;
  *(uint8_t *)((*(int (**)(void))(v3 + 672))() + 20) = 0;
  v1 += 253;
  *v1 = 0;
  v1[1] = 0;
  v1[2] = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61D440 sub_61D440
// ------------------------------------------------------------
int /*thiscall*/ sub_61D440(uint32_t *this)
{
  int v2; // ecx

  if ( (int)*(this + 251) <= 150 )
    *(uint32_t *)(*(this + 28) + 24) = dword_9B941C;
  else
    *(uint32_t *)(*(this + 28) + 24) = -1002733568;
  sub_4926A0(*(uint32_t *)(*(this + 36) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
  sub_4926A0(*(uint32_t *)(*(this + 36) + 8));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 8),
    0,
    -2,
    0,
    0);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 4), 1);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 8), 1);
  *(this + 248) = *(this + 247);
  v2 = *(this + 252);
  *(this + 249) = 0;
  *(this + 250) = 0;
  (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)v2 + 472))(v2, 9, 0, 1, 1);
  (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 564))(*(this + 252));
  return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 252) + 848))(*(this + 252), 1);
}



// ------------------------------------------------------------
// 0x61D540 sub_61D540
// ------------------------------------------------------------
char /*thiscall*/ sub_61D540(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax

  *(uint32_t *)(*(this + 28) + 24) = 0;
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, 150);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 112))(this, v4);
  sub_4939E0(*(uint32_t *)(*(this + 36) + 4), 0);
  return sub_4939E0(*(uint32_t *)(*(this + 36) + 8), 0);
}



// ------------------------------------------------------------
// 0x61D590 CNGrabbingLegOfLotus__vmt218
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt218(int *this, int a2)
{
  int result; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = a2;
  if ( a2 == *(this + 252) && *(this + 248) > 1 )
  {
    v4 = sub_491C10(*(uint32_t *)(*(this + 36) + 4));
    v5 = *(this + 250) + 1;
    *(this + 250) = v5;
    if ( v5 >= 5 * v4 / 1000 )
    {
      --*(this + 248);
      *(this + 250) = 0;
    }
    v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 120))(*(this + 252));
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 916))(*(this + 252));
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 120))(*(this + 252));
    v8 = *this;
    v9 = v6 - v7;
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
    return (*(int (/*thiscall*/ **)(int *, int))(v8 + 112))(this, v12 - v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61D650 CNGrabbingLegOfLotus__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt1F4(int this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 44))(a2) == 273
    && *(uint8_t *)(this + 985) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 948))(a2) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TRAP_OCTOPUS_CATCH",
      -1,
      0,
      0);
    *(uint32_t *)(this + 1004) = (uint64_t)a3[2];
    *(uint32_t *)(this + 1008) = a2;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 120))(a2);
    v6 = *(uint32_t *)(this + 1008);
    *(uint32_t *)(this + 1012) = v5;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 124))(v6);
    v8 = *(uint32_t *)(this + 1008);
    *(uint32_t *)(this + 1016) = v7;
    *(uint32_t *)(this + 1020) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 128))(v8);
    *(uint8_t *)(this + 985) = 1;
    sub_61D440((uint32_t *)this);
  }
  return CNRDPassiveObject__vmt1F4((int *)this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61D710 sub_61D710
// ------------------------------------------------------------
void /*thiscall*/ sub_61D710(uint32_t *this)
{
  int v2; // ecx
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  char v9[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v11; // [esp+Ch] [ebp-20h]
  int v12; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h] BYREF
  int v14; // [esp+18h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+1Ch] [ebp-10h] BYREF

  v2 = *(this + 252);
  if ( v2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 604))(v2, 1);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 612))(*(this + 252), 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 848))(*(this + 252), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 112))(
      *(this + 252),
      *(this + 253),
      *(this + 254),
      *(this + 255));
    v3 = *(this + 252);
    v4 = *this;
    v5 = (*(int (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)v3 + 124))(v3, 50, 0, 1);
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, v5);
    (*(void (/*thiscall*/ **)(uint32_t *, int *, uint32_t *, int))(v4 + 140))(this, &v14, v15, v6);
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 192))(*(this + 252)) / 2;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) - v7;
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int))(*(uint32_t *)*(this + 252) + 112))(
      *(this + 252),
      v14,
      v15[0],
      v8 <= 0 ? 0 : v8);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 308))(*(this + 252)) != 0 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v15[3] = 0;
      v13 = 4;
      sub_431230((int)v9, &v13);
      v13 = 0;
      sub_431230((int)v9, &v13);
      v13 = 1;
      sub_431230((int)v9, &v13);
      v13 = 200;
      sub_431230((int)v9, &v13);
      v13 = 200;
      sub_431230((int)v9, &v13);
      (*(void (/*thiscall*/ **)(uint32_t, int, char *, uint32_t, uint32_t))(*(uint32_t *)*(this + 252) + 560))(
        *(this + 252),
        4,
        v9,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 252) + 564))(*(this + 252));
      if ( Block != nullptr )
        j__free(Block);
    }
    *(this + 252) = 0;
  }
}



// ------------------------------------------------------------
// 0x61D8C0 sub_61D8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_61D8C0(int this)
{
  sub_61D710((uint32_t *)this);
  *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
  return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
}



// ------------------------------------------------------------
// 0x61D900 sub_61D900
// ------------------------------------------------------------
char /*usercall*/ sub_61D900@<al>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  bool v18; // cc
  float v20; // [esp+8h] [ebp-1Ch] BYREF
  float v21; // [esp+Ch] [ebp-18h]
  float v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]
  int v24; // [esp+18h] [ebp-Ch]
  int v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+20h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
  if ( v3 != 150 )
  {
    v18 = a1[251] <= 150;
    if ( (int)a1[251] < 150 )
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
      if ( v3 > 150 )
        goto LABEL_17;
      v18 = a1[251] <= 150;
    }
    if ( v18 )
      return v3;
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1);
    if ( v3 >= 150 )
      return v3;
LABEL_17:
    LOBYTE(v3) = sub_61D540(a1);
    return v3;
  }
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[252] + 840))(a1[252]);
  if ( v3 == 9 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 344))(a1, a1[139]);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
    if ( *(uint8_t *)(v3 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(
        a1,
        "TRAP_OCTOPUS_TIGHTEN",
        -1,
        0,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0 )
      {
        v4 = *a1;
        v20 = 0.0;
        v21 = 0.0;
        v22 = 0.0;
        v23 = 0;
        v24 = 0;
        v25 = 0;
        v26 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 120))(a1);
        v5 = *a1;
        v20 = (float)v26;
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 124))(a1);
        v7 = *a1;
        v26 = v6;
        v21 = (float)v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(a1);
        v9 = a1[252];
        v26 = v8;
        v22 = (float)v8;
        sub_4E5F70(a2, (int)a1, v9, &v20, 1, 1);
      }
      v10 = a1[248];
      v11 = a1[249] + 1;
      a1[249] = v11;
      if ( v11 >= v10 || (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[252] + 724))(a1[252]) != 0 )
      {
        LOBYTE(v3) = sub_61D8C0((int)a1);
      }
      else
      {
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
        LOBYTE(v3) = sub_4926A0(v12);
      }
    }
    v13 = a1[252];
    if ( v13 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 604))(v13, 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)a1[252] + 612))(a1[252], 1, 1);
      v14 = *(uint32_t *)a1[252];
      v15 = sub_61D380((uint32_t **)a1);
      v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, v15);
      v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v16 - 1);
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t, int))(v14 + 112))(a1[252], v17);
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61DAD0 CNGrabbingLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGrabbingLegOfLotus__vmt12C(int this, int a2)
{
  CNLegOfLotus__vmt12C((uint32_t *)this, a2);
  if ( a2 == *(uint32_t *)(this + 1008) )
  {
    sub_61D710((uint32_t *)this);
    *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
    *(uint32_t *)(this + 1008) = 0;
  }
  if ( a2 == this && *(uint32_t *)(this + 1008) != 0 )
    sub_61D710((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x61DB50 CNGrabbingLegOfLotus__vmt14C
// ------------------------------------------------------------
void /*usercall*/ CNGrabbingLegOfLotus__vmt14C(int a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax

  CNRDPassiveObject__vmt14C(a1);
  if ( *(uint8_t *)(a1 + 984) == 0 )
  {
    *(uint32_t *)(*(uint32_t *)(a1 + 112) + 24) = -1002733568;
    *(uint32_t *)(a1 + 980) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
    v3 = *(uint32_t *)a1;
    *(uint8_t *)(a1 + 984) = 1;
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v3 + 212))(a1, "TRAP_OCTOPUS_SWING", -1, 0, 0);
  }
  if ( *(uint32_t *)(a1 + 1008) != 0 )
  {
    sub_61D900((uint32_t *)a1, a2);
  }
  else
  {
    if ( *(float *)(*(uint32_t *)(a1 + 112) + 24) < 0.0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) <= 40 )
      sub_61D8C0(a1);
    if ( *(float *)(*(uint32_t *)(a1 + 112) + 24) >= 0.0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) > *(uint32_t *)(a1 + 980)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0
      && *(uint8_t *)(a1 + 264) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x61DC20 CNGrabbingLegOfLotus__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNGrabbingLegOfLotus__vmt200(int this, int a2, float *a3, char a4)
{
  int v5; // eax

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( *(uint8_t *)(v5 + 16) != 0 || *(float *)v5 > 0.0 )
  {
    sub_61D710((uint32_t *)this);
    *(uint32_t *)(*(uint32_t *)(this + 112) + 24) = dword_9B941C;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
  }
  return CNRDPassiveObject__vmt200((int *)this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61DCA0 CNRisingShuriken__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRisingShuriken__vmtC(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmtC(this);
  result = *(this + 28);
  *(uint32_t *)(result + 36) = 2000;
  return result;
}



// ------------------------------------------------------------
// 0x61DCC0 CNRisingShuriken__vmt14C
// ------------------------------------------------------------
char /*usercall*/ CNRisingShuriken__vmt14C@<al>(uint8_t *a1@<ecx>, int a2@<edi>)
{
  int v3; // eax
  DWORD TickCount; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // edi
  int v8; // edx
  int v10; // [esp+4h] [ebp-70h]
  int v11; // [esp+8h] [ebp-6Ch]
  uint8_t v12[68]; // [esp+Ch] [ebp-68h] BYREF
  int v13; // [esp+50h] [ebp-24h]
  int v14; // [esp+61h] [ebp-13h]
  char v15; // [esp+65h] [ebp-Fh]
  int v16; // [esp+70h] [ebp-4h]

  v16 = dword_796E50;
  CNRDPassiveObject__vmt14C((int)a1);
  v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1);
  if ( v3 >= 500 )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1);
    if ( (uint8_t)v3 != 0 )
    {
      LOBYTE(v3) = a1[264];
      if ( (uint8_t)v3 == 0 )
      {
        TickCount = GetTickCount();
        srand(TickCount);
        v11 = 2 * (rand() % 100 < 10) + 1;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 120))(a1, a2);
        v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 124))(a1);
        if ( *((int *)a1 + 243) > -1 )
        {
          v6 = sub_45EBE0(*((uint32_t **)a1 + 29), 273, *((uint32_t *)a1 + 243));
          if ( v6 != 0 || (v6 = sub_45EBE0(*((uint32_t **)a1 + 29), 529, *((uint32_t *)a1 + 243))) != 0 )
          {
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6);
            v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 124))(v6);
          }
        }
        if ( v11 > 0 )
        {
          v7 = v10;
          do
          {
            sub_423A20((int)v12);
            sub_423A20((int)v12);
            v8 = *(uint32_t *)a1;
            v13 = 2000;
            v14 = 10000;
            v15 = 2;
            v12[12] = 1;
            v12[13] = 1;
            v12[15] = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, uint32_t, uint8_t *, int, int, int, uint32_t, uint32_t))(v8 + 584))(
              a1,
              v7,
              v5,
              500,
              v7,
              v5,
              30081,
              0,
              v12,
              4,
              100,
              1,
              0,
              0);
            v7 += 35;
            --v11;
          }
          while ( v11 != 0 );
        }
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)a1 + 312))(a1, 0);
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61DE30 CNFallingShuriken__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNFallingShuriken__vmt200(int *this, int a2, float *a3, int a4)
{
  int v6; // ebx
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // edi
  int v14; // edi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  uint32_t v19[3]; // [esp+Ch] [ebp-68h] BYREF
  char v20; // [esp+18h] [ebp-5Ch]
  char v21; // [esp+19h] [ebp-5Bh]
  int v22; // [esp+1Bh] [ebp-59h]
  int v23; // [esp+1Fh] [ebp-55h]
  int v24; // [esp+50h] [ebp-24h]
  int v25; // [esp+54h] [ebp-20h]
  int v26; // [esp+58h] [ebp-1Ch]
  int v27; // [esp+61h] [ebp-13h]
  char v28; // [esp+65h] [ebp-Fh]
  int v29; // [esp+70h] [ebp-4h]
  int v30; // [esp+7Ch] [ebp+8h]

  v29 = dword_796E50;
  v30 = CNRDPassiveObject__vmt200(this, a2, a3, a4);
  if ( a2 != 0 )
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
  else
    v6 = 0;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( v6 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 273) == 0
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) != 1
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 1 )
  {
    goto LABEL_14;
  }
  sub_423A20((int)v19);
  sub_423A20((int)v19);
  v7 = *(uint32_t *)v6;
  v24 = 600;
  v27 = 10000;
  v28 = 2;
  v20 = 1;
  v21 = 1;
  v8 = (*(int (/*thiscall*/ **)(int))(v7 + 120))(v6);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v8 )
    v9 = 135 - rand() % 20;
  else
    v9 = rand() % 20 + 45;
  v10 = *this;
  v22 = 300;
  v23 = 300;
  v25 = 0;
  v26 = v9;
  a4 = (*(int (/*thiscall*/ **)(int *))(v10 + 120))(this);
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v12 = *this;
  a3 = (float *)v11;
  v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 128))(this) + 1;
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int, float *, uint32_t))(*this + 136))(this, a4, a3, 0) != 0
    || (*(uint8_t (/*thiscall*/ **)(int *, int *, float **, int, float *, int, int, int))(*this + 140))(
         this,
         &a4,
         &a3,
         a4,
         a3,
         100,
         1,
         1) != 0 )
  {
    v19[1] = a3;
    v19[0] = a4;
    v19[2] = v13;
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
    v14 = *(uint32_t *)dword_8F8520;
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);
    v16 = *(uint32_t *)dword_8F8520;
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
    (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v19, 98);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
LABEL_14:
    *(uint32_t *)(*(this + 28) + 36) = 0;
  }
  return v30;
}



// ------------------------------------------------------------
// 0x61E040 CNFallingShuriken__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNFallingShuriken__vmt14C(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edi

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *this;
  if ( *((uint8_t *)this + 972) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(v2 + 128))(this) <= 0 )
    {
      v5 = *(this + 250);
      v3 = sub_699000((int)(this + 244));
      if ( v3 >= v5 )
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);
    }
    else
    {
      LOBYTE(v3) = sub_4939E0(*(this + 30), 0);
      *((uint8_t *)this + 972) = 0;
    }
  }
  else
  {
    v3 = (*(int (/*thiscall*/ **)(int *))(v2 + 128))(this);
    if ( v3 <= 0 )
    {
      *((uint8_t *)this + 989) = 0;
      *((uint8_t *)this + 990) = 0;
      sub_698F90((int)(this + 244), 2000, 0);
      v4 = *(this + 30);
      *((uint8_t *)this + 972) = 1;
      sub_4939E0(v4, 1);
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                     this,
                     "JEWEL_HIT",
                     -1,
                     0,
                     0);
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x61E0E0 sub_61E0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_61E0E0(uint32_t *this)
{
  uint32_t *v2; // edi
  int result; // eax
  int v4; // eax
  int v5; // [esp-18h] [ebp-20h]
  int v6; // [esp-14h] [ebp-1Ch]
  int v7; // [esp-10h] [ebp-18h]

  v2 = (uint32_t *)*(this + 173);
  if ( v2 == nullptr )
    v2 = this;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    return sub_4E4A50(v2, 30093, 0, v4, v5, v6, v7, 0, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E150 CNGhoulSkullBomb__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNGhoulSkullBomb__vmt14C(uint8_t *this)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) <= 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  if ( *(this + 976) == 1
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
    && *(this + 264) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61E1C0 CNGhoulSkullBomb__vmt144
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulSkullBomb__vmt144(uint32_t *this, int a2, int a3, int a4, int a5)
{
  unsigned int v6; // eax
  unsigned int v7; // eax
  uint64_t v8; // rax

  nullsub_2(a2, a3, a4, a5);
  if ( (uint8_t)a2 == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != 0 )
    {
      v6 = sub_699000((int)(this + 9)) - *(this + 243);
      if ( v6 > 0xBB8 )
      {
        v7 = v6 - 3000;
        if ( v7 >= 0x2BC )
        {
          LOBYTE(v8) = -36;
          *((uint8_t *)this + 976) = 1;
        }
        else
        {
          v8 = (uint64_t)sub_4049C0(100.0, 220.0, v7, 700);
        }
        sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);
      }
    }
    nullsub_2(0, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x61E280 CNGhoulSkullBomb__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNGhoulSkullBomb__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    sub_61E0E0(this);
}



// ------------------------------------------------------------
// 0x61E2B0 CNGhoulSkull__vmt1E4
// ------------------------------------------------------------
bool /*thiscall*/ CNGhoulSkull__vmt1E4(void *this, int a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ebx
  unsigned int v7; // esi
  int v8; // eax
  int v9; // edx
  int v10; // ecx

  v3 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
  v4 = *(uint32_t *)(v3 + 120);
  v5 = v3 + 116;
  if ( v4 != 0 )
    v6 = (*(uint32_t *)(v5 + 8) - v4) >> 2;
  else
    v6 = 0;
  v7 = 0;
  if ( v6 <= 0 )
    return IRDCollisionObject__vmt1E4(this, a2);
  while ( 1 )
  {
    v8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
    v9 = *(uint32_t *)(v8 + 120);
    if ( v9 != 0 && v7 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * v7);
    else
      v10 = 0;
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 340))(v10) == 818 )
      break;
    if ( (int)++v7 >= v6 )
      return IRDCollisionObject__vmt1E4(this, a2);
  }
  return false;
}



// ------------------------------------------------------------
// 0x61E340 CNGhoulSkullSub__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNGhoulSkullSub__vmt14C(int **this)
{
  uint32_t *v2; // edi
  int *v3; // eax
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int *v7; // eax
  int **v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *v13; // ecx
  bool v14; // zf
  char result; // al
  uint8_t v16[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  void *v20; // [esp+18h] [ebp-10h]
  int v21; // [esp+24h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 243) == nullptr && *(this + 244) == nullptr )
  {
    v2 = operator new(0x12Cu);
    v20 = v2;
    v3 = nullptr;
    v21 = 0;
    if ( v2 != nullptr )
    {
      v4 = sub_41ACF0(*(this + 178));
      v3 = sub_428F30(v2, v4, (int)this);
    }
    *(this + 243) = v3;
    v5 = operator new(0x12Cu);
    v20 = v5;
    v21 = 1;
    if ( v5 != nullptr )
    {
      v6 = sub_41ACF0(*(this + 178) + 1);
      v7 = sub_428F30(v5, v6, (int)this);
    }
    else
    {
      v7 = nullptr;
    }
    v21 = -1;
    *(this + 244) = v7;
    v8 = this + 243;
    v20 = (void *)2;
    do
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(**v8 + 12))(*v8, 0);
      v9 = **v8;
      v10 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this);
      v11 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v10);
      v12 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v11);
      (*(void (/*thiscall*/ **)(int *, int))(v9 + 40))(*v8, v12);
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(**v8 + 92))(*v8, v16);
      v13 = *(this + 29);
      v21 = 2;
      sub_4600B0(v13, 2, 0, (int)v16);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      ++v8;
      v14 = v20 == (void *)1;
      Block = nullptr;
      v18 = 0;
      v19 = 0;
      v20 = (char *)v20 - 1;
    }
    while ( !v14 );
  }
  result = *((uint8_t *)*(this + 30) + 170);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
      return ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E4C0 sub_61E4C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61E4C0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNGhoulSkullSub;
  *(this + 244) = 0;
  *(this + 243) = 0;
  sub_61C860((uint32_t **)this);
  return this;
}



// ------------------------------------------------------------
// 0x61E520 CNGhoulSkullSub__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNGhoulSkullSub__vmt0(void *Block, char a2)
{
  sub_61E550();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61E550 sub_61E550
// ------------------------------------------------------------
int /*thiscall*/ sub_61E550(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNGhoulSkullSub;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 972);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 976);
  *(uint32_t *)(this + 972) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)this = &vftbl_CNThrowItemDestroyable;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61E5E0 sub_61E5E0
// ------------------------------------------------------------
char /*thiscall*/ sub_61E5E0(void *this)
{
  char result; // al
  int v3; // eax
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( result != 0 )
  {
    result = *((uint8_t *)this + 264);
    if ( result == 0 )
    {
      v3 = sub_42FCB0(228);
      v4 = 0;
      if ( v3 != 0 )
        v4 = sub_431860(v3, "PassiveObject/Monster/Ghoul/Animation/SkullSub.ani", 1);
      v5 = (char *)sub_44B6C0(284);
      v6 = v5;
      if ( v5 != nullptr )
      {
        sub_44E0D0(v5, v4, 1);
        *(uint32_t *)v6 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v6 = nullptr;
      }
      sub_45FE80(*((uint32_t *)this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);
      v7 = *(uint32_t *)v6;
      v8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
      v9 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 124))(this, v8);
      v10 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 120))(this, v9);
      (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v6, v10);
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "SKULL_BREAK",
               -1,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61E6F0 CNGhoulSkull__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNGhoulSkull__vmt1F4(void *this, uint32_t *a2, float *a3, char a4)
{
  sub_61E5E0(this);
  return CNRDPassiveObject__vmt1F4((int *)this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61E720 sub_61E720
// ------------------------------------------------------------
void /*thiscall*/ sub_61E720(int *this)
{
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void *v13; // ecx
  void *v14[4]; // [esp+4h] [ebp-8Ch] BYREF
  int v15; // [esp+14h] [ebp-7Ch]
  bool v16; // [esp+1Bh] [ebp-75h]
  uint32_t v17[26]; // [esp+1Ch] [ebp-74h] BYREF
  int v18; // [esp+8Ch] [ebp-4h]

  v17[25] = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 88))(this) != 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= 0 )
  {
    if ( *(this + 243) >= 3 )
      goto LABEL_8;
    sub_423A20((int)v17);
    v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 60))(this) + 104);
    if ( v15 != 0 )
    {
      qmemcpy(v17, (const void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 16))(v15), 0x62u);
      v17[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 24))(v15);
      v17[1] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 28))(v15);
      v17[2] = 1;
      *(uint32_t *)((char *)&v17[7] + 3) = (uint64_t)((double)*(uint32_t *)((char *)&v17[7] + 3) * 0.69999999);
      *(uint32_t *)((char *)&v17[8] + 3) = (uint64_t)((double)*(uint32_t *)((char *)&v17[8] + 3) * 0.69999999);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v2 = *(uint32_t *)dword_8F8520;
      v3 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v2 + 36))(dword_8F8520, v3);
      v4 = *(uint32_t *)dword_8F8520;
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v17, 98);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      v6 = dword_8F82A0;
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v8 = *(uint32_t *)v6;
      v16 = v7 == 0;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(v8 + 28))(v6) + 84) = v7 == 0;
      v9 = *(uint32_t *)v6;
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(v6, v12);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v6 + 12))(v6, 0);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v6 + 92))(v6, v14);
      v13 = (void *)*(this + 29);
      v18 = 0;
      sub_4600B0(v13, 2, 0, (int)v14);
      v18 = -1;
      sub_5E5260(v14);
    }
    if ( *(this + 243) >= 3 )
LABEL_8:
      sub_61E5E0(this);
    ++*(this + 243);
  }
}



// ------------------------------------------------------------
// 0x61E930 CNGhoulSkull__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNGhoulSkull__vmt14C(int *this)
{
  sub_61E720(this);
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61E940 CNGhoulSkull__vmt214
// ------------------------------------------------------------
char /*thiscall*/ CNGhoulSkull__vmt214(int *this, int a2, int a3, int a4)
{
  sub_61E720(this);
  return CNRDPassiveObject__vmt214(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61E970 CNAraclothoMissile__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNAraclothoMissile__vmt1F4(int *this, int a2, float *a3, char a4)
{
  uint32_t *v4; // ebx
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v4 = (uint32_t *)a2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 273) != 0 )
  {
    v6 = (uint32_t *)__RTDynamicCast(
                     a2,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDCharacter `RTTI Type Descriptor',
                     0);
    v7 = v6;
    if ( v6 != nullptr )
    {
      v8 = *v6;
      v9 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int))(v8 + 580))(v7, 40002, 0, 0, 0, v11);
      v4 = (uint32_t *)a2;
    }
  }
  return CNRDPassiveObject__vmt1F4(this, v4, a3, a4);
}



// ------------------------------------------------------------
// 0x61EA00 sub_61EA00
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_61EA00(unsigned int *this)
{
  unsigned int result; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // edi
  float v6; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 9));
    if ( result >= *(this + 253) + 100 )
    {
      result = *(this + 173);
      if ( result != 0 )
      {
        v3 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 116))(this, 1);
        v4 = *(this + 243);
        v5 = v3;
        v6 = sub_4049C0(0.0, 400.0, abs32(v4 - v3), 100);
        if ( v4 >= v5 )
        {
          if ( v4 == v5 )
            v6 = 0.0;
        }
        else
        {
          v6 = v6 * -1.0;
        }
        sub_494F20(1, v6);
        result = sub_699000((int)(this + 9));
        *(this + 253) = result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61EAB0 CNAraclothoSpark__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNAraclothoSpark__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 273) != 0 )
  {
    v5 = __RTDynamicCast(
           (int)a2,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDCharacter `RTTI Type Descriptor',
           0);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)v5 + 760))(v5, 6, 1112014848, 8, this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61EB20 CNAraclothoSpark__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNAraclothoSpark__vmt14C(uint8_t *this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint8_t *)(v2 + 170) != 0 )
  {
    LOBYTE(v2) = *(this + 264);
    if ( (uint8_t)v2 == 0 )
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x61EB60 CNAraclothoMissile__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNAraclothoMissile__vmt14C(unsigned int *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  unsigned int v7; // edx
  int v8; // eax
  void *v9; // eax
  int v11; // [esp-10h] [ebp-34h]
  uint8_t v12[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v14; // [esp+10h] [ebp-14h]
  int v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+20h] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 252);
  if ( sub_699000((int)(this + 246)) >= v2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 244) + 12))(*(this + 244));
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 244) + 112))(*(this + 244));
    v3 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 0 ? -24 : 24;
    v4 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this) + v3;
    v5 = *(uint32_t *)*(this + 244);
    v11 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(v5 + 40))(*(this + 244), v4, v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v12);
    v7 = *this;
    v16 = 0;
    v8 = (*(int (/*thiscall*/ **)(unsigned int *))(v7 + 684))(this);
    v9 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, uint8_t *))(*(uint32_t *)v8 + 80))(v8, 2, 0, v12);
    sub_4600B0(v9, v11, 0, 0);
    *((uint8_t *)this + 997) = 0;
    *((uint8_t *)this + 998) = 0;
    sub_698F90((int)(this + 246), 50, 0);
    v16 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v14 = 0;
    v15 = 0;
  }
  return sub_61EA00(this);
}



// ------------------------------------------------------------
// 0x61EC80 CNAraclothoMissile__vmt2B4
// ------------------------------------------------------------
void /*thiscall*/ CNAraclothoMissile__vmt2B4(int *this, int a2, void *a3, int a4, int a5, int a6)
{
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  void *v9; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-4h]

  if ( *(this + 170) <= 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  if ( (int)a3 > 0 )
  {
    if ( *(this + 245) == 0 )
    {
      v7 = operator new(0x12Cu);
      v12 = 0;
      if ( v7 != nullptr )
        v8 = sub_428F30(v7, (int)"Common/HitEffect/Particle/SmallHitParticle.ptl", (int)this);
      else
        v8 = nullptr;
      v12 = -1;
      *(this + 245) = (int)v8;
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 245) + 40))(*(this + 245), a4, a5, a6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v10);
    v9 = (void *)*(this + 29);
    v12 = 1;
    sub_4600B0(v9, 2, 0, (int)v10);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x61ED80 CNCobWeb__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNCobWeb__vmt1F4(int *this, int a2, float *a3, char a4)
{
  uint32_t *v4; // ebx
  int v6; // eax
  char *v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  char *v17; // eax
  char *v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v25; // [esp+Ch] [ebp-10h]
  int v26; // [esp+Ch] [ebp-10h]

  v4 = (uint32_t *)a2;
  if ( *((uint8_t *)this + 264) == 0 )
  {
    v6 = sub_42FCB0(228);
    if ( v6 != 0 )
      v25 = sub_431860(v6, "PassiveObject/Monster/Spider/Ani/BossSlowWebLand.ani", 1);
    else
      v25 = 0;
    if ( v25 != 0 )
    {
      v7 = (char *)sub_44B6C0(284);
      if ( v7 != nullptr )
      {
        sub_44E0D0(v7, v25, 1);
        *(uint32_t *)v7 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v7 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v7, 2, 0, (int)v7, (int)this, 0);
      v8 = *(uint32_t *)v7;
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v7, v11);
      v12 = *(uint32_t *)v7;
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 144))(v7, v13);
      v4 = (uint32_t *)a2;
    }
    if ( rand() % 100 < 50 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 273) != 0 )
    {
      v14 = __RTDynamicCast(
              (int)v4,
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &IRDCharacter `RTTI Type Descriptor',
              0);
      if ( v14 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)v14 + 764))(v14, 16, 1, 0, 0);
        v15 = sub_42FCB0(228);
        v16 = v15 != 0 ? sub_431860(v15, "PassiveObject/Monster/Spider/Ani/BossSlowWebEffect.ani", 1) : 0;
        if ( v25 != 0 )
        {
          v17 = (char *)sub_44B6C0(284);
          if ( v17 != nullptr )
            v18 = sub_44E1F0(v17, v16, 1);
          else
            v18 = nullptr;
          sub_45FE80(*(this + 29), (int)v18, 2, 0, (int)v18, (int)v4, 0);
          v26 = *(uint32_t *)v18;
          v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 128))(v4);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 124))(a2, v19);
          v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 120))(a2, v20);
          (*(void (/*thiscall*/ **)(char *, int))(v26 + 112))(v18, v21);
          v22 = *(uint32_t *)v18;
          v23 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(char *, int))(v22 + 144))(v18, v23);
          v4 = (uint32_t *)a2;
        }
      }
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt1F4(this, v4, a3, a4);
}



// ------------------------------------------------------------
// 0x61EFD0 sub_61EFD0
// ------------------------------------------------------------
int /*thiscall*/ sub_61EFD0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 243);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);
  *(this + 243) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 244) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x61F010 CNSpectressBat__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpectressBat__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 273) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int *, uint32_t))(*a2 + 760))(a2, 5, 1103626240, 5, this, 0);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61F060 CNSpectressBat__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNSpectressBat__vmt12C(uint32_t *this, int a2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  bool v8; // zf
  uint8_t v9[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v11; // [esp+Ch] [ebp-18h]
  int v12; // [esp+10h] [ebp-14h]
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  if ( this == (uint32_t *)a2 )
  {
    v13 = 3;
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 244) + 12))(*(this + 244), 0);
      v3 = *(uint32_t *)*(this + 244);
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v4);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(this + 244), v6);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 244) + 92))(*(this + 244), v9);
      v7 = (void *)*(this + 29);
      v14 = 0;
      sub_4600B0(v7, 2, 0, (int)v9);
      v14 = -1;
      if ( Block != nullptr )
        j__free(Block);
      v8 = v13 == 1;
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      --v13;
    }
    while ( !v8 );
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 20202);
  }
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x61F150 CNSpectressBat__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNSpectressBat__vmt14C(int *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  v2 = *(this + 251);
  v3 = (int)(this + 245);
  if ( sub_699000((int)(this + 245)) >= v2 )
  {
    *(uint8_t *)(v3 + 13) = 0;
    *(uint8_t *)(v3 + 14) = 0;
    sub_698F90(v3, 50, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);
    v4 = *(uint32_t *)*(this + 243);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(this + 243), v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 104))(*(this + 243), *(this + 252));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v10);
    v8 = (void *)*(this + 29);
    v14 = 0;
    sub_4600B0(v8, 2, 0, (int)v10);
    v14 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v12 = 0;
    v13 = 0;
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61F240 sub_61F240
// ------------------------------------------------------------
int /*thiscall*/ sub_61F240(uint32_t *this)
{
  int v2; // ecx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax

  v2 = (int)(this + 245);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 50, 0);
  v3 = operator new(0x12Cu);
  if ( v3 != nullptr )
    v4 = sub_428F30(v3, (int)"PassiveObject/Monster/Wraith/Particle/FlyBat.ptl", 0);
  else
    v4 = nullptr;
  *(this + 243) = v4;
  v5 = operator new(0x12Cu);
  if ( v5 != nullptr )
    v6 = sub_428F30(v5, (int)"PassiveObject/Monster/Wraith/Particle/FlyBatParticle.ptl", 0);
  else
    v6 = nullptr;
  *(this + 244) = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "BAT_FLAP",
           20202,
           0,
           0);
}



// ------------------------------------------------------------
// 0x61F310 CNLOLLaser__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNLOLLaser__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  *((uint8_t *)this + 980) = 1;
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61F320 CNEvilEyeMissile__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNEvilEyeMissile__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  if ( a4 == 0 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHAKE_WAVE", -1, 0, 0);
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x61F360 CNEvilEyeLOLLaser__vmt2C4
// ------------------------------------------------------------
int /*thiscall*/ CNEvilEyeLOLLaser__vmt2C4(void *this, int a2)
{
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  v3 = a2;
  if ( a2 > 0 )
  {
    v4 = 0;
    do
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 4),
        v4,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 8),
        v4,
        0,
        0,
        0);
      v4 += 100;
      --v3;
    }
    while ( v3 != 0 );
  }
  sub_4926A0(*((uint32_t *)this + 30));
  v5 = sub_699000((int)this + 36);
  v6 = *(uint32_t **)this;
  *((uint32_t *)this + 243) = v5;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t **)(((int (/*thiscall*/ *)(void *))v6[85])(this) + 64);
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F410 CNEvilEyeSmallLaser__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNEvilEyeSmallLaser__vmt14C(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // eax
  int v4; // edx

  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )
  {
    v2 = (uint32_t *)*(this + 36);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    v4 = *this;
    if ( v3 == *v2 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 84))(this, 0);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 196))(this, *(uint32_t *)*(this + 36));
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 3 && *((uint8_t *)this + 972) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      30304,
      10,
      0,
      0,
      0,
      0,
      0,
      1,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "STONE_LASER_FIRE",
      -1,
      0,
      0);
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x61F4C0 sub_61F4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_61F4C0(void *this, int a2)
{
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    0,
    **((uint32_t **)this + 36),
    0,
    0,
    0,
    0);
  v3 = a2;
  if ( a2 > 0 )
  {
    v4 = 0;
    do
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 4),
        0,
        v4,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        0,
        *(uint32_t *)(*((uint32_t *)this + 36) + 8),
        0,
        v4,
        0,
        0);
      v4 -= 30;
      --v3;
    }
    while ( v3 != 0 );
  }
  sub_4926A0(*((uint32_t *)this + 30));
  v5 = sub_699000((int)this + 36);
  v6 = *(uint32_t **)this;
  *((uint32_t *)this + 243) = v5;
  *((uint8_t *)this + 980) = 0;
  result = **(uint32_t **)(((int (/*thiscall*/ *)(void *))v6[85])(this) + 64);
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F570 sub_61F570
// ------------------------------------------------------------
int /*thiscall*/ sub_61F570(uint32_t **this)
{
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 36));
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[1]);
  return ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[2]);
}



// ------------------------------------------------------------
// 0x61F5C0 CNEvilEyeQuake__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNEvilEyeQuake__vmt14C(uint32_t **this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *v6; // ecx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  void *v11; // ecx
  uint8_t v12[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *v13; // [esp+Ch] [ebp-28h]
  uint8_t v14[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int v16; // [esp+20h] [ebp-14h]
  int v17; // [esp+24h] [ebp-10h]
  int v18; // [esp+30h] [ebp-4h]

  if ( *(uint8_t *)(((int (/*thiscall*/ *)(uint32_t **))(*this)[50])(this) + 170) != 0 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[21])(this, 0);
  if ( (unsigned int)(sub_699000((int)(this + 9)) - (uint32_t)*(this + 245)) >= 0x3C )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 243) + 12))(*(this + 243), 0);
    v2 = **(this + 243);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3);
    v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(this + 243), v5);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 243) + 92))(*(this + 243), v12);
    v6 = *(this + 29);
    v18 = 0;
    sub_4600B0(v6, 2, 0, (int)v12);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 244) + 12))(*(this + 244), 0);
    v7 = **(this + 244);
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
    v9 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v8);
    v10 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v9);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v7 + 40))(*(this + 244), v10);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 244) + 92))(*(this + 244), v14);
    v11 = *(this + 29);
    LOBYTE(v18) = 1;
    sub_4600B0(v11, 2, 0, (int)v14);
    *(this + 245) = (uint32_t *)sub_699000((int)(this + 9));
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v16 = 0;
    v17 = 0;
    if ( v13 != nullptr )
      j__free(v13);
  }
}



// ------------------------------------------------------------
// 0x61F720 sub_61F720
// ------------------------------------------------------------
int /*thiscall*/ sub_61F720(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int result; // eax

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"PassiveObject/Monster/EvilEye/Particle/Vib_dust.ptl", (int)this);
  else
    v3 = nullptr;
  *(this + 243) = v3;
  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    v5 = sub_428F30(v4, (int)"PassiveObject/Monster/EvilEye/Particle/Vib_rock.ptl", (int)this);
  else
    v5 = nullptr;
  *(this + 244) = v5;
  result = sub_699000((int)(this + 9));
  *(this + 245) = result;
  return result;
}



// ------------------------------------------------------------
// 0x61F7D0 sub_61F7D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61F7D0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEvilEyeLOLLaser;
  sub_5FF8E0((int)this);
  CNEvilEyeLOLLaser__vmt2C4(this, a3);
  return this;
}



// ------------------------------------------------------------
// 0x61F830 sub_61F830
// ------------------------------------------------------------
int /*thiscall*/ sub_61F830(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeLOLLaser;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[2]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61F8B0 sub_61F8B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61F8B0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEvilEyeMissile;
  sub_5FF8E0((int)this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -1,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    1,
    *(uint32_t *)*(this + 36),
    0,
    0,
    0,
    0);
  return this;
}



// ------------------------------------------------------------
// 0x61F950 CNEvilEyeMissile__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNEvilEyeMissile__vmt0(void *Block, char a2)
{
  sub_61F980();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61F980 sub_61F980
// ------------------------------------------------------------
int /*thiscall*/ sub_61F980(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeMissile;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61F9F0 sub_61F9F0
// ------------------------------------------------------------
int /*thiscall*/ sub_61F9F0(int this, char a2, int a3)
{
  int v4; // eax

  sub_52EA60((uint32_t *)this, a2, a3);
  v4 = *(uint32_t *)(this + 144);
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)this = &vftbl_CNEvilEyeSmallLaser;
  CNRDObject__vmtCC((unsigned int *)this, 0, *(uint32_t *)(v4 + 4), 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x61FA60 sub_61FA60
// ------------------------------------------------------------
int /*thiscall*/ sub_61FA60(void ***this)
{
  *this = (void **)&vftbl_CNEvilEyeSmallLaser;
  CNRDObject__vmtD0(this, **(this + 36));
  ((void (/*thiscall*/ *)(void ***, void *))(*this)[52])(this, (*(this + 36))[1]);
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61FAD0 sub_61FAD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_61FAD0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEvilEyeQuake;
  sub_5FF8E0((int)this);
  sub_61F720(this);
  return this;
}



// ------------------------------------------------------------
// 0x61FB30 CNEvilEyeQuake__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNEvilEyeQuake__vmt0(void *Block, char a2)
{
  sub_61FB60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FB60 sub_61FB60
// ------------------------------------------------------------
int /*thiscall*/ sub_61FB60(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEvilEyeQuake;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 972);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 976);
  *(uint32_t *)(this + 972) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(uint32_t *)(this + 976) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x61FBE0 CNEvilEyeLOLLaser__vmt0
// ------------------------------------------------------------
void ***/*thiscall*/ CNEvilEyeLOLLaser__vmt0(void ***Block, char a2)
{
  sub_61F830(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FC10 CNEvilEyeSmallLaser__vmt0
// ------------------------------------------------------------
void ***/*thiscall*/ CNEvilEyeSmallLaser__vmt0(void ***Block, char a2)
{
  sub_61FA60(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x61FC40 sub_61FC40
// ------------------------------------------------------------
int /*thiscall*/ sub_61FC40(int this)
{
  *(uint32_t *)(this + 96) = 545;
  *(uint8_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint8_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 4;
  return 0;
}



// ------------------------------------------------------------
// 0x61FC70 CNMineTrap__vmt288
// ------------------------------------------------------------
int /*thiscall*/ CNMineTrap__vmt288(int this, uint32_t *a2, int a3)
{
  if ( *(uint8_t *)(this + 1000) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 20) != *(uint32_t *)(this + 1004) )
  {
    return 3;
  }
  *a2 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x61FCB0 CNMineTrap__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNMineTrap__vmtC(int this)
{
  int *v2; // eax
  int v3; // eax
  double v4; // st7
  int v5; // edx
  float v7; // [esp+0h] [ebp-20h]
  float v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmtC((int *)this);
  if ( *(uint32_t *)(this + 116) != 0 )
  {
    v2 = *(int **)(this + 348);
    v9 = *v2;
    v10 = v2[1];
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    v8 = (float)v10;
    v7 = (float)v9;
    v4 = sub_4049C0(v7, v8, *(uint32_t *)(*(uint32_t *)(v3 + 108) + 112) - 1, 98);
    v5 = *(uint32_t *)this;
    *(float *)(this + 724) = v4;
    (*(void (/*thiscall*/ **)(int, int))(v5 + 344))(this, this + 724);
  }
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 2, 0, 1, 1);
}



// ------------------------------------------------------------
// 0x61FD30 CNMineTrap__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNMineTrap__vmt14C(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // ecx
  unsigned int v5; // edi
  int v6; // ecx
  int v7; // edx
  int v8; // esi
  uint32_t *v9; // eax
  uint8_t (/*thiscall*/ **v10)(char *, uint32_t); // [esp+4h] [ebp-Ch]
  unsigned int v11; // [esp+8h] [ebp-8h]
  int v12; // [esp+Ch] [ebp-4h]

  CNRDPassiveObject__vmt14C((int)this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( *((uint8_t *)this + 992) != 0 )
    {
      result = *(this + 30);
      if ( result != 0 && *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 2, 0, 2, 0);
    }
    else
    {
      result = sub_699000((int)(this + 9));
      if ( result >= *(this + 249) )
      {
        v3 = *(this + 29);
        v4 = *(uint32_t *)(v3 + 120);
        result = v3 + 116;
        v5 = 0;
        if ( v4 != 0 )
        {
          result = (*(uint32_t *)(result + 8) - v4) >> 2;
          v12 = result;
        }
        else
        {
          v12 = 0;
        }
        v11 = 0;
        if ( v12 > 0 )
        {
          do
          {
            v6 = *(this + 29);
            v7 = *(uint32_t *)(v6 + 120);
            if ( v7 != 0 && v5 < (*(uint32_t *)(v6 + 124) - v7) >> 2 )
              v8 = *(uint32_t *)(v7 + 4 * v5);
            else
              v8 = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 17) != 0 )
            {
              v10 = (uint8_t (/*thiscall*/ **)(char *, uint32_t))*(this + 243);
              v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 340))(v8);
              if ( (*v10)((char *)this + 972, *v9) == 0
                && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 428))(v8) != 0
                 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 432))(v8) != 0)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 128))(v8) == 0
                && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 488))(this, v8) != 0 )
              {
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 3, 0, 2, 0);
              }
              v5 = v11;
            }
            result = v12;
            v11 = ++v5;
          }
          while ( (int)v5 < v12 );
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x61FEA0 CNMineTrap__vmt1D8
// ------------------------------------------------------------
int /*userpurge*/ CNMineTrap__vmt1D8@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3, int a4, int a5, int a6)
{
  uint32_t *v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  int v17; // [esp-4h] [ebp-Ch]

  CNRDPassiveObject__vmt1D8(a1, a2, a3, a3, a4, a5, a6);
  if ( a3 == 2 )
  {
    v12 = *a1;
    v17 = a1[34];
    *((uint8_t *)a1 + 992) = 0;
    (*(void (/*thiscall*/ **)(int *, int))(v12 + 196))(a1, v17);
    v13 = a1[87];
    if ( v13 != 0 && (unsigned int)((a1[88] - v13) >> 2) > 2 )
      v14 = *(uint32_t *)(v13 + 8);
    else
      v14 = 0;
    a1[249] = v14 + sub_699000((int)(a1 + 9));
  }
  else if ( a3 == 3 )
  {
    v7 = (uint32_t *)a1[36];
    v8 = *a1;
    *((uint8_t *)a1 + 992) = 1;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v8 + 196))(a1, *v7);
    v9 = a1[178];
    if ( v9 != 0 && (a1[179] - v9) >> 2 != 0 )
    {
      v10 = *a1;
      v11 = sub_41ACF0(v9);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v10 + 212))(a1, v11, -1, 0, 0);
    }
  }
  v15 = a1[30];
  if ( v15 != 0 )
    sub_4926A0(v15);
  return (*(int (/*thiscall*/ **)(int *))(*a1 + 352))(a1);
}



// ------------------------------------------------------------
// 0x61FF90 CNMineTrap__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNMineTrap__vmt200(int *this, int a2, float *a3, char a4)
{
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  uint64_t v9; // rax
  float v11; // [esp+10h] [ebp-1Ch]
  float v12; // [esp+14h] [ebp-18h]

  v5 = *(this + 178);
  if ( v5 != 0 && (unsigned int)((*(this + 179) - v5) >> 2) > 1 )
  {
    v6 = *this;
    v7 = sub_41ACF0(v5 + 4);
    (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v6 + 212))(this, v7, -1, 0, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v8 = *(this + 87);
    if ( v8 != 0 && (unsigned int)((*(this + 88) - v8) >> 2) > 4 && *(uint32_t *)(v8 + 16) != -1 )
    {
      v12 = (float)*(int *)(*(this + 87) + 24);
      v11 = (float)*(int *)(v8 + 20);
      v9 = (uint64_t)sub_4049C0(
                               v11,
                               v12,
                               *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112) - 1,
                               98);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        *(uint32_t *)(*(this + 87) + 16),
        v9,
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt200(this, a2, a3, a4);
}


