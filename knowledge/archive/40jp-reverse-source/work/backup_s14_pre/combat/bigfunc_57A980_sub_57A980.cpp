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
unsigned int /*fastcall*/ sub_57A980(uint32_t *pArg1, int nArg2, int ArgList)
{
  int v3; // eax
  uint32_t *pArg12; // edi
  char *v5; // eax
  const char *v6; // eax
  char v7; // ecx^2
  char v8; // al
  char v9; // edx^2
  int v10; // eax
  HWND v11; // esi
  const CHAR *v12; // eax
  int v14; // edi
  int pObj13; // esi
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // ebx
  int pObj36; // eax
  int pObj27; // edi
  int v27; // eax
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int pObj33; // eax
  bool v32; // cc
  int i; // edi
  int pObj28; // eax
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
  int pObj22; // esi
  int v46; // eax
  int v47; // ebx
  int pObj14; // esi
  uint32_t *v49; // eax
  int v50; // eax
  int v51; // esi
  const char *v52; // eax
  void *pMem; // eax
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
  int pObj5; // esi
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
  int pObj322; // eax
  uint32_t *v95; // esi
  char *v96; // ebx
  uint32_t *v97; // eax
  const char *v98; // eax
  int v99; // eax
  int v100; // eax
  int dword_8F850C2; // esi
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
  int pObj26; // esi
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
  int pObj9; // esi
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
  int pObj35; // eax
  int pObj4; // esi
  int v157; // eax
  int v158; // ebx
  uint32_t *v159; // edi
  int v160; // ebx
  int v161; // eax
  int v162; // edi
  int v163; // eax
  int v164; // eax
  int v165; // edx
  int pObj31; // eax
  int v167; // eax
  uint32_t *v168; // eax
  int v169; // ebx
  int v170; // eax
  int v171; // eax
  int v172; // eax
  int pObj23; // eax
  int pObj18; // esi
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
  int pObj24; // esi
  int v191; // eax
  int v192; // eax
  int v193; // edi
  int pObj15; // esi
  int v195; // eax
  int v196; // edx
  int v197; // eax
  int v198; // eax
  int pObj; // esi
  int v200; // esi
  int mm; // esi
  int v202; // eax
  int pObj20; // ecx
  int v204; // esi
  int v205; // edi
  int nn; // esi
  int v207; // eax
  int pObj6; // ecx
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
  int pObj122; // ecx
  int *v233; // eax
  int pObj323; // ebx
  int *v235; // esi
  int v236; // eax
  int v237; // edi
  int v238; // eax
  int v239; // edi
  int v240; // eax
  int v241; // eax
  int pObj8; // edi
  int v243; // ebx
  int v244; // eax
  int v245; // eax
  int v246; // eax
  int v247; // edi
  int v248; // edx
  int v249; // eax
  int v250; // edx
  int pObj10; // ecx
  int v252; // edi
  const char *v253; // eax
  int v254; // eax
  int v255; // ecx
  const char *v256; // eax
  int i2; // edi
  int v258; // eax
  int pObj16; // esi
  int v260; // eax
  int pObj2; // ecx
  uint8_t *v262; // esi
  int v263; // eax
  int v264; // eax
  uint32_t *v265; // esi
  int v266; // ebx
  int pObj30; // esi
  int v268; // eax
  int v269; // edi
  int v270; // esi
  int v271; // eax
  int pObj17; // edi
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
  int dword_99FF082; // ebx
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
  int pObj25; // eax
  int pObj252; // esi
  int v310; // esi
  int i4; // edi
  int i3; // esi
  char v313; // bl
  uint8_t v314; // al
  int v315; // ebx
  const char *v316; // eax
  int v317; // edx
  unsigned int nLen; // eax
  char *v319; // edi
  char v320; // cl
  int *v321; // ecx
  int v322; // eax
  int v323; // eax
  int pObj11; // edi
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
  int pObj34; // eax
  int pObj342; // edi
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
  int pObj326; // eax
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
  uint16_t pObj123; // ax
  int v381; // esi
  int dword_99FF084; // ebx
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
  int pObj29; // ecx
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
  int pObj7; // esi
  int v420; // eax
  int v421; // esi
  int pObj21; // ecx
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
  int pObj3; // eax
  int *v489; // eax
  void **v490; // esi
  int v491; // esi
  uint32_t *v492; // esi
  int v493; // edi
  int v494; // ebx
  int v495; // eax
  int pObj19; // eax
  int v497; // esi
  const char *v498; // eax
  int dword_99FF083; // esi
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
  int64_t pObj325; // [esp+Ch] [ebp-944h]
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
  int dword_8F7C042; // [esp+14h] [ebp-93Ch]
  int v551; // [esp+14h] [ebp-93Ch]
  int v552; // [esp+14h] [ebp-93Ch]
  int v553; // [esp+14h] [ebp-93Ch]
  int v554; // [esp+14h] [ebp-93Ch]
  int pObj324; // [esp+14h] [ebp-93Ch]
  int v556; // [esp+14h] [ebp-93Ch]
  int v557; // [esp+14h] [ebp-93Ch]
  int v558; // [esp+18h] [ebp-938h]
  int v559; // [esp+1Ch] [ebp-934h]
  char v560[60]; // [esp+24h] [ebp-92Ch] BYREF
  char v561[60]; // [esp+60h] [ebp-8F0h] BYREF
  char v562[60]; // [esp+9Ch] [ebp-8B4h] BYREF
  int pObj92; // [esp+108h] [ebp-848h] BYREF
  int64_t pObj32; // [esp+10Ch] [ebp-844h] BYREF
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
  int pObj12; // [esp+13Ch] [ebp-814h] BYREF
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
  char pBuf2[63]; // [esp+8D9h] [ebp-77h] BYREF
  char v601; // [esp+918h] [ebp-38h] BYREF
  char v602[4]; // [esp+919h] [ebp-37h] BYREF
  char pBuf[20]; // [esp+920h] [ebp-30h] BYREF
  int16_t v604; // [esp+934h] [ebp-1Ch]
  int *v605; // [esp+938h] [ebp-18h] BYREF
  void *Block[2]; // [esp+93Ch] [ebp-14h] BYREF
  int v607; // [esp+94Ch] [ebp-4h]

  // ── [段 1] 入口：从包体第 2 字节取包类型 v3，switch 分派；pArg1=主管理器（CNGameCore），ArgList=收包缓冲 ──
  //   ★ 本函数 = 服务器→客户端 NOTIFY 包分发器（调用点见 skill_load_tutorial.cpp：NOTIFY PACKET 日志后调它）
  //   pArg12=pArg1 别名（承载主管理器指针）；netshort 槽暂存它；与 ·0x583B90（COMMAND 回报分发器）成对
  Block[1] = (void *)dword_796E50;  // 数组元素写入
  v3 = *(uint8_t *)(ArgList + 1);  // v3 存调用结果
  pArg12 = pArg1;  // pArg12 复制自 pArg1
  *(uint32_t *)netshort = pArg1;  // 指针 netshort 写 pArg1
  // ── [段 2] case 0：空/握手包——仅 sub_404AF0 跳读 16 字节即返回（保活/占位） ──
  switch ( v3 )  // 按包类型 v3 分派到各 NOTIFY 处理器
  {
    case 0:  // 【case 0】包类型分支
      sub_404AF0(&pBuf[4], 16);  // 游标读 n 字节 → &pBuf[4], 16
      return 1;  // 返回 1（已处理该包）
    // ── [段 3] case 1：★ 频道与版本校验（进服第一包）—— ChannelName/TodaySeed/ServerIndex/channelIndex ──
    //   sub_422E70 = CStringManager::getStr（取本地化串）；sub_48BCC0 限量串读入；sub_404AD0/90 游标读 4/1 字节
    case 1:  // 【case 1】包类型分支
      LOBYTE(v579) = 0;  // 低字节写 v579 ← 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      pObj12 = 0;  // pObj12 复制自 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v5 = (char *)sub_422E70(620);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&Destination, 64, v5);  // 限量串读入（带回退）
      sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
      sub_404AD0(netshort);  // 游标读 4 字节 → netshort
      sub_404A90(&v579);  // 游标读 1 字节 → &v579
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      byte_99FCD0 = 99;  // 全局 byte_99FCD0 ← 99
      off_77F3FC(  // 控制台调试日志输出
        "ChannelName [%s], TodaySeed %u %u, ServerIndex %d channelIndex %d",  // 第 1 个实参：串 ChannelName [%s], TodaySeed %u %u, ServerIndex %d channelIndex %d
        &Destination,  // 第 2 个实参：地址 &Destination
        pObj12,  // 第 3 个实参
        *(uint32_t *)netshort,  // 第 4 个实参
        (uint8_t)v579,  // 第 5 个实参：单字节 v579
        HIBYTE(ArgList));  // 第 6 个实参
      //   通道号 >4 时用串 621 格式化频道名，否则查 off_7953CC 表前缀 —— 写 dword_99FCD8
      if ( (uint8_t)v579 > 4u )  // 条件判定
      {
        v6 = (const char *)sub_422E70(621);  // 存 CStringManager::getStr 取本地化串
        sprintf(dword_99FCD8, v6, &Destination);  // 格式化写入 dword_99FCD8
      }
      else
      {
        sprintf(dword_99FCD8, "%s %s", (const char *)*(&off_7953CC + (uint8_t)v579), &Destination);  // 格式化写入 dword_99FCD8
      }
      //   写 dword_8F84B0（频道信息）、dword_8F7B08+460（连接对象字段）→ sub_4BE6B0(通道号)
      dword_8F84B0 = pObj12;  // 全局 dword_8F84B0 ← pObj12
      *(uint32_t *)(dword_8F7B08 + 460) = *(uint32_t *)netshort;  // 全局 dword_8F7B08+460 ← *(uint32_t *)netshort
      sub_4BE6B0(v579);  // 模式字节设置
      //   ★ 版本四字节比对：sub_648D80/sub_648D10 取客户端版本、sub_648F10 取服务端版本，逐字节与 byte_8F85E0 比对 ──
      //   全部相等 → sub_404AF0+sub_41C2B0 收尾返回 1；不等 → MessageBoxA 串 622 + Run Error 并返回 0x80000000
      *(uint32_t *)((char *)pArg12 + 262) = 0;  // 主管理器 +262 写 0
      sub_648D80(&Buffer[52]);  // 版本信息数据 4
      v607 = 0;  // v607 复制自 0
      sub_648F10(nullptr);  // 版本信息转发
      v7 = Buffer[66];  // v7 ← 表达式
      *((uint8_t *)pArg12 + 263) = Buffer[64];  // 主管理器 +263 字节写 Buffer[64]
      v8 = Buffer[68];  // v8 ← 表达式
      v9 = Buffer[70];  // v9 ← 表达式
      *((uint8_t *)pArg12 + 262) = v7;  // 主管理器 +262 字节写 v7
      *((uint8_t *)pArg12 + 264) = v9;  // 主管理器 +264 字节写 v9
      *((uint8_t *)pArg12 + 265) = v8;  // 主管理器 +265 字节写 v8
      sub_648D40(&Buffer[52]);  // 版本信息数据 3
      off_77F3FC(  // 控制台调试日志输出
        "Client Version %d %d %d %d",  // 第 1 个实参：串 Client Version %d %d %d %d
        *((uint8_t *)pArg12 + 262),  // 第 2 个实参
        *((uint8_t *)pArg12 + 263),  // 第 3 个实参
        *((uint8_t *)pArg12 + 264),  // 第 4 个实参
        *((uint8_t *)pArg12 + 265));  // 第 5 个实参
      off_77F3FC(  // 控制台调试日志输出
        "Server Version %d %d %d %d",  // 第 1 个实参：串 Server Version %d %d %d %d
        (uint8_t)byte_8F85E0[0],  // 第 2 个实参
        (uint8_t)byte_8F85E1,  // 第 3 个实参：单字节 byte_8F85E1
        (uint8_t)byte_8F85E2,  // 第 4 个实参：单字节 byte_8F85E2
        (uint8_t)byte_8F85E3);  // 第 5 个实参：单字节 byte_8F85E3
      v10 = 0;  // v10 复制自 0
      while ( *((uint8_t *)pArg12 + v10 + 262) == byte_8F85E0[v10] )  // 循环控制
      {
        if ( ++v10 >= 4 )  // 条件判定
        {
          sub_404AF0(&pBuf[4], 16);  // 游标读 n 字节 → &pBuf[4], 16
          sub_41C2B0(&pBuf[4]);  // 进入频道请求组包
          v607 = -1;  // 局部 v607 → -1
          sub_648DD0(&Buffer[52]);  // 版本信息数据 5
          return 1;  // 返回 1（已处理该包）
        }
      }
      ShowCursor(true);  // 调用 ShowCursor
      v11 = *(HWND *)(dword_79C0A0 + 16);  // v11 存调用结果
      v12 = (const CHAR *)sub_422E70(622);  // v12 存调用结果
      MessageBoxA(v11, v12, "Run Error", 0);  // 调用 MessageBoxA
      PostQuitMessage(0);  // 调用 PostQuitMessage
      v607 = -1;  // 局部 v607 → -1
      sub_648DD0(&Buffer[52]);  // 版本信息数据 5
      return 0x80000000;  // 返回 0x80000000（已处理该包）
    // ── [段 4] case 2：★ 对象可见列表全量刷新（本函数最大 case，319 行） ──
    //   首字节 v573 = 刷新类型（0 全量 / 1 增量 / 2 清空）；v575 = 条目数，循环逐条解析
    //   每条：对象 id（sub_429830 查已有 / sub_42A100 新建）→ 写 +160/+164/+168（队伍/PVP 字段）
    case 2:  // 【case 2】包类型分支
      v573 = 0;  // v573 复制自 0
      v575 = 0;  // v575 复制自 0
      sub_404A90(&v573);  // 游标读 1 字节 → &v573
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      if ( v573 == 2 )  // v573 等于 2
      {
        sub_46D1A0(pArg12[4]);  // 选角资源数组释放与状态复位 this+64 指针数组逐项经 vt 析构
        dword_978998 = 0;  // 全局 dword_978998 ← 0
      }
      v571 = 0;  // v571 复制自 0
      if ( (uint16_t)v575 == 0 )  // 条件判定
        goto LABEL_77;  // 转到 LABEL_77
      while ( 1 )  // 循环控制
      {
        v572 = 0;  // v572 复制自 0
        sub_404AB0(&v572);  // 游标读 2 字节 → &v572
        v14 = 0;  // v14 复制自 0
        if ( v573 != 2 )  // v573 不等于 2
        {
          v14 = sub_429830(v572);  // 存 表按键查找
          if ( v14 == 0 )  // v14 等于 0
          {
            v14 = sub_42A100(v572);  // 存 CNUser 取或建
            if ( (uint16_t)v572 == (uint16_t)word_77F804 )  // 低 16 位比较 v572 == word_77F804
            {
              sub_456850(dword_8F850C);  // 队伍槽重置 4 槽 +188 解锁清空 → 自身
              if ( *((uint32_t *)dword_8F8524 + 17) == 4 )  // 条件判定
              {
                *(uint32_t *)(v14 + 160) = *((uint32_t *)dword_8F8524 + 3);  // v14+160 写 *((uint32_t *)dword_8F8524
                *(uint32_t *)(v14 + 164) = *((uint32_t *)dword_8F8524 + 89);  // v14+164 写 *((uint32_t *)dword_8F8524
                *(uint16_t *)(v14 + 168) = ntohs(*((uint16_t *)dword_8F8524 + 176));  // v14+168 写双字节 ntohs(*((uint16_t *)dwor
              }
            }
          }
        }
        //   v573==1 建对象（sub_579F90 + sub_42A3D0 + vt+1044 关联）；v573==2 清对象
        if ( v573 != 0 && v573 != 2 )  // 条件判定
        {
          if ( v573 == 1 )  // v573 等于 1
          {
            pObj13 = *(uint32_t *)(v14 + 196);  // 读 v14+196 处 4 字节
            if ( pObj13 == 0 )  // pObj13 等于 0
            {
              pObj13 = sub_579F90(*(void **)(v14 + 44));  // 存 职业分发：调 579A60
              sub_42A3D0(pObj13);  // 本机实体绑定
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 1044))(pObj13, v14 + 16);  // 虚表 +1044 调用
            }
            pObj12 = 0;  // pObj12 复制自 0
            sub_4CE550(&Buffer[48]);  // 命令记录写入包装
            sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
            v16 = sub_48BC90(&Buffer[48]);  // 存 读流游标取长度并拷贝载荷
            off_77F3FC("[%5d] Exp %d, DataSize %d", (uint16_t)v572, pObj12, v16);  // 控制台调试日志输出
            v17 = sub_41A5E0(v14 + 53);  // 存 crypt4byte 解密校验
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj13 + 1036))(pObj13, pObj12, v17);  // 虚表 +1036 调用
            (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj13 + 1048))(pObj13, &Buffer[48]);  // 虚表 +1048 调用
            v18 = *(uint32_t *)pObj13;  // v18 ← 表达式
            v19 = sub_41C210(*(uint32_t *)netshort);  // 存 状态判定
            LOBYTE(v19) = (uint8_t)v19 == 0;  // 字节提取赋值
            (*(void (/*thiscall*/ **)(int, int))(v18 + 1056))(pObj13, v19);  // 虚表 +1056 调用
            if ( *(uint8_t *)(dword_8F8500 + 16) != 0 )  // 条件判定
            {
              if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // 条件判定
              {
                v20 = *(uint32_t *)pObj13;  // v20 ← 表达式
                v21 = (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pObj13 + 740))(pObj13, 1, 0);  // 虚表 +740 调用
                (*(void (/*thiscall*/ **)(int, int))(v20 + 728))(pObj13, v21);  // 虚表 +728 调用
                v22 = *(uint32_t *)pObj13;  // v22 ← 表达式
                v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 756))(pObj13, 1);  // 虚表 +756 调用
                (*(void (/*thiscall*/ **)(int, int))(v22 + 744))(pObj13, v23);  // 虚表 +744 调用
              }
              *(uint8_t *)(dword_8F8500 + 16) = 0;  // dword_8F8500+16 写字节 0
            }
            memset(&pBuf[4], 0, 16);  // 调用 memset
            v604 = 0;  // v604 复制自 0
            v569 = 0;  // v569 复制自 0
            //   ★ 装备装载：EquipmentNumber 条循环，每条读 EquipmentType/index/seed/ext_data1/durability（串表输出）
            sub_404A90(&v569);  // 游标读 1 字节 → &v569
            off_77F3FC("EquipmentNumber %d", v569);  // 控制台调试日志输出
            v24 = 0;  // v24 复制自 0
            if ( v569 != 0 )  // v569 不等于 0
            {
              do
              {
                HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
                LOBYTE(v565) = 0;  // 低字节写 v565 ← 0
                v574 = 0;  // v574 复制自 0
                v579 = 0;  // v579 复制自 0
                v580 = 0;  // v580 复制自 0
                sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
                sub_404AB0(&v574);  // 游标读 2 字节 → &v574
                sub_404AD0(&v580);  // 游标读 4 字节 → &v580
                sub_404A90(&v565);  // 游标读 1 字节 → &v565
                sub_404AB0(&v579);  // 游标读 2 字节 → &v579
                off_77F3FC(  // 控制台调试日志输出
                  "EquipmentType %d, index %d, seed %d, ext_data1 %d, durability %d",  // 第 1 个实参：串 EquipmentType %d, index %d, seed %d, ext_data1 %d, durability %d
                  HIBYTE(ArgList),  // 第 2 个实参
                  (uint16_t)v574,  // 第 3 个实参：双字节 v574
                  v580,  // 第 4 个实参
                  (uint8_t)v565,  // 第 5 个实参：单字节 v565
                  (uint16_t)v579);  // 第 6 个实参：双字节 v579
                pObj36 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj13 + 792))(pObj13, HIBYTE(ArgList));  // 虚表 +792 调用
                //   先 sub_4E9B10 建装备描述结构，再 sub_522300 走 PO 工厂建装备对象（type!=3 时）
                pObj27 = pObj36;  // pObj27 复制自 pObj36
                if ( pObj36 != 0  // 条件判定
                  && *(uint32_t *)((v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj36 + 16))(pObj36)) + 4) == (uint16_t)v574 )  // 第 1 个实参：地址 && *(uint32_t *)((v27 = (*(int (·thiscall· **)(int))(*(uint32_t *)pObj36 + 16))(pObj36)) + 4) == (uint16_t)v574
                {
                  v28 = sub_4E9B10(v580, v565, 0, (uint16_t)v579);  // 存 与
                  v29 = *(uint32_t *)pObj27;  // v29 ← 表达式
                  v607 = 3;  // v607 复制自 3
                  (*(void (/*thiscall*/ **)(int, int))(v29 + 184))(pObj27, v28);  // 虚表 +184 调用
                  v607 = -1;  // 局部 v607 → -1
                  sub_445150(v562);  // 分发器 case 0xA 收尾：装备同步资源清理
                  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj27 + 16))(pObj27) + 32) = 0;  // 虚表 +16 调用
                }
                else
                {
                  v30 = sub_522300((void *)(uint16_t)v574, v580, v565, 0, (uint16_t)v579, 0);  // 存 ★ PO 工厂分发器
                  pObj33 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 784))(pObj13, v30);  // 虚表 +784 调用
                  if ( pObj33 != 0 )  // pObj33 不等于 0
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj33 + 4))(pObj33, 1);  // 虚表 +4 调用
                }
                v32 = ++v24 < v569;  // v32 ← 表达式
                pBuf[HIBYTE(ArgList) + 4] = 1;  // 数组元素写入
              }
              while ( v32 );  // 调用 while
            }
            //   ★ 技能装载：SkillNumber 条循环（SkillIndex/SkillLevel），空槽则 sub_45FE80 注册
            for ( i = 0; i < 18; ++i )  // 循环控制
            {
              if ( pBuf[i + 4] == 0 )  // 条件判定
              {
                if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 792))(pObj13, i) != 0 )  // 虚表 +792 调用
                {
                  pObj28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 788))(pObj13, i);  // 虚表 +788 调用
                  if ( pObj28 != 0 )  // pObj28 不等于 0
                    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj28 + 4))(pObj28, 1);  // 虚表 +4 调用
                }
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj13 + 1080))(pObj13, i);  // 虚表 +1080 调用
              }
            }
            if ( (uint16_t)v572 == (uint16_t)word_77F804 )  // 低 16 位比较 v572 == word_77F804
              sub_47CD00(dword_8F8540);  // 逐条处理型别 fld[68]==0 的条件条目：为已注册
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj13 + 1148))(pObj13);  // 虚表 +1148 调用
            //   随后 sub_47CD00(dword_8F8540) 与 18 槽遍历（+792 判定 / +792 取对象）
            v581 = 0;  // v581 复制自 0
            sub_404A90(&v581);  // 游标读 1 字节 → &v581
            off_77F3FC("SkillNumber %d", v581);  // 控制台调试日志输出
            v35 = 0;  // v35 复制自 0
            if ( v581 != 0 )  // v581 不等于 0
            {
              do
              {
                v570 = 0;  // v570 复制自 0
                HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
                sub_404A90(&v570);  // 游标读 1 字节 → &v570
                sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
                off_77F3FC("SkillIndex %d, SkillLevel %d", v570, HIBYTE(ArgList));  // 控制台调试日志输出
                (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pObj13 + 1136))(pObj13, v570, HIBYTE(ArgList));  // 虚表 +1136 调用
                ++v35;  // v35 自增
              }
              while ( v35 < v581 );  // 调用 while
            }
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj13 + 1152))(pObj13);  // 虚表 +1152 调用
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj13 + 1156))(pObj13);  // 虚表 +1156 调用
          }
          //   LABEL_75 → LABEL_77：按 v573 收尾（2 → sub_46B150 清；0 → sub_52C590+sub_49D920+sub_479850 三连刷新）
          goto LABEL_75;  // 转到 LABEL_75
        }
        HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
        v570 = 0;  // v570 复制自 0
        HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
        HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
        i5 = nullptr;  // i5 复制自 nullptr
        sub_429E30(v587);  // CNUser
        v607 = 1;  // v607 复制自 1
        v36 = (char *)sub_422E70(623);  // 存 CStringManager::getStr 取本地化串
        sub_48BCC0(&pBuf2[31], 31, v36);  // 限量串读入（带回退）
        sub_406D60(&pBuf2[31]);  // std::string 从 C 串赋值
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        v589 = HIBYTE(ArgList);  // v589 存调用结果
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        v590 = HIBYTE(ArgList);  // v590 存调用结果
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        sub_41C150(HIBYTE(ArgList));  // crypt4byte 初始化转发
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        v594 = HIBYTE(ArgList);  // v594 存调用结果
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        v592 = HIBYTE(ArgList);  // v592 存调用结果
        sub_404A90(&v570);  // 游标读 1 字节 → &v570
        v37 = 0;  // v37 复制自 0
        if ( v570 != 0 )  // v570 不等于 0
        {
          do
          {
            HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
            v566 = nullptr;  // v566 复制自 nullptr
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404AB0(&v566);  // 游标读 2 字节 → &v566
            v32 = ++v37 < v570;  // v32 ← 表达式
            v593[HIBYTE(v580)] = (uint16_t)v566;  // 数组元素写入
          }
          while ( v32 );  // 调用 while
        }
        sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
        v593[10] = HIBYTE(v574);  // 调用 HIBYTE
        sub_404AD0(&i5);  // 游标读 4 字节 → &i5
        v595 = i5;  // v595 复制自 i5
        sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
        v38 = (const char *)v597[0];  // v38 ← 表达式
        v596 = HIBYTE(v567) == 1;  // v596 ← 表达式
        if ( v597[5] < 0x10u )  // 条件判定
          v38 = (const char *)v597;  // v38 ← 表达式
        v39 = sub_41A5E0(v591);  // 存 crypt4byte 解密校验
        v40 = (const char *)v588[0];  // v40 ← 表达式
        if ( v588[5] < 0x10u )  // 条件判定
          v40 = (const char *)v588;  // v40 ← 表达式
        off_77F3FC(  // 控制台调试日志输出
          "[%5d] Name[%s], Job %d, GrowType %d, Level %d, UserState %d, PvpRank %d, Guild %d, Donkey %d, Creature %d, Creature Name [%s]",  // 第 1 个实参：串 [%5d] Name[%s], Job %d, GrowType %d, Level %d, UserState %d, PvpRank %d, Guild %d, Donkey %d, Creature %d, Creature Name [%s]
          (uint16_t)v572,  // 第 2 个实参：双字节 v572
          v40,  // 第 3 个实参
          v589,  // 第 4 个实参
          v590,  // 第 5 个实参
          v39,  // 第 6 个实参
          v592,  // 第 7 个实参
          v594,  // 第 8 个实参
          v595,  // 第 9 个实参
          HIBYTE(v567),  // 第 10 个实参
          0,  // 第 11 个实参：常量 0
          v38);  // 第 12 个实参
        if ( v14 != 0 )  // v14 不等于 0
        {
          sub_46C250(v587);  // 与
          v41 = *(int **)(v14 + 196);  // v41 存调用结果
          if ( v41 != nullptr )  // v41 不等于 nullptr
          {
            (*(void (/*thiscall*/ **)(int *, char *))(*v41 + 1044))(v41, v587);  // 虚表 +1044 调用
            v42 = sub_41A5E0(v591);  // 存 crypt4byte 解密校验
            v43 = *v41;  // 取 v41 首字段
            v44 = (*(int (/*thiscall*/ **)(int *, int))(*v41 + 1032))(v41, v42);  // 虚表 +1032 调用
            (*(void (/*thiscall*/ **)(int *, uint32_t))(v43 + 1036))(v41, *(uint32_t *)(v44 + 48));  // 虚表 +1036 调用
          }
        }
        if ( v573 != 0 )  // v573 不等于 0
        {
          if ( v573 == 2 )  // v573 等于 2
          {
            pMem = operator new(0x294u);  // pMem 存调用结果
            Block[0] = pMem;  // 数组 Block[0] ← pMem
            LOBYTE(v607) = 2;  // 低字节写 v607 ← 2
            if ( pMem != nullptr )  // pMem 不等于 nullptr
              v54 = (int *)sub_42B0F0(pMem);  // 存 CNRDVirtualCharacter
            else
              v54 = nullptr;  // v54 复制自 nullptr
            v55 = *v54;  // 取 v54 首字段
            LOBYTE(v607) = 1;  // 低字节写 v607 ← 1
            (*(void (/*thiscall*/ **)(int *, char *))(v55 + 348))(v54, v587);  // 虚表 +348 调用
            sub_46D280(v54, v587);  // 追加条目与提示阈值 this+60 向量
          }
          goto LABEL_74;  // 转到 LABEL_74
        }
        pObj22 = *(uint32_t *)(v14 + 192);  // 读 v14+192 处 4 字节
        if ( pObj22 != 0 )  // pObj22 不等于 0
          break;
        if ( (uint16_t)v572 == (uint16_t)word_77F804 )  // 低 16 位比较 v572 == word_77F804
        {
          v46 = sub_42B340(v14);  // 存 虚拟角色惰性创建
          v47 = *(uint32_t *)netshort;  // v47 ← 表达式
          pObj14 = v46;  // pObj14 复制自 v46
          sub_45FE80(18, (uint16_t)v572, v46, 0, 0);  // 对象注册
          v49 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(v47 + 20) + 104) + 40);  // v49 存调用结果
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj14 + 112))(pObj14, *v49, v49[1], 0);  // 虚表 +112 调用
          sub_45B140(*(uint32_t *)(v47 + 20));  // 刷新
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj14 + 376))(pObj14);  // 虚表 +376 调用
          sub_424A40(dword_8F7C08);  // 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
          v50 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);  // 存 频道条目组装
          v51 = v50;  // v51 复制自 v50
          if ( v50 != 0 && (uint8_t)sub_423340(v50 + 32, "[none]") != 0 )  // 条件判定
          {
            v527 = unknown_libname_2(v51 + 60);  // CRT 内部辅助调用
            v52 = (const char *)sub_422E70(1244);  // 存 CStringManager::getStr 取本地化串
            sprintf(OutputString, v52, v527);  // 格式化写入 OutputString
            sub_43BEE0(OutputString, -6567706, 0, -1);  // 【播报上屏】
          }
LABEL_66:
          sub_5603E0(v587);  // 商城对象更新
LABEL_67:
          if ( (uint16_t)v572 == (uint16_t)word_77F804 )  // 低 16 位比较 v572 == word_77F804
            sub_47BAA0(dword_8F8540);  // 开/关对账
        }
LABEL_74:
        v607 = -1;  // 局部 v607 → -1
        sub_41CBF0(v587);  // 成员析构
LABEL_75:
        if ( ++v571 >= (uint16_t)v575 )  // 条件判定
        {
          pArg12 = *(uint32_t **)netshort;  // pArg12 ← 表达式
LABEL_77:
          if ( v573 == 2 )  // v573 等于 2
          {
            sub_46B150(pArg12[4]);  // 频道栏选中恢复与提示文本 +276 标志
          }
          else if ( v573 == 0 )
          {
            if ( dword_9B9460 != 0 )  // dword_9B9460 不等于 0
              sub_632D40();  // 推荐用户列表重建
            sub_52C590(*((uint32_t *)dword_8F8528 + 8));  // 房间 UI 重置
            v56 = *((uint32_t *)dword_8F8528 + 9);  // v56 存调用结果
LABEL_105:
            sub_49D920(v56);  // 房间列表刷新
            sub_479850(dword_8F8510);  // 遍历 180 字节条目表做名次/位置统计
            sub_479850(dword_8F8514);  // 遍历 180 字节条目表做名次/位置统计
            sub_479850(dword_8F8518);  // 遍历 180 字节条目表做名次/位置统计
          }
          return 1;  // 返回 1（已处理该包）
        }
      }
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj22 + 348))(pObj22, v587);  // 虚表 +348 调用
      if ( dword_8F7C08 == pObj22  // 条件判定
        && v14 == sub_41C1B0(dword_8F8500)  // 第 1 个实参：地址 && v14 == sub_41C1B0(dword_8F8500
        && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 611) + 12) == 1 )  // 第 1 个实参：地址 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 611) + 12) == 1
      {
        goto LABEL_66;  // 转到 LABEL_66
      }
      goto LABEL_67;  // 转到 LABEL_67
    // ── [段 5] case 3：ServerId/UserState 同步 —— 写目标对象 +68（状态位）后刷新大厅 UI ──
    //   sub_429830 取对象 → +68=UserState → sub_52C590/sub_49D920 大厅模块刷新；UserState!=0 且场景==1 时 sub_45F1E0
    case 3:  // 【case 3】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v575 = 0;  // v575 复制自 0
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("ServerId %d, UserState %d", (uint16_t)v575, HIBYTE(ArgList));  // 控制台调试日志输出
      v57 = sub_429830(v575);  // 存 表按键查找
      if ( v57 != 0 )  // v57 不等于 0
      {
        *(uint32_t *)(v57 + 68) = HIBYTE(ArgList);  // v57+68 写 HIBYTE(ArgList)
        sub_52C590(*((uint32_t *)dword_8F8528 + 8));  // 房间 UI 重置
        sub_49D920(*((uint32_t *)dword_8F8528 + 9));  // 房间列表刷新
        if ( HIBYTE(ArgList) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // 条件判定
        {
          v58 = *(uint32_t *)(v57 + 192);  // 读 v57+192 处 4 字节
          if ( v58 != 0 )  // v58 不等于 0
            sub_45F1E0(v58);  // 对象注销/退场
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 6] case 4：疲劳值（Stamina）恢复 —— vt+1060 写体力，pArg12[3]==1 时 vt+1056 追加 ──
    //   播报 STAMINA_RECOVER（string 表）
    case 4:  // 【case 4】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("Stamina %d", HIBYTE(ArgList));  // 控制台调试日志输出
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1060))(dword_8F7C04, HIBYTE(ArgList));  // 虚表 +1060 调用
        if ( pArg12[3] == 1 )  // 条件判定
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);  // 虚表 +1056 调用
        if ( HIBYTE(ArgList) == 100 )  // ArgList 高字节 == 100
          sub_432EA0("STAMINA_RECOVER", -1, 0, 0);  // 音效播放包装
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 7] case 5：副本选择回报（DungeonIndex/DungeonDifficulty）—— sub_41A5E0 crypt4byte 校验 + 界面刷新 ──
    case 5:  // 【case 5】包类型分支
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("Number %d", (uint16_t)v579);  // 控制台调试日志输出
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v566 = nullptr;  // v566 复制自 nullptr
      if ( (uint16_t)v579 != 0 )  // 条件判定
      {
        do
        {
          sub_404AB0(netshort);  // 游标读 2 字节 → netshort
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          off_77F3FC("DungeonIndex %d, DungeonDifficulty %d", netshort[0], HIBYTE(ArgList));  // 控制台调试日志输出
          if ( pArg12[3] == 3 )  // 条件判定
          {
            v59 = HIBYTE(ArgList);  // v59 存调用结果
            if ( v59 > sub_472F90(netshort[0]) )  // 条件判定
            {
              v60 = sub_476B60(netshort[0]);  // 存 选区角色数据查找
              sub_57A2D0(v60, v59);  // 字符串小桩
            }
          }
          sub_4896B0(netshort[0], HIBYTE(ArgList));  // 全局键表 dword_99FBA4 建键写值 取键 nArg1 的载荷
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < (uint16_t)v579 );  // 调用 while
      }
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 11) + 16) == 1 )  // 条件判定
      {
        sub_41C1B0(dword_8F8500);  // 按全局键 word_77F804 查表取对象
        v61 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        sub_41A5E0(v61 + 53);  // crypt4byte 解密校验
        sub_546E10(*((uint32_t *)dword_8F8528 + 11));  // 引导步骤推进
        v62 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        v528 = *(uint32_t *)(v62 + 44);  // 读 v62+44 处 4 字节
        v63 = unknown_libname_2(v62 + 16);  // CRT 内部辅助调用
        sub_48BA80(v63, v528);  // 控制台输出 「CH %s %s %d %d「
        sub_48B970(dword_8F8544);  // 216 项开关表读盘并逐项下发
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 8] case 6：ServerId 回报 —— 仅 sub_429FC0 标记 ──
    case 6:  // 【case 6】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      off_77F3FC("ServerId %d", (uint16_t)ArgList);  // 控制台调试日志输出
      pObj5 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 12) + 8);  // pObj5 存调用结果
      if ( pObj5 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 40))(pObj5, 18) != 0 )  // 虚表 +40 调用
      {
        v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 52))(pObj5);  // 虚表 +52 调用
        if ( v65 == (uint16_t)ArgList )  // 条件判定
          sub_525740(*((uint32_t *)dword_8F8528 + 12));  // 辅助
      }
      sub_429FC0(ArgList);  // 玩家槽位清除
      sub_52C590(*((uint32_t *)dword_8F8528 + 8));  // 房间 UI 重置
      v56 = *((uint32_t *)dword_8F8528 + 9);  // v56 存调用结果
      goto LABEL_105;  // 转到 LABEL_105
    // ── [段 9] case 7：P2P 请求（PeerRequestType/ServerId/data）—— sub_41C1B0 查当前管理器 ──
    case 7:  // 【case 7】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v575 = 0;  // v575 复制自 0
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&v579);  // 游标读 4 字节 → &v579
      off_77F3FC("PeerRequestType %d, ServerId %d, data %d", HIBYTE(ArgList), (uint16_t)v575, v579);  // 控制台调试日志输出
      v66 = sub_429830(v575);  // 存 表按键查找
      if ( v66 != 0 )  // v66 不等于 0
      {
        if ( HIBYTE(ArgList) == 0 )  // ArgList 高字节 == 0
        {
          v67 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
          sub_45DB20(dword_8F8524, v67);  // NAT 类型探测
          *(uint32_t *)(v66 + 180) = v579;  // v66+180 写 v579
        }
        sub_44E8D0(dword_8F8528, (void *)0x1D, v66, HIBYTE(ArgList));  // 对象池借出
        if ( HIBYTE(ArgList) == 1 )  // ArgList 高字节 == 1
          *(uint32_t *)(v66 + 176) = v579;  // v66+176 写 v579
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 10] case 8：P2P 应答（ServerId/PeerRequestType/Data）──
    case 8:  // 【case 8】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v575 = 0;  // v575 复制自 0
      sub_404AB0(netshort);  // 游标读 2 字节 → netshort
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&v575);  // 游标读 4 字节 → &v575
      off_77F3FC("ServerId %d, PeerRequestType %d, Data %d", netshort[0], HIBYTE(ArgList), v575);  // 控制台调试日志输出
      v68 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
      memset(Buffer, 0, sizeof(Buffer));  // 调用 memset
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        if ( HIBYTE(ArgList) == 1 )  // ArgList 高字节 == 1
        {
          v70 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
          v530 = unknown_libname_2(v70 + 16);  // CRT 内部辅助调用
          v71 = (const char *)sub_422E70(625);  // 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v71, v530);  // 格式化写入 Buffer
          *(uint32_t *)(v68 + 176) = v575;  // v68+176 写 v575
          sub_4844B0(dword_8F8538);  // 技能槽记录初始化
          sub_57A380(netshort[0]);  // 13 行小函数
          sub_44BBA0(2, 0);  // 窗口显示切换
        }
      }
      else
      {
        v529 = unknown_libname_2(v68 + 16);  // CRT 内部辅助调用
        v69 = (const char *)sub_422E70(624);  // 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v69, v529);  // 格式化写入 Buffer
      }
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      return 1;  // 返回 1（已处理该包）
    // ── [段 11] case 9：★ 队伍信息全量（PartyInfoNumber/PartyIndex/InfoType/Title/MemberMax，242 行） ──
    //   子 switch(HIBYTE) 分 0/1/2/3/4..8 等 InfoType；达到退出条件时播 @@UDP STOP - ENUM_NOTIPACKET_PARTY_INFO 1
    //   并行处理队伍成员表（sub_429830 取成员对象、sub_45F1E0 定位）、sub_406D60 赋串、sub_422E70 取本地化串
    case 9:  // 【case 9】包类型分支
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("PartyInfoNumber %d", (uint16_t)v579);  // 控制台调试日志输出
      v572 = 0;  // v572 复制自 0
      if ( (uint16_t)v579 == 0 )  // 条件判定
        goto LABEL_365;  // 转到 LABEL_365
      while ( 2 )  // 循环控制
      {
        HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
        v574 = 0;  // v574 复制自 0
        sub_404AB0(&v574);  // 游标读 2 字节 → &v574
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        off_77F3FC("PartyIndex %d, InfoType %d", (uint16_t)v574, HIBYTE(ArgList));  // 控制台调试日志输出
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
          v72 = sub_4569F0(v574);  // 存 队员槽查询 472E30 查键命中取节点 +16 值，未命中 0。
        else
          v72 = sub_456EB0((void *)(uint16_t)v574);  // 存 队伍条目取或建 472E30 命中即回；否则 new 0x40 走 456C70 → 456DF0 插入。
        v73 = (uint32_t *)v72;  // v73 ← 表达式
        if ( v72 == 0 )  // v72 等于 0
        {
LABEL_365:
          if ( dword_9B9460 != 0 )  // dword_9B9460 不等于 0
            sub_632D40();  // 推荐用户列表重建
          if ( dword_9B9458 != 0 )  // dword_9B9458 不等于 0
            sub_6312F0();  // 组队列表重建
          return 1;  // 返回 1（已处理该包）
        }
        v74 = *(uint32_t **)(sub_41C1B0(dword_8F8500) + 184);  // v74 存调用结果
        v75 = HIBYTE(ArgList);  // v75 存调用结果
        HIBYTE(v580) = v74 == v73;  // 字节提取赋值
        if ( HIBYTE(ArgList) <= 1u )  // 条件判定
        {
          Destination = 0;  // Destination 复制自 0
          memset(pBuf2, 0, sizeof(pBuf2));  // 调用 memset
          v581 = 0;  // v581 复制自 0
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          sub_404A90(&v581);  // 游标读 1 字节 → &v581
          if ( v581 == 0 )  // v581 等于 0
          {
            v76 = (char *)sub_422E70(626);  // 存 CStringManager::getStr 取本地化串
            sub_48BCC0(&Destination, 64, v76);  // 限量串读入（带回退）
          }
          sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
          off_77F3FC("TitleIndex %d, Title[%s], MemberMax %d", v581, &Destination, HIBYTE(v567));  // 控制台调试日志输出
          v73[2] = v581;  // 数组 v73[2] ← v581
          sub_406D60(&Destination);  // std::string 从 C 串赋值
          v73[15] = HIBYTE(v567);  // 调用 HIBYTE
          v75 = HIBYTE(ArgList);  // v75 存调用结果
        }
        if ( v75 == 0 || v75 == 2 )  // 条件判定
        {
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          v77 = &v605;  // v77 ← 表达式
          for ( j = 4; j != 0; --j )  // 循环控制
          {
            sub_404AB0(v77);  // 游标读 2 字节 → v77
            v77 = (int **)((char *)v77 + 2);  // v77 存调用结果
          }
          sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
          off_77F3FC(  // 控制台调试日志输出
            "ServerId %d %d %d %d MasterSeatIndex %d",  // 第 1 个实参：串 ServerId %d %d %d %d MasterSeatIndex %d
            (uint16_t)v605,  // 第 2 个实参：双字节 v605
            HIWORD(v605),  // 第 3 个实参
            LOWORD(Block[0]),  // 第 4 个实参
            HIWORD(Block[0]),  // 第 5 个实参
            HIBYTE(v567));  // 第 6 个实参
          for ( k = 0; k < 4; ++k )  // 循环控制
            sub_56A6B0(k, *((uint16_t *)&Block[-1] + k));  // 频道对象辅助 2
          v73[14] = HIBYTE(v567);  // 调用 HIBYTE
          v75 = HIBYTE(ArgList);  // v75 存调用结果
        }
        if ( v75 == 3 )  // v75 等于 3
        {
          for ( m = 0; m < 4; ++m )  // 循环控制
            sub_56A6B0(m, 0xFFFF);  // 频道对象辅助 2
        }
        v81 = *(uint32_t **)(sub_429830((uint16_t)word_77F804) + 184);  // v81 存调用结果
        if ( HIBYTE(v580) != 0 )  // v580 高字节 != 0
        {
          if ( v81 != v73 )  // v81 不等于 v73
          {
            if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // 条件判定
            {
              sub_43BB10(0, 1);  // 组件显隐置位 【置位】置 this + 4×pArg2 + 28 所指组件的 +17 = pszArg3 并返回索引。
              sub_43BB10(1, 0);  // 组件显隐置位 【置位】置 this + 4×pArg2 + 28 所指组件的 +17 = pszArg3 并返回索引。
              sub_43BA20(0);  // tab 切换
              sub_43B880(0);  // 面板索引条件设定 【条件设定】nArg2=1 需玩家对象
            }
            if ( dword_9B9458 != 0 )  // dword_9B9458 不等于 0
              sub_631630(0);  // 组队列表刷新入口
            v82 = *(uint32_t *)(*(uint32_t *)netshort + 12);  // v82 存调用结果
            if ( (v82 == 3 || v82 == 2)  // 条件判定
              && *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16) + 104) != 0 )  // 第 1 个实参：地址 && *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16) + 104) != 0
            {
              for ( n = 16; n < 32; n += 4 )  // 循环控制
              {
                v84 = *(uint32_t *)(n + dword_8F850C);  // v84 存调用结果
                if ( v84 != 0 && v84 != sub_429830((uint16_t)word_77F804) )  // 条件判定
                  sub_45F1E0(*(uint32_t *)(v84 + 196));  // 对象注销/退场
              }
            }
            off_77F3FC("@@UDP STOP - ENUM_NOTIPACKET_PARTY_INFO 1");  // 控制台调试日志输出
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);  // 虚表 +152 调用
            sub_456850(dword_8F850C);  // 队伍槽重置 4 槽 +188 解锁清空 → 自身
            if ( HIBYTE(ArgList) == 3 )  // ArgList 高字节 == 3
              v85 = sub_422E70(627);  // 存 CStringManager::getStr 取本地化串
            else
              v85 = sub_422E70(628);  // 存 CStringManager::getStr 取本地化串
            sub_43BEE0(v85, -6567706, 0, -1);  // 【播报上屏】
            sub_432EA0("PARTY_LEAVE", -1, 0, 0);  // 音效播放包装
            goto LABEL_202;  // 转到 LABEL_202
          }
        }
        else
        {
          if ( v81 != v73 )  // v81 不等于 v73
            goto LABEL_202;  // 转到 LABEL_202
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // 条件判定
          {
            sub_43BB10(0, 1);  // 组件显隐置位 【置位】置 this + 4×pArg2 + 28 所指组件的 +17 = pszArg3 并返回索引。
            sub_43BB10(1, 1);  // 组件显隐置位 【置位】置 this + 4×pArg2 + 28 所指组件的 +17 = pszArg3 并返回索引。
          }
          if ( dword_9B9458 != 0 )  // dword_9B9458 不等于 0
            sub_631630(1);  // 组队列表刷新入口
        }
        v575 = sub_456390(0);  // 存 座位号查询
        v571 = sub_429830((uint16_t)word_77F804);  // 存 表按键查找
        v86 = 0;  // v86 复制自 0
        v568[0] = 0;  // 数组 v568[0] ← 0
        v87 = (uint16_t *)(v73 + 10);  // v87 存调用结果
        i5 = (void *)(16 - (uint32_t)&pBuf[4]);  // i5 存调用结果
        do
        {
          v88 = *v87;  // 取 v87 首字段
          *(uint32_t *)&pBuf[4 * v86 + 4] = *(uint32_t *)&pBuf[(uint32_t)i5 + 4 * v86 + dword_8F850C + 4];  // dword_8F850C＝房间/席位表
          sub_456340(v86++, v88);  // 槽位绑定
          v87 += 2;
        }
        while ( v86 < 4 );  // 调用 while
        v89 = sub_456390(0);  // 存 座位号查询
        v531 = v73[14];  // v531 ← 表达式
        pObj12 = v89;  // pObj12 复制自 v89
        sub_456460(v531);  // 本地座位号设置 写 +8；dword_8F7A24+12 == 2 时联动 4542A0 按钮刷新。
        if ( v89 >= 2 )  // 条件判定
        {
          v90 = sub_456420(dword_8F850C);  // 存 座位查找
          off_77F3FC("@@UDP START - ENUM_NOTIPACKET_PARTY_INFO seatIndex %d /// 1", v90);
          v91 = *(uint32_t *)dword_8F8520;  // v91 ← 表达式
          v92 = sub_456420(dword_8F850C);  // 存 座位查找
          (*(void (/*thiscall*/ **)(int, int))(v91 + 148))(dword_8F8520, v92);  // 虚表 +148 调用
        }
        v566 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16) + 104);  // v566 存调用结果
        v93 = 0;  // v93 复制自 0
        pObj322 = 564 - (uint32_t)&pBuf[4];  // pObj322 ← 表达式
        HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
        LODWORD(pObj32) = 564 - (uint32_t)&pBuf[4];
        do
        {
          v95 = *(uint32_t **)&pBuf[4 * v93 + 4];  // v95 ← 表达式
          if ( v95 != nullptr )  // v95 不等于 nullptr
          {
            v96 = &pBuf[4 * v93 + 4 + pObj322];  // v96 ← 表达式
            if ( v95 != *(uint32_t **)&v96[dword_8F850C - 548] )  // 条件判定
            {
              if ( v95[10] < 0x10u )  // 条件判定
                v97 = v95 + 5;
              else
                v97 = (uint32_t *)v95[5];  // v97 ← 表达式
              v532 = v97;  // v532 复制自 v97
              v98 = (const char *)sub_422E70(629);  // 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v98, v532);  // 格式化写入 Buffer
              sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
              if ( HIBYTE(v580) == 0 )  // v580 高字节 == 0
              {
                sub_432EA0("PARTY_LEAVE", -1, 0, 0);  // 音效播放包装
                HIBYTE(v580) = 1;  // 高字节写 v580 ← 1
              }
              if ( v566 != nullptr )  // v566 不等于 nullptr
              {
                v99 = *(uint32_t *)(*(uint32_t *)netshort + 12);  // v99 存调用结果
                if ( v99 == 3 || v99 == 2 )  // 条件判定
                {
                  v100 = *((uint32_t *)dword_8F8528 + 609);  // v100 存调用结果
                  if ( *(uint32_t *)(v100 + 4) != 0 )  // 条件判定
                    *(uint32_t *)&v96[v100] = -1;
                  sub_45F1E0(v95[49]);  // 对象注销/退场
                }
              }
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, v93);  // 虚表 +104 调用
              off_77F3FC("@@REMOVE PEER");  // 控制台调试日志输出
              pObj322 = pObj32;  // pObj322 复制自 pObj32
            }
          }
          ++v93;  // v93 自增
        }
        while ( v93 < 4 );  // 调用 while
        if ( v575 == 1 && pObj12 >= 2 )  // 条件判定
        {
          dword_8F850C2 = dword_8F850C;  // 全局 dword_8F850C2 ← dword_8F850C
          v102 = sub_456480(dword_8F850C) == -1 ? 0 : *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // 存 座位号
          if ( v102 != v571 )  // v102 不等于 v571
            v568[0] = 1;  // 数组 v568[0] ← 1
        }
        v103 = 0;  // v103 复制自 0
        for ( ii = 0; ii < 4; ++ii )  // 循环控制
        {
          v105 = *(uint32_t *)&pBuf[(uint32_t)i5 + 4 * ii + dword_8F850C + 4];  // v105 ← 表达式
          if ( v105 != 0 && v105 != v571 && v105 != *(uint32_t *)&pBuf[4 * ii + 4] )  // 条件判定
          {
            if ( *(uint32_t *)(v105 + 40) < 0x10u )  // 条件判定
              v106 = v105 + 20;
            else
              v106 = *(uint32_t *)(v105 + 20);  // 读 v105+20 处 4 字节
            v533 = v106;  // v533 复制自 v106
            v107 = (const char *)sub_422E70(630);  // 存 CStringManager::getStr 取本地化串
            sprintf(Buffer, v107, v533);  // 格式化写入 Buffer
            sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
            if ( v103 == 0 )  // v103 等于 0
            {
              sub_432EA0("PARTY_JOIN", -1, 0, 0);  // 音效播放包装
              v103 = 1;  // v103 复制自 1
            }
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 100))(  // 虚表 +100 调用
              dword_8F8520,  // 第 1 个实参
              ii,  // 第 2 个实参
              v105,  // 第 3 个实参
              *(uint32_t *)v568,  // 第 4 个实参
              1);  // 第 5 个实参：常量 1
          }
        }
        if ( dword_9B9458 != 0 )  // dword_9B9458 不等于 0
          sub_630750();  // 组队列表页绘制
        if ( v575 > 1 && pObj12 == 1 && *(uint32_t *)(*(uint32_t *)netshort + 12) == 1 )  // 条件判定
          sub_44E8D0(dword_8F8528, (void *)0x2C, 0, 0);  // 对象池借出
LABEL_202:
        if ( HIBYTE(ArgList) == 3 )  // ArgList 高字节 == 3
          sub_456D70(v574);  // 队员移除 472E30 定位 → 4 槽 +184 反查清空
        if ( ++v572 >= (uint16_t)v579 )  // 条件判定
          goto LABEL_365;  // 转到 LABEL_365
        continue;
      }
    // ── [段 12] case 10：★ 队伍席位/离队（SeatIndex/WalkoutType）—— 子 switch 0/1/2/3/7/8 分处置 ──
    //   0/1 → 取席位对象并比对当前管理器；2 → 组队界面刷新（串 627/628）
    case 10:  // 【case 10】包类型分支
      v581 = 0;  // v581 复制自 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90(&v581);  // 游标读 1 字节 → &v581
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("SeatIndex %d, WalkoutType %d", v581, HIBYTE(ArgList));  // 控制台调试日志输出
      switch ( HIBYTE(ArgList) )
      {
        case 0:  // 【case 0】包类型分支
        case 1:  // 【case 1】包类型分支
          v108 = *(uint32_t *)(dword_8F850C + 4 * v581 + 16);  // v108 存调用结果
          if ( v108 == 0 )  // v108 等于 0
            goto LABEL_219;  // 转到 LABEL_219
          if ( v108 == sub_41C1B0(dword_8F8500) )  // 条件判定
          {
            if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
              v109 = sub_422E70(632);  // 存 CStringManager::getStr 取本地化串
            else
              v109 = sub_422E70(631);  // 存 CStringManager::getStr 取本地化串
            goto LABEL_211;  // 转到 LABEL_211
          }
          v110 = v108 + 16;
          if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
          {
            v535 = unknown_libname_2(v110);  // CRT 内部辅助调用
            v112 = (const char *)sub_422E70(634);  // 存 CStringManager::getStr 取本地化串
            goto LABEL_217;  // 转到 LABEL_217
          }
          v534 = unknown_libname_2(v110);  // CRT 内部辅助调用
          v111 = (const char *)sub_422E70(633);  // 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v111, v534);  // 格式化写入 Buffer
          if ( (int)sub_456390(0) > 2 )  // 条件判定
            goto LABEL_218;  // 转到 LABEL_218
          sub_43BD50(0, Buffer, -6567706, 0, -1);  // 聊天行插入 【聊天行插入】pArg2 为频道/窗口号：等于 4 时以 +96 行池基线
          break;
        case 2:  // 【case 2】包类型分支
        case 3:  // 【case 3】包类型分支
          if ( dword_99FEC0 != 0 && (v113 = sub_48F690(v581)) != 0 )  // 条件判定
          {
            if ( v113 == sub_41C1B0(dword_8F8500) )  // 条件判定
            {
              if ( HIBYTE(ArgList) == 2 )  // ArgList 高字节 == 2
                v109 = sub_422E70(635);  // 存 CStringManager::getStr 取本地化串
              else
                v109 = sub_422E70(636);  // 存 CStringManager::getStr 取本地化串
LABEL_211:
              sub_44E8D0(dword_8F8528, (void *)0x1B, v109, 0);  // 对象池借出
            }
            else
            {
              v114 = v113 + 16;
              if ( HIBYTE(ArgList) == 2 )  // ArgList 高字节 == 2
              {
                v536 = unknown_libname_2(v114);  // CRT 内部辅助调用
                v514 = (const char *)sub_422E70(637);  // 存 CStringManager::getStr 取本地化串
                sprintf(Buffer, v514, v536);  // 格式化写入 Buffer
              }
              else
              {
                v535 = unknown_libname_2(v114);  // CRT 内部辅助调用
                v112 = (const char *)sub_422E70(638);  // 存 CStringManager::getStr 取本地化串
LABEL_217:
                sprintf(Buffer, v112, v535);  // 格式化写入 Buffer
              }
LABEL_218:
              sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
            }
          }
          else
          {
LABEL_219:
            off_77F3FC(aCriticalError_16);  // 控制台调试日志输出
          }
          break;
        case 4:  // 【case 4】包类型分支
        case 5:  // 【case 5】包类型分支
        case 6:  // 【case 6】包类型分支
        case 7:  // 【case 7】包类型分支
        case 8:  // 【case 8】包类型分支
          v115 = nullptr;  // v115 复制自 nullptr
          switch ( HIBYTE(ArgList) )
          {
            case 4:  // 【case 4】包类型分支
              v116 = sub_422E70(1935);  // 存 CStringManager::getStr 取本地化串
              sub_44E8D0(dword_8F8528, (void *)0x1B, v116, 0);  // 对象池借出
              break;
            case 5:  // 【case 5】包类型分支
              v117 = sub_422E70(1936);  // 存 CStringManager::getStr 取本地化串
              sub_44E8D0(dword_8F8528, (void *)0x1B, v117, 0);  // 对象池借出
              break;
            case 6:  // 【case 6】包类型分支
              v118 = sub_422E70(1937);  // 存 CStringManager::getStr 取本地化串
              sub_44E8D0(dword_8F8528, (void *)0x1B, v118, 0);  // 对象池借出
              break;
            case 7:  // 【case 7】包类型分支
              v119 = sub_422E70(1938);  // 存 CStringManager::getStr 取本地化串
              sub_44E8D0(dword_8F8528, (void *)0x1B, v119, 0);  // 对象池借出
              break;
            case 8:  // 【case 8】包类型分支
              v120 = sub_422E70(1939);  // 存 CStringManager::getStr 取本地化串
              sub_44E8D0(dword_8F8528, (void *)0x1B, v120, 0);  // 对象池借出
              break;
            default:
              goto LABEL_782;  // 转到 LABEL_782
          }
          break;
        default:
          return 1;  // 返回 1（已处理该包）
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 13] case 11：★ 用户/网络列表（UserNumber + ServerId/LocalIp/PublicIp/Port）—— P2P 拓扑下发 ──
    //   子 switch(HIBYTE) 0..4 处理；sub_42A380 设置对端地址
    case 11:  // 【case 11】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("UserNumber %d", HIBYTE(ArgList));  // 控制台调试日志输出
      v566 = nullptr;  // v566 复制自 nullptr
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        do
        {
          v575 = 0;  // v575 复制自 0
          *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
          pObj12 = 0;  // pObj12 复制自 0
          v579 = 0;  // v579 复制自 0
          i5 = nullptr;  // i5 复制自 nullptr
          sub_404AB0(&v575);  // 游标读 2 字节 → &v575
          sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
          sub_404AD0(&v579);  // 游标读 4 字节 → &v579
          sub_404AB0(netshort);  // 游标读 2 字节 → netshort
          sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
          sub_404A90(&i5);  // 游标读 1 字节 → &i5
          sub_404AD0((char *)&pObj32 + 4);  // 游标读 4 字节 → (char *)&pObj32 + 4
          off_77F3FC("ServerId %d, LocalIp %d, PublicIp %d, Port %d", (uint16_t)v575, pObj12, v579, netshort[0]);  // 控制台调试日志输出
          v121 = sub_429830(v575);  // 存 表按键查找
          if ( v121 != 0 )  // v121 不等于 0
          {
            *(uint32_t *)(v121 + 160) = pObj12;  // v121+160 写 pObj12
            *(uint32_t *)(v121 + 164) = v579;  // v121+164 写 v579
            *(uint16_t *)(v121 + 168) = ntohs(netshort[0]);  // v121+168 写双字节 ntohs(netshort[0])
            *(uint32_t *)(v121 + 8) = pObj32;  // v121+8 写 pObj32
            *(uint32_t *)(v121 + 172) = i5;  // v121+172 写 i5
            *(uint32_t *)(v121 + 12) = HIDWORD(pObj32);  // v121+12 写 HIDWORD(pObj32)
            v122 = (const char *)sub_42A380(0);  // 存 四字节号格式化
            off_77F3FC("Local Ip [%s]", v122);  // 控制台调试日志输出
            v123 = (const char *)sub_42A380(1);  // 存 四字节号格式化
            off_77F3FC("Public Ip [%s]", v123);  // 控制台调试日志输出
          }
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < HIBYTE(ArgList) );  // 调用 while
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 14] case 12：聊天消息（MessageType/ServerId/MessageLength）—— sub_43D900 写入聊天框 ──
    case 12:  // 【case 12】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v575 = 0;  // v575 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      v124 = (char *)sub_422E70(639);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(Str, 256, v124);  // 限量串读入（带回退）
      off_77F3FC("MessageType %d, ServerId %d, MessageLength %d", HIBYTE(ArgList), (uint16_t)v575, strlen(Str));  // 控制台调试日志输出
      if ( HIBYTE(ArgList) == 0 )  // ArgList 高字节 == 0
      {
        v125 = (const char *)sub_422E70(640);  // 存 CStringManager::getStr 取本地化串
        sprintf(v582, v125, Str);  // 格式化写入 v582
        sub_44E8D0(dword_8F8528, (void *)0x24, v582, 0);  // 对象池借出
      }
      sub_43D900(Str, HIBYTE(ArgList), v575, nullptr);  // 聊天消息出口
      return 1;  // 返回 1（已处理该包）
    // ── [段 15] case 13：装备槽同步（ItemSpace/ItemNumber）—— sub_432F00 取物品栏模型 ──
    //   sub_47CD00 刷新装备栏；与 docs/21 §3.2 的「0x0A 角色装备槽同步」为同一机制的服务端回报面
    case 13:  // 【case 13】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v574 = 0;  // v574 复制自 0
      v575 = 0;  // v575 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      if ( HIBYTE(ArgList) == 2 )  // ArgList 高字节 == 2
      {
        sub_404AB0(&v575);  // 游标读 2 字节 → &v575
        sub_50D920((uint16_t)v575);  // 仓储栏类型设置
        off_77F3FC(  // 控制台调试日志输出
          "CNGameCore::NetworkProc - ENUM_NOTIPACKET_ITEM_LIST - Storage capacity = %d",  // 第 1 个实参：串 CNGameCore::NetworkProc - ENUM_NOTIPACKET_ITEM_LIST - Storage capacity = %d
          (uint16_t)v575);  // 第 2 个实参：双字节 v575
      }
      sub_404AB0(&v574);  // 游标读 2 字节 → &v574
      off_77F3FC("ItemSpace %d, ItemNumber %d", HIBYTE(ArgList), (uint16_t)v574);  // 控制台调试日志输出
      v128 = sub_432F00(HIBYTE(ArgList));  // 存 按类型取全局列表对象 【按类型取全局列表对象】case 0/1/2/4 → dword_8F852C 与 dword_8F8534 与 dword_8F8530 与 dword_8F8538+16，其余空【推断：技能与物品来源槽列表】。
      sub_485020(v128);  // 技能槽容器整体释放
      v566 = nullptr;  // v566 复制自 nullptr
      if ( (uint16_t)v574 != 0 )  // 条件判定
      {
        do
        {
          LOBYTE(v572) = 0;  // 低字节写 v572 ← 0
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          v580 = 0;  // v580 复制自 0
          *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
          pObj12 = 0;  // pObj12 复制自 0
          v579 = 0;  // v579 复制自 0
          sub_404AB0(&v580);  // 游标读 2 字节 → &v580
          sub_404AB0(netshort);  // 游标读 2 字节 → netshort
          sub_404AD0(&v579);  // 游标读 4 字节 → &v579
          sub_404A90(&v572);  // 游标读 1 字节 → &v572
          sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
          sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
          off_77F3FC(  // 控制台调试日志输出
            "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d",  // 第 1 个实参：串 SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d
            (uint16_t)v580,  // 第 2 个实参：双字节 v580
            netshort[0],  // 第 3 个实参
            v579,  // 第 4 个实参
            (uint8_t)v572,  // 第 5 个实参：单字节 v572
            (uint16_t)pObj12,  // 第 6 个实参：双字节 pObj12
            HIBYTE(v567));  // 第 7 个实参
          pObj26 = sub_44A980((uint16_t)v580);  // 存 带界索引 getter nArg2 ≥ [2]
          if ( pObj26 != 0 )  // pObj26 不等于 0
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj26 + 60))(pObj26, netshort[0]) != 0 )  // 虚表 +60 调用
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj26 + 40))(pObj26, v579);  // 虚表 +40 调用
            else
              off_77F3FC(aCriticalError_17);  // 控制台调试日志输出
          }
          else
          {
            LOBYTE(v129) = HIBYTE(v567) != 0;  // 字节提取赋值
            v131 = sub_522300((void *)netshort[0], v579, v572, 0, (uint16_t)pObj12, v129);  // 存 ★ PO 工厂分发器
            sub_484F40((uint16_t)v580, v131, 1);  // 技能槽装载
          }
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < (uint16_t)v574 );  // 调用 while
      }
      if ( HIBYTE(ArgList) == 0 )  // ArgList 高字节 == 0
        sub_47CD00(dword_8F8540);  // 逐条处理型别 fld[68]==0 的条件条目：为已注册
      return 1;  // 返回 1（已处理该包）
    // ── [段 16] case 14：★ 物品栏数据同步（第二套路，107 行）—— 含 sub_429830/sub_4337E0 面板刷新 ──
    case 14:  // 【case 14】包类型分支
      v581 = 0;  // v581 复制自 0
      v565 = 0;  // v565 复制自 0
      sub_404A90(&v581);  // 游标读 1 字节 → &v581
      sub_404AB0(&v565);  // 游标读 2 字节 → &v565
      off_77F3FC("ItemSpace %d, ItemNumber %d", v581, (uint16_t)v565);  // 控制台调试日志输出
      sub_432F00(v581);  // 按类型取全局列表对象 【按类型取全局列表对象】case 0/1/2/4 → dword_8F852C 与 dword_8F8534 与 dword_8F8530 与 dword_8F8538+16，其余空【推断：技能与物品来源槽列表】。
      memset(&pBuf[8], 0, 12);  // 调用 memset
      v607 = 4;  // v607 复制自 4
      v566 = nullptr;  // v566 复制自 nullptr
      if ( (uint16_t)v565 != 0 )  // 条件判定
      {
        do
        {
          LOBYTE(v574) = 0;  // 低字节写 v574 ← 0
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          v572 = 0;  // v572 复制自 0
          v579 = 0;  // v579 复制自 0
          v580 = 0;  // v580 复制自 0
          *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
          sub_404AB0(&v572);  // 游标读 2 字节 → &v572
          sub_404AB0(&v579);  // 游标读 2 字节 → &v579
          sub_404AD0(netshort);  // 游标读 4 字节 → netshort
          sub_404A90(&v574);  // 游标读 1 字节 → &v574
          sub_404AB0(&v580);  // 游标读 2 字节 → &v580
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          off_77F3FC(  // 控制台调试日志输出
            "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d",  // 第 1 个实参：串 SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d, IsSealed %d
            (uint16_t)v572,  // 第 2 个实参：双字节 v572
            (uint16_t)v579,  // 第 3 个实参：双字节 v579
            *(uint32_t *)netshort,  // 第 4 个实参
            (uint8_t)v574,  // 第 5 个实参：单字节 v574
            (uint16_t)v580,  // 第 6 个实参：双字节 v580
            HIBYTE(ArgList));  // 第 7 个实参
          v132 = (uint16_t)v572;  // v132 ← 表达式
          v134 = (int *)sub_44A980((uint16_t)v572);  // 存 带界索引 getter nArg2 ≥ [2]
          if ( v134 != nullptr )  // v134 不等于 nullptr
          {
            if ( (uint16_t)v579 == 0xFFFF )  // 条件判定
            {
              sub_484D50(v132);  // 技能槽清空
            }
            else
            {
              v135 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v134 + 60))(v134, (uint16_t)v579);  // 虚表 +60 调用
              v136 = (int (/*thiscall*/ **)(int *))*v134;  // v136 ← 表达式
              if ( v135 != 0 )  // v135 不等于 0
              {
                v137 = v136[11](v134);  // v137 存调用结果
                if ( *(uint32_t *)netshort > v137 )  // 条件判定
                {
                  v138 = (*(int (/*thiscall*/ **)(int *))(*v134 + 44))(v134);  // 虚表 +44 调用
                  Block[0] = (void *)(*(uint32_t *)netshort - v138);  // 调用语句
                  v605 = v134;  // v605 复制自 v134
                  sub_44E340(&v605);  // 8 字节元素容器尾插单值 有空位
                }
                (*(void (/*thiscall*/ **)(int *, uint32_t))(*v134 + 40))(v134, *(uint32_t *)netshort);  // 虚表 +40 调用
              }
              else if ( (*v136)(v134) == 2 )
              {
                v139 = HIBYTE(ArgList) == 1;  // v139 ← 表达式
                *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v134 + 16))(v134) + 32) = v139;  // 虚表 +16 调用
                v140 = sub_4E9B10(*(uint32_t *)netshort, v574, 0, (uint16_t)v580);  // 存 与
                v141 = *v134;  // 取 v134 首字段
                LOBYTE(v607) = 5;  // 低字节写 v607 ← 5
                (*(void (/*thiscall*/ **)(int *, int))(v141 + 184))(v134, v140);  // 虚表 +184 调用
                LOBYTE(v607) = 4;  // 低字节写 v607 ← 4
                sub_445150(v561);  // 分发器 case 0xA 收尾：装备同步资源清理
              }
              else
              {
                off_77F3FC(aCriticalError_17);  // 控制台调试日志输出
              }
            }
          }
          else if ( (uint16_t)v579 != 0xFFFF )
          {
            LOBYTE(v133) = HIBYTE(ArgList) != 0;  // 字节提取赋值
            pObj9 = sub_522300((void *)(uint16_t)v579, *(int *)netshort, v574, 0, (uint16_t)v580, v133);  // 存 ★ PO 工厂分发器
            LODWORD(pObj32) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 44))(pObj9);  // 虚表 +44 调用
            pObj92 = pObj9;  // pObj92 复制自 pObj9
            sub_44E340(&pObj92);  // 8 字节元素容器尾插单值 有空位
            sub_484F40((uint16_t)v572, pObj9, 1);  // 技能槽装载
          }
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < (uint16_t)v565 );  // 调用 while
      }
      if ( v581 == 0 )  // v581 等于 0
        sub_47CD00(dword_8F8540);  // 逐条处理型别 fld[68]==0 的条件条目：为已注册
      v143 = *(uint32_t **)&pBuf[8];  // v143 ← 表达式
      v144 = *(uint32_t **)&pBuf[12];  // v144 ← 表达式
      for ( jj = *(uint32_t **)&pBuf[8]; jj != v144; jj += 2 )  // 循环控制
      {
        v146 = sub_429830((uint16_t)word_77F804);  // 存 表按键查找
        sub_4337E0(*jj, jj[1], v146, (jj == v143) - 1);  // 【物品获得播报】串 1179/1180 格式化
      }
      v607 = -1;  // 局部 v607 → -1
      sub_5E5260(&pBuf[4]);  // 调: sub_5E5260
      v147 = *((uint32_t *)dword_8F8528 + 90);  // v147 存调用结果
      if ( v147 != 0  // 条件判定
        && (*((uint32_t *)dword_8F8528 + 91) - v147) >> 2 != 0  // 第 1 个实参：地址 && (*((uint32_t *)dword_8F8528 + 91) - v147) >> 2 != 0
        && (*(uint32_t *)sub_57A590(0) != 0 || MEMORY[0x34] == 1) )  // 第 1 个实参：地址 && (*(uint32_t *)sub_57A590(0) != 0 || MEMORY[0x34] == 1)
      {
        sub_63B3C0();  // 物品盒数据 5
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 17] case 15：物品数据刷新（DATA %d / CHANGE_ALERT）—— sub_445150 释放旧对象 + vt+348 数据变更通知 ──
    case 15:  // 【case 15】包类型分支
      LOBYTE(v572) = 0;  // 低字节写 v572 ← 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v580 = 0;  // v580 复制自 0
      v574 = 0;  // v574 复制自 0
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AB0(netshort);  // 游标读 2 字节 → netshort
      sub_404AB0(&v580);  // 游标读 2 字节 → &v580
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      sub_404A90(&v572);  // 游标读 1 字节 → &v572
      sub_404AB0(&v574);  // 游标读 2 字节 → &v574
      off_77F3FC(  // 控制台调试日志输出
        "SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d",  // 第 1 个实参：串 SlotIndex %d, ItemIndex %d, Data %d, ext_data1 %d, Durability %d
        netshort[0],  // 第 2 个实参
        (uint16_t)v580,  // 第 3 个实参：双字节 v580
        ArgList,  // 第 4 个实参
        (uint8_t)v572,  // 第 5 个实参：单字节 v572
        (uint16_t)v574);  // 第 6 个实参：双字节 v574
      sprintf(OutputString, "DATA %d", ArgList);  // 格式化写入 OutputString
      OutputDebugStringA(OutputString);  // 调用 OutputDebugStringA
      v148 = v580;  // v148 复制自 v580
      if ( (uint16_t)v580 == 0xFFFF )  // 条件判定
      {
        sub_484D50(netshort[0]);  // 技能槽清空
      }
      else
      {
        v149 = netshort[0];  // v149 ← 表达式
        if ( sub_44A980(netshort[0]) != 0 )  // 条件判定
        {
          v150 = (int *)sub_44A980(v149);  // 存 带界索引 getter nArg2 ≥ [2]
          v151 = (*(int (/*thiscall*/ **)(int *))(*v150 + 16))(v150);  // 虚表 +16 调用
          if ( *(uint32_t *)(v151 + 4) == (uint16_t)v580 )  // 条件判定
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v150 + 20))(v150, 1) != 0 )  // 虚表 +20 调用
            {
              (*(void (/*thiscall*/ **)(int *, int))(*v150 + 40))(v150, ArgList);  // 虚表 +40 调用
            }
            else if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v150 + 20))(v150, 2) != 0 )  // 虚表 +20 调用
            {
              v152 = sub_4E9B10(ArgList, v572, 0, (uint16_t)v574);  // 存 与
              v153 = *v150;  // 取 v150 首字段
              v607 = 6;  // v607 复制自 6
              (*(void (/*thiscall*/ **)(int *, int))(v153 + 184))(v150, v152);  // 虚表 +184 调用
              v607 = -1;  // 局部 v607 → -1
              sub_445150(v560);  // 分发器 case 0xA 收尾：装备同步资源清理
            }
          }
          else
          {
            sub_484D50(netshort[0]);  // 技能槽清空
            v515 = sub_522300((void *)(uint16_t)v580, ArgList, v572, 0, (uint16_t)v574, 1);  // 存 ★ PO 工厂分发器
            sub_484F40(netshort[0], v515, 1);  // 技能槽装载
          }
        }
        else
        {
          v516 = sub_522300((void *)v148, ArgList, v572, 0, (uint16_t)v574, 1);  // 存 ★ PO 工厂分发器
          sub_484F40(netshort[0], v516, 1);  // 技能槽装载
        }
      }
      for ( kk = 0; kk < 2; ++kk )  // 循环控制
        sub_484710(kk, 0);  // 技能槽状态写入
      sub_57A3A0(dword_8F8538);  // std::string 辅助 3
      sub_432EA0("CHANGE_ALERT", -1, 0, 0);  // 音效播放包装
      return 1;  // 返回 1（已处理该包）
    // ── [段 18] case 16：★ 物品移动/合并（SlotNumber + SlotIndex1/ItemSpace/SlotIndex2，112 行） ──
    //   逐对处理：sub_44A980/sub_44AB50 取槽对象，打印 srcItem ItemInfo Address 便于调试
    case 16:  // 【case 16】包类型分支
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("SlotNumber %d", (uint16_t)v579);  // 控制台调试日志输出
      v575 = *(uint32_t *)(dword_8F8538 + 16);  // 读 dword_8F8538+16 处 4 字节
      LODWORD(pObj32) = dword_8F7C04;  // dword_8F7C04＝本地玩家对象
      v566 = nullptr;  // v566 复制自 nullptr
      if ( (uint16_t)v579 == 0 )  // 条件判定
        goto LABEL_316;  // 转到 LABEL_316
      do
      {
        HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
        v580 = 0;  // v580 复制自 0
        *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
        sub_404AB0(&v580);  // 游标读 2 字节 → &v580
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        sub_404AB0(netshort);  // 游标读 2 字节 → netshort
        off_77F3FC("SlotIndex1 %d, ItemSpace %d, SlotIndex2 %d", (uint16_t)v580, HIBYTE(ArgList), netshort[0]);  // 控制台调试日志输出
        pObj35 = sub_44A980((uint16_t)v580);  // 存 带界索引 getter nArg2 ≥ [2]
        pObj4 = pObj35;  // pObj4 复制自 pObj35
        if ( pObj35 != 0 )  // pObj35 不等于 0
        {
          v157 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj35 + 16))(pObj35);  // 虚表 +16 调用
          off_77F3FC("srcItem ItemInfo Address = 0x%x", v157);  // 控制台调试日志输出
        }
        else
        {
          off_77F3FC("srcItem is NULL");  // 控制台调试日志输出
        }
        if ( HIBYTE(ArgList) == 0 )  // ArgList 高字节 == 0
        {
          v158 = netshort[0];  // v158 ← 表达式
          v159 = (uint32_t *)sub_44A980(netshort[0]);  // 存 带界索引 getter nArg2 ≥ [2]
          if ( v159 == nullptr )  // v159 等于 nullptr
            goto LABEL_314;  // 转到 LABEL_314
          v160 = *v159;  // 取 v159 首字段
          v558 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 16))(pObj4, v558) + 4);  // 虚表 +16 调用
LABEL_312:
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v160 + 60))(v159) != 0 )  // 虚表 +60 调用
          {
            v169 = *v159;  // 取 v159 首字段
            v170 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 44))(pObj4);  // 虚表 +44 调用
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v169 + 48))(v159, v170);  // 虚表 +48 调用
          }
          else
          {
            v161 = (*(int (/*thiscall*/ **)(uint32_t *))(*v159 + 16))(v159);  // 虚表 +16 调用
            off_77F3FC(aCriticalError_18, *(uint32_t *)(v161 + 4));  // 控制台调试日志输出
          }
          goto LABEL_315;  // 转到 LABEL_315
        }
        if ( HIBYTE(ArgList) != 3 )  // ArgList 高字节 != 3
        {
          if ( HIBYTE(ArgList) != 1 )  // ArgList 高字节 != 1
            goto LABEL_315;  // 转到 LABEL_315
          v158 = netshort[0];  // v158 ← 表达式
          v168 = (uint32_t *)sub_44A980(netshort[0]);  // 存 带界索引 getter nArg2 ≥ [2]
          v159 = v168;  // v159 复制自 v168
          if ( v168 == nullptr )  // v168 等于 nullptr
          {
LABEL_314:
            sub_484F40(v158, pObj4, 1);  // 技能槽装载
            sub_484F40((uint16_t)v580, 0, 1);  // 技能槽装载
            goto LABEL_315;  // 转到 LABEL_315
          }
          v160 = *v168;  // 取 v168 首字段
          v558 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 16))(pObj4, v558) + 4);  // 虚表 +16 调用
          goto LABEL_312;  // 转到 LABEL_312
        }
        v162 = __RTDynamicCast(pObj4, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // v162 存调用结果
        if ( v162 != 0 )  // v162 不等于 0
        {
          if ( (uint32_t)pObj32 != 0 )  // 条件判定
          {
            v164 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pObj32 + 792))(pObj32, netshort[0]);  // 虚表 +792 调用
            v165 = *(uint32_t *)pObj32;  // v165 ← 表达式
            if ( v164 != 0 )  // v164 不等于 0
            {
              pObj31 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(v165 + 792))(pObj32, netshort[0]);  // 虚表 +792 调用
              v167 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj31 + 16))(pObj31);  // 虚表 +16 调用
              off_77F3FC(aCriticalError_21, *(uint32_t *)(v167 + 4));  // 控制台调试日志输出
            }
            else
            {
              (*(void (/*thiscall*/ **)(uint32_t, int))(v165 + 784))(pObj32, v162);  // 虚表 +784 调用
            }
            sub_484F40((uint16_t)v580, 0, 1);  // 技能槽装载
          }
          else
          {
            off_77F3FC(aCriticalError_20);  // 控制台调试日志输出
            sub_484F40((uint16_t)v580, 0, 1);  // 技能槽装载
          }
        }
        else
        {
          v163 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 16))(pObj4);  // 虚表 +16 调用
          off_77F3FC(aCriticalError_19, *(uint32_t *)(v163 + 4));  // 控制台调试日志输出
          sub_484F40((uint16_t)v580, 0, 1);  // 技能槽装载
        }
LABEL_315:
        v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
      }
      while ( (int)v566 < (uint16_t)v579 );  // 调用 while
LABEL_316:
      sub_4844B0(dword_8F8538);  // 技能槽记录初始化
      sub_44AB50(0, 12);  // 页签切换 读页索引 [26+pArg2]
      sub_44AB50(1, 12);  // 页签切换 读页索引 [26+pArg2]
      v171 = sub_422E70(643);  // 存 CStringManager::getStr 取本地化串
      sub_43BEE0(v171, -6567706, 0, -1);  // 【播报上屏】
      sub_47CD00(dword_8F8540);  // 逐条处理型别 fld[68]==0 的条件条目：为已注册
      return 1;  // 返回 1（已处理该包）
    // ── [段 19] case 17：交易状态（ServerId/TradeState）—— sub_484710 写交易面板 ──
    case 17:  // 【case 17】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v575 = 0;  // v575 复制自 0
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("ServerId %d, TradeState %d", (uint16_t)v575, HIBYTE(ArgList));  // 控制台调试日志输出
      sub_484710((uint16_t)v575 != (uint16_t)word_77F804, HIBYTE(ArgList));  // 技能槽状态写入
      return 1;  // 返回 1（已处理该包）
    // ── [段 20] case 18：★ 交易完成（SlotNumber + 双 SlotIndex，TRADE_OK）—— 双端物品交换落地 ──
    case 18:  // 【case 18】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      off_77F3FC("SlotNumber %d", (uint16_t)ArgList);  // 控制台调试日志输出
      v566 = *(uint32_t **)(dword_8F8538 + 20);  // v566 存调用结果
      v575 = 0;  // v575 复制自 0
      if ( (uint16_t)ArgList != 0 )  // 条件判定
      {
        v172 = sub_44E8D0(dword_8F8528, (void *)0x20, 0, *(uint16_t *)(dword_8F8538 + 4));  // 存 对象池借出
        v575 = __RTDynamicCast(
                 v172,  // 第 1 个实参
                 0,  // 第 2 个实参：常量 0
                 &IRDPopupWindow `RTTI Type Descriptor',  // 第 3 个实参：地址 &IRDPopupWindow `RTTI Type Descriptor」
                 &CNRDItemTradeResultWindow `RTTI Type Descriptor',  // 第 3 个实参：地址 &CNRDItemTradeResultWindow `RTTI Type Descriptor」
                 0);  // 第 3 个实参：常量 0
      }
      pObj12 = 0;  // pObj12 复制自 0
      if ( (uint16_t)ArgList != 0 )  // 条件判定
      {
        do
        {
          *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
          v579 = 0;  // v579 复制自 0
          sub_404AB0(netshort);  // 游标读 2 字节 → netshort
          sub_404AB0(&v579);  // 游标读 2 字节 → &v579
          off_77F3FC("SlotIndex1 %d, SlotIndex2 %d", netshort[0], (uint16_t)v579);  // 控制台调试日志输出
          pObj23 = sub_44A980(netshort[0]);  // 存 带界索引 getter nArg2 ≥ [2]
          pObj18 = pObj23;  // pObj18 复制自 pObj23
          if ( pObj23 != 0 )  // pObj23 不等于 0
          {
            v175 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj23 + 16))(pObj23);  // 虚表 +16 调用
            if ( sub_4F2D40(*(uint32_t *)(v175 + 4)) == 2 )  // 条件判定
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 172))(pObj18);  // 虚表 +172 调用
          }
          v176 = (int *)sub_44A980((uint16_t)v579);  // 存 带界索引 getter nArg2 ≥ [2]
          if ( v575 != 0 )  // v575 不等于 0
            sub_63EDD0(pObj18);  // 交易结果文本
          if ( pObj12 == (uint16_t)ArgList - 1 && pObj18 != 0 )  // 条件判定
          {
            v177 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 56))(pObj18);  // 虚表 +56 调用
            sub_432EA0(v177, -1, 0, 0);  // 音效播放包装
          }
          if ( v176 != nullptr )  // v176 不等于 nullptr
          {
            v178 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v176 + 16))(v176) + 4);  // 虚表 +16 调用
            if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 16))(pObj18) + 4) == v178 )  // 虚表 +16 调用
            {
              v180 = *v176;  // 取 v176 首字段
              v181 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 44))(pObj18);  // 虚表 +44 调用
              (*(void (/*thiscall*/ **)(int *, int))(v180 + 48))(v176, v181);  // 虚表 +48 调用
            }
            else
            {
              v179 = (*(int (/*thiscall*/ **)(int *))(*v176 + 16))(v176);  // 虚表 +16 调用
              off_77F3FC((char *)&byte_729744, *(uint32_t *)(v179 + 4));  // 控制台调试日志输出
            }
          }
          else
          {
            sub_484F40((uint16_t)v579, pObj18, 1);  // 技能槽装载
            sub_484F40(netshort[0], 0, 1);  // 技能槽装载
          }
          ++pObj12;  // pObj12 自增
        }
        while ( pObj12 < (uint16_t)ArgList );  // 调用 while
      }
      sub_4844B0(dword_8F8538);  // 技能槽记录初始化
      sub_44AB50(0, 12);  // 页签切换 读页索引 [26+pArg2]
      v182 = sub_422E70(644);  // 存 CStringManager::getStr 取本地化串
      sub_43BEE0(v182, -6567706, 0, -1);  // 【播报上屏】
      sub_432EA0("TRADE_OK", -1, 0, 0);  // 音效播放包装
      goto LABEL_336;  // 转到 LABEL_336
    // ── [段 21] case 19：★ 技能栏全量（Sp/SkillNumber + SlotIndex/SkillIndex/Level）—— sub_47DC90 族写技能表 ──
    case 19:  // 【case 19】包类型分支
      v569 = 0;  // v569 复制自 0
      v573 = 0;  // v573 复制自 0
      v575 = 0;  // v575 复制自 0
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      off_77F3FC("Sp %d", (uint16_t)v575);  // 控制台调试日志输出
      Value = (uint16_t)v575;  // Value ← 表达式
      sub_404A90(&v569);  // 游标读 1 字节 → &v569
      off_77F3FC("SkillNumber %d", v569);  // 控制台调试日志输出
      sub_483E30(dword_8F853C);  // 技能槽数组整体清空
      sub_47E2B0();  // 全局重置：遍历 dword_99FC34→dword_99FC74 的 4 个对象指针 vector
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1148))(dword_8F7C04);  // 虚表 +1148 调用
      v183 = 0;  // v183 复制自 0
      if ( v569 != 0 )  // v569 不等于 0
      {
        do
        {
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          v581 = 0;  // v581 复制自 0
          sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          sub_404A90(&v581);  // 游标读 1 字节 → &v581
          off_77F3FC("SlotIndex %d, SkillIndex %d, Level %d", HIBYTE(v567), HIBYTE(ArgList), v581);  // 控制台调试日志输出
          sub_57A3C0(HIBYTE(v567), HIBYTE(ArgList));  // 对象/控件辅助
          v537 = v581;  // v537 复制自 v581
          sub_47DC90(HIBYTE(ArgList));  // 薄分发：取当前场景对象
          sub_47DEC0(0, v537);  // 写第 nArg2 条的 clong 串
          if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1136))(  // 虚表 +1136 调用
              dword_8F7C04,  // 第 1 个实参
              HIBYTE(ArgList),  // 第 2 个实参
              v581);  // 第 3 个实参
          ++v183;  // v183 自增
        }
        while ( v183 < v569 );  // 调用 while
      }
      sub_47E4F0();  // 技能参数刷新
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1152))(dword_8F7C04);  // 虚表 +1152 调用
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1156))(dword_8F7C04);  // 虚表 +1156 调用
      }
      sub_404A90(&v573);  // 游标读 1 字节 → &v573
      off_77F3FC("BonusSpNumber %d", v573);  // 控制台调试日志输出
      v184 = 0;  // v184 复制自 0
      if ( v573 != 0 )  // v573 不等于 0
      {
        do
        {
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          pObj12 = 0;  // pObj12 复制自 0
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
          off_77F3FC("SkillIndex %d, BonusSp %d", HIBYTE(ArgList), (uint16_t)pObj12);  // 控制台调试日志输出
          v185 = (uint16_t)pObj12;  // v185 ← 表达式
          *(uint32_t *)(sub_47DC90(HIBYTE(ArgList)) + 540) = v185;  // 内存写入
          ++v184;  // v184 自增
        }
        while ( v184 < v573 );  // 调用 while
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 22] case 20：SP 变化（SkillIndex/BonusSp + SP_DOWN）—— sub_41ACF0 扣点 + 界面刷新 ──
    case 20:  // 【case 20】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v579 = 0;  // v579 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("SkillIndex %d, BonusSp %d", HIBYTE(ArgList), (uint16_t)v579);  // 控制台调试日志输出
      v186 = sub_47DC90(HIBYTE(ArgList));  // 存 薄分发：取当前场景对象
      v187 = v186;  // v187 复制自 v186
      if ( *(uint32_t *)(v186 + 540) < (int)(uint16_t)v579 )  // 条件判定
      {
        v538 = sub_41ACF0(v186 + 20);  // 存 驻留串句柄 → 字符串指针 句柄或全局池 dword_8F7A14 寻址失败 → 返回空串 szPassword；否则返回 0x41AC90
        v188 = (const char *)sub_422E70(645);  // 存 CStringManager::getStr 取本地化串
        sprintf(&Destination, v188, v538);  // 调用 sprintf
        sub_43BEE0(&Destination, -6567706, 0, -1);  // 【播报上屏】
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1240))(dword_8F7C04, 1, HIBYTE(ArgList));  // 虚表 +1240 调用
        sub_432EA0("SP_DOWN", -1, 0, 0);  // 音效播放包装
      }
      *(uint32_t *)(v187 + 540) = (uint16_t)v579;  // v187+540 写 (uint16_t)v579
      return 1;  // 返回 1（已处理该包）
    // ── [段 23] case 21：任务列表（QuestNumber）—— sub_47D1E0/sub_47D9D0 任务管理器写入 ──
    case 21:  // 【case 21】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("QuestNumber %d", HIBYTE(ArgList));  // 控制台调试日志输出
      sub_57A4F0(dword_8F8540);  // 14 行小函数
      v189 = 0;  // v189 复制自 0
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        do
        {
          i5 = nullptr;  // i5 复制自 nullptr
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          sub_47D1E0((uint16_t)i5);  // 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
          ++v189;  // v189 自增
        }
        while ( v189 < HIBYTE(ArgList) );  // 调用 while
      }
      sub_47D9D0(dword_8F8540);  // 条件旗标重算
      sub_553FB0(*((uint32_t *)dword_8F8528 + 21));  // 任务 NPC 查询
      return 1;  // 返回 1（已处理该包）
    // ── [段 24] case 22：★ 位置同步（ServerId/XPos/YPos/Direction）—— sub_429830 取对象 + sub_45E680 设位 ──
    case 22:  // 【case 22】包类型分支
      LOBYTE(v575) = 0;  // 低字节写 v575 ← 0
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      v579 = 0;  // v579 复制自 0
      pObj12 = 0;  // pObj12 复制自 0
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
      sub_404A90(&v575);  // 游标读 1 字节 → &v575
      off_77F3FC(  // 控制台调试日志输出
        "ServerId %d, XPos %d, YPos %d, Direction %d",  // 第 1 个实参：串 ServerId %d, XPos %d, YPos %d, Direction %d
        (uint16_t)ArgList,  // 第 2 个实参：双字节 ArgList
        (int16_t)v579,  // 第 3 个实参
        (int16_t)pObj12,  // 第 4 个实参
        (uint8_t)v575);  // 第 5 个实参：单字节 v575
      if ( (uint16_t)ArgList != (uint16_t)word_77F804 )  // 低 16 位比较 ArgList != word_77F804
      {
        pObj24 = *(uint32_t *)(sub_429830(ArgList) + 192);  // pObj24 存调用结果
        if ( *(uint32_t *)(*(uint32_t *)(pArg12[5] + 44) + 104) != 0 && (uint8_t)sub_45E680(pObj24) != 0 )  // 条件判定
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj24 + 364))(  // 虚表 +364 调用
            pObj24,  // 第 1 个实参
            (int16_t)v579,  // 第 2 个实参
            (int16_t)pObj12,  // 第 3 个实参
            v575);  // 第 4 个实参
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 25] case 23：★ 角色死亡/复活（ServerId/NewTownIndex/NewTownAreaIndex/XPos/YPos/Direction） ──
    //   比对当前管理器 → sub_45FE80 注册 → vt+136 判位成功则 vt+140 落位（100,1,1），失败则 sub_45F1E0 回收
    case 23:  // 【case 23】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
      LOBYTE(v574) = 0;  // 低字节写 v574 ← 0
      v579 = 0;  // v579 复制自 0
      v575 = 0;  // v575 复制自 0
      pObj12 = 0;  // pObj12 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
      sub_404A90(&v574);  // 游标读 1 字节 → &v574
      off_77F3FC(  // 控制台调试日志输出
        "ServerId %d, NewTownIndex %d, NewTownAreaIndex %d, XPos %d, YPos %d, Direction %d",  // 第 1 个实参：串 ServerId %d, NewTownIndex %d, NewTownAreaIndex %d, XPos %d, YPos %d, Direction %d
        (uint16_t)v579,  // 第 2 个实参：双字节 v579
        HIBYTE(ArgList),  // 第 3 个实参
        HIBYTE(v567),  // 第 4 个实参
        (int16_t)v575,  // 第 5 个实参
        (int16_t)pObj12,  // 第 6 个实参
        (uint8_t)v574);  // 第 7 个实参：单字节 v574
      if ( (uint16_t)v579 == (uint16_t)word_77F804 )  // 低 16 位比较 v579 == word_77F804
        return 1;  // 返回 1（已处理该包）
      v191 = sub_429830(v579);  // 存 表按键查找
      v192 = sub_42B340(v191);  // 存 虚拟角色惰性创建
      v193 = pArg12[5];  // v193 ← 表达式
      pObj15 = v192;  // pObj15 复制自 v192
      if ( HIBYTE(ArgList) == *(uint32_t *)(v193 + 100) && (v195 = sub_42F240(v193), HIBYTE(v567) == v195) )  // 条件判定
      {
        sub_45FE80(18, (uint16_t)v579, pObj15, 0, 0);  // 对象注册
        v196 = *(uint32_t *)pObj15;  // v196 ← 表达式
        *(uint32_t *)netshort = (int16_t)pObj12;  // 内存写入
        v580 = (int16_t)v575;  // v580 ← 表达式
        if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(v196 + 136))(  // 虚表 +136 调用
               pObj15,  // 第 1 个实参
               (int16_t)v575,  // 第 2 个实参
               (int16_t)pObj12,  // 第 3 个实参
               0) == 0 )  // 第 4 个实参
          (*(void (/*thiscall*/ **)(int, int *, u_short *, int, uint32_t, int, int, int))(*(uint32_t *)pObj15 + 140))(  // 虚表 +140 调用
            pObj15,  // 第 1 个实参
            &v580,  // 第 2 个实参：地址 &v580
            netshort,  // 第 3 个实参
            v580,  // 第 4 个实参
            *(uint32_t *)netshort,  // 第 5 个实参
            100,  // 第 6 个实参：常量 100
            1,  // 第 7 个实参：常量 1
            1);  // 第 8 个实参：常量 1
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pObj15 + 112))(pObj15, v580, *(uint32_t *)netshort, 0);  // 虚表 +112 调用
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj15 + 364))(pObj15, v580, *(uint32_t *)netshort, v574);  // 虚表 +364 调用
      }
      else
      {
        sub_45F1E0(pObj15);  // 对象注销/退场
      }
      goto LABEL_365;  // 转到 LABEL_365
    // ── [段 26] case 24：★ 城镇/区域切换（TownIndex/TownAreaIndex/UserNumber + 全员坐标，82 行） ──
    //   sub_41C190/sub_41D300 切换场景、sub_424A40 切镜头目标、逐用户 sub_45E680 落位
    case 24:  // 【case 24】包类型分支
      HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v574 = 0;  // v574 复制自 0
      sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0(&v574);  // 游标读 2 字节 → &v574
      off_77F3FC("TownIndex %d, TownAreaIndex %d, UserNumber %d", HIBYTE(v567), HIBYTE(ArgList), (uint16_t)v574);  // 控制台调试日志输出
      v197 = pArg12[3];  // v197 ← 表达式
      if ( v197 == 3 )  // v197 等于 3
      {
        sub_41C190(1);  // 级联通知转发
        sub_444B30(4);  // fade 状态机复位 写 fade 状态
      }
      else if ( v197 != 1 )
      {
        sub_41D300(1);  // 模块切换 setter → 0x41CC80
      }
      sub_45D190(SHIBYTE(v567), (void *)HIBYTE(ArgList));  // 进入/切换房间
      LODWORD(pObj32) = *(uint32_t *)(*(uint32_t *)(pArg12[5] + 44) + 104);  // 调用 LODWORD
      v566 = nullptr;  // v566 复制自 nullptr
      if ( (uint16_t)v574 != 0 )  // 条件判定
      {
        do
        {
          LOBYTE(v572) = 0;  // 低字节写 v572 ← 0
          *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
          v575 = 0;  // v575 复制自 0
          pObj12 = 0;  // pObj12 复制自 0
          sub_404AB0(netshort);  // 游标读 2 字节 → netshort
          sub_404AB0(&v575);  // 游标读 2 字节 → &v575
          sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
          sub_404A90(&v572);  // 游标读 1 字节 → &v572
          off_77F3FC(  // 控制台调试日志输出
            "ServerId %d, XPos %d, YPos %d, Direction %d",  // 第 1 个实参：串 ServerId %d, XPos %d, YPos %d, Direction %d
            netshort[0],  // 第 2 个实参
            (int16_t)v575,  // 第 3 个实参
            (int16_t)pObj12,  // 第 4 个实参
            (uint8_t)v572);  // 第 5 个实参：单字节 v572
          v198 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
          if ( v198 != 0 )  // v198 不等于 0
          {
            pObj = sub_42B340(v198);  // 存 虚拟角色惰性创建
            sub_45FE80(18, netshort[0], pObj, 0, 0);  // 对象注册
            v579 = (int16_t)pObj12;  // v579 ← 表达式
            v580 = (int16_t)v575;  // v580 ← 表达式
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 136))(  // 虚表 +136 调用
                   pObj,  // 第 1 个实参
                   (int16_t)v575,  // 第 2 个实参
                   (int16_t)pObj12,  // 第 3 个实参
                   0) == 0 )  // 第 4 个实参
              (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(*(uint32_t *)pObj + 140))(  // 虚表 +140 调用
                pObj,  // 第 1 个实参
                &v580,  // 第 2 个实参：地址 &v580
                &v579,  // 第 3 个实参：地址 &v579
                v580,  // 第 4 个实参
                v579,  // 第 5 个实参
                100,  // 第 6 个实参：常量 100
                1,  // 第 7 个实参：常量 1
                1);  // 第 8 个实参：常量 1
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v580, v579, 0);  // 虚表 +112 调用
            if ( netshort[0] == (uint16_t)word_77F804 )  // 条件判定
              sub_431820(*(uint8_t *)(dword_8F7A24 + 296));  // 雪花触发条件包装 【雪花触发条件包装】场景类型 1 且 dword_8F7A24+292 计数为 1 时：pszArg5 非零 →
            else
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 364))(pObj, v580, v579, v572);  // 虚表 +364 调用
            if ( netshort[0] != (uint16_t)word_77F804 )  // 条件判定
              sub_42FBE0(pObj);  // 商店复位 【商店复位】+648 组件 +284 与 +285 与 +340 三标志清零。
          }
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < (uint16_t)v574 );  // 调用 while
      }
      byte_8F8118 = 0;  // 全局 byte_8F8118 ← 0
      sub_44F080(dword_8F8528);  // 界面切换收尾
      sub_45B140(pArg12[5]);  // 刷新
      *(uint8_t *)(pArg12[5] + 116) = 0;  // 内存写入
      if ( dword_9B9460 != 0 )  // dword_9B9460 不等于 0
        sub_632D40();  // 推荐用户列表重建
      if ( dword_9B9458 != 0 )  // dword_9B9458 不等于 0
        sub_6312F0();  // 组队列表重建
      sub_424A40(*(uint32_t *)(*(uint32_t *)(pArg12[5] + 44) + 52));  // 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
      return 1;  // 返回 1（已处理该包）
    // ── [段 27] case 26：@@SET HOST 调试切换（HostIndex）—— sub_656710 设主机
    case 26:  // 【case 26】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("HostIndex %d", HIBYTE(ArgList));  // 控制台调试日志输出
      v200 = HIBYTE(ArgList);  // v200 存调用结果
      *(uint32_t *)(sub_656710() + 40) = v200;  // 内存写入
      off_77F3FC("@@SET HOST %d", HIBYTE(ArgList));  // 控制台调试日志输出
      return 1;  // 返回 1（已处理该包）
    // ── [段 28] case 27：sub_41D300 场景复位（无载荷） ──
    case 27:  // 【case 27】包类型分支
      if ( pArg1[3] != 1 )  // 条件判定
        sub_41D300(1);  // 模块切换 setter → 0x41CC80
      sub_41D300(2);  // 模块切换 setter → 0x41CC80
      for ( mm = 16; mm < 32; mm += 4 )  // 循环控制
      {
        v202 = *(uint32_t *)(mm + dword_8F850C);  // v202 存调用结果
        if ( v202 != 0 )  // v202 不等于 0
        {
          pObj20 = *(uint32_t *)(v202 + 196);  // 读 v202+196 处 4 字节
          if ( pObj20 != 0 )  // pObj20 不等于 0
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj20 + 372))(pObj20, 0);  // 虚表 +372 调用
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 29] case 28：库存/仓库刷新（sub_4755F0/sub_476B60/sub_4968E0） ──
    case 28:  // 【case 28】包类型分支
      HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v570 = 0;  // v570 复制自 0
      v581 = 0;  // v581 复制自 0
      v575 = 0;  // v575 复制自 0
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90(&v570);  // 游标读 1 字节 → &v570
      sub_404A90(&v581);  // 游标读 1 字节 → &v581
      off_77F3FC(  // 控制台调试日志输出
        "DungeonIndex %d, DungeonDifficulty %d, MazeIndex %d, BossXPos %d, BossYPos %d",  // 第 1 个实参：串 DungeonIndex %d, DungeonDifficulty %d, MazeIndex %d, BossXPos %d, BossYPos %d
        (uint16_t)v575,  // 第 2 个实参：双字节 v575
        HIBYTE(v567),  // 第 3 个实参
        HIBYTE(ArgList),  // 第 4 个实参
        v570,  // 第 5 个实参
        v581);  // 第 6 个实参
      v204 = *(uint32_t *)(pArg12[7] + 16);  // v204 存调用结果
      v205 = sub_476B60((uint16_t)v575);  // 存 选区角色数据查找
      sub_4755F0((void *)HIBYTE(ArgList));  // 按关卡尺寸
      *(uint32_t *)(v204 + 108) = v205;  // v204+108 写 v205
      dword_99FB8C = HIBYTE(v567);  // 全局 dword_99FB8C ← HIBYTE(v567)
      dword_99FB7C = v570;  // 全局 dword_99FB7C ← v570
      dword_99FB80 = v581;  // 全局 dword_99FB80 ← v581
      *(uint32_t *)dword_99FB70 = 0;  // 指针 dword_99FB70 写 0
      sub_4968E0(dword_99FD58);  // 对象三段清零 + 双 40 字节链释放 + 槽默认值 先把对象前 0x300 与 +768..+816 清零；按全局域号 dword_8F7A24+12
      *((uint8_t *)dword_99FD58 + 1004) = 1;  // 内存写入
      for ( nn = 16; nn < 32; nn += 4 )  // 循环控制
      {
        v207 = *(uint32_t *)(nn + dword_8F850C);  // v207 存调用结果
        if ( v207 != 0 )  // v207 不等于 0
        {
          pObj6 = *(uint32_t *)(v207 + 196);  // 读 v207+196 处 4 字节
          if ( pObj6 != 0 )  // pObj6 不等于 0
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 1292))(pObj6, v205);  // 虚表 +1292 调用
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 30] case 29：★ 地图加载信息（MapXPos/MapYPos/IsSendMapInfo/MapRandomSeed + MapIndex/MonsterNumber，121 行） ──
    //   sub_444E70/sub_453B80/sub_467600 地图管理器装配；怪物逐条加载
    case 29:  // 【case 29】包类型分支
      v573 = 0;  // v573 复制自 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      sub_404A90(&v573);  // 游标读 1 字节 → &v573
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(v568);  // 游标读 4 字节 → v568
      sub_404A90((char *)&v567 + 3);  // 游标读 1 字节 → (char *)&v567 + 3
      off_77F3FC(  // 控制台调试日志输出
        "MapXPos %d, MapYPos %d, IsSendMapInfo %d MapRandomSeed %d",  // 第 1 个实参：串 MapXPos %d, MapYPos %d, IsSendMapInfo %d MapRandomSeed %d
        v573,  // 第 2 个实参
        HIBYTE(ArgList),  // 第 3 个实参
        HIBYTE(v567),  // 第 4 个实参
        *(uint32_t *)v568);  // 第 5 个实参
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;  // 内存写入
      if ( HIBYTE(v567) == 1 )  // v567 高字节 == 1
      {
        if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )  // 条件判定
          ++word_8F7C10;  // word_8F7C10 自增
        v581 = 0;  // v581 复制自 0
        v579 = 0;  // v579 复制自 0
        sub_404AB0(&v579);  // 游标读 2 字节 → &v579
        sub_404A90(&v581);  // 游标读 1 字节 → &v581
        off_77F3FC("MapIndex %d, MonsterNumber %d", (uint16_t)v579, v581);  // 控制台调试日志输出
        v566 = (uint32_t *)sub_467600(v573, HIBYTE(ArgList));  // 存 36 字节网格坐标换算 返回 dword_99FBB4 + 36*
        *v566 = (uint16_t)v579;
        v209 = 0;  // v209 复制自 0
        if ( v581 != 0 )  // v581 不等于 0
        {
          do
          {
            HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
            HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
            HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
            pObj12 = 0;  // pObj12 复制自 0
            v575 = 0;  // v575 复制自 0
            HIBYTE(v565) = 0;  // 高字节写 v565 ← 0
            v570 = 0;  // v570 复制自 0
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
            sub_404AB0(&v575);  // 游标读 2 字节 → &v575
            sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
            sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
            sub_404A90((char *)&v565 + 3);  // 游标读 1 字节 → (char *)&v565 + 3
            sub_404A90(&v570);  // 游标读 1 字节 → &v570
            off_77F3FC(  // 控制台调试日志输出
              "ListIndex %d, MonsterUniqueId %d, MonsterIndex %d, MonsterLevel %d, MonsterType %d isBoxMonster %d boxIndex %d",  // 第 1 个实参：串 ListIndex %d, MonsterUniqueId %d, MonsterIndex %d, MonsterLevel %d, MonsterType %d isBoxMonster %d boxIndex %d
              HIBYTE(v580),  // 第 2 个实参
              (uint16_t)pObj12,  // 第 3 个实参：双字节 pObj12
              (uint16_t)v575,  // 第 4 个实参：双字节 v575
              HIBYTE(v574),  // 第 5 个实参
              HIBYTE(v572),  // 第 6 个实参
              HIBYTE(v565),  // 第 7 个实参
              v570);  // 第 8 个实参
            v210 = (void *)sub_488D90(  // sub_488D90：28 字节记录构造
                             HIBYTE(v580),  // 第 1 个实参
                             (uint16_t)pObj12,  // 第 2 个实参：双字节 pObj12
                             (uint16_t)v575,  // 第 3 个实参：双字节 v575
                             HIBYTE(v574),  // 第 4 个实参
                             HIBYTE(v572),  // 第 5 个实参
                             HIBYTE(v565) != 0,  // 第 6 个实参
                             v570);  // 第 7 个实参
            sub_489580(v210);  // 28 字节元素尾插 容量足够时经
            ++v209;  // v209 自增
          }
          while ( v209 < v581 );  // 调用 while
        }
        sub_4CE8A0((uint16_t)v579);  // 按 ID 解析对象
        v569 = 0;  // v569 复制自 0
        sub_404A90(&v569);  // 游标读 1 字节 → &v569
        v211 = v569;  // v211 复制自 v569
        if ( v569 != 0 )  // v569 不等于 0
        {
          off_77F3FC((char *)&byte_7294BC, v569);  // 控制台调试日志输出
          v211 = v569;  // v211 复制自 v569
        }
        v212 = 0;  // v212 复制自 0
        if ( v211 != 0 )  // v211 不等于 0
        {
          LODWORD(pObj32) = v566 + 5;
          do
          {
            HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
            pObj12 = 0;  // pObj12 复制自 0
            v574 = 0;  // v574 复制自 0
            *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
            v575 = 0;  // v575 复制自 0
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404AB0(&v574);  // 游标读 2 字节 → &v574
            sub_404AB0(netshort);  // 游标读 2 字节 → netshort
            sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
            sub_404AB0(&v575);  // 游标读 2 字节 → &v575
            off_77F3FC(  // 控制台调试日志输出
              (char *)&byte_729460,  // 第 1 个实参
              HIBYTE(v580),  // 第 2 个实参
              (uint16_t)v574,  // 第 3 个实参：双字节 v574
              netshort[0],  // 第 4 个实参
              pObj12,  // 第 5 个实参
              (uint16_t)v575);  // 第 6 个实参：双字节 v575
            v213 = (void *)sub_57A280(HIBYTE(v580), (uint16_t)v574, netshort[0], pObj12, (uint16_t)v575);  // 存 INI/字符串小桩
            sub_57A8F0(v213);  // 转发 57A880 + 655A40 收尾
            ++v212;  // v212 自增
          }
          while ( v212 < v569 );  // 调用 while
        }
      }
      v214 = *(uint32_t **)(*(uint32_t *)(pArg12[7] + 16) + 108);  // v214 存调用结果
      v214[123] = *(uint32_t *)v568;  // 数组元素写入
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )  // 条件判定
      {
        dword_99FB84 = v573;  // 全局 dword_99FB84 ← v573
        dword_99FB88 = HIBYTE(ArgList);  // 全局 dword_99FB88 ← HIBYTE(ArgList)
        sub_453B80(*v214, v573, HIBYTE(ArgList));  // 按钮点击登记 CLICK_BUTTON2 自证：记录 nArg2..nArg4 到 +220/+224/+228
      }
      else
      {
        sub_444E70(v573, HIBYTE(ArgList));  // fade 启动 + 播放广播 置 +20=1、记 +52/+56、复位 +24 与 +60；进临界区
        sub_699030(*(uint32_t *)(pArg12[7] + 16) + 164);  // 【clock_freeze(clk)】
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 31] case 30：地图对象收尾 —— sub_453B10/sub_445830/sub_444ED0 + sub_52D970 逐槽（16..31 步长 4） ──
    //   并 sub_57A340 复位时间通道（前 2456 行有 clock_freeze 调用）
    case 30:  // 【case 30】包类型分支
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )  // 条件判定
      {
        sub_453B10(pArg1[6]);  // 地图消失处理 MAP_DISAPPEAR 自证：置 +148/+165/+166 消失标记，经 dword_8F7A24+28 链换锚定对象并 vmt+124 通知主管理器， 末尾 424A40 解绑角色。
        sub_445830(1);  // 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
      }
      else
      {
        sub_444ED0(pArg1[7]);  // fade 收尾
      }
      sub_57A340(*(uint32_t *)(pArg12[7] + 16));  // std::string 析构辅助
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) != (uint16_t)word_8F7C10 )  // 条件判定
        sub_42B480(500, word_8F7C10 != word_8F7C14 ? 1000 : 5000);  // 倒计时启动
      v225 = 0;  // v225 复制自 0
      for ( i1 = 16; i1 < 32; i1 += 4 )  // 循环控制
      {
        v227 = *(uint32_t *)(i1 + dword_8F850C);  // v227 存调用结果
        if ( v227 != 0 && v227 != sub_41C1B0(dword_8F8500) )  // 条件判定
          sub_52D970(v225, 0);  // 光环事件辅助
        ++v225;  // v225 自增
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 32] case 31：★ 客户端 SEND RESULT 上报（发包 49）—— qmemcpy 复制 0x60 字节帧数据后逐字段 sub_41C0E0 ──
    //   sub_423200(49) 是发包 Begin；sub_423380 收尾提交（docs/24 §一：两步式发包 API）
    case 31:  // 【case 31】包类型分支
      sub_445830(0);  // 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
      *((uint8_t *)dword_99FD58 + 1004) = 0;  // 内存写入
      qmemcpy(&Buffer[32], (char *)dword_99FD58 + 768, 0x60u);  // 调用 qmemcpy
      v215 = sub_456390(0);  // 存 座位号查询
      ArgList = v215;  // ArgList 复制自 v215
      sub_423200(dword_8F7B08, 49);  // 【发送网络包API】
      v216 = 1.0 / (double)ArgList;  // v216 ← 表达式
      *(float *)&ArgList = v216;  // &ArgList 作浮点写 v216
      sub_41C0E0((uint64_t)(v216 * *(float *)&Buffer[32]));  // 发送缓冲写入
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[36]));  // 发送缓冲写入
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[40]));  // 发送缓冲写入
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[44]));  // 发送缓冲写入
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[48]));  // 发送缓冲写入
      sub_41C0E0((uint64_t)(*(float *)&ArgList * *(float *)&Buffer[52]));  // 发送缓冲写入
      sub_43B4C0((uint64_t)(*(float *)&Buffer[56] * *(float *)&ArgList));  // 发包字段
      v218 = sub_477260(dword_99FD58, v217);  // 存 加载进度查询
      sub_41C0E0((uint64_t)v218);  // 发送缓冲写入
      v220 = sub_477280(dword_99FD58, v219);  // 存 读 this+906 处 float 返回
      sub_41C0E0((uint64_t)v220);  // 发送缓冲写入
      v221 = sub_495C80(dword_99FD58);  // 存 百分比分档
      sub_41C0E0(v221);  // 发送缓冲写入
      sub_423380(dword_8F7B08);  // 发包 Commit
      v539 = sub_495C80(dword_99FD58);  // 存 百分比分档
      v223 = (uint64_t)sub_477280(dword_99FD58, v222);  // v223 存调用结果
      v517 = v223;  // v517 复制自 v223
      v508 = (uint64_t)sub_477260(dword_99FD58, HIDWORD(v223));  // v508 存调用结果
      off_77F3FC(  // 控制台调试日志输出
        "SEND RESULT : %d %d %d %d %d %d %d %d %d %d",  // 第 1 个实参：串 SEND RESULT : %d %d %d %d %d %d %d %d %d %d
        (int)(uint64_t)*(float *)&Buffer[32] / v215,  // 第 2 个实参
        (int)(uint64_t)*(float *)&Buffer[36] / v215,  // 第 3 个实参
        (int)(uint64_t)*(float *)&Buffer[40] / v215,  // 第 4 个实参
        (int)(uint64_t)*(float *)&Buffer[44] / v215,  // 第 5 个实参
        (int)(uint64_t)*(float *)&Buffer[48] / v215,  // 第 6 个实参
        (int)(uint64_t)*(float *)&Buffer[52] / v215,  // 第 7 个实参
        (int)(uint64_t)*(float *)&Buffer[56] / v215,  // 第 8 个实参
        v508,  // 第 9 个实参
        v517,  // 第 10 个实参
        v539);  // 第 11 个实参
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )  // 虚表 +120 调用
      {
        v540 = sub_4617A0(dword_99FB8C);  // 存 称号路阶文本拼接 nArg2 为 1/2/3 分别取 EXPERT ROAD、MASTER ROAD、KING ROAD 三段称号
        v224 = (const char *)sub_422E70(646);  // 存 CStringManager::getStr 取本地化串
        sprintf(&Destination, v224, v540);  // 调用 sprintf
        sub_43BEE0(&Destination, -6567706, 0, -1);  // 【播报上屏】
      }
      sub_57A330(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)netshort + 28) + 16));  // 字符串小桩
      return 1;  // 返回 1（已处理该包）
    // ── [段 33] case 32：★ 角色死亡/金币插入（ServerId/DieState + COIN_INSERT，181 行）—— PVP/战场模式核心 ──
    //   sub_424310/sub_424A40/sub_425050 镜头与结算联动；金币 INSERT 播报 + 观战切人
    case 32:  // 【case 32】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v580 = 0;  // v580 复制自 0
      sub_404AB0(&v580);  // 游标读 2 字节 → &v580
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("ServerId %d, DieState %d", (uint16_t)v580, HIBYTE(ArgList));  // 控制台调试日志输出
      v228 = sub_456390(1);  // 存 座位号查询
      v229 = *(uint32_t *)dword_8F8520;  // v229 ← 表达式
      HIDWORD(pObj32) = v228;
      v230 = (*(int (/*thiscall*/ **)(int))(v229 + 120))(dword_8F8520);  // 虚表 +120 调用
      v231 = *(uint32_t **)(v230 + 104);  // v231 存调用结果
      *(uint32_t *)netshort = v230;  // 指针 netshort 写 v230
      pObj122 = 0;  // pObj122 复制自 0
      v566 = v231;  // v566 复制自 v231
      pObj12 = 0;  // pObj12 复制自 0
      v233 = (int *)(dword_8F850C + 16);  // v233 存调用结果
      while ( 1 )  // 循环控制
      {
        pObj323 = *v233;  // 取 v233 首字段
        LODWORD(pObj32) = *v233;
        if ( (uint32_t)pObj32 != 0 && *(uint16_t *)(pObj323 + 4) == (uint16_t)v580 && *(uint32_t *)(pObj323 + 196) != 0 )  // 条件判定
          break;
        ++pObj122;  // pObj122 自增
        ++v233;  // v233 自增
        if ( pObj122 >= 4 )  // 条件判定
        {
          pObj12 = pObj122;  // pObj12 复制自 pObj122
          goto LABEL_460;  // 转到 LABEL_460
        }
      }
      v235 = *(int **)(pObj323 + 196);  // v235 存调用结果
      pObj12 = pObj122;  // pObj12 复制自 pObj122
      if ( HIBYTE(ArgList) == 1 )  // ArgList 高字节 == 1
      {
        if ( (uint8_t)sub_45E680(v235) != 0 )  // 条件判定
        {
          sub_45F1E0(v235);  // 对象注销/退场
          if ( (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235) != 0 )  // 虚表 +1120 调用
          {
            v236 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235);  // 虚表 +1120 调用
            sub_45F1E0(v236);  // 对象注销/退场
          }
        }
        (*(void (/*thiscall*/ **)(int *))(*v235 + 1020))(v235);  // 虚表 +1020 调用
        (*(void (/*thiscall*/ **)(int *, int))(*v235 + 1200))(v235, 1);  // 虚表 +1200 调用
        v237 = *v235;  // 取 v235 首字段
        v238 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*v235 + 740))(v235, 0, 1);  // 虚表 +740 调用
        (*(void (/*thiscall*/ **)(int *, int))(v237 + 732))(v235, v238);  // 虚表 +732 调用
        v239 = *v235;  // 取 v235 首字段
        v240 = (*(int (/*thiscall*/ **)(int *, int))(*v235 + 756))(v235, 1);  // 虚表 +756 调用
        (*(void (/*thiscall*/ **)(int *, int))(v239 + 748))(v235, v240);  // 虚表 +748 调用
        sub_45FE80(273, (uint16_t)v580, v235, 0, 0);  // 对象注册
        if ( (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235) != 0 )  // 虚表 +1120 调用
        {
          v241 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1120))(v235);  // 虚表 +1120 调用
          sub_45FE80(65, (uint16_t)v580, v241, 0, 0);  // 对象注册
        }
        pObj8 = *(uint32_t *)(*(uint32_t *)netshort + 52);  // pObj8 存调用结果
        if ( pObj8 != 0 )  // pObj8 不等于 0
        {
          v243 = *v235;  // 取 v235 首字段
          v244 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj8 + 124))(pObj8, 0);  // 虚表 +124 调用
          v245 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj8 + 120))(pObj8, v244);  // 虚表 +120 调用
          (*(void (/*thiscall*/ **)(int *, int))(v243 + 112))(v235, v245);  // 虚表 +112 调用
          pObj323 = pObj32;  // pObj323 复制自 pObj32
        }
        else
        {
          v246 = (*(int (/*thiscall*/ **)(int *))(*v235 + 120))(v235);  // 虚表 +120 调用
          v247 = *(uint32_t *)(*(uint32_t *)netshort + 44);  // v247 存调用结果
          v248 = *v235;  // 取 v235 首字段
          v575 = v246;  // v575 复制自 v246
          LODWORD(pObj32) = (*(int (/*thiscall*/ **)(int *))(v248 + 124))(v235);  // 虚表 +124 调用
          if ( (int)pObj32 >= sub_425050(v247) )  // 条件判定
            v249 = sub_425050(*(uint32_t *)(*(uint32_t *)netshort + 44));  // 存 总宽换算 224 ×
          else
            v249 = (*(int (/*thiscall*/ **)(int *))(*v235 + 124))(v235);  // 虚表 +124 调用
          v250 = *v235;  // 取 v235 首字段
          *(uint32_t *)v568 = v249;  // 指针 v568 写 v249
          (*(void (/*thiscall*/ **)(int *, int *, char *, int, int, int, int, int))(v250 + 140))(  // 虚表 +140 调用
            v235,  // 第 1 个实参
            &v575,  // 第 2 个实参：地址 &v575
            v568,  // 第 3 个实参
            v575,  // 第 4 个实参
            v249,  // 第 5 个实参
            640,  // 第 6 个实参：常量 640
            1,  // 第 7 个实参：常量 1
            1);  // 第 8 个实参：常量 1
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*v235 + 112))(v235, v575, *(uint32_t *)v568, 0);  // 虚表 +112 调用
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v235 + 308))(v235) != 0 )  // 虚表 +308 调用
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v235 + 580))(  // 虚表 +580 调用
            v235,  // 第 1 个实参
            48001,  // 第 2 个实参：常量 48001
            1,  // 第 3 个实参：常量 1
            0,  // 第 4 个实参：常量 0
            0,  // 第 5 个实参：常量 0
            0,  // 第 6 个实参：常量 0
            0,  // 第 7 个实参：常量 0
            0,  // 第 8 个实参：常量 0
            4,  // 第 9 个实参：常量 4
            0,  // 第 10 个实参：常量 0
            0,  // 第 11 个实参：常量 0
            0);  // 第 12 个实参：常量 0
        pObj10 = dword_8F7C04;  // pObj10 复制自 dword_8F7C04
        if ( (int *)dword_8F7C04 == v235 )  // 条件判定
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*v235 + 560))(v235, 0, 0, 0, 0);  // 虚表 +560 调用
          (*(void (/*thiscall*/ **)(int *))(*v235 + 564))(v235);  // 虚表 +564 调用
          sub_57A2F0(*(uint32_t *)netshort);  // std::string 辅助
          pObj10 = dword_8F7C04;  // pObj10 复制自 dword_8F7C04
        }
        if ( pObj10 != 0 )  // pObj10 不等于 0
        {
          v252 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 376))(pObj10);  // 虚表 +376 调用
          if ( v252 == (*(int (/*thiscall*/ **)(int *))(*v235 + 376))(v235) )  // 虚表 +376 调用
            sub_57A310(*(uint32_t *)netshort);  // std::string 辅助 2
        }
        v541 = unknown_libname_2(pObj323 + 16);  // CRT 内部辅助调用
        v253 = (const char *)sub_422E70(647);  // 存 CStringManager::getStr 取本地化串
        sprintf(&Destination, v253, v541);  // 调用 sprintf
        sub_43BEE0(&Destination, -6567706, 0, -1);  // 【播报上屏】
        v254 = (*(int (/*thiscall*/ **)(int *))(*v235 + 1216))(v235);  // 虚表 +1216 调用
        sub_495DA0(v254);  // 96 字节元素双槽清零
        sub_49C620(1, 1, 0);  // 命令下发包装
        sub_49C5F0(1, 0, 0, 1500);  // 命令记录写入包装
        sub_432EA0("COIN_INSERT", -1, 0, 0);  // 音效播放包装
      }
      else
      {
        if ( SHIDWORD(pObj32) > 1 )  // 条件判定
          sub_45F1E0(v235);  // 对象注销/退场
        v542 = unknown_libname_2(pObj323 + 16);  // CRT 内部辅助调用
        v256 = (const char *)sub_422E70(648);  // 存 CStringManager::getStr 取本地化串
        sprintf(&Destination, v256, v542);  // 调用 sprintf
        sub_43BEE0(&Destination, -6567706, 0, -1);  // 【播报上屏】
      }
      LOBYTE(v255) = HIBYTE(ArgList) == 0;  // 字节提取赋值
      (*(void (/*thiscall*/ **)(int *, int))(*v235 + 1192))(v235, v255);  // 虚表 +1192 调用
      pObj122 = pObj12;  // pObj122 复制自 pObj12
LABEL_460:
      if ( pObj122 == 4 )  // pObj122 等于 4
        off_77F3FC((char *)&byte_7293E8);  // 控制台调试日志输出
      if ( (int)sub_456390(1) <= 0 )  // 条件判定
      {
        if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 608) + 4) == 0  // 条件判定
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0 )  // 第 1 个实参：地址 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0
        {
          sub_49BDB0(2);  // COUNT_DOWN 设置
          goto LABEL_478;  // 转到 LABEL_478
        }
      }
      else
      {
        for ( i2 = 16; i2 < 32; i2 += 4 )  // 循环控制
        {
          v258 = *(uint32_t *)(i2 + dword_8F850C);  // v258 存调用结果
          if ( v258 != 0 )  // v258 不等于 0
          {
            pObj16 = *(uint32_t *)(v258 + 196);  // 读 v258+196 处 4 字节
            if ( pObj16 != 0  // 条件判定
              && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj16 + 1196))(pObj16) != 0  // 第 1 个实参：地址 && (*(uint8_t (·thiscall· **)(int))(*(uint32_t *)pObj16 + 1196))(pObj16) != 0
              && (uint8_t)sub_45E680(pObj16) != 0 )  // 第 1 个实参：地址 && (uint8_t)sub_45E680(pObj16) != 0
            {
              sub_45F1E0(pObj16);  // 对象注销/退场
            }
          }
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0  // 虚表 +1196 调用
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 608) + 4) == 0  // 第 1 个实参：地址 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 608) + 4) == 0
          && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0 )  // 第 1 个实参：地址 && *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4) == 0
        {
          sub_49BDB0(1);  // COUNT_DOWN 设置
LABEL_478:
          v260 = sub_424310(dword_8F7C04);  // 存 当前目标角色选取 模式 3：pArg2/dword_8F850C 槽
          sub_424A40(v260);  // 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
          return 1;  // 返回 1（已处理该包）
        }
      }
      sub_49BDB0(0);  // COUNT_DOWN 设置
      goto LABEL_478;  // 转到 LABEL_478
    // ── [段 34] case 33：疲劳值回报（Stamina）—— sub_57A2B0 写入 ──
    case 33:  // 【case 33】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("Stamina %d", HIBYTE(ArgList));  // 控制台调试日志输出
      pObj2 = dword_8F7C04;  // pObj2 复制自 dword_8F7C04
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
      {
        if ( HIBYTE(ArgList) != 100 )  // ArgList 高字节 != 100
        {
          sub_57A2B0(*(uint32_t *)(*(uint32_t *)(pArg12[7] + 16) + 108));  // 字符串小桩
          pObj2 = dword_8F7C04;  // pObj2 复制自 dword_8F7C04
        }
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 1060))(pObj2, HIBYTE(ArgList));  // 虚表 +1060 调用
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);  // 虚表 +1056 调用
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 35] case 34：★ 评价结算（Rank/NewStyle/NewTechnic/NewHit/NewRank）—— HUD 评价横幅 ──
    //   对应 docs/21 §1.4 三轴评价（HK_STYLE/HK_TECHNIC）；sub_495C80/sub_49BDB0 写横幅
    case 34:  // 【case 34】包类型分支
      v262 = *((uint8_t **)dword_8F8528 + 608);  // v262 存调用结果
      sub_4772A0(0);  // 结算事件：M_RESULT 打开结算界面
      sub_45A420(0);  // CNRDReward 状态机入口
      sub_49BDB0(0);  // COUNT_DOWN 设置
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
      sub_404A90((char *)&v565 + 3);  // 游标读 1 字节 → (char *)&v565 + 3
      off_77F3FC(  // 控制台调试日志输出
        "Rank %d, NewStyle %d, NewTechnic %d, NewHit %d, NewRank %d",  // 第 1 个实参：串 Rank %d, NewStyle %d, NewTechnic %d, NewHit %d, NewRank %d
        HIBYTE(ArgList),  // 第 2 个实参
        HIBYTE(v580),  // 第 3 个实参
        HIBYTE(v574),  // 第 4 个实参
        HIBYTE(v572),  // 第 5 个实参
        HIBYTE(v565));  // 第 6 个实参
      v263 = sub_495C80(dword_99FD58);  // 存 百分比分档
      if ( HIBYTE(ArgList) == v263 )  // ArgList 高字节 == v263
      {
        v262[240] = HIBYTE(v580) != 0;  // 数组元素写入
        v262[241] = HIBYTE(v574) != 0;  // 数组元素写入
        v262[242] = HIBYTE(v572) != 0;  // 数组元素写入
      }
      else
      {
        v264 = sub_495C80(dword_99FD58);  // 存 百分比分档
        off_77F3FC(aCriticalEnumNo, HIBYTE(ArgList), v264);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 36] case 35：★ 任务物品获得（GainedQuestItemSlot + SlotIndex/ItemIndex/ItemData/Durability，106 行） ──
    //   sub_45A750/sub_4772A0 任务与背包刷新
    case 35:  // 【case 35】包类型分支
      v265 = *((uint32_t **)dword_8F8528 + 608);  // v265 存调用结果
      v266 = *((uint32_t *)dword_8F8528 + 609);  // v266 存调用结果
      v575 = 0;  // v575 复制自 0
      pObj12 = 0;  // pObj12 复制自 0
      v579 = 0;  // v579 复制自 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v571 = 0;  // v571 复制自 0
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      sub_404AD0((char *)&pObj32 + 4);  // 游标读 4 字节 → (char *)&pObj32 + 4
      sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
      sub_404AD0(v568);  // 游标读 4 字节 → v568
      sub_404AD0(&v575);  // 游标读 4 字节 → &v575
      sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
      sub_404AD0(&v579);  // 游标读 4 字节 → &v579
      sub_404AD0(netshort);  // 游标读 4 字节 → netshort
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      off_77F3FC(  // 控制台调试日志输出
        "GainedSp %d, GainedExp %d, GainedRankBonusExp %d, gainedPartyBonusExp %d gainedAvatarBonusExp %d\n"  // 第 1 个实参：串 GainedSp %d, GainedExp %d, GainedRankBonusExp %d, gainedPartyBonusExp %d gainedAvatarBonusExp %d\n
        "\t\t\t\t   gainedBurningTimeExp %d gainedPremiumExp %d gainedMatchedChannelExp %d gainedMemberExp %d",  // 第 1 个实参：串 \t\t\t\t gainedBurningTimeExp %d gainedPremiumExp %d gainedMatchedChannelExp %d gainedMemberExp %d
        HIBYTE(v574),  // 第 2 个实参
        HIDWORD(pObj32),  // 第 3 个实参
        (uint32_t)pObj32,  // 第 4 个实参
        *(uint32_t *)v568,  // 第 5 个实参
        v575,  // 第 6 个实参
        pObj12,  // 第 7 个实参
        v579,  // 第 8 个实参
        *(uint32_t *)netshort,  // 第 9 个实参
        v571);  // 第 10 个实参
      v265[58] = HIDWORD(pObj32) - *(uint32_t *)v568;  // 数组元素写入
      v265[51] = pObj32;  // 数组 v265[51] ← pObj32
      v265[52] = *(uint32_t *)v568;  // 数组元素写入
      v265[53] = v575;  // 数组 v265[53] ← v575
      v265[56] = pObj12;  // 数组 v265[56] ← pObj12
      v265[54] = v579;  // 数组 v265[54] ← v579
      v265[55] = *(uint32_t *)netshort;  // 数组元素写入
      v265[57] = v571;  // 数组 v265[57] ← v571
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      off_77F3FC("GainedQuestItemSlot %d", HIBYTE(v580));  // 控制台调试日志输出
      v566 = nullptr;  // v566 复制自 nullptr
      if ( HIBYTE(v580) != 0 )  // v580 高字节 != 0
      {
        do
        {
          sub_404AB0((char *)&v572 + 2);  // 游标读 2 字节 → (char *)&v572 + 2
          sub_404AB0((char *)&v565 + 2);  // 游标读 2 字节 → (char *)&v565 + 2
          sub_404AD0(&i5);  // 游标读 4 字节 → &i5
          sub_404AB0((char *)&v567 + 2);  // 游标读 2 字节 → (char *)&v567 + 2
          off_77F3FC(  // 控制台调试日志输出
            "SlotIndex %d, ItemIndex %d, ItemData %d, Durability %d",  // 第 1 个实参：串 SlotIndex %d, ItemIndex %d, ItemData %d, Durability %d
            HIWORD(v572),  // 第 2 个实参
            HIWORD(v565),  // 第 3 个实参
            i5,  // 第 4 个实参
            HIWORD(v567));  // 第 5 个实参
          pObj30 = sub_44A980(HIWORD(v572));  // 存 带界索引 getter nArg2 ≥ [2]
          if ( pObj30 != 0 )  // pObj30 不等于 0
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj30 + 60))(pObj30, HIWORD(v565)) != 0 )  // 虚表 +60 调用
              (*(void (/*thiscall*/ **)(int, void *))(*(uint32_t *)pObj30 + 48))(pObj30, i5);  // 虚表 +48 调用
            else
              off_77F3FC(aCriticalError_22, HIWORD(v572));  // 控制台调试日志输出
          }
          else
          {
            v268 = sub_522300((void *)HIWORD(v565), (int)i5, 0, 0, HIWORD(v567), 1);  // 存 ★ PO 工厂分发器
            sub_484F40(HIWORD(v572), v268, 1);  // 技能槽装载
          }
          v566 = (uint32_t *)((char *)v566 + 1);  // v566 存调用结果
        }
        while ( (int)v566 < HIBYTE(v580) );  // 调用 while
      }
      v269 = 0;  // v269 复制自 0
      i5 = (void *)(v266 + 564);  // i5 存调用结果
      do
      {
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        off_77F3FC("UseGainedItemSlot %d", HIBYTE(ArgList));  // 控制台调试日志输出
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          ++*(uint32_t *)(v266 + 436);  // 调用语句
          v270 = 0;  // v270 复制自 0
          if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
          {
            do
            {
              sub_404AB0((char *)&v572 + 2);  // 游标读 2 字节 → (char *)&v572 + 2
              sub_404AD0(&v565);  // 游标读 4 字节 → &v565
              off_77F3FC("ItemIndex %d, StackNumber %d", HIWORD(v572), v565);  // 控制台调试日志输出
              sub_45A750(HIWORD(v572), v565, v269);  // 向第 nArg4 组追加一条 52 字节玩家条目 默认
              ++v270;  // v270 自增
            }
            while ( v270 < HIBYTE(ArgList) );  // 调用 while
          }
        }
        else
        {
          *(uint32_t *)i5 = -1;  // 内存写入
        }
        ++v269;  // v269 自增
        i5 = (char *)i5 + 4;  // i5 ← 表达式
      }
      while ( v269 < 4 );  // 调用 while
      v271 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚表 +120 调用
      sub_47BBE0(**(uint32_t **)(v271 + 108), dword_99FB8C);  // 触发条件评估器：遍历条件对象
      sub_4772A0(1);  // 结算事件：M_RESULT 打开结算界面
      return 1;  // 返回 1（已处理该包）
    // ── [段 37] case 36：疲劳上限回报（Fatigue/FatigueMax）──
    case 36:  // 【case 36】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      off_77F3FC("Fatigue %d, FatigueMax %d", (uint16_t)ArgList, (uint16_t)i5);  // 控制台调试日志输出
      word_8F7C10 = ArgList;  // 全局 word_8F7C10 ← ArgList
      word_8F7C14 = (int16_t)i5;  // 全局 word_8F7C14 ← (int16_t)i5
      return 1;  // 返回 1（已处理该包）
    // ── [段 38] case 37：★ 升级/经验（Level/Exp1/Exp2/Exp3/Sp + SP_GET，99 行）—— sub_495310 速率/动画联动 ──
    case 37:  // 【case 37】包类型分支
      LOBYTE(ArgList) = 0;  // 低字节写 ArgList ← 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v579 = 0;  // v579 复制自 0
      v571 = 0;  // v571 复制自 0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404A90(&ArgList);  // 游标读 1 字节 → &ArgList
      sub_404AD0(&v579);  // 游标读 4 字节 → &v579
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      sub_404AD0(&i5);  // 游标读 4 字节 → &i5
      sub_404AB0(netshort);  // 游标读 2 字节 → netshort
      off_77F3FC("Level %d, Exp1 %d, Exp2 %d, Exp3 %d, Sp %d", (uint8_t)ArgList, v579, v571, i5, netshort[0]);  // 控制台调试日志输出
      pObj17 = dword_8F7C04;  // pObj17 复制自 dword_8F7C04
      v273 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
      v274 = sub_41A5E0(v273 + 53);  // 存 crypt4byte 解密校验
      if ( v274 != (uint8_t)ArgList )  // 条件判定
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 15, 2);  // 虚表 +8 调用
        v275 = *(uint32_t *)dword_8F8520;  // v275 ← 表达式
        v276 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj17 + 48))(pObj17);  // 虚表 +48 调用
        (*(void (/*thiscall*/ **)(int, int))(v275 + 36))(dword_8F8520, v276);  // 虚表 +36 调用
        v277 = *(uint32_t *)dword_8F8520;  // v277 ← 表达式
        v278 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj17 + 52))(pObj17);  // 虚表 +52 调用
        (*(void (/*thiscall*/ **)(int, int))(v277 + 36))(dword_8F8520, v278);  // 虚表 +36 调用
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v274);  // 虚表 +32 调用
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);  // 虚表 +32 调用
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚表 +60 调用
        sub_41C1B0(dword_8F8500);  // 按全局键 word_77F804 查表取对象
        sub_41C150((uint8_t)ArgList);  // crypt4byte 初始化转发
        if ( (uint8_t)ArgList > v274 )  // 条件判定
          *(uint8_t *)(dword_8F8500 + 16) = 1;  // dword_8F8500+16 写字节 1
      }
      LODWORD(v279) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj17 + 1032))(pObj17);  // 虚表 +1032 调用
      HIDWORD(v279) = v571;
      v280 = v579 - *(uint32_t *)(v279 + 48);  // v280 存调用结果
      if ( v280 <= 0 )  // 条件判定
      {
        if ( v280 < 0 )  // 条件判定
        {
          v285 = (const char *)sub_422E70(651);  // 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v285, -v280);  // 格式化写入 Buffer
          sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
        }
      }
      else
      {
        if ( v571 != 0 )  // v571 不等于 0
        {
          if ( i5 != nullptr )  // i5 不等于 nullptr
          {
            v518 = __PAIR64__((unsigned int)i5, v571);  // v518 存调用结果
            v509 = v280 - (uint32_t)i5 - v571;  // v509 ← 表达式
            v281 = (const char *)sub_422E70(1519);  // 存 CStringManager::getStr 取本地化串
            sprintf(Buffer, v281, v280, v509, v518);  // 格式化写入 Buffer
          }
          else
          {
            LODWORD(v279) = v280 - v571;
            v519 = v279;  // v519 复制自 v279
            v282 = (const char *)sub_422E70(1517);  // 存 CStringManager::getStr 取本地化串
            sprintf(Buffer, v282, v280, v519);  // 格式化写入 Buffer
          }
        }
        else if ( i5 != nullptr )
        {
          v543 = i5;  // v543 复制自 i5
          v520 = v280 - (uint32_t)i5 - v571;  // v520 ← 表达式
          v283 = (const char *)sub_422E70(1518);  // 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v283, v280, v520, v543);  // 格式化写入 Buffer
        }
        else
        {
          v284 = (const char *)sub_422E70(1516);  // 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v284, v280);  // 格式化写入 Buffer
        }
        sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
        if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1260))(  // 虚表 +1260 调用
            dword_8F7C04,  // 第 1 个实参
            0,  // 第 2 个实参：常量 0
            v280,  // 第 3 个实参
            0,  // 第 4 个实参：常量 0
            0,  // 第 5 个实参：常量 0
            0,  // 第 6 个实参：常量 0
            0,  // 第 7 个实参：常量 0
            0,  // 第 8 个实参：常量 0
            0);  // 第 9 个实参：常量 0
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pObj17 + 1036))(pObj17, v579, (uint8_t)ArgList);  // 虚表 +1036 调用
      if ( netshort[0] > Value )  // 条件判定
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj17 + 1232))(pObj17, 1);  // 虚表 +1232 调用
        sub_57A430(1);  // std::string 辅助 6
        v286 = sub_422E70(652);  // 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v286, -6567706, 0, -1);  // 【播报上屏】
        sub_432EA0("SP_GET", -1, 0, 0);  // 音效播放包装
      }
      Value = netshort[0];  // Value ← 表达式
      return 1;  // 返回 1（已处理该包）
    // ── [段 39] case 38：★ 怪物击杀回报（MonsterUniqueId/ItemNumber + isWarRoom + lastAttackerServerId/addKP/displayExp，163 行） ──
    //   sub_45EBE0 取怪物 → sub_43BEE0 播报 → 经验/掉落结算（docs/21 §1.1 战斗链尾段）
    case 38:  // 【case 38】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v581 = -1;  // 局部 v581 → -1
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      sub_404AB0(netshort);  // 游标读 2 字节 → netshort
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("MonsterUniqueId %d, ItemNumber %d", netshort[0], HIBYTE(ArgList));  // 控制台调试日志输出
      v287 = pArg12[3];  // v287 ← 表达式
      if ( v287 == 3 )  // v287 等于 3
      {
        v288 = pArg12[7];  // v288 ← 表达式
      }
      else
      {
        if ( v287 != 6 )  // v287 不等于 6
          goto LABEL_525;  // 转到 LABEL_525
        v288 = pArg12[10];  // v288 ← 表达式
      }
      if ( *(uint32_t *)(*(uint32_t *)(v288 + 16) + 104) != 0 )  // 条件判定
      {
        v289 = sub_45EBE0(529, netshort[0]);  // 存 id 对 → 对象查找
        v290 = (uint32_t *)__RTDynamicCast(
                           v289,  // 第 1 个实参
                           0,  // 第 2 个实参：常量 0
                           &CNRDObject `RTTI Type Descriptor',  // 第 3 个实参：地址 &CNRDObject `RTTI Type Descriptor」
                           &IRDMonster `RTTI Type Descriptor',  // 第 3 个实参：地址 &IRDMonster `RTTI Type Descriptor」
                           0);  // 第 3 个实参：常量 0
        if ( v290 == nullptr )  // v290 等于 nullptr
          off_77F3FC(aCriticalError_23, netshort[0]);  // 控制台调试日志输出
        srand(10 * (HIBYTE(ArgList) + 100 * netshort[0]));  // 调用 srand
        rand();  // 调用 rand
        LODWORD(pObj32) = 0;
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          do
          {
            *(uint32_t *)v568 = 0;  // 指针 v568 写 0
            pObj12 = 0;  // pObj12 复制自 0
            v571 = 0;  // v571 复制自 0
            i5 = (void *)0xFFFF;  // i5 ← 表达式
            v575 = 0;  // v575 复制自 0
            sub_404AB0(v568);  // 游标读 2 字节 → v568
            sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
            sub_404AD0(&v575);  // 游标读 4 字节 → &v575
            sub_404AB0(&v571);  // 游标读 2 字节 → &v571
            sub_404AB0(&i5);  // 游标读 2 字节 → &i5
            off_77F3FC(  // 控制台调试日志输出
              "ItemUniqueId %d, ItemIndex %d, Data %u, Durability %d rootableServerId %d",  // 第 1 个实参：串 ItemUniqueId %d, ItemIndex %d, Data %u, Durability %d rootableServerId %d
              *(uint16_t *)v568,  // 第 2 个实参
              (uint16_t)pObj12,  // 第 3 个实参：双字节 pObj12
              v575,  // 第 4 个实参
              (uint16_t)v571,  // 第 5 个实参：双字节 v571
              (uint16_t)i5);  // 第 6 个实参：双字节 i5
            if ( v290 != nullptr )  // v290 不等于 nullptr
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v290 + 1188))(  // 虚表 +1188 调用
                v290,  // 第 1 个实参
                HIBYTE(ArgList),  // 第 2 个实参
                (uint16_t)pObj12,  // 第 3 个实参：双字节 pObj12
                v575,  // 第 4 个实参
                *(uint16_t *)v568,  // 第 5 个实参
                (uint16_t)v571,  // 第 6 个实参：双字节 v571
                (uint16_t)i5);  // 第 7 个实参：双字节 i5
            LODWORD(pObj32) = pObj32 + 1;
          }
          while ( (int)pObj32 < HIBYTE(ArgList) );  // 调用 while
        }
        sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
        off_77F3FC("isWarRoom %d", SHIBYTE(v580));  // 控制台调试日志输出
        if ( HIBYTE(v580) != 0 && dword_99FF08 != 0 && v290 != nullptr )  // 条件判定
        {
          i5 = (void *)0xFFFF;  // i5 ← 表达式
          v574 = 0;  // v574 复制自 0
          *(uint32_t *)v568 = 0;  // 指针 v568 写 0
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          sub_404AB0(&v574);  // 游标读 2 字节 → &v574
          sub_404AD0(v568);  // 游标读 4 字节 → v568
          off_77F3FC(  // 控制台调试日志输出
            "lastAttackerServerId %d addKP %d displayExp %d",  // 第 1 个实参：串 lastAttackerServerId %d addKP %d displayExp %d
            (uint16_t)i5,  // 第 2 个实参：双字节 i5
            (uint16_t)v574,  // 第 3 个实参：双字节 v574
            *(uint32_t *)v568);  // 第 4 个实参
          dword_99FF082 = dword_99FF08;  // 全局 dword_99FF082 ← dword_99FF08
          v571 = -1;  // 局部 v571 → -1
          v575 = sub_48FB60((uint16_t)i5, &v571);  // 存 槽按键查找
          if ( v575 != 0 )  // v575 不等于 0
          {
            *(uint32_t *)(dword_99FF082 + 4 * v571 + 80) += (uint16_t)v574;
            *(uint32_t *)(dword_99FF082 + 4 * v571 + 112) += (uint16_t)v574;
            sub_4632D0(*((uint32_t *)dword_8F8528 + 4));  // 席位表快照与排序 dword_99FF08 表 +80 起 8 个值写入 this+335 起
            LODWORD(pObj32) = *(uint32_t *)(v575 + 196);  // 调用 LODWORD
            if ( (uint32_t)pObj32 != 0 )  // 条件判定
            {
              v292 = *(uint32_t *)pObj32;  // v292 ← 表达式
              v293 = (*(int (/*thiscall*/ **)(uint32_t *))(*v290 + 128))(v290);  // 虚表 +128 调用
              v294 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 124))(v290, v293);  // 虚表 +124 调用
              v295 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 120))(v290, v294);  // 虚表 +120 调用
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(v292 + 1264))(  // 虚表 +1264 调用
                pObj32,  // 第 1 个实参
                (uint16_t)v574,  // 第 2 个实参：双字节 v574
                0,  // 第 3 个实参：常量 0
                1,  // 第 4 个实参：常量 1
                v295);  // 第 5 个实参
              v296 = *v290;  // 取 v290 首字段
              v297 = **(uint32_t **)(v575 + 196);  // v297 存调用结果
              LODWORD(pObj32) = *(uint32_t *)(v575 + 196);  // 调用 LODWORD
              v298 = (*(int (/*thiscall*/ **)(uint32_t *))(v296 + 128))(v290);  // 虚表 +128 调用
              v299 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 124))(v290, v298);  // 虚表 +124 调用
              v300 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v290 + 120))(v290, v299);  // 虚表 +120 调用
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(v297 + 1260))(  // 虚表 +1260 调用
                pObj32,  // 第 1 个实参
                0,  // 第 2 个实参：常量 0
                *(uint32_t *)v568,  // 第 3 个实参
                0,  // 第 4 个实参：常量 0
                0,  // 第 5 个实参：常量 0
                1,  // 第 6 个实参：常量 1
                v300);  // 第 7 个实参
            }
            v544 = sub_4633B0(v290);  // 存 std::string 取数据指针
            v521 = unknown_libname_2(v575 + 16);  // CRT 内部辅助调用
            v301 = (const char *)sub_422E70(1930);  // 存 CStringManager::getStr 取本地化串
            sprintf(Format, v301, v521, v544);  // 格式化写入 Format
            sub_43BEE0(Format, -13435036, 0, -1);  // 【播报上屏】
          }
        }
        else
        {
          sub_404A90(&v581);  // 游标读 1 字节 → &v581
          off_77F3FC("championKeyCount %d", (char)v581);  // 控制台调试日志输出
        }
        if ( v290 != nullptr )  // v290 不等于 nullptr
        {
          if ( v581 != 0xFF )  // v581 不等于 0xFF
          {
            off_77F3FC((char *)&byte_729010, *(uint32_t *)dword_99FB70, (char)v581);  // 控制台调试日志输出
            if ( (char)v581 > *(int *)dword_99FB70 )  // 条件判定
            {
              *(uint32_t *)dword_99FB70 = (char)v581;  // 内存写入
              *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 1140) = 1;  // 内存写入
              v302 = *((uint32_t *)dword_8F8528 + 4) + 1128;  // v302 ← 表达式
              *(uint8_t *)(v302 + 13) = 0;  // v302+13 写字节 0
              *(uint8_t *)(v302 + 14) = 0;  // v302+14 写字节 0
              sub_698F90(0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
              sub_496BD0(v290);  // 异常演出节点入链
            }
          }
          if ( v290[1943] == 3 )  // 条件判定
            sub_496BD0(v290);  // 异常演出节点入链
          v303 = *(uint32_t **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108);  // 虚表 +120 调用
          v304 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v290 + 340))(v290);  // 虚表 +340 调用
          sub_47BEE0(*v303, dword_99FB8C, *v304);  // 批量关断：型别
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v290 + 84))(v290, 0);  // 虚表 +84 调用
          v545 = netshort[0];  // v545 ← 表达式
          v305 = sub_4633B0(v290);  // 存 std::string 取数据指针
          off_77F3FC((char *)&byte_728FD0, v305, v545);  // 控制台调试日志输出
          if ( pArg12[3] == 6 )  // 条件判定
            sub_461520(*((uint32_t *)dword_8F8528 + 4));  // 对战计数与 2.6 秒定时 置 +1416=1，this+1404 定时器 2600ms
        }
        return 1;  // 返回 1（已处理该包）
      }
LABEL_525:
      off_77F3FC(aErrorD_1, pArg12[3]);  // 控制台调试日志输出
      return 1;  // 返回 1（已处理该包）
    // ── [段 40] case 39：★ 掉落分配/掷骰（ItemUniqueId/ServerId + [%d] DICE %d，150 行） ──
    //   sub_41C1B0/sub_429830 定位 → 骰子播报 → 物品归属写盘
    case 39:  // 【case 39】包类型分支
      v306 = 0;  // v306 复制自 0
      v571 = 0;  // v571 复制自 0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AB0(&v571);  // 游标读 2 字节 → &v571
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      off_77F3FC("ItemUniqueId %d, ServerId %d", (uint16_t)v571, (uint16_t)i5);  // 控制台调试日志输出
      if ( (uint16_t)i5 == (uint16_t)word_77F804 )  // 低 16 位比较 i5 == word_77F804
        sub_484FF0(dword_8F852C);  // 4 字节列表尾部弹出
      v307 = sub_45EBE0(289, (uint16_t)v571);  // 存 id 对 → 对象查找
      pObj25 = __RTDynamicCast(v307, 0, &CNRDObject `RTTI Type Descriptor', &CNRDItemObject `RTTI Type Descriptor', 0);  // pObj25 存调用结果
      pObj252 = pObj25;  // pObj252 复制自 pObj25
      HIDWORD(pObj32) = pObj25;
      if ( pObj25 == 0 )  // pObj25 等于 0
      {
        off_77F3FC(aCriticalError_25);  // 控制台调试日志输出
        return 1;  // 返回 1（已处理该包）
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj25 + 84))(pObj25, 0);  // 虚表 +84 调用
      pObj12 = *(uint32_t *)(pObj252 + 972);  // 读 pObj252+972 处 4 字节
      if ( pObj12 == 0 )  // pObj12 等于 0
      {
        off_77F3FC(aCriticalError_24);  // 控制台调试日志输出
        return 1;  // 返回 1（已处理该包）
      }
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 16))(pObj12) + 4) != 0 )  // 虚表 +16 调用
      {
        *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
        v580 = 0;  // v580 复制自 0
        for ( i3 = 0; i3 < 4; ++i3 )  // 循环控制
        {
          sub_404A90((char *)&pObj32 + i3);  // 游标读 1 字节 → (char *)&pObj32 + i3
          off_77F3FC("[%d] DICE %d", i3, *((uint8_t *)&pObj32 + i3));  // 控制台调试日志输出
        }
        sub_404AB0(netshort);  // 游标读 2 字节 → netshort
        sub_404AB0(&v580);  // 游标读 2 字节 → &v580
        off_77F3FC("ServerId %d, SlotIndex %d", netshort[0], (uint16_t)v580);  // 控制台调试日志输出
        v313 = 0;  // v313 复制自 0
        HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
        strcpy(Str, (const char *)sub_422E70(653));  // 调用 strcpy
        *(uint32_t *)v568 = 0;  // 指针 v568 写 0
        v575 = 16;  // v575 复制自 16
        do
        {
          v314 = *((uint8_t *)&pObj32 + *(uint32_t *)v568);  // v314 存调用结果
          if ( v314 != 0 )  // v314 不等于 0
          {
            v315 = *(uint32_t *)(v575 + dword_8F850C);  // v315 存调用结果
            if ( v315 != 0 )  // v315 不等于 0
            {
              v546 = v314;  // v546 复制自 v314
              v316 = (const char *)unknown_libname_2(v315 + 16);  // v316 存调用结果
              sprintf(byte_9B9288, " %s[%d]", v316, v546);  // 格式化写入 byte_9B9288
              nLen = strlen(byte_9B9288) + 1;  // nLen ← 表达式
              v319 = &v585;  // v319 ← 表达式
              do
                v320 = *++v319;  // v320 ← 表达式
              while ( v320 != 0 );  // 调用 while
              qmemcpy(v319, byte_9B9288, nLen);  // 调用 qmemcpy
              LOWORD(v317) = *(uint16_t *)(v315 + 4);  // 调用 LOWORD
              v321 = *(int **)(v315 + 196);  // v321 存调用结果
              v322 = *v321;  // 取 v321 首字段
              LOBYTE(v317) = (uint16_t)v317 == netshort[0];  // 字节提取赋值
              HIBYTE(ArgList) = 1;  // 高字节写 ArgList ← 1
              (*(void (/*thiscall*/ **)(int *, int))(v322 + 1256))(v321, v317);  // 虚表 +1256 调用
            }
            v313 = HIBYTE(ArgList);  // v313 存调用结果
          }
          v32 = v575 + 4 < 32;  // v32 ← 表达式
          ++*(uint32_t *)v568;
          v575 += 4;
        }
        while ( v32 );  // 调用 while
        if ( v313 != 0 )  // v313 不等于 0
          sub_43BEE0(Str, -11600063, 0, -1);  // 【播报上屏】
        v323 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
        pObj11 = pObj12;  // pObj11 复制自 pObj12
        if ( v323 != 0 )  // v323 不等于 0
        {
          v522 = v323;  // v522 复制自 v323
          v325 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 44))(pObj12);  // 虚表 +44 调用
          sub_4337E0(pObj11, v325, v522, v313 != 0 ? 0x1F4 : 0);  // 【物品获得播报】串 1179/1180 格式化
        }
        if ( netshort[0] == (uint16_t)word_77F804 )  // 条件判定
        {
          sub_57A360(HIDWORD(pObj32));  // 字符串辅助
          *(float *)&ArgList = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 44))(pObj11));  // 虚表 +44 调用
          HIDWORD(pObj32) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 36))(pObj11);  // 虚表 +36 调用
          sub_432EA0("ITEM_PICK", -1, 0, 0);  // 音效播放包装
          v326 = (uint16_t)v580;  // v326 ← 表达式
          v327 = (uint32_t *)sub_44A980((uint16_t)v580);  // 存 带界索引 getter nArg2 ≥ [2]
          v328 = v327;  // v328 复制自 v327
          if ( v327 != nullptr )  // v327 不等于 nullptr
          {
            v329 = *v327;  // 取 v327 首字段
            v330 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 16))(pObj11);  // 虚表 +16 调用
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(v329 + 60))(v328, *(uint32_t *)(v330 + 4)) != 0 )  // 虚表 +60 调用
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*v328 + 48))(v328, ArgList);  // 虚表 +48 调用
            }
            else
            {
              v331 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 16))(pObj11);  // 虚表 +16 调用
              v332 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v328 + 16))(v328, *(uint32_t *)(v331 + 4));  // 虚表 +16 调用
              off_77F3FC(aErrorD_2, (uint16_t)v580, *(uint32_t *)(v332 + 4));  // 控制台调试日志输出
            }
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj11 + 4))(pObj11, 1);  // 虚表 +4 调用
          }
          else
          {
            sub_484F40(v326, pObj11, 1);  // 技能槽装载
            v328 = (uint32_t *)pObj11;  // v328 ← 表达式
          }
          v333 = *((uint32_t *)dword_8F852C + 1);  // v333 存调用结果
          v334 = v333 - sub_484FA0();  // v334 存调用结果
          v566 = (uint32_t *)v334;  // v566 ← 表达式
          if ( v334 <= 0 || SHIDWORD(pObj32) <= 0 )  // 条件判定
            goto LABEL_336;  // 转到 LABEL_336
          v335 = v334 - 1;  // v335 ← 表达式
          v336 = v335 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v328 + 16))(v328) + 56);  // 虚表 +16 调用
          v337 = ArgList;  // v337 复制自 ArgList
          if ( v336 + 1 < ArgList )  // 条件判定
            v337 = v335 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v328 + 16))(v328) + 56) + 1;  // 虚表 +16 调用
          sub_486330((uint16_t)v580, v337);  // 请求 op 50
          v523 = (double)(int)v566 * 0.001;  // v523 ← 表达式
          v338 = (const char *)sub_422E70(654);  // 存 CStringManager::getStr 取本地化串
          sprintf(OutputString, v338, v523);  // 格式化写入 OutputString
          sub_43BEE0(OutputString, -6567706, 0, -1);  // 【播报上屏】
        }
      }
      else
      {
        v310 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        for ( i4 = 16; i4 < 32; i4 += 4 )  // 循环控制
        {
          *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
          sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
          off_77F3FC("[%d] MONEY %u", v306, ArgList);  // 控制台调试日志输出
          if ( v310 == *(uint32_t *)(i4 + dword_8F850C) && *(float *)&ArgList != 0.0 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(  // 虚表 +48 调用
              **((uint32_t **)dword_8F852C + 3),  // 第 1 个实参
              ArgList);  // 第 2 个实参
            sub_432EA0("ITEM_PICK", -1, 0, 0);  // 音效播放包装
            sub_4337E0(pObj12, ArgList, v310, 0);  // 【物品获得播报】串 1179/1180 格式化
          }
          ++v306;  // v306 自增
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 41] case 40：★ 进副本完成后的实体落位（serverId/xPos/yPos/itemUniqueId..., 40 行） ──
    //   sub_522300 建对象 → new(0x424) + sub_4E2130 建描述 → vt+112 设位(60) → 写 +36=-1500 → sub_45FE80 注册
    case 40:  // 【case 40】包类型分支
      LOBYTE(i5) = 0;  // 低字节写 i5 ← 0
      LODWORD(pObj32) = 0;
      pObj12 = 0;  // pObj12 复制自 0
      v575 = 0;  // v575 复制自 0
      v579 = 0;  // v579 复制自 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      v571 = 0;  // v571 复制自 0
      sub_404AB0(&pObj32);  // 游标读 2 字节 → &pObj32
      sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      sub_404AB0(v568);  // 游标读 2 字节 → v568
      sub_404A90(&i5);  // 游标读 1 字节 → &i5
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      off_77F3FC(  // 控制台调试日志输出
        "serverId %d, xPos %d, yPos %d, itemUniqueId %d, itemIndex %d, ext_data1 %d, data %d, durability %d",  // 第 1 个实参：串 serverId %d, xPos %d, yPos %d, itemUniqueId %d, itemIndex %d, ext_data1 %d, data %d, durability %d
        (uint16_t)pObj32,  // 第 2 个实参：双字节 pObj32
        (int16_t)pObj12,  // 第 3 个实参
        (int16_t)v575,  // 第 4 个实参
        (uint16_t)v579,  // 第 5 个实参：双字节 v579
        *(uint16_t *)v568,  // 第 6 个实参
        (uint8_t)i5,  // 第 7 个实参：单字节 i5
        v571,  // 第 8 个实参
        (uint16_t)ArgList);  // 第 9 个实参：双字节 ArgList
      v359 = sub_522300((void *)*(uint16_t *)v568, v571, (int)i5, 0, (uint16_t)ArgList, 1);  // 存 ★ PO 工厂分发器
      Block[0] = operator new(0x424u);  // 调用 new
      v607 = 7;  // v607 复制自 7
      if ( Block[0] != nullptr )  // 条件判定
        v360 = (int *)sub_4E2130(v359, 0, 0);  // 存 CNRDItemObject
      else
        v360 = nullptr;  // v360 复制自 nullptr
      v361 = *v360;  // 取 v360 首字段
      v607 = -1;  // 局部 v607 → -1
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int))(v361 + 112))(v360, (int16_t)pObj12, (int16_t)v575, 60);  // 虚表 +112 调用
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v360 + 60))(v360) + 36) = -1500;  // 虚表 +60 调用
      sub_45FE80(289, (uint16_t)v579, v360, 0, 0);  // 对象注册
      return 1;  // 返回 1（已处理该包）
    // ── [段 42] case 41：PVP 房间列表（PVP RoomNumber + 逐房字段） ──
    case 41:  // 【case 41】包类型分支
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("PVP RoomNumber %d", (uint16_t)v579);  // 控制台调试日志输出
      HIDWORD(pObj32) = 0;
      if ( (uint16_t)v579 != 0 )  // 条件判定
      {
        do
        {
          Destination = 0;  // Destination 复制自 0
          memset(pBuf2, 0, sizeof(pBuf2));  // 调用 memset
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
          HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
          i5 = nullptr;  // i5 复制自 nullptr
          v571 = 0;  // v571 复制自 0
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          if ( HIBYTE(ArgList) == 0 )  // ArgList 高字节 == 0
          {
            v362 = (char *)sub_422E70(655);  // 存 CStringManager::getStr 取本地化串
            sub_48BCC0(&Destination, 64, v362);  // 限量串读入（带回退）
          }
          sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
          sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
          sub_404AB0(&v571);  // 游标读 2 字节 → &v571
          off_77F3FC(  // 控制台调试日志输出
            "PVP RoomIndex %d, TitleIndex %d, Title [%s], RoomState %d, MasterSeatIndex %d pvpMapIndex %d",  // 第 1 个实参：串 PVP RoomIndex %d, TitleIndex %d, Title [%s], RoomState %d, MasterSeatIndex %d pvpMapIndex %d
            (uint16_t)i5,  // 第 2 个实参：双字节 i5
            HIBYTE(ArgList),  // 第 3 个实参
            &Destination,  // 第 4 个实参：地址 &Destination
            HIBYTE(v580),  // 第 5 个实参
            HIBYTE(v574),  // 第 6 个实参
            (uint16_t)v571);  // 第 7 个实参：双字节 v571
          v363 = (uint32_t *)sub_4879B0((uint16_t)i5);  // 存 按键取房间对象
          v363[19] = HIBYTE(ArgList);  // 调用 HIBYTE
          sub_406D60(&Destination);  // std::string 从 C 串赋值
          v363[18] = HIBYTE(v580);  // 调用 HIBYTE
          v363[28] = (uint16_t)v571;  // 数组元素写入
          sub_48FA30(SHIBYTE(v574));  // 宿主切换
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          HIBYTE(v565) = 0;  // 高字节写 v565 ← 0
          v364 = 0;  // v364 复制自 0
          v365 = v363 + 10;
          do
          {
            HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
            LODWORD(pObj32) = 0;
            sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
            sub_404AB0(&pObj32);  // 游标读 2 字节 → &pObj32
            if ( *v365 == (uint16_t)word_77F804 )  // 条件判定
              HIBYTE(v567) = 1;  // 高字节写 v567 ← 1
            if ( (uint16_t)pObj32 == (uint16_t)word_77F804 )  // 低 16 位比较 pObj32 == word_77F804
              HIBYTE(v565) = 1;  // 高字节写 v565 ← 1
            sub_48F700(v364++, (uint16_t)pObj32, HIBYTE(v572));  // LADDER_DOWN 处理
            ++v365;  // v365 自增
          }
          while ( v364 < 8 );  // 调用 while
          if ( HIBYTE(v565) != 0 )  // v565 高字节 != 0
          {
            sub_48F890(v363);  // 宿主切换 @@SET HOST %d 输出
          }
          else if ( HIBYTE(v567) != 0 )
          {
            sub_48F890(0);  // 宿主切换 @@SET HOST %d 输出
          }
          ++HIDWORD(pObj32);  // 调用 HIDWORD
        }
        while ( SHIDWORD(pObj32) < (uint16_t)v579 );  // 调用 while
      }
      if ( dword_9B9534 != 0 )  // dword_9B9534 不等于 0
        sub_642990(1);  // PVP 房间列表重建
      return 1;  // 返回 1（已处理该包）
    // ── [段 43] case 42：PVP 房态（RoomIndex/RoomState/MasterSeatIndex/pvpMapIndex）—— 等待室就绪判定 ──
    case 42:  // 【case 42】包类型分支
      i5 = nullptr;  // i5 复制自 nullptr
      v571 = 0;  // v571 复制自 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404AB0(&v571);  // 游标读 2 字节 → &v571
      off_77F3FC(  // 控制台调试日志输出
        "RoomIndex %d, RoomState %d, MasterSeatIndex %d pvpMapIndex %d",  // 第 1 个实参：串 RoomIndex %d, RoomState %d, MasterSeatIndex %d pvpMapIndex %d
        (uint16_t)i5,  // 第 2 个实参：双字节 i5
        HIBYTE(ArgList),  // 第 3 个实参
        HIBYTE(v580),  // 第 4 个实参
        (uint16_t)v571);  // 第 5 个实参：双字节 v571
      v370 = (uint16_t)i5;  // v370 ← 表达式
      v371 = sub_487420((uint16_t)i5);  // 存 按键取节点载荷
      if ( v371 != 0 )  // v371 不等于 0
      {
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          *(uint32_t *)(v371 + 72) = HIBYTE(ArgList);  // v371+72 写 HIBYTE(ArgList)
          sub_48FA30(SHIBYTE(v580));  // 宿主切换
          *(uint32_t *)(v371 + 112) = (uint16_t)v571;  // v371+112 写 (uint16_t)v571
          if ( dword_99FEC0 == v371 )  // dword_99FEC0 等于 v371
          {
            off_77F3FC(  // 控制台调试日志输出
              "roomState %d getPVPModule()->isWaitingRoomReadyPacket() %d",  // 第 1 个实参：串 roomState %d getPVPModule()->isWaitingRoomReadyPacket() %d
              HIBYTE(ArgList),  // 第 2 个实参
              *(uint8_t *)(pArg12[8] + 120));  // 第 3 个实参
            if ( HIBYTE(ArgList) == 1 && *(uint8_t *)(pArg12[8] + 120) != 0 )  // 条件判定
              sub_453050(0, 0);  // 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
          }
        }
        else
        {
          sub_487670(v370);  // 按键取节点载荷
        }
      }
      else
      {
        off_77F3FC(aCriticalError_28, v370);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 44] case 43：PVP 座位表（SeatIndex/SeatState/ServerId）—— sub_487420/sub_48F700/sub_48F890 ──
    case 43:  // 【case 43】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("RoomIndex %d, SeatNumber %d", (uint16_t)i5, HIBYTE(ArgList));  // 控制台调试日志输出
      v372 = (uint16_t)i5;  // v372 ← 表达式
      v373 = sub_487420((uint16_t)i5);  // 存 按键取节点载荷
      if ( v373 != 0 )  // v373 不等于 0
      {
        LODWORD(pObj32) = 0;
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          do
          {
            HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
            HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
            v571 = 0;  // v571 复制自 0
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
            sub_404AB0(&v571);  // 游标读 2 字节 → &v571
            off_77F3FC("SeatIndex %d, SeatState %d, ServerId %d", HIBYTE(v580), HIBYTE(v574), (uint16_t)v571);  // 控制台调试日志输出
            HIBYTE(v572) = *(uint32_t *)(v373 + 4 * HIBYTE(v580) + 40) == (uint16_t)word_77F804;  // 字节提取赋值
            v374 = (uint16_t)v571 == (uint16_t)word_77F804;  // v374 ← 表达式
            sub_48F700(SHIBYTE(v580), (uint16_t)v571, HIBYTE(v574));  // LADDER_DOWN 处理
            if ( v374 )  // 条件判定
            {
              sub_48F890(v373);  // 宿主切换 @@SET HOST %d 输出
            }
            else if ( HIBYTE(v572) != 0 )
            {
              sub_48F890(0);  // 宿主切换 @@SET HOST %d 输出
            }
            LODWORD(pObj32) = pObj32 + 1;
          }
          while ( (int)pObj32 < HIBYTE(ArgList) );  // 调用 while
        }
      }
      else
      {
        off_77F3FC(aCriticalError_29, v372);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 45] case 44：PVP 准备状态（SeatIndex/IsReady）—— sub_48F580 ──
    case 44:  // 【case 44】包类型分支
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("SeatIndex %d, IsReady %d", HIBYTE(v580), HIBYTE(ArgList));  // 控制台调试日志输出
      sub_48F580(HIBYTE(v580), HIBYTE(ArgList) != 0);  // 座位/就绪表置位并刷新房间列表 写座位/就绪字节表 dword_99FEB8 加 槽号 = 值，随后
      return 1;  // 返回 1（已处理该包）
    // ── [段 46] case 45：PVP 开始（start PVPMap Num）—— sub_453050/sub_4968E0 ──
    case 45:  // 【case 45】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      *(uint32_t *)(dword_99FEC0 + 116) = HIBYTE(ArgList);  // 全局 dword_99FEC0+116 ← HIBYTE(ArgList)
      off_77F3FC("start PVPMap Num %d", HIBYTE(ArgList));  // 控制台调试日志输出
      sub_453050(1, 0);  // 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
      sub_4968E0(dword_99FD58);  // 对象三段清零 + 双 40 字节链释放 + 槽默认值 先把对象前 0x300 与 +768..+816 清零；按全局域号 dword_8F7A24+12
      *((uint8_t *)dword_99FD58 + 1004) = 1;  // 内存写入
      return 1;  // 返回 1（已处理该包）
    // ── [段 47] case 46：PVP 座位状态（SeatIndex）—— 镜头/播报/UI 三连 ──
    case 46:  // 【case 46】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("SeatIndex %d", HIBYTE(ArgList));  // 控制台调试日志输出
      if ( dword_99FEC0 != 0 )  // dword_99FEC0 不等于 0
      {
        v420 = sub_48F690(HIBYTE(ArgList));  // 存 槽 id 解析
        v421 = v420;  // v421 复制自 v420
        if ( v420 != 0 )  // v420 不等于 0
        {
          pObj21 = *(uint32_t *)(v420 + 196);  // 读 v420+196 处 4 字节
          if ( pObj21 != 0 )  // pObj21 不等于 0
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj21 + 1192))(pObj21, 1);  // 虚表 +1192 调用
            v549 = HIBYTE(ArgList);  // v549 存调用结果
            v423 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚表 +120 调用
            sub_426820(v423, 5, v549);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
            v424 = *(uint32_t *)(v421 + 196);  // 读 v421+196 处 4 字节
            if ( v424 == *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 52) )  // 虚表 +120 调用
            {
              dword_8F7C042 = dword_8F7C04;  // 全局 dword_8F7C042 ← dword_8F7C04
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚表 +120 调用
              v551 = sub_424310(dword_8F7C042);  // 存 当前目标角色选取 模式 3：pArg2/dword_8F850C 槽
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚表 +120 调用
              sub_424A40(v551);  // 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
            }
          }
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 48] case 47：★ PVP 结算（winnerSeatIndex/medal/myPVPRank/playerCount，82 行） ──
    case 47:  // 【case 47】包类型分支
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v581 = 0;  // v581 复制自 0
      HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      v571 = 0;  // v571 复制自 0
      LODWORD(pObj32) = 0;
      v579 = 0;  // v579 复制自 0
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v572 = 0;  // v572 复制自 0
      i5 = nullptr;  // i5 复制自 nullptr
      v575 = 0;  // v575 复制自 0
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404AD0(v568);  // 游标读 4 字节 → v568
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      pObj12 = 0;  // pObj12 复制自 0
      v425 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
      if ( *(uint32_t *)(v425 + 116) == HIBYTE(ArgList) )  // 条件判定
      {
        pObj12 = 0;  // pObj12 复制自 0
      }
      else
      {
        v426 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        if ( *(uint32_t *)(v426 + 116) >= (int)HIBYTE(ArgList) )  // 条件判定
        {
          v427 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
          if ( *(uint32_t *)(v427 + 116) > (int)HIBYTE(ArgList) )  // 条件判定
            pObj12 = -1;  // 局部 pObj12 → -1
        }
        else
        {
          pObj12 = 1;  // pObj12 复制自 1
        }
      }
      v428 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
      *(uint32_t *)(v428 + 116) = HIBYTE(ArgList);  // v428+116 写 HIBYTE(ArgList)
      sub_404A90(&v581);  // 游标读 1 字节 → &v581
      off_77F3FC(  // 控制台调试日志输出
        "winnerSeatIndex %d, medal %d, myPVPRank %d playerCount %d",  // 第 1 个实参：串 winnerSeatIndex %d, medal %d, myPVPRank %d playerCount %d
        HIBYTE(v580),  // 第 2 个实参
        *(uint32_t *)v568,  // 第 3 个实参
        HIBYTE(ArgList),  // 第 4 个实参
        v581);  // 第 5 个实参
      sub_54F540(0);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签
      HIDWORD(pObj32) = 0;
      if ( v581 != 0 )  // v581 不等于 0
      {
        do
        {
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
          sub_550020((uint16_t)i5, pObj32);  // PVP 结算入队转发：按对象槽 8052 过滤后 54FFB0 入队
          sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
          sub_404AD0(&v579);  // 游标读 4 字节 → &v579
          sub_404AD0(netshort);  // 游标读 4 字节 → netshort
          sub_404AD0(&v572);  // 游标读 4 字节 → &v572
          v429 = sub_429830(i5);  // 存 表按键查找
          if ( v429 != 0 )  // v429 不等于 0
          {
            *(uint32_t *)(v429 + 116) = HIBYTE(v574);  // v429+116 写 HIBYTE(v574)
            if ( v429 == sub_41C1B0(dword_8F8500) )  // 条件判定
              sub_57A460(v571);  // 11 行小函数
          }
          ++HIDWORD(pObj32);  // 调用 HIDWORD
        }
        while ( SHIDWORD(pObj32) < v581 );  // 调用 while
      }
      sub_404AB0(&v575);  // 游标读 2 字节 → &v575
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 168) = (uint16_t)v575;  // 内存写入
      sub_453050(4, 0);  // 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
      sub_5500B0(HIBYTE(v580));  // PVP 结算结果应用
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 140) = HIBYTE(ArgList);  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 136) = pObj12;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 144) = v571;  // 内存写入
      sub_54E160(*(uint32_t *)v568);  // 17 行小辅助 大白话：17 行小辅助
      sub_54F540(1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签
      *((uint8_t *)dword_99FD58 + 1004) = 0;  // 内存写入
      sub_47BAA0(dword_8F8540);  // 开/关对账
      return 1;  // 返回 1（已处理该包）
    // ── [段 49] case 48：★ PVP 战绩经验（WinNumber/LoseNumber/curPVPExp/minPVPExp/maxPVPExp）──
    //   写 dword_8F7C18/8F7C1C（全局战绩）→ vt+1032 双级取游标 → sub_54DF30 面板刷新
    case 48:  // 【case 48】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      i5 = nullptr;  // i5 复制自 nullptr
      v575 = 0;  // v575 复制自 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      v571 = 0;  // v571 复制自 0
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      sub_404AD0(&i5);  // 游标读 4 字节 → &i5
      sub_404AD0(&v575);  // 游标读 4 字节 → &v575
      sub_404AD0(v568);  // 游标读 4 字节 → v568
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      off_77F3FC(  // 控制台调试日志输出
        "WinNumber %d, LoseNumber %d curPVPExp %d minPVPExp %d maxPVPExp %d",  // 第 1 个实参：串 WinNumber %d, LoseNumber %d curPVPExp %d minPVPExp %d maxPVPExp %d
        ArgList,  // 第 2 个实参
        i5,  // 第 3 个实参
        v575,  // 第 4 个实参
        *(uint32_t *)v568,  // 第 5 个实参
        v571);  // 第 6 个实参
      dword_8F7C18 = ArgList;  // 全局 dword_8F7C18 ← ArgList
      dword_8F7C1C = (int)i5;  // 全局 dword_8F7C1C ← (int)i5
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
      {
        v430 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);  // 虚表 +1032 调用
        v431 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(  // 虚表 +1032 调用
                 dword_8F7C04,  // 第 1 个实参
                 *(uint32_t *)(v430 + 56));  // 第 2 个实参
        v432 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(  // 虚表 +1032 调用
                 dword_8F7C04,  // 第 1 个实参
                 *(uint32_t *)(v431 + 60));  // 第 2 个实参
        sub_54DF30(*(uint32_t *)(v432 + 52), v558, v559);  // 13 行小辅助 大白话：13 行小辅助
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1040))(dword_8F7C04, v575);  // 虚表 +1040 调用
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 50] case 49：★ PVP 结算上报（发包）—— 复制 0x60 字节后连续 sub_41C0E0 逐字段+sub_423380 提交 ──
    case 49:  // 【case 49】包类型分支
      qmemcpy(&Buffer[32], (char *)dword_99FD58 + 768, 0x60u);  // 调用 qmemcpy
      v433 = (uint64_t)*(float *)&Buffer[108];  // v433 ← 表达式
      v434 = (uint64_t)*(float *)&Buffer[116];  // v434 ← 表达式
      v435 = (uint64_t)*(float *)&Buffer[120];  // v435 ← 表达式
      ArgList = (uint64_t)*(float *)&Buffer[124];  // ArgList ← 表达式
      LODWORD(pObj32) = (uint64_t)*(float *)&Buffer[80];
      HIDWORD(pObj32) = (uint64_t)*(float *)&Buffer[88];
      i5 = (void *)(uint64_t)*(float *)&Buffer[84];  // i5 ← 表达式
      v571 = (uint64_t)*(float *)&Buffer[92];  // v571 ← 表达式
      *(uint32_t *)v568 = (uint64_t)*(float *)&Buffer[96];  // 内存写入
      v575 = (uint64_t)*(float *)&Buffer[100];  // v575 ← 表达式
      pObj12 = (uint64_t)*(float *)&Buffer[104];  // pObj12 ← 表达式
      v579 = (uint64_t)*(float *)&Buffer[64];  // v579 ← 表达式
      *(uint32_t *)netshort = (uint64_t)*(float *)&Buffer[60];  // 内存写入
      v580 = (uint64_t)*(float *)&Buffer[68];  // v580 ← 表达式
      v574 = (uint64_t)*(float *)&Buffer[72];  // v574 ← 表达式
      v572 = (uint64_t)*(float *)&Buffer[76];  // v572 ← 表达式
      v436 = (uint64_t)sub_477280(dword_99FD58, (uint64_t)*(float *)&Buffer[76] >> 32);  // v436 存调用结果
      v565 = v436;  // v565 复制自 v436
      v437 = (uint64_t)sub_477260(dword_99FD58, HIDWORD(v436));  // v437 存调用结果
      v567 = v437;  // v567 复制自 v437
      Block[0] = (void *)(uint64_t)sub_57A480(dword_99FD58, HIDWORD(v437));  // 调用 sub_57A480
      off_77F3FC(  // 控制台调试日志输出
        aEnumCmdpacketR_18,  // 第 1 个实参
        (uint16_t)v433,  // 第 2 个实参：双字节 v433
        (uint16_t)v434,  // 第 3 个实参：双字节 v434
        (uint16_t)v435,  // 第 4 个实参：双字节 v435
        (uint16_t)ArgList,  // 第 5 个实参：双字节 ArgList
        (uint16_t)pObj32,  // 第 6 个实参：双字节 pObj32
        WORD2(pObj32),  // 第 7 个实参
        (uint16_t)i5,  // 第 8 个实参：双字节 i5
        (uint16_t)v571,  // 第 9 个实参：双字节 v571
        *(uint16_t *)v568,  // 第 10 个实参
        (uint16_t)v575,  // 第 11 个实参：双字节 v575
        (uint16_t)pObj12,  // 第 12 个实参：双字节 pObj12
        v579,  // 第 13 个实参
        *(uint32_t *)netshort,  // 第 14 个实参
        v580,  // 第 15 个实参
        v574,  // 第 16 个实参
        v572,  // 第 17 个实参
        v565,  // 第 18 个实参
        v567,  // 第 19 个实参
        Block[0]);  // 第 20 个实参
      sub_423200(dword_8F7B08, 61);  // 【发送网络包API】
      sub_41C0E0(v433);  // 发送缓冲写入
      sub_41C0E0(v434);  // 发送缓冲写入
      sub_41C0E0(v435);  // 发送缓冲写入
      sub_41C0E0(ArgList);  // 发送缓冲写入
      sub_41C0E0(pObj32);  // 发送缓冲写入
      sub_41C0E0(SBYTE4(pObj32));  // 发送缓冲写入
      sub_41C0E0((char)i5);  // 发送缓冲写入
      sub_41C0E0(v571);  // 发送缓冲写入
      sub_41C0E0(v568[0]);  // 发送缓冲写入
      sub_41C0E0(v575);  // 发送缓冲写入
      sub_41C0E0(pObj12);  // 发送缓冲写入
      sub_43B4C0(v579);  // 发包字段
      sub_43B4C0(netshort[0]);  // 发包字段
      sub_43B4C0(v580);  // 发包字段
      sub_43B4C0(v574);  // 发包字段
      sub_43B4C0(v572);  // 发包字段
      sub_43B4C0(v565);  // 发包字段
      sub_43B4C0(v567);  // 发包字段
      sub_43B4C0((char)Block[0]);  // 发包字段
      sub_423380(dword_8F7B08);  // 发包 Commit
      off_77F3FC((char *)&byte_7287B4);  // 控制台调试日志输出
      return 1;  // 返回 1（已处理该包）
    // ── [段 51] case 50：ICON_KEY 图标键（keyCount）—— 写 dword_99FB70 + sub_432EA0 播报 ──
    case 50:  // 【case 50】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("keyCount %d", HIBYTE(ArgList));  // 控制台调试日志输出
      *(uint32_t *)dword_99FB70 = HIBYTE(ArgList);  // 内存写入
      sub_432EA0("ICON_KEY", -1, 0, 0);  // 音效播放包装
      return 1;  // 返回 1（已处理该包）
    // ── [段 52] case 51：金币变化（reason/orgMoney/gainMoney）—— sub_43BEE0 播报 + 面板刷新 ──
    case 51:  // 【case 51】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      pObj32 = 0;  // pObj32 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0((char *)&pObj32 + 4);  // 游标读 4 字节 → (char *)&pObj32 + 4
      sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
      off_77F3FC("reason %d orgMoney %d gainMoney %d", HIBYTE(ArgList), HIDWORD(pObj32), (uint32_t)pObj32);  // 控制台调试日志输出
      if ( dword_8F7C04 != 0 )  // dword_8F7C04 不等于 0
      {
        switch ( HIBYTE(ArgList) )
        {
          case 0:  // 【case 0】包类型分支
            v438 = (const char *)sub_422E70(656);  // 存 CStringManager::getStr 取本地化串
            sprintf(Format, v438);  // 格式化写入 Format
            sub_43BEE0(Format, -13487361, 0, -1);  // 【播报上屏】
            break;
          case 1:  // 【case 1】包类型分支
            v439 = (const char *)sub_422E70(657);  // 存 CStringManager::getStr 取本地化串
            goto LABEL_781;  // 转到 LABEL_781
          case 2:  // 【case 2】包类型分支
            v440 = (const char *)sub_422E70(658);  // 存 CStringManager::getStr 取本地化串
            sprintf(Format, v440);  // 格式化写入 Format
            sub_44E8D0(dword_8F8528, (void *)0x1B, Format, 0);  // 对象池借出
            break;
          case 3:  // 【case 3】包类型分支
            v441 = (const char *)sub_422E70(659);  // 存 CStringManager::getStr 取本地化串
            sprintf(Format, v441);  // 格式化写入 Format
            sub_44E8D0(dword_8F8528, (void *)0x1B, Format, 0);  // 对象池借出
            break;
          case 4:  // 【case 4】包类型分支
            v439 = (const char *)sub_422E70(660);  // 存 CStringManager::getStr 取本地化串
LABEL_781:
            sprintf(Format, v439);  // 格式化写入 Format
            v115 = Format;  // v115 复制自 Format
LABEL_782:
            sub_44E8D0(dword_8F8528, (void *)0x1B, v115, 0);  // 对象池借出
            break;
          default:
            return 1;  // 返回 1（已处理该包）
        }
      }
      else
      {
        v442 = sub_422E70(661);  // 存 CStringManager::getStr 取本地化串
        sub_44E8D0(dword_8F8528, (void *)0x1B, v442, 1);  // 对象池借出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 53] case 52：好友列表（FriendInfoNumber + Name/Level/Job/GrowType/Unique ID）—— sub_47B150 写入 ──
    case 52:  // 【case 52】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("FriendInfoNumber %d", HIBYTE(ArgList));  // 控制台调试日志输出
      v443 = 0;  // v443 复制自 0
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        do
        {
          HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
          HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
          HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
          i5 = nullptr;  // i5 复制自 nullptr
          v444 = (char *)sub_422E70(662);  // 存 CStringManager::getStr 取本地化串
          sub_48BCC0(&v601, 31, v444);  // 限量串读入（带回退）
          sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
          sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
          sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
          sub_404AD0(&i5);  // 游标读 4 字节 → &i5
          off_77F3FC(  // 控制台调试日志输出
            "Name [%s], Level %d, Job %d, GrowType %d, Unique ID %d",  // 第 1 个实参：串 Name [%s], Level %d, Job %d, GrowType %d, Unique ID %d
            &v601,  // 第 2 个实参：地址 &v601
            HIBYTE(v572),  // 第 3 个实参
            HIBYTE(v574),  // 第 4 个实参
            HIBYTE(v580),  // 第 5 个实参
            i5);  // 第 6 个实参
          sub_47B150(&v601, HIBYTE(v572), HIBYTE(v574), HIBYTE(v580), (int)i5);  // 添加好友/成员申请
          ++v443;  // v443 自增
        }
        while ( v443 < HIBYTE(ArgList) );  // 调用 while
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 54] case 53：点券余额（ok/myCera）──
    case 53:  // 【case 53】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&i5);  // 游标读 4 字节 → &i5
      off_77F3FC("ok %d myCera %d", HIBYTE(ArgList), i5);  // 控制台调试日志输出
      dword_8F7C0C = (int)i5;  // 全局 dword_8F7C0C ← (int)i5
      if ( (int)i5 < 0 )  // 条件判定
      {
        off_77F3FC(aCriticalError_31, i5);  // 控制台调试日志输出
        dword_8F7C0C = 0;  // 全局 dword_8F7C0C ← 0
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 55] case 54/55/56：好友增删族（sub_4794F0/sub_47B380/sub_479520/sub_47B400/sub_479850） ──
    case 54:  // 【case 54】包类型分支
      sub_404A90(&ArgList);  // 游标读 1 字节 → &ArgList
      v446 = (char *)sub_422E70(664);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v446);  // 限量串读入（带回退）
      sub_4794F0(&v601, ArgList);  // 按名找到条目后置其 +40 旗标为 uArg3
      sub_47B380(&v601, ArgList);  // 好友上线提示：sub_47B200
      return 1;  // 返回 1（已处理该包）
    case 55:  // 【case 55】包类型分支
      v447 = (char *)sub_422E70(666);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v447);  // 限量串读入（带回退）
      sub_479520(&v601);  // 按名找到条目后清其 +40 旗标
      sub_47B400(&v601);  // 好友下线提示：sub_47B200
      return 1;  // 返回 1（已处理该包）
    case 56:  // 【case 56】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      v445 = 0;  // v445 复制自 0
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        do
        {
          sub_404AF0(&v601, 31);  // 游标读 n 字节 → &v601, 31
          if ( v601 != -1 )  // 条件判定
            sub_4794F0(v602, v601);  // 按名找到条目后置其 +40 旗标为 uArg3
          ++v445;  // v445 自增
        }
        while ( v445 < HIBYTE(ArgList) );  // 调用 while
      }
      sub_479850(dword_8F8510);  // 遍历 180 字节条目表做名次/位置统计
      return 1;  // 返回 1（已处理该包）
    // ── [段 56] case 57/58/59/60/61：公会/周 PVP 经验族（pvpExpOfWeek / ENUM_NOTIPACKET_GUILD_ENTER） ──
    case 57:  // 【case 57】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      off_77F3FC("pvpExpOfWeek %d", ArgList);  // 控制台调试日志输出
      *(float *)(*((uint32_t *)dword_8F8528 + 4) + 1224) = *(float *)&ArgList;  // 内存写入
      return 1;  // 返回 1（已处理该包）
    case 58:  // 【case 58】包类型分支
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      sub_404AD0(Block);  // 游标读 4 字节 → Block
      v457 = (char *)sub_422E70(676);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[31], 31, v457);  // 限量串读入（带回退）
      v458 = (char *)sub_422E70(677);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v458);  // 限量串读入（带回退）
      off_77F3FC("ENUM_NOTIPACKET_GUILD_ENTER - Guild[%d] Guild_Name[%s] Name[%s]", ArgList, &pBuf2[31], &v601);  // 控制台调试日志输出
      v459 = (const char *)sub_422E70(678);  // 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v459, &v601, &pBuf2[31]);  // 格式化写入 Buffer
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      if ( sub_41C1B0(dword_8F8500) != 0 )  // 条件判定
      {
        v460 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        *(float *)(v460 + 120) = *(float *)&ArgList;  // v460+120 写 *(float *)&ArgList
      }
      sub_478EA0(1);  // 列表滚动状态机
      return 1;  // 返回 1（已处理该包）
    case 59:  // 【case 59】包类型分支
      sub_404AD0(Block);  // 游标读 4 字节 → Block
      sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      v454 = (char *)sub_422E70(672);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v454);  // 限量串读入（带回退）
      v455 = (char *)sub_422E70(673);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[31], 31, v455);  // 限量串读入（带回退）
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        v456 = (const char *)sub_422E70(675);  // 存 CStringManager::getStr 取本地化串
      else
        v456 = (const char *)sub_422E70(674);  // 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v456, &pBuf2[31], &v601);  // 格式化写入 Buffer
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      sub_478EA0(1);  // 列表滚动状态机
      return 1;  // 返回 1（已处理该包）
    case 60:  // 【case 60】包类型分支
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      v462 = sub_4BF1B0(ArgList);  // 存 按工会 id 查值指针 键为 0 或未命中回 0，否则回值槽
      if ( v462 != 0 )  // v462 不等于 0
        sub_4BE470(v462);  // 徽章清理与重试重启 状态 +4 为 4/5/6 且 +12 非 0 时：虚调释放已载入图像
      return 1;  // 返回 1（已处理该包）
    case 61:  // 【case 61】包类型分支
      v461 = sub_422E70(679);  // 存 CStringManager::getStr 取本地化串
      sub_43BEE0(v461, -6567706, 0, -1);  // 【播报上屏】
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8514 + 12))(dword_8F8514);  // 虚表 +12 调用
      sub_44E850(11);  // 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
      if ( sub_41C1B0(dword_8F8500) != 0 )  // 条件判定
        *(uint32_t *)(sub_41C1B0(dword_8F8500) + 120) = 0;  // 内存写入
      return 1;  // 返回 1（已处理该包）
    // ── [段 57] case 64/65：公会成员登录登出（flag/channel/name）+ 公会消息（MessageType/name/MessageLength） ──
    case 64:  // 【case 64】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90(&i5);  // 游标读 1 字节 → &i5
      v453 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v453);  // 限量串读入（带回退）
      off_77F3FC(  // 控制台调试日志输出
        "ENUM_NOTIPACKET_GUILD_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s",  // 第 1 个实参：串 ENUM_NOTIPACKET_GUILD_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s
        HIBYTE(ArgList),  // 第 2 个实参
        (uint8_t)i5,  // 第 3 个实参：单字节 i5
        &v601);  // 第 4 个实参：地址 &v601
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        goto LABEL_819;  // 转到 LABEL_819
      sub_479520(&v601);  // 按名找到条目后清其 +40 旗标
      sub_47B400(&v601);  // 好友下线提示：sub_47B200
      return 1;  // 返回 1（已处理该包）
    case 65:  // 【case 65】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      v126 = (char *)sub_422E70(641);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v126);  // 限量串读入（带回退）
      v127 = (char *)sub_422E70(642);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(Str, 256, v127);  // 限量串读入（带回退）
      off_77F3FC("MessageType %d, name %s, MessageLength %d", HIBYTE(ArgList), &v601, strlen(Str));  // 控制台调试日志输出
      sub_43D900(Str, HIBYTE(ArgList), 0, &v601);  // 聊天消息出口
      return 1;  // 返回 1（已处理该包）
    // ── [段 58] case 66：★ 点券特殊物品（CERA_SPECIALITEM）—— 子类型 1 扩容容量 / 2 逐项入包，其余报 Unspecified ──
    case 66:  // 【case 66】包类型分支
      sub_404AB0((char *)&v580 + 2);  // 游标读 2 字节 → (char *)&v580 + 2
      if ( HIWORD(v580) == 1 )  // 条件判定
      {
        *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
        sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
        off_77F3FC((char *)&byte_7285FC, HIWORD(v580), (uint16_t)ArgList);  // 控制台调试日志输出
        v452 = (uint16_t)ArgList;  // v452 ← 表达式
        if ( sub_50D980() < v452 )  // 条件判定
          sub_50D920(v452);  // 仓储栏类型设置
        else
          off_77F3FC("CNGameCore.NetworkProc - ENUM_NOTIPACKET_CERA_SPECIALITEM - Capacity is too small");  // 控制台调试日志输出
        return 1;  // 返回 1（已处理该包）
      }
      if ( HIWORD(v580) != 2 )  // 条件判定
      {
        off_77F3FC("CNGameCore.NetworkProc - ENUM_NOTIPACKET_CERA_SPECIALITEM - Unspecified type");  // 控制台调试日志输出
        return 1;  // 返回 1（已处理该包）
      }
      HIBYTE(ArgList) = -1;  // 字节提取赋值
      v579 = 0;  // v579 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&v579);  // 游标读 4 字节 → &v579
      off_77F3FC((char *)&byte_728628, HIWORD(v580), SHIBYTE(ArgList), v579);  // 控制台调试日志输出
      if ( v579 != 0 )  // v579 不等于 0
      {
        v451 = *((uint32_t *)dword_8F8528 + 611);  // v451 存调用结果
        if ( *(uint32_t *)(v451 + 12) == 1 )  // 条件判定
          *(uint32_t *)(v451 + 10124) = SHIBYTE(ArgList);  // v451+10124 写 SHIBYTE(ArgList)
        sub_41C470(SHIBYTE(ArgList), 1);  // 字节数组 setter
        sub_41C490(SHIBYTE(ArgList), v579);  // dword 数组 setter
        return 1;  // 返回 1（已处理该包）
      }
      v552 = sub_41C4B0(SHIBYTE(ArgList));  // 存 索引取字符串资源
      v449 = (const char *)sub_422E70(668);  // 存 CStringManager::getStr 取本地化串
      sprintf(OutputString, v449, v552);  // 格式化写入 OutputString
      sub_43BEE0(OutputString, -6567706, 0, -1);  // 【播报上屏】
      v450 = HIBYTE(ArgList);  // v450 存调用结果
      if ( SHIBYTE(ArgList) <= 0 )  // 条件判定
        goto LABEL_810;  // 转到 LABEL_810
      if ( SHIBYTE(ArgList) <= 4 )  // 条件判定
      {
        sub_55E820(50000);  // 商城条目
      }
      else
      {
        if ( HIBYTE(ArgList) != 8 )  // ArgList 高字节 != 8
        {
LABEL_810:
          sub_41C470(v450, 0);  // 字节数组 setter
          sub_41C490(SHIBYTE(ArgList), v579);  // dword 数组 setter
          return 1;  // 返回 1（已处理该包）
        }
        sub_55E820(50002);  // 商城条目
      }
      v450 = HIBYTE(ArgList);  // v450 存调用结果
      goto LABEL_810;  // 转到 LABEL_810
    // ── [段 59] case 68/69/70：限购组（buyLimitGroup*）/活动开关（isEnable/eventIndex/eventDuration）/杂项 ──
    case 68:  // 【case 68】包类型分支
      v448 = 0;  // v448 复制自 0
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      off_77F3FC("buyLimitGroupCount %d", (uint16_t)ArgList);  // 控制台调试日志输出
      if ( (uint16_t)ArgList != 0 )  // 条件判定
      {
        do
        {
          sub_404AD0(&i5);  // 游标读 4 字节 → &i5
          off_77F3FC("buyLimitGroup %d", i5);  // 控制台调试日志输出
          sub_55F7B0(i5);  // 全局窗口获取
          ++v448;  // v448 自增
        }
        while ( v448 < (uint16_t)ArgList );  // 调用 while
      }
      return 1;  // 返回 1（已处理该包）
    case 69:  // 【case 69】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      i5 = nullptr;  // i5 复制自 nullptr
      LODWORD(pObj32) = 0;
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      sub_404AB0(&pObj32);  // 游标读 2 字节 → &pObj32
      off_77F3FC("isEnable %d eventIndex %d eventDuration %d", HIBYTE(ArgList), (int16_t)i5, (int16_t)pObj32);  // 控制台调试日志输出
      sub_41C3C0((int16_t)i5);  // 字段 setter
      LOBYTE(v463) = HIBYTE(ArgList) != 0;  // 字节提取赋值
      sub_41C9E0(v463);  // 字段 setter
      return 1;  // 返回 1（已处理该包）
    case 70:  // 【case 70】包类型分支
      v464 = (char *)sub_422E70(672);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v464);  // 限量串读入（带回退）
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v565 + 3);  // 游标读 1 字节 → (char *)&v565 + 3
      sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      off_77F3FC(  // 控制台调试日志输出
        "ENUM_NOTIPACKET_GUILD_INFO - %s, master:%d level:%d mark:%d members:%d establish:%d",  // 第 1 个实参：串 ENUM_NOTIPACKET_GUILD_INFO - %s, master:%d level:%d mark:%d members:%d establish:%d
        &pBuf2[11],  // 第 2 个实参：地址 &pBuf2[11]
        HIBYTE(ArgList),  // 第 3 个实参
        HIBYTE(v565),  // 第 4 个实参
        HIBYTE(v572),  // 第 5 个实参
        HIBYTE(v574),  // 第 6 个实参
        HIBYTE(v580));  // 第 7 个实参
      *(uint32_t *)(dword_8F8514 + 48) = HIBYTE(ArgList);  // 全局 dword_8F8514+48 ← HIBYTE(ArgList)
      *(uint32_t *)(dword_8F8514 + 52) = HIBYTE(v580);  // 全局 dword_8F8514+52 ← HIBYTE(v580)
      return 1;  // 返回 1（已处理该包）
    // ── [段 60] case 71/72/73/74/75：公会创建（GUILD_CREATE）/成员登录登出/入会申请转发（…TO_RESPONSER）/回复/关闭 ──
    case 71:  // 【case 71】包类型分支
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      v465 = (char *)sub_422E70(672);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v465);  // 限量串读入（带回退）
      v466 = (const char *)sub_422E70(1251);  // 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v466, &pBuf2[11]);  // 格式化写入 Buffer
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      off_77F3FC("ENUM_NOTIPACKET_GUILD_CREATE - %s(%d)", &pBuf2[11], ArgList);  // 控制台调试日志输出
      if ( sub_41C1B0(dword_8F8500) != 0 )  // 条件判定
      {
        v467 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        *(float *)(v467 + 120) = *(float *)&ArgList;  // v467+120 写 *(float *)&ArgList
      }
      return 1;  // 返回 1（已处理该包）
    case 72:  // 【case 72】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90(&i5);  // 游标读 1 字节 → &i5
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      v468 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&v601, 31, v468);  // 限量串读入（带回退）
      off_77F3FC(  // 控制台调试日志输出
        "ENUM_NOTIPACKET_MEMBER_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s",  // 第 1 个实参：串 ENUM_NOTIPACKET_MEMBER_MEMBER_LOGIN_OUT - flag:%d channel:%d name:%s
        HIBYTE(ArgList),  // 第 2 个实参
        (uint8_t)i5,  // 第 3 个实参：单字节 i5
        &v601);  // 第 4 个实参：地址 &v601
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
LABEL_819:
        sub_4794F0(&v601, (char)i5);  // 按名找到条目后置其 +40 旗标为 uArg3
        sub_47B380(&v601, (char)i5);  // 好友上线提示：sub_47B200
      }
      else
      {
        sub_479520(&v601);  // 按名找到条目后清其 +40 旗标
      }
      return 1;  // 返回 1（已处理该包）
    case 73:  // 【case 73】包类型分支
      sub_404AB0((char *)&ArgList + 2);  // 游标读 2 字节 → (char *)&ArgList + 2
      v469 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v469);  // 限量串读入（带回退）
      off_77F3FC("ENUM_NOTIPACKET_REQUEST_MEMBER_ENTER_TO_RESPONSER - from Lv.%d %s", SHIWORD(ArgList), &pBuf2[11]);  // 控制台调试日志输出
      sub_44E8D0(dword_8F8528, (void *)0x3A, &pBuf2[11], SHIWORD(ArgList));  // 对象池借出
      return 1;  // 返回 1（已处理该包）
    case 74:  // 【case 74】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      v470 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v470);  // 限量串读入（带回退）
      if ( HIBYTE(ArgList) == 1 )  // ArgList 高字节 == 1
      {
        v471 = (const char *)sub_422E70((HIBYTE(v580) != 1) + 1509);  // 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v471, &pBuf2[11]);  // 格式化写入 Buffer
        sub_478F40(1);  // 列表滚动状态机
      }
      else
      {
        v472 = (const char *)sub_422E70(1511);  // 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v472, &pBuf2[11]);  // 格式化写入 Buffer
      }
      goto LABEL_842;  // 转到 LABEL_842
    case 75:  // 【case 75】包类型分支
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8518 + 12))(dword_8F8518);  // 虚表 +12 调用
      return 1;  // 返回 1（已处理该包）
    // ── [段 61] case 76/77：上交税金（PAY_TAX_TO_UPPER - gold/fatigue）+ 成员退出（MEMBER_SECEDE） ──
    case 76:  // 【case 76】包类型分支
      sub_404AD0(netshort);  // 游标读 4 字节 → netshort
      sub_404AB0((char *)&ArgList + 2);  // 游标读 2 字节 → (char *)&ArgList + 2
      v475 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v475);  // 限量串读入（带回退）
      off_77F3FC("ENUM_NOTIPACKET_PAY_TAX_TO_UPPER - %d gold. %d fatigue", *(uint32_t *)netshort, SHIWORD(ArgList));  // 控制台调试日志输出
      if ( *(int *)netshort > 0 && sub_41C1B0(dword_8F8500) != 0 && *(uint32_t *)(sub_41C1B0(dword_8F8500) + 196) != 0 )  // 条件判定
      {
        v476 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v476 + 196) + 1260))(  // 虚表 +1260 调用
          *(uint32_t *)(v476 + 196),  // 第 1 个实参
          1,  // 第 2 个实参：常量 1
          *(uint32_t *)netshort,  // 第 3 个实参
          0,  // 第 4 个实参：常量 0
          0,  // 第 5 个实参：常量 0
          0,  // 第 6 个实参：常量 0
          0,  // 第 7 个实参：常量 0
          0,  // 第 8 个实参：常量 0
          0);  // 第 9 个实参：常量 0
        sub_57A3F0(*(uint32_t *)netshort);  // std::string 辅助 4
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 48))(  // 虚表 +48 调用
          **((uint32_t **)dword_8F852C + 3),  // 第 1 个实参
          *(uint32_t *)netshort);  // 第 2 个实参
        v553 = *(uint32_t *)netshort;  // v553 ← 表达式
        v477 = (const char *)sub_422E70(1515);  // 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v477, &pBuf2[11], v553);  // 格式化写入 Buffer
      }
      if ( SHIWORD(ArgList) > 0 )  // 条件判定
      {
        word_8F7C10 = (word_8F7C10 - HIWORD(ArgList)) & (((uint16_t)word_8F7C10 - SHIWORD(ArgList) < 0) - 1);  // 全局 word_8F7C10 ← (word_8F7C10 - HIWORD(ArgL
        sub_57A410(SHIWORD(ArgList));  // std::string 辅助 5
        v554 = SHIWORD(ArgList);  // v554 存调用结果
        v478 = (const char *)sub_422E70(1527);  // 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v478, &pBuf2[11], v554);  // 格式化写入 Buffer
      }
LABEL_842:
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      return 1;  // 返回 1（已处理该包）
    case 77:  // 【case 77】包类型分支
      v473 = (char *)sub_422E70(669);  // 存 CStringManager::getStr 取本地化串
      sub_48BCC0(&pBuf2[11], 50, v473);  // 限量串读入（带回退）
      off_77F3FC("ENUM_NOTIPACKET_MEMBER_SECEDE - from %s", &pBuf2[11]);  // 控制台调试日志输出
      v474 = (const char *)sub_422E70(1513);  // 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v474, &pBuf2[11]);  // 格式化写入 Buffer
      sub_43BEE0(Buffer, -6567706, 0, -1);  // 【播报上屏】
      sub_478F40(1);  // 列表滚动状态机
      return 1;  // 返回 1（已处理该包）
    // ── [段 62] case 78/79/80/81：摆摊开张族（sub_42FBB0/sub_430230/sub_542AD0/sub_42FBF0/sub_42FC00） ──
    case 78:  // 【case 78】包类型分支
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AB0(netshort);  // 游标读 2 字节 → netshort
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0((char *)&v574 + 2);  // 游标读 2 字节 → (char *)&v574 + 2
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      off_77F3FC("%d, %d, %d, %d, %d", netshort[0], HIBYTE(v580), HIBYTE(ArgList), HIWORD(v574), (uint16_t)i5);  // 控制台调试日志输出
      v479 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 虚表 +52 调用
      if ( v479 != netshort[0] )  // 条件判定
      {
        v480 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 虚表 +52 调用
        off_77F3FC("%d", v480);  // 控制台调试日志输出
        if ( sub_429830(*(uint32_t *)netshort) != 0 )  // 条件判定
        {
          v481 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
          sub_42FBB0(*(uint32_t *)(v481 + 192), HIBYTE(v580), HIBYTE(ArgList), HIWORD(v574), (uint16_t)i5);  // 个人商店准备 【个人商店准备】【推断：+648 为摆摊组件槽】组件存在 →
          v482 = sub_429830(*(uint32_t *)netshort);  // 存 表按键查找
          sub_430230(*(uint32_t *)(v482 + 192));  // 个人商店开店定位 【个人商店开店定位】
        }
      }
      return 1;  // 返回 1（已处理该包）
    case 79:  // 【case 79】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      if ( sub_429830(ArgList) != 0 )  // 条件判定
      {
        v483 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 虚表 +52 调用
        if ( v483 != (uint16_t)ArgList )  // 条件判定
        {
          v484 = sub_429830(ArgList);  // 存 表按键查找
          sub_42FBE0(*(uint32_t *)(v484 + 192));  // 商店复位 【商店复位】+648 组件 +284 与 +285 与 +340 三标志清零。
        }
      }
      return 1;  // 返回 1（已处理该包）
    case 80:  // 【case 80】包类型分支
      sub_542AD0();  // 摊位页切换
      return 1;  // 返回 1（已处理该包）
    case 81:  // 【case 81】包类型分支
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
      sub_48BCC0(&pBuf2[19], 41, nullptr);  // 限量串读入（带回退）
      off_77F3FC("%d, %s", (uint16_t)ArgList, &pBuf2[19]);  // 控制台调试日志输出
      if ( sub_429830(ArgList) != 0 )  // 条件判定
      {
        v485 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 虚表 +52 调用
        if ( v485 != (uint16_t)ArgList )  // 条件判定
        {
          sub_429830(ArgList);  // 表按键查找
          sub_42FC00(&pBuf2[19]);  // 商店操作转发 【商店操作转发】+648 组件存在 → 清 +285 →
          v486 = sub_429830(ArgList);  // 存 表按键查找
          sub_42FBF0(*(uint32_t *)(v486 + 192));  // 商店标志消解 【商店标志消解】+284 与 +285 均置位时清 +285。
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 63] case 82：★ 摆摊购买回报（Sell private store item）—— sub_4F2CE0 物品检查 + sub_541B30 结算 ──
    case 82:  // 【case 82】包类型分支
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        memset(pBuf, 0, sizeof(pBuf));  // 调用 memset
        sub_404AD0(Block);  // 游标读 4 字节 → Block
        sub_404AB0((char *)&v580 + 2);  // 游标读 2 字节 → (char *)&v580 + 2
        sub_404AB0((char *)&v574 + 2);  // 游标读 2 字节 → (char *)&v574 + 2
        sub_404AD0((char *)&pObj32 + 4);  // 游标读 4 字节 → (char *)&pObj32 + 4
        sub_48BCC0(pBuf, 20, nullptr);  // 限量串读入（带回退）
        sub_404AD0(&i5);  // 游标读 4 字节 → &i5
        sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
        (*(void (/*thiscall*/ **)(uint32_t, void *))(***((uint32_t ***)dword_8F852C + 3) + 40))(  // 虚表 +40 调用
          **((uint32_t **)dword_8F852C + 3),  // 第 1 个实参
          Block[0]);  // 第 2 个实参
        sub_541B30(HIWORD(v580), HIWORD(v574), pBuf, i5, pObj32, HIDWORD(pObj32));  // 摊位条目详情
        pObj324 = pObj32;  // pObj324 复制自 pObj32
        pObj325 = pObj32;  // pObj325 复制自 pObj32
        v507 = i5;  // v507 复制自 i5
        v487 = (const char *)sub_4F2CE0(HIWORD(v580));  // 存 按物品 id 取名称串：查模板表
        off_77F3FC(  // 控制台调试日志输出
          "Sell private store item : %s, %s, %d, %d, %d, %d",  // 第 1 个实参：串 Sell private store item : %s, %s, %d, %d, %d, %d
          pBuf,  // 第 2 个实参
          v487,  // 第 3 个实参
          v507,  // 第 4 个实参
          (uint32_t)pObj325,  // 第 5 个实参
          HIDWORD(pObj325),  // 第 6 个实参
          pObj324);  // 第 7 个实参
      }
      else
      {
        sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
        sub_542000(SHIBYTE(v580));  // 摊位条目查询
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 64] case 83/84/85：摆摊底座回填（sub_541A30）/进出摆摊（user_id/store_owner_id）/摆摊列表 ──
    case 83:  // 【case 83】包类型分支
      sub_404AB0((char *)&ArgList + 2);  // 游标读 2 字节 → (char *)&ArgList + 2
      sub_404AD0(Block);  // 游标读 4 字节 → Block
      pObj3 = sub_541A30();  // 存 摊位条目名取串
      (*(void (/*thiscall*/ **)(int, uint32_t, void *))(*(uint32_t *)pObj3 + 68))(pObj3, HIWORD(ArgList), Block[0]);  // 虚表 +68 调用
      return 1;  // 返回 1（已处理该包）
    case 84:  // 【case 84】包类型分支
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      v579 = 0;  // v579 复制自 0
      LODWORD(pObj32) = 0;
      memset(&pBuf2[19], 0, 41);  // 调用 memset
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      v489 = *(int **)(dword_8F8500 + 8);  // v489 存调用结果
      v490 = (void **)(dword_8F8500 + 8);  // v490 存调用结果
      pObj12 = *v489;  // 取 v489 首字段
      for ( i5 = v489; (uint8_t)sub_4296C0(&i5) != 0; i5 = *v490 )  // 循环控制
      {
        off_77F3FC("user_id : %d ", *(uint16_t *)(*(uint32_t *)(pObj12 + 16) + 4));  // 控制台调试日志输出
        sub_429780(Block, 0);  // STL 内联迭代器后置自增 旧节点写入 uArg2，sub_41C5E0
      }
      for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )  // 循环控制
      {
        sub_404AB0(&v579);  // 游标读 2 字节 → &v579
        sub_48BCC0(&pBuf2[19], 41, nullptr);  // 限量串读入（带回退）
        sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
        sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
        sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
        sub_404AB0((char *)&v565 + 2);  // 游标读 2 字节 → (char *)&v565 + 2
        sub_404AB0(&pObj32);  // 游标读 2 字节 → &pObj32
        off_77F3FC("store_owner_id : %d", (uint16_t)v579);  // 控制台调试日志输出
        if ( sub_429830(v579) != 0 )  // 条件判定
        {
          v491 = *(uint32_t *)(sub_429830(v579) + 192);  // v491 存调用结果
          if ( v491 != 0 )  // v491 不等于 0
          {
            sub_42FBB0(v491, HIBYTE(v574), HIBYTE(v580), SHIWORD(v565), (int16_t)pObj32);  // 个人商店准备 【个人商店准备】【推断：+648 为摆摊组件槽】组件存在 →
            sub_430230(v491);  // 个人商店开店定位 【个人商店开店定位】
            if ( HIBYTE(v572) != 0 )  // v572 高字节 != 0
            {
              sub_42FC00(&pBuf2[19]);  // 商店操作转发 【商店操作转发】+648 组件存在 → 清 +285 →
              sub_42FBF0(v491);  // 商店标志消解 【商店标志消解】+284 与 +285 均置位时清 +285。
            }
          }
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 65] case 85：摆摊列表（40 行，sub_4296C0/sub_429780/sub_42FBB0 族） ──
    case 85:  // 【case 85】包类型分支
      v492 = (uint32_t *)dword_8F7C08;  // v492 ← 表达式
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      sub_42FC30(HIBYTE(v574) == 0);  // 商店状态字写入
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      if ( v492[162] != 0 )  // 条件判定
        goto LABEL_877;  // 转到 LABEL_877
      if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
      {
        sub_431160(v492, 1);  // 【驴子开关】Block=1：已存在 → off_77F3FC
LABEL_877:
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          v493 = *(uint32_t *)(dword_8F7A24 + 20);  // 读 dword_8F7A24+20 处 4 字节
          v494 = *(uint32_t *)(v493 + 100);  // 读 v493+100 处 4 字节
          v556 = (*(int (/*thiscall*/ **)(uint32_t *))(*v492 + 124))(v492);  // 虚表 +124 调用
          v525 = (*(int (/*thiscall*/ **)(uint32_t *))(*v492 + 120))(v492);  // 虚表 +120 调用
          v495 = sub_42F240(v493);  // 存 取动画对象 id 【取动画对象 id】返回 +104 槽对象首字段；空槽返 -1。
          sub_42FBB0(v492, v494, v495, v525, v556);  // 个人商店准备 【个人商店准备】【推断：+648 为摆摊组件槽】组件存在 →
          sub_430230(v492);  // 个人商店开店定位 【个人商店开店定位】
          sub_42FBF0(v492);  // 商店标志消解 【商店标志消解】+284 与 +285 均置位时清 +285。
          sub_541A60(1);  // 摊位子页切换
          for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )  // 循环控制
          {
            sub_404AB0((char *)&v567 + 2);  // 游标读 2 字节 → (char *)&v567 + 2
            sub_404AD0(&pObj32);  // 游标读 4 字节 → &pObj32
            sub_404AB0((char *)&v565 + 2);  // 游标读 2 字节 → (char *)&v565 + 2
            sub_404AD0(Block);  // 游标读 4 字节 → Block
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404AB0((char *)&v572 + 2);  // 游标读 2 字节 → (char *)&v572 + 2
            pObj19 = sub_541A30();  // 存 摊位条目名取串
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, void *, uint32_t, uint32_t))(*(uint32_t *)pObj19 + 56))(  // 虚表 +56 调用
              pObj19,  // 第 1 个实参
              HIWORD(v567),  // 第 2 个实参
              pObj32,  // 第 3 个实参
              HIWORD(v565),  // 第 4 个实参
              Block[0],  // 第 5 个实参
              HIBYTE(v580),  // 第 6 个实参
              HIWORD(v572));  // 第 7 个实参
          }
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 66] case 86：★ 物品强化回报（isSuccess/upgradeRank/serverId/itemIndex）—— sub_4F2CE0 + 结果播报 ──
    case 86:  // 【case 86】包类型分支
      HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
      sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
      if ( HIBYTE(v574) == 1 )  // v574 高字节 == 1
      {
        HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
        HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
        i5 = nullptr;  // i5 复制自 nullptr
        pObj12 = 0;  // pObj12 复制自 0
        sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
        sub_404AB0(&i5);  // 游标读 2 字节 → &i5
        sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
        sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
        off_77F3FC(  // 控制台调试日志输出
          "isSuccess %d, upgradeRank %d, serverId %d, itemIdex %d",  // 第 1 个实参：串 isSuccess %d, upgradeRank %d, serverId %d, itemIdex %d
          HIBYTE(v580),  // 第 2 个实参
          HIBYTE(ArgList),  // 第 3 个实参
          (uint16_t)i5,  // 第 4 个实参：双字节 i5
          (uint16_t)pObj12);  // 第 5 个实参：双字节 pObj12
        v497 = sub_429830(i5);  // 存 表按键查找
        if ( v497 != 0 )  // v497 不等于 0
        {
          if ( HIBYTE(v580) != 0 )  // v580 高字节 != 0
          {
            v557 = sub_4F2CE0((uint16_t)pObj12);  // 存 按物品 id 取名称串：查模板表
            v526 = HIBYTE(ArgList);  // v526 存调用结果
            v513 = unknown_libname_2(v497 + 16);  // CRT 内部辅助调用
            v498 = (const char *)sub_422E70(1673);  // 存 CStringManager::getStr 取本地化串
          }
          else
          {
            ++HIBYTE(ArgList);  // 调用 HIBYTE
            v557 = sub_4F2CE0((uint16_t)pObj12);  // 存 按物品 id 取名称串：查模板表
            v526 = HIBYTE(ArgList);  // v526 存调用结果
            v513 = unknown_libname_2(v497 + 16);  // CRT 内部辅助调用
            v498 = (const char *)sub_422E70(1674);  // 存 CStringManager::getStr 取本地化串
          }
          sprintf(Format, v498, v513, v526, v557);  // 格式化写入 Format
          off_77F3FC(Format);  // 控制台调试日志输出
          sub_43BEE0(Format, -6567706, 0, -1);  // 【播报上屏】
        }
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 67] case 87：★ 战争房间列表（WAR RoomNumber + 逐房字段，76 行）—— sub_49F7D0 建房间条目 ──
    case 87:  // 【case 87】包类型分支
      v579 = 0;  // v579 复制自 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("WAR RoomNumber %d", (uint16_t)v579);  // 控制台调试日志输出
      HIDWORD(pObj32) = 0;
      if ( (uint16_t)v579 != 0 )  // 条件判定
      {
        do
        {
          v366 = 0;  // v366 复制自 0
          v581 = 0;  // v581 复制自 0
          pObj12 = 0;  // pObj12 复制自 0
          i5 = nullptr;  // i5 复制自 nullptr
          HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
          sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
          sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
          sub_404A90(&v581);  // 游标读 1 字节 → &v581
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          off_77F3FC(  // 控制台调试日志输出
            "WAR RoomIndex %d, dungeonKind %d, levelSeparation %d, listIndex %d, RoomState %d warRoomMapIndex %d",  // 第 1 个实参：串 WAR RoomIndex %d, dungeonKind %d, levelSeparation %d, listIndex %d, RoomState %d warRoomMapIndex %d
            (uint16_t)pObj12,  // 第 2 个实参：双字节 pObj12
            HIBYTE(v574),  // 第 3 个实参
            HIBYTE(ArgList),  // 第 4 个实参
            HIBYTE(v580),  // 第 5 个实参
            (char)v581,  // 第 6 个实参
            (uint16_t)i5);  // 第 7 个实参：双字节 i5
          HIBYTE(ArgList) -= dword_77F888;  // 字节提取赋值
          v367 = (uint32_t *)sub_49F7D0((uint16_t)pObj12, HIBYTE(ArgList));  // 存 槽条目改写或新建插入
          v367[18] = (char)v581;  // 数组元素写入
          v367[19] = (uint16_t)i5;  // 数组元素写入
          HIBYTE(v567) = 0;  // 高字节写 v567 ← 0
          HIBYTE(v565) = 0;  // 高字节写 v565 ← 0
          v368 = v367 + 10;
          do
          {
            HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
            LODWORD(pObj32) = 0;
            sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
            sub_404AB0(&pObj32);  // 游标读 2 字节 → &pObj32
            if ( HIBYTE(v572) == 0xFF )  // v572 高字节 == 0xFF
            {
              if ( *v368 == (uint16_t)word_77F804 )  // 条件判定
                HIBYTE(v567) = 1;  // 高字节写 v567 ← 1
            }
            else if ( (uint16_t)pObj32 == (uint16_t)word_77F804 )
            {
              HIBYTE(v565) = 1;  // 高字节写 v565 ← 1
            }
            sub_4900E0(v366++, (uint16_t)pObj32, HIBYTE(v572));  // 角色槽位/物件状态切换总入口 @@SET HOST 宿主转移、LADDER_DOWN 音效、新对象 vtable+372 广播
            ++v368;  // v368 自增
          }
          while ( v366 < 8 );  // 调用 while
          if ( HIBYTE(v565) != 0 )  // v565 高字节 != 0
          {
            sub_48FE80(v367);  // 宿主/UDP 联动收尾
          }
          else if ( HIBYTE(v567) != 0 )
          {
            sub_48FE80(0);  // 宿主/UDP 联动收尾
          }
          if ( v581 != 0xFF )  // v581 不等于 0xFF
            sub_42C6A0(pObj12);  // 提示串直取
          ++HIDWORD(pObj32);  // 调用 HIDWORD
        }
        while ( SHIDWORD(pObj32) < (uint16_t)v579 );  // 调用 while
      }
      if ( dword_9B9454 != 0 )  // dword_9B9454 不等于 0
        sub_62E460(1);  // 列表刷新
      v369 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 10) + 20);  // v369 存调用结果
      *(uint8_t *)(v369 + 16) = (uint16_t)v579 != 0;  // v369+16 写字节 (uint16_t)v579 != 0
      sub_545730(*((uint32_t *)dword_8F8528 + 10));  // 输入框打开
      return 1;  // 返回 1（已处理该包）
    // ── [段 68] case 88：战争房间状态（WarRoomIndex/RoomState）—— sub_42C570/sub_42F160/sub_49EDC0/sub_62E460 ──
    case 88:  // 【case 88】包类型分支
      i5 = nullptr;  // i5 复制自 nullptr
      v579 = 0;  // v579 复制自 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      v375 = 0;  // v375 复制自 0
      if ( (uint16_t)i5 != 0 )  // 条件判定
      {
        do
        {
          sub_404AB0(&v579);  // 游标读 2 字节 → &v579
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          off_77F3FC("WarRoomIndex %d, RoomState %d", (uint16_t)v579, SHIBYTE(ArgList));  // 控制台调试日志输出
          v376 = sub_49EDC0((uint16_t)v579, -1);  // 存 红黑树多槽查表
          if ( v376 != 0 )  // v376 不等于 0
          {
            v377 = *(uint8_t *)(v376 + 72);  // v377 存调用结果
            *(uint32_t *)(v376 + 72) = SHIBYTE(ArgList);  // v376+72 写 SHIBYTE(ArgList)
            if ( dword_99FF08 == v376 )  // dword_99FF08 等于 v376
              sub_42F160(SHIBYTE(ArgList), 0);  // 决斗场状态机 【决斗场状态机】写 +32 状态并复位时钟
            else
              sub_42C570(v579, v377, SHIBYTE(ArgList));  // 提示播报
            if ( (HIBYTE(ArgList) == 0xFF || HIBYTE(ArgList) == 0) && dword_9B9454 != 0 )  // 条件判定
              sub_62E460(1);  // 列表刷新
          }
          else
          {
            off_77F3FC(aCriticalError_30, (uint16_t)v579);  // 控制台调试日志输出
          }
          ++v375;  // v375 自增
        }
        while ( v375 < (uint16_t)i5 );  // 调用 while
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 69] case 89：战争房间座位表（WARRoomIndex/dataCount + SeatIndex/SeatState/ServerId） ──
    case 89:  // 【case 89】包类型分支
      v579 = 0;  // v579 复制自 0
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      off_77F3FC("WARRoomIndex %d, dataCount %d", (uint16_t)v579, HIBYTE(ArgList));  // 控制台调试日志输出
      v378 = sub_49EDC0((uint16_t)v579, -1);  // 存 红黑树多槽查表
      if ( v378 != 0 )  // v378 不等于 0
      {
        LODWORD(pObj32) = 0;
        if ( HIBYTE(ArgList) != 0 )  // ArgList 高字节 != 0
        {
          do
          {
            HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
            pObj12 = 0xFFFF;  // pObj12 复制自 0xFFFF
            sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
            sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
            sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
            off_77F3FC("SeatIndex %d, SeatState %d, ServerId %d", HIBYTE(v580), HIBYTE(v574), (uint16_t)pObj12);  // 控制台调试日志输出
            v379 = false;  // v379 复制自 false
            HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
            if ( HIBYTE(v574) == 0xFF )  // v574 高字节 == 0xFF
              HIBYTE(v572) = *(uint32_t *)(v378 + 4 * HIBYTE(v580) + 40) == (uint16_t)word_77F804;  // 字节提取赋值
            else
              v379 = (uint16_t)pObj12 == (uint16_t)word_77F804;  // v379 ← 表达式
            sub_4900E0(SHIBYTE(v580), (uint16_t)pObj12, HIBYTE(v574));  // 角色槽位/物件状态切换总入口 @@SET HOST 宿主转移、LADDER_DOWN 音效、新对象 vtable+372 广播
            if ( v379 )  // 条件判定
            {
              sub_48FE80(v378);  // 宿主/UDP 联动收尾
            }
            else if ( HIBYTE(v572) != 0 )
            {
              sub_48FE80(0);  // 宿主/UDP 联动收尾
            }
            LODWORD(pObj32) = pObj32 + 1;
          }
          while ( (int)pObj32 < HIBYTE(ArgList) );  // 调用 while
        }
      }
      else
      {
        off_77F3FC(aCriticalError_30, (uint16_t)v579);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 70] case 90/91：战争房间计时（maxMonsterCount/MonsterCount，sub_42B5F0/sub_42B7C0/sub_42C9A0/sub_42E230） ──
    case 90:  // 【case 90】包类型分支
      off_77F3FC((char *)&byte_728AB8);  // 控制台调试日志输出
      return 1;  // 返回 1（已处理该包）
    case 91:  // 【case 91】包类型分支
      HIBYTE(v565) = 0;  // 高字节写 v565 ← 0
      pObj12 = 0;  // pObj12 复制自 0
      sub_404A90((char *)&v565 + 3);  // 游标读 1 字节 → (char *)&v565 + 3
      sub_404AB0(&pObj12);  // 游标读 2 字节 → &pObj12
      sub_42C9A0(pArg12[10]);  // 缓冲释清
      off_77F3FC("maxMonsterCount %d MonsterCount %d", HIBYTE(v565), (uint16_t)pObj12);  // 控制台调试日志输出
      pObj123 = pObj12;  // pObj123 复制自 pObj12
      v381 = 0;  // v381 复制自 0
      if ( (uint16_t)pObj12 != 0 )  // 条件判定
      {
        do
        {
          v571 = 0;  // v571 复制自 0
          i5 = nullptr;  // i5 复制自 nullptr
          HIBYTE(v572) = 0;  // 高字节写 v572 ← 0
          HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
          HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
          HIBYTE(v574) = 0;  // 高字节写 v574 ← 0
          sub_404AB0(&v571);  // 游标读 2 字节 → &v571
          sub_404A90((char *)&v572 + 3);  // 游标读 1 字节 → (char *)&v572 + 3
          sub_404A90((char *)&v574 + 3);  // 游标读 1 字节 → (char *)&v574 + 3
          sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
          sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
          sub_404AB0(&i5);  // 游标读 2 字节 → &i5
          off_77F3FC(  // 控制台调试日志输出
            "uniqueId %d type %d level %d sequence %d posSequence %d nextMonsterMakeInterval %d",  // 第 1 个实参：串 uniqueId %d type %d level %d sequence %d posSequence %d nextMonsterMakeInterval %d
            (uint16_t)v571,  // 第 2 个实参：双字节 v571
            HIBYTE(v572),  // 第 3 个实参
            HIBYTE(v574),  // 第 4 个实参
            HIBYTE(v580),  // 第 5 个实参
            HIBYTE(ArgList),  // 第 6 个实参
            (uint16_t)i5);  // 第 7 个实参：双字节 i5
          sub_42E230(  // sub_42E230：24B 条目入队封装
            (uint16_t)v571,  // 第 1 个实参：双字节 v571
            HIBYTE(v572),  // 第 2 个实参
            HIBYTE(v574),  // 第 3 个实参
            HIBYTE(v580),  // 第 4 个实参
            HIBYTE(ArgList),  // 第 5 个实参
            (uint16_t)i5);  // 第 6 个实参：双字节 i5
          pObj123 = pObj12;  // pObj123 复制自 pObj12
          ++v381;  // v381 自增
        }
        while ( v381 < (uint16_t)pObj12 );  // 调用 while
      }
      sub_42B7C0(HIBYTE(v565), pObj123);  // 三字段写
      sub_42B5F0(pArg12[10]);  // 时钟归零
      return 1;  // 返回 1（已处理该包）
    // ── [段 71] case 92：★ 结算点数落地（myFinishPoint/gainedSP/各加成经验）—— 写 dword_8F8528+607 行的 6 个字段 ──
    //   随后 sub_49E050(1) 触发结算界面
    case 92:  // 【case 92】包类型分支
      i5 = nullptr;  // i5 复制自 nullptr
      v571 = 0;  // v571 复制自 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      v575 = 0;  // v575 复制自 0
      pObj12 = 0;  // pObj12 复制自 0
      v579 = 0;  // v579 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AD0(&i5);  // 游标读 4 字节 → &i5
      sub_404AD0(&v571);  // 游标读 4 字节 → &v571
      sub_404AD0(v568);  // 游标读 4 字节 → v568
      sub_404AD0(&v575);  // 游标读 4 字节 → &v575
      sub_404AD0(&pObj12);  // 游标读 4 字节 → &pObj12
      sub_404AD0(&v579);  // 游标读 4 字节 → &v579
      off_77F3FC(  // 控制台调试日志输出
        "myFinishPoint %d gainedSP %d gainedOriginalExp %d gainedAvatarBonusExp %d, gainedPremiumBonusExp %d, gainedMatch"  // 第 1 个实参：串 myFinishPoint %d gainedSP %d gainedOriginalExp %d gainedAvatarBonusExp %d, gainedPremiumBonusExp %d, gainedMatch
        "edChannelBonusExp %d, gainedMemberBonusExp %d",  // 第 1 个实参：串 edChannelBonusExp %d, gainedMemberBonusExp %d
        i5,  // 第 2 个实参
        HIBYTE(ArgList),  // 第 3 个实参
        v571,  // 第 4 个实参
        *(uint32_t *)v568,  // 第 5 个实参
        v575,  // 第 6 个实参
        pObj12,  // 第 7 个实参
        v579);  // 第 8 个实参
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 124) = i5;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 144) = v571;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 128) = *(uint32_t *)v568;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 132) = v575;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 136) = pObj12;  // 内存写入
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 607) + 140) = v579;  // 内存写入
      sub_49E050(1);  // M_RESULT 演出
      return 1;  // 返回 1（已处理该包）
    // ── [段 72] case 93：★ 拾取物品（ItemUniqueId/ServerId + SlotIndex + ITEM_PICK，96 行） ──
    //   门 pArg1[3]==6（场景类型）→ sub_432EA0 播报 + sub_4337E0 背包刷新
    case 93:  // 【case 93】包类型分支
      if ( pArg1[3] != 6 )  // 条件判定
        off_77F3FC(aCriticalError_26);  // 控制台调试日志输出
      i5 = nullptr;  // i5 复制自 nullptr
      v571 = 0;  // v571 复制自 0
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      sub_404AB0(&v571);  // 游标读 2 字节 → &v571
      off_77F3FC("ItemUniqueId %d, ServerId %d", (uint16_t)i5, (uint16_t)v571);  // 控制台调试日志输出
      v339 = sub_45EBE0(289, (uint16_t)i5);  // 存 id 对 → 对象查找
      pObj34 = __RTDynamicCast(v339, 0, &CNRDObject `RTTI Type Descriptor', &CNRDItemObject `RTTI Type Descriptor', 0);  // pObj34 存调用结果
      pObj342 = pObj34;  // pObj342 复制自 pObj34
      if ( pObj34 != 0  // 条件判定
        && ((*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj34 + 84))(pObj34, 0),  // 第 1 个实参：地址 && ((*(void (·thiscall· **)(int, uint32_t))(*(uint32_t *)pObj34 + 84))(pObj34, 0
            (v342 = *(uint32_t **)(pObj342 + 972)) != nullptr) )  // 第 2 个实参
      {
        if ( (uint16_t)v571 == (uint16_t)word_77F804 )  // 低 16 位比较 v571 == word_77F804
        {
          v343 = sub_41C1B0(dword_8F8500);  // 存 按全局键 word_77F804 查表取对象
          sub_484FF0(dword_8F852C);  // 4 字节列表尾部弹出
          v344 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342) + 4);  // 虚表 +16 调用
          *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
          if ( v344 != 0 )  // v344 不等于 0
          {
            sub_404AB0(&ArgList);  // 游标读 2 字节 → &ArgList
            off_77F3FC("SlotIndex %d", (uint16_t)ArgList);  // 控制台调试日志输出
            v345 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 44))(v342);  // 虚表 +44 调用
            sub_4337E0(v342, v345, v343, 0);  // 【物品获得播报】串 1179/1180 格式化
            sub_57A360(pObj342);  // 字符串辅助
            LODWORD(pObj32) = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 44))(v342);  // 虚表 +44 调用
            HIDWORD(pObj32) = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 36))(v342);  // 虚表 +36 调用
            sub_432EA0("ITEM_PICK", -1, 0, 0);  // 音效播放包装
            v346 = (uint16_t)ArgList;  // v346 ← 表达式
            v347 = (uint32_t *)sub_44A980((uint16_t)ArgList);  // 存 带界索引 getter nArg2 ≥ [2]
            v348 = v347;  // v348 复制自 v347
            if ( v347 != nullptr )  // v347 不等于 nullptr
            {
              v349 = *v347;  // 取 v347 首字段
              v350 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342);  // 虚表 +16 调用
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(v349 + 60))(v348, *(uint32_t *)(v350 + 4)) != 0 )  // 虚表 +60 调用
              {
                (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v348 + 48))(v348, pObj32);  // 虚表 +48 调用
              }
              else
              {
                v351 = (*(int (/*thiscall*/ **)(uint32_t *))(*v342 + 16))(v342);  // 虚表 +16 调用
                v352 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*v348 + 16))(v348, *(uint32_t *)(v351 + 4));  // 虚表 +16 调用
                off_77F3FC(aErrorD_2, (uint16_t)ArgList, *(uint32_t *)(v352 + 4));  // 控制台调试日志输出
              }
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*v342 + 4))(v342, 1);  // 虚表 +4 调用
            }
            else
            {
              sub_484F40(v346, v342, 1);  // 技能槽装载
              v348 = v342;  // v348 复制自 v342
            }
            v353 = *((uint32_t *)dword_8F852C + 1);  // v353 存调用结果
            v354 = v353 - sub_484FA0();  // v354 存调用结果
            v566 = (uint32_t *)v354;  // v566 ← 表达式
            if ( v354 <= 0 || SHIDWORD(pObj32) <= 0 )  // 条件判定
            {
LABEL_336:
              sub_47CD00(dword_8F8540);  // 逐条处理型别 fld[68]==0 的条件条目：为已注册
            }
            else
            {
              v355 = v354 - 1;  // v355 ← 表达式
              v356 = v355 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v348 + 16))(v348) + 56);  // 虚表 +16 调用
              pObj326 = pObj32;  // pObj326 复制自 pObj32
              if ( v356 + 1 < (int)pObj32 )  // 条件判定
                pObj326 = v355 / *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v348 + 16))(v348) + 56) + 1;  // 虚表 +16 调用
              sub_486330((uint16_t)ArgList, pObj326);  // 请求 op 50
              v358 = (const char *)sub_422E70(654);  // 存 CStringManager::getStr 取本地化串
              sprintf(OutputString, v358, (double)(int)v566 * 0.0099999998);  // 格式化写入 OutputString
              sub_43BEE0(OutputString, -6567706, 0, -1);  // 【播报上屏】
            }
          }
          else
          {
            sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
            off_77F3FC("MONEY %u", ArgList);  // 控制台调试日志输出
            if ( *(float *)&ArgList != 0.0 )  // 条件判定
            {
              (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 48))(  // 虚表 +48 调用
                **((uint32_t **)dword_8F852C + 3),  // 第 1 个实参
                ArgList);  // 第 2 个实参
              sub_432EA0("ITEM_PICK", -1, 0, 0);  // 音效播放包装
              sub_4337E0(v342, ArgList, v343, 0);  // 【物品获得播报】串 1179/1180 格式化
            }
          }
        }
      }
      else
      {
        off_77F3FC(aCriticalError_27);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 73] case 94：★ KP（战场点数）加成（seatIndex/incKc）—— getMyRoom()==NULL 时报错返回 ──
    //   sub_48FB60 取房间 → sub_578E80 取席位 → 写 dword_99FF084 的 +80/+112 双槽
    case 94:  // 【case 94】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v579 = 0;  // v579 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      off_77F3FC("seatIndex %d incKc %d", HIBYTE(ArgList), (uint16_t)v579);  // 控制台调试日志输出
      dword_99FF083 = dword_99FF08;  // 全局 dword_99FF083 ← dword_99FF08
      if ( dword_99FF08 != 0 && sub_578E80(HIBYTE(ArgList)) != 0 )  // 条件判定
      {
        *(uint32_t *)(dword_99FF083 + 4 * HIBYTE(ArgList) + 80) += (uint16_t)v579;
        *(uint32_t *)(dword_99FF083 + 4 * HIBYTE(ArgList) + 112) += (uint16_t)v579;
        sub_4632D0(*((uint32_t *)dword_8F8528 + 4));  // 席位表快照与排序 dword_99FF08 表 +80 起 8 个值写入 this+335 起
        if ( *(uint32_t *)(sub_578E80(HIBYTE(ArgList)) + 196) != 0 )  // 条件判定
        {
          v500 = sub_578E80(HIBYTE(ArgList));  // 存 调: sub_578E80 sub_48F660
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(v500 + 196)
                                                                                         + 1264))(  // 第 1 个实参
            *(uint32_t *)(v500 + 196),  // 第 1 个实参
            (uint16_t)v579,  // 第 2 个实参：双字节 v579
            0,  // 第 3 个实参：常量 0
            0,  // 第 4 个实参：常量 0
            0,  // 第 5 个实参：常量 0
            0,  // 第 6 个实参：常量 0
            0);  // 第 7 个实参：常量 0
        }
      }
      else
      {
        off_77F3FC("ENUM_NOTIPACKET_ADD_KP : getMyRoom() == NULL");  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    // ── [段 74] case 95：★ 战场死亡/金币插入（dieSeatIndex/isLive/isUseCoin/addKP/lastAttackerServerId，241 行） ──
    //   死亡方切换观战；COIN_INSERT 播报 + sub_49BDB0(0/1/2) 三态 + sub_424A40 切镜头（LABEL_733/734/747/751 网状）
    case 95:  // 【case 95】包类型分支
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      v581 = 0;  // v581 复制自 0
      v573 = 0;  // v573 复制自 0
      v579 = 0;  // v579 复制自 0
      i5 = (void *)0xFFFF;  // i5 ← 表达式
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90(&v581);  // 游标读 1 字节 → &v581
      sub_404A90(&v573);  // 游标读 1 字节 → &v573
      sub_404AB0(&v579);  // 游标读 2 字节 → &v579
      sub_404AB0(&i5);  // 游标读 2 字节 → &i5
      off_77F3FC(  // 控制台调试日志输出
        "dieSeatIndex %d isLive %d isUseCoin %d addKP %d lastAttackerServerId %d",  // 第 1 个实参：串 dieSeatIndex %d isLive %d isUseCoin %d addKP %d lastAttackerServerId %d
        HIBYTE(ArgList),  // 第 2 个实参
        v581,  // 第 3 个实参
        v573,  // 第 4 个实参
        (uint16_t)v579,  // 第 5 个实参：双字节 v579
        (uint16_t)i5);  // 第 6 个实参：双字节 i5
      dword_99FF084 = dword_99FF08;  // 全局 dword_99FF084 ← dword_99FF08
      v566 = (uint32_t *)dword_99FF08;  // v566 ← 表达式
      if ( dword_99FF08 == 0 )  // dword_99FF08 等于 0
      {
        off_77F3FC((char *)&byte_7289CC);  // 控制台调试日志输出
        return 1;  // 返回 1（已处理该包）
      }
      v571 = -1;  // 局部 v571 → -1
      LODWORD(pObj32) = sub_48FB60((uint16_t)i5, &v571);  // 调用 LODWORD
      v383 = sub_578E80(HIBYTE(ArgList));  // 存 调: sub_578E80 sub_48F660
      if ( (uint32_t)pObj32 != 0 && v383 != 0 )  // 条件判定
      {
        *(uint32_t *)(dword_99FF084 + 4 * v571 + 80) += (uint16_t)v579;
        *(uint32_t *)(dword_99FF084 + 4 * v571 + 112) += (uint16_t)v579;
        sub_4632D0(*((uint32_t *)dword_8F8528 + 4));  // 席位表快照与排序 dword_99FF08 表 +80 起 8 个值写入 this+335 起
        *(uint32_t *)v568 = *(uint32_t *)(v383 + 196);  // 内存写入
        if ( *(uint32_t *)v568 != 0 )  // 条件判定
        {
          v384 = **(uint32_t **)v568;  // v384 ← 表达式
          v385 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v568 + 128))(*(uint32_t *)v568);  // 虚表 +128 调用
          v386 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)v568 + 124))(*(uint32_t *)v568, v385);  // 虚表 +124 调用
          v387 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)v568 + 120))(*(uint32_t *)v568, v386);  // 虚表 +120 调用
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(v384 + 1264))(  // 虚表 +1264 调用
            *(uint32_t *)v568,  // 第 1 个实参
            (uint16_t)v579,  // 第 2 个实参：双字节 v579
            0,  // 第 3 个实参：常量 0
            1,  // 第 4 个实参：常量 1
            v387);  // 第 5 个实参
        }
      }
      v388 = sub_48FD80(dword_99FF084);  // 存 空槽计数
      v389 = pArg12[10];  // v389 ← 表达式
      LODWORD(pObj32) = v388;
      v580 = *(uint32_t *)(v389 + 16);  // 读 v389+16 处 4 字节
      v390 = nullptr;  // v390 复制自 nullptr
      *(uint32_t *)netshort = *(uint32_t *)(v580 + 104);  // 内存写入
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      while ( 1 )  // 循环控制
      {
        v391 = sub_578E80(v390);  // 存 调: sub_578E80 sub_48F660
        v572 = v391;  // v572 复制自 v391
        if ( v391 != 0 && *(uint32_t *)(v391 + 196) != 0 && v390 == (int *)HIBYTE(ArgList) )  // 条件判定
          break;
        v390 = (int *)((char *)v390 + 1);  // v390 存调用结果
        if ( (int)v390 >= 8 )  // 条件判定
        {
          *(uint32_t *)v568 = v390;  // 指针 v568 写 v390
          goto LABEL_734;  // 转到 LABEL_734
        }
      }
      *(uint32_t *)v568 = v390;  // 指针 v568 写 v390
      v392 = *(int **)(v572 + 196);  // v392 存调用结果
      if ( v581 != 1 )  // v581 不等于 1
      {
        sub_4B12B0(1);  // 事件分发
        v413 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*v392 + 124))(v392, 0);  // 虚表 +124 调用
        v511 = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 120))(v392, v413);  // 虚表 +120 调用
        v414 = sub_4633B0(v392);  // 存 std::string 取数据指针
        off_77F3FC(aS_8, v414, v511);  // 控制台调试日志输出
        if ( (int)pObj32 > 1 )  // 条件判定
          sub_45F1E0(v392);  // 对象注销/退场
        v415 = v572 + 16;
        *(uint8_t *)(HIBYTE(ArgList) + dword_99FF084 + 144) = 1;  // 内存写入
        v548 = unknown_libname_2(v415);  // CRT 内部辅助调用
        v416 = (const char *)sub_422E70(648);  // 存 CStringManager::getStr 取本地化串
        sprintf(&Destination, v416, v548);  // 调用 sprintf
        v412 = (void *)sub_43BEE0(&Destination, -6567706, 0, -1);  // 存 【播报上屏】
        goto LABEL_733;  // 转到 LABEL_733
      }
      if ( (uint8_t)sub_45E680(v392) != 0 )  // 条件判定
      {
        sub_45F1E0(v392);  // 对象注销/退场
        if ( (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392) != 0 )  // 虚表 +1120 调用
        {
          v393 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392);  // 虚表 +1120 调用
          sub_45F1E0(v393);  // 对象注销/退场
        }
      }
      (*(void (/*thiscall*/ **)(int *))(*v392 + 1020))(v392);  // 虚表 +1020 调用
      (*(void (/*thiscall*/ **)(int *, int))(*v392 + 1200))(v392, 1);  // 虚表 +1200 调用
      *(uint8_t *)(HIBYTE(ArgList) + dword_99FF084 + 144) = 0;  // 内存写入
      v394 = *v392;  // 取 v392 首字段
      v395 = *v392;  // 取 v392 首字段
      if ( v573 == 1 )  // v573 等于 1
      {
        v396 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v394 + 740))(v392, 0, 1);  // 虚表 +740 调用
        (*(void (/*thiscall*/ **)(int *, int))(v395 + 732))(v392, v396);  // 虚表 +732 调用
        v397 = *v392;  // 取 v392 首字段
        LODWORD(v398) = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 756))(v392, 1);  // 虚表 +756 调用
      }
      else
      {
        HIDWORD(pObj32) = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v394 + 740))(v392, 0, 1);  // 虚表 +740 调用
        (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t))(v395 + 732))(  // 虚表 +732 调用
          v392,  // 第 1 个实参
          (uint64_t)((double)SHIDWORD(pObj32) * 0.80000001) >> 32,  // 第 2 个实参
          (uint64_t)((double)SHIDWORD(pObj32) * 0.80000001));  // 第 3 个实参
        v397 = *v392;  // 取 v392 首字段
        HIDWORD(pObj32) = (*(int (/*thiscall*/ **)(int *, int))(*v392 + 756))(v392, 1);  // 虚表 +756 调用
        v398 = (uint64_t)((double)SHIDWORD(pObj32) * 0.80000001);  // v398 存调用结果
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v397 + 748))(v392, v398);  // 虚表 +748 调用
      v399 = v572;  // v399 复制自 v572
      sub_45FE80(273, *(uint16_t *)(v572 + 4), v392, 0, 0);  // 对象注册
      if ( (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392) != 0 )  // 虚表 +1120 调用
      {
        v400 = *(uint16_t *)(v399 + 4);  // v400 存调用结果
        v401 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1120))(v392);  // 虚表 +1120 调用
        sub_45FE80(65, v400, v401, 0, 0);  // 对象注册
      }
      sub_4B12B0(0);  // 事件分发
      v402 = (*(int (/*thiscall*/ **)(int *))(*v392 + 120))(v392);  // 虚表 +120 调用
      v403 = *v392;  // 取 v392 首字段
      v574 = v402;  // v574 复制自 v402
      v404 = *(uint32_t *)(v580 + 44);  // 读 v580+44 处 4 字节
      HIDWORD(pObj32) = (*(int (/*thiscall*/ **)(int *))(v403 + 124))(v392);  // 虚表 +124 调用
      if ( SHIDWORD(pObj32) >= sub_425050(v404) )  // 条件判定
        v405 = sub_425050(*(uint32_t *)(v580 + 44));  // 存 总宽换算 224 ×
      else
        v405 = (*(int (/*thiscall*/ **)(int *))(*v392 + 124))(v392);  // 虚表 +124 调用
      v406 = *v392;  // 取 v392 首字段
      pObj12 = v405;  // pObj12 复制自 v405
      (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(v406 + 140))(  // 虚表 +140 调用
        v392,  // 第 1 个实参
        &v574,  // 第 2 个实参：地址 &v574
        &pObj12,  // 第 3 个实参：地址 &pObj12
        v574,  // 第 4 个实参
        v405,  // 第 5 个实参
        640,  // 第 6 个实参：常量 640
        1,  // 第 7 个实参：常量 1
        1);  // 第 8 个实参：常量 1
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*v392 + 112))(v392, v574, pObj12, 0);  // 虚表 +112 调用
      v524 = (unsigned int)pObj12;  // v524 ← 表达式
      v510 = v574;  // v510 复制自 v574
      v407 = sub_4633B0(v392);  // 存 std::string 取数据指针
      off_77F3FC(aS_7, v407, v510, v524);  // 控制台调试日志输出
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v392 + 308))(v392) != 0  // 虚表 +308 调用
        && (uint8_t)sub_42B510(pArg12[10]) != 0 )  // 第 1 个实参：地址 && (uint8_t)sub_42B510(pArg12[10]) != 0
      {
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*v392 + 580))(  // 虚表 +580 调用
          v392,  // 第 1 个实参
          48001,  // 第 2 个实参：常量 48001
          1,  // 第 3 个实参：常量 1
          0,  // 第 4 个实参：常量 0
          0,  // 第 5 个实参：常量 0
          0,  // 第 6 个实参：常量 0
          0,  // 第 7 个实参：常量 0
          0,  // 第 8 个实参：常量 0
          4,  // 第 9 个实参：常量 4
          0,  // 第 10 个实参：常量 0
          0,  // 第 11 个实参：常量 0
          0);  // 第 12 个实参：常量 0
      }
      pObj29 = dword_8F7C04;  // pObj29 复制自 dword_8F7C04
      if ( (int *)dword_8F7C04 != v392 )  // 条件判定
        goto LABEL_725;  // 转到 LABEL_725
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*v392 + 560))(v392, 0, 0, 0, 0);  // 虚表 +560 调用
      (*(void (/*thiscall*/ **)(int *))(*v392 + 564))(v392);  // 虚表 +564 调用
      if ( v573 == 1 )  // v573 等于 1
      {
        sub_57A2F0(v580);  // std::string 辅助
        pObj29 = dword_8F7C04;  // pObj29 复制自 dword_8F7C04
LABEL_725:
        if ( v573 == 1 && pObj29 != 0 )  // 条件判定
        {
          v409 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj29 + 376))(pObj29);  // 虚表 +376 调用
          if ( v409 == (*(int (/*thiscall*/ **)(int *))(*v392 + 376))(v392) )  // 虚表 +376 调用
            sub_57A310(v580);  // std::string 辅助 2
        }
      }
      v547 = unknown_libname_2(v572 + 16);  // CRT 内部辅助调用
      v410 = (const char *)sub_422E70(647);  // 存 CStringManager::getStr 取本地化串
      sprintf(&Destination, v410, v547);  // 调用 sprintf
      sub_43BEE0(&Destination, -6567706, 0, -1);  // 【播报上屏】
      v411 = (*(int (/*thiscall*/ **)(int *))(*v392 + 1216))(v392);  // 虚表 +1216 调用
      sub_495DA0(v411);  // 96 字节元素双槽清零
      sub_49C620(1, 1, 0);  // 命令下发包装
      sub_49C5F0(1, 0, 0, 1500);  // 命令记录写入包装
      v412 = sub_432EA0("COIN_INSERT", -1, 0, 0);  // 存 音效播放包装
LABEL_733:
      LOBYTE(v412) = v581 == 0;  // 字节提取赋值
      (*(void (/*thiscall*/ **)(int *, void *))(*v392 + 1192))(v392, v412);  // 虚表 +1192 调用
      v390 = *(int **)v568;  // v390 ← 表达式
LABEL_734:
      HIDWORD(pObj32) = dword_8F7C04;
      if ( v390 == (int *)8 )  // 条件判定
        off_77F3FC((char *)&byte_728974);  // 控制台调试日志输出
      if ( (int)pObj32 > 0 )  // 条件判定
      {
        v417 = 0;  // v417 复制自 0
        while ( 1 )  // 循环控制
        {
          v418 = sub_578E80(v417);  // 存 调: sub_578E80 sub_48F660
          if ( v418 != 0 )  // v418 不等于 0
          {
            pObj7 = *(uint32_t *)(v418 + 196);  // 读 v418+196 处 4 字节
            if ( pObj7 != 0 )  // pObj7 不等于 0
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj7 + 1196))(*(uint32_t *)(v418 + 196)) != 0  // 虚表 +1196 调用
                && (uint8_t)sub_45E680(pObj7) != 0 )  // 第 1 个实参：地址 && (uint8_t)sub_45E680(pObj7) != 0
              {
                sub_45F1E0(pObj7);  // 对象注销/退场
              }
              else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 724))(dword_8F7C04) != 0 )  // 虚表 +724 调用
              {
                HIDWORD(pObj32) = pObj7;
LABEL_747:
                if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0 )  // 虚表 +1196 调用
                  sub_49BDB0(1);  // COUNT_DOWN 设置
                else
                  sub_49BDB0(0);  // COUNT_DOWN 设置
LABEL_751:
                sub_424A40(HIDWORD(pObj32));  // 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
                return 1;  // 返回 1（已处理该包）
              }
            }
          }
          if ( ++v417 >= 8 )  // 条件判定
            goto LABEL_747;  // 转到 LABEL_747
        }
      }
      sub_49BDB0(2);  // COUNT_DOWN 设置
      goto LABEL_751;  // 转到 LABEL_751
    // ── [段 75] case 96：★ 邮箱打开（Mail id/limit/name/money + 每封 item 字段）—— sub_524330 邮箱模块 ──
    //   sub_522300 建每封附件对象 → sub_524B80 入列表 → sub_523800 显示
    case 96:  // 【case 96】包类型分支
      v501 = sub_524330();  // 存 全局
      HIBYTE(ArgList) = 0;  // 高字节写 ArgList ← 0
      HIBYTE(v580) = 0;  // 高字节写 v580 ← 0
      *(uint32_t *)v568 = 0;  // 指针 v568 写 0
      i5 = nullptr;  // i5 复制自 nullptr
      *(uint32_t *)netshort = 0;  // 指针 netshort 写 0
      v579 = 0;  // v579 复制自 0
      v575 = 0;  // v575 复制自 0
      LOBYTE(pObj12) = 0;  // 低字节写 pObj12 ← 0
      v571 = 0;  // v571 复制自 0
      sub_404A90((char *)&ArgList + 3);  // 游标读 1 字节 → (char *)&ArgList + 3
      sub_404A90((char *)&v580 + 3);  // 游标读 1 字节 → (char *)&v580 + 3
      if ( HIBYTE(v580) == 0 )  // v580 高字节 == 0
        sub_523800(v501);  // 散装补漏小函数
      for ( ; HIBYTE(ArgList) != 0; --HIBYTE(ArgList) )  // 循环控制
      {
        sub_404AD0(v568);  // 游标读 4 字节 → v568
        sub_48BCC0(&v601, 30, nullptr);  // 限量串读入（带回退）
        sub_404AD0(&i5);  // 游标读 4 字节 → &i5
        sub_404AB0(netshort);  // 游标读 2 字节 → netshort
        sub_404AD0(&v579);  // 游标读 4 字节 → &v579
        sub_404AB0(&v575);  // 游标读 2 字节 → &v575
        sub_404A90(&pObj12);  // 游标读 1 字节 → &pObj12
        v502 = sub_522300((void *)netshort[0], v579, pObj12, 0, (uint16_t)v575, 1);  // 存 ★ PO 工厂分发器
        sub_404AD0(&v571);  // 游标读 4 字节 → &v571
        sub_524B80(nullptr, *(int *)v568, v571, &v601, i5, v502);  // 发送邮件主逻辑
        off_77F3FC("Mail    <> id : %d, limit : %d, name : %s, money : %d", *(uint32_t *)v568, v571, &v601, i5);  // 控制台调试日志输出
        off_77F3FC(  // 控制台调试日志输出
          " - item <> index : %d, data : %d, upgrade : %d, durability : %d",  // 第 1 个实参：串 - item <> index : %d, data : %d, upgrade : %d, durability : %d
          netshort[0],  // 第 2 个实参
          v579,  // 第 3 个实参
          (uint8_t)pObj12,  // 第 4 个实参：单字节 pObj12
          (uint16_t)v575);  // 第 5 个实参：双字节 v575
      }
      sub_404AB0((char *)&v574 + 2);  // 游标读 2 字节 → (char *)&v574 + 2
      v503 = SHIWORD(v574);  // v503 存调用结果
      *(uint32_t *)(sub_524330() + 8) = v503;  // 内存写入
      return 1;  // 返回 1（已处理该包）
    // ── [段 76] case 97/98：邮箱删除（delete mail count/id）/ 邮箱提取（sub_5226E0 + sub_524160） ──
    case 97:  // 【case 97】包类型分支
      sub_524330();  // 全局
      *(float *)&ArgList = 0.0;  // &ArgList 作浮点写 0.0
      i5 = nullptr;  // i5 复制自 nullptr
      sub_404AD0(&ArgList);  // 游标读 4 字节 → &ArgList
      off_77F3FC("delete mail count : %d", ArgList);  // 控制台调试日志输出
      while ( *(float *)&ArgList != 0.0 )  // 循环控制
      {
        sub_404AD0(&i5);  // 游标读 4 字节 → &i5
        v504 = sub_524160(i5);  // 存 容器扩容/访问辅助
        sub_523760(v504);  // 散装补漏小函数
        --ArgList;
        off_77F3FC("deleted mail id : %d", i5);  // 控制台调试日志输出
      }
      return 1;  // 返回 1（已处理该包）
    case 98:  // 【case 98】包类型分支
      v566 = nullptr;  // v566 复制自 nullptr
      sub_404AB0(&v566);  // 游标读 2 字节 → &v566
      if ( (int16_t)v566 > 0 )  // 条件判定
      {
        v505 = sub_422E70(2065);  // 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v505, -11600063, 0, -1);  // 【播报上屏】
        sub_5226E0();  // 薄转发 → sub_5226E0
      }
      v506 = (int16_t)v566;  // v506 ← 表达式
      *(uint32_t *)(sub_524330() + 4) = v506;  // 内存写入
      return 1;  // 返回 1（已处理该包）
    // ── [段 77] default：未识别包类型，静默 return 1（不中断连接） ──
    default:
      return 1;  // 返回 1（已处理该包）
  }
}

