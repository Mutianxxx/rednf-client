// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_583B90_sub_583B90.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x583B90）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 4518 行；字符串证据 5 条；外调 6 个
//   串: "Age %d isPCRoom %d channelType %d"
//   串: "Error %d"
//   串: "ClearQuestNumber %d"
//   串: "TownIndex %d"
//   串: "CHARACTER_CREATED"
//   调: sub_583B90 sub_404A90 sub_404AD0 sub_6567F0 sub_41D300 sub_45DA30
//   case 分支地图（共 120 处）:
//     L559  case 0x10:
//     L563  case 0x12:
//     L567  case 0x16:
//     L571  case 0x17:
//     L749  case 0x12:
//     L753  case 0x13:
//     L757  case 0x16:
//     L760  case 0x17:
//     L764  case 0x18:
//     L795  case 0x13:
//     L799  case 0x15:
//     L803  case 0x16:
//     L807  case 0x25:
//     L896  case 0x12:
//     L914  case 0x13:
//     L932  case 0x37:
//     L952  case 0x38:
//     L1020  case 0x12:
//     L1038  case 0x13:
//     L1114  case 0x13:
//     L1182  case 0x15:
//     L1186  case 0x13:
//     L1194  case 0xE:
//     L1197  case 0x11:
//     L1314  case 0x11:
//     L1318  case 0x13:
//     L1322  case 0x17:
//     L1469  case 0x11:
//     L1474  case 0x12:
//     L1477  case 0x13:
//     L1483  case 0xE:
//     L1486  case 0x17:
//     L1622  case 0xA:
//     L1626  case 0x11:
//     L1628  case 0x13:
//     L1630  case 0x37:
//     L1713  case 0xA:
//     L1717  case 0x11:
//     L1721  case 0x13:
//     L1788  case 0xA:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x583B90 sub_583B90  size=27453
// ------------------------------------------------------------
int /*userpurge*/ sub_583B90@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<esi>, unsigned int a4, int a5)
{
  int v5; // eax
  uint8_t v7; // al
  int *v8; // edx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  bool v12; // bl
  int v13; // eax
  DWORD v14; // ecx
  char *v15; // eax
  char v16; // cl
  int v17; // eax
  int v18; // eax
  char *v19; // eax
  char v20; // cl
  char *v21; // eax
  char v22; // cl
  char *v23; // eax
  char v24; // cl
  int v25; // eax
  int v26; // eax
  char *v27; // eax
  char v28; // cl
  int v29; // eax
  char *v30; // eax
  char v31; // cl
  int v32; // eax
  int v33; // eax
  int v34; // esi
  int v35; // ebx
  int i; // edi
  int v37; // edi
  int v38; // eax
  int *v39; // esi
  int v40; // eax
  int *v41; // esi
  char *v42; // eax
  char v43; // cl
  uint32_t *v44; // esi
  int v45; // eax
  uint32_t *v46; // esi
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // esi
  const char *v57; // eax
  char *v58; // eax
  char v59; // cl
  char *v60; // eax
  char v61; // cl
  char *v62; // eax
  char v63; // cl
  char *v64; // eax
  char v65; // cl
  char *v66; // eax
  char v67; // cl
  char *v68; // eax
  char v69; // cl
  int v70; // esi
  int v71; // esi
  const char *v72; // eax
  uint32_t *v73; // esi
  int v74; // eax
  char *v75; // eax
  char v76; // cl
  char *v77; // eax
  char v78; // cl
  char *v79; // eax
  char v80; // cl
  int v81; // eax
  int v82; // ebx
  uint32_t *v83; // eax
  uint32_t *v84; // esi
  int v85; // eax
  int v86; // ecx
  uint32_t *v87; // edx
  int v88; // ecx
  const char *v89; // eax
  char v90; // al
  int v91; // ecx
  int v92; // edi
  int v93; // eax
  int *v94; // eax
  char *v95; // eax
  char v96; // cl
  char v97; // cl
  char *v98; // eax
  char v99; // cl
  char *v100; // eax
  char v101; // cl
  uint32_t *v102; // eax
  uint32_t *v103; // eax
  char *v104; // eax
  char v105; // cl
  int *v106; // esi
  int *v107; // eax
  char *v108; // eax
  char v109; // cl
  int *v110; // eax
  int v111; // eax
  int v112; // esi
  int v113; // eax
  bool v114; // zf
  int *v115; // ecx
  char *v116; // eax
  char v117; // cl
  int j; // esi
  int *v119; // esi
  int *v120; // eax
  char *v121; // eax
  char v122; // cl
  int k; // esi
  char *v124; // eax
  char v125; // cl
  int v126; // eax
  uint32_t *v127; // esi
  uint32_t *v128; // edi
  uint32_t *v129; // eax
  char *v130; // eax
  char v131; // cl
  uint32_t *v132; // eax
  int v133; // esi
  char v134; // al
  int v135; // edx
  int v136; // eax
  void *v137; // eax
  int v138; // esi
  int v139; // eax
  int v140; // eax
  int v141; // eax
  int v142; // edi
  int v143; // eax
  int v144; // esi
  void *v145; // eax
  int *v146; // eax
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int v150; // eax
  int *v151; // esi
  int v152; // eax
  int v153; // edx
  int v154; // eax
  void *v155; // eax
  int v156; // eax
  int v157; // esi
  unsigned int v158; // edi
  int v159; // eax
  int v160; // eax
  int v161; // edi
  int v162; // ebx
  int v163; // esi
  int v164; // eax
  int v165; // eax
  int v166; // ebx
  int v167; // eax
  int v168; // esi
  int v169; // eax
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // eax
  int v175; // esi
  int v176; // eax
  int v177; // eax
  int v178; // eax
  int v179; // eax
  int v180; // eax
  int v181; // edi
  int v182; // esi
  int v183; // eax
  int v184; // eax
  int v185; // eax
  int v186; // eax
  int v187; // edi
  int v188; // esi
  char v189; // al
  int v190; // edx
  int v191; // eax
  int v192; // eax
  void *v193; // eax
  int v194; // eax
  int v195; // eax
  int v196; // eax
  int v197; // eax
  int v198; // eax
  int v199; // eax
  int v200; // eax
  int v201; // edi
  int v202; // esi
  char v203; // al
  int v204; // edx
  int v205; // eax
  int v206; // eax
  void *v207; // eax
  int v208; // eax
  int16_t v209; // di
  int v210; // esi
  int v211; // eax
  int v212; // esi
  char v213; // al
  int v214; // edx
  int v215; // eax
  void *v216; // eax
  int v217; // eax
  int v218; // eax
  int v219; // eax
  int v220; // eax
  char *v221; // eax
  char v222; // cl
  int v223; // esi
  int v224; // eax
  char v225; // al
  int v226; // eax
  const char *v227; // eax
  const char *v228; // eax
  int v229; // esi
  uint32_t *v230; // eax
  int v231; // ebx
  int v232; // eax
  int v233; // ebx
  uint32_t *v234; // esi
  int v235; // eax
  const char *v236; // eax
  int v237; // ebx
  int v238; // esi
  const char *v239; // eax
  const char *v240; // eax
  const char *v241; // eax
  const char *v242; // eax
  const char *v243; // eax
  const char *v244; // eax
  const char *v245; // eax
  const char *v246; // eax
  int v247; // eax
  const char *v248; // eax
  int v249; // esi
  int v250; // eax
  int v251; // eax
  int v252; // eax
  int v253; // ebx
  int *v254; // esi
  char v255; // al
  int v256; // edx
  int v257; // eax
  int v258; // eax
  int v259; // esi
  const char *v260; // eax
  int v261; // eax
  int v262; // eax
  int v263; // eax
  int v264; // esi
  const char *v265; // eax
  int v266; // eax
  int v267; // ebx
  const char *v268; // eax
  int v269; // eax
  int v270; // esi
  int v271; // eax
  int v272; // eax
  int v273; // eax
  int v274; // ebx
  int v275; // edi
  int v276; // esi
  char v277; // al
  int v278; // edx
  int v279; // eax
  int v280; // eax
  void *v281; // eax
  int v282; // esi
  int v283; // eax
  int v284; // eax
  const char *v285; // eax
  int v286; // eax
  int v287; // eax
  uint32_t *v288; // esi
  int v289; // eax
  int v290; // ebx
  signed int v291; // edi
  uint8_t *v292; // esi
  uint32_t *v293; // esi
  int v294; // eax
  int v295; // esi
  int v296; // edi
  int v297; // ebx
  int v298; // eax
  int v299; // eax
  char v300; // cl
  uint32_t *v301; // esi
  int v302; // eax
  int v303; // esi
  int v304; // eax
  int v305; // eax
  bool v306; // bl
  int v307; // edi
  int v308; // eax
  int v309; // edi
  int v310; // eax
  int v311; // eax
  int v312; // esi
  int m; // esi
  int v314; // eax
  int v315; // esi
  int v316; // eax
  char *v317; // eax
  const char *v318; // eax
  int v319; // eax
  int v320; // eax
  int v321; // eax
  char *v322; // eax
  int v323; // eax
  int v324; // edx
  int v325; // eax
  char *v326; // eax
  uint8_t n; // bl
  char *v328; // eax
  char *v329; // eax
  int v330; // eax
  const char *v331; // edi
  const char *v332; // eax
  int v333; // esi
  int v334; // eax
  int v335; // eax
  int v336; // eax
  int v337; // eax
  int v338; // eax
  int v339; // eax
  uint8_t *v340; // eax
  uint8_t *v341; // esi
  char v342; // al
  int v343; // eax
  int v344; // eax
  int v345; // eax
  int v346; // eax
  int v347; // eax
  int v348; // eax
  char v349; // bl
  int ii; // esi
  int jj; // esi
  char *v352; // eax
  int v353; // eax
  const char *v354; // eax
  int v355; // eax
  int v356; // eax
  int v357; // eax
  int v358; // eax
  int v359; // esi
  char *v360; // eax
  int v361; // eax
  char *v362; // eax
  const char *v363; // eax
  int v364; // eax
  char *v365; // eax
  const char *v366; // eax
  char *v367; // eax
  int v368; // eax
  const char *v369; // eax
  char *v370; // edx
  int v371; // eax
  int v372; // eax
  int v373; // eax
  int v374; // eax
  int v375; // eax
  int v376; // eax
  const char *v377; // eax
  char *v378; // eax
  const char *v379; // eax
  const char *v380; // eax
  int v381; // esi
  int *v382; // ebx
  int v383; // edi
  int v384; // eax
  int v385; // eax
  int v386; // eax
  int v387; // eax
  int v388; // eax
  int v389; // eax
  int v390; // eax
  const char *v391; // eax
  int v392; // esi
  int *v393; // ebx
  int v394; // eax
  int v395; // eax
  int v396; // esi
  int v397; // eax
  uint32_t *v398; // eax
  int v399; // edx
  int v400; // edi
  int v401; // eax
  int v402; // esi
  int v403; // eax
  int v404; // eax
  int v405; // eax
  int v406; // ecx
  int v408; // [esp-18h] [ebp-384h]
  int v409; // [esp-18h] [ebp-384h]
  int v410; // [esp-18h] [ebp-384h]
  int v411; // [esp-14h] [ebp-380h]
  int v412; // [esp-10h] [ebp-37Ch]
  int v413; // [esp-10h] [ebp-37Ch]
  uint32_t *v414; // [esp-10h] [ebp-37Ch]
  int v415; // [esp-Ch] [ebp-378h]
  uint32_t *v416; // [esp-Ch] [ebp-378h]
  unsigned int v417; // [esp-Ch] [ebp-378h]
  unsigned int v418; // [esp-Ch] [ebp-378h]
  int v419; // [esp-Ch] [ebp-378h]
  unsigned int v420; // [esp-Ch] [ebp-378h]
  unsigned int v421; // [esp-Ch] [ebp-378h]
  unsigned int v422; // [esp-Ch] [ebp-378h]
  unsigned int v423; // [esp-Ch] [ebp-378h]
  unsigned int v424; // [esp-Ch] [ebp-378h]
  unsigned int v425; // [esp-Ch] [ebp-378h]
  unsigned int v426; // [esp-Ch] [ebp-378h]
  unsigned int v427; // [esp-Ch] [ebp-378h]
  uint32_t *v428; // [esp-Ch] [ebp-378h]
  uint32_t *v429; // [esp-Ch] [ebp-378h]
  uint32_t *v430; // [esp-Ch] [ebp-378h]
  int v431; // [esp-Ch] [ebp-378h]
  uint32_t *v432; // [esp-Ch] [ebp-378h]
  int v433; // [esp-Ch] [ebp-378h]
  int v434; // [esp-Ch] [ebp-378h]
  int v435; // [esp-Ch] [ebp-378h]
  int v436; // [esp-Ch] [ebp-378h]
  int v437; // [esp-8h] [ebp-374h]
  int v438; // [esp+4h] [ebp-368h] BYREF
  int *v439; // [esp+8h] [ebp-364h] BYREF
  char v440[4]; // [esp+Ch] [ebp-360h] BYREF
  unsigned int v441; // [esp+10h] [ebp-35Ch] BYREF
  uint8_t v442; // [esp+17h] [ebp-355h] BYREF
  char ArgList[4]; // [esp+18h] [ebp-354h] BYREF
  unsigned int v444; // [esp+1Ch] [ebp-350h] BYREF
  int v445; // [esp+20h] [ebp-34Ch] BYREF
  char v446[4]; // [esp+24h] [ebp-348h] BYREF
  int v447; // [esp+28h] [ebp-344h] BYREF
  char v448[256]; // [esp+2Ch] [ebp-340h] BYREF
  char v449[128]; // [esp+12Ch] [ebp-240h] BYREF
  char v450[128]; // [esp+1ACh] [ebp-1C0h] BYREF
  char Buffer[128]; // [esp+22Ch] [ebp-140h] BYREF
  char v452[64]; // [esp+2ACh] [ebp-C0h] BYREF
  char v453[61]; // [esp+2ECh] [ebp-80h] BYREF
  int16_t v454; // [esp+329h] [ebp-43h]
  char v455; // [esp+32Bh] [ebp-41h]
  char Destination[12]; // [esp+32Ch] [ebp-40h] BYREF
  void *v457[5]; // [esp+338h] [ebp-34h] BYREF
  char v458[4]; // [esp+34Ch] [ebp-20h] BYREF
  __time64_t Time; // [esp+350h] [ebp-1Ch] BYREF
  int v460; // [esp+35Ch] [ebp-10h]
  int v461; // [esp+368h] [ebp-4h]

  v460 = dword_796E50;
  v5 = *(uint8_t *)(a4 + 1) - 1;
  v439 = (int *)a1;
  v437 = a3;
  switch ( v5 )
  {
    case 0:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(v445) = 0;
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&v445 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        *(uint32_t *)v446 = 0;
        sub_404AD0(v446);
        sub_6567F0(*(int *)v446);
        off_77F3FC("Age %d isPCRoom %d channelType %d", HIBYTE(v445), HIBYTE(a4), HIBYTE(a5));
        v7 = HIBYTE(a5);
        if ( HIBYTE(a5) >= 4u )
        {
          v7 = 4;
          HIBYTE(a5) = 4;
        }
        v8 = v439;
        v439[87] = v7;
        v9 = *(uint32_t *)(dword_8F7A24 + 284);
        v10 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 36) + 12);
        v11 = *(uint32_t *)(dword_8F7A24 + 288);
        v12 = false;
        *(uint32_t *)ArgList = v11;
        if ( v9 == v10 )
          v12 = v11 != -1;
        if ( *(uint32_t *)(dword_8F7B08 + 456) == 2 )
          v12 = false;
        if ( v8[3] == 5 && !v12 )
          sub_41D300((int *)dword_8F7A24, 0);
        *(uint8_t *)(v439[4] + 48) = 1;
        sub_45DA30((int)dword_8F8524);
        if ( v12 )
        {
          sub_46BCB0(*(uint32_t *)ArgList, 1);
        }
        else
        {
          sub_423200(dword_8F7B08, 8);
          *(uint32_t *)v440 = 0xFFFF;
          sub_423290(v440, 2);
          HIBYTE(v447) = 2;
          sub_423290((char *)&v447 + 3, 1);
          sub_423380(dword_8F7B08);
        }
        off_77F3FC(
          "isSkipCharacterSelect %d, lastPlayedServer %d lastPlayedCharacterSlotIndex %d curServer %d",
          v12,
          v9,
          *(uint32_t *)ArgList,
          v10);
        *((uint8_t *)v439 + 92) = 0;
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( *(uint32_t *)(a1 + 12) != 0 )
          sub_41D300((int *)dword_8F7A24, 0);
        switch ( HIBYTE(a5) )
        {
          case 2:
            *(uint32_t *)(dword_8F7B08 + 456) = 1;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 4:
            *(uint32_t *)(dword_8F7B08 + 456) = 2;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 5:
            *(uint32_t *)(dword_8F7B08 + 456) = 3;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 6:
            *(uint32_t *)(dword_8F7B08 + 456) = 4;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 7:
            *(uint32_t *)(dword_8F7B08 + 456) = 5;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 0x10:
            *(uint32_t *)(dword_8F7B08 + 456) = 6;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 0x12:
            *(uint32_t *)(dword_8F7B08 + 456) = 7;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 0x16:
            *(uint32_t *)(dword_8F7B08 + 456) = 8;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          case 0x17:
            *(uint32_t *)(dword_8F7B08 + 456) = 9;
            *(uint8_t *)(a1 + 92) = 0;
            break;
          default:
            *(uint32_t *)(dword_8F7B08 + 456) = 10;
            *(uint8_t *)(a1 + 92) = 0;
            break;
        }
      }
      return 1;
    case 2:
      v114 = (uint8_t)a5 == 0;
      *(uint8_t *)(dword_8F7B08 + 466) = 0;
      if ( !v114 )
      {
        if ( *(uint32_t *)(a1 + 12) != 5 )
          sub_41C1E0();
        sub_6989F0(dword_8F7B08);
        goto LABEL_32;
      }
      sub_41C860((uint32_t *)a1);
      return 1;
    case 3:
      v34 = 0;
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 == 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 21 )
        {
          v42 = (char *)sub_422E70(694);
        }
        else
        {
          if ( HIBYTE(a5) != 8 )
          {
LABEL_94:
            *(uint8_t *)(*(uint32_t *)(a1 + 16) + 96) = 0;
            return 1;
          }
          v42 = (char *)sub_422E70(2040);
        }
        off_77F3F8(v43, v42);
        goto LABEL_94;
      }
      HIBYTE(a4) = 0;
      HIBYTE(v444) = 0;
      v445 = 0;
      v441 = 0;
      *(uint32_t *)v440 = 0;
      v447 = 0;
      *(uint32_t *)ArgList = 0;
      v438 = 0;
      sub_404AB0(&v445);
      sub_404AB0(&v441);
      sub_404AB0(v440);
      sub_404A90((uint8_t *)&v444 + 3);
      v35 = 0;
      if ( HIBYTE(v444) != 0 )
      {
        do
        {
          sub_404A90((uint8_t *)&a5 + 3);
          sub_404AD0(&v438);
          off_77F3FC("premium %d : premiumType %d, premiumEndTime %d", v35, HIBYTE(a5), v438);
          sub_41C470((uint8_t *)a1, HIBYTE(a5), 1);
          sub_41C490((uint32_t *)a1, HIBYTE(a5), v438);
          if ( HIBYTE(a5) == 5 )
          {
            sub_461180(1);
          }
          else if ( HIBYTE(a5) != 8 )
          {
            sub_461170(1);
          }
          ++v35;
        }
        while ( v35 < HIBYTE(v444) );
      }
      sub_404AD0(ArgList);
      off_77F3FC(
        "MyServerId %d, Fatigue %d, FatigueMax %d, Cash %d",
        (uint16_t)v445,
        (uint16_t)v441,
        *(uint16_t *)v440,
        *(uint32_t *)ArgList);
      word_8F7C10 = v441;
      LOWORD(word_77F804) = v445;
      word_8F7C14 = *(uint16_t *)v440;
      dword_8F7C0C = *(uint32_t *)ArgList;
      if ( *(int *)ArgList < 0 )
      {
        off_77F3FC(aCriticalError_31, *(uint32_t *)ArgList);
        dword_8F7C0C = 0;
      }
      for ( i = 3; i != 0; --i )
      {
        v442 = 0;
        *(uint32_t *)v446 = 0;
        sub_404AB0(v446);
        sub_404A90(&v442);
        off_77F3FC("QuestTrigger %d, QuestIndex %d", v442, *(uint16_t *)v446);
        if ( v442 != 0xFFFF )
          sub_47D060(*(uint16_t *)v446, v442);
      }
      sub_404AB0(&v447);
      off_77F3FC("ClearQuestNumber %d", (uint16_t)v447);
      if ( (uint16_t)v447 != 0 )
      {
        do
        {
          *(uint32_t *)v446 = 0;
          sub_404AB0(v446);
          v37 = *(uint16_t *)v446;
          HIDWORD(Time) = *(uint16_t *)v446;
          *(uint32_t *)sub_468BA0((char *)&Time + 4) = v37;
          ++v34;
        }
        while ( v34 < (uint16_t)v447 );
      }
      sub_404A90((uint8_t *)&a4 + 3);
      off_77F3FC("TownIndex %d", HIBYTE(a4));
      v38 = sub_4CE8A0((uint32_t *)dword_8F84F0, HIBYTE(a4));
      if ( v38 != 0 )
      {
        v39 = *(int **)(v38 + 100);
        v40 = *v39;
        *(uint32_t *)v446 = *v39;
        if ( *(int **)v446 != v39 )
        {
          while ( *(uint32_t *)(v40 + 48) != 1 )
          {
            sub_4CE5F0((int *)v446);
            v40 = *(uint32_t *)v446;
            if ( *(int **)v446 == v39 )
              goto LABEL_87;
          }
          sub_45D190(SHIBYTE(a4), *(void **)(v40 + 16));
        }
      }
      else
      {
        off_77F3FC(aCriticalError_32);
      }
LABEL_87:
      v41 = v439;
      sub_41D300(v439, 1);
      *(uint8_t *)(v41[4] + 96) = 0;
      if ( HIBYTE(a5) != 0 )
        sub_461190(*((uint32_t *)dword_8F8528 + 4));
      return 1;
    case 4:
      if ( (uint8_t)a5 != 0 )
      {
        v13 = sub_422E70(680);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v13, 0);
        sub_432EA0("CHARACTER_CREATED", -1, 0, 0);
        *(uint8_t *)(*(uint32_t *)(a1 + 16) + 276) = 1;
        sub_46C0E0(0);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_40BE20(v14, "\nError %d", HIBYTE(a5));
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 2:
            v15 = (char *)sub_422E70(681);
            off_77F3F8(v16, v15);
            break;
          case 4:
            v17 = sub_422E70(682);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v17, 0);
            break;
          case 0x12:
            v18 = sub_422E70(683);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v18, 0);
            break;
          case 0x13:
            v19 = (char *)sub_422E70(684);
            off_77F3F8(v20, v19);
            break;
          case 0x16:
LABEL_1083:
            break;
          case 0x17:
            v21 = (char *)sub_422E70(685);
            off_77F3F8(v22, v21);
            break;
          case 0x18:
            v23 = (char *)sub_422E70(686);
            off_77F3F8(v24, v23);
            v25 = sub_422E70(687);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v25, 0);
            break;
          default:
            goto LABEL_1083;
        }
      }
      return 1;
    case 5:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Index %d", HIBYTE(a5));
        v26 = sub_422E70(688);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v26, 0);
        sub_432EA0("CHARACTER_DELETED", -1, 0, 0);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 2:
            v27 = (char *)sub_422E70(689);
            off_77F3F8(v28, v27);
            break;
          case 0x13:
            v29 = sub_422E70(690);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v29, 0);
            break;
          case 0x15:
            v30 = (char *)sub_422E70(691);
            off_77F3F8(v31, v30);
            break;
          case 0x16:
            v32 = sub_422E70(692);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v32, 0);
            break;
          case 0x25:
            v33 = sub_422E70(693);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v33, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 6:
      if ( (uint8_t)a5 != 0 )
      {
LABEL_32:
        sub_41D320(a1);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
          off_77F3FC(aFail_12);
      }
      return 1;
    case 8:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AD0(&a5);
        off_77F3FC("Money %d", a5);
        (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          a5);
        if ( dword_8F7C04 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, 100);
          if ( *(uint32_t *)(a1 + 12) == 1 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
          v44 = *((uint32_t **)dword_8F8528 + 7);
          v45 = sub_422E70(695);
          sub_43BEE0(v44, v45, -6567706, 0, -1);
          sub_432EA0("STAMINA_RECOVER", -1, 0, 0);
        }
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 18 )
        {
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(696);
          goto LABEL_983;
        }
        if ( HIBYTE(a5) == 22 )
        {
          v408 = 697;
          goto LABEL_982;
        }
      }
      return 1;
    case 9:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a4) = 0;
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d, PeerRequestType %d", HIBYTE(a4), HIBYTE(a5));
        switch ( HIBYTE(a4) )
        {
          case 3:
            v46 = *((uint32_t **)dword_8F8528 + 7);
            v47 = sub_422E70(698);
            goto LABEL_983;
          case 4:
            if ( HIBYTE(a5) == 0 )
            {
              v408 = 699;
              goto LABEL_982;
            }
            if ( HIBYTE(a5) == 2 )
            {
              v46 = *((uint32_t **)dword_8F8528 + 7);
              v47 = sub_422E70(700);
              goto LABEL_983;
            }
            break;
          case 0x12:
            switch ( HIBYTE(a5) )
            {
              case 0:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(701);
                goto LABEL_983;
              case 1:
                v408 = 702;
                goto LABEL_982;
              case 2:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(703);
                goto LABEL_983;
              default:
                break;
            }
            break;
          case 0x13:
            switch ( HIBYTE(a5) )
            {
              case 0:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(704);
                goto LABEL_983;
              case 1:
                v408 = 705;
                goto LABEL_982;
              case 2:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(706);
                goto LABEL_983;
              default:
                break;
            }
            break;
          case 0x37:
            if ( HIBYTE(a5) != 0 )
            {
              if ( HIBYTE(a5) == 1 )
              {
                v49 = sub_422E70(1345);
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v49, 0);
              }
              else if ( HIBYTE(a5) == 2 )
              {
                v50 = sub_422E70(1346);
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v50, 0);
              }
            }
            else
            {
              v48 = sub_422E70(1344);
              sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v48, 0);
            }
            break;
          case 0x38:
            if ( HIBYTE(a5) != 0 )
            {
              if ( HIBYTE(a5) == 1 )
              {
                v52 = sub_422E70(1348);
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v52, 0);
              }
              else if ( HIBYTE(a5) == 2 )
              {
                v53 = sub_422E70(1349);
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v53, 0);
              }
            }
            else
            {
              v51 = sub_422E70(1347);
              sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v51, 0);
            }
            break;
          default:
            break;
        }
      }
      return 1;
    case 10:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        sub_404AB0(&a4);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("ServerId %d, PeerRequestType %d", (uint16_t)a4, HIBYTE(a5));
        if ( HIBYTE(a5) == 1 )
        {
          sub_4844B0((int *)dword_8F8538);
          v54 = dword_8F8538;
          *(uint16_t *)(dword_8F8538 + 4) = a4;
          *(uint8_t *)(v54 + 36) = 0;
          *(uint8_t *)(v54 + 64) = 0;
          sub_44BBA0(2, 0);
        }
      }
      else
      {
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d, PeerRequestType %d", HIBYTE(a4), HIBYTE(a5));
        switch ( HIBYTE(a4) )
        {
          case 3:
            v46 = *((uint32_t **)dword_8F8528 + 7);
            v47 = sub_422E70(707);
            goto LABEL_983;
          case 4:
            if ( HIBYTE(a5) == 0 )
            {
              v408 = 708;
              goto LABEL_982;
            }
            if ( HIBYTE(a5) == 2 )
            {
              v46 = *((uint32_t **)dword_8F8528 + 7);
              v47 = sub_422E70(709);
              goto LABEL_983;
            }
            break;
          case 0x12:
            switch ( HIBYTE(a5) )
            {
              case 0:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(710);
                goto LABEL_983;
              case 1:
                v408 = 711;
                goto LABEL_982;
              case 2:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(712);
                goto LABEL_983;
              default:
                break;
            }
            break;
          case 0x13:
            switch ( HIBYTE(a5) )
            {
              case 0:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(713);
                goto LABEL_983;
              case 1:
                v408 = 714;
                goto LABEL_982;
              case 2:
                v46 = *((uint32_t **)dword_8F8528 + 7);
                v47 = sub_422E70(715);
                goto LABEL_983;
              default:
                break;
            }
            break;
          default:
            if ( HIBYTE(a4) == 17 && HIBYTE(a5) == 2 )
            {
              v55 = sub_429830((uint16_t)word_77F804);
              v56 = sub_41A5E0(v55 + 53);
              v415 = dword_9B759C[v56]
                   - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C
                                                                                               + 3));
              v57 = (const char *)sub_422E70(716);
              goto LABEL_812;
            }
            break;
        }
      }
      return 1;
    case 11:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 8 )
        {
          v58 = (char *)sub_422E70(717);
          off_77F3F8(v59, v58);
        }
      }
      return 1;
    case 12:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 18 )
        {
          v60 = (char *)sub_422E70(718);
          off_77F3F8(v61, v60);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          v62 = (char *)sub_422E70(719);
          off_77F3F8(v63, v62);
        }
      }
      return 1;
    case 13:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 4:
            v64 = (char *)sub_422E70(720);
            off_77F3F8(v65, v64);
            break;
          case 0x13:
            v66 = (char *)sub_422E70(721);
            off_77F3F8(v67, v66);
            break;
          case 8:
            v68 = (char *)sub_422E70(722);
            off_77F3F8(v69, v68);
            break;
          default:
            break;
        }
      }
      return 1;
    case 14:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("Error %d, SeatIndex %d", HIBYTE(a5), HIBYTE(a4));
        if ( HIBYTE(a5) == 22 )
        {
          v70 = *(uint32_t *)(dword_8F850C + 4 * HIBYTE(a4) + 16);
          if ( v70 != 0 )
          {
            if ( v70 == sub_429830((uint16_t)word_77F804) )
            {
              strcpy(Buffer, (const char *)sub_422E70(723));
            }
            else
            {
              if ( *(uint32_t *)(v70 + 40) < 0x10u )
                v71 = v70 + 20;
              else
                v71 = *(uint32_t *)(v70 + 20);
              v72 = (const char *)sub_422E70(724);
              sprintf(Buffer, v72, v71);
            }
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
            *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
          }
          else
          {
            off_77F3FC(aCriticalError_33);
            *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
          }
        }
        else
        {
          if ( HIBYTE(a5) == 21 )
          {
            v73 = *((uint32_t **)dword_8F8528 + 7);
            v74 = sub_422E70(725);
            sub_43BEE0(v73, v74, -6567706, 0, -1);
          }
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
        }
      }
      return 1;
    case 15:
      if ( (uint8_t)a5 != 0 )
        return 1;
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0x15:
          v75 = (char *)sub_422E70(726);
          off_77F3F8(v76, v75);
          break;
        case 0x13:
          v77 = (char *)sub_422E70(727);
          off_77F3F8(v78, v77);
          break;
        case 8:
          v79 = (char *)sub_422E70(728);
          off_77F3F8(v80, v79);
          break;
        case 0xE:
          off_77F3FC(aFail_2);
          break;
        case 0x11:
          HIBYTE(a4) = 0;
          sub_404A90((uint8_t *)&a4 + 3);
          off_77F3FC("SeatIndex %d", HIBYTE(a4));
          v81 = sub_583B30(*(uint32_t *)(dword_8F7A24 + 24));
          v82 = v81;
          if ( v81 == -1 )
          {
            off_77F3FC(aCriticalError_46);
            return 1;
          }
          v83 = (uint32_t *)sub_476B60(v81);
          v84 = v83;
          if ( v83 == nullptr )
          {
            off_77F3FC(aCriticalError_34, v82);
            return 1;
          }
          v85 = sub_4F2CE0(v83[24]);
          v86 = *(uint32_t *)(dword_8F850C + 4 * HIBYTE(a4) + 16);
          if ( v86 == 0 )
          {
            off_77F3FC(aCriticalError_47);
            return 1;
          }
          if ( v84[7] < 0x10u )
            v87 = v84 + 2;
          else
            v87 = (uint32_t *)v84[2];
          if ( *(uint32_t *)(v86 + 40) < 0x10u )
            v88 = v86 + 20;
          else
            v88 = *(uint32_t *)(v86 + 20);
          v416 = v87;
          v412 = v84[25];
          v411 = v85;
          v409 = v88;
          v89 = (const char *)sub_422E70(2100);
          sprintf(v449, v89, v409, v411, v412, v416);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v449, -6567706, 0, -1);
          break;
        default:
          break;
      }
      v90 = sub_453BE0(*(uint32_t *)(a1 + 24));
      v91 = *(uint32_t *)(a1 + 24);
      if ( v90 != 0 )
      {
        if ( *(uint32_t *)(v91 + 288) != 0 )
          sub_454680(**(uint32_t **)(v91 + 276), *(uint32_t *)(*(uint32_t *)(v91 + 276) + 4));
        else
          off_77F3FC(aCriticalError0);
      }
      else
      {
        *(uint8_t *)(v91 + 180) = 0;
      }
      return 1;
    case 17:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("ItemSpace %d, SlotNumber %d", HIBYTE(a4), HIBYTE(a5));
        memset(&v457[1], 0, 12);
        v92 = 0;
        v461 = 0;
        if ( HIBYTE(a5) != 0 )
        {
          do
          {
            v439 = nullptr;
            *(uint32_t *)v446 = 0;
            sub_404AB0(&v439);
            sub_404AD0(v446);
            off_77F3FC("SlotIndex %d, StackNumber %d", (uint16_t)v439, *(uint32_t *)v446);
            if ( HIBYTE(a4) == 3 )
            {
              v93 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 788))(
                      dword_8F7C04,
                      (uint16_t)v439,
                      v437);
              if ( v93 != 0 )
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v93 + 4))(v93, 1);
              v437 = (uint16_t)v439;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04);
            }
            else
            {
              HIDWORD(Time) = *(uint32_t *)v446;
              LODWORD(Time) = (uint16_t)v439;
              sub_474950(&Time);
            }
            ++v92;
          }
          while ( v92 < HIBYTE(a5) );
        }
        if ( HIBYTE(a4) != 3 )
        {
          v94 = (int *)sub_432F00(HIBYTE(a4));
          if ( sub_485150(v94, (int)v457) == 0 )
          {
            v95 = (char *)sub_422E70(729);
            off_77F3F8(v96, v95);
          }
        }
        sub_47CD00(dword_8F8540);
        sub_5E5260(v457);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x11:
            v98 = (char *)sub_422E70(730);
            off_77F3F8(v99, v98);
            break;
          case 0x13:
            v100 = (char *)sub_422E70(731);
            off_77F3F8(v101, v100);
            break;
          case 0x17:
            off_77F3F8(v97, "item type error");
            break;
          default:
            break;
        }
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("ItemSpace %d", HIBYTE(a4));
        v102 = (uint32_t *)sub_432F00(HIBYTE(a4));
        if ( v102 != nullptr )
          goto LABEL_243;
      }
      return 1;
    case 18:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        v445 = 0;
        v447 = 0;
        v441 = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404AB0(&v445);
        sub_404AD0(&v441);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AB0(&v447);
        off_77F3FC(
          "ItemSpace1 %d, ItemSlotIndex1 %d, MoveNumber %d, ItemSpace2 %d, ItemSlotIndex2 %d",
          HIBYTE(a4),
          (uint16_t)v445,
          v441,
          HIBYTE(a5),
          (uint16_t)v447);
        if ( HIBYTE(a4) == HIBYTE(a5) )
        {
          v103 = (uint32_t *)sub_432F00(HIBYTE(a4));
          if ( v103 != nullptr && sub_485270(v103, (uint16_t)v445, (uint16_t)v447) == 0 )
          {
            v104 = (char *)sub_422E70(732);
            off_77F3F8(v105, v104);
          }
          return 1;
        }
        if ( HIBYTE(a4) != 0 )
        {
          if ( HIBYTE(a4) != 2 )
          {
            if ( HIBYTE(a4) != 1 )
              goto LABEL_268;
            goto LABEL_257;
          }
          if ( HIBYTE(a5) != 0 )
          {
LABEL_257:
            if ( HIBYTE(a5) == 3 )
            {
              v110 = (int *)sub_432F00(HIBYTE(a4));
              if ( sub_485510(v110, a3, (uint16_t)v445, (uint16_t)v447) == 0 )
              {
                v108 = (char *)sub_422E70(734);
                goto LABEL_733;
              }
              v111 = *(uint32_t *)(a1 + 12);
              if ( v111 == 3 || v111 == 2 || v111 == 4 || v111 == 6 )
              {
                v112 = dword_8F7C04;
                v113 = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_8F7C04 + 792))(
                         dword_8F7C04,
                         (uint16_t)v447,
                         v437,
                         a2);
                if ( v113 != 0 )
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v112 + 812))(v112, v113);
                else
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v112 + 816))(v112, (uint16_t)v447);
              }
LABEL_265:
              sub_47CD00(dword_8F8540);
              return 1;
            }
LABEL_268:
            if ( HIBYTE(a4) > 1u || HIBYTE(a5) != 4 )
            {
              if ( HIBYTE(a4) != 4 )
              {
                if ( HIBYTE(a4) != 3 )
                  return 1;
                v114 = HIBYTE(a5) == 4;
LABEL_273:
                if ( !v114 )
                  return 1;
                v115 = *(int **)(dword_8F8538 + 16);
                if ( HIBYTE(a4) == 4 )
                {
                  if ( sub_485510(v115, a3, (uint16_t)v445, (uint16_t)v447) != 0 )
                    goto LABEL_282;
                  v116 = (char *)sub_422E70(736);
                }
                else
                {
                  if ( sub_485510(v115, a3, (uint16_t)v447, (uint16_t)v445) != 0 )
                    goto LABEL_282;
                  v116 = (char *)sub_422E70(737);
                }
                off_77F3F8(v117, v116);
LABEL_282:
                for ( j = 0; j < 2; ++j )
                  sub_484710((uint32_t *)dword_8F8538, j, 0);
LABEL_289:
                sub_57A3A0(dword_8F8538);
                sub_47CD00(dword_8F8540);
                return 1;
              }
              if ( HIBYTE(a5) >= 2u )
              {
                v114 = HIBYTE(a5) == 3;
                goto LABEL_273;
              }
            }
            v119 = (int *)sub_432F00(HIBYTE(a4));
            v120 = (int *)sub_432F00(HIBYTE(a5));
            if ( sub_485330(v119, (uint16_t)v445, v441, v120, (uint16_t)v447) == 0 )
            {
              v121 = (char *)sub_422E70(735);
              off_77F3F8(v122, v121);
            }
            for ( k = 0; k < 2; ++k )
              sub_484710((uint32_t *)dword_8F8538, k, 0);
            goto LABEL_289;
          }
        }
        else if ( HIBYTE(a5) != 2 )
        {
          goto LABEL_257;
        }
        v106 = (int *)sub_432F00(HIBYTE(a4));
        v107 = (int *)sub_432F00(HIBYTE(a5));
        if ( sub_485330(v106, (uint16_t)v445, v441, v107, (uint16_t)v447) != 0 )
          goto LABEL_265;
        v108 = (char *)sub_422E70(733);
        goto LABEL_733;
      }
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0x11:
          v124 = (char *)sub_422E70(738);
LABEL_303:
          off_77F3F8(v125, v124);
          goto LABEL_304;
        case 0x12:
          v124 = (char *)sub_422E70(739);
          goto LABEL_303;
        case 0x13:
          v124 = (char *)sub_422E70(740);
          goto LABEL_303;
        case 8:
          v126 = sub_422E70(741);
          break;
        case 0xE:
          v126 = sub_422E70(742);
          break;
        case 0x17:
          v124 = (char *)sub_422E70(743);
          goto LABEL_303;
        default:
LABEL_304:
          HIBYTE(a4) = 0;
          HIBYTE(v444) = 0;
          sub_404A90((uint8_t *)&a4 + 3);
          sub_404A90((uint8_t *)&v444 + 3);
          off_77F3FC("ItemSpace1 %d, ItemSpace2 %d", HIBYTE(a4), HIBYTE(v444));
          v127 = (uint32_t *)sub_432F00(HIBYTE(a4));
          v128 = (uint32_t *)sub_432F00(HIBYTE(v444));
          if ( v127 != nullptr )
            sub_484FF0(v127);
          if ( v128 != nullptr && v127 != v128 )
            sub_484FF0(v128);
          return 1;
      }
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v126, 0);
      goto LABEL_304;
    case 19:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("ItemSpace %d", HIBYTE(a5));
        v129 = (uint32_t *)sub_432F00(HIBYTE(a5));
        sub_484FF0(v129);
        sub_432EA0("ARRANGE_FINISH", -1, 0, 0);
        return 1;
      }
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      if ( HIBYTE(a5) == 2 )
      {
        v130 = (char *)sub_422E70(744);
      }
      else
      {
        if ( HIBYTE(a5) != 18 )
          goto LABEL_316;
        v130 = (char *)sub_422E70(745);
      }
      off_77F3F8(v131, v130);
LABEL_316:
      HIBYTE(a4) = 0;
      sub_404A90((uint8_t *)&a4 + 3);
      off_77F3FC("ItemSpace %d", HIBYTE(a4));
      v132 = (uint32_t *)sub_432F00(HIBYTE(a4));
      sub_484FF0(v132);
      return 1;
    case 20:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        v447 = 0;
        *(uint32_t *)v446 = 0;
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)v440 = 0;
        a4 = 0;
        v438 = 0;
        sub_404AD0(v446);
        sub_404AD0(ArgList);
        sub_404AD0(&v438);
        sub_404AD0(v440);
        sub_404AB0(&a5);
        sub_404AB0(&v447);
        sub_404AD0(&a4);
        off_77F3FC(
          "Money %d, Medal %d, fp %d, Cash %d, ItemSlotIndex %d, ItemIndex %d, Data %d",
          *(uint32_t *)v446,
          *(uint32_t *)ArgList,
          v438,
          *(uint32_t *)v440,
          (uint16_t)a5,
          (uint16_t)v447,
          a4);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          *(uint32_t *)v446);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),
          *(uint32_t *)ArgList);
        dword_8F7C0C = *(uint32_t *)v440;
        if ( *(int *)v440 < 0 )
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);
          dword_8F7C0C = 0;
        }
        v133 = sub_44A980((uint16_t)a5);
        if ( v133 != 0 )
        {
          v134 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v133 + 60))(v133, (uint16_t)v447);
          v135 = *(uint32_t *)v133;
          if ( v134 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, unsigned int))(v135 + 48))(v133, a4);
          }
          else
          {
            v136 = (*(int (/*thiscall*/ **)(int))(v135 + 16))(v133);
            off_77F3FC((char *)&byte_7246D4, (uint16_t)a5, *(uint32_t *)(v136 + 4));
          }
        }
        else
        {
          v133 = sub_522300((void *)(uint16_t)v447, a4, 0, 0, -1, 1);
          sub_484F40((int *)dword_8F852C, (uint16_t)a5, v133, 1);
        }
        if ( v133 != 0 )
        {
          v137 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v133 + 56))(v133);
          sub_432EA0(v137, -1, 0, 0);
          if ( *((uint32_t *)dword_8F8528 + 27) == 0 && (uint16_t)a5 >= 9u )
            *(uint32_t *)(*((uint32_t *)dword_8F8528 + 14) + 56) = ((uint16_t)a5 - 9) / 32;
        }
        sub_47CD00(dword_8F8540);
        if ( *(uint32_t *)(a1 + 12) == 6 )
        {
          v138 = dword_99FF08;
          if ( dword_99FF08 != 0 )
            *(uint32_t *)(v138 + 4 * sub_48FCA0() + 112) = v438;
          else
            off_77F3FC(byte_72B81C);
        }
        return 1;
      }
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 4:
          v139 = sub_422E70(746);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v139, 0);
          return 1;
        case 0xA:
          v140 = sub_422E70(747);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v140, 0);
          return 1;
        case 0x11:
          goto LABEL_359;
        case 0x13:
          goto LABEL_361;
        case 0x37:
          v141 = sub_422E70(1342);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v141, 0);
          break;
        case 9:
          off_77F3FC(aFailFp);
          break;
        default:
          break;
      }
      return 1;
    case 21:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        *(uint32_t *)v446 = 0;
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)v440 = 0;
        sub_404AD0(v446);
        sub_404AD0(ArgList);
        sub_404AD0(v440);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC(
          "Money %d, Medal %d, Cash %d, ItemNumber %d",
          *(uint32_t *)v446,
          *(uint32_t *)ArgList,
          *(uint32_t *)v440,
          HIBYTE(a5));
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          *(uint32_t *)v446);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),
          *(uint32_t *)ArgList);
        dword_8F7C0C = *(uint32_t *)v440;
        if ( *(int *)v440 < 0 )
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);
          dword_8F7C0C = 0;
        }
        v142 = 1;
        v439 = nullptr;
        if ( HIBYTE(a5) != 0 )
        {
          do
          {
            a4 = 0;
            v447 = 0;
            v438 = 0;
            sub_404AB0(&a4);
            sub_404AB0(&v447);
            sub_404AD0(&v438);
            off_77F3FC("ItemSlotIndex %d ItemIndex %d Data %d", (uint16_t)a4, (uint16_t)v447, v438);
            v143 = sub_522300((void *)(uint16_t)v447, v438, 0, 0, -1, 1);
            v144 = v143;
            if ( v143 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v143 + 20))(v143, 2) != 0 )
            {
              sub_484F40((int *)dword_8F8534, (uint16_t)a4, v144, 1);
              v145 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v144 + 56))(v144);
              sub_432EA0(v145, -1, 0, 0);
              v146 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v144 + 172))(v144);
              if ( sub_486820((int *)dword_8F8534, (uint16_t)a4, *v146, v142) != 0 )
                ++v142;
            }
            else
            {
              off_77F3FC(aCriticalError_35, (uint16_t)v447);
            }
            v439 = (int *)((char *)v439 + 1);
          }
          while ( (int)v439 < HIBYTE(a5) );
        }
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 4:
            v147 = sub_422E70(748);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v147, 0);
            break;
          case 0xA:
            v148 = sub_422E70(749);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v148, 0);
            break;
          case 0x11:
LABEL_359:
            off_77F3FC(aFail_14);
            break;
          case 0x13:
LABEL_361:
            off_77F3FC(aFail_13);
            break;
          default:
            break;
        }
      }
      return 1;
    case 22:
      if ( (uint8_t)a5 != 0 )
      {
        *(uint32_t *)ArgList = 0;
        a5 = 0;
        a4 = 0;
        *(uint32_t *)v446 = 0;
        *(uint32_t *)v440 = 0;
        sub_404AD0(&a5);
        sub_404AD0(&a4);
        sub_404AD0(v446);
        sub_404AB0(ArgList);
        sub_404AD0(v440);
        off_77F3FC(
          "Money %d, Medal %d, Cash %d, ItemSlotIndex %d, Data %d",
          a5,
          a4,
          *(uint32_t *)v446,
          *(uint16_t *)ArgList,
          *(uint32_t *)v440);
        (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          a5);
        (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),
          a4);
        dword_8F7C0C = *(uint32_t *)v446;
        if ( *(int *)v446 < 0 )
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v446);
          dword_8F7C0C = 0;
        }
        v149 = sub_44A980(*(uint16_t *)ArgList);
        v150 = __RTDynamicCast(v149, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
        v151 = (int *)v150;
        if ( v150 != 0 )
        {
          v152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v150 + 188))(v150);
          sub_583AB0(v152);
          v153 = *v151;
          *(uint32_t *)&v453[4] = *(uint32_t *)v440;
          v461 = 1;
          (*(void (/*thiscall*/ **)(int *, char *))(v153 + 184))(v151, &v453[4]);
          v461 = -1;
          sub_445150(&v453[4]);
        }
        else
        {
          off_77F3FC(aCriticalError_48);
        }
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0xA:
            v154 = sub_422E70(750);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v154, 0);
            break;
          case 0x11:
            off_77F3FC(aFail_16);
            break;
          case 0x13:
            off_77F3FC(aFail_15);
            break;
          default:
            break;
        }
      }
      return 1;
    case 23:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        *(uint32_t *)ArgList = 0;
        *(uint32_t *)v446 = 0;
        sub_404AD0(v446);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AB0(&a4);
        sub_404AB0(ArgList);
        off_77F3FC(
          "Money %d, ItemSpace %d, ItemSlotIndex %d, SellItemNumber %d",
          *(uint32_t *)v446,
          HIBYTE(a5),
          (uint16_t)a4,
          *(uint16_t *)ArgList);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          *(uint32_t *)v446);
        v155 = (void *)(*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 56))(**((uint32_t **)dword_8F852C
                                                                                                 + 3));
        sub_432EA0(v155, -1, 0, 0);
        if ( HIBYTE(a5) != 0 )
        {
          if ( HIBYTE(a5) == 3 )
          {
            v159 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 788))(
                     dword_8F7C04,
                     (uint16_t)a4,
                     a3);
            if ( v159 != 0 )
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v159 + 4))(v159, 1);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04, (uint16_t)a4);
          }
        }
        else
        {
          v156 = sub_44A980((uint16_t)a4);
          v157 = v156;
          if ( v156 != 0 )
          {
            v158 = *(uint16_t *)ArgList;
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v156 + 44))(v156, v437) <= v158 )
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v157 + 4))(v157, 1);
              sub_484F40((int *)dword_8F852C, (uint16_t)a4, 0, 1);
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v157 + 52))(v157, v158);
            }
          }
        }
        sub_47CD00(dword_8F8540);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x11:
            off_77F3FC(aFail_19);
            break;
          case 0x13:
            off_77F3FC(aFail_18);
            break;
          case 0x16:
            off_77F3FC(aFail_17);
            break;
          case 0x37:
            v160 = sub_422E70(1343);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v160, 0);
            break;
          case 0x17:
            off_77F3FC(aFailFp_0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 24:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 == 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0xA:
            v46 = *((uint32_t **)dword_8F8528 + 7);
            v47 = sub_422E70(751);
LABEL_983:
            sub_43BEE0(v46, v47, -6567706, 0, -1);
            break;
          case 0x11:
            off_77F3FC(aFail_21);
            break;
          case 0x13:
            off_77F3FC(aFail_20);
            break;
          default:
            break;
        }
        return 1;
      }
      v161 = 0;
      *(uint32_t *)v446 = 0;
      a4 = 0;
      sub_404AD0(&a4);
      sub_404A90((uint8_t *)&a5 + 3);
      sub_404AB0(v446);
      off_77F3FC("Money %d, ItemSpace %d, ItemSlotIndex %d", a4, HIBYTE(a5), *(uint16_t *)v446);
      (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(***((uint32_t ***)dword_8F852C + 3) + 40))(
        **((uint32_t **)dword_8F852C + 3),
        a4);
      if ( *(uint16_t *)v446 == 0xFFFF )
      {
        v162 = dword_8F7C04;
        do
        {
          v163 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v162 + 792))(v162, v161);
          if ( v163 != 0 )
          {
            v164 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v163 + 172))(v163);
            v165 = sub_41A5E0(v164 + 18);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v163 + 192))(v163, v165);
          }
          ++v161;
        }
        while ( v161 < 18 );
        v166 = 0;
        for ( HIDWORD(Time) = *((uint32_t *)dword_8F852C + 2); v166 < SHIDWORD(Time); ++v166 )
        {
          v167 = sub_44A980(v166);
          v168 = v167;
          if ( v167 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v167 + 20))(v167, 2) != 0 )
          {
            v169 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v168 + 188))(v168);
            v170 = sub_41A5E0(v169 + 32);
            v171 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v168 + 172))(v168);
            if ( v170 < sub_41A5E0(v171 + 18) )
            {
              v172 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v168 + 172))(v168);
              v173 = sub_41A5E0(v172 + 18);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v168 + 192))(v168, v173);
            }
          }
        }
        goto LABEL_418;
      }
      if ( HIBYTE(a5) != 0 )
      {
        if ( HIBYTE(a5) != 3 )
        {
LABEL_418:
          sub_44E850(dword_8F8528, 26);
          sub_432EA0("ITEM_REPAIR", -1, 0, 0);
          return 1;
        }
        v177 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(
                 dword_8F7C04,
                 *(uint16_t *)v446);
        v175 = v177;
        if ( v177 != 0 )
        {
          v176 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v177 + 172))(v177, v437);
          goto LABEL_416;
        }
      }
      else
      {
        v174 = sub_44A980(*(uint16_t *)v446);
        v175 = v174;
        if ( v174 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v174 + 20))(v174, 2) != 0 )
        {
          v176 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v175 + 172))(v175, v437);
LABEL_416:
          v178 = sub_41A5E0(v176 + 18);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v175 + 192))(v175, v178);
          goto LABEL_418;
        }
      }
      off_77F3FC((char *)&byte_72B554);
      goto LABEL_418;
    case 25:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 1:
            v179 = sub_422E70(752);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v179, 0);
            break;
          case 0x11:
            off_77F3FC(aFail_24);
            break;
          case 4:
            v180 = sub_422E70(753);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v180, 0);
            break;
          case 0x13:
            off_77F3FC(aFail_23);
            break;
          case 7:
            off_77F3FC(aFail_22);
            break;
          default:
            break;
        }
      }
      return 1;
    case 26:
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("InputItemTypeNumber %d", HIBYTE(a4));
        v181 = 0;
        if ( HIBYTE(a4) != 0 )
        {
          do
          {
            HIBYTE(v444) = 0;
            v447 = 0;
            v445 = 0;
            sub_404A90((uint8_t *)&v444 + 3);
            sub_404AB0(&v447);
            sub_404AD0(&v445);
            off_77F3FC("ItemSpace %d, SlotIndex %d, ItemNumber %d", HIBYTE(v444), (uint16_t)v447, v445);
            if ( HIBYTE(v444) != 0 )
            {
              if ( HIBYTE(v444) == 3 && dword_8F7C04 != 0 )
              {
                v185 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 788))(
                         dword_8F7C04,
                         (uint16_t)v447);
                if ( v185 != 0 )
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v185 + 4))(v185, 1);
              }
            }
            else
            {
              v182 = sub_44A980((uint16_t)v447);
              v183 = __RTDynamicCast(
                       v182,
                       0,
                       &IRDItem `RTTI Type Descriptor',
                       &CNRecipeStackable `RTTI Type Descriptor',
                       0);
              if ( v183 != 0 )
                dword_795D48 = *(uint32_t *)(v183 + 164);
              if ( (uint16_t)v447 != 0
                && (v184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v182 + 44))(v182)) <= (unsigned int)v445 )
              {
                sub_484D50((int *)dword_8F852C, (uint16_t)v447);
              }
              else
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v182 + 52))(v182, v445);
              }
            }
            ++v181;
          }
          while ( v181 < HIBYTE(a4) );
        }
        v186 = sub_44E8D0((char *)dword_8F8528, (void *)0x22, 0, 0);
        HIDWORD(Time) = __RTDynamicCast(
                          v186,
                          0,
                          &IRDPopupWindow `RTTI Type Descriptor',
                          &CNRDCompoundResultWindow `RTTI Type Descriptor',
                          0);
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("OutputItemTypeNumber %d", HIBYTE(a5));
        v187 = 0;
        if ( HIBYTE(a5) != 0 )
        {
          do
          {
            v447 = 0;
            v441 = 0;
            v445 = 0;
            sub_404AB0(&v447);
            sub_404AB0(&v441);
            sub_404AD0(&v445);
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)v447, (uint16_t)v441, v445);
            if ( (uint16_t)v447 < *((int *)dword_8F852C + 2)
              && (v188 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * (uint16_t)v447)) != 0 )
            {
              v189 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v188 + 60))(v188, (uint16_t)v441);
              v190 = *(uint32_t *)v188;
              if ( v189 != 0 )
              {
                (*(void (/*thiscall*/ **)(int, int))(v190 + 48))(v188, v445);
              }
              else
              {
                v191 = (*(int (/*thiscall*/ **)(int))(v190 + 16))(v188);
                off_77F3FC(aD_1, (uint16_t)v447, *(uint32_t *)(v191 + 4));
              }
            }
            else
            {
              v188 = sub_522300((void *)(uint16_t)v441, v445, 0, 0, -1, 1);
              sub_484F40((int *)dword_8F852C, (uint16_t)v447, v188, 1);
            }
            v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v188 + 20))(v188, 1) == 0;
            v192 = v445;
            if ( v114 )
              v192 = 1;
            sub_63F2F0(v188, v192);
            if ( v187 == HIBYTE(a5) - 1 )
            {
              v193 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v188 + 56))(v188);
              sub_432EA0(v193, -1, 0, 0);
            }
            ++v187;
          }
          while ( v187 < HIBYTE(a5) );
        }
        goto LABEL_265;
      }
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0x11:
          v194 = sub_422E70(754);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v194, 0);
          break;
        case 0xE:
          v195 = sub_422E70(755);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v195, 0);
          break;
        case 0x15:
          v196 = sub_422E70(756);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v196, 0);
          break;
        case 0x16:
          v197 = sub_422E70(757);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v197, 0);
          break;
        case 4:
          v198 = sub_422E70(758);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v198, 0);
          break;
        case 0x13:
          v199 = sub_422E70(759);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v199, 0);
          break;
        case 0x17:
          off_77F3FC(aCriticalError_49);
          break;
        default:
          break;
      }
      return 1;
    case 27:
      sub_54D2B0(0);
      if ( (uint8_t)a5 != 0 )
      {
        *(uint32_t *)v446 = 0;
        sub_404AB0(v446);
        off_77F3FC("SlotIndex %d", *(uint16_t *)v446);
        sub_4850B0((int *)dword_8F852C, *(uint16_t *)v446, 1u);
        v200 = sub_44E8D0((char *)dword_8F8528, (void *)0x18, 0, 0);
        HIDWORD(Time) = __RTDynamicCast(
                          v200,
                          0,
                          &IRDPopupWindow `RTTI Type Descriptor',
                          &CNRDItemDisjointResultWindow `RTTI Type Descriptor',
                          0);
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("OutputItemTypeNumber %d", HIBYTE(a5));
        v201 = 0;
        if ( HIBYTE(a5) != 0 )
        {
          do
          {
            a4 = 0;
            v445 = 0;
            v447 = 0;
            sub_404AB0(&a4);
            sub_404AB0(&v445);
            sub_404AD0(&v447);
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)a4, (uint16_t)v445, v447);
            v202 = sub_44A980((uint16_t)a4);
            if ( v202 != 0 )
            {
              v203 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v202 + 60))(v202, (uint16_t)v445);
              v204 = *(uint32_t *)v202;
              if ( v203 != 0 )
              {
                (*(void (/*thiscall*/ **)(int, int))(v204 + 48))(v202, v447);
              }
              else
              {
                v205 = (*(int (/*thiscall*/ **)(int))(v204 + 16))(v202);
                off_77F3FC(aD_1, (uint16_t)a4, *(uint32_t *)(v205 + 4));
              }
            }
            else
            {
              v202 = sub_522300((void *)(uint16_t)v445, v447, 0, 0, -1, 1);
              sub_484F40((int *)dword_8F852C, (uint16_t)a4, v202, 1);
            }
            v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v202 + 20))(v202, 1) == 0;
            v206 = v447;
            if ( v114 )
              v206 = 1;
            sub_63DFB0(v202, v206);
            if ( v201 == HIBYTE(a5) - 1 )
            {
              v207 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v202 + 56))(v202);
              sub_432EA0(v207, -1, 0, 0);
            }
            ++v201;
          }
          while ( v201 < HIBYTE(a5) );
        }
        goto LABEL_489;
      }
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0x11:
          v208 = sub_422E70(760);
          break;
        case 0x17:
          v208 = sub_422E70(761);
          break;
        case 0x16:
          v208 = sub_422E70(762);
          break;
        case 0x13:
          v208 = sub_422E70(763);
          break;
        case 4:
          v208 = sub_422E70(764);
          break;
        default:
          goto LABEL_747;
      }
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v208, 0);
      goto LABEL_747;
    case 28:
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        sub_404AB0(&a4);
        off_77F3FC("LotteryItemSlotIndex %d", (uint16_t)a4);
        v209 = a4;
        v210 = sub_44A980((uint16_t)a4);
        if ( v210 != 0 )
        {
          if ( v209 != 0 && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v210 + 44))(v210) <= 1 )
            sub_484D50((int *)dword_8F852C, (uint16_t)a4);
          else
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v210 + 52))(v210, 1);
        }
        else
        {
          off_77F3FC(aCriticalError_36);
        }
        a5 = 0;
        v445 = 0;
        *(uint32_t *)v446 = 0;
        v447 = 0;
        sub_404AB0(&a5);
        sub_404AB0(&v445);
        sub_404AD0(&v447);
        sub_404AB0(v446);
        off_77F3FC(
          "SlotIndex %d, ItemIndex %d, Data %d, Durability %d",
          (uint16_t)a5,
          (uint16_t)v445,
          v447,
          *(uint16_t *)v446);
        v211 = sub_44A980((uint16_t)a5);
        v212 = v211;
        if ( v211 != 0 )
        {
          v213 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v211 + 60))(v211, (uint16_t)v445);
          v214 = *(uint32_t *)v212;
          if ( v213 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(v214 + 48))(v212, v447);
          }
          else
          {
            v215 = (*(int (/*thiscall*/ **)(int))(v214 + 16))(v212);
            off_77F3FC(aD_1, (uint16_t)a5, *(uint32_t *)(v215 + 4));
          }
        }
        else
        {
          v212 = sub_522300((void *)(uint16_t)v445, v447, 0, 0, *(uint16_t *)v446, 1);
          sub_484F40((int *)dword_8F852C, (uint16_t)a5, v212, 1);
        }
        if ( v212 != 0 )
        {
          sub_44E8D0((char *)dword_8F8528, (void *)0x23, v212, 1);
          v216 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v212 + 56))(v212);
          sub_432EA0(v216, -1, 0, 0);
        }
LABEL_489:
        sub_47CD00(dword_8F8540);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x11:
            v217 = sub_422E70(765);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v217, 0);
            break;
          case 0xE:
            v218 = sub_422E70(766);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v218, 0);
            break;
          case 4:
            v219 = sub_422E70(767);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v219, 0);
            break;
          case 0x13:
            v220 = sub_422E70(768);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v220, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 29:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("SlotIndex1 %d, SlotIndex2 %d", HIBYTE(a4), HIBYTE(a5));
        if ( sub_483DA0((int *)dword_8F853C, HIBYTE(a4), HIBYTE(a5)) == 0 )
        {
          v221 = (char *)sub_422E70(769);
          off_77F3F8(v222, v221);
        }
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 21 )
        {
          off_77F3FC(aFail_25);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_3);
        }
        *((uint32_t *)dword_8F853C + 2) = (*((uint32_t *)dword_8F853C + 2) - 1)
                                      & ((*((uint32_t *)dword_8F853C + 2) - 1 <= 0) - 1);
      }
      return 1;
    case 30:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(v444) = 0;
        HIBYTE(a4) = 0;
        *(uint32_t *)v446 = 0;
        sub_404AB0(v446);
        sub_404A90((uint8_t *)&v444 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC(
          "Sp %d, SlotIndex %d, SkillIndex %d, Level %d",
          *(uint16_t *)v446,
          HIBYTE(v444),
          HIBYTE(a5),
          HIBYTE(a4));
        Value = *(uint16_t *)v446;
        sub_57A3C0(HIBYTE(v444), HIBYTE(a5));
        v223 = sub_47DC90(HIBYTE(a5));
        sub_47DEC0(0, HIBYTE(a4));
        *(uint32_t *)(v223 + 540) = 0;
        sub_583A40(v223);
        sub_47E4F0();
        if ( dword_8F7C04 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1136))(
            dword_8F7C04,
            HIBYTE(a5),
            HIBYTE(a4));
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1152))(dword_8F7C04);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1156))(dword_8F7C04);
        }
        if ( *((uint32_t *)dword_8F8528 + 26) == 3 )
          sub_583A60(*((uint32_t *)dword_8F8528 + 17));
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x12:
            off_77F3FC(aFail_27);
            break;
          case 0x15:
            off_77F3FC(aFail_26);
            break;
          case 0x16:
            v224 = sub_422E70(770);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v224, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 31:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        *(uint32_t *)v446 = 0;
        v447 = 0;
        a4 = 0;
        sub_404AB0(v446);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AD0(&a4);
        sub_404AB0(&v447);
        off_77F3FC(
          "SlotIndex %d, StatusType %d, ChangeValue %d, ChangeSubValue %d",
          *(uint16_t *)v446,
          HIBYTE(a5),
          a4,
          (uint16_t)v447);
        sub_4850B0((int *)dword_8F852C, *(uint16_t *)v446, 1u);
        v225 = HIBYTE(a5);
        if ( HIBYTE(a5) != 0 )
        {
          if ( HIBYTE(a5) == 1 )
          {
            v418 = a4;
            v228 = (const char *)sub_422E70(772);
            sprintf(Buffer, v228, v418);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
            v229 = dword_8F7C04;
            if ( dword_8F7C04 != 0 )
            {
              v230 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);
              v231 = *(uint32_t *)v229;
              v232 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v229 + 1032))(v229, *v230);
              (*(void (/*thiscall*/ **)(int, unsigned int))(v231 + 1036))(v229, a4 + *(uint32_t *)(v232 + 48));
              if ( *(uint32_t *)(dword_8F7A24 + 12) != 3 )
              {
                v233 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v229 + 1032))(v229) + 44);
                if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v229 + 1032))(v229) + 40) >= v233 )
                {
                  v234 = *((uint32_t **)dword_8F8528 + 7);
                  v235 = sub_422E70(773);
                  sub_43BEE0(v234, v235, -6567706, 0, -1);
                }
              }
            }
            if ( (uint16_t)v447 != 0 && *(uint32_t *)(dword_8F7A24 + 12) != 3 )
            {
              sub_57A430(1);
              v419 = (uint16_t)v447;
              v236 = (const char *)sub_422E70(774);
              sprintf(v452, v236, v419);
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v452, -6567706, 0, -1);
              sub_432EA0("SP_GET", -1, 0, 0);
              Value += (uint16_t)v447;
            }
          }
          else
          {
            v237 = dword_8F7C04;
            v238 = 0;
            if ( dword_8F7C04 != 0 )
            {
              v238 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1052))(dword_8F7C04);
              v225 = HIBYTE(a5);
            }
            switch ( v225 )
            {
              case 2:
                v420 = a4 / 0xA;
                v239 = (const char *)sub_422E70(775);
                sprintf(v452, v239, v420);
                if ( v238 != 0 )
                  *(uint32_t *)v238 += a4;
                break;
              case 3:
                v421 = a4 / 0xA;
                v240 = (const char *)sub_422E70(776);
                sprintf(v452, v240, v421);
                if ( v238 != 0 )
                  *(uint32_t *)(v238 + 4) += a4;
                break;
              case 4:
                v422 = a4 / 0xA;
                v241 = (const char *)sub_422E70(777);
                sprintf(v452, v241, v422);
                if ( v238 != 0 )
                  *(uint16_t *)(v238 + 8) += a4;
                break;
              case 5:
                v423 = a4 / 0xA;
                v242 = (const char *)sub_422E70(778);
                sprintf(v452, v242, v423);
                if ( v238 != 0 )
                  *(uint16_t *)(v238 + 10) += a4;
                break;
              case 6:
                v424 = a4 / 0xA;
                v243 = (const char *)sub_422E70(779);
                sprintf(v452, v243, v424);
                if ( v238 != 0 )
                  *(uint16_t *)(v238 + 12) += a4;
                break;
              case 7:
                v425 = a4 / 0xA;
                v244 = (const char *)sub_422E70(780);
                sprintf(v452, v244, v425);
                if ( v238 != 0 )
                  *(uint16_t *)(v238 + 14) += a4;
                break;
              case 8:
                v426 = a4 / 0xA;
                v245 = (const char *)sub_422E70(781);
                sprintf(v452, v245, v426);
                if ( v238 != 0 )
                  *(uint16_t *)(v238 + 64) += a4;
                break;
              case 9:
                v427 = a4 / 0xA;
                v246 = (const char *)sub_422E70(782);
                sprintf(v452, v246, v427);
                if ( v238 != 0 )
                {
                  *(uint16_t *)(v238 + 16) += a4;
                  *(uint16_t *)(v238 + 18) += a4;
                  *(uint16_t *)(v238 + 20) += a4;
                  *(uint16_t *)(v238 + 22) += a4;
                }
                break;
              case 10:
                v247 = sub_422E70(783);
                sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v247, 0);
                v248 = (const char *)sub_422E70(784);
                sprintf(v452, v248);
                sub_57A430(1);
                break;
              default:
                break;
            }
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v452, -6567706, 0, -1);
            if ( v237 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v237 + 1048))(v237, v238);
              v249 = *(uint32_t *)v237;
              LOBYTE(v250) = sub_41C210(v439) == 0;
              (*(void (/*thiscall*/ **)(int, int))(v249 + 1056))(v237, v250);
            }
          }
        }
        else
        {
          if ( dword_8F7C04 != 0 )
          {
            v226 = *(uint32_t *)(dword_8F7A24 + 12);
            if ( v226 == 3 || v226 == 4 || v226 == 6 )
              (*(void (/*stdcall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1232))(1);
          }
          sub_57A430(1);
          v417 = a4;
          v227 = (const char *)sub_422E70(771);
          sprintf(Buffer, v227, v417);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
          sub_432EA0("SP_GET", -1, 0, 0);
          Value += a4;
        }
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x13:
            off_77F3FC(aFail_28);
            break;
          case 0x11:
            v251 = sub_422E70(785);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v251, 0);
            break;
          case 1:
            v252 = sub_422E70(3002);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v252, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 32:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        v444 = 0;
        sub_404AB0(&v444);
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC(
          "QuestIndex %d, QuestTrigger %d, AcceptItemNumber %d",
          (uint16_t)v444,
          HIBYTE(a4),
          HIBYTE(a5));
        v253 = 0;
        if ( HIBYTE(a5) != 0 )
        {
          do
          {
            v447 = 0;
            v441 = 0;
            v445 = 0;
            sub_404AB0(&v447);
            sub_404AB0(&v441);
            sub_404AD0(&v445);
            off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)v447, (uint16_t)v441, v445);
            v254 = (int *)sub_44A980((uint16_t)v447);
            if ( v254 != nullptr )
            {
              v255 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v254 + 60))(v254, (uint16_t)v441);
              v256 = *v254;
              if ( v255 != 0 )
              {
                (*(void (/*thiscall*/ **)(int *, int))(v256 + 48))(v254, v445);
              }
              else
              {
                v257 = (*(int (/*thiscall*/ **)(int *))(v256 + 16))(v254);
                off_77F3FC(aD_1, (uint16_t)v447, *(uint32_t *)(v257 + 4));
              }
            }
            else
            {
              v258 = sub_522300((void *)(uint16_t)v441, v445, 0, 0, -1, 1);
              sub_484F40((int *)dword_8F852C, (uint16_t)v447, v258, 1);
            }
            ++v253;
          }
          while ( v253 < HIBYTE(a5) );
        }
        v259 = sub_47D060((uint16_t)v444, HIBYTE(a4));
        if ( v259 != 0 )
        {
          if ( (uint8_t)sub_546620((uint16_t)v444) == 0 )
          {
            v428 = unknown_libname_2((uint32_t *)(v259 + 4));
            v260 = (const char *)sub_422E70(786);
            sprintf(Buffer, v260, v428);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
          }
        }
        else
        {
          off_77F3FC(aCriticalError_37);
        }
        sub_47D9D0((uint32_t *)dword_8F8540);
        sub_553FB0(*((uint32_t *)dword_8F8528 + 21));
        sub_432EA0("QUEST_ACCEPT", -1, 0, 0);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x12:
            off_77F3FC(aFail_29);
            break;
          case 0x17:
            v261 = sub_422E70(787);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v261, 0);
            break;
          case 0x11:
            v262 = sub_422E70(788);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v262, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 33:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AB0(&a5);
        off_77F3FC("QuestIndex %d", (uint16_t)a5);
        v263 = sub_47C540((uint16_t)a5);
        v264 = v263;
        if ( v263 != 0 )
        {
          v429 = unknown_libname_2((uint32_t *)(v263 + 4));
          v265 = (const char *)sub_422E70(789);
          sprintf(Buffer, v265, v429);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
          if ( *((uint32_t *)dword_8F8528 + 26) == 8 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 22) + 16) == v264 )
            sub_44AB50(0, 12);
        }
        else
        {
          off_77F3FC(aCriticalError_38);
        }
        sub_47D9D0((uint32_t *)dword_8F8540);
        sub_553FB0(*((uint32_t *)dword_8F8528 + 21));
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
          off_77F3FC(aFail_30);
      }
      return 1;
    case 34:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        sub_404AB0(&a4);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("QuestIndex %d, Trigger %d", (uint16_t)a4, HIBYTE(a5));
        sub_47C8F0((uint16_t)a4, HIBYTE(a5));
        if ( HIBYTE(a5) == 0 )
          sub_432EA0("QUEST_COMPLETE1", -1, 0, 0);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_32);
        }
        else if ( HIBYTE(a5) == 22 )
        {
          off_77F3FC(aFail_31);
        }
      }
      return 1;
    case 35:
      if ( (uint8_t)a5 != 0 )
      {
        v438 = 0;
        sub_404AB0(&v438);
        off_77F3FC("QuestIndex %d", (uint16_t)v438);
        v266 = sub_47C8F0((uint16_t)v438, -1);
        v267 = v266;
        if ( v266 != 0 )
        {
          v430 = unknown_libname_2((uint32_t *)(v266 + 4));
          v268 = (const char *)sub_422E70(790);
          sprintf(Buffer, v268, v430);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
        }
        else
        {
          off_77F3FC(aCriticalError_38);
        }
        sub_432EA0("QUEST_COMPLETE2", -1, 0, 0);
        HIBYTE(v441) = 0;
        sub_404A90((uint8_t *)&v441 + 3);
        off_77F3FC("QuestType %d", HIBYTE(v441));
        if ( HIBYTE(v441) == 0 )
        {
          HIBYTE(a5) = 0;
          sub_404A90((uint8_t *)&a5 + 3);
          off_77F3FC("ItemTypeNumber %d", HIBYTE(a5));
          *(uint32_t *)v446 = 0;
          if ( HIBYTE(a5) != 0 )
          {
            do
            {
              HIBYTE(a4) = 0;
              v447 = 0;
              v444 = 0;
              sub_404A90((uint8_t *)&a4 + 3);
              sub_404AB0(&v447);
              sub_404AD0(&v444);
              off_77F3FC("ItemSpace %d, SlotIndex %d, ItemNumber %d", HIBYTE(a4), (uint16_t)v447, v444);
              if ( HIBYTE(a4) != 0 )
              {
                if ( HIBYTE(a4) == 3 && dword_8F7C04 != 0 )
                {
                  v272 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 788))(
                           dword_8F7C04,
                           (uint16_t)v447);
                  if ( v272 != 0 )
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v272 + 4))(v272, 1);
                }
              }
              else
              {
                v269 = sub_44A980((uint16_t)v447);
                v270 = v269;
                if ( v269 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v269 + 20))(v269, 2) != 0 )
                  v444 = 1;
                if ( (uint16_t)v447 != 0 && (v271 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v270 + 44))(v270)) <= v444 )
                  sub_484D50((int *)dword_8F852C, (uint16_t)v447);
                else
                  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)v270 + 52))(v270, v444);
              }
              ++*(uint32_t *)v446;
            }
            while ( *(int *)v446 < HIBYTE(a5) );
          }
        }
        HIBYTE(v445) = 0;
        sub_404A90((uint8_t *)&v445 + 3);
        off_77F3FC("QuestRewardType %d", HIBYTE(v445));
        if ( HIBYTE(v445) != 0 )
        {
          if ( HIBYTE(v445) == 1 )
          {
            HIBYTE(v447) = 0;
            HIBYTE(v444) = 0;
            sub_404A90((uint8_t *)&v447 + 3);
            sub_404A90((uint8_t *)&v444 + 3);
            off_77F3FC("GrowType %d, SkillNumber %d", HIBYTE(v447), HIBYTE(v444));
            v282 = 0;
            if ( HIBYTE(v444) != 0 )
            {
              do
              {
                HIBYTE(a4) = 0;
                HIBYTE(a5) = 0;
                v442 = 0;
                sub_404A90((uint8_t *)&a4 + 3);
                sub_404A90((uint8_t *)&a5 + 3);
                sub_404A90(&v442);
                off_77F3FC("SlotIndex %d, SkillIndex %d, Level %d", HIBYTE(a4), HIBYTE(a5), v442);
                if ( v442 != 0 )
                  sub_57A3C0(HIBYTE(a4), HIBYTE(a5));
                else
                  sub_57A3C0(HIBYTE(a4), 0);
                v431 = v442;
                sub_47DC90(HIBYTE(a5));
                sub_47DEC0(0, v431);
                *(uint32_t *)(sub_47DC90(HIBYTE(a5)) + 540) = 0;
                ++v282;
              }
              while ( v282 < HIBYTE(v444) );
            }
            sub_47E4F0();
            sub_44AB50(0, 12);
          }
        }
        else
        {
          v273 = sub_44E8D0((char *)dword_8F8528, (void *)0x27, v267, 0);
          v274 = __RTDynamicCast(
                   v273,
                   0,
                   &IRDPopupWindow `RTTI Type Descriptor',
                   &CNRDQuestRewardWindow `RTTI Type Descriptor',
                   0);
          HIBYTE(a5) = 0;
          sub_404A90((uint8_t *)&a5 + 3);
          off_77F3FC("ItemTypeNumber %d", HIBYTE(a5));
          v275 = 0;
          if ( HIBYTE(a5) != 0 )
          {
            do
            {
              a4 = 0;
              v444 = 0;
              v447 = 0;
              sub_404AB0(&a4);
              sub_404AB0(&v444);
              sub_404AD0(&v447);
              off_77F3FC("SlotIndex %d, ItemIndex %d, Data %d", (uint16_t)a4, (uint16_t)v444, v447);
              v276 = sub_44A980((uint16_t)a4);
              if ( v276 != 0 )
              {
                v277 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v276 + 60))(v276, (uint16_t)v444);
                v278 = *(uint32_t *)v276;
                if ( v277 != 0 )
                {
                  (*(void (/*thiscall*/ **)(int, int))(v278 + 48))(v276, v447);
                }
                else
                {
                  v279 = (*(int (/*thiscall*/ **)(int))(v278 + 16))(v276);
                  off_77F3FC(aD_1, (uint16_t)a4, *(uint32_t *)(v279 + 4));
                }
              }
              else
              {
                v276 = sub_522300((void *)(uint16_t)v444, v447, 0, 0, -1, 1);
                sub_484F40((int *)dword_8F852C, (uint16_t)a4, v276, 1);
              }
              if ( v274 != 0 )
              {
                v114 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v276 + 20))(v276, 1) == 0;
                v280 = v447;
                if ( v114 )
                  v280 = 1;
                sub_63F7E0(v276, v280);
              }
              if ( v275 == HIBYTE(a5) - 1 && v276 != 0 )
              {
                v281 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v276 + 56))(v276);
                sub_432EA0(v281, -1, 0, 0);
              }
              ++v275;
            }
            while ( v275 < HIBYTE(a5) );
          }
        }
        sub_47CD00(dword_8F8540);
        sub_546680((uint16_t)v438);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 4:
            v283 = sub_422E70(791);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v283, 0);
            break;
          case 0x13:
            off_77F3FC(aFail_34);
            break;
          case 0x16:
            off_77F3FC(aFail_33);
            break;
          default:
            break;
        }
      }
      return 1;
    case 37:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        HIBYTE(a4) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("Error %d TownIndex %d", HIBYTE(a5), HIBYTE(a4));
        if ( HIBYTE(a5) == 21 )
        {
          off_77F3FC(aFail_4);
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_5);
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
        }
        else if ( HIBYTE(a5) == 8 )
        {
          v284 = sub_4CE8A0((uint32_t *)dword_8F84F0, HIBYTE(a4));
          if ( v284 != 0 )
          {
            v432 = unknown_libname_2((uint32_t *)(v284 + 4));
            v285 = (const char *)sub_422E70(792);
            sprintf(Buffer, v285, v432);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
          }
          else
          {
            off_77F3FC(aCriticalError_39);
          }
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
        }
        else
        {
          if ( HIBYTE(a5) == 55 )
          {
            v286 = sub_422E70(1339);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v286, 0);
          }
          *(uint8_t *)(*(uint32_t *)(a1 + 20) + 116) = 0;
        }
      }
      return 1;
    case 41:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        a4 = 0;
        sub_404AB0(&a4);
        off_77F3FC("MonsterUniqueId %d", (uint16_t)a4);
        if ( HIBYTE(a5) == 21 )
          off_77F3FC(aFail_6);
        v287 = sub_45EBE0(529, (uint16_t)a4);
        if ( v287 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v287 + 84))(v287, 0);
      }
      return 1;
    case 42:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_36);
        }
        else if ( HIBYTE(a5) == 18 )
        {
          off_77F3FC(aFail_35);
        }
      }
      return 1;
    case 43:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AB0(&a5);
        off_77F3FC("ServerId %d", (uint16_t)a5);
        sub_4850B0((int *)dword_8F852C, 1, 1u);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 30, 2);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(
          dword_8F8520,
          (uint16_t)word_77F804);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a5);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);
        return 1;
      }
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0x13:
          off_77F3FC(aFail_40);
          break;
        case 0x15:
          off_77F3FC(aFail_39);
          break;
        case 0x12:
          off_77F3FC(aFail_38);
          break;
        case 0x11:
          off_77F3FC(aFail_37);
          break;
        case 0x16:
          off_77F3FC(aFail_7);
          break;
        default:
          break;
      }
      goto LABEL_747;
    case 44:
      if ( (uint8_t)a5 != 0 )
      {
        sub_458120(*((uint32_t *)dword_8F8528 + 609));
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
          off_77F3FC(aFail_41);
      }
      return 1;
    case 45:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 4 )
        {
          v288 = *((uint32_t **)dword_8F8528 + 7);
          v289 = sub_422E70(793);
          sub_43BEE0(v288, v289, -6567706, 0, -1);
        }
        else if ( HIBYTE(a5) == 21 )
        {
          off_77F3FC(aFail_8);
        }
        sub_484FF0(dword_8F852C);
        v290 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
        v291 = 0;
        a4 = sub_425100(v290);
        if ( (int)a4 > 0 )
        {
          do
          {
            v292 = (uint8_t *)sub_425A00(v291);
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v292 + 40))(v292, 289) != 0 )
              v292[977] = 0;
            ++v291;
          }
          while ( v291 < (int)a4 );
        }
      }
      return 1;
    case 46:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AB0(&a5);
        off_77F3FC("ItemSlotIndex %d", (uint16_t)a5);
        if ( sub_4856E0((int *)dword_8F852C, (uint16_t)a5) == 0 )
        {
          v108 = (char *)sub_422E70(794);
LABEL_733:
          off_77F3F8(v109, v108);
        }
        goto LABEL_265;
      }
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 8:
          v410 = 795;
LABEL_745:
          v293 = *((uint32_t **)dword_8F8528 + 7);
          v294 = sub_422E70(v410);
          break;
        case 0xE:
          v293 = *((uint32_t **)dword_8F8528 + 7);
          v294 = sub_422E70(796);
          break;
        case 0x11:
          off_77F3FC(aFail_9);
          sub_484FF0(dword_8F852C);
          return 1;
        case 0x13:
          v293 = *((uint32_t **)dword_8F8528 + 7);
          v294 = sub_422E70(797);
          break;
        case 0x17:
          v410 = 798;
          goto LABEL_745;
        default:
LABEL_747:
          sub_484FF0(dword_8F852C);
          return 1;
      }
      sub_43BEE0(v293, v294, -6567706, 0, -1);
      goto LABEL_747;
    case 47:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("ENUM_CMDPACKET_MOVE_MAP :: Error %d", HIBYTE(a5));
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(a1 + 28) + 16) + 44) + 472) = 0;
        switch ( HIBYTE(a5) )
        {
          case 0x13:
            off_77F3FC(aFail_43);
            break;
          case 0x14:
            off_77F3FC(aFail_42);
            break;
          case 0x12:
            off_77F3FC(aFail_10);
            break;
          default:
            break;
        }
        if ( ++dword_9B9308 == 5 )
        {
          sub_4232E0(&Time);
          v295 = sub_423020(&Time);
          v296 = sub_423040(&Time);
          v297 = sub_423060(&Time);
          a4 = sub_423080(&Time);
          v298 = sub_4633B0(dword_8F7C04);
          off_77F3FC(aD_2, v295, v296, v297, a4, v298);
          MEMORY[0x1D8] = 0;
        }
      }
      return 1;
    case 48:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_45);
        }
        else if ( HIBYTE(a5) == 22 )
        {
          off_77F3FC(aFail_44);
        }
      }
      return 1;
    case 49:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        *(uint32_t *)v446 = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AB0(&a4);
        sub_404AD0(v446);
        off_77F3FC("ItemSpace %d, SlotIndex %d, DropNumber %d", HIBYTE(a5), (uint16_t)a4, *(uint32_t *)v446);
        if ( HIBYTE(a5) != 0 )
        {
          if ( HIBYTE(a5) == 3 )
          {
            v299 = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_8F7C04 + 788))(
                     dword_8F7C04,
                     (uint16_t)a4,
                     a3,
                     a2);
            if ( v299 != 0 )
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v299 + 4))(v299, 1);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1080))(dword_8F7C04, (uint16_t)a4);
            (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 816))(
              dword_8F7C04,
              (uint16_t)a4,
              -1);
          }
        }
        else if ( sub_4850B0((int *)dword_8F852C, (uint16_t)a4, *(unsigned int *)v446) == 0 )
        {
          off_77F3FC((char *)&byte_72AB00);
          sub_47CD00(dword_8F8540);
          return 1;
        }
        sub_47CD00(dword_8F8540);
        return 1;
      }
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      if ( HIBYTE(a5) == 2 )
      {
        off_77F3FC(aFailDb);
        goto LABEL_780;
      }
      if ( HIBYTE(a5) == 17 )
      {
        v301 = *((uint32_t **)dword_8F8528 + 7);
        v302 = sub_422E70(799);
      }
      else
      {
        if ( HIBYTE(a5) != 19 )
        {
          if ( HIBYTE(a5) == 23 )
            off_77F3F8(v300, "item type error");
LABEL_780:
          HIBYTE(a4) = 0;
          sub_404A90((uint8_t *)&a4 + 3);
          off_77F3FC("ItemSpace %d", HIBYTE(a4));
          v102 = (uint32_t *)sub_432F00(HIBYTE(a4));
          if ( v102 != nullptr )
LABEL_243:
            sub_484FF0(v102);
          return 1;
        }
        v301 = *((uint32_t **)dword_8F8528 + 7);
        v302 = sub_422E70(800);
      }
      sub_43BEE0(v301, v302, -6567706, 0, -1);
      goto LABEL_780;
    case 50:
      if ( (uint8_t)a5 != 0 )
      {
        LOBYTE(a5) = 0;
        sub_404A90(&a5);
        off_77F3FC("EquipmentType %d", (uint8_t)a5);
        v303 = dword_8F7C04;
        v304 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, (uint8_t)a5);
        if ( v304 != 0 )
        {
          v305 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v304 + 188))(v304, v437, a2);
          v306 = sub_41A5E0(v305 + 32) == 1;
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 28, 2);
          v307 = *(uint32_t *)dword_8F8520;
          v308 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v303 + 48))(v303);
          (*(void (/*thiscall*/ **)(int, int))(v307 + 36))(dword_8F8520, v308);
          v309 = *(uint32_t *)dword_8F8520;
          v310 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v303 + 52))(v303);
          (*(void (/*thiscall*/ **)(int, int))(v309 + 36))(dword_8F8520, v310);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a5);
          if ( v306 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
          else
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
        }
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x11:
            off_77F3FC(aFail_49);
            break;
          case 0x13:
            off_77F3FC(aFail_48);
            break;
          case 0x16:
            off_77F3FC(aFail_47);
            break;
          case 0xB:
            off_77F3FC(aFail_46);
            break;
          default:
            break;
        }
      }
      return 1;
    case 52:
      if ( (uint8_t)a5 != 0 )
        return 1;
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("Error %d", HIBYTE(a5));
      if ( HIBYTE(a5) == 4 )
      {
        v408 = 801;
        goto LABEL_982;
      }
      if ( HIBYTE(a5) == 19 )
      {
        off_77F3FC(aFail_50);
        return 1;
      }
      if ( HIBYTE(a5) != 17 )
        return 1;
      v311 = sub_41C1B0();
      v312 = sub_41A5E0(v311 + 53);
      v415 = dword_9B759C[v312]
           - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
      v57 = (const char *)sub_422E70(802);
      goto LABEL_812;
    case 53:
      if ( (uint8_t)a5 != 0 )
      {
        for ( m = 0; m < 8; ++m )
        {
          HIBYTE(a5) = 0;
          sub_404A90((uint8_t *)&a5 + 3);
          off_77F3FC("IsReady %d", HIBYTE(a5));
          sub_48F580(m, HIBYTE(a5) != 0);
        }
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 4:
            v408 = 803;
            goto LABEL_982;
          case 0x13:
            off_77F3FC(aFail_51);
            break;
          case 0x11:
            v314 = sub_41C1B0();
            v315 = sub_41A5E0(v314 + 53);
            v415 = dword_9B759C[v315]
                 - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C
                                                                                             + 3));
            v57 = (const char *)sub_422E70(804);
LABEL_812:
            sprintf(v449, v57, v415);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v449, -6567706, 0, -1);
            break;
          case 0x37:
            v316 = sub_422E70(1341);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v316, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 54:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_53);
        }
        else if ( HIBYTE(a5) == 8 )
        {
          off_77F3FC(aFail_52);
        }
      }
      return 1;
    case 55:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 18 )
        {
          off_77F3FC(aFail_55);
        }
        else if ( HIBYTE(a5) == 22 )
        {
          off_77F3FC(aFail_54);
        }
      }
      return 1;
    case 56:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 0x12:
            off_77F3FC(aFail_58);
            break;
          case 8:
            off_77F3FC(aFail_57);
            break;
          case 0x13:
            off_77F3FC(aFail_56);
            break;
          default:
            break;
        }
      }
      return 1;
    case 57:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 18 )
        {
          off_77F3FC(aFail_60);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_59);
        }
      }
      return 1;
    case 58:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 8 )
        {
          off_77F3FC(aFail_62);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_61);
        }
      }
      return 1;
    case 59:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 8 )
        {
          off_77F3FC(aFail_64);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_63);
        }
      }
      return 1;
    case 61:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 8 )
        {
          off_77F3FC(aFail_66);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(aFail_65);
        }
      }
      return 1;
    case 62:
      HIBYTE(a5) = 0;
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(v441) = 0;
        HIBYTE(v445) = 0;
        HIBYTE(a4) = 0;
        v317 = (char *)sub_422E70(805);
        sub_48BCC0(Destination, 0x1Fu, v317);
        sub_404A90((uint8_t *)&v441 + 3);
        sub_404A90((uint8_t *)&v445 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC(
          "Name [%s], Level %d, Job %d, GrowType %d, Unique ID %d",
          Destination,
          HIBYTE(v441),
          HIBYTE(v445),
          HIBYTE(a4),
          HIBYTE(a5));
        sub_47B150(Destination, HIBYTE(v441), HIBYTE(v445), HIBYTE(a4), HIBYTE(a5));
        v318 = (const char *)sub_422E70(806);
        sprintf(Buffer, v318, Destination);
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        switch ( HIBYTE(a5) )
        {
          case 4:
            v319 = sub_422E70(807);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v319, 0);
            break;
          case 0x12:
            v320 = sub_422E70(808);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v320, 0);
            break;
          case 0x15:
            v321 = sub_422E70(809);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v321, 0);
            break;
          default:
            break;
        }
      }
      return 1;
    case 63:
      if ( (uint8_t)a5 != 0 )
      {
        v322 = (char *)sub_422E70(810);
        sub_48BCC0(Destination, 0x1Fu, v322);
        off_77F3FC("Name [%s]", Destination);
        sub_47A980(Destination);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("Error %d", HIBYTE(a5));
        if ( HIBYTE(a5) == 21 )
        {
          v323 = sub_422E70(811);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v323, 0);
        }
      }
      return 1;
    case 64:
      if ( (uint8_t)a5 == 0 )
        return 1;
      HIBYTE(a5) = 0;
      sub_404A90((uint8_t *)&a5 + 3);
      off_77F3FC("DebugCommand %d", HIBYTE(a5));
      switch ( HIBYTE(a5) )
      {
        case 0:
          word_8F7C14 = -1;
          word_8F7C10 = 0;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, 100);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
          a4 = *(uint32_t *)dword_9B0BBC;
          for ( *(uint32_t *)v446 = dword_9B0BBC; (uint8_t)sub_4296C0(v446) != 0; *(uint32_t *)v446 = dword_9B0BBC )
          {
            sub_4896B0(*(uint32_t *)(a4 + 12), 3);
            sub_442DF0((char *)&Time + 4, 0);
          }
          sub_41C270((int)v439, v324, 1u);
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(812);
          goto LABEL_983;
        case 1:
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(813);
          goto LABEL_983;
        case 2:
          v408 = 814;
          goto LABEL_982;
        case 3:
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(815);
          goto LABEL_983;
        case 4:
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(816);
          goto LABEL_983;
        case 5:
          v408 = 817;
          goto LABEL_982;
        case 6:
          v46 = *((uint32_t **)dword_8F8528 + 7);
          v47 = sub_422E70(818);
          goto LABEL_983;
        default:
          break;
      }
      return 1;
    case 66:
      *(uint32_t *)ArgList = 0;
      *(uint32_t *)v446 = 0;
      a4 = 0;
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AD0(&a5);
        sub_404AD0(&a4);
        sub_404AD0(v446);
        sub_404AD0(ArgList);
        off_77F3FC((char *)&byte_72A6C4, a5, a4, *(uint32_t *)v446, *(uint32_t *)ArgList);
        sub_5601C0(1, a5, a4, -1);
        if ( *(uint32_t *)v446 == *(uint32_t *)ArgList )
          sub_560140(1, a5);
      }
      else
      {
        HIBYTE(a5) = 0;
        *(uint32_t *)v440 = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AD0(&a4);
        sub_404AD0(v446);
        sub_404AD0(ArgList);
        sub_404AD0(v440);
        off_77F3FC((char *)&byte_72A678, HIBYTE(a5), a4, *(uint32_t *)v446, *(uint32_t *)ArgList, *(uint32_t *)v440);
        if ( HIBYTE(a5) == 55 )
        {
          v325 = sub_422E70(1340);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v325, 0);
        }
        else
        {
          sub_5601C0(0, a4, *(uint32_t *)v446, HIBYTE(a5));
          if ( *(uint32_t *)ArgList == *(uint32_t *)v440 )
            sub_560140(0, a4);
        }
      }
      return 1;
    case 67:
      if ( (uint8_t)a5 != 0 )
      {
        memset(v453, 0, sizeof(v453));
        v454 = 0;
        v455 = 0;
        a5 = 0;
        sub_48BCC0(v453, 0x40u, "ERROR!ERROR!");
        sub_404AD0(&a5);
        off_77F3FC("Cera Ticket : %s, Random Value : %d", v453, a5);
        sub_55CB10(v453, a5);
      }
      return 1;
    case 69:
      if ( (uint8_t)a5 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8514 + 12))(dword_8F8514);
        v326 = (char *)sub_422E70(819);
        sub_48BCC0(Destination, 0x1Fu, v326);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_406D60((size_t *)(dword_8F8514 + 20), Destination);
        off_77F3FC("ENUM_CMDPACKET_GUILD_MEMER_LIST - [%s] : %d guild members", Destination, HIBYTE(a5));
        for ( n = 0; n < HIBYTE(a5); ++n )
        {
          v328 = (char *)sub_422E70(820);
          sub_48BCC0(&v453[32], 0x1Fu, v328);
          v329 = (char *)sub_422E70(821);
          sub_48BCC0(v458, 0xDu, v329);
          sub_404AB0((uint16_t *)&v441 + 1);
          sub_404A90((uint8_t *)&v447 + 3);
          sub_404A90((uint8_t *)&a4 + 3);
          sub_404A90((uint8_t *)&v445 + 3);
          v330 = sub_47B150(&v453[32], SHIWORD(v441), SHIBYTE(v447), SHIBYTE(a4), 0);
          *(uint32_t *)(v330 + 40) = SHIBYTE(v445);
          v331 = (const char *)(v330 + 52);
          strcpy((char *)(v330 + 52), v458);
          v433 = *(uint32_t *)(v330 + 40);
          v413 = *(uint32_t *)(v330 + 28);
          v332 = (const char *)unknown_libname_2((uint32_t *)v330);
          off_77F3FC("\t[%s] as [%s]. Lv%d. Ch%d", v332, v331, v413, v433);
        }
        sub_479850(dword_8F8514);
        sub_478F20(dword_8F8514);
      }
      return 1;
    case 70:
      if ( (uint8_t)a5 != 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        switch ( HIBYTE(a5) )
        {
          case 1:
            sub_44E8D0((char *)dword_8F8528, (void *)0x34, 0, 1);
            break;
          case 0x1C:
            v334 = sub_422E70(822);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v334, 0);
            break;
          case 0x1D:
            v335 = sub_422E70(823);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v335, 0);
            break;
          case 0x1E:
            v336 = sub_422E70(824);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v336, 0);
            break;
          default:
            v337 = sub_422E70(825);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v337, 0);
            break;
        }
      }
      return 1;
    case 71:
      sub_4772A0(0);
      sub_45A420(2);
      return 1;
    case 72:
      sub_45A820(*((uint32_t *)dword_8F8528 + 609));
      a5 = 0;
      v349 = 1;
      for ( ii = 0; ii < 4; ++ii )
      {
        sub_404AB0(&a5);
        off_77F3FC(aD_3, ii, (int16_t)a5);
        if ( (uint16_t)a5 == 0 )
          v349 = 0;
      }
      *(uint8_t *)(*((uint32_t *)dword_8F8528 + 609) + 660) = v349;
      return 1;
    case 73:
      LOBYTE(a5) = 0;
      for ( jj = 0; jj < 4; ++jj )
      {
        sub_404A90(&a5);
        off_77F3FC(aD_4, jj, (char)a5);
        sub_4577F0(jj, a5);
      }
      return 1;
    case 74:
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a4) = 0;
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("btn %d event %d", HIBYTE(a4), HIBYTE(a5));
        sub_457FB0(SHIBYTE(a4), HIBYTE(a5));
      }
      else
      {
        off_77F3FC("EPLP COMMAND FAILED : errorEvent %d errorCode %d", 0, 0);
      }
      return 1;
    case 75:
      if ( (uint8_t)a5 != 0 )
      {
        v338 = sub_422E70(826);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v338, 0);
        v339 = sub_429900(dword_8F8500);
        v340 = (uint8_t *)sub_4BF1B0((int **)dword_8F851C, v339);
        v341 = v340;
        if ( v340 != nullptr )
        {
          v342 = sub_4BE1D0(v340);
          sub_4BE1E0(v341, v342 + 1);
        }
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        switch ( HIBYTE(a5) )
        {
          case 0x1F:
            v343 = sub_422E70(827);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v343, 0);
            break;
          case 0x20:
            v344 = sub_422E70(828);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v344, 0);
            break;
          case 0x21:
            v345 = sub_422E70(829);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v345, 0);
            break;
          case 0x22:
            v346 = sub_422E70(830);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v346, 0);
            break;
          case 0x23:
            v347 = sub_422E70(831);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v347, 0);
            break;
          default:
            v348 = sub_422E70(832);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v348, 0);
            break;
        }
      }
      return 1;
    case 76:
      if ( (uint8_t)a5 != 0 )
      {
        sub_404AD0(&a5);
        sub_404A90(&a4);
        v333 = sub_4BF1B0((int **)dword_8F851C, a5);
        if ( v333 == 0 )
          off_77F3FC("ENUM_CMDPACKET_GUILD_INFO - Unexpected guild information. guild = %d", a5);
        off_77F3FC(
          "ENUM_CMDPACKET_GUILD_INFO - guild information received. guild = %d, level = %d",
          a5,
          (uint8_t)a4);
        sub_4BE2B0(v333, a4);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC("ENUM_CMDPACKET_GUILD_INFO - generic error");
      }
      return 1;
    case 77:
      if ( (uint8_t)a5 != 0 )
      {
        sub_404AB0(&a5);
        sub_404AD0(&a4);
        v352 = (char *)sub_422E70(833);
        sub_48BCC0(&v453[32], 0x1Fu, v352);
        v353 = sub_429830(a5);
        v414 = unknown_libname_2((uint32_t *)(v353 + 16));
        v354 = (const char *)sub_422E70(834);
        sprintf(v448, v354, v414, &v453[32]);
        sub_44E8D0((char *)dword_8F8528, (void *)0x35, (int)v448, a4);
      }
      else
      {
        sub_404A90((uint8_t *)&a5 + 3);
        if ( HIBYTE(a5) == 3 )
        {
          v357 = sub_422E70(835);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v357, 0);
        }
        else if ( HIBYTE(a5) == 31 )
        {
          v356 = sub_422E70(836);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v356, 0);
        }
        else
        {
          if ( HIBYTE(a5) == 36 )
            v355 = sub_422E70(837);
          else
            v355 = sub_422E70(838);
LABEL_934:
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v355, 0);
        }
      }
      return 1;
    case 78:
      if ( (uint8_t)a5 != 0 )
      {
        v365 = (char *)sub_422E70(669);
        sub_48BCC0(&v453[12], 0x32u, v365);
        v366 = (const char *)sub_422E70(1508);
        sprintf(Buffer, v366, &v453[12]);
        off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s success", &v453[12]);
        goto LABEL_950;
      }
      v367 = (char *)sub_422E70(669);
      sub_48BCC0(&v453[12], 0x32u, v367);
      sub_404A90((uint8_t *)&a5 + 3);
      switch ( HIBYTE(a5) )
      {
        case '&':
          off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s already requested", &v453[12]);
          return 1;
        case '\'':
          v369 = (const char *)sub_422E70(1529);
          goto LABEL_955;
        case '(':
          v369 = (const char *)sub_422E70(1528);
LABEL_955:
          sprintf(Buffer, v369, &v453[12]);
          v370 = Buffer;
          goto LABEL_956;
        case ')':
          v373 = sub_422E70(1504);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v373, 0);
          return 1;
        case '*':
          v374 = sub_422E70(1505);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v374, 0);
          return 1;
        case '+':
          v375 = sub_422E70(1506);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v375, 0);
          return 1;
        case ',':
          off_77F3FC("ENUM_CMDPACKET_REQUEST_MEMBER_ENTER : %s does not reply", &v453[12]);
          return 1;
        case '.':
          v376 = sub_422E70(1526);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v376, 0);
          return 1;
        case '/':
        case '0':
          v368 = sub_422E70(1530);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v368, 0);
          return 1;
        case '1':
          v371 = sub_422E70(1503);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v371, 0);
          return 1;
        case '2':
          v372 = sub_422E70(1502);
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v372, 0);
          return 1;
        default:
          v434 = HIBYTE(a5);
          v377 = (const char *)sub_422E70(1507);
          sprintf(v450, v377, v434);
          v370 = v450;
LABEL_956:
          sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v370, 0);
          break;
      }
      return 1;
    case 79:
      if ( (uint8_t)a5 != 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        v378 = (char *)sub_422E70(669);
        sub_48BCC0(&v453[12], 0x32u, v378);
        if ( HIBYTE(a5) == 1 || HIBYTE(a5) == 2 )
        {
          v380 = (const char *)sub_422E70((HIBYTE(a5) != 1) + 1509);
          sprintf(Buffer, v380, &v453[12]);
          sub_478F40(1);
        }
        else
        {
          v379 = (const char *)sub_422E70(1524);
          sprintf(Buffer, v379);
        }
LABEL_950:
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
      }
      else
      {
        off_77F3FC("ENUM_CMDPACKET_MEMBER_ENTER_REPLY failed");
      }
      return 1;
    case 80:
      if ( (uint8_t)a5 != 0 )
      {
        v362 = (char *)sub_422E70(669);
        sub_48BCC0(&v453[12], 0x32u, v362);
        off_77F3FC("ENUM_CMDPACKET_MEMBER_SECEDE : %s removed", &v453[12]);
        v363 = (const char *)sub_422E70(1514);
        sprintf(Buffer, v363, &v453[12]);
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
        sub_478F40(1);
        sub_478EA0(1);
      }
      else
      {
        v364 = sub_422E70(1501);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v364, 0);
      }
      return 1;
    case 81:
      if ( (uint8_t)a5 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8518 + 12))(dword_8F8518);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404A90((uint8_t *)&a4 + 3);
        sub_48BCC0(&v453[12], 0x32u, (char *)szPassword);
        v358 = sub_47B150(&v453[12], HIBYTE(a4), 1, 0, 0);
        *(uint32_t *)(v358 + 40) = SHIBYTE(a5);
        HIDWORD(Time) = strlen(&v453[12]);
        if ( HIDWORD(Time) != 0 )
          off_77F3FC("\tupper member- level:%d name:%s channel:%d", HIBYTE(a4), &v453[12], SHIBYTE(a5));
        sub_404A90((uint8_t *)&v445 + 3);
        off_77F3FC("\t%d lower members founded", HIBYTE(v445));
        v359 = 0;
        if ( HIBYTE(v445) != 0 )
        {
          do
          {
            sub_404A90((uint8_t *)&a5 + 3);
            sub_404A90((uint8_t *)&a4 + 3);
            v360 = (char *)sub_422E70(669);
            sub_48BCC0(&v453[12], 0x32u, v360);
            v361 = sub_47B150(&v453[12], HIBYTE(a4), 1, 0, 0);
            *(uint32_t *)(v361 + 40) = SHIBYTE(a5);
            off_77F3FC("\tlower member - level:%d name:%s channel:%d", HIBYTE(a4), &v453[12], SHIBYTE(a5));
            ++v359;
          }
          while ( v359 < HIBYTE(v445) );
        }
        sub_478FC0(dword_8F8518);
        sub_479850(dword_8F8518);
      }
      else
      {
        off_77F3FC("ENUM_CMDPACKET_CALL_MEMER_LIST failed");
      }
      return 1;
    case 82:
      sub_484FF0(dword_8F852C);
      if ( (uint8_t)a5 == 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        switch ( HIBYTE(a5) )
        {
          case 4:
            v355 = sub_422E70(1658);
            goto LABEL_934;
          case 0xA:
            v355 = sub_422E70(1660);
            goto LABEL_934;
          case 0xD:
            v355 = sub_422E70(1654);
            goto LABEL_934;
          case 0x11:
            v355 = sub_422E70(1652);
            goto LABEL_934;
          case 0x16:
            v355 = sub_422E70(1661);
            goto LABEL_934;
          default:
            v435 = HIBYTE(a5);
            v391 = (const char *)sub_422E70(1662);
            goto LABEL_1019;
        }
      }
      sub_4E9A50(&v453[4]);
      v461 = 2;
      sub_404AB0((uint16_t *)&v444 + 1);
      sub_404AD0(v446);
      sub_404A90((uint8_t *)&a5 + 3);
      sub_404A90((uint8_t *)&v445 + 3);
      sub_404AB0((uint16_t *)&v441 + 1);
      off_77F3FC(
        "ENUM_CMDPACKET_UPGRADE_ITEM - slot:%d num:%d type:%d grade:%d slot:%d",
        HIWORD(v444),
        *(uint32_t *)v446,
        HIBYTE(a5),
        HIBYTE(v445),
        HIWORD(v441));
      sub_54D2B0(HIBYTE(a5));
      v392 = HIWORD(v444);
      v393 = (int *)dword_8F852C;
      v394 = sub_44A980(HIWORD(v444));
      if ( v394 == 0 )
      {
        v404 = sub_422E70(1661);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v404, 0);
        off_77F3FC("ENUM_CMDPACKET_UPGRADE_ITEM - ERROR!!! slot %d is NULL", HIWORD(v444));
        v461 = -1;
        sub_445150(&v453[4]);
        return 1;
      }
      if ( *(uint32_t *)v446 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v394 + 40))(v394, *(uint32_t *)v446);
      else
        sub_484D50(v393, v392);
      v395 = sub_44A980(HIWORD(v441));
      v396 = v395;
      if ( v395 == 0 )
      {
        v397 = sub_422E70(1658);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v397, 0);
        off_77F3FC("ENUM_CMDPACKET_UPGRADE_ITEM - ERROR!!! equipment is NULL");
        v461 = -1;
        sub_445150(&v453[4]);
        return 1;
      }
      v398 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v395 + 188))(v395);
      sub_4E9FA0(&v453[4], v398);
      if ( HIBYTE(a5) <= 2u )
      {
        sub_41C150((unsigned int)&v453[8], v399, HIBYTE(v445));
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v396 + 184))(v396, &v453[4]);
        sub_44E8D0((char *)dword_8F8528, (void *)0x3C, v396, HIBYTE(a5));
      }
      else
      {
        sub_583B50();
        sub_484D50((int *)dword_8F852C, HIWORD(v441));
        sub_44E8D0((char *)dword_8F8528, (void *)0x3C, 0, HIBYTE(a5));
        sub_404A90((uint8_t *)&a4 + 3);
        off_77F3FC("\t%d item added", HIBYTE(a4));
        v400 = 0;
        if ( HIBYTE(a4) != 0 )
        {
          do
          {
            sub_404AB0((uint16_t *)&v447 + 1);
            sub_404AB0((uint16_t *)&v439 + 1);
            sub_404AD0(&v438);
            sub_63B040(HIWORD(v439), v438);
            off_77F3FC("\tslot:%d index:%d info:%d", HIWORD(v447), HIWORD(v439), v438);
            v401 = sub_44A980(HIWORD(v447));
            v402 = v401;
            if ( v401 != 0 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v401 + 60))(v401, HIWORD(v439)) != 0 )
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v402 + 48))(v402, v438);
              else
                off_77F3FC("%dslot is not empty. stack impossible", HIWORD(v447));
            }
            else
            {
              v403 = sub_522300((void *)HIWORD(v439), v438, 0, 0, -1, 1);
              sub_484F40((int *)dword_8F852C, HIWORD(v447), v403, 0);
            }
            ++v400;
          }
          while ( v400 < HIBYTE(a4) );
          v461 = -1;
          sub_445150(&v453[4]);
          return 1;
        }
      }
      v461 = -1;
      sub_445150(&v453[4]);
      return 1;
    case 83:
      sub_484FF0(dword_8F852C);
      if ( (uint8_t)a5 == 0 )
      {
        sub_404A90((uint8_t *)&a5 + 3);
        switch ( HIBYTE(a5) )
        {
          case 4:
            v387 = sub_422E70(1695);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v387, 0);
            break;
          case 0xD:
            v390 = sub_422E70(1696);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v390, 0);
            break;
          case 0x11:
            v386 = sub_422E70(1657);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v386, 0);
            break;
          case 0x12:
            v389 = sub_422E70(1694);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v389, 0);
            break;
          case 0x13:
            v388 = sub_422E70(1690);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v388, 0);
            break;
          case 0x16:
            v385 = sub_422E70(1661);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v385, 0);
            break;
          default:
            v435 = HIBYTE(a5);
            v391 = (const char *)sub_422E70(1698);
LABEL_1019:
            sprintf(v450, v391, v435);
            sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v450, 0);
            break;
        }
        return 1;
      }
      sub_404AB0((uint16_t *)&a5 + 1);
      sub_404AD0(v446);
      sub_404AB0((uint16_t *)&a4 + 1);
      off_77F3FC("ENUM_CMDPACKET_RESET_ITEM_ATTR - slot %d, num %d, type %d", HIWORD(a5), *(uint32_t *)v446, HIWORD(a4));
      v381 = HIWORD(a5);
      v382 = (int *)dword_8F852C;
      if ( sub_44A980(HIWORD(a5)) != 0 )
      {
        v383 = *(uint32_t *)v446;
        if ( *(uint32_t *)v446 != 0 )
        {
          v384 = sub_44A980(v381);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v384 + 40))(v384, v383);
        }
        else
        {
          sub_484D50(v382, v381);
        }
      }
      else
      {
        off_77F3FC("ENUM_CMDPACKET_RESET_ITEM_ATTR - slot %d is NULL", v381);
      }
      if ( HIWORD(a4) == 1 )
      {
        v46 = *((uint32_t **)dword_8F8528 + 7);
        v47 = sub_422E70(1699);
        goto LABEL_983;
      }
      if ( HIWORD(a4) != 2 )
        return 1;
      v408 = 1700;
LABEL_982:
      v46 = *((uint32_t **)dword_8F8528 + 7);
      v47 = sub_422E70(v408);
      goto LABEL_983;
    case 84:
      if ( (uint8_t)a5 != 0 )
      {
        sub_541AE0();
        sub_404AD0(v446);
        sub_404AD0(ArgList);
        sub_404AD0(v440);
        sub_404AB0((uint16_t *)&v447 + 1);
        sub_404AB0((uint16_t *)&a4 + 1);
        sub_404AD0(&v438);
        sub_404A90((uint8_t *)&a5 + 3);
        sub_404AB0((uint16_t *)&v445 + 1);
        off_77F3FC(
          "Money %d, Medal %d, Cash %d, ItemSlotIndex %d, ItemIndex %d, Data %d",
          *(uint32_t *)v446,
          *(uint32_t *)ArgList,
          *(uint32_t *)v440,
          HIWORD(v447),
          HIWORD(a4),
          v438);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          *(uint32_t *)v446);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),
          *(uint32_t *)ArgList);
        dword_8F7C0C = *(uint32_t *)v440;
        if ( *(int *)v440 < 0 )
        {
          off_77F3FC(aCriticalError_31, *(uint32_t *)v440);
          dword_8F7C0C = 0;
        }
        sub_541C60(SBYTE2(v447), (void *)HIWORD(a4), v438, HIBYTE(a5), HIWORD(v445));
      }
      else
      {
        sub_541AE0();
        sub_404A90((uint8_t *)&a5 + 3);
        sub_542000(SHIBYTE(a5));
      }
      return 1;
    case 85:
      if ( (uint8_t)a5 == 0 )
        goto LABEL_1038;
      sub_541AE0();
      sub_404AB0((uint16_t *)&v444 + 1);
      sub_404A90((uint8_t *)&a5 + 3);
      sub_541A60(2);
      v436 = HIWORD(v444);
      sub_541A30();
      sub_5419F0(v436);
      for ( ; HIBYTE(a5) != 0; --HIBYTE(a5) )
      {
        sub_404AB0((uint16_t *)&v441 + 1);
        sub_404AD0(ArgList);
        sub_404AB0((uint16_t *)&v445 + 1);
        sub_404AD0(v446);
        sub_404A90((uint8_t *)&a4 + 3);
        sub_404AB0((uint16_t *)&v447 + 1);
        v405 = sub_541A30();
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v405 + 56))(
          v405,
          HIWORD(v441),
          *(uint32_t *)ArgList,
          HIWORD(v445),
          *(uint32_t *)v446,
          HIBYTE(a4),
          HIWORD(v447));
        off_77F3FC(
          " slot %d, price %d, index %d, data %d, upgarade %d, durability %d",
          HIWORD(v441),
          *(uint32_t *)ArgList,
          HIWORD(v445),
          *(uint32_t *)v446,
          HIBYTE(a4),
          HIWORD(v447));
      }
      return 1;
    case 86:
    case 90:
LABEL_1038:
      sub_541AE0();
      return 1;
    case 87:
      if ( (uint8_t)a5 != 0 )
      {
        sub_541AE0();
        off_77F3FC((char *)&byte_72A0DC);
        sub_430230(dword_8F7C08);
        off_77F3FC((char *)&byte_72A0BC);
        sub_541A60(0);
      }
      else
      {
        sub_541AE0();
        sub_404A90((uint8_t *)&a5 + 3);
        sub_5420A0(SHIBYTE(a5));
      }
      return 1;
    case 88:
      if ( (uint8_t)a5 != 0 )
      {
        sub_541AE0();
        sub_42FBE0((uint32_t *)dword_8F7C08);
        sub_542AD0();
      }
      else
      {
        sub_541AE0();
        sub_404A90((uint8_t *)&a5 + 3);
        sub_542190(SHIBYTE(a5));
      }
      return 1;
    case 89:
      if ( (uint8_t)a5 != 0 )
      {
        sub_541AE0();
        sub_42FBF0((uint32_t *)dword_8F7C08);
        sub_541A60(1);
      }
      else
      {
        sub_541AE0();
        sub_404A90((uint8_t *)&a5 + 3);
        sub_542220(SHIBYTE(a5));
      }
      return 1;
    case 92:
      if ( (uint8_t)a5 != 0 )
      {
        a4 = 0;
        a5 = 0;
        sub_404AD0(&a4);
        sub_404AB0(&a5);
        v406 = *(uint32_t *)(a1 + 40);
        if ( *(uint32_t *)(v406 + 32) == 1 )
          sub_583A80(v406, (uint16_t)a5);
      }
      else
      {
        HIBYTE(v439) = 0;
        sub_404A90((uint8_t *)&v439 + 3);
        switch ( HIBYTE(v439) )
        {
          case 4:
            off_77F3FC((char *)&byte_729EF4);
            break;
          case 0xA:
            off_77F3FC(byte_729F08);
            break;
          case 0x13:
LABEL_1077:
            off_77F3FC(byte_729F14);
            break;
          default:
            off_77F3FC("err %d", HIBYTE(v439));
            break;
        }
      }
      return 1;
    case 94:
      if ( (uint8_t)a5 != 0 )
      {
        HIBYTE(a5) = -1;
        sub_404A90((uint8_t *)&a5 + 3);
        off_77F3FC((char *)&byte_72A078, HIBYTE(a5));
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        if ( HIBYTE(a5) == 18 )
        {
          off_77F3FC(byte_72A004);
        }
        else if ( HIBYTE(a5) == 19 )
        {
          off_77F3FC(byte_72A020);
        }
        else
        {
          off_77F3FC((char *)&byte_72A054, HIBYTE(a5));
        }
      }
      return 1;
    case 95:
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        if ( HIBYTE(a5) == 18 )
        {
          off_77F3FC(byte_729FBC);
        }
        else if ( HIBYTE(a5) == 22 )
        {
          off_77F3FC(byte_729FD8);
        }
      }
      return 1;
    case 96:
      if ( (uint8_t)a5 != 0 )
      {
        sub_525130();
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_523390(HIBYTE(a5));
      }
      return 1;
    case 97:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AD0(&a5);
        sub_524760(a5);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_523340(HIBYTE(a5));
      }
      return 1;
    case 98:
      if ( (uint8_t)a5 != 0 )
      {
        a5 = 0;
        sub_404AB0(&a5);
        sub_524790((int16_t)a5);
      }
      else
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        sub_522E50(HIBYTE(a5));
      }
      return 1;
    case 100:
      if ( dword_9B9534 != 0 )
        sub_642410(1);
      if ( dword_9B9454 != 0 )
        sub_62DFD0(1);
      if ( (uint8_t)a5 == 0 )
      {
        HIBYTE(a5) = 0;
        sub_404A90((uint8_t *)&a5 + 3);
        switch ( HIBYTE(a5) )
        {
          case 4:
            off_77F3FC(byte_729FA0);
            break;
          case 0x11:
            off_77F3FC(byte_729F98);
            break;
          case 0x13:
            goto LABEL_1077;
          case 0x37:
            off_77F3FC(byte_729F70);
            break;
          default:
            off_77F3FC(byte_729F50);
            break;
        }
      }
      return 1;
    default:
      return 1;
  }
}

