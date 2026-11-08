// ============================================================
// 【40JP逆向源代码工程】src/game/bigfunc_4C9950_sub_4C9950.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x4C9950）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 3649 行；字符串证据 5 条；外调 6 个
//   串: "SUBWEAPON_IN"
//   串: "R_GN_SLIDING"
//   串: "Character/Gunner/Effect/Animation/WindmillDu"
//   串: "R_GN_WINDMILL"
//   串: "WINDMILL_SWING"
//   调: sub_4C9950 sub_699000 sub_4238E0 sub_431230 sub_5E5260 sub_49C620
//   case 分支地图（共 5 处）:
//     L1848  case 0xC:
//     L1852  case 0xD:
//     L1853  case 0x24:
//     L1854  case 0x27:
//     L1862  case 0x28:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4C9950 sub_4C9950  size=19214
// ------------------------------------------------------------
void /*thiscall*/ sub_4C9950(int *this, int a2, int a3, int a4, int a5)
{
  int v6; // ebx
  int v7; // ebx
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // edi
  int v17; // ecx
  int v18; // eax
  uint32_t *v19; // edi
  int i; // ebx
  int v21; // edx
  int v22; // eax
  void **v23; // eax
  uint32_t *v24; // edi
  int j; // ebx
  int v26; // ecx
  int v27; // eax
  int v28; // ecx
  int v29; // eax
  int v30; // ecx
  int v31; // ecx
  uint32_t *v32; // edi
  int k; // ebx
  int v34; // edx
  int v35; // eax
  uint32_t *v36; // edi
  int m; // ebx
  uint32_t *v38; // edi
  int v39; // eax
  uint32_t *v40; // edi
  int n; // ebx
  uint32_t *v42; // edi
  int ii; // ebx
  uint32_t *v44; // edi
  int jj; // ebx
  int v46; // eax
  uint32_t *v47; // edi
  int kk; // ebx
  int v49; // edx
  int v50; // edi
  int v51; // eax
  int v52; // eax
  int v53; // edi
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // edi
  int v58; // ecx
  int v59; // edi
  int *v60; // edi
  int v61; // ecx
  int v62; // ebx
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // ebx
  int v67; // eax
  int v68; // eax
  int v69; // edi
  int v70; // eax
  int v71; // eax
  int v72; // ebx
  int v73; // edi
  int v74; // eax
  int v75; // eax
  int v76; // edi
  long double v77; // st7
  uint64_t v78; // rax
  int v79; // ecx
  int v80; // eax
  char *v81; // ebx
  int v82; // edi
  int v83; // eax
  void *v84; // eax
  int v85; // edi
  int v86; // eax
  int v87; // edx
  int v88; // ebx
  void *v89; // eax
  int v90; // ebx
  void *v91; // edi
  int v92; // eax
  int v93; // edi
  int v94; // eax
  int v95; // eax
  void *v96; // edx
  int v97; // edi
  int v98; // ecx
  int v99; // ebx
  int v100; // ebx
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // eax
  bool v105; // al
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int v109; // ecx
  int v110; // eax
  int v111; // ecx
  int v112; // eax
  int v113; // edi
  int v114; // eax
  char *v115; // edi
  int v116; // ebx
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // edi
  int v121; // edx
  int v122; // eax
  int v123; // eax
  int v124; // eax
  int v125; // eax
  int v126; // ecx
  int v127; // eax
  int v128; // ecx
  int v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // edx
  int v133; // edi
  int v134; // eax
  int v135; // eax
  int v136; // edi
  int v137; // edi
  int v138; // ecx
  int v139; // ebx
  int v140; // ebx
  int v141; // eax
  int v142; // eax
  int v143; // eax
  uint32_t *v144; // edi
  int v145; // edi
  int v146; // eax
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int v150; // edi
  bool v151; // bl
  int v152; // eax
  int v153; // ecx
  void *v154; // edi
  void **v155; // ecx
  int v156; // eax
  int v157; // ebx
  int v158; // ecx
  int v159; // edi
  int v160; // eax
  int v161; // eax
  void **v162; // ecx
  int v163; // eax
  int v164; // edi
  int v165; // ecx
  int v166; // ebx
  int v167; // eax
  char *v168; // ebx
  int v169; // edi
  int v170; // eax
  int v171; // eax
  void *v172; // eax
  int v173; // edi
  int v174; // eax
  int v175; // eax
  int v176; // eax
  int v177; // ebx
  int v178; // eax
  int v179; // edx
  int v180; // eax
  void **v181; // eax
  int v182; // edx
  int v183; // edi
  int v184; // ebx
  int v185; // ecx
  int v186; // eax
  const char *v187; // edx
  int v188; // eax
  int v189; // eax
  const char *v190; // ecx
  int v191; // eax
  int mm; // edi
  int v193; // ecx
  int v194; // eax
  int *v195; // ebx
  int *v196; // eax
  int v197; // edi
  int v198; // eax
  int v199; // eax
  void *v200; // eax
  void *v201; // ecx
  int v202; // ebx
  int v203; // edi
  int v204; // eax
  int v205; // edi
  int v206; // eax
  bool v207; // zf
  int *v208; // eax
  int v209; // ecx
  int v210; // edx
  int v211; // eax
  int v212; // eax
  int v213; // edi
  int v214; // ebx
  int v215; // ebx
  int v216; // ecx
  int v217; // ebx
  int v218; // ebx
  int v219; // ecx
  int v220; // edx
  uint32_t *v221; // edi
  int v222; // ecx
  int v223; // ebx
  int v224; // ebx
  int v225; // ecx
  uint64_t v226; // rax
  int v227; // eax
  int v228; // eax
  int v229; // edx
  int v230; // eax
  int v231; // eax
  int v232; // eax
  int v233; // ebx
  int v234; // eax
  int v235; // eax
  char v236; // al
  int v237; // eax
  int v238; // eax
  bool v239; // al
  int v240; // eax
  char v241; // al
  int v242; // eax
  char v243; // al
  int v244; // eax
  char v245; // al
  int v246; // eax
  char v247; // al
  int v248; // eax
  char v249; // al
  int v250; // eax
  char v251; // al
  int v252; // eax
  int v253; // ebx
  char v254; // al
  int v255; // eax
  char v256; // al
  int v257; // eax
  char v258; // al
  int v259; // eax
  int v260; // edi
  int v261; // eax
  int v262; // eax
  bool v263; // al
  int v264; // eax
  int v265; // eax
  int v266; // eax
  int v267; // eax
  char v268; // al
  int v269; // eax
  int v270; // eax
  int v271; // eax
  void *v272; // ecx
  char v273; // al
  int v274; // eax
  char v275; // al
  int v276; // eax
  int v277; // eax
  int v278; // eax
  int v279; // ecx
  int v280; // eax
  int v281; // eax
  int v282; // eax
  char v283; // al
  int v284; // eax
  int v285; // ecx
  char *v286; // eax
  int v287; // ebx
  int v288; // eax
  int v289; // eax
  int v290; // eax
  int v291; // eax
  void *v292; // ecx
  int nn; // edi
  int v294; // eax
  int i1; // ebx
  uint32_t *v296; // eax
  int v297; // ecx
  char *v298; // edx
  int v299; // edx
  double v300; // st7
  int v301; // eax
  int v302; // eax
  int v303; // eax
  int v304; // eax
  int v305; // ebx
  int v306; // ebx
  void *v307; // eax
  int v308; // edx
  double v309; // st7
  int v310; // eax
  int v311; // edx
  int v312; // eax
  int v313; // eax
  void **v314; // eax
  int v315; // edi
  int v316; // edi
  int v317; // ebx
  int v318; // edx
  int v319; // eax
  int v320; // eax
  int v321; // ebx
  int v322; // eax
  int v323; // edx
  int v324; // eax
  int v325; // ebx
  int v326; // edi
  int v327; // edx
  int v328; // ecx
  int v329; // eax
  int v330; // ebx
  int v331; // eax
  unsigned int v332; // edi
  int v333; // edx
  int v334; // eax
  int v335; // eax
  int v336; // eax
  int v337; // ebx
  int v338; // eax
  int v339; // eax
  int v340; // eax
  int v341; // edx
  unsigned int v342; // ecx
  int v343; // eax
  int v344; // edx
  unsigned int v345; // ecx
  int v346; // eax
  int v347; // edx
  unsigned int v348; // ecx
  int v349; // edx
  int v350; // edx
  int *v351; // eax
  int v352; // eax
  int v353; // eax
  int v354; // eax
  int v355; // edx
  int v356; // ebx
  int v357; // eax
  int v358; // ebx
  int v359; // edx
  int v360; // eax
  void **v361; // eax
  int v362; // eax
  int v363; // edx
  int v364; // edi
  int v365; // eax
  int v366; // eax
  int v367; // edx
  int v368; // edi
  int *v369; // edi
  int v370; // ecx
  int v371; // ebx
  int v372; // eax
  int v373; // ebx
  int v374; // eax
  int v375; // eax
  int v376; // eax
  int v377; // ecx
  int v378; // edi
  int *v379; // edi
  int v380; // ecx
  int v381; // ebx
  int v382; // eax
  int v383; // ebx
  int v384; // eax
  int v385; // eax
  int v386; // eax
  int v387; // eax
  char v388; // al
  int v389; // eax
  int v390; // edi
  char v391; // al
  int v392; // eax
  int v393; // eax
  int v394; // edi
  int v395; // eax
  int v396; // eax
  int v397; // eax
  int v398; // eax
  uint64_t v399; // rax
  char v400; // al
  int v401; // edi
  int *v402; // edi
  int v403; // ecx
  int v404; // ebx
  int v405; // ebx
  int v406; // eax
  int v407; // eax
  int v408; // eax
  int v409; // eax
  uint64_t v410; // rax
  int v411; // edi
  int v412; // eax
  int v413; // eax
  int v414; // edi
  int v415; // eax
  int v416; // eax
  char v417; // al
  int v418; // eax
  int v419; // eax
  int v420; // eax
  int v421; // eax
  int v422; // eax
  void **v423; // eax
  int v424; // eax
  int v425; // edi
  int v426; // eax
  int v427; // edx
  int v428; // eax
  void **v429; // eax
  int v430; // eax
  int v431; // edi
  int v432; // eax
  int v433; // eax
  int v434; // edx
  int v435; // edi
  int v436; // eax
  int v437; // edx
  int v438; // edi
  int v439; // eax
  int v440; // eax
  int v441; // eax
  int v442; // ecx
  int v443; // edi
  int v444; // ebx
  int v445; // eax
  int v446; // edi
  int v447; // eax
  int v448; // eax
  int v449; // ecx
  int v450; // ecx
  int v451; // edi
  int v452; // eax
  int v453; // ebx
  int v454; // eax
  int v455; // eax
  int v456; // eax
  double v457; // st7
  int v458; // eax
  char v459; // al
  int v460; // ebx
  int *v461; // ebx
  int v462; // edx
  int v463; // edi
  int v464; // eax
  int v465; // edi
  int v466; // eax
  int v467; // eax
  int v468; // eax
  int v469; // eax
  unsigned int v470; // [esp-14h] [ebp-180h]
  int v471; // [esp-10h] [ebp-17Ch]
  int v472; // [esp-10h] [ebp-17Ch]
  int v473; // [esp-Ch] [ebp-178h]
  int v474; // [esp-Ch] [ebp-178h]
  int v475; // [esp-8h] [ebp-174h]
  int v476; // [esp-8h] [ebp-174h]
  int v477; // [esp-8h] [ebp-174h]
  int v478; // [esp-4h] [ebp-170h]
  int v479; // [esp-4h] [ebp-170h]
  int v480; // [esp-4h] [ebp-170h]
  int v481; // [esp-4h] [ebp-170h]
  int v482; // [esp-4h] [ebp-170h]
  int v483; // [esp-4h] [ebp-170h]
  int v484; // [esp-4h] [ebp-170h]
  int v485; // [esp+0h] [ebp-16Ch]
  int v486; // [esp+0h] [ebp-16Ch]
  int v487; // [esp+Ch] [ebp-160h]
  int v488; // [esp+10h] [ebp-15Ch] BYREF
  float v489; // [esp+14h] [ebp-158h]
  int v490; // [esp+18h] [ebp-154h] BYREF
  int v491; // [esp+1Ch] [ebp-150h] BYREF
  void *v492; // [esp+20h] [ebp-14Ch] BYREF
  char Buffer[256]; // [esp+24h] [ebp-148h] BYREF
  char v494[4]; // [esp+124h] [ebp-48h] BYREF
  void *v495[2]; // [esp+128h] [ebp-44h] BYREF
  void *v496[2]; // [esp+130h] [ebp-3Ch] BYREF
  int v497; // [esp+138h] [ebp-34h]
  unsigned int v498; // [esp+13Ch] [ebp-30h]
  char v499[4]; // [esp+140h] [ebp-2Ch] BYREF
  void *Block[2]; // [esp+144h] [ebp-28h] BYREF
  float v501; // [esp+14Ch] [ebp-20h] BYREF
  float v502; // [esp+150h] [ebp-1Ch]
  int v503; // [esp+154h] [ebp-18h]
  unsigned int v504; // [esp+158h] [ebp-14h]
  int v505; // [esp+15Ch] [ebp-10h]
  int v506; // [esp+168h] [ebp-4h]
  float v507; // [esp+174h] [ebp+8h]
  float v508; // [esp+180h] [ebp+14h]
  float v509; // [esp+180h] [ebp+14h]
  int v510; // [esp+180h] [ebp+14h]

  v505 = dword_796E50;
  v487 = *(this + 1639);
  if ( *(float *)&a2 == 0.0 || a2 == 11 || a2 == 6 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 && *((uint8_t *)this + 9500) != 0 )
    {
      v6 = *(this + 2378);
      if ( sub_699000((int)(this + 2372)) < v6 )
      {
        v7 = *this;
        v8 = sub_4238E0(this + 2372);
        (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 944))(this, 1, v8);
      }
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*this + 944))(this, 0, -1);
  }
  v9 = v487;
  if ( v487 == 16 )
  {
    if ( *((uint8_t *)this + 8692) == 0 )
    {
LABEL_12:
      v10 = a2;
      goto LABEL_13;
    }
  }
  else if ( v487 != 22 || *(this + 2129) != 14 )
  {
    goto LABEL_12;
  }
  v10 = a2;
  if ( a2 != 22 )
  {
    v11 = *(this + 2336);
    if ( v11 != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 308))(v11) != 0 )
      {
        v12 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 120))(*(this + 2336));
        v13 = *(this + 2336);
        v490 = v12;
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
        v15 = *(this + 2336);
        v491 = v14;
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 128))(v15);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2336) + 136))(
               *(this + 2336),
               v490,
               v491,
               0) != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2336) + 132))(*(this + 2336), v16) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(
            *(this + 2336),
            v490,
            v491,
            v16);
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2336) + 140))(
                    *(this + 2336),
                    &v490,
                    &v491,
                    v490,
                    v491,
                    100,
                    1,
                    1) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(
            *(this + 2336),
            v490,
            v491,
            v16);
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2336) + 108))(
            *(this + 2336),
            *(this + 2337),
            *(this + 2338),
            *(this + 2339));
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 724))(*(this + 2336)) == 0 )
        {
          v502 = 0.0;
          v503 = 0;
          *(float *)&v504 = 0.0;
          v506 = 0;
          v492 = (void *)4;
          sub_431230((int)&v501, &v492);
          v492 = nullptr;
          sub_431230((int)&v501, &v492);
          v492 = nullptr;
          sub_431230((int)&v501, &v492);
          v492 = (void *)100;
          sub_431230((int)&v501, &v492);
          v492 = (void *)10;
          sub_431230((int)&v501, &v492);
          (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 2336) + 560))(
            *(this + 2336),
            4,
            &v501,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 564))(*(this + 2336));
          v506 = -1;
          sub_5E5260((void **)&v501);
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2336) + 596))(*(this + 2336), 1);
      v17 = *(this + 2340);
      *(this + 2336) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v17 + 76))(v17, 0);
      v9 = v487;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
    v10 = a2;
  }
LABEL_13:
  switch ( v9 )
  {
    case 8:
      v18 = *(this + 2129);
      switch ( v18 )
      {
        case 11:
          v19 = this + 2150;
          for ( i = 2; i != 0; --i )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v19++);
          goto LABEL_43;
        case 5:
          if ( *((uint8_t *)this + 8608) == 0 )
            goto LABEL_44;
          if ( v10 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2153));
LABEL_43:
            v10 = a2;
LABEL_44:
            if ( v10 != 8 )
              *(this + 2129) = -1;
          }
          break;
        case 26:
          if ( v10 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
            sub_49C620(3, 1, 0);
            sub_49C5F0(3, 0, 0, 500);
            goto LABEL_43;
          }
          break;
        case 53:
          if ( v10 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
            goto LABEL_43;
          }
          break;
        default:
          goto LABEL_44;
      }
      if ( v10 != 0 )
        goto LABEL_108;
      v498 = 15;
      v497 = 0;
      LOBYTE(v495[0]) = 0;
      v21 = *this;
      v506 = 1;
      v22 = (*(int (/*thiscall*/ **)(int *))(v21 + 1096))(this);
      sub_4C2020((int)v494, v22);
      v23 = (void **)v495[0];
      if ( v498 < 0x10 )
        v23 = v495;
      goto LABEL_70;
    case 15:
      v24 = this + 2170;
      for ( j = 2; j != 0; --j )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v24++);
      goto LABEL_108;
    case 17:
      (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
      goto LABEL_108;
    case 18:
      if ( v10 == 18 )
        goto LABEL_108;
      v26 = *(this + 2175);
      if ( v26 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v26 + 308))(v26) != 0 )
        {
          if ( (v27 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 120))(*(this + 2175)),
                v28 = *(this + 2175),
                v491 = v27,
                v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v28 + 124))(v28),
                v30 = *(this + 2175),
                v490 = v29,
                (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v30 + 136))(v30, v491, v29, 0) != 0)
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2175) + 132))(*(this + 2175), 0) != 0
            || (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2175)
                                                                                                + 140))(
                 *(this + 2175),
                 &v491,
                 &v490,
                 v491,
                 v490,
                 100,
                 1,
                 1) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2175) + 108))(
              *(this + 2175),
              v491,
              v490,
              0);
          }
          else
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2175) + 108))(
              *(this + 2175),
              *(this + 2176),
              *(this + 2177),
              *(this + 2178));
          }
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 724))(*(this + 2175)) == 0 )
          {
            v502 = 0.0;
            v503 = 0;
            *(float *)&v504 = 0.0;
            v506 = 2;
            v492 = (void *)4;
            sub_431230((int)&v501, &v492);
            v492 = (void *)2;
            sub_431230((int)&v501, &v492);
            v492 = (void *)1;
            sub_431230((int)&v501, &v492);
            v492 = nullptr;
            sub_431230((int)&v501, &v492);
            v492 = nullptr;
            sub_431230((int)&v501, &v492);
            (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 2175) + 560))(
              *(this + 2175),
              4,
              &v501,
              2,
              0);
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 564))(*(this + 2175));
            v506 = -1;
            sub_5E5260((void **)&v501);
          }
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2175) + 596))(*(this + 2175), 1);
        v31 = *(this + 2179);
        *(this + 2175) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v31 + 76))(v31, 0);
      }
      *(this + 2129) = -1;
      v32 = this + 2180;
      for ( k = 2; k != 0; --k )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v32++);
      if ( *(float *)&a2 != 0.0 )
        goto LABEL_108;
      v498 = 15;
      v497 = 0;
      LOBYTE(v495[0]) = 0;
      v34 = *this;
      v506 = 3;
      v35 = (*(int (/*thiscall*/ **)(int *))(v34 + 1096))(this);
      sub_4C2020((int)v494, v35);
      v23 = (void **)v495[0];
      if ( v498 < 0x10 )
        v23 = v495;
LABEL_70:
      (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v23, -1, 0, 0);
      v506 = -1;
      sub_501490(v494);
      break;
    case 20:
      if ( v10 != 20 )
      {
        *(this + 2129) = -1;
        v36 = this + 2188;
        for ( m = 2; m != 0; --m )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v36++);
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);
      }
      goto LABEL_108;
    case 22:
      v38 = this + 2323;
      v491 = 2;
      do
      {
        if ( *v38 != 0 )
        {
          sub_492980(*v38);
          *v38 = 0;
        }
        ++v38;
        --v491;
      }
      while ( *(float *)&v491 != 0.0 );
      v39 = *(this + 2129);
      switch ( v39 )
      {
        case 12:
          v40 = this + 2333;
          for ( n = 3; n != 0; --n )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v40++);
          break;
        case 14:
          if ( a2 == 22 )
            goto LABEL_96;
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2341));
          break;
        case 13:
        case 36:
          if ( a2 == 22 )
            goto LABEL_96;
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 12);
          break;
        case 39:
          sub_492980(*(this + 2343));
          sub_492980(*(this + 2344));
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2349));
          v42 = this + 2352;
          for ( ii = 2; ii != 0; --ii )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(v42 - 5));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v42);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(v42 - 2));
            ++v42;
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 13);
          break;
        default:
          break;
      }
      if ( a2 != 22 )
        *(this + 2129) = -1;
LABEL_96:
      if ( *(float *)&a2 == 0.0 )
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SUBWEAPON_IN", -1, 0, 0);
      if ( *(this + 2242) == 0 )
        (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
LABEL_108:
      if ( a2 == 24 )
      {
        a2 = 8;
        v487 = 24;
      }
      break;
    case 23:
      if ( v10 != 23 )
      {
        v49 = *this;
        *(this + 2129) = -1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v49 + 308))(this) != 0 )
        {
          v50 = *this;
          v51 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 15);
          (*(void (/*thiscall*/ **)(int *, int, int))(v50 + 1296))(this, 15, v51);
        }
      }
      goto LABEL_108;
    case 25:
      (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
      if ( *(float *)&a2 != 0.0 )
        *(this + 2371) = -1;
      goto LABEL_108;
    case 26:
      v44 = this + 2323;
      for ( jj = 2; jj != 0; --jj )
      {
        if ( *v44 != 0 )
        {
          sub_492980(*v44);
          *v44 = 0;
        }
        ++v44;
      }
      v46 = *(this + 2129);
      if ( v46 == 39 )
      {
        v47 = this + 2345;
        for ( kk = 2; kk != 0; --kk )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v47++);
      }
      else if ( v46 == 40 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2358));
      }
      goto LABEL_107;
    case 27:
LABEL_107:
      *(this + 2129) = -1;
      goto LABEL_108;
    default:
      goto LABEL_108;
  }
  switch ( a2 )
  {
    case 12:
      v76 = sub_491C70(*(this + 1813), *(this + 1982));
      v77 = *(float *)(*(this + 28) + 16) * 4.0999999;
      if ( (int)(uint64_t)fabs(v77) <= 200 )
        LODWORD(v78) = 200;
      else
        v78 = (uint64_t)fabs(v77);
      *(this + 2158) = v78;
      v79 = *(this + 30);
      HIDWORD(v78) = *this;
      *(this + 2159) = -1000 * (int)v78 / v76;
      *(this + 2160) = *(uint32_t *)(v79 + 148);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(HIDWORD(v78) + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      v80 = *this;
      *(this + 2161) = -400;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v80 + 212))(this, "R_GN_SLIDING", -1, 0, 0);
      goto LABEL_482;
    case 15:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 28));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
      if ( **(uint32_t **)(a3 + 4) == 3 )
      {
        v81 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 3);
        v82 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 3);
        v83 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        v492 = (void *)sub_47EFD0(v81, 0.0, v82, v83, v83, 0);
        *((float *)this + 97) = (float)(int)v492;
        *(this + 2168) = sub_47EF20(1, v82, -1, -1, 11);
        v84 = (void *)sub_47EF20(2, v82, -1, -1, 11);
        v85 = *this;
        v492 = v84;
        v489 = (double)(int)v84 * 0.0099999998 + 1.0;
        v492 = (void *)(*(int (/*thiscall*/ **)(int *, int))(v85 + 900))(this, 3);
        (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, int, uint32_t))(v85 + 888))(
          this,
          (uint64_t)((double)(int)v492 * v489) >> 32,
          1,
          0,
          1000,
          (uint64_t)((double)(int)v492 * v489));
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        v86 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 35);
        v87 = *this;
        if ( v86 <= 0 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v87 + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int))(v87 + 1160))(this, 35);
          v88 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 35);
          *(float *)&v491 = COERCE_FLOAT(sub_47EF20(0, v88, -1, -1, 11));
          v89 = (void *)sub_47EF20(1, v88, -1, -1, 11);
          v90 = *this;
          v91 = v89;
          v492 = v89;
          (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(v90 + 876))(
            this,
            (uint64_t)((double)v491 * 0.82999998) >> 32,
            0,
            v491,
            (uint64_t)((double)v491 * 0.82999998),
            1,
            0,
            0);
          (*(void (/*fastcall*/ **)(int *, uint32_t, int, void *, uint32_t, int, uint32_t, uint32_t))(*this + 876))(
            this,
            (uint64_t)((double)(int)v492 * 0.82999998) >> 32,
            1,
            v91,
            (uint64_t)((double)(int)v492 * 0.82999998),
            1,
            0,
            0);
        }
      }
      v92 = *(this + 2170);
      v93 = 0;
      *(this + 2167) = 0;
      *((uint8_t *)this + 8676) = 0;
      if ( v92 == 0 )
      {
        v492 = (void *)sub_42FCB0(228);
        v506 = 9;
        if ( v492 != nullptr )
          v94 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust1.ani", 1);
        else
          v94 = 0;
        v506 = -1;
        *(this + 2170) = v94;
        v492 = (void *)sub_42FCB0(228);
        v506 = 10;
        if ( v492 != nullptr )
        {
          v95 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust2.ani", 1);
          v506 = -1;
          *(this + 2171) = v95;
        }
        else
        {
          v506 = -1;
          *(this + 2171) = 0;
        }
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        1,
        *(this + 2170),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -1,
        *(this + 2171),
        0,
        0,
        0,
        0);
      if ( *(this + 2168) == 1 )
      {
        v492 = (void *)sub_42FCB0(228);
        v506 = 11;
        if ( v492 != nullptr )
          v93 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust3.ani", 1);
        v96 = *(void **)(*(this + 30) + 164);
        v506 = -1;
        v492 = v96;
        sub_493D00(v93, *(float *)&v96);
        v492 = (void *)sub_44B6C0(284);
        v506 = 12;
        if ( v492 != nullptr )
          v97 = sub_44E1F0(v93, 1);
        else
          v97 = 0;
        v98 = *(this + 29);
        v506 = -1;
        sub_45FE80(v98, v97, 2, 0, v97, (int)this, 0);
        v99 = *(uint32_t *)v97;
        v478 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        (*(void (/*thiscall*/ **)(int))(v99 + 148))(v97);
        v100 = *(uint32_t *)v97;
        v101 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v102 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v101);
        v103 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v102);
        (*(void (/*thiscall*/ **)(int, int))(v100 + 112))(v97, v103);
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)v97 + 60))(v97, this);
        sub_4A06D0(v478);
      }
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_WINDMILL", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WINDMILL_SWING", -1, 0, 0);
      goto LABEL_482;
    case 16:
      v104 = **(uint32_t **)(a3 + 4);
      *(this + 2172) = v104;
      v105 = v104 == 14 && v487 == 16;
      *((uint8_t *)this + 8692) = v105;
      if ( v105 )
      {
        v106 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(a3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8));
        v107 = __RTDynamicCast(v106, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(this + 2336) = v107;
        if ( v107 != 0 )
        {
          v108 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v107 + 120))(v107);
          v109 = *(this + 2336);
          *(this + 2337) = v108;
          v110 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v109 + 124))(v109);
          v111 = *(this + 2336);
          *(this + 2338) = v110;
          *(this + 2339) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v111 + 128))(v111);
          if ( *(this + 2340) == 0 )
          {
            v492 = operator new(0x8Cu);
            v506 = 13;
            if ( v492 != nullptr )
              v112 = sub_4C12C0(this);
            else
              v112 = 0;
            v506 = -1;
            *(this + 2340) = v112;
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2340) + 56))(
            *(this + 2340),
            *(this + 2336),
            this,
            0,
            0,
            0,
            -1);
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 36));
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      v113 = *this;
      v114 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int *, int))(v113 + 896))(this, v114);
      if ( *((uint8_t *)this + 8692) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
        sub_4AECE0((void *)*(this + 30), 2);
        LOBYTE(a5) = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        *((uint8_t *)this + 8694) = 1;
      }
      else
      {
        v115 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 4);
        v116 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 4);
        v117 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        v492 = (void *)sub_47EFD0(v115, 0.0, v116, v117, v117, 0);
        *((float *)this + 97) = (float)(int)v492;
        v492 = (void *)sub_47EF20(1, v116, -1, -1, 11);
        v118 = *this;
        v489 = (double)(int)v492 * 0.0099999998 + 1.0;
        v492 = (void *)(*(int (/*thiscall*/ **)(int *, int))(v118 + 900))(this, 3);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(
          this,
          0,
          0,
          (uint64_t)((double)(int)v492 * v489),
          (uint64_t)((double)(int)v492 * v489));
        *(this + 114) = sub_47EF20(2, v116, -1, -1, 11);
        v119 = *(this + 2172);
        if ( v119 == 4 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "R_GN_JACKSPIKE",
            -1,
            0,
            0);
        }
        else if ( v119 == 14 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_BBQ", -1, 0, 0);
        }
        *((uint8_t *)this + 8694) = 0;
      }
      *((uint8_t *)this + 8693) = *(this + 2172) == 4
                             && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
                             && (v120 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1132))(this, 0)) == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      goto LABEL_482;
    case 17:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 3, 1000, 1000);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 304);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_PUNISHER", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "PUNISHER_SWING", -1, 0, 0);
      goto LABEL_482;
    case 18:
      v121 = *this;
      *(this + 2174) = **(uint32_t **)(a3 + 4);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v121 + 196))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      v122 = *(this + 2174);
      if ( v122 != 0 )
      {
        if ( v122 == 1 )
        {
          if ( sub_41A5E0((unsigned int)this + 8290) > 3 )
          {
            v133 = sub_41A5E0((unsigned int)this + 8290);
            v134 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v135 = sub_495500(v134);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, v133 * v135 / 3);
          }
          sub_4AECE0((void *)*(this + 30), 9);
          LOBYTE(a5) = 0;
          sub_4450B0(1);
          v136 = sub_4C46B0(this, 3);
          if ( v136 != 0 )
          {
            v492 = *(void **)(*(this + 30) + 164);
            sub_493D00(v136, *(float *)&v492);
            v492 = (void *)sub_44B6C0(284);
            v506 = 17;
            if ( v492 != nullptr )
              v137 = sub_44E1F0(v136, 1);
            else
              v137 = 0;
            v138 = *(this + 29);
            v506 = -1;
            sub_45FE80(v138, v137, 2, 0, v137, (int)this, 0);
            v139 = *(uint32_t *)v137;
            v479 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int))(v139 + 148))(v137);
            v140 = *(uint32_t *)v137;
            v141 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v142 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v141);
            v143 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v142);
            (*(void (/*thiscall*/ **)(int, int))(v140 + 112))(v137, v143);
            (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)v137 + 60))(v137, this);
            sub_4A06D0(v479);
          }
          if ( (uint8_t)sub_423340(this + 2087, szPassword) != 0 )
          {
            if ( (unsigned int)*(this + 2093) < 0x10 )
              v144 = this + 2088;
            else
              v144 = (uint32_t *)*(this + 2088);
            (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, v144, -1, 0, 0);
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), *(this + 2055));
            v145 = *(uint32_t *)*(this + 2054);
            v146 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v147 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v146);
            v148 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v147);
            (*(void (/*thiscall*/ **)(uint32_t, int))(v145 + 40))(*(this + 2054), v148);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 12))(*(this + 2054), 0);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 112))(*(this + 2054), 0);
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 2054) + 92))(*(this + 2054), v496);
            sub_5E5260(v496);
          }
          v149 = *this;
          *(float *)&v491 = 0.0;
          v490 = 0;
          v488 = 0;
          if ( (*(int (/*thiscall*/ **)(int *))(v149 + 1096))(this) == 1 )
          {
            sub_4C17C0(&v491, &v490, &v488, 74, 0, 57);
            v150 = dword_8F830C;
            v151 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
            v152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v150 + 28))(v150);
            v153 = v490;
            *(uint8_t *)(v152 + 84) = v151;
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v150 + 40))(v150, v491, v153, v488);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v150 + 12))(v150, 0);
            (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v150 + 92))(v150, &v501);
            v506 = 18;
            sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);
            goto LABEL_232;
          }
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 2 )
          {
            sub_4C17C0(&v491, &v490, &v488, 63, 0, 85);
            sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall4.ani");
            v506 = 19;
            v154 = (void *)sub_44B6C0(284);
            v492 = v154;
            LOBYTE(v506) = 20;
            if ( v154 != nullptr )
            {
              v489 = COERCE_FLOAT(sub_42FCB0(228));
              LOBYTE(v506) = 21;
              if ( v489 == 0.0 )
              {
                v156 = 0;
              }
              else
              {
                LOBYTE(v155) = Block[0];
                if ( v504 < 0x10 )
                  v155 = Block;
                v156 = sub_431860((char)v155, 1);
              }
              LOBYTE(v506) = 20;
              v157 = sub_44E1F0(v156, 1);
            }
            else
            {
              v157 = 0;
            }
            v158 = *(this + 29);
            LOBYTE(v506) = 19;
            sub_45FE80(v158, (int)v154, 2, 0, v157, (int)this, 1);
            v159 = *(uint32_t *)v157;
            v160 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v159 + 148))(v157, v160);
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v157 + 112))(v157, v491, v490, v488);
            v480 = rand() % 40 + 110;
            v161 = rand();
            sub_4C17C0(&v491, &v490, &v488, v161 % 40 + 13, 0, v480);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");
            v492 = (void *)sub_44B6C0(284);
            LOBYTE(v506) = 22;
            if ( v492 != nullptr )
            {
              v489 = COERCE_FLOAT(sub_42FCB0(228));
              LOBYTE(v506) = 23;
              if ( v489 == 0.0 )
              {
                v163 = 0;
              }
              else
              {
                LOBYTE(v162) = Block[0];
                if ( v504 < 0x10 )
                  v162 = Block;
                v163 = sub_431860((char)v162, 1);
              }
              LOBYTE(v506) = 22;
              v164 = sub_44E1F0(v163, 1);
            }
            else
            {
              v164 = 0;
            }
            v165 = *(this + 29);
            LOBYTE(v506) = 19;
            sub_45FE80(v165, v164, 2, 0, v164, (int)this, 0);
            v166 = *(uint32_t *)v164;
            v167 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v166 + 148))(v164, v167);
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v164 + 112))(v164, v491, v490, v488);
            v506 = -1;
            sub_501490(v499);
          }
        }
        else if ( v122 == 2 )
        {
          sub_4AECE0((void *)*(this + 30), 13);
          LOBYTE(a5) = 0;
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "R_GN_PUNISHER_END",
            -1,
            0,
            0);
        }
      }
      else
      {
        v123 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(a3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8));
        v124 = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(this + 2175) = v124;
        if ( v124 != 0 )
        {
          v125 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v124 + 120))(v124);
          v126 = *(this + 2175);
          *(this + 2176) = v125;
          v127 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v126 + 124))(v126);
          v128 = *(this + 2175);
          *(this + 2177) = v127;
          *(this + 2178) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v128 + 128))(v128);
          if ( *(this + 2179) == 0 )
          {
            v492 = operator new(0x5Cu);
            v506 = 14;
            if ( v492 != nullptr )
              v129 = sub_4C11D0(this);
            else
              v129 = 0;
            v506 = -1;
            *(this + 2179) = v129;
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2179) + 56))(
            *(this + 2179),
            *(this + 2175),
            this,
            0,
            0,
            0,
            -1);
        }
        if ( *(this + 2180) == 0 )
        {
          v492 = (void *)sub_42FCB0(228);
          v506 = 15;
          if ( v492 != nullptr )
            v130 = sub_431860((char)"Character/Gunner/Effect/Animation/TreadShootDust1.ani", 1);
          else
            v130 = 0;
          v506 = -1;
          *(this + 2180) = v130;
          v492 = (void *)sub_42FCB0(228);
          v506 = 16;
          if ( v492 != nullptr )
            v131 = sub_431860((char)"Character/Gunner/Effect/Animation/TreadShootDust2.ani", 1);
          else
            v131 = 0;
          v506 = -1;
          *(this + 2181) = v131;
        }
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(
          this,
          -1,
          *(this + 2180),
          0,
          0,
          0,
          1);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          1,
          *(this + 2181),
          0,
          0,
          0,
          0);
        sub_41A590((unsigned int)(this + 2136), v132, 0);
        *(this + 2129) = 6;
        *((uint8_t *)this + 8576) = 0;
        *((uint8_t *)this + 8728) = 0;
      }
      goto LABEL_482;
    case 19:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 456);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      v168 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 7);
      v169 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 7);
      v170 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
      v492 = (void *)sub_47EFD0(v168, 0.0, v169, v170, v170, 0);
      *((float *)this + 97) = (float)(int)v492;
      v492 = (void *)sub_47EF20(2, v169, -1, -1, 11);
      *((float *)this + 106) = (double)(int)v492 * 0.1;
      *(this + 109) = sub_47EF20(3, v169, -1, -1, 11);
      v492 = (void *)sub_47EF20(1, v169, -1, -1, 11);
      v171 = *this;
      v489 = (double)(int)v492 * 0.0099999998 + 1.0;
      v492 = (void *)(*(int (/*thiscall*/ **)(int *, int))(v171 + 900))(this, 3);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(
        this,
        0,
        0,
        (uint64_t)((double)(int)v492 * v489),
        (uint64_t)((double)(int)v492 * v489));
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_MACH", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "MACH_SWING", -1, 0, 0);
      goto LABEL_482;
    case 20:
      v489 = *(float *)(*(uint32_t *)(a3 + 4) + 8);
      v172 = (void *)sub_41A5E0((unsigned int)(this + 2076));
      v173 = *this;
      v492 = v172;
      v174 = (*(int (/*thiscall*/ **)(int *, int))(v173 + 672))(this, 3);
      v175 = sub_495500(v174);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v173 + 888))(
        this,
        0,
        0,
        1000,
        LODWORD(v489) * (int)v492 * v175 / 10000);
      if ( v487 != 20 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 52));
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 9);
        v176 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 9);
        *(this + 2184) = sub_47EF20(1, v176, -1, -1, 11);
        *(this + 2184) = sub_41A5E0((unsigned int)(this + 2076)) * *(this + 2184) / 100;
        v177 = sub_41A5E0((unsigned int)(this + 2076));
        v178 = sub_47E9D0(0);
        *(this + 2129) = 9;
        v504 = 15;
        v503 = 0;
        LOBYTE(Block[0]) = 0;
        *(this + 2187) = 100000 / (v177 * v178);
        v179 = *this;
        v506 = 24;
        v180 = (*(int (/*thiscall*/ **)(int *))(v179 + 1096))(this);
        if ( v180 >= 0 )
        {
          if ( v180 <= 3 )
          {
            sub_406D60("R_GUN_GRAZE_LOOP");
          }
          else if ( v180 == 4 )
          {
            sub_406D60("R_BOWGUN_GRAZE_LOOP");
          }
        }
        v181 = (void **)Block[0];
        if ( v504 < 0x10 )
          v181 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v181, 11, 0, 0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "GN_RANDOMSHOT",
          -1,
          0,
          0);
        *(this + 2188) = 0;
        *(this + 2189) = 0;
        v182 = -*(this + 2187);
        *(this + 2183) = -1;
        *(this + 2186) = v182;
        sub_6569D0(this + 2130);
        *(this + 2133) = sub_699000((int)(this + 2));
        v506 = -1;
        if ( v504 >= 0x10 )
          j__free(Block[0]);
      }
      v183 = (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this);
      if ( v183 == 1 )
        v183 = 0;
      v184 = sub_4C1000(this);
      if ( v183 == 4 )
        v184 = 4;
      v492 = (void *)(5 * v183 + 1095);
      v185 = *(this + 2 * ((uint32_t)v492 + v184));
      v490 = (int)(this + 2 * ((uint32_t)v492 + v184));
      if ( v185 == 0 )
      {
        v186 = sub_42FCB0(228);
        v489 = *(float *)&v186;
        v506 = 25;
        if ( v186 != 0 )
        {
          v187 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);
          v188 = sub_4319E0(v186, v183, v184, v187, "Effect/Animation/ShootEffect/RandomShoot1.ani", 1);
        }
        else
        {
          v188 = 0;
        }
        v506 = -1;
        *(uint32_t *)v490 = v188;
        v189 = sub_42FCB0(228);
        v489 = *(float *)&v189;
        v506 = 26;
        if ( v189 != 0 )
        {
          v190 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);
          v191 = sub_4319E0(v189, v183, v184, v190, "Effect/Animation/ShootEffect/RandomShoot2.ani", 1);
        }
        else
        {
          v191 = 0;
        }
        v506 = -1;
        *(this + 8 * v183 + 2 * v183 + 2 * v184 + 2191) = v191;
        if ( v184 == 1 )
        {
          v491 = 2;
          do
          {
            for ( mm = 0; ; ++mm )
            {
              v193 = *(this + 2 * (uint32_t)v492 + 2);
              v194 = *(uint32_t *)(v193 + 44);
              if ( v194 != 0 )
                v194 = (*(uint32_t *)(v193 + 48) - v194) / 88;
              if ( mm >= v194 )
                break;
              *(uint32_t *)(sub_4924C0(mm) + 40) = 2;
            }
            --v491;
          }
          while ( *(float *)&v491 != 0.0 );
        }
      }
      v195 = (int *)v490;
      v196 = this + 2188;
      v197 = 0;
      v491 = (int)(this + 2188);
      do
      {
        v198 = *v196;
        if ( v198 != *v195 )
        {
          if ( v198 != 0 )
            (*(void (/*thiscall*/ **)(int *, int))(*this + 208))(this, v198);
          v199 = *v195;
          *(uint32_t *)v491 = *v195;
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
            this,
            2 * (v197 == 0) - 1,
            v199,
            0,
            0,
            0,
            0);
        }
        ++v197;
        v196 = (int *)(v491 + 4);
        ++v195;
        v491 += 4;
      }
      while ( v197 < 2 );
      v200 = **(void ***)(a3 + 4);
      v201 = (void *)*(this + 2183);
      v202 = 0;
      v492 = v201;
      *(this + 2183) = (int)v200;
      if ( v200 == (void *)1 )
      {
        v202 = 4;
      }
      else if ( v200 == (void *)2 )
      {
        v202 = 9;
      }
      else if ( v200 == (void *)3 )
      {
        v202 = 14;
      }
      if ( v201 == v200 )
        ++v202;
      v203 = *(this + 30);
      v204 = sub_491C70(v203, v202);
      sub_493A60(v203, v204);
      LOBYTE(a5) = 0;
      v491 = (int)(this + 2188);
      v490 = 2;
      do
      {
        v205 = *(uint32_t *)v491;
        v206 = sub_491C70(*(uint32_t *)v491, v202);
        sub_493A60(v205, v206);
        v207 = v490 == 1;
        v491 += 4;
        --v490;
      }
      while ( !v207 );
      *(this + 2185) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      if ( v487 != 20 && v492 != (void *)*(this + 2183) )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "R_GN_RANDOMSHOT_CHANGE",
          -1,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "R_QUICK_MOTION",
          -1,
          0,
          0);
      }
      goto LABEL_482;
    case 21:
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SWD_GUARDED", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_GUNGUARD", -1, 0, 0);
      v208 = *(int **)(a3 + 4);
      v209 = *v208;
      v210 = v208[1];
      v211 = *this;
      v491 = v209;
      v488 = v210;
      v212 = (*(int (/*thiscall*/ **)(int *))(v211 + 124))(this);
      v213 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
      v490 = v212;
      v492 = (void *)sub_42FCB0(228);
      v506 = 27;
      if ( v492 != nullptr )
        v214 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
      else
        v214 = 0;
      v506 = -1;
      v492 = (void *)sub_44B6C0(284);
      v506 = 28;
      if ( v492 != nullptr )
        v215 = sub_44E1F0(v214, 1);
      else
        v215 = 0;
      v216 = *(this + 29);
      v506 = -1;
      sub_45FE80(v216, v213, 2, 0, v215, (int)this, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v215 + 148))(v215, v491);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v215 + 112))(v215, v488, v490, v213);
      v492 = (void *)sub_42FCB0(228);
      v506 = 29;
      if ( v492 != nullptr )
        v217 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
      else
        v217 = 0;
      v506 = -1;
      v492 = (void *)sub_44B6C0(284);
      v506 = 30;
      if ( v492 != nullptr )
        v218 = sub_44E1F0(v217, 1);
      else
        v218 = 0;
      v219 = *(this + 29);
      v506 = -1;
      sub_45FE80(v219, v213, 2, 0, v218, (int)this, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v218 + 148))(v218, v491);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v218 + 112))(v218, v488, v490, v213);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 56));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 3, 1000, 1000);
      goto LABEL_482;
    case 22:
      v492 = (void *)*(this + 2242);
      v220 = **(uint32_t **)(a3 + 4);
      v221 = this + 2129;
      *(this + 2129) = v220;
      v222 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      v223 = -1;
      *(this + 2242) = v222;
      v491 = 5;
      switch ( v220 )
      {
        case 12:
          v491 = 1;
LABEL_332:
          v223 = 17;
          break;
        case 13:
        case 36:
          *(float *)&v491 = 0.0;
          goto LABEL_332;
        case 14:
          v491 = 1;
          v223 = 21;
          break;
        case 39:
          v491 = 2;
          goto LABEL_332;
        case 40:
          v491 = 4;
          v223 = 15;
          break;
        default:
          break;
      }
      v224 = v222 + v223;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4 * v224));
      sub_4C4890(this, v491, v224);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *v221);
      LODWORD(v226) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *v221);
      v225 = *(this + 2242);
      v491 = v226;
      LODWORD(v226) = 1000;
      v488 = 1000;
      if ( v225 == 0 )
      {
        v489 = *(float *)(*(this + 30) + 36);
        v490 = LODWORD(v489);
        switch ( *v221 )
        {
          case 0xC:
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);
            v230 = sub_47EF20(1, v491, -1, -1, 11);
            goto LABEL_338;
          case 0xD:
          case 0x24:
          case 0x27:
            v227 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v488 = sub_495540(v227);
            v228 = sub_4B1C40(v491);
            v229 = *this;
            v490 = v228;
            (*(void (/*thiscall*/ **)(int *, float, int))(v229 + 992))(this, COERCE_FLOAT(LODWORD(v489)), 1);
            break;
          case 0x28:
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);
            v230 = sub_47EF20(2, v491, -1, -1, 11);
LABEL_338:
            v490 = v230;
            break;
          default:
            break;
        }
        v226 = (uint64_t)((double)v488 * ((double)SLODWORD(v489) / (double)v490));
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, uint32_t))(*this + 888))(this, 0, 0, 1000, v226);
      v231 = *v221;
      if ( *v221 == 40 )
      {
        v232 = *(this + 2242);
        if ( v232 != 0 )
        {
          if ( v232 == 1 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
            {
              v233 = *this;
              v234 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 152))(this, 0, 0, 0);
              v235 = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int))(*this + 588))(
                       this,
                       "Particle/SubWeapon/Steyr.ptl",
                       0,
                       150,
                       0,
                       85,
                       v234);
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(v233 + 580))(this, 22203, 0, v235);
            }
            v502 = 0.0;
            v503 = 0;
            *(float *)&v504 = 0.0;
            v506 = 31;
            sub_431230((int)&v501, this + 2129);
            v492 = nullptr;
            sub_431230((int)&v501, &v492);
            v492 = nullptr;
            sub_431230((int)&v501, &v492);
            (*(void (/*thiscall*/ **)(int *, int, float *, uint32_t, uint32_t))(*this + 560))(this, 26, &v501, 0, 0);
            if ( *(this + 2358) == 0 )
            {
              v492 = (void *)sub_42FCB0(228);
              LOBYTE(v506) = 32;
              if ( v492 != nullptr )
              {
                v236 = unknown_libname_2(this + 90);
                v237 = sub_431920(v236, (char)"Effect/Animation/ShootEffect/SteyrShoot.ani", 1);
              }
              else
              {
                v237 = 0;
              }
              LOBYTE(v506) = 31;
              *(this + 2358) = v237;
            }
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
              this,
              1,
              *(this + 2358),
              0,
              0,
              0,
              0);
            v506 = -1;
            sub_5E5260((void **)&v501);
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_STEYR", -1, 0, 0);
        }
      }
      else
      {
        switch ( v231 )
        {
          case 39:
            v238 = *(this + 2242);
            if ( v238 != 0 )
            {
              if ( v238 == 1 )
              {
                if ( *((uint8_t *)this + 9428) != 0 )
                  v253 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
                else
                  v253 = 0;
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "R_GN_LASER_SHOT",
                  -1,
                  0,
                  0);
                (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 13);
                if ( v253 < *(this + 2356) )
                {
                  if ( *(this + 2347) == 0 )
                  {
                    v492 = (void *)sub_42FCB0(228);
                    v506 = 39;
                    if ( v492 != nullptr )
                    {
                      v254 = unknown_libname_2(this + 90);
                      v255 = sub_431920(v254, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceEffect.ani", 1);
                    }
                    else
                    {
                      v255 = 0;
                    }
                    v506 = -1;
                    *(this + 2347) = v255;
                  }
                  if ( *(this + 2348) == 0 )
                  {
                    v492 = (void *)sub_42FCB0(228);
                    v506 = 40;
                    if ( v492 != nullptr )
                    {
                      v256 = unknown_libname_2(this + 90);
                      v257 = sub_431920(v256, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceSpark.ani", 1);
                    }
                    else
                    {
                      v257 = 0;
                    }
                    v506 = -1;
                    *(this + 2348) = v257;
                  }
                  sub_4926A0(*(this + 2347));
                  sub_4926A0(*(this + 2348));
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                    this,
                    1,
                    *(this + 2348),
                    0,
                    0,
                    0,
                    0);
                }
                if ( *(this + 2349) == 0 )
                {
                  v492 = (void *)sub_42FCB0(228);
                  v506 = 41;
                  if ( v492 != nullptr )
                  {
                    v258 = unknown_libname_2(this + 90);
                    v259 = sub_431920(v258, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireRing.ani", 1);
                  }
                  else
                  {
                    v259 = 0;
                  }
                  v506 = -1;
                  *(this + 2349) = v259;
                }
                sub_4926A0(*(this + 2349));
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                  this,
                  3,
                  *(this + 2349),
                  0,
                  0,
                  0,
                  0);
                if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
                {
                  v260 = *this;
                  v261 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 152))(this, 0, 0, 0);
                  (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t, int, int))(v260 + 580))(
                    this,
                    22017,
                    v253,
                    0,
                    0,
                    150,
                    0,
                    85,
                    v261);
                }
              }
            }
            else
            {
              v239 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 41) > 0;
              *((uint8_t *)this + 9428) = v239;
              if ( v239 )
              {
                v473 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 41, -1);
                (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
                *(this + 2356) = sub_47EF20(41, 0, v473, -1, 11);
              }
              else
              {
                *(this + 2356) = 0;
              }
              v240 = *(this + 2343);
              *((uint8_t *)this + 9416) = 0;
              *(this + 2355) = 0;
              if ( v240 != 0 )
              {
                *(uint8_t *)(v240 + 160) = 1;
              }
              else
              {
                v492 = (void *)sub_42FCB0(228);
                v506 = 33;
                if ( v492 != nullptr )
                {
                  v241 = unknown_libname_2(this + 90);
                  v242 = sub_431920(v241, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargingEffect.ani", 1);
                }
                else
                {
                  v242 = 0;
                }
                v506 = -1;
                *(this + 2343) = v242;
                v492 = (void *)sub_42FCB0(228);
                v506 = 34;
                if ( v492 != nullptr )
                {
                  v243 = unknown_libname_2(this + 90);
                  v244 = sub_431920(v243, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargeFullEffect.ani", 1);
                  v506 = -1;
                  *(this + 2344) = v244;
                }
                else
                {
                  v506 = -1;
                  *(this + 2344) = 0;
                }
              }
              if ( *(this + 2350) == 0 )
              {
                v492 = (void *)sub_42FCB0(228);
                v506 = 35;
                if ( v492 != nullptr )
                {
                  v245 = unknown_libname_2(this + 90);
                  v246 = sub_431920(
                           v245,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge1.ani",
                           1);
                }
                else
                {
                  v246 = 0;
                }
                v506 = -1;
                *(this + 2350) = v246;
                v492 = (void *)sub_42FCB0(228);
                v506 = 36;
                if ( v492 != nullptr )
                {
                  v247 = unknown_libname_2(this + 90);
                  v248 = sub_431920(
                           v247,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge2.ani",
                           1);
                }
                else
                {
                  v248 = 0;
                }
                v506 = -1;
                *(this + 2351) = v248;
                v492 = (void *)sub_42FCB0(228);
                v506 = 37;
                if ( v492 != nullptr )
                {
                  v249 = unknown_libname_2(this + 90);
                  v250 = sub_431920(
                           v249,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleFullCharge2.ani",
                           1);
                }
                else
                {
                  v250 = 0;
                }
                v506 = -1;
                *(this + 2352) = v250;
                v492 = (void *)sub_42FCB0(228);
                v506 = 38;
                if ( v492 != nullptr )
                {
                  v251 = unknown_libname_2(this + 90);
                  v252 = sub_431920(
                           v251,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleFullCharge1.ani",
                           1);
                }
                else
                {
                  v252 = 0;
                }
                v506 = -1;
                *(this + 2353) = v252;
              }
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_LASER",
                -1,
                0,
                0);
            }
            break;
          case 12:
            v262 = *(this + 2242);
            if ( v262 != 0 )
            {
              if ( v262 == 1 )
              {
                v263 = v492 == (void *)1;
                *((uint8_t *)this + 9301) = v492 == (void *)1;
                if ( v263 )
                {
                  v481 = *(this + 2326);
                  v475 = sub_699000((int)(this + 1640));
                  v270 = sub_47EF20(1, v491, -1, -1, 11);
                  v271 = sub_423A80(0, v270, v475, v481);
                  v272 = (void *)*(this + 30);
                  *(this + 2327) = v271;
                  sub_4AECE0(v272, 0);
                  sub_4939E0(*(this + 30), 1);
                  LOBYTE(a5) = 0;
                  if ( *(this + 2334) == 0 )
                  {
                    v492 = (void *)sub_42FCB0(228);
                    v506 = 44;
                    if ( v492 != nullptr )
                    {
                      v273 = unknown_libname_2(this + 90);
                      v274 = sub_431920(v273, (char)"Effect/Animation/GatlingGunOverHeat.ani", 1);
                    }
                    else
                    {
                      v274 = 0;
                    }
                    v506 = -1;
                    *(this + 2334) = v274;
                    v492 = (void *)sub_42FCB0(228);
                    v506 = 45;
                    if ( v492 != nullptr )
                    {
                      v275 = unknown_libname_2(this + 90);
                      v276 = sub_431920(v275, (char)"Effect/Animation/GatlingOverHeat.ani", 1);
                    }
                    else
                    {
                      v276 = 0;
                    }
                    v506 = -1;
                    *(this + 2335) = v276;
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                    this,
                    1,
                    *(this + 2334),
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                    this,
                    2,
                    *(this + 2335),
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "MACHINEGUN_OVERHIT",
                    -1,
                    0,
                    0);
                }
                else
                {
                  *(this + 2326) = sub_47EF20(2, v491, -1, -1, 11);
                  sub_4C1440(this);
                  v264 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                           dword_8F84E4,
                           "Character/Gunner/Particle/SubWeapon/Gatling.ptl");
                  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v264);
                  v265 = 1000 / sub_47E9D0(0);
                  *(this + 2330) = 0;
                  *(this + 2331) = -1;
                  *(this + 2329) = v265;
                  *(this + 2328) = -v265;
                  if ( *(this + 2332) == 0 )
                  {
                    v492 = operator new(0x12Cu);
                    v506 = 42;
                    if ( v492 != nullptr )
                    {
                      v266 = unknown_libname_2(this + 90);
                      v267 = sub_4C3640(v266, "Effect/Particle/GatlingShell.ptl", this);
                    }
                    else
                    {
                      v267 = 0;
                    }
                    v506 = -1;
                    *(this + 2332) = v267;
                  }
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2332) + 12))(*(this + 2332), 0);
                  if ( *(this + 2333) == 0 )
                  {
                    v492 = (void *)sub_42FCB0(228);
                    v506 = 43;
                    if ( v492 != nullptr )
                    {
                      v268 = unknown_libname_2(this + 90);
                      v269 = sub_431920(v268, (char)"Effect/Animation/GatlingGunShoot.ani", 1);
                    }
                    else
                    {
                      v269 = 0;
                    }
                    v506 = -1;
                    *(this + 2333) = v269;
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                    this,
                    1,
                    *(this + 2333),
                    0,
                    0,
                    0,
                    0);
                }
              }
            }
            else
            {
              *((uint8_t *)this + 9301) = 0;
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_GATTLING",
                -1,
                0,
                0);
            }
            break;
          case 13:
          case 36:
            v285 = *(this + 2242);
            if ( v285 != 0 )
            {
              if ( v285 == 1 )
              {
                v207 = v492 != (void *)1;
                *((uint8_t *)this + 9301) = v492 == (void *)1;
                if ( v207 )
                {
                  *(this + 2326) = sub_47EF20(1, v491, -1, -1, 11);
                  v286 = "Character/Gunner/Effect/Particle/FlameThrower.ptl";
                  if ( *v221 != 13 )
                    v286 = "Character/Gunner/Effect/Particle/FlameThrowerBoost.ptl";
                  sub_401710(v286);
                  v287 = *(uint32_t *)dword_8F84E4;
                  v506 = 46;
                  v288 = unknown_libname_2(v499);
                  v289 = (*(int (/*thiscall*/ **)(int, int))(v287 + 4))(dword_8F84E4, v288);
                  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v289);
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 12))(*(this + 2054), 0);
                  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
                    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
                      this,
                      *v221 != 13 ? 22204 : 22201,
                      0,
                      0,
                      0,
                      141,
                      0,
                      88,
                      4,
                      0,
                      0,
                      0);
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "FLAMETHROWER_FIRE",
                    -1,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "FLAMETHROWER_LOOP",
                    12,
                    0,
                    0);
                  v506 = -1;
                  sub_501490(v499);
                }
                else
                {
                  v482 = *(this + 2326);
                  v476 = sub_699000((int)(this + 1640));
                  v290 = sub_47E9D0(0);
                  v291 = sub_423A80(0, v290, v476, v482);
                  v292 = (void *)*(this + 30);
                  *(this + 2327) = v291;
                  sub_4AECE0(v292, 0);
                  sub_4939E0(*(this + 30), 1);
                  LOBYTE(a5) = 0;
                  (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 12);
                }
              }
            }
            else
            {
              *((uint8_t *)this + 9301) = 0;
              if ( v231 == 13 )
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "GN_FLAMETHROWER",
                  -1,
                  0,
                  0);
              else
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "R_GN_FLAMETHROWER_SHOT",
                  -1,
                  0,
                  0);
            }
            break;
          default:
            if ( v231 == 14 && *(this + 2242) == 1 )
            {
              v277 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                       dword_8F84E4,
                       "Character/Gunner/Particle/SubWeapon/AerialGatling.ptl");
              (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v277);
              *(this + 2329) = 100;
              *(this + 2328) = -100;
              *(this + 2330) = 0;
              v278 = sub_47E9D0(0);
              v279 = v278 * *(this + 2329);
              *(this + 2331) = v278;
              v280 = *(this + 2332);
              *(this + 2326) = v279 + 200;
              if ( v280 == 0 )
              {
                v492 = operator new(0x12Cu);
                v506 = 47;
                if ( v492 != nullptr )
                {
                  v281 = unknown_libname_2(this + 90);
                  v282 = sub_4C3640(v281, "Effect/Particle/GatlingShell.ptl", this);
                }
                else
                {
                  v282 = 0;
                }
                v506 = -1;
                *(this + 2332) = v282;
              }
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2332) + 12))(*(this + 2332), 0);
              if ( *(this + 2341) == 0 )
              {
                v492 = (void *)sub_42FCB0(228);
                v506 = 48;
                if ( v492 != nullptr )
                {
                  v283 = unknown_libname_2(this + 90);
                  v284 = sub_431920(v283, (char)"Effect/Animation/AerialGatlingGunShoot.ani", 1);
                }
                else
                {
                  v284 = 0;
                }
                v506 = -1;
                *(this + 2341) = v284;
              }
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                this,
                1,
                *(this + 2341),
                0,
                0,
                0,
                0);
            }
            break;
        }
      }
      if ( *(this + 2242) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "SUBWEAPON_DRAW",
          -1,
          0,
          0);
        *((uint8_t *)this + 9300) = 0;
        for ( nn = 2; nn <= 3; ++nn )
        {
          v294 = sub_4924C0(nn);
          sub_5E5260((void **)(v294 + 56));
        }
        if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 34) > 0 )
        {
          Block[1] = (void *)-1049624576;
          v503 = 1106247680;
          for ( i1 = 2; i1 <= 3; ++i1 )
          {
            v296 = (uint32_t *)sub_4924C0(i1);
            v297 = *v296;
            v298 = *(char **)(*v296 + 28);
            v502 = (float)*(unsigned int *)(*v296 + 20);
            v492 = v298;
            v492 = &v298[v296[3]];
            v299 = *(uint32_t *)(v297 + 24);
            *(float *)Block = (float)(int)v492;
            v300 = (double)*(int *)(v297 + 24);
            if ( v299 < 0 )
              v300 = v300 + 4294967300.0;
            v301 = v296[4];
            *(float *)&v504 = v300;
            v492 = (void *)-(*(uint32_t *)(v297 + 32) + v299 + v301);
            v501 = (float)(unsigned int)v492;
            v302 = sub_4924C0(i1);
            sub_4931A0((int *)(v302 + 56), Block);
          }
          v483 = *(this + 139) + 608;
          (*(void (/*thiscall*/ **)(int *))(*this + 344))(this);
          v303 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, 34, 0, v303);
          v492 = (void *)sub_47EF20(34, -1, -1, 11, v483);
          *((float *)this + 97) = (float)(int)v492;
        }
      }
LABEL_482:
      sub_4B89D0(a2, a3, *(float *)&a4, *(float *)&a5);
      switch ( a2 )
      {
        case 0:
          *(this + 2134) = -1;
          *(this + 2135) = -1;
          return;
        case 4:
          if ( *(this + 1708) == 2 )
          {
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 8) <= 0 )
            {
              *(this + 2166) = -1;
            }
            else
            {
              v441 = *(this + 30);
              v442 = *(uint32_t *)(v441 + 212);
              if ( v442 != 0 )
                v443 = sub_4910A0(v442);
              else
                v443 = *(uint32_t *)(v441 + 32);
              (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 8);
              v444 = sub_47E9D0(0);
              *(this + 2166) = sub_491C10(*(this + 30)) - v443 - v444;
            }
          }
          return;
        case 6:
          if ( v487 == 7 )
          {
            if ( *(this + 1723) == 1 )
            {
              v470 = abs32(*(this + 2155));
              (*(void (/*thiscall*/ **)(int *, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this + 876))(
                this,
                0,
                v470,
                v470,
                0,
                0,
                0);
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
                this,
                1,
                0,
                0,
                0,
                0,
                0);
              v420 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
              if ( *(this + 2155) < 0 )
                v420 = sub_432E50(v420);
              (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, v420, 4);
            }
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;
            v421 = *this;
            v506 = 60;
            v422 = (*(int (/*thiscall*/ **)(int *))(v421 + 1096))(this);
            sub_4C2020((int)v494, v422);
            v423 = (void **)v495[0];
            if ( v498 < 0x10 )
              v423 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v423, -1, 0, 0);
            if ( v498 >= 0x10 )
              goto LABEL_630;
          }
          return;
        case 7:
          if ( v487 == 7 )
          {
            --*(this + 1724);
            v424 = *(this + 2154);
            if ( v424 != 0 )
            {
              if ( v424 == 1 || v424 == 2 )
              {
                v425 = sub_41A5E0((unsigned int)(this + 2136));
                if ( v425 < sub_41A5E0((unsigned int)(this + 2062)) )
                  *(this + 2154) = (*(this + 2154) == 1) + 1;
                else
                  *(this + 2154) = 3;
              }
              else
              {
                off_77F3FC(aCriticalErrorJ, *(this + 2154));
              }
            }
            else
            {
              *(this + 2154) = 1;
            }
          }
          else
          {
            *(this + 2154) = 0;
            sub_41A590((unsigned int)(this + 2136), v327, 0);
          }
          v426 = *(this + 2154);
          if ( v426 != 0 )
          {
            if ( v426 == 1 || v426 == 2 )
            {
              v433 = sub_41A5E0((unsigned int)(this + 2136));
              sub_41A590((unsigned int)(this + 2136), v434, v433 + 1);
              v435 = sub_699000((int)(this + 1640));
              *(this + 2140) = sub_4C0DF0(0) + v435;
              v436 = sub_4C0DF0(1);
              v437 = *this;
              *(this + 2141) = *(this + 2140) + v436;
              (*(void (/*thiscall*/ **)(int *, uint32_t))(v437 + 196))(this, *(uint32_t *)(*(this + 1554) + 20));
              v438 = *(this + 30);
              v439 = sub_491C70(v438, *(this + 2154) != 1 ? 3 : 0);
              sub_493A60(v438, v439);
              v440 = *(this + 2156);
              if ( v440 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v440 + 80))() != 0 )
              {
                (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
                  this,
                  0,
                  0,
                  0,
                  0,
                  0,
                  0);
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
                  this,
                  1,
                  0,
                  0,
                  0,
                  0,
                  0);
                (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
                sub_495890(0, 0);
                sub_494F20(2, 0.0);
              }
            }
            else if ( v426 == 3 )
            {
              v431 = *this;
              v432 = sub_4C0EB0(this);
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v431 + 888))(this, 0, 0, 1000, v432);
              (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 24));
              sub_4926A0(*(this + 30));
            }
          }
          else
          {
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;
            v427 = *this;
            v506 = 61;
            v428 = (*(int (/*thiscall*/ **)(int *))(v427 + 1096))(this);
            if ( v428 >= 0 )
            {
              if ( v428 <= 3 )
              {
                sub_406D60("GUN_DRAW3");
              }
              else if ( v428 == 4 )
              {
                sub_406D60("BOWGUN_DRAW3");
              }
            }
            v429 = (void **)v495[0];
            if ( v498 < 0x10 )
              v429 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v429, -1, 0, 0);
            v430 = *(this + 2156);
            if ( v430 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v430 + 80))() != 0 )
            {
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
                this,
                0,
                0,
                0,
                0,
                0,
                0);
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
                this,
                1,
                0,
                0,
                0,
                0,
                0);
              (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
              sub_495890(0, 0);
              sub_494F20(2, 0.0);
            }
            if ( v498 >= 0x10 )
LABEL_630:
              j__free(v495[0]);
          }
          return;
        case 8:
          if ( v487 == 8 )
          {
            v340 = sub_41A5E0((unsigned int)(this + 1757));
            v332 = (unsigned int)this + 8577;
            v342 = (unsigned int)this + 8577;
            if ( v340 != 0 )
            {
              v343 = sub_41A5E0(v342);
              v345 = (unsigned int)this + 8577;
              if ( v343 == 1 )
              {
                sub_41A590(v345, v344, 2);
              }
              else
              {
                v346 = sub_41A5E0(v345);
                v348 = (unsigned int)this + 8577;
                if ( v346 == 2 )
                {
                  sub_41A590(v348, v347, 3);
                }
                else if ( sub_41A5E0(v348) == 3 )
                {
                  sub_41C150((unsigned int)this + 8577, v349, 4);
                }
              }
            }
            else
            {
              sub_41A590(v342, v341, 1);
            }
          }
          else
          {
            v328 = *(uint32_t *)(a3 + 4);
            if ( v328 != 0 && (unsigned int)((*(uint32_t *)(a3 + 8) - v328) >> 2) > 1 )
              v329 = *(uint32_t *)(v328 + 4);
            else
              v329 = -1;
            v330 = -1;
            *(this + 2129) = v329;
            if ( v329 == 20 )
            {
              *((uint8_t *)this + 8608) = 1;
              *(this + 2129) = 5;
            }
            else
            {
              *((uint8_t *)this + 8608) = 0;
            }
            v331 = *(this + 2129);
            if ( v331 == 5 || v331 == 47 || v331 == 53 )
            {
              v332 = (unsigned int)this + 8577;
              sub_41A590((unsigned int)this + 8577, v327, 2);
              v334 = *(this + 2129);
              if ( v334 == 5 )
              {
                (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 5);
                sub_47DCD0(this, -1);
              }
              else if ( v334 == 53 )
              {
                v335 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 53);
                (*(void (/*thiscall*/ **)(int *, int, int))(*this + 1160))(this, 53, v335);
                v336 = sub_4B1C40(v485);
                v485 = 3;
                v337 = 1000 * v336;
                v338 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
                v339 = sub_495540(v338);
                v333 = v337 % v339;
                v330 = v337 / v339;
              }
            }
            else
            {
              v332 = (unsigned int)this + 8577;
              sub_41A590((unsigned int)this + 8577, v327, 0);
            }
            sub_41A590((unsigned int)(this + 2136), v333, 0);
            if ( v330 != -1 )
              (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 992))(this, v330, 0);
          }
          if ( sub_41A5E0(v332) == 0 || sub_41A5E0(v332) == 2 )
            *((uint8_t *)this + 8576) = 0;
          if ( sub_41A5E0(v332) != 1 && sub_41A5E0(v332) != 3 )
            goto LABEL_542;
          *((uint8_t *)this + 8596) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4) == 1;
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
          if ( sub_41A5E0(v332) == 1 )
          {
            v350 = *this;
            v351 = (int *)*(this + 1554);
            if ( *((uint8_t *)this + 8596) != 0 )
              v352 = v351[1];
            else
              v352 = *v351;
          }
          else
          {
            if ( sub_41A5E0(v332) != 3 )
              goto LABEL_524;
            v350 = *this;
            v353 = *(this + 1554);
            if ( *((uint8_t *)this + 8596) != 0 )
              v352 = *(uint32_t *)(v353 + 12);
            else
              v352 = *(uint32_t *)(v353 + 8);
          }
          (*(void (/*stdcall*/ **)(int))(v350 + 196))(v352);
LABEL_524:
          sub_4926A0(*(this + 30));
          v354 = sub_4C0DF0(0);
          v355 = *this;
          *(this + 2140) = v354;
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(v355 + 1000))(this) != 0 )
          {
            v356 = (*(int (/*thiscall*/ **)(int *))(*this + 1008))(this);
            v357 = (*(int (/*thiscall*/ **)(int *))(*this + 1004))(this) - v356;
            if ( v357 > *(this + 2140) )
              *(this + 2140) = v357;
          }
          *(this + 2141) = *(this + 2140) + sub_4C0DF0(1);
          if ( sub_41A5E0(v332) == 1 )
          {
            if ( 250000 / sub_4C0EB0(this) >= 125 )
              *(this + 2148) = 250000 / sub_4C0EB0(this) + *(this + 2141);
            else
              *(this + 2148) = *(this + 2141) + 125;
          }
          else
          {
            if ( *(this + 2129) == 47 )
            {
              (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 47);
              v358 = sub_47E9D0(0);
            }
            else
            {
              v358 = 100;
            }
            *(this + 2148) = *(this + 2141) + 1000 * v358 / sub_4C0EB0(this);
          }
          if ( sub_41A5E0(v332) == 3 || sub_41A5E0((unsigned int)(this + 2136)) == 0 )
          {
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;
            v359 = *this;
            v506 = 50;
            v360 = (*(int (/*thiscall*/ **)(int *))(v359 + 1096))(this);
            sub_4C2060(v494, v360);
            v361 = (void **)v495[0];
            if ( v498 < 0x10 )
              v361 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v361, -1, 0, 0);
            v506 = -1;
            if ( v498 >= 0x10 )
              j__free(v495[0]);
          }
          v362 = sub_41A5E0((unsigned int)(this + 2136));
          sub_41A590((unsigned int)(this + 2136), v363, v362 + 1);
LABEL_542:
          if ( sub_41A5E0(v332) == 4 )
          {
            v364 = *this;
            v365 = sub_4C0EB0(this);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v364 + 888))(this, 0, 0, 1000, v365);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
            sub_4926A0(*(this + 30));
            v366 = *(this + 2129);
            if ( v366 != 5 && v366 != 53 )
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "R_GN_FINAL_SHOT",
                -1,
                0,
                0);
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 23) != 0
              && (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 0 )
            {
              v492 = (void *)sub_42FCB0(228);
              v506 = 51;
              if ( v492 != nullptr )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(v367) = (uint8_t)this + 108;
                else
                  v367 = *(this + 91);
                v368 = sub_431920(v367, (char)"Effect/Animation/ReduceRevolverReload1.ani", 1);
              }
              else
              {
                v368 = 0;
              }
              v506 = -1;
              v492 = (void *)sub_44B6C0(284);
              v506 = 52;
              if ( v492 != nullptr )
                v369 = (int *)sub_44E1F0(v368, 1);
              else
                v369 = nullptr;
              v370 = *(this + 29);
              v506 = -1;
              sub_45FE80(v370, (int)v369, 2, 0, (int)v369, (int)this, 0);
              v371 = *v369;
              v372 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
              (*(void (/*thiscall*/ **)(int *, int))(v371 + 148))(v369, v372);
              v373 = *v369;
              v374 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
              v375 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v374);
              v376 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v375);
              (*(void (/*thiscall*/ **)(int *, int))(v373 + 112))(v369, v376);
              v492 = (void *)sub_42FCB0(228);
              v506 = 53;
              if ( v492 != nullptr )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(v377) = (uint8_t)this + 108;
                else
                  v377 = *(this + 91);
                v378 = sub_431920(v377, (char)"Effect/Animation/ReduceRevolverReload2.ani", 1);
              }
              else
              {
                v378 = 0;
              }
              v506 = -1;
              v492 = (void *)sub_44B6C0(284);
              v506 = 54;
              if ( v492 != nullptr )
                v379 = (int *)sub_44E1F0(v378, 1);
              else
                v379 = nullptr;
              v380 = *(this + 29);
              v506 = -1;
              sub_45FE80(v380, (int)v379, 2, 0, (int)v379, (int)this, 0);
              v381 = *v379;
              v382 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
              (*(void (/*thiscall*/ **)(int *, int))(v381 + 148))(v379, v382);
              v383 = *v379;
              v384 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
              v385 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v384);
              v386 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v385);
              (*(void (/*thiscall*/ **)(int *, int))(v383 + 112))(v379, v386);
            }
          }
          v387 = *(this + 2129);
          if ( v387 == 5 || v387 == 47 || v387 == 53 )
          {
            if ( sub_41A5E0((unsigned int)this + 8577) == 2 )
            {
              if ( *(this + 2129) == 5 )
              {
                v408 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
                (*(void (/*thiscall*/ **)(int *, uint32_t, int, int))(*this + 1160))(this, *(this + 2129), 1, v408);
                v509 = (double)(int)sub_47EF20(5, -1, -1, 11, v485) * 0.0099999998 + 1.0;
                v409 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
                v410 = (uint64_t)((double)sub_495500(v409) * v509);
                (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(this, 0, 0, v410, v410);
              }
              v411 = *(this + 30);
              v412 = sub_491C70(v411, 2);
              sub_493A60(v411, v412);
              v413 = *(this + 2129);
              switch ( v413 )
              {
                case 5:
                  if ( *((uint8_t *)this + 8608) != 0 )
                  {
                    v414 = *this;
                    v415 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
                    v416 = sub_432E50(v415);
                    (*(void (/*thiscall*/ **)(int *, int))(v414 + 144))(this, v416);
                    if ( *(this + 2153) == 0 )
                    {
                      v492 = (void *)sub_42FCB0(228);
                      v506 = 55;
                      if ( v492 != nullptr )
                      {
                        v417 = unknown_libname_2(this + 90);
                        v418 = sub_431920(v417, (char)"Effect/Animation/TurningShoot.ani", 1);
                      }
                      else
                      {
                        v418 = 0;
                      }
                      v506 = -1;
                      *(this + 2153) = v418;
                    }
                    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                      this,
                      1,
                      *(this + 2153),
                      0,
                      0,
                      0,
                      0);
                    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                      this,
                      "GN_WESTERN_FIRE",
                      -1,
                      0,
                      0);
                    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                      this,
                      "QUICK_TURN",
                      -1,
                      0,
                      0);
                  }
                  else
                  {
                    (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("R_GN_HEAD_SHOT", -1, 0, 0);
                  }
                  break;
                case 47:
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                    this,
                    "GN_RISING_SHOT",
                    -1,
                    0,
                    0);
                  break;
                case 53:
                  (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("GN_NAPALM", -1, 0, 0);
                  break;
                default:
                  break;
              }
            }
          }
          else if ( v387 == 11 )
          {
            if ( sub_41A5E0((unsigned int)this + 8577) == 0 || sub_41A5E0((unsigned int)this + 8577) == 2 )
            {
              v471 = *(this + 2129);
              v393 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int))(*this + 1160))(this, *(this + 2129), 0, v393);
              v394 = sub_47EF20(v471, -1, -1, 11, v485);
              v395 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
              v396 = sub_495500(v395);
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(
                this,
                0,
                0,
                v396 + v394,
                v396 + v394);
              if ( sub_41A5E0((unsigned int)this + 8577) == 0 )
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("GN_FASTESTGUN", -1, 0, 0);
            }
            else if ( sub_41A5E0((unsigned int)this + 8577) == 1 && sub_41A5E0((unsigned int)(this + 2136)) == 1
                   || sub_41A5E0((unsigned int)this + 8577) == 3 )
            {
              if ( *((uint8_t *)this + 8596) != 0 )
              {
                if ( *(this + 2151) == 0 )
                {
                  v492 = (void *)sub_42FCB0(228);
                  v506 = 56;
                  if ( v492 != nullptr )
                  {
                    v388 = unknown_libname_2(this + 90);
                    v389 = sub_431920(v388, (char)"Effect/Animation/FastShootDown.ani", 1);
                  }
                  else
                  {
                    v389 = 0;
                  }
                  v506 = -1;
                  *(this + 2151) = v389;
                }
                v390 = *(this + 2151);
              }
              else
              {
                if ( *(this + 2150) == 0 )
                {
                  v492 = (void *)sub_42FCB0(228);
                  v506 = 57;
                  if ( v492 != nullptr )
                  {
                    v391 = unknown_libname_2(this + 90);
                    v392 = sub_431920(v391, (char)"Effect/Animation/FastShootUp.ani", 1);
                  }
                  else
                  {
                    v392 = 0;
                  }
                  v506 = -1;
                  *(this + 2150) = v392;
                }
                v390 = *(this + 2150);
              }
              if ( sub_41A5E0((unsigned int)this + 8577) == 1 )
                (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                  this,
                  1,
                  v390,
                  0,
                  0,
                  0,
                  0);
              else
                (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 204))(
                  this,
                  1,
                  v390,
                  32,
                  8,
                  0,
                  0);
            }
          }
          else if ( v387 == 26 && sub_41A5E0((unsigned int)this + 8577) == 0 )
          {
            v472 = *(this + 2129);
            v397 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
            (*(void (/*thiscall*/ **)(int *, uint32_t, int, int))(*this + 1160))(this, *(this + 2129), 1, v397);
            v508 = (double)(int)sub_47EF20(v472, -1, -1, 11, v485) * 0.0099999998 + 1.0;
            v398 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v399 = (uint64_t)((double)sub_495500(v398) * v508);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(this, 0, 0, v399, v399);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8));
            v492 = (void *)sub_42FCB0(228);
            v506 = 58;
            if ( v492 != nullptr )
            {
              v400 = unknown_libname_2(this + 90);
              v401 = sub_431920(v400, (char)"Effect/Animation/CounterShoot.ani", 1);
            }
            else
            {
              v401 = 0;
            }
            v506 = -1;
            v492 = (void *)sub_44B6C0(284);
            v506 = 59;
            if ( v492 != nullptr )
              v402 = (int *)sub_44E1F0(v401, 1);
            else
              v402 = nullptr;
            v403 = *(this + 29);
            v506 = -1;
            sub_45FE80(v403, (int)v402, 2, 0, (int)v402, (int)this, 0);
            v404 = *v402;
            v484 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int *))(v404 + 148))(v402);
            v405 = *v402;
            v477 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 95;
            v406 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
            v407 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v406);
            (*(void (/*thiscall*/ **)(int *, int))(v405 + 112))(v402, v407);
            (*(void (/*thiscall*/ **)(int *, int, int *, int))(*this + 1160))(this, 26, this, -1);
            sub_47DCD0(v477, v484);
          }
          v419 = *(this + 2129);
          if ( v419 != -1 && v419 != 11 )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
          return;
        case 10:
          if ( *(this + 1953) == 0 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 1954));
            v448 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1954));
            v449 = *(this + 1954);
            if ( v449 == 43 )
            {
              v450 = *(this + 1952);
              if ( v450 != 0 )
              {
                if ( v450 == 1 )
                {
                  v451 = sub_47EF20(0, v448, -1, -1, 11);
                  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 944))(this, 1, v451);
                  *((uint8_t *)this + 9500) = 1;
                  *((uint8_t *)this + 9501) = 0;
                  *((uint8_t *)this + 9502) = 0;
                  sub_698F90((int)(this + 2372), v451, 0);
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "GN_CAMOUFLAGE",
                  -1,
                  0,
                  0);
              }
            }
            else if ( v449 == 45 )
            {
              v452 = *(this + 1952);
              if ( v452 != 0 )
              {
                if ( v452 == 1 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
                {
                  v453 = *this;
                  v454 = sub_47E9D0(1);
                  v455 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 1140))(
                           this,
                           45,
                           0,
                           0,
                           0,
                           0,
                           v454,
                           4,
                           0,
                           0,
                           0);
                  (*(void (/*thiscall*/ **)(int *, int, int))(v453 + 580))(this, 22206, v455);
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                  this,
                  "GN_URANIUM_BOMBER",
                  -1,
                  0,
                  0);
              }
            }
            else if ( v449 == 50 && *(this + 1952) == 1 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
                (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
                  this,
                  48015,
                  50,
                  0,
                  0,
                  0,
                  0,
                  0,
                  4,
                  0,
                  0,
                  0);
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*this + 212))(this, "BOMB_AREA", -1, 0);
              v456 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, 50, 0, v456);
              v457 = (double)(int)sub_47EF20(50, -1, -1, 11, 0);
              v458 = 0;
              do
              {
                v510 = v458 + 1;
                sprintf(Buffer, "Effect/Animation/RobotsExplosion%d.ani", v458 + 1);
                v492 = (void *)sub_42FCB0(228);
                v506 = 62;
                if ( v492 != nullptr )
                {
                  v459 = unknown_libname_2(this + 90);
                  v460 = sub_431920(v459, (char)Buffer, 1);
                }
                else
                {
                  v460 = 0;
                }
                v506 = -1;
                v507 = v457 * 0.0018867925;
                sub_4922F0(v507);
                v492 = (void *)sub_44B6C0(284);
                v506 = 63;
                if ( v492 != nullptr )
                  v461 = (int *)sub_44E1F0(v460, 1);
                else
                  v461 = nullptr;
                v462 = *v461;
                v506 = -1;
                *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v462 + 36))(v461) + 8) = 2;
                sub_45FE80(*(this + 29), -1, 2, 0, (int)v461, 0, 0);
                v463 = *v461;
                v464 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
                (*(void (/*thiscall*/ **)(int *, int))(v463 + 148))(v461, v464);
                v465 = *v461;
                v466 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
                v467 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v466);
                v468 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v467);
                (*(void (/*thiscall*/ **)(int *, int))(v465 + 112))(v461, v468);
                v458 = v510;
              }
              while ( v510 < 3 );
            }
          }
          return;
        case 12:
          v445 = *(this + 2163);
          if ( v445 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)v445 + 80))() != 0 )
          {
            v474 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 37, -1);
            (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
            *(this + 114) = sub_47EF20(37, 1, v474, -1, 11);
          }
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1812));
          v446 = *(this + 30);
          v447 = sub_491C70(v446, *(this + 2160));
          sub_493A60(v446, v447);
          sub_4939E0(*(this + 30), 1);
          return;
        case 14:
          v469 = *(this + 1991);
          switch ( v469 )
          {
            case 175:
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_LEAP_BUFF",
                -1,
                0,
                0);
              break;
            case 176:
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_ANCIENT_MEMORY",
                -1,
                0,
                0);
              break;
            case 1:
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_FLAMESHOT",
                -1,
                0,
                0);
              break;
            case 2:
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_ICESHOT",
                -1,
                0,
                0);
              break;
            case 30:
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "GN_SILVERSHOT",
                -1,
                0,
                0);
              break;
            default:
              break;
          }
          return;
        default:
          return;
      }
    case 23:
      if ( v487 == 23 )
      {
        v315 = sub_699000((int)(this + 1640));
        *(this + 2140) = sub_4C0DF0(0) + v315;
        v316 = sub_41A5E0((unsigned int)(this + 2083));
        *(this + 2141) = v316 + *(this + 2140) + *(this + 2361) + sub_4C0DF0(1);
        LOBYTE(a4) = 0;
        LOBYTE(a5) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 15);
        *(float *)&v491 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 15));
        v304 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
        v305 = sub_4954C0(v304);
        v306 = sub_47EF20(1, v491, -1, -1, 11) + v305;
        *(this + 2361) = sub_47EF20(2, v491, -1, -1, 11);
        v307 = (void *)sub_47EF20(3, v491, -1, -1, 11);
        v308 = *this;
        v492 = v307;
        v309 = (double)(int)v307;
        v310 = *(this + 1554);
        *((float *)this + 2363) = v309 * 0.000099999997;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(v308 + 196))(this, *(uint32_t *)(v310 + 92));
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 143, 119, 1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 114, 95, 1, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, v306, v306);
        v311 = *this;
        *(this + 2129) = 15;
        *(this + 2359) = 4;
        *(this + 2360) = 0;
        *(this + 2140) = -1;
        *(this + 2141) = 0;
        *(this + 2364) = 0;
        *(this + 2365) = 0;
        *(this + 2362) = -1;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v311 + 212))(this, "GN_MOVESHOT", -1, 0, 0);
        v504 = 15;
        v503 = 0;
        LOBYTE(Block[0]) = 0;
        v312 = *this;
        v506 = 49;
        v313 = (*(int (/*thiscall*/ **)(int *))(v312 + 1096))(this);
        if ( v313 >= 0 )
        {
          if ( v313 <= 3 )
          {
            sub_406D60("GUN_DRAW3");
          }
          else if ( v313 == 4 )
          {
            sub_406D60("BOWGUN_DRAW3");
          }
        }
        v314 = (void **)Block[0];
        if ( v504 < 0x10 )
          v314 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v314, -1, 0, 0);
        v506 = -1;
        sub_501490(v499);
      }
      goto LABEL_482;
    case 25:
      v317 = **(uint32_t **)(a3 + 4);
      if ( v317 == 27 )
      {
        *(this + 2366) = 60002;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_01", -1, 0, 0);
      }
      else if ( **(uint32_t **)(a3 + 4) == 28 )
      {
        v318 = *this;
        *(this + 2366) = 60003;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v318 + 212))(this, "ROBOT_SET_02", -1, 0, 0);
      }
      else if ( **(uint32_t **)(a3 + 4) == 29 )
      {
        *(this + 2366) = 60004;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_03", -1, 0, 0);
      }
      *(this + 2368) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      *(this + 2369) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
      v319 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, v317, 0, v319);
      *(this + 2367) = sub_47EF20(v317, -1, -1, 11, v485);
      v486 = *(uint32_t *)(*(this + 1554) + 128);
      (*(void (/*thiscall*/ **)(int *))(*this + 196))(this);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      v320 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, v317);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 1160))(this, v317, v320);
      v489 = COERCE_FLOAT(sub_4B1C40(v486));
      v492 = *(void **)(*(this + 30) + 36);
      v321 = *this;
      v485 = 3;
      *(float *)&v491 = (double)(int)v492 / (double)SLODWORD(v489);
      v322 = (*(int (/*thiscall*/ **)(int *))(v321 + 672))(this);
      v489 = COERCE_FLOAT(sub_495540(v322));
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t))(v321 + 888))(
        this,
        (uint64_t)((double)SLODWORD(v489) * *(float *)&v491) >> 32,
        0,
        0,
        1000,
        (uint64_t)((double)SLODWORD(v489) * *(float *)&v491));
      (*(void (/*thiscall*/ **)(int *, void *, int))(*this + 992))(this, v492, 1);
      *(this + 2371) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 12);
      goto LABEL_482;
    case 26:
      *(this + 2129) = **(uint32_t **)(a3 + 4);
      v52 = *(this + 1554);
      *(this + 2242) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      v53 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8);
      sub_4926A0(*(uint32_t *)(v52 + 64));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 64));
      v54 = *(this + 2129);
      if ( v54 == 40 )
      {
        sub_4C4890(this, 4, 16);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, int, int))(*this + 876))(
          this,
          0,
          250,
          0,
          0,
          -500,
          1);
      }
      else if ( v54 == 39 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 39);
        sub_47DD30(this);
        sub_4C4890(this, 2, 16);
        if ( *(this + 2345) == 0 )
        {
          v492 = (void *)sub_42FCB0(228);
          v506 = 4;
          if ( v492 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v55 = sub_431920(
                      (uint8_t)this + 108,
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",
                      1);
            else
              v55 = sub_431920(
                      *(this + 91),
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",
                      1);
          }
          else
          {
            v55 = 0;
          }
          v506 = -1;
          *(this + 2345) = v55;
        }
        if ( *(this + 2346) == 0 )
        {
          v492 = (void *)sub_42FCB0(228);
          v506 = 5;
          if ( v492 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              v56 = sub_431920(
                      (uint8_t)this + 108,
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani",
                      1);
            else
              v56 = sub_431920(*(this + 91), (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani", 1);
          }
          else
          {
            v56 = 0;
          }
          v506 = -1;
          *(this + 2346) = v56;
        }
        sub_4926A0(*(this + 2345));
        sub_4926A0(*(this + 2346));
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          -1,
          *(this + 2345),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          1,
          *(this + 2346),
          0,
          0,
          0,
          0);
        v57 = sub_423A80(100, 400, v53, *(this + 2356));
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, int, int))(*this + 876))(
          this,
          0,
          v57,
          0,
          0,
          -500,
          1);
        if ( v57 > 150 )
        {
          v492 = (void *)sub_42FCB0(228);
          v506 = 6;
          if ( v492 != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              LOBYTE(v58) = (uint8_t)this + 108;
            else
              v58 = *(this + 91);
            v59 = sub_431920(v58, (char)"Effect/Animation/TurningShoot.ani", 1);
          }
          else
          {
            v59 = 0;
          }
          v506 = -1;
          v492 = (void *)sub_44B6C0(284);
          v506 = 7;
          if ( v492 != nullptr )
            v60 = (int *)sub_44E1F0(v59, 1);
          else
            v60 = nullptr;
          v61 = *(this + 29);
          v506 = -1;
          sub_45FE80(v61, (int)v60, 2, 0, (int)v60, (int)this, 0);
          v62 = *v60;
          v63 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          v64 = sub_432E50(v63);
          (*(void (/*thiscall*/ **)(int *, int))(v62 + 148))(v60, v64);
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 130;
          else
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 130;
          v66 = *v60;
          v491 = v65;
          v67 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
          v68 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v67);
          (*(void (/*thiscall*/ **)(int *, int, int))(v66 + 112))(v60, v491, v68);
        }
      }
      v69 = *this;
      v70 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
      v71 = sub_432E50(v70);
      (*(void (/*thiscall*/ **)(int *, int))(v69 + 896))(this, v71);
      v72 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
      v73 = *(uint32_t *)v72;
      v74 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v75 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v74);
      (*(void (/*thiscall*/ **)(int, int))(v73 + 40))(v72, v75);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v72 + 12))(v72, 0);
      (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)v72 + 92))(v72, &v501);
      v506 = 8;
      sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);
LABEL_232:
      v506 = -1;
      sub_5E5260((void **)&v501);
      goto LABEL_482;
    case 27:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 132));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      v323 = *this;
      *(this + 2129) = 48;
      (*(void (/*thiscall*/ **)(int *, int))(v323 + 1160))(this, 48);
      v324 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
      v325 = sub_495500(v324);
      *(this + 2140) = 1000 * sub_47E9D0(0) / v325;
      v326 = 1000 * sub_47E9D0(1);
      *(this + 2148) = *(this + 2140) + v326 / sub_4C0EB0(this);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_CROSS_SHOT", -1, 0, 0);
      goto LABEL_482;
    default:
      goto LABEL_482;
  }
}

