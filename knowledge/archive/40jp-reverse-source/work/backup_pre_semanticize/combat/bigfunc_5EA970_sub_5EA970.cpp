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
int /*thiscall*/ sub_5EA970(int this, int a2, uint32_t **a3, int a4, int a5)
{
  int v6; // ebx
  int v7; // eax
  int v8; // edx
  uint32_t *v9; // eax
  int v10; // eax
  uint32_t *v11; // edi
  int i; // ebx
  int v13; // ecx
  int v14; // ecx
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  char v20; // al
  int v21; // eax
  int v22; // ecx
  uint32_t *v23; // edi
  int v24; // eax
  uint32_t *v25; // edi
  int j; // ebx
  int v27; // ecx
  int v28; // edi
  int v29; // eax
  int v30; // eax
  uint32_t *k; // edi
  int v32; // eax
  int v33; // edi
  int v34; // edi
  int v35; // eax
  int v36; // edi
  int v37; // eax
  int v38; // edi
  int v39; // eax
  int v40; // edx
  int v41; // edi
  char *v42; // ebx
  int v43; // eax
  void *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // ecx
  int v49; // edi
  int v50; // eax
  int v51; // eax
  uint32_t *v52; // eax
  int v53; // ebx
  int v54; // edi
  int v55; // eax
  void *v56; // eax
  int v57; // edi
  uint64_t v58; // rax
  int v59; // ebx
  int v60; // eax
  int v61; // edi
  int v62; // eax
  int v63; // ebx
  int v64; // edi
  int v65; // eax
  int v66; // eax
  int v67; // eax
  int v68; // eax
  bool v69; // zf
  int v70; // eax
  int v71; // eax
  int v72; // edi
  int v73; // eax
  int v74; // edi
  int v75; // edi
  int v76; // eax
  int v77; // edx
  uint32_t *v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // ecx
  int v85; // eax
  uint64_t v86; // rax
  int v87; // edi
  int v88; // eax
  int v89; // ecx
  bool v90; // al
  int v91; // eax
  int v92; // eax
  int v93; // eax
  int v94; // ecx
  int v95; // eax
  int v96; // ecx
  int v97; // eax
  int v98; // eax
  int v99; // edx
  uint32_t **v100; // edi
  uint32_t *v101; // eax
  int v102; // eax
  int v103; // ecx
  int v104; // eax
  void *v105; // ebx
  int v106; // edx
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // edi
  int v111; // ebx
  void *v112; // eax
  int v113; // edx
  char *v114; // eax
  char v115; // al
  char *v116; // edi
  int v117; // ebx
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // edx
  int v123; // eax
  int v124; // eax
  int v125; // edi
  int v126; // eax
  int *v127; // eax
  int v128; // ecx
  int v129; // edi
  int v130; // eax
  int v131; // ecx
  int v132; // ebx
  int *v133; // edi
  int v134; // edx
  int v135; // eax
  int v136; // eax
  int v137; // edi
  int v138; // eax
  int v139; // eax
  void *v140; // eax
  char *v141; // edi
  int v142; // eax
  int v143; // eax
  int v144; // edx
  void *v145; // eax
  double v146; // st7
  int v147; // eax
  void *v148; // eax
  int v149; // edx
  int v150; // eax
  int v151; // ecx
  int v152; // edi
  int v153; // edx
  int v154; // edi
  int v155; // ebx
  char *v156; // eax
  int v157; // edi
  char *v158; // ebx
  int v159; // eax
  void *v160; // eax
  int v161; // edx
  int v162; // edi
  int v163; // eax
  int v164; // eax
  int v165; // edx
  char *v166; // edi
  int v167; // ebx
  int v168; // eax
  int v169; // eax
  int v170; // eax
  int v171; // edi
  int v172; // eax
  int v173; // edi
  int v174; // eax
  void *v175; // eax
  int v176; // edx
  int v177; // edi
  int v178; // ebx
  char *v179; // eax
  void *v180; // eax
  int v181; // edx
  int v182; // edi
  int v183; // eax
  int v184; // eax
  int v185; // eax
  int v186; // eax
  int v187; // ecx
  int v188; // eax
  int v189; // ecx
  int v190; // eax
  int v191; // eax
  char *v192; // edi
  int v193; // ebx
  int v194; // eax
  uint64_t v195; // rax
  int v196; // ebx
  void (/*thiscall*/ **v197)(int, int); // edi
  int v198; // eax
  void *v199; // ecx
  int v200; // eax
  void *v201; // eax
  int v202; // edx
  int v203; // eax
  int v204; // eax
  void *v205; // eax
  int v206; // edx
  int v207; // eax
  int v208; // ebx
  int v209; // eax
  int v210; // eax
  int result; // eax
  uint32_t *v213; // ecx
  int v214; // ecx
  char *v215; // edi
  int v216; // ebx
  int v217; // eax
  int v218; // eax
  int v219; // edx
  int v220; // edi
  int v221; // eax
  void *v222; // eax
  int v223; // edi
  int v224; // eax
  void *v225; // eax
  int *v226; // ecx
  char *v227; // edi
  int v228; // ebx
  int v229; // eax
  char *v230; // edi
  int v231; // eax
  int v232; // edx
  int v233; // ebx
  int v234; // eax
  int v235; // edx
  int v236; // ecx
  int v237; // eax
  int v238; // eax
  int v239; // eax
  int v240; // edi
  int v241; // eax
  int v242; // edx
  int v243; // edi
  int v244; // eax
  int v245; // edi
  int v246; // eax
  int v247; // eax
  int v248; // eax
  int v249; // eax
  int v250; // ecx
  int v251; // eax
  int v252; // ecx
  int v253; // eax
  int v254; // ecx
  int v255; // [esp-Ch] [ebp-60h]
  int v256; // [esp-Ch] [ebp-60h]
  int v257; // [esp-Ch] [ebp-60h]
  int v258; // [esp-8h] [ebp-5Ch]
  int v259; // [esp-4h] [ebp-58h]
  int v260; // [esp-4h] [ebp-58h]
  int v261; // [esp-4h] [ebp-58h]
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
  int v276; // [esp+38h] [ebp-1Ch] BYREF
  int v277; // [esp+3Ch] [ebp-18h] BYREF
  int v278; // [esp+40h] [ebp-14h] BYREF
  int v279; // [esp+44h] [ebp-10h]
  int v280; // [esp+50h] [ebp-4h]
  void *v281; // [esp+60h] [ebp+Ch]
  void *v282; // [esp+60h] [ebp+Ch]
  void *v283; // [esp+60h] [ebp+Ch]

  v279 = *(uint32_t *)(this + 6556);
  v6 = 0;
  switch ( v279 )
  {
    case 10:
      if ( *(uint32_t *)(this + 7812) == 0 )
      {
        v7 = *(uint32_t *)(this + 7816);
        if ( v7 == 12 )
        {
          v8 = *(uint32_t *)this;
          if ( *(uint32_t *)(this + 7808) != 0 )
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8388));
          else
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8380));
        }
        else if ( v7 == 16 )
        {
          if ( *(uint32_t *)(this + 7808) == 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));
        }
        else if ( v7 == 49 && a2 != 10 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 604))(this);
          sub_5E6920(this);
          sub_49C620(0, 1, 0);
          v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1160))(this, 49, 8);
          v10 = sub_47E9D0(v9, 1u);
          sub_49C5F0(0, 0, 0, v10);
        }
      }
      break;
    case 17:
      if ( *(uint32_t *)(this + 8244) == 1 && *(uint32_t *)(this + 8248) == 15 )
      {
        v11 = (uint32_t *)(this + 8268);
        for ( i = 2; i != 0; --i )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *v11++);
        v6 = 0;
      }
      break;
    case 18:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);
      if ( *(uint8_t *)(this + 8292) != 0 )
        goto LABEL_62;
      break;
    case 19:
      v13 = *(uint32_t *)(this + 8300);
      if ( v13 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 308))(v13) != 0 )
        {
          v14 = *(uint32_t *)(this + 8300);
          if ( *(uint8_t *)(this + 8325) != 0 )
            v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 192))(v14) / 10;
          else
            v15 = 3 * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 192))(v14) / 4;
          if ( *(uint32_t *)(this + 8316) != 0 )
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - v15;
          else
            v16 = v15 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
          v17 = *(uint32_t *)(this + 8300);
          v278 = v16;
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 124))(v17);
          v19 = *(uint32_t *)(this + 8300);
          v277 = v18;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v19 + 136))(v19, v278, v18, 0) != 0
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8300) + 132))(
                 *(uint32_t *)(this + 8300),
                 0) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(
              *(uint32_t *)(this + 8300),
              v278,
              v277,
              0);
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(**(uint32_t **)(this + 8300) + 140))(
                      *(uint32_t *)(this + 8300),
                      &v278,
                      &v277,
                      v278,
                      v277,
                      100,
                      1,
                      1) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(
              *(uint32_t *)(this + 8300),
              v278,
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
          v20 = *(uint8_t *)(this + 8325);
          v280 = 0;
          if ( v20 != 0 )
            v21 = *(uint32_t *)(this + 8316);
          else
            v21 = sub_432E50(*(uint32_t *)(this + 8316));
          v276 = v21;
          sub_431230((int)&v271, &v276);
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
        v22 = *(uint32_t *)(this + 8320);
        *(uint32_t *)(this + 8300) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v22 + 76))(v22, 0);
        v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(
                          this,
                          *(uint8_t *)(this + 8324) != 0 ? 18 : 9);
        sub_49C620(0, 1, 0);
        v24 = sub_47E9D0(v23, 1u);
        sub_49C5F0(0, 0, 0, v24);
      }
      if ( *(uint8_t *)(this + 8324) != 0 && *(uint8_t *)(this + 8334) != 0 )
      {
        v25 = (uint32_t *)(this + 8336);
        for ( j = 2; j != 0; --j )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *v25++);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 12);
        *(uint8_t *)(this + 8334) = 0;
        v6 = 0;
      }
      break;
    case 20:
      if ( a2 != 20 )
      {
        v27 = *(uint32_t *)(this + 8356);
        if ( v27 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 308))(v27) != 0 )
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
        v29 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, 0);
        v30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v29);
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v28 + 136))(this, v30) == 0 )
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
      v32 = *(uint32_t *)(this + 8496);
      if ( v32 != 0 )
      {
        if ( v32 == 1 )
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
  if ( v279 == 21 || v279 == 6 )
  {
    v33 = a2;
    if ( a2 != 21 && a2 != 6 && *(int *)(this + 8444) > 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v34 = *(uint32_t *)this;
        v35 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);
        (*(void (/*thiscall*/ **)(int, int, int))(v34 + 1296))(this, 17, v35);
        v33 = a2;
      }
      *(uint32_t *)(this + 8444) = 0;
    }
  }
  else
  {
    v33 = a2;
  }
  if ( v33 == 25 )
  {
    v33 = 8;
    a2 = 8;
    v279 = 25;
  }
  switch ( v33 )
  {
    case 15:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 6216));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
      v36 = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);
      *(float *)&v276 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 2));
      v37 = 0;
      if ( v36 != 0 )
        v37 = sub_47EF20(1, v276, -1, -1, 11);
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
        this,
        0,
        v36,
        v36,
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
      v39 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v38 + 896))(this, v39);
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
        *(uint32_t *)(this + 8232) = sub_47EF20(0, v276, -1, -1, 11);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "FT_SIT", -1, 0, 0);
      goto LABEL_251;
    case 16:
      v40 = *(uint32_t *)this;
      v259 = *a3[1];
      *(uint32_t *)(this + 8240) = v259;
      v41 = (*(int (/*thiscall*/ **)(int, int))(v40 + 1140))(this, v259);
      v42 = (char *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)(this + 8240));
      v43 = *(uint32_t *)(this + 8240);
      if ( v43 == 4 )
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
      else if ( v43 == 6 )
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
      v46 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v42, COERCE_FLOAT(1), v41, v46, v46, 0));
      *(float *)(this + 388) = (float)(int)Block;
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, v41, -1, -1, 11));
      v47 = 0;
      v48 = 0;
      *(float *)&v276 = (double)(int)Block * 0.0099999998 + 1.0;
      if ( v279 == 8 )
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
        (uint64_t)((double)(int)Block * *(float *)&v276),
        (uint64_t)((double)(int)Block * *(float *)&v276));
      v49 = *(uint32_t *)this;
      v50 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v49 + 896))(this, v50);
      goto LABEL_251;
    case 17:
      v51 = *a3[1];
      v276 = 1000;
      *(uint32_t *)(this + 8244) = v51;
      if ( v51 != 0 )
      {
        v53 = *(uint32_t *)(this + 8260);
        v54 = *(uint32_t *)(this + 8264);
      }
      else
      {
        *(uint32_t *)(this + 8248) = a3[1][1];
        *(uint32_t *)(this + 8252) = a3[1][2];
        *(uint32_t *)(this + 8256) = a3[1][3];
        v52 = a3[1];
        v53 = v52[4];
        *(uint32_t *)(this + 8260) = v52[5];
        if ( (unsigned int)sub_41C5A0(a3) > 6 )
          v276 = a3[1][6];
        if ( (unsigned int)sub_41C5A0(a3) <= 7 )
        {
          v54 = v276;
          *(uint32_t *)(this + 8264) = 1000;
        }
        else
        {
          v54 = v276;
          *(uint32_t *)(this + 8264) = a3[1][7];
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
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, v53, v53, v54, v54);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252) = 1000
                                                              * *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252)
                                                              / *(uint32_t *)(this + 6656);
      if ( *(uint32_t *)(this + 8244) == 0 && v53 == 4 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 992))(this, *(uint32_t *)(this + 8252), 0);
      if ( *(uint32_t *)(this + 8244) == 1 )
      {
        v55 = *(uint32_t *)(this + 8248);
        switch ( v55 )
        {
          case 8:
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              v255 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, 8, -1);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);
              v56 = (void *)sub_47EF20(8, 0, v255, -1, 11);
              v276 = (int)v56;
              if ( (int)v56 > 0 )
              {
                v278 = 0;
                Block = v56;
                do
                {
                  v57 = v278 / v276;
                  v58 = (uint64_t)(sub_405400(v278 / v276) * 75.0);
                  HIDWORD(v58) = *(uint32_t *)this;
                  v59 = v58;
                  v277 = v58;
                  if ( (*(int (/*thiscall*/ **)(int))(HIDWORD(v58) + 152))(this) == 0 )
                    v277 = -v59;
                  v60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
                  v277 += v60;
                  v61 = (int)(dword_7930D4[0] * (uint64_t)(sub_4053E0(v57) * 75.0)) / 100;
                  v62 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);
                  v63 = *(uint32_t *)this;
                  v64 = v62 + v61;
                  v65 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                          this,
                          0,
                          0,
                          0,
                          0xFFFF,
                          0,
                          0,
                          0,
                          0);
                  v66 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 128))(this, v65);
                  v67 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)this + 388))(this, v277, v64, v66);
                  v68 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 376))(this, v67);
                  (*(void (/*thiscall*/ **)(int, int, int))(v63 + 592))(this, 60001, v68);
                  v69 = Block == (void *)1;
                  v278 += 360;
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
                v70 = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )
              {
                v70 = sub_431920(this + 108, (char)"Effect/Animation/RoarStun1.ani", 1);
              }
              else
              {
                v70 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun1.ani", 1);
              }
              v280 = -1;
              *(uint32_t *)(this + 8268) = v70;
              *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
              v280 = 3;
              if ( *(float *)&Block == 0.0 )
              {
                v71 = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )
              {
                v71 = sub_431920(this + 108, (char)"Effect/Animation/RoarStun2.ani", 1);
              }
              else
              {
                v71 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun2.ani", 1);
              }
              v280 = -1;
              *(uint32_t *)(this + 8272) = v71;
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
              v73 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
              (*(void (/*thiscall*/ **)(int, int, int))(v72 + 580))(this, 21005, v73);
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
              v74 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 40);
              if ( *(uint32_t *)(this + 8280) == 0 )
                *(uint32_t *)(this + 8280) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(
                                             this,
                                             "Particle/SpiralNen.ptl");
              *(uint32_t *)(*(uint32_t *)(this + 8280) + 85) = sub_47EF20(1, v74, -1, -1, 11);
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                this,
                21007,
                v74,
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
            if ( v55 == 42 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            {
              v75 = *(uint32_t *)this;
              v76 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
              (*(void (/*thiscall*/ **)(int, int, int))(v75 + 580))(this, 21010, v76);
            }
            break;
        }
      }
      goto LABEL_251;
    case 18:
      v77 = *(uint32_t *)this;
      v260 = *a3[1];
      *(uint32_t *)(this + 8284) = v260;
      v78 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(v77 + 1160))(this, v260);
      v79 = *(uint32_t *)(this + 8284);
      if ( v79 == 9 || v79 == 18 )
      {
        v80 = sub_47E9D0(v78, 0);
      }
      else
      {
        if ( v79 != 49 )
          goto LABEL_137;
        v80 = sub_47E9D0(v78, 7u);
      }
      *(uint32_t *)(this + 8288) = v80;
LABEL_137:
      v81 = *(uint32_t *)(this + 8284);
      if ( v81 == 9 || v81 == 49 )
      {
        v82 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 20);
      }
      else
      {
        if ( v81 != 18 )
          goto LABEL_143;
        v82 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 48);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, v82);
LABEL_143:
      if ( v279 == 11 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 51) > 0 )
      {
        v83 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 1140))(this, 51, -1, -1, 11);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)this + 1160))(this, 51, 0, v83);
        v84 = sub_47EF20(v262, v263, v264, v265, LODWORD(v266)) + *(uint32_t *)(this + 8288);
        v85 = *(uint32_t *)(this + 112);
        *(uint32_t *)(this + 8288) = v84;
        v86 = (uint64_t)fabs(*(float *)(v85 + 16));
        HIDWORD(v86) = *(uint32_t *)this;
        LODWORD(v266) = 1;
        v265 = -500 * (int)v86 / v84;
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
      v88 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v87 + 896))(this, v88);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 456);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FT_HOLD",
        -1,
        0,
        0);
      v89 = *(uint32_t *)(this + 8468);
      v90 = v89 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v89 + 80))(v89) != 0;
      *(uint8_t *)(this + 8292) = v90;
      if ( v90 )
        *(uint32_t *)(this + 464) = -998637568;
LABEL_251:
      sub_4B89D0(a2, a3, *(float *)&a4, *(float *)&a5);
      result = a2 - 6;
      switch ( a2 )
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
          if ( v279 != 8 )
          {
            v213 = a3[1];
            if ( v213 != nullptr && (unsigned int)(a3[2] - v213) > 1 )
              v214 = v213[1];
            else
              v214 = -1;
            *(uint32_t *)(this + 8216) = v214;
          }
          if ( *(uint32_t *)(this + 8216) != -1 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1328))(this, 0);
          if ( *(uint32_t *)(this + 8216) == 46 )
          {
            v215 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 46);
            v216 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 46);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1520);
            v217 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
            *(float *)(this + 388) = (float)sub_47EFD0(v215, COERCE_FLOAT(2), v216, v217, v217, 0);
            *(uint32_t *)(this + 452) = sub_47EF20(0, v216, -1, -1, 11);
            v218 = sub_47EF20(1, v216, -1, -1, 11);
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
              v224 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
              (*(void (/*thiscall*/ **)(int, int))(v223 + 212))(this, v224);
              v225 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
              return sub_406D60(v225);
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
            v221 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
            (*(void (/*thiscall*/ **)(int, int))(v220 + 212))(this, v221);
            v222 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 2);
            return sub_406D60(v222);
          }
          return result;
        case 10:
          if ( *(uint32_t *)(this + 7812) == 1 )
          {
            if ( v279 != 10 )
              *(uint32_t *)(this + 8404) = 0;
            v236 = *(uint32_t *)(this + 8400);
            if ( v236 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v236 + 80))(v236) != 0 )
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
          v237 = *(uint32_t *)(this + 7816);
          if ( (v237 == 12 || v237 == 16) && *(uint32_t *)(this + 8380) == 0 )
          {
            v281 = (void *)sub_42FCB0(228);
            v280 = 10;
            if ( v281 != nullptr )
            {
              if ( *(uint32_t *)(this + 384) < 0x10u )
                v238 = sub_431920(this + 108, (char)"Effect/Animation/EnergyCharge.ani", 1);
              else
                v238 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyCharge.ani", 1);
            }
            else
            {
              v238 = 0;
            }
            v280 = -1;
            *(uint32_t *)(this + 8380) = v238;
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
                        v239 = sub_431920(this + 108, (char)"Effect/Animation/EnergyBallShoot.ani", 1);
                      else
                        v239 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyBallShoot.ani", 1);
                    }
                    else
                    {
                      v239 = 0;
                    }
                    v280 = -1;
                    *(uint32_t *)(this + 8388) = v239;
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
                  v241 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
                  result = (*(int (/*thiscall*/ **)(int, int))(v240 + 896))(this, v241);
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
                  v244 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
                  (*(void (/*thiscall*/ **)(int, int))(v243 + 896))(this, v244);
                  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v245 = *(uint32_t *)this;
                    v246 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
                    (*(void (/*thiscall*/ **)(int, int, int))(v245 + 580))(this, 21006, v246);
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
                  result = (int)a3[1];
                  v254 = *(uint32_t *)(result + 4);
                  if ( v254 != 4 )
                    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 148))(this, v254);
                }
              }
              else
              {
                v247 = sub_45EBE0(a3[1][10], a3[1][11]);
                v248 = __RTDynamicCast(
                         v247,
                         0,
                         &CNRDObject `RTTI Type Descriptor',
                         &IRDActiveObject `RTTI Type Descriptor',
                         0);
                *(uint32_t *)(this + 8300) = v248;
                if ( v248 != 0 )
                {
                  v249 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v248 + 120))(v248);
                  v250 = *(uint32_t *)(this + 8300);
                  *(uint32_t *)(this + 8304) = v249;
                  v251 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v250 + 124))(v250);
                  v252 = *(uint32_t *)(this + 8300);
                  *(uint32_t *)(this + 8308) = v251;
                  *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v252 + 128))(v252);
                }
                if ( *(uint32_t *)(this + 8300) != 0 )
                {
                  if ( *(uint32_t *)(this + 8408) == 0 )
                  {
                    v283 = operator new(0x68u);
                    v280 = 12;
                    if ( v283 != nullptr )
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
          v226 = a3[1];
          if ( v226 != nullptr && a3[2] - v226 != 0 )
            result = *v226;
          else
            result = -1;
          *(uint32_t *)(this + 8220) = result;
          if ( result == 1 )
          {
            v227 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 1);
            v228 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1368);
            v229 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
            result = sub_47EFD0(v227, 0.0, v228, v229, v229, 0);
            *(uint32_t *)(this + 8224) = 0;
            *(float *)(this + 388) = (float)result;
            *(uint8_t *)(this + 8228) = 0;
          }
          else if ( result == 2 )
          {
            v230 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);
            v231 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));
            v232 = *(uint32_t *)this;
            v233 = v231;
            *(uint32_t *)(this + 396) = 0;
            v234 = (*(int (/*thiscall*/ **)(int))(v232 + 388))(this);
            result = sub_47EFD0(v230, COERCE_FLOAT(2), v233, v234, v234, 0);
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
      v91 = sub_45EBE0(*a3[1], a3[1][1]);
      v92 = __RTDynamicCast(v91, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      *(uint32_t *)(this + 8300) = v92;
      if ( v92 != 0 )
      {
        v93 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v92 + 120))(v92);
        v94 = *(uint32_t *)(this + 8300);
        *(uint32_t *)(this + 8304) = v93;
        v95 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v94 + 124))(v94);
        v96 = *(uint32_t *)(this + 8300);
        *(uint32_t *)(this + 8308) = v95;
        *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v96 + 128))(v96);
      }
      *(uint32_t *)(this + 8316) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
      *(uint8_t *)(this + 8326) = 0;
      *(uint32_t *)(this + 8328) = 0;
      *(uint8_t *)(this + 8332) = 0;
      *(uint8_t *)(this + 8333) = 0;
      v97 = *(uint32_t *)(this + 8300);
      *(uint8_t *)(this + 8324) = a3[1][2] != 0;
      *(uint8_t *)(this + 8325) = a3[1][3] != 0;
      if ( v97 != 0 )
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
        v100 = (uint32_t **)(this + 8336);
        if ( *(uint32_t *)(this + 8336) == 0 )
        {
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
          v280 = 5;
          if ( *(float *)&Block == 0.0 )
          {
            v101 = nullptr;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )
          {
            v101 = (uint32_t *)sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);
          }
          else
          {
            v101 = (uint32_t *)sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);
          }
          v280 = -1;
          *v100 = v101;
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
          v280 = 6;
          if ( *(float *)&Block == 0.0 )
          {
            v102 = 0;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )
          {
            v102 = sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);
          }
          else
          {
            v102 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);
          }
          v280 = -1;
          *(uint32_t *)(this + 8340) = v102;
        }
        v103 = *(uint32_t *)(this + 8300);
        *(float *)&Block = 1.0;
        if ( v103 != 0 )
        {
          v104 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v103 + 192))(v103);
          *(float *)&Block = sub_4049C0(1.0, 3.0, v104 - 100, 150);
        }
        v105 = Block;
        v276 = 2;
        do
        {
          sub_4920E0(*v100++, *(float *)&v105, *(float *)&v105);
          --v276;
        }
        while ( *(float *)&v276 != 0.0 );
        *(uint8_t *)(this + 8334) = 0;
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(v99 + 1140))(this, 22) <= 0 )
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX");
        else
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX_CRASH");
        v106 = *(uint32_t *)this;
        v107 = *(uint32_t *)(this + 6216);
        if ( *(uint8_t *)(this + 8325) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int))(v106 + 196))(
            this,
            *(uint32_t *)(v107 + 28),
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
            *(uint32_t *)(v107 + 24),
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
      v108 = *(uint32_t *)(this + 556);
      if ( *(uint8_t *)(this + 8324) != 0 )
        v109 = v108 + 1064;
      else
        v109 = v108 + 608;
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 344))(v109);
      v110 = *(uint8_t *)(this + 8324) != 0 ? 18 : 9;
      v111 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      v112 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, v110);
      v113 = *(uint32_t *)this;
      Block = v112;
      v114 = (char *)(*(int (/*thiscall*/ **)(int, int))(v113 + 1160))(this, v110);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v114, 0.0, (int)Block, v111, v111, 0));
      v115 = *(uint8_t *)(this + 8325);
      *(float *)(this + 388) = (float)(int)Block;
      if ( v115 != 0 )
      {
        v116 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 10);
        v117 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 10);
        v118 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v116, 0.0, v117, v118, v118, 0));
        *(float *)(this + 388) = (double)(int)Block + *(float *)(this + 388);
        *(float *)&Block = COERCE_FLOAT(sub_47EF20(2, v117, -1, -1, 11));
        *(float *)(this + 460) = (double)(int)Block + *(float *)(this + 460);
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "HOLD", -1, 0, 0);
      goto LABEL_251;
    case 20:
      v119 = *a3[1];
      *(uint32_t *)(this + 8344) = v119;
      if ( v119 != 0 )
      {
        v121 = *(uint32_t *)(this + 6216);
        if ( *(uint32_t *)(this + 8348) % 2 != 0 )
          v120 = *(uint32_t *)(v121 + 40);
        else
          v120 = *(uint32_t *)(v121 + 36);
      }
      else
      {
        v120 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 32);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, v120);
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
      if ( v279 != 20 )
      {
        v122 = *(uint32_t *)this;
        *(uint32_t *)(this + 8348) = 0;
        *(uint8_t *)(this + 8360) = 0;
        *(uint32_t *)(this + 8364) = (*(int (/*thiscall*/ **)(int))(v122 + 120))(this);
        *(uint32_t *)(this + 8368) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);
        v123 = sub_45EBE0(a3[1][1], a3[1][2]);
        v124 = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(uint32_t *)(this + 8356) = v124;
        if ( v124 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v124 + 776))(v124, 3) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 0);
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 768))(
              *(uint32_t *)(this + 8356),
              3,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 1);
          }
          v125 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 688))(*(uint32_t *)(this + 8356))
                           + 20);
          v126 = sub_42FC90(v125);
          v127 = (int *)sub_4924C0(v126 - 1);
          v128 = *v127;
          if ( *v127 != 0 )
          {
            if ( (unsigned int)((*(uint32_t *)(v128 + 20) >> 2) + 40) <= 0x50 )
              v129 = 80;
            else
              v129 = (*(uint32_t *)(v128 + 20) >> 2) + 40;
            v130 = sub_4918E0(v127, 0);
            v131 = *(uint32_t *)(this + 8356);
            *(uint32_t *)(this + 8372) = v129 - v130;
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v131 + 152))(v131) == 0 )
              *(uint32_t *)(this + 8372) = -*(uint32_t *)(this + 8372);
            v132 = *(uint32_t *)this;
            v133 = *(int **)(this + 8356);
            v134 = *v133;
            Block = v133;
            v135 = (*(int (/*stdcall*/ **)(uint32_t))(v134 + 124))(0);
            v136 = (*(int (/*thiscall*/ **)(int *, int))(*v133 + 120))(v133, v135 + 1);
            (*(void (/*thiscall*/ **)(int, int))(v132 + 112))(this, *(uint32_t *)(this + 8372) + v136);
            v137 = *(uint32_t *)this;
            v138 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 152))(*(uint32_t *)(this + 8356));
            v139 = sub_432E50(v138);
            (*(void (/*thiscall*/ **)(int, int))(v137 + 148))(this, v139);
          }
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 760);
        v140 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
        sub_406D60(v140);
        v141 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);
        v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 14);
        v142 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v141, 0.0, v6, v142, v142, 0));
        *(float *)(this + 388) = (float)(int)Block;
        *(uint32_t *)(this + 8352) = sub_47E9D0(v141, 0);
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
        v143 = *(uint32_t *)(this + 8356);
        ++*(uint32_t *)(this + 8348);
        if ( v143 != 0 )
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
              v145 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 53);
            else
              v145 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 53);
            Block = v145;
            v146 = (double)(int)v145;
            v147 = *(uint32_t *)this;
            *(float *)&v265 = v146;
            v148 = (void *)(*(int (/*thiscall*/ **)(int))(v147 + 124))(this);
            v149 = *(uint32_t *)this;
            Block = v148;
            v266 = (float)(int)v148;
            v150 = (*(int (/*thiscall*/ **)(int))(v149 + 128))(this);
            v151 = *(uint32_t *)(this + 8356);
            Block = (void *)(v150 + 17);
            v267 = (float)(v150 + 17);
            sub_4E5F70(v6, this, v151, (float *)&v265, 1, 1);
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
      LOBYTE(a4) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 44));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 912);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);
      v152 = *(uint32_t *)(this + 8444) + 1;
      ++*(uint32_t *)(this + 6896);
      v153 = *(uint32_t *)this;
      *(uint32_t *)(this + 8444) = v152;
      v154 = (*(int (/*thiscall*/ **)(int))(v153 + 388))(this);
      v155 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);
      v156 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 17);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v156, 0.0, v155, v154, v154, 0));
      *(float *)(this + 388) = (float)(int)Block;
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FT_SKYSTEP",
        -1,
        0,
        0);
      goto LABEL_251;
    case 22:
      v157 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 19);
      v158 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 19);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 56));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1216);
      v159 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v158, 0.0, v157, v159, v159, 0));
      *(float *)(this + 388) = (float)(int)Block;
      v160 = (void *)sub_47EF20(1, v157, -1, -1, 11);
      v161 = *(uint32_t *)this;
      Block = v160;
      *(float *)&v276 = (double)(int)v160 * 0.0099999998 + 1.0;
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
      v163 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
      *(float *)&Block = COERCE_FLOAT(sub_495500(v163));
      (*(void (/*fastcall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t))(v162 + 888))(
        this,
        (uint64_t)((double)(int)Block * *(float *)&v276) >> 32,
        0,
        0,
        1000,
        (uint64_t)((double)(int)Block * *(float *)&v276));
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      if ( *(uint32_t *)(this + 8412) == 0 )
      {
        *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));
        v280 = 7;
        if ( *(float *)&Block == 0.0 )
        {
          v164 = 0;
        }
        else if ( *(uint32_t *)(this + 384) < 0x10u )
        {
          v164 = sub_431920(this + 108, (char)"Effect/Animation/ClosePunchExecute.ani", 1);
        }
        else
        {
          v164 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ClosePunchExecute.ani", 1);
        }
        v280 = -1;
        *(uint32_t *)(this + 8412) = v164;
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
      v166 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 5);
      v167 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 5);
      v168 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v166, COERCE_FLOAT(1), v167, v168, v168, 0));
      *(float *)(this + 388) = (float)(int)Block;
      *(uint32_t *)(this + 456) = sub_47EF20(2, v167, -1, -1, 11);
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, v167, -1, -1, 11));
      v169 = *(uint32_t *)this;
      *(float *)&v276 = (double)(int)Block * 0.0099999998 + 1.0;
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v169 + 876))(this, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v170 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);
      *(float *)&Block = COERCE_FLOAT(sub_495500(v170));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 888))(
        this,
        0,
        0,
        (uint64_t)((double)(int)Block * *(float *)&v276),
        (uint64_t)((double)(int)Block * *(float *)&v276));
      v171 = *(uint32_t *)this;
      v172 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int, int))(v171 + 896))(this, v172);
      v173 = *(uint32_t *)this;
      *(uint8_t *)(this + 8437) = 0;
      v174 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v173 + 1172))(this, 1, -1, 0, 0);
      (*(void (/*thiscall*/ **)(int, int))(v173 + 212))(this, v174);
      v175 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);
      sub_406D60(v175);
      goto LABEL_251;
    case 24:
      v176 = *(uint32_t *)this;
      *(uint32_t *)(this + 8472) = *a3[1];
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
        LOBYTE(a5) = 0;
        v184 = sub_45EBE0(a3[1][1], a3[1][2]);
        v185 = __RTDynamicCast(v184, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(uint32_t *)(this + 8300) = v185;
        if ( v185 != 0 )
        {
          v186 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v185 + 120))(v185);
          v187 = *(uint32_t *)(this + 8300);
          *(uint32_t *)(this + 8304) = v186;
          v188 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v187 + 124))(v187);
          v189 = *(uint32_t *)(this + 8300);
          *(uint32_t *)(this + 8308) = v188;
          *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v189 + 128))(v189);
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
        v177 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
        v178 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);
        v179 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);
        v180 = (void *)sub_47EFD0(v179, 0.0, v178, v177, v177, 0);
        v181 = *(uint32_t *)this;
        Block = v180;
        *(float *)(this + 388) = (float)(int)v180;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v181 + 212))(this, "R_FT_ATK", -1, 0, 0);
        v182 = *(uint32_t *)this;
        v183 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(v182 + 212))(this, v183);
      }
      goto LABEL_251;
    case 26:
      v191 = *(uint32_t *)this;
      *(uint32_t *)(this + 8496) = *a3[1];
      v192 = (char *)(*(int (/*thiscall*/ **)(int, int))(v191 + 1160))(this, 54);
      v193 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 54);
      v194 = *(uint32_t *)(this + 8496);
      if ( v194 != 0 )
      {
        if ( v194 == 1 )
        {
          v199 = *(void **)(this + 120);
          *(uint32_t *)(this + 8500) = a3[1][1];
          sub_4AECE0(v199, 2);
          sub_4939E0(*(uint32_t *)(this + 120), 0);
          LOBYTE(a5) = 0;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1824);
          v200 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);
          v201 = (void *)sub_47EFD0(v192, 0.0, v193, v200, v200, 0);
          v202 = *(uint32_t *)this;
          Block = v201;
          v203 = (*(int (/*thiscall*/ **)(int))(v202 + 388))(this);
          v204 = sub_47EFD0(v192, COERCE_FLOAT(1), v193, v203, v203, 0);
          v205 = (void *)sub_423A80(Block, v204, *(uint32_t *)(this + 8500), dword_9B9348);
          v206 = *(uint32_t *)(this + 8500);
          Block = v205;
          *(float *)(this + 388) = (float)(int)v205;
          v261 = dword_9B9348;
          v258 = v206;
          v256 = sub_47E9D0(v192, 3u);
          v207 = sub_47E9D0(v192, 2u);
          v208 = sub_423A80(v207, v256, v258, v261);
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
              v210 = 0;
            }
            else if ( *(uint32_t *)(this + 384) < 0x10u )
            {
              v210 = sub_431920(this + 108, (char)"Effect/Animation/ShoulderTackle.ani", 1);
            }
            else
            {
              v210 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ShoulderTackle.ani", 1);
            }
            v280 = -1;
            *(uint32_t *)(this + 8512) = v210;
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
        v195 = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));
        v196 = v195;
        if ( (uint32_t)v195 != 0 )
          LODWORD(v195) = sub_47E9D0(v192, 1u);
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, int))(*(uint32_t *)this + 876))(
          this,
          0,
          v196,
          v196,
          0,
          v195,
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
        v198 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
        v197[224](this, v198);
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

