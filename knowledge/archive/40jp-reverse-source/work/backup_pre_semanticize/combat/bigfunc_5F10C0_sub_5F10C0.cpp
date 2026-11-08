// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5F10C0_sub_5F10C0.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5F10C0）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1673 行；字符串证据 5 条；外调 6 个
//   串: "R_SM_MOANING_LOOP"
//   串: "Effect/Animation/GuardDust.ani"
//   串: "Effect/Animation/HardAttackFullCharge2.ani"
//   串: "Effect/Animation/HardAttackFullCharge1.ani"
//   串: "GHOSTSLASH_CHARGE_END"
//   调: sub_5F10C0 sub_4B7430 sub_49C620 sub_699000 sub_47E9D0 sub_425100
//   case 分支地图（共 10 处）:
//     L239  case 0xA:
//     L327  case 0xF:
//     L392  case 0x10:
//     L501  case 0x11:
//     L506  case 0x12:
//     L1311  case 0x13:
//     L1339  case 0x14:
//     L1403  case 0x15:
//     L1445  case 0x16:
//     L1586  case 0x17:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5F10C0 sub_5F10C0  size=10468
// ------------------------------------------------------------
void /*usercall*/ sub_5F10C0(int a1@<ecx>, double a2@<st0>)
{
  int v3; // ecx
  int v4; // edx
  int v5; // edi
  float *v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  float v12; // edi
  int v13; // eax
  int v14; // eax
  uint32_t *v15; // edi
  void *v16; // eax
  int v17; // edx
  int v18; // ecx
  int v19; // edi
  int v20; // edi
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // ecx
  int v25; // edi
  int v26; // edi
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // edi
  void **v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // eax
  int v41; // edi
  void *v42; // ecx
  bool v43; // cc
  int v44; // eax
  int v45; // edi
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // edx
  int v52; // edi
  int v53; // eax
  int v54; // eax
  int v55; // eax
  void *v56; // eax
  int v57; // edx
  int v58; // ecx
  int v59; // eax
  int v60; // eax
  int v61; // edi
  int v62; // edi
  unsigned int j; // edi
  int v64; // eax
  int v65; // ecx
  int v66; // eax
  int v67; // ecx
  int v68; // eax
  int v69; // eax
  int v70; // edx
  int v71; // eax
  int v72; // eax
  int v73; // edx
  char *v74; // edi
  int v75; // eax
  int v76; // edx
  bool v77; // zf
  int v78; // eax
  int v79; // eax
  int v80; // edx
  int v81; // eax
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // eax
  uint32_t *v86; // eax
  int *v87; // eax
  int v88; // edx
  uint32_t *v89; // edi
  int v90; // eax
  int v91; // edx
  int v92; // ecx
  int v93; // edi
  int v94; // edi
  int v95; // ecx
  int v96; // edx
  int v97; // eax
  int v98; // ecx
  int v99; // edi
  int v100; // edi
  int v101; // ecx
  int v102; // edx
  int v103; // eax
  int v104; // eax
  int v105; // edi
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int v109; // edi
  int v110; // eax
  int v111; // eax
  int v112; // eax
  int v113; // eax
  int v114; // eax
  int v115; // eax
  int v116; // eax
  int v117; // edi
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // eax
  int v123; // eax
  bool v124; // al
  int v125; // eax
  int v126; // eax
  int v127; // eax
  int v128; // eax
  int *v129; // edi
  int v130; // eax
  int v131; // edi
  int v132; // eax
  int *v133; // edi
  int v134; // eax
  int v135; // eax
  int v136; // eax
  char *v137; // edi
  int v138; // eax
  char *v139; // edi
  int v140; // eax
  int v141; // eax
  void *v142; // eax
  int v143; // edi
  int v144; // eax
  int v145; // eax
  void *v146; // ecx
  int v147; // eax
  double v148; // st7
  int v149; // ecx
  void *v150; // edx
  int v151; // eax
  int v152; // ecx
  int v153; // edi
  int v154; // [esp+28Ch] [ebp-88h]
  float v155; // [esp+28Ch] [ebp-88h]
  int v156; // [esp+290h] [ebp-84h]
  float v157; // [esp+294h] [ebp-80h]
  char v158; // [esp+294h] [ebp-80h]
  int v159; // [esp+294h] [ebp-80h]
  int *v160; // [esp+298h] [ebp-7Ch]
  int v161; // [esp+29Ch] [ebp-78h]
  int v162; // [esp+2A0h] [ebp-74h]
  int v163; // [esp+2A4h] [ebp-70h] BYREF
  int v164; // [esp+2A8h] [ebp-6Ch]
  int v165; // [esp+2ACh] [ebp-68h]
  int v166; // [esp+2B0h] [ebp-64h]
  int v167; // [esp+2B4h] [ebp-60h]
  int v168; // [esp+2B8h] [ebp-5Ch]
  uint8_t v169[4]; // [esp+2BCh] [ebp-58h] BYREF
  void *v170; // [esp+2C0h] [ebp-54h]
  int v171; // [esp+2C4h] [ebp-50h]
  int v172; // [esp+2C8h] [ebp-4Ch]
  float v173; // [esp+2CCh] [ebp-48h] BYREF
  float v174; // [esp+2D0h] [ebp-44h]
  float v175; // [esp+2D4h] [ebp-40h] BYREF
  void *v176; // [esp+2D8h] [ebp-3Ch]
  int v177; // [esp+2DCh] [ebp-38h]
  int v178; // [esp+2E0h] [ebp-34h]
  int v179; // [esp+2E4h] [ebp-30h] BYREF
  float v180; // [esp+2E8h] [ebp-2Ch] BYREF
  int v181; // [esp+2ECh] [ebp-28h] BYREF
  void *Block; // [esp+2F0h] [ebp-24h]
  void *Src; // [esp+2F4h] [ebp-20h]
  void *v184; // [esp+2F8h] [ebp-1Ch] BYREF
  int k; // [esp+2FCh] [ebp-18h]
  int i; // [esp+300h] [ebp-14h]
  bool v187; // [esp+307h] [ebp-Dh]
  int v188; // [esp+310h] [ebp-4h]

  sub_4B7430((int *)a1, a2);
  if ( *(uint8_t *)(a1 + 8440) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8436) + 80))(*(uint32_t *)(a1 + 8436)) == 0 )
  {
    sub_49C620(1, 0, 0);
    *(uint8_t *)(a1 + 8440) = 0;
  }
  switch ( *(uint32_t *)(a1 + 6556) )
  {
    case 0:
      if ( *(uint8_t *)(a1 + 6752) != 0
        && (v3 = *(uint32_t *)(a1 + 8432)) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3) != 0 )
      {
        if ( *(uint8_t *)(a1 + 8441) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "R_SM_MOANING_LOOP",
            15,
            0,
            0);
          *(uint8_t *)(a1 + 8441) = 1;
        }
      }
      else if ( *(uint8_t *)(a1 + 8441) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 216))(a1, 15);
        *(uint8_t *)(a1 + 8441) = 0;
      }
      goto LABEL_198;
    case 8:
      if ( *(uint32_t *)(a1 + 8216) == 46 && *(uint8_t *)(a1 + 8220) == 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) > 1 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1 + 612))(a1, 0, 0);
        *(uint8_t *)(a1 + 8220) = 1;
      }
      goto LABEL_198;
    case 0xA:
      if ( *(uint32_t *)(a1 + 7812) != 0 )
        goto LABEL_198;
      v54 = *(uint32_t *)(a1 + 7816);
      if ( v54 != 23 )
      {
        if ( v54 == 44 )
        {
          if ( *(uint32_t *)(a1 + 7808) != 1 )
            goto LABEL_198;
        }
        else if ( v54 != 32 )
        {
          goto LABEL_198;
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 612))(a1, 1, 1);
        goto LABEL_198;
      }
      if ( *(uint32_t *)(a1 + 7808) == 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0
        && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 7820) )
      {
        v176 = nullptr;
        v177 = 0;
        v178 = 0;
        v55 = *(uint32_t *)a1;
        v188 = 8;
        v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(v55 + 1160))(a1, 23));
        v181 = 0;
        Block = nullptr;
        v184 = nullptr;
        Src = (void *)sub_47E9D0(5);
        v56 = (void *)sub_47E9D0(7);
        v57 = *(uint32_t *)a1;
        v184 = v56;
        if ( (*(int (/*thiscall*/ **)(int))(v57 + 152))(a1) == 1 )
        {
          v179 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
          v58 = sub_47E9D0(4) + v179;
        }
        else
        {
          v179 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - (uint32_t)Src;
          v58 = v179 - sub_47E9D0(3);
        }
        v59 = *(uint32_t *)a1;
        v181 = v58;
        v179 = (*(int (/*thiscall*/ **)(int))(v59 + 124))(a1);
        Block = (void *)(sub_47E9D0(6) + v179);
        v180 = COERCE_FLOAT(sub_425100(*(uint32_t *)(a1 + 116)));
        for ( i = 0; i < SLODWORD(v180); ++i )
        {
          v60 = sub_425A00(i);
          v61 = v60;
          v179 = v60;
          if ( v60 != 0
            && v60 != a1
            && (uint8_t)sub_423970(v60, &v181) != 0
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v61 + 40))(v61, 273) != 0 )
          {
            v62 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v61 + 376))(v61);
            if ( v62 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 376))(a1) )
              sub_428430(&v179);
          }
        }
        v170 = nullptr;
        v171 = 0;
        v172 = 0;
        LOBYTE(v188) = 9;
        v179 = 1;
        sub_431230(&v179);
        v180 = 0.0;
        sub_431230(&v180);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, v169, 0, 0);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 564))(a1);
        v163 = 0;
        v164 = 0;
        v165 = 0;
        v166 = 0;
        v167 = 0;
        v168 = 0;
        for ( j = 0; v176 != nullptr && j < (v177 - (int)v176) >> 2; ++j )
          sub_4E5F70(a1, *((uint32_t *)v176 + j), &v163, 1, 1);
        sub_5E5260(v169);
        v188 = -1;
        sub_5E5260(&v175);
      }
      goto LABEL_198;
    case 0xF:
      if ( *(uint32_t *)(a1 + 8240) == 1 )
      {
        if ( fabs(*(float *)(*(uint32_t *)(a1 + 112) + 16)) < 40.0 && *(uint8_t *)(a1 + 8256) == 0 )
        {
          v179 = sub_42FCB0(228);
          v188 = 0;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              LOBYTE(v4) = a1 + 108;
            else
              v4 = *(uint32_t *)(a1 + 364);
            v5 = sub_431920(v4, (char)"Effect/Animation/GuardDust.ani", 1);
          }
          else
          {
            v5 = 0;
          }
          v179 = sub_44B6C0(284);
          v188 = 1;
          if ( v179 != 0 )
            v6 = (float *)sub_44E1F0(v5, 1);
          else
            v6 = nullptr;
          v7 = *(uint32_t *)(a1 + 116);
          i = (int)v6;
          v188 = -1;
          sub_45FE80(v7, (int)v6, 2, 0, (int)v6, a1, 0);
          v8 = *(uint32_t *)a1;
          v180 = *v6;
          v9 = (*(int (/*thiscall*/ **)(int))(v8 + 152))(a1);
          (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v180) + 148))(v6, v9);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1) != 0 )
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 45;
          else
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 45;
          v11 = *(uint32_t *)a1;
          v12 = *v6;
          k = v10;
          v13 = (*(int (/*thiscall*/ **)(int))(v11 + 128))(a1);
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v13);
          (*(void (/*thiscall*/ **)(int, int, int))(LODWORD(v12) + 112))(i, k, v14);
          *(uint8_t *)(a1 + 8256) = 1;
        }
        if ( sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8248) )
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 2;
          v180 = 0.0;
          sub_431230(&v180);
          v180 = 0.0;
          sub_431230(&v180);
          v180 = 0.0;
          sub_431230(&v180);
          v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1));
          sub_431230(&v180);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 15, &v175, 0, 0);
          v188 = -1;
          sub_5E5260(&v175);
        }
      }
      goto LABEL_198;
    case 0x10:
      if ( *(uint32_t *)(a1 + 8272) == 1 && sub_699000(a1 + 6560) >= dword_7959F8 )
      {
        if ( *(uint8_t *)(a1 + 8284) == 0 )
        {
          *(uint8_t *)(a1 + 8284) = 1;
          v15 = (uint32_t *)(a1 + 8296);
          for ( k = 2; k != 0; --k )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *v15++);
          v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1));
          v16 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
          v17 = *(uint32_t *)a1;
          v184 = v16;
          i = (*(int (/*thiscall*/ **)(int))(v17 + 128))(a1);
          v179 = sub_42FCB0(228);
          v188 = 3;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              LOBYTE(v18) = a1 + 108;
            else
              v18 = *(uint32_t *)(a1 + 364);
            v19 = sub_431920(v18, (char)"Effect/Animation/HardAttackFullCharge2.ani", 1);
          }
          else
          {
            v19 = 0;
          }
          v179 = sub_44B6C0(284);
          v188 = 4;
          if ( v179 != 0 )
            v20 = sub_44E1F0(v19, 1);
          else
            v20 = 0;
          v21 = *(uint32_t *)(a1 + 116);
          k = v20;
          v188 = -1;
          sub_45FE80(v21, v20, 2, 0, v20, a1, 0);
          v22 = *(uint32_t *)a1;
          v179 = *(uint32_t *)v20;
          v23 = (*(int (/*thiscall*/ **)(int))(v22 + 152))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v179 + 148))(v20, v23);
          (*(void (/*thiscall*/ **)(int, float, void *, int))(*(uint32_t *)v20 + 112))(
            v20,
            COERCE_FLOAT(LODWORD(v180)),
            v184,
            i);
          v179 = sub_42FCB0(228);
          v188 = 5;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              LOBYTE(v24) = a1 + 108;
            else
              v24 = *(uint32_t *)(a1 + 364);
            v25 = sub_431920(v24, (char)"Effect/Animation/HardAttackFullCharge1.ani", 1);
          }
          else
          {
            v25 = 0;
          }
          v179 = sub_44B6C0(284);
          v188 = 6;
          if ( v179 != 0 )
            v26 = sub_44E1F0(v25, 1);
          else
            v26 = 0;
          v27 = *(uint32_t *)(a1 + 116);
          k = v26;
          v188 = -1;
          sub_45FE80(v27, v26, 2, 0, v26, a1, 0);
          v28 = *(uint32_t *)a1;
          v179 = *(uint32_t *)v26;
          v29 = (*(int (/*thiscall*/ **)(int))(v28 + 152))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v179 + 148))(v26, v29);
          (*(void (/*thiscall*/ **)(int, float, void *, int))(*(uint32_t *)v26 + 112))(
            v26,
            COERCE_FLOAT(LODWORD(v180)),
            v184,
            i);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "GHOSTSLASH_CHARGE_END",
            -1,
            0,
            0);
        }
        if ( sub_699000(a1 + 6560) >= dword_7959F8 + 200 )
        {
          v30 = sub_699000(a1 + 6560);
          v31 = sub_42B420(255, 220, -200 - dword_7959F8 + v30, 100);
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)a1 + 252))(a1, 0, v31);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 252))(a1, 1, v31);
        }
      }
      if ( *(uint32_t *)(a1 + 8272) == 2 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 3 && *(uint8_t *)(a1 + 8304) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "GHOSTSLASH_CRY",
          -1,
          0,
          0);
        *(uint8_t *)(a1 + 8304) = 1;
      }
      v32 = *(uint32_t *)(a1 + 8272);
      if ( v32 == 0 || v32 == 2 )
        goto LABEL_66;
      goto LABEL_198;
    case 0x11:
LABEL_66:
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
        goto LABEL_67;
      goto LABEL_198;
    case 0x12:
      if ( *(int *)(a1 + 8308) < 2 )
      {
        v33 = a1 + 6560;
        if ( sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8328) + 200 )
        {
          v34 = (void **)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 924))(a1, 2)];
          v35 = *(uint32_t *)a1;
          v179 = (int)v34;
          v36 = (*(int (/*thiscall*/ **)(int))(v35 + 152))(a1);
          v187 = v36 == 0;
          if ( v36 != 0 )
            v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 20;
          else
            v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 20;
          v38 = *(uint32_t *)a1;
          v180 = *(float *)&v37;
          v184 = *v34;
          v39 = (*(int (/*thiscall*/ **)(int))(v38 + 128))(a1);
          v40 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v39);
          v41 = v179;
          (*((void (/*thiscall*/ **)(int, float, int))v184 + 10))(v179, COERCE_FLOAT(LODWORD(v180)), v40);
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v179 + 28))(v179) + 84) = v187;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v41 + 12))(v41, 0);
          (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v41 + 92))(v41, &v175);
          v42 = *(void **)(a1 + 116);
          v188 = 7;
          sub_4600B0(v42, 2, 0, (int)&v175);
          v33 = a1 + 6560;
          *(uint32_t *)(a1 + 8328) = sub_699000(a1 + 6560);
          v188 = -1;
          sub_5E5260(&v175);
        }
        if ( sub_699000(v33) >= *(uint32_t *)(a1 + 8316) )
        {
          v43 = sub_699000(v33) < *(uint32_t *)(a1 + 8320);
          v44 = *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148);
          if ( v43 )
          {
            if ( v44 == 0 )
              sub_4AECE0(1);
          }
          else if ( v44 == 2 )
          {
            sub_4AECE0(3);
          }
        }
      }
      if ( *(int *)(a1 + 8308) < 2 )
      {
        if ( sub_699000(a1 + 6560) < *(uint32_t *)(a1 + 8324) )
          goto LABEL_198;
      }
      else if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) == 0 )
      {
LABEL_198:
        if ( dword_8F7C04 != a1 || *(uint32_t *)(a1 + 200) == 2 )
          return;
        v106 = *(uint32_t *)(a1 + 6556);
        if ( (v106 == 0 || v106 == 11 || v106 == 8)
          && sub_4842B0(1, (void *)(a1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 1) != 0 )
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 16;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          v179 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 15, &v175, 0, 0);
          v188 = -1;
          sub_5E5260(&v175);
        }
        if ( *(uint32_t *)(a1 + 6556) == 15
          && *(uint32_t *)(a1 + 8240) == 0
          && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8244)
          && (uint8_t)sub_4BFC10(a1 + 8116) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        }
        v107 = *(uint32_t *)(a1 + 6556);
        if ( (v107 == 0 || v107 == 11 || v107 == 8)
          && sub_4842B0(5, (void *)(a1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 5) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 17;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 16, v169, 0, 0);
          v188 = -1;
          sub_5E5260(v169);
        }
        if ( *(uint32_t *)(a1 + 6556) == 16 )
        {
          v108 = *(uint32_t *)(a1 + 8272);
          if ( v108 != 0 )
          {
            if ( v108 != 1 || (uint8_t)sub_4BFC10(a1 + 8116) != 0 )
              goto LABEL_230;
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 19;
            v179 = 2;
            sub_431230(&v179);
            v179 = sub_699000(a1 + 6560);
            sub_431230(&v179);
            goto LABEL_229;
          }
          if ( *(uint8_t *)(a1 + 8276) == 0
            && ((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 6) == 0
             || (uint8_t)sub_4BFC10(a1 + 8116) == 0) )
          {
            *(uint8_t *)(a1 + 8276) = 1;
          }
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 6);
          v109 = sub_47E9D0(0);
          if ( *(uint8_t *)(a1 + 8276) == 0 && sub_699000(a1 + 6560) >= v109 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 18;
            v179 = 1;
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
LABEL_229:
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 16, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
LABEL_230:
        v110 = *(uint32_t *)(a1 + 6556);
        if ( v110 == 0 || v110 == 11 || v110 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(8, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 8) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 20;
            v179 = 0;
            sub_431230(&v179);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 18, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        if ( *(uint32_t *)(a1 + 6556) == 18 && *(int *)(a1 + 8308) < 2 && *(uint32_t *)(a1 + 8312) != -1 )
        {
          if ( sub_699000(a1 + 6560) > *(uint32_t *)(a1 + 8312) )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 8);
            sub_47E440(0);
            *(uint32_t *)(a1 + 8312) = -1;
          }
          else
          {
            v180 = COERCE_FLOAT(sub_4842B0(8, nullptr));
            if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 8) != 0 )
            {
              v170 = nullptr;
              v171 = 0;
              v172 = 0;
              v111 = *(uint32_t *)(a1 + 8308) + 1;
              v188 = 21;
              v179 = v111;
              sub_431230(&v179);
              sub_431230(&v180);
              (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 18, v169, 0, 0);
              v188 = -1;
              sub_5E5260(v169);
            }
          }
        }
        v112 = *(uint32_t *)(a1 + 6556);
        if ( v112 == 0 || v112 == 11 )
        {
          v179 = sub_4842B0(9, nullptr);
          if ( v179 != -1 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 9) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 22;
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 19, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v113 = *(uint32_t *)(a1 + 6556);
        if ( v113 == 0 || v113 == 11 || v113 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(20, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 20) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 23;
            v179 = 20;
            sub_431230(&v179);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v114 = *(uint32_t *)(a1 + 6556);
        if ( v114 == 0 || v114 == 11 || v114 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(21, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 21) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 24;
            v179 = 21;
            sub_431230(&v179);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v115 = *(uint32_t *)(a1 + 6556);
        if ( v115 == 0 || v115 == 11 || v115 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(22, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 22) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 25;
            v179 = 22;
            sub_431230(&v179);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        if ( *(uint32_t *)(a1 + 6556) == 20 && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8364) )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        v116 = *(uint32_t *)(a1 + 6556);
        if ( (v116 == 0 || v116 == 11) && sub_4842B0(23, nullptr) != -1 )
        {
          v179 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 740))(a1);
          v117 = (uint64_t)((double)v179 * flt_9B934C);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 736))(a1) > v117
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 23) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 23);
            Block = nullptr;
            Src = nullptr;
            v184 = nullptr;
            v188 = 26;
            v179 = 0;
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            v179 = 23;
            sub_431230(&v179);
            v118 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 23);
            v179 = sub_4B1C40(v118);
            sub_431230(&v179);
            v179 = sub_47E9D0(8);
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            v179 = 4;
            sub_431230(&v179);
            v179 = 4;
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v181, 0, 0);
            v188 = -1;
            sub_5E5260(&v181);
          }
        }
        v119 = *(uint32_t *)(a1 + 6556);
        if ( (v119 == 0 || v119 == 11)
          && sub_4842B0(24, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 24) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 24);
          Block = nullptr;
          Src = nullptr;
          v184 = nullptr;
          v188 = 27;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          v179 = 24;
          sub_431230(&v179);
          v120 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 1140))(a1, 24, -1, -1, 11);
          v179 = sub_47EF20(1, v120, v160, v161, v162);
          sub_431230(&v179);
          v179 = sub_47E9D0(3);
          sub_431230(&v179);
          v179 = 1;
          sub_431230(&v179);
          v179 = 3;
          sub_431230(&v179);
          v179 = 3;
          sub_431230(&v179);
          v162 = 0;
          v161 = 0;
          v160 = &v181;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 560))(a1, 10);
          v188 = -1;
          sub_5E5260(&v181);
        }
        v121 = *(uint32_t *)(a1 + 6556);
        if ( (v121 == 0 || v121 == 11)
          && sub_4842B0(32, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 32) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          v184 = nullptr;
          v188 = 28;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          v179 = 32;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)a1 + 1160))(a1, 32, 0);
          v179 = sub_47E9D0(v160);
          sub_431230(&v179);
          v179 = 1;
          sub_431230(&v179);
          v179 = 4;
          sub_431230(&v179);
          v179 = 4;
          sub_431230(&v179);
          v160 = nullptr;
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v181, 0);
          v188 = -1;
          sub_5E5260(&v181);
        }
        v122 = *(uint32_t *)(a1 + 6556);
        if ( v122 == 0 || v122 == 11 )
        {
          v124 = false;
          if ( *(uint8_t *)(a1 + 7730) != 0 )
          {
            v179 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 736))(a1);
            v123 = *(uint32_t *)a1;
            v180 = (double)v179 * 100.0;
            v179 = (*(int (/*thiscall*/ **)(int))(v123 + 740))(a1);
            if ( (double)dword_795A08 >= v180 / (double)v179 )
              v124 = true;
          }
          v158 = v124;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 34);
          sub_47E440(v158);
          if ( sub_4842B0(34, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 34) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 34);
            Block = nullptr;
            Src = nullptr;
            v184 = nullptr;
            v188 = 29;
            v179 = 0;
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            v179 = 34;
            sub_431230(&v179);
            v125 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 34);
            v179 = sub_4B1C40(v125);
            sub_431230(&v179);
            v179 = sub_47E9D0(1);
            sub_431230(&v179);
            v179 = 1;
            sub_431230(&v179);
            v179 = 4;
            sub_431230(&v179);
            v179 = 4;
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v181, 0, 0);
            v188 = -1;
            sub_5E5260(&v181);
          }
        }
        v126 = *(uint32_t *)(a1 + 6556);
        if ( (v126 == 0 || v126 == 11)
          && sub_4842B0(44, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 44) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 44);
          Block = nullptr;
          Src = nullptr;
          v184 = nullptr;
          v188 = 30;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          v179 = 44;
          sub_431230(&v179);
          v127 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 44);
          v179 = sub_4B1C40(v127);
          sub_431230(&v179);
          v128 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 1140))(a1, 44, -1, -1, 11);
          v179 = sub_47EF20(1, v128, v160, v161, v162);
          sub_431230(&v179);
          v179 = 1;
          sub_431230(&v179);
          v179 = 4;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 560))(a1, 10);
          v188 = -1;
          sub_5E5260(&v181);
        }
        if ( *(uint32_t *)(a1 + 6556) == 10
          && *(uint32_t *)(a1 + 7812) == 0
          && *(uint32_t *)(a1 + 7808) == 1
          && *(uint32_t *)(a1 + 7816) == 44
          && (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
        }
        v129 = dword_795A98;
        i = (int)dword_795A98;
        do
        {
          v130 = *(uint32_t *)(a1 + 6556);
          if ( (v130 == 0 || v130 == 11)
            && sub_4842B0(*v129, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, *v129) != 0 )
          {
            v131 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 1160))(a1, *(uint32_t *)i);
            Block = nullptr;
            Src = nullptr;
            v184 = nullptr;
            v188 = 31;
            v179 = 0;
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            v179 = *(uint32_t *)i;
            sub_431230(&v179);
            v132 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 1140))(a1, *(uint32_t *)i);
            if ( v132 == -1 )
              v132 = sub_41A5E0(v131 + 510);
            v179 = sub_41A5E0(*(uint32_t *)(v131 + 316) + 14 * (v132 - 1));
            sub_431230(&v179);
            v179 = sub_47E9D0(0);
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            v179 = 4;
            sub_431230(&v179);
            v179 = 0;
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 10, &v181, 0, 0);
            v188 = -1;
            if ( Block != nullptr )
              j__free(Block);
            v129 = (int *)i;
            Block = nullptr;
            Src = nullptr;
            v184 = nullptr;
          }
          i = (int)++v129;
        }
        while ( (int)v129 < (int)&CNAuraBoss `RTTI Type Descriptor' );
        v133 = (int *)&unk_795A88;
        do
        {
          v134 = *(uint32_t *)(a1 + 6556);
          if ( (v134 == 0 || v134 == 11)
            && sub_4842B0(*v133, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, *v133) != 0 )
          {
            v176 = nullptr;
            v177 = 0;
            v178 = 0;
            v179 = *v133;
            v188 = 32;
            sub_430C80(nullptr, 1, (int)&v179);
            (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 14, &v175, 0, 0);
            v188 = -1;
            if ( v176 != nullptr )
              j__free(v176);
            v176 = nullptr;
            v177 = 0;
            v178 = 0;
          }
          ++v133;
        }
        while ( (int)v133 < (int)dword_795A98 );
        if ( *(uint32_t *)(a1 + 6556) == 6
          && *(uint32_t *)(a1 + 6892) == 1
          && sub_4842B0(16, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 16) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 21, 0, 0, 0);
        }
        if ( *(uint32_t *)(a1 + 6556) == 21 && *(uint32_t *)(*(uint32_t *)(a1 + 112) + 192) == 4 )
        {
          v135 = *(uint32_t *)(a1 + 8424);
          if ( v135 >= dword_795A04 )
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 580))(
              a1,
              20016,
              v135 - dword_795A04,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 1, 0, 0, 0);
        }
        if ( *(uint32_t *)(a1 + 6556) == 6
          && *(uint32_t *)(a1 + 6892) == 1
          && sub_4842B0(17, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 17) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 33;
          v179 = 17;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 7, v169, 0, 0);
          v188 = -1;
          if ( v170 != nullptr )
            j__free(v170);
        }
        if ( *(uint32_t *)(a1 + 6556) == 12
          && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 11) > 0
          && sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8228) + *(uint32_t *)(a1 + 8232)
          && *(uint32_t *)(a1 + 8236) < dword_7959FC
          && *(uint32_t *)(a1 + 548) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 11);
          sub_47E440(1);
          if ( sub_4842B0(11, nullptr) != -1 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 11);
        }
        v136 = *(uint32_t *)(a1 + 6556);
        if ( (v136 == 0 || v136 == 11 || v136 == 8)
          && sub_4842B0(46, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 46) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          v184 = nullptr;
          v188 = 34;
          v179 = 2;
          sub_430C80(nullptr, 1, (int)&v179);
          v137 = (char *)Src;
          v179 = 46;
          if ( Block == nullptr )
            goto LABEL_357;
          if ( ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)(((uint8_t *)v184 - (uint8_t *)Block) >> 2) )
          {
            *(uint32_t *)Src = 46;
            Src = v137 + 4;
          }
          else
          {
LABEL_357:
            sub_430C80(Src, 1, (int)&v179);
          }
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 24, &v181, 0, 0);
          v188 = -1;
          if ( Block != nullptr )
            j__free(Block);
        }
        v138 = *(uint32_t *)(a1 + 6556);
        if ( (v138 == 0 || v138 == 11 || v138 == 8)
          && sub_4842B0(31, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 31) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          v184 = nullptr;
          v188 = 35;
          v179 = 0;
          sub_430C80(nullptr, 1, (int)&v179);
          v139 = (char *)Src;
          v179 = 31;
          if ( Block == nullptr )
            goto LABEL_368;
          if ( ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)(((uint8_t *)v184 - (uint8_t *)Block) >> 2) )
          {
            *(uint32_t *)Src = 31;
            Src = v139 + 4;
          }
          else
          {
LABEL_368:
            sub_430C80(Src, 1, (int)&v179);
          }
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 22, &v181, 0, 0);
          v188 = -1;
          if ( Block != nullptr )
            j__free(Block);
        }
        if ( *(uint32_t *)(a1 + 6556) == 22 )
        {
          if ( *(uint32_t *)(a1 + 8448) != 0 )
          {
            if ( sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8472) && *(uint32_t *)(a1 + 8476) == 2 )
              goto LABEL_377;
          }
          else if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
          {
LABEL_377:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
          }
        }
        if ( *(uint32_t *)(a1 + 6556) == 6
          && *(uint8_t *)(a1 + 6988) != 0
          && *(uint32_t *)(a1 + 6896) < *(uint32_t *)(a1 + 6900)
          && sub_4842B0(49, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 49) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 7, 0, 0, 0);
        }
        v140 = *(uint32_t *)(a1 + 6556);
        if ( (v140 == 0 || v140 == 11)
          && sub_4842B0(50, (void *)(a1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 50) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 36;
          v179 = 0;
          sub_431230(&v179);
          v179 = 0;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 23, v169, 0, 0);
          v188 = -1;
          if ( v170 != nullptr )
            j__free(v170);
        }
        if ( *(uint32_t *)(a1 + 6556) != 23 )
          goto LABEL_412;
        v141 = *(uint32_t *)(a1 + 8488);
        if ( v141 != 0 )
        {
          if ( v141 != 1 )
          {
            if ( v141 == 2 )
            {
              if ( *(uint8_t *)(a1 + 8516) == 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 4 )
              {
                v143 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 588))(a1);
                v144 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 1140))(a1);
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)a1 + 1160))(a1, 50, 0, v144);
                v145 = sub_47EF20(50, -1, -1, 11, "Particle/GrandWave.ptl");
                v146 = *(void **)(v143 + 19);
                *(uint32_t *)(v143 + 85) = v145;
                Src = *(void **)(v143 + 15);
                v147 = *(uint32_t *)(a1 + 8492);
                v184 = v146;
                if ( v147 > 0 )
                {
                  v159 = dword_795A0C;
                  v156 = v147;
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 51);
                  v179 = sub_47E9D0(2);
                  v148 = (double)v179 * 0.0099999998;
                  v155 = v148;
                  sub_4049C0(1.0, v155, v156, v159);
                  i = v143 + 15;
                  LODWORD(v180) = 2;
                  do
                  {
                    v149 = i;
                    *(uint32_t *)i = (uint64_t)((double)*(int *)i * v148);
                    v77 = LODWORD(v180) == 1;
                    i = v149 + 4;
                    --LODWORD(v180);
                  }
                  while ( !v77 );
                }
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 580))(
                  a1,
                  20019,
                  *(uint32_t *)(a1 + 8492),
                  v143,
                  0,
                  80,
                  0,
                  0,
                  4,
                  0,
                  0,
                  0);
                v150 = v184;
                *(uint32_t *)(v143 + 15) = Src;
                *(uint32_t *)(v143 + 19) = v150;
                *(uint8_t *)(a1 + 8516) = 1;
              }
              if ( *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 17 )
                (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
            }
            goto LABEL_412;
          }
          if ( (uint8_t)sub_4BFC10(a1 + 8116) == 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 38;
            v179 = 2;
            sub_431230(&v179);
            v179 = sub_699000(a1 + 6560);
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 23, v169, 0, 0);
            v142 = v170;
            goto LABEL_398;
          }
        }
        else if ( sub_699000(a1 + 6560) >= *(uint32_t *)(a1 + 8512) )
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 37;
          if ( (uint8_t)sub_4BFC10(a1 + 8116) != 0
            && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 51) > 0 )
          {
            v179 = 1;
            sub_431230(&v179);
          }
          else
          {
            v179 = 2;
            sub_431230(&v179);
          }
          v179 = 0;
          sub_431230(&v179);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 23, &v175, 0, 0);
          v142 = v176;
LABEL_398:
          v188 = -1;
          if ( v142 != nullptr )
            j__free(v142);
        }
LABEL_412:
        v151 = *(uint32_t *)(a1 + 6556);
        if ( (v151 == 0 || v151 == 11) && sub_4842B0(52, nullptr) != -1 )
        {
          v152 = *(uint32_t *)(a1 + 8444);
          if ( v152 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v152 + 80))(v152) != 0 )
          {
            v153 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 52);
            v179 = sub_41A5E0(v153 + 524);
            sub_47DEE0(0.0);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 52);
            sub_47DEE0(*(float *)&v179);
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1312))(a1, 52) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 39;
            v179 = 52;
            sub_431230(&v179);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 14, v169, 0, 0);
            if ( v170 != nullptr )
              j__free(v170);
          }
        }
        return;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      goto LABEL_198;
    case 0x13:
      if ( *(uint8_t *)(a1 + 8332) == 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 2 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SM_BAL_SHOT",
          -1,
          0,
          0);
        v45 = *(uint32_t *)a1;
        v46 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 1172))(a1, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(v45 + 212))(a1, v46);
        *(uint8_t *)(a1 + 8332) = 1;
      }
      if ( *(uint8_t *)(a1 + 8333) == 0 && *(int *)(*(uint32_t *)(a1 + 120) + 148) >= 8 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SWD_BAL_END",
          -1,
          0,
          0);
        *(uint8_t *)(a1 + 8333) = 1;
      }
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 120) + 170) != 0 )
LABEL_67:
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
      goto LABEL_198;
    case 0x14:
      if ( *(uint8_t *)(*(uint32_t *)(a1 + 8348) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *(uint32_t *)(a1 + 8348));
      if ( *(uint32_t *)(*(uint32_t *)(a1 + 120) + 148) == 0 && sub_4910A0(*(uint32_t *)(a1 + 120)) >= *(uint32_t *)(a1 + 8360) )
      {
        sub_4AECE0(1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
          a1,
          1,
          *(uint32_t *)(a1 + 8348),
          59,
          0,
          0,
          0);
      }
      if ( *(int *)(*(uint32_t *)(a1 + 120) + 148) < 4 || *(uint8_t *)(a1 + 8344) != 0 )
        goto LABEL_198;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) == 0 )
        goto LABEL_106;
      v47 = *(uint32_t *)(a1 + 8340);
      if ( v47 == 20 || v47 == 22 )
      {
        v49 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)a1 + 1140))(a1, v47, -1, -1, 11);
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)a1 + 1160))(a1, *(uint32_t *)(a1 + 8340), 0, v49);
        v50 = sub_47EF20(v160, v161, v162, v163, v164);
        v51 = *(uint32_t *)(a1 + 8356);
        v164 = 0;
        v163 = 0;
        v162 = 0;
        v161 = 4;
        v160 = nullptr;
        *(uint32_t *)(v51 + 85) = v50;
        v52 = *(uint32_t *)a1;
        v53 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t))(*(uint32_t *)a1 + 1140))(
                a1,
                *(uint32_t *)(a1 + 8340),
                *(uint32_t *)(a1 + 8356),
                0,
                80,
                0);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(v52 + 580))(a1, *(uint32_t *)(a1 + 8352), v53);
      }
      else if ( v47 == 21 )
      {
        v48 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 21);
        (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 580))(
          a1,
          *(uint32_t *)(a1 + 8352),
          v48,
          *(uint32_t *)(a1 + 8356),
          0,
          100,
          -4,
          0,
          4,
          0,
          0,
          0);
        *(uint8_t *)(a1 + 8344) = 1;
        goto LABEL_198;
      }
LABEL_106:
      *(uint8_t *)(a1 + 8344) = 1;
      goto LABEL_198;
    case 0x15:
      if ( sub_699000(a1 + 6560) >= 200 && *(uint8_t *)(a1 + 8413) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 876))(
          a1,
          0,
          470,
          470,
          0,
          0,
          0);
        v157 = (double)*(int *)(a1 + 6652) * -0.89999998;
        sub_494F20(2, v157);
        if ( *(uint32_t *)(a1 + 8416) == 0 )
        {
          v179 = sub_42FCB0(228);
          v188 = 10;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              v64 = sub_431920(a1 + 108, (char)"Effect/Animation/JumpAttackHold.ani", 1);
            else
              v64 = sub_431920(*(uint32_t *)(a1 + 364), (char)"Effect/Animation/JumpAttackHold.ani", 1);
          }
          else
          {
            v64 = 0;
          }
          v188 = -1;
          *(uint32_t *)(a1 + 8416) = v64;
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 204))(
          a1,
          1,
          *(uint32_t *)(a1 + 8416),
          0,
          0,
          0,
          0);
        *(uint8_t *)(a1 + 8413) = 1;
      }
      goto LABEL_198;
    case 0x16:
      if ( *(uint32_t *)(a1 + 8448) == 1 )
      {
        v65 = *(uint32_t *)(a1 + 8456);
        if ( v65 != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v65 + 840))(v65) != 9
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8456) + 840))(*(uint32_t *)(a1 + 8456)) != 5
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8456) + 308))(*(uint32_t *)(a1 + 8456)) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(a1 + 8456) + 560))(
            *(uint32_t *)(a1 + 8456),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8456) + 564))(*(uint32_t *)(a1 + 8456));
        }
        v66 = *(uint32_t *)(a1 + 8476);
        if ( v66 != 0 )
        {
          if ( v66 == 1 && sub_699000(a1 + 6560) >= 750 )
          {
            v74 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1160))(a1, 31);
            v75 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 1140))(a1, 31);
            v76 = *(uint32_t *)a1;
            i = v75;
            if ( (*(uint8_t (/*thiscall*/ **)(int))(v76 + 308))(a1) != 0 )
            {
              v77 = *(uint32_t *)(a1 + 8456) == 0;
              v184 = nullptr;
              v180 = 0.0;
              if ( !v77 )
              {
                v78 = *(uint32_t *)a1;
                v173 = 0.0;
                v174 = 0.0;
                v175 = 0.0;
                v176 = nullptr;
                v177 = 0;
                v178 = 0;
                if ( (*(int (/*thiscall*/ **)(int))(v78 + 152))(a1) != 0 )
                  v79 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 43;
                else
                  v79 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 43;
                v80 = *(uint32_t *)a1;
                v180 = *(float *)&v79;
                v173 = (float)v79;
                v179 = (*(int (/*thiscall*/ **)(int))(v80 + 124))(a1);
                v81 = *(uint32_t *)a1;
                v174 = (float)v179;
                v82 = (*(int (/*thiscall*/ **)(int))(v81 + 128))(a1);
                v83 = *(uint32_t *)(a1 + 8456);
                v179 = v82 + 90;
                v175 = (float)(v82 + 90);
                v180 = COERCE_FLOAT(sub_605840(&v184, v83, &v173, 1));
              }
              v84 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 388))(a1);
              v85 = sub_47EFD0(v74, COERCE_FLOAT(1), i, v84, v84, 0);
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, void *, float))(*(uint32_t *)a1 + 580))(
                a1,
                20017,
                v85,
                0,
                0,
                43,
                1,
                90,
                4,
                0,
                v184,
                COERCE_FLOAT(LODWORD(v180)));
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
              a1,
              "BLOOD_SPREAD",
              -1,
              0,
              0);
            sub_5F0460(a1);
            sub_47DCD0(a1, -1);
            v179 = sub_47EF20(2, i, -1, -1, 11);
            v180 = COERCE_FLOAT(sub_47EF20(3, i, -1, -1, 11));
            v86 = operator new(0x7Cu);
            v184 = v86;
            v188 = 11;
            if ( v86 != nullptr )
            {
              *(float *)&v154 = (float)SLODWORD(v180);
              v87 = sub_4B3DF0(v86, 0, 0, v154, v179, 1);
            }
            else
            {
              v87 = nullptr;
            }
            v88 = *v87;
            v188 = -1;
            (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, int, int))(v88 + 56))(v87, a1, a1, 1, 0, 9, -1);
            *(uint32_t *)(a1 + 8476) = 2;
          }
        }
        else if ( sub_699000(a1 + 6560) >= 100 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
          {
            v67 = *(uint32_t *)(a1 + 8456);
            if ( v67 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v67 + 724))(v67) == 0 )
            {
              v68 = *(uint32_t *)a1;
              v173 = 0.0;
              v174 = 0.0;
              v175 = 0.0;
              v176 = nullptr;
              v177 = 0;
              v178 = 0;
              if ( (*(int (/*thiscall*/ **)(int))(v68 + 152))(a1) != 0 )
                v69 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 43;
              else
                v69 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 43;
              v70 = *(uint32_t *)a1;
              v180 = *(float *)&v69;
              v173 = (float)v69;
              v179 = (*(int (/*thiscall*/ **)(int))(v70 + 124))(a1);
              v71 = *(uint32_t *)a1;
              v174 = (float)v179;
              v72 = (*(int (/*thiscall*/ **)(int))(v71 + 128))(a1);
              v73 = *(uint32_t *)(a1 + 8456);
              v179 = v72 + 90;
              v175 = (float)(v72 + 90);
              sub_4E5F70(a1, v73, &v173, 1, 1);
            }
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "BLOOD_SUCK",
            -1,
            0,
            0);
          *(uint32_t *)(a1 + 8476) = 1;
        }
      }
      goto LABEL_198;
    case 0x17:
      if ( *(uint32_t *)(a1 + 8488) == 1 && sub_699000(a1 + 6560) >= dword_795A0C )
      {
        if ( *(uint8_t *)(a1 + 8496) == 0 )
        {
          *(uint8_t *)(a1 + 8496) = 1;
          v89 = (uint32_t *)(a1 + 8504);
          LODWORD(v180) = 2;
          do
          {
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 208))(a1, *v89++);
            --LODWORD(v180);
          }
          while ( v180 != 0.0 );
          i = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1);
          v90 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 124))(a1);
          v91 = *(uint32_t *)a1;
          k = v90;
          v184 = (void *)(*(int (/*thiscall*/ **)(int))(v91 + 128))(a1);
          v179 = sub_42FCB0(228);
          v188 = 12;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              LOBYTE(v92) = a1 + 108;
            else
              v92 = *(uint32_t *)(a1 + 364);
            v93 = sub_431920(v92, (char)"Effect/Animation/grandWaveFullCharge2.ani", 1);
          }
          else
          {
            v93 = 0;
          }
          v179 = sub_44B6C0(284);
          v188 = 13;
          if ( v179 != 0 )
            *(float *)&v94 = COERCE_FLOAT(sub_44E1F0(v93, 1));
          else
            *(float *)&v94 = 0.0;
          v95 = *(uint32_t *)(a1 + 116);
          v180 = *(float *)&v94;
          v188 = -1;
          sub_45FE80(v95, v94, 2, 0, v94, a1, 0);
          v96 = *(uint32_t *)a1;
          v179 = *(uint32_t *)v94;
          v97 = (*(int (/*thiscall*/ **)(int))(v96 + 152))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v179 + 148))(v94, v97);
          (*(void (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)v94 + 112))(v94, i, k, v184);
          v179 = sub_42FCB0(228);
          v188 = 14;
          if ( v179 != 0 )
          {
            if ( *(uint32_t *)(a1 + 384) < 0x10u )
              LOBYTE(v98) = a1 + 108;
            else
              v98 = *(uint32_t *)(a1 + 364);
            v99 = sub_431920(v98, (char)"Effect/Animation/grandWaveFullCharge1.ani", 1);
          }
          else
          {
            v99 = 0;
          }
          v179 = sub_44B6C0(284);
          v188 = 15;
          if ( v179 != 0 )
            *(float *)&v100 = COERCE_FLOAT(sub_44E1F0(v99, 1));
          else
            *(float *)&v100 = 0.0;
          v101 = *(uint32_t *)(a1 + 116);
          v180 = *(float *)&v100;
          v188 = -1;
          sub_45FE80(v101, v100, 2, 0, v100, a1, 0);
          v102 = *(uint32_t *)a1;
          v179 = *(uint32_t *)v100;
          v103 = (*(int (/*thiscall*/ **)(int))(v102 + 152))(a1);
          (*(void (/*thiscall*/ **)(int, int))(v179 + 148))(v100, v103);
          (*(void (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)v100 + 112))(v100, i, k, v184);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
            a1,
            "GHOSTSLASH_CHARGE_END",
            -1,
            0,
            0);
        }
        if ( sub_699000(a1 + 6560) >= dword_795A0C + 200 )
        {
          v104 = sub_699000(a1 + 6560);
          v105 = sub_42B420(255, 220, -200 - dword_795A0C + v104, 100);
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)a1 + 252))(a1, 0, v105);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 252))(a1, 1, v105);
        }
      }
      goto LABEL_198;
    default:
      goto LABEL_198;
  }
}

