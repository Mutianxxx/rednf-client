// ============================================================
// 【40JP逆向源代码工程】src/combat/swordman_skills.cpp
// 模块: 0x5F0000-0x600000
// 来源: work/dump 素材  区块: 0x5F0020-0x5FFE71 §A 技能 PO 基础与波系
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 129
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 技能 PO 基础与波系
// ============================================================
// 0x5F0020 CNSwordman__vmt518
// ------------------------------------------------------------
// 调: sub_53FE50 sub_4C2820 sub_5F9DD0 sub_5EE770 sub_650950
void /*thiscall*/ sub_5F0020(int *this, void *a2, void *Block)
{
  void *v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  uint32_t *v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // ebx
  int v16; // eax
  int v17; // ecx
  float v18; // [esp+4h] [ebp-1Ch]
  void *Blocka; // [esp+2Ch] [ebp+Ch]

  sub_4B3E70(this, a2, (int)Block);
  if ( a2 == (void *)12 || a2 == (void *)13 || a2 == (void *)14 || a2 == (void *)15 || a2 == (void *)4 )
  {
    v15 = 0;
    if ( a2 == (void *)13 )
    {
      v15 = 1;
    }
    else if ( a2 == (void *)14 )
    {
      v15 = 2;
    }
    else if ( a2 == (void *)15 )
    {
      v15 = 3;
    }
    else if ( a2 == (void *)4 )
    {
      v15 = 4;
    }
    if ( (int)Block <= 0 )
    {
      v17 = *(this + v15 + 2132);
      if ( v17 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 80))(v17) == 0 )
        return;
      v9 = *(this + v15 + 2132);
      goto LABEL_61;
    }
    if ( *(this + v15 + 2132) == 0 )
    {
      if ( operator new(0x88u) != nullptr )
        v16 = sub_4C2820(0, a2);
      else
        v16 = 0;
      *(this + v15 + 2132) = v16;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 64))(v16) + 36) = 0;
    }
    sub_5F9DD0(Block);
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + v15 + 2132) + 56))(
      *(this + v15 + 2132),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  else
  {
    if ( a2 == (void *)19 )
    {
      if ( (int)Block <= 0 )
      {
        v6 = *(this + 2137);
        if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6) != 0 )
          sub_53FE50(*(this + 2137));
      }
      else
      {
        if ( *(this + 2137) == 0 )
        {
          v4 = operator new(0x64u);
          if ( v4 != nullptr )
            v5 = sub_5EE770(v4);
          else
            v5 = 0;
          *(this + 2137) = v5;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 64))(v5) + 36) = 0;
        }
        sub_650950((uint32_t *)*(this + 2137), (int)Block);
        (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2137) + 56))(
          *(this + 2137),
          this,
          this,
          0,
          0,
          0,
          -1);
      }
      return;
    }
    if ( a2 == (void *)43 )
    {
      if ( (int)Block > 0 )
      {
        if ( *(this + 2138) == 0 )
        {
          if ( operator new(0x7Cu) != nullptr )
            v7 = sub_4B3C90(0, 0);
          else
            v7 = 0;
          *(this + 2138) = v7;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 64))(v7) + 36) = 0;
        }
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 43);
        Blocka = (void *)sub_47EE70(2, 3, Block);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2138) + 124))(*(this + 2138));
        v18 = (float)(int)Blocka;
        (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2138) + 120))(6, 0, LODWORD(v18));
        (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2138) + 56))(
          *(this + 2138),
          this,
          this,
          0,
          0,
          0,
          -1);
        return;
      }
      v8 = *(this + 2138);
      if ( v8 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 80))(v8) == 0 )
        return;
      v9 = *(this + 2138);
LABEL_61:
      sub_53FE50(v9);
      return;
    }
    if ( a2 == (void *)29 )
    {
      if ( (int)Block <= 0 )
      {
        v14 = *(this + 2139);
        if ( v14 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 80))(v14) == 0 )
          return;
        v9 = *(this + 2139);
        goto LABEL_61;
      }
      if ( *(this + 2139) == 0 )
      {
        if ( operator new(0x84u) != nullptr )
          v10 = sub_5E5B20(0, 0, nullptr);
        else
          v10 = 0;
        *(this + 2139) = v10;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 64))(v10) + 36) = 0;
        v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 29);
        v12 = sub_47E9D0(v11, 0);
        sub_5E5ED0(2, 0, v12);
        v13 = sub_47E9D0(v11, 1u);
        sub_5E5ED0(3, 0, v13);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2139) + 56))(
        *(this + 2139),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
    else if ( a2 == (void *)39 )
    {
      if ( (int)Block <= 0 )
      {
        *(this + 2131) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 39);
        *(this + 2131) = sub_47EF20(0, Block, -1, -1, 11);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x5F0460 sub_5F0460
// ------------------------------------------------------------
// 调: sub_5F0460 sub_431230
void /*usercall*/ sub_5F0460(uint32_t *a1@<ecx>, int a2@<edi>)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  char v9; // al
  int v10; // edx
  bool v11; // zf
  int v12; // eax
  int v13; // ecx
  uint8_t v14[4]; // [esp+8h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-24h]
  int v16; // [esp+10h] [ebp-20h]
  int v17; // [esp+14h] [ebp-1Ch]
  int v18; // [esp+18h] [ebp-18h] BYREF
  int v19; // [esp+1Ch] [ebp-14h] BYREF
  int v20; // [esp+20h] [ebp-10h] BYREF
  int v21; // [esp+2Ch] [ebp-4h]

  v3 = a1[2114];
  if ( v3 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 308))(v3) != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[2114] + 120))(a1[2114], a2);
      v5 = a1[2114];
      v19 = v4;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
      v7 = a1[2114];
      v20 = v6;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 128))(v7);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)a1[2114] + 136))(
             a1[2114],
             v19,
             v20,
             0) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[2114] + 132))(a1[2114], v8) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)a1[2114] + 108))(a1[2114], v19, v20, v8);
      }
      else
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)a1[2114] + 140))(
               a1[2114],
               &v19,
               &v20,
               v19,
               v20,
               100,
               1,
               1);
        v10 = *(uint32_t *)a1[2114];
        if ( v9 != 0 )
        {
          (*(void (/*stdcall*/ **)(int, int))(v10 + 108))(v19, v20);
        }
        else
        {
          v11 = (*(uint8_t (/*cdecl*/ **)(int))(v10 + 132))(v8) == 0;
          v12 = *(uint32_t *)a1[2114];
          if ( v11 )
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(v12 + 108))(a1[2115], a1[2116], a1[2117]);
          else
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(v12 + 108))(a1[2115], a1[2116], v8);
        }
      }
      Block = nullptr;
      v16 = 0;
      v17 = 0;
      v21 = 0;
      v18 = 4;
      sub_431230((int)v14, &v18);
      v18 = 0;
      sub_431230((int)v14, &v18);
      v18 = 1;
      sub_431230((int)v14, &v18);
      v18 = 1000;
      sub_431230((int)v14, &v18);
      v18 = 100;
      sub_431230((int)v14, &v18);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int))(*(uint32_t *)a1[2114] + 560))(a1[2114], 4, v14, 2);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[2114] + 564))(a1[2114]);
      v21 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v16 = 0;
      v17 = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[2114] + 596))(a1[2114], 1);
    v13 = a1[2120];
    a1[2114] = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 76))(v13, 0);
  }
}



// ------------------------------------------------------------
// 0x5F0660 sub_5F0660
// ------------------------------------------------------------
// 调: sub_5F0660 sub_5910D0 sub_650F20 sub_6519E0
uint32_t */*thiscall*/ sub_5F0660(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  sub_5910D0(0, 18, 250, 0);
  *this = &vftbl_CNDOTArea;
  *(this + 43) = 0;
  *(this + 44) = 0;
  *(this + 45) = 0;
  sub_650F20(this);
  sub_6519E0(a2, a3, a4, a5, a6);
  return this;
}



// ------------------------------------------------------------
// 0x5F06F0 CNDOTArea__vmt0
// ------------------------------------------------------------
// 调: sub_5F0720
void */*thiscall*/ CNDOTArea__vmt0(void *Block, char a2)
{
  sub_5F0720();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5F0720 sub_5F0720
// ------------------------------------------------------------
// 调: sub_5F0720 sub_650F70 sub_591190
int /*thiscall*/ sub_5F0720(void **this)
{
  *this = &vftbl_CNDOTArea;
  sub_650F70();
  if ( *(this + 43) != nullptr )
    j__free(*(this + 43));
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x5F07A0 CNSwordman__vmt514
// ------------------------------------------------------------
// 证: "Common/CommonEffect/BuffIcon.img"
// 调: sub_41A5E0 sub_47EF20 sub_510350 sub_418DD0
int /*thiscall*/ sub_5F07A0(int this, char *a2, void *a3)
{
  int result; // eax
  int v6; // eax
  int v7; // ecx
  unsigned int v8; // ebx
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  int *v14; // eax
  int v15; // ebx
  uint32_t *v16; // eax
  int v17; // eax
  void *v18; // eax
  int v19; // eax
  int v20; // ebx
  uint32_t *v21; // eax
  int v22; // eax
  float v23; // edx
  void *v24; // eax
  int v25; // eax
  int v26; // edi
  uint32_t *v27; // eax
  uint8_t *v28; // eax
  uint8_t *v29; // eax
  int v30; // edi
  int v31; // ebx
  int v32; // edi
  uint32_t *v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // ebx
  int v39; // eax
  float v40; // [esp+0h] [ebp-34h]
  int v41; // [esp+4h] [ebp-30h]
  float v42; // [esp+8h] [ebp-2Ch]
  float v43; // [esp+Ch] [ebp-28h]
  int v44; // [esp+Ch] [ebp-28h]
  unsigned int v45; // [esp+10h] [ebp-24h]
  int v46; // [esp+10h] [ebp-24h]
  int v47; // [esp+14h] [ebp-20h]
  int v48; // [esp+1Ch] [ebp-18h]
  int v49; // [esp+1Ch] [ebp-18h]
  void *v50; // [esp+20h] [ebp-14h]
  int *Block; // [esp+24h] [ebp-10h]
  void *v52; // [esp+3Ch] [ebp+8h]
  void *v53; // [esp+3Ch] [ebp+8h]
  float v54; // [esp+3Ch] [ebp+8h]
  void *v55; // [esp+40h] [ebp+Ch]

  sub_4B4170((float *)this, a2, a3);
  result = sub_41A5E0((unsigned int)(a2 + 4));
  switch ( result )
  {
    case 30:
      v50 = (void *)sub_47EF20(0, a3, -1, -1, 11);
      v48 = sub_47EF20(1, a3, -1, -1, 11);
      v6 = *(uint32_t *)(this + 116);
      v7 = *(uint32_t *)(v6 + 120);
      result = v6 + 116;
      v8 = 0;
      if ( v7 != 0 )
      {
        result = (*(uint32_t *)(result + 8) - v7) >> 2;
        v52 = (void *)result;
      }
      else
      {
        v52 = nullptr;
      }
      v55 = nullptr;
      if ( (int)v52 > 0 )
      {
        do
        {
          v9 = *(uint32_t *)(this + 116);
          v10 = *(uint32_t *)(v9 + 120);
          if ( v10 != 0 && v8 < (*(uint32_t *)(v9 + 124) - v10) >> 2 )
            v11 = *(uint32_t *)(v10 + 4 * v8);
          else
            v11 = 0;
          v12 = __RTDynamicCast(
                  v11,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          if ( v12 != 0 )
          {
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 376))(v12);
            if ( v13 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )
            {
              if ( operator new(0x84u) != nullptr )
                v14 = (int *)sub_510350(2, 0, v48, v50, 1, nullptr);
              else
                v14 = nullptr;
              v15 = *v14;
              Block = v14;
              v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(*(uint32_t *)dword_8F84B8 + 60))(
                                dword_8F84B8,
                                "Common/CommonEffect/BuffIcon.img",
                                1,
                                6,
                                -1);
              v45 = sub_418DD0(v16, v45);
              (*(void (/*thiscall*/ **)(int *, int, int, int))(v15 + 56))(Block, v12, this, 1);
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v12 + 212))(
                v12,
                "BUFF_MOONCURTAIN",
                -1,
                0,
                0);
            }
            v8 = (unsigned int)v55;
          }
          result = (int)v52;
          v55 = (void *)++v8;
        }
        while ( (int)v8 < (int)v52 );
      }
      break;
    case 38:
      v53 = (void *)sub_47EF20(0, a3, -1, -1, 11);
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      v49 = sub_47EFD0(a2, COERCE_FLOAT(2), (int)a3, v17, v17, 0);
      if ( *(uint32_t *)(this + 8428) == 0 )
      {
        v18 = operator new(0x7Cu);
        if ( v18 != nullptr )
          v19 = sub_4B3C90((int)v18, 0, 1);
        else
          v19 = 0;
        *(uint32_t *)(this + 8428) = v19;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 64))(v19) + 36) = 0;
      }
      *(uint32_t *)(*(uint32_t *)(this + 8428) + 44) = v53;
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8428) + 124))(*(uint32_t *)(this + 8428));
      v43 = (float)v49;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8428) + 120))(4, 0, LODWORD(v43));
      v20 = **(uint32_t **)(this + 8428);
      v21 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                        dword_8F84B8,
                        "Common/CommonEffect/BuffIcon.img",
                        7,
                        0,
                        -1);
      sub_418DD0(v21, v45);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(v20 + 56))(*(uint32_t *)(this + 8428), this, this, 1);
      v22 = sub_47EF20(1, a3, -1, -1, 11);
      v23 = *(float *)this;
      *(uint32_t *)(this + 8520) = v22;
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(LODWORD(v23) + 212))(
               this,
               "BUFF_OVERDRIVE",
               -1,
               0,
               0);
    case 40:
      if ( *(uint32_t *)(this + 8432) == 0 )
      {
        v24 = operator new(0x70u);
        if ( v24 != nullptr )
          v25 = sub_5EE850(v24);
        else
          v25 = 0;
        *(uint32_t *)(this + 8432) = v25;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 64))(v25) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t, void *))(**(uint32_t **)(this + 8432) + 120))(*(uint32_t *)(this + 8432), a3);
      v26 = **(uint32_t **)(this + 8432);
      v27 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                        dword_8F84B8,
                        "Common/CommonEffect/BuffIcon.img",
                        12,
                        0,
                        -1);
      v46 = sub_418DD0(v27, v45);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(v26 + 56))(*(uint32_t *)(this + 8432), this, this, 1);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)this + 1160))(this, 40, this, -1);
      sub_47DCD0(v46, v47);
      return (*(int (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)this + 212))(this, "BUFF_CONGESTION", -1);
    case 18:
      if ( *(uint32_t *)(this + 8436) == 0 )
      {
        v28 = operator new(0x50u);
        if ( v28 != nullptr )
          v29 = sub_4B1030(v28);
        else
          v29 = nullptr;
        *(uint32_t *)(this + 8436) = v29;
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v29 + 64))(v29) + 36) = 0;
      }
      v30 = *(uint32_t *)(this + 8436);
      v41 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, 18, -1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);
      v31 = sub_47EF20(18, 0, v41, -1, 11);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 64))(v30) + 40) = v31;
      v32 = **(uint32_t **)(this + 8436);
      v33 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                        dword_8F84B8,
                        "Common/CommonEffect/BuffIcon.img",
                        20,
                        0,
                        -1);
      sub_418DD0(v33, v45);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(v32 + 56))(*(uint32_t *)(this + 8436), this, this, 1);
      *(uint8_t *)(this + 8440) = 1;
      sub_49C620((int *)this, 1, 1, 0);
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "G_GHOSTSTEP_DISAPPEAR",
               -1,
               0,
               0);
    case 52:
      if ( *(uint32_t *)(this + 8444) == 0 )
      {
        if ( operator new(0xBCu) != nullptr )
        {
          v34 = sub_47E9D0(a2, 0);
          v35 = sub_5F0660(0, 0, 0, 0, v34);
        }
        else
        {
          v35 = 0;
        }
        *(uint32_t *)(this + 8444) = v35;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v35 + 64))(v35) + 36) = 0;
      }
      v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      v37 = sub_47EFD0(a2, COERCE_FLOAT(1), (int)a3, v36, v36, 0);
      v38 = **(uint32_t **)(this + 8444);
      v54 = (double)v37 * 0.1;
      v44 = sub_47E9D0(a2, 0);
      v42 = (double)sub_47E9D0(a2, 1u) * v54 * 0.0099999998;
      v40 = (double)(int)sub_47EF20(0, a3, -1, -1, 11) * 0.1;
      v39 = sub_47EF20(2, a3, -1, -1, 11);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, int))(v38 + 148))(
        *(uint32_t *)(this + 8444),
        v39 / 2,
        LODWORD(v40),
        LODWORD(v54),
        LODWORD(v42),
        v44);
      return (*(int (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8444) + 56))(
               *(uint32_t *)(this + 8444),
               this,
               this,
               1,
               0,
               0,
               -1);
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F0D40 sub_5F0D40
// ------------------------------------------------------------
// 调: sub_5F0D40 sub_42AF90 sub_657740
int /*thiscall*/ sub_5F0D40(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void ***v3; // edi
  int v4; // ebx
  void **v5; // ebx
  bool v6; // zf
  int v7; // edi
  void **v8; // edi
  void **v9; // edi
  void **v10; // edi
  void ***v11; // edi
  int v12; // ebx
  void **v13; // ebx
  void ***v14; // edi
  void **v15; // ebx
  int v16; // edi
  void (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v18)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v19)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v20)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v21)(uint32_t, int); // ecx
  void **v22; // edi
  void **v23; // edi
  void ***v24; // edi
  void **v25; // ebx
  uint32_t *v26; // edi
  int n; // ebx
  void (/*thiscall*/ ***v28)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v29)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v30)(uint32_t, int); // ecx
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]
  int k; // [esp+4h] [ebp-4h]
  int m; // [esp+4h] [ebp-4h]

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8260);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 8260) = 0;
  v3 = (void ***)(this + 8296);
  for ( i = 2; i != 0; --i )
  {
    v4 = (int)*(v3 - 2);
    if ( v4 != 0 )
    {
      sub_42AF90(*(v3 - 2));
      sub_657740(v4, 228);
    }
    v5 = *v3;
    v6 = *v3 == nullptr;
    *(v3 - 2) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v5);
      sub_657740(v5, 228);
    }
    *v3++ = nullptr;
  }
  v7 = *(uint32_t *)(this + 8336);
  if ( v7 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8336));
    sub_657740(v7, 228);
  }
  v8 = *(void ***)(this + 8368);
  *(uint32_t *)(this + 8336) = 0;
  if ( v8 != nullptr )
  {
    sub_42AF90(v8);
    sub_657740(v8, 228);
  }
  v9 = *(void ***)(this + 8372);
  *(uint32_t *)(this + 8368) = 0;
  if ( v9 != nullptr )
  {
    sub_42AF90(v9);
    sub_657740(v9, 228);
  }
  v10 = *(void ***)(this + 8376);
  *(uint32_t *)(this + 8372) = 0;
  if ( v10 != nullptr )
  {
    sub_42AF90(v10);
    sub_657740(v10, 228);
  }
  *(uint32_t *)(this + 8376) = 0;
  v11 = (void ***)(this + 8388);
  for ( j = 2; j != 0; --j )
  {
    v12 = (int)*(v11 - 2);
    if ( v12 != 0 )
    {
      sub_42AF90(*(v11 - 2));
      sub_657740(v12, 228);
    }
    v13 = *v11;
    v6 = *v11 == nullptr;
    *(v11 - 2) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v13);
      sub_657740(v13, 228);
    }
    *v11++ = nullptr;
  }
  v14 = (void ***)(this + 8404);
  for ( k = 2; k != 0; --k )
  {
    v15 = *v14;
    if ( *v14 != nullptr )
    {
      sub_42AF90(*v14);
      sub_657740(v15, 228);
    }
    *v14++ = nullptr;
  }
  v16 = *(uint32_t *)(this + 8416);
  if ( v16 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8416));
    sub_657740(v16, 228);
  }
  v17 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8428);
  *(uint32_t *)(this + 8416) = 0;
  if ( v17 != nullptr )
    (**v17)(v17, 1);
  v18 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8432);
  *(uint32_t *)(this + 8428) = 0;
  if ( v18 != nullptr )
    (**v18)(v18, 1);
  v19 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8436);
  *(uint32_t *)(this + 8432) = 0;
  if ( v19 != nullptr )
    (**v19)(v19, 1);
  v20 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8444);
  *(uint32_t *)(this + 8436) = 0;
  if ( v20 != nullptr )
    (**v20)(v20, 1);
  v21 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8480);
  *(uint32_t *)(this + 8444) = 0;
  if ( v21 != nullptr )
    (**v21)(v21, 1);
  v22 = *(void ***)(this + 8484);
  *(uint32_t *)(this + 8480) = 0;
  if ( v22 != nullptr )
  {
    sub_42AF90(v22);
    sub_657740(v22, 228);
  }
  v23 = *(void ***)(this + 8500);
  *(uint32_t *)(this + 8484) = 0;
  if ( v23 != nullptr )
  {
    sub_42AF90(v23);
    sub_657740(v23, 228);
  }
  *(uint32_t *)(this + 8500) = 0;
  v24 = (void ***)(this + 8504);
  for ( m = 2; m != 0; --m )
  {
    v25 = *v24;
    if ( *v24 != nullptr )
    {
      sub_42AF90(*v24);
      sub_657740(v25, 228);
    }
    *v24++ = nullptr;
  }
  v26 = (uint32_t *)(this + 8528);
  for ( n = 5; n != 0; --n )
  {
    if ( *v26 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v26)(*v26, 1);
    *v26++ = 0;
  }
  v28 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8548);
  if ( v28 != nullptr )
    (**v28)(v28, 1);
  v29 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8552);
  *(uint32_t *)(this + 8548) = 0;
  if ( v29 != nullptr )
    (**v29)(v29, 1);
  v30 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8556);
  result = 0;
  *(uint32_t *)(this + 8552) = 0;
  if ( v30 != nullptr )
    result = (**v30)(v30, 1);
  *(uint32_t *)(this + 8556) = 0;
  return result;
}


// ------------------------------------------------------------
// ============================================================
// §B 蓄力与血系
// ============================================================
// 0x5F6610 sub_5F6610
// ------------------------------------------------------------
// 调: sub_5F6610
int /*thiscall*/ sub_5F6610(int this)
{
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = -1;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 76) = -1;
  *(uint32_t *)(this + 72) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F6640 sub_5F6640
// ------------------------------------------------------------
// 调: sub_5F6640 sub_53FE50
int /*thiscall*/ sub_5F6640(uint32_t *this)
{
  int result; // eax
  uint32_t *v2; // ecx

  result = (int)this;
  v2 = (uint32_t *)*(this + 12);
  if ( v2 != nullptr )
    return sub_53FE50(v2, result);
  return result;
}



// ------------------------------------------------------------
// 0x5F6650 IRDAppendage__vmt54
// ------------------------------------------------------------
// 调: sub_699030 sub_698FE0
char /*thiscall*/ IRDAppendage__vmt54(uint8_t *this, char a2)
{
  char result; // al
  uint8_t *v3; // ecx

  result = a2;
  if ( *(this + 53) != a2 )
  {
    *(this + 53) = a2;
    v3 = this + 8;
    if ( a2 != 0 )
      return sub_699030((int)v3);
    else
      return sub_698FE0((int)v3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6680 IRDAppendage__vmt30
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ IRDAppendage__vmt30(uint32_t *this, int a2)
{
  int result; // eax

  result = *(this + 9);
  if ( result == a2 )
    *(this + 9) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5F66A0 sub_5F66A0
// ------------------------------------------------------------
// 调: sub_5F66A0 sub_699000
char /*thiscall*/ sub_5F66A0(int this, char a2)
{
  int v2; // eax

  LOBYTE(v2) = a2;
  *(uint8_t *)(this + 68) = a2;
  if ( a2 != 0 )
  {
    v2 = sub_699000(this + 8);
    *(uint32_t *)(this + 76) = v2;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5F66C0 IRDAppendage__vmt4
// ------------------------------------------------------------
// 调: sub_699000
char /*thiscall*/ IRDAppendage__vmt4(int *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  unsigned int v5; // eax
  int v6; // eax
  int v7; // edx

  v2 = sub_699000((int)(this + 2));
  v3 = *(this + 11);
  v4 = v2;
  if ( v3 != 0 && v2 >= v3 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  if ( *((uint8_t *)this + 54) != 0 && *(this + 14) != 0 )
  {
    if ( v3 != 0 && v4 >= v3 - 1200 )
    {
      if ( *(this + 15) == -1 )
        (*(void (/*thiscall*/ **)(int *))(*this + 112))(this);
    }
    else if ( v4 >= 1000 )
    {
      *(this + 15) = -1;
    }
  }
  LOBYTE(v5) = *((uint8_t *)this + 68);
  if ( (uint8_t)v5 != 0 )
  {
    v5 = sub_699000((int)(this + 2));
    if ( *(this + 19) + *(this + 18) < v5 )
    {
      v6 = sub_699000((int)(this + 2));
      v7 = *this;
      *(this + 19) = v6;
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(int *))(v7 + 104))(this);
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x5F6750 sub_5F6750
// ------------------------------------------------------------
// 调: sub_5F6750
int /*thiscall*/ sub_5F6750(int this)
{
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 68) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F6760 IRDAppendage__vmt38
// ------------------------------------------------------------
// 调: sub_53FE50 sub_53FEE0 sub_5402D0 sub_698F90
void /*thiscall*/ IRDAppendage__vmt38(uint32_t *this, int a2, int a3, char a4, int a5, unsigned int ArgList, int a7)
{
  int v7; // ebx
  uint32_t *v9; // ecx
  uint32_t *v10; // edi
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  int v12; // eax
  unsigned int v13; // ebx
  int v14; // ecx
  uint32_t *v15; // edi
  uint32_t *v16; // [esp+8h] [ebp-10h]
  int v17; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+10h] [ebp-8h]
  int v19; // [esp+14h] [ebp-4h]
  int (/*thiscall*/ ***v20)(uint32_t, int); // [esp+34h] [ebp+1Ch]

  v7 = a2;
  if ( a2 == 0 )
    return;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) != 0 )
  {
    v9 = (uint32_t *)*(this + 12);
    if ( v9 != nullptr )
      sub_53FE50(v9, (int)this);
  }
  v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
  v16 = v10;
  v18 = a7;
  if ( a7 != -1 )
    goto LABEL_9;
  if ( ArgList < 0x38 )
  {
    v18 = dword_73A0D0[ArgList];
LABEL_9:
    v11 = nullptr;
    if ( v18 != 0 )
    {
      v12 = v10[1];
      v17 = 0;
      v20 = nullptr;
      if ( v12 != 0 )
        v19 = (v10[2] - v12) >> 2;
      else
        v19 = 0;
      v13 = 0;
      if ( v19 > 0 )
      {
        do
        {
          v14 = v10[1];
          if ( v14 != 0 && v13 < (v10[2] - v14) >> 2 )
            v15 = *(uint32_t **)(v14 + 4 * v13);
          else
            v15 = nullptr;
          if ( v15[16] == ArgList && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v15 + 80))(v15) != 0 )
          {
            if ( v20 == nullptr )
              v20 = (int (/*thiscall*/ ***)(uint32_t, int))v15;
            ++v17;
          }
          v10 = v16;
          ++v13;
        }
        while ( (int)v13 < v19 );
        v11 = v20;
      }
      if ( v17 >= v18 )
      {
        if ( *(uint8_t *)(((int (/*thiscall*/ *)(int (/*thiscall*/ ***)(uint32_t, int)))(*v11)[16])(v11) + 36) != 0 )
          sub_53FEE0(v10, v20);
        else
          sub_53FE50(v10, (int)v20);
      }
      v7 = a2;
    }
    goto LABEL_30;
  }
  off_77F3FC(aCriticalErorrA, ArgList);
LABEL_30:
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
  sub_5402D0(this);
  *(this + 1) = v7;
  *((uint8_t *)this + 21) = 0;
  *((uint8_t *)this + 22) = 0;
  sub_698F90((int)(this + 2), 0, 0);
  *(this + 9) = a3;
  *((uint8_t *)this + 54) = a4;
  *(this + 14) = a5;
  *(this + 16) = ArgList;
  if ( a4 != 0 && a5 != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 108))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 76))(this, 1);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 28))(this);
}



// ------------------------------------------------------------
// 0x5F68E0 IRDAppendage__vmt74
// ------------------------------------------------------------
// 证: 叶子函数（37 行，无外调无字符串）
int /*thiscall*/ IRDAppendage__vmt74(uint32_t *this)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  unsigned int j; // esi
  int v7; // eax
  int v8; // ecx
  uint32_t *v9; // ecx
  int i; // [esp+4h] [ebp-4h]

  if ( *(this + 12) == 0 )
    return 0;
  for ( i = 0; ; ++i )
  {
    v3 = *(this + 12);
    v4 = *(uint32_t *)(v3 + 4);
    if ( v4 != 0 )
      v5 = (*(uint32_t *)(v3 + 8) - v4) >> 2;
    else
      v5 = 0;
    for ( j = 0; (int)j < v5; ++j )
    {
      v7 = *(this + 12);
      v8 = *(uint32_t *)(v7 + 4);
      if ( v8 != 0 && j < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
        v9 = *(uint32_t **)(v8 + 4 * j);
      else
        v9 = nullptr;
      if ( v9 != this && (*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 100))(v9) == i )
        break;
    }
    if ( j == v5 )
      break;
  }
  return i;
}



// ------------------------------------------------------------
// 0x5F6970 IRDAppendage__vmt6C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/BuffStartIcon." | "Common/CommonEffect/Animation/BuffStartIconG" |
//  "Common/CommonEffect/Animation/BuffStartGlow."
// 调: sub_42FCB0 sub_431860 sub_4924C0 sub_44B6C0 sub_44E0D0
void /*usercall*/ sub_5F6970(uint32_t *a1@<ecx>, int a2@<edi>)
{
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edx
  int v7; // edi
  int *v8; // edi
  int v9; // eax
  char *v10; // eax
  char *v11; // ebx
  char *v12; // eax
  int v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // ebx
  char *v17; // eax
  char *v18; // edi
  int j; // edi
  int v20; // eax
  int v21; // edi
  uint8_t v22[4]; // [esp+8h] [ebp-3Ch] BYREF
  void *Block; // [esp+Ch] [ebp-38h]
  uint32_t v24[3]; // [esp+18h] [ebp-2Ch]
  void *v25; // [esp+24h] [ebp-20h]
  int v26; // [esp+28h] [ebp-1Ch]
  int v27; // [esp+2Ch] [ebp-18h]
  int v28; // [esp+30h] [ebp-14h]
  char *i; // [esp+34h] [ebp-10h]
  int v30; // [esp+40h] [ebp-4h]

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 116))(a1);
  v4 = a1[1];
  a1[15] = v3;
  if ( v4 != 0 )
  {
    v25 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4);
    if ( v25 != nullptr )
    {
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 120))(v4, a2);
      v6 = *(uint32_t *)v4;
      v26 = v5;
      v27 = (*(int (/*thiscall*/ **)(int))(v6 + 124))(v4);
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 192))(v4);
      v28 = 30 * (a1[15] + 1) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4) + v7;
      v8 = nullptr;
      v30 = 0;
      if ( sub_42FCB0(228) != 0 )
        v8 = (int *)sub_431860((char)"Common/CommonEffect/Animation/BuffStartIcon.ani", 1);
      v30 = -1;
      for ( i = nullptr; ; ++i )
      {
        v9 = v8[11];
        if ( v9 != 0 )
          v9 = (v8[12] - v9) / 88;
        if ( (int)i >= v9 )
          break;
        *(uint32_t *)sub_4924C0(v8, (int)i) = a1[14];
      }
      v10 = (char *)sub_44B6C0(284);
      v11 = v10;
      i = v10;
      v30 = 1;
      if ( v10 != nullptr )
      {
        sub_44E0D0(v10, (int)v8, 1);
        *(uint32_t *)v11 = &CNRDPooledObject::`vftable';
        v12 = v11;
      }
      else
      {
        v12 = nullptr;
      }
      v24[0] = v12;
      v30 = 2;
      if ( sub_42FCB0(228) != 0 )
        v13 = sub_431860((char)"Common/CommonEffect/Animation/BuffStartIconGlow.ani", 1);
      else
        v13 = 0;
      v14 = (char *)sub_44B6C0(284);
      v15 = v14;
      i = v14;
      v30 = 3;
      if ( v14 != nullptr )
      {
        sub_44E0D0(v14, v13, 1);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v15 = nullptr;
      }
      v24[1] = v15;
      v30 = 4;
      if ( sub_42FCB0(228) != 0 )
        v16 = sub_431860((char)"Common/CommonEffect/Animation/BuffStartGlow.ani", 1);
      else
        v16 = 0;
      v17 = (char *)sub_44B6C0(284);
      v18 = v17;
      i = v17;
      v30 = 5;
      if ( v17 != nullptr )
      {
        sub_44E0D0(v17, v16, 1);
        *(uint32_t *)v18 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v18 = nullptr;
      }
      v24[2] = v18;
      v30 = -1;
      for ( j = 0; j < 3; ++j )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v24[j] + 72))(v24[j]);
        sub_45FE80((int)v25, j, 2, 0, v24[j], v4, 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)v24[j] + 112))(v24[j], v26, v27, v28);
        v20 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v24[j] + 60))(v24[j], v4);
        sub_4A06D0(v20, 2);
      }
      v21 = dword_8F82E4;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F82E4 + 112))(dword_8F82E4, v4);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v21 + 40))(v21, v26, v27, v28);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v21 + 12))(v21, 0);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v21 + 92))(v21, v22);
      v30 = 6;
      sub_4600B0(v25, 2, 0, (int)v22);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v4 + 212))(
        v4,
        "BUFF_ICON_SET",
        -1,
        0,
        0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}


// ------------------------------------------------------------
// 0x5F6C50 IRDAppendage__vmt70
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/BuffEndIcon.an" | "Common/CommonEffect/Animation/BuffEndIconGlo"
// 调: sub_42FCB0 sub_431860 sub_4924C0 sub_44B6C0 sub_44E0D0
int /*thiscall*/ IRDAppendage__vmt70(int *this)
{
  int result; // eax
  int v3; // esi
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  char *v10; // eax
  char *v11; // ebx
  char *v12; // eax
  int v13; // eax
  int v14; // ebx
  char *v15; // eax
  char *v16; // edi
  int j; // edi
  uint32_t v18[2]; // [esp+8h] [ebp-28h]
  int v19; // [esp+10h] [ebp-20h]
  int v20; // [esp+14h] [ebp-1Ch]
  int v21; // [esp+18h] [ebp-18h]
  int v22; // [esp+1Ch] [ebp-14h]
  char *i; // [esp+20h] [ebp-10h]
  int v24; // [esp+2Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*this + 116))(this);
  v3 = *(this + 1);
  *(this + 15) = result;
  if ( v3 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3);
    v22 = result;
    if ( result != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
      v5 = *(uint32_t *)v3;
      v19 = v4;
      v20 = (*(int (/*thiscall*/ **)(int))(v5 + 124))(v3);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 192))(v3);
      v21 = 30 * (*(this + 15) + 1) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3) + v6;
      v7 = sub_42FCB0(228);
      i = (char *)v7;
      v8 = 0;
      v24 = 0;
      if ( v7 != 0 )
        v8 = sub_431860(v7, "Common/CommonEffect/Animation/BuffEndIcon.ani", 1);
      v24 = -1;
      for ( i = nullptr; ; ++i )
      {
        v9 = *(uint32_t *)(v8 + 44);
        if ( v9 != 0 )
          v9 = (*(uint32_t *)(v8 + 48) - v9) / 88;
        if ( (int)i >= v9 )
          break;
        *(uint32_t *)sub_4924C0(i) = *(this + 14);
      }
      v10 = (char *)sub_44B6C0(284);
      v11 = v10;
      i = v10;
      v24 = 1;
      if ( v10 != nullptr )
      {
        sub_44E0D0(v10, v8, 1);
        *(uint32_t *)v11 = &vftbl_CNRDPooledObject;
        v12 = v11;
      }
      else
      {
        v12 = nullptr;
      }
      v18[0] = v12;
      v13 = sub_42FCB0(228);
      i = (char *)v13;
      v24 = 2;
      if ( v13 != 0 )
        v14 = sub_431860(v13, "Common/CommonEffect/Animation/BuffEndIconGlow.ani", 1);
      else
        v14 = 0;
      v15 = (char *)sub_44B6C0(284);
      v16 = v15;
      i = v15;
      v24 = 3;
      if ( v15 != nullptr )
      {
        sub_44E0D0(v15, v14, 1);
        *(uint32_t *)v16 = &vftbl_CNRDPooledObject;
      }
      else
      {
        v16 = nullptr;
      }
      v18[1] = v16;
      v24 = -1;
      for ( j = 0; j < 2; ++j )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v18[j] + 72))(v18[j]);
        sub_45FE80(v22, j, 2, 0, v18[j], v3, 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)v18[j] + 112))(v18[j], v19, v20, v21);
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v18[j] + 60))(v18[j], v3);
        result = sub_4A06D0(2);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6E50 sub_5F6E50
// ------------------------------------------------------------
// 调: sub_5F6E50
int /*thiscall*/ sub_5F6E50(uint32_t *this)
{
  *(this + 20) = 4;
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
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  *(this + 43) = 0;
  *(this + 44) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F6ED0 sub_5F6ED0
// ------------------------------------------------------------
// 调: sub_5F6ED0
int /*thiscall*/ sub_5F6ED0(uint32_t *this, int a2)
{
  *(this + 20) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x5F6EE0 sub_5F6EE0
// ------------------------------------------------------------
// 调: sub_5F6EE0
int /*thiscall*/ sub_5F6EE0(uint32_t *this, int a2)
{
  int result; // eax

  result = a2 - 172;
  switch ( a2 )
  {
    case 172:
      *(this + 33) = 0;
      *(this + 34) = 0;
      *(this + 35) = 0;
      result = 0;
      break;
    case 173:
      *(this + 36) = 0;
      *(this + 37) = 0;
      *(this + 38) = 0;
      *(this + 39) = 0;
      result = 0;
      break;
    case 174:
      *(this + 40) = 0;
      *(this + 41) = 0;
      *(this + 42) = 0;
      *(this + 43) = 0;
      *(this + 44) = 0;
      result = 0;
      break;
    case 185:
      *(this + 31) = 0;
      *(this + 32) = 0;
      result = 0;
      break;
    case 187:
      *(this + 26) = 0;
      *(this + 27) = 0;
      *(this + 28) = 0;
      *(this + 29) = 0;
      *(this + 30) = 0;
      result = 0;
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F6FB0 sub_5F6FB0
// ------------------------------------------------------------
// 调: sub_5F6FB0 sub_41A5E0
int /*thiscall*/ sub_5F6FB0(int this)
{
  float *v2; // ebx
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  double v7; // st7
  int v8; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  v8 = 10;
  v2 = (float *)&unk_73A2F4;
  do
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 792))(*(uint32_t *)(this + 4), v8);
    v4 = result;
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);
      if ( (uint8_t)result == 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 172))(v4);
        v6 = sub_41A5E0(v5 + 4);
        v7 = *v2 + *(float *)(this + 4 * v6 + 84);
        result = this + 4 * v6 + 84;
        *(float *)result = v7;
      }
    }
    ++v2;
    ++v8;
  }
  while ( (int)v2 <= (int)&flt_73A304 );
  return result;
}



// ------------------------------------------------------------
// 0x5F7040 CNArmorMastery__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
void /*thiscall*/ sub_5F7040(int this, int a2)
{
  int v4; // edx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // edx
  int v22; // edx
  float v23; // [esp+Ch] [ebp-4h]
  float v24; // [esp+Ch] [ebp-4h]
  float v25; // [esp+Ch] [ebp-4h]
  float v26; // [esp+Ch] [ebp-4h]
  float v27; // [esp+Ch] [ebp-4h]
  float v28; // [esp+Ch] [ebp-4h]
  float v29; // [esp+Ch] [ebp-4h]
  float v30; // [esp+Ch] [ebp-4h]
  float v31; // [esp+Ch] [ebp-4h]
  float v32; // [esp+Ch] [ebp-4h]
  float v33; // [esp+Ch] [ebp-4h]
  float v34; // [esp+Ch] [ebp-4h]
  float v35; // [esp+Ch] [ebp-4h]
  float v36; // [esp+Ch] [ebp-4h]
  int v37; // [esp+18h] [ebp+8h]
  int v38; // [esp+18h] [ebp+8h]
  int v39; // [esp+18h] [ebp+8h]
  int v40; // [esp+18h] [ebp+8h]
  int v41; // [esp+18h] [ebp+8h]
  int v42; // [esp+18h] [ebp+8h]
  int v43; // [esp+18h] [ebp+8h]
  int v44; // [esp+18h] [ebp+8h]
  int v45; // [esp+18h] [ebp+8h]
  int v46; // [esp+18h] [ebp+8h]
  int v47; // [esp+18h] [ebp+8h]
  int v48; // [esp+18h] [ebp+8h]
  int v49; // [esp+18h] [ebp+8h]
  int v50; // [esp+18h] [ebp+8h]
  int v51; // [esp+18h] [ebp+8h]
  int v52; // [esp+18h] [ebp+8h]
  int v53; // [esp+18h] [ebp+8h]
  int v54; // [esp+18h] [ebp+8h]
  int v55; // [esp+18h] [ebp+8h]
  int v56; // [esp+18h] [ebp+8h]

  if ( *(float *)(this + 84) != 0.0 )
  {
    v23 = *(float *)(this + 104) * *(float *)(this + 84);
    *(float *)&v37 = COERCE_FLOAT(sub_41A5E0(a2 + 802)) + v23;
    sub_41A590(a2 + 802, v4, v37);
    v24 = (double)*(int *)(this + 108) * *(float *)(this + 84) * 0.001;
    *(float *)&v38 = COERCE_FLOAT(sub_41A5E0(a2 + 886)) + v24;
    sub_41A590(a2 + 886, v5, v38);
    v25 = *(float *)(this + 112) * *(float *)(this + 84);
    *(float *)&v39 = COERCE_FLOAT(sub_41A5E0(a2 + 46)) + v25;
    sub_41A590(a2 + 46, v39, v39);
    v40 = (uint64_t)(((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))
                            * *(float *)(this + 120)
                            + (double)*(int *)(this + 116))
                           * *(float *)(this + 84));
    v6 = sub_41A5E0(a2 + 116);
    sub_41A590(a2 + 116, v7, v40 + v6);
  }
  if ( *(float *)(this + 88) != 0.0 )
  {
    v26 = (double)*(int *)(this + 124) * *(float *)(this + 88) * 0.001;
    *(float *)&v41 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v26;
    sub_41A590(a2 + 858, v41, v41);
    v27 = (double)*(int *)(this + 124) * *(float *)(this + 88) * 0.001;
    *(float *)&v42 = COERCE_FLOAT(sub_41A5E0(a2 + 1292)) + v27;
    sub_41A590(a2 + 1292, v8, v42);
    v28 = *(float *)(this + 128) * *(float *)(this + 88);
    *(float *)&v43 = COERCE_FLOAT(sub_41A5E0(a2 + 1208)) + v28;
    sub_41A590(a2 + 1208, v9, v43);
  }
  if ( *(float *)(this + 92) != 0.0 )
  {
    v44 = (uint64_t)(((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))
                            * *(float *)(this + 136)
                            + (double)*(int *)(this + 132))
                           * *(float *)(this + 92));
    v10 = sub_41A5E0(a2 + 60);
    sub_41A590(a2 + 60, v11, v44 + v10);
    v45 = (uint64_t)((double)*(int *)(this + 140) * *(float *)(this + 92));
    v12 = sub_41A5E0(a2 + 900);
    sub_41A590(a2 + 900, v45, v45 + v12);
  }
  if ( *(float *)(this + 96) != 0.0 )
  {
    v46 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))
                           * *(float *)(this + 144)
                           * *(float *)(this + 96));
    v13 = sub_41A5E0(a2 + 1040);
    sub_41A590(a2 + 1040, v14, v46 + v13);
    v29 = *(float *)(this + 148) * *(float *)(this + 96);
    *(float *)&v47 = COERCE_FLOAT(sub_41A5E0(a2 + 802)) + v29;
    sub_41A590(a2 + 802, v47, v47);
    v30 = (double)*(int *)(this + 152) * *(float *)(this + 96) * 0.001;
    *(float *)&v48 = COERCE_FLOAT(sub_41A5E0(a2 + 886)) + v30;
    sub_41A590(a2 + 886, v15, v48);
    v31 = (double)*(int *)(this + 156) * *(float *)(this + 96) * 0.001;
    *(float *)&v49 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v31;
    sub_41A590(a2 + 858, v16, v49);
    v32 = (double)*(int *)(this + 156) * *(float *)(this + 96) * 0.001;
    *(float *)&v50 = COERCE_FLOAT(sub_41A5E0(a2 + 1292)) + v32;
    sub_41A590(a2 + 1292, v50, v50);
  }
  if ( *(float *)(this + 100) != 0.0 )
  {
    v51 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))
                           * *(float *)(this + 160)
                           * *(float *)(this + 100));
    v17 = sub_41A5E0(a2 + 1040);
    sub_41A590(a2 + 1040, v18, v51 + v17);
    v52 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 388))(*(uint32_t *)(this + 4))
                           * *(float *)(this + 164)
                           * *(float *)(this + 100));
    v19 = sub_41A5E0(a2 + 88);
    sub_41A590(a2 + 88, v20, v52 + v19);
    v33 = *(float *)(this + 168) * *(float *)(this + 100);
    *(float *)&v53 = COERCE_FLOAT(sub_41A5E0(a2 + 802)) + v33;
    sub_41A590(a2 + 802, v53, v53);
    v34 = (double)*(int *)(this + 172) * *(float *)(this + 100) * 0.001;
    *(float *)&v54 = COERCE_FLOAT(sub_41A5E0(a2 + 886)) + v34;
    sub_41A590(a2 + 886, v21, v54);
    v35 = (double)*(int *)(this + 176) * *(float *)(this + 100) * 0.001;
    *(float *)&v55 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v35;
    sub_41A590(a2 + 858, v22, v55);
    v36 = (double)*(int *)(this + 176) * *(float *)(this + 100) * 0.001;
    *(float *)&v56 = COERCE_FLOAT(sub_41A5E0(a2 + 1292)) + v36;
    sub_41A590(a2 + 1292, v56, v56);
  }
}


// ------------------------------------------------------------
// 0x5F74E0 sub_5F74E0
// ------------------------------------------------------------
// 调: sub_5F74E0 sub_47E720 sub_47E9D0
int /*thiscall*/ sub_5F74E0(int this, int a2)
{
  int result; // eax

  sub_47E720(*(uint32_t *)(this + 80), a2);
  result = a2 - 172;
  switch ( a2 )
  {
    case 172:
      *(uint32_t *)(this + 132) = sub_47E9D0(0);
      *(float *)(this + 136) = (double)(int)sub_47E9D0(1) * 0.1;
      result = sub_47E9D0(2);
      *(uint32_t *)(this + 140) = result;
      break;
    case 173:
      *(float *)(this + 144) = (double)(int)sub_47E9D0(0) * 0.1;
      *(float *)(this + 148) = (double)(int)sub_47E9D0(1) * 0.0099999998;
      *(uint32_t *)(this + 152) = sub_47E9D0(2);
      result = sub_47E9D0(3);
      *(uint32_t *)(this + 156) = result;
      break;
    case 174:
      *(float *)(this + 160) = (double)(int)sub_47E9D0(0) * 0.1;
      *(float *)(this + 164) = (double)(int)sub_47E9D0(1) * 0.1;
      *(float *)(this + 168) = (double)(int)sub_47E9D0(2) * 0.0099999998;
      *(uint32_t *)(this + 172) = sub_47E9D0(3);
      result = sub_47E9D0(4);
      *(uint32_t *)(this + 176) = result;
      break;
    case 185:
      *(uint32_t *)(this + 124) = sub_47E9D0(0);
      result = sub_47E9D0(1);
      *(float *)(this + 128) = (double)result * 0.1;
      break;
    case 187:
      *(float *)(this + 104) = (double)(int)sub_47E9D0(0) * 0.0099999998;
      *(uint32_t *)(this + 108) = sub_47E9D0(1);
      *(float *)(this + 112) = (double)(int)sub_47E9D0(2) * 0.0099999998;
      *(uint32_t *)(this + 116) = sub_47E9D0(3);
      result = sub_47E9D0(4);
      *(float *)(this + 120) = (double)result * 0.1;
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F7700 sub_5F7700
// ------------------------------------------------------------
// 调: sub_5F7700
int /*thiscall*/ sub_5F7700(uint32_t *this, int a2, int a3)
{
  *(this + 11) = a2;
  *(this + 24) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x5F7720 sub_5F7720
// ------------------------------------------------------------
// 调: sub_5F7720
int /*thiscall*/ sub_5F7720(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 120))(this, a2, a3, a4);
  *(this + 11) = a5;
  *(this + 24) = a6;
  return a6;
}



// ------------------------------------------------------------
// 0x5F7750 sub_5F7750
// ------------------------------------------------------------
// 调: sub_5F7750
int /*thiscall*/ sub_5F7750(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v5; // ebx
  uint8_t *v7; // esi
  int result; // eax

  v5 = a3;
  if ( a3 <= 0 )
  {
    *(this + 11) = a4;
    *(this + 24) = a5;
  }
  else
  {
    v7 = (uint8_t *)(a2 + 4);
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*this + 120))(
        this,
        *((uint32_t *)v7 - 1),
        *v7,
        *((uint32_t *)v7 + 1));
      v7 += 12;
      --v5;
    }
    while ( v5 != 0 );
    *(this + 11) = a4;
    *(this + 24) = a5;
    return a5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F77B0 CNChangeStatus__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（12 行，无外调无字符串）
char /*thiscall*/ CNChangeStatus__vmt20(int this, char a2)
{
  char result; // al

  if ( *(uint32_t *)(this + 96) == 4 )
  {
    result = a2;
    if ( a2 == 0 )
      return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 216))(*(uint32_t *)(this + 4), 6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F77E0 CNChangeStatus__vmt34
// ------------------------------------------------------------
// 证: "BUFF_SHOWTIME_LOOP"
int /*thiscall*/ CNChangeStatus__vmt34(int this)
{
  int result; // eax

  if ( *(uint32_t *)(this + 96) == 4 )
    return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
             *(uint32_t *)(this + 4),
             "BUFF_SHOWTIME_LOOP",
             6,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x5F7800 CNChangeStatus__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（19 行，无外调无字符串）
unsigned int /*thiscall*/ CNChangeStatus__vmt8(uint32_t *this, int a2)
{
  unsigned int result; // eax
  int v4; // esi
  unsigned int i; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( (uint8_t)result != 1 )
  {
    v4 = *(this + 21);
    for ( i = 0; v4 != 0; ++i )
    {
      result = (*(this + 22) - v4) / 12;
      if ( i >= result )
        break;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F7840 CNChangeStatus__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
unsigned int /*thiscall*/ sub_5F7840(int *this, int a2)
{
  int *v2; // ebx
  unsigned int result; // eax
  int v4; // edi
  unsigned int v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  unsigned int v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // esi
  int v16; // ebx
  int v17; // edx
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  int v24; // ebx
  double v25; // st7
  unsigned int v26; // ebx
  int v27; // edx
  unsigned int v28; // ebx
  int v29; // eax
  int v30; // edx
  float v31; // [esp+0h] [ebp-28h]
  float v32; // [esp+0h] [ebp-28h]
  float v33; // [esp+0h] [ebp-28h]
  float v34; // [esp+0h] [ebp-28h]
  float v35; // [esp+0h] [ebp-28h]
  float v36; // [esp+0h] [ebp-28h]
  float v37; // [esp+0h] [ebp-28h]
  float v38; // [esp+0h] [ebp-28h]
  float v39; // [esp+0h] [ebp-28h]
  float v40; // [esp+0h] [ebp-28h]
  int v41; // [esp+10h] [ebp-18h]
  float v42; // [esp+10h] [ebp-18h]
  int v43; // [esp+10h] [ebp-18h]
  int v44; // [esp+10h] [ebp-18h]
  int v45; // [esp+14h] [ebp-14h]
  float v46; // [esp+14h] [ebp-14h]
  int v47; // [esp+18h] [ebp-10h]
  unsigned int v48; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]

  v2 = this;
  result = (*(int (/*fastcall*/ **)(int *))(*this + 128))(this);
  if ( (uint8_t)result != 1 )
  {
    v4 = a2;
    v5 = 0;
    while ( 1 )
    {
      while ( 1 )
      {
        result = v2[21];
        v48 = v5;
        if ( result == 0 )
          return result;
        result = (int)(v2[22] - result) / 12;
        if ( v5 >= result )
          return result;
        v6 = 12 * v5;
        v7 = v2[21] + 12 * v5;
        v41 = v6;
        v8 = *(uint32_t *)v7;
        if ( *(uint32_t *)v7 != 16 && v8 != 17 && v8 != 18 && v8 != 19 )
          break;
        v24 = 4;
        switch ( *(uint32_t *)v7 )
        {
          case 0x10:
            v24 = 0;
            break;
          case 0x11:
            v24 = 1;
            break;
          case 0x12:
            v24 = 2;
            break;
          case 0x13:
            v24 = 3;
            break;
          default:
            break;
        }
        v25 = *(float *)(v7 + 8);
        if ( *(uint8_t *)(v7 + 4) != 0 )
        {
          v46 = v25 * 0.0099999998;
          v26 = 14 * v24 + v4 + 228;
          *(float *)&v44 = COERCE_FLOAT(sub_41A5E0(v26)) + v46;
          sub_41A590(v26, v27, v44);
          v2 = this;
          v5 = v48 + 1;
        }
        else
        {
          v28 = 14 * v24 + v4 + 172;
          v29 = sub_41A5E0(v28);
          sub_41A590(v28, v30, (uint64_t)v25 + v29);
LABEL_104:
          v2 = this;
          v5 = v48 + 1;
        }
      }
      if ( v8 == 20 )
      {
        v9 = v4 + 228;
        v47 = -228 - v4;
        for ( i = 4; i != 0; --i )
        {
          v10 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 672))(*(this + 1), 3);
          v45 = sub_41A5E0(v10 + v9 + v47 + 172);
          v11 = sub_41A5E0(v9 - 56);
          sub_41A590(v9 - 56, v12, v11 - v45);
          v13 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 672))(*(this + 1), 3);
          v42 = COERCE_FLOAT(sub_41A5E0(v13 + v9 + v47 + 228));
          *(float *)&v43 = COERCE_FLOAT(sub_41A5E0(v9)) - v42;
          sub_41A590(v9, v14, v43);
          v9 += 14;
        }
        v4 = a2;
        v2 = this;
        v5 = v48 + 1;
      }
      else
      {
        switch ( *(uint32_t *)v7 )
        {
          case 0x15:
            v15 = 0;
            v16 = v4 + 284;
            do
            {
              if ( sub_497040(v15) != 17 )
              {
                v17 = *(this + 21);
                v18 = *(float *)(v41 + v17 + 8);
                if ( *(uint8_t *)(v41 + v17 + 4) != 0 )
                {
                  v31 = v18 * 0.0099999998;
                  sub_4AED60(v31);
                }
                else
                {
                  sub_4450B0((uint64_t)v18);
                }
              }
              ++v15;
              v16 += 14;
            }
            while ( v15 < 16 );
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) == 0 )
              goto LABEL_50;
            goto LABEL_59;
          case 3:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 1:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 2:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x16:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 4:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x19:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 0x1A:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_50;
          case 5:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
LABEL_50:
            sub_4450B0((uint64_t)v19);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 6:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) == 0 )
              goto LABEL_50;
            goto LABEL_59;
          case 7:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_53;
          case 8:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
            goto LABEL_53;
          case 9:
            v19 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
              goto LABEL_59;
LABEL_53:
            v32 = v19 * 0.001;
            sub_4AED60(v32);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xA:
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v34 = *(float *)(v7 + 8) * 0.0099999998;
              sub_4AED60(v34);
            }
            else
            {
              v21 = sub_433F60(v2[1], 2) * (double)(int)(uint64_t)*(float *)(v7 + 8);
              sub_4450B0((uint64_t)v21);
            }
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xB:
            v22 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v35 = v22 * 0.0099999998;
              sub_4AED60(v35);
            }
            else
            {
              sub_4450B0((uint64_t)v22);
            }
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0x17:
            v23 = *(float *)(v7 + 8);
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v36 = v23 * 0.0099999998;
              sub_4AED60(v36);
            }
            else
            {
              sub_4450B0((uint64_t)v23);
            }
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0x18:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v37 = sub_43B5A0((void *)(v4 + 1292)) * *(float *)(v7 + 8) * 0.0099999998;
            sub_4AED60(v37);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xC:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v38 = sub_43B5A0((void *)(v4 + 1208)) * *(float *)(v7 + 8) * 0.0099999998;
            sub_4AED60(v38);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xD:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v39 = sub_43B5A0((void *)(v4 + 1222)) * *(float *)(v7 + 8) * 0.0099999998;
            sub_4AED60(v39);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xE:
            if ( *(uint8_t *)(v7 + 4) == 0 )
            {
              v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
              goto LABEL_60;
            }
            v40 = sub_43B5A0((void *)(v4 + 1236)) * *(float *)(v7 + 8) * 0.0099999998;
            sub_4AED60(v40);
            v2 = this;
            v5 = v48 + 1;
            break;
          case 0xF:
            if ( *(uint8_t *)(v7 + 4) != 0 )
            {
              v19 = sub_43B5A0((void *)(v4 + 1250)) * *(float *)(v7 + 8);
LABEL_59:
              v20 = v19 * 0.0099999998;
              goto LABEL_60;
            }
            v20 = (double)(int)(uint64_t)*(float *)(v7 + 8);
LABEL_60:
            v33 = v20;
            sub_4AED60(v33);
            v2 = this;
            v5 = v48 + 1;
            break;
          default:
            goto LABEL_104;
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// ============================================================
// §C 状态与buff
// ============================================================
// 0x5F8000 sub_5F8000
// ------------------------------------------------------------
// 调: sub_5F8000
char /*thiscall*/ sub_5F8000(int *this, char *a2, int a3)
{
  int v3; // eax
  int v5; // edx
  char *v6; // eax
  int v7; // esi
  int v8; // [esp+8h] [ebp+8h]

  v3 = *(this + 21);
  if ( v3 != 0 )
    v3 = (*(this + 22) - v3) / 12;
  if ( v3 != a3 )
    return 0;
  v5 = 0;
  if ( a3 <= 0 )
    return 1;
  v6 = a2;
  v7 = *(this + 21) - (uint32_t)a2;
  v8 = v7;
  while ( memcmp(&v6[v7], v6, 0xCu) == 0 )
  {
    ++v5;
    v6 += 12;
    if ( v5 >= a3 )
      return 1;
    v7 = v8;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5F8080 CNChangeStatus__vmt14
// ------------------------------------------------------------
// 调: sub_699000 sub_4938F0 sub_4049C0 sub_491F80 sub_491D00
char /*thiscall*/ CNChangeStatus__vmt14(int this, char a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // edi
  double v8; // st7
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  double v12; // st7
  int v13; // ecx
  int i; // ebx
  int v15; // eax

  LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
  if ( (uint8_t)v6 == 0 )
  {
    v6 = *(uint32_t *)(this + 96);
    switch ( v6 )
    {
      case 3:
        LOBYTE(v6) = a2;
        if ( a2 != 0 )
        {
          v7 = *(uint32_t *)(this + 44) - sub_699000(this + 8);
          sub_4938F0(*(uint32_t *)(4 * (*(uint8_t *)(**(uint32_t **)(this + 112) + 170) != 0) + *(uint32_t *)(this + 112)));
          if ( v7 < 500 )
          {
            v8 = sub_4049C0(255.0, 0.0, 500 - v7, 500);
            sub_491F80(-1, -1, -1, (uint64_t)v8, 1);
          }
          LOBYTE(v6) = sub_491D00(dword_79C0B0, a3, a4, 0.0);
        }
        break;
      case 5:
        v9 = *(uint32_t *)(this + 112);
        v10 = a2 != 0;
        if ( *(uint8_t *)(*(uint32_t *)(v9 + 4 * v10) + 170) != 0 )
          v10 += 2;
        sub_4938F0(*(uint32_t *)(4 * v10 + v9));
        v11 = *(uint32_t *)(this + 44) - sub_699000(this + 8);
        if ( v11 < 500 )
        {
          v12 = sub_4049C0(255.0, 0.0, 500 - v11, 500);
          sub_491F80(-1, -1, -1, (uint64_t)v12, 1);
        }
        v13 = a4 - (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4)) / 2;
        LOBYTE(v6) = sub_491D00(dword_79C0B0, a3, v13, 0.0);
        break;
      case 6:
      case 7:
        for ( i = 0; i < 8; i += 4 )
        {
          sub_4938F0(*(uint32_t *)(*(uint32_t *)(this + 112) + i));
          v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
          LOBYTE(v6) = sub_491D00(dword_79C0B0, a3, a4 - v15, 0.0);
        }
        break;
      default:
        break;
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5F8250 sub_5F8250
// ------------------------------------------------------------
// 调: sub_5F8250 sub_4B2F20 sub_59EE30 sub_504450 sub_5043B0
int /*thiscall*/ sub_5F8250(int *this, int a2, unsigned int a3, int *Block)
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
  void *v18; // ecx
  int v20; // edi
  int v21; // [esp-18h] [ebp-40h]
  int v22; // [esp-Ch] [ebp-34h]
  unsigned int v23; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
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
      sub_4B2F20(this);
    if ( v7 != 0 )
      v12 = (*(this + 2) - v7) / 12;
    else
      v12 = 0;
    if ( v9 >= a3 + v12 )
    {
      v18 = (void *)*(this + 2);
      Blockb = v18;
      if ( ((int)v18 - a2) / 12 >= a3 )
      {
        v27 = (int)v18 - 12 * a3;
        *(this + 2) = sub_59EE30(v27, v18, v18);
        sub_504450(a2, v27, Blockb);
        return sub_5043B0(a2, a2 + 12 * a3, v25);
      }
      else
      {
        sub_59EE30(a2, v18, a2 + 12 * a3);
        v23 = a3 - (*(this + 2) - a2) / 12;
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
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      v21 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(v21, a2, Blocka);
      sub_623C10(v28, a3, v25);
      sub_59EE30(a2, *(this + 2), v28 + 12 * a3);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 12;
      v17 = v16 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[12 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F8500 sub_5F8500
// ------------------------------------------------------------
// 调: sub_5F8500 sub_5F8250
uint32_t */*thiscall*/ sub_5F8500(int *this, uint32_t *a2, int a3, int *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 12 != 0 )
    v6 = (a3 - v5) / 12;
  else
    v6 = 0;
  sub_5F8250(this, a3, 1u, Block);
  *a2 = *(this + 1) + 12 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x5F8570 CNChangeStatus__vmt4
// ------------------------------------------------------------
// 调: sub_4600B0 sub_4E77D0 sub_5E5260
void /*thiscall*/ sub_5F8570(int this)
{
  int v2; // eax
  int *v3; // esi
  int v4; // ebx
  int v5; // edx
  void *v6; // eax
  int *v7; // esi
  int v8; // ebx
  int v9; // ebx
  int v10; // edi
  int v11; // edx
  void *v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  void *v18; // eax
  void **v19; // ecx
  int *v20; // esi
  int v21; // ebx
  int v22; // edi
  int v23; // edx
  void *v24; // eax
  int v25; // ebx
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // edi
  int v31; // eax
  void *v32; // eax
  int v33; // [esp-14h] [ebp-5Ch]
  int v34; // [esp-14h] [ebp-5Ch]
  int v35; // [esp-14h] [ebp-5Ch]
  int v36; // [esp-10h] [ebp-58h]
  int v37; // [esp-10h] [ebp-58h]
  int v38; // [esp-10h] [ebp-58h]
  int v39; // [esp-Ch] [ebp-54h]
  int v40; // [esp-Ch] [ebp-54h]
  int v41; // [esp-Ch] [ebp-54h]
  void *v42[4]; // [esp+4h] [ebp-44h] BYREF
  void *v43[4]; // [esp+14h] [ebp-34h] BYREF
  uint8_t v44[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  int v46; // [esp+34h] [ebp-14h]
  int v47; // [esp+38h] [ebp-10h]
  int v48; // [esp+44h] [ebp-4h]

  v47 = this;
  sub_5F66C0();
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0 )
  {
    v2 = *(uint32_t *)(this + 96);
    if ( v2 != 1 )
    {
      if ( v2 == 2 )
      {
        v7 = *(int **)(this + 4);
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v7 + 340))(v7) == 60003 && dword_8F7C04 != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(int *))(*v7 + 376))(v7);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v8 )
            return;
        }
        v9 = **(uint32_t **)(this + 100);
        v46 = (*(int (/*thiscall*/ **)(int *))(*v7 + 192))(v7);
        v40 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*v7 + 128))(v7, (uint64_t)((double)v46 * -0.5) >> 32)
            - (uint64_t)((double)v46 * -0.5);
        v37 = (*(int (/*thiscall*/ **)(int *))(*v7 + 124))(v7);
        v10 = v47;
        v34 = (*(int (/*thiscall*/ **)(int *))(*v7 + 120))(v7);
        (*(void (/*thiscall*/ **)(uint32_t))(v9 + 40))(*(uint32_t *)(v47 + 100));
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(v10 + 100) + 92))(*(uint32_t *)(v10 + 100), v44);
        v11 = *v7;
        v48 = 1;
        v12 = (void *)(*(int (/*thiscall*/ **)(int *))(v11 + 80))(v7);
        sub_4600B0(v12, 2, 0, (int)v44);
        v13 = **(uint32_t **)(v10 + 104);
        v14 = (*(int (/*thiscall*/ **)(int *))(*v7 + 128))(v7);
        v15 = (*(int (/*thiscall*/ **)(int *, int))(*v7 + 124))(v7, v14);
        v16 = (*(int (/*thiscall*/ **)(int *, int))(*v7 + 120))(v7, v15);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v13 + 40))(*(uint32_t *)(v10 + 104), v16);
        v17 = (*(int (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(v10 + 104) + 92))(*(uint32_t *)(v10 + 104), v43);
        LOBYTE(v48) = 2;
        sub_4E77D0((int)v44, v17);
        LOBYTE(v48) = 1;
        sub_5E5260(v43);
        v18 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(*v7 + 80))(v7, 2, 0, v44);
        sub_4600B0(v18, v34, v37, v40);
        v19 = (void **)v44;
      }
      else
      {
        if ( v2 != 4 )
          return;
        v20 = *(int **)(this + 4);
        v21 = **(uint32_t **)(this + 100);
        v46 = (*(int (/*thiscall*/ **)(int *))(*v20 + 192))(v20);
        v41 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*v20 + 128))(v20, (uint64_t)((double)v46 * -0.5) >> 32)
            - (uint64_t)((double)v46 * -0.5);
        v38 = (*(int (/*thiscall*/ **)(int *))(*v20 + 124))(v20);
        v22 = v47;
        v35 = (*(int (/*thiscall*/ **)(int *))(*v20 + 120))(v20);
        (*(void (/*thiscall*/ **)(uint32_t))(v21 + 40))(*(uint32_t *)(v47 + 100));
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(v22 + 100) + 92))(*(uint32_t *)(v22 + 100), v43);
        v23 = *v20;
        v48 = 3;
        v24 = (void *)(*(int (/*thiscall*/ **)(int *))(v23 + 80))(v20);
        sub_4600B0(v24, 2, 0, (int)v43);
        v25 = **(uint32_t **)(v22 + 104);
        v46 = (*(int (/*thiscall*/ **)(int *))(*v20 + 192))(v20);
        v26 = (uint64_t)((double)v46 * -0.30000001);
        v27 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*v20 + 128))(
                v20,
                (uint64_t)((double)v46 * -0.30000001) >> 32);
        v28 = (*(int (/*thiscall*/ **)(int *, int))(*v20 + 124))(v20, v27 - v26);
        v29 = (*(int (/*thiscall*/ **)(int *, int))(*v20 + 120))(v20, v28);
        v30 = v47;
        (*(void (/*thiscall*/ **)(uint32_t, int))(v25 + 40))(*(uint32_t *)(v47 + 104), v29);
        v31 = (*(int (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(v30 + 104) + 92))(*(uint32_t *)(v30 + 104), v42);
        LOBYTE(v48) = 4;
        sub_4E77D0((int)v43, v31);
        LOBYTE(v48) = 3;
        sub_5E5260(v42);
        v32 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(*v20 + 80))(v20, 2, 0, v43);
        sub_4600B0(v32, v35, v38, v41);
        v19 = v43;
      }
      sub_5E5260(v19);
      return;
    }
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04 )
    {
      v3 = *(int **)(this + 4);
      v4 = **(uint32_t **)(this + 100);
      v46 = (*(int (/*thiscall*/ **)(int *))(*v3 + 192))(v3);
      v39 = (*(int (/*thiscall*/ **)(int *))(*v3 + 128))(v3) - (uint64_t)((double)v46 * -0.5);
      v36 = (*(int (/*thiscall*/ **)(int *))(*v3 + 124))(v3);
      v33 = (*(int (/*thiscall*/ **)(int *))(*v3 + 120))(v3);
      (*(void (/*thiscall*/ **)(uint32_t))(v4 + 40))(*(uint32_t *)(v47 + 100));
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(v47 + 100) + 92))(*(uint32_t *)(v47 + 100), v44);
      v5 = *v3;
      v48 = 0;
      v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(v3, 2, 0, v44);
      sub_4600B0(v6, v33, v36, v39);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}


// ------------------------------------------------------------
// 0x5F88B0 sub_5F88B0
// ------------------------------------------------------------
// 调: sub_5F88B0 sub_5F8500 sub_623C10
uint32_t */*thiscall*/ sub_5F88B0(int *this, int *Block)
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
    return sub_5F8500(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_623C10(v5, 1, Block);
  *(this + 2) = v5 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x5F8930 CNChangeStatus__vmt78
// ------------------------------------------------------------
// 调: sub_5F88B0
uint32_t */*thiscall*/ CNChangeStatus__vmt78(int *this, int a2, char a3, int a4)
{
  int Block; // [esp+0h] [ebp-Ch] BYREF
  char v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  v6 = a3;
  Block = a2;
  v7 = a4;
  return sub_5F88B0(this + 20, &Block);
}



// ------------------------------------------------------------
// 0x5F8960 sub_5F8960
// ------------------------------------------------------------
// 调: sub_5F8960 sub_42AF90 sub_657740
void /*thiscall*/ sub_5F8960(int this)
{
  uint32_t *v2; // edi
  int i; // ebx
  unsigned int j; // ebx
  int v5; // ecx
  void **v6; // ecx
  void **v7; // [esp+Ch] [ebp-4h]

  v2 = (uint32_t *)(this + 100);
  for ( i = 2; i != 0; --i )
  {
    if ( *v2 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  for ( j = 0; ; ++j )
  {
    v5 = *(uint32_t *)(this + 112);
    if ( v5 == 0 || j >= (*(uint32_t *)(this + 116) - v5) >> 2 )
      break;
    v6 = *(void ***)(v5 + 4 * j);
    if ( v6 != nullptr )
    {
      v7 = v6;
      sub_42AF90(v6);
      sub_657740(v7, 228);
    }
    *(uint32_t *)(4 * j + *(uint32_t *)(this + 112)) = 0;
  }
  if ( *(uint32_t *)(this + 112) != 0 )
    j__free(*(void **)(this + 112));
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
}



// ------------------------------------------------------------
// 0x5F8A10 CNChangeStatus__vmt1C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Particle/AttackPowerUp.p" | "Common/CommonEffect/Particle/PowerSpeedHpUp."
// 调: sub_428F30
void /*usercall*/ sub_5F8A10(int *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  uint32_t *v4; // eax
  int *v5; // eax
  int v6; // ecx
  int v7; // edx
  uint32_t *v8; // eax
  int *v9; // eax
  int v10; // ecx
  int v11; // edx
  uint32_t *v12; // eax
  int *v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  int i; // edi
  uint32_t *v20; // eax
  int *v21; // eax
  int v22; // ecx
  int v23; // edx
  uint32_t *v24; // eax
  int *v25; // eax
  int v26; // ecx
  int v27; // edx
  uint32_t *v28; // eax
  uint32_t *v29; // eax
  uint32_t *v30; // eax
  uint32_t *v31; // eax
  int j; // ebx
  int v33; // edi
  uint32_t *v34; // eax
  uint32_t *v35; // ebx
  int *v36; // ecx
  int v37; // edx
  int v38; // eax
  int *v39; // edi
  int v40; // eax
  int v41; // ebx
  void *v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // eax
  uint32_t *v46; // edi
  void *v47; // eax
  void *v48; // eax
  int v49; // edi
  void *v50; // ebx
  void *v51; // eax
  void *v52; // eax
  int k; // edi
  int v54; // eax
  int v55; // ecx
  int v56; // eax
  unsigned int v57; // edx
  int v58; // eax
  int m; // edi
  int v60; // [esp-8h] [ebp-28h]
  void *Block[2]; // [esp+8h] [ebp-18h] BYREF
  uint32_t *v62; // [esp+10h] [ebp-10h] BYREF
  int v63; // [esp+1Ch] [ebp-4h]

  v3 = a1[24];
  switch ( v3 )
  {
    case 1:
      if ( a1[25] == 0 )
      {
        v4 = operator new(0x12Cu);
        Block[0] = v4;
        v63 = 0;
        if ( v4 != nullptr )
          v5 = sub_428F30(v4, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", a1[1]);
        else
          v5 = nullptr;
        v6 = a1[1];
        a1[25] = (int)v5;
        v7 = *v5;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v7 + 112))(v5, v6);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[25] + 12))(a1[25], 0);
      break;
    case 2:
      if ( a1[25] == 0 )
      {
        v8 = operator new(0x12Cu);
        Block[0] = v8;
        v63 = 1;
        if ( v8 != nullptr )
          v9 = sub_428F30(v8, (int)"Common/CommonEffect/Particle/PowerSpeedHpUp.ptl", a1[1]);
        else
          v9 = nullptr;
        v10 = a1[1];
        a1[25] = (int)v9;
        v11 = *v9;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v11 + 112))(v9, v10);
        v12 = operator new(0x12Cu);
        Block[0] = v12;
        v63 = 2;
        if ( v12 != nullptr )
          v13 = sub_428F30(v12, (int)"Character/Gunner/Effect/Particle/Robotics.ptl", a1[1]);
        else
          v13 = nullptr;
        v14 = a1[1];
        a1[26] = (int)v13;
        v15 = *v13;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 112))(v13, v14);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[25] + 12))(a1[25], 0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[26] + 12))(a1[26], 0);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1[1] + 212))(
        a1[1],
        "POWER_UP",
        -1,
        0,
        0);
      break;
    case 3:
      v16 = a1[28];
      if ( v16 == 0 || (a1[29] - v16) >> 2 == 0 )
      {
        v63 = 3;
        if ( sub_42FCB0(228) != 0 )
          v17 = (uint32_t *)sub_431860((char)"Character/Mage/Effect/Animation/MpRegenRateUpStart.ani", 1);
        else
          v17 = nullptr;
        v62 = v17;
        v63 = -1;
        sub_42ABE0(&v62);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 4;
        if ( Block[0] != nullptr )
          v18 = (uint32_t *)sub_431860((char)"Character/Mage/Effect/Animation/MpRegenRateUpLoop.ani", 1);
        else
          v18 = nullptr;
        v63 = -1;
        v62 = v18;
        sub_42ABE0(&v62);
      }
      for ( i = 0; i < 8; i += 4 )
        sub_4926A0(*(uint32_t *)(a1[28] + i));
      break;
    case 4:
      if ( a1[25] == 0 )
      {
        v20 = operator new(0x12Cu);
        Block[0] = v20;
        v63 = 5;
        if ( v20 != nullptr )
          v21 = sub_428F30(v20, (int)"Character/Mage/Effect/Particle/MagicalTempoUp1.ptl", a1[1]);
        else
          v21 = nullptr;
        v22 = a1[1];
        a1[25] = (int)v21;
        v23 = *v21;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int, int))(v23 + 112))(v21, v22, a2);
        v24 = operator new(0x12Cu);
        Block[0] = v24;
        v63 = 6;
        if ( v24 != nullptr )
          v25 = sub_428F30(v24, (int)"Character/Mage/Effect/Particle/MagicalTempoUp2.ptl", a1[1]);
        else
          v25 = nullptr;
        v26 = a1[1];
        a1[26] = (int)v25;
        v27 = *v25;
        v63 = -1;
        (*(void (/*thiscall*/ **)(int *, int))(v27 + 112))(v25, v26);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[25] + 12))(a1[25], 0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[26] + 12))(a1[26], 0);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1[1] + 212))(
        a1[1],
        "BUFF_SHOWTIME_LOOP",
        6,
        0,
        0);
      break;
    case 5:
      if ( (uint8_t)sub_484F10(a1 + 27) != 0 )
      {
        v63 = 7;
        if ( sub_42FCB0(228) != 0 )
          v28 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashUnderStart.ani", 1);
        else
          v28 = nullptr;
        v62 = v28;
        v63 = -1;
        sub_42ABE0(&v62);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 8;
        if ( Block[0] != nullptr )
          v29 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashOverStart.ani", 1);
        else
          v29 = nullptr;
        v63 = -1;
        v62 = v29;
        sub_42ABE0(&v62);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 9;
        if ( Block[0] != nullptr )
          v30 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashUnderLoop.ani", 1);
        else
          v30 = nullptr;
        v63 = -1;
        v62 = v30;
        sub_42ABE0(&v62);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 10;
        if ( Block[0] != nullptr )
          v31 = (uint32_t *)sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashOverLoop.ani", 1);
        else
          v31 = nullptr;
        v62 = v31;
        v63 = -1;
        sub_42ABE0(&v62);
      }
      for ( j = 0; j < 16; j += 4 )
        sub_4926A0(*(uint32_t *)(j + a1[28]));
      Block[0] = (void *)sub_42FCB0(228);
      v63 = 11;
      if ( Block[0] != nullptr )
        v33 = sub_431860((char)"Character/Swordman/Effect/Animation/MindFlashHead.ani", 1);
      else
        v33 = 0;
      v63 = -1;
      v34 = (uint32_t *)sub_44B6C0(284);
      v35 = v34;
      Block[0] = v34;
      v63 = 12;
      if ( v34 != nullptr )
      {
        sub_44E0D0((char *)v34, v33, 1);
        *v35 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v35 = nullptr;
      }
      v36 = (int *)a1[1];
      v37 = *v36;
      v62 = v35;
      v63 = -1;
      v38 = (*(int (/*thiscall*/ **)(int *))(v37 + 80))(v36);
      sub_45FE80(v38, v33, 2, 0, (int)v35, 0, 0);
      v39 = (int *)a1[1];
      v40 = *v39;
      v41 = *v35;
      Block[0] = v39;
      v42 = (void *)(*(int (/*thiscall*/ **)(int *))(v40 + 128))(v39);
      v43 = *v39;
      Block[1] = v42;
      v60 = (int)v42 + (*(int (/*thiscall*/ **)(int *))(v43 + 192))(v39) + 10;
      v44 = (*(int (/*thiscall*/ **)(int *))(*v39 + 124))(v39);
      v45 = (*(int (/*thiscall*/ **)(int *, int))(*v39 + 120))(v39, v44 + 1);
      v46 = v62;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v41 + 112))(v62, v45);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v46 + 60))(v46, a1[1]);
      sub_4A06D0(v60);
      break;
    case 6:
      if ( (uint8_t)sub_484F10(a1 + 27) != 0 )
      {
        v63 = 13;
        if ( sub_42FCB0(228) != 0 )
          v47 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/ProvocationDollBuff1.ani", 1);
        else
          v47 = nullptr;
        Block[0] = v47;
        v63 = -1;
        sub_42ABE0(Block);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 14;
        if ( Block[0] != nullptr )
          v48 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/ProvocationDollBuff2.ani", 1);
        else
          v48 = nullptr;
        v63 = -1;
        Block[0] = v48;
        sub_42ABE0(Block);
      }
      v49 = 0;
      *(float *)Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1] + 192))(a1[1]) * 0.0049999999;
      v50 = Block[0];
      do
      {
        sub_4926A0(*(uint32_t *)(a1[28] + v49));
        sub_4920E0(*(uint32_t **)(a1[28] + v49), *(float *)&v50, *(float *)&v50);
        v49 += 4;
      }
      while ( v49 < 8 );
      break;
    case 7:
      if ( (uint8_t)sub_484F10(a1 + 27) != 0 )
      {
        v63 = 15;
        if ( sub_42FCB0(228) != 0 )
          v51 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/SummonMonsterAura1.ani", 1);
        else
          v51 = nullptr;
        Block[0] = v51;
        v63 = -1;
        sub_42ABE0(Block);
        Block[0] = (void *)sub_42FCB0(228);
        v63 = 16;
        if ( Block[0] != nullptr )
          v52 = (void *)sub_431860((char)"Character/Mage/Effect/Animation/SummonMonsterAura2.ani", 1);
        else
          v52 = nullptr;
        v63 = -1;
        Block[0] = v52;
        sub_42ABE0(Block);
      }
      for ( k = 0; k < 8; k += 4 )
        sub_4926A0(*(uint32_t *)(a1[28] + k));
      break;
    default:
      break;
  }
  v54 = a1[21];
  if ( v54 != 0 )
  {
    Block[0] = (void *)((a1[22] - v54) / 12);
    if ( Block[0] != nullptr )
    {
      v55 = *(uint32_t *)a1[21];
      if ( v55 == 12 || v55 == 13 )
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1[1] + 212))(
          a1[1],
          "CRITICAL_UP",
          -1,
          0,
          0);
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1[1] + 308))(a1[1]) != 0 )
  {
    v56 = a1[21];
    if ( v56 != 0 )
    {
      v57 = (int)((uint64_t)(715827883LL * (a1[22] - v56)) >> 32) >> 1;
      Block[0] = (void *)((a1[22] - v56) / 12);
      if ( v57 + (v57 >> 31) != 0 )
      {
        v58 = a1[21];
        if ( *(uint32_t *)v58 == 21 && *(uint8_t *)(v58 + 4) == 0 && *(float *)(v58 + 8) >= 100.0 )
        {
          for ( m = 0; m < 17; ++m )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[1] + 776))(a1[1], m) != 0
              && sub_496F80(m) != 16 )
            {
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)a1[1] + 764))(a1[1], m, 0, a1[9], 0);
            }
          }
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x5F9170 CNBulletBuff__vmt1C
// ------------------------------------------------------------
// 调: sub_47EF20
int /*thiscall*/ CNBulletBuff__vmt1C(int *this)
{
  uint32_t *v2; // ecx
  int result; // eax

  v2 = (uint32_t *)*(this + 20);
  if ( v2 != nullptr )
  {
    result = *(this + 22) + sub_47EF20(v2, 0, *(this + 21), -1, -1, 11);
    *(this + 23) = result;
    *(this + 11) = 0;
  }
  else
  {
    off_77F3FC(aCriticalError_42);
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F91C0 CNBulletBuff__vmt88
// ------------------------------------------------------------
// 调: sub_699000
char /*thiscall*/ CNBulletBuff__vmt88(uint32_t *this)
{
  if ( (int)*(this + 23) <= 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) == 0 )
    return 0;
  if ( (*(this + 23))-- == 1 )
    *(this + 11) = sub_699000((int)(this + 2)) + 1200;
  return 1;
}



// ------------------------------------------------------------
// 0x5F91F0 sub_5F91F0
// ------------------------------------------------------------
// 调: sub_5F91F0
int /*thiscall*/ sub_5F91F0(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = -1;
  *(uint8_t *)(this + 88) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F9200 CNTrodden__vmt1C
// ------------------------------------------------------------
// 证: 叶子函数（21 行，无外调无字符串）
int /*thiscall*/ CNTrodden__vmt1C(int this)
{
  int v2; // ecx
  int result; // eax

  v2 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 84) = -1;
  *(uint8_t *)(this + 88) = 0;
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
// 0x5F9250 CNTrodden__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（14 行，无外调无字符串）
char /*thiscall*/ CNTrodden__vmt20(uint32_t *this, char a2)
{
  char result; // al
  int v3; // esi

  result = a2;
  if ( a2 == 0 )
  {
    v3 = *(this + 1);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v3 + 612))(v3, 0, 0);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 820))(v3, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5F9280 CNTrodden__vmt10
// ------------------------------------------------------------
// 证: "DOWN_HEAVY" | "DOWN_MIDDLE" | "DOWN_LIGHT" | "STEP_ON"
// 调: sub_432E50 sub_4938F0 sub_42FC90 sub_4AECE0 sub_4B0D20
uint32_t */*usercall*/ sub_5F9280@<eax>(int a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  uint32_t *result; // eax
  int *v5; // esi
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edx
  int v12; // edi
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // edi
  int v17; // eax
  void *v18; // edi
  int v19; // eax
  void *v20; // eax
  int v21; // eax
  int v22; // eax
  int v25; // [esp+0h] [ebp-Ch]
  int v26; // [esp+0h] [ebp-Ch]
  int v27; // [esp+4h] [ebp-8h]
  int v28; // [esp+8h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 840))(*(uint32_t *)(a1 + 80));
  if ( result == (uint32_t *)18 )
  {
    v5 = *(int **)(a1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 200))(*(uint32_t *)(a1 + 80));
      v27 = (int)result;
      if ( result != nullptr )
      {
        v6 = *v5;
        v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80), a2, a3);
        v8 = sub_432E50(v7);
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 144))(v5, v8);
        if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
        sub_4938F0(v27);
        v9 = *(uint32_t *)(v27 + 148);
        v28 = v9;
        if ( v9 != *(uint32_t *)(a1 + 84) )
        {
          if ( v9 > 2 )
          {
            v18 = *(void **)((*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5) + 20);
            if ( (void *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != v18 )
              (*(void (/*thiscall*/ **)(int *, void *))(*v5 + 196))(v5, v18);
            if ( v28 == 10 )
              v19 = (*(int (/*thiscall*/ **)(int *))(*v5 + 912))(v5);
            else
              v19 = sub_42FC90(v27) - 1;
            sub_4AECE0(v18, v19);
            if ( *(uint8_t *)(a1 + 88) == 0 )
            {
              v20 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*v5 + 672))(v5, 3);
              v21 = sub_4B0D20(v20);
              v28 = 0;
              v25 = -1;
              if ( v21 > 60000 )
              {
                if ( v21 > 100000 )
                  (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_HEAVY");
                else
                  (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_MIDDLE");
              }
              else
              {
                (*(void (/*thiscall*/ **)(int *, const char *))(*v5 + 212))(v5, "DOWN_LIGHT");
              }
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*v5 + 212))(v5, "STEP_ON", -1, 0, 0);
              *(uint8_t *)(a1 + 88) = 1;
            }
          }
          else
          {
            v10 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
            v11 = *v5;
            if ( *(uint32_t *)(v10 + 16) != 0 )
            {
              v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 688))(v5);
              if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != *(uint32_t *)(v12 + 16) )
              {
                v13 = *v5;
                v14 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
                (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(v5, *(uint32_t *)(v14 + 16));
              }
            }
            else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v11 + 688))(v5) + 12) != 0 )
            {
              v15 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
              if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5) != *(uint32_t *)(v15 + 12) )
              {
                v16 = *v5;
                v17 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
                (*(void (/*thiscall*/ **)(int *, uint32_t))(v16 + 196))(v5, *(uint32_t *)(v17 + 12));
              }
            }
          }
          *(uint32_t *)(a1 + 84) = v28;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80), v25);
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 120))(*(uint32_t *)(a1 + 80));
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 80) + 124))(*(uint32_t *)(a1 + 80), v26);
        (*(void (/*thiscall*/ **)(int *))(*v5 + 112))(v5);
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
        if ( result != nullptr )
        {
          v22 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
          return sub_4938F0(v22);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5F9510 sub_5F9510
// ------------------------------------------------------------
// 调: sub_5F9510
int /*thiscall*/ sub_5F9510(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 136) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F9530 CNAerialGatlinged__vmt10
// ------------------------------------------------------------
// 调: sub_432E50 sub_699000 sub_4049C0 sub_423AB0 sub_4049F0
int /*thiscall*/ sub_5F9530(int this)
{
  int *v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // eax
  double v8; // st7
  int v9; // eax
  uint64_t v10; // rax
  int v11; // edi
  int v12; // edi
  int v13; // ecx
  int v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  float v19; // [esp+10h] [ebp-30h]
  float v20; // [esp+14h] [ebp-2Ch]
  float v21; // [esp+14h] [ebp-2Ch]
  float v22; // [esp+14h] [ebp-2Ch]
  float v23; // [esp+14h] [ebp-2Ch]
  float v24; // [esp+14h] [ebp-2Ch]
  float v25; // [esp+18h] [ebp-28h]
  float v26; // [esp+18h] [ebp-28h]
  float v27; // [esp+18h] [ebp-28h]
  float v28; // [esp+18h] [ebp-28h]
  float v29; // [esp+18h] [ebp-28h]
  float v30; // [esp+18h] [ebp-28h]
  float v31; // [esp+18h] [ebp-28h]
  int v32; // [esp+30h] [ebp-10h]
  int v33; // [esp+34h] [ebp-Ch]
  int v34; // [esp+38h] [ebp-8h]
  int v35; // [esp+3Ch] [ebp-4h]

  v2 = *(int **)(this + 4);
  v3 = *v2;
  v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80));
  v5 = sub_432E50(v4);
  (*(void (/*thiscall*/ **)(int *, int))(v3 + 144))(v2, v5);
  if ( (*(int (/*thiscall*/ **)(int *))(*v2 + 236))(v2) == 1 )
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v2 + 228))(v2, 0, -1, 0);
  if ( (*(int (/*thiscall*/ **)(int *))(*v2 + 236))(v2) == 0 )
  {
    v6 = sub_699000(this + 8);
    if ( *(uint8_t *)(*(uint32_t *)(this + 80) + 9368) != 0 )
    {
      if ( v6 < 610 )
      {
        v27 = (float)*(int *)(this + 96);
        v35 = (uint64_t)sub_4049C0(0.0, v27, v6, 610);
        v28 = (float)*(int *)(this + 100);
        v34 = (uint64_t)sub_4049C0(0.0, v28, v6, 610);
        v9 = *(uint32_t *)(this + 104);
        if ( v6 >= 410 )
          LODWORD(v10) = sub_423AB0(v9 + 50, v9, v6 - 410, 200, 0);
        else
          LODWORD(v10) = sub_423AB0(0, v9 + 50, v6, 410, 1);
        goto LABEL_14;
      }
      v11 = v6 - 610;
      v29 = (float)*(int *)(this + 84);
      v22 = (float)*(int *)(this + 96);
      v35 = (uint64_t)sub_4049C0(v22, v29, v11, 40);
      v30 = (float)*(int *)(this + 88);
      v23 = (float)*(int *)(this + 100);
      v34 = (uint64_t)sub_4049C0(v23, v30, v11, 40);
      v31 = (float)*(int *)(this + 92);
      v24 = (float)*(int *)(this + 104);
      v8 = sub_4049C0(v24, v31, v11, 40);
    }
    else
    {
      v25 = (float)*(int *)(this + 84);
      v35 = (uint64_t)sub_4049C0(0.0, v25, v6, 850);
      v26 = (float)*(int *)(this + 88);
      v34 = (uint64_t)sub_4049C0(0.0, v26, v6, 850);
      v7 = *(uint32_t *)(this + 92);
      if ( v6 >= 600 )
      {
        v21 = (float)v7;
        v8 = (double)(v7 + 40);
        v19 = v8;
        sub_4049F0(v19, v21, v6 - 600, 250, 0);
      }
      else
      {
        v8 = (double)(v7 + 40);
        v20 = v8;
        sub_4049F0(0.0, v20, v6, 600, 1);
      }
    }
    v10 = (uint64_t)v8;
LABEL_14:
    v12 = v10;
    if ( *(uint8_t *)(this + 120) != 0 && sub_699000(this + 108) <= 50 )
    {
      v35 += (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0 ? 1 : -1;
      ++v12;
    }
    v13 = *(uint32_t *)(this + 80);
    v14 = *v2;
    v32 = v13;
    v33 = v13;
    v15 = (*(int (**)(void))(*(uint32_t *)v13 + 128))();
    v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v32 + 124))(v32, v12 + v15);
    v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v33 + 120))(v33, v34 + v16);
    (*(void (/*thiscall*/ **)(int *, int))(v14 + 112))(v2, v35 + v17);
  }
  (*(void (/*thiscall*/ **)(int *, int, int))(*v2 + 612))(v2, 1, 1);
  return (*(int (/*thiscall*/ **)(int *, uint32_t))(*v2 + 820))(v2, 0);
}


// ------------------------------------------------------------
// 0x5F9810 CNAerialGatlinged__vmt1C
// ------------------------------------------------------------
// 证: "LIFT_UP"
// 调: sub_699070
int /*thiscall*/ CNAerialGatlinged__vmt1C(int this)
{
  int *v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  char v6; // al
  uint8_t *v7; // ecx
  int v8; // eax
  int v9; // edx
  int v11; // [esp+Ch] [ebp-4h]

  sub_699070(this + 8, 1u);
  v2 = *(int **)(this + 4);
  *(uint32_t *)(this + 84) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0
                         ? 214
                         : -214;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 220 - (*(int (/*thiscall*/ **)(int *))(*v2 + 192))(v2) / 2;
  v3 = *v2;
  v11 = *(uint32_t *)(this + 80);
  v4 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v11 + 124))(0);
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 120))(v11, *(uint32_t *)(this + 88) + v4);
  v6 = (*(int (/*thiscall*/ **)(int *, int))(v3 + 136))(v2, *(uint32_t *)(this + 84) + v5);
  v7 = *(uint8_t **)(this + 80);
  if ( v6 != 0 )
  {
    v7[9368] = 0;
  }
  else
  {
    *(uint32_t *)(this + 96) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v7 + 152))(v7) != 0 ? 128 : -128;
    *(uint32_t *)(this + 100) = -1;
    *(uint32_t *)(this + 104) = 188 - (*(int (/*thiscall*/ **)(int *))(*v2 + 192))(v2) / 2;
    *(uint32_t *)(this + 84) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 152))(*(uint32_t *)(this + 80)) != 0
                           ? 150
                           : -150;
    *(uint32_t *)(this + 88) = *(uint32_t *)(this + 100);
    v8 = (*(int (/*thiscall*/ **)(int *))(*v2 + 192))(v2);
    v9 = *(uint32_t *)(this + 80);
    *(uint32_t *)(this + 92) = 155 - v8 / 2;
    *(uint8_t *)(v9 + 9368) = 1;
  }
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 136) = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v2 + 776))(v2, 3) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*v2 + 556))(v2, 0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*v2 + 768))(v2, 3, 0, 0);
    (*(void (/*thiscall*/ **)(int *, int))(*v2 + 556))(v2, 1);
  }
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*v2 + 212))(v2, "LIFT_UP", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x5F9970 CNAerialGatlinged__vmt4
// ------------------------------------------------------------
// 证: "Common/HitEffect/Animation/KnockSmall.ani" | "BBQ_STUCK"
// 调: sub_699000 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E1F0
char /*thiscall*/ CNAerialGatlinged__vmt4(int this)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // edi
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v16; // [esp-10h] [ebp-30h]
  int v17; // [esp-Ch] [ebp-2Ch]
  int v18; // [esp+4h] [ebp-1Ch]
  char *v19; // [esp+Ch] [ebp-14h]

  LOBYTE(v2) = *(uint8_t *)(this + 136);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = *(uint32_t *)(this + 80);
    if ( *(uint8_t *)(v2 + 9368) != 0 )
    {
      v2 = sub_699000(this + 8);
      if ( v2 >= 610 )
      {
        v3 = *(uint32_t *)(this + 4);
        v4 = sub_42FCB0(228);
        v5 = 0;
        if ( v4 != 0 )
          v5 = sub_431860(v4, "Common/HitEffect/Animation/KnockSmall.ani", 1);
        v6 = (char *)sub_44B6C0(284);
        if ( v6 != nullptr )
          v7 = sub_44E1F0(v6, v5, 1);
        else
          v7 = nullptr;
        v16 = *(uint32_t *)(this + 80);
        v19 = v7;
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3);
        sub_45FE80(v8, (int)v7, 2, 0, (int)v7, v16, 0);
        v9 = *(uint32_t *)v7;
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 152))(v3);
        (*(void (/*thiscall*/ **)(char *, int))(v9 + 148))(v7, v10);
        v11 = *(uint32_t *)(this + 80);
        v18 = *(uint32_t *)v7;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 192))(v3) / 2;
        v17 = *(uint32_t *)(this + 104) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 128))(v11) + v12;
        v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 124))(v11, v17);
        v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 120))(v11, v13);
        (*(void (/*thiscall*/ **)(char *, int))(v18 + 112))(v19, *(uint32_t *)(this + 96) + v14);
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v3 + 212))(
                       v3,
                       "BBQ_STUCK",
                       -1,
                       0,
                       0);
        *(uint8_t *)(this + 136) = 1;
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5F9AE0 sub_5F9AE0
// ------------------------------------------------------------
// 调: sub_5F9AE0
int /*thiscall*/ sub_5F9AE0(uint32_t *this)
{
  *(this + 24) = 17;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 1065353216;
  *(this + 30) = 0;
  *(this + 31) = 4;
  *(this + 32) = 0;
  *(this + 33) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5F9B20 sub_5F9B20
// ------------------------------------------------------------
// 调: sub_5F9B20
int /*thiscall*/ sub_5F9B20(uint32_t *this, int a2, int a3)
{
  *(this + 31) = a2;
  *(this + 32) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x5F9B40 CNWeaponMastery__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590 sub_4AED60
void /*thiscall*/ CNWeaponMastery__vmtC(int this, int a2)
{
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edx
  uint32_t *v8; // ecx
  int v9; // edx
  int v10; // edx
  float v11; // [esp+8h] [ebp-8h]
  int v12; // [esp+8h] [ebp-8h]
  int v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+8h] [ebp-8h]
  float v15; // [esp+Ch] [ebp-4h]
  float v16; // [esp+Ch] [ebp-4h]

  v3 = __RTDynamicCast(
         *(uint32_t *)(this + 4),
         0,
         &IRDActiveObject `RTTI Type Descriptor',
         &IRDCharacter `RTTI Type Descriptor',
         0);
  v4 = v3;
  if ( v3 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 792))(v3, 8) == 0
      || (v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 792))(v4, 8),
          (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 200))(v5) == 0) )
    {
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1096))(v4);
      v7 = *(uint32_t **)(this + 88);
      v8 = *(uint32_t **)(this + 84);
      if ( v8 != v7 )
      {
        do
        {
          if ( *v8 == v6 )
            break;
          ++v8;
        }
        while ( v8 != v7 );
        if ( v8 != v7 )
        {
          v11 = *(float *)(this + 108);
          *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v11;
          sub_41A590(a2 + 858, v12, v12);
          v15 = *(float *)(this + 108);
          *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(a2 + 1292)) + v15;
          sub_41A590(a2 + 1292, v9, v13);
          v16 = *(float *)(this + 112);
          *(float *)&v14 = COERCE_FLOAT(sub_41A5E0(a2 + 1208)) + v16;
          sub_41A590(a2 + 1208, v10, v14);
          if ( *(float *)(this + 120) != 0.0
            && ((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 792))(v4, 8) != 0
             || (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 1084))(v4, 8) != 0) )
          {
            sub_4AED60(*(float *)(this + 120));
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5F9CA0 CNWeaponMastery__vmt8
// ------------------------------------------------------------
// 调: sub_45E5A0
void /*thiscall*/ CNWeaponMastery__vmt8(int this, int a2)
{
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // eax
  uint32_t *v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // [esp+8h] [ebp-8h] BYREF
  int v14; // [esp+Ch] [ebp-4h] BYREF
  int v15; // [esp+18h] [ebp+8h]

  if ( *(uint8_t *)(a2 + 16) != 0 )
  {
    v4 = __RTDynamicCast(
           *(uint32_t *)(this + 4),
           0,
           &IRDActiveObject `RTTI Type Descriptor',
           &IRDCharacter `RTTI Type Descriptor',
           0);
    v5 = v4;
    v15 = v4;
    if ( v4 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 792))(v4, 8) == 0
        || (v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 792))(v5, 8),
            (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 200))(v6) == 0) )
      {
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 1096))(v5);
        v8 = *(uint32_t **)(this + 84);
        v14 = v7;
        sub_45E5A0(&v13, v8, *(uint32_t **)(this + 88), &v14);
        if ( v13 != *(uint32_t *)(this + 88) )
        {
          if ( *(uint32_t *)(this + 96) != 17 )
          {
            v9 = 0;
            v10 = (uint32_t *)(a2 + 24);
            while ( 1 )
            {
              if ( *v10 == 17 )
              {
                *(uint32_t *)(a2 + 4 * v9 + 24) = *(uint32_t *)(this + 96);
                *(uint32_t *)(a2 + 4 * v9 + 36) = *(uint32_t *)(this + 100);
                v11 = *(uint32_t *)(this + 104);
                goto LABEL_14;
              }
              v5 = v15;
              if ( *v10 == *(uint32_t *)(this + 96) )
                break;
              ++v9;
              ++v10;
              if ( v9 >= 3 )
                goto LABEL_15;
            }
            v12 = *(uint32_t *)(a2 + 4 * v9 + 48);
            *(float *)(a2 + 4 * v9 + 36) = *(float *)(this + 100) + *(float *)(a2 + 4 * v9 + 36);
            v11 = *(uint32_t *)(this + 104) + v12;
LABEL_14:
            *(uint32_t *)(a2 + 4 * v9 + 48) = v11;
          }
LABEL_15:
          if ( *(uint32_t *)(a2 + 136) == -1082130432 )
            *(float *)(a2 + 136) = ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)v5 + 1188))(v5);
          *(float *)(a2 + 136) = *(float *)(this + 116) * *(float *)(a2 + 136);
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5F9DD0 sub_5F9DD0
// ------------------------------------------------------------
// 调: sub_5F9DD0 sub_47E720 sub_47EF20 sub_431230
int /*thiscall*/ sub_5F9DD0(int this, int a2)
{
  int result; // eax
  int v5; // eax
  void *v6; // ecx
  uint32_t *v7; // eax
  int v8; // [esp-Ch] [ebp-18h]
  int v9; // [esp+8h] [ebp-4h] BYREF
  int v10; // [esp+14h] [ebp+8h]

  result = *(uint32_t *)(this + 132);
  if ( a2 != result )
  {
    v5 = *(uint32_t *)(this + 128);
    v8 = *(uint32_t *)(this + 124);
    *(uint32_t *)(this + 132) = a2;
    sub_47E720(v8, v5);
    v6 = *(void **)(this + 84);
    v7 = (uint32_t *)(this + 80);
    v10 = this + 80;
    if ( v6 != nullptr )
    {
      j__free(v6);
      v7 = (uint32_t *)(this + 80);
    }
    v7[1] = 0;
    v7[2] = 0;
    v7[3] = 0;
    result = *(uint32_t *)(this + 124);
    if ( result != 0 )
    {
      switch ( result )
      {
        case 1:
          if ( *(uint32_t *)(this + 128) == 45 )
          {
            *(uint32_t *)(this + 96) = 11;
            *(float *)(this + 100) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.1;
            *(uint32_t *)(this + 104) = sub_47EF20(1, a2, -1, -1, 11);
            v9 = 2;
            return sub_431230(v10, &v9);
          }
          break;
        case 2:
          if ( *(uint32_t *)(this + 128) == 52 )
          {
            v9 = 3;
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.001;
            return sub_431230(v10, &v9);
          }
          break;
        case 3:
          result = *(uint32_t *)(this + 128);
          if ( result == 35 )
          {
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.001;
            v9 = 0;
            *(float *)(this + 120) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.001;
            return sub_431230(v10, &v9);
          }
          if ( result == 36 )
          {
            *(float *)(this + 108) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.001;
            *(float *)(this + 120) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.001;
            goto LABEL_26;
          }
          break;
        default:
          return result;
      }
    }
    else
    {
      result = *(uint32_t *)(this + 128);
      switch ( result )
      {
        case 12:
          v9 = 0;
          *(float *)(this + 112) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.1;
          return sub_431230(v10, &v9);
        case 13:
          *(uint32_t *)(this + 96) = 11;
          *(uint32_t *)(this + 104) = sub_47EF20(0, a2, -1, -1, 11);
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.1;
LABEL_26:
          v9 = 1;
          return sub_431230(v10, &v9);
        case 14:
          *(float *)(this + 116) = (double)(int)sub_47EF20(0, a2, -1, -1, 11) * 0.0099999998 + 1.0;
          v9 = 3;
          *(float *)(this + 108) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.001;
          return sub_431230(v10, &v9);
        case 15:
          *(uint32_t *)(this + 96) = 3;
          *(uint32_t *)(this + 104) = sub_47EF20(0, a2, -1, -1, 11);
          v9 = 2;
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.1;
          return sub_431230(v10, &v9);
        case 4:
          *(uint32_t *)(this + 96) = 6;
          *(uint32_t *)(this + 104) = sub_47EF20(0, a2, -1, -1, 11);
          v9 = 5;
          *(float *)(this + 100) = (double)(int)sub_47EF20(1, a2, -1, -1, 11) * 0.1;
          return sub_431230(v10, &v9);
        default:
          break;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x5FA160 sub_5FA160
// ------------------------------------------------------------
// 调: sub_5FA160
int /*thiscall*/ sub_5FA160(uint32_t *this)
{
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FA170 CNRobotics__vmt1C
// ------------------------------------------------------------
// 证: "POWER_UP"
// 调: sub_47EF20
int /*thiscall*/ CNRobotics__vmt1C(int *this)
{
  int result; // eax
  int v2; // esi
  uint32_t *v3; // edi
  int v4; // ebx

  result = __RTDynamicCast(*(this + 1), 0, &IRDActiveObject `RTTI Type Descriptor', &CNGunner `RTTI Type Descriptor', 0);
  v2 = result;
  if ( result != 0 )
  {
    v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 46);
    v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 1140))(v2, 46);
    *(this + 23) = sub_47EF20(v3, 1u, v4, -1, -1, 11);
    *(this + 24) = sub_47EF20(v3, 2u, v4, -1, -1, 11);
    *(this + 25) = sub_47EF20(v3, 3u, v4, -1, -1, 11);
    *(this + 26) = sub_47EF20(v3, 4u, v4, -1, -1, 11);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v2 + 212))(
             v2,
             "POWER_UP",
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA230 CNRobotics__vmt20
// ------------------------------------------------------------
// 调: sub_41C5E0 sub_4C1400
uint32_t */*thiscall*/ CNRobotics__vmt20(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  uint32_t *v4; // eax
  void *i; // ebx
  uint32_t *v6; // edi
  uint32_t *v7; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  v3 = (uint32_t *)*(this + 21);
  v4 = (uint32_t *)*v3;
  v9 = (uint32_t *)*v3;
  if ( v9 != v3 )
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)v4[4] + 76))(v4[4], 0);
      sub_41C5E0(&v9);
      v4 = v9;
    }
    while ( v9 != (uint32_t *)*(this + 21) );
  }
  v6 = this + 20;
  v7 = *(uint32_t **)(*(this + 21) + 4);
  for ( i = v7; *((uint8_t *)v7 + 21) == 0; i = v7 )
  {
    sub_4C1400((void *)v7[2]);
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
// 0x5FA2C0 sub_5FA2C0
// ------------------------------------------------------------
// 调: sub_5FA2C0 sub_4015C0 sub_401740 sub_5648C0 sub_433130
int */*thiscall*/ sub_5FA2C0(int **this, int *a2, char a3, int *a4, int a5)
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
// 0x5FA470 CNRobotics__vmt30
// ------------------------------------------------------------
// 调: sub_41C5E0 sub_4C1400 sub_4BE520 sub_4C20A0
int /*thiscall*/ CNRobotics__vmt30(int **this, int a2)
{
  int v2; // esi
  int *v4; // ecx
  int v5; // eax
  uint32_t *v6; // eax
  int result; // eax
  int v8; // esi
  int v9; // [esp+Ch] [ebp-4h] BYREF

  v2 = a2;
  IRDAppendage__vmt30(this, a2);
  if ( (int *)v2 == *(this + 1) )
  {
    v4 = *(this + 21);
    v5 = *v4;
    v9 = *v4;
    if ( (int *)v9 != v4 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v5 + 16) + 76))(*(uint32_t *)(v5 + 16), 0);
        sub_41C5E0(&v9);
        v5 = v9;
      }
      while ( (int *)v9 != *(this + 21) );
    }
    sub_4C1400((void *)(*(this + 21))[1]);
    (*(this + 21))[1] = (int)*(this + 21);
    v6 = *(this + 21);
    *(this + 22) = nullptr;
    *v6 = v6;
    (*(this + 21))[2] = (int)*(this + 21);
  }
  result = sub_4BE520(&v9, &a2);
  v8 = v9;
  if ( (int *)v9 != *(this + 21) )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v9 + 16) + 76))(*(uint32_t *)(v9 + 16), 0);
    return sub_4C20A0(&a2, v8);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA510 sub_5FA510
// ------------------------------------------------------------
// 调: sub_5FA510 sub_5FA2C0 sub_4A3B30
int /*thiscall*/ sub_5FA510(int **this, int a2, int *a3)
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
      v10 = *sub_5FA2C0(this, (int *)&a3, 1, v5, (int)v3);
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
    v12 = *sub_5FA2C0(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x5FA5D0 sub_5FA5D0
// ------------------------------------------------------------
// 调: sub_5FA5D0 sub_4B3C90
int /*thiscall*/ sub_5FA5D0(int *this)
{
  int v2; // esi
  float v4; // [esp+24h] [ebp-1Ch]
  float v5; // [esp+24h] [ebp-1Ch]
  float v6; // [esp+24h] [ebp-1Ch]
  float v7; // [esp+24h] [ebp-1Ch]

  if ( operator new(0x7Cu) != nullptr )
    v2 = sub_4B3C90(0, 2);
  else
    v2 = 0;
  v4 = (float)*(this + 23);
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v2 + 120))(v2, 10, 1, LODWORD(v4));
  v5 = (float)*(this + 24);
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v2 + 120))(v2, 0, 0, LODWORD(v5));
  v6 = (float)*(this + 25);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v2 + 120))(v2, 1, 0, LODWORD(v6));
  v7 = (float)*(this + 26);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v2 + 120))(v2, 8, 0, LODWORD(v7));
  return v2;
}



// ------------------------------------------------------------
// 0x5FA680 CNRobotics__vmt4
// ------------------------------------------------------------
// 调: sub_4C0400 sub_4BE520 sub_5FA5D0 sub_5FA510
int /*thiscall*/ CNRobotics__vmt4(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // ecx
  int result; // eax
  unsigned int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  uint32_t *v12; // eax
  int v13; // ebx
  int v14; // ebx
  int v15; // eax
  int v16[2]; // [esp+4h] [ebp-20h] BYREF
  uint8_t v17[4]; // [esp+Ch] [ebp-18h] BYREF
  int v18; // [esp+10h] [ebp-14h]
  uint8_t v19[4]; // [esp+14h] [ebp-10h] BYREF
  int v20; // [esp+18h] [ebp-Ch] BYREF
  int v21; // [esp+1Ch] [ebp-8h]
  signed int v22; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  v2 = *(uint32_t *)(this + 4);
  if ( v2 == 0 || (*(int (**)(void))(*(uint32_t *)v2 + 80))() == 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));
  v4 = v3;
  v5 = *(uint32_t *)(v3 + 120);
  v18 = v3;
  if ( v5 != 0 )
    v21 = (*(uint32_t *)(v3 + 124) - v5) >> 2;
  else
    v21 = 0;
  result = v21;
  v7 = 0;
  v22 = 0;
  if ( v21 > 0 )
  {
    while ( 1 )
    {
      v8 = *(uint32_t *)(v4 + 120);
      if ( v8 != 0 && v7 < (*(uint32_t *)(v4 + 124) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * v7);
      else
        v9 = 0;
      v10 = __RTDynamicCast(v9, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      v11 = v10;
      if ( v10 != 0 )
      {
        v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 340))(v10);
        if ( (uint8_t)sub_4C0400(*v12) != 0 )
        {
          v20 = v11;
          if ( *(uint32_t *)sub_4BE520(v17, &v20) == *(uint32_t *)(this + 84) )
          {
            v13 = sub_5FA5D0((int *)this);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v13 + 56))(
              v13,
              v11,
              *(uint32_t *)(this + 4),
              0,
              0,
              0,
              -1);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 676))(v11, 2);
            v16[0] = v11;
            v16[1] = v13;
            sub_5FA510((int **)(this + 80), (int)v19, v16);
            v14 = *(uint32_t *)v11;
            v15 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v11 + 736))(v11, *(uint32_t *)(this + 4), 1);
            (*(void (/*thiscall*/ **)(int, int))(v14 + 732))(v11, *(uint32_t *)(this + 92) + v15);
            v4 = v18;
          }
        }
      }
      result = ++v22;
      if ( v22 >= v21 )
        break;
      v7 = v22;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FA7E0 CNRDActiveStatus__vmt50
// ------------------------------------------------------------
// 调: sub_699000 sub_698F90
void /*thiscall*/ CNRDActiveStatus__vmt50(int this, int a2)
{
  int v3; // ebx
  int v4; // ebx
  int v5; // ebx
  int v6; // eax
  double v7; // st7
  int v8; // ecx

  if ( a2 == *(uint32_t *)(this + 4)
    && (*(uint32_t *)(this + 8) == 1 || *(uint32_t *)(this + 8) == 3 || *(uint32_t *)(this + 8) == 7) )
  {
    v3 = *(uint32_t *)(this + 84);
    if ( v3 < sub_699000(this + 60) )
    {
      v5 = 0;
    }
    else
    {
      v4 = *(uint32_t *)(this + 84);
      v5 = v4 - sub_699000(this + 60);
    }
    v6 = *(uint32_t *)(this + 88) + 500;
    *(uint32_t *)(this + 88) = v6;
    v7 = (double)*(int *)(this + 88);
    if ( v6 < 0 )
      v7 = v7 + 4294967300.0;
    if ( (double)*(unsigned int *)(this + 92) * 0.80000001 >= v7 )
    {
      if ( v5 - 500 > 0 )
      {
        *(uint8_t *)(this + 73) = 0;
        *(uint8_t *)(this + 74) = 0;
        sub_698F90(this + 60, v5 - 500, 0);
      }
      v8 = *(uint32_t *)(this + 4);
      if ( *(uint32_t *)(this + 8) == 3 )
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 920))(v8);
      else
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 916))(v8);
    }
  }
}



// ------------------------------------------------------------
// 0x5FA8B0 CNRDActiveStatus__vmt38
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491EA0
char /*thiscall*/ CNRDActiveStatus__vmt38(int this, char a2, int a3, int a4, float a5)
{
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax

  v6 = *(uint32_t *)(this + 8) - 1;
  if ( *(uint32_t *)(this + 8) == 1 )
  {
    LOBYTE(v6) = *(uint8_t *)(this + 97);
    if ( (uint8_t)v6 == 0 )
    {
      if ( a2 != 0 )
      {
        sub_4938F0(*(uint32_t *)(this + 24));
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));
        sub_491EA0(dword_79C0B0, a3, a4, a5, v7, 0.40000001, 0.30000001, 100);
        v8 = *(uint32_t *)(this + 28);
        LOBYTE(v6) = *(uint8_t *)(v8 + 170);
        if ( (uint8_t)v6 == 0 )
        {
          sub_4938F0(v8);
          v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));
          LOBYTE(v6) = sub_491EA0(dword_79C0B0, a3, a4, a5, v9, 0.40000001, 0.30000001, 100);
        }
      }
      else
      {
        sub_4938F0(*(uint32_t *)(this + 20));
        v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));
        LOBYTE(v6) = sub_491EA0(dword_79C0B0, a3, a4, a5, v10, 0.40000001, 0.30000001, 100);
      }
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x5FA9A0 CNRDActiveStatus__vmt4C
// ------------------------------------------------------------
// 证: "STONE_CUT"
// 调: sub_4AED00 sub_497120 sub_605840 sub_4E4A50
char /*userpurge*/ sub_5FA9A0@<al>(uint32_t *a1@<ecx>, double a2@<st0>, int *a3, int a4, int a5)
{
  int v6; // eax
  int v8; // edx
  float *v9; // eax
  int v10; // esi
  float v11; // ecx
  float v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v19; // [esp-28h] [ebp-48h]
  int v20; // [esp-24h] [ebp-44h]
  int v21; // [esp-20h] [ebp-40h]
  int v22; // [esp-1Ch] [ebp-3Ch]
  int v23; // [esp-1Ch] [ebp-3Ch]
  int v24; // [esp-10h] [ebp-30h]
  int v25; // [esp-Ch] [ebp-2Ch]
  float v26; // [esp+4h] [ebp-1Ch] BYREF
  float v27; // [esp+8h] [ebp-18h]
  float v28; // [esp+Ch] [ebp-14h]
  int v29; // [esp+10h] [ebp-10h]
  int v30; // [esp+14h] [ebp-Ch]
  int v31; // [esp+18h] [ebp-8h]
  int v32; // [esp+1Ch] [ebp-4h]
  int v33; // [esp+28h] [ebp+8h]

  if ( a1[2] == 6 )
  {
    LOBYTE(v6) = a5;
    if ( (uint8_t)a5 == 0 )
    {
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[1] + 308))(a1[1]);
      if ( (uint8_t)v6 != 0 )
      {
        v8 = *a3;
        HIBYTE(a5) = 1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v8 + 40))(a3, 33) != 0
          && *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*a3 + 340))(a3) == 46002 )
        {
          HIBYTE(a5) = 0;
        }
        v9 = (float *)(*(int (/*thiscall*/ **)(int *))(*a3 + 348))(a3);
        if ( !sub_4AED00(v9) )
          HIBYTE(a5) = 0;
        v10 = a1[1];
        v33 = (*(int (/*thiscall*/ **)(int *))(*a3 + 376))(a3);
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10);
        if ( v33 != v6 )
        {
          LOBYTE(v6) = HIBYTE(a5);
          if ( HIBYTE(a5) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[1] + 564))(a1[1]);
            sub_497120(6, a1[3]);
            v32 = (uint64_t)a2;
            v11 = *(float *)(a4 + 4);
            v26 = *(float *)a4;
            v12 = *(float *)(a4 + 8);
            v27 = v11;
            v13 = *(uint32_t *)(a4 + 12);
            v28 = v12;
            v14 = *(uint32_t *)(a4 + 16);
            v29 = v13;
            v15 = *(uint32_t *)(a4 + 20);
            v30 = v14;
            v31 = v15;
            v26 = (double)(rand() % 60 - 30) + v26;
            v27 = (double)(rand() % 60 - 30) + v27;
            v16 = rand();
            v22 = a1[1];
            a5 = 0;
            v28 = (double)(v16 % 60 - 30) + v28;
            v25 = sub_605840(&a5, v22, &v26, 0);
            v24 = a5;
            v23 = (uint64_t)*(float *)(a4 + 8);
            v21 = (uint64_t)*(float *)(a4 + 4);
            v20 = (uint64_t)*(float *)a4;
            v19 = v32;
            v17 = (*(int (/*thiscall*/ **)(int *))(*a3 + 576))(a3);
            LOBYTE(v6) = sub_4E4A50((int)a1, v17, 46002, v19, v20, v21, v23, 1, 0, v24, v25);
          }
        }
      }
    }
  }
  else if ( a1[2] == 7 )
  {
    LOBYTE(v6) = a5;
    if ( (uint8_t)a5 == 0 )
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1[1] + 212))(
                     a1[1],
                     "STONE_CUT",
                     -1,
                     0,
                     0);
  }
  else
  {
    v6 = a1[2] - 8;
    if ( a1[2] == 8 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 28))(a1);
      if ( v6 > 200 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int *))(*a1 + 4))(a1, 0, a3);
    }
  }
  return v6;
}


// ------------------------------------------------------------
// 0x5FABA0 sub_5FABA0
// ------------------------------------------------------------
// 调: sub_5FABA0
int /*thiscall*/ sub_5FABA0(int this)
{
  int result; // eax

  if ( *(uint8_t *)(this + 97) == 0
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) != 9
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4)) != 9 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(
      *(uint32_t *)(this + 4),
      9,
      0,
      0,
      0);
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 0) != 100 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, 100);
  if ( (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 1) != 200 )
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, 200);
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 2);
  if ( result != 255 )
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, 255);
  return result;
}



// ------------------------------------------------------------
// 0x5FAC50 sub_5FAC50
// ------------------------------------------------------------
// 调: sub_5FAC50 sub_4938F0 sub_491D00
char /*thiscall*/ sub_5FAC50(int this, char a2, int a3, int a4, float a5)
{
  char result; // al
  int v7; // ecx

  result = *(uint8_t *)(this + 97);
  if ( result == 0 )
  {
    if ( a2 != 0 )
    {
      sub_4938F0(*(uint32_t *)(this + 24));
      sub_491D00(dword_79C0B0, a3, a4, a5);
      v7 = *(uint32_t *)(this + 28);
      result = *(uint8_t *)(v7 + 170);
      if ( result == 0 )
      {
        sub_4938F0(v7);
        return sub_491D00(dword_79C0B0, a3, a4, a5);
      }
    }
    else
    {
      sub_4938F0(*(uint32_t *)(this + 20));
      return sub_491D00(dword_79C0B0, a3, a4, a5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FACE0 sub_5FACE0
// ------------------------------------------------------------
// 调: sub_5FACE0 sub_41A5E0 sub_41A590
int /*stdcall*/ sub_5FACE0(int a1)
{
  int v1; // eax
  int v2; // edx
  int v3; // edx

  v1 = sub_41A5E0(a1 + 88);
  sub_41A590(a1 + 88, v2, v1 + 100);
  return sub_41A590(a1 + 382, v3, 1000);
}



// ------------------------------------------------------------
// 0x5FAD20 sub_5FAD20
// ------------------------------------------------------------
// 调: sub_5FAD20 sub_4938F0 sub_491D00
char /*thiscall*/ sub_5FAD20(int this, char a2, int a3, int a4, float a5)
{
  char result; // al

  result = *(uint8_t *)(this + 97);
  if ( result == 0 )
  {
    result = a2;
    if ( a2 != 0 )
    {
      sub_4938F0(*(uint32_t *)(this + 20));
      return sub_491D00(dword_79C0B0, a3, a4, a5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FAD60 CNRDActiveStatus__vmt30
// ------------------------------------------------------------
// 调: sub_4E99C0 sub_4D8700 sub_4450B0 sub_41A590 sub_5FACE0
int /*fastcall*/ CNRDActiveStatus__vmt30(int a1, int a2, int a3)
{
  int result; // eax
  int v5; // edx
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+0h] [ebp-Ch]
  float v8; // [esp+0h] [ebp-Ch]
  float v9; // [esp+0h] [ebp-Ch]
  float v10; // [esp+0h] [ebp-Ch]
  float v11; // [esp+0h] [ebp-Ch]
  float v12; // [esp+0h] [ebp-Ch]
  float v13; // [esp+0h] [ebp-Ch]
  float v14; // [esp+0h] [ebp-Ch]
  float v15; // [esp+0h] [ebp-Ch]
  float v16; // [esp+0h] [ebp-Ch]
  float v17; // [esp+0h] [ebp-Ch]

  result = *(uint32_t *)(a1 + 8);
  switch ( result )
  {
    case 0:
      v6 = 1.0 - *(float *)(a1 + 104);
      sub_4E99C0(v6);
      v7 = 1.0 - *(float *)(a1 + 104);
      result = sub_4E99C0(v7);
      break;
    case 1:
      sub_4D8700(50);
      sub_4450B0((void *)(a3 + 186), 50);
      result = sub_41A590(a3 + 298, v5, 1000);
      break;
    case 3:
      result = sub_41A590(a3 + 326, a2, 1000);
      break;
    case 4:
      v8 = 1.0 - *(float *)(a1 + 184);
      sub_4E99C0(v8);
      v9 = 1.0 - *(float *)(a1 + 184);
      sub_4E99C0(v9);
      v10 = 1.0 - *(float *)(a1 + 184);
      sub_4E99C0(v10);
      v11 = 1.0 - *(float *)(a1 + 184);
      result = sub_4E99C0(v11);
      break;
    case 7:
      result = sub_5FACE0(a3);
      break;
    case 8:
      result = sub_41A590(a3 + 396, a2, 1000);
      break;
    case 12:
      v12 = *(float *)(a1 + 188) - 1.0;
      sub_4AED60(v12);
      v13 = *(float *)(a1 + 188) - 1.0;
      result = sub_4AED60(v13);
      break;
    case 13:
      v14 = *(float *)(a1 + 192) - 1.0;
      sub_4AED60(v14);
      v15 = *(float *)(a1 + 192) - 1.0;
      sub_4AED60(v15);
      v16 = *(float *)(a1 + 192) - 1.0;
      sub_4AED60(v16);
      v17 = *(float *)(a1 + 192) - 1.0;
      result = sub_4AED60(v17);
      break;
    case 16:
      result = sub_41A590(a3 + 494, a2, 1000);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FAFC0 CNRDActiveStatus__vmt34
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491D00 sub_5FAC50 sub_491DE0
char /*thiscall*/ sub_5FAFC0(int this, float a2, int a3, int a4, float a5)
{
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int v14; // eax
  double v15; // st7
  double v16; // st7
  double v17; // st7
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  double v27; // st7
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v32; // [esp-24h] [ebp-34h]
  int v33; // [esp-24h] [ebp-34h]
  int v34; // [esp-24h] [ebp-34h]
  float v35; // [esp-18h] [ebp-28h]
  float v36; // [esp-18h] [ebp-28h]
  double v37; // [esp+8h] [ebp-8h]
  double v38; // [esp+8h] [ebp-8h]
  double v39; // [esp+8h] [ebp-8h]
  float v40; // [esp+18h] [ebp+8h]
  float v41; // [esp+20h] [ebp+10h]
  float v42; // [esp+20h] [ebp+10h]
  float v43; // [esp+20h] [ebp+10h]

  v6 = *(uint32_t *)(dword_8F7A24 + 244) != 2 ? 50 : 30;
  v7 = *(uint32_t *)(this + 8);
  switch ( v7 )
  {
    case 0:
    case 12:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = LOBYTE(a2);
          if ( LOBYTE(a2) != 0 )
          {
            sub_4938F0(*(uint32_t *)(this + 20));
            v30 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4));
            LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, a4 + v30, 0.0);
          }
        }
      }
      break;
    case 1:
      LOBYTE(v7) = sub_5FAC50(SLOBYTE(a2), a3, a4, a5);
      break;
    case 2:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = LOBYTE(a2);
          if ( LOBYTE(a2) != 0 )
          {
            v37 = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;
            v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
            if ( v7 != 0 )
            {
              v8 = *(uint32_t *)(this + 4);
              v9 = -(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 152))(v8);
              LOBYTE(v9) = v9 == 0;
              v35 = *(float *)&v9;
              v32 = dword_79C0B0;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 200))(v8);
              LOBYTE(v7) = sub_491DE0(
                             v32,
                             a3,
                             a4,
                             v35,
                             0,
                             1,
                             -65281,
                             ((uint8_t)(uint64_t)v37 << 24) | 0xFFFFFF);
            }
          }
        }
      }
      break;
    case 3:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          sub_4938F0(*(uint32_t *)(this + 4 * (LOBYTE(a2) != 0) + 20));
          v28 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
          LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, a4 - v28 - 5, a5);
        }
      }
      break;
    case 5:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          if ( LOBYTE(a2) != 0 )
            sub_4938F0(*(uint32_t *)(this + 24));
          else
            sub_4938F0(*(uint32_t *)(this + 20));
          v29 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
          LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, a4 - v29 - 5, a5);
        }
      }
      break;
    case 6:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = LOBYTE(a2);
        if ( LOBYTE(a2) != 0 )
          goto LABEL_44;
      }
      break;
    case 7:
      LOBYTE(v7) = sub_5FAD20(SLOBYTE(a2), a3, a4, a5);
      break;
    case 8:
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));
      if ( v7 == 4 )
      {
        LOBYTE(v7) = *(uint8_t *)(this + 97);
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
          if ( (uint8_t)v7 == 0 )
          {
            LOBYTE(v7) = LOBYTE(a2);
            if ( LOBYTE(a2) != 0 )
            {
              v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 152))(*(uint32_t *)(this + 4));
              v19 = *(uint32_t *)(this + 4);
              if ( v18 != 0 )
              {
                if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 152))(v19) == 1 )
                {
                  v40 = (float)a3;
                  v23 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
                  v24 = sub_42F220(v23);
                  v22 = (uint64_t)(v40 - (double)(int)sub_4918E0(v24, 1) * 0.75);
                }
                else
                {
                  v22 = a3;
                }
              }
              else
              {
                v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 200))(v19);
                v21 = sub_42F220(v20);
                v22 = (uint64_t)((double)(int)sub_4918E0(v21, 1) * 0.75 + (double)a3);
              }
              sub_4938F0(*(uint32_t *)(this + 20));
              v43 = (float)a4;
              v25 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
              v26 = sub_42F220(v25);
              v27 = v43 - (double)(int)sub_4918E0(v26, 2) * 0.5;
              LOBYTE(v7) = sub_491D00(dword_79C0B0, v22, (uint64_t)v27, 0.0);
            }
          }
        }
      }
      break;
    case 9:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = LOBYTE(a2);
          if ( LOBYTE(a2) != 0 )
          {
            v38 = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;
            if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )
            {
              v10 = *(uint32_t *)(this + 4);
              v11 = -(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 152))(v10);
              LOBYTE(v11) = v11 == 0;
              v36 = *(float *)&v11;
              v33 = dword_79C0B0;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 200))(v10);
              sub_491DE0(v33, a3, a4, v36, 0, 1, -16776961, ((uint8_t)(uint64_t)v38 << 24) | 0xFFFFFF);
            }
LABEL_44:
            sub_4938F0(*(uint32_t *)(this + 20));
            LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, a4, 0.0);
          }
        }
      }
      break;
    case 11:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = LOBYTE(a2);
        if ( LOBYTE(a2) != 0 )
        {
          LOBYTE(a2) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 152))(*(uint32_t *)(this + 4)) == 0;
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0 )
          {
            v39 = sin((double)timeGetTime() * 0.008975979010256551) * 25.0 + (double)(unsigned int)v6;
            if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )
            {
              v34 = dword_79C0B0;
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
              sub_491DE0(v34, a3, a4, a2, 0, 1, -16776961, ((uint8_t)(uint64_t)v39 << 24) | 0xFFFFFF);
            }
          }
          LOBYTE(v7) = dword_8F7A24;
          if ( *(uint32_t *)(dword_8F7A24 + 244) != 2 )
          {
            sub_4938F0(*(uint32_t *)(this + 20));
            v41 = (float)a4;
            v12 = v41
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                * 0.80000001;
            LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, (uint64_t)v12, a2);
          }
        }
      }
      break;
    case 15:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = LOBYTE(a2);
          if ( LOBYTE(a2) != 0 )
          {
            sub_4938F0(*(uint32_t *)(this + 20));
            sub_4938F0(*(uint32_t *)(this + 24));
            v13 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
            sub_491D00(dword_79C0B0, a3, a4 - v13 - 50, 0.0);
            v14 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
            LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, a4 - v14 - 50, 0.0);
          }
        }
      }
      break;
    case 16:
      LOBYTE(v7) = *(uint8_t *)(this + 97);
      if ( (uint8_t)v7 == 0 )
      {
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
        if ( (uint8_t)v7 == 0 )
        {
          LOBYTE(v7) = LOBYTE(a2);
          if ( LOBYTE(a2) != 0 )
          {
            sub_4938F0(*(uint32_t *)(this + 20));
            sub_4938F0(*(uint32_t *)(this + 24));
            sub_4938F0(*(uint32_t *)(this + 28));
            v42 = (float)a4;
            v15 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                * 0.85000002;
            sub_491D00(dword_79C0B0, a3, (uint64_t)v15, 0.0);
            v16 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                * 0.55000001;
            sub_491D00(dword_79C0B0, a3, (uint64_t)v16, 0.0);
            v17 = v42
                - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4)) * 0.25;
            LOBYTE(v7) = sub_491D00(dword_79C0B0, a3, (uint64_t)v17, 0.0);
          }
        }
      }
      break;
    default:
      return v7;
  }
  return v7;
}


// ------------------------------------------------------------
// 0x5FB780 sub_5FB780
// ------------------------------------------------------------
// 证: "CONDITION_STONE"
// 调: sub_5FB780 sub_4926A0 sub_497150 sub_41A5E0
char /*thiscall*/ sub_5FB780(int this, char a2)
{
  char result; // al
  uint64_t v4; // rax
  int v5; // ecx
  int v6; // edi
  int v7; // [esp+10h] [ebp+8h]

  result = a2;
  if ( a2 != 0 )
  {
    sub_4926A0(*(uint32_t *)(this + 20));
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 40) + 12))(*(uint32_t *)(this + 40), 0);
    v4 = (uint64_t)sub_497150(*(uint32_t *)(this + 8), *(uint32_t *)(this + 12));
    v5 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 124) = v4;
    v6 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)v5 + 672))(v5, HIDWORD(v4), 3);
    v7 = sub_41A5E0(v6 + 382);
    *(uint32_t *)(this + 124) = (int)(*(uint32_t *)(this + 124)
                                  * (100 - (uint64_t)((double)v7 * COERCE_FLOAT(sub_41A5E0(v6 + 606)))))
                            / 100;
    return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
             *(uint32_t *)(this + 4),
             "CONDITION_STONE",
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FB830 CNRDActiveStatus__vmt3C
// ------------------------------------------------------------
// 证: "CONDITION_SLOW" | "FROZEN" | "CONDITION_POSION" | "G_POISON_LOOP"
// 调: sub_497120 sub_4926A0 sub_699000 sub_699030
char /*thiscall*/ sub_5FB830(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  uint32_t *v8; // edi
  int i; // ebx
  int v10; // eax
  int v11; // ecx
  float *v12; // eax
  float v13; // ecx
  uint32_t *v14; // edi
  int j; // ebx
  int v16; // eax
  float v18; // [esp+Ch] [ebp-8h]
  float v19; // [esp+10h] [ebp-4h]

  v3 = *this;
  v4 = 0;
  *(this + 22) = 0;
  *((uint8_t *)this + 97) = 0;
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 36))(0);
  switch ( *(this + 2) )
  {
    case 0:
      *((float *)this + 26) = sub_497120(0, *(this + 3));
      if ( (uint8_t)a2 != 0 )
        sub_4926A0(*(this + 5));
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_SLOW",
        -1,
        0,
        0);
      goto LABEL_61;
    case 1:
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) + 12) == 0 )
        goto LABEL_18;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 940))(*(this + 1)) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*(this + 1) + 944))(*(this + 1), 0, -1);
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);
      if ( (uint8_t)a2 != 0 )
      {
        v8 = this + 5;
        for ( i = 3; i != 0; --i )
          sub_4926A0(*v8++);
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "FROZEN",
          -1,
          0,
          0);
        v4 = 0;
      }
      goto LABEL_61;
    case 2:
      *(this + 32) = 0;
      *(this + 34) = 0;
      *(this + 33) = -300;
      v10 = sub_699000((int)(this + 15));
      v11 = *(this + 10);
      *(this + 35) = v10 + 500;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 12))(v11, 0);
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_POSION",
        -1,
        0,
        0);
      if ( (uint8_t)a2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "G_POISON_LOOP",
          2,
          0,
          0);
      goto LABEL_61;
    case 3:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 776))(*(this + 1), 8) != 0 )
        goto LABEL_18;
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);
      sub_699030((int)(this + 15));
      goto LABEL_61;
    case 4:
      *((float *)this + 46) = sub_497120(4, *(this + 3));
      if ( (uint8_t)a2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 10) + 12))(*(this + 10), 0);
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_CURSE",
        -1,
        0,
        0);
      goto LABEL_61;
    case 5:
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_BLIND",
        -1,
        0,
        0);
      goto LABEL_61;
    case 6:
      if ( (uint8_t)a2 != 0 )
        sub_4926A0(*(this + 5));
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDTION_LIGHT",
        -1,
        0,
        0);
      if ( (uint8_t)a2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "CONDITION_LIGTHNING_LOOP",
          4,
          0,
          0);
      goto LABEL_61;
    case 7:
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) + 12) == 0 )
      {
LABEL_18:
        LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 4))(this, 0, 0);
        return v5;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 940))(*(this + 1)) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*(this + 1) + 944))(*(this + 1), 0, -1);
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 848))(*(this + 1), 1);
      sub_5FB780(a2);
      goto LABEL_61;
    case 8:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 776))(*(this + 1), 3) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 4))(this, 0, 0);
        LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 840))(*(this + 1)) == 9;
        *((uint8_t *)this + 204) = v5;
      }
      else
      {
        sub_699030((int)(this + 15));
        if ( (uint8_t)a2 != 0 )
          sub_4926A0(*(this + 5));
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "CONDITION_SLEEP",
          -1,
          0,
          0);
LABEL_61:
        LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 40))(*(this + 1), 273);
        if ( (uint8_t)v5 != 0 )
        {
          do
          {
            v5 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 792))(*(this + 1), v4);
            if ( v5 != 0 )
            {
              v16 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 792))(*(this + 1), v4);
              LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v16 + 288))(v16, *(this + 2), a2);
            }
            ++v4;
          }
          while ( v4 < 18 );
        }
      }
      return v5;
    case 9:
      *(this + 36) = 0;
      *(this + 37) = 0;
      *(this + 38) = sub_699000((int)(this + 15)) + 500;
      if ( (uint8_t)a2 != 0 )
      {
        *((uint8_t *)this + 169) = 0;
        *((uint8_t *)this + 170) = 0;
        sub_698F90((int)(this + 39), 1000, 0);
        sub_4926A0(*(this + 5));
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1)) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1));
          if ( sub_4924C0(0) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 688))(*(this + 1));
            v12 = (float *)sub_4924C0(0);
            v13 = *v12;
            if ( *(uint32_t *)v12 != 0 )
            {
              v18 = (double)*(unsigned int *)(LODWORD(v13) + 20) * 1.5 * v12[5] * 0.0099999998;
              v19 = (double)*(unsigned int *)(LODWORD(v13) + 24) * 1.5 * v12[6] * 0.0070921984;
              if ( v18 > 1.0 )
                v18 = 1.0;
              if ( v19 > 1.0 )
                v19 = 1.0;
              sub_4920E0(v18, v19);
            }
          }
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_POSION",
        -1,
        0,
        0);
      if ( (uint8_t)a2 != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "G_POISON_LOOP",
          3,
          0,
          0);
      goto LABEL_61;
    case 0xB:
      v6 = sub_699000((int)(this + 15));
      v7 = *(this + 2);
      *(this + 49) = v6;
      *(this + 50) = (uint64_t)sub_497120(v7, *(this + 3));
      if ( (uint8_t)a2 != 0 )
        sub_4926A0(*(this + 5));
      *(this + 50) = (uint64_t)(sub_433F60(*(this + 4), 0) * (double)(int)*(this + 50));
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_BLOODING",
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xC:
      *((float *)this + 47) = sub_497120(12, *(this + 3));
      if ( (uint8_t)a2 != 0 )
        sub_4926A0(*(this + 5));
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_HASTE",
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xD:
      *((float *)this + 48) = sub_497120(13, *(this + 3));
      if ( (uint8_t)a2 != 0 )
      {
        v14 = this + 10;
        for ( j = 2; j != 0; --j )
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v14 + 12))(*v14, 0);
          ++v14;
        }
        v4 = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_BLESS",
        -1,
        0,
        0);
      goto LABEL_61;
    case 0xF:
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
        *(this + 1),
        "CONDITION_CONFUSE",
        -1,
        0,
        0);
      goto LABEL_61;
    case 0x10:
      if ( (uint8_t)a2 != 0 )
      {
        sub_4926A0(*(this + 5));
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
          *(this + 1),
          "ZIEG_NOVA_READY_LOOP",
          40100,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + 1) + 896))(*(this + 1), 4, 4);
      goto LABEL_61;
    default:
      goto LABEL_61;
  }
}


// ------------------------------------------------------------
// 0x5FBE20 sub_5FBE20
// ------------------------------------------------------------
// 调: sub_5FBE20 sub_4920E0 sub_4600B0
int /*thiscall*/ sub_5FBE20(int this)
{
  int v2; // edi
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // edi
  uint32_t *v9; // eax
  void *v10; // eax
  uint32_t *v11; // eax
  int v12; // edx
  int v13; // edi
  signed int v14; // ecx
  unsigned int v15; // edx
  int result; // eax
  float v17; // [esp-8h] [ebp-38h]
  float v18; // [esp-4h] [ebp-34h]
  uint8_t v19[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v21; // [esp+14h] [ebp-1Ch]
  int v22; // [esp+18h] [ebp-18h]
  int v23; // [esp+1Ch] [ebp-14h]
  int v24; // [esp+20h] [ebp-10h]
  int v25; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 97) == 0
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) != 9
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4)) != 9 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(
      *(uint32_t *)(this + 4),
      9,
      0,
      0,
      0);
  }
  v2 = 100;
  if ( *(uint8_t *)(*(uint32_t *)(this + 20) + 170) == 0
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(this + 20) + 148);
    v24 = *(uint32_t *)(this + 4);
    v4 = **(uint32_t **)(this + 40);
    v23 = v24;
    v5 = (*(int (**)(void))(*(uint32_t *)v24 + 128))();
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v24 + 124))(v24, v5 + 10 * v3);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v23 + 120))(v23, v6);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(uint32_t *)(this + 40), v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 40) + 92))(*(uint32_t *)(this + 40), v19);
    v8 = Block;
    v25 = 0;
    if ( Block != v21 )
    {
      do
      {
        v18 = *(float *)(this + 120);
        v17 = *(float *)(this + 116);
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 96))(*v8);
        sub_4920E0(v9, v17, v18);
        ++v8;
      }
      while ( v8 != v21 );
    }
    v10 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));
    sub_4600B0(v10, 2, 0, (int)v19);
    v11 = *(uint32_t **)(this + 20);
    v12 = v11[11];
    v13 = v11[37];
    if ( v12 != 0 )
    {
      v15 = (int)((uint64_t)(780903145LL * (v11[12] - v12)) >> 32) >> 4;
      v14 = v15 + (v15 >> 31);
    }
    else
    {
      v14 = 0;
    }
    v23 = v13 / v14;
    v2 = (uint64_t)(255.0 - (double)(v13 / v14) * 155.0);
    v25 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v21 = nullptr;
    v22 = 0;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 0) != v2 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, v2);
  if ( (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 1) != v2 )
    (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, v2);
  result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 256))(*(uint32_t *)(this + 4), 2);
  if ( result != v2 )
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, v2);
  return result;
}



// ------------------------------------------------------------
// 0x5FC010 sub_5FC010
// ------------------------------------------------------------
// 证: "STONE_DIE"
// 调: sub_5FC010 sub_4920E0 sub_4600B0
int /*thiscall*/ sub_5FC010(int this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  void *v9; // eax
  float v11; // [esp-Ch] [ebp-34h]
  float v12; // [esp-8h] [ebp-30h]
  uint8_t v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  uint32_t *v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int v17; // [esp+18h] [ebp-10h]
  int v18; // [esp+24h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4)) != 0 )
  {
    v2 = **(uint32_t **)(this + 44);
    v17 = *(uint32_t *)(this + 4);
    v3 = v17;
    v4 = (*(int (**)(void))(*(uint32_t *)v17 + 128))();
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 124))(v3, v4 + 50);
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(uint32_t *)(this + 44), v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 44) + 12))(*(uint32_t *)(this + 44), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 44) + 92))(*(uint32_t *)(this + 44), v13);
    v7 = Block;
    v18 = 0;
    if ( Block != v15 )
    {
      do
      {
        v12 = *(float *)(this + 120);
        v11 = *(float *)(this + 116);
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 96))(*v7);
        sub_4920E0(v8, v11, v12);
        ++v7;
      }
      while ( v7 != v15 );
    }
    v9 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));
    sub_4600B0(v9, 2, 0, (int)v13);
    v18 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v15 = nullptr;
    v16 = 0;
  }
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
           *(uint32_t *)(this + 4),
           "STONE_DIE",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5FC120 sub_5FC120
// ------------------------------------------------------------
// 调: sub_5FC120 sub_699000 sub_698F90 sub_4D5E40 sub_497150
int /*thiscall*/ sub_5FC120(uint32_t *this)
{
  uint32_t *v1; // ebx
  int *v2; // ecx
  int v3; // eax
  int result; // eax
  int v5; // edi
  int v6; // edi
  unsigned int i; // edx
  int v8; // ecx
  int v9; // ecx
  int *v10; // esi
  uint64_t v11; // rax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  float v18; // [esp+4h] [ebp-2Ch] BYREF
  float v19; // [esp+8h] [ebp-28h]
  float v20; // [esp+Ch] [ebp-24h]
  int v21; // [esp+10h] [ebp-20h]
  int v22; // [esp+14h] [ebp-1Ch]
  int v23; // [esp+18h] [ebp-18h]
  uint32_t *v24; // [esp+1Ch] [ebp-14h]
  int v25; // [esp+20h] [ebp-10h]
  int v26; // [esp+24h] [ebp-Ch]
  int v27; // [esp+28h] [ebp-8h] BYREF
  unsigned int v28; // [esp+2Ch] [ebp-4h]

  v1 = this;
  v2 = (int *)*(this + 1);
  v3 = *v2;
  v24 = v1;
  result = (*(int (/*thiscall*/ **)(int *))(v3 + 308))(v2);
  if ( (uint8_t)result != 0 )
  {
    v5 = v1[45];
    result = sub_699000((int)(v1 + 39));
    if ( result >= v5 )
    {
      *((uint8_t *)v1 + 169) = 0;
      *((uint8_t *)v1 + 170) = 0;
      sub_698F90((int)(v1 + 39), 3000, 0);
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v1[1] + 80))(v1[1]);
      v6 = result;
      v25 = result;
      if ( result != 0 )
      {
        for ( i = 0; ; ++i )
        {
          v8 = *(uint32_t *)(v6 + 120);
          v28 = i;
          result = v8 != 0 ? (*(uint32_t *)(v6 + 124) - v8) >> 2 : 0;
          if ( (int)i >= result )
            break;
          v9 = *(uint32_t *)(v6 + 120);
          if ( v9 != 0 && i < (*(uint32_t *)(v6 + 124) - v9) >> 2 )
            v10 = *(int **)(v9 + 4 * i);
          else
            v10 = nullptr;
          if ( (int *)v1[1] != v10 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v10 + 40))(v10, 17) != 0 )
            {
              (*(void (/*thiscall*/ **)(int *, int))(*v10 + 672))(v10, 3);
              if ( (int)sub_4D5E40(9) < 100
                && (*(int (/*thiscall*/ **)(uint32_t, int *, uint32_t))(*(uint32_t *)v1[1] + 8))(v1[1], v10, 0) < 200 )
              {
                v11 = (uint64_t)sub_497150(9, v1[3]);
                HIDWORD(v11) = *v10;
                v12 = v11;
                v18 = 0.0;
                v19 = 0.0;
                v20 = 0.0;
                v21 = 0;
                v22 = 0;
                v23 = 0;
                v26 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v11) + 120))(v10);
                v13 = *v10;
                v18 = (float)v26;
                v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 124))(v10);
                v15 = *v10;
                v26 = v14;
                v19 = (float)v14;
                v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 192))(v10) / 2;
                v26 = (*(int (/*thiscall*/ **)(int *))(*v10 + 128))(v10) + v16;
                v20 = (float)v26;
                v27 = 0;
                v17 = sub_605840(&v27, v10, &v18, 0);
                sub_4E4A50(0, 48039, v12, 0, 0, 0, 1, 0, v27, v17);
                v6 = v25;
                v1 = v24;
              }
            }
            i = v28;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FC2F0 sub_5FC2F0
// ------------------------------------------------------------
// 调: sub_5FC2F0 sub_605840 sub_4E4A50 sub_5FC010
int /*thiscall*/ sub_5FC2F0(int this)
{
  unsigned int v2; // ecx
  unsigned int v3; // eax
  uint64_t v4; // rax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  float v15; // [esp+4h] [ebp-20h] BYREF
  float v16; // [esp+8h] [ebp-1Ch]
  float v17; // [esp+Ch] [ebp-18h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) == 9 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 560))(
      *(uint32_t *)(this + 4),
      0,
      0,
      0,
      0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 0, -1);
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 1, -1);
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 4) + 252))(*(uint32_t *)(this + 4), 2, -1);
  v2 = *(uint32_t *)(this + 88);
  v3 = *(uint32_t *)(this + 92) >> 1;
  if ( v2 <= v3 )
  {
    v21 = *(uint32_t *)(this + 92) >> 1;
    v4 = (uint64_t)((1.0 - (double)v2 / (double)v3) * (double)*(int *)(this + 124));
    v5 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 124) = v4;
    v15 = 0.0;
    v16 = 0.0;
    v17 = 0.0;
    v18 = 0;
    v19 = 0;
    v20 = 0;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 120))(v5);
    v7 = *(uint32_t *)(this + 4);
    v21 = v6;
    v15 = (float)v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
    v9 = *(uint32_t *)(this + 4);
    v21 = v8;
    v16 = (float)v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 192))(v9) / 2;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 128))(v9);
    v12 = *(uint32_t *)(this + 4);
    v21 = v11 + v10;
    v17 = (float)(v11 + v10);
    v22 = 0;
    v13 = sub_605840(&v22, v12, &v15, 1);
    sub_4E4A50(*(uint32_t *)(this + 16), 48011, *(uint32_t *)(this + 124), 0, 0, 0, 1, 0, v22, v13);
  }
  return sub_5FC010(this);
}



// ------------------------------------------------------------
// 0x5FC450 sub_5FC450
// ------------------------------------------------------------
// 调: sub_5FC450 sub_41A5E0 sub_4DA0F0 sub_699000 sub_497120
char /*thiscall*/ sub_5FC450(int this)
{
  char result; // al
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int v6; // ebx
  int *v7; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // [esp-20h] [ebp-2Ch]
  int v17; // [esp-1Ch] [ebp-28h]
  int v18; // [esp-18h] [ebp-24h]
  char v19; // [esp-Ch] [ebp-18h]
  int v20; // [esp-8h] [ebp-14h]
  int v21; // [esp+4h] [ebp-8h]
  int v22; // [esp+8h] [ebp-4h]
  int v23; // [esp+8h] [ebp-4h]
  int v24; // [esp+8h] [ebp-4h]
  int v25; // [esp+8h] [ebp-4h]

  result = *(uint8_t *)(this + 97);
  if ( result == 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);
    v22 = sub_41A5E0(v3 + 410);
    v4 = (double)v22 * COERCE_FLOAT(sub_41A5E0(v3 + 634));
    if ( (int)(uint64_t)v4 < 100 )
    {
      v20 = *(uint32_t *)(this + 100);
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 3);
      v21 = sub_4DA0F0(v20);
      if ( v21 < 150 )
      {
        v5 = *(uint32_t *)(this + 84);
        if ( sub_699000(this + 60) >= v5 )
          v23 = *(uint32_t *)(this + 84);
        else
          v23 = sub_699000(this + 60);
        sub_497120(*(uint32_t *)(this + 8), *(uint32_t *)(this + 12));
        v24 = (uint64_t)((flt_9A0624 - (double)v21 * flt_9A0628)
                               * (double)(int)(uint64_t)(v4 * (double)v23 * 0.001)
                               * 0.0099999998);
        v25 = (uint64_t)(sub_433F60(*(uint32_t *)(this + 16), 0) * (double)v24);
        v6 = v25 - *(uint32_t *)(this + 144);
        if ( v25 != *(uint32_t *)(this + 144) )
        {
          v7 = *(int **)(this + 4);
          v8 = *v7;
          v9 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v7 + 736))(v7, 0, *(uint32_t *)(this + 16));
          (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 728))(*(uint32_t *)(this + 4), v9 - v6);
          *(uint32_t *)(this + 144) = v25;
        }
        if ( *(uint32_t *)(this + 152) < (unsigned int)sub_699000(this + 60) )
        {
          v10 = *(uint32_t *)(this + 148);
          v11 = *(uint32_t *)(this + 16);
          v12 = *(uint32_t *)(this + 144);
          *(uint32_t *)(this + 148) = v12;
          v13 = *(uint32_t *)(this + 4);
          v19 = dword_8F7C04 == v11;
          v18 = v12 - v10;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 192))(v13);
          v17 = v14 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 128))(v13) + 15;
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13);
          sub_4D7960(v14, v13, this, v15, v16, v17, v18, 4, 0, v19);
          *(uint32_t *)(this + 152) = sub_699000(this + 60) + 500;
        }
      }
    }
    return sub_5FC120((uint32_t *)this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FC610 sub_5FC610
// ------------------------------------------------------------
// 证: "BLOOD_DROP_LOOP"
// 调: sub_5FC610 sub_699000 sub_4924C0 sub_4D7960
void /*usercall*/ sub_5FC610(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  double v5; // st7
  int i; // edi
  int *v7; // ecx
  int v8; // eax
  int v9; // ebx
  bool v10; // cl
  int v11; // edi
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int *v15; // ecx
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // edi
  uint32_t *v21; // ebx
  uint8_t v22; // al
  bool v23; // cf
  uint64_t v24; // rax
  int v25; // ebx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  void *v31; // eax
  int v32; // [esp-18h] [ebp-58h]
  int v33; // [esp-14h] [ebp-54h]
  char v34; // [esp-4h] [ebp-44h]
  uint8_t v35[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *Block; // [esp+8h] [ebp-38h]
  uint8_t v37[4]; // [esp+14h] [ebp-2Ch] BYREF
  void *v38; // [esp+18h] [ebp-28h]
  int v39; // [esp+1Ch] [ebp-24h]
  int v40; // [esp+20h] [ebp-20h]
  int v41; // [esp+24h] [ebp-1Ch]
  int v42; // [esp+28h] [ebp-18h]
  int v43; // [esp+2Ch] [ebp-14h]
  uint8_t v44; // [esp+33h] [ebp-Dh]
  int v45; // [esp+3Ch] [ebp-4h]

  if ( *(uint8_t *)(a1 + 97) == 0 && *(uint32_t *)(a1 + 196) < (unsigned int)sub_699000(a1 + 60) )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 4) + 200))(*(uint32_t *)(a1 + 4), a3, a2);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 40))(*(uint32_t *)(a1 + 4), 273) == 0
      || v4 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 688))(*(uint32_t *)(a1 + 4))
      || v4 == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 688))(*(uint32_t *)(a1 + 4)) + 8)
      || v4 == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 688))(*(uint32_t *)(a1 + 4)) + 20)
      || v4 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 1068))(*(uint32_t *)(a1 + 4)) )
    {
      v5 = 1.0;
      v44 = 0;
    }
    else
    {
      v5 = 1.5;
      v44 = 1;
    }
    v41 = (uint64_t)((double)*(int *)(a1 + 200) * v5);
    v42 = 120;
    v43 = 70;
    for ( i = 0; ; ++i )
    {
      v7 = *(int **)(a1 + 20);
      v8 = v7[11];
      if ( v8 != 0 )
        v8 = (v7[12] - v8) / 88;
      if ( i >= v8 )
        break;
      v9 = v44;
      *(uint32_t *)(sub_4924C0(v7, i) + 48) = *(&v42 + v9);
    }
    v10 = dword_8F7C04 == *(uint32_t *)(a1 + 16);
    v11 = *(uint32_t *)(a1 + 4);
    v12 = *(uint32_t *)v11;
    v43 = v11;
    v34 = v10;
    v13 = (*(int (/*thiscall*/ **)(int))(v12 + 192))(v11);
    v33 = v13 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 128))(v11) + 15;
    v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 124))(v11);
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11);
    sub_4D7960(v13, v11, a1, v14, v32, v33, v41, 4, 0, v34);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 308))(*(uint32_t *)(a1 + 4)) != 0 )
    {
      v15 = *(int **)(a1 + 4);
      v16 = *v15;
      v17 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*v15 + 736))(v15, 1, 0);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v16 + 728))(*(uint32_t *)(a1 + 4), v17 - v41);
    }
    v38 = nullptr;
    v39 = 0;
    v40 = 0;
    v18 = *(uint32_t *)(dword_8F7A24 + 244);
    v45 = 0;
    if ( v18 != 0 )
    {
      v19 = v18 - 1;
      if ( v19 != 0 )
      {
        if ( v19 == 1 )
        {
LABEL_28:
          *(uint32_t *)(a1 + 196) = sub_699000(a1 + 60) + 1000;
          (*(void (/*thiscall*/ **)(uint32_t, const char *, int))(**(uint32_t **)(a1 + 4) + 212))(
            *(uint32_t *)(a1 + 4),
            "BLOOD_DROP_LOOP",
            -1);
          if ( v38 != nullptr )
            j__free(v38);
          return;
        }
        v20 = v41;
      }
      else
      {
        v20 = dword_8F82CC;
      }
    }
    else
    {
      v20 = dword_8F82D0;
    }
    if ( v20 != 0 )
    {
      v21 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 36))(v20);
      v22 = v44;
      v23 = v44 != 0;
      v21[4] = 50;
      v21[1] = v23 ? 10 : 3;
      v21[3] = v22 != 0 ? 80 : 30;
      v41 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 192))(*(uint32_t *)(a1 + 4));
      v24 = (uint64_t)((double)v41 * 0.69999999);
      v21[5] = v24;
      if ( (*(int (/*fastcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4), HIDWORD(v24)) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
        v25 = *(uint32_t *)v20;
        v26 = **(uint32_t **)(a1 + 4);
        v43 = *(uint32_t *)(a1 + 4);
        v27 = (*(int (**)(void))(v26 + 128))();
        v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v43 + 124))(v43, v27);
        v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v43 + 120))(v43, v28);
        (*(void (/*thiscall*/ **)(int, int))(v25 + 40))(v20, v29);
        v30 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v20 + 92))(v20, v35);
        LOBYTE(v45) = 1;
        sub_4E77D0((int)v37, v30);
        LOBYTE(v45) = 0;
        if ( Block != nullptr )
          j__free(Block);
        v31 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4));
        sub_4600B0(v31, 2, 0, (int)v37);
      }
    }
    goto LABEL_28;
  }
}


// ------------------------------------------------------------
// 0x5FC900 sub_5FC900
// ------------------------------------------------------------
// 调: sub_5FC900 sub_698FE0 sub_699030 sub_431230 sub_5E5260
void /*thiscall*/ sub_5FC900(int this)
{
  int v2; // edi
  int v3; // eax
  uint8_t v4[4]; // [esp+8h] [ebp-20h] BYREF
  int v5; // [esp+Ch] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]
  uint32_t v8[4]; // [esp+18h] [ebp-10h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4)) == 4 )
  {
    if ( *(uint8_t *)(this + 74) != 0 && *(uint8_t *)(this + 96) == 0 )
      sub_698FE0(this + 60);
  }
  else
  {
    if ( *(uint8_t *)(this + 74) == 0 )
      sub_699030(this + 60);
    v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 568))(*(uint32_t *)(this + 4));
    if ( *(uint8_t *)(this + 97) == 0 && v2 != 3 && v3 != 3 && v2 != 4 && v3 != 4 && v2 != 5 && v3 != 5 )
    {
      v5 = 0;
      v6 = 0;
      v7 = 0;
      v8[3] = 0;
      v8[0] = 4;
      sub_431230(v8);
      v8[0] = 2;
      sub_431230(v8);
      v8[0] = 0;
      sub_431230(v8);
      v8[0] = 0;
      sub_431230(v8);
      v8[0] = 0;
      sub_431230(v8);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(**(uint32_t **)(this + 4) + 560))(
        *(uint32_t *)(this + 4),
        4,
        v4,
        2,
        0);
      sub_5E5260(v4);
    }
  }
}



// ------------------------------------------------------------
// 0x5FCA50 sub_5FCA50
// ------------------------------------------------------------
// 调: sub_5FCA50 sub_699000 sub_497120 sub_41A5E0 sub_433F60
char /*usercall*/ sub_5FCA50@<al>(int a1@<ecx>, double a2@<st0>)
{
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // edi
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // ebx
  int *v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int v20; // edx
  int v21; // ebx
  int v22; // eax
  int v23; // ebx
  int v24; // edi
  int v25; // eax
  int *v26; // ecx
  int v27; // eax
  void *v28; // eax
  bool v29; // zf
  signed int v30; // eax
  int v31; // eax
  const char *v32; // ecx
  int v33; // eax
  int *v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // ebx
  int v38; // eax
  int v39; // edx
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  int v44; // [esp-20h] [ebp-6Ch]
  int v45; // [esp-1Ch] [ebp-68h]
  int v46; // [esp-18h] [ebp-64h]
  int v47; // [esp-14h] [ebp-60h]
  int v48; // [esp-10h] [ebp-5Ch]
  int v49; // [esp-10h] [ebp-5Ch]
  int v50; // [esp-Ch] [ebp-58h]
  int v51; // [esp-Ch] [ebp-58h]
  char v52; // [esp-Ch] [ebp-58h]
  int v53; // [esp-Ch] [ebp-58h]
  void *v54[4]; // [esp+4h] [ebp-48h] BYREF
  float v55; // [esp+14h] [ebp-38h]
  int v56; // [esp+18h] [ebp-34h]
  int v57; // [esp+1Ch] [ebp-30h]
  uint8_t v58[4]; // [esp+20h] [ebp-2Ch] BYREF
  uint32_t v59[7]; // [esp+24h] [ebp-28h] BYREF
  int v60; // [esp+48h] [ebp-4h]

  v59[6] = dword_796E50;
  LOBYTE(v3) = *(uint8_t *)(a1 + 97);
  if ( (uint8_t)v3 == 0 )
  {
    v4 = *(uint32_t *)(a1 + 84);
    if ( sub_699000(a1 + 60) >= v4 )
      v5 = *(uint32_t *)(a1 + 84);
    else
      v5 = sub_699000(a1 + 60);
    v50 = *(uint32_t *)(a1 + 12);
    v48 = *(uint32_t *)(a1 + 8);
    v57 = v5;
    sub_497120(v48, v50);
    v6 = *(uint32_t *)(a1 + 4);
    v56 = (uint64_t)(a2 * (double)v57 * 0.001);
    v7 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)v6 + 672))(
           v6,
           (uint64_t)(a2 * (double)v57 * 0.001) >> 32,
           3);
    v57 = sub_41A5E0(v7 + 312);
    v55 = COERCE_FLOAT(sub_41A5E0(v7 + 536));
    v8 = (uint64_t)((double)v57 * v55);
    if ( v8 < 100 )
    {
      v9 = (100 - v8) * (uint64_t)(sub_433F60(*(uint32_t *)(a1 + 16), 0) * (double)v56);
      v10 = *(uint32_t *)(a1 + 128);
      v11 = v9 / 100;
      v12 = v9 / 100 - v10;
      if ( v9 / 100 != v10 )
      {
        v13 = *(int **)(a1 + 4);
        v51 = *(uint32_t *)(a1 + 16);
        v56 = *v13;
        v14 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v56 + 736))(v13, 0, v51);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v56 + 728))(*(uint32_t *)(a1 + 4), v14 - v12);
        *(uint32_t *)(a1 + 128) = v11;
      }
      if ( *(uint32_t *)(a1 + 140) < (unsigned int)sub_699000(a1 + 60) )
      {
        v15 = *(uint32_t *)(a1 + 136);
        v16 = *(uint32_t *)(a1 + 16);
        v17 = *(uint32_t *)(a1 + 128);
        *(uint32_t *)(a1 + 136) = v17;
        v18 = v17 - v15;
        v19 = *(uint32_t *)(a1 + 4);
        v20 = *(uint32_t *)v19;
        v57 = v19;
        v52 = dword_8F7C04 == v16;
        v46 = v18;
        v21 = (*(int (/*thiscall*/ **)(int))(v20 + 192))(v19);
        v45 = v21 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 128))(v19) + 15;
        v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 124))(v19);
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 120))(v19);
        sub_4D7960(v21, v19, a1, v22, v44, v45, v46, 4, 0, v52);
        *(uint32_t *)(a1 + 140) = sub_699000(a1 + 60) + 500;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 940))(*(uint32_t *)(a1 + 4)) == 0
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4)) != 0 )
      {
        v23 = **(uint32_t **)(a1 + 40);
        v24 = *(uint32_t *)(a1 + 4);
        v25 = *(uint32_t *)v24;
        v57 = v24;
        v53 = (*(int (**)(void))(v25 + 128))() + 70;
        v49 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 124))(v24);
        v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 120))(v24);
        (*(void (/*thiscall*/ **)(uint32_t))(v23 + 40))(*(uint32_t *)(a1 + 40));
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(a1 + 40) + 92))(*(uint32_t *)(a1 + 40), v54);
        v26 = *(int **)(a1 + 4);
        v27 = *v26;
        v60 = 0;
        v28 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v27 + 80))(v26, 2, 0, v54);
        sub_4600B0(v28, v47, v49, v53);
        v60 = -1;
        sub_5E5260(v54);
      }
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 28))(a1);
      if ( v3 >= *(uint32_t *)(a1 + 132) + 300 )
      {
        if ( rand() % 5 == 0 && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4)) != 0 )
        {
          sub_401710("Common/ActiveStatus/Animation/");
          v60 = 1;
          v30 = rand() & 0x80000001;
          v29 = v30 == 0;
          if ( v30 < 0 )
            v29 = (((uint8_t)v30 - 1) | 0xFFFFFFFE) == -1;
          if ( v29 )
            sub_402410("PoisonFloor1.ani");
          else
            sub_402410("PoisonFloor2.ani");
          v56 = sub_44B6C0(284);
          LOBYTE(v60) = 2;
          if ( v56 != 0 )
          {
            v31 = sub_42FCB0(228);
            v55 = *(float *)&v31;
            LOBYTE(v60) = 3;
            if ( v31 != 0 )
            {
              v32 = (const char *)v59[0];
              if ( v59[5] < 0x10u )
                v32 = (const char *)v59;
              v33 = sub_431860(v31, v32, 1);
              LOBYTE(v60) = 2;
              v34 = (int *)sub_44E1F0(v33, 1);
            }
            else
            {
              LOBYTE(v60) = 2;
              v34 = (int *)sub_44E1F0(0, 1);
            }
          }
          else
          {
            v34 = nullptr;
          }
          v35 = *v34;
          LOBYTE(v60) = 1;
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v35 + 36))(v34) + 8) = 2;
          v36 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4));
          sub_45FE80(v36, (int)v34, 2, 0, (int)v34, 0, 0);
          v37 = *v34;
          v38 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 152))(*(uint32_t *)(a1 + 4));
          (*(void (/*thiscall*/ **)(int *, int))(v37 + 148))(v34, v38);
          v39 = **(uint32_t **)(a1 + 4);
          v40 = *v34;
          v57 = *(uint32_t *)(a1 + 4);
          v41 = (*(int (/*stdcall*/ **)(uint32_t))(v39 + 124))(0);
          v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v57 + 120))(v57, v41);
          (*(void (/*thiscall*/ **)(int *, int))(v40 + 112))(v34, v42);
          v60 = -1;
          sub_501490(v58);
        }
        v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 28))(a1);
        *(uint32_t *)(a1 + 132) = v3;
      }
    }
    else
    {
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1 + 4))(a1, 0, 0);
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x5FCE10 sub_5FCE10
// ------------------------------------------------------------
// 证: "Common/ActiveStatus/Animation/FreezeDie.ani" | "FROZEN_DIE"
// 调: sub_5FCE10 sub_42FCB0 sub_431860 sub_4920E0 sub_44B6C0
void /*userpurge*/ sub_5FCE10(int a1@<ecx>, int a2@<ebx>, int a3@<edi>, char a4)
{
  uint32_t *v5; // ebx
  char *v6; // eax
  char *v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // ebx
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  char *v23; // edi
  uint32_t *v24; // eax
  void *v25; // eax
  int v26; // [esp+24h] [ebp-34h]
  int v27; // [esp+2Ch] [ebp-2Ch]
  float v28; // [esp+2Ch] [ebp-2Ch]
  int v29; // [esp+30h] [ebp-28h]
  float v30; // [esp+30h] [ebp-28h]
  int v31; // [esp+34h] [ebp-24h]
  char v32[4]; // [esp+38h] [ebp-20h] BYREF
  void *Block; // [esp+3Ch] [ebp-1Ch]
  char *v34; // [esp+40h] [ebp-18h]
  int *v35; // [esp+48h] [ebp-10h]
  int v36; // [esp+54h] [ebp-4h]
  int *v37; // [esp+60h] [ebp+8h]
  int *v38; // [esp+60h] [ebp+8h]

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4)) != 0 )
  {
    v29 = a2;
    v27 = a3;
    if ( a4 != 0 )
    {
      v5 = nullptr;
      v36 = 0;
      if ( sub_42FCB0(228) != 0 )
        v5 = (uint32_t *)sub_431860((char)"Common/ActiveStatus/Animation/FreezeDie.ani", 1);
      sub_4920E0(v5, *(float *)(a1 + 108), *(float *)(a1 + 112));
      v6 = (char *)sub_44B6C0(284);
      v7 = v6;
      v36 = 1;
      if ( v6 != nullptr )
      {
        sub_44E0D0(v6, (int)v5, 1);
        *(uint32_t *)v7 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = nullptr;
      }
      v8 = **(uint32_t **)(a1 + 4);
      v26 = *(uint32_t *)(a1 + 4);
      v36 = -1;
      v9 = (*(int (**)(void))(v8 + 80))();
      sub_45FE80(v9, (int)v7, 2, 0, (int)v7, v26, 0);
      v10 = *(uint32_t *)v7;
      v11 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 4) + 152))(*(uint32_t *)(a1 + 4), v27, v29);
      (*(void (/*thiscall*/ **)(char *, int))(v10 + 148))(v7, v11);
      v12 = *(uint32_t *)v7;
      v37 = *(int **)(a1 + 4);
      v13 = *v37;
      v35 = v37;
      v14 = (*(int (**)(void))(v13 + 128))();
      v15 = (*(int (/*thiscall*/ **)(int *, int))(*v37 + 124))(v37, v14);
      v16 = (*(int (/*thiscall*/ **)(int *, int))(*v35 + 120))(v35, v15);
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 112))(v7, v16);
    }
    v17 = dword_8F82BC;
    v18 = *(uint32_t *)dword_8F82BC;
    v38 = *(int **)(a1 + 4);
    v19 = *v38;
    v35 = v38;
    v20 = (*(int (/*stdcall*/ **)(int, int))(v19 + 128))(v27, v29);
    v21 = (*(int (/*thiscall*/ **)(int *, int))(*v38 + 124))(v38, v20 + 50);
    v22 = (*(int (/*thiscall*/ **)(int *, int))(*v35 + 120))(v35, v21);
    (*(void (/*thiscall*/ **)(int, int))(v18 + 40))(v17, v22);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v17 + 12))(v17, 0);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v17 + 92))(v17, v32);
    v23 = (char *)Block;
    v36 = 2;
    if ( Block != v34 )
    {
      do
      {
        v30 = *(float *)(a1 + 112) * 1.5;
        v28 = *(float *)(a1 + 108) * 1.5;
        v24 = (uint32_t *)(*(int (**)(void))(**(uint32_t **)v23 + 96))();
        sub_4920E0(v24, v28, v30);
        v23 += 4;
      }
      while ( v23 != v34 );
    }
    v25 = (void *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4), 2);
    sub_4600B0(v25, 0, (int)v32, v31);
    (*(void (/*thiscall*/ **)(uint32_t, const char *))(**(uint32_t **)(a1 + 4) + 212))(*(uint32_t *)(a1 + 4), "FROZEN_DIE");
    if ( Block != nullptr )
      j__free(Block);
  }
}


// ------------------------------------------------------------
// 0x5FD010 CNRDActiveStatus__vmt2C
// ------------------------------------------------------------
// 调: sub_5FABA0 sub_5FCA50 sub_698FE0 sub_699030 sub_4600B0
char /*usercall*/ sub_5FD010@<al>(int a1@<ecx>, int a2@<ebx>)
{
  bool v3; // zf
  char v4; // al
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // edx
  int *v10; // ecx
  int v11; // edx
  void *v12; // eax
  int i; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int *v18; // ecx
  int v19; // eax
  void *v20; // eax
  int v21; // edi
  int v22; // eax
  int v24; // [esp-10h] [ebp-48h]
  int v25; // [esp-Ch] [ebp-44h]
  int v26; // [esp-8h] [ebp-40h]
  int v27; // [esp-8h] [ebp-40h]
  uint8_t v29[16]; // [esp+8h] [ebp-30h] BYREF
  uint8_t v30[16]; // [esp+18h] [ebp-20h] BYREF
  int v31; // [esp+28h] [ebp-10h]
  int v32; // [esp+34h] [ebp-4h]

  switch ( *(uint32_t *)(a1 + 8) )
  {
    case 1:
      sub_5FABA0(a1);
      break;
    case 2:
      sub_5FCA50(a1);
      break;
    case 3:
      v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 840))(*(uint32_t *)(a1 + 4)) == 9;
      v4 = *(uint8_t *)(a1 + 74);
      if ( v3 )
      {
        if ( v4 != 0 && *(uint8_t *)(a1 + 96) == 0 )
        {
          sub_698FE0(a1 + 60);
          *(uint8_t *)(a1 + 204) = 1;
        }
      }
      else
      {
        if ( v4 == 0 && *(uint8_t *)(a1 + 204) == 0 )
          sub_699030(a1 + 60);
        v5 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 840))(*(uint32_t *)(a1 + 4));
        v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 568))(*(uint32_t *)(a1 + 4));
        if ( *(uint8_t *)(a1 + 97) == 0 && v5 != 3 && v6 != 3 && v5 != 4 && v6 != 4 && v5 != 5 && v6 != 5 && v6 != 9 )
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 560))(
            *(uint32_t *)(a1 + 4),
            9,
            0,
            0,
            0);
      }
      break;
    case 4:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 940))(*(uint32_t *)(a1 + 4)) == 0
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4)) != 0 )
      {
        v7 = **(uint32_t **)(a1 + 40);
        v8 = *(uint32_t *)(a1 + 4);
        v9 = *(uint32_t *)v8;
        v31 = v8;
        v26 = (*(int (/*thiscall*/ **)(int))(v9 + 128))(v8) + 70;
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 124))(v8);
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 120))(v8);
        (*(void (/*thiscall*/ **)(uint32_t))(v7 + 40))(*(uint32_t *)(a1 + 40));
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(a1 + 40) + 92))(*(uint32_t *)(a1 + 40), v30);
        v10 = *(int **)(a1 + 4);
        v11 = *v10;
        v32 = 0;
        v12 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v11 + 80))(v10, 2, 0, v30);
        sub_4600B0(v12, v24, v25, v26);
        v32 = -1;
        sub_5E5260(v30);
      }
      break;
    case 7:
      sub_5FBE20(a1);
      break;
    case 8:
      sub_5FC900(a1);
      break;
    case 9:
      sub_5FC450(a1);
      break;
    case 0xB:
      sub_5FC610(a1);
      break;
    case 0xD:
      if ( *(uint8_t *)(a1 + 97) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 940))(*(uint32_t *)(a1 + 4)) == 0
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4)) != 0 )
      {
        for ( i = 0; i < 2; ++i )
        {
          v14 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 120))(*(uint32_t *)(a1 + 4), a2);
          v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 124))(*(uint32_t *)(a1 + 4));
          v16 = *(uint32_t *)(a1 + 4);
          v31 = v15;
          if ( i != 0 )
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 128))(v16);
          else
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 128))(v16) + 50;
          a2 = v17;
          v27 = v31;
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4 * i + 40) + 40))(*(uint32_t *)(a1 + 4 * i + 40));
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4 * i + 40) + 92))(*(uint32_t *)(a1 + 4 * i + 40));
          v18 = *(int **)(a1 + 4);
          v19 = *v18;
          v32 = 1;
          v20 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v19 + 80))(v18, 2, 0, v29);
          sub_4600B0(v20, (int)v29, v14, v27);
          v32 = -1;
          sub_5E5260(v29);
        }
      }
      break;
    default:
      break;
  }
  v21 = *(uint32_t *)(a1 + 84);
  v22 = sub_699000(a1 + 60);
  if ( v22 >= v21 )
  {
    LOBYTE(v22) = *(uint8_t *)(a1 + 97);
    if ( (uint8_t)v22 == 0 )
      LOBYTE(v22) = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 764))(
                      *(uint32_t *)(a1 + 4),
                      *(uint32_t *)(a1 + 8),
                      0,
                      0,
                      0);
  }
  return v22;
}


// ------------------------------------------------------------
// 0x5FD310 CNRDActiveStatus__vmt40
// ------------------------------------------------------------
// 证: "CONDITION_REMOVE"
// 调: sub_5FCE10 sub_5FC2F0 sub_431230 sub_5E5260
void /*usercall*/ CNRDActiveStatus__vmt40(int a1@<ecx>, int a2@<ebx>)
{
  void *v3[4]; // [esp+8h] [ebp-20h] BYREF
  uint32_t v4[4]; // [esp+18h] [ebp-10h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 212))(
    *(uint32_t *)(a1 + 4),
    "CONDITION_REMOVE",
    -1,
    0,
    0);
  switch ( *(uint32_t *)(a1 + 8) )
  {
    case 1:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 848))(*(uint32_t *)(a1 + 4), 0);
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 840))(*(uint32_t *)(a1 + 4)) == 9 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 560))(
          *(uint32_t *)(a1 + 4),
          0,
          0,
          0,
          0);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(a1 + 4) + 252))(*(uint32_t *)(a1 + 4), 0, -1);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 4) + 252))(*(uint32_t *)(a1 + 4), 1, -1);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 4) + 252))(*(uint32_t *)(a1 + 4), 2, -1);
      if ( *(uint32_t *)(a1 + 88) <= *(uint32_t *)(a1 + 92) >> 1 )
        sub_5FCE10(a1, a2, 0, 1);
      else
        sub_5FCE10(a1, a2, 0, 0);
      break;
    case 2:
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 216))(*(uint32_t *)(a1 + 4), 2);
      break;
    case 3:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 848))(*(uint32_t *)(a1 + 4), 0);
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 840))(*(uint32_t *)(a1 + 4)) == 9 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 560))(
          *(uint32_t *)(a1 + 4),
          0,
          0,
          0,
          0);
      break;
    case 6:
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 216))(*(uint32_t *)(a1 + 4), 4);
      break;
    case 7:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 848))(*(uint32_t *)(a1 + 4), 0);
      sub_5FC2F0(a1);
      break;
    case 8:
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 840))(*(uint32_t *)(a1 + 4)) == 4 )
      {
        memset(&v3[1], 0, 12);
        v4[0] = 4;
        v4[3] = 0;
        sub_431230((int)v3, v4);
        v4[0] = 2;
        sub_431230((int)v3, v4);
        v4[0] = 0;
        sub_431230((int)v3, v4);
        v4[0] = 0;
        sub_431230((int)v3, v4);
        v4[0] = 0;
        sub_431230((int)v3, v4);
        (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(a1 + 4) + 560))(
          *(uint32_t *)(a1 + 4),
          4,
          v3,
          2,
          0);
        sub_5E5260(v3);
      }
      break;
    case 9:
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 216))(*(uint32_t *)(a1 + 4), 3);
      break;
    case 0xB:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 4) + 208))(*(uint32_t *)(a1 + 4), *(uint32_t *)(a1 + 20));
      break;
    case 0x10:
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 216))(*(uint32_t *)(a1 + 4), 40100);
      break;
    default:
      return;
  }
}



// ------------------------------------------------------------
// 0x5FD5C0 CNRDActiveStatus__vmt44
// ------------------------------------------------------------
// 调: sub_5FC010 sub_5FCE10
int /*usercall*/ CNRDActiveStatus__vmt44@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax

  v4 = *(uint32_t *)(a1 + 8) - 1;
  *(uint8_t *)(a1 + 97) = 1;
  if ( v4 != 0 )
  {
    if ( v4 == 6 )
    {
      sub_5FC010(a1);
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1 + 4))(a1, 0, 0);
    }
  }
  else
  {
    sub_5FCE10(a1, a2, a3, 1);
  }
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1 + 4))(a1, 0, 0);
}



// ------------------------------------------------------------
// 0x5FD600 sub_5FD600
// ------------------------------------------------------------
// 调: sub_5FD600
int /*thiscall*/ sub_5FD600(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint8_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 1;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FD630 sub_5FD630
// ------------------------------------------------------------
// 调: sub_5FD630
int /*thiscall*/ sub_5FD630(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
}



// ------------------------------------------------------------
// 0x5FD640 CNChangeHp__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（10 行，无外调无字符串）
char /*thiscall*/ CNChangeHp__vmt78(int this, int a2, int a3, char a4, int a5)
{
  *(uint32_t *)(this + 80) = a2;
  *(uint32_t *)(this + 84) = a3;
  *(uint8_t *)(this + 88) = a4;
  *(uint32_t *)(this + 100) = a5;
  *(uint8_t *)(this + 96) = 0;
  return a4;
}



// ------------------------------------------------------------
// 0x5FD670 CNChangeHp__vmt20
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
char /*thiscall*/ CNChangeHp__vmt20(uint32_t **this, char a2)
{
  char result; // al

  result = a2;
  if ( a2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 8);
  return result;
}



// ------------------------------------------------------------
// 0x5FD690 CNChangeHp__vmt54
// ------------------------------------------------------------
// 调: sub_4939E0
char /*thiscall*/ CNChangeHp__vmt54(int this, char a2)
{
  char result; // al
  int v4; // ecx

  result = IRDAppendage__vmt54((uint8_t *)this, a2);
  v4 = *(uint32_t *)(this + 116);
  if ( v4 != 0 )
    return sub_4939E0(v4, a2);
  return result;
}



// ------------------------------------------------------------
// 0x5FD6C0 CNChangeHp__vmt14
// ------------------------------------------------------------
// 调: sub_4938F0 sub_491D00 sub_699000 sub_491690
uint32_t **/*thiscall*/ CNChangeHp__vmt14(int this, char a2, int a3, int a4, int a5)
{
  uint32_t **result; // eax
  int v7; // ecx
  uint64_t v8; // rax
  uint32_t **v9; // ebx
  int v10; // edi
  uint32_t *v11; // esi
  float v12; // [esp+14h] [ebp+10h]

  result = *(uint32_t ***)(this + 100);
  if ( a2 != 0 )
  {
    if ( result == (uint32_t **)1 )
    {
      v7 = *(uint32_t *)(this + 116);
      if ( v7 != 0 )
      {
        sub_4938F0(v7);
        v12 = (float)a4;
        v8 = (uint64_t)(v12
                              - (double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                              * 0.60000002);
        return (uint32_t **)sub_491D00(dword_79C0B0, a3, v8, 0.0);
      }
    }
  }
  else if ( result == (uint32_t **)2 )
  {
    result = (uint32_t **)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
    v9 = result;
    if ( result != nullptr )
    {
      v10 = ((uint8_t)(((sub_699000(this + 8) / 0x50u) & 1) != 0 ? -78 : 80) << 24) | 0xFFFFFF;
      sub_491690(1, 2, 1, -13487361, v10, 1);
      result = (uint32_t **)v9[51];
      v11 = *result;
      if ( *result != result )
      {
        do
        {
          result = (uint32_t **)sub_491690(1, 2, 1, -13487361, v10, 1);
          v11 = (uint32_t *)*v11;
        }
        while ( v11 != v9[51] );
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FD7C0 CNChangeHp__vmt4
// ------------------------------------------------------------
// 调: sub_433F60 sub_699000
void /*usercall*/ sub_5FD7C0(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  double v4; // st7
  double v5; // st7
  int v6; // eax
  int v7; // ecx
  char *v8; // eax
  int v9; // ecx
  int v10; // eax
  int *v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int *v18; // ecx
  int v19; // edx
  char *v20; // eax
  int v21; // edi
  int v22; // ebx
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  double v26; // st7
  int v27; // eax
  uint64_t v28; // rax
  int v29; // ecx
  void **v30; // ebx
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // edi
  int v36; // ebx
  int v37; // edx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int *v41; // ecx
  int v42; // eax
  void *v43; // eax
  int v44; // eax
  int *v45; // ecx
  int v46; // edx
  char *v47; // eax
  int v48; // edi
  int v49; // ebx
  int v50; // ebx
  int *v51; // ecx
  int v52; // edx
  void *v53; // eax
  void *v54; // eax
  uint32_t *v55; // edi
  int v56; // eax
  int v57; // ecx
  int v58; // eax
  double v59; // st7
  int v60; // eax
  int v61; // eax
  double v62; // st7
  int v63; // ecx
  int v64; // edi
  int v65; // eax
  int v66; // eax
  int v67; // eax
  float v68; // [esp+1Ch] [ebp-58h]
  float v69; // [esp+20h] [ebp-54h]
  int v70; // [esp+20h] [ebp-54h]
  float v71; // [esp+20h] [ebp-54h]
  int v72; // [esp+24h] [ebp-50h]
  int v75; // [esp+34h] [ebp-40h]
  void *v76[4]; // [esp+38h] [ebp-3Ch] BYREF
  char v77[4]; // [esp+48h] [ebp-2Ch] BYREF
  void *Block; // [esp+4Ch] [ebp-28h]
  char *v79; // [esp+50h] [ebp-24h]
  int v80; // [esp+54h] [ebp-20h]
  float v81; // [esp+58h] [ebp-1Ch]
  char *v82; // [esp+5Ch] [ebp-18h]
  float i; // [esp+60h] [ebp-14h]
  int v84; // [esp+64h] [ebp-10h]
  int v85; // [esp+70h] [ebp-4h]

  sub_5F66C0();
  if ( *(uint8_t *)(a1 + 96) == 0 && *(uint8_t *)(a1 + 88) != 0 )
  {
    if ( *(float *)(a1 + 80) <= 0.0 )
      v4 = sub_433F60(*(uint32_t *)(a1 + 36), 0);
    else
      v4 = sub_433F60(*(uint32_t *)(a1 + 4), 2);
    v5 = v4 * *(float *)(a1 + 80);
    *(uint8_t *)(a1 + 96) = 1;
    *(float *)(a1 + 80) = v5;
  }
  if ( *(uint8_t *)(a1 + 104) != 0 )
  {
    if ( *(uint32_t *)(a1 + 84) == -1 )
    {
      if ( sub_699000(a1 + 8) >= *(uint32_t *)(a1 + 112) + 500 )
      {
        v6 = *(uint32_t *)(a1 + 92);
        v7 = *(uint32_t *)(a1 + 108);
        if ( v6 != v7 )
        {
          v8 = (char *)(v6 - v7);
          v9 = *(uint32_t *)(a1 + 4);
          v82 = v8;
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9);
          v11 = *(int **)(a1 + 4);
          v12 = *v11;
          v84 = v10;
          v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 124))(v11);
          v14 = *(uint32_t *)(a1 + 4);
          i = *(float *)&v13;
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 128))(v14);
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 192))(v14);
          sub_4D7960(
            v16 + v15,
            v14,
            a1,
            v84,
            SLODWORD(i),
            v16 + v15,
            (int)v82,
            2 * ((int)v82 <= 0) + 2,
            0,
            dword_8F7C04 == *(uint32_t *)(a1 + 36));
          *(uint32_t *)(a1 + 108) = *(uint32_t *)(a1 + 92);
          *(uint32_t *)(a1 + 112) = sub_699000(a1 + 8);
        }
      }
    }
    else if ( *(uint32_t *)(a1 + 112) == 0 )
    {
      v17 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 120))(*(uint32_t *)(a1 + 4));
      v18 = *(int **)(a1 + 4);
      v19 = *v18;
      i = *(float *)&v17;
      v20 = (char *)(*(int (/*thiscall*/ **)(int *))(v19 + 124))(v18);
      v21 = *(uint32_t *)(a1 + 4);
      v82 = v20;
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 128))(v21);
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 192))(v21) + v22;
      v24 = 2;
      if ( *(float *)(a1 + 80) <= 0.0 )
        v24 = 1;
      sub_4D7960(v23, v21, a1, SLODWORD(i), (int)v82, v23, (uint64_t)*(float *)(a1 + 80), v24, 0, 0);
      *(uint32_t *)(a1 + 112) = 1;
    }
  }
  v25 = *(uint32_t *)(a1 + 84);
  if ( v25 == -1 )
  {
    v82 = (char *)sub_699000(a1 + 8);
    v26 = (double)(int)v82 * *(float *)(a1 + 80) * 0.001;
  }
  else if ( v25 != 0 )
  {
    v27 = sub_699000(a1 + 8);
    v82 = (char *)(uint64_t)*(float *)(a1 + 80);
    v69 = (float)(int)v82;
    v26 = sub_4049C0(0.0, v69, v27, v25);
  }
  else
  {
    v26 = *(float *)(a1 + 80);
  }
  v28 = (uint64_t)v26;
  v29 = *(uint32_t *)(a1 + 92);
  if ( (unsigned int)(uint64_t)v26 != v29 )
  {
    v30 = *(void ***)(a1 + 4);
    HIDWORD(v28) = *(uint32_t *)(a1 + 36);
    *(uint32_t *)(a1 + 92) = v28;
    v31 = v28 - v29;
    v82 = (char *)*v30;
    v32 = (*((int (/*thiscall*/ **)(void **, uint32_t, uint32_t))v82 + 184))(v30, 0, HIDWORD(v28));
    (*((void (/*thiscall*/ **)(void **, int))v82 + 182))(v30, v31 + v32);
  }
  v33 = *(uint32_t *)(a1 + 100);
  if ( v33 == 1 )
  {
    v34 = *(uint32_t *)(a1 + 116);
    if ( v34 != 0 && *(int *)(v34 + 148) >= 4 && *(uint8_t *)(a1 + 120) == 0 )
    {
      v35 = dword_8F82B4;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B4 + 12))(dword_8F82B4, 0);
      v36 = *(uint32_t *)v35;
      v37 = **(uint32_t **)(a1 + 4);
      v84 = *(uint32_t *)(a1 + 4);
      v38 = (*(int (**)(void))(v37 + 128))();
      v39 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v84 + 124))(v84, v38 + 60);
      v40 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v84 + 120))(v84, v39);
      (*(void (/*thiscall*/ **)(int, int))(v36 + 40))(v35, v40);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v35 + 92))(v35, v76);
      v41 = *(int **)(a1 + 4);
      v42 = *v41;
      v85 = 0;
      v43 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v42 + 80))(v41, 2, 0, v76);
      sub_4600B0(v43, a3, a2, v75);
      (*(void (/*thiscall*/ **)(uint32_t, const char *))(**(uint32_t **)(a1 + 4) + 212))(*(uint32_t *)(a1 + 4), "HP_RECOVERED");
      *(uint8_t *)(a1 + 120) = 1;
      v85 = -1;
      sub_5E5260(v76);
    }
  }
  else if ( v33 == 2 )
  {
    v44 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 120))(*(uint32_t *)(a1 + 4));
    v45 = *(int **)(a1 + 4);
    v46 = *v45;
    v84 = v44;
    v47 = (char *)(*(int (/*thiscall*/ **)(int *))(v46 + 124))(v45);
    v48 = *(uint32_t *)(a1 + 4);
    v82 = v47;
    v49 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v48 + 192))(v48) / 2;
    v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v48 + 128))(v48) + v49;
    v72 = (int)v82;
    v70 = v84;
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 124) + 40))(*(uint32_t *)(a1 + 124));
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(a1 + 124) + 92))(*(uint32_t *)(a1 + 124), v77);
    v51 = *(int **)(a1 + 4);
    v52 = *v51;
    v85 = 1;
    v53 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v52 + 80))(v51, 2, 0, v77);
    sub_4600B0(v53, v70, v72, v50);
    v54 = Block;
    v55 = Block;
    v82 = (char *)Block;
    if ( Block != v79 )
    {
      while ( 1 )
      {
        v56 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v55 + 128))(*v55);
        v57 = *v55;
        if ( v56 <= v50 )
        {
          v60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v57 + 120))(v57);
          v59 = v60 <= v84 ? 1.3 : -1.3;
        }
        else
        {
          v58 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v57 + 120))(v57);
          v59 = v58 <= v84 ? 0.5 : -0.5;
        }
        i = v59;
        v61 = rand();
        v71 = i + 0.5;
        v68 = i - 0.5;
        v62 = sub_4049C0(v68, v71, v61 % 100, 99);
        v63 = *v55;
        v81 = v62;
        v64 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v63 + 96))(v63);
        for ( i = 0.0; ; ++LODWORD(i) )
        {
          v65 = *(uint32_t *)(v64 + 44);
          if ( v65 != 0 )
            v65 = (*(uint32_t *)(v64 + 48) - v65) / 88;
          if ( SLODWORD(i) >= v65 )
            break;
          v66 = sub_4924C0(LODWORD(i));
          *(float *)(v66 + 28) = v81;
        }
        v82 += 4;
        if ( v82 == v79 )
          break;
        v55 = v82;
      }
      v54 = Block;
    }
    v85 = -1;
    if ( v54 != nullptr )
      j__free(v54);
    Block = nullptr;
    v79 = nullptr;
    v80 = 0;
  }
  if ( *(uint32_t *)(a1 + 84) != -1
    && *(uint32_t *)(a1 + 92) == (uint64_t)*(float *)(a1 + 80)
    && (*(uint32_t *)(a1 + 100) != 1 || (v67 = *(uint32_t *)(a1 + 116)) == 0 || *(uint8_t *)(v67 + 170) != 0) )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 76))(a1, 0);
  }
}


// ------------------------------------------------------------
// 0x5FDC90 sub_5FDC90
// ------------------------------------------------------------
// 调: sub_5FDC90 sub_42AF90 sub_657740
int /*thiscall*/ sub_5FDC90(int this)
{
  int v2; // edi
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = *(uint32_t *)(this + 116);
  if ( v2 != 0 )
  {
    sub_42AF90(*(void ***)(this + 116));
    result = sub_657740(v2, 228);
  }
  v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 124);
  *(uint32_t *)(this + 116) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(uint32_t *)(this + 124) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5FDCE0 CNChangeHp__vmt1C
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/Heal.ani" | "Character/Swordman/Effect/Particle/DOTAreaDa"
// 调: sub_42FCB0 sub_431860 sub_4926A0 sub_428F30 sub_4924C0
void /*usercall*/ CNChangeHp__vmt1C(int a1@<ecx>, int a2@<edi>)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // edi
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int v20; // eax
  BOOL v22; // [esp-4h] [ebp-1Ch]
  void *Block; // [esp+8h] [ebp-10h]
  void *Blocka; // [esp+8h] [ebp-10h]

  v3 = *(uint32_t *)(a1 + 100);
  *(uint32_t *)(a1 + 92) = 0;
  *(uint8_t *)(a1 + 104) = 1;
  *(uint32_t *)(a1 + 108) = 0;
  *(uint32_t *)(a1 + 112) = 0;
  if ( v3 == 1 && *(float *)(a1 + 80) <= 0.0 )
    *(uint32_t *)(a1 + 100) = 0;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && dword_8F7C04 != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 376))(*(uint32_t *)(a1 + 4));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v4 )
    {
      if ( *(uint32_t *)(a1 + 100) == 1 )
        *(uint32_t *)(a1 + 100) = 0;
      if ( *(float *)(a1 + 80) > 0.0 )
        *(uint8_t *)(a1 + 104) = 0;
    }
  }
  v5 = *(uint32_t *)(a1 + 100);
  if ( v5 == 1 )
  {
    if ( *(uint32_t *)(a1 + 116) == 0 )
    {
      v6 = sub_42FCB0(228);
      if ( v6 != 0 )
        v7 = sub_431860(v6, "Common/CommonEffect/Animation/Heal.ani", 1);
      else
        v7 = 0;
      *(uint32_t *)(a1 + 116) = v7;
    }
    sub_4926A0(*(uint32_t *)(a1 + 116));
    *(uint8_t *)(a1 + 120) = 0;
  }
  else if ( v5 == 2 )
  {
    if ( *(uint32_t *)(a1 + 124) == 0 )
    {
      v8 = operator new(0x12Cu);
      if ( v8 != nullptr )
        v9 = sub_428F30(v8, (int)"Character/Swordman/Effect/Particle/DOTAreaDamage.ptl", 0);
      else
        v9 = nullptr;
      *(uint32_t *)(a1 + 124) = v9;
    }
    v10 = *(uint32_t *)(a1 + 124);
    Block = (void *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 192))(*(uint32_t *)(a1 + 4), a2);
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 36))(v10) + 20) = Block;
    v11 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 688))(*(uint32_t *)(a1 + 4));
    if ( v11 != 0 )
    {
      v12 = *(uint32_t *)(v11 + 44);
      if ( v12 != 0 && (*(uint32_t *)(v11 + 48) - v12) / 88 > 0 )
      {
        v13 = sub_4924C0(0);
        Blocka = (void *)sub_4918E0(v13, 1);
        v14 = sub_4924C0(0);
        v22 = sub_4918E0(v14, 0) <= (int)Blocka;
        v15 = sub_4924C0(0);
        v16 = 2 * sub_4918E0(v15, v22);
        *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 124) + 36))(*(uint32_t *)(a1 + 124)) + 12) = v16;
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 124) + 12))(*(uint32_t *)(a1 + 124), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(a1 + 124) + 112))(*(uint32_t *)(a1 + 124), *(uint32_t *)(a1 + 4));
  }
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && *(float *)(a1 + 80) > 0.0 )
  {
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 64))(a1);
    v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v17 + 32) + 576))(*(uint32_t *)(v17 + 32));
    if ( __RTDynamicCast(v18, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) == dword_8F7C04 )
    {
      v19 = *(uint32_t *)(a1 + 4);
      if ( v19 != dword_8F7C04 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v19 + 40))(v19, 273) != 0 )
      {
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        sub_496010((int)dword_99FD58, v20, 11, 1);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5FDF60 CNMovementController__vmt4
// ------------------------------------------------------------
// 证: 叶子函数（32 行，无外调无字符串）
int /*thiscall*/ CNMovementController__vmt4(int this)
{
  int result; // eax
  int v3; // eax

  IRDAppendage__vmt4((int *)this);
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 840))(*(uint32_t *)(this + 4));
  if ( result == 0 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(this + 4) + 6608);
    if ( v3 > *(uint32_t *)(this + 92) || v3 < *(uint32_t *)(this + 88) )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 876))(
        *(uint32_t *)(this + 4),
        0,
        *(uint32_t *)(*(uint32_t *)(this + 4) + 6608),
        *(uint32_t *)(*(uint32_t *)(this + 4) + 6608),
        0,
        0,
        1);
    result = *(uint32_t *)(*(uint32_t *)(this + 4) + 6612);
    if ( result > *(uint32_t *)(this + 92) || result < *(uint32_t *)(this + 88) )
      return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 4) + 876))(
               *(uint32_t *)(this + 4),
               1,
               *(uint32_t *)(*(uint32_t *)(this + 4) + 6612),
               *(uint32_t *)(*(uint32_t *)(this + 4) + 6612),
               0,
               0,
               1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FDFE0 sub_5FDFE0
// ------------------------------------------------------------
// 调: sub_5FDFE0
int /*usercall*/ sub_5FDFE0@<eax>(int *a1@<ecx>, int a2@<ebx>)
{
  uint32_t *v3; // esi
  int v4; // eax
  int result; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // ebx
  int v15; // eax

  v3 = (uint32_t *)__RTDynamicCast(
                   a1[1],
                   0,
                   &IRDActiveObject `RTTI Type Descriptor',
                   &IRDMonster `RTTI Type Descriptor',
                   0);
  a1[22] = 50 * v3[1652] / 100;
  a1[23] = 120 * v3[1652] / 100;
  v4 = v3[1652] / 3;
  a1[20] = v4;
  a1[21] = 2 * v4;
  result = v3[1787];
  if ( result != 4 && result != 13 && result != 1 )
  {
    v6 = *v3;
    if ( result == 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 1032))(v3);
      if ( *(uint32_t *)(result + 20) != 0 )
      {
        v7 = *v3;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v3 + 1032))(v3, a2);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 156))(v3, *(uint32_t *)(v8 + 20));
        v10 = *v3;
        v11 = v9 + 1;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 1032))(v3);
        v13 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v10 + 160))(v3, *(uint32_t *)(v12 + 20)) + 1;
        if ( v11 <= v13 )
        {
          v14 = 114;
          v15 = 114 * v11 / v13;
        }
        else
        {
          v14 = 143 * v13 / v11;
          v15 = 143;
        }
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t))(*v3 + 876))(v3, 0, v15, v15, 0, 0);
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, uint32_t, uint32_t, uint32_t))(*v3 + 876))(
                 v3,
                 1,
                 v14,
                 v14,
                 0,
                 0,
                 0);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v6 + 876))(
        v3,
        0,
        v3[1652],
        v3[1652],
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*v3 + 876))(
               v3,
               1,
               v3[1653],
               v3[1653],
               0,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FE170 CNSpeedControl__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNSpeedControl__vmtC(int *this, int a2)
{
  unsigned int v4; // edi
  int v5; // edx
  int v6; // edx
  float v8; // [esp+Ch] [ebp-4h]
  float v9; // [esp+Ch] [ebp-4h]
  int v10; // [esp+18h] [ebp+8h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = a2 + 830;
  v8 = (double)*(this + 20) * 0.001;
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(a2 + 830)) + v8;
  sub_41A590(v4, v5, v10);
  v9 = (double)*(this + 21) * 0.001;
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v9;
  return sub_41A590(a2 + 858, v6, v11);
}



// ------------------------------------------------------------
// 0x5FE1F0 CNAuraBoss__vmt1C
// ------------------------------------------------------------
// 证: "Common/Etc/Animation/Aura/BossAuraMaster.ani"
int /*thiscall*/ CNAuraBoss__vmt1C(void *this)
{
  CNRDAuraMaster__vmt1C();
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(
           this,
           "Common/Etc/Animation/Aura/BossAuraMaster.ani");
}



// ------------------------------------------------------------
// 0x5FE210 CNAuraBoss__vmt78
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNAuraBoss__vmt78(int this, int a2)
{
  unsigned int v3; // edi
  int v4; // edx
  int v5; // edi
  int v6; // ebx
  int64_t v7; // rax
  int *v8; // esi
  int v9; // edi
  int v10; // eax
  float v12; // [esp+Ch] [ebp-8h]
  int v13; // [esp+Ch] [ebp-8h]

  v12 = *(float *)(this + 128) * 0.0099999998 - 1.0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 18;
  *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v3)) + v12;
  sub_41A590(v3, v4, v13);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);
  v5 = *(uint32_t *)(this + 4);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 740))(v5);
  v7 = ((int64_t (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)v5 + 684))(v5);
  sub_41A590(v7, SHIDWORD(v7), v6);
  v8 = *(int **)(this + 4);
  v9 = *v8;
  v10 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*v8 + 736))(v8, 1, 0);
  return (*(int (/*thiscall*/ **)(int *, int))(v9 + 728))(v8, v10);
}



// ------------------------------------------------------------
// 0x5FE2C0 sub_5FE2C0
// ------------------------------------------------------------
// 调: sub_5FE2C0 sub_5910D0
uint32_t */*thiscall*/ sub_5FE2C0(uint32_t *this, int a2)
{
  sub_5910D0(0, 33, 500, 0);
  *(this + 32) = a2;
  *this = &vftbl_CNAuraBoss;
  return this;
}



// ------------------------------------------------------------
// 0x5FE2F0 CNAuraBoss__vmt0
// ------------------------------------------------------------
// 调: sub_5FE320
void */*thiscall*/ CNAuraBoss__vmt0(void *Block, char a2)
{
  sub_5FE320();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5FE320 sub_5FE320
// ------------------------------------------------------------
// 调: sub_5FE320 sub_591190
int /*thiscall*/ sub_5FE320(uint32_t *this)
{
  *this = &vftbl_CNAuraBoss;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x5FE330 sub_5FE330
// ------------------------------------------------------------
// 调: sub_5FE330
int /*thiscall*/ sub_5FE330(int this)
{
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint8_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 1000;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FE380 sub_5FE380
// ------------------------------------------------------------
// 调: sub_5FE380
int /*thiscall*/ sub_5FE380(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 76);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 76) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5FE3A0 sub_5FE3A0
// ------------------------------------------------------------
// 证: "Monster/Common/Particle/MonsterDieSmoke.ptl"
// 调: sub_5FE3A0 sub_428F30 sub_4049C0
int /*userpurge*/ sub_5FE3A0@<eax>(int a1@<ecx>, double a2@<st0>, void *Block, int a4, int a5, int a6, int a7)
{
  int v8; // eax
  int v9; // eax
  int v10; // edi

  *(uint32_t *)(a1 + 284) = Block;
  v8 = a4;
  if ( a4 <= 30000 )
  {
    v8 = 30000;
  }
  else if ( a4 >= 170000 )
  {
    v8 = 170000;
  }
  *(uint32_t *)(a1 + 288) = v8;
  *(uint32_t *)(a1 + 292) = a5;
  *(uint32_t *)(a1 + 296) = a6;
  *(uint8_t *)(a1 + 300) = 0;
  if ( operator new(0x12Cu) != nullptr )
    v9 = sub_428F30("Monster/Common/Particle/MonsterDieSmoke.ptl", 0);
  else
    v9 = 0;
  *(uint32_t *)(a1 + 304) = v9;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 28))(v9);
  v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 304) + 36))(*(uint32_t *)(a1 + 304));
  sub_4049C0(20.0, 60.0, *(uint32_t *)(a1 + 288) - 30000, 140000);
  *(float *)v10 = a2;
  sub_4049C0(50.0, 150.0, *(uint32_t *)(a1 + 288) - 30000, 140000);
  *(uint32_t *)(v10 + 12) = (uint64_t)a2;
  *(uint32_t *)(v10 + 20) = (uint64_t)a2;
  *(uint32_t *)(v10 + 16) = 2 * (uint64_t)a2;
  sub_4049C0(1000.0, 2000.0, *(uint32_t *)(a1 + 288) - 30000, 140000);
  *(uint32_t *)(a1 + 308) = (uint64_t)a2;
  *(uint32_t *)(a1 + 320) = a7;
  return a7;
}



// ------------------------------------------------------------
// 0x5FE4F0 CNPieceDestroyEffect__vmt14C
// ------------------------------------------------------------
// 证: "Monster/Common/Animation/MonsterDieFlash.ani"
// 调: sub_699000 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E1F0
int /*thiscall*/ sub_5FE4F0(int *this)
{
  char v2; // al
  int v3; // eax
  int v4; // edx
  int v5; // esi
  bool v6; // zf
  int v7; // edi
  int v8; // edi
  int v9; // ecx
  uint32_t *v10; // edi
  uint64_t v11; // rax
  int v12; // eax
  int v13; // eax
  uint64_t v14; // rax
  int v15; // eax
  unsigned int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  uint64_t v22; // rax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // esi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  signed int v31; // eax
  unsigned int v32; // eax
  int v33; // esi
  float v34; // ecx
  bool v35; // cc
  int v36; // ecx
  int v37; // esi
  int v38; // eax
  void *v39; // ecx
  unsigned int j; // esi
  int result; // eax
  int v42; // [esp-28h] [ebp-180h]
  float v43; // [esp-4h] [ebp-15Ch]
  float v44; // [esp-4h] [ebp-15Ch]
  void *v45; // [esp+Ch] [ebp-14Ch] BYREF
  void *Block; // [esp+10h] [ebp-148h]
  int v47; // [esp+14h] [ebp-144h]
  int v48; // [esp+18h] [ebp-140h]
  int v49; // [esp+1Ch] [ebp-13Ch]
  char v50[4]; // [esp+20h] [ebp-138h] BYREF
  void *v51; // [esp+24h] [ebp-134h]
  void *v52; // [esp+28h] [ebp-130h]
  int v53; // [esp+2Ch] [ebp-12Ch]
  int v54; // [esp+30h] [ebp-128h]
  int v55; // [esp+34h] [ebp-124h]
  float v56; // [esp+38h] [ebp-120h]
  int v57; // [esp+3Ch] [ebp-11Ch]
  int v58; // [esp+40h] [ebp-118h]
  int i; // [esp+44h] [ebp-114h]
  char Buffer[256]; // [esp+48h] [ebp-110h] BYREF
  int v61; // [esp+148h] [ebp-10h]
  int v62; // [esp+154h] [ebp-4h]

  v61 = dword_796E50;
  nullsub_3(this);
  v2 = *((uint8_t *)this + 300);
  v54 = 1;
  if ( v2 != 0 || sub_699000((int)(this + 16)) < *(this + 74) )
    goto LABEL_71;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
  v4 = *this;
  v58 = v3;
  v57 = (*(int (/*thiscall*/ **)(int *))(v4 + 124))(this);
  v5 = 0;
  v55 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v51 = nullptr;
  v52 = nullptr;
  v53 = 0;
  v6 = (*(uint8_t *)(this + 80) & 8) == 0;
  v62 = 0;
  if ( v6 )
    goto LABEL_15;
  LOBYTE(v62) = 1;
  v7 = sub_42FCB0(228) != 0 ? sub_431860((char)"Monster/Common/Animation/MonsterDieFlash.ani", 1) : 0;
  v49 = sub_44B6C0(284);
  LOBYTE(v62) = 2;
  v8 = v49 != 0 ? sub_44E1F0(v7, 1) : 0;
  v9 = *(this + 29);
  LOBYTE(v62) = 0;
  sub_45FE80(v9, v8, 2, 0, v8, (int)this, 0);
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 112))(v8, v58, v57, v55);
  if ( *(uint32_t *)(dword_8F7A24 + 244) == 1 )
  {
LABEL_15:
    v10 = (uint32_t *)v54;
  }
  else
  {
    v5 = dword_8F82E0;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82E0 + 28))(dword_8F82E0);
    v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 36))(v5);
    v10[1] = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);
    v11 = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);
    v10[3] = v11;
    v10[4] = v11;
    v10[5] = v11;
    v56 = sub_4049C0(1.0, 2.0, *(this + 72) - 30000, 140000);
    if ( *(this + 81) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 40))(v5, v58, v57, v55);
      v12 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)v5 + 92))(v5, &v45);
      LOBYTE(v62) = 3;
      sub_4E77D0((int)v50, v12);
      LOBYTE(v62) = 0;
      sub_5E5260(&v45);
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);
      for ( i = (int)v51; (void *)i != v52; i += 4 )
      {
        v43 = v56;
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);
        sub_4922F0(v43);
      }
    }
  }
  if ( (*(uint8_t *)(this + 80) & 2) != 0 )
  {
    v13 = *(uint32_t *)(dword_8F7A24 + 244);
    if ( v13 != 2 )
    {
      v5 = dword_8F82CC[v13 != 1];
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 28))(v5);
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 36))(v5);
      v10[1] = (uint64_t)sub_4049C0(15.0, 60.0, *(this + 72) - 30000, 140000);
      v14 = (uint64_t)sub_4049C0(50.0, 150.0, *(this + 72) - 30000, 140000);
      v10[3] = v14;
      v10[4] = 2 * v14;
      v10[5] = v14;
      v56 = sub_4049C0(1.0, 1.0, *(this + 72) - 30000, 140000);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 40))(v5, v58, v57, v55);
      v15 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)v5 + 92))(v5, &v45);
      LOBYTE(v62) = 4;
      sub_4E77D0((int)v50, v15);
      LOBYTE(v62) = 0;
      sub_5E5260(&v45);
      sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);
      for ( i = (int)v51; (void *)i != v52; i += 4 )
      {
        v44 = v56;
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);
        sub_4922F0(v44);
      }
    }
  }
  if ( (*(uint8_t *)(this + 80) & 1) != 0 && *(this + 73) != 0 )
  {
    v16 = *(uint32_t *)(dword_8F7A24 + 244);
    if ( v16 != 0 )
    {
      if ( v16 == 1 )
      {
        v5 = dword_8F82D4;
      }
      else if ( v16 == 2 )
      {
        v5 = dword_8F82DC;
      }
    }
    else
    {
      v5 = dword_8F82D8;
    }
    if ( v16 <= 1 )
    {
      i = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 28))(v5);
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 36))(v5);
      v17 = *(this + 71);
      switch ( v17 )
      {
        case 1:
        case 2:
          v21 = i;
          *(uint32_t *)(i + 31) = 400;
          *(uint32_t *)(v21 + 35) = 400;
          *(uint32_t *)(v21 + 76) = 0;
          v19 = 100;
          break;
        case 3:
        case 4:
          v20 = i;
          *(uint32_t *)(i + 31) = 700;
          *(uint32_t *)(v20 + 35) = 700;
          *(uint32_t *)(v20 + 76) = *(this + 71) != 3 ? -70 : 70;
          v19 = 40;
          break;
        case 5:
          v18 = i;
          *(uint32_t *)(i + 31) = 800;
          *(uint32_t *)(v18 + 35) = 800;
          *(uint32_t *)(v18 + 76) = 0;
          v19 = 10;
          break;
        default:
          goto LABEL_38;
      }
      v10[10] = v19;
      v10[11] = v19;
    }
LABEL_38:
    v10[1] = (uint64_t)sub_4049C0(10.0, 30.0, *(this + 72) - 30000, 140000);
    v22 = (uint64_t)sub_4049C0(50.0, 150.0, *(this + 72) - 30000, 140000);
    v42 = *(this + 72) - 30000;
    i = v22;
    v56 = sub_4049C0(0.5, 1.0, v42, 140000);
    if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )
    {
      v10[1] = (uint64_t)sub_4049C0(20.0, 60.0, *(this + 72) - 30000, 140000);
      v56 = sub_4049C0(2.0, 4.0, *(this + 72) - 30000, 140000);
      v54 = 10;
    }
    v23 = i;
    v24 = 2 * i;
    v10[3] = i;
    v10[4] = v24;
    v10[5] = v23;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 12))(v5, 0);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 40))(v5, v58, v57, v55);
    v25 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)v5 + 92))(v5, &v45);
    LOBYTE(v62) = 5;
    sub_4E77D0((int)v50, v25);
    LOBYTE(v62) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)*(this + 29), 2, 0, (int)v50);
    v26 = *(uint32_t *)(dword_8F7A24 + 244);
    if ( v26 == 1 )
    {
      sprintf(Buffer, "Monster/Common/m%04d.img", *(this + 73));
    }
    else if ( v26 != 0 )
    {
      if ( v26 == 2 )
        strcpy(Buffer, "Monster/Common/MonsterDiePieceVeryYoung.img");
    }
    else
    {
      strcpy(Buffer, "Monster/Common/MonsterDieYoung.img");
    }
    v49 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, Buffer);
    i = (int)v51;
    if ( v51 != v52 )
    {
      while ( 1 )
      {
        v27 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)i + 200))(*(uint32_t *)i);
        v28 = *(uint32_t *)(v27 + 44);
        v29 = 0;
        v55 = v27;
        v57 = v28 != 0 ? (*(uint32_t *)(v27 + 48) - v28) / 88 : 0;
        v30 = *(uint32_t *)(dword_8F7A24 + 244);
        v58 = 0;
        if ( v30 == 1 )
          break;
        if ( v30 != 0 )
        {
          if ( v30 == 2 )
          {
            v31 = rand() & 0x80000001;
            if ( v31 < 0 )
            {
              v32 = ((uint8_t)v31 - 1) | 0xFFFFFFFE;
LABEL_60:
              v31 = v32 + 1;
            }
LABEL_61:
            v58 = v31;
          }
        }
        else
        {
          v58 = rand() % 3 + 1;
        }
        if ( v57 > 0 )
        {
          do
          {
            v33 = sub_4924C0(v29);
            *(uint32_t *)v33 = sub_418DD0(v58);
            v34 = v56;
            *(float *)(v33 + 24) = v56;
            v35 = ++v29 < v57;
            *(float *)(v33 + 20) = v34;
          }
          while ( v35 );
        }
        i += 4;
        if ( (void *)i == v52 )
          goto LABEL_65;
      }
      v31 = rand() & 0x80000003;
      if ( v31 < 0 )
      {
        v32 = ((uint8_t)v31 - 1) | 0xFFFFFFFC;
        goto LABEL_60;
      }
      goto LABEL_61;
    }
  }
LABEL_65:
  if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TEEN_MONSTER_DIE", -1, 0, 0);
  if ( ++*(this + 81) >= v54 )
  {
    *((uint8_t *)this + 300) = 1;
    *(this + 81) = 0;
  }
  v62 = -1;
  if ( v51 != nullptr )
    j__free(v51);
LABEL_71:
  v36 = (int)(this + 16);
  if ( (*(uint8_t *)(this + 80) & 4) == 0 )
  {
    result = sub_699000(v36);
    if ( result < *(this + 74) )
      return result;
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);
  }
  if ( sub_699000(v36) >= *(this + 74) + 700 )
  {
    v37 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v38 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 76) + 40))(*(this + 76), v37, v38, 30);
    (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 76) + 92))(*(this + 76), &v45);
    v39 = (void *)*(this + 29);
    v62 = 6;
    sub_4600B0(v39, 2, 0, (int)&v45);
    for ( j = 0; Block != nullptr && j < (v47 - (int)Block) >> 2; ++j )
    {
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + j) + 200))(*((uint32_t *)Block + j));
      *(uint32_t *)(sub_4924C0(0) + 48) = *(this + 77);
    }
    v62 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v47 = 0;
    v48 = 0;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 76) + 68))(*(this + 76));
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);
  return result;
}


// ------------------------------------------------------------
// 0x5FEEB0 sub_5FEEB0
// ------------------------------------------------------------
// 调: sub_5FEEB0
int /*thiscall*/ sub_5FEEB0(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 4;
  *(uint32_t *)(this + 96) = 0;
  *(uint8_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FEEE0 sub_5FEEE0
// ------------------------------------------------------------
// 调: sub_5FEEE0 sub_699000 sub_4049C0 sub_47E720 sub_47EFD0
int /*thiscall*/ sub_5FEEE0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  uint64_t v7; // rax
  char *v8; // edi

  *(this + 23) = a3;
  *(this + 20) = a4;
  v6 = sub_699000((int)(this + 2));
  HIDWORD(v7) = rand() % 100;
  LODWORD(v7) = *(this + 20);
  *(this + 26) = HIDWORD(v7) + v6;
  switch ( (int)v7 )
  {
    case 0:
      *(this + 11) = (uint64_t)sub_4049C0(10000.0, 10000.0, a2 - 1, 39);
      v7 = (uint64_t)sub_4049C0(10.0, 100.0, a2 - 1, 39);
      *(this + 22) = v7;
      break;
    case 1:
      v8 = (char *)sub_47E720(1, 0x1Eu);
      *(this + 21) = sub_47EFD0(v8, 0.0, a2, a5, a5, 0);
      LODWORD(v7) = sub_47EF20(v8, 2u, a2, -1, -1, 11);
      *(this + 11) = v7;
      break;
    case 2:
      *(this + 23) = 4;
      *(this + 21) = 0;
      *(this + 22) = 0;
      *(this + 26) = 0;
      *(this + 11) = 0;
      break;
    case 3:
      *(this + 11) = a2;
      break;
    default:
      return v7;
  }
  return v7;
}



// ------------------------------------------------------------
// 0x5FEFE0 CNEnchantWeapon__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（16 行，无外调无字符串）
char /*thiscall*/ CNEnchantWeapon__vmt8(int this, int a2)
{
  char result; // al

  result = *(uint8_t *)(this + 100);
  if ( result != 0 )
  {
    result = a2;
    if ( *(uint8_t *)(a2 + 16) != 0 )
    {
      *(uint32_t *)(a2 + 20) = *(uint32_t *)(this + 92);
      *(uint32_t *)(a2 + 8) += *(uint32_t *)(this + 88);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5FF010 CNEnchantWeapon__vmtC
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_41A590
int /*thiscall*/ CNEnchantWeapon__vmtC(uint32_t *this, int a2)
{
  int v2; // edi
  int v3; // eax
  int v4; // edx

  v2 = *(this + 21);
  v3 = sub_41A5E0(a2 + 1012);
  return sub_41A590(a2 + 1012, v4, v2 + v3);
}



// ------------------------------------------------------------
// 0x5FF040 sub_5FF040
// ------------------------------------------------------------
// 调: sub_5FF040 sub_699000 sub_42B420 sub_491690
char /*thiscall*/ sub_5FF040(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // eax
  uint8_t v4; // al
  int v5; // eax
  uint8_t v6; // al
  int v7; // eax
  uint8_t v8; // al
  int v9; // eax
  uint8_t v10; // al

  LOBYTE(v2) = *(uint8_t *)(a2 + 176);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = *(this + 23);
    if ( v2 != 0 )
    {
      switch ( v2 )
      {
        case 1:
          v5 = sub_699000((int)(this + 2));
          v6 = sub_42B420(100, 220, v5, 250);
          LOBYTE(v2) = sub_491690(1, 2, 1, -65536, (v6 << 24) | 0xFFFFFF, 1);
          break;
        case 3:
          v7 = sub_699000((int)(this + 2));
          v8 = sub_42B420(100, 220, v7, 250);
          LOBYTE(v2) = sub_491690(1, 2, 1, -1, (v8 << 24) | 0xFFFFFF, 1);
          break;
        case 2:
          v9 = sub_699000((int)(this + 2));
          v10 = sub_42B420(100, 220, v9, 250);
          LOBYTE(v2) = sub_491690(1, 3, 1, -1, (v10 << 24) | 0xFFFFFF, 1);
          break;
        default:
          break;
      }
    }
    else
    {
      v3 = sub_699000((int)(this + 2));
      v4 = sub_42B420(100, 220, v3, 250);
      LOBYTE(v2) = sub_491690(1, 2, 1, -16776961, (v4 << 24) | 0xFFFFFF, 1);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5FF170 CNEnchantWeapon__vmt20
// ------------------------------------------------------------
// 证: "FROST_OFF" | "FLAME_OFF"
char /*thiscall*/ CNEnchantWeapon__vmt20(int this, char a2)
{
  int v2; // eax
  int v3; // eax

  LOBYTE(v2) = a2;
  if ( a2 == 0 )
  {
    v3 = *(uint32_t *)(this + 92);
    if ( v3 != 0 )
    {
      v2 = v3 - 1;
      if ( v2 == 0 )
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
                       *(uint32_t *)(this + 4),
                       "FROST_OFF",
                       -1,
                       0,
                       0);
    }
    else
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
                     *(uint32_t *)(this + 4),
                     "FLAME_OFF",
                     -1,
                     0,
                     0);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5FF1C0 CNChangeWeaponElement__vmt8
// ------------------------------------------------------------
// 证: 叶子函数（12 行，无外调无字符串）
char /*thiscall*/ CNChangeWeaponElement__vmt8(int this, int a2)
{
  int v2; // eax

  LOBYTE(v2) = *(uint8_t *)(this + 100);
  if ( (uint8_t)v2 != 0 )
  {
    v2 = *(uint32_t *)(this + 92);
    *(uint32_t *)(a2 + 20) = v2;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5FF1E0 sub_5FF1E0
// ------------------------------------------------------------
// 调: sub_5FF1E0 sub_42AC90
void /*thiscall*/ sub_5FF1E0(int this)
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
  if ( *(uint32_t *)(this + 108) != (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) )
  {
    v18 = 1;
    *(uint32_t *)(v1 + 108) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v1 + 4) + 200))(*(uint32_t *)(v1 + 4));
  }
  v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 792))(*(uint32_t *)(v1 + 4), 8);
  if ( v2 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 40))(*(uint32_t *)(v1 + 4), 273) != 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v1 + 4) + 1084))(*(uint32_t *)(v1 + 4), 8);
  }
  if ( *(uint32_t *)(v1 + 112) == v2 )
  {
    if ( v18 == 0 )
      return;
  }
  else
  {
    *(uint32_t *)(v1 + 112) = v2;
  }
  v3 = v1 + 116;
  if ( *(uint32_t *)(v1 + 120) != 0 )
    j__free(*(void **)(v1 + 120));
  *(uint32_t *)(v1 + 120) = 0;
  *(uint32_t *)(v1 + 124) = 0;
  *(uint32_t *)(v1 + 128) = 0;
  if ( *(uint32_t *)(v1 + 108) != 0 )
  {
    v4 = *(uint32_t *)(v1 + 112);
    if ( v4 != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 248))(v4);
      v6 = *(uint32_t **)(v5 + 4);
      v13 = v5;
      for ( i = v6; v6 != *(uint32_t **)(v13 + 8); i = v6 )
      {
        v7 = *(uint32_t *)(v1 + 108) + 200;
        v14 = *v6;
        v8 = *(uint32_t **)(*(uint32_t *)(v1 + 108) + 204);
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
                sub_42AC90(v3, *(char **)(v3 + 8), 1u, v9 + 3);
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
// 0x5FF350 CNEnchantWeapon__vmt14
// ------------------------------------------------------------
// 调: sub_5FF1E0 sub_5FF040
void /*thiscall*/ CNEnchantWeapon__vmt14(int this, char a2, int a3, int a4, int a5)
{
  int *i; // esi

  if ( a2 == 0 && *(uint8_t *)(this + 100) != 0 )
  {
    sub_5FF1E0(this);
    for ( i = *(int **)(this + 120); i != *(int **)(this + 124); ++i )
      sub_5FF040((uint32_t *)this, *i);
  }
}



// ------------------------------------------------------------
// 0x5FF390 sub_5FF390
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/FlameWeapon.an" | "FLAME_ON"
// 调: sub_5FF390 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF390(int *this)
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v13; // [esp-8h] [ebp-28h]
  int v14; // [esp+0h] [ebp-20h]
  char *v16; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/FlameWeapon.ani", 1);
  else
    v3 = 0;
  *(this + 24) = v3;
  v4 = (char *)sub_44B6C0(284);
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, *(this + 24), 1);
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v4 = nullptr;
  }
  v13 = *(this + 1);
  v16 = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)v13 + 80))();
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, v13, 0);
  v6 = *(this + 1);
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 192))(v6) / 2;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 128))(v6);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 124))(v6, v9 + v8);
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 120))(v6, v10);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v16, v11);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v16 + 60))(v16, *(this + 1));
  sub_4A06D0(v14);
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
           *(this + 1),
           "FLAME_ON",
           -1,
           0);
}



// ------------------------------------------------------------
// 0x5FF4C0 sub_5FF4C0
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/FrostWeapon.an" | "FROST_ON"
// 调: sub_5FF4C0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF4C0(int *this)
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v13; // [esp-8h] [ebp-28h]
  int v14; // [esp+0h] [ebp-20h]
  char *v16; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/FrostWeapon.ani", 1);
  else
    v3 = 0;
  *(this + 24) = v3;
  v4 = (char *)sub_44B6C0(284);
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, *(this + 24), 1);
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v4 = nullptr;
  }
  v13 = *(this + 1);
  v16 = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)v13 + 80))();
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, v13, 0);
  v6 = *(this + 1);
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 192))(v6) / 2;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 128))(v6);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 124))(v6, v9 + v8);
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 120))(v6, v10);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v16, v11);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v16 + 60))(v16, *(this + 1));
  sub_4A06D0(v14);
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t))(*(uint32_t *)*(this + 1) + 212))(
           *(this + 1),
           "FROST_ON",
           -1,
           0);
}



// ------------------------------------------------------------
// 0x5FF5F0 sub_5FF5F0
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/LightWeapon.an"
// 调: sub_5FF5F0 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF5F0(int *this)
{
  int v2; // eax
  char *v3; // ebx
  int v4; // eax
  char *v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v13; // [esp-8h] [ebp-28h]
  int v14; // [esp-4h] [ebp-24h]
  char *v16; // [esp+10h] [ebp-10h]

  v2 = sub_42FCB0(228);
  v3 = nullptr;
  if ( v2 != 0 )
    v4 = sub_431860(v2, "Common/CommonEffect/Animation/LightWeapon.ani", 1);
  else
    v4 = 0;
  *(this + 24) = v4;
  v5 = (char *)sub_44B6C0(284);
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, *(this + 24), 1);
    *(uint32_t *)v5 = &vftbl_CNRDPooledObject;
    v3 = v5;
  }
  v13 = *(this + 1);
  v16 = v3;
  v6 = (*(int (**)(void))(*(uint32_t *)v13 + 80))();
  sub_45FE80(v6, (int)this, 2, 0, (int)v3, v13, 0);
  v7 = *(this + 1);
  v8 = *(uint32_t *)v3;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 192))(v7) / 2;
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 128))(v7) + v9;
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
  v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 120))(v7, v10);
  (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v16, v11);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v16 + 60))(v16, *(this + 1));
  return sub_4A06D0(v14);
}



// ------------------------------------------------------------
// 0x5FF700 sub_5FF700
// ------------------------------------------------------------
// 证: "Common/CommonEffect/Animation/DarkWeaponSpar" | "Common/CommonEffect/Animation/DarkWeaponSmok"
// 调: sub_5FF700 sub_42FCB0 sub_431860 sub_44B6C0 sub_44E0D0
int /*thiscall*/ sub_5FF700(int *this)
{
  int v2; // eax
  int v3; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v14; // [esp-10h] [ebp-28h]
  int v15; // [esp-Ch] [ebp-24h]
  char *v17; // [esp+8h] [ebp-10h]

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Common/CommonEffect/Animation/DarkWeaponSpark.ani", 1);
  else
    v3 = 0;
  *(this + 24) = v3;
  v4 = (char *)sub_44B6C0(284);
  if ( v4 != nullptr )
  {
    sub_44E0D0(v4, *(this + 24), 1);
    *(uint32_t *)v4 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v4 = nullptr;
  }
  v14 = *(this + 1);
  v17 = v4;
  v5 = (*(int (**)(void))(*(uint32_t *)v14 + 80))();
  sub_45FE80(v5, (int)v4, 2, 0, (int)v4, v14, 0);
  v6 = *(this + 1);
  v7 = *(uint32_t *)v4;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 192))(v6) / 2;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 128))(v6) + v8;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 124))(v6);
  v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 120))(v6, v9);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v17, v10);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v17 + 60))(v17, *(this + 1));
  sub_4A06D0(v15);
  v11 = sub_42FCB0(228);
  if ( v11 != 0 )
    v12 = sub_431860(v11, "Common/CommonEffect/Animation/DarkWeaponSmoke.ani", 1);
  else
    v12 = 0;
  return (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v17 + 204))(
           v17,
           100,
           v12,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x5FF860 CNEnchantWeapon__vmt4
// ------------------------------------------------------------
// 调: sub_699000 sub_5FF390 sub_5FF4C0 sub_5FF5F0 sub_5FF700
char /*thiscall*/ CNEnchantWeapon__vmt4(int this)
{
  int v2; // eax

  IRDAppendage__vmt4((int *)this);
  LOBYTE(v2) = *(uint8_t *)(this + 100);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = sub_699000(this + 8);
    if ( *(uint32_t *)(this + 104) < v2 )
    {
      v2 = *(uint32_t *)(this + 80);
      if ( v2 >= 0 )
      {
        if ( v2 <= 1 )
        {
          v2 = *(uint32_t *)(this + 92);
          switch ( v2 )
          {
            case 0:
              LOBYTE(v2) = sub_5FF390((int *)this);
              *(uint8_t *)(this + 100) = 1;
              return v2;
            case 1:
              LOBYTE(v2) = sub_5FF4C0((int *)this);
              *(uint8_t *)(this + 100) = 1;
              return v2;
            case 3:
              LOBYTE(v2) = sub_5FF5F0((int *)this);
              *(uint8_t *)(this + 100) = 1;
              return v2;
            default:
              break;
          }
        }
        if ( v2 == 2 )
          LOBYTE(v2) = sub_5FF700((int *)this);
      }
      *(uint8_t *)(this + 100) = 1;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5FF8E0 sub_5FF8E0
// ------------------------------------------------------------
// 调: sub_5FF8E0
int /*thiscall*/ sub_5FF8E0(int this)
{
  *(uint32_t *)(this + 96) = 33;
  *(uint32_t *)(this + 676) = 0;
  *(uint32_t *)(this + 608) = 200;
  *(uint32_t *)(this + 876) = 0;
  *(uint32_t *)(this + 880) = 1;
  *(uint32_t *)(this + 884) = 0;
  *(uint32_t *)(this + 888) = 0;
  *(uint32_t *)(this + 892) = 0;
  *(uint32_t *)(this + 896) = 0;
  *(uint32_t *)(this + 900) = 0;
  *(uint32_t *)(this + 904) = 0;
  *(uint32_t *)(this + 908) = 0;
  *(uint32_t *)(this + 912) = 0;
  *(uint8_t *)(this + 944) = 0;
  *(uint8_t *)(this + 945) = 0;
  *(uint32_t *)(this + 948) = 3;
  *(uint32_t *)(this + 952) = 0;
  *(uint16_t *)(this + 946) = 255;
  *(uint32_t *)(this + 956) = 255;
  *(uint32_t *)(this + 964) = 0;
  *(uint32_t *)(this + 968) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5FF980 sub_5FF980
// ------------------------------------------------------------
// 调: sub_5FF980
void /*thiscall*/ sub_5FF980(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 219);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void *)*(this + 242);
  *(this + 219) = 0;
  if ( v3 != nullptr )
    j__free(v3);
  *(this + 242) = 0;
}



// ------------------------------------------------------------
// 0x5FF9C0 CNRDPassiveObject__vmt1F4
// ------------------------------------------------------------
// 调: sub_4E5740
int /*thiscall*/ CNRDPassiveObject__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // edi
  int v6; // eax

  v5 = IRDCollisionObject__vmt1F4(this, a2, a3, a4);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
    if ( (uint8_t)sub_4E5740(*(uint32_t *)(v6 + 16), a2) == 0 )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x5FFA20 CNRDPassiveObject__vmt130
// ------------------------------------------------------------
// 证: 叶子函数（16 行，无外调无字符串）
int /*thiscall*/ CNRDPassiveObject__vmt130(void *this)
{
  int v1; // eax
  int v2; // esi

  v1 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);
  v2 = v1;
  if ( v1 == 0 )
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v1 + 40))(v1, 273) != 0 )
    return v2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 529) != 0 )
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 304))(v2);
  else
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
}



// ------------------------------------------------------------
// 0x5FFA80 CNRDPassiveObject__vmt2B8
// ------------------------------------------------------------
// 调: sub_4938F0 sub_4918E0
char /*thiscall*/ sub_5FFA80(int *this, int a2)
{
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // ebx
  int v18; // ebx
  int v19; // ebx
  int v20; // ebx
  int v21; // ebx
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // ebx
  int v26; // eax
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // ecx
  int v31; // ebx
  bool v32; // cc
  int v33; // eax
  int *v34; // eax
  int v35; // ebx
  int v36; // eax
  int *v37; // eax
  unsigned int v38; // ebx
  int v39; // esi
  int v40; // [esp+8h] [ebp-18h]
  int v41; // [esp+Ch] [ebp-14h]
  int v42; // [esp+10h] [ebp-10h]
  int v43; // [esp+14h] [ebp-Ch]
  int v44; // [esp+14h] [ebp-Ch]
  int v45; // [esp+18h] [ebp-8h]
  int v46; // [esp+1Ch] [ebp-4h]
  int v47; // [esp+28h] [ebp+8h]

  if ( a2 == 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2) == 0 )
  {
    return 0;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= v5 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
    v7 = v6;
    if ( *(uint32_t *)(v6 + 148) == -1 )
      sub_4938F0(v6);
    v8 = sub_4918E0((int *)(v7 + 60), 0);
    v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2) - v8;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
    v10 = v9;
    if ( *(uint32_t *)(v9 + 148) == -1 )
      sub_4938F0(v9);
    v11 = sub_4918E0((int *)(v10 + 60), 1);
    v42 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2) + v11;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
    v13 = v12;
    if ( *(uint32_t *)(v12 + 148) == -1 )
      sub_4938F0(v12);
    v43 = sub_4918E0((int *)(v13 + 60), 2);
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) - v43;
    v40 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2) + v14;
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
    v16 = v15;
    if ( *(uint32_t *)(v15 + 148) == -1 )
      sub_4938F0(v15);
    v17 = sub_4918E0((int *)(v16 + 60), 3);
    v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 128))(a2) + v17;
    v46 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) + v18;
    v19 = *(this + 30);
    if ( *(uint32_t *)(v19 + 148) == -1 )
      sub_4938F0(*(this + 30));
    v20 = 15 - sub_4918E0((int *)(v19 + 60), 0);
    v41 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v20;
    v21 = *(this + 30);
    if ( *(uint32_t *)(v21 + 148) == -1 )
      sub_4938F0(*(this + 30));
    v22 = sub_4918E0((int *)(v21 + 60), 1);
    v23 = v22 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 15;
    v24 = *(this + 30);
    v45 = v23;
    if ( *(uint32_t *)(v24 + 148) == -1 )
      sub_4938F0(v24);
    v25 = sub_4918E0((int *)(v24 + 60), 2);
    v26 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - v25;
    v27 = *(this + 30);
    v44 = v26;
    if ( *(uint32_t *)(v27 + 148) == -1 )
      sub_4938F0(v27);
    v28 = sub_4918E0((int *)(v27 + 60), 3);
    v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v30 = v47;
    v31 = v29 + v28;
    if ( v47 < v41 )
    {
      if ( v42 > v45 && v40 < v44 && v46 > v31 )
        return 1;
      v30 = v47;
    }
    if ( v46 > v44 && v46 < v31 )
    {
      if ( v42 <= v41 || v42 >= v45 )
      {
        v32 = v30 < v41;
        if ( v30 <= v41 )
        {
LABEL_35:
          if ( !v32 || v42 <= v45 )
            return 0;
          goto LABEL_37;
        }
        if ( v30 >= v45 )
        {
          v32 = v30 < v41;
          goto LABEL_35;
        }
      }
LABEL_37:
      v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
      v34 = (int *)sub_42F220(v33);
      v35 = sub_4918E0(v34, 3);
      v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 200))(a2);
      v37 = (int *)sub_42F220(v36);
      v38 = abs32(sub_4918E0(v37, 2) - v35);
      v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) + v38 + 15;
      if ( v39 > (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) )
        return 1;
    }
  }
  return 0;
}


// ------------------------------------------------------------
// 0x5FFD50 CNRDPassiveObject__vmt2A8
// ------------------------------------------------------------
// 证: 叶子函数（18 行，无外调无字符串）
void /*thiscall*/ CNRDPassiveObject__vmt2A8(uint32_t *this, int a2)
{
  *(this + 173) = a2;
  if ( a2 != 0 )
  {
    *(this + 152) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    *(this + 220) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 388))(a2);
    *(this + 221) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 392))(a2);
    *(this + 222) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 396))(a2);
    *(this + 223) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 400))(a2);
    *(this + 224) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 404))(a2);
    *(this + 225) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 408))(a2);
    *(this + 226) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 412))(a2);
    *(this + 227) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 416))(a2);
    *(this + 228) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 420))(a2);
  }
}



// ------------------------------------------------------------
// 0x5FFE10 CNRDPassiveObject__vmt2C0
// ------------------------------------------------------------
// 证: 叶子函数（23 行，无外调无字符串）
int /*thiscall*/ CNRDPassiveObject__vmt2C0(int *this)
{
  uint64_t v1; // rax
  uint32_t v3[4]; // [esp+4h] [ebp-14h]
  int v4; // [esp+14h] [ebp-4h]

  v4 = *(this + 171);
  LODWORD(v1) = v4;
  if ( v4 > 0 )
  {
    v3[0] = 1065353216;
    v3[1] = 0x40000000;
    v3[2] = 1077936128;
    v3[3] = 1082130432;
    v1 = (uint64_t)((double)v4 * *(float *)&v3[dword_99FB8C]);
    if ( (int)v1 > 0 )
    {
      *(this + 171) = v1;
      *(this + 170) = v1;
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x5FFE70 CNRDPassiveObject__vmt140
// ------------------------------------------------------------
// 证: 叶子函数（10 行，无外调无字符串）
char /*thiscall*/ CNRDPassiveObject__vmt140(uint8_t *this)
{
  char result; // al

  CNRDObject__vmt140(this);
  result = *(this + 276);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 704))(this);
  return result;
}


