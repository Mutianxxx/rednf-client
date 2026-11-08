// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_57A980_sub_57A980.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x57A980）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 5018 行；字符串证据 5 条；外调 6 个
//   串: "Client Version %d %d %d %d"
//   串: "Server Version %d %d %d %d"
//   串: "Run Error"
//   串: "EquipmentNumber %d"
//   串: "SkillNumber %d"
//   调: sub_57A980 sub_404AF0 sub_422E70 sub_48BCC0 sub_404AD0 sub_404A90
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x57A980 sub_57A980  size=36584
// ------------------------------------------------------------
unsigned int /*fastcall*/ sub_57A980(uint32_t *a1, int a2, int ArgList)
{
  int v3; // eax
  uint32_t *v4; // edi
  char *v5; // eax
  const char *v6; // eax
  char v7; // ecx^2
  char v8; // al
  char v9; // edx^2
  int v10; // eax
  HWND v11; // esi
  const CHAR *v12; // eax
  int v14; // edi
  int v15; // esi
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // eax
  bool v32; // cc
  int i; // edi
  int v34; // eax
  int v35; // edi
  char *v36; // eax
  int v37; // esi
  const char *v38; // esi
  int v39; // eax
  const char *v40; // ecx
  int *v41; // esi
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // esi
  int v46; // eax
  int v47; // ebx
  int v48; // esi
  uint32_t *v49; // eax
  int v50; // eax
  int v51; // esi
  const char *v52; // eax
  void *v53; // eax
  int *v54; // esi
  int v55; // edx
  int v56; // ecx
  int v57; // esi
  int v58; // esi
  int v59; // ebx
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // esi
  int v65; // eax
  int v66; // esi
  int v67; // eax
  int v68; // esi
  const char *v69; // eax
  int v70; // eax
  const char *v71; // eax
  int v72; // eax
  uint32_t *v73; // ebx
  uint32_t *v74; // edx
  char v75; // al
  char *v76; // eax
  int **v77; // esi
  int j; // edi
  int k; // esi
  int m; // esi
  uint32_t *v81; // edx
  int v82; // eax
  int n; // edi
  int v84; // esi
  int v85; // eax
  int v86; // esi
  uint16_t *v87; // edi
  int v88; // eax
  int v89; // esi
  int v90; // eax
  int v91; // esi
  int v92; // eax
  int v93; // edi
  int v94; // eax
  uint32_t *v95; // esi
  char *v96; // ebx
  uint32_t *v97; // eax
  const char *v98; // eax
  int v99; // eax
  int v100; // eax
  int v101; // esi
  int v102; // eax
  char v103; // bl
  int ii; // edi
  int v105; // esi
  int v106; // eax
  const char *v107; // eax
  int v108; // esi
  int v109; // eax
  int v110; // ecx
  const char *v111; // eax
  const char *v112; // eax
  int v113; // esi
  int v114; // ecx
  char *v115; // eax
  int v116; // eax
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // esi
  const char *v122; // eax
  const char *v123; // eax
  char *v124; // eax
  const char *v125; // eax
  char *v126; // eax
  char *v127; // eax
  int v128; // edi
  int v129; // ecx
  int v130; // esi
  int v131; // eax
  int v132; // ebx
  int v133; // ecx
  int *v134; // esi
  char v135; // al
  int (/*thiscall*/ **v136)(int *); // edx
  unsigned int v137; // eax
  int v138; // eax
  bool v139; // bl
  int v140; // eax
  int v141; // edx
  int v142; // esi
  uint32_t *v143; // edi
  uint32_t *v144; // ebx
  uint32_t *jj; // esi
  int v146; // eax
  int v147; // edx
  uint16_t v148; // si
  int v149; // ebx
  int *v150; // esi
  int v151; // eax
  int v152; // eax
  int v153; // edx
  int kk; // esi
  int v155; // eax
  int v156; // esi
  int v157; // eax
  int v158; // ebx
  uint32_t *v159; // edi
  int v160; // ebx
  int v161; // eax
  int v162; // edi
  int v163; // eax
  int v164; // eax
  int v165; // edx
  int v166; // eax
  int v167; // eax
  uint32_t *v168; // eax
  int v169; // ebx
  int v170; // eax
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // esi
  int v175; // eax
  int *v176; // edi
  void *v177; // eax
  int v178; // ebx
  int v179; // eax
  int v180; // ebx
  int v181; // eax
  int v182; // eax
  int v183; // esi
  int v184; // esi
  int v185; // edi
  int v186; // eax
  int v187; // esi
  const char *v188; // eax
  int v189; // esi
  int v190; // esi
  int v191; // eax
  int v192; // eax
  int v193; // edi
  int v194; // esi
  int v195; // eax
  int v196; // edx
  int v197; // eax
  int v198; // eax
  int v199; // esi
  int v200; // esi
  int mm; // esi
  int v202; // eax
  int v203; // ecx
  int v204; // esi
  int v205; // edi
  int nn; // esi
  int v207; // eax
  int v208; // ecx
  int v209; // esi
  void *v210; // eax
  uint8_t v211; // al
  int v212; // esi
  void *v213; // eax
  uint32_t *v214; // edx
  int v215; // esi
  double v216; // st7
  int v217; // edx
  double v218; // st7
  int v219; // edx
  double v220; // st7
  char v221; // al
  int v222; // edx
  uint64_t v223; // rax
  const char *v224; // eax
  int v225; // ebx
  int i1; // esi
  int v227; // edi
  int v228; // eax
  int v229; // edx
  int v230; // eax
  uint32_t *v231; // edi
  int v232; // ecx
  int *v233; // eax
  int v234; // ebx
  int *v235; // esi
  int v236; // eax
  int v237; // edi
  int v238; // eax
  int v239; // edi
  int v240; // eax
  int v241; // eax
  int v242; // edi
  int v243; // ebx
  int v244; // eax
  int v245; // eax
  int v246; // eax
  int v247; // edi
  int v248; // edx
  int v249; // eax
  int v250; // edx
  int v251; // ecx
  int v252; // edi
  const char *v253; // eax
  int v254; // eax
  int v255; // ecx
  const char *v256; // eax
  int i2; // edi
  int v258; // eax
  int v259; // esi
  int v260; // eax
  int v261; // ecx
  uint8_t *v262; // esi
  int v263; // eax
  int v264; // eax
  uint32_t *v265; // esi
  int v266; // ebx
  int v267; // esi
  int v268; // eax
  int v269; // edi
  int v270; // esi
  int v271; // eax
  int v272; // edi
  int v273; // eax
  int v274; // esi
  int v275; // ebx
  int v276; // eax
  int v277; // ebx
  int v278; // eax
  int64_t v279; // rax
  int v280; // esi
  const char *v281; // eax
  const char *v282; // eax
  const char *v283; // eax
  const char *v284; // eax
  const char *v285; // eax
  int v286; // eax
  int v287; // eax
  int v288; // edx
  int v289; // eax
  uint32_t *v290; // esi
  int v291; // ebx
  int v292; // ebx
  int v293; // eax
  int v294; // eax
  int v295; // eax
  int v296; // edx
  int v297; // ebx
  int v298; // eax
  int v299; // eax
  int v300; // eax
  const char *v301; // eax
  int v302; // eax
  uint32_t *v303; // ebx
  uint32_t *v304; // eax
  int v305; // eax
  int v306; // ebx
  int v307; // eax
  int v308; // eax
  int v309; // esi
  int v310; // esi
  int i4; // edi
  int i3; // esi
  char v313; // bl
  uint8_t v314; // al
  int v315; // ebx
  const char *v316; // eax
  int v317; // edx
  unsigned int v318; // eax
  char *v319; // edi
  char v320; // cl
  int *v321; // ecx
  int v322; // eax
  int v323; // eax
  int v324; // edi
  int v325; // eax
  int v326; // ebx
  uint32_t *v327; // eax
  uint32_t *v328; // esi
  int v329; // ebx
  int v330; // eax
  int v331; // eax
  int v332; // eax
  int v333; // edi
  int v334; // edi
  int v335; // edi
  int v336; // edx
  int v337; // eax
  const char *v338; // eax
  int v339; // eax
  int v340; // eax
  int v341; // edi
  uint32_t *v342; // esi
  int v343; // ebx
  int v344; // ecx
  int v345; // eax
  int v346; // ebx
  uint32_t *v347; // eax
  uint32_t *v348; // edi
  int v349; // ebx
  int v350; // eax
  int v351; // eax
  int v352; // eax
  int v353; // esi
  int v354; // esi
  int v355; // esi
  int v356; // edx
  int v357; // eax
  const char *v358; // eax
  int v359; // esi
  int *v360; // esi
  int v361; // edx
  char *v362; // eax
  uint32_t *v363; // esi
  int v364; // edi
  uint32_t *v365; // ebx
  int v366; // esi
  uint32_t *v367; // edi
  uint32_t *v368; // ebx
  int v369; // ecx
  int v370; // ebx
  int v371; // esi
  int v372; // ebx
  int v373; // esi
  bool v374; // bl
  int v375; // esi
  int v376; // eax
  char v377; // cl
  int v378; // esi
  bool v379; // bl
  uint16_t v380; // ax
  int v381; // esi
  int v382; // ebx
  int v383; // esi
  int v384; // esi
  int v385; // eax
  int v386; // eax
  int v387; // eax
  int v388; // eax
  int v389; // edx
  int *v390; // esi
  int v391; // eax
  int *v392; // esi
  int v393; // eax
  int v394; // edx
  int v395; // ebx
  int v396; // eax
  int v397; // ebx
  uint64_t v398; // rax
  int v399; // ebx
  uint16_t v400; // bx
  int v401; // eax
  int v402; // eax
  int v403; // edx
  int v404; // ebx
  int v405; // eax
  int v406; // edx
  int v407; // eax
  int v408; // ecx
  int v409; // edi
  const char *v410; // eax
  int v411; // eax
  void *v412; // eax
  int v413; // eax
  int v414; // eax
  int v415; // ecx
  const char *v416; // eax
  int v417; // edi
  int v418; // eax
  int v419; // esi
  int v420; // eax
  int v421; // esi
  int v422; // ecx
  int v423; // eax
  int v424; // esi
  int v425; // eax
  int v426; // eax
  int v427; // eax
  int v428; // eax
  int v429; // esi
  int v430; // eax
  int v431; // eax
  int v432; // eax
  int v433; // esi
  int v434; // edi
  int v435; // ebx
  uint64_t v436; // rax
  uint64_t v437; // rax
  const char *v438; // eax
  const char *v439; // eax
  const char *v440; // eax
  const char *v441; // eax
  int v442; // eax
  int v443; // esi
  char *v444; // eax
  int v445; // esi
  char *v446; // eax
  char *v447; // eax
  int v448; // esi
  const char *v449; // eax
  char v450; // al
  int v451; // eax
  unsigned int v452; // esi
  char *v453; // eax
  char *v454; // eax
  char *v455; // eax
  const char *v456; // eax
  char *v457; // eax
  char *v458; // eax
  const char *v459; // eax
  int v460; // eax
  int v461; // eax
  int v462; // eax
  int v463; // ecx
  char *v464; // eax
  char *v465; // eax
  const char *v466; // eax
  int v467; // eax
  char *v468; // eax
  char *v469; // eax
  char *v470; // eax
  const char *v471; // eax
  const char *v472; // eax
  char *v473; // eax
  const char *v474; // eax
  char *v475; // eax
  int v476; // eax
  const char *v477; // eax
  const char *v478; // eax
  int v479; // eax
  int v480; // eax
  int v481; // eax
  int v482; // eax
  int v483; // eax
  int v484; // eax
  int v485; // eax
  int v486; // eax
  const char *v487; // eax
  int v488; // eax
  int *v489; // eax
  void **v490; // esi
  int v491; // esi
  uint32_t *v492; // esi
  int v493; // edi
  int v494; // ebx
  int v495; // eax
  int v496; // eax
  int v497; // esi
  const char *v498; // eax
  int v499; // esi
  int v500; // eax
  int v501; // edi
  int v502; // esi
  int v503; // esi
  int v504; // eax
  int v505; // eax
  int v506; // esi
  void *v507; // [esp+8h] [ebp-948h]
  int v508; // [esp+Ch] [ebp-944h]
  int v509; // [esp+Ch] [ebp-944h]
  int v510; // [esp+Ch] [ebp-944h]
  int v511; // [esp+Ch] [ebp-944h]
  int64_t v512; // [esp+Ch] [ebp-944h]
  int v513; // [esp+Ch] [ebp-944h]
  const char *v514; // [esp+10h] [ebp-940h]
  int v515; // [esp+10h] [ebp-940h]
  int v516; // [esp+10h] [ebp-940h]
  int v517; // [esp+10h] [ebp-940h]
  uint64_t v518; // [esp+10h] [ebp-940h]
  int64_t v519; // [esp+10h] [ebp-940h]
  int v520; // [esp+10h] [ebp-940h]
  int v521; // [esp+10h] [ebp-940h]
  int v522; // [esp+10h] [ebp-940h]
  double v523; // [esp+10h] [ebp-940h]
  int64_t v524; // [esp+10h] [ebp-940h]
  int v525; // [esp+10h] [ebp-940h]
  int v526; // [esp+10h] [ebp-940h]
  int v527; // [esp+14h] [ebp-93Ch]
  int v528; // [esp+14h] [ebp-93Ch]
  int v529; // [esp+14h] [ebp-93Ch]
  int v530; // [esp+14h] [ebp-93Ch]
  int v531; // [esp+14h] [ebp-93Ch]
  uint32_t *v532; // [esp+14h] [ebp-93Ch]
  int v533; // [esp+14h] [ebp-93Ch]
  int v534; // [esp+14h] [ebp-93Ch]
  int v535; // [esp+14h] [ebp-93Ch]
  int v536; // [esp+14h] [ebp-93Ch]
  int v537; // [esp+14h] [ebp-93Ch]
  int v538; // [esp+14h] [ebp-93Ch]
  int v539; // [esp+14h] [ebp-93Ch]
  int v540; // [esp+14h] [ebp-93Ch]
  int v541; // [esp+14h] [ebp-93Ch]
  int v542; // [esp+14h] [ebp-93Ch]
  void *v543; // [esp+14h] [ebp-93Ch]
  int v544; // [esp+14h] [ebp-93Ch]
  int v545; // [esp+14h] [ebp-93Ch]
  int v546; // [esp+14h] [ebp-93Ch]
  int v547; // [esp+14h] [ebp-93Ch]
  int v548; // [esp+14h] [ebp-93Ch]
  int v549; // [esp+14h] [ebp-93Ch]
  int v550; // [esp+14h] [ebp-93Ch]
  int v551; // [esp+14h] [ebp-93Ch]
  int v552; // [esp+14h] [ebp-93Ch]
  int v553; // [esp+14h] [ebp-93Ch]
  int v554; // [esp+14h] [ebp-93Ch]
  int v555; // [esp+14h] [ebp-93Ch]
  int v556; // [esp+14h] [ebp-93Ch]
  int v557; // [esp+14h] [ebp-93Ch]
  int v558; // [esp+18h] [ebp-938h]
  int v559; // [esp+1Ch] [ebp-934h]
  char v560[60]; // [esp+24h] [ebp-92Ch] BYREF
  char v561[60]; // [esp+60h] [ebp-8F0h] BYREF
  char v562[60]; // [esp+9Ch] [ebp-8B4h] BYREF
  int v563; // [esp+108h] [ebp-848h] BYREF
  int64_t v564; // [esp+10Ch] [ebp-844h] BYREF
  int v565; // [esp+114h] [ebp-83Ch] BYREF
  uint32_t *v566; // [esp+118h] [ebp-838h] BYREF
  int v567; // [esp+11Ch] [ebp-834h] BYREF
  char v568[4]; // [esp+120h] [ebp-830h] BYREF
  uint8_t v569; // [esp+126h] [ebp-82Ah] BYREF
  uint8_t v570; // [esp+127h] [ebp-829h] BYREF
  int v571; // [esp+128h] [ebp-828h] BYREF
  int v572; // [esp+12Ch] [ebp-824h] BYREF
  uint8_t v573; // [esp+133h] [ebp-81Dh] BYREF
  int v574; // [esp+134h] [ebp-81Ch] BYREF
  int v575; // [esp+138h] [ebp-818h] BYREF
  int v576; // [esp+13Ch] [ebp-814h] BYREF
  void *i5; // [esp+140h] [ebp-810h] BYREF
  u_short netshort[2]; // [esp+144h] [ebp-80Ch] BYREF
  int v579; // [esp+148h] [ebp-808h] BYREF
  int v580; // [esp+14Ch] [ebp-804h] BYREF
  uint8_t v581; // [esp+153h] [ebp-7FDh] BYREF
  char v582[1028]; // [esp+154h] [ebp-7FCh] BYREF
  char Format[256]; // [esp+558h] [ebp-3F8h] BYREF
  CHAR OutputString[255]; // [esp+658h] [ebp-2F8h] BYREF
  char v585; // [esp+757h] [ebp-1F9h] BYREF
  char Str[112]; // [esp+758h] [ebp-1F8h] BYREF
  char v587[4]; // [esp+7C8h] [ebp-188h] BYREF
  uint32_t v588[6]; // [esp+7CCh] [ebp-184h] BYREF
  int v589; // [esp+7E4h] [ebp-16Ch]
  int v590; // [esp+7E8h] [ebp-168h]
  uint8_t v591[15]; // [esp+7EDh] [ebp-163h] BYREF
  int v592; // [esp+7FCh] [ebp-154h]
  uint32_t v593[11]; // [esp+800h] [ebp-150h]
  int v594; // [esp+82Ch] [ebp-124h]
  void *v595; // [esp+830h] [ebp-120h]
  bool v596; // [esp+834h] [ebp-11Ch]
  uint32_t v597[6]; // [esp+840h] [ebp-110h] BYREF
  char Buffer[128]; // [esp+858h] [ebp-F8h] BYREF
  char Destination; // [esp+8D8h] [ebp-78h] BYREF
  char v600[63]; // [esp+8D9h] [ebp-77h] BYREF
  char v601; // [esp+918h] [ebp-38h] BYREF
  char v602[4]; // [esp+919h] [ebp-37h] BYREF
  char v603[20]; // [esp+920h] [ebp-30h] BYREF
  int16_t v604; // [esp+934h] [ebp-1Ch]
  int *v605; // [esp+938h] [ebp-18h] BYREF
  void *Block[2]; // [esp+93Ch] [ebp-14h] BYREF
  int v607; // [esp+94Ch] [ebp-4h]

  Block[1] = (void *)dword_796E50;
  v3 = *(uint8_t *)(ArgList + 1);
  v4 = a1;
  *(uint32_t *)netshort = a1;
  switch ( v3 )
  {
    case 0:
      sub_404AF0(&v603[4], 16);
      return 1;
    case 1:
      LOBYTE(v579) = 0;
      HIBYTE(ArgList) = 0;
      v576 = 0;
      *(uint32_t *)netshort = 0;
      v5 = (char *)sub_422E70(620);
      sub_48BCC0(&Destination, 64, v5);
      sub_404AD0(&v576);
      sub_404AD0(netshort);
      sub_404A90(&v579);
      sub_404A90((char *)&ArgList + 3);
      byte_99FCD0 = 99;
      off_77F3FC(
        "ChannelName [%s], TodaySeed %u %u, ServerIndex %d channelIndex %d",
        &Destination,
        v576,
        *(uint32_t *)netshort,
        (uint8_t)v579,
        HIBYTE(ArgList));
      if ( (uint8_t)v579 > 4u )
      {
        v6 = (const char *)sub_422E70(621);
        sprintf(dword_99FCD8, v6, &Destination);
      }
      else
      {
        sprintf(dword_99FCD8, "%s %s", (const char *)*(&off_7953CC + (uint8_t)v579), &Destination);
      }
      dword_8F84B0 = v576;
      *(uint32_t *)(dword_8F7B08 + 460) = *(uint32_t *)netshort;
      sub_4BE6B0(v579);
      *(uint32_t *)((char *)v4 + 262) = 0;
      sub_648D80(&Buffer[52]);
      v607 = 0;
      sub_648F10(nullptr);
      v7 = Buffer[66];
      *((uint8_t *)v4 + 263) = Buffer[64];
      v8 = Buffer[68];
      v9 = Buffer[70];
      *((uint8_t *)v4 + 262) = v7;
      *((uint8_t *)v4 + 264) = v9;
      *((uint8_t *)v4 + 265) = v8;
      sub_648D40(&Buffer[52]);
      off_77F3FC(
        "Client Version %d %d %d %d",
        *((uint8_t *)v4 + 262),
        *((uint8_t *)v4 + 263),
        *((uint8_t *)v4 + 264),
        *((uint8_t *)v4 + 265));
      off_77F3FC(
        "Server Version %d %d %d %d",
        (uint8_t)byte_8F85E0[0],
        (uint8_t)byte_8F85E1,
        (uint8_t)byte_8F85E2,
        (uint8_t)byte_8F85E3);
      v10 = 0;
      while ( *((uint8_t *)v4 + v10 + 262) == byte_8F85E0[v10] )
      {
        if ( ++v10 >= 4 )
        {
          sub_404AF0(&v603[4], 16);
          sub_41C2B0(&v603[4]);
          v607 = -1;
          sub_648DD0(&Buffer[52]);
          return 1;
        }
      }
      ShowCursor(true);
      v11 = *(HWND *)(dword_79C0A0 + 16);
      v12 = (const CHAR *)sub_422E70(622);
      MessageBoxA(v11, v12, "Run Error", 0);
      PostQuitMessage(0);
      v607 = -1;
      sub_648DD0(&Buffer[52]);
      return 0x80000000;
    case 2:
      v573 = 0;
      v575 = 0;
      sub_404A90(&v573);
      sub_404AB0(&v575);
      if ( v573 == 2 )
      {
        sub_46D1A0(v4[4]);
        dword_978998 = 0;
      }
      v571 = 0;
      if ( (uint16_t)v575 == 0 )
        goto LABEL_77;
      while ( 1 )
      {
        v572 = 0;
        sub_404AB0(&v572);
        v14 = 0;
        if ( v573 != 2 )
        {
          v14 = sub_429830(v572);
          if ( v14 == 0 )
          {
            v14 = sub_42A100(v572);
            if ( (uint16_t)v572 == (uint16_t)word_77F804 )
            {
              sub_456850(dword_8F850C);
              if ( *((uint32_t *)dword_8F8524 + 17) == 4 )
              {
                *(uint32_t *)(v14 + 160) = *((uint32_t *)dword_8F8524 + 3);
                *(uint32_t *)(v14 + 164) = *((uint32_t *)dword_8F8524 + 89);
                *(uint16_t *)(v14 + 168) = ntohs(*((uint16_t *)dword_8F8524 + 176));
              }
            }
          }
        }
        if ( v573 != 0 && v573 != 2 )
        {
          if ( v573 == 1 )
          {
            v15 = *(uint32_t *)(v14 + 196);
            if ( v15 == 0 )
            {
              v15 = sub_579F90(*(void **)(v14 + 44));
              sub_42A3D0(v15);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 1044))(v15, v14 + 16);
            }
            v576 = 0;
            sub_4CE550(&Buffer[48]);
            sub_404AD0(&v576);
            v16 = sub_48BC90(&Buffer[48]);
            off_77F3FC("[%5d] Exp %d, DataSize %d", (uint16_t)v572, v576, v16);
            v17 = sub_41A5E0(v14 + 53);
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v15 + 1036))(v15, v576, v17);
            (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v15 + 1048))(v15, &Buffer[48]);
            v18 = *(uint32_t *)v15;
            v19 = sub_41C210(*(uint32_t *)netshort);
            LOBYTE(v19) = (uint8_t)v19 == 0;
            (*(void (/*thiscall*/ **)(int, int))(v18 + 1056))(v15, v19);
            if ( *(uint8_t *)(dword_8F8500 + 16) != 0 )
            {
              if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )
              {
                v20 = *(uint32_t *)v15;
                v21 = (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)v15 + 740))(v15, 1, 0);
                (*(void (/*thiscall*/ **)(int, int))(v20 + 728))(v15, v21);
                v22 = *(uint32_t *)v15;
                v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 756))(v15, 1);
                (*(void (/*thiscall*/ **)(int, int))(v22 + 744))(v15, v23);
              }
              *(uint8_t *)(dword_8F8500 + 16) = 0;
            }
            memset(&v603[4], 0, 16);
            v604 = 0;
            v569 = 0;
            sub_404A90(&v569);
            off_77F3FC("EquipmentNumber %d", v569);
            v24 = 0;
            if ( v569 != 0 )
            {
              do
              {
                HIBYTE(ArgList) = 0;
                LOBYTE(v565) = 0;
                v574 = 0;
                v579 = 0;
                v580 = 0;
                sub_404A90((char *)&ArgList + 3);
                sub_404AB0(&v574);
                sub_404AD0(&v580);
                sub_404A90(&v565);
                sub_404AB0(&v579);
                off_77F3FC(
                  "EquipmentType %d, index %d, seed %d, ext_data1 %d, durability %d",
                  HIBYTE(ArgList),
                  (uint16_t)v574,
                  v580,
                  (uint8_t)v565,
                  (uint16_t)v579);
                v25 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v15 + 792))(v15, HIBYTE(ArgList));
                v26 = v25;
                if ( v25 != 0
                  && *(uint32_t *)((v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 16))(v25)) + 4) == (uint16_t)v574 )
                {
                  v28 = sub_4E9B10(v580, v565, 0, (uint16_t)v579);
                  v29 = *(uint32_t *)v26;
                  v607 = 3;
                  (*(void (/*thiscall*/ **)(int, int))(v29 + 184))(v26, v28);
                  v607 = -1;
                  sub_445150(v562);
                  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v26 + 16))(v26) + 32) = 0;
                }
                else
                {
                  v30 = sub_522300((void *)(uint16_t)v574, v580, v565, 0, (uint16_t)v579, 0);
                  v31 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 784))(v15, v30);
                  if ( v31 != 0 )
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v31 + 4))(v31, 1);
                }
                v32 = ++v24 < v569;
                v603[HIBYTE(ArgList) + 4] = 1;
              }
              while ( v32 );
            }
            for ( i = 0; i < 18; ++i )
            {
              if ( v603[i + 4] == 0 )
              {
                if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 792))(v15, i) != 0 )
                {
                  v34 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 788))(v15, i);
                  if ( v34 != 0 )
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v34 + 4))(v34, 1);
                }
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 1080))(v15, i);
              }
            }
            if ( (uint16_t)v572 == (uint16_t)word_77F804 )
              sub_47CD00(dword_8F8540);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 1148))(v15);
            v581 = 0;
            sub_404A90(&v581);
            off_77F3FC("SkillNumber %d", v581);
            v35 = 0;
            if ( v581 != 0 )
            {
              do
              {
                v570 = 0;
                HIBYTE(ArgList) = 0;
                sub_404A90(&v570);
                sub_404A90((char *)&ArgList + 3);
                off_77F3FC("SkillIndex %d, SkillLevel %d", v570, HIBYTE(ArgList));
                (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v15 + 1136))(v15, v570, HIBYTE(ArgList));
                ++v35;
              }
              while ( v35 < v581 );
            }
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 1152))(v15);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 1156))(v15);
          }
          goto LABEL_75;
        }
        HIBYTE(ArgList) = 0;
        v570 = 0;
        HIBYTE(v574) = 0;
        HIBYTE(v567) = 0;
        i5 = nullptr;
        sub_429E30(v587);
        v607 = 1;
        v36 = (char *)sub_422E70(623);
        sub_48BCC0(&v600[31], 31, v36);
        sub_406D60(&v600[31]);
        sub_404A90((char *)&ArgList + 3);
        v589 = HIBYTE(ArgList);
        sub_404A90((char *)&ArgList + 3);
        v590 = HIBYTE(ArgList);
        sub_404A90((char *)&ArgList + 3);
        sub_41C150(HIBYTE(ArgList));
        sub_404A90((char *)&ArgList + 3);
        v594 = HIBYTE(ArgList);
        sub_404A90((char *)&ArgList + 3);
        v592 = HIBYTE(ArgList);
        sub_404A90(&v570);
        v37 = 0;
        if ( v570 != 0 )
        {
          do
          {
            HIBYTE(v580) = 0;
            v566 = nullptr;
            sub_404A90((char *)&v580 + 3);
            sub_404AB0(&v566);
            v32 = ++v37 < v570;
            v593[HIBYTE(v580)] = (uint16_t)v566;
          }
          while ( v32 );
        }
        sub_404A90((char *)&v574 + 3);
        v593[10] = HIBYTE(v574);
        sub_404AD0(&i5);
        v595 = i5;
        sub_404A90((char *)&v567 + 3);
        v38 = (const char *)v597[0];
        v596 = HIBYTE(v567) == 1;
        if ( v597[5] < 0x10u )
          v38 = (const char *)v597;
        v39 = sub_41A5E0(v591);
        v40 = (const char *)v588[0];
        if ( v588[5] < 0x10u )
          v40 = (const char *)v588;
        off_77F3FC(
          "[%5d] Name[%s], Job %d, GrowType %d, Level %d, UserState %d, PvpRank %d, Guild %d, Donkey %d, Creature %d, Creature Name [%s]",
          (uint16_t)v572,
          v40,
          v589,
          v590,
          v39,
          v592,
          v594,
          v595,
          HIBYTE(v567),
          0,
          v38);
        if ( v14 != 0 )
        {
          sub_46C250(v587);
          v41 = *(int **)(v14 + 196);
          if ( v41 != nullptr )
          {
            (*(void (/*thiscall*/ **)(int *, char *))(*v41 + 1044))(v41, v587);
            v42 = sub_41A5E0(v591);
            v43 = *v41;
            v44 = (*(int (/*thiscall*/ **)(int *, int))(*v41 + 1032))(v41, v42);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(v43 + 1036))(v41, *(uint32_t *)(v44 + 48));
          }
        }
        if ( v573 != 0 )
        {
          if ( v573 == 2 )
          {
            v53 = operator new(0x294u);
            Block[0] = v53;
            LOBYTE(v607) = 2;
            if ( v53 != nullptr )
              v54 = (int *)sub_42B0F0(v53);
            else
              v54 = nullptr;
            v55 = *v54;
            LOBYTE(v607) = 1;
            (*(void (/*thiscall*/ **)(int *, char *))(v55 + 348))(v54, v587);
            sub_46D280(v54, v587);
          }
          goto LABEL_74;
        }
        v45 = *(uint32_t *)(v14 + 192);
        if ( v45 != 0 )
          break;
        if ( (uint16_t)v572 == (uint16_t)word_77F804 )
        {
          v46 = sub_42B340(v14);
          v47 = *(uint32_t *)netshort;
          v48 = v46;
          sub_45FE80(18, (uint16_t)v572, v46, 0, 0);
          v49 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(v47 + 20) + 104) + 40);
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v48 + 112))(v48, *v49, v49[1], 0);
          sub_45B140(*(uint32_t *)(v47 + 20));
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v48 + 376))(v48);
          sub_424A40(dword_8F7C08);
          v50 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);
          v51 = v50;
          if ( v50 != 0 && (uint8_t)sub_423340(v50 + 32, "[none]") != 0 )
          {
            v527 = unknown_libname_2(v51 + 60);
            v52 = (const char *)sub_422E70(1244);
            sprintf(OutputString, v52, v527);
            sub_43BEE0(OutputString, -6567706, 0, -1);
          }
LABEL_66:
          sub_5603E0(v587);
LABEL_67:
          if ( (uint16_t)v572 == (uint16_t)word_77F804 )
            sub_47BAA0(dword_8F8540);
        }
LABEL_74:
        v607 = -1;
        sub_41CBF0(v587);
LABEL_75:
        if ( ++v571 >= (uint16_t)v575 )
        {
          v4 = *(uint32_t **)netshort;
LABEL_77:
          if ( v573 == 2 )
          {
            sub_46B150(v4[4]);
          }
          else if ( v573 == 0 )
          {
            if ( dword_9B9460 != 0 )
              sub_632D40();
            sub_52C590(*((uint32_t *)dword_8F8528 + 8));
            v56 = *((uint32_t *)dword_8F8528 + 9);
LABEL_105:
            sub_49D920(v56);
            sub_479850(dword_8F8510);
            sub_479850(dword_8F8514);
            sub_479850(dword_8F8518);
          }
          return 1;
        }
      }
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v45 + 348))(v45, v587);
      if ( dword_8F7C08 == v45
        && v14 == sub_41C1B0(dword_8F8500)
        && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 611) + 12) == 1 )
      {
        goto LABEL_66;
      }
      goto LABEL_67;
    case 3:
      HIBYTE(ArgList) = 0;
      v575 = 0;
      sub_404AB0(&v575);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("ServerId %d, UserState %d", (uint16_t)v575, HIBYTE(ArgList));
      v57 = sub_429830(v575);
      if ( v57 != 0 )
      {
        *(uint32_t *)(v57 + 68) = HIBYTE(ArgList);
        sub_52C590(*((uint32_t *)dword_8F8528 + 8));
        sub_49D920(*((uint32_t *)dword_8F8528 + 9));
        if ( HIBYTE(ArgList) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 )
        {
          v58 = *(uint32_t *)(v57 + 192);
          if ( v58 != 0 )
            sub_45F1E0(v58);
        }
      }
      return 1;
    case 4:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("Stamina %d", HIBYTE(ArgList));
      if ( dword_8F7C04 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, HIBYTE(ArgList));
        if ( v4[3] == 1 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
        if ( HIBYTE(ArgList) == 100 )
          sub_432EA0("STAMINA_RECOVER", -1, 0, 0);
      }
      return 1;
    case 5:
      v579 = 0;
      sub_404AB0(&v579);
      off_77F3FC("Number %d", (uint16_t)v579);
      HIBYTE(ArgList) = 0;
      *(uint32_t *)netshort = 0;
      v566 = nullptr;
      if ( (uint16_t)v579 != 0 )
      {
        do
        {
          sub_404AB0(netshort);
          sub_404A90((char *)&ArgList + 3);
          off_77F3FC("DungeonIndex %d, DungeonDifficulty %d", netshort[0], HIBYTE(ArgList));
          if ( v4[3] == 3 )
          {
            v59 = HIBYTE(ArgList);
            if ( v59 > sub_472F90(netshort[0]) )
            {
              v60 = sub_476B60(netshort[0]);
              sub_57A2D0(v60, v59);
            }
          }
          sub_4896B0(netshort[0], HIBYTE(ArgList));
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < (uint16_t)v579 );
      }
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 11) + 16) == 1 )
      {
        sub_41C1B0(dword_8F8500);
        v61 = sub_41C1B0(dword_8F8500);
        sub_41A5E0(v61 + 53);
        sub_546E10(*((uint32_t *)dword_8F8528 + 11));
        v62 = sub_41C1B0(dword_8F8500);
        v528 = *(uint32_t *)(v62 + 44);
        v63 = unknown_libname_2(v62 + 16);
        sub_48BA80(v63, v528);
        sub_48B970(dword_8F8544);
      }
      return 1;
    case 6:
      *(float *)&ArgList = 0.0;
      sub_404AB0(&ArgList);
      off_77F3FC("ServerId %d", (uint16_t)ArgList);
      v64 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 12) + 8);
      if ( v64 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v64 + 40))(v64, 18) != 0 )
      {
        v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v64 + 52))(v64);
        if ( v65 == (uint16_t)ArgList )
          sub_525740(*((uint32_t *)dword_8F8528 + 12));
      }
      sub_429FC0(ArgList);
      sub_52C590(*((uint32_t *)dword_8F8528 + 8));
      v56 = *((uint32_t *)dword_8F8528 + 9);
      goto LABEL_105;
    case 7:
      HIBYTE(ArgList) = 0;
      v575 = 0;
      v579 = 0;
      sub_404AB0(&v575);
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&v579);
      off_77F3FC("PeerRequestType %d, ServerId %d, data %d", HIBYTE(ArgList), (uint16_t)v575, v579);
      v66 = sub_429830(v575);
      if ( v66 != 0 )
      {
        if ( HIBYTE(ArgList) == 0 )
        {
          v67 = sub_41C1B0(dword_8F8500);
          sub_45DB20(dword_8F8524, v67);
          *(uint32_t *)(v66 + 180) = v579;
        }
        sub_44E8D0(dword_8F8528, (void *)0x1D, v66, HIBYTE(ArgList));
        if ( HIBYTE(ArgList) == 1 )
          *(uint32_t *)(v66 + 176) = v579;
      }
      return 1;
    case 8:
      HIBYTE(ArgList) = 0;
      *(uint32_t *)netshort = 0;
      v575 = 0;
      sub_404AB0(netshort);
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&v575);
      off_77F3FC("ServerId %d, PeerRequestType %d, Data %d", netshort[0], HIBYTE(ArgList), v575);
      v68 = sub_429830(*(uint32_t *)netshort);
      memset(Buffer, 0, sizeof(Buffer));
      if ( HIBYTE(ArgList) != 0 )
      {
        if ( HIBYTE(ArgList) == 1 )
        {
          v70 = sub_429830(*(uint32_t *)netshort);
          v530 = unknown_libname_2(v70 + 16);
          v71 = (const char *)sub_422E70(625);
          sprintf(Buffer, v71, v530);
          *(uint32_t *)(v68 + 176) = v575;
          sub_4844B0(dword_8F8538);
          sub_57A380(netshort[0]);
          sub_44BBA0(2, 0);
        }
      }
      else
      {
        v529 = unknown_libname_2(v68 + 16);
        v69 = (const char *)sub_422E70(624);
        sprintf(Buffer, v69, v529);
      }
      sub_43BEE0(Buffer, -6567706, 0, -1);
      return 1;
    case 9:
      v579 = 0;
      sub_404AB0(&v579);
      off_77F3FC("PartyInfoNumber %d", (uint16_t)v579);
      v572 = 0;
      if ( (uint16_t)v579 == 0 )
        goto LABEL_365;
      while ( 2 )
      {
        HIBYTE(ArgList) = 0;
        v574 = 0;
        sub_404AB0(&v574);
        sub_404A90((char *)&ArgList + 3);
        off_77F3FC("PartyIndex %d, InfoType %d", (uint16_t)v574, HIBYTE(ArgList));
        if ( HIBYTE(ArgList) != 0 )
          v72 = sub_4569F0(v574);
        else
          v72 = sub_456EB0((void *)(uint16_t)v574);
        v73 = (uint32_t *)v72;
        if ( v72 == 0 )
        {
LABEL_365:
          if ( dword_9B9460 != 0 )
            sub_632D40();
          if ( dword_9B9458 != 0 )
            sub_6312F0();
          return 1;
        }
        v74 = *(uint32_t **)(sub_41C1B0(dword_8F8500) + 184);
        v75 = HIBYTE(ArgList);
        HIBYTE(v580) = v74 == v73;
        if ( HIBYTE(ArgList) <= 1u )
        {
          Destination = 0;
          memset(v600, 0, sizeof(v600));
          v581 = 0;
          HIBYTE(v567) = 0;
          sub_404A90(&v581);
          if ( v581 == 0 )
          {
            v76 = (char *)sub_422E70(626);
            sub_48BCC0(&Destination, 64, v76);
          }
          sub_404A90((char *)&v567 + 3);
          off_77F3FC("TitleIndex %d, Title[%s], MemberMax %d", v581, &Destination, HIBYTE(v567));
          v73[2] = v581;
          sub_406D60(&Destination);
          v73[15] = HIBYTE(v567);
          v75 = HIBYTE(ArgList);
        }
        if ( v75 == 0 || v75 == 2 )
        {
          HIBYTE(v567) = 0;
          v77 = &v605;
          for ( j = 4; j != 0; --j )
          {
            sub_404AB0(v77);
            v77 = (int **)((char *)v77 + 2);
          }
          sub_404A90((char *)&v567 + 3);
          off_77F3FC(
            "ServerId %d %d %d %d MasterSeatIndex %d",
            (uint16_t)v605,
            HIWORD(v605),
            LOWORD(Block[0]),
            HIWORD(Block[0]),
            HIBYTE(v567));
          for ( k = 0; k < 4; ++k )
            sub_56A6B0(k, *((uint16_t *)&Block[-1] + k));
          v73[14] = HIBYTE(v567);
          v75 = HIBYTE(ArgList);
        }
        if ( v75 == 3 )
        {
          for ( m = 0; m < 4; ++m )
            sub_56A6B0(m, 0xFFFF);
        }
        v81 = *(uint32_t **)(sub_429830((uint16_t)word_77F804) + 184);
        if ( HIBYTE(v580) != 0 )
        {
          if ( v81 != v73 )
          {
            if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
            {
              sub_43BB10(0, 1);
              sub_43BB10(1, 0);
              sub_43BA20(0);
              sub_43B880(0);
            }
            if ( dword_9B9458 != 0 )
              sub_631630(0);
            v82 = *(uint32_t *)(*(uint32_t *)netshort + 12);
            if ( (v82 == 3 || v82 == 2)
              && *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16) + 104) != 0 )
            {
              for ( n = 16; n < 32; n += 4 )
              {
                v84 = *(uint32_t *)(n + dword_8F850C);
                if ( v84 != 0 && v84 != sub_429830((uint16_t)word_77F804) )
                  sub_45F1E0(*(uint32_t *)(v84 + 196));
              }
            }
            off_77F3FC("@@UDP STOP - ENUM_NOTIPACKET_PARTY_INFO 1");
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
            sub_456850(dword_8F850C);
            if ( HIBYTE(ArgList) == 3 )
              v85 = sub_422E70(627);
            else
              v85 = sub_422E70(628);
            sub_43BEE0(v85, -6567706, 0, -1);
            sub_432EA0("PARTY_LEAVE", -1, 0, 0);
            goto LABEL_202;
          }
        }
        else
        {
          if ( v81 != v73 )
            goto LABEL_202;
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
          {
            sub_43BB10(0, 1);
            sub_43BB10(1, 1);
          }
          if ( dword_9B9458 != 0 )
            sub_631630(1);
        }
        v575 = sub_456390(0);
        v571 = sub_429830((uint16_t)word_77F804);
        v86 = 0;
        v568[0] = 0;
        v87 = (uint16_t *)(v73 + 10);
        i5 = (void *)(16 - (uint32_t)&v603[4]);
        do
        {
          v88 = *v87;
          *(uint32_t *)&v603[4 * v86 + 4] = *(uint32_t *)&v603[(uint32_t)i5 + 4 * v86 + dword_8F850C + 4];
          sub_456340(v86++, v88);
          v87 += 2;
        }
        while ( v86 < 4 );
        v89 = sub_456390(0);
        v531 = v73[14];
        v576 = v89;
        sub_456460(v531);
        if ( v89 >= 2 )
        {
          v90 = sub_456420(dword_8F850C);
          off_77F3FC("@@UDP START - ENUM_NOTIPACKET_PARTY_INFO seatIndex %d /// 1", v90);
          v91 = *(uint32_t *)dword_8F8520;
          v92 = sub_456420(dword_8F850C);
          (*(void (/*thiscall*/ **)(int, int))(v91 + 148))(dword_8F8520, v92);
        }
        v566 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16) + 104);
        v93 = 0;
        v94 = 564 - (uint32_t)&v603[4];
        HIBYTE(v580) = 0;
        LODWORD(v564) = 564 - (uint32_t)&v603[4];
        do
        {
          v95 = *(uint32_t **)&v603[4 * v93 + 4];
          if ( v95 != nullptr )
          {
            v96 = &v603[4 * v93 + 4 + v94];
            if ( v95 != *(uint32_t **)&v96[dword_8F850C - 548] )
            {
              if ( v95[10] < 0x10u )
                v97 = v95 + 5;
              else
                v97 = (uint32_t *)v95[5];
              v532 = v97;
              v98 = (const char *)sub_422E70(629);
              sprintf(Buffer, v98, v532);
              sub_43BEE0(Buffer, -6567706, 0, -1);
              if ( HIBYTE(v580) == 0 )
              {
                sub_432EA0("PARTY_LEAVE", -1, 0, 0);
                HIBYTE(v580) = 1;
              }
              if ( v566 != nullptr )
              {
                v99 = *(uint32_t *)(*(uint32_t *)netshort + 12);
                if ( v99 == 3 || v99 == 2 )
                {
                  v100 = *((uint32_t *)dword_8F8528 + 609);
                  if ( *(uint32_t *)(v100 + 4) != 0 )
                    *(uint32_t *)&v96[v100] = -1;
                  sub_45F1E0(v95[49]);
                }
              }
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, v93);
              off_77F3FC("@@REMOVE PEER");
              v94 = v564;
            }
          }
          ++v93;
        }
        while ( v93 < 4 );
        if ( v575 == 1 && v576 >= 2 )
        {
          v101 = dword_8F850C;
          v102 = sub_456480(dword_8F850C) == -1 ? 0 : *(uint32_t *)(v101 + 4 * sub_456480(v101) + 16);
          if ( v102 != v571 )
            v568[0] = 1;
        }
        v103 = 0;
        for ( ii = 0; ii < 4; ++ii )
        {
          v105 = *(uint32_t *)&v603[(uint32_t)i5 + 4 * ii + dword_8F850C + 4];
          if ( v105 != 0 && v105 != v571 && v105 != *(uint32_t *)&v603[4 * ii + 4] )
          {
            if ( *(uint32_t *)(v105 + 40) < 0x10u )
              v106 = v105 + 20;
            else
              v106 = *(uint32_t *)(v105 + 20);
            v533 = v106;
            v107 = (const char *)sub_422E70(630);
            sprintf(Buffer, v107, v533);
            sub_43BEE0(Buffer, -6567706, 0, -1);
            if ( v103 == 0 )
            {
              sub_432EA0("PARTY_JOIN", -1, 0, 0);
              v103 = 1;
            }
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 100))(
              dword_8F8520,
              ii,
              v105,
              *(uint32_t *)v568,
              1);
          }
        }
        if ( dword_9B9458 != 0 )
          sub_630750();
        if ( v575 > 1 && v576 == 1 && *(uint32_t *)(*(uint32_t *)netshort + 12) == 1 )
          sub_44E8D0(dword_8F8528, (void *)0x2C, 0, 0);
LABEL_202:
        if ( HIBYTE(ArgList) == 3 )
          sub_456D70(v574);
        if ( ++v572 >= (uint16_t)v579 )
          goto LABEL_365;
        continue;
      }
    case 10:
      v581 = 0;
      HIBYTE(ArgList) = 0;
      sub_404A90(&v581);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("SeatIndex %d, WalkoutType %d", v581, HIBYTE(ArgList));
      switch ( HIBYTE(ArgList) )
      {
        case 0:
        case 1:
          v108 = *(uint32_t *)(dword_8F850C + 4 * v581 + 16);
          if ( v108 == 0 )
            goto LABEL_219;
          if ( v108 == sub_41C1B0(dword_8F8500) )
          {
            if ( HIBYTE(ArgList) != 0 )
              v109 = sub_422E70(632);
            else
              v109 = sub_422E70(631);
            goto LABEL_211;
          }
          v110 = v108 + 16;
          if ( HIBYTE(ArgList) != 0 )
          {
            v535 = unknown_libname_2(v110);
            v112 = (const char *)sub_422E70(634);
            goto LABEL_217;
          }
          v534 = unknown_libname_2(v110);
          v111 = (const char *)sub_422E70(633);
          sprintf(Buffer, v111, v534);
          if ( (int)sub_456390(0) > 2 )
            goto LABEL_218;
          sub_43BD50(0, Buffer, -6567706, 0, -1);
          break;
        case 2:
        case 3:
          if ( dword_99FEC0 != 0 && (v113 = sub_48F690(v581)) != 0 )
          {
            if ( v113 == sub_41C1B0(dword_8F8500) )
            {
              if ( HIBYTE(ArgList) == 2 )
                v109 = sub_422E70(635);
              else
                v109 = sub_422E70(636);
LABEL_211:
              sub_44E8D0(dword_8F8528, (void *)0x1B, v109, 0);
            }
            else
            {
              v114 = v113 + 16;
              if ( HIBYTE(ArgList) == 2 )
              {
                v536 = unknown_libname_2(v114);
                v514 = (const char *)sub_422E70(637);
                sprintf(Buffer, v514, v536);
              }
              else
              {
                v535 = unknown_libname_2(v114);
                v112 = (const char *)sub_422E70(638);
LABEL_217:
                sprintf(Buffer, v112, v535);
              }
LABEL_218:
              sub_43BEE0(Buffer, -6567706, 0, -1);
            }
          }
          else
          {
LABEL_219:
            off_77F3FC(aCriticalError_16);
          }
          break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
          v115 = nullptr;
          switch ( HIBYTE(ArgList) )
          {
            case 4:
              v116 = sub_422E70(1935);
              sub_44E8D0(dword_8F8528, (void *)0x1B, v116, 0);
              break;
            case 5:
              v117 = sub_422E70(1936);
              sub_44E8D0(dword_8F8528, (void *)0x1B, v117, 0);
              break;
            case 6:
              v118 = sub_422E70(1937);
              sub_44E8D0(dword_8F8528, (void *)0x1B, v118, 0);
              break;
            case 7:
              v119 = sub_422E70(1938);
              sub_44E8D0(dword_8F8528, (void *)0x1B, v119, 0);
              break;
            case 8:
              v120 = sub_422E70(1939);
              sub_44E8D0(dword_8F8528, (void *)0x1B, v120, 0);
              break;
            default:
              goto LABEL_782;
          }
          break;
        default:
          return 1;
      }
      return 1;
    case 11:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("UserNumber %d", HIBYTE(ArgList));
      v566 = nullptr;
      if ( HIBYTE(ArgList) != 0 )
      {
        do
        {
          v575 = 0;
          *(uint32_t *)netshort = 0;
          v576 = 0;
          v579 = 0;
          i5 = nullptr;
          sub_404AB0(&v575);
          sub_404AD0(&v576);
          sub_404AD0(&v579);
          sub_404AB0(netshort);
          sub_404AD0(&v564);
          sub_404A90(&i5);
          sub_404AD0((char *)&v564 + 4);
          off_77F3FC("ServerId %d, LocalIp %d, PublicIp %d, Port %d", (uint16_t)v575, v576, v579, netshort[0]);
          v121 = sub_429830(v575);
          if ( v121 != 0 )
          {
            *(uint32_t *)(v121 + 160) = v576;
            *(uint32_t *)(v121 + 164) = v579;
            *(uint16_t *)(v121 + 168) = ntohs(netshort[0]);
            *(uint32_t *)(v121 + 8) = v564;
            *(uint32_t *)(v121 + 172) = i5;
            *(uint32_t *)(v121 + 12) = HIDWORD(v564);
            v122 = (const char *)sub_42A380(0);
            off_77F3FC("Local Ip [%s]", v122);
            v123 = (const char *)sub_42A380(1);
            off_77F3FC("Public Ip [%s]", v123);
          }
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < HIBYTE(ArgList) );
      }
      return 1;
    case 12:
      HIBYTE(ArgList) = 0;
      v575 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0(&v575);
      v124 = (char *)sub_422E70(639);
      sub_48BCC0(Str, 256, v124);
      off_77F3FC("MessageType %d, ServerId %d, MessageLength %d", HIBYTE(ArgList), (uint16_t)v575, strlen(Str));
      if ( HIBYTE(ArgList) == 0 )
      {
        v125 = (const char *)sub_422E70(640);
        sprintf(v582, v125, Str);
        sub_44E8D0(dword_8F8528, (void *)0x24, v582, 0);
      }
      sub_43D900(Str, HIBYTE(ArgList), v575, nullptr);
      return 1;
    case 13:
      HIBYTE(ArgList) = 0;
      v574 = 0;
      v575 = 0;
      sub_404A90((char *)&ArgList + 3);
      if ( HIBYTE(ArgList) == 2 )
      {
        sub_404AB0(&v575);
        sub_50D920((uint16_t)v575);
        off_77F3FC(
          "CNGameCore::NetworkProc - ENUM_NOTIPACKET_ITEM_LIST - Storage capacity = %d",
          (uint16_t)v575);
      }
      sub_404AB0(&v574);
      off_77F3FC("ItemSpace %d, ItemNumber %d", HIBYTE(ArgList), (uint16_t)v574);
      v128 = sub_432F00(HIBYTE(ArgList));
      sub_485020(v128);
      v566 = nullptr;
      if ( (uint16_t)v574 != 0 )
      {
        do
        {
          LOBYTE(v572) = 0;
          HIBYTE(v567) = 0;
          v580 = 0;
          *(uint32_t *)netshort = 0;
          v576 = 0;
          v579 = 0;
          sub_404AB0(&v580);
          sub_404AB0(netshort);
          sub_404AD0(&v579);
          sub_404A90(&v572);
          sub_404AB0(&v576);
          sub_404A90((char *)&v567 + 3);
          off_77F3FC(
            "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d",
            (uint16_t)v580,
            netshort[0],
            v579,
            (uint8_t)v572,
            (uint16_t)v576,
            HIBYTE(v567));
          v130 = sub_44A980((uint16_t)v580);
          if ( v130 != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v130 + 60))(v130, netshort[0]) != 0 )
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v130 + 40))(v130, v579);
            else
              off_77F3FC(aCriticalError_17);
          }
          else
          {
            LOBYTE(v129) = HIBYTE(v567) != 0;
            v131 = sub_522300((void *)netshort[0], v579, v572, 0, (uint16_t)v576, v129);
            sub_484F40((uint16_t)v580, v131, 1);
          }
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < (uint16_t)v574 );
      }
      if ( HIBYTE(ArgList) == 0 )
        sub_47CD00(dword_8F8540);
      return 1;
    case 14:
      v581 = 0;
      v565 = 0;
      sub_404A90(&v581);
      sub_404AB0(&v565);
      off_77F3FC("ItemSpace %d, ItemNumber %d", v581, (uint16_t)v565);
      sub_432F00(v581);
      memset(&v603[8], 0, 12);
      v607 = 4;
      v566 = nullptr;
      if ( (uint16_t)v565 != 0 )
      {
        do
        {
          LOBYTE(v574) = 0;
          HIBYTE(ArgList) = 0;
          v572 = 0;
          v579 = 0;
          v580 = 0;
          *(uint32_t *)netshort = 0;
          sub_404AB0(&v572);
          sub_404AB0(&v579);
          sub_404AD0(netshort);
          sub_404A90(&v574);
          sub_404AB0(&v580);
          sub_404A90((char *)&ArgList + 3);
          off_77F3FC(
            "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d",
            (uint16_t)v572,
            (uint16_t)v579,
            *(uint32_t *)netshort,
            (uint8_t)v574,
            (uint16_t)v580,
            HIBYTE(ArgList));
          v132 = (uint16_t)v572;
          v134 = (int *)sub_44A980((uint16_t)v572);
          if ( v134 != nullptr )
          {
            if ( (uint16_t)v579 == 0xFFFF )
            {
              sub_484D50(v132);
            }
            else
            {
              v135 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v134 + 60))(v134, (uint16_t)v579);
              v136 = (int (/*thiscall*/ **)(int *))*v134;
              if ( v135 != 0 )
              {
                v137 = v136[11](v134);
                if ( *(uint32_t *)netshort > v137 )
                {
                  v138 = (*(int (/*thiscall*/ **)(int *))(*v134 + 44))(v134);
                  Block[0] = (void *)(*(uint32_t *)netshort - v138);
                  v605 = v134;
                  sub_44E340(&v605);
                }
                (*(void (/*thiscall*/ **)(int *, uint32_t))(*v134 + 40))(v134, *(uint32_t *)netshort);
              }
              else if ( (*v136)(v134) == 2 )
              {
                v139 = HIBYTE(ArgList) == 1;
                *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v134 + 16))(v134) + 32) = v139;
                v140 = sub_4E9B10(*(uint32_t *)netshort, v574, 0, (uint16_t)v580);
                v141 = *v134;
                LOBYTE(v607) = 5;
                (*(void (/*thiscall*/ **)(int *, int))(v141 + 184))(v134, v140);
                LOBYTE(v607) = 4;
                sub_445150(v561);
              }
              else
              {
                off_77F3FC(aCriticalError_17);
              }
            }
          }
          else if ( (uint16_t)v579 != 0xFFFF )
          {
            LOBYTE(v133) = HIBYTE(ArgList) != 0;
            v142 = sub_522300((void *)(uint16_t)v579, *(int *)netshort, v574, 0, (uint16_t)v580, v133);
            LODWORD(v564) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v142 + 44))(v142);
            v563 = v142;
            sub_44E340(&v563);
            sub_484F40((uint16_t)v572, v142, 1);
          }
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < (uint16_t)v565 );
      }
      if ( v581 == 0 )
        sub_47CD00(dword_8F8540);
      v143 = *(uint32_t **)&v603[8];
      v144 = *(uint32_t **)&v603[12];
      for ( jj = *(uint32_t **)&v603[8]; jj != v144; jj += 2 )
      {
        v146 = sub_429830((uint16_t)word_77F804);
        sub_4337E0(*jj, jj[1], v146, (jj == v143) - 1);
      }
      v607 = -1;
      sub_5E5260(&v603[4]);
      v147 = *((uint32_t *)dword_8F8528 + 90);
      if ( v147 != 0
        && (*((uint32_t *)dword_8F8528 + 91) - v147) >> 2 != 0
        && (*(uint32_t *)sub_57A590(0) != 0 || MEMORY[0x34] == 1) )
      {
        sub_63B3C0();
      }
      return 1;
    case 15:
      LOBYTE(v572) = 0;
      *(uint32_t *)netshort = 0;
      v580 = 0;
      v574 = 0;
      *(float *)&ArgList = 0.0;
      sub_404AB0(netshort);
      sub_404AB0(&v580);
      sub_404AD0(&ArgList);
      sub_404A90(&v572);
      sub_404AB0(&v574);
      off_77F3FC(
        "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d",
        netshort[0],
        (uint16_t)v580,
        ArgList,
        (uint8_t)v572,
        (uint16_t)v574);
      sprintf(OutputString, "DATA %d", ArgList);
      OutputDebugStringA(OutputString);
      v148 = v580;
      if ( (uint16_t)v580 == 0xFFFF )
      {
        sub_484D50(netshort[0]);
      }
      else
      {
        v149 = netshort[0];
        if ( sub_44A980(netshort[0]) != 0 )
        {
          v150 = (int *)sub_44A980(v149);
          v151 = (*(int (/*thiscall*/ **)(int *))(*v150 + 16))(v150);
          if ( *(uint32_t *)(v151 + 4) == (uint16_t)v580 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v150 + 20))(v150, 1) != 0 )
            {
              (*(void (/*thiscall*/ **)(int *, int))(*v150 + 40))(v150, ArgList);
            }
            else if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v150 + 20))(v150, 2) != 0 )
            {
              v152 = sub_4E9B10(ArgList, v572, 0, (uint16_t)v574);
              v153 = *v150;
              v607 = 6;
              (*(void (/*thiscall*/ **)(int *, int))(v153 + 184))(v150, v152);
              v607 = -1;
              sub_445150(v560);
            }
          }
          else
          {
            sub_484D50(netshort[0]);
            v515 = sub_522300((void *)(uint16_t)v580, ArgList, v572, 0, (uint16_t)v574, 1);
            sub_484F40(netshort[0], v515, 1);
          }
        }
        else
        {
          v516 = sub_522300((void *)v148, ArgList, v572, 0, (uint16_t)v574, 1);
          sub_484F40(netshort[0], v516, 1);
        }
      }
      for ( kk = 0; kk < 2; ++kk )
        sub_484710(kk, 0);
      sub_57A3A0(dword_8F8538);
      sub_432EA0("CHANGE_ALERT", -1, 0, 0);
      return 1;
    case 16:
      v579 = 0;
      sub_404AB0(&v579);
      off_77F3FC("SlotNumber %d", (uint16_t)v579);
      v575 = *(uint32_t *)(dword_8F8538 + 16);
      LODWORD(v564) = dword_8F7C04;
      v566 = nullptr;
      if ( (uint16_t)v579 == 0 )
        goto LABEL_316;
      do
      {
        HIBYTE(ArgList) = 0;
        v580 = 0;
        *(uint32_t *)netshort = 0;
        sub_404AB0(&v580);
        sub_404A90((char *)&ArgList + 3);
        sub_404AB0(netshort);
        off_77F3FC("SlotIndex1 %d, ItemSpace %d, SlotIndex2 %d", (uint16_t)v580, HIBYTE(ArgList), netshort[0]);
        v155 = sub_44A980((uint16_t)v580);
        v156 = v155;
        if ( v155 != 0 )
        {
          v157 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v155 + 16))(v155);
          off_77F3FC("srcItem ItemInfo Address = 0x%x", v157);
        }
        else
        {
          off_77F3FC("srcItem is NULL");
        }
        if ( HIBYTE(ArgList) == 0 )
        {
          v158 = netshort[0];
          v159 = (uint32_t *)sub_44A980(netshort[0]);
          if ( v159 == nullptr )
            goto LABEL_314;
          v160 = *v159;
          v558 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v156 + 16))(v156, v558) + 4);
LABEL_312:
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v160 + 60))(v159) != 0 )
          {
            v169 = *v159;
            v170 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v156 + 44))(v156);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v169 + 48))(v159, v170);
          }
          else
          {
            v161 = (*(int (/*thiscall*/ **)(uint32_t *))(*v159 + 16))(v159);
            off_77F3FC(aCriticalError_18, *(uint32_t *)(v161 + 4));
          }
          goto LABEL_315;
        }
        if ( HIBYTE(ArgList) != 3 )
        {
          if ( HIBYTE(ArgList) != 1 )
            goto LABEL_315;
          v158 = netshort[0];
          v168 = (uint32_t *)sub_44A980(netshort[0]);
          v159 = v168;
          if ( v168 == nullptr )
          {
LABEL_314:
            sub_484F40(v158, v156, 1);
            sub_484F40((uint16_t)v580, 0, 1);
            goto LABEL_315;
          }
          v160 = *v168;
          v558 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v156 + 16))(v156, v558) + 4);
          goto LABEL_312;
        }
        v162 = __RTDynamicCast(v156, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
        if ( v162 != 0 )
        {
          if ( (uint32_t)v564 != 0 )
          {
            v164 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)v564 + 792))(v564, netshort[0]);
            v165 = *(uint32_t *)v564;
            if ( v164 != 0 )
            {
              v166 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(v165 + 792))(v564, netshort[0]);
              v167 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v166 + 16))(v166);
              off_77F3FC(aCriticalError_21, *(uint32_t *)(v167 + 4));
            }
            else
            {
              (*(void (/*thiscall*/ **)(uint32_t, int))(v165 + 784))(v564, v162);
            }
            sub_484F40((uint16_t)v580, 0, 1);
          }
          else
          {
            off_77F3FC(aCriticalError_20);
            sub_484F40((uint16_t)v580, 0, 1);
          }
        }
        else
        {
          v163 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v156 + 16))(v156);
          off_77F3FC(aCriticalError_19, *(uint32_t *)(v163 + 4));
          sub_484F40((uint16_t)v580, 0, 1);
        }
LABEL_315:
        v566 = (uint32_t *)((char *)v566 + 1);
      }
      while ( (int)v566 < (uint16_t)v579 );
LABEL_316:
      sub_4844B0(dword_8F8538);
      sub_44AB50(0, 12);
      sub_44AB50(1, 12);
      v171 = sub_422E70(643);
      sub_43BEE0(v171, -6567706, 0, -1);
      sub_47CD00(dword_8F8540);
      return 1;
    case 17:
      HIBYTE(ArgList) = 0;
      v575 = 0;
      sub_404AB0(&v575);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("ServerId %d, TradeState %d", (uint16_t)v575, HIBYTE(ArgList));
      sub_484710((uint16_t)v575 != (uint16_t)word_77F804, HIBYTE(ArgList));
      return 1;
    case 18:
      *(float *)&ArgList = 0.0;
      sub_404AB0(&ArgList);
      off_77F3FC("SlotNumber %d", (uint16_t)ArgList);
      v566 = *(uint32_t **)(dword_8F8538 + 20);
      v575 = 0;
      if ( (uint16_t)ArgList != 0 )
      {
        v172 = sub_44E8D0(dword_8F8528, (void *)0x20, 0, *(uint16_t *)(dword_8F8538 + 4));
        v575 = __RTDynamicCast(
                 v172,
                 0,
                 &IRDPopupWindow `RTTI Type Descriptor',
                 &CNRDItemTradeResultWindow `RTTI Type Descriptor',
                 0);
      }
      v576 = 0;
      if ( (uint16_t)ArgList != 0 )
      {
        do
        {
          *(uint32_t *)netshort = 0;
          v579 = 0;
          sub_404AB0(netshort);
          sub_404AB0(&v579);
          off_77F3FC("SlotIndex1 %d, SlotIndex2 %d", netshort[0], (uint16_t)v579);
          v173 = sub_44A980(netshort[0]);
          v174 = v173;
          if ( v173 != 0 )
          {
            v175 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v173 + 16))(v173);
            if ( sub_4F2D40(*(uint32_t *)(v175 + 4)) == 2 )
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v174 + 172))(v174);
          }
          v176 = (int *)sub_44A980((uint16_t)v579);
          if ( v575 != 0 )
            sub_63EDD0(v174);
          if ( v576 == (uint16_t)ArgList - 1 && v174 != 0 )
          {
            v177 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v174 + 56))(v174);
            sub_432EA0(v177, -1, 0, 0);
          }
          if ( v176 != nullptr )
          {
            v178 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v176 + 16))(v176) + 4);
            if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v174 + 16))(v174) + 4) == v178 )
            {
              v180 = *v176;
              v181 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v174 + 44))(v174);
              (*(void (/*thiscall*/ **)(int *, int))(v180 + 48))(v176, v181);
            }
            else
            {
              v179 = (*(int (/*thiscall*/ **)(int *))(*v176 + 16))(v176);
              off_77F3FC((char *)&byte_729744, *(uint32_t *)(v179 + 4));
            }
          }
          else
          {
            sub_484F40((uint16_t)v579, v174, 1);
            sub_484F40(netshort[0], 0, 1);
          }
          ++v576;
        }
        while ( v576 < (uint16_t)ArgList );
      }
      sub_4844B0(dword_8F8538);
      sub_44AB50(0, 12);
      v182 = sub_422E70(644);
      sub_43BEE0(v182, -6567706, 0, -1);
      sub_432EA0("TRADE_OK", -1, 0, 0);
      goto LABEL_336;
    case 19:
      v569 = 0;
      v573 = 0;
      v575 = 0;
      sub_404AB0(&v575);
      off_77F3FC("Sp %d", (uint16_t)v575);
      Value = (uint16_t)v575;
      sub_404A90(&v569);
      off_77F3FC("SkillNumber %d", v569);
      sub_483E30(dword_8F853C);
      sub_47E2B0();
      if ( dword_8F7C04 != 0 )
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1148))(dword_8F7C04);
      v183 = 0;
      if ( v569 != 0 )
      {
        do
        {
          HIBYTE(v567) = 0;
          HIBYTE(ArgList) = 0;
          v581 = 0;
          sub_404A90((char *)&v567 + 3);
          sub_404A90((char *)&ArgList + 3);
          sub_404A90(&v581);
          off_77F3FC("SlotIndex %d, SkillIndex %d, Level %d", HIBYTE(v567), HIBYTE(ArgList), v581);
          sub_57A3C0(HIBYTE(v567), HIBYTE(ArgList));
          v537 = v581;
          sub_47DC90(HIBYTE(ArgList));
          sub_47DEC0(0, v537);
          if ( dword_8F7C04 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1136))(
              dword_8F7C04,
              HIBYTE(ArgList),
              v581);
          ++v183;
        }
        while ( v183 < v569 );
      }
      sub_47E4F0();
      if ( dword_8F7C04 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1152))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1156))(dword_8F7C04);
      }
      sub_404A90(&v573);
      off_77F3FC("BonusSpNumber %d", v573);
      v184 = 0;
      if ( v573 != 0 )
      {
        do
        {
          HIBYTE(ArgList) = 0;
          v576 = 0;
          sub_404A90((char *)&ArgList + 3);
          sub_404AB0(&v576);
          off_77F3FC("SkillIndex %d, BonusSp %d", HIBYTE(ArgList), (uint16_t)v576);
          v185 = (uint16_t)v576;
          *(uint32_t *)(sub_47DC90(HIBYTE(ArgList)) + 540) = v185;
          ++v184;
        }
        while ( v184 < v573 );
      }
      return 1;
    case 20:
      HIBYTE(ArgList) = 0;
      v579 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0(&v579);
      off_77F3FC("SkillIndex %d, BonusSp %d", HIBYTE(ArgList), (uint16_t)v579);
      v186 = sub_47DC90(HIBYTE(ArgList));
      v187 = v186;
      if ( *(uint32_t *)(v186 + 540) < (int)(uint16_t)v579 )
      {
        v538 = sub_41ACF0(v186 + 20);
        v188 = (const char *)sub_422E70(645);
        sprintf(&Destination, v188, v538);
        sub_43BEE0(&Destination, -6567706, 0, -1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1240))(dword_8F7C04, 1, HIBYTE(ArgList));
        sub_432EA0("SP_DOWN", -1, 0, 0);
      }
      *(uint32_t *)(v187 + 540) = (uint16_t)v579;
      return 1;
    case 21:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("QuestNumber %d", HIBYTE(ArgList));
      sub_57A4F0(dword_8F8540);
      v189 = 0;
      if ( HIBYTE(ArgList) != 0 )
      {
        do
        {
          i5 = nullptr;
          sub_404AB0(&i5);
          sub_47D1E0((uint16_t)i5);
          ++v189;
        }
        while ( v189 < HIBYTE(ArgList) );
      }
      sub_47D9D0(dword_8F8540);
      sub_553FB0(*((uint32_t *)dword_8F8528 + 21));
      return 1;
    case 22:
      LOBYTE(v575) = 0;
      *(float *)&ArgList = 0.0;
      v579 = 0;
      v576 = 0;
      sub_404AB0(&ArgList);
      sub_404AB0(&v579);
      sub_404AB0(&v576);
      sub_404A90(&v575);
      off_77F3FC(
        "ServerId %d, XPos %d, YPos %d, Direction %d",
        (uint16_t)ArgList,
        (int16_t)v579,
        (int16_t)v576,
        (uint8_t)v575);
      if ( (uint16_t)ArgList != (uint16_t)word_77F804 )
      {
        v190 = *(uint32_t *)(sub_429830(ArgList) + 192);
        if ( *(uint32_t *)(*(uint32_t *)(v4[5] + 44) + 104) != 0 && (uint8_t)sub_45E680(v190) != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v190 + 364))(
            v190,
            (int16_t)v579,
            (int16_t)v576,
            v575);
      }
      return 1;
    case 23:
      HIBYTE(ArgList) = 0;
      HIBYTE(v567) = 0;
      LOBYTE(v574) = 0;
      v579 = 0;
      v575 = 0;
      v576 = 0;
      sub_404AB0(&v579);
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v567 + 3);
      sub_404AB0(&v575);
      sub_404AB0(&v576);
      sub_404A90(&v574);
      off_77F3FC(
        "ServerId %d, NewTownIndex %d, NewTownAreaIndex %d, XPos %d, YPos %d, Direction %d",
        (uint16_t)v579,
        HIBYTE(ArgList),
        HIBYTE(v567),
        (int16_t)v575,
        (int16_t)v576,
        (uint8_t)v574);
      if ( (uint16_t)v579 == (uint16_t)word_77F804 )
        return 1;
      v191 = sub_429830(v579);
      v192 = sub_42B340(v191);
      v193 = v4[5];
      v194 = v192;
      if ( HIBYTE(ArgList) == *(uint32_t *)(v193 + 100) && (v195 = sub_42F240(v193), HIBYTE(v567) == v195) )
      {
        sub_45FE80(18, (uint16_t)v579, v194, 0, 0);
        v196 = *(uint32_t *)v194;
        *(uint32_t *)netshort = (int16_t)v576;
        v580 = (int16_t)v575;
        if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(v196 + 136))(
               v194,
               (int16_t)v575,
               (int16_t)v576,
               0) == 0 )
          (*(void (/*thiscall*/ **)(int, int *, u_short *, int, uint32_t, int, int, int))(*(uint32_t *)v194 + 140))(
            v194,
            &v580,
            netshort,
            v580,
            *(uint32_t *)netshort,
            100,
            1,
            1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v194 + 112))(v194, v580, *(uint32_t *)netshort, 0);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)v194 + 364))(v194, v580, *(uint32_t *)netshort, v574);
      }
      else
      {
        sub_45F1E0(v194);
      }
      goto LABEL_365;
    case 24:
      HIBYTE(v567) = 0;
      HIBYTE(ArgList) = 0;
      v574 = 0;
      sub_404A90((char *)&v567 + 3);
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0(&v574);
      off_77F3FC("TownIndex %d, TownAreaIndex %d, UserNumber %d", HIBYTE(v567), HIBYTE(ArgList), (uint16_t)v574);
      v197 = v4[3];
      if ( v197 == 3 )
      {
        sub_41C190(1);
        sub_444B30(4);
      }
      else if ( v197 != 1 )
      {
        sub_41D300(1);
      }
      sub_45D190(SHIBYTE(v567), (void *)HIBYTE(ArgList));
      LODWORD(v564) = *(uint32_t *)(*(uint32_t *)(v4[5] + 44) + 104);
      v566 = nullptr;
      if ( (uint16_t)v574 != 0 )
      {
        do
        {
          LOBYTE(v572) = 0;
          *(uint32_t *)netshort = 0;
          v575 = 0;
          v576 = 0;
          sub_404AB0(netshort);
          sub_404AB0(&v575);
          sub_404AB0(&v576);
          sub_404A90(&v572);
          off_77F3FC(
            "ServerId %d, XPos %d, YPos %d, Direction %d",
            netshort[0],
            (int16_t)v575,
            (int16_t)v576,
            (uint8_t)v572);
          v198 = sub_429830(*(uint32_t *)netshort);
          if ( v198 != 0 )
          {
            v199 = sub_42B340(v198);
            sub_45FE80(18, netshort[0], v199, 0, 0);
            v579 = (int16_t)v576;
            v580 = (int16_t)v575;
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v199 + 136))(
                   v199,
                   (int16_t)v575,
                   (int16_t)v576,
                   0) == 0 )
              (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(*(uint32_t *)v199 + 140))(
                v199,
                &v580,
                &v579,
                v580,
                v579,
                100,
                1,
                1);
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v199 + 112))(v199, v580, v579, 0);
            if ( netshort[0] == (uint16_t)word_77F804 )
              sub_431820(*(uint8_t *)(dword_8F7A24 + 296));
            else
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v199 + 364))(v199, v580, v579, v572);
            if ( netshort[0] != (uint16_t)word_77F804 )
              sub_42FBE0(v199);
          }
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < (uint16_t)v574 );
      }
      byte_8F8118 = 0;
      sub_44F080(dword_8F8528);
      sub_45B140(v4[5]);
      *(uint8_t *)(v4[5] + 116) = 0;
      if ( dword_9B9460 != 0 )
        sub_632D40();
      if ( dword_9B9458 != 0 )
        sub_6312F0();
      sub_424A40(*(uint32_t *)(*(uint32_t *)(v4[5] + 44) + 52));
      return 1;
    case 26:
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("HostIndex %d", HIBYTE(ArgList));
      v200 = HIBYTE(ArgList);
      *(uint32_t *)(sub_656710() + 40) = v200;
      off_77F3FC("@@SET HOST %d", HIBYTE(ArgList));
      return 1;
    case 27:
      if ( a1[3] != 1 )
        sub_41D300(1);
      sub_41D300(2);
      for ( mm = 16; mm < 32; mm += 4 )
      {
        v202 = *(uint32_t *)(mm + dword_8F850C);
        if ( v202 != 0 )
        {
          v203 = *(uint32_t *)(v202 + 196);
          if ( v203 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v203 + 372))(v203, 0);
        }
      }
      return 1;
    case 28:
      HIBYTE(v567) = 0;
      HIBYTE(ArgList) = 0;
      v570 = 0;
      v581 = 0;
      v575 = 0;
      sub_404AB0(&v575);
      sub_404A90((char *)&v567 + 3);
      sub_404A90((char *)&ArgList + 3);
      sub_404A90(&v570);
      sub_404A90(&v581);
      off_77F3FC(
        "DungeonIndex %d, DungeonDifficulty %d, MazeIndex %d, BossXPos %d, BossYPos %d",
        (uint16_t)v575,
        HIBYTE(v567),
        HIBYTE(ArgList),
        v570,
        v581);
      v204 = *(uint32_t *)(v4[7] + 16);
      v205 = sub_476B60((uint16_t)v575);
      sub_4755F0((void *)HIBYTE(ArgList));
      *(uint32_t *)(v204 + 108) = v205;
      dword_99FB8C = HIBYTE(v567);
      dword_99FB7C = v570;
      dword_99FB80 = v581;
      *(uint32_t *)dword_99FB70 = 0;
      sub_4968E0(dword_99FD58);
      *((uint8_t *)dword_99FD58 + 1004) = 1;
      for ( nn = 16; nn < 32; nn += 4 )
      {
        v207 = *(uint32_t *)(nn + dword_8F850C);
        if ( v207 != 0 )
        {
          v208 = *(uint32_t *)(v207 + 196);
          if ( v208 != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v208 + 1292))(v208, v205);
        }
      }
      return 1;
    case 29:
      v573 = 0;
      HIBYTE(ArgList) = 0;
      HIBYTE(v567) = 0;
      *(uint32_t *)v568 = 0;
      sub_404A90(&v573);
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(v568);
      sub_404A90((char *)&v567 + 3);
      off_77F3FC(
        "MapXPos %d, MapYPos %d, IsSendMapInfo %d MapRandomSeed %d",
        v573,
        HIBYTE(ArgList),
        HIBYTE(v567),
        *(uint32_t *)v568);
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;
      if ( HIBYTE(v567) == 1 )
      {
        if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )
          ++word_8F7C10;
        v581 = 0;
        v579 = 0;
        sub_404AB0(&v579);
        sub_404A90(&v581);
        off_77F3FC("MapIndex %d, MonsterNumber %d", (uint16_t)v579, v581);
        v566 = (uint32_t *)sub_467600(v573, HIBYTE(ArgList));
        *v566 = (uint16_t)v579;
        v209 = 0;
        if ( v581 != 0 )
        {
          do
          {
            HIBYTE(v580) = 0;
            HIBYTE(v574) = 0;
            HIBYTE(v572) = 0;
            v576 = 0;
            v575 = 0;
            HIBYTE(v565) = 0;
            v570 = 0;
            sub_404A90((char *)&v580 + 3);
            sub_404AB0(&v576);
            sub_404AB0(&v575);
            sub_404A90((char *)&v574 + 3);
            sub_404A90((char *)&v572 + 3);
            sub_404A90((char *)&v565 + 3);
            sub_404A90(&v570);
            off_77F3FC(
              "ListIndex %d, MonsterUniqueId %d, MonsterIndex %d, MonsterLevel %d, MonsterType %d isBoxMonster %d boxIndex %d",
              HIBYTE(v580),
              (uint16_t)v576,
              (uint16_t)v575,
              HIBYTE(v574),
              HIBYTE(v572),
              HIBYTE(v565),
              v570);
            v210 = (void *)sub_488D90(
                             HIBYTE(v580),
                             (uint16_t)v576,
                             (uint16_t)v575,
                             HIBYTE(v574),
                             HIBYTE(v572),
                             HIBYTE(v565) != 0,
                             v570);
            sub_489580(v210);
            ++v209;
          }
          while ( v209 < v581 );
        }
        sub_4CE8A0((uint16_t)v579);
        v569 = 0;
        sub_404A90(&v569);
        v211 = v569;
        if ( v569 != 0 )
        {
          off_77F3FC((char *)&byte_7294BC, v569);
          v211 = v569;
        }
        v212 = 0;
        if ( v211 != 0 )
        {
          LODWORD(v564) = v566 + 5;
          do
          {
            HIBYTE(v580) = 0;
            v576 = 0;
            v574 = 0;
            *(uint32_t *)netshort = 0;
            v575 = 0;
            sub_404A90((char *)&v580 + 3);
            sub_404AB0(&v574);
            sub_404AB0(netshort);
            sub_404AD0(&v576);
            sub_404AB0(&v575);
            off_77F3FC(
              (char *)&byte_729460,
              HIBYTE(v580),
              (uint16_t)v574,
              netshort[0],
              v576,
              (uint16_t)v575);
            v213 = (void *)sub_57A280(HIBYTE(v580), (uint16_t)v574, netshort[0], v576, (uint16_t)v575);
            sub_57A8F0(v213);
            ++v212;
          }
          while ( v212 < v569 );
        }
      }
      v214 = *(uint32_t **)(*(uint32_t *)(v4[7] + 16) + 108);
      v214[123] = *(uint32_t *)v568;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )
      {
        dword_99FB84 = v573;
        dword_99FB88 = HIBYTE(ArgList);
        sub_453B80(*v214, v573, HIBYTE(ArgList));
      }
      else
      {
        sub_444E70(v573, HIBYTE(ArgList));
        sub_699030(*(uint32_t *)(v4[7] + 16) + 164);
      }
      return 1;
    case 30:
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )
      {
        sub_453B10(a1[6]);
        sub_445830(1);
      }
      else
      {
        sub_444ED0(a1[7]);
      }
      sub_57A340(*(uint32_t *)(v4[7] + 16));
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) != (uint16_t)word_8F7C10 )
        sub_42B480(500, word_8F7C10 != word_8F7C14 ? 1000 : 5000);
      v225 = 0;
      for ( i1 = 16; i1 < 32; i1 += 4 )
      {
        v227 = *(uint32_t *)(i1 + dword_8F850C);
        if ( v227 != 0 && v227 != sub_41C1B0(dword_8F8500) )
          sub_52D970(v225, 0);
        ++v225;
      }
      return 1;
    case 31:
      sub_445830(0);
      *((uint8_t *)dword_99FD58 + 1004) = 0;
      qmemcpy(&Buffer[32], (char *)dword_99FD58 + 768, 0x60u);
      v215 = sub_456390(0);
      ArgList = v215;
      sub_423200(dword_8F7B08, 49);
      v216 = 1.0 / (double)ArgList;
      *(float *)&ArgList = v216;
      sub_41C0E0((uint64_t)(v216 * *(float *)&Buffer[32]));
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[36]));
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[40]));
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[44]));
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[48]));
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[52]));
      sub_43B4C0((uint64_t)(*(float *)&Buffer[56] * *(float *)&ArgList));
      v218 = sub_477260(dword_99FD58, v217);
      sub_41C0E0((uint64_t)v218);
      v220 = sub_477280(dword_99FD58, v219);
      sub_41C0E0((uint64_t)v220);
      v221 = sub_495C80(dword_99FD58);
      sub_41C0E0(v221);
      sub_423380(dword_8F7B08);
      v539 = sub_495C80(dword_99FD58);
      v223 = (uint64_t)sub_477280(dword_99FD58, v222);
      v517 = v223;
      v508 = (uint64_t)sub_477260(dword_99FD58, HIDWORD(v223));
      off_77F3FC(
        "SEND RESULT : %d %d %d %d %d %d %d %d %d %d",
        (int)(uint64_t)*(float *)&Buffer[32] / v215,
        (int)(uint64_t)*(float *)&Buffer[36] / v215,
        (int)(uint64_t)*(float *)&Buffer[40] / v215,
        (int)(uint64_t)*(float *)&Buffer[44] / v215,
        (int)(uint64_t)*(float *)&Buffer[48] / v215,
        (int)(uint64_t)*(float *)&Buffer[52] / v215,
        (int)(uint64_t)*(float *)&Buffer[56] / v215,
        v508,
        v517,
        v539);
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )
      {
        v540 = sub_4617A0(dword_99FB8C);
        v224 = (const char *)sub_422E70(646);
        sprintf(&Destination, v224, v540);
        sub_43BEE0(&Destination, -6567706, 0, -1);
      }
      sub_57A330(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16));
      return 1;
    case 32:
      HIBYTE(ArgList) = 0;
      v580 = 0;
      sub_404AB0(&v580);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("ServerId %d, DieState %d", (uint16_t)v580, HIBYTE(ArgList));
      v228 = sub_456390(1);
      v229 = *(uint32_t *)dword_8F8520;
      HIDWORD(v564) = v228;
      v230 = (*(int (/*thiscall*/ **)(int))(v229 + 120))(dword_8F8520);
      v231 = *(uint32_t **)(v230 + 104);
      *(uint32_t *)netshort = v230;
      v232 = 0;
      v566 = v231;
      v576 = 0;
      v233 = (int *)(dword_8F850C + 16);
      while ( 1 )
      {
        v234 = *v233;
        LODWORD(v564) = *v233;
        if ( (uint32_t)v564 != 0 && *(uint16_t *)(v234 + 4) == (uint16_t)v580 && *(uint32_t *)(v234 + 196) != 0 )
          break;
        ++v232;
        ++v233;
        if ( v232 >= 4 )
        {
          v576 = v232;
          goto LABEL_460;
        }
      }
      v235 = *(int **)(v234 + 196);
      v576 = v232;
      if ( HIBYTE(ArgList) == 1 )
      {
        if ( (uint8_t)sub_45E680(v235) != 0 )
        {
          sub_45F1E0(v235);
          if ( (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235) != 0 )
          {
            v236 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235);
            sub_45F1E0(v236);
          }
        }
        (*(void (/*thiscall*/ **)(int *))(*v235 + 1020))(v235);
        (*(void (/*thiscall*/ **)(int *, int))(*v235 + 1200))(v235, 1);
        v237 = *v235;
        v238 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*v235 + 740))(v235, 0, 1);
        (*(void (/*thiscall*/ **)(int *, int))(v237 + 732))(v235, v238);
        v239 = *v235;
        v240 = (*(int (/*thiscall*/ **)(int *, int))(*v235 + 756))(v235, 1);
        (*(void (/*thiscall*/ **)(int *, int))(v239 + 748))(v235, v240);
        sub_45FE80(273, (uint16_t)v580, v235, 0, 0);
        if ( (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235) != 0 )
        {
          v241 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235);
          sub_45FE80(65, (uint16_t)v580, v241, 0, 0);
        }
        v242 = *(uint32_t *)(*(uint32_t *)netshort + 52);
        if ( v242 != 0 )
        {
          v243 = *v235;
          v244 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v242 + 124))(v242, 0);
          v245 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v242 + 120))(v242, v244);
          (*(void (/*thiscall*/ **)(int *, int))(v243 + 112))(v235, v245);
          v234 = v564;
        }
        else
        {
          v246 = (*(int (/*thiscall*/ **)(int *))(*v235 + 120))(v235);
          v247 = *(uint32_t *)(*(uint32_t *)netshort + 44);
          v248 = *v235;
          v575 = v246;
          LODWORD(v564) = (*(int (/*thiscall*/ **)(int *))(v248 + 124))(v235);
          if ( (int)v564 >= sub_425050(v247) )
            v249 = sub_425050(*(uint32_t *)(*(uint32_t *)netshort + 44));
          else
            v249 = (*(int (/*thiscall*/ **)(int *))(*v235 + 124))(v235);
          v250 = *v235;
          *(uint32_t *)v568 = v249;
          (*(void (/*thiscall*/ **)(int *, int *, char *, int, int, int, int, int))(v250 + 140))(
            v235,
            &v575,
            v568,
            v575,
            v249,
            640,
            1,
            1);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*v235 + 112))(v235, v575, *(uint32_t *)v568, 0);
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v235 + 308))(v235) != 0 )
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v235 + 580))(
            v235,
            48001,
            1,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
        v251 = dword_8F7C04;
        if ( (int *)dword_8F7C04 == v235 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*v235 + 560))(v235, 0, 0, 0, 0);
          (*(void (/*thiscall*/ **)(int *))(*v235 + 564))(v235);
          sub_57A2F0(*(uint32_t *)netshort);
          v251 = dword_8F7C04;
        }
        if ( v251 != 0 )
        {
          v252 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v251 + 376))(v251);
          if ( v252 == (*(int (/*thiscall*/ **)(int *))(*v235 + 376))(v235) )
            sub_57A310(*(uint32_t *)netshort);
        }
        v541 = unknown_libname_2(v234 + 16);
        v253 = (const char *)sub_422E70(647);
        sprintf(&Destination, v253, v541);
        sub_43BEE0(&Destination, -6567706, 0, -1);
        v254 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1216))(v235);
        sub_495DA0(v254);
        sub_49C620(1, 1, 0);
        sub_49C5F0(1, 0, 0, 1500);
        sub_432EA0("COIN_INSERT", -1, 0, 0);
      }
      else
      {
        if ( SHIDWORD(v564) > 1 )
          sub_45F1E0(v235);
        v542 = unknown_libname_2(v234 + 16);
        v256 = (const char *)sub_422E70(648);
        sprintf(&Destination, v256, v542);
        sub_43BEE0(&Destination, -6567706, 0, -1);
      }
      LOBYTE(v255) = HIBYTE(ArgList) == 0;
      (*(void (/*thiscall*/ **)(int *, int))(*v235 + 1192))(v235, v255);
      v232 = v576;
LABEL_460:
      if ( v232 == 4 )
        off_77F3FC((char *)&byte_7293E8);
      if ( (int)sub_456390(1) <= 0 )
      {
        if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 608) + 4) == 0
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0 )
        {
          sub_49BDB0(2);
          goto LABEL_478;
        }
      }
      else
      {
        for ( i2 = 16; i2 < 32; i2 += 4 )
        {
          v258 = *(uint32_t *)(i2 + dword_8F850C);
          if ( v258 != 0 )
          {
            v259 = *(uint32_t *)(v258 + 196);
            if ( v259 != 0
              && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v259 + 1196))(v259) != 0
              && (uint8_t)sub_45E680(v259) != 0 )
            {
              sub_45F1E0(v259);
            }
          }
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 608) + 4) == 0
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0 )
        {
          sub_49BDB0(1);
LABEL_478:
          v260 = sub_424310(dword_8F7C04);
          sub_424A40(v260);
          return 1;
        }
      }
      sub_49BDB0(0);
      goto LABEL_478;
    case 33:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("Stamina %d", HIBYTE(ArgList));
      v261 = dword_8F7C04;
      if ( dword_8F7C04 != 0 )
      {
        if ( HIBYTE(ArgList) != 100 )
        {
          sub_57A2B0(*(uint32_t *)(*(uint32_t *)(v4[7] + 16) + 108));
          v261 = dword_8F7C04;
        }
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v261 + 1060))(v261, HIBYTE(ArgList));
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
      }
      return 1;
    case 34:
      v262 = *((uint8_t **)dword_8F8528 + 608);
      sub_4772A0(0);
      sub_45A420(0);
      sub_49BDB0(0);
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v580 + 3);
      sub_404A90((char *)&v574 + 3);
      sub_404A90((char *)&v572 + 3);
      sub_404A90((char *)&v565 + 3);
      off_77F3FC(
        "Rank %d, NewStyle %d, NewTechnic %d, NewHit %d, NewRank %d",
        HIBYTE(ArgList),
        HIBYTE(v580),
        HIBYTE(v574),
        HIBYTE(v572),
        HIBYTE(v565));
      v263 = sub_495C80(dword_99FD58);
      if ( HIBYTE(ArgList) == v263 )
      {
        v262[240] = HIBYTE(v580) != 0;
        v262[241] = HIBYTE(v574) != 0;
        v262[242] = HIBYTE(v572) != 0;
      }
      else
      {
        v264 = sub_495C80(dword_99FD58);
        off_77F3FC(aCriticalEnumNo, HIBYTE(ArgList), v264);
      }
      return 1;
    case 35:
      v265 = *((uint32_t **)dword_8F8528 + 608);
      v266 = *((uint32_t *)dword_8F8528 + 609);
      v575 = 0;
      v576 = 0;
      v579 = 0;
      *(uint32_t *)netshort = 0;
      v571 = 0;
      sub_404A90((char *)&v574 + 3);
      sub_404AD0((char *)&v564 + 4);
      sub_404AD0(&v564);
      sub_404AD0(v568);
      sub_404AD0(&v575);
      sub_404AD0(&v576);
      sub_404AD0(&v579);
      sub_404AD0(netshort);
      sub_404AD0(&v571);
      off_77F3FC(
        "GainedSp %d, GainedExp %d, GainedRankBonusExp %d, gainedPartyBonusExp %d gainedAvatarBonusExp %d\n"
        "\t\t\t\t   gainedBurningTimeExp %d gainedPremiumExp %d gainedMatchedChannelExp %d gainedMemberExp %d",
        HIBYTE(v574),
        HIDWORD(v564),
        (uint32_t)v564,
        *(uint32_t *)v568,
        v575,
        v576,
        v579,
        *(uint32_t *)netshort,
        v571);
      v265[58] = HIDWORD(v564) - *(uint32_t *)v568;
      v265[51] = v564;
      v265[52] = *(uint32_t *)v568;
      v265[53] = v575;
      v265[56] = v576;
      v265[54] = v579;
      v265[55] = *(uint32_t *)netshort;
      v265[57] = v571;
      sub_404A90((char *)&v580 + 3);
      off_77F3FC("GainedQuestItemSlot %d", HIBYTE(v580));
      v566 = nullptr;
      if ( HIBYTE(v580) != 0 )
      {
        do
        {
          sub_404AB0((char *)&v572 + 2);
          sub_404AB0((char *)&v565 + 2);
          sub_404AD0(&i5);
          sub_404AB0((char *)&v567 + 2);
          off_77F3FC(
            "SlotIndex %d, ItemIndex %d, ItemData %d, Durability %d",
            HIWORD(v572),
            HIWORD(v565),
            i5,
            HIWORD(v567));
          v267 = sub_44A980(HIWORD(v572));
          if ( v267 != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v267 + 60))(v267, HIWORD(v565)) != 0 )
              (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)v267 + 48))(v267, i5);
            else
              off_77F3FC(aCriticalError_22, HIWORD(v572));
          }
          else
          {
            v268 = sub_522300((void *)HIWORD(v565), (int)i5, 0, 0, HIWORD(v567), 1);
            sub_484F40(HIWORD(v572), v268, 1);
          }
          v566 = (uint32_t *)((char *)v566 + 1);
        }
        while ( (int)v566 < HIBYTE(v580) );
      }
      v269 = 0;
      i5 = (void *)(v266 + 564);
      do
      {
        sub_404A90((char *)&ArgList + 3);
        off_77F3FC("UseGainedItemSlot %d", HIBYTE(ArgList));
        if ( HIBYTE(ArgList) != 0 )
        {
          ++*(uint32_t *)(v266 + 436);
          v270 = 0;
          if ( HIBYTE(ArgList) != 0 )
          {
            do
            {
              sub_404AB0((char *)&v572 + 2);
              sub_404AD0(&v565);
              off_77F3FC("ItemIndex %d, StackNumber %d", HIWORD(v572), v565);
              sub_45A750(HIWORD(v572), v565, v269);
              ++v270;
            }
            while ( v270 < HIBYTE(ArgList) );
          }
        }
        else
        {
          *(uint32_t *)i5 = -1;
        }
        ++v269;
        i5 = (char *)i5 + 4;
      }
      while ( v269 < 4 );
      v271 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      sub_47BBE0(**(uint32_t **)(v271 + 108), dword_99FB8C);
      sub_4772A0(1);
      return 1;
    case 36:
      *(float *)&ArgList = 0.0;
      i5 = nullptr;
      sub_404AB0(&ArgList);
      sub_404AB0(&i5);
      off_77F3FC("Fatigue %d, FatigueMax %d", (uint16_t)ArgList, (uint16_t)i5);
      word_8F7C10 = ArgList;
      word_8F7C14 = (int16_t)i5;
      return 1;
    case 37:
      LOBYTE(ArgList) = 0;
      *(uint32_t *)netshort = 0;
      v579 = 0;
      v571 = 0;
      i5 = nullptr;
      sub_404A90(&ArgList);
      sub_404AD0(&v579);
      sub_404AD0(&v571);
      sub_404AD0(&i5);
      sub_404AB0(netshort);
      off_77F3FC("Level %d, Exp1 %d, Exp2 %d, Exp3 %d, Sp %d", (uint8_t)ArgList, v579, v571, i5, netshort[0]);
      v272 = dword_8F7C04;
      v273 = sub_41C1B0(dword_8F8500);
      v274 = sub_41A5E0(v273 + 53);
      if ( v274 != (uint8_t)ArgList )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 15, 2);
        v275 = *(uint32_t *)dword_8F8520;
        v276 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v272 + 48))(v272);
        (*(void (/*thiscall*/ **)(int, int))(v275 + 36))(dword_8F8520, v276);
        v277 = *(uint32_t *)dword_8F8520;
        v278 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v272 + 52))(v272);
        (*(void (/*thiscall*/ **)(int, int))(v277 + 36))(dword_8F8520, v278);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v274);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        sub_41C1B0(dword_8F8500);
        sub_41C150((uint8_t)ArgList);
        if ( (uint8_t)ArgList > v274 )
          *(uint8_t *)(dword_8F8500 + 16) = 1;
      }
      LODWORD(v279) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v272 + 1032))(v272);
      HIDWORD(v279) = v571;
      v280 = v579 - *(uint32_t *)(v279 + 48);
      if ( v280 <= 0 )
      {
        if ( v280 < 0 )
        {
          v285 = (const char *)sub_422E70(651);
          sprintf(Buffer, v285, -v280);
          sub_43BEE0(Buffer, -6567706, 0, -1);
        }
      }
      else
      {
        if ( v571 != 0 )
        {
          if ( i5 != nullptr )
          {
            v518 = __PAIR64__((unsigned int)i5, v571);
            v509 = v280 - (uint32_t)i5 - v571;
            v281 = (const char *)sub_422E70(1519);
            sprintf(Buffer, v281, v280, v509, v518);
          }
          else
          {
            LODWORD(v279) = v280 - v571;
            v519 = v279;
            v282 = (const char *)sub_422E70(1517);
            sprintf(Buffer, v282, v280, v519);
          }
        }
        else if ( i5 != nullptr )
        {
          v543 = i5;
          v520 = v280 - (uint32_t)i5 - v571;
          v283 = (const char *)sub_422E70(1518);
          sprintf(Buffer, v283, v280, v520, v543);
        }
        else
        {
          v284 = (const char *)sub_422E70(1516);
          sprintf(Buffer, v284, v280);
        }
        sub_43BEE0(Buffer, -6567706, 0, -1);
        if ( dword_8F7C04 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1260))(
            dword_8F7C04,
            0,
            v280,
            0,
            0,
            0,
            0,
            0,
            0);
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)v272 + 1036))(v272, v579, (uint8_t)ArgList);
      if ( netshort[0] > Value )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v272 + 1232))(v272, 1);
        sub_57A430(1);
        v286 = sub_422E70(652);
        sub_43BEE0(v286, -6567706, 0, -1);
        sub_432EA0("SP_GET", -1, 0, 0);
      }
      Value = netshort[0];
      return 1;
    case 38:
      HIBYTE(ArgList) = 0;
      v581 = -1;
      HIBYTE(v580) = 0;
      *(uint32_t *)netshort = 0;
      sub_404AB0(netshort);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("MonsterUniqueId %d, ItemNumber %d", netshort[0], HIBYTE(ArgList));
      v287 = v4[3];
      if ( v287 == 3 )
      {
        v288 = v4[7];
      }
      else
      {
        if ( v287 != 6 )
          goto LABEL_525;
        v288 = v4[10];
      }
      if ( *(uint32_t *)(*(uint32_t *)(v288 + 16) + 104) != 0 )
      {
        v289 = sub_45EBE0(529, netshort[0]);
        v290 = (uint32_t *)__RTDynamicCast(
                           v289,
                           0,
                           &CNRDObject `RTTI Type Descriptor',
                           &IRDMonster `RTTI Type Descriptor',
                           0);
        if ( v290 == nullptr )
          off_77F3FC(aCriticalError_23, netshort[0]);
        srand(10 * (HIBYTE(ArgList) + 100 * netshort[0]));
        rand();
        LODWORD(v564) = 0;
        if ( HIBYTE(ArgList) != 0 )
        {
          do
          {
            *(uint32_t *)v568 = 0;
            v576 = 0;
            v571 = 0;
            i5 = (void *)0xFFFF;
            v575 = 0;
            sub_404AB0(v568);
            sub_404AB0(&v576);
            sub_404AD0(&v575);
            sub_404AB0(&v571);
            sub_404AB0(&i5);
            off_77F3FC(
              "ItemUniqueId %d, ItemIndex %d, Data %u, Durability %d rootableServerId %d",
              *(uint16_t *)v568,
              (uint16_t)v576,
              v575,
              (uint16_t)v571,
              (uint16_t)i5);
            if ( v290 != nullptr )
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v290 + 1188))(
                v290,
                HIBYTE(ArgList),
                (uint16_t)v576,
                v575,
                *(uint16_t *)v568,
                (uint16_t)v571,
                (uint16_t)i5);
            LODWORD(v564) = v564 + 1;
          }
          while ( (int)v564 < HIBYTE(ArgList) );
        }
        sub_404A90((char *)&v580 + 3);
        off_77F3FC("isWarRoom %d", SHIBYTE(v580));
        if ( HIBYTE(v580) != 0 && dword_99FF08 != 0 && v290 != nullptr )
        {
          i5 = (void *)0xFFFF;
          v574 = 0;
          *(uint32_t *)v568 = 0;
          sub_404AB0(&i5);
          sub_404AB0(&v574);
          sub_404AD0(v568);
          off_77F3FC(
            "lastAttackerServerId %d addKP %d displayExp %d",
            (uint16_t)i5,
            (uint16_t)v574,
            *(uint32_t *)v568);
          v291 = dword_99FF08;
          v571 = -1;
          v575 = sub_48FB60((uint16_t)i5, &v571);
          if ( v575 != 0 )
          {
            *(uint32_t *)(v291 + 4 * v571 + 80) += (uint16_t)v574;
            *(uint32_t *)(v291 + 4 * v571 + 112) += (uint16_t)v574;
            sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
            LODWORD(v564) = *(uint32_t *)(v575 + 196);
            if ( (uint32_t)v564 != 0 )
            {
              v292 = *(uint32_t *)v564;
              v293 = (*(int (/*thiscall*/ **)(uint32_t *))(*v290 + 128))(v290);
              v294 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 124))(v290, v293);
              v295 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 120))(v290, v294);
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(v292 + 1264))(
                v564,
                (uint16_t)v574,
                0,
                1,
                v295);
              v296 = *v290;
              v297 = **(uint32_t **)(v575 + 196);
              LODWORD(v564) = *(uint32_t *)(v575 + 196);
              v298 = (*(int (/*thiscall*/ **)(uint32_t *))(v296 + 128))(v290);
              v299 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 124))(v290, v298);
              v300 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 120))(v290, v299);
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(v297 + 1260))(
                v564,
                0,
                *(uint32_t *)v568,
                0,
                0,
                1,
                v300);
            }
            v544 = sub_4633B0(v290);
            v521 = unknown_libname_2(v575 + 16);
            v301 = (const char *)sub_422E70(1930);
            sprintf(Format, v301, v521, v544);
            sub_43BEE0(Format, -13435036, 0, -1);
          }
        }
        else
        {
          sub_404A90(&v581);
          off_77F3FC("championKeyCount %d", (char)v581);
        }
        if ( v290 != nullptr )
        {
          if ( v581 != 0xFF )
          {
            off_77F3FC((char *)&byte_729010, *(uint32_t *)dword_99FB70, (char)v581);
            if ( (char)v581 > *(int *)dword_99FB70 )
            {
              *(uint32_t *)dword_99FB70 = (char)v581;
              *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 1140) = 1;
              v302 = *((uint32_t *)dword_8F8528 + 4) + 1128;
              *(uint8_t *)(v302 + 13) = 0;
              *(uint8_t *)(v302 + 14) = 0;
              sub_698F90(0, 0);
              sub_496BD0(v290);
            }
          }
          if ( v290[1943] == 3 )
            sub_496BD0(v290);
          v303 = *(uint32_t **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108);
          v304 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v290 + 340))(v290);
          sub_47BEE0(*v303, dword_99FB8C, *v304);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v290 + 84))(v290, 0);
          v545 = netshort[0];
          v305 = sub_4633B0(v290);
          off_77F3FC((char *)&byte_728FD0, v305, v545);
          if ( v4[3] == 6 )
            sub_461520(*((uint32_t *)dword_8F8528 + 4));
        }
        return 1;
      }
LABEL_525:
      off_77F3FC(aErrorD_1, v4[3]);
      return 1;
    case 39:
      v306 = 0;
      v571 = 0;
      i5 = nullptr;
      sub_404AB0(&v571);
      sub_404AB0(&i5);
      off_77F3FC("ItemUniqueId %d, ServerId %d", (uint16_t)v571, (uint16_t)i5);
      if ( (uint16_t)i5 == (uint16_t)word_77F804 )
        sub_484FF0(dword_8F852C);
      v307 = sub_45EBE0(289, (uint16_t)v571);
      v308 = __RTDynamicCast(v307, 0, &CNRDObject `RTTI Type Descriptor', &CNRDItemObject `RTTI Type Descriptor', 0);
      v309 = v308;
      HIDWORD(v564) = v308;
      if ( v308 == 0 )
      {
        off_77F3FC(aCriticalError_25);
        return 1;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v308 + 84))(v308, 0);
      v576 = *(uint32_t *)(v309 + 972);
      if ( v576 == 0 )
      {
        off_77F3FC(aCriticalError_24);
        return 1;
      }
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v576 + 16))(v576) + 4) != 0 )
      {
        *(uint32_t *)netshort = 0;
        v580 = 0;
        for ( i3 = 0; i3 < 4; ++i3 )
        {
          sub_404A90((char *)&v564 + i3);
          off_77F3FC("[%d] DICE %d", i3, *((uint8_t *)&v564 + i3));
        }
        sub_404AB0(netshort);
        sub_404AB0(&v580);
        off_77F3FC("ServerId %d, SlotIndex %d", netshort[0], (uint16_t)v580);
        v313 = 0;
        HIBYTE(ArgList) = 0;
        strcpy(Str, (const char *)sub_422E70(653));
        *(uint32_t *)v568 = 0;
        v575 = 16;
        do
        {
          v314 = *((uint8_t *)&v564 + *(uint32_t *)v568);
          if ( v314 != 0 )
          {
            v315 = *(uint32_t *)(v575 + dword_8F850C);
            if ( v315 != 0 )
            {
              v546 = v314;
              v316 = (const char *)unknown_libname_2(v315 + 16);
              sprintf(byte_9B9288, " %s[%d]", v316, v546);
              v318 = strlen(byte_9B9288) + 1;
              v319 = &v585;
              do
                v320 = *++v319;
              while ( v320 != 0 );
              qmemcpy(v319, byte_9B9288, v318);
              LOWORD(v317) = *(uint16_t *)(v315 + 4);
              v321 = *(int **)(v315 + 196);
              v322 = *v321;
              LOBYTE(v317) = (uint16_t)v317 == netshort[0];
              HIBYTE(ArgList) = 1;
              (*(void (/*thiscall*/ **)(int *, int))(v322 + 1256))(v321, v317);
            }
            v313 = HIBYTE(ArgList);
          }
          v32 = v575 + 4 < 32;
          ++*(uint32_t *)v568;
          v575 += 4;
        }
        while ( v32 );
        if ( v313 != 0 )
          sub_43BEE0(Str, -11600063, 0, -1);
        v323 = sub_429830(*(uint32_t *)netshort);
        v324 = v576;
        if ( v323 != 0 )
        {
          v522 = v323;
          v325 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v576 + 44))(v576);
          sub_4337E0(v324, v325, v522, v313 != 0 ? 0x1F4 : 0);
        }
        if ( netshort[0] == (uint16_t)word_77F804 )
        {
          sub_57A360(HIDWORD(v564));
          *(float *)&ArgList = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v324 + 44))(v324));
          HIDWORD(v564) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v324 + 36))(v324);
          sub_432EA0("ITEM_PICK", -1, 0, 0);
          v326 = (uint16_t)v580;
          v327 = (uint32_t *)sub_44A980((uint16_t)v580);
          v328 = v327;
          if ( v327 != nullptr )
          {
            v329 = *v327;
            v330 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v324 + 16))(v324);
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(v329 + 60))(v328, *(uint32_t *)(v330 + 4)) != 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*v328 + 48))(v328, ArgList);
            }
            else
            {
              v331 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v324 + 16))(v324);
              v332 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v328 + 16))(v328, *(uint32_t *)(v331 + 4));
              off_77F3FC(aErrorD_2, (uint16_t)v580, *(uint32_t *)(v332 + 4));
            }
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v324 + 4))(v324, 1);
          }
          else
          {
            sub_484F40(v326, v324, 1);
            v328 = (uint32_t *)v324;
          }
          v333 = *((uint32_t *)dword_8F852C + 1);
          v334 = v333 - sub_484FA0();
          v566 = (uint32_t *)v334;
          if ( v334 <= 0 || SHIDWORD(v564) <= 0 )
            goto LABEL_336;
          v335 = v334 - 1;
          v336 = v335 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v328 + 16))(v328) + 56);
          v337 = ArgList;
          if ( v336 + 1 < ArgList )
            v337 = v335 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v328 + 16))(v328) + 56) + 1;
          sub_486330((uint16_t)v580, v337);
          v523 = (double)(int)v566 * 0.001;
          v338 = (const char *)sub_422E70(654);
          sprintf(OutputString, v338, v523);
          sub_43BEE0(OutputString, -6567706, 0, -1);
        }
      }
      else
      {
        v310 = sub_41C1B0(dword_8F8500);
        for ( i4 = 16; i4 < 32; i4 += 4 )
        {
          *(float *)&ArgList = 0.0;
          sub_404AD0(&ArgList);
          off_77F3FC("[%d] MONEY %u", v306, ArgList);
          if ( v310 == *(uint32_t *)(i4 + dword_8F850C) && *(float *)&ArgList != 0.0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(
              **((uint32_t **)dword_8F852C + 3),
              ArgList);
            sub_432EA0("ITEM_PICK", -1, 0, 0);
            sub_4337E0(v576, ArgList, v310, 0);
          }
          ++v306;
        }
      }
      return 1;
    case 40:
      LOBYTE(i5) = 0;
      LODWORD(v564) = 0;
      v576 = 0;
      v575 = 0;
      v579 = 0;
      *(uint32_t *)v568 = 0;
      *(float *)&ArgList = 0.0;
      v571 = 0;
      sub_404AB0(&v564);
      sub_404AB0(&v576);
      sub_404AB0(&v575);
      sub_404AB0(&v579);
      sub_404AB0(v568);
      sub_404A90(&i5);
      sub_404AD0(&v571);
      sub_404AB0(&ArgList);
      off_77F3FC(
        "serverId %d, xPos %d, yPos %d, itemUniqueId %d, itemIndex %d, ext_data1 %d, data %d, durability %d",
        (uint16_t)v564,
        (int16_t)v576,
        (int16_t)v575,
        (uint16_t)v579,
        *(uint16_t *)v568,
        (uint8_t)i5,
        v571,
        (uint16_t)ArgList);
      v359 = sub_522300((void *)*(uint16_t *)v568, v571, (int)i5, 0, (uint16_t)ArgList, 1);
      Block[0] = operator new(0x424u);
      v607 = 7;
      if ( Block[0] != nullptr )
        v360 = (int *)sub_4E2130(v359, 0, 0);
      else
        v360 = nullptr;
      v361 = *v360;
      v607 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int))(v361 + 112))(v360, (int16_t)v576, (int16_t)v575, 60);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v360 + 60))(v360) + 36) = -1500;
      sub_45FE80(289, (uint16_t)v579, v360, 0, 0);
      return 1;
    case 41:
      v579 = 0;
      sub_404AB0(&v579);
      off_77F3FC("PVP RoomNumber %d", (uint16_t)v579);
      HIDWORD(v564) = 0;
      if ( (uint16_t)v579 != 0 )
      {
        do
        {
          Destination = 0;
          memset(v600, 0, sizeof(v600));
          HIBYTE(ArgList) = 0;
          HIBYTE(v580) = 0;
          HIBYTE(v574) = 0;
          i5 = nullptr;
          v571 = 0;
          sub_404AB0(&i5);
          sub_404A90((char *)&ArgList + 3);
          if ( HIBYTE(ArgList) == 0 )
          {
            v362 = (char *)sub_422E70(655);
            sub_48BCC0(&Destination, 64, v362);
          }
          sub_404A90((char *)&v580 + 3);
          sub_404A90((char *)&v574 + 3);
          sub_404AB0(&v571);
          off_77F3FC(
            "PVP RoomIndex %d, TitleIndex %d, Title [%s], RoomState %d, MasterSeatIndex %d pvpMapIndex %d",
            (uint16_t)i5,
            HIBYTE(ArgList),
            &Destination,
            HIBYTE(v580),
            HIBYTE(v574),
            (uint16_t)v571);
          v363 = (uint32_t *)sub_4879B0((uint16_t)i5);
          v363[19] = HIBYTE(ArgList);
          sub_406D60(&Destination);
          v363[18] = HIBYTE(v580);
          v363[28] = (uint16_t)v571;
          sub_48FA30(SHIBYTE(v574));
          HIBYTE(v567) = 0;
          HIBYTE(v565) = 0;
          v364 = 0;
          v365 = v363 + 10;
          do
          {
            HIBYTE(v572) = 0;
            LODWORD(v564) = 0;
            sub_404A90((char *)&v572 + 3);
            sub_404AB0(&v564);
            if ( *v365 == (uint16_t)word_77F804 )
              HIBYTE(v567) = 1;
            if ( (uint16_t)v564 == (uint16_t)word_77F804 )
              HIBYTE(v565) = 1;
            sub_48F700(v364++, (uint16_t)v564, HIBYTE(v572));
            ++v365;
          }
          while ( v364 < 8 );
          if ( HIBYTE(v565) != 0 )
          {
            sub_48F890(v363);
          }
          else if ( HIBYTE(v567) != 0 )
          {
            sub_48F890(0);
          }
          ++HIDWORD(v564);
        }
        while ( SHIDWORD(v564) < (uint16_t)v579 );
      }
      if ( dword_9B9534 != 0 )
        sub_642990(1);
      return 1;
    case 42:
      i5 = nullptr;
      v571 = 0;
      HIBYTE(ArgList) = 0;
      HIBYTE(v580) = 0;
      sub_404AB0(&i5);
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v580 + 3);
      sub_404AB0(&v571);
      off_77F3FC(
        "RoomIndex %d, RoomState %d, MasterSeatIndex %d pvpMapIndex %d",
        (uint16_t)i5,
        HIBYTE(ArgList),
        HIBYTE(v580),
        (uint16_t)v571);
      v370 = (uint16_t)i5;
      v371 = sub_487420((uint16_t)i5);
      if ( v371 != 0 )
      {
        if ( HIBYTE(ArgList) != 0 )
        {
          *(uint32_t *)(v371 + 72) = HIBYTE(ArgList);
          sub_48FA30(SHIBYTE(v580));
          *(uint32_t *)(v371 + 112) = (uint16_t)v571;
          if ( dword_99FEC0 == v371 )
          {
            off_77F3FC(
              "roomState %d getPVPModule()->isWaitingRoomReadyPacket() %d",
              HIBYTE(ArgList),
              *(uint8_t *)(v4[8] + 120));
            if ( HIBYTE(ArgList) == 1 && *(uint8_t *)(v4[8] + 120) != 0 )
              sub_453050(0, 0);
          }
        }
        else
        {
          sub_487670(v370);
        }
      }
      else
      {
        off_77F3FC(aCriticalError_28, v370);
      }
      return 1;
    case 43:
      HIBYTE(ArgList) = 0;
      i5 = nullptr;
      sub_404AB0(&i5);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("RoomIndex %d, SeatNumber %d", (uint16_t)i5, HIBYTE(ArgList));
      v372 = (uint16_t)i5;
      v373 = sub_487420((uint16_t)i5);
      if ( v373 != 0 )
      {
        LODWORD(v564) = 0;
        if ( HIBYTE(ArgList) != 0 )
        {
          do
          {
            HIBYTE(v580) = 0;
            HIBYTE(v574) = 0;
            v571 = 0;
            sub_404A90((char *)&v580 + 3);
            sub_404A90((char *)&v574 + 3);
            sub_404AB0(&v571);
            off_77F3FC("SeatIndex %d, SeatState %d, ServerId %d", HIBYTE(v580), HIBYTE(v574), (uint16_t)v571);
            HIBYTE(v572) = *(uint32_t *)(v373 + 4 * HIBYTE(v580) + 40) == (uint16_t)word_77F804;
            v374 = (uint16_t)v571 == (uint16_t)word_77F804;
            sub_48F700(SHIBYTE(v580), (uint16_t)v571, HIBYTE(v574));
            if ( v374 )
            {
              sub_48F890(v373);
            }
            else if ( HIBYTE(v572) != 0 )
            {
              sub_48F890(0);
            }
            LODWORD(v564) = v564 + 1;
          }
          while ( (int)v564 < HIBYTE(ArgList) );
        }
      }
      else
      {
        off_77F3FC(aCriticalError_29, v372);
      }
      return 1;
    case 44:
      HIBYTE(v580) = 0;
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&v580 + 3);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("SeatIndex %d, IsReady %d", HIBYTE(v580), HIBYTE(ArgList));
      sub_48F580(HIBYTE(v580), HIBYTE(ArgList) != 0);
      return 1;
    case 45:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      *(uint32_t *)(dword_99FEC0 + 116) = HIBYTE(ArgList);
      off_77F3FC("start PVPMap Num %d", HIBYTE(ArgList));
      sub_453050(1, 0);
      sub_4968E0(dword_99FD58);
      *((uint8_t *)dword_99FD58 + 1004) = 1;
      return 1;
    case 46:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("SeatIndex %d", HIBYTE(ArgList));
      if ( dword_99FEC0 != 0 )
      {
        v420 = sub_48F690(HIBYTE(ArgList));
        v421 = v420;
        if ( v420 != 0 )
        {
          v422 = *(uint32_t *)(v420 + 196);
          if ( v422 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v422 + 1192))(v422, 1);
            v549 = HIBYTE(ArgList);
            v423 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
            sub_426820(v423, 5, v549);
            v424 = *(uint32_t *)(v421 + 196);
            if ( v424 == *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 52) )
            {
              v550 = dword_8F7C04;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              v551 = sub_424310(v550);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              sub_424A40(v551);
            }
          }
        }
      }
      return 1;
    case 47:
      HIBYTE(v580) = 0;
      HIBYTE(ArgList) = 0;
      v581 = 0;
      HIBYTE(v574) = 0;
      *(uint32_t *)v568 = 0;
      v571 = 0;
      LODWORD(v564) = 0;
      v579 = 0;
      *(uint32_t *)netshort = 0;
      v572 = 0;
      i5 = nullptr;
      v575 = 0;
      sub_404A90((char *)&v580 + 3);
      sub_404AD0(v568);
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&v571);
      v576 = 0;
      v425 = sub_41C1B0(dword_8F8500);
      if ( *(uint32_t *)(v425 + 116) == HIBYTE(ArgList) )
      {
        v576 = 0;
      }
      else
      {
        v426 = sub_41C1B0(dword_8F8500);
        if ( *(uint32_t *)(v426 + 116) >= (int)HIBYTE(ArgList) )
        {
          v427 = sub_41C1B0(dword_8F8500);
          if ( *(uint32_t *)(v427 + 116) > (int)HIBYTE(ArgList) )
            v576 = -1;
        }
        else
        {
          v576 = 1;
        }
      }
      v428 = sub_41C1B0(dword_8F8500);
      *(uint32_t *)(v428 + 116) = HIBYTE(ArgList);
      sub_404A90(&v581);
      off_77F3FC(
        "winnerSeatIndex %d, medal %d, myPVPRank %d playerCount %d",
        HIBYTE(v580),
        *(uint32_t *)v568,
        HIBYTE(ArgList),
        v581);
      sub_54F540(0);
      HIDWORD(v564) = 0;
      if ( v581 != 0 )
      {
        do
        {
          sub_404AB0(&i5);
          sub_404AD0(&v564);
          sub_550020((uint16_t)i5, v564);
          sub_404A90((char *)&v574 + 3);
          sub_404AD0(&v579);
          sub_404AD0(netshort);
          sub_404AD0(&v572);
          v429 = sub_429830(i5);
          if ( v429 != 0 )
          {
            *(uint32_t *)(v429 + 116) = HIBYTE(v574);
            if ( v429 == sub_41C1B0(dword_8F8500) )
              sub_57A460(v571);
          }
          ++HIDWORD(v564);
        }
        while ( SHIDWORD(v564) < v581 );
      }
      sub_404AB0(&v575);
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 168) = (uint16_t)v575;
      sub_453050(4, 0);
      sub_5500B0(HIBYTE(v580));
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 140) = HIBYTE(ArgList);
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 136) = v576;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 144) = v571;
      sub_54E160(*(uint32_t *)v568);
      sub_54F540(1);
      *((uint8_t *)dword_99FD58 + 1004) = 0;
      sub_47BAA0(dword_8F8540);
      return 1;
    case 48:
      *(float *)&ArgList = 0.0;
      i5 = nullptr;
      v575 = 0;
      *(uint32_t *)v568 = 0;
      v571 = 0;
      sub_404AD0(&ArgList);
      sub_404AD0(&i5);
      sub_404AD0(&v575);
      sub_404AD0(v568);
      sub_404AD0(&v571);
      off_77F3FC(
        "WinNumber %d, LoseNumber %d curPVPExp %d minPVPExp %d maxPVPExp %d",
        ArgList,
        i5,
        v575,
        *(uint32_t *)v568,
        v571);
      dword_8F7C18 = ArgList;
      dword_8F7C1C = (int)i5;
      if ( dword_8F7C04 != 0 )
      {
        v430 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
        v431 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(
                 dword_8F7C04,
                 *(uint32_t *)(v430 + 56));
        v432 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(
                 dword_8F7C04,
                 *(uint32_t *)(v431 + 60));
        sub_54DF30(*(uint32_t *)(v432 + 52), v558, v559);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1040))(dword_8F7C04, v575);
      }
      return 1;
    case 49:
      qmemcpy(&Buffer[32], (char *)dword_99FD58 + 768, 0x60u);
      v433 = (uint64_t)*(float *)&Buffer[108];
      v434 = (uint64_t)*(float *)&Buffer[116];
      v435 = (uint64_t)*(float *)&Buffer[120];
      ArgList = (uint64_t)*(float *)&Buffer[124];
      LODWORD(v564) = (uint64_t)*(float *)&Buffer[80];
      HIDWORD(v564) = (uint64_t)*(float *)&Buffer[88];
      i5 = (void *)(uint64_t)*(float *)&Buffer[84];
      v571 = (uint64_t)*(float *)&Buffer[92];
      *(uint32_t *)v568 = (uint64_t)*(float *)&Buffer[96];
      v575 = (uint64_t)*(float *)&Buffer[100];
      v576 = (uint64_t)*(float *)&Buffer[104];
      v579 = (uint64_t)*(float *)&Buffer[64];
      *(uint32_t *)netshort = (uint64_t)*(float *)&Buffer[60];
      v580 = (uint64_t)*(float *)&Buffer[68];
      v574 = (uint64_t)*(float *)&Buffer[72];
      v572 = (uint64_t)*(float *)&Buffer[76];
      v436 = (uint64_t)sub_477280(dword_99FD58, (uint64_t)*(float *)&Buffer[76] >> 32);
      v565 = v436;
      v437 = (uint64_t)sub_477260(dword_99FD58, HIDWORD(v436));
      v567 = v437;
      Block[0] = (void *)(uint64_t)sub_57A480(dword_99FD58, HIDWORD(v437));
      off_77F3FC(
        aEnumCmdpacketR_18,
        (uint16_t)v433,
        (uint16_t)v434,
        (uint16_t)v435,
        (uint16_t)ArgList,
        (uint16_t)v564,
        WORD2(v564),
        (uint16_t)i5,
        (uint16_t)v571,
        *(uint16_t *)v568,
        (uint16_t)v575,
        (uint16_t)v576,
        v579,
        *(uint32_t *)netshort,
        v580,
        v574,
        v572,
        v565,
        v567,
        Block[0]);
      sub_423200(dword_8F7B08, 61);
      sub_41C0E0(v433);
      sub_41C0E0(v434);
      sub_41C0E0(v435);
      sub_41C0E0(ArgList);
      sub_41C0E0(v564);
      sub_41C0E0(SBYTE4(v564));
      sub_41C0E0((char)i5);
      sub_41C0E0(v571);
      sub_41C0E0(v568[0]);
      sub_41C0E0(v575);
      sub_41C0E0(v576);
      sub_43B4C0(v579);
      sub_43B4C0(netshort[0]);
      sub_43B4C0(v580);
      sub_43B4C0(v574);
      sub_43B4C0(v572);
      sub_43B4C0(v565);
      sub_43B4C0(v567);
      sub_43B4C0((char)Block[0]);
      sub_423380(dword_8F7B08);
      off_77F3FC((char *)&byte_7287B4);
      return 1;
    case 50:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("keyCount %d", HIBYTE(ArgList));
      *(uint32_t *)dword_99FB70 = HIBYTE(ArgList);
      sub_432EA0("ICON_KEY", -1, 0, 0);
      return 1;
    case 51:
      HIBYTE(ArgList) = 0;
      v564 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0((char *)&v564 + 4);
      sub_404AD0(&v564);
      off_77F3FC("reason %d orgMoney %d gainMoney %d", HIBYTE(ArgList), HIDWORD(v564), (uint32_t)v564);
      if ( dword_8F7C04 != 0 )
      {
        switch ( HIBYTE(ArgList) )
        {
          case 0:
            v438 = (const char *)sub_422E70(656);
            sprintf(Format, v438);
            sub_43BEE0(Format, -13487361, 0, -1);
            break;
          case 1:
            v439 = (const char *)sub_422E70(657);
            goto LABEL_781;
          case 2:
            v440 = (const char *)sub_422E70(658);
            sprintf(Format, v440);
            sub_44E8D0(dword_8F8528, (void *)0x1B, Format, 0);
            break;
          case 3:
            v441 = (const char *)sub_422E70(659);
            sprintf(Format, v441);
            sub_44E8D0(dword_8F8528, (void *)0x1B, Format, 0);
            break;
          case 4:
            v439 = (const char *)sub_422E70(660);
LABEL_781:
            sprintf(Format, v439);
            v115 = Format;
LABEL_782:
            sub_44E8D0(dword_8F8528, (void *)0x1B, v115, 0);
            break;
          default:
            return 1;
        }
      }
      else
      {
        v442 = sub_422E70(661);
        sub_44E8D0(dword_8F8528, (void *)0x1B, v442, 1);
      }
      return 1;
    case 52:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("FriendInfoNumber %d", HIBYTE(ArgList));
      v443 = 0;
      if ( HIBYTE(ArgList) != 0 )
      {
        do
        {
          HIBYTE(v572) = 0;
          HIBYTE(v574) = 0;
          HIBYTE(v580) = 0;
          i5 = nullptr;
          v444 = (char *)sub_422E70(662);
          sub_48BCC0(&v601, 31, v444);
          sub_404A90((char *)&v572 + 3);
          sub_404A90((char *)&v574 + 3);
          sub_404A90((char *)&v580 + 3);
          sub_404AD0(&i5);
          off_77F3FC(
            "Name [%s], Level %d, Job %d, GrowType %d, Unique ID %d",
            &v601,
            HIBYTE(v572),
            HIBYTE(v574),
            HIBYTE(v580),
            i5);
          sub_47B150(&v601, HIBYTE(v572), HIBYTE(v574), HIBYTE(v580), (int)i5);
          ++v443;
        }
        while ( v443 < HIBYTE(ArgList) );
      }
      return 1;
    case 53:
      HIBYTE(ArgList) = 0;
      i5 = nullptr;
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&i5);
      off_77F3FC("ok %d myCera %d", HIBYTE(ArgList), i5);
      dword_8F7C0C = (int)i5;
      if ( (int)i5 < 0 )
      {
        off_77F3FC(aCriticalError_31, i5);
        dword_8F7C0C = 0;
      }
      return 1;
    case 54:
      sub_404A90(&ArgList);
      v446 = (char *)sub_422E70(664);
      sub_48BCC0(&v601, 31, v446);
      sub_4794F0(&v601, ArgList);
      sub_47B380(&v601, ArgList);
      return 1;
    case 55:
      v447 = (char *)sub_422E70(666);
      sub_48BCC0(&v601, 31, v447);
      sub_479520(&v601);
      sub_47B400(&v601);
      return 1;
    case 56:
      sub_404A90((char *)&ArgList + 3);
      v445 = 0;
      if ( HIBYTE(ArgList) != 0 )
      {
        do
        {
          sub_404AF0(&v601, 31);
          if ( v601 != -1 )
            sub_4794F0(v602, v601);
          ++v445;
        }
        while ( v445 < HIBYTE(ArgList) );
      }
      sub_479850(dword_8F8510);
      return 1;
    case 57:
      *(float *)&ArgList = 0.0;
      sub_404AD0(&ArgList);
      off_77F3FC("pvpExpOfWeek %d", ArgList);
      *(float *)(*((uint32_t *)dword_8F8528 + 4) + 1224) = *(float *)&ArgList;
      return 1;
    case 58:
      sub_404AD0(&ArgList);
      sub_404AD0(Block);
      v457 = (char *)sub_422E70(676);
      sub_48BCC0(&v600[31], 31, v457);
      v458 = (char *)sub_422E70(677);
      sub_48BCC0(&v601, 31, v458);
      off_77F3FC("ENUM_NOTIPACKET_GUILD_ENTER - Guild[%d] Guild_Name[%s] Name[%s]", ArgList, &v600[31], &v601);
      v459 = (const char *)sub_422E70(678);
      sprintf(Buffer, v459, &v601, &v600[31]);
      sub_43BEE0(Buffer, -6567706, 0, -1);
      if ( sub_41C1B0(dword_8F8500) != 0 )
      {
        v460 = sub_41C1B0(dword_8F8500);
        *(float *)(v460 + 120) = *(float *)&ArgList;
      }
      sub_478EA0(1);
      return 1;
    case 59:
      sub_404AD0(Block);
      sub_404AD0(&v564);
      sub_404A90((char *)&ArgList + 3);
      v454 = (char *)sub_422E70(672);
      sub_48BCC0(&v601, 31, v454);
      v455 = (char *)sub_422E70(673);
      sub_48BCC0(&v600[31], 31, v455);
      if ( HIBYTE(ArgList) != 0 )
        v456 = (const char *)sub_422E70(675);
      else
        v456 = (const char *)sub_422E70(674);
      sprintf(Buffer, v456, &v600[31], &v601);
      sub_43BEE0(Buffer, -6567706, 0, -1);
      sub_478EA0(1);
      return 1;
    case 60:
      sub_404AD0(&ArgList);
      v462 = sub_4BF1B0(ArgList);
      if ( v462 != 0 )
        sub_4BE470(v462);
      return 1;
    case 61:
      v461 = sub_422E70(679);
      sub_43BEE0(v461, -6567706, 0, -1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8514 + 12))(dword_8F8514);
      sub_44E850(11);
      if ( sub_41C1B0(dword_8F8500) != 0 )
        *(uint32_t *)(sub_41C1B0(dword_8F8500) + 120) = 0;
      return 1;
    case 64:
      sub_404A90((char *)&ArgList + 3);
      sub_404A90(&i5);
      v453 = (char *)sub_422E70(669);
      sub_48BCC0(&v601, 31, v453);
      off_77F3FC(
        "ENUM_NOTIPACKET_GUILD_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s",
        HIBYTE(ArgList),
        (uint8_t)i5,
        &v601);
      if ( HIBYTE(ArgList) != 0 )
        goto LABEL_819;
      sub_479520(&v601);
      sub_47B400(&v601);
      return 1;
    case 65:
      HIBYTE(ArgList) = 0;
      sub_404A90((char *)&ArgList + 3);
      v126 = (char *)sub_422E70(641);
      sub_48BCC0(&v601, 31, v126);
      v127 = (char *)sub_422E70(642);
      sub_48BCC0(Str, 256, v127);
      off_77F3FC("MessageType %d, name %s, MessageLength %d", HIBYTE(ArgList), &v601, strlen(Str));
      sub_43D900(Str, HIBYTE(ArgList), 0, &v601);
      return 1;
    case 66:
      sub_404AB0((char *)&v580 + 2);
      if ( HIWORD(v580) == 1 )
      {
        *(float *)&ArgList = 0.0;
        sub_404AB0(&ArgList);
        off_77F3FC((char *)&byte_7285FC, HIWORD(v580), (uint16_t)ArgList);
        v452 = (uint16_t)ArgList;
        if ( sub_50D980() < v452 )
          sub_50D920(v452);
        else
          off_77F3FC("CNGameCore.NetworkProc - ENUM_NOTIPACKET_CERA_SPECIALITEM - Capacity is too small");
        return 1;
      }
      if ( HIWORD(v580) != 2 )
      {
        off_77F3FC("CNGameCore.NetworkProc - ENUM_NOTIPACKET_CERA_SPECIALITEM - Unspecified type");
        return 1;
      }
      HIBYTE(ArgList) = -1;
      v579 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&v579);
      off_77F3FC((char *)&byte_728628, HIWORD(v580), SHIBYTE(ArgList), v579);
      if ( v579 != 0 )
      {
        v451 = *((uint32_t *)dword_8F8528 + 611);
        if ( *(uint32_t *)(v451 + 12) == 1 )
          *(uint32_t *)(v451 + 10124) = SHIBYTE(ArgList);
        sub_41C470(SHIBYTE(ArgList), 1);
        sub_41C490(SHIBYTE(ArgList), v579);
        return 1;
      }
      v552 = sub_41C4B0(SHIBYTE(ArgList));
      v449 = (const char *)sub_422E70(668);
      sprintf(OutputString, v449, v552);
      sub_43BEE0(OutputString, -6567706, 0, -1);
      v450 = HIBYTE(ArgList);
      if ( SHIBYTE(ArgList) <= 0 )
        goto LABEL_810;
      if ( SHIBYTE(ArgList) <= 4 )
      {
        sub_55E820(50000);
      }
      else
      {
        if ( HIBYTE(ArgList) != 8 )
        {
LABEL_810:
          sub_41C470(v450, 0);
          sub_41C490(SHIBYTE(ArgList), v579);
          return 1;
        }
        sub_55E820(50002);
      }
      v450 = HIBYTE(ArgList);
      goto LABEL_810;
    case 68:
      v448 = 0;
      *(float *)&ArgList = 0.0;
      i5 = nullptr;
      sub_404AB0(&ArgList);
      off_77F3FC("buyLimitGroupCount %d", (uint16_t)ArgList);
      if ( (uint16_t)ArgList != 0 )
      {
        do
        {
          sub_404AD0(&i5);
          off_77F3FC("buyLimitGroup %d", i5);
          sub_55F7B0(i5);
          ++v448;
        }
        while ( v448 < (uint16_t)ArgList );
      }
      return 1;
    case 69:
      HIBYTE(ArgList) = 0;
      i5 = nullptr;
      LODWORD(v564) = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0(&i5);
      sub_404AB0(&v564);
      off_77F3FC("isEnable %d eventIndex %d eventDuration %d", HIBYTE(ArgList), (int16_t)i5, (int16_t)v564);
      sub_41C3C0((int16_t)i5);
      LOBYTE(v463) = HIBYTE(ArgList) != 0;
      sub_41C9E0(v463);
      return 1;
    case 70:
      v464 = (char *)sub_422E70(672);
      sub_48BCC0(&v600[11], 50, v464);
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v565 + 3);
      sub_404A90((char *)&v572 + 3);
      sub_404A90((char *)&v574 + 3);
      sub_404A90((char *)&v580 + 3);
      off_77F3FC(
        "ENUM_NOTIPACKET_GUILD_INFO - %s, master:%d level:%d mark:%d members:%d establish:%d",
        &v600[11],
        HIBYTE(ArgList),
        HIBYTE(v565),
        HIBYTE(v572),
        HIBYTE(v574),
        HIBYTE(v580));
      *(uint32_t *)(dword_8F8514 + 48) = HIBYTE(ArgList);
      *(uint32_t *)(dword_8F8514 + 52) = HIBYTE(v580);
      return 1;
    case 71:
      sub_404AD0(&ArgList);
      v465 = (char *)sub_422E70(672);
      sub_48BCC0(&v600[11], 50, v465);
      v466 = (const char *)sub_422E70(1251);
      sprintf(Buffer, v466, &v600[11]);
      sub_43BEE0(Buffer, -6567706, 0, -1);
      off_77F3FC("ENUM_NOTIPACKET_GUILD_CREATE - %s(%d)", &v600[11], ArgList);
      if ( sub_41C1B0(dword_8F8500) != 0 )
      {
        v467 = sub_41C1B0(dword_8F8500);
        *(float *)(v467 + 120) = *(float *)&ArgList;
      }
      return 1;
    case 72:
      sub_404A90((char *)&ArgList + 3);
      sub_404A90(&i5);
      sub_404A90((char *)&v580 + 3);
      v468 = (char *)sub_422E70(669);
      sub_48BCC0(&v601, 31, v468);
      off_77F3FC(
        "ENUM_NOTIPACKET_MEMBER_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s",
        HIBYTE(ArgList),
        (uint8_t)i5,
        &v601);
      if ( HIBYTE(ArgList) != 0 )
      {
LABEL_819:
        sub_4794F0(&v601, (char)i5);
        sub_47B380(&v601, (char)i5);
      }
      else
      {
        sub_479520(&v601);
      }
      return 1;
    case 73:
      sub_404AB0((char *)&ArgList + 2);
      v469 = (char *)sub_422E70(669);
      sub_48BCC0(&v600[11], 50, v469);
      off_77F3FC("ENUM_NOTIPACKET_REQUEST_MEMBER_ENTER_TO_RESPONSER - from Lv.%d %s", SHIWORD(ArgList), &v600[11]);
      sub_44E8D0(dword_8F8528, (void *)0x3A, &v600[11], SHIWORD(ArgList));
      return 1;
    case 74:
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v580 + 3);
      sub_404A90((char *)&v574 + 3);
      v470 = (char *)sub_422E70(669);
      sub_48BCC0(&v600[11], 50, v470);
      if ( HIBYTE(ArgList) == 1 )
      {
        v471 = (const char *)sub_422E70((HIBYTE(v580) != 1) + 1509);
        sprintf(Buffer, v471, &v600[11]);
        sub_478F40(1);
      }
      else
      {
        v472 = (const char *)sub_422E70(1511);
        sprintf(Buffer, v472, &v600[11]);
      }
      goto LABEL_842;
    case 75:
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8518 + 12))(dword_8F8518);
      return 1;
    case 76:
      sub_404AD0(netshort);
      sub_404AB0((char *)&ArgList + 2);
      v475 = (char *)sub_422E70(669);
      sub_48BCC0(&v600[11], 50, v475);
      off_77F3FC("ENUM_NOTIPACKET_PAY_TAX_TO_UPPER - %d gold. %d fatigue", *(uint32_t *)netshort, SHIWORD(ArgList));
      if ( *(int *)netshort > 0 && sub_41C1B0(dword_8F8500) != 0 && *(uint32_t *)(sub_41C1B0(dword_8F8500) + 196) != 0 )
      {
        v476 = sub_41C1B0(dword_8F8500);
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v476 + 196) + 1260))(
          *(uint32_t *)(v476 + 196),
          1,
          *(uint32_t *)netshort,
          0,
          0,
          0,
          0,
          0,
          0);
        sub_57A3F0(*(uint32_t *)netshort);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 48))(
          **((uint32_t **)dword_8F852C + 3),
          *(uint32_t *)netshort);
        v553 = *(uint32_t *)netshort;
        v477 = (const char *)sub_422E70(1515);
        sprintf(Buffer, v477, &v600[11], v553);
      }
      if ( SHIWORD(ArgList) > 0 )
      {
        word_8F7C10 = (word_8F7C10 - HIWORD(ArgList)) & (((uint16_t)word_8F7C10 - SHIWORD(ArgList) < 0) - 1);
        sub_57A410(SHIWORD(ArgList));
        v554 = SHIWORD(ArgList);
        v478 = (const char *)sub_422E70(1527);
        sprintf(Buffer, v478, &v600[11], v554);
      }
LABEL_842:
      sub_43BEE0(Buffer, -6567706, 0, -1);
      return 1;
    case 77:
      v473 = (char *)sub_422E70(669);
      sub_48BCC0(&v600[11], 50, v473);
      off_77F3FC("ENUM_NOTIPACKET_MEMBER_SECEDE - from %s", &v600[11]);
      v474 = (const char *)sub_422E70(1513);
      sprintf(Buffer, v474, &v600[11]);
      sub_43BEE0(Buffer, -6567706, 0, -1);
      sub_478F40(1);
      return 1;
    case 78:
      *(uint32_t *)netshort = 0;
      HIBYTE(ArgList) = 0;
      i5 = nullptr;
      sub_404AB0(netshort);
      sub_404A90((char *)&v580 + 3);
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0((char *)&v574 + 2);
      sub_404AB0(&i5);
      off_77F3FC("%d, %d, %d, %d, %d", netshort[0], HIBYTE(v580), HIBYTE(ArgList), HIWORD(v574), (uint16_t)i5);
      v479 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      if ( v479 != netshort[0] )
      {
        v480 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        off_77F3FC("%d", v480);
        if ( sub_429830(*(uint32_t *)netshort) != 0 )
        {
          v481 = sub_429830(*(uint32_t *)netshort);
          sub_42FBB0(*(uint32_t *)(v481 + 192), HIBYTE(v580), HIBYTE(ArgList), HIWORD(v574), (uint16_t)i5);
          v482 = sub_429830(*(uint32_t *)netshort);
          sub_430230(*(uint32_t *)(v482 + 192));
        }
      }
      return 1;
    case 79:
      *(float *)&ArgList = 0.0;
      sub_404AB0(&ArgList);
      if ( sub_429830(ArgList) != 0 )
      {
        v483 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        if ( v483 != (uint16_t)ArgList )
        {
          v484 = sub_429830(ArgList);
          sub_42FBE0(*(uint32_t *)(v484 + 192));
        }
      }
      return 1;
    case 80:
      sub_542AD0();
      return 1;
    case 81:
      *(float *)&ArgList = 0.0;
      sub_404AB0(&ArgList);
      sub_48BCC0(&v600[19], 41, nullptr);
      off_77F3FC("%d, %s", (uint16_t)ArgList, &v600[19]);
      if ( sub_429830(ArgList) != 0 )
      {
        v485 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        if ( v485 != (uint16_t)ArgList )
        {
          sub_429830(ArgList);
          sub_42FC00(&v600[19]);
          v486 = sub_429830(ArgList);
          sub_42FBF0(*(uint32_t *)(v486 + 192));
        }
      }
      return 1;
    case 82:
      sub_404A90((char *)&ArgList + 3);
      if ( HIBYTE(ArgList) != 0 )
      {
        memset(v603, 0, sizeof(v603));
        sub_404AD0(Block);
        sub_404AB0((char *)&v580 + 2);
        sub_404AB0((char *)&v574 + 2);
        sub_404AD0((char *)&v564 + 4);
        sub_48BCC0(v603, 20, nullptr);
        sub_404AD0(&i5);
        sub_404AD0(&v564);
        (*(void (/*thiscall*/ **)(uint32_t, void *))(***((uint32_t ***)dword_8F852C + 3) + 40))(
          **((uint32_t **)dword_8F852C + 3),
          Block[0]);
        sub_541B30(HIWORD(v580), HIWORD(v574), v603, i5, v564, HIDWORD(v564));
        v555 = v564;
        v512 = v564;
        v507 = i5;
        v487 = (const char *)sub_4F2CE0(HIWORD(v580));
        off_77F3FC(
          "Sell private store item : %s, %s, %d, %d, %d, %d",
          v603,
          v487,
          v507,
          (uint32_t)v512,
          HIDWORD(v512),
          v555);
      }
      else
      {
        sub_404A90((char *)&v580 + 3);
        sub_542000(SHIBYTE(v580));
      }
      return 1;
    case 83:
      sub_404AB0((char *)&ArgList + 2);
      sub_404AD0(Block);
      v488 = sub_541A30();
      (*(void (/*thiscall*/ **)(int, uint32_t, void *))(*(uint32_t *)v488 + 68))(v488, HIWORD(ArgList), Block[0]);
      return 1;
    case 84:
      HIBYTE(v580) = 0;
      v579 = 0;
      LODWORD(v564) = 0;
      memset(&v600[19], 0, 41);
      sub_404A90((char *)&ArgList + 3);
      v489 = *(int **)(dword_8F8500 + 8);
      v490 = (void **)(dword_8F8500 + 8);
      v576 = *v489;
      for ( i5 = v489; (uint8_t)sub_4296C0(&i5) != 0; i5 = *v490 )
      {
        off_77F3FC("user_id : %d ", *(uint16_t *)(*(uint32_t *)(v576 + 16) + 4));
        sub_429780(Block, 0);
      }
      for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )
      {
        sub_404AB0(&v579);
        sub_48BCC0(&v600[19], 41, nullptr);
        sub_404A90((char *)&v572 + 3);
        sub_404A90((char *)&v574 + 3);
        sub_404A90((char *)&v580 + 3);
        sub_404AB0((char *)&v565 + 2);
        sub_404AB0(&v564);
        off_77F3FC("store_owner_id : %d", (uint16_t)v579);
        if ( sub_429830(v579) != 0 )
        {
          v491 = *(uint32_t *)(sub_429830(v579) + 192);
          if ( v491 != 0 )
          {
            sub_42FBB0(v491, HIBYTE(v574), HIBYTE(v580), SHIWORD(v565), (int16_t)v564);
            sub_430230(v491);
            if ( HIBYTE(v572) != 0 )
            {
              sub_42FC00(&v600[19]);
              sub_42FBF0(v491);
            }
          }
        }
      }
      return 1;
    case 85:
      v492 = (uint32_t *)dword_8F7C08;
      sub_404A90((char *)&v574 + 3);
      sub_42FC30(HIBYTE(v574) == 0);
      HIBYTE(v580) = 0;
      sub_404A90((char *)&ArgList + 3);
      if ( v492[162] != 0 )
        goto LABEL_877;
      if ( HIBYTE(ArgList) != 0 )
      {
        sub_431160(v492, 1);
LABEL_877:
        if ( HIBYTE(ArgList) != 0 )
        {
          v493 = *(uint32_t *)(dword_8F7A24 + 20);
          v494 = *(uint32_t *)(v493 + 100);
          v556 = (*(int (/*thiscall*/ **)(uint32_t *))(*v492 + 124))(v492);
          v525 = (*(int (/*thiscall*/ **)(uint32_t *))(*v492 + 120))(v492);
          v495 = sub_42F240(v493);
          sub_42FBB0(v492, v494, v495, v525, v556);
          sub_430230(v492);
          sub_42FBF0(v492);
          sub_541A60(1);
          for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )
          {
            sub_404AB0((char *)&v567 + 2);
            sub_404AD0(&v564);
            sub_404AB0((char *)&v565 + 2);
            sub_404AD0(Block);
            sub_404A90((char *)&v580 + 3);
            sub_404AB0((char *)&v572 + 2);
            v496 = sub_541A30();
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, void *, uint32_t, uint32_t))(*(uint32_t *)v496 + 56))(
              v496,
              HIWORD(v567),
              v564,
              HIWORD(v565),
              Block[0],
              HIBYTE(v580),
              HIWORD(v572));
          }
        }
      }
      return 1;
    case 86:
      HIBYTE(v574) = 0;
      sub_404A90((char *)&v574 + 3);
      if ( HIBYTE(v574) == 1 )
      {
        HIBYTE(v580) = 0;
        HIBYTE(ArgList) = 0;
        i5 = nullptr;
        v576 = 0;
        sub_404A90((char *)&v580 + 3);
        sub_404AB0(&i5);
        sub_404AB0(&v576);
        sub_404A90((char *)&ArgList + 3);
        off_77F3FC(
          "isSuccess %d, upgradeRank %d, serverId %d, itemIdex %d",
          HIBYTE(v580),
          HIBYTE(ArgList),
          (uint16_t)i5,
          (uint16_t)v576);
        v497 = sub_429830(i5);
        if ( v497 != 0 )
        {
          if ( HIBYTE(v580) != 0 )
          {
            v557 = sub_4F2CE0((uint16_t)v576);
            v526 = HIBYTE(ArgList);
            v513 = unknown_libname_2(v497 + 16);
            v498 = (const char *)sub_422E70(1673);
          }
          else
          {
            ++HIBYTE(ArgList);
            v557 = sub_4F2CE0((uint16_t)v576);
            v526 = HIBYTE(ArgList);
            v513 = unknown_libname_2(v497 + 16);
            v498 = (const char *)sub_422E70(1674);
          }
          sprintf(Format, v498, v513, v526, v557);
          off_77F3FC(Format);
          sub_43BEE0(Format, -6567706, 0, -1);
        }
      }
      return 1;
    case 87:
      v579 = 0;
      sub_404AB0(&v579);
      off_77F3FC("WAR RoomNumber %d", (uint16_t)v579);
      HIDWORD(v564) = 0;
      if ( (uint16_t)v579 != 0 )
      {
        do
        {
          v366 = 0;
          v581 = 0;
          v576 = 0;
          i5 = nullptr;
          HIBYTE(v574) = 0;
          HIBYTE(ArgList) = 0;
          HIBYTE(v580) = 0;
          sub_404AB0(&v576);
          sub_404A90((char *)&v574 + 3);
          sub_404A90((char *)&ArgList + 3);
          sub_404A90((char *)&v580 + 3);
          sub_404A90(&v581);
          sub_404AB0(&i5);
          off_77F3FC(
            "WAR RoomIndex %d, dungeonKind %d, levelSeparation %d, listIndex %d, RoomState %d warRoomMapIndex %d",
            (uint16_t)v576,
            HIBYTE(v574),
            HIBYTE(ArgList),
            HIBYTE(v580),
            (char)v581,
            (uint16_t)i5);
          HIBYTE(ArgList) -= dword_77F888;
          v367 = (uint32_t *)sub_49F7D0((uint16_t)v576, HIBYTE(ArgList));
          v367[18] = (char)v581;
          v367[19] = (uint16_t)i5;
          HIBYTE(v567) = 0;
          HIBYTE(v565) = 0;
          v368 = v367 + 10;
          do
          {
            HIBYTE(v572) = 0;
            LODWORD(v564) = 0;
            sub_404A90((char *)&v572 + 3);
            sub_404AB0(&v564);
            if ( HIBYTE(v572) == 0xFF )
            {
              if ( *v368 == (uint16_t)word_77F804 )
                HIBYTE(v567) = 1;
            }
            else if ( (uint16_t)v564 == (uint16_t)word_77F804 )
            {
              HIBYTE(v565) = 1;
            }
            sub_4900E0(v366++, (uint16_t)v564, HIBYTE(v572));
            ++v368;
          }
          while ( v366 < 8 );
          if ( HIBYTE(v565) != 0 )
          {
            sub_48FE80(v367);
          }
          else if ( HIBYTE(v567) != 0 )
          {
            sub_48FE80(0);
          }
          if ( v581 != 0xFF )
            sub_42C6A0(v576);
          ++HIDWORD(v564);
        }
        while ( SHIDWORD(v564) < (uint16_t)v579 );
      }
      if ( dword_9B9454 != 0 )
        sub_62E460(1);
      v369 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 10) + 20);
      *(uint8_t *)(v369 + 16) = (uint16_t)v579 != 0;
      sub_545730(*((uint32_t *)dword_8F8528 + 10));
      return 1;
    case 88:
      i5 = nullptr;
      v579 = 0;
      HIBYTE(ArgList) = 0;
      sub_404AB0(&i5);
      v375 = 0;
      if ( (uint16_t)i5 != 0 )
      {
        do
        {
          sub_404AB0(&v579);
          sub_404A90((char *)&ArgList + 3);
          off_77F3FC("WarRoomIndex %d, RoomState %d", (uint16_t)v579, SHIBYTE(ArgList));
          v376 = sub_49EDC0((uint16_t)v579, -1);
          if ( v376 != 0 )
          {
            v377 = *(uint8_t *)(v376 + 72);
            *(uint32_t *)(v376 + 72) = SHIBYTE(ArgList);
            if ( dword_99FF08 == v376 )
              sub_42F160(SHIBYTE(ArgList), 0);
            else
              sub_42C570(v579, v377, SHIBYTE(ArgList));
            if ( (HIBYTE(ArgList) == 0xFF || HIBYTE(ArgList) == 0) && dword_9B9454 != 0 )
              sub_62E460(1);
          }
          else
          {
            off_77F3FC(aCriticalError_30, (uint16_t)v579);
          }
          ++v375;
        }
        while ( v375 < (uint16_t)i5 );
      }
      return 1;
    case 89:
      v579 = 0;
      HIBYTE(ArgList) = 0;
      sub_404AB0(&v579);
      sub_404A90((char *)&ArgList + 3);
      off_77F3FC("WARRoomIndex %d, dataCount %d", (uint16_t)v579, HIBYTE(ArgList));
      v378 = sub_49EDC0((uint16_t)v579, -1);
      if ( v378 != 0 )
      {
        LODWORD(v564) = 0;
        if ( HIBYTE(ArgList) != 0 )
        {
          do
          {
            HIBYTE(v580) = 0;
            v576 = 0xFFFF;
            sub_404A90((char *)&v580 + 3);
            sub_404A90((char *)&v574 + 3);
            sub_404AB0(&v576);
            off_77F3FC("SeatIndex %d, SeatState %d, ServerId %d", HIBYTE(v580), HIBYTE(v574), (uint16_t)v576);
            v379 = false;
            HIBYTE(v572) = 0;
            if ( HIBYTE(v574) == 0xFF )
              HIBYTE(v572) = *(uint32_t *)(v378 + 4 * HIBYTE(v580) + 40) == (uint16_t)word_77F804;
            else
              v379 = (uint16_t)v576 == (uint16_t)word_77F804;
            sub_4900E0(SHIBYTE(v580), (uint16_t)v576, HIBYTE(v574));
            if ( v379 )
            {
              sub_48FE80(v378);
            }
            else if ( HIBYTE(v572) != 0 )
            {
              sub_48FE80(0);
            }
            LODWORD(v564) = v564 + 1;
          }
          while ( (int)v564 < HIBYTE(ArgList) );
        }
      }
      else
      {
        off_77F3FC(aCriticalError_30, (uint16_t)v579);
      }
      return 1;
    case 90:
      off_77F3FC((char *)&byte_728AB8);
      return 1;
    case 91:
      HIBYTE(v565) = 0;
      v576 = 0;
      sub_404A90((char *)&v565 + 3);
      sub_404AB0(&v576);
      sub_42C9A0(v4[10]);
      off_77F3FC("maxMonsterCount %d MonsterCount %d", HIBYTE(v565), (uint16_t)v576);
      v380 = v576;
      v381 = 0;
      if ( (uint16_t)v576 != 0 )
      {
        do
        {
          v571 = 0;
          i5 = nullptr;
          HIBYTE(v572) = 0;
          HIBYTE(v580) = 0;
          HIBYTE(ArgList) = 0;
          HIBYTE(v574) = 0;
          sub_404AB0(&v571);
          sub_404A90((char *)&v572 + 3);
          sub_404A90((char *)&v574 + 3);
          sub_404A90((char *)&v580 + 3);
          sub_404A90((char *)&ArgList + 3);
          sub_404AB0(&i5);
          off_77F3FC(
            "uniqueId %d type %d level %d sequence %d posSequence %d nextMonsterMakeInterval %d",
            (uint16_t)v571,
            HIBYTE(v572),
            HIBYTE(v574),
            HIBYTE(v580),
            HIBYTE(ArgList),
            (uint16_t)i5);
          sub_42E230(
            (uint16_t)v571,
            HIBYTE(v572),
            HIBYTE(v574),
            HIBYTE(v580),
            HIBYTE(ArgList),
            (uint16_t)i5);
          v380 = v576;
          ++v381;
        }
        while ( v381 < (uint16_t)v576 );
      }
      sub_42B7C0(HIBYTE(v565), v380);
      sub_42B5F0(v4[10]);
      return 1;
    case 92:
      i5 = nullptr;
      v571 = 0;
      *(uint32_t *)v568 = 0;
      v575 = 0;
      v576 = 0;
      v579 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AD0(&i5);
      sub_404AD0(&v571);
      sub_404AD0(v568);
      sub_404AD0(&v575);
      sub_404AD0(&v576);
      sub_404AD0(&v579);
      off_77F3FC(
        "myFinishPoint %d gainedSP %d gainedOriginalExp %d gainedAvatarBonusExp %d, gainedPremiumBonusExp %d, gainedMatch"
        "edChannelBonusExp %d, gainedMemberBonusExp %d",
        i5,
        HIBYTE(ArgList),
        v571,
        *(uint32_t *)v568,
        v575,
        v576,
        v579);
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 124) = i5;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 144) = v571;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 128) = *(uint32_t *)v568;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 132) = v575;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 136) = v576;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 140) = v579;
      sub_49E050(1);
      return 1;
    case 93:
      if ( a1[3] != 6 )
        off_77F3FC(aCriticalError_26);
      i5 = nullptr;
      v571 = 0;
      sub_404AB0(&i5);
      sub_404AB0(&v571);
      off_77F3FC("ItemUniqueId %d, ServerId %d", (uint16_t)i5, (uint16_t)v571);
      v339 = sub_45EBE0(289, (uint16_t)i5);
      v340 = __RTDynamicCast(v339, 0, &CNRDObject `RTTI Type Descriptor', &CNRDItemObject `RTTI Type Descriptor', 0);
      v341 = v340;
      if ( v340 != 0
        && ((*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v340 + 84))(v340, 0),
            (v342 = *(uint32_t **)(v341 + 972)) != nullptr) )
      {
        if ( (uint16_t)v571 == (uint16_t)word_77F804 )
        {
          v343 = sub_41C1B0(dword_8F8500);
          sub_484FF0(dword_8F852C);
          v344 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342) + 4);
          *(float *)&ArgList = 0.0;
          if ( v344 != 0 )
          {
            sub_404AB0(&ArgList);
            off_77F3FC("SlotIndex %d", (uint16_t)ArgList);
            v345 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 44))(v342);
            sub_4337E0(v342, v345, v343, 0);
            sub_57A360(v341);
            LODWORD(v564) = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 44))(v342);
            HIDWORD(v564) = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 36))(v342);
            sub_432EA0("ITEM_PICK", -1, 0, 0);
            v346 = (uint16_t)ArgList;
            v347 = (uint32_t *)sub_44A980((uint16_t)ArgList);
            v348 = v347;
            if ( v347 != nullptr )
            {
              v349 = *v347;
              v350 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342);
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(v349 + 60))(v348, *(uint32_t *)(v350 + 4)) != 0 )
              {
                (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v348 + 48))(v348, v564);
              }
              else
              {
                v351 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342);
                v352 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v348 + 16))(v348, *(uint32_t *)(v351 + 4));
                off_77F3FC(aErrorD_2, (uint16_t)ArgList, *(uint32_t *)(v352 + 4));
              }
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*v342 + 4))(v342, 1);
            }
            else
            {
              sub_484F40(v346, v342, 1);
              v348 = v342;
            }
            v353 = *((uint32_t *)dword_8F852C + 1);
            v354 = v353 - sub_484FA0();
            v566 = (uint32_t *)v354;
            if ( v354 <= 0 || SHIDWORD(v564) <= 0 )
            {
LABEL_336:
              sub_47CD00(dword_8F8540);
            }
            else
            {
              v355 = v354 - 1;
              v356 = v355 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v348 + 16))(v348) + 56);
              v357 = v564;
              if ( v356 + 1 < (int)v564 )
                v357 = v355 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v348 + 16))(v348) + 56) + 1;
              sub_486330((uint16_t)ArgList, v357);
              v358 = (const char *)sub_422E70(654);
              sprintf(OutputString, v358, (double)(int)v566 * 0.0099999998);
              sub_43BEE0(OutputString, -6567706, 0, -1);
            }
          }
          else
          {
            sub_404AD0(&ArgList);
            off_77F3FC("MONEY %u", ArgList);
            if ( *(float *)&ArgList != 0.0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(
                **((uint32_t **)dword_8F852C + 3),
                ArgList);
              sub_432EA0("ITEM_PICK", -1, 0, 0);
              sub_4337E0(v342, ArgList, v343, 0);
            }
          }
        }
      }
      else
      {
        off_77F3FC(aCriticalError_27);
      }
      return 1;
    case 94:
      HIBYTE(ArgList) = 0;
      v579 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404AB0(&v579);
      off_77F3FC("seatIndex %d incKc %d", HIBYTE(ArgList), (uint16_t)v579);
      v499 = dword_99FF08;
      if ( dword_99FF08 != 0 && sub_578E80(HIBYTE(ArgList)) != 0 )
      {
        *(uint32_t *)(v499 + 4 * HIBYTE(ArgList) + 80) += (uint16_t)v579;
        *(uint32_t *)(v499 + 4 * HIBYTE(ArgList) + 112) += (uint16_t)v579;
        sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
        if ( *(uint32_t *)(sub_578E80(HIBYTE(ArgList)) + 196) != 0 )
        {
          v500 = sub_578E80(HIBYTE(ArgList));
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v500 + 196)
                                                                                         + 1264))(
            *(uint32_t *)(v500 + 196),
            (uint16_t)v579,
            0,
            0,
            0,
            0,
            0);
        }
      }
      else
      {
        off_77F3FC("ENUM_NOTIPACKET_ADD_KP : getMyRoom() == NULL");
      }
      return 1;
    case 95:
      HIBYTE(ArgList) = 0;
      v581 = 0;
      v573 = 0;
      v579 = 0;
      i5 = (void *)0xFFFF;
      sub_404A90((char *)&ArgList + 3);
      sub_404A90(&v581);
      sub_404A90(&v573);
      sub_404AB0(&v579);
      sub_404AB0(&i5);
      off_77F3FC(
        "dieSeatIndex %d isLive %d isUseCoin %d addKP %d lastAttackerServerId %d",
        HIBYTE(ArgList),
        v581,
        v573,
        (uint16_t)v579,
        (uint16_t)i5);
      v382 = dword_99FF08;
      v566 = (uint32_t *)dword_99FF08;
      if ( dword_99FF08 == 0 )
      {
        off_77F3FC((char *)&byte_7289CC);
        return 1;
      }
      v571 = -1;
      LODWORD(v564) = sub_48FB60((uint16_t)i5, &v571);
      v383 = sub_578E80(HIBYTE(ArgList));
      if ( (uint32_t)v564 != 0 && v383 != 0 )
      {
        *(uint32_t *)(v382 + 4 * v571 + 80) += (uint16_t)v579;
        *(uint32_t *)(v382 + 4 * v571 + 112) += (uint16_t)v579;
        sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
        *(uint32_t *)v568 = *(uint32_t *)(v383 + 196);
        if ( *(uint32_t *)v568 != 0 )
        {
          v384 = **(uint32_t **)v568;
          v385 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v568 + 128))(*(uint32_t *)v568);
          v386 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)v568 + 124))(*(uint32_t *)v568, v385);
          v387 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)v568 + 120))(*(uint32_t *)v568, v386);
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(v384 + 1264))(
            *(uint32_t *)v568,
            (uint16_t)v579,
            0,
            1,
            v387);
        }
      }
      v388 = sub_48FD80(v382);
      v389 = v4[10];
      LODWORD(v564) = v388;
      v580 = *(uint32_t *)(v389 + 16);
      v390 = nullptr;
      *(uint32_t *)netshort = *(uint32_t *)(v580 + 104);
      *(uint32_t *)v568 = 0;
      while ( 1 )
      {
        v391 = sub_578E80(v390);
        v572 = v391;
        if ( v391 != 0 && *(uint32_t *)(v391 + 196) != 0 && v390 == (int *)HIBYTE(ArgList) )
          break;
        v390 = (int *)((char *)v390 + 1);
        if ( (int)v390 >= 8 )
        {
          *(uint32_t *)v568 = v390;
          goto LABEL_734;
        }
      }
      *(uint32_t *)v568 = v390;
      v392 = *(int **)(v572 + 196);
      if ( v581 != 1 )
      {
        sub_4B12B0(1);
        v413 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v392 + 124))(v392, 0);
        v511 = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 120))(v392, v413);
        v414 = sub_4633B0(v392);
        off_77F3FC(aS_8, v414, v511);
        if ( (int)v564 > 1 )
          sub_45F1E0(v392);
        v415 = v572 + 16;
        *(uint8_t *)(HIBYTE(ArgList) + v382 + 144) = 1;
        v548 = unknown_libname_2(v415);
        v416 = (const char *)sub_422E70(648);
        sprintf(&Destination, v416, v548);
        v412 = (void *)sub_43BEE0(&Destination, -6567706, 0, -1);
        goto LABEL_733;
      }
      if ( (uint8_t)sub_45E680(v392) != 0 )
      {
        sub_45F1E0(v392);
        if ( (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392) != 0 )
        {
          v393 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392);
          sub_45F1E0(v393);
        }
      }
      (*(void (/*thiscall*/ **)(int *))(*v392 + 1020))(v392);
      (*(void (/*thiscall*/ **)(int *, int))(*v392 + 1200))(v392, 1);
      *(uint8_t *)(HIBYTE(ArgList) + v382 + 144) = 0;
      v394 = *v392;
      v395 = *v392;
      if ( v573 == 1 )
      {
        v396 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v394 + 740))(v392, 0, 1);
        (*(void (/*thiscall*/ **)(int *, int))(v395 + 732))(v392, v396);
        v397 = *v392;
        LODWORD(v398) = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 756))(v392, 1);
      }
      else
      {
        HIDWORD(v564) = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v394 + 740))(v392, 0, 1);
        (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t))(v395 + 732))(
          v392,
          (uint64_t)((double)SHIDWORD(v564) * 0.80000001) >> 32,
          (uint64_t)((double)SHIDWORD(v564) * 0.80000001));
        v397 = *v392;
        HIDWORD(v564) = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 756))(v392, 1);
        v398 = (uint64_t)((double)SHIDWORD(v564) * 0.80000001);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v397 + 748))(v392, v398);
      v399 = v572;
      sub_45FE80(273, *(uint16_t *)(v572 + 4), v392, 0, 0);
      if ( (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392) != 0 )
      {
        v400 = *(uint16_t *)(v399 + 4);
        v401 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392);
        sub_45FE80(65, v400, v401, 0, 0);
      }
      sub_4B12B0(0);
      v402 = (*(int (/*thiscall*/ **)(int *))(*v392 + 120))(v392);
      v403 = *v392;
      v574 = v402;
      v404 = *(uint32_t *)(v580 + 44);
      HIDWORD(v564) = (*(int (/*thiscall*/ **)(int *))(v403 + 124))(v392);
      if ( SHIDWORD(v564) >= sub_425050(v404) )
        v405 = sub_425050(*(uint32_t *)(v580 + 44));
      else
        v405 = (*(int (/*thiscall*/ **)(int *))(*v392 + 124))(v392);
      v406 = *v392;
      v576 = v405;
      (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(v406 + 140))(
        v392,
        &v574,
        &v576,
        v574,
        v405,
        640,
        1,
        1);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*v392 + 112))(v392, v574, v576, 0);
      v524 = (unsigned int)v576;
      v510 = v574;
      v407 = sub_4633B0(v392);
      off_77F3FC(aS_7, v407, v510, v524);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v392 + 308))(v392) != 0
        && (uint8_t)sub_42B510(v4[10]) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v392 + 580))(
          v392,
          48001,
          1,
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
      v408 = dword_8F7C04;
      if ( (int *)dword_8F7C04 != v392 )
        goto LABEL_725;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*v392 + 560))(v392, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *))(*v392 + 564))(v392);
      if ( v573 == 1 )
      {
        sub_57A2F0(v580);
        v408 = dword_8F7C04;
LABEL_725:
        if ( v573 == 1 && v408 != 0 )
        {
          v409 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v408 + 376))(v408);
          if ( v409 == (*(int (/*thiscall*/ **)(int *))(*v392 + 376))(v392) )
            sub_57A310(v580);
        }
      }
      v547 = unknown_libname_2(v572 + 16);
      v410 = (const char *)sub_422E70(647);
      sprintf(&Destination, v410, v547);
      sub_43BEE0(&Destination, -6567706, 0, -1);
      v411 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1216))(v392);
      sub_495DA0(v411);
      sub_49C620(1, 1, 0);
      sub_49C5F0(1, 0, 0, 1500);
      v412 = sub_432EA0("COIN_INSERT", -1, 0, 0);
LABEL_733:
      LOBYTE(v412) = v581 == 0;
      (*(void (/*thiscall*/ **)(int *, void *))(*v392 + 1192))(v392, v412);
      v390 = *(int **)v568;
LABEL_734:
      HIDWORD(v564) = dword_8F7C04;
      if ( v390 == (int *)8 )
        off_77F3FC((char *)&byte_728974);
      if ( (int)v564 > 0 )
      {
        v417 = 0;
        while ( 1 )
        {
          v418 = sub_578E80(v417);
          if ( v418 != 0 )
          {
            v419 = *(uint32_t *)(v418 + 196);
            if ( v419 != 0 )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v419 + 1196))(*(uint32_t *)(v418 + 196)) != 0
                && (uint8_t)sub_45E680(v419) != 0 )
              {
                sub_45F1E0(v419);
              }
              else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 724))(dword_8F7C04) != 0 )
              {
                HIDWORD(v564) = v419;
LABEL_747:
                if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0 )
                  sub_49BDB0(1);
                else
                  sub_49BDB0(0);
LABEL_751:
                sub_424A40(HIDWORD(v564));
                return 1;
              }
            }
          }
          if ( ++v417 >= 8 )
            goto LABEL_747;
        }
      }
      sub_49BDB0(2);
      goto LABEL_751;
    case 96:
      v501 = sub_524330();
      HIBYTE(ArgList) = 0;
      HIBYTE(v580) = 0;
      *(uint32_t *)v568 = 0;
      i5 = nullptr;
      *(uint32_t *)netshort = 0;
      v579 = 0;
      v575 = 0;
      LOBYTE(v576) = 0;
      v571 = 0;
      sub_404A90((char *)&ArgList + 3);
      sub_404A90((char *)&v580 + 3);
      if ( HIBYTE(v580) == 0 )
        sub_523800(v501);
      for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )
      {
        sub_404AD0(v568);
        sub_48BCC0(&v601, 30, nullptr);
        sub_404AD0(&i5);
        sub_404AB0(netshort);
        sub_404AD0(&v579);
        sub_404AB0(&v575);
        sub_404A90(&v576);
        v502 = sub_522300((void *)netshort[0], v579, v576, 0, (uint16_t)v575, 1);
        sub_404AD0(&v571);
        sub_524B80(nullptr, *(int *)v568, v571, &v601, i5, v502);
        off_77F3FC("Mail    <> id : %d, limit : %d, name : %s, money : %d", *(uint32_t *)v568, v571, &v601, i5);
        off_77F3FC(
          " - item <> index : %d, data : %d, upgrade : %d, durability : %d",
          netshort[0],
          v579,
          (uint8_t)v576,
          (uint16_t)v575);
      }
      sub_404AB0((char *)&v574 + 2);
      v503 = SHIWORD(v574);
      *(uint32_t *)(sub_524330() + 8) = v503;
      return 1;
    case 97:
      sub_524330();
      *(float *)&ArgList = 0.0;
      i5 = nullptr;
      sub_404AD0(&ArgList);
      off_77F3FC("delete mail count : %d", ArgList);
      while ( *(float *)&ArgList != 0.0 )
      {
        sub_404AD0(&i5);
        v504 = sub_524160(i5);
        sub_523760(v504);
        --ArgList;
        off_77F3FC("deleted mail id : %d", i5);
      }
      return 1;
    case 98:
      v566 = nullptr;
      sub_404AB0(&v566);
      if ( (int16_t)v566 > 0 )
      {
        v505 = sub_422E70(2065);
        sub_43BEE0(v505, -11600063, 0, -1);
        sub_5226E0();
      }
      v506 = (int16_t)v566;
      *(uint32_t *)(sub_524330() + 4) = v506;
      return 1;
    default:
      return 1;
  }
}

