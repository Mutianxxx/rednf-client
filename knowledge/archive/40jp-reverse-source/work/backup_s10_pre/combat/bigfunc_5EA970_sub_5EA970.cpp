// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5EA970_sub_5EA970.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5EA970）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 2164 行；字符串证据 5 条；外调 6 个
//   串: "FT_SIT"
//   串: "G_BONECRUSHER"
//   串: "G_LOWKICK"
//   串: "R_FT_KICK_LOW"
//   串: "FT_KENSIN"
//   调: sub_5EA970 sub_5E6920 sub_49C620 sub_47E9D0 sub_49C5F0 sub_432E50
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5EA970 sub_5EA970  size=10856
// ------------------------------------------------------------
int /*thiscall*/ sub_5EA970(int this, int nArg2, uint32_t **pArg3, int nArg4, int nArg5)
{
  int pThis_47412; // ebx
  int fld_1E88; // eax
  int v8; // edx
  uint32_t *pThis_488; // eax
  int v10; // eax
  uint32_t *pThis_204C; // edi
  int i; // ebx
  int fld_206C; // ecx
  int fld_206C2; // ecx
  int v15; // edi
  int pThis_78; // eax
  int fld_206C3; // ecx
  int v18; // eax
  int fld_206C4; // ecx
  char fld_2085; // al
  int fld_207C; // eax
  int fld_2080; // ecx
  uint32_t *fld_2084; // edi
  int v24; // eax
  uint32_t *pThis_2090; // edi
  int j; // ebx
  int fld_20A4; // ecx
  int v28; // edi
  int pThis_7C; // eax
  int pThis_782; // eax
  uint32_t *k; // edi
  int fld_2130; // eax
  int nArg22; // edi
  int v34; // edi
  int pThis_474; // eax
  int fld_70; // edi
  int v37; // eax
  int v38; // edi
  int pThis_98; // eax
  int v40; // edx
  int v41; // edi
  char *fld_2030; // ebx
  int fld_20302; // eax
  void *v44; // eax
  int v45; // eax
  int pThis_184; // eax
  int v47; // eax
  int v48; // ecx
  int v49; // edi
  int pThis_982; // eax
  int v51; // eax
  uint32_t *v52; // eax
  int fld_2044; // ebx
  int fld_2048; // edi
  int fld_2038; // eax
  void *v56; // eax
  int v57; // edi
  uint64_t v58; // rax
  int v59; // ebx
  int pThis_783; // eax
  int v61; // edi
  int pThis_7C2; // eax
  int v63; // ebx
  int v64; // edi
  int pThis_983; // eax
  int pThis_80; // eax
  int pThis_1842; // eax
  int pThis_178; // eax
  bool v69; // zf
  int pThis_6C; // eax
  int pThis_6C2; // eax
  int v72; // edi
  int pThis_4744; // eax
  int pThis_4745; // edi
  int v75; // edi
  int pThis_4746; // eax
  int v77; // edx
  uint32_t *v78; // eax
  int fld_205C; // edx
  int v80; // eax
  int fld_205C2; // eax
  int fld_1848; // eax
  int pThis_4747; // eax
  int fld_2060; // ecx
  int fld_702; // eax
  uint64_t v86; // rax
  int v87; // edi
  int pThis_984; // eax
  int fld_2114; // ecx
  bool v90; // al
  int v91; // eax
  int pObj4; // eax
  int v93; // eax
  int fld_206C7; // ecx
  int v95; // eax
  int fld_206C8; // ecx
  int fld_206C9; // eax
  int v98; // eax
  int v99; // edx
  uint32_t **pThis_20902; // edi
  uint32_t *pThis_6C5; // eax
  int pThis_6C6; // eax
  int fld_206C10; // ecx
  int v104; // eax
  void *Block2; // ebx
  int v106; // edx
  int fld_18482; // eax
  int fld_22C; // eax
  int v109; // eax
  int fld_20842; // edi
  int pThis_1845; // ebx
  void *pThis_47410; // eax
  int v113; // edx
  char *v114; // eax
  char fld_20852; // al
  char *pThis_4885; // edi
  int pThis_47411; // ebx
  int pThis_1846; // eax
  int v119; // eax
  int fld_18484; // eax
  int fld_18483; // eax
  int v122; // edx
  int v123; // eax
  int pObj3; // eax
  int fld_20A42; // edi
  int v126; // eax
  int *v127; // eax
  int v128; // ecx
  int v129; // edi
  int v130; // eax
  int fld_20A43; // ecx
  int v132; // ebx
  int *fld_20A44; // edi
  int v134; // edx
  int v135; // eax
  int v136; // eax
  int v137; // edi
  int fld_20A45; // eax
  int v139; // eax
  void *pThis_4945; // eax
  char *pThis_4886; // edi
  int pThis_1847; // eax
  int fld_20A46; // eax
  int v144; // edx
  void *pThis_35; // eax
  double v146; // st7
  int v147; // eax
  void *v148; // eax
  int v149; // edx
  int v150; // eax
  int fld_20A47; // ecx
  int fld_20FC; // edi
  int v153; // edx
  int v154; // edi
  int pThis_47413; // ebx
  char *pThis_4887; // eax
  int pThis_47414; // edi
  char *pThis_4888; // ebx
  int pThis_1848; // eax
  void *v160; // eax
  int v161; // edx
  int v162; // edi
  int pThis_2A0; // eax
  int pThis_6C7; // eax
  int v165; // edx
  char *pThis_4889; // edi
  int pThis_47415; // ebx
  int pThis_1849; // eax
  int v169; // eax
  int pThis_2A02; // eax
  int v171; // edi
  int pThis_987; // eax
  int v173; // edi
  int v174; // eax
  void *pThis_4946; // eax
  int v176; // edx
  int pThis_18410; // edi
  int pThis_47416; // ebx
  char *pThis_48810; // eax
  void *v180; // eax
  int v181; // edx
  int v182; // edi
  int pThis_4947; // eax
  int v184; // eax
  int pObj; // eax
  int v186; // eax
  int fld_206C11; // ecx
  int v188; // eax
  int fld_206C12; // ecx
  int v190; // eax
  int v191; // eax
  char *v192; // edi
  int pThis_47417; // ebx
  int fld_21302; // eax
  uint64_t fld_703; // rax
  int fld_7032; // ebx
  void (/*thiscall*/ **v197)(int, int); // edi
  int pThis_988; // eax
  void *fld_78; // ecx
  int pThis_18411; // eax
  void *v201; // eax
  int v202; // edx
  int v203; // eax
  int v204; // eax
  void *fld_2134; // eax
  int fld_21342; // edx
  int v207; // eax
  int v208; // ebx
  int v209; // eax
  int pThis_6C8; // eax
  int result; // eax
  uint32_t *v213; // ecx
  int v214; // ecx
  char *pThis_4882; // edi
  int pThis_4748; // ebx
  int pThis_1843; // eax
  int v218; // eax
  int v219; // edx
  int v220; // edi
  int pThis_4943; // eax
  void *pThis_4944; // eax
  int v223; // edi
  int pThis_494; // eax
  void *pThis_4942; // eax
  int *v226; // ecx
  char *pThis_4883; // edi
  int fld_201C; // ebx
  int pThis_1844; // eax
  char *pThis_4884; // edi
  int fld_201C2; // eax
  int v232; // edx
  int fld_201C22; // ebx
  int v234; // eax
  int v235; // edx
  int fld_20D0; // ecx
  int fld_1E882; // eax
  int pThis_6C3; // eax
  int pThis_6C4; // eax
  int v240; // edi
  int pThis_985; // eax
  int v242; // edx
  int v243; // edi
  int pThis_986; // eax
  int v245; // edi
  int pThis_4749; // eax
  int v247; // eax
  int pObj2; // eax
  int v249; // eax
  int fld_206C5; // ecx
  int v251; // eax
  int fld_206C6; // ecx
  int v253; // eax
  int v254; // ecx
  int pThis_4743; // [esp-Ch] [ebp-60h]
  int v256; // [esp-Ch] [ebp-60h]
  int v257; // [esp-Ch] [ebp-60h]
  int fld_213422; // [esp-8h] [ebp-5Ch]
  int v259; // [esp-4h] [ebp-58h]
  int v260; // [esp-4h] [ebp-58h]
  int dword_9B93482; // [esp-4h] [ebp-58h]
  int v262; // [esp+0h] [ebp-54h]
  int v263; // [esp+4h] [ebp-50h]
  int v264; // [esp+8h] [ebp-4Ch]
  int v265; // [esp+Ch] [ebp-48h] BYREF
  float v266; // [esp+10h] [ebp-44h]
  float v267; // [esp+14h] [ebp-40h]
  int v268; // [esp+18h] [ebp-3Ch]
  int v269; // [esp+1Ch] [ebp-38h]
  int v270; // [esp+20h] [ebp-34h]
  void *v271; // [esp+24h] [ebp-30h] BYREF
  int v272; // [esp+28h] [ebp-2Ch]
  int v273; // [esp+2Ch] [ebp-28h]
  int v274; // [esp+30h] [ebp-24h]
  void *Block; // [esp+34h] [ebp-20h] BYREF
  int pThis_4742; // [esp+38h] [ebp-1Ch] BYREF
  int v277; // [esp+3Ch] [ebp-18h] BYREF
  int pThis_784; // [esp+40h] [ebp-14h] BYREF
  int fld_199C; // [esp+44h] [ebp-10h]
  int v280; // [esp+50h] [ebp-4h]
  void *v281; // [esp+60h] [ebp+Ch]
  void *v282; // [esp+60h] [ebp+Ch]
  void *pMem; // [esp+60h] [ebp+Ch]

  fld_199C = *(uint32_t *)(this + 6556);
  pThis_47412 = 0;
  switch ( fld_199C )
  {
    case 10:
      if ( *(uint32_t *)(this + 7812) == 0 )
      {
        fld_1E88 = *(uint32_t *)(this + 7816);
        if ( fld_1E88 == 12 )
        {
          v8 = *(uint32_t *)this;
          if ( *(uint32_t *)(this + 7808) != 0 )
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8388));
          else
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8380));
        }
        else if ( fld_1E88 == 16 )
        {
          if ( *(uint32_t *)(this + 7808) == 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));
        }
        else if ( fld_1E88 == 49 && nArg2 != 10 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 604))(this);
          sub_5E6920(this);
          sub_49C620(0, 1, 0);
          pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1160))(this, 49, 8);
          v10 = sub_47E9D0(pThis_488, 1u);
          sub_49C5F0(0, 0, 0, v10);
        }
      }
      break;
    case 17:
      if ( *(uint32_t *)(this + 8244) == 1 && *(uint32_t *)(this + 8248) == 15 )
      {
        pThis_204C = (uint32_t *)(this + 8268);
        for ( i = 2; i != 0; --i )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_204C++);
        pThis_47412 = 0;
      }
      break;
    case 18:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);
      if ( *(uint8_t *)(this + 8292) != 0 )
        goto LABEL_62;
      break;
    case 19:
      fld_206C = *(uint32_t *)(this + 8300);
      if ( fld_206C != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C + 308))(fld_206C) != 0 )
        {
          fld_206C2 = *(uint32_t *)(this + 8300);
          if ( *(uint8_t *)(this + 8325) != 0 )
            v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C2 + 192))(fld_206C2) / 10;
          else
            v15 = 3 * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C2 + 192))(fld_206C2) / 4;
          if ( *(uint32_t *)(this + 8316) != 0 )
            pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - v15;
          else
            pThis_78 = v15 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
          fld_206C3 = *(uint32_t *)(this + 8300);
          pThis_784 = pThis_78;
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C3 + 124))(fld_206C3);
          fld_206C4 = *(uint32_t *)(this + 8300);
          v277 = v18;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)fld_206C4 + 136))(fld_206C4, pThis_784, v18, 0) != 0
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8300) + 132))(
                 *(uint32_t *)(this + 8300),
                 0) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(
              *(uint32_t *)(this + 8300),
              pThis_784,
              v277,
              0);
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(**(uint32_t **)(this + 8300) + 140))(
                      *(uint32_t *)(this + 8300),
                      &pThis_784,
                      &v277,
                      pThis_784,
                      v277,
                      100,
                      1,
                      1) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(
              *(uint32_t *)(this + 8300),
              pThis_784,
              v277,
              0);
          }
          else
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8300) + 108))(
              *(uint32_t *)(this + 8300),
              *(uint32_t *)(this + 8304),
              *(uint32_t *)(this + 8308),
              *(uint32_t *)(this + 8312));
          }
          v272 = 0;
          v273 = 0;
          v274 = 0;
          fld_2085 = *(uint8_t *)(this + 8325);
          v280 = 0;
          if ( fld_2085 != 0 )
            fld_207C = *(uint32_t *)(this + 8316);
          else
            fld_207C = sub_432E50(*(uint32_t *)(this + 8316));
          pThis_4742 = fld_207C;
          sub_431230((int)&v271, &pThis_4742);
          Block = (void *)2;
          sub_431230((int)&v271, &Block);
          Block = (void *)1;
          sub_431230((int)&v271, &Block);
          *(float *)&Block = 0.0;
          sub_431230((int)&v271, &Block);
          *(float *)&Block = 0.0;
          sub_431230((int)&v271, &Block);
          (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(this + 8300) + 560))(
            *(uint32_t *)(this + 8300),
            4,
            &v271,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8300) + 564))(*(uint32_t *)(this + 8300));
          v280 = -1;
          sub_5E5260(&v271);
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8300) + 596))(*(uint32_t *)(this + 8300), 1);
        fld_2080 = *(uint32_t *)(this + 8320);
        *(uint32_t *)(this + 8300) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_2080 + 76))(fld_2080, 0);
        fld_2084 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(
                          this,
                          *(uint8_t *)(this + 8324) != 0 ? 18 : 9);
        sub_49C620(0, 1, 0);
        v24 = sub_47E9D0(fld_2084, 1u);
        sub_49C5F0(0, 0, 0, v24);
      }
      if ( *(uint8_t *)(this + 8324) != 0 && *(uint8_t *)(this + 8334) != 0 )
      {
        pThis_2090 = (uint32_t *)(this + 8336);
        for ( j = 2; j != 0; --j )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2090++);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 12);
        *(uint8_t *)(this + 8334) = 0;
        pThis_47412 = 0;
      }
      break;
    case 20:
      if ( nArg2 != 20 )
      {
        fld_20A4 = *(uint32_t *)(this + 8356);
        if ( fld_20A4 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_20A4 + 308))(fld_20A4) != 0 )
          {
            v272 = 0;
            v273 = 0;
            v274 = 0;
            v280 = 1;
            Block = (void *)4;
            sub_431230((int)&v271, &Block);
            Block = (void *)2;
            sub_431230((int)&v271, &Block);
            Block = (void *)1;
            sub_431230((int)&v271, &Block);
            *(float *)&Block = 0.0;
            sub_431230((int)&v271, &Block);
            *(float *)&Block = 0.0;
            sub_431230((int)&v271, &Block);
            (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(this + 8356) + 560))(
              *(uint32_t *)(this + 8356),
              4,
              &v271,
              2,
              0);
            (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 564))(*(uint32_t *)(this + 8356));
            v280 = -1;
            sub_5E5260(&v271);
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 612))(
            *(uint32_t *)(this + 8356),
            0,
            0);
          *(uint32_t *)(this + 8356) = 0;
        }
        v28 = *(uint32_t *)this;
        pThis_7C = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, 0);
        pThis_782 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v28 + 136))(this, pThis_782) == 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 112))(
            this,
            *(uint32_t *)(this + 8364),
            *(uint32_t *)(this + 8368),
            0);
      }
      break;
    case 22:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8412));
      for ( k = *(uint32_t **)(this + 8420); k != *(uint32_t **)(this + 8424); k += 2 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*k + 260))(*k, 0, 0, 0);
      if ( *(uint32_t *)(this + 8420) != 0 )
        j__free(*(void **)(this + 8420));
      *(uint32_t *)(this + 8420) = 0;
      *(uint32_t *)(this + 8424) = 0;
      *(uint32_t *)(this + 8428) = 0;
      break;
    case 24:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);
      if ( *(uint32_t *)(this + 8472) == 1 )
        sub_5E6640(this);
      break;
    case 26:
      fld_2130 = *(uint32_t *)(this + 8496);
      if ( fld_2130 != 0 )
      {
        if ( fld_2130 == 1 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8512));
          if ( *(uint32_t *)(this + 8500) >= dword_9B9348 )
          {
LABEL_62:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 284))(this, 0, 0, 1, 2);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
          }
        }
      }
      else
      {
        sub_4BA730((uint32_t *)this, 2, 4, 0, 0);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 1, -1);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 13);
      }
      break;
    default:
      break;
  }
  if ( fld_199C == 21 || fld_199C == 6 )
  {
    nArg22 = nArg2;
    if ( nArg2 != 21 && nArg2 != 6 && *(int *)(this + 8444) > 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v34 = *(uint32_t *)this;
        pThis_474 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);
        (*(void (/*thiscall*/ **)(int, int, int))(v34 + 1296))(this, 17, pThis_474);
        nArg22 = nArg2;
      }
      *(uint32_t *)(this + 8444) = 0;
    }
  }
  else
  {
    nArg22 = nArg2;
  }
  if ( nArg22 == 25 )
  {
    nArg22 = 8;
    nArg2 = 8;
    fld_199C = 25;
  }
  switch ( nArg22 )
  {
    case 15:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 6216));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
      fld_70 = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);
      *(float *)&pThis_4742 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 2));
      v37 = 0;
      if ( fld_70 != 0 )
        v37 = sub_47EF20(1, pThis_4742, -1, -1, 11);
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
        this,
        0,
        fld_70,
        fld_70,
        0,
        v37,
        1);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v38 = *(uint32_t *)this;
      pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v38 + 896))(this, pThis_98);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
        *(uint32_t *)(this + 8232) = sub_47EF20(0, pThis_4742, -1, -1, 11);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "FT_SIT", -1, 0, 0);
      goto LABEL_251;
    case 16:
      v40 = *(uint32_t *)this;
      v259 = *pArg3[1];
      *(uint32_t *)(this + 8240) = v259;
      v41 = (*(int (/*thiscall*/ **)(int, int))(v40 + 1140))(this, v259);
      fld_2030 = (char *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)(this + 8240));
      fld_20302 = *(uint32_t *)(this + 8240);
      if ( fld_20302 == 4 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556));
        v44 = (void *)sub_47EF20(2, v41, -1, -1, 11);
        v265 = 11;
        Block = v44;
        *(float *)(this + 424) = (double)(int)v44 * 0.1;
        v45 = sub_47EF20(3, v41, -1, -1, v265);
        *(float *)&v265 = 0.0;
        *(uint32_t *)(this + 436) = v45;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)this + 212))(
          this,
          "G_BONECRUSHER",
          -1,
          0,
          v265);
      }
      else if ( fld_20302 == 6 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 12));
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 304);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "G_LOWKICK",
          -1,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "R_FT_KICK_LOW",
        -1,
        0,
        0);
      pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(fld_2030, COERCE_FLOAT(1), v41, pThis_184, pThis_184, 0));
      *(float *)(this + 388) = (float)(int)Block;
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, v41, -1, -1, 11));
      v47 = 0;
      v48 = 0;
      *(float *)&pThis_4742 = (double)(int)Block * 0.0099999998 + 1.0;
      if ( fld_199C == 8 )
      {
        v47 = 600;
        v48 = -10000;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
        this,
        0,
        v47,
        v47,
        0,
        v48,
        1);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      *(float *)&Block = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 900))(this, 3));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 888))(
        this,
        0,
        0,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742),
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      v49 = *(uint32_t *)this;
      pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v49 + 896))(this, pThis_982);
      goto LABEL_251;
    case 17:
      v51 = *pArg3[1];
      pThis_4742 = 1000;
      *(uint32_t *)(this + 8244) = v51;
      if ( v51 != 0 )
      {
        fld_2044 = *(uint32_t *)(this + 8260);
        fld_2048 = *(uint32_t *)(this + 8264);
      }
      else
      {
        *(uint32_t *)(this + 8248) = pArg3[1][1];
        *(uint32_t *)(this + 8252) = pArg3[1][2];
        *(uint32_t *)(this + 8256) = pArg3[1][3];
        v52 = pArg3[1];
        fld_2044 = v52[4];
        *(uint32_t *)(this + 8260) = v52[5];
        if ( (unsigned int)sub_41C5A0(pArg3) > 6 )
          pThis_4742 = pArg3[1][6];
        if ( (unsigned int)sub_41C5A0(pArg3) <= 7 )
        {
          fld_2048 = pThis_4742;
          *(uint32_t *)(this + 8264) = 1000;
        }
        else
        {
          fld_2048 = pThis_4742;
          *(uint32_t *)(this + 8264) = pArg3[1][7];
        }
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 16));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, fld_2044, fld_2044, fld_2048, fld_2048);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252) = 1000
                                                              * *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252)
                                                              / *(uint32_t *)(this + 6656);
      if ( *(uint32_t *)(this + 8244) == 0 && fld_2044 == 4 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 992))(this, *(uint32_t *)(this + 8252), 0);
      if ( *(uint32_t *)(this + 8244) == 1 )
      {
        fld_2038 = *(uint32_t *)(this + 8248);
        switch ( fld_2038 )
        {
          case 8:
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              pThis_4743 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, 8, -1);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);
              v56 = (void *)sub_47EF20(8, 0, pThis_4743, -1, 11);
              pThis_4742 = (int)v56;
              if ( (int)v56 > 0 )
              {
                pThis_784 = 0;
                Block = v56;
                do
                {
                  v57 = pThis_784 / pThis_4742;
                  v58 = (uint64_t)(sub_405400(pThis_784 / pThis_4742) * 75.0);
                  HIDWORD(v58) = *(uint32_t *)this;
                  v59 = v58;
                  v277 = v58;
                  if ( (*(int (/*thiscall*/ **)(int))(HIDWORD(v58) + 152))(this) == 0 )
                    v277 = -v59;
                  pThis_783 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
                  v277 += pThis_783;
                  v61 = (int)(dword_7930D4[0] * (uint64_t)(sub_4053E0(v57) * 75.0)) / 100;
                  pThis_7C2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);
                  v63 = *(uint32_t *)this;
                  v64 = pThis_7C2 + v61;
                  pThis_983 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                          this,
                          0,
                          0,
                          0,
                          0xFFFF,
                          0,
                          0,
                          0,
                          0);
                  pThis_80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 128))(this, pThis_983);
                  pThis_1842 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)this + 388))(this, v277, v64, pThis_80);
                  pThis_178 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 376))(this, pThis_1842);
                  (*(void (/*thiscall*/ **)(int, int, int))(v63 + 592))(this, 60001, pThis_178);
                  v69 = Block == (void *)1;
                  pThis_784 += 360;
                  Block = (char *)Block - 1;
                }
                while ( !v69 );
              }
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "FT_KENSIN",
              -1,
              0,
              0);
            break;
          case 15:
            if ( *(uint32_t *)(this + 8268) == 0 )
            {
              *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
              v280 = 2;
              if ( *(float *)&Block == 0.0 )
              {
                pThis_6C = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )
              {
                pThis_6C = sub_431920(this + 108, (char)"Effect/Animation/RoarStun1.ani", 1);
              }
              else
              {
                pThis_6C = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun1.ani", 1);
              }
              v280 = -1;
              *(uint32_t *)(this + 8268) = pThis_6C;
              *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
              v280 = 3;
              if ( *(float *)&Block == 0.0 )
              {
                pThis_6C2 = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )
              {
                pThis_6C2 = sub_431920(this + 108, (char)"Effect/Animation/RoarStun2.ani", 1);
              }
              else
              {
                pThis_6C2 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun2.ani", 1);
              }
              v280 = -1;
              *(uint32_t *)(this + 8272) = pThis_6C2;
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, uint32_t))(*(uint32_t *)this + 204))(
              this,
              1,
              *(uint32_t *)(this + 8268),
              0,
              -65,
              1,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, uint32_t))(*(uint32_t *)this + 204))(
              this,
              1,
              *(uint32_t *)(this + 8272),
              0,
              -65,
              1,
              0);
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              v72 = *(uint32_t *)this;
              pThis_4744 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                      this,
                      15,
                      0,
                      0,
                      0,
                      0,
                      0,
                      4,
                      0,
                      0,
                      0);
              (*(void (/*thiscall*/ **)(int, int, int))(v72 + 580))(this, 21005, pThis_4744);
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "FT_SAJAHU_CAST",
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "SAJAHU_SPREAD",
              -1,
              0,
              0);
            *(uint8_t *)(this + 8276) = 0;
            break;
          case 40:
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 40);
              pThis_4745 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 40);
              if ( *(uint32_t *)(this + 8280) == 0 )
                *(uint32_t *)(this + 8280) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(
                                             this,
                                             "Particle/SpiralNen.ptl");
              *(uint32_t *)(*(uint32_t *)(this + 8280) + 85) = sub_47EF20(1, pThis_4745, -1, -1, 11);
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                this,
                21007,
                pThis_4745,
                *(uint32_t *)(this + 8280),
                0,
                0,
                0,
                50,
                1,
                this,
                0,
                0);
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "FT_SPIRAL_NEN",
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "BUFF_SPIRAL_NEN",
              -1,
              0,
              0);
            break;
          default:
            if ( fld_2038 == 42 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              v75 = *(uint32_t *)this;
              pThis_4746 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                      this,
                      42,
                      0,
                      0,
                      0,
                      0,
                      0,
                      4,
                      0,
                      0,
                      0);
              (*(void (/*thiscall*/ **)(int, int, int))(v75 + 580))(this, 21010, pThis_4746);
            }
            break;
        }
      }
      goto LABEL_251;
    case 18:
      v77 = *(uint32_t *)this;
      v260 = *pArg3[1];
      *(uint32_t *)(this + 8284) = v260;
      v78 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(v77 + 1160))(this, v260);
      fld_205C = *(uint32_t *)(this + 8284);
      if ( fld_205C == 9 || fld_205C == 18 )
      {
        v80 = sub_47E9D0(v78, 0);
      }
      else
      {
        if ( fld_205C != 49 )
          goto LABEL_137;
        v80 = sub_47E9D0(v78, 7u);
      }
      *(uint32_t *)(this + 8288) = v80;
LABEL_137:
      fld_205C2 = *(uint32_t *)(this + 8284);
      if ( fld_205C2 == 9 || fld_205C2 == 49 )
      {
        fld_1848 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 20);
      }
      else
      {
        if ( fld_205C2 != 18 )
          goto LABEL_143;
        fld_1848 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 48);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, fld_1848);
LABEL_143:
      if ( fld_199C == 11 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 51) > 0 )
      {
        pThis_4747 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 1140))(this, 51, -1, -1, 11);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)this + 1160))(this, 51, 0, pThis_4747);
        fld_2060 = sub_47EF20(v262, v263, v264, v265, LODWORD(v266)) + *(uint32_t *)(this + 8288);
        fld_702 = *(uint32_t *)(this + 112);
        *(uint32_t *)(this + 8288) = fld_2060;
        v86 = (uint64_t)fabs(*(float *)(fld_702 + 16));
        HIDWORD(v86) = *(uint32_t *)this;
        LODWORD(v266) = 1;
        v265 = -500 * (int)v86 / fld_2060;
        (*(void (/*thiscall*/ **)(int, uint32_t))(HIDWORD(v86) + 876))(this, 0);
        *(uint32_t *)(this + 8296) = -250;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);
      v87 = *(uint32_t *)this;
      pThis_984 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v87 + 896))(this, pThis_984);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 456);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FT_HOLD",
        -1,
        0,
        0);
      fld_2114 = *(uint32_t *)(this + 8468);
      v90 = fld_2114 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_2114 + 80))(fld_2114) != 0;
      *(uint8_t *)(this + 8292) = v90;
      if ( v90 )
        *(uint32_t *)(this + 464) = -998637568;
LABEL_251:
      sub_4B89D0(nArg2, pArg3, *(float *)&nArg4, *(float *)&nArg5);
      result = nArg2 - 6;
      switch ( nArg2 )
      {
        case 6:
          result = *(uint32_t *)(this + 6892);
          if ( result == 0 )
          {
            result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);
            if ( result > 0 )
            {
              v235 = *(uint32_t *)this;
              *(uint32_t *)(this + 8444) = 0;
              v257 = (*(int (/*thiscall*/ **)(int, int, int))(v235 + 1140))(this, 17, -1);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);
              result = sub_47EF20(17, 1, v257, -1, 11);
              *(uint32_t *)(this + 8448) = result;
            }
          }
          return result;
        case 7:
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "JUMP_KICK",
            -1,
            0,
            0);
          return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                   this,
                   "R_FT_KICK_JUMP",
                   -1,
                   0,
                   0);
        case 8:
          if ( fld_199C != 8 )
          {
            v213 = pArg3[1];
            if ( v213 != nullptr && (unsigned int)(pArg3[2] - v213) > 1 )
              v214 = v213[1];
            else
              v214 = -1;
            *(uint32_t *)(this + 8216) = v214;
          }
          if ( *(uint32_t *)(this + 8216) != -1 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1328))(this, 0);
          if ( *(uint32_t *)(this + 8216) == 46 )
          {
            pThis_4882 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 46);
            pThis_4748 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 46);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1520);
            pThis_1843 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
            *(float *)(this + 388) = (float)sub_47EFD0(pThis_4882, COERCE_FLOAT(2), pThis_4748, pThis_1843, pThis_1843, 0);
            *(uint32_t *)(this + 452) = sub_47EF20(0, pThis_4748, -1, -1, 11);
            v218 = sub_47EF20(1, pThis_4748, -1, -1, 11);
            v219 = *(uint32_t *)this;
            *(uint32_t *)(this + 456) = v218;
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v219 + 212))(
              this,
              "FT_HAMMER_KICK",
              -1,
              0,
              0);
          }
          if ( sub_41A5E0(this + 7028) != 0 )
          {
            if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )
            {
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "R_FT_ATK",
                -1,
                0,
                0);
              v223 = *(uint32_t *)this;
              pThis_494 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
              (*(void (/*thiscall*/ **)(int, int))(v223 + 212))(this, pThis_494);
              pThis_4942 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
              return sub_406D60(pThis_4942);
            }
            else
            {
              result = sub_41A5E0(this + 7028);
              if ( result == 3 && *(uint32_t *)(this + 8216) != 46 )
              {
                (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                  this,
                  "R_FT_KICK_AX",
                  -1,
                  0,
                  0);
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "KICK_AX",
                         -1,
                         0,
                         0);
              }
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
              this,
              "R_FT_ATK",
              -1,
              0,
              0);
            v220 = *(uint32_t *)this;
            pThis_4943 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
            (*(void (/*thiscall*/ **)(int, int))(v220 + 212))(this, pThis_4943);
            pThis_4944 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 2);
            return sub_406D60(pThis_4944);
          }
          return result;
        case 10:
          if ( *(uint32_t *)(this + 7812) == 1 )
          {
            if ( fld_199C != 10 )
              *(uint32_t *)(this + 8404) = 0;
            fld_20D0 = *(uint32_t *)(this + 8400);
            if ( fld_20D0 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_20D0 + 80))(fld_20D0) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(
                this,
                0,
                0,
                2 * *(uint32_t *)(this + 6652),
                2 * *(uint32_t *)(this + 6656));
              if ( *(uint32_t *)(this + 7808) == 0 )
              {
                *(int *)(this + 7820) /= 2;
                *(int *)(this + 7824) /= 2;
              }
            }
          }
          result = *(uint32_t *)(this + 7812);
          if ( result != 0 )
            return result;
          fld_1E882 = *(uint32_t *)(this + 7816);
          if ( (fld_1E882 == 12 || fld_1E882 == 16) && *(uint32_t *)(this + 8380) == 0 )
          {
            v281 = (void *)sub_42FCB0(228);
            v280 = 10;
            if ( v281 != nullptr )
            {
              if ( *(uint32_t *)(this + 384) < 0x10u )
                pThis_6C3 = sub_431920(this + 108, (char)"Effect/Animation/EnergyCharge.ani", 1);
              else
                pThis_6C3 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyCharge.ani", 1);
            }
            else
            {
              pThis_6C3 = 0;
            }
            v280 = -1;
            *(uint32_t *)(this + 8380) = pThis_6C3;
          }
          if ( *(uint32_t *)(this + 7816) == 16 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 16);
            sub_47DCD0(this, -1);
          }
          result = *(uint32_t *)(this + 7816);
          switch ( result )
          {
            case 13:
              *(uint8_t *)(this + 8376) = 0;
LABEL_303:
              if ( *(uint32_t *)(this + 7808) == 1 )
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "FT_HELLTER",
                         -1,
                         0,
                         0);
              return result;
            case 12:
              result = *(uint32_t *)(this + 7808);
              if ( result != 0 )
              {
                if ( result == 1 )
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));
                  if ( *(uint32_t *)(this + 8388) == 0 )
                  {
                    v282 = (void *)sub_42FCB0(228);
                    v280 = 11;
                    if ( v282 != nullptr )
                    {
                      if ( *(uint32_t *)(this + 384) < 0x10u )
                        pThis_6C4 = sub_431920(this + 108, (char)"Effect/Animation/EnergyBallShoot.ani", 1);
                      else
                        pThis_6C4 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyBallShoot.ani", 1);
                    }
                    else
                    {
                      pThis_6C4 = 0;
                    }
                    v280 = -1;
                    *(uint32_t *)(this + 8388) = pThis_6C4;
                  }
                  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                    this,
                    1,
                    *(uint32_t *)(this + 8388),
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
                    this,
                    0,
                    200,
                    200,
                    0,
                    -10000,
                    1);
                  v240 = *(uint32_t *)this;
                  pThis_985 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
                  result = (*(int (/*thiscall*/ **)(int, int))(v240 + 896))(this, pThis_985);
                  *(uint8_t *)(this + 8392) = 0;
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                  this,
                  1,
                  *(uint32_t *)(this + 8380),
                  0,
                  0,
                  0,
                  0);
                *(uint32_t *)(this + 8396) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(
                                             this,
                                             "Particle/EnergyBall.ptl");
                *(uint8_t *)(this + 8384) = 0;
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "FT_NENTAN",
                         -1,
                         0,
                         0);
              }
              break;
            case 16:
              result = *(uint32_t *)(this + 7808);
              if ( result != 0 )
              {
                if ( result == 1 )
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));
                  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
                    this,
                    0,
                    200,
                    200,
                    0,
                    -10000,
                    1);
                  v243 = *(uint32_t *)this;
                  pThis_986 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
                  (*(void (/*thiscall*/ **)(int, int))(v243 + 896))(this, pThis_986);
                  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v245 = *(uint32_t *)this;
                    pThis_4749 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                             this,
                             16,
                             0,
                             0,
                             107,
                             1,
                             62,
                             4,
                             0,
                             0,
                             0);
                    (*(void (/*thiscall*/ **)(int, int, int))(v245 + 580))(this, 21006, pThis_4749);
                  }
                  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                           this,
                           "FT_ENERGY_SHOT",
                           -1,
                           0,
                           0);
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                  this,
                  1,
                  *(uint32_t *)(this + 8380),
                  0,
                  0,
                  0,
                  0);
                v242 = *(uint32_t *)this;
                *(uint8_t *)(this + 8384) = 0;
                (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v242 + 212))(
                  this,
                  "ENERGYING",
                  -1,
                  0,
                  0);
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "FT_ENERGYING",
                         -1,
                         0,
                         0);
              }
              break;
            case 49:
              result = *(uint32_t *)(this + 7808);
              if ( result != 0 )
              {
                if ( result == 1 )
                {
                  result = (int)pArg3[1];
                  v254 = *(uint32_t *)(result + 4);
                  if ( v254 != 4 )
                    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 148))(this, v254);
                }
              }
              else
              {
                v247 = sub_45EBE0(pArg3[1][10], pArg3[1][11]);
                pObj2 = __RTDynamicCast(
                         v247,
                         0,
                         &CNRDObject `RTTI Type Descriptor',
                         &IRDActiveObject `RTTI Type Descriptor',
                         0);
                *(uint32_t *)(this + 8300) = pObj2;
                if ( pObj2 != 0 )
                {
                  v249 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
                  fld_206C5 = *(uint32_t *)(this + 8300);
                  *(uint32_t *)(this + 8304) = v249;
                  v251 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C5 + 124))(fld_206C5);
                  fld_206C6 = *(uint32_t *)(this + 8300);
                  *(uint32_t *)(this + 8308) = v251;
                  *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C6 + 128))(fld_206C6);
                }
                if ( *(uint32_t *)(this + 8300) != 0 )
                {
                  if ( *(uint32_t *)(this + 8408) == 0 )
                  {
                    pMem = operator new(0x68u);
                    v280 = 12;
                    if ( pMem != nullptr )
                      v253 = sub_5E4FC0(this);
                    else
                      v253 = 0;
                    v280 = -1;
                    *(uint32_t *)(this + 8408) = v253;
                  }
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8408)
                                                                                           + 56))(
                    *(uint32_t *)(this + 8408),
                    *(uint32_t *)(this + 8300),
                    this,
                    0,
                    0,
                    0,
                    -1);
                }
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(
                  this,
                  *(uint32_t *)(*(uint32_t *)(this + 6216) + 20));
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "FT_ROPLING",
                         -1,
                         0,
                         0);
              }
              break;
            case 52:
              *(uint8_t *)(this + 8377) = 0;
              goto LABEL_303;
            default:
              return result;
          }
          return result;
        case 12:
          v226 = pArg3[1];
          if ( v226 != nullptr && pArg3[2] - v226 != 0 )
            result = *v226;
          else
            result = -1;
          *(uint32_t *)(this + 8220) = result;
          if ( result == 1 )
          {
            pThis_4883 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 1);
            fld_201C = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1368);
            pThis_1844 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
            result = sub_47EFD0(pThis_4883, 0.0, fld_201C, pThis_1844, pThis_1844, 0);
            *(uint32_t *)(this + 8224) = 0;
            *(float *)(this + 388) = (float)result;
            *(uint8_t *)(this + 8228) = 0;
          }
          else if ( result == 2 )
          {
            pThis_4884 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);
            fld_201C2 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));
            v232 = *(uint32_t *)this;
            fld_201C22 = fld_201C2;
            *(uint32_t *)(this + 396) = 0;
            v234 = (*(int (/*thiscall*/ **)(int))(v232 + 388))(this);
            result = sub_47EFD0(pThis_4884, COERCE_FLOAT(2), fld_201C22, v234, v234, 0);
            *(float *)(this + 388) = (float)result;
          }
          return result;
        case 14:
          result = *(uint32_t *)(this + 7964);
          switch ( result )
          {
            case 176:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_ANCIENT_MEMORY",
                       -1,
                       0,
                       0);
            case 175:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_LEAP_BUFF",
                       -1,
                       0,
                       0);
            case 36:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_SUN_CURTAIN",
                       -1,
                       0,
                       0);
            case 31:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_FAST_FIST_BUFF",
                       -1,
                       0,
                       0);
            case 37:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_STRONG_FIST",
                       -1,
                       0,
                       0);
            case 39:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "FT_FATAL_SPOT",
                       -1,
                       0,
                       0);
            case 38:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "R_FT_POISON_SPREAD",
                       -1,
                       0,
                       0);
            default:
              break;
          }
          return result;
        default:
          return result;
      }
    case 19:
      v91 = sub_45EBE0(*pArg3[1], pArg3[1][1]);
      pObj4 = __RTDynamicCast(v91, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      *(uint32_t *)(this + 8300) = pObj4;
      if ( pObj4 != 0 )
      {
        v93 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 120))(pObj4);
        fld_206C7 = *(uint32_t *)(this + 8300);
        *(uint32_t *)(this + 8304) = v93;
        v95 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C7 + 124))(fld_206C7);
        fld_206C8 = *(uint32_t *)(this + 8300);
        *(uint32_t *)(this + 8308) = v95;
        *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C8 + 128))(fld_206C8);
      }
      *(uint32_t *)(this + 8316) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
      *(uint8_t *)(this + 8326) = 0;
      *(uint32_t *)(this + 8328) = 0;
      *(uint8_t *)(this + 8332) = 0;
      *(uint8_t *)(this + 8333) = 0;
      fld_206C9 = *(uint32_t *)(this + 8300);
      *(uint8_t *)(this + 8324) = pArg3[1][2] != 0;
      *(uint8_t *)(this + 8325) = pArg3[1][3] != 0;
      if ( fld_206C9 != 0 )
      {
        if ( *(uint32_t *)(this + 8320) == 0 )
        {
          *(float *)&Block = COERCE_FLOAT(operator new(0x6Cu));
          v280 = 4;
          if ( *(float *)&Block == 0.0 )
            v98 = 0;
          else
            v98 = sub_5E4DC0(this);
          v280 = -1;
          *(uint32_t *)(this + 8320) = v98;
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8320) + 120))(
          *(uint32_t *)(this + 8320),
          *(uint8_t *)(this + 8324));
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8320) + 124))(
          *(uint32_t *)(this + 8320),
          *(uint8_t *)(this + 8325));
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8320) + 56))(
          *(uint32_t *)(this + 8320),
          *(uint32_t *)(this + 8300),
          this,
          0,
          0,
          0,
          -1);
      }
      v99 = *(uint32_t *)this;
      if ( *(uint8_t *)(this + 8324) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(v99 + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 52));
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "FT_SPIRE",
          -1,
          0,
          0);
        pThis_20902 = (uint32_t **)(this + 8336);
        if ( *(uint32_t *)(this + 8336) == 0 )
        {
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
          v280 = 5;
          if ( *(float *)&Block == 0.0 )
          {
            pThis_6C5 = nullptr;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )
          {
            pThis_6C5 = (uint32_t *)sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);
          }
          else
          {
            pThis_6C5 = (uint32_t *)sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);
          }
          v280 = -1;
          *pThis_20902 = pThis_6C5;
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
          v280 = 6;
          if ( *(float *)&Block == 0.0 )
          {
            pThis_6C6 = 0;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )
          {
            pThis_6C6 = sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);
          }
          else
          {
            pThis_6C6 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);
          }
          v280 = -1;
          *(uint32_t *)(this + 8340) = pThis_6C6;
        }
        fld_206C10 = *(uint32_t *)(this + 8300);
        *(float *)&Block = 1.0;
        if ( fld_206C10 != 0 )
        {
          v104 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C10 + 192))(fld_206C10);
          *(float *)&Block = sub_4049C0(1.0, 3.0, v104 - 100, 150);
        }
        Block2 = Block;
        pThis_4742 = 2;
        do
        {
          sub_4920E0(*pThis_20902++, *(float *)&Block2, *(float *)&Block2);
          --pThis_4742;
        }
        while ( *(float *)&pThis_4742 != 0.0 );
        *(uint8_t *)(this + 8334) = 0;
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(v99 + 1140))(this, 22) <= 0 )
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX");
        else
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX_CRASH");
        v106 = *(uint32_t *)this;
        fld_18482 = *(uint32_t *)(this + 6216);
        if ( *(uint8_t *)(this + 8325) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int))(v106 + 196))(
            this,
            *(uint32_t *)(fld_18482 + 28),
            -1,
            0,
            0,
            v265);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "G_BACK_SUPLEX_START",
            -1,
            0,
            0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int))(v106 + 196))(
            this,
            *(uint32_t *)(fld_18482 + 24),
            -1,
            0,
            0,
            v265);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "G_SUPLEX_START",
            -1,
            0,
            0);
        }
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      sub_495890(2, 0);
      fld_22C = *(uint32_t *)(this + 556);
      if ( *(uint8_t *)(this + 8324) != 0 )
        v109 = fld_22C + 1064;
      else
        v109 = fld_22C + 608;
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 344))(v109);
      fld_20842 = *(uint8_t *)(this + 8324) != 0 ? 18 : 9;
      pThis_1845 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      pThis_47410 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, fld_20842);
      v113 = *(uint32_t *)this;
      Block = pThis_47410;
      v114 = (char *)(*(int (/*thiscall*/ **)(int, int))(v113 + 1160))(this, fld_20842);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v114, 0.0, (int)Block, pThis_1845, pThis_1845, 0));
      fld_20852 = *(uint8_t *)(this + 8325);
      *(float *)(this + 388) = (float)(int)Block;
      if ( fld_20852 != 0 )
      {
        pThis_4885 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 10);
        pThis_47411 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 10);
        pThis_1846 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4885, 0.0, pThis_47411, pThis_1846, pThis_1846, 0));
        *(float *)(this + 388) = (double)(int)Block + *(float *)(this + 388);
        *(float *)&Block = COERCE_FLOAT(sub_47EF20(2, pThis_47411, -1, -1, 11));
        *(float *)(this + 460) = (double)(int)Block + *(float *)(this + 460);
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "HOLD", -1, 0, 0);
      goto LABEL_251;
    case 20:
      v119 = *pArg3[1];
      *(uint32_t *)(this + 8344) = v119;
      if ( v119 != 0 )
      {
        fld_18483 = *(uint32_t *)(this + 6216);
        if ( *(uint32_t *)(this + 8348) % 2 != 0 )
          fld_18484 = *(uint32_t *)(fld_18483 + 40);
        else
          fld_18484 = *(uint32_t *)(fld_18483 + 36);
      }
      else
      {
        fld_18484 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 32);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, fld_18484);
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      if ( fld_199C != 20 )
      {
        v122 = *(uint32_t *)this;
        *(uint32_t *)(this + 8348) = 0;
        *(uint8_t *)(this + 8360) = 0;
        *(uint32_t *)(this + 8364) = (*(int (/*thiscall*/ **)(int))(v122 + 120))(this);
        *(uint32_t *)(this + 8368) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);
        v123 = sub_45EBE0(pArg3[1][1], pArg3[1][2]);
        pObj3 = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(uint32_t *)(this + 8356) = pObj3;
        if ( pObj3 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 776))(pObj3, 3) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 0);
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 768))(
              *(uint32_t *)(this + 8356),
              3,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 1);
          }
          fld_20A42 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 688))(*(uint32_t *)(this + 8356))
                           + 20);
          v126 = sub_42FC90(fld_20A42);
          v127 = (int *)sub_4924C0(v126 - 1);
          v128 = *v127;
          if ( *v127 != 0 )
          {
            if ( (unsigned int)((*(uint32_t *)(v128 + 20) >> 2) + 40) <= 0x50 )
              v129 = 80;
            else
              v129 = (*(uint32_t *)(v128 + 20) >> 2) + 40;
            v130 = sub_4918E0(v127, 0);
            fld_20A43 = *(uint32_t *)(this + 8356);
            *(uint32_t *)(this + 8372) = v129 - v130;
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_20A43 + 152))(fld_20A43) == 0 )
              *(uint32_t *)(this + 8372) = -*(uint32_t *)(this + 8372);
            v132 = *(uint32_t *)this;
            fld_20A44 = *(int **)(this + 8356);
            v134 = *fld_20A44;
            Block = fld_20A44;
            v135 = (*(int (/*stdcall*/ **)(uint32_t))(v134 + 124))(0);
            v136 = (*(int (/*thiscall*/ **)(int *, int))(*fld_20A44 + 120))(fld_20A44, v135 + 1);
            (*(void (/*thiscall*/ **)(int, int))(v132 + 112))(this, *(uint32_t *)(this + 8372) + v136);
            v137 = *(uint32_t *)this;
            fld_20A45 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 152))(*(uint32_t *)(this + 8356));
            v139 = sub_432E50(fld_20A45);
            (*(void (/*thiscall*/ **)(int, int))(v137 + 148))(this, v139);
          }
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 760);
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
        sub_406D60(pThis_4945);
        pThis_4886 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);
        pThis_47412 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 14);
        pThis_1847 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4886, 0.0, pThis_47412, pThis_1847, pThis_1847, 0));
        *(float *)(this + 388) = (float)(int)Block;
        *(uint32_t *)(this + 8352) = sub_47E9D0(pThis_4886, 0);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "RIDE", -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "FT_MOUNTAIN",
          -1,
          0,
          0);
      }
      if ( *(uint32_t *)(this + 8344) == 1 )
      {
        fld_20A46 = *(uint32_t *)(this + 8356);
        ++*(uint32_t *)(this + 8348);
        if ( fld_20A46 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
          {
            v144 = *(uint32_t *)this;
            *(float *)&v265 = 0.0;
            v266 = 0.0;
            v267 = 0.0;
            v268 = 0;
            v269 = 0;
            v270 = 0;
            if ( (*(int (/*thiscall*/ **)(int))(v144 + 152))(this) != 0 )
              pThis_35 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 53);
            else
              pThis_35 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 53);
            Block = pThis_35;
            v146 = (double)(int)pThis_35;
            v147 = *(uint32_t *)this;
            *(float *)&v265 = v146;
            v148 = (void *)(*(int (/*thiscall*/ **)(int))(v147 + 124))(this);
            v149 = *(uint32_t *)this;
            Block = v148;
            v266 = (float)(int)v148;
            v150 = (*(int (/*thiscall*/ **)(int))(v149 + 128))(this);
            fld_20A47 = *(uint32_t *)(this + 8356);
            Block = (void *)(v150 + 17);
            v267 = (float)(v150 + 17);
            sub_4E5F70(pThis_47412, this, fld_20A47, (float *)&v265, 1, 1);
          }
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);
          sub_47DCD0(this, -1);
        }
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "R_FT_MOUNTAIN_ATK",
          -1,
          0,
          0);
      }
      goto LABEL_251;
    case 21:
      LOBYTE(nArg4) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 44));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 912);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);
      fld_20FC = *(uint32_t *)(this + 8444) + 1;
      ++*(uint32_t *)(this + 6896);
      v153 = *(uint32_t *)this;
      *(uint32_t *)(this + 8444) = fld_20FC;
      v154 = (*(int (/*thiscall*/ **)(int))(v153 + 388))(this);
      pThis_47413 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);
      pThis_4887 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 17);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4887, 0.0, pThis_47413, v154, v154, 0));
      *(float *)(this + 388) = (float)(int)Block;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FT_SKYSTEP",
        -1,
        0,
        0);
      goto LABEL_251;
    case 22:
      pThis_47414 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 19);
      pThis_4888 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 19);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 56));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1216);
      pThis_1848 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4888, 0.0, pThis_47414, pThis_1848, pThis_1848, 0));
      *(float *)(this + 388) = (float)(int)Block;
      v160 = (void *)sub_47EF20(1, pThis_47414, -1, -1, 11);
      v161 = *(uint32_t *)this;
      Block = v160;
      *(float *)&pThis_4742 = (double)(int)v160 * 0.0099999998 + 1.0;
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v161 + 876))(this, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v162 = *(uint32_t *)this;
      pThis_2A0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
      *(float *)&Block = COERCE_FLOAT(sub_495500(pThis_2A0));
      (*(void (/*fastcall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t))(v162 + 888))(
        this,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742) >> 32,
        0,
        0,
        1000,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      if ( *(uint32_t *)(this + 8412) == 0 )
      {
        *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
        v280 = 7;
        if ( *(float *)&Block == 0.0 )
        {
          pThis_6C7 = 0;
        }
        else if ( *(uint32_t *)(this + 384) < 0x10u )
        {
          pThis_6C7 = sub_431920(this + 108, (char)"Effect/Animation/ClosePunchExecute.ani", 1);
        }
        else
        {
          pThis_6C7 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ClosePunchExecute.ani", 1);
        }
        v280 = -1;
        *(uint32_t *)(this + 8412) = pThis_6C7;
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        1,
        *(uint32_t *)(this + 8412),
        33,
        -49,
        0,
        0);
      sub_5E5260((void **)(this + 8416));
      v165 = *(uint32_t *)this;
      *(uint32_t *)(this + 8432) = 0;
      *(uint8_t *)(this + 8436) = 0;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v165 + 212))(this, "FT_ONEINCH", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "ONE_INCH_PUNCH",
        -1,
        0,
        0);
      goto LABEL_251;
    case 23:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 8));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 152);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FT_UPPER_READY",
        -1,
        0,
        0);
      pThis_4889 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 5);
      pThis_47415 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 5);
      pThis_1849 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4889, COERCE_FLOAT(1), pThis_47415, pThis_1849, pThis_1849, 0));
      *(float *)(this + 388) = (float)(int)Block;
      *(uint32_t *)(this + 456) = sub_47EF20(2, pThis_47415, -1, -1, 11);
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, pThis_47415, -1, -1, 11));
      v169 = *(uint32_t *)this;
      *(float *)&pThis_4742 = (double)(int)Block * 0.0099999998 + 1.0;
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v169 + 876))(this, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      pThis_2A02 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
      *(float *)&Block = COERCE_FLOAT(sub_495500(pThis_2A02));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 888))(
        this,
        0,
        0,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742),
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      v171 = *(uint32_t *)this;
      pThis_987 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v171 + 896))(this, pThis_987);
      v173 = *(uint32_t *)this;
      *(uint8_t *)(this + 8437) = 0;
      v174 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v173 + 1172))(this, 1, -1, 0, 0);
      (*(void (/*thiscall*/ **)(int, int))(v173 + 212))(this, v174);
      pThis_4946 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
      sub_406D60(pThis_4946);
      goto LABEL_251;
    case 24:
      v176 = *(uint32_t *)this;
      *(uint32_t *)(this + 8472) = *pArg3[1];
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v176 + 876))(this, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      sub_495890(2, 0);
      if ( *(uint32_t *)(this + 8472) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
        LOBYTE(nArg5) = 0;
        v184 = sub_45EBE0(pArg3[1][1], pArg3[1][2]);
        pObj = __RTDynamicCast(v184, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(uint32_t *)(this + 8300) = pObj;
        if ( pObj != 0 )
        {
          v186 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          fld_206C11 = *(uint32_t *)(this + 8300);
          *(uint32_t *)(this + 8304) = v186;
          v188 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C11 + 124))(fld_206C11);
          fld_206C12 = *(uint32_t *)(this + 8300);
          *(uint32_t *)(this + 8308) = v188;
          *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_206C12 + 128))(fld_206C12);
          if ( *(uint32_t *)(this + 8480) == 0 )
          {
            *(float *)&Block = COERCE_FLOAT(operator new(0x64u));
            v280 = 8;
            if ( *(float *)&Block == 0.0 )
              v190 = 0;
            else
              v190 = sub_5E4ED0(this);
            v280 = -1;
            *(uint32_t *)(this + 8480) = v190;
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8480) + 56))(
            *(uint32_t *)(this + 8480),
            *(uint32_t *)(this + 8300),
            this,
            0,
            0,
            0,
            -1);
        }
        *(uint8_t *)(this + 8476) = 0;
        *(uint8_t *)(this + 8477) = 0;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SKYRADE_SWING",
          -1,
          0,
          0);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 60));
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1672);
        pThis_18410 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        pThis_47416 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);
        pThis_48810 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);
        v180 = (void *)sub_47EFD0(pThis_48810, 0.0, pThis_47416, pThis_18410, pThis_18410, 0);
        v181 = *(uint32_t *)this;
        Block = v180;
        *(float *)(this + 388) = (float)(int)v180;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v181 + 212))(this, "R_FT_ATK", -1, 0, 0);
        v182 = *(uint32_t *)this;
        pThis_4947 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(v182 + 212))(this, pThis_4947);
      }
      goto LABEL_251;
    case 26:
      v191 = *(uint32_t *)this;
      *(uint32_t *)(this + 8496) = *pArg3[1];
      v192 = (char *)(*(int (/*thiscall*/ **)(int, int))(v191 + 1160))(this, 54);
      pThis_47417 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 54);
      fld_21302 = *(uint32_t *)(this + 8496);
      if ( fld_21302 != 0 )
      {
        if ( fld_21302 == 1 )
        {
          fld_78 = *(void **)(this + 120);
          *(uint32_t *)(this + 8500) = pArg3[1][1];
          sub_4AECE0(fld_78, 2);
          sub_4939E0(*(uint32_t *)(this + 120), 0);
          LOBYTE(nArg5) = 0;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1824);
          pThis_18411 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
          v201 = (void *)sub_47EFD0(v192, 0.0, pThis_47417, pThis_18411, pThis_18411, 0);
          v202 = *(uint32_t *)this;
          Block = v201;
          v203 = (*(int (/*thiscall*/ **)(int))(v202 + 388))(this);
          v204 = sub_47EFD0(v192, COERCE_FLOAT(1), pThis_47417, v203, v203, 0);
          fld_2134 = (void *)sub_423A80(Block, v204, *(uint32_t *)(this + 8500), dword_9B9348);
          fld_21342 = *(uint32_t *)(this + 8500);
          Block = fld_2134;
          *(float *)(this + 388) = (float)(int)fld_2134;
          dword_9B93482 = dword_9B9348;
          fld_213422 = fld_21342;
          v256 = sub_47E9D0(v192, 3u);
          v207 = sub_47E9D0(v192, 2u);
          v208 = sub_423A80(v207, v256, fld_213422, dword_9B93482);
          Block = *(void **)this;
          v209 = sub_47E9D0(v192, 4u);
          (*((void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))Block + 219))(
            this,
            0,
            v208,
            v208,
            0,
            v209,
            1);
          *(uint32_t *)(this + 8504) = -200;
          *(uint32_t *)(this + 8516) = 0;
          if ( *(uint32_t *)(this + 8512) == 0 )
          {
            *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
            v280 = 9;
            if ( *(float *)&Block == 0.0 )
            {
              pThis_6C8 = 0;
            }
            else if ( *(uint32_t *)(this + 384) < 0x10u )
            {
              pThis_6C8 = sub_431920(this + 108, (char)"Effect/Animation/ShoulderTackle.ani", 1);
            }
            else
            {
              pThis_6C8 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ShoulderTackle.ani", 1);
            }
            v280 = -1;
            *(uint32_t *)(this + 8512) = pThis_6C8;
          }
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            1,
            *(uint32_t *)(this + 8512),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "FT_TK",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "QUICK_MOTION_02",
            -1,
            0,
            0);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 64));
        fld_703 = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));
        fld_7032 = fld_703;
        if ( (uint32_t)fld_703 != 0 )
          LODWORD(fld_703) = sub_47E9D0(v192, 1u);
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, int))(*(uint32_t *)this + 876))(
          this,
          0,
          fld_7032,
          fld_7032,
          0,
          fld_703,
          1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v197 = *(void (/*thiscall*/ ***)(int, int))this;
        pThis_988 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
        v197[224](this, pThis_988);
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 3, 3, 1000, 1000);
        *(uint32_t *)(this + 8508) = 0;
        sub_4BA610(4);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "FT_TK_READY",
          13,
          0,
          0);
      }
      goto LABEL_251;
    default:
      goto LABEL_251;
  }
}

