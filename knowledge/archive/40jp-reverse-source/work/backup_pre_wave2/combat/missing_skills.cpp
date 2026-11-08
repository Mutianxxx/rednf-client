// ============================================================
// 【40JP逆向源代码工程】src/combat/missing_skills.cpp
// 模块: 0x5E0000-0x650000 补漏
// 来源: work/dump 素材  区块: 0x5F9160-0x639D11 §A 0x5E 补漏
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 46
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 0x5E 补漏
// ============================================================
// 0x5F9160 sub_5F9160
// ------------------------------------------------------------
// 调: sub_5F9160
void /*thiscall*/ sub_5F9160(uint8_t *this)
{
  *(this + 40) = 0;
}



// ------------------------------------------------------------
// 0x5FFFE0 sub_5FFFE0
// ------------------------------------------------------------
// 调: sub_5FFFE0 sub_48DA40
int /*thiscall*/ sub_5FFFE0(uint32_t *this, int nArg2)
{
  int result; // eax
  int v4; // eax
  int v5; // [esp-Ch] [ebp-10h]

  result = nArg2;
  if ( *(this + 172) != nArg2 )
  {
    *(this + 172) = nArg2;
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( *(uint32_t *)(result + 44) != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      return sub_48DA40(v4, v5, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// ============================================================
// §B 0x60-0x64 补漏
// ============================================================
// 0x600070 sub_600070
// ------------------------------------------------------------
// 调: sub_600070
bool /*thiscall*/ sub_600070(uint32_t *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  return fld_e1 == 0 || (*(this + 2) - fld_e1) / 24 == 0;
}



// ------------------------------------------------------------
// 0x604660 sub_604660
// ------------------------------------------------------------
// 调: sub_604660
void /*thiscall*/ sub_604660(uint8_t *this)
{
  *(this + 2312) = 0;
}



// ------------------------------------------------------------
// 0x610540 sub_610540
// ------------------------------------------------------------
// 调: sub_610540
int /*thiscall*/ sub_610540(int *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int v6; // eax
  int *v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // [esp+4h] [ebp-8h] BYREF
  int v16; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 88))(this);
    if ( (uint8_t)result != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);
      v7 = (int *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v6 + 104) + 16))(*(uint32_t *)(v6 + 104));
      *(int *)((char *)v7 + 15) = 0;
      *(int *)((char *)v7 + 19) = 0;
      *(int *)((char *)v7 + 23) = 0;
      *(int *)((char *)v7 + 27) = 0;
      *(int *)((char *)v7 + 31) = 0;
      *(int *)((char *)v7 + 35) = 0;
      *(int *)((char *)v7 + 39) = 0;
      *(int *)((char *)v7 + 43) = 0;
      *(int *)((char *)v7 + 47) = 0;
      *(int *)((char *)v7 + 51) = 0;
      *(int *)((char *)v7 + 55) = 0;
      *(int *)((char *)v7 + 59) = 0;
      v16 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v8 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v9 = *this;
      v15 = v8;
      v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 128))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v16, v15, 0) != 0
        || (uint8_t)(result = (*(int (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(*this + 140))(
                              this,
                              &v16,
                              &v15,
                              v16,
                              v15,
                              100,
                              1,
                              1)) != 0 )
      {
        *v7 = v16;
        v7[1] = v15;
        v7[2] = v10;
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v11 = *(uint32_t *)dword_8F8520;
        v12 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
        v13 = *(uint32_t *)dword_8F8520;
        v14 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v7, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x616D80 sub_616D80
// ------------------------------------------------------------
// 调: sub_616D80
void /*thiscall*/ sub_616D80(uint32_t *this)
{
  *(this + 243) = 0;
}



// ------------------------------------------------------------
// 0x61CA70 sub_61CA70
// ------------------------------------------------------------
// 调: sub_61CA70 sub_600790
int /*stdcall*/ sub_61CA70(int nArg1)
{
  return sub_600790(nArg1);  // 【CNRDPassiveObject__vmt12C】
}



// ------------------------------------------------------------
// 0x6217C0 sub_6217C0
// ------------------------------------------------------------
// 调: sub_6217C0
char /*thiscall*/ sub_6217C0(uint32_t *this, int nArg2)
{
  int fld_e249; // edx
  unsigned int i; // ecx
  int v5; // edi
  unsigned int j; // ebx
  int fld_e2492; // eax
  int v8; // ecx
  int v9; // eax
  int fld_e2493; // eax
  int v11; // ecx
  int v12; // ecx
  int fld_e2494; // edx
  int v14; // eax
  int v15; // ecx
  int pObj2; // ecx
  int fld_e2495; // eax
  int v18; // ecx
  int v19; // ecx
  int pObj; // eax

  fld_e249 = *(this + 249);
  for ( i = 0; ; ++i )
  {
    if ( fld_e249 == 0 || i >= (*(this + 250) - fld_e249) >> 2 )
      return 0;
    if ( *(uint32_t *)(*(this + 249) + 4 * i) == nArg2 )
      break;
  }
  v5 = 4 * i;
  if ( *(uint32_t *)(*(this + 249) + 4 * i) != 0 )
  {
    for ( j = 0; ; ++j )
    {
      fld_e2492 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + *(this + 249)) + 700))(*(uint32_t *)(v5 + *(this + 249)));
      v8 = *(uint32_t *)(fld_e2492 + 4);
      v9 = v8 != 0 ? (*(uint32_t *)(fld_e2492 + 8) - v8) >> 2 : 0;
      if ( (int)j >= v9 )
        break;
      fld_e2493 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + *(this + 249)) + 700))(*(uint32_t *)(v5 + *(this + 249)));
      v11 = *(uint32_t *)(fld_e2493 + 4);
      if ( v11 != 0 && j < (*(uint32_t *)(fld_e2493 + 8) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * j);
      else
        v12 = 0;
      fld_e2494 = *(uint32_t *)(*(this + 249) + v5);
      if ( *(uint32_t *)(v12 + 4) == fld_e2494 )
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2494 + 700))(fld_e2494);
        v15 = *(uint32_t *)(v14 + 4);
        if ( v15 != 0 && j < (*(uint32_t *)(v14 + 8) - v15) >> 2 )
          pObj2 = *(uint32_t *)(v15 + 4 * j);
        else
          pObj2 = 0;
        if ( *(uint32_t **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 32) == this )
        {
          fld_e2495 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + *(this + 249)) + 700))(*(uint32_t *)(v5 + *(this + 249)));
          v18 = *(uint32_t *)(fld_e2495 + 4);
          if ( v18 != 0 && j < (*(uint32_t *)(fld_e2495 + 8) - v18) >> 2 )
            v19 = *(uint32_t *)(v18 + 4 * j);
          else
            v19 = 0;
          pObj = __RTDynamicCast(
                  v19,
                  0,
                  &IRDAppendage `RTTI Type Descriptor',
                  &CNWindSimulation `RTTI Type Descriptor',
                  0);
          if ( pObj != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
            break;
          }
        }
      }
    }
  }
  memcpy_0(
    (void *)(v5 + *(this + 249)),
    (const void *)(v5 + *(this + 249) + 4),
    4 * ((*(this + 250) - (v5 + *(this + 249) + 4)) >> 2));
  *(this + 250) -= 4;
  return 1;
}



// ------------------------------------------------------------
// 0x621C90 sub_621C90
// ------------------------------------------------------------
// 调: sub_621C90 sub_6215E0 sub_6214D0 sub_4E75F0
unsigned int /*thiscall*/ sub_621C90(int *this, int nArg2)
{
  int nArg22; // edi
  int fld_e87; // ecx
  int v5; // edx
  int *v6; // eax
  int v7; // edx
  int pThis_F8; // ecx
  int fld_e249; // esi
  unsigned int v10; // edx
  int *nArg222; // eax
  unsigned int result; // eax
  float v13[2]; // [esp+8h] [ebp-20h] BYREF
  uint32_t v14[2]; // [esp+10h] [ebp-18h] BYREF
  void *Block; // [esp+18h] [ebp-10h]
  int v16; // [esp+24h] [ebp-4h]

  nArg22 = nArg2;
  if ( (uint8_t)sub_6215E0(nArg2) == 0 )
  {
    fld_e87 = *(this + 87);
    Block = (void *)(*(uint32_t *)(fld_e87 + 4) / 100);
    v13[0] = (float)(int)Block;
    v5 = *this;
    Block = (void *)(*(uint32_t *)(fld_e87 + 8) / 100);
    v13[1] = (float)(int)Block;
    v14[0] = (*(int (/*thiscall*/ **)(int *))(v5 + 152))(this);
    v14[1] = 4;
    Block = operator new(0x64u);
    v16 = 0;
    if ( Block != nullptr )
      v6 = (int *)sub_6214D0(v13, v14);
    else
      v6 = nullptr;
    v7 = *v6;
    v16 = -1;
    (*(void (/*thiscall*/ **)(int *, int, int *, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(v6, nArg22, this, 0, 0, 0, -1);
  }
  pThis_F8 = (int)(this + 248);
  fld_e249 = *(this + 249);
  if ( fld_e249 != 0 )
    v10 = (*(uint32_t *)(pThis_F8 + 8) - fld_e249) >> 2;
  else
    v10 = 0;
  if ( fld_e249 == 0 || v10 >= (*(uint32_t *)(pThis_F8 + 12) - fld_e249) >> 2 )
    return sub_4E75F0(pThis_F8, *(uint32_t *)(pThis_F8 + 8), 1u, &nArg2);
  nArg222 = *(int **)(pThis_F8 + 8);
  *nArg222 = nArg22;
  result = (unsigned int)(nArg222 + 1);
  *(uint32_t *)(pThis_F8 + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6235F0 sub_6235F0
// ------------------------------------------------------------
// 调: sub_6235F0
int /*thiscall*/ sub_6235F0(uint32_t *this, int nArg2)
{
  int v3; // edx
  int result; // eax

  v3 = *this;
  *(this + 243) = *(uint32_t *)(*(this + 87) + 4);
  result = (*(int (/*stdcall*/ **)(int))(v3 + 372))(100);
  *((uint8_t *)this + 988) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x623730 sub_623730
// ------------------------------------------------------------
// 调: sub_623730 sub_699000 sub_4E4630 sub_4E5CA0
unsigned int /*thiscall*/ sub_623730(uint32_t *this)
{
  unsigned int result; // eax
  unsigned int v3; // ebx
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v10; // edx
  int pObj; // esi
  int v12; // ebx
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // esi
  unsigned int v17; // [esp+4h] [ebp-4h]

  if ( *(this + 240) != 2 )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    *(this + 245) = result;
    return result;
  }
  v3 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v5 = *(uint32_t *)(fld_e29 + 120);
    v17 = v3;
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v5) >> 2 : 0;
    if ( (int)v3 >= v6 )
      break;
    v7 = *(uint32_t *)(fld_e29 + 120);
    if ( v7 != 0 && v3 < (*(uint32_t *)(fld_e29 + 124) - v7) >> 2 )
      pObj2 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
      || ((fld_e292 = *(this + 29), (v10 = *(uint32_t *)(fld_e292 + 120)) == 0) || v3 >= (*(uint32_t *)(fld_e292 + 124) - v10) >> 2
        ? (pObj = 0)
        : (pObj = *(uint32_t *)(v10 + 4 * v3)),
          (uint8_t)sub_4E4630(pObj) == 0
       || (uint8_t)sub_4E5CA0(pObj) != 0
       || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) != 0
       || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) != 0) )
    {
LABEL_32:
      ++v3;
    }
    else
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        if ( v12 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )
          goto LABEL_31;
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + 200;
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) > v13 )
          goto LABEL_31;
        v3 = v17;
      }
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        if ( v14 > (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)
          || (v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - 200,
              (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) < v15) )
        {
LABEL_31:
          v3 = v17;
          goto LABEL_32;
        }
        v3 = v17;
      }
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
      if ( (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v16) <= 60 )
        goto LABEL_34;
      ++v3;
    }
  }
  *(this + 245) = sub_699000((int)(this + 9));
LABEL_34:
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 243) + *(this + 245) < result )
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 3, 0, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62ABE0 sub_62ABE0
// ------------------------------------------------------------
// 调: sub_62ABE0 sub_6000E0
int /*stdcall*/ sub_62ABE0(int nArg1, int nArg2, int nArg3, int nArg4)
{
  return sub_6000E0(nArg1, nArg2, nArg3, nArg4);  // 【CNRDPassiveObject__vmt1D8】
}



// ------------------------------------------------------------
// 0x62D100 sub_62D100
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_62D100 sub_60B8B0
int /*thiscall*/ sub_62D100(void *this)
{
  return sub_60B8B0((int)this);  // 【CNMapObject__vmt2E8】
}



// ------------------------------------------------------------
// 0x631B00 sub_631B00
// ------------------------------------------------------------
// 调: sub_631B00
void sub_631B00()
{
  dword_9B945C = 0;
}



// ------------------------------------------------------------
// 0x649190 sub_649190
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_649190 sub_648FB0
int sub_649190()
{
  return sub_648FB0();
}



// ------------------------------------------------------------
// 0x5E4E30 sub_5E4E30
// ------------------------------------------------------------
// 调: sub_5E4E30
char /*thiscall*/ sub_5E4E30(uint8_t *this, char pszArg2)
{
  *(this + 85) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x5FE160 sub_5FE160
// ------------------------------------------------------------
// 调: sub_5FE160
int /*thiscall*/ sub_5FE160(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x600030 sub_600030
// ------------------------------------------------------------
// 调: sub_600030
void /*stdcall*/ sub_600030(int nArg1)
{
  nullsub_1(nArg1);
  if ( nArg1 == 6 )
    off_77F3FC((char *)&byte_73ABC8);
}



// ------------------------------------------------------------
// 0x6036A0 sub_6036A0
// ------------------------------------------------------------
// 调: sub_6036A0
int sub_6036A0()
{
  return 2;
}



// ------------------------------------------------------------
// 0x607280 sub_607280
// ------------------------------------------------------------
// 调: sub_607280
void /*thiscall*/ sub_607280(uint8_t *this)
{
  *(this + 10) = 0;
}



// ------------------------------------------------------------
// 0x6106A0 sub_6106A0
// ------------------------------------------------------------
// 调: sub_6106A0
int /*thiscall*/ sub_6106A0(uint32_t *this)
{
  *(this + 244) = 0;
  *(this + 243) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x61BE40 sub_61BE40
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_61BE40 sub_600890
int sub_61BE40()
{
  return sub_600890();  // 【CNRDPassiveObject__vmt14C】
}



// ------------------------------------------------------------
// 0x61E140 sub_61E140
// ------------------------------------------------------------
// 调: sub_61E140 sub_5FF9C0
int /*stdcall*/ sub_61E140(int nArg1, int nArg2, int nArg3)
{
  return sub_5FF9C0(nArg1, nArg2, nArg3);  // 【CNRDPassiveObject__vmt1F4】
}



// ------------------------------------------------------------
// 0x621960 sub_621960
// ------------------------------------------------------------
// 调: sub_621960 sub_600790 sub_6217C0
int /*stdcall*/ sub_621960(int nArg1)
{
  int result; // eax

  sub_600790(nArg1);  // 【CNRDPassiveObject__vmt12C】
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 40))(nArg1, 273);
  if ( (uint8_t)result != 0 )
    return sub_6217C0(nArg1);
  return result;
}



// ------------------------------------------------------------
// 0x621DC0 sub_621DC0
// ------------------------------------------------------------
// 调: sub_621DC0 sub_621440 sub_6215E0 sub_6217C0 sub_621C90
char /*thiscall*/ sub_621DC0(uint32_t *this)
{
  unsigned int v2; // ebx
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // esi
  char v12; // [esp+Fh] [ebp-1h]

  v12 = 0;
  v2 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      return v12;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj = *(uint32_t *)(v6 + 4 * v2);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v2 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v2);
      else
        v10 = 0;
      if ( (uint8_t)sub_621440(v10) == 0 )
      {
        if ( (uint8_t)sub_6215E0(v10) == 1 )
          sub_6217C0(v10);
        goto LABEL_20;
      }
      v12 = 1;
      if ( (uint8_t)sub_6215E0(v10) != 0 )
        goto LABEL_20;
      sub_621C90(v10);
      ++v2;
    }
    else
    {
LABEL_20:
      ++v2;
    }
  }
}



// ------------------------------------------------------------
// 0x623620 sub_623620
// ------------------------------------------------------------
// 证: "TRAP_GRASS_DIE"
// 调: sub_623620 sub_600AF0
int /*thiscall*/ sub_623620(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TRAP_GRASS_DIE", -1, 0, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *((uint8_t *)this + 264) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      40006,
      *(uint32_t *)(*(this + 87) + 8),
      0,
      0,
      0,
      0,
      0,
      4,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  return sub_600AF0(nArg2, nArg3, nArg4);  // 【CNRDPassiveObject__vmt200】
}



// ------------------------------------------------------------
// 0x623910 sub_623910
// ------------------------------------------------------------
// 调: sub_623910 sub_6000E0 sub_6236B0 sub_699000
int /*thiscall*/ sub_623910(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax

  if ( *(this + 240) == 4 && nArg2 == 2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 34));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
  }
  sub_6000E0(nArg2, nArg3, nArg4, nArg5);  // 【CNRDPassiveObject__vmt1D8】
  if ( nArg2 == 2 )
  {
    *((uint8_t *)this + 976) = 0;
    return sub_6236B0(0);
  }
  else if ( nArg2 == 3 )
  {
    sub_6236B0(1);
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    *(this + 245) = result;
  }
  else
  {
    result = nArg2 - 4;
    if ( nArg2 == 4 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 12));
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               100,
               *(uint32_t *)(*(this + 36) + 8),
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62AFB0 sub_62AFB0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_62AFB0 sub_60B6B0
int sub_62AFB0()
{
  return sub_60B6B0();  // 【CNMapObject__vmt14C】
}



// ------------------------------------------------------------
// 0x62DF50 sub_62DF50
// ------------------------------------------------------------
// 调: sub_62DF50
void sub_62DF50()
{
  dword_9B9454 = 0;
}



// ------------------------------------------------------------
// 0x633F10 sub_633F10
// ------------------------------------------------------------
// 调: sub_633F10
int /*thiscall*/ sub_633F10(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64B840 sub_64B840
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_64B840 sub_64B740
int sub_64B840()
{
  return sub_64B740();
}



// ------------------------------------------------------------
// 0x5F76F0 sub_5F76F0
// ------------------------------------------------------------
// 调: sub_5F76F0
int /*thiscall*/ sub_5F76F0(uint32_t *this)
{
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FFF80 sub_5FFF80
// ------------------------------------------------------------
// 调: sub_5FFF80
size_t /*thiscall*/ sub_5FFF80(int this, const void *pArg2, size_t Size)
{
  void *pMem; // eax
  void *pMem2; // edi

  if ( *(uint32_t *)(this + 968) != 0 )
    j__free(*(void **)(this + 968));
  *(uint32_t *)(this + 968) = 0;
  pMem = operator new(Size);
  *(uint32_t *)(this + 968) = pMem;
  pMem2 = pMem;
  qmemcpy(pMem2, pArg2, Size);
  *(uint32_t *)(this + 964) = Size;
  return Size;
}



// ------------------------------------------------------------
// 0x600060 sub_600060
// ------------------------------------------------------------
// 调: sub_600060
int /*stdcall*/ sub_600060(int nArg1)
{
  return nullsub_1(nArg1);
}



// ------------------------------------------------------------
// 0x603900 sub_603900
// ------------------------------------------------------------
// 调: sub_603900
int /*thiscall*/ sub_603900(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 100) = 0;
  *(uint8_t *)(this + 101) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6073B0 sub_6073B0
// ------------------------------------------------------------
// 调: sub_6073B0
void /*thiscall*/ sub_6073B0(uint8_t *this)
{
  *(this + 1036) = 0;
}



// ------------------------------------------------------------
// 0x612760 sub_612760
// ------------------------------------------------------------
// 调: sub_612760 sub_60ADE0
int /*stdcall*/ sub_612760(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)
{
  return sub_60ADE0(nArg1, nArg2, nArg3, nArg4, nArg5);  // 【CNMapObject__vmt2B4】
}



// ------------------------------------------------------------
// 0x61C750 sub_61C750
// ------------------------------------------------------------
// 调: sub_61C750 sub_5FF9C0
int /*thiscall*/ sub_61C750(void *this, int nArg2, int nArg3, int nArg4)
{
  float *pThis_15C; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) == 1 )
  {
    pThis_15C = (float *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this);
    *pThis_15C = *pThis_15C * 0.30000001;
  }
  return sub_5FF9C0(nArg2, nArg3, nArg4);  // 【CNRDPassiveObject__vmt1F4】
}



// ------------------------------------------------------------
// 0x621770 sub_621770
// ------------------------------------------------------------
// 调: sub_621770
int /*thiscall*/ sub_621770(uint32_t **this)
{
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 36));
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[1]);
  ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 12345);
  return ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 12346);
}



// ------------------------------------------------------------
// 0x621990 sub_621990
// ------------------------------------------------------------
// 证: "CRYSTAL_BREAK"
// 调: sub_621990 sub_4D7960 sub_4600B0 sub_621770 sub_517740
void /*userpurge*/ sub_621990(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int v8; // edi
  int v9; // eax
  void *v10; // ecx
  unsigned int i; // edx
  int v12; // ecx
  int v13; // edi
  unsigned int j; // ebx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  int v20; // ecx
  int pObj2; // edx
  int v22; // eax
  int v23; // ecx
  int pObj3; // ecx
  int v25; // eax
  int pObj; // eax
  int v27; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+20h] [ebp-4h]
  unsigned int v31; // [esp+34h] [ebp+10h]

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) <= nArg5 )
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 1;
  else
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 1;
  if ( *(uint8_t *)(v8 + pArg1 + 972) == 1 )
  {
    *(uint32_t *)(pArg1 + 4 * v8 + 976) -= nArg4;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);
    sub_4D7960(nArg7, v8, pArg1, nArg5, v9 + 1, nArg7, nArg4, 0, 0, 0);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
    if ( *(int *)(pArg1 + 4 * v8 + 976) <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 876) + 12))(*(uint32_t *)(pArg1 + 876), 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 876) + 40))(
        *(uint32_t *)(pArg1 + 876),
        nArg5,
        nArg6 + 1,
        nArg7 + 50);
      (*(void (/*thiscall*/ **)(uint32_t, int *))(**(uint32_t **)(pArg1 + 876) + 92))(*(uint32_t *)(pArg1 + 876), &v27);
      v10 = *(void **)(pArg1 + 116);
      v30 = 0;
      sub_4600B0(v10, 2, 0, (int)&v27);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
        pArg1,
        "CRYSTAL_BREAK",
        -1,
        0,
        0);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 208))(
          pArg1,
          *(uint32_t *)(*(uint32_t *)(pArg1 + 144) + 12),
          nArg2);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 144) + 8), nArg2);
      v29 = 0;
      Block = nullptr;
      v27 = 0;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 204))(pArg1);
      *(uint8_t *)(v8 + pArg1 + 972) = 0;
      if ( *(uint8_t *)(pArg1 + 972) == 0 && *(uint8_t *)(pArg1 + 973) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 604))(pArg1, 0);
        sub_621770((uint32_t **)pArg1);
        *(uint8_t *)(pArg1 + 984) = 0;
        for ( i = 0; ; i = v31 + 1 )
        {
          v12 = *(uint32_t *)(pArg1 + 996);
          v31 = i;
          if ( v12 == 0 || i >= (*(uint32_t *)(pArg1 + 1000) - v12) >> 2 )
            break;
          v13 = 4 * i;
          if ( *(uint32_t *)(v12 + 4 * i) != 0 )
          {
            for ( j = 0; ; ++j )
            {
              v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v13 + *(uint32_t *)(pArg1 + 996)) + 700))(*(uint32_t *)(v13 + *(uint32_t *)(pArg1 + 996)));
              v16 = *(uint32_t *)(v15 + 4);
              v17 = v16 != 0 ? (*(uint32_t *)(v15 + 8) - v16) >> 2 : 0;
              if ( (int)j >= v17 )
                break;
              v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v13 + *(uint32_t *)(pArg1 + 996)) + 700))(*(uint32_t *)(v13 + *(uint32_t *)(pArg1 + 996)));
              v19 = *(uint32_t *)(v18 + 4);
              if ( v19 != 0 && j < (*(uint32_t *)(v18 + 8) - v19) >> 2 )
                v20 = *(uint32_t *)(v19 + 4 * j);
              else
                v20 = 0;
              pObj2 = *(uint32_t *)(*(uint32_t *)(pArg1 + 996) + v13);
              if ( *(uint32_t *)(v20 + 4) == pObj2 )
              {
                v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 700))(pObj2);
                v23 = *(uint32_t *)(v22 + 4);
                if ( v23 != 0 && j < (*(uint32_t *)(v22 + 8) - v23) >> 2 )
                  pObj3 = *(uint32_t *)(v23 + 4 * j);
                else
                  pObj3 = 0;
                if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 64))(pObj3) + 32) == pArg1 )
                {
                  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v13 + *(uint32_t *)(pArg1 + 996)) + 700))(*(uint32_t *)(v13 + *(uint32_t *)(pArg1 + 996)));
                  v25 = sub_517740(j);
                  pObj = __RTDynamicCast(
                          v25,
                          0,
                          &IRDAppendage `RTTI Type Descriptor',
                          &CNWindSimulation `RTTI Type Descriptor',
                          0);
                  if ( pObj != 0 )
                  {
                    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
                    break;
                  }
                }
              }
            }
          }
        }
      }
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x623550 sub_623550
// ------------------------------------------------------------
// 调: sub_623550
int /*stdcall*/ sub_623550(uint32_t *uArg1, int nArg2)
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20) != 0 )
    return 3;
  *uArg1 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x6236B0 sub_6236B0
// ------------------------------------------------------------
// 调: sub_6236B0 sub_4926A0
int /*thiscall*/ sub_6236B0(uint32_t **this, int nArg2)
{
  int fld_e36; // eax
  uint32_t *v4; // ecx

  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 36));
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 36))[1]);
  sub_4926A0((*(this + 36))[nArg2]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    100,
    (*(this + 36))[nArg2],
    0,
    0,
    0,
    0);
  fld_e36 = (int)*(this + 36);
  v4 = *(uint32_t **)(fld_e36 + 4 * nArg2);
  *(this + 246) = v4;
  return 4 * nArg2 + fld_e36;
}



// ------------------------------------------------------------
// 0x62A8A0 sub_62A8A0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_62A8A0 sub_6000B0
int sub_62A8A0()
{
  return sub_6000B0();  // 【CNRDPassiveObject__vmtC】
}



// ------------------------------------------------------------
// 0x62AFC0 sub_62AFC0
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_62AFC0 sub_5FFE70
int sub_62AFC0()
{
  return sub_5FFE70();  // 【CNRDPassiveObject__vmt140】
}



// ------------------------------------------------------------
// 0x62DF60 sub_62DF60
// ------------------------------------------------------------
// attributes: thunk
// 调: sub_62DF60 sub_55A040
int sub_62DF60()
{
  return sub_55A040();  // 【IRDPopupWindow__vmt20】
}



// ------------------------------------------------------------
// 0x639D10 sub_639D10
// ------------------------------------------------------------
// 调: sub_639D10 sub_554930
int /*stdcall*/ sub_639D10(int nArg1)
{
  return sub_554930(nArg1);  // 【IRDPopupWindow__vmt0】
}


