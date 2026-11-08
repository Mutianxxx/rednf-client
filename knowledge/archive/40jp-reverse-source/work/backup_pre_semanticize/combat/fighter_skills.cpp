// ============================================================
// 【40JP逆向源代码工程】src/combat/fighter_skills.cpp
// 模块: 0x5E0000-0x5F0000
// 来源: work/dump 素材  区块: 0x5E0090-0x5EFBD1 §A 技能基础与投技
// 层级: L2 转写 + 证据标注层（函数体保持 Hex-Rays 忠实输出，零改动；
//       本文件由主代理自研流水线补注：每函数的字符串证据/调用链清单，
//       纯二进制事实提取（tools/annotate_evidence.py），零臆造）
// 函数数: 71
// ============================================================


#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============================================================
// §A 技能基础与投技
// ============================================================
// 0x5E0090 CNMage__vmt514
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_4B3C90 sub_47EF20
void /*thiscall*/ sub_5E0090(int **this, void *a2, void *a3)
{
  void *v3; // ebx
  int v5; // eax
  int *v6; // eax
  int v7; // edx
  int *v8; // edi
  int *v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // ecx
  int v13; // ecx
  void *v14; // eax
  void *v15; // ebx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int *v19; // eax
  int v20; // edx
  int *v21; // edi
  int v22; // ebx
  uint32_t *v23; // eax
  int v24; // edi
  uint32_t *v25; // ebx
  int v26; // eax
  bool v27; // cc
  int i; // edi
  int v29; // ebx
  void *v30; // eax
  const char *v31; // ecx
  int v32; // eax
  void *v33; // eax
  const char *v34; // ecx
  int v35; // eax
  void *v36; // eax
  const char *v37; // ecx
  int v38; // eax
  int *v39; // esi
  int j; // edi
  void *v41; // eax
  int *v42; // eax
  int v43; // edx
  int v44; // edi
  int *v45; // edi
  int v46; // ebx
  void *v47; // ebx
  void **v48; // edi
  uint32_t *v49; // eax
  int *v50; // eax
  int v51; // edx
  int v52; // ebx
  int v53; // ebx
  void *v54; // eax
  int *v55; // eax
  int v56; // edx
  int v57; // edi
  int v58; // [esp+0h] [ebp-138h]
  int v59; // [esp+4h] [ebp-134h]
  float v60; // [esp+Ch] [ebp-12Ch]
  float v61; // [esp+Ch] [ebp-12Ch]
  char v62[4]; // [esp+10h] [ebp-128h] BYREF
  void *Block; // [esp+14h] [ebp-124h]
  void **v64; // [esp+18h] [ebp-120h]
  int v65; // [esp+1Ch] [ebp-11Ch]
  void *v66; // [esp+20h] [ebp-118h]
  void *v67; // [esp+24h] [ebp-114h]
  char Buffer[256]; // [esp+28h] [ebp-110h] BYREF
  int v69; // [esp+128h] [ebp-10h]
  int v70; // [esp+134h] [ebp-4h]
  void **v71; // [esp+140h] [ebp+8h]
  void **v72; // [esp+140h] [ebp+8h]
  void (/*thiscall*/ **v73)(void *, int); // [esp+140h] [ebp+8h]
  BOOL v74; // [esp+140h] [ebp+8h]
  void *v75; // [esp+140h] [ebp+8h]
  void *v76; // [esp+140h] [ebp+8h]
  char *v77; // [esp+144h] [ebp+Ch]
  int v78; // [esp+144h] [ebp+Ch]
  void *v79; // [esp+144h] [ebp+Ch]
  void *v80; // [esp+144h] [ebp+Ch]

  v3 = a3;
  v69 = dword_796E50;
  sub_4B4170(a2, a3);
  v5 = sub_41A5E0((unsigned int)a2 + 4);
  switch ( v5 )
  {
    case 2:
      if ( *(this + 2058) == nullptr )
      {
        v67 = operator new(0x7Cu);
        v70 = 0;
        if ( v67 != nullptr )
          v6 = (int *)sub_4B3C90(0, 4);
        else
          v6 = nullptr;
        *(this + 2058) = v6;
        v7 = *v6;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v7 + 64))(v6) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2058) + 124))(*(this + 2058));
      (*(this + 2058))[11] = sub_47EF20(0, a3, -1, -1, 11);
      v71 = (void **)*(this + 2058);
      v67 = *v71;
      v60 = (float)(int)sub_47EF20(2, a3, -1, -1, 11);
      (*((void (/*thiscall*/ **)(void **, int, uint32_t, uint32_t))v67 + 30))(v71, 9, 0, LODWORD(v60));
      v8 = *(this + 2058);
      v59 = 34;
LABEL_15:
      v11 = *v8;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img");
LABEL_96:
      sub_418DD0(v59);
      (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v11 + 56))(v8, this, this, 1);
      return;
    case 41:
      if ( *(this + 2059) == nullptr )
      {
        v67 = operator new(0x7Cu);
        v70 = 1;
        if ( v67 != nullptr )
          v9 = (int *)sub_4B3C90(0, 3);
        else
          v9 = nullptr;
        *(this + 2059) = v9;
        v10 = *v9;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 64))(v9) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2059) + 124))(*(this + 2059));
      (*(this + 2059))[11] = sub_47EF20(0, a3, -1, -1, 11);
      v72 = (void **)*(this + 2059);
      v67 = *v72;
      v61 = (float)(int)sub_47EF20(1, a3, -1, -1, 11);
      (*((void (/*thiscall*/ **)(void **, int, uint32_t, uint32_t))v67 + 30))(v72, 23, 0, LODWORD(v61));
      v8 = *(this + 2059);
      v59 = 29;
      goto LABEL_15;
    case 29:
      v12 = (int)*(this + 2062);
      if ( v12 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 80))(v12) == 0 )
      {
        *(this + 2063) = (int *)4;
        *(this + 2065) = (int *)-1;
        *(this + 2066) = (int *)-1;
        *(this + 2067) = (int *)-1;
        *(this + 2068) = (int *)-1;
        *(this + 2064) = nullptr;
        v67 = (void *)sub_42FCB0(228);
        v70 = 2;
        if ( v67 != nullptr )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            LOBYTE(v13) = (uint8_t)this + 108;
          else
            v13 = (int)*(this + 91);
          v67 = (void *)sub_431920(v13, (char)"Effect/Animation/ElementalChain/Start.ani", 1);
        }
        else
        {
          v67 = nullptr;
        }
        v14 = (void *)sub_44B6C0(284);
        v15 = v14;
        v66 = v14;
        v70 = 3;
        if ( v14 != nullptr )
        {
          sub_44E0D0((char *)v14, (int)v67, 1);
          *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
        }
        else
        {
          v15 = nullptr;
        }
        v16 = (int)*(this + 29);
        v67 = v15;
        v70 = -1;
        sub_45FE80(v16, (int)a2, 2, 0, (int)v15, (int)this, 0);
        v73 = *(void (/*thiscall*/ ***)(void *, int))v15;
        v58 = ((int (/*thiscall*/ *)(int **))(*this)[32])(this) + 25;
        v17 = ((int (/*thiscall*/ *)(int **))(*this)[31])(this);
        v18 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v17);
        v73[28](v15, v18);
        (*(void (/*thiscall*/ **)(void *, int **))(*(uint32_t *)v15 + 60))(v15, this);
        sub_4A06D0(v58);
        v3 = a3;
      }
      if ( *(this + 2062) == nullptr )
      {
        v66 = operator new(0x7Cu);
        v70 = 4;
        if ( v66 != nullptr )
          v19 = (int *)sub_4B3C90(0, 0);
        else
          v19 = nullptr;
        *(this + 2062) = v19;
        v20 = *v19;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v20 + 64))(v19) + 36) = 0;
      }
      (*(this + 2062))[11] = sub_47EF20(0, v3, -1, -1, 11);
      (*(void (/*thiscall*/ **)(uint32_t))(**(this + 2062) + 124))(*(this + 2062));
      v21 = *(this + 2062);
      v22 = *v21;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img",
        28,
        0,
        -1);
      sub_418DD0(v59);
      (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v22 + 56))(v21, this, this, 1);
      v23 = this + 2069;
      if ( *(this + 2069) == nullptr )
      {
        v77 = nullptr;
        do
        {
          v24 = 0;
          v25 = v23;
          do
          {
            sprintf(Buffer, "Effect/Animation/ElementalChain/LastElement%d%d.ani", v77, v24);
            v66 = (void *)sub_42FCB0(228);
            v70 = 5;
            if ( v66 != nullptr )
            {
              if ( (unsigned int)*(this + 96) < 0x10 )
                v26 = sub_431920((uint8_t)this + 108, (char)Buffer, 1);
              else
                v26 = sub_431920((char)*(this + 91), (char)Buffer, 1);
            }
            else
            {
              v26 = 0;
            }
            *v25 = v26;
            ++v24;
            ++v25;
            v70 = -1;
          }
          while ( v24 < 2 );
          v27 = (int)++v77 < 4;
          v23 = v25;
        }
        while ( v27 );
        for ( i = 0; i < 5; ++i )
        {
          v78 = 2;
          if ( i != 4 )
            v78 = i;
          v74 = i == 4;
          v29 = v74 + 1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkAppear%d.ani", v74 + 1);
          v30 = (void *)sub_42FCB0(228);
          v66 = v30;
          v70 = 6;
          if ( v30 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v31 = (const char *)(this + 91);
            else
              v31 = (const char *)*(this + 91);
            v32 = sub_4319E0((int)v30, v78, v74, v31, Buffer, 1);
          }
          else
          {
            v32 = 0;
          }
          *(this + i + 2077) = (int *)v32;
          v70 = -1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkStay%d.ani", v29);
          v33 = (void *)sub_42FCB0(228);
          v66 = v33;
          v70 = 7;
          if ( v33 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v34 = (const char *)(this + 91);
            else
              v34 = (const char *)*(this + 91);
            v35 = sub_4319E0((int)v33, v78, v74, v34, Buffer, 1);
          }
          else
          {
            v35 = 0;
          }
          *(this + i + 2082) = (int *)v35;
          v70 = -1;
          sprintf(Buffer, "Effect/Animation/ElementalChain/MarkActivate%d.ani", v29);
          v36 = (void *)sub_42FCB0(228);
          v66 = v36;
          v70 = 8;
          if ( v36 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v37 = (const char *)(this + 91);
            else
              v37 = (const char *)*(this + 91);
            v38 = sub_4319E0((int)v36, v78, v74, v37, Buffer, 1);
          }
          else
          {
            v38 = 0;
          }
          *(this + i + 2087) = (int *)v38;
          v70 = -1;
        }
      }
      v39 = (int *)(this + 2082);
      for ( j = 5; j != 0; --j )
      {
        sub_4926A0(*(v39 - 5));
        sub_4926A0(*v39++);
      }
      break;
    case 30:
      if ( *((uint8_t *)this + 8368) != 0 )
      {
        if ( sub_5DA1C0(this) )
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2093) + 76))(*(this + 2093), 0);
      }
      else
      {
        if ( *(this + 2093) == nullptr )
        {
          v41 = operator new(0x50u);
          v66 = v41;
          v70 = 9;
          if ( v41 != nullptr )
            v42 = (int *)sub_4B1030(v41);
          else
            v42 = nullptr;
          *(this + 2093) = v42;
          v43 = *v42;
          v70 = -1;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v43 + 64))(v42) + 36) = 0;
        }
        v79 = *(this + 2093);
        v44 = sub_47EF20(0, v3, -1, -1, 11);
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v79 + 64))(v79) + 40) = v44;
        v45 = *(this + 2093);
        v46 = *v45;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
          dword_8F84B8,
          "Common/CommonEffect/BuffIcon.img",
          31,
          0,
          -1);
        sub_418DD0(v59);
        (*(void (/*thiscall*/ **)(int *, int **, int **, int))(v46 + 56))(v45, this, this, 1);
        Block = nullptr;
        v64 = nullptr;
        v65 = 0;
        v70 = 10;
        sub_5DD040(this, 0xFFFF, (int)v62, 1);
        v47 = Block;
        v48 = (void **)Block;
        if ( Block != v64 )
        {
          do
            sub_5DB260(this, *v48++);
          while ( v48 != v64 );
        }
        if ( v47 != nullptr )
          j__free(v47);
      }
      break;
    case 37:
      if ( *(this + 2095) == nullptr )
      {
        v49 = operator new(0x70u);
        v66 = v49;
        v70 = 11;
        if ( v49 != nullptr )
          v50 = sub_5DB180(v49);
        else
          v50 = nullptr;
        *(this + 2095) = v50;
        v51 = *v50;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v51 + 64))(v50) + 36) = 0;
      }
      v75 = *(this + 2095);
      v52 = sub_47EF20(0, a3, -1, -1, 11);
      *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v75 + 64))(v75) + 40) = v52;
      v53 = **(this + 2095);
      v76 = *(this + 2095);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img",
        32,
        0,
        -1);
      sub_418DD0(v59);
      (*(void (/*thiscall*/ **)(void *, int **, int **, int))(v53 + 56))(v76, this, this, 1);
      *(this + 2096) = (int *)sub_47EF20(1, a3, -1, -1, 11);
      *((float *)this + 2097) = (double)(int)sub_47EF20(2, a3, -1, -1, 11) * 0.0099999998;
      *((float *)this + 2097) = *((float *)this + 2097) / sub_433F60((int)this, 2);
      break;
    case 40:
      if ( *(this + 2060) == nullptr )
      {
        v54 = operator new(0x50u);
        v66 = v54;
        v70 = 12;
        if ( v54 != nullptr )
          v55 = (int *)sub_4B1030(v54);
        else
          v55 = nullptr;
        *(this + 2060) = v55;
        v56 = *v55;
        v70 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v56 + 64))(v55) + 36) = 0;
      }
      v80 = *(this + 2060);
      v57 = sub_47EF20(0, v3, -1, -1, 11);
      *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v80 + 64))(v80) + 40) = v57;
      v8 = *(this + 2060);
      v11 = *v8;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
        dword_8F84B8,
        "Common/CommonEffect/BuffIcon.img",
        33,
        0,
        -1);
      goto LABEL_96;
    default:
      return;
  }
}


// ------------------------------------------------------------
// 0x5E09B0 sub_5E09B0
// ------------------------------------------------------------
// 调: sub_5E09B0 sub_47E9D0 sub_5DD040 sub_47EF20 sub_422E70
void /*thiscall*/ sub_5E09B0(int *this, uint32_t *a2, int a3)
{
  int v5; // eax
  int v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  unsigned int v11; // ebx
  int v12; // eax
  int *v13; // ecx
  uint32_t *v14; // ecx
  char v15; // al
  uint32_t *v16; // esi
  int v17; // eax
  uint32_t *v18; // esi
  int v19; // eax
  int i; // ebx
  int v21; // eax
  int v22; // ebx
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // ebx
  int v29; // edi
  int v30; // eax
  uint32_t *v31; // ecx
  unsigned int v32; // eax
  int v33; // ebx
  int v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // eax
  unsigned int v38; // ebx
  int v39; // edi
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // ecx
  uint32_t *v46; // ebx
  char *v47; // eax
  char *v48; // edi
  int v49; // edx
  int v50; // ebx
  int v51; // eax
  int v52; // ebx
  int v53; // eax
  int v54; // eax
  int v55; // eax
  void *v56[4]; // [esp+Ch] [ebp-14Ch] BYREF
  unsigned int v57; // [esp+1Ch] [ebp-13Ch]
  int v58; // [esp+20h] [ebp-138h]
  char *v59; // [esp+24h] [ebp-134h]
  int v60; // [esp+28h] [ebp-130h]
  int v61; // [esp+2Ch] [ebp-12Ch]
  char v62[4]; // [esp+30h] [ebp-128h] BYREF
  void *Block; // [esp+34h] [ebp-124h]
  int v64; // [esp+38h] [ebp-120h]
  int v65; // [esp+3Ch] [ebp-11Ch]
  bool v66; // [esp+40h] [ebp-118h] BYREF
  char v67; // [esp+41h] [ebp-117h]
  char v68; // [esp+42h] [ebp-116h]
  int v69; // [esp+43h] [ebp-115h]
  char Buffer[256]; // [esp+48h] [ebp-110h] BYREF
  int v71; // [esp+148h] [ebp-10h]
  int v72; // [esp+154h] [ebp-4h]
  int v73; // [esp+160h] [ebp+8h]
  float v74; // [esp+160h] [ebp+8h]

  v71 = dword_796E50;
  v5 = sub_47E9D0(a2, 2u);
  v6 = sub_5DD040(this, v5, 0, 1);
  v7 = sub_47EF20(2, a3, -1, -1, 11) - v6;
  if ( sub_47EF20(1, a3, -1, -1, 11) >= v7 )
  {
    v9 = sub_47E9D0(a2, 2u);
    v10 = sub_5DD040(this, v9, 0, 1);
    v8 = sub_47EF20(2, a3, -1, -1, 11) - v10;
  }
  else
  {
    v8 = sub_47EF20(1, a3, -1, -1, 11);
  }
  v11 = 0;
  v73 = v8;
  if ( v8 > 0 )
  {
    if ( sub_47E9D0(a2, 7u) > 0 )
    {
      Block = nullptr;
      v64 = 0;
      v65 = 0;
      v72 = 0;
      sub_5DD040(this, 60006, (int)v62, 1);
      if ( Block != nullptr )
        v11 = (v64 - (int)Block) >> 2;
      if ( v11 < sub_47E9D0(a2, 7u) )
      {
        v18 = *((uint32_t **)dword_8F8528 + 7);
        v19 = sub_422E70(2104);
        sub_43BEE0(v18, v19, -6567706, 0, -1);
        goto LABEL_58;
      }
      for ( i = 0; i < sub_47E9D0(a2, 7u); ++i )
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, int))(**((uint32_t **)Block + i) + 560))(
          *((uint32_t *)Block + i),
          13,
          0,
          2,
          1);
      v72 = -1;
      if ( Block != nullptr )
        j__free(Block);
    }
    v60 = sub_47E9D0(a2, 2u);
    v58 = sub_47EF20(0, a3, -1, -1, 11);
    v66 = false;
    v67 = 0;
    v68 = 0;
    v69 = 0;
    v66 = sub_47E9D0(a2, 6u) == 1;
    v67 = 2;
    v68 = a3;
    v69 = sub_47EF20(3, a3, -1, -1, 11);
    v21 = sub_47E9D0(a2, 0);
    if ( v21 < 0 )
      return;
    if ( v21 > 1 )
    {
      if ( v21 == 2 )
      {
        v22 = sub_47E9D0(a2, 5u);
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
          v23 = v22 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        else
          v23 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v22;
        v24 = *this;
        v25 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, bool *, uint32_t))(*this + 152))(
                this,
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                &v66,
                0);
        v26 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v25);
        v27 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 376))(this, v58, v23, v26);
        (*(void (/*thiscall*/ **)(int *, int, int))(v24 + 592))(this, v60, v27);
      }
      return;
    }
    v28 = sub_47E9D0(a2, 5u);
    v61 = v28;
    HIBYTE(a3) = 0;
    Block = nullptr;
    v64 = 0;
    v65 = 0;
    v72 = 1;
    if ( sub_47E9D0(a2, 0) != 0 )
      goto LABEL_38;
    v29 = sub_47E9D0(a2, 1u);
    v30 = sub_5DC330(v56, v28, v29);
    LOBYTE(v72) = 2;
    sub_4E77D0((int)v62, v30);
    LOBYTE(v72) = 1;
    sub_5E5260(v56);
    switch ( v29 )
    {
      case 0:
        HIBYTE(a3) = 1;
        break;
      case 1:
        HIBYTE(a3) = 2;
        break;
      case 2:
        HIBYTE(a3) = 3;
        break;
      case 3:
        HIBYTE(a3) = 4;
        break;
      default:
        break;
    }
    v31 = Block;
    if ( Block != nullptr && (v32 = (v64 - (int)Block) >> 2, v57 = v32, v32 != 0) )
    {
      v38 = 0;
      if ( v73 > 0 )
      {
        while ( v38 < v32 )
        {
          v39 = v31[v38];
          v59 = (char *)*this;
          v40 = (*((int (/*thiscall*/ **)(int *, int, char *, int, int, uint32_t, uint32_t, bool *, uint32_t))v59 + 38))(
                  this,
                  2,
                  (char *)&a3 + 3,
                  1,
                  0xFFFF,
                  0,
                  0,
                  &v66,
                  0);
          v41 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v39 + 124))(v39, 0, v40);
          v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v39 + 120))(v39, v41);
          v43 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 376))(this, v58, v42);
          (*((void (/*thiscall*/ **)(int *, int, int))v59 + 148))(this, v60, v43);
          if ( (int)++v38 >= v73 )
            break;
          v32 = v57;
          v31 = Block;
        }
      }
    }
    else
    {
LABEL_38:
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 100;
      else
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 100;
      v34 = *this;
      v35 = (*(int (/*thiscall*/ **)(int *, int, char *, int, int, uint32_t, uint32_t, bool *, uint32_t))(*this + 152))(
              this,
              2,
              (char *)&a3 + 3,
              1,
              0xFFFF,
              0,
              0,
              &v66,
              0);
      v36 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v35);
      v37 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 376))(this, v58, v33, v36);
      (*(void (/*thiscall*/ **)(int *, int, int))(v34 + 592))(this, v60, v37);
    }
    v44 = 0;
    v74 = (double)v61 * 0.0018867925;
    do
    {
      v61 = v44 + 1;
      sprintf(Buffer, "Effect/Animation/SummonSpirit%d.ani", v44 + 1);
      v59 = (char *)sub_42FCB0(228);
      LOBYTE(v72) = 3;
      if ( v59 != nullptr )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v45) = (uint8_t)this + 108;
        else
          v45 = *(this + 91);
        v46 = (uint32_t *)sub_431920(v45, (char)Buffer, 1);
      }
      else
      {
        v46 = nullptr;
      }
      LOBYTE(v72) = 1;
      sub_4922F0(v46, v74);
      v47 = (char *)sub_44B6C0(284);
      v48 = v47;
      v59 = v47;
      LOBYTE(v72) = 4;
      if ( v47 != nullptr )
      {
        sub_44E0D0(v47, (int)v46, 1);
        *(uint32_t *)v48 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v48 = nullptr;
      }
      v49 = *(uint32_t *)v48;
      LOBYTE(v72) = 1;
      *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v49 + 36))(v48) + 8) = 2;
      sub_45FE80(*(this + 29), (int)v48, 2, 0, (int)v48, 0, 0);
      v50 = *(uint32_t *)v48;
      v51 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v50 + 148))(v48, v51);
      v52 = *(uint32_t *)v48;
      v53 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v54 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v53);
      v55 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v54);
      (*(void (/*thiscall*/ **)(char *, int))(v52 + 112))(v48, v55);
      v44 = v61;
    }
    while ( v61 < 4 );
LABEL_58:
    if ( Block != nullptr )
      j__free(Block);
    return;
  }
  v12 = sub_47E9D0(a2, 2u);
  v13 = &dword_738020;
  while ( v12 != *v13 )
  {
    if ( (int)++v13 >= (int)&dword_738030 )
    {
      v14 = &unk_738040;
      while ( v12 != *v14 )
      {
        if ( (int)++v14 >= (int)&dword_738044 )
        {
          v15 = 0;
          goto LABEL_12;
        }
      }
      break;
    }
  }
  v15 = 1;
LABEL_12:
  v16 = *((uint32_t **)dword_8F8528 + 7);
  v17 = sub_422E70(v15 != 0 ? 2103 : 1);
  sub_43BEE0(v16, v17, -6567706, 0, -1);
}


// ------------------------------------------------------------
// ============================================================
// §B 抓爆/吼 stun
// ============================================================
// 0x5E44C0 sub_5E44C0
// ------------------------------------------------------------
// 调: sub_5E44C0
int /*thiscall*/ sub_5E44C0(int this)
{
  *(uint32_t *)(this + 8216) = -1;
  *(uint32_t *)(this + 8220) = -1;
  *(uint32_t *)(this + 8224) = 0;
  *(uint8_t *)(this + 8228) = 0;
  *(uint32_t *)(this + 8232) = 0;
  *(uint32_t *)(this + 8240) = 0;
  *(uint32_t *)(this + 8244) = 0;
  *(uint32_t *)(this + 8248) = 0;
  *(uint32_t *)(this + 8252) = 0;
  *(uint32_t *)(this + 8256) = 0;
  *(uint32_t *)(this + 8260) = 0;
  *(uint32_t *)(this + 8264) = 1000;
  *(uint32_t *)(this + 8268) = 0;
  *(uint32_t *)(this + 8272) = 0;
  *(uint8_t *)(this + 8276) = 0;
  *(uint32_t *)(this + 8280) = 0;
  *(uint32_t *)(this + 8284) = 0;
  *(uint8_t *)(this + 8292) = 0;
  *(uint32_t *)(this + 8296) = 0;
  *(uint32_t *)(this + 8300) = 0;
  *(uint32_t *)(this + 8304) = 0;
  *(uint32_t *)(this + 8308) = 0;
  *(uint32_t *)(this + 8312) = 0;
  *(uint32_t *)(this + 8316) = 4;
  *(uint32_t *)(this + 8320) = 0;
  *(uint8_t *)(this + 8324) = 0;
  *(uint8_t *)(this + 8325) = 0;
  *(uint8_t *)(this + 8326) = 0;
  *(uint32_t *)(this + 8328) = 0;
  *(uint8_t *)(this + 8332) = 0;
  *(uint8_t *)(this + 8333) = 0;
  *(uint8_t *)(this + 8334) = 0;
  *(uint32_t *)(this + 8336) = 0;
  *(uint32_t *)(this + 8340) = 0;
  *(uint32_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8348) = 0;
  *(uint32_t *)(this + 8352) = 0;
  *(uint32_t *)(this + 8356) = 0;
  *(uint8_t *)(this + 8360) = 0;
  *(uint32_t *)(this + 8364) = 0;
  *(uint32_t *)(this + 8368) = 0;
  *(uint32_t *)(this + 8372) = 0;
  *(uint8_t *)(this + 8376) = 0;
  *(uint8_t *)(this + 8377) = 0;
  *(uint32_t *)(this + 8380) = 0;
  *(uint8_t *)(this + 8384) = 0;
  *(uint32_t *)(this + 8388) = 0;
  *(uint8_t *)(this + 8392) = 0;
  *(uint32_t *)(this + 8396) = 0;
  *(uint32_t *)(this + 8400) = 0;
  *(uint32_t *)(this + 8404) = 0;
  *(uint32_t *)(this + 8412) = 0;
  *(uint32_t *)(this + 8432) = 0;
  *(uint8_t *)(this + 8436) = 0;
  *(uint8_t *)(this + 8437) = 0;
  *(uint32_t *)(this + 8444) = 0;
  *(uint32_t *)(this + 8448) = 0;
  *(uint32_t *)(this + 8452) = 0;
  *(uint32_t *)(this + 8456) = 0;
  *(uint32_t *)(this + 8460) = 1065353216;
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;
  *(uint32_t *)(this + 8408) = 0;
  *(uint32_t *)(this + 8472) = 0;
  *(uint32_t *)(this + 8480) = 0;
  *(uint8_t *)(this + 8476) = 0;
  *(uint8_t *)(this + 8477) = 0;
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 0;
  *(uint32_t *)(this + 8492) = 0;
  *(uint32_t *)(this + 8496) = 0;
  *(uint32_t *)(this + 8500) = 0;
  *(uint32_t *)(this + 8504) = 0;
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 0;
  *(uint32_t *)(this + 8516) = 0;
  *(uint32_t *)(this + 8520) = 0;
  *(uint32_t *)(this + 8524) = 0;
  *(uint32_t *)(this + 8528) = 0;
  *(uint32_t *)(this + 8532) = 0;
  *(uint32_t *)(this + 8536) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5E46C0 CNFighter__vmt1F8
// ------------------------------------------------------------
// 调: sub_47DCD0
int /*thiscall*/ CNFighter__vmt1F8(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  int *v6; // eax

  if ( *(this + 1639) == 16
    && *(this + 2060) == 4
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0
    && (uint32_t *)dword_8F7C04 == this
    && (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 776))(a2, 0) != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 772))(a2, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 28))(v5) < 200 )
    {
      v6 = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 4);
      sub_47DCD0(v6, (int)this, -1);
    }
  }
  return IRDActiveObject__vmt1F8(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x5E4750 CNFighter__vmt200
// ------------------------------------------------------------
// 证: 叶子函数（5 行，无外调无字符串）
int /*stdcall*/ CNFighter__vmt200(int a1, int a2, int a3)
{
  return IRDCharacter__vmt200(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x5E47A0 CNFighter__vmt158
// ------------------------------------------------------------
// 证: 叶子函数（15 行，无外调无字符串）
int /*thiscall*/ CNFighter__vmt158(int this, int a2)
{
  int result; // eax
  int v4; // ecx

  result = IRDCharacter__vmt158(this, a2);
  v4 = *(uint32_t *)(this + 8456);
  if ( v4 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4);
    if ( (uint8_t)result != 0 )
      *(float *)(this + 524) = *(float *)(this + 8460) * *(float *)(this + 524);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5E4DC0 sub_5E4DC0
// ------------------------------------------------------------
// 调: sub_5E4DC0 sub_4B1030 sub_64FC40 sub_650D30
uint32_t */*thiscall*/ sub_5E4DC0(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNSuplexed;
  sub_64FC40(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5E4E20 CNSuplexed__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（6 行，无外调无字符串）
char /*thiscall*/ CNSuplexed__vmt78(uint8_t *this, char a2)
{
  *(this + 84) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x5E4E40 CNSuplexed__vmt0
// ------------------------------------------------------------
// 调: sub_5E4E70
void */*thiscall*/ CNSuplexed__vmt0(void *Block, char a2)
{
  sub_5E4E70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E4E70 sub_5E4E70
// ------------------------------------------------------------
// 调: sub_5E4E70 sub_5F6640
int /*thiscall*/ sub_5E4E70(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNSuplexed;
  nullsub_3();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5E4ED0 sub_5E4ED0
// ------------------------------------------------------------
// 调: sub_5E4ED0 sub_4B1030 sub_6500E0 sub_650D30
uint32_t */*thiscall*/ sub_5E4ED0(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNGrabbedExplosion;
  sub_6500E0(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5E4F30 CNGrabbedExplosion__vmt0
// ------------------------------------------------------------
// 调: sub_5E4F60
void */*thiscall*/ CNGrabbedExplosion__vmt0(void *Block, char a2)
{
  sub_5E4F60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E4F60 sub_5E4F60
// ------------------------------------------------------------
// 调: sub_5E4F60 sub_5F6640
int /*thiscall*/ sub_5E4F60(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNGrabbedExplosion;
  nullsub_3();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5E4FC0 sub_5E4FC0
// ------------------------------------------------------------
// 调: sub_5E4FC0 sub_4B1030 sub_650340 sub_650D30
uint32_t */*thiscall*/ sub_5E4FC0(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNThrownEnemy;
  sub_650340(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5E5020 CNThrownEnemy__vmt0
// ------------------------------------------------------------
// 调: sub_5E5050
void */*thiscall*/ CNThrownEnemy__vmt0(void *Block, char a2)
{
  sub_5E5050();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E5050 sub_5E5050
// ------------------------------------------------------------
// 调: sub_5E5050 sub_5F6640
int /*thiscall*/ sub_5E5050(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNThrownEnemy;
  nullsub_3();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5E50B0 sub_5E50B0
// ------------------------------------------------------------
// 调: sub_5E50B0 sub_47E720 sub_47E9D0
int sub_5E50B0()
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(1, 1u);
  dword_795948 = sub_47E9D0(v0, 0);
  v1 = (uint32_t *)sub_47E720(1, 1u);
  dword_79594C = sub_47E9D0(v1, 1u);
  v2 = (uint32_t *)sub_47E720(1, 0x36u);
  result = sub_47E9D0(v2, 0);
  dword_9B9348 = result;
  return result;
}



// ------------------------------------------------------------
// 0x5E51C0 sub_5E51C0
// ------------------------------------------------------------
// 调: sub_5E51C0 sub_623C10
int /*stdcall*/ sub_5E51C0(int a1, int a2, int a3)
{
  sub_623C10(a1, a2, a3);
  return a1 + 12 * a2;
}



// ------------------------------------------------------------
// 0x5E51F0 sub_5E51F0
// ------------------------------------------------------------
// 调: sub_5E51F0 sub_63A7C0
int /*stdcall*/ sub_5E51F0(int a1, int a2, int a3)
{
  sub_63A7C0(a1, a2, a3);
  return a1 + 8 * a2;
}



// ------------------------------------------------------------
// 0x5E5220 sub_5E5220
// ------------------------------------------------------------
// 调: sub_5E5220
uint32_t */*thiscall*/ sub_5E5220(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // eax
  uint32_t *v5; // edx

  v3 = (uint32_t *)*(this + 2);
  v4 = a3 + 2;
  if ( a3 + 2 != v3 )
  {
    v5 = a3;
    do
    {
      *v5 = *v4;
      v5[1] = v4[1];
      v4 += 2;
      v5 += 2;
    }
    while ( v4 != v3 );
  }
  *(this + 2) -= 8;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x5E5260 sub_5E5260
// ------------------------------------------------------------
// 调: sub_5E5260
void /*thiscall*/ sub_5E5260(void **this)
{
  if ( *(this + 1) != nullptr )
    j__free(*(this + 1));
  *(this + 1) = nullptr;
  *(this + 2) = nullptr;
  *(this + 3) = nullptr;
}



// ------------------------------------------------------------
// 0x5E5290 CNFighter__vmt12C
// ------------------------------------------------------------
// 证: 叶子函数（47 行，无外调无字符串）
uint32_t */*thiscall*/ CNFighter__vmt12C(uint32_t *this, uint32_t *a2)
{
  uint32_t *result; // eax
  uint32_t *v4; // ecx
  uint32_t *v5; // edx
  uint32_t *v6; // ecx

  IRDCharacter__vmt12C(a2);
  if ( (uint32_t *)*(this + 2075) == a2 )
    *(this + 2075) = 0;
  if ( (uint32_t *)*(this + 2089) == a2 )
    *(this + 2089) = 0;
  result = (uint32_t *)*(this + 2105);
  if ( result != (uint32_t *)*(this + 2106) )
  {
    while ( 1 )
    {
      v4 = (uint32_t *)*result;
      result += 2;
      if ( v4 == a2 )
        break;
      if ( result == (uint32_t *)*(this + 2106) )
        goto LABEL_13;
    }
    v5 = (uint32_t *)*(this + 2106);
    if ( result != v5 )
    {
      v6 = result - 2;
      do
      {
        *v6 = *result;
        v6[1] = result[1];
        result += 2;
        v6 += 2;
      }
      while ( result != v5 );
    }
    *(this + 2106) -= 8;
  }
LABEL_13:
  if ( a2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 13);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5E5330 sub_5E5330
// ------------------------------------------------------------
// 调: sub_5E5330
void /*thiscall*/ sub_5E5330(int this)
{
  if ( *(uint32_t *)(this + 84) != 0 )
    j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
}



// ------------------------------------------------------------
// 0x5E5360 sub_5E5360
// ------------------------------------------------------------
// 调: sub_5E5360 sub_579200 sub_44BD30 sub_5E51F0 sub_41FEB0
void /*thiscall*/ sub_5E5360(int this, int a2, unsigned int a3, int a4)
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
      sub_579200(this);
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
// 0x5E55B0 sub_5E55B0
// ------------------------------------------------------------
// 调: sub_5E55B0 sub_50F360 sub_59EE30 sub_504450 sub_5043B0
int /*thiscall*/ sub_5E55B0(int *this, int a2, unsigned int a3, int *Block)
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
      sub_50F360(this);
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
// 0x5E5860 sub_5E5860
// ------------------------------------------------------------
// 调: sub_5E5860 sub_50F360 sub_44BD30 sub_5E51F0 sub_41FEB0
void /*thiscall*/ sub_5E5860(int this, int a2, unsigned int a3, int a4)
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
// 0x5E5AB0 sub_5E5AB0
// ------------------------------------------------------------
// 调: sub_5E5AB0 sub_5E55B0
uint32_t */*thiscall*/ sub_5E5AB0(int *this, uint32_t *a2, int a3, int *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 12 != 0 )
    v6 = (a3 - v5) / 12;
  else
    v6 = 0;
  sub_5E55B0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 12 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x5E5B20 sub_5E5B20
// ------------------------------------------------------------
// 调: sub_5E5B20 sub_4B1030 sub_603900 sub_603A50
uint32_t */*thiscall*/ sub_5E5B20(uint32_t *this, int a2, char a3, void *Src)
{
  sub_4B1030(this);
  *this = &vftbl_CNChangeElementTolerance;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 32) = 15;
  *(this + 31) = 0;
  *((uint8_t *)this + 108) = 0;
  sub_603900(this);
  sub_603A50(a2, a3, Src);
  return this;
}



// ------------------------------------------------------------
// 0x5E5BA0 sub_5E5BA0
// ------------------------------------------------------------
// 调: sub_5E5BA0 sub_4B1030 sub_6037B0
uint32_t */*thiscall*/ sub_5E5BA0(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNChangeActiveProperty;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  nullsub_3();
  sub_6037B0(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5E5C10 sub_5E5C10
// ------------------------------------------------------------
// 调: sub_5E5C10 sub_4B1030 sub_650540 sub_650560
uint32_t */*thiscall*/ sub_5E5C10(uint32_t *this, int a2, float a3, int a4, int a5, int a6, int a7)
{
  sub_4B1030(this);
  *this = &vftbl_CNEnchantActiveStatus;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  sub_650540(this);
  sub_650560(a2, a3, a4, a5, a6, a7);
  return this;
}



// ------------------------------------------------------------
// 0x5E5C90 CNEnchantActiveStatus__vmt78
// ------------------------------------------------------------
// 证: 叶子函数（11 行，无外调无字符串）
char /*thiscall*/ CNEnchantActiveStatus__vmt78(int this, int a2, int a3, int a4, char a5, int a6, char a7)
{
  *(uint32_t *)(this + 80) = a2;
  *(float *)(this + 84) = (float)a3;
  *(uint32_t *)(this + 88) = a4;
  *(uint8_t *)(this + 92) = a5;
  *(uint32_t *)(this + 44) = a6;
  *(uint8_t *)(this + 93) = a7;
  return a7;
}



// ------------------------------------------------------------
// 0x5E5CC0 CNEnchantActiveStatus__vmt0
// ------------------------------------------------------------
// 调: sub_5E5CF0
void */*thiscall*/ CNEnchantActiveStatus__vmt0(void *Block, char a2)
{
  sub_5E5CF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5E5CF0 sub_5E5CF0
// ------------------------------------------------------------
// 调: sub_5E5CF0 sub_5F6640
int /*thiscall*/ sub_5E5CF0(void **this)
{
  int result; // eax

  *this = &vftbl_CNEnchantActiveStatus;
  nullsub_3();
  if ( *(this + 27) != nullptr )
    j__free(*(this + 27));
  *(this + 27) = nullptr;
  *(this + 28) = nullptr;
  *(this + 29) = nullptr;
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x5E5D70 sub_5E5D70
// ------------------------------------------------------------
// 调: sub_5E5D70 sub_63A7C0 sub_5E5360
void /*thiscall*/ sub_5E5D70(int this, int a2)
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
    sub_5E5360(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x5E5DE0 sub_5E5DE0
// ------------------------------------------------------------
// 调: sub_5E5DE0 sub_5E5AB0 sub_623C10
uint32_t */*thiscall*/ sub_5E5DE0(int *this, int *Block)
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
    return sub_5E5AB0(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_623C10(v5, 1, Block);
  *(this + 2) = v5 + 12;
  return result;
}



// ------------------------------------------------------------
// 0x5E5E60 sub_5E5E60
// ------------------------------------------------------------
// 调: sub_5E5E60 sub_63A7C0 sub_5E5860
void /*thiscall*/ sub_5E5E60(int this, int a2)
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
    sub_5E5860(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x5E5ED0 sub_5E5ED0
// ------------------------------------------------------------
// 调: sub_5E5ED0 sub_5E5DE0
uint32_t */*thiscall*/ sub_5E5ED0(int *this, int a2, char a3, int a4)
{
  int Block; // [esp+0h] [ebp-Ch] BYREF
  char v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  v6 = a3;
  Block = a2;
  v7 = a4;
  return sub_5E5DE0(this + 21, &Block);
}



// ------------------------------------------------------------
// 0x5E5F00 sub_5E5F00
// ------------------------------------------------------------
// 调: sub_5E5F00 sub_5E5E60
void /*thiscall*/ sub_5E5F00(void *this, int a2, int a3)
{
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v3[0] = a2;
  v3[1] = a3;
  sub_5E5E60((int)this + 80, (int)v3);
}



// ------------------------------------------------------------
// 0x5E5F30 sub_5E5F30
// ------------------------------------------------------------
// 证: "R_FT_KICK_JUMP" | "R_FT_DMG" | "R_FT_DIE" | "FT_JUMP"
// 调: sub_5E5F30 sub_430C80 sub_4015C0
int /*thiscall*/ sub_5E5F30(int this)
{
  int v2; // edi
  int v3; // eax
  unsigned int v4; // edx
  uint32_t *v5; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // edx
  unsigned int v10; // ecx
  uint32_t *v11; // eax
  int v12; // edx
  unsigned int v13; // ecx
  uint32_t *v14; // eax
  int v16; // [esp+Ch] [ebp-4h] BYREF

  v2 = this + 7892;
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6868) = 7;
  *(uint32_t *)(this + 6872) = 13;
  v3 = *(uint32_t *)(this + 7896);
  v16 = 1;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 7900) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 7904) - v3) >> 2 )
  {
    v5 = *(uint32_t **)(this + 7900);
    *v5 = 1;
    *(uint32_t *)(this + 7900) = v5 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 7900), 1, (int)&v16);
  }
  v6 = *(uint32_t *)(v2 + 4);
  v16 = 1;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(v2 + 8) - v6) >> 2;
  else
    v7 = 0;
  if ( v6 != 0 && v7 < (*(uint32_t *)(v2 + 12) - v6) >> 2 )
  {
    v8 = *(uint32_t **)(v2 + 8);
    *v8 = 1;
    *(uint32_t *)(v2 + 8) = v8 + 1;
  }
  else
  {
    sub_430C80(*(void **)(v2 + 8), 1, (int)&v16);
  }
  v9 = *(uint32_t *)(v2 + 4);
  v16 = 4;
  if ( v9 != 0 )
    v10 = (*(uint32_t *)(v2 + 8) - v9) >> 2;
  else
    v10 = 0;
  if ( v9 != 0 && v10 < (*(uint32_t *)(v2 + 12) - v9) >> 2 )
  {
    v11 = *(uint32_t **)(v2 + 8);
    *v11 = 4;
    *(uint32_t *)(v2 + 8) = v11 + 1;
  }
  else
  {
    sub_430C80(*(void **)(v2 + 8), 1, (int)&v16);
  }
  v12 = *(uint32_t *)(v2 + 4);
  v16 = 3;
  if ( v12 != 0 )
    v13 = (*(uint32_t *)(v2 + 8) - v12) >> 2;
  else
    v13 = 0;
  if ( v12 != 0 && v13 < (*(uint32_t *)(v2 + 12) - v12) >> 2 )
  {
    v14 = *(uint32_t **)(v2 + 8);
    *v14 = 3;
    *(uint32_t *)(v2 + 8) = v14 + 1;
  }
  else
  {
    sub_430C80(*(void **)(v2 + 8), 1, (int)&v16);
  }
  *(uint32_t *)(this + 7908) = 600;
  *(uint32_t *)(this + 7912) = -10000;
  *(uint32_t *)(this + 7916) = 1200;
  *(uint32_t *)(this + 7920) = -10000;
  *(uint32_t *)(this + 7844) = 65;
  *(uint32_t *)(this + 7848) = 50;
  *(uint32_t *)(this + 7852) = 1;
  *(uint32_t *)(this + 7928) = 2;
  sub_4015C0("R_FT_KICK_JUMP", 0xEu);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("R_FT_DMG", 8u);
  sub_4015C0("R_FT_DIE", 8u);
  sub_4015C0("FT_JUMP", 7u);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("FT_BACKSTEP", 0xBu);
  sub_4015C0("R_FT_PAM_BREAST", 0xFu);
  sub_4015C0("FT_NOMANA", 9u);
  sub_4015C0("FT_COMMAND_PET", 0xEu);
  return sub_4015C0("FT_THROW", 8u);
}


// ------------------------------------------------------------
// 0x5E61C0 sub_5E61C0
// ------------------------------------------------------------
// 调: sub_5E61C0 sub_53FE50 sub_4B3C90 sub_47EF20 sub_5E5B20
void /*thiscall*/ sub_5E61C0(int *this, void *a2, void *Block)
{
  void *v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  uint32_t *v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  uint32_t *v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  uint32_t *v17; // eax
  int v18; // eax
  int v19; // ecx
  void *v20; // eax
  int v21; // eax
  int v22; // ecx
  float v23; // [esp+4h] [ebp-18h]
  unsigned int v24; // [esp+8h] [ebp-14h]
  void *Blocka; // [esp+28h] [ebp+Ch]

  sub_4B3E70(this, a2, (int)Block);
  if ( a2 == (void *)7 )
  {
    if ( (int)Block <= 0 )
    {
      v6 = *(this + 2130);
      if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6) != 0 )
        sub_53FE50(*(this + 2130));
    }
    else
    {
      if ( *(this + 2130) == 0 )
      {
        v4 = operator new(0x7Cu);
        if ( v4 != nullptr )
          v5 = sub_4B3C90((int)v4, 0, 0);
        else
          v5 = 0;
        *(this + 2130) = v5;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 64))(v5) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 7);
      Blocka = (void *)sub_47EF20(0, Block, -1, -1, 11);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2130) + 124))(*(this + 2130));
      v23 = (float)(int)Blocka;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2130) + 120))(5, 0, LODWORD(v23));
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2130) + 56))(
        *(this + 2130),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
  else if ( a2 == (void *)29 )
  {
    if ( (int)Block <= 0 )
    {
      v11 = *(this + 2131);
      if ( v11 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 80))(v11) != 0 )
        sub_53FE50(*(this + 2131));
    }
    else
    {
      if ( *(this + 2131) == 0 )
      {
        if ( operator new(0x84u) != nullptr )
          v7 = sub_5E5B20(0, 0, nullptr);
        else
          v7 = 0;
        *(this + 2131) = v7;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 64))(v7) + 36) = 0;
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 29);
        v9 = sub_47E9D0(v8, 0);
        sub_5E5ED0(3, 0, v9);
        v10 = sub_47E9D0(v8, 1u);
        sub_5E5ED0(2, 0, v10);
      }
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2131) + 56))(
        *(this + 2131),
        this,
        this,
        0,
        0,
        0,
        -1);
    }
  }
  else if ( a2 == (void *)32 )
  {
    if ( (int)Block <= 0 )
    {
      v15 = *(this + 2132);
      if ( v15 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 80))(v15) != 0 )
        sub_53FE50(*(this + 2132));
    }
    else
    {
      if ( *(this + 2132) == 0 )
      {
        if ( operator new(0x60u) != nullptr )
          v12 = sub_5E5BA0(0);
        else
          v12 = 0;
        *(this + 2132) = v12;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 64))(v12) + 36) = 0;
      }
      sub_5E5330(*(this + 2132));
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 32, 0);
      v14 = sub_47E9D0(v13, v24);
      sub_5E5F00(2, v14);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2132) + 56))(
        *(this + 2132),
        this,
        this,
        0,
        0,
        0);
    }
  }
  else if ( a2 == (void *)35 )
  {
    if ( (int)Block <= 0 )
    {
      v19 = *(this + 2133);
      if ( v19 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 80))(v19) != 0 )
        sub_53FE50(*(this + 2133));
    }
    else
    {
      if ( *(this + 2133) == 0 )
      {
        if ( operator new(0x60u) != nullptr )
          v16 = sub_5E5BA0(0);
        else
          v16 = 0;
        *(this + 2133) = v16;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 64))(v16) + 36) = 0;
      }
      sub_5E5330(*(this + 2133));
      v17 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 35, 0);
      v18 = sub_47E9D0(v17, v24);
      sub_5E5F00(5, v18);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2133) + 56))(
        *(this + 2133),
        this,
        this,
        0,
        0,
        0);
    }
  }
  else if ( a2 == (void *)45 )
  {
    if ( (int)Block <= 0 )
    {
      v22 = *(this + 2134);
      if ( v22 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v22 + 80))(v22) != 0 )
        sub_53FE50(*(this + 2134));
    }
    else
    {
      if ( *(this + 2134) == 0 )
      {
        v20 = operator new(0x88u);
        if ( v20 != nullptr )
          v21 = sub_4C2820((int)v20, 1, 45);
        else
          v21 = 0;
        *(this + 2134) = v21;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 64))(v21) + 36) = 0;
      }
      sub_5F9DD0(Block);
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2134) + 56))(
        *(this + 2134),
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
// 0x5E6640 sub_5E6640
// ------------------------------------------------------------
// 调: sub_5E6640 sub_430C80
void */*thiscall*/ sub_5E6640(uint32_t *this)
{
  uint32_t *v2; // edi
  int i; // ebx
  void *result; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  bool v11; // zf
  int v12; // eax
  char v13; // al
  int v14; // edx
  int v15; // ecx
  uint8_t v16[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  void *Src; // [esp+14h] [ebp-20h]
  int v19; // [esp+18h] [ebp-1Ch]
  int v20; // [esp+1Ch] [ebp-18h] BYREF
  int v21; // [esp+20h] [ebp-14h] BYREF
  int v22; // [esp+24h] [ebp-10h] BYREF
  int v23; // [esp+30h] [ebp-4h]

  v2 = this + 2121;
  for ( i = 3; i != 0; --i )
    result = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *v2++);
  v5 = *(this + 2075);
  if ( v5 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 308))(v5) != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2075) + 120))(*(this + 2075));
      v7 = *(this + 2075);
      v21 = v6;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
      v9 = *(this + 2075);
      v22 = v8;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 128))(v9);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2075) + 136))(
             *(this + 2075),
             v21,
             v22,
             0) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2075) + 132))(*(this + 2075), v10) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2075) + 108))(*(this + 2075), v21, v22, v10);
      }
      else
      {
        v11 = (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2075)
                                                                                               + 140))(
                *(this + 2075),
                &v21,
                &v22,
                v21,
                v22,
                100,
                1,
                1) == 0;
        v12 = *(uint32_t *)*(this + 2075);
        if ( v11 )
        {
          v13 = (*(int (/*cdecl*/ **)(int))(v12 + 132))(v10);
          v14 = *(uint32_t *)*(this + 2075);
          if ( v13 != 0 )
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(v14 + 108))(*(this + 2076), *(this + 2077), v10);
          else
            (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(v14 + 108))(*(this + 2076), *(this + 2077), *(this + 2078));
        }
        else
        {
          (*(void (/*stdcall*/ **)(int, int))(v12 + 108))(v21, v22);
        }
      }
      Block = nullptr;
      Src = nullptr;
      v19 = 0;
      v23 = 0;
      v20 = 4;
      sub_430C80(nullptr, 1, (int)&v20);
      v20 = 0;
      sub_430C80(nullptr, 1, (int)&v20);
      v20 = 1;
      sub_430C80(nullptr, 1, (int)&v20);
      v20 = 400;
      sub_430C80(nullptr, 1, (int)&v20);
      v20 = 400;
      sub_430C80(nullptr, 1, (int)&v20);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(*(uint32_t *)*(this + 2075) + 560))(
        *(this + 2075),
        4,
        v16,
        2,
        0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2075) + 564))(*(this + 2075));
      v23 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      Src = nullptr;
      v19 = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2075) + 596))(*(this + 2075), 1);
    v15 = *(this + 2120);
    *(this + 2075) = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v15 + 76))(v15, 0);
    return sub_432EA0("TOMBTONE_STUCK", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x5E6920 sub_5E6920
// ------------------------------------------------------------
// 调: sub_5E6920 sub_431230 sub_47E9D0 sub_47EFD0
int /*usercall*/ sub_5E6920@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  uint32_t *v5; // ecx
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // eax
  uint32_t *v11; // ecx
  uint32_t *v12; // eax
  char v13; // al
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  char v19; // al
  uint32_t *v20; // edi
  int v21; // eax
  int v22; // [esp-24h] [ebp-94h]
  int v23; // [esp-20h] [ebp-90h]
  int v24; // [esp-1Ch] [ebp-8Ch]
  int v25; // [esp-18h] [ebp-88h]
  uint8_t v26[4]; // [esp+4h] [ebp-6Ch] BYREF
  void *Block; // [esp+8h] [ebp-68h]
  int v28; // [esp+Ch] [ebp-64h]
  int v29; // [esp+10h] [ebp-60h]
  int v30; // [esp+14h] [ebp-5Ch] BYREF
  int v31; // [esp+18h] [ebp-58h] BYREF
  int v32; // [esp+1Ch] [ebp-54h] BYREF
  int v33; // [esp+20h] [ebp-50h] BYREF
  int16_t v34; // [esp+24h] [ebp-4Ch]
  int16_t v35; // [esp+26h] [ebp-4Ah]
  int16_t v36; // [esp+28h] [ebp-48h]
  int v37; // [esp+2Ah] [ebp-46h]
  int v38; // [esp+2Eh] [ebp-42h]
  int16_t v39; // [esp+32h] [ebp-3Eh]
  char v40; // [esp+34h] [ebp-3Ch]
  int v41; // [esp+60h] [ebp-10h]
  int v42; // [esp+6Ch] [ebp-4h]

  result = dword_796E50;
  v5 = (uint32_t *)a1[2075];
  v41 = dword_796E50;
  if ( v5 != nullptr )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 308))(v5) == 0 )
    {
LABEL_13:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[2102] + 76))(a1[2102], 0);
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[2075] + 596))(a1[2075], 1);
      a1[2075] = 0;
      return result;
    }
    v6 = (char *)(*(int (/*thiscall*/ **)(int *, int, int, int))(*a1 + 1160))(a1, 49, a3, a2);
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 1140))(a1, 49);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[2075] + 120))(a1[2075]);
    v9 = (uint32_t *)a1[2075];
    v31 = v8;
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v9 + 124))(v9);
    v11 = (uint32_t *)a1[2075];
    v30 = v10;
    v32 = (*(int (/*thiscall*/ **)(uint32_t *))(*v11 + 128))(v11);
    v31 += (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) != 0 ? 40 : -40;
    v32 -= 10;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)a1[2075] + 136))(a1[2075], v31, v30, 0) != 0
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[2075] + 132))(a1[2075], v32) != 0 )
    {
      v12 = (uint32_t *)v31;
    }
    else
    {
      v13 = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(*(uint32_t *)a1[2075] + 140))(
              a1[2075],
              &v31,
              &v30,
              v31,
              v30,
              100,
              1,
              1);
      v14 = *(uint32_t *)a1[2075];
      if ( v13 != 0 )
      {
        v12 = (uint32_t *)v31;
LABEL_10:
        (*(void (/*stdcall*/ **)(uint32_t *))(v14 + 108))(v12);
        Block = nullptr;
        v28 = 0;
        v29 = 0;
        v42 = 0;
        v32 = 4;
        sub_431230((int)v26, &v32);
        v32 = 0;
        sub_431230((int)v26, &v32);
        v32 = 1;
        sub_431230((int)v26, &v32);
        v32 = sub_47E9D0(v6, 1u);
        sub_431230((int)v26, &v32);
        v32 = sub_47E9D0(v6, 2u);
        sub_431230((int)v26, &v32);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, int, uint32_t))(*(uint32_t *)a1[2075] + 560))(a1[2075], 4, v26, 2, 0);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1[2075] + 564))(a1[2075]);
        v15 = (*(int (/*thiscall*/ **)(int *))(*a1 + 388))(a1);
        v33 = sub_47EFD0(v6, COERCE_FLOAT(2), v7, v15, v15, 0);
        v34 = sub_47E9D0(v6, 4u);
        v35 = sub_47E9D0(v6, 3u);
        v16 = *a1;
        v36 = -1;
        v17 = (*(int (/*thiscall*/ **)(int *))(v16 + 388))(a1);
        v37 = sub_47EFD0(v6, 0.0, v7, v17, v17, 0);
        v18 = (*(int (/*thiscall*/ **)(int *))(*a1 + 388))(a1);
        v38 = sub_47EFD0(v6, COERCE_FLOAT(1), v7, v18, v18, 0);
        v39 = sub_47E9D0(v6, 5u);
        v19 = sub_47E9D0(v6, 6u);
        v20 = (uint32_t *)a1[2075];
        v40 = v19;
        v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 152))(v20);
        v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 128))(v20);
        v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 124))(v20);
        v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 120))(v20);
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*v20 + 56))(v20);
        sub_4E4A50(a1, 48028, v21, v22, v23, v24, v25, 0, 21, &v33);
        v42 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        v28 = 0;
        v29 = 0;
        goto LABEL_13;
      }
      (*(void (/*stdcall*/ **)(int))(v14 + 132))(v32);
      v12 = (uint32_t *)a1[2076];
    }
    v14 = *(uint32_t *)a1[2075];
    goto LABEL_10;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5E6C50 sub_5E6C50
// ------------------------------------------------------------
// 调: sub_5E6C50 sub_42AF90 sub_657740
int /*thiscall*/ sub_5E6C50(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void ***v3; // edi
  void **v4; // ebx
  void ***v5; // edi
  void **v6; // ebx
  int v7; // edi
  void **v8; // edi
  void (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  void **v11; // edi
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  void ***v17; // edi
  void **v18; // ebx
  int result; // eax
  int v20; // edi
  int (/*thiscall*/ ***v21)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v23)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v24)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v25)(uint32_t, int); // ecx
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int v28; // [esp+Ch] [ebp-4h]

  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8320);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 8320) = 0;
  v3 = (void ***)(this + 8268);
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
  v5 = (void ***)(this + 8336);
  for ( j = 2; j != 0; --j )
  {
    v6 = *v5;
    if ( *v5 != nullptr )
    {
      sub_42AF90(*v5);
      sub_657740(v6, 228);
    }
    *v5++ = nullptr;
  }
  v7 = *(uint32_t *)(this + 8380);
  if ( v7 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8380));
    sub_657740(v7, 228);
  }
  v8 = *(void ***)(this + 8388);
  *(uint32_t *)(this + 8380) = 0;
  if ( v8 != nullptr )
  {
    sub_42AF90(v8);
    sub_657740(v8, 228);
  }
  v9 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8400);
  *(uint32_t *)(this + 8388) = 0;
  if ( v9 != nullptr )
    (**v9)(v9, 1);
  v10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8408);
  *(uint32_t *)(this + 8400) = 0;
  if ( v10 != nullptr )
    (**v10)(v10, 1);
  v11 = *(void ***)(this + 8412);
  *(uint32_t *)(this + 8408) = 0;
  if ( v11 != nullptr )
  {
    sub_42AF90(v11);
    sub_657740(v11, 228);
  }
  v12 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8452);
  *(uint32_t *)(this + 8412) = 0;
  if ( v12 != nullptr )
    (**v12)(v12, 1);
  v13 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8456);
  *(uint32_t *)(this + 8452) = 0;
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  v14 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8464);
  *(uint32_t *)(this + 8456) = 0;
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  v15 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8468);
  *(uint32_t *)(this + 8464) = 0;
  if ( v15 != nullptr )
    (**v15)(v15, 1);
  v16 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8480);
  *(uint32_t *)(this + 8468) = 0;
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  *(uint32_t *)(this + 8480) = 0;
  v17 = (void ***)(this + 8484);
  v28 = 3;
  do
  {
    v18 = *v17;
    if ( *v17 != nullptr )
    {
      sub_42AF90(*v17);
      sub_657740(v18, 228);
    }
    *v17++ = nullptr;
    result = v28 - 1;
    v28 = result;
  }
  while ( result != 0 );
  v20 = *(uint32_t *)(this + 8512);
  if ( v20 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8512));
    result = sub_657740(v20, 228);
  }
  v21 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8520);
  *(uint32_t *)(this + 8512) = 0;
  if ( v21 != nullptr )
    result = (**v21)(v21, 1);
  v22 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8524);
  *(uint32_t *)(this + 8520) = 0;
  if ( v22 != nullptr )
    result = (**v22)(v22, 1);
  v23 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8528);
  *(uint32_t *)(this + 8524) = 0;
  if ( v23 != nullptr )
    result = (**v23)(v23, 1);
  v24 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8532);
  *(uint32_t *)(this + 8528) = 0;
  if ( v24 != nullptr )
    result = (**v24)(v24, 1);
  v25 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8536);
  *(uint32_t *)(this + 8532) = 0;
  if ( v25 != nullptr )
    result = (**v25)(v25, 1);
  *(uint32_t *)(this + 8536) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x5E6EE0 CNFighter__vmt1F4
// ------------------------------------------------------------
// 调: sub_4049C0 sub_4AED20
int /*thiscall*/ sub_5E6EE0(int *this, int a2, float *a3, int a4)
{
  uint32_t *v5; // edi
  uint64_t v6; // rax
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  uint64_t v17; // rax
  int v18; // eax
  double v19; // st7
  int v20; // eax
  int v21; // edx
  char *v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // ebx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // eax
  int v35; // edx
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  char *v42; // eax
  int *v43; // ebx
  int v44; // ecx
  uint64_t v45; // rax
  int v46; // ebx
  int v47; // eax
  int v48; // eax
  int v49; // ecx
  float v51; // [esp+8h] [ebp-90h]
  int v52; // [esp+14h] [ebp-84h]
  int v53; // [esp+24h] [ebp-74h]
  unsigned int v54; // [esp+28h] [ebp-70h] BYREF
  int v55; // [esp+2Ch] [ebp-6Ch]
  int v56; // [esp+30h] [ebp-68h]
  void *v57; // [esp+34h] [ebp-64h] BYREF
  void *Block; // [esp+38h] [ebp-60h]
  uint32_t *v59; // [esp+3Ch] [ebp-5Ch] BYREF
  int v60; // [esp+40h] [ebp-58h]
  int v61; // [esp+44h] [ebp-54h] BYREF
  uint32_t v62[17]; // [esp+48h] [ebp-50h] BYREF
  int v63; // [esp+94h] [ebp-4h]

  v62[16] = dword_796E50;
  v5 = (uint32_t *)a2;
  if ( *(this + 1639) == 12 && *(this + 2055) == 1 )
  {
    a2 = *(this + 2056);
    if ( a2 != 0 )
      *((float *)this + 97) = *((float *)this + 97) - (double)a2;
    a2 = (*(int (/*thiscall*/ **)(int *, uint32_t *, uint32_t))(*this + 8))(this, v5, 0);
    v61 = (uint64_t)(double)dword_79594C;
    v51 = (float)v61;
    v6 = (uint64_t)((double)(int)(uint64_t)sub_4049C0(v51, 0.0, a2, dword_795948)
                          * *((float *)this + 97)
                          * 0.0099999998);
    a2 = v6;
    *(this + 2056) = v6;
    *((float *)this + 97) = (double)(int)v6 + *((float *)this + 97);
  }
  if ( *(this + 1639) == 18
    && *(this + 154) == -1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v7 = __RTDynamicCast(
           (int)v5,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &IRDActiveObject `RTTI Type Descriptor',
           0);
    if ( v7 != 0
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 824))(v7) != 0
      && (unsigned int)sub_4AED20((int)v5) <= 1 )
    {
      v8 = *(this + 2071);
      if ( v8 == 9 || v8 == 18 )
      {
        HIBYTE(a2) = 0;
        if ( v8 == 9 && (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 10) > 0 )
        {
          v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 152))(v5);
          if ( v10 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )
            HIBYTE(a2) = 1;
        }
        Block = nullptr;
        v59 = nullptr;
        v60 = 0;
        v11 = *v5;
        v63 = 0;
        *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v11 + 48))(v5));
        sub_431230((int)&v57, &v61);
        *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5));
        sub_431230((int)&v57, &v61);
        v61 = *(this + 2071) == 18;
        sub_431230((int)&v57, &v61);
        a2 = HIBYTE(a2) != 0;
        sub_431230((int)&v57, &a2);
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 19, &v57, 0, 0);
        goto LABEL_22;
      }
      if ( v8 == 49 )
      {
        Block = nullptr;
        v59 = nullptr;
        v60 = 0;
        v63 = 1;
        a2 = 0;
        sub_431230((int)&v57, &a2);
        a2 = 0;
        sub_431230((int)&v57, &a2);
        a2 = 49;
        sub_431230((int)&v57, &a2);
        a2 = 10000;
        sub_431230((int)&v57, &a2);
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 1160))(this, 49, 0);
        a2 = sub_47E9D0(v9, v54);
        sub_431230((int)&v57, &a2);
        a2 = 0;
        sub_431230((int)&v57, &a2);
        a2 = 3;
        sub_431230((int)&v57, &a2);
        a2 = 0;
        sub_431230((int)&v57, &a2);
        a2 = 1000;
        sub_431230((int)&v57, &a2);
        a2 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3) * 0.8);
        sub_431230((int)&v57, &a2);
        a2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 48))(v5);
        sub_431230((int)&v57, &a2);
        a2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5);
        sub_431230((int)&v57, &a2);
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, &v57, 0, 0);
LABEL_22:
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 596))(v5, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        v63 = -1;
        sub_5E5260(&v57);
      }
    }
  }
  if ( *(this + 1639) == 24
    && *(this + 2118) == 0
    && *(this + 154) == -1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v12 = __RTDynamicCast(
            (int)v5,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( v12 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 824))(v12) != 0 )
    {
      *(float *)&v61 = COERCE_FLOAT(sub_4AED20((int)v5));
      v13 = *v5;
      a2 = 100;
      v14 = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *))(v13 + 648))(v5, &a2, this);
      if ( *(float *)&v61 == 0.0 && v14 == 0 )
      {
        Block = nullptr;
        v59 = nullptr;
        v60 = 0;
        v63 = 2;
        v61 = 1;
        sub_431230((int)&v57, &v61);
        *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 48))(v5));
        sub_431230((int)&v57, &v61);
        *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 52))(v5));
        sub_431230((int)&v57, &v61);
        (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 24, &v57, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 596))(v5, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        v63 = -1;
        sub_5E5260(&v57);
      }
    }
  }
  if ( *(this + 1639) == 21 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    Block = nullptr;
    v59 = nullptr;
    v60 = 0;
    v63 = 3;
    a2 = 1;
    sub_431230((int)&v57, &a2);
    a2 = 0;
    sub_431230((int)&v57, &a2);
    *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    a2 = sub_41A5E0(v61 + 928);
    *(float *)&v61 = COERCE_FLOAT(sub_41A5E0(v61 + 942));
    a2 = (int)(8 * (uint64_t)((double)a2 * *(float *)&v61)) / 10;
    sub_431230((int)&v57, &a2);
    (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 6, &v57, 0, 0);
    v63 = -1;
    if ( Block != nullptr )
      j__free(Block);
  }
  if ( *(this + 1639) == 22 )
  {
    v15 = *v5;
    a2 = 100;
    (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v15 + 648))(v5, &a2, this);
    if ( (uint8_t)a4 != 0 || a2 <= 0 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 308))(v5) == 0 )
    {
      v16 = (int)a3;
    }
    else
    {
      v16 = (int)a3;
      v17 = (uint64_t)(a3[4] * 0.5 + *a3);
      v60 = v17;
      v18 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t))(*v5 + 124))(v5, HIDWORD(v17));
      v19 = *(float *)(v16 + 20) * 0.5;
      v55 = v18;
      v53 = (uint64_t)(v19 + *(float *)(v16 + 8));
      *(float *)&v61 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*this + 388))(this));
      v20 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 19);
      v21 = *this;
      v56 = v20;
      v22 = (char *)(*(int (/*thiscall*/ **)(int *, int))(v21 + 1160))(this, 19);
      v23 = sub_47EFD0(v22, COERCE_FLOAT(2), v56, v61, v61, 0);
      v24 = *this;
      v56 = v23;
      v25 = (*(int (/*thiscall*/ **)(int *))(v24 + 152))(this);
      sub_4E4A50(this, 21009, v56, v60, v55, v53, v25, 0, 0, 0);
    }
    v26 = sub_699000((int)(this + 2));
    v59 = v5;
    v60 = v26;
    sub_5E5D70(&v59);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 19);
    sub_47DCD0(this, -1);
  }
  else
  {
    v16 = (int)a3;
  }
  if ( *(this + 1639) == 26 && (uint8_t)a4 == 0 )
  {
    v27 = __RTDynamicCast(
            (int)v5,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( v27 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 308))(v27) != 0 )
    {
      v28 = sub_4AED20((int)v5);
      v29 = *v5;
      a2 = v28;
      v54 = 100;
      v30 = (*(int (/*thiscall*/ **)(uint32_t *, unsigned int *, int *))(v29 + 648))(v5, &v54, this);
      if ( a2 == 0 && v30 == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 688))(v27) + 20) != 0 )
      {
        v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 54);
        v32 = *this;
        v61 = v31;
        a2 = (*(int (/*thiscall*/ **)(int *, int))(v32 + 1140))(this, 54);
        v33 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        v34 = sub_47EFD0((char *)v61, COERCE_FLOAT(2), a2, v33, v33, 0);
        v35 = *this;
        v60 = v34;
        v36 = (*(int (/*thiscall*/ **)(int *))(v35 + 388))(this);
        v37 = sub_47EFD0((char *)v61, COERCE_FLOAT(3), a2, v36, v36, 0);
        v38 = sub_423A80(v60, v37, *(this + 2125), dword_9B9348);
        v39 = *(uint32_t *)v27;
        v62[0] = v38;
        a2 = *this;
        v40 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t *))(v39 + 56))(
                v27,
                0,
                0,
                0,
                0,
                0,
                4,
                0,
                4,
                v62);
        (*(void (/*thiscall*/ **)(int *, int, int))(a2 + 580))(this, 48028, v40);
      }
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 54);
    sub_47DCD0(this, -1);
    v60 = sub_42FCB0(228);
    v63 = 4;
    if ( v60 != 0 )
    {
      if ( (unsigned int)*(this + 96) < 0x10 )
        LOBYTE(v41) = (uint8_t)this + 108;
      else
        v41 = *(this + 91);
      *(float *)&v61 = COERCE_FLOAT(sub_431920(v41, (char)"Effect/Animation/ShoulderTackleHit.ani", 1));
    }
    else
    {
      *(float *)&v61 = 0.0;
    }
    v63 = -1;
    v42 = (char *)sub_44B6C0(284);
    v43 = (int *)v42;
    v60 = (int)v42;
    v63 = 5;
    if ( v42 != nullptr )
    {
      sub_44E0D0(v42, v61, 1);
      *v43 = (int)&CNRDPooledObject::`vftable';
    }
    else
    {
      v43 = nullptr;
    }
    v44 = *(this + 29);
    v61 = (int)v43;
    v63 = -1;
    sub_45FE80(v44, (int)v5, 2, 0, (int)v43, (int)v5, 0);
    a2 = *v43;
    v52 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v5 + 124))(v5, (uint64_t)(a3[5] * 0.5 + a3[2]));
    v45 = (uint64_t)(a3[3] * 0.5 + *a3);
    (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int))(a2 + 112))(v43, HIDWORD(v45), v45, v52);
    v46 = *v43;
    v47 = (*(int (/*thiscall*/ **)(int *, uint32_t *))(*this + 660))(this, v5);
    v48 = sub_432E50(v47);
    (*(void (/*thiscall*/ **)(int, int))(v46 + 148))(v61, v48);
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 9);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 49);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 18);
      sub_47E440(1);
    }
    if ( *(this + 2129) >= 1 )
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "R_FT_PAM_BREAST",
        -1,
        0,
        0);
    v16 = (int)a3;
    ++*(this + 2129);
  }
  v49 = *(this + 2114);
  if ( v49 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v49 + 80))(v49) != 0
    && (*((uint8_t *)this + 404) != 0 || *((float *)this + 97) > 0.0)
    && (uint8_t)a4 == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 37);
    sub_47DCD0(this, -1);
  }
  return sub_4AFB30(this, v5, v16, a4);
}


// ------------------------------------------------------------
// ============================================================
// §C Launch 系召唤
// ============================================================
// 0x5ED470 sub_5ED470
// ------------------------------------------------------------
// 调: sub_5ED470 sub_41A5E0 sub_51A7D0
int /*thiscall*/ sub_5ED470(int this, uint32_t *a2, void *a3)
{
  int result; // eax
  void *v7; // eax
  int *v8; // eax
  int v9; // edx
  int v10; // edi
  double v11; // st7
  int v12; // ecx
  uint32_t *v13; // ebx
  char *v14; // eax
  char *v15; // edi
  int v16; // edx
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  double v23; // st7
  int v24; // ecx
  uint32_t *v25; // ebx
  char *v26; // eax
  char *v27; // edi
  int v28; // edx
  int v29; // ebx
  int v30; // eax
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  unsigned int v37; // ebx
  int v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // edi
  int v42; // ebx
  int *v43; // eax
  int v44; // ebx
  int v45; // eax
  uint32_t *v46; // eax
  double v47; // st7
  int v48; // eax
  void *v49; // eax
  int *v50; // eax
  int v51; // edx
  int v52; // edi
  uint32_t *v53; // eax
  int v54; // ebx
  int *v55; // eax
  int v56; // edx
  int v57; // edi
  uint32_t *v58; // eax
  int v59; // ebx
  int *v60; // eax
  int *v61; // edi
  int *v62; // ecx
  int v63; // eax
  int v64; // edi
  uint32_t *v65; // eax
  int v66; // eax
  int v67; // ecx
  int v68; // ebx
  int *v69; // eax
  int *v70; // edi
  int *v71; // ecx
  int v72; // eax
  uint32_t *v73; // eax
  float v74; // [esp+44h] [ebp-22Ch]
  float v75; // [esp+44h] [ebp-22Ch]
  float v76; // [esp+44h] [ebp-22Ch]
  unsigned int v77; // [esp+48h] [ebp-228h]
  int v78; // [esp+54h] [ebp-21Ch]
  int v79; // [esp+54h] [ebp-21Ch]
  int *v80; // [esp+58h] [ebp-218h]
  void *Blockb; // [esp+5Ch] [ebp-214h]
  void *Blockc; // [esp+5Ch] [ebp-214h]
  void *Block; // [esp+5Ch] [ebp-214h]
  void *Blocka; // [esp+5Ch] [ebp-214h]
  char Buffer[256]; // [esp+60h] [ebp-210h] BYREF
  char v86[256]; // [esp+160h] [ebp-110h] BYREF
  int v87; // [esp+260h] [ebp-10h]
  int v88; // [esp+26Ch] [ebp-4h]
  int v89; // [esp+278h] [ebp+8h]
  int v90; // [esp+278h] [ebp+8h]
  void *v91; // [esp+278h] [ebp+8h]
  void *v92; // [esp+278h] [ebp+8h]
  float v93; // [esp+278h] [ebp+8h]
  void *v94; // [esp+27Ch] [ebp+Ch]
  void *v95; // [esp+27Ch] [ebp+Ch]
  float v96; // [esp+27Ch] [ebp+Ch]
  float v97; // [esp+27Ch] [ebp+Ch]
  void *v98; // [esp+27Ch] [ebp+Ch]
  float v99; // [esp+27Ch] [ebp+Ch]
  void *v100; // [esp+27Ch] [ebp+Ch]

  v87 = dword_796E50;
  sub_4B4170((float *)this, a2, a3);
  result = sub_41A5E0((unsigned int)(a2 + 1));
  v94 = (void *)result;
  if ( result == 20 )
  {
    if ( *(uint32_t *)(this + 8452) == 0 )
    {
      v7 = operator new(0x64u);
      v88 = 0;
      if ( v7 != nullptr )
        v8 = (int *)sub_51A7D0(v7);
      else
        v8 = nullptr;
      *(uint32_t *)(this + 8452) = v8;
      v9 = *v8;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v9 + 64))(v8) + 36) = 0;
    }
    v95 = *(void **)(this + 8452);
    v10 = sub_47EF20(0, a3, -1, -1, 11);
    *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v95 + 64))(v95) + 40) = v10;
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, int, int))(**(uint32_t **)(this + 8452) + 56))(
      *(uint32_t *)(this + 8452),
      this,
      this,
      1,
      0,
      3,
      -1);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "FT_SUPERARMOR",
      -1,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "BUFF_SUPERARMOR",
             -1,
             0,
             0);
  }
  if ( result == 30 || result == 31 || result == 39 || result == 44 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(int, int, void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
        this,
        48015,
        v94,
        0,
        0,
        0,
        0,
        0,
        4,
        0,
        0,
        0);
    if ( v94 == (void *)39 )
    {
      v11 = (double)(int)sub_47EF20(2, a3, -1, -1, 11);
      result = 0;
      do
      {
        v89 = result + 1;
        sprintf(Buffer, "Effect/Animation/AimVitalPoint%d.ani", result + 1);
        Blockb = (void *)sub_42FCB0(228);
        v88 = 1;
        if ( Blockb != nullptr )
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )
            LOBYTE(v12) = this + 108;
          else
            v12 = *(uint32_t *)(this + 364);
          v13 = (uint32_t *)sub_431920(v12, (char)Buffer, 1);
        }
        else
        {
          v13 = nullptr;
        }
        v88 = -1;
        v96 = v11 * 0.0018867925;
        sub_4922F0(v13, v96);
        v14 = (char *)sub_44B6C0(284);
        v15 = v14;
        v88 = 2;
        if ( v14 != nullptr )
        {
          sub_44E0D0(v14, (int)v13, 1);
          *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
        }
        else
        {
          v15 = nullptr;
        }
        v16 = *(uint32_t *)v15;
        v88 = -1;
        *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v16 + 36))(v15) + 8) = 2;
        sub_45FE80(*(uint32_t *)(this + 116), (int)v15, 2, 0, (int)v15, 0, 0);
        v17 = *(uint32_t *)v15;
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(char *, int))(v17 + 148))(v15, v18);
        v19 = *(uint32_t *)v15;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v20);
        v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v21);
        (*(void (/*thiscall*/ **)(char *, int))(v19 + 112))(v15, v22);
        result = v89;
      }
      while ( v89 < 3 );
      return result;
    }
    if ( v94 == (void *)44 )
    {
      v23 = (double)(int)sub_47EF20(1, a3, -1, -1, 11);
      result = 0;
      do
      {
        v90 = result + 1;
        sprintf(v86, "Effect/Animation/Provocation%d.ani", result + 1);
        Blockc = (void *)sub_42FCB0(228);
        v88 = 3;
        if ( Blockc != nullptr )
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )
            LOBYTE(v24) = this + 108;
          else
            v24 = *(uint32_t *)(this + 364);
          v25 = (uint32_t *)sub_431920(v24, (char)v86, 1);
        }
        else
        {
          v25 = nullptr;
        }
        v88 = -1;
        v97 = v23 * 0.0018867925;
        sub_4922F0(v25, v97);
        v26 = (char *)sub_44B6C0(284);
        v27 = v26;
        v88 = 4;
        if ( v26 != nullptr )
        {
          sub_44E0D0(v26, (int)v25, 1);
          *(uint32_t *)v27 = &CNRDPooledObject::`vftable';
        }
        else
        {
          v27 = nullptr;
        }
        v28 = *(uint32_t *)v27;
        v88 = -1;
        *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(v28 + 36))(v27) + 8) = 2;
        sub_45FE80(*(uint32_t *)(this + 116), (int)v27, 2, 0, (int)v27, 0, 0);
        v29 = *(uint32_t *)v27;
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(char *, int))(v29 + 148))(v27, v30);
        v31 = *(uint32_t *)v27;
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        v33 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v32);
        v34 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v33);
        (*(void (/*thiscall*/ **)(char *, int))(v31 + 112))(v27, v34);
        result = v90;
      }
      while ( v90 < 3 );
      return result;
    }
    result = (int)v94;
  }
  if ( result == 36 )
  {
    v78 = sub_47EF20(0, a3, -1, -1, 11);
    Block = (void *)sub_47EF20(1, a3, -1, -1, 11);
    v35 = *(uint32_t *)(this + 116);
    v36 = *(uint32_t *)(v35 + 120);
    result = v35 + 116;
    v37 = 0;
    if ( v36 != 0 )
    {
      result = (*(uint32_t *)(result + 8) - v36) >> 2;
      v91 = (void *)result;
    }
    else
    {
      v91 = nullptr;
    }
    v98 = nullptr;
    if ( (int)v91 > 0 )
    {
      do
      {
        v38 = *(uint32_t *)(this + 116);
        v39 = *(uint32_t *)(v38 + 120);
        if ( v39 != 0 && v37 < (*(uint32_t *)(v38 + 124) - v39) >> 2 )
          v40 = *(uint32_t *)(v39 + 4 * v37);
        else
          v40 = 0;
        v41 = __RTDynamicCast(
                v40,
                0,
                &IRDCollisionObject `RTTI Type Descriptor',
                &IRDActiveObject `RTTI Type Descriptor',
                0);
        if ( v41 != 0 )
        {
          v42 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v41 + 376))(v41);
          if ( v42 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )
          {
            v88 = 5;
            if ( operator new(0x84u) != nullptr )
              v43 = (int *)sub_510350(3, 0, Block, v78, 1, nullptr);
            else
              v43 = nullptr;
            v44 = *v43;
            v80 = v43;
            v45 = *(uint32_t *)dword_8F84B8;
            v88 = -1;
            v46 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(v45 + 60))(
                              dword_8F84B8,
                              "Common/CommonEffect/BuffIcon.img",
                              11,
                              4,
                              -1);
            v77 = sub_418DD0(v46, v77);
            (*(void (/*thiscall*/ **)(int *, int, int, int))(v44 + 56))(v80, v41, this, 1);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v41 + 212))(
              v41,
              "BUFF_SUNCURTAIN",
              -1,
              0,
              0);
          }
          v37 = (unsigned int)v98;
        }
        result = (int)v91;
        v98 = (void *)++v37;
      }
      while ( (int)v37 < (int)v91 );
    }
  }
  else if ( result == 37 )
  {
    v79 = sub_47EF20(0, a3, -1, -1, 11);
    Blocka = (void *)sub_47EF20(1, a3, -1, -1, 11);
    v92 = (void *)sub_47E9D0(a2, 0);
    v47 = (double)sub_47E9D0(a2, 1u);
    v48 = *(uint32_t *)(this + 8456);
    *(float *)(this + 8460) = v47 * 0.0099999998;
    if ( v48 == 0 )
    {
      v49 = operator new(0x7Cu);
      v88 = 6;
      if ( v49 != nullptr )
        v50 = (int *)sub_4B3C90((int)v49, 0, 0);
      else
        v50 = nullptr;
      *(uint32_t *)(this + 8456) = v50;
      v51 = *v50;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v51 + 64))(v50) + 36) = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8456) + 124))(*(uint32_t *)(this + 8456));
    v99 = (float)(int)v92;
    v74 = -v99;
    (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(7, 0, LODWORD(v74));
    v75 = (float)(int)Blocka;
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(0, 0, LODWORD(v75));
    v76 = v99 * -0.001;
    (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**(uint32_t **)(this + 8456) + 120))(24, 0, LODWORD(v76));
    *(uint32_t *)(*(uint32_t *)(this + 8456) + 44) = v79;
    v52 = **(uint32_t **)(this + 8456);
    v53 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, int, int))(*(uint32_t *)dword_8F84B8 + 60))(
                      dword_8F84B8,
                      "Common/CommonEffect/BuffIcon.img",
                      6,
                      5,
                      -1);
    sub_418DD0(v53, v77);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(v52 + 56))(*(uint32_t *)(this + 8456), this, this, 1);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "BUFF_POWERFIST",
             -1,
             0,
             0);
  }
  else if ( result == 38 )
  {
    v100 = (void *)sub_47EF20(0, a3, -1, -1, 11);
    v93 = (double)(int)sub_47EF20(1, a3, -1, -1, 11) * 0.1;
    v54 = sub_47EF20(2, a3, -1, -1, 11);
    if ( *(uint32_t *)(this + 8464) == 0 )
    {
      v88 = 7;
      if ( operator new(0x78u) != nullptr )
        v55 = (int *)sub_5E5C10(2, v93, v54, 1, (int)v100, 1);
      else
        v55 = nullptr;
      *(uint32_t *)(this + 8464) = v55;
      v56 = *v55;
      v88 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v56 + 64))(v55) + 36) = 0;
    }
    (*(void (/*fastcall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, void *, int))(**(uint32_t **)(this + 8464) + 120))(
      *(uint32_t *)(this + 8464),
      (uint64_t)v93 >> 32,
      2,
      (uint64_t)v93,
      v54,
      1,
      v100,
      1);
    v57 = **(uint32_t **)(this + 8464);
    v58 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                      dword_8F84B8,
                      "Common/CommonEffect/BuffIcon.img",
                      8,
                      0,
                      -1);
    sub_418DD0(v58, v77);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(v57 + 56))(*(uint32_t *)(this + 8464), this, this, 1);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "BUFF_POISON_SPREAD",
             -1,
             0,
             0);
  }
  else
  {
    if ( result == 43 )
    {
      v59 = sub_47EF20(0, a3, -1, -1, 11);
      if ( *(uint32_t *)(this + 8400) == 0 )
      {
        v60 = (int *)operator new(0x50u);
        v61 = v60;
        v88 = 8;
        if ( v60 != nullptr )
        {
          *v60 = (int)&IRDAppendage::`vftable';
          sub_4B0D60((uint8_t *)v60 + 4);
          LOBYTE(v88) = 9;
          sub_5F6610(v61);
          sub_5F6750(v61);
          v62 = v61;
        }
        else
        {
          v62 = nullptr;
        }
        *(uint32_t *)(this + 8400) = v62;
        v63 = *v62;
        v88 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v63 + 64))(v62) + 36) = 0;
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8400) + 64))(*(uint32_t *)(this + 8400)) + 40) = v59;
      v64 = **(uint32_t **)(this + 8400);
      v65 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);
      v66 = sub_418DD0(v65, (unsigned int)"Common/CommonEffect/BuffIcon.img");
      v67 = *(uint32_t *)(this + 8400);
    }
    else
    {
      if ( result != 50 )
        return result;
      v68 = sub_47EF20(0, a3, -1, -1, 11);
      if ( *(uint32_t *)(this + 8468) == 0 )
      {
        v69 = (int *)operator new(0x50u);
        v70 = v69;
        v88 = 10;
        if ( v69 != nullptr )
        {
          *v69 = (int)&IRDAppendage::`vftable';
          sub_4B0D60((uint8_t *)v69 + 4);
          LOBYTE(v88) = 11;
          sub_5F6610(v70);
          sub_5F6750(v70);
          v71 = v70;
        }
        else
        {
          v71 = nullptr;
        }
        *(uint32_t *)(this + 8468) = v71;
        v72 = *v71;
        v88 = -1;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v72 + 64))(v71) + 36) = 0;
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8468) + 64))(*(uint32_t *)(this + 8468)) + 40) = v68;
      v64 = **(uint32_t **)(this + 8468);
      v73 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);
      v66 = sub_418DD0(v73, (unsigned int)"Common/CommonEffect/BuffIcon.img");
      v67 = *(uint32_t *)(this + 8468);
    }
    return (*(int (/*thiscall*/ **)(int, int, int, int, int))(v64 + 56))(v67, this, this, 1, v66);
  }
  return result;
}


// ------------------------------------------------------------
// 0x5EDDC0 sub_5EDDC0
// ------------------------------------------------------------
// 调: sub_5EDDC0
int /*thiscall*/ sub_5EDDC0(int this)
{
  *(uint32_t *)(this + 8264) = 100;
  *(uint32_t *)(this + 8216) = -1;
  *(uint8_t *)(this + 8220) = 0;
  *(uint32_t *)(this + 8224) = -1;
  *(uint32_t *)(this + 8228) = 0;
  *(uint32_t *)(this + 8232) = 0;
  *(uint32_t *)(this + 8236) = 0;
  *(uint32_t *)(this + 8240) = 0;
  *(uint32_t *)(this + 8244) = 0;
  *(uint32_t *)(this + 8248) = 0;
  *(uint32_t *)(this + 8252) = 0;
  *(uint8_t *)(this + 8256) = 0;
  *(uint32_t *)(this + 8260) = 0;
  *(uint8_t *)(this + 8268) = 0;
  *(uint32_t *)(this + 8272) = 0;
  *(uint8_t *)(this + 8276) = 0;
  *(uint32_t *)(this + 8280) = 0;
  *(uint8_t *)(this + 8284) = 0;
  *(uint32_t *)(this + 8288) = 0;
  *(uint32_t *)(this + 8296) = 0;
  *(uint32_t *)(this + 8292) = 0;
  *(uint32_t *)(this + 8300) = 0;
  *(uint8_t *)(this + 8304) = 0;
  *(uint8_t *)(this + 8305) = 0;
  *(uint32_t *)(this + 8308) = 0;
  *(uint32_t *)(this + 8312) = 0;
  *(uint32_t *)(this + 8316) = 0;
  *(uint32_t *)(this + 8320) = 0;
  *(uint32_t *)(this + 8324) = 0;
  *(uint32_t *)(this + 8328) = 0;
  *(uint8_t *)(this + 8332) = 0;
  *(uint8_t *)(this + 8333) = 0;
  *(uint32_t *)(this + 8336) = 0;
  *(uint32_t *)(this + 8340) = 0;
  *(uint8_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8348) = 0;
  *(uint32_t *)(this + 8352) = 0;
  *(uint32_t *)(this + 8356) = 0;
  *(uint32_t *)(this + 8360) = 0;
  *(uint32_t *)(this + 8364) = 0;
  *(uint32_t *)(this + 8368) = 0;
  *(uint32_t *)(this + 8372) = 0;
  *(uint32_t *)(this + 8376) = 0;
  *(uint32_t *)(this + 8380) = 0;
  *(uint32_t *)(this + 8388) = 0;
  *(uint32_t *)(this + 8384) = 0;
  *(uint32_t *)(this + 8392) = 0;
  *(uint32_t *)(this + 8396) = 0;
  *(uint32_t *)(this + 8400) = 0;
  *(uint32_t *)(this + 8404) = 0;
  *(uint32_t *)(this + 8408) = 0;
  *(uint8_t *)(this + 8412) = 0;
  *(uint8_t *)(this + 8413) = 0;
  *(uint32_t *)(this + 8416) = 0;
  *(uint32_t *)(this + 8420) = 0;
  *(uint32_t *)(this + 8424) = 0;
  *(uint32_t *)(this + 8428) = 0;
  *(uint32_t *)(this + 8432) = 0;
  *(uint32_t *)(this + 8436) = 0;
  *(uint8_t *)(this + 8440) = 0;
  *(uint8_t *)(this + 8441) = 0;
  *(uint32_t *)(this + 8444) = 0;
  *(uint32_t *)(this + 8448) = 0;
  *(uint32_t *)(this + 8452) = -1;
  *(uint32_t *)(this + 8456) = 0;
  *(uint32_t *)(this + 8460) = 0;
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;
  *(uint32_t *)(this + 8472) = 0;
  *(uint32_t *)(this + 8476) = 0;
  *(uint32_t *)(this + 8480) = 0;
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 0;
  *(uint32_t *)(this + 8492) = 0;
  *(uint8_t *)(this + 8496) = 0;
  *(uint32_t *)(this + 8500) = 0;
  *(uint32_t *)(this + 8504) = 0;
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 0;
  *(uint8_t *)(this + 8516) = 0;
  *(uint32_t *)(this + 8520) = 0;
  *(uint32_t *)(this + 8524) = 0;
  *(uint32_t *)(this + 8528) = 0;
  *(uint32_t *)(this + 8532) = 0;
  *(uint32_t *)(this + 8536) = 0;
  *(uint32_t *)(this + 8540) = 0;
  *(uint32_t *)(this + 8544) = 0;
  *(uint32_t *)(this + 8548) = 0;
  *(uint32_t *)(this + 8552) = 0;
  *(uint32_t *)(this + 8556) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5EDFF0 CNSwordman__vmt3FC
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt3FC(int this)
{
  IRDCharacter__vmt3FC();
  *(uint8_t *)(this + 8440) = 0;
  *(uint8_t *)(this + 8441) = 0;
  *(uint32_t *)(this + 8520) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5EE010 CNSwordman__vmt204
// ------------------------------------------------------------
// 证: 叶子函数（9 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt204(int this, int a2, int a3, int a4)
{
  *(uint32_t *)(this + 8264) = 100;
  *(uint8_t *)(this + 8268) = 0;
  *(uint8_t *)(this + 8305) = 0;
  *(uint8_t *)(this + 8412) = 0;
  return IRDCharacter__vmt204(a2, a3, a4);
}



// ------------------------------------------------------------
// 0x5EE040 CNSwordman__vmt388
// ------------------------------------------------------------
// 证: "SWD_REFLECT"
// 调: sub_699000 sub_47EFD0 sub_47E440
char /*thiscall*/ CNSwordman__vmt388(int this, int a2, int a3)
{
  char result; // al
  int (/*thiscall*/ **v5)(int); // edx
  int v6; // edi
  int v7; // ebx
  char *v8; // eax
  int v9; // edx
  unsigned int *v10; // eax
  int v11; // ecx

  result = (uint8_t)IRDCharacter__vmt388((uint8_t **)this, a2, a3);
  switch ( a2 )
  {
    case 2:
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "SWD_REFLECT",
               -1,
               0,
               0);
    case 11:
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
      *(uint32_t *)(this + 8228) = sub_699000(this + 6560);
      if ( *(uint32_t *)(this + 8236) == 0 )
      {
        v5 = *(int (/*thiscall*/ ***)(int))this;
        *(uint32_t *)(this + 396) = 0;
        v6 = v5[97](this);
        v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 11);
        v8 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);
        *(float *)(this + 388) = (float)sub_47EFD0(v8, 0.0, v7, v6, v6, 0);
      }
      v9 = *(uint32_t *)(this + 8236) + 1;
      *(uint32_t *)(this + 8236) = v9;
      result = v9;
      if ( v9 == dword_7959FC )
        *(uint32_t *)(this + 448) = 2;
      if ( dword_8F7C04 == this )
      {
        v10 = (unsigned int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 11);
        return sub_47E440(v10, 0);
      }
      break;
    case 52:
      v11 = *(uint32_t *)(this + 8444);
      if ( v11 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 80))(v11);
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8444) + 76))(*(uint32_t *)(this + 8444), 0);
      }
      break;
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE170 CNSwordman__vmt288
// ------------------------------------------------------------
// 证: 叶子函数（25 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt288(int this, int *a2, int a3)
{
  int result; // eax
  int v5; // eax
  int v6; // esi

  result = IRDCharacter__vmt288(a2, a3);
  if ( result != 3 )
  {
    if ( *(uint8_t *)(this + 8268) != 0 )
    {
      v5 = *a2;
      v6 = *(uint32_t *)(this + 8264);
      if ( *a2 >= v6 )
        v5 = v6;
      *a2 = v5;
      return 2;
    }
    else if ( *(uint8_t *)(this + 8305) != 0 || *(uint32_t *)(this + 616) == 17 || *(uint8_t *)(this + 8412) != 0 )
    {
      return 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE1E0 CNSwordman__vmt530
// ------------------------------------------------------------
// 调: sub_47E440
char /*userpurge*/ CNSwordman__vmt530@<al>(uint8_t *a1@<ecx>, uint8_t a2@<bl>, char a3)
{
  char result; // al
  char v5; // bl
  int v6; // eax
  unsigned int *v7; // eax
  bool v8; // al
  unsigned int *v9; // eax
  bool v10; // al
  unsigned int *v11; // eax
  bool v12; // al
  unsigned int *v13; // eax
  bool v14; // al
  unsigned int *v15; // eax
  bool v16; // al
  unsigned int *v17; // eax
  unsigned int *v18; // eax
  bool v19; // al
  unsigned int *v20; // eax
  uint8_t v22; // [esp-4h] [ebp-8h]
  uint8_t v23; // [esp-4h] [ebp-8h]
  uint8_t v24; // [esp-4h] [ebp-8h]
  uint8_t v25; // [esp-4h] [ebp-8h]
  uint8_t v26; // [esp-4h] [ebp-8h]
  uint8_t v27; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1);
  if ( result != 0 )
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
    v6 = IRDCharacter__vmt530(a3);
    LOBYTE(v6) = v5 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 10)) > 0;
    v7 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)a1 + 1160))(a1, 20, v6);
    sub_47E440(v7, a2);
    v8 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 10) > 0;
    v22 = v8;
    v9 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 22);
    sub_47E440(v9, v22);
    v10 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 10) > 0;
    v23 = v10;
    v11 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 21);
    sub_47E440(v11, v23);
    v12 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 26) > 0;
    v24 = v12;
    v13 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 8);
    sub_47E440(v13, v24);
    v14 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 28) > 0;
    v25 = v14;
    v15 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 5);
    sub_47E440(v15, v25);
    v16 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 45) > 0;
    v26 = v16;
    v17 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 1);
    sub_47E440(v17, v26);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 48);
    v18 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 1160))(a1);
    sub_47E440(v18, 0x2Eu);
    v19 = v5 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1140))(a1, 54) > 0;
    v27 = v19;
    v20 = (unsigned int *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 1160))(a1, 31);
    return sub_47E440(v20, v27);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE390 CNSwordman__vmt524
// ------------------------------------------------------------
// 调: sub_47E440
char /*thiscall*/ sub_5EE390(uint8_t *this)
{
  int v2; // eax

  LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)v2 == 0 )
    return v2;
  sub_4AFEC0(this);
  LOBYTE(v2) = *(this + 7730);
  if ( (uint8_t)v2 == 0 )
    return v2;
  v2 = *((uint32_t *)this + 1639);
  switch ( v2 )
  {
    case 0:
LABEL_6:
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 1);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 5);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 8);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 9);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 20);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 21);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 22);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 23);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 24);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 25);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 30);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 36);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 38);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 40);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 18);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 41);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 44);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 46);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 31);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 32);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 50);
      sub_47E440(1);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 52);
      LOBYTE(v2) = sub_47E440(1);
      return v2;
    case 6:
      if ( *((uint32_t *)this + 1723) != 1 )
        return v2;
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 16);
      sub_47E440(1);
      if ( *((int *)this + 1724) > 0 )
      {
        if ( *(this + 6988) != 0 )
        {
LABEL_13:
          (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 49);
          LOBYTE(v2) = sub_47E440(1);
          return v2;
        }
        (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1160))(this, 17);
        sub_47E440(1);
      }
      LOBYTE(v2) = *(this + 6988);
      if ( (uint8_t)v2 == 0 )
        return v2;
      goto LABEL_13;
    case 11:
      goto LABEL_6;
    default:
      break;
  }
  return v2;
}


// ------------------------------------------------------------
// 0x5EE610 CNSwordman__vmt490
// ------------------------------------------------------------
// 调: sub_47EF20
int /*thiscall*/ CNSwordman__vmt490(void *this, int a2, uint32_t *a3)
{
  int64_t v4; // rax
  uint32_t *v5; // eax
  int v7; // [esp-10h] [ebp-14h]

  LODWORD(v4) = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 37);
  if ( (int)v4 > 0 )
  {
    LODWORD(v4) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2);
    if ( (uint8_t)v4 != 0 )
    {
      LODWORD(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 172))(a2);
      if ( *(uint32_t *)v4 == 8 )
      {
        v7 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1140))(this, 37, -1);
        v5 = (uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1160))(this);
        v4 = 1374389535LL * sub_47EF20(v5, 0x25u, 0, v7, -1, 11) * *a3;
        *a3 = (SHIDWORD(v4) >> 5) + (HIDWORD(v4) >> 31);
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x5EE690 CNSwordman__vmt454
// ------------------------------------------------------------
// 证: 叶子函数（11 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt454(uint32_t *this)
{
  int v2; // eax
  int v3; // edi

  v2 = *(this + 2107);
  v3 = dword_9A0308;
  if ( v2 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v2 + 80))() != 0 )
    v3 = v3 * *(this + 2130) / 100;
  return v3 * (100 - *(this + 2131)) / 100;
}



// ------------------------------------------------------------
// 0x5EE6F0 CNSwordman__vmt12C
// ------------------------------------------------------------
// 证: 叶子函数（18 行，无外调无字符串）
int /*thiscall*/ CNSwordman__vmt12C(uint32_t *this, uint32_t *a2)
{
  int result; // eax

  result = IRDCharacter__vmt12C(a2);
  if ( (uint32_t *)*(this + 2114) == a2 )
    *(this + 2114) = 0;
  if ( a2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 16);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 13);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 14);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 15);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EE770 sub_5EE770
// ------------------------------------------------------------
// 调: sub_5EE770 sub_4B1030 sub_650800
uint32_t */*thiscall*/ sub_5EE770(uint32_t *this)
{
  sub_4B1030(this);
  *this = &vftbl_CNPinchPowerUp;
  sub_650800(this);
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x5EE7C0 CNPinchPowerUp__vmt0
// ------------------------------------------------------------
// 调: sub_5EE7F0
void */*thiscall*/ CNPinchPowerUp__vmt0(void *Block, char a2)
{
  sub_5EE7F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE7F0 sub_5EE7F0
// ------------------------------------------------------------
// 调: sub_5EE7F0 sub_5F6640
int /*thiscall*/ sub_5EE7F0(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNPinchPowerUp;
  nullsub_3();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5EE850 sub_5EE850
// ------------------------------------------------------------
// 调: sub_5EE850 sub_4B1030 sub_6509D0
uint32_t */*thiscall*/ sub_5EE850(uint32_t *this)
{
  sub_4B1030(this);
  *this = &vftbl_CNReckless;
  sub_6509D0(this);
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x5EE8A0 CNReckless__vmt0
// ------------------------------------------------------------
// 调: sub_5EE8D0
void */*thiscall*/ CNReckless__vmt0(void *Block, char a2)
{
  sub_5EE8D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE8D0 sub_5EE8D0
// ------------------------------------------------------------
// 调: sub_5EE8D0 sub_6509F0 sub_5F6640
int /*thiscall*/ sub_5EE8D0(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNReckless;
  sub_6509F0();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5EE930 sub_5EE930
// ------------------------------------------------------------
// 调: sub_5EE930 sub_4B1030 sub_650D20 sub_650D30
uint32_t */*thiscall*/ sub_5EE930(uint32_t *this, int a2)
{
  sub_4B1030(this);
  *this = &vftbl_CNGrabbedBlastBlood;
  sub_650D20(this);
  sub_650D30(a2);
  return this;
}



// ------------------------------------------------------------
// 0x5EE990 CNGrabbedBlastBlood__vmt0
// ------------------------------------------------------------
// 调: sub_5EE9C0
void */*thiscall*/ CNGrabbedBlastBlood__vmt0(void *Block, char a2)
{
  sub_5EE9C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5EE9C0 sub_5EE9C0
// ------------------------------------------------------------
// 调: sub_5EE9C0 sub_5F6640
int /*thiscall*/ sub_5EE9C0(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNGrabbedBlastBlood;
  nullsub_3();
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5EEA20 sub_5EEA20
// ------------------------------------------------------------
// 调: sub_5EEA20 sub_47E720 sub_47E9D0
int sub_5EEA20()
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(0, 6u);
  dword_7959F8 = sub_47E9D0(v0, 1u);
  v1 = (uint32_t *)sub_47E720(0, 0x17u);
  flt_9B934C = (double)sub_47E9D0(v1, 0) * 0.0099999998;
  v2 = (uint32_t *)sub_47E720(0, 0xBu);
  dword_7959FC = sub_47E9D0(v2, 1u);
  v3 = (uint32_t *)sub_47E720(0, 0x10u);
  dword_795A00 = sub_47E9D0(v3, 0);
  v4 = (uint32_t *)sub_47E720(0, 0x10u);
  flt_9B9350 = (double)sub_47E9D0(v4, 1u) * 0.0099999998;
  v5 = (uint32_t *)sub_47E720(0, 0x10u);
  dword_795A04 = sub_47E9D0(v5, 2u);
  v6 = (uint32_t *)sub_47E720(0, 0x22u);
  dword_795A08 = sub_47E9D0(v6, 0);
  v7 = (uint32_t *)sub_47E720(0, 0x33u);
  result = sub_47E9D0(v7, 0);
  dword_795A0C = result;
  return result;
}



// ------------------------------------------------------------
// 0x5EEB20 CNSwordman__vmt480
// ------------------------------------------------------------
// 调: sub_47E9D0 sub_4B1BA0 sub_47DCC0
int /*thiscall*/ CNSwordman__vmt480(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // eax
  int v4; // ebx
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int64_t v9; // rax
  uint32_t *v10; // edi
  int v11; // ebx
  uint32_t *v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  uint32_t *v17; // [esp+Ch] [ebp-10h] BYREF
  uint32_t *v18; // [esp+10h] [ebp-Ch] BYREF
  int v19; // [esp+14h] [ebp-8h] BYREF
  signed int v20; // [esp+18h] [ebp-4h]

  IRDCharacter__vmt480(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 35) > 0 )
  {
    v2 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 35);
    v3 = v2[103];
    v18 = v2;
    v4 = v3 != 0 ? (v2[104] - v3) / 14 : 0;
    v20 = 0;
    if ( v4 > 0 )
    {
      while ( 1 )
      {
        v19 = sub_47E9D0(v2, v20);
        sub_4B1BA0(&v17, &v19);
        v5 = v17;
        if ( v17 != (uint32_t *)*(this + 1855) )
        {
          v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v19);
          v7 = sub_47DCC0(v6);
          v8 = v5[5];
          if ( v8 < v7 )
            v5[5] = v8 + 1;
        }
        if ( ++v20 >= v4 )
          break;
        v2 = v18;
      }
    }
  }
  LODWORD(v9) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 27);
  if ( (int)v9 > 0 )
  {
    v10 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 27);
    LODWORD(v9) = v10[103];
    v17 = v10;
    if ( (uint32_t)v9 != 0 )
    {
      v9 = 2454267027LL * (v10[104] - (int)v9);
      v11 = (SHIDWORD(v9) >> 3) + (HIDWORD(v9) >> 31);
    }
    else
    {
      v11 = 0;
    }
    v20 = 0;
    if ( v11 > 0 )
    {
      while ( 1 )
      {
        v19 = sub_47E9D0(v10, v20);
        sub_4B1BA0(&v18, &v19);
        v12 = v18;
        if ( v18 != (uint32_t *)*(this + 1855) )
        {
          v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v19);
          v14 = sub_47DCC0(v13);
          v15 = v12[5];
          if ( v15 < v14 )
            v12[5] = v15 + 1;
        }
        LODWORD(v9) = ++v20;
        if ( v20 >= v11 )
          break;
        v10 = v17;
      }
    }
  }
  return v9;
}



// ------------------------------------------------------------
// 0x5EECB0 CNSwordman__vmt48C
// ------------------------------------------------------------
// 调: sub_41A5E0 sub_47E9D0 sub_47DCC0 sub_41A590
int /*usercall*/ CNSwordman__vmt48C@<eax>(int *a1@<ecx>, int a2@<edi>)
{
  int result; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // edx
  uint32_t *v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v15; // edi
  int v16; // edx
  uint32_t *v17; // [esp+8h] [ebp-Ch]
  uint32_t *v18; // [esp+8h] [ebp-Ch]
  int v19; // [esp+Ch] [ebp-8h]
  signed int v20; // [esp+Ch] [ebp-8h]
  unsigned int v21; // [esp+10h] [ebp-4h]
  int v22; // [esp+10h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 1160))(a1, 35, a2);
    v17 = v4;
    if ( sub_41A5E0((unsigned int)v4 + 510) > 0 )
    {
      v5 = v4[103];
      v19 = v5 != 0 ? (v4[104] - v5) / 14 : 0;
      v21 = 0;
      if ( v19 > 0 )
      {
        while ( 1 )
        {
          v6 = *a1;
          v7 = sub_47E9D0(v4, v21);
          v8 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(a1, v7);
          v9 = sub_41A5E0(v8 + 510);
          if ( v9 > 0 && v9 < sub_47DCC0(v8) )
            sub_41A590(v8 + 510, v10, v9 + 1);
          if ( (int)++v21 >= v19 )
            break;
          v4 = v17;
        }
      }
    }
    v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*a1 + 1160))(a1, 27);
    v18 = v11;
    result = sub_41A5E0((unsigned int)v11 + 510);
    if ( result > 0 )
    {
      result = v11[103];
      if ( result != 0 )
      {
        result = (v11[104] - result) / 14;
        v22 = result;
      }
      else
      {
        v22 = 0;
      }
      v20 = 0;
      if ( v22 > 0 )
      {
        while ( 1 )
        {
          v12 = *a1;
          v13 = sub_47E9D0(v11, v20);
          v14 = (*(int (/*thiscall*/ **)(int *, int))(v12 + 1160))(a1, v13);
          v15 = sub_41A5E0(v14 + 510);
          if ( v15 > 0 && v15 < sub_47DCC0(v14) )
            sub_41A590(v14 + 510, v16, v15 + 1);
          result = ++v20;
          if ( v20 >= v22 )
            break;
          v11 = v18;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5EEE40 sub_5EEE40
// ------------------------------------------------------------
// 证: "R_SM_JUMP_ATK" | "R_SM_ATK" | "R_SM_DMG" | "SM_DIE"
// 调: sub_5EEE40 sub_430C80 sub_4015C0
int /*thiscall*/ sub_5EEE40(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // eax
  unsigned int v4; // edx
  uint32_t *v5; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // edx
  unsigned int v10; // ecx
  uint32_t *v11; // eax
  int v13; // [esp+8h] [ebp-4h] BYREF

  v2 = this + 1973;
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *(this + 1716) = 1;
  *(this + 1717) = 8;
  *(this + 1718) = 15;
  v3 = *(this + 1974);
  v13 = 5;
  if ( v3 != 0 )
    v4 = (*(this + 1975) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(this + 1976) - v3) >> 2 )
  {
    v5 = (uint32_t *)*(this + 1975);
    *v5 = 5;
    *(this + 1975) = v5 + 1;
  }
  else
  {
    sub_430C80((int)(this + 1973), *(this + 1975), 1u, &v13);
  }
  v6 = v2[1];
  v13 = 4;
  if ( v6 != 0 )
    v7 = (v2[2] - v6) >> 2;
  else
    v7 = 0;
  if ( v6 != 0 && v7 < (v2[3] - v6) >> 2 )
  {
    v8 = (uint32_t *)v2[2];
    *v8 = 4;
    v2[2] = v8 + 1;
  }
  else
  {
    sub_430C80((int)v2, v2[2], 1u, &v13);
  }
  v9 = v2[1];
  v13 = 5;
  if ( v9 != 0 )
    v10 = (v2[2] - v9) >> 2;
  else
    v10 = 0;
  if ( v9 != 0 && v10 < (v2[3] - v9) >> 2 )
  {
    v11 = (uint32_t *)v2[2];
    *v11 = 5;
    v2[2] = v11 + 1;
  }
  else
  {
    sub_430C80((int)v2, v2[2], 1u, &v13);
  }
  *(this + 1977) = 100;
  *(this + 1978) = -300;
  *(this + 1979) = 200;
  *(this + 1980) = -300;
  *(this + 1961) = 44;
  *(this + 1962) = 65;
  *(this + 1963) = 1;
  *(this + 1982) = 4;
  sub_4015C0("R_SM_JUMP_ATK", 0xDu);
  sub_4015C0("R_SM_ATK", 8u);
  sub_4015C0("R_SM_DMG", 8u);
  sub_4015C0("SM_DIE", 6u);
  sub_4015C0("SM_JUMP", 7u);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0("SM_BACKSTEP", 0xBu);
  sub_4015C0("SM_THRUST", 9u);
  sub_4015C0("SM_NOMANA", 9u);
  sub_4015C0("SM_COMMAND_PET", 0xEu);
  return sub_4015C0("SM_THROW", 8u);
}



// ------------------------------------------------------------
// 0x5EF0A0 CNSwordman__vmt1F4
// ------------------------------------------------------------
// 证: "SACRIFICE_CURED"
// 调: sub_47E9D0 sub_699000 sub_47E440 sub_47EFD0 sub_4D6810
int /*thiscall*/ sub_5EF0A0(int *this, int a2, int a3, int a4)
{
  uint32_t *v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edx
  double v9; // st7
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // edx
  char *v14; // eax
  int v15; // eax
  uint64_t v16; // rax
  uint32_t *v17; // edi
  int *v18; // eax
  int v19; // edx
  uint8_t *v20; // eax
  float v22; // [esp+14h] [ebp-40h]
  void *v23[4]; // [esp+30h] [ebp-24h] BYREF
  void *Block; // [esp+40h] [ebp-14h]
  int v25; // [esp+44h] [ebp-10h]
  int v26; // [esp+50h] [ebp-4h]

  if ( *(this + 1639) == 18 && (int *)dword_8F7C04 == this && *(this + 2077) < 2 )
  {
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 8);
    v6 = sub_47E9D0(v5, 4u);
    v7 = sub_699000((int)(this + 1640));
    v8 = *this;
    *(this + 2078) = v7 + v6;
    (*(void (/*thiscall*/ **)(int *, int))(v8 + 1160))(this, 8);
    sub_47E440(1);
  }
  if ( *(this + 1639) == 21 )
  {
    v25 = *(this + 2105);
    if ( v25 != 0 )
    {
      v9 = (double)v25;
      *(this + 2105) = 0;
      *((float *)this + 97) = *((float *)this + 97) - v9;
    }
    v10 = *(this + 2106) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( v10 >= dword_795A00 )
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 16);
      v13 = *this;
      v25 = v12;
      v14 = (char *)(*(int (/*thiscall*/ **)(int *, int))(v13 + 1160))(this, 16);
      v15 = sub_47EFD0(v14, 0.0, v25, v11, v11, 0);
      v25 = v10 - dword_795A00;
      v16 = (uint64_t)((double)(v10 - dword_795A00) * (double)v15 * flt_9B9350 * 0.0099999998);
      Block = (void *)v16;
      *(this + 2105) = v16;
      *((float *)this + 97) = (double)(int)v16 + *((float *)this + 97);
    }
  }
  v17 = (uint32_t *)a2;
  if ( *(this + 1639) == 10
    && *(this + 1953) == 0
    && *(this + 1954) == 23
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0 )
  {
    a2 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this)
                          * *((float *)this + 2100)
                          * flt_9B934C);
    Block = operator new(0x80u);
    v26 = 0;
    if ( Block != nullptr )
    {
      v22 = (float)a2;
      v18 = (int *)sub_4D6810(LODWORD(v22), 500, 1, 1);
    }
    else
    {
      v18 = nullptr;
    }
    v19 = *v18;
    v26 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t *, int *, uint32_t, uint32_t, uint32_t, int))(v19 + 56))(
      v18,
      v17,
      this,
      0,
      0,
      0,
      -1);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*v17 + 212))(v17, "SACRIFICE_CURED", -1, 0, 0);
  }
  if ( *(this + 1639) == 22
    && *(this + 2112) == 0
    && *(this + 154) == -1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v20 = __RTDynamicCast(
            v17,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDActiveObject `RTTI Type Descriptor',
            0);
    if ( v20 != nullptr
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v20 + 824))(v20) != 0
      && (unsigned int)sub_4AED20((int)v17) <= 1
      && *(this + 2113) == 31 )
    {
      memset(&v23[1], 0, 12);
      v26 = 1;
      a2 = 1;
      sub_431230((int)v23, &a2);
      sub_431230((int)v23, this + 2113);
      a2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v17 + 48))(v17);
      sub_431230((int)v23, &a2);
      a2 = (*(int (/*thiscall*/ **)(uint32_t *))(*v17 + 52))(v17);
      sub_431230((int)v23, &a2);
      (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 22, v23, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v17 + 596))(v17, 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
      v26 = -1;
      sub_5E5260(v23);
    }
  }
  return sub_4AFB30(this, v17, a3, a4);
}


// ------------------------------------------------------------
// 0x5EF3F0 CNSwordman__vmt1FC
// ------------------------------------------------------------
// 调: sub_699000 sub_47DCD0 sub_4E5CA0 sub_4E4C10 sub_47EFD0
int /*fastcall*/ sub_5EF3F0(uint32_t *a1, int a2, int a3, int a4, int a5)
{
  uint32_t *v5; // edi
  float *v7; // eax
  int v8; // edx
  int v9; // ebx
  int *v10; // ebx
  int *v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edi
  char *v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // edi
  int v20; // eax
  bool v22; // zf
  int v23; // ebx
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  int v28; // ebx
  int v29; // ebx
  int v30; // ebx
  int v31; // eax
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // ebx
  int v36; // [esp-10h] [ebp-B8h]
  int v37; // [esp-Ch] [ebp-B4h]
  int v38; // [esp-Ch] [ebp-B4h]
  int v39; // [esp-Ch] [ebp-B4h]
  int v40; // [esp-8h] [ebp-B0h]
  int v41; // [esp-4h] [ebp-ACh]
  int v42; // [esp+0h] [ebp-A8h]
  void *v43[4]; // [esp+Ch] [ebp-9Ch] BYREF
  uint8_t v44[4]; // [esp+1Ch] [ebp-8Ch] BYREF
  void *Block; // [esp+20h] [ebp-88h]
  int v46; // [esp+24h] [ebp-84h]
  int v47; // [esp+28h] [ebp-80h]
  float *v48; // [esp+2Ch] [ebp-7Ch]
  float v49; // [esp+30h] [ebp-78h] BYREF
  uint8_t v50[100]; // [esp+34h] [ebp-74h] BYREF
  int v51; // [esp+98h] [ebp-10h]
  int v52; // [esp+A4h] [ebp-4h]

  v5 = (uint32_t *)a3;
  v51 = dword_796E50;
  v7 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3);
  v8 = *a1;
  v48 = v7;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v8 + 308))(a1) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 2) > 0
    && a1[1639] == 15
    && a1[2063] != -1
    && sub_699000((int)(a1 + 16)) <= a1[2063]
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v5 + 368))(v5) != 0
    && (v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, a1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1312))(a1, 2) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t *))(*a1 + 1160))(a1, 2, a1);
    sub_47DCD0(-1, v42);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*v5 + 312))(v5, 1);
    v10 = *(int **)((*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 60))(v5) + 104);
    v48 = sub_4E5CA0(v5) == 0 ? (float *)a1 : nullptr;
    v11 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 340))(v5);
    v12 = *v10;
    a5 = *v11;
    (*(void (/*thiscall*/ **)(int *, uint8_t *))(v12 + 20))(v10, v50);
    v13 = (*(int (/*thiscall*/ **)(int *))(*v10 + 44))(v10);
    v41 = v5[242];
    v40 = v5[241];
    v36 = v13;
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 672))(v5);
    a3 = sub_4E4C10((int)v5, (int)v48, a5, *(uint32_t *)(v14 + 24), (int)v50, v36, 0, v40, v41);
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 388))(a1);
    a5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 2);
    v16 = (char *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1160))(a1, 2);
    v17 = sub_47EFD0(v16, 0.0, a5, v15, v15, 0);
    v18 = *(uint32_t *)dword_8F8520;
    a5 = v17;
    (*(void (/*thiscall*/ **)(int, int, int))(v18 + 8))(dword_8F8520, 16, 2);
    v19 = *(uint32_t *)dword_8F8520;
    v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a5);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    memset(&v43[1], 0, 12);
    v52 = 0;
    a5 = 1;
    sub_431230((int)v43, &a5);
    a5 = (uint64_t)(*(float *)(a4 + 20) * 0.5 + *(float *)(a4 + 8));
    sub_431230((int)v43, &a5);
    a5 = 1;
    sub_431230((int)v43, &a5);
    a5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1);
    sub_431230((int)v43, &a5);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*a1 + 560))(a1, 15, v43, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1104))(a1, 8);
    *((uint8_t *)a1 + 8268) = 1;
    a1[2066] = 0;
    sub_5E5260(v43);
    return 0;
  }
  else
  {
    v22 = a1[1639] == 15;
    HIBYTE(a3) = 0;
    if ( v22
      && (v23 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, a1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1)
      && (*((uint8_t *)v48 + 16) != 0 || *v48 > 0.0 || *((uint32_t *)v48 + 15) != 0)
      && (uint8_t)a5 == 0 )
    {
      *((uint8_t *)a1 + 8268) = 1;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 3) > 0
           && (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 1) > 0
           && (*((uint8_t *)v48 + 16) != 0 || *v48 > 0.0 || *((uint32_t *)v48 + 15) != 0)
           && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1) == 0 )
    {
      v24 = a1[1639];
      if ( v24 != 4 && v24 != 9 && (uint8_t)a5 == 0 )
      {
        v37 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 1140))(a1, 3, -1);
        (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 1160))(a1);
        v25 = sub_47EF20(3, 0, v37, -1, 11);
        if ( sub_445870(21654682, 10000) < 100 * v25
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1312))(a1, 1) != 0 )
        {
          *((uint8_t *)a1 + 8268) = 1;
          HIBYTE(a3) = 1;
          sub_5E5260((void **)a1 + 2029);
        }
      }
    }
    if ( *((uint8_t *)a1 + 8268) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1160))(a1, 1);
      v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 1);
      v27 = *((uint32_t *)v48 + 3);
      if ( v27 == 1 )
      {
        a1[2066] = 100 - sub_47EF20(3, v26, -1, -1, 11);
      }
      else if ( v27 != 0 )
      {
        if ( v27 == 2 )
          a1[2066] = 100;
      }
      else
      {
        a1[2066] = 100 - sub_47EF20(2, v26, -1, -1, 11);
      }
      if ( *((uint8_t *)a1 + 642) != 0 )
      {
        v28 = a1[161];
      }
      else
      {
        v29 = a1[30];
        if ( v29 != 0 )
        {
          if ( *(uint32_t *)(v29 + 148) == -1 )
            sub_4938F0(a1[30]);
          v28 = *(uint32_t *)(v29 + 112);
        }
        else
        {
          v28 = 0;
        }
      }
      if ( (HIBYTE(a3) != 0 || v28 == 0) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0 )
      {
        Block = nullptr;
        v46 = 0;
        v47 = 0;
        v52 = 1;
        LODWORD(v49) = 1;
        sub_431230((int)v44, &v49);
        LODWORD(v49) = (uint64_t)(*(float *)(a4 + 20) * 0.5 + *(float *)(a4 + 8));
        sub_431230((int)v44, &v49);
        v49 = 0.0;
        sub_431230((int)v44, &v49);
        if ( HIBYTE(a3) == 0
          || (v30 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, a1)) == (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1) )
        {
          a3 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1);
          sub_431230((int)v44, &a3);
        }
        else
        {
          v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1);
          a3 = sub_432E50(v31);
          sub_431230((int)v44, &a3);
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*a1 + 560))(a1, 15, v44, 0, 0);
        v52 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        v46 = 0;
        v47 = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1104))(a1, 8);
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 7) > 0 && *((uint8_t *)a1 + 8268) == 0 )
    {
      v32 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v5 + 660))(v5, a1);
      if ( v32 != (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1)
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v5 + 40))(v5, 17) != 0
        && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1) == 0 )
      {
        v33 = a1[1639];
        if ( v33 != 4 && v33 != 9 && sub_4AED00(v48) )
        {
          v38 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 1140))(a1, 7, -1);
          (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 1160))(a1);
          a3 = sub_47EF20(7, 0, v38, -1, 11);
          v49 = (float)a3;
          a3 = sub_445870(&unk_85B384, 10000);
          if ( v49 * 100.0 > (double)a3 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1312))(a1, 7) != 0 )
            *((uint8_t *)a1 + 8305) = 1;
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1140))(a1, 47) > 0
      && *((uint8_t *)a1 + 8268) == 0
      && *((uint8_t *)a1 + 8305) == 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v5 + 40))(v5, 17) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1) == 0 )
    {
      v34 = a1[1639];
      if ( v34 != 4 && v34 != 9 && sub_4AED00(v48) )
      {
        v39 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 1140))(a1, 47, -1);
        (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 1160))(a1);
        v35 = sub_47EF20(47, 0, v39, -1, 11);
        if ( sub_445870(off_702C24, 10000) < 100 * v35
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1312))(a1, 47) != 0 )
        {
          *((uint8_t *)a1 + 8412) = 1;
        }
      }
    }
    return sub_4AFB80(a1, (int)v5, a4, a5);
  }
}


// ------------------------------------------------------------
// 0x5EFBD0 CNSwordman__vmt200
// ------------------------------------------------------------
// 调: sub_4938F0 sub_432E50 sub_431230 sub_5E5260
int /*thiscall*/ sub_5EFBD0(int this, int a2, uint32_t *Block, int a4)
{
  float v4; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  unsigned int v17; // edx
  int v18; // eax
  int v19; // eax
  uint32_t *v20; // eax
  int v21; // eax
  int v22; // edi
  uint32_t *v23; // edi
  void **v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  int v28; // [esp+74h] [ebp-44h]
  int v29; // [esp+78h] [ebp-40h]
  unsigned int v30; // [esp+80h] [ebp-38h]
  void *v31[4]; // [esp+8Ch] [ebp-2Ch] BYREF
  void *v32[4]; // [esp+9Ch] [ebp-1Ch] BYREF
  int v33; // [esp+B4h] [ebp-4h]

  v4 = *(float *)&a2;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 60) == 0 )
    goto LABEL_11;
  if ( *(uint8_t *)(this + 642) != 0 )
  {
    v6 = *(uint32_t *)(this + 644);
    goto LABEL_8;
  }
  a2 = *(uint32_t *)(this + 120);
  v7 = a2;
  if ( a2 != 0 )
  {
    if ( *(uint32_t *)(a2 + 148) == -1 )
    {
      sub_4938F0(a2);
      v7 = a2;
    }
    v6 = *(uint32_t *)(v7 + 112);
LABEL_8:
    if ( v6 != 0 )
      goto LABEL_11;
  }
  if ( (uint8_t)a4 == 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 13);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 12);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 16);
  }
LABEL_11:
  a4 = sub_4B9720((unsigned int *)this, v4, (int)Block, a4);
  if ( *(uint8_t *)(this + 8305) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    v8 = *(uint32_t *)(this + 616);
    if ( v8 != 3 && v8 != 4 && v8 != 5 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 27, 2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 2);
      v9 = *(uint32_t *)dword_8F8520;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
      v11 = *(uint32_t *)dword_8F8520;
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 200);
      v13 = *(uint32_t *)dword_8F8520;
      v14 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 48))(COERCE_FLOAT(LODWORD(v4)));
      (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
      v15 = *(uint32_t *)dword_8F8520;
      v16 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 52))(COERCE_FLOAT(LODWORD(v4)));
      (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 200);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      memset(&v31[1], 0, 12);
      v17 = *(uint32_t *)this;
      v33 = 0;
      v18 = (*(int (/*thiscall*/ **)(int))(v17 + 152))(this);
      a2 = sub_432E50(v18);
      sub_431230((int)v31, &a2);
      (*(void (/*thiscall*/ **)(int, int, void **, int, uint32_t))(*(uint32_t *)this + 560))(this, 17, v31, 1, 0);
      v33 = -1;
      sub_5E5260(v31);
    }
  }
  if ( *(uint8_t *)(this + 8412) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    v19 = *(uint32_t *)(this + 616);
    if ( v19 != 3 && v19 != 4 && v19 != 5 )
    {
      memset(&v32[1], 0, 12);
      v33 = 1;
      a2 = 0;
      sub_431230((int)v32, &a2);
      a2 = 0;
      sub_431230((int)v32, &a2);
      a2 = 32;
      sub_431230((int)v32, &a2);
      a2 = 0;
      sub_431230((int)v32, &a2);
      v20 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 1160))(this, 32, 0);
      a2 = sub_47E9D0(v20, v30);
      sub_431230((int)v32, &a2);
      a2 = 1;
      sub_431230((int)v32, &a2);
      a2 = 4;
      sub_431230((int)v32, &a2);
      a2 = 4;
      sub_431230((int)v32, &a2);
      (*(void (/*thiscall*/ **)(int, int, void **, uint32_t))(*(uint32_t *)this + 560))(this, 10, v32, 0);
      v33 = -1;
      sub_5E5260(v32);
    }
  }
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 53) > 0 && *(uint8_t *)(this + 8268) == 0 )
  {
    v21 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 348))(COERCE_FLOAT(LODWORD(v4)));
    if ( *(uint8_t *)(v21 + 16) != 0
      || *(float *)v21 > 0.0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 348))(COERCE_FLOAT(LODWORD(v4))) + 60) != 0 )
    {
      v22 = (*(int (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 376))(COERCE_FLOAT(LODWORD(v4)));
      if ( v22 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 376))(this) )
      {
        v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 53);
        a2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 53);
        Block = operator new(0x7Cu);
        v33 = 2;
        if ( Block != nullptr )
        {
          v29 = sub_47EF20(1, a2, -1, -1, 11);
          a2 = sub_47EF20(0, a2, -1, -1, 11);
          *(float *)&v28 = (float)a2;
          v24 = (void **)sub_4B3DF0(Block, 1, 0, v28, v29, 5);
        }
        else
        {
          v24 = nullptr;
        }
        a2 = (int)v24;
        v25 = *v24;
        v33 = -1;
        Block = v25;
        v26 = sub_47E9D0(v23, 0);
        ((void (/*thiscall*/ *)(int, int, int, int, uint32_t, int, int))Block[14])(a2, this, this, 1, 0, 16, v26);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "HOOP_SHIELD",
          -1,
          0,
          0);
      }
    }
  }
  return a4;
}

