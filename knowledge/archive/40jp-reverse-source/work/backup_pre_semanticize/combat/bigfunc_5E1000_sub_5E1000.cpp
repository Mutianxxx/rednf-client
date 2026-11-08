// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5E1000_sub_5E1000.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5E1000）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 2592 行；字符串证据 5 条；外调 6 个
//   串: "WZ_DASH_FALL"
//   串: "Effect/Animation/WarpCloud.ani"
//   串: "PHASE_SHIFT"
//   串: "WZ_PHASE_SHIFT"
//   串: "Effect/Animation/ThrustUnder.ani"
//   调: sub_5E1000 sub_4BA730 sub_42FCB0 sub_431920 sub_44B6C0 sub_44E1F0
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5E1000 sub_5E1000  size=13379
// ------------------------------------------------------------
void /*thiscall*/ sub_5E1000(uint32_t **this, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // edi
  int i; // ebx
  uint32_t *v11; // edi
  int j; // ebx
  uint32_t *v13; // edi
  int k; // ebx
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  int v19; // edi
  int v20; // eax
  int v21; // ecx
  int v22; // edi
  int *v23; // edi
  int v24; // ecx
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  int v30; // edi
  int *v31; // edi
  int v32; // ecx
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // edi
  int v38; // eax
  int v39; // edx
  int v40; // edx
  char *v41; // edi
  int v42; // ebx
  int v43; // eax
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // eax
  int v48; // edx
  int v49; // eax
  int v50; // edi
  uint32_t *v51; // eax
  uint32_t *v52; // eax
  int *v53; // ecx
  int v54; // edx
  int v55; // eax
  int v56; // edi
  int v57; // eax
  float *v58; // edi
  float *m; // ebx
  double v60; // st7
  int v61; // edx
  char *v62; // edi
  int v63; // ebx
  int v64; // eax
  int v65; // eax
  int v66; // edx
  int v67; // eax
  uint32_t *v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // eax
  int v74; // edx
  int v75; // edi
  int v76; // eax
  void *v77; // eax
  uint32_t *v78; // eax
  int v79; // edx
  char *v80; // edi
  int v81; // ebx
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // edx
  int v86; // eax
  uint32_t *v87; // eax
  int v88; // edx
  int v89; // edx
  uint32_t *v90; // eax
  uint32_t *v91; // eax
  char *v92; // edi
  int v93; // eax
  bool v94; // zf
  int v95; // ecx
  int v96; // eax
  int v97; // edx
  int v98; // eax
  int v99; // ebx
  int v100; // eax
  int v101; // edx
  int v102; // ebx
  int v103; // eax
  int v104; // eax
  int v105; // ebx
  int v106; // eax
  int v107; // edx
  int v108; // eax
  int v109; // eax
  int v110; // eax
  uint32_t *v111; // eax
  uint32_t *v112; // edi
  int n; // ebx
  int v114; // eax
  int v115; // ecx
  int v116; // eax
  int v117; // ebx
  int v118; // eax
  int v119; // eax
  void *v120; // eax
  int v121; // edx
  void *v122; // eax
  int v123; // eax
  int v124; // eax
  int v125; // eax
  void *v126; // eax
  int v127; // eax
  int v128; // eax
  int v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // ecx
  int v133; // eax
  bool v134; // al
  int v135; // edi
  uint32_t *v136; // eax
  uint32_t *v137; // eax
  uint32_t *v138; // edi
  int ii; // ebx
  int v140; // edx
  int v141; // eax
  int v142; // eax
  uint32_t *v143; // edi
  int v144; // eax
  int v145; // eax
  int v146; // edx
  int v147; // eax
  int v148; // ebx
  int v149; // eax
  int v150; // eax
  int v151; // ecx
  int v152; // eax
  char v153; // al
  int v154; // ebx
  int v155; // edi
  int v156; // eax
  int v157; // edx
  int v158; // eax
  uint32_t *v159; // eax
  int v160; // eax
  int v161; // ebx
  int v162; // eax
  int v163; // eax
  int v164; // eax
  int v165; // eax
  uint32_t *v166; // eax
  int v167; // eax
  int v168; // edx
  int v169; // ebx
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int v173; // eax
  uint32_t *v174; // eax
  uint32_t *v175; // eax
  int v176; // edi
  int v177; // eax
  int v178; // eax
  int v179; // edi
  int v180; // eax
  int v181; // eax
  int v182; // eax
  int v183; // edi
  int v184; // eax
  int v185; // edx
  int v186; // ebx
  int v187; // eax
  float v188; // eax
  int v189; // ebx
  int v190; // eax
  int v191; // eax
  int v192; // eax
  int v193; // eax
  int v194; // eax
  int v195; // eax
  uint32_t *v196; // eax
  int v197; // ebx
  int v198; // edi
  int v199; // edx
  int v200; // edi
  int *v201; // edi
  int v202; // ecx
  int v203; // ebx
  int v204; // ebx
  int v205; // eax
  int v206; // eax
  int v207; // eax
  int v208; // eax
  double v209; // st7
  int v210; // eax
  int v211; // ecx
  int v212; // edi
  int *v213; // edi
  int v214; // edx
  int v215; // ebx
  int v216; // eax
  int v217; // ebx
  int v218; // eax
  int v219; // eax
  int v220; // eax
  int v221; // eax
  uint32_t *v222; // edi
  int v223; // eax
  uint32_t *v224; // eax
  uint32_t *v225; // eax
  int v226; // eax
  int v227; // ecx
  int jj; // edi
  int v229; // eax
  int v230; // edi
  int v231; // eax
  int v232; // ecx
  int v233; // edi
  int *v234; // edi
  int v235; // edx
  int v236; // ebx
  int v237; // eax
  int v238; // eax
  int v239; // eax
  int v240; // ebx
  int v241; // eax
  int v242; // edi
  int v243; // eax
  int v244; // eax
  int v245; // ebx
  int v246; // eax
  int v247; // eax
  uint32_t *v248; // edi
  int v249; // eax
  uint32_t *v250; // eax
  double v251; // st7
  int v252; // eax
  int v253; // eax
  int v254; // edx
  int v255; // ebx
  int v256; // ebx
  int v257; // ecx
  uint32_t *v258; // edi
  int v259; // edx
  int v260; // eax
  int v261; // eax
  int v262; // ecx
  int *v263; // eax
  int v264; // ebx
  int v265; // eax
  int v266; // edi
  int v267; // eax
  int v268; // eax
  int v269; // edx
  int v270; // eax
  int v271; // eax
  float v272; // eax
  int v273; // eax
  uint32_t *v274; // eax
  uint32_t *v275; // eax
  int64_t v276; // rax
  int v277; // eax
  int v278; // eax
  int v279; // eax
  int v280; // ecx
  int v281; // [esp+B4h] [ebp-1A4h]
  int v282; // [esp+B8h] [ebp-1A0h]
  int v283; // [esp+B8h] [ebp-1A0h]
  int v284; // [esp+BCh] [ebp-19Ch]
  unsigned int v285; // [esp+C8h] [ebp-190h]
  unsigned int v286; // [esp+C8h] [ebp-190h]
  unsigned int v287; // [esp+C8h] [ebp-190h]
  int v288; // [esp+CCh] [ebp-18Ch]
  int v289; // [esp+D0h] [ebp-188h]
  int v290; // [esp+D0h] [ebp-188h]
  int v291; // [esp+D0h] [ebp-188h]
  int v292; // [esp+D0h] [ebp-188h]
  int v293; // [esp+D0h] [ebp-188h]
  int v294; // [esp+D4h] [ebp-184h]
  int v295; // [esp+D4h] [ebp-184h]
  int v296; // [esp+D4h] [ebp-184h]
  int v297; // [esp+D4h] [ebp-184h]
  int v298; // [esp+D4h] [ebp-184h]
  int v299; // [esp+D4h] [ebp-184h]
  uint32_t *v300; // [esp+D8h] [ebp-180h]
  uint32_t *v301; // [esp+D8h] [ebp-180h]
  uint32_t *v302; // [esp+D8h] [ebp-180h]
  int v303; // [esp+D8h] [ebp-180h]
  int v304; // [esp+D8h] [ebp-180h]
  int v305; // [esp+D8h] [ebp-180h]
  int v306; // [esp+D8h] [ebp-180h]
  int v307; // [esp+D8h] [ebp-180h]
  float v308; // [esp+D8h] [ebp-180h]
  int v309; // [esp+DCh] [ebp-17Ch]
  int v310; // [esp+E0h] [ebp-178h]
  int v311; // [esp+E4h] [ebp-174h]
  int v312; // [esp+E8h] [ebp-170h] BYREF
  int v313; // [esp+ECh] [ebp-16Ch]
  int v314; // [esp+F0h] [ebp-168h]
  int v315; // [esp+F4h] [ebp-164h]
  char v316[4]; // [esp+F8h] [ebp-160h] BYREF
  int v317; // [esp+FCh] [ebp-15Ch]
  int v318; // [esp+100h] [ebp-158h]
  int v319; // [esp+104h] [ebp-154h]
  unsigned int v320; // [esp+118h] [ebp-140h]
  float v321; // [esp+11Ch] [ebp-13Ch]
  int v322; // [esp+120h] [ebp-138h] BYREF
  float v323; // [esp+124h] [ebp-134h]
  int v324; // [esp+128h] [ebp-130h]
  char Buffer[276]; // [esp+12Ch] [ebp-12Ch] BYREF
  int v326; // [esp+240h] [ebp-18h]
  int v327; // [esp+244h] [ebp-14h]
  int v328; // [esp+248h] [ebp-10h]
  int v329; // [esp+254h] [ebp-4h]
  int v330; // [esp+260h] [ebp+8h]
  int v331; // [esp+260h] [ebp+8h]
  int v332; // [esp+260h] [ebp+8h]
  int v333; // [esp+260h] [ebp+8h]
  int v334; // [esp+260h] [ebp+8h]
  int v335; // [esp+260h] [ebp+8h]
  int v336; // [esp+260h] [ebp+8h]
  float v337; // [esp+260h] [ebp+8h]
  uint32_t *v338; // [esp+260h] [ebp+8h]
  int v339; // [esp+260h] [ebp+8h]
  int v340; // [esp+260h] [ebp+8h]

  v328 = dword_796E50;
  v322 = (int)*(this + 1639);
  v327 = 15;
  v326 = 0;
  Buffer[260] = 0;
  v6 = a2;
  v329 = 0;
  switch ( v322 )
  {
    case 10:
      if ( *(this + 1953) == nullptr )
      {
        if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + (uint32_t)*(this + 1952) + 2106));
        v7 = (int)*(this + 1954);
        switch ( v7 )
        {
          case 5:
          case 6:
          case 7:
          case 9:
          case 8:
            v15 = (int)*this;
            if ( *(this + 1952) != nullptr )
              v8 = (int)*(this + 2109);
            else
              v8 = (int)*(this + 2108);
            goto LABEL_51;
          case 16:
            if ( a2 != 10 )
            {
              v8 = (int)*(this + 2112);
              goto LABEL_50;
            }
            break;
          case 17:
            if ( *(this + 1952) == (uint32_t *)1 )
            {
              v8 = (int)*(this + 2113);
              goto LABEL_50;
            }
            break;
          case 18:
            if ( *(this + 1952) == nullptr )
            {
              v9 = this + 2114;
              for ( i = 2; i != 0; --i )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *v9++);
              v6 = a2;
            }
            break;
          case 28:
            if ( *(this + 1952) == nullptr )
            {
              v8 = (int)*(this + 2116);
              goto LABEL_50;
            }
            break;
          case 31:
            if ( *(this + 1952) == nullptr )
            {
              v11 = this + 2117;
              for ( j = 3; j != 0; --j )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *v11++);
              v6 = a2;
            }
            break;
          case 15:
            if ( a2 != 10 )
              ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t))(*this)[68])(this, 0, 0);
            break;
          default:
            if ( v7 == 49 && a2 != 10 )
            {
              v13 = this + 2120;
              for ( k = 2; k != 0; --k )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *v13++);
              v6 = a2;
            }
            break;
        }
      }
      break;
    case 18:
      if ( *(this + 2100) == (uint32_t *)4 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2102));
        v8 = (int)*(this + 2103);
        goto LABEL_50;
      }
      break;
    case 19:
      v8 = (int)*(this + 2125);
      goto LABEL_50;
    case 20:
      if ( *(this + 2129) == (uint32_t *)20 )
      {
        v8 = (int)*(this + 2131);
LABEL_50:
        v15 = (int)*this;
LABEL_51:
        (*(void (/*stdcall*/ **)(int))(v15 + 208))(v8);
      }
      break;
    case 21:
      if ( a2 != 21 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2136));
      if ( *(this + 2133) == nullptr )
        sub_4BA730(2, 4, 0, 0);
      break;
    default:
      break;
  }
  if ( v6 == 15 )
  {
    v6 = 8;
    a2 = 8;
    v322 = 15;
  }
  v16 = (int)*(this + 2142);
  if ( v16 != -1 && v6 != 0 && v6 != 11 )
  {
    if ( v16 >= 55 )
      v17 = 4;
    else
      v17 = dword_738048[v16];
    sub_4BA730(2, v17, 0, 0);
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[63])(this, 0, -1);
    ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[63])(this, 1, -1);
    *(this + 2142) = (uint32_t *)-1;
  }
  v18 = a3;
  switch ( v6 )
  {
    case 16:
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 1554));
      ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 1, 1, 1000, 1000);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(*this)[219])(this, 0, 250, 250, 0, -480, 1);
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v19 = (int)*this;
      v20 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v19 + 896))(this, v20);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_DASH_FALL", -1, 0, 0);
      break;
    case 17:
      v324 = sub_42FCB0(228);
      LOBYTE(v329) = 1;
      if ( v324 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v21) = (uint8_t)this + 108;
        else
          v21 = (int)*(this + 91);
        v22 = sub_431920(v21, (char)"Effect/Animation/WarpCloud.ani", 1);
      }
      else
      {
        v22 = 0;
      }
      v324 = sub_44B6C0(284);
      LOBYTE(v329) = 2;
      if ( v324 != 0 )
        v23 = (int *)sub_44E1F0(v22, 1);
      else
        v23 = nullptr;
      v24 = (int)*(this + 29);
      LOBYTE(v329) = 0;
      sub_45FE80(v24, (int)v23, 2, 0, (int)v23, 0, 0);
      v25 = *v23;
      v26 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
      v27 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v26);
      v28 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v27 + 1);
      (*(void (/*thiscall*/ **)(int *, int))(v25 + 112))(v23, v28);
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[145])(
          this,
          23001,
          *(uint32_t *)(*(uint32_t *)(a3 + 4) + 20),
          0,
          0,
          0,
          0,
          50,
          4,
          0,
          0,
          0);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t))(*this)[28])(
        this,
        *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4),
        *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8),
        0);
      v324 = sub_42FCB0(228);
      LOBYTE(v329) = 3;
      if ( v324 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v29) = (uint8_t)this + 108;
        else
          v29 = (int)*(this + 91);
        v30 = sub_431920(v29, (char)"Effect/Animation/WarpCloud.ani", 1);
      }
      else
      {
        v30 = 0;
      }
      v324 = sub_44B6C0(284);
      LOBYTE(v329) = 4;
      if ( v324 != 0 )
        v31 = (int *)sub_44E1F0(v30, 1);
      else
        v31 = nullptr;
      v32 = (int)*(this + 29);
      LOBYTE(v329) = 0;
      sub_45FE80(v32, (int)v31, 2, 0, (int)v31, (int)this, 0);
      v33 = *v31;
      v34 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
      v35 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v34);
      v36 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v35);
      (*(void (/*thiscall*/ **)(int *, int))(v33 + 112))(v31, v36);
      sub_49C620(0, 1, 0);
      v37 = a3;
      sub_49C5F0(0, 0, 0, *(uint32_t *)(*(uint32_t *)(a3 + 4) + 12));
      v38 = (int)*(this + 1542);
      v39 = (int)*this;
      *(this + 2099) = *(uint32_t **)(*(uint32_t *)(v37 + 4) + 16);
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v39 + 196))(this, v38);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, 1000, 1000);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "PHASE_SHIFT", -1, 0, 0);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_PHASE_SHIFT", -1, 0, 0);
      break;
    case 18:
      v40 = (int)*this;
      v300 = **(uint32_t ***)(a3 + 4);
      *(this + 2100) = v300;
      *((uint8_t *)this + 8404) = 0;
      v41 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v40 + 1160))(this, v300);
      v42 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2100));
      if ( *(this + 2100) == (uint32_t *)4 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[86])(this, *(this + 139));
        v43 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v44 = sub_47EFD0(v41, 0.0, v42, v43, v43, 11);
        v45 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v44 - 100);
        v46 = (*(int (/*thiscall*/ **)(uint32_t **))(v45 + 388))(this);
        LODWORD(v323) = 100 * sub_47EFD0(v41, COERCE_FLOAT(2), v42, v46, v46, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)SLODWORD(v323) + *((float *)this + 97);
        *(float *)&v47 = COERCE_FLOAT(sub_47EF20(1, v42, -1, -1, 11));
        v48 = (int)*this;
        v323 = *(float *)&v47;
        v321 = (double)v47 * 0.001 + 1.0;
        v49 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v48 + 672))(this, 3);
        v323 = COERCE_FLOAT(sub_495500(v49));
        v50 = (uint64_t)((double)SLODWORD(v323) * v321);
        ((void (/*fastcall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          (uint64_t)((double)SLODWORD(v323) * v321) >> 32,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, v50, v50);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[1]);
        if ( *(this + 2102) == nullptr )
        {
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 5;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v51 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustUnder.ani", 1);
            else
              v51 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustUnder.ani", 1);
          }
          else
          {
            v51 = nullptr;
          }
          *(this + 2102) = v51;
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 6;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v52 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustOver.ani", 1);
            else
              v52 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustOver.ani", 1);
          }
          else
          {
            v52 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2103) = v52;
        }
        v53 = *(this + 1625);
        v54 = *v53;
        v323 = 0.0;
        v55 = (*(int (/*thiscall*/ **)(int *))(v54 + 248))(v53);
        v324 = v55;
        v320 = 0;
        v321 = 0.0;
        while ( 1 )
        {
          v56 = *(uint32_t *)(v55 + 4);
          if ( v56 == 0 || v320 >= (*(uint32_t *)(v55 + 8) - v56) / 124 )
            break;
          if ( *(uint32_t *)(*(uint32_t *)(LODWORD(v321) + v56 + 60) + 4) != 0 )
          {
            v57 = sub_4924C0(5);
            v58 = *(float **)(v57 + 60);
            for ( m = *(float **)(v57 + 64); v58 != m; v58 += 6 )
            {
              v60 = v58[3] + *v58;
              if ( v60 > (double)SLODWORD(v323) )
                LODWORD(v323) = (uint64_t)v60;
            }
          }
          LODWORD(v321) += 124;
          v55 = v324;
          ++v320;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
          this,
          -1,
          *(this + 2102),
          LODWORD(v323) - 5,
          -41,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2103),
          LODWORD(v323) - 5,
          -41,
          0,
          0);
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_PRICK", -1, 0, 0);
      break;
    case 19:
      v61 = (int)*this;
      v301 = **(uint32_t ***)(a3 + 4);
      *(this + 2124) = v301;
      v62 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v61 + 1160))(this, v301);
      v63 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2124));
      if ( *(this + 2124) == (uint32_t *)12 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 38);
        v64 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v65 = sub_47EFD0(v62, 0.0, v63, v64, v64, 11);
        v66 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v65 - 100);
        v67 = (*(int (/*thiscall*/ **)(uint32_t **))(v66 + 388))(this);
        v324 = 100 * sub_47EFD0(v62, COERCE_FLOAT(4), v63, v67, v67, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)v324 + *((float *)this + 97);
        *(this + 114) = (uint32_t *)sub_47EF20(2, v63, -1, -1, 11);
        v68 = (uint32_t *)sub_47EF20(3, v63, -1, -1, 11);
        v69 = (int)*this;
        *(this + 113) = v68;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v69 + 196))(this, (*(this + 1554))[2]);
        v70 = sub_47EF20(1, v63, -1, -1, 11);
        v71 = (int)*this;
        v324 = v70;
        v323 = (double)v70 * 0.001 + 1.0;
        v72 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v71 + 672))(this, 3);
        v324 = sub_495500(v72);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(
          this,
          0,
          0,
          (uint64_t)((double)v324 * v323),
          (uint64_t)((double)v324 * v323));
        v73 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);
        v74 = (int)*this;
        *(this + 2128) = (uint32_t *)v73;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(v74 + 876))(
          this,
          0,
          360,
          360,
          0,
          -1800,
          1);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, int))(*this)[219])(this, 1, 300, 300, 0, -1500, 1);
        v75 = (int)*this;
        v76 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[38])(this, *(this + 2128));
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v75 + 896))(this, v76);
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "WZ_PRE_HEAVENHIT",
          -1,
          0,
          0);
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
        this,
        "HEAVEN_HIT_MOVE",
        -1,
        0,
        0);
      v77 = (void *)((int (/*thiscall*/ *)(uint32_t **, int))(*this)[293])(this, 1);
      sub_406D60(v77);
      if ( *(this + 2125) == nullptr )
      {
        v324 = sub_42FCB0(228);
        LOBYTE(v329) = 7;
        if ( v324 != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            v78 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/UpperSwing.ani", 1);
          else
            v78 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/UpperSwing.ani", 1);
        }
        else
        {
          v78 = nullptr;
        }
        LOBYTE(v329) = 0;
        *(this + 2125) = v78;
      }
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        1,
        *(this + 2125),
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8504) = 0;
      *(this + 2127) = (uint32_t *)-150;
      break;
    case 20:
      v79 = (int)*this;
      v302 = **(uint32_t ***)(a3 + 4);
      *(this + 2129) = v302;
      *((uint8_t *)this + 8520) = 0;
      v80 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v79 + 1160))(this, v302);
      v81 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2129));
      v82 = (int)*(this + 2129);
      if ( v82 == 13 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 76);
        v83 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v84 = sub_47EFD0(v80, 0.0, v81, v83, v83, 11);
        v85 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v84 - 100);
        v86 = (*(int (/*thiscall*/ **)(uint32_t **))(v85 + 388))(this);
        v324 = 100 * sub_47EFD0(v80, COERCE_FLOAT(3), v81, v86, v86, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)v324 + *((float *)this + 97);
        *(this + 113) = (uint32_t *)sub_47EF20(1, v81, -1, -1, 11);
        v87 = (uint32_t *)sub_47EF20(2, v81, -1, -1, 11);
        v88 = (int)*this;
        *(this + 114) = v87;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v88 + 196))(this, (*(this + 1554))[3]);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 2, 2, 1000, 1000);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "WZ_SWING_READY",
          -1,
          0,
          0);
      }
      else if ( v82 == 20 )
      {
        v89 = (int)*this;
        v303 = (int)(*(this + 139) + 152);
        *(this + 2132) = (uint32_t *)4;
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v89 + 344))(this, v303);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[5]);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 3, 3, 1000, 1000);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        if ( *(this + 2131) == nullptr )
        {
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 8;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v90 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
            else
              v90 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
          }
          else
          {
            v90 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2131) = v90;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2131),
          0,
          0,
          0,
          0);
      }
      break;
    case 21:
      v91 = **(uint32_t ***)(a3 + 4);
      *(this + 2133) = v91;
      if ( v91 != nullptr )
      {
        if ( v91 == (uint32_t *)1 )
          *(this + 2135) = *(uint32_t **)(*(uint32_t *)(v18 + 4) + 4);
      }
      else
      {
        *(this + 2134) = *(uint32_t **)(*(uint32_t *)(v18 + 4) + 4);
      }
      v92 = (char *)((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 2134));
      v93 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2134));
      v94 = *(this + 2134) == (uint32_t *)14;
      v324 = v93;
      if ( v94 )
      {
        v95 = (int)*(this + 2133);
        if ( v95 != 0 )
        {
          if ( v95 == 1 )
          {
            v98 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
            v99 = sub_432E50(v98);
            v100 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);
            v101 = (int)*this;
            if ( v100 == v99 )
              (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v101 + 876))(0, 0, 0, 0, 0, 0);
            else
              (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, int))(v101 + 876))(
                0,
                dword_9B9338,
                dword_9B9338,
                0,
                dword_9B933C,
                1);
            v102 = (int)*this;
            v103 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);
            (*(void (/*thiscall*/ **)(uint32_t **, int))(v102 + 896))(this, v103);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "PALM_FLASH",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "R_WZ_PALMFLASH",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 114);
            v104 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
            v105 = v324;
            v106 = sub_47EFD0(v92, COERCE_FLOAT(1), v324, v104, v104, 0);
            v107 = (int)*this;
            v324 = v106;
            v108 = (*(int (/*thiscall*/ **)(uint32_t **))(v107 + 388))(this);
            v109 = sub_47EFD0(v92, 0.0, v105, v108, v108, 0);
            v324 = sub_423A80(v109, v324, *(this + 2135), dword_9B9340);
            *((float *)this + 97) = (float)v324;
            *(this + 113) = (uint32_t *)sub_47EF20(2, v105, -1, -1, 11);
            *(this + 114) = (uint32_t *)sub_47EF20(3, v105, -1, -1, 11);
          }
        }
        else
        {
          v96 = sub_47EF20(4, v93, -1, -1, 11);
          v97 = (int)*this;
          v324 = v96;
          v323 = (double)v96 * 0.001 + 1.0;
          v324 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v97 + 900))(this, 3);
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(
            this,
            0,
            0,
            (uint64_t)((double)v324 * v323),
            (uint64_t)((double)v324 * v323));
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        }
      }
      v110 = (int)*(this + 2133);
      if ( v110 != 0 )
      {
        if ( v110 == 1 )
        {
          *(this + 2137) = (uint32_t *)-200;
          v112 = this + 2104;
          for ( n = 2; n != 0; --n )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v112 + 12))(*v112, 0);
            ++v112;
          }
          sub_4939E0((int)*(this + 30), 0);
          v114 = sub_491C70(8);
          sub_493A60(v114);
          v115 = (int)*(this + 2136);
          LOBYTE(a5) = 0;
          sub_4939E0(v115, 0);
          v116 = sub_491C70(8);
          sub_493A60(v116);
          sub_491F80(-1, -1, -1, -1, 1);
        }
      }
      else
      {
        if ( *(this + 2136) == nullptr )
        {
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 9;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v111 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HandStrike.ani", 1);
            else
              v111 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/HandStrike.ani", 1);
          }
          else
          {
            v111 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2136) = v111;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2136),
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[4]);
        *(this + 2145) = nullptr;
      }
      break;
    default:
      break;
  }
  v117 = a3;
  sub_4B89D0(a2, a3, *(float *)&a4, *(float *)&a5);
  switch ( a2 )
  {
    case 0:
      goto LABEL_156;
    case 6:
      v123 = (int)*(this + 1723);
      if ( v123 == 0 )
        *((uint8_t *)this + 8585) = 0;
      if ( *((uint8_t *)this + 8585) != 0 && v123 == 1 )
      {
        v285 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          v285,
          v285,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v124 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v124 = sub_432E50(v124);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v124, 4);
        *((uint8_t *)this + 6996) = 1;
      }
      return;
    case 7:
      v125 = (int)*this;
      *((uint8_t *)this + 8220) = 0;
      v126 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v125 + 1172))(this, 1);
      sub_406D60(v126);
      if ( *((uint8_t *)this + 8585) != 0 )
      {
        v286 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          v286,
          v286,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v127 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v127 = sub_432E50(v127);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v127, 4);
      }
      return;
    case 8:
      if ( v322 != 8 )
      {
        if ( (unsigned int)sub_41C5A0(v117) <= 1 )
          v118 = -1;
        else
          v118 = *(uint32_t *)(*(uint32_t *)(v117 + 4) + 4);
        *(this + 2054) = (uint32_t *)v118;
      }
      if ( *(this + 2054) != (uint32_t *)-1 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[332])(this, 0);
      v119 = (int)*this;
      *((uint8_t *)this + 8220) = 0;
      v120 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v119 + 1172))(this, 1);
      sub_406D60(v120);
      if ( sub_41A5E0(this + 1757) >= 2 )
        ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("R_WZ_LAST_ATK", -1, 0, 0);
      else
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_ATK", -1, 0, 0);
      return;
    case 10:
      if ( *(this + 1953) != nullptr )
        return;
      v128 = (int)*(this + 1952);
      a3 = 0;
      v321 = 0.0;
      if ( v128 != 0 )
      {
        if ( v128 == 1 )
        {
          v135 = (int)*(this + 2144);
          if ( v135 > 0 && (unsigned int)sub_41C5A0(v117) > 1 )
            a3 = 1000 * *(uint32_t *)(*(uint32_t *)(v117 + 4) + 4) / v135;
          *((uint8_t *)this + 8585) = 0;
        }
      }
      else
      {
        if ( (unsigned int)sub_41C5A0(v117) <= 0xA )
          v129 = 0;
        else
          v129 = *(uint32_t *)(*(uint32_t *)(v117 + 4) + 40);
        *(this + 2144) = (uint32_t *)v129;
        if ( v129 > 0 )
        {
          *(this + 2142) = *(this + 1954);
          v130 = sub_699000((int)(this + 9));
          v304 = (int)*(this + 2142);
          *(this + 2143) = (uint32_t *)((char *)*(this + 1955) + v130);
          *(this + 1955) = (uint32_t *)-1;
          v131 = sub_5DA1E0(v304);
          sub_4BA610(v131);
          v132 = (int)*(this + 2058);
          *(this + 2145) = nullptr;
          if ( v132 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v132 + 80))(v132) != 0 )
          {
            v289 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 2, -1);
            ((void (/*thiscall*/ *)(uint32_t **))(*this)[290])(this);
            v133 = (int)*(this + 2144) * (1000 - sub_47EF20(2, 3, v289, -1, 11)) / 1000;
            *(this + 2144) = (uint32_t *)v133;
            if ( v133 <= 1 )
              v133 = 1;
            *(this + 2144) = (uint32_t *)v133;
          }
        }
        v134 = (unsigned int)sub_41C5A0(v117) > 0xB && *(uint32_t *)(*(uint32_t *)(v117 + 4) + 44) == 1;
        *((uint8_t *)this + 8584) = v134;
        v294 = 2;
        if ( v134 )
        {
          sub_494F20(2, 0.0);
          v294 = 0;
        }
        sub_495890(v294, 0);
      }
      if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
      {
        if ( *(this + 2106) == nullptr )
        {
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 10;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v136 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow1.ani", 1);
            else
              v136 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow1.ani", 1);
          }
          else
          {
            v136 = nullptr;
          }
          *(this + 2106) = v136;
          v324 = sub_42FCB0(228);
          LOBYTE(v329) = 11;
          if ( v324 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
            {
              LOBYTE(v329) = 0;
              *(this + 2107) = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow2.ani", 1);
            }
            else
            {
              v137 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow2.ani", 1);
              LOBYTE(v329) = 0;
              *(this + 2107) = v137;
            }
          }
          else
          {
            LOBYTE(v329) = 0;
            *(this + 2107) = nullptr;
          }
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + (uint32_t)*(this + 1952) + 2106),
          0,
          0,
          0,
          0);
        if ( *(this + 1952) == (uint32_t *)1 )
        {
          v138 = this + 2104;
          for ( ii = 2; ii != 0; --ii )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v138 + 12))(*v138, 0);
            ++v138;
          }
        }
      }
      v140 = (int)*(this + 1954);
      switch ( v140 )
      {
        case 5:
        case 6:
        case 7:
        case 9:
        case 8:
          if ( *(this + 1952) != nullptr )
          {
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2109),
              0,
              0,
              0,
              0);
            if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
            {
              v277 = sub_5DA920(*(this + 1954));
              sub_5DC480(v277, 0);
            }
            *(this + 2061) = *(this + 1954);
          }
          else
          {
            if ( *(this + 2108) == nullptr )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 12;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v274 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast1.ani", 1);
                else
                  v274 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast1.ani", 1);
              }
              else
              {
                v274 = nullptr;
              }
              *(this + 2108) = v274;
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 13;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v275 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast2.ani", 1);
                else
                  v275 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast2.ani", 1);
              }
              else
              {
                v275 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2109) = v275;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2108),
              0,
              0,
              0,
              0);
            v276 = sub_5DA920(*(this + 1954));
            (*(void (/*thiscall*/ **)(uint32_t **, char *, int, uint32_t, uint32_t))(HIDWORD(v276) + 212))(
              this,
              off_795828[(uint32_t)v276],
              -1,
              0,
              0);
          }
          goto LABEL_509;
        case 10:
          v141 = (int)*(this + 1952);
          if ( v141 != 0 )
          {
            if ( v141 == 1 )
              sub_5DCF20(this);
          }
          else
          {
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "WZ_CHASER_EXPLOSION",
              -1,
              0,
              0);
          }
          goto LABEL_509;
        case 11:
          v142 = (int)*(this + 1952);
          if ( v142 != 0 )
          {
            if ( v142 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 11);
                v330 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 11);
                v143 = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(
                                   this,
                                   "Particle/MagicMissile.ptl");
                v295 = (uint16_t)a3;
                v290 = sub_47EF20(3, v330, -1, -1, 11);
                v144 = sub_47EF20(2, v330, -1, -1, 11);
                *(uint32_t *)((char *)v143 + 85) = sub_423A80(v144, v290, v295, 1000);
                v145 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);
                v146 = (int)*this;
                v322 = v145;
                v147 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v146 + 1132))(this, 1);
                if ( v147 == 2 )
                {
                  if ( v322 == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )
                    v143[18] = -sub_47E9D0(1);
                  else
                    v143[18] = -sub_47E9D0(2);
                }
                else if ( v147 == 3 )
                {
                  if ( v322 == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )
                    v143[18] = sub_47E9D0(1);
                  else
                    v143[18] = sub_47E9D0(2);
                }
                else
                {
                  v143[18] = 0;
                }
                *(float *)&a5 = 0.0;
                a4 = 0;
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + 44;
                else
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - 44;
                v288 = *(uint32_t *)((char *)v143 + 85) * *(uint32_t *)((char *)v143 + 15) / 1000;
                v284 = v143[19];
                v282 = v143[18];
                v281 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 60;
                v149 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
                sub_4B2580(&a5, &a4, this, v148, v149, v281, v282, v284, 15, 0, -1, v288, 30, 30, 30);
                v150 = v143[19];
                v143[18] += a5;
                v143[19] = a4 + v150;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                  this,
                  23007,
                  v330,
                  v143,
                  0,
                  44,
                  0,
                  60,
                  4,
                  0,
                  2,
                  &a3);
                v151 = v143[19];
                v143[18] -= a5;
                v143[19] = v151 - a4;
              }
              sub_5DBBD0("R_WZ_MAGIC_MISSILE", 500);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_MAGIC_MISSILE_READY");
          }
          goto LABEL_509;
        case 15:
          v152 = (int)*(this + 1952);
          if ( v152 != 0 )
          {
            if ( v152 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                v153 = *((uint8_t *)this + 8584);
                dword_78FE2C = 0;
                v154 = v153 != 0 ? 73 : 68;
                v331 = v153 != 0 ? 0 : 0x35;
                sub_5C6A90(a3);
                if ( *((uint8_t *)this + 8584) != 0 )
                  sub_5DAE20(dword_9B9344);
                v155 = (int)*this;
                v156 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int))(*this)[285])(
                         this,
                         15,
                         0,
                         0,
                         v154,
                         0,
                         v331,
                         4,
                         0,
                         dword_78FE2C,
                         dword_78FE28);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v155 + 580))(this, 23008, v156);
              }
              sub_5DBBD0("R_WZ_LANTERN_FIRE", 500);
              if ( *((uint8_t *)this + 8584) != 0 )
              {
                v157 = (int)*this;
                *((uint8_t *)this + 8585) = 1;
                (*(void (/*thiscall*/ **)(uint32_t **, int))(v157 + 1160))(this, 42);
                *(this + 2147) = (uint32_t *)-sub_47E9D0(0);
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 42);
                v321 = COERCE_FLOAT(sub_47E9D0(1));
              }
            }
          }
          else
          {
            sub_5DADE0("R_WZ_LANTERN_FIRE_READY");
          }
          goto LABEL_509;
        case 16:
          v158 = (int)*(this + 1952);
          if ( v158 == 0 )
          {
            if ( *(this + 2112) == nullptr )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 14;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v159 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchFrostHead.ani", 1);
                else
                  v159 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchFrostHead.ani", 1);
              }
              else
              {
                v159 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2112) = v159;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2112),
              0,
              0,
              0,
              0);
            sub_5DADE0("R_WZ_FROSTHEAD_READY");
            goto LABEL_509;
          }
          if ( v158 != 1 )
            goto LABEL_509;
          if ( *(this + 2112) != nullptr )
            sub_4AECE0(2);
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) == 0 )
          {
LABEL_278:
            sub_5DBBD0("R_WZ_FROSTHEAD", 450);
            goto LABEL_509;
          }
          ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 16);
          v332 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 16);
          v160 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/LaunchFrostHead.ptl");
          v296 = (uint16_t)a3;
          v161 = v160;
          v291 = sub_47EF20(3, v332, -1, -1, 11);
          v162 = sub_47EF20(2, v332, -1, -1, 11);
          *(uint32_t *)(v161 + 85) = sub_423A80(v162, v291, v296, 1000);
          v163 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);
          v305 = 1;
          if ( v163 != 2 )
          {
            if ( ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1) == 3 )
            {
              v164 = sub_47E9D0(3);
LABEL_277:
              *(uint32_t *)(v161 + 31) = v164;
              ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                this,
                23009,
                v332,
                v161,
                0,
                42,
                0,
                100,
                4,
                0,
                2,
                &a3);
              goto LABEL_278;
            }
            v305 = 2;
          }
          v164 = sub_47E9D0(v305);
          goto LABEL_277;
        case 17:
          v165 = (int)*(this + 1952);
          if ( v165 != 0 )
          {
            if ( v165 == 1 )
            {
              if ( *(this + 2113) == nullptr )
              {
                v324 = sub_42FCB0(228);
                LOBYTE(v329) = 15;
                if ( v324 != 0 )
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )
                    v166 = (uint32_t *)sub_431920(
                                       (uint8_t)this + 108,
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",
                                       1);
                  else
                    v166 = (uint32_t *)sub_431920(
                                       (char)*(this + 91),
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",
                                       1);
                }
                else
                {
                  v166 = nullptr;
                }
                LOBYTE(v329) = 0;
                *(this + 2113) = v166;
              }
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
                this,
                1,
                *(this + 2113),
                44,
                -60,
                0,
                0);
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                *(float *)&v167 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 1954)));
                v168 = (int)*this;
                v323 = *(float *)&v167;
                v169 = (*(int (/*thiscall*/ **)(uint32_t **, uint32_t))(v168 + 1140))(this, *(this + 1954));
                v170 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(
                         this,
                         "Particle/LaunchFluorescent.ptl");
                v297 = (uint16_t)a3;
                v292 = sub_47EF20(3, v169, -1, -1, 11);
                v171 = sub_47EF20(2, v169, -1, -1, 11);
                *(uint32_t *)(v170 + 85) = sub_423A80(v171, v292, v297, 1000);
                *(float *)&v172 = COERCE_FLOAT(sub_47E9D0(1));
                a5 = v172;
                if ( v172 > 0 )
                {
                  v333 = 0;
                  a4 = v172;
                  do
                  {
                    *(uint32_t *)(v170 + 72) = v333 / a5;
                    ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                      this,
                      23010,
                      v169,
                      v170,
                      0,
                      0,
                      0,
                      60,
                      4,
                      0,
                      2,
                      &a3);
                    v94 = a4 == 1;
                    v333 += 360;
                    --a4;
                  }
                  while ( !v94 );
                }
              }
              sub_5DBBD0("R_WZ_FLUORE", 400);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_FLUORE_READY");
          }
          goto LABEL_509;
        case 18:
          v173 = (int)*(this + 1952);
          if ( v173 != 0 )
          {
            if ( v173 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                v176 = (int)*this;
                v177 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[285])(
                         this,
                         18,
                         0,
                         0,
                         44,
                         0,
                         60,
                         4,
                         0,
                         2,
                         &a3);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v176 + 580))(this, 23011, v177);
              }
              sub_5DBBD0("R_WZ_LAUNCH_PLUTO", 0);
            }
          }
          else
          {
            if ( *(this + 2114) == nullptr )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 16;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v174 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
                else
                  v174 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
              }
              else
              {
                v174 = nullptr;
              }
              *(this + 2114) = v174;
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 17;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v175 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
                else
                  v175 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
              }
              else
              {
                v175 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2115) = v175;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2114),
              0,
              0,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2115),
              0,
              0,
              0,
              0);
            sub_5DADE0("R_WZ_LAUNCH_PLUTO_READY");
          }
          goto LABEL_509;
        case 26:
          v178 = (int)*(this + 1952);
          if ( v178 != 0 )
          {
            if ( v178 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 26);
                v179 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 26);
                v180 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/Void.ptl");
                v298 = (uint16_t)a3;
                v324 = v180;
                v293 = sub_47EF20(3, v179, -1, -1, 11);
                v181 = sub_47EF20(2, v179, -1, -1, 11);
                v283 = v324;
                *(uint32_t *)(v324 + 85) = sub_423A80(v181, v293, v298, 1000) + 300;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                  this,
                  23012,
                  v179,
                  v283,
                  0,
                  38,
                  0,
                  62,
                  4,
                  0,
                  2,
                  &a3);
              }
              sub_5DBBD0("R_WZ_VOID", 500);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_VOID_READY");
          }
          goto LABEL_509;
        case 27:
          v182 = (int)*(this + 1952);
          if ( v182 != 0 )
          {
            if ( v182 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 27);
                a4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 27);
                v183 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/HalloweenBuster.ptl");
                v184 = sub_47E9D0(1);
                v185 = (int)*this;
                v334 = v184;
                v186 = v184 - *(uint32_t *)(v183 + 15);
                v324 = -*(uint32_t *)(v183 + 31);
                if ( (*(int (/*thiscall*/ **)(uint32_t **))(v185 + 152))(this) != 0 )
                  v187 = v334 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);
                else
                  v187 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v334;
                v335 = v187;
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )
                  LODWORD(v188) = v186 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);
                else
                  LODWORD(v188) = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v186;
                v189 = (int)*this;
                *(float *)&a5 = v188;
                v190 = (*(int (/*thiscall*/ **)(uint32_t **, int, int, int, int *))(v189 + 152))(this, 200, 4, 2, &a3);
                v191 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[31])(this, 23013, a4, v183, v190);
                v192 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[32])(this, v335, v191);
                v193 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v324 + v192);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v189 + 584))(this, a5, v193);
              }
              sub_5DBBD0("R_WZ_SHOOTING_STAR", 700);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_SHOOTING_STAR_READY");
          }
          goto LABEL_509;
        case 28:
          v194 = (int)*(this + 1952);
          if ( v194 != 0 )
          {
            if ( v194 == 1 )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 19;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(v199) = (uint8_t)this + 108;
                else
                  v199 = (int)*(this + 91);
                v200 = sub_431920(v199, (char)"Effect/Animation/DisenchantCast2.ani", 1);
              }
              else
              {
                v200 = 0;
              }
              v324 = sub_44B6C0(284);
              LOBYTE(v329) = 20;
              v201 = v324 != 0 ? (int *)sub_44E1F0(v200, 1) : nullptr;
              v202 = (int)*(this + 29);
              LOBYTE(v329) = 0;
              sub_45FE80(v202, (int)v201, 2, 0, (int)v201, (int)this, 0);
              v203 = *v201;
              v306 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
              (*(void (/*thiscall*/ **)(int *))(v203 + 148))(v201);
              v204 = *v201;
              v205 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
              v206 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v205);
              v207 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v206);
              (*(void (/*thiscall*/ **)(int *, int))(v204 + 112))(v201, v207);
              v208 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int))(*this)[290])(this, 28, 0, v208);
              v209 = (double)(int)sub_47EF20(28, -1, -1, 11, v306);
              v210 = 0;
              do
              {
                a5 = v210 + 1;
                sprintf(Buffer, "Effect/Animation/DisenchantArea%d.ani", v210 + 1);
                v324 = sub_42FCB0(228);
                LOBYTE(v329) = 21;
                if ( v324 != 0 )
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )
                    LOBYTE(v211) = (uint8_t)this + 108;
                  else
                    v211 = (int)*(this + 91);
                  v212 = sub_431920(v211, (char)Buffer, 1);
                }
                else
                {
                  v212 = 0;
                }
                LOBYTE(v329) = 0;
                v337 = v209 * 0.0018867925;
                sub_4922F0(v337);
                v324 = sub_44B6C0(284);
                LOBYTE(v329) = 22;
                if ( v324 != 0 )
                  v213 = (int *)sub_44E1F0(v212, 1);
                else
                  v213 = nullptr;
                v214 = *v213;
                LOBYTE(v329) = 0;
                *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v214 + 36))(v213) + 8) = 2;
                sub_45FE80((int)*(this + 29), (int)v213, 2, 0, (int)v213, 0, 0);
                v215 = *v213;
                v216 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
                (*(void (/*thiscall*/ **)(int *, int))(v215 + 148))(v213, v216);
                v217 = *v213;
                v218 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
                v219 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v218);
                v220 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v219);
                (*(void (/*thiscall*/ **)(int *, int))(v217 + 112))(v213, v220);
                v210 = a5;
              }
              while ( a5 < 4 );
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
                ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[145])(
                  this,
                  48015,
                  *(this + 1954),
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
          else
          {
            v195 = sub_42FC90(*(this + 30));
            sub_4AECE0(v195 - 1);
            if ( *(this + 2116) == nullptr )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 18;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v196 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/DisenchantCast1.ani", 1);
                else
                  v196 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/DisenchantCast1.ani", 1);
              }
              else
              {
                v196 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2116) = v196;
            }
            v197 = (int)*(this + 2116);
            v198 = 0;
            v336 = (int)*(this + 1664) * (int)*(this + 1955) / 1000 / sub_42FC90(v197);
            if ( sub_42FC90(v197) > 0 )
            {
              do
                *(uint32_t *)(sub_4924C0(v198++) + 48) = v336;
              while ( v198 < sub_42FC90(*(this + 2116)) );
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2116),
              0,
              0,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "WZ_DISENCHANT",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "DISENCHANT",
              -1,
              0,
              0);
          }
          goto LABEL_509;
        case 31:
          v221 = (int)*(this + 1952);
          if ( v221 != 0 )
          {
            if ( v221 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                v230 = (int)*this;
                v231 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t **, int, int *))(*this)[285])(
                         this,
                         31,
                         0,
                         0,
                         0,
                         0,
                         *(this + 40),
                         4,
                         this,
                         2,
                         &a3);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v230 + 580))(this, 23015, v231);
              }
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 26;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(v232) = (uint8_t)this + 108;
                else
                  v232 = (int)*(this + 91);
                v233 = sub_431920(v232, (char)"Effect/Animation/SunBurstFloor2.ani", 1);
              }
              else
              {
                v233 = 0;
              }
              v324 = sub_44B6C0(284);
              LOBYTE(v329) = 27;
              if ( v324 != 0 )
                v234 = (int *)sub_44E1F0(v233, 1);
              else
                v234 = nullptr;
              v235 = *v234;
              LOBYTE(v329) = 0;
              *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v235 + 36))(v234) + 8) = 2;
              sub_45FE80((int)*(this + 29), (int)v234, 2, 0, (int)v234, 0, 0);
              v236 = *v234;
              v237 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
              v238 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v237);
              v239 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v238);
              (*(void (/*thiscall*/ **)(int *, int))(v236 + 112))(v234, v239);
              v240 = *v234;
              v241 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
              (*(void (/*thiscall*/ **)(int *, int))(v240 + 148))(v234, v241);
              sub_5DBBD0("R_WZ_SUNBURST", 400);
            }
          }
          else
          {
            v222 = this + 2117;
            if ( *(this + 2117) == nullptr )
            {
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 23;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v223 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast1.ani", 1);
                else
                  v223 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast1.ani", 1);
              }
              else
              {
                v223 = 0;
              }
              *v222 = v223;
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 24;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v224 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast2.ani", 1);
                else
                  v224 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast2.ani", 1);
              }
              else
              {
                v224 = nullptr;
              }
              *(this + 2118) = v224;
              v324 = sub_42FCB0(228);
              LOBYTE(v329) = 25;
              if ( v324 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  v225 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstFloor1.ani", 1);
                else
                  v225 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstFloor1.ani", 1);
              }
              else
              {
                v225 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2119) = v225;
            }
            v226 = sub_42FC90(*v222);
            v227 = (uint32_t)*(this + 1664) * (uint32_t)*(this + 1955);
            v338 = this + 2117;
            a5 = 3;
            a4 = v227 / 1000 / v226;
            do
            {
              for ( jj = 0; jj < sub_42FC90(*v338); ++jj )
              {
                v229 = sub_4924C0(jj);
                *(uint32_t *)(v229 + 48) = a4;
              }
              v94 = a5 == 1;
              ++v338;
              --a5;
            }
            while ( !v94 );
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2117),
              0,
              -(int)*(this + 40),
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(
              this,
              2,
              *(this + 2118),
              0,
              -(int)*(this + 40),
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
              this,
              1,
              *(this + 2119),
              0,
              0,
              0,
              1);
            sub_5DADE0("R_WZ_SUNBURST_READY");
          }
          goto LABEL_509;
        case 43:
          if ( *(this + 1952) != (uint32_t *)1 )
            return;
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
          {
            v242 = (int)*this;
            v243 = ((int (/*thiscall*/ *)(uint32_t **, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[147])(
                     this,
                     "Particle/ProvocationDoll.ptl",
                     0,
                     50,
                     0,
                     33,
                     4,
                     0,
                     0,
                     0);
            v244 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 43, v243);
            (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v242 + 580))(this, 23017, v244);
          }
LABEL_447:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_FOLLOW_ME_03",
            -1,
            0,
            0);
          goto LABEL_509;
        default:
          break;
      }
      if ( v140 != 49 )
      {
        if ( v140 != 50 )
        {
          if ( (uint8_t)sub_5DA9B0(*(this + 1954)) != 0 )
          {
            v270 = (int)*(this + 1952);
            if ( v270 != 0 )
            {
              if ( v270 == 1 )
              {
                if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
                {
                  v307 = (int)*(this + 1954);
                  v271 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);
                  v272 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[290])(this, *(this + 1954), v271));
                  sub_5E09B0(v272, v307);
                }
                v273 = (int)*(this + 1954);
                switch ( v273 )
                {
                  case 21:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_ADOR",
                      -1,
                      0,
                      0);
                    break;
                  case 22:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_NIAS",
                      -1,
                      0,
                      0);
                    break;
                  case 23:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_STALKER",
                      -1,
                      0,
                      0);
                    break;
                  case 24:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_WISP",
                      -1,
                      0,
                      0);
                    break;
                  case 25:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "GBLN_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 44:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SANDOR_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 45:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "AUXO_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 46:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "LUIS_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 47:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "ECHEVERRA_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  default:
                    break;
                }
              }
            }
            else
            {
              switch ( v269 )
              {
                case 21:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_ADOR",
                    -1,
                    0,
                    0);
                  break;
                case 22:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_NIAS",
                    -1,
                    0,
                    0);
                  break;
                case 23:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_STALKER",
                    -1,
                    0,
                    0);
                  break;
                case 24:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_WISP",
                    -1,
                    0,
                    0);
                  break;
                case 25:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE",
                    -1,
                    0,
                    0);
                  break;
                case 44:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_SANDOR",
                    -1,
                    0,
                    0);
                  break;
                case 45:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_AUXO",
                    -1,
                    0,
                    0);
                  break;
                case 46:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_LUIS",
                    -1,
                    0,
                    0);
                  break;
                case 47:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_ECHEVERRA",
                    -1,
                    0,
                    0);
                  break;
                default:
                  break;
              }
            }
          }
          goto LABEL_509;
        }
        v265 = (int)*(this + 1952);
        if ( v265 != 0 )
        {
          if ( v265 == 1 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
          {
            v266 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/TargetItBall.ptl");
            v267 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[285])(this, 50, -1, -1, 11);
            ((void (/*thiscall*/ *)(uint32_t **, int, int, int))(*this)[290])(this, 50, 5, v267);
            v268 = sub_47EF20(v309, v310, v311, v312, v313);
            v313 = 0;
            v312 = 0;
            *(uint32_t *)(v266 + 85) = v268;
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, uint32_t, int, uint32_t))(*this)[145])(
              this,
              23018,
              0,
              v266,
              0,
              44,
              0);
          }
          goto LABEL_509;
        }
        goto LABEL_447;
      }
      v245 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 49);
      v246 = (int)*this;
      v324 = v245;
      *(float *)&a5 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t **, int))(v246 + 1140))(this, 49));
      v247 = (int)*(this + 1952);
      if ( v247 == 0 )
      {
        v248 = this + 2120;
        if ( *(this + 2120) == nullptr )
        {
          v322 = sub_42FCB0(228);
          LOBYTE(v329) = 28;
          if ( v322 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v249 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit1.ani", 1);
            else
              v249 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit1.ani", 1);
          }
          else
          {
            v249 = 0;
          }
          *v248 = v249;
          v322 = sub_42FCB0(228);
          LOBYTE(v329) = 29;
          if ( v322 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v250 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
            else
              v250 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
          }
          else
          {
            v250 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2121) = v250;
        }
        v339 = 2;
        v251 = (double)(int)sub_47EF20(0, a5, -1, -1, 11) * 0.0071428572;
        *(float *)&a5 = v251 / *((float *)this + 2122);
        *((float *)this + 2122) = v251;
        do
        {
          sub_4922F0(*(float *)&a5);
          a4 = (int)*this;
          v252 = sub_47E9D0(0);
          (*(void (/*thiscall*/ **)(uint32_t **, int, uint32_t, int, uint32_t, uint32_t, int))(a4 + 204))(
            this,
            1,
            *v248++,
            v252,
            0,
            0,
            1);
          --v339;
        }
        while ( v339 != 0 );
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "R_WZ_SACRIFICE_SPIRIT",
          -1,
          0,
          0);
        goto LABEL_509;
      }
      if ( v247 != 1 )
        goto LABEL_509;
      v253 = sub_47EF20(0, a5, -1, -1, 11);
      v254 = (int)*this;
      LODWORD(v323) = v253 / 2;
      if ( (*(int (/*thiscall*/ **)(uint32_t **))(v254 + 152))(this) == 1 )
      {
        v255 = sub_47E9D0(0);
        a4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v255;
      }
      else
      {
        v256 = sub_47E9D0(0);
        a4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v256;
      }
      v324 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
      v313 = 0;
      v314 = 0;
      v315 = 0;
      v317 = 0;
      v318 = 0;
      v319 = 0;
      v257 = (int)*(this + 29);
      LOBYTE(v329) = 31;
      v340 = 0;
      if ( sub_425100(v257) > 0 )
      {
        do
        {
          v258 = (uint32_t *)sub_425A00(v340);
          v259 = *v258;
          v322 = (int)v258;
          v299 = (*(int (/*thiscall*/ **)(uint32_t *))(v259 + 124))(v258);
          v260 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 120))(v258);
          v261 = sub_499240(a4, v324, v260, v299, 0);
          if ( v261 <= SLODWORD(v323) )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 529) == 0 )
              goto LABEL_437;
            v262 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 340))(v258);
            v263 = &dword_738020;
            while ( v262 != *v263 )
            {
              if ( (int)++v263 >= (int)&dword_738030 )
                goto LABEL_437;
            }
            if ( (uint32_t **)v258[2088] == this )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v258 + 308))(v258) == 0 )
                goto LABEL_440;
            }
            else
            {
LABEL_437:
              v264 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 376))(v258);
              if ( v264 != ((int (/*thiscall*/ *)(uint32_t **))(*this)[94])(this)
                || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 17) == 0 )
              {
                goto LABEL_440;
              }
            }
            sub_428430(&v322);
          }
LABEL_440:
          ++v340;
        }
        while ( v340 < sub_425100(*(this + 29)) );
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
        this,
        "SPIRIT_SACRIFICE",
        -1,
        0,
        0);
      sub_5E5260(v316);
      LOBYTE(v329) = 0;
      sub_5E5260(&v312);
LABEL_509:
      if ( *(this + 1952) == (uint32_t *)1 && *((uint8_t *)this + 8584) != 0 && *((uint8_t *)this + 8585) != 0 )
      {
        v287 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          v287,
          v287,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v278 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v278 = sub_432E50(v278);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v278, 4);
        sub_495890(2, 0);
        v308 = (float)SLODWORD(v321);
        sub_494F20(2, v308);
      }
      return;
    case 11:
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "DASH_LOOP", 9, 0, 0);
LABEL_156:
      if ( *(this + 2142) != (uint32_t *)-1 )
        sub_5DACE0(this);
      return;
    case 12:
      v121 = (int)*this;
      *((uint8_t *)this + 8228) = 0;
      *((uint8_t *)this + 8220) = 0;
      v122 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v121 + 1172))(this, 1);
      sub_406D60(v122);
      return;
    case 14:
      v279 = (int)*(this + 1991);
      switch ( v279 )
      {
        case 176:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ANCIENT_MEMORY", -1, 0, 0);
          break;
        case 175:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_LEAP", -1, 0, 0);
          break;
        case 180:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_UNYIELD_WILL", -1, 0, 0);
          break;
        case 30:
          v280 = *(uint32_t *)(*(uint32_t *)(v117 + 4) + 4);
          *((uint8_t *)this + 8368) = v280 == 0;
          *((uint8_t *)this + 8376) = 0;
          if ( v280 != 0 )
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "R_WZ_FOLLOW_ME",
              -1,
              0,
              0);
          break;
        case 29:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ELEMENTAL_BURN", -1, 0, 0);
          break;
        case 41:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_ANCIENT_LIBRARY",
            -1,
            0,
            0);
          break;
        case 37:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_SHIELD", -1, 0, 0);
          break;
        case 2:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_SHOWTIME",
            -1,
            0,
            0);
          break;
        case 40:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_AUTO_CHASER", -1, 0, 0);
          break;
        default:
          break;
      }
      return;
    default:
      return;
  }
}

