// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5E78C0_sub_5E78C0.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5E78C0）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1972 行；字符串证据 5 条；外调 6 个
//   串: "Particle/ThrowWeb.ptl"
//   串: "Effect/Animation/ThrowWebShoot.ani"
//   串: "G_SHOULDER"
//   串: "SPIRE_SPIN_LOOP"
//   串: "SPIRE_UP"
//   调: sub_5E78C0 sub_4B7430 sub_699000 sub_484E80 sub_44A980 sub_4F3460
//   case 分支地图（共 11 处）:
//     L266  case 0xA:
//     L466  case 0xC:
//     L475  case 0x11:
//     L487  case 0x12:
//     L519  case 0x13:
//     L819  case 0x14:
//     L889  case 0x15:
//     L924  case 0x16:
//     L1658  case 0x17:
//     L1711  case 0x18:
//     L1903  case 0x1A:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5E78C0 sub_5E78C0  size=12390
// ------------------------------------------------------------
void /*usercall*/ sub_5E78C0(int a1@<ecx>, double a2@<st0>)
{
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // edi
  int *v26; // edi
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // edi
  int v33; // eax
  int v34; // eax
  uint32_t *v35; // edi
  int v36; // eax
  int v37; // edi
  bool v38; // bl
  int v39; // eax
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  void *v43; // ecx
  int v44; // ecx
  int v45; // eax
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // ecx
  int v50; // edi
  int v51; // eax
  int v52; // ecx
  bool v53; // zf
  int v54; // eax
  int *v55; // ecx
  int v56; // edx
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // edi
  void *v62; // ecx
  int v63; // edx
  uint32_t *v64; // edi
  int v65; // ecx
  int v66; // eax
  int v67; // ecx
  int v68; // eax
  int v69; // ecx
  int v70; // eax
  int v71; // edx
  int v72; // edi
  int v73; // eax
  int v74; // edx
  char *v75; // eax
  int v76; // edi
  int v77; // eax
  int v78; // edx
  char *v79; // eax
  int v80; // eax
  int v81; // eax
  bool v82; // sf
  int v83; // ecx
  int v84; // eax
  int v85; // ecx
  int v86; // eax
  int v87; // ecx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int v91; // edi
  int v92; // eax
  int v93; // ecx
  int v94; // ecx
  int v95; // eax
  int v96; // ecx
  int v97; // edi
  int v98; // eax
  int v99; // eax
  int v100; // eax
  int v101; // edi
  int v102; // eax
  int v103; // edi
  int v104; // eax
  int v105; // eax
  int v106; // edx
  int v107; // edi
  int v108; // eax
  int v109; // eax
  int v110; // eax
  uint32_t *v111; // edi
  int v112; // eax
  int v113; // ecx
  int v114; // eax
  int v115; // eax
  int v116; // edi
  int v117; // eax
  int v118; // edi
  int v119; // eax
  int v120; // edx
  int v121; // eax
  int v122; // edx
  int *v123; // edi
  int v124; // eax
  int v125; // eax
  int v126; // edx
  int v127; // eax
  int v128; // eax
  int v129; // eax
  void *v130; // ecx
  int v131; // ecx
  int v132; // ecx
  int v133; // edi
  int v134; // eax
  int v135; // eax
  int v136; // eax
  int v137; // eax
  int v138; // eax
  int v139; // ecx
  int v140; // edx
  int v141; // eax
  double v142; // st7
  int v143; // eax
  int v144; // eax
  int v145; // edx
  int v146; // eax
  int v147; // ecx
  int v148; // edi
  char *v149; // eax
  int v150; // eax
  int v151; // eax
  int v152; // edi
  int v153; // ecx
  int v154; // eax
  int v155; // edi
  int v156; // eax
  int v157; // edi
  int v158; // edi
  int v159; // eax
  int v160; // eax
  int v161; // ebx
  int v162; // eax
  int v163; // eax
  void *v164; // ecx
  int v165; // eax
  int v166; // eax
  int v167; // eax
  int v168; // eax
  int v169; // eax
  int v170; // eax
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // edi
  int v175; // eax
  int v176; // edi
  int v177; // ecx
  int v178; // eax
  int v179; // edi
  int v180; // eax
  int v181; // eax
  int v182; // edi
  int v183; // eax
  int v184; // eax
  int v185; // eax
  int v186; // eax
  int v187; // eax
  int v188; // ecx
  int v189; // eax
  int v190; // eax
  unsigned int v191; // edi
  int v192; // ecx
  int v193; // edx
  int *v194; // edi
  int v195; // eax
  int v196; // eax
  uint32_t *v197; // eax
  int v198; // edx
  int v199; // eax
  int v200; // edx
  char *v201; // eax
  char *v202; // eax
  int v203; // ecx
  int v204; // eax
  int *v205; // edi
  int v206; // eax
  int v207; // eax
  int v208; // eax
  int v209; // edi
  int v210; // eax
  int v211; // eax
  int v212; // eax
  int v213; // edi
  int v214; // eax
  int v215; // eax
  int v216; // eax
  int v217; // eax
  int v218; // eax
  int v219; // eax
  int v220; // [esp-14h] [ebp-84h]
  int v221; // [esp-10h] [ebp-80h]
  int v222; // [esp-Ch] [ebp-7Ch]
  int v223; // [esp-8h] [ebp-78h]
  float v224; // [esp+0h] [ebp-70h]
  int v225; // [esp+0h] [ebp-70h]
  int v226; // [esp+4h] [ebp-6Ch]
  int v227; // [esp+8h] [ebp-68h]
  int v228; // [esp+Ch] [ebp-64h]
  float v229; // [esp+10h] [ebp-60h] BYREF
  float v230; // [esp+14h] [ebp-5Ch]
  float v231; // [esp+18h] [ebp-58h]
  int v232; // [esp+1Ch] [ebp-54h]
  int v233; // [esp+20h] [ebp-50h]
  int v234; // [esp+24h] [ebp-4Ch]
  uint8_t v235[4]; // [esp+28h] [ebp-48h] BYREF
  void *Block; // [esp+2Ch] [ebp-44h]
  int v237; // [esp+30h] [ebp-40h]
  int v238; // [esp+34h] [ebp-3Ch]
  float v239; // [esp+38h] [ebp-38h] BYREF
  float v240; // [esp+3Ch] [ebp-34h]
  float v241; // [esp+40h] [ebp-30h] BYREF
  void *v242; // [esp+44h] [ebp-2Ch]
  void *Src; // [esp+48h] [ebp-28h]
  int v244; // [esp+4Ch] [ebp-24h]
  uint8_t v245[4]; // [esp+50h] [ebp-20h] BYREF
  int v246; // [esp+54h] [ebp-1Ch] BYREF
  int v247; // [esp+58h] [ebp-18h] BYREF
  int i; // [esp+5Ch] [ebp-14h] BYREF
  bool v249; // [esp+63h] [ebp-Dh] BYREF
  int v250; // [esp+6Ch] [ebp-4h]

  sub_4B7430((int *)a1, a2);
  switch ( *(uint32_t *)(a1 + 6556) )
  {
    case 0xA:
      v3 = *(uint32_t *)(a1 + 7812);
      if ( v3 == 1 )
      {
        if ( *(uint32_t *)(a1 + 7808) == 1 )
        {
          v4 = *(uint32_t *)(a1 + 8400);
          if ( v4 != 0
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) != 0
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0
            && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 7824)
            && *(uint32_t *)(a1 + 8404) == 0 )
          {
            v5 = sub_484E80(*(uint32_t *)(a1 + 7816));
            if ( v5 != -1 )
            {
              v6 = sub_44A980(v5);
              v7 = __RTDynamicCast(v6, 0, &IRDItem `RTTI Type Descriptor', &CNThrowStackable `RTTI Type Descriptor', 0);
              sub_4F3460();
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 136))(v7, a1, 2, -1);
              ++*(uint32_t *)(a1 + 8404);
            }
          }
        }
      }
      else if ( v3 == 0 )
      {
        v8 = *(uint32_t *)(a1 + 7816);
        switch ( v8 )
        {
          case 13:
            if ( *(uint32_t *)(a1 + 7808) == 1 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 1 && *(uint8_t *)(a1 + 8376) == 0 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
              {
                v9 = *(uint32_t *)a1;
                v10 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 1140))(
                        a1,
                        13,
                        0,
                        0,
                        65,
                        0,
                        50,
                        4,
                        0,
                        0,
                        0);
                (*(void (/*thiscall*/ **)(int, int, int))(v9 + 580))(a1, 21004, v10);
              }
              *(uint8_t *)(a1 + 8376) = 1;
            }
            break;
          case 12:
            if ( *(uint32_t *)(a1 + 7808) == 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 4 && *(uint8_t *)(a1 + 8384) == 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)a1 + 876))(
                a1,
                0,
                200,
                200,
                0,
                -10000,
                1);
              v11 = *(uint32_t *)a1;
              v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 152))(a1, 4);
              v13 = sub_432E50(v12);
              (*(void (/*thiscall*/ **)(int, int))(v11 + 896))(a1, v13);
              *(uint8_t *)(a1 + 8384) = 1;
            }
            if ( *(uint32_t *)(a1 + 7808) == 1
              && *(int *)(*(uint32_t *)(a1 + 8388) + 148) >= 1
              && *(uint8_t *)(a1 + 8392) == 0 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
              {
                v14 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 1140))(a1, 12, -1, -1, 11);
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)a1 + 1160))(a1, 12, 0, v14);
                v15 = sub_47EF20(v226, v227, v228, LODWORD(v229), LODWORD(v230));
                v16 = *(uint32_t *)(a1 + 8396);
                v230 = 0.0;
                v229 = 0.0;
                v226 = 63;
                *(uint32_t *)(v16 + 85) = v15;
                v17 = *(uint32_t *)a1;
                v18 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t))(*(uint32_t *)a1 + 1140))(
                        a1,
                        12,
                        *(uint32_t *)(a1 + 8396),
                        0,
                        70,
                        0);
                (*(void (/*thiscall*/ **)(int, int, int))(v17 + 580))(a1, 21002, v18);
              }
              *(uint8_t *)(a1 + 8392) = 1;
            }
            break;
          case 49:
            v19 = *(uint32_t *)(a1 + 8300);
            if ( v19 != 0
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 840))(v19) != 9
              && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 840))(*(uint32_t *)(a1 + 8300)) != 5
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 308))(*(uint32_t *)(a1 + 8300)) != 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8300) + 560))(
                *(uint32_t *)(a1 + 8300),
                9,
                0,
                2,
                0);
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 564))(*(uint32_t *)(a1 + 8300));
            }
            v20 = *(uint32_t *)(a1 + 7808);
            if ( v20 != 0 )
            {
              if ( v20 == 1 && *(uint32_t *)(a1 + 8300) != 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 1 )
                sub_5E6920(a1);
            }
            else if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0
                   && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
            {
              Block = nullptr;
              v237 = 0;
              v238 = 0;
              v250 = 0;
              v247 = 1;
              sub_431230(&v247);
              *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 1132))(a1, 0));
              sub_431230(&v247);
              (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, v235, 0, 0);
              goto LABEL_159;
            }
            break;
          default:
            if ( v8 == 52
              && *(uint32_t *)(a1 + 7808) == 1
              && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 1
              && *(uint8_t *)(a1 + 8377) == 0 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
              {
                v21 = *(uint32_t *)a1;
                v22 = (*(int (/*thiscall*/ **)(int, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 588))(
                        a1,
                        "Particle/ThrowWeb.ptl",
                        0,
                        65,
                        0,
                        50,
                        4,
                        0,
                        0,
                        0);
                v23 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 1140))(a1, 52, v22);
                (*(void (/*thiscall*/ **)(int, int, int))(v21 + 580))(a1, 21015, v23);
              }
              v246 = sub_42FCB0(228);
              v250 = 1;
              if ( v246 != 0 )
              {
                if ( *(uint32_t *)(a1 + 384) < 0x10u )
                  LOBYTE(v24) = a1 + 108;
                else
                  v24 = *(uint32_t *)(a1 + 364);
                v25 = sub_431920(v24, (char)"Effect/Animation/ThrowWebShoot.ani", 1);
              }
              else
              {
                v25 = 0;
              }
              v246 = sub_44B6C0(284);
              v250 = 2;
              if ( v246 != 0 )
                v26 = (int *)sub_44E1F0(v25, 1);
              else
                v26 = nullptr;
              v27 = *(uint32_t *)(a1 + 116);
              i = (int)v26;
              v250 = -1;
              sub_45FE80(v27, (int)v26, 2, 0, (int)v26, a1, 0);
              v28 = *(uint32_t *)a1;
              v247 = *v26;
              v29 = (*(int (/*thiscall*/ **)(int))(v28 + 152))(a1);
              (*(void (/*thiscall*/ **)(int *, int))(v247 + 148))(v26, v29);
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != 0 )
                v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 65;
              else
                v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 65;
              v31 = *(uint32_t *)a1;
              v32 = *v26;
              v247 = v30;
              v33 = (*(int (/*thiscall*/ **)(int))(v31 + 128))(a1);
              v34 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v33 + 50);
              (*(void (/*thiscall*/ **)(int, int, int))(v32 + 112))(i, v247, v34 - 10);
              *(uint8_t *)(a1 + 8377) = 1;
            }
            break;
        }
      }
      goto LABEL_254;
    case 0xC:
      if ( *(uint8_t *)(a1 + 8228) == 0 && *(uint32_t *)(a1 + 8220) == 1 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 1 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)a1 + 212))(a1, "G_SHOULDER", -1);
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 1160))(a1, 1, a1, -1);
        sub_47DCD0(0, 0);
        *(uint8_t *)(a1 + 8228) = 1;
      }
      goto LABEL_254;
    case 0x11:
      if ( *(uint32_t *)(a1 + 8244) == 1
        && *(uint32_t *)(a1 + 8248) == 15
        && sub_699000(a1 + 6560) >= 500
        && *(uint8_t *)(a1 + 8276) == 0 )
      {
        v35 = *(uint32_t **)(*(uint32_t *)(a1 + 116) + 132);
        v36 = sub_699000(a1 + 6560);
        sub_424120(v35, 2, *(uint32_t *)(a1 + 8256) - v36);
        *(uint8_t *)(a1 + 8276) = 1;
      }
      goto LABEL_254;
    case 0x12:
      if ( *(uint8_t *)(a1 + 8292) != 0 )
      {
        if ( *(uint8_t *)(a1 + 248) == 0 || *(uint32_t *)(a1 + 252) != -16776961 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 284))(a1, 1, -16776961, 1, 2);
        if ( *(uint32_t *)(a1 + 644) != 1 )
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 612))(a1, 1, 1);
      }
      if ( fabs(*(float *)(*(uint32_t *)(a1 + 112) + 16)) >= 50.0 && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8296) + 250 )
      {
        v37 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 924))(a1, 2)];
        v38 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) == 0;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v37 + 28))(v37) + 84) = v38;
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != 0 )
          v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 40;
        else
          v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 40;
        v40 = *(uint32_t *)v37;
        v247 = v39;
        v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
        v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v41);
        (*(void (/*thiscall*/ **)(int, int, int))(v40 + 40))(v37, v247, v42);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v37 + 12))(v37, 0);
        (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v37 + 92))(v37, &v241);
        v43 = *(void **)(a1 + 116);
        v250 = 3;
        sub_4600B0(v43, 2, 0, (int)&v241);
        *(uint32_t *)(a1 + 8296) = sub_699000(a1 + 6560);
        v250 = -1;
        sub_5E5260(&v241);
      }
      goto LABEL_254;
    case 0x13:
      v44 = *(uint32_t *)(a1 + 8300);
      if ( v44 != 0
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v44 + 840))(v44) != 9
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 840))(*(uint32_t *)(a1 + 8300)) != 5 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 308))(*(uint32_t *)(a1 + 8300)) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8300) + 560))(
            *(uint32_t *)(a1 + 8300),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 564))(*(uint32_t *)(a1 + 8300));
        }
        goto LABEL_254;
      }
      if ( *(uint8_t *)(a1 + 8324) == 0 )
        goto LABEL_108;
      v45 = *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148);
      if ( v45 == 2 )
      {
        if ( *(uint8_t *)(a1 + 8332) != 0 )
        {
          v49 = *(uint32_t *)(a1 + 112);
          if ( *(float *)(v49 + 24) > 0.0 && *(float *)(v49 + 24) < 300.0 )
          {
            v224 = -*(float *)(v49 + 24);
            sub_494F20(2, v224);
          }
          if ( *(float *)(*(uint32_t *)(a1 + 112) + 24) < 0.0 )
          {
            sub_4AECE0(3);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
              a1,
              -1,
              *(uint32_t *)(a1 + 8336),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
              a1,
              1,
              *(uint32_t *)(a1 + 8340),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 216))(a1, 11);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
              a1,
              "SPIRE_SPIN_LOOP",
              12,
              0,
              0);
            *(uint8_t *)(a1 + 8334) = 1;
          }
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
        {
          v46 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 1140))(a1, 18, -1, -1);
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 1160))(a1, 18, 2, v46);
          *(float *)&v247 = (float)(int)sub_47EF20(11, v226, v227, v228, LODWORD(v229));
          sub_494F20(2, *(float *)&v247);
          v47 = *(uint32_t *)a1;
          v229 = 0.0;
          v226 = (int)"SPIRE_UP";
          (*(void (/*thiscall*/ **)(int))(v47 + 212))(a1);
          v48 = *(uint32_t *)a1;
          *(uint8_t *)(a1 + 8332) = 1;
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, uint32_t, uint32_t))(v48 + 876))(a1, 0, 143, 119, 1, 0, 0);
          (*(void (/*thiscall*/ **)(int, int, int, int, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 876))(
            a1,
            1,
            95,
            79,
            1,
            0,
            0);
        }
        else if ( *(float *)(*(uint32_t *)(a1 + 112) + 24) >= 0.0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "SPIRE_UP",
            11,
            0,
            0);
          *(uint8_t *)(a1 + 8332) = 1;
        }
      }
      else if ( v45 == 6 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) >= 100 )
      {
        i = *(uint32_t *)(a1 + 120);
        *(float *)&v247 = COERCE_FLOAT(sub_491C70(6));
        v50 = sub_4910A0(i) - v247;
        v51 = sub_491C70(4);
        sub_493A60(*(uint32_t *)(a1 + 120), v50 + v51);
      }
      if ( *(uint8_t *)(a1 + 8326) != 0 )
      {
        if ( *(uint8_t *)(a1 + 8333) == 0 && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8328) + 100 )
        {
          sub_4A0550(40);
          sub_4AECE0(7);
          *(uint8_t *)(a1 + 8333) = 1;
        }
LABEL_108:
        if ( *(uint8_t *)(a1 + 8326) != 0 )
          goto LABEL_254;
      }
      if ( *(uint8_t *)(a1 + 8324) != 0 )
      {
        if ( *(uint8_t *)(a1 + 8332) == 0 )
          goto LABEL_254;
        v52 = *(uint32_t *)(a1 + 112);
        if ( *(float *)(v52 + 24) >= 0.0 || *(uint32_t *)(v52 + 192) != 4 )
          goto LABEL_254;
      }
      else
      {
        if ( *(uint8_t *)(a1 + 8325) != 0 )
          v53 = *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 6;
        else
          v53 = *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 4;
        if ( !v53 )
          goto LABEL_254;
      }
      sub_424120(*(uint32_t **)(*(uint32_t *)(a1 + 116) + 132), 10, 200);
      if ( *(uint32_t *)(a1 + 8300) != 0 )
      {
        v54 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 924))(a1, 0);
        v55 = *(int **)(a1 + 8300);
        v56 = *v55;
        v247 = dword_8F8270[v54];
        v57 = *(uint32_t *)v247;
        i = (int)v55;
        v246 = v57;
        v58 = (*(int (**)(void))(v56 + 128))();
        v59 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 124))(i, v58);
        v60 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v59);
        v61 = v247;
        (*(void (/*thiscall*/ **)(int, int))(v246 + 40))(v247, v60);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v61 + 12))(v61, 0);
        (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v61 + 92))(v61, &v241);
        v62 = *(void **)(a1 + 116);
        v250 = 4;
        sub_4600B0(v62, 2, 0, (int)&v241);
        v250 = -1;
        sub_5E5260(&v241);
      }
      v63 = *(uint32_t *)a1;
      if ( *(uint8_t *)(a1 + 8324) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v63 + 876))(a1, 0, 0, 0, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 876))(
          a1,
          1,
          0,
          0,
          0,
          0,
          0);
        v64 = (uint32_t *)(a1 + 8336);
        v247 = 2;
        do
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *v64++);
          --v247;
        }
        while ( *(float *)&v247 != 0.0 );
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 216))(a1, 12);
        *(uint8_t *)(a1 + 8334) = 0;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SPIRE_CRASH",
          -1,
          0,
          0);
      }
      else if ( (*(int (/*thiscall*/ **)(int, int))(v63 + 1140))(a1, 22) > 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SUPLEX_CRASH",
          -1,
          0,
          0);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
      {
        v65 = *(uint32_t *)(a1 + 8300);
        if ( v65 != 0 )
        {
          v229 = 0.0;
          v230 = 0.0;
          v231 = 0.0;
          v232 = 0;
          v233 = 0;
          v234 = 0;
          v66 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v65 + 120))(v65);
          v67 = *(uint32_t *)(a1 + 8300);
          v246 = v66;
          v229 = (float)v66;
          v68 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v67 + 124))(v67);
          v69 = *(uint32_t *)(a1 + 8300);
          v246 = v68;
          v230 = (float)v68;
          v70 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v69 + 128))(v69);
          v71 = *(uint32_t *)(a1 + 8300);
          v246 = v70;
          v231 = (float)v70;
          sub_4E5F70(a1, v71, &v229, 1, 1);
          v72 = *(uint8_t *)(a1 + 8324) != 0 ? 18 : 9;
          v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 388))(a1);
          v73 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, v72);
          v74 = *(uint32_t *)a1;
          v247 = v73;
          v75 = (char *)(*(int (/*thiscall*/ **)(int, int))(v74 + 1160))(a1, v72);
          v76 = sub_47EFD0(v75, COERCE_FLOAT(1), v247, v246, v246, 0);
          v53 = *(uint8_t *)(a1 + 8325) == 0;
          v247 = v76;
          if ( !v53 )
          {
            v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 388))(a1);
            v77 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 10);
            v78 = *(uint32_t *)a1;
            v247 = v77;
            v79 = (char *)(*(int (/*thiscall*/ **)(int, int))(v78 + 1160))(a1, 10);
            v76 += sub_47EFD0(v79, COERCE_FLOAT(1), v247, v246, v246, 0);
            v247 = v76;
          }
          v80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 792))(a1, 10);
          i = v80;
          if ( v80 != 0
            && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v80 + 16))(v80) + 4) == 10876
            && (uint8_t)sub_4C1070(i) != 0
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)i + 224))(i) != 0 )
          {
            v76 = (uint64_t)((double)v247 * 1.15);
          }
          v81 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 22);
          v53 = v81 == 0;
          v82 = v81 < 0;
          LOBYTE(v81) = *(uint8_t *)(a1 + 8324);
          v249 = !v82 && !v53;
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, unsigned int, uint32_t, uint32_t, int, uint32_t, int, bool *))(*(uint32_t *)a1 + 580))(
            a1,
            (uint8_t)v81 != 0 ? 21008 : 21001,
            v76,
            0,
            0,
            (uint8_t)v81 != 0 ? 0 : 0xFFFFFFD1,
            0,
            0,
            4,
            0,
            1,
            &v249);
          if ( *(uint8_t *)(a1 + 8324) == 0 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 11) > 0 )
          {
            v83 = *(uint32_t *)(a1 + 8300);
            v239 = 0.0;
            v240 = 0.0;
            v241 = 0.0;
            v242 = nullptr;
            Src = nullptr;
            v244 = 0;
            v84 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v83 + 120))(v83, v226);
            v85 = *(uint32_t *)(a1 + 8300);
            v246 = v84;
            v239 = (float)v84;
            v86 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v85 + 124))(v85);
            v87 = *(uint32_t *)(a1 + 8300);
            v246 = v86;
            v240 = (float)v86;
            v88 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v87 + 128))(v87);
            v89 = *(uint32_t *)(a1 + 8300);
            v246 = v88;
            v241 = (float)v88;
            v244 = 1106247680;
            *(float *)&v247 = 0.0;
            v90 = sub_605840(&v247, v89, &v239, 1);
            v91 = *(uint32_t *)(a1 + 8300);
            v226 = v90;
            v225 = v247;
            v223 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
            v222 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v91 + 128))(v91);
            v221 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v91 + 124))(v91);
            v220 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v91 + 120))(v91);
            v92 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1140))(a1);
            sub_4E4A50(a1, 21011, v92, 11, v220, v221, v222, v223, 0, v225);
          }
        }
      }
      *(uint8_t *)(a1 + 8326) = 1;
      *(uint32_t *)(a1 + 8328) = sub_699000(a1 + 6560);
      goto LABEL_254;
    case 0x14:
      v93 = *(uint32_t *)(a1 + 8356);
      if ( v93 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v93 + 724))(v93) != 0 )
        *(uint32_t *)(a1 + 8356) = 0;
      v94 = *(uint32_t *)(a1 + 8356);
      if ( v94 != 0 )
      {
        v95 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v94 + 840))(v94);
        v96 = *(uint32_t *)(a1 + 8356);
        if ( v95 == 9 )
        {
          v97 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v96 + 688))(v96) + 20);
          if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 200))(*(uint32_t *)(a1 + 8356)) == v97 )
          {
            if ( *(uint32_t *)(a1 + 8344) != 1 || *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) != 0 )
            {
              if ( *(uint8_t *)(a1 + 8360) != 0 )
              {
                v99 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 688))(*(uint32_t *)(a1 + 8356));
                v100 = sub_42FC90(*(uint32_t *)(v99 + 20));
                sub_4AECE0(v100 - 1);
                *(uint8_t *)(a1 + 8360) = 0;
              }
            }
            else if ( *(uint8_t *)(a1 + 8360) == 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 688))(*(uint32_t *)(a1 + 8356));
              v98 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 912))(*(uint32_t *)(a1 + 8356));
              sub_4AECE0(v98);
              *(uint8_t *)(a1 + 8360) = 1;
            }
          }
          else
          {
            v101 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 688))(*(uint32_t *)(a1 + 8356))
                             + 20);
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8356) + 196))(*(uint32_t *)(a1 + 8356), v101);
            v102 = sub_42FC90(v101);
            sub_4AECE0(v102 - 1);
            (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 8356) + 612))(*(uint32_t *)(a1 + 8356), 1, 1);
          }
        }
        else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v96 + 840))(v96) != 5
               && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 308))(*(uint32_t *)(a1 + 8356)) != 0 )
        {
          v103 = **(uint32_t **)(a1 + 8356);
          i = *(uint32_t *)(a1 + 8356);
          v104 = (*(int (/*stdcall*/ **)(uint32_t))(v103 + 124))(0);
          v105 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v104);
          (*(void (/*thiscall*/ **)(int, int))(v103 + 108))(i, v105);
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8356) + 560))(
            *(uint32_t *)(a1 + 8356),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8356) + 564))(*(uint32_t *)(a1 + 8356));
        }
        v106 = **(uint32_t **)(a1 + 8356);
        v107 = *(uint32_t *)a1;
        i = *(uint32_t *)(a1 + 8356);
        v108 = (*(int (/*stdcall*/ **)(uint32_t))(v106 + 124))(0);
        v109 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v108 + 1);
        (*(void (/*thiscall*/ **)(int, int))(v107 + 112))(a1, *(uint32_t *)(a1 + 8372) + v109);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      }
      goto LABEL_254;
    case 0x15:
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 5;
        v246 = 1;
        sub_431230(&v246);
        v246 = *(uint8_t *)(a1 + 6988) != 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 6, v235, 0, 0);
LABEL_159:
        v250 = -1;
        sub_5E5260(v235);
      }
      else if ( *(uint32_t *)(*(uint32_t *)(a1 + 112) + 192) == 4 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 6;
        v246 = 2;
        sub_431230(&v246);
        v246 = *(uint8_t *)(a1 + 6988) != 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 6, v235, 0, 0);
        v250 = -1;
        sub_5E5260(v235);
      }
      goto LABEL_254;
    case 0x16:
      v110 = sub_699000(a1 + 8);
      v111 = *(uint32_t **)(a1 + 8420);
      v246 = v110;
      if ( v111 != *(uint32_t **)(a1 + 8424) )
      {
        while ( 1 )
        {
          v112 = v111[1] + *(uint32_t *)(a1 + 520);
          if ( v246 < v112 )
            goto LABEL_168;
          if ( v246 >= v112 + 33 )
            break;
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*v111 + 260))(*v111, 1, 5, -12788993);
          v111 += 2;
LABEL_170:
          if ( v111 == *(uint32_t **)(a1 + 8424) )
            goto LABEL_171;
        }
        v113 = *v111;
        if ( v246 >= v112 + 66 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v113 + 260))(v113, 0, 0, 0);
          v111 = *(uint32_t **)sub_5E5220(v245, v111);
          goto LABEL_170;
        }
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v113 + 260))(v113, 1, 5, -16738561);
LABEL_168:
        v111 += 2;
        goto LABEL_170;
      }
LABEL_171:
      v114 = *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148);
      if ( (v114 == 1 || v114 == 2) && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8432) + 50 )
      {
        v115 = *(uint32_t *)a1;
        v116 = 2 * (*(uint8_t *)(a1 + 8436) == 0) - 1;
        v247 = v116;
        if ( (*(int (/*thiscall*/ **)(int))(v115 + 152))(a1) == 0 )
          v247 = -v116;
        v117 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
        v118 = v247 + v117;
        v119 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
        v120 = *(uint32_t *)a1;
        i = v119;
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(v120 + 128))(a1));
        if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)a1 + 136))(a1, v118, i, 0) != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 132))(a1, v247) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 112))(a1, v118, i, v247);
        }
        *(uint8_t *)(a1 + 8436) = *(uint8_t *)(a1 + 8436) == 0;
        *(uint32_t *)(a1 + 8432) = sub_699000(a1 + 6560);
      }
LABEL_254:
      if ( dword_8F7C04 != a1 || *(uint32_t *)(a1 + 200) == 2 )
        return;
      v165 = *(uint32_t *)(a1 + 6556);
      if ( (v165 == 0 || v165 == 11 || v165 == 15)
        && sub_4842B0(1, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 1) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 12;
        v246 = 1;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 12, v235, 0, 0);
        v250 = -1;
        sub_5E5260(v235);
      }
      v166 = *(uint32_t *)(a1 + 6556);
      if ( (v166 == 0 || v166 == 11)
        && sub_4842B0(2, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 2) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 15, 0, 0, 0);
      }
      if ( *(uint32_t *)(a1 + 6556) == 15 )
      {
        if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )
        {
          Block = nullptr;
          v237 = 0;
          v238 = 0;
          v250 = 13;
          v246 = 2;
          sub_431230(&v246);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 12, v235, 0, 0);
          v250 = -1;
          sub_5E5260(v235);
        }
        if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 || sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8232) )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      }
      v167 = *(uint32_t *)(a1 + 6556);
      if ( (v167 == 0 || v167 == 11 || v167 == 8)
        && sub_4842B0(4, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 4) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 14;
        v246 = 4;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 16, v235, 0, 0);
        v250 = -1;
        sub_5E5260(v235);
      }
      v168 = *(uint32_t *)(a1 + 6556);
      if ( (v168 == 0 || v168 == 11 || v168 == 8)
        && sub_4842B0(6, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 6) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 15;
        v246 = 6;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 16, v235, 0, 0);
        v250 = -1;
        sub_5E5260(v235);
      }
      if ( *(uint32_t *)(a1 + 6556) == 16 && *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      v169 = *(uint32_t *)(a1 + 6556);
      if ( (v169 == 0 || v169 == 11 || v169 == 8)
        && sub_4842B0(5, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 5) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 23, 0, 0, 0);
      }
      if ( *(uint32_t *)(a1 + 6556) == 23 && *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      v170 = *(uint32_t *)(a1 + 6556);
      if ( (v170 == 0 || v170 == 11)
        && sub_4842B0(8, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 8) != 0 )
      {
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 16;
        v246 = 0;
        sub_431230(&v246);
        v246 = 8;
        sub_431230(&v246);
        v171 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 8);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 1160))(a1, 8, v171);
        v246 = sub_4B1C40(v226);
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 8);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)a1 + 560))(a1, 17, &v241, 0);
        v250 = -1;
        sub_5E5260(&v241);
      }
      v172 = *(uint32_t *)(a1 + 6556);
      if ( (v172 == 0 || v172 == 11)
        && sub_4842B0(15, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 15) != 0 )
      {
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 17;
        v246 = 0;
        sub_431230(&v246);
        v246 = 15;
        sub_431230(&v246);
        v173 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 15);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 1160))(a1, 15, v173);
        v246 = sub_4B1C40(v226);
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 15);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)a1 + 560))(a1, 17, &v241, 0);
        v250 = -1;
        sub_5E5260(&v241);
      }
      if ( *(uint32_t *)(a1 + 6556) == 17 )
      {
        v174 = *(uint32_t *)(a1 + 8244);
        if ( sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 4 * v174 + 8252) )
        {
          if ( v174 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
          }
          else
          {
            Block = nullptr;
            v237 = 0;
            v238 = 0;
            v250 = 18;
            v246 = 1;
            sub_431230(&v246);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 17, v235, 0, 0);
            v250 = -1;
            sub_5E5260(v235);
          }
        }
      }
      v175 = *(uint32_t *)(a1 + 6556);
      if ( v175 == 0 || v175 == 11 || v175 == 8 || v175 == 26 )
      {
        v242 = (void *)9;
        Src = (void *)18;
        v244 = 49;
        for ( i = 0; i < 3; ++i )
        {
          v176 = (int)*(&v242 + i);
          if ( sub_4842B0(v176, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, v176) != 0 )
          {
            Block = nullptr;
            v237 = 0;
            v238 = 0;
            v250 = 19;
            v246 = v176;
            sub_431230(&v246);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 18, v235, 0, 0);
            v250 = -1;
            if ( Block != nullptr )
              j__free(Block);
            Block = nullptr;
            v237 = 0;
            v238 = 0;
          }
        }
      }
      if ( *(uint32_t *)(a1 + 6556) == 18 && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8288) )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      if ( *(uint32_t *)(a1 + 6556) == 19 )
      {
        if ( *(uint8_t *)(a1 + 8324) != 0 )
        {
          if ( *(uint8_t *)(a1 + 8333) != 0 )
          {
            v177 = *(uint32_t *)(a1 + 112);
            if ( *(float *)(v177 + 24) < 0.0 && *(uint32_t *)(v177 + 192) == 4 )
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 1, 0, 0, 0);
          }
        }
        else if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        }
      }
      v178 = *(uint32_t *)(a1 + 6556);
      if ( (v178 == 0 || v178 == 11 || v178 == 8)
        && sub_4842B0(12, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 12) != 0 )
      {
        v179 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 12);
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 20;
        v246 = 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 12;
        sub_431230(&v246);
        v180 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 12);
        if ( v180 == -1 )
          v180 = sub_41A5E0(v179 + 510);
        v246 = sub_41A5E0(*(uint32_t *)(v179 + 316) + 14 * (v180 - 1));
        sub_431230(&v246);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = 1;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v241, 0, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v181 = *(uint32_t *)(a1 + 6556);
      if ( (v181 == 0 || v181 == 11)
        && sub_4842B0(16, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 16) != 0 )
      {
        v182 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 16);
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 21;
        v246 = 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 16;
        sub_431230(&v246);
        v183 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 16);
        if ( v183 == -1 )
          v183 = sub_41A5E0(v182 + 510);
        v246 = sub_41A5E0(*(uint32_t *)(v182 + 316) + 14 * (v183 - 1));
        sub_431230(&v246);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = 1;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v241, 0, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v184 = *(uint32_t *)(a1 + 6556);
      if ( (v184 == 0 || v184 == 11 || v184 == 8)
        && sub_4842B0(13, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 13) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 13);
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 22;
        v246 = 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 13;
        sub_431230(&v246);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = sub_47E9D0(1);
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 3;
        sub_431230(&v246);
        v246 = 3;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v241, 0, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v185 = *(uint32_t *)(a1 + 6556);
      if ( (v185 == 0 || v185 == 11 || v185 == 8)
        && sub_4842B0(52, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 52) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 52);
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 23;
        v246 = 0;
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 52;
        sub_431230(&v246);
        v246 = sub_47E9D0(0);
        sub_431230(&v246);
        v246 = sub_47E9D0(1);
        sub_431230(&v246);
        v246 = 0;
        sub_431230(&v246);
        v246 = 3;
        sub_431230(&v246);
        v246 = 3;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v241, 0, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v186 = *(uint32_t *)(a1 + 6556);
      if ( (v186 == 0 || v186 == 11) && sub_4842B0(14, nullptr) != -1 )
      {
        v187 = *(uint32_t *)(a1 + 116);
        v188 = *(uint32_t *)(v187 + 120);
        v189 = v187 + 116;
        v190 = v188 != 0 ? (*(uint32_t *)(v189 + 8) - v188) >> 2 : 0;
        v247 = v190;
        i = 0;
        if ( v190 > 0 )
        {
          v191 = 0;
          while ( 1 )
          {
            v192 = *(uint32_t *)(a1 + 116);
            v193 = *(uint32_t *)(v192 + 120);
            if ( v193 != 0 && v191 < (*(uint32_t *)(v192 + 124) - v193) >> 2 )
              v194 = *(int **)(*(uint32_t *)(v192 + 120) + 4 * i);
            else
              v194 = nullptr;
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v194 + 40))(v194, 17) != 0
              && (*(int (/*thiscall*/ **)(int *))(*v194 + 840))(v194) == 4
              && (*(int (/*thiscall*/ **)(int *))(*v194 + 128))(v194) < 20
              && (*(uint8_t (/*thiscall*/ **)(int *))(*v194 + 724))(v194) == 0
              && (uint8_t)sub_4E4630(v194) != 0 )
            {
              v195 = *v194;
              v241 = 0.0;
              v242 = nullptr;
              Src = nullptr;
              v244 = 0;
              v246 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v195 + 688))(v194) + 20);
              v196 = sub_42FC90(v246);
              v197 = (uint32_t *)sub_4924C0(v196 - 1);
              if ( *v197 != 0 )
              {
                Src = *(void **)(*v197 + 20);
                v198 = *v194;
                LODWORD(v241) = *(uint32_t *)(*v197 + 28) + v197[3];
                if ( (*(int (/*thiscall*/ **)(int *))(v198 + 152))(v194) == 0 )
                  LODWORD(v241) = -LODWORD(v241) - (uint32_t)Src;
                v199 = (*(int (/*thiscall*/ **)(int *))(*v194 + 120))(v194);
                v200 = *v194;
                LODWORD(v241) += v199;
                v242 = (void *)((*(int (/*thiscall*/ **)(int *))(v200 + 448))(v194) - 20);
                v244 = (*(int (/*thiscall*/ **)(int *))(*v194 + 432))(v194) + 40;
                if ( (uint8_t)sub_423970(a1, &v241) != 0 )
                  break;
              }
            }
            v191 = ++i;
            if ( i >= v247 )
              goto LABEL_399;
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 14) != 0 )
          {
            v242 = nullptr;
            Src = nullptr;
            v244 = 0;
            v250 = 24;
            v246 = 0;
            sub_430C80(nullptr, 1, (int)&v246);
            *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*v194 + 48))(v194));
            v201 = (char *)Src;
            if ( v242 == nullptr )
              goto LABEL_392;
            if ( ((uint8_t *)Src - (uint8_t *)v242) >> 2 < (unsigned int)((v244 - (int)v242) >> 2) )
            {
              *(float *)Src = *(float *)&v247;
              Src = v201 + 4;
            }
            else
            {
LABEL_392:
              sub_430C80(Src, 1, (int)&v247);
            }
            *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*v194 + 52))(v194));
            v202 = (char *)Src;
            if ( v242 != nullptr && ((uint8_t *)Src - (uint8_t *)v242) >> 2 < (unsigned int)((v244 - (int)v242) >> 2) )
            {
              *(float *)Src = *(float *)&v247;
              Src = v202 + 4;
            }
            else
            {
              sub_430C80(Src, 1, (int)&v247);
            }
            (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, &v241, 0, 0);
            v250 = -1;
            if ( v242 != nullptr )
              j__free(v242);
          }
        }
      }
LABEL_399:
      if ( *(uint32_t *)(a1 + 6556) != 20 )
        goto LABEL_410;
      if ( *(uint32_t *)(a1 + 8344) == 0 )
      {
        v203 = *(uint32_t *)(a1 + 8356);
        if ( v203 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v203 + 724))(v203) == 0 )
        {
          if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
          {
            Block = nullptr;
            v237 = 0;
            v238 = 0;
            v250 = 25;
            v246 = 1;
            sub_431230(&v246);
            v246 = 0xFFFF;
            sub_431230(&v246);
            v246 = 0xFFFF;
            sub_431230(&v246);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, v235, 0, 0);
            v250 = -1;
            sub_5E5260(v235);
          }
          goto LABEL_410;
        }
LABEL_407:
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        goto LABEL_410;
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) == 0 )
        goto LABEL_410;
      if ( *(uint32_t *)(a1 + 8348) >= *(uint32_t *)(a1 + 8352) )
        goto LABEL_407;
      Block = nullptr;
      v237 = 0;
      v238 = 0;
      v250 = 26;
      v246 = 1;
      sub_431230(&v246);
      v246 = 0xFFFF;
      sub_431230(&v246);
      v246 = 0xFFFF;
      sub_431230(&v246);
      (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, v235, 0, 0);
      v250 = -1;
      if ( Block != nullptr )
        j__free(Block);
LABEL_410:
      if ( *(uint32_t *)(a1 + 6556) == 6
        && *(uint32_t *)(a1 + 6892) == 1
        && *(uint32_t *)(a1 + 6896) < *(uint32_t *)(a1 + 6900)
        && sub_4842B0(17, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 17) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 21, 0, 0, 0);
      }
      v204 = *(uint32_t *)(a1 + 6556);
      if ( (v204 == 0 || v204 == 11 || v204 == 8)
        && sub_4842B0(19, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 19) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 22, 0, 0, 0);
      }
      if ( *(uint32_t *)(a1 + 6556) == 22 && *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      v205 = (int *)&unk_7959D0;
      do
      {
        v206 = *(uint32_t *)(a1 + 6556);
        if ( (v206 == 0 || v206 == 11)
          && sub_4842B0(*v205, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, *v205) != 0 )
        {
          Block = nullptr;
          v237 = 0;
          v238 = 0;
          v246 = *v205;
          v250 = 27;
          sub_431230(&v246);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 14, v235, 0, 0);
          v250 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v237 = 0;
          v238 = 0;
        }
        ++v205;
      }
      while ( (int)v205 < (int)&dword_7959F8 );
      v207 = *(uint32_t *)(a1 + 6556);
      if ( (v207 == 0 || v207 == 11)
        && sub_4842B0(40, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 40) != 0 )
      {
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 28;
        v246 = 0;
        sub_431230(&v246);
        v246 = 40;
        sub_431230(&v246);
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 40));
        v208 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 40);
        v209 = v208;
        v210 = *(float *)&v247 == NAN ? sub_41A5E0(v208 + 510) : v247;
        v246 = sub_41A5E0(*(uint32_t *)(v209 + 316) + 14 * (v210 - 1));
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 1160))(a1, 40, 1);
        v246 = sub_47E9D0(v226);
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)a1 + 560))(a1, 17, &v241, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v211 = *(uint32_t *)(a1 + 6556);
      if ( (v211 == 0 || v211 == 11)
        && sub_4842B0(42, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 42) != 0 )
      {
        v242 = nullptr;
        Src = nullptr;
        v244 = 0;
        v250 = 29;
        v246 = 0;
        sub_431230(&v246);
        v246 = 42;
        sub_431230(&v246);
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 42));
        v212 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 42);
        v213 = v212;
        v214 = *(float *)&v247 == NAN ? sub_41A5E0(v212 + 510) : v247;
        v246 = sub_41A5E0(*(uint32_t *)(v213 + 316) + 14 * (v214 - 1));
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)a1 + 1160))(a1, 42, 0);
        v246 = sub_47E9D0(v226);
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        v246 = 4;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)a1 + 560))(a1, 17, &v241, 0);
        v250 = -1;
        if ( v242 != nullptr )
          j__free(v242);
      }
      v215 = *(uint32_t *)(a1 + 6556);
      if ( (v215 == 0 || v215 == 11 || v215 == 8)
        && sub_4842B0(46, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 46) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 30;
        v246 = 3;
        sub_431230(&v246);
        v246 = 46;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 25, v235, 0, 0);
        v250 = -1;
        if ( Block != nullptr )
          j__free(Block);
      }
      v216 = *(uint32_t *)(a1 + 6556);
      if ( (v216 == 0 || v216 == 11 || v216 == 8)
        && sub_4842B0(3, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 3) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 31;
        v246 = 0;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 24, v235, 0, 0);
        v250 = -1;
        if ( Block != nullptr )
          j__free(Block);
      }
      if ( *(uint32_t *)(a1 + 6556) == 24 )
      {
        v217 = *(uint32_t *)(a1 + 8472);
        if ( v217 != 0 )
        {
          if ( v217 == 1 && *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
            goto LABEL_472;
        }
        else if ( *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 8 )
        {
LABEL_472:
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        }
      }
      v218 = *(uint32_t *)(a1 + 6556);
      if ( (v218 == 0 || v218 == 11)
        && sub_4842B0(54, (void *)(a1 + 8116)) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 54) != 0 )
      {
        Block = nullptr;
        v237 = 0;
        v238 = 0;
        v250 = 32;
        v246 = 0;
        sub_431230(&v246);
        v246 = 54;
        sub_431230(&v246);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 26, v235, 0, 0);
        v250 = -1;
        if ( Block != nullptr )
          j__free(Block);
      }
      if ( *(uint32_t *)(a1 + 6556) == 26 )
      {
        v219 = *(uint32_t *)(a1 + 8496);
        if ( v219 != 0 )
        {
          if ( v219 == 1 && *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        }
        else if ( *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 1 && (uint8_t)sub_4BFC10(a1 + 8116) == 0 )
        {
          Block = nullptr;
          v237 = 0;
          v238 = 0;
          v250 = 33;
          v246 = 1;
          sub_431230(&v246);
          v246 = sub_699000(a1 + 6560);
          v246 -= sub_491C70(1);
          sub_431230(&v246);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 26, v235, 0, 0);
          sub_4BA730(2, 4, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
        }
      }
      return;
    case 0x17:
      if ( *(uint8_t *)(a1 + 8437) != 0 )
        goto LABEL_185;
      if ( sub_699000(a1 + 6560) >= 200 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)a1 + 876))(
          a1,
          0,
          800,
          800,
          0,
          -4000,
          1);
        v121 = sub_699000(a1 + 6560);
        v122 = *(uint32_t *)a1;
        *(uint32_t *)(a1 + 8440) = v121 - 60;
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v122 + 212))(a1, "FT_UPPER_SWING", -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SWING_UPPER",
          -1,
          0,
          0);
        *(uint8_t *)(a1 + 8437) = 1;
      }
      if ( *(uint8_t *)(a1 + 8437) != 0 )
      {
LABEL_185:
        if ( sub_699000(a1 + 6560) <= 350 && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8440) + 60 )
        {
          v123 = (int *)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 924))(a1, 2)];
          v124 = *(uint32_t *)a1;
          v246 = (int)v123;
          v125 = (*(int (/*thiscall*/ **)(int))(v124 + 152))(a1);
          v126 = *(uint32_t *)a1;
          v249 = v125 == 0;
          v247 = *v123;
          v127 = (*(int (/*thiscall*/ **)(int))(v126 + 128))(a1);
          v128 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v127);
          v129 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 120))(a1, v128);
          (*(void (/*thiscall*/ **)(int *, int))(v247 + 40))(v123, v129);
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v123 + 28))(v123) + 84) = v249;
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*v123 + 12))(v123, 0);
          (*(void (/*thiscall*/ **)(int *, float *))(*v123 + 92))(v123, &v241);
          v130 = *(void **)(a1 + 116);
          v250 = 7;
          sub_4600B0(v130, 2, 0, (int)&v241);
          *(uint32_t *)(a1 + 8440) += 60;
          v250 = -1;
          sub_5E5260(&v241);
        }
      }
      goto LABEL_254;
    case 0x18:
      if ( *(uint32_t *)(a1 + 8472) == 1 )
      {
        v131 = *(uint32_t *)(a1 + 8300);
        if ( v131 != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v131 + 840))(v131) != 9
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 840))(*(uint32_t *)(a1 + 8300)) != 5
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 308))(*(uint32_t *)(a1 + 8300)) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8300) + 560))(
            *(uint32_t *)(a1 + 8300),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8300) + 564))(*(uint32_t *)(a1 + 8300));
        }
        if ( *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 8 )
        {
          v132 = *(uint32_t *)(a1 + 8300);
          if ( v132 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v132 + 840))(v132) == 5 )
          {
            if ( *(uint32_t *)(a1 + 8300) != 0 )
            {
              v139 = *(uint32_t *)(a1 + 8480);
              *(uint32_t *)(a1 + 8300) = 0;
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v139 + 76))(v139, 0);
            }
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
          }
          else
          {
            sub_4AECE0(9);
            (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)a1 + 876))(
              a1,
              0,
              1000,
              1000,
              0,
              -10000,
              1);
            v133 = *(uint32_t *)a1;
            v134 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 152))(a1, 4);
            (*(void (/*thiscall*/ **)(int, int))(v133 + 896))(a1, v134);
            (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 888))(a1, 1, 3, 1000, 1000);
            if ( *(uint32_t *)(a1 + 8484) == 0 )
            {
              v246 = sub_42FCB0(228);
              v250 = 8;
              if ( v246 != 0 )
              {
                if ( *(uint32_t *)(a1 + 384) < 0x10u )
                  v135 = sub_431920(a1 + 108, (char)"Effect/Animation/GrabExplosion1.ani", 1);
                else
                  v135 = sub_431920(*(uint32_t *)(a1 + 364), (char)"Effect/Animation/GrabExplosion1.ani", 1);
              }
              else
              {
                v135 = 0;
              }
              *(uint32_t *)(a1 + 8484) = v135;
              v246 = sub_42FCB0(228);
              v250 = 9;
              if ( v246 != 0 )
              {
                if ( *(uint32_t *)(a1 + 384) < 0x10u )
                  v136 = sub_431920(a1 + 108, (char)"Effect/Animation/GrabExplosion2.ani", 1);
                else
                  v136 = sub_431920(*(uint32_t *)(a1 + 364), (char)"Effect/Animation/GrabExplosion2.ani", 1);
              }
              else
              {
                v136 = 0;
              }
              *(uint32_t *)(a1 + 8488) = v136;
              v246 = sub_42FCB0(228);
              v250 = 10;
              if ( v246 != 0 )
              {
                if ( *(uint32_t *)(a1 + 384) < 0x10u )
                {
                  v250 = -1;
                  *(uint32_t *)(a1 + 8492) = sub_431920(a1 + 108, (char)"Effect/Animation/GrabExplosion3.ani", 1);
                }
                else
                {
                  v137 = sub_431920(*(uint32_t *)(a1 + 364), (char)"Effect/Animation/GrabExplosion3.ani", 1);
                  v250 = -1;
                  *(uint32_t *)(a1 + 8492) = v137;
                }
              }
              else
              {
                v250 = -1;
                *(uint32_t *)(a1 + 8492) = 0;
              }
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
              a1,
              1,
              *(uint32_t *)(a1 + 8484),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
              a1,
              2,
              *(uint32_t *)(a1 + 8488),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
              a1,
              2,
              *(uint32_t *)(a1 + 8492),
              0,
              0,
              0,
              0);
            v246 = *(uint32_t *)a1;
            v138 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v246 + 1172))(a1, 1, -1, 0, 0);
            (*(void (/*thiscall*/ **)(int, int))(v246 + 212))(a1, v138);
          }
        }
        if ( *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 12 && *(uint8_t *)(a1 + 8477) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "BURN_ATK",
            -1,
            0,
            0);
          *(uint8_t *)(a1 + 8477) = 1;
        }
        if ( *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 13 && *(uint8_t *)(a1 + 8476) == 0 )
        {
          v53 = *(uint32_t *)(a1 + 8300) == 0;
          i = 0;
          *(float *)&v247 = 0.0;
          if ( !v53 )
          {
            v140 = *(uint32_t *)a1;
            v229 = 0.0;
            v230 = 0.0;
            v231 = 0.0;
            v232 = 0;
            v233 = 0;
            v234 = 0;
            if ( (*(int (/*thiscall*/ **)(int))(v140 + 152))(a1) != 0 )
              v141 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 59;
            else
              v141 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 59;
            v247 = v141;
            v142 = (double)v141;
            v143 = *(uint32_t *)a1;
            v229 = v142;
            v144 = (*(int (/*thiscall*/ **)(int))(v143 + 124))(a1);
            v145 = *(uint32_t *)a1;
            v246 = v144 - 1;
            v230 = (float)(v144 - 1);
            v146 = (*(int (/*thiscall*/ **)(int))(v145 + 128))(a1);
            v147 = *(uint32_t *)(a1 + 8300);
            v246 = v146 + 94;
            v231 = (float)(v146 + 94);
            *(float *)&v247 = COERCE_FLOAT(sub_605840(&i, v147, &v229, 1));
          }
          v148 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 388))(a1);
          v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1140))(a1);
          v149 = (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1160))(a1);
          v150 = sub_47EFD0(v149, COERCE_FLOAT(1), v246, v148, v148, 0);
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, int, int))(*(uint32_t *)a1 + 580))(
            a1,
            21014,
            v150,
            0,
            0,
            59,
            -1,
            94,
            4,
            0,
            i,
            v247);
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1 + 1160))(a1, 3, a1, -1);
          sub_47DCD0(3, 3);
          sub_5E6640(a1);
          *(uint8_t *)(a1 + 8476) = 1;
        }
      }
      goto LABEL_254;
    case 0x1A:
      v151 = *(uint32_t *)(a1 + 8496);
      if ( v151 != 0 )
      {
        if ( v151 == 1 )
        {
          if ( fabs(*(float *)(*(uint32_t *)(a1 + 112) + 16)) >= 20.0
            && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8504) + 200 )
          {
            v158 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 924))(a1, 2)];
            v159 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
            v249 = v159 == 0;
            if ( v159 != 0 )
              v160 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 20;
            else
              v160 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 20;
            v161 = *(uint32_t *)v158;
            v247 = v160;
            v162 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
            v163 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v162);
            (*(void (/*thiscall*/ **)(int, int, int))(v161 + 40))(v158, v247, v163);
            *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v158 + 28))(v158) + 84) = v249;
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v158 + 12))(v158, 0);
            (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v158 + 92))(v158, &v241);
            v164 = *(void **)(a1 + 116);
            v250 = 11;
            sub_4600B0(v164, 2, 0, (int)&v241);
            *(uint32_t *)(a1 + 8504) = sub_699000(a1 + 6560);
            v250 = -1;
            sub_5E5260(&v241);
          }
          if ( *(uint32_t *)(a1 + 8500) >= dword_9B9348 )
          {
            if ( *(uint8_t *)(a1 + 248) == 0 || *(uint32_t *)(a1 + 252) != -16776961 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 284))(a1, 1, -16776961, 1, 2);
            if ( *(uint32_t *)(a1 + 644) != 1 )
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 612))(a1, 1, 1);
          }
        }
      }
      else
      {
        v152 = *(uint32_t *)(a1 + 120);
        if ( *(uint32_t *)(v152 + 148) == 1 && sub_4910C0(*(uint32_t *)(a1 + 120)) == 0 )
          sub_4939E0(v152, 1);
        v153 = *(uint32_t *)(a1 + 112);
        if ( fabs(*(float *)(v153 + 16)) < 5.0 )
          *(uint32_t *)(v153 + 16) = 0;
        v154 = *(uint32_t *)(a1 + 8508);
        if ( v154 != 0 )
        {
          if ( v154 == 1 )
          {
            v155 = sub_491C70(1) + dword_9B9348;
            if ( sub_699000(a1 + 6560) >= v155 )
            {
              sub_4BA730(1, 4, 11, -39);
              *(uint32_t *)(a1 + 8508) = 2;
            }
          }
          else if ( v154 == 2 )
          {
            v156 = sub_699000(a1 + 6560);
            v157 = sub_42B420(255, 220, v156, 100);
            (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)a1 + 252))(a1, 0, v157);
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 252))(a1, 1, v157);
          }
        }
        else if ( *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 1 )
        {
          sub_4BA730(0, 4, 11, -39);
          *(uint32_t *)(a1 + 8508) = 1;
        }
      }
      goto LABEL_254;
    default:
      goto LABEL_254;
  }
}

